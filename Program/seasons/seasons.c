#include "seasons\encounters.c"

object SeasonSystem;

#define CROWN_SEASON  "crown"
#define REED_SEASON   "reed"
#define STORM_SEASON  "storm"
#define SHADOW_SEASON "shadows"

// Проверяем, правильный ли сейчас сезон и запускаем сторю, если нет
bool SZN_CheckChange()
{
	if (!CheckAttributeHasValue(&SeasonSystem, "current")) return SZN_ChangeSeason();

	string currentSeason = SZN_GetCurrentSeasonName();
	string shouldBeSeason = SZN_SeasonForNow();
	if (currentSeason != shouldBeSeason) return SZN_ChangeSeason();

	return false;
}

// В новой игре проставляем текущий сезон на фоне, без эффектов и историй
void SZN_NewGameInit()
{
	SeasonSystem.current = SZN_SeasonForNow();
}


string SZN_GetCurrentSeasonName()
{
	if (!CheckAttributeHasValue(&SeasonSystem, "current")) return SZN_SeasonForNow();
	return SeasonSystem.current;
}

string SZN_SeasonForNow()
{
	return SZN_GetSeasonName(GetDataMonth());
}

string SZN_NextSeason()
{
	int month = GetDataMonth() + 3;
	if (month > 12)
		month -= 12;
	return SZN_GetSeasonName(month);
}

string SZN_GetSeasonName(int month)
{
	if (month <= 2)  return CROWN_SEASON;
	if (month <= 5)  return REED_SEASON;
	if (month <= 8)  return STORM_SEASON;
	if (month <= 11) return SHADOW_SEASON;
	return CROWN_SEASON;
}

bool SZN_ChangeSeason(string toSeason = "")
{
	if (toSeason == "") toSeason = SZN_SeasonForNow();

	object context;
	context.seasonId = toSeason;
	LaunchStoryFrame(&context, "Seasons\Next" + toSeason);
	return true;
}

/*
	Получить множитель модификатора сезона, то есть база 1.0 + float-значение модификатора
	*@param base базовый множитель, обычно единица, т. е. 100%
	*@param min минимальный множитель, для цен используем 0.01 (1%), чтобы не получалось бесплатно
	*@param max максимальный множитель, если нужен

	*@return ножитель вида n.n
*/
float SZN_GetModifierMtp(string modifierName, float base = 1.0, float min = 0.0, float max = 10.0)
{
	aref currentSeason = GetAref(&SeasonSystem, "current", true);
	return GetModifierMtp(&currentSeason, modifierName, base, min, max);
}

int SZN_GetModifierState(string modifierName, int defaultValue = 0)
{
	aref currentSeason = GetAref(&SeasonSystem, "current", true);
	return GetModifierState(&currentSeason, modifierName, defaultValue);
}

int SZN_IncreaseIntByModifier(int value, string modifierName)
{
	return makeint(makefloat(value) * SZN_GetModifierMtp(modifierName));
}

// цветовой конфиг тултипа для историй сезонов
object SZN_TooltipConfig()
{
	object res;
	res.theme = "dark";
	res.color1 = argb(255, 255, 255, 255); // белый
	res.color2 = argb(255, 255, 128, 128);
	res.color3 = ARGB_Color("peach");      // персиковый, для нейтральных модификаторов
	res.color4 = argb(255, 255, 255, 255); // белый
	return res;
}

// цветовой конфиг тултипа для сезонов в интерфейсах
object SZN_TooltipConfigWhite()
{
	object res;
	res.theme = "white";
	res.color1 = argb(255, 47, 39, 29); // тёмно-коричневый
	res.color2 = argb(255, 255, 128, 128);
	res.color3 = argb(255, 47, 39, 29); // под светлую тему
	res.color4 = argb(255, 47, 39, 29); // тёмно-коричневый
	return res;
}

// JOKERTODO правильное DLC
bool SZN_HasDLC()
{
	return GetDLCenabled(DLC_APPID_3);
}

// Заплатка для диалога с контрабандистом
bool SZN_CheckContrabandDialog(ref dialog, ref link)
{
	switch (SZN_GetModifierState(M_CONTRABAND_TRADE_STATUS))
	{
		case 0: return false; break;
		case 1:
			dialog.text = DLG_Convert("Smuggler_cant_trade", "Dialog.txt");
			link.l1 = DLG_Convert("Smuggler_cant_trade_reply", "Dialog.txt");;
			link.l1.go = "exit";
		break;
		case 2:
			dialog.text = DLG_Convert("Smuggler_can_trade", "Dialog.txt");
			link.l1 = DLG_Convert("Smuggler_can_trade_reply", "Dialog.txt");
			link.l1.go = "Meeting_3";
		break;
	}

	return true;
}

// Вывод модификаторов сезона, есть скрытые модификаторы и все модификаторы идут в goodText
void SZN_ShowModifiers(ref rObject, ref sHeader, ref text, ref badText, ref goodText, string modifiersTitle = "")
{
	aref modifiers;
	makearef(modifiers, rObject.modifiers);

	int modifiersQty = GetAttributesNum(modifiers);
	if (modifiersQty == 0) return;
	if (strlen(text) > 0) text += "\n\n";

	text += modifiersTitle;

	// скрытые модификаторы
	object filter;
	SetAttribute(&filter, M_WORLD_SHIPS_CREW_MTP, true);
	SetAttribute(&filter, M_WORLD_SHIPS_HULL_MTP, true);

	for (int i=0; i < modifiersQty; i++)
	{
		aref modifier = GetAttributeN(modifiers, i);
		string modifierId = GetAttributeName(modifier);
		if (CheckAttribute(&filter, modifierId)) continue;

		if (modifierId == "has")
		{
			SZN_ShowEnumModifiers(&modifier, text, badText, goodText);
			continue;
		}

		string modifierValue = GetAttributeValue(modifier);
		float value = stf(modifierValue);

		string humanModifier = "\n" + GetModifierName(modifierId) + ": " + ToHumanModifierPercent(value);
		goodText += humanModifier;
	}

	RemoveFirstNewline(&goodText);
}

// Вывод модификаторов состояний типа доступности крупных калибров
void SZN_ShowEnumModifiers(ref modifiers, ref text, ref badText, ref goodText)
{
	int modifiersNum = GetAttributesNum(modifiers);
	for (int i=0; i < modifiersNum; i++)
	{
		aref modifier = GetAttributeN(modifiers, i);
		string modifierId = GetAttributeName(modifier);
		string humanModifier = newStr() + GetModifierName(modifierId + "_" + sti(GetAttributeValue(modifier)));
		goodText += humanModifier;
	}
}
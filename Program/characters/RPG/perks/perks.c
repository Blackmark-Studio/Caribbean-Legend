#include "characters\RPG\perks\perks.h"
#include "characters\RPG\perks\self_effects.c"
#include "characters\RPG\perks\self_callbacks.c"
#include "characters\RPG\perks\ship_effects.c"
#include "characters\RPG\perks\trees.c"

#event_handler("evntChrPerkDelay","procChrPerkDelay");

object ChrPerksList;

extern void extrnInitPerks();

void InitPerks()
{
	if (LoadSegment("characters\RPG\perks\init.c") )
	{
		extrnInitPerks();
		UnloadSegment("characters\RPG\perks\init.c");
	}
}

bool CheckCharacterPerk(ref chref, ref perkEntity)
{
	switch (VarType(&perkEntity))
	{
		case "string": return HasPerk(chref, perkEntity); break;
		case "aref":   return CheckAttribute(chref, "perks.list."+GetAttributeName(perkEntity)); break;
	}
}

bool HasPerk(ref chr, string perkName)
{
	return CheckAttribute(chr, "perks.list."+ perkName);
}

// Естьи ли перк у персонажа без учёта перков от фантомных офицеров
bool HasPerkNatural(ref chr, string perkName)
{
	if (!HasPerk(chr, perkName)) return false;
	return !CheckAttribute(chr, "perks.list."+perkName + ".fromOfficer");
}

// Прокачать перк и все требуемые для него перки без обновления таблицы
bool SetCharacterPerkWithRequiredNoCash(ref chr, string perkName)
{
	bool refresh = false;
	aref chrPerks;
	makearef(chrPerks, chr.perks.list);
	int i = 0;
	while (i < 5)
	{
		string nextPerk = GetPerkOrRequired(chrPerks, perkName);
		if (SetCharacterPerkNoCash(chr, nextPerk, false)) refresh = true;
		if (nextPerk == perkName) break;
	}

	return refresh;
}

// Прокачать перк и все требуемые для него перки
bool SetCharacterPerkWithRequired(ref chr, string perkName)
{
	bool result = SetCharacterPerkWithRequiredNoCash(chr, perkName);
	CT_UpdateCashTables(chr);
	return result;
}

// Проверяем, надо ли взять другой перк, чтобы взять этот и возвращаем соответствующий
string GetPerkOrRequired(ref chrPerks, string perkName)
{
	if (!CheckAttribute(&ChrPerksList, "list." + perkName + ".condition")) return perkName;

	aref conditions;
	makearef(conditions, ChrPerksList.list.(perkName).condition);

	for(int i=0; i < GetAttributesNum(conditions); i++)
	{
		string tempPerkName = GetAttributeName(GetAttributeN(conditions, i));
		if (!CheckAttribute(chrPerks, tempPerkName)) return GetPerkOrRequired(chrPerks, tempPerkName);
	}

	return perkName;
}

// Применить эффекты от перка
bool ApplyPerkEffects(ref chr, string perkName, bool fromOfficer)
{
	bool refresh = false;
	aref perks;
	makearef(perks, chr.perks.list);

	perks.(perkName) = true;
	if (fromOfficer) perks.(perkName).fromOfficer = true;
	else DeleteAttribute(perks, perkName + ".fromOfficer");

	aref perk;
	makearef(perk, ChrPerksList.list.(perkName));

	switch (perkName)
	{
		case "Grus":
			refresh = true; // нужен рефрешь
		break;

		case "MarathonRunner": 
		{
			if (!IsMainCharacter(chr)) SetChrModifier(chr, M_ENERGY_MAX, PERK_VALUE3_MARATHON_RUNNER, "MarathonRunner");
		}
		break;

		case "KeenEye": 
		{
			if (IsMainCharacter(chr)) break;
			SetChrModifier(chr, M_CRIT_CHANCE, GUN_ITEM_TYPE    + "_" + PERK_VALUE2_KEEN_EYE, "KeenEye");
			SetChrModifier(chr, M_CRIT_CHANCE, MUSKET_ITEM_TYPE + "_" + PERK_VALUE2_KEEN_EYE, "KeenEye");
		}
		break;

		case "Investor": 
		{
			if (!IsMainCharacter(chr))
			{
				SetChrModifier(chr, SKILL_TYPE + SKILL_LEADERSHIP, PERK_VALUE2_INVESTOR, "Investor");
				SetChrModifier(chr, SKILL_TYPE + SKILL_COMMERCE, PERK_VALUE2_INVESTOR, "Investor");
				refresh = true;
			}
		}
		break;
		case "Captain": DeleteAttribute(chr, "CompanionDisable"); break; // есливыдали кэп-перк, значит может
	}

	aref modifiers;
	makearef(modifiers, perk.modifiers);
	aref table = CT_GetTable(chr, CT_STATIC);
	for (int i = 0; i < GetAttributesNum(modifiers); i++)
	{
		aref modifier = GetAttributeN(modifiers, i);
		string modifierName = GetAttributeName(modifier);
		if (modifierName == "callbacks") MergeCallbacks(&table, &modifier);
		else if (modifierName == "has") MergeFlags(&table, &modifier);
		else SetModifierFromSourceDirect(&table, GetAttributeName(modifier), stf(GetAttributeValue(modifier)), perkName);
	}

	return refresh;
}

// Выдача перка NPC от фантомного офицера, не буду совать тут проверку на главного героя и его офицеров
// т. к. применять к ним этот метод нигде не должно, а вызывать его будет много
void SetCharacterPerkFromOfficer(ref captain, string perkName, ref officer)
{
	if (HasPerkNatural(captain, perkName)) return;

	ApplyPerkEffects(captain, perkName, true);
}

// Выдача одиночного перка с применением модификаторов, но без обновления таблицы
// Полезно если выдаем много перков циклами и планируем обновить таблицы в конце
bool SetCharacterPerkNoCash(ref chr, string perkName, bool fromOfficer)
{
	bool refresh = ApplyPerkEffects(chr, perkName, fromOfficer);
	return refresh; // нужен рефрешь
}

// Выдача одиночного перка с применением модификаторов
bool SetCharacterPerk(ref chr, string perkName)
{
	bool refresh = SetCharacterPerkNoCash(chr, perkName, false);

	CT_UpdateCashTables(chr);
	return refresh; // нужен рефрешь
}

// Правильное удаление перка, со сносом модификаторов и коллбэков
void DelCharacterPerk(ref chr, string perkName)
{
	DelCharacterPerkNoCash(chr, perkName);
	CT_UpdateCashTables(chr);
}

// Правильное удаление перка, со сносом модификаторов и коллбэков, но без обновления таблиц
// Полезно если забираем много перков циклами и планируем обновить таблицы в конце
void DelCharacterPerkNoCash(ref chref, string perkName)
{
	DeleteAttribute(chref,"perks.list."+perkName);
	RemoveChrModifier(chref, perkName);
	RemoveChrModifier(chref, "perk_" + perkName);
	aref callbacks = GetPerkCallbacks(perkName);
	makearef(callbacks, ChrPerksList.list.(perkName).modifiers.callbacks);
	for (int i = 0; i < GetAttributesNum(callbacks); i++)
	{
		aref functionsList = GetAttributeN(callbacks, i);
		string listName = GetAttributeName(functionsList);
		for (int j = 0; j < GetAttributesNum(functionsList); j++)
		{
			aref function = GetAttributeN(functionsList, j);
			string funcName = GetAttributeName(function);
			RemoveChrCallback(chref, listName + "." + funcName);
		}
	}
}

aref GetPerkCallbacks(string perkName)
{
	aref callbacks;
	makearef(callbacks, ChrPerksList.list.(perkName).modifiers.callbacks);
	return callbacks;
}

void ActivateCharacterPerk(ref chref, string perkName)
{
	if( !CheckAttribute(&ChrPerksList,"list."+perkName) )
	{
		trace("Invalid perk name - " + perkName);
		return;
	}

	int timeDelay = 0;
	int timeDuration = 0;

	if( CheckAttribute(&ChrPerksList,"list."+perkName+".TimeDuration") )
	{	timeDelay = sti(ChrPerksList.list.(perkName).TimeDuration);
		timeDuration = timeDelay;
	}
	if( CheckAttribute(&ChrPerksList,"list."+perkName+".TimeDelay") )
	{	timeDelay = sti(ChrPerksList.list.(perkName).TimeDelay);
		if(timeDuration<=0)	{timeDuration=timeDelay;}
	}
    // boal fix
    // иначе после применения давался ГГ
	
    int cn;
    if (!CheckCharacterPerk(chref, perkName))
    {

        cn = GetOfficersPerkUsingIdx(chref, perkName);
        if (cn != -1)
        chref = GetCharacter(cn);
    }
    // <--
	chref.perks.list.(perkName).delay = timeDelay;
	chref.perks.list.(perkName).active = timeDuration;

	//if(sti(chref.index) == nMainCharacterIndex)
	if (sti(chref.index) == nMainCharacterIndex || isOfficerInShip(chref, false)) // наследие перка от офа boal 30.06.06
	{
		AddPerkToActiveList(perkName);
	}

	ApplyStatusEffect(chref, perkName);
	if(timeDelay>0) PostEvent("evntChrPerkDelay",1000,"sl",perkName,sti(chref.index));
	Event("eSwitchPerks","l",sti(chref.index));
	// fix boal всегда для ГГ
	Event("eSwitchPerks","l", GetMainCharacterIndex());
}

// evganat - на будущее
int GetCharacterPerkCurDuration(ref chref, string perkName)	// определяем прошедшее время с момента активации перка
{
	if(!CheckAttribute(&ChrPerksList, "list." + perkName + ".TimeDuration"))
		return -1;
	if(!CheckCharacterPerk(chref, perkName))
		return -1;
	if(!IsCharacterPerkOn(chref, perkName))
		return -1;
	int maxDuration = sti(ChrPerksList.list.(perkName).TimeDuration);
	int curActive = sti(chref.perks.list.(perkName).active);
	return maxDuration - curActive;
}

bool GetCharacterPerkUsing(ref chref, string perkName)
{   // можно ли пользовать умение (задержки нет)
	if( !CheckAttribute(chref,"perks.list."+perkName) ) return false;
	if( CheckAttribute(chref,"perks.list."+perkName+".delay") ) return false;
	return true;
}

bool GetOfficersPerkUsing(ref chref, string perkName)
{ // boal препишем внутрянку под новых офов, че в к3 не было? не ведаю.
	string  sOfficerType;	
	ref   offc;	   
	bool  ok = false; // boal fix 25.03.05 проверка на запрет
	bool  okDelay = true;
	int   cn;
	if (GetCharacterPerkUsing(chref, perkName)) {return true;} // босс отдельно
	/* if (GetCharacterEquipByGroup(pchar, HAT_ITEM_TYPE) == "hat5" && IsCompanion(chref) && chref.id != pchar.id)
	{
		if(CheckAttribute(&ChrPerksList, "list."+perkName+".BaseType") && ChrPerksList.list.(perkName).BaseType == "ship")
		{
			if(GetCharacterPerkUsing(pchar, perkName)) return true;
		}
	} */
	if (!CheckAttribute(chref,"perks.list."+perkName))  // у гг нет перка вообще, тогда смотрим офов, иначе выход
	{
		for(int i=1; i<=6; i++)
		{
			sOfficerType = GetOfficerTypeByNum(i);
			if (CheckAttribute(&ChrPerksList, "list." + perkName + ".OfficerType") && ChrPerksList.list.(perkName).OfficerType == sOfficerType)
			{
				cn = sti(chref.Fellows.Passengers.(sOfficerType));
				if(cn<0) {continue;}
				offc = &Characters[cn];
				if (CheckAttribute(offc, "perks.list."+perkName) )          ok = true;
				if (CheckAttribute(offc, "perks.list."+perkName+".delay") ) okDelay = false;
				//if (GetCharacterPerkUsing(chref, perkName) return true;
			}
		}
	}
	return (ok) && (okDelay);
}

// boal
int GetOfficersPerkUsingIdx(ref chref, string perkName)
{
	string  sOfficerType;
	int     cn;
	if (GetCharacterPerkUsing(chref, perkName)) {return sti(chref.index);} // босс отдельно
	for(int i=1; i<=6; i++)
	{
		sOfficerType = GetOfficerTypeByNum(i);
		if (CheckAttribute(&ChrPerksList, "list." + perkName + ".OfficerType") && ChrPerksList.list.(perkName).OfficerType == sOfficerType)
		{
			cn = sti(chref.Fellows.Passengers.(sOfficerType));
			if(cn<0) {continue;}
			if (GetCharacterPerkUsing(&Characters[cn], perkName) ) {return cn;}
		}
	}
	return -1;
}

bool IsCharacterPerkOn(ref chref, string perkName)
{
	aref arRoot, arBase;
	makearef(arRoot,chref.perks.list);
	if( !CheckAttribute(arRoot,perkName) ) return false;
	makearef(arBase,ChrPerksList.list.(perkName));
	if( CheckAttribute(arBase,"TimeDuration") || CheckAttribute(arBase,"TimeDelay") ) {
		return CheckAttribute(arRoot,perkName+".active");
	}
	return true;
}

void CharacterPerkOff(ref chref, string perkName)
{
	if (perkName == "Turn180")
	{
		chref.Tmp.SpeedRecall = 0; // чтоб маневр применить
	}
	DeleteAttribute(chref,"perks.list."+perkName+".active");
	Event("eSwitchPerks","l",sti(chref.index));	 
	// fix boal всегда для ГГ
	Event("eSwitchPerks","l", GetMainCharacterIndex());
	if (sti(chref.index) == nMainCharacterIndex || isOfficerInShip(chref, false)) // наследие перка от офа boal 30.06.06
	{
		DelPerkFromActiveList(perkName);
	}
}

bool CheckOfficersPerk(ref chref, string perkName)
{ // активность перка в данный момент, для временных - режим активности, а не задержки
	bool ret = CheckOfficersPerkWOSelf(chref, perkName);

	if (ret) return true;
	// самого НПС
	if(IsCharacterPerkOn(chref,perkName) == true)
	{
		return true;
	}
	return false;
}

bool CheckOfficersPerkWOSelf(ref chref, string perkName)
{
	int     iOfficer = -1;
	string  sOfficerType;
	if(chref.id == pchar.id)
	{
		if (CheckAttribute(&ChrPerksList, "list." + perkName))
		{
			// boal новая схема наследования. switch не наш метод
			if (CheckAttribute(&ChrPerksList, "list." + perkName + ".OfficerType"))
			{
				sOfficerType = ChrPerksList.list.(perkName).OfficerType;
				iOfficer = sti(pchar.Fellows.Passengers.(sOfficerType));
			}
		}	
	}

	if(iOfficer != -1)
	{
		if(IsCharacterPerkOn(GetCharacter(iOfficer), perkName) == true )
		{
			return true;
		}
	}
	return false;
}
// нигде не юзан
bool CheckCompanionsPerk(ref chref, string perkName)
{
	int i,cn;
	for(i=0; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(chref,i);
		if(cn>=0)
		{	if( IsCharacterPerkOn(GetCharacter(cn),perkName) )	{return true;}
		}
	}
	return false; // fix by boal
}

void procChrPerkDelay()
{
	string perkName = GetEventData();
	int chrIdx = GetEventData();

	aref arPerk;
	makearef(arPerk,Characters[chrIdx].perks.list.(perkName));
	if( !CheckAttribute(arPerk,"delay") ) return;
	int delay = sti(arPerk.delay);
 	// фикс в каюте, палубе, абордаже
 	bool ok;
 	ok = (!bAbordageStarted) && (!bSeaReloadStarted);
 	if (ok || perkName == "Rush")
 	{
		delay--;
	}

	if( CheckAttribute(arPerk,"active") )
	{
		int iActive = sti(arPerk.active)-1;
		if( iActive>0 )	
		{
			arPerk.active = iActive;
			if(!IsPerkIntoList(perkName))
			{
				AddPerkToActiveList(perkName);
			}
		}
		else
		{
			RemoveStatusEffect(&Characters[chrIdx], perkName);
			CharacterPerkOff(GetCharacter(chrIdx),perkName);
		}
	}

	if( delay<=0 )
	{	DeleteAttribute(&Characters[chrIdx],"perks.list."+perkName+".delay");
		DeleteAttribute(&Characters[chrIdx],"perks.list."+perkName+".active");
		PostEvent("evntPerkAgainUsable",1);
		ControlsDesc();
	}
	else
	{
		ControlsDesc();
		Characters[chrIdx].perks.list.(perkName).delay = delay;
		PostEvent("evntChrPerkDelay",1000,"sl",perkName,chrIdx);
	}
}

void EnableUsingAbility(ref chref,string perkName)
{
    // boal fix
    // иначе после применения давался ГГ
	int cn;
    if (!CheckCharacterPerk(chref, perkName))
    {

        cn = GetOfficersPerkUsingIdx(chref, perkName);
        if (cn != -1)
        chref = GetCharacter(cn);
    }
    // <--
    
	Event("evntChrPerkDelay","sl",perkName, sti(chref.index));
}

void PerkLoad()
{
//	int iRDTSC = RDTSC_B();
	string locName = pchar.location;
	aref arPerksRoot,arPerk;
	int i,j,n,tmpi;

	for(i=0; i<MAX_CHARACTERS; i++)
	{
		if(Characters[i].location == locName || isOfficerInShip(&Characters[i], false))
		{
			makearef(arPerksRoot,Characters[i].perks.list);
			n = GetAttributesNum(arPerksRoot);
			for(j=0; j<n; j++)
			{
				arPerk = GetAttributeN(arPerksRoot,j);
				if( CheckAttribute(arPerk,"delay") )
				{
					tmpi = sti(arPerk.delay);
					if( tmpi>0 )
					{
						PostEvent("evntChrPerkDelay",1000,"sl",GetAttributeName(arPerk),i);
					}
				}
			}
		}
	}
	// belamour legendary edition при с/л таймер запускаем заново -->
	if(IsCharacterPerkOn(pchar, "IronWill")) 
	{
		ActivateCharacterPerk(pchar,"IronWill");
	}
	for(i=0; i<4; i++)
	{
		n = GetOfficersIndex(pchar,i);
		if(n == -1) continue;
		ref chr = GetCharacter(n);
		if(IsCharacterPerkOn(chr, "IronWill"))
		{
			ActivateCharacterPerk(chr,"IronWill");
		}
	}
	//<--
//	trace("TIME!!! PerkLoad() = " + RDTSC_E(iRDTSC));
}
// boal под новые слоты -->
void ClearActiveChrPerks(ref chref)
{
	int i,cn;
    ref offc; // boal
    string  sOfficerType;	
    
    if (bAbordageStarted || bSeaReloadStarted) return; 
	
	ClearActive(chref); // босс отдельно
	if (CheckAttribute(chref, "Fellows.Passengers")) // не у всех есть
	{
		for (i=1; i<=6; i++)
		{
			sOfficerType = GetOfficerTypeByNum(i);
			cn = sti(chref.Fellows.Passengers.(sOfficerType));
			if(cn<0) {continue;}
			offc = &Characters[cn];
			ClearActive(offc);
		}
	}
}

void ClearActive(ref offic)
{
	aref arPerksRoot, arPerk;
	int i,n;
	
	makearef(arPerksRoot, offic.perks.list);
		
	n = GetAttributesNum(arPerksRoot);
	for (i=0; i<n; i++)
	{
		arPerk = GetAttributeN(arPerksRoot,i);

		if (CheckAttribute(arPerk, "delay"))
        {
			DeleteAttribute(arPerk,"delay");
		}
		if (CheckAttribute(arPerk,"active"))
        {
			DeleteAttribute(arPerk,"active");
		}
	}
}
// был баг К3, этот перк не работал вовсе
void AcceptWindCatcherPerk(ref refCharacter)
{
    int  nShipType;
    ref  refBaseShip, refRealShip;

	nShipType = GetCharacterShipType(refCharacter);
	if (nShipType==SHIP_NOTUSED) return;

	refRealShip = GetRealShip(nShipType);
	refBaseShip = GetShipByType(sti(refRealShip.BaseType));
		
	if (CheckOfficersPerk(refCharacter, "WindCatcher"))
	{
		refRealShip.InertiaAccelerationX	= stf(refBaseShip.InertiaAccelerationX) + stf(refBaseShip.InertiaAccelerationX) * PERK_VALUE_WIND_CATCHER;
		refRealShip.InertiaAccelerationY	= stf(refBaseShip.InertiaAccelerationY) + stf(refBaseShip.InertiaAccelerationY) * PERK_VALUE_WIND_CATCHER;
		refRealShip.InertiaAccelerationZ	= stf(refBaseShip.InertiaAccelerationZ) + stf(refBaseShip.InertiaAccelerationZ) * PERK_VALUE_WIND_CATCHER;
		// потмоу что перк помогает только быстрее набирать скорость, нет торможения
	}
	else
	{   // вернём, если перк снят
	    refRealShip.InertiaAccelerationX	= stf(refBaseShip.InertiaAccelerationX);
		refRealShip.InertiaAccelerationY	= stf(refBaseShip.InertiaAccelerationY);
		refRealShip.InertiaAccelerationZ	= stf(refBaseShip.InertiaAccelerationZ);
	}
	if (iArcadeSails == 0) // момент инерции ниже для тактики
	{
	    refRealShip.InertiaAccelerationY = stf(refRealShip.InertiaAccelerationY) / 2.0;
	}
}

// Jason: зелье берсеркера
void PerkBerserkerReaction()
{
	RemoveItems(pchar, "berserker_potion", 1);
	AddCharacterHealth(pchar, -2);
	if(!ShowCharString()) Log_info(XI_ConvertString("TinctureUsed"));
	PlaySound("Ambient\Tavern\glotok_001.wav");
	PlaySound("Types\" + LanguageGetLanguage() + "\warrior03.wav");
}

// belamour legendary edition количество открытых перков у персонажа
int СharacterPerksEnb(ref chr, string perkType)
{
	int total = 0; 
	int perksQ, i;
	string perkName;
	aref arPerksRoot;
	
	makearef(arPerksRoot,ChrPerksList.list);
	perksQ = GetAttributesNum(arPerksRoot);
	for(i=0; i<perksQ; i++)
	{
        perkName = GetAttributeName(GetAttributeN(arPerksRoot,i));
        if(CheckAttribute(arPerksRoot, perkName + ".Hidden")) continue;
		if(!CheckAttribute(chr, "perks.list."+perkName)) continue;
        if(!CheckAttribute(arPerksRoot, perkName + ".BaseType")) arPerksRoot.(perkName).BaseType = "self";
		if(CheckAttributeEqualTo(arPerksRoot, perkName + ".BaseType", perkType)) total++;
	} 
	return total;
}

// belamour legendary edition наличие перка у ГГ с учётом офицеров
bool CheckOfficersPerkEnable(string perkName)
{
	string  sOfficerType;	   
	int   cn;
	
	if( CheckAttribute(pchar,"perks.list."+perkName) ) return true;
	for(int i=1; i<=6; i++)
	{
		sOfficerType = GetOfficerTypeByNum(i);
		if (CheckAttribute(&ChrPerksList, "list." + perkName + ".OfficerType") && ChrPerksList.list.(perkName).OfficerType == sOfficerType)
		{
			cn = sti(pchar.Fellows.Passengers.(sOfficerType));
			if(cn<0) continue;
			if (CheckAttribute(&Characters[cn], "perks.list."+perkName)) return true;
		}
	}
	return false;
}

// belamour legendary edition время действия спосбности плюс кулдаун 
int AbilityTimeDuration(string stage, string perkName)
{
	if(CheckAttribute(pchar,"perks.list."+perkName+"."+stage)) return sti(pchar.perks.list.(perkName).(stage));
	for(int i=1; i<=6; i++)
	{
		string sOfficerType = GetOfficerTypeByNum(i);
		if (CheckAttribute(&ChrPerksList, "list."+perkName+".OfficerType") && ChrPerksList.list.(perkName).OfficerType == sOfficerType)
		{
			int cn = sti(pchar.Fellows.Passengers.(sOfficerType));
			if(cn<0) continue;
			if(CheckAttribute(&Characters[cn],"perks.list."+perkName+"."+stage)) return sti(Characters[cn].perks.list.(perkName).(stage));
		}
	}
	return -1;
}

// подсчёт перков для интерфейса belamour cle -->
int GetMaxPerks(ref chr, string perkType)
{
	int maximum = 0;
	
	int perksQ, i;
	string perkName;
	aref arPerksRoot;
	
	makearef(arPerksRoot,ChrPerksList.list);
	perksQ = GetAttributesNum(arPerksRoot);
	
	if(sti(chr.index) == GetMainCharacterIndex())
	{
		string HT;
		if(IsCharacterPerkOn(chr, "HT1")) HT = "HT1";
		if(IsCharacterPerkOn(chr, "HT2")) HT = "HT2";
		if(IsCharacterPerkOn(chr, "HT3")) HT = "HT3";
		if(IsCharacterPerkOn(chr, "HT4")) HT = "HT4";
		for(i=0; i<perksQ; i++)
		{
			perkName = GetAttributeName(GetAttributeN(arPerksRoot,i));
			if(CheckAttribute(arPerksRoot, perkName + ".Hidden")) continue;
			if(CheckAttribute(arPerksRoot, perkName + ".NPCOnly")) continue;
			if(CheckAttribute(arPerksRoot, perkName + ".HeroType") && arPerksRoot.(perkName).HeroType != HT) continue;
			if(!CheckAttribute(arPerksRoot, perkName + ".BaseType")) continue;
			if(arPerksRoot.(perkName).BaseType != perkType) continue;
			maximum++;
		}
		return maximum;
	}
	for(i=0; i<perksQ; i++)
	{
		perkName = GetAttributeName(GetAttributeN(arPerksRoot,i));
		if(CheckAttribute(arPerksRoot, perkName + ".Hidden")) continue;
		if(CheckAttribute(arPerksRoot, perkName + ".PlayerOnly")) continue;
		if(!CheckAttribute(arPerksRoot, perkName + ".BaseType")) continue;
		if(arPerksRoot.(perkName).BaseType != perkType) continue;
		maximum++;
	}
	return maximum;
}

bool bPerksMaxSelf(ref chr)
{
	if(СharacterPerksEnb(chr, "self") >= GetMaxPerks(chr, "self")) return true;
	
	return false;
}

bool bPerksMaxShip(ref chr)
{
	if(СharacterPerksEnb(chr, "ship") >= GetMaxPerks(chr, "ship")) return true;
	
	return false;
}

bool HaveAllPerks(ref chr, string type) // any, self, ship
{
    bool bFreeSelf, bFreeShip;
    bool bAny  = (type == "any");
    if (bAny)
    {
        bFreeSelf = GetAttributeInt(chr, "perks.FreePoints_self") > 0;
        bFreeShip = GetAttributeInt(chr, "perks.FreePoints_ship") > 0;
        if(!bFreeSelf && !bFreeShip) return true; // Нечего прокачивать
    }

	string perkName, perkType;
	aref arPerksRoot;
	makearef(arPerksRoot, ChrPerksList.list);
	int perksQ = GetAttributesNum(arPerksRoot);
    bool bHero = (sti(chr.index) == GetMainCharacterIndex());

	for(int i = 0; i < perksQ; i++)
	{
		perkName = GetAttributeName(GetAttributeN(arPerksRoot,i));
        if(!CheckAttribute(arPerksRoot, perkName + ".BaseType")) continue;   // Предыстории
        perkType = ChrPerksList.list.(perkName).BaseType;
		if(!bAny && perkType != type) continue; // Не тот тип
        if(bAny)
        {
            if(!bFreeSelf && perkType == "self") continue;
            if(!bFreeShip && perkType == "ship") continue;
        }
        if(CheckAttribute(arPerksRoot, perkName + ".HeroType")) continue;    // Личные спецперки
        if(!bHero && CheckAttribute(arPerksRoot, perkName + ".PlayerOnly")) continue; // Не ГГ
        if(bHero && CheckAttribute(arPerksRoot, perkName + ".NPCOnly")) continue;     // Не НПЦ
        if(CheckAttribute(arPerksRoot, perkName + ".Hidden")) continue;       // Скрытые

		if(!CheckCharacterPerk(chr, perkName)) return false; // Перк доступен, но не прокачан
	}
    return true;
}
// <-- подсчёт перков для интерфейса

ref PerkFromID(string perkName)
{
	aref res;
	makearef(res, ChrPerksList.list.(perkName));
	return &res;
}

ref FindPerk_VT(ref entity)
{
	return FindObject_VT(&entity, "PerkFromID", "");
}

int GetPerkPrice(ref entity)
{
	aref perk = FindPerk_VT(&entity);
	return GetAttributeInt(perk, "cost");
}

string GetPerkJob(ref entity)
{
	aref perk = FindPerk_VT(&entity);
	return GetAttributeOrDefault(perk, "officerType", "None");
}

int GetFreePerkPoints(ref chr, string type)
{
	return GetAttributeInt(chr, "perks.FreePoints_" + type);
}

void SetFreePerkPoints(ref chr, int value, string type)
{
	SetAttribute(chr, "perks.FreePoints_" + type, value);
}

void RemoveAllPerksNoCash(ref chr)
{
	aref perks, perk;
	makearef(perks, chr.perks.list);

	for (int i=GetAttributesNum(perks)-1; i > -1; i--)
	{
		string perkName = GetAttributeName(GetAttributeN(perks, i));
		perk = FindPerk_VT(perkName);
		if (CheckAttribute(perk, "HeroType")) continue;
		if (CheckAttribute(perk, "Hidden")) continue;
		
		DelCharacterPerkNoCash(chr, perkName);
	}
}

void ReapplyAllPerks(ref chr)
{
	aref perks, perk;
	makearef(perks, chr.perks.list);

	for (int i=GetAttributesNum(perks)-1; i > -1; i--)
	{
		aref charPerk = GetAttributeN(perks, i);
		string perkName = GetAttributeName(charPerk);
		SetCharacterPerkNoCash(chr, perkName, false);
	}

	CT_UpdateCashTables(chr);
}

string GetPerkDescribe(ref ref_Id_Idx, ref chr)
{
	aref perk = FindPerk_VT(&ref_Id_Idx);
	string perkName = GetAttributeName(perk);
	string descrKey = "perk" + perkName;
	if (!IsMainCharacter(chr) && HasDescriptor(perk, "Alternate")) descrKey += "_alternate";
	if (perkName == "master") return PerkMasterDescription(chr);
	return DLG_Convert(descrKey, "AbilityDescribe.txt", &perk);
}

string GetPerkName(ref ref_Id_Idx)
{
	aref perk = FindPerk_VT(&ref_Id_Idx);
	string perkName = GetAttributeName(perk);
	return DLG_Convert(perkName, "AbilityDescribe.txt", &perk);
}
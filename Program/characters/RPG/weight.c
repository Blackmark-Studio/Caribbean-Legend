#define OVERLOAD_NONE  0 // не перегружен, в норме
#define OVERLOAD_LIGHT 1 // перегружен, медленно ходит, фаст-тревел не пашет
#define OVERLOAD_HARD  2 // ходить нельзя вообще
#define MIN_ACTION_SPEED 0.40 // ниже этого значения скорость движений не может упасть
#define OVERLOAD_MIN_IMPACT_ACTION_SPEED 0.85 // даже при минимальной перегрузке будет снижение скорости до такого
#define OVERLOAD_MAX_SKILL_IMPACT 50.0 // сколько умения максимум отбирает перегрузка

// Получить вес предметов с оптимизацией
float GetItemsWeight(ref _chref)
{
	if (bCabinStarted || bAbordageStarted || !bSeaActive || !CheckAttribute(&_chref, "ItemsWeight"))
	{
		return GetItemsWeightEx(&_chref);
	}
	return stf(_chref.ItemsWeight);
}

 // Штраф перевеса, от -1 до -n при 200% перегрузе
int GetWeightSkillImpact(ref chr)
{
	float fOverload = GetAttributeFloat(chr, "WeightLoadLevel");
	if (fOverload <= 1) return 0;

	fOverload = fClamp(1, 2, fOverload);
	int result = makeint((-OVERLOAD_MAX_SKILL_IMPACT * (fOverload-1)) - 0.5);
	return func_min(-1, result);
}

// Получить точный вес предметов
float GetItemsWeightEx(ref chr)
{
	float   Amount = 0;
	string  itemID;
	ref     itm;

	for (int j=0; j < TOTAL_ITEMS; j++)
	{
		makeref(itm,Items[j]);
		if(!CheckAttribute(itm, "ID")) continue;
		itemID = itm.id;
		if (CheckAttribute(chr, "items."+itemID)) Amount += sti(chr.items.(itemID))*stf(itm.Weight);
	}
	chr.ItemsWeight = Amount; // оптимицация тормозов в бою на море
	return Amount;
}

// Сколько можно засунуть в персонажа предметов с перегрузом
int GetMaxItemsWeightWithOverload(ref chr)
{
	return GetMaxItemsWeight(chr) * 2;
}

// Сколько можно засунуть в персонажа без перегруза
int GetMaxItemsWeight(ref chr)
{
	if (!CheckAttribute(chr, "Skill.FencingS")) return 999999; // сундук или труп не имееют скила и ограничения
	if (!CheckAttribute(chr, "ct.land.MaxWeight"))
	{
		aref landTable = CT_GetTable(chr, CT_LAND);
		aref equipTable = CT_GetTable(chr, CT_EQUIP);
		return CT_SetMaxWeight(&landTable, &equipTable, chr);
	}
	return GetAttributeInt(chr, "ct.land.MaxWeight");
}

// Общая проверка перегрузки персонажа предметами
void CheckAndSetOverloadMode(ref chr)
{
	if (!CheckAttribute(chr, "actions")) return;     // сундуки не трогаем
	if (!CheckAttribute(chr, "equip.blade")) return; // невооруженные пофигу

	float fOverload;
	int overloadMode = OVERLOAD_NONE; // это управляет доступными режимами перемещения
	float fActionsSpeed = 1.0;        // это управляет cкоростью движений персонажа

	if (IsEquipCharacterByArtefact(chr, "totem_06")) fOverload = 0;
	else fOverload = GetItemsWeight(chr) / GetMaxItemsWeight(chr);

	//if (fOverload >= 2.0) overloadMode      = OVERLOAD_HARD;  // двигаться вообще нельзя при 200%
	if (fOverload >= 1.5) overloadMode = OVERLOAD_LIGHT; // нельзя спринтовать
	else overloadMode                  = OVERLOAD_NONE;  // всё можно до 150%

	// начиная с 100% загрузки весом начинаем снижать скорость движений
	if (fOverload > 1) fActionsSpeed = 1 - Bring2Range(0.0, MIN_ACTION_SPEED, 1.0, 2.0, fOverload);

	// Особые ситуации с замедлением имитацией перегруза
	if (IsMainCharacter(chr))
	{
		if (chr.model == "protocusto" || CheckAttribute(chr, "GenQuest.CantRun"))
		{
			overloadMode = func_max(OVERLOAD_LIGHT, overloadMode);
			fActionsSpeed = func_fmin(OVERLOAD_MIN_IMPACT_ACTION_SPEED, fActionsSpeed);
		}
	}

	if (fActionsSpeed < 1) fActionsSpeed = func_fmin(OVERLOAD_MIN_IMPACT_ACTION_SPEED, fActionsSpeed);

	chr.WeightLoadLevel = fOverload; // это управляет штрафом к скиллам и возможностью быстрого перехода
	SetCharacterActionsSpeed(chr, fActionsSpeed);
	SendMessage(chr, "lsl", MSG_CHARACTER_EX_MSG, "SetOverload", overloadMode);
}

void SetCharacterActionsSpeed(ref chr, float fSpeed)
{
	chr.baseAttackSpeed = fSpeed;
	chr.baseMoveSpeed = fSpeed;
}
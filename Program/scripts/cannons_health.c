// Система здоровья пушек
#include "scripts/cannons_health.h"

// Получить среднее состояние пушек борта в объект
// `bortName` = R/L/B/F
int CAN_SetBortInfo(ref result, ref cannons, string bortName)
{
	float totalDamage = 0;
	aref bort = cannons.borts.("cannon"+bortName).damages$aref;
	int cannonsQty = 0;

	for (string cannonName, aref _a: &bort)
	{
		float damage = bort.(cannonName);
		if (damage >= 1.0) continue;
		cannonsQty++;
		totalDamage += damage;
	}

	totalDamage = func_fmax(0.0, totalDamage);

	int mainType = cannons.Type$int(CANNON_TYPE_NONECANNON);
	result.(bortName).goodCannons = cannonsQty;
	result.(bortName).cannonsIdx = cannons.("cannon" + bortName).Type$int(mainType);
	result.(bortName).cannonsQty = cannonsQty;
	result.(bortName).goodIdx = GetCannonGoodsIdxByType(int(result.(bortName).cannonsIdx));

	if (cannonsQty == 0) SetAttribute(result, bortName + ".averageHealth", 0.0);
	else SetAttribute(result, bortName + ".averageHealth", 1.0 - totalDamage / cannonsQty);
	return cannonsQty;
}

// Собрать всю инфу о состоянии пушек по бортам
object CAN_GetFullInfo(ref chr, string bortName = "all")
{
	object result;
	aref cannons = GetAref(chr, "ship.cannons");
	int cannonsQty = 0;

	if (bortName != "all")
	{
		CAN_SetBortInfo(&result, &cannons, bortName);
		return result;
	}

	cannonsQty += CAN_SetBortInfo(&result, &cannons, "R");
	cannonsQty += CAN_SetBortInfo(&result, &cannons, "L");
	cannonsQty += CAN_SetBortInfo(&result, &cannons, "B");
	cannonsQty += CAN_SetBortInfo(&result, &cannons, "F");
	result.cannonsQty = cannonsQty;
	return result;
}

// Добавить общий износ орудиям калибра N в трюме персонажа
aref CAN_AddDamageInStock(ref chr, ref good, float addDamage = 0.0, string mode = "Ship")
{
	string stockAttribute = mode == "Ship" ? "Ship.Cargo.Goods." : "Storage.Goods.";

	aref shipGood = GetAref(chr, stockAttribute + good.name, true);
	float currentDamage = GetAttributeFloat(&shipGood, "totalDamage");
	shipGood.totalDamage = fts(func_fmax(0.0, currentDamage+addDamage), 2);
	shipGood.cannonsQty = mode == "Ship" ? GetAttributeValue(shipGood) : shipGood.quantity;
	return shipGood;
}

// Пересчитать общие повреждения орудий калибра N в трюме персонажа на текущее количество орудий
void CAN_UpdateDamageInStock(ref chr, ref good)
{
	if (!CheckAttribute(good, "CannonIdx")) return;

	aref shipGood = GetAref(chr, "Ship.Cargo.Goods." + good.name, true);
	float currentDamage = GetAttributeFloat(&shipGood, "totalDamage");
	int cashedQty = GetAttributeInt(&shipGood, "cannonsQty");
	int realQty = int(GetAttributeValue(shipGood));
	if (realQty == 0) shipGood.totalDamage = 0.0; // нет орудий, нет урона
	else if (realQty < cashedQty)
	{
		float health = 1.0 - currentDamage / cashedQty;
		shipGood.totalDamage = func_fmax(0.0, currentDamage + (realQty-cashedQty) * (1.0-health));
	}
	// Если орудий стало больше, то дамаг добавляем отдельно через `CAN_AddDamageInStock`, либо это целые орудия

	shipGood.cannonsQty = realQty;
}

// Получить состояние орудий калибра N в трюме персонажа
float CAN_GetCannonsStockHealth(ref chr, string goodName, string mode = "Ship")
{
	string stockAttribute = mode == "Ship" ? "Ship.Cargo.Goods." : "Storage.Goods.";
	aref shipGood = GetAref(chr, stockAttribute + goodName);
	if (shipGood == nullptr) return 0.0;

	float cannonsQty = mode == "Ship" ? float(GetAttributeValue(shipGood)) : shipGood.quantity;
	if (cannonsQty == 0.0) return 0.0;

	return 1.0 - GetAttributeFloat(&shipGood, "totalDamage") / cannonsQty;
}

// Получить состояние орудий калибра N в трюме персонажа как nn%
string GetHumanCannonsHealthInStock(ref chr, ref good)
{
	if (!CheckAttribute(good, "CannonIdx")) return "";
	return ToHumanPercent(int(CAN_GetCannonsStockHealth(chr, good.name) * 100));
}

// Передаем урон орудиям между кораблями или на склад
void CAN_TransferCannons(ref rFrom, ref rTo, ref good, int qty, string mode = "Ship")
{
	if (!CheckAttribute(good, "CannonIdx")) return;

	float damage;
	switch (mode)
	{
		case "Ship":
			damage = 1.0-CAN_GetCannonsStockHealth(rFrom, good.name, "Ship");
			CAN_AddDamageInStock(rTo, good, qty * damage);
			CAN_AddDamageInStock(rFrom, good, -qty * damage);
		break;
		case "toStorage":
			damage = 1.0-CAN_GetCannonsStockHealth(rFrom, good.name, "Ship");
			CAN_AddDamageInStock(rTo, good, qty * damage, "storage");
			CAN_AddDamageInStock(rFrom, good, -qty * damage);
		break;
		case "fromStorage":
			damage = 1.0-CAN_GetCannonsStockHealth(rFrom, good.name, "Storage");
			CAN_AddDamageInStock(rTo, good, qty * damage);
			CAN_AddDamageInStock(rFrom, good, -qty * damage, "storage");
		break;
	}
}

// Починить все орудия на бортах и в трюме
void CAN_RepairAllCannons(ref chr)
{
	int allGoodsQty = GetArraySize(&Goods);
	for (int i = 0; i < allGoodsQty; i++)
	{
		ref good = &Goods[i];
		if (!CheckAttribute(good, "CannonIdx")) continue;
		int qty = GetCargoGoods(chr, i);
		if (qty <= 0) continue;

		DeleteAttribute(chr, "Ship.Cargo.Goods." + good.name + ".totalDamage");
		DeleteAttribute(chr, "Ship.Cargo.Goods." + good.name + ".cannonsqty");
	}

	SetShipCannonsDamagesNull(chr, false);
}

// Получить цену на ремонт N орудий с учётом их состояния
int GetCannonsRepairCost(ref chr, ref storeNPC, int goodIdx, int qty, float health)
{
	int price = GetStoreGoodsPrice(storeNPC, goodIdx, PRICE_TYPE_BUY, pchar, qty); // цена покупки орудий игроком в качестве базы
	price -= GetStoreGoodsPrice(storeNPC, goodIdx, PRICE_TYPE_SELL, pchar, qty);   // вычитаем цену продажи
	price = int(GetFloatModifiedByDifficulty(float(price), 0.2, 1.0));             // модифицируем от сложности
	return int(float(price) * (1.0-health));                                       // делаем скидку от состояния орудий
}


// Получить цену починки всех пушек на корабле и в трюме
int GetAllCannonsRepairCost(ref chr, ref storeNPC)
{
	object cannonsInfo = CAN_GetFullInfo(chr);
	int summ = 0;
	// добавляем цену за ремонт установленных орудий
	string borts[4] = {"l", "r", "f", "b"};
	for (int index, ref bortName: borts)
	{
		int cannonsQty = int(cannonsInfo.(bortName).goodcannons);
		int cannonGoodsIdx =  int(cannonsInfo.(bortName).goodidx);
		float averageHealth = float(cannonsInfo.(bortName).averagehealth);
		summ += GetCannonsRepairCost(chr, storeNPC, cannonGoodsIdx, cannonsQty, averageHealth);
	 }

	// добавляем цену за ремонт всех орудий в трюме
	for (int i, ref good: &Goods)
	{
		if (!CheckAttribute(good, "CannonIdx")) continue;
		int qty = GetCargoGoods(chr, i);
		if (qty <= 0) continue;

		float totalDamage = GetAttributeFloat(chr, "Ship.Cargo.Goods." + good.name + ".totalDamage");
		float health = totalDamage == 0.0 ? 1.0 : 1.0 - (totalDamage / qty);

		summ += GetCannonsRepairCost(chr, storeNPC, i, qty, health);
	}
	
	return summ;
}

// Зависимость урона снаряда от состояния борта
float CAN_GetDamageMtpForHealth(float health, float bonus)
{
	if (health > CAN_BUFF_LEVEL) return Bring2Range(0.0, CAN_BUFF_DAMAGE_MTP + bonus, CAN_BUFF_LEVEL, 1.0, health);
	if (health < CAN_DEBUFF_LEVEL) return Bring2Range(CAN_DEBUFF_DAMAGE_MTP, 0.0, 0.0, CAN_DEBUFF_LEVEL, health);
	return 0.0
}

// Зависимость перезарядки от состояния борта
float CAN_GetReloadMtpForHealth(float health, float bonus)
{
	if (health > CAN_BUFF_LEVEL) return Bring2Range(0.0, CAN_BUFF_RELOAD_MTP + bonus, CAN_BUFF_LEVEL, 1.0, health);
	if (health < CAN_DEBUFF_LEVEL) return Bring2Range(CAN_DEBUFF_RELOAD_MTP, 0.0, 0.0, CAN_DEBUFF_LEVEL, health);
	return 0.0
}

// Обновляем данные о здоровье орудий, записываем в кэш
void CAN_CashCannonsHealth(ref chr, bool forceUpdate = false)
{
	if (CheckAttribute(chr, "fort")) return;

	aref cash = CAN_GetHealthCash(chr.id);
	if (!forceUpdate && TMSTM_Timestamp(0) < cash.updateAt$int(0)) return;

	object cannonsInfo = CAN_GetFullInfo(chr);
	float bonus = CheckOfficersPerk(chr, "Bombardier") ? PERK_VALUE_BOMBARDIER : 0.0;
	cash.talisman = IsCharacterEquippedArtefact(chr, "talisman3");
	if (bool(cash.talisman)) bonus += 0.10;
	cash.cannonsSkillMtp = 1-(0.3*pow(GetSkillAfterPenalty(chr, SKILL_CANNONS)*0.01, 0.7));

	float health = float(cannonsInfo.R.averageHealth);
	cash.cannonR.level = int(cannonsInfo.R.goodcannons) > 0 ? CAN_HumanCannonsHealthLevel(health) : CAN_HEALTH_LEVEL_NORMAL;
	cash.cannonR.damageMtp = CAN_GetDamageMtpForHealth(health, bonus);
	cash.cannonR.reloadMtp = CAN_GetReloadMtpForHealth(health, bonus);

	health = float(cannonsInfo.L.averageHealth);
	cash.cannonL.level = int(cannonsInfo.L.goodcannons) > 0 ? CAN_HumanCannonsHealthLevel(health) : CAN_HEALTH_LEVEL_NORMAL;
	cash.cannonL.damageMtp = CAN_GetDamageMtpForHealth(health, bonus);
	cash.cannonL.reloadMtp = CAN_GetReloadMtpForHealth(health, bonus);

	health = float(cannonsInfo.B.averageHealth);
	cash.cannonB.damageMtp = CAN_GetDamageMtpForHealth(health, bonus);
	cash.cannonB.reloadMtp = CAN_GetReloadMtpForHealth(health, bonus);

	health = float(cannonsInfo.F.averageHealth);
	cash.cannonF.damageMtp = CAN_GetDamageMtpForHealth(health, bonus);
	cash.cannonF.reloadMtp = CAN_GetReloadMtpForHealth(health, bonus);

	cash.updateAt = TMSTM_Timestamp(CAN_UPDATE_COOLDOWN);
}

// Кэш по орудиям для персонажа
aref CAN_GetHealthCash(string chrId)
{
	return touchattr(TEV.localMapCash.cannonsHealth.(chrId));
}

// Применяем состояние орудий к урону
float CAN_GetHealthDamageMtp(ref chr, string bortName)
{
	aref cash = CAN_GetHealthCash(chr.id);
	return cash.(bortName).damageMtp$float(0.0);
}

// Применяем состояние орудий к перезарядке
float CAN_GetHealthReloadMtp(ref chr, string bortName)
{
	aref cash = CAN_GetHealthCash(chr.id);
	return cash.(bortName).reloadMtp$float(0.0);
}

// Получить здоровье наименее целого борта, учитываем только боковые
float CAN_GetMostDamagedBortHealth(ref chr)
{
	object result;
	aref cannons = GetAref(chr, "ship.cannons");
	int cannonsQty = 0;

	CAN_SetBortInfo(&result, &cannons, "R");
	CAN_SetBortInfo(&result, &cannons, "L");
	if (int(result.r.goodCannons) + int(result.l.goodCannons) < 1) return 1.0;

	float health = result.r.averagehealth;
	if (float(result.l.averagehealth) < health) health = result.l.averagehealth;
	return health;
}

int CAN_HumanCannonsHealthLevel(float health)
{
	int level = CAN_HEALTH_LEVEL_NORMAL;
	if (health < CAN_DEBUFF_LEVEL) level = CAN_HEALTH_LEVEL_BROKEN;
	if (health > CAN_BUFF_LEVEL) level = CAN_HEALTH_LEVEL_FRESH;
	return level;
}

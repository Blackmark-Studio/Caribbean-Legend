#include "Loc_ai\fightparams\melee.c"
#include "Loc_ai\fightparams\range.c"
#include "Loc_ai\fightparams\exp.c"
#include "Loc_ai\fightparams\utility.c"
#include "Loc_ai\fightparams\fightparams.h"

// Является ли удар/выстрел критическим
bool LAi_IsHitCritical(ref attacker, ref table, string weaponType, string strikeType)
{
	float critChance = GetCritChance(table, weaponType);                 // получили крит-шанс персонажа для оружия
	Perk_Reaper(attacker, strikeType, &critChance);
	int strikeConter = GetAttributeInt(attacker, "chr_ai.crit_counter"); // получили количество промахов
	critChance += CRIT_PSEUDO_RANDOM_VALUE * strikeConter;               // +- за каждый промах

	if (critChance > frand(0.99))
	{
		SetAttribute(attacker, "chr_ai.crit_counter", func_min(0, -strikeConter)); // обнуляем или бахаем штраф, если каунтер был положительный
		return true; // кританули
	}

	AddToAttributeInt(attacker, "chr_ai.crit_counter", 1); // не кританули, записываем +1
	return false;
}

void ModifyDamageMtpByCrit(ref attacker, ref attackerLandTable, ref enemyLandTable, string weaponType, string strikeType, float damageMtp)
{
	if (!LAi_IsHitCritical(&attacker, &attackerLandTable, weaponType, strikeType)) return; // если крит

	float criticalDamageMtp = GetCritDamageMtp(&attackerLandTable, weaponType);           // получаем наш + крит урона
	criticalDamageMtp -= GetCritDefence(&enemyLandTable);                                 // вычитаем вражеское снижение крит урона
	damageMtp += criticalDamageMtp;                                                       // добавляем модификатор
}

bool LAi_IsGroupDamagableEnemy(ref attacker, ref enemy)
{
	if (!CheckAttribute(attacker, "chr_ai.group")) return true;
	if (!CheckAttribute(enemy, "chr_ai.group")) return true;

	if (attacker.chr_ai.group == enemy.chr_ai.group)
	{
		return false;
	}
	else if (enemy.chr_ai.group == LAI_GROUP_PLAYER && attacker.chr_ai.group == "Tmp_friend")
	{
		return false;
	}
	else if (attacker.chr_ai.group == LAI_GROUP_PLAYER && enemy.chr_ai.group == "TMP_FRIEND")
	{
		return false;
	}
	else if (enemy.chr_ai.group == LAI_GROUP_PEACE)
	{
		return false;
	}
	else if (CheckAttribute(attacker, "LSC_clan") && CheckAttribute(enemy, "LSC_clan"))
	{
		return false;
	}

	return true;
}


void LAi_SetResultOfDeath(ref attack, ref enemy, bool isSetBalde)
{
    if (sti(attack.index) == GetMainCharacterIndex())
    {
		if (CheckCharacterItem(pchar, "HolTradeLicence") && CheckAttribute(enemy, "City") && sti(enemy.nation) == HOLLAND) // Jason: изъятие лицензии
		{
			TakeNationLicence(HOLLAND);
			log_info(XI_ConvertString("LicenseCancel"));
		}
		if (CheckAttribute(enemy, "City") && sti(enemy.nation) == PIRATE) 
		{
			pchar.GenQuest.Piratekill = sti(pchar.GenQuest.Piratekill)+1;
			log_testinfo("Репутация у пиратов изменилась и равна "+sti(pchar.GenQuest.Piratekill)+"");
		}
		if (CheckAttribute(enemy, "LSC_clan")) // Jason: обиды кланов
		{
			DoQuestCheckDelay(enemy.chr_ai.group+"Conflict", 0.5);
		}
		if (findsubstr(enemy.model, "canib" , 0) != -1) // Jason: репутация индейцев
		{
			ChangeIndianRelation(-0.5);
		}
		if (findsubstr(enemy.model, "miskito" , 0) != -1)
		{
			ChangeIndianRelation(-1.0);
		}
		if (findsubstr(enemy.model, "squaw" , 0) != -1)
		{
			ChangeIndianRelation(-2.5);
		}
		if (GetRelation2BaseNation(sti(enemy.nation)) == RELATION_ENEMY)
		{
			if (!isSetBalde)
			{
				LAi_ChangeReputation(attack, -1);   // to_do
			if (CheckAttribute(enemy, "City"))
			{
				ChangeCharacterHunterScore(attack, NationShortName(sti(enemy.nation)) + "hunter", 2);
			}
		}
		}
		else
		{
			if (CheckAttribute(enemy, "City"))
			{
				ChangeCharacterHunterScore(attack, NationShortName(sti(enemy.nation)) + "hunter", 3);
			}
		}
		// обида нации на разборки в городе boal 19.09.05
  		if (CheckAttribute(enemy, "City"))
		{
			// нужна проверка на дуэли и квесты
			if (GetSummonSkillFromName(attack, SKILL_SNEAK) < rand(140)) // скрытность
			{
			    SetNationRelation2MainCharacter(sti(enemy.nation), RELATION_ENEMY);
		    }
		}
	}
}
// boal <--

float LAi_NPC_GetAttackPreferenceWeight(aref chr, string attackType, float fOff, float fOn)
{
	if(LAi_GetBladeFencingType(chr) == attackType) return fOn; 
	return fOff;
}

//--------------------------------------------------------------------------------
//Параметры NPC
//--------------------------------------------------------------------------------

float npc_return_tmp;
bool npc_return_tmpb;

//Атаки
//Скорость нарастания вероятности атаки в секунду  p > 0
#event_handler("NPC_Event_GetAttackActive","LAi_NPC_GetAttackActive");
float LAi_NPC_GetAttackActive()
{
	aref chr = GetEventData();
	float level = LAi_GetCharacterFightLevel(chr);
	npc_return_tmp = 0.3 + level*0.7;
	npc_return_tmp = npc_return_tmp + 0.1;
	return npc_return_tmp;
}

//Вес выбора удара "fast", 0 - никогда не выбирать
#event_handler("NPC_Event_GetAttackWeightFast","LAi_NPC_GetAttackWeightFast");
float LAi_NPC_GetAttackWeightFast()
{
	aref chr = GetEventData();
	npc_return_tmp = 20.0 * LAi_NPC_GetAttackPreferenceWeight(chr, "FencingS", 1.0, 3.0);
	npc_return_tmp = npc_return_tmp * LAi_NPC_GetAttackPreferenceWeight(chr, "FencingH", 1.0, 0.5);
	npc_return_tmp = npc_return_tmp * (0.8 + (0.1 * MOD_SKILL_ENEMY_RATE));
	return npc_return_tmp;
}

//Вес выбора удара "force", 0 - никогда не выбирать
#event_handler("NPC_Event_GetAttackWeightForce","LAi_NPC_GetAttackWeightForce");
float LAi_NPC_GetAttackWeightForce()
{
	aref chr = GetEventData();
	npc_return_tmp = 50.0 * LAi_NPC_GetAttackPreferenceWeight(chr, "FencingL", 1.0, 3.0);
	npc_return_tmp = npc_return_tmp * (0.8 + (0.1 * MOD_SKILL_ENEMY_RATE));
	return npc_return_tmp;
}

//Вес выбора удара "round", 0 - никогда не выбирать, если врагов <3 то удар не выбирается
#event_handler("NPC_Event_GetAttackWeightRound","LAi_NPC_GetAttackWeightRound");
float LAi_NPC_GetAttackWeightRound()
{
	aref chr = GetEventData();
	npc_return_tmp = 20.0;
	npc_return_tmp = npc_return_tmp * (0.8 + (0.1 * MOD_SKILL_ENEMY_RATE));
	return npc_return_tmp;
}

//Вес выбора удара "break", 0 - никогда не выбирать
#event_handler("NPC_Event_GetAttackWeightBreak","LAi_NPC_GetAttackWeightBreak");
float LAi_NPC_GetAttackWeightBreak()
{
	aref chr = GetEventData();
	npc_return_tmp = 20.0 * LAi_NPC_GetAttackPreferenceWeight(chr, "FencingH", 1.0, 3.0);
	npc_return_tmp = npc_return_tmp * LAi_NPC_GetAttackPreferenceWeight(chr, "FencingL", 1.0, 0.5);
	npc_return_tmp = npc_return_tmp * (0.6 + (0.1 * MOD_SKILL_ENEMY_RATE));
	return npc_return_tmp;
}

//Вес выбора удара "feint", 0 - никогда не выбирать
#event_handler("NPC_Event_GetAttackWeightFeint","LAi_NPC_GetAttackWeightFeint");
float LAi_NPC_GetAttackWeightFeint()
{
	aref chr = GetEventData();
	npc_return_tmp = 10.0; //30 boal fix
	npc_return_tmp = npc_return_tmp * (0.6 + (0.1 * MOD_SKILL_ENEMY_RATE));
	return npc_return_tmp;
}

//Прараметры защиты
//Вероятность желания защитится - кубик с такой вероятностью кидается 2 раза в секунду
#event_handler("NPC_Event_GetDefenceActive","LAi_NPC_GetAttackDefence");
float LAi_NPC_GetAttackDefence()
{
	aref chr = GetEventData();
	float level = LAi_GetCharacterFightLevel(chr);
	//npc_return_tmp = 0.05 + level*0.4;
	npc_return_tmp = 0.3 + level*0.35;
	/*if (!iArcadeFencingAI)	// to_do
	{
		npc_return_tmp = npc_return_tmp + 0.2;
	}*/
	return npc_return_tmp;
}

// boal 20.01.08 коммент - забавно, что спустя два года, понал как и что с вероятностями. Они все приводятся к 0-1 от веса общей суммы, то есть фактически умножение на сложность или цифры распределяют сумму по другим акшенам, а не усиливают этот
// Экшены идут парами - все атаки и защита (блок + пари)
//Вес выбора блока, 0 - никогда не выбирать
#event_handler("NPC_Event_GetDefenceWeightBlock","LAi_NPC_GetDefenceWeightBlock");
float LAi_NPC_GetDefenceWeightBlock()
{
	aref chr = GetEventData();
	npc_return_tmp = 80.0;
	npc_return_tmp = npc_return_tmp * (0.5 + (0.05 * MOD_SKILL_ENEMY_RATE));   // boal
	return npc_return_tmp;
}

//Вес выбора  паррирования, 0 - никогда не выбирать
//кубик с такой вероятностью кидается 2 раза в секунду
#event_handler("NPC_Event_GetDefenceWeightParry","LAi_NPC_GetDefenceWeightParry");
float LAi_NPC_GetDefenceWeightParry()
{
	aref chr = GetEventData();
	npc_return_tmp = 20.0; // 40 boal
	npc_return_tmp = npc_return_tmp * (0.6 + (0.1 * MOD_SKILL_ENEMY_RATE));
	return npc_return_tmp;
}

//Разрешён ли отскок
#event_handler("NPC_Event_EnableRecoil","LAi_NPC_EnableRecoil");
bool LAi_NPC_EnableRecoil()
{
	aref chr = GetEventData();
	npc_return_tmpb = true;
	return npc_return_tmpb;
}


//Параметры стрельбы
//Вероятность желания выстрелить - кубик с такой вероятностью кидается 2 раза в секунду
#event_handler("NPC_Event_GetFireActive","LAi_NPC_GetFireActive");
float LAi_NPC_GetFireActive()
{
	aref chr = GetEventData();
	if (!LAi_IsArmed(&chr)) return 0.0;

	float level = LAi_GetCharacterGunLevel(chr);
	npc_return_tmp = 0.001 + level*0.06;
	// boal наши офицеры пулят из всех стволов -->
	if (chr.chr_ai.group == LAI_GROUP_PLAYER)
	{
        npc_return_tmp = 0.38 + npc_return_tmp;
	}
	else
	{
	// boal наши офицеры пулят из всех стволов <--
		if (CheckAttribute(chr, "SuperShooter"))
		{
			npc_return_tmp = npc_return_tmp + 0.4 * MOD_SKILL_ENEMY_RATE / 10.0;
		}
		else
		{
			npc_return_tmp = npc_return_tmp + 0.1 * MOD_SKILL_ENEMY_RATE / 10.0;
		}
	}
	//if (npc_return_tmp > 0.5) npc_return_tmp = 0.5;
	
	return npc_return_tmp;
}

//Разрешён ли выстрел
#event_handler("NPC_Event_EnableFire","LAi_NPC_EnableFire");
bool LAi_NPC_EnableFire()
{
	aref chr = GetEventData();
	return   true;
	/*float level = LAi_GetCharacterGunLevel(chr);
	npc_return_tmpb = false;
	if(!iArcadeFencingAI)
	{
		level = level + 0.02;
	}
	else
	{
		level = level - 0.01;
	}
	if(level > 0.1) npc_return_tmpb = true;
	return npc_return_tmpb;    */
}

//Разрещён ли временный перевыбор цели среди ближних - опрашивается постоянно
#event_handler("NPC_Event_AdaptiveTargetSelect","LAi_NPC_AdaptiveTargetSelect");
bool LAi_NPC_AdaptiveTargetSelect()
{
	aref chr = GetEventData();
	if(chr.chr_ai.type == LAI_TYPE_ACTOR)
	{
		npc_return_tmpb = false;
	}else{
		npc_return_tmpb = true;
	}
	return npc_return_tmpb;
}

//--------------------------------------------------------------------------------
//Work
//--------------------------------------------------------------------------------

#event_handler("Location_CharacterSGFire","LAi_Location_CharacterSGFire");
void LAi_Location_CharacterSGFire()
{
	aref attack = GetEventData();
	aref enemy = GetEventData();
	float kDmg = GetEventData();
	if(LAi_IsDead(enemy)) return;
	//Реакция груп на атаку
	LAi_group_Attack(attack, enemy);
	//AddCharacterExp(attack, 100*kDmg);
	//Наносим повреждение
	LAi_ApplyCharacterDamage(enemy, MakeInt((5 + rand(5))*kDmg),"fire");
	//Проверим на смерть
	LAi_CheckKillCharacter(enemy);
}

#event_handler("ChrAttackAction", "LAi_ChrAttackAction");
bool LAi_ChrAttackAction()
{
	aref attack = GetEventData();
	string attackType = GetEventData();
	float curEnergy = Lai_CharacterGetEnergy(attack);
	float needEnergy = LAi_CalcUseEnergyForBlade(attack, attackType);
	if(curEnergy >= needEnergy)
	{
		npc_return_tmpb = true;
	}
	else
	{
		npc_return_tmpb = false;
	}
	return npc_return_tmpb;
}

#event_handler("ChrFgtActApply", "LAi_ChrFightActionApply");
void LAi_ChrFightActionApply()
{
	aref attack = GetEventData();
	string attackType = GetEventData();
	float needEnergy = LAi_CalcUseEnergyForBlade(attack, attackType);
	Lai_CharacterChangeEnergy(attack, -needEnergy);
	
	// TUTOR-ВСТАВКА
	if(TW_IsActive() && objTask.land_fight == "2_Defence" && attack.id == "SharlieTutorial_EnemyPirate_0" && attackType == "hit_parry")
	{
		TW_IncreaseCounter("land_fight", "FightDefence_parry", 1);
		if(TW_CheckCounter("land_fight", "FightDefence_block") && TW_CheckCounter("land_fight", "FightDefence_parry"))
			TW_FinishLand_Fight_2_Defence();
	}
}

//Получить относительную затрачиваемую энергию
#event_handler("NPC_Event_GetActionEnergy","LAi_NPC_GetActionEnergy");
float LAi_NPC_GetActionEnergy()
{
	aref chr = GetEventData();
	string act = GetEventData();
	npc_return_tmp = LAi_CalcUseEnergyForBlade(chr, act) / LAi_GetCharacterMaxEnergy(chr);  // boal
	return npc_return_tmp;
}

//Необходимо вернуть максимально быстро нормализованое значение жизни
#event_handler("NpcEvtHP", "LAi_NPC_EvtGetHP");
float LAi_NPC_EvtGetHP()
{
	aref chr = GetEventData();
	npc_return_tmp = LAi_GetCharacterRelHP(chr);
	return npc_return_tmp;
}

//Необходимо вернуть максимально быстро нормализованое значение энергии
#event_handler("NpcEvtEny", "LAi_NPC_EvtGetEny");
float LAi_NPC_EvtGetEny()
{
	aref chr = GetEventData();
	npc_return_tmp = LAi_GetCharacterRelEnergy(chr);
	return npc_return_tmp;
}

float SprintStartEnergyReq = 15.0;

#event_handler("ChrCheckEnergy", "LAi_Chr_CheckEnergy");
bool LAi_Chr_CheckEnergy()
{
	aref chr = GetEventData();
	string action = GetEventData(); // "recoil" - отскок назад, "strafe_l" и "strafe_r" - отскоки влево и вправо
	bool res = false;
	float needEnergy = 3.0;
	if (action == SPRINT_MOVE)
	{
		if (!LAi_group_IsActivePlayerAlarm()) return true;
		else needEnergy = SprintStartEnergyReq;
	}
	else if (action == STRAFE_L_MOVE || action == STRAFE_R_MOVE || action == STRAFE_B_MOVE)
	{
		if (HasPerk(chr, "TannedLeather")) needEnergy = PERK_VALUE2_TANNED_LEATHER;
	}

    /* switch(action)
    {
        case "recoil":        needEnergy = 3.0;    break;
        case "strafe_l":    needEnergy = 3.0;    break;
        case "strafe_r":    needEnergy = 3.0;    break;
    } */
	if (stf(chr.chr_ai.energy) >= needEnergy)
	{
		res = true;
		if (action != SPRINT_MOVE) Lai_CharacterChangeEnergy(chr, -needEnergy);
	}
	return res;
}

void ChickenGod_KhopeshKill(aref chr) {
	sld = ItemsFromID("khopesh1");
	if (!CheckAttribute(sld, "kills")) {
		sld.kills = 0;
	}
	
	sld.kills = sti(sld.kills) + 1;
	if (sti(sld.kills) >= 113) {
		TakeNItems(chr, "khopesh1", -1);
		TakeNItems(chr, "khopesh3", +1);
		EquipCharacterbyItem(chr, "khopesh3");
		SendMessage(chr, "ll", MSG_CHARACTER_BLADEHAND, 1);
	}
}

//belamour cle 1.5 френдлифаер
#event_handler("NPC_Event_ShotOnlyEnemyTest", "LAi_ShotOnlyEnemy");
bool LAi_ShotOnlyEnemy()
{
	if (!LAi_group_IsActivePlayerAlarm()) return false;
	
	aref chr = GetEventData();
	
	if(IsOfficer(chr)  && IsCharacterPerkOn(chr, "GunProfessional") && CharUseMusket(chr)) return true;
	if(chr.id == "RD_Prosper") return true;
	
	return false;
}

// evganat - прицеливание - обновление
#event_handler("AimingUpdate", "AimingUpdate");
void AimingUpdate()
{
	float fTime = GetEventData();
	int isFindedTarget = GetEventData();
	aref target = GetEventData();
	BI_CrosshairRefresh(fTime, isFindedTarget, target);
}

#event_handler("GetShardsQuantity","GetShardsQuantity");
int GetShardsQuantity()
{
	aref chr = GetEventData();
	string sType;
	if(CharUseMusket(chr))
		sType = "musket";
	else
		sType = "gun";
	
	string sBullet = LAi_GetCharacterBulletType(chr, sType);
	if(IsBulletGrape(sBullet))
	{
		if(CheckAttribute(chr, "chr_ai."+sType+".shards"))
			return sti(chr.chr_ai.(sType).shards);
	}
	return 1;
}

#event_handler("GetShotParams","GetShotParams");
aref GetShotParams()
{
	aref chr = GetEventData();
	string sType;
	if(CharUseMusket(chr))
		sType = "musket";
	else
		sType = "gun";
	aref arShards;
	makearef(arShards, chr.chr_ai.(stype));
	return arShards;
}

void ResetCritChanceBonus(aref chr)
{
	chr.chr_ai.crit_counter = 0;
}


float Lai_UpdateEnergyPerDltTime(aref chr, float curEnergy, float dltTime)
{
	float fMultiplier = 1.6666667;
	
	if(CheckAttribute(chr,"chr_ai.energy") && CheckAttribute(chr,"chr_ai.energyMax"))
	{
		if(stf(chr.chr_ai.energy) < stf(chr.chr_ai.energyMax)*0.1) fMultiplier = 3.0;
	}
	if(CheckCharacterPerk(chr, "Energaiser")) // скрытый перк боссов и ГГ
	{
		fMultiplier = fMultiplier * 1.5;
	}
	if(CheckCharacterPerk(chr, "Tireless")) 
	{
		fMultiplier = fMultiplier * 1.15;
	}
	if(CheckCharacterPerk(chr, "HT3")) 
	{
		fMultiplier = fMultiplier * 1.15;
	}
	if(GetCharacterEquipByGroup(chr, BLADE_ITEM_TYPE) == "blade_SP_3")
	{
		fMultiplier *= 1.0 + Bring2Range(0.0, 0.875, 0.0, 0.5, (1.0 - LAi_GetCharacterRelHP(chr)) / 2.0);
	}

	bool bPeace = true;
	if(CheckAttribute(chr, "chr_ai.group") && chr.chr_ai.group == LAI_GROUP_PLAYER && LAi_group_IsActivePlayerAlarm())
		bPeace = false;
	else if(CheckAttribute(chr, "chr_ai.tmpl") && chr.chr_ai.tmpl == LAI_TMPL_FIGHT)
		bPeace = false;
	if(bPeace)
		fMultiplier *= 3.0;

	if(CheckAttribute(chr, "cheats.energyupdate")) fMultiplier = fMultiplier * 10.0;
	float fEnergy;
	fEnergy = curEnergy + dltTime * fMultiplier; 

	return fEnergy;
}

void LAi_Achievments_ExtraDamage(ref attacker, int damage)
{
	if (CheckAttribute(pchar,"Achievment.ExtraDamage")) return;
	if (IsMainCharacter(attacker) && damage <= 999) return;

	Achievment_Set("ach_CL_122");
	pchar.Achievment.ExtraDamage = true;
}

#event_handler("Event_GetAdditionalMeleeDist", "LAi_GetAdditionalMeleeDist");
float LAi_GetAdditionalMeleeDist()
{
	aref attack = GetEventData();
	string sAttackType = GetEventData();
	if (sAttackType != FORCE_STRIKE || sAttackType != FAST_STRIKE) return 0.0;
	if (HasPerk(&attack, "SabreHurricane")) return 30.0;
	return 0.0;
}

#event_handler("Event_GetAdditionalMeleeAng", "LAi_GetAdditionalMeleeAng");
float LAi_GetAdditionalMeleeAng()
{
	aref attack = GetEventData();
	string sAttackType = GetEventData();
	if (sAttackType != FORCE_STRIKE || sAttackType != FAST_STRIKE) return 0.0;
	if (HasPerk(&attack, "SabreHurricane")) return 30.0;
	return 0.0;
}
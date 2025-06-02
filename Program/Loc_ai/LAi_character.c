
//------------------------------------------------------------------------------------------
//Login
//------------------------------------------------------------------------------------------

//Установить время загрузки персонажа
void LAi_SetLoginTime(aref chr, float start, float end)
{
	if(start < 0) start = 0;
	if(start >= 24) start = 23.99999999;
	if(end < 0) end = 0;
	if(end >= 24) end = 23.99999999;
	chr.location.stime = start;
	chr.location.etime = end;
}

//Удалить время загрузки персонажа
void LAi_RemoveLoginTime(aref chr)
{
	aref loc;
	makearef(loc, chr.location);
	DeleteAttribute(loc, "stime");
	DeleteAttribute(loc, "etime");
}

//Данный персонаж является верующим, и в определённое время находиться в церкви
void LAi_SetFanatic(aref chr, string churchID, string group, string locator, float start, float end)
{
	chr.location.church = churchID;
	chr.location.church.group = group;
	chr.location.church.locator = locator;
	chr.location.church.stime = start;
	chr.location.church.etime = end;
}

//Сделать обычным персонаж
void LAi_RemoveFanatic(aref chr)
{
	aref loc;
	makearef(loc, chr.location);
	DeleteAttribute(loc, "church");
}

//Запретить перерождение персонажа после убийства
void LAi_NoRebirthEnable(aref chr)
{
	chr.location.norebirth = "1";
}

//Разрешить перерождение персонажа после убийства
void LAi_NoRebirthDisable(aref chr)
{
	aref loc;
	makearef(loc, chr.location);
	DeleteAttribute(loc, "norebirth");
}

//Перерождение нпс со старым именем
void LAi_RebirthOldName(aref chr)
{
	chr.location.rebirthOldName = true;
}

//Разрешить/запретить персонажу загружаться в захваченную локацию
void LAi_LoginInCaptureTown(aref chr, bool isEnable)
{
	aref loc;
	makearef(loc, chr.location);
	if(isEnable)
	{
		loc.loadcapture = "1";
	}else{
		DeleteAttribute(loc, "loadcapture");
	}
}

//------------------------------------------------------------------------------------------
//Fight, hp
//------------------------------------------------------------------------------------------

//Установить хитпойнты
void LAi_SetHP(aref chr, float cur, float max)
{
	if(max < 1) max = 1;
	if(cur < 0) cur = 0;
	if(cur > max) cur = max;
	chr.chr_ai.hp = cur;
	chr.chr_ai.hp_max = max;
}

//Установить текущии хитпойнты
void LAi_SetCurHP(aref chr, float cur)
{
	float maxHP = LAI_DEFAULT_HP_MAX;
	if(CheckAttribute(chr, "chr_ai.hp_max"))
	{
		maxHP = stf(chr.chr_ai.hp_max);
		if(maxHP < 1) maxHP = 1;
	}
	chr.chr_ai.hp_max = maxHP;
	if(cur < 0) cur = 0;
	if(cur > maxHP) cur = maxHP;
	chr.chr_ai.hp = cur;
	if (cur == 0.0 && CheckAttribute(chr, "PGGAi"))
	{
		PGG_CheckDead(chr);
	}
}

//Установить текущии хитпойнты и энергию максимальными
void LAi_SetCurHPMax(aref chr)
{
	float maxHP = LAI_DEFAULT_HP_MAX;
	if(CheckAttribute(chr, "chr_ai.hp_max"))
	{
		maxHP = stf(chr.chr_ai.hp_max);
		if(maxHP < 1) maxHP = 1;
	}
	chr.chr_ai.hp_max = maxHP;
	chr.chr_ai.hp = maxHP;

	chr.chr_ai.energy    = LAi_GetCharacterMaxEnergy(chr); // восстановление там, где мах НР
}

//Скорость изменения хп в секунду
void LAi_SetDltHealth(aref chr, float healthPerSec)
{
	//if(healthPerSec < 0) healthPerSec = 0;
	chr.chr_ai.hp_dlt = healthPerSec;
}

//Использовать бутылочку-лечилку
void LAi_UseHealthBottle(aref chr, float healthInBottle)
{
	if(healthInBottle <= 0) return;	
	if(!CheckAttribute(chr, "chr_ai.hp_bottle"))
	{
		chr.chr_ai.hp_bottle = "0";
	}
	chr.chr_ai.hp_bottle = stf(chr.chr_ai.hp_bottle) + healthInBottle;
	if(chr.id == Characters[nMainCharacterIndex].id) chr.chr_ai.usedbottlemax = stf(chr.chr_ai.hp_bottle);
}
// boal
void LAi_UseHealthBottleSpeed(aref chr, float healthSpeed)
{
	if (healthSpeed <= 0) return;
	
	chr.chr_ai.hp_dlt_bottle = healthSpeed;
}

//navy -->
void LAi_AlcoholSetDrunk(aref chr, float alcoholDegree, float time)
{
	//эффекты не суммируются.
	if (CheckAttribute(chr, "chr_ai.drunk")) return;
	//float energyMax;
	if(sti(chr.index) == GetMainCharacterIndex()) notification(XI_ConvertString("Drunk note"),"Drunk");
	chr.chr_ai.drunk = time;
	bool bHat8 = GetCharacterEquipByGroup(chr, HAT_ITEM_TYPE) == "hat8";
	int n = 0;
	//много рома в таверне
	if (alcoholDegree > 70)
	{
		if(bHat8) n = 10;
		else n = -20;
		chr.chr_ai.drunk.skill.FencingL     = n;
		chr.chr_ai.drunk.skill.FencingS     = n;
		chr.chr_ai.drunk.skill.FencingH     = n;
		chr.chr_ai.drunk.skill.Pistol       = n;
		chr.chr_ai.drunk.skill.Fortune      = n;
		chr.chr_ai.drunk.skill.Sneak        = n;
		chr.chr_ai.drunk.skill.Leadership   = n;
	}
	else
	{
		if(bHat8) n = 5;
		//Ром
		if (alcoholDegree > 50)
		{
			chr.chr_ai.drunk.skill.FencingL = -10 + n;
			chr.chr_ai.drunk.skill.FencingH = 10 + n;
		}
		//вино
		else
		{
			chr.chr_ai.drunk.skill.FencingL = 10 + n;
			chr.chr_ai.drunk.skill.FencingH = -10 + n;
		}
		chr.chr_ai.drunk.skill.Fortune = 5 + n;
		chr.chr_ai.drunk.skill.Pistol = -20 + n;
	}

	//думал бонус к макс энергии сделать, но оно по другому работает :) пока так.. а там видно будет.
	if(CheckAttribute(chr, "chr_ai.energy"))
	{
		/*
		energyMax = stf(chr.chr_ai.energyMax);
		if(energyMax < 1) energyMax = 1;
		chr.chr_ai.drunk.energyMax = energyMax*0.2;
		chr.chr_ai.energyMax = stf(chr.chr_ai.energyMax) + stf(chr.chr_ai.drunk.energyMax);
		*/
		chr.chr_ai.energy = stf(chr.chr_ai.energy) + 20;
	}
}

void LAi_SetAlcoholNormal(aref chr)
{
	/*
	if(CheckAttribute(chr, "chr_ai.energyMax"))
	{
		chr.chr_ai.energyMax = stf(chr.chr_ai.energyMax) - stf(chr.chr_ai.drunk.energyMax);
	}
	*/
	if (CheckAttribute(pchar, "questTemp.Rum")) DeleteAttribute(pchar, "questTemp.Rum");
	if (CheckAttribute(pchar, "GenQuest.CamShuttle")) DeleteAttribute(pchar, "GenQuest.CamShuttle");

	DeleteAttribute(chr, "chr_ai.drunk");
}
//<--

//Использовать бутылочку-противоядие
void LAi_UseAtidoteBottle(aref chr)
{
	DeleteAttribute(chr, "chr_ai.poison");
}

//Отравлен
bool LAi_IsPoison(aref chr)
{
	if(CheckAttribute(chr, "chr_ai.poison")) return true;
	return false;
}

//Сделать персонажа бессмертным
void LAi_SetImmortal(aref chr, bool isImmortal)
{
	if(isImmortal)
	{
		chr.chr_ai.immortal = "1";
	}else{
		aref chr_ai;
		makearef(chr_ai, chr.chr_ai);
		DeleteAttribute(chr_ai, "immortal");
	}
}

//Узнать отношение персонажа к бессмертию
bool LAi_IsImmortal(aref chr)
{
	if(CheckAttribute(chr, "chr_ai.immortal"))
	{
		if(sti(chr.chr_ai.immortal) != 0)
		{
			return true;
		}
	}
	return false;
}


//Получить хп персонажа
float LAi_GetCharacterHP(aref chr)
{
	float curHp = 0.0;
	if(CheckAttribute(chr, "chr_ai.hp"))
	{
		curHp = stf(chr.chr_ai.hp);
	}
	float maxHp = LAi_GetCharacterMaxHP(chr);
	if(curHp > maxHp) curHp = maxHp;
	chr.chr_ai.hp = curHp;
	chr.chr_ai.hp_max = maxHp;
	return curHp;
}

//Получить максимальные хп персонажа
float LAi_GetCharacterMaxHP(aref chr)
{
	float max_hp = 0.0;
	if(CheckAttribute(chr, "chr_ai.hp_max"))
	{
		max_hp = stf(chr.chr_ai.hp_max);
	}
	if(max_hp < 0.0) max_hp = 0.0;
	
	if(IsEquipCharacterByArtefact(chr, "amulet_7"))
	{
		if(!CheckAttribute(chr, "chr_ai.hp_max_back"))
		{
			chr.chr_ai.hp_max_back = max_hp;
			if(ShipBonus2Artefact(chr, SHIP_GALEON_SM))
				max_hp += makeint(100.0/stf(chr.rank)) + 40.0;
			else
				max_hp += makeint(100.0/stf(chr.rank)) + 23.0;	
		}
	}
	else
	{
		if(CheckAttribute(chr, "chr_ai.hp_max_back"))
		{
			max_hp = stf(chr.chr_ai.hp_max_back);
			DeleteAttribute(chr, "chr_ai.hp_max_back");
		}
	}
	
	chr.chr_ai.hp_max = max_hp;
	return max_hp;
}

//Получить относительные хп персонажа 0..1
float LAi_GetCharacterRelHP(aref chr)
{
	float hp = LAi_GetCharacterHP(chr);
	float maxhp = LAi_GetCharacterMaxHP(chr);
	if(maxhp <= 0.0) return 0.0;
	if(maxhp > 0.0)
	{
		return hp/maxhp;
	}
	return 0.0;
}

//Получить относительную энергию персонажа 0..1
float LAi_GetCharacterRelEnergy(aref chr)
{
	float energy = 0.0;
	if(CheckAttribute(chr, "chr_ai.energy"))
	{
		energy = stf(chr.chr_ai.energy);
		energy = energy / LAi_GetCharacterMaxEnergy(chr); // boal
	}
	return energy;
}
// boal
float LAi_GetCharacterMaxEnergy(aref chr)
{
	if(CheckAttribute(chr, "chr_ai.energyMax"))
	{
		return stf(chr.chr_ai.energyMax);
	}
	return LAI_DEFAULT_ENERGY_MAX;
}

//Установить проверяльщик хп, если их становиться меньше чем, вызвать квест
void LAi_SetCheckMinHP(aref chr, float min, bool immortal, string quest)
{
	if(min < 0.9999999) min = 0.9999999;
	chr.chr_ai.hpchecker = min;
	chr.chr_ai.hpchecker.quest = quest;
	chr.chr_ai.hpchecker.immortal = immortal;
}

//Удалить проверяльщик хп
void LAi_RemoveCheckMinHP(aref chr)
{
	aref chr_ai;
	makearef(chr_ai, chr.chr_ai);
	DeleteAttribute(chr_ai, "hpchecker");	
}

//Убить персонажа
void LAi_KillCharacter(aref chr)
{
	chr.chr_ai.hp = "0";
	if(CheckAttribute(chr, "chr_ai.immortal"))
	{
		string old = chr.chr_ai.immortal;
		chr.chr_ai.immortal = "0";
		LAi_CheckKillCharacter(chr);
		chr.chr_ai.immortal = old;
	}else{
		LAi_CheckKillCharacter(chr);
	}
}

// belamour убить бессмертного персонажа
void LAi_KillImmortalCharacter(ref chr)
{
	if(CheckCharacterPerk(chr, "IronWill"))
	{
		DelCharacterPerk(chr, "IronWill");
	}
	if(CheckAttribute(chr, "OfficerImmortal"))
	{
		DeleteAttribute(chr, "OfficerImmortal");
	}
	if(CheckAttribute(chr, "chr_ai.immortal"))
	{
		DeleteAttribute(chr, "chr_ai.immortal");
	}
	LAi_KillCharacter(chr);
}

//Убит ли персонаж
bool LAi_IsDead(aref chr)
{
	if(chr.id == "0") return true; // boal если фантома нет, то НПС умер
	if(CheckAttribute(chr, "chr_ai.hp") == false) return true;
	if(stf(chr.chr_ai.hp) < 1.0) return true;
	return false;
}


//------------------------------------------------------------------------------------------
//Other
//------------------------------------------------------------------------------------------

//Является ли персонаж управляемым
bool LAi_IsCharacterControl(aref chr)
{
	if(CheckAttribute(chr, "chr_ai.tmpl"))
	{
		if(chr.chr_ai.tmpl == LAI_TMPL_PLAYER) return true;
	}
	return false;
}

//Запретить диалог с персонажем
void LAi_CharacterDisableDialog(aref chr)
{
	chr.chr_ai.disableDlg = "1";
}

//Разрешить диалог с персонажем
void LAi_CharacterEnableDialog(aref chr)
{
	chr.chr_ai.disableDlg = "0";
}

//Разрешить при смерти порождить фантома
void LAi_CharacterReincarnation(aref chr, bool isEnable, bool isUseCurModel)
{
	LAi_CharacterReincarnationEx(chr, isEnable, isUseCurModel, "");
}

//Разрешить при смерти порождить фантома
void LAi_CharacterReincarnationEx(aref chr, bool isEnable, bool isUseCurModel, string locgroup)
{
	if(isEnable)
	{
		if(isUseCurModel)
		{
			chr.chr_ai.reincarnation = "0";
		}else{
			chr.chr_ai.reincarnation = "1";
		}
		if(locgroup == "") locgroup = "goto";
		chr.chr_ai.reincarnation.group = locgroup;
	}
	else
	{
		chr.chr_ai = "";
		aref chr_ai;
		makearef(chr_ai, chr.chr_ai);
		DeleteAttribute(chr_ai, "reincarnation");
	}	
}

bool LAi_CharacterIsReincarnation(aref chr)
{
	if(CheckAttribute(chr, "chr_ai.reincarnation") == false) return false;
	return true;
}

bool LAi_CharacterReincarnationMode(aref chr)
{
	if(CheckAttribute(chr, "chr_ai.reincarnation") == false)
	{
		Trace("LAi_CharacterReincarnationMode -> no field chr.chr_ai.reincarnation");
		return false;
	}
	if(sti(chr.chr_ai.reincarnation) != 0) return true;
	return false;
}

string LAi_CharacterReincarnationGroup(aref chr)
{
	if(CheckAttribute(chr, "chr_ai.reincarnation.group") == false)
	{
		Trace("LAi_CharacterReincarnationGroup -> no field chr.chr_ai.reincarnation");
		return "goto";
	}
	if(chr.chr_ai.reincarnation.group != "") return chr.chr_ai.reincarnation.group;
	return "goto";
}

//eddy. установить установить шаг повышения ранга фантома при реинкарнации.
bool LAi_SetReincarnationRankStep(aref _chr, int _step) 
{
	if(CheckAttribute(_chr, "chr_ai.reincarnation"))
	{
		_chr.chr_ai.reincarnation.step = _step;
		_chr.baseIndex = _chr.index; //теперь все реинкарнированные фантомы будут помнить индекс своего прародителя.
		return true;
	}
	else Trace("LAi_SetReincarnationRankStep -> no field chr.chr_ai.reincarnation");
	return false;
}

//------------------------------------------------------------------------------------------
//Other
//------------------------------------------------------------------------------------------

//Проиграть звук
void LAi_CharacterPlaySound(aref chr, string soundname)
{
	SendMessage(chr, "s", soundname);
}

//Переключиться в боевой или мирный режим
void LAi_SetFightMode(aref chr, int isFightMode)
{
	if(isFightMode)
	{
		if(SendMessage(chr, "ls", MSG_CHARACTER_EX_MSG, "CheckFightMode") != 0)
			return; //Не для переключения между режимами эта функция
		if(CheckAttribute(chr, "PriorityMode"))
			isFightMode = sti(chr.PriorityMode);
	}
	SendMessage(chr, "lsl", MSG_CHARACTER_EX_MSG, "ChangeFightMode", isFightMode);
}
// boal
void LAi_SetFightModeForOfficers(bool isFightMode)
{
    ref chr;
    int j, cn;
    for(j=1; j<4; j++)
    {
        cn = GetOfficersIndex(GetMainCharacter(),j);
        if( cn>0 )
        {
	        chr = GetCharacter(cn);
	        LAi_type_officer_Init(chr);
	        //LAi_group_UpdateTargets(chr);
			LAi_SetFightMode(chr, isFightMode);
	    }
	}
}

//Присвоить персонажу боевой режим (для появления без анимации доставания оружия на абордажах, штурмах и т.д.)
void LAi_InstantFightMode(aref chr)
{
	if(CheckAttribute(chr, "PriorityMode"))
		SendMessage(chr, "lsl", MSG_CHARACTER_EX_MSG, "SetFightMode", sti(chr.PriorityMode));
	else
		SendMessage(chr, "lsl", MSG_CHARACTER_EX_MSG, "SetFightMode", 1);
}

//Заблокировать текущий режим (!!! сбрасывается при смене шаблона !!!)
void LAi_LockFightMode(aref chr, bool isLockFightMode)
{
	SendMessage(&chr, "lsl", MSG_CHARACTER_EX_MSG, "LockFightMode", isLockFightMode);
}

//Получить режим боя (2 - мушкетный у универсалов, 1 - сабля у универсалов и просто боевой у остальных, 0 - мирный)
int LAi_CheckFightMode(aref chr)
{
	return SendMessage(&chr, "ls", MSG_CHARACTER_EX_MSG, "CheckFightMode");
}

//------------------------------------------------------------------------------------------
//Weapons
//------------------------------------------------------------------------------------------


//Получить относительный заряд пистолета
float LAi_GetCharacterRelCharge(aref chr, string sType)
{
	if(CheckAttribute(chr, "chr_ai."+sType+".charge"))
	{
		if(CheckAttribute(chr, "chr_ai."+sType+".chargeprc"))
		{
			if(sti(chr.chr_ai.(sType).chargeprc))
			{
				if(!CheckAttribute(chr, "chr_ai."+sType+".charge_max")) return 0.0;
				float charge = stf(chr.chr_ai.(sType).charge);
				float chargemax = stf(chr.chr_ai.(sType).charge_max);
				if(chargemax <= 0) return 0.0;
				if(charge >= chargemax) charge = chargemax;
				charge = charge/chargemax;
				if(charge < 0.0) charge = 0.0;
				if(charge > 1.0) charge = 1.0;
				return charge;
			}
			else return 1.0;
		}
		else chr.chr_ai.(sType).chargeprc = "1";
	}
	return 0.0;
}

//Получить максимальное количество зарядов пистолета
int LAi_GetCharacterChargeQuant(aref chr, string sType)
{
	if(CheckAttribute(chr, "chr_ai."+sType+".charge_max"))
	{
		return sti(chr.chr_ai.(sType).charge_max);
	}
	return 0;
}

//Получить текущее количество зарядов пистолета
int LAi_GetCharacterChargeCur(aref chr, string sType)
{
	if(CheckAttribute(chr, "chr_ai."+sType+".charge"))
	{
		float charge = stf(chr.chr_ai.(sType).charge);
		return MakeInt(charge);
	}
	return 0;
}

//Установить количество зарядов
void LAi_GunSetChargeQuant(aref chr, string sType, int quant)
{
	if(quant < 0) quant = 0;
	if(quant > 5) quant = 5;
	chr.chr_ai.(sType).charge_max = quant;
	
	int iCharge = iGetPistolChargeNum(chr, sType, quant);
	chr.chr_ai.(sType).charge = iCharge;
	
	chr.chr_ai.(sType).chargeprc = "1";
}

void LAi_SetCharacterBulletType(ref rChar, string sBullet)
{
	switch(sBullet)
	{
		case "bullet":
			TakeNItems(rChar, sBullet, 30 + rand(20));
		break;
		case "cartridge":
			TakeNItems(rChar, sBullet, 5 + rand(5));
		break;
		case "grapeshot":
			TakeNItems(rChar, sBullet, 10 + rand(5));
		break;
		case "shotgun_bullet":
			TakeNItems(rChar, sBullet, 10 + rand(10));
		break;
		case "powder_pellet":
			TakeNItems(rChar, sBullet, 5 + rand(5));
		break;
		case "grenade":
			TakeNItems(rChar, sBullet, 5 + rand(5));
		break;
		case "harpoon":
			TakeNItems(rChar, sBullet, 5 + rand(5));
		break;
	}
}

// ugeen --> получим тип пуль на одетом огнестрельном оружии
string LAi_GetCharacterBulletType(ref rChar, string sType)
{
	string sBulletType = "";	
	string sGun;
	if(sType == "gun")
		sGun = GetCharacterEquipByGroup(rChar, GUN_ITEM_TYPE);
	else
		sGun = GetCharacterEquipByGroup(rChar, MUSKET_ITEM_TYPE);
	
	if(sGun != "") 
	{
		if(CheckAttribute(rChar,"chr_ai."+sType+".bullet"))		
		{
			sBulletType 	= rChar.chr_ai.(sType).bullet;
		}	
	}			
	return sBulletType;
}

bool IsBulletGrape(string sBullet)
{
	if(sBullet == "grapeshot" || sBullet == "GunEchin" || sBullet == "grapeshot_double")
		return true;
	return false;
}

// ugeen --> получим тип пороха на одетом огнестрельном оружии и известном типе пуль
string LAi_GetCharacterGunpowderType(ref rChar, string sType)
{
	string sGunpowderType = "";		
	string sGun;
	if(sType == "gun")
		sGun = GetCharacterEquipByGroup(rChar, GUN_ITEM_TYPE);
	else
		sGun = GetCharacterEquipByGroup(rChar, MUSKET_ITEM_TYPE);
	
	if(sGun != "") 
	{
		if(CheckAttribute(rChar,"chr_ai."+sType+".gunpowder"))		
		{
			sGunPowderType  = rChar.chr_ai.(sType).gunpowder;
		}	
	}			
	return sGunpowderType;
}

string LAi_SetCharacterDefaultBulletType(ref rChar, string sType)
{
	string sAttr;
	string sBulletType = "";
	int iNum;
	bool isBulletSet = false;
	aref rType;
	string sGun;
	if(sType == "gun")
		sGun = GetCharacterEquipByGroup(rChar, GUN_ITEM_TYPE);
	else
		sGun = GetCharacterEquipByGroup(rChar, MUSKET_ITEM_TYPE);
	
	if(sGun != "") 
	{
		ref rItm = ItemsFromID(sGun); 
		makearef(rType, rItm.type);
		iNum = GetAttributesNum(rType);
		for (int i = 0; i < iNum; i++)
		{
			sAttr = GetAttributeName(GetAttributeN(rType, i));
			if(sti(rItm.type.(sAttr).Default) > 0)
			{
				sBulletType = rItm.type.(sAttr).bullet;
				isBulletSet = LAi_SetCharacterUseBullet(rChar, sType, sBulletType);
			}
		}
		if(!isBulletSet) trace("can't set default bullet for character id " + rChar.id);
	}			
	return sBulletType;
}

// belamour получить дефолтный тип пуль для огнестрела
string LAi_GetCharacterDefaultBulletType(string sGun)
{
	string sAttr;
	string sBulletType = "";
	int iNum;
	aref rType;
	
	if(sGun != "") 
	{
		ref rItm = ItemsFromID(sGun); 
		makearef(rType, rItm.type);
		iNum = GetAttributesNum(rType);
		for (int i = 0; i < iNum; i++)
		{
			sAttr = GetAttributeName(GetAttributeN(rType, i));
			if(sti(rItm.type.(sAttr).Default) > 0)
			{
				sBulletType = rItm.type.(sAttr).bullet;
			}
		}
	}			
	return sBulletType;
}

// belamour зарядить оружие имеющимся типом боеприпаса
void GunCharging(ref _Ch, string sType, string sGun)
{
	string sAttr, Bullet;
	string sBulletType = "";
	int iNum;
	aref rType, aref gun;
	Items_FindItem(sGun, &Gun);
	makearef(rType, gun.type);
	iNum = GetAttributesNum(rType);
	for (int i = 0; i < iNum; i++)
	{
		sAttr = GetAttributeName(GetAttributeN(rType, i));
		sBulletType = gun.type.(sAttr).bullet;
		if(GetCharacterItem(_Ch, sBulletType) > 0) 
		{
			if(gun.type.(sAttr).gunpowder != "" && GetCharacterItem(_Ch, gun.type.(sAttr).gunpowder) > 0) {Bullet = sBulletType; break;}
			if(gun.type.(sAttr).gunpowder == "") {Bullet = sBulletType; break;}
		}
	}
	if(Bullet != "")
	{
		LAi_SetCharacterUseBullet(_Ch, sType, Bullet);
		LAi_GunSetUnload(_Ch, sType);
		PlaySound("People Fight\reload1.wav");
	}
	else PlaySound("PEOPLE FIGHT\MushketEmpty.wav");
}

bool LAi_CanCharacterUseBullet(ref chr, string type, string bullet) {
	string gunName = GetCharacterEquipByGroup(chr, type);

	if (gunName == "") {
		return false;
	}

	ref gun = ItemsFromID(gunName);
	aref gunBulletType;
	makearef(gunBulletType, gun.type);
	int bulletCount = GetAttributesNum(gunBulletType);
	for (int i = 0; i < bulletCount; i++) {
		aref gunBullet = GetAttributeN(gunBulletType, i);
		if (bullet == gunBullet.bullet) {
			return true;
		}
	}

	return false;
}


bool LAi_SetCharacterUseBullet(ref rChar, string sType, string sBullet)
{
	string 	sAttr;
	string 	sBulletType = "";
	int 	iNum;
	aref 	rType;
	string	sGun;
	if(sType == "gun")
		sGun = GetCharacterEquipByGroup(rChar, GUN_ITEM_TYPE);
	else
		sGun = GetCharacterEquipByGroup(rChar, MUSKET_ITEM_TYPE);
	
	if(sGun != "") 
	{
		rChar.bullets.(sType) = sBullet;
		ref rItm = ItemsFromID(sGun); 
		makearef(rType, rItm.type);
		iNum = GetAttributesNum(rType);		
		for (int i = 0; i < iNum; i++)
		{
			sAttr = GetAttributeName(GetAttributeN(rType, i));
			sBulletType = rItm.type.(sAttr).bullet;
			if(sBulletType == sBullet)
			{
				rChar.chr_ai.(sType).sGun			= sGun;
				rChar.chr_ai.(sType).bulletType		= sAttr;
				rChar.chr_ai.(sType).bulletNum 		= iNum;
				rChar.chr_ai.(sType).bullet 		= sBulletType;
				rChar.chr_ai.(sType).gunpowder		= rItm.type.(sAttr).gunpowder;
				rChar.chr_ai.(sType).accuracy		= rItm.type.(sAttr).Accuracy;
				rChar.chr_ai.(sType).chargespeed	= rItm.type.(sAttr).ChargeSpeed;				
				rChar.chr_ai.(sType).DmgMin_NC		= rItm.type.(sAttr).DmgMin_NC;
				rChar.chr_ai.(sType).DmgMax_NC 		= rItm.type.(sAttr).DmgMax_NC;
				rChar.chr_ai.(sType).DmgMin_C 		= rItm.type.(sAttr).DmgMin_C;				
				rChar.chr_ai.(sType).DmgMax_C 		= rItm.type.(sAttr).DmgMax_C;
				rChar.chr_ai.(sType).EnergyP_NC 	= rItm.type.(sAttr).EnergyP_NC;
				rChar.chr_ai.(sType).EnergyP_C 		= rItm.type.(sAttr).EnergyP_C;
				rChar.chr_ai.(sType).Stun_NC 		= rItm.type.(sAttr).Stun_NC;
				rChar.chr_ai.(sType).Stun_C			= rItm.type.(sAttr).Stun_C;						
				rChar.chr_ai.(sType).MultiDmg       = rItm.type.(sAttr).multidmg;
				rChar.chr_ai.(sType).MisFire		= rItm.type.(sAttr).misfire;
				rChar.chr_ai.(sType).SelfDamage		= rItm.type.(sAttr).SelfDamage;
				rChar.chr_ai.(sType).Explosion		= rItm.type.(sAttr).Explosion;
				
				if(IsBulletGrape(sBullet))
				{
					rChar.chr_ai.(sType).basedmg	= rItm.type.(sAttr).basedmg;
					rChar.chr_ai.(sType).shards		= rItm.type.(sAttr).shards;
					rChar.chr_ai.(sType).width		= rItm.type.(sAttr).width;
					rChar.chr_ai.(sType).height		= rItm.type.(sAttr).height;
				}
				
				rItm.ChargeSpeed			= rItm.type.(sAttr).ChargeSpeed;
				rItm.Accuracy				= rItm.type.(sAttr).Accuracy;
				rItm.DmgMin					= rItm.type.(sAttr).DmgMin_NC;
				rItm.DmgMax					= rItm.type.(sAttr).DmgMax_NC;
				rItm.dmg_min 				= rItm.type.(sAttr).DmgMin_NC;
				rItm.dmg_max				= rItm.type.(sAttr).DmgMax_NC;
								
				if(CheckAttribute(rItm,"chargeQ"))										LAi_GunSetChargeQuant(rChar, sType, sti(rItm.chargeQ));
				else																	LAi_GunSetChargeQuant(rChar, sType, 0);						
				if(CheckAttribute(rItm,"chargespeed") && stf(rItm.chargespeed) > 0.0)	LAi_GunSetChargeSpeed(rChar, sType, 1.0/stf(rItm.chargespeed));
				else																	LAi_GunSetChargeSpeed(rChar, sType, 0.0);				
				if(CheckAttribute(rItm,"dmg_min"))										LAi_GunSetDamageMin(rChar, sType, stf(rItm.dmg_min));
				else																	LAi_GunSetDamageMin(rChar, sType, 0.0);				
				if(CheckAttribute(rItm,"dmg_max"))										LAi_GunSetDamageMax(rChar, sType, stf(rItm.dmg_max));
				else																	LAi_GunSetDamageMax(rChar, sType, 0.0);				
				if(CheckAttribute(rItm,"accuracy"))										LAi_GunSetAccuracy(rChar, sType, stf(rItm.accuracy)*0.01);
				else																	LAi_GunSetAccuracy(rChar, sType, 0.0);
			
				return true;	
			}
		}
	}			
	return false;
}

float LAi_GetGunChargeProgress(aref chr)
{
	if(GetCharacterEquipByGroup(chr, GUN_ITEM_TYPE) == "") return 0.0;
	if(CheckAttribute(chr, "chr_ai.gun.charge"))
	{
		float charge = chr.chr_ai.gun.charge;
		if(charge > 1.0) charge -= MakeInt(chr.chr_ai.gun.charge);
		if(CheckAttribute(chr, "chr_ai.gun.charge_max") && MakeInt(chr.chr_ai.gun.charge_max) == MakeInt(chr.chr_ai.gun.charge))
			charge = 0.0;
	}
	else return 0.0;

	return charge;
}

float LAi_GetMusketChargeProgress(aref chr)
{
	if(GetCharacterEquipByGroup(chr, MUSKET_ITEM_TYPE) == "") return 0.0;
	if(CheckAttribute(chr, "chr_ai.musket.charge"))
	{
		float charge = chr.chr_ai.musket.charge;
		if(charge > 1.0) charge -= MakeInt(chr.chr_ai.musket.charge);
		if(CheckAttribute(chr, "chr_ai.musket.charge_max") && MakeInt(chr.chr_ai.musket.charge_max) == MakeInt(chr.chr_ai.musket.charge))
			charge = 0.0;
	}
	else return 0.0;

	return charge;
}

float LAi_GetPotionProgress(aref chr)
{
	if(CheckAttribute(chr, "chr_ai.usedbottlemax"))
	{
		float fmax = stf(chr.chr_ai.usedbottlemax); 
		if(CheckAttribute(chr, "chr_ai.hp_bottle"))
		{
			float fcur = stf(chr.chr_ai.hp_bottle);
		}
		else return 1.0;
		
		return 1.0 - fcur/fmax;
	}
	return 1.0;
}

// Warship. Методы по зарядке пистоля -->
// Ugeen --> переработка с учётом нескольких типов пуль и пороха на одетом огнестреле
int iGetMinPistolChargeNum(ref rChar, string sType) // Чего меньше, пороха или пуль?
{
	string sBulletType = LAi_GetCharacterBulletType(rChar, sType);	 			// узнаем тип пуль
	int iBulletQty = GetCharacterItem(rChar, sBulletType);   					// считаем кол-во пуль
	string sGunPowderType = LAi_GetCharacterGunpowderType(rChar, sType); 		// тип пороха
	if(sGunPowderType != "")
	{
		int iGunPowderQty = GetCharacterItem(rChar, sGunPowderType); 			// кол-во пороха		
		int iChargeQty = func_min(iBulletQty, iGunPowderQty); 					// Узнаем, чего меньше
		return iChargeQty;
	}		
	return iBulletQty;
}

int iGetPistolChargeNum(ref rChar, string sType, int iQuant) // Скока можем зарядить
{
	int iChargeQty = iGetMinPistolChargeNum(rChar, sType);

	if(iChargeQty == 0) return 0;
	if(iChargeQty >= iQuant) return iQuant;
	if(iChargeQty < iQuant) return iChargeQty;
}
// <-- Методы по зарядке огнестрельного оружия

//Разрядить оружие
void LAi_GunSetUnload(aref chr, string sType)
{
	chr.chr_ai.(sType).charge = "0";
	chr.chr_ai.(sType).chargeprc = "1";
}

//Установить скорость заряда оружия
void LAi_GunSetChargeSpeed(aref chr, string sType, float speed)
{
	if(speed < 0.0) speed = 0.0;
	if(speed > 4.0) speed = 4.0;
	chr.chr_ai.(sType).charge_dlt = speed;
}

//Установить минимальный урон от оружия
void LAi_GunSetDamageMin(aref chr, string sType, float min)
{
	chr.chr_ai.(sType).dmggunmin = min;
}

//Установить максимальный урон от оружия
void LAi_GunSetDamageMax(aref chr, string sType, float max)
{
	chr.chr_ai.(sType).dmggunmax = max;
}

//Установить вероятность попадания на максимальной дальности стрельбы
void LAi_GunSetAccuracy(aref chr, string sType, float accuracy)
{
	if(accuracy < 0.0) accuracy = 0.0;
	if(accuracy > 1.0) accuracy = 1.0;
	chr.chr_ai.(sType).accuracy = accuracy;
}

//Установить минимальный урон от сабли
void LAi_BladeSetDamageMin(aref chr, float min)
{
	chr.chr_ai.dmgbldmin = min;
}

//Установить максимальный урон от сабли
void LAi_BladeSetDamageMax(aref chr, float max)
{
	chr.chr_ai.dmgbldmax = max;
}

//Установить вероятность пробивки
void LAi_BladeSetPiercing(aref chr, float piercing)
{
	if(piercing < 0.0) piercing = 0.0;
	if(piercing > 1.0) piercing = 1.0;
	chr.chr_ai.piercing = piercing;
}

//Установить вероятность неблокирования
void LAi_BladeSetBlock(aref chr, float block)
{
	if(block < 0.0) block = 0.0;
	if(block > 1.0) block = 1.0;
	chr.chr_ai.block = block;
}
// тип сабли boal
void LAi_BladeFencingType(aref chr, string FencingType)
{
	chr.chr_ai.FencingType = FencingType;
}

string LAi_GetBladeFencingType(aref chr)
{
    if(CheckAttribute(chr, "chr_ai.FencingType"))
	{
        return chr.chr_ai.FencingType;
    }
    return SKILL_FENCING;
}

// тип мушкета
void LAi_MushketFencingType(aref chr, string FencingType)
{
	chr.chr_ai.MushketFencingType = FencingType;
}

string LAi_GetMushketFencingType(aref chr)
{
    if(CheckAttribute(chr, "chr_ai.MushketFencingType"))
	{
        return chr.chr_ai.MushketFencingType;
    }
    return SKILL_FENCING;
}

void LAi_SetBladeEnergyType(aref chr, float fEnergyType)
{
	chr.chr_ai.BladeEnergyType = fEnergyType;
}

float LAi_GetBladeEnergyType(aref chr)
{
    if (CheckAttribute(chr, "chr_ai.BladeEnergyType"))
	{
        return stf(chr.chr_ai.BladeEnergyType);
    }
    return 1.0;
}

void LAi_SetMushketEnergyType(aref chr, float fEnergyType)
{
	chr.chr_ai.MushketEnergyType = fEnergyType;
}

float LAi_GetMushketEnergyType(aref chr)
{
    if (CheckAttribute(chr, "chr_ai.MushketEnergyType"))
	{
        return stf(chr.chr_ai.MushketEnergyType);
    }
    return 1.0;
}


//------------------------------------------------------------------------------------------
//Internal
//------------------------------------------------------------------------------------------

float SprintEnergyCost = 3.0;

//Процессируем всех загруженных персонажей
void LAi_AllCharactersUpdate(float dltTime)
{
	for(int i = 0; i < LAi_numloginedcharacters; i++)
	{
		int idx = LAi_loginedcharacters[i];
		if(idx >= 0)
		{
			//Персонаж
			aref chr_ai;
			makearef(chr_ai, Characters[idx].chr_ai);
			ref chr = &Characters[idx];
			if(LAi_IsDead(chr)) continue;
			//Востоновление жизни
			float dlthp = LAI_DEFAULT_DLTHP;
			if(CheckAttribute(chr_ai, "hp_dlt")) dlthp = stf(chr_ai.hp_dlt);
			if(idx == GetMainCharacterIndex() && CheckAttribute(chr, "cheats.hpupdate")) dlthp *= 10.0;
			float hp = stf(chr_ai.hp) + dlthp*dltTime;
			float oldhp = hp;
			if(CheckAttribute(chr_ai, "hp_bottle"))
			{
				float bottle = stf(chr_ai.hp_bottle);
				if(bottle > 0)
				{
					//Скорость высасывания из бутылки
					float bottledlthp = LAI_DEFAULT_DLTBLTHP;
					if(CheckAttribute(chr_ai, "hp_dlt_bottle"))
					{
						bottledlthp = stf(chr_ai.hp_dlt_bottle);
					}
					//Количество вытянутых хп за текущий период времени
					bottledlthp = bottledlthp*dltTime;				
					if(bottledlthp > bottle)
					{
						bottledlthp = bottle;
					}
					bottle = bottle - bottledlthp;
					hp = hp + bottledlthp;
					chr_ai.hp_bottle = bottle;
				}else{
					//Нет больше бутылки
					DeleteAttribute(chr_ai, "hp_bottle");
					DeleteAttribute(chr_ai, "hp_dlt_bottle");//fix
					if(idx==GetMainCharacterIndex())
					DeleteAttribute(chr, "chr_ai.usedbottlemax");
					
				}
			}
			if(CheckAttribute(chr_ai, "poison"))
			{
				chr_ai.poison = stf(chr_ai.poison) - dltTime;
				if(stf(chr_ai.poison) <= 0.0)
				{
					DeleteAttribute(chr_ai, "poison");
				}else{
					hp = hp - dltTime*2.0;
					if (!CheckAttribute(chr, "poison.hp") || hp < sti(chr.poison.hp)-1.0)
					{
						chr.poison.hp = hp;
						if(bDrawBars) SendMessage(chr, "lfff", MSG_CHARACTER_VIEWDAMAGE, hp, MakeFloat(MakeInt(chr.chr_ai.hp)), MakeFloat(MakeInt(chr.chr_ai.hp_max)));
					}
				}
			}
			//navy --> время действия бутылки
			if(CheckAttribute(chr_ai, "drunk"))
			{
				chr_ai.drunk = sti(chr_ai.drunk) - 1;
				if(sti(chr_ai.drunk) < 1) LAi_SetAlcoholNormal(chr);
			}
			//<--
			if(LAi_IsImmortal(chr))
			{
				if(hp < oldhp) hp = oldhp;
			}
			float maxhp = stf(chr_ai.hp_max);
			if(hp > maxhp)
			{
				hp = maxhp;
				DeleteAttribute(chr_ai, "bottle");
			}
			chr_ai.hp = hp;
			//Проверка квеста на hp
			LAi_ProcessCheckMinHP(chr);
			//Проверка на смерть
			LAi_CheckKillCharacter(chr);
			
			//--> Восстановление зарядов огнестрельного оружия
			float charge, dltcharge;
			float ChargeMax = 0.0;
			bool bMus = IsMusketer(chr);
			bool bPeace = !LAi_IsFightMode(chr);
			bool bAiming = false;
			if(idx == GetMainCharacterIndex())
			{
				string sAimingStep;
				SendMessage(pchar, "lse", MSG_CHARACTER_EX_MSG, "GetAimingStep", &sAimingStep);
				if(sAimingStep != "none")
					bAiming = true;
				if(CheckAttribute(chr_ai, "kill_timer"))
				{
					float killTimer = stf(chr_ai.kill_timer);
					killTimer -= dltTime;
					if(killTimer <= 0.0)
						DeleteAttribute(chr_ai, "kill_timer");
					else
						chr_ai.kill_timer = killTimer;
				}
			}
			
			if(CheckAttribute(chr_ai, "getheadshot"))
			{
				float headshotCD = stf(chr_ai.getheadshot);
				headshotCD -= dltTime;
				if(headshotCD <= 0.0)
					DeleteAttribute(chr_ai, "getheadshot");
				else
					chr_ai.getheadshot = headshotCD;
			}
			
			//Для пистолета
			if(!bAiming)
			{
				if (bRechargePistolOnLine || bPeace)
				{
					if(CheckAttribute(chr_ai, "gun.charge_max")) ChargeMax = stf(chr_ai.gun.charge_max);
					if(ChargeMax > 0.0)
					{
						if(sti(chr_ai.gun.chargeprc))
						{
							charge = stf(chr_ai.gun.charge);
							if((iGetMinPistolChargeNum(chr, "gun") - charge) > 0)
							{
								if(!CheckAttribute(chr_ai, "gun.charge_pSkill"))
								{	//Скорость зарядки
									chr_ai.gun.charge_pSkill = LAi_GunReloadSpeed(chr, "gun");
								}

								dltcharge = stf(chr_ai.gun.charge_pSkill);

								//Подзаряжаем пистолет
								charge = charge + dltcharge*dltTime;
								if(charge >= ChargeMax)
								{
									charge = ChargeMax;
									chr_ai.gun.chargeprc = "0";
									DeleteAttribute(chr_ai, "gun.charge_pSkill");

									// boal 24.04.04 озвучка зарядки пистоля -->
									if (Characters[idx].index == GetMainCharacterIndex() && LAi_IsFightMode(pchar))
									{
										PlaySound("People Fight\reload1.wav");
									}
								}
								chr_ai.gun.charge = charge;
							}
						}
					}
					else chr_ai.gun.charge = "0";
				}
				
				//Для мушкета в мирном режиме без тревоги и/или если его держат в руках
				if(bMus) //НО НЕ В САБЕЛЬНОМ
				{
					ChargeMax = 0.0;
					if(CheckAttribute(chr_ai, "musket.charge_max")) ChargeMax = stf(chr_ai.musket.charge_max);
					if(ChargeMax > 0.0)
					{
						if(sti(chr_ai.musket.chargeprc))
						{
							charge = stf(chr_ai.musket.charge);
							if((iGetMinPistolChargeNum(chr, "musket") - charge) > 0)
							{
								if(!CheckAttribute(chr_ai, "musket.charge_pSkill"))
								{	//Скорость зарядки
									chr_ai.musket.charge_pSkill = LAi_GunReloadSpeed(chr, "musket");
								}

								dltcharge = stf(chr_ai.musket.charge_pSkill);

								//Подзаряжаем мушкет
								charge = charge + dltcharge*dltTime;
								if(charge >= ChargeMax)
								{
									charge = ChargeMax;
									chr_ai.musket.chargeprc = "0";
									DeleteAttribute(chr_ai, "musket.charge_pSkill");

									// boal 24.04.04 озвучка зарядки пистоля -->
									if (Characters[idx].index == GetMainCharacterIndex() && LAi_IsFightMode(pchar))
									{
										PlaySound("People Fight\reload1.wav");
									}
								}
								chr_ai.musket.charge = charge;
							}
						}
					}
					else chr_ai.musket.charge = "0";
				}
			}
			//<-- Восстановление зарядов огнестрельного оружия
			
			//Востановление энергии
			if(CheckAttribute(chr_ai, "energy"))
			{
				float energy = stf(chr_ai.energy);
				if(idx == GetMainCharacterIndex() && SendMessage(pchar, "ls", MSG_CHARACTER_EX_MSG, "IsSprint") == 1 && LAi_group_IsActivePlayerAlarm())
				{
					energy -= dltTime * SprintEnergyCost;
					if(energy < 0.0)
						SendMessage(pchar, "ls", MSG_CHARACTER_EX_MSG, "StopSprint");
				}
				else
					energy = Lai_UpdateEnergyPerDltTime(chr, stf(chr_ai.energy), dltTime);
				if(energy < 0.0)
					energy = 0.0;
				if(energy > LAi_GetCharacterMaxEnergy(chr))   // boal
					energy = LAi_GetCharacterMaxEnergy(chr);
				chr_ai.energy = energy;
			}
		}
	}
}

void LAi_ProcessCheckMinHP(aref chr)
{
	if(CheckAttribute(chr, "chr_ai.hpchecker"))
	{
		float minhp = stf(chr.chr_ai.hpchecker);
		float hp = stf(chr.chr_ai.hp);
		if(hp < minhp)
		{
			if(sti(chr.chr_ai.hpchecker.immortal))
			{
				LAi_SetImmortal(chr, true);
				chr.chr_ai.hp = minhp;
			}
			if(chr.chr_ai.hpchecker.quest != "")
			{
				LAi_QuestDelay(chr.chr_ai.hpchecker.quest, 0.0);
			}
			LAi_RemoveCheckMinHP(chr);
		}
	}
}

void LAi_CharacterSaveAy(aref chr)
{
	float ay = 0.0;
	if(GetCharacterAy(chr, &ay) == false) ay = 0.0;
	chr.chr_ai.type.ay = ay;	
}

void LAi_CharacterRestoreAy(aref chr)
{
	if(CheckAttribute(chr, "chr_ai.type.ay"))
	{
		float ay = stf(chr.chr_ai.type.ay);
		aref type;
		makearef(type, chr.chr_ai.type);
		DeleteAttribute(type, "ay");
		CharacterTurnAy(chr, ay);
	}
}

string GetSkillNameByIdx(int idx)
{
	string ret = "";
	switch (idx)
	{
		case 1:    ret = SKILL_F_LIGHT;   break;
		case 2:    ret = SKILL_FENCING;   break;
		case 3:    ret = SKILL_F_HEAVY;   break;
		case 4:    ret = SKILL_PISTOL;    break;
		case 5:    ret = SKILL_FORTUNE;   break;

		case 6:    ret = SKILL_LEADERSHIP; break;
		case 7:    ret = SKILL_COMMERCE;   break;
		case 8:    ret = SKILL_ACCURACY;   break;
		case 9:    ret = SKILL_CANNONS;    break;
		case 10:   ret = SKILL_SAILING;    break;
		case 11:   ret = SKILL_REPAIR;     break;
		case 12:   ret = SKILL_GRAPPLING;  break;
		case 13:   ret = SKILL_DEFENCE;    break;
		case 14:   ret = SKILL_SNEAK;      break;

		case 15:   ret = SPECIAL_S;   break;
		case 16:   ret = SPECIAL_P;   break;
		case 17:   ret = SPECIAL_A;   break;
		case 18:   ret = SPECIAL_C;   break;
		case 19:   ret = SPECIAL_I;   break;
		case 20:   ret = SPECIAL_E;   break;
		case 21:   ret = SPECIAL_L;   break;
	}
	return ret;
}


string GetSkillNameByTRIdx(string _type, int idx)
{
	string ret = "";

	switch (_type)
	{
		case "SelfType":
		switch (idx)
			{
				case 1:    ret = SKILL_LEADERSHIP; break;
				case 2:    ret = SKILL_F_LIGHT;   break;
				case 3:    ret = SKILL_FENCING;   break;
				case 4:    ret = SKILL_F_HEAVY;   break;
				case 5:    ret = SKILL_PISTOL;    break;
				case 6:    ret = SKILL_FORTUNE;   break;
				case 7:    ret = SKILL_SNEAK;      break;
			}
		break;

		case "ShipType" :
		switch (idx)
			{
				case 1:    ret = SKILL_SAILING; break;
				case 2:    ret = SKILL_ACCURACY;   break;
				case 3:    ret = SKILL_CANNONS;   break;
				case 4:    ret = SKILL_GRAPPLING;   break;
				case 5:    ret = SKILL_DEFENCE;    break;
				case 6:    ret = SKILL_REPAIR;   break;
				case 7:    ret = SKILL_COMMERCE;      break;
			}
		break;

		case "SPECIALType":
		switch (idx)
		{
			case 1:   ret = SPECIAL_S;   break;
			case 2:   ret = SPECIAL_P;   break;
			case 3:   ret = SPECIAL_A;   break;
			case 4:   ret = SPECIAL_C;   break;
			case 5:   ret = SPECIAL_I;   break;
			case 6:   ret = SPECIAL_E;   break;
			case 7:   ret = SPECIAL_L;   break;
		}
		break;
	}
	return ret;
}

bool isShipTypeSkill(string _param)
{
	return CheckAttribute(&NullCharacter, "ShipType." + _param);
}

bool isSelfTypeSkill(string _param)
{
	return CheckAttribute(&NullCharacter, "SelfType." + _param);
}

bool isSPECIALTypeSkill(string _param)
{
	return CheckAttribute(&NullCharacter, "SPECIALType." + _param);
}

// нужно не перекрывать ещё и признаки фантома
void ChangeAttributesFromCharacter(ref CopyChref, ref PastChref, bool _dialogCopy)
{
    aref arToChar;
    aref arFromChar;

    CopyChref.model            = PastChref.model;
    CopyChref.model.animation  = PastChref.model.animation;
    CopyChref.sex              = CopyChref.sex;
    CopyChref.headModel        = PastChref.headModel;
    CopyChref.FaceId           = PastChref.FaceId;
    CopyChref.nation           = PastChref.nation;

	CopyChref.name             = PastChref.name;
    CopyChref.lastname         = PastChref.lastname;

    CopyChref.rank             = PastChref.rank;
    CopyChref.reputation       = makeint(PastChref.reputation);
	
	CopyChref.baseCapIdx       = PastChref.index; //Id оригинального в структуру клона

    if (CheckAttribute(PastChref, "loyality"))
    {
    	CopyChref.loyality         = PastChref.loyality;
	}
	else DeleteAttribute(CopyChref, "loyality");
	if (CheckAttribute(PastChref, "alignment"))
	{
    	CopyChref.alignment        = PastChref.alignment;
    }
    else DeleteAttribute(CopyChref, "alignment");

    CopyChref.Money            = PastChref.Money;

    CopyChref.chr_ai.hp         = makeint(PastChref.chr_ai.hp);
    CopyChref.chr.chr_ai.hp_max = makeint(PastChref.chr_ai.hp_max);

    LAi_SetHP(CopyChref, makeint(PastChref.chr_ai.hp_max), makeint(PastChref.chr_ai.hp_max));
	LAi_SetCurHPMax(CopyChref);
	
	//копируем структуру quest от оригинального кэпа, очень нужно по квестам :)
	if (CheckAttribute(PastChref, "quest"))
    {
	    aref arToCharQuest, arFromCharQuest;
		makearef(arFromCharQuest, PastChref.quest);
		makearef(arToCharQuest, CopyChref.quest);
		DeleteAttribute(arToCharQuest, "");
		CopyAttributes(arToCharQuest, arFromCharQuest);
	}
	
	if (CheckAttribute(PastChref, "quest.officertype"))
    {
        CopyChref.quest.officertype     =   PastChref.quest.officertype;
    }
    else
    {
        DeleteAttribute(CopyChref, "quest.officertype");
    }

    if (CheckAttribute(PastChref, "Payment"))
    {
        CopyChref.Payment     =   PastChref.Payment; // платить ЗП
    }
    else
    {
        DeleteAttribute(CopyChref, "Payment");
    }
    if (CheckAttribute(PastChref, "HoldEquip"))
    {
        CopyChref.HoldEquip   =   PastChref.HoldEquip; // не отдавать саблю и пистоль
    }
	else
    {
        DeleteAttribute(CopyChref, "HoldEquip");
    }
    if (CheckAttribute(PastChref, "SaveItemsForDead"))
    {
        CopyChref.SaveItemsForDead   =   true;
    }
	else
    {
        DeleteAttribute(CopyChref, "SaveItemsForDead");
    }
    if (CheckAttribute(PastChref, "DontClearDead"))
    {
        CopyChref.DontClearDead   =   true;
    }
	else
    {
        DeleteAttribute(CopyChref, "DontClearDead");
    }
    if (CheckAttribute(PastChref, "OfficerWantToGo.DontGo"))
    {
        CopyChref.OfficerWantToGo.DontGo   =   true;
    }
	else
    {
        DeleteAttribute(CopyChref, "OfficerWantToGo.DontGo");
    }
    // skill
    DeleteAttribute(CopyChref, "skill");
    CopyChref.skill = "";

    makearef(arToChar, CopyChref.skill);
    makearef(arFromChar, PastChref.skill);

    CopyAttributes(arToChar,arFromChar);

    // SPECIAL
    DeleteAttribute(CopyChref, "SPECIAL");
    CopyChref.SPECIAL = "";

    makearef(arToChar, CopyChref.SPECIAL);
    makearef(arFromChar, PastChref.SPECIAL);

    CopyAttributes(arToChar,arFromChar);

    // Statistic
    DeleteAttribute(CopyChref, "Statistic");
    CopyChref.Statistic = "";

    makearef(arToChar, CopyChref.Statistic);
    makearef(arFromChar, PastChref.Statistic);

    CopyAttributes(arToChar,arFromChar);

    // perks
    DeleteAttribute(CopyChref, "perks");
    CopyChref.perks = "";

    makearef(arToChar, CopyChref.perks);
    makearef(arFromChar, PastChref.perks);

    CopyAttributes(arToChar,arFromChar);
    // items
    DeleteAttribute(CopyChref, "Items");
    CopyChref.Items = "";

    makearef(arToChar, CopyChref.Items);
    makearef(arFromChar, PastChref.Items);

    CopyAttributes(arToChar,arFromChar);
	
	// equipped items
	DeleteAttribute(CopyChref, "equip_item");
	CopyChref.equip_item = "";
	makearef(arToChar, CopyChref.equip_item);
    makearef(arFromChar, PastChref.equip_item);

    CopyAttributes(arToChar,arFromChar);
	

    if (CheckAttribute(PastChref, "equip.blade"))
    {
		CopyChref.equip.blade =   PastChref.equip.blade;
	}
	if (CheckAttribute(PastChref, "equip.gun"))
    {
		CopyChref.equip.gun   =   PastChref.equip.gun;
	}
	if (CheckAttribute(PastChref, "equip.musket"))
    {
		CopyChref.equip.musket =   PastChref.equip.musket;
	}
	if (CheckAttribute(PastChref, "CanTakeMushket"))
    {
		CopyChref.CanTakeMushket = PastChref.CanTakeMushket;
	}
	if (CheckAttribute(PastChref, "PriorityMode"))
    {
		CopyChref.PriorityMode = sti(PastChref.PriorityMode);
	}
	if (CheckAttribute(PastChref, "MusketerDistance"))
    {
		CopyChref.MusketerDistance = sti(PastChref.MusketerDistance);
	}
	// belamour legendary edition зарядим огнестрел 
	if (CheckAttribute(PastChref, "chr_ai.gun.bullet"))
	{
		LAi_SetCharacterUseBullet(CopyChref, GUN_ITEM_TYPE, PastChref.chr_ai.gun.bullet); 
	}
	if (CheckAttribute(PastChref, "chr_ai.musket.bullet"))
	{
		LAi_SetCharacterUseBullet(CopyChref, MUSKET_ITEM_TYPE, PastChref.chr_ai.musket.bullet); 
	}
	// health
	if (CheckAttribute(PastChref, "Health.TotalDamg"))
    {
		CopyChref.Health.TotalDamg =   PastChref.Health.TotalDamg;
	}
	else
	{
        CopyChref.Health.TotalDamg = 0;
	}
	
	if (CheckAttribute(PastChref, "PerkValue.EnergyPlus"))
	{
		CopyChref.PerkValue.EnergyPlus =   PastChref.PerkValue.EnergyPlus;
	}
	
	if (CheckAttribute(PastChref,"bonusEnergy"))
	{
		CopyChref.bonusEnergy = PastChref.bonusEnergy;
	}

	// ugeen --> нужно для генерации различных ситуации в каюте абордированного кэпа
	if (CheckAttribute(PastChref,"Situation")) // если в каюте кэпа возникла ситуация 
	{
		CopyChref.Situation = PastChref.Situation;
		CopyChref.Situation.type = PastChref.Situation.type;
	}
	
	if (CheckAttribute(PastChref,"EncType"))
	{
		CopyChref.EncType = PastChref.EncType;
	}
	
	if (CheckAttribute(PastChref,"RealEncounterType"))
	{
		CopyChref.RealEncounterType = PastChref.RealEncounterType;
	}

	if (CheckAttribute(PastChref,"Ship"))
	{
		makearef(arToChar, CopyChref.Back.Ship);
		makearef(arFromChar, PastChref.Ship);
		CopyAttributes(arToChar, arFromChar);		
	}	
	// <-- ugeen
	
	if (_dialogCopy && CheckAttribute(PastChref, "Dialog.Filename"))
	{
	    CopyChref.Dialog.Filename    = PastChref.Dialog.Filename;
	    CopyChref.Dialog.CurrentNode = PastChref.Dialog.CurrentNode;
	    if (CheckAttribute(PastChref, "greeting")) CopyChref.greeting = PastChref.greeting; //eddy.нет логам!
		else
		{
			DeleteAttribute(CopyChref, "greeting");
		}
	}

	if (CheckAttribute(PastChref,"сt"))
	{
		makearef(arToChar, CopyChref.сt);
		makearef(arFromChar, PastChref.сt);
		CopyAttributes(arToChar, arFromChar);
	}

	if (CheckAttribute(PastChref,"personality"))
	{
		makearef(arToChar, CopyChref.personality);
		makearef(arFromChar, PastChref.personality);
		CopyAttributes(arToChar, arFromChar);
	}

	SetEnergyToCharacter(CopyChref);
	//SetNewModelToChar(CopyChref);  // чтоб сабли были правильные
}

string GetRPGText(string _param)
{
    int    idLngFile = -1;
    string totalInfo;

    idLngFile = LanguageOpenFile("RPGDescribe.txt");
    totalInfo = LanguageConvertString(idLngFile, _param);
    LanguageCloseFile(idLngFile);

    return totalInfo;
}

// В будущем должно быть в кеш-таблице для глобалки, пока что просто берем из предметов
float GetSquadronPowerMtp(ref chr)
{
	aref table = CT_GetTable(chr, CT_EQUIP);
	return GetAttributeFloat(table, M_SQUADRON_POWER);
}

// Число = число * (Пиратес 1 * множитель + Пиратес 2 * множитель)
// JOKERTODO: добавить в метод выбор типа пиратес, сейчас тут с эффектами, кроме навигации
void NormalizeByPirates(ref value, ref chr, string pirA, string pirB, int mtpA, int mtpB)
{
	value *= (mtpA * GetSpecialWithEffects(chr, pirA) + mtpB * GetSpecialWithEffects(chr, pirB));
	value *= 0.01;
}
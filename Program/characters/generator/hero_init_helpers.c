 // RB Квестовые офицеры
ref InitHugo(string name, string lastname)
{
	ref sld = GetCharacter(NPC_GenerateCharacter("Avendel", "Hugh", "man", "man", 10, HOLLAND, -1, true, "quest"));
	SetHeroAutolevel(sld);
	FantomMakeCoolFighter(sld, 20, 50, 50, "blade_04", "pistol1", "bullet", 50);
	sld.name = name;
	sld.lastname = lastname;
	sld.dialog.FileName = "Quest\Portugal_dialog.c";
	sld.dialog.currentnode = "Avendel_tavern";
	sld.greeting = "avendel_1";
	sld.rank = 12;
	LAi_SetHP(sld, 80, 80);
	SetSelfSkill(sld, 10, 12, 10, 10, 70);
	SetShipSkill(sld, 50, 75, 15, 15, 25, 55, 10, 15, 30);
	SetSPECIAL(sld, 3, 8, 3, 10, 10, 3, 6);
	SetCharacterPerk(sld, "BasicCommerce");
	SetCharacterPerk(sld, "AdvancedCommerce");
	SetCharacterPerk(sld, "BasicBattleState");
	SetCharacterPerk(sld, "AdvancedBattleState");
	SetCharacterPerk(sld, "BasicDefense");
	SetCharacterPerk(sld, "Gunman");
	GiveItem2Character(sld, "blade_12");
	sld.equip.blade = "blade_12";
	GiveItem2Character(sld, "pistol1");
	EquipCharacterbyItem(sld, "pistol1");
	TakeNItems(sld, "bullet", 10);
	AddItems(sld, "gunpowder", 10);
	LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "bullet");
	LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
	LAi_SetImmortal(sld, true);
	LAi_SetSitType(sld);
	return sld;
}

ref InitTichingitu()
{
	ref sld = GetCharacter(NPC_GenerateCharacter("Tichingitu", "maskog", "man", "man", 1, FRANCE, 10, false, "quest"));
	sld.name = StringFromKey("SharlieTrial_27"); // 270912
	sld.lastname = StringFromKey("SharlieTrial_28");
	sld.greeting = "Tichingitu";
	sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
	sld.dialog.currentnode = "Tichingitu";
	sld.rank = 12;
	SetSPECIAL(sld, 4, 9, 5, 5, 10, 8, 8);
	GiveItem2Character(sld, "unarmed");
	sld.equip.blade = "unarmed";
	sld.equip.gun = "";
	LAi_SetImmortal(sld, true); // 170712
	return sld;
}

ref InitKnippel()
{
	ref sld = GetCharacter(NPC_GenerateCharacter("Knippel", "Kneepel", "man", "man_B", 20, ENGLAND, -1, false, "quest"));
	SetHeroAutolevel(sld);
	sld.name = StringFromKey("QuestsUtilite_36");
	sld.lastname = StringFromKey("QuestsUtilite_37");
	sld.greeting = "knippel_1";
	sld.CompanionDisable = true;
	sld.rank = 20;
	LAi_SetHP(sld, 120, 120);
	SetSelfSkill(sld, 10, 12, 10, 10, 70);
	SetShipSkill(sld, 50, 20, 75, 75, 45, 20, 20, 10, 15);
	SetSPECIAL(sld, 9, 10, 6, 5, 5, 5, 9);
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "LongRangeShoot");
	SetCharacterPerk(sld, "CannonProfessional");
	SetCharacterPerk(sld, "FastReload");
	sld.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
	sld.dialog.currentnode = "First time";
	GiveItem2Character(sld, "blade_12");
	sld.equip.blade = "blade_12";
	GiveItem2Character(sld, "pistol1");
	EquipCharacterbyItem(sld, "pistol1");
	TakeNItems(sld, "bullet", 50);
	AddItems(sld, "gunpowder", 50);
	TakeNItems(sld,"potion2", 3);
	sld.money = 1000;
	LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "bullet");
	return sld;
}

ref initLongway()
{
	ref sld = GetCharacter(NPC_GenerateCharacter("Longway", "Longway", "man", "Longway", 20, HOLLAND, -1, false, "quest"));
	SetHeroAutolevel(sld);
	sld.name = StringFromKey("QuestsUtilite_42");
	sld.lastname = StringFromKey("QuestsUtilite_43");
	sld.greeting = "Longway";
	sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
	sld.dialog.currentnode = "First time";
	sld.CompanionDisable = true;
	sld.rank = 20;
	sld.money = 5000;
	SetSelfSkill(sld, 45, 45, 45, 40, 50);
	SetShipSkill(sld, 50, 20, 25, 25, 65, 20, 20, 50, 15);
	SetSPECIAL(sld, 8, 9, 6, 5, 10, 7, 5);
	LAi_SetHP(sld, 250, 250);
	SetCharacterPerk(sld, "Energaiser");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "ShipSpeedUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "StormProfessional");
	SetCharacterPerk(sld, "WindCatcher");
	SetCharacterPerk(sld, "SailsMan");
	SetCharacterPerk(sld, "SailingProfessional");
	GiveItem2Character(sld, "blade_08");
	sld.equip.blade = "blade_08";
	GiveItem2Character(sld, "pistol3");
	EquipCharacterbyItem(sld, "pistol3");
	LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "grapeshot");
	TakeNItems(sld, "grapeshot", 50);
	AddItems(sld, "gunpowder", 50);
	TakeNItems(sld, "potion2", 1);
	return sld;
}

ref InitTommy()
{
	ref sld = GetCharacter(NPC_GenerateCharacter("Irons", "Irons", "man", "Irons", 12, ENGLAND, -1, false, "quest"));
	SetHeroAutolevel(sld);
	sld.name = StringFromKey("BlackMark_5");
	sld.lastname = StringFromKey("BlackMark_6");
	sld.rank = 12;
	sld.CanTakeMushket = true;
	sld.PriorityMode = 2;
	sld.MusketerDistance = 10;
	SetSPECIAL(sld, 6, 9, 6, 3, 7, 6, 9);
	SetSelfSkill(sld, 15, 15, 50, 60, 20);
	SetShipSkill(sld, 5, 1, 4, 6, 1, 1, 7, 1, 10);
	SetCharacterPerk(sld, "Energaiser");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "BasicDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Gunman");
	SetCharacterPerk(sld, "Sniper"); //Снайпер
	GiveItem2Character(sld, "cirass10");
	EquipCharacterByItem(sld, "cirass10");
	GiveItem2Character(sld, "blade_42");
	EquipCharacterByItem(sld, "blade_42");
	GiveItem2Character(sld, "indian_2");
	GiveItem2Character(sld, "mushket1");
	EquipCharacterByItem(sld, "mushket1");
	AddItems(sld, "potionrum", 5);
	AddItems(sld, "GunPowder", 15);
	AddItems(sld, "bullet", 15);
	LAi_SetCharacterUseBullet(sld, MUSKET_ITEM_TYPE, "bullet");
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	return sld;
}

// Первый раз автолевелится как босс, автолевелится как герой при взятии в команду
ref initDuran()
{
	ref sld = GetCharacter(NPC_GenerateCharacter("Duran", "Claude_Durand", "man", "man", 1, FRANCE, -1, false, "soldier"));
	sld.name = StringFromKey("FMQ_49");
	sld.lastname = StringFromKey("FMQ_50");
	sld.Dialog.Filename = "Quest\LineMiniQuests\FMQ_Tortuga.c";
	sld.Dialog.currentnode = "mercen";
	sld.SpecialRole = "mercen";
	sld.rank = 15;
	sld.reputation = 25;
	sld.alignment = "bad";
	SetSPECIAL(sld, 8, 5, 8, 4, 6, 8, 5);
	return sld;
}


ref InitTonzag()
{
	ref sld = GetCharacter(NPC_GenerateCharacter("Tonzag", "Tonzag", "man", "man", 30, ENGLAND, -1, false, "quest"));
	sld.name = StringFromKey("QuestsUtilite_46");
	sld.lastname = StringFromKey("QuestsUtilite_47");
	sld.greeting = "tonzag_2";
	sld.Dialog.Filename = "Quest\HollandGambit\Tonzag.c";
	sld.dialog.currentnode = "First time";
	sld.rank = 30;
	LAi_SetHP(sld, 250, 250);
	sld.money = 5000;
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	SetSelfSkill(sld, 60, 60, 65, 60, 50);
	SetShipSkill(sld, 50, 20, 20, 20, 20, 20, 70, 20, 70);
	SetSPECIAL(sld, 10, 3, 10, 3, 6, 10, 8);
	SetCharacterPerk(sld, "Energaiser");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "BladeDancer");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "Gunman");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "GrapplingProfessional");
	SetCharacterPerk(sld, "MusketsShoot");
	GiveItem2Character(sld, "blade_07");
	sld.equip.blade = "blade_07";
	GiveItem2Character(sld, "pistol3");
	EquipCharacterbyItem(sld, "pistol3");
	LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "grapeshot");
	TakeNItems(sld, "grapeshot", 50);
	AddItems(sld, "gunpowder", 50);
	TakeNItems(sld, "potion2", 2);
	return sld;
}

ref InitLongwayFP(string id, ref NPChar)
{
	ref sld = GetCharacter(NPC_GenerateCharacter(id, "Longway", "man", "Longway", 20, HOLLAND, -1, false, "quest"));
	sld.name = StringFromKey("QuestsUtilite_42");
	sld.lastname = StringFromKey("QuestsUtilite_43");
	sld.greeting = "Longway";
	sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
	sld.Dialog.currentnode = "Longway_officer";
	sld.rank = 20;
	sld.money = 5000;
	SetSPECIAL(sld, 8, 9, 6, 5, 10, 7, 5);
	string sTemp = GetGeneratedItem("blade_41");
	GiveItem2Character(sld, sTemp);
	EquipCharacterbyItem(sld, sTemp);
	sTemp = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
	if(sTemp != "")
	{
			GiveItem2Character(sld,   sTemp);
			EquipCharacterbyItem(sld, sTemp);
			sTemp = LAi_GetCharacterBulletType(NPChar, GUN_ITEM_TYPE);
			LAi_SetCharacterBulletType(sld, sTemp);
			LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, sTemp);
			sTemp = LAi_GetCharacterGunpowderType(NPChar, GUN_ITEM_TYPE);
			if(sTemp != "") AddItems(sld, sTemp, 30 + rand(20));
	}
	TakeNItems(sld, "potion2", 1);
	sld.quest.meeting = true;
	sld.quest.OfficerPrice = sti(pchar.rank)*200;
	sld.OfficerWantToGo.DontGo = true;
	sld.loyality = MAX_LOYALITY;
	sld.OfficerImmortal = true;
	sld.CanTakeMushket = true;
	ForceHeroAutolevel(sld);
	AddPassenger(pchar, sld, false);
	SetCharacterRemovable(sld, true);
	sld.Payment = true;
	return sld;
}

ref InitFolke(string name, string lastname)
{
	ref sld = GetCharacter(NPC_GenerateCharacter("Folke", "DeLuck", "man", "man", 1, FRANCE, -1, false, "quest"));
	SetHeroAutolevel(sld);
	sld.name = name;
	sld.lastname = lastname;
	sld.greeting = "officer_hire";
	sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
	sld.dialog.currentnode = "Folke";
	LAi_SetImmortal(sld, true);
	sld.CompanionDisable = true;
	sld.rank = 5;
	LAi_SetHP(sld, 90, 90);
	sld.money = 0;
	SetSelfSkill(sld, 25, 28, 21, 24, 22);
	SetShipSkill(sld, 10, 5, 24, 22, 30, 15, 5, 15, 18);
	SetSPECIAL(sld, 8, 9, 6, 5, 10, 7, 5);
	SetCharacterPerk(sld, "ShipSpeedUp");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "BasicDefense");
	GiveItem2Character(sld, "unarmed");
	EquipCharacterbyItem(sld, "unarmed");
	return sld;
}

// RB Квестовые офицеры
bool SetHeroAutolevel(ref chr)
{
	switch (chr.id)
	{
		case "Duran":        return SetAdaptivelevel(chr, 8, GEN_TYPE_OFFICER, GEN_MINIBOSS, GEN_ARCHETYPE_PIRATE, GEN_ARCHETYPE_FREE, GEN_FIXED_PIRATES, 0.6); break;
		case "Folke":        return SetAdaptivelevel(chr, 4, GEN_TYPE_OFFICER, GEN_MINIBOSS, GEN_ARCHETYPE_NAVIGATOR, GEN_ARCHETYPE_CANNONER, GEN_FIXED_PIRATES, 0.4); break;
		case "Tichingitu":   return SetAdaptivelevel(chr, 5, GEN_TYPE_OFFICER, GEN_MINIBOSS, GEN_ARCHETYPE_GUNMAN, GEN_ARCHETYPE_FREE, GEN_FIXED_PIRATES, 0.6); break;
		case "Irons":        return SetAdaptivelevel(chr, 7, GEN_TYPE_OFFICER, GEN_MINIBOSS, GEN_ARCHETYPE_GUNMAN, GEN_ARCHETYPE_FREE, GEN_FIXED_PIRATES, 0.6); break;
		case "Longway":      return SetAdaptivelevel(chr, 11, GEN_TYPE_OFFICER, GEN_MINIBOSS, GEN_ARCHETYPE_NAVIGATOR, GEN_ARCHETYPE_GUNMAN, GEN_FIXED_PIRATES, 0.45);  break;
		case "Longway_FP":   return SetAdaptivelevel(chr, 11, GEN_TYPE_OFFICER, GEN_MINIBOSS, GEN_ARCHETYPE_NAVIGATOR, GEN_ARCHETYPE_GUNMAN, GEN_FIXED_PIRATES, 0.45);  break;
		case "Knippel":      return SetAdaptivelevel(chr, 13, GEN_TYPE_OFFICER, GEN_MINIBOSS, GEN_ARCHETYPE_CANNONER, GEN_ARCHETYPE_BOATSWAIN, GEN_FIXED_PIRATES, 0.4); break;
		case "Kneepel_FP":   return SetAdaptivelevel(chr, 13, GEN_TYPE_OFFICER, GEN_MINIBOSS, GEN_ARCHETYPE_CANNONER, GEN_ARCHETYPE_BOATSWAIN, GEN_FIXED_PIRATES, 0.4); break;
		case "Tonzag":       return SetAdaptivelevel(chr, 12, GEN_TYPE_OFFICER, GEN_MINIBOSS, GEN_ARCHETYPE_SOLDIER, GEN_ARCHETYPE_FREE, GEN_FIXED_PIRATES, 0.6); break;
		case "Mary":
		{
			if (!CheckAttribute(chr, "quest.blade31")) return SetAdaptivelevel(chr, 16, GEN_TYPE_OFFICER, GEN_MINIBOSS, GEN_ARCHETYPE_DUELIST, GEN_ARCHETYPE_FREE, GEN_FIXED_PIRATES, 0.6);
			return SetAdaptivelevel(chr, 16, GEN_TYPE_OFFICER, GEN_MINIBOSS, GEN_ARCHETYPE_SOLDIER, GEN_ARCHETYPE_FREE, GEN_FIXED_PIRATES, 0.6);
		}
		break;
		case "Helena":       return SetAdaptivelevel(chr, 14, GEN_TYPE_OFFICER, GEN_MINIBOSS, GEN_ARCHETYPE_NAVIGATOR, GEN_ARCHETYPE_BOATSWAIN, GEN_FIXED_PIRATES, 0.5); break;
		case "GriffOfficer": return SetAdaptivelevel(chr, 18, GEN_TYPE_OFFICER, GEN_MINIBOSS, GEN_ARCHETYPE_NAVIGATOR, GEN_ARCHETYPE_CANNONER, GEN_FIXED_PIRATES, 0.4); break;
		case "Ecliaton_Cap": return SetAdaptivelevel(chr, 24, GEN_TYPE_OFFICER, GEN_MINIBOSS, GEN_ARCHETYPE_CANNONER, GEN_ARCHETYPE_NAVIGATOR, GEN_FIXED_PIRATES, 0.4); break;
		case "Baker":        return SetAdaptivelevel(chr, 18, GEN_TYPE_OFFICER, GEN_MINIBOSS, GEN_ARCHETYPE_DOCTOR, GEN_ARCHETYPE_PEASANT, GEN_FIXED_PIRATES, 0.35); break;
		case "Avendel":      return SetAdaptivelevel(chr, 12, GEN_TYPE_OFFICER, GEN_MINIBOSS, GEN_ARCHETYPE_TREASURER, GEN_ARCHETYPE_PEASANT, GEN_FIXED_PIRATES, 0.4); break;
	}

	trace("missing template for hero: " + chr.id);
	return false;
}

void ForceHeroPerks(ref chr)
{
	switch (chr.id)
	{
		case "Longway":
		{
			SetCharacterPerkWithRequired(chr, "Captain");
		}
		break;
		case "Longway_FP":
		{
			SetCharacterPerkWithRequired(chr, "Captain");
		}
		break;
		case "Knippel":
		{
			SetCharacterPerkWithRequired(chr, "Captain");
		}
		break;
		case "Kneepel_FP":
		{
			SetCharacterPerkWithRequired(chr, "Captain");
		}
		break;
		case "Tonzag":
		{
			SetCharacterPerkWithRequired(chr, "SharedExperience");
		}
		break;
		case "Helena":
		{
			SetCharacterPerkWithRequired(chr, "ByWorker");
		}
		break;
		case "GriffOfficer":
		{
			SetCharacterPerkWithRequired(chr, "Captain");
			RemoveCaptainOfficers(chr);
			GEN_SetNavyFromShip(chr);
		}
		break;
		case "Ecliaton_Cap":
		{
			SetCharacterPerkWithRequired(chr, "Captain");
			RemoveCaptainOfficers(chr);
			GEN_SetNavyFromShip(chr);
		}
		break;
	}
}
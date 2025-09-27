 // RB Квестовые офицеры
ref InitHugo(string name, string lastname)
{
	ref sld = GetCharacter(NPC_GenerateCharacter("Avendel", "Hugh", "man", "man", 10, HOLLAND, -1, true, "quest"));
	FantomMakeCoolFighter(sld, 20, 50, 50, "blade_04", "pistol1", "bullet", 50);
	sld.name = name;
	sld.lastname = lastname;
	sld.dialog.FileName = "Quest\Portugal_dialog.c";
	sld.dialog.currentnode = "Avendel_tavern";
	sld.greeting = "avendel_1";
	sld.rank = 12;
	SetSPECIAL(sld, 3, 8, 3, 10, 10, 3, 6);
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
	// FreeSitLocator("Marigo_tavern", "sit_front1");
	// ChangeCharacterAddressGroup(sld, "Marigo_tavern", "sit", "sit_front1");
	// AddLandQuestMark(sld, "questmarkmain");
	SetFunctionTimerCondition("Portugal_BeginOver", 0, 0, 2, false);
	pchar.questTemp.Portugal = "begin";
	InitHeroRebalance(sld, 0.6, GEN_ARCHETYPE_TREASURER, GEN_ARCHETYPE_PEASANT);
	Log_Info("InitHugo: " + sld.name);
	return sld;
}

ref InitFolke(string name, string lastname)
{
	ref sld = GetCharacter(NPC_GenerateCharacter("Folke", "DeLuck", "man", "man", 1, FRANCE, -1, false, "quest"));
	sld.name = name;
	sld.lastname = lastname;
	sld.greeting = "officer_hire";
	sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
	sld.dialog.currentnode = "Folke";
	LAi_SetImmortal(sld, true);
	sld.CompanionDisable = true;
	sld.rank = 5;
	sld.money = 0;
	SetSPECIAL(sld, 8, 9, 6, 5, 10, 7, 5);
	GiveItem2Character(sld, "unarmed");
	EquipCharacterbyItem(sld, "unarmed");
	ChangeCharacterAddressGroup(sld, "Fortfrance_prison", "goto", "goto23");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocator(sld, "reload", "reload1", "FolkeStay", -1);
	pchar.questTemp.Sharlie = "takeskiper";
	
	sld = GetCharacter(NPC_GenerateCharacter("Del_Ohranik", "sold_fra_2", "man", "man", sti(pchar.rank), FRANCE, 0, true, "soldier"));
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	ChangeCharacterAddressGroup(sld, "Fortfrance_prison", "goto", "goto12");
	LAi_SetActorType(sld);
	LAi_ActorFollow(sld, CharacterFromID("Folke"), "", -1);
	
	StartQuestMovie(true, false, true);
	DoQuestCheckDelay("Del_Turma", 0.1);
	InitHeroRebalance(sld, 0.6, GEN_ARCHETYPE_NAVIGATOR, GEN_ARCHETYPE_SOLDIER); // RB Квестовые офицеры
	return sld;
}
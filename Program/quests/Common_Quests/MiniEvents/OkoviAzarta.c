void OZ_Kuznets_NoAgree()
{
	CloseQuestHeader("OZ");
	sld = CharacterFromID("OZ_Blacksmith");
	LAi_CharacterDisableDialog(sld);
	sld.lifeday = 0;
}

void OZ_Kuznets_Agree()
{
	AddQuestRecord("OZ", "2");
	AddQuestUserData("OZ", "sSex", GetSexPhrase("ся","ась"));
	
	sld = GetCharacter(NPC_GenerateCharacter("OZ_Shuler", "citiz_8", "man", "man", 5, PIRATE, -1, true, "marginal"));
	sld.name = StringFromKey("Neutral_33");
	sld.lastname = StringFromKey("Neutral_34");
	sld.dialog.filename = "Quest\MiniEvents\OkoviAzarta_dialog.c";
	sld.dialog.currentnode = "OZ_Shuler_1";
	FreeSitLocator("PortSpein_tavern", "sit_base6");
	ChangeCharacterAddressGroup(sld, "PortSpein_tavern", "sit", "sit_base6");
	LAi_SetSitType(sld);
	AddLandQuestMark(sld, "questmarkmain");
	
	GiveItem2Character(sld, "Mineral26");
	GiveItem2Character(sld, "totem_13");
	GiveItem2Character(sld, "OZ_book");
	GiveItem2Character(sld, "OZ_letter");
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	
	PChar.quest.OZ_Grot.win_condition.l1 = "item";
	PChar.quest.OZ_Grot.win_condition.l1.item = "OZ_letter";
	PChar.quest.OZ_Grot.function = "OZ_Grot";
}

void OZ_GameCards()
{
	pchar.OZ_TrueMoney = sti(pchar.money); 
	pchar.OZ_StartGameMoney = 100000; // фиксированная сумма для карточной игры
	pchar.money = sti(pchar.OZ_StartGameMoney); 

	sld = CharacterFromID("OZ_Shuler");
	sld.money = 100000;
	pchar.GenQuest.Cards.npcharIdx = sld.index;
	pchar.GenQuest.Cards.iRate = 5000;
	pchar.GenQuest.Cards.SitType = true;
	pchar.GenQuest.Cards.OnWin = "OZ_GameWin";
	pchar.GenQuest.Cards.OnLoss = "OZ_GameLoss";
	pchar.GenQuest.Cards.DontStop = true;
	LaunchCardsGame();
}

void OZ_GameWin(string qName)
{
	if (CheckAttribute(pchar, "OZ_TrueMoney") && CheckAttribute(pchar, "OZ_StartGameMoney"))
	{
		int delta = sti(pchar.money) - sti(pchar.OZ_StartGameMoney);
		pchar.money = sti(pchar.OZ_TrueMoney) + delta;

		DeleteAttribute(pchar, "OZ_TrueMoney");
		DeleteAttribute(pchar, "OZ_StartGameMoney");
	}
	chrDisableReloadToLocation = true;
	sld = CharacterFromID("OZ_Shuler");
	sld.dialog.currentnode = "OZ_Shuler_Win_1";
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorSetSitMode(sld);
	LAi_ActorDialogNow(sld, pchar, "", -1);
}

void OZ_GameLoss(string qName)
{
	if (CheckAttribute(pchar, "OZ_TrueMoney") && CheckAttribute(pchar, "OZ_StartGameMoney"))
	{
			int delta = sti(pchar.money) - sti(pchar.OZ_StartGameMoney);
			pchar.money = sti(pchar.OZ_TrueMoney) + delta;

			if (delta < 0) 
			{
				ref sld = CharacterFromID("OZ_Shuler");
				sld.money = -delta;
			}

			DeleteAttribute(pchar, "OZ_TrueMoney");
			DeleteAttribute(pchar, "OZ_StartGameMoney");
	}
	chrDisableReloadToLocation = true;
	sld = CharacterFromID("OZ_Shuler");
	//sld.dialog.currentnode = "OZ_Shuler_Win_1";
	sld.dialog.currentnode = "OZ_Shuler_Lose_1";
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorSetSitMode(sld);
	LAi_ActorDialogNow(sld, pchar, "", -1);
}

void OZ_GameCards_Duel()
{
	LAi_LocationFightDisable(loadedLocation, false);
	LAi_SetFightMode(pchar, true);
	
	sld = CharacterFromID("OZ_Shuler");
	ChangeCharacterAddressGroup(sld, PChar.location, "tables", "stay3");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
	LAi_group_SetCheckFunction("EnemyFight", "OZ_GameCards_Duel_2");
	
	PChar.quest.OZ_Shuler_Bitva_3.win_condition.l1 = "item";
	PChar.quest.OZ_Shuler_Bitva_3.win_condition.l1.item = "OZ_book";
	PChar.quest.OZ_Shuler_Bitva_3.function = "OZ_Shuler_Bitva_3";
	
	/*PChar.Quest.Duel_Fight_Right_Now.win_condition.l1 = "Location";
	PChar.Quest.Duel_Fight_Right_Now.win_condition.l1.Location = "Clone_location";
	PChar.Quest.Duel_Fight_Right_Now.function = "OZ_GameCards_Duel_2";

	LocationMakeClone(pchar.location);
	Locations[FindLocation("Clone_location")].image = "loading\tavern_fight.tga";
	DoReloadCharacterToLocation("Clone_location", "goto", "goto5");*/
}

void OZ_GameCards_Duel_2(string qName)
{
	LAi_LocationFightDisable(loadedLocation, true);
	chrDisableReloadToLocation = false;
	DoQuestCheckDelay("hide_weapon", 1.2);
}

void OZ_GameCards_Lose(string qName)
{
	chrDisableReloadToLocation = false;
	AddQuestRecord("OZ", "4");
	pchar.questTemp.OZ_Tavern_1 = true;
	sld = CharacterFromID("OZ_Shuler"); 
	sld.quest.OZ_Shuler_Lose = true;
	AddLandQuestMark(characterFromId("PortSpein_tavernkeeper"), "questmarkmain");
}

void OZ_GameCards_Fail()
{
	chrDisableReloadToLocation = false;
	AddQuestRecord("OZ", "5");
	pchar.questTemp.OZ_Tavern_1 = true;
	sld = CharacterFromID("PortSpein_tavernkeeper");
	AddLandQuestMark(sld, "questmarkmain");
	sld.quest.OZ_Shuler_Fail = true;
}

void OZ_Felip_1()
{
	AddQuestRecord("OZ", "6");
	
	sld = GetCharacter(NPC_GenerateCharacter("OZ_Felip", "citiz_7", "man", "man", 5, SPAIN, -1, false, "quest"));
	sld.name = StringFromKey("Neutral_29");
	sld.lastname = StringFromKey("Neutral_30");
	GiveItem2Character(sld, "blade_09");
	EquipCharacterByItem(sld, "blade_09");
	sld.City = "PortSpein";
	sld.dialog.filename = "Quest\MiniEvents\OkoviAzarta_dialog.c";
	sld.dialog.currentnode = "OZ_Felip_1";
	ChangeCharacterAddressGroup(sld, "PortSpein_houseS1", "barmen", "stay");
	LAi_SetStayType(sld);
	AddLandQuestMark(sld, "questmarkmain");
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
}

void OZ_Felip_2()
{
	AddQuestRecord("OZ", "7");
	
	sld = GetCharacter(NPC_GenerateCharacter("OZ_Frantsuz", "citiz_6", "man", "man", 5, FRANCE, -1, true, "soldier"));
	sld.dialog.filename = "Quest\MiniEvents\OkoviAzarta_dialog.c";
	sld.dialog.currentnode = "OZ_Frantsuz_1";
	FreeSitLocator("PortSpein_tavern", "sit_front6");
	ChangeCharacterAddressGroup(sld, "PortSpein_tavern", "sit", "sit_front6");
	LAi_SetSitType(sld);
	LAi_CharacterDisableDialog(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
	
	sld = CharacterFromID("OZ_Shuler");
	LAi_CharacterEnableDialog(sld);
	LAi_SetSitType(sld);
	sld.dialog.filename = "Quest\MiniEvents\OkoviAzarta_dialog.c";
	sld.dialog.currentnode = "OZ_Shuler_11";
	AddLandQuestMark(sld, "questmarkmain");
}

void OZ_Shuler_Bitva()
{
	chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(loadedLocation, false);
	LAi_SetFightMode(pchar, true);
	
	sld = CharacterFromID("OZ_Shuler");
	ChangeCharacterAddressGroup(sld, PChar.location, "tables", "stay3");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
	LAi_group_SetCheckFunction("EnemyFight", "OZ_Shuler_Bitva_2");
}

void OZ_Shuler_Bitva_2(string qName)
{
	LAi_LocationFightDisable(loadedLocation, true);
	DoQuestCheckDelay("hide_weapon", 1.2);
	
	PChar.quest.OZ_Shuler_Bitva_3.win_condition.l1 = "item";
	PChar.quest.OZ_Shuler_Bitva_3.win_condition.l1.item = "OZ_book";
	PChar.quest.OZ_Shuler_Bitva_3.function = "OZ_Shuler_Bitva_3";
}

void OZ_Shuler_Bitva_3(string qName)
{
	if (CheckAttribute(pchar, "questTemp.OZ_Draka"))
	{
		sld = GetCharacter(NPC_GenerateCharacter("OZ_Frantsuz", "citiz_6", "man", "man", 5, FRANCE, -1, true, "soldier"));
		ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
	}
	else
	{
		sld = CharacterFromID("OZ_Frantsuz");
		ChangeCharacterAddressGroup(sld, PChar.location, "tables", "stay3");
	}
	LAi_CharacterEnableDialog(sld);
	sld.dialog.filename = "Quest\MiniEvents\OkoviAzarta_dialog.c";
	sld.dialog.currentnode = "OZ_Frantsuz_1";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void OZ_Frantsuz_1()
{
	OZ_Frantsuz_exit();
	sld = CharacterFromID("OZ_Blacksmith");
	AddLandQuestMark(sld, "questmarkmain");
	if (CheckAttribute(pchar, "questTemp.OZ_Draka"))
	{
	AddQuestRecord("OZ", "8_1");
	}
	else
	{
	AddQuestRecord("OZ", "8");
	}
}

void OZ_Frantsuz_2()
{
	OZ_Frantsuz_exit(); 
	if (CheckAttribute(pchar, "questTemp.OZ_Draka"))
	{
	AddQuestRecord("OZ", "9_1");
	}
	else
	{
	AddQuestRecord("OZ", "9");
	}
	sld = CharacterFromID("OZ_Blacksmith");
	sld.dialog.filename = "Quest\MiniEvents\OkoviAzarta_dialog.c";
	sld.dialog.currentnode = "OZ_Kuznets_Fail";
	sld.lifeday = 30;
	SaveCurrentNpcQuestDateParam(sld, "LifeTimeCreate");
}

void OZ_Frantsuz_exit()
{
	chrDisableReloadToLocation = false;
	sld = CharacterFromID("OZ_Frantsuz");
	sld.lifeday = 0;
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", 15);
}

void OZ_Kuznets_Nagrada()
{
	AddQuestRecord("OZ", "10");
	if (!CheckAttribute(pchar, "questTemp.OZ_Dolg")){CloseQuestHeader("OZ");}
	sld = CharacterFromID("OZ_Blacksmith");
	sld.dialog.filename = "Quest\MiniEvents\OkoviAzarta_dialog.c";
	sld.dialog.currentnode = "OZ_Kuznets_Tovar";
	sld.Merchant.type = "OZ_Blacksmith";
	GiveItemToTrader(sld);
}

void OZ_Kuznets_Reset(string qName)
{
	sld = CharacterFromID("OZ_Blacksmith");
	sld.dialog.filename = "Quest\MiniEvents\OkoviAzarta_dialog.c";
	sld.dialog.currentnode = "OZ_Kuznets_Tovar";
}

void OZ_Kuznets_Reset_2(string qName)
{
	sld = CharacterFromID("OZ_Blacksmith");
	GiveItemToTrader(sld);
	DeleteAttribute(sld, "quest.OZ_Kuznets_tovar");
}

void OZ_Kuznets_Fail()
{
	sld = CharacterFromID("OZ_Blacksmith");
	sld.lifeday = 0;
	LAi_CharacterDisableDialog(sld);
}

void OZ_Grot(string qName)
{
	SetFunctionLocationCondition("OZ_Grot_2", "Trinidad_Grot", false);
	locations[FindLocation("Trinidad_Grot")].DisableEncounters = true;
}

void OZ_Grot_2(string qName)
{
	chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(loadedLocation, true);
	TakeItemFromCharacter(pchar, "OZ_letter");
	ref sld = &locations[FindLocation("Trinidad_Grot")];
	sld.box1 = Items_MakeTime(0, 0, 0, 2025);
	if (CheckAttribute(pchar, "questTemp.OZ_Draka")){sld.box1.items.gold = 10000;} else {sld.box1.items.gold = 100000}
	sld.box1.items.map_normal = 1;
	sld.box1.items.pistol5 = 1;
	sld.box1.items.GunPowder = 50;
	sld.box1.items.bullet = 50;
	sld.box1.items.potionwine = 2;
	sld.box1.items.potion1 = 5;
	sld.box1.items.potion3 = 1;
	SetFunctionLocatorCondition("OZ_Grot_3", "Trinidad_Grot", "box", "box1", false)
}

void OZ_Grot_3(string qName)
{
	for (i=1; i<=3; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("OZ_Bandit_"+i, "citiz_4"+(rand(8)+1), "man", "man", 5, PIRATE, 0, true, "pirate"));
		sld.dialog.filename = "Quest\MiniEvents\OkoviAzarta_dialog.c";
		sld.dialog.currentnode = "OZ_Bandit_1";
		ChangeCharacterAddressGroup(sld, "Trinidad_Grot", "reload", "reload1");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
	}	
}

void OZ_Grot_4()
{
	LAi_LocationFightDisable(loadedLocation, false);
	LAi_SetFightMode(pchar, true);
	for (i=1; i<=3; i++)
	{
		sld = CharacterFromID("OZ_Bandit_"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
	LAi_group_SetCheckFunction("EnemyFight", "OZ_Grot_5");
	DeleteAttribute(pchar, "questTemp.OZ_Draka");
}

void OZ_Grot_5(string qName)
{
	chrDisableReloadToLocation = false;
	locations[FindLocation("Trinidad_Grot")].DisableEncounters = false;
	DoQuestCheckDelay("hide_weapon", 1.2);
	
	sld = CharacterFromID("OZ_Felip");
	sld.dialog.filename = "Quest\MiniEvents\OkoviAzarta_dialog.c";
	sld.dialog.currentnode = "OZ_Felip_11";
	AddLandQuestMark(sld, "questmarkmain");
	
	SetFunctionTimerCondition("OZ_Felip_timer", 0, 0, 3, false);
}

void OZ_Felip_timer(string qName)
{
	ChangeCharacterComplexReputation(pchar, "nobility", -10);
	ChangeCharacterHunterScore(pchar, "spahunter", 50);
	
	sld = CharacterFromID("OZ_Felip");
	sld.lifeday = 0;
	LAi_CharacterDisableDialog(sld);
	AddQuestRecord("OZ", "11");
	if (!CheckCharacterItem(pchar, "OZ_book")){CloseQuestHeader("OZ");}
}

void OZ_Felip_good()
{
	sld = CharacterFromID("OZ_Felip");
	sld.lifeday = 0;
	LAi_CharacterDisableDialog(sld);
	DeleteQuestCondition("OZ_Felip_timer");
	if (!CheckCharacterItem(pchar, "OZ_book")){CloseQuestHeader("OZ");}
}

void OZ_Felip_bad()
{
	LAi_LocationFightDisable(loadedLocation, false);
	LAi_SetFightMode(pchar, true);
	chrDisableReloadToLocation = true;
	sld = CharacterFromID("OZ_Felip");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	DeleteQuestCondition("OZ_Felip_timer");
	
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
	LAi_group_SetCheckFunction("EnemyFight", "OZ_Felip_bad_2");
}

void OZ_Felip_bad_2(string qName)
{
	chrDisableReloadToLocation = false;
	ChangeCharacterComplexReputation(pchar, "nobility", -2);
	ChangeCharacterHunterScore(pchar, "spahunter", 50);
	LAi_group_AttackGroup("SPAIN_CITIZENS", LAI_GROUP_PLAYER);
	AddQuestRecord("OZ", "12");
	if (!CheckCharacterItem(pchar, "OZ_book")){CloseQuestHeader("OZ");}
}
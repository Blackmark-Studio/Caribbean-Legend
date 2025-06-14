//=================================================================
//======================кейсы из quests_reaction===================
//=================================================================
bool Longway_QuestComplete(string sQuestName, string qname)
{
	ref sld, npchar;
	int i, idx;
	
	bool condition = true;
		
	if (sQuestName == "PZ_BETA_Test_Start_S_samogo_nachala_2") {
		AddQuestRecord("Holl_Gambit", "1-36");
		AddQuestRecord("Holl_Gambit", "1-38");
		AddQuestRecord("Holl_Gambit", "1-39");
		LocatorReloadEnterDisable("GVIK", "reload2", false);
		pchar.questTemp.HWIC.Holl = "MerdokDie";
		GiveItem2Character(PChar, "MerdokArchive");
		sld = characterFromId("Lucas");
		sld.dialog.filename = "Quest\HollandGambit\LucasRodenburg.c";
		sld.dialog.currentnode = "Second_time";
		AddLandQuestMark(sld, "questmarkmain");
		
		// Sinistra - квест Лонгвэя "Путеводная звезда"
		PChar.quest.PZ_Start.win_condition.l1 = "location";
		PChar.quest.PZ_Start.win_condition.l1.location = "Curacao";
		PChar.quest.PZ_Start.win_condition = "PZ_Start";
	}
	
	else if (sQuestName == "PZ_BETA_Test_Start_BasTer") {
		SetQuestHeader("PZ");
		AddQuestRecord("PZ", "1");
		
		//Sinistra - квест Лонгвэя "Путеводная звезда"
		pchar.questTemp.PZ_BasTerAlkash = true;
		pchar.questTemp.PZ_BasTerTavern = true;
		pchar.questTemp.PZ_LongwayGood = true;
	}
	
	else if (sQuestName == "PZ_Start") {
		if (GetCharacterIndex("Longway") != -1 && CheckPassengerInCharacter(pchar, "Longway") && !CheckAttribute(pchar, "questTemp.PZ_Start"))
		{
			if (CheckCharacterItem(PChar, "MerdokArchive"))
			{
				pchar.GenQuest.CabinLock = true;
				Island_SetReloadEnableGlobal("Curacao", false);
				bQuestDisableMapEnter = true;
				DoQuestCheckDelay("PZ_VorovstvoVKaute", 2.5);
				pchar.questTemp.PZ_NashliArhiv = true;
			}
			else SetTimerCondition("PZ_Etap1_Start", 0, 0, 30, false);	// 1 этап стартует через 30 дней
			pchar.questTemp.PZ_Start = true;
			pchar.questTemp.PZ_LongwayNelzyaOtdatArube = true;
		}
	}
	
	else if (sQuestName == "PZ_VorovstvoVKaute") {
		DeleteAttribute(pchar, "GenQuest.CabinLock");
		pchar.GenQuest.DontSetCabinOfficer = true;
		chrDisableReloadToLocation = true;
		Sea_CabinStartNow();
		DoQuestCheckDelay("PZ_VorovstvoVKaute_2", 1.8);
	}
	
	else if (sQuestName == "PZ_VorovstvoVKaute_2") {
		if (GetCharacterIndex("Tichingitu") != -1 && CheckPassengerInCharacter(pchar, "Tichingitu"))
		{
			sld = characterFromId("Tichingitu");
			ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Tichingitu_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
			return true;
		}
		if (GetCharacterIndex("Duran") != -1 && CheckPassengerInCharacter(pchar, "Duran"))
		{
			sld = characterFromId("Duran");
			ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Duran_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
			return true;
		}
		if (GetCharacterIndex("Folke") != -1 && CheckPassengerInCharacter(pchar, "Folke"))
		{
			sld = characterFromId("Folke");
			ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Folke_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
			return true;
		}
		sld = GetCharacter(NPC_GenerateCharacter("Alonso", "Alonso", "man", "man", sti(pchar.rank), pchar.nation, 0, true, "soldier"));
		sld.name 	= StringFromKey("Longway_1");
		sld.lastname = StringFromKey("Longway_2");
		ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_Alonso_1";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
		sld.location = "None";
	}
	
	else if (sQuestName == "PZ_OsmatrivaemSunduk") {
		LAi_SetActorType(pchar);
		LAi_ActorTurnToLocator(PChar, "box", "box1");
		LAi_ActorAnimation(pchar, "Barman_idle", "PZ_OsmatrivaemSunduk_2", 5);
	}
	
	else if (sQuestName == "PZ_OsmatrivaemSunduk_2") {
		pchar.questTemp.PZ_OsmatrivaemSunduk = true;
		DoQuestCheckDelay("TalkSelf_Quest", 0.5);
	}
	
	else if (sQuestName == "PZ_OsmatrivaemSunduk_3") {
		pchar.questTemp.PZ_RodenburgUkradenaStranitsa = true;
		AddQuestRecord("Holl_Gambit", "1-48");
		DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
		Island_SetReloadEnableGlobal("Curacao", true);
		bQuestDisableMapEnter = false;
		chrDisableReloadToLocation = false;
	}
	
	else if (sQuestName == "PZ_LigaInJungle") {
		PChar.quest.PZ_LigaInJungle2.win_condition.l1 = "Location_Type";
		PChar.quest.PZ_LigaInJungle2.win_condition.l1.location_type = "jungle";
		PChar.quest.PZ_LigaInJungle2.win_condition = "PZ_LigaInJungleVstrecha";
	}
	
	else if (sQuestName == "PZ_LigaInJungleVstrecha") {
		if (loadedLocation.id.label == "ExitTown")	
		{
			PChar.quest.PZ_LigaInJungle3.win_condition.l1 = "ExitFromLocation";
			PChar.quest.PZ_LigaInJungle3.win_condition.l1.location = PChar.location;
			PChar.quest.PZ_LigaInJungle3.win_condition = "PZ_LigaInJungle";
		}
		else
		{
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], true);
			chrDisableReloadToLocation = true;
			GetCharacterPos(pchar, &locx, &locy, &locz);
			for (i=1; i<=4; i++)
			{	
				sld = GetCharacter(NPC_GenerateCharacter("LigaInJungle_"+i, "killer_4", "man", "man", sti(pchar.rank), PIRATE, -1, true, "hunter"));
				ChangeCharacterAddressGroup(sld, pchar.location, "goto",  LAi_FindFarLocator("goto", locx, locy, locz));
				sld.viper = true;
				if (i>=2 && i<=4)
				{
					LAi_SetActorType(sld);
					LAi_ActorFollow(sld, pchar, "", -1);
				}
				if (i==1)
				{
					sld.model = "killer_2";
					sld.model.animation = "man";
					Characters_RefreshModel(sld);
					FantomMakeCoolFighter(sld, sti(pchar.rank)+5, 50, 50, "blade_13", "pistol3", "grapeshot", 100);
					sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
					sld.dialog.currentnode = "PZ_LigaInJungle_1";
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
			}
		}
	}
	
	else if (sQuestName == "PZ_LigaInJunglePosleBitvy") {
		DoQuestCheckDelay("hide_weapon", 1.2);
		if (CharacterIsHere("Longway"))
		{
			sld = characterFromId("Longway");
			LAi_RemoveCheckMinHP(sld);
			LAi_SetImmortal(sld, false);
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Longway_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		}
		else chrDisableReloadToLocation = false;
		SetTimerCondition("PZ_Etap1_Start", 0, 0, 30, false);	// 1 этап стартует через 30 дней
	}
	
	else if (sQuestName == "PZ_Etap1_Start") {
		PChar.quest.PZ_Etap1_Start2.win_condition.l1 = "Location_Type";
		PChar.quest.PZ_Etap1_Start2.win_condition.l1.location_type = "town";
		PChar.quest.PZ_Etap1_Start2.win_condition = "PZ_Etap1_Start2";
	}
	
	else if (sQuestName == "PZ_Etap1_Start2") {
		if (GetCharacterIndex("Longway") != -1 && CheckPassengerInCharacter(pchar, "Longway"))
		{
			sld = characterFromId("Longway");
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto9");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Longway_11";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			bDisableFastReload = true;
			chrDisableReloadToLocation = true;
			pchar.quest.Mary_giveme_sex1.over = "yes";
		}
	}
	
	else if (sQuestName == "PZ_LongwayUhoditOtNasNavsegda") {
		sld = characterFromId("Longway");
		RemovePassenger(pchar, sld);
		sld.location = "None";
		
		AddQuestRecord("PZ", "2");
		CloseQuestHeader("PZ");
		AddQuestRecordInfo("PZ_LongwayProshaetsya", "1");
	}
	
	else if (sQuestName == "PZ_IshemLongway") {
		pchar.questTemp.PZ_BasTerAlkash = true;
		pchar.questTemp.PZ_BasTerTavern = true;
		AddMapQuestMarkIsland("Guadeloupe", false);
		
		SetTimerCondition("PZ_BasTer_Opozdal", 0, 0, 10, false);	//Таймер на провал
	}
	
	else if (sQuestName == "PZ_BasTer_Opozdal") {
		pchar.questTemp.PZ_BasTerOpozdal = true;
		DeleteAttribute(pchar, "questTemp.PZ_BasTerAlkash");
	}
	
	else if (sQuestName == "PZ_SharliePlennik_BadFinal") {
		sld = GetCharacter(CreateCharacterClone(CharacterFromID("basterJailOff"), 0));
		sld.id = "BasterJailOffClone";
		ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto22");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocator(sld, "goto", "goto23", "PZ_SharliePlennik_BadFinal_1", -1);
		DoQuestFunctionDelay("Puancie_InJailTalk", 3.0);
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_SharliePlennik_BadFinal_1";
		WaitDate("", 0, 0, 2, 0, 0);
		RecalculateJumpTable();
		RefreshWeather();
		RefreshLandTime();
	}
	
	else if (sQuestName == "PZ_SharliePlennik_BadFinal_1") {
		sld = characterFromId("BasterJailOffClone");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
	}
	
	else if (sQuestName == "PZ_SharliePlennik_BadFinal_2") {
		DoQuestReloadToLocation("BasTer_town", "reload", "reload_jail", "PZ_SharliePlennik_BadFinal_3");
	}
	
	else if (sQuestName == "PZ_SharliePlennik_BadFinal_3") {
		CloseQuestHeader("PZ");
		bDisableLandEncounters = false;
		if (CheckAttribute(pchar, "questTemp.PZ_BasTerAlkash2")) AddQuestRecord("PZ", "4");
		if (CheckAttribute(pchar, "questTemp.PZ_BasTerTavern2")) AddQuestRecord("PZ", "8");
		
		LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", false);
		LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", false);
		//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", false);
		bDisableCharacterMenu = false;
		InterfaceStates.Buttons.Save.enable = true;
		bDisableFastReload = false;
		chrDisableReloadToLocation = false;
	}
	
	else if (sQuestName == "PZ_KorablPort_BadFinal") {
		CloseQuestHeader("PZ");
		AddQuestRecord("PZ", "6");
		bDisableLandEncounters = false;
		SetTimerCondition("PZ_KorablPort_BadFinal2", 0, 0, 7, false);
	}
	
	else if (sQuestName == "PZ_KorablPort_BadFinal2") {
		LocatorReloadEnterDisable("BasTer_town", "gate_back", false);
		Island_SetReloadEnableGlobal("Guadeloupe", true);
		LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", false);
		LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", false);
		//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", false);
	}
	
	else if (sQuestName == "PZ_KorablBuhta_BadFinal") {
		CloseQuestHeader("PZ");
		AddQuestRecord("PZ", "7");
		bDisableLandEncounters = false;
		
		LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", false);
		LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", false);
		//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", false);
	}
	
	else if (sQuestName == "PZ_IshemLongway_Otryad") {
		for (i=1; i<=4; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("PZ_BasTer_OtryadPeshera"+i, "sold_fra_"+(rand(7)+1), "man", "man", sti(pchar.rank), FRANCE, 0, true, "soldier"));
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, pchar.location, "rld",  "loc"+i);
			LAi_SetHP(sld, 60.0, 60.0);
		}
		sld = GetCharacter(NPC_GenerateCharacter("PZ_BasTer_OtryadPesheraOff", "off_fra_3", "man", "man", sti(pchar.rank), FRANCE, 0, true, "soldier"));
		LAi_SetActorType(sld);
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_BasTer_OtryadPeshera_1";
		ChangeCharacterAddressGroup(sld, pchar.location, "rld",  "loc7");
		LAi_SetActorType(pchar);
		SetActorDialogAny2Pchar(sld.id, "", -1, 0.0);
		LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 2.0);
		LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 2.0);
	}
	
	else if (sQuestName == "PZ_BasTer_OtryadPeshera_Kill_3") {
		chrDisableReloadToLocation = false;
		
		PChar.quest.PZ_IshemLongway_SorraKomendant.win_condition.l1 = "location";
		PChar.quest.PZ_IshemLongway_SorraKomendant.win_condition.l1.location = "Guadeloupe_CaveEntrance";
		PChar.quest.PZ_IshemLongway_SorraKomendant.win_condition = "PZ_IshemLongway_SorraKomendant";
	}
	
	else if (sQuestName == "PZ_BasTer_OtryadRazveli") {
		for (i=1; i<=5; i++)
		{
			sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
			ChangeCharacterAddressGroup(sld, "none", "", "");
		}
		sld = CharacterFromID("PZ_BasTer_OtryadPesheraOff");
		ChangeCharacterAddressGroup(sld, "none", "", "");
		
		DoQuestCheckDelay("PZ_BasTer_OtryadRazveli2", 20.0);
		PChar.quest.PZ_BasTer_OtryadRazveli3.win_condition.l1 = "ExitFromLocation";
		PChar.quest.PZ_BasTer_OtryadRazveli3.win_condition.l1.location = PChar.location;
		PChar.quest.PZ_BasTer_OtryadRazveli3.win_condition = "PZ_BasTer_OtryadRazveli3";
	}
	
	else if (sQuestName == "PZ_BasTer_OtryadRazveli2") {
		for (i=1; i<=5; i++)
		{
			sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
			sld.lifeday = 0;
			ChangeCharacterAddressGroup(sld, "Guadeloupe_CaveEntrance", "reload", "reload1");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		sld = CharacterFromID("PZ_BasTer_OtryadPesheraOff");
		sld.lifeday = 0;
		ChangeCharacterAddressGroup(sld, "Guadeloupe_CaveEntrance", "reload", "reload1");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		
		sld = CharacterFromID("Longway");
		LAi_SetOfficerType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		DeleteQuestCondition("PZ_BasTer_OtryadRazveli3");
	}
	
	else if (sQuestName == "PZ_BasTer_OtryadRazveli3") {
		Event("QuestDelayExit","sl", "", 0);
	}
	
	else if (sQuestName == "PZ_BasTer_Strazha") {
		chrDisableReloadToLocation = true;
		LAi_LocationFightDisable(&Locations[FindLocation("BasTer_town")], true);
		for (i=1; i<=3; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("PZ_BasTer_Strazha_"+i, "sold_fra_"+(rand(7)+1), "man", "man", 10, FRANCE, 0, true, "soldier"));
			ChangeCharacterAddressGroup(sld, "BasTer_town", "goto", "goto19");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			if (i == 3)
			{
				sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
				sld.dialog.currentnode = "PZ_BasTerStop";
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
		}
	}
	
	else if (sQuestName == "PZ_BasTer_TurmaPriveli") {
		TeleportCharacterToPos(pchar, 9.21, 0.00, -11.35);
		sld = CharacterFromID("BasTerJailOff");
		sld.dialog.filename = "Common_Prison.c";
		sld.dialog.currentnode = "PZ_BasTer_ComendantDialog";
		LAi_SetActorType(sld);
		LAi_ActorSetHuberMode(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
	}
	
	else if (sQuestName == "PZ_IshemLongway_OtryadUPeshery") {
		chrDisableReloadToLocation = true;
		LAi_LocationFightDisable(&Locations[FindLocation("Guadeloupe_CaveEntrance")], true);
		LAi_SetPlayerType(pchar);
		
		sld = CharacterFromID("Longway");
		ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto1");
		LAi_CharacterEnableDialog(sld);
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_BasTer_SOtryadom_DialogLongway";
		LAi_SetStayType(sld);
		sld.talker = 5;
		
		for (i=1; i<=5; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("PZ_BasTer_OtryadPeshera"+i, "sold_fra_"+(rand(7)+1), "man", "man", 5, FRANCE, 0, true, "soldier"));
			ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload2");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			LAi_SetHP(sld, 60.0, 60.0);
		}
		sld = GetCharacter(NPC_GenerateCharacter("PZ_BasTer_OtryadPesheraOff", "off_fra_3", "man", "man", sti(pchar.rank), FRANCE, 0, true, "soldier"));
		ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload2");
		LAi_SetActorType(sld);
		LAi_ActorFollow(sld, pchar, "", -1);
	}
	
	else if (sQuestName == "PZ_BasTer_MyUbilLongway_BadFinal") {
		sld = GetCharacter(NPC_GenerateCharacter("PZ_BasTer_OtryadPesheraOff", "off_fra_3", "man", "man", sti(pchar.rank), FRANCE, 0, true, "soldier"));
		ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload2");
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_BasTer_SOtryadom_UbiliLongway";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	
	else if (sQuestName == "PZ_LongwayNelzyaUmeret") {
		CloseQuestHeader("PZ");
		AddQuestRecord("PZ", "12");
		bDisableLandEncounters = false;
		
		LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", false);
		LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", false);
		//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", false);
		chrDisableReloadToLocation = false;
	}
	
	else if (sQuestName == "PZ_IshemLongway_SorraKomendant") {
		chrDisableReloadToLocation = true;
		LAi_LocationFightDisable(&Locations[FindLocation("Guadeloupe_CaveEntrance")], true);
		
		sld = CharacterFromID("Longway");
		ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto1");
		LAi_CharacterEnableDialog(sld);
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_IshemLongway_SorraKomendant_Dialog";
		LAi_SetStayType(sld);
		sld.talker = 5;
	}
	
	else if (sQuestName == "PZ_IshemLongway_SorraKomendant_Dialog_Povernutsya") {
		CharacterTurnToLoc(pchar, "reload", "reload2");
	}
	
	else if (sQuestName == "PZ_IshemLongway_SorraKomendant_Pobeda1") {
		if (!LAi_isDead(CharacterFromID("Longway")))
		{
			DoQuestCheckDelay("hide_weapon", 1.2);
			sld = CharacterFromID("Longway");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_IshemLongway_SorraKomendant_Dialog_4";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		}
	}
	
	else if (sQuestName == "PZ_IshemLongway_VPesheru") {
		DoQuestReloadToLocation("Guadeloupe_Cave", "monsters", "monster12", "PZ_IshemLongway_VPesheru_2");
	}
	
	else if (sQuestName == "PZ_IshemLongway_VPesheru_2") {
		LAi_SetPlayerType(pchar);
		TeleportCharacterToPosAy(pchar, 9.20, 1.26, -0.44, -1.70);
		LAi_SetFightMode(pchar, true);
		
		sld = CharacterFromID("Longway");
		ChangeCharacterAddressGroup(sld, pchar.location, "monsters", "monster11");
		TeleportCharacterToPosAy(sld, 7.35, 1.26, -2.19, 0.90);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		LAi_SetCurHPMax(pchar);
		LAi_GetCharacterMaxEnergy(pchar);
		LAi_SetCurHPMax(sld);
		LAi_GetCharacterMaxEnergy(sld);
		
		for(i=1; i<=3; i++)
		{
			idx = GetOfficersIndex(pchar, i);
			if(idx < 0) continue;
			sld = &Characters[idx];
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload2");
			OfficersFollow();
		}
		
		for (i=1; i<=4; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("PZ_BasTer_OtryadPeshera"+i, "sold_fra_"+(rand(7)+1), "man", "man", sti(pchar.rank), FRANCE, 0, true, "soldier"));
			ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload4");
			TeleportCharacterToPosAy(sld, 0.74, 1.90, -1.86, 0.00);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetHP(sld, 60.0, 60.0);
		}
		sld = GetCharacter(NPC_GenerateCharacter("PZ_BasTer_OtryadPeshera5", "mush_fra_"+(rand(2)+1), "man", "mushketer", sti(pchar.rank), FRANCE, 0, false, "soldier"));
		ChangeCharacterAddressGroup(sld, pchar.location, "monsters", "monster8");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		LAi_SetHP(sld, 60.0, 60.0);
		GiveItem2Character(sld, "grape_mushket");
		EquipCharacterByItem(sld, "grape_mushket");
		AddItems(sld, "grenade", 5);
		LAi_SetCharacterUseBullet(sld, MUSKET_ITEM_TYPE, "grenade");
		sld.MusketerDistance = 0;
		
		// Босс мальтиец
		sld = GetCharacter(NPC_GenerateCharacter("PZ_BasTer_OtryadPeshera6", "mush_fra_6", "man", "mushketer", sti(pchar.rank), FRANCE, 0, false, "soldier"));
		ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		GiveItem2Character(sld, "mushket5");
		EquipCharacterByItem(sld, "mushket5");
		AddItems(sld, "cartridge", 20);
		LAi_SetCharacterUseBullet(sld, MUSKET_ITEM_TYPE, "cartridge");
		sld.MusketerDistance = 0;
		
		DoQuestCheckDelay("PZ_IshemLongway_VPesheru_4", 25.0);
		
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		LAi_group_SetCheck("EnemyFight", "PZ_IshemLongway_VPesheru_3");
	}
	
	else if (sQuestName == "PZ_IshemLongway_VPesheru_3") {
		if (!LAi_isDead(CharacterFromID("Longway")))
		{
			DoQuestCheckDelay("hide_weapon", 1.2);
			sld = CharacterFromID("Longway");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			if (CheckAttribute(pchar, "questTemp.PZ_IshemLongway_SorraKomendant")) sld.dialog.currentnode = "PZ_IshemLongway_SorraKomendant_Dialog_6";
			else sld.dialog.currentnode = "PZ_IshemLongway_SrazuNashli_4";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		}
	}
	
	else if (sQuestName == "PZ_IshemLongway_VPesheru_4") {
		sld = CharacterFromID("PZ_BasTer_OtryadPeshera6");
		sld.MusketerDistance = 5;
	}
	
	else if (sQuestName == "PZ_IshemLongway_VyhodIsPeshery") {
		sld = CharacterFromID("Longway");
		ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto1");
		AddPassenger(pchar, sld, false);
		sld.OfficerImmortal = true;
		sld.Health.HP       = 60.0;
		sld.Health.maxHP    = 60.0;
		LAi_SetActorType(sld);
		LAi_ActorFollowEverywhere(sld, "", -1);
		sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
		sld.Dialog.CurrentNode = "Longway_officer";
		
		LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", false);
		LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", false);
		//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", false);
		chrDisableReloadToLocation = false;
		bDisableLandEncounters = false;
		AddQuestRecord("PZ", "14");
		DeleteQuestCondition("PZ_LongwayNelzyaUmeret");
		DeleteQuestCondition("PZ_KorablBuhta_BadFinal");
		
		//Продолжение второго этапа
		PChar.quest.PZ_LongwayRazgovorVKaute.win_condition.l1 = "EnterToSea"
		PChar.quest.PZ_LongwayRazgovorVKaute.win_condition = "PZ_LongwayRazgovorVKaute";
	}
	
	else if (sQuestName == "PZ_IshemLongway_Zastupaemsya") {
		if (!LAi_isDead(CharacterFromID("Longway")))
		{
			DoQuestCheckDelay("hide_weapon", 1.2);
			sld = CharacterFromID("Longway");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_IshemLongway_Zastupaemsya_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		}
	}
	
	else if (sQuestName == "PZ_IshemLongway_Zastupaemsya_5") {
		if (!LAi_isDead(CharacterFromID("Longway")))
		{
			DoQuestCheckDelay("hide_weapon", 1.2);
			sld = CharacterFromID("Longway");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_IshemLongway_Zastupaemsya_6";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		}
	}
	
	else if (sQuestName == "PZ_BasTerPeshera") {
		LAi_SetFightMode(pchar, true);
		chrDisableReloadToLocation = true;
		DeleteAttribute(pchar, "questTemp.PZ_BasTerTurma");
		DelLandQuestMarkToPhantom();
		PChar.quest.PZ_LongwayNelzyaUmeret.win_condition.l1 = "NPC_Death";
		PChar.quest.PZ_LongwayNelzyaUmeret.win_condition.l1.character = "Longway";
		PChar.quest.PZ_LongwayNelzyaUmeret.win_condition = "PZ_LongwayNelzyaUmeret";
		
		sld = CharacterFromID("Longway");
		LAi_SetImmortal(sld, false);
		DeleteAttribute(sld, "OfficerImmortal");
		if(CheckAttribute(sld, "Health.HP")) DeleteAttribute(sld, "Health.HP");
		if(CheckAttribute(sld, "Health.maxHP")) DeleteAttribute(sld, "Health.maxHP");
		sTemp = "RestoreHealth_" + sld.index;
		if(CheckAttribute(PChar, "quest.RestoreHealth_" + sld.index)) PChar.quest.(sTemp).over = "Yes";
		ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto1");
		LAi_CharacterEnableDialog(sld);
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_IshemLongway_SrazuNashli_1";
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		
		for (i=1; i<=3; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("PZ_BasTer_OtryadPeshera"+i, "sold_fra_"+(rand(7)+1), "man", "man", sti(pchar.rank), FRANCE, 0, true, "soldier"));
			ChangeCharacterAddressGroup(sld, pchar.location, "quest",  "player");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetHP(sld, 60.0, 60.0);
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		LAi_group_SetCheck("EnemyFight", "PZ_BasTerPeshera_2");
	}
	
	else if (sQuestName == "PZ_BasTerPeshera_2") {
		DoQuestCheckDelay("hide_weapon", 1.2);
		sld = CharacterFromID("Longway");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
	}
	
	else if (sQuestName == "PZ_LongwayRazgovorVKaute") {	//Старт 2 этапа
		pchar.GenQuest.CabinLock = true;
		Island_SetReloadEnableGlobal("Guadeloupe", false);
		bQuestDisableMapEnter = true;
		DoQuestCheckDelay("PZ_LongwayRazgovorVKaute_2", 2.5);
	}
	
	else if (sQuestName == "PZ_LongwayRazgovorVKaute_2") {
		DeleteAttribute(pchar, "GenQuest.CabinLock");
		pchar.GenQuest.DontSetCabinOfficer = true;
		chrDisableReloadToLocation = true;
		Sea_CabinStartNow();
		DoQuestCheckDelay("PZ_LongwayRazgovorVKaute_3", 1.8);
	}
	
	else if (sQuestName == "PZ_LongwayRazgovorVKaute_3") {
		sld = CharacterFromID("Longway");
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_LongwayRazgovorOProshlom";
		LAi_SetStayType(sld);
		ChangeCharacterAddressGroup(sld, PChar.location, "rld", "loc1");
		CharacterTurnByChr(sld, pchar);	
		AddLandQuestMark(sld, "questmarkmain");
	}
	
	//Начало флешбека в Формозе
	else if (sQuestName == "PZ_Formosa_Start") {
		TeleportCharacterToPosAy(pchar, -3.71, 2.00, 0.66, 1.60);
		LAi_SetActorType(pchar);
		LAi_ActorGoToLocator(pchar, "goto", "goto23", "", -1);
		StartQuestMovie(true, false, true);
		locCameraFromToPos(4.50, 2.36, 0.13, false, -4.75, 1.60, -0.32);
		
		chrDisableReloadToLocation = false;
		//InterfaceStates.Buttons.Save.enable = false;
		//bDisableCharacterMenu = true;
		LAi_SetCurHPMax(pchar);
		LAi_SetCheckMinHP(pchar, 1, true, "SkritoeBessmertie");
		pchar.GenQuest.CannotWait = true;
		pchar.GenQuest.BlockTalkSelf = true;
		pchar.BaseNation = HOLLAND;
		
		GiveItem2Character(PChar, "blade_11");
		EquipCharacterByItem(Pchar, "blade_11");
		RemoveCharacterEquip(PChar, GUN_ITEM_TYPE);
		
		sld = GetCharacter(NPC_GenerateCharacter("PZ_Formosa_tavernkeeper", "barmen_9", "man", "man", 1, HOLLAND, 14, false, "quest"));
		SaveCurrentNpcQuestDateParam(sld, "LifeTimeCreate");
		sld.name = StringFromKey("Longway_3");
		sld.lastname = StringFromKey("Longway_4");
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_Formosa_Tavern_1";
		sld.location	= "Formosa_Tavern";
		sld.location.group = "barmen";
		sld.location.locator = "stay";
		LAi_SetStayType(sld);
		//AddLandQuestMark(sld, "questmarkmain");
		
		/*sld = GetCharacter(NPC_GenerateCharacter("PZ_Formosa_waitress", "women_11", "woman", "towngirl", 1, HOLLAND, 14, false, "quest"));
		SaveCurrentNpcQuestDateParam(sld, "LifeTimeCreate");
		sld.location	= "Formosa_Tavern";
		sld.location.group = "waitress";
		sld.location.locator = "barmen";
		LAi_CharacterDisableDialog(sld);
		LAi_SetWaitressType(sld);*/
		
		sld = GetCharacter(NPC_GenerateCharacter("PZ_Formosa_smuggler", "citiz_29", "man", "man", 1, PIRATE, 14, false, "quest"));
		SaveCurrentNpcQuestDateParam(sld, "LifeTimeCreate");
		sld.name = StringFromKey("Longway_5");
		sld.lastname = StringFromKey("Longway_6");
		GiveItem2Character(sld, BLADE_SABER);
		EquipCharacterbyItem(sld, BLADE_SABER);
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_Formosa_smuggler_1";
		LAi_SetActorType(sld);
		LAi_ActorSetSitMode(sld);
		LAi_CharacterDisableDialog(sld);
		ChangeCharacterAddressGroup(sld, "Formosa_Tavern", "sit", "sit_front2");
		
		sld = GetCharacter(NPC_GenerateCharacter("PZ_JohanVanMerden", "Merdok", "man", "man", 1, HOLLAND, 14, false, "quest"));
		SaveCurrentNpcQuestDateParam(sld, "LifeTimeCreate");
		sld.name = StringFromKey("Longway_7");
		sld.lastname = StringFromKey("Longway_8");
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_Formosa_JohanVanMerden_1";
		LAi_SetStayType(sld);
		ChangeCharacterAddressGroup(sld, "Formosa_houseSp1", "barmen", "bar1");
		//AddLandQuestMark(sld, "questmarkmain");
		
		LocatorReloadEnterDisable("Formosa", "houseSp1", true);
		
		DoQuestCheckDelay("PZ_Formosa1_Info", 0.2);
		DoQuestCheckDelay("PZ_Formosa1_1", 0.7);
		
		//Декоративные жители в городе
		for (i=1; i<=10; i++)
		{				
			sld = GetCharacter(NPC_GenerateCharacter("PZ_Formoza_MirnyeMan_"+i, "citiz_"+(rand(39)+1), "man", "man", 5, HOLLAND, 14, false, ""));
			SaveCurrentNpcQuestDateParam(sld, "LifeTimeCreate");
			LAi_SetCitizenType(sld);
			LAi_CharacterDisableDialog(sld);
			ChangeCharacterAddressGroup(sld, "Formosa", "goto", "goto"+(rand(19)+1));
			LAi_SetLoginTime(sld, 6.0, 21.99);
		}
		for (i=1; i<=6; i++)
		{				
			sld = GetCharacter(NPC_GenerateCharacter("PZ_Formoza_MirnyeWoman_"+i, "girl_"+(rand(10)+1), "woman", "woman", 5, HOLLAND, 14, false, "quest"));
			SaveCurrentNpcQuestDateParam(sld, "LifeTimeCreate");
			LAi_SetCitizenType(sld);
			LAi_CharacterDisableDialog(sld);
			ChangeCharacterAddressGroup(sld, "Formosa", "goto", "goto"+(rand(19)+1));
			LAi_SetLoginTime(sld, 6.0, 21.99);
		}
		for (i=1; i<=4; i++)
		{				
			sld = GetCharacter(NPC_GenerateCharacter("PZ_Formoza_Guard_"+i, "sold_hol_"+(rand(7)+1), "man", "man", 5, HOLLAND, 14, true, "soldier"));
			SaveCurrentNpcQuestDateParam(sld, "LifeTimeCreate");
			LAi_SetGuardianType(sld);
			LAi_CharacterDisableDialog(sld);
			ChangeCharacterAddressGroup(sld, "Formosa", "soldiers", "protector"+i);
			LAi_SetLoginTime(sld, 6.0, 21.99);
		}
		for (i=1; i<=6; i++)
		{				
			sld = GetCharacter(NPC_GenerateCharacter("PZ_Formoza_Sold_"+i, "sold_hol_"+(rand(7)+1), "man", "man", 5, HOLLAND, 14, true, "soldier"));
			SaveCurrentNpcQuestDateParam(sld, "LifeTimeCreate");
			LAi_SetWarriorType(sld);
			LAi_CharacterDisableDialog(sld);
			ChangeCharacterAddressGroup(sld, "Formosa", "patrol", "patrol"+i);
			LAi_SetLoginTime(sld, 6.0, 21.99);
		}
		for (i=1; i<=4; i++)
		{				
			sld = GetCharacter(NPC_GenerateCharacter("PZ_Formoza_MirnyeManTorgovets_"+i, "citiz_"+(rand(19)+1), "man", "man", 5, HOLLAND, 14, false, ""));
			SaveCurrentNpcQuestDateParam(sld, "LifeTimeCreate");
			LAi_SetStayType(sld);
			LAi_CharacterDisableDialog(sld);
			ChangeCharacterAddressGroup(sld, "Formosa", "merchant", "merchant"+i);
			LAi_SetLoginTime(sld, 6.0, 21.99);
		}
		//Декоративные алкаши в таверне города
		sld = GetCharacter(NPC_GenerateCharacter("PZ_Formoza_Alkash_1", "citiz_"+(rand(39)+1), "man", "man", 5, HOLLAND, 14, false, ""));
		SaveCurrentNpcQuestDateParam(sld, "LifeTimeCreate");
		LAi_SetSitType(sld);
		LAi_CharacterDisableDialog(sld);
		ChangeCharacterAddressGroup(sld, "Formosa_tavern", "sit", "sit_base4");
		
		sld = GetCharacter(NPC_GenerateCharacter("PZ_Formoza_Alkash_2", "citiz_"+(rand(39)+1), "man", "man", 5, HOLLAND, 14, false, ""));
		SaveCurrentNpcQuestDateParam(sld, "LifeTimeCreate");
		LAi_SetSitType(sld);
		LAi_CharacterDisableDialog(sld);
		ChangeCharacterAddressGroup(sld, "Formosa_tavern", "sit", "sit_front4");
		
		sld = GetCharacter(NPC_GenerateCharacter("PZ_Formoza_Alkash_3", "citiz_"+(rand(39)+1), "man", "man", 5, HOLLAND, 14, false, ""));
		SaveCurrentNpcQuestDateParam(sld, "LifeTimeCreate");
		LAi_SetSitType(sld);
		LAi_CharacterDisableDialog(sld);
		ChangeCharacterAddressGroup(sld, "Formosa_tavern", "sit", "sit2");
		//Декоративные жители для катсцен
		sld = GetCharacter(NPC_GenerateCharacter("PZ_Formoza_MirnyeWoman_Anturazh1", "girl_"+(rand(10)+1), "woman", "woman", 5, HOLLAND, 0, false, "quest"));
		LAi_SetCitizenType(sld);
		LAi_CharacterDisableDialog(sld);
		ChangeCharacterAddressGroup(sld, "Formosa", "goto", "goto21");
		LAi_SetLoginTime(sld, 6.0, 21.99);
	}
	
	else if (sQuestName == "PZ_Formosa1_Info") {
		pchar.GenQuest.FrameLockEsc = true;
		SetLaunchFrameFormParam(StringFromKey("Longway_9", NewStr()), "", 0, 4.0);
		LaunchFrameForm();
	}
	
	else if (sQuestName == "PZ_Formosa1_1") {
		LAi_SetActorType(pchar);
		LAi_ActorGoToLocator(pchar, "officers", "houseS2_3", "", -1);
		DoQuestCheckDelay("PZ_Formosa1_2", 7.5);
		SetMusic("music_way_back_then");
		pchar.questTemp.lockedMusic = true;
	}
	
	else if (sQuestName == "PZ_Formosa1_2") {
		LAi_Fade("PZ_Formosa1_3", "");
	}
	
	else if (sQuestName == "PZ_Formosa1_3") {
		locCameraFromToPos(2.28, 5.40, -2.24, true, 7.62, 5.60, -5.24);
		DoQuestCheckDelay("PZ_Formosa1_5", 3.0);
	}
	
	else if (sQuestName == "PZ_Formosa1_4") {
		LAi_Fade("PZ_Formosa1_5", "");
	}
	
	else if (sQuestName == "PZ_Formosa1_5") {
		locCameraFromToPos(-5.29, 6.06, 0.63, false, 3.08, 2.70, -3.05);
		TeleportCharacterToPos(pchar, 0.33, 2.00, -0.20);
		LAi_SetActorType(pchar);
		LAi_ActorGoToLocator(pchar, "reload", "reload4_back", "", -1);
		DoQuestCheckDelay("PZ_Formosa1_6", 3.5);
	}
	
	else if (sQuestName == "PZ_Formosa1_6") {
		DoQuestReloadToLocation("Formosa_tavern", "reload", "reload1", "PZ_Formosa1_7");
	}
	
	else if (sQuestName == "PZ_Formosa1_7") {
		TeleportCharacterToPosAy(pchar, -0.90, 0.00, 1.20, 3.00);
		LAi_SetActorType(pchar);
		LAi_ActorGoToLocator(pchar, "waitress", "barmen", "PZ_Formosa1_8", -1);
		locCameraFromToPos(1.25, 2.17, -1.26, true, -2.19, -1.00, -4.53);
	}
	
	else if (sQuestName == "PZ_Formosa1_8") {
		LAi_SetStayType(pchar);
		sld = CharacterFromID("PZ_Formosa_tavernkeeper");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
	}
	
	else if (sQuestName == "PZ_Formosa1_9") {
		locCameraSleep(false);
		LAi_SetActorType(pchar);
		LAi_ActorGoToLocator(pchar, "tables", "stay3", "PZ_Formosa1_10", -1);
		locCameraFromToPos(-0.83, 0.94, 4.45, true, -3.62, -0.30, 0.51);
	}
	
	else if (sQuestName == "PZ_Formosa1_10") {
		LAi_SetStayType(pchar);
		sld = CharacterFromID("PZ_Formosa_smuggler");
		LAi_ActorDialog(sld, pchar, "", 0, 0);
	}
	
	else if (sQuestName == "PZ_Formosa_Spustya4Dnya") {
		LAi_SetStayType(pchar);
		TeleportCharacterToPosAy(pchar, -0.44, 0.00, 0.70, 1.10);
		locCameraFromToPos(-2.64, 2.14, 0.73, true, 2.78, -1.00, 2.74);
		
		sld = CharacterFromID("PZ_Formosa_smuggler");
		ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1_back");
		TeleportCharacterToPosAy(sld, 3.23, 0.00, 3.07, -2.00);
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_Formosa_smuggler_11";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	
	else if (sQuestName == "PZ_Formosa1_11") {
		locCameraSleep(false);
		DoQuestReloadToLocation("Formosa_houseSp1", "goto", "goto2", "PZ_Formosa1_12");
	}
	
	else if (sQuestName == "PZ_Formosa1_12") {
		LAi_SetStayType(pchar);
		sld = CharacterFromID("PZ_JohanVanMerden");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
	}
	
	else if (sQuestName == "PZ_Formosa_Spustya7Dney") {
		LAi_SetStayType(pchar);
		CharacterTurnToLoc(pchar, "goto", "goto2");
		locCameraFromToPos(-21.26, 1.89, 9.91, true, -30.14, 0.84, 12.96);
		
		sld = CharacterFromID("PZ_JohanVanMerden");
		ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto2");
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_Formosa_JohanVanMerden_11";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	
	else if (sQuestName == "PZ_Batavia_Puteshestvie") {
		LAi_SetActorType(pchar);
		LAi_ActorGoToLocator(pchar, "reload", "basement1", "", -1);
		locCameraFromToPos(-3.54, 5.78, 49.75, true, 1.22, 3.33, 41.27);
		DoQuestCheckDelay("PZ_Batavia_1", 6.0);
		
		//Декоративные жители в городе
		for (i=1; i<=10; i++)
		{				
			sld = GetCharacter(NPC_GenerateCharacter("PZ_Batavia_MirnyeMan_"+i, "citiz_"+(rand(39)+1), "man", "man", 5, HOLLAND, 14, false, ""));
			SaveCurrentNpcQuestDateParam(sld, "LifeTimeCreate");
			LAi_SetCitizenType(sld);
			LAi_CharacterDisableDialog(sld);
			ChangeCharacterAddressGroup(sld, "Batavia", "goto", "goto"+(rand(19)+1));
			LAi_SetLoginTime(sld, 6.0, 21.99);
		}
		for (i=1; i<=6; i++)
		{				
			sld = GetCharacter(NPC_GenerateCharacter("PZ_Batavia_MirnyeWoman_"+i, "girl_"+(rand(10)+1), "woman", "woman", 5, HOLLAND, 14, false, "quest"));
			SaveCurrentNpcQuestDateParam(sld, "LifeTimeCreate");
			LAi_SetCitizenType(sld);
			LAi_CharacterDisableDialog(sld);
			ChangeCharacterAddressGroup(sld, "Batavia", "goto", "goto"+(rand(19)+1));
			LAi_SetLoginTime(sld, 6.0, 21.99);
		}
		for (i=1; i<=5; i++)
		{				
			sld = GetCharacter(NPC_GenerateCharacter("PZ_Batavia_MirnyeManTorgovets_"+i, "citiz_"+(rand(19)+1), "man", "man", 5, HOLLAND, 14, false, ""));
			SaveCurrentNpcQuestDateParam(sld, "LifeTimeCreate");
			LAi_SetStayType(sld);
			LAi_CharacterDisableDialog(sld);
			ChangeCharacterAddressGroup(sld, "Batavia", "merchant", "merchant"+i);
			LAi_SetLoginTime(sld, 6.0, 21.99);
		}
		
		LocatorReloadEnterDisable("Batavia", "reload3_back", true);
		//LocatorReloadEnterDisable("Batavia", "gate_back", true);		//Плантацию закрываем
		LocatorReloadEnterDisable("Batavia", "HouseF3", true);
		
		sld = GetCharacter(NPC_GenerateCharacter("PZ_OliverTrust", "smuggler_boss", "man", "man", 1, HOLLAND, -1, false, "quest"));
		sld.name = StringFromKey("Longway_10");
		sld.lastname = StringFromKey("Longway_11");
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_OliverTrust_1";
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld, "Batavia_store", "barmen", "stay");
		//AddLandQuestMark(sld, "questmarkmain");
				
		sld = GetCharacter(NPC_GenerateCharacter("PZ_SoldResid_1", "sold_hol_"+(rand(7)+1), "man", "man", 5, HOLLAND, -1, true, "soldier"));
		LAi_SetStayType(sld);
		LAi_CharacterDisableDialog(sld);
		ChangeCharacterAddressGroup(sld, "Batavia", "soldiers", "soldier2");
		LAi_SetHP(sld, 50.0, 50.0);
		sld.CantLoot = true;
		
		//DoQuestCheckDelay("PZ_Batavia_Log", 3.0);
	}
	
	/*else if (sQuestName == "PZ_Batavia_Log") {
		Log_Info("Нужно найти магазин");
		PlaySound("interface\notebook.wav");
	}*/
	
	else if (sQuestName == "PZ_Batavia_1") {
		LAi_Fade("PZ_Batavia_2", "");
	}
	
	else if (sQuestName == "PZ_Batavia_2") {
		locCameraFromToPos(-6.62, 7.87, 35.55, true, -12.06, 4.34, 42.34);
		LAi_SetActorType(pchar);
		LAi_ActorGoToLocator(pchar, "reload", "reload6", "PZ_Batavia_3", -1);
	}
	
	else if (sQuestName == "PZ_Batavia_3") {
		DoQuestReloadToLocation("Batavia_Store", "reload", "reload1", "PZ_Batavia_4");
	}
	
	else if (sQuestName == "PZ_Batavia_4") {
		LAi_SetStayType(pchar);
		sld = CharacterFromID("PZ_OliverTrust");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
	}
	
	else if (sQuestName == "PZ_Batavia_plantation_setguards") {
		locCameraFromToPos(6.19, 3.87, 10.15, false, 3.67, 2.26, 19.36);
		chrDisableReloadToLocation = true;
		LAi_SetActorType(pchar);
		LAi_ActorRunToLocator(pchar, "quest", "detector4", "PZ_Batavia_plantation_selfdialog", -1);
		
		// для ношения мушкета в будущем (доступно только в этом варианте)
		if (!CheckCharacterPerk(pchar, "Gunman")) SetCharacterPerk(pchar, "Gunman");
		pchar.CanTakeMushket = true;
		pchar.PriorityMode = 2;
		
		//Димен
		sld = GetCharacter(NPC_GenerateCharacter("PZ_AntoniOneDimen", "banker_1_2", "man", "man", sti(pchar.rank), HOLLAND, -1, false, "quest"));
		sld.name = StringFromKey("Longway_12");
		sld.lastname = StringFromKey("Longway_13");
		GiveItem2Character(sld, "blade_17");
		EquipCharacterByItem(sld, "blade_17");
		GiveItem2Character(sld, "pistol5");
		EquipCharacterByItem(sld, "pistol5");
		sld.CantLoot = true;
		LAi_SetHP(sld, 200.0, 200.0);
		ChangeCharacterAddressGroup(sld, "Batavia_plantation", "goto", "goto18");
		LAi_SetStayType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		
		for (i = 1; i <= 6; i++)
		{
			if (i == 1)
			{
				//Сепп
				sld = GetCharacter(NPC_GenerateCharacter("PZ_SoldPlantation_1", "mercen_26", "man", "man", sti(pchar.rank), HOLLAND, -1, false, "quest"));
				sld.name = StringFromKey("Longway_14");
				sld.lastname = StringFromKey("Longway_15");
				GiveItem2Character(sld, "topor_04");
				EquipCharacterByItem(sld, "topor_04");
				GiveItem2Character(sld, "pistol3");
				EquipCharacterByItem(sld, "pistol3");
				sld.CantLoot = true;
				LAi_SetHP(sld, 300.0, 300.0);
				ChangeCharacterAddressGroup(sld, "Batavia_plantation", "goto",  "goto18");
				LAi_SetStayType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			else
			{
				sld = GetCharacter(NPC_GenerateCharacter("PZ_SoldPlantation_"+i, "sold_hol_"+(rand(7)+1), "man", "man", sti(pchar.rank), HOLLAND, -1, true, "soldier"));
				ChangeCharacterAddressGroup(sld, "Batavia_plantation", "goto",  "goto18");
				LAi_SetStayType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_SetHP(sld, 50.0, 50.0);
				sld.CantLoot = true;
			}
		}
	}
		
	else if (sQuestName == "PZ_Batavia_plantation_selfdialog") {		
		LAi_Fade("PZ_Batavia_plantation_selfdialog_2", "");
	}
	
	else if (sQuestName == "PZ_Batavia_plantation_selfdialog_2") {
		locCameraFromToPos(2.28, 5.52, 20.08, true, 0.67, 0.44, 42.55);
		LAi_SetActorType(pchar);
		pchar.dialog.filename = "Quest\CompanionQuests\Longway.c";
		pchar.dialog.currentnode = "PZ_Batavia_PlantationSelfDialog";
		LAi_ActorSelfDialog(pchar, "pchar_back_to_player");
	}
	
	else if (sQuestName == "PZ_Batavia_PlantationFight") {
		EndQuestMovie();
		InterfaceStates.Buttons.Save.enable = false;
		locCameraTarget(PChar);
		locCameraFollow();
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_SetCheckMinHP(characterFromID("PZ_AntoniOneDimen"), 1, true, "PZ_PlantationDimenSit");
		PlaySound("Voice\Russian\hambit\Longway-02.wav");
	}
	
	else if (sQuestName == "PZ_PlantationDimenSit") {
		sld = CharacterFromID("PZ_AntoniOneDimen");
		LAi_SetActorType(sld);
		LAi_ActorSetGroundSitMode(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		LAi_ActorWaitDialog(sld, pchar);
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_Batavia_PlantationDimen1";
	}
	
	else if (sQuestName == "PZ_Batavia_PlantationDimenDead1") {
		sld = CharacterFromID("PZ_AntoniOneDimen");
		LAi_SetImmortal(sld, false);
		LAi_KillCharacter(sld);
		
		DoQuestCheckDelay("PZ_Batavia_PlantationDimenDead2", 2.0);
	}
	
	else if (sQuestName == "PZ_Batavia_PlantationDimenDead2") {
		LAi_SetActorType(pchar);
		pchar.dialog.filename = "Quest\CompanionQuests\Longway.c";
		pchar.dialog.currentnode = "PZ_Batavia_Plantation_DimenDeadSelfDialog";
		LAi_ActorSelfDialog(pchar, "pchar_back_to_player");
	}
					
	else if (sQuestName == "PZ_Batavia_BitvaLubovnitsa") {
		locCameraFromToPos(1.95, 1.72, -2.27, false, -0.92, -0.60, 2.75);
		chrDisableReloadToLocation = true;
		//Сепп
		sld = GetCharacter(NPC_GenerateCharacter("PZ_Sepp", "mercen_26", "man", "man", sti(pchar.rank), HOLLAND, -1, false, "quest"));
		sld.name = StringFromKey("Longway_14");
		sld.lastname = StringFromKey("Longway_15");
		GiveItem2Character(sld, "topor_04");
		EquipCharacterByItem(sld, "topor_04");
		GiveItem2Character(sld, "pistol3");
		EquipCharacterByItem(sld, "pistol3");
		sld.CantLoot = true;
		LAi_SetHP(sld, 300.0, 300.0);
		ChangeCharacterAddressGroup(sld, "Batavia_HouseF3", "goto", "goto5");
		TeleportCharacterToPosAy(sld, -2.56, 0.02, 1.42, 1.00);
		LAi_SetActorType(sld);
		//Ветте
		sld = GetCharacter(NPC_GenerateCharacter("PZ_Brigitta", "Maman_6", "woman", "woman_B", 1, HOLLAND, 14, false, "quest"));
		SaveCurrentNpcQuestDateParam(sld, "LifeTimeCreate");
		sld.name = StringFromKey("Longway_16");
		sld.lastname = StringFromKey("Longway_17");
		sld.CantLoot = true;
		LAi_SetHP(sld, 25.0, 25.0);
		ChangeCharacterAddressGroup(sld, "Batavia_HouseF3", "goto", "goto5");
		TeleportCharacterToPosAy(sld, -0.95, 0.02, 3.26, -2.60);
		LAi_SetActorType(sld);
		//Люйтерс
		sld = GetCharacter(NPC_GenerateCharacter("PZ_Rubbe", "flutist_11", "man", "musician", sti(pchar.rank), HOLLAND, -1, false, "quest"));
		sld.name = StringFromKey("Longway_18");
		sld.lastname = StringFromKey("Longway_19");
		//GiveItem2Character(sld, "blade_06");
		//EquipCharacterByItem(sld, "blade_06");
		//GiveItem2Character(sld, "pistol1");
		//EquipCharacterByItem(sld, "pistol1");
		sld.CantLoot = true;
		LAi_SetHP(sld, 125.0, 125.0);
		ChangeCharacterAddressGroup(sld, "Batavia_HouseF3", "goto", "goto5");
		TeleportCharacterToPosAy(sld, 1.34, 0.02, 3.14, 4.00);
		LAi_SetFlutistStayAnimation(sld);
		//Димен
		sld = GetCharacter(NPC_GenerateCharacter("PZ_AntoniOneDimen", "banker_1_2", "man", "man", sti(pchar.rank), HOLLAND, -1, false, "quest"));
		sld.name = StringFromKey("Longway_12");
		sld.lastname = StringFromKey("Longway_13");
		GiveItem2Character(sld, "blade_17");
		EquipCharacterByItem(sld, "blade_17");
		GiveItem2Character(sld, "pistol5");
		EquipCharacterByItem(sld, "pistol5");
		sld.CantLoot = true;
		LAi_SetHP(sld, 200.0, 200.0);
		ChangeCharacterAddressGroup(sld, "Batavia_HouseF3", "goto", "goto1");
		LAi_SetActorType(sld);
		LAi_ActorTurnToLocator(sld, "reload", "reload1");
		
		LAi_SetActorType(pchar);
		LAi_ActorFollow(pchar, sld, "PZ_Batavia_BitvaLubovnitsa_2", -1);
		
		DoQuestCheckDelay("PZ_Batavia_BitvaLubovnitsa_music", 0.7);
	}
	
	else if (sQuestName == "PZ_Batavia_BitvaLubovnitsa_music") {
		SetMusic("hol_music_brothel");
	}
	
	else if (sQuestName == "PZ_Batavia_BitvaLubovnitsa_2") {
		LAi_SetPlayerType(pchar);
		sld = CharacterFromID("PZ_AntoniOneDimen");
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_Batavia_BitvaLubovnitsa_1";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
	}
	
	else if (sQuestName == "PZ_Batavia_BitvaLubovnitsa_3") {
		LAi_SetActorType(pchar);
		pchar.dialog.filename = "Quest\CompanionQuests\Longway.c";
		pchar.dialog.currentnode = "PZ_Batavia_BitvaLubovnitsa_21";
		LAi_ActorSelfDialog(pchar, "pchar_back_to_player");
	}
	
	else if (sQuestName == "PZ_Batavia_BitvaLubovnitsa_4") {
		locCameraFromToPos(-0.46, 1.83, 2.19, false, 3.02, -0.80, 3.71);
	}
	
	else if (sQuestName == "PZ_Batavia_BitvaLubovnitsa_5") {
		sld = CharacterFromID("PZ_Brigitta");
		LAi_SetActorType(sld);
		LAi_ActorRunToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
	}
	
	else if (sQuestName == "PZ_Batavia_BitvaSoStrazhnikami") {
		TeleportCharacterToPos(pchar, -6.79, 5.22, 26.56);
		locCameraFromToPos(-2.68, 6.18, 31.28, false, 0.53, 5.00, 19.17);
		LAi_SetActorType(pchar);
		LAi_ActorGoToLocator(pchar, "quest", "quest3", "PZ_Batavia_BitvaSoStrazhnikami_2", -1);
	}
	
	else if (sQuestName == "PZ_Batavia_BitvaSoStrazhnikami_2") {
		LAi_SetStayType(pchar);
		sld = CharacterFromID("PZ_SoldResid_1");
		LAi_CharacterEnableDialog(sld);
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_Batavia_BitvaSoStrazhnikami_1";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
	}
	
	else if (sQuestName == "PZ_Batavia_resedinsia_1") {
		//LAi_SetActorType(pchar);
		LAi_ActorTurnToCharacter(pchar, CharacterFromID("PZ_SoldResid_1"));
		LAi_ActorAnimation(pchar, "Shot", "1", 1.5);
		DoQuestCheckDelay("PZ_Batavia_resedinsia_2", 0.9);
	}
	
	else if (sQuestName == "PZ_Batavia_resedinsia_2") {
		sld = CharacterFromID("PZ_SoldResid_1");
		LAi_KillCharacter(sld);
		DoQuestCheckDelay("PZ_Batavia_BitvaResidensia_2", 2.0);
	}
	
	else if (sQuestName == "PZ_Batavia_BitvaResidensia_2") {
		locCameraSleep(false);
		EndQuestMovie();
		InterfaceStates.Buttons.Save.enable = false;
		DoQuestReloadToLocation("Batavia_townhall", "reload", "reload1", "PZ_Batavia_BitvaResidensia_3");
	}
	
	else if (sQuestName == "PZ_Batavia_BitvaResidensia_3") {
		PlaySound("Voice\Russian\hambit\Longway-02.wav");
		LAi_SetPlayerType(pchar);
		//LAi_LocationFightDisable(&Locations[FindLocation("Batavia_townhall")], false);
		LocatorReloadEnterDisable("Batavia_townhall", "reload1_back", true);
		LAi_SetFightMode(pchar, true);
		for (i=1; i<=4; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("PZ_SoldResid_"+i, "sold_hol_"+(rand(7)+1), "man", "man", sti(pchar.rank), HOLLAND, -1, true, "soldier"));
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto"+i);
			LAi_SetHP(sld, 50.0, 50.0);
			sld.CantLoot = true;
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		LAi_group_SetCheck("EnemyFight", "PZ_Batavia_BitvaResidensia_4");
	}
	
	else if (sQuestName == "PZ_Batavia_BitvaResidensia_4") {
		chrDisableReloadToLocation = false;
		PChar.quest.PZ_Batavia_BitvaResidensia_5.win_condition.l1 = "location";
		PChar.quest.PZ_Batavia_BitvaResidensia_5.win_condition.l1.location = "Batavia_townhallRoom";
		PChar.quest.PZ_Batavia_BitvaResidensia_5.win_condition = "PZ_Batavia_BitvaResidensia_5";
		sld = &Locations[FindLocation("Batavia_townhallRoom")];
		sld.locators_radius.goto.goto4 = 1.0;
	}
	
	else if (sQuestName == "PZ_Batavia_BitvaResidensia_5") {
		//LAi_SetFightMode(pchar, true);
		chrDisableReloadToLocation = true;
		sld = GetCharacter(NPC_GenerateCharacter("PZ_AntoniOneDimen", "banker_1_2", "man", "man", sti(pchar.rank), HOLLAND, -1, false, "quest"));
		sld.name = StringFromKey("Longway_12");
		sld.lastname = StringFromKey("Longway_13");
		GiveItem2Character(sld, "blade_17");
		EquipCharacterByItem(sld, "blade_17");
		GiveItem2Character(sld, "pistol5");
		EquipCharacterByItem(sld, "pistol5");
		sld.CantLoot = true;
		LAi_SetHP(sld, 200.0, 200.0);
		ChangeCharacterAddressGroup(sld, "Batavia_townhallRoom", "barmen", "bar1");
		LAi_SetActorType(sld);
		LAi_SetImmortal(sld, true);
		
		PChar.quest.PZ_Batavia_BitvaResidensia_5_1.win_condition.l1 = "locator";
		PChar.quest.PZ_Batavia_BitvaResidensia_5_1.win_condition.l1.location = "Batavia_townhallRoom";
		PChar.quest.PZ_Batavia_BitvaResidensia_5_1.win_condition.l1.locator_group = "goto";
		PChar.quest.PZ_Batavia_BitvaResidensia_5_1.win_condition.l1.locator = "goto4";
		PChar.quest.PZ_Batavia_BitvaResidensia_5_1.win_condition = "PZ_Batavia_BitvaResidensia_5_1";
	}
	
	else if (sQuestName == "PZ_Batavia_BitvaResidensia_5_1") {
		sld = CharacterFromID("PZ_AntoniOneDimen");
		LAi_SetImmortal(sld, false);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		LAi_SetCheckMinHP(sld, 1, true, "PZ_Batavia_BitvaResidensia_6");
	}
	
	else if (sQuestName == "PZ_Batavia_BitvaResidensia_6") {
		DoQuestCheckDelay("hide_weapon", 1.2);
		sld = CharacterFromID("PZ_AntoniOneDimen");
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_1";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	
	else if (sQuestName == "PZ_Batavia_BitvaResidensia_7") {
		sld = CharacterFromID("PZ_AntoniOneDimen");
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_7";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	
	else if (sQuestName == "PZ_Batavia_BitvaResidensia_8") {
		sld = CharacterFromID("PZ_AntoniOneDimen");
		LAi_SetActorType(pchar);
		LAi_ActorFollow(pchar, sld, "PZ_Batavia_BitvaResidensia_10", -1);
	}
	
	else if (sQuestName == "PZ_Batavia_BitvaResidensia_10") {
		sld = CharacterFromID("PZ_AntoniOneDimen");
		LAi_SetImmortal(sld, false);
		LAi_KillCharacter(sld);
		sld = &Locations[FindLocation("Batavia_townhallRoom")];
		sld.locators_radius.goto.goto4 = 0.5;
		
		DoQuestCheckDelay("PZ_Batavia_BitvaResidensia_11", 2.0);
	}
	
	else if (sQuestName == "PZ_Batavia_BitvaResidensia_11") {
		LAi_SetActorType(pchar);
		pchar.dialog.filename = "Quest\CompanionQuests\Longway.c";
		pchar.dialog.currentnode = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_14";
		LAi_ActorSelfDialog(pchar, "pchar_back_to_player");
	}
	
	else if (sQuestName == "PZ_Formosa2_Start") {
		StartQuestMovie(true, false, true);
		LAi_SetCurHPMax(pchar);
		LAi_GetCharacterMaxEnergy(pchar);
		chrDisableReloadToLocation = true;
		for (i=1; i<=3; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("PZ_FormosaBandit_"+i, "citiz_" + (rand(9) + 41), "man", "man", sti(pchar.rank), PIRATE, -1, true, "pirate"));
			ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto9");
			LAi_SetActorType(sld);
			LAi_ActorTurnToLocator(sld, "goto", "goto7");
			LAi_SetHP(sld, 120.0, 120.0);
			sld.CantLoot = true;
			if (i==1)
			{
				sld.name = StringFromKey("Longway_20");
				sld.lastname = StringFromKey("Longway_21");
				sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
				sld.dialog.currentnode = "PZ_Formosa_bandit_1";
				LAi_SetHP(sld, 160.0, 160.0);
			}
		}
		LAi_SetActorType(pchar);
		LAi_ActorGoToLocator(pchar, "reload", "houseSp1", "", -1);
		DoQuestCheckDelay("PZ_Formosa2_IshemMerden_4", 10.0);
		DoQuestCheckDelay("PZ_Formosa2_IshemMerden_5", 9.5);
		
		DoQuestCheckDelay("PZ_Formosa2_music", 0.5);
	}
	
	else if (sQuestName == "PZ_Formosa2_music") {
		SetMusic("music_way_back_then");
	}
	
	else if (sQuestName == "PZ_Formosa2_IshemMerden_4") {
		for (i=1; i<=3; i++)
		{
			sld = CharacterFromID("PZ_FormosaBandit_"+i);
			LAi_SetActorType(sld);
			if (i==1) LAi_ActorDialog(sld, pchar, "", -1, 0);
			else LAi_ActorFollow(sld, pchar, "", -1);
		}
	}
	
	else if (sQuestName == "PZ_Formosa2_IshemMerden_5") {
		LAi_SetStayType(pchar);
		CharacterTurnToLoc(pchar, "goto", "goto9");
	}
	
	else if (sQuestName == "PZ_Formosa2_IshemMerden_6") {
		sld = CharacterFromID("PZ_JohanVanMerden");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		LAi_SetCheckMinHP(sld, 1, true, "");
	}
	
	else if (sQuestName == "PZ_Formosa2_IshemMerden_7") {
		Event("QuestDelayExit","sl", "", 0);
		DoQuestCheckDelay("hide_weapon", 1.2);
		LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], true);
		sld = CharacterFromID("PZ_JohanVanMerden");
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_Formosa_JohanVanMerden_21";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	
	else if (sQuestName == "PZ_Formosa2_IshemMerden_8") {
		sld = CharacterFromID("PZ_JohanVanMerden");
		ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto2");
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_Formosa_JohanVanMerden_24";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
	}

	else if (sQuestName == "PZ_SegodnyaVremya_2") {
		DeleteAttribute(pchar, "GenQuest.CabinLock");
		Sea_CabinStartNow();
		DoQuestCheckDelay("PZ_SegodnyaVremya_3", 1.8);
	}
	
	else if (sQuestName == "PZ_SegodnyaVremya_3") {
		sld = CharacterFromID("Longway");
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_Longway_PosleRasskaza";
		ChangeCharacterAddressGroup(sld, PChar.location, "rld", "loc1");
		LAi_SetActorType(pchar);
		LAi_SetActorType(sld);
		SetActorDialogAny2Pchar(sld.id, "", 0, 0.0);
		LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 0.0);
		LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 0.0);
	}
	
	//Старт 3 этапа
	else if (sQuestName == "PZ_Kapstervil_Start") {
		StartQuestMovie(true, false, true);
		locCameraFromToPos(125.19, 5.17, -156.42, false, 115.00, 1.24, -166.00);
		DoQuestCheckDelay("PZ_Kapstervil_Start_2", 2.5);
		LAi_SetActorType(pchar);
		LAi_ActorGoToLocator(pchar, "reload", "reload7", "PZ_Kapstervil_OstavlyaemZapisku", -1);
		locations[FindLocation("Kapstervil_ExitTown")].DisableEncounters = true;
		locations[FindLocation("Kapstervil_Jungle")].DisableEncounters = true;
		locations[FindLocation("Kapstervil_Grot")].DisableEncounters = true;
		chrDisableReloadToLocation = false;
		LAi_SetCurHPMax(pchar);
		GiveItem2Character(pchar, "pistol1");
		EquipCharacterByItem(pchar, "pistol1");
		AddItems(pchar, "cartridge", 10);
		LAi_SetCharacterUseBullet(pchar, GUN_ITEM_TYPE, "cartridge");
		
		sld = GetCharacter(NPC_GenerateCharacter("PZ_Kapstervil_priest", "priest_2", "man", "man", 1, FRANCE, 14, false, "quest"));
		SaveCurrentNpcQuestDateParam(sld, "LifeTimeCreate");
		sld.name = StringFromKey("Longway_22");
		sld.lastname = StringFromKey("Longway_23");
		ChangeCharacterAddressGroup(sld, "Kapstervil_Church", "barmen", "bar1");
		LAi_SetActorType(sld);
		
		sld = GetCharacter(NPC_GenerateCharacter("PZ_Kapstervil_tavernkeeper", "barmen_8", "man", "man", 1, FRANCE, 14, false, "quest"));
		SaveCurrentNpcQuestDateParam(sld, "LifeTimeCreate");
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		ChangeCharacterAddressGroup(sld, "Kapstervil_tavern", "barmen", "stay");
		LAi_SetActorType(sld);
		
		sld = GetCharacter(NPC_GenerateCharacter("PZ_Kapstervil_waitress", "women_13", "woman", "towngirl", 1, FRANCE, 14, false, "quest"));
		SaveCurrentNpcQuestDateParam(sld, "LifeTimeCreate");
		sld.location	= "Kapstervil_Tavern";
		sld.location.group = "waitress";
		sld.location.locator = "barmen";
		LAi_CharacterDisableDialog(sld);
		LAi_SetWaitressType(sld);
		
		sld = GetCharacter(NPC_GenerateCharacter("PZ_Kapstervil_trader", "trader_8", "man", "man", 1, FRANCE, 14, false, "quest"));
		SaveCurrentNpcQuestDateParam(sld, "LifeTimeCreate");
		ChangeCharacterAddressGroup(sld, "Kapstervil_store", "barmen", "stay");
		LAi_SetActorType(sld);
		
		DoQuestCheckDelay("PZ_Kapstervil_Log", 3.0);
		
		//Декоративные жители в городе
		for (i=1; i<=10; i++)
		{				
			sld = GetCharacter(NPC_GenerateCharacter("PZ_Kapstervil_MirnyeMan_"+i, "citiz_"+(rand(39)+1), "man", "man", 5, FRANCE, 14, false, ""));
			SaveCurrentNpcQuestDateParam(sld, "LifeTimeCreate");
			LAi_SetCitizenType(sld);
			LAi_CharacterDisableDialog(sld);
			ChangeCharacterAddressGroup(sld, "Kapstervil", "goto", "goto"+(rand(19)+1));
			LAi_SetLoginTime(sld, 6.0, 21.99);
		}
		for (i=1; i<=6; i++)
		{				
			sld = GetCharacter(NPC_GenerateCharacter("PZ_Kapstervil_MirnyeWoman_"+i, "girl_"+(rand(10)+1), "woman", "woman", 5, FRANCE, 14, false, "quest"));
			SaveCurrentNpcQuestDateParam(sld, "LifeTimeCreate");
			LAi_SetCitizenType(sld);
			LAi_CharacterDisableDialog(sld);
			ChangeCharacterAddressGroup(sld, "Kapstervil", "goto", "goto"+(rand(19)+1));
			LAi_SetLoginTime(sld, 6.0, 21.99);
		}
		for (i=1; i<=4; i++)
		{				
			sld = GetCharacter(NPC_GenerateCharacter("PZ_Kapstervil_Guard_"+i, "sold_fra_"+(rand(7)+1), "man", "man", 5, FRANCE, 14, true, "soldier"));
			SaveCurrentNpcQuestDateParam(sld, "LifeTimeCreate");
			LAi_SetGuardianType(sld);
			LAi_CharacterDisableDialog(sld);
			ChangeCharacterAddressGroup(sld, "Kapstervil", "soldiers", "protector"+i);
			LAi_SetLoginTime(sld, 6.0, 21.99);
		}
		for (i=1; i<=6; i++)
		{				
			sld = GetCharacter(NPC_GenerateCharacter("PZ_Kapstervil_Sold_"+i, "sold_fra_"+(rand(7)+1), "man", "man", 5, FRANCE, 14, true, "soldier"));
			SaveCurrentNpcQuestDateParam(sld, "LifeTimeCreate");
			LAi_SetWarriorType(sld);
			LAi_CharacterDisableDialog(sld);
			ChangeCharacterAddressGroup(sld, "Kapstervil", "patrol", "patrol"+i);
			LAi_SetLoginTime(sld, 6.0, 21.99);
		}
		for (i=1; i<=4; i++)
		{				
			sld = GetCharacter(NPC_GenerateCharacter("PZ_Kapstervil_MirnyeManTorgovets_"+i, "citiz_"+(rand(19)+1), "man", "man", 5, FRANCE, 14, false, ""));
			SaveCurrentNpcQuestDateParam(sld, "LifeTimeCreate");
			LAi_SetStayType(sld);
			LAi_CharacterDisableDialog(sld);
			ChangeCharacterAddressGroup(sld, "Kapstervil", "merchant", "merchant"+i);
			LAi_SetLoginTime(sld, 6.0, 21.99);
		}
		//Декоративные жители в церкви Капстервиля
		for (i=1; i<=6; i++)
		{				
			sld = GetCharacter(NPC_GenerateCharacter("PZ_Kapstervil_MirnyeManChurch_"+i, "citiz_"+(rand(19)+1), "man", "man", 5, FRANCE, 14, false, ""));
			SaveCurrentNpcQuestDateParam(sld, "LifeTimeCreate");
			LAi_SetSitType(sld);
			sld.nonTable = true;
			LAi_CharacterDisableDialog(sld);
			ChangeCharacterAddressGroup(sld, "Kapstervil_Church", "sit", "sit"+i);
			LAi_SetLoginTime(sld, 6.0, 21.99);
		}
		
		//Декоративные алкаши в таверне города
		sld = GetCharacter(NPC_GenerateCharacter("PZ_Kapstervil_Alkash_1", "citiz_"+(rand(39)+1), "man", "man", 5, FRANCE, 14, false, ""));
		SaveCurrentNpcQuestDateParam(sld, "LifeTimeCreate");
		LAi_SetSitType(sld);
		LAi_CharacterDisableDialog(sld);
		ChangeCharacterAddressGroup(sld, "Kapstervil_tavern", "sit", "sit_base4");
		
		sld = GetCharacter(NPC_GenerateCharacter("PZ_Kapstervil_Alkash_2", "citiz_"+(rand(39)+1), "man", "man", 5, FRANCE, 14, false, ""));
		SaveCurrentNpcQuestDateParam(sld, "LifeTimeCreate");
		LAi_SetSitType(sld);
		LAi_CharacterDisableDialog(sld);
		ChangeCharacterAddressGroup(sld, "Kapstervil_tavern", "sit", "sit_front4");
		
		sld = GetCharacter(NPC_GenerateCharacter("PZ_Kapstervil_Alkash_3", "citiz_"+(rand(39)+1), "man", "man", 5, FRANCE, 14, false, ""));
		SaveCurrentNpcQuestDateParam(sld, "LifeTimeCreate");
		LAi_SetSitType(sld);
		LAi_CharacterDisableDialog(sld);
		ChangeCharacterAddressGroup(sld, "Kapstervil_tavern", "sit", "sit2");
	}
	
	else if (sQuestName == "PZ_Kapstervil_Start_2") {
		LAi_Fade("PZ_Kapstervil_Start_3", "");
	}
	
	else if (sQuestName == "PZ_Kapstervil_Start_3") {
		locCameraFromToPos(115.50, 1.92, -162.72, true, 126.00, 7.00, -164.00);
	}
	
	else if (sQuestName == "PZ_Kapstervil_OstavlyaemZapisku") {
		DoQuestReloadToLocation("Kapstervil_church", "reload", "reload1", "PZ_Kapstervil_OstavlyaemZapisku_1");
	}
	
	else if (sQuestName == "PZ_Kapstervil_OstavlyaemZapisku_1") {
		LAi_SetActorType(pchar);
		LAi_ActorGoToLocator(pchar, "goto", "goto2", "PZ_Kapstervil_OstavlyaemZapisku_2", -1);
		locCameraFlyToPositionLookToHero(0.01, 1.6, 1.30, 4.50, 1.5, -2.20, -1, 5000/GetDeltaTime());
		Pchar.FuncCameraFly = "PZ_Kapstervil_OstavlyaemZapisku_1_1";
	}
	
	else if (sQuestName == "PZ_Kapstervil_OstavlyaemZapisku_2") {
		LAi_SetActorType(pchar);
		LAi_ActorAnimation(pchar, "Barman_idle", "PZ_Kapstervil_OstavlyaemZapisku_3", 3);
	}
	
	else if (sQuestName == "PZ_Kapstervil_OstavlyaemZapisku_3") {
		//Log_Info("Вы оставили письмо");
		PlaySound("interface\notebook.wav");
		DoQuestCheckDelay("PZ_Kapstervil_OstavlyaemZapisku_4", 1.5);
		LAi_FadeLong("PZ_Kapstervil_OstavlyaemZapisku_3_1", "");
	}
	
	else if (sQuestName == "PZ_Kapstervil_OstavlyaemZapisku_3_1") {
		locCameraResetState();
		locCameraFromToPos(0.47, 1.91, 0.37, true, 6.54, -0.50, 0.16);
		locCameraSleep(false);
	}
	
	else if (sQuestName == "PZ_Kapstervil_OstavlyaemZapisku_4") {
		LAi_SetActorType(pchar);
		LAi_ActorGoToLocator(pchar, "reload", "reload1", "PZ_Kapstervil_OstavlyaemZapisku_5", -1);
	}
	
	else if (sQuestName == "PZ_Kapstervil_OstavlyaemZapisku_5") {
		LAi_SetStayType(pchar);
		SetCurrentTime(21, 00);
		RecalculateJumpTable();
		RefreshWeather();
		RefreshLandTime();
		pchar.GenQuest.FrameLockEsc = true;
		SetLaunchFrameFormParam(StringFromKey("Longway_24", NewStr()), "Reload_To_Location", 0, 4.0);
		SetLaunchFrameReloadLocationParam("Kapstervil_ExitTown", "goto", "goto7", "PZ_Kapstervil_VstrechaZhorzh_1");
		LaunchFrameForm();
	}
	
	else if (sQuestName == "PZ_Kapstervil_VstrechaZhorzh_1") {
		locCameraFromToPos(24.18, 1.50, -22.82, false, 16.40, 0.60, -19.15);
		sld = CharacterFromID("PZ_Kapstervil_priest");
		ChangeCharacterAddressGroup(sld, "Kapstervil_ExitTown", "goto", "goto8");
		LAi_SetActorType(sld);
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_Zhorzh_1";
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		
		DoQuestCheckDelay("PZ_Kapstervil_VstrechaZhorzh_2", 0.2);
	}
	
	else if (sQuestName == "PZ_Kapstervil_Jungle") {
		locCameraFromToPos(-1.95, 1.47, 15.20, false, -4.38, 0.10, 6.47);
		ResetSound();
		DoQuestCheckDelay("PZ_Kapstervil_Jungle_3", 0.5);
		
		for (i=11; i<=14; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("PZ_KapstervilBandit_"+i, "citiz_" + (rand(9) + 41), "man", "man", 5, PIRATE, 0, true, "pirate"));
			ChangeCharacterAddressGroup(sld, pchar.location, "rld",  "aloc"+i);
			LAi_SetActorType(sld);
			LAi_ActorTurnToLocator(sld, "goto", "goto1");
			LAi_SetHP(sld, 30.0, 30.0);
			sld.CantLoot = true;
			
			if (i==14)
			{
				sld.name = StringFromKey("Longway_25");
				sld.lastname = StringFromKey("Longway_26");
				sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
				sld.dialog.currentnode = "PZ_VorugaChurch_1";
				LAi_SetHP(sld, 100.0, 100.0);
				ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto4");
				LAi_ActorTurnToLocator(sld, "goto", "goto1");
			}
		}
		TeleportCharacterToPosAy(pchar, -4.25, 0.01, 15.87, 3.10);
	}
	
	else if (sQuestName == "PZ_Kapstervil_Jungle_3") {
		LAi_SetActorType(pchar);
		sld = CharacterFromID("PZ_KapstervilBandit_14");
		SetActorDialogAny2Pchar(sld.id, "", -1, 0.0);
		LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
	}
	
	else if (sQuestName == "PZ_VorugaChurch_win") {
		sld = CharacterFromID("PZ_KapstervilBandit_14");
		LAi_SetActorType(sld);
		LAi_ActorSetGroundSitMode(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		LAi_ActorWaitDialog(sld, pchar);
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_VorugaChurch_6";
	}
	
	else if (sQuestName == "PZ_VorugaChurch_win_2") {
		sld = CharacterFromID("PZ_KapstervilBandit_14");
		LAi_SetImmortal(sld, false);
		LAi_KillCharacter(sld);
		
		DoQuestCheckDelay("PZ_VorugaChurch_win_3", 2.0);
	}
	
	else if (sQuestName == "PZ_VorugaChurch_win_3") {
		DoQuestReloadToLocation("Kapstervil_Grot", "goto", "goto5", "PZ_Kapstervil_Grot");
	}
	
	else if (sQuestName == "PZ_Kapstervil_Grot") {
		LAi_SetCurHPMax(pchar);
		LAi_GetCharacterMaxEnergy(pchar);
		pchar.dialog.filename = "Quest\CompanionQuests\Longway.c";
		pchar.dialog.currentnode = "PZ_Kapstervil_GrotSoldiers_0";
		LAi_ActorSelfDialog(pchar, "pchar_back_to_player");
	}
	
	else if (sQuestName == "PZ_Kapstervil_Grot_1") {
		pchar.dialog.filename = "Quest\CompanionQuests\Longway.c";
		pchar.dialog.currentnode = "PZ_Kapstervil_GrotSoldiers_1";
		LAi_ActorSelfDialog(pchar, "pchar_back_to_player");
	}
	
	else if (sQuestName == "PZ_Kapstervil_Grot_2") {
		locCameraFromToPos(6.16, 2.54, -0.40, true, -0.59, -0.40, -0.80);
		DoQuestCheckDelay("PZ_Kapstervil_Grot_3", 1.5);
	}
	
	else if (sQuestName == "PZ_Kapstervil_Grot_3") {
		sld = CharacterFromID("PZ_Kapstervil_GrotSoldier_1");
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_Kapstervil_GrotSoldiers_3";
		LAi_SetActorType(sld);
		LAi_ActorDialogNow(sld, Pchar, "", -1);
		locCameraSleep(true);
	}
	
	else if (sQuestName == "PZ_Kapstervil_Grot_4") {
		sld = CharacterFromID("PZ_Kapstervil_GrotSoldier_2");
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_Kapstervil_GrotSoldiers_5";
		LAi_SetActorType(sld);
		LAi_ActorDialogNow(sld, Pchar, "", -1);
	}
	
	else if (sQuestName == "PZ_Kapstervil_Grot_5") {
		sld = CharacterFromID("PZ_Kapstervil_GrotSoldier_1");
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_Kapstervil_GrotSoldiers_7";
		LAi_SetActorType(sld);
		LAi_ActorDialogNow(sld, Pchar, "", -1);
	}
	
	else if (sQuestName == "PZ_Kapstervil_Grot_5_1") {
		EndQuestMovie();
		InterfaceStates.Buttons.Save.enable = false;
		locCameraSleep(false);
		locCameraToPos(5.40, 2.60, 9.20, true);
		locCameraTarget(PChar);
		locCameraFollow();
		LAi_SetActorType(pchar);
		
		pchar.dialog.filename = "Quest\CompanionQuests\Longway.c";
		pchar.dialog.currentnode = "PZ_Kapstervil_GrotSoldiers_9";
		LAi_ActorSelfDialog(pchar, "pchar_back_to_player");
	}
	
	else if (sQuestName == "PZ_Kapstervil_Grot_6") {
		LAi_SetActorType(pchar);
		DoQuestCheckDelay("PZ_Kapstervil_SecondVstrechaZhorzh", 1.5);
	}
	
	else if (sQuestName == "PZ_Kapstervil_SecondVstrechaZhorzh") {
		LAi_SetStayType(pchar);
		SetCurrentTime(21, 00);
		RecalculateJumpTable();
		RefreshWeather();
		RefreshLandTime();
		
		pchar.GenQuest.FrameLockEsc = true;
		SetLaunchFrameFormParam(StringFromKey("Longway_27", NewStr()), "Reload_To_Location", 0, 4.0);
		SetLaunchFrameReloadLocationParam("Kapstervil_ExitTown", "goto", "goto7", "PZ_Kapstervil_SecondVstrechaZhorz_1");
		LaunchFrameForm();
	}
	
	else if (sQuestName == "PZ_Kapstervil_SecondVstrechaZhorz_1") {
		StartQuestMovie(true, false, true);
		locCameraFromToPos(24.18, 1.50, -22.82, false, 16.40, 0.60, -19.15);
		sld = CharacterFromID("PZ_Kapstervil_priest");
		ChangeCharacterAddressGroup(sld, "Kapstervil_ExitTown", "goto", "goto8");
		LAi_SetActorType(sld);
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_Zhorzh_11";
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	
	else if (sQuestName == "PZ_Kapstervil_PoiskZvezda") {
		LAi_SetCurHPMax(pchar);
		LAi_GetCharacterMaxEnergy(pchar);
		LAi_SetPlayerType(pchar);
		chrDisableReloadToLocation = true;
		
		sld = CharacterFromID("PZ_Kapstervil_priest");
		ChangeCharacterAddressGroup(sld, "Kapstervil_Church", "barmen", "bar1");
		LAi_CharacterDisableDialog(sld);
		
		sld = GetCharacter(NPC_GenerateCharacter("PZ_Kapstervil_Kurier", "citiz_7", "man", "man", sti(pchar.rank), FRANCE, 0, false, "quest"));
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_Kapstervil_Kurier_1";
		ChangeCharacterAddressGroup(sld, "Kapstervil", "goto", "goto5");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	
	else if (sQuestName == "PZ_Kapstervil_ChitaemPismo") {
		LAi_SetActorType(pchar);
		pchar.dialog.filename = "Quest\CompanionQuests\Longway.c";
		pchar.dialog.currentnode = "PZ_Kapstervil_ChitaemPismo_Dialog";
		LAi_ActorSelfDialog(pchar, "pchar_back_to_player");
	}
	
	else if (sQuestName == "PZ_CreateTerunyi") {
		LAi_CharacterDisableDialog(characterFromID("PZ_Kapstervil_tavernkeeper"));
		
		sld = GetCharacter(NPC_GenerateCharacter("PZ_MathieuTerunyi", "trader_14", "man", "man", 1, FRANCE, -1, false, "quest"));
		sld.name = StringFromKey("Longway_28");
		sld.lastname = StringFromKey("Longway_29");
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_Terunyi1";
		ChangeCharacterAddressGroup(sld, "Kapstervil_Store", "goto", "goto3");
		LAi_SetStayType(sld);
		AddLandQuestMark(sld, "questmarkmain");
	}
	
	else if (sQuestName == "PZ_TeleportToPier") {
		AddMoneyToCharacter(pchar, 5000);
		
		LAi_SetStayType(pchar);
		SetCurrentTime(12, 00);
		RecalculateJumpTable();
		RefreshWeather();
		RefreshLandTime();
		
		pchar.GenQuest.FrameLockEsc = true;
		SetLaunchFrameFormParam(StringFromKey("Longway_30", NewStr()), "Reload_To_Location", 0, 4);
		SetLaunchFrameReloadLocationParam("Kapstervil", "reload", "reload1_back", "PZ_TerunyiTalk");
		LaunchFrameForm();
	}
	
	else if (sQuestName == "PZ_TerunyiTalk") {
		sld = characterFromID("PZ_MathieuTerunyi");
		sld.dialog.currentnode = "PZ_Terunyi4";
		ChangeCharacterAddressGroup(sld, "Kapstervil", "goto", "goto15");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	
	else if (sQuestName == "PZ_Flashback_Final_1") {
		DeleteAttribute(pchar, "GenQuest.CabinLock");
		Sea_CabinStartNow();
		DoQuestCheckDelay("PZ_Flashback_Final_2", 1.8);
	}
	
	else if (sQuestName == "PZ_Flashback_Final_2") {
		chrDisableReloadToLocation = true;
		sld = CharacterFromID("Longway");
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_Longway_PosleRasskaza21";
		ChangeCharacterAddressGroup(sld, PChar.location, "rld", "loc1");
		LAi_SetActorType(pchar);
		LAi_SetActorType(sld);
		SetActorDialogAny2Pchar(sld.id, "", 0, 0.0);
		LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 0.0);
		LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 0.0);
	}
	
	else if (sQuestName == "PZ_LongwayUhoditIzKauty") {
		sld = CharacterFromID("Longway");
		LAi_SetOfficerType(sld);
		sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
		sld.Dialog.CurrentNode = "Longway_officer";
		ChangeCharacterAddressGroup(sld, "none", "", "");
	}
	
	else if (sQuestName == "PZ_HelenaOrAlonso") {
		if (GetCharacterIndex("Helena") != -1 && CheckPassengerInCharacter(pchar, "Helena"))
		{
			sld = CharacterFromID("Helena");
			ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Helena_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		}
		else
		{
			sld = GetCharacter(NPC_GenerateCharacter("Alonso", "Alonso", "man", "man", sti(pchar.rank), pchar.nation, 0, true, "soldier"));
			sld.name = StringFromKey("Longway_1");
			sld.lastname = StringFromKey("Longway_2");
			ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Alonso_11";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			sld.location = "None";
		}
	}
	
	else if (sQuestName == "PZ_PoiskBanten_2") {
		if (GetCharacterIndex("Helena") != -1 && CheckPassengerInCharacter(pchar, "Helena"))
		{
			sld = CharacterFromID("Helena");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Helena_5";
			LAi_SetActorType(npchar);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		}
		else
		{
			sld = CharacterFromID("Alonso");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Alonso_15";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		}
	}
	
	else if (sQuestName == "PZ_Banten_PlyazhKapster") {
		DeleteQuestCondition("PZ_Banten_PlyazhKapster_Proval");
		QuestCloseSeaExit();
		
		PChar.quest.PZ_Banten_Mayak4.win_condition.l1 = "location";
		PChar.quest.PZ_Banten_Mayak4.win_condition.l1.location = "Mayak4";
		PChar.quest.PZ_Banten_Mayak4.win_condition = "PZ_Banten_Mayak4";
		
		sld = &Locations[FindLocation("Mayak4")];
		sld.locators_radius.goto.goto31 = 2.5;
		LAi_LocationFightDisable(&Locations[FindLocation("Mayak4")], true);
		
		DeleteAttribute(pchar, "questTemp.PZ_BasTerTurma");
		DelLandQuestMarkToPhantom();
	}
	
	else if (sQuestName == "PZ_Banten_PlyazhKapster_Proval") {
		DeleteQuestCondition("PZ_Banten_PlyazhKapster");
		AddQuestRecord("PZ", "16");
		CloseQuestHeader("PZ");
	}
	
	else if (sQuestName == "PZ_Banten_Mayak4") {
		chrDisableReloadToLocation = true;
		
		sld = GetCharacter(NPC_GenerateCharacter("PZ_BasTerJailOff_Clone", "off_fra_2", "man", "man", sti(pchar.rank), FRANCE, -1, true, "soldier"));
		sld.name = StringFromKey("Longway_31");
		sld.lastname = StringFromKey("Longway_32");
		ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto2");
		LAi_SetActorType(sld);
		TeleportCharacterToPosAy(sld, 0.97, 29.00, -9.06, 1.50);
						
		sld = GetCharacter(NPC_GenerateCharacter("PZ_Neznakomets", "officer_1", "man", "man", sti(pchar.rank), FRANCE, -1, true, "soldier"));
		sld.name = StringFromKey("Longway_33");
		sld.lastname = StringFromKey("Longway_34");
		ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto2");
		LAi_SetActorType(sld);
		TeleportCharacterToPosAy(sld, 2.54, 29.00, -8.67, -2.00);
		
		sld = CharacterFromID("Longway");
		ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto28");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 3, 0);
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_Longway_21";
	}
	
	else if (sQuestName == "PZ_MayakPodslushivanie") {
		LAi_SetStayType(pchar);
		pchar.questTemp.NoFast = true;
		StartQuestMovie(true, false, true);
		SetCameraDialogMode(CharacterFromID("PZ_BasTerJailOff_Clone"));
		locCameraFlyToPositionLookToHero(-24.56, 8.19, -5.66, 1.91, 31.11, -13.72, 1, 12000/GetDeltaTime());
		Pchar.FuncCameraFly = "PZ_MayakPodslushivanie_2";
	}
	
	else if (sQuestName == "PZ_MayakPodslushivanie_3") {
		sld = CharacterFromID("PZ_Neznakomets");
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_MayakPodslushivanie_Dialog_1";
		LAi_SetActorType(sld);
		LAi_ActorDialogNow(sld, Pchar, "", -1);
		locCameraSleep(true);
	}
	
	else if (sQuestName == "PZ_MayakPodslushivanie_win") {
		sld = CharacterFromID("PZ_BasTerJailOff_Clone");
		LAi_SetActorType(sld);
		LAi_ActorSetGroundSitMode(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		LAi_ActorWaitDialog(sld, pchar);
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_Mayak_KomendantSidit_1";
	}
	
	else if (sQuestName == "PZ_Mayak_Longway") {
		sld = CharacterFromID("Longway");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_Longway_25";
	}
	
	else if (sQuestName == "CameraReset") {
		locCameraTarget(PChar);
		locCameraFollow();
	}
	
	// Этап 4, Обманчивая Звезда
	else if (sQuestName == "PZ_Etap4_Start") {
		chrDisableReloadToLocation = true;
		LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], true);
		
		for (i=1; i<=6; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("PZ_PoterpKrushenie_"+i, "prizon_"+(rand(7)+1), "man", "man_B", sti(pchar.rank), PIRATE, -1, false, "marginal"));
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto3");
			if (i==1)
			{
				sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
				sld.dialog.currentnode = "PZ_PoterpKrushenie_1";
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else LAi_ActorFollow(sld, pchar, "", -1);
		}
	}
	
	else if (sQuestName == "PZ_Beliz_PoterpKrushenie") {
		chrDisableReloadToLocation = true;
		pchar.GenQuest.CannotWait = true; // временно
		LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], true);
		for (i=1; i<=6; i++)
		{
			sld = CharacterFromID("PZ_PoterpKrushenie_"+i);
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, pchar.location, "quest",  "quest1");
			if (i==1)
			{
				sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
				sld.dialog.currentnode = "PZ_PoterpKrushenie_11";
				LAi_ActorDialog(sld, pchar, "", 5, 0);
			}
			else LAi_ActorFollow(sld, pchar, "", -1);
		}
	}
	
	// это если отказались "подвезти" крушенцев
	else if (sQuestName == "PZ_Beliz_QuestCitizenDialog") {
		chrDisableReloadToLocation = true;
		pchar.GenQuest.CannotWait = true; // временно 
		LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], true);
		
		sld = GetCharacter(NPC_GenerateCharacter("PZ_BelizZhitelNovosti", "citiz_4", "man", "man", 1, ENGLAND, 0, false, "quest"));
		ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto5");
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_BelizZhitelNovosti_1";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	
	// провал квеста, если где-то шлялись месяц
	else if (sQuestName == "PZ_BelizFail") {
		CloseQuestHeader("PZ");
		
		DeleteQuestCondition("PZ_Beliz_PoterpKrushenie");
		DelMapQuestMarkCity("Beliz");
	}
	
	else if (sQuestName == "PZ_BelizPrisonSoldierDialog") {
		LAi_SetStayType(pchar);
		
		sld = GetCharacter(NPC_GenerateCharacter("PZ_BelizPrisonQuestSoldier", "sold_eng_" + (rand(7) + 1), "man", "man", 1, ENGLAND, -1, true, "soldier"));
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_BelizPrisonQuestSoldier1";
		ChangeCharacterAddressGroup(sld, "Beliz_prison", "goto", "goto25");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 2, 0);
		
		DoQuestCheckDelay("PZ_BelizPrisonSoldierDialog_2", 1.0);
	}
	
	else if (sQuestName == "PZ_BelizPrisonSoldierDialog_2") {
		CharacterTurnToLoc(pchar, "goto", "goto25");
	}
	
	else if (sQuestName == "PZ_BelizPrisonLongway_UvodyatNaKazn") {
		LAi_Fade("PZ_BelizPrisonLongway_UvodyatNaKazn_2", "");
		LAi_SetStayType(pchar);
		CharacterTurnToLoc(pchar, "goto", "goto25");
	}
	
	else if (sQuestName == "PZ_BelizPrisonLongway_UvodyatNaKazn_2") {
		sld = characterFromID("PZ_MatthewLutter");
		ChangeCharacterAddressGroup(sld, "Beliz_prison", "goto", "goto25");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocation(sld, "reload", "reload1", "", "", "", "", -1);
		LAi_SetImmortal(sld, true);
		sld.lifeday = 0;
		LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
		
		sld = characterFromID("PZ_BelizPrisonQuestSoldier");
		ChangeCharacterAddressGroup(sld, "Beliz_prison", "goto", "goto25");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocation(sld, "reload", "reload1", "", "", "", "", -1);
		LAi_SetImmortal(sld, true);
		sld.lifeday = 0;
		LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
		
		DoQuestCheckDelay("PZ_BelizPrisonLongwayDialog", 1.5);
	}
	
	else if (sQuestName == "PZ_BelizPrisonLongwayDialog") {
		sld = CharacterFromID("Longway");
		if (!CharacterIsHere("Longway"))
		{
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"));
		}
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_Longway_35";
	}
	
	else if (sQuestName == "PZ_BelizPrisonLongwayBack") {
		LAi_SetPlayerType(pchar);
		Return_LongwayOfficer();
		pchar.questTemp.Beliz.AskForLatterAndSotta = true; // флаг для расспроса горожан и пьяниц
	}
	
	else if (sQuestName == "PZ_LongwayBelizDialog") {
		if (sti(pchar.questTemp.PZ_BelizAskCitizens) >= 3)
		{
			DeleteAttribute(pchar, "questTemp.Beliz.AskForLatterAndSotta");
			
			sld = CharacterFromID("Longway");
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"));
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Longway_37";
		}
	}
	
	else if (sQuestName == "PZ_LongwayBelizDialogBack") {
		AddQuestRecord("PZ", "19");
		Return_LongwayOfficer();
		
		sld = characterFromID("Charles_Priest");
		sld.name = StringFromKey("Longway_35");
		sld.lastname = StringFromKey("Longway_36");
		
		PChar.quest.PZ_OhotaNaZvezdu_Kapstervil.win_condition.l1 = "location";
		PChar.quest.PZ_OhotaNaZvezdu_Kapstervil.win_condition.l1.location = "Nevis";
		PChar.quest.PZ_OhotaNaZvezdu_Kapstervil.win_condition = "PZ_OhotaNaZvezdu_Kapstervil";
		AddMapQuestMarkIsland("Nevis", false);
		
		PChar.quest.PZ_OhotaNaZvezdu_Yamaika.win_condition.l1 = "location";
		PChar.quest.PZ_OhotaNaZvezdu_Yamaika.win_condition.l1.location = "Jamaica";
		PChar.quest.PZ_OhotaNaZvezdu_Yamaika.win_condition = "PZ_OhotaNaZvezdu_Yamaika";
		AddMapQuestMarkIsland("Jamaica", false);
	}
	
	else if (sQuestName == "PZ_OhotaNaZvezdu_Kapstervil") {
		DeleteAttribute(pchar, "GenQuest.CannotWait");
		pchar.questTemp.PZ_OhotaNaZvezdu_Kapstervil = true;
		DeleteQuestCondition("PZ_OhotaNaZvezdu_Yamaika");
	
		pchar.GenQuest.CabinLock = true;
		Island_SetReloadEnableGlobal("Nevis", false);
		bQuestDisableMapEnter = true;
		DoQuestCheckDelay("PZ_OhotaNaZvezdu_2", 2.5);
		
		// Клон-корабль на Сент-Кристофере
		sld = GetCharacter(NPC_GenerateCharacter("PZ_EdgardoSotta_Clone", "Rodriges", "man", "man", sti(pchar.rank), FRANCE, -1, false, "soldier"));
		sld.name = StringFromKey("Longway_37");
		sld.lastname = StringFromKey("Longway_38");
		FantomMakeCoolSailor(sld, SHIP_GALEON_H, StringFromKey("Longway_39"), CANNON_TYPE_CANNON_LBS32, 90, 90, 90);
		sld.AlwaysFriend = true;
		sld.Abordage.Enable = false;
		sld.DontDeskTalk = true;
		sld.ShipHideImmortal = 1000;
		Group_FindOrCreateGroup("PZ_EdgardoShipClone");
		Group_SetType("PZ_EdgardoShipClone", "pirate");
		Group_AddCharacter("PZ_EdgardoShipClone", "PZ_EdgardoSotta_Clone");
		Group_SetGroupCommander("PZ_EdgardoShipClone", "PZ_EdgardoSotta_Clone");
		Group_SetTaskNone("PZ_EdgardoShipClone");
		Group_SetAddress("PZ_EdgardoShipClone", "Nevis", "IslandShips1", "ship_4");
	}
	
	else if (sQuestName == "PZ_OhotaNaZvezdu_Yamaika") {
		DeleteAttribute(pchar, "GenQuest.CannotWait");
		pchar.questTemp.PZ_OhotaNaZvezdu_Yamaika = true;
		DeleteQuestCondition("PZ_OhotaNaZvezdu_Kapstervil");
	
		pchar.GenQuest.CabinLock = true;
		Island_SetReloadEnableGlobal("Jamaica", false);
		bQuestDisableMapEnter = true;
		DoQuestCheckDelay("PZ_OhotaNaZvezdu_2", 2.5);
		
		// Клон-корабль на Ямайке
		sld = GetCharacter(NPC_GenerateCharacter("PZ_EdgardoSotta_Clone", "Rodriges", "man", "man", sti(pchar.rank), ENGLAND, -1, false, "soldier"));
		sld.name = StringFromKey("Longway_37");
		sld.lastname = StringFromKey("Longway_38");
		FantomMakeCoolSailor(sld, SHIP_GALEON_H, StringFromKey("Longway_39"), CANNON_TYPE_CANNON_LBS32, 90, 90, 90);
		sld.AlwaysFriend = true;
		sld.Abordage.Enable = false;
		sld.DontDeskTalk = true;
		sld.ShipHideImmortal = 1000;
		Group_FindOrCreateGroup("PZ_EdgardoShipClone");
		Group_SetType("PZ_EdgardoShipClone", "pirate");
		Group_AddCharacter("PZ_EdgardoShipClone", "PZ_EdgardoSotta_Clone");
		Group_SetGroupCommander("PZ_EdgardoShipClone", "PZ_EdgardoSotta_Clone");
		Group_SetTaskNone("PZ_EdgardoShipClone");
		Group_SetAddress("PZ_EdgardoShipClone", "Jamaica", "IslandShips1", "ship_4");
	}
	
	else if (sQuestName == "PZ_OhotaNaZvezdu_2") {
		DeleteAttribute(pchar, "GenQuest.CabinLock");
		pchar.GenQuest.DontSetCabinOfficer = true;
		chrDisableReloadToLocation = true;
		Sea_CabinStartNow();
		DoQuestCheckDelay("PZ_OhotaNaZvezdu_3", 1.8);
	}
	
	else if (sQuestName == "PZ_OhotaNaZvezdu_3") {
		sld = CharacterFromID("Longway");
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_Longway_41";
		LAi_SetStayType(sld);
		ChangeCharacterAddressGroup(sld, PChar.location, "rld", "loc1");
		CharacterTurnByChr(sld, pchar);	
		AddLandQuestMark(sld, "questmarkmain");
	}
	
	else if (sQuestName == "PZ_GotovimShlupki_Buhta") {
		chrDisableReloadToLocation = true;
		InterfaceStates.Buttons.Save.enable = false;
		DeleteQuestCondition("PZ_ZvezdaUhodimNaGlobalkru_Proval");
		pchar.questTemp.PZ_GotovimShlupki = true;
		LAi_SetStayType(pchar);
		sld = characterFromID("PZ_EdgardoSotta_Clone");
		sld.lifeday = 0;
		DoQuestCheckDelay("TalkSelf_Quest", 1.0);
	}
	
	else if (sQuestName == "PZ_ShturmZvezdy") {
		SetCurrentTime(24, 00);
		RecalculateJumpTable();
		RefreshWeather();
		RefreshLandTime();
		LAi_LocationDisableOfficersGen("Deck_Galeon_Ship", false);
		LAi_LocationFightDisable(&Locations[FindLocation("Deck_Galeon_Ship")], false);
		pchar.GenQuest.FrameLockEsc = true;
		SetLaunchFrameFormParam(StringFromKey("Longway_40"), "Reload_To_Location", 0, 4.0);
		SetLaunchFrameReloadLocationParam("Deck_Galeon_Ship", "reload", "reload2", "PZ_ShturmZvezdy_Rasstavlyaem");
		LaunchFrameForm();
	}
	
	else if (sQuestName == "PZ_ShturmZvezdy_Rasstavlyaem") {
		PlaySound("interface\" + LanguageGetLanguage() + "\_GTBoard2.wav");
		PlaySound("interface\abordage_wining.wav");
		DoQuestFunctionDelay("Terrapin_SetMusic", 1.2);
		bDisableCharacterMenu = true;
		
		// наши мушкетёры
		for (i = 1; i <= 4; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("PZ_MorningStar_OurMush" + i, "mush_ctz_" + (4 + rand(2)), "man", "mushketer", 15, FRANCE, 0, false, "soldier"));
			FantomMakeCoolFighter(sld, 15, 10, 70, "", "mushket1", "cartridge", 140);
			switch (i)
			{
				case 1:
					ChangeCharacterAddressGroup(sld, "Deck_Galeon_Ship", "quest", "liga1");
				break;
				
				case 2:
					ChangeCharacterAddressGroup(sld, "Deck_Galeon_Ship", "quest", "liga2");
				break;
				
				case 3:
					ChangeCharacterAddressGroup(sld, "Deck_Galeon_Ship", "quest", "liga4");
				break;
				
				case 4:
					ChangeCharacterAddressGroup(sld, "Deck_Galeon_Ship", "quest", "liga5");
				break;
			}
			sld.MusketerDistance = 0;
			sld.CantLoot = true;
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
		
		// мушкетёры врага
		for (i = 1; i <= 4; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("PZ_MorningStar_EnemyMush" + i, "mush_ctz_" + (rand(2) + 7), "man", "mushketer", 15, PIRATE, 0, false, "soldier"));
			FantomMakeCoolFighter(sld, 15, 10, 70, "", "mushket1", "cartridge", 140);
			switch (i)
			{
				case 1:
					ChangeCharacterAddressGroup(sld, "Deck_Galeon_Ship", "goto", "aloc6");
				break;
				
				case 2:
					ChangeCharacterAddressGroup(sld, "Deck_Galeon_Ship", "goto", "aloc7");
				break;
				
				case 3:
					ChangeCharacterAddressGroup(sld, "Deck_Galeon_Ship", "goto", "aloc16");
				break;
				
				case 4:
					ChangeCharacterAddressGroup(sld, "Deck_Galeon_Ship", "goto", "aloc4");
				break;
			}
			sld.MusketerDistance = 0;
			sld.CantLoot = true;
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
			
		// наши "пехотинцы"
		for (i = 1; i <= 9; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("PZ_MorningStar_OurCrew" + i, "citiz_"+(rand(9) + 31), "man", "man", sti(pchar.rank), FRANCE, 0, true, "soldier"));
			LAi_SetWarriorType(sld);
			if (i < 8) ChangeCharacterAddressGroup(sld, "Deck_Galeon_Ship", "quest", "quest1");
			else ChangeCharacterAddressGroup(sld, "Deck_Galeon_Ship", "quest", "quest2");
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_SetHP(sld, 150.0, 150.0);
			sld.CantLoot = true;
		}
		
		// первая группа "пехотинцев" врага во главе со злым наёмником
		for (i = 1; i <= 6; i++)
		{
			if (i == 1) 
			{
				sld = GetCharacter(NPC_GenerateCharacter("PZ_MorningStar_EnemyCrewMercenary1" + i, "citiz_" + (rand(9) + 51), "man", "man", 20, PIRATE, 0, true, "quest"));
				ChangeCharacterAddressGroup(sld, "Deck_Galeon_Ship", "rld", "loc2");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_SetHP(sld, 200.0, 200.0);
				sld.CantLoot = true;
			}
			else
			{
				sld = GetCharacter(NPC_GenerateCharacter("PZ_MorningStar_EnemyCrew1_" + i, "citiz_" + (rand(9) + 41), "man", "man", sti(pchar.rank), PIRATE, 0, true, "soldier"));
				ChangeCharacterAddressGroup(sld, "Deck_Galeon_Ship", "goto", "goto2");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_SetHP(sld, 150.0, 150.0);
				sld.CantLoot = true;
			}
		}
		
		// вторая группа "пехотинцев" врага во главе со злым наёмником
		for (i = 1; i <= 6; i++)
		{
			if (i == 1) 
			{
				sld = GetCharacter(NPC_GenerateCharacter("PZ_MorningStar_EnemyCrewMercenary2" + i, "citiz_" + (rand(9) + 51), "man", "man", 20, PIRATE, 0, true, "quest"));
				ChangeCharacterAddressGroup(sld, "Deck_Galeon_Ship", "rld", "aloc8");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_SetHP(sld, 200.0, 200.0);
				sld.CantLoot = true;
			}
			else
			{
				sld = GetCharacter(NPC_GenerateCharacter("PZ_MorningStar_EnemyCrew2_" + i, "citiz_" + (rand(9) + 41), "man", "man", sti(pchar.rank), PIRATE, 0, true, "soldier"));
				ChangeCharacterAddressGroup(sld, "Deck_Galeon_Ship", "goto", "aloc8");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_SetHP(sld, 150.0, 150.0);
				sld.CantLoot = true;
			}
		}
		
		// третья группа "пехотинцев" врага во главе со злым наёмником
		for (i = 1; i <= 6; i++)
		{
			if (i == 1) 
			{
				sld = GetCharacter(NPC_GenerateCharacter("PZ_MorningStar_EnemyCrewMercenary3" + i, "citiz_" + (rand(9) + 51), "man", "man", 20, PIRATE, 0, true, "quest"));
				ChangeCharacterAddressGroup(sld, "Deck_Galeon_Ship", "rld", "loc1");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_SetHP(sld, 200.0, 200.0);
				sld.CantLoot = true;
			}
			else
			{
				sld = GetCharacter(NPC_GenerateCharacter("PZ_MorningStar_EnemyCrew3_" + i, "citiz_" + (rand(9) + 41), "man", "man", sti(pchar.rank), PIRATE, 0, true, "soldier"));
				ChangeCharacterAddressGroup(sld, "Deck_Galeon_Ship", "goto", "goto1");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_SetHP(sld, 150.0, 150.0);
				sld.CantLoot = true;
			}
		}
		
		LAi_SetPlayerType(pchar);
		LAi_SetFightMode(pchar, true);
		
		for(i = 1; i <= 3; i++)
		{
			idx = GetOfficersIndex(pchar, i);
			if(idx < 0) continue;
			sld = &Characters[idx];
			ChangeCharacterAddressGroup(sld, "Deck_Galeon_Ship", "quest", "liga"+i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
		sld = CharacterFromID("Longway");
		DeleteAttribute(sld, "OfficerImmortal");
		if(CheckAttribute(sld, "Health.HP")) DeleteAttribute(sld, "Health.HP");
		if(CheckAttribute(sld, "Health.maxHP")) DeleteAttribute(sld, "Health.maxHP");
		sTemp = "RestoreHealth_" + sld.index;
		if(CheckAttribute(PChar, "quest.RestoreHealth_" + sld.index)) PChar.quest.(sTemp).over = "Yes";
		ChangeCharacterAddressGroup(sld, "Deck_Galeon_Ship", "officers", "reload1_1");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "PZ_ZvezdaPobeda");
		
		SetShowTimer(100.0);
		DoQuestCheckDelay("PZ_ZvezdaPodkreplenie", 100.0);
		
		PChar.quest.PZ_ZvezdaLongwayMertv.win_condition.l1 = "NPC_Death";
		PChar.quest.PZ_ZvezdaLongwayMertv.win_condition.l1.character = "Longway";
		PChar.quest.PZ_ZvezdaLongwayMertv.win_condition = "PZ_ZvezdaLongwayMertv";
	}
	
	else if (sQuestName == "PZ_ZvezdaPobeda") {
		ClearAllLogStrings();
		Event("QuestDelayExit","sl", "", 0);
		DeleteAttribute(pchar, "showTimer");
		Log_Info(StringFromKey("Longway_41"));
		LAi_SetActorType(pchar);
		DoQuestCheckDelay("PZ_ZvezdaPobeda_2", 1.5);
	}
	
	else if (sQuestName == "PZ_ZvezdaPobeda_2") {
		LAi_Fade("PZ_ZvezdaPobeda_3", "");
	}
	
	else if (sQuestName == "PZ_ZvezdaPobeda_3") {
		TeleportCharacterToPosAy(pchar, -0.15, 4.68, -28.40, 3.10);
		
		sld = GetCharacter(NPC_GenerateCharacter("PZ_EdgardoSott", "Rodriges", "man", "man", sti(pchar.rank), SPAIN, -1, false, "soldier"));
		sld.name = StringFromKey("Longway_37");
		sld.lastname = StringFromKey("Longway_38");
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_Zvezda_DialogWithCapitan";
		FantomMakeCoolFighter(sld, sti(pchar.rank), 80, 80, "blade_20", "pistol4", "grapeshot", 0);
		ChangeCharacterAddressGroup(sld, PChar.location, "goto", "stand");
		LAi_SetActorType(sld);
		SetActorDialogAny2Pchar(sld.id, "", -1, 0.0);
		LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", -1);
		LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
		LAi_SetHP(sld, 400.0, 400.0);
		sld.CantLoot = true;
		
		for(i=1; i<=3; i++)
		{
			idx = GetOfficersIndex(pchar, i);
			if(idx < 0) continue;
			sld = &Characters[idx];
			ChangeCharacterAddressGroup(sld, "none", "", "");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
	}
	
	else if (sQuestName == "PZ_ZvezdaPodkreplenie") {
		ClearAllLogStrings();
		DeleteAttribute(pchar, "showTimer");
		Log_Info(StringFromKey("Longway_42"));
		pchar.questTemp.PZ.StrategicGoods = true;
		
		PlaySound("interface\abordage_wining.wav");
		PlaySound("Ambient\SEA\Ship_bell_Two.wav");
		
		for (i = 1; i <= 15; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("PZ_MorningStar_Reinforcement" + i, "citiz_" + (rand(9) + 41), "man", "man", sti(pchar.rank), PIRATE, -1, true, "soldier"));
			LAi_SetWarriorType(sld);
			if (i < 8) ChangeCharacterAddressGroup(sld, "Deck_Galeon_Ship", "quest", "quest3");
			else ChangeCharacterAddressGroup(sld, "Deck_Galeon_Ship", "quest", "quest4");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetHP(sld, 150.0, 150.0);
		}
	}
	
	else if (sQuestName == "PZ_ZvezdaLongwayMertv") {
		ClearAllLogStrings();
		Event("QuestDelayExit","sl", "", 0);
		DeleteAttribute(pchar, "showTimer");
		Log_Info(StringFromKey("Longway_43"));
		PlaySound("interface\notebook.wav");
		DoQuestCheckDelay("PZ_ZvezdaLongwayMertv_2", 3.0);
	}
	
	else if (sQuestName == "PZ_ZvezdaLongwayMertv_2") {
		if (CheckAttribute(pchar, "questTemp.PZ_OhotaNaZvezdu_Kapstervil"))
		{
			DoQuestReloadToLocation("Shore43", "reload", "sea", "PZ_ZvezdaLongwayMertv_3");
		}
		if (CheckAttribute(pchar, "questTemp.PZ_OhotaNaZvezdu_Yamaika"))
		{
			DoQuestReloadToLocation("Shore36", "reload", "sea", "PZ_ZvezdaLongwayMertv_3");
		}
	}
	
	else if (sQuestName == "PZ_ZvezdaLongwayMertv_3") {
		CloseQuestHeader("PZ");
		AddQuestRecord("PZ", "24");
		LAi_group_Delete("EnemyFight");
		chrDisableReloadToLocation = false;
		bDisableCharacterMenu = false;
		InterfaceStates.Buttons.Save.enable = true;
		for(i=1; i<=3; i++)
		{
			idx = GetOfficersIndex(pchar, i);
			if(idx < 0) continue;
			sld = &Characters[idx];
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			LAi_SetOfficerType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
	}
	
	else if (sQuestName == "PZ_ZvezdaUhodimNaGlobalkru_Proval") {
		CloseQuestHeader("PZ");
		AddQuestRecord("PZ", "20");
		DeleteQuestCondition("PZ_GotovimShlupki_Buhta");
	}
	
	else if (sQuestName == "PZ_SottaFight") {
		LAi_SetPlayerType(pchar);
		
		sld = characterFromID("PZ_EdgardoSott");
		LAi_group_MoveCharacter(sld, "EnemyFight");
		
		sld = GetCharacter(NPC_GenerateCharacter("PZ_Sotta_podmoga_1", "mercen_6", "man", "man", sti(pchar.rank), PIRATE, -1, false, "pirate"));
		sld.CantLoot = true;
		LAi_SetHP(sld, 60+MOD_SKILL_ENEMY_RATE*20, 60+MOD_SKILL_ENEMY_RATE*20); 
		GiveItem2Character(sld, "blade_20");
		EquipCharacterByItem(sld, "blade_20");
		ChangeCharacterAddressGroup(sld, pchar.location, "goto", "aloc16");
		TeleportCharacterToPos(sld, -0.03, 4.00, -25.93);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "PZ_CreateAnabelleLutter");
	}
	
	else if (sQuestName == "PZ_CreateAnabelleLutter") {
		LAi_SetActorType(pchar);
		DoQuestCheckDelay("PZ_CreateAnabelleLutter_2", 1.2);
	}
	
	else if (sQuestName == "PZ_CreateAnabelleLutter_2") {
		LAi_Fade("PZ_CreateAnabelleLutter_3", "");
	}
	
	else if (sQuestName == "PZ_CreateAnabelleLutter_3") {
		SetMusic("music_deck");
		
		LAi_SetStayType(pchar);
		TeleportCharacterToPosAy(pchar, 0.00, 4.00, -31.35, 0.00);
		
		sld = GetCharacter(NPC_GenerateCharacter("PZ_AnabelleLutter", "Women_22", "woman", "woman", 1, ENGLAND, -1, false, "quest"));
		sld.name = StringFromKey("Longway_44");
		sld.lastname = StringFromKey("Longway_45");
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_AnabelleLutter1";
		ChangeCharacterAddressGroup(sld, pchar.location, "goto", "aloc16");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		
		sld = CharacterFromID("Longway");
		ChangeCharacterAddressGroup(sld, PChar.location, "goto", "aloc16");
		LAi_SetActorType(sld);
		LAi_ActorFollow(sld, pchar, "", -1);
	}
	
	else if (sQuestName == "PZ_AnabelleGo") {
		LAi_SetStayType(pchar);
		CharacterTurnToLoc(pchar, "goto", "aloc16");
		sld = characterFromID("PZ_AnabelleLutter");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocation(sld, "goto", "aloc7", "none", "", "", "", -1);
		sld.lifeday = 0;
		DoQuestCheckDelay("PZ_LongwayCabinDialog", 2.0);
	}
	
	else if (sQuestName == "PZ_LongwayCabinDialog") {
		sld = CharacterFromID("Longway");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_Longway_47";
	}
	
	else if (sQuestName == "PZ_TeleportToShore") {
		LAi_SetPlayerType(pchar);
		AddQuestRecord("PZ", "22");
		
		chrDisableReloadToLocation = false;
		bDisableCharacterMenu = false;
		InterfaceStates.Buttons.Save.enable = true;
		
		if (CheckAttribute(pchar, "questTemp.PZ_OhotaNaZvezdu_Kapstervil"))
		{
			DoQuestReloadToLocation("Shore43", "reload", "sea", "");
		}
		if (CheckAttribute(pchar, "questTemp.PZ_OhotaNaZvezdu_Yamaika"))
		{
			DoQuestReloadToLocation("Shore36", "reload", "sea", "");
		}
		
		for(i=1; i<=3; i++)
		{
			idx = GetOfficersIndex(pchar, i);
			if(idx < 0) continue;
			sld = &Characters[idx];
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			LAi_SetOfficerType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
		
		DeleteQuestCondition("PZ_ZvezdaLongwayMertv");
		sld = characterFromID("Longway");
		sld.OfficerImmortal = true;
		sld.Health.HP       = 60.0;
		sld.Health.maxHP    = 60.0;
		SetCharacterPerk(sld, "ShipEscape");
		Return_LongwayOfficer();
		
		PChar.quest.PZ_LongwayCapstervilleDialog.win_condition.l1 = "location";
		PChar.quest.PZ_LongwayCapstervilleDialog.win_condition.l1.location = "Charles_town";
		PChar.quest.PZ_LongwayCapstervilleDialog.win_condition = "PZ_LongwayCapstervilleDialog";
		PChar.quest.PZ_ZvezdaNagrada.win_condition.l1 = "EnterToSea"
		PChar.quest.PZ_ZvezdaNagrada.win_condition = "PZ_ZvezdaNagrada";
		AddMapQuestMarkCity("Charles", false);
		DelMapQuestMarkIsland("Nevis");
		DelMapQuestMarkIsland("Jamaica");
	}
	
	else if (sQuestName == "PZ_ZvezdaNagrada") {
		if (!CheckAttribute(pchar, "questTemp.PZ.StrategicGoods"))
		{
			notification(StringFromKey("Longway_46"), "None");
			
			SetCharacterGoods(pchar, GOOD_SANDAL, GetCargoGoods(pchar, GOOD_SANDAL)+350);
			SetCharacterGoods(pchar, GOOD_SHIPSILK, GetCargoGoods(pchar, GOOD_SHIPSILK)+350);
			SetCharacterGoods(pchar, GOOD_ROPES, GetCargoGoods(pchar, GOOD_ROPES)+350);
			SetCharacterGoods(pchar, GOOD_OIL, GetCargoGoods(pchar, GOOD_OIL)+350);
			
			pchar.Ship.Crew.Quantity = sti(pchar.ship.Crew.Quantity) - 100 + rand(50);
		}
	}
	
	else if (sQuestName == "PZ_LongwayCapstervilleDialog") {
		chrDisableReloadToLocation = true;
		sld = CharacterFromID("Longway");
		ChangeCharacterAddressGroup(sld, "Charles_town", "goto", "goto15");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_Longway_53";
	}
		
	else if (sQuestName == "PZ_ToCapstervilleChurch") {
		chrDisableReloadToLocation = false;
		Return_LongwayOfficer();
		QuestSetCurrentNode("Charles_Priest", "Gravel1");
	}
	
	else if (sQuestName == "PZ_Etap5_Start") {
		LocatorReloadEnterDisable("Pirates_town", "reload3_back", false);
		
		if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie"))
		{
			sld = characterFromID("Dodson");
			ChangeCharacterAddressGroup(sld, "none", "", "");
		}
		else
		{
			sld = characterFromID("Terrax");
			ChangeCharacterAddressGroup(sld, "none", "", "");
		}
		
		// проверка следующая: "Сага" не провалена, Акула выжил на ОС, Элен - девушка ГГ и в офицерах
		if (!CheckAttribute(pchar, "questTemp.Sharlie.Hardcore_Tortuga") && (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) && (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")))
		{
			sld = characterFromID("Norman");
			LAi_RemoveLoginTime(sld);
			ChangeCharacterAddressGroup(sld, "none", "", "");
			
			sld = GetCharacter(NPC_GenerateCharacter("Norman_clone", "Norman_1", "man", "Norman", 45, PIRATE, -1, true, "quest"));
			sld.name 	= StringFromKey("Longway_47");
			sld.lastname = StringFromKey("Longway_48");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Norman1";
			sld.greeting = "Norman_1";
			sld.MultiFighter = 2.5;
			ChangeCharacterAddressGroup(sld, "Pirates_townhall", "sit", "sit1");
			TakeNItems(sld, "potion2", 20);
			TakeNItems(sld, "bullet", 100);
			TakeNItems(sld, "gunpowder", 100);
			GiveItem2Character(sld, "pistol5");
			GiveItem2Character(sld, "blade_29");
			EquipCharacterbyItem(sld, "pistol5"); 
			EquipCharacterbyItem(sld, "blade_29");
			LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "bullet");
			SetSPECIAL(sld, 10, 10, 10, 5, 5, 10, 5);
			LAi_SetHP(sld, 700, 700);
			SetSelfSkill(sld, 100, 100, 100, 100, 100);
			LAi_SetHuberType(sld);
		}
		
		if (!CheckAttribute(pchar, "questTemp.Saga.Late") && (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) && (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")))
		{
			// Элен
			sld = characterFromId("Helena");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_HelenaIslaTesoro1";
			ChangeCharacterAddressGroup(sld, "Pirates_townhall", "goto", "goto1");
			LAi_SetStayType(sld);
			LAi_CharacterEnableDialog(sld);
		}
		
		PChar.quest.PZ_Etap5_Start2.win_condition.l1 = "location";
		PChar.quest.PZ_Etap5_Start2.win_condition.l1.location = "Pirates_townhall";
		PChar.quest.PZ_Etap5_Start2.win_condition = "PZ_Etap5_Start2";
	}
	
	else if (sQuestName == "PZ_NormanBackToStreets") {
		sld = characterFromID("Norman_clone");
		sld.lifeday = 0;
		
		sld = characterFromID("Norman");
		ChangeCharacterAddressGroup(sld, "Pirates_town", "goto", "goto1");
		LAi_SetLoginTime(sld, 11.0, 20.0);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
		
		if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie"))
		{
			sld = characterFromId("Terrax");
			ChangeCharacterAddressGroup(sld, "Pirates_townhall", "sit", "sit1");
			sld.standUp = true; //вставать и нападать на врага
			LAi_SetHuberType(sld);
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			LAi_SetImmortal(sld, true);
			sld.watchBoxes = true; 
			
			sld = characterFromId("Vensan");
			sld.dialog.FileName = "Mayor\LaVega_Mayor.c";
			sld.dialog.currentnode = "I_know_you_good";
			sld.greeting = "town_pirate";
			ChangeCharacterAddressGroup(sld, "LaVega_townhall", "sit", "sit1");
			sld.standUp = true; //вставать и нападать на врага
			LAi_SetHuberType(sld);
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			LAi_SetImmortal(sld, true);
			sld.watchBoxes = true; 
		}
		else
		{
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "First time";
			ChangeCharacterAddressGroup(sld, "Pirates_townhall", "sit", "sit1");
			sld.standUp = true; //вставать и нападать на врага
			LAi_SetHuberType(sld);
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			LAi_SetImmortal(sld, true);
			sld.watchBoxes = true; 
		}
		if (!CheckAttribute(pchar, "questTemp.Saga.Late") && (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) && (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")))
		{
			// Элен
			sld = characterFromID("Helena");
			sld.Dialog.Filename = "Quest\Saga\Helena.c";
			sld.dialog.currentnode = "islatesoro";
			LAi_SetStayType(sld);
			LAi_CharacterEnableDialog(sld);
		}
	}
	
	else if (sQuestName == "PZ_Etap5_Start2") {
		PChar.quest.PZ_Etap5_Start3.win_condition.l1 = "location";
		PChar.quest.PZ_Etap5_Start3.win_condition.l1.location = "Pirates_town";
		PChar.quest.PZ_Etap5_Start3.win_condition = "PZ_Etap5_Start3";
		
		pchar.questTemp.PZ_DialogSvensonBlock = true;	// В диалоге со Свенсоном не будем говорить о Левассере
	}
	
	else if (sQuestName == "PZ_Etap5_Start3") {
		chrDisableReloadToLocation = true;
		
		if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
		{
			sld = characterFromId("Mary");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Mary_Sharptown1";
		}
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
		{
			sld = characterFromId("Helena");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Helena_Sharptown1";
		}
		ChangeCharacterAddressGroup(sld, "Pirates_town", "goto", "goto14");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	
	else if (sQuestName == "PZ_Etap5_NaverhuTavernBandits") {
		for (i=1; i<=3; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("PZ_NaverhuTavernBandits_"+i, "citiz_" + (rand(9) + 41), "man", "man", sti(pchar.rank), PIRATE, -1, true, "pirate"));
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, pchar.location, "quest",  "quest"+i);
			LAi_ActorTurnToCharacter(sld, pchar);
			if (i==1)
			{
				sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
				sld.dialog.currentnode = "PZ_Etap5_NaverhuTavernBandits_1";
				LAi_ActorDialog(sld, pchar, "", 0, 0);
			}
		}
	}
	
	else if (sQuestName == "PZ_Etap5_NaverhuTavernBandits_Win") {
		DoQuestCheckDelay("hide_weapon", 1.2);
		AddQuestRecord("PZ", "25");
		if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
		{
			AddQuestUserData("PZ", "sText", StringFromKey("Longway_49"));
			sld = CharacterFromID("Mary");
		}
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
		{
			AddQuestUserData("PZ", "sText", StringFromKey("Longway_50"));
			sld = CharacterFromID("Helena");
		}
		LAi_SetImmortal(sld, false);
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_MaryHelena_BitvaNaverhu_1";
		LAi_SetStayType(sld);
		AddLandQuestMark(sld, "questmarkmain");
		LAi_group_Delete("EnemyFight");
	}
	
	else if (sQuestName == "PZ_NeedToTortuga") {
		chrDisableReloadToLocation = false;
		if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) Return_MaryOfficer();
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) Return_HelenaOfficer();
		
		sld = characterFromID("Longway");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocation(sld, "reload", "reload1", "", "", "", "", 4);
		sld.location = "None";
		
		PChar.quest.PZ_TortugaStart.win_condition.l1 = "location";
		PChar.quest.PZ_TortugaStart.win_condition.l1.location = "Tortuga";
		PChar.quest.PZ_TortugaStart.win_condition = "PZ_TortugaStart";
		DelMapQuestMarkCity("Pirates");
		AddMapQuestMarkCity("Tortuga", false);
	}
	
	else if (sQuestName == "PZ_LongwayToPiratesShipyard") {
		if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) Return_MaryOfficer();
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) Return_HelenaOfficer();
		sld = characterFromID("Longway");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "PZ_LongwayToPiratesShipyard2", 4);
	}
	
	else if (sQuestName == "PZ_LongwayToPiratesShipyard2") {
		chrDisableReloadToLocation = false;
		sld = characterFromID("Longway");
		sld.dialog.currentnode = "PZ_Longway_WaitForShip1";
		ChangeCharacterAddressGroup(sld, "Pirates_shipyard", "goto", "goto1");
		LAi_SetWarriorType(sld);
	}
	
	else if (sQuestName == "PZ_LongwayToLaVegaTavern") {
		if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) Return_MaryOfficer();
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) Return_HelenaOfficer();
		sld = characterFromID("Longway");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "PZ_LongwayToLaVegaTavern2", 4);
	}
	
	else if (sQuestName == "PZ_LongwayToLaVegaTavern2") {
		chrDisableReloadToLocation = false;
		sld = characterFromID("Longway");
		sld.dialog.currentnode = "PZ_Longway_WaitForShip1";
		ChangeCharacterAddressGroup(sld, "LaVega_tavern", "table", "table4");
		LAi_SetWarriorType(sld);
	}
		
	else if (sQuestName == "PZ_TortugaStart") {
		pchar.GenQuest.CabinLock = true;
		Island_SetReloadEnableGlobal("Tortuga", false);
		bQuestDisableMapEnter = true;
		
		DoQuestCheckDelay("PZ_TortugaCabinTeleport", 2.5);
	}
	
	else if (sQuestName == "PZ_TortugaCabinTeleport") {
		DeleteAttribute(pchar, "GenQuest.CabinLock");
		pchar.GenQuest.DontSetCabinOfficer = true;
		chrDisableReloadToLocation = true;
		Sea_CabinStartNow();
		
		if (GetCharacterIndex("Helena") != -1 && CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && !CheckAttribute(pchar, "questTemp.PZ_TortugaStart"))
		{
			pchar.questTemp.questTemp.PZ_TortugaStart = true;
			sld = CharacterFromID("Helena");
			ChangeCharacterAddressGroup(sld, Get_My_Cabin(), "rld", "loc1");
			DoQuestCheckDelay("PZ_HelenaTortugaCabinDialog", 1.8);
		}
		
		if (GetCharacterIndex("Mary") != -1 && CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && !CheckAttribute(pchar, "questTemp.PZ_TortugaStart"))
		{
			pchar.questTemp.questTemp.PZ_TortugaStart = true;
			sld = CharacterFromID("Mary");
			ChangeCharacterAddressGroup(sld, Get_My_Cabin(), "rld", "loc1");
			DoQuestCheckDelay("PZ_MaryTortugaCabinDialog", 1.8);
		}
	}
	
	else if (sQuestName == "PZ_HelenaTortugaCabinDialog") {
		sld = CharacterFromID("Helena");
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_HelenaTortugaCabin_1";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	
	else if (sQuestName == "PZ_MaryTortugaCabinDialog") {
		sld = CharacterFromID("Mary");
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_MaryTortugaCabin_1";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	
	else if (sQuestName == "PZ_TortugaCabin_Exit") {
		DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
		Island_SetReloadEnableGlobal("Tortuga", true);
		bQuestDisableMapEnter = false;
		chrDisableReloadToLocation = false;
		
		AddQuestRecord("PZ", "27");
		
		if (GetCharacterIndex("Helena") != -1 && CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromID("Helena");
		if (GetCharacterIndex("Mary") != -1 && CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld = characterFromID("Mary");
		RemovePassenger(pchar, sld);
		LAi_SetActorType(sld);
		//LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
		
		pchar.questTemp.PZ.TortugaCitizensAsk = true; // флаг для расспроса горожан Тортуги
	}
	
	else if (sQuestName == "PZ_CreateRobertMartin") {
		DeleteAttribute(pchar, "questTemp.PZ.TortugaCitizensAsk");
		AddQuestRecord("PZ", "28");
		locations[FindLocation("Mayak6")].DisableEncounters = true;//энкаунтеры закрыть
		LAi_LocationFightDisable(&Locations[FindLocation("Mayak6")], true); // для особо умных
		AddGeometryToLocation("Mayak6", "smg");
		
		sld = GetCharacter(NPC_GenerateCharacter("PZ_RobertMartin", "Marten", "man", "man", 30, FRANCE, -1, true, "quest"));
		FantomMakeCoolFighter(sld, 30, 80, 80, "blade_19", "pistol5", "bullet", 150);
		sld.name = StringFromKey("Longway_51");
		sld.lastname = StringFromKey("Longway_52");
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_RobertMartin1";
		sld.greeting = "pirat_common";
		ChangeCharacterAddressGroup(sld, "Mayak6", "smugglers", "smugglerload");
		LAi_SetStayType(sld);
		AddLandQuestMark(sld, "questmarkmain");
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		for (i=1; i<=3; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("PZ_MayakPiraty_"+i, "citiz_" + (rand(9) + 41), "man", "man", sti(pchar.rank), PIRATE, -1, true, "pirate"));
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Mayak6", "smugglers",  "smuggler0"+i);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
		
		sld = GetCharacter(NPC_GenerateCharacter("PZ_RobertMartin_CloneMayakShip", "Marten", "man", "man", 30, FRANCE, -1, true, "quest"));
		sld.name = StringFromKey("Longway_51");
		sld.lastname = StringFromKey("Longway_52");
		LAi_SetImmortal(sld, true);
		FantomMakeCoolSailor(sld, SHIP_GALEON_L, StringFromKey("Longway_53"), CANNON_TYPE_CANNON_LBS16, 50, 50, 50);
		sld.AlwaysFriend = true;
		sld.ShipHideImmortal = 800;
		sld.DontDeskTalk = true;
		sld.Ship.Mode = "pirate";
		Group_FindOrCreateGroup("PZ_RM_Mir");
		Group_SetType("PZ_RM_Mir", "pirate");
		Group_AddCharacter("PZ_RM_Mir", "PZ_RobertMartin_CloneMayakShip");
		Group_SetGroupCommander("PZ_RM_Mir", "PZ_RobertMartin_CloneMayakShip");
		Group_SetAddress("PZ_RM_Mir", "Tortuga", "quest_ships", "reload_fort1");
	}
	
	else if (sQuestName == "PZ_LighthouseMartinGo") {
		AddQuestRecord("PZ", "29");
		if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) AddQuestUserData("PZ", "sText", StringFromKey("Longway_49"));
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) AddQuestUserData("PZ", "sText", StringFromKey("Longway_50"));
		
		sld = characterFromID("PZ_RobertMartin");
		LAi_SetActorType(sld);
		
		chrDisableReloadToLocation = false;
		
		if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
		{
			sld = CharacterFromID("Mary");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_MaryTortugaCabin_11";
		}
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
		{
			sld = CharacterFromID("Helena");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_HelenaTortugaCabin_11";
		}
		ChangeCharacterAddressGroup(sld, Get_My_Cabin(), "rld", "loc1");
		LAi_SetStayType(sld);
		AddLandQuestMark(sld, "questmarkmain");
		
		sld = &Locations[FindLocation("Tortuga_town")];
		sld.reload.l22.disable = false;
		
		sld = &Locations[FindLocation("Tortuga_brothelElite")];
		sld.id.label = "Brothel";
		LAi_LocationDisableOfficersGen("Tortuga_brothelElite", true);
		
		for (i=1; i<=4; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("PZ_ElitaShluha_"+i, "Women_"+i, "woman", "towngirl", 1, FRANCE, -1, false, "quest"));
			LAi_SetCitizenType(sld);
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "Tortuga_brothelElite", "goto", "goto"+i);
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_ElitaShluha_1";
		}
	}
	
	else if (sQuestName == "PZ_ElitaShluha_VKomnate") {
		DoQuestReloadToLocation("Tortuga_brothelElite_room1", "reload", "reload1", "PZ_ElitaShluha_VKomnate_2");
	}
	
	else if (sQuestName == "PZ_ElitaShluha_VKomnate_2") {
		chrDisableReloadToLocation = true;
		LAi_SetPlayerType(pchar);
		sld = CharacterFromID(pchar.PZ_ElitaShluha);
		ChangeCharacterAddressGroup(sld, "Tortuga_brothelElite_room1", "barmen", "stay");
		LAi_SetStayType(sld);
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_ElitaShluha_8";
		bDisableCharacterMenu = false;
	}
	
	else if (sQuestName == "PZ_ElitaShluha_Fuck") {
		LAi_SetPlayerType(pchar);
		
		WaitDate("", 0, 0, 0, 1, 0);
		sld = characterFromId(pchar.PZ_ElitaShluha);
		LAi_SetStayType(sld);
		sld.dialog.currentnode = "PZ_ElitaShluha_After";
		
		// кач от борделя
		if (CheckNPCQuestDate(pchar, "BrothelSex"))
		{
			if(IsEquipCharacterByArtefact(pchar, "totem_03")) 	
			{
				AddCharacterHealth(pchar, 10);
				AddCharacterMaxHealth(pchar, 1.0);
			}
			else AddCharacterHealth(pchar, 5);
			SetNPCQuestDate(pchar, "BrothelSex");
		}
		// изменение статусов
		ChangeCharacterComplexReputation(pchar,"nobility", -1);
		AddCharacterExpToSkill(pchar, "Leadership", 30);
		AddCharacterExpToSkill(pchar, "FencingS", -15);
		AddCharacterExpToSkill(pchar, "Pistol", -15);
	}
	
	else if (sQuestName == "PZ_TortugaKlemanLebren") {
		LAi_LocationFightDisable(loadedLocation, true);
		chrDisableReloadToLocation = true;
		
		sld = GetCharacter(NPC_GenerateCharacter("PZ_KlemanLebren", "citiz_56", "man", "man", sti(pchar.rank), PIRATE, -1, false, "quest"));
		sld.name = StringFromKey("Longway_54");
		sld.lastname = StringFromKey("Longway_55");
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_KlemanLebren_1";
		FantomMakeCoolSailor(sld, SHIP_FRIGATE_H, StringFromKey("Longway_56"), CANNON_TYPE_CANNON_LBS24, 80, 80, 80);
		GiveItem2Character(sld, "blade_07");
		EquipCharacterByItem(sld, "blade_07");
		GiveItem2Character(sld, "pistol4");
		EquipCharacterByItem(sld, "pistol4");
		LAi_SetHP(sld, 350.0, 350.0);
		SetSelfSkill(sld, 85, 85, 85, 85, 85);
		SetCharacterPerk(sld, "MusketsShoot");
		sld.AlwaysEnemy = true;
		sld.AlwaysSandbankManeuver = true;
		sld.DontRansackCaptain = true;
		UpgradeShipParameter(sld, "SpeedRate");//апгрейдить скорость
		UpgradeShipParameter(sld, "TurnRate");//манёвренность
		UpgradeShipParameter(sld, "HP");//корпус
		ChangeCharacterAddressGroup(sld, "Tortuga_town", "goto", "goto33");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 2, 0);
		
		// Клон-корабль в порту Тортуги
		sld = GetCharacter(NPC_GenerateCharacter("PZ_KlemanLebren_Clon", "citiz_56", "man", "man", sti(pchar.rank), FRANCE, -1, false, "quest"));
		sld.name = StringFromKey("Longway_54");
		sld.lastname = StringFromKey("Longway_55");
		FantomMakeCoolSailor(sld, SHIP_FRIGATE_H, StringFromKey("Longway_56"), CANNON_TYPE_CANNON_LBS24, 80, 80, 80);
		sld.AlwaysFriend = true;
		sld.Abordage.Enable = false;
		sld.DontDeskTalk = true;
		sld.ShipHideImmortal = 1000;
		Group_FindOrCreateGroup("PZ_ClementShipClon");
		Group_SetType("PZ_ClementShipClon", "pirate");
		Group_AddCharacter("PZ_ClementShipClon", "PZ_KlemanLebren_Clon");
		Group_SetGroupCommander("PZ_ClementShipClon", "PZ_KlemanLebren_Clon");
		Group_SetTaskNone("PZ_ClementShipClon");
		Group_SetAddress("PZ_ClementShipClon", "Tortuga", "IslandShips1", "ship_4");
	}
	
	else if (sQuestName == "PZ_TortugaRazgovorVKauteSDevushkoy") {
		pchar.GenQuest.CabinLock = true;
		Island_SetReloadEnableGlobal("Tortuga", false);
		bQuestDisableMapEnter = true;
		DoQuestCheckDelay("PZ_TortugaRazgovorVKauteSDevushkoy_2", 2.5);
	}
	
	else if (sQuestName == "PZ_TortugaRazgovorVKauteSDevushkoy_2") {
		DeleteAttribute(pchar, "GenQuest.CabinLock");
		pchar.GenQuest.DontSetCabinOfficer = true;
		chrDisableReloadToLocation = true;
		Sea_CabinStartNow();
		DoQuestCheckDelay("PZ_TortugaRazgovorVKauteSDevushkoy_3", 1.8);
	}
	
	else if (sQuestName == "PZ_TortugaRazgovorVKauteSDevushkoy_3") {
		if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) 
		{
			sld = CharacterFromID("Mary");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			if (CheckAttribute(pchar, "questTemp.PZ_PredupredilNashuDevushku")) sld.dialog.currentnode = "PZ_MaryRazgovorOBordeli_Good_1";
			else sld.dialog.currentnode = "PZ_MaryRazgovorOBordeli_Bad_8";
		}
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
		{
			sld = CharacterFromID("Helena");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			if (CheckAttribute(pchar, "questTemp.PZ_PredupredilNashuDevushku")) sld.dialog.currentnode = "PZ_HelenaRazgovorOBordeli_Good_1";
			else sld.dialog.currentnode = "PZ_HelenaRazgovorOBordeli_Bad_1";
		}
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	
	else if (sQuestName == "PZ_SetHeavyFrigate") {
		AddQuestRecord("PZ", "33");
		Island_SetReloadEnableGlobal("Hispaniola1", false);
		bQuestDisableMapEnter = true;
		
		Group_FindOrCreateGroup("ClementLebrunGroup");
		Group_AddCharacter("ClementLebrunGroup", "PZ_KlemanLebren");
		Group_SetType("ClementLebrunGroup", "pirate");
		Group_SetGroupCommander("ClementLebrunGroup", "PZ_KlemanLebren");
		Group_SetAddress("ClementLebrunGroup", "Hispaniola1", "quest_ships", "quest_ship_3");
		Group_SetTaskAttack("ClementLebrunGroup", PLAYER_GROUP);
		Group_LockTask("ClementLebrunGroup");
		
		pchar.quest.PZ_LebrenDeath.win_condition.l1 = "Group_Death";
		pchar.quest.PZ_LebrenDeath.win_condition.l1.group = "ClementLebrunGroup";
		pchar.quest.PZ_LebrenDeath.win_condition = "PZ_LebrenDeath";
		
		sld = CharacterFromID("PZ_KlemanLebren_Clon");	//Убираем клона на Тортуге
		sld.lifeday = 0;
	}
	
	else if (sQuestName == "PZ_LebrenDeath") {
		DoQuestCheckDelay("sea_victory", 1.5);
		
		Island_SetReloadEnableGlobal("Hispaniola1", true);
		bQuestDisableMapEnter = false;

		Group_DeleteGroup("ClementLebrunGroup");
		
		// парад записей в СЖ!
		if (CheckAttribute(pchar, "questTemp.PZ.HeavyFrigateAbordage")) 
		{
			AddQuestRecord("PZ", "34");
			if (CheckCharacterItem(pchar, "ClementLebrunJournal")) AddQuestUserData("PZ", "sText", StringFromKey("Longway_57"));
		}
		else
		{
			AddQuestRecord("PZ", "35");
		}
		
		//Islands[FindIsland("Hispaniola2")].alwaysStorm = true;
		Islands[FindIsland("Hispaniola2")].storm = true;
		PChar.quest.PZ_PoP_Rain.win_condition.l1 = "location";
		PChar.quest.PZ_PoP_Rain.win_condition.l1.location = "Hispaniola2";
		PChar.quest.PZ_PoP_Rain.win_condition = "PZ_PoP_Rain";
	}
	
	else if (sQuestName == "PZ_PoP_Rain") {
		SetCurrentTime(22, 00);
		RecalculateJumpTable();
		RefreshWeather();
		RefreshLandTime();

		pchar.ship.HP = sti(pchar.ship.HP) / 4;
		pchar.ship.masts.mast3 = 1;
		pchar.GenQuest.CabinLock = true;
		Island_SetReloadEnableGlobal("Hispaniola2", false);
		bQuestDisableMapEnter = true;
		DoQuestCheckDelay("PZ_PoP_Rain_2", 7.0);
	}
	
	else if (sQuestName == "PZ_PoP_Rain_2") {
		DeleteAttribute(pchar, "GenQuest.CabinLock");
		pchar.GenQuest.DontSetCabinOfficer = true;
		chrDisableReloadToLocation = true;
		Sea_CabinStartNow();
		DoQuestCheckDelay("PZ_PoP_Rain_3", 1.8);
		
		if (GetCharacterIndex("Tichingitu") != -1 && CheckPassengerInCharacter(pchar, "Tichingitu"))
		{
			sld = characterFromId("Tichingitu");
			ChangeCharacterAddressGroup(sld, Get_My_Cabin(), "reload", "reload1");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Tichingitu_11";
			LAi_SetActorType(sld);
			//sld.MusketerDistance = 10;
			return true;
		}
		sld = GetCharacter(NPC_GenerateCharacter("PZ_RandomSailor", "citiz_39", "man", "man", sti(pchar.rank), pchar.nation, 0, true, "soldier"));
		sld.name 	= StringFromKey("Longway_58");
		sld.lastname = StringFromKey("Longway_59");
		ChangeCharacterAddressGroup(sld, Get_My_Cabin(), "reload", "reload1");
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_Matros_1";
		LAi_SetActorType(sld);
	}
	
	else if (sQuestName == "PZ_PoP_Rain_3") {
		if (GetCharacterIndex("Tichingitu") != -1 && CheckPassengerInCharacter(pchar, "Tichingitu"))
		{
			sld = characterFromId("Tichingitu");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			return true;
		}
		sld = characterFromId("PZ_RandomSailor");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		sld.location = "None";
	}
	
	else if (sQuestName == "PZ_PoP_Rain_4") {
		chrDisableReloadToLocation = false;
		if (GetCharacterIndex("Tichingitu") != -1 && CheckPassengerInCharacter(pchar, "Tichingitu"))
		{
			sld = characterFromId("Tichingitu");
			RemovePassenger(pchar, sld);
		}
		PChar.quest.PZ_PoP_AnriTiboNaPirse.win_condition.l1 = "location";
		PChar.quest.PZ_PoP_AnriTiboNaPirse.win_condition.l1.location = "PortPax_town";
		PChar.quest.PZ_PoP_AnriTiboNaPirse.win_condition = "PZ_PoP_AnriTiboNaPirse";
		LAi_LocationDisableOfficersGen("PortPax_town", true);
		LAi_LocationFightDisable(&Locations[FindLocation("PortPax_town")], true);
		DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
		Island_SetReloadEnableGlobal("Hispaniola2", true);
		Island_SetReloadEnableLocal("Hispaniola2", "reload_2", false)
		Island_SetGotoEnableLocal("Hispaniola2", "reload_2", false);
		Island_SetReloadEnableLocal("Hispaniola2", "reload_3", false)
		Island_SetGotoEnableLocal("Hispaniola2", "reload_3", false);
		pchar.GenQuest.CannotWait = true;
		pchar.questTemp.TimeLock = true;
		pchar.Cheats.SeaTeleport = true;
	}
	
	else if (sQuestName == "PZ_PoP_AnriTiboNaPirse") {
		chrDisableReloadToLocation = true;
		bDisableCharacterMenu = true;
		InterfaceStates.Buttons.Save.enable = false;
		
		if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sld = characterFromId("Mary");
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sld = characterFromId("Helena");
		ChangeCharacterAddressGroup(sld, "PortPax_town", "reload", "reload1_back");
		LAi_SetActorType(sld);
		LAi_ActorFollow(sld, pchar, "", -1);
		
		sld = GetCharacter(NPC_GenerateCharacter("Tibo", "Tibo", "man", "man", 35, FRANCE, -1, true, "quest"));
		FantomMakeCoolFighter(sld, 35, 100, 100, "blade_18", "pistol4", "bullet", 250);
		GiveItem2Character(sld, "cirass7");
		EquipCharacterbyItem(sld, "cirass7");
		sld.name = StringFromKey("Longway_60");
		sld.lastname = StringFromKey("Longway_61");
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_AnriTibo_1";
		sld.greeting = "Tibo";
		sld.SaveItemsForDead = true;
		sld.DontClearDead = true;
		TakeNItems(sld, "potion2", 8);
		TakeNItems(sld, "potion3", 5);
		SetCharacterPerk(sld, "Energaiser");
		SetCharacterPerk(sld, "BasicDefense");
		SetCharacterPerk(sld, "BasicDefense");
		SetCharacterPerk(sld, "AdvancedDefense");
		SetCharacterPerk(sld, "CriticalHit");
		SetCharacterPerk(sld, "Tireless");
		SetCharacterPerk(sld, "HardHitter");
		SetCharacterPerk(sld, "Sliding");
		SetCharacterPerk(sld, "BladeDancer");
		SetCharacterPerk(sld, "SwordplayProfessional");
		SetCharacterPerk(sld, "Gunman");
		SetCharacterPerk(sld, "GunProfessional");
		ChangeCharacterAddressGroup(sld, "PortPax_town", "quest", "quest1");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 3, 0);
	}
	
	else if (sQuestName == "PZ_GoToTiboHouse") {
		sld = CharacterFromID("Tibo");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocator(sld, "reload", "houseF1", "PZ_TeleportToTiboHouse", -1);

		LAi_SetActorType(pchar);
		LAi_ActorFollow(pchar, CharacterFromID("Tibo"), "", -1);

		if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sld = CharacterFromID("Mary");
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sld = CharacterFromID("Helena");
		LAi_SetActorType(sld);
		LAi_ActorFollow(sld, CharacterFromID("Tibo"), "", -1);
	}
	
	else if (sQuestName == "PZ_TeleportToTiboHouse") {
		DoQuestReloadToLocation("PortPax_houseF1", "reload", "reload1", "PZ_TiboHouseDialog");
	}
	
	else if (sQuestName == "PZ_TiboHouseDialog") {
		LAi_SetStayType(pchar);
		TeleportCharacterToPosAy(pchar, -0.20, -0.79, 0.93, -0.00);
		
		if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sld = CharacterFromID("Mary");
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sld = CharacterFromID("Helena");
		ChangeCharacterAddressGroup(sld, "PortPax_houseF1", "barmen", "bar1");
		CharacterTurnAy(sld, 2.50);
		
		sld = characterFromID("Tibo");
		sld.dialog.currentnode = "PZ_AnriTibo_9";
		ChangeCharacterAddressGroup(sld, "PortPax_houseF1", "goto", "goto1");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0)
	}
	
	else if (sQuestName == "PZ_PoP_EscortToGuber") {
		for (i=1; i<=2; i++)
		{
			sld = CharacterFromID("PZ_PoP_Escort_"+i);
			ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto18");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocator(sld, "reload", "reload3", "PZ_TeleportToGuber", -1);
			sld.lifeday = 0;
		}
		LAi_SetActorType(pchar);
		LAi_ActorRunToLocator(pchar, "reload", "reload3", "PZ_TeleportToGuber", -1);
		
		if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sld = CharacterFromID("Mary");
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sld = CharacterFromID("Helena");
		RemovePassenger(pchar, sld);
		sld.location = "None";
		
		sld = CharacterFromID("Tibo");
		sld.location = "None";
	}
	
	else if (sQuestName == "PZ_TeleportToGuber") {
		DoQuestReloadToLocation("PortPax_townhall", "reload", "reload1", "PZ_PoPGuber");
	}
	
	else if (sQuestName == "PZ_PoPGuber") {
		bDisableCharacterMenu = false;
		InterfaceStates.Buttons.Save.enable = true;
		LAi_SetPlayerType(pchar);
		AddLandQuestMark(characterFromId("PortPax_Mayor"), "questmarkmain");
		AddQuestRecord("PZ", "36");
	}
	
	else if (sQuestName == "PZ_SharleBezhitObratno") {
		DoQuestReloadToLocation("PortPax_town", "reload", "reload3", "PZ_SharleBezhitObratno_2");
	}
	
	else if (sQuestName == "PZ_SharleBezhitObratno_2") {
		LAi_SetActorType(pchar);
		LAi_ActorRunToLocator(pchar, "reload", "houseF1", "PZ_SharleBezhitObratno_3", -1);
	}
	
	else if (sQuestName == "PZ_SharleBezhitObratno_3") {
		SetMusic("");
		DoQuestReloadToLocation("PortPax_houseF1", "reload", "reload1", "PZ_SharleBezhitObratno_4");
	}
	
	else if (sQuestName == "PZ_SharleBezhitObratno_4") {
		StartQuestMovie(true, false, true);
		locCameraFromToPos(-1.80, 1.13, -0.76, false, 0.85, -1.60, 2.29);
		TeleportCharacterToPosAy(pchar, -0.20, -0.79, 0.93, -0.00);
		LAi_SetStayType(pchar);
		pchar.questTemp.PZ_TiboUkralDevu = true;
		DoQuestCheckDelay("TalkSelf_Quest", 1.0);
		DoQuestCheckDelay("PZ_SharleBezhitObratno_4_1", 2.0);
		DoQuestCheckDelay("PZ_SharleBezhitObratno_5", 7.0);
		
		sld = GetCharacter(NPC_GenerateCharacter("PZ_PoP_TrupVKormane", "citiz_43", "man", "man", 1, PIRATE, 0, false, "quest"));
		ChangeCharacterAddressGroup(sld, PChar.location, "barmen", "bar1");
		TeleportCharacterToPosAy(sld, -0.98, -1.0, 2.89, 3.00);
		LAi_SetActorType(sld);
		LAi_ActorAnimation(sld, "lay_3", "", 7.5);
		LaunchBlood(sld, 0.1, true, "fight");
		LaunchBlood(sld, 0.1, true, "fight");
		
		if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
		{
			sld = GetCharacter(NPC_GenerateCharacter("PZ_PoP_TrupVKormane2", "citiz_24", "man", "man", 1, PIRATE, 0, false, "quest"));
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto2");
			TeleportCharacterToPosAy(sld, 0.31, -1.0, 1.07, -0.40);
			LAi_SetActorType(sld);
			LAi_ActorSetLayMode(sld);
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_PoP_TrupVKormane3", "citiz_41", "man", "man", 1, PIRATE, 0, false, "quest"));
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto1");
			LAi_SetActorType(sld);
			LAi_ActorSetLayMode(sld);
		}
	}
	
	else if (sQuestName == "PZ_SharleBezhitObratno_4_1") {
		locCameraSleep(false);
		locCameraFromToPos(-1.80, 1.13, -0.76, false, 0.85, -2.30, 2.29);
	}
	
	else if (sQuestName == "PZ_SharleBezhitObratno_5") {
		EndQuestMovie();
		SetLocationCapturedState("PortPax_town", true);
		DeleteAttribute(pchar, "questTemp.lockedMusic");
		DoQuestReloadToLocation("PortPax_town", "reload", "houseF1", "PZ_SharleBezhitObratno_6");
	}
	
	else if (sQuestName == "PZ_SharleBezhitObratno_6") {
		bDisableCharacterMenu = false;
		InterfaceStates.Buttons.Save.enable = true;
		LAi_SetPlayerType(pchar);
		sld = CharacterFromID("Longway");
		LAi_LoginInCaptureTown(sld, true);
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_Longway_71";
		ChangeCharacterAddressGroup(sld, "PortPax_town", "goto", "goto8");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0)
	}
	
	else if (sQuestName == "PZ_PoP_Pogonya") {
		DeleteAttribute(pchar, "Cheats.SeaTeleport");
		AddQuestRecord("PZ", "37");
		if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) AddQuestUserData("PZ", "sText", StringFromKey("Longway_49"));
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) AddQuestUserData("PZ", "sText", StringFromKey("Longway_50"));
		//Island_SetReloadEnableGlobal("Hispaniola2", false);
		//bQuestDisableMapEnter = true;
		PChar.quest.PZ_TeleportVTrum.win_condition.l1 = "Group_Death";
		PChar.quest.PZ_TeleportVTrum.win_condition.l1.group = "PZ_RM_Attack";
		PChar.quest.PZ_TeleportVTrum.win_condition = "PZ_TeleportVTrum";
	}
	
	else if (sQuestName == "PZ_TeleportVTrum") {
		DeleteAttribute(&Islands[FindIsland("Hispaniola2")], "alwaysStorm");
		DeleteAttribute(&Islands[FindIsland("Hispaniola2")], "storm");
		pchar.GenQuest.CabinLock = true;
		DoQuestCheckDelay("PZ_TeleportVTrum_2", 3.0);
		
		pchar.questTemp.PZ_PoP_More.ShipPos.x = pchar.ship.pos.x;
		pchar.questTemp.PZ_PoP_More.ShipPos.z = pchar.ship.pos.z;
		pchar.questTemp.PZ_PoP_More.ShipPos.Island = AISea.Island;
	}
	
	else if (sQuestName == "PZ_TeleportVTrum_2") {
		DeleteAttribute(pchar, "GenQuest.CabinLock");
		chrDisableReloadToLocation = true;
		
		CloneLocation("My_deck", "Clone_location");
		DeleteAttribute(&locations[FindLocation("Clone_location")], "boarding");
		DoQuestReloadToLocation("Clone_location", "reload", "reload_gundeck1", "PZ_DoprosRobertMartin_Trum");
	}
	
	else if (sQuestName == "PZ_DoprosRobertMartin_Trum") {
		sld = GetCharacter(NPC_GenerateCharacter("PZ_RobertMartinPlennik", "Marten", "man", "man", 30, FRANCE, -1, false, "quest"));
		sld.name = StringFromKey("Longway_51");
		sld.lastname = StringFromKey("Longway_52");
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_RobertMartin_12";
		ChangeCharacterAddressGroup(sld, "Clone_location", "goto","goto5");
		LAi_SetStayType(sld);
		sld.CantLoot = true;	
		LAi_SetPlayerType(pchar);
		
		//if(CheckAttribute (pchar, "IsMushketer")) SetMainCharacterToMushketer("", false);
		RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
		LAi_SetActorType(pchar);
		DoQuestCheckDelay("PZ_DoprosRobertMartin_Trum_2", 1.0);
		StartQuestMovie(true, false, true);
		//locCameraFromToPos(3.29, 14.23, -3.63, false, 0.58, 11.00, -8.04);
		locCameraFromToPos(-0.65, 7.06, -9.15, false, -0.81, 5.47, -4.05);
		pchar.GenQuest.BlockDialogCamera = true;
	}
	
	else if (sQuestName == "PZ_DoprosRobertMartin_Trum_2") {
		LAi_SetActorType(pchar);
		LAi_ActorGoToLocator(pchar, "goto", "goto6", "", -1);
		DoQuestCheckDelay("PZ_DoprosRobertMartin_Trum_3", 4.0);
		SetMusic("");
	}
	
	else if (sQuestName == "PZ_DoprosRobertMartin_Trum_3") {
		LAi_FadeLong("PZ_DoprosRobertMartin_Trum_4", "");
	}
	
	else if (sQuestName == "PZ_DoprosRobertMartin_Trum_4") {
		ChangeCharacterAddressGroup(pchar, PChar.location, "rld", "loc0");
		TeleportCharacterToPosAy(pchar, 0.50, 5.60, 8.75, 3.00);
		sld = CharacterFromID("PZ_RobertMartinPlennik");
		ChangeCharacterAddressGroup(sld, PChar.location, "rld", "aloc0");
		LAi_SetActorType(sld);
		LAi_SetActorType(pchar);
		LAi_ActorTurnToCharacter(sld, pchar);
		LAi_ActorTurnToCharacter(pchar, sld);
		//locCameraFromToPos(-3.66, 14.03, -1.28, true, 1.91, 10.82, -4.36);
		locCameraFromToPos(-2.80, 7.72, 6.77, true, 0.66, 5.00, 8.26);
		DoQuestCheckDelay("PZ_DoprosRobertMartin_Trum_5", 1.0);
	}
	
	else if (sQuestName == "PZ_DoprosRobertMartin_Trum_5") {
		TeleportCharacterToPosAy(pchar, 0.50, 5.60, 8.75, 3.00);
		sld = CharacterFromID("PZ_RobertMartinPlennik");
		LAi_SetActorType(sld);
		LAi_ActorAnimation(sld, "beatmarten_1", "1", 3.8);
		LAi_SetActorType(pchar);
		LAi_ActorAnimation(pchar, "beatmarten_1", "1", 3.8);
		DoQuestCheckDelay("PZ_DoprosRobertMartin_Trum_5_1", 1.8);
	}
	
	else if (sQuestName == "PZ_DoprosRobertMartin_Trum_5_1") {
		LAi_Fade("PZ_DoprosRobertMartin_Trum_5_2", "");
	}
	
	else if (sQuestName == "PZ_DoprosRobertMartin_Trum_5_2") {
		LAi_SetStayType(pchar);
		sld = CharacterFromID("PZ_RobertMartinPlennik");
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_RobertMartin_13";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0)
	}
	
	else if (sQuestName == "PZ_DoprosRobertMartin_Trum_6") {
		sld = CharacterFromID("PZ_RobertMartinPlennik");
		LAi_SetActorType(sld);
		LAi_ActorAnimation(sld, "beatmarten_2", "1", 3.8);
		LAi_SetActorType(pchar);
		LAi_ActorAnimation(pchar, "beatmarten_2", "1", 3.8);
		DoQuestCheckDelay("PZ_DoprosRobertMartin_Trum_6_1", 1.8);
	}
	
	else if (sQuestName == "PZ_DoprosRobertMartin_Trum_6_1") {
		LAi_Fade("PZ_DoprosRobertMartin_Trum_6_2", "");
	}
	
	else if (sQuestName == "PZ_DoprosRobertMartin_Trum_6_2") {
		//TeleportCharacterToPosAy(pchar, -0.55, 12.00, -1.30, -2.20);
		locCameraFromToPos(-2.80, 7.72, 6.77, true, 0.66, 5.00, 8.26);
		LAi_SetStayType(pchar);
		sld = CharacterFromID("PZ_RobertMartinPlennik");
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_RobertMartin_16";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0)
	}
	
	else if (sQuestName == "PZ_DoprosRobertMartin_Trum_7") {
		LAi_Fade("PZ_DoprosRobertMartin_Trum_7_1", "");
	}
	
	else if (sQuestName == "PZ_DoprosRobertMartin_Trum_7_1") {
		//TeleportCharacterToPosAy(pchar, -0.55, 12.00, -1.30, -2.20);
		TeleportCharacterToPosAy(pchar, 0.35, 5.60, 6.30, 1.40);
		sld = CharacterFromID("PZ_RobertMartinPlennik");
		LAi_SetActorType(sld);
		LAi_ActorAnimation(sld, "beatmarten_3", "1", 17.8);
		LAi_SetActorType(pchar);
		LAi_ActorAnimation(pchar, "beatmarten_3", "1", 17.8);
		locCameraFromToPos(-0.06, 7.96, 7.60, true, 1.12, 4.74, 5.73);
		DoQuestCheckDelay("PZ_DoprosRobertMartin_Trum_8", 5.5);
		DoQuestCheckDelay("PZ_DoprosRobertMartin_Trum_9", 8.5);
	}
	
	else if (sQuestName == "PZ_DoprosRobertMartin_Trum_8") {
		locCameraFromToPos(1.94, 7.44, 9.79, true, 0.75, 4.87, 6.00);
	}
	
	else if (sQuestName == "PZ_DoprosRobertMartin_Trum_9") {
		LAi_FadeLong("PZ_DoprosRobertMartin_1", "");
	}
	
	else if (sQuestName == "PZ_DoprosRobertMartin_1") {
		LAi_SetStayType(pchar);
		sld = CharacterFromID("PZ_RobertMartinPlennik");
		TeleportCharacterToPosAy(pchar, 0.50, 5.60, 8.75, 3.00);
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_RobertMartin_19";
		LAi_SetActorType(sld);
		//LAi_ActorSetGroundSitMode(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0)
	}
	
	else if (sQuestName == "PZ_AlonsoKazn") {
		sld = GetCharacter(NPC_GenerateCharacter("Alonso", "Alonso", "man", "man", 25, pchar.nation, -1, true, "soldier"));
		sld.name = StringFromKey("Longway_1");
		sld.lastname = StringFromKey("Longway_2");
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_AlonsoKaznDialog_1";
		ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto4");
		//TeleportCharacterToPosAy(sld, 1.26, 5.63, -2.10, -1.10);
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
	}
	
	else if (sQuestName == "PZ_AlonsoKazn_2") {
		LAi_SetStayType(pchar);
		sld = CharacterFromID("Alonso");
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_AlonsoKaznDialog_4";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
	}
	
	else if (sQuestName == "PZ_AlonsoKazn_3") {
		PlaySound("People Fight\Damage_NPC_06.wav");
		DoQuestCheckDelay("PZ_AlonsoKazn_4", 1.2);
	}
	
	else if (sQuestName == "PZ_AlonsoKazn_4") {
		PlaySound("People Fight\Damage_NPC_01.wav");
		DoQuestCheckDelay("PZ_AlonsoKazn_5", 1.2);
	}
	
	else if (sQuestName == "PZ_AlonsoKazn_5") {
		sld = CharacterFromID("PZ_RobertMartinPlennik");
		LaunchBlood(sld, 1.0, true, "fight");
		LaunchBlood(sld, 1.0, true, "fight");
		LaunchBlood(sld, 1.0, true, "fight");
		LAi_SetActorType(sld);
		LAi_ActorSetLayMode(sld);
		sld.lifeday = 0;
		sld.location = "None";
		PlaySound("People Fight\Death_NPC_06.wav");
		DoQuestCheckDelay("PZ_AlonsoKazn_6", 1.2);
	}
	
	else if (sQuestName == "PZ_AlonsoKazn_6") {
		LAi_FadeToBlackEnd();
		DoQuestCheckDelay("PZ_AlonsoKazn_7", 1.5);
	}
	
	else if (sQuestName == "PZ_AlonsoKazn_7") {
		LAi_SetStayType(pchar);
		sld = CharacterFromID("Alonso");
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_AlonsoKaznDialog_6";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
	}
	
	else if (sQuestName == "PZ_LongwayKazn_1") {
		PlaySound("Interface\Door_Kick.wav");
		sld = CharacterFromID("Longway");
		sld.greeting = "";
		ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
		LAi_SetActorType(sld);
		DoQuestCheckDelay("PZ_LongwayKazn_2", 1.0);
	}
	
	else if (sQuestName == "PZ_LongwayKazn_2") {
		sld = CharacterFromID("Longway");
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_LongwayKaznDialog_2";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
	}
	
	else if (sQuestName == "PZ_LongwayKazn_3") {
		sld = CharacterFromID("Longway");
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_LongwayKaznDialog_4";
		ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto4");
		TeleportCharacterToPosAy(sld, 1.26, 12.00, -2.10, -1.10);
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
	}
	
	else if (sQuestName == "PZ_LongwayKazn_4") {
		PlaySound("People Fight\Damage_NPC_06.wav");
		DoQuestCheckDelay("PZ_LongwayKazn_5", 1.2);
	}
	
	else if (sQuestName == "PZ_LongwayKazn_5") {
		PlaySound("People Fight\Damage_NPC_01.wav");
		DoQuestCheckDelay("PZ_LongwayKazn_6", 1.2);
	}
	
	else if (sQuestName == "PZ_LongwayKazn_6") {
		sld = CharacterFromID("Longway");
		ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto4");
		CharacterTurnByChr(sld, pchar);
		
		sld = CharacterFromID("PZ_RobertMartinPlennik");
		LaunchBlood(sld, 1.0, true, "fight");
		LaunchBlood(sld, 1.0, true, "fight");
		LaunchBlood(sld, 1.0, true, "fight");
		LAi_SetActorType(sld);
		LAi_ActorSetLayMode(sld);
		TeleportCharacterToPosAy(sld, -0.33, 12.00, -5.64, 0.00);
		PlaySound("People Fight\Death_NPC_06.wav");
		DoQuestCheckDelay("PZ_LongwayKazn_7", 1.2);
	}
	
	else if (sQuestName == "PZ_LongwayKazn_7") {
		//sld = CharacterFromID("PZ_RobertMartinPlennik");
		//LAi_SetActorType(sld);
		//LAi_ActorAnimation(sld, "beatmarten_4", "1", 5.8);
		LAi_FadeToBlackEnd();
		LAi_SetStayType(pchar);
		sld = CharacterFromID("PZ_RobertMartinPlennik");
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_LongwayKaznDialog_9";
		LAi_SetActorType(sld);
		LAi_ActorSetLayMode(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
	}
	
	else if (sQuestName == "PZ_LongwayKazn_11") {
		sld = CharacterFromID("PZ_RobertMartinPlennik");
		TeleportCharacterToPosAy(sld, -0.33, 12.00, -5.64, 0.00);
		LAi_SetActorType(sld);
		LAi_ActorAnimation(sld, "beatmarten_4", "1", 14.8);
		DoQuestCheckDelay("PZ_LongwayKazn_12", 11.4);
	}
	
	else if (sQuestName == "PZ_LongwayKazn_12") {
		LAi_SetActorType(pchar);
		LAi_ActorAnimation(pchar, "Shot", "1", 1.5);
		DoQuestCheckDelay("PZ_LongwayKazn_13", 0.9);
	}
	
	else if (sQuestName == "PZ_LongwayKazn_13") {
		DoQuestCheckDelay("PZ_LongwayKazn_14", 1.3);
		Achievment_SetStat(95, 1);
	}
	
	else if (sQuestName == "PZ_LongwayKazn_14") {
		LAi_Fade("PZ_LongwayKazn_15", "");
	}
	
	else if (sQuestName == "PZ_LongwayKazn_15") {
		sld = CharacterFromID("PZ_RobertMartinPlennik");
		ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto4");
		sld.lifeday = 0;
		sld.location = "None";
		LAi_SetActorType(sld);
		LAi_ActorSetLayMode(sld);
		
		LAi_SetStayType(pchar);
		sld = CharacterFromID("Longway");
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_LongwayKaznDialog_11";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
	}
	
	else if (sQuestName == "PZ_Etap6_Opozdal") {
		pchar.questTemp.PZ_Etap6_Opozdal = true;
	}
	
	else if (sQuestName == "PZ_Etap6_Start") {
		pchar.GenQuest.CabinLock = true;
		Island_SetReloadEnableGlobal("Tortuga", false);
		bQuestDisableMapEnter = true;
		
		DoQuestCheckDelay("PZ_Etap6_Start2", 2.5);
	}
	
	else if (sQuestName == "PZ_Etap6_Start2") {
		SetCurrentTime(10, 00);
		RecalculateJumpTable();
		RefreshWeather();
		RefreshLandTime();
		setCharacterShipLocation(pchar, "Shore58");
		setWDMPointXZ("Shore58");
		DeleteQuestCondition("PZ_Etap6_Opozdal");
		DoQuestReloadToLocation("Shore58", "goto", "goto9", "PZ_Etap6TortugaShore");
	}
	
	else if (sQuestName == "PZ_Etap6TortugaShore") {
		chrDisableReloadToLocation = true;
		QuestCloseSeaExit();
		sld = CharacterFromID("Longway");
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_Longway_81";
		ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto3");
		LAi_SetStayType(sld);
		AddLandQuestMark(sld, "questmarkmain");
		//LAi_ActorDialog(sld, pchar, "", -1, 0);
		
		if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
		{
			sld = CharacterFromID("Mary");
			sld.model = "Mary_beaten";
		}
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
		{
			sld = CharacterFromID("Helena");
			sld.model = "Rumba_beaten";
		}
		RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
		RemoveCharacterEquip(sld, GUN_ITEM_TYPE);
		pchar.GenQuestBox.Tortuga_Torture_room.box3.items.key_levasser = 1;	// Ключ Левассера в сундуке
		
		sld = characterFromID("Tortuga_Mayor");
		ChangeCharacterAddressGroup(sld, "none", "", "");
	}
	
	else if (sQuestName == "PZ_Etap6TortugaPodzemelie") {
		PChar.quest.PZ_Etap6TortugaPytochnaya.win_condition.l1 = "locator";
		PChar.quest.PZ_Etap6TortugaPytochnaya.win_condition.l1.location = "Tortuga_Cave";
		PChar.quest.PZ_Etap6TortugaPytochnaya.win_condition.l1.locator_group = "reload";
		PChar.quest.PZ_Etap6TortugaPytochnaya.win_condition.l1.locator = "reload3_back";
		PChar.quest.PZ_Etap6TortugaPytochnaya.win_condition = "PZ_Etap6TortugaPytochnaya";
		LAi_LocationDisableOfficersGen("Tortuga_Cave", false);
		DoQuestCheckDelay("PZ_Etap6TortugaPodzemelie_Longway", 2.0);
	}
	
	else if (sQuestName == "PZ_Etap6TortugaPodzemelie_Longway") {
		if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
		{
			sld = CharacterFromID("Longway");
			ChangeCharacterAddressGroup(sld, PChar.location, "officers", "reload2_2");
			Return_LongwayOfficer();
			AddQuestRecord("PZ", "46");
		}
		else
		{
			sld = CharacterFromID("Longway");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			Return_LongwayOfficer();
			RemovePassenger(pchar, sld);
			AddQuestRecord("PZ", "47");
		}
		
		if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) AddQuestUserData("PZ", "sText", StringFromKey("Longway_49"));
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) AddQuestUserData("PZ", "sText", StringFromKey("Longway_50"));
	}
	
	else if (sQuestName == "PZ_Etap6TortugaPytochnaya") {
		DoQuestReloadToLocation("Tortuga_Torture_room", "reload", "reload1", "PZ_Etap6TortugaPytochnaya2");
	}
	
	else if (sQuestName == "PZ_MarcelineLongwayGo") {
		chrDisableReloadToLocation = false;
		AddQuestRecord("PZ", "41");
		if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) AddQuestUserData("PZ", "sText", StringFromKey("Longway_49"));
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) AddQuestUserData("PZ", "sText", StringFromKey("Longway_50"));
		
		sld = characterFromID("Longway");
		RemovePassenger(pchar, sld);
		LAi_SetActorType(sld);
		LAi_ActorRunToLocation(sld, "reload", "reload1_back", "", "", "", "", -1);
		sld.location = "None";
		
		pchar.quest.PZ_Marceline.win_condition.l1 = "location";
		pchar.quest.PZ_Marceline.win_condition.l1.location = "Tortuga_TownhallRoom";
		pchar.quest.PZ_Marceline.win_condition = "PZ_CreateSoldier";
	}
	
	else if (sQuestName == "PZ_CreateSoldier") {
		chrDisableReloadToLocation = true;
		
		sld = GetCharacter(NPC_GenerateCharacter("PZ_FrenchSoldier", "sold_fra_" + (rand(7) + 1), "man", "man", sti(pchar.rank), FRANCE, -1, true, "soldier"));
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_FrenchSoldier1";
		ChangeCharacterAddressGroup(sld, "Tortuga_TownhallRoom", "reload", "reload2");
		LAi_SetStayType(sld);
	}
	
	else if (sQuestName == "PZ_FrenchSoldierFight") {
		sld = characterFromID("PZ_FrenchSoldier");
		LAi_group_MoveCharacter(sld, "EnemyFight");
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "PZ_FrenchSoldierDead");
	}
	
	else if (sQuestName == "PZ_FrenchSoldierDead") {
		chrDisableReloadToLocation = false;
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
		
		pchar.quest.PZ_CreateMarceline.win_condition.l1 = "location";
		pchar.quest.PZ_CreateMarceline.win_condition.l1.location = "Tortuga_townhallBedroom";
		pchar.quest.PZ_CreateMarceline.win_condition = "PZ_CreateMarceline";
	}
	
	else if (sQuestName == "PZ_CreateMarceline") {
		sld = GetCharacter(NPC_GenerateCharacter("PZ_Marceline", "Levaser_Wife", "woman", "towngirl", 5, FRANCE, -1, false, "quest"));
		sld.name = StringFromKey("Longway_62");
		sld.lastname = StringFromKey("Longway_63");
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_Marceline1";
		ChangeCharacterAddressGroup(sld, "Tortuga_townhallBedroom", "barmen", "stay");
		LAi_SetStayType(sld);
	}
	
	else if (sQuestName == "PZ_MarcelineOver") {
		PChar.quest.PZ_Etap6TortugaPytochnaya.win_condition.l1 = "locator";
		PChar.quest.PZ_Etap6TortugaPytochnaya.win_condition.l1.location = "Tortuga_Cave";
		PChar.quest.PZ_Etap6TortugaPytochnaya.win_condition.l1.locator_group = "reload";
		PChar.quest.PZ_Etap6TortugaPytochnaya.win_condition.l1.locator = "reload3_back";
		PChar.quest.PZ_Etap6TortugaPytochnaya.win_condition = "PZ_Etap6TortugaPytochnaya";
		
		pchar.questTemp.PZ_DevushkaRanena_Sredne = true;
		pchar.questTemp.PZ_FlagMarselinaInfo = true;
		
		sld = characterFromID("PZ_Marceline");
		sld.lifeday = 0;
		LAi_CharacterDisableDialog(sld);
		
		// и снова парад записей в СЖ
		switch (pchar.questTemp.FMQT.Marceline)
		{
			case "Fuck":
				AddQuestRecord("PZ", "44");
			break;
			
			case "NoFuck":
				AddQuestRecord("PZ", "44");
			break;
			
			case "Deception":
				AddQuestRecord("PZ", "43");
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) AddQuestUserData("PZ", "sText", StringFromKey("Longway_49"));
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) AddQuestUserData("PZ", "sText", StringFromKey("Longway_50"));
			break;
		}
	}
	
	else if (sQuestName == "PZ_TogetherLongwayGo") {
		chrDisableReloadToLocation = false;
		
		AddQuestRecord("PZ", "42");
		if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) AddQuestUserData("PZ", "sText", StringFromKey("Longway_49"));
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) AddQuestUserData("PZ", "sText", StringFromKey("Longway_50"));
		if (CheckAttribute(pchar, "questTemp.FMQT_ObchistilSunduk")) AddQuestUserData("PZ", "sText1", StringFromKey("Longway_64"));
		
		pchar.questTemp.PZ_LongwayRyadom = true;
		Return_LongwayOfficer();
		
		sld = CharacterFromID("Longway");
		LAi_SetActorType(sld);
		LAi_ActorFollowEverywhere(sld, "", -1);
		
		PChar.quest.PZ_Etap6_BrothelPoiskSestry.win_condition.l1 = "location";
		PChar.quest.PZ_Etap6_BrothelPoiskSestry.win_condition.l1.location = "Tortuga_brothelElite";
		PChar.quest.PZ_Etap6_BrothelPoiskSestry.win_condition = "PZ_Etap6_BrothelPoiskSestry";
	}
	
	else if (sQuestName == "PZ_Etap6_BrothelPoiskSestry") {
		for (i=1; i<=4; i++)
		{
			sld = characterFromID("PZ_ElitaShluha_" + i);
			LAi_CharacterEnableDialog(sld);
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_ElitaShluha_18";
		}
		if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
		{
			sld = characterFromID("Longway");
			ChangeCharacterAddressGroup(sld, "Tortuga_BrothelElite", "officers", "reload1_3");
			Return_LongwayOfficer();
		}
		if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko") && !CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
		{
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				sld = CharacterFromID("Mary");
				EquipCharacterByItem(sld, "blade_31");
				ChangeCharacterAddressGroup(sld, "Tortuga_BrothelElite", "officers", "reload1_2");
				Return_MaryOfficer();
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				sld = CharacterFromID("Helena");
				EquipCharacterByItem(sld, "pirate_cutlass");
				ChangeCharacterAddressGroup(sld, "Tortuga_BrothelElite", "officers", "reload1_2");
				Return_HelenaOfficer();
			}
		}
		
		if (CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden") && !CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
		{
			for (i = 1; i <= 4; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("PZ_EliteBrothelMercenary" + i, "citiz_" + (rand(9) + 51), "man", "man", sti(pchar.rank), FRANCE, -1, true, "quest"));
				ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto" + i);
				LAi_SetImmortal(sld, true);
				LAi_SetActorType(sld);
				LAi_ActorSetLayMode(sld);
			}
			
			for (i=1; i<=4; i++)
			{
				sld = characterFromID("PZ_ElitaShluha_" + i);
				sld.dialog.currentnode = "PZ_ElitaShluha_18_1";
			}
		}
		
		LocatorReloadEnterDisable("Tortuga_BrothelElite", "reload1", true);
	}
	
	else if (sQuestName == "PZ_EliteBrothelFight") {
		chrDisableReloadToLocation = true;
		PlaySound("People Fight\Peace_woman_death_05.wav");
		
		for (i=1; i<=4; i++)
		{
			if (CharacterIsAlive("PZ_ElitaShluha_" + i))
			{
				sld = characterFromID("PZ_ElitaShluha_" + i);
				//LAi_CharacterDisableDialog(sld);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload3", "none", "", "", "", -1);
			}
		}
		
		for (i = 1; i <= 4; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("PZ_EliteBrothelMercenary" + i, "citiz_" + (rand(9) + 51), "man", "man", sti(pchar.rank), FRANCE, -1, true, "quest"));
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			if (i==3) ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload2");
			if (i==4) ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload2");
			LAi_SetHP(sld, 400, 400);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		}
		
		LAi_group_SetCheck("EnemyFight", "PZ_EliteBrothelCreateChangShin");
	}
	
	else if (sQuestName == "PZ_EliteBrothelCreateChangShin") {
		chrDisableReloadToLocation = false;
		LocatorReloadEnterDisable(pchar.location, "reload2", false);
		LAi_group_Delete("EnemyFight");
		for (i=1; i<=4; i++)
		{
			if (CharacterIsAlive("PZ_ElitaShluha_" + i))
			{
				sld = characterFromID("PZ_ElitaShluha_" + i);
				LAi_CharacterDisableDialog(sld);
			}
		}
		
		sld = GetCharacter(NPC_GenerateCharacter("PZ_ChangShin", "Mei_Shin", "woman", "towngirl2", 30, FRANCE, -1, false, "quest"));
		FantomMakeCoolFighter(sld, 30, 80, 80, "blade_41", "", "", 0);
		sld.name = StringFromKey("Longway_65");
		sld.lastname = StringFromKey("Longway_66");
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_ChangShin1";
		ChangeCharacterAddressGroup(sld, "Tortuga_brothelElite_room2", "goto", "goto10");
		LAi_SetActorType(sld);
		LAi_SetHP(sld, 600, 600);
		EquipCharacterByItem(sld, "blade_41");
		GiveItem2Character(sld, "cirass8");
		EquipCharacterByItem(sld, "cirass8");
		sld.SaveItemsForDead = true;
		SetCharacterPerk(sld, "Energaiser");
		SetCharacterPerk(sld, "BasicDefense");
		SetCharacterPerk(sld, "AdvancedDefense");
		SetCharacterPerk(sld, "CriticalHit");
		SetCharacterPerk(sld, "Tireless");
		SetCharacterPerk(sld, "Gunman");
		SetCharacterPerk(sld, "GunProfessional");
		SetCharacterPerk(sld, "Sliding");
		SetCharacterPerk(sld, "HardHitter");
		SetCharacterPerk(sld, "SwordplayProfessional");
		AddItems(sld, "potion2", 1);
		
		PChar.quest.PZ_EliteBrothelCreateChangShin2.win_condition.l1 = "location";
		PChar.quest.PZ_EliteBrothelCreateChangShin2.win_condition.l1.location = "Tortuga_brothelElite_room2";
		PChar.quest.PZ_EliteBrothelCreateChangShin2.win_condition = "PZ_EliteBrothelCreateChangShin2";
	}
	
	else if (sQuestName == "PZ_LongwayTurnToChangShin") {
		sld = characterFromID("Longway");
		LAi_SetActorType(sld);
		LAi_ActorTurnToCharacter(sld, characterFromId("PZ_ChangShin"));
	}
	
	else if (sQuestName == "PZ_EliteBrothelCreateChangShin2") {
		chrDisableReloadToLocation = true;
		pchar.questTemp.PZ_FlagShinInfo = true;		// Флаг, что были у Чанг Шин
		SetMusic("music_way_back_then");
		if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
		{
			sld = CharacterFromID("Longway");
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto1");
			Return_LongwayOfficer();
			
			sld = characterFromID("PZ_ChangShin");
			LAi_SetStayType(sld);
			sld.talker = 5;
		}
		if (CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden") && !CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
		{
			sld = CharacterFromID("Longway");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_LongwayPrishelOdin";
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto9");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			
		}
		if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko") && !CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
		{
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				sld = CharacterFromID("Mary");
				ChangeCharacterAddressGroup(sld, PChar.location, "barmen", "bar2");
				Return_MaryOfficer();
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				sld = CharacterFromID("Helena");
				ChangeCharacterAddressGroup(sld, PChar.location, "barmen", "bar2");
				Return_HelenaOfficer();
			}
		}
		
		if (CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden"))
		{
			// Левассера победили, поэтому после Чанг Шин идём на берег
			PChar.quest.PZ_ObratnoNaBereg.win_condition.l1 = "location";
			PChar.quest.PZ_ObratnoNaBereg.win_condition.l1.location = "Shore58";
			PChar.quest.PZ_ObratnoNaBereg.win_condition = "PZ_ObratnoNaBereg";
		}
		else
		{
			// Ещё не были у Левассера, поэтому после Чанг Шин идём в подземелье
			PChar.quest.PZ_Etap6TortugaPytochnaya.win_condition.l1 = "locator";
			PChar.quest.PZ_Etap6TortugaPytochnaya.win_condition.l1.location = "Tortuga_Cave";
			PChar.quest.PZ_Etap6TortugaPytochnaya.win_condition.l1.locator_group = "reload";
			PChar.quest.PZ_Etap6TortugaPytochnaya.win_condition.l1.locator = "reload3_back";
			PChar.quest.PZ_Etap6TortugaPytochnaya.win_condition = "PZ_Etap6TortugaPytochnaya";
		}
		
		for (i=1; i<=4; i++)
		{
			if (CharacterIsAlive("PZ_ElitaShluha_" + i))
			{
				// Вернуть шлюх на место
				sld = characterFromID("PZ_ElitaShluha_" + i);
				LAi_SetCitizenType(sld);
				ChangeCharacterAddressGroup(sld, "Tortuga_brothelElite", "goto", "goto"+i);
			}
		}
	}
	
	else if (sQuestName == "PZ_BrothelTeleportVZal") {
		DeleteAttribute(pchar, "questTemp.PZ_LongwayRyadom");
		sld = CharacterFromID("Longway");
		RemovePassenger(pchar, sld);
		if (!CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden")) pchar.questTemp.PZ_DevushkaRanena_Sredne = true;
		LocatorReloadEnterDisable("Tortuga_brothelElite", "reload2", true);
		DoQuestReloadToLocation("Tortuga_brothelElite", "reload", "reload2", "PZ_EliteBrothelFinalDialog");
	}
	
	else if (sQuestName == "PZ_ChangShinFightWithLongway") {
		Return_LongwayOfficer();
		
		sld = characterFromID("PZ_ChangShin");
		LAi_group_MoveCharacter(sld, "EnemyFight");
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "PZ_ChangShinDeathWithLongway");
	}
	
	else if (sQuestName == "PZ_ChangShinAndLongwayFightMe") {
		if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko") && !CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
		{
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) Return_MaryOfficer();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) Return_HelenaOfficer();
		}
		
		sld = characterFromID("Longway");
		RemovePassenger(pchar, sld);
		LAi_RemoveCheckMinHP(sld);
		LAi_SetImmortal(sld, false);
		DeleteAttribute(sld, "OfficerImmortal");
		if(CheckAttribute(sld, "Health.HP")) DeleteAttribute(sld, "Health.HP");
		if(CheckAttribute(sld, "Health.maxHP")) DeleteAttribute(sld, "Health.maxHP");
		sTemp = "RestoreHealth_" + sld.index;
		if(CheckAttribute(PChar, "quest.RestoreHealth_" + sld.index)) PChar.quest.(sTemp).over = "Yes";
		LAi_group_MoveCharacter(sld, "EnemyFight");
		sld.SaveItemsForDead = true;
		sld.DontClearDead = true;
		// Проверка, получим ли оберег
		if (CheckAttribute(pchar, "questTemp.PZ.LongwayMayfang") || CheckAttribute(pchar, "questTemp.PZ.LongwayTorero") || CheckAttribute(pchar, "questTemp.PZ.LongwayElCasador"))
		{
			GiveItem2Character(sld, "talisman14");
		}

		sld = characterFromID("PZ_ChangShin");
		LAi_group_MoveCharacter(sld, "EnemyFight");
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "PZ_ChangShinDeathWithLongway");
		DeleteAttribute(pchar, "questTemp.PZ_LongwayRyadom");
	}
	
	else if (sQuestName == "PZ_LongwayPrishelOdin_ChangShinNext") {
		sld = characterFromID("Longway");
		LAi_SetActorType(sld);
		LAi_ActorFollow(sld, pchar, "", -1);
		
		sld = characterFromID("PZ_ChangShin");
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		if (CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva")) sld.dialog.currentnode = "PZ_LongwayPrishelOdin5";
		else
		{
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko")) sld.dialog.currentnode = "PZ_LongwayPrishelOdin9";
			else sld.dialog.currentnode = "PZ_LongwayPrishelOdin15";
		}
		LAi_SetStayType(sld);
		sld.talker = 5;
	}
	
	else if (sQuestName == "PZ_ChangShinDeathWithLongway") {
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
		pchar.questTemp.PZ_ChangShinMertva = true;
		LAi_SetPlayerType(pchar);
		if (!CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden")) pchar.questTemp.PZ_DevushkaRanena_Tyazhelo = true;
		
		if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
		{
			sld = characterFromID("Longway");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Longway_91";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		}
		if (CharacterIsHere("Mary"))
		{
			sld = characterFromID("Mary");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Mary_91";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		}
		if (CharacterIsHere("Helena")) DoQuestCheckDelay("PZ_LeaveEliteBrothel", 1.0);
		if (!CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom") && !CharacterIsHere("Mary") && !CharacterIsHere("Helena")) DoQuestCheckDelay("PZ_LeaveEliteBrothel", 1.0);
	}
	
	else if (sQuestName == "PZ_LeaveEliteBrothel") {
		chrDisableReloadToLocation = false;
		
		LAi_SetPlayerType(pchar);
		
		if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom")) Return_LongwayOfficer();
		if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) Return_MaryOfficer();
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) Return_HelenaOfficer();
		
		PChar.quest.PZ_EliteBrothelFinalDialog.win_condition.l1 = "location";
		PChar.quest.PZ_EliteBrothelFinalDialog.win_condition.l1.location = "Tortuga_brothelElite";
		PChar.quest.PZ_EliteBrothelFinalDialog.win_condition = "PZ_EliteBrothelFinalDialog";
	}
	
	else if (sQuestName == "PZ_EliteBrothelFinalDialog") {
		chrDisableReloadToLocation = true;
		Achievment_Set("ach_CL_128");
		
		if (CharacterIsAlive("PZ_ElitaShluha_1")) sld = characterFromID("PZ_ElitaShluha_1");
		else sld = characterFromID("PZ_ElitaShluha_2");
		sld.dialog.currentnode = "PZ_ElitaShluha_Final1";
		LAi_CharacterEnableDialog(sld);
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	
	else if (sQuestName == "PZ_ToTortugaStreets") {
		chrDisableReloadToLocation = false;
		LocatorReloadEnterDisable("Tortuga_brothelElite", "reload1", false);
		
		for (i=1; i<=4; i++)
		{
			if (CharacterIsAlive("PZ_ElitaShluha_" + i))
			{
				sld = characterFromID("PZ_ElitaShluha_" + i);
				sld.lifeday = 0;
				LAi_CharacterDisableDialog(sld);
			}
		}
		
		if (CheckAttribute(pchar, "questTemp.PZ_ChangShinMertva"))
		{
			PChar.quest.PZ_CreateTortugaStreetSoldiers.win_condition.l1 = "location";
			PChar.quest.PZ_CreateTortugaStreetSoldiers.win_condition.l1.location = "Tortuga_town";
			PChar.quest.PZ_CreateTortugaStreetSoldiers.win_condition = "PZ_CreateTortugaStreetSoldiers";
		}
		
		//Куча СЖ
		if (CheckAttribute(pchar, "questTemp.PZ_ChangShinMertva") && CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
		{
			if (!CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden"))
			{
				AddQuestRecord("PZ", "52");
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) AddQuestUserData("PZ", "sText", StringFromKey("Longway_49"));
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) AddQuestUserData("PZ", "sText", StringFromKey("Longway_50"));
			}
			else 
			{
				AddQuestRecord("PZ", "53");
			}
		}
		if (CheckAttribute(pchar, "questTemp.PZ_ChangShinMertva") && !CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom") && CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden") && CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) AddQuestRecord("PZ", "54");
		if (!CheckAttribute(pchar, "questTemp.PZ_ChangShinMertva") && !CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom") && CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden") && CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) 
		{
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko")) AddQuestRecord("PZ", "55");
			else AddQuestRecord("PZ", "56");
		}
		if (CheckAttribute(pchar, "questTemp.PZ_ChangShinMertva") && !CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom") && !CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden"))
		{
			AddQuestRecord("PZ", "57");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) AddQuestUserData("PZ", "sText", StringFromKey("Longway_49"));
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) AddQuestUserData("PZ", "sText", StringFromKey("Longway_50"));
		}
	}
	
	else if (sQuestName == "PZ_CreateTortugaStreetSoldiers") {
		chrDisableReloadToLocation = true;
		
		LocatorReloadEnterDisable("Tortuga_town", "houseS4", true);
		
		for (i = 1; i <= 3; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("PZ_TortugaSoldiers" + i, "sold_fra_" + (rand(7) + 1), "man", "man", sti(pchar.rank), FRANCE, 0, true, "soldier"));
			PlaceCharacter(sld, "goto", "random_must_be_near");
			if (i == 1)
			{
				sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
				sld.dialog.currentnode = "PZ_TortugaSoldier1";
				sld.greeting = "patrol";
				LAi_SetActorTypeNoGroup(sld);
				SetActorDialogAny2Pchar(sld.id, "pchar_back_to_player", 0, -1);
				LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", -1);
			}
			else
			{
				LAi_SetActorTypeNoGroup(sld);
				LAi_ActorFollow(sld, pchar, "", -1);
				LAi_CharacterDisableDialog(sld);
			}
		}
	}
	
	else if (sQuestName == "PZ_TortugaSoldiersFight") {
		chrDisableReloadToLocation = false;
		for (i = 1; i <= 3; i++)
		{
			LAi_SetFightMode(pchar, true);
			sld = characterFromID("PZ_TortugaSoldiers" + i);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		}
	}
			
	else if (sQuestName == "PZ_Etap6TortugaPytochnaya2") {		// Sinistra катсцена пыточной
		StartQuestMovie(true, false, true);
		LAi_SetStayType(pchar);
		pchar.GenQuest.BlockDialogCamera = true;
		if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
		{
			locCameraFromToPos(-19.19, 1.37, 0.51, false, -19.34, -0.60, -4.61);
			DoQuestCheckDelay("PZ_Etap6TortugaPytochnaya3", 4.0);
		}
		if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
		{
			locCameraFromToPos(-19.19, 1.37, 0.51, false, -19.34, -0.60, -4.61);
			DoQuestCheckDelay("PZ_Etap6TortugaPytochnaya4", 4.0);
		}
		if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
		{
			locCameraFromToPos(-19.19, 1.37, 0.51, false, -19.34, -0.60, -4.61);
			DoQuestCheckDelay("PZ_Etap6TortugaPytochnaya3", 4.0);
		}
		
		if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
		{
			sld = CharacterFromID("Longway");
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto1");
			TeleportCharacterToPos(sld, -12.45, 2.89, -0.50);
			LAi_SetActorType(sld);
			LAi_ActorTurnToLocator(sld, "goto", "goto6");
		}
		
		sld = GetCharacter(CreateCharacterClone(CharacterFromID("Tortuga_Mayor"), -1));
		sld.id = "Levasser";
		TakeItemFromCharacter(sld, "key_levasser");
		GiveItem2Character(sld, "pistol1"); 
		EquipCharacterbyItem(sld, "pistol1");
		ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto6");
		LAi_SetActorType(sld);
		LAi_ActorTurnToLocator(sld, "goto", "goto4");
		if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo")) LAi_ActorTurnToLocator(sld, "torture", "torture_3");
		
		sld = CharacterFromID("Tibo");
		ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
		LAi_SetActorType(sld);
		LAi_ActorTurnToLocator(sld, "goto", "goto6");
		
		if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sld = CharacterFromID("Mary");
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sld = CharacterFromID("Helena");
		if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
		{
			ChangeCharacterAddressGroup(sld, PChar.location, "torture", "torture_1");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "torture_1", "", 1.8);
		}
		if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
		{
			ChangeCharacterAddressGroup(sld, PChar.location, "torture", "torture_2");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "torture_2", "", 1.8);
		}
		if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
		{
			ChangeCharacterAddressGroup(sld, PChar.location, "torture", "torture_3");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "torture_3", "", 1.8);
		}
		
		sld = &Locations[FindLocation("Tortuga_Cave")];
		sld.reload.l3.name = "reload3_back";
		sld.reload.l3.go = "Tortuga_Torture_room";
		sld.reload.l3.emerge = "reload1";
		sld.reload.l3.autoreload = "1";
		SetTimerCondition("PZ_TortureRoomClose", 0, 0, 30, false);//пыточная доступна месяц, потом закроется
	}
	
	else if (sQuestName == "PZ_Etap6TortugaPytochnaya3") {
		if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
		{
			locCameraFromToPos(-17.83, 1.78, 1.80, true, -20.35, 0.20, 1.24);
		}
		else
		{
			locCameraFromToPos(-16.54, 0.93, 2.64, true, -20.51, -0.25, 1.09);	//В колодках
		}
		DoQuestCheckDelay("PZ_Etap6TortugaPytochnaya4", 3.0);
	}
	
	else if (sQuestName == "PZ_Etap6TortugaPytochnaya4") {
		if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
		{
			locCameraFromToPos(-17.80, 2.28, 2.72, true, -19.57, -0.20, 5.77);
		}
		else
		{
			locCameraFromToPos(-17.09, 1.65, 1.76, true, -20.10, -0.60, 5.81);
		}
		DoQuestCheckDelay("PZ_Etap6TortugaPytochnaya5", 4.0);
	}
	
	else if (sQuestName == "PZ_Etap6TortugaPytochnaya5") {
		locCameraFromToPos(-14.74, 1.33, 1.66, true, -12.44, -0.50, -1.37);
		if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
		{
			DoQuestCheckDelay("PZ_Etap6TortugaPytochnaya5_4", 3.0);
		}
		if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
		{
			DoQuestCheckDelay("PZ_Etap6TortugaPytochnaya5_4", 3.0);
		}
		if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
		{
			DoQuestCheckDelay("PZ_Etap6TortugaPytochnaya5_4", 3.0);
		}
	}
	
	else if (sQuestName == "PZ_Etap6TortugaPytochnaya5_1") {
		DoQuestCheckDelay("PZ_Etap6TortugaPytochnaya6", 4.0);
		locCameraFromToPos(-16.54, 0.93, 2.64, true, -20.51, -0.25, 1.09);		//В колодках
	}
	
	else if (sQuestName == "PZ_Etap6TortugaPytochnaya5_2") {
		DoQuestCheckDelay("PZ_Etap6TortugaPytochnaya6", 4.0);
		locCameraFromToPos(-16.00, 2.12, -0.83, true, -12.95, -0.57, 2.26);		//В цепях
	}
	
	else if (sQuestName == "PZ_Etap6TortugaPytochnaya5_3") {
		DoQuestCheckDelay("PZ_Etap6TortugaPytochnaya6", 5.0);
		locCameraFromToPos(-17.61, 0.43, 2.63, true, -20.53, -1.20, 3.11);		//На крюке
	}
	
	else if (sQuestName == "PZ_Etap6TortugaPytochnaya5_4") {
		if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
		{
			LAi_FadeLong("PZ_Etap6TortugaPytochnaya5_3", "");
		}
		if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
		{
			LAi_FadeLong("PZ_Etap6TortugaPytochnaya5_1", "");
		}
		if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
		{
			LAi_FadeLong("PZ_Etap6TortugaPytochnaya5_2", "");
		}
	}
	
	else if (sQuestName == "PZ_Etap6TortugaPytochnaya6") {
		DoQuestCheckDelay("PZ_Etap6TortugaPytochnaya7", 5.0);
		if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
		{
			locCameraFromToPos(-13.52, 2.15, 1.05, true, -14.13, 0.04, 2.69);
		}
		if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
		{
			locCameraFromToPos(-18.99, 0.91, 2.17, true, -20.55, 0.46, 1.27);
		}
		if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
		{
			locCameraFromToPos(-17.88, 0.28, 2.42, true, -20.02, 0.98, 3.18);
		}
	}
	
	else if (sQuestName == "PZ_Etap6TortugaPytochnaya7") {
		LAi_FadeLong("PZ_Etap6TortugaPytochnaya8", "");
	}
	
	else if (sQuestName == "PZ_Etap6TortugaPytochnaya8") {
		sld = CharacterFromID("Levasser");
		ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto3");
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_TortureRoom_Levasser_1";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
		locCameraFromToPos(-18.62, 1.27, 2.11, true, -14.27, 1.24, -1.62);
	}
	
	else if (sQuestName == "PZ_Etap6TortugaPytochnaya9") {
		sld = CharacterFromID("Levasser");
		LAi_SetActorType(sld);
		
		locCameraSleep(false);
		if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
		{
			locCameraFromToPos(-16.74, 2.58, -0.51, true, -13.13, -0.72, 2.49);
			LAi_ActorGoToLocator(sld, "goto", "goto8", "PZ_Etap6TortugaPytochnaya10", -1);
		}
		if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
		{
			locCameraFromToPos(-18.38, 1.77, 2.73, true, -20.53, 0.01, 0.32);
			LAi_ActorGoToLocator(sld, "goto", "goto7", "PZ_Etap6TortugaPytochnaya10", -1);
		}
		if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
		{
			locCameraFromToPos(-16.97, 2.09, 3.98, true, -20.02, -0.17, 2.28);
			LAi_ActorGoToLocator(sld, "goto", "goto9", "PZ_Etap6TortugaPytochnaya10", -1);
		}
	}
	
	else if (sQuestName == "PZ_Etap6TortugaPytochnaya10") {
		sld = CharacterFromID("Levasser");
		LAi_SetActorType(sld);
		if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) LAi_ActorTurnToCharacter(sld, CharacterFromID("Mary"));
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) LAi_ActorTurnToCharacter(sld, CharacterFromID("Helena"));
		LAi_ActorAnimation(sld, "attack_break_1", "1", 1.8);
		DoQuestCheckDelay("PZ_Etap6TortugaPytochnaya11", 1.0);
	}
	
	else if (sQuestName == "PZ_Etap6TortugaPytochnaya11") {
		if (!CheckAttribute(pchar, "questTemp.PZ_Etap6_Opozdal")) PlaySound("People Fight\Peace_woman_death_05.wav");
		DoQuestCheckDelay("PZ_Etap6TortugaPytochnaya12", 1.5);
	}
	
	else if (sQuestName == "PZ_Etap6TortugaPytochnaya12") {
		sld = CharacterFromID("Levasser");
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_TortureRoom_Levasser_6";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
	}
	
	else if (sQuestName == "PZ_Etap6TortugaPytochnaya13") {
		locCameraSleep(true);
		LAi_FadeLong("PZ_Etap6TortugaPytochnaya14", "");
	}
	
	else if (sQuestName == "PZ_Etap6TortugaPytochnaya14") {
		locCameraSleep(false);
		sld = CharacterFromID("Levasser");
		ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto3");
		LAi_SetActorType(sld);
		locCameraFromToPos(-18.62, 1.27, 2.11, true, -14.27, 1.24, -1.62);
		DoQuestCheckDelay("PZ_Etap6TortugaPytochnaya15", 1.0);
	}
	
	else if (sQuestName == "PZ_Etap6TortugaPytochnaya15") {
		LAi_SetActorType(pchar);
		LAi_ActorGoToLocator(pchar, "goto", "goto2", "", -1);
		DoQuestCheckDelay("PZ_Etap6TortugaPytochnaya16", 1.0);
		
		sld = CharacterFromID("Tibo");
		CharacterTurnByChr(sld, pchar);
	}
	
	else if (sQuestName == "PZ_Etap6TortugaPytochnaya16") {
		sld = CharacterFromID("Levasser");
		LAi_SetActorType(sld);
		LAi_ActorAnimation(sld, "Shot", "1", 1.8);
		DoQuestCheckDelay("PZ_Etap6TortugaPytochnaya17", 1.0);
	}
	
	else if (sQuestName == "PZ_Etap6TortugaPytochnaya17") {
		LAi_SetStayType(pchar);
		DoQuestCheckDelay("PZ_Etap6TortugaPytochnaya18", 1.0);
	}
	
	else if (sQuestName == "PZ_Etap6TortugaPytochnaya18") {
		sld = CharacterFromID("Levasser");
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_TortureRoom_Levasser_15";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
	}
	
	else if (sQuestName == "PZ_Etap6TortugaPytochnaya19") {
		sld = CharacterFromID("Levasser");
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_TortureRoom_Levasser_18";
		LAi_SetGroundSitType(sld);
		
		LAi_SetActorType(pchar);
		DoQuestCheckDelay("hide_weapon", 1.2);
		DoQuestCheckDelay("PZ_Etap6TortugaPytochnaya19_1", 1.5);
		
		if (CharacterIsAlive("Tibo"))
		{
			sld = CharacterFromID("Tibo");
			LAi_KillCharacter(sld);
		}
	}
	
	else if (sQuestName == "PZ_Etap6TortugaPytochnaya19_1") {
		LAi_SetActorType(pchar);
		if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko")) LAi_ActorRunToLocator(pchar, "goto", "goto8", "PZ_Etap6TortugaPytochnaya20", -1);
		if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne")) LAi_ActorRunToLocator(pchar, "goto", "goto7", "PZ_Etap6TortugaPytochnaya20", -1);
		if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo")) LAi_ActorRunToLocator(pchar, "goto", "goto9", "PZ_Etap6TortugaPytochnaya20", -1);
	}
	
	else if (sQuestName == "PZ_Etap6TortugaPytochnaya20") {
		LAi_FadeLong("PZ_Etap6TortugaPytochnaya21", "");
	}
	
	else if (sQuestName == "PZ_Etap6TortugaPytochnaya21") {
		LAi_SetStayType(pchar);
		if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sld = CharacterFromID("Mary");
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sld = CharacterFromID("Helena");
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_TortureRoom_Devushka_1";
		ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto5");
		ChangeCharacterAddressGroup(pchar, PChar.location, "goto", "goto3");
		LAi_SetActorType(sld);
		if (!CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko")) 
		{
			LAi_ActorSetGroundSitMode(sld);
			CharacterTurnToLoc(sld, "goto", "goto3");
			locCameraFromToPos(-15.32, 1.24, 1.31, true, -14.25, -1.00, -1.50);
		}
		CharacterTurnByChr(sld, pchar);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
	}
	
	else if (sQuestName == "PZ_TortureRoom_Levasser_Mertv1") {
		LAi_SetActorType(pchar);
		LAi_ActorAnimation(pchar, "Shot", "1", 1.5);
		DoQuestCheckDelay("PZ_TortureRoom_Levasser_Mertv2", 0.9);
	}
	
	else if (sQuestName == "PZ_TortureRoom_Levasser_Mertv2") {
		LAi_SetPlayerType(pchar);
		if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) Return_MaryOfficer();
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) Return_HelenaOfficer();
		if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom")) Return_LongwayOfficer();
		pchar.questTemp.PZ_LevasserMertv = true;
		pchar.questTemp.PZ_LevasserPobezhden = true;
		sld = CharacterFromID("Levasser");
		LAi_SetImmortal(sld, false);
		LAi_KillCharacter(sld);
		
		PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition.l1 = "locator";
		PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition.l1.location = "Tortuga_Torture_room";
		PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition.l1.locator_group = "reload";
		PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition.l1.locator = "reload1";
		PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition = "PZ_TortureRoom_Levasser_ObratnoNaBereg";
	}
	
	else if (sQuestName == "PZ_TortureRoom_Levasser_ObratnoNaBereg") {
		DoQuestReloadToLocation("Shore58", "goto", "goto4", "PZ_ObratnoNaBereg");
	}
	
	else if (sQuestName == "PZ_ObratnoNaBereg") {
		LAi_SetPlayerType(pchar);
		
		if (!CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva")) 
		{
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sld = CharacterFromID("Mary");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sld = CharacterFromID("Helena");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko")) sld.dialog.currentnode = "PZ_Etap6_NaBeregu_DevaZdorovaya_1";
			else sld.dialog.currentnode = "PZ_Etap6_NaBeregu_DevaBolnaya_1";
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto9");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		}
		if (CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva") && CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden") && CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo")) 
		{
			DoQuestCheckDelay("PZ_Final_SdaemKvestPuansi", 1.0);
		}
		if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom")) 
		{
			sld = CharacterFromID("Longway");
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto14");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
		}
		if (CheckAttribute(pchar, "questTemp.PZ_LevasserPlenen")) 
		{
			sld = CharacterFromID("Levasser");
			//ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto3");
			ChangeCharacterAddressGroup(sld, "My_Deck", "rld", "aloc2");
			LAi_SetActorType(sld);
			RemoveAllCharacterItems(sld, true);
			//LAi_ActorFollow(sld, pchar, "", -1);
		}
	}
	
	else if (sQuestName == "PZ_TortureRoom_Levasser_DevushkaMertva") {
		locCameraSleep(true);
		sld = CharacterFromID("Levasser");
		LAi_SetActorType(sld);
		if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) LAi_ActorTurnToCharacter(sld, CharacterFromID("Mary"));
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) LAi_ActorTurnToCharacter(sld, CharacterFromID("Helena"));
		LAi_ActorAnimation(sld, "Barman_idle", "1", 4);
		DoQuestCheckDelay("PZ_TortureRoom_Levasser_DevushkaMertva2", 3.0);
	}
	
	else if (sQuestName == "PZ_TortureRoom_Levasser_DevushkaMertva2") {
		LAi_FadeLong("PZ_TortureRoom_Levasser_DevushkaMertva3", "");
	}
	
	else if (sQuestName == "PZ_TortureRoom_Levasser_DevushkaMertva3") {
		pchar.questTemp.PZ_DevushkaMertva = true;
		if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sld = CharacterFromID("Mary");
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sld = CharacterFromID("Helena");
		LAi_SetImmortal(sld, false);
		DeleteAttribute(sld, "OfficerImmortal");
		if(CheckAttribute(sld, "Health.HP")) DeleteAttribute(sld, "Health.HP");
		if(CheckAttribute(sld, "Health.maxHP")) DeleteAttribute(sld, "Health.maxHP");
		sTemp = "RestoreHealth_" + sld.index;
		if(CheckAttribute(PChar, "quest.RestoreHealth_" + sld.index)) PChar.quest.(sTemp).over = "Yes";
		LAi_KillCharacter(sld);
		DoQuestCheckDelay("PZ_TortureRoom_Levasser_DevushkaMertva4", 1.5);
	}
	
	else if (sQuestName == "PZ_TortureRoom_Levasser_DevushkaMertva4") {
		sld = CharacterFromID("Levasser");
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_TortureRoom_Levasser_12";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
	}
	
	else if (sQuestName == "PZ_TortureRoom_Levasser_DevushkaMertva5") {
		LAi_SetActorType(pchar);
		if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
		{
			LAi_ActorGoToLocator(pchar, "goto", "goto8", "PZ_TortureRoom_Levasser_DevushkaMertva6", -1);
		}
		if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
		{
			LAi_ActorGoToLocator(pchar, "goto", "goto7", "PZ_TortureRoom_Levasser_DevushkaMertva6", -1);
		}
		if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
		{
			LAi_ActorGoToLocator(pchar, "goto", "goto9", "PZ_TortureRoom_Levasser_DevushkaMertva6", -1);
		}
	}
	
	else if (sQuestName == "PZ_TortureRoom_Levasser_DevushkaMertva6") {
		if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
		{
			CharacterTurnToLoc(pchar, "torture", "torture_1");
		}
		if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
		{
			CharacterTurnToLoc(pchar, "torture", "torture_2");
		}
		if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
		{
			CharacterTurnToLoc(pchar, "torture", "torture_3");
		}
		DoQuestCheckDelay("PZ_TortureRoom_Levasser_DevushkaMertva7", 1.0);
	}
	
	else if (sQuestName == "PZ_TortureRoom_Levasser_DevushkaMertva7") {
		pchar.questTemp.PZ_DevaMertva = true;
		DoQuestCheckDelay("TalkSelf_Quest", 1.0);
	}
	
	else if (sQuestName == "PZ_TortureRoom_Levasser_DevushkaMertva8") {
		pchar.questTemp.PZ_LevasserMertv = true;
		pchar.questTemp.PZ_LevasserPobezhden = true;
		
		if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
		{
			AddQuestRecord("PZ", "45");
			PChar.quest.PZ_Etap6_BrothelPoiskSestry.win_condition.l1 = "location";
			PChar.quest.PZ_Etap6_BrothelPoiskSestry.win_condition.l1.location = "Tortuga_brothelElite";
			PChar.quest.PZ_Etap6_BrothelPoiskSestry.win_condition = "PZ_Etap6_BrothelPoiskSestry";
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				sld = CharacterFromID("Longway");
				sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
				sld.dialog.currentnode = "PZ_TortureRoom_Longway_1";
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else chrDisableReloadToLocation = false;
		}
		else
		{
			PChar.quest.PZ_ObratnoNaBereg.win_condition.l1 = "location";
			PChar.quest.PZ_ObratnoNaBereg.win_condition.l1.location = "Shore58";
			PChar.quest.PZ_ObratnoNaBereg.win_condition = "PZ_ObratnoNaBereg";
		}
		LAi_SetPlayerType(pchar);
	}
	
	else if (sQuestName == "PZ_SDevushkoyKShin") {
		LAi_SetPlayerType(pchar);
		chrDisableReloadToLocation = false;
		if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) Return_MaryOfficer();
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) Return_HelenaOfficer();
		AddQuestRecord("PZ", "49");
		PChar.quest.PZ_Etap6_BrothelPoiskSestry.win_condition.l1 = "location";
		PChar.quest.PZ_Etap6_BrothelPoiskSestry.win_condition.l1.location = "Tortuga_brothelElite";
		PChar.quest.PZ_Etap6_BrothelPoiskSestry.win_condition = "PZ_Etap6_BrothelPoiskSestry";
	}
	
	else if (sQuestName == "PZ_SLongwayKShin") {
		LAi_SetPlayerType(pchar);
		chrDisableReloadToLocation = false;
		AddQuestRecord("PZ", "50");
		if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) AddQuestUserData("PZ", "sText", StringFromKey("Longway_49"));
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) AddQuestUserData("PZ", "sText", StringFromKey("Longway_50"));
		PChar.quest.PZ_Etap6_BrothelPoiskSestry.win_condition.l1 = "location";
		PChar.quest.PZ_Etap6_BrothelPoiskSestry.win_condition.l1.location = "Tortuga_brothelElite";
		PChar.quest.PZ_Etap6_BrothelPoiskSestry.win_condition = "PZ_Etap6_BrothelPoiskSestry";
	}
	
	// Сдаём квест Пунанси. Здесь прописываются итоги квеста:
	else if (sQuestName == "PZ_Final_SdaemKvestPuansi") {
		chrDisableReloadToLocation = false;
		bDisableLandEncounters = false;
		QuestOpenSeaExit();
		DeleteAttribute(pchar, "GenQuest.CabinLock");
		Island_SetReloadEnableGlobal("Tortuga", true);
		bQuestDisableMapEnter = false;
		LAi_SetPlayerType(pchar);
		QuestSetCurrentNode("Puancie", "PZ1");	//На Капстервиль
		AddMapQuestMarkCity("Charles", true);
		AddLandQuestMark(characterFromId("Puancie"), "questmarkmain");
		if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
		{
			sld = characterFromID("Mary");
			LAi_SetImmortal(sld, false);
			LAi_RemoveCheckMinHP(sld);
			Return_MaryOfficer();
			
			pchar.questTemp.MarySexBlock = true;
			pchar.quest.Mary_giveme_sex.over = "yes";
			pchar.quest.Mary_giveme_sex1.over = "yes";
		}
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
		{
			sld = characterFromID("Helena");
			LAi_SetImmortal(sld, false);
			LAi_RemoveCheckMinHP(sld);
			Return_HelenaOfficer();
		}
		if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
		{
			sld = characterFromID("Longway");
			LAi_SetImmortal(sld, false);
			LAi_RemoveCheckMinHP(sld);
			Return_LongwayOfficer();
		}
		AddQuestRecord("PZ", "48");
		if (!CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
		{
			AddQuestUserData("PZ", "sText", StringFromKey("Longway_67"));
			PChar.quest.PZ_RazgovorSVrachom.win_condition.l1 = "location";
			PChar.quest.PZ_RazgovorSVrachom.win_condition.l1.location = "Tortuga";
			PChar.quest.PZ_RazgovorSVrachom.win_condition = "PZ_RazgovorSVrachom";
		}
		CloseQuestHeader("PZ");
		Tortuga_DeleteShipGuard();
	}
	
	else if (sQuestName == "PZ_RazgovorSVrachom") {
		pchar.GenQuest.CabinLock = true;
		Island_SetReloadEnableGlobal("Tortuga", false);
		bQuestDisableMapEnter = true;
		
		DoQuestCheckDelay("PZ_RazgovorSVrachom_2", 2.5);
	}
	
	else if (sQuestName == "PZ_RazgovorSVrachom_2") {
		DeleteAttribute(pchar, "GenQuest.CabinLock");
		pchar.GenQuest.DontSetCabinOfficer = true;
		chrDisableReloadToLocation = true;
		Sea_CabinStartNow();
		
		if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sld = CharacterFromID("Mary");
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sld = CharacterFromID("Helena");
		RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
		RemoveCharacterEquip(sld, GUN_ITEM_TYPE);
		ChangeCharacterAddressGroup(sld, Get_My_Cabin(), "lay", "lay1");
		LAi_SetActorType(sld);
		LAi_ActorSetLayMode(sld);
		//sld = CharacterFromID("Baker");
		//ChangeCharacterAddressGroup(sld, Get_My_Cabin(), "rld", "loc1");
		DoQuestCheckDelay("PZ_RazgovorSVrachom_3", 6.0);
	}
	
	else if (sQuestName == "PZ_RazgovorSVrachom_3") {
		sld = CharacterFromID("Baker");
		ChangeCharacterAddressGroup(sld, Get_My_Cabin(), "reload", "reload1");
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_Baker_1";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	
	else if (sQuestName == "PZ_RazgovorSVrachom_4") {
		DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
		Island_SetReloadEnableGlobal("Tortuga", true);
		bQuestDisableMapEnter = false;
		chrDisableReloadToLocation = false;
		pchar.questTemp.GoldenGirl_Block = true;	// Запрещаем квест Дороже Золота
		
		Return_BakerOfficer();
		if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sld = CharacterFromID("Mary");
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sld = CharacterFromID("Helena");
		RemovePassenger(pchar, sld);
		
		if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko")) SetTimerCondition("PZ_DevushkaVstalaSKrovati", 0, 0, 3, false);
		if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne")) SetTimerCondition("PZ_DevushkaVstalaSKrovati", 0, 0, 7, false);
		if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo")) SetTimerCondition("PZ_DevushkaVstalaSKrovati", 0, 0, 14, false);
		
		SetTimerCondition("PZ_DevushkaLezhitVKrovati", 0, 0, 1, true);
	}
	
	else if (sQuestName == "PZ_DevushkaLezhitVKrovati") {
		if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sld = CharacterFromID("Mary");
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sld = CharacterFromID("Helena");
		ChangeCharacterAddressGroup(sld, Get_My_Cabin(), "lay", "lay1");
		LAi_SetActorType(sld);
		LAi_ActorSetLayMode(sld);
	}
	
	else if (sQuestName == "PZ_DevushkaVstalaSKrovati") {
		DeleteQuestCondition("PZ_DevushkaLezhitVKrovati");
		if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
		{
			sld = CharacterFromID("Mary");
			sld.model = "Mary";
		}
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
		{
			sld = CharacterFromID("Helena");
			sld.model = "Rumba";
		}
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_DevushkaVstalaSKrovati_Dialog1";
		ChangeCharacterAddressGroup(sld, Get_My_Cabin(), "rld", "loc1");
		if(Get_My_Cabin() == "My_Cabin_Medium2") ChangeCharacterAddressGroup(sld, Get_My_Cabin(), "goto", "goto3");
		if(Get_My_Cabin() == "My_Cabin_Huge") ChangeCharacterAddressGroup(sld, Get_My_Cabin(), "officers", "officer8");
		LAi_SetStayType(sld);
		AddLandQuestMark(sld, "questmarkmain");
		
		SetTimerCondition("PZ_DevushkaVstalaSKrovati2", 0, 0, 1, true);
	}
	
	else if (sQuestName == "PZ_DevushkaVstalaSKrovati2") {
		if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sld = CharacterFromID("Mary");
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sld = CharacterFromID("Helena");
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_DevushkaVstalaSKrovati_Dialog1";
		ChangeCharacterAddressGroup(sld, Get_My_Cabin(), "rld", "loc1");
		if(Get_My_Cabin() == "My_Cabin_Medium2") ChangeCharacterAddressGroup(sld, Get_My_Cabin(), "goto", "goto3");
		if(Get_My_Cabin() == "My_Cabin_Huge") ChangeCharacterAddressGroup(sld, Get_My_Cabin(), "officers", "officer8");
		LAi_SetStayType(sld);
	}
	
	else if (sQuestName == "PZ_DevushkaStoitVosstanovlenie") {
		DeleteQuestCondition("PZ_DevushkaVstalaSKrovati2");
		if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sld = CharacterFromID("Mary");
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sld = CharacterFromID("Helena");
		LAi_SetActorType(sld);
		
		if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko")) SetTimerCondition("PZ_DevushkaSnovaOfficer", 0, 0, 7, false);
		if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne")) SetTimerCondition("PZ_DevushkaSnovaOfficer", 0, 0, 14, false);
		if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo")) SetTimerCondition("PZ_DevushkaSnovaOfficer", 0, 0, 21, false);
	}
	
	else if (sQuestName == "PZ_DevushkaSnovaOfficer") {
		DeleteQuestCondition("PZ_DevushkaLezhitVKrovati");
		if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sld = CharacterFromID("Mary");
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sld = CharacterFromID("Helena");
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_DevushkaSnovaOfficer_Sex1";
		ChangeCharacterAddressGroup(sld, Get_My_Cabin(), "rld", "loc1");
		if(Get_My_Cabin() == "My_Cabin_Medium2") ChangeCharacterAddressGroup(sld, Get_My_Cabin(), "goto", "goto3");
		if(Get_My_Cabin() == "My_Cabin_Huge") ChangeCharacterAddressGroup(sld, Get_My_Cabin(), "officers", "officer8");
		LAi_SetStayType(sld);
		AddLandQuestMark(sld, "questmarkmain");
		
		SetTimerCondition("PZ_DevushkaSnovaOfficer2", 0, 0, 1, true);
	}
	
	else if (sQuestName == "PZ_DevushkaSnovaOfficer2") {
		if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sld = CharacterFromID("Mary");
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sld = CharacterFromID("Helena");
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_DevushkaSnovaOfficer_Sex1";
		ChangeCharacterAddressGroup(sld, Get_My_Cabin(), "rld", "loc1");
		if(Get_My_Cabin() == "My_Cabin_Medium2") ChangeCharacterAddressGroup(sld, Get_My_Cabin(), "goto", "goto3");
		if(Get_My_Cabin() == "My_Cabin_Huge") ChangeCharacterAddressGroup(sld, Get_My_Cabin(), "officers", "officer8");
		LAi_SetStayType(sld);
	}
	
	else if (sQuestName == "PZ_DevushkaSnovaOfficer3") {
		if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
		{
			Return_MaryOfficer();
			sld = CharacterFromID("Mary");
			EquipCharacterByItem(sld, "blade_31");
			DeleteAttribute(pchar, "questTemp.MarySexBlock");
		}
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
		{
			Return_HelenaOfficer();
			sld = CharacterFromID("Helena");
			EquipCharacterByItem(sld, "pirate_cutlass");
		}
		AddPassenger(pchar, sld, false);
		chrDisableReloadToLocation = false;
		DeleteAttribute(pchar, "questTemp.PZ_DevushkaSnovaOfficer");
		DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
	}
	
	else if (sQuestName == "PZ_AfterPoincyLongwayDialog") {
		chrDisableReloadToLocation = true;
		
		sld = characterFromID("Longway");
		if (!CharacterIsHere("Longway")) ChangeCharacterAddressGroup(sld, PChar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"));
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_Longway_101";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	
	else if (sQuestName == "PZ_LevasserVGostyahUPuansie") {
		StartQuestMovie(true, false, true);
		LAi_SetStayType(pchar);
		LAi_FadeLong("PZ_LevasserVGostyahUPuansie2", "");
	}
	
	else if (sQuestName == "PZ_LevasserVGostyahUPuansie2") {
		sld = characterFromID("Levasser");
		ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
		TeleportCharacterToPosAy(sld, 3.46, 0.89, -4.01, -2.00);
		LAi_SetActorType(sld);
		
		sld = GetCharacter(NPC_GenerateCharacter("PZ_SoldFra_1", "sold_fra_"+(rand(7)+1), "man", "man", sti(pchar.rank), FRANCE, 0, true, "soldier"));
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
		TeleportCharacterToPosAy(sld, 4.55, 0.89, -4.51, -2.00);
		
		sld = GetCharacter(NPC_GenerateCharacter("PZ_SoldFra_2", "sold_fra_"+(rand(7)+1), "man", "man", sti(pchar.rank), FRANCE, 0, true, "soldier"));
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
		TeleportCharacterToPosAy(sld, 3.70, 0.89, -2.92, -2.00);
		
		sld = characterFromID("Puancie");
		sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
		sld.dialog.currentnode = "PZ_PuansieDialogWithLevasser_1";
		LAi_SetActorType(sld);
		LAi_ActorSetHuberMode(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
		locCameraFromToPos(-1.96, 1.96, -6.00, true, 2.62, 0.71, -4.16);
		pchar.GenQuest.BlockDialogCamera = true;
	}
	
	else if (sQuestName == "PZ_LevasserVGostyahUPuansie3") {
		sld = characterFromID("Levasser");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocation(sld, "reload", "reload1", "", "", "", "", -1);
		sld.location = "None";
		sld = characterFromID("PZ_SoldFra_1");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocation(sld, "reload", "reload1", "", "", "", "", -1);
		sld.location = "None";
		sld = characterFromID("PZ_SoldFra_2");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocation(sld, "reload", "reload1", "", "", "", "", -1);
		sld.location = "None";
		
		DoQuestCheckDelay("PZ_LevasserVGostyahUPuansie4", 2.5);
		Achievment_Set("ach_CL_129");
	}
	
	else if (sQuestName == "PZ_LevasserVGostyahUPuansie4") {
		DeleteAttribute(pchar, "GenQuest.BlockDialogCamera");
		LAi_SetStayType(pchar);
		LAi_FadeLong("PZ_LevasserVGostyahUPuansie5", "");
	}
	
	else if (sQuestName == "PZ_LevasserVGostyahUPuansie5") {
		LAi_SetPlayerType(pchar);
		locCameraTarget(PChar);
		locCameraFollow();
		sld = characterFromID("Puancie");
		sld.dialog.filename = "Governor\Puancie.c";
		sld.dialog.currentnode = "PZ5";
		LAi_SetActorType(sld);
		LAi_ActorSetHuberMode(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
		EndQuestMovie();
	}
	
	else if (sQuestName == "PZ_TortureRoomClose") {//закрыть пыточную
		sld = &Locations[FindLocation("Tortuga_Cave")];
		sld.locators_radius.reload.reload3_back = 0;
	}
	
	else
	{
		condition = false;
	}
	
	return condition;
}

void PZ_Kapstervil_OstavlyaemZapisku_1_1()
{
	locCameraSleep(true);
}

void PZ_MayakPodslushivanie_2()
{
	locCameraToPos(1.91, 31.11, -13.72, false);
	DoQuestCheckDelay("PZ_MayakPodslushivanie_3", 1.5);
}
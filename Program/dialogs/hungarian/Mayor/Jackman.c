// Якоб Джекман
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

// ============================= блок angry ==========>>>>>>>>>>>>>>>>>>>>>>>>>
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
            switch (npchar.angry.kind) //сюда расписываем реакцию ангри. В npchar.angry.name пробелы удалены!!!
            {
                case "repeat":
                    if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
                    if (npchar.angry.name == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                break;
            }
        }
    }
// <<<<<<<<<<<<<<<<<<<<<<======= блок angry ===================================
// ============================================================================

	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
            dialog.text = NPCStringReactionRepeat(""+ GetSexPhrase("Van valami mondanivalója? Nincs? Akkor tûnj el innen!","Ha, " + pchar.name + "! Van valami dolgod velem? Nem? Akkor ne zavarjon.") +"",
                         "Azt hiszem, elég világosan fejeztem ki magam, ne idegesítsen tovább.", "Bár világosan fejeztem ki magam, te továbbra is idegesítesz!",
                         "Rendben, kezdek belefáradni ebbe a bunkóságba, takarodj, te szörnyszülött.", "repeat", 3, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Én máris elmegyek.",
                                               "Persze, Jackman...",
                                               "Bocs, Jackman...",
                                               "Aú...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";

			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Megôrültél? Mészárost akartál játszani? Minden kalóz haragszik rád, fiú, jobb, ha elhagyod ezt a helyet...", "Úgy tûnik, hogy megharagudtál, fiú. Ki akartad nyújtani a kezed egy kicsit? Ne vedd sértésnek, de nincs itt semmi keresnivalód. Tûnj innen!");
				link.l1 = RandPhraseSimple("Figyelj, én helyre akarom hozni a helyzetet...", "Segítsen megoldani ezt a problémát...");
				link.l1.go = "pirate_town";
				break;
			}

			//--> Сага
			if(CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "maruntown")
			{
				link.l1 = "Hol találom Jimmy Higgins-t?";
				link.l1.go = "Saga_Jimmy";
			}	
			if(CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "jackman")
			{
				link.l1 = "Megint én, Jackman. Azt mondják, hogy néhány eltûnt embert keresel...";
				link.l1.go = "Saga_search";
			}	
			//<-- Сага

			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
				{
					link.l1 = "A foglyáról van szó.";
					link.l1.go = "CapComission1";
					DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
				}	
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.PirateShips"))
				{
					link.l1 = "Hello, Jackman. A küldetésedrôl...";
					link.l1.go = "CapComission3";
				}
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
				{
					link.l1 = "A foglyáról van szó.";
					link.l1.go = "CapComission6";
				}
			}	
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

        case "I_know_you_good":
            dialog.text = NPCStringReactionRepeat(GetFullName(pchar) + ", örülök, hogy látlak! Mit akarsz?",
                         "Mit akarsz?", "Már megint te? Ne zavard az embereket, ha nincs semmi dolgod!",
                         "Te "+ GetSexPhrase("jó magánzó vagy"," jó lány") +", úgyhogy egyelôre élhetsz. De nem akarok veled többet beszélni.", "repeat", 10, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Csak látogatóba jöttem.",
                                               "Semmi...",
                                               "Rendben, Jackman, sajnálom...",
                                               "Francba! Nos, ahogy mondod...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";

			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Megôrültél? Hentest akartál játszani? Minden kalóz haragszik rád, fiú, jobb ha elhagyod ezt a helyet...");
				link.l1 = RandPhraseSimple("Figyelj, én helyre akarom hozni a helyzetet...", "Segítsen megoldani ezt a problémát...");
				link.l1.go = "pirate_town";
				break;
			}

			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
			{
				link.l1 = "A foglyáról van szó.";
				link.l1.go = "CapComission1";
				DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
			}				
		break;

//-----------------------------------------пиратская сага----------------------------------------------------
		case "Saga_Jimmy":
			dialog.text = "Tényleg! Valakinek szüksége van erre a lusta seggre! Már napok óta egyedül issza a rumot a kunyhójában. Nem tanácsolom, hogy meglátogasd. Még józanul sem a legjobb ember...";
			link.l1 = "Semmi baj, én sem vagyok szent. Hol van a kunyhója?";
			link.l1.go = "Saga_Jimmy_1";
		break;
		
		case "Saga_Jimmy_1":
			dialog.text = "A kocsma elôtt. Jó helyet választott, hogy gyorsan elszaladjon egy italért.";
			link.l1 = "Köszönjük!";
			link.l1.go = "Saga_Jimmy_2";
		break;
		
		case "Saga_Jimmy_2":
			DialogExit();
			pchar.quest.Saga_createJimmy.win_condition.l1 = "location";
			pchar.quest.Saga_createJimmy.win_condition.l1.location = "FortOrange_House1";
			pchar.quest.Saga_createJimmy.function = "Saga_CreateJimmy";
			pchar.questTemp.Saga = "jimmy";
		break;
		
		case "Saga_search":
			dialog.text = "És ki mondta ezt neked? Az a részeges Higgins? Megtudtál valamit Gladys Chandlerrôl vagy Henry-rôl, a hóhérról?";
			link.l1 = "Igazából semmi különöset, de valami konkrétumot szeretnék megtudni arról a Hóhérról.";
			link.l1.go = "Saga_search_1";
		break;
		
		case "Saga_search_1":
			dialog.text = "Nincs mit tudni róla. Most már kevesen emlékeznek rá, de húsz évvel ezelôtt Henry nagyon népszerû volt a kurvák körében Bridgetowntól Tortugáig. Hát persze! A 'Neptun', hajóskapitánya, aki magának Butcher kapitánynak a parancsnoksága alatt állt! Persze már nagyon öreg lehet, ha még él.\nAz esélyek csekélyek, de tudod, semmi sem lehetetlen. Húszezer pezót fizetek bármilyen információért róla, a dupláját, ha élve hozzák ide.";
			link.l1 = "Mennyit fizet Gladysért és a lányáért?";
			link.l1.go = "Saga_search_2";
		break;
		
		case "Saga_search_2":
			dialog.text = "Ó, ô nem a lánya. Ha élve hozza el a lányt, egy csomó dublont fizetek. Gladys nem érdekel. Kérdések?";
			link.l1 = "Bárcsak tudnám ennek a felhajtásnak az okát, de nem kérdezem. Úgy néz ki, hogy megrövidítheti az életrajzomat.";
			link.l1.go = "Saga_search_3";
		break;
		
		case "Saga_search_3":
			dialog.text = "Talán... Ezek a titkok nem tartoznak rád. Kevesebbet tudni, tovább élni. Ne próbálj megint ilyen kérdéseket feltenni nekem, mert már kezdek gyanakodni, hogy valami nincs rendben veled. Tûnj el, mielôtt meggondolom magam.";
			link.l1 = "Viszlát, báró!";
			link.l1.go = "Saga_search_4";
		break;
		
		case "Saga_search_4":
			DialogExit();
			AddQuestRecord("Saga", "6");
			if (CheckAttribute(pchar, "questTemp.Saga.Jimmysecret"))
			{
				AddQuestUserData("Saga", "sText", "Antiguába, most. A korvettre fel kell szállni.");
				DeleteAttribute(pchar, "questTemp.Saga.Jimmysecret");
			}
			pchar.quest.Saga_createDonovan.win_condition.l1 = "location";
			pchar.quest.Saga_createDonovan.win_condition.l1.location = "Antigua";
			pchar.quest.Saga_createDonovan.function = "Saga_createDonovan";
			pchar.questTemp.Saga = "donovan";
		break;
		
		// абордаж, в каюте
		case "Jackman_abordage":
			dialog.text = "Ha! Újra találkozunk, kapitány "+GetFullName(pchar)+". Elismerem, méltó ellenfél vagy, annak ellenére, hogy megpróbálod magadat Maroon-Townban együgyûnek beállítani. Megtudtam valamit rólad, a holland Nyugat-indiai Társasággal folytatott intrikáidra fény derült... Most már értem, milyen típus vagy.";
			link.l1 = "Én is ismerem a te fajtádat, Jacob. Szóval ne keltsünk illúziókat.";
			link.l1.go = "Jackman_abordage_1";
		break;
		
		case "Jackman_abordage_1":
			dialog.text = "És hogyan csaptál be engem 'Marlin'! Gondolom, szegény bátyám meghalt...";
			link.l1 = "Gondolom, bosszút akarsz állni érte? De nekem is van egy hosszú számlám számodra. A sarokba szorított Nathanielért, a feleségéért, a fregattjáért, a megrágalmazott Sharkért, Blaze Sharpért...";
			link.l1.go = "Jackman_abordage_2";
		break;
		
		case "Jackman_abordage_2":
			dialog.text = "Blaze? Nem én öltem meg.";
			link.l1 = "Még ha ez igaz is, a listám többi része elég. Elegem van a nevedbôl. Elég a szavakból, Jackman! A pengéink beszélni fognak!";
			link.l1.go = "Jackman_abordage_3";
		break;
		
		case "Jackman_abordage_3":
			dialog.text = "Egy ilyen heves bolond... A fenébe veled! Most már jobb, ha kitartasz! Jacob Jackmant még sosem gyôzték le! Carpacho, épp idôben jöttél! Gyere ide!";
			link.l1 = "...";
			link.l1.go = "Jackman_abordage_4";
		break;
		
		case "Jackman_abordage_4":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "Saga_AfterJackmanBoarding");
			AddDialogExitQuest("MainHeroFightModeOn");
			// подкрепление
			int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+12;
			int iScl = 30 + 2*sti(pchar.rank);
			sld = GetCharacter(NPC_GenerateCharacter("Saga_JackmanCabinHelper", "citiz_58", "man", "man", iRank, sti(npchar.nation), 0, true, "quest"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_21", "pistol4", "bullet", iScl*2+100);
			LAi_SetCheckMinHP(sld, 150, true, "Saga_DannyHurryHelp");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_BRDENEMY);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			sld = characterFromId("Danielle");
			RemovePassenger(Pchar, sld);
		break;

		//*************************** Генератор "Captain's offer - Ransom" **********************
		case "CapComission1":
			dialog.text = "Ha-ha. Azt hiszed, hogy csak egy foglyom van itt? Nevezd meg.";
			link.l1 = pchar.GenQuest.CaptainComission.SlaveName + ". Itt van?";
			link.l1.go = "CapComission2";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
		break;

		case "CapComission2":
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.DaysLeft"))
			{
				dialog.text = "Itt volt. Eladtam annak a barbadosi ültetvénytulajdonosnak - Bishop ezredesnek, amikor egy hete itt járt.";
				link.l1 = "A fenébe...";
				link.l1.go = "CapComission2_1";
			}
			else
			{
				dialog.text = "Á, végre. Arra gondoltam, hogy eladom annak a barbadosi ültetvényesnek, aki egy-két héten belül itt lesz... Van váltságdíja?";
				link.l1 = "Nézze, van egy kis probléma... Valójában, nincs annyi pénzem. De kész vagyok dolgozni.";
				link.l1.go = "CapComission2_2";
				if(makeint(pchar.money) > 150000)
				{
					link.l2 = "Jó, hogy nem adtad el. Itt vannak az érméi - 150.000 pezó. Hol kaphatom meg?"
					link.l2.go = "CapComission2_3";
				}	
			}
		break;
		
		case "CapComission2_1":
			dialog.text = "Túl lassú voltál... És miért érdekel téged? Csak a rokonaival tárgyaltam.";
			link.l1 = "Ôk kértek meg, hogy jöjjek ide.";
			link.l1.go = "CapComission2_11";
		break;
		
		case "CapComission2_11":
			dialog.text = "Hát, elkéstél. Nem tehetek semmit.";
			link.l1 = "Figyelj, mennyiért adtad el ôt, ha nem titok?"; 
			link.l1.go = "CapComission2_12";
		break;
		
		case "CapComission2_12":
			dialog.text = "Eh, ez nem az. De nem mondom meg... Nevetni fogsz, ha megteszem. Ha-ha-ha-ha-ha! Viszontlátásra.";
			link.l1 = "Viszlát...";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "10");
			AddQuestUserData("CaptainComission1", "sName", "Jackman")); // belamour gen
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			CaptainComission_GenerateManager();
		break;
		
		case "CapComission2_2":
			if(rand(1) == 0)
			{
				dialog.text = "Nocsak, nocsak... Van egy kis dolgom... Nem is tudom, hogy kezdjem. El kell süllyesztenem egy kalózt, aki átlépte a határt.";
				link.l1 = "Nem lehet egyszerûen megölni a dzsungelben?";
				link.l1.go = "CapComission2_2_1";
			}
			else
			{
				dialog.text = "Nos, " + pchar.name + ", tudod, ez nem így mûködik. Gyere vissza a pénzzel, és megkapod a gyengébbik feledet, ha-ha.";
				link.l1 = "Jól van. Viszlát.";
				link.l1.go = "CapComission2_4";
			}
		break;

		case "CapComission2_2_1":
			dialog.text = "Az üzlet nem így mûködik, tudod... Nem kell a halála, meg kell tanítanom néhány embert, hogy ne vegyék el a zsákmányom egy részét. De ha a cápákat eteti, nem leszek mérges.";
			link.l1 = "Miért nem küldöd utána a saját embereidet?";
			link.l1.go = "CapComission2_2_2";
		break;
		
		case "CapComission2_2_2":
			CaptainComission_GetRandomShore();
			pchar.GenQuest.CaptainComission.ShipName1 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.ShipName2 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			sLoc = XI_ConvertString(pchar.GenQuest.CaptainComission.Island + "Abl");
			dialog.text = "Hm... Nos, "  + GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.UnknownPirateName, NAME_NOM) + " meggyôzött néhány kalózt, hogy a zsákmányuk egy részét a mi rejtekhelyünkön tartják, nem messze " + XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Gen") + ". Két hajójuk '" + pchar.GenQuest.CaptainComission.ShipName1 + "' és '" + pchar.GenQuest.CaptainComission.ShipName2 + "' nemrég vetett horgonyt és elhajózott " + sLoc + ". Most már érted, miért nem bízhatom az embereimre ezt a munkát?";
			link.l1 = "Én igen. Mennyi idôm van?";
			link.l1.go = "CapComission2_2_3";
		break;
		
		case "CapComission2_2_3":
			dialog.text = "12-15 nap, nem több, gondolom. Nem akarom, hogy eljussanak a rejtekhelyre, különben hülyeség lesz elsüllyeszteni ôket az értékes rakománnyal. Ebben az esetben jobb lenne, ha ide hoznák...";
			link.l1 = "Rendben, én benne vagyok. Megpróbálom elkapni ôket.";
			link.l1.go = "CapComission2_2_4";
		break;
		
		case "CapComission2_2_4":
			AddQuestRecord("CaptainComission1", "24");
			AddQuestUserData("CaptainComission1", "sName", "Jackman")); // belamour gen
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sShipName1", pchar.GenQuest.CaptainComission.ShipName1);
			AddQuestUserData("CaptainComission1", "sShipName2", pchar.GenQuest.CaptainComission.ShipName2);
			AddQuestUserData("CaptainComission1", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Dat")); // belamour gen
			AddQuestUserData("CaptainComission1", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.GenQuest.CaptainComission.Island) + "Voc")); // belamour gen
			pchar.quest.CapComission_PirateAttack.win_condition.l1 = "location";
            pchar.quest.CapComission_PirateAttack.win_condition.l1.location = pchar.GenQuest.CaptainComission.Island;
            pchar.quest.CapComission_PirateAttack.function = "CaptainComission_GeneratePirateShips"; 
			SetFunctionTimerCondition("CaptainComission_PirateShipsOver", 0, 0, 15, false);
			pchar.GenQuest.CaptainComission.PirateShips = "goaway";	
			DialogExit();
		break;
		
		case "CapComission2_3":
			dialog.text = "Ne aggódjatok. Az embereim majd átadják a hajódnak. És miért érdekel téged?";
			link.l1 = "Nem érdekel. A rokonai kértek meg, hogy szállítsam le.";
			link.l1.go = "CapComission2_31";
		break;
		
		case "CapComission2_31":
			dialog.text = "Á, rendben van. Már majdnem megbántam, hogy ilyen alacsony árat adtam az emberedért. Ha-ha-ha-ha-ha-ha. Viszontlátásra.";
			link.l1 = "Viszlát.";
			link.l1.go = "CapComission2_32";
		break;
		
		case "CapComission2_32":
			AddQuestRecord("CaptainComission1", "9");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));	// belamour gen		
			addMoneyToCharacter(pchar, -150000);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission2_4":
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
			{
				AddQuestRecord("CaptainComission1", "31");
				AddQuestUserData("CaptainComission1", "sName", "Jackman"); // belamour gen
				//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			}	
			pchar.GenQuest.CaptainComission.RepeatSpeak = true;		
			DialogExit();
		break;
		
		case "CapComission3":
			dialog.text = "Szóval, , " + GetFullName(pchar) + ", elsüllyesztetted a haveromat? He-he-he-he...";
			if(pchar.GenQuest.CaptainComission.PirateShips == "goaway")
			{
				link.l1 = "Nem. Nem sikerült elkapnom ôket. És nem találkoztam velük, amikor visszatértem.";
				link.l1.go = "CapComission4";
			}
			if(pchar.GenQuest.CaptainComission.PirateShips == "died")	
			{
				link.l1 = "Én igen. Elküldtem ôket, hogy etessék a cápákat.";
				link.l1.go = "CapComission5";
			}
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
		break;
		
		case "CapComission4":
			dialog.text = "A francba! Találkoztál velük vagy sem, most már mindegy! És mi lesz a következô javaslatod?";
			link.l1 = "Talán van egy könnyebb munkád számomra?";
			link.l1.go = "CapComission4_1";
			link.l2 = "Figyelj, Jackman, csökkentsd az árat a fogolyért...";
			link.l2.go = "CapComission4_2";
		break;
		
		case "CapComission4_1":
			dialog.text = "Nem.";
			link.l1 = "Akkor viszlát...";
			link.l1.go = "CapComission4_3";
		break;
		
		case "CapComission4_2":
			dialog.text = "Lejjebb vinni az árat? Épp most vesztettem el a készletemet a hozzá nem értésed miatt! És most felemelhetem az árat! Elviheti 200,000 pesoért, ha akarja, vagy eltûnhet innen a pokolba.";
			link.l1 = "Ez túl drága... Viszlát...";
			link.l1.go = "CapComission4_4";
			if(sti(pchar.money) >= 200000)
			{
				link.l2 = "A francba, vedd el az érméidet.";
				link.l2.go = "CapComission4_5";
			}	
		break;
		
		case "CapComission4_3":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "27");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();
		break;
		
		case "CapComission4_4":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "28");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
		break;
		
		case "CapComission4_5":
			dialog.text = "Rendben, elviheted ezt a gyengét...";
			link.l1 = "Ég veled!";
			link.l1.go = "CapComission4_6";
		break;
		
		case "CapComission4_6":
			addMoneyToCharacter(pchar, -200000);
			AddQuestRecord("CaptainComission1", "29");
			AddQuestUserData("CaptainComission1", "sName", "Jackman"); // belamour gen
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc")); // belamour gen
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			pchar.GenQuest.CaptainComission.SlaveAddMoney = true;
			DialogExit();	
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission5":
			dialog.text = "Ho-ho! Szép munka! Fogd a gyengédet és sok szerencsét.";
			link.l1 = "Köszönöm. Viszlát.";
			link.l1.go = "CapComission5_1";
		break;
		
		case "CapComission5_1":
			AddQuestRecord("CaptainComission1", "34");
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc")); // belamour gen
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission6":
			dialog.text = "Elhoztad a pénzt, Charles? Nem vicceltem azzal, hogy eladom az embert az ültetvénynek.";			
			link.l1 = "Figyelj, "+ NPChar.name +", van egy probléma... Nincs annyi pénzem. De kész vagyok dolgozni.";
			link.l1.go = "CapComission2_2";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "Jó, hogy nem adtad el. Itt vannak az érméi - 150.000 pezó. Hol kaphatom meg?"
				link.l2.go = "CapComission2_3";
			}			
		break;
		
		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Rablás!!! Ez elfogadhatatlan! Készülj fel, "+ GetSexPhrase("fiú","lány") +"...", "Hé, mi a fenét csinálsz ott?! Azt hitted, hogy kirabolhatsz? Végeztél...", "Várj, mi a fene? Vedd le a kezed! Kiderült, hogy te egy tolvaj vagy! Vége a sornak, te szemétláda...");
			link.l1 = LinkRandPhrase("A francba!", "Carramba!!", "A francba!!");
			link.l1.go = "PL_Q3_fight";
		break;
					
		// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple("Tûnj el innen!","Takarodj az otthonomból!");
			link.l1 = "Oups...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся с Джекменом через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Ne zavarj az olcsó beszédeddel. Legközelebb nem fog tetszeni az eredmény...";
        			link.l1 = "Megvan.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryRepeat_2":
            dialog.text = "Vége, nincs beszéd." "Nem akarok veled többet beszélgetni, úgyhogy jobb, ha nem zavarsz.";
			link.l1 = RandPhraseSimple("Ahogy kívánod...", "Akkor jó...");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся с Джекменом через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Remélem, hogy több tiszteletet fogsz mutatni, és nem leszel többé bunkó? Különben meg kell, hogy öljelek. Az nagyon kellemetlen lenne.";
        			link.l1 = "Biztos lehetsz benne, Jackman, hogy meg fogom.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
		break;
		case "AngryExitAgainWithOut":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
            DoReloadCharacterToLocation("Fortorange_town","reload","reload6");
		break;
		// <<<<<<<<<<<<============= блок нод angry =============================
		case "pirate_town":
            dialog.text = "Megoldani a problémát? Érti, hogy mit tett? Mindegy, hozz nekem egymillió pezót, és én ráveszem a srácokat, hogy felejtsék el a 'feats'. Ha nem tetszik az ötlet, akkor mehetsz a pokolba.";
			if (sti(Pchar.money) >= 1000000)
			{
				link.l1 = "Rendben, kész vagyok fizetni.";
				link.l1.go = "pirate_town_pay";
			}
			link.l2 = "Megvan. Elmegyek.";
			link.l2.go = "pirate_town_exit";
		break;
		
		case "pirate_town_exit":
			DialogExit();
            bDisableFastReload = true;//закрыть переход
			pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
			pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
			pchar.quest.pirate_in_town.function = "TownPirate_battle";
		break;
		
		case "pirate_town_pay":
            dialog.text = "Jól van. Tekintsd magad újra tisztának. De remélem, hogy nem fogsz többé ilyen undorító dolgokat csinálni.";
			link.l1 = "Nem fogok. Túl drága nekem. Viszlát...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000000);
			pchar.GenQuest.Piratekill = 0;
		break;
	}
}

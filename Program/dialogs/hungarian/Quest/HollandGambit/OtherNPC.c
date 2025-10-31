// диалоги прочих НПС
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Egy bogár. Mondd meg a fejlesztôknek.";
			link.l1 = "Úgy lesz!";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			if (npchar.id == "HWICFernando") NextDiag.CurrentNode = "Fernando";
			DialogExit();
		break;
	
//---------------------------------------за Голландию--------------------------------------------------
		//сопроводить торговца
		case "Baltazar":
			pchar.quest.Create_BaltazarOver.over = "yes";//снять прерывание
			dialog.text = "Micsoda szerencse! Kapitány, véletlenül szükségem van egy kísérôre Philipsburgba, nagyon sürgôsen...";
			link.l1 = "Te vagy Balthazar Ridderbock?";
			link.l1.go = "Baltazar_1";
			DelLandQuestMark(npchar);
		break;
		
		case "Baltazar_1":
			dialog.text = "Mi a fene, máris híresebb vagyok, mint az alkirály! Ki maga? Mit akar?";
			link.l1 = "Kapitány vagyok " + GetFullName(pchar) + ". Lucas Rodenburg küldött hozzád. Felhatalmaztak, hogy a védelmem alá vegyem önt és a hajóját.";
			link.l1.go = "Baltazar_2";			
		break;
		
		case "Baltazar_2":
			dialog.text = "Oh, mynheer Rodenburg biztosan meghallotta a segítségkérésemet! Tudja, van egy magánhajós...";
			link.l1 = "Hagyjuk a történetének részleteit, már ismerem ôket.";
			link.l1.go = "Baltazar_3";			
		break;
		
		case "Baltazar_3":
			dialog.text = "Hát persze, hogy ismerem! Már így is túl sok idôt vesztettem... Legkésôbb két hét múlva meg kell érkeznem Philipsburgba.";
			link.l1 = "Akkor menj a hajódra, és készülj fel a kihajózásra. Azonnal kihajózunk!";
			link.l1.go = "Baltazar_4";			
		break;
		
		case "Baltazar_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 4);
			SetCharacterRemovable(npchar, false);
			npchar.CompanionEnemyEnable = false; //всегда друзья
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.loyality = MAX_LOYALITY;
			AddQuestRecord("Holl_Gambit", "1-3");
			AddMapQuestMarkCity("Marigo", true);
			if(bImCasual)
			{
				NewGameTip("Felfedezô mód: a küldetés idôtartama megduplázódott");
				SetFunctionTimerCondition("Baltazar_ConvoyOver", 0, 0, 28, false);
			}
			else SetFunctionTimerCondition("Baltazar_ConvoyOver", 0, 0, 14, false); //таймер
			pchar.quest.BaltazarConvoy_fail.win_condition.l1 = "NPC_Death";//прерывание на потопление сопровождаемого
			pchar.quest.BaltazarConvoy_fail.win_condition.l1.character = "Baltazar";
			pchar.quest.BaltazarConvoy_fail.function = "Baltazar_fail";
			pchar.quest.BaltazarConvoy_complete.win_condition.l1 = "location";//прерывание на выполнение
			pchar.quest.BaltazarConvoy_complete.win_condition.l1.location = "Marigo_town";
			pchar.quest.BaltazarConvoy_complete.function = "Baltazar_complete";
			if (rand(1) == 0)
			{
				BaltazarPirateGlobalCreate();
			}
			else
			{
				pchar.questTemp.HWIC.Holl.BaltazarAttack = "true";
				pchar.quest.BaltazarConvoy_Attack.win_condition.l1 = "location";//прерывание на выполнение
				pchar.quest.BaltazarConvoy_Attack.win_condition.l1.location = "SentMartin";
				pchar.quest.BaltazarConvoy_Attack.function = "BaltazarPirateSeaCreate";
			}
		break;
		
		case "Baltazar_5":
			dialog.text = "Köszönöm a segítségét, kapitány! Az ön védelme nem is jöhetett volna jobbkor, kérem, fogadja el köszönetemet és ezt az 5 000 pesót.";
			link.l1 = "Hmm... Ez nem túl nagylelkû jutalom egy élet megmentéséért...";
			link.l1.go = "Baltazar_6";			
		break;
		
		case "Baltazar_6":
			dialog.text = "Egyébként, ha lesz rá lehetôségem, küldök egy levelet mynheer Rodenburgnak - a lehetô legnagyobb elismeréssel a tetteiért. Most mennem kell.";
			link.l1 = "Nos, akkor viszlát, Balthazar.";
			link.l1.go = "Baltazar_7";			
		break;
		
		case "Baltazar_7":
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2_back", "none", "", "", "", 3.0);
			AddQuestRecord("Holl_Gambit", "1-6");
			AddMoneyToCharacter(pchar, 5000);
			ChangeCharacterComplexReputation(pchar,"nobility", 2); 
			ChangeCharacterNationReputation(pchar, HOLLAND, 1);
			ChangeOfficersLoyality("good_all", 1);
			pchar.questTemp.HWIC.Holl = "BaltazarCom";
			AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
			AddMapQuestMarkCity("Villemstad", true);
		break;
		
		//командировка в Сантьяго
		case "Santiago_Trip":
			dialog.text = "Senor! Várj... úgy tûnik, elejtettél valamit...";
			link.l1 = "Mi az? Ah?!";
			link.l1.go = "Santiago_Trip_1";
		break;
		
		case "Santiago_Trip_1":
			DialogExit();
			PlaySound("People Fight\Death_NPC_08.wav");
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("Hátulról ütötték le eszméletlenül.", "", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 15, 10); //крутим время
			RecalculateJumpTable();
			DoQuestFunctionDelay("SantiagoTripInHouse", 4.0);
		break;
		
		case "Santiago_Trip_2":
			dialog.text = "Bocsánat, barátom - csak enyhén kellett megütnöm, hogy ne okozzon bajt. Tudom, hogy valószínûleg fáj a fejed, de mindegy, túl fogod élni. Ha lesz rá idô...";
			link.l1 = "Ki vagy te, a fenébe is, és mi folyik itt?";
			link.l1.go = "Santiago_Trip_3";
		break;
		
		case "Santiago_Trip_3":
			dialog.text = "Nyugi, nyugi, barátom - különben megint le kell nyugtatnom téged. Ugye nem akarjuk, hogy ezek a martalócok betörjenek, és rozsdás kardjukkal csörömpöljenek? Csendben kell beszélnünk.";
			link.l1 = "Add vissza a kardomat, te köcsög, és szépen elbeszélgetünk, esküszöm!";
			link.l1.go = "Santiago_Trip_4";
		break;
		
		case "Santiago_Trip_4":
			dialog.text = "Gyors kisember vagy, ugye? Egyelôre nincs szükség acélra. Mondd el, amit tudni akarok, és talán egy darabban hagyod el ezt a helyet. Világos? Akkor beszélgessünk egy kicsit.\nHallgatsz? Jó, akkor megegyeztünk. Mit vittél Rodenburgból a bankárhoz?";
			link.l1 = "Egy levelet.";
			link.l1.go = "Santiago_Trip_5";
		break;
		
		case "Santiago_Trip_5":
			dialog.text = "Okos. Tudom, hogy nem egy csokor százszorszép volt. Mi volt abban a levélben, fiam?";
			link.l1 = "Honnan tudjam? Nem szoktam elolvasni a rám bízott leveleket. Talán szerelmes üzenet volt. Tudod, mit mondanak a hatalommal bíró emberekrôl...";
			link.l1.go = "Santiago_Trip_6";
		break;
		
		case "Santiago_Trip_6":
			dialog.text = "...Egy ôszinte kapitányt elég ritka látni ezekben a nyomorúságos idôkben. Nos, ez rossz hír önnek. Mit mondott ez az istenverte bankár, amikor megkapta a csomagot? Miféle üzletet kötött a hollandokkal?";
			link.l1 = "Franciaországból csempészett parfümökkel kereskednek... vagy bajor tehénszarral, azt hiszem.";
			link.l1.go = "Santiago_Trip_7";
			link.l2 = "A kérdés valamilyen kártérítésrôl szólt. Csak ennyit tudok.";
			link.l2.go = "Santiago_Trip_8";
		break;
		
		case "Santiago_Trip_7":
			dialog.text = "Bátor fickó vagy... És humorérzékkel is. Kár lenne megölni téged. Gaston kedvelne téged. Bár... egyelôre maradj itt. Mennem kell, hogy ellenôrizzek valamit, és Miguel majd vigyáz rád, amíg távol vagyok.";
			link.l1 = "Esküszöm, 'barátom' - ezt még megbánod! ";
			link.l1.go = "Santiago_Trip_9";
		break;
		
		case "Santiago_Trip_8":
			dialog.text = "Ott megy az arrogancia... Amikor a dolgok rosszul állnak, a mi bátor kapitányunk józanságot mutat. Sokkal hamarabb is megtehetted volna, és idôt és bajt spóroltál volna nekünk. Nos, nekem most mennem kell, hogy ellenôrizzek valamit, de aztán visszajövök, és beszélgetünk, ha még szükség lesz rá, mármint. Egyelôre maradj itt. Miguel vigyáz rád, amíg távol vagyok.";
			link.l1 = "Esküszöm, 'barátom' - ezt még megbánod! ";
			link.l1.go = "Santiago_Trip_11";
		break;
		
		case "Santiago_Trip_9":
			dialog.text = "De természetesen. Maradj csendben, 'hero' - talán még minden rendben lesz.";
			link.l1 = "...";
			link.l1.go = "Santiago_Trip_11";
		break;
		
		case "Santiago_Trip_10":
			dialog.text = "Maradj itt, és reméld, hogy a rugalmasságod igazolja magát.";
			link.l1 = "...";
			link.l1.go = "Santiago_Trip_11";
		break;
		
		case "Santiago_Trip_11":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "1-44");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "Santiago_HouseSp2", "goto", "goto4", "", -1);
			pchar.quest.Santiago_Trip1.win_condition.l1 = "item";
			pchar.quest.Santiago_Trip1.win_condition.l1.item = "slave_01";
			pchar.quest.Santiago_Trip1.function = "SantiagoTrip_wait";
		break;
		
		case "Santiago_Trip_12":
			dialog.text = "Mi a fene?!";
			link.l1 = "Készülj a halálra, te gazember!";
			link.l1.go = "Santiago_Trip_13";
		break;
		
		case "Santiago_Trip_13":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "SantiagoTripExitFromRoom");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Santiago_Trip_14":
			dialog.text = "Micsoda zûrzavar! Kíváncsi voltam, mi ez a zaj. Gratulálok - okos fickó vagy!";
			link.l1 = "Okosabb, mint gondolnád... Lássuk, mit tudsz tenni egy fegyveres ellenféllel szemben!";
			link.l1.go = "Santiago_Trip_15";
		break;
		
		case "Santiago_Trip_15":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "SantiagoTripExitHouse");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		//офицер-посланник по 5 заданию
		case "HollQuest_Officer":
			dialog.text = "Mynheer Lucas Rodenburg azonnal látni akar. Azonnal gyere el hozzá.";
			link.l1 = "Máris megyek.";
			link.l1.go = "HollQuest_Officer_exit";			
		break;
		
		case "HollQuest_Officer_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
			pchar.questTemp.HWIC.Holl = "MerdokStart";
			AddQuestRecord("Holl_Gambit", "1-36");
		break;
		
//---------------------------------------------против всех----------------------------------------------
		//убрать испанского идальго
		case "Fernando":
			dialog.text = "Mit akarsz tôlem?";
			link.l1 = "A fejedet!";
			link.l1.go = "Fernando_fight";
			link.l2 = "Semmit, nem számít.";
			link.l2.go = "exit";	
			NextDiag.TempNode = "Fernando_repeat";
		break;
		
		case "Fernando_repeat":
			dialog.text = "Megint te vagy az? Mit akarsz tôlem?! Magyarázd meg magad!";
			link.l1 = "A fejedet!";
			link.l1.go = "Fernando_fight";
			link.l2 = "Semmit, nem számít.";
			link.l2.go = "exit";	
			NextDiag.TempNode = "Fernando_repeat";		
		break;
		
		case "Fernando_fight":
			chrDisableReloadToLocation = true;//выходы закроем
			LAi_SetWarriorType(npchar);
            LAi_group_MoveCharacter(npchar, "SPAIN_CITIZENS");
			LAi_group_Attack(NPChar, Pchar);
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
			pchar.quest.HWIC_Fernando.win_condition.l1 = "NPC_Death";
			pchar.quest.HWIC_Fernando.win_condition.l1.character = "HWICFernando";
			pchar.quest.HWIC_Fernando.function = "Fernando_died";
		break;
		
		//в доме Флитвуда
		case "Fleetwood_soldier"://для любителей сунуть нос куда не надо
			if (CheckAttribute(npchar, "quest.talked"))
			{
			dialog.text = "Már megint te vagy az? Miért szaglászol itt? Egyáltalán nem tetszik. Rendben, letartóztatlak és elküldelek a parancsnoki irodába vizsgálatra. Fiúk, fogjátok el ezt a fickót!";
			link.l1 = "De én csak azt akartam...";
			link.l1.go = "Fleetwood_soldier_4";	
			}
			else
			{
			dialog.text = "Ki maga és mit akar? Magyarázatot kérek!";
			link.l1 = "Sajnálom, uram, úgy tûnik, rossz házba jöttem. Elnézését kérem.";
			link.l1.go = "Fleetwood_soldier_1";	
			link.l2 = "Richard Fleetwoodot szeretném látni.";
			link.l2.go = "Fleetwood_soldier_2";		
			}
		break;
		
		case "Fleetwood_soldier_1":
			dialog.text = "Igen, így van. Rossz emberrel beszél. Legyen szíves azonnal távozni!";
			link.l1 = "Igen, persze.";
			link.l1.go = "Fleetwood_soldier_3";			
		break;
		
		case "Fleetwood_soldier_2":
			dialog.text = "Tényleg? Igen. Ki mondta, hogy itt lakik? Gyanúsnak tûnik... Rendben, letartóztatom és a parancsnoki irodába küldöm vizsgálatra. Fiúk, fogjátok el ezt a fickót!";
			link.l1 = "De én csak Richardot akartam látni...";
			link.l1.go = "Fleetwood_soldier_4";	
		break;
		
		case "Fleetwood_soldier_3":
			DialogExit();
			npchar.quest.talked = "true";
			DoQuestReloadToLocation("SentJons_town", "reload", "houseSP3", "");
			pchar.quest.Fleetwood_Soldier.win_condition.l1 = "location";
			pchar.quest.Fleetwood_Soldier.win_condition.l1.location = "SentJons_houseSP3";
			pchar.quest.Fleetwood_Soldier.function = "Fleetwood_Soldier";//для настырных
		break;
		
		case "Fleetwood_soldier_4":
			DialogExit();
			GoToPrison("SentJons", 1000, 10);			
		break;
		
		case "Theft_soldier":
			dialog.text = "Ah! Tolvajok? Kémek? Tartsd meg a kalapodat!";
			link.l1 = "Hup!";
			link.l1.go = "Attack_Theft_soldier";			
		break;
		
		case "Attack_Theft_soldier":
			LAi_group_Delete("EnemyFight");
			LAi_SetHP(npchar, 500, 500);
			LAi_SetWarriorType(npchar);
            LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Attack_soldier":
			dialog.text = "Ah! Mit keres itt ez a fickó? Fiúk, van itt egy kém! Fegyverbe!";
			link.l1 = "Hup!";
			link.l1.go = "Attack_soldier_fight";			
		break;
		
		case "Attack_soldier_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//снять запрет драки
			LAi_group_Delete("EnemyFight");
			for (i=1; i<=4; i++)
			{
			sld = characterFromId("Attack_sold_"+i);	
			LAi_SetWarriorType(sld);
            LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "PrepareToStreetFight");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		//Книппель-пленник в трюме
		case "Sailor_deck":
			chrDisableReloadToLocation = true;
			dialog.text = "Kapitány, kikérdeztük ezt a gazembert, ahogy mondta. Egy kicsit ki kellett égetnünk... Nála volt ez a levél. Megpróbálta megenni, de mi nem hagytuk. Ahogy gondoltuk, el akart vinni egy lányt Willemstadba, hogy elvigye a fônökéhez.";
			link.l1 = "Egy levél? Nézzük meg. Aztán majd én magam beszélek vele.";
			link.l1.go = "Sailor_deck_1";			
		break;
		
		case "Sailor_deck_1":
			DialogExit();
			AddLandQuestMark(characterFromId("KnippelClone"), "questmarkmain");
			GiveItem2Character(pchar, "NPC_Letter");
			AddQuestRecordInfo("LetterToAbi", "1");
		break;
		
		case "Sailor_deck_2":
			dialog.text = "Mik a parancsai, kapitány?";
			link.l1 = "Dobja ki a hullát a fedélzetre. És készüljenek a partra!";
			link.l1.go = "Sailor_deck_3";			
			// belamour legendary edition -->
			link.l2 = "Temessék el a tengerbe, teljes katonai tiszteletadással. Az öregember az utolsó pillanatig bátran harcolt. Még azt az ágyút is ô töltötte meg és célozta meg, miután kiütötték a kocsiból. Igazi kár. Egy másik világban bajtársak lehettünk volna...";
			link.l2.go = "Sailor_deck_3a";
		break;
		
		case "Sailor_deck_3a":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			dialog.text = "Igenis, kapitány!";
			link.l1 = "...";
			link.l1.go = "Sailor_deck_4";			
		break;
		
		case "Sailor_deck_3":
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "Sneak", 120);
			AddCharacterExpToSkill(pchar, "FencingL", 30);
			AddCharacterExpToSkill(pchar, "FencingS", 30);
			AddCharacterExpToSkill(pchar, "FencingH", 30);
			AddCharacterExpToSkill(pchar, "Pistol", 30);
			// <-- legendary edition
			dialog.text = "Igenis, kapitány!";
			link.l1 = "...";
			link.l1.go = "Sailor_deck_4";			
		break;
		
		case "Sailor_deck_4":
			DialogExit();
			chrDisableReloadToLocation = false;
			AddQuestRecord("Holl_Gambit", "3-21");
			LAi_SetActorType(pchar);
			sld = characterFromId("KnippelClone");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld.lifeday = 0;
			for (i=1; i<=3; i++)
			{
				sld = characterFromId("Sailor_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "ReturnMCPlayer", 3);
			}
			pchar.questTemp.HWIC.Self = "toVillemstad";
			sld = characterFromId("Solomon");
			sld.greeting = "solomon_2";
			AddLandQuestMark(sld, "questmarkmain");
			AddMapQuestMarkCity("Villemstad", false);
			LocatorReloadEnterDisable("Villemstad_town", "houseSP2", false);//откроем дом Аби
			LocatorReloadEnterDisable("Villemstad_houseSP2", "reload2", true);//закроем комнату Аби
		break;
		
		//Лонгвэй-пленник в трюме
		case "Sailor_deck_5":
			chrDisableReloadToLocation = true;
			dialog.text = "Elôkészítettük a kínaiakat a kihallgatásra, ahogy parancsolta, kapitány. Semmi sem volt nála, sem iratok. Készítettünk egy parazsat, és éppen most hevítjük a bilincseket és a fogókat.";
			link.l1 = "Szép munka, Alonso. De mielôtt elkezdenéd, megpróbálnék szót érteni vele. Talán úgy dönt, hogy önként együttmûködik?";
			link.l1.go = "Sailor_deck_6";			
		break;
		
		case "Sailor_deck_6":
			dialog.text = "Ahogy mondja, kapitány.";
			link.l1 = "...";
			link.l1.go = "exit";	
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
		break;
		
		case "Sailor_deck_7":
			dialog.text = "Igen, kapitány?";
			link.l1 = "Tegye bilincsbe, és tartsa szemmel, amíg Guadeloupe-ra nem érünk. Maguk hárman mindig legyenek itt. Az életükkel felelnek érte.";
			link.l1.go = "Sailor_deck_8";			
		break;
		
		case "Sailor_deck_8":
			dialog.text = "Igenis, kapitány!";
			link.l1 = "";
			link.l1.go = "Sailor_deck_9";			
		break;
		
		case "Sailor_deck_9":
			chrDisableReloadToLocation = false;
			AddQuestRecord("Holl_Gambit", "3-48");
			sld = characterFromId("LongwayClone");
			LAi_SetActorType(sld);
			LAi_SetGroundSitType(sld);
			DialogExit();
			pchar.quest.Longway_Shore.win_condition.l1 = "location";
			pchar.quest.Longway_Shore.win_condition.l1.location = "Shore31";
			pchar.quest.Longway_Shore.function = "LongwayInShore";
			AddMapQuestMarkShore("Shore31", true);
			if(bImCasual) NewGameTip("Felfedezô mód: az idôzítô nincs kikapcsolva. Tartsd be a határidôt!");
		break;
		
		//пьяница - передача письма Флитвуду
		case "Drunkard":
			DelLandQuestMark(npchar);
			dialog.text = "H-ic! Jó estét, uram! Mit szeretne? Talán meghívhatna egy öreg részegesnek egy italra? És én...";
			link.l1 = "Figyelj ide, vén részeges... Maga Jack Harrison?";
			link.l1.go = "Drunkard_1";			
		break;
		
		case "Drunkard_1":
			dialog.text = "Ó! Igen, én vagyok. Ki más lehetne? Ki más lehetne? Mit csináltunk egy drogos sza-lo-lo-o-rral...";
			link.l1 = "Ó, Uram, adj nekem türelmet! Milyen tengerész? Az arcodra van írva, hogy szárazföldi csavargó vagy... Pénzt akarsz keresni?";
			link.l1.go = "Drunkard_2";			
		break;
		
		case "Drunkard_2":
			dialog.text = "Mindig pénzt akarok keresni. Mit csináljak? De nem fogok senkit sem megölni. És nem is lopok semmit. És te nem vagy az esetem.";
			link.l1 = "Nem kell megölnie senkit, és kétlem, hogy valóban képes lenne rá. Túlságosan is ügyetlen vagy. Most pedig... Itt van egy levél. Vigye el, és vigye el a kormányzó rezidenciájától balra lévô házba. Richard Fleetwoodnak szól.";
			link.l1.go = "Drunkard_3";			
		break;
		
		case "Drunkard_3":
			dialog.text = "Richard Fleetwoodnak? Nem... azonnal letartóztatnak.";
			link.l1 = "Fogd be és figyelj. Senki sem fogja letartóztatni. Azt fogja mondani, hogy Charlie Knippeltôl jött Abigail miatt. Be fogják engedni. Ismételje meg, amit mondtam.";
			link.l1.go = "Drunkard_4";			
		break;
		
		case "Drunkard_4":
			dialog.text = "Ki az az Abigail? Ismerem Knippelt...";
			link.l1 = "Nem tartozik magára. Minél kevesebbet tudsz, annál tovább élsz. Nos, én várok. Ismétlem.";
			link.l1.go = "Drunkard_5";			
		break;
		
		case "Drunkard_5":
			dialog.text = "Charlie Knippeltôl jöttem az ur..... miatt. Abigail. Ez az. ";
			link.l1 = "Szép munka. Kap 5000 pezót a munkáért.";
			link.l1.go = "Drunkard_6";			
		break;
		
		case "Drunkard_6":
			if (makeint(Pchar.money) >= 5000)
			{
				dialog.text = "5000 pezót? Oh.... Csak egy levél kézbesítéséért?";
				link.l1 = "Nem. Kap egy másik levelet. Eljössz vele a kocsmába, és itt foglalsz helyet. Majd én átveszem tôled. Ne csinálj semmi ostobaságot, és ne félj - figyelni foglak, és a közeledben maradok. Fogadd el ezt az összeget elôlegnek, hogy könnyebben érezd magad.";
				link.l1.go = "Drunkard_7";	
			}
			else
			{
				dialog.text = "Ötezer? Van egyáltalán ennyi pénzed?";
				link.l1 = "Ha! Persze, hogy van. Máris hozom.";
				link.l1.go = "Drunkard_no_money";	
				NextDiag.CurrentNode = "Drunkard_no_money";
			}
		break;
		
		case "Drunkard_no_money":
			dialog.text = "Elhoztad az ötezret?";
			if (makeint(Pchar.money) >= 5000)
			{
				link.l1 = "Igen. Tessék. Ne aggódj, ne aggódj.";
				link.l1.go = "Drunkard_7";
			}
			else
			{
				link.l1 = "Ne. Várj. Hamarosan visszajövök.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Drunkard_no_money";
			}
		break;
		
		case "Drunkard_7":
			AddMoneyToCharacter(pchar, -5000);
			RemoveItems(PChar, "MC_Letter", 1);
			dialog.text = "Hmm... Most már mehetek, uram?";
			link.l1 = "Nem, csütörtök reggel... Persze, most rögtön, te tökfej! Most pedig igya meg a rumot és menjen!";
			link.l1.go = "Drunkard_8";			
		break;
		
		case "Drunkard_8":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-26");
			LAi_SetStayType(npchar);
			LAi_RemoveLoginTime(npchar);//удалить время загрузки
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, "sentjons_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "sentjons_town", "reload", "reload4_back", "DrunkardGoTown", -1);
			chrDisableReloadToLocation = true;//закрыть локацию
			LocatorReloadEnterDisable("SentJons_town", "reload1_back", true);
			LocatorReloadEnterDisable("SentJons_town", "reload2_back", true);
			LocatorReloadEnterDisable("SentJons_town", "gate_back", true);//чтобы не сбежал
		break;
		
		case "Drunkard_9":
			DelLandQuestMark(npchar);
			dialog.text = "Á, itt van, uram... Jobb lett volna, ha ezt nem teszem. Richárd dühös lett, amikor befejezte az olvasást. Azt hittem, meg fog ölni.";
			link.l1 = "De hát itt vagy! Ne aggódj - ezt nem merte volna megtenni -, te nagyon értékes voltál számára abban a pillanatban, ha-ha! El sem tudod képzelni, mennyire...";
			link.l1.go = "Drunkard_10";			
		break;
		
		case "Drunkard_10":
			dialog.text = "Innom kell egy italt... Itt a válasza neked.";
			link.l1 = "Add ide nekem! És tartsd a szádat!";
			link.l1.go = "Drunkard_11";			
		break;
		
		case "Drunkard_11":
			GiveItem2Character(pchar, "MC_Letter");
			ChangeItemDescribe("MC_Letter", "itmdescr_MC_Letter1");
			AddQuestRecordInfo("FleetwoodAnswer", "1");
			dialog.text = "Nehéz lesz beszélnem a következô napokban... Viszontlátásra... Azt kívánom, hogy soha többé ne lássalak.";
			link.l1 = "Nyugalom, vén részeges, ha-ha-ha-ha! Mi-mi-mit tegyünk egy részeges sza-lorral... Igyál és pihenj - most már mindennek vége!";
			link.l1.go = "Drunkard_12";			
		break;
		
		case "Drunkard_12":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Holl_Gambit", "3-27");
			pchar.questTemp.HWIC.Self = "FleetwoodAgree";
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
		break;
		
		//кэп курьерского судна
		case "Cureer_abordage":
			dialog.text = "Mi a fenéért támadtátok meg a hajómat? Nincs nálam sem értéktárgy, sem pénz - csak papírok, amik amúgy sem használnak nektek!";
			link.l1 = "Fogd be. Vesztettél, úgyhogy most már hallgatni fogsz rám. Nincs szükségem sem a hajójára, sem a papírjaira. Azt akarom, hogy adja át ezt az üzenetet a fônökének, annak a mocskos patkánynak, Lucas Rodenburgnak. Mondja meg neki, hogy Fleetwood kapitány üdvözletét küldi.";
			link.l1.go = "Cureer_abordage_1";			
		break;
		
		case "Cureer_abordage_1":
			dialog.text = "Fleetwood kapitány? De...";
			link.l1 = "Átadja ezt a levelet a fônökének, vagy inkább én adjam át? Kereshetek egy másik jelöltet is a kézbesítésre. Én minden hétvégén unalomûzésbôl kirabolom a maga mocskos Társaságának hajóit, csak hogy tudja.";
			link.l1.go = "Cureer_abordage_2";			
		break;
		
		case "Cureer_abordage_2":
			dialog.text = "Rendben, Sir Fleetwood. Átadom.";
			link.l1 = "Remek. Most már elbúcsúzhatunk egymástól, Mynheer. Ma nagyon szerencsésnek mondhatja magát. És ne felejtsen el meglátogatni egy templomot, ha megérkezik!";
			link.l1.go = "Cureer_abordage_3";			
		break;
		
		case "Cureer_abordage_3":
			DialogExit();
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			Lai_SetPlayerType(pchar);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetImmortal(sld, true);
			sld.ShipEnemyDisable  = true;
			pchar.quest.HWICCureer_AfterBattle.over = "yes";
			pchar.quest.HWICCureerOnMapOver.over = "yes";
			AddQuestRecord("Holl_Gambit", "3-39");
			Log_TestInfo("THE LETTER HAS BEEN DELIVERED!");
			RemoveItems(PChar, "MC_Letter", 1);
			pchar.questTemp.HWIC.Self = "LetterToLucasSent";
			pchar.quest.Curacao_exploring.win_condition.l1 = "location";
			pchar.quest.Curacao_exploring.win_condition.l1.location = "Curacao";
			pchar.quest.Curacao_exploring.function = "CuracaoExploring";
			DoQuestCheckDelay("LAi_ReloadBoarding", 1.0);
			AddComplexSeaExpToScill(50, 50, 50, 100, 50, 50, 0);
			AddComplexSelfExpToScill(30, 30, 30, 30);
			AddMapQuestMarkIsland("Curacao", true);
		break;
		
		//Матиас Бек в тюрьме
		case "MatiasBek"://на случай если геймер захочет пообщаться
			dialog.text = "Törvénytelenül tartóztattak le! Nincs kapcsolatom az angolokkal! Ezek mind Rodenburg cselszövései. Ne is törôdj vele. Peter Stuyvesant hamarosan megérkezik - ô majd mindent elrendez!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "MatiasBek";
		break;
		
		//стражник у входа в резиденцию
		case "QuestGuard":
			dialog.text = "Mynheer Lucas Rodenburg most nem akar senkit sem látni. Legyen szíves azonnal elhagyni a rezidenciát.";
			link.l1 = "Hm. Értem. Egy hét múlva megpróbálok beugrani...";
			link.l1.go = "exit";
			NextDiag.TempNode = "QuestGuard";		
		break;
		
		//Питер Стайвесант
		case "Stivesant":
			dialog.text = "A rezidenciára megyünk, kapitány. Már elküldtem az embereimet az erôdbe, hogy információkat szerezzek Matthias Beckrôl. Ha jelenleg valóban börtönben van, akkor már biztosan kiengedték, és elkísérték a városba. Kövessenek!";
			link.l1 = "Igen, Mynheer Stuyvesant.";
			link.l1.go = "Stivesant_1";			
		break;
		
		case "Stivesant_1":
			DialogExit();
			AddLandQuestMark(npchar, "questmarkmain");
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "Villemstad_townhall", "goto", "goto2", "OpenVillemstadResidence", -1);
		break;
		
		case "ArestLucas_1":
			dialog.text = "Lucas! Mi folyik itt? Hol van Matthias Beck? Igaz, hogy börtönbe küldted?";
			link.l1 = "";
			link.l1.go = "ArestLucas_2";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
		break;
		
		case "ArestLucas_2":
			StartInstantDialog("Lucas", "ArestLucas_3", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_3":
			dialog.text = "Helló, Mynheer Stuyvesant. Bizonyítékom van arra, hogy kapcsolatban áll a brit hírszerzéssel és közvetlenül Fleetwood kapitánnyal. Ô adta a tippet az átkozott briteknek, hogy támadják meg a futár brigantinkat, hogy megszerezzék a Társaság bizalmas levelezését.";
			link.l1 = "";
			link.l1.go = "ArestLucas_4";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));
			LAi_ActorAnimation(npchar, "dialog_stay13", "1", 4.5);
		break;
		
		case "ArestLucas_4":
			StartInstantDialog("Stivesant", "ArestLucas_5", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_5":
			dialog.text = "Honnan szerezte ezt az információt?";
			link.l1 = "";
			link.l1.go = "ArestLucas_6";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
		break;
		
		case "ArestLucas_6":
			StartInstantDialog("Lucas", "ArestLucas_7", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_7":
			dialog.text = "Ezt a futárbrigantin kapitánya állította. Richard Fleetwood felszállt a hajójára, és elvette az iratait; ezután a hajót szabadon engedték. Rajtam, rajtad és Matthias Beck-en kívül senkinek sem volt információja sem az útvonalról, sem a menetrendrôl.";
			link.l1 = "";
			link.l1.go = "ArestLucas_8";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));
		break;
		
		case "ArestLucas_8":
			StartInstantDialog("Stivesant", "ArestLucas_9", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_9":
			dialog.text = "És ezért döntött úgy, hogy Beck adta a tippet Fleetwoodnak, hogy támadja meg a brigantint? Micsoda ostobaság! Fleetwood egy közönséges kalóz; csak kereskedelmi hajókat támad meg. Miért lett volna szüksége a papírokra, amelyek egyébként csak könyvelési információkat tartalmaztak?";
			link.l1 = "";
			link.l1.go = "ArestLucas_10";		
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
		break;
		
		case "ArestLucas_10":
			StartInstantDialog("Lucas", "ArestLucas_11", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_11":
			dialog.text = "Mynheer, a futár más fontos társasági dokumentumokat is szállított - nem csak a szokásos jelentéseket. És most ezek mind a britek kezében vannak. Ezért döntöttem úgy, hogy letartóztatom Becket.";
			link.l1 = "";
			link.l1.go = "ArestLucas_12";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));			
		break;
		
		case "ArestLucas_12":
			StartInstantDialog("Stivesant", "ArestLucas_13", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_13":
			dialog.text = "A fenébe! Ez egy igazi hatalomátvétel! Felfogtad egyáltalán, hogy mit tettél, Lucas? Hol van a futárbrigantin kapitánya?";
			link.l1 = "";
			link.l1.go = "ArestLucas_14";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
			LAi_ActorAnimation(npchar, "dialog_stay13", "1", 4.5);
		break;
		
		case "ArestLucas_14":
			StartInstantDialog("Lucas", "ArestLucas_15", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_15":
			dialog.text = "Philipsburgba ment, Mynheer.";
			link.l1 = "";
			link.l1.go = "ArestLucas_16";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));	
		break;
		
		case "ArestLucas_16":
			StartInstantDialog("Stivesant", "ArestLucas_17", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_17":
			dialog.text = "Rendben, akkor. Parancsot adtam Beck szabadon bocsátására. Ide fogják hozni, és aztán hárman elbeszélgetünk.";
			link.l1 = "";
			link.l1.go = "ArestLucas_18";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
		break;
		
		case "ArestLucas_18":
			StartInstantDialog("Lucas", "ArestLucas_19", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_19":
			dialog.text = "Rendben, nem bánom. Hárman - rendben. Beszéljünk.";
			link.l1 = "";
			link.l1.go = "ArestLucas_20";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));	
		break;
		
		case "ArestLucas_20":
			DialogExit();
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			ChangeCharacterAddressGroup(sld, "Villemstad_townhall", "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "governor1", "DoubleTalkWithLucas", -1.0);
			locCameraFromToPos(4.70, 2.92, -4.19, false, 3.60, -0.70, 5.00);
			DoQuestCheckDelay("PiterTalkWithLucas_2", 4.5);
		break;
		
		case "ArestLucas_40":
			dialog.text = "Megfizetsz a törvénytelenségedért, Rodenburg! A vádjai abszurdak. Még a brigantin kapitányát sem engedte látni! Nem hoztál elô semmilyen bizonyítékot, minden vád személyesen tôled származik.\nAz Úrra esküszöm, ártatlan vagyok! Nincs és nem is volt semmilyen kapcsolatom a britekkel!";
			link.l1 = "";
			link.l1.go = "ArestLucas_41";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
		break;
		
		case "ArestLucas_41":
			StartInstantDialog("Lucas", "ArestLucas_42", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_42":
			dialog.text = "Ó, tényleg? Akkor honnan tudott Fleetwood a mi brigantinkról, és hogy nem csak a szokásos iratok voltak a fedélzeten?";
			link.l1 = "";
			link.l1.go = "ArestLucas_43";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Villemstad_Mayor"));
		break;
		
		case "ArestLucas_43":
			dialog.text = "...";
			link.l1 = "Rodenburg hazudik. Richard Fleetwood nem támadhatta meg a futárbrigantint.";
			link.l1.go = "ArestLucas_44";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
			sld = characterFromId("Stivesant");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			sld = characterFromId("Villemstad_Mayor");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
		break;
		
		case "ArestLucas_44":
			dialog.text = "És ki vagy te, Mynheer? Milyen alapon tesz ilyen kijelentéseket?";
			link.l1 = "A nevem " + GetFullName(pchar) + ". Én személyesen likvidáltam Fleetwood kapitányt, csapdába csalva ôt. A holttestét a sirályok eszik a török partokon. A tisztviselôk nem tudtak megvédeni minket, holland kereskedôket az agressziójától, ezért magam végeztem vele. És ez még azelôtt történt, hogy a futár brigantint kifosztották volna...";
			link.l1.go = "ArestLucas_46";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "ArestLucas_46":
			dialog.text = "";
			link.l1 = "Fleetwood egyszerûen nem tehette volna meg, ô már halott volt. A helyiektôl a kocsmában megtudtam, hogy Mathias Becket letartóztatták, ezért úgy döntöttem, hogy utánajárok az ügynek, mert mindig is úgy hittem, hogy mynheer Beck kristályhírû ember...";
			link.l1.go = "ArestLucas_47";			
		break;
		
		case "ArestLucas_47":
			dialog.text = "";
			link.l1 = "A kikötôben azt mondták nekem, hogy a xebecet mindenféle bûnözôkkel és zsoldosokkal rakodtad meg, a Társaság gárdistái a parton maradtak. Követtem a hajódat és elfoglaltam, megöltem minden gyilkos gyilkost, akit felbéreltél. Kihallgattam Longway kapitányt, a szabadságáért cserébe mindent elmondott, Mynheer Rodenburg...";
			link.l1.go = "ArestLucas_48";			
		break;
		
		case "ArestLucas_48":
			dialog.text = "";
			link.l1 = "Azt tervezted, hogy átveszed a hatalmat Curacao felett, és utasítottad Longwayt, hogy süllyessze el a mynheer Stuyvesant gályát. Ismerve az ön módszereit, biztos vagyok benne, hogy a brigantin szegény kapitánya meghalt. Bizonyára azért szervezte meg a futárhajó elleni támadást, hogy precedenst teremtsen, igazam van? És ezt az akciót az ön bérgyilkosa, Jacob van Berg hajtotta végre? Longway sokat mesélt nekem errôl az emberrôl.";
			link.l1.go = "ArestLucas_49";			
		break;
		
		case "ArestLucas_49":
			dialog.text = "Ez... ez egy szemenszedett hazugság! Mirôl beszélsz, Mynheer? Ki a fene maga?";
			link.l1 = "Én egy független kapitány vagyok, aki meg akarta tisztítani a tengert és a szárazföldet attól a gazember Fleetwoodtól, és aki belekeveredett az önök politikai intrikáiba! Én figyelmeztettem mynheer Stuyvesantot, hogy milyen veszélyben van. És azért vagyok itt, hogy Curacaón véget vessenek az önök fosztogatásainak - a törvényes hatóságokkal együtt!";
			link.l1.go = "ArestLucas_50";			
		break;
		
		case "ArestLucas_50":
			dialog.text = "Micsoda szemtelenség! Felelni fogsz a szavaidért, Mynheer 'független kapitány'! Te...";
			link.l1 = "";
			link.l1.go = "ArestLucas_51";
		break;
		
		case "ArestLucas_51":
			StartInstantDialog("Stivesant", "ArestLucas_52", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_52":
			dialog.text = "Elég, Lucas. Megfizetsz a bûneidért! Eleget hallottam és láttam. Lucas Rodenburg, letartóztatom a Társaság igazgatója elleni merénylet, erôszakos hatalomátvételi kísérlet és a futárhajó kapitánya meggyilkolásának gyanúja miatt.\nMellett biztos vagyok benne, hogy a hivatalos nyomozás során többet fogunk megtudni az életrajzod érdekes részeirôl. Önt ôrizetbe veszik, és Amszterdamba szállítják, ahol bíróság elé állítják. Vigyék el!";
			link.l1 = "";
			link.l1.go = "ArestLucas_53";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
			sld = characterFromId("Lucas");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromID("Stivesant"));					
		break;
		
		case "ArestLucas_53":
			StartInstantDialog("Lucas", "ArestLucas_54", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_54":
			dialog.text = "De...";
			link.l1 = "";
			link.l1.go = "ArestLucas_55";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));			
		break;
		
		case "ArestLucas_55":
			DialogExit();
			LAi_ActorTurnToCharacter(pchar, characterFromID("Lucas"));
			sld = characterFromId("Lucas");
			LAi_SetImmortal(sld, true);//защита от хитреца
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Villemstad_townhall", "goto", "goto6");
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "LucasGoToPrison", -1);
			for (i=3; i<=5; i++)
			{
			sld = characterFromId("StivesantGuard_"+i);
			LAi_ActorFollow(sld, characterFromID("Lucas"), "", -1);
			}
			LAi_SetActorType(PChar);
			locCameraFromToPos(4.70, 2.92, -4.19, false, -4.60, -1.70, 5.50);
			DoQuestFunctionDelay("SecondDayInVillemstad", 6.0);
		break;
		
		case "Stivesant_10":
			dialog.text = "Kapitány " + GetFullName(pchar) + "! A willemstadi gyarmati adminisztráció nevében kérem, hogy fogadja ôszinte köszönetünket az Ön tetteiért, amelyek segítettek nekünk letartóztatni ezt a veszélyes bûnözôt. Szeretném személyesen is megköszönni, mivel valószínûleg az életemmel tartozom Önnek.";
			link.l1 = "Az összes holland gyarmat érdekében cselekedtem, Mynheer.";
			link.l1.go = "Stivesant_11";			
		break;
		
		case "Stivesant_11":
			dialog.text = "A szerénysége tiszteletet parancsol, barátom. Most néhány formaságot szeretnék elintézni: mivel a Meifenget csak jó céllal és szorult helyzetben foglaltad el, nem lehetnek követeléseid. De ez a hajó a Társaság tulajdona, és kérem, hogy adja vissza.";
			link.l1 = "Természetesen, Mynheer.";
			link.l1.go = "Stivesant_12";			
		break;
		
		case "Stivesant_12":
		//удаляем Мейфенг
		DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//удаляем атрибут квестового корабля
		if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_MAYFANG)
		{
			pchar.Ship.Type = GenerateShipExt(SHIP_TARTANE, true, pchar);
			pchar.Ship.name = "A boat";
			SetBaseShipData(pchar);
			SetCrewQuantityOverMax(PChar, 0);//сажаем на тартану
		}
		else
		{
			for(i = 1; i < COMPANION_MAX; i++)
			{
			int iTemp = GetCompanionIndex(PChar, i);
			if(iTemp > 0)
				{
				sld = GetCharacter(iTemp);
				if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
					{
						pchar.questTemp.HWIC.Self.CompanionIndex = sld.Index;
						sld = GetCharacter(sti(pchar.questTemp.HWIC.Self.CompanionIndex));
						RemoveCharacterCompanion(PChar, sld);
						AddPassenger(PChar, sld, false);
					}
				}
			}
		}
			dialog.text = "Kérem, jöjjön el holnap a rezidenciámra - a Szabad Tartományok Köztársaságának érdekében tett tetteiért a Szabad Tartományok Köztársasága nevében kitüntetést fog kapni. Arra kérlek, hogy ne hagyd el a várost.";
			link.l1 = "Rendben, Mynheer. Holnap beugrom.";
			link.l1.go = "Stivesant_13";			
		break;
		
		case "Stivesant_13":
			DialogExit();
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			sld.dialog.currentnode = "Bek_2";
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "Bek_2":
			dialog.text = "Személyesen is szeretném megköszönni, kapitány úr, a vállalkozó szellemét és a kellô idôben nyújtott segítségét. Ne felejtsen el holnap idejönni, értékes ajándékot készítek Önnek.";
			link.l1 = "Köszönöm, Mynheer Beck. Ott leszek!";
			link.l1.go = "Bek_3";			
		break;
		
		case "Bek_3":
			DialogExit();
			pchar.quest.Award_FromPiter.win_condition.l1 = "Timer";
			pchar.quest.Award_FromPiter.win_condition.l1.date.hour  = 9.0;
			pchar.quest.Award_FromPiter.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Award_FromPiter.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Award_FromPiter.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Award_FromPiter.function = "OpenResidenceDoor";
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Villemstad_town", "reload5_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload10_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload3_back", true);//закрыть вход в резиденцию
			LocatorReloadEnterDisable("Villemstad_town", "reloadR2", true);//закрыть боковой вход в резиденцию
			AddQuestRecord("Holl_Gambit", "3-53");
			DoQuestReloadToLocation("Villemstad_prison", "goto", "goto23", "TalkWithLucasPrisoner");
			for (i=4; i<=5; i++)
			{
				sld = characterFromId("StivesantGuard_"+i);
				sld.lifeday = 0;//подчистим солдат
			}
		break;
		
		case "Stivesant_14":
			dialog.text = "" + GetFullName(pchar) + ", a Szabad Tartományok Köztársasága nevében ezennel egy személyes fegyvert és 100 000 pezó összegû pénzt kap a holland nép ellenségének, az államellenes bûnözô Richard Fleetwoodnak a likvidálásában tett kezdeményezéséért. Gratulálok!";
			link.l1 = "Köszönöm, Mynheer Styuvesant!";
			link.l1.go = "Stivesant_15";			
		break;
		
		case "Stivesant_15":
			dialog.text = "Továbbá, a példátlan bátorságért, a vállalaton belüli áruló összeesküvés leleplezéséért és a vállalat volt alelnökének elfogására irányuló kockázatos mûveletért 150 000 pezó jutalomban részesül. Emellett engedélyt kap arra is, hogy szerzôdéseket kössön a Holland Nyugat-indiai Társasággal\nBizonyos vagyok benne, hogy az új igazgatóhelyettesünk talál majd jól fizetô állást egy ilyen bátor kapitánynak, mint ön.";
			link.l1 = "Köszönöm! Ezt észben fogom tartani.";
			link.l1.go = "Stivesant_16";			
		break;
		
		case "Stivesant_16":
			AddMoneyToCharacter(pchar, 250000);
			GiveItem2Character(pchar, GetGeneratedItem("blade_16")); // belamour legendary edition используем GetGeneratedItem иначе пачка одинаковых клинков из первой части массива
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			dialog.text = "Legyen tisztában azzal, hogy mindig számíthat a segítségemre bármilyen ügyletben, amíg Hollandia oldalán és érdekében cselekszik. Most pedig halljuk, mit mond Willemstad kormányzója, Matthias Beck.";
			link.l1 = "";
			link.l1.go = "Stivesant_17";			
		break;
		
		case "Stivesant_17":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			LAi_SetActorType(sld);
			sld.dialog.currentnode = "Bek_4";
			LAi_ActorDialog(sld, pchar, "", -1, 0);		
		break;
		
		case "Bek_4":
			dialog.text = "Ôszinte hálámat fejezem ki, kapitány úr, a bátorságáért és éleslátásáért, amellyel felfedezte az állam elleni összeesküvést. Szeretném átadni önnek ezt az értékes navigációs mûszert, amely minden hadihajós ember számára felbecsülhetetlen értékû.";
			link.l1 = "Köszönöm, Mynheer Beck";
			link.l1.go = "Bek_5";			
		break;
		
		case "Bek_5":
			GiveItem2Character(pchar, "bussol");
			dialog.text = "Szeretném, ha tudná: Ön most már a barátom, és ez sokat jelent. Mindig szívesen látott vendég leszel nálam. Gyere bármikor és bármilyen okból - szívesen nyújtok neked bármilyen segítséget, amire szükséged lehet.";
			link.l1 = "Ezt örömmel hallom, Mynheer!";
			link.l1.go = "Bek_6";			
		break;
		
		case "Bek_6"://наведем порядок в городе
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-54");
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			LAi_SetHuberStayType(sld);
			sld.Dialog.Filename = "Common_Mayor.c";//patch-8
			sld.dialog.currentnode = "First time";
			sld.quest.meeting = "1";
			for (i=1; i<=3; i++)
			{
				sld = characterFromId("StivesantGuard_"+i);
				sld.lifeday = 0;//подчистим солдат
			}
			sld = characterFromId("Stivesant");
			LAi_ActorGoToLocator(sld, "goto", "goto6", "StivesantSitDown", -1);
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Villemstad_town", "reload1_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload2_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "gate_back", false);
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			DelMapQuestMarkCity("Villemstad");
		break;
		
		case "Bek_7":
			dialog.text = "Hollandia büszke Önre, Mynheer. Az önhöz hasonló kapitányok alkotják a holland flotta gerincét a Karib-tengeren. Tessék, kérem, fogadják el a jutalmukat.";
			link.l1 = "Köszönöm, Mynheer. Megtiszteltetés Hollandiát szolgálni!";
			link.l1.go = "Bek_8";
		break;
		
		case "Bek_8":
			TakeNItems(pchar, "gold_dublon", 1000);
			ChangeCharacterComplexReputation(pchar,"authority", 5);
			ChangeCharacterNationReputation(pchar, HOLLAND, 20);
			DialogExit();
			sld = characterFromId("Lucas");
			LAi_SetActorType(sld);
			sld.dialog.currentnode = "LucasAward_2";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Stivesant_18":
			dialog.text = "Örülök, hogy látlak. Hogy van?";
			link.l1 = "Jól. Csak beugrottam meglátogatni.";
			link.l1.go = "exit";	
			NextDiag.TempNode = "Stivesant_18";
		break;
		
		// Jason НСО
		case "Stivesant_19":
			if (ChangeCharacterHunterScore(pchar, "holhunter", 0) > 10)
			{
				dialog.text = "Nézd csak, ki van itt! A " + GetFullName(pchar) + ". Nemrég küldtük el fejvadászainkat, akiknek ide kellett hozniuk téged. És ez a szolgáltatás sokba került.";
				link.l1 = "Uhm... mennem kell...";
				link.l1.go = "arest";
				break;
			}
			// belamour legendary edition фикс проверки мундира с мушкетом
			if (pchar.questTemp.Patria == "epizode_4" && IsUniformEquip())
			{
				dialog.text = "Ön a francia haditengerészet kapitánya? Jó, kevés az idôm, de meghallgatom, amit mondani akar. Mi szél hozta ide?";
				link.l1 = "Mynheer Stuyvesant, Szent Kristófról jöttem a francia gyarmatok fôkormányzójának, Chevalier de Poincy-nak az üzenetével.";
				link.l1.go = "Stivesant_20";
			}
			else
			{
				dialog.text = "Elnézést, kapitány, de most nagyon elfoglalt vagyok, és nem tudok elég idôt szánni önre. Beszéljen Mathias Beck mynheerrel, hadd hallja, mit akar mondani.";
				link.l1 = "Hmm...";
				link.l1.go = "Stivesant_19_1";
			}
		break;
		
		case "Stivesant_19_1":
			DialogExit();
			npchar.dialog.currentnode = "Stivesant_19";
		break;
		
		case "Stivesant_20":
			sld = characterFromId("Patria_FlautCap");
			dialog.text = "Chevalier de Poincy-tól? Határozottan nem számítottam rá, hogy ilyen kevés idôbe telik... khm... hogy van Chevalier?";
			link.l1 = "Minden rendben van, Mynheer. Monsieur de Poincy utasított, hogy adjam át ezt a levelet önnek. A másik feladatom az volt, hogy kísérjem '"+sld.ship.name+"' rakománnyal az ön társasága számára Willemstad kikötôjébe. A hajó a dokkban van, és a rakomány nem sérült meg.";
			link.l1.go = "Stivesant_21";
		break;
		
		case "Stivesant_21":
			dialog.text = "Egy flotta a cégünk rakományával? Érdekes... És a levél, kapitány?";
			link.l1 = "Itt van. Kérem, vegye el.";
			link.l1.go = "Stivesant_22";
		break;
		
		case "Stivesant_22":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "Hmmm... (olvasás). Egy ellenôrzés az anyaállamból... Ahem... Huh, nos... ez érdekes, he-he-he... Egyébként, kapitány, úgy hallottam, hogy Franciaország háborúban áll Spanyolországgal a Karib-tengeren? A San Jose erôd ostroma és kifosztása, a spanyol hadihajó megsemmisítése Kuba keleti partjainál...";
			link.l1 = "Hispaniola nyugati partjainál, Kikötô-au-Prince-nél, Mynheer. San Jose ostromának egyetlen célja pedig az volt, hogy a spanyoloktól anyagi kártérítést kapjanak a Saint-Pierre elleni támadásért. Már jó ideje rossz viszonyban vagyunk Spanyolországgal... Mikor térjek vissza a válaszért?";
			link.l1.go = "Stivesant_23";
		break;
		
		case "Stivesant_23":
			dialog.text = "Nem tartom fel, kapitány úr, ön katona, valószínûleg sok ügye van, és biztos vagyok benne, hogy Chevalier már alig várja a visszatérését. Legyen olyan kedves, és várjon itt, a nappaliban két órát, amíg összeállítom a választ arra a levélre. Foglaljon helyet és pihenjen itt, ha kívánja, bort vagy rumot szolgálunk fel önnek...";
			link.l1 = "Köszönöm, Mynheer, én inkább egy pohár finom bort szeretnék...";
			link.l1.go = "Stivesant_24";
		break;
		
		case "Stivesant_24":
			chrDisableReloadToLocation = true;//закрыть локацию
			pchar.quest.Patria_CureerTimeOver.over = "yes"; //снять таймер
			pchar.quest.Patria_CureerFail.over = "yes"; //снять прерывание
			sld = characterFromId("Patria_FlautCap");
			RemoveCharacterCompanion(pchar, sld);
			sld.lifeday = 0;
			DialogExit();
			npchar.dialog.currentnode = "Stivesant_25";
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, "Villemstad_townhall", "goto", "goto6");
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "Patria_StivesantWait", -1);
			pchar.questTemp.Patria = "epizode_4_return";
		break;
		
		case "Stivesant_25":
			GiveItem2Character(pchar, "Reserve_item_01");
			ChangeItemDescribe("Reserve_item_01", "itmdescr_Reserve_item_01_2");
			dialog.text = "A válasz Monsieur de Poincy úrnak készen áll. Tessék, kérem, vegye el... Sok szerencsét, kapitány.";
			link.l1 = "Köszönöm, Mynheer. Viszontlátásra!";
			link.l1.go = "Stivesant_26";
		break;
		
		case "Stivesant_26":
			DialogExit();
			npchar.dialog.currentnode = "Stivesant_19";
			chrDisableReloadToLocation = false;
			AddQuestRecord("Patria", "23");
			SetFunctionTimerCondition("Patria_CureerBackOver", 0, 0, 31, false);
		break;
		
		case "Stivesant_27":
			if (ChangeCharacterHunterScore(pchar, "holhunter", 0) > 10)
			{
				dialog.text = "Nézd csak, ki van itt! A " + GetFullName(pchar) + ". Nemrég küldtük el fejvadászainkat, akiknek ide kellett hozniuk téged. És ez a szolgáltatás sokba került.";
				link.l1 = "Uhm... mennem kell...";
				link.l1.go = "arest";
				break;
			}
			if (pchar.questTemp.Patria == "epizode_6" && IsUniformEquip())
			{
				dialog.text = "Megint jött egy üzenettel Philippe de Poincy fôkormányzótól, ugye?";
				link.l1 = "Igen, Mynheer Stuyvesant. Sint Maarten partjainál történt egy kellemetlen félreértés - a párizsi felügyelôt, Noel Forget bárót szállító hajót lelôtték a Philipsburgi erôdnél, és...";
				link.l1.go = "Stivesant_28";
			}
			else
			{
				dialog.text = "Elnézést, kapitány, de most nagyon elfoglalt vagyok, és nem tudok elég idôt szánni önre. Beszéljen Mathias Beck mynheerrel, hadd hallja, mit akar mondani.";
				link.l1 = "Hmm...";
				link.l1.go = "Stivesant_27_1";
			}
		break;
		
		case "Stivesant_27_1":
			DialogExit();
			npchar.dialog.currentnode = "Stivesant_27";
		break;
		
		case "Stivesant_28":
			if (pchar.questTemp.HWIC.Detector == "holl_win" || pchar.questTemp.HWIC.Detector == "self_win")
			{
				dialog.text = "És ezért van itt, kapitány úr. Nem fogok diplomáciai vitákba bocsátkozni: mondja meg Chevalier-nek, hogy már nem ô a felelôs Sint Maartenért. Elég volt belôle. Ami pedig az anyaállam ellenôrzését illeti - hadd találjon ki valamit, de Poincy-nak sosem esett nehezére mindent a feje tetejére állítani.";
				link.l1 = "Pontosan ezt kellene mondanom neki?";
				link.l1.go = "Stivesant_29";
			}
			else
			{
				dialog.text = "És ezért van itt, kapitány. Nem fogok diplomáciai vitákba bocsátkozni: az urad az utóbbi idôben túlságosan mohó volt Sint Maartenen, úgyhogy itt az ideje, hogy csillapítsd csillapíthatatlan éhségét. És azt hiszem, ezt ô is tökéletesen megérti. Önnek, Charles de Maure kapitány, szintén vannak kérdéseink a Richard Fleetwood nevû brit banditával kapcsolatos közelmúltbeli eseményekkel kapcsolatban, úgyhogy egy ideig itt kell maradnia.\nSergeant! Vegye el a kapitány fegyvereit, és vigye a parancsnoki irodába!";
				link.l1 = "Egy szolgálatban lévô francia tisztet késleltetni elfogadhatatlan!";
				link.l1.go = "Stivesant_31";
			}
		break;
		
		case "Stivesant_29":
			dialog.text = "Magam sem tudnám jobban megfogalmazni, kapitány. A parancsnoka mindent meg fog érteni, de nem kell ebbe belemerülnie, az nem változtat semmin. Minden jót kívánok. Ôrmester, vezesse Charles de Maure urat a kijárathoz!";
			link.l1 = "...";
			link.l1.go = "Stivesant_30";
		break;
		
		case "Stivesant_30":
			DialogExit();
			DoQuestReloadToLocation("Villemstad_town", "reload", "reload3", "Patria_DiplomatGetOut");
		break;
		
		case "Stivesant_31":
			dialog.text = "Sajnos én más véleményen vagyok. Ôrmester! Ellenállás esetén alkalmazzon erôszakot!";
			link.l1 = "Még nem tudja, kivel van dolga, Mynheer...";
			link.l1.go = "Stivesant_32";
		break;
		
		case "Stivesant_32":
			DialogExit();
			Patria_DiplomatFight();
		break;
		
		case "Stivesant_33":
			dialog.text = "Kicsit furcsa önt, Charles de Maure kapitányt ebben a szerepben látni... Remélem, tudja garantálni a mentességet azoknak, akik önhöz fordulnak a tárgyalásokért...";
			link.l1 = "Ebben biztos lehet, Mynheer Stuyvesant.";
			link.l1.go = "Stivesant_34";
		break;
		
		case "Stivesant_34":
			dialog.text = "Szóval, adna nekem egy lehetôséget, hogy elolvassam a megállapodást, amelyet elôkészített? Ha jól értem, a levél tartalmát tartalmazza?";
			link.l1 = "Pontosan, Mynheer, csak hivatalos formában. Franciaország részérôl - a semleges kapcsolatok helyreállítása, Sint Maarten szigetére vonatkozó minden igény elutasítása. Anglia részérôl - a kereskedelmi háború befejezése. A részleteket mind leírták itt ... És természetesen anyagi kártérítés az önök által kezdeményezett katonai akciók miatt elszenvedett károkért.";
			link.l1.go = "Stivesant_35";
		break;
		
		case "Stivesant_35":
			dialog.text = "Kérem, legyen olyan kedves és adja ide a dokumentumot.";
			link.l1 = "Hát persze.";
			link.l1.go = "Stivesant_36";
		break;
		
		case "Stivesant_36":
			dialog.text = "...(olvasás)...";
			link.l1 = "...";
			link.l1.go = "Stivesant_37";
		break;
		
		case "Stivesant_37":
			LAi_Fade("", "");
			dialog.text = "Mivel nem hagytak más választást, aláírom ezt a megállapodást. De számomra Willemstad és lakosainak védelme a legfontosabb.";
			link.l1 = "Ezután mindhárom példányt aláírással hitelesítjük. Philippe de Poincy fôkormányzótól felhatalmazást kaptam, hogy Franciaország részérôl jóváhagyjam a dokumentumot, Anglia részérôl Doily ezredes fogja aláírni.";
			link.l1.go = "Stivesant_38";
		break;
		
		case "Stivesant_38":
			dialog.text = "...(aláírás)...";
			link.l1 = "Tökéletes! Most már alá kellene írnunk...";
			link.l1.go = "Stivesant_39";
		break;
		
		case "Stivesant_39":
			LAi_Fade("", "");
			dialog.text = "Szóval, úgy hiszem, most már lefújja az ostromot?";
			link.l1 = "Kétségtelenül. Remélem, hogy a holland fél a megállapodás minden feltételét betartja, anélkül, hogy megsérti azt.";
			link.l1.go = "Stivesant_40";
		break;
		
		case "Stivesant_40":
			dialog.text = "Ha Anglia vagy Franciaország nem sérti meg, akkor mi is betartjuk a szerzôdés feltételeit, ne aggódjon.";
			link.l1 = "Mindig jobb kereskedni, mint harcolni, Mynheer Stuyvesant. És most már nyugodtan visszatérhet Willemstadba. Az ostromot feloldják, és hajórajunk hamarosan elhagyja Curacao vizeit.";
			link.l1.go = "Stivesant_41";
		break;
		
		case "Stivesant_41":
			DialogExit(); // Стайвесант уходит, подходит д'Ойли
			Patria_CuracaoStivesantGo();
		break;
		
		case "Stivesant_42":
			dialog.text = "Szóval, ön Noel Forget báró? Huh, és ön bizonyára maga Monsieur Charles de Maure! Üdvözlöm, admirális-helyettes úr! Nem véletlenül nevezik Önt a szigetvilág legravaszabb összeesküvôjének - nem lehet tudni, hogy jelenleg kinek az oldalán áll...";
			link.l1 = "Az ellentengernagy jelenleg a király és az önök ôszinte, meghatalmazott képviselôjének oldalán áll.";
			link.l1.go = "Stivesant_43";
		break;
		
		case "Stivesant_43":
			dialog.text = "A király messze van innen, és Franciaország is, báró úr, de Szent Kristóf és Chevalier de Poincy közel van. Ô a francia gyarmatok igazi tulajdonosa. De facto... De vajon azért van itt, hogy megszerezzen valamit, ami kompromittálja de Poincy-t a pénzügyminiszter szemében?";
			link.l1 = "Pontosan, Mynheer.";
			link.l1.go = "Stivesant_44";
		break;
		
		case "Stivesant_44":
			dialog.text = "Vannak ilyen dokumentumaim. Ez egy egész fôkönyv az én és de Poincy számláival a bányáról és néhány más ügyrôl. Ezen kívül talál benne egy egész halom papírt, amelyek az üzlethez kapcsolódnak, Philippe de Poincy személyes aláírásával. Garantálom önnek, hogy ezeknek a papíroknak a tartalma egy érdeklôdô személy kezében mélyebbre fojtja Chevalier-t, mint a Karib-tenger feneke.";
			link.l1 = "Mit akar ezért a fôkönyvért?";
			link.l1.go = "Stivesant_45";
		break;
		
		case "Stivesant_45":
			dialog.text = "Egy fillérért adom el. Csupán egymillió pezó ezüstben.";
			link.l1 = "Egymillió pezó?!";
			link.l1.go = "Stivesant_46";
		break;
		
		case "Stivesant_46":
			dialog.text = "Így van, báró. Ez az összeg legalább részben fedezi a közelmúltbeli háború okozta veszteségeket. Adok egy tanácsot: forduljon Charles de Maure úrhoz. A de Poincy-nak és khm... másoknak tett szolgálatai során valószínûleg hatalmas vagyonra tett szert, és az egymillió megszerzése nem fog neki gondot okozni. Szinte biztos vagyok benne.\nAdok egy határidôt - egy hónapot. Ezen idô elteltével, ha nem hozza el a jelzett összeget, levelet küldök a Chevaliernek, amelyben leírom a nálam tett látogatásának részleteit. Kitalálhatod, mi történik ezután.";
			link.l1 = "Maga zsarol engem! Meg kell értenie, hogy nekem nem lehet egymillióm a gyarmatokon!";
			link.l1.go = "Stivesant_47";
		break;
		
		case "Stivesant_47":
			dialog.text = "Természetesen megértem. Ezért azonnal rámutattam arra a személyre, aki rendelkezik ezzel a millióval. Ha Monsieur de Maure visszautasítja, az lesz a legjobb, báró úr, ha elhajózik Európába, mielôtt a Chevalier megkapja a levelemet, különben azt kockáztatja, hogy örökre itt marad. Ami Monsieur de Maure-t illeti... természetesen elveszíti az admirálisi rangját, de kijut... és talán még de Poincy-tól is megszabadul a módszereivel, nekem ez teljesen megfelel.\nNos, uraim, hallották, amit mondtam. Egy hónap múlva egy millióval várom önöket a rezidenciámon. Garantáltan szabad be- és kilépés.";
			link.l1 = "...";
			link.l1.go = "Stivesant_48";
		break;
		
		case "Stivesant_48":
			DialogExit();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			locCameraTarget(pchar);
			locCameraFollow();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = true;
			bDisableCharacterMenu = false;
			sld = CharacterFromID("Noel");
			sld.dialog.currentnode = "noel_84";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
			sld = CharacterFromID("Stivesant");
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "Patria_CondotierStivesantInHall", 12.0);
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("Stivesant_sold_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
			}
		break;
		
		case "Stivesant_49":
			if (sti(pchar.money) >= 1000000)
			{
				dialog.text = "Charles de Maure ellentengernagy úr, még csak nem is kételkedtem abban, hogy elhozza nekem ezt a pénzt. Talán túl keveset kértem öntôl, de hát... A báró csak egy bábu a következô játszmájában, igaz? A rang és a pénz nem elég önnek, most már de Poincy helyét is át akarja venni, igazam van? Egyet kell értenie, egy millió nem nagy összeg a francia gyarmatok fôkormányzói posztjáért! Ezt a pénzt hónapokon belül visszakapja, ha a maga vasmarkát vesszük figyelembe.";
				link.l1 = "Fogja az egymillióját, Mynheer. Szeretném visszakapni az ígért fôkönyvemet.";
				link.l1.go = "Stivesant_50";
			}
			else
			{
				dialog.text = "Jobb, ha az egymillió begyûjtésére koncentrál, Monsieur, ahelyett, hogy értelmetlen látogatásokra pazarolja az idejét.";
				link.l1 = "...";
				link.l1.go = "Stivesant_49_1";
			}
		break;
		
		case "Stivesant_49_1":
			DialogExit();
			npchar.dialog.currentnode = "Stivesant_49";
		break;
		
		case "Stivesant_50":
			pchar.quest.Patria_CondotierStivesantTimeOver.over = "yes"; // снять таймер
			AddMoneyToCharacter(pchar, -1000000);
			GiveItem2Character(pchar, "Reserve_item_01");
			ref itm = ItemsFromID("Reserve_item_01");
			itm.picIndex = 15;
			itm.picTexture = "ITEMS_26";
			itm.price = 0;
			itm.Weight = 2.0;
			itm.name = "itmname_Reserve_item_01_1";
			ChangeItemDescribe("Reserve_item_01", "itmdescr_Reserve_item_01_4");
			dialog.text = "Természetesen, admirális-helyettes. És ne ráncolja a homlokát: ha majd fôkormányzó lesz, meglátja, hogy a Holland Nyugat-indiai Kereskedelmi Társaság jövedelmezôbb üzleti partner, mint a kapzsi és háborúskodó britek. Hát nem tudja, hogy ha egy britnek az ujját adja, az egész kezét elveszi? Ha nem, akkor ezt a nehezebb úton fogod megtanulni. Úgyhogy még nem búcsúzom el tôletek. Tartsa meg a papírjait. Remélem, a bárójuk elég kompetens ahhoz, hogy legyôzze Chevalier-t.";
			link.l1 = "Köszönöm. Viszlát, Mynheer Stuvesant.";
			link.l1.go = "Stivesant_51";
		break;
		
		case "Stivesant_51":
			DialogExit();
			AddQuestRecord("Patria", "84");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", -1);
			pchar.quest.Patria_CondotierCabin.win_condition.l1 = "location";
			pchar.quest.Patria_CondotierCabin.win_condition.l1.location = "Curacao";
			pchar.quest.Patria_CondotierCabin.function = "Patria_CondotierCabin";
		break;
		
		case "vanberg_sold":
			dialog.text = "Ha-ha-ha-ha! Nézzenek oda! Jacobnak igaza volt, mint mindig - ez a róka jó okkal ment a szigetre. Úgy tûnik, hogy egy rakás arany van a ládában. Nagyon óvatlan vagy, hogy egyedül jöttél ide, barátom. De ez megkönnyíti a munkánkat!";
			link.l1 = "Azok a szemétládák lenyomoztak! Nem gondoltam, hogy ez lesz... De nem leszek könnyû préda!";
			link.l1.go = "vanberg_sold_1";			
		break;
		
		case "vanberg_sold_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("vanberg_sold_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "PrepareMassakraInShore");
			AddDialogExitQuest("MainHeroFightModeOn");			
		break;
		
		case "Abihouselady":
			dialog.text = "Keres valakit?";
			link.l1 = "Igen, az vagyok. Hol van Solomon és Abigail Shneur?";
			link.l1.go = "Abihouselady_1";			
		break;
		
		case "Abihouselady_1":
			dialog.text = "Már nem laknak itt. Egyszerûen nem engedhetik meg maguknak a helyet. Abigail, szegény lány, a kormányzó egyik szolgájaként dolgozik. Keményen dolgozik minden nap, hogy megélhetést biztosítson magának és az apjának. Salamon minden nap a kocsmában iszik, nem bírja elviselni, ami velük történt. Most egy kis kunyhóban élnek, nem messze a tengertôl...";
			link.l1 = "Ó... Rendben, köszönöm az információt. Mennem kell.";
			link.l1.go = "Abihouselady_2";
		break;
		
		case "Abihouselady_2":
			DialogExit();
			NextDiag.CurrentNode = "Abihouselady_3";
		break;
		
		case "Abihouselady_3":
			dialog.text = "Mit szeretnél még tudni, Mynheer?";
			link.l1 = "Semmit, nem számít.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Abihouselady_3";
		break;
		
		//удаление Мейфенг при провале квеста
		case "TempOffGuard":
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//удаляем атрибут квестового корабля
			if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_MAYFANG)
			{
				pchar.Ship.Type = GenerateShipExt(SHIP_TARTANE, true, pchar);
				pchar.Ship.name = "A boat";
				SetBaseShipData(pchar);
				SetCrewQuantityOverMax(PChar, 0);//сажаем на тартану
			}
			else
			{
				for(i = 1; i < COMPANION_MAX; i++)
				{
						iTemp = GetCompanionIndex(PChar, i);
					if(iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
						{
							pchar.questTemp.HWIC.Self.CompanionIndex = sld.Index;
							sld = GetCharacter(sti(pchar.questTemp.HWIC.Self.CompanionIndex));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			dialog.text = "Kapitány úr, ön eltulajdonította a Holland Nyugat-indiai Társaság egyik hajóját. Felhatalmaztak, hogy elkobozzam, és ellenállás esetén erôszakot alkalmazzak. Ez Peter Stuyvesant parancsa.";
			link.l1 = "Nos, ha ez maga Peter Stuyvesant parancsa... Nem fogok háborúzni Hollandiával egy hajó miatt. Vigyék.";
			link.l1.go = "TempOffGuard_1";			
		break;
		
		case "TempOffGuard_1":
			dialog.text = "Jó magának, hogy észérveket mutat.";
			link.l1 = "...";
			link.l1.go = "TempOffGuard_2";
		break;
		
		case "TempOffGuard_2":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;//открыть локацию
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");
		break;
		
		// Jason НСО
		case "arest":
			dialog.text = "Természetesen itt az ideje, hogy elmenj, még el is kísérlek. Ôrség! Kapjátok el!";
		    link.l1 = "Kényszerítsetek!";
		    link.l1.go = "fight";
		break;
		
		case "fight":
            Pchar.quest.ArestInResidenceEnd.win_condition.l1          = "ExitFromLocation";
		    Pchar.quest.ArestInResidenceEnd.win_condition.l1.location = Pchar.location;
		    Pchar.quest.ArestInResidenceEnd.win_condition             = "ArestInResidenceEnd";
		    Pchar.quest.ArestInResidenceEnd.ResidenceLocation = Pchar.location;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_LockFightMode(Pchar, true); // ножками путь убегает
		    LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		    LAi_group_Attack(NPChar, Pchar); // не работает на бессмертного мера :(
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // фантом солдат
			if (i != -1)
			{
			    LAi_group_Attack(&Characters[i], Pchar);
			}
		break;
		
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar, "Hé, figyeljetek! Mint a város polgára, megkérlek, hogy ne járkálj felnyílt pengével a kezedben.", "Tudod, mint a város polgára, tisztelettel megkérlek, hogy ne járkálj felnyílt pengével a kezedben.");
			link.l1 = LinkRandPhrase("Jól van.", "Rendben.", "Ahogy mondod...");
			link.l1.go = "exit";
		break;
	}
}

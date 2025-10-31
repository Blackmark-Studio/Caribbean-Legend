// диалоги НПС по квесту 'Карибские нравы'
void ProcessDialogEvent()
{
	ref NPChar, sld, rColony;
	aref Link, NextDiag;
	int iTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Mit szeretne?";
			link.l1 = "Nem, semmit.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// Жерар Лекруа
		case "lecrua":
			pchar.quest.Trial_LineOver.over = "yes"; //снять таймер
			dialog.text = "Jó napot kívánok. Ön bizonyára "+GetFullName(pchar)+"?";
			link.l1 = "Igaza van, Monsieur LeCroix. Kapitány "+GetFullName(pchar)+" szolgálatára. Fadey, a moszkovita ajánlotta önt nekem...";
			link.l1.go = "lecrua_1";
			DelLandQuestMark(npchar);
		break;
		
		case "lecrua_1":
			iTemp = FindColony("Baster");
			rColony = GetColonyByIndex(iTemp);
			bOk = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			dialog.text = "Igen, igen, igen. Kedves barátom, Fadey részletesen leírta önt és a helyzetét. Tudtam, hogy ön az, amint megláttam az ajtóban. Mondja kapitány, milyen hajója van?";
			if(sti(pchar.ship.type) == SHIP_NOTUSED || !bOk)
			{
				link.l1 = "Ah... jelenleg nincs hajóm, monsieur...";
				link.l1.go = "lecrua_noship";
			}
			else
			{
				link.l1 = "Van egy "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(RealShips[sti(pchar.ship.type)].basetype), "nevem")))+", a neve "+pchar.ship.name+".";
				if (6-sti(RealShips[sti(pchar.ship.type)].Class) < 0) link.l1.go = "lecrua_badship";
				else link.l1.go = "lecrua_2";
			}
		break;
		
		case "lecrua_noship":
			dialog.text = "Ha! Akkor miféle kapitány maga, ha nincs hajója? Sajnálom, uram, de ebben az esetben nem tudok munkát ajánlani önnek. Minden jót, adja át üdvözletemet Fadeynek!";
			link.l1 = "Hm...";
			link.l1.go = "lecrua_exit";
			sTotalTemp = "I don't have a ship at the moment";
		break;
		
		case "lecrua_badship":
			dialog.text = "Nos, ez egyszerûen nem fog menni. Az nem hajó, uram, hanem egy csónak! Sajnos, monsieur, ön nem illik a szerepbe. Üdvözlöm Fadeyt a nevemben, jó napot!";
			link.l1 = "Hm...";
			link.l1.go = "lecrua_exit";
			sTotalTemp = "My ship wasn't big enough for him";
		break;
		
		case "lecrua_exit":
			DialogExit();
			npchar.lifeday = 0;
			NextDiag.CurrentNode = "lecrua_repeat";
			AddQuestRecord("Trial", "3");
			AddQuestUserData("Trial", "sText", sTotalTemp);
			CloseQuestHeader("Trial");
			DeleteAttribute(pchar, "questTemp.Trial");
			pchar.questTemp.TrialEnd = true;
		break;
		
		case "lecrua_repeat":
			dialog.text = "Ön és én már mindent megbeszéltünk, monsieur. Nem igaz?";
			link.l1 = "Oui, Monsieur LeCroix... Máris megyek.";
			link.l1.go = "exit";
			NextDiag.TempNode = "lecrua_repeat";
		break;
		
		case "lecrua_2":
			dialog.text = "Remek. Ebben az esetben, maga jól illik hozzám. Készen áll, hogy azonnal tengerre szálljon?";
			link.l1 = "Igen, uram, készen állok. Mit kell tennem?";
			link.l1.go = "lecrua_3";
		break;
		
		case "lecrua_3":
			sld = characterFromId("BasTer_trader");
			dialog.text = "Egy kis adag lôport és bombákat kell szállítanod Kikötô-au-Prince-be, a francia Hispaniolára. A parancsnok már régóta vár rá, úgyhogy ne veszítsd az idôt, körülbelül tíz napod van hátra\nRespected "+GetFullName(sld)+" gondoskodik a szállításról és a hajóra rakodásról. A parancsnok ötezer darab nyolcezret fizet neked a munkáért.";
			link.l1 = "És ez az egész munka?";
			link.l1.go = "lecrua_4";
		break;
		
		case "lecrua_4":
			dialog.text = "Ó, semmi gond, uram. A parancsnok majd elmagyarázza az igazi feladatot, amikor elhozza a lôszert. Ez a szállítmány csak egy kis aperitif az ön elôtt álló munkához. De ne féljen, ha jól végzi a munkát, komoly pénzt fog keresni.";
			link.l1 = "Teljes figyelmem az öné, monsieur. A hajóm készen áll a rakomány felvételére.";
			link.l1.go = "lecrua_5";
		break;
		
		case "lecrua_5":
			dialog.text = "Akkor ne vesztegessük az idôt, kapitány! Menjen a hajójához, és készüljön fel az indulásra.";
			link.l1 = "Megyek már!";
			link.l1.go = "lecrua_6";
		break;
		
		case "lecrua_6":
			DialogExit();
			NextDiag.CurrentNode = "lecrua_repeat";
			AddQuestRecord("Trial", "4");
			pchar.questTemp.Trial = "fraht";
			AddMapQuestMarkCity("PortPax", false);
			// belamour legendary edition халява по чекбоксу
			if(!bImCasual) SetFunctionTimerCondition("Trial_FrahtFail", 0, 0, 17, false); // таймер
			else NewGameTip("Felfedezô mód: az idôzítô ki van kapcsolva.");
			SetFunctionTimerCondition("Trial_LecruaHide", 0, 0, 1, false); // таймер
			// груз
			SetCharacterGoods(pchar, GOOD_BOMBS, GetCargoGoods(pchar, GOOD_BOMBS)+2500);
			SetCharacterGoods(pchar, GOOD_POWDER, GetCargoGoods(pchar, GOOD_POWDER)+2500);
			// Sinistra Пасхалка с Диего
			pchar.quest.VsD_DiegoNachalo.win_condition.l1 = "Ship_location";
			pchar.quest.VsD_DiegoNachalo.win_condition.l1.location = "PortPax_town";
			PChar.quest.VsD_DiegoNachalo.win_condition = "VsD_DiegoNachalo";
			
			// отключить все враждебные энкаунтеры на глобальной карте
			pchar.worldmapencountersoff = "1";
			SetFunctionTimerCondition("DelNavigatorNoShow", 0, 0, 180, false);
			pchar.systeminfo.tutorial.navigatorTrial = true;
		break;
		
		// Флориан Шоке
		case "florian_deck":
			if(!bImCasual) pchar.quest.Trial_CannonFail.over = "yes"; // belamour legendary edition снять таймер
			DelMapQuestMarkShore("shore47");
			DelLandQuestMark(npchar);
			sld = CharacterFromID("PortRoyal_shipyarder");
			if(CheckAttribute(sld, "TrialDelQuestMark"))
			{
				DeleteAttribute(sld, "TrialDelQuestMark");
				DelLandQuestMark(sld);
				DelMapQuestMarkCity("PortRoyal");
			}
			dialog.text = "Miben segíthetek, uram?";
			link.l1 = "Jó napot, kapitány. Maga Florian Shoke, ugye?";
			link.l1.go = "florian_deck_1";
		break;
		
		case "florian_deck_1":
			dialog.text = "Igen, én vagyok. És önök a Kikötô-au-Prince-i csomaghajó, ha nem tévedek?";
			link.l1 = "Igen, van tizenöt ágyúm az ön számára. A határidô majdnem lejárt, alig bírtam ki...";
			link.l1.go = "florian_deck_2";
		break;
		
		case "florian_deck_2":
			if (GetSquadronGoods(pchar, GOOD_CANNON_24) < 15)
			{
				dialog.text = "Hm. Furcsa humorérzéke van, uram! Valamiért nem látom, hogy tizenöt ágyút pakolnának ki a hajójáról...";
				link.l1 = "Nos, tudja, volt egy lékünk, és a rakomány egy részét ki kellett dobnunk a fedélzetre...";
				link.l1.go = "florian_deck_fail";
			}
			else
			{
				dialog.text = "Örülök, hogy látom, kapitány...";
				link.l1 = ""+GetFullName(pchar)+". Kapitány "+GetFullName(pchar)+".";
				link.l1.go = "florian_deck_3";
			}
		break;
		
		case "florian_deck_3":
			dialog.text = "Örülök, hogy megismerhetem. Ne vesztegessük az idôt, és vigyük fel ezeket az ágyúkat a fedélzetre. Ez nem lesz könnyû, úgyhogy szükségem lesz az emberei segítségére.";
			link.l1 = "Megoldjuk. Maga ott, állítsa fel a tákolmányt és a szerelvényt a egy hajógyárban!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Trial_TakeCannons");
		break;
		
		case "florian_deck_fail":
			dialog.text = "Te istenverte idióta! Ha még ezzel az egyszerû feladattal sem tudsz megbirkózni, a következô viharban biztosan elsüllyedsz. Menjen vissza a hajójára, kapitány, és csináljon valami olyat, amiben jobb, például virágot szállítson a nemes hölgyeknek. Még jobb, ha visszahajózol Európába, és az Újvilágot az igazi férfiakra hagyod. Jó napot, uram!";
			link.l1 = "De...";
			link.l1.go = "florian_deck_fail_1";
		break;
		
		case "florian_deck_fail_1":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true; 
			RemoveCharacterGoods(pchar, GOOD_CANNON_24, GetCargoGoods(pchar, GOOD_CANNON_24));
			SetFunctionTimerCondition("Trial_RemoveFlorian", 0, 0, 1, false);
			sld = characterFromId("Lecrua");
			sld.lifeday = 0;
			AddQuestRecord("Trial", "10");
			CloseQuestHeader("Trial");
			DeleteAttribute(pchar, "questTemp.Trial");
			pchar.questTemp.TrialEnd = true;
			ChangeCharacterNationReputation(pchar, FRANCE, -3);
		break;
		
		case "florian_deck_4":
			dialog.text = "Hú, ez aztán szomjas munka volt! Köszönöm a szolgálatot, kapitány! Vegye el a jutalmát, kétszáz dublont.";
			link.l1 = "Köszönöm!";
			link.l1.go = "florian_deck_5";
		break;
		
		case "florian_deck_5":
			TakeNItems(pchar, "gold_dublon", 200);
			dialog.text = "De ez még nem minden, kapitány. Szeretne még 75 arany dupla escudót?";
			link.l1 = "Ez ígéretesen hangzik, de attól függ, hogy mit kér tôlem érte, uram.";
			link.l1.go = "florian_deck_6";
		break;
		
		case "florian_deck_6":
			dialog.text = "Nem fogok hazudni, ez veszélyes. Mint már talán tudjátok, egy spanyol nehéz gályára leselkedtem, értékes rakománnyal. A hajót a dokkokba tették javításra. A forrásaim szerint tegnap kellett volna kihajóznia, de ez nem történt meg\nMellesleg a portobellói ügynököm nem jutott el a találkozási pontra, hogy átadja az általam várt frissítéseket. Gyanítom, hogy a spanyolok tartóztatták le. Fizetek neked, hogy osonj be Portobellóba, és derítsd ki két dolgot: miért van még mindig ott a gálya, és mi történt az ügynökömmel. Benne vagy?";
			link.l1 = "Attól tartok, nincs megfelelô kiképzésem egy ilyen akcióhoz. Én úriember vagyok, nem kém. Lehet, hogy magam is bajba kerülök, és nem tudnék segíteni.";
			link.l1.go = "florian_deck_bye";
			link.l2 = "Veszélyesen hangzik, de jövedelmezô. Megkockáztatom. Hogy hívják az emberét, és mi a gálya neve?";
			link.l2.go = "florian_deck_7";
		break;
		
		case "florian_deck_bye":
			dialog.text = "Hát, nem jogosult rá? Megértem magát. Akkor viszlát, kapitány, még egyszer köszönöm a segítségét!";
			link.l1 = "Minden jót, Monsieur Shoke.";
			link.l1.go = "florian_deck_bye_1";
		break;
		
		case "florian_deck_bye_1":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true; 
			SetFunctionTimerCondition("Trial_RemoveFlorian", 0, 0, 1, false);
			sld = characterFromId("Lecrua");
			sld.lifeday = 0;
			AddQuestRecord("Trial", "11");
			CloseQuestHeader("Trial");
			DeleteAttribute(pchar, "questTemp.Trial");
			pchar.questTemp.TrialEnd = true;
		break;
		
		case "florian_deck_7":
			dialog.text = "Igen, akkor jól figyelj. Az emberem neve Sylvan Laforet, de Portobellóban Jaime Silicio kereskedônek hívják. A gálya neve 'Alacantara'. Azt tanácsolom, hogy éjjel, a dzsungelen keresztül menjetek át a város kapuján. A portobellói ôrök mostanában nagyon gyanakvóak, arról nem is beszélve, hogy Sylvan eltûnése nem sok jót ígér arra nézve, hogy életben van és jól van. Két napotok van, amíg el kell tûnnöm innen, mielôtt a spanyol ôrjáratok ránk találnak. Sok szerencsét, monsieur!";
			link.l1 = "Hamarosan találkozunk, Monsieur Shoke...";
			link.l1.go = "florian_deck_8";
		break;
		
		case "florian_deck_8":
			bQuestDisableMapEnter = true;//закрыть карту
			pchar.GenQuest.MapClosedNoBattle = true; // доступно ожидание и sailto
			DialogExit();
			npchar.DeckDialogNode = "florian_deck_repeat";
			NextDiag.CurrentNode = "florian_deck_repeat";
			pchar.questTemp.Trial = "spy";
			AddQuestRecord("Trial", "12");
			// belamour legendary edition -->
			if(!bImCasual) 
			{
				pchar.quest.trial_spy_over.win_condition.l1 = "Timer";
				pchar.quest.trial_spy_over.win_condition.l1.date.hour  = sti(GetTime() + 2);
				pchar.quest.trial_spy_over.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 2);
				pchar.quest.trial_spy_over.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
				pchar.quest.trial_spy_over.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 2);
				pchar.quest.trial_spy_over.function = "Trial_SpyTimeOver";
			}
			else NewGameTip("Felfedezô mód: az idôzítô ki van kapcsolva.");
			// <-- legendary edition
			//Log_Info("You have received amulet 'Gypsy's fan'");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "obereg_4");
			pchar.quest.NewGameTip5.win_condition.l1 = "location";
			pchar.quest.NewGameTip5.win_condition.l1.location = "PortoBello_town";
			pchar.quest.NewGameTip5.function = "ShowNewGameTip";
			pchar.quest.NewGameTip5.text = "Az ôrök kevésbé gyanakodnak, ha lassú tempóban sétálsz!";
			
			pchar.quest.Trial_CreatHabitue.win_condition.l1 = "location";
			pchar.quest.Trial_CreatHabitue.win_condition.l1.location = "PortoBello_tavern";
			pchar.quest.Trial_CreatHabitue.function = "Trial_CreatHabitue";
			
			pchar.quest.Tutorial_stealth.win_condition.l1 = "location";
			pchar.quest.Tutorial_stealth.win_condition.l1.location = "PortoBello_ExitTown";
			pchar.quest.Tutorial_stealth.function = "Tutorial_stealth";
			
			QuestPointerToLoc("shore47", "reload", "reload1_back");
			QuestPointerToLoc("PortoBello_Jungle_02", "reload", "reload1_back");
			QuestPointerToLoc("PortoBello_Jungle_01", "reload", "reload3_back");
			QuestPointerToLoc("PortoBello_ExitTown", "reload", "reload4");
			QuestPointerToLoc("PortoBello_Town", "reload", "reload41_back");
			QuestPointerToLoc("PortoBello_Town", "reload", "reload4_back");
		break;
		
		case "florian_deck_repeat":
			dialog.text = "Mindent megbeszéltünk kapitány, nem igaz?";
			link.l1 = "Igen. Már úton vagyok.";
			link.l1.go = "exit";
			NextDiag.TempNode = "florian_deck_repeat";
		break;
		
		case "florian_failspy":
			pchar.quest.trial_spy_over.over = "yes"; //снять прерывание
			dialog.text = "Hogy haladnak a dolgok, kapitány? Mit sikerült kiderítenie?";
			link.l1 = "A dolgok rosszul alakulnak, Monsieur Shoke. Nem vagyok valami jó kém, nagyon hamar rájöttek. El kellett menekülnöm a városból, miután megküzdöttem néhány ôrrel. Az egyetlen dolog, amit sikerült megtudnom, hogy az ön emberét, Sylvan Laforet-t letartóztatták és börtönben tartják.";
			link.l1.go = "florian_failspy_1";
		break;
		
		case "florian_failspy_1":
			dialog.text = "Az isten verje meg! Ez nem jó... Megtudtál valamit a gályáról?";
			link.l1 = "Nem, nem tudtam.";
			link.l1.go = "florian_failspy_2";
		break;
		
		case "florian_failspy_2":
			dialog.text = "A francba. Tényleg szükségem lenne néhány információra róla. De ez a díj túl kövér ahhoz, hogy feladjam! Mindegy, megpróbálok odaküldeni egy másik felderítôt... Kapitány, kérem, hogy egyelôre ne hagyjon itt. Szükségem lehet a segítségére. Várnál egy másik napig, amíg én az Alacantara-ról szimatolok?";
			link.l1 = "Persze, hogy várok! Szeretném jóvátenni ezt a kudarcot.";
			link.l1.go = "florian_9";
			link.l2 = "Nem hinném. Úgy tûnik, túl rossz vagyok ezekben a játékokban. Hazafelé veszem az irányt.";
			link.l2.go = "florian_failspy_3";
		break;
		
		case "florian_failspy_3":
			dialog.text = "Nos, ez a te döntésed. Minden jót, kapitány.";
			link.l1 = "Viszlát, Monsieur Shoke.";
			link.l1.go = "florian_failspy_4";
		break;
		
		case "florian_failspy_4":
			DialogExit();
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true; 
			SetFunctionTimerCondition("Trial_RemoveFlorian", 0, 0, 1, false);
			sld = characterFromId("Lecrua");
			sld.lifeday = 0;
			CloseQuestHeader("Trial");
			DeleteAttribute(pchar, "questTemp.Trial");
			pchar.questTemp.TrialEnd = true;
		break;
		
		case "florian_failspy_5":
			pchar.quest.trial_spy_over.over = "yes"; //снять прерывание
			dialog.text = "Hogy haladnak a dolgok, kapitány? Mit sikerült kiderítenie?";
			link.l1 = "A dolgok rosszul alakulnak, Monsieur Shoke. Nem vagyok valami jó kém, nagyon hamar rájöttek. Az egyetlen dolog, amit sikerült megtudnom, hogy az ön emberét, Sylvan Laforet-t letartóztatták és valahol fogva tartják.";
			link.l1.go = "florian_failspy_1";
		break;
		
		case "florian_9":
			dialog.text = "Akkor menjen a hajójára, kapitány. Holnap ugyanebben az idôben, vagy egy kicsit késôbb, meg kell látogatnia engem. Talán addigra kiderítek valamit. Ne tegye a lábát a partra, várjon meg a hajóján!";
			link.l1 = "Rendben, akkor várjon meg a hajón. Rendben.";
			link.l1.go = "florian_10";
		break;
		
		case "florian_10":
			dialog.text = "És kapitány, fogd ezt az erszényt. Az erôfeszítései mégsem voltak teljesen hiábavalóak. Legalább tudjuk, mi történt szegény öreg Sylvannal...";
			link.l1 = "...";
			link.l1.go = "florian_11";
		break;
		
		case "florian_11":
			DialogExit();
			Island_SetReloadEnableGlobal("Portobello", false);//закрыть остров	
			npchar.DeckDialogNode = "florian_deck_wait";
			NextDiag.CurrentNode = "florian_deck_wait";
			pchar.questTemp.Trial = "spy_wait";
			pchar.quest.Trial_spyfail_wait.win_condition.l1 = "Timer";
			pchar.quest.Trial_spyfail_wait.win_condition.l1.date.hour  = sti(GetTime()+rand(12));
			pchar.quest.Trial_spyfail_wait.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Trial_spyfail_wait.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Trial_spyfail_wait.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Trial_spyfail_wait.function = "Trial_Spyfail_NextStage";
			TakeNItems(pchar, "purse2", 1);
			Log_Info("Kaptál egy erszény dublont.");
		break;
		
		case "florian_deck_wait":
			dialog.text = "Kapitány, pillanatnyilag nincs semmi újdonságom. Még mindig várunk...";
			link.l1 = "Jól van...";
			link.l1.go = "exit";
			NextDiag.TempNode = "florian_deck_wait";
		break;
		
		case "florian_12":
			pchar.quest.trial_spy_over.over = "yes"; //снять прерывание
			dialog.text = "Hogy haladnak a dolgok, kapitány? Mit sikerült kiderítenie?";
			link.l1 = "El van intézve. Az emberét, Sylvan Laforet-t letartóztatták és börtönben tartják fogva. Vége van számára.";
			link.l1.go = "florian_13";
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("PortoBello_Town", "reload", "gate_back");
			QuestPointerDelLoc("PortoBello_ExitTown", "reload", "reload1_back");
			QuestPointerDelLoc("PortoBello_Jungle_01", "reload", "reload2_back");
			QuestPointerDelLoc("PortoBello_Jungle_02", "reload", "reload3_back");
			QuestPointerDelLoc("shore47", "reload", "boat");
		break;
		
		case "florian_13":
			dialog.text = "Az istenit! Ez szörnyû... Megtudtál valamit a gályáról?";
			link.l1 = "Igen. Már egy ideje készül a hajóra, de Portobello kormányzója a kikötôben szándékozik tartani. Jelenleg arra vár, hogy Cartagenából megérkezzen egy 'Puebla' nevû barkentine, amely lôporszállítmányt visz a 'Alcantara'. gálya matróza szerint nincs elég belôle, és a kormányzó kalózoktól tart.";
			link.l1.go = "florian_14";
		break;
		
		case "florian_14":
			dialog.text = "Milyen érdekes!";
			link.l1 = "De ha a Puebla nem érkezik meg három napon belül, akkor az 'Alcantara' nem vár tovább és kihajózik.";
			link.l1.go = "florian_15";
		break;
		
		case "florian_15":
			dialog.text = "Kiváló munka, kapitány "+GetFullName(pchar)+"! Nagyon elégedett vagyok! Tessék, itt a jutalmad. Teljesen kiérdemelted!";
			link.l1 = "Köszönöm! Van még más feladatod is számomra?";
			link.l1.go = "florian_16";
		break;
		
		case "florian_16":
			TakeNItems(pchar, "gold_dublon", 75);
			dialog.text = "Olvasol a gondolataimban, "+GetFullName(pchar)+"! Igen, a fenébe is! Mivel az Alacantarának kevés a puskapora, hagyhatom, hogy kihajózzon a nyílt tengerre, aztán rákényszeríthetem egy elhúzódó tengeri harcra, amelyben az ô puskaporuk elôbb fogy el, mint a miénk, haha!\nEl kell érned, hogy az utánpótlásbárka Puebla soha ne érje el Portobellót. Nem hajózhatok közel a parthoz, a járôrök könnyen észreveszik a fregattomat, és elkergetnek, mielôtt elkaphatnám Alacantarát\nA Pueblával egyedül is elbánsz. Találjátok meg és szabaduljatok meg tôle. Süllyesszék el, vagy vegyék el zsákmányként, nem érdekel. Csak akadályozza meg, hogy ideérjen!\nHa sikerül, akkor menjen Guadeloupe-ra, és keresse fel Gerard LeCroix-t. Azt hiszem, már ismeri ôt, nem igaz? Meg fogja fizetni neked a megérdemelt érmét.";
			link.l1 = "Megegyeztünk! Máris indulok, hogy elvágjam a Pueblát!";
			link.l1.go = "florian_19";
			link.l2 = "Várjon egy kicsit, Monsieur Choquet. Az a helyzet, hogy én még mindig... Mondjuk úgy, hogy nem vagyok hozzászokva a tengeri csatákhoz. Ön pedig egy fregatt kapitánya, nyilván nem egy tengeri csatát tudhat maga mögött. Ha nem esik nehezére, akkor... Hogy is mondjam...";
			link.l2.go = "florian_guide_01";
		break;
		
		case "florian_17":
			dialog.text = "Örülök, hogy itt van, kapitány. Most kaptam információt a kémemtôl, és van egy fontos küldetésem az ön számára.";
			link.l1 = "Csupa fül vagyok.";
			link.l1.go = "florian_18";
		break;
		
		case "florian_18":
			dialog.text = "Az Alacantara készen áll a kihajózásra, de a gálya kapitánya várja, hogy a barkentine 'Puebla' megérkezzen Cartagenából lôszerrel megrakodva. Úgy tûnik, az Alacantara nem rendelkezik elegendô lôporral, ezért a spanyolok még nem állnak készen a kihajózásra. De a kapitány türelmének van határa, és ha Puebla nem jön három napon belül, akkor a gálya nélküle hagyja el Portobellót\nAz Alacantarának kevés a lôpora, hagyhatom, hogy kihajózzon a nyílt tengerre, és akkor hosszadalmas tengeri harcra kényszeríthetem, amelyben az ô puskaporuk elôbb fogy el, mint a miénk. A célod a Puebla elfogása és megsemmisítése. Süllyesszék el, vagy vegyék zsákmányul, nem érdekel. Csak akadályozd meg, hogy az utánpótlást szállító barkentine ideérjen!\nHa sikerül, akkor menj Guadeloupe-ra, és keresd fel Gerard LeCroix-t, azt hiszem, már ismered, nem igaz? Meg fogja fizetni neked a megérdemelt érmét.";
			link.l1 = "Megegyeztünk! Máris indulok, hogy elvágjam a Pueblát!";
			link.l1.go = "florian_19";
			link.l2 = "Várjon egy kicsit, Monsieur Choquet. Az a helyzet, hogy én még mindig... Mondjuk úgy, hogy nem vagyok hozzászokva a tengeri csatákhoz. Ön pedig egy fregatt kapitánya, nyilván nem egy tengeri csatát tudhat maga mögött. Ha nem esik nehezére, akkor... Hogy is mondjam...";
			link.l2.go = "florian_guide_01";
		break;
		
		case "florian_19":
			DialogExit();
			Island_SetReloadEnableGlobal("Portobello", true); // открыть остров
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true; 
			SetFunctionTimerCondition("Trial_RemoveFlorian", 0, 0, 1, false);
			Trial_CreatePueblaBarqueInWorld();
			pchar.questTemp.Trial = "puebla";
			AddQuestRecord("Trial", "19");
		break;
		// belamour legendary edition дополнительное обучение -->
		case "florian_guide_01":
			dialog.text = "Szeretnéd, ha leckét adnék neked a tengeri harc taktikájából? Örömmel, kapitány! Különösen, mivel ez a saját érdekemben történik: Biztos akarok lenni benne, hogy sikeresen elfogja a 'Puebla'.";
			link.l1 = "Nem, nem úgy értettem. Rendben, felejtse el: Biztos vagyok benne, hogy nem lesz gondom elkapni egy barkentine-t.";
			link.l1.go = "florian_19";
			link.l2 = "Igen, pontosan így értettem. Biztos vagyok benne, hogy ez az új tudás nem fog ártani nekem.";
			link.l2.go = "florian_guide_02";
		break;
		
		case "florian_guide_02":
			dialog.text = "Tehát az elsô dolog, amit nem szabad elfelejtened, hogy a csata fele már azelôtt megnyert vagy elvesztett dolog, hogy egyáltalán elkezdôdött volna. Sok múlik azon, hogy te és a hajód mennyire álltok készen rá.";
			link.l1 = "...";
			link.l1.go = "florian_guide_03";
		break;
		
		case "florian_guide_03":
			dialog.text = "Elôször is, gyôzôdjön meg róla, hogy a hajóját megjavították. Ha lyukak vannak a hajótestén, akkor nem lesz nehéz az ellenségnek a fenékre küldeni. Ha pedig rongyok lógnak vitorlák helyett, akkor ez nagyon jelentôsen korlátozza a mozgékonyságotokat. Az ellenség könnyen elmenekülhet elôled, ha az erôviszonyok nem neki kedveznek, vagy ami még rosszabb, utolérhet, és egy veszteséges csatát kényszeríthet rád - vagy akár azonnal a fedélzetedre is szállhat. Ráadásul szakadt vitorlákkal nehezen fogod tudni megszerezni az idôjárásmérôt, vagyis szélárnyékba kerülni az ellenfeledtôl, ahová szeretnél.";
			link.l1 = "Idôjárásmérô, értem. Még valami?";
			link.l1.go = "florian_guide_04";
		break;
		
		case "florian_guide_04":
			dialog.text = "Gyôzôdj meg róla, hogy van elég embered. Még a legerôsebb, 42 kilós ágyúkkal felszerelt hajó is használhatatlanná válik, ha egy tüzér rohangál három ágyú újratöltésére, és egyszerûen nincs, aki a vitorlákat irányítsa. Általában én egy ilyen hajóra azonnal felszállnék, és elfoglalnám.";
			link.l1 = "Elég ember, értettem.";
			link.l1.go = "florian_guide_05";
		break;
		
		case "florian_guide_05":
			dialog.text = "Emellett vigyázz az ágyúidra is: idôvel elhasználódnak és felrobbannak. Idôvel a csövek állapota romlik, és ha az ágyúid a csata közepén kezdenek el robbanni, az nagyon rosszul végzôdhet számodra. Nekem egyáltalán nem volt szerencsém: az ágyúkról, amelyekkel vitorláztam, kiderült, hogy több öntési hiba is volt bennük. Ha nem hoztatok volna idôben pótlást, egyszerûen feladtam volna a hadmûveletet, hiszen a Militant tûzerejében sokkal gyengébb lett volna, mint az Alcantara. Az eszközöket idôben kell cserélni.";
			link.l1 = "Most már értem, miért volt ez olyan fontos!";
			link.l1.go = "florian_guide_06";
		break;
		
		case "florian_guide_06":
			dialog.text = "Az ágyúk mellett a lôszer mennyiségére is figyelni kell. Az Alcantara emiatt fog nekem esni. Ha kevés lôporral rendelkezik, nem lesz képes hosszú csatát vívni - azonnal közelharcba kell vonulnia. És erre fogok játszani: a fregattom gyorsabb, egy nehéz gálya nem fog tudni meglépni elôle. De nekem sem kell közelharcba kerülnöm: Tüzérségi párbajt fogok elrendelni nagy távolságból, majd amikor az Alcantara puskapora elfogy, közel megyek, grappeshot-tal gereblyézem, és felszállok rá.";
			link.l1 = "Kétségbeesett helyzet...";
			link.l1.go = "florian_guide_07";
		break;
		
		case "florian_guide_07":
			dialog.text = "Pontosan. Tartsd szemmel a puskaport és a lôszert. Ha elfogy a szilárd lövedék - és valószínûleg nem leszel képes elsüllyeszteni egy ellenséges hajót. Ha elfogy a szôlôlövedék - nem reménykedhetsz a partraszállásban, ha túlerôben vagy. Ha nincs chainshotod vagy knipplesed, nem fogod tudni utolérni az ellenséget, vagy nem fogsz tudni elmenekülni elôle, ha gyorsabb. Mindenféle lôszer fontos.";
			link.l1 = "Tanulságos, köszönöm.";
			link.l1.go = "florian_guide_08";
		break;
		
		case "florian_guide_08":
			dialog.text = "És végül, a hajód és az ellenséges hajó típusától és méretétôl függôen alkalmazd a megfelelô taktikát. A tengeren kompromisszumot kell kötni a tûzerô és a sebesség között. Egy nagy és lassú hajón nincs értelme egy brigget vagy korvettet üldözni, hogy felszállhass - úgysem éred utol, ha nem puhítod meg elôbb lánclövéssel. Ilyenkor bölcsebb, ha lôtávolról szétrobbantod, és a roncsok között szeded szét. Ha mégis fel kell szállnod egy ilyen hajóra, akkor inkább egy gyors és manôverezô hajót használj.";
			link.l1 = "...";
			link.l1.go = "florian_guide_09";
		break;
		
		case "florian_guide_09":
			dialog.text = "Ugyanakkor ne menjen szemtôl szembe egy brigggel rendelkezô hajóval. Egy ilyen szörnyeteg egyetlen széles oldalcsapása szilánkká zúzza a kisebb hajók' hajótestét. Használd ki a sebességben és manôverezôképességben rejlô elônyödet, tépd le az árbocát és a kötélzetét, majd közelítsd meg és gereblyézd a fedélzetét grapeshotokkal, ha mégis fel kell szállnod. Ha el kell süllyesztened... nem lesz könnyû feladat, de lehetséges. Felszállhatsz a fedélzetre, majd lôheted a puskaporos tárát, de soha nem szégyen elmenekülni. Egy jó kapitány a túlzott hôsiesség helyett megmenti a hajóját és a legénységet a biztos haláltól. Ne feledd, a diszkréció és az óvatosság gyakran a bátorság jobbik oldala.";
			link.l1 = "Köszönöm szépen, Monsieur Choquet!";
			link.l1.go = "florian_guide_10";
		break;
		
		case "florian_guide_10":
			AddCharacterSkillDontClearExp(pchar, SKILL_CANNONS, 1);
			AddCharacterSkillDontClearExp(pchar, SKILL_ACCURACY, 1);
			//Log_info(XI_ConvertString("Experience Bonus")+": +1 "+XI_ConvertString(SKILL_CANNONS));
			notification(XI_ConvertString("Tapasztalat bónusz")+": +1 ", SKILL_CANNONS);
			//Log_info(XI_ConvertString("Experience Bonus")+": +1 "+XI_ConvertString(SKILL_ACCURACY));
			notification(XI_ConvertString("Tapasztalat bónusz")+": +1 ",SKILL_ACCURACY);
			dialog.text = "Örülök, hogy segíthetek kapitány. Remélem, hogy ez a tudás segít önnek a jövôben.";
			link.l1 = "Biztos vagyok benne, hogy segíteni fog. Elindulunk, hogy elfogjuk a 'Pueblát.!'";
			link.l1.go = "florian_19";
		break;
		// <-- legendary edition дополнительное обучение

		// испанский офицер в таверне
		case "tavern_officer":
			dialog.text = "Szokatlan akcentusa van, senor. Vagy mondhatnám 'monsieur'? Szeretné látni Jaime Silicio-t? Talán megoszthatnának egy cellát. Vigyétek, fiúk!";
			link.l1 = "Nos, ha nem tetszik az akcentusom, talán bevezethetlek a francia kardforgatásba!";
			link.l1.go = "tavern_officer_1";
		break;
		
		case "tavern_officer_1":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorTypeNoGroup(npchar);
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
            LAi_group_SetCheck("EnemyFight", "Trial_AfterTavernFight");
			AddDialogExitQuest("MainHeroFightModeOn");
			SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}

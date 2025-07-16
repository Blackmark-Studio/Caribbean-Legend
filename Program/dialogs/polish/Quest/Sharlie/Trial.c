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
			dialog.text = "Czego chcesz?";
			link.l1 = "Nie, nic.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// Жерар Лекруа
		case "lecrua":
			pchar.quest.Trial_LineOver.over = "yes"; //снять таймер
			dialog.text = "Dzień dobry. Musisz być "+GetFullName(pchar)+"?";
			link.l1 = "Masz rację, Monsieur LeCroix. Kapitan "+GetFullName(pchar)+" do usług. Fadej Moskwicin polecił mi ciebie...";
			link.l1.go = "lecrua_1";
			DelLandQuestMark(npchar);
		break;
		
		case "lecrua_1":
			iTemp = FindColony("Baster");
			rColony = GetColonyByIndex(iTemp);
			bOk = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			dialog.text = "Tak, tak. Mój drogi przyjaciel Fadey opisał cię i twoją sytuację szczegółowo. Wiedziałem, że to ty, jak tylko zobaczyłem cię w drzwiach. Powiedz mi, kapitanie, jaki masz statek?";
			if(sti(pchar.ship.type) == SHIP_NOTUSED || !bOk)
			{
				link.l1 = "Ach...Nie mam w tej chwili statku, monsieur...";
				link.l1.go = "lecrua_noship";
			}
			else
			{
				link.l1 = "Mam "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(RealShips[sti(pchar.ship.type)].basetype),"Imię")))+", jej imię to "+pchar.ship.name+".";
				if (6-sti(RealShips[sti(pchar.ship.type)].Class) < 0) link.l1.go = "lecrua_badship";
				else link.l1.go = "lecrua_2";
			}
		break;
		
		case "lecrua_noship":
			dialog.text = "Ha! Cóż to za kapitan z ciebie, skoro nie masz statku? Przykro mi, monsieur, ale w takim wypadku nie mam dla ciebie żadnej pracy. Wszystkiego najlepszego, przekaż moje pozdrowienia Fadeyowi!";
			link.l1 = "Hm...";
			link.l1.go = "lecrua_exit";
			sTotalTemp = "I don't have a ship at the moment";
		break;
		
		case "lecrua_badship":
			dialog.text = "Cóż, to po prostu nie wystarczy. To nie jest statek, proszę pana, to łódź! Niestety, monsieur, nie pasujesz do tej roli. Pozdrów ode mnie Fadeja, dobrego dnia!";
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
			dialog.text = "Ty i ja już wszystko omówiliśmy, monsieur. Czyż nie?";
			link.l1 = "Oui, Monsieur LeCroix... Już idę.";
			link.l1.go = "exit";
			NextDiag.TempNode = "lecrua_repeat";
		break;
		
		case "lecrua_2":
			dialog.text = "Znakomicie. W takim razie doskonale do mnie pasujesz. Jesteś gotów od razu wyruszyć na morze?";
			link.l1 = "Tak, monsieur, jestem gotów. Co mam zrobić?";
			link.l1.go = "lecrua_3";
		break;
		
		case "lecrua_3":
			sld = characterFromId("BasTer_trader");
			dialog.text = "Musisz dostarczyć małą partię prochu i bomb do Port-au-Prince, na francuską Hispaniolę. Komendant czeka na to już od jakiegoś czasu, więc nie trać czasu, masz około dziesięć dni\nSzanowny "+GetFullName(sld)+" zajmie się dostarczeniem i załadunkiem na twój statek. Komendant zapłaci ci za to pięć tysięcy sztuk srebra.";
			link.l1 = "I to cała robota?";
			link.l1.go = "lecrua_4";
		break;
		
		case "lecrua_4":
			dialog.text = "O, w żadnym razie, monsieur. Komendant wyjaśni ci prawdziwe zadanie, kiedy przyniesiesz amunicję. Ten ładunek to tylko mała przystawka do pracy, która cię czeka. Ale nie obawiaj się, jeśli dobrze wykonasz zadanie, zarobisz poważne pieniądze.";
			link.l1 = "Masz moją niepodzielną uwagę, monsieur. Mój statek jest gotów przyjąć ładunek na pokład.";
			link.l1.go = "lecrua_5";
		break;
		
		case "lecrua_5":
			dialog.text = "Nie traćmy więc czasu, kapitanie! Udaj się na swój statek i przygotuj do wypłynięcia.";
			link.l1 = "Idę!";
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
			else NewGameTip("Exploration mode: timer is disabled.");
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
			dialog.text = "Jak mogę pomóc, panie?";
			link.l1 = "Dzień dobry, kapitanie. Jesteś Florian Shoke, jak mniemam?";
			link.l1.go = "florian_deck_1";
		break;
		
		case "florian_deck_1":
			dialog.text = "Ja. A ty jesteś statkiem pocztowym z Port-au-Prince, jeśli się nie mylę?";
			link.l1 = "Aj, mam dla ciebie piętnaście dział. Termin był niemal nieuchronny, ledwo zdążyłem...";
			link.l1.go = "florian_deck_2";
		break;
		
		case "florian_deck_2":
			if (GetSquadronGoods(pchar, GOOD_CANNON_24) < 15)
			{
				dialog.text = "Hm. Dziwne poczucie humoru, panie! Z jakiegoś powodu nie widzę, żeby z twojego statku wyładowywano piętnaście dział...";
				link.l1 = "Cóż, widzisz, mieliśmy przeciek i musieliśmy wyrzucić część ładunku za burtę...";
				link.l1.go = "florian_deck_fail";
			}
			else
			{
				dialog.text = "Miło cię widzieć, kapitanie?..";
				link.l1 = ""+GetFullName(pchar)+". Kapitanie "+GetFullName(pchar)+".";
				link.l1.go = "florian_deck_3";
			}
		break;
		
		case "florian_deck_3":
			dialog.text = "Miło cię poznać. Nie traćmy czasu i ładujmy te działa na pokład. To nie będzie łatwe, więc będę potrzebował pomocy twoich ludzi.";
			link.l1 = "Dam radę. Ty tam, ustaw bloczek i takelunek na rei!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Trial_TakeCannons");
		break;
		
		case "florian_deck_fail":
			dialog.text = "Ty cholerny idioto! Jeśli nie potrafisz poradzić sobie z tym prostym zadaniem, na pewno zatoniesz w następnym sztormie. Wróć na swój statek, kapitanie, i zajmij się czymś, w czym jesteś lepszy, jak dostarczaniem kwiatów szlachetnym damom. A najlepiej, wróć do Europy i zostaw Nowy Świat prawdziwym mężczyznom. Dzień dobry, panie!";
			link.l1 = "Ale...";
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
			dialog.text = "Uf, to była ciężka robota, która zżerała gardło! Dziękuję za usługę, kapitanie! Weź swoją nagrodę, dwieście doblonów.";
			link.l1 = "Dziękuję!";
			link.l1.go = "florian_deck_5";
		break;
		
		case "florian_deck_5":
			TakeNItems(pchar, "gold_dublon", 200);
			Log_Info("You've received 200 doubloons.");
			PlaySound("interface\important_item.wav");
			dialog.text = "Ale to nie wszystko, kapitanie. Chciałbyś zarobić jeszcze dwieście pięćdziesiąt złotych podwójnych escudos?";
			link.l1 = "Brzmi obiecująco, ale wszystko zależy od tego, co mnie pan o to poprosi, sir.";
			link.l1.go = "florian_deck_6";
		break;
		
		case "florian_deck_6":
			dialog.text = "Nie będę kłamać, to niebezpieczne. Jak już pewnie wiesz, czyham na hiszpański ciężki galeon z cennym ładunkiem. Statek został umieszczony w doku na naprawę. Według moich źródeł, miał wypłynąć wczoraj, ale to się nie stało\nPoza tym, mój agent w Portobello nie dotarł na miejsce spotkania, aby dostarczyć aktualizacje, na które czekam. Podejrzewam, że Hiszpanie go aresztowali. Zapłacę ci, abyś zakradł się do Portobello i dowiedział się dwóch rzeczy: dlaczego galeon wciąż tam jest i co się stało z moim agentem. Zgadzasz się?";
			link.l1 = "Obawiam się, że brakuje mi odpowiedniego przeszkolenia do takiej operacji. Jestem dżentelmenem, nie szpiegiem. Mogę sam wpaść w kłopoty i nie będę w stanie ci pomóc.";
			link.l1.go = "florian_deck_bye";
			link.l2 = "Wydaje się niebezpieczne, ale opłacalne. Zaryzykuję. Jak się nazywa twój człowiek i jak nazywa się galeon?";
			link.l2.go = "florian_deck_7";
		break;
		
		case "florian_deck_bye":
			dialog.text = "Czyżbyś nie był uprawniony? Rozumiem cię. Żegnaj zatem, kapitanie, jeszcze raz dziękuję za pomoc!";
			link.l1 = "Wszystkiego najlepszego, Monsieur Shoke.";
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
			dialog.text = "Słuchaj no uważnie. Mój człowiek nazywa się Sylvan Laforet, ale w Portobello znany jest jako Jaime Silicio, kupiec. Galeon nazywa się 'Alacantara'. Radzę ci przejść przez bramy miasta nocą, przez dżunglę. Strażnicy Portobello są teraz bardzo podejrzliwi, nie wspominając już o tym, że zniknięcie Sylvana nie wróży mu dobrze, jeśli chodzi o jego stan żywy i zdrowy. Masz dwa dni, zanim będę musiał się stąd wynieść, zanim hiszpańskie patrole nas znajdą. Powodzenia, monsieur!";
			link.l1 = "Do zobaczenia wkrótce, Monsieur Shoke...";
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
			else NewGameTip("Exploration mode: timer is disabled.");
			// <-- legendary edition
			//Log_Info("You have received amulet 'Gypsy's fan'");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "obereg_4");
			pchar.quest.NewGameTip5.win_condition.l1 = "location";
			pchar.quest.NewGameTip5.win_condition.l1.location = "PortoBello_town";
			pchar.quest.NewGameTip5.function = "ShowNewGameTip";
			pchar.quest.NewGameTip5.text = "Guards are less suspicious when you walk at slow pace!";
			
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
			dialog.text = "Omówiliśmy wszystko, kapitanie, prawda?";
			link.l1 = "Tak. Właśnie idę.";
			link.l1.go = "exit";
			NextDiag.TempNode = "florian_deck_repeat";
		break;
		
		case "florian_failspy":
			pchar.quest.trial_spy_over.over = "yes"; //снять прерывание
			dialog.text = "Jak się sprawy mają, kapitanie? Co udało ci się dowiedzieć?";
			link.l1 = "Sprawy idą źle, Monsieur Shoke. Nie jestem dobrym szpiegiem, szybko mnie odkryli. Musiałem uciekać z miasta po walce z kilkoma strażnikami. Jedyną rzeczą, którą udało mi się odkryć, jest to, że wasz człowiek Sylvan Laforet został aresztowany i trzymany jest w więzieniu.";
			link.l1.go = "florian_failspy_1";
		break;
		
		case "florian_failspy_1":
			dialog.text = "Do cholery! To niedobrze... Czy dowiedziałeś się czegoś o galeonie?";
			link.l1 = "Nie, nie zrobiłem tego.";
			link.l1.go = "florian_failspy_2";
		break;
		
		case "florian_failspy_2":
			dialog.text = "Do diabła. Naprawdę potrzebuję informacji na ten temat. Ale ta zdobycz jest zbyt tłusta, by z niej zrezygnować! W każdym razie spróbuję wysłać tam kolejnego zwiadowcę... Kapitanie, proszę, nie opuszczaj mnie jeszcze. Mogę potrzebować twojej pomocy. Czy poczekasz do jutra, podczas gdy ja będę węszył informacje o Alacantarze?";
			link.l1 = "Oczywiście, poczekam! Chciałbym nadrobić tę porażkę.";
			link.l1.go = "florian_9";
			link.l2 = "Nie sądzę. Najwyraźniej jestem zbyt kiepski w te gry. Wracam do domu.";
			link.l2.go = "florian_failspy_3";
		break;
		
		case "florian_failspy_3":
			dialog.text = "Cóż, to twój wybór. Wszystkiego najlepszego, kapitanie.";
			link.l1 = "Żegnaj, Monsieur Shoke.";
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
			dialog.text = "Jak się mają sprawy, kapitanie? Co udało ci się dowiedzieć?";
			link.l1 = "Sprawy mają się kiepsko, Monsieur Shoke. Nie jestem dobrym szpiegiem, szybko mnie odkryli. Jedyne, co udało mi się odkryć, to że twój człowiek, Sylvan Laforet został aresztowany i jest gdzieś przetrzymywany.";
			link.l1.go = "florian_failspy_1";
		break;
		
		case "florian_9":
			dialog.text = "Zatem ruszaj na swój statek, kapitanie. Jutro o tej samej porze, albo trochę później, będziesz musiał mnie odwiedzić. Może do tego czasu coś się dowiem. Nie schodź na ląd, czekaj na mnie na swoim statku!";
			link.l1 = "Dobrze. Zrobię to.";
			link.l1.go = "florian_10";
		break;
		
		case "florian_10":
			dialog.text = "A kapitanie, weź tę sakiewkę. Twoje wysiłki nie poszły całkiem na marne. Przynajmniej wiemy, co się stało z biednym starym Sylvanem...";
			link.l1 = "I'm looking for my brother. Have you seen him?";
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
			Log_Info("You've received a purse of doubloons");
		break;
		
		case "florian_deck_wait":
			dialog.text = "Kapitanie, nie mam żadnych wieści w tej chwili. Nadal czekamy...";
			link.l1 = "Dobrze...";
			link.l1.go = "exit";
			NextDiag.TempNode = "florian_deck_wait";
		break;
		
		case "florian_12":
			pchar.quest.trial_spy_over.over = "yes"; //снять прерывание
			dialog.text = "Jak idą sprawy, kapitanie? Czego zdołałeś się dowiedzieć?";
			link.l1 = "To zrobione. Twój człowiek, Sylvan Laforet, został aresztowany i jest przetrzymywany w więzieniu. To koniec dla niego.";
			link.l1.go = "florian_13";
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("PortoBello_Town", "reload", "gate_back");
			QuestPointerDelLoc("PortoBello_ExitTown", "reload", "reload1_back");
			QuestPointerDelLoc("PortoBello_Jungle_01", "reload", "reload2_back");
			QuestPointerDelLoc("PortoBello_Jungle_02", "reload", "reload3_back");
			QuestPointerDelLoc("shore47", "reload", "boat");
		break;
		
		case "florian_13":
			dialog.text = "Do diabła! To straszne... Dowiedziałeś się czegoś o galeonie?";
			link.l1 = "Tak.  Ona jest przygotowywana do wypłynięcia już od pewnego czasu, ale gubernator Portobello zamierza ją zatrzymać przy nabrzeżu. Teraz czeka na barkentine o nazwie 'Puebla', która ma przybyć z Kartageny z ładunkiem prochu dla 'Alcantary'. Według marynarza z galeonu nie mają jej wystarczająco, a gubernator obawia się piratów.";
			link.l1.go = "florian_14";
		break;
		
		case "florian_14":
			dialog.text = "Jakże interesujące!";
			link.l1 = " Lecz jeśli Puebla nie przybędzie w ciągu trzech dni, to Alacantara przestanie czekać i wyruszy w morze.";
			link.l1.go = "florian_15";
		break;
		
		case "florian_15":
			dialog.text = "Doskonale wykonana robota, Kapitanie "+GetFullName(pchar)+"! Jestem bardzo zadowolony! Oto twoja nagroda. W pełni na nią zasłużyłeś!";
			link.l1 = "Dziękuję! Czy masz dla mnie jakieś inne zadania?";
			link.l1.go = "florian_16";
		break;
		
		case "florian_16":
			TakeNItems(pchar, "gold_dublon", 250);
			Log_Info("You've received 250 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Czytasz w moich myślach, "+GetFullName(pchar)+"Tak, do diabła! Skoro Alacantara ma mało prochu, mogę pozwolić jej wypłynąć na otwarte morze, a potem zmusić ją do długotrwałej bitwy morskiej, w której ich proch skończy się przed naszym, haha!\nMusisz upewnić się, że barkentini zaopatrzeniowy Puebla nigdy nie dotrze do Portobello. Nie mogę żeglować blisko brzegu, patrole łatwo zauważą mój fregat i odpędzą mnie, zanim przechwycę Alacantarę\nMożesz zająć się Pueblą samodzielnie. Znajdź ją i pozbądź się jej. Zatop ją lub weź jako nagrodę, nie obchodzi mnie to. Po prostu powstrzymaj ją przed dotarciem tutaj!\nJeśli ci się uda, udaj się na Gwadelupę i zobacz się z Gerardem LeCroix, wierzę, że już go znasz, prawda? On zapłaci ci monety, na które zasługujesz.";
			link.l1 = "Umowa stoi! Wyruszam, by odciąć Pueblę!";
			link.l1.go = "florian_19";
			link.l2 = "Poczekaj chwilę, Monsieur Choquet. Rzecz w tym, że ja wciąż... Powiedzmy, że nie jestem szczególnie przyzwyczajony do morskich bitew. A ty jesteś kapitanem fregaty, masz za sobą z pewnością więcej niż jedną morską bitwę. Jeśli to nie problem, mógłbyś... Jakby to ująć...";
			link.l2.go = "florian_guide_01";
		break;
		
		case "florian_17":
			dialog.text = "Cieszę się, że jesteś tutaj, kapitanie. Właśnie otrzymałem informacje od mojego szpiega i mam dla ciebie ważną misję.";
			link.l1 = "Zamieniam się w słuch.";
			link.l1.go = "florian_18";
		break;
		
		case "florian_18":
			dialog.text = "Alacantara jest gotowa do wypłynięcia, ale kapitan galeonu czeka na przybycie barkentini 'Puebla' z Kartageny załadowanej amunicją. Najwyraźniej Alacantara nie ma wystarczającej ilości prochu, więc Hiszpanie nie są jeszcze gotowi do wypłynięcia. Ale cierpliwość kapitana ma swoje granice i jeśli Puebla nie przybędzie w ciągu trzech dni, to galeon opuści Portobello bez niej\nAlacantara ma mało prochu, mogę pozwolić jej wypłynąć na otwarte morze, a następnie zmusić ją do długotrwałej walki morskiej, w której ich proch skończy się przed naszym. Twoim celem jest przechwycenie Puebli i jej zniszczenie. Zatop ją lub zdobądź jako łup, nie obchodzi mnie to. Po prostu uniemożliw tej barkentini zaopatrzeniowej dotarcie tutaj!\nJeśli ci się uda, udaj się na Guadeloupe i odwiedź Gerarda LeCroix, wierzę, że już go znasz, prawda? On zapłaci ci zasłużone monety.";
			link.l1 = "Umowa stoi! Wyruszam, by odciąć Pueblę!";
			link.l1.go = "florian_19";
			link.l2 = "Poczekaj chwilę, Monsieur Choquet. Rzecz w tym, że ja jeszcze... Powiedzmy, nie jestem szczególnie przyzwyczajony do morskich bitew. A ty jesteś kapitanem fregaty, masz za sobą oczywiście więcej niż jedną bitwę morską. Jeśli to nie sprawi ci trudności, mógłbyś... Jak by to ująć...";
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
			dialog.text = "Chciałbyś, żebym dał ci lekcję taktyki walki morskiej? Z przyjemnością, kapitanie! Zwłaszcza, że leży to w moim własnym interesie: chcę mieć pewność, że skutecznie przechwycisz 'Pueblę'.";
			link.l1 = "Nie, nie to miałem na myśli. Dobrze, zapomnij o tym: jestem pewien, że nie będę miał żadnych problemów z przechwyceniem barkentini.";
			link.l1.go = "florian_19";
			link.l2 = "Tak, właśnie to miałem na myśli. Jestem pewien, że nowa wiedza mi nie zaszkodzi.";
			link.l2.go = "florian_guide_02";
		break;
		
		case "florian_guide_02":
			dialog.text = "Więc pierwsza rzecz, którą musisz zapamiętać, to że połowa bitwy jest wygrana lub przegrana zanim się w ogóle zacznie. Wiele zależy od tego, jak bardzo ty i twój statek jesteście na nią gotowi.";
			link.l1 = "...";
			link.l1.go = "florian_guide_03";
		break;
		
		case "florian_guide_03":
			dialog.text = "Najpierw upewnij się, że twój statek jest naprawiony. Jeśli masz dziury w kadłubie, to wróg z łatwością pośle cię na dno. A jeśli zamiast żagli masz łachmany, to znacznie ogranicza twoją mobilność. Wróg może łatwo cię zostawić w tyle, jeśli równowaga sił nie jest na jego korzyść, lub co gorsza, dogonić cię i narzucić ci niekorzystną bitwę - albo od razu cię abordażować. Co więcej, z podartymi żaglami będziesz miał trudności z osiągnięciem przewagi nawietrznej, czyli dostaniem się na wiatr przeciwnika, gdzie chcesz się znaleźć.";
			link.l1 = "Przewaga nawietrzna, zrozumiałem. Coś jeszcze?";
			link.l1.go = "florian_guide_04";
		break;
		
		case "florian_guide_04":
			dialog.text = "Upewnij się, że masz wystarczająco ludzi. Nawet najpotężniejszy statek z 42-funtowymi działami staje się bezużyteczny, jeśli masz jednego artylerzystę biegnącego, by przeładować trzy działa i po prostu nie ma nikogo, kto kontrolowałby żagle. Ogólnie rzecz biorąc, po prostu natychmiast wszedłbym na taki statek i przejął go.";
			link.l1 = "Dostatecznie ludzi, rozumiem.";
			link.l1.go = "florian_guide_05";
		break;
		
		case "florian_guide_05":
			dialog.text = "Również, uważaj na swoje działa: z czasem się zużywają i wybuchają. Z czasem stan luf pogarsza się, a jeśli twoje działa zaczną wybuchać w trakcie bitwy, może to bardzo źle się skończyć dla ciebie. Nie miałem w ogóle szczęścia: partia dział, z którymi płynąłem, okazała się mieć kilka wad odlewniczych. Gdybyś nie dostarczył zamienników na czas, po prostu zrezygnowałbym z operacji, ponieważ Militarny byłby znacznie słabszy od Alcantary pod względem siły ognia. Narzędzia trzeba wymieniać na czas.";
			link.l1 = "Teraz rozumiem, dlaczego to było tak ważne!";
			link.l1.go = "florian_guide_06";
		break;
		
		case "florian_guide_06":
			dialog.text = "Oprócz dział, zwracaj także uwagę na ilość amunicji. Alcantara przypadnie mi z tego powodu. Jeśli ma niskie zapasy prochu, nie będzie w stanie stoczyć długiej bitwy - musi natychmiast przejść do walki wręcz. A ja na tym zagram: mój fregat jest szybszy, ciężki galeon nie będzie w stanie się od niego oddalić. Ale ja również nie muszę się zbliżać: narzucę pojedynek artyleryjski na dalekim zasięgu, a potem, gdy proch na Alcantarze się skończy, zamknę, ostrzelam ją kartaczami i zaatakuję na pokładzie.";
			link.l1 = "Desperacka sytuacja...";
			link.l1.go = "florian_guide_07";
		break;
		
		case "florian_guide_07":
			dialog.text = "Dokładnie. Miej oko na swój proch i amunicję. Jeśli skończą ci się pełne kule - najprawdopodobniej nie będziesz w stanie zatopić wrogiego statku. Jeśli skończą ci się kartacze, nie masz co liczyć na abordaż, jeśli masz przewagę liczebną. Jeśli nie masz łańcuchowych kul lub knippli, nie będziesz w stanie dogonić wroga ani uciec od niego, jeśli jest szybszy. Wszystkie rodzaje amunicji są ważne.";
			link.l1 = "Pouczające, dzięki.";
			link.l1.go = "florian_guide_08";
		break;
		
		case "florian_guide_08":
			dialog.text = "I wreszcie, w zależności od typu i rozmiaru twojego statku oraz statku wroga, użyj odpowiedniej taktyki. Na morzu trzeba wybierać między siłą ognia a szybkością. Na dużym i wolnym statku nie ma sensu gonić brygu lub korwety, aby ją abordażować - i tak jej nie dogonisz, jeśli wcześniej nie osłabisz jej ogniem łańcuchowym. W takich przypadkach lepiej jest rozbić ją z dystansu i przeszukać wrak. Jeśli nadal musisz abordażować taki statek, lepiej jest użyć szybkiego i zwrotnego okrętu.";
			link.l1 = "... ";
			link.l1.go = "florian_guide_09";
		break;
		
		case "florian_guide_09":
			dialog.text = "Jednocześnie nie idź na czołowe starcie z okrętem liniowym mając tylko brygantynę. Jedna salwa z takiego monstrum zetrze kadłuby mniejszych statków na drzazgi. Wykorzystaj swoją przewagę w szybkości i zwrotności, strąć jej maszty i takielunek, a potem zbliż się i obsyp pokład kartaczem, jeśli nadal musisz ją abordażować. Jeśli musisz ją zatopić... nie będzie to łatwe zadanie, ale możliwe. Możesz dokonać abordażu, a potem wysadzić jej komorę prochową, ale nigdy nie jest wstydem uciekać. Dobry kapitan ocali swój statek i załogę przed pewną śmiercią zamiast nadmiernego bohaterstwa. Pamiętaj, że rozwaga i ostrożność często są lepszą częścią odwagi.";
			link.l1 = "Dziękuję bardzo, Monsieur Choquet!";
			link.l1.go = "florian_guide_10";
		break;
		
		case "florian_guide_10":
			AddCharacterSkillDontClearExp(pchar, SKILL_CANNONS, 1);
			AddCharacterSkillDontClearExp(pchar, SKILL_ACCURACY, 1);
			//Log_info(XI_ConvertString("Experience Bonus")+": +1 "+XI_ConvertString(SKILL_CANNONS));
			notification(XI_ConvertString("Experience Bonus")+": +1 ", SKILL_CANNONS);
			//Log_info(XI_ConvertString("Experience Bonus")+": +1 "+XI_ConvertString(SKILL_ACCURACY));
			notification(XI_ConvertString("Experience Bonus")+": +1 ",SKILL_ACCURACY);
			dialog.text = "Z przyjemnością pomogę kapitanie. Mam nadzieję, że ta wiedza przyda się wam w przyszłości.";
			link.l1 = "Jestem pewien, że to pomoże. Ruszamy przechwycić 'Pueblę!'";
			link.l1.go = "florian_19";
		break;
		// <-- legendary edition дополнительное обучение

		// испанский офицер в таверне
		case "tavern_officer":
			dialog.text = "To niezwykły akcent, señor. A może powinienem powiedzieć 'monsieur'? Chcesz zobaczyć Jaime Silicio? Może podzielicie tę samą celę. Zabrać go, chłopcy!";
			link.l1 = "Cóż, jeśli nie podoba ci się mój akcent, być może mogę cię zapoznać z francuską szermierką!";
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

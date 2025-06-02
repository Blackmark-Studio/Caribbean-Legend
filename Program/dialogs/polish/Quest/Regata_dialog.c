void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n, iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	bool ok;
    int iTest;
    ref rColony;
    string sFrom_sea = "";
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		//вестовой
		case "Regata_Cureer":
			dialog.text = "Dzień dobry. Czy jesteś kapitanem "+GetFullName(pchar)+"?";
			link.l1 = "Tak, to ja. I o co chodzi?";
			link.l1.go = "Regata_Cureer_1";
		break;
		
		case "Regata_Cureer_1":
			dialog.text = "Mam dla ciebie list od gubernatora Jamajki, pana Edwarda Doily'ego.";
			link.l1 = "O rany! Nie spodziewałem się tego... Czego ode mnie chce gubernator?";
			link.l1.go = "Regata_Cureer_2";
		break;
		
		case "Regata_Cureer_2":
			dialog.text = "Przeczytaj list, panie. W skrócie, zaproponowano ci udział w regatach, wyścigu przez całe archipelag. Plotki o twoich umiejętnościach morskich i niezwykłej szybkości żeglugi nie przeszły niezauważone.";
			link.l1 = "Niesamowite! Cóż, ja... ja to rozważę.";
			link.l1.go = "Regata_Cureer_3";
			GiveItem2Character(pchar, "letter_open");
			ChangeItemDescribe("letter_open", "itmdescr_letter_open_Regata");
			AddQuestRecordInfo("RegataLetter", "1");
		break;
		
		case "Regata_Cureer_3":
			if (Pchar.BaseNation == SPAIN || Pchar.BaseNation == HOLLAND)
			{
				dialog.text = "Również mam zapewnić ci swobodny dostęp do portu w Port Royal. Oto licencja na 30 dni. Teraz moja misja jest zakończona. Żegnaj, kapitanie.";
				link.l1 = "Dzięki. Licencja jest bardzo mile widziana. Żegnaj!";
				link.l1.go = "Cureer_exit";
				GiveNationLicence(HOLLAND, 30);
			}
			else
			{
				dialog.text = "Dobrze. Teraz moja misja jest zakończona. Żegnaj, kapitanie.";
				link.l1 = "Żegnaj!";
				link.l1.go = "Cureer_exit";
			}
		break;
		
		case "Cureer_exit":
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
			pchar.questTemp.Regata.ToPortRoyal = "true";
			SetQuestHeader("Regata");
			AddQuestRecord("Regata", "1");
		break;
		
		//распорядитель регаты
		case "Regata_Head":
			if (CheckAttribute(pchar, "questTemp.Regata.Begin"))
			{
				dialog.text = "Dzień dobry. Biorzysz udział w regatach, jak mniemam?";
				link.l1 = "Dokładnie, sir. Nazywam się "+GetFullName(pchar)+" . Otrzymałem zaproszenie.";
				link.l1.go = "Regata_Head_1";
			}
			else
			{
				dialog.text = "Chcesz czegoś, panie?";
				link.l1 = "Nie, to nic. Już odchodzę.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Regata_Head";
			}
		break;
		
		case "Regata_Head_1":
			iTest = FindColony("PortRoyal"); 
			if (iTest != -1)
			{
				rColony = GetColonyByIndex(iTest);
			}
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
			{
				dialog.text = "Jestem rad, że cię spotykam, kapitanie "+GetFullName(pchar)+"  Zaczynajmy więc. Już wiesz co nieco z listu, prawda? Tylko lugry, i ona musi być jedynym statkiem w twojej eskadrze, aby wziąć udział w regacie. Czy spełniłeś te wymagania?";
				// belamour legendary edition допускаем курьерский люггер 
				ok = sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_LUGGER || sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_CAREERLUGGER;
				if((GetCompanionQuantity(pchar) > 1) || !ok)
				{
					link.l1 = "Jeszcze nie. Zrobię to teraz i wkrótce wrócę.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Regata_Head_repeat";
				}
				else
				{
					link.l1 = "Tak, mam.";
					link.l1.go = "Regata_Head_2";
				}
			}
			else
			{
				dialog.text = "Przybyłeś, aby wziąć udział w regatach, ale gdzie jest twój statek, kapitanie?";
				link.l1 = "Przepraszam, panie. Natychmiast sprowadzę mój statek do portu.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Regata_Head_repeat";
			}
		break;
		
		case "Regata_Head_repeat":
			if (CheckAttribute(pchar, "questTemp.Regata.Begin"))
			{
				iTest = FindColony("PortRoyal"); 
				if (iTest != -1)
				{
					rColony = GetColonyByIndex(iTest);
				}
				ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
				if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
				{
					ok = sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_LUGGER || sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_CAREERLUGGER;
					dialog.text = "Ach, to znowu ty. Czy dopełniłeś wszystkiego, aby spełnić wymagania do regat?";
					// belamour legendary edition допускаем курьерский люггер 
					if ((GetCompanionQuantity(pchar) > 1) || !ok)
					{
						link.l1 = "Jeszcze nie. Zrobię to teraz i wkrótce wrócę.";
						link.l1.go = "exit";
						NextDiag.TempNode = "Regata_Head_repeat";
					}
					else
					{
						link.l1 = "Tak, mam.";
						link.l1.go = "Regata_Head_2";
					}
				}
				else
				{
					dialog.text = "Kapitanie, nie mamy o czym rozmawiać, dopóki nie zobaczę twojego statku na redzie. Rozumiesz mnie, czy mam się powtórzyć?";
					link.l1 = "Przepraszam, panie. Natychmiast sprowadzę mój statek do portu.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Regata_Head_repeat";
				}
			}
			else
			{
				dialog.text = "Czegoś Pan sobie życzy?";
				link.l1 = "Nie... to nic. Już odchodzę.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Regata_Head";
			}
		break;
		
		case "Regata_Head_2":
			dialog.text = "Dobrze. Teraz kolejny punkt. Jak się nazywa twój statek?";
			link.l1 = "'"+pchar.Ship.Name+" '.";
			link.l1.go = "Regata_Head_3";
		break;
		
		case "Regata_Head_3":
			dialog.text = "W związku z tym, że regatę organizują angielskie władze i zgodnie z ustalonymi zasadami, nazwa twojego statku musi zostać zmieniona na czas wydarzenia. Nie martw się, dotyczy to każdego uczestnika.";
			link.l1 = "Mówią, że to zła wróżba, jeśli zmienisz nazwę swojego statku.";
			link.l1.go = "Regata_Head_4";
		break;
		
		case "Regata_Head_4":
			dialog.text = "Możesz zmienić nazwę z powrotem po regatach. A więc twój lugger będzie nosił nazwę 'Święta Katarzyna'.";
			link.l1 = "Rozumiem to, panie, zmienię nazwę.";
			link.l1.go = "Regata_Head_5";
			pchar.Ship.Name = "Saint Catherine";
		break;
		
		case "Regata_Head_5":
			dialog.text = "Teraz porozmawiajmy o samej regacie. Słuchaj uważnie. Otrzymasz również regulamin.\nRegata zaczyna się i kończy w Port Royal. Jest pięć punktów, które musisz osiągnąć\nPierwszy to Port Royal do Belize, West Main\nDrugi to Belize do Port-au-Prince, Hispaniola\nTrzeci to Port-au-Prince do St.John's, Antigua\nCzwarty to St.John's do Bridgetown, Barbados\nA ostatni to Bridgetown do Port Royal\nCzy wszystko jasne?";
			link.l1 = "Krystalicznie jasno, panie.";
			link.l1.go = "Regata_Head_6";
		break;
		
		case "Regata_Head_6":
			dialog.text = "Wspaniale. Musisz zameldować się w każdym biurze portowym w następujących miastach: Belize, Port-au-Prince, St.John's, Bridgetown. Zostaniesz zdyskwalifikowany, jeśli pominiesz któreś z tych miast lub złamiesz właściwą kolejność.\nBiura będą otwarte dwadzieścia cztery godziny na dobę podczas trwania regaty. Zapukaj do drzwi, a oni cię wpuszczą.";
			link.l1 = "Zrozumiano.";
			link.l1.go = "Regata_Head_7";
		break;
		
		case "Regata_Head_7":
			dialog.text = "Zabrania się zmiany statku i dodawania więcej statków do twojej eskadry. To będzie weryfikowane w każdym mieście, weź to pod uwagę.";
			link.l1 = "Zastanowię się nad tym. Kogo zwykle uznaje się za zwycięzcę i czy możemy porozmawiać o nagrodach?";
			link.l1.go = "Regata_Head_8";
		break;
		
		case "Regata_Head_8":
			dialog.text = "Regaty mają tylko jednego zwycięzcę - kapitana, którego statek jako pierwszy dotrze do Port-Royal. Nagroda jest bardzo cenna. Zwycięzca otrzyma dużą sumę - 250 000 pesos. Dodatkowo, zostanie obdarowany zestawem cennych upominków.";
			link.l1 = "Więc przegrani nic nie dostają?";
			link.l1.go = "Regata_Head_9";
		break;
		
		case "Regata_Head_9":
			dialog.text = "Dokładnie. Do tego wielu bogatych i biednych obywateli angielskich kolonii stawia zakłady na zwycięzcę regat. Możesz również postawić na... siebie. Normalnie każdy kapitan tak robi. Jeśli wygrasz, zarobisz jeszcze więcej i nie zapomnij o motywacji. Zwykle przyjmuję zakłady.\nStawiasz na swoje zwycięstwo?";
			link.l1 = "Ha! Oczywiście, że jestem. Ile mogę postawić?";
			link.l1.go = "Regata_rate";
			link.l2 = "Pomyślę o tym. Może postawię.";
			link.l2.go = "Regata_Head_10";
		break;
		
		case "Regata_Head_10":
			if (CheckAttribute(pchar, "questTemp.Regata.Begin"))
			{
				dialog.text = "Zastanów się, jeśli chcesz. Masz trochę czasu, zanim regaty się rozpoczną.";
				link.l1 = "Dobrze. Kiedy się zaczyna?";
				link.l1.go = "Regata_Head_11";
				DeleteAttribute(pchar, "questTemp.Regata.Rate");
				pchar.questTemp.Regata.Ratenext = "true";
			}
			else
			{
				dialog.text = "Pomyśl, jeśli chcesz. Masz trochę czasu, zanim zacznie się regaty.";
				link.l1 = "Dobrze.";
				link.l1.go = "exit";
			}
		break;
		
		case "Regata_Head_11":
			CreateRegataAdversaries();
			dialog.text = "W ciągu trzech dni, o godzinie dwunastej, w południe. Przyjdź na molo i nie spóźnij się. Będziesz miał pięciu konkurentów.\n"+pchar.questTemp.Regata.AdversaryName.a+", z "+pchar.questTemp.Regata.AdversaryShipName.a+"\n"+pchar.questTemp.Regata.AdversaryName.b+", z "+pchar.questTemp.Regata.AdversaryShipName.b+"\n"+pchar.questTemp.Regata.AdversaryName.c+", z "+pchar.questTemp.Regata.AdversaryShipName.c+"\n"+pchar.questTemp.Regata.AdversaryName.d+", z "+pchar.questTemp.Regata.AdversaryShipName.d+"\n"+pchar.questTemp.Regata.AdversaryName.e+", z "+pchar.questTemp.Regata.AdversaryShipName.e+"\nWszyscy oni to doświadczeni kapitanowie. Cóż, najwyraźniej to wszystko. Weź papier z zasadami na wszelki wypadek. Do zobaczenia na starcie!";
			link.l1 = "Żegnaj, panie.";
			if (Pchar.BaseNation == SPAIN || Pchar.BaseNation == HOLLAND) link.l1.go = "Regata_Head_13";
			else link.l1.go = "Regata_Head_12";
		break;
		
		case "Regata_Head_12":
			DialogExit();
			pchar.quest.RegataToPortRoyalTimeOver.over = "yes";//снять таймер
			SetFunctionTimerCondition("Regata_SetTime", 0, 0, 3, false);
			pchar.quest.Regata_Lost.win_condition.l1 = "Timer";
			pchar.quest.Regata_Lost.win_condition.l1.date.hour  = 13.0;
			pchar.quest.Regata_Lost.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 3);
			pchar.quest.Regata_Lost.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 3);
			pchar.quest.Regata_Lost.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 3);
			pchar.quest.Regata_Lost.function = "Regata_Lost";
			pchar.quest.Regata_Start.win_condition.l1 = "Timer";
			pchar.quest.Regata_Start.win_condition.l1.date.hour  = 12.0;
			pchar.quest.Regata_Start.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 3);
			pchar.quest.Regata_Start.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 3);
			pchar.quest.Regata_Start.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 3);
			pchar.quest.Regata_Start.win_condition.l2 = "locator";
			pchar.quest.Regata_Start.win_condition.l2.location = "Portroyal_town";
			pchar.quest.Regata_Start.win_condition.l2.locator_group = "reload";
			pchar.quest.Regata_Start.win_condition.l2.locator = "reload1_back";
			pchar.quest.Regata_Start.function = "Regata_Start";
			AddQuestRecordInfo("RegataRules", "1");
			NextDiag.CurrentNode = "Regata_Prepare";
			DeleteAttribute(pchar, "questTemp.Regata.Begin");
			pchar.questTemp.Regata.Prepare = "true";
			AddQuestRecord("Regata", "2");
		break;
		
		case "Regata_Head_13":
			dialog.text = "Poczekaj! Dam ci licencję na odwiedzanie angielskich i francuskich portów na 30 dni. Regaty nie potrwają dłużej niż miesiąc. Proszę, weź ją.";
			link.l1 = "Dzięki!";
			link.l1.go = "Regata_Head_12";
			GiveNationLicence(HOLLAND, 30);
		break;
		
		case "Regata_rate":
			dialog.text = "Ile stawiasz?";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "Regata_rate_1";
			link.l2 = "Przypuszczam, że nadal potrzebuję trochę czasu na przemyślenie.";
			link.l2.go = "Regata_Head_10";
		break;
		
		case "Regata_rate_1":
			int iQty = sti(dialogEditStrings[4]);
			pchar.questTemp.Regata.Rate = sti(iQty);
			if (iQty < 10000)
			{
				dialog.text = "Panie, to nie jest śmieszne, ani trochę. Nie będę pracować za tak małą sumę.";
				link.l1 = "Przepraszam... Przemyślmy jeszcze raz stawkę.";
				link.l1.go = "Regata_rate";
				break;
			}
			if (iQty > 100000)
			{
				dialog.text = "Panie, nie mogę przyjąć takich stawek ze względu na zasady regat. Proszę je zmniejszyć do rozsądnej wartości.";
				link.l1 = "Niestety. Przemyślmy jeszcze raz tę sumę.";
				link.l1.go = "Regata_rate";
				break;
			}
			dialog.text = ""+iQty+"? To jest zacny zakład. Jestem gotów go przyjąć. Pańskie pieniądze, panie?";
			if (makeint(Pchar.money) >= sti(pchar.questTemp.Regata.Rate))
			{
				link.l1 = "Proszę, weź to.";
				link.l1.go = "Regata_rate_2";
			}
			link.l2 = "Nie mam teraz wystarczająco monet. Przyjdę do ciebie później i postawimy stawkę. I jeszcze się nad tym zastanowię, być może przemyślę kwotę.";
			link.l2.go = "Regata_Head_10";
		break;
		
		case "Regata_rate_2":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Regata.Rate));
			pchar.questTemp.Regata.Advantage = sti(pchar.questTemp.Regata.Rate)*(1.5+frand(1.5)); // dlc
			dialog.text = "Wspaniale! Teraz wszystko, co musisz zrobić, to być pierwszym, a nagroda będzie twoja. Jej ostateczna wartość może się różnić, wszystko zależy od tego, ile osób postawi na ciebie ostatecznie.";
			if (!CheckAttribute(pchar, "questTemp.Regata.Ratenext"))
			{
				link.l1 = "Rozumiem. Kiedy zaczyna się regata?";
				link.l1.go = "Regata_Head_11";
			}
			else
			{
				link.l1 = "Widzę. Będę czekał na rozpoczęcie. Do zobaczenia!";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.Regata.Ratenext");
				NextDiag.TempNode = "Regata_Prepare";
			}
		break;
		
		case "Regata_Prepare":
			dialog.text = "Ah znowu tu jesteś, kapitanie "+GetFullName(pchar)+"? Czego chcesz?";
			if (!CheckAttribute(pchar, "questTemp.Regata.Rate"))
			{
				link.l1 = "Chcę postawić na moje zwycięstwo.";
				link.l1.go = "Regata_rate";
			}
			link.l2 = "Nie, to nic. Po prostu chciałem cię przywitać.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Regata_Prepare";
		break;
		
		//старт регаты
		case "Regata_CitMan":
			dialog.text = RandPhraseSimple(LinkRandPhrase("Kapitanie, czy to wasz pierwszy raz? Pozwólcie, że powiem wam, iż powinniście być ostrożni. Wasi konkurenci mogą przygotować dla was bardzo nieprzyjemne niespodzianki...","Kapitanie, postawiłem na ciebie. Nie zawiedź mnie!","Kapitanie, miejscowi w portach regaty mogą zaproponować ci zakup czegoś. Często może to być naprawdę przydatne. Rozważ to."),LinkRandPhrase("Bezpiecznej podróży, kapitanie!","Kapitanie, proszę bądź ostrożny, Kastylijczycy często polują na lugry uczestników w hiszpańskich wodach.","Słyszałem, że niektórzy podejrzani osobnicy często oferują swoje 'usługi' kapitanom regat. To od ciebie zależy, czy przyjmiesz ich oferty, czy nie."));
			link.l1 = "Tak, tak, oczywiście... dzięki, chyba.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_CitMan";
		break;
		
		case "Regata_CitWom":
			dialog.text = LinkRandPhrase("Kapitanie, ja i mój mąż postawiliśmy dziesięć tysięcy na twoje zwycięstwo. Nie zawiedź nas! Będę się za ciebie modlić!","Kapitanie! Życzę ci szczęścia!","Uhm... jesteś takim odważnym i dzielnym kapitanem...");
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_CitWom";
		break;
		
		case "Regata_CitHorse":
			dialog.text = LinkRandPhrase("Hej, żeglarzu! Pomachaj piękności! Będę czekać na twój powrót!","Ej, słony żeglarzu! Pani powiedziała, że odda mnie jako nagrodę zwycięzcy regaty za darmo... Spróbuj wygrać, jesteś taki przystojny!","Nie zapomnij nas odwiedzić, kiedy wrócisz, przystojniaku, zaspokoimy cię według najwyższych standardów!");
			link.l1 = "Cóż, hah... Rozważę to, dziękuję!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_CitHorse";
		break;
		
		case "Regata_Prepare_1":
			if (sti(environment.time) < 12.0)
			{
				dialog.text = "Kapitanie, regata zaczyna się o 12:00. Możesz teraz odpocząć, przygotowujemy uroczystość. Wróć w południe, twoi konkurenci zrobią to samo.";
				link.l1 = "Bardzo dobrze, panie! Będę czekał na rozpoczęcie...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Oto jesteś, kapitanie.";
				link.l1 = "Ja i moja załoga jesteśmy gotowi, sir! Czekam na rozpoczęcie...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Regata_Prepare_1";
		break;
		
		case "Regata_Start":
			dialog.text = "A więc, panowie, oto jesteśmy. Ogłaszam rozpoczęcie regaty. Zasady są wam znane. Ten, kto jako pierwszy tutaj powróci, zostanie wychwalany jako zwycięzca. Panie i panowie, życzmy szczęścia naszym dzielnym kapitanom!\nPanowie! Czy jesteście gotowi? Na miejsca! Gotowi! Start!";
			link.l1 = "...";
			link.l1.go = "Regata_Start_1";
		break;
		
		case "Regata_Start_1":
			DialogExit();
			PlaySound("people fight\mushketshot.wav");
			log_info("The regatta has started! Get aboard! Head to Belize!");
			for (i=1; i <=5; i++)
			{
				sld = characterFromId("Regata_Cap_F"+i);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
			}
			Island_SetReloadEnableGlobal("Jamaica", false);//на остров нельзя
			SetFunctionTimerCondition("ReturnJamaicaNorm", 0, 0, 1, false);//таймер на возврат нормы
			LocatorReloadEnterDisable("Portroyal_town", "reload1_back", false);//откроем выход в море
			DeleteAttribute(pchar, "questTemp.Regata.Prepare");
			pchar.questTemp.Regata.Go = "true";
			pchar.questTemp.Regata.Town = "Beliz";
			pchar.quest.Regata_PU.win_condition.l1 = "locator";
			pchar.quest.Regata_PU.win_condition.l1.location = "Beliz_town";
			pchar.quest.Regata_PU.win_condition.l1.locator_group = "reload";
			pchar.quest.Regata_PU.win_condition.l1.locator = "reload10_back";
			pchar.quest.Regata_PU.win_condition.l2 = "Night";
			pchar.quest.Regata_PU.function = "RegataPU_Open";//вход в ПУ ночью
			//ситуации
			pchar.quest.Regata_ShYarder.win_condition.l1 = "location";
			pchar.quest.Regata_ShYarder.win_condition.l1.location = "Beliz_town";
			pchar.quest.Regata_ShYarder.function = "RegataShipyarder";
			sld = characterFromId("Beliz_shipyarder");
			LAi_RemoveLoginTime(sld);
			AddQuestRecord("Regata", "3");
		break;
		//старт регаты
		
		//верфист с парусами
		case "Regata_Shipyarder":
			dialog.text = "Witaj, kapitanie! Zostałem poinformowany, że bierzesz udział w regatach karaibskich.";
			link.l1 = "To prawda. Wieści rzeczywiście rozchodzą się po archipelagu szybciej niż wiatr.";
			link.l1.go = "Regata_Shipyarder_1";
		break;
		
		case "Regata_Shipyarder_1":
			dialog.text = "Owszem, kapitanie. Mam dla ciebie propozycję. Dotyczy ona twojego statku i regaty.";
			link.l1 = "Heh! Interesujące. Słucham cię, panie.";
			link.l1.go = "Regata_Shipyarder_2";
		break;
		
		case "Regata_Shipyarder_2":
			dialog.text = "Mam zestaw doskonałych żagli dla lugra, są wykonane z najlepszego bawełny. Te żagle zwiększą przyspieszenie twojego statku i dadzą ci przewagę czasową nad przeciwnikami\nJestem gotów je ci sprzedać, to znaczy, jeśli chcesz je kupić.";
			link.l1 = "Ile chcesz za te żagle?";
			link.l1.go = "Regata_Shipyarder_3";
		break;
		
		case "Regata_Shipyarder_3":
			dialog.text = "Tylko 15 000 pesos. Musisz przyznać, że to bardzo skromna cena za... sytuację taką jak ta.";
			if (makeint(Pchar.money) >= 15000)
			{
				link.l1 = "Zgadzam się. Kupuję te nowe żagle dla mojego lugra. Proszę, oto pieniądze, panie. Czy byłbyś tak uprzejmy dostarczyć je na mój statek, podczas gdy ja się zameldowuję?";
				link.l1.go = "Regata_Shipyarder_4";
			}
			link.l2 = "Nie mam takich pieniędzy. Więc nie będę mógł kupić twoich żagli.";
			link.l2.go = "Regata_Shipyarder_exit";
		break;
		
		case "Regata_Shipyarder_4":
			AddMoneyToCharacter(pchar, -15000);
			dialog.text = "To będzie zrobione, sir. Moi ludzie tylko czekają na rozkaz, i obiecuję wam, że tego nie pożałujecie. Poza tym te żagle są pięknie pomalowane na niebiesko. Wasza piękność to doceni.";
			link.l1 = "Zatem dobrze! Cóż, muszę iść, a ty zajmij się żaglami.";
			link.l1.go = "Shipyarder_exit";
			for (i=1; i <=5; i++)
			{
				if (i==1) sTemp = "a";
				if (i==2) sTemp = "b";
				if (i==3) sTemp = "c";
				if (i==4) sTemp = "d";
				if (i==5) sTemp = "e";
				pchar.questTemp.Regata.AdversarySecondTransition.Time.(sTemp) = sti(pchar.questTemp.Regata.AdversarySecondTransition.Time.(sTemp))+12;//выиграл 12 часов у всех
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversarySecondTransition.Time.(sTemp)));
			}
			RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails = 3;
			SetSailsColor(Pchar, 5);
			AddQuestRecord("Regata", "28");
		break;
		
		case "Regata_Shipyarder_exit":
			dialog.text = "Jaka szkoda. Cóż, to twój wybór. Żegnaj, kapitanie.";
			link.l1 = "Żegnaj!";
			link.l1.go = "Shipyarder_exit";
			pchar.questTemp.Regata.AdversarySecondTransition.Time.d = sti(pchar.questTemp.Regata.AdversarySecondTransition.Time.d)-16;//четвертый соперник выиграл 16 часов
			log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversarySecondTransition.Time.e));
			AddQuestRecord("Regata", "29");
		break;
		
		case "Shipyarder_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload5_back", "Beliz_Shipyard", "sit", "sit1", "ReturnRegataSYNorm", 5);
		break;
		//верфист с парусами
		
		//контрики с пушками
		case "Regata_Contra":
			dialog.text = "Cześć, kapitanie "+GetFullName(pchar)+" Musimy z tobą porozmawiać... właściwie to tylko... propozycja biznesowa.";
			link.l1 = "Hm. Interesujące i skąd wiesz, kim jestem?";
			link.l1.go = "Regata_Contra_1";
		break;
		
		case "Regata_Contra_1":
			dialog.text = "Cóż mogę powiedzieć, zawsze mówili, że jestem utalentowany... Ha-ha, cóż, Regaty są w pełnym rozkwicie, a ty bierzesz w nich udział, jesteś sławnym Kapitanem!";
			link.l1 = "Rozumiem. Cóż, mów, co myślisz.";
			link.l1.go = "Regata_Contra_2";
		break;
		
		case "Regata_Contra_2":
			if (sti(pchar.questTemp.Regata.Index != 1))
			{
				sTemp = pchar.questTemp.Regata.ContraIndex;
				dialog.text = "Wiemy, że przed tobą jest jeszcze jeden uczestnik - "+pchar.questTemp.Regata.AdversaryName.(sTemp)+" z "+pchar.questTemp.Regata.AdversaryShipName.(sTemp)+"Opuścił port niedawno, a wkrótce będzie płynął obok przylądka Gonaives.";
			}
			else
			{
				dialog.text = "Wiemy, że jest jeszcze jeden uczestnik tuż za tobą - "+pchar.questTemp.Regata.AdversaryName.b+" z "+pchar.questTemp.Regata.AdversaryShipName.b+" .    Będzie tu za kilka godzin.";
			}
			link.l1 = "Hmm... jesteś bardzo dobrze poinformowany.";
			link.l1.go = "Regata_Contra_3";
		break;
		
		case "Regata_Contra_3":
			if (sti(pchar.questTemp.Regata.Index != 1)) sTemp = "letting you pass ahead of him and take his position";
			else sTemp = "therefore you will be taking a lead for a long time";
			dialog.text = "Zdecydowanie. Przejdźmy do sedna. Oferujemy naszą pomoc za twoje pieniądze. Umieściliśmy cztery działa z naszego statku na przylądku za zatoką Gonaives. Każdy statek regatowy musi go podwoić\nDziała są załadowane łańcuchowymi kulami. Jeśli się dogadamy, powiem naszym przyjaciołom z dział, aby zniszczyli żagle twojego konkurenta, żeby musiał stracić czas na ich naprawę, "+sTemp+".";
			link.l1 = "Ile chcesz za tę usługę?";
			link.l1.go = "Regata_Contra_4";
			link.l2 = "Nie. Nie zamierzam używać takich metod, by wygrać. Myliłeś się co do mnie. Żegnajcie, panowie.";
			link.l2.go = "Regata_Contra_exit";
		break;
		
		case "Regata_Contra_exit":
			dialog.text = "Cóż kapitanie, to twój wybór. Żegnaj.";
			link.l1 = "Dzięki za informacje o przylądku. Będę się od niego trzymał z daleka.";
			link.l1.go = "Contra_exit";
			AddQuestRecord("Regata", "31");
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
		break;
		
		case "Regata_Contra_4":
			if (sti(pchar.questTemp.Regata.Index != 1)) iTemp = 50000;
			else iTemp = 30000;
			dialog.text = "Niewiele. Tylko "+iTemp+" pesos. A jeden z waszych konkurentów straci prawie dwa dni z powodu... wypadku, ha-ha!";
			if (makeint(Pchar.money) >= iTemp)
			{
				link.l1 = "Heh! Gadacie z sensem, przyjacielu! Ja płacę. Ale jakie mam gwarancje, że wykonacie swoje zadanie? I że nie ostrzelacie mojego statku, kiedy będę przepływał przez przylądek?";
				link.l1.go = "Regata_Contra_5";
			}
			link.l2 = "Nie mam takich pieniędzy. Więc nie będę mógł skorzystać z twoich usług.";
			link.l2.go = "Regata_Contra_exit";
		break;
		
		case "Regata_Contra_5":
			dialog.text = "Kapitanie, błagam, jesteśmy przemytnikami, nie jakimiś piratami. Wszyscy jesteśmy uczciwymi ludźmi... na swój sposób. Musiałeś kiedyś korzystać z naszych usług, prawda? Masz moje słowo. Możesz na nim polegać.";
			link.l1 = "Zgoda, dobrze więc, bierz swoje pieniądze.";
			link.l1.go = "Regata_Contra_6";
		break;
		
		case "Regata_Contra_6":
			AddQuestRecord("Regata", "30");
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
			dialog.text = "Będziecie zadowoleni z tej transakcji, kapitanie. I od razu poinformuję o tym moich chłopców z dział. Powodzenia!";
			link.l1 = " Nawzajem...";
			link.l1.go = "Contra_exit";
			if (sti(pchar.questTemp.Regata.Index != 1))
			{
				AddMoneyToCharacter(pchar, -50000);
				sTemp = pchar.questTemp.Regata.ContraIndex;
				pchar.questTemp.Regata.AdversaryThirdTransition.Time.(sTemp) = sti(pchar.questTemp.Regata.AdversaryThirdTransition.Time.(sTemp))+48;//задержка на 48 часов
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversaryThirdTransition.Time.(sTemp)));
			}
			else
			{
				AddMoneyToCharacter(pchar, -30000);
				pchar.questTemp.Regata.AdversaryThirdTransition.Time.b = sti(pchar.questTemp.Regata.AdversaryThirdTransition.Time.b)+36;//задержка на 36 часов
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversaryThirdTransition.Time.b));
			}
		break;
		
		case "Contra_exit":
			DialogExit();
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("RegataContra_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "quest", "quest2", "none", "", "", "", 10.0);
			}
		break;
		//контрики с пушками
		
		//падре
		case "Regata_Padre":
			pchar.questTemp.Regata.BranderName = GenerateRandomNameToShip(ENGLAND);
			dialog.text = "Dobry dzień, mój synu. Pragnę cię powitać i pokornie zapytać: czy chcesz przyczynić się do skarbca parafialnego jako lojalny sługa Anglii i naszego wielkiego Pana?";
			link.l1 = "Ojcze, ludzie czynią dobroczynność z powołania duszy, nie z przymusu. Zaczynam myśleć, że wszyscy na archipelagu postanowili okradać kapitanów regaty...";
			link.l1.go = "Regata_Padre_exit";
			link.l2 = "Z pewnością, ojcze święty. Ile by wystarczyło?";
			link.l2.go = "Regata_Padre_1";
		break;
		
		case "Regata_Padre_1":
			dialog.text = "Tak bardzo, jak tylko pozwolą ci na to twoje życzenia i możliwości, mój synu. Nasza parafia będzie wdzięczna nawet za najmniejszą sumę.";
			Link.l1.edit = 4;			
			link.l1 = "";
			link.l1.go = "Regata_Padre_2";
		break;
		
		case "Regata_Padre_2":
			iTemp = sti(dialogEditStrings[4]);
			if (iTemp <= 0 || sti(pchar.money) < iTemp)
			{
				dialog.text = "To złe podejście, mój synu. Wszyscy mamy grzechy, nie zapominaj o swojej duszy. Będziesz musiał stanąć przed naszym Stwórcą... i być może wkrótce.";
				link.l1 = "Nie potrzebuję twoich kazań, święty ojcze. Żegnaj.";
				link.l1.go = "Padre_exit";
				ChangeCharacterComplexReputation(pchar, "nobility", -3);
				AddQuestRecord("Regata", "35");
				break;
			}
			if (iTemp > 0 && iTemp <= 1000)//ничего не скажет
			{
				dialog.text = "Nasz parafianin i ja dziękujemy ci za ten skromny dar.";
				link.l1 = "Jesteś mile widziany, święty ojcze.";
				link.l1.go = "Padre_exit";
				AddMoneyToCharacter(pchar, -iTemp);
				AddQuestRecord("Regata", "35");
			}
			if (iTemp > 1000 && iTemp <= 5000)//1 категория - намекнет
			{
				dialog.text = "Nasza parafia i ja dziękujemy ci za ten dar. I chcę cię ostrzec, mój synu, że niektórzy grzeszni ludzie zamierzają cię skrzywdzić. Uważaj na morzu!";
				link.l1 = "Ojcze, każdego dnia ludzie planują coś przeciwko mnie... Ale dziękuję za twoje troski o mój los.";
				link.l1.go = "Padre_exit";
				AddMoneyToCharacter(pchar, -iTemp);
				AddQuestRecord("Regata", "34");
				AddQuestUserData("Regata", "sMoney", iTemp);
			}
			if (iTemp > 5000 && iTemp <= 10000)//2 категория - скажет
			{
				dialog.text = " Dziękuję ci w imieniu naszej parafii za ten cenny dar. W zamian chcę cię ostrzec, że niektórzy naprawdę źli ludzie spiskują przeciwko tobie. Słyszałem, że ci nikczemni apostaci zamierzają zatopić twój statek w tym właśnie porcie\nJuż przygotowali statek pełen prochu na ten zły czyn. Bądź ostrożny, mój synu, te zagubione dusze są poważne w swoich nikczemnych zamiarach... Niech cię Bóg błogosławi!";
				link.l1 = "Dziękuję, święty ojcze. Będę uważny.";
				link.l1.go = "Padre_exit";
				AddMoneyToCharacter(pchar, -iTemp);
				AddQuestRecord("Regata", "33");
				AddQuestUserData("Regata", "sMoney", iTemp);
			}
			if (iTemp > 10000)//3 категория - расскажет полностью
			{
				dialog.text = "Jesteś bardzo hojny, mój synu. Skromność pokornego sługi Bożego nie pozwala mi przyjąć całej sumy, którą chcesz ofiarować na dobro naszego kościoła. Wezmę tylko 10 000 pesos\nW zamian chcę cię ostrzec, że źli ludzie spiskują przeciwko tobie. Słyszałem, że ci nikczemni apostaci zamierzają zatopić twój statek w tym właśnie porcie\nPrzygotowali lugier pełen prochu o nazwie '"+pchar.questTemp.Regata.BranderName+"', płynie pod angielską banderą, aby zbliżyć się do ciebie bez wzbudzania podejrzeń. Bądź ostrożny, synu mój, te zagubione dusze są poważne w swoich nikczemnych zamiarach.\nZniszcz ich, daję ci rozgrzeszenie za ten grzech. Błogosławię cię! Będę się za ciebie modlił, synu mój.";
				link.l1 = "Dziękuję, święty ojcze. Jeśli te dranie ośmielą się zrobić coś złego, wyślę ich prosto do piekła!";
				link.l1.go = "Padre_exit";
				AddMoneyToCharacter(pchar, -10000);
				ChangeCharacterComplexReputation(pchar, "nobility", 2);
				AddQuestRecord("Regata", "32");
				AddQuestUserData("Regata", "sText", pchar.questTemp.Regata.BranderName);
			}
		break;
		
		case "Regata_Padre_exit":
			dialog.text = "Nie gniewaj się, synu mój. Gniew to grzech. Masz prawo nie czynić dobroczynności. Idź w pokoju, synu mój.";
			link.l1 = "Żegnaj, święty ojcze.";
			link.l1.go = "Padre_exit";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddQuestRecord("Regata", "35");					  
		break;
		
		case "Padre_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload7_back", "SentJons_church", "barmen", "stay", "ReturnRegataPadreNorm", 5);
		break;
		
		case "Regata_Spyglass":
			dialog.text = "Dzień dobry, kapitanie! Nazywam się "+npchar.name+" i chciałbym...";
			link.l1 = "... zaproponować mi coś... Czy mam rację, młoda damo?";
			link.l1.go = "Regata_Spyglass_1";
		break;
		
		case "Regata_Spyglass_1":
			dialog.text = "Oczywiście, kapitanie! I dlaczego jesteś tak zaskoczony? Jesteś przystojnym żeglarzem i bierzesz udział w regatach, więc na pewno każdy chętnie sprzeda ci jakieś przydatne morskie rzeczy.";
			link.l1 = "Dobrze, piękności, masz rację. Co masz dla mnie?";
			link.l1.go = "Regata_Spyglass_2";
		break;
		
		case "Regata_Spyglass_2":
			if(hrand(11) > 10)//отличная труба
			{
				pchar.questTemp.Regata.Spy = "spyglass4";
				sTemp = "an excellent spyglass";
				pchar.questTemp.Regata.SpyPrice = 20000;
				pchar.questTemp.Regata.SpyIndex = 12;//выигрыш - 12 часов
			}
			else
			{
				if(hrand(11) < 6)//обычная труба
				{
					pchar.questTemp.Regata.Spy = "spyglass2";
					sTemp = "an ordinary spyglass";
					pchar.questTemp.Regata.SpyPrice = 1800;
					pchar.questTemp.Regata.SpyIndex = 4;//выигрыш - 4 часа
				}
				else//хорошая труба - как пригодится
				{
					pchar.questTemp.Regata.Spy = "spyglass3";
					sTemp = "a good spyglass";
					pchar.questTemp.Regata.SpyPrice = 10000;
					pchar.questTemp.Regata.SpyIndex = 8;//выигрыш - 8 часов
				}
			}
			dialog.text = "Proszę, spójrz. Odziedziczyłem to po moim ojcu. On także był marynarzem, jak ty, i miał wiele nawigacyjnych gratów. Nie potrzebuję tego, ale tobie na pewno się przyda. Proszę tylko "+FindRussianMoneyString(sti(pchar.questTemp.Regata.SpyPrice))+" dla tego.";
			if (sti(pchar.money) >= sti(pchar.questTemp.Regata.SpyPrice))
			{
				link.l1 = "No, no..."+sTemp+" ! Interesujące! Mówię ci, kupię to od ciebie. Dla twoich pięknych oczu. Więc chcesz "+FindRussianMoneyString(sti(pchar.questTemp.Regata.SpyPrice))+" za to? Proszę, weź swoje pieniądze.";
				link.l1.go = "Regata_Spyglass_3";
			}
			link.l2 = "Hm..."+sTemp+"? Nie, dziewczyno, przykro mi, ale tego nie potrzebuję. Mam już bardzo ładną lunetę swoją własną. Więc... niestety!";
			link.l2.go = "Regata_Spyglass_exit";
		break;
		
		case "Regata_Spyglass_3":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Regata.SpyPrice));
			GiveItem2Character(pchar, pchar.questTemp.Regata.Spy);
			dialog.text = "Dziękuję, kapitanie. Mam nadzieję, że dobrze Ci posłuży. Cieszę się, że uznałeś to za przydatne. Powodzenia w regatach!";
			link.l1 = "Dziękuję, "+npchar.name+" ! Żegnaj.";
			link.l1.go = "Spyglass_exit";
			for (i=1; i <=5; i++)
			{
				if (i==1) sTemp = "a";
				if (i==2) sTemp = "b";
				if (i==3) sTemp = "c";
				if (i==4) sTemp = "d";
				if (i==5) sTemp = "e";
				pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp) = sti(pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp))+sti(pchar.questTemp.Regata.SpyIndex);//купил трубу - выиграл время
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp)));
			}
		break;
		
		case "Regata_Spyglass_exit":
			dialog.text = "Jaka szkoda, kapitanie. Miałem nadzieję, że będzie to dla ciebie przydatne. Cóż, spróbuję sprzedać to komuś innemu. Żegnaj!";
			link.l1 = "Żegnaj, "+npchar.name+".";
			link.l1.go = "Spyglass_exit";
			pchar.questTemp.Regata.AdversaryFourthTransition.Time.c = sti(pchar.questTemp.Regata.AdversaryFourthTransition.Time.c)-sti(pchar.questTemp.Regata.SpyIndex);//третий соперник выиграл время
		break;
		
		case "Spyglass_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10);
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		case "Regata_SiegeOfficer":
			dialog.text = "Witaj, kapitanie. Czyżbyś nie był uczestnikiem regaty? Mam rację?";
			link.l1 = "Tak. A co to za sprawa, oficerze?";
			link.l1.go = "Regata_SiegeOfficer_1";
		break;
		
		case "Regata_SiegeOfficer_1":
			dialog.text = "Zapewne już wiesz, że nasza kolonia jest oblężona przez Hiszpanów. Dlatego nasz gubernator chce z tobą porozmawiać. Czy byłbyś tak uprzejmy odwiedzić go? Sprawa jest teraz bardzo pilna.";
			link.l1 = "Hm... Dobrze, udam się natychmiast do Jego Ekscelencji, chociaż naprawdę nie rozumiem, jak mogę być zaangażowany w operacje wojskowe.";
			link.l1.go = "Regata_SiegeOfficer_2";
		break;
		
		case "Regata_SiegeOfficer_2":
			dialog.text = "Jesteś zamieszany, kapitanie. Nie traćmy czasu i ruszajmy do rezydencji. Chodź za mną.";
			link.l1.go = "Regata_SiegeOfficer_3";
		break;
		
		case "Regata_SiegeOfficer_3":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "Bridgetown_townhall", "goto", "governor1", "RegataSiegeHover", -1);
		break;
		
		case "Regata_SiegeOfficer_4":
			dialog.text = "Panie! Jestem gotów wysłać cywilów na pański statek. Czy idziemy teraz?";
			link.l1 = "Tak, oczywiście. Natychmiast wypływamy. Powiedz ludziom, żeby wsiedli na szalupy.";
			link.l1.go = "Regata_SiegeOfficer_5";
		break;
		
		case "Regata_SiegeOfficer_5":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "RegataSiegeOpen", -1);
			for (i=1; i <=9; i++)
			{
				sld = characterFromId("RegataBridgWom_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "quest", "quest1", "none", "", "", "", 30);
			}
		break;
		
		case "Regata_SiegeOfficer_6":
			dialog.text = "Zrobiliśmy to... Wygląda na to, że ten slup był zwiadowcą eskadry, a te kastylijskie dranie kręciły się wokół. Kapitanie, proszę pomóż mi zabrać kobiety do jaskiń, istnieje możliwość, że są tu jeszcze inne oddziały hiszpańskie.";
			link.l1 = "Dobrze. Chodźmy!";
			link.l1.go = "Regata_SiegeOfficer_7";
		break;
		
		case "Regata_SiegeOfficer_7":
			DialogExit();
			sld = characterFromId("SiegeOfficer");
			LAi_ActorFollowEverywhere(sld, "", -1);
			pchar.quest.Regata_Siege3.win_condition.l1 = "location";
			pchar.quest.Regata_Siege3.win_condition.l1.location = "Barbados_cave";
			pchar.quest.Regata_Siege3.function = "RegataBarbadosCave";
		break;
		
		case "Regata_SiegeOfficer_8":
			dialog.text = "Podziękowania za twoją pomoc, kapitanie! Gdyby nie ty i twoja odwaga... Jesteś prawdziwym bohaterem, ukończyłeś tę operację pomimo wszystkich niebezpieczeństw i własnych interesów. Zastanawiałem się, jak cię wynagrodzić... i jest sposób, by zwiększyć twoje szanse w regatach.";
			link.l1 = "Interesujące. Co to za droga?";
			link.l1.go = "Regata_skiper";
		break;
		
		case "Regata_Hovernor":
			dialog.text = "Witaj, kapitanie "+GetFullName(pchar)+" . Dobrze, że przyszedłeś. Nasze miasto potrzebuje twojej pomocy.";
			link.l1 = "Panie, jeśli mówisz o hiszpańskiej eskadrze, która właśnie szturmuje twoją kolonię, to nie mam pojęcia, jak mogę ci pomóc. Dowodzę lugrem, a nie okrętem liniowym...";
			link.l1.go = "Regata_Hovernor_1";
		break;
		
		case "Regata_Hovernor_1":
			dialog.text = "Słuchaj mnie, kapitanie, a zrozumiesz. Jesteśmy w poważnych tarapatach. Miasto jest pod hiszpańskim oblężeniem. Decydująca bitwa z fortem zaraz się rozpocznie. Poza tym, kilkuset Hiszpanów już wylądowało i zablokowało każde wyjście z miasta, teraz mogą nas zaatakować z morza i lądu\nGarnizon fortu przygotowuje się do obrony miasta przed eskadrą i brakuje żołnierzy w samej osadzie. Każdy mężczyzna zdolny do posługiwania się bronią jest zmobilizowany, ale co z innymi?\nJest tam setki dusz kobiet w Bridgetown. Czy możesz sobie wyobrazić, co się z nimi stanie, jeśli nie uda nam się obronić naszej kolonii? Wierzę, że rozumiesz.";
			link.l1 = "Sir, rozumiem cię, ale, znów, jak mogę pomóc? Czego ode mnie chcesz? Walczyć z liniowymi okrętami czy zaciągnąć się z moją załogą do miejskiej milicji?";
			link.l1.go = "Regata_Hovernor_2";
		break;
		
		case "Regata_Hovernor_2":
			switch (sti(Pchar.BaseNation))
			{
				case ENGLAND: sTemp = "You are English , help us to save English citizens and what is important - women!" break;
				case FRANCE: sTemp = "You are French, so you basically are our ally, help us to save English citizens and what is more important - women!" break;
				case SPAIN: sTemp = "I know that you are Spanish and these are your people in the sea, so I know that I am already asking for a lot, but these women are innocent and have nothing to do with this battle. So please I beg of you, help them!" break;
				case HOLLAND: sTemp = "I know that you are Dutch and our nations are at war, but you are participating in the English regatta under the English flag. Don't you think that it is right to fight for innocent and peaceful people, for women? Please captain, help them!" break;
			}
			dialog.text = "Żadne z nich. Proszę cię tylko o jedno. Zabierz kobiety i dzieci stąd na swoim statku. Nie ma ich wielu, około setki. Zabierz ich do Cape Harrison wraz z porucznikiem Mahonym, on zadba o ich bezpieczeństwo w jaskini\nJestem pewien, że Hiszpanie ich nie będą szukać. Nie mam żadnych statków do dyspozycji, wszystko co mieliśmy zostało zatopione przez hiszpańską eskadrę. Jesteś moją ostatnią nadzieją. Możesz zabrać ich do przylądka w jednym rejsie, mimo że twój statek będzie przeciążony. Okręty liniowe nie będą za tobą podążać.\nNie mogę prosić nikogo innego o to."+sTemp+"";
			link.l1 = "Sir, przykro mi, ale mój statek jest już przeładowany i nie będzie w stanie pomieścić tylu ludzi nawet na dwa rejsy. Każda przypadkowa kula armatnia, nawet upadła w pobliżu, pośle mój statek i wasze kobiety na dno morza. Wybaczcie mi, ale nie mogę wam pomóc.";
			link.l1.go = "Regata_Hovernor_exit";
			link.l2 = "Bardzo dobrze, panie. Pomogę wam. Honor marynarza zobowiązuje mnie do tego.";
			link.l2.go = "Regata_Hovernor_3";
		break;
		
		case "Regata_Hovernor_3":
			dialog.text = "Cieszę się, że się zgodziłeś. Jesteś prawdziwym żołnierzem. Porucznik Mahony przyprowadzi kobiety i dzieci na twój statek. Powodzenia, kapitanie!";
			link.l1 = "Dziękuję, panie. Nie traćmy czasu!";
			link.l1.go = "Regata_Hovernor_4";
		break;
		
		case "Regata_Hovernor_wait":
			dialog.text = "Pospiesz się, kapitanie. Czas ucieka.";
			link.l1 = "Płynę już!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_Hovernor_wait";
		break;
		
		case "Regata_Hovernor_exit":
			dialog.text = "To jest niewiarygodne. Nawet nie spróbujesz? Cóż, masz do tego prawo. Nie mogę niczego od ciebie wymagać. Gdybyś był zwykłym kapitanem, skonfiskowałbym twój statek dla dobra setki kobiet, ale bierzesz udział w regatach, a zatem jesteś pod ochroną gubernatora generalnego angielskich kolonii\nMiałem nadzieję, że twoje sumienie weźmie górę, ale się myliłem. Idź i niech Bóg będzie miłosierny dla twojej duszy!";
			link.l1 = "Żegnaj, panie.";
			link.l1.go = "Hovernor_exit";
		break;
		
		case "Hovernor_exit":
			DialogExit();
			pchar.quest.Regata_TH.over = "yes"; // belamour снять прерывание
			pchar.questTemp.Regata.AdversaryFifthTransition.Time.e = sti(pchar.questTemp.Regata.AdversaryFifthTransition.Time.e)-36;//пятый противник выиграл 36 часов
			ChangeCharacterComplexReputation(pchar, "nobility", -8);
			ChangeCharacterNationReputation(pchar, ENGLAND, -5);
			//вертаем губера в норму
			npchar.Dialog.Filename = "Common_Mayor.c";
			npchar.dialog.currentnode = "First time";
			//удаляем лейтенанта
			sld = characterFromId("SiegeOfficer");
			sld.lifeday = 0;
			//открываем ворота и выход в море
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Bridgetown_town", "reload1_back", false);
			LocatorReloadEnterDisable("Bridgetown_town", "reload2_back", false);
			LocatorReloadEnterDisable("Bridgetown_town", "gate1_back", false);
			LocatorReloadEnterDisable("Bridgetown_town", "gate_back", false);
			LocatorReloadEnterDisable("Bridgetown_Exittown", "reload3", false);
			//остров в норму
			n = FindIsland("Barbados");	
			DeleteAttribute(Islands[n], "DontSetShipInPort");
			//осаду снимем через 5 дней
			SetFunctionTimerCondition("RegataSiegeDelete", 0, 0, 5, false);
			for (i=1; i <=9; i++)//девок счистим
			{
				sld = characterFromId("RegataBridgWom_"+i);
				sld.lifeday = 0; // patch-7
				LAi_CharacterDisableDialog(sld);
			}
			AddQuestRecord("Regata", "38");
			AddQuestUserData("Regata", "sName", GetFullName(npchar));
		break;
		
		case "Regata_Hovernor_4":
			DialogExit();
			pchar.quest.Regata_TH.over = "yes"; // belamour снять прерывание
			NextDiag.CurrentNode = "Regata_Hovernor_wait";
			sld = characterFromId("SiegeOfficer");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "Bridgetown_town", "goto", "goto4", "", 10);
			pchar.quest.Regata_evacuation.win_condition.l1 = "location";
			pchar.quest.Regata_evacuation.win_condition.l1.location = "Bridgetown_town";
			pchar.quest.Regata_evacuation.function = "RegataSiegeEvacuation";
			AddQuestRecord("Regata", "36");
			AddQuestUserData("Regata", "sName", GetFullName(npchar));
		break;
		
		case "Regata_BridgWom":
			dialog.text = "Hiszpanie nas wytropili! Boże, ratuj nas!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_BridgWom";
		break;
		
		case "Regata_BridgWom_1":
			dialog.text = "Porucznik Mahony nie żyje... to musi być koszmar. Był dzielnym oficerem. Kapitanie, czy mógłbyś nas zabrać do jaskini? Po prostu nas tam zabierz, a my się sobą zajmiemy.";
			link.l1 = "Pewnie. Chodź za mną!";
			link.l1.go = "Regata_BridgWom_2";
		break;
		
		case "Regata_BridgWom_2":
			DialogExit();
			for (i=1; i <=9; i++)
			{
				sld = characterFromId("RegataBridgWom_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			pchar.quest.Regata_Siege3.win_condition.l1 = "location";
			pchar.quest.Regata_Siege3.win_condition.l1.location = "Barbados_cave";
			pchar.quest.Regata_Siege3.function = "RegataBarbadosCave";
		break;
		
		case "Regata_BridgWom_3":
			dialog.text = "Oto jesteśmy... dziękuję, kapitanie! Właśnie uratowałeś nas wszystkich! Myślałem, jak cię wynagrodzić... jest sposób na poprawę twoich szans w regatach.";
			link.l1 = "Idź dalej.";
			link.l1.go = "Regata_skiper";
		break;
		
		case "Regata_skiper":
			pchar.questTemp.Regata.Name = GetFullName(npchar);
			dialog.text = "Zmierzacie do Port Royal? Najkrótsza trasa wiedzie przez Curacao. Wróćcie do Bridgetown. Znajdźcie człowieka o imieniu Woodrow Dougherty, to stary żeglarz i doświadczony nawigator. Doskonale zna obszar między Barbados a Jamajką, będzie dla was wielką pomocą\nTo zaoszczędzi wam dużo cennego czasu, którego tak desperacko potrzebujecie, żeby wygrać. Znajdźcie go w lokalnym kościele i powiedzcie mu, że "+GetFullName(npchar)+" - wysłał cię, nie odmówi ci. Zabierz go do Port Royal, i tak miał tam płynąć.";
			link.l1 = "Bardzo dobrze! Dobry nawigator będzie mi przydatny. Żegnaj.";
			link.l1.go = "Regata_skiper_1";
		break;
		
		case "Regata_skiper_1":
			dialog.text = "Żegnaj, kapitanie! Powodzenia!";
			link.l1 = "Być może, spotkamy się ponownie...";
			link.l1.go = "Regata_skiper_2";
		break;
		
		case "Regata_skiper_2":
			DialogExit();
			AddQuestRecord("Regata", "37");
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			ChangeCharacterNationReputation(pchar, ENGLAND, 10);
			LAi_SetStayType(npchar);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0; // patch-8
			for (i=1; i <=9; i++)
			{
				sld = characterFromId("RegataBridgWom_"+i);
				LAi_SetStayType(sld);
				LAi_CharacterDisableDialog(sld);
				sld.lifeday = 0; // patch-8
			}
			//вертаем губера в норму
			sld = characterFromId("Bridgetown_Mayor");
			sld.Dialog.Filename = "Common_Mayor.c";
			sld.dialog.currentnode = "First time";
			//открываем ворота и выход в море
			LocatorReloadEnterDisable("Shore4", "boat", false);
			LocatorReloadEnterDisable("Bridgetown_town", "gate1_back", false);
			LocatorReloadEnterDisable("Bridgetown_town", "gate_back", false);
			LocatorReloadEnterDisable("Bridgetown_Exittown", "reload3", false);
			LocatorReloadEnterDisable("Barbados_cave", "reload1", false);
			bQuestDisableMapEnter = false;
			//осаду снимем через 5 дней
			SetFunctionTimerCondition("RegataSiegeDelete", 0, 0, 5, false);
			RegataSiegeSkiper();//поставим Вудро в церковь
		break;
		
		case "Regata_SiegeSkiper":
			dialog.text = "Dzień dobry. Chcesz czegoś?";
			link.l1 = "Twoje imię to Woodrow Dougherty, czy mam rację?";
			link.l1.go = "Regata_SiegeSkiper_1";
		break;
		
		case "Regata_SiegeSkiper_1":
			dialog.text = "Masz rację. Jak mogę być pomocny?";
			link.l1 = "Wiem, że jesteś doświadczonym nawigatorem i dobrze znasz wody między Barbados a Curacao. Wiem także, że chcesz dotrzeć do Port Royal. Jestem uczestnikiem regat i jest jeszcze jeden ostatni przystanek - Port Royal. Chcę Cię poprosić, byś dołączył do mojej załogi jako nawigator na tę ostatnią podróż.";
			link.l1.go = "Regata_SiegeSkiper_2";
		break;
		
		case "Regata_SiegeSkiper_2":
			dialog.text = "Interesujące... I dlaczego myślisz, że dołączę do twojej załogi?";
			link.l1 = "Cóż, ponieważ słyszałem o tobie od "+pchar.questTemp.Regata.Name+"z wszelkimi gwarancjami, że nie odmówisz. A z powodu mojej pomocy dla Bridgetown w tej krytycznej chwili...";
			link.l1.go = "Regata_SiegeSkiper_3";
		break;
		
		case "Regata_SiegeSkiper_3"://а тут - как уж свезет
			if(hrand(2) != 2)
			{
				dialog.text = "Od "+pchar.questTemp.Regata.Name+"? Teraz rozumiem, pewnie. Dobrze, kapitanie, pomogę ci popłynąć najkrótszą drogą do Port Royal. Czy zamierzasz wyruszyć teraz?";
				link.l1 = "Tak.";
				link.l1.go = "Regata_SiegeSkiper_4";
			}
			else
			{
				dialog.text = ""+pchar.questTemp.Regata.Name+"? Rozumiem. Ależ kapitanie, nie mogę opuścić mego miasta w tak niebezpiecznym czasie. Musisz mnie zrozumieć jako żołnierza, który zapewnił nam bezinteresowną pomoc\nNie chcę, by ludzie szeptali za moimi plecami, że stary Woodrow uciekł w obliczu ostatecznej bitwy przeciwko Hiszpanom. Zostanę. Nie miej żalu, kapitanie.";
				link.l1 = "I to twoje ostatnie słowo? Ale ja pomogłem waszej kolonii...";
				link.l1.go = "Regata_SiegeSkiper_6";
			}
		break;
		
		case "Regata_SiegeSkiper_4":
			dialog.text = "Nie traćmy więc czasu. Pozwól tylko, że spakuję swoje rzeczy i będę do twojej dyspozycji.";
			link.l1 = "Moi marynarze będą czekać na ciebie na molo i dostarczą cię na 'Świętą Katarzynę'. Dziękuję, Woodrow!";
			link.l1.go = "SiegeSkiper_hire";
		break;
		
		case "Regata_SiegeSkiper_6":
			dialog.text = "Kapitanie, regaty to sport, a hiszpańskie oblężenie mojego domu to życie. Nigdzie z tobą nie pójdę. I powtórzę się, musisz mnie zrozumieć - honor i obowiązek wciąż coś znaczą w tym świecie. To moje ostatnie słowo i nie zamierzam go zmieniać.\nJednakże mogę ci doradzić, jak najszybciej tam dotrzeć najbezpieczniejszą trasą, żegluj na północny zachód w stronę Dominiki, a stamtąd kieruj się na Martynikę lub Gwadelupę, zależy od ciebie i wiatru. Następnie żegluj bezpośrednio w stronę Port-Royal, albo możesz żeglować przez Curaçao, czego bym nie polecał, ale jeśli masz dobre stosunki z Holendrami, to proszę bardzo.";
			link.l1 = "Cóż, dziękuję... ale jestem rozczarowany. Żegnaj, Woodrow.";
			link.l1.go = "SiegeSkiper_exit";
		break;
		
		case "SiegeSkiper_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
		break;
		
		case "SiegeSkiper_hire":
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 10.0);
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.loyality = 25;
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			//пересчитываем время пятого перехода
			for (i=1; i <=5; i++)
			{
				if (i==1) sTemp = "a";
				if (i==2) sTemp = "b";
				if (i==3) sTemp = "c";
				if (i==4) sTemp = "d";
				if (i==5) sTemp = "e";
				pchar.questTemp.Regata.AdversaryFifthTransition.Time.(sTemp) = sti(pchar.questTemp.Regata.AdversaryFifthTransition.Time.(sTemp))+18+(rand(18));//выигрыш до 1.5 суток
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp)));
			}
			SetFunctionTimerCondition("SiegeSkiperOver", 0, 0, 15, false);//чтобы не присвоил офицера
			DialogExit();
		break;
		
		case "Regata_Finish":
		iTest = FindColony("Portroyal"); 
		if (iTest != -1)
		{
			rColony = GetColonyByIndex(iTest);
			sFrom_sea = rColony.from_sea;
		}
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
		{
			//снимаем запреты
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			bool bRegLugger = sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_LUGGER || sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_CAREERLUGGER;
			if (CheckAttribute(pchar, "questTemp.Regata.Breach") || !CheckAttribute(pchar, "questTemp.Regata.Bridgetown") || GetCompanionQuantity(pchar) > 1 || !bRegLugger || pchar.Ship.Name != "Saint Catherine")
			{
				dialog.text = "Złamałeś zasady regat na ostatnim etapie. Twój wynik został zdyskwalifikowany. Nie mam ci nic więcej do powiedzenia, kapitanie.";
				link.l1 = "Eh...co do diabła! Cóż, nic się nie da zrobić, byłeś zbyt uważny. Żegnaj!";
				link.l1.go = "exit";
				npchar.lifeday = 1;
				DeleteAttribute(pchar, "questTemp.Regata");
				AddQuestRecord("Regata", "45");
				CloseQuestHeader("Regata");
			}
			else
			{
				n=1;
				for (i=1; i <=5; i++)
				{
					if (i==1) sTemp = "a";
					if (i==2) sTemp = "b";
					if (i==3) sTemp = "c";
					if (i==4) sTemp = "d";
					if (i==5) sTemp = "e";
					if (pchar.questTemp.Regata.AdversaryFifthTransition.Time.(sTemp) < sti(pchar.questTemp.Regata.FifthTransitionTime)) n++;
					pchar.questTemp.Regata.Result = n;//место в регате
				}
				if (n==1)
				{
					dialog.text = "Kapitan "+GetFullName(pchar)+", moje gratulacje! Zajęło to "+sti(pchar.questTemp.Regata.FifthTransitionTime)+" godziny na ukończenie regat, a zostawiłeś wszystkich przeciwników daleko w tyle. To niezwykły wynik!";
					link.l1 = "Dziękuję za miłe słowa, panie!";
					link.l1.go = "First_result";
				}
				else
				{
					if (n==6)
					{
						dialog.text = "Kapitanie, niestety, ale twój wynik jest najgorszy, spędziłeś "+sti(pchar.questTemp.Regata.FifthTransitionTime)+" godziny. Nie smuć się, miałeś naprawdę trudnych przeciwników.";
						link.l1 = "Nie jestem smutny, panie. Cieszę się, że wziąłem udział w regatach i sprawdziłem swoje umiejętności.";
						link.l1.go = "Other_result";
						AddQuestRecord("Regata", "44");
						CloseQuestHeader("Regata");
					}
					else
					{
          				dialog.text = "Kapitanie, jesteś w "+n+"miejsce. Gratulacje z udanym wynikiem, pokazałeś godny czas - "+sti(pchar.questTemp.Regata.FifthTransitionTime)+" godzin. Gratulacje mimo twojej porażki!";
						link.l1 = "To w porządku, sir. Cieszę się, że pokazałem dobry wynik w tej trudnej konkurencji.";
						link.l1.go = "Other_result";
						if (n==2) AddQuestRecord("Regata", "40");
						if (n==3) AddQuestRecord("Regata", "41");
						if (n==4) AddQuestRecord("Regata", "42");
						if (n==5) AddQuestRecord("Regata", "43");
						CloseQuestHeader("Regata");
					}
				}
			}
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex("SiegeSkiper");
			sld = &Characters[sti(Pchar.questTemp.FiringOfficerIDX)];
			CheckForReleaseOfficer(sti(Pchar.questTemp.FiringOfficerIDX));
			RemovePassenger(Pchar, sld);
			DeleteAttribute(sld, "Payment");
			DeleteAttribute(Pchar, "questTemp.FiringOfficerIDX");//удаляем из офицеров
			log_info("Woodrow Dougherty has landed");
			pchar.quest.SiegeSkiperOver.over = "yes"; //снять таймер
		}
		else
		{
			dialog.text = "Panie, pozwól, że zapytam - gdzie jest twój statek? Nie widzę go...";
			link.l1 = "Przepraszam, panie. Natychmiast zabiorę ją do portu.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_Finish";
		}
		break;
		
		case "First_result":
			if (CheckAttribute(pchar, "questTemp.Regata.Rate")) sTemp = "Come and see me in my office. I will give you your prize for your stake.";
			else sTemp = "And if you had made a stake on your victory as I offered you to, you would have gotten an extra prize too.";
			dialog.text = "Odwiedź gubernatora generalnego jutro, a on da ci twoje 250 000 pesos i cenne prezenty. "+sTemp+"Nie opuszczaj miasta, zgodnie z tradycją nagrody zostaną przekazane do skarbca miejskiego, jeśli zwycięzca nie odbierze ich w ciągu tygodnia.";
			link.l1 = "Rozumiem, panie. Odwiedzę go jutro!";
			link.l1.go = "First_result_1";
		break;
		
		case "First_result_1":
			DialogExit();
			//npchar.lifeday = 7;
			Achievment_Set("ach_09");
			npchar.dialog.currentnode = "Other_result_repeat";
			pchar.questTemp.Regata.Win = "true";
			pchar.quest.Regata_Final.win_condition.l1 = "Timer";
			pchar.quest.Regata_Final.win_condition.l1.date.hour  = 6.0;
			pchar.quest.Regata_Final.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Regata_Final.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Regata_Final.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Regata_Final.function = "RegataFinal";
			SetFunctionTimerCondition("RegataFinalOver", 0, 0, 8, false);//таймер не снимаем - через 8 дней подчистится все автоматически
			// слухи
			AddSimpleRumour("Ah, you are the legendary captain, the winner of the regatta! It's such a pleasure to see you in flesh!", ENGLAND, 60, 10);
			AddSimpleRumour("Ha, look at this, a master of wind and waves, the winner of the regatta! You have my respect...", ENGLAND, 60, 10);
			AddSimpleRumour("Oh, a great sailor, a king of the wind and the sea, the winner of regatta has visited our city! We are glad to see you, captain!", ENGLAND, 60, 10);
			AddSimpleRumour("Oh, yes I was lucky to chat with a living legend, the captain who is capable of crossing the archipelago in three days even facing a headwind! My respects, captain!", ENGLAND, 60, 10);
			AddSimpleRumour("Ah, so you are the legendary captain, the winner of the regatta! Pleasure to see you!", FRANCE, 60, 10);
			AddSimpleRumour("Ha, aren't you the master of wind and waves, the winner of the regatta! You have my respects...", FRANCE, 60, 10);
			AddSimpleRumour("Oh, a great sailor, a king of the wind and the sea, the winner of regatta has visited our city! We are glad to see you, captain!", FRANCE, 60, 10);
			AddSimpleRumour("Oh, yes I was lucky to chat with a living legend, the captain capable of crossing the archipelago in three days even facing a headwind! My respects, captain!", FRANCE, 60, 10);
			// экспа
			AddComplexSeaExpToScill(2000, 300, 300, 0, 500, 500, 0);
			AddCharacterExpToSkill(pchar, "Leadership", 2000);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 1000);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
			ChangeCharacterComplexReputation(pchar, "authority", 10);
			ChangeCharacterComplexReputation(pchar, "fame", 15);
			ChangeOfficersLoyality("good_all", 3);
			AddQuestRecord("Regata", "39");
			CloseQuestHeader("Regata");
		break;
		
		case "Other_result":
			dialog.text = "To dobrze usłyszeć honorową odpowiedź. Powodzenia, kapitanie!";
			link.l1 = "Żegnaj, panie.";
			link.l1.go = "Other_result_1";
		break;
		
		case "Other_result_1":
			DialogExit();
			npchar.dialog.currentnode = "Other_result_repeat";
			SetFunctionTimerCondition("RegataFinalOver", 0, 0, 1, false);
			// экспа
			AddComplexSeaExpToScill(500, 100, 100, 0, 100, 100, 0);
			AddCharacterExpToSkill(pchar, "Leadership", 200);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		case "Other_result_repeat":
			dialog.text = "Czegoś jeszcze chcesz, kapitanie?";
			link.l1 = "Nie... to nic.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Other_result_repeat";
		break;
		
		case "Give_advantage":
			dialog.text = "Ach, oto jesteś, panie "+GetFullName(pchar)+". Cieszę się, że cię widzę. Jesteś tu po swoją nagrodę? Jest gotowa dla ciebie.";
			link.l1 = "To dobrze słyszeć! Jakiej wielkości jest moja dodatkowa nagroda?";
			link.l1.go = "Give_advantage_1";
		break;
		
		case "Give_advantage_1":
			dialog.text = "Rozważając wszystkie stawki, twoja ostateczna nagroda to "+FindRussianMoneyString(makeint(pchar.questTemp.Regata.Advantage))+". Proszę, weź to. Gratulacje!";
			link.l1 = "Dzięki!";
			link.l1.go = "Give_advantage_2";
		break;
		
		case "Give_advantage_2":
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.Regata.Advantage));
			dialog.text = "Z pewnością, twoja popularność wśród obywateli Port Royal wzrosła. Myślę, że jesteś w stanie to dostrzec... lecz niestety pamięć ludzi jest krótka. Więc kąp się w chwale, póki wciąż jest tak jasna!";
			link.l1 = "Rozmawiasz o najprzyjemniejszych rzeczach, panie... Cóż, zobaczmy, jak to jest kąpać się w chwale. Żegnaj! To była przyjemność.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Other_result_repeat";
		break;
		
		case "Regata_CitMan_1":
			if (CheckAttribute(pchar, "questTemp.Regata"))
			{
				if (CheckAttribute(pchar, "questTemp.Regata.Result"))
				{
					if (sti(pchar.questTemp.Regata.Result) == 1)
					{
						dialog.text = "Gratulacje z powodu twego zwycięstwa, kapitanie! Znakomity wynik!";
						link.l1 = "Dzięki!";
						link.l1.go = "exit";
					}
					else
					{
						dialog.text = "Nie smuć się, kapitanie. Nie jest łatwo wygrać regatę, samo uczestnictwo w niej to przywilej!";
						link.l1 = "Nie martw się o mnie. Jestem zadowolony z mojego wyniku.";
						link.l1.go = "exit";
					}
				}
				else
				{
					dialog.text = "Cieszę się, że cię widzę, kapitanie! Powinieneś się zarejestrować, rozmawiając z sir Stevensonem.";
					link.l1 = "Rozumiem. Już do niego idę!";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Ach, kapitanie, czemuż zawiodłeś w taki sposób i to na samym ostatnim etapie!";
				link.l1 = "Tak, takie głupie z mojej strony...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Regata_CitMan_1";
		break;
		
		case "Regata_CitWom_1":
			if (CheckAttribute(pchar, "questTemp.Regata"))
			{
				if (CheckAttribute(pchar, "questTemp.Regata.Result"))
				{
					if (sti(pchar.questTemp.Regata.Result) == 1)
					{
						dialog.text = "Gratulacje z okazji zwycięstwa, kapitanie! Doskonały wynik!";
						link.l1 = "Dziękuję!";
						link.l1.go = "exit";
					}
					else
					{
						dialog.text = "Nie smuć się, kapitanie. Niełatwo wygrać regaty, samo uczestnictwo w nich to przywilej!";
						link.l1 = "Nie martw się o mnie. Jestem zadowolony z mojego wyniku.";
						link.l1.go = "exit";
					}
				}
				else
				{
					dialog.text = "Radość widzieć cię, kapitanie! Powinieneś zarejestrować się, rozmawiając z sir Stevensonem.";
					link.l1 = "Widzę. Już idę!";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Ach, kapitanie, dlaczegoś tak zawiódł i to na samym ostatnim etapie!";
				link.l1 = "Tak, tak głupio z mojej strony...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Regata_CitWom_1";
		break;
		
		case "Regata_CitHorse_1":
			if (CheckAttribute(pchar, "questTemp.Regata"))
			{
				if (CheckAttribute(pchar, "questTemp.Regata.Result"))
				{
					if (sti(pchar.questTemp.Regata.Result) == 1)
					{
						dialog.text = "Gratulacje z twojego zwycięstwa, kapitanie! Znakomity wynik!";
						link.l1 = "Dziękuję!";
						link.l1.go = "exit";
					}
					else
					{
						dialog.text = "Nie bądź smutny, kapitanie. Nie jest łatwo wygrać w regatach, samo uczestnictwo w nich to przywilej!";
						link.l1 = "Nie martw się o mnie. Jestem zadowolony z mojego wyniku.";
						link.l1.go = "exit";
					}
				}
				else
				{
					dialog.text = "Miło cię widzieć, kapitanie! Powinieneś się zarejestrować, rozmawiając z sir Stevensonem.";
					link.l1 = "Widzę. Jestem w drodze!";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Ach, kapitanie, czemuż zawiodłeś w taki sposób i to na samym ostatnim etapie!";
				link.l1 = "Tak, takie to było głupie z mojej strony...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Regata_CitHorse_1";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

void CreateRegataAdversaries()
{
	string sTemp;
	for (int i=0; i<=4; i++)
	{
	if (i==0) sTemp = "a";
	if (i==1) sTemp = "b";
	if (i==2) sTemp = "c";
	if (i==3) sTemp = "d";
	if (i==4) sTemp = "e";
	pchar.questTemp.Regata.AdversaryName.(sTemp) = GenerateRandomName_Generator(i, "man");
	pchar.questTemp.Regata.AdversaryShipName.(sTemp) = GenerateRandomNameToShip(ENGLAND);
	pchar.questTemp.Regata.AdversarySpeed.(sTemp) = 0.4+frand(0.9);
	log_testinfo(FindRussianDaysString(stf(pchar.questTemp.Regata.AdversarySpeed.(sTemp))));
	}
}

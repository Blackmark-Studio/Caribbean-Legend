// Ричард Флитвуд - английский капитан
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
			{
				if (pchar.questTemp.HWIC.Eng == "Start_main")
				{
					dialog.text = "Witaj, kapitanie! Nie daj się zwieść mojemu wyglądowi, jestem w porządku, prawie ślepy, ale w porządku. Pozwól, że się przedstawię, jestem Richard Fleetwood.";
					link.l1 = "Dzień dobry, to przyjemność cię poznać, jestem kapitanem "+GetFullName(pchar)+".";
					link.l1.go = "First_Task";
					DelLandQuestMark(npchar);
					break;
				}
				if (pchar.questTemp.HWIC.Eng == "GotoPortoffice")
				{
					if (sti(Pchar.Ship.Type) != SHIP_NOTUSED)
					{
						dialog.text = "Prosiłem cię, żebyś zacumował swój statek. Czy w ogóle mnie słuchasz?";
						link.l1 = "Oczywiście, że tak. Zajmuję się tym.";
						link.l1.go = "exit";
					}
					else
					{
						dialog.text = "Więc, znów tu jesteś. Przejmij dowodzenie nad 'Valkyrią' - moja załoga jest poinformowana o szczegółach - i popłyń do Bridgetown. Odwiedź każdą interesującą osobę w mieście i rozsiej plotki, o których rozmawialiśmy. Potem bądź gotów na atak tego drania. Nie zmieniaj statku i nie twórz eskadry, inaczej podejrzewa zasadzkę i się nie pojawi.\nMusisz zdobyć jego statek i dostarczyć go do St. John's. To niezwykle ważne, abyś znalazł dziennik pirata, ponieważ jest to jedyny dowód, jaki będziemy mieć na udział Lucasa Rodenburga. Jestem pewien, że sobie z tym poradzisz. Powodzenia, kapitanie.";
						link.l1 = "Podziękowania! Wykonam zadanie zgodnie z naszym planem.";
						link.l1.go = "First_Task_3";
						DelLandQuestMark(npchar);
						DelMapQuestMarkCity("SentJons");
					}
					break;
				}
				if (pchar.questTemp.HWIC.Eng == "MirageTake")//а вот теперь начинается перебор кораблей
				{
					pchar.quest.ToAntiguaMirageOver.over = "yes"; //снять таймер
					int iMir = 0;
					int iVal = 0;
					for(i = 0; i < COMPANION_MAX; i++)
					{
						iTemp = GetCompanionIndex(PChar, i);
						if(iTemp > 0)
						{
							sld = GetCharacter(iTemp);
							pchar.questTemp.HWIC.Eng.CompanionIndex = sld.Index;
							if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MIRAGE)
							{
							iMir = 1;
							RealShips[sti(sld.Ship.Type)].ship.upgrades.hull = 1;//чистый корпус
							SetShipSailsFromFile(sld, "ships/parus_silk.tga");
							SetSailsColor(sld, 0);//белый хлопковый парус
							DeleteAttribute(sld, "ship.sails");//починить паруса
							DeleteAttribute(sld, "ship.masts");//вернуть мачты
							}
							if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_VALCIRIA) iVal = 1;
						}
					}//установили признак наличия кораблей в эскадре.
					if (iMir == 1 && iVal == 0)//потеряли Валькирию
					{
						dialog.text = "Jesteś z powrotem, kapitanie... Już wiem wszystko o twojej podróży.";
						link.l1 = "Czyżby? Więc musisz wiedzieć, że...";
						link.l1.go = "Fleetwood_lostVal";
						DelLandQuestMark(npchar);
						DelMapQuestMarkCity("SentJons");
						break;
					}
					if (iMir == 0 && iVal == 1)//потеряли Мираж
					{
						dialog.text = "Jesteś z powrotem, kapitanie... Już wiem wszystko o twojej podróży.";
						link.l1 = "Czyżby? Więc musisz wiedzieć, że...";
						link.l1.go = "Fleetwood_lostMir";
						DelLandQuestMark(npchar);
						DelMapQuestMarkCity("SentJons");
						break;
					}
					if (iMir == 0 && iVal == 0)//а это вообще плохо
					{
						dialog.text = "Jesteś z powrotem, kapitanie... Już wszystko wiem o twojej podróży.";
						link.l1 = "Czyżby? Więc musisz wiedzieć, że...";
						link.l1.go = "Fleetwood_lostFull";
						DelLandQuestMark(npchar);
						DelMapQuestMarkCity("SentJons");
						break;
					}
						dialog.text = "Jesteś z powrotem, kapitanie... Już wiem wszystko o twojej podróży.";
						link.l1 = "Naprawdę? Więc musisz wiedzieć, że...";
					link.l1.go = "Fleetwood_complete";
					DelLandQuestMark(npchar);
					DelMapQuestMarkCity("SentJons");
					break;
				}
				if (pchar.questTemp.HWIC.Eng == "toAntigua")
				{
					dialog.text = "Witaj, mój przyjacielu! Cieszę się, że cię widzę! Czy masz Abigail na swoim statku?";
					link.l1 = "Niestety, nie, Richard. Odmówiła pójścia ze mną, ponieważ jej wyjazd byłby ciężkim ciosem dla jej ojca, który już stracił każdą monetę. Zdecydowałem się zająć problemem i odnaleźć pieniądze Salomona oraz tę wyspę...";
					link.l1.go = "Fleetwood_LastTask";
					DelLandQuestMark(npchar);
					DelMapQuestMarkCity("SentJons");
					break;
				}
				dialog.text = "Czy coś jeszcze, kapitanie?";
				link.l1 = "Nie, już odchodzę.";
				link.l1.go = "exit";		
				NextDiag.TempNode = "First time";
			}
				dialog.text = "Coś jeszcze, kapitanie?";
				link.l1 = "Nie, już odchodzę.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Fleetwood_abordage":
			PlaySound("Voice\English\hambit\Richard Flitwood-03.wav");
			dialog.text = "Przeklęty piracie! Wygrałeś abordaż, ale mimo to wypełnię swój obowiązek. Zaaranżowałem podpalenie prochowni i mój statek wkrótce wybuchnie razem z twoim 'Statkiem Widmo'. Nie zatopisz już ani jednego angielskiego statku. Zginę z honorem!";
			link.l1 = "Przykro mi, że muszę cię rozczarować, ale się mylisz, Fleetwood. Na moim statku nie ma piratów, już wcześniej się nimi zająłem. Potrzebowałem ciebie, a ten statek posłużył jako niezła pułapka.\nDość uprzejmości, muszę cię jeszcze zabić i uciec z tej płonącej łajby!";
			link.l1.go = "Fleetwood_abordage_1";
		break;
		
		case "Fleetwood_abordage_1":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle("PrepareToBoom"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.HWIC.Holl = "FleetwoodCapture";
			pchar.GenQuest.Detonation = true; // patch-4
		break;
		
		case "First_Task":
			dialog.text = "Charlie już mnie poinformował o twoim udanym przechwyceniu wrogiego karawanu handlowego. Cieszę się, że mogę cię poznać, Anglia potrzebuje takich odważnych kapitanów. Teraz pozwól, że powiem ci coś bardzo ważnego.";
			link.l1 = "Słucham, panie Fleetwood.";
			link.l1.go = "First_Task_1";			
		break;
		
		case "First_Task_1":
			dialog.text = "Piraciak popełnia akty przemocy na całym archipelagu, podszywając się pod 'Latającego Holendra', legendarny statek widmo. Udaje 'Latającego Holendra', legendarny statek widmo. Jestem pewien, że to Holender, ale latać nie potrafi. Skłaniam się ku wierze, że to najemnik Lucasa Rodenburga, wicedyrektora Holenderskiej Kompanii Zachodnioindyjskiej.\nRodenburg ogłosił cichą wojnę handlową przeciwko Anglii - ten 'statek widmo' atakuje jedynie statki handlowe pod angielską banderą. Dla kompanii kluczowe jest osłabienie naszego wpływu na ten obszar bez prowadzenia prawdziwej wojny.\nŚcigam ten statek widmo od jakiegoś czasu, ale jej kapitan to bardzo doświadczony żeglarz, a jego statek jest szybki i zwrotny.\nSkoro niemożliwe jest złapanie szakalu w otwartej walce, powinniśmy działać przebiegle, a ostatnia próba zamachu na moje życie przyniesie nam wielką przysługę. Co o tym sądzisz, kapitanie? Boisz się?";
			link.l1 = "Nie ma mowy. Z przyjemnością pomogę ci wytropić i zatopić tego drania. Miałeś mnie o to poprosić, prawda?";
			link.l1.go = "First_Task_2";	
		break;
		
		case "First_Task_2":
			dialog.text = "Masz rację. Teraz omówmy szczegóły. Moi ludzie rozpuszczą plotki, że jestem prawie martwy i sprzedałem ci mój statek 'Valkyrie'. Następnie przejdziemy do naszego małego oszustwa. Będziesz udawać kupca, który kupił brygantynę ode mnie i pozbył się większości dział.\nTwoim zadaniem jest popłynąć na Barbados i mówić wszystkim tam, że twoje ładownie są wypełnione cennym ładunkiem, a twoje kieszenie pełne monet. Daj im znać, że wkrótce zamierzasz wypłynąć. Odgrywaj rolę chciwego, prostego, ale bogatego kupca.\nNasz cholerny Holender zdobywa informacje o statkach handlowych przy Bridgetown. Nie wiadomo, kto dokładnie mu je dostarcza. Każdy jest podejrzany - od lokalnego kupca po gubernatora, choć ta ostatnia możliwość jest dość przerażająca.\nPrzejmij dowodzenie nad moją 'Valkyrie' i jej załogą. Ale najpierw powinieneś zostawić tutaj wszystkie swoje statki, już rozmawiałem z miejscowym kapitanem portu, to będzie kosztować 10 000 pesos miesięcznie za twój okręt flagowy.\nKiedy to zrobisz, wróć do mnie, a ja się tym zajmę. Ach, kapitanie, nie zapomnij wziąć swojej działki za przechwycenie srebrnej karawany i dziesięciu tysięcy dla kapitana portu, pieniądze są w komodzie.";
			link.l1 = "Zrozumiałem, panie Fleetwood. Idę zobaczyć się z kapitanem portu.";
			link.l1.go = "exit";	
			pchar.questTemp.HWIC.Eng = "GotoPortoffice";
			bDisableFastReload = false;//откроем быстрый переход
			DeleteAttribute(pchar, "questTemp.HWIC.CanTake");//иные варианты более невозможны
			AddLandQuestMark(characterFromId("SentJons_PortMan"), "questmarkmain");
		break;
		
		case "First_Task_3":
			DialogExit();
			pchar.questTemp.HWIC.TakeQuestShip = "true";//все ПУ недоступны для стоянки до поры, также корабль нельзя продать
			pchar.questTemp.HWIC.EngEquip = "true"; //форма солдат
			pchar.questTemp.HWIC.Eng = "GotoBridgetown";
			GetValckiriaToCharacter(pchar);
			pchar.quest.Knippel_Officer.win_condition.l1 = "location";
			pchar.quest.Knippel_Officer.win_condition.l1.location = "SentJons_houseSP3";
			pchar.quest.Knippel_Officer.function = "KnippelToOfficer";
			pchar.questTemp.HWIC.Eng.BridgeCounter = 0;//счетчик посещений неписей Бриджтауна по квесту
			AddQuestRecord("Holl_Gambit", "2-5");
			AddMapQuestMarkCity("Bridgetown", false);
			AddLandQuestMark(characterFromId("Bridgetown_trader"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_shipyarder"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_Mayor"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_tavernkeeper"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_usurer"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_PortMan"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_Hostess"), "questmarkmain");
		break;
		
		//изымаем корабль
		case "Fleetwood_lostMir":
			dialog.text = "Tak, wiem, że nie udało ci się schwytać pirackiego statku. Wszystkie moje plany są zrujnowane. Zabieram ci 'Valkyrię'. Możesz już odejść, nie potrzebuję twoich usług.";
			link.l1 = "Tak mi przykro z tego powodu. Żegnaj, panie Fleetwood.";
			link.l1.go = "Fleetwood_RemoveShip";
			pchar.questTemp.HWIC.Eng.ShipType = SHIP_VALCIRIA;
		break;
		
		case "Fleetwood_lostVal":
			dialog.text = "Tak, jestem świadomy, że straciłeś 'Valkyrię'. To było najbardziej nie do zaakceptowania... Zamierzam zabrać przejęty statek piracki. Możesz już iść, nie potrzebuję twoich usług.";
			link.l1 = "Przykro mi z tego powodu. Żegnaj, Panie Fleetwood.";
			link.l1.go = "Fleetwood_RemoveShip";
			pchar.questTemp.HWIC.Eng.ShipType = SHIP_MIRAGE;
		break;
		
		case "Fleetwood_lostFull":
			dialog.text = "Tak, jestem świadomy, że jesteś rzadkim partaczem i nieudacznikiem. Nie zdobyłeś pirackiego statku i straciłeś moją 'Walkirię'. Jestem naprawdę rozczarowany tobą. Wynoś się!";
			link.l1 = "Przykro mi z tego powodu. Żegnaj, panie Fleetwood.";
			link.l1.go = "exit";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex("Knippel");
			AddDialogExitQuestFunction("LandEnc_OfficerFired");//Книппеля из офицеров
			sld = characterFromId("Knippel");
			ChangeCharacterAddressGroup(sld, "SentJons_houseH1", "goto", "goto1");//Книппеля домой
			pchar.questTemp.HWIC.Eng = "end";
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.EngEquip");
			pchar.questTemp.HWIC.Detector = "eng_fail";
			AddSimpleRumourCity("They say that you have failed some secret assignment of Richard Fleetwood. Well, you have got nothing to do on Antigua now...", "SentJons", 20, 3, "");
		break;
		
		case "Fleetwood_RemoveShip":
			DialogExit();
			AddDialogExitQuestFunction("Fleetwood_RemoveShip");
			pchar.questTemp.HWIC.Eng = "end";
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.EngEquip");
			pchar.questTemp.HWIC.Detector = "eng_fail";
			AddSimpleRumourCity("They say that you have failed some secret assignment of Richard Fleetwood. Well, you have got nothing to do on Antigua now...", "SentJons", 20, 3, "");
		break;
		
		case "Fleetwood_complete":
			pchar.questTemp.HWIC.Eng.ShipType = SHIP_VALCIRIA;
			AddDialogExitQuestFunction("Fleetwood_RemoveShip");	
			if (CheckCharacterItem(pchar, "JacobJournal"))//проверяем журнал
			{
				dialog.text = "Tak, jestem świadomy, że odniosłeś sukces w naszym planie. Wyeliminowałeś nikczemnego pirata i przejąłeś jego statek. Jakie jest jego prawdziwe imię?";
				link.l1 = "Morgan Fate";
				link.l1.go = "Abigile";
			}
			else//нет журнала - нет продолжения квеста
			{
				dialog.text = "Tak, jestem świadomy, że udało ci się zrealizować nasz plan. Wyeliminowałeś nikczemnego pirata i przejąłeś jego statek. Odbiorę moją 'Walkirię'. Możesz zatrzymać piracki okręt jako zdobycz. Będzie to również służyć jako pewnego rodzaju... rekompensata. Twój zakotwiczony statek w porcie spłonął, gdy ogień na nabrzeżu zaczął się rozprzestrzeniać. Przepraszam za niedogodności, "+pchar.name+"... Mam nadzieję, że statek widmo posłuży ci lepiej.\nZleciłem, aby twój nowy statek został oczyszczony z uporczywego brudu i wodorostów. Ubiorą też twoją piękność w nowe żagle z najlepszego bawełny.\nNa koniec, proszę przyjmij swoją nagrodę w wysokości 100 000 peso i to narzędzie nawigacyjne. Zawsze chciałem je podarować godnemu żeglarzowi, a ty wykonałeś tam wspaniałą robotę! Cóż, nadszedł czas na pożegnanie, załatwiłem tutaj swoje sprawy i powinienem wrócić do Europy. Powodzenia, kapitanie!";
				link.l1 = "Nawzajem, Richard!";
				link.l1.go = "exit";
				LocatorReloadEnterDisable("SentJons_houseSP3", "reload2", true);//закроем Флитвуда в комнате и пусть там сидит
				pchar.questTemp.HWIC.Eng = "end";
				pchar.questTemp.HWIC.Detector = "eng_win_half";
				CloseQuestHeader("Holl_Gambit");
			}
			AddMoneyToCharacter(pchar, 100000);
			GiveItem2Character(pchar, "bussol");
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.EngEquip");
			AddSimpleRumourCity("Mówią, że ty i Richard Fleetwood zaplanowaliście jakąś operację militarną i osobiście zniszczyliście tego nieuchwytnego pirata, który rabował nasze statki handlowe. Jesteś prawdziwym bohaterem, kapitanie!", "SentJons", 20, 3, "");
		break;
		
		case "Abigile":
			dialog.text = "Mirage? Bardzo odpowiednia nazwa, powiedziałbym... Zamierzam odebrać moją 'Walkirię' od ciebie, a w zamian możesz zatrzymać statek piracki jako zdobycz. To będzie również pewnego rodzaju rekompensata. Twój zakotwiczony statek w porcie spłonął, gdy ogień zaczął się rozprzestrzeniać w dokach. Przykro mi, "+pchar.name+"... Mam nadzieję, że   statek widmo lepiej ci posłuży.\nNakazałem oczyścić twój nowy okręt z tego upartego brudu i wodorostów. Ubiorą też twoją piękność w nowe żagle z najlepszego bawełny.\nW końcu, przyjmij swoją nagrodę w wysokości 100 000 pesos oraz to narzędzie nawigacyjne, zawsze chciałem przekazać je godnemu żeglarzowi... Dobrze się spisałeś tam na zewnątrz i jestem z ciebie dumny! Czy masz dziennik bastard?";
			link.l1 = "Tak, oczywiście. Oto jest, weź to. Chcę cię o coś zapytać, czy wśród najemników Lucasa Rodenburga jest jakiś... Azjata?";
			link.l1.go = "Abigile_1";			
		break;
		
		case "Abigile_1":
			RemoveItems(PChar, "JacobJournal", 1);
			dialog.text = "Tak, jest. Chińczyk Longway, kapitan swojego prywatnego statku 'Meifeng'. Czy przeczytałeś to z dziennika pirata? Spójrzmy...(czytając) No, no. Jak się spodziewałem, Lucas Rodenburg stał za tym wszystkim! Cóż, nieważne, to nie jest nasza sprawa teraz... Nasz gubernator-general poradzi sobie z tym łajdakiem. Lucas Rodenburg będzie musiał wziąć odpowiedzialność za wszystko, co zrobił!";
			link.l1 = "Hm, interesujące, a jak angielski gubernator generalny zdoła 'rozprawić się' z poddanym Holandii?";
			link.l1.go = "Abigile_2";			
		break;
		
		case "Abigile_2":
			dialog.text = "Zawsze istnieją polityczne nici do pociągnięcia, mój drogi przyjacielu... Holandia będzie musiała przyznać, że rozpoczęła wojnę handlową z Anglią, ale jest mało prawdopodobne, że to zrobią. Zamiast tego, obwinią za wszystko Rodenburga. Lucas może stracić swoją pozycję, albo i nie. Tak czy inaczej, jego kariera dozna ciężkiego ciosu.\nJednak to nie nasza sprawa teraz, kapitanie. Dobrze wykonałeś swoją część zadania. Dlatego mam dla ciebie kolejną bardzo delikatną sprawę.";
			link.l1 = "Słucham, Richardzie. Kto tym razem będzie następnym wrogiem angielskiej korony do zniszczenia?";
			link.l1.go = "Abigile_3";			
		break;
		
		case "Abigile_3":
			dialog.text = "Nie, tym razem chcę poprosić cię o zajęcie się bardziej osobistą i pokojową sprawą. Pozwól, że opowiem ci krótką historię, która dotyczy przy okazji twojego 'Mirage'.";
			link.l1 = "Idź dalej.";
			link.l1.go = "Abigile_4";			
		break;
		
		case "Abigile_4":
			dialog.text = "Byłem na rajdzie, polując na statek widmo miesiąc przed tym, jak się spotkaliśmy. To było na południe od Martyniki, niedaleko długości geograficznej 64 st. 41'. Usłyszeliśmy, że gdzieś w oddali trwa walka, ale wiatr był zbyt słaby, więc nie zdążyliśmy na czas. Angielski flet został zatopiony przez statek widmo w pobliżu jakiejś małej wyspy, która nawet nie jest zaznaczona na mapie.\nNie udało mi się złapać pirata i postanowiłem odwiedzić tę wyspę, mając nadzieję znaleźć jakichś ocalałych. I znalazłem ich. Parę żydowskich uchodźców, ojca i córkę. Dziewczyna nazywała się Abigail i była piękna! Żywy cud... Wziąłem ich na pokład i dostarczyłem do Curacao, chociaż jej ojciec, Salomon, nie okazał mi zbyt wiele sympatii.\nJak zrozumiałem, myślał, że to ja byłem piratem, który zatopił ich statek, stary człowiek niewiele wie o statkach i różnicach między nimi. Podczas tej małej podróży ja i Abigail staliśmy się przyjaciółmi, a mówiąc całkowicie szczerze, zakochaliśmy się w sobie. Czyż to nie historia?\nI niedawno dowiedziałem się, że drań Rodenburg od jakiegoś czasu zaleca się do mojej Abigail, pomyśl tylko! Zamierzałem ją tu przywieźć, gdy tylko rozwiążę sprawę dotyczącą zaginionych pieniędzy jej ojca, schował każdą monetę, jaką miał, na tej wyspie, o której wspomniałem. Nie udało mi się znaleźć jej lokalizacji. Nie możemy dłużej czekać.\nPonieważ moje zdrowie wciąż nie pozwala mi samemu wyruszyć w morze, proszę cię, abyś udał się do Willemstad, znalazł Abigail i przyprowadził ją tutaj. Wspomnij moje imię, a ona ci zaufa.";
			link.l1 = "Nie widzę żadnych problemów w tej sprawie. Jestem gotów do wypłynięcia teraz.";
			link.l1.go = "Abigile_5";			
		break;
		
		case "Abigile_5":
			PlaySound("Voice\English\hambit\Richard Flitwood-02.wav");
			dialog.text = "Doskonałe! Cieszę się, że mogę na ciebie liczyć, "+pchar.name+". Twoja praca zostanie dobrze wynagrodzona, nie martw się o to.";
			link.l1 = "Nie każę ci długo czekać. Do zobaczenia wkrótce, Richard!";
			link.l1.go = "Abigile_6";			
		break;
		
		case "Abigile_6":
			DialogExit();
			npchar.greeting = "fleetwood_2";
			LocatorReloadEnterDisable("Villemstad_town", "houseSP2", false);//откроем дом Аби
			LocatorReloadEnterDisable("Villemstad_houseSp2", "reload2", true);//закроем спальню Аби
			AddQuestRecord("Holl_Gambit", "2-16");
			pchar.questTemp.HWIC.Eng = "toAbigile";
			sld = characterFromId("Bridgetown_tavernkeeper");
			sld.model = "barmen_3";
			sld.name = "Harry";
			sld.lastname = "Fletcher";//перерисуем бармена Бриджтауна
			sld.greeting = "barmen_1";
			sld = characterFromId("Solomon");
			sld.greeting = "solomon_2";
			AddLandQuestMark(sld, "questmarkmain");
			AddMapQuestMarkCity("Villemstad", false);
		break;
		
		case "Fleetwood_LastTask":
			dialog.text = ""+pchar.name+",  czy naprawdę zdecydowałeś się odnaleźć wyspę? Jestem pod wrażeniem twojej hojności. Czy ją znalazłeś?";
			link.l1 = "Tak, zrobiłem to. Niestety, tutaj zaczynają się złe wieści. Ledwo uciekłem z tego przeklętego miejsca... Wciąż drżę, gdy o tym myślę...";
			link.l1.go = "Fleetwood_LastTask_1";
		break;
		
		case "Fleetwood_LastTask_1":
			dialog.text = "Co tam się wydarzyło? Powiedz mi, przyjacielu, nie trzymaj mnie w niepewności!";
			link.l1 = "Przybyłem na wyspę i skierowałem się do groty, gdzie Salomon prawdopodobnie schował swoją skrzynię. Faktycznie tam była. Ale kiedy jej dotknąłem, jakaś nieznana siła wyrzuciła mnie w górę. Usłyszałem wybuch i zostałem rzucony na ziemię dziesięć stóp od skrzyni...";
			link.l1.go = "Fleetwood_LastTask_2";
		break;
		
		case "Fleetwood_LastTask_2":
			dialog.text = "Niesamowite!";
			link.l1 = "Ledwo to przeżyłem - mam kilka bolesnych zadrapań. Gdy odzyskiwałem przytomność, przerażające dźwięki huczały w mojej głowie i straszliwa kreatura wyłoniła się prosto z ziemi... o Boże, ten potwór!";
			link.l1.go = "Fleetwood_LastTask_3";
		break;
		
		case "Fleetwood_LastTask_3":
			dialog.text = ""+pchar.name+"... ";
			link.l1 = "Richard, nie jestem szalony. To naprawdę się wydarzyło, choć sam ledwo w to wierzę. To było całkowicie wysuszone i pomalowane zwłoki Indianina z pękiem piór na głowie. Ten potwór coś zagrzmiał, potem wyciągnął ogromną indiańską maczugę i zaatakował mnie!";
			link.l1.go = "Fleetwood_LastTask_4";
		break;
		
		case "Fleetwood_LastTask_4":
			dialog.text = "";
			link.l1 = "Na Boga... Wciąż nie mogę pojąć, jak udało mi się poradzić sobie z tą rzeczą... Uderzyłem ją tyle razy, że wystarczyłoby to, by zabić tuzin ludzi, a ona wciąż stała... Gdy odzyskałem oddech, otworzyłem ten przeklęty kufer... Nie było w nim pieniędzy, ale zamiast tego było coś innego. Spójrz, bardzo intrygujący przedmiot!";
			link.l1.go = "Fleetwood_LastTask_5";
		break;
		
		case "Fleetwood_LastTask_5":
			RemoveItems(PChar, "GastonHead", 1);
			dialog.text = "B-r-r... okropne..."+pchar.name+", czekaj... to na pewno on! To głowa łajdaka, który próbował mnie zabić, oślepiając pieprzem!";
			link.l1 = "Znasz go? Nazywa się Gaston, barman z Bridgetown i zwolennik van Berga, kapitana statku-widmo. Rozpoznałem go od razu, ale nie wiem, kto go zabił i jak jego odcięta głowa znalazła się w skrzyni Salomona na nieznanej wyspie!";
			link.l1.go = "Fleetwood_LastTask_6";
		break;
		
		case "Fleetwood_LastTask_6":
			dialog.text = "Masz rację, to naprawdę przerażająca i tajemnicza historia. Mistyczna...";
			link.l1 = "Dokładnie. Nie było sensu wracać do Abigail z powodu braku pieniędzy. Więc jestem tutaj, aby ci o tym opowiedzieć. Być może ty, Richard, zrozumiesz coś z tego bałaganu...";
			link.l1.go = "Fleetwood_LastTask_7";
		break;
		
		case "Fleetwood_LastTask_7":
			dialog.text = "Ja? Nic tu nie rozumiem, tak jak ty... Ale mogę ci coś powiedzieć na pewno - mam złe przeczucia co do tego..."+pchar.name+", posłuchaj mnie teraz. Idź i sprawdź Bridgetown, aby upewnić się, że... Gaston zniknął na dobre. Następnie proszę cię, abyś przybył do Laguny Blanca na Curaçao za 20 dni. Charlie Knippel będzie tam na ciebie czekał. Zbiorę pieniądze dla ojca Abigail. Dam je Charliemu, a ty zaniesiesz je Solomonowi i dostarczysz Abigail na Antiguę. Tym razem nie będzie przeszkód, musisz to zrozumieć. Idź, mój przyjacielu!";
			link.l1 = "Dobrze, Richard. Natychmiast postawię żagle.";
			link.l1.go = "Fleetwood_LastTask_8";
		break;
		
		case "Fleetwood_LastTask_8":
			DialogExit();
			pchar.questTemp.HWIC.Eng = "toBarbados";
			AddQuestRecord("Holl_Gambit", "2-21");
			SetFunctionTimerCondition("HWICEng_toBarbadosOver", 0, 0, 20, false);//чтобы не тянули
			AddSimpleRumourCity("Och, kapitanie, słyszałem, że Richard Fleetwood naprawdę cię podziwia. Uwierz mi, jego pochwały kosztują dużo. Musisz być bardzo ważną osobą...", "SentJons", 20, 3, "");
			AddMapQuestMarkCity("Bridgetown", false);
			AddLandQuestMark(characterFromId("Bridgetown_tavernkeeper"), "questmarkmain");
		break;
		
//---------------------------------------------против всех-----------------------------------------------
		
		case "InTerksShore":
			DelLandQuestMark(npchar);
			pchar.quest.Fleetwood_ShoreOver.over = "yes";//снять таймер
			dialog.text = "Domyślam się, że to ty jesteś łajdakiem, który porwał moją Abigail. Charlie nie wrócił do mnie, więc to również twoja wina.";
			link.l1 = "Masz rację, panie Fleetwood. To ja. Charlie pomógł mi wkraść się w zaufanie Abigail dzięki listowi, który do niej napisałeś. Ale przejdźmy od razu do interesów... Czy przyniosłeś pieniądze?";
			link.l1.go = "InTerksShore_1";
		break;
		
		case "InTerksShore_1":
			dialog.text = "Mam. Ale najpierw chcę zobaczyć Abigail. Muszę być pewien, że jest żywa i nietknięta, ponieważ nie zamierzam ufać słowu bękarta.";
			link.l1 = "Czyż nie sądzisz, panie, że nie jesteś w pozycji, by dyktować swoje warunki?";
			link.l1.go = "InTerksShore_2";
			// belamour legendary edition -->
			link.l2 = "Nie chcę już grać w tę grę. Abi zostanie ze mną, a ty zostajesz na tej plaży! Ognia!";
			link.l2.go = "InTerksShore_2a";
		break;

		case "InTerksShore_2a"://массовая драка на необитаемом острове
			AddCharacterExpToSkill(pchar, "FencingL", 60);
			AddCharacterExpToSkill(pchar, "FencingS", 60);
			AddCharacterExpToSkill(pchar, "FencingH", 60);
			AddCharacterExpToSkill(pchar, "Pistol", 60);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=3; i++)//офицеры Флитвуда
			{
				sld = characterFromId("FlOfficer_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			for (i=1; i<=7; i++)//засада Флитвуда
			{
				sld = GetCharacter(NPC_GenerateCharacter("EnemySailor_"+i, "sold_eng_"+i, "man", "man", 18, ENGLAND, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, 18, 30, 30, "blade_19", "pistol2", "bullet", 40);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				if (i >= 1 && i < 3) ChangeCharacterAddressGroup(sld, "Shore56", "goto", "goto2");
				else ChangeCharacterAddressGroup(sld, "Shore56", "goto", "goto9");
			}
			for (i=1; i<=7; i++)//наши - к бою!
			{
				sld = characterFromId("OwrSailor_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "FleetwoodDiedInShore");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;

		case "InTerksShore_2":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			// <-- legendary edition
			dialog.text = "Rozumiem to, ale też nie jestem głupcem. Nie ma mowy o pieniądzach, dopóki nie zobaczę Abigail. I co z tego? Czekam.";
			link.l1 = "Dobrze. Teraz nadszedł czas, by wyłożyć karty na stół, Kapitanie Fleetwood. Zorganizowałem nasze spotkanie tutaj nie z powodu pieniędzy. Cóż, oczywiście, chciałbym je wziąć, ale najpierw potrzebuję ciebie.";
			link.l1.go = "InTerksShore_3";
		break;
		
		case "InTerksShore_3":
			dialog.text = "Ja? To staje się coraz bardziej interesujące... Myślę, że zaczynam rozumieć, co się tu naprawdę dzieje. Powiedz mi, czy Abigail żyje? Ona żyje, czy ją zamordowałeś, draniu?";
			link.l1 = "Przypuszczam, że zostawię cię w niewiedzy co do jej losu. Jedno tylko musisz wiedzieć - jej tu nie ma. Odegrała swoją rolę znakomicie, jesteś teraz w moich rękach. Miłość to takie cudowne uczucie... Jakżebym inaczej wywabił lisa z jego nory na otwartą przestrzeń? Ha-ha-ha!";
			link.l1.go = "InTerksShore_4";
		break;
		
		case "InTerksShore_4":
			dialog.text = "Nie ciesz się tak prędko, łajdaku. Zorganizowałem ci piękne powitanie na tej wyspie i nie wiadomo, kto jest w czyich rękach! Więc przygotuj się, masz mi wiele do powiedzenia - o Abigail, o Charliem, zapłacisz za to, że ich skrzywdziłeś!";
			link.l1 = "Już drżę ze strachu! Czas zakończyć naszą rozmowę, panie. Przygotuj się na piekło, bo w niebie nie ma dla ciebie miejsca.";
			link.l1.go = "InTerksShore_5";
		break;
		
		case "InTerksShore_5"://массовая драка на необитаемом острове
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=3; i++)//офицеры Флитвуда
			{
				sld = characterFromId("FlOfficer_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			for (i=1; i<=7; i++)//засада Флитвуда
			{
				sld = GetCharacter(NPC_GenerateCharacter("EnemySailor_"+i, "sold_eng_"+i, "man", "man", 18, ENGLAND, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, 18, 30, 30, "blade_19", "pistol2", "bullet", 40);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				if (i >= 1 && i < 3) ChangeCharacterAddressGroup(sld, "Shore56", "goto", "goto2");
				else ChangeCharacterAddressGroup(sld, "Shore56", "goto", "goto9");
			}
			for (i=1; i<=7; i++)//наши - к бою!
			{
				sld = characterFromId("OwrSailor_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "FleetwoodDiedInShore");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
	}
}

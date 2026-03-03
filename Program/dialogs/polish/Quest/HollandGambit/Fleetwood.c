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
					dialog.text = "Czołem, kapitanie! Niech cię tylko nie zmyli mój wygląd. Mam się dobrze. No, prawie... moje oko coś odmawia współpracy i nie widzę zbyt dobrze. Ale to nic. Pozwól, że się przedstawię, jestem Richard Fleetwood.";
					link.l1 = "Dzień dobry. Miło cię poznać, jestem kapitan "+GetFullName(pchar)+".";
					link.l1.go = "First_Task";
					DelLandQuestMark(npchar);
					break;
				}
				if (pchar.questTemp.HWIC.Eng == "GotoPortoffice")
				{
					if (sti(Pchar.Ship.Type) != SHIP_NOTUSED)
					{
						dialog.text = "Przecież prosiłem cię, byś zacumował swój statek... Czy w ogóle mnie słuchasz?!";
						link.l1 = "Oczywiście, że tak. Pracuję nad tym.";
						link.l1.go = "exit";
					}
					else
					{
						dialog.text = "A więc znów tu jesteś. Doskonale. Teraz przejmij, proszę dowodzenie nad 'Valkyrią' - moja załoga została już o wszystkim poinformowana. A potem chce, byś popłynął do Bridgetown. Odwiedź każdą ważną i wpływową osobę w tym mieście i rozsiej plotki, o których rozmawialiśmy. Wiesz, ludzie to straszne gaduły. Następnie bądź gotów na atak tego drania. Tylko nie zmieniaj statku i nie twórz eskadry, inaczej skapną się, że to zasadzka i nasz cel się nie pojawi.\nTwoim zadaniem jest przejąć jego statek i dostarczyć prosto do St. John. Najważniejsze jest to, byś odnalazł dziennik tego pirata, bo to jedyny dowód, jaki będziemy mieć na udział Lucasa Rodenburga. Pamiętaj o tym. Jestem pewien, że sobie z tym poradzisz. Powodzenia, kapitanie.";
						link.l1 = "Dzięki, przyda się. Nie martw się, wykonam zadanie i wrócę tu zarówno ze statkiem jak i dziennikiem. Do widzenia.";
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
						dialog.text = "Widzę, że wróciłeś, kapitanie... Ale tak się składa, że wiem już wszystko o twoich przygodach.";
						link.l1 = "Czyżby? Więc musisz wiedzieć, że...";
						link.l1.go = "Fleetwood_lostVal";
						DelLandQuestMark(npchar);
						DelMapQuestMarkCity("SentJons");
						break;
					}
					if (iMir == 0 && iVal == 1)//потеряли Мираж
					{
						dialog.text = "Widzę, że wróciłeś, kapitanie... Ale tak się składa, że wiem już wszystko o twoich przygodach.";
						link.l1 = "Czyżby? Więc musisz wiedzieć, że...";
						link.l1.go = "Fleetwood_lostMir";
						DelLandQuestMark(npchar);
						DelMapQuestMarkCity("SentJons");
						break;
					}
					if (iMir == 0 && iVal == 0)//а это вообще плохо
					{
						dialog.text = "Widzę, że wróciłeś, kapitanie... Ale tak się składa, że wiem już wszystko o twoich przygodach.";
						link.l1 = "Czyżby? Więc musisz wiedzieć, że...";
						link.l1.go = "Fleetwood_lostFull";
						DelLandQuestMark(npchar);
						DelMapQuestMarkCity("SentJons");
						break;
					}
						dialog.text = "Widzę, że wróciłeś, kapitanie... Ale tak się składa, że wiem już wszystko o twoich przygodach.";
						link.l1 = "Naprawdę? Więc musisz wiedzieć, że...";
					link.l1.go = "Fleetwood_complete";
					DelLandQuestMark(npchar);
					DelMapQuestMarkCity("SentJons");
					break;
				}
				if (pchar.questTemp.HWIC.Eng == "toAntigua")
				{
					dialog.text = "Witaj, mój przyjacielu! Cieszę się, że cię widzę! Czy Abigail jest na twoim statku?";
					link.l1 = "Niestety nie, Richardzie... Nie chciała za mną iść, bo to byłoby straszliwym ciosem dla jej ojca, Salomona, który i tak już wiele wycierpiał przez utratę majątku. Dlatego zdecydowałem, że najpierw odnajdę pieniądze Salomona oraz tę tajemniczą wyspę...";
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
			dialog.text = "Przeklęty piracie! Może i wygrałeś, ale i tak zrobię, co do mnie należy! Podpaliłem prochownie - zaraz wszystko wyleci w powietrze, razem z twoim przeklętym 'Statkiem Widmo'! Już nigdy więcej nie zatopisz angielskiego statku! Zginę z honorem!";
			link.l1 = "W takim razie muszę cię rozczarować, Fleetwood. Mylisz się - na moim statku nie ma piratów. Już się ich pozbyłem. Potrzebowałem tylko ciebie, a ten okręt posłużył jako przynęta. Ha-ha! \nAle Dość uprzejmości. Nie ma czasu, skoro ta łajba ma wybuchnąć. En garde!";
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
			dialog.text = "Charlie już mi doniósł o twoim sukcesie w przechwyceniu wrogiego konwoju. Cieszę się, że mogę cię wreszcie poznać. Anglia potrzebuje takich odważnych kapitanów. A teraz pozwól, że przejdę do rzeczy - do spraw najwyższej wagi.";
			link.l1 = "Słucham, panie Fleetwood.";
			link.l1.go = "First_Task_1";			
		break;
		
		case "First_Task_1":
			dialog.text = "
			Po całym archipelagu grasuje pirat, który podszywa się pod 'Latającego Holendra', ten legendarny statek-widmo. Tak właśnie sam siebie nazywa - 'Latający Holender'. Ale zapewniam cię, że ten łajdak nie potrafi latać. Podejrzewam, że to może być najemnik Lucasa Rodenburga, wicedyrektora Holenderskiej Kompanii Zachodnioindyjskiej. \nRodenburg ogłosił cichą wojnę handlową przeciwko Anglii - ten 'statek widmo' atakuje tylko i wyłącznie statki pod angielską banderą. Nic dziwnego - Kompania za wszelką chce osłabić nasz wpływ na Karaibach i jednocześnie nie musieć prowadzić prawdziwej wojny, która przecież kosztuje. \nŚcigam 'Latająceho Holendra' od jakiegoś czasu, ale jego kapitan to cholernie doświadczony żeglarz, a sam statek jest szybki i zwrotny. \nSkoro nie da się go dorwać w otwartej walce, powinniśmy przyjąć bardziej przebiegłą taktykę. A ta próba zamachu na moje życie może się nam całkiem dobrze przydać, wiesz?";
			link.l1 = "Cóż, z przyjemnością pomogę ci wytropić i zatopić tego drania. Zresztą i tak zamierzałeś mnie o to poprosić, prawda?";
			link.l1.go = "First_Task_2";	
		break;
		
		case "First_Task_2":
			dialog.text = "Masz rację. Dlatego skoro mamy to już za sobą, to omówmy szczegóły. Moi ludzie właśnie rozpuszczą plotki, że jestem na łożu śmierci i sprzedałem ci moją 'Valkyrię'. A teraz nasze małe oszustwo: ty odegrasz rolę kupca, który właśnie nabył ten statek i... rozbroił ją, wywalając z niej większość armat. \nTwoim zadaniem jest popłynąć na Barbados i głośno opowiedzieć tam wszystkim, że twój bezbronny statek jest wypełniony po brzegi jakimś cennym towarem, a ty sam masz mnóstwo monet. Potwarzaj też, że zaraz zamierzasz wypłynąć. Wciel się w rolę chciwego, bogatego kupca, który nie może się powstrzymać od przechwał na temat swojego bogactwa i chęci zysku. \nNasz pieprzony Holender zbiera informacje o statkach handlowych właśnie przy Bridgetown. Nie wiadomo tylko, kto dokładnie mu je dostarcza. Każdy jest podejrzany - od lokalnego kupca aż po samego gubernatora, choć ta ostatnia możliwość budzi największy niepokój. \nPrzejmij dowodzenie nad moją 'Valkyrie' i jej załogą. Ale najpierw musisz zostawić tu wszystkie swoje statki - już rozmawiałem z urzędnikiem portowym. Przechowanie statku będzie kosztować 10 000 pesos miesięcznie. \nGdy to załatwisz, wróć tu do mnie, a ja się tym zajmę. Ach, kapitanie, no i nie zapomnij odebrać swojej nagrody za przechwycenie srebrnej karawany. Natomiast pieniądze dla urzędnika znajdziesz tutaj, w komodzie.";
			link.l1 = "Zrozumiałem, panie Fleetwood. Idę zobaczyć się z zarządcą portu.";
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
			dialog.text = "Tak, wiem, że spieprzyłeś robotę i nie masz tego statku. Teraz wszystkie moje plany szlag trafił! Zabieram ci 'Valkyrię'. Możesz już odejść, nie potrzebuję twoich usług.";
			link.l1 = "Tak mi przykro z tego powodu... Żegnaj, panie Fleetwood.";
			link.l1.go = "Fleetwood_RemoveShip";
			pchar.questTemp.HWIC.Eng.ShipType = SHIP_VALCIRIA;
		break;
		
		case "Fleetwood_lostVal":
			dialog.text = "Tak, jestem świadomy, że straciłeś moją 'Valkyrię'. Z tym najbardziej nie mogłem się pogodzić... W takim razie zabiorę przejęty statek. Możesz już iść, nie potrzebuję twoich usług.";
			link.l1 = "Przykro mi z tego powodu... Żegnaj, Panie Fleetwood.";
			link.l1.go = "Fleetwood_RemoveShip";
			pchar.questTemp.HWIC.Eng.ShipType = SHIP_MIRAGE;
		break;
		
		case "Fleetwood_lostFull":
			dialog.text = "Tak, jestem tego świadomy - jesteś żałosnym nieudacznikiem i partaczem bez grama honoru! Nie tylko spieprzyłeś sprawę z pirackiem statkiem, to jeszcze straciłeś moją 'Valkirię'. Jak mogłem zaufać takiemu skończonemu kretynowi?! Żałuję dnia, gdy ci zaufałem. Wynoś się stąd!";
			link.l1 = "Przykro mi z tego powodu... Żegnaj, panie Fleetwood.";
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
			AddSimpleRumourCity("Mówią, że nie zdołałeś wypełnić jakiejś tajnej misji od Richarda Fleetwoda. W takim razie już nie masz co robić na Antigui...", "SentJons", 20, 3, "");
		break;
		
		case "Fleetwood_RemoveShip":
			DialogExit();
			AddDialogExitQuestFunction("Fleetwood_RemoveShip");
			pchar.questTemp.HWIC.Eng = "end";
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.EngEquip");
			pchar.questTemp.HWIC.Detector = "eng_fail";
			AddSimpleRumourCity("Mówią, że nie zdołałeś wypełnić jakiejś tajnej misji od Richarda Fleetwoda. W takim razie już nie masz co robić na Antigui...", "SentJons", 20, 3, "");
		break;
		
		case "Fleetwood_complete":
			pchar.questTemp.HWIC.Eng.ShipType = SHIP_VALCIRIA;
			AddDialogExitQuestFunction("Fleetwood_RemoveShip");	
			if (CheckCharacterItem(pchar, "JacobJournal"))//проверяем журнал
			{
				dialog.text = "Tak, już o tym wiem, że wypełniłeś swoją misję. Wyeliminowałeś nikczemnego pirata i przejąłeś jego statek. Jakaj jest jego prawdziwa nazwa?";
				link.l1 = "Fata Morgana";
				link.l1.go = "Abigile";
			}
			else//нет журнала - нет продолжения квеста
			{
				dialog.text = "Tak, już o tym wiem, że udało ci się zrealizować nasz plan. Wyeliminowałeś nikczemnego pirata i przejąłeś jego statek. Odbiorę moją 'Valkirię'. A co do pirackiego statku... Możesz go sobie zatrzymać jako łup. Posłuży to jako pewnego rodzaju... cóż, rekompensata. Nie spodoba ci się to, kapitanie, ale... \nNiedawno w mieście wybuchł pożar - do jego ofiar należy także twój statek. Spłonął w porcie, gdy tylko ogień zaczął się rozprzestrzeniać. Bardzo mi przykro, sir. I przepraszam za niedogodności, "+pchar.name+"... Mam nadzieję, że statek widmo posłuży ci lepiej. Już zleciłem, by go wyczyścili z całego tego brudu i wodorostów. Statek dostanie też nowe żagle z najlepszego rodzaju bawełny. \nA poza tym, przyjmij proszę  swoją nagrodę w wysokości 100 000 peso, a także ten przyrząd nawigacyjny. Zawsze chciałem oddać go w ręce jakiegoś godnego kapitana - ty odwaliłeś kawał dobrej roboty, więc od teraz będzie twój. A teraz nadszedł czas na pożegnanie, właśnie kończę załatwiać tu swoje sprawy i już zaraz wyruszam do Europy. Powodzenia, kapitanie!";
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
			AddSimpleRumourCity("Mówią, że ty i Richard Fleetwood zniszczyliście tą nieuchwytną szumowitę, który terroryzował naszych kupców. Podobno dokonałeś to osobiście. Jesteś prawdziwym bohaterem, kapitanie!", "SentJons", 20, 3, "");
		break;
		
		case "Abigile":
			dialog.text = "'Mirage'? Cóż, to bardzo trafna nazwa... W takim razie przejmę z powrotem 'Valkirię', a ty możesz zatrzymać sobie ten piracki statek. To będzie również pewnego rodzaju... cóż, rekompensata. Nie spodoba ci się to, kapitanie, ale... \nNiedawno w mieście wybuchł pożar - do jego ofiar należy także twój statek. Spłonął w porcie, gdy tylko ogień zaczął się rozprzestrzeniać. Bardzo mi przykro, sir. I przepraszam za niedogodności, "+pchar.name+"... Mam nadzieję, że statek widmo posłuży ci lepiej. Już zleciłem, by go wyczyścili z całego tego brudu i wodorostów. Statek dostanie też nowe żagle z najlepszego rodzaju bawełny. \nA poza tym, przyjmij proszę  swoją nagrodę w wysokości 100 000 peso, a także ten przyrząd nawigacyjny. Zawsze chciałem oddać go w ręce jakiegoś godnego kapitana - ty odwaliłeś kawał dobrej roboty, więc od teraz będzie twój. Jestem z ciebie dumny. A czy masz dziennik tego bękarta?";
			link.l1 = "Tak, oczywiście. Oto on. A tak przy okazji, chcę cię o coś zapytać. Czy wśród najemników Lucasa Rodenburga jest jakiś... Azjata?";
			link.l1.go = "Abigile_1";			
		break;
		
		case "Abigile_1":
			RemoveItems(PChar, "JacobJournal", 1);
			dialog.text = "Tak, jest. Chińczyk Longway, kapitan prywatnego statku 'Meifeng'. Jak rozumiem wyczytałeś to tego dziennika? Spójrzmy... (czytając) No, no. A więc jest tak, jak się spodziewałem! To Lucas Rodenburg stał za tym wszystkim! Zresztą teraz to już nieważne - to nie nasza sprawa... to gubernator generalny poradzi sobie z tym łajdakiem. Lucas Rodenburg będzie musiał wziąć odpowiedzialność za wszystko, czego się dopuścił!";
			link.l1 = "Hmm, to ciekawe, tylko że jak angielski gubernator generalny zdoła 'rozprawić się' z poddanym Holandii?";
			link.l1.go = "Abigile_2";
		break;
		
		case "Abigile_2":
			dialog.text = "Zawsze istnieją polityczne nici do pociągnięcia, mój drogi przyjacielu... Prawda jest taka, że w teraz Holandia będzie musiała przyznać się do tego, że rozpoczęła wojnę handlową z Anglią. Wątpie jednak, że to zrobią. Zamiast tego, pewno zwalą całą winę na Rodenburga. Lucas może stracić swoją pozycję, choć kto wie? Tak czy inaczej, ten kariera tego człowieka bardzo na tym ucierpi. \nJednak to już nie nasza sprawa. Dobrze wykonałeś swoją część zadania. Dlatego mam dla ciebie kolejną bardzo delikatną sprawę.";
			link.l1 = "Słucham, Richardzie. Kto tym razem będzie następnym celem angielskiej korony?";
			link.l1.go = "Abigile_3";			
		break;
		
		case "Abigile_3":
			dialog.text = "Nie, tym razem akurat poproszę cię o zajęcie się czymś bardziej osobistym i pokojowym. Pozwól, że opowiem ci krótką historię, która przy okazji dotyczy też twojego 'Mirage'.";
			link.l1 = "Kontynuuj..";
			link.l1.go = "Abigile_4";			
		break;
		
		case "Abigile_4":
			dialog.text = "Miesiąc przed naszym spotkaniem sam wypłynąłem, by dorwać ten statek-widmo. To było trochę na południe od Martyniki, w okolicach 64°41' długości geograficznej. W pewnym momencie usłyszeliśmy odgłosy walki, ale niestety - wiatr był zbyt słaby, więc nie dotarliśmy tam na czas. Angielska fluita została zatopiona przez ten przeklęty okręt w pobliżu jakiejś małej wyspy, która nie widnieje na żadnej mapie. \nNie zdołałem dopaść tego drania, ale rozejrzałem się po tej wyspie z nadzieją, że znajdę jakichś ocalałych.I znalazłem ich. Dwójkę żydowskich uchodźców, ojca i córkę. Dziewczyna nazywała się Abigail i rany, była tak oszałamiająco piękna... Prawdziwy klejnot. Zabrałem ich na pokład i odstawiłem do Curacao, choć jej ojciec, Salomon, nie darzył mnie zbytnią sympatią. \nJak zrozumiałem, podejrzewał, że to ja zatopiłem ich statek. Stary człowiek nie zna się na statkach i nie dostrzega różnic między nimi. W trakcie tego krótkiego rejsu zaprzyjaźniłem się z Abigail. A mówiąc wprost: zakochaliśmy się w sobie. Piękna historia, prawda?\n Natomiast niedawno dowiedziałem się, że ten łotr Rodenburg od jakiegoś czasu zabiega o względy mojej Abigail... Wyobrażasz to sobie?! Dlatego chciałem ją tu przywieźć, jak tylko odzyskam pieniądze jej ojca — ukrył cały swój majątek na tej wyspie, o której wspomniałem. Niestety, moje poszukiwania spełzły na niczym. A teraz nie możemy już dłużej zwlekać.\n Moje zdrowie wciąż nie pozwala mi wypłynąć... Dlatego proszę cię: udaj się do Willemstad, znajdź Abigail i przyprowadź ją do mnie. Wspomnij moje imię - zaufa ci.";
			link.l1 = "Oczywiśnie, mogę to załatwić. Wypłynę jak najszybciej!";
			link.l1.go = "Abigile_5";			
		break;
		
		case "Abigile_5":
			PlaySound("Voice\English\hambit\Richard Flitwood-02.wav");
			dialog.text = "Doskonałe! Cieszę się, że mogę na ciebie liczyć, "+pchar.name+". I nie martw się, zostaniesz za to sowicie wynagrodzony.";
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
			dialog.text = "Naprawdę się na to zdecydowałeś, "+pchar.name+"? Czy znalazłeś wyspę? Jestem pod wrażeniem... Twoja determinacja zasługuje na uznanie. Ale czy udało się? Znalazłeś ją?";
			link.l1 = "Tak, odnalazłem. Ale tutaj zaczynają się złe wieści. Cholera, ledwo uszedłem stamtąd życiem... Co robyło, rany. Wciąż przechodzą mnie dreszcze, gdy o tym myślę...";
			link.l1.go = "Fleetwood_LastTask_1";
		break;
		
		case "Fleetwood_LastTask_1":
			dialog.text = "Tak? Co się tam stało?  Opowiadaj, przyjacielu! Nie trzymaj mnie w niepewności!";
			link.l1 = "Dotarłem na wyspę i od razu ruszyłem do tamtejszej groty. Napewniej właśnie tam Salomon schował swoją skrzynię. I faktycznie - była tam.  Ale gdy tylko jej dotknąłem... Boże, co to było (czyni znak krzyża). Jakaś niewidzialna siła uniosła mnie w powietrze! Usłyszałem huk, a potem coś rzuciło mną o ziemię, dobre trzy metry od dalej...";
			link.l1.go = "Fleetwood_LastTask_2";
		break;
		
		case "Fleetwood_LastTask_2":
			dialog.text = "Nie do wiary...";
			link.l1 = "Chyba tylko cudem to przeżyłem. Parę bolesnych ran, siniaki... ale najgorsze przyszło potem. Gdy dochodziłem do siebie, usłyszałem jakieś upiorne, dudniące dźwięki... i wtedy pojawiło się TO. Bóg jeden wie, co to było! Jakaś piekielkna kreatura! Wypełzła prosto z ziemi i... Boże Święty, ten potwór!";
			link.l1.go = "Fleetwood_LastTask_3";
		break;
		
		case "Fleetwood_LastTask_3":
			dialog.text = ""+pchar.name+"... ";
			link.l1 = "Richard, nie jestem szalony. To naprawdę się wydarzyło, choć sam ledwo w to wierzę. To coś wyglądało jak wysuszone, pomalowane ścierwo Indianina z pękiem piór na głowie. I... i wrzasnął coś niezrozumiałego, potem sięgnął po ogromną, prymitywną maczugę i rzucił się na mnie! To było całkowicie wysuszone i pomalowane zwłoki Indianina z pękiem piór na głowie. Ten potwór coś zagrzmiał, potem wyciągnął ogromną indiańską maczugę i zaatakował mnie!";
			link.l1.go = "Fleetwood_LastTask_4";
		break;
		
		case "Fleetwood_LastTask_4":
			dialog.text = "";
			link.l1 = "Na Boga... Wciąż nie mogę pojąć, jak udało mi się to coś załatwić... Nawalałem w to tyle razy, że wystarczyłoby to, by wybić cały garnizon. A te... zwłoki dalej się ruszały. Jak tylko odzyskałem siły, ruszyłem w stronę tego kufra... Żadnych pieniędzy tam nie było, ale zamiast tego znalazłem pewną interesującą 'rzecz'. ";
			link.l1.go = "Fleetwood_LastTask_5";
		break;
		
		case "Fleetwood_LastTask_5":
			RemoveItems(PChar, "GastonHead", 1);
			dialog.text = "Ugh... Co za obrzydlistwo...! Hmm, "+pchar.name+", zaczekaj... Tak! To na pewno on! To głowa łajdaka, który próbował mnie oślepić i zabić!";
			link.l1 = "Znasz go? To Gaston - barman z Bridgetown i pachołek van Berga, tego od statku-widmo. Rozpoznałem go od razu. Ale kto go zabił? I jakim cudem jego łeb trafił do skrzyni Salomona na tej przeklętej wyspie?";
			link.l1.go = "Fleetwood_LastTask_6";
		break;
		
		case "Fleetwood_LastTask_6":
			dialog.text = "Masz rację, to wszystko jest... jakieś chore. Przerażające. I tajemnicze jak wszyscy diabli. Jakby związane z jakąś obcą siłą z innego świata.";
			link.l1 = "Dokładnie. Nie miałem czego szukać u Abigail - wracać bez grosza nie ma sensu. Dlatego tu jestem. Może ty, Richard, pomożesz mi zrozumieć ten cały obłęd...?";
			link.l1.go = "Fleetwood_LastTask_7";
		break;
		
		case "Fleetwood_LastTask_7":
			dialog.text = "Ja? Sam gówno z tego rozumiem, tak jak ty... Ale jedno wiem na pewno - coś tu nie gra. Mam złe przeczucia, bardzo złe... "+pchar.name+", posłuchaj mnie teraz. Musisz wrócić do Bridgetown iupewnić się, że... Gaston zniknął raz na zawsze. Potem spotkaj się z Charliem Knippelem w Lagunie Blanca na Curacao - za dwadzieścia dni. \nZbiorę pieniądze dla ojca Abigail i przekażę je Charliemu. Ty zaniesiesz je Salomonowi i zabierzesz Abigail na Antiguę. Tym razem wszystko musi się udać. Nie może być absolutnie żadnych przeszkód. Ruszaj, przyjacielu!";
			link.l1 = "Zrozumiałem, Richard. Natychmiast postawię żagle.";
			link.l1.go = "Fleetwood_LastTask_8";
		break;
		
		case "Fleetwood_LastTask_8":
			DialogExit();
			pchar.questTemp.HWIC.Eng = "toBarbados";
			AddQuestRecord("Holl_Gambit", "2-21");
			SetFunctionTimerCondition("HWICEng_toBarbadosOver", 0, 0, 20, false);//чтобы не тянули
			AddSimpleRumourCity("Kapitanie! Słyszałem, że Richard Fleetwood naprawdę cię podziwia. A wierz mi, że jego pochwały wiele kosztują. Musisz być cholernie ważną osobą...", "SentJons", 20, 3, "");
			AddMapQuestMarkCity("Bridgetown", false);
			AddLandQuestMark(characterFromId("Bridgetown_tavernkeeper"), "questmarkmain");
		break;
		
//---------------------------------------------против всех-----------------------------------------------
		
		case "InTerksShore":
			DelLandQuestMark(npchar);
			pchar.quest.Fleetwood_ShoreOver.over = "yes";//снять таймер
			dialog.text = "Domyślam się, że to ty jesteś łajdakiem, który porwał moją Abigail. Charlie nie wrócił... więc to też twoja robota, prawda?";
			link.l1 = "Masz rację, panie Fleetwood. To byłem ja. Charlie pomógł mi zdobyć zaufanie Abigail, wykorzystując list, który sam jej napisałeś. Ale darujmy sobie gadki - przejdźmy do interesów. Przyniosłeś pieniądze?";
			link.l1.go = "InTerksShore_1";
		break;
		
		case "InTerksShore_1":
			dialog.text = "Przyniosłem. Ale najpierw chcę zobaczyć Abigail. Muszę wiedzieć, że żyje i nic jej nie zrobiono. Nie mam zamiaru wierzyć na słowo jakiemuś szumowinie.";
			link.l1 = "Czyż nie sądzisz, panie, że nie jesteś w pozycji, by dyktować warunki?";
			link.l1.go = "InTerksShore_2";
			// belamour legendary edition -->
			link.l2 = "Mam dosyć tej farsy! Abigail zostaje ze mną, a ty... pozostaniesz tu, na tej plaży! Ognia!";
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
			dialog.text = "Rozumiem... ale nie jestem głupcem. Jeśli nie zobaczę dziewczyny, to nie ma mowy o żadnych pieniądzach. Czekam więc.";
			link.l1 = "Dobrze. Teraz nadszedł czas, by wyłożyć karty na stół, Kapitanie Fleetwood. Spotkanie tutaj nie miało nic wspólnego z pieniędzmi. Owszem, chętnie bym je przyjął, ale przede wszystkim potrzebuję ciebie.";
			link.l1.go = "InTerksShore_3";
		break;
		
		case "InTerksShore_3":
			dialog.text = "Mnie? Teraz robi się naprawdę ciekawie. Zaczynam pojmować, co tu się tak naprawdę dzieje. Powiedz mi jedno - Abigail... żyje? Czy ją zamordowałeś, ty podły psie?";
			link.l1 = "Pozwól, że zostawię cię z tą niepewnością. Wiedz jedno - nie ma jej tutaj. Odegrała swoją rolę perfekcyjnie, a ty, kapitanie... jesteś dokładnie tam, gdzie chciałem cię mieć. Miłość... to urocze złudzenie, prawda? To przez nią nawet najostrożniejszy lis wyjdzie w końcu z nory. Ha-ha-ha!";
			link.l1.go = "InTerksShore_4";
		break;
		
		case "InTerksShore_4":
			dialog.text = "Nie ciesz się tak prędko, łajdaku! Zorganizowałem ci piękne powitanie na tej wyspie. A to, kto jest w czyich rękach, dopiero się przekonamy! Lepiej się przygotuj, masz mi wiele do powiedzenia - o Abigail, o Charliem... zapłacisz za to, co im zrobiłeś!";
			link.l1 = "Oho, już się trzęsę ze strachu! Koniec tej szopki. Przygotuj się na piekło - bo w niebie i tak nie ma dla ciebie miejsca.";
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

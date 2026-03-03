// Лукас Роденбург - вице-директор ГВИК
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HWIC.CanTake") && !CheckAttribute(pchar, "questTemp.HWIC.CanTake.Holl"))
			{
				dialog.text = "Mów głośniej chłopcze, ale szybko. Jestem zajętym człowiekiem.";
				link.l1 = "Słyszałem, że zatrudniasz kapitanów.";
				link.l1.go = "Holl_start";	
			break;
			}
			dialog.text = "Masz do mnie jakąś sprawe?";
			link.l1 = "Nie, przepraszam. Wychodzę.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Second_time":
		if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
		{
			if (pchar.questTemp.HWIC.Holl == "BaltazarEsc")
			{
				dialog.text = "Miałeś być już w połowie drogi do Sint Maarten, kapitanie.";
				link.l1 = "Przygotowuję się do wypłynięcia, mynheer.";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "BaltazarCom")
			{
				dialog.text = "Ach, kapitanie, oto jesteś! Nie zauważyłem cię, właśnie skończyłem czytać list od Ridderbrocka. Zrobiłeś niemałe wrażenie. Nazywa cię 'strażnikiem kupców i postrachem piratów. Boskim darem dla Kompanii!' Co o tym sądzisz?";
				link.l1 = "Wolałbym pozostać zwykłym kapitanem. Zwykłym, ale bogatym kapitanem.";
				link.l1.go = "SantiagoTrip";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "SantiagoTripBegin")
			{
				dialog.text = "Dlaczego wciąż tu jesteś, a nie w drodze na Kubę?!";
				link.l1 = "Tak, tak, jestem w drodze, mynheer.";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "SantiagoTripFinal")
			{
				sld = characterFromId("Santiago_usurer");
				dialog.text = "Ah, kapitanie! Przyznaję, że zaczynałem się martwić. Jak poszło?";
				link.l1 = "Nie obyło się bez kłopotów, ale opowiem ci o tym później. Najpierw interesy. Señor "+GetFullName(sld)+" kazał mi przekazać ci następujące słowa: 'ten człowiek musi umrzeć'. Wtedy Geraldi uzna incydent za zamknięty. Powiedział też, że ta decyzja jest wolą ich rodziny.";
				link.l1.go = "SantiagoTrip_8";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "SantiagoTripComplete")
			{
				dialog.text = "Cieszę się, że cię widzę, kapitein! Dobrze, że przyszedłeś mnie odwiedzić.";
				link.l1 = "Dzień dobry, mój panie. Zakładam, że masz dla mnie kolejną robotę od Kompanii?";
				link.l1.go = "JacobBerg";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "JacobTakeShip")
			{
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED)
				{
					dialog.text = "Powiedziałem ci, żebyś zacumował swój statek. Czy jesteś zbyt głupi lub ignorant, by wykonywać bezpośrednie rozkazy?";
					link.l1 = "Żaden, panie. Jestem w drodze.";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Zatem zacumowałeś swój statek. Teraz pożyczę ci mój szybek. Czy jesteś gotów, aby natychmiast rozpocząć tę misję? Mój statek jest dobrze wyposażony i gotowy do żeglugi, więc nie masz się czym martwić.";
					link.l1 = "Tak, oczywiście. Jestem gotów, Mynheer Rodenburg.";
					link.l1.go = "JacobBerg_6";
					DelLandQuestMark(npchar);
				}
			break;
			}
			if (pchar.questTemp.HWIC.Holl == "JacobLongway")
			{
				dialog.text = "Co tu jeszcze robisz? Idź natychmiast zobaczyć się z Longwayem.";
				link.l1 = "Przepraszam, jestem w drodze.";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "MirageTake")//а вот теперь начинается дурдом с перебором кораблей
			{
				int iMir = 0;
				int iMef = 0;
				for(i = 0; i < COMPANION_MAX; i++)
				{
				iTemp = GetCompanionIndex(PChar, i);
				if(iTemp > 0)
				{
					sld = GetCharacter(iTemp);
					pchar.questTemp.HWIC.Holl.CompanionIndex = sld.Index;
					if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MIRAGE) iMir = 1;
					if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG) iMef = 1;
				}
				}//установили признак наличия кораблей в эскадре.
				RemoveItems(PChar, "JacobJournal", 1);//удалим журнал ван Берга
				pchar.quest.MirageConvoyOver.over = "yes"; //снять таймер
				if (iMir == 1 && iMef == 0)//потеряли Мейфенг
				{
					dialog.text = "Kapitanie... Już wiem o waszej podróży.";
					link.l1 = "O, naprawdę? Więc musisz wiedzieć, że...";
					link.l1.go = "Jacob_lostMef";
					DelLandQuestMark(npchar);
					break;
				}
				if (iMir == 0 && iMef == 1)//потеряли Мираж
				{
					dialog.text = "Kapitanie... Już wiem o twojej podróży.";
					link.l1 = "Czyżby? Zatem musisz wiedzieć, że...";
					link.l1.go = "Jacob_lostMir";
					DelLandQuestMark(npchar);
					break;
				}
				if (iMir == 0 && iMef == 0)//а это вообще плохо
				{
					dialog.text = "Kapitanie... Już wiem o twojej podróży.";
					link.l1 = "Czyżby? Zatem musisz wiedzieć, że...";
					link.l1.go = "Jacob_failFull";
					DelLandQuestMark(npchar);
					break;
				}
					dialog.text = "Oto jesteś, Kapiteinie... Już wiem wszystko o twojej podróży.";
					link.l1 = "Czyżby? Zatem musisz wiedzieć, że...";
			link.l1.go = "Jacob_complete";
			DelLandQuestMark(npchar);
			break;
			}
			if (pchar.questTemp.HWIC.Holl == "toAntigua")
			{
				dialog.text = "Udaj się na Antiguę. Teraz.";
				link.l1 = "Przepraszam, jestem w drodze.";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "FleetwoodSink" || pchar.questTemp.HWIC.Holl == "FleetwoodCapture")
			{//опять начинаем проверять корабли
				iMir = 0;
				for(i = 0; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if(iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						pchar.questTemp.HWIC.Holl.CompanionIndex = sld.Index;
						if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MIRAGE) iMir = 1;
					}
				}//установили признак наличия Миража в эскадре.
				pchar.quest.ToAntiguaOver.over = "yes"; //снять таймер
				if (iMir == 0)//потеряли Мираж
				{
					dialog.text = "Zostałem poinformowany o twoim przybyciu, kapitanie. Wiem również, że straciłeś mój 'Miraż' w bitwie.";
					link.l1 = "Jesteś dobrze poinformowany, Mynheer Rodenburg. Pomimo wszelkich moich starań, nie udało nam się jej uratować.";
					link.l1.go = "Fleetwood_fail";
					DelLandQuestMark(npchar);
				}
				else
				{
					dialog.text = "Zostałem poinformowany o twoim przybyciu, kapitanie. Widzę, że 'Miraż' jest bezpiecznie zacumowany. To dobrze.";
					link.l1 = "To wszystko według twoich instrukcji, mynheer. Kazałeś mi zabić Fleetwooda i jest martwy. Kazałeś mi przyprowadzić 'Miraż' z powrotem do lokalnego portu i jest tutaj.";
					link.l1.go = "Fleetwood_complete";
					DelLandQuestMark(npchar);
				}
				pchar.quest.Meifeng_fail.over = "yes";
				Group_DeleteGroup("Meifeng_Empty");
				sld = characterFromId("MeifengCap");
				sld.lifeday = 0;//зачистим Мейфенг без китайца
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "Abby_prepare")
			{
				dialog.text = "Ach, oto jesteś. Dobrze cię widzieć. Mam dla ciebie kolejną misję, tak jak obiecałem.";
				link.l1 = "Słucham, panie.";
				link.l1.go = "Abby";
				DelLandQuestMark(npchar);
				break;
			}
			if (!CheckAttribute(pchar, "questTemp.HWIC.Holl.LucasMoney") && pchar.questTemp.HWIC.Holl == "AbbyAgreeMarried")
			{
				dialog.text = "Ach, cieszę się, że cię widzę, mój chłopcze. Spóźniłeś się, a ja zacząłem się martwić. Udało ci się coś zdobyć od Abigail?";
				link.l1 = "Nie tylko to, rozwiązałem również twoje inne problemy. Znalazłem wyspę i zaginiony skarb Shneura. Solomon jest zadowolony, a Abigail powie 'tak' na twoje oświadczyny. Gratulacje, mynheer!";
				link.l1.go = "Abby_2";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "NotFindAbbyIsland")
			{
				dialog.text = "Ah, cieszę się, że cię widzę, mój przyjacielu. Czy udało ci się zdobyć coś od Abigail?";
				link.l1 = "Tak. Rozmawiałem z Abigail i jej ojcem. Jest pewien problem, mynheer: utracona fortuna jej ojca. Abigail czuje się niegodna ciebie, obawia się plotek i szeptów ludzi, jeśli jako panna bez posagu poślubiłaby takiego dżentelmena jak ty. Mam nadzieję, że to rozumiesz.";
				link.l1.go = "Abby_6";
				DelLandQuestMark(npchar);
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.LucasMoney") && pchar.questTemp.HWIC.Holl == "AbbyAgreeMarried")
			{
				dialog.text = "Ah, mój przyjacielu! Ufaj, że przyniosłeś dobre wieści?";
				link.l1 = "Twój plan się powiódł. Abigail powie tak. Gratulacje, mynheer.";
				link.l1.go = "Abby_8";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "MerdokStart")
			{
				dialog.text = "Oczekiwałem na ciebie. Mój chłopcze, jesteś w wielkim niebezpieczeństwie.";
				link.l1 = "Co masz na myśli?";
				link.l1.go = "Merdok";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "MerdokDie")
			{
				dialog.text = "Moi agenci na przystani powiedzieli mi, że przybyłeś. Czy Johan van Merden nie żyje?";
				link.l1 = "Tak. On i jego wspólnik odeszli. To była ciężka walka, ale doprowadziłem ją do końca.";
				link.l1.go = "Merdok_4";
				DelLandQuestMark(npchar);
				break;
			}
			dialog.text = "Nie mamy już nic do omówienia, kapitanie.";
			link.l1 = "Zrozumiano, wychodzę.";
			link.l1.go = "exit";
			break;
		}
		dialog.text = "Czego chcesz? Czas to pieniądz.";
		link.l1 = "Przepraszam, odchodzę.";
		link.l1.go = "exit";
		break;
		
//------------------------------------------------1 задание--------------------------------------------
		case "Holl_start":
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("Bridgetown_tavernkeeper"));
			DelLandQuestMark(characterFromId("Knippel"));
			DelMapQuestMarkCity("Bridgetown");
			DelMapQuestMarkCity("Villemstad");
			DelMapQuestMarkCity("SentJons");
			dialog.text = "Być może. Kim jesteś? Mów szybko, czas to pieniądz.";
			link.l1 = "Jestem kapitanem "+pchar.name+", mój statek i umiejętności mogą być dla ciebie użyteczne.";
			link.l1.go = "Holl_start_0";			
		break;
		
		case "Holl_start_0":
			dialog.text = "Hm, nieznany stop do zbadania w tyglu.";
			link.l1 = "To dlatego jestem tutaj, mynheer.";
			link.l1.go = "Holl_start_1";			
		break;
		
		case "Holl_start_1":
			pchar.questTemp.HWIC.Holl.PirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			dialog.text = "Bardzo dobrze, zobaczymy, jaką masz odwagę. W porządku, Kapitanie, jakkolwiek masz na imię, czy znasz Balthazara Ridderbrocka? Nie? Jakież to szczęście. Tacy chciwi, zrzędliwi, porywczy idioci jak on to rzadki widok.\nAle wydaje się, że tak wybitne cechy nie wystarczyły temu człowiekowi, więc był na tyle sprytny, by obrazić korsarza o imieniu "+GetName(NAMETYPE_ORIG,pchar.questTemp.HWIC.Holl.PirateName,NAME_NOM)+" w lokalnej karczmie i natychmiast wezwał straż, gdy tylko obrażona strona sięgnęła po miecz...";
			link.l1 = "...a oni powiesili pirata na pierwszej wolnej linie?";
			link.l1.go = "Holl_start_2";			
		break;
		
		case "Holl_start_2":
			dialog.text = "To nie takie proste. "+GetName(NAMETYPE_ORIG,pchar.questTemp.HWIC.Holl.PirateName,NAME_NOM)+" nie jest zwykłym piratem, lecz holenderskim kaprem, weteranem ostatnich dwóch wojen z Brytyjczykami. Lokalni podatnicy darzą go sympatią. Nie mogę tego samego powiedzieć o Ridderbrocku.";
			link.l1 = "Więc nasz kaper wciąż żyje?";
			link.l1.go = "Holl_start_3";			
		break;
		
		case "Holl_start_3":
			dialog.text = "Tak, ale on jest naprawdę wściekły. Dlatego Ridderbrock jest przerażony do szpiku kości.";
			link.l1 = "Przypuszczam, że moje szczęście właśnie się kończy. Kiedy spotkam się z Mynheerem Ridderbrockiem?";
			link.l1.go = "Holl_start_4";			
		break;
		
		case "Holl_start_4":
			dialog.text = "Niezwłocznie. Dobrzy ludzie z Philipsburga oczekują na dostawę cukru, którą nasz wspólny znajomy Ridderbrock obiecał dostarczyć. Nie uważam go za kogoś wartego skóry jego butów, lecz niestety pracuje dla nas, więc ruszaj do biura portowego. Znajdź tam Ridderbrocka i powiedz mu, że nakazałem mu natychmiast wypłynąć.\nBędziesz go śledzić i...eskortować do Philipsburga w jednym kawałku. Nie chcę aby "+GetName(NAMETYPE_ORIG,pchar.questTemp.HWIC.Holl.PirateName,NAME_NOM)+" wysłał reputację Kompanii na dno Karaibów wraz z jego ładunkiem.";
			link.l1 = "Ech, misja eskortowa. A co z zapłatą za to... nieprzyjemne zadanie?";
			link.l1.go = "Holl_start_5";			
		break;
		
		case "Holl_start_5":
			dialog.text = "Kapitanie, najpierw wykonaj zadanie. Balthazar zapłaci ci, jak tylko dotrze do celu. W Philipsburgu! Nie w skrzyni Davy'ego Jonesa! Potem zgłoś się do mnie, gdy zadanie zostanie wykonane. Jeśli odniesiesz sukces, będziesz mógł liczyć na moją dalszą opiekę oraz na opiekę Kompanii. Spocznij.";
			link.l1 = "Do zobaczenia, mynheer.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Create_Baltazar");
			pchar.questTemp.HWIC.Holl = "BaltazarEsc";
			NextDiag.TempNode = "Second_time";
			pchar.quest.HWIC_ReturnOfficer.over = "yes";//чтобы офицер не доставал
			pchar.questTemp.HWIC.CanTake.Holl = "true";//признак, что голландка уже бралась
		break;
		
//----------------------------------------------задание 1а--------------------------------------------	
		case "SantiagoTrip":
			dialog.text = "Tak, Ridderbrock to skąpy skurczybyk nawet jak na Holendra. Cóż, już mnie nie obchodzi co z nim będzie. Porozmawiajmy o tobie, Kapitanie Jak-Ci-Tam-Na-Imię. Podoba mi się twój styl, więc zamierzam zaoferować ci kolejną robotę. Tym razem zapłacę za nią sam.";
			link.l1 = "Słucham, mynheer.";
			link.l1.go = "SantiagoTrip_1";			
			AddSimpleRumourCity("Ach, więc to ty jesteś tym dzielnym kapiteinem, który eskortował tego łajdaka Ridderbrocka? Słyszeliśmy o tym... Zapłacił ci tylko pięć tysięcy pesos! Chwalił się tym bez przerwy w karczmie w Philipsburgu pijany jak świnia. Gdybym był kapitanem, wywlekłbym go na ulicę i okładał.", "Villemstad", 20, 3, "");//слух по 1 заданию
		break;
		
		case "SantiagoTrip_1":
			dialog.text = "Potrzebuję człowieka do bardzo ważnej sprawy. Dobrze poradziłeś sobie ze sprawą Ridderbrocka, więc Kompania wierzy, że mogę ci to powierzyć.";
			link.l1 = "Chyba jestem zaszczycony. O co chodzi?";
			link.l1.go = "SantiagoTrip_2";
		break;
		
		case "SantiagoTrip_2":
			sld = characterFromId("Santiago_usurer");
			dialog.text = "Nie mogę podać ci dokładnych szczegółów, ale wiedz, że to nie jest moja praca, to zadanie Kompanii, więc masz szansę zyskać nasze względy, co zapewniam cię, że jest bardzo opłacalne.\nŻegluj do Santiago na Kubie i dostarcz tę paczkę Donowi "+GetFullName(sld)+".  Ma wysoką pozycję w banku Geraldi'ego i jest także moim... naszym partnerem biznesowym. Masz dostarczyć mu to złoto, które zaraz ci dam. Ufam twojej uczciwości, kapitanie. Cóż, jeśli nie twojej uczciwości, to instynktowi przetrwania. Kompania zawsze znajduje tych, którzy próbują nas okraść.";
			link.l1 = "Czy wątpicie we mnie, mynheer?";
			link.l1.go = "SantiagoTrip_3";
		break;
		
		case "SantiagoTrip_3":
			if (pchar.BaseNation == ENGLAND || pchar.BaseNation == FRANCE) sTemp = " Udzielam ci również tej krótkoterminowej licencji handlowej, aby oszczędzić ci wszelkich dyplomatycznych uwikłań z Hiszpanami. Pozwoli ci to na pewien czas cumować w hiszpańskich koloniach.";
			else sTemp = "";
			dialog.text = "Na tę chwilę, nie wątpię w ciebie. Uwierz mi, nie rozmawiałbym z tobą o tej sprawie, gdybym miał wątpliwości. Wiedz, że straciliśmy dużo czasu na przygotowanie tej roboty, więc masz tylko piętnaście dni na dostarczenie."+sTemp+"\nMoja wiadomość i paczka muszą być dostarczone na czas. To jest kluczowe, chłopcze. Śpiesz się, ale bądź ostrożny, to nie będzie łatwe zadanie.";
			link.l1 = "Czy coś jeszcze? Dlaczego mnie ostrzegasz, mynheer Rodenburg?";
			link.l1.go = "SantiagoTrip_4";
		break;
		
		case "SantiagoTrip_4":
			if (pchar.BaseNation == ENGLAND || pchar.BaseNation == FRANCE) GiveNationLicence(HOLLAND, 20);
			dialog.text = "Powiedzmy, że mam swoje podejrzenia. Nie martw się, jeśli zrobisz to tak szybko, jak ostatnie zadanie, będziesz miał szansę stać się cennym agentem do delikatnych spraw Kompanii.";
			link.l1 = "Wszystko, co mam zrobić, to dostarczyć ten list i pieniądze do bankiera w Santiago w ciągu piętnastu dni? Na pierwszy rzut oka nie brzmi zbyt trudno.";
			link.l1.go = "SantiagoTrip_5";
		break;
		
		case "SantiagoTrip_5":
			dialog.text = "Nie tak szybko, chłopcze... Wydaje mi się, że nie do końca pojmujesz powagę tej sytuacji. Wykonanie tej roboty sprawi, że będę ci bardzo zobowiązany. Z drugiej strony, jeśli się nie uda, to będę bardzo wkurzony. W takim wypadku nasikam na ciebie. Czy się rozumiemy, kapitein "+GetFullName(pchar)+"?";
			link.l1 = "Zrozumiałem. Masz moje słowo. Zrobię wszystko, co w mojej mocy, by utrzymać cię w dobrym nastroju.";
			link.l1.go = "SantiagoTrip_6";
		break;
		
		case "SantiagoTrip_6":
			dialog.text = "Bardzo dobrze. Teraz weź list, te skrzynie i pamiętaj o warunkach. I jeszcze jedno: trzymaj się z dala od kłopotów w Santiago.";
			link.l1 = "Bardzo dobrze.";
			link.l1.go = "SantiagoTrip_7";
		break;
		
		case "SantiagoTrip_7":
			DialogExit();
			GiveItem2Character(pchar, "NPC_Letter");
			ChangeItemDescribe("NPC_Letter", "itmdescr_NPC_Letter4");
			TakeNItems(pchar, "chest", 5); 
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("SantiagoTripOver", 0, 0, 32, false);
			}
			else SetFunctionTimerCondition("SantiagoTripOver", 0, 0, 16, false); //таймер
			AddQuestRecord("Holl_Gambit", "1-43");
			pchar.questTemp.HWIC.Holl = "SantiagoTripBegin";
			AddMapQuestMarkCity("Santiago", true);
			AddLandQuestMark(characterFromId("Santiago_usurer"), "questmarkmain");
		break;
		
		case "SantiagoTrip_8":
			dialog.text = "'Musi umrzeć'... tak po prostu. Nie spodziewałem się tego. Hm. Dobrze wykonałeś swoją robotę, kapitanie. Teraz daj mi raport.";
			link.l1 = "Nic specjalnego... to była łatwa robota.";
			link.l1.go = "SantiagoTrip_9";
			link.l2 = "Zostałem ogłuszony i porwany przez jakiegoś człowieka w Santiago. Bardzo interesował się twoimi sprawami z Geraldim. Udało mi się uciec, ale najpierw musiałem go zabić. Jedyną wskazówką, jaką zostawił, było imię jakiegoś człowieka imieniem Gaston, nie mam pojęcia, o co w tym wszystkim chodziło.";
			link.l2.go = "SantiagoTrip_10";
			link.l3 = "Zostałem ogłuszony i porwany przez mężczyznę w Santiago. Bardzo interesował się twoimi interesami z Geraldim. Udało mi się uciec, ale najpierw musiałem go zabić. Nie zdążyłem się niczego od niego dowiedzieć, zanim wysłałem go do piekła.";
			link.l3.go = "SantiagoTrip_11";
		break;
		
		case "SantiagoTrip_9":
			dialog.text = "Wdzięczność Kompanii nie ogranicza się jedynie do słów. Weź swoją nagrodę, zasłużyłeś na nią.";
			link.l1 = "Praca dla Kompanii jest całkiem opłacalna.";
			link.l1.go = "SantiagoTrip_12";
		break;
		
		case "SantiagoTrip_10":
			dialog.text = "Co! Porwanie... Zaraz, zaraz... Gaston! Rozumiem... Chyba. Niestety, mój chłopcze, zostałeś wciągnięty w plugawą aferę. Jesteśmy na nieznanych wodach, więc zobaczymy, jak się to rozwinie. Cieszę się, że udało ci się przeżyć.\nPorozmawiajmy o przyjemniejszych rzeczach - przyjmij tę nagrodę, zasłużyłeś na nią.";
			link.l1 = "Praca dla Kompanii jest całkiem dochodowa";
			link.l1.go = "SantiagoTrip_12";
		break;
		
		case "SantiagoTrip_11":
			dialog.text = "Bzdura! Porwanie cię... Mam jednak pewne podejrzenia. Dowiesz się więcej, jeśli będziesz dalej dla mnie pracować. Masz szczęście i cieszę się, że ci się udało.\nPorozmawiajmy o przyjemniejszych rzeczach - przyjmij tę nagrodę, na którą sobie zasłużyłeś.";
			link.l1 = "Praca dla Kompanii jest całkiem dochodowa";
			link.l1.go = "SantiagoTrip_12";
		break;
		
		case "SantiagoTrip_12":
			AddMoneyToCharacter(pchar, 25000);
			dialog.text = "Dokładnie, mój chłopcze! Możesz stać się dobrze opłacanym agentem Kompanii, jeśli będziemy dalej współpracować. Teraz idź, odpocznij po podróży. Spełniłeś moje oczekiwania. Byłbym naprawdę wdzięczny, gdybyś wrócił za tydzień, mamy jeszcze wiele do zrobienia.";
			link.l1 = "Możesz na mnie liczyć, Mynheer Rodenburg.";
			link.l1.go = "SantiagoTrip_13";
		break;
		
		case "SantiagoTrip_13":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "true";
			AddQuestRecord("Holl_Gambit", "1-46");
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			AddCharacterExpToSkill(pchar, "Leadership", 80);
			AddSimpleRumourCity("My brother at the Company says that Mynheer Rodenburg is quite pleased by your performance, kapitein. Don't lose your chance, Lucas rarely shows such favor.", "Villemstad", 10, 3, "");
			SetTimerFunction("GollandGambit_2_ZadanieStart", 0, 0, 7);
		break;
		
//-----------------------------------------------2 задание--------------------------------------------
		case "JacobBerg":
			dialog.text = "Jesteś bystry, kapitanie. Dokładnie tak. Cóż, porozmawiajmy o szczegółach nadchodzącej misji...";
			link.l1 = "Słucham uważnie.";
			link.l1.go = "JacobBerg_1";			
		break;
		
		case "JacobBerg_1":
			dialog.text = " Mam dla ciebie bardzo poważną i ważną misję, i oczekuję, że wykonasz wszystko zgodnie z moimi instrukcjami. Jak wiesz, relacje między Zjednoczonymi Prowincjami a Anglią są... nieprzyjazne. Brytyjczycy są pewni, że to oni powinni rządzić światem. Problem w tym - nie wszyscy zgadzają się z takim twierdzeniem. Gdziekolwiek płyną, by robić interesy, możesz być pewny, że Holenderska Kompania Wschodnioindyjska dotarła tam pierwsza.\nMy, Holendrzy, mamy największą flotę handlową na świecie, a nasze eskadry wojskowe mogą bronić interesów Republiki zarówno tutaj, jak i za granicą. Anglicy zazdroszczą nam naszej potęgi handlowej i robią, co mogą, aby sabotować działalność Kompanii. Teraz jest pewien angielski kapitan marynarki o imieniu Richard Fleetwood. Pomimo bycia oficerem na etacie Wspólnoty, obecnie działa jako pirat. Atakuje i plądruje każdy statek, który ośmieli się płynąć pod holenderską banderą na Karaibach. Tłumaczy swoje działania jako środek zapobiegawczy przeciwko 'statkowi widmo', który zatapia angielskich handlarzy. Twierdzi, że ten 'statek widmo' to korsarz pływający pod holenderskim listem kaperskim.\nSłyszałeś o 'statku widmo', kapitanie?";
			link.l1 = "Takie bzdury można usłyszeć w każdej karczmie. Wystarczy kupić trochę rumu staremu bosmanowi, a usłyszysz każdą opowieść, jaką tylko zechcesz...";
			link.l1.go = "JacobBerg_2";
		break;
		
		case "JacobBerg_2":
			dialog.text = "Ta sprawa to nie jest pijacka fantazja. Zbadałem działania tego 'statku-widmo'. Dowiedziałem się, że to jest statek z drewna i płótna, załogowany przez zwykłych ludzi, kecz o nazwie 'Miraż'. Jest pod dowództwem człowieka o imieniu Jacob van Berg, który podaje ją za legendarnego 'Latającego Holendra'.";
			link.l1 = "Van Berg? To holenderskie nazwisko. Prawdziwy 'Latający Holender', co?";
			link.l1.go = "JacobBerg_3";
		break;
		
		case "JacobBerg_3":
			dialog.text = "Zgadza się. Jacob van Berg jest Holendrem, pierwotnie z Lejdy. Lecz Republika skazała go na stryczek dawno temu. To zbiegły przestępca, pirat działający wyłącznie dla własnych interesów. Richard Fleetwood poluje na van Berga. Ten fakt wykorzystamy przeciw temu bezczelnemu Anglikowi.\nWolałbym nie zabijać Fleetwooda od razu, choć zasłużył na to dawno temu. Śmierć to za mało dla niego. Chcę nie tylko go zabić, ale także zniszczyć jego imię i honor. Tego właśnie chcę. To także nauczy innych aroganckich angielskich wieprzy lekcji.\nPorozmawiajmy o szczegółach.";
			link.l1 = "Mynheer, to zaczyna brzmieć jak coś osobistego...";
			link.l1.go = "JacobBerg_4";
		break;
		
		case "JacobBerg_4":
			dialog.text = "To nie twoja sprawa. Masz wykonywać rozkazy, a potem dostaniesz zapłatę. Dzięki mojemu agentowi dowiedziałem się, gdzie Jacob van Berg ukrywa się ze swoim 'Miraż'. Operuje z miasta na południowym wybrzeżu Hiszpańskiego kontynentu. Idź do niego i dowiedz się, gdzie zakotwiczył swój statek widmo\nPotem go zabij, znajdź jego 'Miraż', weź go jako zdobycz i dostarcz tutaj. Musisz przejąć 'Miraż', nawet nie myśl o jego zatopieniu.";
			link.l1 = "Brzmi wystarczająco prosto. Gdzie powinienem szukać van Berga?";
			link.l1.go = "JacobBerg_5";
		break;
		
		case "JacobBerg_5":
			dialog.text = "Wszystkie szczegóły przekaże ci mój agent. Nazywa się Longway, to Chińczyk. Udostępniam ci mój osobisty statek, szebek 'Meifeng' na tę misję. Longway jest jej kapitanem, ale będzie przyjmował rozkazy od ciebie.\nUdaj się do lokalnego urzędu portowego i zacumuj tam wszystkie swoje jednostki. Wróć do mnie, gdy to zrobisz.";
			link.l1 = "Dobrze, odwiedzę zarządcę portu. Nie każę ci zbyt długo czekać.";
			link.l1.go = "exit";
			pchar.questTemp.HWIC.Holl = "JacobTakeShip";
			AddLandQuestMark(characterFromId("Villemstad_portman"), "questmarkmain");
		break;
		
		case "JacobBerg_6":
			dialog.text = "Longway czeka na ciebie na zewnątrz. Pokaże ci twój nowy statek i przekaże informacje o miejscu pobytu van Berga. Powodzenia, kapitanie, i nie zawiedź mnie. Pamiętaj, że musisz przyprowadzić 'Meifeng' z powrotem do mnie, więc staraj się jej nie zatopić, przejmując 'Miraż'.";
			link.l1 = "W drodze!";
			link.l1.go = "JacobBerg_7";	
		break;
		
		case "JacobBerg_7":
			DialogExit();
			pchar.quest.Create_Longway.win_condition.l1 = "location";
			pchar.quest.Create_Longway.win_condition.l1.location = "Villemstad_town";
			pchar.quest.Create_Longway.function = "Create_Longway";
			pchar.questTemp.HWIC.Holl = "JacobLongway";
			AddQuestRecord("Holl_Gambit", "1-7");
			pchar.questTemp.HWIC.TakeQuestShip = "true";//все ПУ недоступны для стоянки до поры, также корабль нельзя продать
			pchar.questTemp.HWIC.HollEquip = "true";//форма солдат
			DeleteAttribute(pchar, "questTemp.HWIC.CanTake");//иные варианты более невозможны
		break;
		
		//дурдом продолжается
		case "Jacob_lostMir":
			dialog.text = "Ty niekompetentny głupcze. Nie udało ci się przejąć pirackiego statku. Wszystkie moje plany są zrujnowane. Zabieram ci 'Meifeng'. Wynoś się, już cię nie potrzebujemy.";
			link.l1 = "Przykro mi. Żegnaj, panie Rodenburg.";
			link.l1.go = "Jacob_RemoveShip";
			pchar.questTemp.HWIC.Holl.ShipType = SHIP_MAYFANG;
		break;
		
		case "Jacob_lostMef":
			dialog.text = "Ty bezmyślny idioto. Straciłeś 'Meifeng'. To jest niedopuszczalne... Zabiorę ci 'Miraż' i wstrzymam twoją zapłatę jako rekompensatę za moją stratę. Wynoś się, już cię nie potrzebujemy.";
			link.l1 = "Przykro mi. Żegnaj, Mynheer Rodenburg.";
			link.l1.go = "Jacob_RemoveShip";
			pchar.questTemp.HWIC.Holl.ShipType = SHIP_MIRAGE;
		break;
		
		case "Jacob_failFull":
			dialog.text = "Mój Boże, jesteś naprawdę rzadkim okazem. Niezdolny nieudacznik i idiota. Nie udało ci się schwytać 'Miraż' i straciłeś 'Meifeng' przy okazji. Wynoś się, do cholery, z mojego biura!";
			link.l1 = "Odchodzę.";
			link.l1.go = "exit";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex("Longway");
			AddDialogExitQuestFunction("LandEnc_OfficerFired");//Лонгвэя из офицеров
			pchar.questTemp.HWIC.Holl = "end";
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			pchar.questTemp.HWIC.Detector = "holl_fail";
		break;
		
		case "Jacob_complete":
			dialog.text = "Świetna robota. Wieść o twoim sukcesie już dotarła do moich uszu. Van Berg nie żyje, a ty zdobyłeś jego statek. Twoja zapłata to 50 000 pesos, weź je.\nPrzejmuję od ciebie 'Meifenga'. Teraz nadszedł czas, abyś objął dowództwo nad 'Miraż', która odegra ważną rolę w następnym etapie. Jesteś gotów?";
			link.l1 = "Tak, Panie Rodenburg.";
			link.l1.go = "Fleetwood";
			pchar.questTemp.HWIC.Holl.ShipType = SHIP_MAYFANG;
			AddDialogExitQuestFunction("Jacob_RemoveShip");	
			AddSimpleRumourCity("They say that you are on special assignment for Mynheer Rodenburg himself. Something about sending those English to the bottom of the sea. It seems that you are a man on the rise, kapitein.", "Villemstad", 15, 3, "");
		break;
		
		case "Jacob_RemoveShip":
			DialogExit();
			AddDialogExitQuestFunction("Jacob_RemoveShip");	
			sld = characterFromId("Longway");
			sld.lifeday = 0;
			pchar.questTemp.HWIC.Holl = "end";
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			pchar.questTemp.HWIC.Detector = "holl_fail";
			AddSimpleRumourCity("They say that you have failed Mynheer Rodenburg himself. Good luck, you'll need it.", "Villemstad", 20, 3, "");
		break;
		
//----------------------------------------------3 задание-------------------------------------------------
		
		case "Fleetwood":
			AddMoneyToCharacter(pchar, 50000);
			dialog.text = "Teraz zajmiemy się Fleetwoodem. Zamierzasz wywabić go za pomocą 'statku widmo' 'Miraż', który tak entuzjastycznie ścigał. Zastaw pułapkę blisko Dominiki, 'Miraż' posłuży jako przynęta.\nNajpierw poinformujesz Fleetwooda, że 'Miraż' widziano niedaleko Dominiki. Nasz dzielny Anglik rzuci wszystko, co robi, i natychmiast wyruszy do Dominiki w poszukiwaniu swojej zdobyczy. Nie rozmawiaj z Fleetwoodem bezpośrednio, bo nie wyjdziesz z tego żywy. Znajdź aptekę w St. John's. Aptekarz John Murdock to mój stary przyjaciel.\nPowiedz mu, że działasz na moje polecenie, a on pomoże ci znaleźć miejscowe uszy, które napełnisz soczystymi kłamstwami o 'statku widmo' atakującym angielskich kupców wokół Dominiki.";
			link.l1 = "Mogę to zrobić. Celem jest zasadzka na Fleetwooda na Dominice, prawda?";
			link.l1.go = "Fleetwood_1";
		break;
		
		case "Fleetwood_1":
			dialog.text = "Dokładnie. Longway i 'Meifeng' będą czekać na ciebie w pobliżu Dominiki. We dwóch łatwo pokonacie angielskiego psa. Przejmijcie jego statek i przeszukajcie kajutę. Chcę jego dziennik pokładowy. Zapłacę za niego ekstra.\nAle twoim głównym celem jest zabicie tego drania Fleetwooda, więc jeśli abordaż jest niemożliwy - poślij go na dno. Przede wszystkim musisz zachować 'Miraż' za wszelką cenę. Ona ma kluczową rolę do odegrania w następnym etapie planu.";
			link.l1 = "Zrozumiano.";
			link.l1.go = "Fleetwood_2";
		break;
		
		case "Fleetwood_2":
			dialog.text = "Rada dla ciebie, kapitanie. Nie rzucaj kotwicy w St. John's. Zatrzymaj się w jednej z zatok wyspy i przejdź do miasta przez dżunglę, w przeciwnym razie John nie będzie z tobą rozmawiał. Jeśli zwrócisz na siebie zbyt dużą uwagę, będzie udawał, że cię nie zna. Uważaj również na morzu - 'Miraż' jest znany wśród angielskich kolonii, więc unikaj ich okrętów wojennych i osiedli, jeśli nie chcesz być zaatakowany przez watahę morskich wilków. To wszystko. Niech Bóg będzie z tobą.";
			link.l1 = "Aye aye.";
			link.l1.go = "Fleetwood_3";
		break;
		
		case "Fleetwood_3":
			DialogExit();	
			pchar.questTemp.HWIC.Holl = "toAntigua";
			AddQuestRecord("Holl_Gambit", "1-15");
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			SetFunctionTimerCondition("ToAntiguaOver", 0, 0, 60, false); //таймер 2 месяца
			AddMapQuestMarkShore("Shore1", false);
			AddMapQuestMarkShore("Shore2", false);
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
		break;
		
		case "Fleetwood_complete":
			if (pchar.questTemp.HWIC.Holl == "FleetwoodSink")//Флитвуд утоп с журналом
			{
				dialog.text = "Powróciłeś, kapiteinie... Masz dziennik pokładowy Richarda Fleetwooda?";
				link.l1 = "Niestety nie. Nie miałem okazji wejść na jego statek, zanim go zatopił.";
				link.l1.go = "Fleetwood_complete_1";
				break;
			}
			if (!CheckCharacterItem(pchar, "FleetwoodJournal"))
			{
				dialog.text = "Powróciłeś, kapitanie... Czy masz dziennik Richarda Fleetwooda?";
				link.l1 = "Niestety, nie udało mi się. Udało mi się wejść na Valkyrię i zabić człowieka w walce wręcz, ale nie znalazłem jego dziennika. Jeden z jego ludzi podpalił magazyn i mieliśmy tylko sekundy, by uciec z życiem.";
				link.l1.go = "Fleetwood_complete_1";
				break;
			}
			dialog.text = "„Wróciłeś, kapitanie... Czy masz dziennik pokładowy Richarda Fleetwooda?”";
			link.l1 = "Zrobiłem to. Oto jest. Udało mi się wejść na pokład Valkyrii, chociaż było to o mały włos. Drań odpalił ładunek swojego statku i wysadził go w powietrze. Ledwo uszliśmy z życiem.";
			link.l1.go = "Fleetwood_complete_2";
		break;
		
		case "Fleetwood_complete_1":
			AddMoneyToCharacter(pchar, 100000);
			dialog.text = "To wielka szkoda, odpowiedziałoby to na wiele naszych pytań. Teraz to bez znaczenia. Zabiłeś tego bezczelnego angielskiego psa i to jest najważniejsze. Oto twoja nagroda - 100 000 pesos. Zabieram od ciebie 'Miraż', zamierzamy zwrócić ten statek do Anglii.";
			link.l1 = "Na litość boską?! To zacny statek, chciałem go zatrzymać!";
			link.l1.go = "Fleetwood_complete_3";
		break;
		
		case "Fleetwood_complete_2":
			AddMoneyToCharacter(pchar, 150000);
			RemoveItems(PChar, "FleetwoodJournal", 1);
			dialog.text = "Znakomicie! Jesteś bardzo zdolnym człowiekiem. Gdyby wszyscy nasi kapitanowie byli tacy jak ty, Republika Holenderska byłaby pierwsza wśród największych morskich narodów w historii. Oto twoja nagroda - 100 000 pesos i dodatkowe 50 000 pesos za dziennik. Zabieram od ciebie 'Miraż', zamierzamy zwrócić ten statek Anglii.";
			link.l1 = "Co do diabła?! To piękny statek, chciałem go zatrzymać!";
			link.l1.go = "Fleetwood_complete_3";
		break;
		
		case "Fleetwood_complete_3":
			dialog.text = "Mój chłopcze, jesteś doskonałym żołnierzem, ale zaufaj mi i mojemu doświadczeniu w sprawach polityki. Pamiętasz, co mówiłem o Fleetwoodzie? Zamierzam przybić jego imię i reputację do kamienia młyńskiego i wrzucić go w głębiny. A ci aroganccy szlachcice z Port Royal będą musieli to przełknąć i zadławić się.\nZrobimy z Richarda Fleetwooda kapitana 'statku widmo' Miraż, wilkołaka grającego przeciwko sobie Anglię i Niderlandy, plądrującego, grabieżnego i mordującego pokojowych obywateli obu krajów tylko po to, by się wzbogacić! Co za parodia! Już przygotowałem dowody i świadków, ale 'Miraż' będzie głównym wydarzeniem mojej doskonałej gry.";
			link.l1 = "Więc do diabła ze mną. Zamierzasz poświęcić mój doskonały statek dla swojego planu!?";
			link.l1.go = "Fleetwood_complete_4";
			AddDialogExitQuestFunction("Lucas_ExangeShip");
		break;
		
		case "Fleetwood_complete_4":
			dialog.text = "Uważaj na język, chłopcze, to jest wojna. Czasem musimy poświęcić nie tylko ludzi, ale i statki oraz bogate osady, by osiągnąć nasze polityczne cele. Każda wojna niesie ze sobą straty... Mówiąc o stratach, mam dla ciebie złe wieści. \nKiedy byłeś nieobecny, Willemstad został zaatakowany przez angielskich kaperów. Fort zdołał ich odpędzić, ale nie zanim dostali się do portu z branderami. \nTwój statek został złapany na kotwicy i spalony do linii wodnej. To całkowita strata.";
			link.l1 = "Monsieur, niech to diabli, chyba sobie teraz ze mnie żartujesz. Do wszystkich diabłów! Co ja teraz zrobię?!";
			link.l1.go = "Fleetwood_complete_5";			
		break;
		
		case "Fleetwood_complete_5":
			dialog.text = "Nie bądź tak zdenerwowany, kapitanie, mam też dobre wieści. Aby złagodzić twoje oburzenie, daję ci mój Piękny Wiatr, szebeke 'Meifeng'. Możesz korzystać z tego statku w dowolny sposób, w granicach rozsądku. Dodatkowo, spotkaj się ze mną jutro w rezydencji gubernatora, zostałeś nominowany do nagrody państwowej z wdzięcznością Republiki Niderlandzkiej i Kompanii Zachodnioindyjskiej. Nie opuszczaj miasta, dopóki jej nie otrzymasz, kapitanie.";
			link.l1 = "To trochę łagodzi gorycz moich strat. Jestem zaszczycony. A tak przy okazji, panie, gdzie się podział Longway?";
			link.l1.go = "Fleetwood_complete_6";
		break;
		
		case "Fleetwood_complete_6":
			dialog.text = "Nagle Longway zniknął zaraz po tym, jak kazałem mu płynąć na Dominikę. Mam podejrzenia, że angielscy agenci się na niego zasadzili... a może nie. Prowadzę dochodzenie.";
			link.l1 = "Rozumiem. Jego pomoc na Dominice byłaby bardzo mile widziana. Fleetwood i jego 'Walkiria' stanowili przerażający duet. Mam nadzieję, że Longway wciąż żyje... Tot zeins, mynheer!";
			link.l1.go = "Fleetwood_complete_7";
			pchar.questTemp.HWIC.Holl = "Award";
			AddQuestRecord("Holl_Gambit", "1-24");
			LocatorReloadEnterDisable("Villemstad_town", "reload1_back", true);
			LocatorReloadEnterDisable("Villemstad_town", "reload2_back", true);
			LocatorReloadEnterDisable("Villemstad_town", "gate_back", true);
		break;
		
		case "Fleetwood_complete_7":
			DialogExit();
			AddDialogExitQuestFunction("GollandGambit_AwardFromLucas_1");
			AddSimpleRumour("Tell me captain, was that damned English dog Fleetwood was really responsible for plundering English 'and' Dutch merchants? Really? Such an artful dodger! It is good that you have eliminated this bastard. You are a real hero, captain!", HOLLAND, 10, 3);
		break;
		
		case "Fleetwood_fail":
			dialog.text = "Nie jesteś zwykłym błaznem, jesteś całym cyrkiem. Byliśmy tak blisko finału, a ty to spartaczyłeś... Zapłacę ci 30 000 pesos za eliminację Fleetwooda. Nie mam już dla ciebie misji i nasze porozumienie jest skończone. Wynoś się.";
			link.l1 = "Jak sobie życzysz.";
			link.l1.go = "Fleetwood_fail_1";			
		break;
		
		case "Fleetwood_fail_1":
			AddMoneyToCharacter(pchar, 30000);
			dialog.text = "Mam złe wieści dla ciebie.\nPodczas twojej nieobecności, Willemstad został zaatakowany przez angielskich kaperów. Fort zdołał ich odpędzić, lecz nie zanim dostali się do portu z branderami.\nTwój statek został złapany na kotwicy i spalony do linii wodnej. Stracony całkowicie.";
			link.l1 = "Chyba pójdę się do cholery! Dzięki za nic!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//можно пользоваться ПУ
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			CloseQuestHeader("Holl_Gambit");
			pchar.questTemp.HWIC.Holl = "end";
			pchar.questTemp.HWIC.Detector = "holl_fail";
			AddSimpleRumour("Tell me, captain, is it true that you have sunk this damned English dog Fleetwood? Really? It is good that you have eliminated this bastard. You did well, captain!", HOLLAND, 15, 3);
		break;
		
		case "LucasAward":
			dialog.text = "Kapitanie "+GetFullName(pchar)+"! Za wyeliminowanie Richarda Fleetwooda, niebezpiecznego przestępcy, za ujawnienie zdradzieckiego angielskiego spisku przeciwko Republice, za odwagę i męstwo, zostajesz nagrodzony tysiącem złotych dublonów w imieniu Republiki Niderlandzkiej!\nOtrzymujesz także to cenne narzędzie nawigacyjne - marzenie każdego wojskowego żeglarza.";
			link.l1 = "Jestem szczęśliwy, mogąc służyć Republice!";
			link.l1.go = "LucasAward_1";			
		break;
		
		case "LucasAward_1":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			LAi_SetActorType(sld);
			sld.Dialog.Filename = "Quest\HollandGambit\OtherNPC.c";
			sld.dialog.currentnode = "Bek_7";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			GiveItem2Character(pchar, "bussol");
		break;
		
		case "LucasAward_2":
			dialog.text = "Gratulacje raz jeszcze, przyjacielu. I proszę, odwiedź mnie za tydzień. Potrzebujemy cię do niezwykle delikatnej sprawy.";
			link.l1 = "Zrozumiano, Mynheer Rodenburg. Odwiedzę cię za tydzień.";
			link.l1.go = "LucasAward_3";			
		break;
		
		case "LucasAward_3"://наведем порядок
			LAi_SetActorType(pchar);
			DialogExit();
			AddQuestRecord("Holl_Gambit", "1-25");
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			LAi_ActorGoToLocator(sld, "goto", "goto6", "BekSitDown", -1);
			for (i=1; i<=3; i++)
			{
				sld = characterFromId("LucasGuard_"+i);
				sld.lifeday = 0;//подчистим солдат
			}
			sld = characterFromId("Lucas");
			LAi_ActorGoToLocator(sld, "reload", "reload1", "LucasReturnInCabinet", -1);
			bDisableFastReload = true;
			LocatorReloadEnterDisable("Villemstad_town", "reload1_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload2_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "gate_back", false);
			SetTimerFunction("GollandGambit_4_ZadanieStart", 0, 0, 7);
			AddSimpleRumourCity("They say that you were given a state award by Matias Beck himself! The Republic should be proud to have people like you, kapetein!", "Villemstad", 20, 4, "");
		break;
		
//--------------------------------------------------4 задание----------------------------------------------
		
		case "Abby":
			dialog.text = "Pozwól, że opowiem ci historię. Pomoże ci to zrozumieć, jak delikatne jest twoje następne zadanie. Kilka miesięcy temu fluita pod angielską banderą, która płynęła do Willemstad, została zaatakowana przez nieżyjącego już Jacoba van Berga. Zabrał statek i zatopił go niedaleko wyspy, której nie ma na żadnej z naszych map. Przeżyło tylko dwoje pasażerów fluty. Żyd o imieniu Solomon Shneur i jego córka Abigail. Wszyscy inni pasażerowie zginęli, w tym reszta ich rodziny. Dwoje naszych żydów dotarło na wyspę, unosząc się na szczątkach. Solomonowi udało się nawet przetransportować skrzynię wypełnioną rodzinnym złotem. Bardzo oszczędny z niego człowiek. Innym bohaterem naszej opowieści, Richard Fleetwood, żeglował w pobliżu i usłyszał odgłosy walki. Przybył za późno, aby schwytać van Berga, a 'Miraż' uciekł. Fleetwood postanowił sprawdzić wyspę pod kątem ocalałych. Uratował Solomona i Abigail przed pewną śmiercią na tej bezludnej wyspie. Niestety dla starego Żyda, Solomon nie ma oka marynarza. Pomylił 'Valkerie' Richarda z 'Miraż' Jacoba i - przerażony, że pirat wraca, aby dokończyć dzieła - ukrył swoje złoto gdzieś na wyspie. W rezultacie, on i jego córka przybyli tutaj bez grosza, zostali przywiezieni przez Fleetwooda do Laguny Blanca, niedaleko Willemstad, ich pierwotnego celu podróży. Solomon opowiedział mi tę historię. Republika Holenderska wspiera swobodę praktykowania religii. W ramach tej polityki, Kompania wspiera społeczność żydowską tutaj. Dlatego zadbałem, aby mieli dach nad głową oraz co jeść i nosić. Często odwiedzałem ich miejsce. Abigail to... niezwykła młoda kobieta. Szczera i ufna. Nie będę cię okłamywał, kapitanie, chcę jej i zamierzam uczynić ją moją żoną. Ona również mnie kocha, ale coś stanęło między nami.";
			link.l1 = "Jej ojciec niezbyt zachwycony gojem jako zięciem?";
			link.l1.go = "Abby_0";			
		break;
		
		case "Abby_0":
			dialog.text = "Ha! Stary Salomon byłby w siódmym niebie, gdybym poślubił Abigail, obrzezany zięć czy nie. W rzeczy samej, on ją skłania do przyjęcia mojej propozycji. Nie, nie, to coś, co wykracza poza Żyda i Goja. Proszę cię, chłopcze, rozwiąż dla mnie ten problem. Porozmawiaj z Abigail i dowiedz się, co jest nie tak\nJesteś obcy, może powiedzieć ci rzeczy, których nigdy nie powiedziałaby znajomym ludziom ze względu na swoją czarującą skromność. Dom Shneura znajduje się po prawej stronie od biura kompanii, jeśli staniesz do niego tyłem. Wiem, że jesteś gładkowarzący\nAle zapamiętaj jedno: Richard Fleetwood był prawdziwym kapitanem 'statku-ducha'... Miej to na uwadze podczas rozmowy z Abigail.";
			link.l1 = "Ha! Pewnie, że to pamiętam, Mynheer Rodenburg. Czyż to nie jest oficjalnie uznany fakt? Nie będę tracić czasu, natychmiast złożę wizytę twojej ukochanej.";
			link.l1.go = "Abby_1";			
		break;
		
		case "Abby_1":
			LocatorReloadEnterDisable("Villemstad_town", "houseSP2", false);//откроем дом Аби
			DialogExit();
			pchar.questTemp.HWIC.Holl = "AbbyInHouse";
			AddQuestRecord("Holl_Gambit", "1-26");
			AddLandQuestMark(characterFromId("Abigile"), "questmarkmain");
		break;
		
		case "Abby_2":
			dialog.text = "Czy naprawdę znalazłeś wyspę, gdzie Salomon ukrył swoje złoto? To wspaniale! Zaczynam myśleć, że jesteś w stanie wykonać każde zadanie... Znalazłeś coś jeszcze w tej skrytce?";
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.ScullnotReturn"))
			{
				link.l1 = "Nie, nic więcej. Tylko pieniądze.";
				link.l1.go = "Abby_3";
			}
			else
			{
				link.l1 = "Był tam interesujący przedmiot - nefrytowa czaszka. Dałem ją Solomonowi, powiedział, że to rodzinna pamiątka. Powiedział też, że zamierzałeś ją od niego kupić...";
				link.l1.go = "Abby_4";
			}
		break;
		
		case "Abby_3":
			pchar.questTemp.HWIC.Holl.LucasItem = "obereg_11";
			dialog.text = "Hm. Dobrze więc. To dość dziwne jednakże. Cokolwiek... Jestem ci dłużny, panie, i nigdy tego nie zapomnę. Przygotowałem dla ciebie nagrodę - 50 000 pesos i ten amulet. Teraz jest twój.";
			link.l1 = "Dziękuję, panie Rodenburg!";
			link.l1.go = "Abby_5";
		break;
		
		case "Abby_4":
			pchar.questTemp.HWIC.Holl.LucasItem = "totem_04";
			dialog.text = "Doskonale! Tak, zamierzam kupić ten artefakt od Solomona, on go nie potrzebuje, a ja mam bardzo hojnego nabywcę na niego. Przygotowałem dla ciebie nagrodę - 50 000 peso i ten amulet. Teraz jest twój.";
			link.l1 = "Dziękuję, panie Rodenburg!";
			link.l1.go = "Abby_5";
		break;
		
		case "Abby_5":
			dialog.text = "Nie mam teraz żadnej pracy godnej takiego kapitana jak ty. Ale nie opuszczaj Curacao na długo, wkrótce znów będę potrzebował twoich usług.";
			link.l1 = "Zrozumiałem, mynheer. Do widzenia!";
			link.l1.go = "exit";
			GiveItem2Character(pchar, pchar.questTemp.HWIC.Holl.LucasItem);
			AddMoneyToCharacter(pchar, 50000);
			pchar.questTemp.HWIC.Holl = "Merdok_wait";
			AddQuestRecord("Holl_Gambit", "1-34");
			DelMapQuestMarkCity("Villemstad");
			SetTimerFunction("GollandGambit_5_ZadanieStart", 0, 0, 10);
			AddSimpleRumourCity("Słyszałeś najnowsze wieści? Mynheer Rodenburg poślubi Abigail Shneur, piękną córkę starego szalonego Żyda Salomona. Cóż mogę powiedzieć, to szczęściara. Jeśli Bóg pozwoli, przed ślubem zostanie ochrzczona jako prawdziwa chrześcijanka!", "Villemstad", 20, 3, "");
		break;
		
		case "Abby_6":
			dialog.text = "Ha, i to wszystko? Czysta absurdalność... jak bardzo kobiece. Posłuchaj mnie, mój chłopcze, ten problem można łatwo rozwiązać. Wiem, ile pieniędzy było w skarbcu Salomona: 200 000 pesos. Jestem gotów poświęcić tę sumę dla mojego i Abigail szczęścia. Dam ci pieniądze i opuścisz Curacao na tydzień lub dwa. Potem wrócisz do Salomona i dasz mu pieniądze. Udawaj, że znalazłeś skarbiec. Wilk będzie syty, a owca cała. Oto, weź wymaganą sumę.";
			link.l1 = "Dobry i prosty plan. Zróbmy to.";
			link.l1.go = "Abby_7";
		break;
		
		case "Abby_7":
			dialog.text = " Wypłyń na otwarte morze i wróć do mnie za dziesięć dni. Zrób coś pożytecznego. Poszukaj Manga Rosa, wytwórz jakieś materiały, czy coś. ";
			link.l1 = "Cokolwiek powiesz, Panie Rodenburg.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 200000);
			pchar.questTemp.HWIC.Holl = "GiveLucasMoney";
			SaveCurrentQuestDateParam("questTemp.HWIC.Holl.LucasMoney");
			pchar.questTemp.HWIC.Holl.LucasMoney = "true";
			AddQuestRecord("Holl_Gambit", "1-35");
		break;
		
		case "Abby_8":
			pchar.questTemp.HWIC.Holl.LucasItem = "obereg_11";
			dialog.text = "Znakomicie! Po raz kolejny wykonałeś zadanie perfekcyjnie. Jestem ci wdzięczny, panie, i nigdy tego nie zapomnę. Przygotowałem dla ciebie nagrodę - 50 000 pesos i ten amulet. Teraz jest twój.";
			link.l1 = "Dziękuję, Panie Rodenburg!";
			link.l1.go = "Abby_5";
		break;
		
//-------------------------------------------5 задание-------------------------------------------------
		case "Merdok":
			dialog.text = "Tak, dokładnie tak. Mój przyjacielu, czasami trudno dostrzec, kto jest twoim przyjacielem, a kto wrogiem. Czasami przegapiasz moment, gdy twój najbliższy współpracownik staje się twoim nemezis. Nasz wspólny znajomy z St John's, John Murdock - znany również jako Johan van Merden - to były agent Kompanii, który sprzedał się angielskiej flocie.\nJego najnowsza misja to eliminacja jednej z najjaśniejszych gwiazd Kompanii... ciebie.";
			link.l1 = "Jestem zaszczycony. Cieszę się, że mi powiedziałeś, w przeciwnym razie bym się tego nie spodziewał.";
			link.l1.go = "Merdok_1";
		break;
		
		case "Merdok_1":
			dialog.text = "Dokładnie, kapiteinie. To sprytny pies. Znajdź drania i zabij go, zanim zaatakuje. Płyń na Antiguę i poszukaj tajnego wejścia do jego apteki. Przed kościołem jest właz prowadzący do tajnego tunelu. Użyj go.";
			link.l1 = "Zajmę się tym.";
			link.l1.go = "Merdok_2";
		break;
		
		case "Merdok_2":
			dialog.text = "Jeszcze jedna rzecz, kapitein. Gdy Johan będzie martwy, przeszukaj jego zwłoki, dom i piwnicę. Ma archiwum - gruby rejestr, w którym zapisywał przeklęte notatki podczas pracy dla Kompanii. Te informacje zniszczą nas wszystkich, jeśli nasi wrogowie je znajdą.\nZnajdź to przeklęte archiwum i dostarcz je do mnie, zapłacę za to ekstra. Teraz idź. Szczęść Boże, Kapitein "+pchar.name+", i spróbuj wrócić w jednym kawałku. Republika cię potrzebuje!";
			link.l1 = "Obiecuję wam, mynheer, wrócić w jednym kawałku. Z pewnością leży to w moim najlepszym interesie!";
			link.l1.go = "Merdok_3";
		break;
		
		case "Merdok_3":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "KillMerdok";
			AddQuestRecord("Holl_Gambit", "1-42");
			LocatorReloadEnterDisable("Villemstad_town", "reload1_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload2_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "gate_back", false);
			bDisableFastReload = false;
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload2", false);//откроем проход в подземелье из дома
			LocatorReloadEnterDisable("SentJons_TownCave", "reload1_back", false);//откроем проход в дом из подземелья
			LocatorReloadEnterDisable("SentJons_town", "HouseF3", true);//аптеку закроем
			pchar.quest.Merdok_inCave.win_condition.l1 = "location";
			pchar.quest.Merdok_inCave.win_condition.l1.location = "SentJons_TownCave";
			pchar.quest.Merdok_inCave.function = "MerdokInUndergroundCave";
			LAi_LocationDisableOfficersGen("SentJons_TownCave", true);//офицеров в шахту не пускать
			DelMapQuestMarkCity("Villemstad");
			AddMapQuestMarkCity("SentJons", false);
		break;
		
		case "Merdok_4":
			dialog.text = "Wybornie, kapitanie! Cieszę się, naprawdę. Czy znalazłeś jego archiwum?";
			if (CheckCharacterItem(pchar, "MerdokArchive"))//архив
			{
				link.l1 = "Tak, oto jest. Nie było żadnych innych dokumentów na zwłokach chemika ani w jego skrzyniach.";
				link.l1.go = "Merdok_book";
			}
			link.l2 = "Nie. Szukałem wszędzie, ale nic nie znalazłem.";
			link.l2.go = "Merdok_5";
			DeleteAttribute("SentJons_TownCave", "box2");//если не нашли шифр - уже и не найдем
		break;
		
		case "Merdok_5":
			dialog.text = "Niewątpliwie szkoda, ale nie mam z tym problemu. Jestem pewien, że Johan nie miał wystarczająco dużo czasu, by przekazać to Anglikom, w przeciwnym razie już mielibyśmy sznury na szyjach... Najprawdopodobniej ukrył to w jakimś tajnym skrytce... niech tam zostanie na zawsze! Gratuluję ci, kapitanie, pomyślnego zakończenia naszej misji!";
			link.l1 = "Wdzięczność!";
			link.l1.go = "Merdok_6";
			
			SetTimerCondition("PZ_LigaInJungle", 0, 0, 7, false);	// проверку не прошёл, значит нападёт Лига через неделю, после чего начнётся таймер на 30 дней 1 этапа
		break;
		
		case "Merdok_book":
			dialog.text = "Znakomicie! Teraz jest tam, gdzie jego miejsce. Udowodniłeś, że jesteś najlepszy po raz kolejny... Daj mi książkę... za archiwum jest nagroda - ten wyśmienity muszkiet. Wiernie mi służył, a teraz jest twój!";
			link.l1 = "";
			if (CheckAttribute(pchar, "questTemp.PZ_RodenburgUkradenaStranitsa"))
			{
				link.l1.go = "Merdok_book_2";
			}
			else
			{
				link.l1.go = "Merdok_book_6";
			}
			RemoveItems(PChar, "MerdokArchive", 1);
		break;
		
		case "Merdok_book_2":
			dialog.text = "Co kombinujesz, kapitanie? Brakuje kilku stron - stron, które są dla mnie bardzo ważne. Myślałeś, że tego nie zauważę, żebyś mógł je użyć przeciwko mnie? A może liczyłeś na coś więcej? Obawiam się, że muszę cię rozczarować w obu przypadkach.";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				Notification_Perk(true, "Trustworthy");
				link.l1 = " (Godny zaufania) Przepraszam. Moim jedynym błędem było to, że sam wcześniej nie sprawdziłem archiwum.";
				link.l1.go = "VD_Merdok_book_3";
				SetTimerCondition("PZ_Etap1_Start", 0, 0, 30, false);	// 1 этап стартует через 30 дней
			}
			else
			{
				Notification_Perk(false, "Trustworthy");
				link.l1 = "Czy naprawdę wyrwałbym strony, a potem oddał archiwum z obojętnym wyrazem twarzy?";
				link.l1.go = "Merdok_book_3";
				SetTimerCondition("PZ_LigaInJungle", 0, 0, 7, false);	// проверку не прошёл, значит нападёт Лига через неделю, после чего начнётся таймер на 30 дней 1 этапа
			}
			LAi_Fade("", "");
		break;
		
		case "Merdok_book_3":
			dialog.text = "Chciwość, głupota i bezczelność czasami popychają ludzi do najbardziej szalonych czynów, kapitanie.";
			link.l1 = "Żaden z tych trzech mnie nie zmotywował, zapewniam cię.";
			link.l1.go = "Merdok_book_4";
		break;
		
		case "Merdok_book_4":
			dialog.text = "Więc mówisz, że van Merden usunął te strony i ukrył je gdzie indziej?";
			link.l1 = "Dokładnie. Mogę wrócić i ich szukać - przewrócić aptekę do góry nogami, a nawet całe St. John's - jeśli uznasz to za konieczne.";
			link.l1.go = "Merdok_book_5";
		break;
		
		case "Merdok_book_5":
			dialog.text = "Nie trzeba, panie. Większość ważnych rzeczy jest tu i tak, a bez brakujących stron reszta nie stanowi dla mnie zagrożenia.";
			link.l1 = "";
			link.l1.go = "Merdok_book_6";
		break;
		
		case "VD_Merdok_book_3":
			dialog.text = "Więc to brak troski lub ciekawości, a nie nieuczciwość czy tajny plan? Czy myślisz, że już tak było, gdy to znalazłeś?";
			link.l1 = "Najprawdopodobniej, Mynheer Rodenburg. Być może van Merden wyrwał te strony wcześniej. ";
			link.l1.go = "VD_Merdok_book_4";
		break;
		
		case "VD_Merdok_book_4":
			dialog.text = "Może to i lepiej. Bez tych stron reszta archiwum nie stanowi dla mnie zagrożenia - zwłaszcza w rękach ignoranckich.";
			link.l1 = "";
			if (IsCharacterPerkOn(pchar, "Trustworthy")) link.l1.go = "Merdok_book_6";
			else link.l1 = "Merdok_6";
		break;
		
		case "Merdok_book_6":
			dialog.text = "Za archiwum jest nagroda - ten doskonały muszkiet. Służył mi z wielkim wyróżnieniem, a teraz jest twój!";
			link.l1 = "Dzięki!";
			link.l1.go = "Merdok_6";
			GiveItem2Character(PChar, "mushket2");
		break;
		
		case "Merdok_6":
			dialog.text = "Zrobiliśmy to dobrze, ty i ja, kapitanie. Nie jest przesadą stwierdzenie, że nic z tego by się nie wydarzyło bez ciebie. Osiągniesz niesamowite wyżyny kariery, jeśli będziesz nadal służył Republice, być może nawet zostaniesz nobilitowany.";
			link.l1 = "Zdaje się, że to pożegnanie, Mynheer Rodenburg.";
			link.l1.go = "Merdok_7";
		break;
		
		case "Merdok_7":
			dialog.text = "To pożegnanie, "+pchar.name+".  Zrealizowałem wszystko, co chciałem tutaj, więc za tydzień wracam do domu, do Amsterdamu. Moja nowa żona Abigail i mój teść Solomon będą mi towarzyszyć. Peter Stuyvesant już znalazł nowego wice-dyrektora Kompanii, więc porozmawiaj z nim, jeśli czegoś potrzebujesz\nZa twoje usługi przekazuję ci 'Meifeng'. Jest teraz twój, kapitanie, zasłużyłeś na niego.";
			link.l1 = "Dziękuję, Mynheer Rodenburg. Bardzo przywiązałem się do 'Meifeng' i już zacząłem go traktować jak swoją własność.";
			link.l1.go = "Merdok_8";
		break;
		
		case "Merdok_8":
			dialog.text = "I teraz muszę cię prosić, byś mnie opuścił, chłopcze. Mam wiele rzeczy do zrobienia, zanim wyruszymy w rejs... Odwiedź mnie kiedyś w Amsterdamie! Wypijemy kielicha i wspomnimy stare dobre czasy...";
			link.l1 = "Aj, panie. Mam nadzieję, że wszyscy jesteście szczęśliwi i dostatni w swoim nowym życiu! Żegnaj!";
			link.l1.go = "Merdok_9";
			// belamour legendary edition -->
			link.l2 = "Aye, mynheer. Mam nadzieję, że wszyscy jesteście szczęśliwi i dostatni w swoim nowym życiu!\n(przez zaciśnięte zęby) ... Mam nadzieję, że się już nie spotkamy, ty arogancki draniu. Poczekaj tylko, aż odkryjesz radości z bycia żonatym z 'nieśmiałą' żydowską jędzą.";
			link.l2.go = "Merdok_9a";
		break;
		
		case "Merdok_9a":
			AddCharacterExpToSkill(pchar, "FencingL", 60);
			AddCharacterExpToSkill(pchar, "FencingS", 60);
			AddCharacterExpToSkill(pchar, "FencingH", 60);
			AddCharacterExpToSkill(pchar, "Pistol", 60);
			DialogExit();
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//можно пользоваться ПУ
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			pchar.questTemp.HWIC.Holl = "end";
			AddQuestRecord("Holl_Gambit", "1-41");
			CloseQuestHeader("Holl_Gambit");
			sld = characterFromId("Abigile");//уберем Аби
			sld.lifeday = 0;
			sld = characterFromId("Solomon");//уберем Соломона
			sld.lifeday = 0;
			pchar.quest.Lucas_quit.win_condition.l1 = "Timer";
			pchar.quest.Lucas_quit.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Lucas_quit.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 7);
			pchar.quest.Lucas_quit.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 7);
			pchar.quest.Lucas_quit.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 7);
			pchar.quest.Lucas_quit.function = "LucasQuit";//прерывание на Лукаса
			pchar.questTemp.HWIC.Detector = "holl_win";
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			sld.Dialog.Filename = "Common_Mayor.c";//patch-8
			sld.dialog.currentnode = "First time";
			sld.quest.meeting = "1";
			DelMapQuestMarkCity("Villemstad");
			AddMapQuestMarkCity("FortFrance", false);
			AddLandQuestMark(characterFromId("Mishelle"), "questmarkmain");
			AddSimpleRumourCity("Mynheer Rodenburg popłynął do Amsterdamu ze swoją młodą żoną i teściem. Czy jesteś nowym wicedyrektorem?", "Villemstad", 30, 3, "");
			AddSimpleRumour("Mówią, kapitein, że cieszysz się uznaniem gubernatora generalnego. Mynheer Rodenburg podobno mianował cię swoim następcą w Kompanii, czy tak?", HOLLAND, 30, 3);
		break;
		
		case "Merdok_9":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			// <-- legendary edition
			DialogExit();
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//можно пользоваться ПУ
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			pchar.questTemp.HWIC.Holl = "end";
			AddQuestRecord("Holl_Gambit", "1-41");
			CloseQuestHeader("Holl_Gambit");
			sld = characterFromId("Abigile");//уберем Аби
			sld.lifeday = 0;
			sld = characterFromId("Solomon");//уберем Соломона
			sld.lifeday = 0;
			pchar.quest.Lucas_quit.win_condition.l1 = "Timer";
			pchar.quest.Lucas_quit.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Lucas_quit.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 7);
			pchar.quest.Lucas_quit.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 7);
			pchar.quest.Lucas_quit.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 7);
			pchar.quest.Lucas_quit.function = "LucasQuit";//прерывание на Лукаса
			pchar.questTemp.HWIC.Detector = "holl_win";
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			sld.Dialog.Filename = "Common_Mayor.c";//patch-8
			sld.dialog.currentnode = "First time";
			sld.quest.meeting = "1";
			DelMapQuestMarkCity("Villemstad");
			AddMapQuestMarkCity("FortFrance", false);
			AddLandQuestMark(characterFromId("Mishelle"), "questmarkmain");
			AddSimpleRumourCity("Mynheer Rodenburg has sailed to Amsterdam with his young wife and father-in-law. Are you the new vice-director?", "Villemstad", 30, 3, "");
			AddSimpleRumour("They say, kapitein, that you are well regarded by the governor-general. Mynheer Rodenburg supposedly appointed you as his successor in the Company, is that so?", HOLLAND, 30, 3);
		break;
		
//----------------------------------------------за Англию------------------------------------------------------
		case "Lucas_abordage":
			dialog.text = "Boże na Niebie! Pies Fleetwooda! Może i dziś wygrałeś, ale Lucas Rodenburg tanio skóry nie sprzeda.";
			link.l1 = "Nie sądzę. Oddasz mi swoje życie za darmo, ty holenderski skąpcze.";
			link.l1.go = "Lucas_abordage_1";
		break;
		
		case "Lucas_abordage_1":
			PlaySound("Voice\English\hambit\Lucas Rodenburg-04.wav");
			dialog.text = "Z głębokości piekła nasram ci do ust! Właśnie podpaliłem ładownię, a ogień wkrótce dotrze do prochowni! Nasze statki są związane w zwarciu, więc nie ma nadziei na ucieczkę! Spłoniesz albo nakarmisz rekiny!";
			link.l1 = "Cholera! Cofnijcie się, ludzie, musimy się wycofać!";
			link.l1.go = "Lucas_abordage_2";
			// belamour legendary edition -->
			link.l2 = "Nie odejdę, dopóki twoja dusza nie opuści twego ciała. Nie ruszaj się, to będzie bolało.";
			link.l2.go = "Lucas_abordage_2a";
		break;
		
		case "Lucas_abordage_2a":
			AddCharacterExpToSkill(pchar, "FencingL", 60);
			AddCharacterExpToSkill(pchar, "FencingS", 60);
			AddCharacterExpToSkill(pchar, "FencingH", 60);
			AddCharacterExpToSkill(pchar, "Pistol", 60);
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle("PrepareToBoom1"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.GenQuest.Detonation = true; // patch-4
		break;
		
		case "Lucas_abordage_2":
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			// <-- legendary edition
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle("PrepareToBoom1"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.GenQuest.Detonation = true; // patch-4
		break;
		
//----------------------------------------------против всех--------------------------------------------------
		case "LucasPrisoner":
			dialog.text = " Dlaczego tu jesteś, łajdaku? Przyszedłeś się ze mnie nabijać? Może w końcu powiesz mi, jaka jest twoja rola w tej grze. To ty przejąłeś brygantynę, prawda? Czy to był twój plan od początku?";
			link.l1 = "Przybyłem, by przekazać ci pewne pozdrowienia, Lucasie Rodenburg. Najlepsze pozdrowienia od Johna Merdocka, którego zdradziłeś. Byłeś moim zadaniem i wykonałem je. Żegnaj na razie.";
			link.l1.go = "LucasPrisoner_1";
		break;
		
		case "LucasPrisoner_1":
			PlaySound("Voice\English\hambit\Lucas Rodenburg-04.wav");
			dialog.text = "Johan? Haha! Więc to on stał za tym wszystkim! Ten stary hultaj! Ale gra jeszcze się nie skończyła. Jacob van Berg idzie po ciebie i nie uciekniesz! Ty i twój statek jesteście przegrani, ty żałosny morski żebraku!";
			link.l1 = "Oszczędź swój głos na sąd kata, Rodenburgu.";
			link.l1.go = "LucasPrisoner_2";
		break;
		
		case "LucasPrisoner_2":
			DialogExit();
			pchar.questTemp.jailCanMove = true; //разрешить пройти мимо стражи
			LAi_SetPlayerType(pchar);
			pchar.quest.Login_Joakim.win_condition.l1 = "location";
			pchar.quest.Login_Joakim.win_condition.l1.location = "Villemstad_town";
			pchar.quest.Login_Joakim.function = "Create_Joakim";
			pchar.questTemp.HWIC.Self = "JoakimMeeting";
			SetFunctionTimerCondition("LucasQuit", 0, 0, 7, false);
		break;
	}
}

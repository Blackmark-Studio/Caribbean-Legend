// Филипп де Пуанси - генерал-губернатор французских колоний
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.Terrapin_KathyFox"))
			{
				dialog.text = "Witam, "+pchar.name+". Come in; I've already been informed.";
				link.l1 = "Zawiadomiony? Może to jakieś nieporozumienie, Wasza Ekscelencjo. Przyszedłem zameldować o pomyślnym zakończeniu misji, ale widzę, że nie jesteście w najlepszym nastroju.";
				link.l1.go = "PZ_PoincyAngry1";
				DeleteAttribute(pchar, "questTemp.Terrapin");
				DeleteAttribute(pchar, "questTemp.Terrapin_KathyFox");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "done")
			{
				dialog.text = "Cieszę się, że cię widzę, "+pchar.name+"Jestem poinformowany o twoich osiągnięciach, a co najważniejsze, udało ci się wypełnić misję! Pokazałeś się z najlepszej strony i cieszę się, że się co do ciebie nie pomyliłem.";
				link.l1 = "Czy mogę teraz otrzymać od was pisemny rozkaz o uwolnieniu mojego brata?";
				link.l1.go = "serve";
				AddCharacterExpToSkill(pchar, "Sneak", 500);
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Hardcore_Tortuga") && CheckAttribute(pchar, "questTemp.Sharlie.LevasserDied"))
			{
				dialog.text = "Cieszę się, że cię widzę, "+pchar.name+" Słyszałem o twoich czynach i co najważniejsze, twoja misja została wykonana! Muszę jednak powiedzieć, że spodziewałem się mądrzejszego pomysłu niż frontalny atak. Żal zmarłych francuskich żołnierzy.\nAle wojna to wojna, zawsze są ofiary. Wypełniłeś swój obowiązek i cieszę się, że miałem rację co do ciebie.";
				link.l1 = "Czy mogę teraz otrzymać od was pisemny rozkaz uwolnienia mego brata?";
				link.l1.go = "serve";
				DeleteAttribute(pchar, "questTemp.Sharlie.Hardcore_Tortuga");
				DeleteAttribute(pchar, "questTemp.Sharlie.LevasserDied");
				break;
			}
			// Jason НСО 
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && GetCharacterIndex("Noel") == -1 && pchar.questTemp.Patria != "epizode_12_barondie" && pchar.questTemp.Patria != "epizode_12_baronfail" && pchar.questTemp.Patria != "epizode_12_baronkilled" && pchar.questTemp.Patria != "fail" && pchar.questTemp.Patria != "end")
			{
				if (CheckCharacterItem(pchar, "patent_fra"))
				{
					dialog.text = "Miło cię widzieć, Charles. Przede wszystkim pozwól mi pogratulować ci pomyślnego ukończenia skomplikowanego zadania ochrony kolonii Saint-Pierre przed hiszpańskimi najeźdźcami. Znakomita robota, mój przyjacielu!";
					link.l1 = "Dziękuję, Chevalier.";
					link.l1.go = "patria";
					Patria_SetInspector();
				}
				else
				{
					dialog.text = "Miło cię widzieć, Charles. Przede wszystkim pozwól mi pogratulować ci pomyślnego ukończenia skomplikowanego zadania ochrony kolonii Saint-Pierre przed hiszpańskimi najeźdźcami. Wspaniała robota, mój przyjacielu! Przedstawiam ci kolejną okazję do współpracy z Marynarką. Francja desperacko potrzebuje oficerów takich jak ty. Mam nadzieję, że tym razem będziesz bardziej rozsądny... Weź patent, Kapitanie Charles de Maure!";
					link.l1 = "Dziękuję, Chevalier. Cieszę się, że mogę pomóc krajowi i chętnie będę kontynuować służbę!";
					link.l1.go = "patria";
					if (!CheckCharacterItem(pchar, "suit1")) GiveItem2Character(pchar, "suit1");
					GiveItem2Character(pchar, "patent_fra");
					EquipCharacterbyItem(pchar, "patent_fra");
					Items[sti(pchar.EquipedPatentId)].TitulCur = 2; 
					Items[sti(pchar.EquipedPatentId)].TitulCurNext = 0;
					ChangeCharacterNationReputation(pchar, FRANCE, 100);
					Patria_SetInspector();
				}
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria != "fail" && pchar.questTemp.Patria != "end")
			{
				if (!CheckCharacterItem(pchar, "patent_fra"))
				{
					dialog.text = "Charles, rozczarowujesz mnie. W wyniku twoich nierozważnych działań straciłeś swój patent i rangę w Królewskiej Marynarce. Nie ma miejsca na dalszą współpracę. Zwolniony.";
					link.l1 = "Hmm...";
					link.l1.go = "patria_patentfail";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_1_return")
				{
					dialog.text = "Cieszę się, że cię widzę, Charles. Zgłaszaj się!";
					if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Fail"))
					{
						link.l1 = "Robota wykonana, okup z kolonii San Jose został odebrany. Ale są złe wieści: w bitwie fort 'Eclatant' został zatopiony. Ostrzegałem kapitana, by uważał, ale mnie nie posłuchał, i...";
						link.l1.go = "patria_8_1";
					}
					else
					{
						link.l1 = "Robota skończona, okup z kolonii San Jose został odebrany.";
						link.l1.go = "patria_8";
					}
					break;
				}
				// belamour legendary edition фикс проверки мундира с мушкетом
				if(!IsUniformEquip())
				{
					dialog.text = "Panie, od tego dnia wchodź do moich sal jedynie w odpowiednim mundurze!";
					link.l1 = "...";
					link.l1.go = "exit";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_2_return" && IsUniformEquip())
				{
					dialog.text = "Baronie, kapitanie! Cieszę się, że cię widzę!";
					link.l1 = "Zadanie zostało wykonane, Chevalier.";
					link.l1.go = "patria_14";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_3_return" && IsUniformEquip())
				{
					dialog.text = TimeGreeting()+", kapitanie. Jakie wieści przynosisz?";
					if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Fail"))
					{
						link.l1 = "Hiszpanie rzeczywiście planowali atak na Port-au-Prince. Na zachodnim krańcu Hispanioli znaleźliśmy potężną eskadrę wroga. Została całkowicie zniszczona. Jednak 'Eclatant' został zatopiony.";
						link.l1.go = "patria_26_1";
					}
					else
					{
						link.l1 = "Hiszpanie rzeczywiście planowali atak na Port-au-Prince. Na zachodnim krańcu Hispanioli znaleźliśmy potężną eskadrę wroga. Została całkowicie zniszczona.";
						link.l1.go = "patria_26";
					}
					break;
				}
				if (pchar.questTemp.Patria == "epizode_4_return" && IsUniformEquip())
				{
					dialog.text = TimeGreeting()+", Charles. Jak się ma Mynheer Stuyvesant?";
					link.l1 = "Wszystko w porządku, Chevalierze. Dostawa zakończyła się sukcesem, oto odpowiedź na twój list.";
					link.l1.go = "patria_31";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_5_return" && IsUniformEquip())
				{
					dialog.text = "Charles, baronie... Już wróciłeś?";
					link.l1 = "...";
					link.l1.go = "patria_36";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_6_return" && IsUniformEquip())
				{
					dialog.text = "Nie podoba mi się twoje zmarszczone czoło, Charles. Co powiedział Stuyvesant, melduj!";
					if (pchar.questTemp.HWIC.Detector == "holl_win" || pchar.questTemp.HWIC.Detector == "self_win") link.l1 = "Dosłownie powiedział: 'powiedz Chevalierowi, że nie jest już odpowiedzialny za Sint-Maarten. Dość go. A jeśli chodzi o inspekcję z macierzystego państwa - niech coś wymyśli, de Poincy nigdy nie miał trudności z przewracaniem wszystkiego do góry nogami'. Po ogłoszeniu tej wiadomości, mynheer wyrzucił mnie z rezydencji. To był koniec naszych negocjacji.";
					else link.l1 = "Cóż, oto co powiedział: 'twój pan był ostatnio zbyt chciwy na Sint-Maarten, więc czas poskromić jego nienasycony głód.' Po tym próbował mnie aresztować. Musiałem torować sobie drogę do statku ostrzem. Tyle o holenderskiej dyplomacji.";
					link.l1.go = "patria_43";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_7_go" && IsUniformEquip())
				{
					dialog.text = "Kapitana, czekaliśmy na ciebie. Wyjaśniłem baronowi obecną sytuację, a on w pełni poparł moją decyzję. Holendrzy odpowiedzą za swoją arogancję.";
					link.l1 = "Wojna zatem?";
					link.l1.go = "patria_51";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_7_continue" && IsUniformEquip() && pchar.location.from_sea == "Charles_town") // add-7
				{
					Patria_HunterShipChecker();
					if (CheckAttribute(pchar, "questTemp.Patria.Hunter.GiveShip"))
					{
						dialog.text = "Widzę, mój przyjacielu, że pojmałeś statek wschodnioindyjski z towarami. Wybornie!";
						link.l1 = "Przekazuję ci statek, wydaj rozkazy urzędnikom portowym, Kawalerze.";
						link.l1.go = "patria_55";
					}
					else
					{
						dialog.text = "Czy masz jakieś pytania, Charles?";
						link.l1 = "Nie w tej chwili, monsieur. W takim razie ruszam...";
						link.l1.go = "exit";
					}
					break;
				}
				if (pchar.questTemp.Patria == "epizode_8" && IsUniformEquip())
				{
					dialog.text = "Wreszcie przybyłeś, kapitanie! Na Saint Christopher jest nagły wypadek!";
					link.l1 = "Nieprzyjazna eskadra?";
					link.l1.go = "patria_59";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_8_wait" && IsUniformEquip() && GetCompanionQuantity(pchar) < 5)
				{
					dialog.text = "Czy jesteś gotów wziąć naszego kuriera lugra?";
					link.l1 = "Jestem.";
					link.l1.go = "patria_64";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_8_return")
				{
					dialog.text = "Kapitanie de Maure, Sir Doily! Cieszę się, że cię widzę! Całe miasto obserwowało, jak nauczyłeś hiszpańsko-holenderskich łotrów, którzy pożądali naszej kolonii, lekcji!";
					link.l1 = "To był mój obowiązek, Chevalier.";
					link.l1.go = "patria_66";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_9_start" && IsUniformEquip())
				{
					dialog.text = TimeGreeting()+"Zaczynajmy, Charles, dobrze?";
					link.l1 = "Oczywiście, Chevalier. Dlatego tu jestem.";
					link.l1.go = "patria_69";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_9_return" && IsUniformEquip())
				{
					dialog.text = "Jestem rad powitać w moim gabinecie wiceadmirała Królewskiej Marynarki Francji! Tak, mój przyjacielu, nie myliłeś się: osobiście podpisałem rozkaz o twoim mianowaniu. Formalnie, musi on jeszcze zostać zatwierdzony we Francji, ale nawet nie musisz wątpić, że to się stanie. Gratulacje!";
					link.l1 = "Służę mojej ojczyźnie!";
					link.l1.go = "patria_76";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_10_return" && IsUniformEquip())
				{
					if (GetQuestPastDayParam("questTemp.Patria.Curacao.Date") < 30) sTemp = "will be ready soon and"; // в зависимости от времени сколько добирался
					else sTemp = "is ready and";
					dialog.text = "Czy udało ci się w twoich przedsięwzięciach? Czy pułkownik Doily był zadowolony?";
					link.l1 = " Wszystko poszło doskonale, Chevalier. Karawan Stuyvesanta został przechwycony, wszyscy niewolnicy przywiezieni na Jamajkę, eskadra pułkownika "+sTemp+"  w drodze na Curacao.";
					link.l1.go = "patria_81";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_11_return" && IsUniformEquip())
				{
					dialog.text = "Chwała zwycięzcom! Gratulacje, gratulacje, mój przyjacielu! Nigdy nie przestajesz zadziwiać.";
					link.l1 = "Dziękuję, Chevalier. Stuyvestant został ukarany i jest gotów zapłacić odszkodowania, pokój został przywrócony, Saint Martin należy teraz wyłącznie do Francji.";
					link.l1.go = "patria_85";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_continue")
				{
					dialog.text = "Tak więc, przyjacielu, cieszę się, że znów cię widzę. Czy dobrze wypocząłeś?";
					link.l1 = "Tak, Chevalier. To była bardzo potrzebna przerwa... Wspominałeś o jakimś delikatnym interesie?";
					link.l1.go = "patria_88";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_baronalive")
				{
					dialog.text = "Mój przyjacielu, musisz być czarodziejem! Udało ci się dokonać wyczynu! Nasz baron już nie chce tutaj zakładać Kompanii Handlowej.";
					link.l1 = "Wierzę, że jego jedynym życzeniem teraz jest powrót do Paryża.";
					link.l1.go = "patria_103";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_barondie")
				{
					dialog.text = "Charles, słyszałeś o baronie? Zabrali go piraci...";
					link.l1 = "Tak, Chevalier. Niestety, baron nie żyje. Wiem to na pewno.";
					link.l1.go = "patria_112";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_baronfail")
				{
					dialog.text = "Charles, jak idą twoje postępy? Powiedziano mi, że baron wszedł na pokład twojego statku...";
					link.l1 = "Tak, Chevalier. Był na pokładzie, pracowałem nad nim, ale... zmarł na gorączkę.";
					link.l1.go = "patria_x112";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_baronkilled")
				{
					dialog.text = "Charles, jak idzie ci postęp? Powiedziano mi, że baron wszedł na twój statek...";
					link.l1 = "Tak, Chevalier. Był na pokładzie, pracowałem nad nim, ale... zginął w bitwie.";
					link.l1.go = "patria_y112";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_baronwin")
				{
					dialog.text = "Mój przyjacielu, musisz być czarownikiem! Udało ci się dokonać wyczynu! Nasz baron już nie chce tworzyć tutaj Kompanii Handlowej.";
					link.l1 = "Zapewne teraz zmierza do Paryża.";
					link.l1.go = "patria_117";
					break;
				}
				dialog.text = "Czy masz jakieś pytania, Charles?";
				link.l1 = "W tej chwili nie, monsieur. W takim razie ruszam...";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Czego chcesz? Monsieur?";
			link.l1 = "Nic poważnego, tylko wizyta kurtuazyjna. Już wychodzę...";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// в тюрьме при старте игры
		case "Puancie_Jail":
			dialog.text = "Dzień dobry, Charles. Pozwól, że się przedstawię: jestem Philippe de Poincy i ja...";
			link.l1 = "Po jaką cholerę zostałem wsadzony do więzienia? To jakiś skandal! Jestem francuskim szlachcicem i...";
			link.l1.go = "Puancie_Jail_1";			
			// belamour legendary edition -->
			link.l2 = "Dobre... popołudnie? Dobry żart, Panie. Skąd wiesz, kim jestem?";
			link.l2.go = "Puancie_Jail_1a";	
		break;
		
		case "Puancie_Jail_1a":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 40);
			dialog.text = "Młody człowieku, proszę cię, abyś mi nie przerywał! Rozmawiasz z gubernatorem generalnym francuskich kolonii archipelagu Karaibów! Wybaczę twój zuchwały ton tylko dlatego, że nie mogłeś wiedzieć, kto stoi przed tobą. Ale radziłbym ci być bardziej powściągliwym.";
			link.l1 = "Hmm... Przepraszam, Wasza Łaskawość.";
			link.l1.go = "Puancie_Jail_2";
		break;
		
		case "Puancie_Jail_1":
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "FencingL", 10);
			AddCharacterExpToSkill(pchar, "FencingS", 10);
			AddCharacterExpToSkill(pchar, "FencingH", 10);
			AddCharacterExpToSkill(pchar, "Pistol", 10);
			// <-- legendary edition
			dialog.text = "Słuchaj mnie, młody człowieku, i nie przerywaj mi! Rozmawiasz z generałem-gubernatorem francuskich kolonii na karaibskim archipelagu! Wybaczę ci ton tylko z powodu twojej nieświadomości, z kim rozmawiałeś. Ale radziłbym ci w przyszłości być bardziej powściągliwym.";
			link.l1 = "Wybacz mi, Wasza Ekscelencjo.";
			link.l1.go = "Puancie_Jail_2";			
		break;
		
		case "Puancie_Jail_2":
			dialog.text = "Od razu lepiej. A teraz, odnośnie twojego poprzedniego pytania - zostałeś uznany - przez pomyłkę - za hiszpańskiego szpiega i aresztowany, dopóki nie wyjaśni się twój status. Przeklęci Kastylijczycy stali się ostatnio bardziej aktywni, dlatego nakazałem zatrzymywać wszystkich podejrzanych.\nAle teraz wiemy, kim jesteś - naprawdę jesteś Charles de Maure, bratem Michelle de Monper, i osobiście przyszedłem tutaj, aby cię uwolnić. A ty krzyczysz na mnie jak mały chłopiec!";
			link.l1 = "Przepraszam ponownie, Wasza Ekscelencjo. Czy teraz jestem wolny?";
			link.l1.go = "Puancie_Jail_3";			
		break;
		
		case "Puancie_Jail_3":
			dialog.text = "Tak, jesteś. Ale chcę porozmawiać z tobą na osobności, zanim sierżant otworzy twoją celę. Czy wiesz, że twój brat, jeden z najwartościowszych wojowników Zakonu Maltańskiego, został aresztowany i postawiony pod strażą?";
			link.l1 = "Znałem tylko, że mój brat ma kłopoty i potrzebuje pomocy. Dlatego przybyłem tutaj z Paryża.";
			link.l1.go = "Puancie_Jail_4";			
		break;
		
		case "Puancie_Jail_4":
			dialog.text = "Cieszę się, że to słyszę. Chcę, żebyś wiedział, że monsieur de Monper jest w poważnych tarapatach. Mam wszelkie powody, by podejrzewać go o nadużycie władzy, sprzeniewierzenie mienia i krzywoprzysięstwo. Ale możesz mu pomóc.";
			link.l1 = "Monsieur, czy mógłbyś mi opowiedzieć więcej? Nie rozumiem, Michel był dumą Zakonu i...";
			link.l1.go = "Puancie_Jail_5";			
		break;
		
		case "Puancie_Jail_5":
			dialog.text = "Też tak myślałem. Wszyscy tak myśleliśmy! Ale jego ostatnie działania sprawiły, że... zaczęliśmy wątpić w jego lojalność wobec Zakonu, więc został aresztowany. Michel sam opowie ci szczegóły. Wyjaśni, jak możesz mu pomóc rozwiązać oskarżenia i uniknąć hańby.";
			link.l1 = "Gdzie jest teraz mój brat? Powiedziałeś mi, że jest w więzieniu, ale nie widziałem go w pobliżu...";
			link.l1.go = "Puancie_Jail_6";			
		break;
		
		case "Puancie_Jail_6":
			dialog.text = "Powiedziałem, że jest uwięziony, młodzieńcze? Czy ty mnie w ogóle słuchasz?! Powiedziałem, że jest aresztowany! To nie to samo. Michel de Monper jest trzymany w areszcie w podziemnej bazie Saint Pierre, która jest własnością Zakonu Maltańskiego.\nPozwalam ci odwiedzać bazę bez żadnych ograniczeń i rozmawiać z bratem tak często, jak uznasz za stosowne. Oficerowie i żołnierze Zakonu są świadomi moich instrukcji i nie będą cię zatrzymywać.";
			link.l1 = "Gdzie jest ta podziemna baza?";
			link.l1.go = "Puancie_Jail_7";			
		break;
		
		case "Puancie_Jail_7":
			dialog.text = "Tutaj, w Saint Pierre oczywiście. Znajdź lokalne więzienie i wejdź przez drzwi z symbolami Zakonu. Zejdź na dół do kazamaty na drugim poziomie piwnicy. Monsieur Monper tam będzie. Ale nie martw się: przy wyjściu z więzienia zostaniesz spotkany i eskortowany do swego brata - wszystko załatwiłem... To wszystko. Mam nadzieję, że spotkamy się ponownie, Charles. Sierżancie!";
			link.l1 = "Proszę poczekać, Wasza Ekscelencjo! A co z moim... dobytkiem? Moim mieczem i resztą?";
			link.l1.go = "Puancie_Jail_8";			
		break;
		
		case "Puancie_Jail_8":
			dialog.text = "Twoje rzeczy zostały skonfiskowane na spłatę długu twojego brata. Żegnaj, Monsieur de Maure.";
			link.l1 = "Co do ch...";
			link.l1.go = "Puancie_Jail_9";			
		break;
		
		case "Puancie_Jail_9":
			DialogExit();
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Sharlie_GoFromPrison", 3.5);
			NextDiag.CurrentNode = "First time";
			locCameraFromToPos(-11.09, 0.65, 3.05, true, -12.59, 0.09, -4.66);
		break;
		
		// возвращаем деньги
		case "saga":
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Charles_townhall", "reload1_back", false);
			dialog.text = "Aha, Charles de Maure we własnej osobie! Cieszę się, że cię widzę. Rozumiem, że przyszedłeś tutaj, aby porozmawiać ze mną o losie swego brata?";
			link.l1 = "Jestem gotów spłacić to, co Michel de Monper jest winien Zakonowi i osobiście Tobie.";
			if (sti(pchar.money) >= 1000000) link.l1.go = "saga_1";
			else link.l1.go = "saga_exit";			
		break;
		
		case "saga_exit":
			dialog.text = "Hm.. Ale gdzie są pieniądze? Masz dziwne poczucie humoru, młody człowieku, i tego nie rozumiem.";
			link.l1 = "Wybacz mi, Chevalierze. Zapomniałem zabrać pieniądze z mojego kufra na statku. Wkrótce wrócę.";
			link.l1.go = "exit";
			NextDiag.TempNode = "saga_repeat";	
		break;
		
		case "saga_repeat":
			dialog.text = "„Przyniosłeś pieniądze, Charles?”";
			if (sti(pchar.money) >= 1000000)
			{
				link.l1 = "Na pewno! Mam nadzieję, że ta suma całkowicie pokryje wszystkie twoje koszty.";
				link.l1.go = "saga_1";
			}
			else
			{
				link.l1 = "Jeszcze nie...";
				link.l1.go = "exit";
				NextDiag.TempNode = "saga_repeat";
			}		
		break;
		
		case "saga_1":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Charles");
			AddMoneyToCharacter(pchar, -1000000);
			dialog.text = "Wspaniale! Wezmę je od ciebie. Pokazałeś się z najlepszej strony, Charles!";
			link.l1 = "Kiedy otrzymam rozkaz uwolnienia Michela de Monpera?";
			link.l1.go = "saga_2";			
		break;
		
		case "saga_2":
			dialog.text = "Nie śpiesz się, młody człowieku. Mogę tylko szanować, że spłacasz długi i chronisz swoją rodzinę, narażając własne życie na niebezpieczeństwo. To rzadka szlachetność w dzisiejszych czasach... Ale pieniądze nie są główną częścią tej smutnej historii. Twój brat otrzymał tak dużą sumę na warunkach bardzo delikatnej misji.\nMichel de Monper, jako wierny katolik, przysiągł na Księgę, że znajdzie sposób, aby ukarać jednego bezczelnego heretyka i przywrócić sprawiedliwość, którą naruszył dla chwały Zakonu i Świętego Kościoła...";
			link.l1 = "Ale nie będzie mógł dotrzymać słowa, będąc aresztowanym! Jeśli go uwolnisz, we dwóch będziemy w stanie ukończyć misję znacznie szybciej, niż gdybym robił to sam.";
			link.l1.go = "saga_3";			
		break;
		
		case "saga_3":
			dialog.text = "Widzisz, mój przyjacielu, twój brat dał mi silny powód, by nie ufać jego przyzwoitości. Nie ma gwarancji, że nie ucieknie i nie złamie przysięgi. Więc jeśli chcesz zdjąć z niego wszystkie zarzuty - sam złóż przysięgę. Monsieur de Monper powie ci szczegóły.";
			link.l1 = "Hm... Nie spodziewałem się tego. Ale nie pozostawiasz mi wyboru. Podejmę ostateczną decyzję po rozmowie z moim bratem.";
			link.l1.go = "saga_4";			
		break;
		
		case "saga_4":
			dialog.text = "Zaczynam cię naprawdę lubić, Charles. Być może pewnego dnia zostaniemy przyjaciółmi. W każdym razie, to mój ostatni warunek uwolnienia twojego brata. Daję ci słowo, że reputacja twojej rodziny nie ucierpi, jeśli zrobisz to, czego twój brat nie zrobił. A w przyszłości będziesz mógł liczyć na moją przyjaźń.";
			link.l1 = "Zrozumiałem w pełni. Żegnaj!";
			link.l1.go = "saga_5";			
		break;
		
		case "saga_5":
			DialogExit();
			pchar.questTemp.Saga = "mishelle";//Сага - старт
			AddQuestRecord("Sharlie", "21");
			NextDiag.CurrentNode = "First time";
			AddMapQuestMarkCity("FortFrance", false);
			AddLandQuestMark(characterFromId("Mishelle"), "questmarkmain");
		break;
		
		case "serve":
			dialog.text = "Nie martw się, "+pchar.name+"Ja dotrzymam słowa. Twój brat zostanie uwolniony, a wszystkie oskarżenia zostaną z niego zdjęte. Reputacja twojej rodziny jest teraz bezpieczna. Powiedziałbym, że to wszystko dzięki twoim zasługom i tylko twoim. Twój ojciec może być dumny, że wychował takiego syna.";
			link.l1 = "Dziękuję za miłe słowa, Chevalierze. Rozumiem, że mogę natychmiast udać się na Martynikę?";
			link.l1.go = "serve_1";	
			Island_SetReloadEnableGlobal("Tortuga", true);
			CloseQuestHeader("Terrapin");
			SetFunctionTimerCondition("Terrapin_SetFontene", 0, 0, 5, false); // таймер
		break;
		
		case "serve_1":
			dialog.text = "Poczekaj chwilę, mój przyjacielu. Mam nadzieję, że mogę cię nazywać przyjacielem, prawda? Chciałbym osobiście wyrazić swoją wdzięczność. Obserwuję twoje postępy odkąd tu dotarłeś i wiem o większości twoich uczynków. Zdobyłeś sobie wielkie imię na Karaibach i, bez wątpienia, jesteś również dobrze znany i szanowany w pewnych kręgach społeczeństwa. Francja potrzebuje ludzi takich jak ty\nKapitanie "+GetFullName(pchar)+"! Na mocy władzy, danej mi przez Jego Królewską Mość, Króla Francji, mam zaszczyt zaoferować ci patent kapitana Królewskiej Marynarki i powierzyć pod twoje dowództwo okręt francuskiej floty, lekką fregate 'Gryffondor'!\nJej były kapitan, de Fontenot, dzięki tobie zostanie gubernatorem Tortugi, a najlepsza lekka fregata na Karaibach potrzebuje kapitana. Czy przyjmujesz tę ofertę?";
			link.l1 = "Interesujące. A co w zamian?";
			link.l1.go = "serve_2";		
		break;
		
		case "serve_2":
			dialog.text = "Niewiele. Dziesięcinę z twojego połowu i okazjonalne wykonywanie delikatnych misji. Czekam na twoją decyzję.";
			link.l1 = "Żaden człowiek nie odrzuciłby takiej propozycji, Wasza Ekscelencjo! To zaszczyt służyć mojemu narodowi!";
			link.l1.go = "serve_3";
			link.l2 = "Proszę wybaczyć mi brak skromności, lecz muszę odrzucić Pańską ofertę na razie. Sprawy rodzinne mogą wymagać natychmiastowego powrotu do ojczyzny.";
			link.l2.go = "serve_no";
			InterfaceStates.Buttons.Save.enable = true;
		break;
		
		case "serve_no":
			ChangeCharacterComplexReputation(pchar, "fame", 7);
			dialog.text = "Szkoda. Miałem nadzieję, że się zgodzisz... Ale, mimo wszystko, jestem zmuszony prosić cię o jeszcze jedną przysługę, właściwie to leży to również w twoim interesie. Martynika jest pod atakiem. W porcie i w samym mieście toczą się ciężkie walki.\nNiestety, nie mam nikogo, kogo mógłbym tam wysłać, aby pomóc garnizonowi, tylko ciebie. Proszę cię jako patriote ojczyzny, byś odparł atak wszelkimi niezbędnymi środkami. Mam nadzieję, że masz wystarczające zasoby, by to zrobić.\nPoza tym, twój brat wciąż tam jest, możesz uratować jego życie.";
			link.l1 = "Mój brat jest w niebezpieczeństwie? Już ruszam!";
			link.l1.go = "serve_exit";			
		break;
		
		case "serve_3":
			dialog.text = "Takie honorowe słowa! Słowa prawdziwego żołnierza i lojalnego syna Ojczyzny! Gratulacje, monsieur "+GetFullName(pchar)+"Zostajesz mianowany dowódcą sił morskich Francji. Przyjmij ode mnie ten mundur. Noś go z dumą i bądź go godzien!";
			link.l1 = "Służę mojej ojczyźnie!";
			link.l1.go = "serve_4";	
			locCameraFromToPos(-2.63, 2.20, -4.96, true, 2.64, 0.22, -4.96);
			npchar.greeting = "puancie_1";			
		break;
		
		case "serve_4":
			dialog.text = "Lekka fregata 'Gryffondor' jest teraz pod twoim dowództwem. Od tej chwili ten doskonały okręt jest twój. Wykorzystaj jego wysokie walory dla chwały Jego Królewskiej Mości i wzmocnienia francuskiego wpływu na archipelagu Karaibskim!";
			link.l1 = "Natychmiast!";
			link.l1.go = "serve_5";
			LAi_Fade("SharlePutsSuit", "");
		break;
		
		case "serve_5":
			if (GetCompanionQuantity(pchar) > 4)
			{
				dialog.text = "Ale twoja eskadra jest już zbyt duża, więc wróć po 'Gryffondor', gdy pozbędziesz się jednego statku.";
				link.l1 = "Dobrze. Zrobię to.";
				link.l1.go = "serve_wait";		
			}
			else
			{
				dialog.text = "Oprócz statku otrzymasz jego obecnego kapitana oraz załogę. Jeśli chcesz, możesz zostawić go pod swoją komendą lub zdjąć go ze statku, a my znajdziemy mu inną posadę.";
				link.l1 = "Zrozumiano!";
				link.l1.go = "serve_6";
			}
		break;
		
		case "serve_6":
			dialog.text = "Lecz mam dla ciebie złe wieści, kapitanie. Właśnie poinformowano mnie, że Martynika jest atakowana. Toczą się ciężkie walki w porcie i w samym mieście.\nNiestety, nie mam nikogo, kogo mógłbym tam wysłać, by pomóc garnizonowi, prócz ciebie. Oto twoja pierwsza misja:\n Odzyskaj, a następnie utrzymaj Saint Pierre! Poza tym, twój brat wciąż tam jest, możesz uratować mu życie.";
			link.l1 = "Mój brat jest w niebezpieczeństwie? Już ruszam!";
			link.l1.go = "serve_7";
		break;
		
		case "serve_7":
			DialogExit();
			locCameraTarget(PChar);
			locCameraFollow();
			CreateGriffondor();
			sld = characterFromId("GriffOfficer");
			SetCharacterRemovable(sld, true);
			SetCompanionIndex(pchar, -1, sti(sld.index));
			sld.loyality = MAX_LOYALITY;
			NextDiag.CurrentNode = "First time";
			DeleteAttribute(pchar, "questTemp.Terrapin");
			pchar.questTemp.Sharlie = "senpierbattle";
			pchar.questTemp.Sharlie.DefendSP = "true";
			AddQuestRecord("Sharlie", "24");
			pchar.quest.DefendSP_prepare.win_condition.l1 = "location";
			pchar.quest.DefendSP_prepare.win_condition.l1.location = "Martinique";
			pchar.quest.DefendSP_prepare.function = "DefendSP_PrepareMartinique";
			AddCharacterExpToSkill(pchar, "Leadership", 2000);
			AddCharacterExpToSkill(pchar, "Fortune", 500);
			pchar.questTemp.GoldenGirl_Block = true;	// Запрещаем квест Дороже Золота
		break;
		
		case "serve_wait":
			DialogExit();
			NextDiag.CurrentNode = "serve_shipcheck";
		break;
		
		case "serve_shipcheck":
			dialog.text = "Czy jesteś gotów objąć dowództwo nad 'Gryffondor'?";
			if (GetCompanionQuantity(pchar) > 4)
			{
				link.l1 = "Jeszcze nie, przemieszczam moje statki w eskadrze...";
				link.l1.go = "exit";
			}
			else
			{
				link.l1 = "Jestem.";
				link.l1.go = "serve_5a";
			}
			NextDiag.TempNode = "serve_wait";
		break;
		
		case "serve_5a":
			dialog.text = "Znakomicie! Wraz ze statkiem otrzymasz jego obecnego kapitana i załogę. Jeśli chcesz, możesz go zostawić pod swoim dowództwem lub mu podziękować, a my znajdziemy dla niego inną pozycję.";
			link.l1 = "Zrozumiano!";
			link.l1.go = "serve_6";
		break;
		
		case "serve_exit":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			DeleteAttribute(pchar, "questTemp.Terrapin");
			pchar.questTemp.Sharlie = "senpierbattle";
			pchar.questTemp.Sharlie.DefendSP = "true";
			AddQuestRecord("Sharlie", "23");
			pchar.quest.DefendSP_prepare.win_condition.l1 = "location";
			pchar.quest.DefendSP_prepare.win_condition.l1.location = "Martinique";
			pchar.quest.DefendSP_prepare.function = "DefendSP_PrepareMartinique";
			AddCharacterExpToSkill(pchar, "Leadership", 1000);
			AddCharacterExpToSkill(pchar, "Fortune", 250);
		break;
		
		// Jason НСО
		case "patria":
			if (CheckAttribute(pchar, "questTemp.Mtraxx.CharleePrince")) DeleteAttribute(pchar, "questTemp.Mtraxx.CharleePrince"); // Rebbebion, удалить команду пиратов на всякий
			dialog.text = "A to dopiero początek, Monsieur! Jestem pewien, że zajdziesz daleko z takim wojskowym talentem! I już mam kolejne zlecenie dla znakomitego oficera marynarki, z którym, jestem przekonany, poradzisz sobie równie dobrze. Co więcej, jest ono bezpośrednio związane z twoją poprzednią misją.";
			link.l1 = "Zamieniam się w słuch, monsieur";
			link.l1.go = "patria_1";
		break;
		
		case "patria_1":
			dialog.text = "Pozwól, że najpierw przedstawię ci osobę, która weszła do mojego gabinetu. Poznaj barona Noela Forgeta, honorowego członka Francuskiej Kompanii Handlowej Indii Zachodnich. Przybył na archipelag, aby zbadać nasze kolonie w celu rozszerzenia organizacji plantacji trzciny cukrowej i innych upraw, a także zbadania możliwości rozwoju więzi handlowych w naszym regionie. Z Paryża zalecono, aby udzielić mu wszelkiego rodzaju wsparcia i pomocy w tych kwestiach, co niewątpliwie uczynimy. Baronie, przedstawiam ci pana Charlesa de Maure, jednego z najzdolniejszych kapitanów w służbie Francji...";
			link.l1 = "";
			link.l1.go = "patria_2";
		break;
		
		case "patria_2":
			DialogExit();
			sld = characterFromId("Noel");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "patria_3":
			dialog.text = "Więc, Charles, podczas gdy ja i baron inspekcjonujemy Saint Christopher, przydzielam ci następujące zadanie. Nikt nie może atakować francuskich osiedli i oczekiwać, że ujdzie mu to na sucho, a Hiszpanie, choć już zostali ukarani za agresję na Martynikę, muszą odpowiedzieć za swoje zbrodnie i zrekompensować szkody wyrządzone kolonii swoimi sakwami.\nRazem z francuskim baronem przybyła potężna eskadra składająca się z potężnego 66-działowego okrętu 'Eclatant'. Kapitan statku to doświadczony żeglarz, ale po raz pierwszy na Karaibach, więc podlega twojemu dowództwu. Razem z 'Eclatant' wyruszysz na wybrzeża hiszpańskiej wyspy Trynidad i zażądasz od Hiszpanów odszkodowania pieniężnego w wysokości trzystu tysięcy pesos za atak na Saint Pierre.";
			link.l1 = "Chevalier, czy naprawdę wierzysz, że Hiszpanie się zgodzą?";
			link.l1.go = "patria_4";
		break;
		
		case "patria_4":
			dialog.text = "Jestem tego pewien - po tym, jak 'Eclatant' i twoja eskadra zdmuchnie Fort w San Jose z powierzchni ziemi. Lądowanie wojsk i zajmowanie miasta, tracenie żołnierzy, myślę, że nie będzie potrzebne. Atakuj bez ostrzeżenia, zniszcz fort, a potem daj sygnał komendantowi, że chcesz ustalić warunki. W tej sytuacji Hiszpanie nie będą mieli dokąd się udać i woleliby zapłacić. Co byś zrobił, gdybyś działał na miejscu gubernatora miasta, które zostało bez ochrony?";
			link.l1 = "Hmm, to wydaje się rozsądne, Chevalier.";
			link.l1.go = "patria_5";
		break;
		
		case "patria_5":
			dialog.text = "Czy jest jasne, co masz zrobić?";
			link.l1 = "Tak, Wasza Łaskawość.";
			link.l1.go = "patria_6";
		break;
		
		case "patria_6":
			// belamour legendary edition фикс проверки мундира с мушкетом
			if(IsUniformEquip())
			{
				dialog.text = "Zatem do dzieła. Oto list do kapitana 'Eclatant' z potwierdzeniem twojej władzy. Ten doskonały statek z dobrze wyszkoloną załogą jest teraz do twojej dyspozycji. Charles, i nie zapomnij, że teraz służysz Francji, a aby odpowiednio komunikować się z urzędnikami jak ja, zaleca się noszenie munduru. Doskonale ci pasuje. Powodzenia, kapitanie de Maure!";
			}
			else
			{
				dialog.text = "To do dzieła. Oto list do Kapitana 'Eclatant' z potwierdzeniem twoich uprawnień. Ten doskonały okręt z dobrze wyszkoloną załogą jest teraz do twojej dyspozycji. Ach, i Charles: załóż mundur kapitana, rozkazuję ci! Po pierwsze, nie przystoi oficerowi Królewskiej Marynarki Francuskiej wyglądać jak handlarz czy jakiś korsarz, a po drugie, mundur doskonale ci pasuje. Wykonać natychmiast, Kapitanie de Maure!";
			}
			link.l1 = "";
			link.l1.go = "patria_7";
		break;
		
		case "patria_7":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			LAi_SetHuberType(npchar);
			AddQuestRecord("Patria", "1");
			pchar.questTemp.Patria = "epizode_1";
			Patria_SetEcliaton();
			pchar.questTemp.GoldenGirl_Block = true;	// Запрещаем квест Дороже Золота
		break;
		
		case "patria_8_1":
			if (sti(pchar.money) >= 300000) AddMoneyToCharacter(pchar, -300000);
			else pchar.questTemp.Patria.NoMoney = "true";
			dialog.text = "'Eclatant' zatonął? Charles, to katastrofa! Co teraz powie minister? Zawiodłeś mnie, Charles! Byłem pewien, że mogę polegać na twoim doświadczeniu, a ty... Niestety, ale poniesiesz za to odpowiedzialność. Napiszę raport, a ty lepiej zniknij na jakiś czas. Twoja służba w Królewskiej Marynarce dobiegła końca.";
			link.l1 = "Hmm... Przykro mi, Monsieur. Wygląda na to, że naprawdę lepiej będzie, jeśli zniknę na miesiąc lub dwa, aż minister uspokoi swój gniew. Żegnaj, i jeszcze raz bardzo przepraszam, że cię zawiodłem.";
			link.l1.go = "patria_8_2";
		break;
		
		case "patria_8_2":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			pchar.questTemp.Patria = "fail";
			AddQuestRecord("Patria", "8");
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			RemoveItems(pchar, "patent_fra", 1);
			if (CheckAttribute(pchar, "questTemp.Patria.NoMoney"))
			{
				ChangeCharacterComplexReputation(pchar, "nobility", -20);
				ChangeCharacterNationReputation(pchar, FRANCE, -30);
				DeleteAttribute(pchar, "questTemp.Patria.NoMoney");
			}
			else
			{
				ChangeCharacterComplexReputation(pchar, "nobility", -5);
				ChangeCharacterNationReputation(pchar, FRANCE, -5);
			}
			pchar.quest.Patria_SanJoseReturnOver.over = "yes"; // снять таймер
		break;
		
		case "patria_8":
			if (sti(pchar.money) >= 300000)
			{
				dialog.text = "Doskonale!";
				link.l1 = "Proszę, weź te trzysta tysięcy.";
				link.l1.go = "patria_9";
			}
			else
			{
				dialog.text = "Doskonałe, ale gdzie są pieniądze, Charles?";
				link.l1 = "Aha, W skrzyni na statku, dostarczę to za chwilę!";
				link.l1.go = "patria_8_3";
			}
		break;
		
		case "patria_8_3":
			DialogExit();
			npchar.dialog.currentnode = "patria_8_4";
		break;
		
		case "patria_8_4":
			dialog.text = "Więc, Charles, czy przyniosłeś okup z Trynidadu?";
			if (sti(pchar.money) >= 300000)
			{
				link.l1 = "Tak, Monsieur. Oto jest.";
				link.l1.go = "patria_9";
			}
			else
			{
				link.l1 = "Zaraz go przyniosę!";
				link.l1.go = "patria_8_3";
			}
		break;
		
		case "patria_9":
			AddMoneyToCharacter(pchar, -300000);
			dialog.text = "Jestem z ciebie zadowolony, Charles, nigdy mnie nie zawodzisz. Zadanie nie było łatwe, a ty otrzymujesz nagrodę w wysokości 50 000 pesos z kwoty wykupu. Weź to, wszystko jest twoje.";
			link.l1 = "Moje dzięki, Chevalier.";
			link.l1.go = "patria_10";
		break;
		
		case "patria_10":
			AddMoneyToCharacter(pchar, 50000);
			dialog.text = "Jest już dla ciebie nowe zadanie. Monsieur Forget zakończył inspekcję na Saint Christopher i teraz pragnie odwiedzić nasze północne kolonie. Proszę cię, abyś zabrał barona na Tortugę i Hispaniolę, pomógł mu we wszystkich jego sprawach i spełnił jego prośby. Czy to jasne, Charles?";
			link.l1 = "Oczywiście, Chevalier.";
			link.l1.go = "patria_11";
		break;
		
		case "patria_11":
			dialog.text = "Baron ma mało czasu, więc proszę cię, byś nie rozpraszał się na inne sprawy i nie opóźniał podróży na dłużej niż dwa miesiące.";
			link.l1 = "Oczywiście, Monsieur. Podróż między wyspami nie zajmuje tyle czasu, chyba że sprawy Monsieura Forgeta w koloniach są czasochłonne.";
			link.l1.go = "patria_12";
		break;
		
		case "patria_12":
			dialog.text = "Doskonale. W takim razie baron popłynie na twoim statku. Daj mu najlepszą kajutę, jaką masz.";
			link.l1 = "Oczywiście, Chevalier!";
			if(IsUniformEquip()) link.l1.go = "patria_13";
			else link.l1.go = "patria_13_1";
		break;
		
		case "patria_13_1":
			dialog.text = "I jeszcze jedno, Charles: Znowu jesteś bez munduru oficerskiego! To jest twoje ostatnie ostrzeżenie. Od tej chwili proszę, abyś przychodził do mnie tylko w mundurze, w przeciwnym razie nie będę cię słuchać. Jesteś na służbie, a dyscyplina powinna być wszystkim, zwłaszcza w wyglądzie oficera marynarki!";
			link.l1 = "Proszę o wybaczenie, Chevalierze. To się więcej nie powtórzy.";
			link.l1.go = "patria_13";
		break;
		
		case "patria_13":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			AddQuestRecord("Patria", "9");
			pchar.questTemp.Patria = "epizode_2";
			Patria_VisiterBegin();
			pchar.quest.Patria_SanJoseReturnOver.over = "yes"; // снять таймер
			ChangeCharacterNationReputation(pchar, FRANCE, 10);
			ChangeCharacterComplexReputation(pchar, "nobility", 3); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
		break;
		
		case "patria_14":
			sld = characterFromId("Noel");
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto4");
			dialog.text = "Nie miałem wątpliwości, że twoja podróż zakończy się sukcesem. Czy są jakieś wieści z Tortugi lub z Port-au-Prince?";
			link.l1 = "...";
			link.l1.go = "patria_15";
		break;
		
		case "patria_15":
			DialogExit(); // переключение на инспектора
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Noel"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_16";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			bDisableCharacterMenu = true;//лоченые интерфейсы
		break;
		
		case "patria_16":
			dialog.text = "";
			link.l1 = "Tak, Chevalier, przynoszę wieści, ale nie są one zbyt przyjemne. Po pierwsze, gubernator Port-au-Prince jest pewien, że Hiszpanie przygotowują atak na kolonię i w tym celu zbierają eskadrę wojskową na... em-m, jak to się nazywa... na Santiago, tak. I to nie wydaje się być plotką. Uważam, że nie możemy zignorować tej sprawy, zwłaszcza że plantacje Port-au-Prince są jednymi z najlepszych, jakie kiedykolwiek widziałem.";
			link.l1.go = "patria_17";
		break;
		
		case "patria_17":
			dialog.text = "Czy Hiszpanie szykują się do ataku na Port-au-Prince? Hmm... Dobrze. Poinstruujemy cię, jak poradzić sobie z tym kapitanem Charlesem de Maure. 'Eclatant' jest właśnie naprawiony, wyposażony i gotowy do żeglugi...";
			link.l1 = "I jeszcze jedna rzecz, monsieur: w Paryżu wyspę Saint Martin, która leży na północ stąd, uważa się za francuską kolonię, ale kapitan Charles de Maure powiedział mi, że kontrolują ją Holendrzy. Czy to prawda, Chevalier?";
			link.l1.go = "patria_18";
		break;
		
		case "patria_18":
			dialog.text = "Hmm... To prawda do pewnego stopnia. Saint Martin to francuska kolonia. Jednakże, Baron, z ekonomicznego punktu widzenia, ta wyspa jest absolutnie bezużyteczna - obszar jest mały, gleba tam jest skąpa, wychudzona, świeżej wody jest niewiele, a ta, która jest w studniach, jest mętna i gorzka. Powiedziano mi nawet, że tam zbierano deszczówkę do picia.\nDlatego Saint Martin został przekazany Holenderskiej Kompanii Zachodnioindyjskiej w długoterminową dzierżawę, która wykorzystuje go jako północny punkt tranzytowy dla statków Kompanii z regionu do metropolii. Holendrzy rozszerzyli tam osadę Phillipsburg, zbudowali fort i port, a dla tych, którzy przybyli do archipelagu stosunkowo niedawno, jak kapitan Charles de Maure, Saint Martin wydaje się być holenderską kolonią.";
			link.l1 = "Ale de jure wyspa należy do nas?";
			link.l1.go = "patria_19";
		break;
		
		case "patria_19":
			dialog.text = "Oczywiście. Ale jak już powiedziałem, bardziej opłaca się otrzymywać pieniądze za wynajem niż korzystać z jego skąpych zasobów.";
			link.l1 = "Wydaje mi się, że ta wyspa byłaby bardzo przydatna dla Francuskiej Kompanii Handlowej Indii Zachodnich, gdy pojawi się na Karaibach. Znaczenie, które właśnie ogłosiłeś - północna placówka na drodze do Europy. Muszę odwiedzić tę kolonię i bardzo prawdopodobne, że wynajem wyspy dla Holendrów zostanie przerwany.";
			link.l1.go = "patria_20";
		break;
		
		case "patria_20":
			dialog.text = "Najpierw musisz wysłać zapytanie do Willemstad, do dyrektora Holenderskiej Kompanii Zachodnioindyjskiej, Mince Piotra Stuyvesanta. On musi dać swoje pozwolenie na inspekcję wyspy - w końcu Holendrzy są tam od dawna.";
			link.l1 = "Zatem musimy wysłać kuriera do Willemstad.";
			link.l1.go = "patria_21";
		break;
		
		case "patria_21":
			dialog.text = "Problem polega na tym, że pan Stuyvesant rzadko bywa w Willemstad, ciągle podróżuje i zajmuje się sprawami Kompanii na swoim galeonie...";
			link.l1 = "Ale przynajmniej czasami tam bywa, jak sądzę? Tak czy inaczej, Holendrzy są zobowiązani zapewnić inspekcję wyspy jej prawowitym właścicielom. Dlaczego nie wyślemy listu do gubernatora Philipsburga?";
			link.l1.go = "patria_22";
		break;
		
		case "patria_22":
			dialog.text = "Mynheer Martin Thomas, z całym należnym mu szacunkiem, jest tylko prostym pracownikiem, prawdziwym zarządem zajmuje się Kompania. Baronie, rozwiążę ten problem, nie martw się, to zajmie trochę czasu.";
			link.l1 = "Cóż, mam mnóstwo czasu. W końcu musimy jeszcze odwiedzić południowe kolonie, Gwadelupę i Martynikę. Szkoda, że kapitan Charles de Maure nie towarzyszy mi tym razem - musi znów udać się na Hispaniolę...";
			link.l1.go = "patria_23";
		break;
		
		case "patria_23":
			DialogExit();
			LAi_SetActorType(pchar); // 17-add
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_24";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			ChangeCharacterNationReputation(pchar, FRANCE, 10);
		break;
		
		case "patria_24":
			dialog.text = "Tak, tak, opóźniamy naszego drogiego kapitana naszymi nudnymi rozmowami! Charles, zabierz 'Eclatant' do eskadry, skieruj się na Hispaniolę i dowiedz się o jakichkolwiek prawdziwych zagrożeniach dla Port-au-Prince ze strony Hiszpanów. Jeśli jakieś są, to się nimi zajmij. Jednak nie mnie uczyć Ciebie, wiesz wszystko lepiej niż ja. Jeśli niczego nie znajdziesz, nie trać czasu, potrzebuję Cię tutaj. Czekam na Twój raport nie później niż za miesiąc. Powodzenia, przyjacielu!";
			link.l1 = "Dziękuję, Chevalier. Wypłynę natychmiast.";
			if (ChangeCharacterHunterScore(pchar, "holhunter", 0) > 10) link.l1.go = "patria_25_1";
			else link.l1.go = "patria_25_2";
		break;
		
		case "patria_25_1":
			dialog.text = "I jeszcze jedna sprawa, Charles: Słyszałem, że masz problemy z holenderskimi władzami? Proszę, załatw tę sprawę jak najszybciej, w najbliższej przyszłości będziesz musiał odwiedzić ich kolonie. Jak rozumiesz, to byłoby niemożliwe pod ostrzałem z fortów.";
			link.l1 = "W porządku, Monsieur, zostanie to zrobione.";
			link.l1.go = "patria_25";
		break;
		
		case "patria_25_2":
			dialog.text = "I jeszcze jedno, Charles: ostrzegam cię: unikaj wszelkich konfliktów z Holendrami. W najbliższej przyszłości będziesz musiał odwiedzić ich kolonie. Jak rozumiesz, byłoby to niemożliwe pod ostrzałem z fortów...";
			link.l1 = "Dobrze, Monsieur. Bez kłótni z Holendrami.";
			link.l1.go = "patria_25";
		break;
		
		case "patria_25":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			LAi_SetHuberType(npchar);
			AddQuestRecord("Patria", "15");
			pchar.questTemp.Patria = "epizode_3";
			Patria_PortPaxBegin();
			ChangeCharacterComplexReputation(pchar, "nobility", 1); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		case "patria_26_1":
			dialog.text = "'Éclatant' zatonął? Charles, to katastrofa! Co teraz powie minister? Zawiodłeś mnie, Charles! Byłem pewien, że mogę polegać na twoim doświadczeniu, a ty... Niestety, ale będziesz musiał za to odpowiedzieć. Napiszę raport, a ty lepiej zniknij na jakiś czas. Twoja służba w Królewskiej Marynarce jest zakończona.";
			link.l1 = "Hmm ... Przepraszam, monsieur. Wydaje się, że rzeczywiście lepiej będzie, jeśli zniknę na miesiąc lub dwa, aż minister się uspokoi. Żegnaj, i jeszcze raz bardzo przepraszam, że cię zawiodłem.";
			link.l1.go = "patria_26_2";
		break;
		
		case "patria_26_2":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			pchar.questTemp.Patria = "fail";
			AddQuestRecord("Patria", "19");
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			RemoveItems(pchar, "patent_fra", 1);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			ChangeCharacterNationReputation(pchar, FRANCE, -5);
			pchar.quest.Patria_PortPaxOver.over = "yes"; // снять таймер
		break;
		
		case "patria_26":
			dialog.text = "Znakomicie! Dopóki mamy w naszej marynarce takich kapitanów jak ty, nie musimy się obawiać podstępów Kastylijczyków. Jutro wyślę kuriera do Port-au-Prince z depeszą oraz pocztą z Francji, a jednocześnie wspomnę w osobistym liście do Monsieur Jeremy'ego Deschamps du Mussaca, że byłoby miło podziękować ci za służbę, tak więc mogę zapewnić, że ty, Charles, otrzymasz zasłużoną nagrodę.\nA teraz przejdźmy do twojego następnego zadania. Tak, mój przyjacielu, mam dla ciebie nowe zadanie, jednak tym razem nie wojskowe, lecz bardzo delikatne, i chciałbym, abyś się nim zajął.";
			link.l1 = "Zamieniam się w słuch, Chevalierze.";
			link.l1.go = "patria_27";
		break;
		
		case "patria_27":
			dialog.text = "Przypuszczam, że pamiętasz moją rozmowę z Monsieur Forget na temat Saint Martin? Musimy zapewnić barona, że kolonia została skontrolowana, a ty pojedziesz na Curacao, do Willemstad, do dyrektora Kompanii Petera Stuyvesanta. Jest tam teraz i będzie jeszcze przez trzy tygodnie. Ponadto, będziesz musiał eskortować fluit z towarami Kompanii na Curacao i przekazać Mynheerowi Stuyvesantowi list ode mnie.";
			link.l1 = "Czy to wszystkie zadania?";
			link.l1.go = "patria_28";
		break;
		
		case "patria_28":
			dialog.text = "Tak, kapitanie. Poinformuj mnie o odpowiedzi Pana Stuyvesanta. Powinniśmy zdążyć na czas, zanim Monsieur Forget wróci z podróży na Martynikę i Gwadelupę, i wreszcie będzie mógł odwiedzić Saint Martin, które naprawdę chce zobaczyć.";
			link.l1 = "Bardzo dobrze. Czy mogę iść?";
			link.l1.go = "patria_29";
		break;
		
		case "patria_29":
			dialog.text = "Możesz, Charles. Nie zwlekaj zbyt długo, baron nie lubi czekać. I odwiedzając Petera Stuyvesanta, upewnij się, że masz na sobie mundur! Wszystko musi wyglądać oficjalnie, jeśli wiesz, co mam na myśli.";
			link.l1 = "Oczywiście, Chevalier. Do widzenia!";
			link.l1.go = "patria_30";
		break;
		
		case "patria_30":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			AddQuestRecord("Patria", "20");
			pchar.questTemp.Patria = "epizode_4";
			Patria_CureerBegin();
			pchar.quest.Patria_PortPaxOver.over = "yes"; // снять таймер
			GiveItem2Character(pchar, "Reserve_item_01");
			ChangeItemDescribe("Reserve_item_01", "itmdescr_Reserve_item_01_1");
			ChangeCharacterNationReputation(pchar, FRANCE, 10);
			ChangeCharacterComplexReputation(pchar, "nobility", 5); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 5);
			ChangeCharacterComplexReputation(pchar, "fame", 5);
		break;
		
		case "patria_31":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "Dziękuję, kapitanie, daj mi to... (czyta)... No cóż, doskonale! Peter Stuyvesant mówi, że baron Forget będzie mógł odwiedzić Saint Martin w celu inspekcji i że gubernator Philipsburga zostanie o tym poinformowany i będzie współpracował. Myślę, że po wizycie baron podejmie właściwą decyzję - pozostawić wyspę do wynajęcia Holendrom.\nA teraz, najcieplejsze wiadomości, kapitanie! Mam kilka rzeczy do przekazania. Po pierwsze: biorąc pod uwagę wszystkie twoje wojskowe osiągnięcia, awansujesz na stanowisko 'Komandora'. Przyjmij moje gratulacje, Monsieur!";
			link.l1 = "Służę Francji!";
			link.l1.go = "patria_32";
		break;
		
		case "patria_32":
			dialog.text = "A po drugie: gubernator Port-au-Prince przesłał nam statek handlowy pełen towarów dla ciebie: 500 dużych worków kawy i 500 worków kakao. To wszystko zbiory plantacji na Hispanioli, tych, które ochroniłeś przed hiszpańskimi napadami. Również szczególnie cenny ładunek był przeznaczony dla ciebie - 50 jednostek drewna guajakowego. Nie sądzę, bym musiał ci tłumaczyć, co to jest. Twoje towary znajdują się w magazynie w sklepie w Capsterville i możesz je odebrać od kupca w dowolnym momencie.";
			link.l1 = "Dziękuję, Chevalier! Fantastyczne wieści!";
			link.l1.go = "patria_33";
		break;
		
		case "patria_33":
			dialog.text = "A teraz, co do twojego następnego zadania: Baron Forget wróci do Saint-Christopher w każdej chwili. Zabierzesz go do Saint Martin i upewnisz się, że jest dobrze strzeżony. I, że tak powiem, będziesz uważnie obserwował, co się dzieje w Philipsburgu, a potem złożysz mi raport. Nie opuszczaj miasta, kapitanie, gdy tylko baron przybędzie - mój sługa cię znajdzie i złoży raport.";
			link.l1 = "Wszystko jasne. Mogę już iść?";
			link.l1.go = "patria_34";
		break;
		
		case "patria_34":
			dialog.text = "Możesz. Kilka dni odpoczynku na lądzie będzie dla ciebie dobre i pożyteczne.";
			link.l1 = "...";
			link.l1.go = "patria_35";
		break;
		
		case "patria_35":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			AddQuestRecord("Patria", "25");
			pchar.questTemp.Patria = "epizode_5";
			pchar.quest.Patria_CureerBackOver.over = "yes"; // снять таймер
			Items[sti(pchar.EquipedPatentId)].TitulCur = 4; 
        	Items[sti(pchar.EquipedPatentId)].TitulCurNext = 0;
			pchar.quest.Patria_SanMartin_wait.win_condition.l1 = "Timer";
			pchar.quest.Patria_SanMartin_wait.win_condition.l1.date.hour  = 8+rand(2);
			pchar.quest.Patria_SanMartin_wait.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1+rand(1));
			pchar.quest.Patria_SanMartin_wait.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1+rand(1));
			pchar.quest.Patria_SanMartin_wait.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1+rand(1));
			pchar.quest.Patria_SanMartin_wait.win_condition.l2 = "Location_Type";
			pchar.quest.Patria_SanMartin_wait.win_condition.l2.location_type = "town";
			pchar.quest.Patria_SanMartin_wait.function = "Patria_SanMartinBaron";
			pchar.questTemp.Patria.Goods = "true"; // товары-призы
			bQuestDisableMapEnter = true;//закрыть карту
			pchar.GenQuest.MapClosedNoBattle = true;
			ChangeCharacterComplexReputation(pchar, "nobility", 1); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		case "patria_36":
			DialogExit(); // переключение на инспектора
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Noel"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_37";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			bDisableCharacterMenu = true;//лоченые интерфейсы
		break;
		
		case "patria_37":
			dialog.text = "";
			link.l1 = "Tak, Chevalier, już z powrotem! Twoi holenderscy przyjaciele w pobliżu Saint Martin przywitali nas ogniem z dział fortu i zaatakowali nas eskadrą trzech statków. Tylko dzięki umiejętnościom kapitana Charlesa de Maure i jego załogi udało nam się uciec! Wydaje się, że Mynheer Peter Stuyvesant naprawdę nie chce widzieć wysłanników francuskiego króla w Philipsburgu, co o tym myślisz, Chevalier?";
			link.l1.go = "patria_38";
		break;
		
		case "patria_38":
			dialog.text = "Co?! Oto list od Stuyvesanta z jego osobistym podpisem, w którym gwarantuje...";
			link.l1 = "Lecz komendant fortu Philipsburg najwyraźniej otrzymał inny list od Stuyvesanta, nakazujący mu strzelać do woli i zastawić na nas zasadzkę z eskadrą! Czy to był przypadek, Chevalier?! Nie! Oni wyraźnie czekali tam na nas! Z kulami armatnimi i śrutem!";
			link.l1.go = "patria_39";
		break;
		
		case "patria_39":
			dialog.text = "Baronie, błagam... Zajmę się tym. Natychmiast wyślemy naszego drogiego kapitana, Charlesa de Maure, ponownie na Curacao, by spotkał się ze Stuyvesantem. Kapitan ma długą historię radzenia sobie z delikatnymi sytuacjami... A teraz poproszę służbę, by przygotowała kąpiel i dobry obiad dla ciebie.";
			link.l1 = "...";
			link.l1.go = "patria_40";
		break;
		
		case "patria_40":
			DialogExit();
			LAi_SetActorType(pchar); // 14-add
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_41";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "patria_41":
			dialog.text = "Charles, mój przyjacielu, musisz się spieszyć do Willemstad. Być może Stuyvesant wciąż tam jest. Jeśli nie - dowiedz się, gdzie się znajduje, i go znajdź. Podczas spotkania opowiedz mu o incydencie i zażądaj wyjaśnień. Polegam na twoim doświadczeniu i autorytecie, i powierzam ci przeprowadzenie negocjacji. Następnie, nie tracąc ani minuty, wróć i zdaj mi relację z wyników spotkania.";
			link.l1 = "Zadanie jest jasne, Chevalier. Przygotuję statek i wyruszę natychmiast.";
			link.l1.go = "patria_42";
		break;
		
		case "patria_42":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			LAi_SetHuberType(npchar);
			AddQuestRecord("Patria", "29");
			pchar.questTemp.Patria = "epizode_6";
			Patria_DiplomatBegin();
			ChangeCharacterComplexReputation(pchar, "nobility", 3); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
		break;
		
		case "patria_43":
			dialog.text = "Nie mogę w to uwierzyć...";
			link.l1 = "Co więcej, w drodze powrotnej zostałem zaatakowany przez eskadrę holenderskiej marynarki wojennej. Proszę, wyjaśnij mi, Szewalierze, co tu się dzieje?";
			link.l1.go = "patria_44";
		break;
		
		case "patria_44":
			dialog.text = "Mój przyjacielu, wiem, jak spostrzegawczy jesteś, więc niczego przed tobą nie ukryję. Jedyne, o co cię proszę - to, co usłyszysz, nie może opuścić tego pokoju. Czy obiecujesz?";
			link.l1 = "Oczywiście, Chevalier.";
			link.l1.go = "patria_45";
		break;
		
		case "patria_45":
			dialog.text = "Dobrze. Jestem pewien, że czeka cię wielka kariera we francuskiej marynarce. Oczywiście, z moją pomocą możesz awansować do rangi wiceadmirała! Ale odbiegam od tematu... A teraz, co do Holendrów i Saint Martin.\nDługo przed twoim przybyciem na Saint Martin, odkryto tam duże złoża soli. Na początku nikt się tym nie przejmował, ale potem Hiszpanie na Kubie i Hispanioli wyrazili wielkie zainteresowanie – aby solić tusze byków. Jak zapewne rozumiesz, nie możemy handlować bezpośrednio z Hiszpanią, dlatego...";
			link.l1 = "...stworzyłeś 'negocjatora' w formie Holenderskiej Kompanii Zachodnioindyjskiej...";
			link.l1.go = "patria_46";
		break;
		
		case "patria_46":
			dialog.text = "Właśnie tak! Myślisz szybko - i trafnie, Charles! A teraz, wiedząc o inspekcji z Paryża, Stuyvesant postanowił śmiało przejąć interes solny w swoje ręce, licząc na to, że nie jesteśmy chętni opowiadać wszystkim o naszej umowie z Hiszpanami. Ale tu się pomylił. Nikt nie może odważyć się zabrać z rąk francuskiego gubernatora generalnego bez kary! I pokażemy mu to.";
			link.l1 = "Jak rozumiem, baron Forget nie może o tym wiedzieć...";
			link.l1.go = "patria_47";
		break;
		
		case "patria_47":
			dialog.text = "Mój przyjacielu, masz absolutną rację, baron nie musi znać szczegółów. Wystarczy, że już się wydarzyło: próba zamachu na życie przedstawiciela króla Francji, atak na statki misji dyplomatycznej, to znaczy - na ciebie, a co najważniejsze: de facto aneksja wyspy Saint Martin! To wystarczy, aby uzasadnić działania wojenne przeciwko Holendrom.";
			link.l1 = "Wojna?!";
			link.l1.go = "patria_48";
		break;
		
		case "patria_48":
			dialog.text = "Dokładnie! Mój przyjacielu, stanowisko wiceadmirała nie jest dla ciebie tak odległe, rozumiesz? Wyobraź sobie siebie na rozmowach w Luwrze w mundurze admirała, a sam Ludwik XIV przyjmie takiego zaszczytnego gościa... Musimy postawić Holendrów na ich miejscu! Stuyvesant pożałuje tego, co zrobił. Zgadzasz się?";
			link.l1 = "Zgadzam się, Chevalier. Holendrzy muszą odpowiedzieć za swoje oburzające i nikczemne czyny.";
			link.l1.go = "patria_49";
		break;
		
		case "patria_49":
			dialog.text = "Doskonałe. Powiadomię barona o naszej decyzji i natychmiast wyślę kurierów do francuskich kolonii! A ty, mój przyjacielu, możesz odpocząć po długiej drodze, a jutro po dziewiątej rano proszę mnie odwiedzić. Przygotuję dla ciebie zadanie bojowe.";
			link.l1 = "Zgoda, Monsieur. Pozwól, że się oddalę.";
			link.l1.go = "patria_50";
		break;
		
		case "patria_50":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			LAi_SetHuberType(npchar);
			AddQuestRecord("Patria", "33");
			pchar.questTemp.Patria = "epizode_7";
			Patria_HunterBegin();
			pchar.quest.Patria_DiplomatTimeOver.over = "yes"; // снять таймер
			ChangeCharacterComplexReputation(pchar, "nobility", 1); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		case "patria_51":
			dialog.text = "Nie nazwałbym tego wojną, raczej wymuszeniem pokoju w rzeczywistości. A jeśli Stuyvesant zmieni zdanie, to tylko nas uszczęśliwi. Dlatego teraz musimy pokazać mu, że próbując zdobyć wyspę Saint Martin, straci znacznie więcej, niż zyska. I tutaj wchodzisz do gry, Charles.";
			link.l1 = "Słucham.";
			link.l1.go = "patria_52";
		break;
		
		case "patria_52":
			dialog.text = "Saint Martin jest bazą przeładunkową dla holenderskich statków zmierzających do Europy. Statki Kompanii regularnie zatrzymują się w zatoce w Philipsburgu. Do tej pory wody były dla nich dość bezpieczne. Do tej pory, Kapitanie!.. Wyruszysz na wybrzeża Saint Martin i będziesz je patrolować oraz przechwytywać handlowe statki Kompanii.\nDo transportu cennych towarów Kompania wykorzystuje East-Indians - twarde, dobrze uzbrojone statki z dużymi ładowniami. To będą twoje cele. Przechwyć pięć takich statków wraz z ich towarami i przywieź je jako nagrody do Casterville. Po tym będziemy kontynuować negocjacje ze Stuyvesantem, a być może, po zliczeniu strat, zmieni zdanie.";
			link.l1 = "Zadanie jest jasne. Mogę iść?";
			link.l1.go = "patria_53";
		// belamour legendary edition -->
			link.l2 = "Monsieur, jestem zmuszony zapytać, ale czy mógłbyś wziąć udział w finansowaniu tej operacji. To będą miesiące żeglugi, ciągłe naprawy i straty...";
			link.l2.go = "patria_53a";
		break;
		
		case "patria_53a":
			AddMoneyToCharacter(pchar, 20000);
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			dialog.text = "Obawiam się, że nasze rezerwy są wyczerpane, Charles. Utrzymanie Ecliaton i walki kosztowały nas już półroczny budżet francuskich kolonii. Teraz to wszystko, co mogę ci teraz dać. Pomyśl o przyszłych nagrodach, Charles! Czeka cię wielka przyszłość!";
			link.l1 = "Tak jest, sir!";
			link.l1.go = "patria_54";
		break;
		// <-- legendary edtion
		case "patria_53":
			dialog.text = "Idź, mój przyjacielu, i niech szczęście towarzyszy każdemu twemu krokowi.";
			link.l1 = "...";
			link.l1.go = "patria_54";
		break;
		
		case "patria_54":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			AddQuestRecord("Patria", "34");
			pchar.questTemp.Patria = "epizode_7_continue";
			Patria_HunterContinue();
		break;
		
		case "patria_55":
			pchar.questTemp.Patria.Hunter = sti(pchar.questTemp.Patria.Hunter)+1;
			if (sti(pchar.questTemp.Patria.Hunter) > 4) // все собрал
			{
				dialog.text = "Zadanie zostało wykonane, kapitanie. Dziękuję za doskonałą służbę! Powinieneś otrzymać część dochodu ze sprzedaży trofeów - dwieście tysięcy pesos.";
				link.l1 = "Cieszę się, że to słyszę, monsieur!";
				link.l1.go = "patria_57";
			}
			else
			{
				dialog.text = "A więc masz tylko "+FindRussianQtyString(5-sti(pchar.questTemp.Patria.Hunter))+" Holenderskie statki odpłynęły, by przywieźć towar do naszego portu.";
				link.l1 = "Tak, Chevalier!";
				link.l1.go = "patria_56";
			}
		break;
		
		case "patria_56":
			DialogExit();
			AddQuestRecord("Patria", "35");
			AddQuestUserData("Patria", "sQty", 5-sti(pchar.questTemp.Patria.Hunter));
			DeleteAttribute(pchar, "questTemp.Patria.Hunter.GiveShip");
		break;
		
		// belamour legendary edition -->
		case "patria_57":
			AddMoneyToCharacter(pchar, 200000);
			dialog.text = "I to nie wszystko. Ostatnio trochę myślałem... Charles, naprawdę zrobiłeś wiele dla Francji. Eliminacja, szczerze mówiąc, zdrajcy Levasseura, obrona Saint-Pierre przed zdradzieckim atakiem Hiszpanii, udane pokonanie fortu kolonii San Jose i otrzymanie odszkodowania od Hiszpanów jako kara za ich śmiałą sztuczkę... A potem osobiście towarzyszyłeś przedstawicielowi francuskiej korony, który przybył z Europy, a nawet uratowałeś mu życie, uciekając z zasadzki holenderskiej na wodach Philipsburga!";
			link.l1 = "Monsieur, naprawdę, zawstydzasz mnie... Po prostu wykonuję swój obowiązek.";
			link.l1.go = "patria_57_1";
		break;
		
		case "patria_57_1":
			PlaySound("interface\important_item.wav");
			dialog.text = "Jesteś skromny jak zawsze, mój przyjacielu. A teraz, podczas wykonywania kolejnego zadania zmuszania Holandii do pokoju, znów mnie nie zawiodłeś. Nie boję się tego słowa - bohater narodu! Jako gubernator generalny francuskich kolonii na archipelagu, mam przy sobie kilka egzemplarzy najwyższego odznaczenia Francji i... Ale, przy okazji, proszę cię, abyś przeczytał ten dokument.";
			link.l1 = "Za wybitną służbę na rzecz Francji... w imieniu Jego Królewskiej Mości, króla Francji... przyznaje się oficerowi marynarki w służbie Francji, kapitanowi Charlesowi de Maure, synowi Henriego de Montpe... Chevalier, żartujesz sobie?";
			link.l1.go = "patria_57_2";
		break;
		
		case "patria_57_2":
			dialog.text = "Nie ma za co, mój przyjacielu. Mam zaszczyt wynagrodzić cię, jak na to zasługujesz, wręczając ci najwyższe odznaczenie Francji - Order Świętego Ludwika! Każdy obywatel naszego kraju powinien znać swojego bohatera! I Saint-Pierre jest ci dłużny! Zasługujesz na ten Order, Charles.";
			link.l1 = "Naprawdę, nie wiem, co powiedzieć... Dziękuję, Panie Generale Gubernatorze! Przysięgam nadal służyć Francji z dumą i nie cofać się przed wrogiem!";
			link.l1.go = "patria_57_3";
		break;
		
		case "patria_57_3":
			GiveItem2Character(pchar, "talisman9");
			Log_Info("You've received the Order of Saint Louis! You are the hero of the nation!");
			PlaySound("interface\important_item.wav");
			DoQuestCheckDelay("sea_victory", 0.5);
			dialog.text = "Słowa prawdziwego oficera! Jestem naprawdę dumny z ciebie, Charles. Teraz odpocznij trochę. Zasłużyłeś na to. W międzyczasie zajmę się negocjacjami ze Stuyvesantem - być może zdał sobie już sprawę, że bardziej nieopłacalne jest dla niego być z nami wrogiem niż przyjacielem. Nie opuszczaj miasta, będę cię potrzebował za dwa dni.";
			link.l1 = "Zgoda, Monsieur. Będę czekać na dalsze instrukcje.";
			link.l1.go = "patria_58";
		break;
		// <-- legendary edtion
		case "patria_58":
			DialogExit();
			AddQuestRecord("Patria", "36");
			pchar.questTemp.Patria = "epizode_7_end";
			pchar.quest.Patria_siege_begin.win_condition.l1 = "Timer";
			pchar.quest.Patria_siege_begin.win_condition.l1.date.hour  = 9.00;
			pchar.quest.Patria_siege_begin.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 2);
			pchar.quest.Patria_siege_begin.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
			pchar.quest.Patria_siege_begin.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 2);
			pchar.quest.Patria_siege_begin.win_condition.l2 = "location";
			pchar.quest.Patria_siege_begin.win_condition.l2.location = "Charles_town";
			pchar.quest.Patria_siege_begin.function = "Patria_SiegeBegin";
			bQuestDisableMapEnter = true;//закрыть карту
			pchar.GenQuest.MapClosedNoBattle = true;
			ChangeCharacterNationReputation(pchar, FRANCE, 15);
			ChangeCharacterComplexReputation(pchar, "nobility", 5); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 5);
			ChangeCharacterComplexReputation(pchar, "fame", 5);
		break;
		
		case "patria_59":
			dialog.text = "Tak. Wygląda na to, że Stuyvesant zaczął odpowiadać działaniami wojskowymi w sojuszu z Hiszpanią. Wspólna eskadra holendersko-hiszpańska obległa Saint-Christophe. Strażnice co godzinę raportują mi o każdym z ich ruchów.";
			link.l1 = "Oblężenie?";
			link.l1.go = "patria_60";
		break;
		
		case "patria_60":
			dialog.text = "Oczywiście. Nie zdecydowali się na bezpośredni atak, i to w sumie dobrze. Musimy działać szybko, kapitanie, zanim wróg zdąży zablokować całą wyspę.";
			link.l1 = "Co musimy zrobić?";
			link.l1.go = "patria_61";
		break;
		
		case "patria_61":
			dialog.text = "W Saint-Jones, na Antigui, stacjonuje eskadra angielskiej marynarki wojennej pułkownika Doily. Obecnie odwiedza Sir Jonathana Foxa. Musisz przejść obok wrogich statków i dostać się na Antiguę. Tam spotkasz pułkownika, wręczysz mu mój list i poprosisz go o pomoc.";
			link.l1 = "Czy myślisz, że pułkownik zgodzi się nam pomóc?";
			link.l1.go = "patria_62";
		break;
		
		case "patria_62":
			dialog.text = "Mam nadzieję. List powinien przekonać go, że nagroda za jego pomoc będzie całkiem pokaźna... Również musimy wysłać list do kapitana 'Eclatant', obecnie znajdującego się u wybrzeży Gwadelupy, musi się pospieszyć do Saint-Christopher. Siła ognia 'Eclatant' znacznie pomoże nam w bitwie. Ponieważ nie możesz być w dwóch miejscach jednocześnie, nasza kurierka lugger dołączy do twojej eskadry - musisz ją przeprowadzić bez uszkodzeń przez krąg wrogów, a ona uda się do Gwadelupy, zanim 'Eclatant' wyruszy na południe...";
			link.l1 = "Rozumiem. Przejdź przez oblężenie, eskortuj lugier kurierski i śpiesz się do Saint-Jones do pułkownika Doily'ego z twoim listem.";
			link.l1.go = "patria_63";
		break;
		
		case "patria_63":
			dialog.text = "Dokładnie. Czy jesteś gotów przyjąć kolejny statek do swojej eskadry?";
			if (GetCompanionQuantity(pchar) > 4)
			{
				link.l1 = "Pozbędę się jednego statku i wrócę do ciebie.";
				link.l1.go = "patria_63_1";
			}
			else
			{
				link.l1 = "Tak.";
				link.l1.go = "patria_64";
			}
		break;
		
		case "patria_63_1":
			DialogExit();
			pchar.questTemp.Patria = "epizode_8_wait";
		break;
		
		case "patria_64":
			dialog.text = "Wybornie. Weź list, lugger jest gotowy i czeka na twoje rozkazy.";
			link.l1 = "Nie traćmy czasu, Chevalier!";
			link.l1.go = "patria_65";
		break;
		
		case "patria_65":
			DialogExit();
			AddQuestRecord("Patria", "38");
			pchar.questTemp.Patria = "epizode_8_continue";
			GiveItem2Character(pchar, "Reserve_item_01");
			ChangeItemDescribe("Reserve_item_01", "itmdescr_Reserve_item_01_3");
			Patria_SiegeCreateSquadron();
		break;
		
		case "patria_66":
			dialog.text = "Tak-tak, mój przyjacielu, wiem wszystko o twojej skromności. Jesteś prawdziwym oficerem! I otrzymasz nagrodę, zapewniam cię! Przypuszczam, że po ciężkiej bitwie potrzebujesz wypoczynku? Masz cały tydzień. Przyjdź do mojego pokoju za siedem dni - miasto przygotuje nagrodę dla swojego bohatera.";
			link.l1 = "Tak, Monsieur. Czy mogę iść?";
			link.l1.go = "patria_67";
		break;
		
		case "patria_67":
			dialog.text = "Idź i wypocznij dobrze. Później będziemy musieli zająć się poważnymi sprawami - Jak widzisz, pokój z Holendrami jest w tym momencie niemożliwy. Na razie, pułkownik i ja omówimy kilka ważnych kwestii.";
			link.l1 = "W takim razie spotkamy się za tydzień, Chevalier.";
			link.l1.go = "patria_68";
		break;
		
		case "patria_68":
			DialogExit();
			AddQuestRecord("Patria", "45");
			pchar.questTemp.Patria = "epizode_8_end";
			Patria_SiegeEnd();
			ChangeCharacterNationReputation(pchar, FRANCE, 20);
			ChangeCharacterComplexReputation(pchar, "nobility", 10); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 10);
			ChangeCharacterComplexReputation(pchar, "fame", 10);
		break;
		
		case "patria_69":
			pchar.quest.Patria_BastionTimeOver.over = "yes"; //снять таймер
			dialog.text = "Mieliśmy rozmowę z pułkownikiem Doily i zgodził się mi pomóc. Anglia pomoże nam w wojnie przeciw Holendrom. Ty i ja musimy uderzyć z powrotem i przywrócić sprawiedliwość - wyspa Saint Martin musi wrócić do Francji. Zlecam to zadanie najlepszemu kapitanowi marynarki - tobie, Charles de Maure! Wróg jeszcze nie otrząsnął się z klęski swojej eskadry, zaatakujemy Philipsburg i go zdobędziemy.\nBitwa nie będzie łatwa. Najpierw musimy zniszczyć fort, potem przełamać obronę garnizonu...(szeptem) Będziesz musiał także przeprowadzić forsowny marsz przez dżunglę do złoża soli, o którym ci mówiłem, i zabić tam stacjonujących wrogów...";
			link.l1 = "Zadanie jest dość trudne, Chevalier...";
			link.l1.go = "patria_70";
		break;
		
		case "patria_70":
			dialog.text = "Doskonale cię rozumiem, przyjacielu. Twoja eskadra zostanie wzmocniona. Gubernatorzy Basse-Terre i Saint-Pierre powinni już przygotować po jednym okręcie - fregacie. Będziesz musiał tylko odwiedzić Gwadelupę i Martynikę, aby przejąć te fregaty pod swoje dowództwo. Jeśli, oczywiście, sam ich chcesz - nie będę nalegał na wybór okrętów. Daję ci także dotację w wysokości 20.000 pesos na zakup prowiantu i wyposażenia dla twojego okrętu flagowego. Proszę, weź to...";
			link.l1 = "Bardzo dobrze, monsieur.";
			if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Fail")) link.l1.go = "patria_71";
			else link.l1.go = "patria_71_1";
		break;
		
		case "patria_71_1":
			dialog.text = "Również, jak zwykle, statek 'Eclatant' jest pod twoim dowództwem. Został naprawiony i wyposażony, czeka na redzie, a po rozmowie z kapitanem będziesz mógł go przejąć w dowolnym momencie.";
			link.l1 = "Doskonale!";
			link.l1.go = "patria_71";
			pchar.questTemp.Patria.Ecliaton_Bastion = "true";
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_7";
			sld.DeckDialogNode = "ecliaton_cap_7";
		break;
		
		case "patria_71":
			AddMoneyToCharacter(pchar, 20000);
			dialog.text = "Nie możemy tracić czasu, kapitanie. Jak poinformowali mnie moi szpiedzy, Holendrzy rozumieją zagrożenie dla Saint Martin i zamierzają wzmocnić jego obronę. Ale masz jeszcze dwa miesiące. Musisz wykonać zadanie na czas!";
			link.l1 = "Zrobię to... (szepcząc) Gdzie jest złoże soli na Saint Martin? Nie jest zaznaczone na żadnej mapie wyspy...";
			link.l1.go = "patria_72";
		break;
		
		case "patria_72":
			dialog.text = "„(szeptem) Kiedy zaatakujesz miasto, przesłuchaj wicekróla Philipsburga, Pana Martina Thomasa, on ci powie. Ten Holender to tchórz i nie będzie ci się opierał, gwarantuję to.”";
			link.l1 = "Rozumiem. Czy mogę zatem odejść?";
			link.l1.go = "patria_73";
		break;
		
		case "patria_73":
			dialog.text = "Poczekaj chwilę, Charles. Jeszcze nie otrzymałeś swojej nagrody za ocalenie Saint-Christopher. Weź te skrzynie złota od mieszkańców miasta, a także nasze najszczersze podziękowania, których żadna suma pieniędzy nie wyrazi!";
			link.l1 = "Dziękuję, monsieur!";
			link.l1.go = "patria_74";
		break;
		
		case "patria_74":
			TakeNItems(pchar, "chest", 10);
			Log_Info("You've received 10 chests of doublons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Teraz możesz iść. Powodzenia, kapitanie! Wszyscy czekamy na twoje zwycięstwo!";
			link.l1 = "Żegnaj, Chevalier.";
			link.l1.go = "patria_75";
		break;
		
		case "patria_75":
			DialogExit();
			sTemp = "";
			if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Bastion")) sTemp = "The warship 'Eclatant' will also be under my command.";
			AddQuestRecord("Patria", "48");
			AddQuestUserData("Patria", "sText", sTemp);
			pchar.questTemp.Patria = "epizode_9_continue";
			SetFunctionTimerCondition("Patria_BastionSturmTimeOver", 0, 0, 62, false);
			// вернуть Синт-Маартен в норму
			int n = FindIsland("SentMartin");
			Islands[n].reload.l1.radius = 600.0;
			LocatorReloadEnterDisable("Marigo_ExitTown", "reload3", false); // открыть городские ворота
			sld = CharacterFromID("Marigo Fort Commander");
			LAi_SetImmortal(sld, false);
			Character_SetAbordageEnable(sld, true);
			// атрибут квестовой высадки десанта
			pchar.TempPerks.QuestTroopers = true;
		break;
		
		case "patria_76":
			dialog.text = "Kto by pomyślał zaledwie rok temu, że zostaniesz awansowany do rangi wiceadmirała, mój przyjacielu? Mogę tylko zgadywać, jak dumny będzie twój ojciec, gdy ta wiadomość dotrze do Francji!";
			link.l1 = "Mój drogi ojciec będzie z tego najbardziej uradowany.";
			link.l1.go = "patria_77";
		break;
		
		case "patria_77":
			dialog.text = "Zdobyłeś swoje miejsce we flocie! Saint Martin został zwrócony Francji, Stuyvesant nauczył się surowej lekcji. To było wielkie zwycięstwo! Ale nie możemy się zatrzymać, nie możemy pozwolić Holendrom odpocząć ani na chwilę. Będą pociągnięci do odpowiedzialności za swoją zdradę! Pułkownik Doily jest teraz w Port-Royal, przygotowując swoją eskadrę morską: zamierzamy złamać kręgosłup naszego wroga, uderzając na Curacao. Ale to będzie później, a tymczasem musimy upiec dwie pieczenie na jednym ogniu, Charles.\nKompania nie zdobyła całego swojego niezmierzonego bogactwa na handlu. Główne źródło dochodów Holendrów w regionie to praca niewolnicza na ich plantacjach. Jeśli nie wiesz, Charles: Holandia jest największym narodem posiadającym i handlującym niewolnikami. Wschodnioindyjskie statki regularnie przywożące 'czarne kości słoniowe' przypływają na Curacao z Afryki Zachodniej. I przypadkiem coś o tym wiem, niestety dla Stuyvesanta.\nW tej chwili dwa holenderskie Wschodnioindyjskie statki płyną w kierunku Karaibów z Gwinei. Ich ładownie są pełne czarnych więźniów. Za dziesięć dni lub około tego czasu karawana będzie płynęła wokół wyspy Trynidad w kierunku Curacao. Twoim zadaniem jest odnalezienie karawany i przechwycenie tych dwóch Wschodnioindyjskich statków i ich ładunku. Musisz zniszczyć eskortujące statki i dostarczyć niewolników naszemu sojusznikowi, pułkownikowi Doily, na Jamajce. To bardzo ważne, Charles, w ten sposób zdobędziemy jego zaufanie... Mam nadzieję, że rozumiesz.\nPrzykro mi, że nie zostawiam ci czasu na odpoczynek, ale to zadanie jest ważne i delikatne, i mogę je powierzyć tylko tobie.";
			link.l1 = "Służba to nie słodki cukierek, Chevalier. Wiem to lepiej niż ktokolwiek inny. Przygotuję mój statek i wyruszę, jak tylko będę mógł.";
			link.l1.go = "patria_78";
		break;
		
		case "patria_78":
			dialog.text = "Życzę Ci pomyślnych wiatrów i bezpiecznej podróży, wiceadmirał. A gdy powrócisz do Saint-Christopher, nasz wspólny przyjaciel, monsieur Noel Forget, zakończy inspekcję Philipsburga, a ja dopilnuję, aby część trofeów zdobytych na Holendrach trafiła do Ciebie osobiście.";
			link.l1 = "Będę bardzo wdzięczny, Chevalier. Czy mogę iść?";
			link.l1.go = "patria_79";
		break;
		
		case "patria_79":
			dialog.text = "Idź. Powodzenia, przyjacielu!";
			link.l1 = "... ";
			link.l1.go = "patria_80";
		break;
		
		case "patria_80":
			DialogExit();
			Items[sti(pchar.EquipedPatentId)].TitulCur = 5; 
        	Items[sti(pchar.EquipedPatentId)].TitulCurNext = 0;
			pchar.questTemp.Patria = "epizode_10_start";
			AddQuestRecord("Patria", "52");
			Patria_SlaveShipsStart();
			ChangeCharacterNationReputation(pchar, FRANCE, 15);
			ChangeCharacterComplexReputation(pchar, "nobility", 10); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 10);
			ChangeCharacterComplexReputation(pchar, "fame", 10);
		break;
		
		case "patria_81":
			dialog.text = "Wyśmienicie! Nie znasz słowa 'niemożliwe', Charles. Zwykłem myśleć, że twój brat był najlepszym oficerem marynarki na Karaibach, ale ma się od ciebie wiele nauczyć, jeśli pozwolisz mi na to surowe porównanie. Myślę, że już wiesz, kto uda się do naszego drogiego pułkownika, by wziąć udział w szturmie na Willemstad.";
			link.l1 = "Absolutnie nie, Monsieur! Skądże mogłem wiedzieć!";
			link.l1.go = "patria_82";
		break;
		
		case "patria_82":
			dialog.text = "Ach, twój słynny zmysł humoru, mój drogi przyjacielu! Ha-ha! Oczywiście, to będziesz ty, wiceadmirał. Najbardziej godny ze wszystkich. Jesteś gotowy?";
			link.l1 = "Oczywiście, Chevalier. Potrzebuję tylko trochę napraw, trochę sprzętu - i jestem gotów do drogi.";
			if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Fail")) link.l1.go = "patria_83";
			else link.l1.go = "patria_83_1";
		break;
		
		case "patria_83_1":
			dialog.text = "Nie zapomnij przejąć dowodzenia nad 'Eclatant'. Został naprawiony i wyposażony, czeka na ciebie w doku. Markiz Hubert Dassier już traci cierpliwość i nie może się doczekać, by wyruszyć z tobą do kolejnej bitwy.";
			link.l1 = "Świetnie. Potężny statek z dalekosiężnymi kolubrynami to dokładnie to, czego potrzebuję, by zbombardować fort.";
			link.l1.go = "patria_83";
			pchar.questTemp.Patria.Ecliaton_Curacao = "true";
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_11";
			sld.DeckDialogNode = "ecliaton_cap_11";
		break;
		
		case "patria_83":
			dialog.text = "Poczekaj chwilę, Charles. Nasz przyjaciel, baron Forget, przyniósł dla ciebie wieści z Saint Martin.";
			link.l1 = "...";
			link.l1.go = "patria_84";
		break;
		
		case "patria_84":
			DialogExit();
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_25";
			sld.greeting = "noel_3";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
			ChangeCharacterComplexReputation(pchar, "nobility", 2); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "fame", 2);
		break;
		
		case "patria_85":
			dialog.text = "Mam dla ciebie wieści z Paryża. Twoje mianowanie na stanowisko wiceadmirała zostało podpisane przez Króla. Otrzymasz odpowiednie dokumenty. Gratuluję ci zatem!";
			link.l1 = "Dziękuję, Monsieur! Cieszę się, że mogę służyć Francji i Królowi!";
			link.l1.go = "patria_coat";
		break;
		
		case "patria_coat":
			dialog.text = "I ja, jak zawsze, bardzo się cieszę, słysząc te słowa od ciebie. Charles, może masz ochotę podzielić się ze mną odrobiną wina? Przywiezione prosto z Paryża, takiego tutaj nie znajdziesz przez cały dzień jazdy!";
			link.l1 = "Dziękuję, kawalerze, ale myślę, że odmówię. Muszę później wrócić na statek, a nie przystoi wiceadmirałowi Francji stać pijanym na ćwierćpokładzie.";
			link.l1.go = "patria_coat_01";
			link.l2 = "Cóż, czemu nie? Nie codziennie mam okazję wypić kielich z samym gubernatorem generalnym!";
			link.l2.go = "patria_coat_02";
		break;
		
		case "patria_coat_01":
			dialog.text = "Cóż, mógłbyś zrobić sobie przerwę, nie musisz od razu wracać na statek. Ale to twoja wola, i szanuję ją. Dobrze, przejdźmy od razu do interesów.";
			link.l1 = "Słucham uważnie.";
			link.l1.go = "patria_coat_13";
		break;
		
		case "patria_coat_02":
			dialog.text = "I nie każdy generał-gubernator ma to szczęście, by jego wiceadmirał był nie tylko najlepszym oficerem marynarki, ale także przyjacielem, z którym mógłby zasiąść przy jednym stole i pić wino przywiezione z odległej ojczyzny!";
			link.l1 = "Dla Francji!";
			link.l1.go = "patria_coat_03";
			link.l2 = "Za twoje zdrowie, kawalerze!";
			link.l2.go = "patria_coat_04";
		break;
		
		case "patria_coat_03":
			dialog.text = "I za króla!";
			link.l1 = "... ";
			link.l1.go = "patria_coat_05";
		break;
		
		case "patria_coat_04":
			dialog.text = "I tobie, Charles!";
			link.l1 = "...";
			link.l1.go = "patria_coat_05";
		break;
		
		case "patria_coat_05":
			LAi_Fade("", "");
			if(LAi_GetCharacterHP(pchar) == LAi_GetCharacterMaxHP(pchar))
			pchar.chr_ai.hp = stf(pchar.chr_ai.hp) - 1.0;
			GiveItem2Character(pchar, "potionwine");
			DoCharacterUsedItem(pchar, "potionwine");
			npchar.dialog.currentnode = "patria_coat_06";
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorSetHuberMode(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 1.2);
		break;
		
		case "patria_coat_06":
			dialog.text = "Hm, wyborne wino! Czyż nie sądzisz?";
			link.l1 = "Tak, miałeś rację. Przypomina mi wino, które robią w domu w Gaskonii...";
			link.l1.go = "patria_coat_07";
		break;
		
		case "patria_coat_07":
			dialog.text = "Jesteś trochę w błędzie, przyjacielu - to Bordeaux. Niemniej jednak, jestem pewien, że wino z Gaskonii jest równie dobre!";
			link.l1 = "Myślę, że zaczynam zapominać jego smak... Ile czasu minęło od mojego wyjazdu z Francji? Rok? Dwa?";
			link.l1.go = "patria_coat_08";
		break;
		
		case "patria_coat_08":
			dialog.text = "Ach, Charles, wydaje się, że spotkaliśmy się dopiero niedawno... i to nie w najprzyjemniejszych okolicznościach. Wybacz mi, że o tym wspominam, ale gdyby ktoś wtedy powiedział mi, że w tej celi więziennej przede mną stoi mój przyszły praworęczny człowiek we francuskich koloniach, prawdopodobnie wybuchnąłbym śmiechem.";
			link.l1 = "Nieprzeniknione są ścieżki Pana.";
			link.l1.go = "patria_coat_09";
		break;
		
		case "patria_coat_09":
			dialog.text = "Przepraszam, co pan właśnie powiedział?";
			link.l1 = "To łacina, szewalierze. Ścieżki Pana są niezbadane. Nikt nie wie, co życie ma w zanadrzu.";
			link.l1.go = "patria_coat_10";
		break;
		
		case "patria_coat_10":
			dialog.text = "Nie przestajesz mnie zadziwiać, Charles. Spójrz na siebie - nie miałem pojęcia, że potrafisz również mówić po łacinie. Ale z drugiej strony, w pewnym stopniu sami kształtujemy nasze przeznaczenie, prawda?";
			link.l1 = "Myślę, że oba są prawdziwe. Tylko Pan wie, co nas czeka. Ale nagradza wytrwałych.";
			link.l1.go = "patria_coat_11";
		break;
		
		case "patria_coat_11":
			dialog.text = "Nie mógłbym się bardziej zgodzić. Pamiętam, na przykład, jak wręczałem ci nominację na oficera marynarki i dawałem ci ten mundur. A teraz, przede mną, stoi wiceadmirał, nie mniej!";
			link.l1 = "Czas leci, chevalier.";
			link.l1.go = "patria_coat_12";
		break;
		
		case "patria_coat_12":
			dialog.text = "Indeed... And even on your uniform, I see the cuts left by sabers; some cuts have been stitched, and some are clearly fresh. This needs to be corrected.";
			link.l1 = "Cóż masz na myśli, Panie Gubernatorze-Generale?";
			link.l1.go = "patria_coat_13";
		break;
		
		case "patria_coat_13":
			dialog.text = "Oprócz twojej nowej pozycji wiceadmirała francuskiej floty na archipelagu Karaibów, mam dla ciebie jeszcze jeden prezent.";
			link.l1 = "Sprawiasz, że się rumienię, szewalierze. Jaki prezent?";
			link.l1.go = "patria_coat_14";
		break;
		
		case "patria_coat_14":
			dialog.text = "Umówiłem się z moim osobistym krawcem - najlepszym w francuskich koloniach! - aby uszył mundur odpowiedni dla twojej rangi. Nie martw się o zapłatę, wszystkim się zająłem.";
			link.l1 = "Jestem naprawdę wdzięczny! Na pewno odwiedzę twojego krawca. Gdzie mogę go znaleźć?";
			link.l1.go = "patria_coat_15";
		break;
		
		case "patria_coat_15":
			dialog.text = "Powinien być teraz w biurze portowym - właśnie przybył nowy statek kurierski z lądu z małymi paczkami. Nasz krawiec zawsze zamawia materiały, które tutaj trudno znaleźć.";
			link.l1 = "Zatem udam się do biura portowego. Jeszcze raz dziękuję, monsieur!";
			link.l1.go = "patria_86";
		break;
		
		case "patria_86":
			dialog.text = "A teraz, jestem pewien, że będziesz potrzebował porządnie odpocząć. Daję ci miesiąc, i upewnij się, że dobrze go wykorzystasz. Żadnej pracy, żadnych zmartwień. Przekaż całą pracę swoim oficerom i dobrze odpocznij. Możesz korzystać z pokoi w mojej rezydencji. Służba uczyni twój wypoczynek jak najbardziej komfortowym. Spotkamy się za miesiąc - i będę miał delikatną sprawę do omówienia z tobą.";
			link.l1 = "Bardzo dobrze, Kawalerze. Do widzenia!";
			link.l1.go = "patria_87";
		break;
		
		case "patria_87":
			npchar.dialog.currentnode = "First time";
			LAi_Fade("","");
			LAi_SetHuberType(npchar);
			DialogExit();
			AddQuestRecord("Patria", "65"); // далее коллизия Пуанси-Инспектор-Шарль
			pchar.questTemp.Patria = "epizode_12_start";
			ChangeCharacterNationReputation(pchar, FRANCE, 15);
			SetFunctionLocationCondition("Patria_Tailor", "Charles_PortOffice", false)
			Patria_CondotierStart();
			ChangeCharacterComplexReputation(pchar, "nobility", 15); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 15);
			ChangeCharacterComplexReputation(pchar, "fame", 15);
		break;
		
		case "patria_88":
			dialog.text = "Tak, Charles. Myślałem, że poradzę sobie z tym sam, ale... niestety, muszę ponownie skorzystać z twoich talentów. Ale najpierw muszę ci coś dać: trzysta tysięcy pesos i pięć skrzyń z doublonami. To duża część wkładu, który Stuyvesant mi zapłacił zgodnie z umową. Myślę, że na to wszystko zasłużyłeś, ponieważ wykonałeś większość pracy. Przyjmij to. Czy jesteś zadowolony, mój przyjacielu?";
			link.l1 = "Pieniądze nigdy nikomu nie zaszkodziły, monsieur, dobrze nauczyłem się tej lekcji.";
			link.l1.go = "patria_89";
		break;
		
		case "patria_89":
			AddMoneyToCharacter(pchar, 300000); 
			TakeNItems(pchar, "chest", 5);
			dialog.text = "Ach, wiceadmirał, mam nadzieję, że nie jesteś obrażony tym, co się stało w przeszłości?.. Jesteś teraz bohaterem swojego narodu, wiesz o tym? Jak się czujesz w tej nowej roli? Pamiętaj: wielu godnych oficerów spędziło dekady wspinając się po szczeblach kariery, ale bez doświadczonej ręki... pozostają na stanowisku dowódcy. Ale ty, mój przyjacielu, masz unikalną zdolność do osiągania niemożliwego! I masz przyjaciela na wysokich stanowiskach, który jest także twoim opiekunem, więc jeśli w przyszłości będziesz miał jakieś problemy, będę tam, by ci pomóc.";
			link.l1 = "Dziękuję za te miłe słowa, Wasza Ekscelencjo. Mam wrażenie, że osiągnąłem prawie wszystko w tym regionie. Oczywiście, z waszą pomocą. Myślę, że teraz mogę zająć się swoimi sprawami w spokoju? Muszę pomyśleć o swojej rodzinie.";
			link.l1.go = "patria_90";
		break;
		
		case "patria_90":
			dialog.text = "Chcesz się ożenić, Charles? Ah-ha-ha! Wskaż na jakąkolwiek piękną kobietę w Paryżu - a od razu będzie twoja! Ale, niestety, to będzie musiało poczekać. Potrzebuję cię tutaj, mój przyjacielu, przynajmniej na razie.";
			link.l1 = "Wydaje się, że Francja jest silniejsza niż kiedykolwiek w Archipelagu. Sojusz z Anglikami, rozejm z Kompanią. Nie ma już problematycznych... 'Levasseurów'. Prawda?";
			link.l1.go = "patria_91";
		break;
		
		case "patria_91":
			dialog.text = "Narody, podobnie jak ludzie, zawsze pragną więcej, bez względu na to, ile już mają... A my rzeczywiście mamy nowego 'Levasseura', wiceadmirała...";
			link.l1 = "Naprawdę? A kto to?";
			link.l1.go = "patria_92";
		break;
		
		case "patria_92":
			dialog.text = "To nasz stary wspólny znajomy, baron Noel Forget. Pamiętasz, dlaczego tu przybył?";
			link.l1 = "Hmm... Wspomniałeś coś o Kompanii Handlowej Indii Zachodnich. Paryż zdecydował się stworzyć taką samą organizację jak Holendrzy?";
			link.l1.go = "patria_93";
		break;
		
		case "patria_93":
			dialog.text = "Dokładnie. Analogicznie do Kompanii Niderlandzkiej. Ale stworzyć ją od zera jest bardzo trudno. Widzisz, Stuyvesant miał dekady handlu z różnymi kontynentami w swoim doświadczeniu, rozwiniętą sieć agentów i potężną flotę statków handlowych. Francja tego nie ma, a jeśli nie wiedziałeś, Karolu, król obecnie przeżywa poważny brak funduszy. Pragną naprawić sytuację finansową metropolii, kierując tu handel, ale nie rozumieją, z czym będziemy musieli się zmierzyć.\nRywalizacja zarówno z Anglikami, jak i Holendrami, terytorialne ambicje Hiszpanów, piractwo rozwijające się jak nigdy wcześniej. Każda jednostka handlowa musi być eskortowana przez okręt wojenny, inaczej będzie narażona na ryzyko nigdy nie dotarcia do celu. I nie mamy potężnej floty jak Wschodnioindyjska Kompania Holenderska, ani potężnych Galeonów jak te hiszpańskie.";
			link.l1 = "  Ale czy wyjaśniłeś to wszystko baronowi?  O piratach też? ";
			link.l1.go = "patria_94";
		break;
		
		case "patria_94":
			dialog.text = "Oczywiście, że zrobiłem. I o wygnaniu piratów z Tortugi po twojej misji usunięcia Levasseura, czego piraci nie zapomnieli i zawsze będą nam to mieć za złe. Zorganizowałem spotkania z różnymi osobami, które potwierdziły moje obawy, ale niestety, to nie miało wpływu na barona. Został tu wysłany przez ministrów i jest im coś winien... Tak to już jest.";
			link.l1 = "Pff...";
			link.l1.go = "patria_95";
		break;
		
		case "patria_95":
			dialog.text = "A nie ukrywajmy faktu, że kompania handlowa na Archipelagu, pod bezpośrednią kontrolą z Paryża... ty i ja, wiceadmirał... nie potrzebujemy jej tutaj.";
			link.l1 = "Rozumiem.";
			link.l1.go = "patria_96";
		break;
		
		case "patria_96":
			dialog.text = "Widzisz, przyjacielu, jestem z tobą niezwykle szczery... Tak więc, miałem nadzieję z całego serca, że Monsieur Forget zmieni zdanie co do utworzenia tej kompanii handlowej, ale... to się nie stało. Wyczerpałem cały mój wpływ na barona, a teraz ty musisz wejść do gry.";
			link.l1 = "Hmm... Tak jak z Levasseur?";
			link.l1.go = "patria_97";
		break;
		
		case "patria_97":
			dialog.text = "O Boże nie, za kogo mnie masz, Charles?! Baron to wpływowa postać, przyjaciel Ministra Finansów! I poza tym, fizyczne usunięcie go niczego nie osiągnie: po prostu wyślą nowego polityka z Paryża. Musimy zniszczyć samą ideę zorganizowania takiej kompanii, rozumiesz, Charles? Aby baron wrócił do Francji i zameldował, że to byłoby finansowo ryzykowne, bezsensowne...";
			link.l1 = "Masz jakiś pomysł, monsieur?";
			link.l1.go = "patria_98";
		break;
		
		case "patria_98":
			dialog.text = "Niestety, nie, Charles. Próbowałem wszystkiego. Straszyłem go brakiem statków i pieniędzy, Holendrami, piratami... Bez efektu.";
			link.l1 = "Wydaje się, że potrzebujemy czegoś poważniejszego niż tylko słowa. Hm... Piraci, mówisz?";
			link.l1.go = "patria_99";
		break;
		
		case "patria_99":
			dialog.text = "Widzę, że masz jakiś pomysł, przyjacielu? Nie miałem wątpliwości. Masz genialny umysł. Przekonaj tego barona, a ja upewnię się, że twój ojciec będzie miał wystarczająco pieniędzy, by napełnić cały twój dom bogactwami godnymi Luwru. Obiecuję ci to, Charles.";
			link.l1 = "Bardzo dobrze, Chevalier. Zadanie jest jasne.";
			link.l1.go = "patria_100";
		break;
		
		case "patria_100":
			dialog.text = "Przysięgam, Charles, nie pożałujesz, jeśli ci się uda. Możesz być tego pewien. Czy kiedykolwiek cię zdradziłem, przyjacielu?";
			link.l1 = "Absolutnie nie, monsieur. Gdzie mogę znaleźć barona?";
			link.l1.go = "patria_101";
		break;
		
		case "patria_101":
			dialog.text = "Obecnie jest w Port-au-Prince. Powiedział, że niekończące się pola i doliny Hispanioli są bardzo urocze...";
			link.l1 = "Świetnie. Teraz pozwól mi się pożegnać.";
			link.l1.go = "patria_102";
		break;
		
		case "patria_102":
			DialogExit();
			AddQuestRecord("Patria", "67");
			pchar.questTemp.Patria = "epizode_12_pirates";
			Patria_CondotierSail();
		break;
		
		case "patria_103":
			dialog.text = "Dokładnie tak. Baron powiedział mi wszystko. Po tym, co przeszedł... Jednakże, potrafisz wyjaśnić rzeczy jasno, jak nikt inny, wiceadmirał! Powinienem się tego od Ciebie nauczyć!";
			link.l1 = "Wiele się od ciebie nauczyłem, Chevalier.";
			link.l1.go = "patria_104";
		break;
		
		case "patria_104":
			dialog.text = "Mój przyjacielu, jestem ci dłużny. Zapewniam cię, że twój drogi ojciec będzie miał wszystko, czego potrzebuje lub kiedykolwiek będzie potrzebował w swoim życiu, a wasz rodzinny dom będzie najlepszy w prowincji... a także jednym z najlepszych we Francji. Poza tym, zapłacę ci 100 000 pesos - mam nadzieję, że to pokryje twój dług u piratów...";
			link.l1 = "To miło słyszeć, Monsieur!";
			link.l1.go = "patria_105add";
		break;
		
		case "patria_105add":
			AddMoneyToCharacter(pchar, 100000); 
			dialog.text = "Przygotowałem także specjalny prezent dla ciebie. Jestem pewien, że zrozumiesz wartość tego przedmiotu i szczerość mojej wdzięczności za twoją lojalną służbę! Więc, Wiceadmirał Charles de Maure, ofiaruję ci mój osobisty ceremonialny miecz Zakonu Maltańskiego! Ta cenna broń będzie pasować do twojego munduru, jak sądzę! Jeśli zdecydujesz się wrócić do Paryża, baron Noel Forget obiecał przedstawić cię królowi - powinieneś przyjść do niego w pełnej paradzie: w mundurze i z tą znakomitą klingą! Czekają cię jeszcze bardziej chwalebne możliwości kariery w marynarce francuskiej!";
			link.l1 = "Ten miecz nie ma sobie równych w swej piękności! Dziękuję, Monsieur, naprawdę nie zasługuję na ten zaszczyt...";
			link.l1.go = "patria_105";
		break;
		
		case "patria_105":
			ref itm = ItemsFromID("blade_36");
			itm.picIndex = 16;
			itm.picTexture = "ITEMS_17";
			itm.price = 10000;
			itm.Weight = 3.0;
			itm.lenght = 1.05;
			itm.curve = 1.0;
			itm.Balance = 1.9;
			GiveItem2Character(pchar, "blade_36");
			Log_Info("You've received the Maltese Sword");
			PlaySound("interface\important_item.wav");
			dialog.text = "Robisz! A podczas gdy jesteś tu, czekają cię wielkie zmiany. Dobre zmiany. Wiceadmirał Charles de Maure, mianuję cię gubernatorem Saint Martin!";
			link.l1 = "Hah! Czy dobrze usłyszałem?";
			link.l1.go = "patria_106";
		break;
		
		case "patria_106":
			ChangeCharacterComplexReputation(pchar, "nobility", 12); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 12);
			ChangeCharacterComplexReputation(pchar, "fame", 12);
			dialog.text = "Tak, mój przyjacielu. Teraz jesteś gubernatorem Saint Martin, które tak pilnie chroniłeś.";
			link.l1 = "Chevalier, pozwól mi odmówić tego zaszczytu. Nie chcę być związany z tą jedną biedną wyspą! A te wszystkie domowe sprawy... To nie jest to, do czego zostałem stworzony!";
			link.l1.go = "patria_107";
		break;
		
		case "patria_107":
			dialog.text = "Nie przyjmuję odmowy. Mój przyjacielu, nie obawiaj się: będziesz żyć jak wcześniej. Wszystkie nudne sprawy załatwi obecny pełniący obowiązki gubernatora. Ty będziesz de facto gubernatorem. Charles, czy nie rozumiesz, dlaczego to właśnie ciebie mianowano na zarządcę Saint Martin? Teraz jest właściwy moment, gdy nikt nie będzie zadawał pytań. Potrzebuję tam jednego z MOICH ludzi jako gubernatora, rozumiesz, co mam na myśli?";
			link.l1 = "Kopalnia soli?";
			link.l1.go = "patria_108";
		break;
		
		case "patria_108":
			dialog.text = "Oczywiście! A druga dobra wiadomość: od teraz, 15-go dnia każdego miesiąca, będziesz otrzymywał część zysków z kopalni, jak również z handlu Doily'ego. Twój pasywny dochód wyniesie 100.000 pesos miesięcznie.";
			link.l1 = "Hah! Cieszę się, że to słyszę! Dziękuję, Chevalier. Cóż, jeśli nie będę musiał tam siedzieć na stałe, przyjmuję stanowisko gubernatora. A co, jeśli zdecyduję się popłynąć do Francji?";
			link.l1.go = "patria_109";
		break;
		
		case "patria_109":
			dialog.text = "Kiedy zdecydujesz – odejdziesz, a ja, choć bardzo rozczarowany, znajdę ci zastępstwo. Ale to nie wszystko. Mam tu list od twego ojca. Spójrz.";
			link.l1 = "Od mego ojca? Jestem zachwycony!.. Bardzo dobrze, Monsieur, umowa stoi. Czy mogę już iść? Chciałbym przeczytać list... Żadnych nowych zadań dla mnie?";
			link.l1.go = "patria_110";
		break;
		
		case "patria_110":
			dialog.text = "Nie teraz, Gubernatorze, ale jeśli znajdę jakieś zajęcie, wiem, jak Cię znaleźć. Powodzenia, Charles!";
			link.l1 = "I dla ciebie, Chevalier!";
			if (pchar.questTemp.Patria == "epizode_12_baronwin") link.l1.go = "patria_119";
			else link.l1.go = "patria_111";
		break;
		
		case "patria_111":
			DialogExit();
			AddQuestRecord("Patria", "77");
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			pchar.questTemp.Patria = "end"; // конец линейки
			pchar.questTemp.Patria.Governor = "true"; // Шарль губернатор
			AddQuestRecordInfo("Sharlie_Father_1", "1");
			sld = CharacterFromID(pchar.questTemp.Patria.SpanishID);
			SetCharacterRemovable(sld, true);
		break;
		
		case "patria_112":
			dialog.text = "Na Boga, co za katastrofa! Teraz mamy więcej problemów do rozwiązania. Czy to twoja wina, Charles? Powiedz mi prawdę. Czy to był wypadek?";
			link.l1 = "Cóż, coś poszło nie tak...";
			link.l1.go = "patria_113";
		break;
		
		case "patria_x112":
			dialog.text = "Niech to szlag, co za katastrofa! Teraz mamy więcej problemów do rozwiązania. Baron wybrał bardzo złe miejsce na śmierć! Jesteś pewien, że nie pomogłeś mu odejść z tego świata?";
			link.l1 = "Co Ty mówisz, Chevalierze?! Oczywiście, że nie!";
			link.l1.go = "patria_x113";
		break;
		
		case "patria_y112":
			dialog.text = "Cholera jasna, co za katastrofa! Teraz mamy więcej problemów do rozwiązania. Czy jesteś pewien, że nie pomogłeś mu odejść z tego świata?";
			link.l1 = "Co Ty mówisz, Kawalerze?! Oczywiście, że nie!";
			link.l1.go = "patria_y113";
		break;
		
		case "patria_x113":
			dialog.text = "Dobrze. Cóż, mój przyjacielu, może nie wszystko jest stracone. Gorączka to gorączka, prawda? A dopóki nie przybędzie nowy inspektor z ministerstwa, posprzątamy tutaj bałagan i będziemy czekać na naszych gości dobrze uzbrojeni... A teraz, Charles, musimy zamknąć wszystkie nasze kontakty. Mam nadzieję, że rozumiesz dlaczego?";
			link.l1 = "Oczywiście.";
			link.l1.go = "patria_114";
		break;
		
		case "patria_y113":
			dialog.text = "Dobrze. Cóż, przyjacielu, może nie wszystko jest stracone. Bitwy na Karaibach są do przewidzenia, prawda? A dopóki nowy inspektor z ministerstwa nie przybędzie, posprzątamy tutaj bałagan i będziemy czekać na naszych gości dobrze uzbrojeni... A teraz, Charles, musimy zamknąć wszystkie nasze kontakty. Mam nadzieję, że rozumiesz dlaczego?";
			link.l1 = "Oczywiście.";
			link.l1.go = "patria_114";
		break;
		
		case "patria_113":
			dialog.text = "Zgoda. No cóż, mój przyjacielu, może nie wszystko jest stracone. Piraci to piraci, prawda? A dopóki nie przybędzie nowy inspektor z ministerstwa, posprzątamy tu bałagan i będziemy czekać na naszych gości dobrze uzbrojeni... A teraz, Charles, musimy zakończyć wszystkie nasze kontakty. Mam nadzieję, że rozumiesz dlaczego?";
			link.l1 = "Oczywiście.";
			link.l1.go = "patria_114";
		break;
		
		case "patria_114":
			dialog.text = "W każdym razie, mój przyjacielu, zrobiłeś wszystko, co mogłeś. A to lepsze niż nic. Cieszę się, że los nas połączył. Możesz zachować swoją pozycję, a jestem pewien, że czeka cię wielka kariera we Francji. I myślę, że nadszedł czas, byś wrócił do Paryża. Oto list od twojego ojca. Weź go.";
			link.l1 = "Mój ojciec? Toż to bardzo mile widziane!.. Dobrze, Monsieur, rozumiem. Żadnych kontaktów, pełna tajemnica, i jak najszybciej do Paryża. Mogę już iść? Chciałbym przeczytać list...";
			link.l1.go = "patria_115";
		break;
		
		case "patria_115":
			dialog.text = "Idź, Charles. Powodzenia!";
			link.l1 = "I tobie, szlachetny kawalerze!";
			link.l1.go = "patria_116";
		break;
		
		case "patria_116":
			DialogExit();
			AddQuestRecord("Patria", "78");
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			pchar.questTemp.Patria = "end"; // конец линейки
			AddQuestRecordInfo("Sharlie_Father_1", "1");
			sld = CharacterFromID(pchar.questTemp.Patria.SpanishID);
			SetCharacterRemovable(sld, true);
		break;
		
		case "patria_117":
			dialog.text = "Dokładnie. Potrafisz wyjaśniać rzeczy jaśniej niż ktokolwiek inny, wiceadmirał! Powinienem się tego od ciebie nauczyć!!";
			link.l1 = "Dużo się od ciebie nauczyłem, Chevalier.";
			link.l1.go = "patria_118";
		break;
		
		case "patria_118":
			dialog.text = "Mój przyjacielu, jestem ci winien. Zapewniam cię, że twój drogi ojciec będzie miał wszystko, czego potrzebuje lub kiedykolwiek będzie potrzebował w swoim życiu, a wasz rodzinny dom będzie najlepszy w prowincji... i jednym z najlepszych we Francji. Oprócz tego zapłacę ci 100.000 pesos - mam nadzieję, że pokryje to twoje koszty podróży i pozwoli ci na zasłużony odpoczynek.";
			link.l1 = "To wspaniale słyszeć, monsieur!";
			link.l1.go = "patria_105add";
		break;
		
		case "patria_119":
			DialogExit();
			AddQuestRecord("Patria", "87");
			pchar.questTemp.Patria = "europe";
			pchar.questTemp.Patria.Governor = "true"; // Шарль губернатор
			AddQuestRecordInfo("Sharlie_Father_1", "1");
			SetFunctionTimerCondition("Patria_EuropeTime", 0, 0, 175+rand(10), false); // таймер
		break;
		
		case "patria_prison":
			dialog.text = "Jak mogłeś, Charles! Jak mogłeś mi to zrobić?!";
			link.l1 = "Ehem...";
			link.l1.go = "patria_prison_1";
		break;
		
		case "patria_prison_1":
			dialog.text = "Wiem, że to byłeś ty! To ty to zrobiłeś! Nie zaprzeczaj! Bez twojej pomocy baron Forget nigdy nie dostałby ani raportów od zarządcy kopalni, ani lokalizacji kopalni, ani nawet dokumentów Petera Stuyvesanta. Twoje imię tam nie padło, ale pozwól, że ci powiem, wiem na pewno: to byłeś ty. Dlaczego, Charles?.. Po prostu mi odpowiedz... Dlaczego? Michel? Milion pesos? Levasseur? A może stanowisko gubernatora generalnego?";
			// belamour legendary edition -->
			link.l1 = "Czy pamiętasz nasze pierwsze spotkanie, Chevalier? Jak postawiłeś mnie na miejscu? Jak wymusiłeś na mnie milion peso? Chciałem tylko, żebyśmy pewnego dnia zamienili się miejscami. Nie mam ci nic więcej do powiedzenia.";
			link.l1.go = "patria_prison_2";
			link.l2 = "Za Levasseura. Dług miliona, to jeszcze mogę zrozumieć. Pracowałem, zabijałem, zarabiałem, rabowałem, ale wynagrodziłem ci wszystkie szkody. A to ci nie wystarczyło. Ty, Chevalier, wysłałeś mnie na samobójczą misję przeciwko koronie, abyś mógł dalej wzmacniać swoją osobistą władzę! Twoja zdrada domagała się odpowiedzi. I ją otrzymałeś!";
			link.l2.go = "patria_prison_2";
			link.l3 = "Ambicja, Chevalier. W tym dziwacznym nowym świecie osiągnąłem już prawie wszystko, co mogłem. Stanowisko gubernatora generalnego wydawało mi się godnym celem. Wiele się od ciebie nauczyłem. Do widzenia!";
			link.l3.go = "patria_prison_2";
			link.l4 = "Sam nie wiem, szczerze mówiąc. Może dlatego, że jestem pod wrażeniem barona i jego wiernej służby dla naszego kraju? W każdym razie, teraz będziesz miał dość czasu, aby zastanowić się nad tym zagadnieniem za mnie. Żegnaj!";
			link.l4.go = "patria_prison_2";
			// <-- legendary edition
		break;
		
		case "patria_prison_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload = true;//закрыть переход
			LAi_SetActorType(npchar);
			SetFunctionTimerCondition("Patria_EuropePuancieClear", 0, 0, 5, false); // таймер
			pchar.quest.Patria_Europe_final.win_condition.l1 = "location";
			pchar.quest.Patria_Europe_final.win_condition.l1.location = "Charles_town";
			pchar.quest.Patria_Europe_final.function = "Patria_EuropeFinal";
		break;
		
		case "patria_patentfail":
			DialogExit();
			pchar.questTemp.Patria = "fail";
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			// убрать Эклятон, если есть
			if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton"))
			{
				sld = characterFromId("Ecliaton_Cap");
				RemoveCharacterCompanion(pchar, sld);
				sld.lifeday = 0;
				DeleteAttribute(pchar, "questTemp.Patria.Ecliaton");
			}
		break;
		
		// Rebbebion, квест "Путеводная звезда"
		case "PZ1":
			SetTimerCondition("PZ_NormanBackToStreets", 0, 0, 1, false);	//Вовзращаем Акулу или Тиракса в Шарптаун
			// ставим сразу прерывание, чтобы потом по тысячу раз не копировать
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				if (CheckAttribute(pchar, "questTemp.PZ.LongwayMayfang") || CheckAttribute(pchar, "questTemp.PZ.LongwayTorero") || CheckAttribute(pchar, "questTemp.PZ.LongwayElCasador"))
				{
					PChar.quest.PZ_AfterPoincyLongwayDialog.win_condition.l1 = "location";
					PChar.quest.PZ_AfterPoincyLongwayDialog.win_condition.l1.location = "Charles_town";
					PChar.quest.PZ_AfterPoincyLongwayDialog.win_condition = "PZ_AfterPoincyLongwayDialog";
				}
			}
			
			if (!CheckAttribute(pchar, "questTemp.PZ_ChangShinMertva")) 
			{
				dialog.text = "Dobrze cię widzieć, Charles. Słyszałem o twoich wyczynach. Znakomita robota!";
				if (CheckAttribute(pchar, "questTemp.PZ_LevasserPlenen"))
				{
					link.l1 = "To nie wszystko, Wasza Ekscelencjo.";
					link.l1.go = "PZ2";
				}
				else
				{
					link.l1 = "Czy mogę otrzymać od ciebie pisemny rozkaz, by mój brat został teraz zwolniony z aresztu?";
					link.l1.go = "serve";
				}
			}
			else 
			{
				dialog.text = "Greetings, Charles. Come in; I've already been informed.";
				link.l1 = "Zawiadomiony? Może to jakaś pomyłka, Wasza Ekscelencjo. Przyszedłem zgłosić pomyślne zakończenie waszej misji, ale widzę, że nie jesteście w najlepszym nastroju.";
				link.l1.go = "PZ_PoincyAngry1";
			}
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.PZ_LongwayNelzyaOtdatArube");
		break;
					
		case "PZ2":
			dialog.text = "Czyżby? Co masz na myśli, kapitanie?";
			link.l1 = "Udało mi się schwytać Levasseura żywcem i przyprowadzić go do ciebie. Jak tylko skończymy, rozkażę ci go przyprowadzić.";
			link.l1.go = "PZ3";
		break;
		
		case "PZ3":
			dialog.text = "Nie sądziłem, że coś takiego jest w ogóle możliwe! Naprawdę, świetna robota, Charles! Wątpię, czy nawet twój znakomity brat mógłby zrobić to lepiej. Twój ojciec byłby z ciebie dumny, mój przyjacielu.";
			link.l1 = "Dziękuję za miłe słowa, Monsieur Philippe.";
			link.l1.go = "exit";
			npchar.greeting = "";
			AddDialogExitQuest("PZ_LevasserVGostyahUPuansie");
		break;
		
		case "PZ5":
			dialog.text = "Bardzo dobrze, Charles. Jestem z ciebie zadowolony.";
			link.l1 = "Czy mogę otrzymać od Ciebie pisemny rozkaz o natychmiastowym uwolnieniu mojego brata z aresztu?";
			link.l1.go = "serve";
			LAi_SetHuberType(npchar);
		break;
		
		case "PZ_PoincyAngry1":
			dialog.text = "„Może powinienem był wziąć pod uwagę, że nie jesteś swoim bratem - nie jesteś wojskowym, ani tajnym agentem, i nie masz jeszcze doświadczenia w delikatnych operacjach. Nie powinieneś był walczyć z żołnierzami otwarcie na ulicach Tortugi. Będą dochodzenia, i dotyczące mnie również. Od poważnych ludzi, jak rozumiesz.”";
			link.l1 = "Proszę o wybaczenie, Chevalier. Jak zapewne rozumiesz, Levasseur nie ustąpiłby bez walki.";
			link.l1.go = "PZ_PoincyAngry2";
		break;
		
		case "PZ_PoincyAngry2":
			dialog.text = "Prawda, ale... nieważne. Nieźle jak na pierwszą operację. Zgłoszę, że zaatakował Królewskiego Audytora i jego eskortę podczas oficjalnej inspekcji.";
			if (CheckAttribute(pchar, "questTemp.PZ_LevasserPlenen"))
			{
				link.l1 = "Wasza Ekscelencjo, jeśli to pomoże, mogę przyprowadzić Levasseura do Ciebie. Moi ludzie i ja mieliśmy szczęście pojmać go w ustronnym miejscu po tym, jak jego siepacze próbowali nas aresztować na ulicach.";
				link.l1.go = "PZ_PoincyAngry3";
			}
			else
			{
				link.l1 = "Czy mogę otrzymać od ciebie pisemny rozkaz, aby mój brat został teraz zwolniony z aresztu?";
				link.l1.go = "serve";
			}
		break;
				
		case "PZ_PoincyAngry3":
			dialog.text = "Co powiedziałeś, Charles? Powiedz to jeszcze raz.";
			link.l1 = "François Levasseur jest teraz w mojej ładowni, gotowy do przekazania wam, monsieur Philippe.";
			link.l1.go = "PZ_PoincyAngry4";
		break;
		
		case "PZ_PoincyAngry4":
			dialog.text = "Zapomnij o wszystkim, co powiedziałem wcześniej. Zdecydowanie przesadziłem. Znakomita robota. Nie jestem pewien, czy nawet twój znakomity brat mógłby tego dokonać.";
			link.l1 = "Dziękuję, Chevalier.";
			link.l1.go = "PZ_PoincyAngry5";
		break;
		
		case "PZ_PoincyAngry5":
			dialog.text = "Masz wielki potencjał, mój przyjacielu. Życzyłbym sobie, aby twoje talenty były częściej wykorzystywane dla dobra kraju. Ale proszę, postaraj się być bardziej... dyskretny od teraz. Nasza praca zazwyczaj wymaga delikatnego podejścia. Och tak, i jeszcze jedna rzecz.";
			link.l1 = "Tak, Wasza Lordowska Mość?";
			link.l1.go = "exit";
			npchar.greeting = "";
			AddDialogExitQuest("PZ_LevasserVGostyahUPuansie");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

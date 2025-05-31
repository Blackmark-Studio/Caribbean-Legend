// Элен МакАртур - сомнительная любовь и офицер
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	string 	sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Co to jest?";
			link.l1 = "Nie, to nic.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "After_boarding":
			dialog.text = "Dziękuję za pomoc, kapitanie!";
			link.l1 = "Boże mój... Jesteś jeszcze piękniejsza, niż sobie wyobrażałem!";
			link.l1.go = "After_boarding_1";
		break;
		
		case "After_boarding_1":
			dialog.text = "Do diabła z moją urodą! Wiesz, ile żalu mi przyniosła? Odciąłabym sobie nos, gdyby to nie zniszczyło mojej reputacji. Ten drań nie pozwoliłby mi opuścić korwety żywą, ciągle powtarzał, że 'wiem za dużo.' Wczoraj powiedział mi, że ma dość czekania i zamierza mnie wziąć wbrew mojej woli. Nie mogłeś przybyć w lepszym momencie! Ale gdzie moje maniery, nazywam się Helen McArthur. Mój tata nazywał mnie Rumba, bo ciągle przypadkowo tłukłam delikatną porcelanę, którą 'nabył', więc teraz tak nazywa mnie moja załoga.";
			link.l1 = " Nazywam się "+GetFullName(pchar)+" i jestem tu, by cię uratować. Przeszukiwałem Karaiby przez kilka dni, szukając cię dla pani Gladys.";
			link.l1.go = "After_boarding_2";
		break;
		
		case "After_boarding_2":
			dialog.text = "Pani Gladys!? Jak się ma?";
			link.l1 = "Umierałem z niepokoju o ciebie. Ale wkrótce ją zobaczysz, płyniemy do Blueweld. Możesz mi opowiedzieć o wszystkim, co ci się przydarzyło w drodze.";
			link.l1.go = "After_boarding_3";
		break;
		
		case "After_boarding_3":
			dialog.text = "Jeśli mam być szczera, "+pchar.name+", chciałabym teraz zjeść coś i się zdrzemnąć. Jestem wyczerpana po tych wszystkich dniach spędzonych na statku tego potwora...";
			link.l1 = "Oczywiście, pani McArthur. Rozkażę stewardowi, aby podał ci posiłek i przygotował łóżko w twych prywatnych kwaterach.";
			link.l1.go = "After_boarding_4";
		break;
		
		case "After_boarding_4":
			DialogExit();
			LAi_SetActorType(npchar);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			npchar.greeting = "helena_2";
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			pchar.questTemp.Saga = "returntoblueveld";
			Island_SetReloadEnableGlobal("Antigua", true);//на остров можно
			bQuestDisableMapEnter = false;//открыть карту
			AddQuestRecord("Saga", "11");
			pchar.quest.Saga_returnBlueveld.win_condition.l1 = "location";
			pchar.quest.Saga_returnBlueveld.win_condition.l1.location = "Santacatalina_town";
			pchar.quest.Saga_returnBlueveld.function = "Saga_returnBlueveld";
			SetFunctionTimerCondition("Helena_ReturnOver", 0, 0, 45, false);
			sld = characterFromId("gladis");
			sld.greeting = "gladis_3";
		break;
		
		case "Return_blueveld":
			pchar.quest.Helena_ReturnOver.over = "yes";
			dialog.text = "Kapitánie de Maure, jeszcze raz dziękuję Ci z głębi serca za Twoje szybkie ratunek. Musisz odwiedzić mnie i moją matkę. Nasz dom nie jest daleko stąd, po lewej stronie, gdy idziesz z przystani. I wiedz o tym "+pchar.name+", Nigdy ci nie wybaczę, jeśli odpłyniesz bez pożegnania!";
			link.l1 = "Cała przyjemność po mojej stronie, pani McArthur. Na pewno się do pani zgłoszę!";
			link.l1.go = "Return_blueveld_1";
		break;
		
		case "Return_blueveld_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "houseSp3", "SantaCatalina_houseSp3_bedroom", "goto", "goto1", "OpenTheDoors", -1);
			AddQuestRecord("Saga", "13");
			LocatorReloadEnterDisable("SantaCatalina_houseS1", "reload2", false); // открыть кабинет Свенсона
			pchar.questTemp.Saga = "svenson";//идем к Свенсону
			sld = characterFromId("JS_girl");
			sld.dialog.currentnode = "js_girl";
			npchar.dialog.currentnode = "Helena_wait";
			sld = characterFromId("Gladis");
			sld.dialog.currentnode = "Gladis_regard";
			LocatorReloadEnterDisable("SantaCatalina_houseSp3", "reload2", true);//закрыть спальню Элен
			// закрыть город до беседы с Глэдис
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", true);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", true);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", true);
		break;
		
		case "Helena_wait":
			dialog.text = "Ah, oto jesteś, Kapitanie de Maure! Cieszę się, że jesteś tutaj, mam do ciebie wiele pytań.";
			link.l1 = "Przepraszam, pani McArthur, ale musimy nieco opóźnić naszą rozmowę. Muszę zdobyć więcej informacji, zanim będę mógł udzielić satysfakcjonujących odpowiedzi. Na razie proszę cię, abyś nie pokazywała się na ulicy. Mam nadzieję, że twoje oczekiwanie nie potrwa długo. Zaufaj mi i czekaj.";
			
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.CanDrink")) {
				link.l1.go = "drinking_refuse";
				link.l2 = "Sam powiedziałeś, że nie wybaczyłbyś mi, gdybym nie wpadła.";
				link.l2.go = "drinking_accept";
				
				DeleteQuestCondition("HelenDrinking_NoVisit");
				DeleteAttribute(pchar, "questTemp.HelenDrinking.CanDrink");
			} else {
				link.l1.go = "exit";
				NextDiag.TempNode = "Helena_wait";
			}
		break;
		
		case "Helena_hire":
			dialog.text = "Ach, oto jesteś, mój kapitanie! Twoje oczy mówią mi, że masz dla mnie wieści!";
			link.l1 = "Kapitan Svenson powiedział mi, że chcesz ze mną popłynąć. Doceniam twoje pragnienie, a także panna Gladys wspomniała, że tęsknisz za morzem. Witamy na pokładzie, panno Helen McArthur!";
			link.l1.go = "Helena_hire_1";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_friend"))
			{
				link.l2 = "Kapitan Svenson powiedział mi, że chcesz żeglować ze mną. Doceniam twoje pragnienie, a pani Gladys wspomniała, że tęskniłaś za morzem. Witaj w mojej załodze, pani Helen Sharp!";
				link.l2.go = "Helena_hire_2";
				pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 2;
			}
		break;
		
		case "Helena_hire_1":
			DeleteAttribute(pchar, "questTemp.Saga.Helena_friend");
			dialog.text = "Tak jest, kapitanie! Nienawidzę tego mówić, panie, ale potrafię się bronić i nie będę tolerować, gdy mężczyźni pozwalają sobie na zbyt wiele. Nie ponoszę odpowiedzialności za żadne odcięte ręce czy wydłubane oczy.";
			link.l1 = "Nie martw się, na moim statku panuje niezachwiana dyscyplina. Muszę cię jednak o coś zapytać...";
			link.l1.go = "Helena_hire_1_1";
		break;
		
		case "Helena_hire_1_1":
			dialog.text = "...Tak?";
			link.l1 = "Jan Svenson i ja dowiedzieliśmy się, że jesteś prawowitą dziedziczką Isla Tesoro. Tak, to prawda, nie kręć głową! Mam połowę mapy, która dowodzi twoich praw. To nie będzie łatwe, ale Jan i ja zrobimy wszystko, co w naszej mocy, aby pomóc ci zostać prawowitą właścicielką.";
			link.l1.go = "Helena_hire_1_2";
		break;
		
		case "Helena_hire_1_2":
			dialog.text = ""+pchar.name+", czy ty poważnie? To niegrzecznie drażnić biedną dziewczynę w ten sposób! Jakże mogłabym mieć prawo własności do całej wyspy?!";
			link.l1 = "Jestem całkowicie poważny, pani McArthur. I zamierzam pomóc ci odzyskać twoje prawo do dziedzictwa. Wypływajmy teraz!";
			link.l1.go = "Helena_hire_6";
		break;
		
		case "Helena_hire_2":
			dialog.text = "Co-co powiedziałeś? Helen Sharp? Dlaczego Sharp?";
			link.l1 = "Helen, jesteś córką Beatrice Sharp i jedyną spadkobierczynią dynastii Sharp. To jest połowa mapy, którą przez te wszystkie lata przechowywała pani Gladys. To dowód na twoje prawa do Isla Tesoro. Nie będzie łatwo, ale ja i Jan Svenson zrobimy wszystko, co w naszej mocy, aby pomóc ci odziedziczyć wyspę twojego dziadka.";
			link.l1.go = "Helena_hire_3";
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 3;
			notification("Helen approves", "Helena");
			npchar.lastname = "Sharp";
		break;
		
		case "Helena_hire_3":
			dialog.text = "Oh... Moja biedna matka! Chciałabym kiedyś odnaleźć jej grób i pomodlić się tam za jej duszę. Ale... czekaj! Niemożliwe!";
			link.l1 = "Cóż to, pani Sharp?";
			link.l1.go = "Helena_hire_4";
		break;
		
		case "Helena_hire_4":
			dialog.text = "Proroctwo cyganki właśnie się spełniło... Teraz wreszcie to rozumiem.";
			link.l1 = "Eh? Jaka przepowiednia?";
			link.l1.go = "Helena_hire_5";
		break;
		
		case "Helena_hire_5":
			dialog.text = ""+pchar.name+", możesz mnie nazwać naiwną, ale i tak ci to powiem. Kiedy byłam młodą dziewczyną, cyganka powiedziała mi: 'Twój los będzie w rękach mężczyzny, który nie przyjmie monety wdowy, który zwróci złoto zmarłego i który nazwie matkę'\nWtedy myślałam, że to wszystko to bzdury, ale jakoś udało ci się spełnić każdą część tej przepowiedni, nie ma sposobu, byś o tym wiedział!";
			link.l1 = "Twój los, mówisz... Cóż, może masz rację. Nie zawiodę cię. Razem poszukamy grobu twojej matki. A teraz... Pani Helen Sharp! Przygotuj się do wypłynięcia i nie spóźnij się!";
			link.l1.go = "Helena_hire_6";
		break;
		
		case "Helena_hire_6":
			dialog.text = "Tak jest, kapitanie!";
			link.l1 = "...";
			link.l1.go = "Helena_hire_add";
		break;
		
		case "Helena_hire_add":
			LAi_SetImmortal(npchar, false);
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Saga_HireHelena", -1);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", false);//открыть выходы из города
			pchar.questTemp.Saga = "svenson_wait";
			AddQuestRecord("Saga", "24");
			AddQuestUserData("Saga", "sTimer", AddDaysToDateString(367));
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("Saga_BaronsQuestsGo", 0, 0, 2, false);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			
			if (pchar.questTemp.HelenDrinking.Result != "no_visit") {
				AddQuestRecord("HelenDrinking", "3");
				
				SetFunctionLocationCondition("HelenDrinking_IslaTesoroAmbush", "Pirates_town", false);
				sld = &locations[FindLocation("Pirates_town")];
				sld.locators_radius.quest.detector1 = 4.0;
			}
		break;
		
		//-->  консультации по морским сражениям в искушении барбазона
		case "sea_bomb":
			dialog.text = "Kapitanie "+pchar.name+"! Mam pomysł...";
			link.l1 = ""+npchar.name+" ? Nie jest tu bezpiecznie, mówiłam ci, żebyś został na statku...";
			link.l1.go = "sea_bomb_1";
		break;
		
		case "sea_bomb_1":
			dialog.text = "Charles, w tej starej wannie jest tyle prochu, że jeśli wybuchnie, cały wyspa poleci prosto do drzwi świętego Piotra! Nie ma znaczenia, czy każesz mi się ukryć, czy nie, więc słuchaj mnie!";
			link.l1 = "Dobrze, mów szybko!";
			link.l1.go = "sea_bomb_2";
		break;
		
		case "sea_bomb_2":
			dialog.text = "Korweta i fregata. Nie rozpoznają statku Knive'a jako wrogiego. Możemy wykorzystać ich beztroskę przeciwko nim. Weźmy kilka beczek prochu, ustawmy lont i odpłyńmy do statków\nPozwolą nam się zbliżyć, podpalimy lont, zrzucimy beczkę na jeden z nich i odpłyniemy tak szybko, jak to możliwe. A potem obejrzymy spektakularną eksplozję... Co ty na to?";
			link.l1 = "Improwizowany statek ogniowy... bardzo przebiegłe! Twój plan jest na tyle szalony, że może się udać... jeśli uda nam się zbliżyć na tyle, by nie zostać rozpoznanym.";
			link.l1.go = "sea_bomb_3";
		break;
		
		case "sea_bomb_3":
			dialog.text = "Cóż mamy do stracenia "+pchar.name+"? Nie będzie łatwo walczyć z dwoma statkami naraz, ale będziemy mieli szansę wyrównać szanse...";
			link.l1 = "Dobra. Do dzieła! Chłopaki! Weźcie trzy beczki prochu! Musimy stąd czym prędzej uciec! Uwielbiam twoją wyobraźnię, "+npchar.name+"... Nigdy bym sama na to nie wpadła.";
			link.l1.go = "sea_bomb_4";
		break;
		
		case "sea_bomb_4":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetOfficerType(npchar);
			npchar.dialog.currentnode = "Helena_officer";
			pchar.questTemp.Saga.BarbTemptation.Bomb = "true";
			pchar.questTemp.Saga.BarbTemptation.adviser = "Helena";
		break;
		
		case "fugas":
			dialog.text = "Tak, kapitanie, co się dzieje?";
			link.l1 = "Okręt Jackmana znajduje się w Zatoce Sabo-Matila, ciężka fregata 'Centurion'. Ten statek należał kiedyś do Hawkesów, więc w kabinie Jackmana muszą być ważne przedmioty i dokumenty...musimy go abordażować.";
			link.l1.go = "fugas_1";
		break;
		
		case "fugas_1":
			dialog.text = "Łatwiej powiedzieć niż zrobić. Jak zamierzasz to zrobić na naszej polakrze? Mają więcej ludzi i dział niż my.";
			link.l1 = "Masz rację. Jackman ma co najmniej dwa razy więcej ludzi niż my, a wszyscy są doświadczonymi szermierzami. Byłoby szaleństwem atakować ich bez wstępnego bombardowania. Ale długotrwała walka też nie jest najlepszą opcją. Więc myślałem nad tym, co zrobić.";
			link.l1.go = "fugas_2";
		break;
		
		case "fugas_2":
			dialog.text = ""+pchar.name+", jeszcze nas nie rozpoznali jako wroga, tak jak ci idioci z Turks... Możemy spróbować naszego triku jeszcze raz...";
			link.l1 = "Helen, właśnie Ci powiedziałem, że musimy wejść na pokład i przeszukać fregatę, wysadzenie jej w powietrze nie wchodzi w grę.";
			link.l1.go = "fugas_3";
		break;
		
		case "fugas_3":
			dialog.text = "Poczekaj chwilę, "+pchar.name+", nie zatopimy jej. Zróbmy to inaczej.  Słuchaj, weźmiemy kilka pustych beczek po rumie i napełnimy je prochem, kartaczami i krótkimi lontami. Następnie podpłyniemy bliżej ich fregaty i rzucimy improwizowane ładunki wybuchowe na ich pokład.";
			link.l1 = "Ha! Twój kobiecy spryt wciąż mnie zadziwia! Zamiast statku ogniowego, proponujesz fogaż? Myślisz, że to może zadziałać?";
			link.l1.go = "fugas_4";
		break;
		
		case "fugas_4":
			dialog.text = "A czemuż nie? Ich burta jest wyższa niż nasza, ale dwóch lub trzech ludzi wspomaganych przez bloczek mogłoby łatwo podnieść i rzucić w pełni załadowaną beczkę. Krzykniemy - 'Oto darmowy rum od Knive'a! A beczki wybuchną, zanim zdążą zareagować.";
			link.l1 = "Wystrzeliwujący kartacz zamieni jego najlepszych ludzi na pokładzie w mielone... Do diabła, brzmi to kusząco.";
			link.l1.go = "fugas_5";
		break;
		
		case "fugas_5":
			dialog.text = "Rzućmy pięć beczek naraz z rufowego pokładu na nadbudówkę."+pchar.name+", mamy element zaskoczenia. Jeszcze niczego nie podejrzewają! A potem natychmiast odpłyniemy od nich, zanim będą mieli szansę nas abordażować.";
			link.l1 = "Cóż, spróbujmy. Nie mogą nas rozpoznać, zanim umieścimy te beczki z materiałami wybuchowymi na ich pokładzie... Nie będzie łatwo się zbliżyć. Jackman nie jest tak wielkim głupcem jak Ghoul.";
			link.l1.go = "fugas_6";
		break;
		
		case "fugas_6":
			dialog.text = "Zaryzykujmy, "+pchar.name+"Jak już mówiłam wcześniej, co mamy do stracenia?";
			link.l1 = "Dobry punkt... Stójcie chłopcy! Przygotujcie fougasses i gotujcie się do walki!";
			link.l1.go = "fugas_7";
		break;
		
		case "fugas_7":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			pchar.questTemp.Saga.BarbTemptation.Fugas = "true";
			AddQuestRecord("BarbTemptation", "21");
			DeleteAttribute(npchar, "quest.fugas");
		break;
		//<--  консультации по морским сражениям
		
	// --> разговор по итогам Саги
		case "result":
			//if (!CheckAttribute(pchar, "questTemp.Saga.Helena_friend")) // не друзья
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 11) {
				Achievment_Set("ach_CL_83");
			}
			
			if (sti(pchar.questTemp.Saga.HelenRelation) < 6)
			{
				dialog.text = "Cóż, mój drogi kapitanie... Czas pożegnać się ze sobą. Moja służba się skończyła i pora przyzwyczaić się do bycia Królową Piratów Isla Tesoro. Mam nadzieję, że będę godną następczynią mego wuja. Dziękuję za pomoc.";
				link.l1 = "Aj, szkoda się z tobą rozstawać, ale takie są kaprysy losu. Masz teraz o wiele ważniejsze obowiązki niż służenie na moim statku.";
				link.l1.go = "result_1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.HelenDrinking.Mary")) {
					dialog.text = "Chciałabym móc zostać na twoim statku. Blisko ciebie... Ale to niemożliwe. Bądź szczęśliwy, Charles. I niech ona będzie ciebie warta!";
					link.l1 = "Przykro mi, Helen.";
					link.l1.go = "result_mary";
				} else {
					dialog.text = "To takie dziwne, "+pchar.name+"!  Właśnie stałam się właścicielką całej wyspy, ale nie czuję się Królową Isla Tesoro... Sądzę, że nowy przywódca Bractwa lepiej zarządzałby kolonią niż ja. Mam wiele do nauczenia się.";
					link.l1 = "Nie martw się o to, Helen, jesteś kobietą, która potrafi o siebie zadbać - tak jak mi powiedziałaś, gdy po raz pierwszy weszłaś na pokład.";
					link.l1.go = "result_9";
				}
			}
			
			DeleteQuestCondition("HelenDrinking_AtSHDN");
			DeleteQuestCondition("HelenDrinking_InBlueweldAfterCave");
		break;
		
		case "result_mary":
			dialog.text = "No, nadal będziemy przyjaciółmi, prawda?";
			link.l1 = "Oczywiście... Helen, spotkamy się ponownie na Isla Tesoro. Czy powinienem zabrać cię na twoją wyspę?";
			link.l1.go = "result_12";
		break;
		
		case "result_1":
			dialog.text = "Masz rację... Słuchaj, zaoszczędziłam swoją część łupu podczas żeglugi na twoim statku. Weź to i nawet nie próbuj odrzucić mojej oferty - nie chcę być ci dłużna.";
			link.l1 = "Hej teraz, zaczekaj chwilę...";
			link.l1.go = "result_2";
		break;
		
		case "result_2":
			dialog.text = "Wiem, co zamierzasz powiedzieć. Oczywiście, twoja pomoc była znacznie bardziej znacząca niż ta skromna skrzynia skarbów. Ale to wszystko, co teraz posiadam i muszę ci to spłacić. Weź to, jeśli sam tego nie weźmiesz, zostawię to w twojej kajucie.";
			link.l1 = "Czy teraz popłyniesz sam? Może mógłbym cię zabrać na Isla Tesoro?";
			link.l1.go = "result_3";
		break;
		
		case "result_3":
			GiveItem2Character(pchar, "chest");
			Log_Info("You have received a chest with doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Nie ma potrzeby, "+pchar.name+"Sam dotrę na wyspę. Mam przy sobie miecz i pistolet, to wystarczy na jakiś czas... Jestem pewna, że Królowa Isla Tesoro nie musi się martwić o dochody, gdy już tam dotrę.";
			link.l1 = "Tak jest, wasza wysokość. Życzę ci powodzenia w nowym życiu.";
			if (!CheckAttribute(pchar, "questTemp.Saga.Beltrop_die")) link.l1.go = "result_4";
			else link.l1.go = "result_7";
		break;
		
		case "result_4":
			dialog.text = "Dość tego, nawet w żartach. Dla ciebie wciąż jestem Heleną. Ale to nie wszystko, co chciałam powiedzieć. Odnalazłam mojego ojca, choć było to trochę dziwne. Zapłacił swoim dobrym imieniem angielskiego szlachcica za moje dziedzictwo i to mnie niepokoi. Angielska Wspólnota go ściga i nie chcę, żebyś ty, "+pchar.name+", by wziąć w tym udział.";
			link.l1 = "Oprzytomniej, Helen! On jest bandytą i piratem!";
			link.l1.go = "result_5";
		break;
		
		case "result_5":
			dialog.text = "Pirat? A kimże ty, do cholery, jesteś, by coś takiego mówić? To mój ojciec i to jest dla mnie ważne! A ja, córka bandyty i pirata, mam gdzieś, co angielska sprawiedliwość o nim myśli. Jeśli spróbujesz w jakikolwiek sposób skrzywdzić mojego ojca, zapomnę wszystko dobre, co dla mnie zrobiłeś, wiedz to. Uważaj to za ostrzeżenie.";
			link.l1 = "Czyżby? Tak naprawdę, dziewczyno, powinnaś być bardziej grzeczna. Nie zauważyłem żadnych skarg z twojej стороны na moje pirackie zachowanie, kiedy ratowałem twoją piękną skórę z rąk tego gwałciciela Donovana, czy kiedy dzieliliśmy się zyskami z naszych zdobyczy!";
			link.l1.go = "result_6";
		break;
		
		case "result_6":
			dialog.text = "Ja... Przepraszam. Cofam to, wybacz mi. Straciłam głowę... Ale mimo to, chciałabym pozostać twoją przyjaciółką, co byłoby niemożliwe, jeśli zaczniesz ścigać mojego ojca.";
			link.l1 = "Zrozumiano. Ale nigdy nie waż się mi grozić, kobieto. Powinnaś już wiedzieć po żegludze na moim statku, że nie boję się nikogo i niczego. Szczególnie nie będę tolerował braku szacunku od kobiety - Królowej Piratów czy nie. Mogę być dżentelmenem, ale nawet moja cierpliwość ma swoje granice. Teraz, gdy to wyjaśniliśmy, żegnaj. Życzę ci powodzenia.";
			link.l1.go = "result_8";
		break;
		
		case "result_7":
			dialog.text = "Dziękuję... Być może spotkamy się ponownie, "+pchar.name+"...";
			link.l1 = " A czemuż by nie? Odwiedzę Isla Tesoro jeszcze nie raz w przyszłości. Do zobaczenia tam... Żegnaj, Heleno.";
			link.l1.go = "result_8";
		break;
		
		case "result_8": // Элен уходит, но её не затираем
			DialogExit();
			RemovePassenger(pchar, npchar);
			//chrDisableReloadToLocation = true;//закрыть локацию  // уже не надо.
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "goto", "goto24", "", "", "", "", 7);//OpenTheDoors лесник . чтобы бежала и исчезла а не стояла.
			AddQuestRecord("Testament", "11");
			CloseQuestHeader("Testament");
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false); // лесник . пирс. 
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false); // ворота.
			InterfaceStates.Buttons.Save.enable = true;//можно сохраняться		
			if (CheckAttribute(pchar, "questTemp.LSC.MaryWait")) {
				pchar.questTemp.LSC.Mary = "return";
			}
		break;
		
		case "result_9": // вот тут - ключевой момент, если игрок нашёл Мэри - выбирай, какая девушка милее
			dialog.text = "Jestem pewna. "+pchar.name+", Chciałabym zostać na twoim statku, jeśli mi pozwolisz. Zostać z tobą...";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive")
			{
				link.l1 = "Nie rozumiesz, Helen. Cała twoja przyszłość jest przed tobą i nie masz się o co martwić. Przede mną tylko wojna, polityczne intrygi i całkowita niepewność. Musisz ułożyć sobie życie, w którym nie ma miejsca dla takiego dzikiego włóczęgi jak ja.";
				link.l1.go = "result_10";
				link.l2 = "Wybieram Helene) To więcej, niż mogłem się spodziewać, Helen. Oczywiście, że nie chcę cię stracić, ale lepiej byłoby, gdybyś udała się na Isla Tesoro. Kto wie, dokąd jeszcze zaprowadzi mnie los. Teraz przede mną wojna, polityczne intrygi i niepewność.";
				link.l2.go = "result_15";
			}
			else
			{
				link.l1 = "To więcej, niż mogłem się spodziewać, Helen. Oczywiście, że nie chcę cię stracić, ale lepiej byłoby, gdybyś udała się na Isla Tesoro. Kto wie, dokąd jeszcze zaprowadzi mnie mój los. Teraz przede mną wojna, polityczne intrygi i niepewność.";
				link.l1.go = "result_15";
			}
		break;
		
		case "result_10":
			dialog.text = ""+pchar.name+"Nie kłam mi. Po prostu nie chcesz... Powiedz mi, kim ona jest? To ta rudowłosa ladacznica z Miasta Porzuconych Statków, czyż nie mam racji?";
			link.l1 = "Helen! Próbuję ci powiedzieć, co uważam za najlepsze dla ciebie! Jak możesz tego nie rozumieć?!";
			link.l1.go = "result_11";
		break;
		
		case "result_11":
			dialog.text = "Oczywiście, oczywiście, że tak... A jak ona zdołała cię oczarować, co? Co ona ma, czego *ja* nie mam?! Czy naprawdę jest taka dobra? Eh, "+pchar.name+"... Cóż, to twoja decyzja, nie pozostaje mi nic innego, jak wrócić na moją wyspę. Nie mogę stać między wami\nDziękuję za wszystko, co dla mnie zrobiłeś, Charles. Jesteś najlepszym człowiekiem, jakiego kiedykolwiek spotkałam. Mam nadzieję, że możemy pozostać przyjaciółmi?";
			link.l1 = "Oczywiście... Helen, zobaczymy się ponownie na Isla Tesoro. Czy chcesz, żebym cię tam zabrał?";
			link.l1.go = "result_12";
		break;
		
		case "result_12":
			dialog.text = "Nie ma potrzeby. Kupię nowy statek. Zebrałam wystarczająco pieniędzy, by kupić i wyposażyć szkuner, służąc pod twoim dowództwem. Znów popłynę na nowym 'Tęcza'.";
			link.l1 = "Cieszę się, Helen, że byłaś tak... oszczędna. Ale żeglowanie na szkunerze nie przystoi Królowej Piratów z Isla Tesoro. Wkrótce powinnaś zdobyć dla siebie fregatę.";
			link.l1.go = "result_13";
		break;
		
		case "result_13":
			dialog.text = "Być może, "+pchar.name+" Dobrze. Pójdę do stoczni, ale najpierw... daj mi całusa na pożegnanie... Proszę...?";
			link.l1 = "Helen...";
			link.l1.go = "result_14";
		break;
		
		case "result_14": // прощальный поцелуй
			DialogExit();
			SetMusic("music_romantic");
			SetLaunchFrameFormParam("", "", 0, 12);
			SetLaunchFrameFormPic("loading\inside\kiss.tga");
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 0, 20); //крутим время
			RecalculateJumpTable();
			DoQuestCheckDelay("Saga_HelenaBye", 0.5);
			pchar.questTemp.LSC.Mary = "return"; // к Мэри
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false); // лесник . пирс. 
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false); // ворота.
			InterfaceStates.Buttons.Save.enable = true;//можно сохраняться
		break;
		
		case "result_15":
			dialog.text = "Los mój jest związany z twoim odkąd się spotkaliśmy. Czy tego nie rozumiesz?"+pchar.name+"? Będę podążać za tobą na krańce świata!";
			link.l1 = "A co z twoim ojcem? Laurence Beltrope? On jest moim wrogiem...";
			link.l1.go = "result_16";
		break;
		
		case "result_16":
			dialog.text = "Mój ojciec to Sean McArthur. Kochałam go i opłakiwałam jego śmierć. Był moim jedynym ojcem. A ten pirat... Nawet nie chcę o nim mówić.";
			link.l1 = "Hele... Moja droga Hele!";
			link.l1.go = "result_17";
		break;
		
		case "result_17":
			dialog.text = ""+pchar.name+", Zawsze chciałam Ci powiedzieć, że jesteś najwspanialszym człowiekiem, jakiego kiedykolwiek spotkałam! Zrobiłeś dla mnie tak wiele, że nigdy nie będę w stanie Ci się odwdzięczyć. Chcę zostać z Tobą. Na zawsze. Wyjdę za Ciebie, jeśli zechcesz... Kocham Cię.";
			link.l1 = "Zawsze będziemy razem. Obiecuję!"; // а куда же ты теперь денешься :)
			if (!CheckAttribute(pchar, "questTemp.Saga.Helena_friend")) {
				link.l1.go = "result_17A";
			} else {
				link.l1.go = "result_18";
			}
		break;
		
		case "result_17A":
			dialog.text = "Obiecaj, że zrobisz coś dla mnie teraz? I proszę, nie śmiej się!";
			link.l1 = "Obiecuję, moja droga!";
			link.l1.go = "result_17A_1";
		break;
		
		case "result_17A_1":
			dialog.text = "Nazywaj mnie moim prawdziwym imieniem. Proszę!";
			link.l1 = "Kochać cię, Helen Sharp.";
			link.l1.go = "result_18";
		break;
		
		case "result_18":
			dialog.text = ""+pchar.name+", mój drogi... Przytul mnie! Czekałam na ten moment zbyt długo!";
			link.l1 = "Helen, moja droga...";
			link.l1.go = "result_19";
		break;
		
		case "result_19": // романтик-сцена
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			StartQuestMovie(true, true, true);
			PlayStereoOGG("music_romantic");
			InterfaceStates.Buttons.Save.enable = false;//запретить сохраняться
			locCameraRotateAroundHero(0.0, 2.0, 0.0, 0.01, 0.0, 2.0, 0.0, 580);
			Pchar.FuncCameraFly = "";
			DoQuestCheckDelay("Saga_HelenaRomantic", 20.0);
			pchar.GenQuest.MusicContinue = true;
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			DeleteAttribute(pchar, "questTemp.LSC.MaryWait");
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false); // лесник . пирс. 
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false); // ворота.																					   
			
			pchar.quest.HelenUpgradeShip.win_condition.l1 = "Timer";
			pchar.quest.HelenUpgradeShip.win_condition.l1.date.day = GetAddingDataDay(0, 0, 180);
			pchar.quest.HelenUpgradeShip.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 180);
			pchar.quest.HelenUpgradeShip.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 180);
			pchar.quest.HelenUpgradeShip.win_condition.l2 = "location";
			pchar.quest.HelenUpgradeShip.win_condition.l2.location = "PortRoyal_town";
			pchar.quest.HelenUpgradeShip.function = "HelenUpgradeShip";
			
			// Квест Лонгвея "Путеводная звезда", начало 5 этапа
			if (GetCharacterIndex("Longway") != -1 && CheckPassengerInCharacter(pchar, "Longway") && CheckAttribute(pchar, "questTemp.PZ_Etap5_Start") && !CheckAttribute(pchar, "questTemp.PZ_ProvalFinal"))
			{
				PChar.quest.PZ_Etap5_Start.win_condition.l1 = "location";
				PChar.quest.PZ_Etap5_Start.win_condition.l1.location = "Pirates_town";
				PChar.quest.PZ_Etap5_Start.win_condition = "PZ_Etap5_Start";
				AddMapQuestMarkCity("Pirates", false);
			}
		break;
		
		case "happy":
			dialog.text = ""+pchar.name+"! To było... niesamowite! Nie chcę nigdzie indziej iść... Zostańmy tu do rana. Świat może poczekać!";
			link.l1 = "Poczekamy z tym, Helen!";
			link.l1.go = "happy_1";
		break;
		
		case "happy_1":
			DialogExit();
			LSC_MaryLoveWaitTime();
			SetLaunchFrameFormParam("Next morning...", "", 0, 4);
			LaunchFrameForm();
			DoQuestCheckDelay("Saga_HelenaRomantic_5", 4.0);
			pchar.questTemp.Saga.Helena_officer = "true"; // показатель, что Элен - наша навсегда
			
			pchar.GenQuest.BrothelCount = 0;
			
			pchar.quest.Helen_GiveSex.win_condition.l1 = "Timer";
			pchar.quest.Helen_GiveSex.win_condition.l1.date.day = GetAddingDataDay(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l1.date.month = GetAddingDataMonth(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l1.date.year  = GetAddingDataYear(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l2 = "Location_Type";
			pchar.quest.Helen_GiveSex.win_condition.l2.location_type = "town";
			pchar.quest.Helen_GiveSex.function = "Helen_GiveSex";
			
			// Запуск квеста Дороже золота
			SetFunctionTimerCondition("GoldenGirl_Start", 0, 0, 1, false);
		break;
		
	// -------------------------------------------- провалы саги ------------------------------------
		case "failcenturion":
			dialog.text = "Kapitanie! Jackman nie żyje... Czy moja rodzina jest wreszcie bezpieczna?";
			link.l1 = "Tak, Helen, wszyscy jesteście bezpieczni. Ale 'Centurion' został zatopiony, a wraz z nim wszystkie dokumenty, które mogłyby nam pomóc znaleźć grób twojej matki i udowodnić twoje prawa do roszczeń na Isla Tesoro... Eh... Teraz będę musiał szturmować Tortugę sam...";
			link.l1.go = "failcenturion_1";
		break;
		
		case "failcenturion_1":
			dialog.text = ""+pchar.name+", nie martw się tak bardzo. Nic nie możemy na to poradzić. Nie martw się też o mnie, poradzę sobie bez tej wyspy. Dziękuję za wszystko, co dla mnie zrobiłeś!";
			link.l1 = "Wygląda na to, że zamierzasz... mnie opuścić, prawda?";
			link.l1.go = "failcenturion_2";
		break;
		
		case "failcenturion_2":
			dialog.text = "Tak, mój kapitanie. Udało mi się zebrać wystarczająco pieniędzy, aby kupić i wyposażyć szkuner. Znów popłynę na mojej 'Tęczy'. Spotkamy się ponownie w Blueweld... Wracam do domu.";
			link.l1 = "No cóż... powodzenia, Helen!";
			link.l1.go = "failcenturion_3";
		break;
		
		case "failcenturion_3":
			DialogExit();
			RemovePassenger(pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 5.0);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary") && GetCharacterIndex("Mary") != -1 && !CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) // patch-6
			{
				pchar.questTemp.LSC.Mary = "return"; // к Мэри
			}
		break;
		
		case "late_l1":
			dialog.text = "Cóż, mój kapitanie... Wygląda na to, że ponieśliśmy porażkę. Żegnaj. Wracam do domu. Zarobiłam wystarczająco dużo pod twoim dowództwem, by kupić sobie nową szkunerę. Spotkamy się ponownie na morzu!";
			link.l1 = "Powodzenia, Helen. Przykro mi za wszystko. Żegnaj.";
			link.l1.go = "failcenturion_3";
		break;
		
		case "late_l2":
			dialog.text = "Kapitanie! Jackman nie żyje... Więc wydaje się, że moja rodzina jest bezpieczna, prawda?";
			link.l1 = "Tak, Helen, jest bezpiecznie. Ale nie jestem zadowolony, straciłem zbyt wiele czasu, a Isla Tesoro to teraz angielska kolonia. Zostałaś bez swojego dziedzictwa, więc będę musiał sam szturmować Tortugę...";
			link.l1.go = "failcenturion_1";
		break;
		
		case "late_l3":
			dialog.text = ""+pchar.name+", co powiedział ci prawnik?";
			link.l1 = "Straciłam zbyt wiele czasu i Isla Tesoro jest teraz angielską kolonią. Zostałaś bez swojego dziedzictwa, więc będę musiał sam szturmować Tortugę... Niestety, przegraliśmy.";
			link.l1.go = "failcenturion_1";
		break;
	// <-- провалы Саги
		
		// секс - Элен соглашается не всегда (голова болит, а что вы хотели? :)) и сама не требует секса
		case "cabin_sex":
			if (CheckAttribute(npchar, "quest.refusesex")) {
				dialog.text = "Nie, kochanie, to nie zadziała.";
				link.l1 = "Cóż, czemu nie?!";
				link.l1.go = "refuse";
				break;
			}
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
			if (drand(4) == 0)// вероятность отказа 20%
			{
				dialog.text = RandPhraseSimple(""+pchar.name+", nie czuję się dzisiaj dobrze. Nie martw się, proszę, to nie twoja wina. Nie róbmy tego dzisiaj..."," "+pchar.name+"  Drogi, byłam bardzo zmęczona przez ostatnie dni. Szczerze mówiąc, jedyne czego pragnę, to sen. Wybacz mi. Zróbmy to innym razem.");
				link.l1 = RandPhraseSimple("Dobrze...","To w porządku. Jak sobie życzysz...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = RandPhraseSimple(""+pchar.name+", nastrój jest właśnie odpowiedni, chodźmy!",""+pchar.name+"jasne, bez żadnych pytań! Chodźmy!");
				link.l1 = RandPhraseSimple("To moja dziewczyna...","Jesteś taka urocza, Helen...");
				link.l1.go = "exit";
				pchar.quest.sex_partner = Npchar.id;
				AddDialogExitQuest("cabin_sex_go");
			}
		break;
		
		case "sex_after":
			dialog.text = LinkRandPhrase(RandPhraseSimple("To było cudowne, "+pchar.name+"!..","Byłeś wspaniały jak zawsze, drogi..."),RandPhraseSimple("To było wspaniałe, Charles!","Miałam cudowny czas, drogi!"),RandPhraseSimple("Z tobą nigdy nie jest nudno, mój kapitanie!","Byłeś wspaniały, kochanie!"));
			link.l1 = RandPhraseSimple(" Kocham cię... ","Zawsze dobrze być z tobą, Helen...");
			link.l1.go = "exit";
			NextDiag.TempNode = "Helena_officer";
			chrDisableReloadToLocation = false;//открыть локаци.
		break;
		
		case "room_sex":
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "tavern")
			{
				dialog.text = ""+pchar.name+", wiesz, że zawsze się cieszę, aby... Ale to nie odpowiedni czas teraz - musimy złapać tego łajdaka Thibauta, zanim ucieknie.";
				link.l1 = "Masz rację, jak zawsze, Helen...";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(npchar, "quest.refusesex")) {
				dialog.text = "Nie, kochanie, to nie zadziała.";
				link.l1 = "No cóż, czemu nie?!";
				link.l1.go = "refuse";
				break;
			}
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
			if (drand(4) == 0) // вероятность отказа 20%
			{
				dialog.text = RandPhraseSimple(""+pchar.name+", dzisiaj nie czuję się dobrze. Nie czuj się urażony, proszę. Nie róbmy tego dzisiaj...",""+pchar.name+", drogi, byłam tak zmęczona przez ostatnie kilka dni. Szczerze mówiąc, chcę tylko spać. Wybacz mi. Zróbmy to innym razem.");
				link.l1 = RandPhraseSimple("Dobrze...","W porządku. Jak sobie życzysz...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = RandPhraseSimple(""+pchar.name+", kocham cię! Chodźmy!",""+pchar.name+"Tak jest, kapitanie! Ruszajmy!");
				link.l1 = RandPhraseSimple("Jesteś moją dobrą dziewczyną...","Jesteś przepiękna, Helen...");
				link.l1.go = "room_sex_go";
			}
		break;
		
		case "room_sex_go":
			DialogExit();
			pchar.quest.sex_partner = Npchar.id;
			chrDisableReloadToLocation = true;
			//npchar.quest.daily_sex_room = true; // для первого раза в таверне чтобы счетчик запустить . лесник
			//npchar.quest.daily_sex_cabin = true;
			if (sti(pchar.money) >= 10) AddMoneyToCharacter(pchar, -10);
			sld = CharacterFromID("Helena");
			ChangeCharacterAddressGroup(sld, loadedLocation.fastreload + "_tavern_upstairs", "quest", "quest3");
			DoFunctionReloadToLocation(loadedLocation.fastreload + "_tavern_upstairs", "quest", "quest4", "GiveKissInRoom");
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Helena_officer":
			ref rLoc = &Locations[FindLocation(pchar.location)];
			dialog.text = LinkRandPhrase("Tak, "+pchar.name+"?","Tak, mój kapitanie?","Słucham, "+pchar.name+"...");
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.CutlassTraining")) {
				DeleteAttribute(pchar, "questTemp.HelenDrinking.CutlassTraining");
				dialog.text = "Patrz na to, mój kapitanie!";
				link.l1 = "Wow, ależ uścisk! Widzę, że nie traciłaś czasu, Helen.";
				link.l1.go = "cutlass_training";
				NextDiag.TempNode = "Helena_officer";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && sti(pchar.GenQuest.BrothelCount) > 0 && !CheckAttribute(npchar, "quest.refusesex")) {
				dialog.text = "Mój drogi, co do twoich wizyt u prostytutek.";
				npchar.quest.refusesex = true;
				link.l1 = "Co? Helen, zupełnie się mylisz! Ja tylko...";
				link.l1.go = "brothel_found";
				NextDiag.TempNode = "Helena_officer";
				SetFunctionTimerCondition("Helena_ClearRefuseSex", 0, 0, 180, false);
				DeleteQuestCondition("Helen_GiveSex");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Helen, zamierzam odwiedzić zagubione indiańskie miasto Tayasal. Nie będę ci kłamać: ta podróż jest bardzo niebezpieczna, a co więcej - obejmuje teleportację przez idola. Czy ty... pójdziesz za mną?";
				Link.l4.go = "tieyasal";
			}
       ////////////////////////казначей///////////////////////////////////////////////////////////
           		// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Helen, daj mi pełen raport o statku.";
			    Link.l11.go = "QMASTER_1";
			        
			    // Warship. Автозакупка товара
				Link.l12 = "Chcę, abyś kupował pewne towary za każdym razem, gdy jesteśmy w porcie.";
				Link.l12.go = "QMASTER_2";
			}
			
            /////////////////////////////////////казначей////////////////////////////////////////////////////////////     			
			if (CheckAttribute(NPChar, "IsCompanionClone"))//////////////////компаньон//////////////////////////////////////////////
			{
				//dialog.text = "Przybyłem na twoje wezwanie, kapitanie.";
				Link.l2 = "Eleno, muszę ci wydać kilka rozkazów.";
				Link.l2.go = "Companion_Tasks";
				
				sld = GetCharacter(sti(npchar.RealCompanionIdx));
				if (CheckAttribute(pchar, "questTemp.HelenDrinking.Rainbow") && sld.ship.type == pchar.questTemp.HelenDrinking.Rainbow && CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) {
					DeleteAttribute(link, "");
					dialog.text = "Czy uważasz, że to zabawne?";
					link.l1 = "Ładny statek, prawda? Zdobyłem go dla ciebie, Helen! Pomyśl tylko, jaki facet na Karaibach daje swojej damie prawdziwy statek, co?";
					link.l1.go = "rainbow";
					
					NextDiag.TempNode = "Helena_officer";
					break;
				}
				
				NextDiag.TempNode = "Helena_officer";// не забыть менять в зависисомости от оффа
				break;
			}																															
			if (CheckAttribute(npchar, "quest.fugas"))
			{
				Link.l3 = "Helen, potrzebuję twojej rady.";
				Link.l3.go = "fugas";
			}
			Link.l1 = "Helen, mam dla ciebie zlecenie...";
            Link.l1.go = "stay_follow";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && pchar.location == Get_My_Cabin() && GetNpcQuestPastDayWOInit(npchar, "sex_date") >= 1) // mitrokosta - очередные исправления интима
			{
				Link.l2 = RandPhraseSimple("Helen, zostańmy razem sami w kajucie... na kilka godzin? Co o tym sądzisz?","Kochanie, spędźmy następne kilka godzin tête-à-tête? Podoba ci się ten pomysł?");
				Link.l2.go = "cabin_sex";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && rLoc.type == "tavern" && sti(pchar.money) >= 10 && GetNpcQuestPastDayWOInit(npchar, "sex_date") >= 1) // mitrokosta - очередные исправления интима
			{
				Link.l2 = RandPhraseSimple("Helen, dlaczego nie wynajmiemy pokoju i nie zostaniemy tam na osobności... przez następne kilka godzin? Co o tym sądzisz?","Kochanie, spędźmy kilka następnych godzin tête-à-tête? Wynajmiemy pokój... co myślisz?");
				Link.l2.go = "room_sex";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && rLoc.type == "town" && sti(pchar.money) >= 1000 && GetNpcQuestPastDayWOInit(npchar, "special_sex_date") >= 30 && !CheckAttribute(npchar, "quest.refusesex"))
			{
				Link.l2 = "Heleńko, droga, czy mogę zaprosić cię na chwilę relaksu w tawernie?";
				Link.l2.go = "special_sex";
			}
			if (CheckAttribute(pchar, "questTemp.MysteryPortRoyal_Helena")) {
				link.l4 = "Helen, wygląda na to, że znalazłem ostatnią wolę twojego wielbiciela – Francisa. Zostawił ci swoje dziedzictwo.";
				link.l4.go = "MysteryPortRoyal_Helena_1";
			}
			if (CheckCharacterItem(pchar, "pirate_cutlass") && !CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) {
				link.l4 = "Myślę, że ten kordelas teraz należy do ciebie. Blaise to twój rzekomy wujek...";
				link.l4.go = "give_cutlass";
			}
			link.l9 = "Nic teraz, Helen.";
			NPChar.id = "Helena"; // лесник . Идентификация Элен на всяк. случай . если потеряет сознание.
			link.l9.go = "exit";
			NextDiag.TempNode = "Helena_officer";
		break;
		
		/////////////////////////// ответы для казнаячея - Элен ..(элен казначей - ужас!))///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Charles, kochanie, czy jesteś chory czy coś? Cóż, oczekujesz, że zejdę pod pokład, pozamiatam ładownię i zacznę liczyć szczury?";
			Link.l1 = "Racja, przepraszam kochanie, mój błąd...";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "A ja chcę mieć własny okręt liniowy, ze setką dział płynący z prędkością 20 węzłów. Byłam kapitanem jak ty przez całe życie. Znajdź sobie przeklętego intendententa i zawracaj mu tym głowę.";
			link.l1 = "Tak, masz rację, Helen. Przepraszam za to.";
			link.l1.go = "exit";
		break;
		//Указания для компаньона 19.02.08 -->/////////////////////////////////////////////////////////////////////////////////////////
		case "Companion_Tasks":
			dialog.Text = "Słucham uważnie.";
			Link.l1 = "O naszej polityce abordażu...";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "O statku, którym dowodzisz...";
			Link.l2.go = "Companion_TaskChange";
			Link.l8 = "Nic do tej pory.";
			Link.l8.go = "exit";
			 
		break;
		
		case "Companion_TaskBoarding":
			dialog.Text = "Jakie jest twoje życzenie, mój kapitanie?";
			Link.l1 = "Nie chcę, żebyś się na coś zaokrętowywał. Utrzymuj siebie i swoich ludzi w bezpieczeństwie.";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "Chcę, abyś wszedł na pokład wrogich statków przy pierwszej okazji.";
			Link.l2.go = "Companion_TaskBoardingYes";
		break;
		
		case "Companion_TaskChange":
			dialog.Text = "Tak, mój kapitanie?";
			Link.l1 = "Byłabym wdzięczna, gdybyś powstrzymał się od zamiany statków po wejściu na pokład. Ona jest dla mnie zbyt cenna.";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "Jeśli zdarzy ci się wejść na pokład jakiegoś statku, przyjrzyj się dobrze zdobycznemu okrętowi. Jeśli jest coś warta, śmiało weź ją dla siebie.";
			Link.l2.go = "Companion_TaskChangeYes";
		break;
		
		case "Companion_TaskBoardingNo":
			dialog.Text = "Dobrze,   pomyślę o tym.";
			Link.l1 = "Zastanowi się nad tym... Jasne, jakbym w ogóle mógł jej wydawać rozkazy.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
		break;
		
		case "Companion_TaskBoardingYes":
			dialog.Text = "Dobrze, zastanowię się nad tym.";
			Link.l1 = "Ona się nad tym zastanowi... Tak, jakbym i tak mógł wydawać jej rozkazy.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
		break;
		
		case "Companion_TaskChangeNo":
			dialog.Text = "Dobrze, pomyślę o tym.";
			Link.l1 = "Ona to przemyśli... Jasne, jakbym mógł jej w ogóle wydawać rozkazy.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;
		
		case "Companion_TaskChangeYes":
			dialog.Text = "Dobrze, zastanowię się nad tym.";
			Link.l1 = "Zastanowi się nad tym... Jasne, jakbym mógł jej w ogóle wydawać rozkazy.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;
	//	<========//////////////////////////////////////																																			  
		
		case "stay_follow":
            dialog.Text = "Rozkazy?";
            Link.l1 = "Stań tutaj!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Za mną i trzymaj tempo!";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Zmień rodzaj amunicji do swojej broni palnej.";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Wybierz rodzaj amunicji:";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");;
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;		
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "Natychmiast, kapitanie!";
            Link.l1 = "...";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Natychmiast, kapitanie!";
            Link.l1 = "...";
            Link.l1.go = "Exit";
        break;
		//<-- ----------------------------------- офицерский блок ----------------------------------------
		
		// --> суп из черепахи
		case "terrapin_grot":
			dialog.text = "Tam jesteś! W końcu cię znalazłam... To było coś, mój kapitanie! Nigdy nie widziałam takiego biegu po dachu i skoku z takiej zapierającej dech w piersiach wysokości! Moje serce było gotowe eksplodować! Pewnego dnia zabijesz mnie tymi swoimi sztuczkami, drogi... Och, nie jesteś sam... Kim jest ta dziewczyna?";
			link.l1 = "To jest Catherine Fox, córka pułkownika Foxa, dowódcy słynnego angielskiego morskiego regimentu piechoty 'Morskie Lisy'. Zabieramy ją na Antiguę.";
			link.l1.go = "terrapin_grot_1";
		break;
		
		case "terrapin_grot_1":
			dialog.text = "„Czyżby...Witamy na pokładzie, Pani Fox! Nie nie, nie trzym się ramienia kapitana de Maure, możesz iść całkiem dobrze sama! A teraz do szalupy ratunkowej - musimy się stąd wydostać.”"; 
			link.l1 = "Ha! Dziękuję, Helen! Co bym bez ciebie zrobił? Catherine, chodź za nami!";
			link.l1.go = "terrapin_grot_2";
		break;
		
		case "terrapin_grot_2":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			Terrapin_GotoShip();
		break;
		// <-- суп из черепахи
		
		// --> калеуче
		case "on_coast":
			dialog.text = "W końcu się obudziłeś, drogi! Jak się czujesz? Prawie mnie przyprawiłeś o zawał...";
			link.l1 = "Helen, co się stało? Moja głowa pęka...";
			link.l1.go = "on_coast_1";
		break;
		
		case "on_coast_1":
			dialog.text = "Kiedy weszliśmy do kajuty kapitana, leżałeś nieruchomo na podłodze. Moje serce prawie przestało bić! Chłopcy podnieśli cię i przeciągnęli z powrotem na nasz statek - w samą porę, bo martwi leżący na pokładzie zaczęli znów się podnosić.\nCo za horror! To prawie wystarczy, bym uwierzyła w Boga! Byli całkowicie odporni na nasze ostrza i kule! Szybko przecięliśmy liny i próbowaliśmy odpłynąć, ale salwa z ich statku poważnie uszkodziła nasz i straciliśmy kontrolę. Potem podnieśli żagle i zniknęli w mgnieniu oka.\nNasz statek osiadł na mieliźnie, więc musieliśmy uciekać na ten brzeg, zanim burza go zniszczy. Wielu dobrych ludzi zginęło dziś, ale statek przetrwał na koniec... gdybym tylko nie rozkazała go porzucić...";
			link.l1 = "Nie twoja wina, Helen. To była właściwa decyzja. Co bym bez ciebie zrobił?";
			link.l1.go = "on_coast_2";
		break;
		
		case "on_coast_2":
			dialog.text = "Zaciągnęłam cię do łodzi, a potem na brzeg. Wyglądałeś na martwego, tylko twoje serce ledwo biło. Spójrz! Moje ręce wciąż się trzęsą";
			link.l1 = "Dziękuję, kochanie. Jestem ci dłużna. Jak długo tutaj leżę?";
			link.l1.go = "on_coast_3";
		break;
		
		case "on_coast_3":
			dialog.text = "Cały dzień. Myłam i opatrywałam twoje rany, dawałam ci lekarstwa i nalewałam rumu. Teraz musisz wyzdrowieć!";
			link.l1 = "Nie umrę tym razem, kochanie. Chociaż nie czuję się dobrze... blurgh....";
			link.l1.go = "on_coast_4";
		break;
		
		case "on_coast_4":
			dialog.text = "Powiedz mi.... Czy to był prawdziwy 'Latający Holender', Charles? Dlaczego nas zaatakowali? I dlaczego nie strzelali do nas przy podejściu, ale próbowali zatopić nas natychmiast po wejściu na pokład?";
			link.l1 = "Ich kapitan potrzebował tego amuletu, o którym rozmawiałam z Tuttuathapakiem, indiańskim szamanem. Dlaczego go potrzebowali, nie wiem... ale jak tylko ich przywódca dostał amulet, pozbyli się nas... Wszechmogący Boże, co za nieszczęsny koszmar! Statek obsadzony przez żywych trupów! Niemożliwe do uwierzenia...";
			link.l1.go = "on_coast_5";
		break;
		
		case "on_coast_5":
			dialog.text = "Aj, teraz przyszła nasza kolej, by napotkać 'Latającego Holendra'. Gah! Aż mnie ciarki przechodzą! W następnym porcie, w którym się zatrzymamy, idę do kościoła, zapalę świecę i będę modlić się do naszego Pana Jezusa Chrystusa o nasze cudowne ocalenie. Cholera, jestem tak wdzięczny, że nawet pomodlę się do jakichś papieskich świętych...";
			link.l1 = " Będę tam z tobą, Helen, dawno nie byłem na porządnej spowiedzi... Ale najpierw musimy wrócić do tej wioski. Muszę opowiedzieć Tuttuathapakowi wszystko. Ten przeklęty statek zaatakował nas przez amulet! Mam nadzieję, że ten czerwonoskóry diabeł ma jakieś pomysły, po co do diabła tym żywym trupom mógł być on potrzebny.";
			link.l1.go = "on_coast_6";
		break;
		
		case "on_coast_6":
			dialog.text = "Dobrze.   Ale musimy być ostrożni - twoje rany ledwo się zagoiły.";
			link.l1 = "Ale pomożesz mi szybciej wyzdrowieć, prawda? Kocham Cię, Helen...";
			link.l1.go = "on_coast_7";
		break;
		
		case "on_coast_7":
			chrDisableReloadToLocation = false;//открыть локацию
			dialog.text = "Też cię kocham, mój drogi...";
			link.l1 = "...";
			link.l1.go = "on_coast_8";
		break;
		
		case "on_coast_8":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			AddQuestRecord("Caleuche", "5");
		break;
		// <-- калеуче
		
		// на Тайясаль
		case "tieyasal":
			dialog.text = ""+pchar.name+", powiedziałam ci raz, że teraz dzielimy losy. Twój los jest moim losem. Kiedy ruszamy?";
			link.l1 = "Bardzo się cieszę, że to słyszę. Powiem ci trochę później, kiedy tam pójdziemy. Musimy się przygotować.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Jestem gotowa, mój kapitanie! Pójdę za tobą na koniec świata!";
			link.l1 = "Dziękuję, moja miłości...";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "20");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		// на Исла Тесоро
		case "islatesoro":
			dialog.text = "O, "+pchar.name+" ! Cieszę się, że cię widzę! Co tu robisz na Isla Tesoro?";
			link.l1 = "To samo co zawsze - interesy. Chciałem tylko wpaść i zobaczyć się z tobą. Jak się masz, Helen?";
			link.l1.go = "islatesoro_1";
		break;
		
		case "islatesoro_1":
			DialogExit();
			NextDiag.CurrentNode = "islatesoro";
		break;
		
		// Jason Дороже золота
		case "GoldenGirl":
			dialog.text = "Co się dzieje z naszym najdroższym gubernatorem, Kapitanie? Czyj tyłek tym razem kopniemy? Hiszpanów, piratów, czy kogoś gorszego?";
			link.l1 = "To gorzej, Helen, znacznie gorzej. Gubernator zamierza złożyć wizytę kosztownej kurtyzanie, a ja mam mu towarzyszyć jako ciekawostka. Obiecał swojej kochance przyprowadzić prawdziwego korsarza, awanturnika i wszechstronnego wilka morskiego. Czeka mnie więc nudna rozmowa, przepłacone wino i nudni szlachcice.";
			link.l1.go = "GoldenGirl_1";
			link.l2 = "Wprost przeciwnie, zaproszenie na przyjemne wydarzenie towarzyskie, prowadzone przez damę. Jego Ekscelencja zaskoczył mnie, prosząc, abym mu towarzyszyła, ale szczerze mówiąc, cieszę się, że mogę na chwilę oderwać się od pracy.";
			link.l2.go = "GoldenGirl_5";
		break;
		
		case "GoldenGirl_1":
			dialog.text = "Oj... więc straszliwy kapitan Charles de Maure przebierze się i zatańczy jak oswojona małpka dla ich zabawy? Jakie to słodkie! Mam lepszy pomysł. Postawmy żagle i wynośmy się stąd. Jeśli masz ochotę na zasłużony urlop, popłyńmy na Isla Tesoro. Zawsze jesteśmy tam mile widziani. Opalanie się, biały piasek, starzy przyjaciele, poncz rumowy, oderwanie się od rzeczywistości - co tylko chcesz.";
			link.l1 = "Spójrz, to wszystko brzmi fantastycznie, i bardzo bym chciała... ale później. Obiecałam gubernatorowi, to ważne dla staruszka i...";
			link.l1.go = "GoldenGirl_2";
		break;
		
		case "GoldenGirl_2":
			dialog.text = "A co z tego? Myślisz, że twoja szlachetna krew coś dla nich znaczy? Może nie jestem z francuskiej krwi, ale wiem wszystko o ich 'wysokim towarzystwie', a dla nich Charles de Maure nie jest kapitanem, którego ludzie śledzą i powierzają mu swoje życie. Nie jest dżentelmenem jak oni. Prawdziwi dżentelmeni nie pływają po morzu i nie walczą w chmurze prochu strzelniczego. Charles de Maure to tylko ciekawy dodatek do ich posiłku. Jak oswojony lampart czy domowy Murzyn przebrany w stroje! Wymyślna zabawka! Od kiedy poddajesz się takiemu traktowaniu?!";
			link.l1 = "Helen, proszę, uspokój się. Jestem pewien, że mogę znieść kilka nieprzyjemnych spojrzeń dla zadowolenia gubernatora i naszej przyszłej pomyślności. Dobrze jest mieć potężnych przyjaciół. W końcu to będzie łatwiejsze niż prowadzenie abordażu! A te 'nieudaczniki' nie zawsze są takie. Nawet w wyższych sferach są godni ludzie... przynajmniej powinni być.";
			link.l1.go = "GoldenGirl_3";
		break;
		
		case "GoldenGirl_3":
			dialog.text = "Cokolwiek. (rzuca włosami) Ale ostrzegam cię - nie ma mowy, żebym wcisnęła się w elegancką suknię. Jeśli zmusisz mnie iść, założę moje spodnie. Mam gdzieś, czy wszystkie damy na Karaibach zemdleją z dezaprobaty.";
			link.l1 = "Nie zamierzałam cię do tego zmuszać. Nie ma sensu, abyśmy oboje cierpieli. Przetrwam tę imprezę, a potem popłyniemy na Isla Tesoro. Jako niespodziankę, trzymałam w ładowni skrzynię doskonałej hiszpańskiej madery...";
			link.l1.go = "GoldenGirl_4";
		break;
		
		case "GoldenGirl_4":
			dialog.text = "Oh ho ho, Charles! Czy chcesz powiedzieć, że nie jestem odpowiednia dla tak szacownego towarzystwa? Że dziewczyna w bryczesach zrujnuje ci wieczór? Jakie to interesujące. Dobrze więc, ale nie zapomnij ubrać się jak fircyk. Małpy w eleganckich strojach potrafią poruszyć nawet serce kurtyzany. Udanej zabawy!";
			link.l1 = "Helen, czekaj! Cholera jasna...kobiety!";
			link.l1.go = "GoldenGirl_8";
		break;
		
		case "GoldenGirl_5":
			dialog.text = "Tak, zasłużyliśmy na trochę odpoczynku. Ale niech mnie diabli, jeśli wcisnę się w jakąś elegancką suknię dla tego. Jak daleko myślisz, że plotki o twojej kobiecie ubranej jak mężczyzna i marynarz sięgną?";
			link.l1 = "Ah...Nie sądzę, że to dobry pomysł. Jakby to ująć...to nie jest wydarzenie, na które mężczyźni przyprowadzają swoje żony czy szanowane damy...";
			link.l1.go = "GoldenGirl_6";
		break;
		
		case "GoldenGirl_6":
			dialog.text = "Ha! Kurwy i deprawacja! Wspaniale - więc idziesz na orgię! Czemu po prostu, do cholery, tego nie powiedziałeś? Masz szczęście, że nie jestem zazdrosną babą i nie zastrzelę cię na miejscu. Przynajmniej nie teraz.";
			link.l1 = "Helen proszę, wszystko co robię, to towarzyszę naszemu gubernatorowi, poprosił mnie o to i był bardzo uporczywy. Nie będzie żadnych choler... kurtyzan\nCzekaj, to źle zabrzmiało... Chciałem powiedzieć, będzie cholerne pieprzenie kurtyzan... o, do diabła! Po prostu oddaję mu szacunek!";
			link.l1.go = "GoldenGirl_7";
		break;
		
		case "GoldenGirl_7":
			dialog.text = "Proponuję, byś ubrał się modnie na 'oddanie szacunku', Kapitanie de Maure. To wyższe sfery i w ogóle. To czysty skandal pojawić się tam bez kołnierza i mankietów. Nawet na orgię. Baw się dobrze.";
			link.l1 = "Helen, zaczekaj! Cholera...kobiety!";
			link.l1.go = "GoldenGirl_9";
		break;
		
		case "GoldenGirl_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlExit", 15.0);
			pchar.questTemp.GoldenGirl.Angry1 = "true";
		break;
		
		case "GoldenGirl_9":
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlExit", 15.0);
			pchar.questTemp.GoldenGirl.Angry2 = "true";
		break;
		
		case "GoldenGirl_10":
			dialog.text = "Mankiety i kołnierzyk, Kapitanie. A może koronki. Słyszałam, że znów są w modzie. Ale co ja tam wiem!";
			link.l1 = "O Heleno, daj spokój!";
			link.l1.go = "GoldenGirl_11";
		break;
		
		case "GoldenGirl_11":
			DialogExit();
			NextDiag.CurrentNode = "GoldenGirl_10";
		break;
		
		case "GoldenGirl_12":
			dialog.text = "Spójrz na to! Mój drogi kapitan, wrócił z orgii!";
			link.l1 = "...";
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angry1")) link.l1.go = "GoldenGirl_13";
			else link.l1.go = "GoldenGirl_18";
		break;
		
		case "GoldenGirl_13":
			dialog.text = "Czy miejscowa szlachta nadal aprobuje swoją nową małpę? Dlaczego, mówią, że jej występ zeszłej nocy był legendarny! Hazard na statki i dziwki, wyzywanie wysoko urodzonych księciów na pojedynki? Czy mógłbyś uprzejmie wyjaśnić, co do diabła się z tobą dzieje?";
			link.l1 = "Helen, pozwól mi wyjaśnić! To nie takie proste. Cholera, przepraszam, ale nigdy nie pomyślałem, że będę musiał nocować u Madame Botot. Spałem tam tylko, tak, sam przysięgam! I tak, wygrałem fregatę w grze karcianej. Wyobraź sobie to?";
			link.l1.go = "GoldenGirl_14";
		break;
		
		case "GoldenGirl_14":
			dialog.text = "Zatem! Albo jesteś wielkim kłamcą, świętym, albo głupcem. Omówimy później dziwki i statki, które wygrałeś - teraz opowiedz mi wszystko o pojedynku i dlaczego wszyscy plotkują, że wyzwałeś na pojedynek księcia korony?";
			link.l1 = "Nie książę koronny, tylko bękart hrabiego. Jest synem bardzo wpływowego szlachcica, hrabiego de Levi Vantadur. Słuchaj, to nie ja zacząłem! To on mnie wyzwał, a teraz muszę wygrać pojedynek, nie raniąc go zbytnio, by uniknąć gniewu jego ojca.";
			link.l1.go = "GoldenGirl_15";
		break;
		
		case "GoldenGirl_15":
			dialog.text = "O, 'tylko syn hrabiego', co? Jesteś teraz poważny, Charles?! A jak mamy to zrobić? Co jeśli oszuka? Zabije cię!";
			link.l1 = "To dlatego Ekscelencja dostarczył mi szlachetnych sekundantów. Zabiorę ze sobą tylko ich - jeśli coś pójdzie nie tak, przynajmniej będę mógł udowodnić, że wszystko odbyło się zgodnie z kodeksem pojedynków i prawem. Proszę cię, abyś pilnował fregaty, kiedy mnie nie będzie.";
			link.l1.go = "GoldenGirl_16";
		break;
		
		case "GoldenGirl_16":
			dialog.text = "Upewnijmy się, że dobrze to zrozumiałam... Zniknąłeś na cały dzień i noc, a w grze w karty wygrałeś dziwkę i fregatę. A teraz masz zamiar walczyć z szlachetnym skurczybykiem, którego nie możesz zabić, podczas gdy *ja* mam tu po prostu siedzieć i czekać? Jak mam się czuć w związku z tym wszystkim?!";
			link.l1 = "Helen, posłuchaj, masz wszelkie prawo być na mnie wściekła i bardzo mi przykro, ale to po prostu...";
			link.l1.go = "GoldenGirl_17";
		break;
		
		case "GoldenGirl_17":
			dialog.text = "Wiesz co, mam już tego dość. Po prostu idź i rób swoje! Ja tylko odkurzę twoją kajutę i zrobię twoje brudne pranie! Nawet nie myśl, że jesteś bez winy. Porozmawiamy o tym, gdy to się skończy. Zajmę się twoim nowym fregatem, wielki Kapitanie de Maure, nie martw się. Och, i Kapitanie de Maure, postaraj się nie zginąć... bo planuję zabić cię sama później. Teraz wybacz mi, zamknę się w swojej kajucie i wypiję butelkę tej miłej madera, którą znalazłam w twojej kajucie.";
			link.l1 = "Helen, pozwól mi tylko wyjaśnić! Cholera... Znowu to samo!";
			link.l1.go = "GoldenGirl_23";
		break;
		
		case "GoldenGirl_18":
			dialog.text = "Słyszałam, że najnowsza paryska moda wymaga, by dżentelmeni wygrywali statki i kurtyzany w grach karcianych zamiast je kupować! Co więcej, jeśli ktoś chce zrobić dobre wrażenie, musi wyzwać ich poprzednich właścicieli na pojedynek. W co ty się tym razem wpakowałeś?!";
			link.l1 = "Helen, to nie jest takie proste. Do diabła, przepraszam, ale nigdy nie myślałem, że będę musiał spędzić noc u Madame Botot! Ostatnia noc zamieniła się w wyczerpującą i brutalną bitwę umysłów. I tak, wygrałem cholerną fregatę w karty. Wyobrażasz to sobie?";
			link.l1.go = "GoldenGirl_19";
		break;
		
		case "GoldenGirl_19":
			dialog.text = "Pięknie. Czy to znaczy, że wygrałeś również kurtyzanę? A co postawiłeś przeciwko tej fregacie, którą wygrałeś? Nie nasz statek, przecież nie mogłeś...";
			link.l1 = "Musiałem. Spójrz, teraz to nie ma znaczenia, w końcu wygrałem. Mój przeciwnik wyzwał mnie na pojedynek i oskarżył o oszustwo. Jest bękartem niezwykle wpływowego szlachcica, hrabiego de Levi Vantadur. Co oznacza, że będę musiał zrobić wszystko, by go nie zabić ani nie zranić zbyt mocno.";
			link.l1.go = "GoldenGirl_20";
		break;
		
		case "GoldenGirl_20":
			dialog.text = "Czy on zrobi to samo? Czy postradałeś zmysły, Charles? Ryzykować swój statek, ryzykować swoje życie przez jakąś inną kobietę?! Czy ona naprawdę jest tego warta? Czy ja nic dla ciebie nie znaczę?!";
			link.l1 = "Helen, nie ma powodu do zazdrości, przysięgam. To po prostu się stało. Musiałem to zrobić, a gubernator zapewnił mi szlachetnych oficerów jako sekundantów, aby upewnić się, że wszystko odbędzie się zgodnie z zasadami. Nie mogę zabrać ani Ciebie, ani naszych ludzi ze sobą. Proszę, opiekuj się fregatą, gdy mnie nie będzie.";
			link.l1.go = "GoldenGirl_21";
		break;
		
		case "GoldenGirl_21":
			dialog.text = "Po prostu świetnie! Najpierw idziesz na orgię z nieznajomymi kobietami i wracasz następnego ranka, a ja nawet cię za to nie ukarałam. Teraz mówisz mi, że prawie straciłeś nasz statek w grze karcianej, ale wygrałeś kurtyzanę! A teraz zamierzasz walczyć o jej 'honor' z jakimś szlachetnie urodzonym skurwysynem, którego nawet nie możesz zabić! Jak mam się do tego wszystkiego odnosić? Powiedz mi.";
			link.l1 = "Helen, słuchaj, masz pełne prawo być na mnie zła, ale pozwól mi wyjaśnić...";
			link.l1.go = "GoldenGirl_22";
		break;
		
		case "GoldenGirl_22":
			dialog.text = "Wiesz co, mam tego dość. Idź i walcz w swoim przeklętym pojedynku. Zajmę się twoją nową fregatą, wielki Kapitanie de Maure, nie martw się. A teraz wybacz, zamknę się w swojej kajucie i wypiję butelkę tego pysznego madery, którą znalazłam w twojej kabinie. Ale jeśli coś ci się stanie, przysięgam na Boga, że sprowadzę ogień piekielny na to miasto i zakopię ten burdel i pałac twojej ukochanej Ekscelencji!";
			link.l1 = "Helen, wszystko będzie dobrze, zaufaj mi... Czekaj, dokąd idziesz?! Cholera! Znowu to samo...";
			link.l1.go = "GoldenGirl_23";
		break;
		
		case "GoldenGirl_23":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlToFregat", 15.0);
		break;
		
		case "GoldenGirl_24":
			dialog.text = "Charles, masz coś do wyjaśnienia. Czy łaskawie powiesz mi, co do cholery się stało? Nie ustawiłam odpowiedniej warty, a chłopcy pili... jakieś łotry zaatakowały nasz statek i związały nas, gdy spaliśmy. Następnie te plugawce zaczęły pytać mnie, jak daleko się posuniesz, by mnie uratować. Na końcu zamknęli mnie w ładowni. Straciłam rachubę dni, które czekałam!";
			link.l1 = "Ten drań chciał mi odpłacić za hańbę, którą mu przyniosłam. Bałam się, że ci coś zrobi! Dzięki Bogu, że jesteś cały!";
			link.l1.go = "GoldenGirl_25";
		break;
		
		case "GoldenGirl_25":
			dialog.text = "Domyślam się, że musiałeś coś zrobić, żeby mnie odzyskać? Coś złego, prawda?";
			link.l1 = "Ważne jest tylko to, że jesteś z powrotem ze mną. Zawiodłem cię, Helen. Tak mi przykro! Mam nadzieję, że znajdziesz w sercu miejsce, by mi wybaczyć!";
			link.l1.go = "GoldenGirl_26";
		break;
		
		case "GoldenGirl_26":
			dialog.text = "Już to zrobiłam. Miałam dużo czasu, by przemyśleć, co powiedziałam... Przykro mi też, Charles. Gdybym tylko nie brała zbyt osobiście twoich interesów z tym markizem. Ustawiłabym odpowiednią straż tej nocy, byłabym na straży. Ach! Jestem tylko bezużyteczną kobietą!";
			link.l1 = "Przestań to mówić, przeszłość to przeszłość. Kocham cię i już nigdy cię nie opuszczę. Obiecuję!";
			link.l1.go = "GoldenGirl_27";
		break;
		
		case "GoldenGirl_27":
			dialog.text = "Chyba lepiej, żebym nie wiedziała, co dokładnie zrobiłeś, prawda? Dobrze, jesteśmy znowu razem i to jest najważniejsze.";
			link.l1 = "Nie mam przed tobą tajemnic. Powiem ci...";
			link.l1.go = "GoldenGirl_28";
		break;
		
		case "GoldenGirl_28":
			DialogExit();
			SetLaunchFrameFormParam("Some time has passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			npchar.dialog.currentnode = "GoldenGirl_28_1";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "GoldenGirl_28_1":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "Co za bałagan... Wiem, że nie miałeś wyboru, ale jak to wytłumaczyć Di Lu Parkesowi i jego przyjaciołom? Mam na myśli, że teraz jesteś przestępcą!";
				link.l1 = "Zdecydowałem się zapłacić tę cenę, ale naprawdę nie miałem wyboru. Nie martw się, znajdę sposób, aby to naprawić i przywrócić nasze dobre imię. Jeśli nie, to zawsze będziemy mile widziani na Isla Tesoro! Dam sobie radę, jeśli będziesz ze mną.";
			}
			else
			{
				dialog.text = "Co za historia, Charles... Wierzę, że nie miałeś wyboru w tej sprawie, ale co dalej? Czy ten Anglik naprawi wszystko, czy będzie wojna? Jesteś pewien, że nie chcesz przyjechać do Basse-Terre, aby zobaczyć, jak zakuwają tego drania w kajdany?";
				link.l1 = "Wiesz Helen, dwa tygodnie temu nigdy bym tego nie przegapił. Ale dziś mówię do diabła z nim! Już mnie nie obchodzi jego sprawiedliwa kara. Jesteśmy znów razem, to wszystko, co się liczy!";
			}
			link.l1.go = "GoldenGirl_29";
		break;
		
		case "GoldenGirl_29":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "Ty wiesz, że zawsze będę z tobą. Ha! To nie pierwszy raz, kiedy ty i ja wylądowaliśmy po szyję w sentynach. Znowu nam się uda.";
				link.l1 = "Prawda. Wypływamy, kochanie! Horyzont na nas czeka!";
			}
			else
			{
				dialog.text = "Podoba mi się twój sposób myślenia, Charles! Żadnych więcej szlachciców: Francuzów, Brytyjczyków, Hiszpanów - nieważne. Myślę, że zasłużyliśmy na wakacje!";
				link.l1 = "Zgoda. Tylko ty i ja! Żadnych więcej gubernatorów i szlacheckich bękartów!";
			}
			link.l1.go = "GoldenGirl_30";
		break;
		
		case "GoldenGirl_30":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "Tak jest, kapitanie!";
				link.l1 = "";
			}
			else
			{
				dialog.text = "Brzmi cudownie! Pójdę powiedzieć chłopakom, że czas podnieść kotwicę! A Charles...";
				link.l1 = "Wiem, Helen, wiem. Dołączę do ciebie za chwilę.";
			}
			link.l1.go = "GoldenGirl_31";
		break;
		
		case "GoldenGirl_31":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "GoldenGirl_GirlGoOnBoard", 10.0);
		break;
		
		case "GoldenGirl_32":
			dialog.text = "Charles, udało ci się! Portugalczycy opowiedzieli mi wszystko! Co za historia!";
			link.l1 = "Dzięki Bogu, że żyjesz, Helen! Nie masz pojęcia, jak bardzo się cieszę, że znów cię widzę!";
			link.l1.go = "GoldenGirl_33";
		break;
		
		case "GoldenGirl_33":
			dialog.text = "Mówiąc o tym. Obiecałeś mi coś powiedzieć, pamiętasz? Coś dużego i skomplikowanego. To twoja szansa, Kapitanie. Co się, do cholery, stało?!";
			link.l1 = "Kochałem cię, Helen. Reszta jest nieistotna.";
			link.l1.go = "GoldenGirl_34";
		break;
		
		case "GoldenGirl_34":
			dialog.text = "Aj, to było pomocne, ale... Cholera, ja też, Charles. Też cię kocham. Mój Boże, tak bardzo za tobą tęskniłam!";
			link.l1 = "Ja też. Chodź ze mną, nie opuszczę cię tej nocy, nawet jeśli niebo zacznie się walić na to nędzne miasto. Nigdy więcej cię nie opuszczę. Nigdy.";
			link.l1.go = "GoldenGirl_35";
		break;
		
		case "GoldenGirl_35":
			dialog.text = "Chyba lepiej, żebym nie wiedziała, co dokładnie zrobiłeś, prawda? Aye, jesteśmy znowu razem i to jest najważniejsze.";
			link.l1 = "Nie mam przed tobą tajemnic. Powiem ci...";
			link.l1.go = "GoldenGirl_36";
		break;
		
		case "GoldenGirl_36":
			DialogExit();
			SetLaunchFrameFormParam("Some time has passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			npchar.dialog.currentnode = "GoldenGirl_36_1";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "GoldenGirl_36_1":
			dialog.text = "Niewiarygodne! Czy właśnie powiedziałeś, że Francja i Anglia stoją na krawędzi wojny z powodu mnie?";
			link.l1 = "Nie, Helen. To dlatego, że popełniłem bardzo poważny błąd w osądzie. Ale musiałem cię sprowadzić z powrotem i wszystko naprawić.";
			link.l1.go = "GoldenGirl_37";
		break;
		
		case "GoldenGirl_37":
			dialog.text = "To wszystko jest bardzo wzruszające i romantyczne, jestem nawet gotowa zapomnieć, jak to się wszystko zaczęło. Prawie gotowa. Ale poważnie, aresztowali cię, bo Portugalczycy podali złą nazwę przeklętej brygantyny?";
			link.l1 = "Wprost przeciwnie, dał mi prawdziwego! Chciałabym wiedzieć, jak mu się to udało i dlaczego. A tak przy okazji, gdzie jest sam człowiek?!";
			link.l1.go = "GoldenGirl_38";
		break;
		
		case "GoldenGirl_38":
			dialog.text = "Odszedł. Zaraz po tym, jak mnie tu przywiózł. Nie chciałam korzystać z 'gościnności' kurtyzany, którą wygrałeś, więc poprosiłam Bartholomew, by wynajął mi pokój. Zapłacił za niego i zniknął, nie mówiąc ani słowa. A właściwie, nie, zostawił jednak list dla ciebie!";
			link.l1 = "List? Od Bartłomieja Portugalczyka? To coś nowego. Nie podoba mi się, dokąd to zmierza...";
			link.l1.go = "GoldenGirl_39";
		break;
		
		case "GoldenGirl_39":
			dialog.text = "Dobrze, zostawię cię tutaj, abyś to przeczytał, a ja pójdę przywitać się z chłopakami. Muszą się martwić. Nigdy bym nie pomyślała, że będę tęsknić za tymi ponurymi psimi twarzami! W międzyczasie postaraj się nie wpaść w kolejną katastrofę!";
			link.l1 = "Cholera... Wciąż nie mogę uwierzyć, że cię przyprowadziłam z powrotem!";
			link.l1.go = "GoldenGirl_40";
		break;
		
		case "GoldenGirl_40":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_SPGirlReturn", 10.0);
		break;
		
		// Jason Долго и счастливо
		case "LongHappy":
			RemoveItems(pchar, "potionwine", 2);
			dialog.text = "Biały piasek, przejrzysta zielona woda, ty, ja i dobre wino - Charles, to takie romantyczne! Powinniśmy częściej spacerować razem, dobrze?";
			link.l1 = "Cieszę się, że ci się podoba. Myślę, że powinniśmy teraz znaleźć na to więcej czasu.";
			link.l1.go = "LongHappy_1";
		break;
		
		case "LongHappy_1":
			dialog.text = "Charles, co ty wyprawiasz i dlaczego klęczysz? To takie nagłe...";
			link.l1 = "Helen, kocham cię. I pragnę żyć z tobą każdego dnia, który mi jest dany z góry. Dlatego tutaj i teraz, wobec tego morza i nieba, proszę cię - Helen Beatrice Sharp - byś dała mi zaszczyt stać u mego boku przed ludźmi i Bogiem aż do śmierci nas rozłączy. Ja, Charles de Maure, Chevalier de Monper, pytam cię - czy zostaniesz moją żoną?";
			link.l1.go = "LongHappy_2";
		break;
		
		case "LongHappy_2":
			if (pchar.location == "Shore_ship1")
			{
				dialog.text = "Wiesz, nigdy nie lubiłam tych formalności, ale jestem z tobą aż po kres świata. A co do twojego pytania, odpowiedź brzmi... oj, przepraszam, rozlałam!";
				link.l1 = "Nieważne, to tylko wino, a nigdy nie kochałam tej koszuli...";
				link.l1.go = "LongHappy_3";
			}
			else
			{
				dialog.text = "Charles, oczywiście, że tak! Tak, tak i jeszcze raz tak!!! Ale mam nadzieję, że nie planujesz przenieść nas do jakiegoś zakurzonego rodzinnego zamku, by uprawiać rzepę aż do końca naszych dni?";
				link.l1 = "Cóż, mamy rodzinny zamek, ale nie jest zakurzony i nie będziemy tam zostawać. Nasze życie to wolność i horyzont na wyciągnięcie ręki!";
				link.l1.go = "LongHappy_4";
			}
		break;
		
		case "LongHappy_3":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			DoQuestCheckDelay("Helena_LoveSex", 1.0);
			npchar.dialog.currentnode = "LongHappy_5";
			LAi_SetStayType(npchar);
		break;
		
		case "LongHappy_4":
			dialog.text = "Więc toast za ciebie, mój kapitanie, mój mężu, i za nasze wesele!";
			link.l1 = "Za ciebie, moja miłości! I za naszą przyszłość razem, tyle przed nami!";
			link.l1.go = "LongHappy_6";
		break;
		
		case "LongHappy_5":
			dialog.text = "W takim razie toast za ciebie, mój kapitanie, mój mężu, i za moje wesele!";
			link.l1 = "Za ciebie, moja miłości! I za naszą wspólną przyszłość, tyle nas jeszcze czeka!";
			link.l1.go = "LongHappy_6";
		break;
		
		case "LongHappy_6":
			DialogExit();
			chrDisableReloadToLocation = false;
			npchar.dialog.currentnode = "Helena_officer";
			LongHappy_MarryToSenPierre();
		break;
		
		case "LongHappy_7":
			dialog.text = "A więc, opat Benoit powrócił i jest gotów nas poślubić. Ale żebyś wiedział, nie ubiorę sukni nawet na taką okazję! Myślisz, że noszenie przeze mnie spodni wywoła sensację?";
			link.l1 = "Helen,   kocham cię w każdym stroju, a oni się z tym pogodzą. Najpierw chciałem się z tobą skonsultować w sprawie gości i ceremonii.";
			link.l1.go = "LongHappy_8";
		break;
		
		case "LongHappy_8":
			dialog.text = "Aj, jest jeden problem - większość naszych najlepszych przyjaciół, z którymi chętnie podzielilibyśmy się tym dniem, nie będzie wpuszczona do miasta, nie mówiąc już o kościele. Dlatego - weźmy ślub tutaj z wszystkimi ważnymi osobami, jak się tego oczekuje, a potem popłyniemy na Isla Tessoro i zrobimy prawdziwą uroczystość z naszymi prawdziwymi przyjaciółmi, co o tym sądzisz?";
			link.l1 = "Brzmi dobrze dla mnie! Porozmawiam z opatem Benoit, ale musimy wysłać zaproszenia i więcej...";
			link.l1.go = "LongHappy_9";
		break;
		
		case "LongHappy_9":
			dialog.text = "Spokojnie, kapitanie. Twoja przyszła żona pomoże dźwigać część ciężaru! Wszystko załatwię na Isla Tesoro i napiszę do naszych przyjaciół, tylko powiedz mi: jak duży ślub chcesz?";
			link.l1 = "  Tylko ty, ja i nasi najbliżsi przyjaciele.  Po całym tym oficjalnym blichtrze tutaj na Martynice będziemy pragnąć szczerej intymności.";
			link.l1.go = "LongHappy_10";
			link.l2 = "Każdy musi zapamiętać ten dzień! Zawołaj wszystkich! Nikt nie zostanie pominięty!";
			link.l2.go = "LongHappy_11";
		break;
		
		case "LongHappy_10":
			pchar.questTemp.LongHappy.SmallMarry = "true";
			dialog.text = "Przytulnie i przyjaźnie - czytasz mi w myślach! Będziemy musieli odwiedzić Sharptown, a ja wszystko przygotuję. Myślę, że pięćdziesiąt beczek rumu i dwa tuziny beczek wina wystarczy. Również, na jedzenie i rozrywkę będziemy potrzebować trzysta tysięcy sztuk ośmiu.";
			link.l1 = "Przypomnij mi - dlaczego to ty nie zarządzasz finansami statku? Ja to wszystko załatwię. Tylko krótka wizyta u opata, a potem wyruszamy do Sharptown.";
			link.l1.go = "LongHappy_12";
		break;
		
		case "LongHappy_11":
			pchar.questTemp.LongHappy.BigMarry = "true";
			dialog.text = "Więc, chcesz urządzić przyjęcie jak prawdziwe wilki morskie? Dobrze! Będziemy musieli odwiedzić Sharptown, a ja przygotuję wszystko. Musimy się porządnie zaopatrzyć - myślę, że sto beczek rumu i pięćdziesiąt beczek wina wystarczy. A inne wydatki wyniosą co najmniej pięćset tysięcy sztuk ośmiu.";
			link.l1 = "Czy zapraszasz całą Bractwo Wybrzeża? O do diabła, zróbmy to! Zdobędę zapasy. Tylko szybka wizyta u opata i wyruszamy do Sharptown.";
			link.l1.go = "LongHappy_12";
		break;
		
		case "LongHappy_12":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "10");
			AddQuestUserData("LongHappy", "sName", "Helen");
			LongHappy_MarryGoToBenua();
		break;
		
		case "LongHappy_13":
			dialog.text = "Charles, zajmę się załadunkiem, a potem rozdam zaproszenia baronowi i dogadam się z karczmarzem. Nie powinno to zająć zbyt długo.";
			link.l1 = "Nie martw się, moja droga, zajmę się czymś dochodowym... Albo po prostu zdrzemnę się na piasku. Nie sądziłem, że łatwiej będzie szturmować Tortugę niż zaplanować własny ślub, na miłość boską.";
			link.l1.go = "LongHappy_14";
		break;
		
		case "LongHappy_14":
			DialogExit();
			SetLaunchFrameFormParam("Several hours have passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 4, 0);
			LongHappy_IslaTesoroRemoveGoods();
			npchar.dialog.currentnode = "LongHappy_15";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "LongHappy_15":
			dialog.text = "Czy udało Ci się odpocząć, Charles? Mam dobre wieści i złe wieści. Złe wieści są takie, że miejscowi mieli tyle zabawy w zeszłym tygodniu, że przypadkowo spalili na cholery 'Starego Dzięcioła'! Dobre wieści są takie, że baron obiecał, że zostanie odbudowany większy i lepszy, zanim wrócimy. Zaaranżowałem wszystko, więc możemy wyruszać w rejs.";
			link.l1 = "Mam nadzieję, że nasze wesele nie zostawi podobnej sterty popiołów w mieście, gdy odejdziemy. To cholernie szkoda, bardzo lubiłem 'Starego Dzięcioła' - przytulny, intymny, z delikatnym zapachem wymiocin i pakunku! No cóż, kochanie, masz rację - powinniśmy ruszać.";
			link.l1.go = "LongHappy_16";
		break;
		
		case "LongHappy_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "12");
			pchar.questTemp.LongHappy = "marry_wait";
			pchar.questTemp.LongHappy.DrinkReady = "true";
		break;
		
		case "LongHappy_17":
			dialog.text = "Jan jest już w mieście z Gladys, wyobrażasz sobie? Nie myślałam, że kiedykolwiek przyjdą na mój ślub! O słodki Jezu! Nawet kiedy byliśmy w tym okropnym indyjskim mieście-świątyni, nie byłam tak przerażona jak teraz!";
			link.l1 = "Wszystko w porządku, kochanie, wszystko w porządku. Martwię się również - nerwy to normalka. Skoro goście już przyszli, powinnam iść do Ojca Benoit i dowiedzieć się, kiedy rozpocznie się nabożeństwo.";
			link.l1.go = "LongHappy_18";
		break;
		
		case "LongHappy_18":
			dialog.text = "To będzie cholernie długi i trudny dzień... Idę zobaczyć się z Janem i Gladys.";
			link.l1 = "Cieszę się, że mogli przyjść. Stary Svensson kocha cię jak własną córkę, a pani McArthur jeszcze bardziej. Dobrze, że są tu dzisiaj. Idź i nie martw się - wszystko będzie dobrze.";
			link.l1.go = "LongHappy_19";
		break;
		
		case "LongHappy_19":
			DialogExit();
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0);
			AddQuestRecord("LongHappy", "14");
			AddQuestUserData("LongHappy", "sName", "Helen");
		break;
		
		case "LongHappy_20":
			dialog.text = "Tak.";
			link.l1 = "";
			link.l1.go = "LongHappy_21";
		break;
		
		case "LongHappy_21":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_27";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_22":
			dialog.text = "Tak.";
			link.l1 = "";
			link.l1.go = "LongHappy_23";
		break;
		
		case "LongHappy_23":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_29";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_24":
			dialog.text = "Tak.";
			link.l1 = "";
			link.l1.go = "LongHappy_25";
		break;
		
		case "LongHappy_25":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_31";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_26":
			dialog.text = "";
			link.l1 = "Ja, Charles Henry de Maure, kawaler de Monper, biorę ciebie, Heleno Beatrice Sharp, za żonę, aby mieć i trzymać, od tego dnia naprzód, na lepsze i na gorsze, na bogatsze i na biedniejsze, w chorobie i w zdrowiu, aż do śmierci nas rozłączy. Zgodnie z Świętym Prawem Bożym, w obecności Boga, składam tę przysięgę.";
			link.l1.go = "LongHappy_27";
		break;
		
		case "LongHappy_27":
			dialog.text = "Ja, Helen Beatrice Sharp, biorę ciebie, Charlesie Henry de Maure, za męża, aby mieć i trzymać, od tego dnia naprzód, na lepsze i na gorsze, w bogactwie i w biedzie, w chorobie i w zdrowiu, aż śmierć nas rozłączy. Zgodnie z świętym prawem Bożym, w obecności Boga, składam tę przysięgę.";
			link.l1 = "";
			link.l1.go = "LongHappy_28";
		break;
		
		case "LongHappy_28":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_33";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_29":
			dialog.text = "Amen.";
			link.l1 = "";
			link.l1.go = "LongHappy_30";
		break;
		
		case "LongHappy_30":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_35";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_31":
			dialog.text = "Helen Beatrice de Maure, Madame de Monper - oh, jakże to brzmi pięknie, mój najdroższy mężu!";
			link.l1 = "Nie słyszałam nic lepszego, moja żono!";
			link.l1.go = "LongHappy_32";
		break;
		
		case "LongHappy_32":
			dialog.text = "Wiesz - myślałam, że to niczego nie zmieni, i prawdopodobnie nie zmieniło - kochałam cię już wcześniej i chciałam spędzić z tobą resztę dni, ale ten dzień, ta święta ceremonia... Jestem naprawdę szczęśliwa, Charles! Szczęśliwa jak nigdy przedtem, i spójrz na Gladys i Jana - oni promienieją! Wokół jest tyle szczęśliwych twarzy! A tak przy okazji - nadszedł czas, byś przeszedł się po gościach i przyjął ich gratulacje. Wróć, gdy skończysz, nie zapomnij - czekają na nas w Sharptown.";
			link.l1 = "Zrobię to od razu, kochanie. Jeden pocałunek zanim pójdę!";
			link.l1.go = "LongHappy_33";
		break;
		
		case "LongHappy_33":
			DialogExit();
			LongHappy_MarryKiss();
		break;
		
		case "LongHappy_34":
			dialog.text = "Witaj, mężu, czy już rozmawiałeś z gośćmi?";
			link.l1 = "Jeszcze nie, bądź cierpliwa, żono, wkrótce wrócę.";
			link.l1.go = "LongHappy_34_1";
			link.l2 = "Tak, nigdy wcześniej nie słyszałam tylu gratulacji naraz. I wiesz co - myślę, że większość z nich mówiła szczerze!";
			link.l2.go = "LongHappy_35";
		break;
		
		case "LongHappy_34_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_34";
		break;
		
		case "LongHappy_35":
			dialog.text = "Tak, ci szlachcice są zaskakująco szczerzy - przyznam, że spodziewałam się więcej fałszu i hipokryzji. A może po prostu jestem tak szczęśliwa, że niczego nie zauważam. Ale przecież nasi przyjaciele czekają na nas w Sharptown! Kiedy wypływamy?";
			link.l1 = "Teraz. Polecimy na skrzydłach orłów prosto na przyjacielską ucztę. Mam nadzieję, moja żono, że nie masz nic przeciwko spędzeniu tej nocy w naszej kajucie?";
			link.l1.go = "LongHappy_36";
		break;
		
		case "LongHappy_36":
			dialog.text = "O tak, mój mężu, jesteś taki romantyczny! I nie drgaj tak, teraz mam prawo całować cię publicznie... Aye, możemy już iść!";
			link.l1 = "Nawigatorze, wytycz kurs na Sharptown i nie przeszkadzaj nam z żadnego powodu! Nie obchodzi mnie, czy flota duchów się na nas zbliża!";
			link.l1.go = "LongHappy_37";
		break;
		
		case "LongHappy_37":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_38";
			LongHappy_MarryComplete();
		break;
		
		case "LongHappy_38":
			dialog.text = "O mój drogi mężu, jestem taka szczęśliwa! Dziś jest wspaniały dzień...";
			link.l1 = "";
			link.l1.go = "LongHappy_38_1";
		break;
		
		case "LongHappy_38_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_38";
		break;
		
		case "LongHappy_39":
			dialog.text = "Chodź, Charles. Ten kłamca będzie martwy, zanim dotknie ziemi!";
			link.l1 = "";
			link.l1.go = "LongHappy_40";
		break;
		
		case "LongHappy_40":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angerran") && CharacterIsAlive("Angerran")) // fix 02-04-20
			{
				sld = characterFromId("Angerran");
				sld.dialog.currentnode = "Shivo_6";
			}
			else 
			{
				sld = characterFromId("LH_Dussak");
				sld.dialog.currentnode = "Dussak_5";
			}
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "LongHappy_41":
			dialog.text = "Ze mną wszystko w porządku, Charles, jest dobrze. Jak się ma Nathan?";
			link.l1 = "Tyle krwi... Dannie, czy on oddycha? Widzę, że oddycha!";
			link.l1.go = "LongHappy_42";
		break;
		
		case "LongHappy_42":
			DialogExit();
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_9";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "LongHappy_43":
			dialog.text = "Szybciej, drogi, nie trać czasu!";
			link.l1 = "";
			link.l1.go = "LongHappy_43_1";
		break;
		
		case "LongHappy_43_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_43";
		break;
		
		case "LongHappy_44":
			dialog.text = "Charles, czy wszystko w porządku? Co za rzeźnia! Przepraszam, utknęliśmy na górze, było tam tuzin tych drani, więc musiałam najpierw się nimi zająć!";
			link.l1 = "To w porządku, poradziłam sobie. Cieszę się, że mogłam wreszcie zakończyć tę historię z Jacques'em... w końcu. Dostał, na co zasłużył.";
			link.l1.go = "LongHappy_45";
		break;
		
		case "LongHappy_45":
			dialog.text = "W porządku, mój drogi, zakończmy tutaj i wracajmy. Nie mogę przestać myśleć o Nathanie, jak on się ma? Osłonił mnie przed tą kulą!";
			link.l1 = "Masz rację, kochanie, ja też się martwię. Idź, jestem tuż za tobą.";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner")) link.l1.go = "LongHappy_46";
			else link.l1.go = "LongHappy_48";
		break;
		
		case "LongHappy_46":
			dialog.text = "Znaleźliśmy Marcusa! Był w ładowni, związany i nieprzytomny.";
			link.l1 = "On żyje?";
			link.l1.go = "LongHappy_47";
		break;
		
		case "LongHappy_47":
			dialog.text = "Nie martw się, kochanie, Baron Tyrex będzie żył dłużej niż my. Właśnie się obudził i już szumi, ciągle woła o rum, szablę i mostek - w tej kolejności.";
			link.l1 = "To nasz stary Marcus! Pozwólmy mu chwilę odpocząć, podczas gdy my tu skończymy, a potem wrócimy na brzeg.";
			link.l1.go = "LongHappy_48";
		break;
		
		case "LongHappy_48":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LongHappy_BarbExit", -1);
		break;
		
		case "LongHappy_49":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") && CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "Tak mi przykro, kochanie... Najpierw nasz wierny przyjaciel Tichingitu, teraz Gino... Barbazon powinien był zostać zabity tuzin razy za wszystko, co zrobił!";
				link.l1 = "Niestety, zrobiłam to tylko raz. Czuję się też źle... Ale wygraliśmy, i on już nikogo nie skrzywdzi.";
				link.l1.go = "LongHappy_50";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
				{
					dialog.text = "Czuję się tak okropnie z powodu Gino, Charles! Kiedy się dowiedziałam, nie mogłam w to uwierzyć! Jak się masz, kochanie?";
					link.l1 = "Też nie mogę w to uwierzyć... co za sposób, by odejść... Nie wyobrażałam sobie, że ten dzień tak się potoczy.";
				}
				else
				{
					dialog.text = "Ciekaw jestem, czy przyszli historycy napiszą o wielkiej bitwie w Zatoce Kaperskiej? Dzień, kiedy baronowie Bractwa Wybrzeża spotkali się w otwartej bitwie - założę się, że hiszpańska Costa Garda ociera łzy wdzięczności! Ale, znów wygraliśmy! Nasi przyjaciele żyją, a nasi wrogowie nie - wspaniały prezent ślubny!";
					link.l1 = "Tak, taka uroczystość, ale daliśmy radę, mój aniele. Daliśmy radę.";
				}
				link.l1.go = "LongHappy_50";
			}
		break;
		
		case "LongHappy_50":
			dialog.text = "Chodź, Dannie znalazł nam dom tutaj, na obrzeżach miasta, nie chcę teraz wracać na statek, dopóki nie zostanie posprzątany. Usiądziemy i wypijemy za tych, którzy nie dotrwali.";
			link.l1 = "Tak, Helen, chodźmy.";
			link.l1.go = "LongHappy_51";
		break;
		
		case "LongHappy_51":
			DialogExit();
			LongHappy_LogBook();
			DoQuestCheckDelay("LongHappy_MarryFinalizing", 0.5);
		break;
		
		case "LongHappy_52":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "Czuję się tak źle z powodu Gino, Charles! Kiedy się dowiedziałam, nie mogłam w to uwierzyć! Jak się masz?";
				link.l1 = "Też nie mogę w to uwierzyć... co za sposób na odejście... Nie wyobrażałam sobie, że ten dzień tak się potoczy.";
			}
			else
			{
				dialog.text = "Czy widziałeś Jastrzębia? Dannie wypuścił mnie, gdy Gino powiedział 'niebezpieczeństwo minęło'. Cieszę się, że wszystko jest w porządku. Nasi przyjaciele żyją, a nasi wrogowie są martwi - wspaniały prezent ślubny!";
				link.l1 = "Ja też, kochanie. I wygraliśmy. Barbazon nie żyje, baronowie zbierają resztki swoich załóg. Walka się skończyła.";
			}
			link.l1.go = "LongHappy_53";
		break;
		
		case "LongHappy_53":
			dialog.text = "Charles, widzę, że ledwo stoisz, ale odwiedziłam tawernę i nie uwierzysz, co usłyszałam od barmana.";
			link.l1 = "Aj, słyszałam to od Jana, on tam też był. Wydaje mi się, że nasz drogi Indianin wyruszył na ścieżkę wojenną. Chodźmy do Zatoki Sabo-Matila, kilka osób widziało, jak odchodził w tamtym kierunku.";
			link.l1.go = "LongHappy_54";
		break;
		
		case "LongHappy_54":
			DialogExit();
			LongHappy_LogBook();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.longhappy_shoregirl.win_condition.l1 = "location";
			pchar.quest.longhappy_shoregirl.win_condition.l1.location = "Shore_ship1";
			pchar.quest.longhappy_shoregirl.function = "LongHappy_SetShoreGirl";
		break;
		
		case "LongHappy_55":
			dialog.text = "Boże na wysokości! To jest duch, Tichingitu! Uf, śmieję się tutaj do rozpuku! Czemu my, Europejczycy, nie przyjmujemy takiego zwyczaju też?! Och Charles, prawie zasypiasz na stojąco! Chodź, Dannie znalazła dla nas dom tutaj na obrzeżach - musisz odpocząć.";
			link.l1 = " Prowadź ... Myślę, że już kiedyś zasnąłem na tej plaży.";
			link.l1.go = "LongHappy_56";
		break;
		
		case "LongHappy_56":
			DialogExit();
			DoQuestCheckDelay("LongHappy_MarryFinalizing", 0.5);
		break;
		
		case "tonzag_jailed":
			dialog.text = "... W porządku.";
			link.l1 = "Dobrze to słyszeć.";
			link.l1.go = "exit";
			link.l2 = "Naprawdę?";
			link.l2.go = "tonzag_jailed_1";
			locCameraFromToPos(-15.50, 2.28, -1.23, true, -27.00, -10.60, -22.70);
		break;
		
		case "tonzag_jailed_1":
			dialog.text = "Tak.";
			link.l1 = "Dobrze to słyszeć.";
			link.l1.go = "exit";
			link.l2 = "Chodź, widzę, że coś cię trapi!";
			link.l2.go = "tonzag_jailed_2";
		break;
		
		case "tonzag_jailed_2":
			dialog.text = "Jestem całkowicie w porządku, odpuść sobie!\nCharles, idź do diabła! Nienawidzę lochów, nienawidzę ciebie i tej przeklętej wyspy! Wyciągnij mnie stąd natychmiast!\nPrzepraszam... naprawdę nie lubię lochów, nie dotykaj mnie!";
			link.l1 = "Przepraszam. Wszyscy czegoś się boimy.";
			link.l1.go = "exit";
		break;
		
		case "tonzag_aftershot":
			dialog.text = "AAAA! Wypuśćcie nas stąd! Charles, zrób coś!";
			link.l1 = "Ogarnij się!";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Helena_officer";
			AddDialogExitQuestFunction("Tonzag_TichingituAfterShot");
		break;
		
		case "tonzag_after_boarding":
			dialog.text = "Mój kapitanie, wróg przebił kadłub na drugim pokładzie i wysadził desant. Bitwy szaleją na całym statku, a większość załóg dział jest wyłączona z walki! Musimy ratować naszą załogę i Hercule'a! Pójdziesz, czy ja mam iść?";
			link.l1 = "    Tym razem, pójdę sam, Helen! Przejmij dowodzenie nad statkiem i zabierz nas stąd!";
			link.l1.go = "tonzag_after_boarding_1";
			DelLandQuestMark(npchar);
		break;
		
		case "tonzag_after_boarding_1":
			dialog.text = "Tak jest, mój kapitanie. Nie zawiodę cię, a ty proszę, bądź ostrożny!";
			link.l1 = "Wiem, Helen. Ty też bądź ostrożna!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_GoToGunDeck");
		break;
		
		case "tonzag_after_victory":
			dialog.text = "Zwycięstwo, mój kapitanie! Oddział desantowy został wyeliminowany, wróg wybrał odwrót i skierował się na południe. Stan statku jest zadowalający. Żywa załoga: "+GetCrewQuantity(pchar)+" ludzie. Raport zakończony!";
			link.l1 = "Dziękuję, Helen, a co...";
			link.l1.go = "tonzag_after_victory_1";
		break;
		
		case "tonzag_after_victory_1":
			dialog.text = "Rozbierz się, zwycięzco, twoją nagrodą jest robić ze mną, co tylko chcesz!";
			link.l1 = "Yyy...";
			link.l1.go = "tonzag_after_victory_2";
			link.l2 = "Chodźmy!";
			link.l2.go = "tonzag_after_victory_2";
		break;
		
		case "tonzag_after_victory_2":
			dialog.text = "O, cześć, Hercule. Przepraszam, złapałeś nas w nieodpowiednim momencie! Ale cholera, cieszę się, że widzę cię żywego i pokrytego krwią kogoś innego - naturalny stan dla ciebie, co?";
			link.l1 = " ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HelenBoardingDialog");
		break;
		
		case "tonzag_after_victory_3":
			dialog.text = "";
			link.l1 = "Cóż, Helen, jesteś niesamowita!";
			link.l1.go = "tonzag_after_victory_4";
		break;
		
		case "tonzag_after_victory_4":
			dialog.text = "Jeszcze nawet nie zaczęłam, mój Kapitanie. Świętujemy?";
			link.l1 = "Nie potrzebuję przekonywania!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ShowFrame");
		break;
		
		case "tonzag_dead":
			dialog.text = "Nie patrz, nie patrz, nie patrz... To jest jakiś inny świat, mój Kapitanie! Tak nie może być!";
			link.l1 = "Myślę, że to teraz nasz świat, kochany. I masz rację, nie zwlekajmy...";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Helena_officer";
		break;
		
		// Jason Исла Мона
		case "IslaMona":
			dialog.text = "Obawiam się, że ta pandemia daje się we znaki twoim dziewczętom, Rodrigo. Zajmij je szydełkowaniem czy czymś takim!";
			link.l1 = "Ta rozmowa wyraźnie donikąd nie prowadzi. Ustaliliśmy, że jutro pójdziemy do kościoła. Pomodlić się... oczywiście.";
			link.l1.go = "IslaMona_1";
		break;
		
		case "IslaMona_1":
			DialogExit();
			LAi_SetOfficerType(npchar);
			npchar.dialog.currentnode = "Helena_officer";
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_26";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_2":
			dialog.text = "Jestem z ciebie dumna, mój ukochany!";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
		break;
		
		case "IslaMona_3":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			sld = characterFromId("Himenes_companion_1");
			sld.dialog.currentnode = "island_man_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_4":
			dialog.text = "Cóż, Charles...";
			link.l1 = "Co znów masz na myśli, Helen?";
			link.l1.go = "IslaMona_5";
		break;
		
		case "IslaMona_5":
			dialog.text = "Fakt, że najbardziej skandaliczna para na Karaibach posiada aż dwie wyspy! Moje pirackie schronienie na Isla Tesoro i twoja obiecana ziemia - jak myślisz, jak długo wytrzymają, gdy cywilizacja w końcu przyjdzie na Indie Zachodnie?";
			link.l1 = "Dość długo, by starczyło nam na całe życie, kochanie. A potem? Nie możemy kontrolować, co się wtedy stanie. Inni opowiedzą naszą historię. Najważniejsze jest to, że ty i ja jesteśmy tu i teraz, razem i szczęśliwi.";
			link.l1.go = "IslaMona_6";
		break;
		
		case "IslaMona_6":
			dialog.text = "Mówiąc o szczęściu... Zaraz idę na górę: muszę zapalić świece, pościelić łóżko, może napisać coś w moim dzienniku...";
			link.l1 = "Zostanę tu jeszcze chwilę, a potem przyjdę, by pomóc ci 'pościelić łóżko'.";
			link.l1.go = "IslaMona_7";
		break;
		
		case "IslaMona_7":
			dialog.text = "Nie zwlekaj za długo...";
			link.l1 = "";
			link.l1.go = "IslaMona_8";
		break;
		
		case "IslaMona_8":
			DialogExit();
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			DoQuestFunctionDelay("IslaMona_ChurchReloadToRoom", 0.5);
			ChangeCharacterAddressGroup(npchar, "IslaMona_TwoFloorRoom", "goto", "goto4");
			DoQuestCheckDelay("Helena_LoveSex", 2.5);
			NextDiag.CurrentNode = "sex_after";
			pchar.questTemp.IslaMona.Doorlock = "true";
		break;
		
		case "drinking_refuse":
			dialog.text = "Czy naprawdę jesteś aż tak zajęty? Szkoda, ale rozumiem. Znajdę sobie coś innego do zajęcia.";
			link.l1 = "";
			link.l1.go = "exit";
			NextDiag.TempNode = "Helena_wait";
			
			pchar.questTemp.HelenDrinking.Result = "no_visit";
			CloseQuestHeader("HelenDrinking");
		break;
		
		case "drinking_accept":
			dialog.text = "Miło, że pamiętasz. Chciałam ci powiedzieć, że jestem bardzo wdzięczna. Nie codziennie ktoś cię ratuje przed... wiesz czym. Chodźmy się napić. Ja stawiam.";
			link.l1 = "Helen... Co powie Gladys?";
			link.l1.go = "drinking_accept_1";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToHouse");
		break;
		
		case "drinking_accept_1":
			dialog.text = "Bardzo śmieszne, Charles. Chodź, i nie denerwuj mnie.";
			link.l1 = "Czy to randka?";
			link.l1.go = "drinking_accept_1_1";
			link.l2 = "Już idę, nie trzeba się irytować.";
			link.l2.go = "drinking_accept_1_2";
		break;
		
		case "drinking_accept_1_1":
			dialog.text = "Ha-ha! Chciałbyś! Musiałabym się całkowicie upić!";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "drinking_accept_1_2":
			dialog.text = "To lepiej.";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "drinking_in_tavern":
			dialog.text = "";
			link.l1 = "... miała wiele zalet, ale nie umiała trzymać alkoholu. Tak się poznaliśmy.";
			link.l1.go = "drinking_in_tavern_1";
			link.l2 = "... mój ojciec nalegał na służbę wojskową. Uległem i pojechałem do Paryża z listem polecającym. Ale nigdy nie dotarłem do wyznaczonego adresu i zostałem artystą.";
			link.l2.go = "drinking_in_tavern_2";
		break;
				
		case "drinking_in_tavern_1":
			dialog.text = "Ach, teraz rozumiem, o jakich cnotach mówisz. Jak miała na imię?";
			link.l1 = "Lulu.";
			link.l1.go = "drinking_in_tavern_1_1";
		break;
		
		case "drinking_in_tavern_1_1":
			dialog.text = "Lulu... Tymi opowieściami kompletnie zepsułaś mi Paryż. Myślałam, że to miasto wielkiego życia, ale brzmi tylko jak wielki elegancki burdel.";
			link.l1 = "Czy potępiasz burdele?";
			link.l1.go = "drinking_in_tavern_1_2";
		break;
		
		case "drinking_in_tavern_1_2":
			dialog.text = "Tak, kapitanie, i nie rozumiem mężczyzn, którzy je odwiedzają.";
			link.l1 = "(wpatruj się w kubek)";
			link.l1.go = "drinking_in_tavern_1_4";
			link.l2 = "(mam straszny kaszel)";
			link.l2.go = "drinking_in_tavern_1_4";
			link.l3 = "Uh... co kto lubi... chyba?";
			link.l3.go = "drinking_in_tavern_1_4";
		break;
		
		case "drinking_in_tavern_1_4":
			dialog.text = "(śmiech) Ha! Powinieneś był zobaczyć swoją minę! Przestraszony? Wznieśmy kolejny toast! Za Paryż!";
			link.l1 = "Do Paryża!";
			link.l1.go = "drinking_in_tavern_3";
		break;
		
		case "drinking_in_tavern_2":
			dialog.text = "„(śmieje się) Ty-ty?! Artysta? Czyli piękno i duma angielskiej floty, gwałciciel i po prostu sukinsyn Donovan, zginął z rąk paryskiego artysty? Ach, szkoda, że nie miałeś na sobie nieskazitelnego żabotu podczas abordażu i nie obiłeś tej kanalii laską!”";
			link.l1 = "Tak, bardzo niefortunnie. Żabot akurat był w praniu tego dnia.";
			link.l1.go = "drinking_in_tavern_2_1";
		break;
		
		case "drinking_in_tavern_2_1":
			dialog.text = "„(śmieje się) No cóż, dziękuję, Charles. Nie wiem, jak reszta dzisiejszego wieczoru się potoczy, ale już jest świetnie. Może nawet pozwolę ci namalować mój portret. Ale pamiętaj, nie w tym samym stylu, w jakim malowałeś swoje paryskie dziewczyny!”";
			link.l1 = "Ha! To jeśli zgodzę się cię namalować.";
			link.l1.go = "drinking_in_tavern_3";
		break;
		
		case "drinking_in_tavern_3":
			dialog.text = "Przepraszam, mój kapitanie, słuchając o twoich przygodach i życiu szlachetnych... kurtyzan obu płci. Rekin mnie pożre, nigdy nie uwierzę, że nie mogłeś znaleźć czegoś bardziej wartościowego do zrobienia z twoim czasem! Nawet nie waż się mówić mi, że wszystko, co robiłeś, to mazałeś płótna i trwoniłeś pieniądze tatusia. Nie przetrwałbyś z nami dnia, gdyby to była prawda.";
			link.l1 = "Miałam... inne zajęcia.";
			link.l1.go = "drinking_in_tavern_" + pchar.HeroParam.HeroType;
		break;
		
		case "drinking_in_tavern_herotype_3":
			dialog.text = "";
			link.l1 = "Połączyłem życie na dworze z służbą wojskową, ale nie... hehe, nie całkiem tak, jak chciał mój ojciec, oczywiście. Kilka ucieczek przez okno i jedna bójka - i zaprzyjaźniłem się ze strażnikami. I naturalnie nauczyłem się wielu rzeczy, zahartowałem ciało. Starsi towarzysze nauczyli mnie przyjmować uderzenia, nosić zbroję, władać mieczem i odpowiednio się relaksować. Ostatnia część szczególnie mi odpowiadała, oczywiście. Nie uwierzysz, ale nie każdy może machać mieczem od rana do południa, a potem pić od południa do następnego poranka.";
			link.l1.go = "drinking_in_tavern_4";
		break;
		
		case "drinking_in_tavern_herotype_1":
			dialog.text = " ";
			link.l1 = " Myślisz, że łatwo było w stolicy dla szlachcica z kiepską reputacją i pustym portfelem, tracąc list polecający od tatusia już pierwszego dnia? Musiałem się postawić i nie pozwolić nikomu się ze mnie naśmiewać. Lekcje szermierki w domu nie poszły w zapomnienie, a na każdą krzywą spojrzenie odpowiadałem pojedynkiem. W końcu naprawdę się w to wkręciłem. Mimo to nikogo nie zabiłem i udało mi się opuścić Paryż, zanim natknąłem się na doświadczonego wojownika, który by mnie wykończył.";
			link.l1.go = "drinking_in_tavern_4";
		break;
		
		case "drinking_in_tavern_herotype_4":
			dialog.text = " ";
			link.l1 = "Spędzałem dużo czasu na cmentarzach. Nie myśl źle - to było po prostu popularne hobby w moim towarzystwie. Dla odwagi chodziliśmy nocą na cmentarz, stawialiśmy puste butelki na płocie i strzelaliśmy do nich na czas. Przez noc marnowaliśmy setki kul i skrzynkę szampana. Teraz oczywiście wstydzę się takiego zachowania, ale wtedy zwycięzca zgarniał solidny jackpot i otrzymywał pewne... przychylności ze strony dam na dworze. Wszystko było używane - nawet trochę bawiłem się mieszankami prochu. Ale dlaczego żaden z nas nie pomyślał, żeby nauczyć się robić papierowe naboje - tego nigdy nie pojmę.";
			link.l1.go = "drinking_in_tavern_4";
		break;
		
		case "drinking_in_tavern_herotype_2":
			dialog.text = "";
			link.l1 = "Studiowałem, i to dość pilnie - nawet byłem bliski dostania się na Sorbonę. Pracowałem w biurze, dopóki nie zaczęło to być nudne, a w ogóle - zajmowałem się trochę wszystkim. Nauczyciel, stary przyjaciel mojego ojca, wolał praktykę od teorii, więc miałem okazję zobaczyć Paryż z każdej strony i porozmawiać z różnymi ludźmi: od bandytów po szlachtę. Wszystko to okazało się przydatne tutaj.";
			link.l1.go = "drinking_in_tavern_4";
		break;
		
		case "drinking_in_tavern_4":
			dialog.text = "I... to wszystko? A więc jest w tobie coś jeszcze, mój kapitanie. Coś, czego jeszcze w sobie nie dostrzegłeś. Za ciebie!";
			link.l1 = "Za zdrowie!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_TavernChange");
		break;
		
		case "drinking_my_background":
			dialog.text = " ";
			link.l1 = "Opowiedz mi swoją historię, Helen. Moje przygody w Stolicy bledną w porównaniu do dziewczyny poniżej trzydziestki, dowodzącej szkunerem ze stu ludźmi na pokładzie.";
			link.l1.go = "drinking_my_background_1";
		break;
		
		case "drinking_my_background_1":
			dialog.text = "„Nieco poniżej trzydziestki, co, Charles? Za taki mocny komentarz, będziesz musiał zapłacić za następną kolejkę! Wszyscy moi ludzie nie żyją, i nie dowodzę już szkunerem. Szczerze mówiąc, nie wiem, czy jeszcze kiedyś będę dowodzić.”";
			link.l1 = "Przepraszam, Helen. Nie chciałem dotknąć czułego punktu. Ale dlaczego uważasz, że twoja kariera kapitana dobiegła końca?";
			link.l1.go = "drinking_my_background_2";
		break;
		
		case "drinking_my_background_2":
			dialog.text = "Because my crew is dead, and a different one won't ever accept me. Eh! Fine, my captain, you've told me a lot about your life; now it's my turn! The truth is not at the bottom of this mug, so let's dispense with the mystery.";
			link.l1 = "";
			link.l1.go = "drinking_my_background_3";
		break;
		
		case "drinking_my_background_3":
			dialog.text = "Mój przypadek, Charles, jest wyjątkowy. Mój ojciec był jednym z najlepszych żeglarzy w tych stronach, wysoko cenionym przez Leśnego Diabła, jego załoga go uwielbiała, a on kochał mnie bardziej niż życie.";
			link.l1 = "";
			link.l1.go = "drinking_my_background_4";
		break;
		
		case "drinking_my_background_4":
			dialog.text = "Zabierz choć jedną z tych rzeczy, a albo wysłałby mnie do Londynu, by żyć w... cywilizacji, albo zostawiłby mnie tu, by więdnąć jak moja matka. Na początku wszystko układało się świetnie: chciałam wolności, prawdziwej wolności, Charles, a umiejętne dowodzenie okrętem wojennym z lojalną załogą daje ci dokładnie to. I mój ojciec dał mi wszystko, co mógł. Wypłynęłam z nim na morze w wieku dwunastu lat, spędziłam pierwsze sześć miesięcy, goniąc szczury w ładowni, i dopiero wtedy pozwolono mi pracować z marynarzami.";
			link.l1 = "Sean MacArthur zrobił z ciebie szczura okrętowego? Przykro mi, Helen, ale z tego nie ma powrotu! Jak załoga cię przyjęła?";
			link.l1.go = "drinking_my_background_5";
		break;
		
		case "drinking_my_background_5":
			dialog.text = "Well, perhaps I'm exaggerating a bit for the sake of a good story? My father's crew accepted me; he gathered fine people. But since then, I've been afraid... of holds and any small dark spaces in general. Ha! Svensson almost killed my father when he found out!";
			link.l1 = "Jest dla ciebie ważny. Wyraźnie odegrał rolę w twoim losie, nie mniejszą niż Sean.";
			link.l1.go = "drinking_my_background_6";
		break;
		
		case "drinking_my_background_6":
			dialog.text = "Tak. Wszyscy baronowie otwarcie powiedzieli mojemu ojcu, że jest głupcem, ale to Diabeł z Lasu dał mu swoje poparcie i uścisnął mu dłoń, gdy pobiłam rekord załogi wspinając się na maszt. Tamten moment pozostanie ze mną na zawsze: triumfalne okrzyki załogi i, gdziekolwiek spojrzałam, czysty morski horyzont. I aprobujące spojrzenie mojego ojca, nie mogłam go zobaczyć, ale czułam je całym sercem.";
			link.l1 = "Mój triumf zakończył się tym, że spadłem z takielunku w pierwszy dzień podróży do Gwadelupy.";
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.TakeFolke")) {
				link.l1 = link.l1+" Mój sternik, Deluc, miał również bardzo wymowny wyraz twarzy."}
			link.l1.go ="picie_moje_tło_7";
		break;
		
		case "drinking_my_background_7":
			dialog.text = "Ah-ha-ha! I can imagine! Don't worry, that was a long time ago; now you're a real sea wolf!";
			link.l1 = "";
			link.l1.go = "drinking_my_background_8";
		break;
		
		case "drinking_my_background_8":
			dialog.text = "Za nasze triumfy!";
			link.l1 = "Słuchajcie, słuchajcie!";
			link.l1.go = "drinking_my_background_12";
		break;
		
		case "drinking_my_background_12":
			dialog.text = "... And then I gradually rose through the ranks, served at the captain's table in councils with my father and officers. Learned a lot. From the age of fifteen, they started taking me on military campaigns, and I killed a man in my very first battle. It was a disgusting campaign; we shouldn't have set sail on a Monday... Really shouldn't have!";
			link.l1 = "W wieku piętnastu lat? Przerażasz mnie, Helen.";
			link.l1.go = "drinking_my_background_13";
		break;
		
		case "drinking_my_background_12":
			dialog.text = "Nie mogłam nawet zrozumieć, co się stało. Holenderski kupiec miał swoją awangardę - najemników Kompanii. Postanowili zagrać odważnie i kontratakowali nasz rufowy pokład. A ja, głupia, bez żadnego strachu o własne życie, wystawiłam swoją blond głowę. Od razu oberwałam kolbą pistoletu. Ale chwilę przed tym udało mi się wbić szpadę w jakiegoś głupca z Kompanii.";
			link.l1 = "Na Boga, a co z Seanem? Jak to możliwe, że cię nie wyrzucił na brzeg po tym?";
			link.l1.go = "drinking_my_background_13";
		break;
		
		case "drinking_my_background_13":
			dialog.text = "Mój ojciec również nie wyszedł z tej bitwy bez szwanku, a widok mojego rozbitego głupiego łba na pewno nie pomógł. Powoli zaczął się pogarszać, i prawdopodobnie nikt tego nie zauważył oprócz mnie. A potem odszedł. Zgodnie z jego wolą, odziedziczyłam Tęczę z jej załogą i wystarczającymi funduszami, by utrzymać statek na powierzchni przez rok.";
			link.l1 = "I czy załoga zaakceptowała cię jako kapitana?";
			link.l1.go = "drinking_my_background_14";
		break;
		
		case "drinking_my_background_14":
			dialog.text = "Nie żyjemy w bajce, mój kapitanie. Niektórzy spotkali się z wolą mego ojca z wrogością - sprawy przybrały nieprzyjemny obrót\nGdyby choć jeden marynarz opuścił Tęczę, odmawiając służby pod moim dowództwem, byłoby to bardzo złe dla mojego wizerunku. Ale Svensson interweniował i wszystko naprawił. Nikt wtedy nie opuścił załogi... Osiem lat dowodziłam moją pięknością, transportowałam podejrzane towary dla Leśnego Diabła, szukałam skarbów, żyłam... Ale teraz, to wszystko przeszłość.";
			link.l1 = "Nie w przeszłości. Wierzę, że jesteś przeznaczony do żeglugi pod własną banderą ponownie! Wypijmy za to!";
			link.l1.go = "drinking_my_background_sea";
			link.l2 = "Może nie odzyskamy statku, ale twój rapier wciąż jest przy tobie.";
			link.l2.go = "drinking_my_background_land";
		break;
		
		case "drinking_my_background_sea":
			dialog.text = "Wiesz, kiedy mówisz to w ten sposób, też w to wierzę. Napijmy się!";
			link.l1 = "";
			link.l1.go = "drinking_my_background_15";
			
			AddCharacterSkill(npchar, SKILL_COMMERCE, 5);
			AddCharacterSkill(npchar, SKILL_ACCURACY, 5);
			AddCharacterSkill(npchar, SKILL_CANNONS, 5);
			AddCharacterSkill(npchar, SKILL_SAILING, 5);
			AddCharacterSkill(npchar, SKILL_REPAIR, 5);
			AddCharacterSkill(npchar, SKILL_GRAPPLING, 5);
			AddCharacterSkill(npchar, SKILL_DEFENCE, 5);
			notification("Naval Skills +", "Helena");
			
			pchar.questTemp.HelenDrinking.Background = "sea";
		break;
		
		case "drinking_my_background_land":
			dialog.text = "Аle czy moja szpada przyniesie mi szczęście? Odpowiedź jest prawdopodobnie na dnie tego kufla. Pijmy!";
			link.l1 = "";
			link.l1.go = "drinking_my_background_15";
			
			AddCharacterSkill(npchar, SKILL_F_LIGHT, 5);
			AddCharacterSkill(npchar, SKILL_FENCING, 5);
			AddCharacterSkill(npchar, SKILL_F_HEAVY, 5);
			AddCharacterSkill(npchar, SKILL_PISTOL, 5);
			AddCharacterSkill(npchar, SKILL_FORTUNE, 5);
			AddCharacterSkill(npchar, SKILL_LEADERSHIP, 5);
			AddCharacterSkill(npchar, SKILL_SNEAK, 5);
			notification("Personal Skills +", "Helena");
			
			pchar.questTemp.HelenDrinking.Background = "land";
		break;
		
		case "drinking_my_background_15":
			dialog.text = "Zastanawiałam się nad twoim życiem w Europie... Spójrz, jesteś miejskim fircykiem, a ja tylko zwykłą dziewczyną, ale już zdobyliśmy imiona w najniebezpieczniejszym zakątku świata.";
			link.l1 = "Brzmi jak toast! Więc, czy jest coś, co nas łączy?";
			link.l1.go = "drinking_my_background_16";
		break;
		
		case "drinking_my_background_16":
			dialog.text = "Cóż, stoję na ramionach mojego ojca. Nie wiem, jak to u ciebie, ale być może twoja rodzina również miała na ciebie nie mniejszy wpływ? Może jeszcze tego nie zauważyłeś?";
			link.l1 = "Zapytam mojego drogiego brata, gdy tylko wyciągnę go z więzienia.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_TavernEmpty");
		break;
		
		case "drinking_game":
			dialog.text = "Cóż, to wszystko, mój kapitanie. Wymieniliśmy się historiami, czas zakończyć wieczór.";
			link.l1 = "Hmm, miałam nadzieję na inne zakończenie wieczoru.";
			link.l1.go = "drinking_game_1";
		break;
		
		case "drinking_game_1":
			dialog.text = "Noc jeszcze się nie skończyła. Proponuję grę: jeśli dobrze rozegrasz swoje karty, być może twoje modlitwy zostaną wysłuchane.";
			link.l1 = "Zamierzamy grać w karty? Wchodzę w to!";
			link.l1.go = "drinking_game_2";
		break;
		
		case "drinking_game_2":
			dialog.text = "Spokojnie, wilku morski. Nie będę z tobą grała w rozbieranego pokera.";
			link.l1 = "Tak, masz rację, Helen. Nie mamy tu prywatności.";
			link.l1.go = "drinking_game_3";
		break;
		
		case "drinking_game_3":
			dialog.text = "To nie jedyna rzecz, której nam brakuje, Charles... To nie jest gra karciana, ale nie martw się, zakładam, że jesteś w tym mistrzem. 'Nigdy' - słyszałeś o tym?";
			link.l1 = "Znajomy. Z przeszłego życia. Czy często w to grywasz?";
			link.l1.go = "drinking_game_4";
		break;
		
		case "drinking_game_4":
			dialog.text = "Zawsze chciałam spróbować, ale nie miałam z kim grać.";
			link.l1 = "To dość śmiała gra na nasz pierwszy wspólny drink. Jesteś pewien?";
			link.l1.go = "drinking_game_5";
			link.l2 = "A propos, gdzie wszyscy? Jesteśmy tu sami?";
			link.l2.go = "drinking_game_6";
		break;
		
		case "drinking_game_5":
			dialog.text = "Tak, po ostatnich wydarzeniach, muszę trochę pożyć. Zrobić coś głupiego, wiesz?";
			link.l1 = "Nie, to zawsze kończy się źle, Rumbo.";
			link.l1.go = "drinking_game_refuse";
			link.l2 = "Zaczynajmy! Panie przodem!";
			link.l2.go = "drinking_game_accept";
		break;
		
		case "drinking_game_6":
			dialog.text = "Wysłałam ich wszystkich do domu - nie trzeba pozwalać obcym podsłuchiwać.";
			link.l1 = "Nie, to zawsze kończy się źle, Rumba.";
			link.l1.go = "drinking_game_refuse";
			link.l2 = "Do dzieła! Panie przodem!";
			link.l2.go = "drinking_game_accept";
		break;
		
		case "drinking_game_refuse":
			dialog.text = "Szkoda, ale może masz rację. To co, jeszcze jeden drink?";
			link.l1 = "Zaczynajmy! Panie przodem!";
			link.l1.go = "drinking_game_refuse_1";
		break;
		
		case "drinking_game_refuse_1":
			dialog.text = "Załatwiłam to - pokój na górze jest twój. Był zajęty przez jakiegoś ważnego francuskiego oficera, ale chłopcy Leśnego Diabła grzecznie poprosili go, żeby opuścił miejsce. Idź się zdrzemnąć - nie pozwolę ci błąkać się po ulicy, a tym bardziej wypływać na morze w takim stanie.";
			link.l1 = "Tak, pani kapitan!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToTavernRoom");
		break;
		
		case "drinking_game_accept":
			dialog.text = "Ha! Hic! To znaczy, że zaczynasz!";
			link.l1 = "Ostrożnie, kochanie! Hmm. Nigdy nie goniłam szczurów w ładowni!";
			link.l1.go = "drinking_game_accept_1";
		break;
		
		case "drinking_game_accept_1":
			dialog.text = "Więc tak to jest? Trzeba mieć się na baczności z tobą! (Pije)";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_2";
		break;
		
		case "drinking_game_accept_2":
			dialog.text = "Brr! Sama pamięć o tym... No cóż, trzymaj się, przystojniaku: nigdy nie spadłam z reji!";
			link.l1 = "Ile jeszcze będziemy się bujać na tej łajbie, kapitanie?";
			link.l1.go = "drinking_game_accept_3";
		break;
		
		case "drinking_game_accept_3":
			dialog.text = "";
			link.l1 = "Ładnie! Pozwól mi, panienko, wznieść za ciebie toast! (Pije)";
			link.l1.go = "drinking_game_accept_4";
		break;
		
		case "drinking_game_accept_4":
			dialog.text = "";
			link.l1 = "Nie byłam nigdy przesądna.";
			link.l1.go = "drinking_game_accept_5";
			
			LAi_Fade("", "");
			pchar.GenQuest.CamShuttle = 1;
			SetCamShuttle(loadedLocation);
			SetPitch(0.95);
		break;
		
		case "drinking_game_accept_5":
			dialog.text = "A ty siebie nazywasz żeglarzem! Dobrze wiesz, kim jesteśmy. Nigdy nie wiadomo, co przyniesie rejs, nie wiadomo, kiedy i gdzie zobaczysz ląd, jeśli w ogóle. Musisz szukać odpowiedzi poza mapami i narzędziami nawigacyjnymi! Na zdrowie! (Pije)";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_6";
		break;
		
		case "drinking_game_accept_6":
			dialog.text = "A dziewczęta, które malowałeś osobiście... Czy podobał im się wynik?";
			link.l1 = "Nie zawsze podobały im się obrazy, ale, um... rezultat - zawsze.";
			link.l1.go = "drinking_game_accept_7";
		break;
		
		case "drinking_game_accept_7":
			dialog.text = "Charles! Gdybyśmy się wtedy spotkali, zastrzeliłabym cię lub wzięła jako zakładnika dla okupu. A tak przy okazji, nigdy nie brałam do ręki pędzli.";
			link.l1 = "Hej! Cóż, to całkowicie banalne. Droga Helen, jeśli zacznę wymieniać rzeczy, których nigdy nie podjęłaś...";
			link.l1.go = "drinking_game_accept_8";
		break;
		
		case "drinking_game_accept_8":
			dialog.text = "W porządku, dobrze, będę grała uczciwie. Twój ruch, mój kapitanie.";
			link.l1 = "(Pociąga łyk) Hic!. Hmm...Nigdy jeszcze moje modelki nie uderzyły mnie rękojeścią pistoletu w głowę.";
			link.l1.go = "drinking_game_accept_9";
		break;
		
		case "drinking_game_accept_9":
			dialog.text = "(Siorbie) Uch. Gramy w tę grę źle, drogi. Myślałam, że będziemy pić i poznawać się nawzajem, ale zamiast tego wymieniamy się obelgami i... i... Czk. Cholera!";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_10";
			
			LAi_Fade("", "");
			pchar.GenQuest.CamShuttle = 2;
			SetCamShuttle(loadedLocation);
			SetPitch(0.90);
		break;
		
		case "drinking_game_accept_10":
			dialog.text = "Uczyńmy to bardziej interesującym! I najlepiej coś, co nie jest związane z tym, o czym rozmawialiśmy godzinę temu!";
			link.l1 = "Jeszcze nigdy nie obudziłam się w nieznanym miejscu po pijackiej hulance.";
			link.l1.go = "drinking_game_accept_11";
		break;
		
		case "drinking_game_accept_10":
			dialog.text = "Auć! Cholera, Charles! (Pije)";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_11";
		break;
		
		case "drinking_game_accept_11":
			dialog.text = "Ja... Hic... nie mogę uwierzyć. Przyznaję się, winny - mała Rumba często trafiała na dno. Ale nigdy nie byłem w więzieniu!";
			link.l1 = "Jak to ci się udało...?";
			link.l1.go = "drinking_game_accept_12";
		break;
		
		case "drinking_game_accept_12":
			dialog.text = "Hahaha! Pij, pij!";
			link.l1 = "Pożałuję tego. (Pije)";
			
			if (IsCharacterEquippedArtefact(pchar, "totem_01")) {
				link.l1.go = "drinking_game_accept_13";
			} else {
				link.l1.go = "exit";
				AddDialogExitQuestFunction("HelenDrinking_LightsOut");
			}
		break;
		
		case "drinking_game_accept_13":
			dialog.text = "Chodź, mój drogi. Ostatnie pytanie i ostatnia szansa, by mnie przechytrzyć!";
			link.l1 = "Nie... Ja... Wyjdźmy na świeże powietrze.";
			link.l1.go = "drinking_game_enough";
			link.l2 = "Piłem często, ale nigdy tak... Nigdy nie upiłem się tak z dziewczyną. Przysięgam na swoje słowo, picie to naprawdę wielki grzech...";
			link.l2.go = "drinking_game_accept_14";
			
			LAi_Fade("", "");
			pchar.GenQuest.CamShuttle = 3;
			SetCamShuttle(loadedLocation);
			SetPitch(0.85);
		break;
		
		case "drinking_game_enough":
			dialog.text = "Eh!";
			link.l1 = "";
			link.l1.go = "drinking_game_refuse_1";
		break;
		
		case "drinking_game_accept_14":
			dialog.text = "";
			link.l1 = "C-czekaj... Nie pijesz?";
			link.l1.go = "drinking_game_accept_15";
		break;
		
		case "drinking_game_accept_15":
			dialog.text = "Ah-ha-ha! To zabawne! Masz wysokie cele, mój kapitanie. Niech to będzie... hik!... wiadome tobie...";
			link.l1 = " ";
			link.l1.go = "drinking_game_accept_16";
		break;
		
		case "drinking_game_accept_16":
			dialog.text = "Że mam nieszczęście żyć w załodze składającej się wyłącznie z mężczyzn i muszę zachowywać się ostrożnie. Jestem uczciwą dziewczyną.";
			link.l1 = "Jestem s-szczęśliwy z twojego powodu, H-Helen.";
			link.l1.go = "drinking_game_accept_17";
		break;
		
		case "drinking_game_accept_17":
			dialog.text = "Będziesz jeszcze szczęśliwszy, bo wygrałam! Ale, szczerze mówiąc, nigdy wcześniej nie upiłam się tak z żadnym facetem.";
			link.l1 = "„(Cicho bierze łyk) D-do ciebie. Gratulacje... cz-czkawka...”";
			link.l1.go = "drinking_game_accept_18";
		break;
		
		case "drinking_game_accept_18":
			dialog.text = "Hej-hej-hej! Kapitanie, dokąd się wybierasz? Może się obraziłeś?";
			link.l1 = "Potrzebuję... p-przerwy? Tylko pójdę znaleźć m-mój miecz...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_ExitTavern");
		break;
		
		case "drinking_at_svenson":
			dialog.text = "Kapitanie, jesteś gotów? Nie ma odwrotu, a jeśli coś pójdzie nie tak, zmuszę cię do poślubienia mnie.";
			link.l1 = "Phew! Daj mi przynajmniej zaczerpnąć świeżego powietrza! Jesteś tego pewna, Helen?";
			link.l1.go = "drinking_at_svenson_1";
		break;
		
		case "drinking_at_svenson_1":
			dialog.text = "Tak, do diabła, i nie stój tam jak słup! Muszę się zgubić, choćby tylko na jedną noc!";
			link.l1 = "Obawiam się, że po tej nocy to ja będę chciała się zgubić. Chodźmy, zanim obudzimy całe miasto.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_EnterSvenson");
		break;
		
		case "drinking_give_key":
			dialog.text = "Cap, take the key and go upstairs. There should be a chest; you probably saw it when Svensson had it. Grab the barrel and head back immediately.";
			link.l1 = "Chwileczkę, drogi, dlaczego muszę okradać twojego szefa?";
			link.l1.go = "drinking_give_key_1";
			
			GiveItem2Character(pchar, "key3");
			PlaySound("interface\important_item.wav");
		break;
		
		case "drinking_give_key_1":
			dialog.text = "Don't be silly. I've been here since childhood; if the owners return, I can handle it and cover for you. Come on, don't lower your sail now!";
			link.l1 = "Ostra jak nóż, prawdziwa przemytniczka! Czekaj, będę szybki.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GotKey");
		break;
		
		case "drinking_got_whiskey":
			dialog.text = "Zrozumiano?";
			link.l1 = "Nie pierwszy to kufer, który opróżniłem, i z pewnością nie ostatni!";
			link.l1.go = "drinking_got_whiskey_1";
		break;
		
		case "drinking_got_whiskey_1":
			dialog.text = "Jestem z ciebie dumna! Haha! Pierwszorzędna irlandzka whiskey, 'Bushmills'! W tawernie nie podadzą nam takiego trunku.";
			link.l1 = "Brzmi dobrze, ale czy Svensson nie zauważy, że go brakuje?";
			link.l1.go = "drinking_got_whiskey_2";
		break;
		
		case "drinking_got_whiskey_2":
			dialog.text = "Na pewno zauważy, ale sam tego nie pije. Wygląda na to, że zachował to jako prezent dla swojego pirackiego kumpla Dodsona, a Dodson albo zniknął, albo kogoś zabił...";
			link.l1 = "To straszne! Taki dar absolutnie nie może się zmarnować. Chwytaj beczkę, a my zmieniamy scenerię!";
			link.l1.go = "drinking_got_whiskey_3";
		break;
		
		case "drinking_got_whiskey_3":
			dialog.text = "Dobrze powiedziane, kapitanie. Jeszcze jedna rzecz - powiedz mi, czy zabrałeś coś jeszcze ze skrzyni? Odpowiedz szczerze.";
			if (HelenDrinking_RobbedSvenson()) {
				link.l1 = "Wziąłem coś, nawyk, wiesz.";
				link.l1.go = "drinking_got_whiskey_notbelieve";
			}
			
			link.l2 = "Nie. Nie jestem pewna, czy jestem piratem, ale na pewno nie jestem złodziejką.";
			link.l2.go = "drinking_got_whiskey_believe";
			
			if (HelenDrinking_RobbedSvenson()) {
				link.l2.go = "drinking_got_whiskey_notbelieve";
				pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 2;
				notification("Helen disapproves", "Helena");
				pchar.questTemp.HelenDrinking.RobbedSvenson = true;
			}
		break;
		
		case "drinking_got_whiskey_believe":
			dialog.text = "Jakoś ci wierzę... głupia, że jestem!";
			link.l1 = " ";
			link.l1.go = "drinking_get_out";
		break;
		
		case "drinking_got_whiskey_notbelieve":
			dialog.text = "Idź i upewnij się, że niczego nie zabraliście z jakiegoś powodu.";
			link.l1 = "";
			link.l1.go = "exit";
			if (!HelenDrinking_RobbedSvenson()) {
				AddDialogExitQuestFunction("HelenDrinking_JoanEnter");
				TakeItemFromCharacter(pchar, "cask_whisky");
				sld = ItemsFromID("cask_whisky");
				sld.price = sld.pricebak;
				DeleteAttribute(sld, "pricebak");
			}
			
			NextDiag.TempNode = "drinking_got_whiskey_notbelieve";
		break;
		
		case "drinking_get_out":
			DialogExit();
			
			AddDialogExitQuestFunction("HelenDrinking_JoanEnter");
			TakeItemFromCharacter(pchar, "cask_whisky");
			sld = ItemsFromID("cask_whisky");
			sld.price = sld.pricebak;
			DeleteAttribute(sld, "pricebak");
		break;
		
		case "drinking_at_fort":
			dialog.text = "Hej, hej, moja droga! Skup się! Moja twarz, pocałowana przez morską bryzę, jest tutaj!";
			link.l1 = "Uf, cóż, twój kostium to coś! Musiałeś zaoszczędzić sporo pieniędzy na materiale do szycia. A ja... hic! Widziałem wiele! Ale to... Ale to jest najlepsze, co widziałem.";
			link.l1.go = "drinking_at_fort_1";
			locCameraFromToPos(-1.65, 44.45, 76.64, true, -5.93, 42.10, 70.13);
		break;
		
		case "drinking_at_fort_1":
			dialog.text = "Wszyscy to mówią, ale z jakiegoś powodu wierzę ci! Naprawdę ci się podoba?";
			link.l1 = "Och, oczywiście, bardzo korzystnie podkreśla twoją sylwetkę, choć...";
			link.l1.go = "drinking_at_fort_2";
		break;
		
		case "drinking_at_fort_2":
			dialog.text = "Och, teraz wszystko zepsułeś!";
			link.l1 = "... chociaż nie mam wątpliwości, że wśród zwykłych ludzi wzbudza to podziw!";
			link.l1.go = "drinking_at_fort_3";
		break;
		
		case "drinking_at_fort_3":
			dialog.text = "Jestem raczej pod wrażeniem tego dziwnego rozpowszechnionego zwyczaju wśród pospólstwa i nie tylko, by nosić gęste europejskie stroje w takim upale. To sprawia, że nasze wioski wyglądają jeszcze bardziej komicznie... Podoba mi się mój strój, Charles. W nim czuję się piękna, a to ważne dla kobiety.";
			link.l1 = "Pozostałabyś równie piękna bez tego stroju, Helen.";
			link.l1.go = "drinking_at_fort_4";
		break;
		
		case "drinking_at_fort_4":
			dialog.text = "Ostrożnie, mój kapitanie! Mówienie takich słodkich rzeczy może zepsuć biedną dziewczynę!";
			link.l1 = "Jeśli ona nie ma nic przeciwko, to ja też nie mam.";
			link.l1.go = "drinking_at_fort_5";
		break;
		
		case "drinking_at_fort_5":
			dialog.text = "Hee-hee! Lepiej zapytaj mnie o coś innego. Lubię, kiedy stajesz się dociekliwy.";
			link.l1 = "W takim razie wciśnijmy pytanie o twój strój. Nie wierzę, że wilki morskie mogą brać kapitana na poważnie w takim ubiorze.";
			link.l1.go = "drinking_at_fort_6";
		break;
		
		case "drinking_at_fort_6":
			dialog.text = "A nie wierzę, że wilki morskie, ogólnie rzecz biorąc, mogą zobaczyć kobietę jako kapitana, więc mój strój prawdopodobnie nie dodał moich problemów. A może nie miał czasu dodać, bo to nowa rzecz. Sama go uszyłam!\nAh-ha-ha! Kiedyś nosiłam jedno z tych... jak to się nazywa? Nasza armia nadal je nosi! B-r-r... Widząc jedno z nich teraz robi mi się niedobrze.";
			link.l1 = "Uniformy?";
			link.l1.go = "drinking_at_fort_7";
		break;
		
		case "drinking_at_fort_7":
			dialog.text = "O, dokładnie, mundur! Czerwony mundur! Jak ten, który nosi tamten gość.";
			link.l1 = "...";
			link.l1.go = "exit";
			
			pchar.GenQuest.BlockDialogCamera = true;
			AddDialogExitQuestFunction("HelenDrinking_OfficerAtFort");
		break;
		
		case "drinking_at_fort_7_1":
			dialog.text = "Och, przepraszam, majorze, pozwól, że poczęstuję cię wyborną irlandzką whiskey jako... hik!... przeprosinami.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog2");
		break;
		
		case "drinking_at_fort_7_2":
			dialog.text = "Charles nie wpadnie w kłopoty, prawda, Majorze? Powiedz mi, że nie wpadnie, ślicznie proszę!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog4");
		break;
		
		case "drinking_at_fort_8":
			dialog.text = "Tak się cieszę! Napijmy się!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToVillage");
		break;
		
		case "drinking_at_miskito":
			dialog.text = "Och. Spójrz, co mam!";
			link.l1 = "Helen... Czy planujesz użyć tego... aby podnieść sobie nastrój?!.. Nawet o tym nie myśl! Bieluń może całkowicie zawładnąć człowiekiem, wyczerpać jego siły, złamać jego wolę! Zanim się obejrzysz, jesteś żywym trupem, a potem bardzo szybko, martwym...";
			link.l1.go = "drinking_at_miskito_1";
		break;
		
		case "drinking_at_miskito_1":
			dialog.text = "Charles, ale... właśnie teraz...";
			link.l1 = "Żadnych ale. Przepraszam, że jestem surowa, ale to nie są żarty. Zabieram ci to. Nie mogę uwierzyć, co sobie myślałeś... Tutaj, wypij to i ochłoń.";
			link.l1.go = "drinking_at_miskito_2";
			
			GiveItem2Character(pchar, "cannabis7");
			PlaySound("interface\important_item.wav");
		break;
		
		case "drinking_at_miskito_2":
			dialog.text = "Przepraszam, Charles. Masz absolutnie rację, wiem. Chwilowa słabość. To się nie powtórzy. Dzięki za ocalenie mnie od pokusy diabła...";
			link.l1 = "Zapomnijmy o tym... Teraz powiedz mi, jak udało ci się zdobyć szacunek w mieście, utrzymać dobre relacje z oficerami garnizonu i zaprzyjaźnić się z tubylcami?";
			link.l1.go = "drinking_at_miskito_3";
		break;
		
		case "drinking_at_miskito_3":
			dialog.text = "Szanują Svenssona, a część tego szacunku przenosi się na mnie. Nasze małe miasteczko przetrwa wyłącznie dzięki interesom Jana. Dzieli się częścią zysków ze swoich plantacji kakao z czerwonymi kurtkami, a Miskito zawdzięczają mu całe swoje utrzymanie.";
			link.l1 = "Jak to się stało?";
			link.l1.go = "drinking_at_miskito_4";
		break;
		
		case "drinking_at_miskito_4":
			dialog.text = "Kiedy Kastylijczycy rządzili, nie przeszkadzali zbytnio Indianom. Ale po wygnaniu szlachetnych Hidalgo, nasi ludzie postanowili przejąć kontrolę nad lokalnymi lasami. Jan rozwiązał sprawę dość stanowczo wtedy - nawet wysłał ludzi do Londynu! Oczywiście, nie z dobroci serca: wydobycie kakao w lesie, gdzie każdy krzak cię nienawidzi, to beznadziejna sprawa. Ale teraz, Indianie nie tylko pomagają Janowi przemycać z Porto Bello do Blueweld, ale też wycinają własne lasy za marne grosze. Brawo, Leśny Diable, brawo!";
			link.l1 = "Brzmi, jakbyś nie do końca aprobowała jego metody.";
			link.l1.go = "drinking_at_miskito_5";
		break;
		
		case "drinking_at_miskito_5":
			dialog.text = "Kochałam i szanowałam lud Miskito, lecz również szanuję strategię Jana. Nie żyjemy w bajce, mój kapitanie.";
			link.l1 = "Hm... Widzę, że twoja relacja ze Svenssonem jest bardziej skomplikowana, niż wydaje się na pierwszy rzut oka...";
			link.l1.go = "drinking_at_miskito_6";
		break;
		
		case "drinking_at_miskito_6":
			dialog.text = "Even more than you know. His wife has a good reason to be venomous towards me... Jan has been eyeing me since I was about fifteen. It was around the time I started walking the decks of the Rainbow as an equal, and apparently, something clicked in the Forest Devil's mind back then... But I've said too much, my captain. Let's not delve into this topic; gossiping about our patron is not very decent.";
			link.l1 = "W takim razie zmieńmy temat. Chciałam powiedzieć, że wyraźnie pasujesz do tej kompanii, i uważają cię za swojego.";
			link.l1.go = "drinking_at_miskito_7";
		break;
		
		case "drinking_at_miskito_7":
			dialog.text = "Tak się składa, że znacznie łatwiej mi przebywać w towarzystwie Indian, Cyganów i innych przyzwoitych wyrzutków. Mamine gulasze, ogniska na plaży i pokład Tęczy - zbudowałam sobie przytulny, mały świat, Kapitanie. Szkoda, że to wszystko runęło właśnie wtedy, gdy myślałam, że wszystko już rozgryzłam.";
			link.l1 = "Beczka jest prawie pusta... Jeszcze jedna kolejka?";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToShipyard");
		break;
		
		case "drinking_at_perlas":
			dialog.text = "To takie dobre... Cieszę się, że zgodziłeś się spędzić ze mną czas, Kapitanie. Naprawdę tego potrzebowałam. Wierzę, że Ty też.";
			link.l1 = "Tak, minęła chwila, odkąd tak odpoczywałam. To będzie coś, co zapamiętam!";
			link.l1.go = "drinking_at_perlas_1";
		break;
		
		case "drinking_at_perlas_1":
			dialog.text = "Zapewne myślisz, że diabli wiedzą co o mnie teraz, Charles. Z natury jestem bardzo zamkniętą osobą. Po prostu... cholera, po prostu chciałam poczuć, że żyję! Chciałam tylko z kimś porozmawiać!";
			link.l1 = "A co z Gladys? Jan?";
			link.l1.go = "drinking_at_perlas_2";
		break;
		
		case "drinking_at_perlas_2":
			dialog.text = "Wszystko, co robi mama, to płacze, a Jan wydaje się teraz innym człowiekiem. Może sobie to wyobrażam, nie wiem, ale jakby się teraz mnie wstydził? Wybacz, ja... (pociąga nosem).\nDość tego, stara dziewczyno. Przepraszam, trochę się uniosłam.";
			link.l1 = "Nie musisz przepraszać. Rozumiem wszystko, a przynajmniej tak mi się wydaje.";
			link.l1.go = "drinking_at_perlas_3";
		break;
		
		case "drinking_at_perlas_3":
			dialog.text = "Mówię to wszystko, ponieważ dopiero co się poznaliśmy, a nie jestem przyzwyczajona do bycia tak otwartą nawet wobec tych, których znam od dawna. Nazywają mnie Rumba, rzekomo z powodu mojego charakteru, ale jak widzisz, to błędne określenie. Czy rum już się skończył?";
			link.l1 = "Jakiś czas temu, a już świta.";
			link.l1.go = "drinking_at_perlas_4";
		break;
		
		case "drinking_at_perlas_4":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_friend") && !CheckAttribute(pchar, "questTemp.HelenDrinking.RobbedSvenson")) {
				dialog.text = "Przepraszam, mój kapitanie, jeśli miałeś inne oczekiwania co do naszego wieczoru. Ja... Nie mogę. Nie dzisiaj.";
			} else {
				dialog.text = "W takim razie dziękuję za wieczór, Kapitanie. Kto wie, może to powtórzymy.";
			}
			link.l1 = "Oczywiście, Helen.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_PoormanTalk");
		break;
		
		case "ambush":
			dialog.text = "Dzięki za przywiezienie mnie tutaj, kapitanie. Rozejrzyjmy się, dobrze? Zbadajmy moje dziedzictwo.";
			link.l1 = "Nie byłeś tu wcześniej?";
			link.l1.go = "ambush_1";
		break;
		
		case "ambush_1":
			dialog.text = "No, it's quite a ways away; besides, I'm no pirate. This place has never been particularly fascinating, and after they killed Blaise... It's better not to linger here.";
			link.l1 = "Nie będziemy. Już żałuję, że cię tu przyprowadziłam.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPrepareAmbush");
		break;
		
		case "after_ambush":
			switch (pchar.questTemp.HelenDrinking.IslaTesoroAmbush) {
				case "A":
					if (!CheckAttribute(pchar, "questTemp.HelenDrinking.IslaTesoroAmbush.TriedB") && !CheckAttribute(pchar, "questTemp.HelenDrinking.IslaTesoroAmbush.TriedC")) {
						dialog.text = "Did you have to, Captain? Why so quick to fight? Well, one should not just a winner, I guess. Come on, let's take a look at the residence; there's nothing else worth seeing here anyway.";
						pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 1;
						notification("Helen disapproves", "Helena");
					} else {
						dialog.text = "Kudos, my Captain, for trying to resolve the issue wisely before getting into a fight. Come on, let's take a look at the residence; there's nothing else worth seeing here anyway.";
					}
					
					link.l1 = "A co z tym ogromnym statkiem wyciągniętym na brzeg?";
					link.l1.go = "after_ambush_1";
				break;
				
				case "B":
					dialog.text = "You skillfully fooled those fools, my Captain! I almost burst out laughing, honest! Come on, let's take a look at the residence; there's nothing else worth seeing here anyway.";
					pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
					notification("Helen approves", "Helena");
					
					link.l1 = "A co z tym ogromnym statkiem wyciągniętym na brzeg?";
					link.l1.go = "after_ambush_1";
				break;
				
				case "C":
					dialog.text = "Zaczekaj, pozwól dziewczynie złapać oddech! Czy ty naprawdę jesteś tym Charlie Prince?";
					pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
					notification("Helen approves", "Helena");
					
					link.l1 = "Był taki okres w mojej biografii, tak. Czy jesteś pod wrażeniem?";
					link.l1.go = "after_ambush_c";
				break;
			}
		break;
		
		case "after_ambush_1":
			dialog.text = "Tak, masz rację. Chciałabym to zbadać, ale szczerze mówiąc, Charles, trochę się tego boję. Chodźmy.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroGoToResidence");
		break;
		
		case "after_ambush_c":
			dialog.text = "O mój Boże, tak! Pamiętaj, żeby później powiedzieć mi wszystko, dobrze? Bo słyszałam tylko opowieści... bardzo nieprzyzwoite opowieści!";
			link.l1 = "Powiem ci wszystko... prawie wszystko.";
			link.l1.go = "after_ambush_c_1";
		break;
		
		case "after_ambush_c_1":
			dialog.text = "I'll be waiting eagerly! Come on, let's take a look at the residence; there's nothing else worth seeing here anyway.";
			link.l1 = "A co z tym ogromnym statkiem wyciągniętym na brzeg?";
			link.l1.go = "after_ambush_1";
		break;
		
		case "ambush_inresidence":
			dialog.text = "Zatłoczona, zimna nora z absurdalnymi żądaniami. Już czuję się jak w pułapce!";
			link.l1 = "Widzę, że jak dotąd nie jesteś zadowolony z potencjalnego majątku?";
			link.l1.go = "ambush_inresidence_1";
		break;
		
		case "ambush_inresidence_1":
			dialog.text = "Nie, Charles. Może jestem zbyt wybredna, ale jak na razie uosabia to wszystko, czego się boję i nienawidzę. Mam nadzieję, że będę mogła to wynająć... Chociaż nie jestem pewna, na co wydam te pieniądze.";
			link.l1 = "Nie lekceważ wartości czynszu. Ja nie mam czynszu, i często muszę wymyślać sposoby, by opłacić moją załogę. Kupisz sobie nowy statek, 'Tęcza II' - brzmi dobrze, nie sądzisz?!";
			link.l1.go = "ambush_inresidence_sea";
			link.l2 = "Jest wiele sposobów, by wydać pieniądze na siebie. Zacznij od spersonalizowanego miecza i butelki doskonałego wina. Zafunduj sobie, Helen, zasługujesz na to.";
			link.l2.go = "ambush_inresidence_land";
		break;
		
		case "ambush_inresidence_sea":
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Background") && pchar.questTemp.HelenDrinking.Background == "sea") {
				dialog.text = "Dziękuję, mój kapitanie. Cieszę się, że to słyszę. Szczególnie miło słyszeć to po raz drugi. Znasz mnie dobrze.";
				pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 3;
				notification("Helen approves", "Helena");
			} else {
				dialog.text = "Dziękuję, mój kapitanie. Cieszę się, że to słyszę.";
			}
			
			link.l1 = "";
			link.l1.go = "ambush_inresidence_2";
			
			sld = CharacterFromID("Helena");
			
			AddCharacterSkill(sld, SKILL_COMMERCE, 5);
			AddCharacterSkill(sld, SKILL_ACCURACY, 5);
			AddCharacterSkill(sld, SKILL_CANNONS, 5);
			AddCharacterSkill(sld, SKILL_SAILING, 5);
			AddCharacterSkill(sld, SKILL_REPAIR, 5);
			AddCharacterSkill(sld, SKILL_GRAPPLING, 5);
			AddCharacterSkill(sld, SKILL_DEFENCE, 5);
		break;
		
		case "ambush_inresidence_land":
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Background") && pchar.questTemp.HelenDrinking.Background == "land") {
				dialog.text = "Czy myślisz, że na to zasługuję? Nigdy nie wydawałam pieniędzy na takie drobiazgi, ale chyba na wszystko przychodzi pierwszy raz. Widzę, że nie przestaniesz próbować sprawić, bym zapomniała o morzu, co? Może masz rację...";
				pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 3;
				notification("Helen disapproves", "Helena");
			} else {
				dialog.text = "Czy myślisz, że na to zasługuję? Nigdy nie wydawałam pieniędzy na takie drobiazgi, ale chyba zawsze jest ten pierwszy raz.";
			}
			link.l1 = "";
			link.l1.go = "ambush_inresidence_2";
			
			sld = CharacterFromID("Helena");
			
			AddCharacterSkill(sld, SKILL_F_LIGHT, 5);
			AddCharacterSkill(sld, SKILL_FENCING, 5);
			AddCharacterSkill(sld, SKILL_F_HEAVY, 5);
			AddCharacterSkill(sld, SKILL_PISTOL, 5);
			AddCharacterSkill(sld, SKILL_FORTUNE, 5);
			AddCharacterSkill(sld, SKILL_LEADERSHIP, 5);
			AddCharacterSkill(sld, SKILL_SNEAK, 5);
		break;
		
		case "ambush_inresidence_2":
			dialog.text = "Tak czy inaczej, inspekcja zakończona. Wygląda na to, że nie ma tu żadnych kosztowności - motłoch już zdążył wszystko złupić, i jestem pewna, że drugie piętro jest w takim samym stanie.";
			link.l1 = "To tak, jakbyś się zmieniła, Helen. Kiedy ostatnio się spotykaliśmy, byłaś... nie wiem, bardziej otwarta?";
			link.l1.go = "ambush_inresidence_3";
		break;
		
		case "ambush_inresidence_3":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6) {
				dialog.text = "Niczego się nie zmieniło, mój kapitanie, ale wiele spadło na barki biednej dziewczyny, haha! Nie chciałam cię urazić. Po prostu muszę teraz dużo rzeczy przemyśleć. Wiesz, takie ostre zakręty w życiu nie zdarzają się codziennie. A my wciąż mamy mnóstwo czasu razem!";
				link.l1 = "Cieszę się, że to słyszę! Wynośmy się stąd.";
			} else {
				dialog.text = "Much has changed, Captain. I'm afraid I have to be more mature now and look at life differently. It's not a fairy tale about a princess and inheritance; it's big politics, and I still have to realize my place in it. And my family's place too.";
				link.l1 = "Cieszę się, że to wyjaśniliśmy. Chodźmy stąd.";
			}
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroBeforeExit");
		break;
		
		case "ambush_inresidence_wait":
			dialog.text = "Tak?";
			if (CheckCharacterItem(pchar, "pirate_cutlass")) {
				link.l1 = "Hej, nie wszystko zostało splądrowane! Spójrz, Helen! Ta szabla wydaje się być legendarna, skoro nawet miejscowe łajdactwo zawahało się ją przywłaszczyć.";
				link.l1.go = "ambush_inresidence_give_cutlass";
			}
			
			link.l2 = "Nie, nic.";
			link.l2.go = "exit";
			
			NextDiag.TempNode = "ambush_inresidence_wait";
		break;
		
		case "ambush_inresidence_give_cutlass":
			dialog.text = "Wow, to jest... legendarny kordelas samego Blaise'a! Piraci darzyli go zbyt wielkim szacunkiem, by zabrać szablę z jego domu nawet po jego śmierci. Oczywiście zabrali pieniądze i kosztowności, ale nawet przyszłe wisielce mają resztki honoru...";
			link.l1 = "It looks like someone is clearly tidying up here. As if the owner will come back... This is not a home; it's a memorial!";
			link.l1.go = "ambush_inresidence_give_cutlass_1";
		break;
		
		case "ambush_inresidence_give_cutlass_1":
			dialog.text = "Dzięki za bystre spostrzeżenie, Charles. Całkowicie zrujnowałeś to miejsce w moich oczach, ha-ha!";
			link.l1 = "    Myślę, że ta szabla jest teraz twoja. Blaise to twój tak zwany wuj...";
			link.l1.go = "ambush_inresidence_give_cutlass_2";
		break;
		
		case "ambush_inresidence_give_cutlass_2":
			dialog.text = "Dodajesz do tego jeszcze więcej grozy, mój kapitanie. Ja... Ja nie mogę. Obawiam się, że jeśli to zaakceptuję, moje dotychczasowe życie całkowicie się skończy.";
			link.l1 = "Więc nie traktuj tego jako część spadku, lecz jako dar od przystojnego mężczyzny.";
			link.l1.go = "ambush_inresidence_give_cutlass_3";
		break;
		
		case "ambush_inresidence_give_cutlass_3":
			dialog.text = "Kto to może być? Żartuję! Dzięki za rozwianie moich ponurych myśli, mój kapitanie. Obiecuję, że będę dużo trenować, by zasłużyć na ten miecz!";
			link.l1 = "Jesteś godna najznamienitszej broni, Helen. Chodźmy, skończyliśmy tutaj.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GiveCutlass");
		break;
		
		case "give_cutlass":
			dialog.text = "O rany, to jest... legendarny szabla samego Blaise'a! Piraci szanowali go zbyt mocno, by zabrać jego szablę z domu nawet po jego śmierci. Oczywiście zabrali pieniądze i kosztowności, ale nawet przyszłe straceńce mają resztki honoru\nJa... Ja nie mogę. Boję się, że jeśli to przyjmę, moje dawne życie dobiegnie całkowitego końca.";
			link.l1 = "W takim razie nie traktuj tego jako część spadku, lecz jako dar od przystojnego mężczyzny.";
			link.l1.go = "give_cutlass_1";
		break;
		
		case "give_cutlass_1":
			dialog.text = "Kto to może być? Żartuję tylko! Dzięki za rozwianie moich mrocznych myśli, mój kapitanie.";
			link.l1 = "Jesteś godna najwspanialszej broni, Helen. Cieszę się, że ci się podoba.";
			link.l1.go = "give_cutlass_2";
		break;
		
		case "give_cutlass_2":
			dialog.text = "Obiecuję, że będę dużo trenować, aby stać się godnym tego ostrza!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GiveCutlass");
		break;
		
		case "arrive":
			dialog.text = "Mój kapitanie! Charlie!";
			link.l1 = "Charlie? To coś nowego! Cieszę się, że cię widzę, drogi.";
			link.l1.go = "arrive_1";
		break;

		case "arrive_1":
			dialog.text = "Przez przypadek popełniłam gafę, ha! Cieszę się, że też cię widzę...";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JungleDialog1");
		break;

		case "arrive_2":
			dialog.text = "Tak wiele o siostrzanej solidarności! Mój kapitanie, ja... naprawdę się martwiłam i tak bardzo za tobą tęskniłam!";
			link.l1 = "Więc po co musiałeś wracać do domu?";
			link.l1.go = "arrive_3";
		break;

		case "arrive_3":
			dialog.text = "To... Ach, racja! Mam dla ciebie mały prezent, tutaj!";
			link.l1 = "Trzy amulety... Eleno, dlaczego? Czy chciałaś mnie śledzić?";
			link.l1.go = "arrive_4";
			
			GiveItem2Character(pchar, pchar.questTemp.Saga.BaronReturn.Indian);
			GiveItem2Character(pchar, pchar.questTemp.Saga.BaronReturn.Amulet);
			GiveItem2Character(pchar, pchar.questTemp.Saga.BaronReturn.Obereg);
		break;

		case "arrive_4":
			dialog.text = "Podejdź tutaj, głupcze!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FirstKiss");
		break;

		case "after_kiss":
			dialog.text = "Nie waż się zepsuć tej chwili - wyobrażałam ją sobie przez całe życie!";
			link.l1 = "Nie zrobię tego, Helen.";
			link.l1.go = "after_kiss_a";
			link.l2 = "Całe życie czekałeś, żeby mnie poznać? Pochlebia mi to!";
			link.l2.go = "after_kiss_b";
			if (GetCharacterIndex("Mary") >= 0 && CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive") {
				link.l3 = "Helen,  jest coś... Na Wyspie Sprawiedliwości spotkałem kobietę, i...";
				link.l3.go = "after_kiss_c";
			}
			locCameraFromToPos(-19.00, 1.56, 19.07, true, -11.19, -0.90, 17.49);
		break;
		
		case "after_kiss_a":
			dialog.text = "Cholera jasna! Powiesz mi wszystko, wszystko! Będę czekać na ciebie na statku, mój kapitanie!";
			link.l1 = "Czekaj!...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterKiss1");
		break;
		
		case "after_kiss_b":
			dialog.text = "Głupcze! Chcesz mnie obrazić? Dobrze, jestem obrażona! Ha-ha! Pójdę na statek na razie, zanim Danny jeszcze bardziej mnie wyśmieje...";
			link.l1 = "Poczekaj!...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterKiss1");
		break;
		
		case "after_kiss_c":
			dialog.text = "Głupcze! Prosiłam cię, byś nie psuł chwili! Spotkałeś... cóż, spotkałeś - ale nie widzę pierścionka na twoim palcu. Ale nie myśl, że ci to ujdzie na sucho - będę czekać na szczegółową opowieść, gdy wrócisz na statek.";
			link.l1 = "Poczekaj!...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterKiss1");
		break;
		
		case "loot_good":
			dialog.text = "Mój kapitanie, co słychać? Widzę po twojej bladej twarzy, że prawnik postanowił dorzucić ci więcej problemów zamiast pomóc.";
			link.l1 = "Masz rację, Helen. Loxley zażądał imponującej zaliczki, a sama sprawa będzie mnie kosztować niemałą sumkę. Idę potrząsnąć Janem - mam tego dość! To tak, jakby Bractwo postanowiło przerzucić na mnie wszystkie swoje wydatki!";
			link.l1.go = "loot_good_1";
		break;
		
		case "loot_good_1":
			dialog.text = "Nie ma w tym złej woli, Charles. Tacy po prostu są - nie ruszą palcem, jeśli nie muszą. Jestem pewna, że Jan ci pomoże, a ja także nie będę stała bezczynnie.";
			link.l1 = "Wiem, Helen. Powiedz mi, co masz na myśli.";
			link.l1.go = "loot_good_2";
		break;
		
		case "loot_good_2":
			dialog.text = "Kiedyś pracowałam dla Jana - przemycałam cenne drewno po całym Maine. Ale jestem zaradną dziewczyną i podczas tych wszystkich podróży odłożyłam coś dla siebie.";
			link.l1 = "I Jan się nie dowiedział? Sprytnie!";
			link.l1.go = "loot_good_3";
		break;
		
		case "loot_good_3":
			dialog.text = "Miałam dobrego skarbnika. Krótko mówiąc, zebrałam przyzwoitą sumkę pieniędzy i schowałam ją niedaleko stąd. Idziesz teraz do Jana? W takim razie odwiedźmy San Juan del Norte. W pobliżu jest jaskinia, a będziemy potrzebować kilku marynarzy, żeby nam pomogli, abyśmy nie musieli wszystkiego dźwigać sami.";
			link.l1 = "Już wszystko rozgryzłeś, prawda? Dzięki, Helen, na pewno odwiedzimy, jeśli znajdziemy czas.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_CreateLoot");
		break;
		
		case "loot_bad":
			dialog.text = "Mój kapitanie, jakie wieści? Widzę po twojej bladej twarzy, że prawnik postanowił dorzucić ci więcej problemów zamiast pomóc.";
			link.l1 = "Masz rację, Helen. Loxley zażądał imponującej zaliczki, a sama sprawa będzie mnie kosztować niemałą sumkę. Idę potrząsnąć Janem - mam tego dość! Wygląda na to, że Bractwo postanowiło przerzucić na mnie wszystkie swoje wydatki!";
			link.l1.go = "loot_bad_1";
		break;
		
		case "loot_bad_1":
			dialog.text = "Czy myślałeś, że jesteś w bajce? Nie martw się, wszyscy jesteśmy na tym samym statku, a ja ci pomogę. W końcu mam prawo do spadku, prawda?";
			link.l1 = "To prawda... Powiedz mi, co ci chodzi po głowie!";
			link.l1.go = "loot_bad_2";
		break;
		
		case "loot_bad_2":
			dialog.text = "Mam coś schowanego w San Juan del Norte. Jest tam niedaleko jaskinia - wystarczy, że zbierzemy kilku żeglarzy, żeby nie musieć wszystkiego nosić sami.";
			link.l1 = "Już wszystko rozgryzłeś, prawda? Dzięki, Helen, na pewno odwiedzimy, jeśli będziemy mieli czas.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_CreateLoot");
		break;
		
		case "shdn":
			dialog.text = "To jest to, Charles! Ale musisz iść sam - nienawidzę jaskiń!";
			link.l1 = "Jak każde zamknięte przestrzenie, wiem, Helen. Poczekaj na mnie tutaj.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GoForLoot");
		break;
		
		case "shdn_ambush":
			dialog.text = "Mamy problem! Oddział żołnierzy idzie w tę stronę, i wyglądają groźnie. Uważaj, Charles, to nie są zwykli strażnicy przybrzeżni - jest z nimi francuski oficer! Proszę cię, tylko nie rób nic głupiego!";
			link.l1 = "Kiedy ja kiedykolwiek zrobiłem coś głupiego?!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_SpawnAmbushSoldiers");
		break;
		
		case "shdn_ambush_1":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6) {
				dialog.text = "Ha, druga opcja brzmi bardziej kusząco, ale mam nadzieję, że nie jesteś zbyt dumny z siebie, Charles?";
			} else {
				dialog.text = "Nie mogę powiedzieć, że jestem zaskoczona, Charles...";
			}
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog1");
		break;
		
		case "shdn_ambush_2":
			dialog.text = "Czy skończyłeś? Teraz moja kolej mówić!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_HelenKillFrancois");
		break;
		
		case "shdn_ambush_3":
			dialog.text = "Nazywam się Helen MacArthur! Kapitanie, wiesz, kim jestem i dla kogo pracuję! Poinformuj swoich ludzi, zwłaszcza tego eleganckiego głupca leżącego na ziemi, o dzisiejszych wynikach, które zaraz ogłoszę!";
			link.l1 = " ";
			link.l1.go = "exit";
			CharacterTurnToLoc(npchar, "quest", "richard");
			sld = CharacterFromID("HelenDrinking_Richard");
			CharacterTurnByChr(sld, npchar);
			
			AddDialogExitQuestFunction("HelenDrinking_AfterFrancoisDeath2");
		break;
		
		case "shdn_ambush_4":
			dialog.text = "Protest? Nie obchodzi mnie, czy napiszesz do samego Cromwella. Po pierwsze, Monsieur de Maure nie stracił dziś honoru.";
			link.l1 = "";
			link.l1.go = "shdn_ambush_5";
			CharacterTurnToLoc(npchar, "quest", "richard");
		break;
		
		case "shdn_ambush_5":
			dialog.text = "Po drugie, pułkownik de Tavann został postrzelony przez dziewczynę w bardzo pikantnym stroju za nazwanie jej prostytutką.";
			link.l1 = "";
			link.l1.go = "shdn_ambush_6";
		break;
		
		case "shdn_ambush_6":
			dialog.text = "Po trzecie, natychmiast wycofujesz swoich żołnierzy i zapominasz o tym, co się stało, chyba że chcesz, aby Lasowy Diabeł się o tym dowiedział.";
			link.l1 = "";
			link.l1.go = "shdn_ambush_7";
		break;
		
		case "shdn_ambush_7":
			locCameraSleep(false);
			dialog.text = "Nie ma pytań, jak widzę. Miłego dnia, Kapitanie.";
			link.l1 = "Panie Boże, Helen, jesteś w ogniu!";
			link.l1.go = "shdn_ambush_8";
		break;
		
		case "shdn_ambush_8":
			dialog.text = "Później, Charles. Wynośmy się stąd, zanim otrząsną się z szoku. Ja też cała się trzęsę. Możemy porozmawiać w Blueweld?";
			link.l1 = "Zgoda.";
			link.l1.go = "exit";
			CharacterTurnByChr(npchar, pchar);
			
			AddDialogExitQuestFunction("HelenDrinking_AfterFrancoisDeath3");
		break;
		
		case "duel_victory":
			dialog.text = "Ucieknijmy stąd, zanim otrząsną się z szoku. Musimy jeszcze odzyskać ironwood, pamiętasz? Możemy porozmawiać w Blueweld.";
			link.l1 = "Wow!  Nawet bez gratulacji?  Dobrze, chodźmy.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_DuelVictory1");
		break;
		
		case "after_cave":
			dialog.text = "W końcu, dom...";
			link.l1 = "Co myślisz o tym, co się stało?";
			link.l1.go = "after_cave_1";
		break;
		
		case "after_cave_1":
			dialog.text = "Nie rozumiem pojedynków. Męska rozrywka, zwykle kończąca się dwoma trupami, a w szczęśliwy dzień, nawet więcej. A honor... Wierzę, że honor buduje się na pragnieniu unikania konfliktu aż do samego końca, bo rzadko jest tego wart. Ha! Posłuchaj tylko - gadam jakieś bzdury!";
			link.l1 = "To interesująca perspektywa, Helen. Chociaż nie każdy by się z nią zgodził.";
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Duel")) {
				link.l1.go = "after_cave_duel";
			} else {
				link.l1.go = "after_cave_notduel";
			}
		break;
		
		case "after_cave_duel":
			dialog.text = "Żal, że dałeś się wciągnąć w ich gierki. Pułkownik był wyraźnie opętany, a reszta tylko pragnęła widowiska i materiału do plotek. Cóż, nie będę się nad tym rozwodzić - i tak już dziś wystarczająco się nacierpiałeś.";
			link.l1 = "Tak, po pojedynkach zawsze jest uczucie pustki. Wystarczy przygód na dzisiaj. Co chcesz robić dalej?";
			if (sti(pchar.questTemp.Saga.HelenRelation) == 7 || sti(pchar.questTemp.Saga.HelenRelation) == 8) {
				link.l1.go = "after_cave_mild";
			} else {
				if (sti(pchar.questTemp.Saga.HelenRelation) < 7) {
					link.l1.go = "after_cave_cold";
				} else {
					link.l1.go = "after_cave_lewd";
				}
			}
		break;
		
		case "after_cave_notduel":
			dialog.text = "Ach! Chciałam tylko powiedzieć, że jestem z nas dumna. Pokazałeś dziś prawdziwą odwagę, mój kapitanie. Nie uległeś histerii załogi, która chciała cię po raz pierwszy dowodzić. Wytrzymałeś wobec pozorów czerwonego munduru i obsesji niebieskiego. Pułkownik wyraźnie szukał śmierci, ale dostał jedynie ranę w nieodpowiednim miejscu, ha-ha!";
			link.l1 = "Dzięki, Helen. Świetnie wyprowadziłaś nas z opałów, jak prawdziwy oficer marynarki. Czy jesteś z siebie dumna?";
			link.l1.go = "after_cave_notduel_1";
		break;
		
		case "after_cave_notduel_1":
			dialog.text = "Tak, tego mi było trzeba. Szkoda tylko, że to był niebieski mundur, a nie czerwony, ale przynajmniej osoba, która go nosiła, dostała, na co zasłużyła.";
			link.l1 = "Ta osoba jest rzeczywiście nieistotna, przyznaję. Dość przygód na dziś. Co chcesz robić dalej?";
			if (sti(pchar.questTemp.Saga.HelenRelation) == 7 || sti(pchar.questTemp.Saga.HelenRelation) == 8) {
				link.l1.go = "after_cave_mild";
			} else {
				if (sti(pchar.questTemp.Saga.HelenRelation) < 7) {
					link.l1.go = "after_cave_cold";
				} else {
					link.l1.go = "after_cave_lewd";
				}
			}
		break;
		
		case "after_cave_mild":
			dialog.text = "Wracam do domu, mój kapitanie. Tęskniłam za moją mamą... Gladys. Szkoda, że jest teraz w domu, inaczej zaprosiłabym cię do siebie!";
			link.l1 = "Rzeczywiście, to wstyd!";
			link.l1.go = "after_cave_mild_1";
		break;
		
		case "after_cave_mild_1":
			dialog.text = "Nie bądź taki przygnębiony. Wkrótce, mój drogi. W międzyczasie...";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_SecondKiss");
		break;
		
		case "after_second_kiss":
			locCameraFromToPos(4.97, 3.71, 16.06, true, 5.09, 1.25, 11.67);
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Kiss")) {
				dialog.text = "M-m-m, ten jest nawet lepszy niż nasz pierwszy. Pamiętasz? Przy bożku?";
				link.l1 = "To nie jest coś, co można zapomnieć, drogi.";
				link.l1.go = "after_second_kiss_1";
			} else {
				dialog.text = "Tylko nie waż się zepsuć tej chwili - wyobrażałam ją sobie przez całe życie!";
				link.l1 = "Nie zrobię tego, Helen.";
				link.l1.go = "after_second_kiss_a";
				link.l2 = "Całe życie czekałeś, by mnie poznać? Schlebia mi to!";
				link.l2.go = "after_second_kiss_b";
			}
		break;
		
		case "after_second_kiss_1":
			dialog.text = "Ohh! Weź się w garść, dziewczyno! Do następnego spotkania, mój kapitanie.";
			link.l1 = "Do tego czasu, Helen.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveMild");
		break;
		
		case "after_second_kiss_a":
			dialog.text = "Do diabła, racja! Wkrótce się zobaczymy, mój kapitanie.";
			link.l1 = "Do zobaczenia, Helen. O Boże, cóż za dziewczyna...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveMild");
		break;
		
		case "after_second_kiss_b":
			dialog.text = "Idioto! Chcesz mnie obrazić? Dobrze, jestem obrażona! Ha-ha! Zobaczymy się wkrótce, mój kapitanie.";
			link.l1 = "Do zobaczenia, Helen. O Boże, cóż za dziewczyna...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveMild");
		break;
		
		case "after_cave_cold":
			dialog.text = "Wracam do domu, Kapitanie. Przypuszczam, że kwestia pieniędzy z prawnikiem jest teraz rozwiązana? Czekają nas trudne przeszkody, więc postarajmy się unikać kłopotów od teraz. Kłopoty znajdą nas same.";
			link.l1 = "O rany, naprawdę?";
			link.l1.go = "after_cave_cold_1";
		break;
		
		case "after_cave_cold_1":
			dialog.text = "Przepraszam za szczerość, Kapitanie. Mój los również teraz się waży, wiesz.";
			link.l1 = "Znam, spróbuję poradzić sobie z tym jak najgodniej. Do zobaczenia na statku, Helen.";
			link.l1.go = "after_cave_cold_2";
		break;
		
		case "after_cave_cold_2":
			dialog.text = "Tak jest, Kapitanie!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveCold");
		break;
		
		case "after_cave_lewd":
			dialog.text = "Co dalej? Pokażę ci.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_SecondKiss");
		break;
		
		case "after_second_kiss1":
			locCameraFromToPos(4.97, 3.71, 16.06, true, 5.09, 1.25, 11.67);
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Kiss")) {
				dialog.text = "M-m-m, ten jest nawet lepszy niż nasz pierwszy. Pamiętasz? Przy bożku?";
				link.l1 = "To nie jest coś, co się zapomina, drogi.";
				link.l1.go = "after_second_kiss1_1";
			} else {
				dialog.text = "Nie waż się zepsuć tej chwili - wyobrażałam ją sobie przez całe życie!";
				link.l1 = "Nie zrobię tego, Helen.";
				link.l1.go = "after_second_kiss1_a";
				link.l2 = "Czekałeś całe życie, by mnie spotkać? Pochlebia mi to!";
				link.l2.go = "after_second_kiss1_b";
			}
		break;
		
		case "after_second_kiss1_1":
			dialog.text = "Cholernie prawda! Wow! Gladys nie ma teraz w domu. Chcesz wejść?";
			link.l1 = "Zapraszasz mnie do siebie? A czym się zajmiemy?";
			link.l1.go = "after_cave_lewd_accept";
			if (GetCharacterIndex("Mary") >= 0 && CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive") {
				link.l2 = "Nie, Helen. Inna kobieta czeka na mnie na Wyspie Sprawiedliwości. Nie mogę jej tego zrobić.";
				link.l2.go = "after_cave_lewd_refuse_mary";
			}
			link.l3 = "Innym razem, mój drogi. Naprawdę tego pragnę, ale dzisiaj prawie mnie to wykończyło. Nadrobimy zaległy czas dziesięciokrotnie.";
			link.l3.go = "after_cave_lewd_refuse_head";
		break;
		
		case "after_second_kiss1_a":
			dialog.text = "Cholera, zgadza się! Łał! Gladys nie ma teraz w domu. Chcesz wejść?";
			if (GetCharacterIndex("Mary") >= 0 && CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive") {
				link.l1 = "Nie, Helen. Inna kobieta czeka na mnie na Wyspie Sprawiedliwości. Nie mogę jej tego zrobić.";
				link.l1.go = "after_cave_lewd_refuse_mary";
			}
			link.l2 = "Innym razem, mój drogi. Naprawdę tego pragnę, ale dzisiaj prawie mnie to wykończyło. Nadrobimy i zrekompensujemy stracony czas dziesięciokrotnie.";
			link.l2.go = "after_cave_lewd_refuse_head";
			link.l3 = "Zapraszasz mnie do siebie? I co będziemy robić?";
			link.l3.go = "after_cave_lewd_accept";
		break;
		
		case "after_second_kiss1_b":
			dialog.text = "Głupcze! Chcesz mnie obrazić? Dobrze, jestem obrażona! Ha-ha! Będziesz musiał to naprawić, mój kapitanie. Wow! Gladys nie ma teraz w domu. Chcesz wejść?";
			if (GetCharacterIndex("Mary") >= 0 && CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive") {
				link.l1 = "Nie, Helen. Inna kobieta czeka na mnie na Wyspie Sprawiedliwości. Nie mogę jej tego zrobić.";
				link.l1.go = "after_cave_lewd_refuse_mary";
			}
			link.l2 = "Innym razem, mój drogi. Naprawdę tego pragnę, ale dzisiaj prawie mnie to wykończyło. Nadrobimy i zrekompensujemy stracony czas dziesięciokrotnie.";
			link.l2.go = "after_cave_lewd_refuse_head";
			link.l3 = "Zapraszasz mnie? A co będziemy robić?";
			link.l3.go = "after_cave_lewd_accept";
		break;
		
		case "after_cave_lewd_refuse_mary":
			dialog.text = "Ach, więc nie jestem wystarczająco biegły w sztuce uwodzenia? A ona jest? Kim ona jest?";
			link.l1 = "Jej imię to Mary Casper, i ją kocham.";
			link.l1.go = "after_cave_lewd_refuse_mary_1";
		break;
		
		case "after_cave_lewd_refuse_mary_1":
			dialog.text = "„Ten rudzielec w czerwonym mundurze? W czerwonym mundurze... Cóż, jeśli potrzebowałam znaku, to jest on tutaj. To nie miało się wydarzyć. I nie martw się, Kapitanie, to nie wpłynie na moją służbę na twoim statku.”";
			link.l1 = "Przykro mi, Helen.";
			link.l1.go = "exit";
			
			pchar.questTemp.HelenDrinking.Mary = true;
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveRefuseMary");
		break;
		
		case "after_cave_lewd_refuse_head":
			dialog.text = "O, mój kapitanie! Niebezpiecznie jest zostawić kobietę w takim stanie! Trzymam cię za słowo, a teraz uciekaj... Muszę teraz być sama i spróbować poradzić sobie z moim problemem... na własną rękę! Do zobaczenia na statku!";
			link.l1 = "Co za dziewczyna!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveRefuseMild");
		break;
		
		case "after_cave_lewd_accept":
			dialog.text = "Nie martw się, moja droga, poprowadzę cię, jeśli się zgubisz.";
			link.l1 = "No to... prowadź!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveAccept");
		break;
		
		case "after_cave_bedroom":
			dialog.text = "Nie mów nic, błagam cię.";
			link.l1 = "...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveSex1");
		break;
		
		case "after_cave_sex":
			dialog.text = "... oczywiście, do dziś, moje rozumienie tego tematu opierało się wyłącznie na wulgarnych rozmowach załogi 'Tęczy', jeśli można to w ogóle nazwać rozmowami, oczywiście.";
			link.l1 = "I jak było? Czy rzeczywistość spełniła twoje oczekiwania?";
			link.l1.go = "after_cave_sex_1";
		break;
		
		case "after_cave_sex_1":
			dialog.text = "Bardzo mi się to podobało, ale czuję, że nie doświadczyłam tego w pełni. I jakże...";
			link.l1 = "Pokażę ci! Czy możemy kontynuować?";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveSex2");
		break;
		
		case "after_cave_sex_again":
			dialog.text = "Och, teraz rozumiem! To było po prostu cudowne, mój kapitanie!";
			link.l1 = "Zaskoczyłeś mnie, delikatnie mówiąc!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveGladysEnter");
		break;
		
		case "after_cave_gladys":
			dialog.text = "Ha-ha-ha! To dopiero dobre! Teraz albo zatka uszy woskiem, albo pobiegnie na najwyższą platformę fortu!";
			link.l1 = "To było niespodziewane, ale bardzo zabawne, ah-ha-ha!";
			link.l1.go = "after_cave_gladys_1";
			locCameraFromToPos(-0.62, 1.93, -0.39, true, -2.46, -1.20, 1.01);	// Sinistra - постельная камера
		break;
		
		case "after_cave_gladys_1":
			dialog.text = "Gotowy, mój kapitanie?";
			link.l1 = "Już?! Nie, Helen, miej litość nade mną, proszę. Nagłe pojawienie się Gladys zdecydowanie nie poprawiło atmosfery.";
			link.l1.go = "after_cave_gladys_2";
		break;
		
		case "after_cave_gladys_2":
			dialog.text = "Cóż, co możesz zrobić... Chociaż...";
			link.l1 = "Nie, nie, opuść żagle!";
			link.l1.go = "after_cave_gladys_3";
		break;
		
		case "after_cave_gladys_3":
			dialog.text = "Dobrze, więc zostańmy razem przez chwilę. Nasza przyszłość jest taka mroczna i przerażająca, ale po raz pierwszy od dłuższego czasu nie boję się niczego innego. Wiem, że jakiś nowy strach się wkradnie, ale nie dzisiaj. Nie dzisiaj, mój kapitanie.";
			link.l1 = "Nie dzisiaj, mój drogi. Nie dzisiaj.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveFin");
		break;
		
		case "give_potions":
			dialog.text = "Pozwolenie na rozmowę, kapitanie?";
			link.l1 = "Tak, Helen?";
			link.l1.go = "give_potions_1";
		break;
		
		case "give_potions_1":
			dialog.text = "Znam tego Snake Eye - to dobry człowiek, ale trochę dziwny. Regularnie wysyła ludzi na misje, Bóg wie po co. Widzę, że i ty dostąpiłeś tego wątpliwego zaszczytu.";
			if (!CheckAttribute(CharacterFromID("SnakeEye"), "quest.amulet")) {
				link.l1 = "Zgadza się, muszę przynieść mu trzy amulety, inaczej nie będzie mógł mi pomóc dostać się do miejsca Jastrzębia. Ale wiesz, co jest zabawne? Już je miałem przy sobie! Może wiedział o tym od samego początku?";
				link.l1.go = "give_potions_already";
			} else {
				link.l1 = "Zgadza się, muszę mu przynieść trzy amulety, inaczej nie będzie w stanie pomóc mi dostać się do miejsca Hawk'a. Nie mogę teraz zrozumieć, gdzie je znaleźć, a czas ucieka.";
				link.l1.go = "give_potions_3";
			}
		break;
		
		case "give_potions_already":
			dialog.text = "Och, co za wstyd! Cieszę się, że nie musiałeś biegać za tymi amuletami od latarników, ale miałam nadzieję, że chociaż raz mogę być ci użyteczna, chciałam się wykazać.";
			link.l1 = "Bzdura, Helen. Nie musisz mi niczego udowadniać.";
			link.l1.go = "give_potions_4";
		break;
		
		case "give_potions_3":
			dialog.text = "Pomogę ci! Przyznaję, miałam nadzieję, że choć raz mogłabym być dla ciebie użyteczna, liczyłam na to, że się sprawdzę.";
			link.l1 = "Bzdury, Heleno. Nie musisz mi niczego udowadniać.";
			link.l1.go = "give_potions_4";
		break;
		
		case "give_potions_4":
			dialog.text = "Niemniej jednak, chcę ci pomóc. Proszę, weź klucz do mojego pokoju... to znaczy, do skrzyni w moim pokoju! Niewiele tam jest, ale tobie się przyda. I... Charles, postaraj się teraz nie wybuchnąć śmiechem!";
			link.l1 = "Ahem, nie zamierzałem tego robić. Widzę, że interesujesz się takimi rzeczami?";
			link.l1.go = "give_potions_5";
		break;
		
		case "give_potions_5":
			dialog.text = "Jestem żeglarzem, mój kapitanie, tak jak ty. W naszym fachu musimy zrobić wszystko, co w naszej mocy, by zdobyć przychylność Pani Szczęścia.";
			link.l1 = "Dziękuję, Helen. Naprawdę to doceniam.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GivePotionsKey");
		break;
		
		case "upgrade":
			dialog.text = "Kochańku, mam dla ciebie prezent!";
			link.l1 = "Widzę, oto jest - stoi i uśmiecha się!";
			link.l1.go = "upgrade_1";
		break;
		
		case "upgrade_1":
			dialog.text = "Ha-ha, przestań! Kiedyś dostarczyłam niezłą partię jedwabiu lokalnemu szkutnikowi, więc teraz jest mi winien całkowitą modernizację statku. Myślałam o oddaniu mu 'Tęczy' do tej roboty, ale to się nie udało. Twój statek natomiast mógłby naprawdę skorzystać z takiej opieki, nie sądzisz?";
			link.l1 = "Rzeczywiście, wspaniały podarunek, Helen - w sam raz dla ciebie!";
			link.l1.go = "upgrade_2";
		break;
		
		case "upgrade_2":
			dialog.text = "Jestem zadowolona, że ci się podoba. Odwiedź go w każdej chwili i powiedz mu, że cię przysłałam. Zrobią wszystko, co w ich mocy.";
			link.l1 = "Zdecydowanie!";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Helena_officer";
			AddDialogExitQuestFunction("HelenUpgradeShip1");
		break;
		
		case "give_sex":
			dialog.text = "Pozwolenie na rozmowę, mój kapitanie?";
			link.l1 = "Oczywiście, mój drogi.";
			link.l1.go = "give_sex_1";
		break;
		
		case "give_sex_1":
			dialog.text = LinkRandPhrase("Twoja dama tęskni za tobą i domaga się uwagi. Czy mogę poprosić o zorganizowanie dla niej pokoju i poświęcenie jej trochę czasu?","Zgłaszam: twoja obecność jest wymagana w łóżku w lokalnej tawernie. Tylko pięć minut twojego czasu, ale załoga ma nadzieję, że zostaniesz dłużej!","Bunt na statku, mój kapitanie! Mam za zadanie wręczyć ci czarną plamę w prywatnych okolicznościach. Idź ze mną natychmiast!");
			link.l1 = "Ha-ha, ahem! Twoja prośba została spełniona, Oficerze Sharp!";
			link.l1.go = "give_sex_1_yes";
			link.l2 = "Nie dzisiaj, drogi. Za dużo się teraz dzieje.";
			link.l2.go = "give_sex_1_no";
		break;
		
		case "give_sex_1_yes":
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
			DialogExit();
			AddDialogExitQuestFunction("Helen_GiveSexGoToTavern");
		break;
		
		case "give_sex_1_no":
			dialog.text = "Och, a co biedna dziewczyna ma zrobić, co? Dobrze, mój drogi, innym razem zatem.";
			link.l1 = "";
			link.l1.go = "give_sex_2_no";
		break;
		
		case "give_sex_2_no":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			npchar.location = "None";
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetOfficerType(npchar);
			chrDisableReloadToLocation = false;
			
			pchar.quest.Helen_GiveSex.win_condition.l1 = "Timer";
			pchar.quest.Helen_GiveSex.win_condition.l1.date.day = GetAddingDataDay(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l1.date.month = GetAddingDataMonth(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l1.date.year  = GetAddingDataYear(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l2 = "Location_Type";
			pchar.quest.Helen_GiveSex.win_condition.l2.location_type = "town";
			pchar.quest.Helen_GiveSex.function = "Helen_GiveSex";
		break;
		
		case "special_sex":
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
			SaveCurrentNpcQuestDateParam(npchar, "special_sex_date");
			
			dialog.text = "Ha! Nie musisz pytać mnie dwa razy! Oczywiście, ruszajmy!";
			link.l1 = " ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Helen_GiveSexGoToTavern");
		break;
		
		case "rainbow":
			dialog.text = "Zaraz wyrzucę cię za burtę!";
			link.l1 = "Hej, hej, hej! Spokojnie, moja droga!";
			link.l1.go = "rainbow_1";
		break;
		
		case "rainbow_1":
			dialog.text = "Chodź tutaj, łotrze!";
			link.l1 = "Żartowałem, Helen! Nie chciałem cię obrazić!";
			link.l1.go = "rainbow_2";
		break;
		
		case "rainbow_2":
			dialog.text = "O, naprawdę? Ssij kpiarzu...";
			link.l1 = "Jesteś najpiękniejsza, i szaleńczo cię kocham!";
			link.l1.go = "rainbow_3";
		break;
		
		case "rainbow_3":
			dialog.text = "Zgub się, Charles.";
			link.l1 = "";
			link.l1.go = "exit";
			
			DeleteAttribute(pchar, "questTemp.HelenDrinking.Rainbow");
			Achievment_Set("ach_CL_84");
		break;
		
		case "joan":
			dialog.text = "To ty jesteś ladacznicą! Ciesz się, że Jan uczynił z ciebie uczciwą kobietę, bo inaczej wciąż rozkładałabyś nogi przed każdym przechodniem!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JoanDialog2");
		break;
		
		case "joan_1":
			dialog.text = "Jawnogrzesznica! Chodźmy, Charles!";
			link.l1 = "...";
			link.l1.go = "exit";
			
			ResetSound();
			SetMusic("helendrinking_shanty");
			pchar.questTemp.lockedMusic = true;
			AddDialogExitQuestFunction("HelenDrinking_GoToFort");
		break;
		
		case "cutlass_training":
			dialog.text = "Szabla leży idealnie w mojej dłoni! Nie wiem, jak to wyjaśnić... Zawsze miałam trudności z innymi rodzajami broni białej, jak rapiry i miecze. Ale ta szabla to inna historia! Czuję się wspaniale! Dziękuję, Charles!";
			link.l1 = "Przeznaczenie ma sposób na odnalezienie nas. Cieszę się z twojego powodu, Helen!";
			link.l1.go = "exit";
			notification("Medium Weapons +", "Helena");
		break;
		
		case "brothel_found":
			dialog.text = "Zachowaj swoje opowieści dla kogoś innego, na mnie nie zadziałają. Czy wyglądam na naiwnego, zakochanego głupca? No cóż, JESTEM w tobie szaleńczo zakochana, ale nazwanie mnie głupcem byłoby przesadą\n Słuchaj, kochanie, rób co chcesz, ale miej na uwadze, że nie znajdziesz lepszej kobiety niż ja. Jeśli chcesz jej szukać w burdelach, proszę bardzo, ale wtedy zniknę z twojego życia na zawsze.";
			link.l1 = "Helen, ja...";
			link.l1.go = "brothel_found_1";
		break;
		
		case "brothel_found_1":
			dialog.text = "Rozumiem wszystko, Charles. Kochasz tylko mnie, a to są tylko naturalne popędy. Wiesz, jaki jest mój naturalny popęd? Szacunek od mojego mężczyzny. Kobieta może nie być zadowolona tylko z miłości, kochanie. Zapomnijmy teraz o tym nieporozumieniu, ale zastanów się trochę nad moimi słowami. Dobrze?";
			link.l1 = "Dobrze, Helen.";
			link.l1.go = "exit";
		break;
		
		case "refuse":
			dialog.text = "Wiesz, jak to jest. Najpierw daj dziewczynie ostygnąć.";
			link.l1 = "Wzdych...";
			link.l1.go = "exit";
		break;
		
		// Тайна Порт-Рояля
		case "MysteryPortRoyal_Helena_1":
			dialog.text = "Francis... pamiętam go. Zawsze czekał na mój przyjazd do Port Royal i był niepoprawnym romantykiem. Miło było spędzać czas z kimś, kto nie miał nic wspólnego z morzem – te wszystkie wiersze i serenady... To było coś nowego. Przebłysk świata, którego nigdy nie znałam\nFrancis był bogaty, inteligentny i przystojny – świetna partia. Każda dziewczyna tutaj straciłaby dla niego głowę, ale wtedy miałam ważniejsze sprawy – utrzymać Tęczę na wodzie.";
			link.l1 = "Wszystkie jego listy były o tobie. Mogę ci oddać wszystko, co ci zostawił, jeśli chcesz.";
			link.l1.go = "MysteryPortRoyal_Helena_2";
		break;
		
		case "MysteryPortRoyal_Helena_2":
			dialog.text = "Nie wiedziałam, że był chory. To wszystko jest takie głupie. Co do jego daru... Mam już wszystko, czego mi trzeba. Zatrzymaj to.";
			link.l1 = "Jego dziedzictwo i tak ci się przysłuży – czyli spełniłem jego ostatnią wolę. Ciekawa historia.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.MysteryPortRoyal_Helena");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}

bool HelenDrinking_RobbedSvenson() {
	sld = &locations[FindLocation("SantaCatalina_houseS1_residence")];
	if (!CheckAttribute(sld, "private1.items.chest")) { 
		return true;
	}
	
	if (sti(sld.private1.items.chest) < 2) {
		return true;
	}
	
	return false;
}

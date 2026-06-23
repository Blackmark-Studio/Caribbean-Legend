// Хенрик Ведекер. Он же Механик.
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Dzień dobry, panie. Nigdy wcześniej cię nie widziałem. Jesteś nowicjuszem? I czy to pierwszy raz, gdy postanowiłeś odwiedzić tę platformę?";
				link.l1 = TimeGreeting()+". Nazywam się "+GetFullName(pchar)+" Jestem tu nowicjuszem i po prostu rozglądam się, poznaję ludzi...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				if (pchar.questTemp.LSC == "platinum_wait")
				{
					dialog.text = "Słuchaj, "+pchar.name+"jeśli będziesz mnie ciągle rozpraszać, nigdy nie skończę napraw.";
					link.l1 = "Tak, tak, pamiętam to. Przepraszam, że sprawiłem ci kłopot!";
					link.l1.go = "exit";
					break;
				}
				// возвращение блудного скафандра
				if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
				{
					dialog.text = "Ach! Spójrzcie tylko na to! Utopiec wrócił z innego świata! Teraz powiedz mi, jak udało ci się zrobić taki trik? Odprawili ci pogrzeb i pochowali cię pod twoją nieobecność, na wypadek gdybyś nie wiedział...";
					link.l1 = "Szkoda, ale jeszcze nie zamierzam umierać. Sztuczka jest prosta - dotknąłem tylko idola Kukulkana na dnie. Teleportował mnie na Dominikę, prosto do wioski Karibów...";
					link.l1.go = "return";
					break;
				}
				
				dialog.text = "Ach, "+GetFullName(pchar)+"! "+TimeGreeting()+"!";
				// квестовые ветки
				if(pchar.questTemp.LSC == "mechanic")
				{
					link.l4 = "Henrik,   mam dla ciebie interes. Bardzo ważny interes. Ole Christiansen mi o tobie opowiedział. Nazywają go także Białym Chłopcem.";
					link.l4.go = "mechanic_1";
				}
				if(pchar.questTemp.LSC == "platinum" && GetCharacterItem(pchar, "jewelry10") >= 11)
				{
					link.l4 = "Henrik, przyniosłem ci wystarczającą ilość 'srebra'. Dokładnie tak, jak prosiłeś: jeden twój plus dodatkowe dziesięć sztuk. Proszę, weź je.";
					link.l4.go = "mechanic_15";
				}
				if(pchar.questTemp.LSC == "underwater_check")
				{
					link.l4 = "Znowu ja, Henrik. Jak tam twój strój? Udało ci się go naprawić?";
					link.l4.go = "mechanic_20";
				}
				if(pchar.questTemp.LSC == "platinum_add_wait" && GetCharacterItem(pchar, "jewelry10") >= int(pchar.questTemp.LSC.PtAddQty))
				{
					link.l4 = "Mam wystarczająco dużo metalu, tego, o który prosiłeś. Weź to.";
					link.l4.go = "mechanic_23";
				}
				if(pchar.questTemp.LSC == "underwater_prepare")
				{
					link.l4 = "Dzień dobry, Henrik. No i co, czy skafander gotowy do nurkowania?";
					link.l4.go = "immersion";
				}
				if(pchar.questTemp.LSC == "underwater_natan" && CheckAttribute(pchar, "questTemp.LSC.NatanTalk"))
				{
					link.l4 = "To koniec, poradziłem sobie z problemami i jestem gotów nurkować. Kiedy zaczynamy?";
					link.l4.go = "immersion_1";
				}
				if(CheckAttribute(pchar, "questTemp.LSC.UW_ready"))
				{
					link.l5 = "Cześć, Henrik. No i co, czy skafander gotowy do nurkowania?";
					link.l5.go = "immersion_next";
				}
				if(CheckAttribute(pchar, "questTemp.LSC.UW_end") && CheckCharacterItem(pchar, "underwater"))
				{
					link.l5 = "Chcę zwrócić twój garnitur.";
					link.l5.go = "immersion_next_2";
				}
				// квестовые ветки				
				link.l1 = LinkRandPhrase("Masz coś ciekawego do powiedzenia?","Czy coś nowego wydarzyło się na wyspie?","Opowiesz mi najnowsze plotki?");
				link.l1.go = "rumours_LSC";
				link.l3 = "Chciałem tylko wiedzieć, jak się masz.";
				link.l3.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "I ja jestem Henrik Vedecker. Jednak większość miejscowych zna mnie jako Mechanika i jest to bardzo trafne określenie, w istocie.";
			if(pchar.questTemp.LSC == "mechanic")
			{
				link.l1 = "Czy to ty, Henrik Vedecker? Miło cię poznać! Szukałem cię.";
				link.l1.go = "mechanic";
			}
			else
			{
				link.l1 = "Ty musisz być mistrzem wszystkich fachów, prawda?";
				link.l1.go = "meeting_1";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting_1":
			dialog.text = "Ach, tak, Narwale naprawdę doceniają moje umiejętności. Moje narzędzia pozwalają im zdobywać wiele cennych rzeczy z zatopionych statków na zewnętrznym pierścieniu, dzięki czemu mogą kupować zaopatrzenie od admirała Dodsona\nWłaściwie nauka i eksploracje są moją pasją. Dlatego przepraszam, jeśli nie będę mógł poświęcić ci wystarczająco dużo czasu - moje eksperymenty pochłaniają prawie cały mój czas.";
			link.l1 = "Rozumiem. Nie będę cię niepokoił bez powodu, panie Vedecker, zapewniam cię. Bardzo się cieszę, że cię poznałem!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "mechanic":
			dialog.text = "Byłeś? A dlaczego?";
			link.l1 = "Ole Christiansen opowiedział mi o tobie. Nazywają go także Białym Chłopcem.";
			link.l1.go = "mechanic_1";
		break;
		
		case "mechanic_1":
			dialog.text = "Ach, ten zabawny gość! Tak, tak, znam go. A co ci powiedział?";
			link.l1 = "Przepraszam, jeśli moje następne pytanie wyda się głupie, ale... i tak je zadam. Ole powiedział mi, że możesz nauczyć mnie, jak nurkować na dno, pod wodą. Proszę, nie śmiej się ze mnie, jeśli to tylko jego wyobraźnia.";
			link.l1.go = "mechanic_2";
		break;
		
		case "mechanic_2":
			dialog.text = "To prawda. Sam byłem na dnie kilka razy. Choć już nie nurkuję, ławica roi się teraz od olbrzymich krabów i, oczywiście, jak widać, nie jestem w stanie z nimi walczyć, jestem naukowcem, nie mogę walczyć z tymi stworzeniami.\nPoza tym, byli też dwaj inni ludzie, dwóch Narwali, którzy zwykli nurkować, ale w końcu przestali to robić - plądrowanie ładowni statków z zewnętrznego pierścienia okazało się bezpieczniejsze niż nurkowanie w miejscu zainfekowanym olbrzymimi krabami\nTeraz rzadko korzystają z mojego sprzętu, ani jednego nurkowania przez ostatnie kilka miesięcy z powodu pęknięcia w skafandrze...";
			link.l1 = "Naprawdę masz skafander, w którym możesz zanurkować na dno? Czy źle cię usłyszałem?";
			link.l1.go = "mechanic_3";
		break;
		
		case "mechanic_3":
			dialog.text = "Twoje uszy są na właściwym miejscu, młodzieńcze. Sam wymyśliłem i wykonałem ten strój. Jest zrobiony z grubej, całkowicie wodoodpornej tkaniny, części metalowych i stalowego hełmu, który wykułem razem z Jurgenem w jego kuźni\nDodatkowo wzmocniłem strój metalową płytą na piersi, nakolannikami, ochraniaczami na klatkę piersiową i butami dla lepszej ochrony przed krabami oraz dodatkowym obciążeniem\nSpecjalne zbiorniki, wypełnione sprężonym powietrzem, zapewniają funkcję podtrzymywania życia i możliwość spędzenia trochę czasu pod wodą. Strój jest unikalny i jestem z niego całkiem dumny.";
			link.l1 = "To wspaniale. Ale czy wspomniałeś, że ten strój jest uszkodzony?";
			link.l1.go = "mechanic_4";
		break;
		
		case "mechanic_4":
			dialog.text = "Niestety, tak jest. Kilka części skafandra było połączonych metalowymi płytami, aby osiągnąć elastyczność i dodatkową ochronę, ale woda morska źle na nie wpłynęła. Płyty rdzewiały przez lata użytkowania i straciły swoje zdolności ochronne przed wodą\nDobrze, że zauważyłem uszkodzenie i zapobiegłem śmierci ludzi. Nawet suchy skafander zawierał trochę soli i wody, które całkowicie dokończyły swoje złe dzieło.";
			link.l1 = "Cóż... Ale możesz naprawić ten strój! Możesz zastąpić stare, zardzewiałe części nowymi... Prawda?";
			link.l1.go = "mechanic_5";
		break;
		
		case "mechanic_5":
			dialog.text = "Po co? Żeby znowu ich zastąpić za rok? Wiesz, jak trudna jest ta praca? Składać strój z elastycznymi złączami i uczynić go wodoodpornym? To co najmniej tydzień pracy bez odpoczynku.";
			link.l1 = "I to jest powód, dla którego jesteś gotów wyrzucić swój wynalazek?";
			link.l1.go = "mechanic_6";
		break;
		
		case "mechanic_6":
			dialog.text = "Nie, oczywiście że nie. Mam pomysł. Muszę wykonać połączenia z metalu, który nie może zostać zniszczony przez wodę i sól. I wiem, jaki metal może pomóc...";
			link.l1 = "Więc w czym tkwi problem?";
			link.l1.go = "mechanic_7";
		break;
		
		case "mechanic_7":
			dialog.text = "Problem polega na tym, że ten metal jest bardzo rzadki. Mam tylko jeden kawałek, co z pewnością nie wystarczy. Potrzebuję co najmniej dziesięciu dodatkowych kawałków, a nawet piętnastu.";
			link.l1 = "A cóż to za... metal, o którym mówisz?";
			link.l1.go = "mechanic_8";
		break;
		
		case "mechanic_8":
			dialog.text = "„Och, to jest unikalny metal, naprawdę niedoceniany przez wielu. Ma wysoką trwałość, plastyczność i jest absolutnie odporny na działanie czynników zewnętrznych - ani woda, ani sól nie mogą go uszkodzić\nByć może już wcześniej widziałeś ten metal. Jest biały, wygląda jak srebro, dlatego Hiszpanie nazwali go 'srebro'. Ha! Jest sto razy lepszy niż srebro! Nawet lepszy niż złoto! Pewnego dnia to zrozumieją, ale jeszcze nie nadszedł właściwy czas.”";
			link.l1 = "Słuchaj, dlaczego nie możesz użyć innych rodzajów metalu zamiast tego? Dlaczego nie używasz złota do produkcji tych płyt? Nigdy nie słyszałem, żeby złoto zardzewiało lub się zniszczyło.";
			link.l1.go = "mechanic_9";
		break;
		
		case "mechanic_9":
			dialog.text = "Masz giętki i żywy umysł, młodzieńcze. Dobrze to wiedzieć. Niestety, twoja propozycja nie zadziała. Myśl o złocie była pierwszą, która przyszła mi do głowy. Ale złoto jest zbyt miękkie, by łączyć różne części zbroi. Niestety, jedynie platyna się nada. Będę tworzył części tylko z niej, nawet jeśli zajmie to lata, aby zebrać wystarczająco. Ale widziałem już kawałki tego metalu na Wyspie - często jest mieszany ze srebrem z powodu swojego wyglądu.";
			link.l1 = "Hm. A jeśli pomogę ci znaleźć wystarczająco dużo tego... 'srebra', pożyczysz mi skafander, abym mógł nurkować pod wodą?";
			link.l1.go = "mechanic_10";
		break;
		
		case "mechanic_10":
			dialog.text = "Nie musisz pytać! Oczywiście, że to zrobię. Już ci mówiłem, że nie zanurkuję tam z powodu krabów, i nikt inny też nie chce tego zrobić.";
			link.l1 = "W takim razie pokaż mi ten kawałek metalu, abym zrozumiał, czego muszę szukać.";
			link.l1.go = "mechanic_11";
		break;
		
		case "mechanic_11":
			dialog.text = "Więc zamierzasz go szukać? Doskonale. Oto, weź ten kawałek jako przykład. Szukaj go wśród rudy srebra i grudek. Nie będzie łatwo go znaleźć, ale dasz sobie radę. Na srebrze są małe zaciemnienia, ale nasz metal jest czysty i znacznie twardszy niż srebro. Najprostszym sposobem na jego przetestowanie byłoby porysowanie go srebrną monetą, jeśli moneta zostanie uszkodzona, to go znalazłeś.";
			link.l1 = "Dobrze. Zamierzam natychmiast tego szukać. Masz jakieś sugestie, gdzie powinienem tego szukać?";
			link.l1.go = "mechanic_12";
		break;
		
		case "mechanic_12":
			GiveItem2Character(pchar, "jewelry10");
			PlaySound("interface\important_item.wav");
			Log_Info("You have received a platinum ingot");
			dialog.text = "Niestety, nie wiem. Gdybym wiedział, gdzie to znaleźć, zrobiłbym to sam. Ale mogę ci dać radę. Szukaj na statkach Rivados. Nie odwiedzam ich, więc jest bardzo prawdopodobne, że mogą to mieć.";
			link.l1 = "Rozważę to, Henrik. Mam nadzieję, że będę miał szczęście.";
			link.l1.go = "mechanic_13";
		break;
		
		case "mechanic_13":
			dialog.text = "Zbierz jeszcze dziesięć kawałków. To minimum, by naprawić strój. Powodzenia!";
			link.l1 = "Dzięki. Żegnaj, Mechaniku!";
			link.l1.go = "mechanic_14";
		break;
		
		case "mechanic_14":
			DialogExit();
			pchar.questTemp.LSC = "platinum";
			AddQuestRecord("LSC", "7");
			if (GetSummonSkillFromName(pchar, SKILL_FORTUNE) >= 65 || rand(2) == 1) pchar.questTemp.LSC.PtAddQty = 0;
			else pchar.questTemp.LSC.PtAddQty = rand(4);
		break;
		
		case "mechanic_15":
			RemoveItems(pchar, "jewelry10", 11);
			dialog.text = "Cóż, cóż, pokaż mi... Doskonale! Dobra robota, młodzieńcze! Czy to było trudne?";
			link.l1 = "Nie do końca...";
			link.l1.go = "mechanic_16";
		break;
		
		case "mechanic_16":
			dialog.text = "Cóż, teraz mogę zacząć naprawy. Nie będę tracił czasu i zacznę jutro. Naprawdę nie możesz się doczekać nurkowania, prawda?";
			link.l1 = "Rzeczywiście. Naprawdę chcę zbadać podwodne głębiny.";
			link.l1.go = "mechanic_17";
		break;
		
		case "mechanic_17":
			dialog.text = "To bardzo dobrze, ponieważ będę miał dla ciebie prośbę, kiedy zorganizujemy twoje nurkowanie. Ale porozmawiamy o tym później. Przyjdź do mnie za pięć dni, mam nadzieję, że skończę naprawy.";
			link.l1 = "Zgoda. Życzę ci powodzenia!";
			link.l1.go = "mechanic_18";
		break;
		
		case "mechanic_18":
			dialog.text = "Na pewno potrzebne będzie szczęście, ale naprawa zbroi wymaga głównie umiejętności. Poza tym, będę musiał spędzić dzień przy piecu z Jurgenem, aby zrobić płytę z metalu, który mi przyniosłeś.";
			link.l1 = "W takim razie nie będę ci przeszkadzać. Do zobaczenia za pięć dni. Żegnaj!";
			link.l1.go = "mechanic_19";
		break;
		
		case "mechanic_19":
			DialogExit();
			pchar.questTemp.LSC = "platinum_wait";
			AddQuestRecord("LSC", "8");
			SetFunctionTimerCondition("LSC_PrepareUnderwater_Check", 0, 0, 5, false); // таймер
			AddCharacterExpToSkill(pchar, "Fortune", 300);
		break;
		
		case "mechanic_20":
			if (int(pchar.questTemp.LSC.PtAddQty) == 0)
			{
				dialog.text = "Tak. Ja i Jurgen wykonaliśmy piekielną robotę, a ilość części, które przyniosłeś, była wystarczająca, by to zrobić. Skafander jest naprawiony i przygotowany. Muszę tylko przeprowadzić kilka testów, ale jestem pewny, że wszystko jest w porządku. Przyjdź jutro o 10 rano - napełnię zbiorniki powietrzem i będziesz mógł robić, co chcesz.";
				link.l1 = "Wybornie! Nie mogę się doczekać. Do zobaczenia jutro, Henrik!";
				link.l1.go = "mechanic_24";
				DeleteAttribute(pchar, "questTemp.LSC.PtAddQty");
				AddCharacterExpToSkill(pchar, "Fortune", 100);
			}
			else
			{
				dialog.text = "Muszę cię rozczarować, "+pchar.name+"Jak przypuszczałem, nie ma wystarczającej ilości metalu. Potrzebuję "+FindRussianQtyString(int(pchar.questTemp.LSC.PtAddQty))+" więcej części, aby dokończyć naprawę. Muszę znowu poprosić cię o pomoc.";
				link.l1 = "No cóż, nie spodziewałem się takiego obrotu wydarzeń. Dobrze, spróbuję znaleźć bryłki, których Ci brakuje.";
				link.l1.go = "mechanic_21";
			}
		break;
		
		case "mechanic_21":
			dialog.text = "Będę na ciebie czekać. Możesz być pewien, że ta suma na pewno wystarczy. Po prostu ich przyprowadź, a ja skończę pracę w jeden dzień.";
			link.l1 = "Mam nadzieję... Do zobaczenia!";
			link.l1.go = "mechanic_22";
		break;
		
		case "mechanic_22":
			DialogExit();
			pchar.questTemp.LSC = "platinum_add_wait";
			AddQuestRecord("LSC", "9");
			AddQuestUserData("LSC", "sQty", FindRussianQtyString(int(pchar.questTemp.LSC.PtAddQty)));
		break;
		
		case "mechanic_23":
			RemoveItems(pchar, "jewelry10", int(pchar.questTemp.LSC.PtAddQty));
			dialog.text = "Wspaniale! Teraz strój zostanie przywrócony. Muszę tylko przeprowadzić kilka testów, ale jestem pewien, że wszystko jest w porządku. Przyjdź jutro o 10 rano - napełnię zbiorniki powietrzem i będziesz mógł robić, co zechcesz.";
			link.l1 = "Doskonale! Nie mogę się doczekać. Do zobaczenia jutro, Henrik!";
			link.l1.go = "mechanic_24";
		break;
		
		case "mechanic_24":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.LSC.PtAddQty"))
			{
				iTemp = 2;
				sTemp = "the day after tomorrow";
				DeleteAttribute(pchar, "pchar.questTemp.LSC.PtAddQty");
			}
			else
			{
				iTemp = 1;
				sTemp = "tomorrow";
			}
			if (!CheckAttribute(pchar, "questTemp.LSC.NatanTalk")) string sText = "But I have to find Nathaniel Hawk first before I dive."; //не было разговора с Натаном
			else sText = "";
			AddQuestRecord("LSC", "10");
			AddQuestUserData("LSC", "sText1", sTemp);
			AddQuestUserData("LSC", "sText2", sText);
			pchar.quest.LSC_prepunderwater.win_condition.l1 = "Timer";
			pchar.quest.LSC_prepunderwater.win_condition.l1.date.hour  = 10;
			pchar.quest.LSC_prepunderwater.win_condition.l1.date.day   = GetAddingDataDay(0, 0, iTemp);
			pchar.quest.LSC_prepunderwater.win_condition.l1.date.month = GetAddingDataMonth(0, 0, iTemp);
			pchar.quest.LSC_prepunderwater.win_condition.l1.date.year  = GetAddingDataYear(0, 0, iTemp);
			pchar.quest.LSC_prepunderwater.function = "LSC_PrepareUnderwater";
			pchar.questTemp.LSC = "wait";
		break;
		
		case "immersion":
			dialog.text = "Tak, skafander jest gotowy i napełniony powietrzem. Możesz nurkować.";
			if (!CheckAttribute(pchar, "questTemp.LSC.NatanTalk")) // не было разговора с Натаном
			{
				link.l1 = "Dobrze. Ale teraz nie mogę nurkować, muszę rozwiązać pewien problem dotyczący mojego... przyjaciela, Nathana Hawka. Nie mogę go znaleźć. Czy strój może trochę poczekać?";
				link.l1.go = "natan";
			}
			else
			{
				link.l1 = "Znacząco! Kiedy zaczniemy? Teraz?";
				link.l1.go = "immersion_1";
			}
		break;
		
		case "natan":
			dialog.text = "Jasne. Może poczekać. Czyżbyś nie szukał swojego przyjaciela od roku?";
			link.l1 = "Oczywiście, nie będę. Może znajdę go nawet dzisiaj. Odwiedzę cię zaraz po tym, jak załatwię z nim swoje sprawy.";
			link.l1.go = "natan_1";
		break;
		
		case "natan_1":
			dialog.text = "Tak proszę. Przyjdź, gdy będziesz gotowy do nurkowania.";
			link.l1 = "Dzięki!";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "underwater_natan";
		break;
		
		case "immersion_1":
			dialog.text = "Teraz, jeśli chcesz. Ale najpierw pozwól, że udzielę ci małej instrukcji. Rozpoczniesz swoje nurkowanie z platformy 'Feniks', możesz tam dotrzeć od rufy San Gabriela. Jest tam winda, która zabierze cię na dół i z powrotem. To jedyny sposób na powrót\nLepiej zapamiętaj lokalizację windy pod wodą i nie zgub się. Zbiorniki kombinezonu mają wystarczająco powietrza na dwadzieścia minut nurkowania. Obserwuj czas, bo inaczej się udusisz\nNie oddalaj się za bardzo od windy, bo nie zdążysz wrócić na czas, a Boże broń, żebyś opuścił naszą mieliznę - zostaniesz spłaszczony jak flądra\nBądź ostrożny i uważaj na kraby. Jeśli podejdziesz do nich zbyt blisko, zaatakują cię. Nie ryzykuj, jeśli nie musisz, nie będziesz w stanie zabić całej paczki, a szybka ucieczka nie wchodzi tam w grę.";
			link.l1 = "Zajmę się krabami. Resztę mam pod kontrolą. Nie zanurzaj się głębiej, nie oddalaj się od windy i nie zapomnij o czasie. Kiedy mogę się zanurzyć?";
			link.l1.go = "immersion_2";
		break;
		
		case "immersion_2":
			dialog.text = "Kiedy tylko chcesz, ale tylko od 7 rano do 21. W ciemności nic nie zobaczysz.";
			link.l1 = "Zrozumiano.";
			link.l1.go = "immersion_4";
		break;
		
		case "immersion_4":
			dialog.text = "To właśnie to. Weź kombinezon z pokoju na platformie. Zdejmij go po nurkowaniu i przynieś mi. Napełnię go znowu powietrzem. Ale nie próbuj nurkować więcej niż raz dziennie, nawet 20 minut nurkowania i oddychania sprężonym powietrzem jest szkodliwe dla zdrowia.";
			link.l1 = "Cóż, nie zanurkuję więcej niż raz dziennie, zatem.";
			link.l1.go = "immersion_5";
		break;
		
		case "immersion_5":
			dialog.text = "Jestem zadowolony, że rozumiesz. Teraz idź i powodzenia!";
			link.l1 = "Dzięki!";
			link.l1.go = "immersion_6";
		break;
		
		case "immersion_6":
			DialogExit();
			pchar.questTemp.LSC = "first_immersion"; // флаг на первое погружение
			pchar.questTemp.LSC.immersion = "true"; // погружение возможно
			pchar.quest.LSC_takeUnderwater.win_condition.l1 = "locator";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.location = "FenixPlatform";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.locator_group = "item";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.locator = "armor";
			pchar.quest.LSC_takeUnderwater.function = "LSC_takeUnderwater"; // выдача костюма
			pchar.quest.LSC_UnderwaterDolly.win_condition.l1 = "locator";
			pchar.quest.LSC_UnderwaterDolly.win_condition.l1.location = "Underwater";
			pchar.quest.LSC_UnderwaterDolly.win_condition.l1.locator_group = "quest";
			pchar.quest.LSC_UnderwaterDolly.win_condition.l1.locator = "dolly";
			pchar.quest.LSC_UnderwaterDolly.function = "LSC_FindUnderwaterDolly"; // нашли статую
			NextDiag.CurrentNode = "after_first_immersion"; // нода после первого погружения
			AddQuestRecord("LSC", "11");
			QuestPointerToLoc("UnderWater", "quest", "dolly");
		break;
		
		case "after_first_immersion":
			if (CheckAttribute(pchar, "questTemp.LSC.immersion"))
			{
				dialog.text = "Więc, dlaczego wciąż tu jesteś? Strój na ciebie czeka.";
				link.l1 = "Tak, tak. Już idę.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Więc, jak poszło pierwsze nurkowanie?";
				if (CheckAttribute(pchar, "questTemp.LSC.FindDolly"))
				{
					link.l1 = "Najwspanialej, jestem zadowolony z rezultatów. Znalazłem kamienny idol w zatopionym galeonie. Słyszałem, że Rivados składali mu wcześniej ofiary. Powiedz mi, Henrik, czy znasz kogoś, kto mógłby mi o nim więcej opowiedzieć?";
					link.l1.go = "af_immersion_1";
				}
				else
				{
					link.l1 = "Dobrze. Zrobiłem to! Było naprawdę interesujące, choć trochę ekscytujące.";
					link.l1.go = "af_immersion_2";
				}
			}
			NextDiag.TempNode = "after_first_immersion";
		break;
		
		case "af_immersion_1":
			dialog.text = "Interesujesz się naszą historią? Idź do Antonio Betancourta. Urodził się tutaj. Mieszka na flecie Pluto. Jeśli on o czymś nie wie - to nikt nie wie.";
			link.l1 = "Doskonale! Na pewno go odwiedzę.";
			link.l1.go = "af_immersion_2";
			pchar.questTemp.LSC.Betancur = "true";
			AddQuestRecord("LSC", "14");
		break;
		
		case "af_immersion_2":
			dialog.text = "Zostaw tu skafander. Wróć jutro lub innego dnia, napełnię go powietrzem.";
			if (CheckCharacterItem(pchar, "underwater"))
			{
				link.l1 = "Pewnie. Oto twój strój. Dzięki!";
				link.l1.go = "af_immersion_3";
			}
			else
			{
				link.l1 = "Oczywiście. Przyniosę to natychmiast!";
				link.l1.go = "af_immersion_wait";
			}
		break;
		
		case "af_immersion_wait":
			dialog.text = "Czy przyniosłeś mi mój sprzęt?";
			if (CheckCharacterItem(pchar, "underwater"))
			{
				link.l1 = "Pewnie. Oto twój garnitur. Dzięki!";
				link.l1.go = "af_immersion_3";
			}
			else
			{
				link.l1 = "Zrobię to natychmiast!";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "af_immersion_wait";
		break;
		
		case "af_immersion_3":
			DialogExit();
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			RemoveItems(pchar, "underwater", 1);
			LocatorReloadEnterDisable("SanGabrielMechanic", "reload3", false);
			SetFunctionTimerCondition("LSC_ReadyUnderwater", 0, 0, 1, false);
			NextDiag.CurrentNode = "First time";
			// даем старт мини-квестам с крабикусами
			sld = characterFromId("Carpentero");
			if(!CheckAttribute(sld, "quest.crab")) sld.quest.crab = "begin";
			if (GetCharacterIndex("LSC_Jacklin") != -1)
			{
				sld = characterFromId("LSC_Jacklin");
				sld.quest.crab = "true";
			}
		break;
		
		// блок погружений, за искл. первого
		case "immersion_next":
			if (CheckAttribute(npchar, "quest.guarantee")) // требует залог
			{
				dialog.text = "Tak, oczywiście. Kombinezon został przetestowany i napełniony powietrzem. Masz przy sobie zastaw? 500 000 pesos?";
				if (int(pchar.money) >= 500000)
				{
					link.l1 = "Tak, oczywiście. Proszę, weź to.";
					link.l1.go = "immersion_next_pay";
				}
				else
				{
					link.l1 = "Och! Zapomniałem o tym. Przyniosę to natychmiast...";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Tak, oczywiście. Skafander został przetestowany i napełniony powietrzem. Sprawdź platformę 'Feniks', jak zawsze.";
				link.l1 = "W takim razie nurkuję. Dzięki!";
				link.l1.go = "immersion_next_1";
			}
		break;
		
		case "immersion_next_1":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.LSC.UW_ready"); 
			LocatorReloadEnterDisable("LostShipsCity_town", "reload72", false); //открываем вход в Феникс
			pchar.questTemp.LSC.immersion = "true"; // погружение возможно
			pchar.quest.LSC_takeUnderwater.win_condition.l1 = "locator";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.location = "FenixPlatform";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.locator_group = "item";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.locator = "armor";
			pchar.quest.LSC_takeUnderwater.function = "LSC_takeUnderwater"; // выдача костюма
		break;
		
		case "immersion_next_2":
			dialog.text = "W porządku. Wróć jutro albo później. Zamierzam przygotować strój.";
			link.l1 = "Dzięki, Mechaniku!";
			link.l1.go = "immersion_next_3";
		break;
		
		case "immersion_next_3":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.LSC.UW_end"); 
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			RemoveItems(pchar, "underwater", 1);
			if (CheckAttribute(npchar, "quest.guarantee")) AddMoneyToCharacter(pchar, 500000); // возврат залога
			LocatorReloadEnterDisable("SanGabrielMechanic", "reload3", false);
			SetFunctionTimerCondition("LSC_ReadyUnderwater", 0, 0, 1, false);
		break;
		
		case "immersion_next_pay":
			AddMoneyToCharacter(pchar, -500000);
			dialog.text = "Zwrócimy ci pieniądze, gdy oddasz mundur. Uczciwa transakcja.";
			link.l1 = "Dzięki, Mechaniku! Teraz idę nurkować.";
			link.l1.go = "immersion_next_1";
		break;
		// блок погружений
		
	//--------------------------------------вернулся на Остров---------------------------------------------
		case "return":
			dialog.text = "Poczekaj chwilę, proszę! Jaka statua? A-ach, teraz rozumiem. Masz na myśli ten idol w zatopionym statku 'San-Geronimo', prawda? Więc te opowieści Rivados są prawdziwe?";
			link.l1 = "Dokładnie! I nie ma żadnych opowieści. Znam jeszcze dwa idole na archipelagu, które teleportują ludzi, którzy ich dotkną, z jednego na drugi, po okręgu.";
			link.l1.go = "return_1";
		break;
		
		case "return_1":
			dialog.text = "Widzę, widzę. Będę musiał ci zaufać, choć twoje słowa to antynaukowy nonsens. Teleporty, posągi... ha! I kto mógłby o tym pomyśleć, jak takie rzeczy w ogóle działają?";
			link.l1 = "Po prostu mi zaufaj i nie próbuj doszukiwać się tu logiki. Nie kłamię.";
			link.l1.go = "return_2";
		break;
		
		case "return_2":
			dialog.text = "Dobrze. Ale mam nadzieję, że nie zgubiłeś garnituru podczas tego swojego teleportu?";
			if(CheckCharacterItem(pchar, "underwater"))
			{
				link.l1 = "Oczywiście, że nie. To uratowało mnie przed Karaibami, że tak powiem. Oto jest.";
				link.l1.go = "return_4";
			}
			else
			{
				link.l1 = "Pewnie, że nie. To mnie uratowało przed Karaibami, że tak powiem. Ale teraz nie mam go przy sobie.";
				link.l1.go = "return_3";
			}
		break;
		
		case "return_3":
			dialog.text = "Więc przynieś mi to, do diabła! Nie będziemy rozmawiać, dopóki mi tego nie zwrócisz, wiedz o tym!";
			link.l1 = "Spokojnie, Mechaniku. Zwrócę ci to!";
			link.l1.go = "exit";
			NextDiag.TempNode = "return_underwater";
		break;
		
		case "return_underwater":
			if(CheckCharacterItem(pchar, "underwater"))
			{
				dialog.text = "Ach, rzeczywiście przyniosłeś mój garnitur! Dzięki, zaczynałem się o niego martwić.";
				link.l1 = "Nie było potrzeby się tym martwić. Obiecałem ci, że to zwrócę.";
				link.l1.go = "return_4";
			}
			else
			{
				dialog.text = "Nie przychodź tu, dopóki nie masz mojego stroju.";
				link.l1 = "Dobrze, dobrze.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "return_underwater";
		break;
		
		case "return_4":
			DeleteAttribute(pchar, "questTemp.LSC.UW_end"); 
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			RemoveItems(pchar, "underwater", 1);
			SetFunctionTimerCondition("LSC_ReadyUnderwater", 0, 0, 1, false);
			dialog.text = "Bardzo dobrze. Zacząłem myśleć o zrobieniu nowego, ale to byłaby praca na rok, nie mniej... Cieszę się, że wykazałeś się dobrą gospodarką i zwróciłeś moją własność w całości. Nawet dam ci prezent.";
			link.l1 = "Jesteś poważny?";
			link.l1.go = "return_5";
		break;
		
		case "return_5":
			dialog.text = "Oczywiście, że tak! Pomogłeś mi naprawić strój i nie wyrzuciłeś go przy pierwszej okazji. Dbałeś o niego, a w końcu zwróciłeś go do mnie. W każdym razie, oto porządna skrzynka narzędziowa. Naucz się, jak jej używać. Dzięki niej będziesz mógł stworzyć wiele pożytecznych rzeczy.";
			link.l1 = "A czegoż innego mógłbym się spodziewać od Mechanika! Oczywiście, skrzynka z narzędziami! Wielkie dzięki, Henrik, jestem poruszony... Nie zasłużyłem na taki prezent.";
			link.l1.go = "return_6";
		break;
		
		case "return_6":
			GiveItem2Character(pchar, "mechanic_tool");
			Log_Info("You have received a toolbox");
			PlaySound("interface\important_item.wav");
			dialog.text = "Wiem lepiej, na co zasłużyłeś, a na co nie. Weź to! Przyda ci się. Ale zbroję dam ci ponownie tylko wtedy, gdy wpłacisz 500 000 pesos z powodu twojego nawyku teleportacji przez idoli.";
			link.l1 = "Och! Cóż, rozumiem, że... środki ostrożności...";
			link.l1.go = "return_7";
		break;
		
		case "return_7":
			dialog.text = "Oczywiście. A co jeśli pewnego dnia uciekniesz z nim? Wtedy pieniądze będą moją rekompensatą.";
			link.l1 = "Dobrze, Henrick. Zgadzam się. Szczerze mówiąc, myślałem, że nigdy mi tego już nie oddasz.";
			link.l1.go = "return_8";
		break;
		
		case "return_8":
			dialog.text = "Nie ma mowy. Złóż pół miliona, a wszystko będzie twoje.";
			link.l1 = "Zgoda! Czy mogę, jak zwykle, zabrać to do nurkowania? Od jutra?";
			link.l1.go = "return_9";
		break;
		
		case "return_9":
			dialog.text = "Dokładnie.";
			link.l1 = "Dzięki! Do zobaczenia, Henrik!";
			link.l1.go = "return_10";
		break;
		
		case "return_10":
			DialogExit();
			AddQuestRecord("LSC", "26");
			npchar.quest.return_isl = "true";
			npchar.quest.guarantee = "true"; // залог за скафандр
			NextDiag.CurrentNode = "First time";
		break;
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Co tam robisz, co? Złodzieju!","Spójrz tylko na to! Ledwie pogrążyłem się w zadumie, a ty postanowiłeś sprawdzić moją skrzynię!","Zdecydowałeś się zajrzeć do moich skrzyń? Nie ujdzie ci to na sucho!");
			link.l1 = "Cholera!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Co?! Postanowiłeś sprawdzić moje skrzynie? Nie ujdzie ci to na sucho!";
			link.l1 = "Niemądra dziewczyno!...";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Słuchaj, lepiej schowaj swoją broń. To mnie denerwuje.","Wiesz, bieganie z ostrzem nie jest tu tolerowane. Schowaj to.","Słuchaj, nie udawaj średniowiecznego rycerza biegającego z mieczem na około. Odłóż to, to nie pasuje do ciebie...");
			link.l1 = LinkRandPhrase("Dobrze.","Z pewnością.","Jak mówisz...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Słuchaj, jestem obywatelem miasta i prosiłbym cię, byś schował swój miecz.","Słuchaj, jestem obywatelem miasta i proszę cię, abyś schował swoją klingę");
				link.l1 = LinkRandPhrase("W porządku.","Jasne.","Jak mówisz...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Bądź ostrożny, kumplu, biegając z bronią. Mogę się zdenerwować...","Nie lubię, gdy ludzie chodzą przede mną z gotową bronią. To mnie przeraża...");
				link.l1 = RandPhraseSimple("Zrozumiano.","Zabieram to.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

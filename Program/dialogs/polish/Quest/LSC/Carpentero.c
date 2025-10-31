// Санчо Карпентеро - бармен
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "Nie chcę z tobą rozmawiać. Atakujesz pokojowych ludzi bez powodu i prowokujesz ich do walki. Wynoś się z mojej tawerny!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = ""+pchar.name+" ! Cieszę się, że cię widzę! Wiedziałem, wiedziałem, że plotki to kłamstwo! Cholera, musimy teraz koniecznie to opić!";
				link.l1 = "Cóż, napijmy się, kumplu! Ja też cholernie się cieszę, że cię widzę!";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			// пей до дна
			if (CheckAttribute(npchar, "quest.drink") && npchar.quest.drink == "fail")
			{
				dialog.text = ""+pchar.name+"Przykro mi z powodu twojej porażki. Niewielu jest w stanie przepić grubasa. Jak się ma twoja głowa?";
				link.l1 = "Tak, przyjacielu, masz tam solidny mocny rum. Jestem ci winien za napoje... ile?";
				link.l1.go = "drunk_fail";
				break;
			}
			if (CheckAttribute(npchar, "quest.drink") && npchar.quest.drink == "win")
			{
				dialog.text = "Pokonałeś Fazio, "+pchar.name+" ! Jestem zaskoczony, tylko nieliczni zdołali go przepić. Proszę, oto twoje dwieście dublonów.";
				link.l1 = "Dziękuję za miłe słowa, kumplu!";
				link.l1.go = "drunk_win";
				break;
			}
			// крабовый салат
			if (CheckAttribute(npchar, "quest.crab") && npchar.quest.crab == "begin")
			{
				dialog.text = ""+pchar.name+" ? Mówią, że zanurzyłeś się na dno w stroju zrobionym przez mechanika Narwala. Czy to prawda, czy tylko plotki, jak zwykle?";
				link.l1 = "To prawda, kumplu. Naprawdę tam nurkowałem.";
				link.l1.go = "crab";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Witaj w mojej tawernie, nowy przybyszu! Witaj! Zawsze znajdziesz napitki w mojej tawernie, moje piwnice są pełne wina, choć nie mogę tego samego powiedzieć o jedzeniu, ha-ha... Żartuję. Nazywam się Sancho Carpentero i jestem właścicielem tego miejsca.";
				link.l1 = TimeGreeting()+", Sancho. Nazywam się "+GetFullName(pchar)+"Miło cię poznać.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ach, mój przyjacielu "+pchar.name+"! Cieszę się, że cię widzę w mojej tawernie! Chcesz coś wypić?";
				// квестовые ветки
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "search_mush_1" && !CheckAttribute(npchar, "quest.mushket"))
				{
					link.l6 = "Słuchaj, Sancho, wiesz, gdzie mogę zdobyć dobrą muszkietę? Nie zwykły boczny oręż żołnierza, ale coś celnego, może do polowania?";
					link.l6.go = "mushket";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "search_mush_2")
				{
					link.l6 = "Słuchaj, Sancho, mam do ciebie kilka pytań. Szukam człowieka o imieniu Adolf Barbier. Mówią, że często odwiedza to miejsce...";
					link.l6.go = "adolf";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "barmen_whiskey")
				{
					link.l6 = "Słuchaj, Sancho, mówią, że Chad Kapper kupił od ciebie trochę arszeniku...";
					link.l6.go = "whiskey";
				}
				if (CheckCharacterItem(pchar, "talisman1") && CheckAttribute(npchar, "quest.rat"))
				{
					link.l7 = "Sancho, chcesz, żebym pokazał ci coś interesującego? Czy to jest maska nietoperza, którą tak bardzo chciałeś zdobyć?";
					link.l7.go = "rat";
				}
				if (CheckCharacterItem(pchar, "talisman1") && CheckAttribute(npchar, "quest.ratmoney") && PCharDublonsTotal() >= 1)
				{
					if (PCharDublonsTotal() >= sti(npchar.quest.ratmoney))
					{
						if(!CheckAttribute(npchar, "quest.ratmoneyagain")) ChangeCharacterComplexReputation(pchar, "fame", 5);
						link.l7 = "Sancho, przyszedłem po moją kirysę. Oto pieniądze.";
						link.l7.go = "rat_3";
					}
					else
					{
						npchar.quest.ratmoneyagain = true;
						link.l7 = "Sancho, przyszedłem po moją kirysę. Oto pieniądze.";
						link.l7.go = "rat_take_money_not_all";
					}
				}
				if (makeint(pchar.money) >= 25)
				{
					link.l1 = "Podaj mi rumu, Sancho.";
					link.l1.go = "drink";
				}
				if (makeint(pchar.money) >= 20)
				{
					link.l2 = "Chcę zostać na noc.";
					link.l2.go = "room";
				}
				if (stf(environment.time) >= 6.0 && stf(environment.time) <= 18.0 && makeint(pchar.money) >= 300)
				{
					link.l9 = "Nudno... Sancho, chcę spędzić tu czas z butelką wina aż do wieczora...";
					link.l9.go = "drink_sit";
				}
				link.l3 = LinkRandPhrase("Masz coś ciekawego do opowiedzenia?","Co się ostatnio wydarzyło na wyspie?","Jakieś plotki?");
				link.l3.go = "rumours_LSC";
				if (CheckAttribute(npchar, "quest.crab") && npchar.quest.crab == "current" && CheckCharacterItem(pchar, "crab_pincers"))
				{
					link.l10 = "Sancho, chcę sprzedać ci pazury kraba.";
					link.l10.go = "crab_trade";
				}
				link.l4 = "Sancho, chcę cię o coś zapytać o Wyspę.";
				link.l4.go = "int_quests"; //информационный блок
				link.l5 = "Nie, kumplu. Po prostu chciałem sprawdzić, jak sobie tu radzisz.";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "Ja też. Mam nadzieję, że będę cię widywać przynajmniej co drugi dzień albo nawet co wieczór, ha-ha! Szczerze cieszę się z każdego gościa w mojej tawernie.";
			if (makeint(pchar.money) >= 25)
			{
				link.l1 = "Podaj mi trochę rumu, Sancho.";
				link.l1.go = "drink";
			}
			if (makeint(pchar.money) >= 20)
			{
				link.l2 = "Chcę zostać na noc.";
				link.l2.go = "room";
			}
			link.l3 = "Sancho, chcę cię zapytać o coś związanego z wyspą.";
			link.l3.go = "int_quests"; //информационный блок
			link.l4 = "Do zobaczenia, Sancho!";
			link.l4.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "mushket":
			dialog.text = "Nie, przyjacielu, nie mogę ci pomóc. Wiesz, jestem specjalistą od kufli piwa i butelek wina - ale nie od muszkietów, ha-ha! Idź do sklepu, słyszałem, że Axel czasami sprzedaje ciekawe bronie. Może tam znajdziesz to, czego potrzebujesz.";
			link.l1 = "Dziękuję za radę.";
			link.l1.go = "exit";
			npchar.quest.mushket = "true";
		break;
		
		case "adolf":
			dialog.text = "Adolf? Tak, czasami mnie odwiedza, choć nie widziałem go przez ostatnie kilka dni. Zniknął odkąd rozmawiał z tamtym grubym człowiekiem Giuseppe.";
			link.l1 = "Giuseppe? Masz na myśli Giuseppe Fazio?";
			link.l1.go = "adolf_1";
		break;
		
		case "adolf_1":
			dialog.text = "Ha, kumplu, na Wyspie jest tylko jeden Giuseppe - Giuseppe Fazio. Aye, to on. Siedzieli przez kilka godzin, pijąc rum i prowadząc bardzo ożywioną rozmowę.";
			link.l1 = "Czy oni się kłócili?";
			link.l1.go = "adolf_2";
		break;
		
		case "adolf_2":
			dialog.text = "Nie. Wyglądało, jakby byli starymi kumplami. Posłuchaj, po prostu odwiedź Fazio w 'Karolinie' i zapytaj go o Adolfa.";
			link.l1 = "Dobrze, zrobię to.";
			link.l1.go = "adolf_3";
		break;
		
		case "adolf_3":
			dialog.text = "To wszystko? Mówiłeś, że masz kilka pytań...";
			link.l1 = "Tak. Powiedz mi, kim są Czerwona Mary i Cyklop Marcello?";
			link.l1.go = "adolf_4";
		break;
		
		case "adolf_4":
			dialog.text = "Ruda Mary jest jedną z Narwali. Młoda i piękna dziewczyna, ale zupełnie dzika, tak. Potrafi posługiwać się szablą i pistoletem równie dobrze jak każdy mężczyzna. Była dziewczyną Alana Milrowa, byłego lidera klanu Narwali, zanim admirał go zabił\nŚmierć Alana mocno ją dotknęła, większość czasu spędza na płaczu i przeklinaniu Rekina w swojej kajucie na 'Ceres Smithy'... Ale ona się z tego otrząśnie, życie toczy się dalej\nNiewiele wiem o Marcellu, widziałem go tylko kilka razy. Podejrzany typ. Mówią, że był kiedyś królewskim myśliwym, stracił oko w walce i wypłynął jako oficer abordażowy\nNienawidzi piratów, wygląda na to, że ma do nich urazę. Nic dziwnego, biorąc pod uwagę jego wcześniejszą służbę w oddziałach abordażowych statków handlowych.";
			link.l1 = "Rozumiem. Wielkie dzięki, Sancho, bardzo mi pomogłeś!";
			link.l1.go = "adolf_5";
		break;
		
		case "adolf_5":
			dialog.text = "Witaj, przyjacielu, przyjdź do mnie znów, a napijemy się razem piwa...";
			link.l1 = "Jasne!";
			link.l1.go = "adolf_6";
		break;
		
		case "adolf_6":
			DialogExit();
			pchar.questTemp.Saga.SharkHunt = "search_mush_3"; //флаг на Джузеппе
			AddQuestRecord("SharkHunt", "13");
		break;
		
		// виски для Акулы
		case "whiskey":
			dialog.text = "Kapera? Nie. Nie odwiedzał tawerny ostatnio. Marcello Cyklop kupił flaszkę arszeniku zaledwie piętnaście minut temu - również ma problem ze szczurami. Doskonale go rozumiem... Przeklęte szczury.";
			link.l1 = "Marcello Cyklop?!";
			link.l1.go = "whiskey_1";
		break;
		
		case "whiskey_1":
			dialog.text = "Cóż, tak. Czy to dziwne?";
			link.l1 = "Nie, oczywiście, że nie! Szukałem go od kilku dni i okazuje się, że był tu niedawno. Czy mógłbyś mi powiedzieć, dokąd się udał?";
			link.l1.go = "whiskey_2";
		break;
		
		case "whiskey_2":
			dialog.text = "Był z Adolfem Barbierem, który mieszka na 'Santa Florentina'. Być może, tam się udali.";
			link.l1 = "Dzięki!";
			link.l1.go = "whiskey_3";
		break;
		
		case "whiskey_3":
			dialog.text = "Jeśli potrzebujesz trochę arszeniku, mogę sprzedać flakon za dwadzieścia dublonów.";
			link.l1 = "Dobrze. Porozmawiamy o tym później, Sancho. Do zobaczenia!";
			link.l1.go = "whiskey_4";
		break;
		
		case "whiskey_4":
			DialogExit();
			pchar.questTemp.Saga.SharkHunt = "whiskey_poison"; // флаг - виски травят
			AddQuestRecord("SharkHunt", "37");
			sld = CharacterFromID("LSC_Adolf");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "SantaFlorentinaShipInside4", "goto", "goto2");
			sld = CharacterFromID("Dodson");
			sld.dialog.currentnode = "whiskey"; // ноду Акуле
			// важный момент! От дальнейшего поведения геймера зависит результат
			pchar.quest.LSC_Whiskeypoison_SF.win_condition.l1 = "location";
			pchar.quest.LSC_Whiskeypoison_SF.win_condition.l1.location = "SantaFlorentinaShipInside4";
			pchar.quest.LSC_Whiskeypoison_SF.function = "LSC_WhiskeyPoison_SF"; // прерывание на Санта-Флорентину
			pchar.quest.LSC_Whiskeypoison_AE.win_condition.l1 = "location";
			pchar.quest.LSC_Whiskeypoison_AE.win_condition.l1.location = "AvaShipInside3";
			pchar.quest.LSC_Whiskeypoison_AE.function = "LSC_WhiskeyPoison_AE"; // прерывание на Эву
			pchar.quest.LSC_Whiskeypoison_exit.win_condition.l1 = "location";
			pchar.quest.LSC_Whiskeypoison_exit.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_Whiskeypoison_exit.function = "LSC_Whiskeypoison_exit"; // прерывание на выход из таверны
			// закрываем вход к Фацио
			LocatorReloadEnterDisable("LostShipsCity_town", "reload20", true);
			LocatorReloadEnterDisable("LostShipsCity_town", "reload24", true);
		break;
		
		// пей до дна
		case "drunk_fail":
			dialog.text = "Chodź, przyjacielu! Nie jesteś mi nic winien. Już straciłeś sto dublonów. To był błąd zadawać się z Fazio...";
			if (sti(pchar.money) >= 500)
			{
				link.l1 = "Nie, nie, Sancho! Dziękuję i proszę, weź te pięćset pesos. To powinno pokryć koszt napojów, o ile dobrze pamiętam. Nie chcę być twoim dłużnikiem.";
				AddMoneyToCharacter(pchar, -500);
			}
			else link.l1 = "Eh, dzięki, Sancho. Masz rację.";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "quest.drink");
		break;
		
		case "drunk_win":
			DialogExit();
			TakeNItems(pchar, "gold_dublon", 200);
			Log_Info("You have received 200 doubloons");
			PlaySound("interface\important_item.wav");
			DeleteAttribute(npchar, "quest.drink");
		break;
		
		// крабовый салат
		case "crab":
			dialog.text = "Hm...  zatem mam dla ciebie propozycję.  Czy widziałeś tam gigantyczne kraby?";
			link.l1 = "  Widziałem kraby? Były ich hordy! A o jakiej propozycji mówisz?";
			link.l1.go = "crab_1";
		break;
		
		case "crab_1":
			dialog.text = "Jeśli zabijesz jakieś kraby, nie zapomnij przynieść mi ich szczypców. Zapłacę ci dobrze w dublonach - pięć monet za każdy. Axel Yost nie zapłaci tyle, uwierz mi. Nie proszę cię, żebyś polował na kraby dla tego zadania - ale jeśli natkniesz się na jakieś, proszę, miej to na uwadze...";
			link.l1 = "Dlaczego szczypce? A co z innymi częściami kraba? Co z nimi robicie?";
			link.l1.go = "crab_2";
		break;
		
		case "crab_2":
			dialog.text = " Dlaczego szczypce? Bo większość mięsa jest na nich. Kraby nie mają dużo mięsa na nogach, a ciała pokryte są solidnym pancerzem. Mięso krabów to tutaj przysmak, ma wyborny smak i jest bardzo pożywne\nMam też na nie unikalny przepis, więc zapłacę ci pięć dublonów za każdą szczypcę.";
			link.l1 = "Dobrze. Będę to mieć na uwadze.";
			link.l1.go = "crab_3";
		break;
		
		case "crab_3":
			DialogExit();
			npchar.quest.crab = "current";
		break;
		
		case "crab_trade":
			iTotalTemp = GetCharacterItem(pchar, "crab_pincers")
			dialog.text = "Znakomicie! Ile ich masz?";
			link.l1 = ""+FindRussianQtyString(iTotalTemp)+".";
			link.l1.go = "crab_trade_1";
			link.l2 = "Zmieniałem zdanie.";
			link.l2.go = "exit";
		break;
		
		case "crab_trade_1":
			dialog.text = "Umowa stoi. Proszę, weź swoje dublony - "+FindRussianQtyString(iTotalTemp*5)+" Dzięki, kumplu, jeśli zdobędziesz więcej, przynieś je do mnie.";
			link.l1 = "Oczywiście, przyjacielu.";
			link.l1.go = "crab_trade_2";
		break;
		
		case "crab_trade_2":
			DialogExit();
			RemoveItems(pchar, "crab_pincers", iTotalTemp);
			TakeNItems(pchar, "gold_dublon", iTotalTemp*5);
			PlaySound("interface\important_item.wav");
			Log_Info("You have received "+iTotalTemp*5+" doubloons");
		break;
		
		// крыс
		case "rat":
			dialog.text = "Co?! Pokaż mi! Pozwól mi to zobaczyć!";
			link.l1 = "Oczywiście.";
			link.l1.go = "rat_1";
		break;
		
		case "rat_1":
			PlaySound("interface\important_item.wav");
			dialog.text = "To jest to... Naprawdę jest! Jest dokładnie taki sam, jak ten na rysunku, który narysował dla mnie żeglarz! Przyjacielu, musi być powód, dla którego mi to przyniosłeś, czego za to chcesz? Ile?";
			link.l1 = "Oczywiście przyniosłem to do ciebie z jakiegoś powodu. Ale co do nagrody, co możesz mi zaoferować? O ile pamiętam, obiecałeś mi królewską nagrodę za tę rzecz...";
			link.l1.go = "rat_2";
			link.l2 = "Przykro mi, kumplu, to nie jest na sprzedaż. Potrzebuję tego dla siebie. Chciałem tylko upewnić się, że to jest talizman, o którym mówiłeś.";
			link.l2.go = "rat_exit";
		break;
		
		case "rat_exit":
			PlaySound("interface\important_item.wav");
			dialog.text = "Eh, co za wstyd... Tak, chłopcze, to dokładnie ten talizman. Szczęściarz z ciebie! Teraz szczury nie będą już sprawiać ci kłopotów. A ja będę musiał dalej je tępić arszenikiem...";
			link.l1 = "Przepraszam, że cię drażniłem, Sancho. Nigdy wcześniej tego nie widziałem, więc potrzebowałem konsultacji. Przepraszam.";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "quest.rat");
		break;
		
		case "rat_2":
			dialog.text = "Za to,"+pchar.name+", oferuję ci możliwość zakupu najwspanialszego i najcenniejszego przedmiotu, jaki posiadam. Byłaby to doskonała wymiana za ten amulet, zwłaszcza dla odważnego wojownika takiego jak ty. Pozwól, że go dla ciebie przyniosę.\nSpójrz: oto unikalna, wspaniała Kura Milanu, misternie wykonana! Zapewnia wyjątkową ochronę w walce, pozwalając na swobodny ruch, a przy tym jest lekka i wygodna. Zbroja tej jakości jest rzadkością zarówno na Karaibach, jak i w Europie.\nNatknąłem się na tę zbroję w kajucie kapitana hiszpańskiego okrętu wojennego kilka lat temu i trzymałem ją właśnie na taką okazję. Jestem gotów sprzedać ci ją za dwa tysiące złotych monet i Boga Szczurów!";
			link.l1 = "Hmm... TO jest doskonały kirys! Myślę, że ta wymiana mi odpowiada. Zajmę się problemem z szczurami, ale znalezienie innego takiego kirysu byłoby prawie niemożliwe. Nigdy wcześniej nie widziałem czegoś podobnego. Naprawdę, to wyjątkowy kawałek zbroi.";
			link.l1.go = "rat_yes";
			link.l2 = "Ile? Sancho, czy twoje szczury już cię dziś rano kilka razy pogryzły? Co masz na myśli, mówiąc dwa tysiące? Czy wiesz, ile mnie kosztowało, by zdobyć ci ten idol? Obniż cenę natychmiast!";
			link.l2.go = "rat_torg";
			link.l3 = "Ileż?! Jesteś rekinem, wiesz o tym, Sancho? 'Zaoferować możliwość zakupu!' Ha! Za takie pieniądze mógłbym sobie zamówić zbroję na lądzie, która odbijałaby kule i jeszcze by mnie leczyła! A na co ci tyle złota? Żeby Jurgen odlał ci własny pomnik i wystawił go na pełną wysokość na 'San Agustin'?";
			link.l3.go = "rat_no";
		break;
		
		case "rat_yes":
			dialog.text = "Cieszę się, że jesteś na pokładzie, mój przyjacielu. Dzięki za to, że nie zapomniałeś o moim problemie! Więc będę oczekiwać moich dublonów. Zbroja będzie na ciebie czekać.";
			link.l1 = "Zaraz ich przyprowadzę!";
			link.l1.go = "rat_yes_1";
		break;
		
		case "rat_yes_1":
			DialogExit();
			DeleteAttribute(npchar, "quest.rat");
			npchar.quest.ratmoney = 2000;
		break;
		
		case "rat_torg":
			if(GetSummonSkillFromName(pchar, SKILL_COMMERCE) < 60)
			{
				Notification_Skill(false, 60, SKILL_COMMERCE);
				dialog.text = " "+pchar.name+", w innych okolicznościach, zażądałbym pięciu tysięcy. Sam admirał wykazał zainteresowanie, i nie jest sam, uwierz mi. Nie spiesz się z decyzją. Zbroja będzie na ciebie czekać tak długo, jak będziesz potrzebować. Sprzedam ją tylko tobie.";
				link.l1 = "Pomyślę o tym, Sancho. Pomyślę długo i intensywnie.";
				link.l1.go = "rat_yes_1";
				AddCharacterExpToSkill(pchar, "Commerce", 400);
			}
			else
			{
				Notification_Skill(true, 60, SKILL_COMMERCE);
				dialog.text = ""+pchar.name+"w innych okolicznościach, żądałbym pięciu tysięcy. Sam admirał wyraził zainteresowanie, i nie jest sam, uwierz mi. Dobrze, obniżę pięćset, biorąc pod uwagę, że nie zapomniałeś o mnie i moim problemie. Wygląda na to, że po drodze były jakieś przygody.";
				link.l1 = "To lepiej. Ale wciąż nie rozumiem, dlaczego miałbym płacić więcej w tej wymianie równie unikalnych przedmiotów. Może to ty powinieneś mi zapłacić, co Sancho?";
				link.l1.go = "rat_yes_1500";
				AddCharacterExpToSkill(pchar, "Commerce", 100);
			}
		break;
		
		case "rat_yes_1500":
			if(GetSummonSkillFromName(pchar, SKILL_COMMERCE) < 90)
			{
				Notification_Skill(false, 90, SKILL_COMMERCE);
				dialog.text = "Nie, "+pchar.name+", nie ma mowy. Mogę poradzić sobie ze szczurami za pomocą trucizny, ale ta zbroja może pewnego dnia uratować ci życie. A będziesz wyglądać jak włoski książę, nosząc ją. Tysiąc pięćset, to moja ostateczna oferta. Weź sobie czas na przemyślenie, i daj mi znać. Zbroja będzie czekać na ciebie tak długo, jak będziesz potrzebować, sprzedam ją tylko tobie.";
				link.l1 = "Sancho, gdybyś nie był jedynym karczmarzem na tym ponurym cmentarzysku... Pomyślę nad twoją propozycją.";
				link.l1.go = "rat_yes_1500exit";
				AddCharacterExpToSkill(pchar, "Commerce", 600);
			}
			else
			{
				Notification_Skill(true, 60, SKILL_COMMERCE);
				dialog.text = "Dla wojskowego kapitana i pirata, naprawdę wiesz, jak negocjować! Pamiętasz Josta? Raz udało mu się kupić cały mój arsenik ze zniżką, podczas gdy szczury już mnie dręczyły. Dobrze, "+pchar.name+", wygrałeś. Odejmuje ci jeszcze pięćset! Ale to moja ostateczna oferta!";
				link.l1 = "This still feels like a rip-off, but at least now I won't feel like a typical damsel in distress in the jungle. Wait for the money; I'll bring it soon.";
				link.l1.go = "rat_yes_1000exit";
				AddCharacterExpToSkill(pchar, "Commerce", 200);
			}
		break;
		
		case "rat_no":
			dialog.text = "Spokojnie, "+pchar.name+"Od kogoś innego zażądałbym pięciu tysięcy! Sam admirał wyraził zainteresowanie, i nie jest sam, uwierz mi. Zbroja będzie na ciebie czekać tak długo, jak będzie to konieczne. To także jest wliczone w cenę idola.";
			link.l1 = "Co za zaszczyt! Poleruj dalej swoje kielichy, a ja ruszam w drogę. Dwa tysiące!";
			link.l1.go = "rat_yes_1";
		break;
		
		case "rat_yes_1500exit":
			DialogExit();
			DeleteAttribute(npchar, "quest.rat");
			npchar.quest.ratmoney = 1500;
		break;
		
		case "rat_yes_1000exit":
			Achievment_SetStat(106, 1);
			DialogExit();
			DeleteAttribute(npchar, "quest.rat");
			npchar.quest.ratmoney = 1000;
		break;
		case "rat_3":
			dialog.text = "Zrobione! Cieszę się, że się zgodziłeś, kumplu. Dzięki, że nie zapomniałeś o moim problemie! Weź tę kirysę i niech dobrze ci służy w bitwie.";
			link.l1 = "Proszę, weź również swój talizman - wygląda na to, że ciemne dni nadchodzą dla szczurów w twojej tawernie!";
			link.l1.go = "rat_4";
		break;
		
		case "rat_4":
			DialogExit();
			GiveItem2Character(pchar, "cirass4");
			RemoveItems(pchar, "talisman1", 1);
			RemoveDublonsFromPCharTotal(sti(npchar.quest.ratmoney));
			Log_Info("You have given away the talisman 'God of rats'");
			Log_Info("You have received a Milanese armor");
			Log_Info("You gave "+FindRussianDublonString(sti(npchar.quest.ratmoney))+"");
			PlaySound("interface\important_item.wav");
			DeleteAttribute(npchar, "quest.ratmoney");
			if(CheckAttribute(npchar, "quest.ratmoneyagain"))
				DeleteAttribute(npchar, "quest.ratmoneyagain");
		break;
		
		case "rat_take_money_not_all":
			npchar.quest.ratmoney = sti(npchar.quest.ratmoney) - PCharDublonsTotal();
			Log_Info("You gave "+FindRussianDublonString(PCharDublonsTotal())+"");
			RemoveDublonsFromPCharTotal(PCharDublonsTotal());
			PlaySound("interface\important_item.wav");
			dialog.text = "Wciąż budzisz we mnie podziw "+FindRussianDublonString(sti(npchar.quest.ratmoney))+", "+pchar.name+".";
			link.l1 = "Nie przypominaj mi!";
			link.l1.go = "exit";
		break;
		
		//--> информационный блок
		case "int_quests":
			dialog.text = "Słucham.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Co to za miejsce? Czy możesz mi o nim więcej powiedzieć?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Jak mogę opuścić Wyspę?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Co powinienem wiedzieć o Wyspie?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "A jak sobie tutaj radzisz? Jak tam twoja tawerna?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Nie mam pytań, nieważne...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "„To miejsce? Cóż, nazywają je Wyspą Sprawiedliwości, Wyspą Porzuconych Statków lub Miastem Porzuconych Statków - ale my po prostu nazywamy je Wyspą. Jest utworzona z wraków statków, które utknęły na mieliznach wśród raf. Centralna część Wyspy to obszar zamieszkały, a zewnętrzny pierścień jest niezamieszkany. Od dziesięciu lat nie było żadnego kontaktu ze światem zewnętrznym.”";
			link.l1 = "Zrozumiano...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Zbuduj długą łódź lub tratwę. Ale to nie skończy się dla ciebie dobrze. Wokół Wyspy znajduje się obszar burzy anomalii, nie przejdziesz przez zewnętrzny pierścień bez ryzyka dla życia. Dodatkowo, Wyspa jest okrążana przez silny prąd\nPotrzebujesz załogi, aby mieć choćby cień szansy na przetrwanie. I bardzo niewielu miejscowych jest chętnych opuścić to miejsce. Jeszcze mniej jest gotowych podjąć jakiekolwiek ryzyko. Ludzie lubią tu sposób życia. Zapytaj, jeśli mi nie wierzysz.";
			link.l1 = "Rozumiem...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Najpierw powinieneś pamiętać, że na Wyspie Sprawiedliwości jest kilka stref zamkniętych. Dwa klany - Narwale i Rivados, żyją tu od dawna, walcząc między sobą i bezwzględnie chroniąc terytoria, które uważają za swoje. Spróbuj odwiedzić ich bez zaproszenia, a jesteś martwy.\nMusisz znać aktualne hasło, jeśli chcesz wejść na ich terytorium. Nie martw się o przypadkowe dostanie się tam, strażnicy dadzą ci kilka ostrzeżeń, zanim zaczną strzelać.";
			link.l1 = "Zapamiętam to...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "You know, my friend, it's fine. I used to work with food and drinks: I worked as a cook a long time ago in Europe, as an intendant in a garrison, a tavern keeper, and a cook on a ship; so the first thing I did here was establishing a tavern\nI like my job and my life is oddly satisfying. Folks are friendly here, mostly. At least they don't kill each other frequently. Clans don't interfere with my activities. All in all, this the best place I've had my life. I'm free here and no one tells me what to do\nThe only thing driving me mad are rats. They torture me, eating my provisions and ruining my tableware. I have trouble getting rid of them.";
			link.l1 = "Szczury? Tak, są problemem wszystkich...";
			link.l1.go = "ansewer_4_1";
		break;
		
		case "ansewer_4_1":
			dialog.text = "Niestety, jestem tutaj najwięcej nieszczęśliwą osobą, jeśli chodzi o szczury. Inne statki nie są tak terroryzowane przez szczury, a Axel Yost jakoś sobie z nimi poradził raz na zawsze. Co do mnie, mam tu całe armie szczurów pełzających. Eh, mówili mi, że istnieje specjalny amulet zwany Bogiem Szczurów.\nWygląda jak maska nietoperza. Mówią, że ten amulet straszy szczury na śmierć. Przypuszczam, że ktoś sprzedał Axelowi ten amulet, on kupuje i odsprzedaje każdy kawałek śmieci, który znajdą na zewnętrznym pierścieniu.\nChciałbym, żeby ktoś przyniósł mi ten amulet, oferuję tej osobie królewską nagrodę!";
			link.l1 = "Interesujące...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
			npchar.quest.rat = "true";
		break;
		//<-- информационный блок
		
		//--> выпивка
		case "drink":
			if (CheckAttribute(pchar, "questTemp.Rum") && sti(pchar.questTemp.Rum) > 4)
			{
				dialog.text = ""+pchar.name+", myślę, że powinieneś przestać. Nie daj Boże, wpadniesz w kłopoty lub wypadniesz za burtę, by stać się posiłkiem dla krabów... To nie jest dobry pomysł, by tutaj pić za dużo, wielu ludzi zginęło z tego powodu.";
				link.l1 = "Hm... Myślę, że masz rację, Sancho - już mi wystarczy. Dzięki za troskę!";			
				link.l1.go = "exit";
			}
			else
			{
				AddMoneyToCharacter(pchar, -25);
				if(!IsEquipCharacterByArtefact(pchar, "totem_01"))
				{
					if (CheckAttribute(pchar, "questTemp.Rum"))
					{
						pchar.questTemp.Rum = sti(pchar.questTemp.Rum) + 1;
					}
					else pchar.questTemp.Rum = 1;
				}
				else 
				{
					if(CheckAttribute(pchar, "questTemp.Rum")) DeleteAttribute(pchar, "questTemp.Rum");
				}				
				WaitDate("",0,0,0, 0, 30);
				
				dialog.text = "Jesteś mile widziany, kumplu. Tylko dwadzieścia pięć pesos za pintę mojego najlepszego rumu!";
				link.l1 = RandPhraseSimple(LinkRandPhrase("Cóż, za twoje zdrowie i za dobrobyt twojej tawerny, kumplu!","No cóż, za tych, którzy są na morzu!","Zatem, za mieszkańców waszej Wyspy!"),LinkRandPhrase("Cóż, na Wyspę, i oby trwała wiecznie!","Niechaj wicher zawsze sprzyja naszym uczynkom!","Zatem, na szczęście, radość i... kobiety!"));		
				link.l1.go = "drink_1";
			}
		break;
		
		case "drink_1":
			DialogExit();
			LAi_Fade("", "");
			if (CheckAttribute(pchar, "questTemp.Rum"))
			{
				if (sti(pchar.questTemp.Rum) < 3) LAi_AlcoholSetDrunk(pchar, 51, 5600);
				else LAi_AlcoholSetDrunk(pchar, 71, sti(pchar.questTemp.Rum)*2800);
			}
		break;
		
		case "drink_sit":
			if (chrDisableReloadToLocation || pchar.questTemp.Saga.SharkHunt == "barmen_whiskey" || pchar.questTemp.Saga.SharkHunt == "whiskey_poison") //идёт квест
			{
				dialog.text = "Nie sądzę, że to dobry pomysł, abyś teraz pił. Zaufaj mi...";
				link.l1 = "Dobrze.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye") || CheckAttribute(pchar, "questTemp.LSC.MaryWait")) // подружился с Мэри
			{
				dialog.text = "Heh, jesteś dziwnym człowiekiem... Czyżbyś nie miał tu nikogo, z kim mógłbyś spędzić czas na Wyspie? Człowieku, Mary mnie zabije, jeśli pozwolę ci tu zostać i upić się samemu. Przyjdź tu wieczorem razem i bawcie się do świtu, jeśli chcesz.";
				link.l1 = "Dobrze...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Żaden problem, kamracie. Za jedyne trzysta pesos dostaniesz świetną butelkę "+LinkRandPhrase("Hiszpański","Włoski","Francuski")+"  wino - i baw się, jak długo chcesz.";
				link.l1 = "Dzięki!";
				link.l1.go = "drink_sit_1";
			}
		break;
		
		case "drink_sit_1":
			DialogExit();
			sld = ItemsFromID("potionrum");
			sld.shown = true;
			sld.startLocation = "FleuronTavern";
			sld.startLocator = "bottle";
			DoQuestReloadToLocation("FleuronTavern", "quest", "sit2", "LSC_DrinkSit");
		break;
		//<-- выпивка
		
		//--> сон в таверне
		case "room":
   			if (chrDisableReloadToLocation || pchar.questTemp.Saga.SharkHunt == "barmen_whiskey" || pchar.questTemp.Saga.SharkHunt == "whiskey_poison") //идёт квест
			{
				dialog.text = "Nie sądzę, że powinieneś teraz spać. Uwierz mi...";
				link.l1 = "Dobrze.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye") || CheckAttribute(pchar, "questTemp.LSC.MaryWait")) // подружился с Мэри
			{
				if(!isDay())
				{
					dialog.text = "Jeszcze nigdy nie spotkałem tak dziwnego człowieka. Piękna dziewczyna czeka na niego w 'Kowalni Ceres', a on zamierza spędzić noc w tawernie. Nawet nie myśl, że pozwolę ci tu spać. Mary by mnie za to zabiła.";
					link.l1 = "Dobrze...";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Możesz odpocząć na górze do wieczora. Ale nie pozwolę ci zostać tu na noc - Mary by mnie za to zabiła. Przykro mi...";
					link.l1 = "Dobrze. Zostanę tu do wieczora...";
					link.l1.go = "hall_night_wait";
					link.l2 = "Dobrze... Poradzę sobie bez snu.";
					link.l2.go = "exit";
				}
				break;
			}
			dialog.text = "Możesz spać w łóżku na górze za jedyne dwadzieścia pesos. Kiedy mam cię obudzić?";
			if(!isDay())
			{
				link.l1 = "Rano.";
				link.l1.go = "hall_day_wait";
			}
			else
			{
				link.l1 = "Przed zmierzchem.";
				link.l1.go = "hall_night_wait";
				link.l2 = "Następnego ranka.";
				link.l2.go = "hall_day_wait";
			}
			link.l3 = "Zmieniliem zdanie. Nie chcę spać.";
			link.l3.go = "exit";
		break;
		
		case "hall_night_wait":
			AddMoneyToCharacter(pchar, -20);
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			TavernWaitDate_LSC("wait_night");
		break;
		
		case "hall_day_wait":
			AddMoneyToCharacter(pchar, -20);
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			TavernWaitDate_LSC("wait_day");
		break;
		//<-- сон в таверне
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}

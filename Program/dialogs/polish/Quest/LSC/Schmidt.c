// Юрген Шмидт - оружейник
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp, iRem;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	string NodeName = Dialog.CurrentNode;
	string NodePrevName = "";
	if (CheckAttribute(NextDiag, "PrevNode")) NodePrevName = NextDiag.PrevNode;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = "Słuchaj, panie, czemu pozwoliłeś, żeby pięści poszły w ruch, co? Nie masz czego szukać w moim warsztacie, dopóki jesteś naszym wrogiem. Wynocha!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) // стал другом нарвалов
				{
					dialog.text = "Ach, "+GetFullName(pchar)+"! Słyszałem o twoich czynach. Dobrze, że zostałeś przyjacielem Donalda i naszym sprzymierzeńcem. Narwale potrafią docenić przyjaźń, mogę ci to zapewnić.";
					link.l1 = "Mam nadzieję. Czy mogę teraz liczyć na twoje usługi?";
					link.l1.go = "friend";
				}
				else
				{
					dialog.text = "Więc? Czego chcesz?";
					link.l1 = TimeGreeting()+". Nazywam się "+GetFullName(pchar)+"  A ja po prostu spaceruję, poznając ludzi. Czy przeszkadzam?";
				link.l1.go = "meeting";
				}
				npchar.quest.meeting = "1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) // стал другом нарвалов
				{
					dialog.text = "Ach, "+GetFullName(pchar)+"! Słyszałem o twoich czynach. Dobrze, że zostałeś przyjacielem Donalda i naszym sojusznikiem. Narwale potrafią docenić przyjaźń, mogę ci to zapewnić.";
					link.l1 = "Mam nadzieję. Czy mogę teraz liczyć na twoje usługi?";
					link.l1.go = "friend";
				}
				else
				{
					dialog.text = "Ach, "+GetFullName(pchar)+" ! Chcesz znowu porozmawiać? Muszę cię rozczarować, nie mam na to ani czasu, ani ochoty.";
					link.l1 = "Dobrze, nie będę cię niepokoić.";
					link.l1.go = "exit";
				}
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Dokładnie! Przeszkadzasz mi, panie. Jestem Jurgen Schmidt, rusznikarz i kowal klanu Narwalów. Zaopatruję naszych ludzi w broń. Ale zrobienie dobrej klingi, klucza, zamka czy naprawa mechanizmu wieżowego muszkietonu wymaga czasu. To wymaga dużo czasu, cierpliwości i uwagi. Dlatego nie lubię, gdy ludzie mi przeszkadzają.";
			link.l1 = "Czy robisz broń? Czy mogę coś u ciebie zamówić?";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Nie. Tworzę broń tylko dla członków klanu Narwali. To moja zasada i będę się jej trzymać. Więc nawet nie licz na to, panie. Dołącz do naszego klanu lub przynajmniej zostań naszym sojusznikiem, a wtedy porozmawiamy.";
			link.l1 = " Dobrze. Zatem cię opuszczam. Przepraszam za kłopot!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "friend":
			dialog.text = "Możesz. Przyjaciel Narwali jest także moim przyjacielem, więc cię słucham.";
			link.l1 = "Chciałbym zamówić ostrze.";
			link.l1.go = "blade";
			if (CheckAttribute(npchar, "quest.narval_blade") && pchar.questTemp.LSC.Mary == "alive")
			{
				link.l2 = "Słyszałem, że wykonałeś specjalne ostrze dla nieżyjącego Alana Milrowa. Widziałem ten pałasz, to wspaniała broń. Czy mogę zamówić coś podobnego?";
				link.l2.go = "narval";
			}
			link.l3 = "Nie mam jeszcze pomysłów. Pomyślę o tym, a potem wrócę!";
			link.l3.go = "exit";
			NextDiag.TempNode = "Jurgen";
		break;
		
		case "Jurgen":
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "Ha, "+GetFullName(pchar)+"! A więc nie utonąłeś? Co za niespodzianka! Czy naprawdę żyjesz?";
				link.l1 = "Nie martw się, Jurgen. Żyję! Nie miałem zamiaru się utopić...";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				NextDiag.TempNode = "Jurgen";
				break;
			}
			dialog.text = "Ach, "+GetFullName(pchar)+" ! Czego chcesz?";
			if (CheckAttribute(npchar, "quest.narval_blade") && npchar.quest.narval_blade == "ferrum")
			{
				if (GetCharacterItem(pchar, "jewelry11") >= 3)
				{
					link.l4 = "Przyniosłem ci trzy kawałki specjalnego żelaza, jak prosiłeś. Spójrz, czy to jest to, czego chcesz?";
					link.l4.go = "narval_7";
				}
				if (CheckCharacterItem(pchar, "meteorite"))
				{
					link.l5 = "Spójrz, Jurgen. Znalazłem ciekawy sztabek żelaza na dnie, ale waży znacznie więcej, niż prosiłeś. Pięć funtów, nie mniej.";
					link.l5.go = "narval_7_1";
				}
			}
			if (!CheckAttribute(npchar, "quest.blade_done"))
			{
				link.l1 = "Chciałbym zamówić ostrze.";
				if (!CheckAttribute(npchar, "quest.blade_rules")) link.l1.go = "blade";
				else link.l1.go = "blade_4";
			}
			if (CheckAttribute(npchar, "quest.blade_payseek"))
			{
				link.l1 = "Przywiozłem ci więcej dublonów jako zapłatę za ostrze.";
				link.l1.go = "blade_3";
			}
			if (CheckAttribute(npchar, "quest.narval_blade") && pchar.questTemp.LSC.Mary == "alive" && npchar.quest.narval_blade == "begin" && pchar.questTemp.LSC != "return") // patch-9
			{
				link.l2 = "Słyszałem, że zrobiłeś specjalny miecz dla świętej pamięci Alana Milrowa. Widziałem ten pałasz, to wspaniała broń. Czy mogę zamówić coś podobnego?";
				link.l2.go = "narval";
			}
			if (CheckAttribute(npchar, "blade_date") && GetNpcQuestPastDayParam(npchar, "blade_date") >= 20)
			{
				link.l1 = "Przyszedłem po moje zamówienie. Musi już być gotowe, prawda?";
				link.l1.go = "blade_done_2";
			}
			link.l3 = "Nie, to nic takiego, po prostu chciałem cię przywitać.";
			link.l3.go = "exit";
			NextDiag.TempNode = "Jurgen";
		break;
		
		// --> заказ клинков
		case "blade":
			dialog.text = "Dobrze. Ale mam pewne specjalne wymagania przy każdym zamówieniu, więc najpierw uważnie posłuchaj.";
			link.l1 = "Zamieniam się w słuch.";
			link.l1.go = "blade_1";
		break;
		
		case "blade_1":
			dialog.text = "Możesz zamówić ode mnie tylko jedno ostrze i tylko raz. Nie robię konkretnej broni, możesz podać tylko typ - rapier, szabla lub miecz szeroki. Pomyśl mądrze, zanim dokonasz wyboru, ostateczne cechy i jakość ostrza będą zależeć od materiałów, jakie posiadam w danej chwili\nTeraz. Wykonanie twojego zamówienia zajmie dwadzieścia dni. Przyjmuję tylko dublony. Tysiąc monet. Pieniądze z góry.";
			link.l1 = "Naprawdę! Drogie...";
			link.l1.go = "blade_2";
		break;
		
		case "blade_2":
			dialog.text = "Jest drogie. Ale robię doskonałe klingi, więc cena jest całkiem uczciwa. To twój wybór, bez presji.";
			link.l1 = "Rozumiem, Jurgen. Tak, chcę złożyć zamówienie.";
			link.l1.go = "blade_3";
			link.l2 = "Hm. Potrzebuję czasu, aby się zastanowić, zanim coś od ciebie zamówię. Porozmawiamy o tym później!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Jurgen";
			npchar.quest.blade_rules = "true";
			npchar.quest.blade_dublon = 1000;
			AddQuestRecord("LSC", "17");
		break;
		
		case "blade_3":
			dialog.text = "Bardzo dobrze. Daj mi zatem swoje doubloony.";
			if (PCharDublonsTotal() > 0)
			{
				npchar.quest.blade_pay = PCharDublonsTotal();
				link.l1 = "Oto, proszę. Mam "+FindRussianQtyString(sti(npchar.quest.blade_pay))+".";
				link.l1.go = "blade_pay";
			}
			link.l2 = "Hm. Niestety, nie mam żadnych przy sobie teraz. Ale na pewno je przyniosę i będziemy kontynuować naszą rozmowę.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Jurgen";
		break;
		
		case "blade_4":
			dialog.text = "Więc to twój ostateczny wybór? Jesteś pewien?";
			link.l1 = "Tak, jestem.";
			link.l1.go = "blade_3";
		break;
		
		case "blade_pay": // оплата
			if (sti(npchar.quest.blade_dublon) < sti(npchar.quest.blade_pay)) // полная сумма
			{
				npchar.quest.blade_pay = sti(npchar.quest.blade_dublon);
				iTemp = 0;
			}
			else iTemp = sti(npchar.quest.blade_dublon)-sti(npchar.quest.blade_pay);
			npchar.quest.blade_dublon = iTemp; // запоминаем остаток
			RemoveDublonsFromPCharTotal(sti(npchar.quest.blade_pay));
			Log_Info("You have given "+sti(npchar.quest.blade_pay)+" doubloons");
			PlaySound("interface\important_item.wav");
			if (iTemp == 0)
			{
				dialog.text = "Wspaniale. Zapłaciłeś mi za moją pracę i materiały, więc mogę teraz zacząć.";
				link.l1 = "Czy mogę złożyć zamówienie?";
				link.l1.go = "blade_done";
			}
			else
			{
				dialog.text = "Dobrze. Przyjmuję twoje dublony. Musisz mi przynieść "+FindRussianQtyString(sti(npchar.quest.blade_dublon))+" więcej.";
				link.l1 = "Przyniosę ci je, kiedy je zdobędę.";
				link.l1.go = "exit";
				npchar.quest.blade_payseek = "true";
			}
		break;
		
		case "blade_done":
			DeleteAttribute(npchar, "quest.blade_payseek");
			dialog.text = "Jasne! Jaki rodzaj lubisz najbardziej? Szpady, szable czy miecze szerokie?";
			link.l1 = "Rapiery. Lubię elegancką i lekką broń.";
			link.l1.go = "rapier";
			link.l2 = "Szable. Moim zdaniem są optymalne.";
			link.l2.go = "sabre";
			link.l3 = "Szable na pewno! Tnij i siekaj!";
			link.l3.go = "palash";
		break;
		
		case "rapier":
			npchar.quest.blade_done = SelectJurgenBladeDone("rapier");
			dialog.text = "Jak sobie życzysz. Wróć po swoje zamówienie za dwadzieścia dni, nie wcześniej.";
			link.l1 = "Dzięki!   Zobaczymy się za dwadzieścia dni.  Do widzenia, Jurgen.";
			link.l1.go = "blade_done_1";
		break;
		
		case "sabre":
			npchar.quest.blade_done = SelectJurgenBladeDone("sabre");
			dialog.text = "Jak sobie życzysz. Wróć po swoje zamówienie za dwadzieścia dni, nie wcześniej.";
			link.l1 = "Dzięki! Zobaczymy się za dwadzieścia dni. Do widzenia, Jurgen.";
			link.l1.go = "blade_done_1";
		break;
		
		case "palash":
			npchar.quest.blade_done = SelectJurgenBladeDone("palash");
			dialog.text = "Jak sobie życzysz. Wróć po swoje zamówienie za dwadzieścia dni, nie wcześniej.";
			link.l1 = "Dzięki! Zobaczymy się za dwadzieścia dni. Do widzenia, Jurgen.";
			link.l1.go = "blade_done_1";
		break;
		
		case "blade_done_1":
			DialogExit();
			SaveCurrentNpcQuestDateParam(npchar, "blade_date");
			NextDiag.CurrentNode = "Jurgen";
			AddQuestRecord("LSC", "18");
		break;
		
		case "blade_done_2":
			dialog.text = "Tak. Twoja klinga jest gotowa. Proszę, weź ją i używaj. Zrozumiesz, że jest warta swojej ceny, gdy tylko jej dotkniesz.";
			link.l1 = "Dzięki, Jurgen.";
			link.l1.go = "blade_done_3";
		break;
		
		case "blade_done_3":
			DialogExit();
			NextDiag.CurrentNode = "Jurgen";
			GiveItem2Character(pchar, npchar.quest.blade_done);
			PlaySound("interface\important_item.wav");
			DeleteAttribute(npchar, "blade_date");
		break;
		
		// заказ палаша Нарвал для Мэри
		case "narval":
			dialog.text = "Niestety, mój przyjacielu, muszę odmówić z dwóch powodów. Po pierwsze, zrobię taki miecz tylko dla członka klanu Narwali i tylko dla kogoś wyjątkowego. Po drugie, nie mam materiałów na to.";
			link.l1 = "A jaki to specjalny żelaz, którego potrzebujesz? Słyszałem, że zdobyli je z dna...";
			link.l1.go = "narval_1";
		break;
		
		case "narval_1":
			dialog.text = "Dokładnie. Wszędzie wokół naszej mielizny są rozrzucone kawałki tego metalu. Nie wiem, jak się tu dostały. Ale to żelazo jest wyjątkowe, nigdy nie rdzewieje, a ostrza z niego wykonane nigdy się nie tępią. Więc jeśli udałoby ci się zdobyć to żelazo, moglibyśmy rozwiązać tę sprawę. Ale jest jeszcze jeden problem, nie jesteś Narwalem...";
			link.l1 = "Czy to naprawdę ma znaczenie?";
			link.l1.go = "narval_2";
		break;
		
		case "narval_2":
			dialog.text = "Tak. Możesz to uznać za moją fanaberię, ale taki pałasz wykonam tylko dla Narwala.";
			link.l1 = "Cóż... Dobrze, akceptuję to. Ale mam pomysł. Czy mogę zamówić tę klingę dla członka klanu Narwali?";
			link.l1.go = "narval_3";
		break;
		
		case "narval_3":
			dialog.text = "Hm. Przypuszczam, że mogę to zrobić, jeśli przyniesiesz mi żelazo. To nie naruszy moich zasad... Dla kogo chcesz, żebym wykonał ten miecz?";
			link.l1 = "Za Czerwoną Marię. Ona jest z klanu Narwali i zasługuje na posiadanie tak doskonałej broni.";
			link.l1.go = "narval_4";
		break;
		
		case "narval_4":
			dialog.text = "Ha! Sam mógłbym na to wpaść. Staję się za stary... No cóż, zgadzam się. Mary będzie naprawdę szczęśliwa z takiego prezentu, jestem pewien... Przynieś mi żelazo, a zrobię szablę. Wezmę za ostrze... ah, nieważne, zrobię to za darmo. To będzie prezent nie tylko od ciebie, ale od nas obojga.";
			link.l1 = "Dzięki! Ile żelaza będziesz potrzebować?";
			link.l1.go = "narval_5";
		break;
		
		case "narval_5":
			dialog.text = "Te kawałki, które znajdowaliśmy na dnie, były całkiem takie same - po funcie każdy. Potrzebuję trzech takich kawałków.";
			link.l1 = "Dobrze. Spróbuję ich znaleźć. I porozmawiamy ponownie.";
			link.l1.go = "narval_6";
		break;
		
		case "narval_6":
			DialogExit();
			npchar.quest.narval_blade = "ferrum";
			NextDiag.CurrentNode = "Jurgen";
			// кладем гигантский кусок метеорита на дно
			sld = ItemsFromID("meteorite");
			sld.shown = true;
			sld.startLocation = "underwater";
			sld.startLocator = "item"+(rand(7)+1);
			Log_TestInfo("Meteorite in the locator " + sld.startLocator);
			pchar.quest.LSC_narval_ferrum.win_condition.l1 = "item";
			pchar.quest.LSC_narval_ferrum.win_condition.l1.item = "meteorite";
			pchar.quest.LSC_narval_ferrum.function = "LSC_NarvalFerrum";
			AddQuestRecord("LSC", "19");
		break;
		
		case "narval_7":
			RemoveItems(pchar, "jewelry11", 3);
			PlaySound("interface\important_item.wav");
			dialog.text = "Niech no zobaczę... Tak, to on! Czy trudno było znaleźć takie małe kawałki na dnie?";
			link.l1 = "Cóż, cóż mogę powiedzieć... Mary jest warta takich kłopotów, prawda?";
			link.l1.go = "narval_8";
			pchar.quest.LSC_narval_ferrum.over = "yes"; //снять прерывание
		break;
		
		case "narval_7_1":
			RemoveItems(pchar, "meteorite", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Niech no zobaczę... A to ci dopiero! Tak, to jest dolne żelazo, ale nigdy wcześniej nie widziałem tak dużych kawałków. To wystarczy na zrobienie szabli. Czy trudno było to znaleźć?";
			link.l1 = "Cóż, co mogę powiedzieć... Mary jest warta takich kłopotów, prawda?";
			link.l1.go = "narval_8";
		break;
		
		case "narval_8":
			dialog.text = "Coraz bardziej cię lubię, "+pchar.name+"... Zatem dobrze. Teraz moja kolej, by pracować w imieniu naszej pięknej Amazonki. Zajmie dwa dni, by wykonać ten pałasz, odłożę inne zamówienia.\nPrzyprowadź mi Mary pojutrze. Nie mów jej, to niespodzianka. Będzie szczęśliwa jak dziecko.";
			link.l1 = "Dobrze, Jurgen. Umowa stoi! Do zobaczenia pojutrze!";
			link.l1.go = "narval_9";
		break;
		
		case "narval_9":
			DialogExit();
			npchar.quest.narval_blade = "work";
			NextDiag.CurrentNode = "narval_10";
			SetFunctionTimerCondition("LSC_NarvalBladeForMary", 0, 0, 2, false); // таймер
			AddQuestRecord("LSC", "21");
		break;
		
		case "narval_10":
			dialog.text = ""+pchar.name+", nie zawracaj mi głowy. Chcesz, żebym zdążył zrobić ten pałasz na czas, prawda?";
			link.l1 = "Tak, oczywiście. Odchodzę.";
			link.l1.go = "exit";
			NextDiag.TempNode = "narval_10";
		break;
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Co tam robisz, co? Złodzieju!","Spójrz tylko na to! Ledwie się zatopiłem w rozmyślaniach, a ty postanowiłeś sprawdzić moją skrzynię!","Postanowiłeś sprawdzić moje skrzynie? Nie ujdzie ci to na sucho!");
			link.l1 = "Cholera!";
			link.l1.go = "fight";
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Słuchaj, lepiej schowaj broń. Denerwuje mnie.","Wiesz, bieganie z ostrzem nie jest tutaj tolerowane. Schowaj to.","Słuchaj, nie udawaj średniowiecznego rycerza biegającego z mieczem. Odłóż go, to do ciebie nie pasuje...");
			link.l1 = LinkRandPhrase("Dobrze.","Dobrze.","Jak mówisz...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Słuchaj, jestem obywatelem miasta i proszę cię o schowanie broni.","Słuchaj, jestem obywatelem miasta i proszę cię, byś schował swój miecz.");
				link.l1 = LinkRandPhrase("Dobrze.","Dobrze.","Jak powiadasz...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Uważaj, kolego, biegając z bronią. Mogę się zdenerwować...","Nie lubię, gdy mężczyźni przechodzą przede mną z gotową bronią. Przeraża mnie to...");
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

string SelectJurgenBladeDone(string _sType)
{
	string sBlade;
	switch (_sType)
	{
		case "rapier":
			if (sti(pchar.rank) > 15) sBlade = "q_blade_18"; 
			else sBlade = "q_blade_16";
		break;
		
		case "sabre":
			if (sti(pchar.rank) > 15) sBlade = "q_blade_19"; 
			else sBlade = "q_blade_10";
		break;
		
		case "palash":
			if (sti(pchar.rank) > 15) sBlade = "q_blade_21"; 
			else sBlade = "q_blade_13";
		break;
	}
	return sBlade;
}

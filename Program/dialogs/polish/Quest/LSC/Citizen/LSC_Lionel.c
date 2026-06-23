// Лайонел Маскетт - мещанин
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
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && int(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "Nie chcę z tobą rozmawiać. Atakujesz spokojnych cywilów bez powodu i prowokujesz ich do walki. Zmykaj stąd!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Witaj, "+GetAddress_Form(NPChar)+" Czy jesteś tu nowicjuszem?";
				link.l1 = TimeGreeting()+". Nazywam się "+GetFullName(pchar)+"Tak, jestem.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ach, "+GetFullName(pchar)+"! "+TimeGreeting()+"Chcesz czegoś?";
				link.l1 = LinkRandPhrase("Masz coś ciekawego do powiedzenia?","Czy wydarzyło się coś nowego na wyspie?","Opowiesz mi ostatnie plotki?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Chcę zadać ci kilka pytań o wyspę.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Chciałem tylko wiedzieć, jak się masz. Do zobaczenia!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Nazywam się Lionell. Miło cię poznać. Jak się tu dostałeś?";
			link.l1 = "Na barku... Słyszałem, że jest tu jakaś baza przemytników i postanowiłem ją zbadać... Zbadałem. Bark jest zatopiony, a ja jestem tutaj.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Czy oni naprawdę uważają Wyspę za bazę przemytników?";
			link.l1 = "Cóż, nie oficjalnie. Większość nawet nie wierzy w twoje istnienie.";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Serio... A dlaczego mieliby? W rzeczywistości nie istniejemy. Nie możesz opuścić tego miejsca. Choć mówią, że było połączenie z Kubą... Ale ja tego nie pamiętam, a mieszkam tu prawie osiem lat.";
			link.l1 = "Rozumiem. Było mi miło z tobą porozmawiać. Do zobaczenia!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Masz coś ciekawego do powiedzenia?","Czy wydarzyło się coś nowego na wyspie?","Czy opowiesz mi ostatnie plotki?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Chcę zadać ci kilka pytań o wyspę.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Słucham.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Jak tu dotarłeś?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Czy chciałbyś wrócić na stały ląd?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "A co ludzie robią tutaj, na Wyspie Sprawiedliwości?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "A skąd tutaj bierzecie wszystkie rzeczy? Żywność, tkaniny, napoje?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Bez pytań. Wybacz...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "To dziwna opowieść. Ta Wyspa jest jedynym miejscem na wszystkich Karaibach, które widziałem. Kiedy sprawy poszły źle dla mnie, wypłynąłem na statku handlowym ze starej Anglii. Miałem zamiar znaleźć pracę w Belize, zostać urzędnikiem w porcie. Ale nigdy nie dotarliśmy do Belize\nNie jestem żeglarzem, więc nie znam szczegółów. Nadeszła burza i następnego dnia nasz statek został zniszczony przez rafy. Nigdy nie zapomnę tego strasznego uderzenia, krzyków\nKtoś krzyknął, że w kadłubie jest dziura, ludzie zaczęli skakać za burtę. Ja... nie umiem pływać. Więc zostałem. Ironią losu, to uratowało mi życie. Statek przetrwał, a burza ucichła o świcie\nPodjąłem jedyną słuszną decyzję, zanim opuściłem statek. Wziąłem trochę jedzenia, zbudowałem tratwę i przepłynąłem przez spokojne morze do zewnętrznego pierścienia. Tak właśnie przeżyłem, jako jedyny z całej załogi.";
			link.l1 = "Widzę...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "To było moje jedyne marzenie przez pierwsze dwa lata tutaj. Ale teraz... Co sprawia, że Wyspa jest gorsza niż jakiekolwiek inne miejsce na świecie? Tak, nie ma tu zielonych pól z owcami, ale jest wspaniałe morze i nocne niebo pełne pięknych gwiazd. Jestem dobrze najedzony, noszę przyzwoite ubrania, na które nie było mnie stać, mieszkając w Anglii. Mam wielu przyjaciół\n Nie, panie, nie chcę opuszczać tego miejsca. Co mnie tam czeka? Praca biurowa pod rządami wrzaskliwego szefa za trzysta peso tygodniowo? Nie ma mowy! Znalazłem tutaj wszystko, czego szukałem, niczego więcej mi nie potrzeba.";
			link.l1 = "Zrozumiałem. Cieszę się dla ciebie!";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Co najbardziej lubią. Klany bawią się w wojnę, piraci sprzedają prowiant, Axel Yost kupuje i sprzedaje rzeczy, Sancho Carpentero podaje napoje i zabawia ludzi, brat Julian modli się, odprawia Mszę i sprzedaje lekarstwa. Loderdale i Solderra intrygują przeciwko sobie, Abbot lubi się wywyższać, Jillian i Tanneke marzą o prawdziwej miłości...";
			link.l1 = "Ciekawe...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Ze statków, mój przyjacielu, ze statków. Ulubionym zajęciem większości jest eksploracja okrętów z zewnętrznego pierścienia i pozyskiwanie z nich rzeczy. Można tam znaleźć wszystko, broń, leki, przyprawy i rum. Wiele statków wciąż pozostaje niezbadanych. Prąd morski często przynosi tu kolejną ofiarę...";
			link.l1 = "Interesujące...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Co ty tam robisz, co? Złodzieju!","Spójrz tylko na to! Ledwie się pogrążyłem w zadumie, a ty postanowiłeś sprawdzić moją skrzynię!","Zdecydowałeś się sprawdzić moje skrzynie? Nie ujdzie ci to na sucho!");
			link.l1 = "Cholera!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Co?! Zdecydowałeś się sprawdzić moje skrzynie? Nie ujdzie ci to na sucho!";
			link.l1 = "Niemądra dziewczyno!";
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
			dialog.text = LinkRandPhrase("Słuchaj, lepiej schowaj broń. Przez nią się denerwuję.","Wiesz, bieganie z ostrzem nie jest tutaj tolerowane. Schowaj to.","Słuchaj, nie udawaj średniowiecznego rycerza biegającego z mieczem. Odłóż go, to do ciebie nie pasuje...");
			link.l1 = LinkRandPhrase("Dobrze.","W porządku.","Jak mówisz...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Słuchaj, jestem obywatelem miasta i prosiłbym cię, byś schował swój miecz.","Słuchaj, jestem obywatelem tego miasta i proszę cię, byś schował swój miecz.");
				link.l1 = LinkRandPhrase("Dobrze.","Dobrze.","Jak mówisz...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Uważaj, kumplu, kiedy biegasz z bronią. Mogę się zdenerwować...","Nie lubię, gdy mężczyźni chodzą przede mną z bronią w pogotowiu. To mnie przeraża...");
				link.l1 = RandPhraseSimple("Zrozumiałem.","Zabieram to.");
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

// Джиллиан Стайнер - просто девушка
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
				dialog.text = "Nie chcę z tobą rozmawiać. Atakujesz spokojnych cywilów bez powodu i prowokujesz ich do walki. Zmykaj!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Och... witaj! Przestraszyłeś mnie. Podszedłeś tak cicho... Czego chcesz?";
				link.l1 = TimeGreeting()+". Nazywam się "+GetFullName(pchar)+" . Jestem nowy tutaj i poznaję miejscowych, i w końcu zdecydowałem się przyjść i porozmawiać z taką piękną damą jak ty. Jak masz na imię?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ach, "+GetFullName(pchar)+"! "+TimeGreeting()+"Chcesz czegoś?";
				link.l1 = LinkRandPhrase("Masz coś ciekawego do powiedzenia?","Czy wydarzyło się coś nowego na wyspie?","Czy opowiesz mi ostatnie plotki?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Chcę zadać ci kilka pytań o wyspie.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Chciałem tylko wiedzieć, jak się miewasz. Do zobaczenia!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Pan mnie zawstydza, ale to i tak przyjemność. Dziękuję za komplement. Nazywam się Jillian, Jillian Steiner. Miło cię poznać.";
			link.l1 = "Ja też, Jillian.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Jesteś tu nowy? I jak się tu dostałeś, powiedz mi? Przeżyłeś katastrofę statku?";
			link.l1 = "Cóż... coś w tym rodzaju. Płynąłem tutaj barką i prawie udało mi się przepłynąć przez rafy, ale niestety uderzyłem w szczątki statków i moja łódź zatonęła. I dopłynąłem tutaj sam.";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "„Och! Więc przybyłeś tu z własnej woli? Niewiarygodne!”";
			link.l1 = "Tak, jestem szalony. Postanowiłem odnaleźć tę Wyspę Sprawiedliwości i w końcu mi się to udało. Choć teraz nie wiem, jak się z niej wydostać.";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Jesteś bardzo odważny albo lekkomyślny. Żeglować tutaj na barce... Teraz będziesz żyć z nami, bo nikt nie zdołał opuścić tego miejsca od dziesięciu lat.";
			link.l1 = "Wciąż mam nadzieję. Dobrze, Jillian, nie będę ci przeszkadzać. Do zobaczenia!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Tak, oczywiście, "+pchar.name+" Słucham.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Jak się tu dostałeś?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Czy chcesz opuścić Wyspę?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "I jak ci mija dzień? Czym się zajmujesz?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Twierdzisz, że nie jesteś zamężna... Czyżby taka piękna dziewczyna nie miała tutaj żadnych adoratorów?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Bez pytań. Przepraszam...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Żeglowałem z Anglii z rodzicami. Chcieliśmy rozpocząć nowe życie i... tutaj rozpocząłem nowe życie. Rodzice zginęli, a ja ledwo przeżyłem. Dotarłem do jakiegoś statku z zewnętrznego pierścienia i leżałem tam nieprzytomny przez dzień, aż znalazł mnie jeden z tutejszych. Umarłbym tam, gdyby mnie nie znalazł.";
			link.l1 = "Widzę...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "A dokąd? Kto mnie potrzebuje i gdzie? Nie mam domu, męża ani pieniędzy. Nigdy nie byłam nigdzie poza tą Wyspą i londyńskimi slumsami. Wydaje się, że to moje przeznaczenie, aby tu żyć...";
			link.l1 = "Jesteś tego pewien?";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Przeważnie pomagam bratu Julianowi w kościele. Zajmuję się też prostymi pracami w sklepie Axela. Tak zarabiam monety. Jestem dziewczyną i nie mogę wspinać się po wrakach statków na zewnętrznym pierścieniu.";
			link.l1 = "Jasne...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Tee-hee... są admiratorzy, tak, ale nie ma wartości. Nie lubię żadnego z nich i nie chcę żyć z mężczyzną, którego nie lubię. Ci, których lubię, nie zwracają na mnie uwagi. Cóż, jestem tylko zwykłą biedną dziewczyną...";
			link.l1 = "To dopiero początek nowego życia dla ciebie...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Co tam robisz, a? Złodzieju!","Spójrz tylko na to! Ledwie pogrążyłem się w rozmyślaniach, a ty postanowiłeś sprawdzić moją skrzynię!","Zdecydowałeś się sprawdzić moje skrzynie? Nie ujdzie ci to na sucho!");
			link.l1 = "Cholera!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Co?! Zdecydowałeś się sprawdzić moje skrzynie? Nie ujdzie ci to na sucho!";
			link.l1 = "Nierozważna dziewczyno!";
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
			dialog.text = LinkRandPhrase("Słuchaj, lepiej schowaj swoją broń. To mnie denerwuje.","Wiesz, bieganie z ostrzem nie jest tu tolerowane. Schowaj je.","Słuchaj, nie udawaj średniowiecznego rycerza biegającego z mieczem. Schowaj to, nie pasuje do ciebie...");
			link.l1 = LinkRandPhrase("Dobrze.","Dobrze.","Jak mówisz...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Słuchaj, jestem obywatelem miasta i proszę cię, byś opuścił swój miecz.","Słuchaj, jestem obywatelem miasta i proszę cię, byś schował swój miecz.");
				link.l1 = LinkRandPhrase("Dobrze.","Cóż, więc.","Jak powiadasz...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Bądź ostrożny, kolego, biegając z bronią. Mogę się zdenerwować...","Nie lubię, gdy mężczyźni chodzą przede mną z gotową bronią. To mnie przeraża...");
				link.l1 = RandPhraseSimple("Rozumiem.","Zabieram to.");
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

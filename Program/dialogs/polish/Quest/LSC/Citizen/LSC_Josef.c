// Джозеф Лодердэйл - английский военный офицер
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
				dialog.text = "Nie chcę z tobą rozmawiać. Atakujesz spokojnych cywilów bez powodu i prowokujesz ich do walki. Zjeżdżaj!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Dzień dobry, panie. Cieszę się, że spotykam tu szlachetnego człowieka.";
				link.l1 = TimeGreeting()+"Tak naprawdę, byłem tak blisko zwykłych ludzi podczas mojego pobytu na Archipelagu, że zacząłem zapominać o swoim szlachectwie...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = TimeGreeting()+", "+GetFullName(pchar)+"! Cieszę się, że cię spotkałem! Co powiesz?";
				link.l1 = LinkRandPhrase("Masz coś ciekawego do powiedzenia?","Zdarzyło się coś nowego na wyspie?","Czy opowiesz mi ostatnie plotki?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Chcę zadać ci kilka pytań o wyspę.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Chciałem tylko wiedzieć, jak się miewasz. Do zobaczenia!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Och, i jeszcze jesteś skromny! Prawdziwy dżentelmen! Myślę, że będziemy przyjaciółmi, nie jesteś jak ten nadęty opat... Pozwól, że się przedstawię - Josef Loderdale, były kapitan angielskiej floty morskiej.";
			link.l1 = "Miło cię poznać. "+GetFullName(pchar)+"do usług!";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Jest dość nudno żyć tutaj, więc odwiedź tawernę wieczorem, możemy wypić kieliszek wina i odbyć interesującą rozmowę...";
			link.l1 = "Będę o tym pamiętać, panie. Do zobaczenia!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Masz coś ciekawego do powiedzenia?"," Czy na wyspie wydarzyło się coś nowego?","Opowiesz mi ostatnie plotki?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Chcę zadać ci kilka pytań o wyspę.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;

//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Z przyjemnością odpowiem na twoje pytania, panie...";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Jak tu trafiłeś?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Jakie usługi mogę tu otrzymać?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Jako oficer wojskowy, jakie masz zdanie na temat dominacji piratów tutaj?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Widziałem tu wiele zamkniętych skrzyń, na Wyspie. Ludzie sobie nie ufają, prawda?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Nie ma pytań. Przepraszam...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Pełniłem służbę wojskową. Walczyłem z hiszpańskim szkunerem wojennym, wierzyliśmy, że to ten statek odpowiedzialny za plądrowanie angielskich kupców. Walka była długa, prawie ich mieliśmy, ale nagła burza pokrzyżowała plany. W rezultacie oba statki rozbiły się w pobliżu zewnętrznych pierścieni\nLos ma poczucie humoru, ja i kapitan hiszpański przeżyliśmy. Być może już go tu spotkałeś. Jego nazwisko to Lorenzo Solderra, rzadki kawał łotra. Uważaj na niego.";
			link.l1 = "Rozumiem. Wezmę pod uwagę twoje ostrzeżenie...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Jeśli potrzebujesz odpoczynku - odwiedź tawernę Sancho. Zawsze zapewni ci jedzenie, napoje i łóżko. Jeśli chcesz zdobyć proch, amunicję, broń i inne rzeczy - idź do Axela Yosta, prowadzi lokalny sklep. Leki można kupić od brata Juliana, sprzedaje on również święte przedmioty w swoim kościele\nNarwale mają bardzo utalentowanego kowala, nazywa się Schmidt. Mówią, że tworzy doskonałe ostrza. Jest jeszcze jeden utalentowany rzemieślnik wśród Narwali, ale nie udało mi się dowiedzieć o nim więcej\n A jeśli masz problemy z piratami lub klanami, zobacz się z Giuseppe Fazio, on jest specjalistą od takich spraw.";
			link.l1 = "Dzięki za informację!";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Nie mogę powiedzieć, że mi się to podoba, ale nie mogę nic na to poradzić. Przyznaję, że piratom zajęło tylko kilka dni, by zaprowadzić pokój i ustanowić porządek na Wyspie Sprawiedliwości. Zanim przybyli piraci, klany regularnie się ze sobą biły, a zwykli ludzie cierpieli najbardziej\nPoza tym, sprzedają jedzenie bardzo schludnie i uczciwie - obywatele dostają je za bardzo niską cenę, nie można tego samego powiedzieć o klanach, piraci zdzierają z nich skórę za rozpoczęcie wojny\nZnam bardzo mądrego pirata, nazywa się Layton Dexter. To on zajmuje się handlem. Rozmawiałem z nim raz, zastanawiam się, jak taki utalentowany i dobrze wykształcony człowiek, który zna się na taktyce, kartografii i handlu, dołączył do piratów\nZajęło mu tylko kilka dni, by stworzyć doskonałą mapę Wyspy. Widziałem ją, ma prawie wszystko. Wierzę, że zrobił ją na wypadek możliwej wojny z klanami...";
			link.l1 = "Widzę...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
			sld = characterFromId("Dexter");
			sld.quest.map = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "To jest właściwa rzecz do zrobienia. Mówią, że dawno temu kradzież była normalną rzeczą na Wyspie, dopóki wszystkie skrzynie nie dostały nowych zamków. A jednak, wciąż jest ktoś, kto potrafi otwierać te skrzynie. Chociaż kradnie tylko rum i tanią biżuterię, nigdy nie zabrał złota ani pieniędzy\nWszystkie zamki są unikalne, nie ma dwóch takich samych kluczy - Jurgen Schmidt zadbał o to. Wytwarza nie tylko ostrza, ale także zamki i klucze. Powiedziano mi, że zewnętrzne skrzynie nie zawierają cennych rzeczy, poważne przedmioty zawsze trzymane są na statkach.";
			link.l1 = "Interesujące...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Co tam robisz, co? Złodzieju!","Spójrz tylko na to! Jak tylko pogrążyłem się w zadumie, postanowiłeś sprawdzić moją skrzynię!","Zdecydowałeś się sprawdzić moje skrzynie? Nie ujdzie ci to na sucho!");
			link.l1 = "Kurwa!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Co?! Postanowiłeś sprawdzić moje skrzynie? Nie ujdzie ci to na sucho!";
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
			dialog.text = LinkRandPhrase("Słuchaj, lepiej schowaj swoją broń. To mnie denerwuje.","Wiesz, bieganie z ostrzem nie jest tutaj tolerowane. Schowaj to.","Słuchaj, nie udawaj średniowiecznego rycerza biegającego z mieczem. Schowaj to, nie pasuje do ciebie...");
			link.l1 = LinkRandPhrase("Dobrze.","Jak sobie życzysz...","Jak powiadasz...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Słuchaj, jestem obywatelem miasta i proszę cię, byś schował swój miecz.","Słuchaj, jestem obywatelem miasta i proszę cię, byś schował swój miecz.");
				link.l1 = LinkRandPhrase("Dobrze.","Jak sobie życzysz...","Jak mówisz...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Uważaj, kumplu, biegając z bronią. Mogę się zdenerwować...","Nie lubię, gdy mężczyźni przechodzą przede mną z bronią w pogotowiu. To mnie przeraża...");
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

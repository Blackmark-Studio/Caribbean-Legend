// Виктор Кассель - бандит
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
				dialog.text = "Hm... Czego chcesz, przyjacielu? Jeśli chcesz pogadać, muszę cię rozczarować. Nie mam ochoty na rozmowę.";
				link.l1 = "Szkoda... Chciałem porozmawiać. Jestem tu nowy i dopiero poznaję ludzi...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ach, "+GetFullName(pchar)+" ! Czego chcesz?";
				link.l1 = LinkRandPhrase("Masz coś ciekawego do powiedzenia?","Czy coś nowego wydarzyło się na wyspie?","Czy opowiesz mi ostatnie plotki?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Chcę zadać ci kilka pytań o wyspę.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Chciałem tylko wiedzieć, jak się masz. Do zobaczenia!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Nowicjusz? Hm. Dobrze więc. Jestem Victor Cassel i lepiej, żebyś mnie nie denerwował, kiedy mam zły humor. I kiedy mam dobry humor też. Nie tracę czasu na pogawędki, od razu walę ludzi, jeśli są zbyt natarczywi.";
			link.l1 = "Cóż, a ja jestem "+GetFullName(pchar)+"  A tak przy okazji, mogę łatwo oddać. Ale mam nadzieję, że nie będzie ku temu powodu. Nie będę ci przeszkadzać, jeśli jesteś taki małomówny. Żegnaj.";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Masz coś ciekawego do powiedzenia?","Czy coś nowego wydarzyło się na wyspie?","Czy opowiesz mi ostatnie plotki?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Chcę zadać ci kilka pytań o wyspę.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Tak? I co mogę ci powiedzieć?";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Jak tu się dostałeś?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Jak wygląda życie tutaj?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Kto jest tu... najważniejszą osobą?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "A gdzie mogę zdobyć monety na Wyspie Sprawiedliwości?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Bez pytań. Przepraszam...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Przykro mi, przyjacielu, ale co cię trapi? Dopiero co tu dotarłem. Nie chcę rozmawiać o tej historii, zwłaszcza z człowiekiem, którego nie znam.";
			link.l1 = "Cóż, przykro mi...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Wydaje się to nudne. Męczące, monotonne i bezsensowne. Zamierzam dołączyć do piratów Rekina, ci chłopcy są tego warci. Z wielką przyjemnością dołączę do załogi, muszę tylko... trochę się rozejrzeć. Jestem pewien, że znajdą sposób, by wydostać się z Wyspy.";
			link.l1 = "Naprawdę? Rozumiem...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Admirał na pewno! Piraci trzymają Narwale i Rivados w swoim pięści, a klany nie odważają się nic powiedzieć. Następni w kolejce są przywódcy klanów, Donald Greenspy z Narwali i Czarny Eddy z Rivados. Axel Yost - kupiec z Narwali to również ważna osoba. I oczywiście Sancho Carpentero, to dobry chłopak...";
			link.l1 = "Widzę...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Skrzynie. Oczywiście, najpierw musisz je otworzyć, ludzie tutaj sobie nie ufają, więc wszystkie skrzynie mają zamki. Powiem ci jedno, przyjacielu, najlepsze błyskotki trzymane są wewnątrz statków pod czujnym okiem ich właścicieli\nMożesz też eksplorować zewnętrzny pierścień, ale módl się, by nie spaść przez zgniłe drewno. Albo możesz polować na olbrzymie kraby, za mięso z ich szczypiec możesz dostać dobrą cenę.";
			link.l1 = "Zrozumiałem...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Co ty tam robisz, co? Złodzieju!","Popatrz tylko na to! Ledwie pogrążyłem się w zadumie, a ty postanowiłeś sprawdzić moją skrzynię!","Postanowiłeś przeszukać moje skrzynie? Nie ujdzie ci to na sucho!");
			link.l1 = "Cholera!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Co?! Zdecydowałeś się sprawdzić moje skrzynie? Nie ujdzie ci to na sucho!";
			link.l1 = "Zgubiona dziewczyno!";
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
			dialog.text = LinkRandPhrase("Słuchaj, lepiej schowaj broń. To mnie denerwuje.","Wiesz, bieganie z ostrzem nie jest tu tolerowane. Schowaj je.","Słuchaj, nie udawaj średniowiecznego rycerza biegającego z mieczem wkoło. Schowaj to, nie pasuje do ciebie...");
			link.l1 = LinkRandPhrase("Dobrze.","Dobrze.","Jak mówisz...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Słuchaj, jestem obywatelem miasta i proszę cię, abyś schował swoją broń.","Słuchaj, jestem obywatelem miasta i poprosiłbym cię o schowanie ostrza.");
				link.l1 = LinkRandPhrase("Dobrze.","Dobrze.","Jak mówisz...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Ostrożnie, kumplu, gdy biegasz z bronią. Mogę się zdenerwować...","Nie lubię, gdy mężczyźni przechodzą przede mną z gotową bronią. To mnie przeraża...");
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

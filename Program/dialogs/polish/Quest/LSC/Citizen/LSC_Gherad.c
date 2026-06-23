// Гхерад Смиитс - матрос
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
				dialog.text = "Nie chcę z tobą rozmawiać. Atakujesz spokojnych cywilów bez powodu i prowokujesz ich do walki. Zgiń przepadnij!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Dzień dobry, kamracie, ha-ha! Co tu robisz?";
				link.l1 = TimeGreeting()+" Czy ja cię znam?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ach, "+GetFullName(pchar)+"! "+TimeGreeting()+"Chcesz czegoś?";
				link.l1 = LinkRandPhrase("Masz coś ciekawego do powiedzenia?","Czy wydarzyło się coś nowego na wyspie?","Czy opowiesz mi ostatnie plotki?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Chciałbym zadać ci kilka pytań o wyspę.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Tylko chciałem wiedzieć, jak się miewasz. Do zobaczenia!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Oczywiście, że nie, ale łatwo to naprawić, prawda? Jestem Gerard Smeets, marynarz, żeglarz z Rotterdamu. A ty wyglądasz jak kwatermistrz, co najmniej...";
			link.l1 = "Coś w tym rodzaju. Nazywam się "+GetFullName(pchar)+"Miło cię poznać.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Wyglądasz bardziej na właściciela statku lub kasjera... Bez wątpienia jesteś dobrze wykształconym człowiekiem. Miło cię poznać. Jak się tu dostałeś?";
			link.l1 = "Postanowiłem zbadać nieznany obszar. Bukanierzy z Kuby powiedzieli mi, że jest tu coś interesującego, więc postanowiłem to sprawdzić...";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Jesteś jedynym ocalałym? Gdzie zatonął twój statek? Blisko pierścienia?";
			link.l1 = "Jestem jedyny. A moja tartana leży na dnie morza, nawet nie dotarła do pierścienia.";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Rozumiem. Cóż, utknąłeś tu na jakiś czas. Odwiedź Sancho, by zdobyć trochę rumu, to dobry uczynek...";
			link.l1 = "Zrobię to. Do zobaczenia!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Masz coś ciekawego do powiedzenia?","Czy wydarzyło się coś nowego na wyspie?","Czy opowiesz mi najnowsze plotki?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Chcę zadać ci kilka pytań o wyspę.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Jasne, przyjacielu. Słucham.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Powiedz mi, jak się tutaj znalazłeś?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Chcesz opuścić Wyspę i wrócić do swojego normalnego życia?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Nie przeszkadzają ci te klany?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Jak powstała Wyspa, masz jakieś pomysły na ten temat?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Bez pytań. Wybacz...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Przybyłem tu z tym nadętym kogutem zwanym Abbot. Służyłem na jego statku. Wiesz co? Ludzie tacy jak on nigdy nie powinni stawiać stopy na pokładzie, bo przynoszą pecha. Diabeł musiał sprawić, że popłynął z nami.\nMieliśmy tylko przepłynąć z Jamajki do Belize, łatwizna. Ale zły los nas ścigał: nasz bosman wypadł za burtę, nawigator popełnił błąd, przeklęci Hiszpanie i burza na koniec. I oto jesteśmy tutaj.";
			link.l1 = "Interesujące...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Chciałbym wiedzieć, kumplu. Kiedyś wiedziałem, ale teraz nie. Życie tutaj jest w porządku, mnóstwo rumu i wina, dobre jedzenie, nie za dużo, ale i tak lepsze niż to gówno, które jadłem na statkach\nDobrzy ludzie też mieszkają na Wyspie. Są ludzie, z którymi można się napić lub pogadać. Lubię tu być. Więc nie jestem nawet pewien... Nie, chyba nie, nie chcę wyjeżdżać. Kiedyś byłem zły i głodny, spójrz na mój brzuch teraz, ha-ha!";
			link.l1 = "Świetnie! Cieszę się z tobą.";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Nie, nie lubią. Po prostu nie kłóć się z nimi i nie odwiedzaj ich terytoriów bez pozwolenia. Naprawdę tego nie znoszą. Narwale to dobrzy chłopcy, większość z nich urodziła się tutaj i nie widzieli innego życia. Wielu z nich ma wielkie umiejętności, na przykład Jurgen Schmidt. On jest bogiem kowalstwa!";
			link.l1 = "Widzę...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Łatwe jak ciasto. Mielizna i rafy. Zewnętrzny pierścień składa się ze statków od góry do dołu. Statki wpadają w burzę, uderzają w rafy lub sam zewnętrzny pierścień. W ten sposób Wyspa rośnie. Choć nie mam pojęcia, dlaczego wewnętrzne statki pozostają nad wodą.";
			link.l1 = "Widzę...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Co tam robisz, co? Złodzieju!","Spójrz tylko na to! Ledwie się zamyśliłem, a ty już postanowiłeś zajrzeć do mojej skrzyni!","Postanowiłeś sprawdzić moje skrzynie? Nie ujdzie ci to na sucho!");
			link.l1 = "Cholera jasna!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Co?! Zdecydowałeś się sprawdzić moje skrzynie? Nie ujdzie ci to na sucho!";
			link.l1 = "Głupia dziewucha!";
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
			dialog.text = LinkRandPhrase("Słuchaj, lepiej schowaj swą broń. To mnie denerwuje.","Wiesz, bieganie z ostrzem nie jest tu tolerowane. Zabierz to.","Słuchaj, nie udawaj średniowiecznego rycerza biegającego z mieczem na oślep. Odłóż go, to do ciebie nie pasuje...");
			link.l1 = LinkRandPhrase("Dobrze.","Jak sobie życzysz...","Jak powiadasz...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Słuchaj, jestem obywatelem miasta i proszę cię o schowanie broni.","Słuchaj, jestem obywatelem miasta i proszę cię, byś schował swój miecz.");
				link.l1 = LinkRandPhrase("Dobrze.","Cokolwiek zatem.","Jak powiadasz...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Uważaj, kumplu, gdy biegniesz z bronią. Mogę się zdenerwować...","Nie lubię, gdy mężczyźni chodzą przede mną z bronią gotową do użycia. To mnie przeraża...");
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

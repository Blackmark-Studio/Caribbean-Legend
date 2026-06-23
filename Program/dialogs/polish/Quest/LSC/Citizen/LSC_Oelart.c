// Оеларт Котеел - канонир
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
				dialog.text = "Nie chcę z tobą rozmawiać. Atakujesz spokojnych cywilów bez powodu i prowokujesz ich do walki. Znikaj!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Dzień dobry, panie! Podoba ci się pogoda?";
				link.l1 = TimeGreeting()+". Czuję się dobrze przy każdej pogodzie, z wyjątkiem burz na otwartym morzu...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ach, "+GetFullName(pchar)+"! "+TimeGreeting()+"Chcesz czegoś?";
				link.l1 = LinkRandPhrase("Masz coś ciekawego do powiedzenia?","Czy coś nowego wydarzyło się na wyspie?","Czy opowiesz mi ostatnie plotki?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Chcę zadać ci kilka pytań o wyspę.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Chciałem tylko wiedzieć, jak się miewasz. Do zobaczenia!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Zaufaj mi, czuję to samo. Nigdy cię wcześniej nie widziałem... nazywam się Oelart Koteel i byłem mistrzem artylerii na holenderskim okręcie wojennym.";
			link.l1 = ""+GetFullName(pchar)+"Tak, jestem tu nowicjuszem. Właściwie, właśnie przybyłem.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Jestem tu nowicjuszem, jestem tu mniej niż rok. I naprawdę mam nadzieję, że nie zostanę tu zbyt długo, chociaż wszyscy próbują mnie przekonać do przeciwnych myśli. Miło cię poznać!";
			link.l1 = "Miło mi cię również poznać, "+npchar.name+"... ";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Masz coś ciekawego do powiedzenia?","Czy coś nowego wydarzyło się na wyspie?","Czy opowiesz mi ostatnie plotki?");
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
				link.l2 = "Chcesz opuścić Wyspę?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Czy kiedykolwiek zastanawiałeś się, jak powstała Wyspa?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Czy kiedykolwiek odwiedziłeś statki klanu?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Bez pytań. Wybacz...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Dość banalne. Walczyliśmy z angielskim szkunerem i prawie wygraliśmy bitwę. Uciekli, więc ich ścigaliśmy. Minął dzień, byliśmy blisko, by ich złapać, ale odstrzelili nasz główny maszt i, oczywiście, udało im się uciec\nJeśli chodzi o nas, prawie zatopił nas silny sztorm, potem prąd nas porwał, a na końcu nasz statek został wyrzucony na rafę blisko zewnętrznego pierścienia. Tylko nielicznym udało się przeżyć...";
			link.l1 = "Widzę...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "To jest moje marzenie. Nie możesz sobie wyobrazić, jak znudziłem się tym miejscem. Ale jak mogę je opuścić? Nie mam pojęcia. Nie ma tu statków i nie ma możliwości zbudowania nowego. Byłoby to samobójstwo, płynąć małą łodzią.";
			link.l1 = "Rozumiem...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Według statków, ma około stu lat. Ale istnieje możliwość, że może być starsza, ze względu na zewnętrzny pierścień. Jest zbudowana ze statków od góry do dołu, być może starsze jednostki są głęboko pod wodą\nCo do formacji Wyspy... Wierzę, że prądy i burze przynosiły tu umierające statki, więc powstała sztuczna mielizna. Zewnętrzny pierścień został na niej zbudowany\nWewnętrzne statki, na których mieszkamy... albo były pierwsze, albo jakoś udało im się przejść przez zewnętrzny pierścień. To całkiem możliwe, admirał i jego piraci w końcu dotarli do nas na swoim brygu.";
			link.l1 = "Interesujące...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Odwiedziłem Rivados. Czarny Eddy kiedyś potrzebował konsultacji w sprawie dział okrętowych i nie mam pojęcia dlaczego. Więc jeden z czarnych facetów mnie znalazł i dał mi hasło. Odwiedziłem ich 'Protektora' i 'Velasco'. Strażnicy są twardzi, więc nawet nie próbuj ich omijać bez hasła.";
			link.l1 = "Widzę...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Co tam robisz, co? Złodziej!","Popatrz tylko! Ledwie pogrążyłem się w rozmyślaniach, a ty postanowiłeś sprawdzić moją skrzynię!","Zdecydowałeś się sprawdzić moje skrzynie? Nie ujdzie ci to na sucho!");
			link.l1 = "Cholera!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Co?! Zdecydowałeś się sprawdzić moje skrzynie? Nie ujdzie ci to na sucho!";
			link.l1 = "Niemądra dziewczyna!";
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
			dialog.text = LinkRandPhrase("Słuchaj, lepiej schowaj broń. To mnie denerwuje.","Wiesz, bieganie z ostrzem nie jest tu tolerowane. Odłóż to.","Słuchaj, nie udawaj średniowiecznego rycerza biegającego z mieczem. Opuść go, to ci nie pasuje...");
			link.l1 = LinkRandPhrase("Dobrze.","Dobrze.","Jak mówisz...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Słuchaj, jestem obywatelem tego miasta i prosiłbym cię o schowanie swojej szabli.","Słuchaj, jestem obywatelem miasta i proszę cię, byś schował swój miecz.");
				link.l1 = LinkRandPhrase("Dobrze.","Dobrze.","Jak mówisz...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Uważaj, kumplu, biegając z bronią. Mogę się zdenerwować...","Nie lubię, gdy mężczyźni chodzą przede mną z bronią gotową do strzału. To mnie przeraża...");
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

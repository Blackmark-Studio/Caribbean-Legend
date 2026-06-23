// Джаспер Пратт - каторжник
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
				dialog.text = "Dzień dobry, panie. Czegoś pan potrzebuje?";
				link.l1 = TimeGreeting()+". Nazywam się "+GetFullName(pchar)+", a jak się zwiesz? Jestem tu nowy...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ach, "+GetFullName(pchar)+"! "+TimeGreeting()+" !  Chcesz czegoś?";
				link.l1 = LinkRandPhrase("Masz coś ciekawego do powiedzenia?","Czy wydarzyło się coś nowego na wyspie?","Opowiesz mi ostatnie plotki?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Chciałbym zadać ci kilka pytań o wyspę.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Chciałem tylko wiedzieć, jak się masz. Do zobaczenia!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Ja? Jestem Jasper, były skazaniec państwowy. Dlatego ludzie patrzą na mnie spode łba. A, do diabła z nimi, przywykłem do tego...";
			link.l1 = "Nie obchodzi mnie, kim byłeś, liczy się to, kim jesteś teraz.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "To zła rzecz, że nie wszyscy myślą tak jak ty, panie.";
			link.l1 = "Cóż, jestem znany z liberalnego podejścia...";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Cieszę się za ciebie. Nie martw się, mimo mojej przeszłości, nie stanowię zagrożenia dla sakiewek i skrzyń mieszkańców Wyspy. Cieszę się, że w końcu mogę żyć w spokoju.";
			link.l1 = "Miło cię poznać, Jasper. Do zobaczenia!"link.l1.go ="wyjście";
			link.l2 = LinkRandPhrase("Masz coś ciekawego do powiedzenia?","Czy na wyspie wydarzyło się coś nowego?","Opowiesz mi najnowsze plotki?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Chcę zadać ci kilka pytań o wyspę.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Tak, oczywiście. Odpowiem ci, jeśli będę mógł. Pytaj.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Jak zostałeś mieszkańcem Wyspy?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Czy lubisz to miejsce?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Czy wspomniałeś, że ludzie patrzą na ciebie krzywo? Czy to z powodu twojej przeszłości?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Ta Wyspa jest całkiem interesująca, nie sądzisz?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Bez pytań. Przepraszam...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Uciekłem z plantacji na Kubie. Było nas pięciu i zdecydowaliśmy, że lepiej umrzeć, niż nadal łamać sobie plecy za baty. Udało nam się oszukać strażników i zniknąć w dżungli, potem dotarliśmy do brzegu i zbudowaliśmy tratwę.\nChcieliśmy dotrzeć na Tortugę, ale los zdecydował inaczej. Nikt z nas nie wiedział, jak nawigować, więc się zgubiliśmy. Potem skończyła się woda... Nie chcę tego wspominać. W rezultacie byłem jedynym, który dotarł na Wyspę i przeżył.";
			link.l1 = "Widzę...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Wiesz, nie mam nic przeciwko temu. Po tym, co przeszedłem na plantacji, to miejsce wydaje się niebem dla mnie. Nie potrzebuję wiele... Trochę jedzenia, wody i szklankę rumu każdego wieczoru. Nikt mi tu nie przeszkadza i nie zamierzam opuszczać tego miejsca. Umrę tutaj, gdy nadejdzie mój czas.";
			link.l1 = "Widzę...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Sprawa jest taka, że Wyspa jest placem zabaw dla jakiegoś tajemniczego złodzieja. Zamki nie stanowią dla niego problemu. Głównie kręci się wokół komnat admirała. Choć nasze skrzynie też nie są nietknięte. Nikt nie wie, kim jest ten złodziej, więc podejrzewają ludzi z... hm, kryminalną przeszłością\nZłodziej jest jednak trochę dziwny: po pierwsze, zabiera tylko butelki z alkoholem i jakieś drobiazgi, nigdy nie zabiera cennych przedmiotów. Śmieszne, prawda?";
			link.l1 = "Zrozumiałem...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Tak, zgadzam się. Dużo pływałem wokół wewnętrznych statków Wyspy. Jest bardzo mało wyjść z wody. San Augustin, miejsce mostu. Gloria, upadły maszt. Jeśli popłyniesz blisko platformy Fenix, a potem wokół Ceres Smitie, dotrzesz do kabiny Mary Casper na dziobie statku\nSzczelina w Tartarusie doprowadzi cię do więzienia. Jest dziura w dziobie San Augustine, można wejść do pomieszczenia magazynowego admirała, ale to niezbyt zalecany kierunek działania. Najniższe drzwi Tartarus są często zamknięte, pamiętaj o tym\n I oczywiście możesz wejść do Fernandy, to samotna i rozdarta fletnia. Mówią, że nikt tam nie mieszka, ale często zauważam światła w kabinie i czasami słyszę dziwne pijackie piosenki i płacze.";
			link.l1 = "Interesujące... Muszę bardziej zbadać to miejsce.";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Co tam robisz, co? Złodzieju!","Spójrz tylko na to! Ledwo się zagłębiłem w rozmyślania, a ty postanowiłeś sprawdzić moją skrzynię!","Zdecydowałeś się sprawdzić moje skrzynie? Nie ujdziesz z tym na sucho!");
			link.l1 = "Cholera!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Co?! Postanowiłeś sprawdzić moje skrzynie? Nie ujdzie ci to na sucho!";
			link.l1 = "Głupia dziewczyno!";
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
			dialog.text = LinkRandPhrase("Słuchaj, lepiej schowaj swoją broń. To mnie denerwuje.","Wiesz, bieganie z ostrzem nie jest tu tolerowane. Schowaj to.","Słuchaj, nie udawaj średniowiecznego rycerza biegającego z mieczem. Odłóż to, nie pasuje do ciebie...");
			link.l1 = LinkRandPhrase("Dobrze.","Cokolwiek zatem.","Jak powiadasz...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Słuchaj, jestem obywatelem miasta i proszę cię, żebyś schował swój miecz.","Słuchaj, jestem obywatelem miasta i proszę cię, byś trzymał miecz na wodzy.");
				link.l1 = LinkRandPhrase("Dobrze.","Niech będzie.","Jak mówisz...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Uważaj, kumplu, biegając z bronią. Mogę się zdenerwować...","Nie lubię, gdy mężczyźni chodzą przede mną z bronią gotową do użycia. To mnie przeraża...");
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

// Дугал Эббот - дворянин
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
				dialog.text = "Nie chcę z tobą rozmawiać. Atakujesz pokojowych cywilów bez powodu i prowokujesz ich do walki. Zmykaj!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Witaj, panie. Pozwól, że się przedstawię - Dougall Abbot. Miło widzieć tu szlachcica. Jestem zmęczony miejscowymi wieśniakami. Nigdy bym nie pomyślał, że będę musiał spędzić resztę życia wśród pospólstwa.";
				link.l1 = TimeGreeting()+" . Nazywam się "+GetFullName(pchar)+"Miło cię poznać. A czemu nie lubisz miejscowych?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ach, "+GetFullName(pchar)+"! "+TimeGreeting()+"Chcesz coś?";
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
			dialog.text = "Nie znasz ich dobrze. Czy dopiero tu przybyłeś? Nie pamiętam jednak żadnego niedawnego wraku statku...";
			link.l1 = "Przybyłem tutaj na małej barki...";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Tak, to się zdarza często - statki toną, a tylko kilku rozbitków dociera tutaj na łodziach ze swoich statków. Czasami ludzie żyją tu miesiącami i nigdy ich nie spotkasz.";
			link.l1 = "Rozumiem. Miło było cię poznać, panie Abbot. Do zobaczenia!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Masz coś ciekawego do powiedzenia?","Czy coś nowego wydarzyło się na wyspie?","Czy opowiesz mi najnowsze plotki?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Chcę zadać ci kilka pytań dotyczących wyspy.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Słucham.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Jak się tu dostałeś?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Co możesz mi powiedzieć o tutejszych?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Co możesz mi powiedzieć o klanach?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "A co z pogodą? Czy często zdarzają się tu burze?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Bez pytań. Przepraszam...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "To było pięć lat temu, ale wciąż pamiętam to doskonale, jakby to było wczoraj. Pewnego niefortunnego dnia postanowiłem popłynąć moim fletem z Port Royal do Belize, było zbyt cenne ładunek, by powierzyć innym to zadanie\nNastępnego dnia zaczęły się moje niepowodzenia, najpierw nasz bosman się upił i wypadł za burtę, potem prawie uderzyliśmy w rafy, a na końcu nasz nawigator popełnił błąd, więc popłynęliśmy w złym kierunku\nWtedy ścigała nas fregata i galeon. Próbowaliśmy uciec, ale byli natarczywi. Galeon został w tyle, ale fregata w końcu nas dogoniła\nGaleon był zbyt daleko stąd, więc weszliśmy na pokład fregaty bez strzału. Te hiszpańskie psy się tego nie spodziewały i wygraliśmy, ale większość mojej załogi zginęła\nKilka godzin później dopadła nas burza, nie mogliśmy walczyć z pogodą przy tak małej załodze i teraz widzisz rezultat. Mój flet jest gdzieś na zewnętrznym pierścieniu, ja i trzech innych ocalałych dotarliśmy tutaj.";
			link.l1 = "Zrozumiałem...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Łajdacy. Wszyscy do jednego. Męty wszelkiej maści. Richard Shambon to kryminalista, widać to na jego twarzy. Kassel? Zabijanie dla niego jest tak naturalne jak oddychanie. Jasper Pratt to skazaniec. Musket to pijak. Czy mam kontynuować?\nJosef Loderdale to jedyny przyzwoity człowiek tutaj, poza tobą, to były wojskowy angielskiej marynarki. Są tu dwaj szlachcice - Antonio Betancourt i Lorenzo Solderra, przeklęte hiszpańskie męty, nawet nie usiądę z nim przy tym samym stole.";
			link.l1 = "Widzę...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Banda łajdaków i szumowin. Jednak nie krzywdzą nas. Bardziej interesuje ich dźganie i strzelanie do siebie nawzajem. Nie mogą bez tego żyć. Też nie lubię piratów, ale muszę przyznać, że uczynili Wyspę spokojniejszym miejscem, kiedy tu przybyli.";
			link.l1 = "Interesujące...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "   Nigdy tego nie robią. Burze często zdarzają się wokół Wyspy, ale to miejsce jest zawsze spokojne i ciche, może to jakiś rodzaj magii lub woli Boga, nie wiem. Czasami silny wiatr może dotrzeć do tego miejsca i to wszystko. Deszcze nie mogą wyrządzić żadnej szkody również.  ";
			link.l1 = "Interesujące...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Co tam robisz, co? Złodzieju!","Spójrz tylko na to! Gdy tylko pogrążyłem się w zadumie, postanowiłeś sprawdzić moją skrzynię!","Postanowiłeś sprawdzić moje skrzynie? Nie ujdzie ci to na sucho!");
			link.l1 = "Do diabła!";
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
			dialog.text = LinkRandPhrase("Słuchaj, lepiej schowaj swoją broń. To mnie denerwuje.","Wiesz, bieganie z ostrzem nie jest tu tolerowane. Schowaj je.","Słuchaj, nie udawaj średniowiecznego rycerza, biegającego z mieczem. Odłóż to, to do ciebie nie pasuje...");
			link.l1 = LinkRandPhrase("Dobrze.","Dobrze.","Jak mówisz...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Słuchaj, jestem obywatelem miasta i proszę cię, abyś schował swój miecz.","Słuchaj, jestem obywatelem miasta i prosiłbym cię, abyś schował swój miecz.");
				link.l1 = LinkRandPhrase("W porządku.","Jak tam sobie chcesz.","Jak mówisz...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Uważaj, kumplu, z bieganiem z bronią. Mogę się zdenerwować...","Nie lubię, gdy mężczyźni przechodzą przede mną z bronią gotową do użycia. To mnie przeraża...");
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

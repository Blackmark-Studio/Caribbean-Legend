// Альваро Гомец - капитан
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
				dialog.text = "O, nowa twarz! Witaj. A kiedy tu przybyłeś? Nie pamiętam żadnego niedawnego wraku statku.";
				link.l1 = TimeGreeting()+". Nazywam się "+GetFullName(pchar)+" I mój statek zatonął tak cicho i szybko, że nikt tego nie zauważył. I na Wyspę dotarłem równie szybko i cicho. Tak po prostu...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ach, "+GetFullName(pchar)+"! "+TimeGreeting()+"Chcesz czegoś?";
				link.l1 = LinkRandPhrase("Masz coś ciekawego do powiedzenia?","Czy wydarzyło się coś nowego na wyspie?","Czy opowiesz mi ostatnie plotki?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Chcę zadać ci kilka pytań o wyspę.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Chciałem tylko wiedzieć, jak się masz. Do zobaczenia!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Widzę, Och, zapomniałem się przedstawić. Wybaczcie mi, señor. Nazywam się Alvaro Gomez i kiedyś byłem kapitanem własnej brygantyny. Eh, teraz moja piękna brygantyna leży na dnie tuż za zewnętrznym pierścieniem... Wiele wody upłynęło od tamtej pory. Ach, nieważne. Miło cię poznać!";
			link.l1 = "Miło cię poznać, señor Gomez.";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Masz coś ciekawego do powiedzenia?","Czy wydarzyło się coś nowego na wyspie?","Opowiesz mi ostatnie plotki?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Chciałbym zadać ci kilka pytań o wyspę.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Słucham, señor.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Powiedziałeś, że byłeś kapitanem. Jak trafiłeś na wyspę?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Co możesz mi powiedzieć o życiu na wyspie?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Powiedz mi, czy tubylcy żyją tu w pokoju, czy nie? Oczywiście nie mówię o klanach.";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "A skąd miejscowi zdobywają zaopatrzenie?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Bez pytań. Przepraszam...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Jak wszyscy inni. Burza mnie dopadła, straciłem maszt i kontrolę nad sterem. Zostaliśmy porwani przez prąd i wyrzuceni na rafy. Mój statek nawet nie dotarł do zewnętrznego pierścienia i został zniszczony. Przeżyło tylko kilku ludzi.";
			link.l1 = "Smutna historia...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Co mogę powiedzieć? Mamy wszystko, czego potrzebujemy do godnego życia. Chociaż czasami robi się tu naprawdę nudno. I ta melancholia... Pierwszy rok był najgorszy, ale później przywykłem. Żal mi mojej biednej żony Sabriny, musi być pewna, że umarłem. Mam nadzieję, że udało jej się ponownie wyjść za mąż\nNie martw się, przyzwyczaisz się. Odwiedź tawernę, sklep, kościół, poznaj innych ludzi. Nie idź do Narwali ani Rivados, dopóki naprawdę nie musisz, to podstępne dranie.";
			link.l1 = "Widzę...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Prawda, kłótnie i bójki są tutaj potajemnie zabronione. Jeśli pobijesz kogoś bez odpowiedniego powodu lub, nie daj Boże, zabijesz, to skończysz na izolacji. Możesz nawet pewnej nocy zostać wyrzucony za burtę. Było tu kilku awanturników na Wyspie. Pierwszy po prostu zniknął, drugi zmarł w celi Tartaru po miesiącach spędzonych wewnątrz. Oczywiście, to nie znaczy, że nie możesz się bronić. Ale miejscowi są w rzeczywistości dość pokojowi. Abbott jest pyszałkowaty, ale nie agresywny. Kassel to prawdziwy drań, ale trzyma ręce czyste. Pratt to były skazaniec, ale jest nieszkodliwy. Mamy tu dwóch byłych oficerów marynarki - Loderdale'a i Solderrę. Przybyli tutaj podczas bitwy niedaleko. Ironią losu, obaj przeżyli, by nadal knuć krwawe plany przeciwko sobie.";
			link.l1 = "Zrozumiano...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Z ładowni, oczywiście. Wszystkie zapasy, zgromadzone z innych statków, były przechowywane w St. Augustin i dzielone pomiędzy wszystkich, dopóki nie pojawili się piraci. Teraz ściskają Wyspę w pięści, ponieważ posiadają zaopatrzenie\nJasne, mamy swoje własne skrytki, więc jest w porządku. Także strzelamy do ptaków i łowimy ryby... Ale najlepsze polowanie kończy się zabiciem gigantycznego kraba. Mają bardzo smaczne i pożywne mięso. Choć można je zobaczyć tylko na zewnętrznym pierścieniu\nNurkowanie, by je łowić, jest zbyt ryzykowne. Był jeden, kto był na tyle odważny, by polować na nie pod wodą. Pewnego dnia sam stał się ofiarą. Od tamtej pory nikt nie chce tam polować na kraby.";
			link.l1 = "Interesujące...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Co tam robisz, co? Złodzieju!","Spójrz tylko na to! Ledwie pogrążyłem się w zadumie, a ty postanowiłeś sprawdzić moją skrzynię!","Zdecydowałeś się sprawdzić moje skrzynie? Nie ujdzie ci to na sucho!");
			link.l1 = "Cholera jasna!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Co?! Postanowiłeś sprawdzić moje skrzynie? Nie ujdzie ci to na sucho!";
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
			dialog.text = LinkRandPhrase("Słuchaj, lepiej schowaj swoją broń. To mnie denerwuje.","Wiesz, bieganie z ostrzem nie jest tu tolerowane. Schowaj je.","Słuchaj, nie udawaj średniowiecznego rycerza biegającego z mieczem. Odłóż go, to do ciebie nie pasuje...");
			link.l1 = LinkRandPhrase("Dobrze.","Pewnie.","Jak powiadasz...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Słuchaj, jestem obywatelem tego miasta i proszę cię, byś trzymał swój miecz na wodzy.","Słuchaj, jestem obywatelem miasta i proszę cię, abyś schował swój miecz.");
				link.l1 = LinkRandPhrase("Dobrze.","Cokolwiek wtedy.","Jak mówisz...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Uważaj, przyjacielu, biegając z bronią. Mogę się zdenerwować...","Nie lubię, gdy ludzie chodzą przede mną z bronią gotową do strzału. To mnie przeraża...");
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

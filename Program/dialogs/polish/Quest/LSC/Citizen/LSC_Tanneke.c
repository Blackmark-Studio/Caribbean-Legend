// Таннеке Эверс - просто девушка
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
				dialog.text = "Nie chcę z tobą rozmawiać. Atakujesz pokojowych cywilów bez powodu i prowokujesz ich do walki. Znikaj!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Dzień dobry! Czy ja cię znam? Nie widziałem cię wcześniej, to pewne...";
				link.l1 = TimeGreeting()+". To prawda, jestem nowym... gościem tutaj. Nazywam się "+GetFullName(pchar)+" i jestem kapitanem.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ach, "+GetFullName(pchar)+"! "+TimeGreeting()+"Chcesz czegoś?";
				link.l1 = LinkRandPhrase("Masz coś ciekawego do powiedzenia?"," Czy coś nowego wydarzyło się na wyspie?","Czy opowiesz mi ostatnie plotki?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Chcę zadać ci kilka pytań o wyspę.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Chciałem tylko wiedzieć, jak się masz. Do zobaczenia!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Byłeś kapitanem?";
			link.l1 = "Dlaczego miałbym być? Wciąż jestem kapitanem... a-ah, już rozumiem! Myślisz, że mój statek zatonął lub został zniszczony przez rafy. Nie. Ona jest blisko brzegów Zachodniego Głównego. Dotarłem tutaj na barku, choć skończyło się to źle, bark dostał dziurę w kadłubie i zatonął.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Przybyłeś tu na barku? A jak udało ci się przetrwać burzę?";
			link.l1 = "Jaka burza? Nie pamiętam żadnej burzy...";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Jak to możliwe? Zawsze wokół Wyspy jest burza. Wszyscy tak mówią.";
			link.l1 = "„Cóż, tak nie jest albo miałem szczęście to ominąć. Morze było absolutnie spokojne... przepraszam, czy mogę poznać imię takiej pięknej damy?”";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Och! Przepraszam, zapomniałam się przedstawić... Nazywam się Tanneke. Miło cię poznać.";
			link.l1 = "Miło cię poznać również, Tanneke... To dla mnie przyjemność.";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "A dlaczego zdecydowałeś się dotrzeć na naszą Wyspę na barku? A-ah, rozumiem - prąd cię tu przygnał. Nikt nie wie o Wyspie i ludzie zawsze trafiają tu przez przypadek.";
			link.l1 = "To nie jest prawda. Krążą całkiem prawdziwe plotki o Wyspie, w tym jej położenie. Dlatego postanowiłem zobaczyć to na własne oczy...";
			link.l1.go = "meeting_5";
		break;
		
		case "meeting_5":
			dialog.text = "Teraz rozumiem. Jesteś jak Adolf Barbier, czytałeś za dużo kapitana Alvarado i postanowiłeś szukać złota admirała de Betancourt. Niestety, kapitanie, jeśli taki przebiegły łotr jak Barbier nie zdołał go znaleźć, to wątpię, że tobie się uda.\nI naprawdę myślę, że nie ma żadnego złota admirała, Antonio musiał to wymyślić, żeby pokazać nam, jak ważnym człowiekiem był jego dziadek... Cóż, zostaniesz z nami. Dotarcie tutaj było łatwe, ale opuszczenie musi być niemożliwe. Mam na myśli opuszczenie w jednym kawałku.";
			link.l1 = "To nic. Myślę, że będę w stanie sobie z tym poradzić, nie mam na myśli złota Betancourta, o którym wspomniałeś - to pierwszy raz, gdy o nim słyszę, mam na myśli opuszczenie Wyspy. Żywym. Było mi miło z tobą porozmawiać, Tanneke. Do zobaczenia!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Pytaj, kapitanie...";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Jak tu dotarłeś?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Próbowałeś kiedyś opuścić Wyspę?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Jak tu żyjecie?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Czy dziewczęta muszą kupować jedzenie od admirała, czy dostają je za darmo?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Żadnych pytań. Wybacz...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Jestem Holenderką, ale mieszkaliśmy w Santiago. Moi rodzice wysłali mnie do pracy jako służąca dla rodziny bankiera Geraldi. Słyszałeś o nich? Trzy lata temu jeden z nich wypłynął do Nowej Hiszpanii na kurierze lugrowym. Powiedziano mi, bym mu towarzyszyła. Drugiego dnia naszej podróży zostaliśmy złapani przez brygantynę pod hiszpańską banderą\nIch oficer wszedł na pokład naszego statku i rozmawiał z naszym kapitanem, kapitan wpadł w szał i odprawił oficera. Zostaliśmy zaatakowani, gdy tylko gość dotarł na swój statek. Próbowaliśmy uciec, ale udało im się nas abordażować. O ile zrozumiałam, potrzebowali mojego pana Geraldi, bo wpadli do kajuty, schwytali go i zabrali. Mnie i marynarzy zabrano do ładowni i tam zostawiono.\n Myślałam, że nas zatopią, ale po prostu odpłynęli. Marynarzom udało się opuścić ładownię, ale nasz kapitan zginął w walce i nikt z ocalałych nie wiedział, jak nawigować właściwy kurs. Płynęliśmy gdzieś przez jakiś czas, aż silny sztorm nas porwał\n Kilka godzin później nasz lugier został wyrzucony na zewnętrzny pierścień. Nadal tam jest. Miałam na tyle szczęścia, że przeżyłam burzę, a po świcie ja i kilku innych 'szczęśliwców' dotarliśmy na Wyspę.";
			link.l1 = "Widzę...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Nie. I jak sobie to wyobrażasz? Nie ma tu żadnych statków gotowych do wypłynięcia, a użycie łodzi to jak podpisanie sobie wyroku śmierci. Jak mówiłem, burze są tutaj częste. Pamiętam tylko jedną próbę opuszczenia tego miejsca - pięciu mieszkańców zbudowało porządną łódź z żaglami i wiosłami\nWalczyli z prądem przez kilka godzin, a potem w końcu dotarli na otwarte morze. Kilka dni później jeden z nich wrócił na zewnętrzny pierścień... przywiązany do wraku masztu i martwy. To zabiło w innych chęć do takich śmiałych czynów.";
			link.l1 = "Rozumiem...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Nie martw się. Nie jest gorzej niż być sługą tej zarozumiałej rodziny lichwiarzy. Musisz tylko przyzwyczaić się do tego miejsca, a potem może nawet je pokochasz. A propos, nie jestem jedynym, który tak myśli. A klany... nie przeszkadzają mi.";
			link.l1 = "Interesujące...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Oczywiście, że kupujemy. Ach, kapitanie, jest tu wystarczająco pracy dla dziewczyny: sprzątanie, gotowanie, pomaganie innym... nie siedzimy bezczynnie, ale nikt tu się nie przemęcza. Piraci sprzedają jedzenie tanio dla zwykłych obywateli, w przeciwieństwie do klanów. Więc nie głodujemy\nPomagam Gillian i Natalie, a one pomagają mi, jeśli potrzebuję. Jesteśmy przyjaciółkami. Jest jeszcze jedna dziewczyna na Wyspie, Hiszpanka. Nazywa się Ramona, ale zazwyczaj trzyma się na uboczu i nie jesteśmy zbyt chętni, by się z nią zaprzyjaźnić.";
			link.l1 = "A dlaczego tak jest?";
			link.l1.go = "ansewer_4_1";
		break;
		
		case "ansewer_4_1":
			dialog.text = "Cóż... powiedzmy, że mamy różne spojrzenia na życie. Porozmawiaj z nią, a zrozumiesz.";
			link.l1 = "Interesujące...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Co tam robisz, co? Złodzieju!","Spójrz tylko na to! Ledwie pogrążyłem się w zadumie, a ty postanowiłeś sprawdzić moją skrzynię!","Postanowiłeś sprawdzić moje skrzynie? Nie ujdzie ci to na sucho!");
			link.l1 = "Cholera!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Co?! Zdecydowałeś się sprawdzić moje skrzynie? Nie ujdzie ci to na sucho!";
			link.l1 = "Nierozsądna dziewczyno!";
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
			dialog.text = LinkRandPhrase("Słuchaj, lepiej schowaj swoją broń. Denerwuje mnie to.","Wiesz, bieganie z ostrzem tutaj nie jest tolerowane. Schowaj je.","Słuchaj, nie udawaj średniowiecznego rycerza biegającego z mieczem w ręku. Odłóż go, to nie dla ciebie...");
			link.l1 = LinkRandPhrase("Dobrze.","Jak sobie życzysz...","Jak powiadasz...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Słuchaj, jestem obywatelem miasta i proszę cię, byś schował swój miecz.","Słuchaj, jestem obywatelem miasta i proszę cię o schowanie broni.");
				link.l1 = LinkRandPhrase("Dobrze.","Jak sobie życzysz...","Jak powiadasz...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Bądź ostrożny, kumplu, gdy biegniesz z bronią. Mogę się zdenerwować...","Nie lubię, gdy mężczyźni przechodzą przede mną z gotową bronią. To mnie przeraża...");
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

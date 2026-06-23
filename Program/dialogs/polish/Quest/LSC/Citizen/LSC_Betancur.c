// Антонио Бетанкур - потомок Франциско Бетанкура
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
				dialog.text = "Witaj, witaj... Czego chcesz, przyjacielu?";
				link.l1 = TimeGreeting()+". Nazywam się "+GetFullName(pchar)+"  A ja tylko chciałem wiedzieć, kim jesteś. Widzisz, jestem nowo przybyłym, spaceruję po mieście i rozmawiam z ludźmi.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ach, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Czego chcesz tym razem?";
				if(CheckAttribute(pchar, "questTemp.LSC.Betancur"))
				{
					link.l4 = "Antonio, mówią, że dobrze znasz historię Wyspy. Mam do ciebie pytanie na ten temat.";
					link.l4.go = "dolly";
				}
				dialog.text = "Ach, "+GetFullName(pchar)+"! "+TimeGreeting()+"Chcesz czegoś?";
				link.l1 = LinkRandPhrase("Masz coś ciekawego do powiedzenia?","Czy coś nowego wydarzyło się na wyspie?","Czy opowiesz mi ostatnie plotki?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Chciałbym zadać ci kilka pytań o wyspę.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Chciałem tylko wiedzieć, jak się masz. Do zobaczenia!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Wspaniale. I dobrze ci pójdzie, bo wszyscy tutaj jesteśmy jedną wielką rodziną. Oprócz Narwali i plugawych Rivados oczywiście. Nazywam się Antonio, Antonio Betancourt. Jestem wnukiem Francisco Betancourt, jeśli to nazwisko coś ci mówi.";
			link.l1 = "Francisco Betancourt? Słyszałem to imię wcześniej... Ach, tak! Dios mi o nim wspominał i czytałem o nim w notatkach Alvarado...";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Nie mam pojęcia, kim jest wasz Dios, ale kapitan Alvarado odwiedził nas dawno temu. Widziałem go osobiście, kiedy byłem dzieckiem. Odpłynął z wyspy i napisał o tym w swoich rękopisach. A Francisco Betancourt był hiszpańskim admirałem, dowódcą eskadry wojskowej. Rozpoczął historię tego miejsca z powodu faktu, że wszyscy Rivados są potomkami czarnych niewolników z Tartaru, flagowego statku eskadry. Narwale to dzieci pierwszych białych osadników, członków załogi Tartaru, San Augustine i San Geronimo.";
			link.l1 = "Niesamowite! Czy urodziłeś się tutaj?";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Dokładnie. Jestem prostym potomkiem człowieka, który właściwie zajął Wyspę.";
			link.l1 = "Rozumiem. Miło cię poznać, Antonio. Do zobaczenia.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		// квестовая часть
		case "dolly":
			dialog.text = "Hm... Pewnie, przyjacielu, pytaj mnie. Odpowiem na twoje pytania, oczywiście, ale tylko jeśli znam odpowiedzi.";
			link.l1 = "Powiedz mi, czy pamiętasz czas, gdy galeon San Geronimo wciąż tu był?";
			link.l1.go = "dolly_1";
		break;
		
		case "dolly_1":
			dialog.text = "Oczywiście, że pamiętam. To był bardzo wyjątkowy statek. Był tam ciekawy indiański posąg, a te plugawce Rivados odprawiali ofiary rytualne.";
			link.l1 = " A jak oni to robili? Odbierali ludziom serca jak Majowie? A może ścinali głowy?";
			link.l1.go = "dolly_2";
		break;
		
		case "dolly_2":
			dialog.text = "Nie... To była bardzo szczególna statua - wciągała ofiary do siebie i znikały na zawsze. Narzędzie diabła... Dzięki Bogu, że zatonęła z okrętem i nigdy nie wyrządzi więcej szkody. Ciekawe, że ofiary zawsze składano o tej samej porze rano. Statua zamieniała się w złoto pod światłem wschodzącego słońca\nTo wtedy dzikusy przynosiły ofiary, głównie Narwale, które pojmali.";
			link.l1 = "Interesujące! A czy ktoś próbował kiedyś zbadać, jak działa ten posąg?";
			link.l1.go = "dolly_3";
		break;
		
		case "dolly_3":
			dialog.text = "Oczywiście, że nie! Po pierwsze, Rivados nie pozwalają nikomu poza swoimi zbliżać się do San Geronimo, a po drugie, uczciwy katolik musi trzymać się z dala od diabelskich poczynań.";
			link.l1 = "Rozumiem. Widzę, że nie lubisz Rivados. Mam rację?";
			link.l1.go = "dolly_4";
		break;
		
		case "dolly_4":
			dialog.text = "Czyżbym? Nienawidzę tych brudnych pogan! Na wypadek, gdybyś nie wiedział, mój dziadek był kapitanem statku, na którym Murzyni razem ze swoim przywódcą, Rivados, zbuntowali się. Zostawić ich tak zwanego przywódcę, by gnił w ładowni, było właściwym postępkiem. Miałem także wspaniały klucz ze skarbca św. Anny\nNikt nie wie, gdzie jest ten skarbiec, może leży na dnie morza otoczony krabami, ale klucz był dla mnie miłą pamiątką i jednak został skradziony! Jestem pewien, że to czarni go ukradli. Pewnie próbują znaleźć skarbiec. Wątpię, żeby im się udało, minęło zbyt wiele czasu, ha-ha! Śmiecie...";
			link.l1 = "Rozumiem. Dzięki za twoją interesującą opowieść!";
			link.l1.go = "dolly_5";
		break;
		
		case "dolly_5":
			dialog.text = "Jesteś mile widziany, zawsze chętnie porozmawiam!";
			link.l1 = "Żegnaj!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.LSC.Betancur");
			AddQuestRecord("LSC", "16");
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Słucham, kumplu.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Więc nie widziałeś niczego innego poza Wyspą w swoim życiu?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Urodziłeś się tutaj... Dlaczego nie jesteś członkiem klanu Narwali? Myślałem, że wszyscy rodowici biali ludzie są Narwalami...";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "A co robisz na Wyspie?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Czy kiedykolwiek pragnąłeś opuścić Wyspę na jakiś czas? Zobaczyć świat...";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Bez pytań. Przepraszam...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Wydaje się, że tak, tak. Ale nie myśl, że jestem głupcem czy ograniczonym człowiekiem. Odziedziczyłem wspaniałą bibliotekę po dziadku, a mój ojciec zapewnił mi doskonałe wykształcenie. Znam starożytną historię, geografię, astronomię, znam angielski, francuski, hiszpański, a nawet łacinę\nWielu żeglarzy, którzy byli wszędzie, wie mniej ode mnie. Chociaż nie widziałem niczego poza tymi wrakami statków, mentalnie odwiedziłem Europę, Chiny i Indie...";
			link.l1 = "Widzę...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "To nieprawda, choć masz dziewięćdziesiąt procent racji. Ale nie jestem Narwalem i nie chcę się nim stać. Po co? Żeby stać na straży godzinami jak głupiec albo walczyć z Riva-dosami? Nie ma mowy, oszczędź mi tego. Jestem inny. Wolę żyć niezależnie i czytać książki.";
			link.l1 = "Rozumiem...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Ojciec zostawił mi całkiem przyzwoite dziedzictwo i wydaję je ostrożnie. Więc nie muszę czaić się w starych wrakach statków, by znaleźć jakieś klejnoty do wymiany na jedzenie. Nie wierzę w wielkie skarby wewnątrz starych statków\nJedynym skarbem, który znam, jest skarbiec św. Anny. To duża żelazna skrzynia. Ale nikt jeszcze nie zdołał jej znaleźć\nRównież zamierzam napisać szczegółową historię Wyspy opartą na lokalnych opowieściach. Jak myślisz - powinienem spróbować?";
			link.l1 = "Jestem tego pewien. Znam przynajmniej jednego człowieka na Archipelagu, który zapłaciłby za taką książkę dużo złota. To twoja szansa...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "„Czasem o tym myślę. Może gdyby statek, który potrafiłby poradzić sobie z prądem i przetrwać burze, przypłynął tutaj, zaryzykowałbym. Jestem naprawdę chętny zobaczyć rzeczy, które są tak interesująco opisane w moich książkach! Ale to na razie tylko marzenia...”";
			link.l1 = "Marzenia się spełniają. Wystarczy w nie wierzyć...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Co tam robisz, co? Złodzieju!","Spójrz tylko na to! Ledwie pogrążyłem się w zadumie, a ty postanowiłeś sprawdzić moją skrzynię!","Zdecydowałeś się sprawdzić moje skrzynie? Nie ujdzie ci to na sucho!");
			link.l1 = "Cholera!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Co?! Zdecydowałeś się sprawdzić moje skrzynie? Nie ujdzie ci to na sucho!";
			link.l1 = "Nie rozumna dziewczyno!";
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
			dialog.text = LinkRandPhrase("Słuchaj, lepiej schowaj broń. To mnie denerwuje.","Wiesz, bieganie z ostrzem nie jest tutaj tolerowane. Schowaj je.","Słuchaj, nie udawaj średniowiecznego rycerza biegającego z mieczem wkoło. Schowaj to, to do ciebie nie pasuje...");
			link.l1 = LinkRandPhrase("Dobrze.","Jak sobie życzysz...","Jak powiadasz...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Słuchaj, jestem obywatelem miasta i prosiłbym cię, abyś trzymał swój miecz w pochwie.","Słuchaj, jestem obywatelem miasta i proszę cię, byś schował swój oręż.");
				link.l1 = LinkRandPhrase("Dobrze.","Jak sobie życzysz...","Jak powiadasz...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Bądź ostrożny, kumplu, gdy biegasz z bronią. Mogę się zdenerwować...","Nie lubię, gdy mężczyźni chodzą przede mną z bronią gotową do użycia. To mnie przeraża...");
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

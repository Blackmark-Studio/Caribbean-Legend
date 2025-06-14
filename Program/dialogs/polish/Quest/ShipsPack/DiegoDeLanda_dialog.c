void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag, arTmp;
	int i, n;
	string sTemp, sStr;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Czego chcecie?";
			link.l1 = "Nic.";
			link.l1.go = "exit";
		break;

		//--> Встреча
		case "DiegoDeLanda_Meeting":
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 1)
			{
				dialog.text = "Smutna historia, prawda?";
				link.l1 = "Kim jesteś?";
				link.l1.go = "DiegoDeLanda_Meeting_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 2)
			{
				dialog.text = "Witaj, kapitanie.";
				link.l1 = "Poczekaj! Już się spotkaliśmy!";
				link.l1.go = "DiegoDeLanda_Meeting_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 3)
			{
				dialog.text = "Raz. Dwa. Trzy.";
				link.l1 = "Zakończmy ten spektakl. Kim pan jest?";
				link.l1.go = "DiegoDeLanda_Meeting_Third_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 4)
			{
				
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 5)
			{
				
			}
			DelLandQuestMark(npchar);
		break;
		
		case "DiegoDeLanda_Meeting_2":
			if (CheckAttribute(pchar, "questTemp.DiegoDeLanda_SantaMisericordia"))
			{
				dialog.text = "Wiecie, co jest wyjątkowego w tym grobowcu? Spoczywają tu dwie dusze, związane... więzami krwi. Ojciec i syn de Alameda. Jeden padł z rąk grzeszników, drugi... Hm, odnalazł swoją drogę do Pana.";
				link.l1 = "Dziennik dona Fernando zaprowadził mnie tutaj.";
				link.l1.go = "DiegoDeLanda_SantaMisericordia_2";
			}
			if (CheckAttribute(pchar, "questTemp.DiegoDeLanda_LadyBeth"))
			{
				dialog.text = "Widzieliście panią Bishop? Smutny los, prawda? Ale obawiam się, że zasłużony.";
				link.l1 = "Zna pan Elizabeth?";
				link.l1.go = "DiegoDeLanda_LadyBeth_2";
			}
			if (CheckAttribute(pchar, "questTemp.DiegoDeLanda_Memento"))
			{
				dialog.text = "Mortimer Grim.";
				link.l1 = "Znał go pan, rzecz jasna?";
				link.l1.go = "DiegoDeLanda_Memento_2";
			}
		break;

		case "DiegoDeLanda_Meeting_Third_2":
			dialog.text = "\nJeszcze trzy. Przy sześciu wszystko się wyjaśni.";
			link.l1 = "Jeśli nie odpowiecie mi jasno teraz, to ja...";
			link.l1.go = "DiegoDeLanda_Meeting_Third_3";
		break;

		case "DiegoDeLanda_Meeting_Third_3":
			dialog.text = "\nDobrze wam idzie, kapitanie. Zasłużyliście, by poznać moje imię. Nazywam się Diego de Landa.";
			link.l1 = "Naprawdę jesteście księdzem?";
			link.l1.go = "DiegoDeLanda_Meeting_Third_4";
		break;

		case "DiegoDeLanda_Meeting_Third_4":
			dialog.text = "Przede wszystkim jestem artystą. Ale nie spieszmy się...";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_Meeting_2";
		break;
		//<-- Встреча
		
		//--> Святое Милосердие
		case "DiegoDeLanda_SantaMisericordia_2":
			dialog.text = "Ach... Dziennik. Niezwykła rzecz – słowo pisane. Jest niczym... ścieżka w ciemności. Prowadzi tam, gdzie czeka... objawienie. Naszą parafię często odwiedzał don Fernando. Zwłaszcza w ostatnim roku.";
			link.l1 = "Służycie w miejscowej parafii? Znał pan dona Fernando?";
			link.l1.go = "DiegoDeLanda_SantaMisericordia_3";
		break;

		case "DiegoDeLanda_SantaMisericordia_3":
			dialog.text = "...";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_SantaMisericordia_4";
		break;

		case "DiegoDeLanda_SantaMisericordia_4":
			dialog.text = "Obserwowałem jego drogę. A ta księga, którą zabraliście. Wiecie, co czyni ją wyjątkową?";
			link.l1 = "Wygląda na starą.";
			link.l1.go = "DiegoDeLanda_SantaMisericordia_5";
		break;

		case "DiegoDeLanda_SantaMisericordia_5":
			dialog.text = "Starą? O nie. Ona jest... oświecona. Biblia don de Alamidy-starszego. Każde jej słowo jest jak latarnia w ciemności. Weźcie ją. Pomagajcie braciom w Chrystusie, a być może... i was zaprowadzi do czegoś... większego.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_leaving";
		break;
		//<-- Святое Милосердие

		//--> Леди Бет
		case "DiegoDeLanda_LadyBeth_2":
			dialog.text = "Och, tak. Biedna kobieta. Jej mąż... nie jest zbyt dobrym człowiekiem. Mówią, że jego plantacje są najbardziej dochodowe na Barbadosie. I najbardziej okrutne. Wiecie, ilu niewolników umiera u niego co miesiąc? Niedawno zatłukł na śmierć prawdziwego lekarza z Anglii – człowieka wielkiej wiedzy i talentu. Ale jej los nie jest wiele lepszy, uwierzcie mi.";
			link.l1 = "Wygląda na to, że jesteście dobrze poinformowani.";
			link.l1.go = "DiegoDeLanda_LadyBeth_3";
		break;

		case "DiegoDeLanda_LadyBeth_3":
			dialog.text = "Ludzie przychodzą do mnie na spowiedź, kapitanie. Słyszę to, czego boją się wyznać nawet najbliższym. Ich lęki, ich grzechy... ich ból.";
			link.l1 = "Nie boicie się prześladowań? Katolickiemu księdzu niełatwo na angielskich terytoriach.";
			link.l1.go = "DiegoDeLanda_LadyBeth_4";
		break;

		case "DiegoDeLanda_LadyBeth_4":
			dialog.text = "Moje lęki są niczym w porównaniu z tym, co właśnie zostawiliście za drzwiami tego domu. A ta książeczka, którą zabraliście tej nieszczęsnej kobiecie... Gdyby strach miał formę, wyglądałby właśnie tak\n"+
			"Dzień dobry, kapitanie.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_leaving";
		break;
		
		//<-- Леди Бет
		
		//--> Мементо
		case "DiegoDeLanda_Memento_2":
			dialog.text = "Tygrysie, Tygrysie, płonący strachu\n"+
			"Płoniesz w nocnych lasach\n"+
			"Czyj nieśmiertelny wzrok, z miłością, stworzył ciebie – tak strasznego?\n"+
			"Oczywiście, że go znałem, kapitanie. Ale czy znał go pan?";
			link.l1 = "Nigdy nie spotkałem człowieka o bardziej tragicznej historii.";
			link.l1.go = "DiegoDeLanda_Memento_3";
		break;

		case "DiegoDeLanda_Memento_3":
			dialog.text = "Spotkał pan, ale jeszcze tego nie docenił\n"+
			"Czyli jednak nie znał pan Grima. Mimo że trzyma pan jego czaszkę w rękach.";
			link.l1 = "Co?!";
			link.l1.go = "DiegoDeLanda_Memento_4";
		break;

		case "DiegoDeLanda_Memento_4":
			dialog.text = "To nie po chrześcijańsku tak obchodzić się ze zmarłym. Proszę, oto mała instrukcja post mortem. Mój prezent dla pana\n"+
			"Dzień dobry, kapitanie.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_leaving";
			SetAlchemyRecipeKnown("blade_SP_3low");	// рецепты от Катласа
			SetAlchemyRecipeKnown("blade_SP_3");
		break;

		//<-- Мементо

		//--> Прощание
		case "DiegoDeLanda_Leaving":
			DialogExit();
			AddDialogExitQuestFunction("DiegoDeLanda_Leaving");
		break;

		case "DiegoDeLanda_Leaving_1":
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 1)
			{
				dialog.text = "Powiedzcie mi... Po co? To było niebezpieczne i głupie. Co jest waszym ogniem, kapitanie? Co was napędza?";
				link.l1 = "To nie wasza sprawa.";
				link.l1.go = "DiegoDeLanda_leaving_First_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 2)
			{
				dialog.text = "Drugi.";
				link.l1 = "Ostatnim razem mówiliście zagadkami. Teraz też zamierzacie?";
				link.l1.go = "DiegoDeLanda_leaving_Second_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 3)
			{
				dialog.text = "...";
				link.l1 = "Poczekajcie, de Landa. Nie mogę pozwolić wam po prostu odejść.";
				link.l1.go = "DiegoDeLanda_Leaving_Third_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 4)
			{

			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 5)
			{

			}
		break;
		
		case "DiegoDeLanda_Leaving_First_2": // Первое прощание
			dialog.text = "Nie mogę zrozumieć. Innych – tak. Ale was – jeszcze nie.";
			link.l1 = "Innych?";
			link.l1.go = "DiegoDeLanda_Leaving_First_3";
		break;

		case "DiegoDeLanda_Leaving_First_3":
			dialog.text = "Jeden, na przykład, dąży do sprawiedliwości. Albo był też inny... opętany mrocznymi wodami śmierci. Ludzie tak łatwo zatracają się w swoich pragnieniach. Prawda?";
			link.l1 = "Jesteście dziwnym księdzem, ojcze.";
			link.l1.go = "DiegoDeLanda_Leaving_First_4";
		break;

		case "DiegoDeLanda_Leaving_First_4":
			dialog.text = "...";
			link.l1 = "Chyba już pójdę.";
			link.l1.go = "DiegoDeLanda_Leaving_First_5";
		break;

		case "DiegoDeLanda_Leaving_First_5":
			dialog.text = "Oczywiście. Wasza praca dopiero się zaczyna, kapitanie.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_Leaving_End";
		break;

		case "DiegoDeLanda_leaving_Second_2": // Второе прощание
			dialog.text = "\nPrawdziwa zagadka stoi teraz przede mną. Zebraliście już dwie… relikwie. Lubicie zbierać takie rzeczy? Jesteście kolekcjonerem?";
			link.l1 = "Skąd wiecie?";
			link.l1.go = "DiegoDeLanda_leaving_Second_3";
		break;

		case "DiegoDeLanda_leaving_Second_3":
			dialog.text = "Łowca trofeów?";
			link.l1 = "Powtarzam pytanie: skąd wiecie?";
			link.l1.go = "DiegoDeLanda_leaving_Second_4";
		break;

		case "DiegoDeLanda_leaving_Second_4":
			dialog.text = "Miłośnik mocnych wrażeń?";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_leaving_Second_5";
		break;
		
		case "DiegoDeLanda_leaving_Second_5":
			dialog.text = "\nAch. No tak. Oczywiście. Cóż, kapitanie, nie będę was zatrzymywał.";
			link.l1 = "Chwileczkę, ojcze. Nadal nie odpowiedzieliście na moje pytanie.";
			link.l1.go = "DiegoDeLanda_leaving_Second_6";
		break;

		case "DiegoDeLanda_leaving_Second_6":
			dialog.text = "Och, kapitanie. Nie mogę. Czasami odpowiedzi bolą bardziej niż ignorancja. Idźcie w pokoju. I pilnujcie swojej kolekcji... trofeów. Mogą się przydać w podróży, która was czeka.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_Leaving_End";
		break;

		case "DiegoDeLanda_Leaving_Third_2": // Третье прощание
			dialog.text = "No dalej, kapitanie. Czy to was nie ciekawi? Czy to nie zabawne? Czy już wystarczy wam trofeów?\n"+
			"To jest wasz ogień, kapitanie. Chcecie wiedzieć, co będzie dalej. Kochacie piękne statki i ciekawe rzeczy\n"+
			"Po prostu nie możecie nie zebrać ich wszystkich.\n"+
			"\n"+
			"Możecie mnie teraz zastrzelić.";
			link.l1 = "Co?!";
			link.l1.go = "DiegoDeLanda_Leaving_Third_3";
		break;

		case "DiegoDeLanda_Leaving_Third_3":
			dialog.text = "Proszę bardzo. Ale wtedy nie poznacie wszystkiego i nie zdobędziecie pełnego zestawu trofeów. Statki, swoją drogą, dostaniecie wszystkie\n"+
			"Miłego dnia, kapitanie.";
			link.l1 = "(Puścić)";
			link.l1.go = "DiegoDeLanda_Leaving_End";
			link.l2 = "(Zastrzelić)";
			link.l2.go = "DiegoDeLanda_Leaving_Shoot";
		break;
		
		case "DiegoDeLanda_Leaving_End":
			DialogExit();
			AddDialogExitQuestFunction("DiegoDeLanda_Leaving_End");
		break;
		
		case "DiegoDeLanda_Leaving_Shoot":
			DialogExit();
			AddDialogExitQuestFunction("DiegoDeLanda_Leaving_Shoot");
		break;
		
		
		//<-- Прощание
	}
} 
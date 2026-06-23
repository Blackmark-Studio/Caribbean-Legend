// торговец Аксель Йост
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
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "Spójrz na to..."+GetFullName(pchar)+"!  Czy wróciłeś z zaświatów? Jak to możliwe?";
				link.l1 = "Ludzie nie wracają z zaświatów, Axel. To proste - nie byłem martwy, ha-ha!";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = "Heh, kumpel, nie będę robił z tobą interesów, dopóki nie załatwisz spraw z Narwalami. Nie chcę kłopotów. Idź do Fazio, on się tym zajmie.";
				link.l1 = "Dobrze, zrobię to natychmiast.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && int(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "Nie chcę z tobą rozmawiać. Atakujesz spokojnych ludzi bez powodu i prowokujesz ich do walki. Zjeżdżaj!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "O! Nowa twarz! Co cię tu sprowadza? Choć, to nie moja sprawa. Pozwól, że się przedstawię: nazywam się Axel Yost i jestem właścicielem tego sklepu. Czy coś ci się podoba?";
				link.l1 = TimeGreeting()+". Nazywam się "+GetFullName(pchar)+"Jakie towary masz do zaoferowania?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ach, "+pchar.name+"„! Cieszę się, że cię widzę. Chcesz coś kupić lub sprzedać?”";
				// квестовые ветки
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "search_mush_1")
				{
					link.l4 = "Słuchaj, Axel, masz na sprzedaż porządną muszkietę? Nie taką zwykłą żołnierską strzelbę, ale coś do precyzyjnego i dalekiego zasięgu?";
					link.l4.go = "adolf";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "trader_whiskey")
				{
					link.l4 = "Słuchaj, Axel, czy Chad Kapper poprosił cię o beczkę whisky? ";
					link.l4.go = "whiskey";
				}
				if (CheckAttribute(npchar, "quest.ole_pearl"))
				{
					link.l5 = "Słuchaj, Axel, musiałeś słyszeć moją rozmowę z tym miejscowym głupkiem. O jakiej koralce on mówił? Nie rozumiem tego.";
					link.l5.go = "ole_pearl";
				}
				link.l1 = "Tak. Handlujmy, Axel!";
				link.l1.go = "Trade_items";
				link.l2 = LinkRandPhrase("Masz coś ciekawego do opowiedzenia?","Co się ostatnio wydarzyło na Wyspie?","Jakieś plotki?");
				link.l2.go = "rumours_LSC";
				link.l3 = "Jeszcze nie. Po prostu chciałem cię przywitać.";
				link.l3.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "Wszelakie rzeczy. Mikstury, ostrza, broń palna, amunicja, kirysy, klejnoty i minerały. Zaczarowane amulety i talizmany. Śmieci i przedmioty codziennego użytku. Ludzie przynoszą mi wszystko, co znajdą na rozbitych statkach, rzeczy, których sami nie potrzebują\nWięc możesz zrobić to samo. Muszę cię jednak ostrzec. Nie oferuję prowiantu ani towarów okrętowych.";
			link.l1 = "Dobrze, Axel. Zobaczmy twoje towary.";
			link.l1.go = "Trade_items";
			link.l2 = "Dzięki, Axel. Wezmę to pod uwagę. Zobaczę się z tobą, jak tylko będę potrzebować twoich usług.";
			link.l2.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "Trade_items":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 5)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;
		
		// наводка на Адольфа
		case "adolf":
			dialog.text = "To musi być jakiś żart. Jesteś trzecią osobą, która pyta. Nie mam tu takiej broni. Ale kilka miesięcy temu Adolf Barbier próbował sprzedać mi swój sztucer myśliwski z lunetą. Cudowna broń, mówię ci. Dokładnie to, czego szukasz\nAle Barbier zażądał piekielnie wysokiej ceny za to. Więc musiałem odrzucić jego ofertę.";
			link.l1 = "Interesujące! A gdzie mogę znaleźć Barbiera?";
			link.l1.go = "adolf_1";
		break;
		
		case "adolf_1":
			dialog.text = "Nie mam pojęcia. Pewnie gdzieś się kręci. Często odwiedza tawernę Sancho, lubi wypić wieczorem.";
			link.l1 = "Dzięki! Myślę, że znajdę go tam. Powiedz mi, Axel, kto jeszcze pytał cię o tę strzelbę? Wspomniałeś o innych, którzy się nią interesowali, kto to był?";
			link.l1.go = "adolf_2";
		break;
		
		case "adolf_2":
			dialog.text = "Mary Casper i Marcello, znany również jako Cyklop. Nie mam pojęcia, dlaczego dziewczyna potrzebowałaby strzelby, ale nasza Czerwona Mary to znana wariatka. Rok temu wykupiła tony prochu strzelniczego, by robić miny, na ogłuszanie krabów, jak twierdziła. Dzięki Bogu, nie pozwolono jej na to\nA Marcello chciał kupić strzelbę do polowania na ptaki, człowiek zmęczył się soloną wołowiną. Odesłałem ich oboje do Adolfa, nie wiem, czy kupili od niego strzelbę, czy nie\nRównież, ten chytry pies Giuseppe Fazio ostatnio wypytywał o Adolfa. Może on też chce kupić ten stutzen.";
			link.l1 = "Heh, mam wielu konkurentów. Dobrze, pójdę poszukać Adolfa - miejmy nadzieję, że jeszcze nie sprzedał tej broni.";
			link.l1.go = "adolf_3";
		break;
		
		case "adolf_3":
			DialogExit();
			pchar.questTemp.Saga.SharkHunt = "search_mush_2"; //флаг на таверну
			AddQuestRecord("SharkHunt", "12");
			sld = characterFromId("LSC_Adolf");
			sld.lifeday = 0; // убираем настоящего Адольфа
		break;
		
		// бусинка для Белого Мальчика - просто инфа
		case "ole_pearl":
			dialog.text = "Każdy to wie, panie! On prosi wszystkich o te paciorki, tak nazywa duże perły. Daj mu jeden, a będziesz jego najlepszym przyjacielem.";
			link.l1 = "Teraz rozumiem. Dziękuję, Axel, nigdy bym się sam nie domyślił.";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "quest.ole_pearl");
		break;
		
		// виски для Акулы
		case "whiskey":
			dialog.text = "Tak, przyjacielu, zrobił to. Ale rozczaruję cię, jeśli chcesz kupić beczkę Bushmills. Miałem tylko jedną beczkę i Chad ją kupił. Mogę ci zaoferować szkocką whisky - jest tak dobra jak irlandzka, a, szczerze mówiąc, smak podoba mi się o wiele bardziej.";
			link.l1 = "Może później. Czy Chad kupił od ciebie coś jeszcze?";
			link.l1.go = "whiskey_1";
		break;
		
		case "whiskey_1":
			dialog.text = "Nie. Interesował się arszenikiem, mówił, że na Tartarusie jest zbyt wiele szczurów i chce je wyplenić. Nie potrzebowałem arszeniku odkąd zatrudniłem tego idiotę Ollego do sprzątania mojego sklepu, wszystkie szczury poszły do tawerny biednego Sancho. Nie wiem dlaczego szczury tak bardzo boją się Ollego...";
			link.l1 = "Może ma koty w rodzinie...";
			link.l1.go = "whiskey_2";
		break;
		
		case "whiskey_2":
			dialog.text = "Ha-ha! Może... Sancho ma arsen - to pewne.";
			link.l1 = "Rozumiem. Dzięki za informację, zatem!";
			link.l1.go = "whiskey_3";
		break;
		
		case "whiskey_3":
			DialogExit();
			AddQuestRecord("SharkHunt", "36");
			pchar.questTemp.Saga.SharkHunt = "barmen_whiskey"; // флаг на таверну - поиск мышьяка
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}

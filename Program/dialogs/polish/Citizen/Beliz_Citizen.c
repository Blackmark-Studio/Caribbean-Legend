// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("Jakie pytania?","Czego chcesz?");
			link.l1 = RandPhraseSimple("Zmieniam zdanie.","Nie mam teraz nic do powiedzenia.");
		    link.l1.go = "exit";
			// Rebbebion, квест "Путеводная звезда" ==>
			if (CheckAttribute(pchar, "questTemp.PZ_Beliz.AskForLatterAndSotta") && !CheckAttribute(npchar, "questTemp.PZ_Sotta") && !CheckAttribute(npchar, "questTemp.PZ_Lutter"))
			{
				if (rand(1) == 0)
				{
					link.l1 = "Czy przypadkiem nie natknąłeś się na kapitana Edgardo Sottę? Możesz nam o nim coś opowiedzieć? Wydaje się być człowiekiem wartym poznania.";
					link.l1.go = "Sotta1";
					link.l2 = "Czy nie idziesz zobaczyć egzekucji Papli?";
					link.l2.go = "Lutter1";
				}
				else
				{
					link.l1 = "Powiedz mi, czy widziałeś bohatera dnia, kapitana Edgardo Sottę? Niestety, przegapiłem go. Jaki on jest? Nie mogę uwierzyć, że kupiec złapał niesławnego Gadający Wicher Matta!";
					link.l1.go = "Sotta1_1";
					link.l2 = "Widzę, że całe miasto świętuje pojmanie Luttera, nawet ci, którzy nigdy nie chodzą na morze."link.l2.go ="Lutter1_1";
				}
			}
			// <== квест "Путеводная звезда"
			//--> Дикая Роза
			if(CheckAttribute(pchar, "questTemp.WildRose_Etap6_Beliz") && CheckAttribute(pchar, "questTemp.WildRose_Beliz_Citizen") && !CheckAttribute(npchar, "quest.WildRose_Vopros") && npchar.city == "Beliz")
			{
				link.l1 = "Około półtora miesiąca temu do Belize przybył pewien Jerome Souvernier. Został ranny w bijatyce w 'Szklanym Oku', ale przeżył. Czy możesz mi powiedzieć, gdzie go mogę znaleźć?";
				link.l1.go = "WildRose_Beliz_Citizen_1";
			}
			if(CheckAttribute(pchar, "questTemp.WildRose_Etap6_Beliz") && CheckAttribute(pchar, "questTemp.WildRose_Beliz_Citizen_2") && !CheckAttribute(npchar, "quest.WildRose_Vopros") && npchar.city == "Beliz")
			{
				link.l1 = "Około półtora miesiąca temu, mniej więcej, w Belize pojawił się pewien dżentelmen. Nazywał się Jerome Souvernier. Szukał innego mężczyzny — więc musiał rozmawiać z mieszkańcami miasta. Później został ranny w bijatyce w tawernie, ale na szczęście przeżył. Czy możesz mi powiedzieć, gdzie go znaleźć?";
				link.l1.go = "WildRose_Beliz_Citizen_2";
			}
			if(CheckAttribute(pchar, "questTemp.WildRose_Etap6_Beliz") && CheckAttribute(pchar, "questTemp.WildRose_Beliz_Citizen_3") && !CheckAttribute(npchar, "quest.WildRose_Vopros") && npchar.city == "Beliz")
			{
				link.l1 = "Próbuję odnaleźć człowieka, który przybył do Belize około dwóch miesięcy temu. Nazywa się Jerome Souvernier. Szukał pewnego dżentelmena i przypuszczam, że rozmawiał o tym z mieszkańcami miasta...";
				link.l1.go = "WildRose_Beliz_Citizen_3";
			}
			//<-- Дикая Роза
		break;
		
		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = "Myślisz, że pracuję dla tajnej służby "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "Cóż... nie. Żegnaj zatem.";
			link.l1.go = "exit";
			link.l2 = "Jakieś inne pytanie?";
			link.l2.go = "new question";
		break;
		
		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = "Czy wyglądam jak biuro śledcze? Nie wiem, nie mam pojęcia.";

            link.l1 = "Jesteś takim bałaganiarzem! Precz.";
			link.l1.go = "exit";
			link.l2 = "Jakieś inne pytanie, zatem?";
			link.l2.go = "new question";
		break;
		
		// Квест "Путеводная звезда" ==>
		case "Sotta1":
			dialog.text = "Nie rozmawiałem z nim, ale widziałem jego statek - ciężki galeon. Niebezpiecznie jest żeglować samotnie po tych wodach, ale Sotta radzi sobie bez eskorty.";
			link.l1 = "Pewnie goni za każdym złotym dukatem i tnie koszty, gdzie tylko się da. Cóż, nie zatrzymuję cię. Dzień dobry.";
			link.l1.go = "Exit";
			
			npchar.questTemp.PZ_Sotta = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Sotta1_1":
			dialog.text = "Aye, trudno w to uwierzyć! Ale nie wierz we wszystko, co słyszysz, panie. Widziałem go, tak jasno, jak widzę cię teraz. Dobrze, że złapał Luttera, ale po co ta cała kupiecka maskarada? Zachowuje się jak żołnierz. Zawsze mogę to poznać - krewny mój służył przez lata.";
			link.l1 = "Interesujące. Cóż, każdy ma swoje tajemnice. Lepiej już pójdę. Dzięki za wgląd.";
			link.l1.go = "Exit";
			
			npchar.questTemp.PZ_Sotta = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Lutter1":
			dialog.text = "Widziałem już tego człowieka. Trudno uwierzyć, że to ten sam pirat, który przez lata terroryzował naszych kupców. Jak on w ogóle dostał własne dowództwo? Widziałem żołnierzy, którzy go eskortowali - krzyczących, płaczących, śmiejących się. Szaleniec.";
			link.l1 = "Może porażka i rzeczywistość jego nieuchronnej śmierci były dla niego zbyt wielkim ciężarem. Ale to nie ma znaczenia. Żegnaj!";
			link.l1.go = "Exit";
			
			npchar.questTemp.PZ_Lutter = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Lutter1_1":
			dialog.text = "Tak, i ja też świętuję - wielu moich rodaków zginęło z jego rąk. Nieszczęśnicy stracili ojca, brata, syna - rozumiesz, co mam na myśli. Ta barbarzyństwo trwało zbyt długo! Matt musiał być jednym z najszczęśliwszych piratów ostatnich lat, jeśli mnie pytasz.";
			link.l1 = "Prędzej czy później szczęście zawsze się kończy. Do zobaczenia.";
			link.l1.go = "Exit";
			
			npchar.questTemp.PZ_Lutter = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		// <== Квест "Путеводная звезда"
		
		//--> Дикая Роза
		case "WildRose_Beliz_Citizen_1":
    		dialog.text = "Nie znam takiego, proszę pana. Bijatyki w tawernie to niemal codzienność, a pamiętanie każdego, kto ucierpiał, to niewdzięczna sprawa.";
    		link.l1 = "Rozumiem, dziękuję. Wszystkiego dobrego.";
    		link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.WildRose_Beliz_Citizen");
			pchar.questTemp.WildRose_Beliz_Citizen_2 = true;
			npchar.quest.WildRose_Vopros;
 		break;
		
		case "WildRose_Beliz_Citizen_2":
    		dialog.text = "Souvernier? Francuz... Tak, był taki. Zwracał się do mnie, ale niczego mu nie mogłem pomóc. Nie miałem już okazji go widzieć, przepraszam.";
    		link.l1 = "Dziękuję. W takim razie będę kontynuować swoje pytania.";
    		link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.WildRose_Beliz_Citizen_2");
			pchar.questTemp.WildRose_Beliz_Citizen_3 = true;
			npchar.quest.WildRose_Vopros;
 		break;
		
		case "WildRose_Beliz_Citizen_3":
			dialog.text = "Pan Jerome! Oczywiście, pamiętam go. Jeszcze został ranny w bijatyce w tawernie. Od tego czasu prawie nie wychodzi z domu, leczy ranę na nodze.";
			link.l1 = "A gdzie znajduje się ten dom?";
    		link.l1.go = "WildRose_Beliz_Citizen_3_1";
 		break;
		
		case "WildRose_Beliz_Citizen_3_1":
    		dialog.text = "To tutaj, całkiem blisko, przy administracji portu. Dom z czerwoną dachówką. Tam go znajdziesz.";
    		link.l1 = "Dziękuję, bardzo mi Pan pomógł! Wszystkiego najlepszego!";
    		link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.WildRose_Beliz_Citizen_3");
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_3_citizen");
 		break;
		//<-- Дикая Роза
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

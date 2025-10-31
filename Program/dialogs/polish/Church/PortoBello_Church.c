// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakie pytania, "+GetSexPhrase("mój synu","moja córko")+"?","Pytaj śmiało, słucham..."),"Słucham, mów teraz, "+GetSexPhrase("mój synu","moja córko")+"...","Po raz trzeci, "+GetSexPhrase("mój synu","moja córko")+", poproś o to, czego potrzebujesz.","Duchowny ma od groma pracy, "+GetSexPhrase("mój synu","moja córko")+" a ty mnie ewidentnie rozpraszasz...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniliłem zdanie...","Nie teraz, ojcze..."),"Nie mam nic do powiedzenia, przepraszam.","Zapytam, ale później. Wybacz mi, ojcze.","Przepraszam, święty ojcze...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Письмо от покойника
			if (CheckAttribute(pchar, "questTemp.LFD_Church_1"))
            {
                link.l1 = "Ojcze święty, szukam Marisy Caldera. Mówią, że była bardzo pobożna i regularnie uczęszczała do kościoła. Czy możesz mi powiedzieć, gdzie ją znaleźć?";
                link.l1.go = "LFD_Church_1_1";
            }
			//<-- Письмо от покойника
		break;
		
		//--> Письмо от покойника
		case "LFD_Church_1_1":
			dialog.text = "Marisa była jedną z naszych najwierniejszych parafianek, prawdziwą duszą naszego kościoła. Jej nieobecność to wielka strata dla naszej wspólnoty. Co zmusiło ją do zniknięcia, nie wiem, ale jestem przekonany, że spotkały ją niesprawiedliwe próby, a w tle czaiły się knowania diabła i jego sług.\nCzasami dochodzą mnie pogłoski, że widziano ją w mieście, ale nic więcej. Pozostaje nam tylko ufać w wolę Pana i wierzyć, że pewnego dnia powróci i znów znajdzie ukojenie pod dachem kościoła.";
			link.l1 = "Może znasz kogoś, kto mógłby powiedzieć o niej coś więcej?";
			link.l1.go = "LFD_Church_1_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LFD_Church_1_2":
			dialog.text = ""+GetSexPhrase("Synu mój","Córko moja")+", powiedz, po co ci Marisa? Wiem, że od czasu do czasu szukają jej ludzie, którzy nie wyglądają na sprawiedliwych. Świat pełen jest pokus i nie każdy, kto jej szuka, ma dobre intencje. Zanim powiem choć słowo, muszę być pewien, że nie przyniesiesz krzywdy ani jej, ani tym, którzy mogą być z nią związani.";
			link.l1 = "Rozumiem twoje obawy, ojcze święty, ale zapewniam cię: nie mam złych zamiarów. Chcę tylko dostarczyć jej list, który zbyt długo wędrował do adresatki. Kto wie, może zawiera coś ważnego dla niej. Proszę, spójrz.";
			link.l1.go = "LFD_Church_1_3";
			TakeItemFromCharacter(pchar, "LFD_letter");
			notification("Oddano: List do Marisy Caldera", "None");
		break;
		
		case "LFD_Church_1_3":
			dialog.text = "Tak, ten list wygląda, jakby przeszedł wiele burz i sztormów, zanim trafił w twoje ręce. Kto wie, co w nim napisano i jakie będą skutki jego przeczytania... Ale postępujesz szlachetnie, kapitanie, oddając go adresatce. Jeśli ktoś wie, gdzie teraz jest Marisa, to jej przyjaciółka Dolores Moño – jedyna, której mogła zaufać.\nJej dom znajduje się na lewo od biura portowego. Mam nadzieję, że ten list nie przyniesie Marisie nowych cierpień – i tak już doznała ich wystarczająco dużo.";
			link.l1 = "Dziękuję ci, ojcze święty. Niech Pan cię strzeże.";
			link.l1.go = "LFD_Church_1_4";
			GiveItem2Character(PChar, "LFD_letter");
		break;
		
		case "LFD_Church_1_4":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Church_1");
		break;
		//<-- Письмо от покойника
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

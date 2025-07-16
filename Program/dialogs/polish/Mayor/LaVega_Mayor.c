// заместитель Маркуса Тиракса в Ла Веге
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

// ------------------------------------------блок angry-----------------------------------------------
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
            switch (npchar.angry.kind) //сюда расписываем реакцию ангри. В npchar.angry.name пробелы удалены!!!
            {
                case "repeat":
                    if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
                    if (npchar.angry.name == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                break;
            }
        }
    }
// ------------------------------------------блок angry-----------------------------------------------

	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
            dialog.text = NPCStringReactionRepeat("Masz coś do powiedzenia? Nie? To wynoś się stąd!"," Myślę, że wyraziłem się jasno, przestań mnie denerwować.","Chociaż wyraziłem się jasno, nadal mnie irytujesz!","Dobrze, zaczyna mnie męczyć ta nieuprzejmość.","repeat",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Już odchodzę.","Pewnie"+npchar.name+"... ","Przykro mi, "+npchar.name+"... ","Ojej...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

        case "I_know_you_good":
            dialog.text = NPCStringReactionRepeat(GetFullName(pchar)+", cieszę się, że cię widzę! Czego sobie życzysz?","Co jeszcze?"," Znowu ty? Nie zawracaj ludziom głowy, jeśli nie masz nic do roboty!","Wiem, że jesteś przyzwoitym człowiekiem. Ale skończyłem z tobą rozmawiać.","powtórz",10,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Nic. Po prostu chciałem cię zobaczyć.","Nic...","Dobrze, "+npchar.name+"Przepraszam...","Do diabła, to tylko moja wina...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Złodziejstwo!!! Czy ty mówisz poważnie?! Jesteś skończony, kolego...","Zaczekaj, co do diabła? Okazuje się, że jesteś złodziejem! To twój koniec...");
			link.l1 = LinkRandPhrase("Cholera!","Carramba!!","Do diabła!!");
			link.l1.go = "PL_Q3_fight";
		break;
					
		// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple(" "+GetSexPhrase("Odejdź","Odejdź ")+" stąd!"," Wynoś się z mojego domu!");
			link.l1 = "Och...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Nie zawracaj mi głowy swoimi tanimi gadkami. Następnym razem nie spodoba ci się wynik...";
        			link.l1 = "Zrozumiałem.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryRepeat_2":
            dialog.text = "To koniec, nie ma rozmów.";
			link.l1 = RandPhraseSimple("Jak sobie życzysz...","Dobrze więc...");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Mam nadzieję, że okażesz mi więcej szacunku i przestaniesz być niegrzeczny? W przeciwnym razie będę musiał cię zabić. To byłoby bardzo nieprzyjemne.";
        			link.l1 = "Zrozumiałem, kapitanie."+npchar.name+"Możesz być pewien, że tak zrobię.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
		break;
		case "AngryExitAgainWithOut":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
            DoReloadCharacterToLocation("Lavega_town","reload","reload6");
		break;
		// <<<<<<<<<<<<============= блок нод angry =============================
		
		// Rebbebion, квест "Путеводная звезда"
		case "PZ1":
			dialog.text = "Ah, to ty, de Maure. Cóż za niespodzianka. Na diabła morskiego, twój przyjazd to najciekawsza rzecz, jaka się wydarzyła od dłuższego czasu, do diabła.";
			link.l1 = "Dobrze cię widzieć, Vensan. Cieszysz się rządzeniem wioską?";
			link.l1.go = "PZ2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ2":
			dialog.text = "Jakże bym mógł? Jestem kapitanem, i to cholernie dobrym, a nie jakimś przeklętym księgowym. I czekałem na posłańców Marcusa, żeby wezwali mnie na nową podróż, dłużej niż czekałem na Boże Narodzenie, przeklęte klątwy!";
			link.l1 = "Święta Bożego Narodzenia i przekleństwa w jednym zdaniu, to coś. Aye, nie zazdroszczę ci. Choć wielu chciałoby być na twoim miejscu. Ale przybyłem do ciebie w interesach, Vensan.";
			link.l1.go = "PZ3";
		break;
		
		case "PZ3":
			dialog.text = "Interes?! No, wykrztuś to z siebie - wymyśliłeś coś? Masz dobry trop? Zaraz osuszę lokalną piwniczkę z czystej nudy i tych cholernych obliczeń.";
			link.l1 = "Cóż, chodzi bardziej o to, że mam do ciebie pytanie, nic więcej.";
			link.l1.go = "PZ4";
		break;
		
		case "PZ4":
			dialog.text = "Do diabła! Ale dobrze, słucham, Charles.";
			link.l1 = "Czy przybyła do was jakaś kobieta? A może zauważyliście ją w La Vega? Znana jest pod imieniem Belle Étoile, choć to tylko pseudonim, więc mogła się przedstawić pod innym imieniem. Ważne jest to, że... ma żółtą skórę. Ale nie jest niewolnicą ani robotnicą - to zamożna kobieta.";
			link.l1.go = "PZ5";
		break;
		
		case "PZ5":
			dialog.text = "Żółtoskóry, ale bogaty? Nigdy nie mieliśmy tu kogoś takiego, nigdy! Wygląda na to, że wciąż prowadzisz swoje interesujące życie, de Maure! Prawie ci zazdroszczę.";
			link.l1 = "Czyżby... Cóż, dzięki za twój czas, Vensan. Już cię dłużej nie będę odciągać od twojej buchalterii, heh-heh.";
			link.l1.go = "Exit";
			
			AddQuestRecord("PZ", "40");
			
			pchar.quest.PZ_SetHeavyFrigate.win_condition.l1 = "location";
			pchar.quest.PZ_SetHeavyFrigate.win_condition.l1.location = "Hispaniola1";
			pchar.quest.PZ_SetHeavyFrigate.win_condition = "PZ_SetHeavyFrigate";
			DelMapQuestMarkCity("LaVega");
			AddMapQuestMarkCity("PortPax", false);
			LocatorReloadEnterDisable("LaVega_ExitTown", "reload1_back", true);
			LocatorReloadEnterDisable("PortPax_town", "gate_back", true);
		break;
	}
}

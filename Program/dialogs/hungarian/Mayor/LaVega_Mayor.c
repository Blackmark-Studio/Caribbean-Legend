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
            dialog.text = NPCStringReactionRepeat("Van valami mondanivalója? Nincs? Akkor tûnj el innen!",
                         "Azt hiszem, világosan fejeztem ki magam, ne idegesítsen tovább.", "Bár világosan fejeztem ki magam, te továbbra is idegesítesz!",
                         "Rendben, kezdek belefáradni ebbe a bunkóságba.", "repeat", 3, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Én máris elmegyek.",
                                               "Biztos"+npchar.name+"...",
                                               "Sajnálom, "+npchar.name+"...",
                                               "Oups...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

        case "I_know_you_good":
            dialog.text = NPCStringReactionRepeat(GetFullName(pchar) + ", örülök, hogy látlak! Mit kívánsz?",
                         "Mi mást?", " Már megint te? Ne zavard az embereket, ha nincs semmi dolgod!",
                         "Tudom, hogy te egy tisztességes ember vagy. De én már nem beszélek veled.", "repeat", 10, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Semmi. Csak látni akartalak.",
                                               "Semmi...",
                                               "Oké, "+npchar.name+", bocsánat...",
                                               "Francba, ez csak az én hibám...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Tolvajlás!!! Ez most komoly?! Végeztél, haver...", "Várj, mi a fene? Kiderült, hogy tolvaj vagy! Végeztél...");
			link.l1 = LinkRandPhrase("A francba!", "Carramba!!", "A francba!!");
			link.l1.go = "PL_Q3_fight";
		break;
					
		// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple(""+ GetSexPhrase("Tûnj el","Tûnj el ") +" innen!", "Takarodj az otthonomból!");
			link.l1 = "Oups...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Ne zavarj az olcsó beszédeddel. Legközelebb nem fog tetszeni az eredmény...";
        			link.l1 = "Megvan.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryRepeat_2":
            dialog.text = "Vége van, nincs beszéd.";
			link.l1 = RandPhraseSimple("Ahogy kívánod...", "Akkor jó...");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Remélem, hogy több tiszteletet mutatsz majd irántam, és nem leszel többé goromba? Különben meg kell, hogy öljelek. Az nagyon kellemetlen lenne.";
        			link.l1 = ""+npchar.name+", Biztos lehetsz benne, hogy meg fogom.";
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
		case "PZ_1":
			dialog.text = "Á, te vagy az, de Maure. Micsoda meglepetés. A tenger ördögére, a te érkezésed a legérdekesebb dolog, ami hosszú ideje történt, a fenébe is.";
			link.l1 = "Én is örülök, hogy látlak, Vensan. Élvezed a falu irányítását?";
			link.l1.go = "PZ_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_2":
			dialog.text = "Hogy tehettem volna? Kapitány vagyok, méghozzá rohadt jó, nem valami rohadt könyvelô. És már régebb óta várok Marcus' messengersre, hogy új útra hívjon, mint ahogyan a karácsonyt vártam, átkozott átkok!";
			link.l1 = "Karácsony és átkok egy mondatban, ez már valami. Igen, nem irigyellek. Bár sokan szeretnének a jelenlegi helyzetedben lenni. De én üzleti ügyben jöttem hozzád, Vensan.";
			link.l1.go = "PZ_3";
		break;
		
		case "PZ_3":
			dialog.text = "Üzleti ügyben?! Nos, akkor köpd ki - kitaláltál valamit? Van egy jó ötleted? Már majdnem lecsapoltam a helyi pincét a puszta unalomtól és ezektôl az átkozott számításoktól.";
			link.l1 = "Nos, inkább csak egy kérdésem lenne hozzád, semmi több.";
			link.l1.go = "PZ_4";
		break;
		
		case "PZ_4":
			dialog.text = "A fenébe! De rendben, hallgatlak, Charles.";
			link.l1 = "Egy nô jött hozzád? Vagy talán La Vegában szúrtad ki? A Belle Étoile névre hallgat, bár ez csak egy álnév, szóval lehet, hogy más néven mutatkozott be. Ami fontos, hogy ô... sárga bôrû. De nem rabszolga vagy munkás - ô egy gazdag nô.";
			link.l1.go = "PZ_5";
		break;
		
		case "PZ_5":
			dialog.text = "Sárga bôrû, de gazdag? Soha nem volt még ilyen emberünk itt, soha! Úgy tûnik, még mindig érdekes életet élsz, de Maure! Majdnem irigykedem.";
			link.l1 = "Tényleg így van... Nos, köszönöm az idejét, Vensan. Nem akarom tovább zavarni a könyvelésétôl, heh-heh.";
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

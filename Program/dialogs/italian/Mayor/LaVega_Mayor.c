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
            dialog.text = NPCStringReactionRepeat("Hai qualcosa da dirmi? No? Allora vattene da qui!","Credo di essermi espresso chiaramente, smetti di infastidirmi.","Nonostante mi sia espresso chiaramente, continui a infastidirmi!","Bene, sto perdendo la pazienza con questa maleducazione.","ripeti",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sto già partendo.","Certo"+npchar.name+"...","Mi dispiace, "+npchar.name+"...","Ops...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

        case "I_know_you_good":
            dialog.text = NPCStringReactionRepeat(GetFullName(pchar)+", sono felice di vederti! Cosa desideri?","Cosa altro?","Di nuovo tu? Non disturbare la gente se non hai nulla da fare!","So che sei un uomo decente. Ma ho finito di parlarti.","ripeti",10,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Nulla. Volevo solo vederti.","Niente...","Ok, "+npchar.name+", scusa...","Maledizione, è solo colpa mia...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Furto!!! Sul serio?! Sei finito, amico...","Aspetta, che diavolo? Si scopre che sei un ladro! Sei finito...");
			link.l1 = LinkRandPhrase("Merda!","Carramba!!","Maledizione!!");
			link.l1.go = "PL_Q3_fight";
		break;
					
		// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple(""+GetSexPhrase("Vattene","Vattene ")+" da qui!","Vattene dalla mia casa!");
			link.l1 = "Ops...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Non infastidirmi con le tue chiacchiere da quattro soldi. La prossima volta il risultato non ti piacerà...";
        			link.l1 = "Ce l'ho fatta.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryRepeat_2":
            dialog.text = "È finita, niente chiacchiere.";
			link.l1 = RandPhraseSimple("Come desiderate...","Bene allora...");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Spero che mostrerai più rispetto per me e smetterai di essere maleducato? Altrimenti dovrei ucciderti. Sarebbe molto sgradevole.";
        			link.l1 = ""+npchar.name+", puoi essere sicuro, lo farò.";
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
			dialog.text = "Ah, sei tu, de Maure. Che sorpresa. Per il diavolo del mare, la tua arrivo è la cosa più interessante che sia accaduta da molto tempo, dannazione.";
			link.l1 = "È un piacere vederti anche tu, Vensan. Ti piace governare il villaggio?";
			link.l1.go = "PZ2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ2":
			dialog.text = "Come potrei? Sono un capitano, maledettamente bravo in ciò, non qualche dannato ragioniere. E ho aspettato i messaggeri di Marcus per convocarmi per un nuovo viaggio più a lungo di quanto abbia aspettato il Natale, maledizioni!";
			link.l1 = "Natale e maledizioni in una sola frase, questa è nuova. Già, non ti invidio. Anche se, a molti piacerebbe essere al tuo posto. Ma sono venuto da te per affari, Vensan.";
			link.l1.go = "PZ3";
		break;
		
		case "PZ3":
			dialog.text = "Affari?! Beh, sputalo fuori allora - hai pensato a qualcosa? Hai una buona pista? Sto per svuotare la cantina locale per pura noia e tutti questi maledetti calcoli.";
			link.l1 = "Ebbene, è più che ho una domanda per te, nient'altro.";
			link.l1.go = "PZ4";
		break;
		
		case "PZ4":
			dialog.text = "Maledizione! Ma va bene, ti sto ascoltando, Charles.";
			link.l1 = "È venuta a trovarti una donna? O forse l'hai vista a La Vega? Si fa chiamare Belle Étoile, anche se è solo un alias, quindi potrebbe essersi presentata con un nome diverso. Ciò che è importante è che... ha la pelle gialla. Ma non è una schiava o una lavoratrice - è una donna ricca.";
			link.l1.go = "PZ5";
		break;
		
		case "PZ5":
			dialog.text = "Pelle gialla, ma ricco? Non abbiamo mai avuto nessuno del genere qui, mai! Sembra che tu stia ancora vivendo quella tua interessante vita, de Maure! Quasi mi fai invidia.";
			link.l1 = "È così... Beh, grazie per il tuo tempo, Vensan. Non ti distrarrò più a lungo dalla tua contabilità, eh-eh.";
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

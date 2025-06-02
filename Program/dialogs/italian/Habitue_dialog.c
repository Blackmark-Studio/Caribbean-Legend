#include "DIALOGS\%language%\Common_Duel.c" //navy
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
    ref NPChar, d;
	aref Link, Diag;
	string NPC_Meeting, TempInfoCharacterID_1, TempInfoCharacterID_2, sQuestTitle, sStr;
	int DonationSize;
    	
	// Warship 18.05.08
	int iLa_Puesta; // La puesta - это ставка по-испански
    	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(Diag, NPChar.Dialog);
	
    ProcessCommonDialogRumors(NPChar, Link, Diag);//homo 25/06/06
    ProcessDuelDialog(NPChar, Link, Diag); //navy

	int iEnemyDice, iPCDice;
	int d1,d2,d3,d4;
	bool ok;
    ref sld;
    
	if (npchar.quest.Meeting != LastSpeakDate())
	{
		npchar.quest.Meeting = LastSpeakDate();
		npchar.money = 100 + rand(10) * makeint(50 * sti(PChar.rank) * (10.0 / MOD_SKILL_ENEMY_RATE));
		if (sti(npchar.money) < 150) npchar.money = 150;
        if (bBettaTestMode)
        {
            Dialog.CurrentNode = "Beta_test";
        }
	}
	switch (Dialog.CurrentNode)
	{
		// -----------------------------------Диалог первый - первая встреча
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

        case "Beta_test":
            dialog.text = "Selezione del tipo di ubriacone (beta)";
			link.l1 = "Ubriacone";
			link.l1.go = "Beta_test_alc";
            link.l2 = "Carte giocatore d'azzardo";
			link.l2.go = "Beta_test_card";
			link.l3 = "Giocatore di dadi";
			link.l3.go = "Beta_test_dice";
		break;
		
		case "Beta_test_alc":
            dialog.text = "Ubriacone selezionato";
			link.l1 = "Continua";
			link.l1.go = "First time";
			npchar.quest.last_theme = 0;
		    npchar.quest.last_theme_game = 0;
		break;
		
		case "Beta_test_card":
            dialog.text = "Giocatore di carte (30% di probabilità di risentirsi subito)";
			link.l1 = "Continua";
			link.l1.go = "First time";
			npchar.quest.last_theme = 1;
		    npchar.quest.last_theme_game = 0;
		break;
		
		case "Beta_test_dice":
            dialog.text = "Giocatore di dadi (30% di risentire subito)";
			link.l1 = "Continua";
			link.l1.go = "First time";
			npchar.quest.last_theme = 1;
		    npchar.quest.last_theme_game = 1;
		break;
		
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = LinkRandPhrase("Potrei essere ubriaco ma non sono un idiota. Se bevo con te ora, il giorno dopo i soldati mi prenderanno. Assolutamente no!","Non sono un nemico della mia città. Non berrò con te!",""+GetSexPhrase("compagno","ragazza")+", faresti meglio a lasciare questo posto mentre puoi ancora...");
				link.l1 = RandPhraseSimple("Bene, come desideri...","Ehi, sai, non ho bisogno di ubriacarmi così tanto. Non è il momento giusto per farlo."); 
				link.l1.go = "exit";
				break;
			}
			if(CheckAttribute(pchar,"questTemp.HabitueSpeakDisable") && rand(1) == 0) // если дуэлянт то каждый второй посылает нафик
			{
				dialog.text = "Ah, mis"+GetSexPhrase("ter","s")+", sicuramente, ho sentito parlare di te, he-he. La gente nelle taverne dice che sei un provocatore e un duellante. Dico che la nostra gente non si spaventa facilmente, ma nessuno vuole morire per una tazza di rum. Trovo spaventoso anche solo sedermi vicino a te, quindi sarebbe meglio se passassi.";
				link.l1 = LinkRandPhrase("Buon viaggio, allora!","Sparisci, mentre sono ancora di buon umore...","Vai, vai! Sparisci, cibo per pesci!");
				link.l1.go = "exit";
				link.l2 = "Aspetta, volevo fare una domanda....";
				link.l2.go = "talk_habitue_duel";
				break;
			}
			
            ok = CheckFreeSitFront(npchar);
            
            dialog.text = "Non stare nella mia luce, non riesco a vedere le mosche nella brocca!";
            link.l1 = "Non sto in piedi...";
		    link.l1.go = "exit";
		    if (!chrDisableReloadToLocation)
		    {
	            switch (npchar.quest.last_theme)
				{
					case "0": //пьяный.
						dialog.text = "Hic! Oh, "+GetSexPhrase("compagno, sembri proprio un vecchio lupo di mare navigato","ragazza, sicuramente sembri un vecchio lupo di mare esperto")+"! Forse, mi compreresti un bicchiere di rum?";
						link.l1 = "Potrei essere un vecchio lupo di mare, ma questo non significa che comprerò alcol per la canaglia...";
						link.l1.go = "exit";

						if (makeint(pchar.money) >= 100 && ok) // только старые острова окучены на сесть
						{
							link.l2 = "Mi unirei volentieri alla tua compagnia.";
							link.l2.go = "talk_with_alchogol";
						}
						else
						{
	                        link.l2 = "E perché mai?";
							link.l2.go = "talk_with_alchogol_song";
						}
					break;

					case "1":
	                    if (rand(3) != 1 && ok)
	                    {
							switch (sti(npchar.quest.last_theme_game))
							{
							    case 0 :
									// Игра в карты boal 20/05/05 -->
	                                if (CheckNPCQuestDate(npchar, "Card_date_begin"))
									{
										Dialog.text = RandPhraseSimple("Una partita a carte, forse? Un gioco molto interessante!","Suggerisco di giocare a carte. Cosa ne dici?");
										link.l1 = "E perché no? Certo, giochiamo.";
										link.l1.go = "Cards_begin";
										link.l2 = "E quali sono le regole del tuo gioco?";
										link.l2.go = "Cards_Rule";
										link.l3 = "Non ora.";
										link.l3.go = "exit";
									}
									else
					    			{
										Dialog.text = "No, non giocherò più a carte con te.";
						    			link.l1 = "Come dici tu.";
						    			link.l1.go = "exit";
									}
			                        // Игра в карты boal 20/05/05 <--
		                        break;

								case 1:
								// кости
		    						// Игра в кости boal 13/07/05 -->
	                                if (CheckNPCQuestDate(npchar, "Dice_date_begin"))
									{
										Dialog.text = RandPhraseSimple("Una partita a dadi, forse? Un gioco molto interessante!","Suggerisco di tirare alcuni dadi. Cosa dici?");
										link.l1 = "E perché no? Certo, giochiamo.";
										link.l1.go = "Dice_begin";
										link.l2 = "E quali sono le regole del tuo gioco?";
										link.l2.go = "Dice_Rule";
										link.l3 = "Non ora.";
										link.l3.go = "exit";
									}
									else
					    			{
										Dialog.text = "No, non giocherò più a dadi con te.";
					    				link.l1 = "Come dici tu.";
					    				link.l1.go = "exit";
									}
			                        // Игра в кости boal 13/07/05 <--
			                        //navy --> Дуэли
									if (CheckAttribute(NPchar, "Quest.DiceCheats") && sti(NPchar.Quest.DiceCheats) >= 1) 
									{
					    				link.l9 = RandSwear()+" Stavi barando!!!";
					    				link.l9.go = "outraged";
									}
									//navy <--
			    				break;
	    					} 
						}
	        			else
	        			{
	                        dialog.text = RandPhraseSimple("Allontanati dal mio tavolo! Ora!"," Oh? Cosa? Chi è quello? Hic... Vattene!");
	                        link.l1 = RandPhraseSimple("Bere condanna la tua anima peccatrice! Ritorna in te stesso!","Non essere scortese con me.");
	        			    link.l1.go = "exit";
	        			    link.l2 = RandPhraseSimple("Guarda la tua lingua, canaglia! O ti insegnerò le buone maniere.","E se ti colpissi in testa ora, immagino che ti aiuterebbe a rinsavire.");
	        	            link.l2.go = "tavern_keeper";
	        			}
					break;
				}
			}
			Diag.TempNode = "First time";
	    break;
	    
		case "talk_habitue_duel":
			dialog.text = "Non ti sto dicendo niente, signorina"+GetSexPhrase("ter","s")+"! E non credo che qualcuno altro parlerà con te, dato che significa sempre guai. Ma sai, le persone tendono ad avere una memoria corta, quindi tra un mese o due potrebbero dimenticare la tua avventura, se non gliela ricordi di nuovo, ovviamente, he-he! Addio, mis"+GetSexPhrase("ter","s")+". ";
			link.l1 = "Bene...";
			link.l1.go = "exit";
		break;
		
	    // карты -->
	    case "Cards_Rule":
   			dialog.text = CARDS_RULE;
			link.l1 = "Bene, allora cominciamo...";
			link.l1.go = "Cards_begin";
			link.l3 = "No, non è per me...";
			link.l3.go = "exit";
		break;
		
		case "Cards_begin":
			Diag.tempnode = "Cards_Node";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.questTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("alc");
		break;

		case "Cards_Node":
			Diag.tempNode = "first time";

			Dialog.text = "Determiniamo prima la scommessa poi (inserisci scommessa).";
			link.l1 = "100";
			link.l1.edit = 1;
			link.l1.go = "Cards_Node_2";
			link.l3 = "Immagino che debba andare.";
			link.l3.go = "exit_sit";
		break;
		
		case "Cards_Node_2":
			iLa_Puesta = GetStrSmallRegister(dialogEditStrings[1]);
            if (!CheckCardsGameSmallRate())
		    {
                dialog.text = "Sei un noto baro. Non giocherò d'azzardo con te.";
                link.l1 = "È tutto bugie! Beh, comunque.";
			    link.l1.go = "exit_sit";
			    break;
		    }
		    
			if (sti(PCHar.Money) < sti(iLa_Puesta)*3)
		    {
                dialog.text = "Vedo che sei al verde, "+GetSexPhrase("amico","tesoro")+". Torna quando diventi ricco.";
                link.l1 = "Bene.";
			    link.l1.go = "exit_sit";
			    break;
		    }
		
			if (sti(NPChar.Money) < sti(iLa_Puesta)*3)
		    {
                dialog.text = "Ho già perso tutto quello che avevo. Oggi non è il mio giorno fortunato.";
                link.l1 = "Bene.";
			    link.l1.go = "exit_sit";
			    break;
		    }
		else
		{
			if(sti(iLa_Puesta) < 50)
			{
				dialog.text = "Ti stai prendendo gioco di me o cosa?! Giocando per "+iLa_Puesta+" pesos?! Giocare per scommesse ragionevoli, o me ne vado!";
				link.l1 = "Sì, hai ragione. Dobbiamo alzare un po' la scommessa.";
				link.l1.go = "Cards_begin_2";
				link.l2 = "Ho cambiato idea, non gioco più.";
				link.l2.go = "exit_sit";
				break;
			}
			
			if(sti(iLa_Puesta) > 1000)
			{
				dialog.text = "Giocare per così tanti soldi? No, passo, a meno che non cambi la scommessa.";
				link.l1 = "Sì, hai ragione. Dobbiamo abbassare un po' la scommessa.";
				link.l1.go = "Cards_begin_2";
				link.l2 = "Effettivamente, ho deciso di non giocare affatto.";
				link.l2.go = "exit_sit";
				break;
			}
			dialog.text = "Bene, giochiamo per "+iLa_Puesta+" monete.";
			link.l1 = "Distribuisci le carte!";
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
			pchar.GenQuest.Cards.iRate     = sti(iLa_Puesta);
            pchar.GenQuest.Cards.SitType   = true;
		}
		break;
		
		case "Cards_begin_2":
			dialog.text = "Allora qual è la scommessa? (Inserisci scommessa)";
			link.l1 = "50";
			link.l1.edit = 1;
			link.l1.go = "Cards_Node_2";
			link.l2 = "Credo che non giocherò, dopo tutto...";
			link.l2.go = "exit_sit";
		break;
							
		case "Cards_begin_go":
            // анлим игры в день SetNPCQuestDate(npchar, "Card_date_begin");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
            LaunchCardsGame();
		break;
	    // карты <--
	    // КОСТИ -->
	    case "Dice_Rule":
   			dialog.text = DICE_RULE;
			link.l1 = "Bene, allora cominciamo...";
			link.l1.go = "Dice_begin";
			link.l3 = "No, non è per me...";
			link.l3.go = "exit";
		break;

		case "Dice_begin":
			Diag.tempnode = "Dice_Node";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.questTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("alc");
		break;

		case "Dice_Node":
		    Diag.tempNode = "first time";		    
			Dialog.text = "Determiniamo la scommessa (inserisci scommessa).";
			link.l1 = "50";
			link.l1.edit = 1;
			link.l1.go = "Dice_Node_2";
			link.l3 = "Immagino che devo andare.";
			link.l3.go = "exit_sit";
		break;

		case "Dice_Node_2":
			iLa_Puesta = GetStrSmallRegister(dialogEditStrings[1]);
            if (!CheckDiceGameSmallRate())
		    {
				dialog.text = "Sei un noto baro. Non lancerò i dadi con te.";
                link.l1 = "È tutto bugie! Beh, comunque.";
			    link.l1.go = "exit_sit";
			    break;
		    }

			if (sti(pchar.Money) < sti(iLa_Puesta)*6)
		    {
                dialog.text = "Vedo che sei al verde, "+GetSexPhrase("amico","tesoro")+". Torna quando diventi ricco.";
                link.l1 = "Bene.";
			    link.l1.go = "exit_sit";
			    break;
		    }
			
			if (sti(npchar.Money) < sti(iLa_Puesta)*6)
		    {
                dialog.text = "Ho già perso tutto quello che avevo. Oggi non è il mio giorno fortunato.";
                link.l1 = "Bene.";
			    link.l1.go = "exit_sit";
			    break;
		    }
		else
		{
			if(sti(iLa_Puesta) < 50)
			{
				dialog.text = "Stai ridendo di me o cosa?! Giocando per "+iLa_Puesta+" pesos al giorno?! Giocare per scommesse ragionevoli, o sono fuori!";
				link.l1 = "Sì, hai ragione. Dobbiamo alzare un po' la scommessa.";
				link.l1.go = "Dice_begin_2";
				link.l2 = "Ho cambiato idea, non gioco.";
				link.l2.go = "exit_sit";
				break;
			}
			
			if(sti(iLa_Puesta) > 1000)
			{
				dialog.text = "Giocare a dadi per così tanti soldi? No, passo, a meno che non cambi la scommessa.";
				link.l1 = "Sì, hai ragione. Dobbiamo ridurre un po' la scommessa.";
				link.l1.go = "Dice_begin_2";
				link.l2 = "Infatti, ho deciso di non giocare affatto.";
				link.l2.go = "exit_sit";
				break;
			}
			dialog.text = "Bene, giochiamo per "+iLa_Puesta+" monete per dado.";
			link.l1 = "Andiamo!";
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
			pchar.GenQuest.Dice.iRate     = sti(iLa_Puesta);
            pchar.GenQuest.Dice.SitType   = true;
		}
		break;
		
		case "Dice_begin_2":
			dialog.text = "Allora qual è la scommessa? (Inserisci scommessa)";
			link.l1 = "50";
			link.l1.edit = 1;
			link.l1.go = "Dice_Node_2";
			link.l2 = "Credo che alla fine non giocherò...";
			link.l2.go = "exit_sit";
			break;

		case "Dice_begin_go":
            // анлим игры в день SetNPCQuestDate(npchar, "Dice_date_begin");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
            LaunchDiceGame();
		break;
	    // КОСТИ <--

		/////////////////////////////////////////////
        case "talk_with_alchogol_song":
			dialog.text = "Ebbene, h-hic! Le cose vanno bene. Hic! Non lo vedi arrivare. Hi-ic! Questo rum è buono. Rum nero della Giamaica. hic!\nEcco, metti e versa!";
			link.l1 = "Va bene, perché no.";
			link.l1.go = "talk_with_alchogol_song_2";
			link.l2 = "Mi dispiace amico, devo andare.";
			link.l2.go = "exit";
		break;
		
		case "talk_with_alchogol_song_2":
			dialog.text = "Boccali e volti vanno e vengono... Hic... Fino a quando non cado a terra. Bevo tutto il tempo... Hic! Dove è il liquore... E qual è la rima...";
			link.l1 = "Qui c'è il rum e le ragazze sono belle, tutte vogliono un bucaniere, ma sembra che solo il rum sia mio.";
			link.l1.go = "talk_with_alchogol_song_3";
			link.l2 = "Non ho tempo per questo.";
			link.l2.go = "exit";
		break;
		
		case "talk_with_alchogol_song_3":
			dialog.text = "Quando sei triste, non cercare di pensare, vieni da noi e beviamo! Tutto andrà sicuramente bene, io sono tuo amico, e tu sei il mio!";
			link.l1 = "Avere un amico è davvero fantastico, quando te ne vai lui aspetterà, con un amico non c'è odio, ma quando il rum è finito c'è solo un dibattito. Quindi beviamo amico, prima che io vada e sia in ritardo...";
			link.l1.go = "exit";
		break;
		
		case "talk_with_alchogol":
			Diag.TempNode = "begin_sit";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.questTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("alc");
		break;

		case "begin_sit":
			Diag.TempNode = "first time";
			dialog.snd = "Voice\HADI\HADI028";
			dialog.text = LinkRandPhrase("Hic! Ora è meglio! Sicuramente è meglio! Allora? Mi offri del rum o cosa?","Siediti, "+GetAddress_Form(npchar)+", beviamo una tazza del buon vecchio rum giamaicano. Non fa mai male alla salute. E se sei interessato a quello che sta succedendo - non troverai un posto migliore di questa taverna, te lo assicuro. Un po' di soldi, un paio di bicchieri di rum decente - e saprai tutto quello che dovevi sapere, e anche di più, fidati di un vecchio avventore...","Ehi, per favore, siediti, "+GetSexPhrase("mio buon amico","signorina")+", beviamo... Perché non bere in buona compagnia? Puoi sentire molte cose interessanti se sei paziente e bevi lentamente, a piccoli sorsi... Ci sono capitani che si vantano delle loro avventure, ci sono molti altri che blaterano cose importanti, quando non si controllano più... Molte persone passano il loro tempo lì, e molti hanno qualcosa da raccontare, credimi, "+GetSexPhrase("il mio buon amico","Signorina")+".");
			link.l1 = "E perché no! Barista! Rum, per entrambi!";
			link.l1.go = "sit_2";
		break;

		// Церковный генератор. Квест №2 -->
		case "Alcogol_GenQuest_Church_2_1":
			dialog.text = "Certo! Hai sentito... i banditi saccheggiano persino le chiese!";
				link.l1 = "Beh, sembra proprio il lavoro dei pirati, chi altri...";
				link.l1.go = "Alcogol_GenQuest_Church_2_2";
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople");
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen");
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskAlcash");
			break;
			
		case "Alcogol_GenQuest_Church_2_2":
			dialog.text = "Quali pirati? Solo comuni terroni, e sicuro i maledetti locali... Se fossero stati visitatori, non avrebbero saputo quando le casse della chiesa erano piene. E difficilmente si sarebbero messi in quel guaio, comunque.";
				link.l1 = "Coraggiosi, questo è certo. Hanno aperto così galantemente una fragile barra della porta...";
				link.l1.go = "Alcogol_GenQuest_Church_2_3";
			break;
			
		case "Alcogol_GenQuest_Church_2_3":
			dialog.text = "A-ha. E anche furbi. Chi si esporrebbe in questo modo?";
				link.l1 = "Vero. L'intera parrocchia stava risparmiando denaro da donare alla chiesa, e ora questi astuti ragazzi hanno fatto la loro fortuna con esso? Sicuramente saranno catturati. Ora tutto il mondo li sta cercando.";
				link.l1.go = "Alcogol_GenQuest_Church_2_4";
			break;
			
		case "Alcogol_GenQuest_Church_2_4":
			dialog.text = "Affatto. Chi lo cercherà? Hanno appena derubato la chiesa e lasciato la città, spariti come il vento. La giungla è vasta, molto vasta, li cercheresti lì fino al giorno del giudizio. E dopo un paio di mesi la gente si dimenticherà completamente, segna le mie parole!";
				link.l1 = "Non credo. Queste cose non possono essere perdonate.";
				link.l1.go = "Alcogol_GenQuest_Church_2_5";
			break;
			
		case "Alcogol_GenQuest_Church_2_5":
			dialog.text = "La memoria di un uomo è come una scialuppa che perde. Le persone dimenticheranno e perdoneranno. Ma Dio?! Lui vede tutto. È lui che devi temere. Dico, dieci anni fa è successo qualcosa di terribile a un vecchio compagno di mine. Anche lui mancava di rispetto per il Creatore, e quasi è andato dritto dal diavolo del mare...";
				link.l1 = "Mi dispiace amico, devo andare. Parleremo di quel tuo compagno un'altra volta. Ci vediamo.";
				link.l1.go = "Alcogol_GenQuest_Church_2_6";
			break;
			
		case "Alcogol_GenQuest_Church_2_6":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");			
			string sGenLocation = QuestGetGangLocation(PChar.GenQuest.ChurchQuest_2.QuestTown);
			PChar.GenQuest.ChurchQuest_2.QuestGangJungle = sGenLocation;
			SetFunctionLocationCondition("Church_GenQuest2_GenerateBandits", sGenLocation, false);
			locations[FindLocation(sGenLocation)].DisableEncounters = true;
			PChar.GenQuest.ChurchQuest_2.WayOfShortVariant = true; // Нужно для проверки при убийстве банды
			SetFunctionTimerConditionParam("Church_GenQuest2_TimeIsLeft", 0, 0, 1, MakeInt(24 - GetHour()), false);
			Log_TestInfo("The bandits who raided the church shall be in location - " + sGenLocation + " Time to search for them - 1 day");
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "2");
			break;
		// <-- Церковный генератор. Квест №2
		//--> работорговец
			case "Jamaica_ratH_1":
				dialog.text = "Oh Francois! Certo, ricordo quel tipo... No, non lo so. Ma, sai, potresti chiedere alla nostra cameriera di lui. Per tutto il tempo che ha vissuto qui, ha passato ogni notte con lui. Una sgualdrina è, questo è sicuro. Forse lui ha sparato qualche segreto a lei.";
				link.l1 = "Grazie per il consiglio, amico. Andrò a parlarle.";
				link.l1.go = "exit_sit";
				pchar.questTemp.Slavetrader = "FindRatJamaica_W";
			break;
			
			case "EscapeSlave_Villemstad_H1":
				dialog.text = "Sì, a volte possono succedere cose molto strane in mare aperto. Nel mio ultimo viaggio ho visto qualcosa di dav-vero...";
				link.l1 = "Vai avanti, raccontami, solo non esagerare troppo. Nel frattempo ti prenderò un altro rum.";
				link.l1.go = "EscapeSlave_Villemstad_H2";
			break;
			
			case "EscapeSlave_Villemstad_H2":
				dialog.text = "Giuro a Dio, nobile"+GetSexPhrase("signore","signora")+" - L'ho visto con i miei occhi... Una nave stava navigando, ma invece di marinai c'erano delle gigantesche scimmie... o macachi... scimmie, capisci.";
				link.l1 = "Cosa?! Dimmi, amico, anche tu stai bevendo durante il turno di guardia?";
				link.l1.go = "EscapeSlave_Villemstad_H3";
			break;
			
			case "EscapeSlave_Villemstad_H3":
				dialog.text = "Mi accechi se sto mentendo! Non hai mai sentito parlare del gamberetto scimmia? Accidenti a me, gamberetti ah-ah! ... La nave scimmia.";
				link.l1 = "Che nave di scimmie?";
				link.l1.go = "EscapeSlave_Villemstad_H4";
			break;
			
			case "EscapeSlave_Villemstad_H4":
				dialog.text = "Oh-hoe, dico che l'ho visto con i miei occhi. Faceva tempesta. Non si vedeva un accidente, e poi la nave è apparsa dal nulla. Vele strappate. Aveva la vela di prua spezzata così come la vela maestra, e perbacco e dannazione aveva tutto spezzato! Eppure sfrecciava controvento!\nE c'erano scimmie sul suo ponte... tante come... una colonia di foche! E un vero gorilla stava al timone! Nove piedi, camicia rossa e denti di squalo al posto della croce sul petto... Occhi rossi, zanne lampeggianti, ci ha visti e ha urlato qualcosa...";
				link.l1 = "Stai mentendo spudoratamente, amico. Sai, si possono vedere cose quando si è ubriachi. Dopo mi dirai che era il Olandese Volante.";
				link.l1.go = "EscapeSlave_Villemstad_H5";
			break;
			
			case "EscapeSlave_Villemstad_H5":
				dialog.text = "No, non era olandese. Ti sto dicendo la verità! Era una barca, e sulla poppa c'era un'iscrizione - "+pchar.questTemp.Slavetrader.ShipName+".";
				link.l1 = "Maledizione! Credo di capire di quali 'scimmie' stavi parlando. Infatti, il rum può sciogliere le lingue - basta solo ascoltare...";
				link.l1.go = "EscapeSlave_Villemstad_H6";
			break;
			
			case "EscapeSlave_Villemstad_H6":
				dialog.text = "Vedi - te lo dicevo! E tu non mi credevi!.. Va bene, beviamo un ultimo bicchiere, e sono pronto per andare.";
				link.l1 = "Bene, grazie per una storia interessante. Devo andare. Buona fortuna a te, compagno.";
				link.l1.go = "exit_sit";
				Pchar.quest.Slavetrader_EscapeSlave.win_condition.l1 = "location";
				Pchar.quest.Slavetrader_EscapeSlave.win_condition.l1.location = pchar.questTemp.Slavetrader.Island.Shore;
				Pchar.quest.Slavetrader_EscapeSlave.function = "Slavetrader_EscapeSlaveInShore";
				AddQuestRecord("Slavetrader", "22_4");
				AddQuestUserData("Slavetrader", "sAreal", pchar.questTemp.SlavetraderAreal.add);
				pchar.questTemp.Slavetrader = "FindMayak";
			break;
		
		//Голландский Гамбит, против всех
		case "Lucas_Tavern":
			DelMarkInTavernHWIC();
			dialog.text = "No, capitano. La vita di un marinaio non fa per me. Sai, anch'io avevo una nave una volta, ma... ho avuto un colpo di sfortuna davvero brutto.";
			link.l1 = "Ascolta - Ho visto una nave insolita all'orizzonte - si chiama 'Meifeng'. Non ho mai visto una nave simile prima d'ora. Chi è il proprietario? Forse, è in vendita? Mi piacerebbe darci un'occhiata.";
			link.l1.go = "Lucas_Tavern_1";
		break;
		
		case "Lucas_Tavern_1":
			dialog.text = "Ha! Nemmeno per sogno, capitano. Non credo che il tipo cinese venderà la sua nave a te o a chiunque altro.";
			link.l1 = "Un cinese? Ci sono cinesi a Curacao? E addirittura un capitano della sua stessa nave?";
			link.l1.go = "Lucas_Tavern_2";
		break;
		
		case "Lucas_Tavern_2":
			dialog.text = "C'è, come puoi vedere. Ma questa non è la sua nave, in realtà - appartiene alla Compagnia di Commercio. Dicono, il mio signore Rodenburg, il vice direttore e ora governatore in carica, la possiede.";
			link.l1 = "Allora, Matthias Beck si è ritirato?";
			link.l1.go = "Lucas_Tavern_3";
		break;
		
		case "Lucas_Tavern_3":
			dialog.text = "Ha! Signore, dovresti davvero visitare più spesso la terraferma - o almeno interessarti alle notizie. Matthias Beck è stato licenziato e messo dietro le sbarre fino a quando tutte le circostanze non sono state chiarite.";
			link.l1 = "Non dirlo nemmeno! Infatti, sto passando troppo tempo in mare. E quando è successo questo?";
			link.l1.go = "Lucas_Tavern_4";
		break;
		
		case "Lucas_Tavern_4":
			dialog.text = "Effettivamente, solo un paio di giorni fa. Una brigantina da corriere è arrivata nel porto. Non era nelle migliori condizioni, chiaramente aveva partecipato a un combattimento feroce. Il capitano è andato direttamente dal mio signore Rodenburg con il suo rapporto, e in poche ore Matthias Beck è stato arrestato dal mio signore Rodenburg e dal comandante su sospetto di collaborazione con l'intelligence inglese.";
			link.l1 = "Stai raccontando cose terribili. Come può un governatore di Curacao essere una spia inglese?";
			link.l1.go = "Lucas_Tavern_5";
		break;
		
		case "Lucas_Tavern_5":
			dialog.text = "Sinceramente, anch'io fatico a crederci. Ho sentito dire che presto il direttore della Compagnia, Peter Stuyvesant in persona, arriverà qui. A quanto pare, condurrà personalmente l'indagine.";
			link.l1 = "Allora hai ragione. Può essere rischioso disturbare il mio Rodenburg in questo momento.";
			link.l1.go = "Lucas_Tavern_6";
		break;
		
		case "Lucas_Tavern_6":
			dialog.text = "Buon pensiero, capitano! Tanto più che 'Meifeng' è attualmente in carico. È appena tornata dal viaggio verso la costa meridionale del Main, e presto salperà di nuovo. E, ti dico, lì stanno succedendo cose strane. Marinai olandesi e guardie della Compagnia sono stati sollevati dal dovere, e si sta formando un altro equipaggio. E giuro su tutte le tazze di rum che ho bevuto nella mia vita, quei nuovi volontari sono completamente diversi, tutti pirati, banditi e tagliagole!";
			link.l1 = "Un miracolo, davvero! Peccato! Una nave così bella... Beh, il destino ha deciso diversamente... Grazie per un racconto interessante e per le novità! È stato un piacere parlare con te!";
			link.l1.go = "Lucas_Tavern_7";
		break;
		
		case "Lucas_Tavern_7":
			dialog.text = "Bene, grazie per la compagnia e il rum, capitano! Torna a trovarci quando vuoi!";
			link.l1 = "Certo che lo farò!";
			link.l1.go = "exit_sit";
			AddQuestRecord("Holl_Gambit", "3-44");
			pchar.questTemp.HWIC.Self = "AttackMeifeng";
			//ставим прерывание на выход в море Мейфенг
			pchar.quest.HWIC_Meifeng.win_condition.l1 = "Timer";
			pchar.quest.HWIC_Meifeng.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.HWIC_Meifeng.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.HWIC_Meifeng.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.HWIC_Meifeng.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.HWIC_Meifeng.function = "CreateMeifengOnMap";
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("QuestShipsTerms_Over", 0, 0, 12, false); // таймер
			pchar.quest.Meifeng_fail.over = "yes"; //снять прерывание
			Group_DelCharacter("Meifeng_Empty", "Longway");
			Group_DeleteGroup("Meifeng_Empty");//удалить Мейфенг из порта
		break;
		
			//Jason --> поиск дезертира
		case "FindFugitiveHb":
			npchar.quest.fugitive = "true";
			if (npchar.location == pchar.GenQuest.FindFugitive.City+"_tavern" && sti(pchar.GenQuest.FindFugitive.Chance) == 2)
			{
				pchar.GenQuest.FindFugitive.Shore = SelectQuestShoreLocation();
				dialog.text = "Ah! "+pchar.GenQuest.FindFugitive.Name+"? Lo so, lo so... È molto introverso, quel tuo collega. Un lupo solitario, per così dire. Naviga sulla sua lunga barca lungo la costa dell'isola tutto il giorno fino a notte. La gente pensa che sia un pescatore, ma in realtà è un pescatore di perle... He-he! Lo so per dannatamente certo!";
				link.l1 = "Ehi! Allora... puoi dirmi dove trovarlo?";
				link.l1.go = "FindFugitiveHb_1";
			}
			else
			{
				dialog.text = ""+pchar.GenQuest.FindFugitive.Name+"? No, lo giuro, non ho mai sentito parlare di lui... Ma tu - Hic! Puoi chiedere al nostro barista - lui deve saperlo di sicuro!";
				link.l1 = "Mmm... Va bene, farò qualche altra domanda in giro. Bene, amico, grazie per la compagnia. Ci vediamo!";
				link.l1.go = "exit_sit";
			}
		break;
		
		case "FindFugitiveHb_1":
			dialog.text = "Certo, posso! Ogni mattina lui può essere trovato sulla spiaggia, a "+XI_ConvertString(pchar.GenQuest.FindFugitive.Shore+"Gen")+". Vieni il più presto possibile, altrimenti salperà e dovrai aspettare fino al mattino successivo.";
			link.l1 = "Grazie! Mi hai aiutato molto, amico! Ci vediamo!";
			link.l1.go = "exit_sit";
			pchar.GenQuest.FindFugitive.Chance = 3; // чтобы никто больше не говорил
			AddQuestRecord("MayorsQuestsList", "12-3");
			AddQuestUserData("MayorsQuestsList", "sShore", XI_ConvertString(pchar.GenQuest.FindFugitive.Shore+"Gen"));
			sld = characterFromId("Fugitive");
			LAi_SetWarriorType(sld);
			LAi_warrior_DialogEnable(sld, true);
			sld.dialog.currentnode = "Fugitive_shore";
			LAi_SetLoginTime(sld, 4.0, 6.0);
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.FindFugitive.Shore, "goto", "goto1");
		break;
		//<-- поиск дезертира
		
		// Карибские нравы
		case "trial_spy":
			dialog.text = "Se ne stava in giro nel nostro cantiere navale, chiedendo qua e là agli operai. E questo è ciò che gli ha giocato un brutto tiro. Alcune persone hanno avvertito il comandante su individui sospetti che giravano per la città, così lo hanno detenuto, e poi si è scoperto che in realtà non era affatto un mercante.";
			link.l1 = "Capisco, stava per rubare qualche progetto segreto del tuo costruttore di navi?";
			link.l1.go = "trial_spy_1";
		break;
		
		case "trial_spy_1":
			dialog.text = "Chi lo sa? Ma sono abbastanza sicuro che fosse interessato al galeone 'Alacantara' in primo luogo! Hic! Posso giurarlo! Questa nave viene equipaggiata dal signor governatore in persona, quindi scommetto che quel furfante ha cercato di fiutare qualcosa su di lei.";
			link.l1 = "Ah! È molto probabile. Sicuramente il governatore la caricherà con qualcosa di prezioso...";
			link.l1.go = "trial_spy_2";
		break;
		
		case "trial_spy_2":
			dialog.text = "Questo va senza dire! Dev'essere qualcosa che merita davvero attenzione, te lo dico! Oh, e la gente diceva che i pescatori hanno visto una nave militare straniera in queste acque... probabilmente una fregata. Forse, è da lì che è venuto quella spia?";
			link.l1 = "Sì, può essere... Va bene, amico, grazie per la compagnia, ma devo andare!";
			link.l1.go = "exit_sit";
			pchar.questTemp.Trial = "spy_drink";
			
			if(CheckAttribute(pchar,"questTemp.trialHabitueId"))
			{
				if (GetCharacterIndex(pchar.questTemp.trialHabitueId) != -1)
				{
					sld = characterFromId(pchar.questTemp.trialHabitueId);
					sld.lifeday = 0;
					DeleteAttribute(pchar,"questTemp.trialHabitueId");
					LAi_CharacterDisableDialog(sld);
					DelLandQuestMark(sld);
				}
			}
			// belamour legendary edtion -->
			if (GetCharacterIndex("PortoBello_Poorman") < 0)
			{
				// новый нищий
				sld = GetCharacter(NPC_GenerateCharacter("PortoBello_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, SPAIN, -1, false, "slave"));
				sld.city = "PortoBello";
				sld.location	= "PortoBello_town";
				sld.location.group = "goto";
				sld.location.locator = "goto15";
				sld.forStay.locator = "goto15"; //где генеримся в случае стояния
				sld.forSit.locator0 = "goto3";
				sld.forSit.locator1 = "goto25"; //три локатора, где генеримся в случае сидения
				sld.forSit.locator2 = "goto12";
				LAi_SetLoginTime(sld, 9.0, 21.99);
				sld.Dialog.Filename = "Common_poorman.c";
				LAi_SetPoorType(sld);
				LAi_SetHP(sld, 50.0, 50.0);
				sld.greeting = "poorman_male";
				LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
			}
			sld = characterFromId("PortoBello_Poorman");
			LAi_RemoveLoginTime(sld);
			ChangeCharacterAddressGroup(sld, "Portobello_town", "goto", "goto15");
			AddLandQuestMark(sld, "questmarkmain");
			DelLandQuestMark(characterFromId("portobello_tavernkeeper"));
			// <-- legendary edtion
			AddQuestRecord("Trial", "14");
		break;
		
		case "sit_2":
			Statistic_AddValue(pchar, "TavernDrink", 1);
			AddMoneyToCharacter(pchar, -2);
			//navy --> Alcohol - rum count;
			if(!IsEquipCharacterByArtefact(pchar, "totem_01"))
			{
				if (CheckAttribute(pchar, "questTemp.Rum"))
				{
					pchar.questTemp.Rum = sti(pchar.questTemp.Rum) + 1;
				}
				else pchar.questTemp.Rum = 1;
			}
			else 
			{
				if(CheckAttribute(pchar, "questTemp.Rum")) DeleteAttribute(pchar, "questTemp.Rum");
			}				
			//<-- navy
			if(!CheckAttribute(pchar, "questTemp.TimeLock")) WaitDate("",0,0,0, 0, 30);
			
			if (CheckAttribute(pchar, "questTemp.Rum"))
			{
				DeleteAttribute(pchar, "chr_ai.drunk");
				if (sti(pchar.questTemp.Rum) < 3) LAi_AlcoholSetDrunk(pchar, 51, 5600);
				else
				{
					LAi_AlcoholSetDrunk(pchar, 71, sti(pchar.questTemp.Rum)*2800);
					Pchar.GenQuest.CamShuttle = makeint(sti(pchar.questTemp.Rum)/2); // Jason
				}
			}
			
			// Sinistra - Квест "Путеводная звезда" ==>
			if (CheckAttribute(pchar, "questTemp.PZ_BasTerAlkash") && npchar.city == "baster")
			{
				dialog.text = "Alla tua salute e alla tua generosità!";
				link.l1 = "Compagno, hai visto un tipo cinese in giro per la città?";
				link.l1.go = "PZ_BasTerAlkash_1";
				break;
			}
			// <== Квест "Путеводная звезда" - Sinistra
			
			dialog.text = LinkRandPhrase("Sei un "+GetSexPhrase("vero amico","brava ragazza")+"! Piacere di conoscerti! Alla salute!","Hic! Questo è un ottimo rum! Hic... Salute!","Per la tua salute e per la tua generosità!");
			link.l1 = "Eh, è un rum davvero forte. Va bene, devo andare. Buon divertimento!";
			link.l1.go = "exit_sit";
			if (makeint(pchar.money) >=2)
			{
				link.l2 = "Un'altra tazza, ti dispiace?";
				link.l2.go = "sit_3";
			}

			link.l4 = LinkRandPhrase("Sembra che io abbia trascorso un'eternità in mare. Ci sono novità?","Cosa dicono le persone? Certamente, ti offrirò da bere.","Dimmi, amico, quali storie sono popolari nelle taverne ora?");
			link.l4.go = "rumours_habitue";
		break;

		case "sit_3":
			int iSituation;
			if(IsEquipCharacterByArtefact(pchar, "totem_01")) iSituation = makeint(rand(3));
			else iSituation = makeint(rand(5));
			switch (iSituation)
			{
				case 0:
					dialog.text = "Oh! Una grande idea!";
					link.l1 = "Barista! Ancora rum!";
					link.l1.go = "sit_2";
				break;

				case 1:
					dialog.text = "A te! Oh, dannazione! Chi è quello?";
					link.l1 = "Eh? Cosa? Dove? Devo avere le allucinazioni.";
					link.l1.go = "sit_2";// to_do "sit_case_5_exit";
				break;
				
                case 2:
	         		dialog.text = "Beviamo allora! Un altro?";
					link.l1 = "Vai avanti!";
					link.l1.go = "sit_2";
                break;				
				
				case 3:
					if(rand(1) == 0)
					{
						dialog.text = RandPhraseSimple("Ehi, tu, "+GetAddress_Form(NPChar)+", sicuramente pensi che tutti ti ammirino, vero? Beh, se mi chiedi, sei solo un brigante ordinario!.. E un assassino! 'Pirata nobile'! Ah! Un bandito è un bandito... Hic... Sia sulla terra che in mare..","Hic! "+GetSexPhrase("Sco... Canaglia","Po... Porcheria")+"! Vuoi che beva fino a svenire - hic - e poi ruberai tutti i miei soldi!");
						link.l1 = "Vedo che hai già bevuto abbastanza... Vai a smaltirla... E io devo andare...";
						link.l1.go = "exit_sit";						
						link.l2 = "Non mi piace il tuo tono, amico. Tieni a freno la lingua, capito?";
						link.l2.go = "sit_case_2_enemy";
						link.l3 = "A chi hai appena chiamato bandito, tu terraferma?! Vediamo cosa dirai con un buco nella pancia!";
						link.l3.go = "sit_case_2_enemy2";
					link.l4 = "Calmati! Hai dimenticato? Sono il tuo unico vero amico!";
					link.l4.go = "sit_case_2_friend";		
					}
					else
					{
						// Captain Beltrop, 27.06.21, новый вариант
						/* if (rand(1) == 0)
						{
							Diag.CurrentNode = Diag.TempNode;
							AddDialogExitQuestFunction("Tavern_SetBadHabitue");
							DialogExit();
						}
						else
						{ */
							dialog.text = RandPhraseSimple("Perché mi stai fissando? Aspetterai che svenisca - hic - e poi mi ruberai tutto il mio denaro! Da dove è spuntata tutta questa canaglia?! Hic... Non c'è posto per una persona decente in questa taverna?","Mi rispetti?.. Sì, tu! Mi rispetti?! Stai attento... Non sono uno con cui giocare... Un colpo tra gli occhi... E sei praticamente morto...");
							link.l1 = "Compagno, sei ubriaco come un porco. Vai a casa e dormi... E devo andare anch'io...";	
							link.l1.go = "exit_sit";
							link.l2 = "Frena i tuoi cavalli, compagno. Fai attenzione a chi stai parlando.";
							link.l2.go = "sit_case_2_enemy1";
							link.l3 = "Cosa hai appena detto?! Ti darò una lezione!";
							link.l3.go = "sit_case_2_enemy2";
							link.l4 = "Calmati! Mi hai dimenticato? Sono il tuo unico vero amico!";
							link.l4.go = "sit_case_2_friend";	
						//}
					}
				break;

				case 4:
					dialog.text = "Ascolta! Sei un bravo uomo! Forse, mi aiuterai... con un affare?";
					link.l1 = "No, credo di dover andare ora.";
					link.l1.go = "exit_sit";
					link.l2 = "Certo! Hic! Siamo amici... non siamo? Hic!";
					link.l2.go = "sit_case_3";
				break;

				case 5:
					if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > rand(110) )
					{
						dialog.text = "...E poi ho c-catturato la sua sciabola per la l-lama...";
						link.l1 = "...e poi ha detto...";
						link.l1.go = "sit_2";
					}
					else
					{
						dialog.text = "...E poi ho a-agganciato la sua spada per la l-lama...";
						link.l1 = "...hic! ...e poi lei ha detto...";
						link.l1.go = "sit_case_4_exit";
					}
				break;
			}
		break;

		case "sit_case_5_exit": // дуэль
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("fighting");
		break;

		case "sit_case_4_exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.questTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("without_memory");
		break;

		case "sit_case_3":
			dialog.snd = "Voice\HADI\HADI037";
			dialog.text = "Il p-punto è che uno dei s-soldati mi ha insultato. Q-Questo è!";
			link.l1 = "Un s-soldato? N-No, credo che passerò.";
			link.l1.go = "exit_sit";
			link.l2 = "Calmati! Mi hai dimenticato? Sono il tuo unico vero amico!";
			link.l2.go = "sit_2";
		break;

		case "sit_case_2_friend":
			dialog.snd = "Voice\HADI\HADI038";
			dialog.text = "Tu? Che tipo di amico sei tu? N-no! Tu... tu vuoi uccidermi! E-Ecco cos'è!";
			link.l1 = "Ebbene, certamente hai già bevuto abbastanza. Addio.";
			link.l1.go = "exit_sit";
			link.l2 = "Cosa? Ti dimostrerò che non ho intenzione di ucciderti! Io... Io ti taglierò la mano!... Senza... essa non potrai essere ucciso!... Hic!";
			link.l2.go = "sit_case_2_friend_2";
		break;

		case "sit_case_2_friend_2":
			dialog.snd = "Voice\HADI\HADI039";
			dialog.text = "Aaaah! Prendi "+GetSexPhrase("lui","lei")+" via da me!";
			link.l1 = "Calmati... hic... Non farà male!... È meno doloroso di una rasatura!";
			link.l1.go = "tavern_keeper";
		break;

		case "sit_case_2_enemy":
			dialog.snd = "Voice\HADI\HADI040";
			dialog.text = "Non cercare di intimidirmi! Hic! Non mi spavento così facilmente!.. E tu - dovresti essere impiccato alla forca... Con tutti della tua specie - hic! Puoi gonfiare le tue piume quanto vuoi - ma puzzi ancora di pesce marcio! E non starò a guardare la mia lingua quando - hic! - parlo con la tua specie! Mi fate tutti schifo!";
			link.l1 = "Argh, perché sto parlando con un ubriacone del genere comunque... Credo che andrò a prendermi un sospiro d'aria fresca...";
			link.l1.go = "exit_sit1";
			link.l2 = "Sei troppo audace, amico. Ti farò ingoiare le tue stesse parole!";
			link.l2.go = "sit_case_2_enemy3";
		break;

		case "sit_case_2_enemy1":		
			dialog.snd = "Voice\HADI\HADI040";
			dialog.text = "Cosa?! Ti strangolerò con le mie stesse mani! Hic... Nessuno è sfuggito a me - hic! - fino ad ora!";
			link.l1 = "Non sei un maiale ubriaco? Per rovinare una serata così bella... Va bene, vai a catturare i tuoi scarafaggi - e io me ne vado da qui.";
			link.l1.go = "exit_sit1";
			link.l2 = RandSwear()+"Vedo che non hai intenzione di calmarti. Beh, allora è ora di una lezione di buone maniere.";
			link.l2.go = "sit_case_2_enemy3";
		break;
		
		case "sit_case_2_enemy2":	
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			if(rand(1) == 0)
			{
				dialog.text = LinkRandPhrase("Avvicinati, te mascalzone! Riceverai ciò che meriti!",RandSwear()+"Ti darò quello che meriti!","Ha! Bene, cane di mare - vediamo come te la cavi sulla terraferma!");
				link.l1 = RandPhraseSimple(RandPhraseSimple("Giuro che te ne pentirai!","Accorcerò la tua lingua sporca fino alle orecchie!"),RandPhraseSimple("Ti squarterò come un maiale, dal tuo sedere verso quel cesso che alcuni chiamano bocca!","Giuro che ti farò stare zitto!"));
				link.l1.go = "fight_right_now";
			}
			else
			{
				dialog.text = "Ehi, ragazzi! Diamo una bella pulita a questa spazzatura dalla nostra città!";
				link.l1 = RandPhraseSimple(RandSwear()+"Dite le vostre preghiere, bastardi!","Oh, quindi non sei solo?! Beh, buon per te - avrai compagnia all'inferno!");
				link.l1.go = "fight_right_now_1";
			}
		break;
		
		case "sit_case_2_enemy3":	
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			if(rand(1) == 0)
			{
				dialog.text = LinkRandPhrase("Avvicinati, mascalzone! Riceverai ciò che meriti!",RandSwear()+"Ti darò ciò che meriti!","Ha! Va bene, cane di mare - vediamo come te la caverai sulla terraferma!");
				link.l1 = RandPhraseSimple(RandPhraseSimple("Ti giuro che te ne pentirai!","Accorcerò la tua lingua sporca fino alle orecchie!"),RandPhraseSimple("Ti squarterò come un maiale, dal tuo sedere fino a quella fogna che alcuni chiamano bocca!","Giuro che ti farò stare zitto!"));
				link.l1.go = "fight_right_now";
			}
			else
			{
				dialog.text = "Ehi, ragazzi! Spazziamo via questa spazzatura dalla nostra città!";
				link.l1 = RandPhraseSimple(RandSwear()+"Recitate le vostre preghiere, bastardi!","Oh, quindi non sei solo?! Beh, buono per te - avrai compagnia all'inferno!");
				link.l1.go = "fight_right_now_1";
			}
		break;		
		
		case "exit_sit":			
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");
		break;

		case "exit_sit1":
			ChangeCharacterComplexReputationToNeutral(pchar,"nobility", 2.0);			
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");
		break;
				
		case "tavern_keeper":			
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("tavern_keeper");
		break;
		
		// Captain Beltrop, 27.06.21, новый вариант
		case "bad_habitue":
			dialog.text = "Ehi, non ho capito qualcosa! Non appena ho girato l'angolo, qualche nuovo pivello è sbarcato al mio posto. Fuori da qui!";
			link.l1 = "È sempre così: appena ti siedi al tavolo scopri che è già occupato... Tieni pure il tuo posto, stavo per andarmene comunque.";
			link.l1.go = "bad_habitue1";
			link.l2 = "Un'altra frase come quella dalla tua bocca sporca e sarà l'ultima cosa che dirai nella tua vita, capisci?";
			link.l2.go = "bad_habitue2";
			link.l3 = "Non so se questo era davvero il tuo posto, ma non ti permetterò di parlare con me in quel modo. Guarda le tue parole.";
			link.l3.go = "bad_habitue3";
		break;
		
		case "bad_habitue1":
			DialogExit();
			pchar.questTemp.BadHabitueSit = true; // атрибут усаживания
			AddDialogExitQuest("exit_sit");
		break;
		
		case "bad_habitue2":
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			if(rand(1) == 0)
			{
				dialog.text = LinkRandPhrase("Andiamo, canaglie! Sta per arrivare la vostra dose!",RandSwear()+"Adesso ti spoglierò come si deve!","Ha! Dai, marinaio - vediamo cosa sai fare sulla terraferma!");
				link.l1 = RandPhraseSimple(RandPhraseSimple("Giuro che te ne pentirai!","Ti taglierò quella maledetta lingua!"),RandPhraseSimple("Ti squarterò come un maiale, dal tuo sedere fino a quel buco che alcuni chiamano bocca!","Giuro che ti farò chiudere quella bocca!"));
				link.l1.go = "fight_right_now";
			}
			else
			{
				dialog.text = "Andiamo, ragazzi! Dobbiamo liberare la nostra città da questa spina nel fianco!";
				link.l1 = RandPhraseSimple(RandSwear()+"Pregate, bastardi!","Oh, non sei solo! Beh, avrai compagnia all'inferno!");
				link.l1.go = "fight_right_now_1";
			}
		break;
		
		case "bad_habitue3":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			if(rand(1) == 0)
			{
				dialog.text = LinkRandPhrase("Andiamo, canaglie! State per avere la vostra dose!",RandSwear()+"Ora ti spoglierò come si deve!","Ha! Dai, marinaio - vediamo cosa sai fare sulla terraferma!");
				link.l1 = RandPhraseSimple(RandPhraseSimple("Ti giuro che te ne pentirai!","Ti taglierò quella maledetta lingua!"),RandPhraseSimple("Ti squarterò come un maiale, dal tuo culo verso quel cloaca che alcuni chiamano bocca!","Giuro che ti farò chiudere il becco!"));
				link.l1.go = "fight_right_now";
			}
			else
			{
				dialog.text = "Andiamo ragazzi! Liberiamo questa città da questa peste!";
				link.l1 = RandPhraseSimple(RandSwear()+"Pregate, maledetti!","Oh, non sei solo! Beh, avrai compagnia all'inferno!");
				link.l1.go = "fight_right_now_1";
			}
		break;
		
		//--> Sinistra Длинные тени старых грехов
		case "DTSG_NightIskat":
			dialog.text = "C-certo, tutti noi ci conosciamo! Perché chiedi?";
            link.l1 = "Volevo visitare il prestanome e ho scoperto che ha venduto la sua vecchia casa. Sai dove vive ora?";
            link.l1.go = "DTSG_NightIskat_2";
		break;
		
		case "DTSG_NightIskat_2":
			dialog.text = "Perché hai bisogno di lui a quest'ora, hic? Basta visitare la banca la mattina!";
            link.l1 = "Ho bisogno di soldi urgentemente. Lascia che il sacco di denaro lavori per un cambiamento! Il loro tipo ci chiama sempre parassiti che solo mendicano, si lamentano e non restituiscono mai ciò che dobbiamo.";
            link.l1.go = "DTSG_NightIskat_3";
		break;
		
		case "DTSG_NightIskat_3":
			dialog.text = "Ha-ha-ha, hic, sì, lascialo lavorare! Sai dove viveva il nostro glorioso capitano Fleetwood?";
            link.l1 = "Certo, chi non conosceva Richard. Ora lì vive il banchiere?";
            link.l1.go = "DTSG_NightIskat_4";
		break;
		
		case "DTSG_NightIskat_4":
			dialog.text = "Hai ragione. Quando ci sei, amico - digli che si è montato la testa.";
            link.l1 = "Eh-eh, farò sicuramente quello. Addio.";
            link.l1.go = "DTSG_NightIskat_5";
		break;
		
		case "DTSG_NightIskat_5":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DTSG_NightIskat");
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuest("exit_sit");
			
			chrDisableReloadToLocation = true;
			sld = CharacterFromID("Knippel");
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Knippel_SluhSmertFleetWood";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		//<-- Длинные тени старых грехов
		
		//--> Путеводная звезда
		case "PZ_BasTerAlkash_1":
			dialog.text = "Ha-ha-ha, ho visto un cinese? L'abbiamo visto tutti!";
			link.l1 = "Cosa c'è di così divertente? Non sto parlando di un circo itinerante, se è quello che intendi. Sto parlando di un combattente, un ufficiale di marina.";
			link.l1.go = "PZ_BasTerAlkash_2";
		break;
		
		case "PZ_BasTerAlkash_2":
			dialog.text = "Ah, capisco cosa intendi! Già, l'ho visto. Anche dopo essermi rimesso in sesto, non potevo smettere di vederlo... Non riesco a dimenticarlo!";
			link.l1 = "È interessante. Continua. Facciamo un altro brindisi - probabilmente stai bevendo adesso per dimenticare tutto. Dimmi cosa hai visto prima di farlo.";
			link.l1.go = "PZ_BasTerAlkash_3";
		break;
		
		case "PZ_BasTerAlkash_3":
			dialog.text = "Un circo viaggiante, un bel niente! Saltava, girava, e faceva roteare quella sciabola - non ho mai visto nessuno così abile e terrificante con un'arma.";
			link.l1 = "Sembra proprio lui. Con chi stava combattendo? Te lo ricordi?";
			link.l1.go = "PZ_BasTerAlkash_4";
		break;
		
		case "PZ_BasTerAlkash_4":
			dialog.text = "Le guardie, compagno! Sta anche strizzando gli occhi a loro! Anche se, credo che lui sembri sempre così. Cosa ne pensi?";
			link.l1 = "Non lo so, amico. Continua. Pensavano che fosse una spia? Perché le guardie lo hanno attaccato?";
			link.l1.go = "PZ_BasTerAlkash_5";
		break;
		
		case "PZ_BasTerAlkash_5":
			dialog.text = "Chissà? Stavano cercando di capire cosa stesse facendo in città...";
			link.l1 = "Allora, l'hanno arrestato? O...";
			link.l1.go = "PZ_BasTerAlkash_6";
		break;
		
		case "PZ_BasTerAlkash_6":
			dialog.text = "Ah, che illusione! Non sono riusciti a prenderlo. Ha abbattuto le guardie in città e si è rifugiato nella giungla. Hanno mandato diversi gruppi alla sua ricerca, ma nessuno è tornato. Riesci a immaginare? Ha trasformato quella grotta in una vera fortezza!";
			link.l1 = "È qualcosa. Riposati e cerca di dimenticarlo. Credo che andrò ora - mi gira la testa.";
			link.l1.go = "PZ_BasTerAlkash_7";
		break;
		
		case "PZ_BasTerAlkash_7":
			DialogExit();
			bDisableLandEncounters = true;
			DeleteAttribute(pchar, "questTemp.PZ_BasTerTavern");
			DeleteAttribute(pchar, "questTemp.PZ_BasTerAlkash");
			pchar.questTemp.PZ_BasTerAlkash2 = true;
			DeleteQuestCondition("PZ_BasTer_Opozdal");
			pchar.questTemp.PZ_BasTerTurma = true;
			AddLandQuestMarkToPhantom("baster_prison", "basterJailOff");
			DelMapQuestMarkIsland("Guadeloupe");
			AddQuestRecord("PZ", "3");
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuest("exit_sit");
			
			PChar.quest.PZ_BasTerPeshera.win_condition.l1 = "location";
			PChar.quest.PZ_BasTerPeshera.win_condition.l1.location = "Guadeloupe_CaveEntrance";
			PChar.quest.PZ_BasTerPeshera.win_condition = "PZ_BasTerPeshera";
			
			LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", false);
			LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", false);
			//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", false);
		break;
		
		case "Sotta1":
			dialog.text = "Non l'ho visto personalmente - è stato attorno all'ufficio del governatore, eh! Ma il suo equipaggio ha fatto una gran festa qui.";
			link.l1 = "È così?";
			link.l1.go = "Sotta2";
		break;
		
		case "Sotta2":
			dialog.text = "Tutti dicono che sia un mercante. Ma il suo equipaggio non sembrava la feccia da taverna, te lo dico! Avevano un'aria come se... come se... qual è la parola...?";
			link.l1 = "Capisco. Grazie per la compagnia, amico. Stai tranquillo.";
			link.l1.go = "exit_sit";
			
			npchar.questTemp.Sotta = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Lutter1":
			dialog.text = "Sto festeggiando! E chi dice che sono solo? Sei qui, compagno! E per quanto riguarda Matt, era destinato a succedere prima o poi.";
			link.l1 = "Cosa ti fa dire questo? Ho sentito dire che era un pirata incredibilmente fortunato, favorito dalla Fortuna per anni!";
			link.l1.go = "Lutter2";
		break;
		
		case "Lutter2":
			dialog.text = "Eh, non era solo Fortuna, eh! Era un pirata solitario, non un membro della Fratellanza! E quelli non durano a lungo... Anche se, ho sentito dire che una volta era sotto l'ala di Levasseur.";
			link.l1 = "Giusto, i solitari non durano a lungo. Bene, festeggia. Devo andare, compagno.";
			link.l1.go = "exit_sit";
			
			npchar.questTemp.Lutter = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Sepp1":
			dialog.text = "Eek, sì, n-no, non l'ho mai visto. Chi è?";
			link.l1 = "È il capitano di una delle navi più veloci dell'Arcipelago, la brigantina 'Banten'. Ne hai sentito parlare?";
			link.l1.go = "Sepp2";
		break;
		
		case "Sepp2":
			pchar.questTemp.PZ.TortugaHabitueblock = true;
			
			dialog.text = "Eh, no, non mi interessano le navi, amico, eek! Ne prendiamo un'altra tazza?";
			link.l1 = "Non per me. Comunque non ho ottenuto quello che volevo qui.";
			link.l1.go = "exit_sit";
		break;
		//<-- Путеводная звезда
		
	}
}

bool CheckFreeSitFront(ref _npchar)
{
 	ref rCharacter; //ищем
	int n;

	if (!CheckAttribute(_npchar, "Default.ToLocator")) return false;
	
	for (n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter, Characters[n]);
		if (CheckAttribute(rCharacter, "location") && rCharacter.location == _npchar.location)
		{
            if (rCharacter.location.locator == _npchar.Default.ToLocator)
                return  false;
		}
    }
    return  true;
}

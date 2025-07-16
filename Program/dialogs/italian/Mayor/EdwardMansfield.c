// Эдвард Мэнсфилд, глава буканьеров и авторитетный пират, английская линейка
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
    
// ============================================================================
// ============================= блок angry ==========>>>>>>>>>>>>>>>>>>>>>>>>>
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
                break;
            }
        }
    }
// <<<<<<<<<<<<<<<<<<<<<<======= блок angry ===================================
// ============================================================================
	switch(Dialog.CurrentNode)
	{
		case "First time":
            NextDiag.TempNode = "First time";
            if (CheckAttribute(npchar, "Sp5LaVegaAttackDone"))
            {
            	if (NPChar.quest.meeting == "0")
				{
					dialog.Text = TimeGreeting()+"! Io sono "+GetFullName(NPChar)+", il nuovo governatore di questa fossa. Non sarà facile mettere ordine tra i teppisti locali, ma non rappresentano più una minaccia per le colonie spagnole.";
					Link.l1 = "Sono lieto di incontrarti. Sono il capitano "+GetFullName(Pchar)+". Scusa, ma dovrei andare.";
					Link.l1.go = "exit";
					NPChar.quest.meeting = "1";
				}
				else
				{
					dialog.Text = TimeGreeting()+". Sono occupato, davvero occupato, devo controllare i teppisti locali per prevenire qualsiasi minaccia alle colonie spagnole.";
					Link.l1 = "Non ti disturberò allora.";
					Link.l1.go = "exit";
				}
            }
            else
            {
				dialog.text = NPCStringReactionRepeat("Hai qualcosa da dirmi? No? Allora "+GetSexPhrase("vattene da qui!","Ti chiedo di non disturbarmi.")+"","Credo di essere stato chiaro...","Anche se mi sono spiegato chiaramente, continui a infastidirmi!","Beh, sei oltre ogni misura "+GetSexPhrase("troppo maleducato, mon cheri","una tale scortesia, ragazza","una tale mancanza di rispetto, ragazza")+"...","ripeti",30,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Me ne sto andando.","Sì, "+npchar.name+", vedo questo.","Mi dispiace, "+npchar.name+"...","Ahi...",npchar,Dialog.CurrentNode);
				link.l1.go = "exit";
			}


					if (npchar.city == sti(pchar.HeroParam.Location))
					{
						if(!CheckAttribute(PChar, "questTemp.pirateStartQuest"))
						{
							link.l2 = "Hai qualche lavoro per me?";
							link.l2.go = "pirateStartQuest";
						}
						else
						{
							if(pchar.questTemp.pirateStartQuest == "3" && !CheckAttribute(PChar, "questTemp.pirateStartQuest.many"))
							{
								link.l2 = "Ho trovato la pista, ma ho bisogno di qualche moneta - 30.000 pesos per attirare il ratto fuori dalla sua tana.";
								link.l2.go = "pirateStartQuest_many";	
							}
							if(pchar.questTemp.pirateStartQuest == "3" && GetCharacterItem(pchar, "letter_open") > 0)
							{
								link.l2 = "Ecco, guarda questa lettera che ho trovato sul cadavere del contrabbandiere";
								link.l2.go = "pirateStartQuest_info_1";	
							}
							if(pchar.questTemp.pirateStartQuest == "5")
							{
								link.l2 = "È fatto. Norman Vigo e la sua nave appartengono al diavolo del mare.";
								link.l2.go = "pirateStartQuest_final";	
							}
						}
					}
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		//zagolski. начальный квест за пирата ===================================
		case "pirateStartQuest":
			dialog.text = "Hm.. Lavoro, hai detto? In realtà, è bene che tu mi abbia chiesto. Ho bisogno di un uomo dall'esterno. Voglio scoprire qualcosa nella città più vicina ma i miei uomini sono conosciuti lì. Non posso prometterti molto ma otterrai qualcosa.";
			link.l1 = "Qual è la missione?";
			link.l1.go = "pirateStartQuest_1";
			link.l2 = "Mi dispiace, ma non correrò il rischio per qualche briciola. Addio.";
			link.l2.go = "exit";
			pchar.questTemp.pirateStartQuest = "0";
		break;
		case "pirateStartQuest_1":
			dialog.text = "Allora ascolta, avevo un accordo per consegnare 200 schiavi un mese fa con il capitano dello schooner 'Saintblue'. Volevo venderli al proprietario della piantagione locale. Il tempo è passato e il cliente ha iniziato a preoccuparsi, ma ieri mi è stato detto che lo schooner è stato visto non lontano dall'isola. Ma! Il capitano non si è presentato. Oggi, il mio cliente mi ha chiesto di restituire il suo anticipo e ha detto che gli è stato offerto di comprare schiavi da un altro venditore. Più costoso, ma tutta la manciata di schiavi in una volta.";
			link.l1 = "E quindi? Devo trovare 200 schiavi in pochi giorni per salvarti da una perdita di anticipo? Per pochi soldi?";
			link.l1.go = "pirateStartQuest_2";
		break;
		case "pirateStartQuest_2":
			dialog.text = "Certo che no. Sembro forse un idiota? Comunque non gli restituirò l'anticipo. Ma ho bisogno di prova che quegli schiavi che gli sono stati offerti sono miei. Trova coloro che gli hanno proposto un nuovo affare e riceverai i tuoi 10.000 pesos. Affare?";
			link.l1 = "Sono dentro. Hai qualche sospetto su chi potrebbe essere?";
			link.l1.go = "pirateStartQuest_3";
			link.l2 = "Non c'è speranza. Cerca qualcun altro, solo per 10.000? Mi dispiace ma non funzionerà.";
			link.l2.go = "exit";
		break;
		case "pirateStartQuest_3":
			dialog.text = "Se avessi avuto delle idee, non avrei mai utilizzato i tuoi servizi. Quegli uomini sarebbero già morti. Ma sono desideroso di sapere come hanno scoperto del carico della 'Saintblue' e del mio cliente. Sembra che sia stato abbastanza facile per loro. Vedi ora?";
			link.l1 = "Sì, qualcuno ti ha tradito.";
			link.l1.go = "pirateStartQuest_4";

			pchar.questTemp.pirateStartQuest = "1";
			pchar.questTemp.pirateStartQuest.City = npchar.city;
			pchar.questTemp.pirateStartQuest.Areal = GetArealByCityName(pchar.questTemp.pirateStartQuest.City);
			pchar.questTemp.pirateStartQuest.Name = GetFullName(npchar);

			AddQuestRecord("pSQ", "1");
			AddQuestUserData("pSQ", "sCity", XI_ConvertString("Colony" + pchar.questTemp.pirateStartQuest.City + "Gen"));
			AddQuestUserData("pSQ", "sName", pchar.questTemp.pirateStartQuest.Name);
		break;
		case "pirateStartQuest_4":
			dialog.text = "Esatto! Lo sto cercando. Uccidere i miei concorrenti e riportare i miei schiavi non sono la tua priorità. Ho bisogno di quel ratto, in realtà la sua testa su uno spiedo per essere onesti. Vedi ora, perché i miei uomini non dovrebbero sapere nulla della tua missione? Sospetterò di tutti fino a quando non scoprirò chi vende le informazioni. E in realtà non lo voglio proprio...";
			link.l1 = "Capisco. Allora manterrò un profilo basso. Sono sulla mia strada.";
			link.l1.go = "exit";
		break;

		case "pirateStartQuest_many":
			dialog.text = "Trentamila dici? È una somma considerevole... Posso darti solo 5.000 pesos, è tutto quello che ho ora. E non provare nemmeno a scappare con i soldi o ti troverò e ti impiccherò alla recinzione più vicina! Capito?";
			link.l1 = "Bene, allora dammi cinquemila...";
			link.l1.go = "pirateStartQuest_many_1";
		break;
		case "pirateStartQuest_many_1":
			dialog.text = "Prendilo. Sto aspettando il risultato della tua ricerca.";
			link.l1 = "Andrà tutto bene.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 5000);
			pchar.questTemp.pirateStartQuest.many = "";
		break;

		//------------------------------------
		case "pirateStartQuest_info_1":
			dialog.text = "Ha! Notizie eccellenti! Ero sicuro che ce l'avresti fatta. Ho delle informazioni intriganti.";
			link.l1 = "Ho fatto il mio lavoro e voglio avere i miei diecimila.";
			link.l1.go = "pirateStartQuest_info_2";
			TakeItemFromCharacter(pchar, "letter_open");
		break;
		case "pirateStartQuest_info_2":
			dialog.text = "Certo, ecco la tua ricompensa. Ma non scappare, ho un altro incarico per te.\nPfaifer è un membro dell'equipaggio di Norman Vigo del luggar 'Septima'. Sono sicuro che Norman Vigo è il ratto, anche se è uno di noi. È stato visto recentemente nelle acque dell'isola. Il tuo compito è mandare questo ratto al diavolo del mare. Non mi hai deluso la prima volta, quindi voglio chiederti di occuparti anche di questo. Ti pagherò 15.000 pesos. Affare?";
			link.l1 = "Sono su di esso! Considera il traditore morto.";
			link.l1.go = "pirateStartQuest_info_3";
			link.l2 = "Sai, non voglio partecipare... Non ho tempo comunque. Mi dispiace, ma me ne vado.";
			link.l2.go = "pirateStartQuest_info_noex";
			AddMoneyToCharacter(pchar, 10000);
		break;
		case "pirateStartQuest_info_noex":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.pirateStartQuest = "0";
			CloseQuestHeader("pSQ");
		break;
		case "pirateStartQuest_info_3":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.pirateStartQuest = "4";

			AddQuestRecord("pSQ", "7");
			AddQuestUserData("pSQ", "sName", pchar.questTemp.pirateStartQuest.Name);

			pchar.quest.zpq_seaBattle.win_condition.l1 = "location";
			pchar.quest.zpq_seaBattle.win_condition.l1.location = pchar.questTemp.pirateStartQuest.Areal;
			pchar.quest.zpq_seaBattle.function = "pirateStartQuest_seaBattle";
		break;

		case "pirateStartQuest_final":
			dialog.text = "Lo so, lo so. I miei uomini hanno assistito alla battaglia e mi hanno già riferito della tua vittoria impeccabile. Bene, hai fatto bene il tuo lavoro. Ecco 15.000 pesos, come promesso. E grazie, mi hai aiutato molto.";
			link.l1 = "Va bene, sono stato felice di aiutare! Ma devo andare ora, sono stato qui troppo a lungo e ho molte cose da fare. Addio!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 15000);
			pchar.questTemp.pirateStartQuest = "0";
			CloseQuestHeader("pSQ");
			group_DeleteGroup("pirateStartQuest_Smuggler_group");
		break;
				
 		case "No_Mansfield_first_time":
			dialog.text = "Saluti, mi chiamo Alistair Good. Sono stato eletto capo dei bucanieri dopo la morte di Mansfield.";
			link.l1 = "È un piacere conoscerti, Alistair.";
			link.l1.go = "exit";
			NextDiag.TempNode = "No_Mansfield";
  		break;
 		case "No_Mansfield":
			dialog.text = "Non ho tempo per parlare con te. Vieni a trovarmi più tardi.";
			link.l1 = "Sto già andando via.";
			link.l1.go = "exit";
  		break;
		

// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple(""+GetSexPhrase("Prendi","Prendi")+" fuori!","Vattene dalla mia casa!");
			link.l1 = "Ops...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся с Мэнсфилдом через 30 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Non disturbarmi, ricorda questo.";
        			link.l1 = "Ce l'ho fatta.";
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
            DoReloadCharacterToLocation("LaVega_town","reload","reload6");
		break;
// <<<<<<<<<<<<============= блок нод angry =============================
	}
}

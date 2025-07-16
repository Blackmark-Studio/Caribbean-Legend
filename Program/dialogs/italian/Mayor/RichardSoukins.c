// Соукинс в Пуэрто-Принсипе
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
            dialog.text = "Hai qualche affare con me? No? Allora vai via!";
			link.l1 = "Sto già andando via.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";


					if (npchar.city == sti(pchar.HeroParam.Location))
					{
						if(!CheckAttribute(PChar, "questTemp.pirateStartQuest"))
						{
							link.l2 = "Avete qualche lavoro per me?";
							link.l2.go = "pirateStartQuest";
						}
						else
						{
							if(pchar.questTemp.pirateStartQuest == "3" && !CheckAttribute(PChar, "questTemp.pirateStartQuest.many"))
							{
								link.l2 = "Ho raccolto la traccia, ma ho bisogno di alcune monete - 30.000 pesos per attirare il ratto fuori dal suo buco.";
								link.l2.go = "pirateStartQuest_many";	
							}
							if(pchar.questTemp.pirateStartQuest == "3" && GetCharacterItem(pchar, "letter_open") > 0)
							{
								link.l2 = "Ecco, guarda questa lettera che ho trovato sul cadavere del contrabbandiere";
								link.l2.go = "pirateStartQuest_info_1";	
							}
							if(pchar.questTemp.pirateStartQuest == "5")
							{
								link.l2 = "È fatto. Norman Vigo e la sua nave sono andati al diavolo del mare.";
								link.l2.go = "pirateStartQuest_final";	
							}
						}
					}
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		//zagolski. начальный квест за пирата ===================================
		case "pirateStartQuest":
			dialog.text = "Mh... lavoro, hai detto? In realtà è bene che tu mi abbia chiesto. Ho bisogno di un uomo dall'esterno. Voglio scoprire qualcosa nella città più vicina ma i miei uomini sono conosciuti lì. Non posso prometterti molto ma otterrai qualcosa.";
			link.l1 = "Bene! Qual è la missione?";
			link.l1.go = "pirateStartQuest_1";
			link.l2 = "Mi dispiace, ma non rischierò per qualche spicciolo. Addio.";
			link.l2.go = "exit";
			pchar.questTemp.pirateStartQuest = "0";
		break;
		case "pirateStartQuest_1":
			dialog.text = "Allora ascolta, avevo un accordo per consegnare 200 schiavi un mese fa con il capitano dello schooner 'Saintblue'. Volevo venderli al proprietario della piantagione locale. Il tempo è passato e il cliente ha iniziato a preoccuparsi, ma ieri mi è stato detto che lo schooner è stato visto non lontano dall'isola. Ma! Il capitano non si è presentato. Oggi, il mio cliente mi ha chiesto di restituire il suo anticipo e ha detto che gli è stato offerto di comprare schiavi da un altro venditore. Più costoso, ma tutto il gruppo di schiavi e subito.";
			link.l1 = "E allora? Devo trovare 200 schiavi in pochi giorni per salvarti da una perdita di anticipo? Per poche monete?";
			link.l1.go = "pirateStartQuest_2";
		break;
		case "pirateStartQuest_2":
			dialog.text = "Certo che no. Sembro un idiota? Non gli restituirò comunque il suo anticipo. Ma ho bisogno di una prova che quegli schiavi che gli sono stati offerti sono miei. Trova coloro che gli hanno offerto un nuovo accordo e otterrai i tuoi 10.000 pesos. Affare?";
			link.l1 = "Sono dentro. Hai qualche sospetto? Chi potrebbe averlo fatto?";
			link.l1.go = "pirateStartQuest_3";
			link.l2 = "Non c'è speranza. Cerca qualcun altro. Solo per 10.000? Mi dispiace ma non funzionerà.";
			link.l2.go = "exit";
		break;
		case "pirateStartQuest_3":
			dialog.text = "Se avessi avuto delle idee, non avrei mai utilizzato i tuoi servizi. Quegli uomini sarebbero già morti. Ma sono ansioso di sapere come hanno scoperto del carico della 'Saintblue' e del mio cliente. Sembra che per loro sia stato abbastanza facile. Vedi ora?";
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
			dialog.text = "Esatto! Lo sto cercando. Uccidere i miei concorrenti e riportare i miei schiavi non sono la tua priorità. Ho bisogno di quel ratto, in realtà della sua testa infilzata su uno spiedo per essere onesto. Vedi ora, perché i miei uomini non dovrebbero sapere nulla della tua missione? Sospetterò di tutti fino a quando non scoprirò chi vende le informazioni. E non voglio davvero che accada...";
			link.l1 = "Capisco. Allora manterrò un profilo basso. Sono sulla mia strada.";
			link.l1.go = "exit";
		break;

		case "pirateStartQuest_many":
			dialog.text = "Trentamila dici? È una somma grande... Posso darti solo 5.000 pesos, è tutto quello che ho adesso. E non pensare nemmeno di scappare con i soldi o ti troverò e ti impiccherò sulla recinzione più vicina! Capito?";
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
			dialog.text = "Ah! Ottima notizia! Ero sicuro che ce l'avresti fatta. Ho delle informazioni intriganti.";
			link.l1 = "Ho fatto il mio lavoro e voglio avere i miei diecimila.";
			link.l1.go = "pirateStartQuest_info_2";
			TakeItemFromCharacter(pchar, "letter_open");
		break;
		case "pirateStartQuest_info_2":
			dialog.text = "Certo, ecco la tua ricompensa. Ma non scappare, ho un altro incarico per te.\nPfaifer è un membro dell'equipaggio di Norman Vigo del lugger 'Septima'. Sono sicuro che Norman Vigo è il ratto, anche se è uno di noi. È stato recentemente visto nelle acque dell'isola. Il tuo lavoro è mandare questo ratto al diavolo del mare. Non mi hai deluso la prima volta, quindi voglio chiederti di occuparti anche di questa faccenda. Ti pagherò 15.000 pesos. Affare fatto?";
			link.l1 = "Sono su di esso! Considera il traditore Norman Vigo morto.";
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
			dialog.text = "Lo so, lo so. I miei uomini hanno osservato la battaglia e hanno già riferito della tua vittoria impeccabile. Bene, hai svolto bene il tuo lavoro. Ecco i 15.000 pesos che ti avevo promesso. E grazie, mi hai aiutato moltissimo.";
			link.l1 = "Va bene, sono stato felice di aiutare! Ma devo andare ora, sono stato qui troppo a lungo e ho molte cose da fare. Addio!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 15000);
			pchar.questTemp.pirateStartQuest = "0";
			CloseQuestHeader("pSQ");
			group_DeleteGroup("pirateStartQuest_Smuggler_group");
		break;


	}
}

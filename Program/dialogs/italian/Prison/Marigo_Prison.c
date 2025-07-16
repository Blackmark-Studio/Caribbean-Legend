// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Parla, sto ascoltando";
			link.l1 = "Mi sono sbagliato. Addio.";
			link.l1.go = "Exit";
			//искушение барбазона
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation.Prison"))
            { 
                link.l1 = "Qui avete sotto arresto Simon Morelle. È un contrabbandiere la cui goletta è stata affondata da una pattuglia non molto tempo fa. Posso vederlo?";
                link.l1.go = "BarbTemptation";
				DeleteAttribute(pchar, "questTemp.Saga.BarbTemptation.Prison");
            }
			// Addon-2016 Jason ФМК-Сент-Кристофер
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "way_div")
			{
				link.l1 = "Ufficiale, sono stato mandato qui dal mio governatore di Philipsburg. Mi ha chiesto di perquisire l'isola e le sue acque alla ricerca di spie inglesi. Sua Eccellenza mi ha anche detto che tu potresti fornirmi delle informazioni utili.";
				link.l1.go = "FMQN";
			}
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "way_div_2")
			{
				link.l1 = "Ufficiale, ho trovato la pattuglia mancante. Ho anche trovato le spie britanniche. Sono qui sull'isola.";
				link.l1.go = "FMQN_3";
			}
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "hol_peace_rew")
			{
				link.l1 = "Sono di nuovo io, ufficiale. Avete arrestato le spie?";
				link.l1.go = "FMQN_8";
			}
		break;
		
		//искушение барбазона
		case "BarbTemptation":
			dialog.text = "E perché ne avete bisogno, signore?";
			link.l1 = "Voglio dirgli che è un maledetto bastardo e furfante. Spero che lo aiuti a stare in piedi sulla forca.";
			link.l1.go = "BarbTemptation_1";
		break;
		
		case "BarbTemptation_1":
			dialog.text = "Ah-ah! Hai senso dell'umorismo, signore... Beh, duemila pesos e puoi andare avanti.";
			if(sti(Pchar.money) >= 2000)
			{
				link.l1 = "Prendilo, ufficiale. Grazie!";
				link.l1.go = "BarbTemptation_2";
			}
			link.l2 = "Hm... Sai, ho cambiato idea. Meglio sprecare i miei soldi in taverna.";
			link.l2.go = "BarbTemptation_4";
		break;
		
		case "BarbTemptation_2":
			AddMoneyToCharacter(pchar, -2000);
			dialog.text = "Siete i benvenuti... Andate avanti!";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
		break;
		
		case "BarbTemptation_4":
			dialog.text = "Come desideri, non riceverai una proposta del genere la prossima volta.";
			link.l1 = "Non ne ho bisogno comunque. Ci vediamo, ufficiale!";
			link.l1.go = "exit";
		break;
		
		// Addon-2016 Jason ФМК-Сент-Кристофер
		case "FMQN":
			DelLandQuestMark(npchar);
			dialog.text = "Utile? Ah! Pensandoci meglio, aspetta. Ho qualcosa di utile da dirti. Una delle nostre pattuglie è scomparsa nella giungla. Avrebbero dovuto essere già tornati nelle loro caserme, ma sembra che preferiscano la compagnia dei pappagalli. O forse è successo davvero qualcosa. Se li trovi durante le tue ricerche, per favore, dì loro di inventare una giustificazione decente per il loro ritardo, altrimenti non gradiranno le conseguenze... Il comandante della pattuglia si chiama Jannes Hoffman.";
			link.l1 = "È tutto, ufficiale?";
			link.l1.go = "FMQN_1";
		break;
		
		case "FMQN_1":
			dialog.text = "Sì, dannazione. Mi dispiace ma non ho altro da dirti. Buona fortuna, capitano.";
			link.l1 = "Grazie...";
			link.l1.go = "FMQN_2";
		break;
		
		case "FMQN_2":
			DialogExit();
			pchar.questTemp.FMQN = "way_div_1";
			AddQuestRecord("FMQ_Nevis", "10");
			FMQN_SetSoldiersInCave();
		break;
		
		case "FMQN_3":
			DelLandQuestMark(npchar);
			dialog.text = "Cosa?! Spero che non stia scherzando? Dammi un rapporto!";
			link.l1 = "Mi sono imbattuto in una pattuglia vicino a una grotta nella giungla. Mi hanno fermato e chiesto dove stavo andando e perché, poi mi hanno lasciato andare. Dannazione, se non erano gli inglesi travestiti da olandesi! Ho visto anche qualcosa di curioso nella giungla che sembrava esattamente un gruppo di uomini nudi nascosti nei cespugli. Presumo che il gruppo di incursione britannico abbia disarmato la vostra pattuglia e preso le loro uniformi.";
			link.l1.go = "FMQN_4";
		break;
		
		case "FMQN_4":
			dialog.text = "...";
			link.l1 = "Come capirai, non ho voluto rischiare di lottare contro una squadra di giubbe rosse addestrate, quindi mi sono precipitato da te con un rapporto.";
			link.l1.go = "FMQN_5";
		break;
		
		case "FMQN_5":
			dialog.text = "Allora-allora... Una grotta hai detto? Quanti di loro hai contato??";
			link.l1 = "Cinque uomini. E sì, penso che siano entrati in quella grotta.";
			link.l1.go = "FMQN_6";
		break;
		
		case "FMQN_6":
			dialog.text = "Mando immediatamente una squadra alla grotta! Capitano, se gli uomini che hai incontrato sono davvero spie britanniche, riceverai una ricompensa ben meritata. Sei libero di unirti alla squadra se vuoi assistere le autorità nell'arresto di quei bastardi e ricevere una ricompensa extra, dopotutto sono ordini del governatore. Quindi, vieni con noi?";
			link.l1 = "No ufficiale, inseguire le spie è tuo compito. Assicurati di mandare una squadra ben armata, questi canaglie sono troppo pericolosi...";
			link.l1.go = "FMQN_7";
			link.l2 = "Credo di poterlo fare. I tuoi uomini troveranno le spie più velocemente con il mio aiuto.";
			link.l2.go = "FMQN_10";
		break;
		
		case "FMQN_7":
			dialog.text = "La tua scelta, capitano, terrò conto del tuo consiglio. Vieni a trovarmi domani per sentire i risultati della nostra operazione.";
			link.l1 = "Ci vediamo domani.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_HollandPeace");
		break;
		
		case "FMQN_8":
			DelLandQuestMark(npchar);
			dialog.text = "Le vostre informazioni erano corrette, capitano. Abbiamo trovato quei bastardi dentro la grotta. Non avevano intenzione di arrendersi e si sono impegnati in una lotta. Di conseguenza - li abbiamo eliminati tutti.. Abbiamo anche trovato la pattuglia scomparsa. Stanno bene e vivi, anche se un po' malconci... Grazie, capitano, a nome di tutti i buoni cittadini di Philipsburg. La vostra vigilanza sarà premiata come promesso. Per favore, prendetela.";
			link.l1 = "Grazie!";
			link.l1.go = "FMQN_9";
		break;
		
		case "FMQN_9":
			AddMoneyToCharacter(pchar, 10000);
			dialog.text = "Sei sempre un ospite gradito a Sint-Maarten. Ora, scusami, ho altri affari di cui occuparmi.";
			link.l1 = "Anche io. Addio.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_HollandPeaceComplete");
		break;
		
		case "FMQN_10":
			dialog.text = "Molto bene. Il tuo aiuto è molto apprezzato. Vai alle porte della città, la squadra punitiva si riunirà lì tra un'ora.";
			link.l1 = "Un piccolo consiglio, dovresti mandare i migliori soldati che hai per questa missione. Quegli spie sono pericolosi.";
			link.l1.go = "FMQN_11";
		break;
		
		case "FMQN_11":
			dialog.text = "Non preoccuparti. Sto inviando i nostri soldati più esperti sotto il comando dell'ufficiale Hans Shulte - il maestro di spada di Philipsburg.";
			link.l1 = "Benissimo! Non perdiamo tempo allora.";
			link.l1.go = "exit";
			WaitDate("",0,0,0,1,5);
			AddDialogExitQuestFunction("FMQN_HollandBattle");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

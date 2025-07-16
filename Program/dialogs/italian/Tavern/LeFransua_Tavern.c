// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quali domande hai?","Come posso aiutarti, "+GetAddress_Form(NPChar)+"?"),"Hai cercato di farmi una domanda non molto tempo fa, "+GetAddress_Form(NPChar)+"...","Durante tutto il giorno, questa è la terza volta che parli di una certa domanda...","Altre domande, presumo?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea...","Non ho niente di cui parlare al momento."),"Uh, dove se ne è andata la mia memoria...","Sì, è davvero la terza volta...","No, quali domande?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";						
			//Jason, Бремя гасконца
			if (CheckAttribute(PChar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "hire" && !CheckAttribute(npchar, "quest.storehelper"))
			{
				link.l1 = "Ascolta, "+npchar.name+", sono venuto da te per un affare insolito. Ho bisogno di trovare un uomo che desideri una vita tranquilla e pacifica sulla baia come assistente di un mercante in un negozio di Saint-Pierre. Lo stipendio è buono e avrà un tetto sulla testa di cui occuparsi. Sapresti suggerire a chi potrei rivolgermi?";
				link.l1.go = "storehelper";
			}
			if (CheckAttribute(PChar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "seabattle" && !CheckAttribute(npchar, "quest.seabattle") && pchar.location.from_sea == "LeFransua_town")
			{
				link.l1 = "Sono qui per le botti di vino che stai per caricare sulla mia nave per la consegna a Guadalupa...";
				link.l1.go = "seabattle";
			}
			//Бремя гасконца
			//Jason, Португалец
			if (CheckAttribute(PChar, "questTemp.Portugal") && pchar.questTemp.Portugal == "PortugalLeFransua" && !CheckAttribute(npchar, "quest.portugal") && Pchar.location.from_sea == "LeFransua_town")
			{
				link.l1 = "Sai, "+npchar.name+", sto cercando un amico. Doveva arrivare qui e non si sentiva bene. Forse i suoi amici lo hanno aiutato...";
				link.l1.go = "Portugal";
			}
			//Португалец
		break;
		
		case "storehelper":
			dialog.text = "Ehm.. Abbiamo diverse persone qui che vorrebbero passare da una vita da marinaio a quella da terricolo. Potrei aiutarti, ma ti dico subito: non sarà gratis.";
			link.l1 = "Eh! E quanto vuoi?";
			link.l1.go = "storehelper_1";
		break;
		
		case "storehelper_1":
			dialog.text = "Mille pezzi di otto. E non devi fare nulla, tra un'ora i candidati per il lavoro saranno nella mia taverna, più candidati. Potrai parlare con loro e scegliere quello che ti piace più degli altri.";
			if (sti(Pchar.money) >= 1000)
			{
				link.l1 = "Ahh... Va bene, ecco, prendi mille!";
				link.l1.go = "storehelper_2";
			}
			link.l2 = "Mi dispiace, ma non ho così tanti soldi!";
			link.l2.go = "storehelper_exit";
		break;
		
		case "storehelper_2":
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = "Non preoccuparti, amico. Riceverai la metà di questa somma indietro dal candidato. Gli dirò che questo è il costo dei tuoi servizi, he he... Non daranno più di cinquecento. Passa dalla mia taverna tra un'ora, entro quel tempo avrò trovato le persone di cui hai bisogno qui ad aspettarti.";
			link.l1 = "Bene. Tornerò tra un'ora, "+npchar.name+".";
			link.l1.go = "storehelper_3";
			npchar.quest.storehelper = "true";
			DelLandQuestMark(npchar);
		break;
		
		case "storehelper_3":
			DialogExit();
			SetLaunchFrameFormParam("One hour passed...", "", 0, 5);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0); //крутим время
			RecalculateJumpTable();
			Storehelper_hire("");
		break;
		
		case "storehelper_exit":
			dialog.text = "Mi dispiace anche a me che tu non abbia quel tipo di soldi. Ma lo sai bene, affari del genere non si fanno solo per un 'grazie'. Quindi...";
			link.l1 = "Capisco. Ma davvero non ho i soldi. Va bene, addio...";
			link.l1.go = "exit";
			//pchar.quest.storehelper.over = "yes";
			//AddTimeToCurrent(2,0);
			//DeleteAttribute(pchar, "questTemp.Sharlie.Storehelper");
			//CloseQuestHeader("SharlieA");
		break;
		
		case "seabattle":
			DelLandQuestMark(npchar);
			dialog.text = "Di cosa stai parlando, compagno? Di quale vino parli?";
			link.l1 = "Sono stato mandato da un uomo di nome Walter Catcher. Ha detto che hai bisogno di una nave per trasferire del vino a Guadeloupe per diecimila pesos. E che hai bisogno proprio della mia nave per questo lavoro...";
			link.l1.go = "seabattle_1";
			npchar.quest.seabattle = "true";
		break;
		
		case "seabattle_1":
			dialog.text = "Ascolta compagno, non tratto con il vino, non ho bisogno dei tuoi servizi, e non conosco nessun Walter Catcher.";
			link.l1 = "Che strano! Quindi, quel Catturatore non è stato mandato da te... Allora, di cosa si tratta questa commedia?";
			link.l1.go = "seabattle_2";
		break;
		
		case "seabattle_2":
			dialog.text = "Eh! Beh, questo è o un errore o una cattiva barzelletta o...";
			link.l1 = "O cosa?";
			link.l1.go = "seabattle_3";
		break;
		
		case "seabattle_3":
			dialog.text = "Non capisci da solo? Qualcuno doveva attirarti a Le Francois, per cosa non lo so. Al tuo posto, mi sbrigerei a sparire da qui stando il più attento possibile. Questa puzza di affari sporchi, compagno...";
			link.l1 = "Suppongo tu abbia ragione. Non mi piaceva quella faccia del Cacciatore. Va bene, seguirò il tuo consiglio. Addio, Cesar!";
			link.l1.go = "seabattle_4";
		break;
		
		case "seabattle_4":
			DialogExit();
			AddQuestRecord("Sharlie", "16");
			pchar.quest.seabattle.win_condition.l1 = "location";
			pchar.quest.seabattle.win_condition.l1.location = "Martinique";
			pchar.quest.seabattle.function = "SharlieSeabattle_ship";
			
			pchar.quest.NewGameTip4.win_condition.l1 = "location";
			pchar.quest.NewGameTip4.win_condition.l1.location = "LeFransua_town";
			pchar.quest.NewGameTip4.function = "ShowNewGameTip";
			pchar.quest.NewGameTip4.text = "Your first sea battle is coming! Save you game!";					  
		break;
		
		case "Portugal":
			dialog.text = "Sì, il tuo amico è arrivato qui, capitano. È arrivato ieri e ha affittato una stanza al piano di sopra. Anche i suoi compagni di equipaggio sono qui, he-he... Stanno seduti là. Chiedi a loro!";
			link.l1 = "...";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			DialogExit();
			AddDialogExitQuestFunction("Portugal_enterPirates");
			npchar.quest.portugal = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

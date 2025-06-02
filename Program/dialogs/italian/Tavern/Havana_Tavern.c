// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Tutte le voci di "+GetCityName(npchar.city)+" al vostro servizio. Cosa vorreste scoprire?","Ne stavamo proprio parlando. Devi aver dimenticato...","Questa è la terza volta oggi che parli di qualche domanda...","Ripeti come un pappagallo...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sai, "+NPChar.name+", forse la prossima volta.","Giusto, per qualche motivo ho dimenticato...","Sì, è davvero la terza volta...","Sì...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Slavetrader") && pchar.questTemp.Slavetrader == "FindRatHavana")
            {
                link.l1 = "Francois Gontier è per caso passato per la tua città? Ha una corvetta '"+pchar.questTemp.Slavetrader.ShipName+"', giusto nel caso... ";
                link.l1.go = "Havana_ratT_1";
            }
			if (CheckAttribute(npchar, "quest.batabano"))
            {
                link.l1 = "Dimmi, amico, dove potrei trovare Don Diego de Montoya? Sono in ritardo? È già partito per Main?";
                link.l1.go = "guardoftruth";
            }
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "Ascolta, è passato di qui un uomo di nome Joachim Merriman? Un medico di mezza età, portoghese, con baffi, barba imperiale e occhi penetranti? Forse, voleva affittare una stanza?";
				link.l1.go = "caleuche";
			}
		break;

		case "Havana_ratT_1":
			dialog.text = "Aha, quel tizio tetro? Sì, è passato da me. Ti dirò una cosa: aveva un appuntamento con Oregon-e-Haskon. Ha fatto domanda per ricevere un brevetto. Ma non ha funzionato per lui ed è uscito di lì.";
			Link.l1 = "E dove ha salpato, lo sai? Lo sto inseguendo da Porto Bello e semplicemente non riesco a trovarlo.";
			Link.l1.go = "Havana_ratT_2";
		break;
		
		case "Havana_ratT_2":
			dialog.text = "Cosa ne vuoi da lui? Ha paura degli estranei, si nasconde sempre da tutti, appena vede uno straniero armato afferra una spada. Si muove solo circondato da quattro guardie. Potresti essere l'uomo da cui si guarda?";
			Link.l1 = "Signore, la gente continua a dirlo! Cosa, sembro un assassino? È un mio vecchio amico, ho fretta di passargli delle notizie, sarà molto felice di sapere che non ha più bisogno di nascondersi, nessuno lo sta cercando.";
			Link.l1.go = "Havana_ratT_3";
		break;
		
		case "Havana_ratT_3":
			dialog.text = "Non c'è bisogno che si nasconda? Ah-ah-ah! Proprio un giorno prima della sua partenza da L'Avana, un intero branco di teppisti ha cercato di ucciderlo nella giungla... Naturalmente, aveva la sua gente e li hanno trasformati in polpetta in un secondo. E tu stai dicendo...";
			Link.l1 = "Oh, su. Probabilmente erano solo alcuni banditi locali che cercavano di rubare il suo portafoglio. Sai bene quanti furfanti si aggirano per la giungla. Quindi, dove se n'è andato?";
			Link.l1.go = "Havana_ratT_4";
		break;
		
		case "Havana_ratT_4":
			dialog.text = "Ebbene, dopo essere stato mandato lontano e per molto tempo dalla residenza, continuava a ripetere che si sarebbe consegnato ai mangiarane, ai suoi connazionali. Si è messo in viaggio per Tortuga, da un certo d'Ogeron... Ha anche borbottato qualcosa sulla sua amante, ma non sono riuscito a capirlo bene.";
			Link.l1 = "Allora, Tortuga? Ottimo! Spero di prenderlo lì. Grazie, "+npchar.name+", sei stato di grande aiuto. Addio.";
			Link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_7");
			pchar.questTemp.Slavetrader = "FindRatTortuga";
			pchar.quest.Slavetrader_findTortugaRat.win_condition.l1 = "location";
            pchar.quest.Slavetrader_findTortugaRat.win_condition.l1.location = "Tortuga_HouseHut";
            pchar.quest.Slavetrader_findTortugaRat.win_condition = "Slavetrader_findTortugaRat";
		break;

		case "guardoftruth":
			dialog.text = "Hm...E perché un francese dovrebbe essere interessato a Don Diego, eh?";
			link.l1 = "Il fatto che io sia francese è irrilevante. Ciò che conta è questo documento firmato dall'Inquisitore. Dai un'occhiata... vedi ora? Ho un messaggio urgente per Diego.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "A-ha, quindi lavori per Sua Reverenza, Padre Vincento? Questo cambia le cose. Don Diego de Montoya è partito due giorni fa con la sua squadra, ma è presto tornato sulla sua goletta da corriere. Una delle sue navi è naufragata sugli scogli a sud di Cuba, quindi oggi ha comprato materiale per le riparazioni\nControlla la baia a Sud, troverai lì una nave e lo stesso uomo. Dubito che siano già riusciti a riparare i buchi.";
			link.l1 = "Grazie, amico! Sei stato di grande aiuto!";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Per niente, in qualsiasi momento. Sono sempre felice di aiutare un fratello gesuita.";
			link.l1 = "Sì, pax vobiscum e tutto il resto.";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			DialogExit();
			DeleteAttribute(npchar, "quest.batabano");
			AddQuestRecord("Guardoftruth", "47");
			pchar.quest.GuardOT_Batabano.win_condition.l1 = "location";
			pchar.quest.GuardOT_Batabano.win_condition.l1.location = "Shore13";
			pchar.quest.GuardOT_Batabano.function = "GuardOT_SanAntonioPrepare";
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "Lo sa il Diavolo, amico. Potrebbe essere arrivato, ma non ne so nulla. Mi dispiace.";
			link.l1 = "Capisco. Peccato. Continuerò la mia ricerca...";
			link.l1.go = "exit";
			npchar.quest.caleuche = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

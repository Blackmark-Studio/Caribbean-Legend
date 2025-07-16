// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Che tipo di domande?","Cosa vuoi, "+GetAddress_Form(NPChar)+"?"),"Hai già provato a farmi una domanda "+GetAddress_Form(NPChar)+"...","Stai parlando della stessa questione per la terza volta oggi...","Guarda, se non hai niente da dirmi riguardo le questioni del porto, allora non disturbarmi con le tue domande.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea.","Non ho nulla di cui parlare."),"Mai mente.","Infatti, già la terza volta...","Mi dispiace, ma per ora non mi interessano gli affari del porto.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatHavana")
            {
                link.l1 = "Buon giorno a te. Vorrei saperne di più su una corvetta chiamata '"+pchar.questTemp.Slavetrader.ShipName+"' sotto il comando di Francois Gontier.";
                link.l1.go = "Havana_ratP_1";
			}
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "Scusami, è arrivato al tuo porto un uomo di nome Joachim Merriman? Un signore di mezza età, portoghese, con baffi, barba imperiale e occhi penetranti?";
				link.l1.go = "caleuche";
			}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_3" && !CheckAttribute(npchar, "quest.Mtraxx"))
			{
				link.l1 = "Sono interessato a una nave chiamata 'Cantavro'. Sto cercando il suo capitano - Esberdo Cabanas, per una questione privata. Potresti aiutarmi?";
				link.l1.go = "mtraxx";
			}
		break;
		
		case "Havana_ratP_1":
			dialog.text = NPCStringReactionRepeat("Sì, era qui. Ma è già andato. Chiedi al nostro oste di lui, ha affittato una stanza al piano di sopra.","Hai già chiesto di questo e ho risposto.","Ti dico che hai già chiesto di questo Gontier..","Ti prego di non disturbarmi!","block",0,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Grazie. Lo farò.","Mh, beh ...","Sì, ho davvero chiesto ...","Scusa, "+npchar.name+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "Non posso dirti nulla su di lui. Anche se è arrivato, non si è mai registrato da nessuna parte.";
			link.l1 = "Capisco. Che peccato... Va bene, continuerò la mia ricerca ...";
			link.l1.go = "exit";
			npchar.quest.caleuche = "true";
		break;
		
		// Addon 2016-1 Jason пиратская линейка
		case "mtraxx":
			dialog.text = "Vediamo... la goletta 'Cantavro' ha preso il largo due giorni fa per una pattuglia... tuttavia, la destinazione non è elencata. È una nave militare, quindi la destinazione è nota solo al suo capitano e al comandante del forte. Ti suggerirei di parlare direttamente con il comandante, puoi trovarlo al forte, se desideri saperne di più. Purtroppo, questo è tutto ciò che posso fare per te.";
			link.l1 = "Capisco. Beh, grazie per il tuo tempo...";
			link.l1.go = "exit";
			npchar.quest.Mtraxx = "true";
			AddQuestRecord("Roger_1", "5");
			DelLandQuestMark(npchar);
			AddLandQuestMark(characterFromId("Havana_tavernkeeper"), "questmarkmain");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Tutti i rumors di "+GetCityName(npchar.city)+" al vostro servizio. Cosa vorreste scoprire?","Ne stavamo proprio parlando. Devi aver dimenticato...","Questa è la terza volta oggi che parli di qualche domanda...","Ripeti sempre le stesse cose come un pappagallo...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sai, "+NPChar.name+", forse la prossima volta.","Giusto, ho dimenticato per qualche motivo...","Sì, è davvero la terza volta...","Sì...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatPanama")
            {
                link.l1 = "Ho sentito dire che avete un corsaro di nome Francois Gontier nella vostra città. Sapreste per caso dove posso trovarlo?";
                link.l1.go = "Panama_rat_1";
            }
			// Addon-2016 Jason ”ЊЉ-ѓваделупа
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "headhunter_panama")
            {
                link.l1 = "Guarda, sto cercando un uomo chiamato Bertrand Pinette, ne hai mai sentito parlare? È arrivato a Panama non molto tempo fa. Un signore imponente con una parrucca. Potrebbe essere stato qui...";
                link.l1.go = "FMQG";
            }
		break;

		//-->работорговец
		case "Panama_rat_1":
			dialog.text = NPCStringReactionRepeat("Sì, abbiamo avuto un tipo del genere in città. Se ne stava in giro per luoghi oscuri... Poi alcuni dei suoi compagni sono venuti a fargli visita, sembravano una banda di tagliagole. Ha lasciato la città con loro.","Hai già chiesto di questo e ti ho risposto.","Te l'ho detto, avevi già chiesto di quel Gontier.","Ascolta, vai via e smetti di infastidirmi! Hai completamente perso la testa?","block",0,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("E dove è andato, lo sai?","Mm, immagino di sì...","Sì, esatto, l'ho chiesto...","Scusa, "+npchar.name+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "Panama_rat_2";
		break;
		
		case "Panama_rat_2":
			dialog.text = "Ebbene, c'è solo una via di uscita da qui a piedi - Portobello. Ed è andato a piedi. Quindi cercalo là.";
			link.l1 = "Grazie, sei stato di grande aiuto!";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "FindRatPortobello";
			AddQuestRecord("Slavetrader", "21_1");
		break;
		//<--работорговец
		
		// Addon-2016 Jason ”ЊЉ-ѓваделупа
		case "FMQG":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("panama");
			dialog.text = "Bertrand Pinette? Francese? Mai sentito parlare di lui. No compagno, non abbiamo visto francesi da un po'.";
			link.l1 = "Che peccato... Sei sicuro? È amico di un importante hidalgo chiamato Don Carlos de Milyar. Dovevano arrivare qui insieme.";
			link.l1.go = "FMQG_1";
		break;
		
		case "FMQG_1":
			dialog.text = "Signor de Milyar? Quel gentiluomo ha visitato Panama un anno fa. In realtà, Don Carlos de Milyar vive a Portobello. È un grande amico del governatore locale.";
			link.l1 = "Capisco. Non c'era bisogno di sprecare tempo e fiato nella giungla. Grazie compagno.";
			link.l1.go = "FMQG_2";
		break;
		
		case "FMQG_2":
			DialogExit();
			pchar.questTemp.FMQG = "headhunter_portobello";
			AddQuestRecord("FMQ_Guadeloupe", "8");
			AddMapQuestMarkCity("PortoBello", true);
			AddLandQuestMark(characterFromId("PortoBello_tavernkeeper"), "questmarkmain");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

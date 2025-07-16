// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Qual tipo di domande?","Cosa vuoi, "+GetAddress_Form(NPChar)+"?"),"Hai già cercato di farmi una domanda "+GetAddress_Form(NPChar)+"...","Stai parlando di qualche questione per la terza volta oggi...","Guarda, se non hai nulla da dirmi riguardo alle questioni del porto, allora non disturbarmi con le tue domande.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea.","Non ho nulla di cui parlare."),"Mai mente.","Infatti, già la terza volta...","Mi dispiace, ma al momento non sono interessato agli affari del porto.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			
			if (pchar.questTemp.Slavetrader == "FindRatJamaica")
            {
                link.l1 = "Buon giorno. Il capitano Francois Gontier si è registrato qui? Stava navigando da Porto Bello su una corvetta chiamata '"+pchar.questTemp.Slavetrader.ShipName+"'.'";
                link.l1.go = "Jamaica_ratPP_1";
            }
			
		break;
		
		case "Jamaica_ratPP_1":
			dialog.text = NPCStringReactionRepeat("No, non l'ha fatto. E la corvetta '"+pchar.questTemp.Slavetrader.ShipName+"' non è stato visto a Port-Royal.","Hai già chiesto di questo ed ho risposto.","Ti dico che hai già chiesto di questo tale Gontier.","Per favore, non distrarmi dal mio lavoro!","block",0,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Grazie. Continuerò a cercare.","Mh, beh...","Sì, ho davvero chiesto ...","Scusa, "+npchar.name+"...",npchar,Dialog.CurrentNode);
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

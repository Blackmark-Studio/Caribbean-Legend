// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Che tipo di domande?","Cosa vuoi, "+GetAddress_Form(NPChar)+"?"),"Hai già provato a farmi una domanda "+GetAddress_Form(NPChar)+"...","Hai parlato della stessa questione per la terza volta oggi...","Guarda, se non hai nulla da dirmi riguardo gli affari del porto, allora non disturbarmi con le tue domande.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea.","Non ho nulla di cui parlare."),"Non importa.","Infatti, già la terza volta...","Mi dispiace, ma per ora non mi interessano le questioni del porto.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			
			if (pchar.questTemp.Slavetrader == "FindRatTortuga")
            {
                link.l1 = "Buon giorno. Sto cercando Francois Gontier. La sua corvetta '"+pchar.questTemp.Slavetrader.ShipName+"' deve essere stato qui nel vostro porto.";
                link.l1.go = "Tortuga_ratP_1";
            }
			
		break;

		case "Tortuga_ratP_1":
			dialog.text = NPCStringReactionRepeat("Mh... Devo deluderti. Corvette '"+pchar.questTemp.Slavetrader.ShipName+" non è mai stato qui e nemmeno Francois Gontier si è registrato qui.","Hai già chiesto di questo e ho risposto.","Ti dico che hai già chiesto di questo Gontier.","Per favore, non distrarmi dal mio lavoro!","block",0,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Grazie. Continuerò a cercare.","Mm, beh...","Sì, ho davvero chiesto ...","Scusa, "+npchar.name+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

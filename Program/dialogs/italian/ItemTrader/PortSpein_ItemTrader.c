// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Che tipo di domande?","Cosa vuoi, "+GetAddress_Form(NPChar)+"?"),"Di nuovo domande, "+GetAddress_Form(NPChar)+"...","Domande, domande... Che ne dici di fare un po' di commercio, "+GetAddress_Form(NPChar)+"eh?","Ascolta, quanto tempo pensi di parlare?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Nessuna domanda per ora...","Mi dispiace, non ho nulla da dire ora..."),"Di nuovo, mi dispiace...","Forse è davvero il momento di commerciare...","Mi dispiace, facciamo affari...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "Ascolta, il nome 'Juan' ti dice qualcosa?";
				link.l1.go = "Consumption";
			}			
		break;
		
		//Цена чахотки
		case "Consumption":
			dialog.text = "No, non lo fa... Ora, per favore non disturbarmi, sono piuttosto occupato... Che domanda idiota...";
			link.l1 = "Capisco. Scusa per aver sprecato il tuo tempo...";
			link.l1.go = "exit";
			npchar.quest.Consumption = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

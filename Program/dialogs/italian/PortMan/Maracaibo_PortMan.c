// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Qual tipo di domande?","Cosa vuoi, "+GetAddress_Form(NPChar)+"?"),"Hai già provato a farmi una domanda "+GetAddress_Form(NPChar)+"...","Hai parlato della stessa questione per la terza volta oggi...","Guarda, se non hai nulla da dirmi riguardo gli affari del porto, allora non disturbarmi con le tue domande.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea.","Non ho nulla di cui parlare."),"Non importa","Infatti, già la terza volta...","Mi dispiace, ma per ora non mi interessano le questioni del porto.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

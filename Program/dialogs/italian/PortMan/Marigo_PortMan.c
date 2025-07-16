// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Che tipo di domande?","Cosa vuoi, "+GetAddress_Form(NPChar)+"?"),"Hai già provato a farmi una domanda "+GetAddress_Form(NPChar)+"...","Stai parlando di una certa questione per la terza volta oggi...","Guarda, se non hai nulla da dirmi riguardo le questioni del porto, allora non disturbarmi con le tue domande.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea.","Non ho nulla di cui parlare."),"Mai mente.","Infatti, già la terza volta...","Mi dispiace, ma per ora non mi interessano gli affari del porto.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "maarten1")
			{
				link.l1 = "Cerco un galeone chiamato 'Admirable' sotto la bandiera francese. Il suo capitano si chiama Gaius Marchais. Puoi dirmi dove è salpato successivamente? Forse, si è registrato qui?";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Hmmm, 'Ammirevole'? Galeone? Me lo ricordo. Vediamo qui... l'abbiamo noleggiato per consegnare paprika a Bridgetown su Barbados. E' successo qualcosa?";
			link.l1 = "No, ma Gaius è mio amico e non vedo l'ora di incontrarlo.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Allora naviga verso Barbados. Ma dubito che lo troverai lì, è passato molto tempo. Almeno puoi chiedere al maestro del porto locale di aiutarti.";
			link.l1 = "Eccomi di nuovo in viaggio, immagino.";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			DialogExit();
			AddQuestRecord("Guardoftruth", "12");
			pchar.questTemp.Guardoftruth = "barbados";
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

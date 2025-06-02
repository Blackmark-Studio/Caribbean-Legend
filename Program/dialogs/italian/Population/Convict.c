// диалог освобожденных каторжников рудника
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = NPCStringReactionRepeat("Di nuovo tu, signore?","Ascolta, signore, sarebbe meglio se te ne andassi...","Non disturbarmi, signore! Te lo chiedo gentilmente.","Oh, non posso sopportarlo... Anche remare su una galea era meglio.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sì, sono di nuovo io.","Non dirmi cosa fare.","E se continuo a infastidire?","Torna in cambusa allora!",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Cosa vuoi, signore?";
				link.l1 = "Da te? Niente, suppongo. Volevo solo dire ciao.";
				link.l1.go = "exit";
				npchar.quest.meeting = "1";
			}
			NextDiag.TempNode = "First time";
		break;

		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Non sfidare il tuo destino, compagno! Metti via la tua arma!","Ascolta, sono un cittadino di questa città e ti chiedo di riporre la tua spada.");
			link.l1 = LinkRandPhrase("Bene...","Come desideri...","Come dici tu...");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

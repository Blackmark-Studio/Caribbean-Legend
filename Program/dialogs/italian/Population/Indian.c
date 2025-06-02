//Jason общий диалог индейцев на улицах
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
			dialog.text = NPCStringReactionRepeat(""+GetSexPhrase("Viso pallido","Bianca squaw")+" vuole parlare?","Di nuovo tu, "+GetSexPhrase("viso pallido","squaw bianca")+".",""+GetSexPhrase("Viso pallido ama parlare. Come una donna.","La donna bianca ama parlare.")+"","Grande Spirito ha portato viso pallido"+GetSexPhrase("fratello","sorella")+" a me.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sì.","Sì, sono di nuovo io.","Molto poetico.","Sono contento di vederti anche io.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Come, fratello bianco. Vuoi parlare con l'indiano?";
				link.l1 = "Saluti, figlio della giungla. Sono lieto di vederti ma devo andare.";
				link.l1.go = "exit";
				npchar.quest.meeting = "1";
			}
			NextDiag.TempNode = "First time";
		break;

		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Non tentare gli spiriti, viso pallido! Metti via il coltello lungo!","Non affrettarti verso la morte, viso pallido! Metti via il coltello lungo!");
			link.l1 = LinkRandPhrase("Bene.","Come desideri.","Come dici tu.");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

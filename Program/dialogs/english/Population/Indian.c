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
			dialog.text = NPCStringReactionRepeat(""+GetSexPhrase("Paleface","White squaw")+" wants to talk?","You again, "+GetSexPhrase("paleface","white squaw")+".",""+GetSexPhrase("Paleface loves talking. Like a squaw.","White squaw loves talking.")+"","Great Spirit brought the paleface"+GetSexPhrase("brother","sister")+" to me.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Yes.","Yes, it's me again.","Very poetic.","I am glad to see you too.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Hello, white brother. You want to talk with Indian?";
				link.l1 = "Greetings, son of the jungle. I am glad to see you, but I have to go.";
				link.l1.go = "exit";
				npchar.quest.meeting = "1";
			}
			NextDiag.TempNode = "First time";
		break;

		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Don't tempt spirits, paleface! Put the long knife away!","Don't rush to your death, paleface! Put the long knife away!");
			link.l1 = LinkRandPhrase("Fine.","As you wish.","As you say.");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

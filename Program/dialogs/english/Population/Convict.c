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
			dialog.text = NPCStringReactionRepeat("You again, señor?","Listen, sir, you'd better walk away...","Don't bother me, sir! I ask you kindly.","Oh, I can't bear that... Even rowing a galley was better.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Yes, it's me again.","Don't tell me what to do.","And what if I keep bothering?","Get back to the galley then!",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "What do you want, señor?";
				link.l1 = "From you? Nothing, I suppose. Just wanted to say hello.";
				link.l1.go = "exit";
				npchar.quest.meeting = "1";
			}
			NextDiag.TempNode = "First time";
		break;

		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Don't tempt fate, mate! Put away your weapon!","Listen, I am a citizen of this town and I'm asking you to sheath your blade.");
			link.l1 = LinkRandPhrase("Fine...","As you wish...","As you say...");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

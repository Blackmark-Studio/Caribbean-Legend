void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	DeleteAttribute(&Dialog, "Links");
	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
		case "initial":
			dialog.text = _replica("initial_text");
			link.l1 = _replica("initial_l1");
			link.l1.go = "cheers";
		break;
		case "cheers":
			dialog.text = _replica("cheers_text");
			link.l1 = _replica("cheers_l1");
			link.l1.go = "exit";
			link.l2 = _replica("cheers_l2");
			link.l2.go = "endParty";
		break;
		case "repeat":
			dialog.text = _replica("repeat_text");
			link.l1 = _replica("cheers_l1");
			link.l1.go = "exit";
			link.l2 = _replica("repeat_l2");
			link.l2.go = "endParty";
		break;
		case "endParty":
			DialogExit();
			AddDialogExitQuestFunction("_Birthday_GoToCabin");
		break;
		case "Exit":
			DialogExit();
			NextDiag.currentNode = "repeat";
		break;
	}
}

string _replica(string key)
{
	string base = "Dialog_Alonso_";
	return DLG_Convert(base + key, "StoryFrames\RandomEvents\Birthday.txt");
}
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link;
	DeleteAttribute(&Dialog, "Links");
	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);

	switch (Dialog.CurrentNode)
	{
		case "initial":
			dialog.text = _replica("initial_text");
			link.l1 = _replica("initial_l1");
			link.l1.go = "exit";
		break;
		case "Exit":
			DialogExit();
		break;
	}
}

string _replica(string key)
{
	string base = "Dialog_Irons_";
	return DLG_Convert(base + key, "StoryFrames\RandomEvents\Birthday.txt");
}
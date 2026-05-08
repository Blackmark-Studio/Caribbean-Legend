void ProcessDialogEvent()
{
	ref NPChar;
	aref Link;
	DeleteAttribute(&Dialog, "Links");
	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);

	if (Dialog.CurrentNode == "initial" && CheckAttribute(NPChar, "SpecialRole")) Dialog.CurrentNode = NPChar.specialRole + "_initial";

	switch (Dialog.CurrentNode)
	{
		case "initial":
			dialog.text = _replica("initial_text");
			link.l1 = _replica("initial_l1");
			link.l1.go = "Exit";
		break;
		case "fgirl_initial":
			dialog.text = _replica("fgirl_initial_text");
			link.l1 = _replica("fgirl_initial_l1");
			link.l1.go = "Exit";
		break;
		case "fwife_initial":
			dialog.text = _replica("fwife_initial_text");
			link.l1 = _replica("fwife_initial_l1");
			link.l1.go = "Exit";
		break;
		case "Exit":
			DialogExit();
		break;
	}
}
string _replica(string key)
{
	string base = "Dialog_Helena_";
	return DLG_Convert(base + key, "StoryFrames\RandomEvents\Birthday.txt");
}
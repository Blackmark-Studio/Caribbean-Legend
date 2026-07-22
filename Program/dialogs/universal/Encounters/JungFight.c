
void ProcessDialogEvent()
{
    object dlgContext;
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link,  Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    string file = "Dialogs\Encounters\JungFight.txt";
    string diagType  = NPChar.JungFightType;
    string enemyType = NPChar.JungFightEnemies;

	switch(Dialog.CurrentNode)
	{
        // Не помог
		case "First time":
            NextDiag.TempNode = "First time";
            //if (bOfficer) diagType = "Officer";
			dialog.text = DLG_Convert(diagType + "_Win_" + enemyType + "_NoHelp", file);
            link.l0 = DLG_Convert("JungFight_Ok", file);
            link.l0.go = "Exit";
		break;

        case "Victory":
            NextDiag.TempNode = "Victory";
            if (NPChar.id == "JF_Officer") diagType = "Officer";
			dialog.text = DLG_Convert("JungFight_" + diagType + "_Thanks", file);
            link.l1 = DLG_Convert("JungFight_Victory_Ok", file);
            link.l1.go = "Exit";
        break;

        case "Reward":
            NextDiag.TempNode = "Victory";
            if (NPChar.id == "JF_Officer") diagType = "Officer";
			dialog.text = DLG_Convert("JungFight_" + diagType + "_Reward_" + enemyType, file);
            link.l1 = DLG_Convert("JungFight_Reward_Ok", file);
            link.l1.go = "Exit Reward";
        break;

		case "Exit Reward":
            // Up relation
            AddMoneyToCharacter(PChar, int(PChar.Rank)*500 + hrand(3000));
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
            JungFightReward(NPChar);
        break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
        break;
	}
}

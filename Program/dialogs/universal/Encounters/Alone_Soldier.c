
void ProcessDialogEvent()
{
    object dlgContext;
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link,  Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
            NextDiag.TempNode = "First time";
            if ("HaveGift" !in NPChar)
            {
                if (CheckCharacterItem(PChar, "potionrum"))
                {
                    link.l0 = DLG_Convert("Alone_Soldier_GiveRum", "Dialogs\Encounters\Alone_Soldier.txt");
                    link.l0.go = "GiveRum";
                }
                if (CheckCharacterItem(PChar, "potionwine"))
                {
                    link.l1 = DLG_Convert("Alone_Soldier_GiveWine", "Dialogs\Encounters\Alone_Soldier.txt");
                    link.l1.go = "GiveWine";
                }
            }
			if (NPChar.quest.meeting == "0")
			{
                NPChar.quest.meeting = "1";
				dialog.text = DLG_Convert("Alone_Soldier_First_time_text_1", "Dialogs\Encounters\Alone_Soldier.txt");
				link.l3 = DLG_Convert("Alone_Soldier_Bye", "Dialogs\Encounters\Alone_Soldier.txt");
				link.l3.go = "Exit";
                break;
			}
			dialog.text = DLG_Convert("Alone_Soldier_First_time_text_2", "Dialogs\Encounters\Alone_Soldier.txt");
            link.l3 = DLG_Convert("Alone_Soldier_Bye_2", "Dialogs\Encounters\Alone_Soldier.txt");
            link.l3.go = "Exit";
		break;

        case "GiveRum":
            NextDiag.TempNode = "Boozy";
            JungAloneSoldierPotion("potionrum", int(NPChar.Nation));
            dialog.text = DLG_Convert("Alone_Soldier_Thanks_Rum", "Dialogs\Encounters\Alone_Soldier.txt");
            link.l1 = DLG_Convert("Alone_Soldier_Rum_End", "Dialogs\Encounters\Alone_Soldier.txt");
            link.l1.go = "Exit";
        break;

        case "GiveWine":
            NextDiag.TempNode = "Boozy";
            JungAloneSoldierPotion("potionwine", int(NPChar.Nation));
            dialog.text = DLG_Convert("Alone_Soldier_Thanks_Wine", "Dialogs\Encounters\Alone_Soldier.txt");
            link.l1 = DLG_Convert("Alone_Soldier_Wine_End", "Dialogs\Encounters\Alone_Soldier.txt");
            link.l1.go = "Exit";
        break;

        case "Boozy":
            dialog.text = DLG_Convert("Alone_Soldier_Boozy", "Dialogs\Encounters\Alone_Soldier.txt");
            link.l1 = DLG_Convert("Alone_Soldier_Boozy_Ok", "Dialogs\Encounters\Alone_Soldier.txt");
            link.l1.go = "Exit";
        break;

		case "CitizenNotBlade":
			dialog.text = DLG_Convert("Alone_Soldier_NoBlade_" + rand(1), "Dialogs\Encounters\Alone_Soldier.txt");
			link.l1 = DLG_Convert("Alone_Soldier_NoBlade_Ok_" + rand(1), "Dialogs\Encounters\Alone_Soldier.txt");
			link.l1.go = "Exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

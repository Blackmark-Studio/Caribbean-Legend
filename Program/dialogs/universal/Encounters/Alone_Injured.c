
void ProcessDialogEvent()
{
    object dlgContext;
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link,  Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    string dialogType = NPChar.DialogFlag;
    if (dialogType == "Soldier" && GetRelation2BaseNation(int(NPChar.Nation)) == RELATION_ENEMY)
        dialogType = "EnemySoldier";

	switch(Dialog.CurrentNode)
	{
		case "First time":
            NextDiag.TempNode = "First time";
			if (NPChar.quest.meeting == "0")
			{
                NPChar.quest.meeting = "1";
				dialog.text = DLG_Convert(dialogType + "_First_time_1", "Dialogs\Encounters\Alone_Injured.txt");
                if (CheckCharacterItem(PChar, "potion1"))
                {
                    link.l0 = DLG_Convert("InjuredGuy_Give_Potion", "Dialogs\Encounters\Alone_Injured.txt");
                    link.l0.go = "Give Potion";
                }
                if (CheckCharacterItem(PChar, "potion2"))
                {
                    link.l1 = DLG_Convert("InjuredGuy_Give_Elixir", "Dialogs\Encounters\Alone_Injured.txt");
                    link.l1.go = "Give Elixir";
                }
                if (CheckCharacterItem(PChar, "potion4"))
                {
                    link.l2 = DLG_Convert("InjuredGuy_Give_Mixture", "Dialogs\Encounters\Alone_Injured.txt");
                    link.l2.go = "Give Mixture";
                }
                link.l3 = DLG_Convert("InjuredGuy_Kill", "Dialogs\Encounters\Alone_Injured.txt");
				link.l3.go = "Kill";
				link.l4 = DLG_Convert(dialogType + "_Bye_1", "Dialogs\Encounters\Alone_Injured.txt");
				link.l4.go = "Exit";
                break;
			}
            dialog.text = DLG_Convert(dialogType + "_First_time_2", "Dialogs\Encounters\Alone_Injured.txt");
            link.l0 = DLG_Convert("InjuredGuy_Kill", "Dialogs\Encounters\Alone_Injured.txt");
            link.l0.go = "Kill";
            link.l1 = DLG_Convert(dialogType + "_Bye_2", "Dialogs\Encounters\Alone_Injured.txt");
            link.l1.go = "Exit";
		break;

        case "Give Potion":
            NPChar.PotionToUse = "potion1";
            NPChar.RepIncr = 1;
            TakeNItems(PChar, "potion1", -1);
            AddCharacterExpToSkill(PChar, SKILL_DEFENCE, 5);
            ChangeCharacterComplexReputation(PChar, "nobility", 1);
            dialog.text = DLG_Convert(dialogType + "_ThanksPotion", "Dialogs\Encounters\Alone_Injured.txt");
            link.l0 = DLG_Convert(dialogType + "_Bye_3", "Dialogs\Encounters\Alone_Injured.txt");
            link.l0.go = "Exit Heal";
        break;

        case "Give Elixir":
            NPChar.PotionToUse = "potion2";
            NPChar.RepIncr = 2;
            TakeNItems(PChar, "potion2", -1);
            AddCharacterExpToSkill(PChar, SKILL_DEFENCE, 10);
            ChangeCharacterComplexReputation(PChar, "nobility", 2);
            dialog.text = DLG_Convert(dialogType + "_ThanksElixir", "Dialogs\Encounters\Alone_Injured.txt");
            link.l0 = DLG_Convert(dialogType + "_Bye_3", "Dialogs\Encounters\Alone_Injured.txt");
            link.l0.go = "Exit Heal";
        break;

        case "Give Mixture":
            NPChar.PotionToUse = "potion4";
            NPChar.RepIncr = 3;
            TakeNItems(PChar, "potion4", -1);
            AddCharacterExpToSkill(PChar, SKILL_DEFENCE, 12);
            ChangeCharacterComplexReputation(PChar, "nobility", 2);
            dialog.text = DLG_Convert(dialogType + "_ThanksMixture", "Dialogs\Encounters\Alone_Injured.txt");
            link.l0 = DLG_Convert(dialogType + "_Bye_3", "Dialogs\Encounters\Alone_Injured.txt");
            link.l0.go = "Exit Heal";
        break;

        case "Exit Heal":
            AddDialogExitQuestFunction("JungInjuredHeal");
			DialogExit();
		break;

        case "Kill":
            AddDialogExitQuestFunction("JungInjuredKill");
			DialogExit();
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

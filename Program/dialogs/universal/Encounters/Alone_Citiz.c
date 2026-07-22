
void ProcessDialogEvent()
{
    object dlgContext;
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link,  Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    if (FindSubStr(Dialog.CurrentNode, "Rumours", 0) != -1)
        Dialog.CurrentNode = "Rumours"; // Из-за идиотизма в движке с EmergencyExit

	switch(Dialog.CurrentNode)
	{
		case "First time":
            NextDiag.TempNode = "First time";
            dlgContext.Chance = JungWalker_RobberyChance();
			if (NPChar.quest.meeting == "0")
			{
                NPChar.quest.meeting = "1";
				dialog.text = DLG_Convert("Alone_Citiz_First_time_text_1", "Dialogs\Encounters\Alone_Citiz.txt");
                link.l10 = DLG_Convert("Alone_Citiz_ToRumours_first", "Dialogs\Encounters\Alone_Citiz.txt");
                link.l10.go = "Rumours";
                link.l0 = DLG_Convert("Alone_Citiz_First_time_l0", "Dialogs\Encounters\Alone_Citiz.txt", &dlgContext);
				link.l0.go = "Robbery";
				link.l1 = DLG_Convert("Alone_Citiz_First_time_l1", "Dialogs\Encounters\Alone_Citiz.txt");
				link.l1.go = "Exit";
                break;
			}
			dialog.text = DLG_Convert("Alone_Citiz_First_time_text_2", "Dialogs\Encounters\Alone_Citiz.txt");
            link.l10 = DLG_Convert("Alone_Citiz_ToRumours_second", "Dialogs\Encounters\Alone_Citiz.txt");
            link.l10.go = "Rumours";
            link.l0 = DLG_Convert("Alone_Citiz_First_time_l0_a", "Dialogs\Encounters\Alone_Citiz.txt", &dlgContext);
            link.l0.go = "Robbery";
            link.l1 = DLG_Convert("Alone_Citiz_First_time_l0_b", "Dialogs\Encounters\Alone_Citiz.txt");
            link.l1.go = "Exit";
		break;

		case "Rumours":
            string srum, posrep[3], answ[3];
            if (NPChar.Quest.Repeat.Rumours$int(0) < 2)
                 srum = SelectRumourEx("townman", NPChar);
            else srum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)];

            while(srum == NPChar.LastRumour$string(""))
                srum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)];
            NPChar.LastRumour = srum;

            for(int i = 0; i < 3; i++)
            {
                posrep[i] = DLG_Convert("Alone_Citiz_Rumours_posrep_" + (i+1), "Dialogs\Encounters\Alone_Citiz.txt");
                answ[i] = DLG_Convert("Alone_Citiz_Rumours_answ_" + (i+1), "Dialogs\Encounters\Alone_Citiz.txt");
            }

            Dialog.Text = NPCStringReactionRepeat(srum + posrep[0], srum + posrep[1], srum + posrep[2],
            DLG_Convert("Alone_Citiz_Rumours_Block", "Dialogs\Encounters\Alone_Citiz.txt"), "block", 1, NPChar, Dialog.CurrentNode);

            int qty = NPChar.Quest.Repeat.Rumours.ans;
            if (qty < 3)
            {
                link.l1 = HeroStringReactionRepeat(answ[0], answ[1], answ[2], "", NPChar, Dialog.CurrentNode);
                link.l1.go = qty != 2 ? "Rumours " + NPChar.Quest.repeat.Rumours : "Exit";
                if (qty != 2)
                {
                    link.l2 = DLG_Convert("Alone_Citiz_Rumours_Bye", "Dialogs\Encounters\Alone_Citiz.txt");
                    link.l2.go = "Exit";
                }
            }
            else
            {
                link.l1 = DLG_Convert("Alone_Citiz_Rumours_Block_Ok", "Dialogs\Encounters\Alone_Citiz.txt");;
                link.l1.go = "Exit";
            }
		break;

        case "Robbery":
            if (1 + rand(99) > JungWalker_RobberyChance())
            {
                NPChar.RobberyFail = ""; // Флаг, что была неудачная попытка ограбить
                Notification(DLG_Convert("Alone_Citiz_Bullying_Fail", "Dialogs\Encounters\Alone_Citiz.txt"), "Rats");
                dialog.text = DLG_Convert("Alone_Citiz_Robbery_text_1", "Dialogs\Encounters\Alone_Citiz.txt");
                link.l0 = DLG_Convert("Alone_Citiz_Robbery_l1", "Dialogs\Encounters\Alone_Citiz.txt");
                link.l0.go = "WalkerEscape";
                break;
            }

            NextDiag.TempNode = "AfterRobbery";
            Notification(DLG_Convert("Alone_Citiz_Bullying_Success", "Dialogs\Encounters\Alone_Citiz.txt"), "Berserker");
            dialog.text = DLG_Convert("Alone_Citiz_Robbery_text_2", "Dialogs\Encounters\Alone_Citiz.txt");
            link.l0 = DLG_Convert("Alone_Citiz_Robbery_l2", "Dialogs\Encounters\Alone_Citiz.txt");
            link.l0.go = "ExitJewel";
        break;

		case "AfterRobbery":
            NextDiag.TempNode = "AfterRobbery";
            dialog.text = DLG_Convert("Alone_Citiz_AfterRobbery_text_1", "Dialogs\Encounters\Alone_Citiz.txt");
            link.l0 = DLG_Convert("Alone_Citiz_AfterRobbery_l1", "Dialogs\Encounters\Alone_Citiz.txt");
            link.l0.go = "Exit";
		break;

		case "WalkerEscape":
            AddCharacterExpToSkill(PChar, SKILL_SNEAK, 15);
            ChangeCharacterNationReputation(PChar, int(NPChar.Nation), -3);
            ChangeCharacterComplexReputation(PChar, "nobility", -2);
			NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
            JungWalker_Escape(NPChar);
		break;

		case "ExitJewel":
            // Затереть по выходу с локации
            NPChar.LifeDay = 0;
            // Добыча
            TakeNItems(PChar, "jewelry"+(36 + hrand(14)), 1 + hrand(1));
            TakeNItems(PChar, "jewelry"+(36 + hrand(14)), hrand(1));
            TakeNItems(PChar, "jewelry"+(36 + hrand(14)), hrand(1));
            // Для слухов о грабеже, если не будет убит
            string QuestName = "Quest.Alone_Citiz_" + NPChar.id;
            QuestName += (QuestName + "_Clear" in PChar) ? "_Clear" : "_DelayClear";
            aref arClearCond = &PChar.(QuestName);
            arClearCond.RobberySuccess = true;
            // Экспа и репутация
            AddCharacterExpToSkill(PChar, SKILL_SNEAK, 10);
            ChangeCharacterNationReputation(PChar, int(NPChar.Nation), -1);
            ChangeCharacterComplexReputation(PChar, "nobility", -1);
            //
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

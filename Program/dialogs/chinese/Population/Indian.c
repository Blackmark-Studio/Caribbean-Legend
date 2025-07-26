// 杰森街头印第安人通用对话
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
            dialog.text = NPCStringReactionRepeat(""+ GetSexPhrase("白皮肤的家伙","白皮肤的女人") +"想说话? ", 
                "又是你, "+ GetSexPhrase("白皮肤的家伙","白皮肤的女人") +"。 ", 
                ""+ GetSexPhrase("白皮肤的家伙像女人一样爱说话。 ","白皮肤的女人就爱说话。 ") +"",
                "伟大的神灵把白皮肤的" + GetSexPhrase("兄弟","姐妹") + "带到了我面前。 ", "block", 1, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat("是的。 ", 
                "对, 又是我。 ",
                "真有诗意。 ", 
                "我也很高兴见到你。 ", npchar, Dialog.CurrentNode);
            link.l1.go = "exit";
            
            if (npchar.quest.meeting == "0")
            {
                dialog.text = "你好, 白皮肤的兄弟。 你想和印第安人说话吗? ";
                link.l1 = "问候你, 丛林之子。 很高兴见到你, 但我得走了。 ";
                link.l1.go = "exit";
                npchar.quest.meeting = "1";
            }
            NextDiag.TempNode = "First time";
        break;

        // 公民角色对露出武器的评论
        case "CitizenNotBlade":
            dialog.text = NPCharSexPhrase(NPChar, "别惹神灵, 白皮肤的家伙! 收起长刀! ", "别赶着去死, 白皮肤的家伙! 收起长刀! ");
            link.l1 = LinkRandPhrase("好的。 ", "如你所愿。 ", "如你所说。 ");
            link.l1.go = "exit";
        break;

        case "Exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;
    }
}
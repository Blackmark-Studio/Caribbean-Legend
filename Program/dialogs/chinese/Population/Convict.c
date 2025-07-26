// 矿场获释囚犯对话
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
            dialog.text = NPCStringReactionRepeat("又是你, 先生? ", 
                "听着, 先生, 你最好走开... ", 
                "别烦我, 先生! 我恳请你。 ",
                "哦, 我受不了了... 哪怕是在划桨船上当苦力都比这强。 ", "block", 1, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat("是的, 又是我。 ", 
                "别对我指手画脚。 ",
                "要是我偏要烦你呢? ", 
                "那你就回划桨船去吧! ", npchar, Dialog.CurrentNode);
            link.l1.go = "exit";
            
            if (npchar.quest.meeting == "0")
            {
                dialog.text = "你想要什么, 先生? ";
                link.l1 = "从你这儿? 我想没什么。 只是想打个招呼。 ";
                link.l1.go = "exit";
                npchar.quest.meeting = "1";
            }
            NextDiag.TempNode = "First time";
        break;

        // 公民角色对露出武器的评论
        case "CitizenNotBlade":
            dialog.text = NPCharSexPhrase(NPChar, "别挑战命运, 伙计! 收起你的武器! ", "听着, 我是这个镇的公民, 我请求你把剑收起来。 ");
            link.l1 = LinkRandPhrase("好吧... ", "如你所愿... ", "如你所说... ");
            link.l1.go = "exit";
        break;

        case "Exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;
    }
}
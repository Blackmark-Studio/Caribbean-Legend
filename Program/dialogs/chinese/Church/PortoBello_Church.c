// 城市相关对话
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
    {
        case "quests":
            dialog.text = NPCStringReactionRepeat(RandPhraseSimple("什么问题, "+ GetSexPhrase("我的孩子","我的孩子") +"?", "请问吧, 我在听... "), "我在听, 请说, "+ GetSexPhrase("我的孩子","我的孩子") +"... ", "第三次了, "+ GetSexPhrase("我的孩子","我的孩子") +", 问你需要什么。 ",
                          "神职人员有很多工作, 而你在分散我的注意力, "+ GetSexPhrase("我的孩子","我的孩子") +"... ", "block", 1, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了... ", "现在不了, 神父... "), "我没什么要说的, 抱歉。 ",
                      "我会问的, 但不是现在。 原谅我, 神父。 ", "请原谅我, 神父... ", npchar, Dialog.CurrentNode);
            link.l1.go = "exit";
        break;
    }
    UnloadSegment(NPChar.FileDialog2);  // 如果switch内部某处通过return退出, 别忘了进行卸载
}
// 城市对话处理
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
    {
        case "quests":
            dialog.text = NPCStringReactionRepeat(RandPhraseSimple("什么样的问题, " + GetSexPhrase("我的孩子", "我的孩子") + "?", "说吧, 我在听... "), "我在听, 现在说吧, " + GetSexPhrase("我的孩子", "我的孩子") + "... ", "这是第三次了, " + GetSexPhrase("我的孩子", "我的孩子") + ", 说出你需要什么。 ",
                          "神职人员有很多工作, 而你在打扰我, " + GetSexPhrase("我的孩子", "我的孩子") + "... ", "block", 1, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了... ", "现在不了, 神父... "), "我没什么要说的, 抱歉。 ",
                      "我会问的, 但稍后。 请原谅我, 神父。 ", "请原谅我, 神父... ", npchar, Dialog.CurrentNode);
            link.l1.go = "exit";
        break;
    }
    UnloadSegment(NPChar.FileDialog2);  // 如果在switch内部的某个地方通过return退出, 别忘了进行卸载
}
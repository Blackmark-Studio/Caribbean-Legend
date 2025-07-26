// 城市相关对话
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
    {
        case "quests":
            dialog.text = NPCStringReactionRepeat(RandPhraseSimple("你想要什么? 直接问吧。 ", "我在听, 你有什么问题? "), "这是你第二次试图问我... ", "这是你第三次试图问我... ",
                          "这要到什么时候才结束? ! 我是个大忙人, 忙着处理殖民地事务, 而你还在烦我! ", "block", 1, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了, 抱歉。 ", "现在不行。 地点和时间都不对。 "), "确实, 我现在没什么要说的, 抱歉。 ",
                      "我稍后再问。 ", "对不起, " + GetAddress_FormToNPC(NPChar) + "... ", npchar, Dialog.CurrentNode);
            link.l1.go = "exit";
        break;
    }
    UnloadSegment(NPChar.FileDialog2);  // 如果在switch内部的某个地方通过return退出, 别忘了进行卸载
}
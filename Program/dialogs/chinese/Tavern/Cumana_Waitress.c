// 城市对话处理
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
    {
        case "quests":
            dialog.text = NPCStringReactionRepeat(RandPhraseSimple("有问题吗, " + GetAddress_Form(NPChar) + "? ", "我能为你做什么, " + GetAddress_Form(NPChar) + "? "), "" + GetSexPhrase("嗯, 你打什么主意, " + GetAddress_Form(NPChar) + "? ", "又来问奇怪的问题? 伙计, 去喝点朗姆酒什么的吧... ") + "", "一整天里, 这已经是你第三次问这类问题了... " + GetSexPhrase(" 这是在刷存在感吗? ", ""),
                          "我猜你又有问题要问吧, " + GetAddress_Form(NPChar) + "? ", "block", 1, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了", "我现在没什么想聊的。 "), "不, 没什么要紧的... ",
                      "没门儿, 亲爱的... ", "不, 什么问题? ... ", npchar, Dialog.CurrentNode);
            link.l1.go = "exit";
        break;
    }
    UnloadSegment(NPChar.FileDialog2);  // 如果在switch中某处通过return退出, 别忘了执行卸载
}
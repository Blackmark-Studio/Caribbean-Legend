// 城市对话处理
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
    {
        case "quests":
            dialog.text = NPCStringReactionRepeat(RandPhraseSimple("有什么问题吗, " + GetAddress_Form(NPChar) + "? ", "需要我帮什么忙, " + GetAddress_Form(NPChar) + "? "), "" + GetSexPhrase("嗯, 你到底想干什么, " + GetAddress_Form(NPChar) + "? ", "又是这些奇怪的问题? 伙计, 去喝杯朗姆酒什么的吧... ") + "", "一整天下来, 这已经是你第三次问问题了... " + GetSexPhrase(" 这是在引起注意吗? ", ""),
                          "我猜你又有问题要问, " + GetAddress_Form(NPChar) + "? ", "block", 1, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了", "我现在没什么好说的。 "), "不, 没什么要紧的... ",
                      "没门儿, 亲爱的... ", "不, 什么问题? ... ", npchar, Dialog.CurrentNode);
            link.l1.go = "exit";
        break;
    }
    UnloadSegment(NPChar.FileDialog2);  // 如果在switch中某个地方通过return退出, 别忘了做卸载
}
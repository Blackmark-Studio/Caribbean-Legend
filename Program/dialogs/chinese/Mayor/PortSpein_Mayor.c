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
            if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
            {
                link.l1 = "阁下, 1654年4月有一艘护卫舰由米格尔.迪乔索指挥。 从那以后他就失踪了。 您还记得关于他的任何事情吗? 也许他拜访过您, 谈过话... ";
                link.l1.go = "guardoftruth";
            }
        break;
        
        case "guardoftruth":
            dialog.text = "是的, 我记得那个人。 但我不记得关于他的任何细节。 他来过这里, 然后就离开了。 我帮不了你。 ";
            link.l1 = "我明白了。 抱歉打扰您了。 ";
            link.l1.go = "exit";
            npchar.quest.guardoftruth = "true";
        break;
    }
    UnloadSegment(NPChar.FileDialog2);  // 如果在switch内部的某个地方通过return退出, 别忘了进行卸载
}
// 城市对话处理
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
    {
        case "quests":
            dialog.text = NPCStringReactionRepeat("关于" + GetCityName(npchar.city) + "的所有传闻都为您效劳。 您想了解什么? ",
                          "我们刚才还在说这个呢。 您一定是忘了... ", "今天这已经是您第三次问这类问题了... ",
                          "您像只鹦鹉一样反复问同样的话... ", "block", 1, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat("您知道吗, " + Npchar.name+ ", 或许下次吧。 ", "对, 不知怎么的我就忘了... ",
                      "是的, 确实是第三次了... ", "嗯... ", npchar, Dialog.CurrentNode);
            link.l1.go = "exit";
            if (pchar.questTemp.Slavetrader == "FindRatJamaica")
            {
                link.l1 = "您碰巧知道我在哪里可以找到弗朗索瓦.贡捷吗? ";
                link.l1.go = "Jamaica_ratP_1";
            }
            // 真理守护者
            if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok" && !CheckAttribute(npchar, "quest.jino"))
            {
                link.l1 = "听着, 有没有一位炼金术士, 或者说医师, 到这个镇上来? 他是意大利人, 大约三十岁, 名叫吉诺.格维内利。 您听说过吗? ";
                link.l1.go = "guardoftruth";
            }
        break;

        case "Jamaica_ratP_1":
            dialog.text = NPCStringReactionRepeat("我完全不知道。 我甚至从没听过这个名字。 ", "您已经问过了, 我也回答过您了。 ", "我告诉过您, 您已经问过那个贡捷了。 ", "听着, 走开别烦我! 您是不是完全昏了头? ", "block", 0, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat("那好吧, 我会继续找的。 ", "嗯, 我想是吧... ", "是的, 对, 我问过... ", "抱歉, " + npchar.name+ "... ", npchar, Dialog.CurrentNode);
        break;
        
        case "guardoftruth":
            dialog.text = LinkRandPhrase("不, 没听说过。 我们这儿有草药师和医师, 但没有叫这个名字的。 ", "这是我第一次听到这么奇怪的名字。 不, 我们这儿从没来过您说的那个人。 ", "我们这儿根本没有炼金术士。 我们有医师, 但没有叫这么奇怪名字的。 ");
            link.l1 = "明白了。 真遗憾。 我会继续寻找的! ";
            link.l1.go = "exit";
            npchar.quest.jino = "true";
        break;
    }
    UnloadSegment(NPChar.FileDialog2);  // 如果在switch中某处通过return退出, 别忘了执行卸载
}
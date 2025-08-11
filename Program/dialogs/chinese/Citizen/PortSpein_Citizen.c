// 城市对话处理
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
    {
        case "quests":
            dialog.text = RandPhraseSimple("什么问题? ", "你想做什么? ");
            link.l1 = RandPhraseSimple("我改变主意了。 ", "我现在没什么可说的。 ");
            link.l1.go = "exit";
            // 笑声的代价
            if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
            {
                link.l1 = "告诉我, ‘胡安’这个名字有印象吗? ";
                link.l1.go = "Consumption";
            }
            if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
            {
                link.l1 = "听着, 伙计, 1654年4月, 一艘由米格尔.迪乔索指挥的护卫舰停泊在这个港口。 他在那天失踪了。 你还记得什么相关的事情吗? ";
                link.l1.go = "guardoftruth";
            }
        break;
        
        case "info":
        // 替换为某些NPC的描述, 关于任务
            dialog.text = "你以为我是" + NationNameGenitive(sti(NPChar.nation)) + "的特工吗? ";
            link.l1 = "好吧... 不是。 那么再见。 ";
            link.l1.go = "exit";
            link.l2 = "那么, 还有其他问题吗? ";
            link.l2.go = "new question";
        break;
        
        case "town":
        // 替换为如何通行的描述, 关于任务
            dialog.text = "我看起来像调查局的人吗? 我不知道, 什么都不知道。 ";

            link.l1 = "你真是个糊涂虫! 走开。 ";
            link.l1.go = "exit";
            link.l2 = "那么, 还有其他问题吗? ";
            link.l2.go = "new question";
        break;
        
        // 笑声的代价
        case "Consumption":
            dialog.text = "你在开玩笑吗? 每个殖民地都有二十多个胡安! ";
            link.l1 = "我知道了。 抱歉打扰... ";
            link.l1.go = "exit";
            npchar.quest.Consumption = "true";
        break;
        
        // 真理守护者
        case "guardoftruth":
            dialog.text = LinkRandPhrase("得了吧, 船长! 你觉得我会记得这种事? ", "对不起, 先生, 我帮不了你。 ", "先生, 你真觉得我会记得这种琐事? 我自己的麻烦已经够多了。 ");
            link.l1 = LinkRandPhrase("我知道了。 抱歉打扰... ", "真遗憾, 再见。 ", "好吧, 再见... ");
            link.l1.go = "exit";
            npchar.quest.guardoftruth = "true";
        break;
    }
    UnloadSegment(NPChar.FileDialog2);  // 若switch内部某处通过return退出, 切记执行卸载
}
// 城市对话处理
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("你有什么问题吗? ", "我能帮你什么忙? "), "你刚才已经问过我问题了... ", "在我的造船厂或是这个镇上的任何地方, 我从未见过如此好奇的人。 ",
                          "问这么多问题干什么? 我的工作是造船。 我们还是专注于此吧。 ", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了... ", "我现在没什么好说的。 "), "嗯, 我的记性去哪儿了... ",
                      "嗯, 好吧... ", "继续... ", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// 2016-1 附加内容 Jason 海盗系列
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_2")
            {
                link.l1 = "听着, 师傅, 你在这里造船, 对吗? ... 也换船帆... 你有没有想过... 用更好的帆布材料? ";
                link.l1.go = "mtraxx";
			}
		break;
		
		// 2016-1 附加内容 Jason 海盗系列
		case "mtraxx":
            dialog.text = "先生, 你说话像在猜谜... 坦率地说, 你来这里想干什么? 别担心, 我不是什么文书, 这里也不是海关。 ";
			link.l1 = "啊, 很高兴我们想法一致! 先生, 丝绸帆布。 据我所知, 如果追求速度, 没有比这更好的帆材料了。 ";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
            dialog.text = "不仅是速度, 还有它的迎风航行能力。 你是要卖船用丝绸吗? 这确实是贵重货物。 但有个障碍: 我根本不知道如何在生产中使用它。 你明白吗? 这种材料需要非常特殊的能力和技能, 而我没有。 老实说, 我的造船厂有完全不同的专业领域, 如果你给我提供俄罗斯帝国的绳索, 不管价格如何, 我都会欣然买下所有。 我们一直需要绳索, 但这里不需要船用丝绸, 很抱歉! ";
			link.l1 = "嗯, 我明白了。 谢谢你的时间, 师傅。 祝你好运! ";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            DialogExit();
			AddQuestRecord("Roger_2", "4");
			pchar.questTemp.Mtraxx = "silk_3";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // 如果在switch中某个地方通过return退出, 别忘了进行卸载
}
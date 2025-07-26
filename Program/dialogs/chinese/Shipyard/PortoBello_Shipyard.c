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
			if (pchar.questTemp.Slavetrader == "FindRatPortobello")
            {
                link.l1 = "听着, 有没有一个叫弗朗索瓦.贡捷的私掠者偶然来找过你? 我知道他最近在贝洛港。 ";
                link.l1.go = "Portobello_ratS_1";
            }
		break;
		
		case "Portobello_ratS_1":
			dialog.text = "他来过。 他从我这里买了一艘护卫舰, 然后很快就出海了。 ";
			link.l1 = "谢谢! 你知道他去了哪里吗? ";
			link.l1.go = "Portobello_ratS_2";
		break;
			
		case "Portobello_ratS_2":
			dialog.text = "不, 伙计, 我一点头绪也没有。 我修理和出售船只, 但不跟踪它们去哪里。 这不关我的事。 ";
			link.l1 = "好吧, 谢谢... 让我们看看你去了哪里... ";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "FindRatPortobello_1";
			AddQuestRecord("Slavetrader", "21_2");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // 如果在switch中某个地方通过return退出, 别忘了进行卸载
}
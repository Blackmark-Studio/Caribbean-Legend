// 城市相关对话
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("说吧, 你想要什么? ",
                          "我们刚刚还在谈论这个。 你一定是忘了... ", "这是你今天第三次问我问题了... ",
                          "听着, 这是一家商店。 人们在这里买东西。 别打扰我! ", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("你知道的, " + Npchar.name+ ", 也许下次吧。 ", "是的, 不知为什么我忘了... ",
                      "是的, 这确实是第三次了... ", "嗯, 我不会了... ", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// 哄笑的代价
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "告诉我, 胡安这个名字对你有什么意义吗? ";
				link.l1.go = "Consumption";
			}
			if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "1654年4月, 一艘护卫舰在米格尔.迪乔索船长的指挥下停靠在你的港口, 之后他就失踪了。 他的名字有印象吗? 也许他从你这里购买过一些商品, 或者说过什么... ";
				link.l1.go = "guardoftruth";
			}
		break;
		
		// 哄笑的代价
		case "Consumption":
			dialog.text = "哦, 得了吧, 船长! 今天我的店里刚来了两个叫胡安的, 昨天还有一个。 怎么, 我得记住每一个人吗? ";
			link.l1 = "好吧。 抱歉打扰你了... ";
			link.l1.go = "exit";
			npchar.quest.Consumption = "true";
		break;
		
		case "guardoftruth":
			dialog.text = "哦, 船长, 那段时间有太多的护卫舰和大帆船进出这里, 有米格尔也有卡洛斯... ";
			link.l1 = "我明白了。 那么, 你帮不了什么忙... ";
			link.l1.go = "exit";
			npchar.quest.guardoftruth = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
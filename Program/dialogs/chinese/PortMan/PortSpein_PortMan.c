// 城市相关对话
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("什么问题? ", "你想要什么, " + GetAddress_Form(NPChar) + "? "), "你已经试过问我问题了, " + GetAddress_Form(NPChar) + "... ", "你今天已经第三次谈论某个问题了... ",
                          "听着, 如果你没有关于港口事务的事情告诉我, 就别用问题打扰我。 ", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了。 ", "我没什么可谈的。 "), "没关系。 ", "确实, 已经第三次了... ", "抱歉, 但我现在对港口事务不感兴趣。 ", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// 笑声的代价
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "告诉我,'胡安'这个名字对你有什么意义吗? ";
				link.l1.go = "Consumption";
			}
			if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "先生, 1654年4月有一艘护卫舰在米格尔.迪乔索的指挥下停在这里。 然后他就失踪了。 你还记得关于这件事的任何信息吗? 也许迪乔索来过这里并登记了他的船... ";
				link.l1.go = "guardoftruth";
			}
		break;
		
		// 笑声的代价
		case "Consumption":
			dialog.text = "胡安? 就这些? 先生, 你是喝醉了还是在跟我开愚蠢的玩笑? 你能记得他的姓氏或者至少他的船名吗? 看在上帝的份上, 这是西班牙殖民地。 你知道这里有多少个胡安吗? 没有任何细节我帮不了你。 ";
			link.l1 = "我明白了。 抱歉打扰你了... ";
			link.l1.go = "exit";
			pchar.questTemp.Consumption.AskJuan = sti(pchar.questTemp.Consumption.AskJuan)+1;
			if(sti(pchar.questTemp.Consumption.AskJuan) == 3)
			{
				pchar.quest.Consumption2.win_condition.l1 = "location";
				pchar.quest.Consumption2.win_condition.l1.location = "PortSpein_town";
				pchar.quest.Consumption2.function = "Consumption_CreateSergio";
			}
			npchar.quest.Consumption = "true";
		break;
		
		case "guardoftruth":
			dialog.text = "让我看看我的笔记... 啊哈! 是的, 米格尔.迪乔索船长在1654年4月乘坐护卫舰'圣奎特里亚'来到这里。 他登记来自圣安德烈斯-普罗维登斯殖民地。 他正前往西班牙加的斯。 于1654年4月14日起航。 我知道的就这些。 ";
			link.l1 = "驶向欧洲? 我明白了。 谢谢! ";
			link.l1.go = "exit";
			npchar.quest.guardoftruth = "true";
			AddQuestRecord("Guardoftruth", "39");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // 如果switch内部某处通过return退出, 别忘了进行卸载
}
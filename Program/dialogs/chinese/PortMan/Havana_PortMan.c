// 城市相关对话
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("什么问题? ", "你想要什么, " + GetAddress_Form(NPChar) + "? "), "你已经试过问我问题了, " + GetAddress_Form(NPChar) + "... ", "你今天已经第三次谈论某个问题了... ",
                          "听着, 如果你没有关于港口事务的事情告诉我, 就别用你的问题打扰我。 ", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了。 ", "我没什么可谈的。 "), "没关系。 ", "确实, 已经第三次了... ", "抱歉, 但我现在对港口事务不感兴趣。 ", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatHavana")
            {
                link.l1 = "日安。 我想了解一艘名为‘" + pchar.questTemp.Slavetrader.ShipName + "’。 由弗朗索瓦.贡捷指挥的护卫舰的情况。 ";
                link.l1.go = "Havana_ratP_1";
			}
			// 卡勒幽船
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "打扰一下, 请问有个叫约阿希姆.梅里曼的人到你们港口了吗? 一位中年先生, 葡萄牙人, 留着小胡子。 帝王须, 还有一双锐利的眼睛? ";
				link.l1.go = "caleuche";
			}
			// Addon 2016-1 Jason 海盗系列
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_3" && !CheckAttribute(npchar, "quest.Mtraxx"))
			{
				link.l1 = "我对一艘名为‘Cantavro’的船很感兴趣。 我在找它的船长 --埃斯贝尔多.卡巴纳斯, 有私事要找他。 你能帮我吗? ";
				link.l1.go = "mtraxx";
			}
		break;
		
		case "Havana_ratP_1":
			dialog.text = NPCStringReactionRepeat("是的, 他来过这里。 但已经离开了。 去问我们的酒馆老板吧, 他在楼上租了个房间。 ", "你已经问过这个问题了, 我也回答过了。 ", "我告诉过你, 你已经问过这个贡捷了... ", "请别打扰我! ", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("谢谢。 我会去问的。 ", "嗯, 好吧... ", "是的, 我确实问过... ", "抱歉, " + npchar.name+ "... ", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		
		// 卡勒幽船
		case "caleuche":
			dialog.text = "我对他一无所知。 就算他来了, 也从没在任何地方登记过。 ";
			link.l1 = "我知道了。 真遗憾... 好吧, 我会继续寻找... ";
			link.l1.go = "exit";
			npchar.quest.caleuche = "true";
		break;
		
		// Addon 2016-1 Jason 海盗系列
		case "mtraxx":
			dialog.text = "让我想想... 双桅纵帆船‘Cantavro’两天前起航执行巡逻任务了... 不过, 位置没有记录。 这是一艘军用船只, 所以目的地只有船长和堡垒指挥官知道。 我建议你直接和指挥官谈谈, 如果你想知道更多的话, 可以在堡垒找到他。 不幸的是, 我能为你做的只有这些了。 ";
			link.l1 = "我明白了。 好吧, 谢谢你抽出时间... ";
			link.l1.go = "exit";
			npchar.quest.Mtraxx = "true";
			AddQuestRecord("Roger_1", "5");
			DelLandQuestMark(npchar);
			AddLandQuestMark(characterFromId("Havana_tavernkeeper"), "questmarkmain");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // 如果switch内部某处通过return退出, 别忘了进行卸载
}
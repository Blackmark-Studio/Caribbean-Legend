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
			if (CheckAttribute(pchar, "questTemp.Mtraxx"))
            {
				if (pchar.questTemp.Mtraxx == "silk_2" || pchar.questTemp.Mtraxx == "silk_3")
				{
					link.l1 = "我听说这家造船厂能提高船只的航行速度。 这需要一些非常罕见的丝绸帆布。 你想... 谈谈这个吗? ";
					link.l1.go = "mtraxx";
				}
			}
			if (CheckAttribute(npchar, "quest.upgradeship")) {
				link.l2 = "我是麦克阿瑟小姐派来的, 关于... ";
				link.l2.go = "helen_upgradeship";
			}
			
			if (CheckAttribute(npchar, "quest.upgradeship.money") && HelenCanUpgrade()) {
				link.l2 = "开始对船只进行大修! ";
				link.l2.go = "helen_upgradeship_money";
			}
		break;
		
		// 2016-1 附加内容 Jason 海盗系列
		case "mtraxx":
            dialog.text = "年轻人, 你能说清楚一点吗? 你到底为什么来这里? 如果你想改进你的船 - 我们马上开始谈正事。 ";
			link.l1 = "不完全是。 你提供的那种服务需要商店里没有的货物。 我想向你提供你可能需要的那种材料。 ";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
            dialog.text = "哦... 嗯... 你知道只有这个殖民地的当局才被允许处理这种战略物资吗? 你可以提供自己的丝绸让我来改进你的船, 但是, 出售它是严格禁止的。 从我这里购买也是一样 - 这种活动会被处以重罚。 ";
			link.l1 = "嗯, 这里既不是商店, 也不是海关... ";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = "我所有的丝绸帆布都是直接从客户那里获得的, 或者通过总督的特别许可购买有限的数量。 如果你没有其他问题, 请让我继续工作。 ";
			link.l1 = "嗯... 很好。 祝你今天愉快, 师傅。 ";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            DialogExit();
			AddQuestRecord("Roger_2", "5");
			pchar.questTemp.Mtraxx = "silk_4";
		break;
		
		case "helen_upgradeship":
			dialog.text = "哦, 我知道! 你真幸运, 船长。 是关于船只的全面大修吗? 我们会处理好一切的; 我们的造船厂和普利茅斯的一样好! ";
			link.l1 = "我想这不会是免费的服务吧? ";
			link.l1.go = "helen_upgradeship_1";
		break;
		
		case "helen_upgradeship_1":
			dialog.text = "当然, 船长, 这样的服务不可能是免费的, 即使对克伦威尔也不行! 但是, 我说话算数, 只收钱 - 你不必走私违禁品。 ";
			link.l1 = "可以理解。 多少钱? ";
			link.l1.go = "helen_upgradeship_2";
		break;
		
		case "helen_upgradeship_2":
			dialog.text = "这取决于你的旗舰的大小, 船长。 一级船要花你五千枚杜布隆金币, 而五级船 - 只需要一千枚。 ";
			link.l1 = "好吧, 我做决定后就来找你。 ";
			link.l1.go = "exit";
			
			npchar.quest.upgradeship.money = true;
		break;
		
		case "helen_upgradeship_money":
			dialog.text = "太好了, 现在我需要的一切都有了。 那么, 我开始工作了。 ";
			link.l1 = "我等着。 ";
			link.l1.go = "helen_upgradeship_money_1";
			
			iTemp = GetCharacterShipType(pchar);
			sld = GetRealShip(iTemp);
			iTemp = (7 - sti(sld.class)) * 1000;
			RemoveDublonsFromPCharTotal(iTemp);
		break;
		
		case "helen_upgradeship_money_1":
			AddTimeToCurrent(6, 30);
			dialog.text = "... 我想就这样了... 质量有保证。 ";
			link.l1 = "谢谢! 我会检查的。 ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenUpgradeShip2");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // 如果在switch中某个地方通过return退出, 别忘了进行卸载
}

bool HelenCanUpgrade() {
	int shipIndex = GetCharacterShipType(pchar);
	if (shipIndex == SHIP_NOTUSED) {
		return false;
	}
	
	sld = GetRealShip(shipIndex);
	if (sti(sld.class) == 7) {
		return false;
	}
	
	int cost = (7 - sti(sld.class)) * 1000;
	return (PCharDublonsTotal() >= cost);
}
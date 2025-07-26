// 城市对话处理
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("你有什么问题吗? ", "我能为你做些什么? "), "你刚才已经问过我问题了... ", "在我的造船厂或是镇上其他任何地方, 我从未见过如此好奇的人。 ",
                          "问这么多问题做什么? 我的工作是造船, 咱们还是专注于此吧。 ", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了... ", "我现在没什么可聊的。 "), "嗯, 我的记性去哪儿了... ",
                      "嗯, 好吧... ", "继续... ", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// 荷兰 Gambit (荷兰策略) 
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "我正载着一批咖啡前往布鲁维尔德, 想再多买些货物, 但问题是: 我从一个退伍军人那里买的这艘双桅横帆船, 装了24门重炮, 数量多到吓人。 你知道, 我又不是去参战。 我想把这些炮全卖给你, 然后买12门六磅炮 --吓唬海盗足够用了。 剩下的空间我要装货物。 ";
                link.l1.go = "ShipyardDone";
			}
		break;
		
		case "ShipyardDone":
			dialog.text = "行, 卖吧。 我这儿六磅炮一直很充足, 但重炮总是缺, 因为大家都在买却没人愿意卖, 除非是彻底报废的。 所以如果你的重炮还能正常使用, 我会给你合适的价格。 ";
			link.l1 = "哇, 太好了! 我马上就下令处理。 ";
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-10");
			DelLandQuestMark(npchar);
			if (sti(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7) 
			{
			AddQuestRecord("Holl_Gambit", "2-6");
			pchar.quest.GotoBridgetownOver.over = "yes";//移除计时器
			DelMapQuestMarkCity("Bridgetown");
			pchar.questTemp.HWIC.Eng = "SeekVanBerg";
				pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
				pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
				//如果(RealShips[sti(pchar.ship.type)].basetype不等于SHIP_VALCIRIA 或者 GetCompanionQuantity(pchar) > 1) 则添加对话退出任务函数("FailVanBergInWorld");
				//否则添加对话退出任务函数("CreateVanBergInWorld");
			}
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // 如果在switch中某处通过return退出, 别忘了执行卸载
}
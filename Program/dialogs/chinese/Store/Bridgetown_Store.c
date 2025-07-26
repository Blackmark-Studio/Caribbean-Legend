// 城市相关对话
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("说吧, 你想要什么? ",
                          "我们刚聊过这个。 你肯定是忘了... ", "这已经是今天你第三次问这类问题了... ",
                          "听着, 这是商店。 人们来这儿买东西。 别打扰我! ", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("你知道吗, " + Npchar.name+ ", 或许下次吧。 ", "对, 不知怎么就忘了... ",
                      "是啊, 真的是第三次了... ", "嗯, 我不会了... ", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//荷兰 Gambit (荷兰策略) 
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "听着, 有消息说伯利兹的红木和可可价格很快就会暴涨。 我最近做了笔好生意, 赚了不少金币, 嘿嘿... 我想采购一些这批货。 能给我打折吗? ";
                link.l1.go = "StoreDone";
            }
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "barbados1")
			{
				link.l1 = "最近有艘名为‘令人钦佩’的大帆船在盖乌斯.马沙船长的指挥下停靠在你的殖民地。 告诉我, 他有没有在这里储备弹药或用于转售的商品? ";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "StoreDone":
			dialog.text = "好吧, 先生, 如果批量确实很大, 那我们当然可以商量一个合理的折扣。 ";
			link.l1 = "太好了! 我听说造船厂很快就会有新的弗鲁伊特帆船出售。 我会等着买那艘船。 尽管我已经把双桅横帆船上的所有加农炮都拆了, 但货舱还是装不下所有这些货物! 我稍后再来! ";
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-11");
			DelLandQuestMark(npchar);
			if (sti(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7) 
			{
				AddQuestRecord("Holl_Gambit", "2-6");
				pchar.questTemp.HWIC.Eng = "SeekVanBerg";
				pchar.quest.GotoBridgetownOver.over = "yes";//取消计时器
				DelMapQuestMarkCity("Bridgetown");
				pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
				pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "哈! 我记得那个奇怪的家伙! 他听信了一些愚蠢的传言, 说瓜德罗普会急需香草, 因为有一队欧洲大商人将在那里停留, 尽可能多地购买香料。 我每个月都听到这种无稽之谈, 但马沙却把这当真了。 他在这里待了一个星期, 让我收集足够装满他货舱的香草。 看来他把所有的钱都花在这上面了。 我为那个人感到难过, 但如果人们想发疯, 我也阻止不了。 ";
			link.l1 = "那么, 他现在可能在瓜德罗普? ";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "很可能。 因为他会一直等待他幻想中的‘商人’, 直到基督再临, 而他卖香草只会赔钱。 如果他明智的话, 就会留在巴斯特尔, 直到香草需求激增, 或者确定有其他更需要香草的地方。 ";
			link.l1 = "好的。 谢谢你, 你帮了我大忙! ";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			DialogExit();
			AddQuestRecord("Guardoftruth", "14");
			pchar.questTemp.Guardoftruth = "guadeloupe";
			pchar.quest.GuardOT_guadeloupe.win_condition.l1 = "location";
			pchar.quest.GuardOT_guadeloupe.win_condition.l1.location = "guadeloupe";
			pchar.quest.GuardOT_guadeloupe.function = "GuardOT_CreateTwoShips";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
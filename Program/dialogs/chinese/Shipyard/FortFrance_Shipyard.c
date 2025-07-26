// 城市对话处理
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("你有什么问题吗? ", "我能为你做些什么? "), "你刚才已经问过我问题了... ", "在我的造船厂或是这个镇上的任何地方, 我从未见过如此好奇的人。 ",
                          "问这么多问题做什么? 我的工作是造船。 我们还是专注于此吧。 ", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了... ", "我现在没什么可聊的。 "), "嗯, 我的记性去哪儿了... ",
                      "嗯, 好吧... ", "继续... ", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// 2016年附加内容 Jason 海盗系列
			if (CheckAttribute(pchar, "questTemp.FMQM") && pchar.questTemp.FMQM == "begin")
            {
                link.l1 = "你的人告诉我你想见我。 我洗耳恭听。 ";
                link.l1.go = "FMQM";
            }
			if (CheckAttribute(pchar, "questTemp.FMQM") && pchar.questTemp.FMQM == "oil" && GetSquadronGoods(pchar, GOOD_OIL) >= 50)
            {
                link.l1 = "我完成任务了。 我的货舱里有" + FindRussianQtyString(GetSquadronGoods(pchar, GOOD_OIL)) + "桶树脂。 ";
                link.l1.go = "FMQM_9";
            }
		break;
		
		// 2016年附加内容 Jason 海盗系列
		case "FMQM":
			pchar.quest.FMQM_Denial.over = "yes";
			dialog.text = "是的是的, " +GetFullName(pchar)+ "船长。 我看到你的船驶入我们的港口, 立即派我的工人去找你。 那我们直奔主题: 你是新来的, 但大家都说你已经是个经验丰富的水手, 而且运气很好。 这就是为什么我要给你提个商业建议。 ";
			link.l1 = "有意思! 继续说, 告诉我。 ";
			link.l1.go = "FMQM_1";
			DelLandQuestMark(npchar);
		break;
		
		case "FMQM_1":
			dialog.text = "你听说过西班牙人在特立尼达岛生产的特殊树脂吗? 这是一种具有战略价值的稀有资源, 用于加固船体。 每桶都价值不菲, 因为西班牙人将所有树脂都用于海军需求。 简单地说, 每个殖民地当局都控制着这种商品的贸易, 这完全是走私品。 \n我需要这种树脂来完成一项特殊订单。 当然, 我们的商店没有, 当地的军用仓库也没有, 或者他们根本不想卖。 这其实无关紧要。 重要的是我需要树脂, 而且我知道哪里能弄到。 我只需要一个愿意登船突袭的船长。 ";
			link.l1 = "我想, 我开始明白你的意思了... ";
			link.l1.go = "FMQM_2";
		break;
		
		case "FMQM_2":
			dialog.text = "太好了。 现在听着, 一支小型贸易船队位于特立尼达附近, 或者更准确地说, 在圣何塞港。 其中一艘船载有一批不错的树脂, 就是我急需的那种树脂。 如果你喜欢掠夺我们国家敌人的想法, 我会告诉你更多。 你怎么说? ";
			link.l1 = "我喜欢你的提议。 我准备试试看。 ";
			link.l1.go = "FMQM_3";
			link.l2 = "我放弃, 先生。 我的船和船员目前状态不太好。 ";
			link.l2.go = "FMQM_exit";
		break;
		
		case "FMQM_exit":
			dialog.text = "好吧, 你有权做你想做的事。 抱歉占用你的时间, 船长。 ";
			link.l1 = "再见。 ";
			link.l1.go = "FMQM_exit_1";
		break;
		
		case "FMQM_exit_1":
			DialogExit();
			pchar.questTemp.FMQM = "fail";
			AddQuestRecord("FMQ_Martinique", "3");
			CloseQuestHeader("FMQ_Martinique");
		break;
		
		case "FMQM_3":
			string sTemp = "barquentine";
			if (MOD_SKILL_ENEMY_RATE < 7) sTemp = "barque";// 2016年附加内容 Jason 海盗系列
			dialog.text = "那听着: 船队由三艘船组成, 树脂会和其他货物一起装在一艘名为‘Bensecho’的" + sTemp + "上。 这是你的主要目标。 正如我之前所说, 西班牙人从特立尼达的圣何塞启航, 前往波多黎各的圣胡安。 他们明天启航, 所以你可以自由选择在哪里攻击他们。 ";
			link.l1 = "知道了。 报酬呢? ";
			link.l1.go = "FMQM_4";
		break;
		
		case "FMQM_4":
			dialog.text = "我只对树脂感兴趣。 每桶那种东西我会付15枚金杜布隆。 根据我的信息, ‘Bensecho’号载有大约100桶。 ";
			link.l1 = "天哪! 这可是一大笔钱! ";
			link.l1.go = "FMQM_5";
		break;
		
		case "FMQM_5":
			dialog.text = "是的。 我已经告诉过你, 这种特殊商品非常昂贵和稀有。 ";
			link.l1 = "你还告诉我这是走私品。 ";
			link.l1.go = "FMQM_6";
		break;
		
		case "FMQM_6":
			dialog.text = "别担心, 你不需要把它带到商店或走私者那里。 任务完成后来找我, 我们会把你的船停在我的造船厂修理, 然后在晚上秘密卸载所有货物。 没人会怀疑什么。 ";
			link.l1 = "你比我考虑得更周到, 师傅。 很好。 那就不浪费时间了。 我这就去启航。 ";
			link.l1.go = "FMQM_7";
		break;
		
		case "FMQM_7":
			dialog.text = "祝你好运, 船长。 ";
			link.l1 = "... ";
			link.l1.go = "FMQM_8";
		break;
		
		case "FMQM_8":
			DialogExit();
			pchar.questTemp.FMQM = "convoy";
			AddQuestRecord("FMQ_Martinique", "4");
			SetFunctionTimerCondition("FMQM_ConvoyStart", 0, 0, 1, false);
		break;
		
		case "FMQM_9":
			dialog.text = "太好了! 按照我们之前的约定, 把你的船停在船坞里。 我们今晚在那里卸货。 回到你的船上, 让我为你准备钱。 ";
			link.l1 = "那就这么办。 ";
			link.l1.go = "FMQM_10";
			DelLandQuestMark(npchar);
		break;
		
		case "FMQM_10":
			pchar.quest.FMQM_Late.over = "yes";
			DialogExit();
			InterfaceStates.Buttons.Save.enable = false;
			chrDisableReloadToLocation = true;
			pchar.GenQuest.FrameLockEsc = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
			pchar.questTemp.FMQM = "remove_oil";
			pchar.questTemp.FMQM.Oil = "true";
			pchar.questTemp.FMQM.Qty = GetSquadronGoods(pchar, GOOD_OIL);
			DoQuestFunctionDelay("FMQM_WaitTime", 1.0);
			RemoveCharacterGoods(pchar, GOOD_OIL, GetSquadronGoods(pchar, GOOD_OIL));
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // 如果在switch中某个地方通过return退出, 别忘了进行卸载
}
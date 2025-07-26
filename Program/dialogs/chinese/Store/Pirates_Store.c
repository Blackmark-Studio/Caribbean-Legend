// 城市相关对话
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	bool bOk;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("说吧, 你想要什么? ",
                          "我们刚聊过这个。 你肯定是忘了... ", "这已经是今天你第三次问这类问题了... ",
                          "听着, 这是商店。 人们来这儿买东西。 别打扰我! ", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("你知道吗, " + Npchar.name+ ", 或许下次吧。 ", "对, 不知怎么就忘了... ",
                      "是啊, 真的是第三次了... ", "嗯, 我不会了... ", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				link.l1 = "听着, " + npchar.name+ ", 你最近在宝藏岛见过米格尔.迪乔索吗? ";
				link.l1.go = "tieyasal";
			}
			// Addon 2016-1 Jason 海盗线
			if(CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "pasq_start")
			{
				link.l1 = "" + npchar.name+ ", 我代表马库斯.泰雷克斯来这里。 他说你需要一个人来做件事。 ";
				link.l1.go = "mtraxx";
			}
			if(CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "pasq_win")
			{
				link.l1 = "" + npchar.name+ ", ‘罗斯博霍姆号’已被找到并捕获。 我们该开始卸货和清点了吗? ";
				link.l1.go = "mtraxx_5";
			}
		break;
				
		// 玛雅城
		case "tieyasal":
			dialog.text = "是的, 我见过。 他在这里为他的船购买了补给。 顺便说一下, 这是最近的事。 你俩简直就是差了几天没遇上。 顺便说一句, 他可能还在这个定居点。 你知道, 我不帮人打探消息。 多问问周围的人, 说不准你就能找到你要找的先生。 ";
			link.l1 = "好的。 谢谢你的信息! ";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			DialogExit();
			npchar.quest.tieyasal = "true";
		break;
		
		// Addon 2016-1 Jason 海盗线
		case "mtraxx":
			pchar.quest.Mtraxx_PasqualeLate.over = "yes";
            dialog.text = "正是! 你及时赶到了, 这很好。 现在让我告诉你事情的关键... ";
			link.l1 = "我洗耳恭听。 ";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
			string sTemp = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.questTemp.Mtraxx.Crdn.Ship), "Name")));
            dialog.text = "目前, 一艘名为‘罗斯博霍姆号’的荷兰" + sTemp + ", 正与一艘护卫船一同抵达我们的海域。 它装载着乌木, 从威廉斯塔德出发, 将与另一艘护卫船汇合, 以确保前往欧洲的航行安全。 我不知道它会走什么路线, 是经过圣马丁还是西班牙岛, 但我知道它们的 rendezvous 点坐标\n你的任务是在那里找到荷兰人, 登上那艘商船, 并把货物带给我。 货物一送到, 我就付款。 ";
			link.l1 = "明白了。 时间和地点呢? ";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
			int i = sti(pchar.questTemp.Mtraxx.Crdn.minN2) - 10;
			int n = sti(pchar.questTemp.Mtraxx.Crdn.minW2) - 10;
            dialog.text = "" + sti(pchar.questTemp.Mtraxx.Crdn.degN) + " " + i + " 北, " + sti(pchar.questTemp.Mtraxx.Crdn.degW) + " " + n + " 西。 它一定在宝藏岛以南或西南的某个地方, 我不擅长这个, 我不是水手, 但你是。 你有大约五天的时间来完成这项任务。 ";
			link.l1 = "记下了... 我知道了。 那就不浪费时间了! ";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = "祝你好运, 船长。 我会等你和货物回来。 ";
			link.l1 = "... ";
			link.l1.go = "mtraxx_4";
		break;
		
		case "mtraxx_4":
           DialogExit();
		   pchar.questTemp.Mtraxx = "pasq_convoy";
		   i = sti(pchar.questTemp.Mtraxx.Crdn.minN2) - 10;
           n = sti(pchar.questTemp.Mtraxx.Crdn.minW2) - 10;
		   AddQuestRecord("Roger_4", "3");
		   AddQuestUserData("Roger_4", "sShip", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.questTemp.Mtraxx.Crdn.Ship), "Name") + "Gen")));
		   AddQuestUserData("Roger_4", "sdegN", sti(pchar.questTemp.Mtraxx.Crdn.degN));
		   AddQuestUserData("Roger_4", "sminN", i);
		   AddQuestUserData("Roger_4", "sdegW", sti(pchar.questTemp.Mtraxx.Crdn.degW));
		   AddQuestUserData("Roger_4", "sminW", n);
		   SetFunctionTimerCondition("Mtraxx_PasqualeTimeConvoy", 0, 0, 6, false);
		   SetFunctionTimerCondition("Mtraxx_PasqualeConvoyOver", 0, 0, 7, false);
		break;
		
		case "mtraxx_5":
			iTotalTemp = GetSquadronGoods(pchar, GOOD_EBONY);
			if (iTotalTemp < 1)
			{
				dialog.text = "年轻人, 你在开玩笑吗? 你的货舱里连一块乌木板都没有! 这是无耻的欺骗! 滚出去! 我会把这件事告诉马库斯! 滚出去!! ";
				link.l1 = "嗯... ";
				link.l1.go = "mtraxx_6";
				break;
			}
			if (iTotalTemp < makeint(sti(pchar.questTemp.Mtraxx.Crdn.Ebony) / 4))
			{
				dialog.text = "小子, 你在开玩笑吗? 你的货舱里只有几块乌木碎片! 这是无耻的欺骗! 滚出去! 我会把这件事告诉马库斯! 滚出去!! ";
				link.l1 = "嗯... ";
				link.l1.go = "mtraxx_6";
				break;
			}
			if (iTotalTemp < sti(pchar.questTemp.Mtraxx.Crdn.Ebony) - 20)
			{
				dialog.text = "‘罗斯博霍姆号’至少有" + FindRussianQtyString(sti(pchar.questTemp.Mtraxx.Crdn.Ebony)) + "乌木。 你为什么只给我带来这么少? ";
				link.l1 = "嗯... 你知道的, 战斗中不得不丢弃了一部分。 还有那些该死的老鼠... ";
				link.l1.go = "mtraxx_7";
				break;
			}
            dialog.text = "很好。 你有多少? " + FindRussianQtyString(iTotalTemp) + "? 太棒了! 我会按每块150比索的价格付给你。 ";
			link.l1 = "150西班牙银元? 我觉得这乌木要值钱得多。 ";
			link.l1.go = "mtraxx_10";
		break;
		
		case "mtraxx_6":
           DialogExit();
		   pchar.questTemp.Mtraxx = "pasq_angry";
		   DoQuestReloadToLocation("Pirates_town", "reload", "reload6", "");
		   AddQuestRecord("Roger_4", "8");
		   CloseQuestHeader("Roger_4");
		   QuestSetCurrentNode("Terrax", "mtraxx_34");
		break;
		
		case "mtraxx_7":
            dialog.text = "老鼠? 好吧好吧... 但算了。 每块100比索, 你可以走了。 ";
			link.l1 = "只有100比索? 这简直是抢劫! ";
			link.l1.go = "mtraxx_8";
		break;
		
		case "mtraxx_8":
			AddMoneyToCharacter(pchar, iTotalTemp * 100);
			RemoveCharacterGoods(pchar, GOOD_EBONY, iTotalTemp);
            dialog.text = "抢劫是你的行当, 船长, 我只是个普通商人。 拿着你的钱, 我们别再争论了, 你已经把我的一部分货物卖到别处, 赚了不少钱了。 ";
			link.l1 = "那去你的吧! ";
			link.l1.go = "mtraxx_9";
		break;
		
		case "mtraxx_9":
           DialogExit();
		   pchar.questTemp.Mtraxx = "pasq_fail";
		   AddQuestRecord("Roger_4", "8");
		   CloseQuestHeader("Roger_4");
		   QuestSetCurrentNode("Terrax", "mtraxx_34");
		break;
		
		case "mtraxx_10":
            dialog.text = "你说得对, 船长, 但首先, 你试试去卖赃物, 我倒要看看其他商人会出多少钱买。 我给你的价格已经很高了。 其次, 这是我提供的线索, 你自己永远找不到那支商队, 而且船上还有其他贵重物品和货物, 我也没要那些。 第三, 我会在马库斯.泰雷克斯面前给你美言, 这很值钱, 相信我。 最后, 第四, 一个可怜的商人总得想办法谋生。 ";
			link.l1 = "哇! 面对如此论据, 我必须让步, " + npchar.name+ "。 我们来清点吧。 ";
			link.l1.go = "mtraxx_11";
		break;
		
		case "mtraxx_11":
			AddMoneyToCharacter(pchar, iTotalTemp * 150);
			RemoveCharacterGoods(pchar, GOOD_EBONY, iTotalTemp);
            dialog.text = "太好了。 拿上你的硬币。 合作愉快。 一定要时不时来看看我的店。 祝你在海上好运! ";
			link.l1 = "也祝你生意兴隆... ";
			link.l1.go = "mtraxx_12";
		break;
		
		case "mtraxx_12":
           DialogExit();
		   pchar.questTemp.Mtraxx = "pasq_complete";
		   AddQuestRecord("Roger_4", "9");
		   pchar.quest.mtr_pasq_fin.win_condition.l1 = "location";
		   pchar.quest.mtr_pasq_fin.win_condition.l1.location = "Pirates_town";
		   pchar.quest.mtr_pasq_fin.function = "Mtraxx_PasqualeJeffry";
		   bDisableFastReload = true;
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
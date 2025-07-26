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
			/* //--> 加斯科涅人的负担
			if (!CheckAttribute(npchar, "quest.storehelper") && pchar.questTemp.Sharlie == "ship")
			{
				Link.l1 = "听着, 先生, 我在找工作。 不是全职或搬运货物那种, 更像是跑腿之类的。 你需要帮手吗? ";
				Link.l1.go = "Sharlie_storehelper";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "return")
			{
				Link.l1 = "我完成了你的差事。 我找到格拉兰.拉沃伊了。 ";
				Link.l1.go = "Sharlie_storehelper_2";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "choise")
			{
				Link.l1 = "认识一下你的新助手吧, 先生。 ";
				Link.l1.go = "Sharlie_storehelper_11";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "final")
			{
				Link.l1 = "又是我, 先生。 我来拿报酬了。 ";
				Link.l1.go = "Sharlie_storehelper_13";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
			{
				link.l1 = "看看这对耳环, 先生。 我在丛林里被杀的土匪身上找到的。 这显然是能工巧匠的作品, 肯定不是本地的。 你对这耳环有什么了解吗? ";
                link.l1.go = "Sharlie_junglejew";
			}
			//<—— 加斯科涅人的负担 */
		break;
		
		//--> 加斯科涅人的负担
		case "Sharlie_storehelper":
			if (FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE) == "") 
			{
				dialog.text = "抱歉, 先生, 但你的剑呢? 不带刃具出城可不安全。 谁知道丛林里会发生什么! ";
				link.l1 = "该死, 我完全忘了! 东西全被没收了! ";
				link.l1.go = "Store_noweapon";
				break;
			}
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("Fortfrance_town", "reload", "reload6_back");
			dialog.text = "找工作? 嗯, 我想有个活你或许愿意接。 我的助手不见了, 他以前在仓库干活。 已经失踪一周了, 这很麻烦, 因为我得替他干活, 根本没时间\n请找到这个蠢货, 弄清楚他为什么撂挑子。 最好把他带回来。 我给你一千西班牙银元。 ";
			link.l1 = "好, 我接了。 告诉我他的名字和长相。 你知道该去哪儿找他吗? ";
			link.l1.go = "Sharlie_storehelper_1";
			link.l2 = "天知道去哪儿找个人就为了那点破钱? 你开玩笑吧! ";
			link.l2.go = "Sharlie_storehelper_exit";
			npchar.quest.storehelper = "true";
		break;
		
		case "Sharlie_storehelper_exit":
			AddTimeToCurrent(2, 0);
			LocatorReloadEnterDisable("Fortfrance_town", "reload10_back", false);// 允许进入
			dialog.text = "嘿, 先生。 到底是谁在找工作, 是你还是我? 如果你不想接, 我也不勉强。 祝你愉快。 ";
			link.l1 = "嗯... 我想我该去港务局看看, 也许他们有更靠谱的活计。 ";
			link.l1.go = "exit";
		break;
		
		case "Sharlie_storehelper_1":
			dialog.text = "他叫格拉兰.拉沃伊。 长相? 三十五岁, 络腮胡, 穿棕色长外套和白衬衫。 哦, 他总戴顶滑稽的三角帽, 装得像个屁股上别着锚的舰队司令\n圣皮埃尔镇我找遍了, 他不在。 肯定在丛林里, 或者在弗朗索瓦港跟那帮海盗混在一起\n弗朗索瓦港是岛上东部的海盗据点。 他可能在那儿跟海盗鬼混, 或者在酒馆喝酒, 或者在商店跟当地商人吵架\n怎么去弗朗索瓦港? 出城门进丛林, 在十字路口走左边岔路, 然后沿路右转, 再从岩石间的左通道走, 就能找到。 应该不会迷路。 ";
			link.l1 = "好。 我这就去找。 一有消息马上通知你。 ";
			link.l1.go = "exit";
			AddQuestRecord("SharlieA", "1");
			pchar.questTemp.Sharlie.Storehelper = "true";
			pchar.questTemp.Sharlie.Storehelper.Chance = rand(2);
			AddDialogExitQuestFunction("Sharlie_CreateStorehelper");
			// 任务指引标记
			QuestPointerToLoc("fortfrance_town", "reload", "gate_back");
			QuestPointerToLoc("fortfrance_exittown", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_01", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_02", "reload", "reload3_back");
			QuestPointerToLoc("lefransua_exittown", "reload", "reload1_back");
		break;
		
		case "Sharlie_storehelper_2":
			DelLandQuestMark(npchar);
			// 移除任务指引标记
			QuestPointerDelLoc("lefransua_town", "reload", "gate_back");
			QuestPointerDelLoc("lefransua_exittown", "reload", "reload2_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerDelLoc("fortfrance_town", "reload", "reload6_back");
			dialog.text = "哦? 他人呢? ";
			link.l1 = "我在弗朗索瓦港找到他了。 他再也不想为你工作了。 还说了很多你的坏话... 想听听吗? ";
			link.l1.go = "Sharlie_storehelper_3";
		break;
		
		case "Sharlie_storehelper_3":
			dialog.text = "不了, 免了吧... 真遗憾! 现在没助手我可怎么办? ";
			link.l1 = "再雇一个呗。 或者真像格拉兰说的那么糟? ";
			link.l1.go = "Sharlie_storehelper_4";
		break;
		
		case "Sharlie_storehelper_4":
			dialog.text = "真倒霉。 那懒鬼说什么了? ";
			link.l1 = "首先, 他显然没闲着, 呵呵。 他说圣皮埃尔没人愿意给你干活, 因为... 你给的工钱太少。 对了, " + npchar.name+ ", 你还欠我承诺的一千比索呢。 ";
			link.l1.go = "Sharlie_storehelper_5";
		break;
		
		case "Sharlie_storehelper_5":
			AddMoneyToCharacter(pchar, 1000);
			dialog.text = "拿钱吧。 哈! 工钱少! 当然没人愿意干。 那混蛋肯定到处说我坏话。 我能怎么办? 总不能什么都自己干! \n不把货物清点完我都睡不着, 那些工人总偷东西。 上次装货少了五桶朗姆酒, 肯定是工人‘不小心’顺走了... ";
			link.l1 = "呃, 我也不知道该怎么建议。 好了, 祝你顺利。 我该走了。 ";
			link.l1.go = "Sharlie_storehelper_6";
		break;
		
		case "Sharlie_storehelper_6":
			dialog.text = "等等! 我觉得你能帮我。 既然你能找到那混蛋, 或许也能... ";
			link.l1 = "我倒想知道, 这镇上没人信你, 我一个新来的能做什么? ";
			link.l1.go = "Sharlie_storehelper_7";
		break;
		
		case "Sharlie_storehelper_7":
			dialog.text = "让我说完, 先生。 你去过弗朗索瓦港。 我想让你再去一次, 帮我找个雇工。 也许格拉兰没把我在海盗窝里的名声彻底搞臭\n工作很简单: 清点货物。 监视码头工人防偷。 有时我不在时替我看店, 当然有额外报酬\n告诉他们我提供店内住宿, 每周五百西班牙银元。 先生, 我正打算扩展生意, 现在情况刚好起来, 需要个助手! \n对了, 最好去找当地酒馆老板切萨雷.克雷格帮忙找工人。 那混蛋肯定能帮你找到愿意干活的人, 当然不是免费的。 ";
			link.l1 = "嗯, 我可以试试, 不过没把握... 这活你给多少钱? ";
			link.l1.go = "Sharlie_storehelper_8";
		break;
		
		case "Sharlie_storehelper_8":
			dialog.text = "这取决于你找来的工人怎么样。 人越好, 我给的报酬越高。 这很公平吧? ";
			link.l1 = "你不觉得这是让我瞎忙活吗? 我怎么知道你怎么评价工人? 你随便说个好坏... ";
			link.l1.go = "Sharlie_storehelper_9";
		break;
		
		case "Sharlie_storehelper_9":
			dialog.text = "先生! 说我小气 maybe 没错, 但没人能说我不诚实! 我说按结果付报酬, 就肯定算数。 也请站在我的角度想想: 你要是带个懒鬼来, 不仅偷懒耍滑, 说不定晚上还偷我东西! ";
			link.l1 = "好吧, 我同意。 我信你, " + npchar.name+ "。 保证不找吉普赛人。 ";
			link.l1.go = "Sharlie_storehelper_10";
		break;
		
		case "Sharlie_storehelper_10":
			DialogExit();
			SetLaunchFrameFormParam("返回弗朗索瓦港... ", "Reload_To_Location", 0, 3.0);
			SetLaunchFrameReloadLocationParam("LeFransua_tavern", "reload", "reload1", "SharlieA_TeleportLF");
			LaunchFrameForm();
		break;
		
		case "Sharlie_storehelper_11":
			dialog.text = "帮我找到工人了? 太好了。 让我跟他谈谈, 一小时后回来拿报酬。 ";
			link.l1 = "好, 一小时后见。 ";
			link.l1.go = "Sharlie_storehelper_12";
			DelLandQuestMark(npchar);
		break;
		
		case "Sharlie_storehelper_12":
			chrDisableReloadToLocation = false;//允许地点重加载
			pchar.questTemp.Sharlie.Storehelper = "final";
			DialogExit();
			SetLaunchFrameFormParam("一小时后... ", "", 0, 5);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0); //时间流逝
			RecalculateJumpTable();
			AddQuestRecord("SharlieA", "5");
			AddLandQuestMark(npchar, "questmarkmain");
		break;
		
		case "Sharlie_storehelper_13":
			switch (sti(pchar.questTemp.Sharlie.Storehelper.Quality))
			{
				case 0:
					AddMoneyToCharacter(pchar, 3000);
					dialog.text = "你找的工人我挺满意, 虽然嘴比手勤, 但别担心, 我很快就能让他闭嘴干活。 这是三千西班牙银元报酬, 拿好。 ";
					link.l1 = "谢谢! 请问先生, 镇上还有其他人需要帮忙处理重要事务吗? ";
					link.l1.go = "Sharlie_storehelper_14a";
				break;
				
				case 1:
					AddMoneyToCharacter(pchar, 5000);
					dialog.text = "你找的工人真是个宝! 比那个混蛋格拉兰强多了。 我非常满意, 先生。 这是五千西班牙银元报酬。 ";
					link.l1 = "谢谢! 请问先生, 镇上还有其他人需要帮忙处理重要事务吗? ";
					link.l1.go = "Sharlie_storehelper_14a";
				break;
				
				case 2:
					AddMoneyToCharacter(pchar, 4000);
					dialog.text = "你找的工人不错。 虽然还不懂全部窍门, 但肯定能很快上手。 我很满意, 先生。 这是四千西班牙银元报酬。 ";
					link.l1 = "谢谢! 请问先生, 镇上还有其他人需要帮忙处理重要事务吗? ";
					link.l1.go = "Sharlie_storehelper_14a";
				break;
			}
		break;
		
		case "Sharlie_storehelper_14a":
			LocatorReloadEnterDisable("Fortfrance_town", "reload10_back", false);// 允许进入
			dialog.text = "嗯... 刚才我看到港务长一脸烦躁地去了港务局。 去问问他, 说不定出什么事了。 ";
			link.l1 = "我这就去。 谢谢你, 先生。 ";
			link.l1.go = "Sharlie_storehelper_14";
			DelLandQuestMark(npchar);
		break;
		
		case "Sharlie_storehelper_14":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Sharlie.Storehelper");
			CloseQuestHeader("SharlieA");
			
			QuestPointerDelLoc("lefransua_town", "reload", "gate_back");
			QuestPointerDelLoc("lefransua_exittown", "reload", "reload2_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerDelLoc("fortfrance_town", "reload", "reload6_back");
			
			QuestPointerToLoc("fortfrance_town", "reload", "reload10_back");
		break;
		
		case "Sharlie_junglejew":
			dialog.text = "嗯, 这对耳环挺漂亮。 我给你... 四千西班牙银元吧。 估计没人给更高了。 成交吗? ";
			link.l1 = "成交! 给你。 ";
			link.l1.go = "Sharlie_junglejew_1";
			link.l2 = "不了, 我想自己留着这珠宝。 ";
			link.l2.go = "exit";
			npchar.quest.junglejew = "true";
		break;
		
		case "Sharlie_junglejew_1":
			DialogExit();
			PlaySound("interface\important_item.wav");
			Log_Info("你交出了耳环");
			RemoveItems(pchar, "jewelry25", 1);
			AddMoneyToCharacter(pchar, 4000);
			AddQuestRecord("SharlieE", "4");
			CloseQuestHeader("SharlieE");
			DeleteAttribute(pchar, "questTemp.Sharlie.Junglejew");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
			{
				DelLandQuestMark(characterFromId("FortFrance_Mayor"));
			}
		break;
		
		case "Store_noweapon":
			dialog.text = "那可不行。 我建议你去找总督寻求帮助。 ";
			link.l1 = "谢谢你的建议。 我正打算这么做。 ";
			link.l1.go = "exit";
		break;
		//<-- 加斯科涅人的负担
	}
	UnloadSegment(NPChar.FileDialog2);
}

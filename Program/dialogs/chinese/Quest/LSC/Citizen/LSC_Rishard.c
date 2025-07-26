// 理查德.香邦 - 走私者
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	float locx, locy, locz;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "我不想和你说话。 你无故攻击和平市民, 还挑衅他们打架。 滚开! ";
				link.l1 = "嗯... ";
				link.l1.go = "exit";
				break;
			}
			// --> 戒指任务
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "find" && CheckAttribute(npchar, "quest.answer_2") && GetNpcQuestPastDayParam(npchar, "quest_date") >= 3 && !CheckAttribute(npchar, "quest.ring"))
			{
				dialog.text = "哦! 你在这儿, 伙计。 我正想自己去找你呢。 我需要你, 朋友。 ";
				link.l1 = "你今天异常友好啊, 理查德。 好吧, 我听着。 ";
				link.l1.go = "ring";
				break;
			}
			// <—— 戒指任务
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "你想干嘛? 说实话, 我今天心情不太好。 其实我都忘了上次心情好是什么时候了。 ";
				link.l1 = "真有那么糟吗, 伙计? ";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "啊, " +GetFullName(pchar)+ "! " +TimeGreeting()+ "! 想要点什么? ";
				link.l1 = LinkRandPhrase("有什么有趣的事要说吗? ", "岛上有什么新鲜事吗? ", "能告诉我最新的八卦吗? ");
				link.l1.go = "rumours_LSC";
				link.l2 = "我想问你几个关于这个岛的问题。 ";
				link.l2.go = "int_quests"; // 信息区块
				link.l5 = "只是想知道你过得怎么样。 再见! ";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // 第一次见面
			dialog.text = "糟? 不, 不算糟。 只是心情不对。 你想干嘛? ";
			link.l1 = "只是想认识你。 我是新来的, 所以在岛上四处走走, 认识些人。 ";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "是吗? 那好吧。 我是理查德.香邦。 很久以前我做过贵重物品走私, 其中有些是非法的, 但过去九年我一直在打捞沉船, 搜寻废料, 用它们换食物和金子。 ";
			link.l1 = "我是" +GetFullName(pchar)+ ", 一个船长... ";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "你是说前船长, 哈哈? ";
			link.l1 = "嗯, 其实我的船现在在蓝港。 我是乘小帆船来的。 ";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "真的? 不可能! 你的小帆船现在在哪? ";
			link.l1 = "嗯... 在海底。 ";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "啊... 我还以为... 算了, 伙计, 我还是去喝点朗姆酒吧... ";
			link.l1 = "祝你好运。 和你聊天很愉快。 再见! ";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("有什么有趣的事要说吗? ", "岛上有什么新鲜事吗? ", "能告诉我最新的八卦吗? ");
			link.l2.go = "rumours_LSC";
			link.l3 = "我想问你几个关于这个岛的问题。 ";
			link.l3.go = "int_quests"; // 信息区块
			NextDiag.TempNode = "First time";
		break;
		
		// 戒指任务
		case "ring":
			dialog.text = "我以前不友好吗? 得了吧, 谁都有心情不好的时候! 告诉我, 岛上有人说你是个出色的战士, 是真的吗? ";
			link.l1 = "我不知道他们怎么说, 但如果你是问我会不会用剑, 我会。 ";
			link.l1.go = "ring_1";
			npchar.quest.ring = "true";
		break;
		
		case "ring_1":
			dialog.text = "知道了。 看来那些传言是真的... 听着, " +pchar.name+ ", 记得我跟你说过外围环吗? 还有在那里能找到贵重物品? ";
			link.l1 = "你们都喜欢聊那个环... 而且说的都一样。 ";
			link.l1.go = "ring_2";
		break;
		
		case "ring_2":
			dialog.text = "不然还能说什么, 哈哈! 好吧, 直说了。 (压低声音) 我在外围环发现一艘未被探索的船, 状况很好, 这很少见\n那是艘大船, 轻帆船。 两个月前甚至更晚才被冲到这里, 其他人还没发现, 所以我们有机会靠掠夺船舱赚大钱。 ";
			link.l1 = "不错, 为你高兴。 但这和我有什么关系? 你想让我跟你一起去? ";
			link.l1.go = "ring_3";
		break;
		
		case "ring_3":
			dialog.text = "正是! 听着, 轻帆船的船首损坏了, 那些该死的螃蟹从洞里钻进去, 在里面筑了巢。 它们在的时候根本没法偷偷进去, 而且我也不知道怎么爬上上层甲板\n我不是好战士, 好几年没碰过剑了, 没法独自杀死那些生物。 所以我才来找你。 ";
			link.l1 = "所以你想让我把船里的螃蟹都杀了, 对吧? ";
			link.l1.go = "ring_4";
		break;
		
		case "ring_4":
			dialog.text = "是的。 我们做个交易: 我带你去船那里, 你负责清掉螃蟹, 找到的战利品我们平分。 很公平 --我发现了船, 你负责清理。 ";
			link.l1 = "不了, 伙计, 我没兴趣。 为了不确定的战利品去半沉的船里和螃蟹打架, 不是我的风格。 你找别的愿意冒险的小伙子吧。 ";
			link.l1.go = "ring_exit";
			link.l2 = "有意思... 我早就想探索外围环了。 成交! 我去杀螃蟹。 ";
			link.l2.go = "ring_5";
		break;
		
		case "ring_exit":
			dialog.text = "太可惜了... 你犯了个错误。 外围环的船上有很多好东西... 而且那艘船还没人去过。 好吧, 随你。 再见... ";
			link.l1 = "再见, 伙计... ";
			link.l1.go = "exit";
		break;
		
		case "ring_5":
			dialog.text = "我就知道没看错你, 朋友。 我感觉我们能在里面找到很多好东西... ";
			link.l1 = "走着瞧。 你知道里面有多少只螃蟹吗? ";
			link.l1.go = "ring_6";
		break;
		
		case "ring_6":
			dialog.text = "我觉得大概四五只... 平均来说。 ";
			link.l1 = "可以。 我们什么时候去? ";
			link.l1.go = "ring_7";
		break;
		
		case "ring_7":
			dialog.text = "明天去吧, 我们得准备一下。 去朱利安修士那里买点解毒剂, 螃蟹的钳子有毒。 小心为上。 明天早上八点在‘倾斜甲板’见, 知道在哪吗? ";
			link.l1 = "不知道, 解释一下。 ";
			link.l1.go = "ring_8";
		break;
		
		case "ring_8":
			dialog.text = "圣奥古斯丁号后面有艘旧船残骸, 船首在水下, 船尾高高翘起, 所以叫‘倾斜甲板’。 只能游泳过去, 从桥底下出发, 绕过圣奥古斯丁号的任意一侧。 我们在那里会合。 ";
			link.l1 = "好的。 明天见! ";
			link.l1.go = "ring_9";
		break;
		
		case "ring_repeat":
			dialog.text = "八点, ‘倾斜甲板’... ";
			link.l1 = "知道了, 知道了... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "ring_repeat";
		break;
		
		case "ring_9":
			DialogExit();
			NextDiag.CurrentNode = "ring_repeat";
			pchar.quest.LSC_Ring_Start.win_condition.l1 = "Timer";
			pchar.quest.LSC_Ring_Start.win_condition.l1.date.hour  = 7.0;
			pchar.quest.LSC_Ring_Start.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.LSC_Ring_Start.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.LSC_Ring_Start.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.LSC_Ring_Start.function = "LSC_RingStart"; // 准备就绪
			pchar.quest.LSC_Ring_Over.win_condition.l1 = "Timer";
			pchar.quest.LSC_Ring_Over.win_condition.l1.date.hour  = 10.0;
			pchar.quest.LSC_Ring_Over.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.LSC_Ring_Over.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.LSC_Ring_Over.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.LSC_Ring_Over.function = "LSC_RingOver"; // 迟到
			AddQuestRecord("LSC_Ring", "1");
		break;
		
		case "ring_10":
			dialog.text = "啊哈, 你来了, 伙计。 准备好做螃蟹沙拉了吗? ";
			link.l1 = "当然! ";
			link.l1.go = "ring_11";
		break;
		
		case "ring_11":
			dialog.text = "很好。 现在转头看向外围环, 看到了吗? 水面上露出的两艘沉船? ";
			link.l1 = "嗯... 看到了。 ";
			link.l1.go = "ring_12";
		break;
		
		case "ring_12":
			dialog.text = "现在从它们中间看向外围环, 看到那艘船首翘起的大帆船了吗? 就在我们正前方, 仔细看。 ";
			link.l1 = "... ";
			link.l1.go = "ring_look";
		break;
		
		case "ring_look":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload_ring");
			DoQuestCheckDelay("LSC_RingTalkLook", 6.0);
		break;
		
		case "ring_13":
			dialog.text = "";
			link.l1 = "我想我看到了... 是的! ";
			link.l1.go = "ring_13a";
		break;
		
		case "ring_13a":
			dialog.text = "那就是我们的目标。 直着游过去, 别转弯。 到外围环后我会告诉你回来的路。 货舱的入口在船首的洞里。 记住, 你不杀完螃蟹我不进去。 ";
			link.l1 = "嗯, 我们昨天说好了, 你带我去船那里, 我杀螃蟹。 游泳吧? ";
			link.l1.go = "ring_14";
		break;
		
		case "ring_14":
			dialog.text = "当然! 我跟着你。 ";
			link.l1 = "... ";
			link.l1.go = "ring_swim";
		break;
		
		case "ring_swim":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetImmortal(npchar, true);
			pchar.quest.LSC_Ring_enter.win_condition.l1 = "locator";
			pchar.quest.LSC_Ring_enter.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_Ring_enter.win_condition.l1.locator_group = "reload";
			pchar.quest.LSC_Ring_enter.win_condition.l1.locator = "reload_ring";
			pchar.quest.LSC_Ring_enter.function = "LSC_RingEnter";
			LSC_RingSetItems(); // 布置物品
			AddQuestRecord("LSC_Ring", "3");
		break;
		
		case "ring_15":
			dialog.text = "呵, 干得好! 你把这些脏东西都杀了! ";
			link.l1 = "我记得有人说‘四五只’螃蟹... 提醒我一下, 谁说的? ";
			link.l1.go = "ring_16";
		break;
		
		case "ring_16":
			dialog.text = "伙计, 我从没进过货舱数过, 只是从洞口看了看。 我没想骗你。 ";
			link.l1 = "随便吧。 我们检查一下货舱... ";
			link.l1.go = "ring_17";
		break;
		
		case "ring_17":
			dialog.text = "当然! 我们来这就是为了这个, 不是吗? ";
			link.l1 = "没错! 别浪费时间了... ";
			link.l1.go = "ring_18";
		break;
		
		case "ring_18":
			DialogExit();
			NextDiag.CurrentNode = "ring_wait";
			LAi_SetWarriorType(npchar);
			LAi_warrior_DialogEnable(npchar, true);
			LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
			DoQuestCheckDelay("LSC_RingDialog", 60.0); // 1分钟搜索时间
			npchar.quest.diagnode = "ring_19";
			AddQuestRecord("LSC_Ring", "4");
		break;
		
		case "ring_wait":
			dialog.text = "等一下, 伙计, 我还没检查完所有地方。 你再找找, 也许能发现更多贵重物品。 ";
			link.l1 = "好吧... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "ring_wait";
		break;
		
		case "ring_19":
			dialog.text = "没什么特别的。 可惜没有贵重物品, 桶里是粮食, 箱子里是椰干, 不过我找到了一箱昂贵的葡萄酒。 你找到了什么? ";
			link.l1 = "我也没找到有趣的东西, 几个箱子有点价值, 剩下的就是你说的咸牛肉和椰干。 ";
			link.l1.go = "ring_20";
		break;
		
		case "ring_20":
			dialog.text = "不够啊... 我们上楼去检查上层甲板和船舱吧。 ";
			link.l1 = "走吧。 ";
			link.l1.go = "ring_21";
		break;
		
		case "ring_21":
			DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("ExternalRingInside", "reload1", true);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.LSC_Ring_deck.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LSC_Ring_deck.win_condition.l1.location = pchar.location;
			pchar.quest.LSC_Ring_deck.win_condition = "LSC_RingEnterDeck";
			for (i=1; i<=3; i++)
			{
				sld = ItemsFromID("purse"+i);
				sld.shown = true;
				sld.startLocation = "ExternalRingDeck";
				sld.startLocator = "item"+i;
			}
		break;
		
		case "ring_22":
			dialog.text = "该死! 看看那个! 该死的螃蟹居然爬到了甲板上! 它们怎么做到的? ! ";
			link.l1 = "别当懦夫! 待在这儿别动, 别引它们注意。 我马上解决这些东西... ";
			link.l1.go = "ring_23";
		break;
		
		case "ring_23":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocator(npchar, "reload", "reload1", "", -1);
		break;
		
		case "ring_24":
			dialog.text = "呼! 看来你击剑的传闻是真的! 要是我一个人在这儿, 早跳海了... ";
			link.l1 = "听着, 你以前怎么成为走私者的? 还是说在躲什么人? ";
			link.l1.go = "ring_25";
		break;
		
		case "ring_25":
			dialog.text = "伙计, 首先, 我以前更年轻。 更强壮, 也更鲁莽; 其次, 我不是雇佣兵, 不想打仗 --我是走私者, 总是尽量避免流血; 第三, 我更喜欢帆和舵, 而不是刀剑和手枪; 最后, 在这里生活多年让我变得软弱了\n所以别怪我。 我们检查上层甲板吧, 这船看起来经历过激烈战斗 --看看这损坏... ";
			link.l1 = "你说得对, 这船肯定受过猛烈炮击。 好吧, 我们找找有趣的东西。 ";
			link.l1.go = "ring_26";
		break;
		
		case "ring_26":
			dialog.text = "是啊。 我们得找到进入内室的入口。 ";
			link.l1 = "成交, 别浪费时间了。 看到螃蟹叫我。 ";
			link.l1.go = "ring_27";
		break;
		
		case "ring_27":
			DialogExit();
			NextDiag.CurrentNode = "ring_wait";
			LAi_SetWarriorType(npchar);
			LAi_warrior_DialogEnable(npchar, true);
			LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
			DoQuestCheckDelay("LSC_RingDialog", 80.0); // 1.3分钟搜索时间
			npchar.quest.diagnode = "ring_28";
			AddQuestRecord("LSC_Ring", "5");
		break;
		
		case "ring_28":
			dialog.text = "还是没找到贵重物品... 我找到了一些有趣的小东西, 就这样。 不过没关系, 甲板上通常没什么值钱的, 好东西都在船舱里。 那边有个进入船长室的入口, 我们去看看。 ";
			link.l1 = "小心点, 谁知道里面有什么。 也许我该先进去? ";
			link.l1.go = "ring_29";
		break;
		
		case "ring_29":
			dialog.text = "走吧, " +pchar.name+ "。 我不会再躲在你后面了, 这确实很丢人... ";
			link.l1 = "那走吧... ";
			link.l1.go = "ring_30";
		break;
		
		case "ring_30":
			DialogExit();
			chrDisableReloadToLocation = true;
			LocatorReloadEnterDisable("ExternalRingDeck", "reload2", false);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "ExternalRingCabin1", "reload", "reload1", "OpenTheDoors", -1);
			pchar.quest.LSC_Ring_cabin.win_condition.l1 = "location";
			pchar.quest.LSC_Ring_cabin.win_condition.l1.location = "ExternalRingCabin1";
			pchar.quest.LSC_Ring_cabin.win_condition = "LSC_RingEnterCabin";
			sld = ItemsFromID("RingCapBook"); // 放置'圣塔-露西亚'日志
			sld.shown = true;
			sld.startLocation = "ExternalRingCabin1";
			sld.startLocator = "item1";
		break;
		
		case "ring_31":
			dialog.text = "看来我运气不错 --这里没有螃蟹也没有其他脏东西。 现在我们把这个船舱翻个底朝天, 该死, 我开始生气了, 只找到了两打达布隆和一些杂物! ";
			link.l1 = "冷静点。 你说得对, 贵重物品总是藏在船长室。 看看我们找到了什么! ";
			link.l1.go = "ring_32";
		break;
		
		case "ring_32":
			DialogExit();
			NextDiag.CurrentNode = "ring_wait";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto2", "LSC_RingSetToBarman", -1);
			DoQuestCheckDelay("LSC_RingDialog", 30.0); // 30秒搜索时间
			npchar.quest.diagnode = "ring_33";
		break;
		
		case "ring_33":
			dialog.text = "哈哈! 正如我所想! 我了解商人的习惯, 他们喜欢藏秘密 stash, 把船上的财宝藏在那里! 这艘轻帆船的船长是个狡猾的无赖, 但我不会轻易被骗! 看看我找到了什么! 没有我你绝对找不到! ";
			link.l1 = "给我看看! ";
			link.l1.go = "ring_34";
		break;
		
		case "ring_34":
			dialog.text = "四万比索, 两箱达布隆, 一包祖母绿和一堆珠宝! 船主相当富有... 好吧, 至少没白费力气, 虽然我本以为能找到更多。 我们公平分配吧。 ";
			link.l1 = "太棒了, 理查德。 至少我们赚了些钱! ";
			link.l1.go = "ring_35";
		break;
		
		case "ring_35":
			TakeNItems(pchar, "jewelry4", 25);
			TakeNItems(pchar, "chest", 1);
			TakeNItems(pchar, "icollection", 1);
			AddMoneyToCharacter(pchar, 20000);
			Log_Info("你获得了一箱达布隆");
			Log_Info("你获得了25颗祖母绿");
			Log_Info("你获得了一套珠宝");
			PlaySound("interface\important_item.wav");
			dialog.text = "好吧, 甲板上各自找到的东西就归各自。 你没意见吧? 你在箱子和柜子里找到什么有用的了吗? ";
			link.l1 = "一些印第安物品。 护身符。 文件之类的。 ";
			link.l1.go = "ring_36";
		break;
		
		case "ring_36":
			dialog.text = "自己留着吧, 毕竟你做了最危险的工作。 ";
			if (CheckAttribute(pchar, "questTemp.LSC.Ring.ReadCapBook")) // 已读日志
			{
				link.l1 = "好的。 我还找到了别的东西, 像你这样的寻宝者可能会感兴趣。 给, 桌上有本船长日志, 里面的故事很悲伤... 但和我们有点关系。 货舱里藏着一个装满金子的箱子! 看看吧! ";
				link.l1.go = "ring_41";
			}
			else
			{
				if (CheckCharacterItem(pchar, "RingCapBook")) // 已拿日志
				{
					link.l1 = "好的。 但我还找到了一样东西 --船长日志。 ";
					link.l1.go = "ring_38";
				}
				else
				{
					link.l1 = "好的, 我同意这个条件, 哈哈。 那么, 该回去了吗? ";
					link.l1.go = "ring_37";
				}
			}
		break;
		
		case "ring_37":
			dialog.text = "是的。 别告诉别人这艘船的事, 这是我们的秘密。 当然, 我们不需要椰干, 但粮食对我们有用, 不用再从舰队司令那里买了。 ";
			link.l1 = "好, 我同意。 希望别人不会很快发现这艘船。 走吧! ";
			link.l1.go = "ring_cabin_exit";
		break;
		
		case "ring_38":
			dialog.text = "你读了吗? ";
			link.l1 = "还没... ";
			link.l1.go = "ring_39";
		break;
		
		case "ring_39":
			dialog.text = "那我们读读看! 能了解到重要信息, 也能知道它怎么到这里的。 读吧! ";
			link.l1 = "嗯。 好吧, 我现在读... ";
			link.l1.go = "ring_40";
		break;
		
		case "ring_40":
			DialogExit();
			NextDiag.CurrentNode = "book_wait";
			LAi_SetWarriorType(npchar);
			LAi_warrior_DialogEnable(npchar, true);
			LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
		break;
		
		case "book_wait":
			dialog.text = "你读了吗? 里面写了什么? ";
			if (CheckAttribute(pchar, "questTemp.LSC.Ring.ReadCapBook")) // 已读日志
			{
				link.l1 = "嗯, 听着... 故事很悲伤... 但现在和我们有点关系。 你的寻宝技能也许能帮上忙, 货舱里有个藏着金子的箱子! 看看吧! ";
				link.l1.go = "ring_41";
			}
			else
			{
				link.l1 = "等一下, 我读了告诉你... ";
				link.l1.go = "exit";
				NextDiag.TempNode = "book_wait";
			}
		break;
		
		case "ring_41":
			dialog.text = "真的? " +pchar.name+ ", 我... 嗯... 我不太会读书。 详细告诉我里面写了什么, 嗯? ";
			link.l1 = "长话短说: 这艘轻帆船从南美穿越加勒比海前往新西班牙。 船长娶了奥里诺科下游一个部落的印第安公主, 她告诉了他族人献祭的地方... ";
			link.l1.go = "ring_42";
		break;
		
		case "ring_42":
			dialog.text = "";
			link.l1 = "金块就是他们的祭品。 当然, 我们勇敢的船长在大副和军需官的帮助下抢劫了这个黄金藏匿点, 把它放在货舱的一个箱子里, 上面盖着椰干... ";
			link.l1.go = "ring_43";
		break;
		
		case "ring_43":
			dialog.text = "";
			link.l1 = "但似乎抢劫印第安圣地遭到了惩罚。 船陷入无风带, 水源短缺, 开始流行热病, 还遭到了海盗袭击。 水手们责怪印第安女孩 --船长的妻子, 要求把她扔下海。 船长当然拒绝了, 船员开始叛变... ";
			link.l1.go = "ring_44";
		break;
		
		case "ring_44":
			dialog.text = "";
			link.l1 = "船长在战斗中失败了。 根据最后记录, 他和印第安女孩锁在船舱里, 试图射击破门而入的愤怒水手, 当时风暴正在逼近... 看来是风暴把船带到了这里。 故事的结局很清楚: 女孩被枪杀, 船长肯定被叛军杀死了。 ";
			link.l1.go = "ring_45";
		break;
		
		case "ring_45":
			dialog.text = "嗯。 确实是个悲伤的故事。 但你没骗我吧? 货舱里真的有装金子的箱子? 我简直不敢相信! 哪一个? 我们去! 我要检查每一包。 每一桶! ";
			link.l1 = "走吧。 我也迫不及待想开始找了。 ";
			link.l1.go = "ring_seek_gold";
		break;
		
		case "ring_cabin_exit":
			DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("ExternalRingInside", "reload1", false); // 打开出口
			LocatorReloadEnterDisable("LostShipsCity_town", "reload_ring", false); // 打开入口 // patch-2
			DoQuestReloadToLocation("ExternalRingDeck", "reload", "reload2", "LSC_RingFinalStage");
			sld = ItemsFromID("RingCapBook");
			sld.shown = false; // 移除日志
			AddQuestRecord("LSC_Ring", "6");
		break;
		
		case "ring_seek_gold":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			// 设置定位器触发条件
			pchar.quest.LSC_Ring_gold.win_condition.l1 = "locator";
			pchar.quest.LSC_Ring_gold.win_condition.l1.location = "ExternalRingInside";
			pchar.quest.LSC_Ring_gold.win_condition.l1.locator_group = "quest";
			pchar.quest.LSC_Ring_gold.win_condition.l1.locator = "gold";
			pchar.quest.LSC_Ring_gold.win_condition = "LSC_RingFindGold";
			// 替换箱子内容
			pchar.GenQuestBox.ExternalRingInside = true;
			pchar.GenQuestBox.ExternalRingInside.box1.items.jewelry5 = 2522;
			AddQuestRecord("LSC_Ring", "7");
		break;
		
		case "ring_46":
			dialog.text = "哈哈! 我们找到了! 真的存在! 看看那一大堆! 整个箱子! 至少有五千块金块! 我从没见过这么多金子! ";
			link.l1 = "恭喜你, 伙伴。 看来我们的任务成功结束了... 这么多金子我们怎么处理? ";
			link.l1.go = "ring_47";
		break;
		
		case "ring_47":
			dialog.text = "你什么意思? 我们对半分! ";
			link.l1 = "当然要分。 你想把金子藏在哪? 留在这儿? ";
			link.l1.go = "ring_48";
		break;
		
		case "ring_48":
			dialog.text = "哈! 我当然会把金子藏在我的 stash 里, 没人能找到! 藏匿是我的专长! 我会把一半金子装在这个桶里, 这是我的份, 日落前带走\n你怎么处理你的那份都行, 但最好也藏到自己的 stash 里。 如果金子不见了别怪我, 我以我的方式保持诚实, 不会拿你的份, 但以后来的人... 他们可能会找到。 ";
			link.l1 = "好的。 我会考虑怎么处理我的金子。 把你的份装进桶里吧... ";
			link.l1.go = "ring_49";
		break;
		
		case "ring_49":
			DialogExit();
			SetLaunchFrameFormParam("两小时后... "+ NewStr() +"金子已分好! ", "", 0, 5);//提示框
			WaitDate("", 0, 0, 0, 2, 10);
			LaunchFrameForm();
			RecalculateJumpTable();
			sld = characterFromId("LSC_Rishard");
			sld.quest.diagnode = "ring_50";
			DoQuestCheckDelay("LSC_RingDialog", 5.0);
		break;
		
		case "ring_50":
			dialog.text = "好了... 谢谢你, " +pchar.name+ ", 谢谢你陪我来。 没有你我做不到。 现在我该考虑造艘小帆船... 离开这里... 啊, 不管了, 以后再想\n我还有活要干 --把金子搬到安全的地方。 再见, 朋友, 希望你明智地使用你的那份! ";
			link.l1 = "再见, 理查德。 今天真是光荣的一天。 再见! ";
			link.l1.go = "ring_51";
		break;
		
		case "ring_51":
			DialogExit();
			LocatorReloadEnterDisable("ExternalRingInside", "reload1", false); // 打开出口
			LocatorReloadEnterDisable("LostShipsCity_town", "reload_ring", false); // 打开入口
			DoQuestCheckDelay("LSC_RingFinalStage", 0.5);
			DeleteAttribute(pchar, "questTemp.LSC.Ring.ReadCapBook");
			AddQuestRecord("LSC_Ring", "8");
		break;
//-------------------------------------—— 问答区块 ---------------------------------------------
		case "int_quests":
			dialog.text = "问题? 哦, 好吧, 如果你真的需要... ";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "你是怎么到这里来的? ";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "你想离开这个岛吗? ";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "你考虑过加入某个帮派吗? 比如独角鲸帮? ";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "外围环真的能找到很多有趣的东西吗? ";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "没问题了。 失陪... ";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "十年来, 我和同伴们乘装备精良的小帆船从古巴往返这个岛, 一直保守着岛的位置秘密 --我们运输牛的尸体, 用新鲜肉换取当地船舱里的货物和金子\n好时光! 这里一直缺粮食, 主要是面包和咸牛肉, 所以他们用香料跟我们换鲜肉, 这些香料在欧洲能卖大价钱! 每次航行我赚的钱都够买下托尔图加所有的妓女\n但一切都有尽头, 我们的好日子也一样。 天气变糟了 --风暴更强, 航行到岛上变得更危险。 一些同伴退出了, 但我和十几个勇敢的人留了下来\n最后, 我们在离岛两英里的礁石上搁浅了。 我至今不知道自己是怎么游过风暴海的。 就这样, 我成了过去交易的对象之一。 ";
			link.l1 = "有趣的故事... ";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "哈! 我会离开这里的, 该死的! 但不是现在。 我回古巴能做什么? 朋友都没了, 口袋也空了。 等我在外围环找到一艘载有贵重货物的船或一堆达布隆, 就开始造船。 ";
			link.l1 = "我知道了... ";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
			SaveCurrentNpcQuestDateParam(npchar, "quest_date");
		break;
		
		case "ansewer_3":
			dialog.text = "我为什么要加入? 像个白痴一样每隔三天站岗, 不让人靠近圣盖博号? 而且他们不喜欢招新人, 都是本地土著... 黑人也一样。 不, 我宁愿单干。 ";
			link.l1 = "我知道了... ";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "当然! 这就是岛上和当地人赖以生存的东西。 你知道这里什么时候热闹吗? 有新船来的时候。 但不管怎样, 外围环还有很多未被探索的船, 装满了金子和货物\n问题是外围环几乎无法探索, 那里一片混乱, 如果你被缠住。 滑倒或摔得很惨 --可能会困在出不来的洞里, 那就完了。 很多人就这样死了。 ";
			link.l1 = "嗯... 有意思。 ";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <—— 问答区块
		
//---------------------------------------—— 特殊反应 -----------------------------------------------
		// 发现玩家在箱子里
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("你在那里做什么, 啊? 小偷! ", "看看那个! 我一沉思, 你就决定检查我的箱子! ", "决定检查我的箱子? 你不会得逞的! ");
			link.l1 = "该死! ";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "什么? ! 决定检查我的箱子? 你不会得逞的! ";
			link.l1 = "愚蠢的女孩! ";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		// 注意到露出的武器
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("听着, 你最好把武器收起来。 它让我紧张。 ", "你知道, 在这里挥舞武器是不被容忍的。 收起来。 ", "听着, 别扮演中世纪骑士到处挥剑。 收起来, 这不适合你... ");
			link.l1 = LinkRandPhrase("好的。 ", "好吧。 ", "如你所说... ");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "听着, 我是这个城市的公民, 我请你收剑。 ", "听着, 我是这个城市的公民, 我请你收剑。 ");
				link.l1 = LinkRandPhrase("好的。 ", "好吧。 ", "如你所说... ");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "小心点, 朋友, 带着武器跑。 我可能会紧张... ", "我不喜欢男人在我面前拿着武器。 这让我害怕... ");
				link.l1 = RandPhraseSimple("知道了。 ", "我收起来。 ");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <—— 特殊反应
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
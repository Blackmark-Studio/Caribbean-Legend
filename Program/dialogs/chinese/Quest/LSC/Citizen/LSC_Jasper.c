// 贾斯珀.普拉特 -  convict
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

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
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "日安, 先生。 想要点什么? ";
				link.l1 = TimeGreeting() + "。 我叫" +GetFullName(pchar)+ ", 你呢? 我是刚来这里的... ";
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
			dialog.text = "我? 我是贾斯珀, 前 state convict。 所以人们都用异样的眼光看我。 啊, 管他们呢, 我已经习惯了... ";
			link.l1 = "我不在乎你过去是谁, 现在的你才重要。 ";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "可惜不是每个人都像你这样想, 先生。 ";
			link.l1 = "嗯, 我以思想开放著称... ";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "为你高兴。 别担心, 尽管我有过去, 但我对岛上居民的钱包和箱子没有威胁。 我很高兴终于能过上平静的生活。 ";
			link.l1 = "很高兴认识你, 贾斯珀。 再见! ";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("有什么有趣的事要说吗? ", "岛上有什么新鲜事吗? ", "能告诉我最新的八卦吗? ");
			link.l2.go = "rumours_LSC";
			link.l3 = "我想问你几个关于这个岛的问题。 ";
			link.l3.go = "int_quests"; // 信息区块
			NextDiag.TempNode = "First time";
		break;
		
//-------------------------------------—— 问答区块 ---------------------------------------------
		case "int_quests":
			dialog.text = "当然可以。 如果我能回答, 我会回答你。 问吧。 ";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "你是怎么成为岛上居民的? ";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "你喜欢这个地方吗? ";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "你提到人们用异样的眼光看你。 是因为你的过去吗? ";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "这个岛很有趣, 你不觉得吗? ";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "没问题了。 失陪... ";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "我从古巴种植园逃出来的。 我们有五个人, 觉得与其继续被鞭挞折磨, 不如死了更好。 我们设法骗过守卫, 消失在丛林里, 然后到达海岸, 造了一个木筏\n我们想前往托尔图加, 但命运弄人。 我们没人知道如何导航, 所以迷路了。 然后水喝光了... 我不想回忆那些。 结果, 我是唯一到达这个岛并活下来的人。 ";
			link.l1 = "我明白了... ";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "你知道, 我觉得这里挺好。 在种植园经历了那么多之后, 这个地方对我来说就像天堂。 我需要的不多... 一点食物。 水和每晚一杯朗姆酒。 这里没人打扰我, 我也不打算离开这里。 时机到了我就会死在这里。 ";
			link.l1 = "我明白了... ";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "问题是这个岛有个神秘的小偷在活动。 对他来说锁不是问题。 他主要在舰队司令的房间附近晃悠。 不过我们的箱子也没能幸免\n没人知道这个小偷是谁, 所以他们怀疑有... 嗯, 有犯罪前科的人\n不过这个小偷有点奇怪: 首先, 他只拿装烈酒的瓶子和一些小饰品, 从不拿贵重物品。 很有趣, 不是吗? ";
			link.l1 = "知道了... ";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "是的, 我同意。 我在岛的内圈船只周围游过很多次。 从水里上来的出口很少。 圣奥古斯丁号的桥边。 荣耀号的倒下的桅杆处。 如果你游近凤凰平台, 然后绕过刻瑞斯铁匠号号, 你会到达玛丽.卡斯帕在船首的船舱\n塔尔塔罗斯号的裂缝会通向监狱。 圣奥古斯丁号船首有个洞, 你可以进入舰队司令的储藏室, 但这不建议。 塔尔塔罗斯号最下面的门经常是关着的, 记住这一点\n当然, 你可以进入费尔南达号, 那是一艘孤零零的破旧长笛帆船。 他们说那里没人住, 但我经常注意到船舱里有灯光, 有时还能听到奇怪的醉酒歌声和哭声。 ";
			link.l1 = "有意思... 我需要多探索一下这个地方。 ";
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
			link.l1 = LinkRandPhrase("好的。 ", "那好吧。 ", "如你所说... ");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "听着, 我是这个城市的公民, 我请你收剑。 ", "听着, 我是这个城市的公民, 我请你收剑。 ");
				link.l1 = LinkRandPhrase("好的。 ", "那好吧。 ", "如你所说... ");
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
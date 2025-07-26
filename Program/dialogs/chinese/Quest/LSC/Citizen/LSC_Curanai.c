// 库拉奈 - 印第安人
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
				dialog.text = "白人兄弟想要什么? ";
				link.l1 = TimeGreeting() + "。 白人兄弟? 告诉我, 为什么你们印第安人要么叫我们白人兄弟, 要么叫白脸狗? ";
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
				if (CheckAttribute(npchar, "quest.answer_2"))
				{
					link.l3 = "看看你能找到什么。 也许我会买些东西... ";
					link.l3.go = "trade";
				}
				link.l5 = "只是想知道你过得怎么样。 再见! ";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // 第一次见面
			dialog.text = "我们在这里和平共处, 白人兄弟。 库拉奈不叫白人兄弟白脸狗。 不是所有白人都是狗。 我也可以叫很多印第安人红皮狗。 ";
			link.l1 = "嗯。 我觉得你是个哲学家... ";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "库拉奈不懂你, 白人兄弟。 哲学家是什么意思? ";
			link.l1 = "没关系, 红皮兄弟。 我只是喜欢你的思考方式。 你说你叫库拉奈? 我叫" +GetFullName(pchar)+ "。 很高兴认识你。 ";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "库拉奈很高兴知道白人兄弟的名字。 ";
			link.l1 = "很好。 回头见! ";
			link.l1.go = "exit";
			link.l3 = "我想问你几个关于这个岛的问题。 ";
			link.l3.go = "int_quests"; // 信息区块
			NextDiag.TempNode = "First time";
		break;
		
		case "trade":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 4)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;
		
//-------------------------------------—— 问答区块 ---------------------------------------------
		case "int_quests":
			dialog.text = "问吧, 白脸兄弟, 库拉奈会回答。 ";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "你是怎么到这里来的? ";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "你在岛上做什么? ";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "你想回家吗? ";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "你在岛上生活和平吗? 这里会发生打架或争吵吗? ";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "没问题了。 失陪... ";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "我和部落的几个战士决定划竹筏去靠近我们土地的小岛, 晴天可以看见的那个。 但突然遭遇风暴, 把我们卷进了公海。 我们没意识到陆地和小岛消失得多快\n我们在海上漂了很多个日夜。 所有兄弟都因饥渴而死。 只剩下我一个 --神灵怜悯库拉奈, 把木筏带到了这个岛。 我活了下来。 ";
			link.l1 = "是啊... 悲伤的故事。 ";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "库拉奈捕鱼。 用鱼叉叉鱼。 很少能叉到大螃蟹。 抓到就高兴 --螃蟹很美味, 非常美味。 一只钳子够吃好几天。 库拉奈也会潜到一个地方, 那里没有大螃蟹。 捡黄色的石头。 蓝色的石头。 黑色的石头和珍珠, 大大小小的。 然后卖给白脸人。 ";
			link.l1 = "我明白了... ";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "库拉奈想回家。 但家在哪里? 库拉奈不知道村庄在哪, 也不知道怎么回去。 ";
			link.l1 = "嗯。 我能说什么呢... ";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "独角鲸帮和里瓦多斯帮经常互相打斗。 我们和平生活, 不伤害任何人。 有时白脸人喝火酒骂街, 但不杀人。 有两个军官战士, 互相憎恨。 总有一天一个会杀了另一个。 库拉奈知道。 ";
			link.l1 = "我明白了... ";
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
			link.l1 = LinkRandPhrase("好的。 ", "当然。 ", "如你所说... ");
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
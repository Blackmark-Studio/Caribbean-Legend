// 莱昂内尔.马斯凯特 - 市民
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
				dialog.text = "日安, " + GetAddress_Form(NPChar) + "。 你是新来的吗? ";
				link.l1 = TimeGreeting() + "。 我叫" +GetFullName(pchar)+ "。 是的。 ";
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
			dialog.text = "我叫莱昂内尔。 很高兴认识你。 你怎么到这里来的? ";
			link.l1 = "乘一艘三桅帆船... 听说这里有走私者的基地, 就想来探索... 探索完了。 船沉了, 我就留在这了。 ";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "他们真的把这个岛当成走私者的基地吗? ";
			link.l1 = "呃, 官方不算。 大部分人甚至不相信你们的存在。 ";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "说真的... 他们为什么要信? 我们其实根本不存在。 你没法离开这里。 虽然有人说以前和古巴有联系... 但我不记得了, 我已经在这里住了快八年。 ";
			link.l1 = "明白了。 和你聊天很愉快。 再见! ";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("有什么有趣的事要说吗? ", "岛上有什么新鲜事吗? ", "能告诉我最新的八卦吗? ");
			link.l2.go = "rumours_LSC";
			link.l3 = "我想问你几个关于这个岛的问题。 ";
			link.l3.go = "int_quests"; // 信息区块
			NextDiag.TempNode = "First time";
		break;
		
//------------------------------------- —问答区块 ---------------------------------------------
		case "int_quests":
			dialog.text = "我在听。 ";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "你是怎么到这里来的? ";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "你想回大陆吗? ";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "岛上的人都做些什么? ";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "你们在这里的所有物资从哪来? 食物。 衣服。 饮料? ";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "没问题了。 失陪... ";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "说来奇怪。 这个岛是我见过的加勒比地区中最特别的地方。 当我在英国混不下去时, 我搭上了一艘商船, 想在伯利兹找份港口办公室职员的工作, 但我们始终没到那里\n我不是水手, 所以不清楚细节。 一场风暴过后, 第二天船就触礁了。 我永远忘不了那可怕的撞击声和尖叫声\n有人喊船体破了个洞, 人们开始跳海。 我... 我不会游泳, 所以留了下来。 讽刺的是, 这救了我的命。 船撑过了风暴, 黎明时风平浪静\n在离船前我做了唯一正确的决定: 带上食物, 做了个木筏, 漂到了外围的船只残骸区。 全船只有我活了下来。 ";
			link.l1 = "我知道了... ";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "前两年我唯一的梦想就是离开。 但现在... 这个岛比世界上其他地方差在哪? 虽然没有牧羊的绿草地, 但有壮丽的大海和布满繁星的夜空。 我吃得饱, 穿得暖 —这在英国时根本不敢想。 我还有很多朋友\n不, 先生, 我不想离开。 外面有什么在等我? 每周三百比索。 在吵吵嚷嚷的老板手下做文职? 算了吧! 我在这里找到了想要的一切, 别无所求。 ";
			link.l1 = "了解了。 为你高兴! ";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "各取所好罢了。 帮派玩战争游戏, 海盗卖物资, 阿克塞尔.约斯特做买卖, 桑乔.卡彭特罗开酒馆招待客人, 朱利安修士祈祷。 做弥撒。 卖药。 洛德代尔和索德拉互相算计, 埃博特自命不凡, 吉利安和坦妮克渴望真爱... ";
			link.l1 = "有意思... ";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "从船上啊, 朋友, 从船上。 大部分人最喜欢的活动就是探索外围的船只残骸, 从中搜集物资。 你能在那里找到任何东西: 武器。 药品。 香料和朗姆酒。 很多船还没被探索过。 洋流经常会把新的‘受害者’冲到这里... ";
			link.l1 = "有意思... ";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// < —问答区块
		
//--------------------------------------- —特殊反应 -----------------------------------------------
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
// < —特殊反应
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
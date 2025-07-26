// 约瑟夫.洛德代尔 - 英国海军军官
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
				dialog.text = "日安, 先生。 很高兴在这里见到一位贵族。 ";
				link.l1 = TimeGreeting() + "。 实际上, 我在群岛期间与平民过于亲近, 几乎快忘记自己的贵族身份了... ";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = TimeGreeting() + ", " +GetFullName(pchar)+ "! 很高兴见到你! 有什么想聊的? ";
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
			dialog.text = "哦, 你还很谦虚! 真正的绅士! 我想我们会成为朋友, 你不像那个傲慢的埃博特... 容我自我介绍 --约瑟夫.洛德代尔, 前英国海军舰队上尉。 ";
			link.l1 = "很高兴认识你。 " +GetFullName(pchar)+ ", 为你效劳! ";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "在这里生活很无聊, 晚上可以去桑乔的酒馆, 我们可以喝杯酒, 聊聊天... ";
			link.l1 = "我会记住的, 先生。 再见! ";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("有什么有趣的事要说吗? ", "岛上有什么新鲜事吗? ", "能告诉我最新的八卦吗? ");
			link.l2.go = "rumours_LSC";
			link.l3 = "我想问你几个关于这个岛的问题。 ";
			link.l3.go = "int_quests"; // 信息区块
			NextDiag.TempNode = "First time";
		break;

//-------------------------------------—— 问答区块 ---------------------------------------------
		case "int_quests":
			dialog.text = "很荣幸回答你的问题, 先生... ";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "你是怎么到这里来的? ";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "在这里能获得什么服务? ";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "作为一名军官, 你如何看待海盗在这里的统治? ";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "我在岛上看到很多上锁的箱子。 人们彼此不信任, 对吧? ";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "没问题了。 失陪... ";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "履行军事职责时来到这里。 我当时在与西班牙武装单桅帆船交战, 我们认为它就是掠夺英国商船的罪魁祸首。 战斗持续了很久, 我们几乎要俘获它, 但突然的风暴毁了一切。 结果, 两艘船都在外环附近失事\n命运真会开玩笑, 我和西班牙船长都活了下来。 也许你已经在这里见过他了。 他叫洛伦佐.索德拉, 是个罕见的混蛋。 小心他。 ";
			link.l1 = "知道了。 我会记住你的警告... ";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "如果你需要休息 --去桑乔的酒馆。 他会一直为你提供食物。 饮料和床铺。 如果你想要火药。 弹药。 武器和其他物品 --去找阿克塞尔.约斯特, 他开了当地的商店。 药品可以从朱利安修士那里购买, 他也在教堂里卖圣物\n独角鲸帮有个非常有才华的铁匠, 名叫施密特。 据说他能打造出色的刀剑。 独角鲸帮中还有另一位有才华的工匠, 但我没能了解更多\n如果你与海盗或帮派有麻烦, 就去找朱塞佩.法齐奥, 他是处理此类事务的专家。 ";
			link.l1 = "感谢提供信息! ";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "我不能说喜欢, 但也无能为力。 我承认, 海盗只用了几天就实现了和平并在岛上建立了秩序。 在海盗到来之前, 帮派经常互相争斗, 普通人受苦最多\n此外, 他们卖食物很规矩。 公平 --市民能用很低的价格买到, 而帮派就不同了, 海盗会因为战争报复而狠狠敲诈他们\n我认识一个很聪明的海盗, 名叫莱顿.德克斯特。 他负责贸易。 我曾和他谈过一次, 很好奇这样一个有才华。 受过良好教育, 懂战术。 制图和贸易的人, 怎么会加入海盗\n他只用了几天就绘制了一幅出色的岛屿地图。 我见过, 几乎包含了所有信息。 我相信他是为了可能与帮派的战争而绘制的... ";
			link.l1 = "我明白了... ";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
			sld = characterFromId("Dexter");
			sld.quest.map = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "这是正确的做法。 据说很久以前, 岛上偷窃成风, 直到所有箱子都换了新锁。 但仍有人能撬开箱子。 不过他只偷朗姆酒和廉价珠宝, 从不拿黄金或钱财\n所有锁都是独特的, 没有相同的钥匙 --尤尔根.施密特确保了这一点。 他不仅制作刀剑, 还制作锁和钥匙。 有人告诉我, 外围的箱子里没有贵重物品, 重要物品总是放在船内。 ";
			link.l1 = "有意思... ";
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
			link.l1 = LinkRandPhrase("好的。 ", "如你所愿... ", "如你所说... ");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "听着, 我是这个城市的公民, 我请你收剑。 ", "听着, 我是这个城市的公民, 我请你收剑。 ");
				link.l1 = LinkRandPhrase("好的。 ", "如你所愿... ", "如你所说... ");
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
// 维克多.卡塞尔 - 匪徒
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
				dialog.text = "我不想和你说话。 你无缘无故攻击和平的平民, 还挑衅他们打架。 走开! ";
				link.l1 = "嗯... ";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "嗯... 你想要什么, 伙计? 如果你想聊天, 我得让你失望了。 我没心情说话。 ";
				link.l1 = "太遗憾了... 我本想聊聊的。 我是这里的新来者, 只是想认识一下大家... ";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "啊, " +GetFullName(pchar)+ "! 你想要什么? ";
				link.l1 = LinkRandPhrase("有什么有趣的事情要说吗? ", "岛上有什么新鲜事吗? ", "你能给我讲讲最近的传闻吗? ");
				link.l1.go = "rumours_LSC";
				link.l2 = "我想问你几个关于这个岛的问题。 ";
				link.l2.go = "int_quests"; // 信息块
				link.l5 = "只是想知道你过得怎么样。 再见! ";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // 第一次见面
			dialog.text = "新来的? 嗯。 那好吧。 我是维克多.卡塞尔, 你最好别在我心情不好的时候惹我生气, 心情好的时候也一样。 我没时间闲聊, 如果有人太纠缠, 我会直接揍人。 ";
			link.l1 = "好吧, 我是" +GetFullName(pchar)+ "。 顺便说一句, 我也很能打。 但希望没机会验证。 如果你这么不爱交际, 我就不打扰了。 再见。 ";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("有什么有趣的事情要说吗? ", "岛上有什么新鲜事吗? ", "你能给我讲讲最近的传闻吗? ");
			link.l2.go = "rumours_LSC";
			link.l3 = "我想问你几个关于这个岛的问题。 ";
			link.l3.go = "int_quests"; // 信息块
			NextDiag.TempNode = "First time";
		break;
		
//-------------------------------------—— 问答块 ---------------------------------------------
		case "int_quests":
			dialog.text = "嗯? 你想知道什么? ";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "你怎么到这里的? ";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "这里的生活是什么样的? ";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "这里最... 重要的人是谁? ";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "在岛上怎么赚钱? ";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "没有问题。 抱歉... ";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "抱歉, 朋友, 这和你有什么关系? 我就是到这里了。 不想聊那些事, 尤其是和不认识的人。 ";
			link.l1 = "好吧, 抱歉... ";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "无聊透顶。 乏味。 枯燥。 毫无意义。 我打算加入鲨鱼海盗团, 那些家伙值得追随。 我很乐意加入他们的队伍, 只是需要先... 打探一下。 我相信他们会找到离开这个岛的路。 ";
			link.l1 = "真的吗? 我知道了... ";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "当然是舰队司令! 海盗们把独角鲸和里瓦多牢牢控制在手里, 帮派都不敢吭声。 接下来是帮派首领, 独角鲸的唐纳德.格林斯皮和里瓦多的黑埃迪。 独角鲸的商人阿克塞尔.约斯特也很重要。 当然还有桑乔.卡彭特罗, 他是个不错的家伙... ";
			link.l1 = "了解了... ";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "箱子。 当然, 你得先打开它们, 这里的人互不信任, 所以所有箱子都上了锁。 告诉你吧, 伙计, 最好的宝贝都在船里, 由主人看守着\n你也可以去外环探险, 但祈祷别从腐烂的木板上掉下去。 或者捕猎巨型螃蟹, 它们钳子上的肉能卖个好价钱。 ";
			link.l1 = "知道了... ";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <—— 问答块
		
//---------------------------------------—— 特殊反应 -----------------------------------------------
		// 发现主角在箱子里
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("你在那里干什么, 啊? 小偷! ", "看看这个! 我一不留神, 你就决定检查我的箱子了! ", "决定检查我的箱子了? 你逃不掉的! ");
			link.l1 = "该死! ";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "什么? ! 决定检查我的箱子了? 你逃不掉的! ";
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
		
		// 对露出武器的评论
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("听着, 你最好把武器收起来。 这让我很紧张。 ", "你知道吗, 在这里带着刀乱跑是不被允许的。 把它收起来。 ", "听着, 别扮演中世纪的骑士, 拿着剑到处跑。 把它收起来, 这不适合你... ");
			link.l1 = LinkRandPhrase("好吧。 ", "好吧。 ", "如你所说... ");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "听着, 我是这个城市的公民, 我希望你把刀收起来。 ", "听着, 我是这个城市的公民, 我希望你把刀收起来。 ");
				link.l1 = LinkRandPhrase("好吧。 ", "好吧。 ", "如你所说... ");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "小心点, 伙计, 带着武器乱跑。 我会紧张的... ", "我不喜欢男人拿着武器在我面前走来走去。 这让我害怕... ");
				link.l1 = RandPhraseSimple("明白了。 ", "我收起来。 ");
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
// Орeли Бeртин - просто житeльница
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
				dialog.text = "日安, 先生。 您有什么事吗? ";
				link.l1 = TimeGreeting()+"。 我叫"+GetFullName(pchar)+", 我是新来的, 所以正在了解当地人。 ";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "啊, "+GetFullName(pchar)+"! "+TimeGreeting()+"! 想要点什么吗? ";
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
			dialog.text = "我明白了。 我叫奥雷莉.伯廷。 你是怎么来到这里的? ";
			link.l1 = "可以说我只是想看看神秘的正义岛。 ";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "那么你一定是那些自愿来到这里的疯子之一... 好吧, 现在你有足够的时间去看看这个岛, 尝尝它的'正义'。 ";
			link.l1 = "根据你的讽刺, 这里的正义有什么问题吗? ";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "不, 一切都很好。 但出于某种原因, 我们不得不向海盗支付食物钱, 而不久前这些食物对所有人来说都是免费的。 当帮派在我们岛的这一部分开始战斗时, 我们应该躲在船里, 以免被射杀或屠杀\n我的意思是, 他们被允许在我们的领土上为所欲为, 但我们不能在他们的领土上做同样的事情。 但没关系, 没有更多的麻烦了... ";
			link.l1 = "我明白了。 很好, 很高兴认识你。 再见! ";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//------------------------------------- —问答块 ---------------------------------------------
		case "int_quests":
			dialog.text = "我在听。 ";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "你在这里住了很久了吗? ";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "岛上有什么有趣的地方吗? ";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "你对帮派有什么看法? ";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "海盗会打扰你们吗? ";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "没有问题。 抱歉... ";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "很久了。 我已经记不清了。 大概有十七年了... 不, 也许是十八年... 或者是二十年? 现在是哪一年? ";
			link.l1 = "我明白了... 那么你在这里是个老居民了? ";
			link.l1.go = "ansewer_1_1";
		break;
		
		case "ansewer_1_1":
			dialog.text = "相对来说。 我还记得海盗们和我们交易的日子, 那时最鲁莽和聪明的独角鲸会航行到大陆, 用物资交换船上货舱里的货物。 但这里有很多人除了这个岛什么地方都没见过, 因为他们就出生在这里。 他们不仅是这里的老居民, 更是本地人。 ";
			link.l1 = "真有趣... ";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "是的, 有很多。 这里的一切都很有趣。 四处走走, 自己看看。 在岛的中心部分游泳。 参观一家酒馆。 一家商店和一座教堂。 问题是, 我可以向你保证, 这种兴趣会在一周内消失。 ";
			link.l1 = "明白了... ";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "我们应该如何看待那些强盗呢? 我尽量远离他们, 仅此而已。 至少独角鲸对这个岛有一些好处, 他们中间有非常有才华的工匠, 但里瓦多人只是野蛮人和异教徒\n他们仍然像几百年前一样遵守他们的非洲法律。 畜生。 他们唯一学会的就是使用火器。 他们说他们还进行同类相食的仪式! ";
			link.l1 = "太可怕了... ";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "他们把我们自己的食物卖给我们这一点有点烦人, 但他们不会伤害市民。 实际上, 恰恰相反, 他们让帮派们安分了下来, 防止了任何暴力行为\n有一个市民制造了麻烦, 挥舞着他的军刀。 他甚至打伤了另外两个当地人。 海盗们把他带到塔尔塔罗斯关了几个星期。 现在这个人很安静, 也很平和。 我们不常见到他, 外环成了他的新家... ";
			link.l1 = "我明白了... ";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// < —问答块
		
//--------------------------------------- —特殊反应 -----------------------------------------------
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
// < —特殊反应
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
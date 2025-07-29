// 道格尔.埃博特 - 贵族
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
				dialog.text = "日安, 先生。 容我自我介绍 —道格尔.埃博特。 很高兴在这里见到一位贵族。 我受够了当地的农民。 我从没想过这辈子要和普通人一起生活。 ";
				link.l1 = TimeGreeting() + "。 我叫" +GetFullName(pchar)+ "。 很高兴认识你。 你为什么不喜欢当地人? ";
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
			dialog.text = "你不太了解他们。 你刚到这里吗? 不过我不记得最近有船只失事... ";
			link.l1 = "我乘一艘小三桅帆船来的... ";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "是的, 这种情况经常发生 —船只沉没, 只有少数幸存者乘救生艇来到这里。 有时人们在这里住了好几个月, 你却从未见过他们。 ";
			link.l1 = "我明白了。 很高兴认识你, 埃博特先生。 再见! ";
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
				link.l2 = "你能跟我说说当地人吗? ";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "你能跟我说说各个帮派吗? ";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "还有天气呢? 这里经常有风暴吗? ";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "没问题了。 失陪... ";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "那是五年前的事了, 但我仍然记得很清楚, 就像发生在昨天一样。 不幸的一天, 我决定乘我的长笛帆船从皇家港航行到伯利兹, 货物太贵重, 不敢托付给别人\n第二天我的不幸就开始了, 首先我们的水手长喝醉了掉进海里, 然后我们差点撞上礁石, 最后我们的领航员犯了错误, 所以我们航错了方向\n然后我们被一艘双桅横帆船和一艘大帆船追赶。 我们试图逃跑, 但他们穷追不舍。 大帆船被甩在后面, 但双桅横帆船最终追上了我们\n大帆船离那里太远, 所以我们没有开枪就登上了双桅横帆船。 那些西班牙狗没有料到, 我们赢了, 但我的大部分船员都死了\n几小时后, 我们遭遇了风暴, 船员太少, 无法与天气抗争, 现在你看到了结果。 我的长笛帆船在外环的某个地方, 我和其他三个幸存者来到了这里。 ";
			link.l1 = "知道了... ";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "都是些败类。 全都是。 各种底层人物。 理查德.香邦是个罪犯, 一看脸就知道。 卡塞尔? 对他来说杀人就像呼吸一样自然。 贾斯珀.普拉特是个 convict。 马斯基特是个酒鬼。 需要我继续说吗? \n约瑟夫.洛德代尔是这里唯一正派的人, 除了你, 他是英国海军的退役军人。 这里有两个贵族 —安东尼奥.贝坦科特和洛伦佐.索德拉, 该死的西班牙败类, 我甚至不会和他坐在同一张桌子旁。 ";
			link.l1 = "我明白了... ";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "一群混蛋和败类。 不过他们不伤害我们。 他们更感兴趣的是互相刺杀和射击。 没有这个他们就活不下去。 我也不喜欢海盗, 但我必须承认, 他们来到这里后, 岛上变得更和平了。 ";
			link.l1 = "有意思... ";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "从来没有。 岛周围经常有风暴, 但这个地方总是很平静, 也许是某种魔法或上帝的旨意, 我不知道。 有时会有强风到达这里, 就这样。 雨水也不会造成任何损害。 ";
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
			link.l1 = LinkRandPhrase("好的。 ", "好的。 ", "如你所说... ");
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
// < —特殊反应
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
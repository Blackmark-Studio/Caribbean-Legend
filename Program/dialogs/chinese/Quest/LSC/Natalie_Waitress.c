// 女服务员娜塔莉娅.布谢尔
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
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "哦! 他们告诉我你淹死了... 骗子! ";
				link.l1 = "当然, 他们是这么说的! 哈! 我很好! ";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "日安, " + GetAddress_Form(NPChar) + "! 第一次来这里吗? 我以前没见过你... 希望你能多来光顾, 桑乔能提供各种各样的好酒。 对了, 我叫娜塔莉娅, 在酒馆帮桑乔打理事务。 ";
				link.l1 = TimeGreeting() + "。 我叫" +GetFullName(pchar)+ "。 很高兴见到你。 你以前没见过我, 因为我最近刚到这里。 ";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "啊, " +GetFullName(pchar)+ "! " +TimeGreeting()+ "! 想要点什么吗? ";
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
			dialog.text = "最近? 又有船失事了吗? 我没听说... 或者你不是像图拉姆先生那样乘着桅杆残骸来的吧? 哦, 请原谅我的好奇心, 你知道的, 女人的天性如此。 ";
			link.l1 = "不, 没关系, 娜塔莉娅。 我是乘三桅帆船来的, 但它沉没了。 很高兴认识你。 回头见! ";
			link.l1.go = "exit";
			link.l2 = "不, 没关系。 只是想问你几个关于这个岛的问题。 ";
			link.l2.go = "int_quests"; // 信息区块
			NextDiag.TempNode = "First time";
		break;
		
//-------------------------------------—— 问答区块 ---------------------------------------------
		case "int_quests":
			dialog.text = "我在听。 ";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "你在酒馆工作。 能跟我说说老板吗? ";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "你是怎么到这里来的? ";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "这里住了多少人? ";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "看到新面孔你从不觉得奇怪吗? ";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "没问题了。 失陪... ";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "只有正面的评价, " + GetAddress_Form(NPChar) + "。 桑乔总是有很多种酒 --从陈年葡萄酒到普通麦芽酒和朗姆酒。 几年前他发现了一大批陈年葡萄酒。 桑乔花了两个月把装酒瓶的箱子搬到他的储藏室\n现在我们有充足的葡萄酒, 在群岛上只有总督才能喝到那么多。 朗姆酒也不成问题。 桑乔不仅能提供饮品, 还能提供最新消息。 好的建议和一张温暖的床过夜。 ";
			link.l1 = "我明白了... ";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "哦, 那是个悲伤的故事。 七年前, 我和我的追求者从父母家私奔, 决定从圣地亚哥搬到伯利兹。 领航员在大陆附近犯了错, 所以我们向北航行了错误的方向, 遇到了风暴。 我们的船在外环附近沉没了\n我的追求者那天和大多数人一样遇难了。 我和幸存者们在这个岛上开始了新生活。 ";
			link.l1 = "悲伤的故事... ";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "相当多。 里瓦多斯和独角鲸家族人数众多, 他们已经在这里生活了几十年。 普通人没那么多, 但酒馆每晚都客满。 我几乎来不及上酒。 ";
			link.l1 = "真的吗? 有意思。 ";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "我们为什么要惊讶? 经常有很多新面孔来。 我甚至不知道我们这里住了多少人。 有时我第一次见到一个人, 他却告诉我他已经在这里住了一年。 ";
			link.l1 = "好吧... ";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <—— 问答区块
		
//---------------------------------------—— 特殊反应 -----------------------------------------------
		// 发现玩家在箱子里
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("你在那里做什么, 嗯? 小偷! ", "看看那个! 我一沉思, 你就决定检查我的箱子! ", "决定检查我的箱子? 你不会得逞的! ");
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
				dialog.text = NPCharSexPhrase(NPChar, "听着, 我是这个城市的公民, 我请你把剑收起来。 ", "听着, 我是这个城市的公民, 我请你把剑收起来。 ");
				link.l1 = LinkRandPhrase("好的。 ", "好吧。 ", "如你所说... ");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "小心点, 朋友, 带着武器跑。 我可能会紧张... ", "我不喜欢人们在我面前拿着武器。 这让我害怕... ");
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
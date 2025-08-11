// 赫拉尔德.斯密茨 - 水手
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
				dialog.text = "日安, 伙计, 哈哈! 你在这里做什么? ";
				link.l1 = TimeGreeting() + "。 我认识你吗? ";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "啊, " +GetFullName(pchar)+ "! " +TimeGreeting()+ "! 想要点什么吗? ";
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
			dialog.text = "当然, 你不认识我, 但这很容易解决, 对吧? 我是赫拉尔德.斯密茨, 水手, 来自鹿特丹的海员。 而你看起来至少像个军需官... ";
			link.l1 = "差不多吧。 我叫" +GetFullName(pchar)+ "。 很高兴认识你。 ";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "你看起来更像个船主或出纳员... 毫无疑问, 你是个受过良好教育的人。 很高兴认识你。 你是怎么到这里来的? ";
			link.l1 = "我决定探索一个未知的区域。 来自古巴的海盗告诉我, 这个区域有一些东西, 我决定去看看... ";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "你是唯一的幸存者吗? 你的船在哪里沉没的? 在环礁附近吗? ";
			link.l1 = "我是唯一的幸存者。 我的塔尔坦船沉到了海底, 甚至都没到环礁。 ";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "我明白了。 嗯, 你要在这里待一段时间了。 去拜访桑乔, 弄点朗姆酒, 这是个不错的主意... ";
			link.l1 = "我会的。 再见! ";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("有什么有趣的事情要说吗? ", "岛上有什么新鲜事吗? ", "你能给我讲讲最近的传闻吗? ");
			link.l2.go = "rumours_LSC";
			link.l3 = "我想问你几个关于这个岛的问题。 ";
			link.l3.go = "int_quests"; // 信息块
			NextDiag.TempNode = "First time";
		break;
		
//------------------------------------- —问答块 ---------------------------------------------
		case "int_quests":
			dialog.text = "当然, 朋友。 我在听。 ";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "告诉我, 你是怎么到这里来的? ";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "你想离开这个岛, 回到正常的生活吗? ";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "部落不会打扰你吗? ";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "这个岛是怎么形成的, 你有什么想法吗? ";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "没有问题。 抱歉... ";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "我是和那个自命不凡的家伙阿博特一起来到这里的。 我在他的船上服役。 你知道吗? 像他这样的人永远不应该踏上船甲板, 因为他们会带来厄运。 一定是魔鬼让他和我们一起航行的。 \n我们只需要从牙买加航行到伯利兹, 小菜一碟。 但厄运一直追着我们: 我们的水手长落水了, 领航员犯了个错误, 该死的西班牙人, 最后还有一场风暴。 然后我们就到了这里。 ";
			link.l1 = "有趣... ";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "我希望我知道, 伙计。 我曾经想过, 但现在不想了。 这里的生活很好, 有很多朗姆酒和葡萄酒, 好吃的食物, 虽然不多, 但无论如何都比我在船上吃的那些垃圾要好\n岛上也住着好人。 有可以一起喝酒或聊天的人。 我喜欢这里。 所以我甚至不确定... 不, 我想我不想离开。 我曾经又生气又饿, 看看我现在的肚子, 哈哈! ";
			link.l1 = "太好了! 我为你高兴。 ";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "不, 他们不打扰我。 只要不跟他们争论, 不未经允许就进入他们的领地。 他们真的不喜欢这样。 独角鲸族的人都很好, 他们大多数人都出生在这里, 从未见过其他的生活。 他们中的许多人都非常有技巧, 比如于尔根.施密特。 他是个铁匠之神! ";
			link.l1 = "我明白了... ";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "很简单。 浅滩和暗礁。 外围的环礁是由从上到下的船只组成的。 船只被风暴困住, 撞上暗礁或外围的环礁本身。 这就是岛屿增长的方式。 不过我不知道为什么内部的船只能浮在水面上。 ";
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
			link.l1 = LinkRandPhrase("好吧。 ", "随你便... ", "如你所说... ");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "听着, 我是这个城市的公民, 我希望你把刀收起来。 ", "听着, 我是这个城市的公民, 我希望你把刀收起来。 ");
				link.l1 = LinkRandPhrase("好吧。 ", "随便吧。 ", "如你所说... ");
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
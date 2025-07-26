// 阿尔瓦罗.戈麦斯 - 船长
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
				dialog.text = "哦, 一张新面孔! 问候你。 你什么时候到这儿的? 我不记得最近有船只失事。 ";
				link.l1 = TimeGreeting() + "。 我叫" +GetFullName(pchar)+ "。 我的船沉得如此安静和迅速, 没人注意到。 我也迅速而安静地到达了这个岛。 就像那样... ";
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
			dialog.text = "我明白了, 哦, 我忘了介绍自己。 请原谅, 先生。 我叫阿尔瓦罗.戈麦斯, 曾经是自己双桅船的船长。 唉, 现在我漂亮的双桅船正躺在外环后面的海底... 从那以后, 时光飞逝。 啊, 不管怎样。 很高兴见到你! ";
			link.l1 = "我也很高兴见到你, 戈麦斯先生。 ";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("有什么有趣的事情要说吗? ", "岛上有什么新鲜事吗? ", "你能给我讲讲最近的传闻吗? ");
			link.l2.go = "rumours_LSC";
			link.l3 = "我想问你几个关于这个岛的问题。 ";
			link.l3.go = "int_quests"; // 信息块
			NextDiag.TempNode = "First time";
		break;
		
//-------------------------------------—— 问答块 ---------------------------------------------
		case "int_quests":
			dialog.text = "我在听, 先生。 ";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "你说你曾是船长。 你是怎么到这个岛上的? ";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "关于岛上的生活, 你能告诉我什么? ";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "告诉我, 当地人在这里生活和平吗? 当然, 我不是说帮派之间。 ";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "当地人从哪里获得食物? ";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "没有问题。 抱歉... ";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "和其他人一样。 风暴困住了我, 我失去了桅杆和舵控。 我们被洋流带走, 抛到了礁石上。 我的船甚至没到外环就被毁了。 只有几个人幸存下来。 ";
			link.l1 = "悲伤的故事... ";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "我能说什么? 我们拥有体面生活所需的一切。 尽管有时这里真的很沉闷。 还有那种忧郁... 第一年是最糟糕的, 但后来我习惯了。 我为我可怜的妻子萨布丽娜感到难过, 她一定以为我死了。 我确实希望她设法再婚了\n别难过, 你会习惯的。 去酒馆。 商店。 教堂, 见见其他人。 除非万不得已, 否则不要去独角鲸或里瓦多那里, 他们是狡猾的混蛋。 ";
			link.l1 = "我明白了... ";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "真的, 这里秘密禁止争吵和打架。 如果你没有正当理由打人, 或者上帝保佑, 杀人, 那么你最终会被孤立。 你甚至可能在某天晚上被扔到海里。 岛上以前有几个好斗的人。 第一个就这么消失了, 第二个在塔塔罗斯的牢房里关了几个月后死了\n当然, 这并不意味着你不能保护自己。 但当地人实际上相当和平。 阿博特是个爱炫耀的人, 但不具攻击性。 卡塞尔是个真正的混蛋, 但他不沾手脏活。 普拉特是个前罪犯, 但他无害\n我们这里有两位前海军军官 --洛德拉代尔和索莱拉。 他们在不远处战斗时来到了这里。 具有讽刺意味的是, 他们都活了下来, 继续制定针对彼此的嗜血计划。 ";
			link.l1 = "知道了... ";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "当然是从货舱里。 所有从其他船上收集的食物, 过去都存放在圣奥古斯丁号上, 在海盗出现之前大家共享。 现在他们用拳头挤压这个岛, 因为他们拥有物资\n当然, 我们有自己的藏匿处, 所以没关系。 我们也射鸟和钓鱼... 但最好的狩猎以杀死一只巨型螃蟹结束。 它们的肉非常美味且有营养。 不过它们只在外环出现\n潜水捕猎它们太危险了。 曾经有一个勇敢的人在水下捕猎它们。 有一天他自己成了猎物。 从那以后, 没有人想在那里捕猎螃蟹了。 ";
			link.l1 = "有趣... ";
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
			link.l1 = LinkRandPhrase("好吧。 ", "当然。 ", "如你所说... ");
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
// <—— 特殊反应
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
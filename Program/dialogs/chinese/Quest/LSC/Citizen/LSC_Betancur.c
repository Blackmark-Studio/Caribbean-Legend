// 安东尼奥.贝坦库尔 - 弗朗西斯科.贝坦库尔的后裔
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
				dialog.text = "你好, 你好... 朋友, 你想要什么? ";
				link.l1 = TimeGreeting() + "。 我叫" +GetFullName(pchar)+ "。 我只是想知道你是谁。 看, 我是新来的, 在城里四处走走, 和人们聊聊天。 ";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "啊, " +GetFullName(pchar)+ "! " +TimeGreeting()+ "! 你这次想要什么? ";
				if(CheckAttribute(pchar, "questTemp.LSC.Betancur"))
				{
					link.l4 = "安东尼奥, 他们说你很了解这个岛的历史。 我有一个关于它的问题要问你。 ";
					link.l4.go = "dolly";
				}
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
			dialog.text = "太好了。 你会做得很好, 因为我们在这里都是一个大家庭。 当然, 除了独角鲸和肮脏的里瓦多人。 我叫安东尼奥, 安东尼奥.贝坦库尔。 如果这个名字对你有什么意义的话, 我是弗朗西斯科.贝坦库尔的孙子。 ";
			link.l1 = "弗朗西斯科.贝坦库尔? 我以前听过这个名字... 啊, 当然! 迪奥斯跟我讲过他, 我还在阿尔瓦拉多的笔记里读到过他... ";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "我不知道你的那个迪奥斯是谁, 但阿尔瓦拉多船长很久以前拜访过我们。 我小时候亲眼见过他。 他驶离了这个岛, 并在他的手稿中写下了关于它的内容。 而弗朗西斯科.贝坦库尔是一位西班牙舰队司令, 一支军事中队的指挥官\n由于所有里瓦多人都是中队旗舰'塔塔罗斯'号上黑奴的后代, 他开启了这个地方的历史。 独角鲸则是'塔塔罗斯'号。 '圣奥古斯丁'号和'圣赫罗尼莫'号首批白人定居者。 船员的后代。 ";
			link.l1 = "难以置信! 那么你是在这里出生的吗? ";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "没错。 我是那个基本上占领了这个岛的人的直系后代。 ";
			link.l1 = "我明白了。 很高兴认识你, 安东尼奥。 再见。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		// 任务部分
		case "dolly":
			dialog.text = "嗯... 当然, 朋友, 问吧。 我会回答你的问题, 当然, 前提是我知道答案。 ";
			link.l1 = "告诉我, 你还记得'圣赫罗尼莫'号大帆船还在这里的时候吗? ";
			link.l1.go = "dolly_1";
		break;
		
		case "dolly_1":
			dialog.text = "当然, 我记得。 那是一艘非常特别的船。 船上有一个有趣的印第安雕像, 这些肮脏的异教里瓦多人会进行献祭。 ";
			link.l1 = "他们是怎么做的? 像玛雅人一样挖出人们的心脏吗? 还是砍头? ";
			link.l1.go = "dolly_2";
		break;
		
		case "dolly_2":
			dialog.text = "不... 那是一个非常特别的雕像 --它把受害者拖进自己体内, 他们就永远消失了。 魔鬼的工具... 感谢上帝, 它和船一起沉没了, 再也不会造成任何伤害。 有趣的是, 献祭总是在早上同一时间进行。 雕像在初升太阳的光线下会变成金色\n那时野蛮人会带来受害者, 大多是他们俘虏的独角鲸。 ";
			link.l1 = "有趣! 有没有人尝试过探索这个雕像如何运作? ";
			link.l1.go = "dolly_3";
		break;
		
		case "dolly_3":
			dialog.text = "当然没有! 首先, 里瓦多人不让任何非自己人靠近'圣赫罗尼莫'号; 其次, 一个诚实的天主教徒必须远离魔鬼的行为。 ";
			link.l1 = "明白了。 我看你不喜欢里瓦多人。 对吗? ";
			link.l1.go = "dolly_4";
		break;
		
		case "dolly_4":
			dialog.text = "我不喜欢吗? 我恨那些肮脏的异教徒! 如果你不知道, 我爷爷是那艘船的船长, 黑人连同他们的领袖里瓦多在船上发动了叛变。 把他们所谓的领袖留在货舱里腐烂是正确的做法。 我还曾有一把来自圣安娜宝库的华丽钥匙\n没人知道宝库在哪里, 也许它在海底, 周围有螃蟹, 但这把钥匙对我来说是个甜蜜的纪念, 可它被偷了! 我确定是那些黑人干的。 他们一定在试图找到宝库。 我怀疑他们会成功, 时间太久了, 哈哈! 人渣... ";
			link.l1 = "我明白了。 谢谢你有趣的故事! ";
			link.l1.go = "dolly_5";
		break;
		
		case "dolly_5":
			dialog.text = "不客气, 我总是很高兴交谈! ";
			link.l1 = "再见! ";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.LSC.Betancur");
			AddQuestRecord("LSC", "16");
		break;
		
//-------------------------------------—— 问答块 ---------------------------------------------
		case "int_quests":
			dialog.text = "我在听, 伙计。 ";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "那么除了这个岛, 你一生中没见过别的东西吗? ";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "你在这里出生... 那你为什么不是独角鲸帮派的成员? 我以为所有本地白人都是独角鲸... ";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "你在这个岛上做什么? ";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "告诉我, 你有没有想过离开这个岛一段时间? 去看看世界... ";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "没有问题。 抱歉... ";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "似乎是这样, 是的。 但别以为我是个白痴或思想狭隘的人。 我从爷爷那里继承了一个很好的图书馆, 父亲给了我良好的教育。 我了解古代历史。 地理。 天文学, 我懂英语。 法语。 西班牙语, 甚至拉丁语\n很多去过各地的水手知道的都比我少。 尽管除了这些沉船我什么都没见过, 但我在精神上已经游历了欧洲。 中国和印度... ";
			link.l1 = "我明白了... ";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "虽然你有百分之九十是对的, 但这不是真的。 但我不是独角鲸, 我也不想成为其中一员。 为了什么目的? 像个傻瓜一样站几个小时的岗, 或者和里瓦多人战斗? 不可能, 饶了我吧。 我不一样。 我更喜欢独立生活和读书。 ";
			link.l1 = "我明白了... ";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "父亲给我留下了一笔可观的遗产, 我小心地花费。 所以我不需要在旧沉船周围潜伏寻找珠宝来换取食物。 我不相信旧船里有巨大的宝藏\n我知道的唯一宝藏是圣安娜的宝库。 那是一个大铁箱。 但还没人找到它\n另外, 我打算根据当地故事写一本详细的岛屿历史。 你觉得 --我应该试试吗? ";
			link.l1 = "我确信应该。 我知道群岛上至少有一个人会为这样的书支付很多金子。 所以这是你的机会... ";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "有时我会想。 也许如果有一艘能应对洋流并在风暴中幸存的船来到这里, 我会冒险。 我真的很想看看我书中描述得如此有趣的东西! 但现在这些只是梦想... ";
			link.l1 = "梦想会成真。 只要相信它们... ";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <—— 问答块
		
//---------------------------------------—— 特殊反应 -----------------------------------------------
		// 发现主角在箱子里
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("你在那里干什么, 啊? 小偷! ", "看看这个! 我一不留神, 你就决定检查我的箱子了! ", "决定检查我的箱子了? 你逃不掉的! ");
			link.l1 = "废话! ";
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
			link.l1 = LinkRandPhrase("好吧。 ", "如你所愿... ", "如你所说... ");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "听着, 我是这个城市的公民, 我希望你把刀收起来。 ", "听着, 我是这个城市的公民, 我希望你把刀收起来。 ");
				link.l1 = LinkRandPhrase("好吧。 ", "如你所愿... ", "如你所说... ");
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
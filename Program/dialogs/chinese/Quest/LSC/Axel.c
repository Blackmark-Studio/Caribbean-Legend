// 商人阿克塞尔.约斯特
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
				dialog.text = "你看看这是谁... "+GetFullName(pchar)+"! 你从阴间回来了? 这怎么可能? ";
				link.l1 = "人可不会从阴间回来, 阿克塞尔。 很简单 —我根本没死, 哈哈! ";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = "嘿, 伙计, 在你和独角鲸帮把事情解决之前, 我不会和你做生意。 我不想惹麻烦。 去找法奇奥, 他能处理这个。 ";
				link.l1 = "好吧, 我马上去处理。 ";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "我不想和你说话。 你无缘无故攻击和平的人, 还煽动他们打架。 滚开! ";
				link.l1 = "嗯... ";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "哦! 一张新面孔! 什么风把你吹来了? 不过, 这不关我的事。 让我自我介绍一下: 我叫阿克塞尔.约斯特, 这家店是我的。 看到你喜欢的东西了吗? ";
				link.l1 = TimeGreeting()+"。 我叫"+GetFullName(pchar)+"。 你有什么货? ";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "啊, "+pchar.name+"! 很高兴见到你。 你想买点什么还是卖点什么? ";
				// 任务分支
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "search_mush_1")
				{
					link.l4 = "听着, 阿克塞尔, 你有好的滑膛枪卖吗? 不是普通士兵的手枪, 是那种精准且射程远的? ";
					link.l4.go = "adolf";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "trader_whiskey")
				{
					link.l4 = "听着, 阿克塞尔, 查德.卡珀让你给他弄一桶威士忌了吗? ";
					link.l4.go = "whiskey";
				}
				if (CheckAttribute(npchar, "quest.ole_pearl"))
				{
					link.l5 = "听着, 阿克塞尔, 你一定听到了我和那个本地傻瓜的谈话。 他要的是什么珠子? 我没弄明白。 ";
					link.l5.go = "ole_pearl";
				}
				link.l1 = "是的。 我们交易吧, 阿克塞尔! ";
				link.l1.go = "Trade_items";
				link.l2 = LinkRandPhrase("有什么有趣的事要告诉我吗? ", "岛上最近发生了什么事? ", "有什么八卦吗? ");
				link.l2.go = "rumours_LSC";
				link.l3 = "还没有。 只是想跟你打个招呼。 ";
				link.l3.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "各种各样的东西。 混合物。 刀刃。 火器。 弹药。 胸甲。 宝石和矿物。 附魔的护身符和护身符。 垃圾和日常用品。 人们把他们在失事船只上找到的所有东西都带给我, 那些他们自己不需要的东西\n所以你也可以这么做。 不过, 我必须警告你。 我不提供食物或船上用品。 ";
			link.l1 = "好的, 阿克塞尔。 让我看看你的货。 ";
			link.l1.go = "Trade_items";
			link.l2 = "谢谢你, 阿克塞尔。 我会记住的。 一旦我需要你的服务, 我会来看你的。 ";
			link.l2.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "Trade_items":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 5)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;
		
		// 指向阿道夫的提示
		case "adolf":
			dialog.text = "这一定是某种玩笑。 你是第三个人问了。 我这里不携带这种武器。 但几个月前, 阿道夫.巴比耶试图把他的带瞄准镜的施图岑猎枪卖给我。 我告诉你, 那是一件很棒的武器。 正是你要找的\n但巴比耶要价太高了。 所以, 我不得不拒绝了他的报价。 ";
			link.l1 = "有意思! 我在哪里可以找到巴比耶? ";
			link.l1.go = "adolf_1";
		break;
		
		case "adolf_1":
			dialog.text = "我不知道。 他可能在某个地方闲逛。 他经常去桑乔的酒馆, 他喜欢每天晚上喝一杯。 ";
			link.l1 = "谢谢! 我想我会在那里找到他。 告诉我, 阿克塞尔, 还有谁问过你关于步枪的事? 你提到过还有其他人感兴趣, 他们会是谁? ";
			link.l1.go = "adolf_2";
		break;
		
		case "adolf_2":
			dialog.text = "玛丽.卡斯帕和马塞洛, 也被称为独眼龙。 我不知道这个女孩为什么需要步枪, 但我们的红玛丽是出了名的狂人。 一年前, 她买了大量火药来制造地雷, 她说要用来击晕螃蟹\n谢天谢地, 她没被允许这么做\n而马塞洛想买一支步枪来猎鸟, 他吃咸牛肉吃腻了。 我把他们都介绍给了阿道夫, 不知道他们有没有从他那里买步枪\n还有, 那个狡猾的家伙朱塞佩.法奇奥最近也打听过阿道夫。 也许, 他也想买这支施图岑猎枪。 ";
			link.l1 = "呵, 我的竞争对手还真不少。 好吧, 我去找阿道夫 —希望他还没把枪卖掉。 ";
			link.l1.go = "adolf_3";
		break;
		
		case "adolf_3":
			DialogExit();
			pchar.questTemp.Saga.SharkHunt = "search_mush_2"; // 酒馆标记
			AddQuestRecord("SharkHunt", "12");
			sld = characterFromId("LSC_Adolf");
			sld.lifeday = 0; // 移除真正的阿道夫
		break;
		
		// 给白小子的珠子 - 只是信息
		case "ole_pearl":
			dialog.text = "这谁都知道, 先生! 他见人就问这些珠子, 他把大珍珠叫做珠子。 给他一颗, 你就会成为他最好的朋友。 ";
			link.l1 = "现在我明白了。 谢谢你, 阿克塞尔, 我自己永远也猜不到。 ";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "quest.ole_pearl");
		break;
		
		// 给鲨鱼的威士忌
		case "whiskey":
			dialog.text = "是的, 伙计, 他确实问过。 但如果你也想买一桶布什米尔威士忌, 我会让你失望的。 我只有一桶, 查德买走了。 我可以给你苏格兰威士忌 —和爱尔兰威士忌一样好, 实际上, 我更喜欢它的味道。 ";
			link.l1 = "也许以后吧。 查德还从你这里买了别的东西吗? ";
			link.l1.go = "whiskey_1";
		break;
		
		case "whiskey_1":
			dialog.text = "没有。 他对砒霜感兴趣, 他说塔塔罗斯的老鼠太多了, 他想把它们消灭掉。 自从我雇了那个傻瓜奥勒来打扫我的店, 我就不需要砒霜了, 所有的老鼠都跑到可怜的桑乔的酒馆去了。 我不知道为什么老鼠这么怕奥勒... ";
			link.l1 = "也许, 他家里有猫... ";
			link.l1.go = "whiskey_2";
		break;
		
		case "whiskey_2":
			dialog.text = "哈哈! 也许吧... 桑乔肯定有砒霜。 ";
			link.l1 = "我明白了。 那就谢谢你的信息了! ";
			link.l1.go = "whiskey_3";
		break;
		
		case "whiskey_3":
			DialogExit();
			AddQuestRecord("SharkHunt", "36");
			pchar.questTemp.Saga.SharkHunt = "barmen_whiskey"; // 酒馆标记 - 寻找老鼠药
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
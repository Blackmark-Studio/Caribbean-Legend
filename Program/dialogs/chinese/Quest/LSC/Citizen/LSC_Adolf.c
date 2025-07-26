// 阿道夫.巴比尔 - 冒险家
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
				dialog.text = "你好, 你好... 我以前没见过你。 最近来的? ";
				link.l1 = "你是说最近到岛上? 是的。 我叫" +GetFullName(pchar)+ ", 一个水手和冒险家。 ";
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
			dialog.text = "哈, 和我一样。 不过我不是水手, 但对冒险的热情把我带到了这里。 现在我像其他人一样被困在这片船只坟场里。 顺便说一句, 我叫阿道夫.巴比尔。 ";
			link.l1 = "很高兴认识你, 阿道夫。 再见。 ";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("有什么有趣的事要说吗? ", "岛上有什么新鲜事吗? ", "能告诉我最新的八卦吗? ");
			link.l2.go = "rumours_LSC";
			link.l3 = "我想问你几个关于这个岛的问题。 ";
			link.l3.go = "int_quests"; // 信息区块
			NextDiag.TempNode = "First time";
		break;
		
		//----------------------------------阿道夫.巴比尔----------------------------------------
		case "Adolf":
			dialog.text = "你他妈的为什么未经允许闯入我的住所? ";
			link.l1 = "你对客人太没礼貌了, 阿道夫。 我是来和你谈生意的。 ";
			link.l1.go = "Adolf_1";
		break;
		
		case "Adolf_1":
			dialog.text = "我不跟陌生人做生意! 出去! ";
			link.l1 = "就这样? 你跟独角鲸帮做生意, 却不跟我做? 真丢脸... ";
			link.l1.go = "Adolf_2";
		break;
		
		case "Adolf_2":
			dialog.text = "你在胡说什么, 小丑? 跟独角鲸帮做什么生意? 这是你滚出去的最后机会, 否则我就亲自把你扔出去! ";
			link.l1 = "你没胆子这么做, ‘扔人大师’... 现在听着。 你准备用来射杀舰队司令的短管步枪在哪? 你是自己说, 还是要我让你开口? ";
			link.l1.go = "Adolf_3";
		break;
		
		case "Adolf_3":
			dialog.text = "什么? 什么短管步枪? 什么舰队司令? 你疯了吗, 伙计? 我已经把短管步枪卖掉了, 现在没有了。 我卖给谁不关你的事。 他们用它做什么我也不在乎。 我不打算射杀任何人 --不管是舰队司令还是将军。 你明白吗, 混蛋? ";
			link.l1 = "我只知道你是个骗子和杀人犯, 阿道夫。 我知道你没卖掉, 而是赎回了它。 我还知道你拿了一大笔钱还债和买这个船舱... ";
			link.l1.go = "Adolf_4";
		break;
		
		case "Adolf_4":
			dialog.text = "这是我的钱, 混蛋! 我自己赚的! 我已经卖掉了短管步枪! ";
			link.l1 = "你在撒谎, 阿道夫。 你被独角鲸帮雇来射杀舰队司令。 他们给你钱赎回短管步枪, 还付钱买了这个地方。 你比我清楚, 这扇门后面的船首斜桅是岛上唯一能射击鲨鱼住所后阳台的地方。 ";
			link.l1.go = "Adolf_5";
		break;
		
		case "Adolf_5":
			dialog.text = "你疯了, 混蛋! 你该立刻被关起来! 塞斯尔离开这里之前, 我等这个船舱等了半年... ";
			link.l1 = "够了。 我会搜查你和你的船舱, 肯定能找到短管步枪和更多证据。 然后我们一起去见鲨鱼。 他会很高兴直视你的眼睛。 ";
			link.l1.go = "Adolf_6";
		break;
		
		case "Adolf_6":
			dialog.text = "啊, 你个变态! 我宁愿死, 也不让疯子碰我的东西! ";
			link.l1 = "那我就不经你允许自己动手了... ";
			link.l1.go = "Adolf_7";
		break;
		
		case "Adolf_7":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//允许战斗
			chrDisableReloadToLocation = true;//关闭地点
			DialogExit();
			LAi_SetWarriorType(npchar);
			ChangeCharacterAddressGroup(npchar, pchar.location, "barmen", "stay");
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetImmortal(npchar, false);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LSC_AdolfDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
//-------------------------------------—— 问答区块 ---------------------------------------------
	case "int_quests":
			dialog.text = "好吧, 我们聊聊。 你想知道什么? ";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "你是怎么到这里来的? ";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "你能跟我说说当地的帮派吗? ";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "你探索过外围的船只吗? ";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "这个岛和古巴或大陆有联系吗? ";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "没问题了。 失陪... ";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "我找到了一个水手的手稿 --阿尔瓦拉多, 西班牙人。 他详细描述了这个岛, 提到了几艘有趣的船: 圣奥古斯丁号。 圣赫罗尼莫号和塔尔塔罗斯号。 它们都是德贝坦库尔特舰队的一部分, 五十年前失踪了\n我研究了那次探险。 结果发现还有第四艘船叫圣安娜号, 载着舰队的财宝 --大量达布隆! 此外, 船上还有金矿石。 我决定找到这个岛\n我和一个认识的船长做了笔交易, 乘他的纵帆船起航。 我猜故事的结局你也清楚了。 我们找到了这个岛。 德贝坦库尔特的船, 甚至他的后代 --安东尼奥.德贝坦库尔特就住在这里。 但我没能离开\n纵帆船触礁损坏, 同伴死了, 我和其他幸存者来到这里。 最糟糕的是我没找到想要的东西 --既没有圣安娜号的财宝, 也没有金矿石。 ";
			link.l1 = "我也读过阿尔瓦拉多的笔记。 很有趣的故事。 ";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "里瓦多斯帮是该死的异教败类。 他们是德贝坦库尔特从非洲带来的黑奴后代。 虽然他们从白人那里学会了使用刀剑和火枪, 但仍是野蛮人\n独角鲸帮是好人, 聪明且战斗能力强, 他们中有杰出的工匠。 我认识很多独角鲸帮的人, 也许有一天我会加入他们\n海盗是群混蛋, 该死的。 我们没叫他们来, 他们却来了, 抢走我们的补给, 还敢把我们自己的食物卖给我们! 混蛋, 对吧? 可惜我们赶不走他们, 只能和他们共处。 ";
			link.l1 = "有意思... ";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "当然。 人得赚钱。 该死的海盗要金子。 比索或各种贵重物品来换食物。 他们卖给我这样的本地人比卖给帮派便宜些, 但也不是慈善。 谢天谢地, 外围有足够的船只可以掠夺, 很多自失事以来就没人动过\n这是个有趣的活动, 但也危险: 可能掉进积水的船舱。 摔断骨头。 被绳子缠住。 被木片砸到, 或者遇到巨型螃蟹 --它们经常光顾那里的船舱。 ";
			link.l1 = "我明白了... ";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "可惜没有。 据说很久以前, 古巴的海盗和走私者会来这里 --用物资交换黄金和货物。 甚至独角鲸帮也去过定居点。 但现在都是历史了。 没人敢乘脆弱的小船冒险。 风暴瞬间就能摧毁小船, 而我们这里没有更好的船只。 ";
			link.l1 = "我明白了... ";
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
			link.l1 = LinkRandPhrase("好的。 ", "好的。 ", "如你所说... ");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "听着, 我是这个城市的公民, 我请你收剑。 ", "听着, 我是这个城市的公民, 我请你收剑。 ");
				link.l1 = LinkRandPhrase("好的。 ", "好的。 ", "如你所说... ");
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
// 尤尔根.施密特 - 武器匠
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp, iRem;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	string NodeName = Dialog.CurrentNode;
	string NodePrevName = "";
	if (CheckAttribute(NextDiag, "PrevNode")) NodePrevName = NextDiag.PrevNode;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = "听着, 先生, 你为什么要动手? 你现在是我们的敌人, 别在我的工坊里晃悠。 出去! ";
				link.l1 = "嗯... ";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) // 成为独角鲸帮的朋友
				{
					dialog.text = "啊, " +GetFullName(pchar)+ "! 我听说了你的事迹。 很高兴你成为了唐纳德的朋友和我们的盟友。 独角鲸帮懂得感恩, 这一点我可以肯定。 ";
					link.l1 = "希望如此。 我现在可以请你帮忙吗? ";
					link.l1.go = "friend";
				}
				else
				{
					dialog.text = "那么? 你想要什么? ";
					link.l1 = TimeGreeting() + "。 我叫" +GetFullName(pchar)+ "。 只是随便走走, 认识一下大家。 打扰你了吗? ";
				link.l1.go = "meeting";
				}
				npchar.quest.meeting = "1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) // 成为独角鲸帮的朋友
				{
					dialog.text = "啊, " +GetFullName(pchar)+ "! 我听说了你的事迹。 很高兴你成为了唐纳德的朋友和我们的盟友。 独角鲸帮懂得感恩, 这一点我可以肯定。 ";
					link.l1 = "希望如此。 我现在可以请你帮忙吗? ";
					link.l1.go = "friend";
				}
				else
				{
					dialog.text = "啊, " +GetFullName(pchar)+ "! 又想聊天? 恐怕我没时间也没兴趣。 ";
					link.l1 = "好吧, 不打扰你了。 ";
					link.l1.go = "exit";
				}
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // 第一次见面
			dialog.text = "没错! 你就是在打扰我, 先生。 我是尤尔根.施密特, 独角鲸帮的武器匠和铁匠。 我为我们的人提供武器。 但打造一把好剑。 钥匙。 锁或者修理塔式燧发枪的机械装置都需要时间。 这需要大量的时间。 耐心和专注。 所以我不喜欢别人打扰我。 ";
			link.l1 = "你会制作武器? 我能向你订购吗? ";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "不行。 我只给独角鲸帮成员制作武器。 这是我的原则, 我会坚持。 所以别抱希望了, 先生。 要么加入我们帮派, 至少成为我们的盟友, 那样我们再谈。 ";
			link.l1 = "好吧。 那我走了。 抱歉打扰! ";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "friend":
			dialog.text = "可以。 独角鲸帮的朋友也是我的朋友, 我听你说。 ";
			link.l1 = "我想订购一把剑。 ";
			link.l1.go = "blade";
			if (CheckAttribute(npchar, "quest.narval_blade") && pchar.questTemp.LSC.Mary == "alive")
			{
				link.l2 = "我听说你为已故的艾伦.米尔罗打造过一把特殊的剑。 我见过那把阔剑, 非常厉害。 我能订购类似的吗? ";
				link.l2.go = "narval";
			}
			link.l3 = "我还没想好。 我考虑一下再来! ";
			link.l3.go = "exit";
			NextDiag.TempNode = "Jurgen";
		break;
		
		case "Jurgen":
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "哈, " +GetFullName(pchar)+ "! 这么说你没淹死? 真不可思议! 你真的还活着? ";
				link.l1 = "别担心, 尤尔根。 我活着! 我可没打算淹死... ";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				NextDiag.TempNode = "Jurgen";
				break;
			}
			dialog.text = "啊, " +GetFullName(pchar)+ "! 你想要什么? ";
			if (CheckAttribute(npchar, "quest.narval_blade") && npchar.quest.narval_blade == "ferrum")
			{
				if (GetCharacterItem(pchar, "jewelry11") >= 3)
				{
					link.l4 = "我按你要求带来了三块特殊铁矿石。 看看, 是你要的吗? ";
					link.l4.go = "narval_7";
				}
				if (CheckCharacterItem(pchar, "meteorite"))
				{
					link.l5 = "看看这个, 尤尔根。 我在海底找到一块有趣的铁锭, 但比你要的重得多。 至少五磅。 ";
					link.l5.go = "narval_7_1";
				}
			}
			if (!CheckAttribute(npchar, "quest.blade_done"))
			{
				link.l1 = "我想订购一把剑。 ";
				if (!CheckAttribute(npchar, "quest.blade_rules")) link.l1.go = "blade";
				else link.l1.go = "blade_4";
			}
			if (CheckAttribute(npchar, "quest.blade_payseek"))
			{
				link.l1 = "我带来了更多达布隆支付剑的费用。 ";
				link.l1.go = "blade_3";
			}
			if (CheckAttribute(npchar, "quest.narval_blade") && pchar.questTemp.LSC.Mary == "alive" && npchar.quest.narval_blade == "begin" && pchar.questTemp.LSC != "return") // patch-9
			{
				link.l2 = "我听说你为已故的艾伦.米尔罗打造过一把特殊的剑。 我见过那把阔剑, 非常厉害。 我能订购类似的吗? ";
				link.l2.go = "narval";
			}
			if (CheckAttribute(npchar, "blade_date") && GetNpcQuestPastDayParam(npchar, "blade_date") >= 20)
			{
				link.l1 = "我来取订单。 应该已经完成了, 对吗? ";
				link.l1.go = "blade_done_2";
			}
			link.l3 = "不, 没什么, 只是想问候一下。 ";
			link.l3.go = "exit";
			NextDiag.TempNode = "Jurgen";
		break;
		
		// --> 订购刀剑
		case "blade":
			dialog.text = "好的。 但我的订单有特殊要求, 先仔细听好。 ";
			link.l1 = "我洗耳恭听。 ";
			link.l1.go = "blade_1";
		break;
		
		case "blade_1":
			dialog.text = "你只能向我订购一把剑, 且只能订一次。 我不做特定武器, 你只需说明类型 —细剑。 军刀或阔剑。 做选择前仔细考虑, 最终剑的特性和质量取决于我目前拥有的材料\n现在, 制作需要二十天。 我只收达布隆。 一千枚金币。 先付款。 ";
			link.l1 = "真贵... ";
			link.l1.go = "blade_2";
		break;
		
		case "blade_2":
			dialog.text = "是贵。 但我做的是精品刀剑, 价格很公道。 反正你自己决定, 不强迫。 ";
			link.l1 = "知道了, 尤尔根。 我想下订单。 ";
			link.l1.go = "blade_3";
			link.l2 = "嗯。 在向你订购前我需要时间考虑。 以后再谈! ";
			link.l2.go = "exit";
			NextDiag.TempNode = "Jurgen";
			npchar.quest.blade_rules = "true";
			npchar.quest.blade_dublon = 1000;
			AddQuestRecord("LSC", "17");
		break;
		
		case "blade_3":
			dialog.text = "很好。 把达布隆给我吧。 ";
			if (PCharDublonsTotal() > 0)
			{
				npchar.quest.blade_pay = PCharDublonsTotal();
				link.l1 = "给你。 我有" + FindRussianQtyString(sti(npchar.quest.blade_pay)) + "枚。 ";
				link.l1.go = "blade_pay";
			}
			link.l2 = "嗯。 可惜我现在没带。 但我肯定会带来, 然后我们继续谈。 ";
			link.l2.go = "exit";
			NextDiag.TempNode = "Jurgen";
		break;
		
		case "blade_4":
			dialog.text = "所以这是你的最终选择? 确定吗? ";
			link.l1 = "是的, 确定。 ";
			link.l1.go = "blade_3";
		break;
		
		case "blade_pay": // 付款
			if (sti(npchar.quest.blade_dublon) < sti(npchar.quest.blade_pay)) // 全额支付
			{
				npchar.quest.blade_pay = sti(npchar.quest.blade_dublon);
				iTemp = 0;
			}
			else iTemp = sti(npchar.quest.blade_dublon)-sti(npchar.quest.blade_pay);
			npchar.quest.blade_dublon = iTemp; // 记录余额
			RemoveDublonsFromPCharTotal(sti(npchar.quest.blade_pay));
			Log_Info("你给了" + sti(npchar.quest.blade_pay) + "枚达布隆");
			PlaySound("interface\important_item.wav");
			if (iTemp == 0)
			{
				dialog.text = "太好了。 你已经支付了制作费用和材料费用, 我可以开始了。 ";
				link.l1 = "我可以下订单了吗? ";
				link.l1.go = "blade_done";
			}
			else
			{
				dialog.text = "好的。 我收下这些达布隆。 你还需要再带来" + FindRussianQtyString(sti(npchar.quest.blade_dublon)) + "枚。 ";
				link.l1 = "等我有了就带来。 ";
				link.l1.go = "exit";
				npchar.quest.blade_payseek = "true";
			}
		break;
		
		case "blade_done":
			DeleteAttribute(npchar, "quest.blade_payseek");
			dialog.text = "当然! 你最喜欢哪种类型? 细剑。 军刀还是阔剑? ";
			link.l1 = "细剑。 我喜欢优雅轻便的武器。 ";
			link.l1.go = "rapier";
			link.l2 = "军刀。 我认为它们最实用。 ";
			link.l2.go = "sabre";
			link.l3 = "当然是阔剑! 劈砍起来爽快! ";
			link.l3.go = "palash";
		break;
		
		case "rapier":
			npchar.quest.blade_done = SelectJurgenBladeDone("rapier");
			dialog.text = "如你所愿。 二十天后再来取, 别早来。 ";
			link.l1 = "谢谢! 二十天后见。 再见, 尤尔根。 ";
			link.l1.go = "blade_done_1";
		break;
		
		case "sabre":
			npchar.quest.blade_done = SelectJurgenBladeDone("sabre");
			dialog.text = "如你所愿。 二十天后再来取, 别早来。 ";
			link.l1 = "谢谢! 二十天后见。 再见, 尤尔根。 ";
			link.l1.go = "blade_done_1";
		break;
		
		case "palash":
			npchar.quest.blade_done = SelectJurgenBladeDone("palash");
			dialog.text = "如你所愿。 二十天后再来取, 别早来。 ";
			link.l1 = "谢谢! 二十天后见。 再见, 尤尔根。 ";
			link.l1.go = "blade_done_1";
		break;
		
		case "blade_done_1":
			DialogExit();
			SaveCurrentNpcQuestDateParam(npchar, "blade_date");
			NextDiag.CurrentNode = "Jurgen";
			AddQuestRecord("LSC", "18");
		break;
		
		case "blade_done_2":
			dialog.text = "是的。 你的剑已经完成。 请拿去吧, 使用它。 你一触摸就会明白它物有所值。 ";
			link.l1 = "谢谢, 尤尔根。 ";
			link.l1.go = "blade_done_3";
		break;
		
		case "blade_done_3":
			DialogExit();
			NextDiag.CurrentNode = "Jurgen";
			GiveItem2Character(pchar, npchar.quest.blade_done);
			PlaySound("interface\important_item.wav");
			DeleteAttribute(npchar, "blade_date");
		break;
		
		// 为玛丽订购独角鲸阔剑
		case "narval":
			dialog.text = "可惜, 朋友, 我得拒绝, 有两个原因。 第一, 我只给独角鲸帮成员制作这种阔剑, 而且是特别的人。 第二, 我没有材料。 ";
			link.l1 = "你需要的特殊铁是什么? 我听说那是从海底找到的... ";
			link.l1.go = "narval_1";
		break;
		
		case "narval_1":
			dialog.text = "没错。 我们浅滩周围散落着这种金属块。 我不知道它们怎么来的。 但这种铁很独特, 永远不会生锈, 用它做的刀剑永远不会变钝。 所以如果你能弄到这种铁, 我们或许可以解决问题。 但还有个问题, 你不是独角鲸帮的... ";
			link.l1 = "这真的重要吗? ";
			link.l1.go = "narval_2";
		break;
		
		case "narval_2":
			dialog.text = "是的。 你可以认为这是我的怪癖, 但我只给独角鲸帮成员制作这种阔剑。 ";
			link.l1 = "好吧... 行。 但我有个想法。 我能为独角鲸帮成员订购这把剑吗? ";
			link.l1.go = "narval_3";
		break;
		
		case "narval_3":
			dialog.text = "嗯。 我想如果你能带来铁, 应该可以。 这不违反我的原则... 你想让我为谁制作这把阔剑? ";
			link.l1 = "为红玛丽。 她是独角鲸帮的, 她值得拥有这样一把出色的武器。 ";
			link.l1.go = "narval_4";
		break;
		
		case "narval_4":
			dialog.text = "哈! 我早该想到。 我真是老了... 好吧, 我同意。 玛丽收到这样的礼物一定会很高兴, 我确定... 把铁带来, 我就制作阔剑。 至于费用... 啊, 算了, 我免费做。 这不仅是你的礼物, 也是我们俩的心意。 ";
			link.l1 = "谢谢! 你需要多少铁? ";
			link.l1.go = "narval_5";
		break;
		
		case "narval_5":
			dialog.text = "我们在海底找到的那些铁块都差不多 —每块一磅。 我需要三块这样的。 ";
			link.l1 = "好的。 我会试着找到它们。 我们回头再谈。 ";
			link.l1.go = "narval_6";
		break;
		
		case "narval_6":
			DialogExit();
			npchar.quest.narval_blade = "ferrum";
			NextDiag.CurrentNode = "Jurgen";
			// 在海底放置巨大的陨石块
			sld = ItemsFromID("meteorite");
			sld.shown = true;
			sld.startLocation = "underwater";
			sld.startLocator = "item"+(rand(7)+1);
			Log_TestInfo("陨石在定位器 " + sld.startLocator);
			pchar.quest.LSC_narval_ferrum.win_condition.l1 = "item";
			pchar.quest.LSC_narval_ferrum.win_condition.l1.item = "meteorite";
			pchar.quest.LSC_narval_ferrum.function = "LSC_NarvalFerrum";
			AddQuestRecord("LSC", "19");
		break;
		
		case "narval_7":
			RemoveItems(pchar, "jewelry11", 3);
			PlaySound("interface\important_item.wav");
			dialog.text = "让我看看... 对! 就是这个! 在海底找这么小的碎片很难吗? ";
			link.l1 = "怎么说呢... 为了玛丽, 这点麻烦值得, 不是吗? ";
			link.l1.go = "narval_8";
			pchar.quest.LSC_narval_ferrum.over = "yes"; // 取消中断
		break;
		
		case "narval_7_1":
			RemoveItems(pchar, "meteorite", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "让我看看... 这可不常见! 是的, 是海底的铁, 但我从没见过这么大的块。 这块足够制作阔剑了。 找到它很难吗? ";
			link.l1 = "怎么说呢... 为了玛丽, 这点麻烦值得, 不是吗? ";
			link.l1.go = "narval_8";
		break;
		
		case "narval_8":
			dialog.text = "我越来越喜欢你了, " +pchar.name+ "... 很好。 现在该我为我们美丽的亚马逊女战士出力了。 制作阔剑需要两天, 我会把其他订单放一边\n后天带玛丽来见我。 别告诉她, 这是惊喜。 她会高兴得像个孩子。 ";
			link.l1 = "好的, 尤尔根。 就这么定了! 后天见! ";
			link.l1.go = "narval_9";
		break;
		
		case "narval_9":
			DialogExit();
			npchar.quest.narval_blade = "work";
			NextDiag.CurrentNode = "narval_10";
			SetFunctionTimerCondition("LSC_NarvalBladeForMary", 0, 0, 2, false); // 计时器
			AddQuestRecord("LSC", "21");
		break;
		
		case "narval_10":
			dialog.text = ""+pchar.name+", 别打扰我。 你想让我按时做好阔剑, 不是吗? ";
			link.l1 = "是的, 当然。 我走了。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "narval_10";
		break;
		
//--------------------------------------- —特殊反应 -----------------------------------------------
		// 发现玩家在箱子里
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("你在那里做什么, 啊? 小偷! ", "看看那个! 我一沉思, 你就决定检查我的箱子! ", "决定检查我的箱子? 你不会得逞的! ");
			link.l1 = "该死! ";
			link.l1.go = "fight";
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
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
// < —特殊反应
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

string SelectJurgenBladeDone(string _sType)
{
	string sBlade;
	switch (_sType)
	{
		case "rapier":
			if (sti(pchar.rank) > 15) sBlade = "q_blade_18"; 
			else sBlade = "q_blade_16";
		break;
		
		case "sabre":
			if (sti(pchar.rank) > 15) sBlade = "q_blade_19"; 
			else sBlade = "q_blade_10";
		break;
		
		case "palash":
			if (sti(pchar.rank) > 15) sBlade = "q_blade_21"; 
			else sBlade = "q_blade_13";
		break;
	}
	return sBlade;
}
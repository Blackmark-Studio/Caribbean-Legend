// 朱利安兄弟 - 牧师
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp;

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
				dialog.text = "我不想和你说话。 你无缘无故攻击和平的当地人, 还挑衅他们打架。 滚开, 无神论者! ";
				link.l1 = "如你所愿... ";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "你能活下来我并不惊讶。 主的道路是神秘的。 生与死都在祂的手中。 ";
				link.l1 = "我完全同意你的看法, 朱利安兄弟。 ";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "欢迎来到我们岛上的圣教堂, 我的孩子。 门永远为你敞开。 我是朱利安兄弟, 很高兴见到任何我们伟大主的仆人。 ";
				link.l1 = TimeGreeting()+"。 我叫"+GetFullName(pchar)+"。 很高兴见到你, 朱利安兄弟。 ";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "啊, "+GetFullName(pchar)+"! "+TimeGreeting()+"! 想要点什么? ";
				link.l1 = "我想问你几个关于这个岛的问题。 ";
				link.l1.go = "int_quests"; //信息块
				link.l2 = "我能从你这里买些药水吗? ";
				link.l2.go = "potion";
				link.l3 = "你有什么圣物要卖吗? ";
				link.l3.go = "amulet";
				link.l5 = "只是想在这里祈祷, 看看你过得怎么样。 再见! ";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // 第一次见面
			dialog.text = "我希望你能更经常地参观我们的教堂。 照顾好你的灵魂, 我的孩子。 我也能治愈你的身体, 我在这里不仅是牧师, 也是医生。 ";
			link.l1 = "我想问你几个关于这个岛的问题。 ";
			link.l1.go = "int_quests"; //信息块
			link.l2 = "我能从你这里买些药水吗? ";
			link.l2.go = "potion";
			link.l3 = "你有什么圣物要卖吗? ";
			link.l3.go = "amulet";
			link.l4 = "我得走了, 朱利安兄弟。 再见! ";
			link.l4.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "potion":
			dialog.text = "当然, 我的孩子。 你需要什么药水? ";
			if (!CheckAttribute(npchar, "potion1_date") || GetNpcQuestPastDayParam(npchar, "potion1_date") >= 1)
			{
				link.l1 = "一瓶简单的治疗药水。 ";
				link.l1.go = "potion1";
			}
			if (!CheckAttribute(npchar, "potion2_date") || GetNpcQuestPastDayParam(npchar, "potion2_date") >= 1)
			{
				link.l2 = "一瓶治疗灵药。 ";
				link.l2.go = "potion2";
			}
			if (!CheckAttribute(npchar, "potion3_date") || GetNpcQuestPastDayParam(npchar, "potion3_date") >= 1)
			{
				link.l3 = "一瓶解毒剂。 ";
				link.l3.go = "potion3";
			}
			if (!CheckAttribute(npchar, "potion4_date") || GetNpcQuestPastDayParam(npchar, "potion4_date") >= 1)
			{
				link.l4 = "一瓶草药合剂。 ";
				link.l4.go = "potion4";
			}
			link.l5 = "对不起, 朱利安兄弟, 我改变主意了。 ";
			link.l5.go = "exit";
		break;
		
		case "potion1":
			npchar.quest.price = 90;
			npchar.quest.type = 1;
			dialog.text = "一瓶药水? 90比索, 我的孩子。 ";
			if (sti(Pchar.money) >= 90)
			{
				link.l1 = "拿去吧, 朱利安兄弟。 ";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "我现在没有足够的硬币... 我稍后再来。 ";
				link.l1.go = "exit";
			}
		break;
		
		case "potion2":
			npchar.quest.price = 500;
			npchar.quest.type = 2;
			dialog.text = "一瓶灵药? 500比索, 我的孩子。 ";
			if (sti(Pchar.money) >= 500)
			{
				link.l1 = "拿去吧, 朱利安兄弟。 ";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "我现在没有足够的硬币... 我稍后再来。 ";
				link.l1.go = "exit";
			}
		break;
		
		case "potion3":
			npchar.quest.price = 200;
			npchar.quest.type = 3;
			dialog.text = "一瓶解毒剂? 200比索, 我的孩子。 ";
			if (sti(Pchar.money) >= 200)
			{
				link.l1 = "拿去吧, 朱利安兄弟。 ";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "我现在没有足够的硬币... 我稍后再来。 ";
				link.l1.go = "exit";
			}
		break;
		
		case "potion4":
			npchar.quest.price = 900;
			npchar.quest.type = 4;
			dialog.text = "一瓶合剂? 900比索, 我的孩子。 ";
			if (sti(Pchar.money) >= 900)
			{
				link.l1 = "拿去吧, 朱利安兄弟。 ";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "我现在没有足够的硬币... 我稍后再来。 ";
				link.l1.go = "exit";
			}
		break;
		
		case "potion_pay":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.price));
			iTemp = sti(npchar.quest.type);
			GiveItem2Character(pchar, "potion"+iTemp);
			PlaySound("interface\important_item.wav");
			dialog.text = "给。 拿着你的药。 愿上帝指引你! ";
			link.l1 = "谢谢你, 朱利安兄弟。 ";
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "potion"+iTemp+"_date");
		break;
		
		case "amulet":
			bool bOK = (!CheckAttribute(npchar, "amulet_date")) || (GetNpcQuestPastDayParam(npchar, "amulet_date") >= 3)
			if (bOk && GetSummonSkillFromName(pchar, SKILL_FORTUNE) > (10+hrand(110)))
			{
				npchar.quest.amulet = SelectLSCChurchAmulet();
				dialog.text = "是的, 我可以给你一些圣护身符, 它们能保护人们免受伤害和疾病。 任何护身符的价格都是一样的 --十个金杜布隆。 今天我可以给你"+XI_ConvertString(npchar.quest.amulet)+"。 ";
				if (PCharDublonsTotal() >= 10)
				{
					link.l1 = "是的, 我想买这个护身符。 这是你的金子。 ";
					link.l1.go = "amulet_pay";
					link.l2 = "我不需要这个护身符, 朱利安兄弟。 我会等到你有我需要的东西。 ";
					link.l2.go = "exit";
					SaveCurrentNpcQuestDateParam(npchar, "amulet_date");
				}
				else
				{
					link.l1 = "我现在没有足够的硬币... 我稍后再来。 ";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "不, 我的孩子, 不幸的是我没有别的了。 改天再来看看, 也许我会为你找到些什么。 ";
				link.l1 = "成交, 朱利安兄弟。 ";
				link.l1.go = "exit";
			}
		break;
		
		case "amulet_pay":
			RemoveDublonsFromPCharTotal(10);
			GiveItem2Character(pchar, npchar.quest.amulet);
			Log_Info("你收到了一个护身符");
			PlaySound("interface\important_item.wav");
			dialog.text = "谢谢你, 我的孩子。 你的钱会派上用场的。 拿着你的护身符, 愿上帝保佑你! ";
			link.l1 = "感谢你, 朱利安兄弟。 ";
			link.l1.go = "exit";
		break;
		
//-------------------------------------—— 问答块 ---------------------------------------------
		case "int_quests":
			dialog.text = "我在听。 ";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "你是怎么到这里来的, 朱利安兄弟? ";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "你的教区有多少人? ";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "这里谁卖东西? ";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "这个岛有被摧毁的风险吗? 也许是风暴? ";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "没有问题了。 对不起... ";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "和许多当地人一样, 我的孩子。 我的船在从哈瓦那到新西班牙的航行中被风暴击沉了。 感谢上帝, 我活了下来, 现在我在这里为祂服务, 帮助可怜的灵魂找到他们真正的道路。 ";
			link.l1 = "我明白了... ";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "比我希望的少。 大多数独角鲸帮更喜欢暴力而不是仁慈, 里瓦多斯人是贫穷和迷失的羔羊。 他们盲目地进行异教仪式, 把他们不朽的灵魂置于危险之中。 他们中有一个危险的巫师, 必须由神圣的宗教裁判所净化。 ";
			link.l1 = "我明白了... ";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "桑乔.卡彭特在弗莱龙号上拥有一家酒馆, 你可以在那里找到食物。 饮料和温暖的床。 阿克塞尔.约斯特在'埃斯梅拉达号'上出售各种各样的商品。 问问街上的人, 我的孩子, 他们很多人在外环找到了有趣的东西。 ";
			link.l1 = "谢谢你! ";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "一切都在我们主的手中, 我的孩子。 我们相信祂, 我们信任祂。 严重的麻烦总是远离我们的岛屿 --风暴经常在岛外发生, 但这里总是很安静。 ";
			link.l1 = "谢谢。 你让我放心了。 ";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <—— 问答块
		
//---------------------------------------—— 特殊反应 -----------------------------------------------
		// 发现玩家在箱子里
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("你在那里做什么, 嗯? 小偷! ", "看看那个! 我一陷入沉思, 你就决定检查我的箱子! ", "决定检查我的箱子? 你不会逃脱的! ");
			link.l1 = "该死的! ";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "什么? ! 决定检查我的箱子? 你不会逃脱的! ";
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
		
		// 发现露出的武器
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("听着, 你最好把武器收起来。 这让我紧张。 ", "你知道, 在这里携带武器是不被容忍的。 收起来。 ", "听着, 不要扮演中世纪骑士到处跑着拿剑。 收起来, 这不适合你... ");
			link.l1 = LinkRandPhrase("好的。 ", "好吧。 ", "如你所说... ");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "听着, 我是这个城市的公民, 我请求你收起你的 blade。 ", "听着, 我是这个城市的公民, 我请求你收起你的 blade。 ");
				link.l1 = LinkRandPhrase("好的。 ", "好吧。 ", "如你所说... ");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "小心点, 伙计, 带着武器跑。 我可能会紧张... ", "我不喜欢人们拿着武器在我面前走。 这让我害怕... ");
				link.l1 = RandPhraseSimple("知道了。 ", "我正在收起来。 ");
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

string SelectLSCChurchAmulet();
{
	string sAmulet;
	switch (hrand(3))
	{
		case 0: sAmulet = "amulet_2"; break;
		case 1: sAmulet = "amulet_3"; break;
		case 2: sAmulet = "amulet_6"; break;
		case 3: sAmulet = "amulet_7"; break;
	}
	return sAmulet;
}
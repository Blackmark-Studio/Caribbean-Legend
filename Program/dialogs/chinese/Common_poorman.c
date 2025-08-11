#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06

	switch(Dialog.CurrentNode)
	{
		case "First time":
			// --> 卡莱乌切
			if (CheckAttribute(pchar, "questTemp.Caleuche.SeekAmulet") && hrand(1) == 0 && sti(Pchar.money) >= 2000) 
			{
				dialog.text = "看, 先生, 你不想买一件有趣的小东西吗? 不贵, 只要几千比索... ";
				link.l1 = "嗯。 可能是偷来的这个'小东西', 现在想甩掉它? ";
				link.l1.go = "caleuche";
				break;
			}
			// < —卡莱乌切
			if (npchar.quest.meeting == "0")
			{
				dialog.text = LinkRandPhrase("你好。 我叫" + GetFullName(npchar) + "。 我想你见到我并不高兴, 但也许你至少会记住我的名字... ", 
					"问候你, " + GetAddress_Form(NPChar) + "。 我叫" + GetFullName(npchar) + "。 ", 
					"我叫" + GetFullName(npchar) + ", " + GetAddress_Form(NPChar) + "。 很高兴见到你。 ");
				link.l1 = RandPhraseSimple("问候。 ", "你好。 ");
				link.l1.go = "First time";
				// 加勒比习俗
				if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "spy_drink" && pchar.location == "portobello_town")
				{
					link.l2 = "嘿, 听着, 你想赚几千比索而不是这些可怜的施舍吗? ";
					link.l2.go = "trial";
				}
				// --> 贝齐.普莱斯的秘密
				if (CheckAttribute(pchar, "questTemp.TBP_BuyKulon3") && pchar.location == "Villemstad_town")
				{
					link.l2 = "那个带浮雕的吊坠... 你从哪里找到的? ";
					link.l2.go = "TBP_Kulon_1";
				}
				// < —贝齐.普莱斯的秘密
				npchar.quest.meeting = "1";
			}			
			else
			{
				dialog.text = NPCStringReactionRepeat("看我落魄到什么地步... ", 
					"靠施舍生活不容易... ", 
					"我愿意付出一切摆脱这种贫困! ",
					"又是你? ..", "block", 1, npchar, Dialog.CurrentNode);

				link.l1 = HeroStringReactionRepeat("我知道了。 好吧, 没什么大不了的。 ", 
					"当然。 嗯, 你知道, 历史上最伟大的人也是最贫穷的。 ",
					"那你应该开始做点什么, 而不是整天坐在这里。 ", 
					"啊哈。 已经烦我了? ", npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "pester", npchar, Dialog.CurrentNode);
				link.l2 = RandPhraseSimple("你需要什么? ", "你想要什么? ");
				link.l2.go = "Whants";
				// 加勒比习俗
				if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "spy_drink" && pchar.location == "portobello_town")
				{
					DelLandQuestMark(npchar);
					link.l2 = "嘿, 听着, 你想赚几千比索而不是这些可怜的施舍吗? ";
					link.l2.go = "trial";
				}
				// --> 贝齐.普莱斯的秘密
				if (CheckAttribute(pchar, "questTemp.TBP_BuyKulon3") && pchar.location == "Villemstad_town")
				{
					link.l2 = "那个带宝石的吊坠... 你从哪里找到的? ";
					link.l2.go = "TBP_Kulon_1";
				}
				// < —贝齐.普莱斯的秘密
				link.l3 = LinkRandPhrase("你能告诉我一些有趣的事吗? ", 
					"镇上有什么新鲜事? ", "哦, 我想听听最新的八卦... ");
				link.l3.go = "rumours_poor";
			}
			NextDiag.TempNode = "First time";
		break;
		case "pester":
			dialog.text = RandPhraseSimple("不, 为什么, 已经烦了? 如你所见, 我并不忙... ", 
				"只是让我很累。 虽然穷, 但我还是个人。 ");
			link.l1 = "呵, 我知道了... ";
			link.l1.go = "exit";
		break;
		//退出
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//施舍
		case "Whants":
			if (!CheckAttribute(npchar, "wants_date") || GetNpcQuestPastDayParam(npchar, "wants_date") >= 1 || bBettaTestMode)
			{
				dialog.text = PCharRepPhrase("嗯, " + GetAddress_Form(NPChar) + ", 人们说了很多关于你的坏话。 但我仍然相信人们 - 即使是像你这样的人。 请给我施舍买面包和水, 可怜可怜我。 ",
					"我求你了, " + GetAddress_Form(NPChar) + "! 请不要拒绝一个穷人, 给点施舍买顿饭... ");
				link.l1 = RandPhraseSimple("我什么也不会给你。 ", "没有钱你也能过。 ");
				link.l1.go = "exit";
				Link.l2 = "好吧, 你需要多少? ";
				Link.l2.go = "Whants_1";
			}
			else
			{
				dialog.text = PCharRepPhrase("从你这里? 什么都不要。 ", "我不需要任何东西, " + GetAddress_Form(NPChar) + ", 谢谢。 ");
				link.l1 = RandPhraseSimple("嗯, 好吧。 ", "显然, 你的生活还不算太糟, 伙计。 ");
				link.l1.go = "exit";
			}
		break;
		case "Whants_1":
			dialog.text = "我不会拒绝哪怕一个小铜板, " + GetAddress_Form(NPChar) + "。 就像你的钱包和仁慈能给的那么多... ";
			Link.l1.edit = 2;			
			link.l1 = "";
			link.l1.go = "Whants_2";
		break;
		case "Whants_2":
			SaveCurrentNpcQuestDateParam(npchar, "wants_date");
			int iTemp = sti(dialogEditStrings[2]);
			if (iTemp <= 0 || sti(pchar.money) < iTemp)
			{
				dialog.text = "嘲笑弱者和疲惫的人是一种罪过... ";
				link.l1 = "哈哈哈! 你以为我会给你钱吗, 你这个疯乞丐? ! ";
				link.l1.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", -2);
				break;
			}
			if (iTemp > 0 && iTemp <= 100)
			{
				dialog.text = "谢谢你的" + FindRussianMoneyString(iTemp) + ", " + GetAddress_Form(NPChar) + "。 现在我可以用这些钱买些面包了... ";
				link.l1 = "给你, 流浪汉 - 去补充点体力吧。 ";
				link.l1.go = "exit";
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(41, 1);
			}
			if (iTemp > 100 && iTemp <= 500)
			{
				dialog.text = "谢谢你, " + GetAddress_Form(NPChar) + "。 现在我可以用这些钱生活一周了! ";
				link.l1 = "很高兴能帮助你。 ";
				link.l1.go = "exit";
				OfficersReaction("good");
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(41, 1);
			}
			if (iTemp > 500 && iTemp <= 1000)
			{
				dialog.text = "谢谢你, " + GetAddress_Form(NPChar) + "。 我会告诉所有人你的善良! ";
				link.l1 = "这真的没必要。 ";
				link.l1.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", iTemp/2000.0+0.5);
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(41, 1);
			}
			if (iTemp > 1000 && iTemp <= 5000)
			{
				dialog.text = "谢谢你, 尊敬的" + GetSexPhrase("先生","女士") + " " + GetAddress_Form(NPChar) + "。 愿上帝保佑你... ";
				link.l1 = "是的, 他的保护当然不会有坏处! ";
				link.l1.go = "exit";
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), iTemp/10000.0+0.5);
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(41, 1);
			}
			if (iTemp > 5000 && iTemp <= 10000)
			{
				dialog.text = "谢谢你, " + GetSexPhrase("最尊敬的先生","最尊敬的女士") + " " + GetAddress_Form(NPChar) + "。 祝你一切顺利! ";
				link.l1 = "谢谢你, 伙计。 ";
				link.l1.go = "exit";
				AddCharacterExpToSkill(pchar, "Leadership", iTemp/5000.0);
				AddCharacterExpToSkill(pchar, "Fortune", iTemp/5000.0);
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(41, 1);
			}
                 if (iTemp > 10000 && iTemp < 25000)
			{
				dialog.text = "听着, " + GetAddress_Form(NPChar) + ", 你疯了吗? 你给我" + FindRussianMoneyString(iTemp) + "! 我不能接受这么多钱, 肯定有什么陷阱... 离我远点! ";
				link.l1 = "好吧, 如你所愿... ";
				link.l1.go = "exit";
			}
                 if (iTemp == 25000)
			{
				dialog.text = "两万五千比索收下了... 这些钱足够我和莱拉用一整年了! ";
				link.l1 = "先过好这一年吧... ";
				link.l1.go = "exit";
			}
			if (iTemp > 25000)
			{
				dialog.text = "听着, " + GetAddress_Form(NPChar) + ", 你疯了吗? 你给我" + FindRussianMoneyString(iTemp) + "! 我不能接受这么多钱, 肯定有什么陷阱... 离我远点! ";
				link.l1 = "好吧, 如你所愿... ";
				link.l1.go = "exit";
			}
		break;
		
		case "trial":
			DelLandQuestMark(npchar);
			dialog.text = "一个愚蠢的问题, 先生! 我当然愿意! 但是... 我需要做什么? 你当然不会因为我美丽的笑容就给我钱。 ";
			link.l1 = "当然不是。 现在听着。 我代表总督本人行事。 大人怀疑造船厂有人故意破坏他的大帆船'阿拉坎塔拉'的下水。 最近抓获一名法国间谍后, 他的怀疑更加强烈了... ";
			link.l1.go = "trial_1";
		break;
		
		case "trial_1":
			dialog.text = "";
			link.l1 = "大人已经听过造船匠的辩解, 但他不确定是否说了实话。 我们需要找出是谁在破坏工作以及为什么。 去码头, 四处看看, 问问工人们, 为什么'阿拉坎塔拉'还没准备好航行... ";
			link.l1.go = "trial_2";
		break;
		
		case "trial_2":
			dialog.text = "";
			link.l1 = "没人会怀疑你, 你甚至可能弄到一堆烟草。 至于我, 没人会告诉我任何事。 每个人都会知道我为谁工作。 如果你能学到任何有价值的东西, 你将获得三千比索。 足够让你放弃'工作'至少一个月。 ";
			link.l1.go = "trial_3";
		break;
		
		case "trial_3":
			dialog.text = "三千比索? 但是, 尊敬的先生... ";
			link.l1 = "你在和我讨价还价吗? 哦, 如果你发现是谁在拖延, 你还会再得到两千比索。 成交? ";
			link.l1.go = "trial_4";
		break;
		
		case "trial_4":
			dialog.text = "好吧, 先生。 应该不会太难 - 我的很多老朋友现在都在码头工作。 嘿, 我很久以前也是水手... 大概十年前... ";
			link.l1 = "你以后再给我讲你的人生故事。 晚上十一点后在码头见我。 现在走吧。 ";
			link.l1.go = "trial_5";
		break;
		
		case "trial_5":
			chrDisableReloadToLocation = true;//关闭地点
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload5_back", "none", "", "", "OpenTheDoors", 10.0);
			pchar.questTemp.Trial = "spy_poorman";
			pchar.quest.trial_spy_poorman.win_condition.l1 = "Timer";
			pchar.quest.trial_spy_poorman.win_condition.l1.date.hour  = 22.00;
			pchar.quest.trial_spy_poorman.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.trial_spy_poorman.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.trial_spy_poorman.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.trial_spy_poorman.function = "Trial_SetPoormanInPort";
			pchar.quest.Trial_ReturnPoormanNorm.win_condition.l1 = "Timer";
			pchar.quest.Trial_ReturnPoormanNorm.win_condition.l1.date.hour  = 6.00;
			pchar.quest.Trial_ReturnPoormanNorm.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Trial_ReturnPoormanNorm.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Trial_ReturnPoormanNorm.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Trial_ReturnPoormanNorm.win_condition = "Trial_ReturnPoormanNorm";
			//SetTimerCondition("Trial_ReturnPoormanNorm", 0, 0, 1, false);
			AddQuestRecord("Trial", "15");
		break;
		
		case "trial_6":
			dialog.text = "晚上好, 先生... ";
			link.l1 = "那么? 你发现了什么吗? ";
			link.l1.go = "trial_7";
			DelLandQuestMark(npchar);
		break;
		
		case "trial_7":
			dialog.text = "我发现了, 先生, 我发现了。 不确定这和你告诉我的是否一致... 你带钱了吗? 五千比索。 ";
			if (sti(pchar.money) >= 5000)
			{
				link.l1 = "别担心。 这是你的钱。 现在说出来。 ";
				link.l1.go = "trial_8";
			}
			else
			{
				link.l1 = "先告诉我信息, 然后给钱。 来吧, 别浪费我的时间! ";
				link.l1.go = "trial_fail";
			}
		break;
		
		case "trial_fail":
			dialog.text = "你想骗我, 先生! 如果你不打算付钱 - 自己去问别人吧。 甚至别想拔剑, 否则我就叫卫兵! ";
			link.l1 = "... ";
			link.l1.go = "trial_fail_1";
		break;
		
		case "trial_fail_1":
			chrDisableReloadToLocation = true;//关闭地点
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 10.0);
			pchar.questTemp.Trial = "spy_fail";
			AddQuestRecord("Trial", "16");
			sld = characterFromId("Florian");
			sld.DeckDialogNode = "florian_failspy_5";
		break;
		
		case "trial_8":
			AddMoneyToCharacter(pchar, -5000);
			dialog.text = "事情是这样的:'阿拉坎塔拉'早就准备好航行了, 但有意没有装货, 这是总督本人的命令。 至少别人是这么告诉我的。 木匠们现在在做各种无关紧要的小工作, 这不影响船只出发。 \n大家都在等卡塔赫纳的一艘三桅帆船到来。 问题是在船长看来,'阿拉坎塔拉'的火药储备不足。 所以船一直在这里等着, 直到'普埃布拉'号带来火药。 \n但所有人都认为这一切等待只是浪费时间, 所以如果'普埃布拉'号三天内不到,'阿拉坎塔拉'号将不带火药起锚... ";
			link.l1 = "是这样吗? 谁告诉你的? 名字? ";
			link.l1.go = "trial_9";
		break;
		
		case "trial_9":
			dialog.text = "'阿拉坎塔拉'号的一个水手 - 费利佩.达宾霍... 但这其实根本不是秘密, 是总督大人自己下的命令... ";
			link.l1 = "我明白了。 这正是我所期望的。 法国间谍在镇上, 但这些白痴像妓女一样喋喋不休, 难以置信! 任何先来的人都能知道大人的计划。 哦, 那个费利佩.达宾霍现在有大麻烦了! 还有'阿拉坎塔拉'号的水手长也是! 他的船员不懂纪律, 这是他的错! ";
			link.l1.go = "trial_10";
			QuestPointerToLoc("PortoBello_Town", "reload", "gate_back");
			QuestPointerToLoc("PortoBello_ExitTown", "reload", "reload1_back");
			QuestPointerToLoc("PortoBello_Jungle_01", "reload", "reload2_back");
			QuestPointerToLoc("PortoBello_Jungle_02", "reload", "reload3_back");
			QuestPointerToLoc("shore47", "reload", "boat");
		break;
		
		case "trial_10":
			dialog.text = "哦... 所以你一开始就知道了? 但是为什么... 这不是我的错! 你让我这么做的! ";
			link.l1 = "这不是你的错, 你不应该担心, 没人会惩罚你。 现在我们知道'阿拉坎塔拉'号的船员可以向敌人泄露任何信息 - 即使是应该保密的信息。 好了, 你现在可以走了。 谢谢你的帮助。 去花你的钱吧。 ";
			link.l1.go = "trial_11";
			// belamour传奇版 -->
			link.l2 = "再见。 (杀了他)";
			link.l2.go = "trial_11a";
		break;
		
		case "trial_11a":
			DialogExit();
			AddMoneyToCharacter(npchar, 5000);
			npchar.SaveItemsForDead  = true; 
			LAi_SetActorType(pchar);
			// 如果没有佩戴手枪或步枪, 就发放制式武器
			if(!CheckAttribute(pchar,"equip."+GUN_ITEM_TYPE))
			{
				GiveItem2Character(pchar, "pistol1");
				EquipCharacterbyItem(pchar, "pistol1");
			}
			LAi_ActorAnimation(pchar, "Shot", "RIP_Bomzh", 1.0); 
		break;
		
		case "trial_11":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddCharacterExpToSkill(pchar, "Sneak", 50);
			// < —传奇版
			chrDisableReloadToLocation = true;//关闭地点
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 10.0);
			pchar.questTemp.Trial = "spy_win";
			AddQuestRecord("Trial", "17");
			sld = characterFromId("Florian");
			sld.DeckDialogNode = "florian_12";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		// --> 卡莱乌切
		case "Caleuche":
			dialog.text = "对不起, 好先生... 我在和一个陌生人玩骰子时赢了它, 我以为这是一个有魔力的治疗护身符, 但我错了... 它不能治病, 市场商人也对它不感兴趣。 而你来了 - 一个水手, 船长, 一个有学问的人。 看看它, 你可能会觉得有用。 \n对你来说这几千比索是小数目, 但对我来说是一个月的面包和一口朗姆酒。 看, 先生... ";
			link.l1 = "好吧, 给我看看... ";
			link.l1.go = "Caleuche_1";
		break;
		
		case "Caleuche_1":
			Log_Info("你得到了一个奇怪的护身符");
			PlaySound("interface\important_item.wav");
			dialog.text = "给你... ";
			link.l1 = "一般般... 有趣的东西, 我承认。 我确定这是从印第安人定居点偷来的。 好吧, 我买了。 这是你的钱。 ";
			link.l1.go = "Caleuche_2";
		break;
		
		case "Caleuche_2":
			AddMoneyToCharacter(pchar, -2000);
			dialog.text = "谢谢你, 先生! 我希望这个东西能给你带来好运! 愿上帝保佑你! ";
			link.l1 = "祝你好运, 伙计。 不要一下子把所有钱都花在酒馆里。 ";
			link.l1.go = "Caleuche_3";
		break;
		
		case "Caleuche_3":
			DialogExit();
			GiveItem2Character(pchar, "kaleuche_amulet1"); 
		break;
		// < —卡莱乌切
		
		// --> 贝齐.普莱斯的秘密
		case "TBP_Kulon_1":
			dialog.text = "呃, " + GetAddress_Form(NPChar) + ", 你为什么关心一个旧饰品? ";
			link.l1 = "当我用靴子踢你愚蠢的头时, 你会立刻明白我为什么关心。 ";
			link.l1.go = "TBP_Kulon_TO";
			if (CheckAttribute(pchar, "questTemp.TBP_BuyKulon2"))
			{
				link.l2 = "这个吊坠属于贝齐.普莱斯。 那么你从哪里找到它的? ";
				link.l2.go = "TBP_Kulon_leadership";
			}
			DeleteAttribute(pchar, "questTemp.TBP_BuyKulon3");
		break;

		case "TBP_Kulon_TO":
			dialog.text = "它躺在有灯笼的房子附近, " + GetAddress_Form(NPChar) + "。 被一个粗人的靴子踩在泥里。 但那房子已经很久没人住了, 所以我认为它是无主的... ";
			link.l1 = "嗯... ";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "FencingH", 100);
			DeleteAttribute(pchar, "questTemp.TBP_BuyKulon2");
		break;

		case "TBP_Kulon_leadership":
			dialog.text = "它躺在有灯笼的房子附近, " + GetAddress_Form(NPChar) + "。 被一个粗人的靴子踩在泥里。 但那房子已经很久没人住了, 所以我认为它是无主的... ";
			link.l1 = "嗯... ";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			DeleteAttribute(pchar, "questTemp.TBP_BuyKulon2");
		break;
		// <-- 贝齐.普莱斯的秘密
	}
}
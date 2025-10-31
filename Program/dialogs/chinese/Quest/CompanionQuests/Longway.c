void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag, arTmp;
	int i, n;
	string sTemp, sStr;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "你需要什么? ";
			link.l1 = "没什么。 ";
			link.l1.go = "exit";
		break;
		
		// 任务'导航星'
		// 阶段0, 序幕
		case "PZ_Alonso_1":
			dialog.text = "很抱歉打扰您的住所, 船长先生, 但这非常重要。 ";
			link.l1 = "希望如此, 阿隆索。 如果你们每个人都像这样闯入这里, 我们就有麻烦了。 那么, 发生了什么? ";
			link.l1.go = "PZ_Alonso_2";
		break;
		
		case "PZ_Alonso_2":
			dialog.text = "我们发现您的储物柜被翻找过。 ";
			link.l1 = "什么? ! 等等... 你是怎么发现的? 你们都在我的船舱里做什么? ";
			link.l1.go = "PZ_Alonso_3";
		break;
		
		case "PZ_Alonso_3":
			dialog.text = "当您外出时 —无论是在镇上还是在铺位上休息, 我们偶尔会打扫您的住所。 您从未注意到? 还是忘了? ";
			link.l1 = "哦, 对了。 好吧, 你现在可以走了。 ";
			link.l1.go = "PZ_OsmatrivaemKautu";
		break;
		
		case "PZ_Tichingitu_1":
			dialog.text = "查尔斯船长, 看! 有人在翻您的大抽屉。 ";
			link.l1 = "什么? 你什么时候注意到的? 知道是谁吗? ";
			link.l1.go = "PZ_Tichingitu_2";
		break;
		
		case "PZ_Tichingitu_2":
			dialog.text = "不久前, 我来看您的时候。 神灵没有告诉我可能是谁。 ";
			link.l1 = "说得好, 蒂钦吉图。 现在请原谅, 我需要检查是否有东西丢失。 ";
			link.l1.go = "PZ_OsmatrivaemKautu";
		break;
		
		case "PZ_Duran_1":
			dialog.text = "嘿, 船长, 你在看什么? 有人翻了你的东西。 连我都注意到了。 ";
			link.l1 = "不是你吗? 毕竟, 我给你的薪水不如弗朗索瓦慷慨。 ";
			link.l1.go = "PZ_Duran_2";
		break;
		
		case "PZ_Duran_2":
			dialog.text = "嘿, 如果我是小偷, 我不会告诉你, 对吧? 我会拿走贵重物品并清理现场。 这混乱不是我的风格。 ";
			link.l1 = "我不想承认, 但你是对的。 好吧, 克劳德, 把你的讽刺留到以后。 我得检查小偷拿了什么。 ";
			link.l1.go = "PZ_OsmatrivaemKautu";
		break;
		
		case "PZ_Folke_1":
			dialog.text = "船长, 我今天注意到有人翻了您的储物柜。 您没注意到吗? ";
			link.l1 = "什么? 我不是一直在检查储物柜, 福尔克, 而且我也不总是在船舱里。 老实告诉我 —是你吗? 上次我们在岸上时, 你又搞砸了并借了更多的银行贷款? ";
			link.l1.go = "PZ_Folke_2";
		break;
		
		case "PZ_Folke_2":
			dialog.text = "完全不是, 船长。 我口袋里和储物柜里没有您的任何东西。 而且永远不会有。 ";
			link.l1 = "我当然希望不是。 你可以走了 —我会检查丢了什么。 ";
			link.l1.go = "PZ_OsmatrivaemKautu";
		break;
		
		case "PZ_OsmatrivaemKautu":
			DialogExit();
			AddDialogExitQuestFunction("PZ_OsmatrivaemSunduk_0");
		break;
		
		case "PZ_LigaInJungle_1":
			dialog.text = "查尔斯.德莫尔, 对吗? ";
			link.l1 = "从你脸上的表情看, 我觉得你已经知道答案了。 那么, 你想要什么? ";
			link.l1.go = "PZ_LigaInJungle_2";
		break;
		
		case "PZ_LigaInJungle_2":
			dialog.text = "你的脑袋。 ";
			link.l1 = "真有趣! 我得说, 我喜欢这次对话的开头。 但在我们继续之前, 你至少能告诉我我得罪了谁吗? 也许我们可以协商。 ";
			link.l1.go = "PZ_LigaInJungle_3";
		break;
		
		case "PZ_LigaInJungle_3":
			dialog.text = "我们不是 amateurs, 德莫尔先生。 即使我们告诉你, 也帮不了你 —我们的雇主已经离开群岛了。 你无法伤害他们或道歉。 我们已经拿到报酬, 现在是时候履行我们的约定了。 ";
			link.l1 = "如果你已经拿到报酬, 为什么还要流血? ";
			link.l1.go = "PZ_LigaInJungle_4";
		break;
		
		case "PZ_LigaInJungle_4":
			dialog.text = "我们不是 amateurs。 我们重视自己的声誉。 ";
			link.l1 = "恐怕这次你无法维护声誉了。 ";
			link.l1.go = "PZ_LigaInJungle_5";
		break;
		
		case "PZ_LigaInJungle_5":
			dialog.text = "我们走着瞧。 结束后搜查他的尸体! 烧掉你找到的任何东西! ";
			link.l1 = "烧掉什么? ..";
			link.l1.go = "PZ_LigaInJungle_6";
		break;
		
		case "PZ_LigaInJungle_6":
			DialogExit();
			
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetFightMode(pchar, true);
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("LigaInJungle_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_LigaInJunglePosleBitvy");
			
			if (CharacterIsHere("Longway"))
			{
				sld = characterFromId("Longway");
				LAi_SetCheckMinHP(sld, 1, true, "");
			}
		break;
		
		case "PZ_Longway_1":
			dialog.text = "那个蒙面人说的话... 难道是... ? ";
			link.l1 = "怎么了, 朗威? 这不是第一次赏金猎人追我了, 但你似乎异常担心。 ";
			link.l1.go = "PZ_Longway_2";
		break;
		
		case "PZ_Longway_2":
			dialog.text = "朗威认为他知道是谁派这些人来追您的, 船长阁下。 ";
			link.l1 = "有什么我该知道的吗? ";
			link.l1.go = "PZ_Longway_3";
		break;
		
		case "PZ_Longway_3":
			dialog.text = "这是罗登堡大人的手段 —除掉那些帮助过他但知道太多的人。 ";
			link.l1 = "真的... 那个蒙面人确实说他的雇主最近离开了群岛。 这正是卢卡斯的计划! 你认为我们应该期待更多袭击吗? ";
			link.l1.go = "PZ_Longway_4";
		break;
		
		case "PZ_Longway_4":
			dialog.text = "做好万全准备是明智的, 船长阁下。 ";
			link.l1 = "明智的话。 我们会的。 但卢卡斯在找什么? 他认为我有什么? 朗威, 你有什么想法吗? ";
			link.l1.go = "PZ_Longway_5";
		break;
		
		case "PZ_Longway_5":
			dialog.text = "嗯嗯, 不, 朗威不知道那可能是什么。 ";
			link.l1 = "真遗憾。 但好吧, 我们离开这里。 ";
			link.l1.go = "PZ_Longway_6";
		break;
		
		case "PZ_Longway_6":
			DialogExit();
			
			ReturnOfficer_Longway();
			
			chrDisableReloadToLocation = false;
			pchar.questTemp.PZ_RazgovorGerrits = true;
			pchar.questTemp.PZ_PodozrenieLucas = true;
		break;
		
		// 阶段1, 忠于誓言
		case "PZ_Longway_11":
			dialog.text = "船长阁下, 朗威希望与您交谈。 这非常重要。 ";
			if (CheckAttribute(pchar, "questTemp.PZ_PodozrenieLucas"))
			{
				link.l1 = "怎么了, 朗威? 你是担心卢卡斯的告别方式, 还是发现了新情况? ";
				link.l1.go = "PZ_Longway_12";
				AddCharacterExpToSkill(pchar, "Sneak", 100);
			}
			else
			{
				link.l1 = "当然! 你在想什么? ";
				link.l1.go = "PZ_Longway_13";
			}
		break;
		
		case "PZ_Longway_12":
			dialog.text = "不幸的是, 没有。 ";
			link.l1 = "那是什么, 朗威? ";
			link.l1.go = "PZ_Longway_13";
		break;
		
		case "PZ_Longway_13":
			dialog.text = "朗威不能说。 但是... 他希望请求允许离开。 ";
			link.l1 = "离开? 比如, 永远? 为什么, 朗威? 作为你的船长, 我有权知道原因。 ";
			link.l1.go = "PZ_Longway_14";
		break;
		
		case "PZ_Longway_14":
			dialog.text = "没错, 船长阁下。 但朗威既不是劳工也不是仆人。 他是自愿来帮忙的, 也可以以同样的方式离开。 这不会是永远的 —有一件重要的事情要处理。 朗威希望事情完成后回来。 ";
			link.l1 = "这是什么事? 告诉我 —如果不是作为你的船长, 那就作为与你经历过很多的人。 ";
			link.l1.go = "PZ_Longway_15";
		break;
		
		case "PZ_Longway_15":
			dialog.text = "朗威只能说他发过誓 —很久以前。 履行誓言的时候到了。 否则... 朗威的生命就没有意义了。 ";
			link.l1 = "你说得对, 朗威 —你不是囚犯, 我也不是狱卒。 你可以自由离开。 祝你好运。 ";
			link.l1.go = "PZ_Longway_Otpustit_1";
			link.l2 = "你可以走, 但至少告诉我你要去哪里。 我可以帮忙, 不会问太多问题。 ";
			link.l2.go = "PZ_Longway_Pomoch_1";
			link.l3 = "我也有一项重要任务 —拯救我的兄弟。 为此, 我需要每个人, 包括你, 朗威。 没有你我们做不到。 ";
			link.l3.go = "PZ_Longway_NeOtpuskaem_1";
		break;
		
		case "PZ_Longway_NeOtpuskaem_1":
			dialog.text = "不要试图利用我的同情或责任感。 我完全理解。 你发过誓吗, 船长阁下? ";
			link.l1 = "我当然发过。 所以如实告诉我一切, 我和我的人肯定会帮助你。 ";
			link.l1.go = "PZ_Longway_NeOtpuskaem_2";
		break;
		
		case "PZ_Longway_NeOtpuskaem_2":
			dialog.text = "朗威不能。 只是... 不能。 这是一个巨大的秘密, 甚至不是我该分享的。 ";
			link.l1 = "太遗憾了。 我以为我们之间有信任。 你不能离开船 —我现在有所有军官支持我。 ";
			link.l1.go = "PZ_Longway_NeOtpuskaem_3";
			link.l2 = "你说得对, 朗威 —你不是囚犯, 我也不是狱卒。 你可以自由离开。 祝你好运。 ";
			link.l2.go = "PZ_Longway_Otpustit_1";
		break;
		
		case "PZ_Longway_NeOtpuskaem_3":
			dialog.text = "你不能这么做! ";
			link.l1 = "不幸的是, 我可以, 朗威。 现在回到你的岗位。 ";
			link.l1.go = "PZ_Longway_NeOtpuskaem_4";
		break;
		
		case "PZ_Longway_NeOtpuskaem_4":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			npchar.Dialog.CurrentNode = "Longway_officer";
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			PChar.quest.PZ_LongwayUhoditOtNasNavsegda.win_condition.l1 = "MapEnter";
			PChar.quest.PZ_LongwayUhoditOtNasNavsegda.win_condition = "PZ_LongwayUhoditOtNasNavsegda";
		break;
		
		case "PZ_Longway_Otpustit_1":
			dialog.text = "我没想到你会这么轻易让我走。 谢谢你, 船长阁下。 ";
			link.l1 = "啊, 没什么。 但告诉我 —你的事情完成后, 我在哪里可以找到你? ";
			link.l1.go = "PZ_Longway_GdeIskat_1";
		break;
		
		case "PZ_Longway_Pomoch_1":
			dialog.text = "朗威真的不能说, 不管他多么希望能说。 但他感谢船长阁下愿意提供帮助。 ";
			link.l1 = "那就这样吧。 你履行誓言后, 我该去哪里找你? ";
			link.l1.go = "PZ_Longway_GdeIskat_1";
			pchar.questTemp.PZ_LongwayGood = true;
		break;
		
		case "PZ_Longway_GdeIskat_1":
			dialog.text = "我预计一个月内完成我的事情。 之后, 朗威会在巴斯特尔的酒馆再等你一周。 ";
			link.l1 = "好吧, 不管你说什么, 我的朋友。 这不是告别。 巴斯特尔见。 ";
			link.l1.go = "PZ_Longway_GdeIskat_2";
		break;
		
		case "PZ_Longway_GdeIskat_2":
			DialogExit();
			
			RemovePassenger(pchar, npchar);
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			LAi_SetImmortal(npchar, true);
			npchar.location = "None";
			
			SetQuestHeader("PZ");
			AddQuestRecord("PZ", "1");
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			SetTimerCondition("PZ_IshemLongway", 0, 0, 30, false);
		break;
		
		case "PZ_SharliePlennik_BadFinal_1":
			dialog.text = "好吧, 你好, 船长。 ";
			link.l1 = "我不喜欢你的冷笑, 先生。 ";
			link.l1.go = "PZ_SharliePlennik_BadFinal_2";
		break;
		
		case "PZ_SharliePlennik_BadFinal_2":
			dialog.text = "我很遗憾。 我来告诉你, 你终于自由了。 但如果你想在这个豪华船舱里多待一会儿, 欢迎之至。 ";
			link.l1 = "完全不想。 那么, 朗威被找到了? 他在哪里? 在某个牢房里? ";
			link.l1.go = "PZ_SharliePlennik_BadFinal_3";
		break;
		
		case "PZ_SharliePlennik_BadFinal_3":
			dialog.text = "更像是在另一个世界 —他不跟我们任何人说话, 直接投入了战斗。 ";
			link.l1 = "该死! 你本可以抓住他的。 ";
			link.l1.go = "PZ_SharliePlennik_BadFinal_4";
		break;
		
		case "PZ_SharliePlennik_BadFinal_4":
			dialog.text = "有些人杀了比抓住容易得多, 你不知道吗? 你应该高兴我们没有对你怀恨在心 —你的中国人又造成了一场屠杀, 我们需要更多配备神射手的部队来对付他。 ";
			link.l1 = "是的, 确实。 谢谢你。 ";
			link.l1.go = "PZ_SharliePlennik_BadFinal_5";
		break;
		
		case "PZ_SharliePlennik_BadFinal_5":
			dialog.text = "说到这个, 既然他是你的朋友, 我们在他身上发现了一些文件。 我们不明白是什么 —你可能更清楚。 没被血覆盖的部分写着一些胡言乱语。 ";
			link.l1 = "那是... 该死。 谢谢你把它们还给我。 再见, 军官。 ";
			link.l1.go = "PZ_SharliePlennik_BadFinal_6";
		break;
		
		case "PZ_SharliePlennik_BadFinal_6":
			DialogExit();
			
			LAi_ActorGoToLocator(npchar, "goto", "goto22", "", -1);
			DoQuestCheckDelay("PZ_SharliePlennik_BadFinal_2", 3.0);
		break;
		
		case "PZ_BasTerStop":
			dialog.text = "跟我们来, 指挥官想和你谈谈。 ";
			link.l1 = "我想这和我寻找那个中国人有关? ";
			link.l1.go = "PZ_BasTerStop_2";
		break;
		
		case "PZ_BasTerStop_2":
			dialog.text = "你自己会看到的, 先生。 ";
			link.l1 = "我被指控什么了吗? ";
			link.l1.go = "PZ_BasTerStop_3";
		break;
		
		case "PZ_BasTerStop_3":
			dialog.text = "完全没有。 没有人想逮捕或拘留你。 目前是这样。 我说指挥官想和你谈谈, 就是这个意思。 ";
			link.l1 = "哦, 好吧... ";
			link.l1.go = "PZ_BasTerStop_4";
		break;
		
		case "PZ_BasTerStop_4":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation("BasTer_town")], false);
			DoQuestReloadToLocation("BasTer_prison", "goto", "goto17", "PZ_BasTer_TurmaPriveli");
		break;
		
		case "PZ_BasTer_OtryadPeshera_1":
			dialog.text = "有什么想法吗? 这个黄皮肤的人极其危险。 我们不是第一支被派来的小队。 命令就是命令, 但我不想愚蠢地在没有可靠计划的情况下进去送死。 ";
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				link.l1 = "他一个人在里面, 我和你们一起。 我来对付他 —你们专注于掩护我。 我们会成功的。 ";
				link.l1.go = "PZ_BasTer_OtryadPeshera_2";
				if (pchar.location.from_sea != "BasTer_Town")
				{
					link.l2 = "我有一个。 你们都要死 —就在这里。 ";
					link.l2.go = "PZ_BasTer_OtryadPeshera_Kill_1";
				}
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				link.l1 = "别担心, 我们只是去和他谈谈。 ";
				link.l1.go = "PZ_BasTer_OtryadPeshera_2";
				if (pchar.location.from_sea != "BasTer_Town")
				{
					link.l2 = "抱歉, 但你们今天都得死。 而且不会是死在一个中国人手里。 ";
					link.l2.go = "PZ_BasTer_OtryadPeshera_Kill_1";
				}
			}
		break;
		
		case "PZ_BasTer_OtryadPeshera_Kill_1":
			pchar.questTemp.PZ_Podelnik = true;
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "所以你不是赏金猎人... 但即使你是, 你也是那个该死的中国人的朋友! ";
				link.l1 = "没错。 我反正得摆脱你们 —没必要拖延不可避免的事。 ";
				link.l1.go = "PZ_BasTer_OtryadPeshera_Kill_2";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "你是什么意思? ! 你答应过要帮忙的! ";
				link.l1 = "我想你无论如何都不会给我们一条和平的出路。 这不是针对个人。 ";
				link.l1.go = "PZ_BasTer_OtryadPeshera_Kill_2";
			}
		break;
		
		case "PZ_BasTer_OtryadPeshera_Kill_2":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			chrDisableReloadToLocation = true;
			
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			sld = CharacterFromID("PZ_BasTer_OtryadPesheraOff");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_BasTer_OtryadPeshera_Kill_3");
		break;
		
		case "PZ_BasTer_OtryadPeshera_2":
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "我愿意相信。 ";
				link.l1 = "我面对过更糟的。 一个中国人不会是我们的末日。 走吧, 伙计们! ";
				link.l1.go = "PZ_BasTer_OtryadPeshera_3";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "如果谈话不如预期怎么办? ";
				link.l1 = "我不希望那样, 但如果是那样, 我将不得不自卫。 我们走吧。 ";
				link.l1.go = "PZ_BasTer_OtryadPeshera_3";
			}
		break;
		
		case "PZ_BasTer_OtryadPeshera_3":
			DialogExit();
			
			DoQuestReloadToLocation("Guadeloupe_CaveEntrance", "reload", "reload2", "PZ_IshemLongway_OtryadUPeshery");
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway":
			dialog.text = "船长阁下? ! 朗威不敢相信您和他们在一起! ";
			link.l1 = "不, 朗威, 我只是来谈谈! 不是你想的那样! ";
			link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_2";
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_2":
			dialog.text = "那你应该一个人来。 你试图降低我的警惕, 以便在这些士兵的帮助下攻击我! ";
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayGood"))
			{
				link.l1 = "如果可以, 我会的。 我是他们还没有攻击你的唯一原因。 冷静下来, 我们谈谈, 好吗? ";
				link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_3";
			}
			else
			{
				link.l1 = "别废话了! 如果我想, 我早就杀了你了。 放下武器, 我们谈谈。 这是你船长的命令。 ";
				link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_Bad_1";
			}
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_3":
			dialog.text = "是。 朗威信任您, 船长阁下。 ";
			link.l1 = "看, 这样更好。 现在, 告诉我... ";
			link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_4";
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_4":
			StartInstantDialog("PZ_BasTer_OtryadPesheraOff", "PZ_BasTer_SOtryadom_DialogLongway_5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_5":
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "先生, 发生了什么事? 这是什么... 感人的重逢? 你应该帮助我们消灭那个中国野蛮人, 不是吗? ";
				link.l1 = "我是在帮。 我要带他走, 所有的杀戮都会停止。 你会告诉指挥官我们一起杀了他。 成交? ";
				link.l1.go = "PZ_BasTer_SOtryadomOhotnik_1";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "干得好, 船长! 他放下了武器。 很高兴有你和我们在一起。 现在把他带到指挥官那里。 ";
				link.l1 = "我为什么要那样做? 我为朗威的行为支付了黄金罚款 —一笔慷慨的罚款。 你们的军官是证人 —他们会证实的。 指挥官授权我带我的人回船。 ";
				link.l1.go = "PZ_BasTer_SOtryadomDrug_1";
			}
		break;
		
		case "PZ_BasTer_SOtryadomDrug_1":
			dialog.text = "指挥官可能受够了这些血黄金, 但我没有。 他在那个血腥的洞穴里杀死的一些人是我的朋友。 此外, 我怀疑他反正不会在意我们是否杀了那个中国人。 ";
			link.l1 = "你确定想知道吗? 关于你被杀的朋友... 听说过那群厚颜无耻的强盗吗? 一定是他们。 ";
			link.l1.go = "PZ_BasTer_SOtryadomDrug_2";
		break;
		
		case "PZ_BasTer_SOtryadomDrug_2":
			StartInstantDialog("Longway", "PZ_BasTer_SOtryadomDrug_3", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_BasTer_SOtryadomDrug_3":
			dialog.text = "";
			link.l1 = "朗威, 你没有像他们声称的那样杀死那么多士兵, 对吧? ";
			link.l1.go = "PZ_BasTer_SOtryadomDrug_4";
		break;
		
		case "PZ_BasTer_SOtryadomDrug_4":
			dialog.text = "没错, 船长阁下。 朗威看到了那伙人。 他们躲在洞穴深处, 所以没有注意到他。 朗威听到了强盗和士兵之间的谈话。 咒骂和战斗的声音。 ";
			link.l1 = "";
			link.l1.go = "PZ_BasTer_SOtryadomDrug_5";
		break;
		
		case "PZ_BasTer_SOtryadomDrug_5":
			StartInstantDialog("PZ_BasTer_OtryadPesheraOff", "PZ_BasTer_SOtryadomDrug_6", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_BasTer_SOtryadomDrug_6":
			dialog.text = "";
			link.l1 = "看? 一切都吻合。 朗威可能脾气暴躁, 但他是个诚实的人。 我们要走了。 如果你们碰我们, 就会玷污你们的制服。 再见, 先生们。 ";
			link.l1.go = "PZ_BasTer_SOtryadomDrug_7";
		break;
		
		case "PZ_BasTer_SOtryadomDrug_7":
			DialogExit();
			
			AddQuestRecord("PZ", "13");
			LAi_LocationFightDisable(&Locations[FindLocation("Guadeloupe_CaveEntrance")], false);
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
			LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", false);
			LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", false);
			//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", false);
			
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "PZ_BasTer_OtryadRazveli", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				LAi_CharacterDisableDialog(sld);
			}
			sld = CharacterFromID("PZ_BasTer_OtryadPesheraOff");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "PZ_BasTer_OtryadRazveli", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_CharacterDisableDialog(sld);
			
			sld = CharacterFromID("Longway");
			AddPassenger(pchar, sld, false);
			LAi_SetImmortal(sld, false);
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			sld.Dialog.CurrentNode = "Longway_officer";
			
			DeleteQuestCondition("PZ_LongwayNelzyaUmeret");
			
			//第二阶段继续
			PChar.quest.PZ_LongwayRazgovorVKaute.win_condition.l1 = "EnterToSea"
			PChar.quest.PZ_LongwayRazgovorVKaute.win_condition = "PZ_LongwayRazgovorVKaute";
		break;
		
		case "PZ_BasTer_SOtryadomOhotnik_1":
			dialog.text = "没门, 先生! 他杀了我们很多人, 现在你说他会逃脱惩罚? ! 要么你帮我们杀了那个混蛋, 要么至少别碍事! ";
			link.l1 = "恐怕我必须干预。 真的很抱歉。 ";
			link.l1.go = "PZ_BasTer_SOtryadomOhotnik_2";
		break;
		
		case "PZ_BasTer_SOtryadomOhotnik_2":
			DialogExit();
			
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Longway");
			LAi_SetImmortal(sld, false);
			DeleteAttribute(sld, "OfficerImmortal");
			if(CheckAttribute(sld, "Health.HP")) DeleteAttribute(sld, "Health.HP");
			if(CheckAttribute(sld, "Health.maxHP")) DeleteAttribute(sld, "Health.maxHP");
			sTemp = "RestoreHealth_" + sld.index;
			if(CheckAttribute(PChar, "quest.RestoreHealth_" + sld.index)) PChar.quest.(sTemp).over = "Yes";
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_CharacterDisableDialog(sld);
			}
			sld = CharacterFromID("PZ_BasTer_OtryadPesheraOff");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_CharacterDisableDialog(sld);
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_IshemLongway_Zastupaemsya");
			
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition.l1 = "NPC_Death";
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition.l1.character = "Longway";
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition = "PZ_LongwayNelzyaUmeret";
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_Bad_1":
			dialog.text = "如果你只是想谈谈, 就不会让我解除武装。 但老虎即使收起爪子, 仍然是老虎。 你一定早就决定背叛朗威了 —没必要撒谎。 自卫吧, 船长! ";
			link.l1 = "该死! ";
			link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_Bad_2";
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_Bad_2":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("Guadeloupe_CaveEntrance")], false);
			LAi_SetFightMode(pchar, true);
			
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				LAi_CharacterDisableDialog(sld);
			}
			
			sld = CharacterFromID("Longway");
			LAi_SetImmortal(sld, false);
			DeleteAttribute(sld, "OfficerImmortal");
			if(CheckAttribute(sld, "Health.HP")) DeleteAttribute(sld, "Health.HP");
			if(CheckAttribute(sld, "Health.maxHP")) DeleteAttribute(sld, "Health.maxHP");
			sTemp = "RestoreHealth_" + sld.index;
			if(CheckAttribute(PChar, "quest.RestoreHealth_" + sld.index)) PChar.quest.(sTemp).over = "Yes";
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_BasTer_MyUbilLongway_BadFinal");
		break;
		
		case "PZ_BasTer_SOtryadom_UbiliLongway":
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "真不敢相信我们解决了他! 但告诉我, 为什么他叫你船长? ";
				link.l1 = "这比看起来更复杂, 伙计。 我需要让你们的指挥官放心。 重要的是结果, 对吧? 结果是朗威死了, 我帮了你们。 ";
				link.l1.go = "PZ_BasTer_SOtryadom_UbiliLongway_2";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "即使有你在场也没用 —他还是袭击了我们。 该死的野蛮人... ";
				link.l1 = "你不应该那样谈论他。 他攻击我们是因为他心烦意乱, 以为我和你们在一起。 ";
				link.l1.go = "PZ_BasTer_SOtryadom_UbiliLongway_2";
			}
		break;
		
		case "PZ_BasTer_SOtryadom_UbiliLongway_2":
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "也许吧。 在这种情况下, 再见, 先生。 我们会自己告诉指挥官那个中国人终于死了。 ";
				link.l1 = "很好, 谢谢你。 再见, 伙计们。 ";
				link.l1.go = "PZ_BasTer_SOtryadom_UbiliLongway_3";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "好吧, 不管心烦意乱还是不心烦意乱, 野蛮还是不野蛮, 都改变不了什么 —他之前杀了我们很多人, 先流了血。 ";
				link.l1 = "一定有什么驱使他到了那种状态。 但我们不要纠结于此。 我要走了, 你们可以在方便的时候回到指挥官那里。 再见。 ";
				link.l1.go = "PZ_BasTer_SOtryadom_UbiliLongway_3";
			}
		break;
		
		case "PZ_BasTer_SOtryadom_UbiliLongway_3":
			DialogExit();
			
			LAi_SetWarriorType(npchar);
			LAi_CharacterDisableDialog(npchar);
			ChangeCharacterNationReputation(pchar, FRANCE, 12);
			AddQuestRecord("PZ", "11");
			CloseQuestHeader("PZ");
			
			LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", false);
			LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", false);
			//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", false);
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog":
			dialog.text = "船长阁下? ";
			link.l1 = "是我! 我到处在找你, 朗威。 你在镇上引起了不小的轰动。 我们有很多事情要讨论, 所以立即回船。 ";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_2";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_2":
			dialog.text = "在那边! ";
			link.l1 = "我看到我们有伴了。 看来我们要晚一点了。 ";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_3";
			locCameraFromToPos(-12.27, 1.29, -8.89, true, -3.23, -1.20, -4.77);
			DoQuestCheckDelay("PZ_IshemLongway_SorraKomendant_Dialog_Povernutsya", 1.3);
			
			for (i=1; i<=5; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("PZ_BasTer_OtryadPeshera"+i, "sold_fra_"+(rand(7)+1), "man", "man", sti(pchar.rank), FRANCE, 0, true, "soldier"));
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload2");
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, pchar, "", -1);
				LAi_SetHP(sld, 60.0, 60.0);
			}
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_3":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("Guadeloupe_CaveEntrance")], false);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Longway");
			LAi_SetImmortal(sld, false);
			DeleteAttribute(sld, "OfficerImmortal");
			if(CheckAttribute(sld, "Health.HP")) DeleteAttribute(sld, "Health.HP");
			if(CheckAttribute(sld, "Health.maxHP")) DeleteAttribute(sld, "Health.maxHP");
			sTemp = "RestoreHealth_" + sld.index;
			if(CheckAttribute(PChar, "quest.RestoreHealth_" + sld.index)) PChar.quest.(sTemp).over = "Yes";
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_IshemLongway_SorraKomendant_Pobeda1");
			
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition.l1 = "NPC_Death";
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition.l1.character = "Longway";
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition = "PZ_LongwayNelzyaUmeret";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_4":
			dialog.text = "更多人来了! ";
			link.l1 = "他们真固执 —我得承认。 我们在这里太暴露了。 我们去洞穴 —更容易自卫。 ";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_5";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_5":
			DialogExit();
			pchar.questTemp.PZ_IshemLongway_SorraKomendant = true;
			PlaySound("Interface\MusketFire1.wav");
			PlaySound("Interface\MusketFire1.wav");
			PlaySound("Interface\MusketFire1.wav");
			
			sld = CharacterFromID("Longway");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "Guadeloupe_Cave", "goto", "locator1", "PZ_IshemLongway_VPesheru", -1);
			
			LAi_SetActorType(pchar);
			LAi_ActorRunToLocation(pchar, "reload", "reload1", "Guadeloupe_Cave", "goto", "locator1", "PZ_IshemLongway_VPesheru", -1);
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_6":
			dialog.text = "我们不能永远待在这里。 ";
			link.l1 = "这就是在发生这一切之后你想说的第一件事吗, 朗威? 你不觉得是时候解释一下发生了什么吗? ";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_7";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_7":
			dialog.text = "船长阁下, 朗威... ";
			link.l1 = "但你说得对 —我们不能待在这里。 在另一支小队出现之前, 我们开始行动。 我们起航后在船上谈。 ";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_8";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_8":
			DoQuestReloadToLocation("Guadeloupe_CaveEntrance", "reload", "reload1", "PZ_IshemLongway_VyhodIsPeshery");
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_1":
			dialog.text = "白人的狡猾和恶意是无止境的。 ";
			link.l1 = "嘿, 我也是白人! 此外, 你杀了他们的朋友和战友 —他们有权生气。 ";
			link.l1.go = "PZ_IshemLongway_Zastupaemsya_2";
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_2":
			dialog.text = "你原谅他们了吗, 船长阁下? ";
			link.l1 = "我原谅你, 朗威。 我敦促你不要以肤色评判人。 你最应该理解这一点。 我们被打断了 —我们刚才说到... ? ";
			link.l1.go = "PZ_IshemLongway_Zastupaemsya_3";
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_3":
			dialog.text = "船长! 在你后面! ";
			link.l1 = "哦, 他们今天不会让我们好好谈话的... ";
			link.l1.go = "PZ_IshemLongway_Zastupaemsya_4";
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_4":
			DialogExit();
			LAi_SetCurHPMax(pchar);
			LAi_GetCharacterMaxEnergy(pchar);
			LAi_SetCurHPMax(sld);
			LAi_GetCharacterMaxEnergy(sld);
			
			sld = CharacterFromID("Longway");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			for (i=6; i<=10; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("PZ_BasTer_OtryadPeshera"+i, "sold_fra_"+(rand(7)+1), "man", "man", sti(pchar.rank), FRANCE, 0, true, "soldier"));
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload2");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_SetHP(sld, 60.0, 60.0);
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_IshemLongway_Zastupaemsya_5");
			
			AddDialogExitQuest("MainHeroFightModeOn"); // Rebbebion, fix
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_6":
			dialog.text = "安全了, 船长阁下。 ";
			link.l1 = "很好, 但我们不要在这里逗留。 你和我有很多事情要谈。 跟我来 —我们回船。 ";
			link.l1.go = "PZ_IshemLongway_Zastupaemsya_7";
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_7":
			DialogExit();
			
			sld = CharacterFromID("Longway");
			AddPassenger(pchar, sld, false);
			sld.OfficerImmortal = true;
			sld.Health.HP       = 60.0;
			sld.Health.maxHP    = 60.0;
		
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			sld.Dialog.CurrentNode = "Longway_officer";
			
			LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", false);
			LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", false);
			//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", false);
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
			AddQuestRecord("PZ", "14");
			DeleteQuestCondition("PZ_LongwayNelzyaUmeret");
			DeleteQuestCondition("PZ_KorablBuhta_BadFinal");
			
			//第二阶段继续
			PChar.quest.PZ_LongwayRazgovorVKaute.win_condition.l1 = "EnterToSea"
			PChar.quest.PZ_LongwayRazgovorVKaute.win_condition = "PZ_LongwayRazgovorVKaute";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_1":
			dialog.text = "船长阁下, 真的是您... ? ";
			link.l1 = "是我, 朗威。 你还好吗? ";
			link.l1.go = "PZ_IshemLongway_SrazuNashli_2";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_2":
			dialog.text = "朗威很好。 谢谢。 但是, 船长! 看! ";
			link.l1 = "跑到洞穴去, 快点! 这是个好的防御位置! ";
			link.l1.go = "PZ_IshemLongway_SrazuNashli_3";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_3":
			DialogExit();
			PlaySound("Interface\MusketFire1.wav");
			PlaySound("Interface\MusketFire1.wav");
			PlaySound("Interface\MusketFire1.wav");
			
			sld = CharacterFromID("Longway");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "Guadeloupe_Cave", "goto", "locator1", "PZ_IshemLongway_VPesheru", -1);
			
			LAi_SetActorType(pchar);
			LAi_ActorRunToLocation(pchar, "reload", "reload1", "Guadeloupe_Cave", "goto", "locator1", "PZ_IshemLongway_VPesheru", -1);
		break;
		
		case "PZ_IshemLongway_SrazuNashli_4":
			dialog.text = "朗威会检查士兵是否还在来。 ";
			link.l1 = "我们一起去 —我们无法抵抗整个驻军。 ";
			link.l1.go = "PZ_IshemLongway_SrazuNashli_5";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_5":
			dialog.text = "是, 船长阁下? ";
			link.l1 = "我们有很多事情要谈。 现在跟我来 —我们需要立即起锚。 ";
			link.l1.go = "PZ_IshemLongway_SrazuNashli_6";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_6":
			DoQuestReloadToLocation("Guadeloupe_CaveEntrance", "reload", "reload1", "PZ_IshemLongway_VyhodIsPeshery");
		break;
		
		// 阶段2, 历史篇章
		case "PZ_LongwayRazgovorOProshlom":
			dialog.text = "再次感谢您的帮助, 船长阁下。 我相信您有很多问题。 ";
			link.l1 = "可以这么说。 你为什么杀那些士兵? 你不会为了取乐而杀人 —我知道。 ";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_LongwayRazgovorOProshlom_2":
			dialog.text = "不, 朗威不会。 士兵们试图阻止朗威, 而监狱不是选择。 他们不会听一个中国人的 —只有白人才能得到那种礼遇。 ";
			link.l1 = "他们也不总是听其他白人的, 但我明白你的意思。 尽管如此, 像屠宰牲畜一样在城里屠杀他们? 你在巴斯特尔做什么? ";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_3";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_3":
			dialog.text = "白人不仅经常不听我的; 有时他们甚至不说话。 当他们说话时, 就是叫卫兵。 朗威无法选择自己的肤色或眼睛, 但他为自己是谁而自豪。 当士兵嘲笑和威胁时, 朗威会感到厌倦... 和愤怒。 ";
			link.l1 = "从现在起, 我们一起工作。 人们会和我说话而不是叫卫兵... 通常是这样。 但说真的, 告诉我你的任务。 让我帮助你。 ";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_4";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_4":
			dialog.text = "请, 船长阁下, 理解朗威。 他发誓要独自完成这件事。 不要逼他。 你欠朗威这么多。 ";
			link.l1 = "我真的很感激, 但那时我自己就能处理范.默登。 然而, 我们从一开始就扯平了 —你说我挽回了你的面子, 你救了我的命。 现在我又救了你一次。 ";
			if (CheckAttribute(pchar, "questTemp.PZ_NashliArhiv")) link.l1.go = "PZ_LongwayRazgovorOProshlom_5";
			else link.l1.go = "PZ_LongwayRazgovorOProshlom_Grubim_1";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_5":
			dialog.text = "嗯... 你说得对, 船长阁下。 朗威相信您是他在白人中真正的朋友。 曾经, 他也这样认为, 但被狠狠地误解了。 您还记得约翰.默多克吗? 约翰.范.默登? ";
			link.l1 = "你提到范.默登真奇怪。 最近, 有人就在我眼皮底下从他的档案里撕了几页。 这和你的事有关吗? 你找到小偷了吗? ";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_6";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_6":
			dialog.text = "找到了。 小偷是... 朗威。 他非常抱歉, 船长阁下。 那时, 他不知道是否能完全信任您。 ";
			if (sti(pchar.reputation.nobility) <= 60)
			{
				link.l1 = "你谈论友谊, 却背后偷我的东西? 这是第一次也是最后一次, 朗威。 你明白吗? ";
				link.l1.go = "PZ_LongwayRazgovorOProshlom_Grubim_1";
				Notification_Reputation(false, 61, "low");
			}
			else
			{
				link.l1 = "你是怎么做到的, 朗威? ";
				link.l1.go = "PZ_LongwayRazgovorOProshlom_Proshaem_1";
				Notification_Reputation(true, 71, "low");
			}
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Grubim_1":
			dialog.text = "朗威明白。 他是认真的。 ";
			link.l1 = "希望如此。 现在告诉我你是如何走到这一步的 —你许了什么诺言, 何时, 对谁。 ";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_Grubim_2";
			if (CheckAttribute(pchar, "questTemp.PZ_NashliArhiv")) AddComplexSelfExpToScill(100, 100, 100, 100);
			Notification_Approve(false, "Longway");
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Grubim_2":
			dialog.text = "是, 船长阁下\n朗威在寻找对他来说最重要的在世之人 —常兴。 ";
			link.l1 = "常兴 —是你最好的朋友吗? ";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_7";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Proshaem_1":
			dialog.text = "多亏了您的善良, 其他船员很快就习惯了我并开始信任我。 ";
			link.l1 = "好吧, 我明白了。 不喜欢表扬, 但干得好, 朗威... 如果你清理了你闯入留下的烂摊子。 ";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_Proshaem_2";
			AddComplexLandExpToScill(200, 200, 0);
			pchar.questTemp.PZ_FlagArhiv = true;
			Notification_Approve(true, "Longway");
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Proshaem_2":
			dialog.text = "对。 但没时间了。 ";
			link.l1 = "我想也是。 但尽量别再那样做了, 好吗? 如果你需要什么, 直接问。 你可以信任我。 现在, 告诉我你的誓言。 ";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_Proshaem_3";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Proshaem_3":
			dialog.text = "当然, 船长阁下, 朗威很高兴与您分担重担。 \n朗威在寻找对他来说最重要的在世之人 —常兴。 ";
			link.l1 = "常兴 —是你最好的朋友吗? ";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_7";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_7":
			dialog.text = "常兴是我的家人, 我的妹妹。 她多年前失踪了。 为了找到她, 朗威在寻找可能知道她下落的人。 ";
			link.l1 = "这和范.默登的档案有什么关系? 和你妹妹的失踪有关吗? ";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_8";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_8":
			dialog.text = "没错。 这一切都是相连的。 朗威和约翰多年前在你们称为福尔摩沙的地方相识, 远在我来到群岛之前。 ";
			link.l1 = "你们认识这么多年了? 范.默登也参与其中? 真是个故事! 他和你妹妹的失踪有什么联系? ";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_9";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_9":
			dialog.text = "他帮助我寻找非常坏的人 —即使以白人的标准来看。 奥利维罗.费门特洛斯。 安东.范.迪门和乔普.范德温克。 ";
			link.l1 = "从名字判断, 一个是葡萄牙人, 另外两个是荷兰人。 ";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_10";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_10":
			dialog.text = "是的, 正确。 但搜索没有成功。 朗威耐心等待上天的指引。 所以当您获得范.默登的档案时, 我决定研究它。 当我找到第一页提到奥利维罗时, 我撕下它们并逃离了船舱。 ";
			link.l1 = "一切终于串联起来了。 ";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_11";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_11":
			dialog.text = "但故事本身才刚刚开始。 船长阁下, 您想知道朗威从一开始的搜索经历吗? 您准备好坐下来听了吗? ";
			link.l1 = "这正是我叫你到船舱的原因。 请讲。 ";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_12";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_12":
			DialogExit();
			
			SetCurrentTime(12, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			SetMainCharacterIndex(GetCharacterIndex("Longway"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			DoQuestReloadToLocation("Formosa", "patrol", "patrol1", "PZ_Formosa_Start");
		break;
		
		case "PZ_Formosa_Tavern_1":
			dialog.text = "中国人不准进来。 这是一家体面的场所, 为体面的人服务 —不是为你这种人。 ";
			link.l1 = "我只有一个问题。 让我问完就走。 ";
			link.l1.go = "PZ_Formosa_Tavern_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Formosa_Tavern_2":
			dialog.text = "先学会好好说话! 我告诉过你 —不欢迎你这种人。 ";
			link.l1 = "我在哪里可以找到奥利维罗.费门特洛斯? 告诉我, 我就走。 ";
			link.l1.go = "PZ_Formosa_Tavern_3";
		break;
		
		case "PZ_Formosa_Tavern_3":
			dialog.text = "你也聋了吗? 别考验我的耐心, 否则整个房间很快就会弥漫着黄种人的 guts。 ";
			link.l1 = "我的族人在这里生活了数千年。 这是我们的岛屿, 我们甚至不能进入一个简单的酒馆? ";
			link.l1.go = "PZ_Formosa_Tavern_4";
		break;
		
		case "PZ_Formosa_Tavern_4":
			dialog.text = "哦, 口气不小啊? 你可能会因此被绞死。 滚出去! ";
			link.l1 = "... ";
			link.l1.go = "PZ_Formosa_Tavern_5";
		break;
		
		case "PZ_Formosa_Tavern_5":
			DialogExit();
			locCameraSleep(true);
			LAi_CharacterDisableDialog(npchar);
			
			sld = CharacterFromID("PZ_Formosa_smuggler");
			LAi_CharacterEnableDialog(sld);
			//AddLandQuestMark(sld, "questmarkmain");
			LAi_Fade("PZ_Formosa1_9", "");
		break;
		
		case "PZ_Formosa_smuggler_1":
			dialog.text = "我听说了你的大麻烦, 我的小朋友。 你不该那么大声 —错误的名字, 错误的地方。 ";
			link.l1 = "你知道这个人的事? ! 告诉我! ";
			link.l1.go = "PZ_Formosa_smuggler_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Formosa_smuggler_2":
			dialog.text = "冷静点, 伙计。 ";
			link.l1 = "抱歉。 ";
			link.l1.go = "PZ_Formosa_smuggler_3";
		break;
		
		case "PZ_Formosa_smuggler_3":
			dialog.text = "我不要你的道歉, 但我要你的钱。 也许那样我会帮你。 我是马塞洛.舒尔特。 你呢? 你有钱, 对吧? ";
			link.l1 = "我叫张图。 我有钱。 够了吗? ";
			link.l1.go = "PZ_Formosa_smuggler_4";
		break;
		
		case "PZ_Formosa_smuggler_4":
			dialog.text = "(吹口哨) 埃斯库多。 比索。 基尔德。 达布隆... 甚至还有一些你们那种奇怪的硬币。 这就行了。 好吧, 钟钟, 我会看看能找到什么关于那个人的信息。 别担心, 我几乎每天都在这里, 所以你的钱很安全。 每天来看看, 我们肯定会碰面。 ";
			link.l1 = "希望如此。 我没有更多钱了... ";
			link.l1.go = "PZ_Formosa_smuggler_5";
		break;
		
		case "PZ_Formosa_smuggler_5":
			DialogExit();
			LAi_SetStayType(pchar);
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("几天过去了, "+ NewStr() +"1645年4月4日。 ", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Formosa_tavern", "goto", "goto1", "PZ_Formosa_Spustya4Dnya");
			LaunchFrameForm();
		break;
		
		case "PZ_Formosa_smuggler_11":
			dialog.text = "啊, 张张! 你已经在这里了。 ";
			link.l1 = "我叫张图。 ";
			link.l1.go = "PZ_Formosa_smuggler_12";
		break;
		
		case "PZ_Formosa_smuggler_12":
			dialog.text = "没关系, 伙计。 ";
			link.l1 = "你找到奥利维罗在哪里了吗? ";
			link.l1.go = "PZ_Formosa_smuggler_13";
		break;
		
		case "PZ_Formosa_smuggler_13":
			dialog.text = "不, 一点都不知道。 ";
			link.l1 = "我的钱! ";
			link.l1.go = "PZ_Formosa_smuggler_14";
		break;
		
		case "PZ_Formosa_smuggler_14":
			dialog.text = "别这么急躁! 如果我什么都没查到, 我还敢再接近你吗? 我要介绍一个知道的人给你。 你很幸运, 他喜欢你这样的亚洲人。 他甚至有相配的仆人 —见鬼, 甚至有女仆。 还在学你们的脏话。 名叫约翰.范.默登。 他会在官邸附近的一栋两层楼的房子里等你。 ";
			link.l1 = "谢谢。 ";
			link.l1.go = "PZ_Formosa_smuggler_15";
		break;
		
		case "PZ_Formosa_smuggler_15":
			DialogExit();
			
			locCameraSleep(true);
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(pchar, "reload", "reload1_back", "PZ_Formosa1_11", -1);
			LAi_ActorGoToLocation(npchar, "goto", "goto3", "", "", "", "", -1);
			npchar.location = "None";
			LocatorReloadEnterDisable("Formosa", "houseSp1", false);
		break;
		
		case "PZ_Formosa_JohanVanMerden_1":
			dialog.text = "你显然是张张? 进来吧, 别害羞。 ";
			link.l1 = "我叫张图。 ";
			link.l1.go = "PZ_Formosa_JohanVanMerden_2";
			DelLandQuestMark(npchar);
			locCameraFromToPos(-1.91, 2.06, -1.75, true, 2.23, -0.85, 0.85);
		break;
		
		case "PZ_Formosa_JohanVanMerden_2":
			dialog.text = "是吗? 抱歉。 那个马塞洛和他的玩笑... 真遗憾, 很少有人对你们的文化感兴趣。 就因为不同的语言和眼睛的形状。 但你很聪明。 不像那些黑人, 呵呵。 ";
			link.l1 = "(用普通话) 所以走私者没撒谎 —你确实是个有文化的人。 你真的说我们的语言? ";
			link.l1.go = "PZ_Formosa_JohanVanMerden_2a";
			link.l2 = "感谢你对我文化的赞美之词。 你一定是约翰.范.默登? ";
			link.l2.go = "PZ_Formosa_JohanVanMerden_3";
		break;
		
		case "PZ_Formosa_JohanVanMerden_2a":
			dialog.text = "哦... 我只听懂了几个词。 你看, 我还在学习。 你能继续用荷兰语吗? ";
			link.l1 = "如你所愿。 你是约翰.范.默登? ";
			link.l1.go = "PZ_Formosa_JohanVanMerden_3";
		break;
		
		case "PZ_Formosa_JohanVanMerden_3":
			dialog.text = "是的, 张图, 是我。 我听说你在找奥利维罗.费门特洛斯。 我确实知道在哪里能找到他, 但首先告诉我 —你为什么找他? 你的答案将决定我的回答。 ";
			link.l1 = "他... 绑架了我最后也是最亲爱的家人 —我的妹妹, 常兴。 ";
			link.l1.go = "PZ_Formosa_JohanVanMerden_4";
		break;
		
		case "PZ_Formosa_JohanVanMerden_4":
			dialog.text = "那我必须让你失望了, 张图。 现在她可能已经没有希望了。 她很可能被卖给了富有的种植园主或妓院。 无论哪种方式, 你都救不了她。 ";
			link.l1 = "我相信常兴还活着。 奥利维罗盯上了她。 她骄傲地拒绝了他。 他在我不在家时偷走了她。 并且... 杀了我们的父母。 ";
			link.l1.go = "PZ_Formosa_JohanVanMerden_5";
		break;
		
		case "PZ_Formosa_JohanVanMerden_5":
			dialog.text = "我... 很抱歉。 如果是这样的话, 常兴 —对吗? —可能还活着。 我们这样办: 给我一些时间, 确切查明奥利维罗现在在哪里。 比如说一周。 然后我们再见面。 在城门外见 —谁知道有什么眼睛在跟踪你到这里。 我不想比习惯的更卷入其中, 希望你理解。 ";
			link.l1 = "我... 我非常感激您, 范.默登先生。 期待我们下次见面。 ";
			link.l1.go = "PZ_Formosa_JohanVanMerden_6";
		break;
		
		case "PZ_Formosa_JohanVanMerden_6":
			DialogExit();
			LAi_SetStayType(pchar);
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("一周过去了, "+ NewStr() +"1645年4月11日。 ", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Formosa_ExitTown", "goto", "goto3", "PZ_Formosa_Spustya7Dney");
			LaunchFrameForm();
		break;
		
		case "PZ_Formosa_JohanVanMerden_11":
			dialog.text = "你好, 张图。 我看到你眼中的火焰。 我确实有消息, 但不是好消息。 ";
			link.l1 = "任何消息对我都极为重要。 请告诉我, 范.默登先生。 ";
			link.l1.go = "PZ_Formosa_JohanVanMerden_12";
		break;
		
		case "PZ_Formosa_JohanVanMerden_12":
			dialog.text = "唉... 费门特洛斯大约一个月前出发去巴达维亚了。 这是我得到的关于他的唯一线索。 好消息是他计划在那里待一段时间, 所以如果你现在去, 就能抓住他。 坏消息? 他是总督安东尼.范.迪门的密友。 你无法接近他。 ";
			link.l1 = "这个消息足够了。 衷心感谢您, 范.默登先生。 我立即出发。 ";
			link.l1.go = "PZ_Formosa_JohanVanMerden_13";
		break;
		
		case "PZ_Formosa_JohanVanMerden_13":
			dialog.text = "我就知道你会这么说, 所以我决定为你和常兴增加胜算。 我给我的老朋友奥利弗.特鲁斯特写了封信。 他在巴达维亚开了一家店。 他欠我一个人情, 所以会帮助你。 ";
			link.l1 = "我... 我不知道该说什么... ";
			link.l1.go = "PZ_Formosa_JohanVanMerden_14";
			//Log_Info("您收到了信件");
			PlaySound("interface\important_item.wav");
		break;
		
		case "PZ_Formosa_JohanVanMerden_14":
			dialog.text = "简单说声'谢谢'就够了。 如果你在城里找不到奥利维罗, 就找晨星号。 你总能通过他的船追踪到他。 祝你好运, 我的朋友 —你和你妹妹会需要的。 ";
			link.l1 = "我从心底感谢您, 范.默登先生。 ";
			link.l1.go = "PZ_Formosa_JohanVanMerden_15";
		break;
		
		case "PZ_Formosa_JohanVanMerden_15":
			DialogExit();
			LAi_SetStayType(pchar);
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("巴达维亚, "+ NewStr() +"1645年5月29日。 ", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Batavia", "merchant", "mrcActive5", "PZ_Batavia_Puteshestvie");
			LaunchFrameForm();
		break;
		
		case "PZ_OliverTrust_1": //
			dialog.text = "你是谁, 在这里做什么? 我不与你这种人交易。 ";
			link.l1 = "我有一封信给你。 ";
			link.l1.go = "PZ_OliverTrust_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_OliverTrust_2":
			dialog.text = "啊, 信使! 虽然我今天没期待任何信件。 待在这里! 我看看。 ";
			link.l1 = "你是奥利弗.特鲁斯特吗? 范.默登派我来的。 ";
			link.l1.go = "PZ_OliverTrust_3";
			//Log_Info("您递交了信件");
			PlaySound("interface\important_item.wav");
		break;
		
		case "PZ_OliverTrust_3":
			dialog.text = "我看得懂, 你知道。 通常我会把你赶走, 但像范.默登这样的人不会接受拒绝。 终于到了和范.迪门清算的时候了。 ";
			link.l1 = "我的目标是费门特洛斯。 范.迪门呢? ";
			link.l1.go = "PZ_OliverTrust_4";
		break;
		
		case "PZ_OliverTrust_4":
			dialog.text = "那不关你的事。 你应该感激我帮你。 现在仔细听, 在我认为这是个坏主意之前。 我认识费门特洛斯。 他在这里待了一段时间, 但现在不在了。 晨星号几周前离开了。 天知道它什么时候回来。 所以你的目标变了, 是费门特洛斯的一个朋友... ";
			link.l1 = "... 范.迪门。 ";
			link.l1.go = "PZ_OliverTrust_5";
		break;
		
		case "PZ_OliverTrust_5":
			dialog.text = "是的。 你也知道? 我猜约翰告诉你了? 哦, 范.默登... 你真是个大胆的混蛋。 但既然你已经知道范.迪门, 你也知道他的高位, 对吧? 你有什么宏伟计划接近总督? 我确定不是强攻他的官邸! ";
			link.l1 = "张图是个熟练的战士。 ";
			link.l1.go = "PZ_OliverTrust_6";
		break;
		
		case "PZ_OliverTrust_6":
			dialog.text = "熟练的战士, 嗯? 你意识到我们现在都被卷进来了吗? 如果你被抓, 我会怎么样? 为了你自己和我的安全, 我必须帮助你。 除了住在官邸, 范.迪门还定期访问城外的种植园和他的情妇维特。 ";
			link.l1 = "你提到要帮助我。 ";
			link.l1.go = "PZ_OliverTrust_12";
		break;
		
		case "PZ_OliverTrust_12":
			dialog.text = "我认为每个人都应该有激情, 有爱好。 至于我, 我收集稀有昂贵的武器。 有时它们有历史, 有时没有, 但总是致命的。 我的收藏可能对你的 crusade 有用。 那么, 告诉我, 你计划在哪里伏击范.迪门? ";
			link.l1 = "(官邸) 既然你有这么多好武器, 我要拿最好的 blade。 有了它, 张图在白人中将无人能敌。 ";
			link.l1.go = "PZ_OliverTrust_resedinsia_1";
			link.l2 = "(种植园) 我会在种植园的路上伏击他们 —他们无处可逃。 ";
			link.l2.go = "PZ_OliverTrust_Plantation1";
			link.l3 = "(情妇处) 情妇那里人不会多, 所以卫兵不会及时反应。 ";
			link.l3.go = "PZ_OliverTrust_lubovnitsa_1";
			SetCharacterPerk(pchar, "Gunman");
			SetCharacterPerk(pchar, "GunProfessional");
			InterfaceStates.Buttons.Save.enable = false;
		break;
		
		// Rebbebion, ну, с Богом... 
		case "PZ_OliverTrust_Plantation1":
			pchar.questTemp.PZ_Batavia_plantation_Go = true;
			
			dialog.text = "好选择! 我印象深刻。 为了充分利用, 你需要一把好火器。 告诉我, 张图, 你能瞄准多远? ";
			link.l1 = "说实话... 不太远, 我必须确保不失误。 "
			link.l1.go = "PZ_OliverTrust_Plantation_MediumDistance1";
			link.l2 = "我会从远处攻击 —我的敌人甚至不会意识到我从哪里击中他。 ";
			link.l2.go = "PZ_OliverTrust_Plantation_FarDistance1";
			notification("神射手解锁", "Longway");
			SetCharacterPerk(pchar, "Sniper");
		break;
		
		case "PZ_OliverTrust_Plantation_MediumDistance1":
			// 让朗威成为火枪手并同时发放火枪
			/* pchar.model = "Longway_mush";
			pchar.model.animation = "mushketer"; */
			pchar.model = "Longway";
			pchar.model.animation = "Longway";
			Characters_RefreshModel(pchar);
			GiveItem2Character(pchar, "mushket6"); 
			EquipCharacterByItem(pchar, "mushket6");
			//Log_Info("您获得了塔式火绳枪");
			PlaySound("interface\important_item.wav");
			
			AddItems(pchar, "grapeshot", 50);
			AddItems(pchar, "gunpowder", 50);
			LAi_SetCharacterUseBullet(pchar, GUN_ITEM_TYPE, "grapeshot");
			
			dialog.text = "我明白了。 那样的话, 拿这个! 一把古董葡萄牙塔式 blunderbuss, 发射大口径弹药。 即使在旧大陆也不再生产了。 ";
			link.l1 = "我小时候见过一把... ";
			link.l1.go = "PZ_OliverTrust_Plantation_MediumDistance2";
		break;
		
		case "PZ_OliverTrust_Plantation_MediumDistance2":
			dialog.text = "所以, 你知道如何使用它? ";
			link.l1 = "不... ";
			link.l1.go = "PZ_OliverTrust_Plantation_MediumDistance3";
		break;
		
		case "PZ_OliverTrust_Plantation_MediumDistance3":
			dialog.text = "记住, 可互换机制已经生锈了。 没有油能修复 —它彻底坏了。 装填很困难, 所以现在就做。 仔细看 —用点力, 像这样。 但不要太用力, 否则会弄坏它。 ";
			link.l1 = "像这样? ";
			link.l1.go = "PZ_OliverTrust_Plantation_MediumDistance4";
		break;
		
		case "PZ_OliverTrust_Plantation_MediumDistance4":
			dialog.text = "正是。 ";
			link.l1 = "明白了。 非常感谢! ";
			link.l1.go = "PZ_OliverTrust_13";
		break;
		
		case "PZ_OliverTrust_Plantation_FarDistance1":
			// 让朗威成为火枪手并同时发放火枪
			/* pchar.model = "Longway_mush";
			pchar.model.animation = "mushketer"; */
			pchar.model = "Longway";
			pchar.model.animation = "Longway";
			Characters_RefreshModel(pchar);
			GiveItem2Character(pchar, "mushket2x2"); 
			EquipCharacterByItem(pchar, "mushket2x2");
			//Log_Info("您获得了双管猎枪");
			PlaySound("interface\important_item.wav");
			
			AddItems(pchar, "bullet", 50);
			AddItems(pchar, "gunpowder", 50);
			LAi_SetCharacterUseBullet(pchar, GUN_ITEM_TYPE, "bullet");
			
			dialog.text = "真正的神射手! 小心, 这是一份礼物。 这是罕见的案例, 武器既华丽又致命。 一把双管猎枪! 拿着很重, 使用简单。 你已经知道如何射击了吗? ";
			link.l1 = "明白了。 非常感谢! ";
			link.l1.go = "PZ_OliverTrust_13";
		break;
		
		case "PZ_OliverTrust_lubovnitsa_1":
			dialog.text = "你对卫兵的看法是对的, 但不要低估危险。 范.迪门在城里从不离开他的得力助手乔普.范德温克。 ";
			link.l1 = "那么, 他们和维特在一起... ? ";
			link.l1.go = "PZ_OliverTrust_lubovnitsa_2";
			pchar.questTemp.PZ_Batavia_lubovnitsa_Go = true;
			AddCharacterSkillDontClearExp(pchar, "Sailing", 10);
			AddCharacterSkillDontClearExp(pchar, "Commerce", 10);
			AddCharacterSkillDontClearExp(pchar, "Repair", 10);
			notification("航海技能+", "Longway");
			notification("鼠狼解锁", "Longway");
			SetCharacterPerk(pchar, "RatsWolf");
		break;
		
		case "PZ_OliverTrust_lubovnitsa_2":
			dialog.text = "什么? 哈! 你想象力真丰富, 中国人! 安东是个懦夫, 范德温克在那里是为了保护他, 以防有人打扰他们的'私人时间'\n乔普总是穿着厚重的战壕装甲 —大多数冷兵器都无法穿透。 这就是为什么你也需要特别的东西。 拿这把细剑。 它很长, 比大多数其他 swords 更坚固, 重量像一把好 blade。 ";
			link.l1 = "用于对抗装甲敌人的细剑... ? ";
			link.l1.go = "PZ_OliverTrust_lubovnitsa_3";
			//Log_Info("您获得了细剑");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(PChar, "blade_26");
			EquipCharacterByItem(Pchar, "blade_26");
		break;
		
		case "PZ_OliverTrust_lubovnitsa_3":
			dialog.text = "不要瞄准装甲本身 —这不是 estoc。 攻击缝隙和弱点, 如腹股沟。 腋窝和喉咙。 消耗他, 掌握节奏。 乔普还挥舞着一把重斧, 所以不要试图格挡他的打击 —躲开。 \n万一你找不到破绽, 拿这把 blunderbuss。 它通常装的是散弹, 但我为你准备了一套钢箭。 ";
			link.l1 = "火枪用的箭... ? ";
			link.l1.go = "PZ_OliverTrust_lubovnitsa_4";
			//Log_Info("您获得了滑膛枪");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(PChar, "pistol8");
			EquipCharacterByItem(Pchar, "pistol8");
			AddItems(Pchar, "harpoon", 30);
			AddItems(Pchar, "gunpowder", 30);
			LAi_SetCharacterUseBullet(Pchar, GUN_ITEM_TYPE, "harpoon");
		break;
		
		case "PZ_OliverTrust_lubovnitsa_4":
			dialog.text = "不寻常, 对吧? 新旧结合。 设计为单手射击, 但如果太重, 就用双手。 很多人都这样做。 \n还有这个, 试试这件柳条装甲。 它比乔普的胸甲轻, 但仍提供不错的保护。 不要让他的斧头直接命中 —即使是米兰装甲也无法承受那样的武器。 你明白吗? ";
			link.l1 = "是的, 我明白。 谢谢您, 特鲁斯特先生! ";
			link.l1.go = "PZ_OliverTrust_13";
			//Log_Info("您获得了皮制胸甲");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(PChar, "cirass5");
			EquipCharacterByItem(Pchar, "cirass5");
		break;
		
		case "PZ_OliverTrust_resedinsia_1":
			dialog.text = "过于自信了, 是吗? 也许我太早告诉你我的收藏了。 但是... 你已经下定决心了。 在光天化日之下攻击官邸是一个大胆的举动, 出人意料。 这把 blade 应该适合你的需要。 它不是世界上最好的, 但非常适合刺。 砍和劈。 ";
			link.l1 = "Clewang! 我认出这把 blade。 邻近岛屿的人经常使用。 ";
			link.l1.go = "PZ_OliverTrust_resedinsia_2";
			pchar.questTemp.PZ_Batavia_resedinsia_Go = true;
			notification("决斗者解锁", "Longway");
			SetCharacterPerk(pchar, "TannedLeather");
			SetCharacterPerk(pchar, "HT1");
		break;
		
		case "PZ_OliverTrust_resedinsia_2":
			dialog.text = "你以前用过吗? 很好。 你时间不多, 有很多敌人要面对。 这里, 也拿这个 —一把三管手枪, 镶嵌精美。 现在在我面前装填; 以后你没有时间了。 穿上这件决斗背心。 它很轻, 会给你所需的速度, 还有一些保护。 ";
			link.l1 = "谢谢您, 特鲁斯特先生! ";
			link.l1.go = "PZ_OliverTrust_13";
			//Log_Info("您获得了克利旺刀");
			//Log_Info("您获得了三管猎枪");
			//Log_Info("您获得了决斗背心");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(PChar, "blade_30");
			EquipCharacterByItem(Pchar, "blade_30");
			GiveItem2Character(PChar, "pistol2");
			EquipCharacterByItem(Pchar, "pistol2");
			GiveItem2Character(PChar, "cirass6");
			EquipCharacterByItem(Pchar, "cirass6");
			AddItems(Pchar, "grapeshot", 50);
			AddItems(Pchar, "gunpowder", 50);
			LAi_SetCharacterUseBullet(Pchar, GUN_ITEM_TYPE, "grapeshot");
		break;
		
		case "PZ_OliverTrust_13":
			dialog.text = "等等, 我们还没结束。 你活下来符合我们的共同利益。 拿着这个药, 战斗后治疗伤口。 \n还有这个不死药。 它味道和气味都很糟糕, 但能杀死你体内的任何毒药。 范.迪门的保镖乔普.范德温克在他的武器上涂了那东西。 自大的混蛋, 所以你将占优势。 ";
			link.l1 = "我不知道是否能足够感谢您, 特鲁斯特先生... ";
			link.l1.go = "PZ_OliverTrust_14";
			//Log_Info("您获得了10瓶治疗药水");
			//Log_Info("您获得了解毒药");
			PlaySound("interface\important_item.wav");
			AddItems(Pchar, "potion1", 10);
			AddItems(Pchar, "potion3", 1);
		break;
		
		case "PZ_OliverTrust_14":
			dialog.text = "你最好的感谢是如果被抓不要供出我。 尽管很可能他们会当场杀了你。 但如果你活下来, 告诉范.迪门他的死归功于我。 你能做到吗? ";
			link.l1 = "没问题。 再次感谢您, 特鲁斯特先生。 再见! ";
			link.l1.go = "PZ_Batavia_NaOhotu";
		break;
		
		case "PZ_Batavia_NaOhotu":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_resedinsia_Go"))
			{
				DoQuestReloadToLocation("Batavia", "reload", "reload1", "PZ_Batavia_BitvaSoStrazhnikami");
			}
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_lubovnitsa_Go"))
			{
				DoQuestReloadToLocation("Batavia_HouseF3", "reload", "reload1", "PZ_Batavia_BitvaLubovnitsa");
			}
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_Plantation_Go"))
			{
				/*EndQuestMovie();
				sld = &Locations[FindLocation("Batavia_plantation")];
				sld.locators_radius.quest.detector4 = 3.0;
				PChar.quest.PZ_Batavia_plantation1.win_condition.l1 = "locator";
				PChar.quest.PZ_Batavia_plantation1.win_condition.l1.location = "Batavia_plantation";
				PChar.quest.PZ_Batavia_plantation1.win_condition.l1.locator_group = "quest";
				PChar.quest.PZ_Batavia_plantation1.win_condition.l1.locator = "detector4";
				PChar.quest.PZ_Batavia_plantation1.win_condition = "PZ_Batavia_plantation_selfdialog";*/
				DoQuestReloadToLocation("Batavia_plantation", "quest", "detector2", "PZ_Batavia_plantation_setguards");
			}
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_1":
			dialog.text = "站住! 你要去哪里, 中国人? ";
			link.l1 = "去官邸。 ";
			link.l1.go = "PZ_Batavia_BitvaSoStrazhnikami_2";
			locCameraFromToPos(-0.44, 7.45, 24.65, true, -1.90, 5.10, 18.50);
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_2":
			dialog.text = "那是个反问句, 天才。 你凭什么认为有人会让你这样的人进去? ";
			link.l1 = "我和范.迪门先生有事务。 请让我过去。 ";
			link.l1.go = "PZ_Batavia_BitvaSoStrazhnikami_3";
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_3":
			dialog.text = "你知道总督的名字? 嗯... 告诉我你的事务是什么。 我会转达并给你答复。 ";
			link.l1 = "我只和范.迪门先生谈话。 他在等我。 让开, 否则你会后悔的。 ";
			link.l1.go = "PZ_Batavia_BitvaSoStrazhnikami_4";
			locCameraSleep(true);
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_4":
			dialog.text = "好吧, 好吧, 别叫了, 窄眼。 要么听我的, 要么没门。 ";
			link.l1 = "那就听我的。 ";
			link.l1.go = "PZ_Batavia_BitvaSoStrazhnikami_5";
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_5":
			DialogExit();
			LAi_SetActorType(pchar);
			CharacterTurnByChr(pchar, CharacterFromID("PZ_SoldResid_1"));
			LAi_group_MoveCharacter(pchar, LAI_GROUP_PLAYER);
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			
			sld = CharacterFromID("PZ_SoldResid_1");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
				
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			
			DoQuestCheckDelay("PZ_Batavia_resedinsia_1", 0.9);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_1":
			dialog.text = "该死的农民! 谁雇了你? 我会给你比那更多的钱! ";
			link.l1 = "你们白人只关心黄金。 愿龙诅咒你们这类人。 我来是为了信息, 但你们的人不让我进去。 ";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_2";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_2":
			dialog.text = "你想要什么? ! ";
			link.l1 = "费门特洛斯。 他现在在哪里? ";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_3";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_3":
			dialog.text = "奥利维罗? 但你到底为什么找他? 我什么都不会告诉你! ";
			link.l1 = "他杀了我的家人, 绑架了我的妹妹。 我给你的建议是开始说话。 为了你自己好。 ";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_4";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_4":
			dialog.text = "你要对我做什么? 整个驻军很快就会到这里。 ";
			link.l1 = "你听说过 Lynchy 吗? 这是我文化中的一种惩罚。 意思是'千刀万剐'。 ";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_5";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_5":
			dialog.text = "你没有时间在我身上施加那么多刀伤, 你这个蠢货! ";
			link.l1 = "这是一种比喻。 刽子手一刀一刀地砍。 或者切掉身体的部分。 我们尽可能多地做 —除非你开始说话。 ";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_6";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_6":
			DialogExit();
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_Sepp", "mercen_26", "man", "man", sti(pchar.rank), HOLLAND, -1, false, "quest"));
			sld.name = "Joep";
			sld.lastname = "van der Vink";
			GiveItem2Character(sld, "topor_04");
			EquipCharacterByItem(sld, "topor_04");
			GiveItem2Character(sld, "pistol3");
			EquipCharacterByItem(sld, "pistol3");
			sld.CantLoot = true;
			LAi_SetHP(sld, 300.0, 300.0);
			ChangeCharacterAddressGroup(sld, "Batavia_townhallRoom", "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			
			LAi_SetStayType(pchar);
			locCameraFromToPos(-3.06, 1.64, -0.43, true, 1.87, -1.20, 2.39);
			DoQuestCheckDelay("PZ_Batavia_BitvaResidensia_7", 2.5);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_7":
			dialog.text = "啊-啊-啊!!! 停下! 停下, 你这个肮脏的畜生。 我告诉你, 我什么都告诉你。 只要停下。 乔普! 终于! 你他妈的这段时间在哪里? ! ";
			link.l1 = "真是不巧... ";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_8";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_8":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_Sepp");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_9";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_9":
			dialog.text = "安东? 你需要马上看医生。 我一处理完这里就帮你去。 你! 你这个黄色屠夫, 到底在做什么? ! ";
			link.l1 = "黄色屠夫? 我有点喜欢这个称呼。 我只有一个问题需要回答, 但似乎没人愿意回答... ";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_10";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_10":
			dialog.text = "什么问题? ! ";
			link.l1 = "奥利维罗.费门特洛斯在哪里? 你就不能说那个吗? ";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_11";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_11":
			dialog.text = "我他妈才不在乎费门特洛斯! 谁给你钱和信息的? ! ";
			link.l1 = "奥利弗.特鲁斯特。 顺便说一句, 他想让我告诉你, 你欠他一条命。 ";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_12";
			
			sld = CharacterFromID("PZ_AntoniOneDimen");
			LAi_ActorSetGroundSitMode(sld);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_12":
			dialog.text = "特鲁斯特? ! 哈哈哈哈哈哈! 那个守财奴, 以为仅仅因为我们拿了他的种植园就能报复? 等我解决了你, 我们很快就会拿走他的商店和他的命。 ";
			link.l1 = "你在浪费我的时间。 ";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_13";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_13":
			DialogExit();
			LAi_SetFightMode(pchar, true);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			
			PChar.quest.PZ_Batavia_BitvaResidensia_8.win_condition.l1 = "NPC_Death";
			PChar.quest.PZ_Batavia_BitvaResidensia_8.win_condition.l1.character = "PZ_Sepp";
			PChar.quest.PZ_Batavia_BitvaResidensia_8.win_condition = "PZ_Batavia_BitvaResidensia_8";
		break;
		
		case "PZ_Batavia_PlantationSelfDialog":
			dialog.text = "(用普通话) 那么, 让我们找个好的伏击点。 ";
			if (CheckCharacterItem(pchar, "mushket6"))
			{
				link.l1 = "(用普通话) 用这个生锈的东西, 我需要靠近。 快速齐射 —锋利而无情。 恐惧和恐慌会完成剩下的。 ";
				link.l1.go = "Exit";
			}
			else
			{
				link.l1 = "(用普通话) 就在这里。 他们一开始甚至不会看到我。 最好的战斗是那些没有开始的... 或者以很少流血迅速结束的。 ";
				link.l1.go = "Exit";
			}
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_Batavia_PlantationFight");
		break;
		
		case "PZ_Batavia_PlantationDimen1":
			if (!CharacterIsAlive("PZ_SoldPlantation_1") && !CharacterIsAlive("PZ_SoldPlantation_2") &&  !CharacterIsAlive("PZ_SoldPlantation_3") && !CharacterIsAlive("PZ_SoldPlantation_4") && !CharacterIsAlive("PZ_SoldPlantation_5") && !CharacterIsAlive("PZ_SoldPlantation_6"))
			{
				dialog.text = "讨厌的畜生... 逃奴, 是吗? 你怎么得到这样的武器? 有人雇你... ? ";
				link.l1 = "没时间了! 告诉我奥利维罗.费门特洛斯在哪里 —现在! ";
				link.l1.go = "PZ_Batavia_PlantationDimen2";
			}
			else
			{
				dialog.text = RandSwear()+"";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_PlantationDimenSit");
			}
		break;
		
		case "PZ_Batavia_PlantationDimen2":
			dialog.text = "呵呵, 有趣... 没时间了 —血从我的肚子里涌出来。 在地狱里燃烧吧, 异教徒... ";
			link.l1 = "(用普通话) 不!!! ";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_Batavia_PlantationDimenDead1");
		break;
		
		case "PZ_Batavia_Plantation_DimenDeadSelfDialog":
			dialog.text = "(用普通话) 为什么, 为什么, 为什么? ! 我现在怎么找费门特洛斯? ! ";
			link.l1 = "但首先, 我需要隐藏 —一定有人已经报告了这场屠杀... ";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_final";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_1":
			dialog.text = " 嗝! 一个中国人! 我没想到像你这样的人会被邀请到这里。 喜欢看, 嗯? 呵呵。 ";
			link.l1 = "为什么这里有这么多人... ? 你是谁? ";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_2";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_2":
			dialog.text = "你不通过我的衣服认出我吗? 和我说话时注意语气! 嗝! ";
			link.l1 = "那么, 你一定是范.迪门先生。 抱歉我的无知。 这里在举行狂欢节吗? ";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_3";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_3":
			dialog.text = "没错, 我的好人, 没有其他方式! 变装狂欢节! 哈哈哈! 不错, 农民! 我肯定卢瑟斯会很乐意穿维特的裙子, 哈哈哈! ";
			link.l1 = "卢瑟斯? ..";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_4";
			locCameraFromToPos(-4.45, 2.11, 1.53, true, 0.47, -0.30, 2.74);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_4":
			dialog.text = "那个可怜的丈夫借口, 喜欢从衣柜里偷看, 而他亲爱的妻子正在被上床。 她不介意! ";
			link.l1 = "";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_4_1";
			sld = CharacterFromID("PZ_Rubbe");
			CharacterTurnByChr(npchar, sld);
			CharacterTurnByChr(pchar, sld);
			CharacterTurnByChr(CharacterFromID("PZ_Brigitta"), sld);
			DoQuestCheckDelay("PZ_Batavia_BitvaLubovnitsa_4", 2.5);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_4_1":
			Event("QuestDelayExit","sl", "", 0);
			dialog.text = "对, 维特, 亲爱的? 嘿嘿。 ";
			link.l1 = "(用普通话) 这里到底发生了什么... ";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_5";
			sld = CharacterFromID("PZ_Rubbe");
			CharacterTurnByChr(npchar, CharacterFromID("PZ_Brigitta"));
			CharacterTurnByChr(pchar, npchar);
			CharacterTurnByChr(CharacterFromID("PZ_Brigitta"), npchar);
			locCameraFromToPos(-2.21, 1.90, 2.26, true, -0.81, -0.40, 4.36);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_5":
			dialog.text = " 嗝! 我不知道你刚才说什么, 但从你眼里的神情和语气, 你同意我的看法! 范.哈恩是个该死的变态。 所以, 你到底是什么人? 劳工? 维特邀请你了? ";
			link.l1 = "我... ";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_6";
			CharacterTurnByChr(pchar, npchar);
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(CharacterFromID("PZ_Brigitta"), pchar);
			locCameraFromToPos(-4.45, 2.11, 1.53, true, 0.47, -0.30, 2.74);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_6":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_Sepp");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaLubovnitsa_7";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_7":
			dialog.text = "在这里邀请劳工太过分了, 即使是维特。 他显然迷路了, 走错了地方。 嘿, 你。 离开这里, 忘记你所看到的一切。 你的主人是谁? 我们会联系他, 你们俩都会因为沉默而得到报酬。 你甚至可能被允许回到大陆的家人身边。 回答我然后离开。 ";
			link.l1 = "实际上, 我是来谈事务的。 ";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_8";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_8":
			dialog.text = "呵呵, 事务。 只有范.迪门先生在这里做'事务'。 我的工作是保护他免受你这样的人伤害。 而卢瑟斯... 就是卢瑟斯。 或者... 维特真的邀请你到这里了? ";
			link.l1 = "不, 我是来... ";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_9";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_9":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_Rubbe");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaLubovnitsa_10";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_10":
			dialog.text = "我最亲爱的维特真的会邀请一个黄屁股到这里吗? ! 滚出去!!! ";
			link.l1 = "可怜的戴绿帽的... ";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_11";
			link.l2 = "没人和你说话。 闭上你的嘴。 别假装你有胆子或尊严。 ";
			link.l2.go = "PZ_Batavia_BitvaLubovnitsa_12";
			GiveItem2Character(npchar, "blade_06");
			EquipCharacterByItem(npchar, "blade_06");
			LAi_SetActorType(npchar);
			npchar.model.animation = "man";
			Characters_RefreshModel(npchar);
			SetCameraDialogMode(npchar);
			locCameraToPos(-1.88, 1.72, 0.27, false);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_11":
			dialog.text = "绿... 绿... 绿帽? ! 不, 我爱她胜过爱自己。 哈, 像你这样的愚蠢中国人不会明白的! ";
			link.l1 = "(用普通话) 病态的混蛋。 ";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_13";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_12":
			dialog.text = "鸡... 鸡... 鸡巴? ! 它很好! 是的! 我只知道其他男人给我亲爱的维特更多快乐, 就这样! ";
			link.l1 = "正如我们家乡所说, 男人直到只剩下一根手指时仍然是男人。 如果你是男人, 你就会明白。 ";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_13";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_13":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_Brigitta");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaLubovnitsa_14";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_14":
			dialog.text = "当然, 我没邀请他, 不过你知道吗, 他挺不错的。 等你们都走了他说不定会留下来。 我已经和我们的狗试过了, 但还没和... ";
			link.l1 = "闭嘴, 男人说话时别插嘴, 婊子! 这里只有你是畜生。 我来谈正事。 我在找奥利维罗.费门特洛斯。 你们一定是他的朋友。 范.迪门先生, 能否请你告诉我他可能在哪里? ";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_15";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_15":
			dialog.text = "安东, 他侮辱我! 侮辱我! 你不会就这么算了吧? ! ";
			link.l1 = "... ";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_16";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_16":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_AntoniOneDimen");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaLubovnitsa_17";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_17":
			dialog.text = "呵呵, 抱歉, 伙计, 但这位女士生气了。 我得给你上堂礼仪课。 第一课。 ";
			link.l1 = "但你能帮我找奥利维罗吗? ";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_18";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_18":
			dialog.text = "这对一个将死的劳工没帮助。 ";
			link.l1 = "(用普通话) 你们都该死... ";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_19";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_19":
			DialogExit();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = false;
			
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetFightMode(pchar, true);
			PlaySound("Voice\Russian\hambit\Longway-02.wav");
			
			sld = CharacterFromID("PZ_AntoniOneDimen");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			sld = CharacterFromID("PZ_Sepp");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			sld = CharacterFromID("PZ_Rubbe");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_Batavia_BitvaLubovnitsa_3");
			
			sld = CharacterFromID("PZ_Brigitta");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			PlaySound("People Fight\Peace_woman_death_05.wav");
			DoQuestCheckDelay("PZ_Batavia_BitvaLubovnitsa_5", 3.0);    //需要再一次, 否则不跑
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_21":
			dialog.text = "(用普通话) 该死! 我什么都没问到! ";
			link.l1 = "(用普通话) 我永远不会忘记这一天... 我得在卫兵到来前离开这里。 不过他们大概也不会在意这疯人院里的动静... ";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_final";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_14":
			dialog.text = "(用普通话) 诸神诅咒这一天! 我在对付范.迪门的走狗时, 他流血而死了... ! ";
			link.l1 = "(用普通话) 卫兵要来了。 我得杀出一条路出去。 ";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_final";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_final":
			DialogExit();
			RemoveCharacterEquip(PChar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(PChar, MUSKET_ITEM_TYPE);
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_resedinsia_Go"))
			{
				TakeItemFromCharacter(pchar, "blade_30");
				TakeItemFromCharacter(pchar, "pistol2");
			}
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_lubovnitsa_Go"))
			{
				TakeItemFromCharacter(pchar, "blade_26");
				TakeItemFromCharacter(pchar, "pistol8");
			}
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_Plantation_Go"))
			{
				TakeItemFromCharacter(pchar, "mushket6");
				TakeItemFromCharacter(pchar, "mushket2x2");
			}
			EquipCharacterByItem(Pchar, "blade_11");
			pchar.model = "Longway";
			pchar.model.animation = "Longway";
			Characters_RefreshModel(pchar);
			
			
			SetCurrentTime(2, 30);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("福尔摩沙,"+ NewStr() +"1645年7月26日。 ", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Formosa", "goto", "goto7", "PZ_Formosa2_Start");
			LaunchFrameForm();
		break;
		
		case "PZ_Formosa_smuggler_21":
			dialog.text = "哦, 是张张! 你这次需要什么帮助, 我的小朋友? ";
			link.l1 = "我叫张图... 你什么意思? ";
			link.l1.go = "PZ_Formosa_smuggler_22";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Formosa_smuggler_22":
			dialog.text = "你很看不起我, 是吗? 你不会来这里除非需要什么。 ";
			link.l1 = "你知道范.默登在哪里吗? 他在镇上吗? 他不在家。 我需要和他谈谈。 ";
			link.l1.go = "PZ_Formosa_smuggler_23";
		break;
		
		case "PZ_Formosa_smuggler_23":
			dialog.text = "不能指望一个人整天待在家里, 等着一个黄皮肤的人出现。 他在岛上有生意。 今晚就会回镇上, 所以别担心, 张张! ";
			link.l1 = "谢谢。 再见。 ";
			link.l1.go = "PZ_Formosa_smuggler_24";
		break;
		
		case "PZ_Formosa_smuggler_24":
			SetCurrentTime(1, 30);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			DoQuestReloadToLocation("Formosa", "goto", "goto7", "PZ_Formosa2_IshemMerden_3");
		break;
		
		case "PZ_Formosa_bandit_1":
			dialog.text = "嘿, 窄眼! 这么急干什么? 这个时候体面人都睡了。 ";
			link.l1 = "那你呢? ";
			link.l1.go = "PZ_Formosa_bandit_2";
		break;
		
		case "PZ_Formosa_bandit_2":
			dialog.text = "说得好! 我们在巡逻! 听说有个小黄家伙在镇上窥探, 打扰敬畏上帝的人。 ";
			link.l1 = "请问那可能是谁? ";
			link.l1.go = "PZ_Formosa_bandit_3";
		break;
		
		case "PZ_Formosa_bandit_3":
			dialog.text = "够了, 别说了 —天晚了, 我开始犯困了。 ";
			link.l1 = "很快你就会永远睡去。 ";
			link.l1.go = "PZ_Formosa_bandit_4";
		break;
		
		case "PZ_Formosa_bandit_4":
			DialogExit();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = false;
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("PZ_JohanVanMerden");
			ChangeCharacterAddressGroup(sld, PChar.location, "patrol", "patrol7");
			GiveItem2Character(sld, "blade_31");
			EquipCharacterByItem(sld, "blade_31");
			LAi_SetActorType(sld);
			
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("PZ_FormosaBandit_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_Formosa2_IshemMerden_7");
			
			DoQuestCheckDelay("PZ_Formosa2_IshemMerden_6", 10.0);
		break;
		
		case "PZ_Formosa_JohanVanMerden_21":
			dialog.text = "张图, 你没事吧? ";
			link.l1 = "范.默登先生! 我没事, 多亏了你的干预。 你没事吧? 这是最重要的问题。 ";
			link.l1.go = "PZ_Formosa_JohanVanMerden_22";
		break;
		
		case "PZ_Formosa_JohanVanMerden_22":
			dialog.text = "总是为别人着想, 不是吗? 我们有共同的特质。 看到他们攻击你时我不能袖手旁观, 尽管我知道你能应付。 回答你的问题, 我没事, 只是有点累。 腿有点发抖。 如果你不介意, 我们进去吧。 可以在那里谈。 ";
			link.l1 = "当然, 范.默登先生, 这毕竟是你的房子。 ";
			link.l1.go = "PZ_Formosa_JohanVanMerden_23";
		break;
		
		case "PZ_Formosa_JohanVanMerden_23":
			DoQuestReloadToLocation("Formosa_houseSp1", "goto", "goto1", "PZ_Formosa2_IshemMerden_8");
		break;
		
		case "PZ_Formosa_JohanVanMerden_24":
			dialog.text = "现在我们可以不慌不忙。 安静地谈谈了。 告诉我, 张图, 你为什么来找我? ";
			link.l1 = "你说得对, 范.默登先生。 我刚从巴达维亚回来, 并且... ";
			link.l1.go = "PZ_Formosa_JohanVanMerden_25";
		break;
		
		case "PZ_Formosa_JohanVanMerden_25":
			dialog.text = "等等。 是可怜的常兴吗... ? ";
			link.l1 = "不, 完全不是! 希望不是。 上天仍对我隐瞒她的命运。 至于费门特洛斯... 他不在巴达维亚。 范.迪门没帮上忙。 ";
			link.l1.go = "PZ_Formosa_JohanVanMerden_26";
		break;
		
		case "PZ_Formosa_JohanVanMerden_26":
			dialog.text = "他不会帮忙的, 因为他和奥利维罗是老朋友。 正如英国人所说, 是犯罪的朋友和伙伴。 如果他给你任何有用的东西, 我会惊讶。 ";
			link.l1 = "是的, 多亏了你和特鲁斯特, 我获得了强大的武器。 我攻击范.迪门是为了审问他, 找出费门特洛斯在哪里。 但他在我得知任何信息前就死了... ";
			link.l1.go = "PZ_Formosa_JohanVanMerden_28";
		break;
		
		case "PZ_Formosa_JohanVanMerden_28":
			dialog.text = "令人印象深刻。 你已经意识到人们不总是愿意分享所知。 所以还有其他... 可以说是说服的方法。 我以为你可能得知了你妹妹的死讯, 所以才暴怒。 但你现在为什么来找我? 我告诉过你, 除了他偶尔访问巴达维亚, 我不知道费门特洛斯去哪里。 随着范.迪门的死, 最后一条线索也断了。 ";
			link.l1 = "但你知道很多事和很多人。 我想你可能会再次帮忙, 也许像以前一样四处打听费门特洛斯的消息。 你是第一个对我好的白人。 第一个... 白人朋友。 ";
			link.l1.go = "PZ_Formosa_JohanVanMerden_29";
		break;
		
		case "PZ_Formosa_JohanVanMerden_29":
			dialog.text = "这... 很感人。 ";
			link.l1 = "范.默登先生, 你为什么笑... ? ";
			link.l1.go = "PZ_Formosa_JohanVanMerden_30";
		break;
		
		case "PZ_Formosa_JohanVanMerden_30":
			dialog.text = "嗯? 哦, 抱歉, 张图。 我老了, 随着年龄增长变得多愁善感。 这是真诚的微笑 —我无法隐藏。 我很高兴你把我当作朋友。 既然我们是朋友, 我也希望你时不时帮我一下。 作为回报, 我肯定会帮你找费门特洛斯。 别担心 —你不会落入陷阱。 ";
			link.l1 = "嗯, 怎么帮你? ";
			link.l1.go = "PZ_Formosa_JohanVanMerden_31";
		break;
		
		case "PZ_Formosa_JohanVanMerden_31":
			dialog.text = "自从我们上次见面后, 我加深了对你的语言和文化的研究, 尤其是医学。 我希望你时不时帮我找一些 relic plaques。 我会像其他工作一样慷慨付钱给你。 我希望我们能偶尔用中文练习对话。 我不好意思问我的仆人, 但朋友... ";
			link.l1 = "张图会尽力, 范.默登先生。 ";
			link.l1.go = "PZ_Formosa_JohanVanMerden_32";
		break;
		
		case "PZ_Formosa_JohanVanMerden_32":
			dialog.text = "好。 你和我前方有很长的路, 我的朋友。 一条长路。 哈! 我觉得这对你来说是个好的掩护名字。 这是我行业的有用实践。 荷兰语中是'Lange Afstand'。 英语说是'Long Way'。 你更喜欢哪个? ";
			link.l1 = "我更喜欢英语版本。 Long。 Way。 Longway。 在我的语言中听起来很合适。 谢谢你倾听, 范.默登先生。 朗威会等待你的指示, 准备好协助你并完成你的请求。 ";
			link.l1.go = "PZ_Formosa_JohanVanMerden_33";
		break;
		
		case "PZ_Formosa_JohanVanMerden_33":
			DialogExit();
			
			SetCurrentTime(15, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			DeleteAttribute(pchar, "questTemp.lockedMusic");
			
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			
			bQuestDisableMapEnter = true;
			pchar.GenQuest.CabinLock = true;
			QuestToSeaLogin_Launch();
			QuestToSeaLogin_PrepareLoc("Guadeloupe", "Quest_Ships", "Quest_ship_8", false);
			DoQuestCheckDelay("PZ_SegodnyaVremya_2", 5.0);
		break;
		
		// 阶段3, 追踪星星
		case "PZ_Longway_PosleRasskaza":
			dialog.text = "说到档案, 船长阁下, 你带在身上吗? 这是我需要的全部 —我熟记密码。 ";
			if (CheckCharacterItem(pchar, "MerdokArchive"))
			{
				notification("所有技能+", "Longway");
				AddCharacterExpToSkill(npchar, "Leadership", 50);
				AddCharacterExpToSkill(npchar, "FencingL", 50);
				AddCharacterExpToSkill(npchar, "FencingS", 50);
				AddCharacterExpToSkill(npchar, "FencingH", 50);
				AddCharacterExpToSkill(npchar, "Pistol", 50);
				AddCharacterExpToSkill(npchar, "Fortune", 50);
				AddCharacterExpToSkill(npchar, "Sneak", 50);
				AddCharacterExpToSkill(npchar, "Sailing", 50);
				AddCharacterExpToSkill(npchar, "Accuracy", 50);
				AddCharacterExpToSkill(npchar, "Cannons", 50);
				AddCharacterExpToSkill(npchar, "Grappling", 50);
				AddCharacterExpToSkill(npchar, "Defence", 50);
				AddCharacterExpToSkill(npchar, "Repair", 50);
				AddCharacterExpToSkill(npchar, "Commerce", 50);    
				
				link.l1 = "是的, 我留着, 想着有一天可能有用。 ";
				link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_1";
			}
			else
			{
				link.l1 = "不幸的是, 没有。 这是你寻找妹妹的最后希望吗? ";
				link.l1.go = "PZ_Longway_PosleRasskaza_2";
			}
		break;
		
		case "PZ_Longway_PosleRasskaza_2":
			dialog.text = "朗威很高兴船长先生关心。 目前还有希望。 我在瓜德罗普找到新线索。 ";
			link.l1 = "那好。 告诉我你在那里发生了什么。 ";
			link.l1.go = "PZ_Longway_PosleRasskaza_3";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_1":
			dialog.text = "那是明智的决定。 也许我们能在里面找到帮助我们寻找常兴的东西。 ";
			link.l1 = "那太好了。 我们现在就研究它。 ";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_2";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_2":
			dialog.text = "是的, 我们一起研究。 年份是... 1637年。 安东.范.迪门出售... 出售... ";
			link.l1 = "奴隶, 对吗? ";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_3";
			AddQuestRecordInfo("PZ_ArchiveOneMerden", "1");
			RemoveItems(PChar, "MerdokArchive", 1);
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_3":
			dialog.text = "我的族人女性, 卖给富有的白人。 ";
			link.l1 = "太可怕了。 ";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_4";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_4":
			dialog.text = "船长阁下, 你似乎不惊讶。 那些女性的命运一点也不困扰你吗? ";
			link.l1 = "朗威, 当然真诚地困扰我。 我从内部见过这种肮脏。 但我一直是女性的倡导者... 老实说, 还是个有点风流的人。 你杀了范.迪门很好; 他罪有应得。 还有其他吗? ";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_5";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_5":
			dialog.text = "范.迪门只和他完全信任的人合作 —他的得力助手乔普.范德温克, 以及那个该死的奥利维罗.费门特洛斯。 还有... 还有... ";
			link.l1 = "怎么了? 你脸色苍白, 朗威。 ";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_6";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_6":
			dialog.text = "约翰.范.默登... ";
			link.l1 = "我很抱歉。 那很糟糕, 但你为什么如此震惊? 之前你说撕下了所有提到费门特洛斯的页面。 那时没发现范.默登的提及吗? ";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_7";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_7":
			dialog.text = "朗威当时很匆忙, 一定错过了这个重要部分。 ";
			link.l1 = "我明白。 当你准备好时, 我们继续寻找现在能用的任何东西。 ";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_8";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_8":
			dialog.text = "上面写着费门特洛斯会派他的人抓捕女性, 替换她们并销毁记录。 然后默登会把她们送到巴达维亚, 范德温克和范.迪门在那里把我们的女性卖给白人。 要是我早点知道就好了... ";
			link.l1 = "所以, 最终他们都一起工作。 别责怪自己, 朗威。 你不可能知道。 档案最近才到你手中。 还有其他吗? ";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_9";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_9":
			dialog.text = "是的。 他们这样做了将近十年。 这么多女性失去了家庭。 荣誉和希望... 但后来费门特洛斯停止了与范.默登的合作。 这是他帮助我的唯一原因 —他只想摆脱前合伙人。 ";
			link.l1 = "这里还记录了他们肮脏勾当之余的其他细节吗? ";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_10";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_10":
			dialog.text = "更多范.默登的阴暗想法。 他发现范.迪门骗了他的钱。 所以, 他派我去巴达维亚, 希望我死在那里, 同时也希望我带范.迪门一起走。 ";
			link.l1 = "冷酷。 但也极其聪明。 ";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_11";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_11":
			dialog.text = "可能更糟。 是范.默登派那些暴徒去他家杀我。 他只是在意识到我可能自己打败他们时才介入帮忙。 ";
			link.l1 = "毫无疑问, 他都考虑到了。 ";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_12";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_12":
			dialog.text = "我活着回来后, 他一定以为我发现了他的真实目的并来复仇。 我们谈话时, 他把枪藏在桌子下瞄准我。 但后来我称他为我的第一个白人朋友... 他几乎笑出来... ";
			link.l1 = "那很糟糕, 朗威。 意识到我们视为朋友的人一直在背后嘲笑我们, 这是痛苦的事。 ";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_13";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_13":
			dialog.text = "朗威很久以前就知道了, 在到达这个群岛前不久。 我被葡萄牙人俘虏, 他们想绞死我。 罗登堡勋爵救了我的命。 ";
			link.l1 = "你就是这样为他服务的吗? 卢卡斯也在福尔摩沙? ";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_14";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_14":
			dialog.text = "是的, 没错。 不仅是他 —还有范.伯格。 范.默登告诉我是他建议罗登堡放过我。 但一段时间后, 朗威从一个不可靠的来源得知, 实际上是约翰派葡萄牙人追杀我。 我当时不信... 但现在我意识到可能是真的... ";
			link.l1 = "恶心。 ";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_15";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_15":
			dialog.text = "尽管如此, 那天我心中产生了怀疑。 所以当我得知船长阁下和范.默登对峙时, 朗威想起了你的善良, 站在了你的一边。 ";
			link.l1 = "那是正确的决定, 朗威。 呵呵, 原来一直以来, 你第一个真正的白人朋友是我。 ";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_16";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_16":
			dialog.text = "看来是这样, 船长阁下。 现在我明白了。 范.默登告诉我是他的朋友。 但实际上, 朗威对他来说不过是另一个劳工 —只是比大多数更有用。 \n就这样。 其他页面涉及账目, 以及范.伯格和罗登堡之间的业务细节。 ";
			link.l1 = "我明白了。 现在你该告诉我你在瓜德罗普做了什么。 ";
			link.l1.go = "PZ_Longway_PosleRasskaza_3";
		break;
		
		case "PZ_Longway_PosleRasskaza_3":
			dialog.text = "我在寻找晨星号。 其中一张撕下的档案页面说它最后出现在圣克里斯托弗附近。 ";
			link.l1 = "为什么在那里? 我们约定在瓜德罗普见面, 我在那里找到了你。 ";
			link.l1.go = "PZ_Longway_PosleRasskaza_4";
		break;
		
		case "PZ_Longway_PosleRasskaza_4":
			dialog.text = "因为圣克里斯托弗是乔治.格拉维尔的家, 他是范.默登的线人之一。 乔治认为我还在为约翰工作。 此外, 格拉维尔曾对范.默登犯下严重罪行。 而朗威帮助掩盖了它。 ";
			link.l1 = "那是什么罪行? ";
			link.l1.go = "PZ_Longway_PosleRasskaza_5";
		break;
		
		case "PZ_Longway_PosleRasskaza_5":
			dialog.text = "那不重要。 重要的是乔治欠朗威一笔债。 所以, 我去了格拉维尔担任助理牧师的教堂。 船长阁下准备好听下去了吗? 你似乎有点分心。 ";
			link.l1 = "抱歉, 我分心了。 是的, 当然, 继续, 朗威。 ";
			link.l1.go = "PZ_Longway_PosleRasskaza_6";
		break;
		
		case "PZ_Longway_PosleRasskaza_6":
			DialogExit();
			SetCurrentTime(9, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			SetMainCharacterIndex(GetCharacterIndex("Longway"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("卡普斯特维尔,"+ NewStr() +"圣克里斯托弗岛。 ", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Kapstervil", "patrol", "patrol12", "PZ_Kapstervil_Start");
			LaunchFrameForm();
		break;
		
		case "PZ_Zhorzh_1":
			dialog.text = "很好, 你没迟到。 你知道, 我不想在这里待得比必要更久! 这次你需要什么, 朗威? ";
			link.l1 = "改变你的语气, 格拉维尔。 组织需要你的服务。 ";
			link.l1.go = "PZ_Zhorzh_2";
		break;
		
		case "PZ_Zhorzh_2":
			dialog.text = "我必须承认, 我很久没有他们的消息了。 他们忘了我吗? ";
			link.l1 = "我可以提醒他们。 也许告诉范.默登先生你做了什么。 ";
			link.l1.go = "PZ_Zhorzh_3";
		break;
		
		case "PZ_Zhorzh_3":
			dialog.text = "好了, 好了, 没必要这么生气! 我能为你做什么? ";
			link.l1 = "我需要关于晨星号的信息。 你能找到的任何信息。 越多越好。 ";
			link.l1.go = "PZ_Zhorzh_4";
		break;
		
		case "PZ_Zhorzh_4":
			dialog.text = "当然, 但需要时间! 至少两天! ";
			link.l1 = "为什么这么久? ";
			link.l1.go = "PZ_Zhorzh_5";
		break;
		
		case "PZ_Zhorzh_5":
			dialog.text = "通常, 需要从奉献箱拿钱来让我的线人开口。 但我们最近被抢劫了! 当然, 神父会宣布新的捐款收集, 但我们仍然需要修理屋顶 —它在漏水! 需要很多捐款来修理。 ";
			link.l1 = "两天。 我不能永远待在这里。 我没有那种时间。 朗威不以耐心著称。 范.默登先生更不。 或者我该提醒你, 格拉维尔? ";
			link.l1.go = "PZ_Zhorzh_6";
		break;
		
		case "PZ_Zhorzh_6":
			dialog.text = "我无法控制无法触及的事情! 我会尽力。 不过, 如果你找到那些强盗并带回我们的捐款, 我会更快找到! ";
			link.l1 = "我会考虑的。 你开始搜索。 两天。 不能再多。 同一时间同一地点见面。 ";
			link.l1.go = "PZ_Zhorzh_7";
		break;
		
		case "PZ_Zhorzh_7":
			DialogExit(); 
			SetCurrentTime(12, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("一天后... "+ NewStr() +"寻找教堂抢劫者。 ", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Kapstervil_Jungle", "goto", "goto1", "PZ_Kapstervil_Jungle");
			LaunchFrameForm();
		break;
		
		case "PZ_VorugaChurch_1":
			dialog.text = "嗯, 看看! 我们岛上有个窄眼男人! 从主人那里逃跑了, 嗯? 你在躲谁, 如果你不介意问的话? ";
			link.l1 = "我是自由人。 ";
			link.l1.go = "PZ_VorugaChurch_2";
		break;
		
		case "PZ_VorugaChurch_2":
			dialog.text = "哈! 当然。 但你看起来强壮聪明, 即使眼睛有点斜。 想加入我们的帮派吗? 反正我觉得你无处可去。 ";
			link.l1 = "朗威认为你更感兴趣抢劫他而不是招募他。 ";
			link.l1.go = "PZ_VorugaChurch_3";
		break;
		
		case "PZ_VorugaChurch_3":
			dialog.text = "呵, 算你幸运。 我们最近抢劫了镇上的教堂, 你能相信吗? 为什么? 因为从小偷那里偷东西不算偷。 ";
			link.l1 = "我没打算追捕你, 但很高兴找到你。 ";
			link.l1.go = "PZ_VorugaChurch_4";
		break;
		
		case "PZ_VorugaChurch_4":
			dialog.text = "追捕我们? 啊, 所以你是雇佣兵, 不是逃跑的劳工。 那你倒霉了。 ";
			link.l1 = "正是。 ";
			link.l1.go = "PZ_VorugaChurch_5";
		break;
		
		case "PZ_VorugaChurch_5":
			DialogExit();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = false;
			
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			LAi_SetCheckMinHP(npchar, 1, true, "PZ_VorugaChurch_win");
			for (i=11; i<=14; i++)
			{
				sld = CharacterFromID("PZ_KapstervilBandit_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		break;
		
		case "PZ_VorugaChurch_6":
			if (!CharacterIsAlive("PZ_KapstervilBandit_11") && !CharacterIsAlive("PZ_KapstervilBandit_12") && !CharacterIsAlive("PZ_KapstervilBandit_13"))
			{
				dialog.text = "操... 你为什么不马上杀了我? 你想从我这里得到什么? 你要把我拖到监狱吗? ";
				link.l1 = "我对此没兴趣。 只要告诉我你把金子藏在哪里。 ";
				link.l1.go = "PZ_VorugaChurch_7";
			}
			else
			{
				dialog.text = RandSwear()+"";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_VorugaChurch_win");    
			}
		break;
		
		case "PZ_VorugaChurch_7":
			dialog.text = "呵... 你这个黄皮肤的混蛋... ";
			link.l1 = "朗威的耐心快耗尽了。 我反正会找到的。 唯一的问题是你会受多久的苦。 ";
			link.l1.go = "PZ_VorugaChurch_8";
			LAi_group_Delete("EnemyFight");
		break;
		
		case "PZ_VorugaChurch_8":
			dialog.text = "好吧, 好吧... 在一个山洞里。 所有东西都在那里。 钱是你的了。 只是... 只是别杀我, 好吗? ";
			link.l1 = "我没说不会有任何痛苦... ";
			link.l1.go = "PZ_VorugaChurch_9";
		break;
		
		case "PZ_VorugaChurch_9":
			DialogExit();
			
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "Shot", "1", 1.5);
			DoQuestCheckDelay("PZ_VorugaChurch_win_2", 0.9);
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_0":
			StartQuestMovie(true, false, true);
			locCameraFromToPos(2.48, 0.87, 9.26, true, 6.72, -0.85, 6.05);
			dialog.text = "(用普通话) 这是强盗的藏身处。 ";
			link.l1 = "";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_0_1";
			CharacterTurnToLoc(pchar, "box", "box1");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_0_1":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto2", "PZ_Kapstervil_Grot_1", -1);
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_1":
			dialog.text = "(用普通话) 好多啊! ";
			link.l1 = "";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_1_1";
			CharacterTurnToLoc(pchar, "box", "box1");
			locCameraFromToPos(6.83, 2.65, 6.62, true, 2.83, -1.00, 7.67);
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_1_1":
			dialog.text = "(用普通话) 我听到脚步声... ";
			link.l1 = "(用普通话) 还有人在这里... ";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_2";
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_2":
			DialogExit();
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_Kapstervil_GrotSoldier_1", "sold_fra_7", "man", "man", 5, FRANCE, -1, true, "soldier"));
			LAi_SetActorType(sld);
			sld.CantLoot = true;
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
			TeleportCharacterToPosAy(sld, 4.17, 0.65, -1.42, 0.00);
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_Kapstervil_GrotSoldier_2", "sold_fra_5", "man", "man", 5, FRANCE, -1, true, "soldier"));
			LAi_SetActorType(sld);
			sld.CantLoot = true;
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
			TeleportCharacterToPosAy(sld, 4.10, 0.65, 0.30, 3.00);
			
			LAi_SetStayType(pchar);
			LAi_Fade("PZ_Kapstervil_Grot_2", "");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_3":
			dialog.text = "我们到底在这里做什么? 已经没人了 —我们确保所有强盗都走了。 ";
			link.l1 = "";
			link.l1.go = "exit";
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("PZ_Kapstervil_GrotSoldier_2"));
			AddDialogExitQuest("PZ_Kapstervil_Grot_4");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_5":
			dialog.text = "重点就在这里, 蠢货! 他们会回来的, 我们会热烈欢迎他们。 ";
			link.l1 = "";
			link.l1.go = "exit";
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("PZ_Kapstervil_GrotSoldier_1"));
			AddDialogExitQuest("PZ_Kapstervil_Grot_5");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_7":
			dialog.text = "我会四处看看, 确保没人藏着。 反正我也无聊... ";
			link.l1 = "";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_8";
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("PZ_Kapstervil_GrotSoldier_2"));
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_8":
			DialogExit();
			LAi_Fade("PZ_Kapstervil_Grot_5_1", "");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_9":
			dialog.text = "(用普通话) 士兵! 真不幸... 我现在该怎么办? ";
			link.l1 = "(用普通话) 我比白人士兵更需要这笔钱! 我不会不带它离开! ";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_10";
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_10":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("PZ_Kapstervil_GrotSoldier_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyWithRadius");
				LAi_group_SetRelation("EnemyWithRadius", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
				LAi_group_SetLookRadius("EnemyWithRadius", 6.0);
				LAi_group_SetHearRadius("EnemyWithRadius", 2.0);
				LAi_group_SetSayRadius("EnemyWithRadius", 12.0);
				LAi_group_SetCheck("EnemyWithRadius", "PZ_Kapstervil_Grot_6");
			}
		break;
		
		case "PZ_Zhorzh_11":
			dialog.text = "啊, 朗威先生, 你回来了! ";
			link.l1 = "当然。 有什么疑问吗? 你找到晨星号的信息了吗, 乔治? ";
			link.l1.go = "PZ_Zhorzh_12";
		break;
		
		case "PZ_Zhorzh_12":
			dialog.text = "是的, 先生。 那是一艘重型帆船, 据说由一个西班牙人指挥... ";
			link.l1 = "他是葡萄牙人。 你们白人甚至分不清彼此。 ";
			link.l1.go = "PZ_Zhorzh_13";
		break;
		
		case "PZ_Zhorzh_13":
			dialog.text = "哦, 对。 我的错。 无论如何, 我发现他对帆船进行了大量改装, 试图将其伪装成商船, 配备小口径 cannons 和更少的船员。 但他扩大了货舱, 装满了货物 —重得几乎无法航行。 ";
			link.l1 = "所以他决定开始新生活。 很好。 现在, 我在哪里可以找到他? ";
			link.l1.go = "PZ_Zhorzh_14";
		break;
		
		case "PZ_Zhorzh_14":
			dialog.text = "那更棘手。 他在我们的殖民地和英国殖民地之间不断移动, 但只在向风群岛之间。 不过, 我得知他目前正带着大量葡萄酒前往巴斯特尔。 ";
			link.l1 = "我需要想办法尽快到达那里。 ";
			link.l1.go = "PZ_Zhorzh_15";
		break;
		
		case "PZ_Zhorzh_15":
			dialog.text = "那是你的事, 朗威先生。 我自己的问题已经够多了... 比如修理那个该死的屋顶。 ";
			link.l1 = "说到关心的事, 我找到了那些教堂抢劫者。 这是你的捐款。 修理屋顶 —你的上帝没有屋顶可不好。 ";
			link.l1.go = "PZ_Zhorzh_16";
		break;
		
		case "PZ_Zhorzh_16":
			dialog.text = "非常感谢你, 朗威先生! 我从没想过你会是做这件事的人。 ";
			link.l1 = "我也没想到。 但我得在那两天做点什么。 ";
			link.l1.go = "PZ_Zhorzh_17";
		break;
		
		case "PZ_Zhorzh_17":
			dialog.text = "那么, 你需要去瓜德罗普? 我会给你找一艘去那里的船。 期待很快收到我的消息! ";
			link.l1 = "那会有帮助。 谢谢你, 乔治。 ";
			link.l1.go = "PZ_Zhorzh_18";
		break;
		
		case "PZ_Zhorzh_18":
			DialogExit();
			SetCurrentTime(9, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = false;
			
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("第二天早上... "+ NewStr() +"卡普斯特维尔", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Kapstervil", "goto", "goto19", "PZ_Kapstervil_PoiskZvezda");
			LaunchFrameForm();
		break;
		
		case "PZ_Kapstervil_Kurier_1":
			dialog.text = "你一定是乔治的熟人? 他让我把这个给你。 ";
			link.l1 = "一张便条? 谢谢。 你怎么知道是给我的? ";
			link.l1.go = "PZ_Kapstervil_Kurier_2";
		break;
		
		case "PZ_Kapstervil_Kurier_2":
			dialog.text = "认真的? ";
			link.l1 = "哦, 对。 ";
			link.l1.go = "PZ_Kapstervil_Kurier_3";
		break;
		
		case "PZ_Kapstervil_Kurier_3":
			DialogExit();
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("PZ_Kapstervil_ChitaemPismo", 1.5);
		break;
		
		case "PZ_Kapstervil_ChitaemPismo_Dialog":
			dialog.text = "(读信) 朗威先生, ‘普罗旺斯'帆船明天早上出发前往巴斯特尔。 船长马蒂厄.特鲁尼可以在酒馆找到。 向范.默登先生问好。 - 乔治.格拉维尔。 ";
			link.l1 = "";
			link.l1.go = "PZ_Kapstervil_ChitaemPismo_Dialog_2";
		break;
		
		case "PZ_Kapstervil_ChitaemPismo_Dialog_2":
			DialogExit();
			LAi_RemoveCheckMinHP(pchar);
			chrDisableReloadToLocation = false;
			LAi_SetPlayerType(pchar);
			sld = characterFromId("PZ_Kapstervil_tavernkeeper");
			sld.dialog.currentnode = "PZ_TerunyiTavern1";
			LAi_SetBarmanType(sld);
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "PZ_TerunyiTavern1":
			dialog.text = "我们不在这里为你这种人提供饮料。 除非我想听到关于跳蚤的抱怨, 否则也不会租给你房间。 ";
			link.l1 = "我不需要饮料或房间。 而且... 朗威没有跳蚤。 ";
			link.l1.go = "PZ_TerunyiTavern2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_TerunyiTavern2":
			dialog.text = "我他妈怎么知道? 好吧, 说出来。 你想要什么? 然后出去。 ";
			link.l1 = "我会的。 我在找马蒂厄.特鲁尼船长。 我似乎找不到他。 你知道他在哪里吗? ";
			link.l1.go = "PZ_TerunyiTavern3";
		break;
		
		case "PZ_TerunyiTavern3":
			dialog.text = "他在当地商店忙着准备他的船启航。 那比和你这样的中国佬聊天重要得多, 但你显然不明白。 ";
			link.l1 = "实际上, 我曾经是... 没关系。 现在不重要。 ";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_CreateTerunyi");
		break;
		
		case "PZ_Terunyi1":
			dialog.text = "你想要什么, 中国佬? 没看见我在忙吗? 我需要准备我的船。 ";
			link.l1 = "马蒂厄.特鲁尼船长? ";
			link.l1.go = "PZ_Terunyi2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Terunyi2":
			dialog.text = "好吧, 这不再有趣了。 像你这样的人怎么知道我是谁? 有人派你来的? ";
			link.l1 = "不必担心。 我听说你要航行到巴斯特尔。 你能带我作为乘客吗? 我会付钱。 ";
			link.l1.go = "PZ_Terunyi3";
		break;
		
		case "PZ_Terunyi3":
			dialog.text = "这越来越好了。 我要去圣皮埃尔, 不是巴斯特尔, 但这是个短途绕行。 很好, 因为我不必让你在船上待得比必要更久。 五千比索。 我们三小时后出发。 在码头付款。 尽管我是商人, 但没有讨价还价。 明白了吗? ";
			link.l1 = "是的。 谢谢你。 码头见, 特鲁尼船长。 ";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TeleportToPier");
		break;
		
		case "PZ_Terunyi4":
			dialog.text = "你终究还是出现了, 中国佬。 我以为你不会来 —没人会自愿给你这种人真钱。 ";
			link.l1 = "五千比索, 正如你要求的。 你准备好启航了吗? ";
			link.l1.go = "PZ_Terunyi5";
		break;
		
		case "PZ_Terunyi5":
			AddMoneyToCharacter(pchar, -5000);
			
			dialog.text = "不, 不! 我应该问你才对。 但我认为你准备好了。 来吧。 你会划小艇。 别指望有合适的客舱! 你是我们绕行的唯一原因。 ";
			link.l1 = "我不需要舒适。 只要把我带到那里。 ";
			link.l1.go = "PZ_Terunyi6";
		break;
		
		case "PZ_Terunyi6":
			DialogExit();
			
			SetCurrentTime(2, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			InterfaceStates.Buttons.Save.enable = true;
			
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			
			QuestToSeaLogin_Launch();
			QuestToSeaLogin_PrepareLoc("Guadeloupe", "Quest_Ships", "Quest_ship_8", false);
			DoQuestCheckDelay("PZ_Flashback_Final_1", 3.5);
		break;
		
		case "PZ_Longway_PosleRasskaza21":
			dialog.text = "... 所以朗威无法确切弄清楚晨星号的去向。 ";
			link.l1 = "是啊, 我明白你怎么陷入那堆麻烦的。 ";
			link.l1.go = "PZ_Longway_PosleRasskaza22";
		break;
		
		case "PZ_Longway_PosleRasskaza22":
			if (GetCharacterIndex("Helena") != -1 && CheckPassengerInCharacter(pchar, "Helena")) sStr = "Helena";
			else sStr = "Alonso";
			dialog.text = "我在瓜德罗普水域看到一艘双桅船。 也许是班滕号。 我会试着查明。 好了, 你现在可以走了, 朗威。 把" + sStr + "带来。 ";
			link.l1.go = "PZ_Longway_PosleRasskaza23";
		break;
		
		case "PZ_Longway_PosleRasskaza23":
			DialogExit();
			LAi_SetStayType(pchar);
			LAi_FadeLong("PZ_LongwayUhoditIzKauty", "PZ_HelenaOrAlonso");
		break;
		
		case "PZ_Helena_1":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				dialog.text = "我的船长, 一切都好吗? 朗威一说你需要我, 我就来了。 ";
				link.l1 = "我只是在试图理清头绪。 你记得我们在岛外看到的那艘双桅船的名字吗? ";
				link.l1.go = "PZ_Helena_3";
			}
			else
			{
				dialog.text = "你想见我? ";
				link.l1 = "是的。 你记得最近我们看到的那艘双桅船吗? 查明它的位置和名字。 ";
				link.l1.go = "PZ_Helena_2";
			}
		break;
		
		case "PZ_Helena_2":
			dialog.text = "我记得, 但为什么突然对双桅船感兴趣? 查明可能需要一些时间。 ";
			link.l1 = "海伦, 求你就这么做吧。 是的, 我知道可能需要一段时间。 我会等。 ";
			link.l1.go = "PZ_PoiskBanten";
		break;
		
		case "PZ_Helena_3":
			dialog.text = "不, 我没查。 怎么了? 很重要吗? ";
			link.l1 = "嗯嗯。 你能多查些吗? 我需要知道他们现在锚泊在哪里, 如果还没离开瓜德罗普水域的话。 ";
			link.l1.go = "PZ_Helena_4";
		break;
		
		case "PZ_Helena_4":
			dialog.text = "当然可以。 只是提醒一下, 可能需要一段时间。 我会带小艇和几个伙计去帮忙, 好吗, 查尔斯? ";
			link.l1 = "当然, 海伦, 谢谢你。 我会等。 ";
			link.l1.go = "PZ_PoiskBanten";
		break;
		
		case "PZ_Alonso_11":
			dialog.text = "船长先生, 您叫我? ";
			link.l1 = "是的, 阿隆索。 我们回去接朗威时, 在岛外水域经过一艘双桅船。 你碰巧看到它的名字了吗? ";
			link.l1.go = "PZ_Alonso_12";
		break;
		
		case "PZ_Alonso_12":
			dialog.text = "没有, 我的工作是留意新兵并参与登船先锋队。 此外, 我没有望远镜, 而且我们离得没那么近。 ";
			link.l1 = "没错。 但我还是需要查明。 去办吧。 ";
			link.l1.go = "PZ_Alonso_13";
		break;
		
		case "PZ_Alonso_13":
			dialog.text = "是, 船长。 我想半天就能搞定。 ";
			link.l1 = "快点。 我会等。 ";
			link.l1.go = "PZ_PoiskBanten";
		break;
		
		case "PZ_PoiskBanten":
			DialogExit();
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			LAi_SetStayType(pchar);
			SetLaunchFrameFormParam("五小时后... ", "PZ_PoiskBanten_2", 0, 4.0);
			LaunchFrameForm();
			locCameraSleep(true);
		break;
		
		case "PZ_Helena_5":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				dialog.text = "我已经查明一切。 我不在时一切都好吗, 我的船长? ";
				link.l1 = "是的, 我很好, 谢谢你, 海伦。 告诉我。 ";
				link.l1.go = "PZ_Helena_7";
			}
			else
			{
				dialog.text = "呼, 我回来了。 我找到你要的双桅船了。 ";
				link.l1 = "欢迎回来。 它的位置和名字是什么? ";
				link.l1.go = "PZ_Helena_6";
			}
		break;
		
		case "PZ_Helena_6":
			dialog.text = "班滕号。 这个名字对你有意义, 对吧? 它现在在灯塔那里, 有几个船员上岸了。 我们要攻击那艘船吗? ";
			link.l1 = "不, 我们需要确切知道谁上岸了。 我们将从陆路前往灯塔。 考虑到我们已经延误了, 是时候离开港口了。 我们应该在偏远的地方锚泊。 卡普斯特海滩不错。 我们快点, 海伦。 ";
			link.l1.go = "PZ_BasTerMayak";
		break;
		
		case "PZ_Helena_7":
			dialog.text = "嗯, 那艘双桅船叫班滕号, 锚泊在灯塔处。 有些船员在那里上岸了。 你打算怎么做? ";
			link.l1 = "要查明的话, 我们得悄无声息地到达灯塔, 而这只能步行。 我们的船需要在安全的地方锚泊。 卡普斯特海滩怎么样? ";
			link.l1.go = "PZ_Helena_8";
		break;
		
		case "PZ_Helena_8":
			dialog.text = "好主意。 查尔斯, 你想让我和你一起去灯塔吗? ";
			link.l1 = "我在移船时会考虑的 —你已经够累了。 ";
			link.l1.go = "PZ_BasTerMayak";
		break;
		
		case "PZ_Alonso_15":
			dialog.text = "我一做完就回来了, 船长先生。 ";
			link.l1 = "很好。 报告吧, 阿隆索。 ";
			link.l1.go = "PZ_Alonso_16";
		break;
		
		case "PZ_Alonso_16":
			dialog.text = "那艘双桅船还在岛外 —准确地说在灯塔那里。 船尾的名字是班滕号。 他们有几个船员上岸了。 ";
			link.l1 = "干得好, 阿隆索。 让船员立即准备起锚。 ";
			link.l1.go = "PZ_Alonso_17";
		break;
		
		case "PZ_Alonso_17":
			dialog.text = "也准备登船吗? ";
			link.l1 = "还没。 如果他们的船长前往灯塔, 我们在海上攻击的话, 他可能会躲进城里。 我们先去卡普斯特海滩确保船的安全, 然后步行接近灯塔。 ";
			link.l1.go = "PZ_BasTerMayak";
		break;
		
		case "PZ_BasTerMayak":
			DialogExit();
			locCameraSleep(false);
			LAi_SetPlayerType(pchar);
			ChangeCharacterAddressGroup(npchar, "none", "", "");
			chrDisableReloadToLocation = false;
			bDisableCharacterMenu = false;
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			Island_SetReloadEnableGlobal("Guadeloupe", true);
			
			AddQuestRecord("PZ", "15");
			PChar.quest.PZ_Banten_PlyazhKapster.win_condition.l1 = "location";
			PChar.quest.PZ_Banten_PlyazhKapster.win_condition.l1.location = "Shore29";
			PChar.quest.PZ_Banten_PlyazhKapster.win_condition = "PZ_Banten_PlyazhKapster";
			
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1 = "Timer";
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1.date.hour = sti(GetTime() + 7);
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1.date.day = GetAddingDataDay(0, 0, 0);
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1.date.year = GetAddingDataYear(0, 0, 0);
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition = "PZ_Banten_PlyazhKapster_Proval";
			
			if (GetCharacterIndex("Helena") != -1 && CheckPassengerInCharacter(pchar, "Helena"))
			{
				LAi_SetActorType(npchar);
				LAi_ActorFollow(npchar, pchar, "", -1);
				LAi_SetOfficerType(npchar);
				npchar.Dialog.Filename = "Quest\Saga\Helena.c";
				npchar.Dialog.CurrentNode = "Helena_officer";
			}
		break;
		
		case "PZ_Longway_21":
			dialog.text = "船长阁下, 看! 灯塔里面有人。 ";
			link.l1 = "好, 我们及时赶到了! 赶紧去抓他们。 阿隆索今天有很多活要干了。 ";
			link.l1.go = "PZ_Longway_22";
		break;
		
		case "PZ_Longway_22":
			dialog.text = "但如果他们在这过程中死了怎么办? ";
			link.l1 = "你有什么建议? ";
			link.l1.go = "PZ_Longway_23";
		break;
		
		case "PZ_Longway_23":
			dialog.text = "我们悄悄潜入, 先偷听他们的对话。 ";
			link.l1 = "我怀疑不被窗口看到的话很难做到。 但我们试试吧。 ";
			link.l1.go = "PZ_Longway_24";
		break;
		
		case "PZ_Longway_24":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			npchar.Dialog.CurrentNode = "Longway_officer";
			LAi_SetCheckMinHP(npchar, 1, true, "HiddenImmortality");
			PChar.quest.PZ_MayakPodslushivanie.win_condition.l1 = "locator";
			PChar.quest.PZ_MayakPodslushivanie.win_condition.l1.location = "Mayak4";
			PChar.quest.PZ_MayakPodslushivanie.win_condition.l1.locator_group = "goto";
			PChar.quest.PZ_MayakPodslushivanie.win_condition.l1.locator = "goto31";
			PChar.quest.PZ_MayakPodslushivanie.win_condition = "PZ_MayakPodslushivanie";
		break;
		
		case "PZ_MayakPodslushivanie_Dialog_1":
			dialog.text = "想想我说的话。 好好想想。 钱不是问题 —当然在一定限度内。 但即使是那个限度, 对你来说也会像一座金山 —那个中国人必须死! 我以前派人追过他, 但都没用。 不过这次, 如果他们和你的人合作... ";
			link.l1 = "";
			link.l1.go = "PZ_MayakPodslushivanie_Dialog_1_1";
			CharacterTurnByChr(npchar, CharacterFromID("PZ_BasTerJailOff_Clone"));
		break;
		
		case "PZ_MayakPodslushivanie_Dialog_1_1":
			StartInstantDialog("PZ_BasTerJailOff_Clone", "PZ_MayakPodslushivanie_Dialog_2", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_MayakPodslushivanie_Dialog_2":
			dialog.text = "看, 我们被监视了! 是他! 他和他该死的船长! ";
			link.l1 = "";
			link.l1.go = "PZ_MayakPodslushivanie_Dialog_3";
			CharacterTurnToLoc(npchar, "item", "flower5");
		break;
		
		case "PZ_MayakPodslushivanie_Dialog_3":
			DialogExit();
			EndQuestMovie();
			locCameraSleep(false);
			locCameraToPos(1.52, 18.87, -9.55, true);
			DoQuestCheckDelay("CameraReset", 1.0);
			DeleteAttribute(pchar, "questTemp.NoFast");
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("PZ_Neznakomets");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			
			sld = CharacterFromID("PZ_BasTerJailOff_Clone");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetCheckMinHP(sld, 1, true, "PZ_MayakPodslushivanie_win");
			
			for (i=1; i<=4; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("PZ_Neznakomets_Bandit_"+i, "citiz_" + (rand(9) + 41), "man", "man", sti(pchar.rank), PIRATE, -1, true, "pirate"));
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload2");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		break;
		
		case "PZ_Mayak_KomendantSidit_1":
			if (!CharacterIsAlive("PZ_Neznakomets_Bandit_1") && !CharacterIsAlive("PZ_Neznakomets_Bandit_2") && !CharacterIsAlive("PZ_Neznakomets_Bandit_3")&& !CharacterIsAlive("PZ_Neznakomets_Bandit_4"))
			{
				dialog.text = "该死的, 肮脏的亚洲人... 因为你, 我受了这么多苦。 而现在, 为此, 我就要死了... ";
				link.l1 = "我们会带你去见我们的医生, 指挥官阁下。 只要告诉我们你在和谁说话 —这很重要。 ";
				link.l1.go = "PZ_Mayak_KomendantSidit_2";
				LAi_group_Delete("EnemyFight");
			}
			else
			{
				dialog.text = RandSwear()+"";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_MayakPodslushivanie_win");	
			}
		break;
		
		case "PZ_Mayak_KomendantSidit_2":
			dialog.text = "他的名字... 是乔普.范德温克, 他... 哈... ";
			link.l1 = "... ";
			link.l1.go = "PZ_Mayak_KomendantSidit_3";
		break;
		
		case "PZ_Mayak_KomendantSidit_3":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_KillCharacter(npchar);
			DoQuestCheckDelay("PZ_Mayak_Longway", 1.5);
		break;
		
		case "PZ_Longway_25":
			dialog.text = "";
			link.l1 = "他死了... 好吧, 至少我们知道了名字。 朗威... ? ";
			link.l1.go = "PZ_Longway_26";
		break;
		
		case "PZ_Longway_26":
			dialog.text = "那绝对不可能... ";
			link.l1 = "你脸色有点苍白, 朗威。 ";
			link.l1.go = "PZ_Longway_27";
		break;
		
		case "PZ_Longway_27":
			dialog.text = "朗威很确定他十年前就杀了范德温克\n他们要跑了! 他们的船很快! ";
			link.l1 = "是的, 一艘奇妙的双桅船... 可惜对我们来说。 即使我们及时到达我们的船, 等我们升起帆乘风追赶时, 他们也已经走了。 ";
			link.l1.go = "PZ_Longway_28";
		break;
		
		case "PZ_Longway_28":
			dialog.text = "这可能是结束... ";
			link.l1 = "不, 朗威。 听我说。 如果他们计划留在群岛, 我们迟早会遇到他们 —世界很小, 加勒比海尤其如此。 一旦我们再次找到他们的踪迹, 我会放下一切去追他们。 我向你保证。 听到了吗? ";
			link.l1.go = "PZ_Longway_29";
		break;
		
		case "PZ_Longway_29":
			dialog.text = "是的, 船长阁下。 谢谢你。 ";
			link.l1 = "振作起来, 朗威。 我们得赶紧回船 —指挥官的死很快就会成为大新闻。 ";
			link.l1.go = "PZ_Longway_30";
		break;
		
		case "PZ_Longway_30":
			DialogExit();
			
			ReturnOfficer_Longway();
			LAi_RemoveCheckMinHP(npchar);
			AddQuestRecord("PZ", "17");
			sld = &Locations[FindLocation("Mayak4")];
			sld.locators_radius.goto.goto31 = 0.5;
			
			chrDisableReloadToLocation = false;
			QuestOpenSeaExit();
			
			pchar.questTemp.PZ_Etap4_Start = true;
		break;
		
		// 阶段4, 欺骗之星
		case "PZ_PoterpKrushenie_1":
			dialog.text = "先生! 等一下! 你是船长吗? ";
			link.l1 = "也许吧。 你怎么猜到的? 你想要什么? ";
			link.l1.go = "PZ_PoterpKrushenie_2";
		break;
		
		case "PZ_PoterpKrushenie_2":
			dialog.text = "嗯, 这周围除了山和茂密的丛林什么都没有 —没有通往城市的路。 然而, 你在这里。 你不只是观光, 对吧? ";
			link.l1 = "观察力不错。 但你还没告诉我你想要什么。 ";
			link.l1.go = "PZ_PoterpKrushenie_3";
		break;
		
		case "PZ_PoterpKrushenie_3":
			dialog.text = "啊, 对! 船长, 我们的船在这个海湾外触礁了。 我们是唯一幸存的... ";
			link.l1 = "我很遗憾。 你想让我带你们去某个地方, 是吗? ";
			link.l1.go = "PZ_PoterpKrushenie_4";
		break;
		
		case "PZ_PoterpKrushenie_4":
			dialog.text = "是的... 我发誓我们不会惹麻烦。 把我们送到伯利兹, 我们从那里就能应付了。 ";
			link.l1 = "不远, 是吗? 那样的话, 欢迎登船。 ";
			link.l1.go = "PZ_PoterpKrushenie_5";
			link.l2 = "抱歉, 但我要往反方向走。 ";
			link.l2.go = "PZ_PoterpKrushenie_7";
		break;
		
		case "PZ_PoterpKrushenie_5":
			dialog.text = "谢谢你, 船长! 没有你, 我们不知道要被困多久。 ";
			link.l1 = "的确。 我们别浪费时间了! ";
			link.l1.go = "PZ_PoterpKrushenie_6";
		break;
		
		case "PZ_PoterpKrushenie_6":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			DeleteAttribute(&locations[FindLocation("Shore9")], "DisableEncounters");
			
			for (i=1; i<=6; i++)
			{
				sld = CharacterFromID("PZ_PoterpKrushenie_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "sea", "", "", "", "", -1);
				sld.location = "None";
			}
			
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition.l1 = "location";
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition.l1.location = "Beliz_town";
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition = "PZ_Beliz_PoterpKrushenie";
			AddMapQuestMarkCity("Beliz", false);
			
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			
			SetTimerCondition("PZ_BelizFail", 0, 0, 30, false);
		break;
		
		case "PZ_PoterpKrushenie_7":
			dialog.text = "但伯利兹很近! 肯定不会花很久吧? ";
			link.l1 = "我很着急。 不能绕道。 ";
			link.l1.go = "PZ_PoterpKrushenie_8";
		break;
		
		case "PZ_PoterpKrushenie_8":
			dialog.text = "连短途都不行吗? 就到伯利兹? 求你了, 船长, 别把我们丢下! ";
			link.l1 = "好吧, 希望我不会后悔。 都上船! ";
			link.l1.go = "PZ_PoterpKrushenie_6";
			link.l2 = "人生如此。 祝你们今天愉快, 朋友们。 ";
			link.l2.go = "PZ_PoterpKrushenie_9";
		break;
		
		case "PZ_PoterpKrushenie_9":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			DeleteAttribute(&locations[FindLocation("Shore9")], "DisableEncounters");
			
			for (i=1; i<=6; i++)
			{
				sld = CharacterFromID("PZ_PoterpKrushenie_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "", "", "", "", 10);
				sld.location = "None";
			}
			
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition.l1 = "location";
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition.l1.location = "Beliz_town";
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition = "PZ_Beliz_QuestCitizenDialog";
			
			AddMapQuestMarkCity("Beliz", false);
			
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			AddCharacterExpToSkill(pchar, "FencingL", 20);
			AddCharacterExpToSkill(pchar, "FencingS", 20);
			AddCharacterExpToSkill(pchar, "FencingH", 20);
			AddCharacterExpToSkill(pchar, "Pistol", 20);
			
			pchar.questTemp.PZ.Shipwreckers.Decline = true;
			
			SetTimerCondition("PZ_BelizFail", 0, 0, 30, false);
		break;
		
		case "PZ_PoterpKrushenie_11":
			dialog.text = "再次感谢你, 船长! 我们只是普通水手, 所以没什么能给你的。 ";
			link.l1 = "好吧, 至少我们没走太多弯路。 ";
			link.l1.go = "PZ_PoterpKrushenie_12";
		break;
		
		case "PZ_PoterpKrushenie_12":
			dialog.text = "我们会为你的健康举杯, 在教堂为你点一支蜡烛。 ";
			link.l1 = "那总比什么都没有好。 干杯, 伙计们! ";
			link.l1.go = "PZ_PoterpKrushenie_13";
		break;
		
		case "PZ_PoterpKrushenie_13":
			DialogExit();
			for (i=1; i<=6; i++)
			{
				sld = CharacterFromID("PZ_PoterpKrushenie_"+i);
				LAi_SetCitizenType(sld);
				LAi_CharacterDisableDialog(sld);
				sld.lifeday = 0;
				sld.location = "None";
			}
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_BelizZhitelNovosti", "citiz_4", "man", "man", 1, ENGLAND, 0, false, "quest"));
			ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto5");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_BelizZhitelNovosti_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "PZ_BelizZhitelNovosti_1":
			dialog.text = "你听说了吗? 他们终于抓住他了! 我们的水域终于安全了! ";
			link.l1 = "那是... 好消息吗? 但他们抓住了谁? ";
			link.l1.go = "PZ_BelizZhitelNovosti_2";
			DeleteQuestCondition("PZ_BelizFail");
		break;
		
		case "PZ_BelizZhitelNovosti_2":
			dialog.text = "马修.卢特, 就是那个‘风袋’! ";
			link.l1 = "我不熟悉 —他做了什么? ";
			link.l1.go = "PZ_BelizZhitelNovosti_3";
		break;
		
		case "PZ_BelizZhitelNovosti_3":
			dialog.text = "你不知道? ! 好吧, 你显然不是英国人, 我看得出来。 他是个海盗, 多年来一直在他的‘海鸥号’上掠夺我们和西班牙人。 ";
			link.l1 = "同时掠夺英国人和西班牙人? 那很不寻常。 ";
			link.l1.go = "PZ_BelizZhitelNovosti_4";
		break;
		
		case "PZ_BelizZhitelNovosti_4":
			dialog.text = "确实。 海岸警卫队一直抓不到他, 但最终, 他贪多嚼不烂 —输给了某艘奇怪的商船, 如果你能相信的话。 ";
			link.l1 = "真有趣。 那艘商船有什么奇怪的? ";
			link.l1.go = "PZ_BelizZhitelNovosti_5";
		break;
		
		case "PZ_BelizZhitelNovosti_5":
			dialog.text = "嗯, 那只是一艘巨大。 笨拙的帆船, 没有护航! 但多亏了她那个疯子船长, 卢特今天要唱最后一首歌了 —他就要被绞死了。 你应该来看看! ";
			link.l1 = "我可能会, 但现在我有其他事要处理。 ";
			link.l1.go = "PZ_BelizZhitelNovosti_6";
		break;
		
		case "PZ_BelizZhitelNovosti_6":
			DialogExit();
			
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			
			sld = CharacterFromID("Longway");
			if (!CharacterIsHere("Longway"))
			{
				ChangeCharacterAddressGroup(sld, PChar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"));
			}
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Longway_31";
		break;
		
		case "PZ_Longway_31":
			dialog.text = "船长阁下! ";
			link.l1 = "一艘西班牙商船击败了大胆的海盗... 你和朗威想的一样, 对吧? ";
			link.l1.go = "PZ_Longway_32";
		break;
		
		case "PZ_Longway_32":
			dialog.text = "晨星号... ";
			link.l1 = "很可能 —整个群岛没有其他商船船长像他那样。 ";
			link.l1.go = "PZ_Longway_33";
		break;
		
		case "PZ_Longway_33":
			dialog.text = "我们必须立即找到他! ";
			link.l1 = "对。 但我在港口没看到任何重型帆船。 我们试着在卢特被绞死前和他谈谈。 看看他是否名副其实。 ";
			link.l1.go = "PZ_Longway_34";
		break;
		
		case "PZ_Longway_34":
			DialogExit();
			ReturnOfficer_Longway();
			if (!CheckAttribute(pchar, "questTemp.PZ.Shipwreckers.Decline")) AddQuestRecord("PZ", "18");
			else AddQuestRecord("PZ", "18_1");
			pchar.questTemp.PZ_Beliz_Komendant = true;
			AddLandQuestMarkToPhantom("beliz_prison", "belizJailOff");
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
		break;
		
		case "PZ_Beliz_Komendant_8":
			dialog.text = "他还活着吗? 我们能和他谈谈吗? ";
			link.l1 = "";
			link.l1.go = "PZ_Beliz_Komendant_9";
			CharacterTurnByChr(npchar, CharacterFromID("BelizJailOff"));
		break;
		
		case "PZ_Beliz_Komendant_9":
			StartInstantDialogNoType("BelizJailOff", "PZ_Beliz_Komendant_10", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Beliz_Komendant_10":
			dialog.text = "什么? 哦, 是的。 他还活着 —处决还没发生。 你可以去和他谈谈 —他比以往任何时候都更健谈。 但最近, 他一直在胡言乱语,  mostly talking to himself。 ‘风袋’疯了... 我等不及要绞死他了, 免得我们都被他的喋喋不休逼疯。 ";
			link.l1 = "";
			link.l1.go = "PZ_Beliz_Komendant_11";
		break;
		
		case "PZ_Beliz_Komendant_11":
			StartInstantDialog("Longway", "PZ_Beliz_Komendant_12", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Beliz_Komendant_12":
			dialog.text = "谢谢。 ";
			link.l1 = "";
			link.l1.go = "PZ_Beliz_Komendant_13";
			CharacterTurnByChr(npchar, CharacterFromID("BelizJailOff"));
		break;
		
		case "PZ_Beliz_Komendant_13":
			DialogExit();
			pchar.questTemp.jailCanMove = true;
			
			ReturnOfficer_Longway();
			
			sld = CharacterFromID("BelizJailOff");
			LAi_SetHuberType(sld);
			sld.Dialog.Filename = "Common_Prison.c";
			sld.Dialog.CurrentNode = "First_officer";
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_MatthewLutter", "mercen_15", "man", "man", 1, ENGLAND, -1, false, "quest"));
			sld.name = "Matthew";
			sld.lastname = "Lutter";
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_MatthewLutter1";
			ChangeCharacterAddressGroup(sld, "Beliz_prison", "goto", "goto9");
			LAi_SetStayType(sld);
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "PZ_MatthewLutter1":
			dialog.text = "他偷了我的宝藏! ";
			link.l1 = "马修.卢特? ";
			link.l1.go = "PZ_MatthewLutter2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_MatthewLutter2":
			dialog.text = "我的宝藏现在和他绑在一起了, 你知道的, 是‘他’! 我们什么也做不了! 你想要什么? ! 你想从我们这里拿走更多东西吗? 已经什么都没有了! 她会死的! 或者更糟! ";
			link.l1 = "谁会死? 什么宝藏? 没关系, 这是你自己的错 —你攻击了那艘帆船, 而不是相反。 ";
			link.l1.go = "PZ_MatthewLutter3";
		break;
		
		case "PZ_MatthewLutter3":
			dialog.text = "不! 是相反的! 该死的那个西班牙贵族! 他是我们陷入这种困境的原因! 他径直向我们驶来, 近距离开炮! 然后他从我们这里夺走了她! ";
			link.l1 = "真的吗? 那不奇怪。 你还能告诉我们关于他的什么? 还有... 他拿走了什么? ‘她’是谁? ";
			link.l1.go = "PZ_MatthewLutter5";
		break;
		
		case "PZ_MatthewLutter5":
			dialog.text = "啊-啊-啊!!!啊啊啊啊!!! ";
			link.l1 = "我明白了, 我在浪费时间... ";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_BelizPrisonSoldierDialog");
		break;
		
		case "PZ_BelizPrisonQuestSoldier1":
			dialog.text = "船长, 如果你允许... 卢特! 出来! 结束了, 伙计。 ";
			link.l1 = "";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_BelizPrisonLongway_UvodyatNaKazn");
		break;
		
		case "PZ_Longway_35":
			dialog.text = "船长, 我们需要更多地了解索塔和卢特。 我们四处问问吧。 ";
			link.l1 = "好主意, 朗威。 反正我们从那个大喊大叫的人那里也没得到多少信息。 ";
			link.l1.go = "PZ_Longway_36";
		break;
		
		case "PZ_Longway_36":
			dialog.text = "但最好从索塔开始。 ";
			link.l1 = "对, 他是我们要找的人。 我们走。 ";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_BelizPrisonLongwayBack");
		break;
		
		case "PZ_Longway_37":
			dialog.text = "他们什么都不知道! ";
			link.l1 = "显然。 但我们已经有足够的信息自己开始思考了。 据我所知, 索塔可能很快会试图出售他获得的那些战略物资。 ";
			link.l1.go = "PZ_Longway_38";
		break;
		
		case "PZ_Longway_38":
			dialog.text = "正是! ";
			link.l1 = "我们应该在他前往皇家港或卡普斯特维尔的路上拦截他。 唯一的问题是他要去哪里, 我们应该在哪里与他交战。 或者也许我们会在公海上抓住他。 ";
			link.l1.go = "PZ_Longway_39";
		break;
		
		case "PZ_Longway_39":
			dialog.text = "不! 朗威的意思是... 费门特洛斯是一位经验丰富的船长。 在公海上战斗可能胜负难料。 我们在港口伏击他会有更好的机会。 ";
			link.l1 = "我想你是对的。 不管马特和他之间到底发生了什么, 索塔很危险, 不能低估。 ";
			link.l1.go = "PZ_Longway_40";
		break;
		
		case "PZ_Longway_40":
			dialog.text = "我们也不能等! ";
			link.l1 = "又说对了, 朗威。 所以我们立即起锚, 然后计划下一步行动。 ";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LongwayBelizDialogBack");
			DelMapQuestMarkCity("Beliz");
		break;
		
		case "PZ_Longway_41":
			dialog.text = "船长阁下, 晨星号在港口! ";
			link.l1 = "是的, 我已经注意到了。 ";
			link.l1.go = "PZ_Longway_42";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Longway_42":
			dialog.text = "你的计划是什么? ";
			link.l1 = "我还没决定。 在堡垒的炮火下登船将是自杀。 即使我们捕获了他们的重型帆船, 我们也无法乘坐它逃脱。 你有什么想法吗, 朗威? ";
			link.l1.go = "PZ_Longway_43";
		break;
		
		case "PZ_Longway_43":
			dialog.text = "是的。 我们可以在安全的海湾锚泊, 然后在夜幕掩护下乘船接近那艘帆船。 ";
			if (CheckAttribute(pchar, "questTemp.PZ_OhotaNaZvezdu_Kapstervil"))
			{
				link.l1 = "半月湾怎么样, 朗威? ";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_OhotaNaZvezdu_Yamaika"))
			{
				link.l1 = "我认为波特兰峡很合适 —足够近且相对安全。 你觉得呢? ";
			}
			link.l1.go = "PZ_Longway_44";
		break;
		
		case "PZ_Longway_44":
			dialog.text = "选择不错。 ";
			link.l1 = "太好了, 就这么定了。 我们漏掉什么了吗? ";
			link.l1.go = "PZ_Longway_45";
		break;
		
		case "PZ_Longway_45":
			dialog.text = "我想没有, 船长阁下。 我们只需要做好准备。 ";
			link.l1 = "完全正确。 ";
			link.l1.go = "PZ_Longway_46";
		break;
		
		case "PZ_Longway_46":
			DialogExit();
			
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "GenQuest.CabinLock");
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			bQuestDisableMapEnter = false;
			AddQuestRecord("PZ", "21");
			if (CheckAttribute(pchar, "questTemp.PZ_OhotaNaZvezdu_Kapstervil"))
			{
				AddQuestUserData("PZ", "sText", "半月湾");
				Island_SetReloadEnableGlobal("Nevis", true);
				
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition.l1 = "location";
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition.l1.location = "Shore43";
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition = "PZ_GotovimShlupki_Buhta";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_OhotaNaZvezdu_Yamaika"))
			{
				AddQuestUserData("PZ", "sText", "波特兰峡");
				Island_SetReloadEnableGlobal("Jamaica", true);
				
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition.l1 = "location";
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition.l1.location = "Shore36";
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition = "PZ_GotovimShlupki_Buhta";
			}
			PChar.quest.PZ_ZvezdaUhodimNaGlobalkru_Proval.win_condition.l1 = "MapEnter";
			PChar.quest.PZ_ZvezdaUhodimNaGlobalkru_Proval.win_condition = "PZ_ZvezdaUhodimNaGlobalkru_Proval";
			
			sld = CharacterFromID("Longway");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			LAi_SetOfficerType(sld);
			sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			sld.Dialog.CurrentNode = "Longway_officer";
		break;
		
		case "PZ_Zvezda_DialogWithCapitan":
			dialog.text = "你他妈的是谁, 发生了什么事? 霍姆斯先生! ";
			link.l1 = "霍姆斯先生不再在这里工作了。 而且我们已经把所有舱口都封死了。 所以, 我们会有一段时间不受打扰, 费门特洛斯先生。 ";
			link.l1.go = "PZ_Zvezda_DialogWithCapitan_2";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_Zvezda_DialogWithCapitan_2":
			dialog.text = "什么? 费门特洛斯? 我叫埃德加多.索塔! ";
			link.l1 = "嗯哼, 我以前听过这个。 我们知道那不是你的真名, 奥利维罗。 ";
			link.l1.go = "PZ_Zvezda_DialogWithCapitan_3";
		break;
		
		case "PZ_Zvezda_DialogWithCapitan_3":
			dialog.text = "费门特洛斯死了! ";
			link.l1 = "再想想, 你看起来太年轻了。 显然, 你不可能是十年前晨星号的船长。 那么, 奥利维罗怎么了? ";
			link.l1.go = "PZ_Zvezda_DialogWithCapitan_4";
		break;
		
		case "PZ_Zvezda_DialogWithCapitan_4":
			dialog.text = "我们摆脱了他。 他只是我们必须清理的另一个问题 —就像站在你旁边的那个一样。 ";
			link.l1 = "好吧, 既然你不是费门特洛斯, 也许你仍然可以回答我们的问题。 我们在找一个他从我朋友那里带走的人。 ";
			link.l1.go = "PZ_Zvezda_DialogWithCapitan_5";
		break;
		
		case "PZ_Zvezda_DialogWithCapitan_5":
			dialog.text = "我什么都不会告诉你! 他永远不会原谅我这件事。 ";
			link.l1 = "现在, 你最好担心我们是否会原谅你... ";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_SottaFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PZ_AnabelleLutter1":
			dialog.text = "他终于死了... ";
			link.l1 = "没错。 你是谁, 夫人? 他是强迫你留下的吗? 我很同情; 你一定经历了可怕的折磨... ";
			link.l1.go = "PZ_AnabelleLutter2";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_AnabelleLutter2":
			dialog.text = "我是安娜贝尔.卢特。 感谢上帝, 我没受太多苦, 但我很感激你的关心, 先生... ? ";
			link.l1 = "查尔斯.德.莫尔船长。 你说卢特... ";
			link.l1.go = "PZ_AnabelleLutter3";
		break;
		
		case "PZ_AnabelleLutter3":
			dialog.text = "啊, 你一定听说过马特? 可怜的傻瓜... 我是他的... 伴侣。 ";
			link.l1 = "卢特夫人, 对你的损失我深表遗憾。 你现在是寡妇了。 如果不是秘密的话, 你的娘家姓什么? ";
			link.l1.go = "PZ_AnabelleLutter4";
		break;
		
		case "PZ_AnabelleLutter4":
			dialog.text = "我没有。 仔细看看我。 我可怜的母亲是海盗的黑皮肤女奴。 没人知道我父亲是谁, 所以他们懒得给我一个合适的名字。 ";
			link.l1 = "那为什么没人碰你? 别误会 —我很高兴没发生那样的事。 但仍然, 这很... 不寻常。 ";
			link.l1.go = "PZ_AnabelleLutter5";
		break;
		
		case "PZ_AnabelleLutter5":
			dialog.text = "你说得对。 但我们还是直言不讳吧。 我不是娇生惯养的贵族女性; 我是奴隶的女儿。 我不会因为沉重的谈话而晕倒。 ";
			link.l1 = "呃, 我也不是娇生惯养的人。 但请继续。 为什么船员们没有碰那个女奴的女儿? 你不认识你父亲, 他似乎也不在乎。 ";
			link.l1.go = "PZ_AnabelleLutter6";
		break;
		
		case "PZ_AnabelleLutter6":
			dialog.text = "我想是吧。 既然你知道马特的事, 你知道他为勒瓦瑟工作过一段时间吗? ";
			link.l1 = "是的, 我在寻找晨星号时听说过。 但那有什么关系? 请告诉我一切。 ";
			link.l1.go = "PZ_AnabelleLutter7";
		break;
		
		case "PZ_AnabelleLutter7":
			dialog.text = "你还是不明白, 是吗? 显然, 你没听说过勒瓦瑟的... 偏好? ";
			link.l1 = "没听说过, 但话说回来, 那和... 有什么关系? ";
			link.l1.go = "PZ_AnabelleLutter8";
		break;
		
		case "PZ_AnabelleLutter8":
			dialog.text = "哦, 我想我得把一切都告诉你。 如果你太敏感的话, 先生, 坐下。 事情是这样的, 他和很多女人上床, 而且... ";
			if (pchar.questTemp.FMQT == "end")
			{
				link.l1 = "他的妻子离他不远, 她几乎和任何人上床。 ";
				link.l1.go = "PZ_AnabelleLutterKnow1";
			}
			else
			{
				link.l1 = "哦不。 ";
				link.l1.go = "PZ_AnabelleLutterDontKnow1";
			}
		break;
		
		case "PZ_AnabelleLutterKnow1":
			dialog.text = "嗯, 你知道他们怎么说... 有其夫必有其妻。 但不, 我肯定他做得更过分。 ";
			link.l1 = "有多过分? ";
			link.l1.go = "PZ_AnabelleLutter9";
		break;
		
		case "PZ_AnabelleLutterDontKnow1":
			dialog.text = "先生, 你的讽刺用错了地方。 你不知道我们在说什么。 ";
			link.l1 = "好吧, 好吧, 对不起。 请继续。 ";
			link.l1.go = "PZ_AnabelleLutter9";
		break;
		
		case "PZ_AnabelleLutter9":
			dialog.text = "这不仅仅是背叛配偶。 他在违背妇女意愿的情况下占有她们。 而且这不是一次性的虐待。 他绑架女孩, 把她们关在他拥有的一个酒窖里。 ";
			link.l1 = "所以他定期获取女奴? 而你本应是其中之一? ";
			link.l1.go = "PZ_AnabelleLutter10";
		break;
		
		case "PZ_AnabelleLutter10":
			dialog.text = "后者你说对了。 但可惜, 前者不是。 他不需要奴隶。 勒瓦瑟疯了 —以他自己的方式, 不像我的马特。 弗朗索瓦想完全拥有一个女人, 身体和灵魂。 当然, 这与爱无关。 他需要自由的女人来摧毁她们的意志。 他喜欢看着她们的外表。 行为和说话方式随着时间的推移而改变... ";
			link.l1 = "恶心... ";
			link.l1.go = "PZ_AnabelleLutter11";
		break;
		
		case "PZ_AnabelleLutter11":
			dialog.text = "你已经觉得有点恶心了。 现在想象一下那些女人的感受。 我听说过所有这些, 不仅仅是从马特那里。 勒瓦瑟曾经有一个葡萄牙贵族女人... ";
			link.l1 = "你视而不见, 保持沉默。 告诉我们一切。 我在旧世界和在群岛期间见过各种各样的事情。 现在没什么能让我惊讶的了。 ";
			link.l1.go = "PZ_AnabelleLutterWant1";
			link.l2 = "停, 我不想知道她发生了什么。 我希望那些女人在他手里没受太久的苦。 ";
			link.l2.go = "PZ_AnabelleLutter12";
		break;
		
		case "PZ_AnabelleLutterWant1":
			dialog.text = "但你从未听说过这样的事。 我希望你永远不会看到。 她被带到他面前时仍然骄傲而不屈, 尽管正如马特告诉我的, 勒瓦瑟的人在接管她丈夫在坎佩切附近的种植园后, 一路强奸她到托尔图加 —那些怪物朝他双膝开枪后, 他死于内出血... ";
			link.l1 = "一个坚强的女人... 但你说勒瓦瑟通常不碰他自己想要的女人。 ";
			link.l1.go = "PZ_AnabelleLutterWant2";
		break;
		
		case "PZ_AnabelleLutterWant2":
			dialog.text = "他特别要求的那些人是不受碰的。 但莱昂蒂娜夫人是一份礼物。 对他们所有人来说都是一个意想不到的惊喜。 所以他们放纵了自己... ";
			link.l1 = "我明白了... ";
			link.l1.go = "PZ_AnabelleLutterWant3";
		break;
		
		case "PZ_AnabelleLutterWant3":
			dialog.text = "我猜... 马特已经成为弗朗索瓦的宠儿之一。 他被邀请参加勒瓦瑟的一个秘密聚会... 在宴会上, 一个海盗抱怨女人不够。 勒瓦瑟笑了, 然后... ";
			link.l1 = "然后? 发生了什么? ";
			link.l1.go = "PZ_AnabelleLutterWant4";
		break;
		
		case "PZ_AnabelleLutterWant4":
			dialog.text = "... 然后她被带了出来。 被拴着! 被打, 背上有抓痕, 蒙着眼睛, 塞着嘴。 当他们取下 gag 时, 她只说... ";
			link.l1 = "想象是可怕的事。 她是不是用尽一切诅咒他? ";
			link.l1.go = "PZ_AnabelleLutterWant5";
		break;
		
		case "PZ_AnabelleLutterWant5":
			dialog.text = "如果只是那样... 唐娜.莱昂蒂娜只是低声说, ‘我的主人希望什么? ’";
			link.l1 = "我想我要吐了。 马特告诉你她后来怎么样了吗? ";
			link.l1.go = "PZ_AnabelleLutterWant6";
		break;
		
		case "PZ_AnabelleLutterWant6":
			dialog.text = "当然是被谋杀了。 但不是死在勒瓦瑟手里。 他像流浪狗一样丢弃了她。 他的一个船长开枪打死了她。 在她死前, 她只说了一个词... ";
			link.l1 = "诅咒? 祈祷? ";
			link.l1.go = "PZ_AnabelleLutterWant7";
		break;
		
		case "PZ_AnabelleLutterWant7":
			dialog.text = "不。 ‘谢谢... ’";
			link.l1 = "在经历了这样的折磨后感谢死亡... 她一定忍受了什么... 以及在那个怪物巢穴里像她一样的其他人... ";
			link.l1.go = "PZ_AnabelleLutter12";
		break;
		
		case "PZ_AnabelleLutter12":
			dialog.text = "勒瓦瑟特别鄙视奴隶和黑皮肤女性 —他说她们没有什么可摧毁的。 她们在他手下活不了多久, 印第安人也是如此 —除了少数特别固执的。 但野性和反抗也不是答案 —他会杀死那些太快试图取悦他的人, 以及那些反抗太久的人。 ";
			link.l1 = "太可怕了... 告诉我, 勒瓦瑟有没有抓过亚洲女性? ";
			link.l1.go = "PZ_AnabelleLutter13";
		break;
		
		case "PZ_AnabelleLutter13":
			dialog.text = "没有, 至少我没听说过。 至于我... 我已经告诉过你, 他不喜欢黑皮肤女性。 所以当马特为弗朗索瓦工作时, 他会在托尔图加的街上公开和我散步。 他甚至带我去过一次住所。 ";
			link.l1 = "但勒瓦瑟还是想把你变成他的奴隶之一... ";
			link.l1.go = "PZ_AnabelleLutter14";
		break;
		
		case "PZ_AnabelleLutter14":
			dialog.text = "正是... 我不知道他为什么这么喜欢我... 当马特发现后, 他一接到通知就逃离了岛屿。 他再也没有回到托尔图加。 他可能有点疯狂, 但他爱我。 他称我为他的宝藏... ";
			link.l1 = "所以这就是他说索塔从他那里夺走了宝藏的意思! ";
			link.l1.go = "PZ_AnabelleLutter15";
		break;
		
		case "PZ_AnabelleLutter15":
			dialog.text = "呵, 他这么说过? 哦, 马特... 但看来我们注定无法一起变老。 如果勒瓦瑟盯上了某个女人, 他会不惜一切代价得到她, 不管她的背景或代价如何。 索塔是他的船长之一, 他照做了。 ";
			link.l1 = "我明白了。 现在你打算做什么, 安娜贝尔? ";
			link.l1.go = "PZ_AnabelleLutter16";
		break;
		
		case "PZ_AnabelleLutter16":
			dialog.text = "逃跑。 去一个勒瓦瑟的人找不到我的地方。 改名字。 伪装自己... ";
			link.l1 = "希望你成功。 祝你一切顺利, 安娜贝尔。 ";
			link.l1.go = "PZ_AnabelleLutter17";
			if (sti(pchar.Money) >= 10000)
			{
				link.l2 = "你需要钱来安排通行。 拿着这个。 这里有一万比索。 ";
				link.l2.go = "PZ_AnabelleLutter17_Peso";
			}
			if (PCharDublonsTotal() >= 100)
			{
				link.l3 = "你需要的不仅仅是一点钱。 不是每个人都愿意帮助一个黑皮肤的女孩, 即使是混血儿。 给你, 拿一百杜布隆 —找艘船躲起来。 ";
				link.l3.go = "PZ_AnabelleLutter17_Dublon";
			}
		break;
		
		case "PZ_AnabelleLutter17":
			dialog.text = "你也是! 再见, 船长。 ";
			link.l1 = "再见。 ";
			link.l1.go = "Exit";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddDialogExitQuest("PZ_AnabelleGo");
		break;
		
		case "PZ_AnabelleLutter17_Peso":
			dialog.text = "我... 我不知道该说什么。 除了马特, 从来没有人对我这么好。 ";
			link.l1 = "也许这是一个信号。 表明你最终会在某个地方幸福地老去。 再会。 ";
			link.l1.go = "Exit";
			AddMoneyToCharacter(pchar, -10000);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddDialogExitQuest("PZ_AnabelleGo");
		break;
		
		case "PZ_AnabelleLutter17_Dublon":
			dialog.text = "你说得对。 非常感谢你这个。 我余生都会在祈祷中记住你。 ";
			link.l1 = "谢谢你。 一路顺风。 ";
			link.l1.go = "Exit";
			RemoveDublonsFromPCharTotal(100);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			AddDialogExitQuest("PZ_AnabelleGo");
		break;
		
		case "PZ_Longway_47":
			dialog.text = "那个人... 不, 他不再是个人了。 他是野兽。 一个怪物。 那样折磨女人... ";
			link.l1 = "我知道你在想什么, 朗威。 但你听到了 —他从未有过黄皮肤的女人。 ";
			link.l1.go = "PZ_Longway_48";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_Longway_48":
			dialog.text = "但他认识整个团伙! 范德温克。 费门特洛斯。 索塔... 我们刚在他的日志里读到过。 如果那个特定的‘她’是... 她呢? ";
			link.l1 = "谁知道呢... 一个一心报复费门特洛斯的女人 —很容易理解你为什么会这么想。 但可能是任何被奥利维罗毁掉生活的女人。 不一定是你妹妹。 甚至不一定是黄皮肤女人。 ";
			link.l1.go = "PZ_Longway_49";
		break;
		
		case "PZ_Longway_49":
			dialog.text = "你是... 在最后一刻拒绝尝试吗, 船长阁下? ";
			link.l1 = "不, 朗威。 但你怎么想象呢? 勒瓦瑟不太可能回答我们任何问题。 像这样在托尔图加四处打探太危险了。 ";
			link.l1.go = "PZ_Longway_50";
		break;
		
		case "PZ_Longway_50":
			dialog.text = "那你建议怎么办? ";
			link.l1 = "等待。 我们知道勒瓦瑟不喜欢你妹妹那样的女人。 所以我们现在可以保存资源。 耐心和力量。 弗朗索瓦是个硬骨头, 尤其是因为他的‘乌龟’。 但有斯文森的帮助, 我们可以按我们的条件和他谈。 我答应过你会帮你找妹妹, 并打算信守承诺。 你相信我吗, 朗威? ";
			link.l1.go = "PZ_Longway_51";
		break;
		
		case "PZ_Longway_51":
			dialog.text = "嗯... 是, 船长阁下。 但朗威还有一个请求。 ";
			link.l1 = "什么? 你不会又打算独自行动吧? 上次结局不太好。 ";
			link.l1.go = "PZ_Longway_52";
		break;
		
		case "PZ_Longway_52":
			dialog.text = "完全不是, 船长阁下。 我现在意识到, 不幸的是, 在一个由白人统治的世界里, 像我这样的人无法独自做任何事。 朗威请你在卡普斯特维尔靠岸, 给乔治.格拉韦尔送封信, 让他在你准备的时候打听一下。 ";
			link.l1 = "好主意, 朗威。 我们会这么做。 ";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TeleportToShore");
		break;
		
		case "PZ_Longway_53":
			dialog.text = "船长阁下, 有件事朗威需要问... ";
			link.l1 = "你忘了写信吗? 你可以直接和格拉韦尔谈。 ";
			link.l1.go = "PZ_Longway_54";
		break;
		
		case "PZ_Longway_54":
			dialog.text = "不, 信已经准备好了。 但朗威觉得最好不要独自在镇上逛。 船长阁下... 你能帮我把信交给乔治吗? 求你了? ";
			link.l1 = "我看起来像信使吗? 还是说你才是船长? ";
			link.l1.go = "PZ_Longway_55";
		break;
		
		case "PZ_Longway_55":
			dialog.text = "船长阁下... ";
			link.l1 = "哈哈哈, 我开玩笑的, 朗威! 提醒我去哪里找你的这个格拉韦尔? ";
			link.l1.go = "PZ_Longway_56";
		break;
		
		case "PZ_Longway_56":
			dialog.text = "他在教堂工作。 ";
			link.l1 = "好的, 我来处理。 ";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_ToCapstervilleChurch");
			AddLandQuestMark(characterFromId("Charles_Priest"), "questmarkmain");
		break;
		
		// 阶段5
		case "PZ_Mary_Sharptown1":
			dialog.text = "查尔斯, 我亲爱的查尔斯, 怎么了? 你看起来很担心, 而且... 好吧, 很累。 ";
			link.l1 = "哦, 不, 不, 玛丽, 我没事。 只是... 我在托尔图加的任务。 似乎又一次陷入了僵局... 还有Sharp的遗嘱绝对让我付出了代价, 天哪。 但没关系。 ";
			link.l1.go = "PZ_Mary_Sharptown2";
		break;
		
		case "PZ_Mary_Sharptown2":
			dialog.text = "什么? 什么任务? 那和Sharp有什么关系? 我完全不明白! ";
			link.l1 = "太多问题了, 玛丽。 这里不适合谈这些。 我们去酒馆房间谈好吗? 就像你喜欢的那样, 看不见也想不到。 我会告诉你我过去一年都在做什么。 ";
			link.l1.go = "PZ_Mary_Sharptown3";
		break;
		
		case "PZ_Mary_Sharptown3":
			dialog.text = "好吧! 但要注意: 如果你在隐瞒什么... ";
			link.l1 = "绝对没有! 走吧, 反正我们有时间消磨... ";
			link.l1.go = "PZ_HelenaMary_Exit";
		break;
		
		case "PZ_Helena_Sharptown1":
			dialog.text = "真奇怪, 不是吗, 查尔斯? 我本该拥有这个岛, 但我一点也不觉得自己拥有它。 ";
			link.l1 = "你这么认为? ";
			link.l1.go = "PZ_Helena_Sharptown2";
		break;
		
		case "PZ_Helena_Sharptown2":
			dialog.text = "哦, 你的笑容... 你确实知道如何对待女孩。 但你怎么了? 你的表情不对劲! ";
			link.l1 = "为什么? 这是我平常的脸, 也很帅。 ";
			link.l1.go = "PZ_Helena_Sharptown3";
		break;
		
		case "PZ_Helena_Sharptown3":
			dialog.text = "查尔斯, 我从你声音里能听出来 —你最近情绪低落。 ";
			link.l1 = "我肩上担子很重, 尤其是朗威的事。 我只是累了。 但现在放弃太晚了, 特别是因为我向他和我父亲许了诺。 ";
			link.l1.go = "PZ_Helena_Sharptown4";
		break;
		
		case "PZ_Helena_Sharptown4":
			dialog.text = "我不明白... 朗威和这有什么关系? 你许了什么承诺? ";
			link.l1 = "如果我们要谈这个, 去酒馆租个房间谈。 远离其他人。 ";
			link.l1.go = "PZ_Helena_Sharptown5";
		break;
		
		case "PZ_Helena_Sharptown5":
			dialog.text = "好吧, 走吧。 反正也没别的事可做, 至少我们可以一起待一段时间。 ";
			link.l1 = "前面带路, 亲爱的! ";
			link.l1.go = "PZ_HelenaMary_Exit";
		break;
		
		case "PZ_HelenaMary_Exit":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) ReturnOfficer_Mary();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) ReturnOfficer_Helena();
			WaitDate("", 0, 0, 0, 2, 0);
			LAi_SetImmortal(npchar, true);
			ChangeCharacterAddressGroup(npchar, "Pirates_tavern_upstairs", "goto", "goto1");
			DoQuestReloadToLocation("Pirates_tavern_upstairs", "goto", "goto2", "PZ_Etap5_NaverhuTavernBandits");
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "看他们在彼此怀里睡得多么甜蜜! 真可爱! ";
				link.l1 = "嫉妒了? ";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "醒醒! 你们这对情侣睡得怎么样? ";
				link.l1 = "很好, 谢谢关心。 你们这些家伙睡得如何? ";
			}
			link.l1.go = "PZ_Etap5_NaverhuTavernBandits_2";
			locCameraFromToPos(2.34, 1.92, 1.66, true, -1.66, -0.69, -0.02);
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "这是个愚蠢的问题, 你不觉得吗? ";
				link.l1 = "确实。 而且你们这么做很愚蠢。 想知道为什么吗? ";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "他们说你伶牙俐齿, 查尔斯.德.莫尔。 ";
				link.l1 = "不止是伶牙俐齿。 想试试吗? 但告诉我, 为什么我们睡觉时你们不攻击? ";
			}
			link.l1.go = "PZ_Etap5_NaverhuTavernBandits_3";
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "为什么? ";
				link.l1 = "你不应该在早上惹玛丽生气。 你很快就会知道为什么。 ";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "简单! 天很黑, 你知道, 所以我们分不清你们哪个是女的。 ";
				link.l1 = "混蛋。 ";
			}
			link.l1.go = "PZ_Etap5_NaverhuTavernBandits_4";
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "不像你, 我不怕女人。 说到这个 —伙计们, 把她安全带走, 否则胡格诺会把我们变成女人! ";
				link.l1 = "胡... 谁? ";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "至少我看起来像个男人。 伙计们, 活捉金发的 —胡格诺在等她。 ";
				link.l1 = "胡... 谁? ";
			}
			link.l1.go = "PZ_Etap5_NaverhuTavernBandits_5";
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_5":
			DialogExit();
			LAi_SetFightMode(pchar, true);
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("PZ_NaverhuTavernBandits_"+i);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				
				LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
				LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
				LAi_group_SetCheck("EnemyFight", "PZ_Etap5_NaverhuTavernBandits_Win");
			}
		break;
		
		case "PZ_MaryHelena_BitvaNaverhu_1":
			DelLandQuestMark(npchar);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "那是谁, 查尔斯? 那个胡格诺到底是谁? 真的是... ? ";
				link.l1 = "只有一个, 玛丽。 我们最好... ";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "查尔斯... 那是什么? 胡格诺? 这是我想的那个人吗? ";
				link.l1 = "恐怕是, 海伦。 我们需要... ";
			}
			link.l1.go = "PZ_MaryHelena_BitvaNaverhu_2";
		break;
		
		case "PZ_MaryHelena_BitvaNaverhu_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "你听到了吗? 有人来了, 没错。 可能是这些死人的朋友。 ";
				link.l1 = "那我们就看着他们加入。 准备好... ";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "你听到了吗? 脚步声。 ";
				link.l1 = "我确实听到了。 站在我身后。 ";
			}
			link.l1.go = "PZ_MaryHelena_BitvaNaverhu_3";
		break;
		
		case "PZ_MaryHelena_BitvaNaverhu_3":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) ReturnOfficer_Mary();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) ReturnOfficer_Helena();
			sld = CharacterFromID("Longway");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Longway_61";
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			RemovePassenger(pchar, sld);
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "PZ_Longway_61":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "船长阁下, " + sStr + "女士。 ";
			link.l1 = "朗威? ! 你觉得你能就这样走进我们的房间? 如果我们正在... ? ";
			link.l1.go = "PZ_Longway_62";
			
			//预先创建船只占位符
			sld = GetCharacter(NPC_GenerateCharacter("PZ_ShipStasis", "citiz_46", "man", "man", sti(pchar.rank), PIRATE, -1, false, "quest"));
			SetSPECIAL(sld, 1, 1, 1, 1, 1, 1, 1);
		break;
		
		case "PZ_Longway_62":
			dialog.text = "嗯, 请原谅, 船长阁下。 我以为如果你们在忙的话会关上门。 但朗威发现门是开着的。 ";
			link.l1 = "是破了, 不是开着。 但告诉我, 我的朋友, 你为什么这么该死的冷静? 地板上有尸体, 我们都有武器, 而你... ";
			link.l1.go = "PZ_Longway_63";
		break;
		
		case "PZ_Longway_63":
			dialog.text = "嗯, 我习惯了。 ";
			link.l1 = "你无法反驳, 对吧? 但说真的, 你来这里的路上没听到打斗声吗? 没看到这些混蛋走进酒馆然后上楼吗? ";
			link.l1.go = "PZ_Longway_64";
		break;
		
		case "PZ_Longway_64":
			dialog.text = "没有, 船长阁下。 我上来时在大厅没看到陌生人。 ";
			link.l1 = "真是荒谬的巧合。 那你想要什么, 朗威? ";
			link.l1.go = "PZ_Longway_65";
		break;
		
		case "PZ_Longway_65":
			dialog.text = "我急需一艘船和船员, 船长阁下。 ";
			link.l1 = "什么? 为什么? 你终于找到长兴的踪迹了? 如果是这样, 我们现在就一起去追她。 ";
			link.l1.go = "PZ_Longway_66";
		break;
		
		case "PZ_Longway_66":
			dialog.text = "可惜不是长兴。 是... 乔普.范德温克。 乔治.格拉韦尔捎了个信, 我在村里散步时收到了, 而你... 在和女士休息。 ";
			link.l1 = "是啊, 我休息得很好, 告诉你。 但为什么我们现在要分开, 朗威? 我们有一长串重要任务要完成, 还有危险人物要杀。 ";
			link.l1.go = "PZ_Longway_67";
		break;
		
		case "PZ_Longway_67":
			dialog.text = "范德温克不像勒瓦瑟那么危险。 此外, 我已经打败过他一次。 我会再打败他一次。 这次, 确保他彻底死透。 我不想我们都在他身上浪费宝贵时间。 你应该去托尔图加, 向重要人物打听我们需要的任何信息。 我自己去抓范德温克。 船长阁下, 这不值得浪费你的时间, 而且我也曾是船长。 我能应付。 ";
			link.l1 = "嗯, 你有道理, 朗威。 范德温克可能没那么危险, 但‘班滕号’是群岛最快的船之一。 不是每艘船都能追上她。 船员呢? 你打算怎么自己迅速召集人手? ";
			link.l1.go = "PZ_Longway_68";
		break;
		
		case "PZ_Longway_68":
			dialog.text = "我知道合适的地方, 而且我在那里有公司的关系。 或者至少我可以像对乔治那样假装。 公司... 罗登堡先生急需战斗人员。 专业船员, 不问问题的人时, 会使用他们的服务。 ";
			link.l1 = "那么是雇佣船员... 有这种事存在也合理。 要花多少钱? ";
			link.l1.go = "PZ_Longway_69";
		break;
		
		case "PZ_Longway_69":
			dialog.text = "两千五。 现在就要。 ";
			link.l1 = "就这些? 在酒馆雇佣一整支正规船员队伍都不止这个数, 尤其是大船。 显然罗登堡和他的代理人在特殊地方有特殊价格。 ";
			link.l1.go = "PZ_Longway_70";
		break;
		
		case "PZ_Longway_70":
			dialog.text = "我是说杜布隆, 船长阁下。 ";
			link.l1 = "什么? ! ";
			link.l1.go = "PZ_Longway_70_4";
		break;
		
		case "PZ_Longway_70_4":
			dialog.text = "你没听错, 船长阁下。 这很重要。 我不会为小事要这么多。 ";
			link.l1 = "是, 我听到了, 但我还是不敢相信。 确实是特殊价格。 他们收比索吗? ";
			link.l1.go = "PZ_Longway_70_5";
		break;
		
		case "PZ_Longway_70_5":
			dialog.text = "收... 从白人那里。 朗威可能有麻烦, 但... 我想如果我努力请求, 能说服他们。 总有办法。 ";
			link.l1 = "好吧, 算点什么。 而你还得弄艘船... 可能也在某个‘特殊地方’? 我都不敢问要花多少钱... ";
			link.l1.go = "PZ_Longway_70_6";
		break;
		
		case "PZ_Longway_70_6":
			dialog.text = "不完全是, 船长阁下。 船员有自己的船。 ";
			link.l1 = "但? ";
			link.l1.go = "PZ_Longway_70_7";
		break;
		
		case "PZ_Longway_70_7":
			dialog.text = "‘美凤号’。 她可能成为决定性因素 —群岛没有比她更快的船。 而且她是... 曾是我的, 所以我了解她。 你会把她借给我吗, 船长阁下? ";
			if (PCharDublonsTotal() >= 2500)
			{
				link.l1 = "给你。 两千五百杜布隆。 只要你把范德温克的头放在纯金盘子上带给我, 哈哈哈哈! ";
				link.l1.go = "PZ_Longway_Dublons_1";
			}
			if (sti(pchar.Money) >= 300000)
			{
				link.l2 = "我没带那么多杜布隆, 朗威。 而且我怀疑船上也不会有 —你说的是一堆金子。 但比索, 当然。 三十万正好是你需要的。 ";
				link.l2.go = "PZ_Longway_Peso_1";
			}
			link.l3 = "你知道吗, 朗威... 你真的建议我支付足够装备一支围攻舰队的钱, 就为了让你去打一个普通暴徒? ! ";
			link.l3.go = "PZ_Longway_Otkaz";
		break;
				
		case "PZ_Longway_Dublons_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) AddQuestUserData("PZ", "sText", "Mary");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) AddQuestUserData("PZ", "sText", "Helen");
			
			dialog.text = "哦... 朗威从心底感谢你, 船长阁下! 但还是, ‘美凤号’怎么办? ";
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				link.l1 = "她怎么了? 我的朋友, 你来的路上撞到头了吗? 她现在就在我们的舰队里! ";
				link.l1.go = "PZ_Longway_Mayfang1";
			}
			else
			{
				link.l1 = "我需要考虑一下, 朗威。 我们有多少时间抓范德温克? ";
				link.l1.go = "PZ_Longway_NoMayfang1";
			}
			RemoveDublonsFromPCharTotal(2500);
			pchar.questTemp.PZ_FlagShipDublons = true;
			Notification_Approve(true, "Longway");
		break;
		
		case "PZ_Longway_Peso_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) AddQuestUserData("PZ", "sText", "Mary");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) AddQuestUserData("PZ", "sText", "Helen");
			
			dialog.text = "船长阁下, 你犯了个小错误。 应该是二十五万比索。 ";
			link.l1 = "我没犯; 这是查尔斯.德.莫尔在朋友需要帮助时的特别汇率, 哈哈。 我多给你点, 这样你就有足够的钱应付一切了。 ";
			link.l1.go = "PZ_Longway_Peso_2";
			AddMoneyToCharacter(pchar, -300000);
		break;
		
		case "PZ_Longway_Peso_2":
			dialog.text = "非常感谢, 船长阁下... 但是, ‘美凤号’怎么办? ";
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				link.l1 = "她怎么了? 我的朋友, 你来的路上撞到头了吗? 她现在就在我们的舰队里! ";
				link.l1.go = "PZ_Longway_Mayfang1";
			}
			else
			{
				link.l1 = "我需要考虑一下, 朗威。 我们有多少时间抓范德温克? ";
				link.l1.go = "PZ_Longway_NoMayfang1";
			}
		break;
		
		case "PZ_Longway_Otkaz":
			dialog.text = "没有别的办法了, 船长阁下, 请冷静... ";
			link.l1 = "哦, 我还没开始呢。 听着。 五万比索。 这足够从造船厂买一艘双桅船, 准备好战斗, 甚至雇佣船员了。 ";
			link.l1.go = "PZ_Longway_Otkaz_2";
			AddMoneyToCharacter(pchar, -50000);
			
			pchar.questTemp.PZ.LongwayBrig = true; // 朗威将乘坐双桅船
			Notification_Approve(false, "Longway");
		break;
		
		case "PZ_Longway_Otkaz_2":
			dialog.text = "但是, 船长阁下。 这可能够一个白人船长用! 不是每个人都愿意和朗威打交道。 他们在卖给我任何东西之前都会狠狠砍价! ";
			link.l1 = "所以, 要有说服力! 从你最初的... 提议来看, 你很擅长讨价还价。 你还在这里? 拿着钱走吧, 既然你说这么紧急! ";
			link.l1.go = "PZ_Longway_Otkaz_3";
		break;
		
		case "PZ_Longway_Otkaz_3":
			dialog.text = "是, 船长阁下... ";
			link.l1 = "别那样看着我。 我稍后在托尔图加见你。 祝你好运。 ";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
			AddQuestRecord("PZ", "58");
		break;
		
		case "PZ_Longway_Mayfang1":
			dialog.text = "呃, 不, 船长阁下。 当然, 我记得。 朗威只是问问你是否准备好和我分享她。 ";
			link.l1 = "我准备好。 毕竟, 范德温克和你妹妹的不幸与我们名单上的其他人一样有关。 所以抓住他真的很重要。 我把‘美凤号’交给你指挥。 ";
			link.l1.go = "PZ_Longway_Mayfang2";
		break;
		
		case "PZ_Longway_Mayfang2":
			// 如果"美凤号"在主角那里
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
						{
							//pchar.questTemp.PZ.Mayfang.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Mayfang.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			
			pchar.questTemp.PZ.LongwayMayfang = true;
			pchar.questTemp.PZ_FlagShip = true;
			
			dialog.text = "难以置信... 谢谢你, 船长阁下! ";
			link.l1 = "啊, 没什么。 她曾是你的船, 我会永远记得。 好了, 去吧。 杀了那个混蛋。 我去托尔图加。 ";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
			AddQuestRecord("PZ", "59");
			Notification_Approve(true, "Longway");
		break;
		
		
		case "PZ_Longway_NoMayfang1":
			dialog.text = "时间不多了, 船长阁下。 我们不应该浪费 —长兴可能需要我们的帮助... ";
			link.l1 = "我知道, 朗威。 但我们到底有多少时间抓范德温克? ";
			link.l1.go = "PZ_Longway_NoMayfang2";
		break;
		
		case "PZ_Longway_NoMayfang2":
			dialog.text = "几个月 —他按固定路线航行大约这么久, 然后消失一段时间。 正如格拉韦尔在信中告诉我的。 ";
			link.l1 = "好吧。 那我们去船上... ";
			link.l1.go = "PZ_Longway_NoMayfang3";
		break;
		
		case "PZ_Longway_NoMayfang3":
			dialog.text = "恐怕我的准备工作必须立即开始, 船长阁下。 这样当我拿到‘美凤号’时就可以马上出发。 我需要提前和那些人谈判。 ";
			link.l1 = "那我们在哪里见面? ";
			link.l1.go = "PZ_Longway_NoMayfang4";
		break;
		
		case "PZ_Longway_NoMayfang4":
			AddQuestRecord("PZ", "60");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) AddQuestUserData("PZ", "sText", "Mary");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) AddQuestUserData("PZ", "sText", "Helen");
			
			i = FindColony("Pirates");
			if (colonies[i].nation != ENGLAND)
			{
				dialog.text = "就在这里。 但为了方便你, 我们可以在造船厂见面。 ";
				link.l1 = "为什么只有我不知道只要出对价钱, 在这里就能雇佣一整支战斗船员? ";
				link.l1.go = "PZ_Longway_NoMayfangIslaTesoro1";
			}
			else
			{
				dialog.text = "那些雇佣兵过去在伊斯拉特索罗有个地方, 但被迫搬到这里。 ";
				link.l1 = "我明白为什么。 那在拉维加我去哪里找你? ";
				link.l1.go = "PZ_Longway_NoMayfangLaVega1";
			}
		break;
		
		case "PZ_Longway_NoMayfangIslaTesoro1":
			dialog.text = "因为很少有人知道。 而且能负担得起的人更少。 很长一段时间里, 罗登堡先生是他们唯一的客户。 ";
			link.l1 = "我明白了。 好吧, 朗威。 在那里见。 ";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LongwayToPiratesShipyard");
		break;
		
		case "PZ_Longway_NoMayfangLaVega1":
			dialog.text = "酒馆, 船长阁下。 我还能在哪里? ";
			link.l1 = "说得对。 回头见, 朗威! 照顾好自己。 ";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LongwayToLaVegaTavern");
		break;
		
		case "PZ_Longway_WaitForShip1":
			dialog.text = "船长阁下, 我通知你船员准备好了。 还有最后一件事要处理。 ‘美凤号’怎么办? ";
			link.l1 = "到目前为止, 我还没真正为你挑到一艘配得上你的船, 朗威。 ";
			link.l1.go = "PZ_Longway_WaitForShip2";
			if ((FindCompanionShips(SHIP_SCHOONER_W)) || (FindCompanionShips(SHIP_BRIG)) || (FindCompanionShips(SHIP_CORVETTE)) || (FindCompanionShips(SHIP_POLACRE)) || (FindCompanionShips(SHIP_XebekVML)) || (FindCompanionShips(SHIP_BRIGANTINE)))
			{
				if (FindCompanionShips(SHIP_SCHOONER_W)) sStr = "War schooner";
				if (FindCompanionShips(SHIP_BRIG)) sStr = "Brig";
				if (FindCompanionShips(SHIP_CORVETTE)) sStr = "Corvette";
				if (FindCompanionShips(SHIP_POLACRE)) sStr = "Polacre";
				if (FindCompanionShips(SHIP_XebekVML)) sStr = "Xebek";
				if (FindCompanionShips(SHIP_BRIGANTINE)) sStr = "Brigantine";
				link.l2 = "'" + sStr + "'是你的了.";
				link.l2.go = "PZ_Longway_NoQuestShip1";
			}
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				link.l3 = "‘美凤号’呢? 你以为我会让她浪费吗? ";
				link.l3.go = "PZ_Longway_Mayfang3";
			}
			if (FindCompanionShips(SHIP_CURSED_FDM))
			{
				link.l4 = "我有一艘... 特别的船给你, 朗威。 一艘快船。 甚至比美凤号更致命。 这是战 galley, ‘飞翔之心’。 ";
				link.l4.go = "PZ_Longway_Caleuche1";
			}
			if (FindCompanionShips(SHIP_POLACRE_QUEST))
			{
				link.l5 = "你喜欢 三桅小帆船, 朗威。 那双桅帆船呢? 尤其是这艘, ‘斗牛士’。 当然不是为赛艇建造的, 但她相当强大。 ";
				link.l5.go = "PZ_Longway_Torero1";
			}
			if (FindCompanionShips(SHIP_ELCASADOR))
			{
				link.l6 = "我必须承认, 我没想到有一天会有值得用它的地方。 你觉得这艘 galleon 怎么样? 强大的‘埃尔卡萨多’! ";
				link.l6.go = "PZ_Longway_ElCasador1";
			}
		break;
		
		case "PZ_Longway_NoQuestShip1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			
			// 现在一起唱, 孩子们: 我恨补丁, 我恨补丁, 我恨补丁, 恨... 救命!!! 
			if ((FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_SCHOONER_W)
						{
							//pchar.questTemp.PZ.SchoonerW.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.SchoonerW.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwaySchoonerW = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_BRIG)
						{
							//pchar.questTemp.PZ.Brig.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Brig.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayBrig = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_CORVETTE)
						{
							//pchar.questTemp.PZ.Corvette.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Corvette.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayCorvette = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_POLACRE)
						{
							//pchar.questTemp.PZ.Polacre.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Polacre.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayPolacre = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_XebekVML)
						{
							//pchar.questTemp.PZ.Xebek.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Xebek.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayXebek = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_BRIGANTINE)
						{
							//pchar.questTemp.PZ.Brigantine.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Brigantine.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayBrigantine = true;
			}
			
			dialog.text = "这不是‘美凤号’, 船长阁下! ‘美凤号’怎么了? ";
			link.l1 = "朗威! " + sStr + "有危险! 你妹妹也一样! 而你还在为没有这样的船而发脾气? ! 任何人都会为有这样的船而高兴! 由你指挥她, 让范德温克看看你的能力。 ";
			link.l1.go = "PZ_Longway_NoQuestShip2";
		break;
		
		case "PZ_Longway_NoQuestShip2":
			dialog.text = "好吧... 希望上天赐我好运。 就像我希望你在托尔图加也有好运一样。 再见, 船长阁下。 ";
			link.l1 = "我相信会的。 再见, 朗威。 ";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
			pchar.questTemp.PZ_NoQuestShip = true;
		break;
		
		case "PZ_Longway_Mayfang3":
			// 如果"美凤号"在主角那里
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
						{
							//pchar.questTemp.PZ.Mayfang.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Mayfang.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			
			pchar.questTemp.PZ.LongwayMayfang = true;
			pchar.questTemp.PZ_FlagShip = true;
			
			dialog.text = "呃, 不, 船长阁下。 当然, 我记得。 朗威只是问问你是否准备好和我分享她。 ";
			link.l1 = "我准备好。 毕竟, 范德温克和你妹妹的不幸与我们名单上的其他人一样有关。 所以抓住他真的很重要。 我把‘美凤号’交给你指挥。 ";
			link.l1.go = "PZ_Longway_Mayfang4";
		break;
		
		case "PZ_Longway_Mayfang4":
			dialog.text = "难以置信... 谢谢你, 船长阁下! ";
			link.l1 = "啊, 没什么。 她曾是你的船, 我会永远记得。 好了, 去吧。 杀了那个混蛋。 我去托尔图加。 ";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
			Notification_Approve(true, "Longway");
		break;
		
		case "PZ_Longway_Caleuche1":
			dialog.text = "我... 我不能指挥这个, 船长阁下。 朗威仍然在乎自己的生命。 灵魂和理智。 ";
			link.l1 = "哈哈哈, 朗威! 得了吧, 我不知道你这么迷信。 但不管怎样, 诅咒已经解除了, 所以你没什么好怕的。 ";
			link.l1.go = "PZ_Longway_Caleuche2";
		break;
		
		case "PZ_Longway_Caleuche2":
			dialog.text = "啊... 但范德温克知道吗? 他一看到那艘船就会像受惊的兔子一样逃跑。 ";
			link.l1 = "你说得对。 好吧, 我们再给你找别的。 ";
			link.l1.go = "PZ_Longway_WaitForShip2";
		break;
		
		case "PZ_Longway_Torero1":
			// 如果"托雷罗"在主角那里
			if (FindCompanionShips(SHIP_POLACRE_QUEST))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_POLACRE_QUEST)
						{
							//pchar.questTemp.PZ.Torero.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Torero.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			
			pchar.questTemp.PZ.LongwayTorero = true;
			if (CheckAttribute(pchar, "questTemp.PZ_FlagShipDublons"))
			{
				pchar.questTemp.PZ_FlagShip = true;
				Notification_Approve(true, "Longway");
			}
			
			dialog.text = "我当船长时从未驾驶过三桅船。 她很有趣, 但现在最重要的是速度, 不是力量。 ";
			link.l1 = "没错, 但毕竟是三桅船。 她可能不如‘班滕号’快, 但你可以在他们无法做到的角度迎风。 甚至比‘美凤号’曾经做到的还要多。 所以利用这一点。 ";
			link.l1.go = "PZ_Longway_Torero2";
		break;
		
		case "PZ_Longway_Torero2":
			dialog.text = "还是... ‘美凤号’更好... 可惜你让她浪费了, 船长阁下。 祝你在托尔图加好运。 ";
			link.l1 = "你也一样, 朗威。 谢谢。 ";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
		break;
		
		case "PZ_Longway_ElCasador1":
			// 如果"埃尔卡萨多"在主角那里
			if (FindCompanionShips(SHIP_ELCASADOR))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_ELCASADOR)
						{
							//pchar.questTemp.PZ.ElCasador.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.ElCasador.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			
			pchar.questTemp.PZ.LongwayElCasador = true;
			if (CheckAttribute(pchar, "questTemp.PZ_FlagShipDublons"))
			{
				pchar.questTemp.PZ_FlagShip = true;
				Notification_Approve(true, "Longway");
			}
			
			dialog.text = "那可能是群岛最不寻常的 galleon, 船长阁下。 我能驾驭它, 但它比‘班滕号’慢... ";
			link.l1 = "嗯, 你又不是在和乔普赛艇, 对吧? ";
			link.l1.go = "PZ_Longway_ElCasador2";
		break;
		
		case "PZ_Longway_ElCasador2":
			dialog.text = "随你怎么说。 但‘美凤号’更好... 可惜你让她浪费了, 船长阁下。 祝你在托尔图加好运。 ";
			link.l1 = "你也一样, 朗威。 谢谢。 ";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
		break;
		
		case "PZ_Longway_WaitForShip2":
			NextDiag.TempNode = "PZ_Longway_WaitForShip1";
			
			dialog.text = "感谢你的关心, 船长阁下, 但请快点 —我们时间不多了。 ";
			link.l1 = "我知道。 但你不想徒劳无功, 对吧? 好吧, 我会给你找艘合适的船。 ";
			link.l1.go = "Exit";
		break;
		
		case "PZ_HelenaTortugaCabin_1":
			dialog.text = "我们快到了, 查尔斯。 你决定从哪里开始了吗? 也许我们在街上问人... ";
			link.l1 = "也许吧。 但不是我们 —是我。 你留在船上, 海伦。 ";
			link.l1.go = "PZ_HelenaTortugaCabin_2";
		break;
		
		case "PZ_HelenaTortugaCabin_2":
			dialog.text = "查尔斯, 当然, 我还是对那些恶棍和他们说的话感到不安, 我留在船员的保护下是有道理的... 但你独自进入龙潭虎穴并没有让我感到更安全。 ";
			link.l1 = "我明白。 但如果出了问题, 独自逃跑更容易, 知道你是安全的。 这是命令, 海伦。 在这里等我, 尽量别太担心。 ";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TortugaCabin_Exit");
		break;
		
		case "PZ_MaryTortugaCabin_1":
			dialog.text = "这是托尔图加, 查尔斯, 没错。 我等不及要去敲门, 问问那头肥驴想从我这里得到什么... ";
			link.l1 = "这正是你要留在船上的原因, 我亲爱的。 ";
			link.l1.go = "PZ_MaryTortugaCabin_2";
			
			pchar.questTemp.MarySexBlock = true;
			pchar.quest.Mary_giveme_sex.over = "yes";
			pchar.quest.Mary_giveme_sex1.over = "yes";
		break;
		
		case "PZ_MaryTortugaCabin_2":
			dialog.text = "没门! 你以为我会让你一个人上岸? ";
			link.l1 = "我认为如果勒瓦瑟决定完成他的雇佣兵未竟的事, 我们将没有反击的机会。 我不想不必要地激怒他, 尤其是因为我的目标不是他, 而是乔普.范德温克。 ";
			link.l1.go = "PZ_MaryTortugaCabin_3";
		break;
		
		case "PZ_MaryTortugaCabin_3":
			dialog.text = "所以我现在被关起来了, 是吗? ";
			link.l1 = "我不是在命令你, 我是在请求你, 玛丽。 ";
			link.l1.go = "PZ_MaryTortugaCabin_4";
		break;
		
		case "PZ_MaryTortugaCabin_4":
			dialog.text = "如果你在那个鬼岛的某个小巷里出了什么事怎么办? ";
			link.l1 = "那我保证不逞英雄。 知道你安全会帮助我跑得更快。 所以在船上等我, 看在上帝的份上, 不管发生什么都不要上岸。 ";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TortugaCabin_Exit");
		break;
		
		case "PZ_RobertMartin1":
			chrDisableReloadToLocation = true;
			
			dialog.text = "你是谁? 我怀疑你穿过海滩不只是为了聊天。 ";
			link.l1 = "没错。 查尔斯.德.莫尔。 罗伯特.马丁? ";
			link.l1.go = "PZ_RobertMartin2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_RobertMartin2":
			dialog.text = "查尔斯.德.莫尔? 该死, 别让我卷入任何可疑的事。 是的, 是我。 那么, 你想要什么? ";
			link.l1 = "有人告诉我你是乔普.范德温克的朋友, 而且... ";
			link.l1.go = "PZ_RobertMartin3";
		break;
		
		case "PZ_RobertMartin3":
			dialog.text = "谁告诉你的? 我会把他们的肠子都溅出来。 好吧, 我们认识, 仅此而已。 我不想因为他惹了你而惹上麻烦。 ";
			link.l1 = "呵, 你很快就放弃朋友了... ";
			link.l1.go = "PZ_RobertMartin4";
		break;
		
		case "PZ_RobertMartin4":
			dialog.text = "别这么想。 我不是怕你。 但为什么要自找麻烦甚至制造麻烦呢? 我不像你听说的那样和乔普很熟。 你在找他吗? ";
			link.l1 = "是的, 算是吧。 我知道他已经离开托尔图加了, 但多了解他一些也无妨 —他去过哪里, 和谁谈过话。 你能帮忙吗? ";
			link.l1.go = "PZ_RobertMartin5";
		break;
		
		case "PZ_RobertMartin5":
			dialog.text = "反正这对你也没帮助, 所以... 为什么不呢? 他在一家妓院。 那家妓院。 我想你能负担得起, 所以我告诉你。 ";
			link.l1 = "一家新妓院? 难道一家对你来说不够了吗? ";
			link.l1.go = "PZ_RobertMartin6";
		break;
		
		case "PZ_RobertMartin6":
			dialog.text = "嗯, 不是新的, 但知道的人不多。 而且只有少数人能负担得起。 我猜你的时候到了。 但要注意 —只收杜布隆。 给银币, 你会被踢屁股。 ";
			link.l1 = "我猜也是。 你说这家妓院在哪里? ";
			link.l1.go = "PZ_RobertMartin7";
		break;
		
		case "PZ_RobertMartin7":
			dialog.text = "你知道那栋有圆柱的建筑吗? 就是那家。 他们有个多么棒的女主人啊! 黄皮肤, 太漂亮了! 哈, 我看你已经流口水了, 嗯? ";
			link.l1 = "呵呵, 算是吧。 谢谢, 罗伯特。 今天你没惹麻烦 —你帮了我大忙。 ";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LighthouseMartinGo");
		break;
		
		case "PZ_MaryTortugaCabin_11":
			dialog.text = "你终于回来了, 查尔斯! 我简直坐立不安, 知道吗! ";
			link.l1 = "我不会久留, 玛丽。 我有点事要处理... 我就不跟你卖关子了 —是朗威的事。 我需要去当地一家妓院。 ";
			link.l1.go = "PZ_MaryTortugaCabin_12";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_MaryTortugaCabin_12":
			dialog.text = "我就知道不该让你一个人上岸。 要么你忘了戴帽子, 脑袋热昏了... 要么你撞到脑袋了, 知道吗! ";
			link.l1 = "玛丽, 听我说。 这家店的老板有可能是朗威的妹妹。 为了确认, 我得见见她, 但我只会这么做。 不进去我可做不到。 但我不想让你胡思乱想。 ";
			link.l1.go = "PZ_MaryTortugaCabin_13";
		break;
		
		case "PZ_MaryTortugaCabin_13":
			dialog.text = "你确定没骗我吗, 查尔斯? ";
			link.l1 = "玛丽, 这么想... 你听说过有男人会提前警告爱人关于... ?";
			link.l1.go = "PZ_MaryTortugaCabin_14";
		break;
		
		case "PZ_MaryTortugaCabin_14":
			dialog.text = "打住, 查尔斯, 我甚至不想去想。 我相信并信任你。 希望你不会在那里待得比必要的时间长。 ";
			link.l1 = "不会多待一分钟, 亲爱的, 我保证。 去去就回, 你看着吧。 ";
			link.l1.go = "PZ_PredupredilNashuDevushku";
		break;
		
		case "PZ_HelenaTortugaCabin_11":
			dialog.text = "查尔斯! 你回来得比我预期的还快。 但发生了什么? 你看起来不太好... 你找到关于乔普.范德温克的什么了吗? ";
			link.l1 = "还没有。 我了解了一些情况, 但要进一步... 我需要去一家... 妓院。 当然不是你想的那样。 ";
			link.l1.go = "PZ_HelenaTortugaCabin_12";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_HelenaTortugaCabin_12":
			dialog.text = "妓院? 我不知道这些地方除了明显的功能还能提供什么。 ";
			link.l1 = "我只是需要和老板聊聊。 而且这不是普通的妓院。 传闻是 - 这是一家非常昂贵的场所, 只接待上流社会人士... ";
			link.l1.go = "PZ_HelenaTortugaCabin_13";
		break;
				
		case "PZ_HelenaTortugaCabin_13":
			dialog.text = "那么这正适合你, 亲爱的。 哦, 我开玩笑的。 不过, 我还是不高兴你去那里。 但是... ";
			link.l1 = "我保证我去完全是为了朗威的事。 很可能那个地方的老板是他的妹妹。 我不会待很久。 ";
			link.l1.go = "PZ_HelenaTortugaCabin_14";
		break;
		
		case "PZ_HelenaTortugaCabin_14":
			dialog.text = "随你便。 你没有义务告诉我这些事。 我从未答应过你我不会和别的男人睡觉。 然而, 我没有。 因为这是我理所当然的事。 ";
			link.l1 = "在其他情况下, 我会带你一起去, 但是... ";
			link.l1.go = "PZ_HelenaTortugaCabin_15";
		break;
		
		case "PZ_HelenaTortugaCabin_15":
			dialog.text = "谢谢, 但不必了。 查尔斯, 别担心。 我不是那种愚蠢的嫉妒女孩。 嗯, 也许会嫉妒, 但不愚蠢。 而且我相信你。 我真傻! ";
			link.l1 = "谢谢你, 海伦。 我很快就回来。 ";
			link.l1.go = "PZ_PredupredilNashuDevushku";
		break;
		
		case "PZ_PredupredilNashuDevushku":
			DialogExit();
			LAi_SetActorType(npchar);
			pchar.questTemp.PZ_PredupredilNashuDevushku = true;
		break;
		
		case "PZ_ElitaShluha_1":
			dialog.text = "哦, 我们店里来了新面孔? 欢迎, 先生。 食物。 陈年葡萄酒。 热水澡 - 如果你能负担得起和我们中的一位共度时光, 这些都在等着你。 ";
			link.l1 = "感谢你的欢迎, 小姐。 但我不是为这个来的。 我在找某人... ";
			link.l1.go = "PZ_ElitaShluha_2";
			
			// 从灯塔移除马丁
			sld = characterFromID("PZ_RobertMartin");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			
			for (i=1; i<=3; i++)
			{
				sld = characterFromID("PZ_MayakPiraty_"+i);
				sld.lifeday = 0;
			}
			
			sld = characterFromID("PZ_RobertMartin_CloneMayakShip");
			sld.lifeday = 0;
			
			locations[FindLocation("Mayak6")].DisableEncounters = false;
			LAi_LocationFightDisable(&Locations[FindLocation("Mayak6")], false);
			RemoveGeometryFromLocation("Mayak6", "smg");
		break;
		
		case "PZ_ElitaShluha_2":
			dialog.text = "只有用心灵才能看得清楚; 本质的东西用眼是看不见的。 ";
			link.l1 = "真美。 我以前从未听过这些话。 ";
			link.l1.go = "PZ_ElitaShluha_3";
		break;
		
		case "PZ_ElitaShluha_3":
			dialog.text = "我们在这里接受教育, 不只是玩偶。 女主人认为这对我们的店很重要。 ";
			link.l1 = "女主人! 那就是我要找的人。 听说她是黄皮肤。 告诉我, 是真的吗? 顺便问一下, 她叫什么名字? ";
			link.l1.go = "PZ_ElitaShluha_4";
		break;
		
		case "PZ_ElitaShluha_4":
			dialog.text = "是真的。 但她的商业头脑比许多白人女性都好。 她叫美丽星辰。 但别再说了。 ";
			link.l1 = "别再说了, 你说? 我来就是为了说话。 我再问几个问题就走。 ";
			link.l1.go = "PZ_ElitaShluha_5";
		break;
		
		case "PZ_ElitaShluha_5":
			dialog.text = "这对店里有什么好处? 这里人们不是为身体付钱, 而是为时间付钱。 你想说话? 欢迎。 但要先付钱。 我们会在房间里低声交谈, 避开窥探的耳朵。 我不在乎我们在那里做什么 - 我不在乎我们是否点蜡烛祈祷。 有个客户曾经让我帮他写诗。 另一个让我谈论他的烦恼, 称我为他的好朋友。 第三个 - 只是点蜡烛, 然后... ";
			link.l1 = "嗯, 我不想知道 - 我最近已经听到一些不愉快的事了。 我该付你多少钱? ";
			link.l1.go = "PZ_ElitaShluha_6";
		break;
		
		case "PZ_ElitaShluha_6":
			dialog.text = "二百五十杜布隆。 不议价。 如果我们发现是个身无分文的装腔作势者, 我们会毫不后悔地把他扔出去。 如果他富有但贪婪, 我们会提高价格 - 他反正会付。 ";
			if (PCharDublonsTotal() >= 250)
			{
				link.l1 = "给你, 二百五十枚金币。 ";
				link.l1.go = "PZ_ElitaShluha_7";
			}
			link.l2 = "哇, 这地方比牙买加的那家妓院还贵。 我能等拿到金子再来吗? ";
			link.l2.go = "PZ_ElitaShluha_Otkaz_1";
		break;
		
		case "PZ_ElitaShluha_7":
			dialog.text = "好的。 我们从哪里开始? 晚餐, 带或不带蜡烛, 洗澡, 还是聊天? ";
			link.l1 = "我时间不多, 所以直接问问题吧。 带路。 ";
			link.l1.go = "PZ_ElitaShluha_IdemVKomnatu";
			RemoveDublonsFromPCharTotal(250);
		break;
		
		case "PZ_ElitaShluha_Otkaz_1":
			dialog.text = "当然可以。 耐心是交际花的美德之一。 把乞丐扔出去是一回事。 让像你这样的有钱绅士去取钱, 甚至借钱, 是另一回事。 ";
			link.l1 = "交际花的美德... 真讽刺。 我马上回来。 ";
			link.l1.go = "PZ_ElitaShluha_Otkaz_2";
		break;
		
		case "PZ_ElitaShluha_Otkaz_2":
			DialogExit();
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("PZ_ElitaShluha_"+i);
				LAi_CharacterDisableDialog(sld);
			}
			LAi_CharacterEnableDialog(npchar);
			npchar.dialog.filename = "Quest\CompanionQuests\Longway.c";
			npchar.dialog.currentnode = "PZ_ElitaShluha_Again";
		break;
		
		case "PZ_ElitaShluha_Again":
			dialog.text = "欢迎回来, 先生! 那么, 你是谁? 有钱的绅士还是装腔作势者? ";
			if (PCharDublonsTotal() >= 250)
			{
				link.l1 = "当然, 我是有钱的绅士, 小姐。 这是你的金子 - 整整二百五十杜布隆。 不用数了。 ";
				link.l1.go = "PZ_ElitaShluha_Again_1";
			}
			link.l2 = "我还不够, 再等等。 ";
			link.l2.go = "exit";
			NextDiag.TempNode = "PZ_ElitaShluha_Again";
		break;
		
		case "PZ_ElitaShluha_Again_1":
			dialog.text = "我们这里不数钱。 嗯, 有些硬币看起来弯曲破损 - 女主人不会太喜欢, 但至少都是真金。 ";
			link.l1 = "真是个... 优雅的人。 ";
			link.l1.go = "PZ_ElitaShluha_Again_2";
			RemoveDublonsFromPCharTotal(250);
		break;
		
		case "PZ_ElitaShluha_Again_2":
			dialog.text = "没错。 埃托ile夫人可以温柔体贴, 也可以严厉, 甚至冷酷无情。 这就是为什么我们不数钱, 顺便说一下。 女主人不总是马上收到钱, 但她总能得到应得的。 如果不是金子, 就是血。 任何风月场所都需要守护者和赞助人。 而我们的与店的地位相称。 ";
			link.l1 = "我已经付钱了, 所以带路吧。 ";
			link.l1.go = "PZ_ElitaShluha_IdemVKomnatu";
		break;
		
		case "PZ_ElitaShluha_IdemVKomnatu":
			DialogExit();
			pchar.PZ_ElitaShluha = npchar.id;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "reload", "reload3", "PZ_ElitaShluha_VKomnate", -1);
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, npchar, "", -1);
			bDisableCharacterMenu = true;
		break;
		
		case "PZ_ElitaShluha_8":
			dialog.text = "那么, 你有什么问题, 先生? 我会尽力满足你的... 好奇心。 ";
			link.l1 = "你知道我感兴趣的是什么, 小姐 - 你的女主人, 埃托ile夫人。 ";
			link.l1.go = "PZ_ElitaShluha_9";
		break;
		
		case "PZ_ElitaShluha_9":
			dialog.text = "关于她我能说什么呢? 她对我们来说仍然是个谜, 即使对我们也是如此。 尽管她关心我们的福祉。 健康和安全, 但她不社交, 也不与我们任何人亲近。 ";
			link.l1 = "也许她不喜欢长谈。 告诉我, 她说话有口音吗? ";
			link.l1.go = "PZ_ElitaShluha_10";
		break;
		
		case "PZ_ElitaShluha_10":
			dialog.text = "不, 你为什么这么想? 就因为她是黄皮肤? 她讲纯正的法语和其他几种语言。 她可以和客人及潜在利益相关者就任何话题进行长达一小时的交谈。 ";
			link.l1 = "你不说。 有趣... 她现在在这里吗? 如果在, 我就进去见她, 不再浪费你真正... 昂贵的时间, 这样你就可以回去工作了。 ";
			link.l1.go = "PZ_ElitaShluha_11";
		break;
		
		case "PZ_ElitaShluha_11":
			dialog.text = "没有多少可回去的 - 尽管我们女主人的目标是让这里成为群岛最好的地方。 一个精英场所, 任何商人。 贵族或只是受过教育的人都不会羞于前来 - 因为我们提供的不仅仅是身体。 ";
			link.l1 = "但她不太成功, 是吗? ";
			link.l1.go = "PZ_ElitaShluha_12";
		break;
		
		case "PZ_ElitaShluha_12":
			dialog.text = "怎么说呢... 她不把我们每个人都看作商品, 就像在更简单的场所那样, 而是看作一个项目。 昂贵的衣服。 药品。 教育 - 她在我们每个人身上投资。 如果我们在旧世界的大城市, 她就成功了! 但在这里... 即使是一个有才华的商人, 如果商品太贵, 几乎没人能买, 也赚不到钱。 即使我们降价, 我们仍然注定有一天会破产。 ";
			link.l1 = "很遗憾听到这个。 那么你的女主人现在在哪里? ";
			link.l1.go = "PZ_ElitaShluha_13";
		break;
		
		case "PZ_ElitaShluha_13":
			dialog.text = "到目前为止, 我们在这里生活得很好, 我可以告诉你。 这需要付出努力并达到她的标准... 至于这位女士, 她去了伊斯帕尼奥拉岛, 讨论将我们全部搬到太子港的可能性 - 毕竟, 那里有更多贸易路线交汇, 我们的生意在那里不会闲置并几乎持续亏损。 ";
			link.l1 = "是这样吗? 勒瓦瑟没有投资这个地方以确保其稳定吗? ";
			link.l1.go = "PZ_ElitaShluha_14";
		break;
		
		case "PZ_ElitaShluha_14":
			dialog.text = "不太多。 他来找我们, 说如果我们时不时去他那里, 他才会大量投资。 但女士断然拒绝了。 如此坚决, 以至于大人有那么一瞬间措手不及。 我从未见过她或他那样。 ";
			link.l1 = "呵呵, 看看。 她似乎知道... 勇敢, 非常勇敢。 ";
			link.l1.go = "PZ_ElitaShluha_15";
		break;
		
		case "PZ_ElitaShluha_15":
			dialog.text = "知道什么? 不过, 既然我们聊得这么好, 我再告诉你一件事, 但这是个大秘密, 所以不要和任何人讨论! ";
			link.l1 = "哦不, 小姐。 我向你保证, 我不想以任何方式伤害你的女士。 请继续。 ";
			link.l1.go = "PZ_ElitaShluha_16";
		break;
		
		case "PZ_ElitaShluha_16":
			dialog.text = "我甚至不知道你是否能伤害她, 因为美丽星辰每天都练习击剑, 她在整个城市都没有值得一战的对手。 除了太子港, 她还计划让马库斯.泰雷克斯本人投资! 或者说, 向他贷款。 你能想象吗? ";
			link.l1 = "是的, 我觉得今天我要和另一位经常练习击剑的女士进行一场非常艰难的谈话... 好吧, 谢谢你的分享, 小姐。 祝你有美好的一天和慷慨的客户。 ";
			link.l1.go = "PZ_ElitaShluha_17";
		break;
		
		case "PZ_ElitaShluha_17":
			dialog.text = "谢谢你。 但你为什么这么匆忙? 你已经全额付款了, 我们还没聊那么久。 此外, 你身上有某种精致的东西, 先生。 比来我们店的罕见富人多得多。 我们真的不享受彼此的陪伴吗? ";
			link.l1 = "你知道... 管他呢? 我为什么要假装和撒谎, 好像我不想要这个? 和你这样的女人在一起的机会非常难得。 ";
			link.l1.go = "PZ_ElitaShluha_YesSex";
			link.l2 = "哦, 很遗憾, 小姐。 我来只是为了说话。 此外... 有人在等我。 ";
			link.l2.go = "PZ_ElitaShluha_NoSex";
		break;
		
		case "PZ_ElitaShluha_NoSex":
			dialog.text = "好像那曾阻止过任何人。 在这种情况下, 你值得尊敬, 先生。 我为你的‘某人’感到非常高兴。 ";
			link.l1 = "再次感谢你, 小姐。 再见。 ";
			link.l1.go = "PZ_ElitaShluha_NoSex_2";
		break;
		
		case "PZ_ElitaShluha_NoSex_2":
			DialogExit();
			AddQuestRecord("PZ", "30");
			chrDisableReloadToLocation = false;
			bDisableFastReload = true;
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("PZ_ElitaShluha_"+i);
				LAi_CharacterDisableDialog(sld);
			}
			npchar.lifeday = 0;
			
			PChar.quest.PZ_TortugaKlemanLebren.win_condition.l1 = "location";
			PChar.quest.PZ_TortugaKlemanLebren.win_condition.l1.location = "Tortuga_town";
			PChar.quest.PZ_TortugaKlemanLebren.win_condition = "PZ_TortugaKlemanLebren";
			DelMapQuestMarkCity("Tortuga");
			AddMapQuestMarkCity("LaVega", false);
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1 && !CheckAttribute(pchar, "questTemp.PZ_PredupredilNashuDevushku"))
			{
				setCharacterShipLocation(pchar, "Tortuga_town");
				setWDMPointXZ("Tortuga_town");
			}
		break;
		
		case "PZ_ElitaShluha_YesSex":
			dialog.text = "谢谢你。 先一起洗个热水澡怎么样? ";
			link.l1 = "双手赞成。 ";
			link.l1.go = "PZ_ElitaShluha_YesSex_2";
		break;
		
		case "PZ_ElitaShluha_YesSex_2":
			DialogExit();
			LAi_SetStayType(pchar);
			DoQuestCheckDelay("PlaySex_1", 1.0);
			DoQuestCheckDelay("PZ_ElitaShluha_Fuck", 1.0);
		break;
		
		case "PZ_ElitaShluha_After":
			dialog.text = "那是一次神奇的体验, 先生。 我没想到一个男人能像那样让我惊喜。 你确实知道如何给女人带来快乐... ";
			link.l1 = "这取决于女人。 ";
			link.l1.go = "PZ_ElitaShluha_After_2";
		break;
		
		case "PZ_ElitaShluha_After_2":
			dialog.text = "你后悔吗? ";
			link.l1 = "现在, 绝对不。 再见, 小姐。 ";
			link.l1.go = "PZ_ElitaShluha_After_3";
		break;
		
		case "PZ_ElitaShluha_After_3":
			DialogExit();
			AddQuestRecord("PZ", "30");
			chrDisableReloadToLocation = false;
			bDisableFastReload = true;
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("PZ_ElitaShluha_"+i);
				LAi_CharacterDisableDialog(sld);
			}
			npchar.lifeday = 0;
			LAi_SetPlayerType(pchar);
			pchar.questTemp.PZ.EliteWhoreFucked = true; // 标记有过性行为 (用于与泰雷克斯的对话) 
			
			PChar.quest.PZ_TortugaKlemanLebren.win_condition.l1 = "location";
			PChar.quest.PZ_TortugaKlemanLebren.win_condition.l1.location = "Tortuga_town";
			PChar.quest.PZ_TortugaKlemanLebren.win_condition = "PZ_TortugaKlemanLebren";
			DelMapQuestMarkCity("Tortuga");
			AddMapQuestMarkCity("LaVega", false);
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1 && !CheckAttribute(pchar, "questTemp.PZ_PredupredilNashuDevushku"))
			{
				setCharacterShipLocation(pchar, "Tortuga_town");
				setWDMPointXZ("Tortuga_town");
			}
		break;
		
		case "PZ_KlemanLebren_1":
			dialog.text = "走路看着点, 装腔作势的! ";
			link.l1 = "注意你的嘴! ";
			link.l1.go = "PZ_KlemanLebren_2";
		break;
		
		case "PZ_KlemanLebren_2":
			dialog.text = "我在看着路, 而你在数乌鸦。 ";
			link.l1 = "如果你在看, 你可以绕开, 不是吗? ";
			link.l1.go = "PZ_KlemanLebren_3";
		break;
		
		case "PZ_KlemanLebren_3":
			dialog.text = "我为什么要绕开你? ! ";
			link.l1 = "我建议我们到城外去看看, 谁欠谁什么。 ";
			link.l1.go = "PZ_KlemanLebren_4";
		break;
		
		case "PZ_KlemanLebren_4":
			dialog.text = "嗯嗯, 不。 我不知道大人您如此厌恶一个普通人的无意触碰。 ";
			link.l1 = "再说一遍? ";
			link.l1.go = "PZ_KlemanLebren_5";
		break;
		
		case "PZ_KlemanLebren_5":
			dialog.text = "嗯, 抱歉。 我无意推你。 ";
			link.l1 = "这就对了。 ";
			link.l1.go = "PZ_KlemanLebren_6";
		break;
		
		case "PZ_KlemanLebren_6":
			DialogExit();
			
			LAi_LocationFightDisable(loadedLocation, false);
			chrDisableReloadToLocation = false;
			
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4", "", "", "", "", -1);
			npchar.location = "None";
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				sld = CharacterFromID("Mary");
				DelLandQuestMark(sld);
				if (CheckAttribute(pchar, "questTemp.PZ_PredupredilNashuDevushku"))
				{
					PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1 = "location";
					PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1.location = "Tortuga";
					PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition = "PZ_TortugaRazgovorVKauteSDevushkoy";
				}
				else
				{
					ChangeCharacterAddressGroup(sld, "Tortuga_town", "rld", "loc0");
					sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
					sld.dialog.currentnode = "PZ_MaryRazgovorOBordeli_Bad_1";
					LAi_SetStayType(sld);
					CharacterTurnToLoc(sld, "quest", "quest1");
					sld.talker = 5;
					chrDisableReloadToLocation = true;
					LAi_LocationFightDisable(loadedLocation, true);
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				sld = CharacterFromID("Helena");
				DelLandQuestMark(sld);
				PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1 = "location";
				PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1.location = "Tortuga";
				PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition = "PZ_TortugaRazgovorVKauteSDevushkoy";
			}
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_1":
			dialog.text = "如果你迟到半小时, 查尔斯, 我会让我们的炮弹把这个肮脏的窝点炸个粉碎, 知道吗! 你找到你要找的了吗? 那是她吗, 朗威的妹妹? 你见到她了吗? ";
			link.l1 = "嘘, 玛丽, 别那样说话。 不, 我没见到长兴... ";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_2";
			
			DeleteAttribute(pchar, "questTemp.MarySexBlock");
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_2":
			dialog.text = "那你到底为什么花了这么长时间? 你在那里干什么? ";
			link.l1 = "你没什么可担心的。 一旦我了解到所有可能的情况, 我就离开了那个地方, 就像我答应你的那样。 ";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_3";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_3":
			dialog.text = "快说, 知道吗! ";
			link.l1 = "目前店主不在托尔图加。 对她的服务需求在这里很低, 因为她雇佣穿着昂贵衣服的受过良好教育的女士, 而且只接受黄金作为支付... ";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_4";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_4":
			dialog.text = "你也付钱给她们了? ! ";
			link.l1 = "否则她们不会和我说话。 以这种方式, 难怪她们没有很多顾客。 这位夫人决定把她的生意搬到太子港, 希望吸引更富有的客户。 但显然她缺钱, 因为她决定向马库斯.泰雷克斯寻求贷款... ";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_5";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_5":
			dialog.text = "他认识她吗? ";
			link.l1 = "我们到拉维加就知道了。 如果我们赶紧出发, 停止不必要的闲聊, 我们会抓住这个亚洲女人, 不管她是谁。 ";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_6";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_6":
			dialog.text = "去那家妓院没必要, 查尔斯。 我相信如果我们努力, 我们可以在酒馆或街上找到所有这些信息, 知道吗。 ";
			link.l1 = "下次我带你一起去, 这样你就不会满脑子胡思乱想了, 嗯? 现在, 我们开始办事吧。 ";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_1":
			dialog.text = "哦, 我看我来晚了点, 知道吗! 好吧, 等等, 你这个无赖... ";
			link.l1 = "玛丽, 你到底在这里干什么? ! 我告诉过你待在船上! ";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_2";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_2":
			dialog.text = "所以我不会阻止你和妓女鬼混? ! 别想否认, 查尔斯! 船员在那里看到你了, 知道吗! 你怎么能这样? ! ";
			link.l1 = "我就知道。 我想我应该带他们一起去, 这样他们就能看到我在做什么 - 或者说没做什么 - 而不是小题大做... ";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_3";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_3":
			dialog.text = "你在指责我们的人撒谎? 在你自己做了那种事后, 你这个畜生? ";
			link.l1 = "我只指责他们无比愚蠢。 在不了解情况的情况下, 你... ";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_4";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_4":
			dialog.text = "哦哦, 查尔斯, 我想你和你的妓女们不会喜欢我如果及时赶到那个窝点会怎么‘理解’情况。 但你很幸运 - 我不得不自己划这该死的船... ";
			link.l1 = "据说艰苦的体力劳动能清除你头脑中不必要的想法。 但你仍然有很多, 所以你也要划回去。 ";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_5";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_5":
			dialog.text = "我不走, 知道吗! ";
			link.l1 = "玛丽, 我不想在勒瓦瑟的人面前在这里谈这个。 冷静下来, 看看周围, 做出判断。 现在不是时候也不是地方。 ";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_6";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_6":
			dialog.text = "去你的。 我的东西还在船舱里... 但别以为我会再划桨, 知道吗! 你身上一定还有点贵族的样子! ";
			link.l1 = "我是个无赖和畜生, 记得吗? 我会在船上证明这一点, 但我得先到那里。 所以你的请求是徒劳的。 ";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_7";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_7":
			DialogExit();
			LAi_LocationFightDisable(loadedLocation, false);
			
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", Get_My_Cabin(), "rld", "loc1", "OpenTheDoors", -1);
			
			PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1 = "location";
			PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1.location = "Tortuga";
			PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition = "PZ_TortugaRazgovorVKauteSDevushkoy";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_8":
			dialog.text = "你让全体船员都在笑你, 知道吗! ";
			link.l1 = "嗯, 也许也在笑你。 他们很久没见过这样的场面了。 现在你脾气冷静了一点, 让我告诉你发生了什么。 ";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_9";
			
			DeleteAttribute(pchar, "questTemp.MarySexBlock");
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_9":
			dialog.text = "查尔斯, 我现在什么都听说了。 我只有一个问题: 我对你不够好吗? 我有什么欠缺吗? ";
			link.l1 = "这不礼貌, 但我会用一个问题回答: 我有没有给过你不相信我的好理由? 嗯? 我不记得有这样的事。 所以深呼吸, 听我说。 除了知道乔普.范德温克去过一家妓院, 我没查到多少关于他的信息。 不是‘唱歌的乌鸦’附近的那家, 而是码头附近的另一家。 我以前不知道... 显然不像我们的水手, 他们让你了解了情况。 尽管他们不被允许去那里... ";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_10";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_10":
			dialog.text = "什么样的妓院不让水手进, 知道吗? ";
			link.l1 = "一家雇佣穿着丝绸衣服。 头脑里不只是空气的女士的妓院。 她们的服务专门用黄金杜布隆支付。 这不仅是任何人的突发奇想, 也是她们神秘的女主人美丽星辰的命令。 ";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_11";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_11":
			dialog.text = "神秘, 知道吗。 ";
			link.l1 = "不仅如此。 她是亚洲人。 ";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_12";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_12":
			dialog.text = "亚洲人? 托尔图加妓院的女主人? ";
			link.l1 = "可能是长兴。 这就是我去那里的原因 - 我想亲眼见见她。 仅此而已。 ";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_13";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_13":
			dialog.text = "她是什么样的? ";
			link.l1 = "我不知道。 她不在那里, 所以我不得不和另一个... 明星聊天。 ";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_14";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_14":
			dialog.text = "她也是亚洲人吗, 知道吗? ";
			link.l1 = "不, 她是白人。 她告诉我美丽星辰最近过得不太好, 所以决定搬到太子港。 有道理, 因为那里的人更富有。 这位夫人一定缺钱, 因为她需要贷款才能在伊斯帕尼奥拉岛开展业务, 她打算从泰雷克斯那里贷款。 所以如果我们赶紧去拉维加, 我们可以在马库斯见到她之前拦截她。 ";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_15";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_15":
			dialog.text = "我他妈不在乎她。 马库斯或其他任何人, 知道吗。 查尔斯, 就告诉我一件事 - 你有没有和她妓院里的任何女孩在一起? ";
			link.l1 = "我不需要那个, 玛丽。 我有你, 世界上最好的女孩。 我不明白你为什么意识不到这一点。 ";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_16";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_16":
			dialog.text = "实际上, 真相很容易弄清楚, 知道吗, 嘻嘻。 如果你没和任何人在一起, 你现在一定精力充沛。 我们现在就来检查一下, 知道吗! ";
			link.l1 = "玛丽, 求你..";
			link.l1.go = "exit";
			pchar.quest.sex_partner = Npchar.id;
			AddDialogExitQuestFunction("LoveSex_Cabin_Go");
			pchar.questTemp.PZ_MaryRazgovorOBordeli = true;
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_17":
			DeleteAttribute(pchar, "questTemp.PZ_MaryRazgovorOBordeli");
			if (CheckAttribute(pchar, "questTemp.PZ.EliteWhoreFucked"))
			{
				if (IsCharacterPerkOn(pchar, "Medic"))
				{
					notification("Excellent Health", "Medic");
					dialog.text = "(身体极佳) 呃... 看来你没撒谎, 查尔斯, 知道吗... ";
					link.l1 = "我没必要欺骗你, 亲爱的... ";
					link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_18";
				}
				else
				{
					notification("Perk check failed", "Medic");
					dialog.text = "查尔斯, 你是... 认真的吗? 那是什么? ";
					link.l1 = "哦, 这热度对我没好处。 咳咳。 ";
					link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_19";
				}
			}
			else
			{
				dialog.text = "呃... 看来你没撒谎, 查尔斯, 知道吗... ";
				link.l1 = "我没必要欺骗你, 亲爱的... ";
				link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_18";
			}
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_18":
			dialog.text = "但我不会忘记那次划小艇的经历! ";
			link.l1 = "哈! ";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_19":
			dialog.text = "你以前从没抱怨过, 不是吗? ";
			link.l1 = "你试试在该死的岛上跑来跑去... ";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_20";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_20":
			dialog.text = "还有妓院, 知道吗! 你真的... ";
			link.l1 = "玛丽, 对不起。 ";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_21";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_21":
			dialog.text = "什么? ! 所以你... ";
			link.l1 = "我不是为那个抱歉。 该死。 我的意思是, 除了你, 我没和任何人在一起, 我告诉过你。 我只是... 无法安心, 仅此而已。 你知道, 当拉罗什的大炮盯着你时, 这很难做到。 ";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_22";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_22":
			dialog.text = "这是个好借口, 查尔斯。 好吧, 我相信你。 这次... 但要知道我仍然在生你的气, 知道吗! ";
			link.l1 = "我会赢得你的原谅, 我保证。 ";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_1":
			dialog.text = "好吧, 情郎, 告诉我你发现了什么。 值得冒失去我好感的风险吗? ";
			link.l1 = "我真的分不清你是在开玩笑还是认真的。 这很值得 - 尽管我没有亲眼见到女主人。 她是亚洲人, 名叫美丽星辰- 一颗美丽的星星。 当然不是她的真名... ";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Good_2";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_2":
			dialog.text = "为此你必须去妓院? 你不能在旅馆查到吗? ";
			link.l1 = "镇上的人不太谈论这个地方。 为什么? 这是个好问题。 你可以自己问美丽星辰- 她去了伊斯帕尼奥拉岛。 ";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Good_3";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_3":
			dialog.text = "托尔图加不够她待? ";
			link.l1 = "显然, 这里的生意不好。 她不雇佣普通的港口女孩, 而是穿着华丽。 受过教育的女士。 ";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Good_4";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_4":
			dialog.text = "她们为什么要那样做? ";
			link.l1 = "这是另一个好问题。 不管怎样, 我们的小鸟决定飞到太子港, 德.穆萨克的领地。 但为这次努力的贷款将从不是别人, 正是泰雷克斯那里获得。 ";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Good_5";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_5":
			dialog.text = "我希望这个故事很快结束。 我们不要浪费时间, 设定航向拉维加。 ";
			link.l1 = "我们就这么做。 ";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_1":
			dialog.text = "你是个勇敢的人, 查尔斯, 我承认这一点。 这么轻松地出现, 如此面不改色, 好像什么都没发生过。 ";
			link.l1 = "我想是某个船员多嘴了? 当然没有任何背景。 因为实际上什么也没发生 - 至少不是你想的那样。 ";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_2";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_2":
			dialog.text = "我很高兴你没有否认, 查尔斯。 ";
			link.l1 = "我本来要告诉你一切的, 海伦。 ";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_3";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_3":
			dialog.text = "别, 查尔斯。 细节我不太感兴趣。 但原因感兴趣。 告诉我, 我有什么问题吗? ";
			link.l1 = "让我们从原因开始。 我发现托尔图加有两家妓院。 一家很有名。 另一家 - 人们知道, 但很少有人想谈论。 它由一个亚洲女人拥有... ";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_4";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_4":
			dialog.text = "你是现编的吗? ";
			link.l1 = "我到底为什么要那样做, 海伦? ! 如果你不相信我, 他们会在那个地方证实的! ";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_5";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_5":
			dialog.text = "首先, 你告诉我不要上岸, 所以我不可能去那里。 其次, 你以为我是谁? ! 我不会靠近那样的地方! 第三... 继续说。 ";
			link.l1 = "很好。 我决定去那里亲眼见见埃托ile夫人。 这是我唯一的目的, 该死的! ";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_6";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_6":
			dialog.text = "我想是这样。 你见到她了吗? ";
			link.l1 = "没有。 她去了伊斯帕尼奥拉岛。 她在这里过得不好, 所以决定去太子港碰碰运气。 在那里, 她店里穿着丝绸。 受过良好教育的女士能给她带来比托尔图加更多的利润... ";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_7";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_7":
			dialog.text = "穿着华丽。 受过教育? 哇, 生活能带给你什么。 但你应该喜欢她们本来的样子。 ";
			link.l1 = "海伦, 别这样。 我没做任何值得你不信任的事。 ";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_8";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_8":
			dialog.text = "没错。 如果你想欺骗我, 你不会这么冷静。 但你应该警告我你的计划, 查尔斯。 ";
			link.l1 = "你说得对, 亲爱的。 但我决定节省时间。 我的错。 ";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_9";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_9":
			dialog.text = "好吧。 现在怎么办, 我们计划航向太子港? ";
			link.l1 = "拉维加。 别惊讶, 海伦.美丽星辰夫人过得不好。 她需要贷款才能把生意搬到太子港, 所以决定向马库斯借钱。 如果我们赶紧, 我们可以在那里抓住她。 所以不要浪费一分钟。 ";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_NaLaVega":
			DialogExit();
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) 
			{
				AddLandQuestMark(characterFromId("Terrax"), "questmarkmain");
				QuestSetCurrentNode("Terrax", "PZ_1");
			}
			else 
			{
				AddLandQuestMark(characterFromId("Vensan"), "questmarkmain");
				QuestSetCurrentNode("Vensan", "PZ_1");
			}
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			Island_SetReloadEnableGlobal("Tortuga", true);
			bQuestDisableMapEnter = false;
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				sld = CharacterFromID("Mary");
				AddPassenger(pchar, sld, false);
				ReturnOfficer_Mary();
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				sld = CharacterFromID("Helena");
				AddPassenger(pchar, sld, false);
				ReturnOfficer_Helena();
			}
			if (!CheckAttribute(pchar, "questTemp.PZ_PredupredilNashuDevushku")) AddQuestRecord("PZ", "31");
		break;
		
		case "PZ_KlemanLebren_7":
			dialog.text = "真不敢相信像你这样的混蛋和你的乌合之众打败了我们! ";
			link.l1 = "你... ";
			link.l1.go = "PZ_KlemanLebren_8";
		break;
		
		case "PZ_KlemanLebren_8":
			dialog.text = "哦, 你认出我了? ";
			link.l1 = "我们见过吗? ";
			link.l1.go = "PZ_KlemanLebren_9";
		break;
		
		case "PZ_KlemanLebren_9":
			dialog.text = "什么? ! 你他妈在开玩笑吗? ! ";
			link.l1 = "我不记得我遇到的所有不文明的混蛋。 你最好告诉我们谁派你来杀我们。 或者也许他们只是想摆脱你? ";
			link.l1.go = "PZ_KlemanLebren_10";
		break;
		
		case "PZ_KlemanLebren_10":
			dialog.text = "我不会对像你这样的人说任何话。 你以为你自己很了不起! 等我们在这里稍作休息后, 看看你还能不能再撑住。 ";
			link.l1 = "太可惜了。 你很恶心, 但我本可以把你送到另一个岛上。 现在我只能送你到另一边。 ";
			link.l1.go = "PZ_KlemanLebren_11";
		break;
		
		case "PZ_KlemanLebren_11":
			pchar.questTemp.PZ.HeavyFrigateAbordage = true; // 标记 - 进行了登船战斗
			
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PZ_Tichingitu_11":
			dialog.text = "叫我吗, 船长? ";
			link.l1 = "是的, 伙计。 报告损伤情况。 ";
			link.l1.go = "PZ_Tichingitu_12";
		break;
		
		case "PZ_Tichingitu_12":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "玛丽";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "海伦";
			dialog.text = "有一场猛烈的风暴。 船在嘎吱作响, 裂开发出声响; 摇晃得很厉害。 ";
			link.l1 = "是的, 我注意到了, 蒂钦吉图, 我的朋友。 我和" + sStr + "要上岸。 你负责留守。 立即开始 repairs —在风暴平息前, 去造船厂没用。 此外, 我们不会在这里久留。 ";
			link.l1.go = "PZ_Tichingitu_13";
		break;
		
		case "PZ_Tichingitu_13":
			dialog.text = "我会让一切好转的。 ";
			link.l1 = "太好了, 谢谢。 那我们就放心去镇上了。 ";
			link.l1.go = "PZ_Tichingitu_14";
		break;
		
		case "PZ_Tichingitu_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "PZ_PoP_Rain_4", -1);
		break;
		
		case "PZ_Matros_1":
			dialog.text = "船长先生? 很荣幸。 但这种时候您通常会找阿隆索。 如果可以问的话, 一切都好吗? ";
			link.l1 = "是的, 一切都好。 但我们的阿隆索更擅长破坏, 而不是修理任何东西。 从每一层意义上来说。 船的情况有多糟? ";
			link.l1.go = "PZ_Matros_2";
		break;
		
		case "PZ_Matros_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "玛丽";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "海伦";
			dialog.text = "即使我们没有沉没, 阿隆索也会告诉您情况很糟糕。 您提到了 repairs —我们要开始吗? ";
			link.l1 = "是的, 做你能做的。 但不要计划全面长期的工作 —我在镇上办完事后, 我们很快就会起锚。 我和" + sStr + "不会在那里, 所以如果发生任何事, 你自己做决定。 一切听从阿隆索的。 ";
			link.l1.go = "PZ_Matros_3";
		break;
		
		case "PZ_Matros_3":
			dialog.text = "遵命, 船长先生。 ";
			link.l1 = "放松。 ";
			link.l1.go = "PZ_Matros_4";
		break;
		
		case "PZ_Matros_4":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			Island_SetReloadEnableGlobal("Hispaniola2", true);
			bQuestDisableMapEnter = false;
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "PZ_PoP_Rain_4", -1);
		break;
		
		case "PZ_AnriTibo_1":
			dialog.text = "问候您, 先生! 欢迎来到太子港。 ";
			link.l1 = "也祝你日安, 先生。 你是谁, 我为何受此欢迎? 我不想在这种雨天和风暴后进行长谈。 ";
			link.l1.go = "PZ_AnriTibo_2";
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_PoP_ChangShin", "Mei_Shin", "woman", "towngirl2", 30, FRANCE, 0, false, "quest"));
			FantomMakeCoolFighter(sld, 30, 80, 80, "blade_41", "", "", 0);
			sld.name = "张";
			sld.lastname = "欣";
			ChangeCharacterAddressGroup(sld, "PortPax_town", "goto", "goto16");
			EquipCharacterByItem(sld, "blade_41");
			GiveItem2Character(sld, "cirass8");
			EquipCharacterByItem(sld, "cirass8");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload8_back", "none", "", "", "", -1);
		break;
		
		case "PZ_AnriTibo_2":
			dialog.text = "哦, 我不会占用您太多时间, 德.莫尔先生。 ";
			link.l1 = "我认识你吗? ";
			link.l1.go = "PZ_AnriTibo_3";
		break;
		
		case "PZ_AnriTibo_3":
			dialog.text = "哦, 不, 但整个群岛都知道您是谁。 啊, 我太没礼貌了! 亨利.蒂博, 为您效劳。 我是德.穆萨克大人的信使。 他一发现您的船, 就命令我向您致以最热烈的欢迎, 先生。 ";
			link.l1 = "嗯, 这就解释了很多。 很高兴认识您, 蒂博先生。 ";
			link.l1.go = "PZ_AnriTibo_4";
		break;
		
		case "PZ_AnriTibo_4":
			dialog.text = "我也很荣幸, 德.莫尔先生! 请跟我来。 像您这样身份的人及其美丽的同伴被困在这家臭酒馆里是不合适的。 大人已在城里为您分配了一所房子, 并指示我全方位协助您。 请别忘了事后向潘西大人转达他的最良好祝愿。 ";
			link.l1 = "实际上, 我的差事需要保密。 你知道, 蒂博先生, 我认为... ";
			link.l1.go = "PZ_AnriTibo_5";
		break;
		
		case "PZ_AnriTibo_5":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) StartInstantDialog("Helena", "PZ_HelenaPortPax1", "Quest\CompanionQuests\Longway.c");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) StartInstantDialog("Mary", "PZ_MaryPortPax1", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_HelenaPortPax1":
			dialog.text = "查尔斯。 我很少求你什么, 更不会打断你, 但我们能利用他们的提议吗? 我受够了在雨中淋湿。 我还觉得恶心头晕。 ";
			link.l1 = "呵呵, 你确定是因为雨吗? ";
			link.l1.go = "PZ_HelenaPortPax2";
		break;
		
		case "PZ_HelenaPortPax2":
			dialog.text = "住嘴, 查尔斯! 不管怎样, 我想休息。 在一张大床上, 没有海浪。 ";
			link.l1 = "好吧。 我们擦干身子, 休息一下, 然后马上回到正事上。 ";
			link.l1.go = "PZ_AnriTibo_6";
		break;
		
		case "PZ_MaryPortPax1":
			dialog.text = "我们能在这房子里休息一下吗? 我感觉不舒服, 而且我也... 累了, 查尔斯。 好吧。 ";
			link.l1 = "玛丽, 亲爱的, 我明白, 但也许我们应该去酒馆。 这整件事闻起来很糟糕, 不是吗? ";
			link.l1.go = "PZ_MaryPortPax2";
		break;
		
		case "PZ_MaryPortPax2":
			dialog.text = "我能出什么事? 这甚至不是托尔图加。 ";
			link.l1 = "这正是我害怕的。 ";
			link.l1.go = "PZ_MaryPortPax3";
		break;
		
		case "PZ_MaryPortPax3":
			dialog.text = "求你了? 如果有什么事, 我会在房间里设置防御 —就像... 以前那样, 好吗。 你比任何人都了解我, 查尔斯, 所以你知道我能应付。 ";
			link.l1 = "好吧, 好吧。 希望这不会像以前那样。 ";
			link.l1.go = "PZ_AnriTibo_6";
		break;
		
		case "PZ_AnriTibo_6":
			StartInstantDialog("Tibo", "PZ_AnriTibo_7", "Quest\CompanionQuests\Longway.c");
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) ReturnOfficer_Mary();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) ReturnOfficer_Helena();
		break;
		
		case "PZ_AnriTibo_7":
			dialog.text = "我就知道您会改变主意, 先生! 关于您的担忧, 我完全理解。 但是, 您看, 潘西大人和总督是老朋友, 因此您在我们镇上是受欢迎的客人, 德.莫尔先生! ";
			link.l1 = "哦, 好吧... 那么, 带我们去房子吧。 ";
			link.l1.go = "PZ_AnriTibo_8";
		break;
		
		case "PZ_AnriTibo_8":
			dialog.text = "当然, 先生! 请跟我来。 ";
			link.l1 = "谢谢你。 ";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_GoToTiboHouse");
		break;
		
		case "PZ_AnriTibo_9":
			dialog.text = "先生, 总督在等您。 他请您尽快去见他 —他想私下和您谈谈。 ";
			link.l1 = "他已经知道了吗? ";
			link.l1.go = "PZ_AnriTibo_10";
		break;
		
		case "PZ_AnriTibo_10":
			pchar.questTemp.PZ.PortPaxMayorTalk = true; // 与总督谈话的标记
			
			dialog.text = "当然, 他知道! 这就是为什么他在等您。 让您的爱人甜甜地睡吧, 同时您去见德.穆萨克先生。 一场风暴不会阻止著名的查尔斯.德.莫尔, 对吧? 但大人, 如您所知, 在预约之间没有太多时间可以浪费... ";
			link.l1 = "嗯, 这是真的, 蒂博先生。 ";
			link.l1.go = "PZ_AnriTibo_11";
			
			for (i=1; i<=2; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("PZ_PoP_Escort_"+i, "sold_fra_"+(rand(7)+1), "man", "man", sti(pchar.rank), FRANCE, -1, true, "soldier"));
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
			}
		break;
		
		case "PZ_AnriTibo_11":
			StartInstantDialog("PZ_PoP_Escort_1", "PZ_AnriTibo_12", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_AnriTibo_12":
			dialog.text = "我们会为您带路, 船长。 ";
			link.l1 = "哦, 所以我甚至有荣誉护卫... 好吧, 带路。 ";
			link.l1.go = "PZ_AnriTibo_13";
		break;
		
		case "PZ_AnriTibo_13":
			DoQuestReloadToLocation("PortPax_town", "reload", "houseF1", "PZ_PoP_EscortToGuber");
		break;
		
		case "PZ_Longway_71":
			dialog.text = "船长阁下! ";
			link.l1 = "朗威! 到船上! 现在! ";
			link.l1.go = "PZ_Longway_72";
		break;
		
		case "PZ_Longway_72":
			dialog.text = "但我看到长兴了! ";
			link.l1 = "什么? ! 在哪里? 什么时候? 她在你的船上吗? ";
			link.l1.go = "PZ_Longway_73";
		break;
		
		case "PZ_Longway_73":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "玛丽";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "海伦";
			dialog.text = "不! 在城里, 朗威从远处看到了她。 没时间追上了 —她正在登上一艘刚刚起航的大帆船! ";
			link.l1 = "我们会追上那艘大帆船! 但告诉我 —你在任何地方见过" + sStr + "吗? ";
			link.l1.go = "PZ_Longway_74";
		break;
		
		case "PZ_Longway_74":
			dialog.text = "没有! 发生什么事了? ";
			link.l1 = "是的, 发生了事情! 她有危险! 你见过勒瓦瑟的侄子吗? 名叫亨利.蒂博! 讨厌的。 瘦弱的。 长头发的小胡子年轻人! ";
			link.l1.go = "PZ_Longway_75";
		break;
		
		case "PZ_Longway_75":
			dialog.text = "(用普通话) 你不需要谈论可笑的胡子, 船长... (用蹩脚的法语) 我看到他了! 他和雇佣兵也登上了同一艘大帆船。 ";
			link.l1 = "我们立即追击! ";
			link.l1.go = "PZ_Longway_76";
		break;
		
		case "PZ_Longway_76":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "玛丽";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "海伦";
			dialog.text = "您的船磨损得很厉害, 船长阁下! ";
			link.l1 = "我不在乎! " + sStr + "的生命危在旦夕! ";
			link.l1.go = "PZ_Longway_77";
		break;
		
		case "PZ_Longway_77":
			if (CheckAttribute(pchar, "questTemp.PZ.LongwayMayfang"))
			{
				dialog.text = "我的...'你的美凤'会带我们通过! ";
				link.l1 = "哦, 她会的! 快点! ";
				link.l1.go = "PZ_Longway_78";
			}
			else
			{
				dialog.text = "不要让我们陷入自杀式攻击。 使用您之前提供给我的船! ";
				link.l1 = "好主意, 朗威! 我们快点! ";
				link.l1.go = "PZ_Longway_78";
			}
		break;
		
		case "PZ_Longway_78":
			DialogExit();
			AddDialogExitQuestFunction("PZ_Longway_78");
		break;
		
		case "PZ_RobertMartin_8":
			dialog.text = "又是你... 我就知道我应该拒绝, 让别人带走你的女孩。 ";
			link.l1 = "她在哪里? ! 告诉我! 不... 闭嘴。 你只会在船舱里, 戴着镣铐说话! 听到了吗? ! ";
			link.l1.go = "PZ_RobertMartin_9";
		break;
		
		case "PZ_RobertMartin_9":
			dialog.text = "... ";
			link.l1 = "她的刀刃。 如果你现在不开始唱歌, 我就用它把你切成碎片。 ";
			link.l1.go = "PZ_RobertMartin_10";
			/*RemoveAllCharacterItems(npchar, true);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) GiveItem2Character(pchar, "blade_31");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) GiveItem2Character(pchar, "pirate_cutlass");*/
		break;
		
		case "PZ_RobertMartin_10":
			dialog.text = "你... 你他妈疯了! ..";
			link.l1 = "现在你即将看到我令人不快的一面... ";
			link.l1.go = "PZ_RobertMartin_11";
		break;
		
		case "PZ_RobertMartin_11":
			DialogExit();
			LAi_ReloadBoarding();
		break;
		
		case "PZ_RobertMartin_13":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "玛丽";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "海伦";
			dialog.text = "就这样? ";
			link.l1 = "我再问你一次! " + sStr + "在哪里? ! 中国女人在哪里? ! 亨利.蒂博在哪里? ! ";
			link.l1.go = "PZ_RobertMartin_14";
			LAi_ActorAnimation(npchar, "beatmarten_idle_1", "", 0.3);
		break;
		
		case "PZ_RobertMartin_14":
			dialog.text = "(吐血) 你打得像个女孩。 ";
			link.l1 = "你这个婊子! 我会把每一个字都从你嘴里打出来! ";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DoprosRobertMartin_Trum_6");
			LAi_ActorAnimation(npchar, "beatmarten_idle_1", "", 0.3);
		break;
		
		case "PZ_RobertMartin_16":
			dialog.text = "可悲。 尽管... 我会说。 为什么不呢, 哈哈。 他们都在另一艘船上, 就在去托尔图加的路上。 你太晚了。 ";
			link.l1 = "如果她头上掉了一根头发... ";
			link.l1.go = "PZ_RobertMartin_17";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "beatmarten_idle_2", "", 0.3);
			locCameraFromToPos(-2.80, 7.72, 6.77, true, 1.00, 5.13, 7.23);
		break;
		
		case "PZ_RobertMartin_17":
			dialog.text = "那是谁的错? ! 你杀了埃德加多.索塔! 勒瓦瑟生平第一次想尝尝女孩的滋味, 却没有马上得到! 我们的船员第一次未能执行他的直接命令! 这个人可以像魔鬼一样可怕... ";
			link.l1 = "那我会比魔鬼更可怕, 如果你不告诉我我想知道的, 就给你一点个人的地狱, 听到了吗? ! ";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) link.l1.go = "PZ_RobertMartin_Mary_1";
			else link.l1.go = "PZ_RobertMartin_Helena_1";
			//if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) link.l1.go = "PZ_RobertMartin_Helena_1";
		break;
		
		case "PZ_RobertMartin_Mary_1":
			dialog.text = "我不在乎你的悲伤 - 从你那双疯狂的眼睛来看, 我反正也是个死人。 不过, 德.莫尔, 我得给你一些 credit。 ";
			link.l1 = "你到底在说什么? ";
			link.l1.go = "PZ_RobertMartin_Mary_2";
		break;
		
		case "PZ_RobertMartin_Mary_2":
			dialog.text = "勒瓦瑟喜欢金发女郎。 但我一直更喜欢红发女郎, 就像你一样, 呵呵... 你有一个多么辣的妞! ";
			link.l1 = "你说得对, 你活不过今天... ";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DoprosRobertMartin_Trum_7");
		break;
		
		case "PZ_RobertMartin_Helena_1":
			dialog.text = "我不在乎你想要什么。 但让我告诉你勒瓦瑟想要什么 - 漂亮的金发女孩, 哈哈哈哈哈哈哈哈! 首先, 他有她... ";
			link.l1 = "啊 --! ";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DoprosRobertMartin_Trum_7");
		break;
		
		case "PZ_RobertMartin_19":
			dialog.text = "尖叫和殴打一个手无寸铁的人 - 可悲。 这就是你所能做的一切。 你输了, 德.莫尔! 你想知道你什么时候真正输了吗, 你这个可悲的白痴? ";
			link.l1 = "启发我。 但如果我没留下印象, 你会失去一根手指。 或者一只耳朵。 或者你臭嘴里的那些烂牙。 或者别的什么。 选择在你... ";
			link.l1.go = "PZ_RobertMartin_20";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "beatmarten_idle_3", "", 0.3);
			//locCameraFromToPos(-1.75, 14.14, -0.31, true, 1.26, 11.00, -4.00);
			locCameraFromToPos(-2.80, 7.72, 6.77, true, 0.66, 5.00, 8.26);
		break;
		
		case "PZ_RobertMartin_20":
			dialog.text = "呵呵, 我有你没有的东西。 你认为勒瓦瑟不知道潘西那个老狐狸在策划什么反对他吗? 弗朗索瓦知道一切, 一切! 甚至兄弟会的男爵们都不敢挑战他。 而你, 自以为是的家伙, 你做到了。 但是... ";
			link.l1 = "但是什么? ! 你他妈别拖下去! 开始说, 否则我就开始一根一根地掰断你的手指! ";
			link.l1.go = "PZ_RobertMartin_21";
		break;
		
		case "PZ_RobertMartin_21":
			dialog.text = "哈哈, 勇敢的德.莫尔船长! 但好吧。 我。 亨利和那个黄皮肤的女人决定最好在这里摧毁你。 并把它归咎于泰雷克斯, 这样兄弟会的老傻瓜们就会开始另一场战争! 或者也许是德.穆萨克 - 他一直把鼻子伸到不该去的地方... 你知道, 每个人都嘲笑我驾驶大帆船, 但它轻松地度过了风暴, 不像你的破烂。 ";
			link.l1 = "够了! 勒瓦瑟把他的受害者关在哪里? ";
			link.l1.go = "PZ_RobertMartin_22";
		break;
		
		case "PZ_RobertMartin_22":
			dialog.text = "所以你知道他的秘密地方, 地牢? 哦, 是的, 他是真正的地牢大师, 哈哈哈! 但你真的能挑战他吗? 我怀疑。 你想打败野兽? 那就自己成为野兽。 看看你是否能像弗朗索瓦对待那些女孩一样打败我。 就像他很快会对待你的... ";
			if (!CheckAttribute(pchar, "questTemp.PZ_FlagShip"))
			{
				link.l1 = "阿罗 —奥 —松 --!!! ";
				link.l1.go = "PZ_RobertMartin_23";
			}
			else
			{
				link.l1 = "... ";
				link.l1.go = "PZ_LongwayKaznDialog_1";
			}
		break;
		
		case "PZ_RobertMartin_23":
			DialogExit();
			LAi_SetStayType(pchar);
			CharacterTurnByChr(pchar, CharacterFromID("PZ_RobertMartinPlennik"));
			LAi_Fade("PZ_AlonsoKazn", "");
		break;
		
		case "PZ_LongwayKaznDialog_1":
			DialogExit();
			LAi_SetStayType(pchar);
			CharacterTurnByChr(pchar, CharacterFromID("PZ_RobertMartinPlennik"));
			DoQuestCheckDelay("PZ_LongwayKazn_1", 1.0);
		break;
		
		case "PZ_LongwayKaznDialog_2":
			dialog.text = "";
			link.l1 = "我告诉过你别麻烦, 该死的! ..";
			link.l1.go = "PZ_LongwayKaznDialog_3";
		break;
		
		case "PZ_LongwayKaznDialog_3":
			DialogExit();
			LAi_SetStayType(pchar);
			LAi_Fade("PZ_LongwayKazn_3", "");
		break;
		
		case "PZ_LongwayKaznDialog_4":
			dialog.text = "请允许我, 船长阁下。 ";
			link.l1 = "朗威? 允许什么? ";
			link.l1.go = "PZ_LongwayKaznDialog_5";
		break;
		
		case "PZ_LongwayKaznDialog_5":
			dialog.text = "白人折磨身体。 我的人民知道需要先折磨可怜的灵魂, 用一点持续的痛苦逼疯。 你不能不做准备就拿走和折磨。 总是需要特殊的方法。 这里你需要... 凌迟。 ";
			link.l1 = "凌迟? ";
			link.l1.go = "PZ_LongwayKaznDialog_6";
		break;
		
		case "PZ_LongwayKaznDialog_6":
			dialog.text = "是的, 船长阁下。 千刀万剐之死。 ";
			link.l1 = "你疯了吗? ! 脑袋坏了? 你在胡扯什么死法? ! 我需要先让他说话! ";
			link.l1.go = "PZ_LongwayKaznDialog_7";
		break;
		
		case "PZ_LongwayKaznDialog_7":
			dialog.text = "朗威知道, 船长阁下。 朗威知道该做什么。 这个混蛋会告诉我一切。 给我时间... ";
			link.l1 = "时间? 时间? ! 好吧... 做吧。 只是求你, 我恳求你, 从他那里得到一切, 一切! ";
			link.l1.go = "PZ_LongwayKaznDialog_8";
		break;
		
		case "PZ_LongwayKaznDialog_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, CharacterFromID("PZ_RobertMartinPlennik"), "PZ_LongwayKazn_3_1", -1);
		break;
		
		case "PZ_LongwayKaznDialog_9":
			dialog.text = "杀了我, 求你杀了我... 你还想从我这里得到什么? ! ";
			link.l1 = "没什么了。 闭嘴去死吧。 ";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LongwayKazn_11");
		break;//
		
		case "PZ_LongwayKaznDialog_9_1":
			DialogExit();
			sld = CharacterFromID("PZ_RobertMartinPlennik")
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "Shot", "1", 1.5);
			DoQuestCheckDelay("PZ_LongwayKazn_9", 0.9);
		break;
		
		case "PZ_LongwayKaznDialog_10":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "Shot", "1", 1.5);
			DoQuestCheckDelay("PZ_LongwayKazn_9", 0.9);
		break;
		
		case "PZ_LongwayKaznDialog_11":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "玛丽";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "海伦";
			dialog.text = "射击很干净, 船长阁下。 我告诉过你会有效的。 ";
			link.l1 = "是的。 干得好。 那么, 去地牢吧。 升起所有风帆! 设定航向托尔图加。 如果" + sStr + "头上掉了一根头发, 上帝保佑这座该死的城市... ";
			link.l1.go = "PZ_LongwayKaznDialog_12";
		break;
		
		case "PZ_LongwayKaznDialog_12":
			DialogExit();
			AddQuestRecord("PZ", "39");
			pchar.questTemp.PZ_FlagMartinInfo = true;
			AddDialogExitQuestFunction("PZ_FinalKaznOnShip_DlgExit");
		break;
		
		case "PZ_AlonsoKaznDialog_1":
			dialog.text = "我的上帝... 我从未见过或听过您... 像这样, 船长先生。 ";
			link.l1 = "他是你的了, 阿隆索! 去吧, 让我看看宗教裁判所对胡格诺派及其追随者做了什么... 我会看着... 然后你可以对他做任何你想做的事。 ";
			link.l1.go = "PZ_AlonsoKaznDialog_2";
		break;
		
		case "PZ_AlonsoKaznDialog_2":
			dialog.text = "是, 是, 船长先生... ";
			link.l1 = "";
			link.l1.go = "PZ_AlonsoKaznDialog_3";
		break;
		
		case "PZ_AlonsoKaznDialog_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, CharacterFromID("PZ_RobertMartinPlennik"), "PZ_AlonsoKazn_2", -1);
		break;
		
		case "PZ_AlonsoKaznDialog_4":
			dialog.text = "不会花太久, 船长先生... ";
			link.l1 = "看在上帝的份上, 做吧! ";
			link.l1.go = "PZ_AlonsoKaznDialog_5";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("PZ_RobertMartinPlennik"));
			//LAi_ActorAnimation(npchar, "Barman_idle", "1", 5);
		break;
		
		case "PZ_AlonsoKaznDialog_5":
			DialogExit();
			LAi_SetStayType(pchar);
			LAi_FadeToBlackStart();
			DoQuestCheckDelay("PZ_AlonsoKazn_3", 1.5);
		break;
		
		case "PZ_AlonsoKaznDialog_6":
			dialog.text = "起来, 你这个狗屎。 起来, 我说! ";
			link.l1 = "他死了吗? 死了? ! ";
			link.l1.go = "PZ_AlonsoKaznDialog_7";
			CharacterTurnByChr(npchar, CharacterFromID("PZ_RobertMartinPlennik"));
			CharacterTurnByChr(pchar, CharacterFromID("PZ_RobertMartinPlennik"));
		break;
		
		case "PZ_AlonsoKaznDialog_7":
			dialog.text = "看起来是这样, 船长... ";
			link.l1 = "你到底做了什么? ! ";
			link.l1.go = "PZ_AlonsoKaznDialog_8";
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(pchar, npchar);
		break;
		
		case "PZ_AlonsoKaznDialog_8":
			dialog.text = "谁知道这个蠢货会这么虚弱! 他也弄脏了内裤, 肮脏的人渣! 我真该死, 火是不必要的... ";
			link.l1 = "你... 好吧。 把他扔到海里喂鱼。 设定航向托尔图加。 如果需要, 我会把它一块砖一块砖地拆开 —首先是拉罗什, 然后... 如果我没有发现她活着, 上帝保佑我... ";
			link.l1.go = "PZ_AlonsoKaznDialog_9";
		break;
		
		case "PZ_AlonsoKaznDialog_9":
			DialogExit();
			AddQuestRecord("PZ", "38");
			AddDialogExitQuestFunction("PZ_FinalKaznOnShip_DlgExit");
		break;
		
		case "PZ_Norman1":
			dialog.text = "终于。 这个宝座现在是我的了。 在这块岩石上, 我将建造... ";
			link.l1 = "搞什么鬼... 说真的? ";
			link.l1.go = "PZ_Norman2";
		break;
		
		case "PZ_Norman2":
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "马库斯";
			else sTemp = "鲨鱼";
			
			dialog.text = "... 我的教堂。 我现在是罗马教皇。 不要在上帝的房子里发誓! ";
			link.l1 = "而我还以为... 好吧, 教皇陛下, 您能好心告诉您的信徒" + sTemp + "现在在哪里吗? ";
			link.l1.go = "PZ_Norman3";
		break;
		
		case "PZ_Norman3":
			dialog.text = "他正在进行神圣的使命。 可以说是一次新的十字军东征。 他要从恶人那里拿走钱, 带给我。 ";
			link.l1 = "给你, 对。 他提到什么时候回来吗? ";
			link.l1.go = "PZ_Norman4";
		break;
		
		case "PZ_Norman4":
			NextDiag.TempNode = "PZ_NormanBlock";
			
			dialog.text = "一个月后。 也许稍晚一点。 我在等他和我们其余的教众回来。 ";
			link.l1 = "所以他真的在海上。 我最好在染上你得的病之前离开。 ";
			link.l1.go = "Exit";
		break;
		
		case "PZ_NormanBlock":
			NextDiag.TempNode = "PZ_NormanBlock";
			
			dialog.text = "我将在圣火中净化他们所有人... ";
			link.l1 = "你的头需要净化一下... ";
			link.l1.go = "Exit";
		break;
		
		case "PZ_HelenaIslaTesoro1":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				// 哦, 这是个多么大的权宜之计, 嗯... 
				sld = characterFromId("Mary");
				if (sld.location != "Pirates_townhall")
				{
					if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "和马库斯一起";
					else sTemp = "和史蒂夫一起";
					
					dialog.text = "查尔斯! 我能为你做什么? ";
					link.l1 = "你好, 海伦! 我想和" + sTemp + "谈谈。 他在楼上吗? 还是在酒馆里? ";
					link.l1.go = "PZ_HelenaIslaTesoroGood1";
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "马库斯";
					else sTemp = "史蒂夫";
					
					dialog.text = "查尔斯! 还有... 啊, 真是个惊喜。 我能为你们俩做什么? ";
					link.l1 = "你好, 海伦。 " + sTemp + "在哪里? ";
					link.l1.go = "PZ_HelenaIslaTesoroGoodMaryHere1";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "马库斯";
				else sTemp = "鲨鱼";
				
				dialog.text = TimeGreeting() + ", 查尔斯。 什么风把你吹来了? ";
				link.l1 = TimeGreeting() + ", 海伦。 我在找" + sTemp + "。 你知道他在哪里吗? ";
				link.l1.go = "PZ_HelenaIslaTesoroBad1";
			}
		break;
		
		case "PZ_HelenaIslaTesoroGood1":
			dialog.text = "他出去了, 但恐怕他要离开很长时间 —确切地说是出海了。 ";
			link.l1 = "该死。 发生什么事了吗? 他说什么时候回来吗? ";
			link.l1.go = "PZ_HelenaIslaTesoroGood2";
		break;
		
		case "PZ_HelenaIslaTesoroGood2":
			dialog.text = "他没说, 但没什么严重的 —像往常一样, 他有了好线索。 他通常一个月回来, 最多两个月。 我知道这是怎么回事, 有时我自己也想念船甲板... ";
			link.l1 = "你总是可以去海上。 有时一起去会很好 —你在'彩虹号'上, 我在... ";
			link.l1.go = "PZ_HelenaIslaTesoroGood3";
		break;
		
		case "PZ_HelenaIslaTesoroGood3":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroGoodBlock";
			
			dialog.text = "会的。 但你的... 女朋友可能不会欣赏。 而且我不想成为电灯泡。 ";
			link.l1 = "咳咳, 对不起, 海伦, 我不是有意冒犯你。 谢谢你的聊天。 回头见。 ";
			link.l1.go = "Exit";
		break;
		
// Синистра, нe забудь снять эту заглушку и вeрнуть дeфолтную послe этого этапа, плиз
		case "PZ_HelenaIslaTesoroGoodBlock":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroGoodBlock";
			
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "马库斯";
			else sTemp = "史蒂夫";
			
			dialog.text = "查尔斯, 你回来了。 还有什么我能帮你的吗? ";
			link.l1 = "不, 谢谢, 海伦。 只是想看看" + sTemp + "有没有出现。 ";
			link.l1.go = "Exit";
		break;
		
		case "PZ_HelenaIslaTesoroBad1":
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "泰克斯";
			else sTemp = "史蒂文";
			
			dialog.text = "如果你来找我, 我会很惊讶。 至于" + sTemp + ", 他出海了。 ";
			link.l1 = "哦, 真的吗? 他告诉你他什么时候回来吗? ";
			link.l1.go = "PZ_HelenaIslaTesoroBad2";
		break;
		
		case "PZ_HelenaIslaTesoroBad2":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroBadBlock";
			
			dialog.text = "显然, 他厌倦了经营这个污水坑, 想提醒自己他仍然是一艘船的船长。 这不是第一次了。 他通常一个月后回来, 也许一个半月。 ";
			link.l1 = "该死, 所以男爵们并不总是像那样一动不动? 谢谢你, 海伦。 再见。 ";
			link.l1.go = "Exit";
		break;
		
		// Синистра, нe забудь снять эту заглушку и вeрнуть дeфолтную послe этого этапа, плиз
		case "PZ_HelenaIslaTesoroBadBlock":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroBadBlock";
			
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "马库斯";
			else sTemp = "史蒂文";
			
			dialog.text = "" + sTemp + "还没回来, 查尔斯";
			link.l1 = "我知道了, 只是问问。 ";
			link.l1.go = "Exit";
		break;
		
		case "PZ_HelenaIslaTesoroGoodMaryHere1":
			dialog.text = "他是个自由人, 不是吗? 他想什么时候出海就什么时候出海。 ";
			link.l1 = "他当然可以。 那么, 他在哪里? ";
			link.l1.go = "PZ_HelenaIslaTesoroGoodMaryHere2";
		break;
		
		case "PZ_HelenaIslaTesoroGoodMaryHere2":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroGoodMaryHereBlock";
			
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "马库斯";
			else sTemp = "鲨鱼";
			
			dialog.text = "但是查尔斯, 如果他不在岛上, 他就去掠夺西班牙人了。 现在, 如果你不介意, 我有很多事情要做。 时不时来看看 —通常, " + sTemp + "大约一个月后回来, 有时会晚一点。 ";
			link.l1 = "好吧, 海伦, 谢谢你。 我们会忙起来的。 ";
			link.l1.go = "Exit";
		break;
		
		// Синистра, нe забудь снять эту заглушку и вeрнуть дeфолтную послe этого этапа, плиз
		case "PZ_HelenaIslaTesoroGoodMaryHereBlock":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroGoodMaryHereBlock";
			
			dialog.text = "我现在没心情。 也许改天再来吧, 查尔斯? ";
			link.l1 = "当然, 海伦。 抱歉打扰你。 保重。 ";
			link.l1.go = "Exit";
		break;
		
		case "PZ_Longway_81":
			if (CheckAttribute(pchar, "questTemp.PZ_FlagMartinInfo"))
			{
				dialog.text = "我们到位了, 船长阁下。 你还记得路吗? ";
				link.l1 = "当然, 朗威。 只希望我们不要在那个该死的地牢里迷路... ";
				link.l1.go = "PZ_Longway_FlagMartinInfo_1";		//Sinistra
			}
			else
			{
				dialog.text = "我们到位了, 船长阁下。 你有计划吗? ";
				link.l1 = "我还在想... 怎么, 你有什么主意? ";
				link.l1.go = "PZ_Longway_NotMartinInfo_1";		//Rebbebion
			}
			DelLandQuestMark(npchar);
			LAi_SetCheckMinHP(npchar, 1, true, "");		//第6章给朗威永生
			
			LocatorReloadEnterDisable("Tortuga_town", "houseS4", false);
		break;
		
		case "PZ_Longway_NotMartinInfo_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "玛丽";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "海伦";
			dialog.text = "嗯, 我想如果我们冲到长兴... ";
			link.l1 = "朗威... 我理解你有多想见你的妹妹, 但" + sStr + "现在正处于生命危险之中, 这可不是比喻! 你需要明白, 救她是首要任务! ";
			link.l1.go = "PZ_Longway_NotMartinInfo_2";
		break;
		
		case "PZ_Longway_NotMartinInfo_2":
			dialog.text = "船长阁下, 我怀疑你是否真的明白, 这十年来我经历了什么。 我现在正在经历什么。 ";
			link.l1 = "你知道, 在某种程度上, 我明白。 我的兄弟被关在监狱里。 虽然他们还没有伤害他, 但随时都可能对他为所欲为。 ";
			link.l1.go = "PZ_Longway_NotMartinInfo_3";
		break;
		
		case "PZ_Longway_NotMartinInfo_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "玛丽";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "海伦";
			dialog.text = "但是如果你只需要营救" + sStr + "小姐, 你会去哪里呢? ";
			if (CheckAttribute(pchar, "questTemp.FMQT.GiveDiamonds") && !CheckAttribute(pchar, "questTemp.FMQT_ObchistilSunduk"))
			{
				link.l1 = "有一个地方... 一个人... 但别为这事操心, 朗威 - 我必须自己处理。 ";
				link.l1.go = "PZ_GoMarceline1";
			}
			link.l2 = "说实话, 我甚至不知道去哪里。 如果我到处乱打听, 我会引起注意, 然后" + sStr + "就真的完了。 所以... 我只是不知道。 ";
			link.l2.go = "PZ_GoTogether1";
		break;
		
		case "PZ_GoMarceline1":
			dialog.text = "什么? 为什么? ";
			link.l1 = "他们不会让你进去的 - 那是上流社会, 该死的。 所以, 我自己去。 与此同时, 你去找你的妹妹。 我一有空就会加入你。 祝你好运, 朗威! ";
			link.l1.go = "PZ_GoMarceline2";
			RemovePassenger(pchar, npchar);
		break;
		
		case "PZ_GoMarceline2":
			dialog.text = "好的! 谢谢你, 船长阁下。 也祝你好运! ";
			link.l1 = "哦, 谢谢 - 我今天非常需要。 我们都需要。 ";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_MarcelineLongwayGo");
		break;
		
		case "PZ_GoTogether1":
			dialog.text = "船长阁下... ";
			link.l1 = "没关系。 我们去找你的妹妹, 朗威。 如果我们现在分开 - 我们就死定了。 让我们赶紧去找你的妹妹, 看看勒瓦瑟的巢穴在哪里。 然后我们再一起去 - 我现在需要所有能得到的帮助。 我希望我们不会太晚。 ";
			link.l1.go = "PZ_GoTogether2";
		break;
		
		case "PZ_GoTogether2":
			dialog.text = "我们不会太晚的, 船长阁下。 让我们不要再拖延或浪费时间争论了。 让我们去长兴! ";
			link.l1 = "你说得对, 我们赶紧走吧。 ";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TogetherLongwayGo");
		break;
		
		case "PZ_FrenchSoldier1":
			dialog.text = "你到底要去哪里? 你知道那扇门通向哪里吗? ";
			link.l1 = "我非常清楚。 我去那里是有正事, 不是出于好奇或偷窃。 ";
			link.l1.go = "PZ_FrenchSoldier2";
		break;
		
		case "PZ_FrenchSoldier2":
			dialog.text = "什么正事? 勒瓦瑟夫人现在没空。 再说, 她是个已婚女人 - 人们不应该在她的住所附近晃荡。 ";
			link.l1 = "已婚, 好吧。 但她确实时不时会举行招待会, 包括私人招待会。 现在就是这样一个时候。 她在等我, 我很忙。 ";
			link.l1.go = "PZ_FrenchSoldier3";
		break;
		
		case "PZ_FrenchSoldier3":
			dialog.text = "如果是这样, 她会通知我的。 ";
			link.l1 = "我是一种特殊的客人 - 那种不需要通报的客人。 ";
			link.l1.go = "PZ_FrenchSoldier4";
		break;
		
		case "PZ_FrenchSoldier4":
			dialog.text = "是的, 那种会让大人命令枪毙我的客人。 或者夫人自己会把我剥皮。 ";
			link.l1 = "我以前是马塞尔琳夫人的客人。 我向你保证, 事后什么事都不会发生在你身上, 士兵。 ";
			link.l1.go = "PZ_FrenchSoldier5";
		break;
		
		case "PZ_FrenchSoldier5":
			dialog.text = "当然, 睁一只眼闭一只眼, 让每个人都进来 - 那是城市卫兵的工作。 ";
			link.l1 = "我没时间和你这个顽固的笨蛋纠缠... ";
			link.l1.go = "Exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_FrenchSoldierFight");
		break;
		
		case "PZ_Marceline1":
			dialog.text = "你... ";
			// 开始检查通过"几乎像家一样"的结果
			switch (pchar.questTemp.FMQT.Marceline)
			{
				// 分了钻石并"冷却了性交, 碳塑料" (c)
				case "Fuck":
					link.l1 = "哦, 是的, 夫人。 你的骑士很高兴再次见到你。 我看你见到我很惊讶。 这次见面的喜悦... 不是相互的吗? ";
					link.l1.go = "PZ_MarcelineFuck1";
				break;
				
				// 分了钻石, 没有性交和碳塑料
				case "NoFuck":
					link.l1 = "是的, 我做到了。 我意识到我可能不是这个岛上最英俊或最有价值的人, 正如你上次见面时提到的, 但至少你知道我是个诚实的人。 听我说, 夫人 - 我不会占用你太多... 宝贵的时间。 ";
					link.l1.go = "PZ_MarcelineNoFuck1";
				break;
				
				// "在中间某个地方相遇" (c)
				case "Deception":
					link.l1 = "嘘, 看在上帝的份上, 别再尖叫了, 夫人。 我来这里不是为了报复你欺骗你的骑士并带着龙的宝藏逃跑。 我向你保证, 如果我想杀你, 我只会开枪然后逃命。 毕竟这是托尔图加! 但我想你已经知道那样做有失我的身份。 ";
					link.l1.go = "PZ_MarcelineDeception1";
				break;
			}
		break;
		
		case "PZ_MarcelineFuck1":
			dialog.text = "哦, 不! 我只是觉得... 好吧, 没关系! 你知道, 恶毒的舌头在散布关于我的肮脏谣言 - 一个可怜的女人, 即使她想, 也不能伤害任何人, 也不能保护自己免受敌人的伤害。 此外, 已经过了这么久... 我以为你是来责备我的, 而不是带着善意。 我很高兴我错了。 当你被敌人包围时, 生活是艰难的。 ";
			link.l1 = "我怎么会呢? 即使我听到了这样的话, 我也不会相信一个字。 但你是对的 - 我不是仅仅为了见你而来。 虽然我很高兴见到你。 我知道这听起来不寻常, 但是... 这次你的骑士需要你的帮助, 夫人。 ";
			link.l1.go = "PZ_Marceline2";
		break;
		
		case "PZ_MarcelineNoFuck1":
			dialog.text = "你比我想象的要敏感得多。 然而, 你也并非没有过错, 德.莫尔先生 - 我原以为你会更... 文雅。 事实上... 要么你一直都是这样, 要么群岛已经腐蚀了你。 你应该重新学习如何与女士交谈。 但你是对的 - 你是个诚实的人, 尽管... 简单。 ";
			link.l1 = "而你是一个骄傲且报复心强的女人。 你的眼神。 言语和... 行动都暴露了这一点。 所以如果有人能理解我, 那就是你。 就像我曾经理解你一样。 所以让我们不要再纠结于过去了。 你能帮助我吗, 夫人? ";
			link.l1.go = "PZ_Marceline2";
		break;
		
		case "PZ_MarcelineDeception1":
			dialog.text = "哦... 我承认当时我对你不够友善。 但那只是因为我还不完全确定你, 仅此而已! 你会把所有的钻石都从我身边夺走吗? 或者把我的丈夫带到那里, 说你从我们的仆人那里得知我偷了他的东西, 否认你参与其中? 毕竟, 每个人都在寻求他的青睐, 而不是像我这样的可怜女人... 现在我意识到我错怪你了。 请接受我的道歉... 我的骑士。 ";
			link.l1 = "我不知道现在这些是否真诚。 但这并不重要。 我需要你的帮助, 马塞尔琳夫人。 这是生死攸关的事情。 请不要拒绝。 ";
			link.l1.go = "PZ_Marceline2";
		break;
		
		case "PZ_Marceline2":
			dialog.text = "我的帮助... ? 我当然不是城里最不起眼的女人, 但我的影响力并不像你们所有人想象的那么大。 我是一个统治而不治理的女王。 但我会听你说。 我这个卑微的人能为你做什么? ";
			link.l1 = "我意识到这对你来说是个不愉快的话题, 但我正在寻找你的丈夫, 夫人, 而且越快越好。 事实是... ";
			link.l1.go = "PZ_Marceline3";
		break;
		
		case "PZ_Marceline3":
			dialog.text = "这是个玩笑吗? 他现在不在住所? 那他出差去了。 我帮不了你, 德.莫尔先生。 ";
			link.l1 = "你避开了我的目光。 你知道。 我也知道。 我只是需要到达那里。 请不要假装这是你第一次听说地牢 - 你太聪明了, 不可能不知道。 ";
			link.l1.go = "PZ_Marceline4";
		break;
		
		case "PZ_Marceline4":
			dialog.text = "哦, 我觉得这次谈话会让我多一根白发。 好像我还不够多的第一道皱纹。 你到底对我们所有人做了什么, 弗朗索瓦... ";
			link.l1 = "一根白发只会增添你的高贵, 不会夺走你的美丽。 但一个善良。 无辜的女孩落入了你丈夫的手中。 现在她冒着失去美丽。 健康甚至生命的危险! ... ! 你知道那些被困在那里的人会遭遇什么。 请, 夫人。 马塞尔琳... 帮助你的骑士。 ";
			link.l1.go = "PZ_Marceline5";
		break;
		
		case "PZ_Marceline5":
			dialog.text = "真的不再是我的骑士了, 对吧? 来吧, 我不傻。 但是... 我会帮助你的, 德.莫尔。 毕竟, 这不可能永远持续下去。 总有一天会公开的。 对我来说, 现在重要的是及时以正确的方式脱身。 而且... 我不能让你因我‘丈夫'对你... 熟人所做的一切而遭受永恒的痛苦。 ";
			link.l1 = "我可能不再是你的骑士, 夫人。 但你从一开始就不是我的淑女。 然而, 我会终生感激你。 那么这个地方在哪里? ";
			link.l1.go = "PZ_Marceline6";
		break;
		
		case "PZ_Marceline6":
			dialog.text = "好吧, 我就相信你的话, 查尔斯。 在城市地牢里。 有一个死胡同里有一个大桶, 旁边有一条通道通向这个恶魔的巢穴。 我没往里看。 我只跟踪过他一次, 很久以前。 当我听到那些可怜生物的非人的尖叫时, 我吓坏了。 ";
			link.l1 = "你今天拯救了许多生命, 夫人。 不仅是我亲爱的人, 还有所有那些将来可能落入你丈夫手中的人。 谢谢你。 ";
			link.l1.go = "PZ_Marceline7";
		break;
		
		case "PZ_Marceline7":
			dialog.text = "啊, 别用那些空洞的话来烦我了, 先生。 你要求我做了很多。 而我冒了很大的风险。 现在试着让你新的屠龙之旅成功吧... 我的骑士。 ";
			link.l1 = "我会尽力的。 再见, 马塞尔琳。 ";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_MarcelineOver");
		break;
		
		case "PZ_ElitaShluha_18":
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko") && !CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				dialog.text = "那么, 你是个强盗, 先生... ? 我们不雇佣这样的新女孩; 我们所有人都是自愿来这里的。 我得请你和你的... 同伙离开。 我会确保这个女孩得到治疗 - 否则, 我会向当局报告你! ";
				link.l1 = "我们不是强盗。 但这个女孩比得上任何一个强盗。 她可不是为了好看才带刀的。 她只是受伤了。 这个人是我的朋友, 也是你女主人的兄弟。 所以, 让我们见她。 ";
				link.l1.go = "PZ_ElitaShluha_WithLongwayAndGirl1";
			}
			else
			{
				dialog.text = "很高兴再次见到你, 先生! 但你知道我们这里不接受... 低级别的客人。 即使他们有人担保并付了钱。 尤其是黄皮肤的劳工或黑奴。 恐怕你的朋友得离开。 ";
				link.l1 = "别在你女主人面前这么说。 她也是黄皮肤。 而且这不是劳工, 而是她的兄弟。 你不会妨碍家人团聚, 对吧? ";
				link.l1.go = "PZ_ElitaShluha_WithLongway1";
			}
		break;
		
		case "PZ_ElitaShluha_18_1":
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko") && !CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				dialog.text = "情况越来越糟了。 先是那个疯狂的黄皮肤劳工, 现在又是你。 不, 先生, 我们不会为那些被强迫带到这里的女孩付钱; 她们都是自愿来的。 ";
				link.l1 = "我救了这个女孩, 她永远不会在一个配不上她的地方工作。 你说的劳工? ";
				link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithGirl1";
			}
			else
			{
				dialog.text = "哦, 先生, 你的时机真不好! 我们今天不再接受客人了 - 你自己也能看到这里发生了什么。 ";
				link.l1 = "这就是我来的原因。 是一个黄皮肤的人组织了这一切, 对吧? ";
				link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithoutGirl1";
			}
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithGirl1":
			dialog.text = "是的, 先生, 一个劳工! 我们几乎听不懂他在说什么! 这个衣衫褴褛的人闯进来, 要求见夫人。 他向我们保证他是她的兄弟。 我们叫人来, 但... ";
			link.l1 = "这对他来说不是障碍。 然后呢? ";
			link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithGirl2";
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithGirl2":
			for (i = 1; i <= 4; i++)
			{
				sld = characterFromId("PZ_EliteBrothelMercenary" + i);
				sld.lifeday = 0;
			}
			
			dialog.text = "结果证明, 他没有撒谎。 夫人出来见我们, 认出了他。 事实上, 他们还在她豪华的地方交谈。 ";
			link.l1 = "谁知道他在想什么。 我们进去 - 如果必要的话, 我们会救她。 别大惊小怪 - 这会毁了这个地方的声誉。 ";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_EliteBrothelCreateChangShin");
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithoutGirl1":
			dialog.text = "没错, 先生。 他说他是夫人的兄弟。 ";
			link.l1 = "而你不让他进来... ";
			link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithoutGirl2";
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithoutGirl2":
			dialog.text = "当然不! 夫人穿着优雅, 说话不带口音, 不像那个劳工。 我们试图赶走他, 他却打倒了所有的守卫, 你能想象吗? ! ";
			link.l1 = "我很容易想象。 他现在在哪里? ";
			link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithoutGirl3";
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithoutGirl3":
			for (i = 1; i <= 4; i++)
			{
				sld = characterFromId("PZ_EliteBrothelMercenary" + i);
				sld.lifeday = 0;
			}
			
			dialog.text = "他和夫人还在谈论什么, 但我们听不懂 - 可能是用他们自己的语言。 ";
			link.l1 = "我去找他们。 也许你的夫人需要帮助。 别叫守卫 - 如果这事公开了, 就没人会再来你的门前了。 ";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_EliteBrothelCreateChangShin");
		break;
		
		case "PZ_ElitaShluha_WithLongway1":
			dialog.text = "兄弟? 女主人很有尊严, 这比我能说的关于这个‘兄弟'的话要多得多。 别打扰她的头脑, 也别想用这个劳工来骗她。 把他带走。 ";
			link.l1 = "我告诉过你, 他们很久以前就分开了。 他只是不太幸运。 我们自己会为我们在这里的时间付钱。 现在通知女主人。 ";
			link.l1.go = "PZ_ElitaShluha_WithLongway2";
		break;
		
		case "PZ_ElitaShluha_WithLongway2":
			dialog.text = "她没什么要被你惊动的。 而且我不喜欢你的坚持。 伙计们! 把那个劳工扔出去! 还有他那个被误导的主人! ";
			link.l1 = "该死! 一个妓女竟然如此傲慢! ";
			link.l1.go = "Exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_EliteBrothelFight");
		break;
		
		case "PZ_ElitaShluha_WithLongwayAndGirl1":
			dialog.text = "没门! 让女主人单独和你这奇怪的一伙人在一起? 只有你一个人去, 先生。 而你的... 朋友在外面等着 - 我们这里是个体面的地方。 ";
			link.l1 = "你为什么担心她? 大家都知道她是托尔图加最好的剑客之一。 而且我的朋友比这个镇上的大多数人都要体面。 ";
			link.l1.go = "PZ_ElitaShluha_WithLongwayAndGirl2";
		break;
		
		case "PZ_ElitaShluha_WithLongwayAndGirl2":
			dialog.text = "伙计们! 这里有一个受伤的强盗和一个肮脏的劳工! 他们想从我们女主人那里得到什么! 对付他们! ";
			link.l1 = "多么尽职, 该死的... ";
			link.l1.go = "Exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_EliteBrothelFight");
		break;
		
		case "PZ_ChangShin1":
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			sld = characterFromId("Longway");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto9", "PZ_LongwayTurnToChangShin", -1);
			
			// 现在, 再次检查通过结果。 朗威和我们在一起, 田还在妓院
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				dialog.text = "我猜你是查尔斯.德.莫尔? 还有这个... 哦。 ";
				link.l1 = "而你一定是贝勒.埃托伊尔。 或者我应该说长兴? 是的, 这是你的兄弟。 他已经找了你十多年了。 他和我有很多很多问题要问你。 而且时间不多了。 ";
				link.l1.go = "PZ_ChangShin_WithLongway1";
			}
			// 和朗威。 田一起来
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom") && CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
			{
				dialog.text = "我的天哪, 你活下来了。 你有一个相当不错的守护者, 即使他来得有点晚。 比那个显然认为我是他的守护者, 现在站在你旁边的人要好。 上天眷顾你, 我亲爱的女孩。 ";
				link.l1 = "我看得出你知道。 这样更好 - 不用解释了。 但告诉我, 长兴, 你在笑什么? 你喜欢看着其他女孩受苦, 不是吗? 毕竟是你出卖了她们。 ";
				link.l1.go = "PZ_ChangShin_WithLongwayAndGirl1";
			}
			// 朗威和我们在一起, 田在天堂
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom") && CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "玛丽";
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "海伦";
				dialog.text = "查尔斯.德.莫尔, 对吧? 我听说你想见我。 那么, 什么事困扰着你? 上次你来我们这里的时候不喜欢我们的服务吗? ";
				link.l1 = "我刚从你的另一个地方来, 长兴。 " + sStr + ", 我的爱人, 死了。 我知道你也参与了这件事。 ";
				link.l1.go = "PZ_ChangShin_GirlDied1";
			}
		break;
		
		case "PZ_ChangShin_WithLongway1":
			dialog.text = "长兴... 我已经很久没有听到这个名字了。 已经很久了。 白人... 你们总是很匆忙。 为什么不悠闲地团聚一下呢? 我不在乎, 不过。 我已经多年不再依赖别人了。 你为什么不说话, 我的兄弟? 见到你自己的妹妹不高兴吗? 毕竟你一直在如此执着地寻找我。 ";
			link.l1 = "我们有其他紧急且更重要的事情要处理。 和你的妹妹谈谈, 朗威。 但记住我们还要去哪里。 我们需要赶紧。 而且我也有问题要问她。 ";
			link.l1.go = "PZ_Longway_SisterDialog1";
		break;
		
		case "PZ_Longway_SisterDialog1":
			locCameraFromToPos(0.65, 2.59, -3.06, true, 0.23, 0.34, -5.21);
			
			sld = characterFromId("Longway");
			ChangeCharacterAddressGroup(sld, "Tortuga_brothelElite_room2", "goto", "goto8");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromId("PZ_ChangShin"));
			
			sld = characterFromId("PZ_ChangShin");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromId("Longway"));
			
			dialog.text = "(用普通话)朗威, 嗯? 好吧, 除了名字, 你没怎么变... 张图。 ";
			link.l1 = "(用普通话)但你变了很多, 妹妹。 发生了什么? 你曾经的目光像正午的太阳一样温暖。 现在却冰冷, 什么也不表达, 只有轻蔑。 还有你的声音? 我曾经喜欢让你笑, 听那些银铃般的笑声... 现在却比冬天的angoango还要冷。 而且你穿着他们的衣服。 而且你自己出卖女人, 尽管你曾经被费尔门特洛斯绑架过。 ";
			link.l1.go = "PZ_Longway_SisterDialog2";
		break;
		
		case "PZ_Longway_SisterDialog2":
			dialog.text = "你跑来教训我, 尽管你曾经为罗登堡工作, 他是群岛上最大的恶棍之一? 你以为我不知道你的事? 我一直都知道。 轮不到你来评判我变成了什么样子, 为什么变成这样, 我被误导的哥哥。 ";
			link.l1 = "那么让我知道, 兴! 告诉我。 如果你知道我在群岛上, 为什么在这么多年后你不想见我? 我把我的一生都献给了寻找你... ";
			link.l1.go = "PZ_Longway_SisterDialog3";
		break;
		
		case "PZ_Longway_SisterDialog3":
			dialog.text = "因为你和上天都没有保护我免受最可怕的命运。 然后我意识到, 这个世界上没有人需要任何人。 我们只能依靠自己。 好吧, 如果你想知道, 我会告诉你。 但我会用他的语言说。 我相信他也很想听。 你会说法语, 对吧, 图? ";
			link.l1 = "(用蹩脚的法语): 是的, 我会说那种语言。 ";
			link.l1.go = "PZ_Longway_SisterDialog4";
		break;
		
		case "PZ_Longway_SisterDialog4":
			dialog.text = "哈哈哈哈, 哦, 天哪! 你的口音太可怕了。 不过这不是你的错 - 法语的发音和拼写确实很难。 ";
			link.l1 = "你现在笑得不一样了, 妹妹... ";
			link.l1.go = "PZ_ChangShin_WithLongway3";
		break;
		
		/*case "PZ_Longway_SisterDialog5":
			ReturnOfficer_Longway();
			
			StartInstantDialog("PZ_ChangShin", "PZ_ChangShin_WithLongway3", "Quest\CompanionQuests\Longway.c");
		break;*/
		
		case "PZ_ChangShin_WithLongway3":
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			sld = characterFromId("Longway");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto9", "PZ_LongwayTurnToChangShin", -1);
			dialog.text = "我亲爱的哥哥想知道这些年来我发生了什么。 我想你也听听会很好 - 正如你所说, 你有问题。 所以别担心 - 我会用法语告诉你一切。 ";
			link.l1 = "只告诉我要点 - 朗威给我讲他的人生故事时, 花了好几个小时。 而我现在很匆忙。 ";
			link.l1.go = "PZ_ChangShin_WithLongway4";
		break;
		
		case "PZ_ChangShin_WithLongway4":
			dialog.text = "你要耐心点。 我把这一切都藏在心里一年多了。 如果你打断我, 我就不回答你的任何问题。 ";
			link.l1 = "好吧... 那你说吧。 ";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_ChangShin_WithLongwayAndGirl1":
			dialog.text = "你的礼貌在哪里, 查尔斯.德.莫尔? 我听说你是一个举止优雅。 典型的绅士。 只是谣言, 但实际上... 是个失败者? 我就知道。 而且你错了 - 我同等地恨所有男人和女人。 事实上, 我不信任任何人, 不疑惑, 不期待任何事。 如果我能抓住你, 我会很高兴地捏碎你的睾丸。 但这么多年后听到我的真名, 有点... 令人耳目一新。 ";
			link.l1 = "我是女士的绅士, 不是像你这样的女巫。 而且不管怎样, 考虑到你参与折磨我最关心的人, 你还能期待什么? 我几乎无法控制自己不对你做些什么。 至少为了他。 朗威是我的朋友。 而你是他的家人。 他已经找了你十多年了。 他应该和你谈谈。 ";
			link.l1.go = "PZ_ChangShin_WithLongwayAndGirl2";
		break;
		
		case "PZ_ChangShin_WithLongwayAndGirl2":
			dialog.text = "多么多愁善感。 而我不在乎, 这多么可悲。 但你现在不会轻易逃脱, 对吧, 图? 不是因为杀了你和所有人, 只是因为迟到了一次。 但知道... 我想你确实应该知道。 你认识我时, 我还不是这样, 哥哥。 ";
			link.l1 = "不管你发生了什么... 你总是有选择的, 长兴。 ";
			link.l1.go = "PZ_ChangShin_WithLongwayAndGirl3";
		break;
		
		case "PZ_ChangShin_WithLongwayAndGirl3":
			dialog.text = "你还年轻, 不知道世界是如何运作的, 查尔斯.德.莫尔。 生活中只有一个真正的选择: 生或死。 我想你也应该知道一切。 所以我会用法语讲我的故事。 你会说法语, 对吧, 图? ";
			link.l1 = "带着口音。 但他听得很明白。 你可以开始了。 ";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_ChangShin_GirlDied1":
			dialog.text = "这些年来你在哪里? 伊斯帕尼奥拉岛只有一两天的路程。 她的死也是你的错。 还有你。 你迟到了十多年。 我们的救世主, 我们的守护者。 女人越早学会保护自己越好。 有些人及时学会了, 有些人没有。 还有人没有足够的头脑去学会。 ";
			link.l1 = "小心你接下来要说的每一个字。 我还没有因为我的朋友, 你的兄弟, 把你撕成碎片。 你根本不知道他为你经历了什么。 ";
			link.l1.go = "PZ_ChangShin_GirlDied2";
		break;
		
		case "PZ_ChangShin_GirlDied2":
			dialog.text = "我非常怀疑他经历过任何与我所经历的 remotely 相似的事情。 ";
			link.l1 = "那么告诉我们。 ";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_ChangShin2":
			dialog.text = "好吧, 我能说什么呢, 我当时年轻。 愚蠢。 天真。 而且偏执。 图有没有告诉你, 奥利维里奥.费尔门特洛斯杀了我父母和我之后绑架了我? ";
			link.l1 = "是的。 ";
			link.l1.go = "PZ_ChangShin3";
		break;
		
		case "PZ_ChangShin3":
			dialog.text = "他向我求爱并表白感情, 但我拒绝了他。 就在那时, 他屠杀了我们全家并偷走了我。 然后... ";
			link.l1 = "我能猜到。 ";
			link.l1.go = "PZ_ChangShin4";
		break;
		
		case "PZ_ChangShin4":
			dialog.text = "我希望你能。 然后他又一次热泪盈眶地向我表白, 说这是唯一的办法, 因为我的家人永远不会让我和他走。 ";
			link.l1 = "疯狂... ";
			link.l1.go = "PZ_ChangShin5";
		break;
		
		case "PZ_ChangShin5":
			dialog.text = "呵呵, 这个词可以描述我从那以后的整个人生。 我又拒绝了他。 这种情况持续了一段时间。 但显然, 这不可能永远持续下去, 因为我完全在他的掌控之下。 ";
			link.l1 = "所以确实发生了? ";
			link.l1.go = "PZ_ChangShin6";
		break;
		
		case "PZ_ChangShin6":
			dialog.text = "当然。 他粗暴无情地强迫了我。 虽然这对强奸犯来说从来都不是问题, 但他之前不是还 tearfully 向我表白过他伟大的爱吗? 噗! 显然爱已经消失了。 这一切每天都像例行公事一样继续着。 一开始, 我大喊大叫并反抗, 但后来我停止了 - 反正有什么意义呢... ? ";
			link.l1 = "但费尔门特洛斯得到了应有的下场, 而你最终来到了这里。 这是怎么发生的? ";
			link.l1.go = "PZ_ChangShin7";
		break;
		
		case "PZ_ChangShin7":
			dialog.text = "嗯, 很快他就厌倦了我。 很有趣, 不是吗? 他杀了我和图的父母, 偷走了我, 定期侮辱我, 最后却抛弃了我。 他来到这个群岛, 把我作为奴隶卖给了勒瓦瑟。 ";
			link.l1 = "我不会把这希望加诸我的敌人。 那么你是如何生存下来的? 首先是如何获得自由的? 据我所知, 勒瓦瑟从不放女人出他的藏身之处。 他总是把她们处理掉。 ";
			link.l1.go = "PZ_ChangShin8";
		break;
		
		case "PZ_ChangShin8":
			dialog.text = "现在就是这样。 勒瓦瑟那时不同。 不, 他一直是个禽兽。 但起初, 他偶尔会绑架当地年轻的殖民者, 在他的地下室强奸她们, 并几乎立即处理掉她们, 以避免花钱让她们保持沉默。 那些年里, 他很少把她们关押超过几天。 而对我来说, 从一开始就不同。 ";
			link.l1 = "因为你是奴隶, 对吗? ";
			link.l1.go = "PZ_ChangShin9";
		break;
		
		case "PZ_ChangShin9":
			dialog.text = "正是。 勒瓦瑟的主要欲望不仅仅是身体上的快感。 甚至不是对受害者的一时权力感 - 毕竟他对整个岛屿都有这种权力。 但是... ";
			link.l1 = "... 看着她们崩溃的快感 - 她们的意志。 外表。 声音。 行为。 ";
			link.l1.go = "PZ_ChangShin10";
		break;
		
		case "PZ_ChangShin10":
			dialog.text = "是的。 我看你做了功课, 船长。 但在那方面, 我对他来说并不有趣 - 费尔门特洛斯把我带来时已经崩溃了。 勒瓦瑟并不认为我漂亮 - 他不喜欢亚洲女人。 你知道, 出于某种原因, 这对我影响很大 - 我意识到我有魅力, 但我不认为自己真的漂亮。 当人们告诉我时, 我也不相信。 即使现在, 当我锻炼。 穿丝绸。 喷上香水时。 不是说我需要折磨者的认可, 但是... ";
			link.l1 = "那么, 我再重复一遍我的问题 - 你是如何生存下来的? 一旦他厌倦了一个女人, 他就会处理掉她。 正如你所说, 他一开始就厌倦了你。 ";
			link.l1.go = "PZ_ChangShin11";
		break;
		
		case "PZ_ChangShin11":
			dialog.text = "我想我从一开始就让他感到无聊这一事实起了作用。 还有我是奴隶的事实 - 我无处可去, 无话可说。 几千年来, 女奴一直受到这样的待遇。 他开始思考如何让他和我在一起的时间对他来说‘有趣'。 ";
			link.l1 = "我想这就是他现在这种癖好的起源。 ";
			link.l1.go = "PZ_ChangShin12";
		break;
		
		case "PZ_ChangShin12":
			dialog.text = "正是。 起初是殴打。 吐口水和其他羞辱。 还有嘲弄 - 既嘲笑我的外表, 也嘲笑我的出身。 我的血统。 然后是第一次酷刑 - 刀。 钳子。 煎锅... 这就是为什么我穿得如此严实 - 我全身都是伤疤。 烧伤和 mutilations。 这就是为什么我再也不打算在男人面前脱衣服了。 再也不会了。 然后我终于意识到, 当费尔门特洛斯绑架我时, 我就应该意识到的事情。 ";
			link.l1 = "那是什么? ";
			link.l1.go = "PZ_ChangShin13";
		break;
		
		case "PZ_ChangShin13":
			dialog.text = "我不应该再做一个无助的傀儡。 相反, 我应该掌控自己的生活。 对我来说, 女人只能通过控制周围的男人来改变自己的生活。 ";
			link.l1 = "我不会说勒瓦瑟是可以被控制的。 ";
			link.l1.go = "PZ_ChangShin14";
		break;
		
		case "PZ_ChangShin14":
			dialog.text = "你说得没错。 但小心地影响他是可能的。 勒瓦瑟同样讨厌从一开始就完全服从和争论或恳求。 奉承也是如此 - 显然他意识到自己真的是头猪。 这一点我立刻就意识到了, 付出了相当痛苦的代价。 但是, 当他在又一个晚上的酷刑和暴力之后对一切都满意时, 就可以温和地和他交谈。 我可能不是贵族出身, 但我不缺乏智慧。 ";
			link.l1 = "那你们谈了什么? ";
			link.l1.go = "PZ_ChangShin15";
		break;
		
		case "PZ_ChangShin15":
			dialog.text = "我引起了他的兴趣。 提出了酷刑的想法, 建议最好不要使用哪些酷刑工具, 哪些值得先使用。 当然, 起初他把这些都用在我身上。 但后来... 他开始以自己扭曲的方式尊重我。 他脑子里在想什么? 我试图找出他是如何变成这样的, 但他又把我打个半死。 然后他带来了一个私人医生。 ";
			link.l1 = "这比我已经听到的关于他的事情还要奇怪和恶心。 ";
			link.l1.go = "PZ_ChangShin16";
		break;
		
		case "PZ_ChangShin16":
			dialog.text = "他不再要求我献身给他。 他称我为学生。 但他总是说, 作为他的项目, 我完全令人失望。 我想是为了让我保持警觉。 所以他开始教我击剑和语言。 虽然他把我关在地下室, 但得到所有昂贵衣服的是我, 而不是他的妻子。 ";
			link.l1 = "确实是一个项目。 你经营这个地方的方式可以看到明显的相似之处。 ";
			link.l1.go = "PZ_ChangShin17";
		break;
		
		case "PZ_ChangShin17":
			dialog.text = "我以前没想到这一点, 嗯。 我不喜欢你的类比, 因为我不折磨我的女性员工。 我也不让我的客户这样做。 尽管我恨那些荡妇并嫉妒她们的美丽。 记住, 我和那头猪没有任何共同之处。 ";
			link.l1 = "那么你是如何得到这个妓院的? ";
			link.l1.go = "PZ_ChangShin18";
		break;
		
		case "PZ_ChangShin18":
			dialog.text = "当然是从勒瓦瑟那里。 有一段时间, 他把我留在他的地方。 时不时地, 甚至会问我如何打破这个或那个女孩。 毕竟, 我对他来说很特别, 即使他从不承认。 我是第一个。 我看到了一切。 ";
			link.l1 = "又是谁向谁学习? ";
			link.l1.go = "PZ_ChangShin19";
		break;
		
		case "PZ_ChangShin19":
			dialog.text = "我不是那样的! 我从心底里恨任何把一切都拱手相让的人! 这不公平! 这个妓院是我的主意! 我的工人是商人。 官员和贵族的女儿, 他们有时会和勒瓦瑟扯上关系。 我请他把她们交给我。 在秘密地窖里的酷刑和羞辱是一回事。 但为他们这样的人做交际花的公开活动是另一回事! ";
			link.l1 = "我不会说你的女性员工看起来那么屈辱。 悲惨和崩溃。 ";
			link.l1.go = "PZ_ChangShin20";
		break;
		
		case "PZ_ChangShin20":
			dialog.text = "因为她们知道如果她们哪怕发出一点声音, 勒瓦瑟甚至我会对她们做什么。 但你当然有部分是对的。 葡萄酒。 食物。 丝绸。 没有日常酷刑 - 她们中的许多人开始把我视为救世主。 该死的傻瓜! 只有少数人不喜欢待在这里。 有些人他很不情愿地送给了我。 他会笑着说, 我总是可以把她们中的任何一个还给他, 以解决我地方的资金问题。 但我总是拒绝。 至少这样她们会把金子带回来, 而不是在地下室里白白死去。 对她们来说, 这太容易了。 ";
			link.l1 = "真遗憾, 不是每个人都感到屈辱, 把比宗教裁判所更糟糕的修道院换成像你妓院这样的金笼子... ";
			link.l1.go = "PZ_ChangShin21";
		break;
		
		case "PZ_ChangShin21":
			dialog.text = "你评判我? 我不仅想生存, 还想建立成功的生意。 尽管不知不觉, 勒瓦瑟还是感激我的。 即使我不再是奴隶, 他也不能让我走。 我仍然被迫为他工作, 帮助他的手下。 尤其是他那骨瘦如柴的侄子, 每次见到我都会流口水。 但不敢攻击我或以恶劣的态度对我说话。 恶心。 你知道, 尽管他称我为失望, 但我比蒂博和马滕加起来还要有用。 我经常按他的命令陪伴他们, 就像我当时在太子港一样。 ";
			link.l1 = "这一切都解释了很多... ";
			link.l1.go = "PZ_ChangShin22";
		break;
		
		case "PZ_ChangShin22":
			dialog.text = "没错。 听着。 我没有折磨你的爱人。 就像我没有用这双手折磨任何女孩一样, 即使我有时会给勒瓦瑟建议。 但既然我们在这个话题上... ";
			link.l1 = "什么? ";
			link.l1.go = "PZ_ChangShin23";
		break;
		
		case "PZ_ChangShin23":
			dialog.text = "如你所知, 勒瓦瑟有时会要求把在托尔图加见过的某个女孩带给他, 然后她就离开了岛屿。 或者有人会为了赢得他的青睐而给他带来一个陌生人, 就像我一样。 绑架你的爱人是我的主意。 ";
			link.l1 = "你刚才说什么... ? ";
			link.l1.go = "PZ_ChangShin24";
		break;
		
		case "PZ_ChangShin24":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "起初, 我们考虑过绑架那个曾经和你很亲近的金发女郎。 但既然她现在碰不得, 而且因为我们已经答应给他一个女孩, 你这个红发女郎就不得不做了。 ";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "我听说了关于你那位从不离开你身边的迷人同伴的传闻。 考虑到勒瓦瑟对金发女郎的喜爱, 我很容易就说服了他这个想法。 ";
			dialog.text = "索塔, 他的杂种, 本应给他带来那个混血儿, 卢特的妻子。 但你杀了索塔, 所以 - 大人物没有混血儿了。 勒瓦瑟很生气。 每个人都被打了 - 蒂博。 马滕, 甚至我。 我不知道谁让我更生气: 他, 因为他又打了我, 还是你, 因为你造成了这一切... " + sStr + "";
			link.l1 = "所以甚至不是因为他... 是你做的。 ";
			link.l1.go = "PZ_ChangShin25";
		break;
		
		case "PZ_ChangShin25":
			dialog.text = "我甚至不指望你的原谅, 而且我也不需要。 如果你想要血, 你会得到血。 你会非常后悔的。 但我不会拒绝理解。 十年来我第一次需要它。 我所做的一切只是尽力有一天离开托尔图加。 你有什么问题要问我吗, 查尔斯.德.莫尔? ";
			if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo") && !CheckAttribute(pchar, "questTemp.PZ_FlagMarselinaInfo") && !CheckAttribute(pchar, "questTemp.PZ_FlagMartinInfo"))
			{
				link.l1 = "但你参与了绑架。 而且你知道勒瓦瑟把他的受害者关在哪里。 告诉我在哪里。 如果最坏的情况还没有发生 - 我会认真考虑不报复你。 ";
				link.l1.go = "PZ_ChangShinDontKnow1";
			}
			else
			{
				link.l1 = "好吧, 这一切终于有了头绪... ";
				link.l1.go = "PZ_ChangShin26";
			}
		break;
		
		case "PZ_ChangShinDontKnow1":
			dialog.text = "我知道, 因为我去过那里。 如果你觉得我和他有不健康的相互依恋 - 那你就大错特错了。 我会很高兴看到有人把那头猪放在烤架上。 ";
			link.l1 = "我没时间了, 长兴。 它在哪里? ";
			link.l1.go = "PZ_ChangShinDontKnow2";
		break;
		
		case "PZ_ChangShinDontKnow2":
			dialog.text = "你知道城市街道下的当地地牢吗? 那就是你要去的地方。 在一个死胡同里有一个大酒桶, 旁边有一条秘密通道通向他的‘ pleasure room', 正如他有时所说的。 ";
			link.l1 = "好吧, 这一切终于有了头绪... ";
			link.l1.go = "PZ_ChangShin26";
		break;
		
		case "PZ_ChangShin26":
			if (CheckAttribute(pchar, "questTemp.PZ_FlagArhiv") && CheckAttribute(pchar, "questTemp.PZ_FlagShip")) StartInstantDialog("Longway", "PZ_Longway_SisterDialog6", "Quest\CompanionQuests\Longway.c");
			else
			{
				dialog.text = "算你狠。 现在滚出去。 尽管这么多年来我想说出一切, 但意识到你知道我所有的秘密, 知道对我做了什么 - 这很恶心。 现在看到你只会让我生气。 哦, 还有图留下和我在一起。 ";
				link.l1 = "为什么? ";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet1";
			}
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet1":
			dialog.text = "也许因为我是他的家人? 因为我看到他和你在一起的样子 - 一个被打败的。 可怜的嘟囔者, 甚至没有时间完全学会语言并开始正确说话。 然而他告诉我你们是朋友。 很明显你是如何影响他的。 至少我会把他培养成一个男人。 ";
			link.l1 = "你真的对自己满意吗? 你会把他变成什么样的人? 一个以生命为交易的残忍。 痛苦的生物? ";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet2";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet2":
			StartInstantDialog("Longway", "PZ_Longway_SisterDialog_Ubezhdaet3", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet3":
			if (CheckAttribute(pchar, "questTemp.PZ_FlagArhiv") || CheckAttribute(pchar, "questTemp.PZ_FlagShip"))
			{
				dialog.text = "船长阁下, 请停止。 我请求你让我妹妹安静。 并且... 我会和她待在一起。 ";
				link.l1 = "你... 什么? 朗威... 但为什么? 你看不出她变成了什么样吗? ";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet4";
			}
			else
			{
				dialog.text = "你有什么不同吗? 你随着时间的推移改变了。 变得更糟。 起初, 你礼貌而善解人意。 但后来你变得粗鲁, 甚至比罗登堡还粗鲁。 当我需要一艘好船去抓范德温克时, 你给了我一些垃圾! ";
				link.l1 = "朗威... ";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet8";
			}
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "玛丽";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "海伦";
			dialog.text = "一旦我出海, 花了这么多年只是为了找到并拯救我的妹妹。 现在她在这里, 安全了。 我的使命完成了。 并且... 我的名字是张图。 朗威是叛徒范默登给我起的名字, 如果你忘了的话。 但张图是个自由人。 张图的漫长旅程终于结束了。 ";
			link.l1 = "她会把你变成像罗登堡曾经那样的仆人。 她会因为你是家人而向你施压。 你会如此轻易地站在那个给我和" + sStr + "带来这么多痛苦的人一边吗? ";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet5";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet5":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "玛丽";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "海伦";
			dialog.text = "现在, 是你在向张图施压。 请让我走。 我很累。 你是个好人, 船长 - 上天可以证明。 但你不是我的家人。 她是。 如果我不留下来, 那么所有这些年都将是徒劳的。 现在我将成为她的指路明星, 重新点燃她熄灭的火焰 - 温暖而舒适, 而不是烧毁一切。 ";
			if (CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden"))
			{
				link.l1 = "嗯, 你说得对。 我现在可能逼得太紧了。 好吧, 我一直尊重你。 祝你和你妹妹久别重逢。 但我警告你, 和她在一起你不会找到平静。 ";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet6";
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko") && !CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva")) 
				{
					pchar.questTemp.PZ_LongwayHochetMira = true;
					link.l1.go = "PZ_Longway_SisterDialog_ReactiaDevushek";
				}
				
			}
			else
			{
				link.l1 = "你现在不能离开我! 我还需要把" + sStr + "从勒瓦瑟那里救出来! 你想让我一个人去吗? 帮助我, 朗威。 然后我会让你走。 我向你保证。 ";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet6";
			}
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet6":
			if (CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden"))
			{
				dialog.text = "我能处理。 你不必再担心我了。 谢谢。 ";
				link.l1 = "看来你妹妹对我们和平分手感到生气。 ";
			}
			else
			{
				dialog.text = "你会想办法的, 船长阁下。 你是我见过的最聪明的人。 你可以轻松对付那个只习惯折磨女人的蠕虫。 我请求你, 不要强迫我。 我妹妹有太多话要和我说了! 并且... 我的名字是张图。 ";
				link.l1 = "你意识到现在离开我是在背叛我吗? ! 尤其是和她待在一起 - 这个引发了这一切的女人! ";
			}
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet7";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet7":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "玛丽";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "海伦";
			if (CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden"))
			{
				dialog.text = "别担心, 船长。 尽管她对我说话不尊重, 但我是哥哥, 是她最后的男性亲属。 你可以走了。 我不会让她杀了你。 再见。 ";
				link.l1 = "再见... 张图。 ";
				DeleteAttribute(pchar, "questTemp.PZ_LongwayRyadom");
				AddDialogExitQuest("PZ_BrothelTeleportVZal");	//和平分手
			}
			else
			{
				dialog.text = "我已经说完了。 再见, 船长。 祝你好运。 张图将永远是自由人。 别忘了。 ";
				link.l1 = "这就是我放弃一切并帮助你寻找后得到的? ! 在他们现在对" + sStr + "所做的之后? ! 你是个叛徒, 张图。 你们两个都会像这样死去, 你们这对该死的蛇! ";
				link.l1.go = "exit";
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				AddDialogExitQuest("MainHeroFightModeOn");
				AddDialogExitQuest("PZ_ChangShinAndLongwayFightMe");
			}
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet8":
			dialog.text = "我的名字是张图。 朗威死了。 是你杀了他。 你不再是我的船长。 现在你会死。 我的家人终于会找到平静, 我们的星星将在夜空中明亮地闪耀。 ";
			if (IsCharacterPerkOn(pchar, "Trustworthy") && GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 85)
			{
				link.l1 = "(值得信赖) (领导力) 朗威... 张图。 停下。 我知道我不是你理想的船长。 但你真的想为此杀了我吗? 在我们经历了这一切之后? 先是罗登堡, 现在是寻找你妹妹。 ";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet9";
				Notification_Perk(true, "Trustworthy");
				notification("技能检查通过", SKILL_LEADERSHIP);
			}
			else
			{
				link.l1 = "朗威, 我是你的船长。 不是你的家人, 也不是保姆。 我发号施令, 不会考虑是否无意中冒犯了你。 你在提要求, 好像我们是老夫老妻, 天哪... ";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet15";
				if (!IsCharacterPerkOn(pchar, "Trustworthy")) Notification_Perk(false, "Trustworthy");
				if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 85) notification("技能检查失败 (85)", SKILL_LEADERSHIP);
			}
			link.l2 = "是的。 我现在明白了。 你和你妹妹一样, 是个只关心自己的烂人... 朗威。 就像你妹妹一样。 我的家人会活过这一天。 你的... 不会。 去死吧! ";
			link.l2.go = "PZ_Longway_SisterDialog_Ubezhdaet8_1";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet8_1":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetFightMode(pchar, true);
			DoQuestCheckDelay("PZ_ChangShinAndLongwayFightMe", 0.5);
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet9":
			dialog.text = "如果在你和我的家人之间做出选择 - 我仍然选择家人, 即使这是一个艰难的选择。 ";
			link.l1 = "一个在你寻找她的这些年里没有伸出一根手指的家人? 哦, 但合适的时机刚刚到来! 至于我, 我放弃一切来帮助你。 你站在这里, 就是结果。 见鬼, 我比她更像你的家人, 我的朋友! ";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet10";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet10":
			dialog.text = "你说得对。 一如既往, 你说得对。 你会原谅我吗, 船长阁下? ";
			link.l1 = "没有什么可原谅的! 你说得对一件事 - 我并不总是你应得的船长。 我想现在我们扯平了。 顺便问一下, 你希望我以后怎么称呼你? 朗威? 还是张图? ";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet11";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet11":
			dialog.text = "就叫朗威吧。 我已经习惯了你这样称呼我。 ";
			link.l1 = "那么让我们忘记所有分歧, 再次欢迎你加入, 朗威。 ";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet12";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet12":
			StartInstantDialog("PZ_ChangShin", "PZ_Longway_SisterDialog_Ubezhdaet13", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet13":
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			dialog.text = "图! 你在说什么? ! 为什么停下来? 杀了他! 对他来说, 你永远只是个劳工! 你的家人只有我! ";
			link.l1 = "她很生气, 不是吗, 朗威? 你不再是他的家人了, 兴。 当你得知朗威到达群岛却选择无视时, 就已经不是了。 我们走。 ";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet14";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet14":
			dialog.text = "我想我永远没机会根除他的奴性了。 我救不了他。 那我就亲自杀了你们俩。 ";
			link.l1 = "你才是这里无法被拯救的人。 你知道, 我之前对你太理解和宽容了。 但这样更好。 我想连朗威都意识到你是条毒蛇了。 他不会太为你哀悼的。 ";
			link.l1.go = "exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_ChangShinFightWithLongway");
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet15":
			dialog.text = "现在不是开玩笑的时候! 你用笑话掩盖恐惧和失败! 这只会让我更加确信。 防御吧, 德.莫尔! 因为张图不打算放过你。 ";
			link.l1 = "很遗憾事情以这种方式结束。 但如果这是你想要的, 那就这样吧。 在这种情况下, 你也不会从我这里得到任何怜悯。 ";
			link.l1.go = "exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_ChangShinAndLongwayFightMe");
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaDevushek":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) StartInstantDialog("Mary", "PZ_Longway_SisterDialog_ReactiaMary", "Quest\CompanionQuests\Longway.c");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) StartInstantDialog("Helena", "PZ_Longway_SisterDialog_ReactiaHelena", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayHochetMira"))
			{
				dialog.text = "查尔斯, 听着... ";
				link.l1 = "海伦? ";
			}
			else
			{
				dialog.text = "查尔斯, 朗威, 住手... ";
				link.l1 = "海伦, 你最好现在到我后面来。 如果他们攻击我们, 我会更放心。 ";
			}
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaHelena2";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena2":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayHochetMira"))
			{
				dialog.text = "我太累了, 几乎站不住。 我只想离开这里。 如果朗威不想回船, 我们不会强迫他, 对吧? 我会做你的领航员和大副, 我的船长。 希望也是你最信任和最爱的人。 此外, 他说得有道理 - 我们不是他的家人。 她是, 不管好坏。 ";
				link.l1 = "但她呢? 她是你被折磨的原因, 这都是她的主意。 而且是她绑架了你。 ";
			}
			else
			{
				dialog.text = "但他们不会攻击, 对吧? 我们现在就离开, 就这样。 如果这是他在我们为他做了所有事后的想法, 那么试图改变他的想法也没有意义。 行动胜于雄辩。 如果他想和他妹妹待在一起, 就让他吧。 ";
				link.l1 = "海伦, 你因为她受了这么多苦... ";
			}
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaHelena3";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena3":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayHochetMira"))
			{
				dialog.text = "别管那个女魔头和她的恶魔了。 它们很快就会吞噬她的灵魂。 而我们的灵魂值得好好休息。 我们走吧。 ";
				link.l1 = "是的。 我想我们应该走。 我们离开这里吧, 我的天使。 还有你 - 朗威, 或者张图 - 再见。 ";
			}
			else
			{
				dialog.text = "但我没有死。 最糟糕的事情没有发生。 我在这里, 和你在一起, 这才是重要的。 而且勒瓦瑟死了。 没有他, 她什么都不是。 她的地方在赔钱, 很快就会倒闭。 他们会一起垮台。 我们走吧, 我的船长。 我们在这里没什么可做的了。 ";
				link.l1 = "我不会争辩, 海伦。 ";
			}
			AddDialogExitQuest("PZ_BrothelTeleportVZal");		//和平分手
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena4":
			StartInstantDialog("Helena", "PZ_Longway_SisterDialog_ReactiaHelena5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena5":
			dialog.text = "你要去哪里? ";
			link.l1 = "怎么, 惊讶我们不急于把你和你妹妹开膛破肚吗, 朗威? 这就是我们之间的区别。 而你仍然认为我是坏人... 但好吧, 看。 如果你想杀我, 那就意味着你也得杀了海伦。 她受伤了, 受了伤。 你真的想这么做吗? ";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaHelena6";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena6":
			dialog.text = "嗯嗯。 ";
			link.l1 = "我能从你眼里看到怀疑, 尽管你对我有很多怨恨。 但我们都该听听海伦的意见, 不是吗? 我们船员中没有比她更善良。 更宽容的人了。 我们要走了。 如果你还有一点良知或理智, 就不会挡我们的路。 ";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaHelena7";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena7":
			dialog.text = "随你便。 我道歉。 但你不再是我的船长了。 ";
			link.l1 = "我会想办法克服的。 不管你妹妹做了什么, 我都祝你和她一切顺利。 再见, 朗威。 ";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_BrothelTeleportVZal");		//和平分手
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary":
			dialog.text = "来吧, 查尔斯, 是时候镇压这场兵变了。 ";
			link.l1 = "天知道我不想那么做... 而且我仍然不想。 ";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary2";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary2":
			dialog.text = "你不想? ! 查尔斯, 听我说。 你为他做了这么多, 得到了什么回报? 背叛和恶语相向, 好吧! 你真的打算让这一切过去吗? ";
			link.l1 = "我不想流朗威的血。 我没有忘记我们曾经是朋友。 ";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary3";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary3":
			dialog.text = "去他的这样的朋友 - 他们比敌人还糟糕, 好吧! 查尔斯, 看着我。 看看发生在我身上的事 - 因为他妹妹, 在去这个该死的岛屿的路上, 她嘲笑。 侮辱和羞辱我! ";
			link.l1 = "玛丽, 我明白 - 你现在非常非常生气... ";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary4";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary4":
			dialog.text = "哦不, 查尔斯, 我不只是生气, 不... 我是愤怒! 不仅仅是因为那个可怜的小混蛋对你说的话! 再看看我, 查尔斯 - 想象一下, 如果我们不在这里结束这一切, 会有多少女孩经历这些。 ";
			link.l1 = "他们不会再伤害任何人了。 勒瓦瑟死了。 ";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary5";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary5":
			dialog.text = "查尔斯, 你真的听了她喷出的异端邪说吗? 她和那个臭猪一样, 对地下室里发生的事负有责任。 现在看看朗威 - 或者现在他叫什么名字。 看看她多快就把他拉到她那边, 好吧! 谁知道她会在那个叛徒的脑子里灌输什么其他病态的想法? 你认为那个女魔头很难把他推向勒瓦瑟的道路吗? 查尔斯, 不要想他现在是什么样。 想想一年后... 甚至一个月后他会变成什么样的怪物。 你知道我是对的, 不是吗? ";
			link.l1 = "尽管我不愿意承认, 但我没有什么可以反驳你, 玛丽... ";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary6";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary6":
			StartInstantDialog("PZ_ChangShin", "PZ_Longway_SisterDialog_ReactiaMary7", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary7":
			dialog.text = "哈哈哈! 太有趣了, 多么精彩的表演。 我很久没有这么开心地笑过了。 而且她有胆量, 我得承认这一点。 ";
			link.l1 = "闭上你的嘴, 你这个婊子。 ";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary8";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary8":
			dialog.text = "这很有趣, 不是吗, 德.莫尔? 我很想亲眼看到图把你打倒。 而你的女人和我一样嗜血。 非常好。 我不会袖手旁观 - 我和勒瓦瑟以及托尔图加的一些顶尖人物一起训练过。 让我们看看谁的二人组能胜出。 ";
			link.l1 = "你的老师不怎么样。 而且你惹恼了玛丽。 你完蛋了。 即使我不在这里, 你们的二人组也无法与她抗衡。 ";
			link.l1.go = "exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_ChangShinAndLongwayFightMe");
		break;
		
		case "PZ_Longway_SisterDialog6":
			dialog.text = "是的。 终于。 朗威可以再和我妹妹谈谈吗, 船长阁下? 不会太久。 ";
			link.l1 = "当然。 只是要快 - 我们没有太多时间。 ";
			link.l1.go = "PZ_Longway_SisterDialog7";
		break;
		
		case "PZ_Longway_SisterDialog7":
			dialog.text = "朗威快点说。 ";
			link.l1 = "好。 ";
			link.l1.go = "PZ_Longway_SisterDialog7_1";
		break;
		
		case "PZ_ChangShin26":
			StartInstantDialog("СhangShin", "PZ_Longway_SisterDialog7_1", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog7_1":
			locCameraFromToPos(0.65, 2.59, -3.06, true, 0.23, 0.34, -5.21);
			
			sld = characterFromId("Longway");
			ChangeCharacterAddressGroup(sld, "Tortuga_brothelElite_room2", "goto", "goto8");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromId("PZ_ChangShin"));
			
			sld = characterFromId("PZ_ChangShin");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromId("Longway"));
			
			dialog.text = "你想告诉我什么, 我的哥哥? ";
			link.l1 = "朗威对你很失望, 兴。 ";
			link.l1.go = "PZ_Longway_SisterDialog8";
		break;
		
		case "PZ_Longway_SisterDialog8":
			dialog.text = "(用普通话) 既然你想再谈谈, 图, 为什么不说我们的语言? 你为他感到尴尬吗? 如果我是你, 我会更尴尬你的口音。 ";
			link.l1 = "不。 朗威对船长阁下没有秘密。 不再有了。 ";
			link.l1.go = "PZ_Longway_SisterDialog9";
		break;
		
		case "PZ_Longway_SisterDialog9":
			dialog.text = "(用法语) 先是罗登堡, 现在是德.莫尔。 你总是需要一个‘先生'。 你十多年来在这里一无所获。 你甚至学不会他们的任何语言。 而且它们比我们的简单得多! 如果说有谁令人失望, 那就是你。 ";
			link.l1 = "但我不做女人的交易。 我不参与她们的绑架和折磨。 ";
			link.l1.go = "PZ_Longway_SisterDialog10";
		break;
		
		case "PZ_Longway_SisterDialog10":
			dialog.text = "你是认真的吗? 要我列出你为罗登堡做的事情吗? 相比之下, 我所做的只是小儿科。 ";
			link.l1 = "我有一个目的 - 找到你。 但你甚至不想见我。 当我找到你时, 我发现的是一个怪物, 而不是曾经照亮我道路的温暖指路星。 ";
			link.l1.go = "PZ_Longway_SisterDialog11";
		break;
		
		case "PZ_Longway_SisterDialog11":
			dialog.text = "一个怪物? 好吧, 也许你是对的。 我不再是你认识的那个开朗的女孩了。 如果我一直那样, 生活早就把我嚼碎并吐出来了。 我必须长出自己的牙齿。 我的星星早已熄灭。 但我仍然是你的妹妹, 图。 ";
			link.l1 = "不。 你不再是我的妹妹了。 ";
			link.l1.go = "PZ_Longway_SisterDialog12";
		break;
		
		case "PZ_Longway_SisterDialog12":
			dialog.text = "这么多年后就这么轻易地放弃我了? 呵呵... 谁知道呢, 如果那天你及时回家杀了费尔门特洛斯, 我可能还是老样子? ";
			link.l1 = "你说得对。 这也有我的部分责任。 这是我的责任。 我会结束它。 我会让你摆脱痛苦。 结束这种悲惨的存在。 ";
			link.l1.go = "PZ_Longway_SisterDialog13";
		break;
		
		case "PZ_Longway_SisterDialog13":
			dialog.text = "你真的要杀了你自己的妹妹吗, 张图? 不是说你会成功, 但事实是... ";
			link.l1 = "你不再是我的妹妹了。 兴十年前就死了。 而今天是张图最终死去的日子。 从现在开始, 永远, 我的名字是... 朗威。 ";
			link.l1.go = "Exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_ChangShinFightWithLongway");
		break;
		
		case "PZ_Longway_FlagMartinInfo_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "玛丽";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "海伦";
			dialog.text = "首先, 我们营救长兴。 ";
			link.l1 = "什么? ! 你好像不明白, 我的朋友。 你妹妹没有立即危险, 但" + sStr + "有。 需要我提醒你, 长兴和马滕。 蒂博一样对此负有责任吗? ";
			link.l1.go = "PZ_Longway_FlagMartinInfo_2";
		break;
		
		case "PZ_Longway_FlagMartinInfo_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "玛丽";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "海伦";
			dialog.text = "那不是真的! 她是... ";
			link.l1 = "你知道当我们在这里争论时, 勒瓦瑟可能对" + sStr + "做了什么吗? ";
			link.l1.go = "PZ_Longway_FlagMartinInfo_3";
		break;
		
		case "PZ_Longway_FlagMartinInfo_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "玛丽";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "海伦";
			dialog.text = "但长兴是我剩下的一切, 船长... 你的家人仍然完好无损... ";
			link.l1 = + sStr + "可能不是我的妻子, 但她和我的家人一样亲。 ";
			link.l1.go = "PZ_Longway_FlagMartinInfo_4";
		break;
		
		case "PZ_Longway_FlagMartinInfo_4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "玛丽";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "海伦";
			dialog.text = "长兴是我最后的指路星, 船长。 此外, 你欠我从罗伯特.马滕那里得到供词的人情。 ";
			if (CheckAttribute(pchar, "questTemp.PZ_FlagArhiv") && CheckAttribute(pchar, "questTemp.PZ_FlagShip"))
			{
				link.l1 = "我们会去找你妹妹, 我保证。 但勒瓦瑟这段时间没有碰她。 " + sStr + "比长兴危险得多。 先帮我救她, 我会欠你一个大人情。 ";
				link.l1.go = "PZ_Longway_FlagMartinInfo_VD1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_FlagArhiv") || CheckAttribute(pchar, "questTemp.PZ_FlagShip"))
				{
					if (IsCharacterPerkOn(pchar, "Trustworthy") && GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 85)
					{
						link.l1 = "(值得信赖) (领导力) 我们会去找你妹妹, 我保证。 但勒瓦瑟这段时间没有碰她。 " + sStr + "比长兴危险得多。 先帮我救她, 我会欠你一个大人情。 ";
						link.l1.go = "PZ_Longway_FlagMartinInfo_VD1";
						Notification_Perk(true, "Trustworthy");
						notification("技能检查通过", SKILL_LEADERSHIP);
					}
					else
					{
						link.l1 = "听我说! 你妹妹是安全的。 但" + sStr + "现在在一个变态手里, 他可能正在折磨她 - 或者更糟! 你认为如果勒瓦瑟像对待地牢里其他可怜女孩那样对待你妹妹, 她还能拥有这么高档的场所吗? ! ";
						link.l1.go = "PZ_Longway_FlagMartinInfo_netVD1";
						if (!IsCharacterPerkOn(pchar, "Trustworthy")) Notification_Perk(false, "Trustworthy");
						if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 85) notification("技能检查失败 (85)", SKILL_LEADERSHIP);
					}
				}
			}
			link.l2 = "我不会在无意义的争论上浪费时间。 我们各有各的优先事项。 我们再分开吧。 愿我的神帮助我, 你的神帮助你。 ";
			link.l2.go = "PZ_Longway_FlagMartinInfo_Razdelimsya";
			link.l3 = "你说得对。 我欠你一个人情。 好吧, 就按你说的办。 此外, 没有你, 我可能无法对付勒瓦瑟和他的人。 但如果我们在处理你妹妹时" + sStr + "出了什么事... ";
			link.l3.go = "PZ_Longway_FlagMartinInfo_IdemKSestreLongweya";
		break;
		
		case "PZ_Longway_FlagMartinInfo_Razdelimsya":
			dialog.text = "谢谢你的理解, 船长阁下。 祝你好运! ";
			link.l1 = "也祝你好运, 朗威。 ";
			link.l1.go = "PZ_Longway_FlagMartinInfo_SharleOdinVPodzemelie";
		break;
		
		case "PZ_Longway_FlagMartinInfo_IdemKSestreLongweya":
			dialog.text = "空洞的威胁是没有用的, 船长阁下。 我们必须快点, 这样我们才能及时处理所有事情。 ";
			link.l1 = "我希望你的神能听到。 我们走吧! ";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TogetherLongwayGo");
		break;
		
		case "PZ_Longway_FlagMartinInfo_netVD1":
			dialog.text = "出于尊重, 我会放过你, 船长阁下。 就这一次。 下次我会打你。 我现在要去找我妹妹了, 不管你是否同意。 ";
			link.l1 = "我不会再浪费时间和你争论了, 朗威。 最终, 我们都有比什么都珍贵的东西。 ";
			link.l1.go = "PZ_Longway_FlagMartinInfo_SharleOdinVPodzemelie";
		break;
		
		case "PZ_Longway_FlagMartinInfo_SharleOdinVPodzemelie":
			pchar.questTemp.PZ_DevushkaRanena_Legko = true;
			LAi_LocationDisableOfficersGen("Tortuga_Cave", true);
			DoQuestReloadToLocation("Tortuga_Cave", "reload", "reload2", "PZ_Etap6TortugaPodzemelie");
		break;
		
		case "PZ_Longway_FlagMartinInfo_VD1":
			dialog.text = "嗯嗯, 好吧, 船长阁下。 但我们必须快点。 ";
			link.l1 = "对。 谢谢你, 朗威。 ";
			link.l1.go = "PZ_Longway_FlagMartinInfo_VD2";
		break;
		
		case "PZ_Longway_FlagMartinInfo_VD2":
			pchar.questTemp.PZ_LongwayRyadom = true;
			pchar.questTemp.PZ_DevushkaRanena_Legko = true;
			LAi_LocationDisableOfficersGen("Tortuga_Cave", true);
			DoQuestReloadToLocation("Tortuga_Cave", "reload", "reload2", "PZ_Etap6TortugaPodzemelie");
		break;
		
		case "PZ_TortureRoom_Levasser_1":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				dialog.text = "好吧, 好吧, 我们这里有谁... 该死。 查尔斯.德.莫尔和他的斜眼杂种。 ";
				link.l1 = "这里只有一个杂种。 如果你想看看, 照照镜子, 你这个胡格诺混蛋。 或者看看你的侄子。 不过, 他看起来更像一只邋遢的老鼠。 ";
				link.l1.go = "PZ_TortureRoom_Levasser_2";
			}
			else
			{
				dialog.text = "我告诉过你不要打扰我! 啊, 查尔斯.德.莫尔, 呵呵。 真是个 persistent 的小害虫。 ";
				link.l1 = "我就是这样。 现在闭嘴并... ";
				link.l1.go = "PZ_TortureRoom_Levasser_1_1";
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne") || CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo") || CheckAttribute(pchar, "questTemp.PZ_Etap6_Opozdal")) Achievment_Set("ach_CL_130");
			}
			locCameraSleep(true);
			sld = CharacterFromID("Tibo");
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto2");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("Levasser"));
		break;
		
		case "PZ_TortureRoom_Levasser_1_1":
			dialog.text = "你不在自己的船上, 小子! 这个岛上只有一个男人, 那就是我! ";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_Etap6TortugaPytochnaya9");
		break;
		
		case "PZ_TortureRoom_Levasser_2":
			StartInstantDialog("Tibo", "PZ_TortureRoom_Levasser_3", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_3":
			dialog.text = "你怎么敢, 你这个人渣! ";
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_4";
			sld = CharacterFromID("Tibo");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_4":
			StartInstantDialog("Levasser", "PZ_TortureRoom_Levasser_5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_5":
			dialog.text = "冷静点, 侄子! 德.莫尔先生即将接受一堂礼仪课。 ";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_Etap6TortugaPytochnaya9");
			sld = CharacterFromID("Tibo");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("Levasser"));
		break;
		
		case "PZ_TortureRoom_Levasser_6":
			if (!CheckAttribute(pchar, "questTemp.PZ_Etap6_Opozdal"))
			{
				dialog.text = "我允许你尖叫了吗? ! ";
			}
			else
			{
				dialog.text = "那股火气去哪儿了, 嗯, 漂亮的东西? 啊, 我想我明白了... ";
			}
			link.l1 = "放开她, 你这个混蛋! ";
			link.l1.go = "PZ_TortureRoom_Levasser_7";
			LAi_SetActorType(npchar);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) LAi_ActorTurnToCharacter(npchar, CharacterFromID("Mary"));
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) LAi_ActorTurnToCharacter(npchar, CharacterFromID("Helena"));
		break;
		
		case "PZ_TortureRoom_Levasser_7":
			dialog.text = "呵呵呵... 你可以大喊大叫侮辱我, 但我能看到你像风中的叶子一样颤抖。 我在你眼里看到了恐惧。 你和亨利有共同点。 无意冒犯, 侄子。 ";
			link.l1 = "你说得对, 是恐惧。 但不是怕你, 人渣。 ";
			link.l1.go = "PZ_TortureRoom_Levasser_7_1";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_7_1":
			dialog.text = "当然, 当然。 我以前都听过 - 你什么都不怕, 德.莫尔。 她告诉我的。 ‘哦, 查尔斯会来的, 查尔斯会救我... 查尔斯这个, 查尔斯那个...'好吧, 查尔斯来了。 查尔斯有前排座位。 亨利, 让我们的客人舒服点。 ";
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_8";
		break;
		
		case "PZ_TortureRoom_Levasser_8":
			StartInstantDialog("Tibo", "PZ_TortureRoom_Levasser_9", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_9":
			if (CheckAttribute(pchar, "questTemp.PZ_Etap6_Opozdal"))
			{
				dialog.text = "没必要这样, 叔叔。 恐怕你这次有点太过分了... ";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
				{
					dialog.text = "叔叔, 我需要你帮我处理这个... ";
				}
				else
				{
					dialog.text = "我该干掉他吗, 叔叔, 还是让他先看看? ";
				}
			}
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_10";
			LAi_SetActorType(npchar);
			//LAi_ActorTurnToCharacter(npchar, CharacterFromID("Levasser"));
			LAi_ActorTurnToLocator(npchar, "goto", "goto8");
			locCameraFromToPos(-15.67, 2.57, -1.23, true, -17.49, 1.42, -3.26);
		break;
		
		case "PZ_TortureRoom_Levasser_10":
			StartInstantDialog("Levasser", "PZ_TortureRoom_Levasser_11", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_11":
			if (CheckAttribute(pchar, "questTemp.PZ_Etap6_Opozdal"))
			{
				dialog.text = "不是我, 是那边的白骑士先生来救援太晚了。 看来表演结束了, 哈哈哈哈! ";
				link.l1 = "天哪, 不... ";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_TortureRoom_Levasser_DevushkaMertva");
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
				{
					dialog.text = "我想是这样。 你是怎么活到这个年纪的? 顺便问一下, 同样的问题也给你, 德.莫尔。 ";
					link.l1 = "你不知道我有多少问题要问你, 屠夫! ";
				}
				else
				{
					dialog.text = "我希望我们的小表演有观众... 但我认为这里的顽固先生不会给我们那个 pleasure。 ";
					link.l1 = "唯一得到 pleasure 的是我 - 把你开膛破肚, 屠夫! ";
				}
				link.l1.go = "PZ_TortureRoom_Levasser_14";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
			{
				locCameraFromToPos(-16.74, 2.58, -0.51, true, -13.13, -0.72, 2.49);
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
			{
				locCameraFromToPos(-18.38, 1.77, 2.73, true, -20.53, 0.01, 0.32);
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
			{
				locCameraFromToPos(-16.97, 2.09, 3.98, true, -20.02, -0.17, 2.28);
			}
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("Tibo"));
		break;
		
		case "PZ_TortureRoom_Levasser_12":
			dialog.text = "来吧, 继续, 把她抱起来! 哈哈哈! ";
			link.l1 = "他妈的畜生, 我会让你们后悔出生! ";
			link.l1.go = "PZ_TortureRoom_Levasser_13";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_13":
			DialogExit();
			EndQuestMovie();
			locCameraSleep(false);
			DeleteAttribute(pchar, "GenQuest.BlockDialogCamera");
			LAi_SetPlayerType(pchar);
			locCameraTarget(PChar);
			locCameraFollow();
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				sld = CharacterFromID("Longway");
				ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
				ReturnOfficer_Longway();
				PlaySound("VOICE\Russian\hambit\Longway-02.wav");
			}
			LAi_SetFightMode(pchar, true);
			sld = CharacterFromID("Levasser");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			sld = CharacterFromID("Tibo");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "PZ_TortureRoom_Levasser_DevushkaMertva5");
		break;
		
		case "PZ_TortureRoom_Levasser_14":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "屠夫? 我更多地认为自己是一个艺术家, 一个画家 - 你至少可以试着把它看作艺术... 观察。 \n你喜欢我的作品吗? 这确实是我的杰作之一。 老实说, 我更喜欢金发女郎, 但她... 最后, 我原谅了她这丑陋的头发颜色。 不仅仅是头发 - 这个女孩像火一样! 我差点把自己烧伤。 她挣扎。 咬人。 像野兽一样咆哮! 让我想起一个红皮肤的野蛮人, 我和他玩得很开心, 即使时间不长... ";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "屠夫? 我更多地认为自己是一个艺术家, 一个画家 - 你至少可以试着把它看作艺术... 观察。 \n看, 我还没对她完成 - 这幅画布上还有很多空白。 她不仅美丽, 而且像岩石一样坚强, 像冰一样寒冷。 我甚至不得不费点力气让她尖叫。 她坚持到最后, 只是为了不让我听到她可爱声音的 pleasure。 ";
			}
			link.l1 = "现在释放她, 你这个堕落者。 ";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_Etap6TortugaPytochnaya13");
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_15":
			dialog.text = "你认为你要去哪里? 这块肉现在是我的财产了。 就像周围的一切 - 这个小镇, 这个堡垒... 我就是托尔图加。 而你和庞西, 那个臭烘烘的老火鸡, 永远无法改变这一点。 ";
			link.l1 = "勒瓦瑟, 你... ";
			link.l1.go = "PZ_TortureRoom_Levasser_16";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_16":
			dialog.text = "对你来说是勒内.德.布阿杜弗莱.德.莱特先生。 ";
			link.l1 = "我他妈不在乎。 拔出你的剑, 让我看看你在战斗中有什么价值 - 和一个男人, 而不是一个手无寸铁的女孩。 ";
			link.l1.go = "PZ_TortureRoom_Levasser_17";
		break;
		
		case "PZ_TortureRoom_Levasser_17":
			dialog.text = "你真是个男人! 但你说得对, 我自己也厌倦了所有这些 chatter。 我想回到... 我的女人身边。 但我会问你最后一个问题。 你是怎么到这里的? 谁泄露了这个地方的位置? 只有少数人知道。 ";
			if (CheckAttribute(pchar, "questTemp.PZ_FlagMartinInfo"))
			{
				link.l1 = "你的共同朋友马滕像夜莺一样唱歌。 实际上, 更像是屠宰场里的猪一样尖叫... ";
				link.l1.go = "PZ_TortureRoom_Levasser_FlagMartinInfo_1";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_FlagMarselinaInfo"))
			{
				link.l2 = "也许最好对你保密。 我担心这可能会伤害你的自尊心, 勒内先生... 什么的。 ";
				link.l2.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_1";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
			{
				link.l3 = "你的一个受害者, 勒瓦瑟。 ";
				link.l3.go = "PZ_TortureRoom_Levasser_FlagShinInfo_1";
			}
		break;
		
		case "PZ_TortureRoom_Levasser_FlagShinInfo_1":
			dialog.text = "骗子, 你这个无赖! 没有人离开这些墙! ";
			link.l1 = "用用你的记忆, 来吧。 有一个。 长兴。 ";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagShinInfo_2";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagShinInfo_2":
			dialog.text = "不可能。 不是她。 我的一些想法是由那个小魔鬼催生的。 哦哦, 我们互相教了很多, 呵呵。 她最终决定清理良心了吗? 我怀疑。 毕竟, 我很久以前就把它从她身上抹去了! ";
			link.l1 = "现在我要把你榨干。 一滴一滴地。 ";
			link.l1.go = "PZ_TortureRoom_Levasser_Bitva";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMartinInfo_1":
			dialog.text = "你还叫我屠夫, 你这个可怜的伪君子! 呵呵... 但只要他在地狱里燃烧, 我就没什么好怕的。 ";
			link.l1 = "他在那里等你。 还有你那无赖的侄子。 我们不要让他失望。 ";
			link.l1.go = "PZ_TortureRoom_Levasser_Bitva";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_1":
			dialog.text = "我再伤害一下这个玩具怎么样? 割开她的肚子或喉咙, 看着她流血而死, 而你试图接近她... ";
			link.l1 = "不管你说什么, 勒瓦瑟, 不管你说什么... 你妻子向你问好。 并附上一个告别鞠躬。 ";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_2";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_2":
			dialog.text = "什么? ! 哈-哈... 该死的马塞尔琳... 你这个可怜的婊子, 婊子, 婊子, 婊子! ";
			link.l1 = "她就是这样。 你们很般配。 不过她至少头脑更清醒一点。 至少乍一看是这样。 ";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_3";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_3":
			dialog.text = "我要把她的鸡头钉在尖桩上。 但在那之前... 哦哦, 很多很多事情会发生在那个荡妇身上... 。 我甚至会让我的新玩具休息一下。 等等! 我有个更好的主意。 我会把她借给亨利。 当然, 只是一段时间。 ";
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_4";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_4":
			StartInstantDialog("Tibo", "PZ_TortureRoom_Levasser_FlagMarselinaInfo_5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_5":
			dialog.text = "真的吗? 谢谢你, 叔叔! ";
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_6";
			CharacterTurnByChr(npchar, CharacterFromID("Levasser"));
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_6":
			StartInstantDialog("Levasser", "PZ_TortureRoom_Levasser_FlagMarselinaInfo_7", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_7":
			dialog.text = "先应得的 - 帮我一把, 嗯? ";
			link.l1 = "他快要失控了。 ";
			link.l1.go = "PZ_TortureRoom_Levasser_Bitva";
			CharacterTurnByChr(npchar, CharacterFromID("Tibo"));
		break;
		
		case "PZ_TortureRoom_Levasser_Bitva":
			DialogExit();
			EndQuestMovie();
			locCameraSleep(false);
			DeleteAttribute(pchar, "GenQuest.BlockDialogCamera");
			LAi_SetPlayerType(pchar);
			locCameraTarget(PChar);
			locCameraFollow();
			
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				sld = CharacterFromID("Longway");
				ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
				ReturnOfficer_Longway();
				PlaySound("VOICE\Russian\hambit\Longway-02.wav");
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sld = CharacterFromID("Mary");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sld = CharacterFromID("Helena");
			LAi_SetImmortal(sld, true);
			
			LAi_SetFightMode(pchar, true);
			sld = CharacterFromID("Levasser");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetCheckMinHP(sld, 1, true, "PZ_Etap6TortugaPytochnaya19");
			sld = CharacterFromID("Tibo");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		break;
		
		case "PZ_TortureRoom_Longway_1":
			dialog.text = "船长阁下... 朗威表示哀悼。 我们尽力了。 ";
			link.l1 = "不是一切, 远远不够。 ";
			link.l1.go = "PZ_TortureRoom_Longway_2";
		break;
		
		case "PZ_TortureRoom_Longway_2":
			dialog.text = "朗威要去找长兴。 你会和我一起去吗? ";
			link.l1 = "是的, 我和你一起去, 朗威。 但记住 - 你妹妹在这场血腥表演中也有积极参与。 她必须非常努力才能说服我放过她。 而你不会帮助她。 现在来吧, 是时候结束这一切了。 ";
			link.l1.go = "PZ_TortureRoom_Longway_3";
		break;
		
		case "PZ_TortureRoom_Longway_3":
			DialogExit();
			ReturnOfficer_Longway();
			chrDisableReloadToLocation = false;
		break;
		
		case "PZ_TortureRoom_Devushka_1":
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "查尔斯, 我就知道, 好吧! 我就知道你会来! 你总是这样, 不是吗? ";
					link.l1 = "我不想第四次测试这个, 玛丽... 那些恶棍, 他们... ";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "哦, 我的船长, 你不知道你来得有多及时。 那些... 那些怪物... ";
					link.l1 = "现在结束了, 海伦。 没事了, 都结束了。 哦, 我的上帝, 他们对你做了什么... ";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "查尔斯, 你来了! 我就知道, 我就知道, 好吧! ";
					link.l1 = "我全速航行, 拼命赶来, 玛丽。 你... 他们有没有? ..";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "我的船长... 你在这里... 我几乎失去了希望... ";
					link.l1 = "我尽快赶来了, 海伦。 很抱歉花了这么长时间。 ";
				}
				locCameraFromToPos(-15.32, 1.24, 1.31, true, -14.25, -1.00, -1.50);
			}
			link.l1.go = "PZ_TortureRoom_Devushka_2";
		break;
		
		case "PZ_TortureRoom_Devushka_2":
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "不, 查尔斯, 不。 他们试过了, 但我尽力反抗了。 这就是为什么他们把我打得这么惨... 求你了, 查尔斯, 我们离开这里吧... 好吗? ";
					link.l1 = "马上, 我亲爱的。 还有最后一件事要做。 ";
					link.l1.go = "PZ_TortureRoom_Devushka_3";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "他们没有那样做, 查尔斯! 他们没有。 其余的会愈合。 求你了, 带我离开这里。 ";
					link.l1 = "当然, 我亲爱的。 这里只剩下一件事要做。 ";
					link.l1.go = "PZ_TortureRoom_Devushka_3";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "不, 查尔斯, 不。 他们试过了, 但你及时赶到了。 就像以前一样。 这是第几次了? ";
					link.l1 = "我没数过, 玛丽。 我永远不会。 ";
					link.l1.go = "PZ_TortureRoom_Devushka_2_1";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "你到了... 正好及时。 最糟糕的事情没有发生。 现在, 求你了, 我们离开这里。 任何地方。 ";
					link.l1 = "站起来, 海伦。 上楼去。 我得先处理这个混蛋。 ";
					link.l1.go = "PZ_TortureRoom_Devushka_3";
				}
			}
		break;
		
		case "PZ_TortureRoom_Devushka_2_1":
			dialog.text = "我不会停止计数。 现在请让我们离开这个地方。 ";
			link.l1 = "当然, 我亲爱的。 我们在这里没有更多要做的了。 除了一件事。 ";
			link.l1.go = "PZ_TortureRoom_Longway_3";
		break;
		
		case "PZ_TortureRoom_Devushka_3":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko")) AddPassenger(pchar, npchar, false);
			LAi_SetPlayerType(pchar);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) ReturnOfficer_Mary();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) ReturnOfficer_Helena();
		break;
		
		case "PZ_TortureRoom_Levasser_18":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				dialog.text = "那又怎样, 哈-哈, 你没胆子, 流鼻涕的家伙? 让你的黄皮肤野猪帮你一把... 或者自己动手, 然后你就有理由告诉庞西你有多勇敢。 ";
				link.l1 = "我宁愿告诉大家你是个多么懦弱的混蛋。 ";
			}
			else
			{
				dialog.text = "怎么, 你真的想看我流血而死? 你很享受, 嗯? 你会告诉你的女人你是个英雄。 看到墙上的那具骷髅了吗? 圣地亚哥的银行家妻子... 她的男人也认为自己是英雄, 但当我把他放在那个轮子上旋转时, 他结果只是个好尖叫的人... ";
				link.l1 = "我可以把你的尸体放在上面, 混蛋, 但我担心它支撑不住你屁股的重量。 ";
			}
			link.l1.go = "PZ_TortureRoom_Levasser_19";
		break;
		
		case "PZ_TortureRoom_Levasser_19":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				dialog.text = "懦弱? 哦, 哈-哈, 来吧... ";
				link.l1 = "残忍不是懦弱的对立面。 但像你这样的人不会知道区别。 ";
				link.l1.go = "PZ_TortureRoom_Levasser_20";
			}
			else
			{
				dialog.text = "这很聪明。 记住我的话, 德.莫尔: 你会像那个大人物一样死去, 因为自己的尖叫而声音嘶哑, 因为你的... 的哭声而耳聋。 ";
				link.l1 = "在地狱里燃烧吧, 人渣。 ";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_TortureRoom_Levasser_Mertv1");
			}
		break;
		
		case "PZ_TortureRoom_Levasser_20":
			dialog.text = "是的, 我承认我不是哲学家。 看到墙上的那具骷髅了吗, 德.莫尔? 那是圣地亚哥银行家妻子剩下的全部。 他也喜欢说大话, 但当我开始把他的身体缠绕在那个轮子上时, 一切都停止了。 剩下的只有尖叫, 几乎让我耳聋... ";
			link.l1 = "我们把这结束吧。 ";
			link.l1.go = "PZ_TortureRoom_Levasser_21";
		break;
		
		case "PZ_TortureRoom_Levasser_21":
			StartInstantDialog("Longway", "PZ_TortureRoom_Levasser_22", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_22":
			dialog.text = "等一下, 船长阁下... 别这么快。 ";
			link.l1 = "怎么了, 朗威? ";
			link.l1.go = "PZ_TortureRoom_Levasser_23";
		break;
		
		case "PZ_TortureRoom_Levasser_23":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "玛丽";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "海伦";
			dialog.text = "别杀他。 太简单了。 他应得更糟的。 ";
			link.l1 = "你为你妹妹生气, 我的朋友。 而我为他对" + sStr + "所做的... 以及他可能对她做的感到愤怒。 但我不是像他那样的动物。 我可以用那个火盆里的煤烧他, 在那个轮子上打断他的骨头... 我可以给他戴上镣铐, 让他因失血而死。 但我不能冒险他的某个手下救他。 我不能冒这个险。 ";
			link.l1.go = "PZ_TortureRoom_Levasser_24";
		break;
		
		case "PZ_TortureRoom_Levasser_24":
			dialog.text = "等等, 船长阁下。 我不是那个意思。 我在说庞西。 ";
			link.l1 = "他怎么了? ";
			link.l1.go = "PZ_TortureRoom_Levasser_25";
		break;
		
		case "PZ_TortureRoom_Levasser_25":
			dialog.text = "想想如果你把这个动物活着交给他, 他会怎么奖励你。 他会给你大量的达布隆。 而这个人渣宁愿死在这里, 也不愿在卡普斯特维尔的地牢里腐烂。 ";
			link.l1 = "你可能是对的, 朗威。 但我不知道这个混蛋和骑士之间到底发生了什么。 相信我, 我比你更了解这群人。 如果像他们说的那样一切都是为了钱, 这两个人可能会达成交易。 庞西可能会放了他, 另一个这样的房间可能会出现在其他岛屿或旧世界的某个城市。 ";
			link.l1.go = "PZ_TortureRoom_Levasser_26";
			link.l2 = "主意不错, 朗威。 不过我怀疑骑士会那么慷慨... 这真的不是他的本性。 但对我来说, 这反正不是为了钱。 把他扶起来! 给他包扎伤口, 以免他提前死亡。 ";
			link.l2.go = "PZ_TortureRoom_Levasser_28";
		break;
		
		case "PZ_TortureRoom_Levasser_26":
			StartInstantDialogNoType("Levasser", "PZ_TortureRoom_Levasser_27", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_27":
			dialog.text = "但首先, 我要来找你。 还有你的伙伴。 我不会碰你, 斜眼男人 - 你不值得我浪费时间。 ";
			link.l1 = "你看, 朗威? 这一切必须现在结束。 此时此地。 ";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_TortureRoom_Levasser_Mertv1");
		break;
		
		case "PZ_TortureRoom_Levasser_28":
			StartInstantDialogNoType("Levasser", "PZ_TortureRoom_Levasser_29", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_29":
			dialog.text = "等一下, 船长, 等一下, 哈-哈。 ";
			link.l1 = "怎么了, 前总督先生? ";
			link.l1.go = "PZ_TortureRoom_Levasser_30";
		break;
		
		case "PZ_TortureRoom_Levasser_30":
			dialog.text = "我的钥匙在这个房间的某个地方。 它打开我办公室的一个箱子。 里面有二十万银币和一把好刀。 如果这还不够, 在我妻子的卧室里, 在五斗橱里, 有一批昂贵的宝石。 ";
			link.l1 = "嗯, 你想换什么? ";
			link.l1.go = "PZ_TortureRoom_Levasser_31";
		break;
		
		case "PZ_TortureRoom_Levasser_31":
			dialog.text = "一颗子弹。 现在就杀了我。 ";
			link.l1 = "那骑士德.庞西呢? 我听说你们是老朋友... 你不想见他吗? ";
			link.l1.go = "PZ_TortureRoom_Levasser_32";
		break;
		
		case "PZ_TortureRoom_Levasser_32":
			dialog.text = "去他妈的庞西! 那么, 你同意吗? ";
			link.l1 = "不太同意, 德... 先生。 我不想列出你的全名。 ";
			link.l1.go = "PZ_TortureRoom_Levasser_33";
		break;
		
		case "PZ_TortureRoom_Levasser_33":
			dialog.text = "这对你来说还不够吗? 好吧, 还有更多... ";
			link.l1 = "你受害者的尖叫一定让你耳聋了, 勒瓦瑟。 我告诉过你, 这不是为了钱。 你害怕庞西是有原因的, 对吧? 我甚至不想知道他会对你做什么。 但如果这能为你的... 艺术带来一点报应, 那就这样吧。 ";
			link.l1.go = "PZ_TortureRoom_Levasser_34";
			pchar.questTemp.PZ_LevasserPlenen = true;
			pchar.questTemp.PZ_LevasserPobezhden = true;
		break;
		
		case "PZ_TortureRoom_Levasser_34":
			dialog.text = "所以这就是你的真面目, 哈-哈... 不比我好。 ";
			link.l1 = "够了。 朗威 - 把他扶起来! ";
			link.l1.go = "PZ_TortureRoom_Levasser_35";
		break;
		
		case "PZ_TortureRoom_Levasser_35":
			DialogExit();
			
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition.l1 = "locator";
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition.l1.location = "Tortuga_Torture_room";
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition.l1.locator_group = "reload";
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition.l1.locator = "reload1";
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition = "PZ_TortureRoom_Levasser_ObratnoNaBereg";
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) ReturnOfficer_Mary();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) ReturnOfficer_Helena();
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom")) ReturnOfficer_Longway();
			sld = CharacterFromID("Levasser");
			sld.location = "None";
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		break;
		
		case "PZ_Etap6_NaBeregu_DevaZdorovaya_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
				{
					dialog.text = "我们的船... 我从没想过我会这么高兴看到她... 好吧。 终于, 这场噩梦结束了。 ";
				}
				else
				{
					dialog.text = "终于结束了。 现在去哪里, 查尔斯? ";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
				{
					dialog.text = "我不敢相信一切都结束了... 我们现在做什么, 我的船长? ";
				}
				else
				{
					dialog.text = "好吧, 就这样, 我的船长。 我们现在做什么? ";
				}
			}
			if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
			{
				link.l1 = "唉, 还没有结束。 长兴... 只有当我从她那里得到答案时, 这个故事才真正结束。 ";
				link.l1.go = "PZ_Etap6_NaBeregu_DevaZdorovaya_2";
			}
		else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LevasserPlenen"))
				{
					link.l1 = "航向卡普斯特维尔。 是时候让勒瓦瑟先生成为历史的一部分了。 ";
				}
				else
				{
					link.l1 = "骑士的任务完成了。 我需要向他报告。 不过我会省略一些细节。 我只希望他信守诺言, 米歇尔能被释放... ";
				}
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_Final_SdaemKvestPuansi");
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaZdorovaya_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "我也是, 好吧。 所以我和你一起去。 查尔斯, 别想跟我争辩。 ";
				link.l1 = "玛丽, 亲爱的, 你需要休息。 你都快晕倒了... ";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "我和你一起去。 ";
				link.l1 = "海伦, 你差点死在那个恶魔手里。 你几乎站不稳... ";
			}
			link.l1.go = "PZ_Etap6_NaBeregu_DevaZdorovaya_3";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaZdorovaya_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "我需要你, 查尔斯。 你也需要我。 如果今晚有人会晕倒, 那一定是长兴。 在她妓院的地板上, 眉间中枪! ";
				link.l1 = "是啊, 勒瓦瑟没能打掉你的战斗精神。 我本想送你回船, 但我知道你还是会跟着我... ";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "但我还能握剑。 查尔斯, 我必须去那里。 我需要理解是什么驱使她这么做。 你明白为什么这对我如此重要吗? ";
				link.l1 = "我明白你需要休息和疗伤。 而且需要很长时间。 ";
			}
			link.l1.go = "PZ_Etap6_NaBeregu_DevaZdorovaya_4";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaZdorovaya_4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "你太了解我了, 查尔斯, 好吧。 所以我们别再闲聊了, 把这事做完。 ";
				link.l1 = "随你便。 但保持警惕。 没人知道外面有什么惊喜在等着我们。 ";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "可以等。 你为我而来, 现在我要和你一起去。 不管你愿不愿意。 ";
				link.l1 = "我看得出你还有勇气, 海伦。 很好。 跟在我后面, 看在上帝的份上, 小心点。 ";
			}
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_SDevushkoyKShin");
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_1":
			if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "我们的船... 真不敢相信我又要登上她了, 好吧... ";
					link.l1 = "她在等你, 玛丽。 还有丰盛的饭菜和柔软的床... ";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "呃... 没想到我能自己走到船上。 ";
					link.l1 = "你是我见过最坚韧的人, 海伦。 现在进去, 然后上床... ";
				}
				link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_2";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "我们的船... 真不敢相信我又要登上她了, 好吧... ";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "呃... 没想到我能自己走到船上。 ";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_LevasserPlenen"))
				{
					link.l1 = "航向卡普斯特维尔。 是时候让勒瓦瑟先生成为历史的一部分了。 ";
				}
				else
				{
					link.l1 = "骑士的任务完成了。 我需要向他报告。 不过我会省略一些细节。 我只希望他信守诺言, 米歇尔能被释放... ";
				}
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_Final_SdaemKvestPuansi");
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "还有你, 查尔斯... 为什么是那种表情? 你又在打什么主意, 不是吗? ";
				link.l1 = "长兴。 我也必须找到她。 ";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "那你呢? 你要去哪里? ";
				link.l1 = "去见长兴。 她是这场噩梦的最后一章。 ";
			}
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_3";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "那我和你一起去! 她欠我太多了, 好吧! ";
				link.l1 = "玛丽, 亲爱的, 你好不容易才走到船上。 而且你现在连剑都握不稳。 我会让她为对你做的一切付出代价, 我向上帝发誓。 但如果你留在船上, 知道你安全, 我会感觉好多了。 ";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "我的船长, 我很想和你一起去... 请小心。 谁知道她还能干出什么? 她按住我, 而那个混蛋蒂博... ";
				link.l1 = "最糟糕的已经过去了, 海伦。 很快就会结束, 我保证。 ";
			}
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_4";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
				{
					dialog.text = "好吧, 至少朗韦会在我不在的时候支持你。 但如果你出了什么事, 我会亲手把他和长兴埋了! ";
					link.l1 = "会没事的。 现在去休息。 我很快就会回来。 ";
					link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_7";
				}
				else
				{
					dialog.text = "朗韦去哪了, 查尔斯? ";
					link.l1 = "他没等我就去找长兴了。 我拦不住他, 但我能怎么办? ";
					link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_5";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
				{
					dialog.text = "好吧, 至少朗韦和你一起去。 这至少让人安心一些。 ";
					link.l1 = "看到了吗? 没必要担心。 我不会去太久。 ";
					link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_7";
				}
				else
				{
					dialog.text = "朗韦在哪? 我刚意识到他不在这儿。 ";
					link.l1 = "他没等我就去找他妹妹了。 我不怪他。 他等这一刻等了太久。 ";
					link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_5";
					
				}
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_5":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "查尔斯, 我有种不祥的预感... ";
				link.l1 = "我知道。 这场噩梦持续得太久了, 结局已经不远。 最糟糕的已经过去了。 ";
				link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_6";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "谁知道他在想什么, 查尔斯? 保持警惕, 好吗? ";
				link.l1 = "我会的。 我很快就会回来, 海伦。 ";
				link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_7";
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_6":
			dialog.text = "答应我你会做好任何准备。 ";
			link.l1 = "我准备好了, 也会做好准备。 我很快就会回来, 玛丽。 ";
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_7";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_7":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom")) StartInstantDialog("Longway", "PZ_Etap6_NaBeregu_DevaBolnaya_8", "Quest\CompanionQuests\Longway.c");
			else
			{
				DialogExit();
				LAi_SetPlayerType(pchar);
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sld = CharacterFromID("Mary");
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sld = CharacterFromID("Helena");
				LAi_ActorRunToLocation(sld, "reload", "sea", "", "", "", "", -1);
				sld.location = "None";
				AddQuestRecord("PZ", "51");
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) AddQuestUserData("PZ", "sText", "Mary");
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) AddQuestUserData("PZ", "sText", "Helen");
				PChar.quest.PZ_Etap6_BrothelPoiskSestry.win_condition.l1 = "location";
				PChar.quest.PZ_Etap6_BrothelPoiskSestry.win_condition.l1.location = "Tortuga_brothelElite";
				PChar.quest.PZ_Etap6_BrothelPoiskSestry.win_condition = "PZ_Etap6_BrothelPoiskSestry";
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_8":
			dialog.text = "朗韦帮了你, 船长。 现在轮到你遵守诺言了。 ";
			link.l1 = "你都听到了, 朗韦。 我们去见你妹妹。 ";
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_9";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_9":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "尊敬的船长, 朗韦有最后一个请求: 让长兴解释自己的行为。 在你做任何决定之前, 先听听她怎么说。 ";
			link.l1 = "玛丽遭遇的一切都怪她。 但我会给她一个解释的机会。 ";
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_10";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_10":
			dialog.text = "朗韦信任你的承诺。 你的判断和你的仁慈。 ";
			link.l1 = "伙计, 在这场血腥的混乱中, 没有理性或仁慈的余地。 是时候结束这一切了。 ";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_SLongwayKShin");
		break;
		
		case "PZ_LongwayPrishelOdin":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sStr = "Helen";
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				dialog.text = "尊敬的船长... ";
				link.l1 = sStr + "死了。 ";
				link.l1.go = "PZ_LongwayPrishelOdin2";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					dialog.text = "船长, " + sStr + "女士, 很高兴见到你。 这位是... 长兴。 ";
					link.l1 = "我猜到了, 朗韦。 退后。 你已经有足够的时间和你妹妹交谈了。 现在她必须为帮助勒瓦瑟的手下绑架" + sStr + "向她作出回答。 ";
					link.l1.go = "PZ_LongwayPrishelOdin7";
				}
				else
				{
					dialog.text = "你来了... " + sStr + "女士在哪里? 她... ? ";
					link.l1 = "不, 朗韦。 谢天谢地, 没有。 我把她送到船上去了。 否则, 我甚至不会在这里进行这场对话。 然而, 这仍然不会轻松或愉快。 ";
					link.l1.go = "PZ_LongwayPrishelOdin12";
				}
			}
		break;
		
		case "PZ_LongwayPrishelOdin2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "长兴和我向你表示哀悼... ";
			link.l1 = "长兴的哀悼? ! 你不妨代表勒瓦瑟向我表示哀悼, 朗韦! 你很清楚, 她和其他爪牙一起参与了绑架" + sStr + "的行动! 现在她走了... ! ";
			link.l1.go = "PZ_LongwayPrishelOdin3";
		break;
		
		case "PZ_LongwayPrishelOdin3":
			dialog.text = "我们... 我理解你现在的感受, 尊敬的船长。 ";
			link.l1 = "哦, 真的吗? ";
			link.l1.go = "PZ_LongwayPrishelOdin4";
		break;
		
		case "PZ_LongwayPrishelOdin4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "我失去了父母, 你还记得。 如果你还记得的话。 此外, 折磨并杀害" + sStr + "的不是长兴。 我理解你的痛苦, 你的愤怒。 但我妹妹的罪行还轮不到你来评判。 请听我说完。 ";
			link.l1 = "我记得。 我会听你讲故事。 但长话短说! 要知道, 我不能让这样的事情不受惩罚! ";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LongwayPrishelOdin_ChangShinNext");
		break;
		
		case "PZ_LongwayPrishelOdin5":
			dialog.text = "那我最好再从头讲一遍, 德.莫尔先生。 我们的图法语太差了, 你差点攻击他。 ";
			link.l1 = "你应该闭嘴。 我没打算攻击朗韦, 但你... 你才是她死亡的罪魁祸首。 ";
			link.l1.go = "PZ_LongwayPrishelOdin6";
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			sld = characterFromId("Longway");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto9", "PZ_LongwayTurnToChangShin", -1);
		break;
		
		case "PZ_LongwayPrishelOdin6":
			dialog.text = "我会反驳这一点, 但我意识到我宁愿不反驳。 图把你描述成一个值得尊敬和理解的人。 但真的是这样吗? 我还有必要开口吗? 还是你已经下定决心了? ";
			link.l1 = "你知道如何看透别人的心思, 小姐。 现在真的不值得争论。 但如果你想为自己辩解... 好吧, 说吧。 看在朗韦的份上, 我会听你说。 ";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_LongwayPrishelOdin7":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "她可以解释一切, 尊敬的船长... 事情不是你想的那样... 真的不是... ";
			link.l1 = "那就解释一下。 但不是向我解释。 " + sStr + "。 看着她的眼睛。 看看她的瘀伤和伤口。 然后告诉她事情不是那样的。 ";
			link.l1.go = "PZ_LongwayPrishelOdin8";
		break;
		
		case "PZ_LongwayPrishelOdin8":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "我代表星向你道歉, 船长... ";
			link.l1 = "从她得意的表情来看, 你是在白费力气。 她不值得你道歉。 ";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LongwayPrishelOdin_ChangShinNext");
		break;
		
		case "PZ_LongwayPrishelOdin9":
			dialog.text = "你对他太苛刻了, 德.莫尔先生。 不过你可能已经习惯了像对待典型的黄皮肤劳工那样对待他。 ";
			link.l1 = "你想让朗韦反对我吗? 这行不通。 我一直尊重他, 他也知道这一点。 这才是最重要的。 我意识到玩游戏是你现在唯一能做的。 ";
			link.l1.go = "PZ_LongwayPrishelOdin10";
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			sld = characterFromId("Longway");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto9", "PZ_LongwayTurnToChangShin", -1);
		break;
		
		case "PZ_LongwayPrishelOdin10":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "你想怎么做? 在可怜的图终于在十年后再次找到家人时, 把他带走? ";
			link.l1 = "血缘并不总是意味着家庭。 但你建议我们怎么做? 让你对" + sStr + "所做的一切不受惩罚? 让朗韦偶尔去看望一个毫不留情地贩卖其他女孩的女人? ";
			link.l1.go = "PZ_LongwayPrishelOdin11";
		break;
		
		case "PZ_LongwayPrishelOdin11":
			dialog.text = "嗯, 首先, 听着。 不像他, 我能用完美的法语复述我刚才告诉他的话。 我的故事。 直视你的眼睛, 甚至是她的眼睛。 而且这一切都没有你可能已经厌倦的口音。 毕竟, 我们都有什么可失去的? ";
			link.l1 = "我习惯了朗韦的口音; 这是他对我而言的一部分。 我会听你说, 但只是为了我的朋友。 继续。 ";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_LongwayPrishelOdin12":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "为什么不呢, 尊敬的船长... ? ";
			link.l1 = "你真的需要问吗? 她参与了绑架" + sStr + ", 不是吗? ";
			link.l1.go = "PZ_LongwayPrishelOdin13";
		break;
		
		case "PZ_LongwayPrishelOdin13":
			dialog.text = "我... 真诚地道歉。 这也是我的错, 没能在十年前救回我的妹妹, 没能保护她免受这一切的伤害。 ";
			link.l1 = "你不应该为那些毫无悔意的人道歉, 朗韦。 你说完了吗? 轮到我和她谈谈了。 ";
			link.l1.go = "PZ_LongwayPrishelOdin14";
		break;
		
		case "PZ_LongwayPrishelOdin14":
			dialog.text = "尊敬的船长, 等等! 长兴和勒瓦瑟不一样。 不完全一样。 她会告诉我这十年来她的生活。 也让我告诉你。 ";
			link.l1 = "好吧, 朗韦。 我在听。 很多事情取决于你要告诉我什么。 ";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LongwayPrishelOdin_ChangShinNext");
		break;
		
		case "PZ_LongwayPrishelOdin15":
			dialog.text = "如果是你说, 我们都会头疼。 让我来, 图。 我猜你是查尔斯.德.莫尔? ";
			link.l1 = "没错。 而你是贝儿.埃托勒, 也被称为长兴。 你和蒂博。 马蒂内一起参与了绑架我的爱人。 当我提到这件事时, 你还在笑。 美好的回忆? ";
			link.l1.go = "PZ_LongwayPrishelOdin16";
		break;
		
		case "PZ_LongwayPrishelOdin16":
			dialog.text = "否认也没用。 但现在又怎样? 你要在我哥哥面前折磨我吗? 还是让他帮你折磨我? 或者干脆杀了我? 你真的会对他这么做吗? ";
			link.l1 = "就像我说的, 尽管我现在很想做, 但我还是在和你说话。 别逼我。 告诉我你之前告诉他的话。 然后我们再看看接下来会怎样。 ";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_Longway_91":
			if (!CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden"))
			{
				dialog.text = "我还是不敢相信长兴会变成... 这样。 ";
				link.l1 = "人是会变的, 朗韦。 任何人都可能被击垮, 或者被磨灭最后一丝善良和信念。 ";
				link.l1.go = "PZ_Longway_ToGirl1";
			}
			else
			{
				dialog.text = "朗韦还是不敢相信我妹妹会变成... 这样。 为什么... 为什么? 要是那天我在家就好了... ";
				link.l1 = "别为假设的事情自责。 此外, 这些年来你也没有闲着 —你一直在努力弥补。 ";
				link.l1.go = "PZ_Longway_ToShore1";
			}
		break;
		
		case "PZ_Longway_ToGirl1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "呃... 我想就是这样, 尊敬的船长。 ";
			link.l1 = "我们离开这里吧。 我们还有清理她留下的烂摊子, 尽快救出" + sStr + "。 ";
			link.l1.go = "PZ_Longway_ToGirl2";
		break;
		
		case "PZ_Longway_ToGirl2":
			dialog.text = "是。 我们得快点 —因为我已经耽误太久了。 ";
			link.l1 = "这不是你的错, 朗韦。 我们快点! ";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LeaveEliteBrothel");
		break;
		
		case "PZ_Longway_ToShore1":
			dialog.text = "对。 谢谢你的支持, 尊敬的船长。 ";
			link.l1 = "别客气。 她根本不值得你奉献 —即使她本可以, 她也没有主动找过你。 你的星星早已熄灭, 她很久以前就不再是你的家人了。 现在我们是你的家人, 朗韦。 ";
			link.l1.go = "PZ_Longway_ToShore2";
		break;
		
		case "PZ_Longway_ToShore2":
			dialog.text = "是的... 确实如此。 而我一直太盲目, 直到现在才明白。 ";
			link.l1 = "迟到总比不到好。 现在让我们回家 —我们的船在等着我们。 ";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LeaveEliteBrothel");
		break;
		
		case "PZ_Mary_91":
			dialog.text = "好吧。 你根本不知道我有多期待这一刻。 ";
			link.l1 = "我相信我知道。 你感觉如何, 玛丽? 我之所以想避免流血冲突, 是因为我不确定你是否能像往常一样稳稳地握剑 —当我忙着对付另一个人时, 他们中的一个可能会占上风。 ";
			link.l1.go = "PZ_Mary_92";
		break;
		
		case "PZ_Mary_92":
			dialog.text = "你低估我了。 此外, 愤怒是一剂良药。 我毫不怀疑你会来救我 —就像你总是做的那样, 好吧。 你知道吗, 查尔斯... 尽管你称我为你的红色护身符, 但如果你也是我的护身符呢? 当我们在一起时, 总会发生一些奇妙的事情。 ";
			link.l1 = "我是你的护身符? 为什么, 我喜欢这个想法。 ";
			link.l1.go = "PZ_Mary_93";
		break;
		
		case "PZ_Mary_93":
			dialog.text = "看吧, 你已经在笑了! 现在让我们离开这个恶心的地方 —快点, 快点, 好吧。 ";
			link.l1 = "呃呵, 这场混乱让我深受打击。 我希望它能以任何其他方式结束。 ";
			link.l1.go = "PZ_Mary_94";
		break;
		
		case "PZ_Mary_94":
			dialog.text = "我不希望。 她无可救药了, 查尔斯。 她还把朗韦拖下了水。 他做出了选择, 也让我们别无选择。 想想我们今天帮助的那些人。 ";
			link.l1 = "再一次, 我无法反驳你, 玛丽。 这次我甚至不想反驳。 来吧, 我的红色护身符... ";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LeaveEliteBrothel");
		break;
		
		case "PZ_ElitaShluha_Final1":
			if (CheckAttribute(pchar, "questTemp.PZ_ChangShinMertva"))
			{
				dialog.text = "那里发生了什么, 先生? 我们听到了咒骂和喊叫。 但直到一切结束我们才敢呼救。 ";
				link.l1 = "你们做得对。 你们的女主人死了。 你们自由了。 如果我是你们, 我会收集妓院的钱财, 平分后尽快逃离这个岛屿。 我知道你们是可敬的女士, 而不仅仅是妓女, 所以你们会有一个超越这个悲惨地方的未来。 ";
				link.l1.go = "PZ_ElitaShluha_Final2";
			}
			else
			{
				dialog.text = "哦, 是你, 先生。 你知道女主人什么时候下来吗? ";
				link.l1 = "不会很快。 如果我是你, 我会远离那扇门。 永远不要和她谈论今晚的事 —她不会分享任何事情, 好奇的猫会一次性丢掉性命。 看来你们的老板娘不喜欢任何人窥探她的秘密。 ";
				link.l1.go = "PZ_ElitaShluha_Final3";
			}
		break;
		
		case "PZ_ElitaShluha_Final2":
			dialog.text = "是你杀了她? ! ";
			link.l1 = "是的。 如果你们逗留或试图叫卫兵来抓我, 那将是你们最大的错误。 她从来不是你们的守护神 —无论她给了你们多少丝绸和教育, 你们都被囚禁在这里, 被迫委身于她所指的任何乌合之众。 我祝你们一切顺利, 希望你们能顺利离开这里。 再见, 女士们。 ";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_ToTortugaStreets");
		break;
		
		case "PZ_ElitaShluha_Final3":
			dialog.text = "她真的没事吗? 我们可以进去吗? 我们需要叫卫兵吗? ";
			link.l1 = "她永远不会好了。 你们可以试着自己问她... 但要冒风险。 她还在和她哥哥谈话。 我想他们不会喜欢被打扰。 ";
			link.l1.go = "PZ_ElitaShluha_Final4";
		break;
		
		case "PZ_ElitaShluha_Final4":
			dialog.text = "我明白了... 好吧, 你有空再来看看我们, 先生。 ";
			link.l1 = "永远不会。 再见, 女士们。 ";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_ToTortugaStreets");
		break;
		
		case "PZ_TortugaSoldier1":
			dialog.text = "站住! 有人报告说从埃托勒小姐的住所传来尖叫和打斗声。 卫兵认为你与此事有关。 放下武器, 跟我们走, 先生。 ";
			if (!CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				link.l1 = "没错, 但我们不是挑起争斗的人, 我们是结束它的人。 雇佣的暴徒因拖欠工资而反叛, 袭击了埃托勒夫人以抢劫她。 相信雇佣军, 对吧? 我们赢了这一天, 但不幸的是, 她没能活下来。 ";
				link.l1.go = "PZ_TortugaSoldier2";
			}
			else
			{
				link.l1 = "我今天失去了我的挚爱, 所以让我过去吧, 警官。 ";
				link.l1.go = "PZ_TortugaSoldierGirlDied1";
			}
		break;
		
		case "PZ_TortugaSoldier2":
			dialog.text = "你知道我们不能只听你一面之词, 对吧? 我们必须拘留你。 你需要妓院的女性员工作为证人。 让我们看看她们有什么要说的。 ";
			link.l1 = "我爱的人受了重伤。 我也累得要死。 你们就不能让我们走吗? ";
			link.l1.go = "PZ_TortugaSoldier3";
		break;
		
		case "PZ_TortugaSoldier3":
			dialog.text = "我们会尽快解决这件事。 现在跟我们走。 ";
			link.l1 = "见鬼去吧... ";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TortugaSoldiersFight");
		break;
		
		case "PZ_TortugaSoldierGirlDied1":
			dialog.text = "节哀顺变, 先生。 我还不是警官, 但... 不管怎样, 算了。 你能和我们一起去, 告诉我们那里发生了什么吗? ";
			link.l1 = "我会告诉你的。 妓院正在赔钱, 没有现金支付守卫的雇佣军。 他们决定拿走剩下的东西, 就在我碰巧在那里的时候。 埃托勒夫人和我击退了他们, 但她因伤重去世。 现在, 终于让我过去了。 ";
			link.l1.go = "PZ_TortugaSoldierGirlDied2";
		break;
		
		case "PZ_TortugaSoldierGirlDied2":
			dialog.text = "我很想让你过去, 但有很多文书工作要做。 我还需要采访在这里工作的女士们。 恐怕你至少得在镇上呆一天, 即使你说的是真的, 先生。 ";
			link.l1 = "见鬼去吧... ";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TortugaSoldiersFight");
		break;
		
		case "PZ_Longway_101":
			dialog.text = "朗韦有东西给你, 船长先生。 ";
			link.l1 = "多么美丽而奇特。 我从未见过这样的东西。 这是什么? ";
			link.l1.go = "PZ_Longway_102";
			GiveItem2Character(PChar, "talisman14");
			PlaySound("interface\important_item.wav");
		break;
		
		case "PZ_Longway_102":
			dialog.text = "这是我家乡的船长护身符。 既然朗韦不再是船长了, 我就把它送给你。 ";
			link.l1 = "谢谢你, 朗韦。 随着范德温克的死, 你向所有你想复仇的人报了仇。 我很高兴一切都这样解决了。 ";
			link.l1.go = "PZ_Longway_103";
		break;
		
		case "PZ_Longway_103":
			dialog.text = "要是我能说服星重新做个好人就好了... ";
			link.l1 = "她不会再听任何人的话了, 甚至是她的哥哥。 你已经尽力了。 我们都尽力了。 ";
			link.l1.go = "PZ_Longway_104";
		break;
		
		case "PZ_Longway_104":
			dialog.text = "是的... 非常感谢, 尊敬的船长。 朗韦重获自由, 又有了家和朋友。 ";
			link.l1 = "不客气, 我的朋友。 现在, 你为什么不和我一起去拜访我的哥哥呢? 哦, 真是讽刺! ";
			link.l1.go = "PZ_Longway_105";
		break;
		
		case "PZ_Longway_105":
			DialogExit();
			DeleteAttribute(npchar, "CompanionDisable");//тeпeрь можeм и в компаньоны
			chrDisableReloadToLocation = false;
			ReturnOfficer_Longway();
		break;
		
		case "PZ_PuansieDialogWithLevasser_1":
			dialog.text = "我们又见面了, 弗朗索瓦。 看来生活对你不薄啊, 呵呵。 ";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_1_1";
			LAi_SetHuberType(npchar);
		break;
		case "PZ_PuansieDialogWithLevasser_1_1":
			StartInstantDialog("Levasser", "PZ_PuansieDialogWithLevasser_2", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_2":
			dialog.text = "普安西, 你这个贪婪的混蛋... 差点被你金库里的金子噎死, 你还不满足? ";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_2_1";
			CharacterTurnByChr(npchar, CharacterFromID("Puancie"));
		break;
		case "PZ_PuansieDialogWithLevasser_2_1":
			StartInstantDialogNoType("Puancie", "PZ_PuansieDialogWithLevasser_3", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_3":
			//LAi_SetActorType(npchar);
			//LAi_ActorSetHuberMode(npchar);
			dialog.text = "我会和你分享一些, 弗朗索瓦。 你会有足够的, 相信我。 ";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_3_1";
			//LAi_tmpl_SetDialog(npchar, pchar, -1.0);
		break;
		case "PZ_PuansieDialogWithLevasser_3_1":
			StartInstantDialog("Levasser", "PZ_PuansieDialogWithLevasser_4", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_4":
			dialog.text = "什么... 你是什么意思? ";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_4_1";
			CharacterTurnByChr(npchar, CharacterFromID("Puancie"));
		break;
		case "PZ_PuansieDialogWithLevasser_4_1":
			StartInstantDialogNoType("Puancie", "PZ_PuansieDialogWithLevasser_5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_5":
			dialog.text = "";
			link.l1 = "总督阁下, 你打算... ";
			link.l1.go = "PZ_PuansieDialogWithLevasser_6";
		break;
		
		case "PZ_PuansieDialogWithLevasser_6":
			dialog.text = "查尔斯, 我的朋友, 你完成了你的工作, 而且做得非常出色! 这个人会怎么样不应该是你关心的... 然而, 船长, 知道这一点对你可能会有用, 以防你聪明的脑袋有什么愚蠢的想法。 可以说, 我们的共同朋友将面临一场严重的消化不良。 我听说金子对胃不好... 我希望我不需要进一步解释。 ";
			link.l1 = "不, 总督阁下。 ";
			link.l1.go = "PZ_PuansieDialogWithLevasser_7";
		break;
		
		case "PZ_PuansieDialogWithLevasser_7":
			dialog.text = "与弗朗索瓦先生不同, 你有一个光明的未来, 查尔斯。 孩子们, 把那头猪送到监狱去! ";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_7_1";
		break;
		case "PZ_PuansieDialogWithLevasser_7_1":
			StartInstantDialog("Levasser", "PZ_PuansieDialogWithLevasser_8", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_8":
			dialog.text = "放开我, 你们这些杂种! 你满意了吗, 德.莫尔? ! 去你妈的! 你们俩都会和我一起在地狱里被油炸! ";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LevasserVGostyahUPuansie3");
			CharacterTurnByChr(npchar, CharacterFromID("Puancie"));
			sld = characterFromID("PZ_SoldFra_1");
			CharacterTurnByChr(sld, CharacterFromID("Levasser"));
			sld = characterFromID("PZ_SoldFra_2");
			CharacterTurnByChr(sld, CharacterFromID("Levasser"));
		break;
		
		case "PZ_Baker_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Kasper";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Sharp";
			dialog.text = "好了, 先生。 我检查了" + sStr + "小姐... ";
			link.l1 = "情况有多糟, 雷蒙德? ";
			link.l1.go = "PZ_Baker_2";
		break;
		
		case "PZ_Baker_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					dialog.text = "没什么可担心的, 船长。 玛丽当然伤得很重, 但总的来说, 一切都会好的。 她应该卧床几天, 我预计两周后她就能恢复行动。 ";
					link.l1 = "我知道了。 谢谢, 雷蒙德。 退下吧。 ";
					link.l1.go = "PZ_Baker_4";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
				{
					dialog.text = "玛丽被打得很惨, 船长。 有瘀伤。 割伤... 当然还有震惊 —尽管她试图不表现出来。 ";
					link.l1 = "她一如既往地坚强。 但我想她意识到现在最好卧床休息。 不过要多久? ";
					link.l1.go = "PZ_Baker_3";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
				{
					dialog.text = "即使是职业士兵也很难在她经历的事情中幸存下来, 船长。 扭伤。 拉伤。 瘀伤 —我们很幸运那些混蛋没有打断她的骨头。 不过, 她的肌腱受损了, 所以至少一个月内她无法挥剑。 ";
					link.l1 = "去他的剑。 她什么时候能站起来? ";
					link.l1.go = "PZ_Baker_3";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					dialog.text = "别担心, 船长。 海伦受伤了, 但不严重。 她现在必须卧床, 但我想两周内她会完全康复。 ";
					link.l1 = "我知道了。 谢谢, 雷蒙德。 退下吧。 ";
					link.l1.go = "PZ_Baker_4";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
				{
					dialog.text = "她被打得很惨, 船长。 身体上的伤害只是诊断的一部分... 待在那个可怕的地方让她想起了在杨梅号上经历的噩梦。 ";
					link.l1 = "当然... 该死! 她什么时候能站起来? ";
					link.l1.go = "PZ_Baker_3";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
				{
					dialog.text = "海伦在刀刃上行走, 船长。 我很惊讶她在经历了这一切后还能活下来。 没有内出血或骨折, 但有很多扭伤和拉伤。 ";
					link.l1 = "可怜的东西。 她需要多久才能康复? ";
					link.l1.go = "PZ_Baker_3";
				}
			}
		break;
		
		case "PZ_Baker_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
				{
					dialog.text = "至少一周, 先生。 如果她听从我的建议, 大约一个月后应该能恢复行动。 ";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
				{
					dialog.text = "至少两周前不行, 先生。 之后, 我允许她在甲板上短时间散步。 完全康复至少需要两个月。 ";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
				{
					dialog.text = "先生, 至少一周内别打扰她, 我只能告诉你这些。 完全康复需要大约一个月。 ";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
				{
					dialog.text = "她应该卧床两周; 之后, 她可能可以在甲板上走动。 但别指望至少两个月内看到她恢复行动。 ";
				}
			}
			link.l1 = "我知道了。 谢谢, 雷蒙德。 退下吧。 ";
			link.l1.go = "PZ_Baker_4";
		break;
		
		case "PZ_Baker_4":
			DialogExit();
			sld = CharacterFromID("Baker");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "PZ_RazgovorSVrachom_4", -1);
		break;
		
		case "PZ_DevushkaVstalaSKrovati_Dialog1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "没想到躺了这么久, 自己站起来比想象中难, 好吧! ";
				link.l1 = "也许你不该这么突然停止卧床休息, 亲爱的。 ";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "哦-哈, 我的头... ";
				link.l1 = "海伦! 你是不是起得太早了? 你几乎站不稳! ";
			}
			link.l1.go = "PZ_DevushkaVstalaSKrovati_Dialog2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_DevushkaVstalaSKrovati_Dialog2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "我宁愿烧了这该死的床也不愿再躺上去 —至少在我从船头走到船尾再回来之前! ";
				link.l1 = "这是一张舒适的好床。 船也不错。 所以我不打算阻止你。 但我会在那里确保你不做傻事。 ";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "我没事, 船长, 虽然还没完全好。 我还没准备好挥剑, 但我极其讨厌这张床。 ";
				link.l1 = "好吧, 在甲板上短时间散步可能不会伤害你。 但连想都别想靠近缆绳! ";
			}
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DevushkaStoitVosstanovlenie");
		break;
		
		case "PZ_DevushkaSnovaOfficer_Sex1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "查尔斯, 你不觉得你已经把我忘了吗? 提醒我我们上次同床是什么时候, 好吧! ";
				link.l1 = "在... 我们别谈那个了, 好吗, 玛丽? ";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "我的船长, 我作为女人已经不能让你感兴趣了吗? ";
				link.l1 = "真没想到, 海伦。 通常都是我提起... 但我不确定你在... 之后是否准备好了。 ";
			}
			link.l1.go = "PZ_DevushkaSnovaOfficer_Sex2";
			DelLandQuestMark(npchar);
			pchar.questTemp.PZ_DevushkaSnovaOfficer = true;
			DeleteQuestCondition("PZ_DevushkaSnovaOfficer2");
		break;
		
		case "PZ_DevushkaSnovaOfficer_Sex2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "那至少谈谈我, 好吧。 或者在那两个混蛋打我之后, 我变得让你讨厌了? ";
				link.l1 = "这是我听过最愚蠢的话。 我只是不想在你准备好之前打扰你。 既然你已经... ";
				link.l1.go = "PZ_DevushkaSnovaOfficer_Sex3";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "没关系, 查尔斯, 真的。 我只是尽量不去想它。 此外, 你把我从最坏的情况中救了出来。 所以我们别说话了, 只是... 弥补一下。 ";
				link.l1 = "这是个该死的好主意, 海伦。 ";
				link.l1.go = "exit";
				pchar.quest.sex_partner = Npchar.id;
				AddDialogExitQuestFunction("LoveSex_Cabin_Go");
			}
		break;
		
		case "PZ_DevushkaSnovaOfficer_Sex3":
				dialog.text = "查尔斯, 我不是想要, 我是在要求, 好吧! ";
				link.l1 = "我不敢拒绝你... ";
				link.l1.go = "exit";
				pchar.quest.sex_partner = Npchar.id;
				AddDialogExitQuestFunction("LoveSex_Cabin_Go");
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "查尔斯, 我们需要谈谈, 好吧。 ";
				link.l1 = "有什么不对劲吗, 玛丽? 你看起来很焦虑, 通常这不是好兆头。 ";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "我的船长, 有件事我需要告诉你。 ";
				link.l1 = "是吗, 海伦? 我在听。 ";
			}
			link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "就是这样! 我准备好恢复军官职责了, 这不是好事吗? ";
				link.l1 = "原来如此。 好吧, 如果你觉得足够强壮, 不仅是好事, 更是太棒了。 ";
				link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog3";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "我厌倦了船员像看虚弱的老妇人一样盯着我。 我想回到舵轮前, 通过练习挥剑来伸展手臂... ";
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					link.l1 = "如果你觉得可以, 我不反对, 亲爱的。 我去拿你的装备。 我会很高兴让你掌舵。 但战斗中要小心, 好吗? ";
					link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog2_1";
				}
				else
				{
					link.l1 = "驾驶台上很想念你, 海伦。 至于剑, 我想是时候把它还给你了。 ";
					link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog3";
				}
			}
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog2_1":
			dialog.text = "当然, 我的船长, 听你的。 ";
			link.l1 = "好。 ";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DevushkaSnovaOfficer3");
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "太好了, 好吧! 我等不及要练习剑术了... ";
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					link.l1 = "很高兴听到这个, 玛丽。 但不要一下子就投入战斗... 但我在跟谁说话呢? ";
					link.l1.go = "exit";
					AddDialogExitQuest("PZ_DevushkaSnovaOfficer3");
				}
				else
				{
					link.l1 = "我想你会很高兴看到那把帕拉什回到剑鞘... ";
					link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog4";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "我... 我不知道该说什么, 查尔斯。 我才意识到这把弯刀对我有多重要... ";
				link.l1 = "我早就知道了, 所以它一直安全地等着你。 ";
				link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog4";
				notification("Gave Cutlass of Blaze", "None");
				PlaySound("interface\important_item.wav");
			}
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "我的独角鲸, 好吧!!! 查尔斯, 你救了它! 我不只是高兴, 我是激动! 谢谢你, 谢谢你! 我好怕它留在马丁的船上... ";
				link.l1 = "这把刀属于你的手, 我的红色护身符。 我相信你不会再弄丢了... 好吧, 我不打扰你们团聚了, 哈哈! ";
				notification("Gave Narwhal", "None");
				PlaySound("interface\important_item.wav");
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_DevushkaSnovaOfficer3");
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "谢谢你, 查尔斯。 你知道, 这可能就是我爱你的原因... ";
				link.l1 = "因为找回丢失的东西? 哈哈哈... ";
				link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog5";
			}
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog5":
			dialog.text = "你在笑, 但我是认真的。 ";
			link.l1 = "我知道, 海伦。 我也爱你, 尽管我还不确定为什么。 ";
			link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog6";
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog6":
			dialog.text = "也许因为我还没用这把弯刀砍你。 ";
			link.l1 = "我会躲到小船上去救自己。 我在那里等你, 海伦。 ";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DevushkaSnovaOfficer3");
		break;
	}
}
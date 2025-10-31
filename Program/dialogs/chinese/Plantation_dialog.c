// 种植园居民对话
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp, i, n;
	string sTemp;
	bool bOk;
	
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
			dialog.text = "你需要什么吗? ";
			link.l1 = "不, 不需要。 ";
			link.l1.go = "exit";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		// 奴隶
		case "plantation_slave":
			dialog.text = RandPhraseSimple(RandPhraseSimple("我太累了, 已经快要撑不住了... ", "不能再这样活下去了! "), RandPhraseSimple("这工作简直要了我的命。 ", "守卫想把我们都逼死! "));				
			link.l1 = RandPhraseSimple("真遗憾。 ", "我很抱歉。 ");
			link.l1.go = "exit";				
		break;
		
		// 海盗线的奴隶
		case "pirate_slave":
			dialog.text = RandPhraseSimple(RandPhraseSimple("听着, 走开! ", "滚出去! "), RandPhraseSimple("你想干什么? ! ", "快滚蛋! "));				
			link.l1 = RandPhraseSimple("嗯... ", "好吧... ");
			link.l1.go = "exit";				
		break;
		
		// 守卫 - 士兵
		case "plantation_soldier":
			dialog.text = RandPhraseSimple(RandPhraseSimple("去找种植园主麻烦吧", "别打扰奴隶, 伙计。 "), RandPhraseSimple("我的工作就是督促这些懒鬼。 ", "该死, 今天还是一样热... "));
			link.l1 = RandPhraseSimple("我知道了... ", "确实... ");
			link.l1.go = "exit";
		break;
		
		// 守卫 - 护卫
		case "plantation_protector":
            if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
				if (sti(pchar.nation) == PIRATE)
				{
					PlaySound("Voice\English\soldier_arest_1.wav");
					dialog.text = RandPhraseSimple("海盗? ! 抓住他! ", "他是海盗! 攻击! ");
					link.l1 = RandPhraseSimple("海盗又怎样? ", "哈, 有本事就来抓我。 ");
					link.l1.go = "fight"; 
					break;
				}
				PlaySound("Voice\English\soldier_arest_2.wav");
				dialog.text = RandPhraseSimple("哈哈, 你挂着" + NationNameGenitive(sti(pchar.nation)) + "的旗帜! 我想我们的指挥官会很乐意和你聊聊! ", "嗯哼, 这里都能闻到" + NationNameAblative(sti(pchar.nation)) + "的味道! 间谍? ! 该让你和我们的指挥官谈谈了。 ");
				link.l1 = RandPhraseSimple("先尝尝我剑的厉害! ", "让你见识下我的刀锋! ");
				link.l1.go = "fight"; 
			}
			else
			{
				if (GetNationRelation(sti(NPChar.nation), GetBaseHeroNation()) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
				{
					if (sti(pchar.nation) == PIRATE)
					{
						PlaySound("Voice\English\soldier_arest_1.wav");
						dialog.text = RandPhraseSimple("海盗? ! 抓住他! ", "他是海盗! 攻击! ");
						link.l1 = RandPhraseSimple("海盗? 在哪? ", "哈, 放马过来。 ");
						link.l1.go = "fight"; 
						break;
					}
					PlaySound("Voice\English\soldier_arest_4.wav");
					dialog.text = RandPhraseSimple("你是谁? 来这里做什么? ", "站住! 你在这里有什么目的? ");
					if (CheckNationLicence(HOLLAND))
					{
						link.l1 = "我想见见这里的负责人谈生意, 我有贸易许可证。 ";
						link.l1.go = "Licence";
					}
					else
					{
						link.l1 = "我想见见这里的负责人谈生意。 ";
						if (GetSummonSkillFromName(pchar, SKILL_SNEAK) < (10 + rand(50) + rand(50))) link.l1.go = "PegYou";
						else link.l1.go = "NotPegYou";
					}
					if (IsCharacterPerkOn(pchar, "Trustworthy"))
					{
						link.l2 = "(值得信赖)尊敬的先生们, 我来此是为了公平互利的贸易, 请允许我见种植园主。 ";
						link.l2.go = "mtraxx_soldier_1";
						Notification_Perk(true, "Trustworthy");
					}
				}
				else
				{
					PlaySound("Voice\English\soldier_arest_4.wav");
					dialog.text = RandPhraseSimple("你是谁? 来这里做什么? ", "站住! 你在这里有什么目的? ");
					link.l1 = "我想见见这里的负责人谈生意。 ";
					link.l1.go = "NotPegYou";
				}
			}
		break;
		
		case "Licence":
			iTemp = GetDaysContinueNationLicence(HOLLAND);
			if (ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -12)
			{
				PlaySound("Voice\English\soldier_arest_2.wav");
				dialog.text = "许可证? 等一下... 哈哈, 真有趣! 我知道你是谁。 你是通缉犯, 伙计! 你的悬赏金很高! 抓住他! ";
				link.l1 = RandPhraseSimple("既然这样, 你就尝尝我的剑吧! ", "去你的。 ");
				link.l1.go = "fight";	
				break;
			}
			if (iTemp == -1)
			{
				PlaySound("Voice\English\soldier_arest_1.wav");
				dialog.text = "让我看看... 哈! 你的许可证过期了。 所以跟我来, 我带你去见指挥官... ";
				link.l1 = RandPhraseSimple("该死! 我想是时候让你见识一下我的剑了, 伙计。 ", "我可不这么想... ");
				link.l1.go = "fight";	
				TakeNationLicence(HOLLAND);
				break;
			}
			dialog.text = "好吧。 你可以进来。 规矩点, 别打扰奴隶。 ";
			link.l1 = "别担心, 朋友。 ";
			link.l1.go = "plantation_exit";
		break;
		
		case "PegYou":
			PlaySound("Voice\English\soldier_arest_2.wav");
			dialog.text = "生意? 哈哈! 好吧, 真有趣! 你身上千里之外都能闻到" + NationNameAblative(sti(GetBaseHeroNation())) + "的味道! 是时候让你见见我们的指挥官了。 ";
			link.l1 = "不, 我想是时候让你见识一下我的剑了。 ";
			link.l1.go = "fight";
		break;
		
		case "NotPegYou":
			dialog.text = "好吧。 你可以进来。 规矩点, 别打扰奴隶。 ";
			link.l1 = "别担心, 朋友。 ";
			link.l1.go = "plantation_exit";
		break;
		
		case "plantation_exit":
			DialogExit();
			NextDiag.CurrentNode = "plantation_repeat";
		break;
		
		case "plantation_repeat":
			dialog.text = "快点, 走开! ";
			link.l1 = "... ";
			link.l1.go = "plantation_exit";
		break;
		
		// 马拉开波的管理者 // Addon 2016-1 Jason
		case "Plantator":
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "plant_2") // belamour legendary edition 
			{
				dialog.text = "有什么事吗, 先生? ";
				link.l1 = TimeGreeting() + ",先生。 我有个生意想和你谈谈。 我有奴隶要卖。 " + FindRussianQtyString(sti(GetSquadronGoods(pchar, GOOD_SLAVES))) + "。 有兴趣吗? ";
				link.l1.go = "mtraxx";
				break;
			}
			dialog.text = "有什么事吗, 先生? ";
			link.l1 = "只是随便走走, 想打个招呼。 ";
			link.l1.go = "plantator_x";
		break;
		
		case "plantator_x":
           DialogExit();
		   npchar.dialog.currentnode = "plantator";
		break;
		
		case "plantator_1":
			bOk = GetSquadronGoods(pchar, GOOD_COFFEE) >= 500 || GetSquadronGoods(pchar, GOOD_CINNAMON) >= 500 || GetSquadronGoods(pchar, GOOD_COPRA) >= 500;
			if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup") && bOk) // 尝试赎回帅哥
			{
				dialog.text = "又是你, 先生。 你好吗? ";
				link.l1 = "我有个生意想和你谈谈。 你生产糖和可可。 我想买你的货物, 但不是用钱, 我可以用我自己的货物交换。 也许我们可以做个交易? ";
				link.l1.go = "mtraxx_5";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "plant_6" && bOk)
			{
				dialog.text = "又是你, 先生。 你好吗? ";
				link.l1 = "我有个生意想和你谈谈。 你生产糖和可可。 我想买你的货物, 但不是用钱, 我可以用我自己的货物交换。 也许我们可以做个交易? ";
				link.l1.go = "mtraxx_5";
				break;
			}
			dialog.text = "又是你, 先生。 你好吗? ";
			link.l1 = "谢谢, 我很好。 ";
			link.l1.go = "plantator_1x";
		break;
		
		case "plantator_1x":
           DialogExit();
		   npchar.dialog.currentnode = "plantator_1";
		break;
		
		case "mtraxx":
			// belamour legendary edition 欺骗种植园主的可能性 -->
			if (GetSquadronGoods(pchar, GOOD_SLAVES) >= 50 || CheckCharacterPerk(pchar, "Trustworthy") || ChangeCharacterHunterScore(Pchar, "spahunter", 0) <= -50)
			{
				dialog.text = "我必须让你失望了, 先生, 我们目前不需要奴隶。 埃杜阿尔多.德.洛萨达船长在最近的一次袭击中捕获的海盗已经供应给我们了。 ";
				link.l1 = "海盗在这里? 你怎么能在这里睡得着? ";
				link.l1.go = "mtraxx_1";
			}
			else
			{
				dialog.text = "啊, 让我看看... 我会买你的奴隶。 只是我觉得你不是你说的那个人。 跟我去指挥官办公室吧, 亲爱的, 如果我错了, 我会全额赔偿你的精神损失。 现在请原谅我。 卫兵! ";
				link.l1 = RandPhraseSimple("做梦吧, 我不会活着投降的!', '除非我死了! ");
				link.l1.go = "mtraxx_fail";
			}
		break;
		
		case "mtraxx_fail":
            DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddQuestRecord("Roger_3", "27");
			sld = characterFromId("Mtr_plantation_boss");
			sld.lifeday = 0;
			Mtraxx_PlantPellyClear();
			Mtraxx_TerraxReset(3);
		break;
		// < —传奇版
		case "mtraxx_1":
			DelMapQuestMarkCity("baster");
			DelLandQuestMark(characterFromId("Fadey"));
			dialog.text = "我们有很好的守卫, 所以暴动的可能性很低。 但你在某种程度上是对的: 这些混蛋是可怕的工人。 如果总督没有要求我尊重德.洛萨达先生, 我是不会买他们的。 另外, 他要的价钱也不高。 ";
			link.l1 = "我明白了。 我得去洛斯-特克斯了... 先生, 我可以在你的种植园里走走, 看看吗? 也许我想买些你的产品... ";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
			dialog.text = "你是商人吗? ";
			link.l1 = "在某种程度上, 是的。 我不是专业的商人, 但我从不拒绝有前途的交易。 ";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
			dialog.text = "有趣。 很好, 我允许你。 如果你有任何想法, 回来告诉我。 ";
			link.l1 = "谢谢你, 先生。 我相信我会的。 ";
			link.l1.go = "mtraxx_4";
		break;
		
		case "mtraxx_4":
           DialogExit();
		   NextDiag.CurrentNode = "plantator_1";
		   pchar.questTemp.Mtraxx = "plant_3";
		   AddQuestRecord("Roger_3", "5");
		   Mtraxx_PlantSetMaxRocur();
		break;
		
		case "mtraxx_5":
			dialog.text = "为什么不呢? 你提供什么货物? ";
			if (GetSquadronGoods(pchar, GOOD_COFFEE) >= 500)
			{
				link.l1 = "500箱咖啡。 ";
				link.l1.go = "mtraxx_coffee";
			}
			if (GetSquadronGoods(pchar, GOOD_CINNAMON) >= 500)
			{
				link.l2 = "500箱香草。 ";
				link.l2.go = "mtraxx_cinnamon";
			}
			if (GetSquadronGoods(pchar, GOOD_COPRA) >= 500)
			{
				link.l3 = "500箱椰子干。 ";
				link.l3.go = "mtraxx_copra";
			}
		break;
		
		case "mtraxx_coffee":
			i = hrand(3) + 1;
			n = 5 - i;
			pchar.questTemp.Mtraxx.PlantGood.Cargo = 11;
			pchar.questTemp.Mtraxx.PlantGood.Sugar = i * 100;
			pchar.questTemp.Mtraxx.PlantGood.Cocoa = n * 100;
			dialog.text = "五百箱咖啡? 嗯... 让我看看... (计算)我准备用" + sti(pchar.questTemp.Mtraxx.PlantGood.Sugar) + "袋糖和" + sti(pchar.questTemp.Mtraxx.PlantGood.Cocoa) + "箱可可交换你的咖啡。 成交吗? ";
			link.l1 = "嗯... 我原本希望条件更好些。 好吧, 谁在乎呢。 成交! ";
			link.l1.go = "mtraxx_6";
			if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup"))
			{
				link.l1 = "(值得信赖)尊敬的先生, 请允许我提出异议! 我给你带来了最高质量的商品。 我知道我提供的每一件商品的价值, 也知道你提供的每一件商品的价值。 我应该从你这边得到更多的货物, 而且这笔交易对你来说仍然是有利可图的 —你很清楚这一点。 ";
				link.l1.go = "mtraxx_PlantVykup_2";
				Notification_Perk(true, "Trustworthy");
			}
		break;
		
		case "mtraxx_cinnamon":
			i = hrand(3) + 1;
			n = 5 - i;
			pchar.questTemp.Mtraxx.PlantGood.Cargo = 19;
			pchar.questTemp.Mtraxx.PlantGood.Sugar = i * 106;
			pchar.questTemp.Mtraxx.PlantGood.Cocoa = n * 106;
			dialog.text = "五百箱香草? 嗯... 让我看看... (计算)我准备用" + sti(pchar.questTemp.Mtraxx.PlantGood.Sugar) + "袋糖和" + sti(pchar.questTemp.Mtraxx.PlantGood.Cocoa) + "箱可可交换你的香草。 成交吗? ";
			link.l1 = "嗯... 我原本希望条件更好些。 好吧, 谁在乎呢。 成交! ";
			link.l1.go = "mtraxx_6";
			if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup"))
			{
				link.l1 = "(值得信赖)尊敬的先生, 请允许我提出异议! 我给你带来了最高质量的商品。 我知道我提供的每一件商品的价值, 也知道你提供的每一件商品的价值。 我应该从你这边得到更多的货物, 而且这笔交易对你来说仍然是有利可图的 —你很清楚这一点。 ";
				link.l1.go = "mtraxx_PlantVykup_2";
				Notification_Perk(true, "Trustworthy");
			}
		break;
		
		case "mtraxx_copra":
			i = hrand(3) + 1;
			n = 5 - i;
			pchar.questTemp.Mtraxx.PlantGood.Cargo = 20;
			pchar.questTemp.Mtraxx.PlantGood.Sugar = i * 100;
			pchar.questTemp.Mtraxx.PlantGood.Cocoa = n * 100;
			dialog.text = "五百箱椰子干? 嗯... 让我看看... (计算)我准备用" + sti(pchar.questTemp.Mtraxx.PlantGood.Sugar) + "袋糖和" + sti(pchar.questTemp.Mtraxx.PlantGood.Cocoa) + "箱可可交换你的椰子干。 成交吗? ";
			link.l1 = "嗯... 我原本希望条件更好些... 好吧, 谁在乎呢。 成交! ";
			link.l1.go = "mtraxx_6";
			if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup"))
			{
				link.l1 = "(值得信赖)尊敬的先生, 请允许我提出异议! 我给你带来了最高质量的商品。 我知道我提供的每一件商品的价值, 也知道你提供的每一件商品的价值。 我应该从你这边得到更多的货物, 而且这笔交易对你来说仍然是有利可图的 —你很清楚这一点。 ";
				link.l1.go = "mtraxx_PlantVykup_2";
				Notification_Perk(true, "Trustworthy");
			}
		break;
		
		case "mtraxx_6":
			dialog.text = "太好了! 这对我们双方都是有利可图的交易! 我们什么时候进行交换? ";
			link.l1 = "我应该先准备好货物。 我相信你也一样。 我们明天晚上四点开始交换吧。 我的人会在日落前把箱子送来。 ";
			link.l1.go = "mtraxx_7";
		break;
		
		
		case "mtraxx_7":
			dialog.text = "成交。 那么, 明天见, 先生! ";
			link.l1 = "再见... ";
			link.l1.go = "mtraxx_8";
		break;
		
		case "mtraxx_8":
            DialogExit();
			NextDiag.CurrentNode = "plantator_1";
			AddQuestRecord("Roger_3", "10");
			pchar.questTemp.Mtraxx = "plant_7";
			pchar.GenQuest.CannotWait = true;// 禁止等待
			pchar.quest.mtraxx_plant_goods.win_condition.l1 = "ExitFromLocation";
			pchar.quest.mtraxx_plant_goods.win_condition.l1.location = pchar.location;
			pchar.quest.mtraxx_plant_goods.function = "Mtraxx_PlantFindRocurDay";
		break;
		
		case "mtraxx_9":
			dialog.text = "就是这样, 先生。 如果你以后需要糖或可可, 请随时来找我。 随时欢迎! ";
			link.l1 = "如果这笔交易证明是有利可图的 —我们会再见面的。 我现在该走了, 先生。 ";
			link.l1.go = "mtraxx_10";
		break;
		
		case "mtraxx_10":
			dialog.text = "再见, 先生! ";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantAfterTrading");
		break;
		
		case "mtraxx_soldier_1":
			dialog.text = "你看起来不像个商人, 外国人。 出示你的许可证。 ";
			link.l1 = "饶了我吧! 一张纸就能决定一个人能不能做生意吗? 它们太贵了! 我最近才开始做生意, 但这已经成了我的爱好! 让我过去, 我一定会在种植园主面前替你俩美言几句。 ";
			link.l1.go = "mtraxx_10";
		break;
		
		case "mtraxx_soldier_2":
			dialog.text = "你口才真好, 你这个吝啬鬼。 好吧, 去吧。 但别忘了告诉老板是我们推荐你来的。 ";
			link.l1 = "当然。 谢谢。 ";
			link.l1.go = "plantation_exit";
		break;
		
		case "mtraxx_PlantVykup_2":
			dialog.text = "你对当前的价格很了解, 船长! 你显然很有谈判技巧, 即使你看起来像个新手。 好吧, 如果你的货物真的是一流的, 我想我应该给你多加点。 ";
			link.l1 = "当然是一流的, 我发誓! 还有一件事, 先生。 我想从你这里买些东西。 ";
			link.l1.go = "mtraxx_PlantVykup_3";
		break;
		
		case "mtraxx_PlantVykup_3":
			dialog.text = "哦? 买什么? ";
			link.l1 = "一个人, 不是东西。 我想买你的一个奴隶当私人仆人。 可以吗? ";
			link.l1.go = "mtraxx_PlantVykup_4";
		break;
		
		case "mtraxx_PlantVykup_4":
			dialog.text = "没问题。 我们会给你找个合适的。 ";
			link.l1 = "我对一个特定的奴隶感兴趣。 那个面容迷人的 —一个你不会羞于带到正式场合或让他为客人斟酒的人。 他自我介绍说叫让.皮卡德。 我们已经很投缘了。 ";
			link.l1.go = "mtraxx_PlantVykup_5";
		break;
		
		case "mtraxx_PlantVykup_5":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 70)
			{
				dialog.text = "是的, 让.皮卡德很抢手 —不只是为了斟酒。 一位有影响力的英国人已经联系过我。 一个叫... 帕托姆森的人? 他给我送了封信。 ";
				link.l1 = "但帕托姆森和他的客户都还没出现。 我准备现在就从你这里买下让。 开个价吧 —女士们还在等着呢! ";
				link.l1.go = "mtraxx_PlantVykup_10";
				Notification_Skill(true, 60, SKILL_COMMERCE);
			}
			else
			{
				dialog.text = "啊, 投缘。 我明白。 但恐怕我必须拒绝 —让.皮卡德不出售。 对不起, 先生。 ";
				link.l1 = "哦? 为什么? 我愿意出高价。 开个价吧。 ";
				link.l1.go = "mtraxx_PlantVykup_6";
				notification("Skill Check Failed (70)", SKILL_COMMERCE);
			}
		break;
		
		case "mtraxx_PlantVykup_6":
			dialog.text = "无价之宝。 他已经有买家了。 我已经答应把他卖给别人了。 没什么好说的了。 让我们回到最初的交易, 完成贸易吧。 ";
			link.l1 = "嗯, 随你便, 先生。 ";
			link.l1.go = "mtraxx_PlantVykup_7";
		break;
		
		case "mtraxx_PlantVykup_7":
			dialog.text = "太好了! 这对我们双方都是有利可图的交易! 我们什么时候进行交换? ";
			link.l1 = "我应该先准备好货物。 我相信你也一样。 我们明天晚上四点开始交换吧。 我的人会在日落前把箱子送来。 ";
			link.l1.go = "mtraxx_PlantVykup_8";
		break;
		
		
		case "mtraxx_PlantVykup_8":
			dialog.text = "成交。 那么, 明天见, 先生! ";
			link.l1 = "再见... ";
			link.l1.go = "mtraxx_PlantVykup_9";
		break;
		
		case "mtraxx_PlantVykup_9":
            DialogExit();
			NextDiag.CurrentNode = "plantator_1";
			pchar.questTemp.mtraxx_PlantVykup2 = true;
			DeleteAttribute(pchar, "questTemp.mtraxx_PlantVykup");
			DoFunctionReloadToLocation("Shore37", "goto", "goto6", "Mtraxx_PlantPlantVykup_1");
		break;
		
		case "mtraxx_PlantVykup_10":
			dialog.text = "如你所愿, 先生。 但要明白, 价格不菲: 五百枚杜布隆。 ";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "没问题 —给你。 一个好的私人仆人比普通奴隶更值钱, 你很清楚这一点。 ";
				link.l1.go = "mtraxx_PlantVykup_11";
			}
			else
			{
				link.l2 = "你开的价可不低, 先生。 但我对这个奴隶很感兴趣。 等我一下。 如果帕托姆森来了, 告诉他皮卡德已经卖了 —哈哈! ";
				link.l2.go = "mtraxx_PlantVykup_13";
			}
		break;
		
		case "mtraxx_PlantVykup_11":
			dialog.text = "你说得对。 我会安排好的。 皮卡德会在外面等你。 ";
			link.l1 = "... ";
			link.l1.go = "mtraxx_PlantVykup_12";
			RemoveDublonsFromPCharTotal(500);
		break;
		
		case "mtraxx_PlantVykup_12":
            DialogExit();
			NextDiag.CurrentNode = "plantator_1";
			pchar.questTemp.mtraxx_PlantVykup3 = true;
			DeleteAttribute(pchar, "questTemp.mtraxx_PlantVykup");
			DoFunctionReloadToLocation("Maracaibo_ExitTown", "rld", "loc17", "Mtraxx_PlantPlantVykup_2");
		break;
		
		case "mtraxx_PlantVykup_13":
			dialog.text = "如果他带着全款来, 我怀疑我不会拒绝他。 所以快点, 船长。 ";
			link.l1 = "我很快就回来。 ";
			link.l1.go = "mtraxx_PlantVykup_14";
		break;
		
		case "mtraxx_PlantVykup_14":
            DialogExit();
			NextDiag.CurrentNode = "mtraxx_PlantVykup_15";
			DeleteAttribute(pchar, "questTemp.mtraxx_PlantVykup");
		break;
		
		case "mtraxx_PlantVykup_15":
			dialog.text = "你把让.皮卡德的金子带来了吗, 船长? 时间紧迫。 ";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "我很清楚。 所以给你, 拿着你的金子, 把我的新家庭仆人给我。 ";
				link.l1.go = "mtraxx_PlantVykup_16";
			}
			else
			{
				link.l2 = "还在筹集 —是你定了这么高的价格, 先生。 ";
				link.l2.go = "mtraxx_PlantVykup_14";
			}
		break;
		
		case "mtraxx_PlantVykup_16":
			dialog.text = "我从未见过有人花这么多钱买一个仆人。 但从你穿着这么讲究来看, 你一定习惯了这种大手笔的购买。 我会通知我的人, 皮卡德会在出口等你。 ";
			link.l1 = "... ";
			link.l1.go = "mtraxx_PlantVykup_12";
			RemoveDublonsFromPCharTotal(500);
		break;
	}
}
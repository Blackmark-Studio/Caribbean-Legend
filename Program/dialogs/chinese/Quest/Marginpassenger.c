void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "发现一个漏洞。 务必告知开发者。 ";
			link.l1 = "好的";
			link.l1.go = "exit";
		break;
		
		//甲板上的对话
		case "MarginCap":
			dialog.text = "你好, 船长。 你想从我这里得到什么? ";
			link.l1 = "是的, 正是如此, " + GetAddress_FormToNPC(NPChar) + "。 你的船上有一位乘客让我很感兴趣。 他/她的名字是" + pchar.GenQuest.Marginpassenger.q1Name + "。 我希望你的乘客成为我的乘客。 如果你同意, 我们就分道扬镳, 再也不见。 ";
			link.l1.go = "MarginCap_1";
		break;
	
		case "MarginCap_1":
			dialog.text = "是这样吗? 如果我说不呢? ";
			link.l1 = "那我就不得不让你重新考虑你的决定了 —用我的几轮炮火, 它们此刻正瞄准着你的方向。 别挑战你的运气, " + GetAddress_FormToNPC(NPChar) + "。 ";
			link.l1.go = "MarginCap_2";
		break;
		
		case "MarginCap_2":
			int MCparam = (7-sti(RealShips[sti(pchar.ship.type)].Class))*100+sti(pchar.ship.Crew.Morale)+sti(pchar.Ship.Crew.Exp.Sailors)+sti(pchar.Ship.Crew.Exp.Cannoners)+sti(pchar.Ship.Crew.Exp.Soldiers);
			int NPCparam = (7-sti(RealShips[sti(npchar.ship.type)].Class))*100+sti(npchar.ship.Crew.Morale)+sti(npchar.Ship.Crew.Exp.Sailors)+sti(npchar.Ship.Crew.Exp.Cannoners)+sti(npchar.Ship.Crew.Exp.Soldiers);
			if (MCparam > NPCparam)//主动交出
			{
				dialog.text = "那我别无选择。 对我来说, 船员的命运比一个人的命运更有价值。 但你不会就这么算了的! 我不会忘记的! ";
				link.l1 = "冷静点, 别让自己心脏病发作... 把我的新乘客带来! ";
				link.l1.go = "MarginCap_3";
			}
			else
			{
				dialog.text = "你最好离开我的船, 先生, 趁我还允许你这么做。 别想吓唬我。 你敢攻击我的船, 就会立刻被击退。 趁我现在心情好, 滚出去! ";
				link.l1 = "我警告过你了。 我这就走。 回头见, " + GetAddress_FormToNPC(NPChar) + "! ";
				link.l1.go = "MarginCap_4";
			}
		break;
	
		case "MarginCap_3":
			DialogExit();
			npchar.Dialog.CurrentNode = "MarginCap_repeat";
			//移交乘客
			sld = GetCharacter(NPC_GenerateCharacter("MarginPass", pchar.GenQuest.Marginpassenger.model, pchar.GenQuest.Marginpassenger.sex, pchar.GenQuest.Marginpassenger.ani, 2, sti(pchar.GenQuest.Marginpassenger.Nation), -1, true, "quest"));
			sld.Dialog.Filename = "Quest\Marginpassenger.c";
			sld.Dialog.currentnode = "MarginPass";
			sld.name = pchar.GenQuest.Marginpassenger.q1Name;
			sld.lastname = "";
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			Map_ReleaseQuestEncounter(npchar.id);
			npchar.Abordage.Enable = false; // 禁止登船
			npchar.ShipEnemyDisable = true;
			npchar.AlwaysFriend = true;
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), -1);
		break;
		
		case "MarginCap_4":
			DialogExit();
			NextDiag.CurrentNode = "MarginCap_repeat";
			pchar.GenQuest.Marginpassenger.Mustboarding = "true";
			AddQuestRecord("Marginpassenger", "5");
			AddQuestUserData("Marginpassenger", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name")+"Acc")));
			AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), -1);
		break;
		
		case "MarginCap_repeat":
			dialog.text = "我们已经谈过了, 记得吗? 离我的船远点! ";
			link.l1 = "... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "MarginCap_repeat";
		break;
		
		case "MarginCap_abordage":
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger.Mustboarding"))
			{
				dialog.text = "啊, 混蛋! 为你的行为下地狱吧! ";
				link.l1 = "我曾提议你和平地把乘客交给我... 而你拒绝了我的提议。 现在你只能怪自己! ";
				link.l1.go = "MarginCap_abordage_1";
			}
			else
			{
				dialog.text = "啊, 混蛋! 你为什么攻击这艘和平的船? 很多人都死了! 海盗! ";
				link.l1 = "但你船上有一个有价值的人... " + pchar.GenQuest.Marginpassenger.q1Name + "。 我要你的乘客。 ";
				link.l1.go = "MarginCap_abordage_2";
			}
		break;
		
		case "MarginCap_abordage_1":
			dialog.text = "你... 是肮脏的海盗! ";
			link.l1 = "少说废话, 我的朋友... ";
			link.l1.go = "MarginCap_abordage_3";
		break;
		
		case "MarginCap_abordage_2":
			dialog.text = "这就是你在我船上屠杀的原因? 很多人都死了! 海盗! ";
			link.l1 = "少说废话, 我的朋友... ";
			link.l1.go = "MarginCap_abordage_3";
		break;
		
		case "MarginCap_abordage_3":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "Marginpassenger_GivePrisoner");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "MarginNeed":
			dialog.text = "你想要什么, " + GetAddress_Form(NPChar) + "? ";
			link.l1 = "你是" + pchar.GenQuest.Marginpassenger.q2Name + "吗? ";
			link.l1.go = "MarginNeed_1";
		break;
		
		case "MarginNeed_1":
			dialog.text = "是的, 是我。 你想提交申请吗? 那你应该知道... ";
			link.l1 = "等一下, 先生。 我有一个稍微不同的申请... 你认识一个叫" + pchar.GenQuest.Marginpassenger.q1Name + "的人吗? ";
			link.l1.go = "MarginNeed_2";
		break;
		
		case "MarginNeed_2":
			switch (pchar.GenQuest.Marginpassenger.sex)
			{
				case "woman":
					dialog.text = "是的, 我认识她... 当然认识! 怎么了? ";
					link.l1 = "她卷入了一个非常不愉快的事件: 她的船被海盗俘虏了。 幸运的是, 我有机会登上他们的船, 救了这个可怜的人。 她告诉了我你的名字, 于是我就来了。 ";
					link.l1.go = "MarginNeed_woman";
				break;
				case "man":
					dialog.text = "是的, 我非常了解这个人。 怎么了? ";
					link.l1 = "他卷入了一个非常不愉快的事件: 他的船被海盗俘虏了。 幸运的是, 我有机会登上他们的船, 救了这个囚徒。 他告诉了我你的名字, 于是我就来了。 ";
					link.l1.go = "MarginNeed_man";
				break;
			}
		break;
		
		case "MarginNeed_woman":
			dialog.text = "哦, 天哪! 她现在在哪里? 你为什么不带她来这里? ";
			link.l1 = "她很安全。 关于你的问题... 没那么简单。 我本可以自己把她带回家, 但我可以把这个机会让给你。 当然, 需要一笔 modest 的费用。 ";
			link.l1.go = "MarginNeed_woman_1";
		break;
		
		case "MarginNeed_woman_1":
			dialog.text = "嗯... 我不明白... ";
			link.l1 = "你为什么不明白? 你给我金子, 我把女孩给你, 你可以利用这个情况来满足你的利益... 你想娶她, 对吗? 我会用这些硬币修理我的船, 在与海盗的战斗中它受损了。 ";
			link.l1.go = "MarginNeed_money";
		break;
		
		case "MarginNeed_man":
			dialog.text = "哦, 天哪! 他现在在哪里? 你为什么不带他来这里? ";
			link.l1 = "他很安全。 关于你的问题... 没那么简单。 我本可以自己把他带回家, 但我可以把这个机会让给你, 考虑到你在他的家族中有自己的利益。 当然, 需要一笔 modest 的费用。 ";
			link.l1.go = "MarginNeed_man_1";
		break;
		
		case "MarginNeed_man_1":
			dialog.text = "嗯... 我不明白... ";
			link.l1 = "你为什么不明白? 你给我金子, 我把你的朋友给你, 你可以利用这个情况来满足你的利益。 你知道, 我有一些信息... 我会用这些硬币修理我的船, 在与海盗的战斗中它受损了。 ";
			link.l1.go = "MarginNeed_money";
		break;
		
		case "MarginNeed_money":
			dialog.text = "好吧, 好吧... 你想要多少? ";
			link.l1 = "记住我要的是达布隆, 不是比索。 ";
			link.l1.go = "MarginNeed_money_1";
		break;
		
		case "MarginNeed_money_1":
			dialog.text = "好的, 好的... 那么你想要多少达布隆? ";
			Link.l1.edit = 1;			
			link.l1 = "";
			link.l1.go = "MarginNeed_money_2";
		break;
		
		case "MarginNeed_money_2":
		iTemp = sti(dialogEditStrings[1]);
		int iSum = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*5*stf(pchar.GenQuest.Marginpassenger.Chance));
		if (iTemp <= 0)
		{
			dialog.text = "真有趣。 好吧, 我们就当你的笑话很有趣。 再见! ";
			link.l1 = "嗯... ";
			link.l1.go = "MarginNeed_exit";
			break;
		}
		if (iTemp > 0 && iTemp <= iSum)
		{
			if (hrand(2) > 1) // Addon-2016 Jason 减少达布隆发放
			{
				dialog.text = "好的, 我同意。 我有所需的金额。 " + pchar.GenQuest.Marginpassenger.q1Name + "在哪里? ";
				link.l1 = "现在应该在码头了。 所以你可以去接乘客了。 ";
				link.l1.go = "MarginNeed_dublon";
			}
			else
			{
				dialog.text = "对不起, 我没有那么多达布隆。 比索可以吗? ";
				link.l1 = "我想要达布隆, 但我想船长会接受比索... 给我吧。 ";
				link.l1.go = "MarginNeed_peso";
				link.l2 = "不, 我只需要达布隆。 ";
				link.l2.go = "MarginNeed_dublon_exit";
			}
			break;
		}
		if (iTemp > iSum && iTemp < 1000)
		{
			dialog.text = "不幸的是, 我没有这么多钱。 所以即使我很想接受你的提议, 也做不到。 ";
			link.l1 = "嗯... ";
			link.l1.go = "MarginNeed_exit";
			break;
		}
		if (iTemp > 1000 && iTemp < 3000)
		{
			dialog.text = "先生, 你知道你在说什么吗? 你意识到这个金额太大了吗? 滚出这里! ";
			link.l1 = "嗯... ";
			link.l1.go = "MarginNeed_exit";
			break;
		}
			dialog.text = "好吧... 先生, 你必须马上去看医生。 看起来你发高烧了, 或者... 不管怎样, 你需要医生。 我太忙了。 再见! ";
			link.l1 = "嗯... ";
			link.l1.go = "MarginNeed_exit";
		break;
		
		case "MarginNeed_dublon":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			iTemp = sti(dialogEditStrings[1]);
			TakeNItems(pchar, "gold_dublon", iTemp);
			AddQuestRecord("Marginpassenger", "9");
			AddQuestUserData("Marginpassenger", "sSum", iTemp);
			CloseQuestHeader("Marginpassenger");
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
			AddCharacterExpToSkill(pchar, "Fortune", 100);//运气
		break;
		
		case "MarginNeed_peso":
			dialog.text = "给你, 这是你想要的全部比索... " + pchar.GenQuest.Marginpassenger.q1Name + "在哪里? ";
			link.l1 = "现在应该在码头了。 所以你可以去接乘客了。 ";
			link.l1.go = "MarginNeed_peso_1";
		break;
		
		case "MarginNeed_peso_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			iTemp = sti(dialogEditStrings[1])*500;
			AddMoneyToCharacter(pchar, iTemp);
			AddQuestRecord("Marginpassenger", "10");
			AddQuestUserData("Marginpassenger", "sSum", FindRussianMoneyString(iTemp));
			CloseQuestHeader("Marginpassenger");
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
			AddCharacterExpToSkill(pchar, "Fortune", 80);//运气
		break;
		
		case "MarginNeed_dublon_exit":
			dialog.text = "那么, 即使我很想接受你的提议, 也做不到。 再见! ";
			link.l1 = "嗯... ";
			link.l1.go = "MarginNeed_exit";
		break;
		
		case "MarginNeed_exit":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Marginpassenger", "11");
			AddQuestUserData("Marginpassenger", "sName2", pchar.GenQuest.Marginpassenger.q2Name);
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City));
			// belamour gen: 好人时日无多 -->
			if(CheckAttribute(pchar, "questTemp.LongHappy"))
			{
				AddQuestUserData("Marginpassenger", "sBaron", "到普林西比港, 找黑牧师");
			}
			else
			{
				AddQuestUserData("Marginpassenger", "sBaron", "到勒弗朗索瓦, 找好心的雅克");
			}
			// < —belamour gen
			pchar.GenQuest.Marginpassenger = "cabin";
		break;
		
		case "MarginPass":
			dialog.text = "这是... 怎么回事? ! ";
			link.l1 = "很简单, " + NPCharSexPhrase(NPChar, "伙计", "姑娘") + "。 你现在是我亲爱的乘客了。 一位受保护的乘客。 别试图反抗, 否则你会被关进货舱。 ";
			link.l1.go = "MarginPass_1";
		break;
		
		case "MarginPass_1":
			dialog.text = "你是说我是你的囚徒? ";
			link.l1 = "哦, 不。 当然不是。 不是囚徒, 而是亲爱的客人。 一位非常有价值的客人... ";
			link.l1.go = "MarginPass_2";
		break;
		
		case "MarginPass_2":
			dialog.text = "你... 你会为你的行为付出代价的! ";
			link.l1 = "你又错了, " + NPCharSexPhrase(NPChar, "伙计", "亲爱的") + "。 我不会付出代价, 但我会得到报酬。 别再说了, 去你的船舱! ";
			link.l1.go = "MarginPass_3";
		break;
		
		case "MarginPass_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "", "", "none", "", "", "", 1.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.quest.Marginpassenger_InWorldOver.over = "yes"; //移除中断
			pchar.quest.Marginpassenger_Sink.over = "yes"; //移除中断
			pchar.GenQuest.Marginpassenger = "take";
			if (rand(2) == 1) pchar.GenQuest.Marginpassenger.lose = "true";
			else Marginpassenger_CreateNeedman();
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger.Boarding")) AddQuestRecord("Marginpassenger", "6");
			else AddQuestRecord("Marginpassenger", "4");
			AddQuestUserData("Marginpassenger", "sName1", pchar.GenQuest.Marginpassenger.q1Name);
			AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName);
			AddQuestUserData("Marginpassenger", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name")+"Acc")));
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
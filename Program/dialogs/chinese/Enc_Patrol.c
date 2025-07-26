void ProcessDialogEvent()
{
	ref NPChar, sld;
	ref arItem;
	aref Link, Diag;
	int i, iShipType, iShipGoods;
	int jewelType;
	string sItemName = "";
	string sItem;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	int iTemp = sti(npchar.EncQty);
	string sTemp = "Patrol" + locations[FindLocation(npchar.location)].index + "_";
	string sGroup = "PatrolGroup_" + locations[FindLocation(npchar.location)].index;
	string sTemp1, sTemp2;

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;

		case "exit_fight":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, sGroup);
			}
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "LandEnc_PatrolAfrer");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_noFight":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				sld.Dialog.CurrentNode = "GoodBye";
				sld.greeting = "soldier_common";
				LAi_SetWarriorType(sld);
				LAi_warrior_DialogEnable(sld, true);
				LAi_group_MoveCharacter(sld, sGroup);				
			}
			LAi_group_SetCheck(sGroup, "LandEnc_PatrolAfrer");
			DialogExit();			
		break;

		case "First Time":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
			}
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
    			if (pchar.nation == npchar.nation)
				{
					dialog.text = RandPhraseSimple("哦看, 好像这个恶棍在" + XI_ConvertString("Colony" + npchar.city + "Dat") + "拉响了警报! 抓住他" + GetSexPhrase("们","她") + "!! ", "嘿, 看看这个! 几个" + NationNamePeople(sti(pchar.nation)) + "竟然与" + NationNameAblative(sti(npchar.nation)) + "为敌! 抓住这个恶棍!! ");
				}
				else
				{
					dialog.text = RandPhraseSimple("在" + XI_ConvertString("Colony" + npchar.city + "Gen") + "附近有敌方特工! 抓住他" + GetSexPhrase("们","她") + "!! ", "嘿, 看, " + NationNamePeople(sti(pchar.nation)) + "几乎在" + XI_ConvertString("Colony" + npchar.city + "Dat") + "附近走动! 立即抓住他!! ");
				}
				link.l1 = RandPhraseSimple("好吧, 你们可以试试。 这里只有我们... ", "嘿, 没人会在这里帮你们。 ");
				link.l1.go = "exit_fight"; 				
			}
			else
			{				
				// belamour传奇版
				sTemp1 = "";
				if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation)) sTemp1 = "舰队副司令! ";
				if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE) sTemp1 = "总督大人! ";
				
				dialog.text = LinkRandPhrase("请允许我介绍自己! 我是来自" + XI_ConvertString("Colony" + npchar.city + "Gen") + "的巡逻军官, 我们在寻找一名逃犯。 ",
					"你好, 我是这支巡逻队的队长。 我们在寻找一名从" + XI_ConvertString("Colony" + npchar.city + "Gen") + "逃脱的奴隶。 ",
					"向你问好, " + GetAddress_Form(NPChar) + "。 我的分队正在" + XI_ConvertString("Colony" + npchar.city + "Gen") + "附近区域巡逻。 ");
				Link.l1 = LinkRandPhrase("非常好。 我能帮你什么吗? ",
				"非常好。 " + GetAddress_FormToNPC(NPChar) + ", 我能为你做些什么吗? ",
				"非常好。 有什么我可以为你效劳的吗? ");
				Link.l1.go = "Node_2";
			}
		break;
		
		case "Node_2":
			dialog.text = RandPhraseSimple("你在这个地区看到什么可疑的东西了吗? ",
				"你遇到过看起来可疑的人吗, " + GetAddress_Form(NPChar) + "? ");
			Link.l1 = RandPhraseSimple("不, 没有那样的东西。 ", "没有, 军官, 一切看起来都很平静。 ");
			Link.l1.go = "Node_3";		
		break;

		case "Node_3":
			Diag.TempNode = "GoodBye";
			dialog.text = RandPhraseSimple("好吧, 我不再耽误你了。 再见, " + GetAddress_Form(NPChar) + "。 ",
				"我明白了。 那么再见。 ");
			Link.l1 = "祝你好运。 ";
			Link.l1.go = "exit_noFight";
		break;

		case "GoodBye":
			Diag.TempNode = "GoodBye";
			dialog.text = LinkRandPhrase("不要干扰我们执行任务。 ",
				"我希望你别打扰我们! ",
				"哦, 又是你... 走你的路, 别打扰我们。 ");
			Link.l1 = "好的。 ";
			Link.l1.go = "Exit";			
		break;
		
		// 生成器 "匆忙的理由"
		case "Reason_To_Fast_1":
				if(Pchar.Location == Pchar.location.from_sea)
				{
					dialog.text = "嗯... 我以前没见过你。 你是谁? ";
					link.l1 = "我就是你们在等的人... ";
					link.l1.go = "Reason_To_Fast_11";
					link.l2 = "我是" +GetFullName(pchar)+ "船长。 我想知道为什么你会这么匆忙, 差点把裤子忘在妓院... ";
					link.l2.go = "Reason_To_Fast_21";
					link.l3 = "我是" +GetFullName(pchar)+ "船长。 我只是在这里散步, 呼吸着咸咸的海风... ";
					link.l3.go = "Reason_To_Fast_31";
				}
				else
				{
					Diag.TempNode = "GoodBye";
					dialog.text = "你终于来了。 我以为再也见不到你了。 和你在一起的那个家伙是谁? ";
					link.l1 = "什么家伙? ";
					link.l1.go = "Reason_To_Fast_Hunter";
				} 
		break;
		
		case "Reason_To_Fast_Hunter":
			DialogExit();	
			AddDialogExitQuest("ReasonToFast_MeetHunter");
		break;
		
		case "Reason_To_Fast_11":
			dialog.text = "你看起来不太像我会信任的" + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + "。 ";
			if(!CheckCharacterItem(pchar,"mapQuest"))
			{
				link.l1 = "好吧, 我会把你说的都告诉他。 ";
				link.l1.go = "Reason_To_Fast_12";
			}	
			link.l2 = "这个" + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + "是谁? ";
			link.l2.go = "Reason_To_Fast_13";
		break;
		
		case "Reason_To_Fast_21":
			dialog.text = "好奇心杀死的人比猫多得多... ";
			link.l1 = "好吧好吧! ";
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAfter";	
		break;
		
		case "Reason_To_Fast_31":
			Diag.TempNode = "Reason_To_Fast_GoodBye";
			dialog.text = "潮水来了。 你最好离开海湾, 这里的水会涨到棕榈树的高度。 ";
			link.l1 = "没问题, 我是个游泳健将。 ";
			link.l1.go = "Reason_To_Fast_GoodBye_0";
			pchar.questTemp.ReasonToFast = "MeetPatrolFail";
		break;
		
		case "Reason_To_Fast_12":
			jewelType = sti(pchar.questTemp.ReasonToFast.p4);
			pchar.questTemp.ReasonToFast.item = "jewelry" + jewelType;
			sItem = "jewelry" + jewelType;
			switch (jewelType)
			{
				case 1:
					sItemName = "紫水晶";
				break;
				case 2:
					sItemName = "钻石";
				break;
				case 3:
					sItemName = "红宝石";
				break;
				case 4:
					sItemName = "祖母绿";
				break;
			}
			pchar.questTemp.ReasonToFast.jewType = sItemName;
			dialog.text = "好吧, 好吧。 你带了承诺的30颗" + sItemName + "吗? ";
			link.l1 = GetName(NAMETYPE_MAIN , pchar.questTemp.ReasonToFast.p3, NAME_NOM) + "说没有足够的时间收集那么多宝石。 他命令我用金钱代替。 ";
			link.l1.go = "Reason_To_Fast_14";
			if (GetCharacterItem(pchar, pchar.questTemp.ReasonToFast.item) >= 30)
			{
				link.l2 = "给你。 ";
				link.l2.go = "Reason_To_Fast_15";
			}			
		break;
		
		case "Reason_To_Fast_13":
			dialog.text = "嘿! 你会在地狱里知道的! ";
			link.l1 = "真是自信... ";
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAfter";	
		break;
		
		case "Reason_To_Fast_14":
			dialog.text = "好吧, 那么你欠我" + sti(pchar.questTemp.ReasonToFast.p5) + "比索, 正如我们约定的。 ";
			link.l1 = "这是不是有点太多了? ";
			link.l1.go = "Reason_To_Fast_16";
			if(makeint(pchar.money) >= sti(pchar.questTemp.ReasonToFast.p5))
			{
				link.l2 = "给你。 ";
				link.l2.go = "Reason_To_Fast_17";
			}	
			link.l3 = "但我身上没有那么多钱! ";
			link.l3.go = "Reason_To_Fast_18";	
			AddQuestRecord("ReasonToFast", "9");
			AddQuestUserData("ReasonToFast", "sText", pchar.questTemp.ReasonToFast.jewType);
		break;
		
		case "Reason_To_Fast_15":
			TakeNItems(pchar, pchar.questTemp.ReasonToFast.item, -30); 
			dialog.text = "一切都符合协议。 给你。 这张地图是从被绞死的海盗那里拿到的, 就是"  + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + "打听的那个海盗。 ";
			link.l1 = "交易完成! ";
			link.l1.go = "Reason_To_Fast_15_1";
		break;
		
		case "Reason_To_Fast_15_1":
			Diag.TempNode = "Reason_To_Fast_GoodBye";
			DialogExit();
			AddQuestRecord("ReasonToFast", "10");
			AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM));
			pchar.questTemp.ReasonToFast = "PatrolSuccess_2";
			GiveItem2Character(pchar, "mapQuest"); 
			arItem = ItemsFromID("mapQuest");
			ReasonToFast_GenerateTreasureMap(arItem);	
			DeleteAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther");//可以和告密者说话 
			AddDialogExitQuest("pchar_back_to_player");	
			LAi_LocationFightDisable(&locations[FindLocation(pchar.questTemp.ReasonToFast.PatrolLocation)], false);	
		break;
		
		case "Reason_To_Fast_16":
			dialog.text = "我们已经提前和" + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_ABL) + "谈好了金额。 我一点也不喜欢这样。 杀了他" + GetSexPhrase("们","她") + ", 伙计们! ";
			link.l1 = "好吧, 你们可以试试! ";
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAfter";	
		break;
		
		case "Reason_To_Fast_17":
			pchar.questTemp.ReasonToFast = "PatrolSuccess_1";
			AddMoneyToCharacter(pchar, -makeint(sti(pchar.questTemp.ReasonToFast.p5)));
			pchar.GenQuest.CannotWait = 1; // 锁定休息界面
			if(CheckAttribute(pchar,"questTemp.ReasonToFast.chain")) DeleteAttribute(pchar,"questTemp.ReasonToFast.chain");
			if(CheckAttribute(pchar,"questTemp.ReasonToFast.ShipName")) DeleteAttribute(pchar,"questTemp.ReasonToFast.ShipName");
			if(CheckAttribute(pchar,"questTemp.ReasonToFast.ShipTypeName")) DeleteAttribute(pchar,"questTemp.ReasonToFast.TypeName");
			switch (sti(pchar.questTemp.ReasonToFast.target))
			{
				case 0: // 载有货物的船
					sTemp1 = generateRandomNameToShip(sti(pchar.questTemp.ReasonToFast.GuardNation));
					iShipType = ReasonToFast_GetVictimShipType();
					iShipGoods = ReasonToFast_GetVictimShipGoods();
					dialog.text = "太好了! 现在我们来谈正事。 我们截获了那艘" + GetStrSmallRegister(pchar.questTemp.ReasonToFast.ShipTypeName) + "'" + sTemp1 + "', 船上载有" + GetGoodsNameAlt(iShipGoods) + "货物, 船员已经被拘留,'货物'还在船上。 船员是在港口的落魄者中雇佣的, 他们明天之前不会进港。 你可以随意处理他们。 ";
					link.l1 = "好的。 我会把你的话告诉" + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_DAT) + "。 ";
					link.l1.go = "Reason_To_Fast_GoodBye_0";
					pchar.questTemp.ReasonToFast.chain = "A0";
					pchar.questTemp.ReasonToFast.ShipName = sTemp1;										
					DeleteAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther");//可以和告密者说话
					AddQuestRecord("ReasonToFast", "11");
					AddQuestUserData("ReasonToFast", "sShipType", pchar.questTemp.ReasonToFast.ShipTypeName);					
					AddQuestUserData("ReasonToFast", "sShipName", sTemp1);
					AddQuestUserData("ReasonToFast", "sGoodsName", GetGoodsNameAlt(iShipGoods));
					ReasonToFast_GenerateVictimShip(iShipType, iShipGoods);					
				break;

				case 1: // 总督的宝藏
					switch(rand(3))
					{
						case 0:
							sTemp1 = "总督女儿的嫁妆是";
						break;
						case 1:
							sTemp1 = "总督给总督的礼物是";
						break;
						case 2:
							sTemp1 = "总督周年纪念的礼物是";
						break;
						case 3:
							sTemp1 = "总督的'养老金'是";
						break;
					}
					switch(rand(3))
					{
						case 0:
							sTemp2 = "欺骗";
						break;
						case 1:
							sTemp2 = "恶作剧";
						break;
						case 2:
							sTemp2 = "玩笑";
						break;
						case 3:
							sTemp2 = "淘气";
						break;
					}
					pchar.questTemp.ReasonToFast.password = sTemp2;
					sTemp2 = generateRandomNameToShip(sti(pchar.questTemp.ReasonToFast.GuardNation));
					dialog.text = "太好了! " + sTemp1 + "放在他的闺房里。 信使船随时都会到达, 但你仍然需要处理。 仆人是'我们的'人。 密码:'" + pchar.questTemp.ReasonToFast.password + "', 回复:'" + sTemp2 + "'。 ";
					link.l1 = "好的。 我会把你的话告诉" + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_DAT) + "。 ";
					link.l1.go = "Reason_To_Fast_GoodBye_0";
					pchar.questTemp.ReasonToFast.chain = "A1";
					AddQuestRecord("ReasonToFast", "12");
					pchar.questTemp.ReasonToFast.ShipName = sTemp2;
					DeleteAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther");//可以和告密者说话
					
					pchar.quest.ReasonToFast_ClearLakey.win_condition.l1 = "Timer";
					pchar.quest.ReasonToFast_ClearLakey.win_condition.l1.date.day = GetAddingDataDay(0, 0, 2);
					pchar.quest.ReasonToFast_ClearLakey.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
					pchar.quest.ReasonToFast_ClearLakey.win_condition.l1.date.year = GetAddingDataYear(0, 0, 2);
					pchar.quest.ReasonToFast_ClearLakey.function = "ReasonToFast_ClearLakey";
				break;				
			}
		break;
		
		case "Reason_To_Fast_18":
			if(makeint(pchar.money) >= sti(pchar.questTemp.ReasonToFast.p5))
			{
				dialog.text = "你想骗我吗? ! 你这狗东西! ";
				link.l1 = "闭嘴! ";
				link.l1.go = "Reason_To_Fast_ExitFight";
				pchar.questTemp.ReasonToFast = "PatrolAfter";	
			}
			else
			{
				dialog.text = "你把钱喝光了! 我的钱! ... 啊。 ";
				link.l1 = "该死! ";
				link.l1.go = "Reason_To_Fast_ExitFight";
				pchar.questTemp.ReasonToFast = "PatrolAfter";	
			}
		break;

		case "Reason_To_Fast_GoodBye_0":
			LAi_SetPlayerType(pchar);
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				sld.Dialog.CurrentNode = "Reason_To_Fast_GoodBye";
				sld.greeting = "soldier_common";
				LAi_SetWarriorType(sld);
				LAi_warrior_DialogEnable(sld, true);
				LAi_group_MoveCharacter(sld, sGroup);				
			}
			pchar.quest.RemovePatrolFromShore.win_condition.l1          = "ExitFromLocation";
			pchar.quest.RemovePatrolFromShore.win_condition.l1.location = pchar.location; 
            pchar.quest.RemovePatrolFromShore.function    				= "ReasonToFast_DeletePatrolFromShore"; 
			DialogExit();			
		break;
		
		case "Reason_To_Fast_GoodBye":
			Diag.TempNode = "Reason_To_Fast_GoodBye";
			dialog.text = "你最好离开海湾, 潮水已经来了... ";
			link.l1 = "是的, 是的, 我这就走。 ";
			link.l1.go = "Exit";
		break;
		
		case "Reason_To_Fast_ExitFight":
			pchar.questTemp.ReasonToFast.relation = GetNationRelation2MainCharacter(sti(pchar.questTemp.ReasonToFast.GuardNation));
			SetNationRelation2MainCharacter(sti(pchar.questTemp.ReasonToFast.GuardNation), RELATION_ENEMY); 
			
			pchar.GenQuest.HunterScore2Pause = 1; // 猎人分数不增加
			pchar.GenQuest.ReputationNotChange = 1; // 不改变声誉
			
			chrDisableReloadToLocation = true;
			LAi_SetPlayerType(pchar);
			LAi_LocationFightDisable(&locations[FindLocation(pchar.questTemp.ReasonToFast.PatrolLocation)], false);	
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, sGroup);
			}
			if(pchar.questTemp.ReasonToFast == "PatrolAngry")
			{
				sld = CharacterFromID("ReasonToFast_Hunter");
				if(sld != -1) 
				{ 
					LAi_SetWarriorType(sld); 
					LAi_group_MoveCharacter(sld, sGroup);
				}
			}			
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors"); 
			LAi_group_SetCheck(sGroup, "ReasonToFast_PatrolDied");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Reason_To_Fast_AfterHunter1":
			dialog.text = "我们不是约定信使必须单独来吗? ";
			link.l1 = "缺乏协调。 信使迷路了。 我是来代替的。 ";
			link.l1.go = "Reason_To_Fast_11";
			link.l2 = "我是单独来的, 但不是为了你所期望的。 ";
			link.l2.go = "Reason_To_Fast_AfterHunter2";
		break;
		
		case "Reason_To_Fast_AfterHunter2":
			dialog.text = "所以, 你终究还是追踪到我了, 很抱歉将要发生的事... ";
			link.l1 = "啊! ";
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAfterHunter";	
		break;
		
		case "Reason_To_Fast_AfterHunter3":
			dialog.text = "你这个混蛋! 我差点就相信了! 卫兵! 抓住他" + GetSexPhrase("们","她") + "... ";
			link.l1 = "试试吧, 混蛋们! ";
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAngry";	
		break;
		// 生成器 "匆忙的理由"
	}
}
// 不公平的竞争者
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "这是一个漏洞。 请告知开发人员";
			link.l1 = "当然! ";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "ShadowGuarder":
			dialog.text = "你需要什么? ";
			link.l1 = "你是" + pchar.questTemp.Shadowtrader.Guardername + "吗? 当地商人派我来的。 他此刻正急切地等待你的出现。 ";
			link.l1.go = "ShadowGuarder_1";
			DelLandQuestMark(npchar);
		break;
	
		case "ShadowGuarder_1":
			dialog.text = "啊, 但我一直在这里等他! 有人告诉我他会来酒馆! 抱歉, 我马上就去。 ";
			link.l1 = "很好! ";
			link.l1.go = "ShadowGuarder_2";
		break;
	
		case "ShadowGuarder_2":
			DialogExit();
			chrDisableReloadToLocation = true;
			sld = characterFromId("ShadowGuarder");	
			LAi_SetStayType(sld);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.questTemp.Shadowtrader.City + "_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", pchar.questTemp.Shadowtrader.City +"_store", "goto", "goto2", "OpenTheDoors", 6);
			pchar.questTemp.Shadowtrader = "begin";
			AddLandQuestMark(characterFromId("BasTer_trader"), "questmarkmain");
		break;
	
		case "ShadowAgent":
			dialog.text = "晚上好, 船长。 想搞点便宜货, 嗯? 跟我来! ";
			link.l1 = "带路吧。 ";
			link.l1.go = "ShadowAgent_1";
		break;
	
		case "ShadowAgent_1":
			DeleteAttribute(pchar, "questTemp.Shadowtrader.SeekTrader");
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "houseS4", "CommonFlamHouse", "barmen", "stay", "Shadow_inRoom", 40);
		break;
	
		case "ShadowTrader":
			dialog.text = "晚上好, 先生。 很高兴认识新客户, 哈! 让我介绍一下自己: 我是" + GetFullName(npchar) + "。 我向你保证, 我有这个镇上最便宜的货物。 ";
			link.l1 = "终于见到你了... " + npchar.name+ "。 我想我会让你失望的: 我找你不是为了交易, 而是为了结束你肮脏的勾当。 你已经成为一个重要人物的眼中钉。 这根刺已经扎得太深, 他渴望不惜一切代价把你除掉... ";
			link.l1.go = "ShadowTrader_1";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				Notification_Perk(true, "Trustworthy");
				link.l2 = "站住, 罪犯人渣! 你不知道经营商业需要纳税吗? 在我眼皮底下没人能违法! " + GetFullName(npchar) + ", 你违反了法律, 你偷来的货物现在被没收了! 门外就有武装士兵, 所以别想装傻! ";
				link.l2.go = "ShadowTrader_2";
			}
			AddLandQuestMark(characterFromId("BasTer_trader"), "questmarkmain");
		break;
	
		case "ShadowTrader_1":
			dialog.text = "真的吗? 我没想到... 你到底是谁? ! 这是个圈套! 我想我知道谁该为此负责! 不惜一切代价... 伙计们, 杀了他! ";
			link.l1 = "来跳舞吧, 恶棍! ";
			link.l1.go = "ShadowTrader_fight";
			NextDiag.currentnode = "ShadowTrader_6";
		break;
	
	case "ShadowTrader_2":
		dialog.text = "哦, 上帝... 长官, 听着! 我们做个交易吧。 你是个明智而仁慈的人! 我会给你5000八里亚尔, 你让我们从二楼逃走。 你也可以拿走货物, 你需要它们, 对吧? 你为什么需要我? 我现在就离开这个镇, 再也不会有人见到我们。 而你会得到你的钱。 你觉得怎么样, 长官? ";
		link.l1 = "你真的认为,人渣, 我会为了这么点小钱而玷污我的职责吗? ";
		link.l1.go = "ShadowTrader_3";
		break;
	
	case "ShadowTrader_3":
		dialog.text = "好吧, 好吧, 长官, 把我所有的都拿走 —10,000比索。 我发誓这是我所有的了! ";
		link.l1 = "嗯... 如果我逮捕你, 你所有的钱都会被没收... 很好! 这个走私点关闭, 所有货物没收... 把钱给我, 然后滚蛋。 别再在这里露面了! ";
		link.l1.go = "ShadowTrader_4";
		break;
		
	case "ShadowTrader_4":
			dialog.text = "谢谢你, 谢谢你, 谢谢你, 长官! 这是你的钱, 你不会再在这里见到我了。 我们走! ";
			link.l1 = "滚出去, 否则我就逮捕你! ";
			link.l1.go = "ShadowTrader_escape";
		break;
	
		case "ShadowTrader_fight":
			LAi_SetPlayerType(pchar);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("ShadowAgent_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				sld.nation = PIRATE;
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "ShadowTrader_afterfight");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
	
		case "ShadowTrader_escape"://恐吓成功
			AddMoneyToCharacter(pchar, 10000);
			LAi_SetPlayerType(pchar);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("ShadowAgent_"+i);	
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload3", "none", "", "", "", 7.0);
			}
			sld = characterFromID("ShadowTrader"); 
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload3", "none", "", "", "", 7.0);
			DialogExit();
			DoQuestFunctionDelay("ShadowTrader_final", 9.0);
			pchar.questTemp.Shadowtrader.End.Escape = "true";
			AddQuestRecord("Shadowtrader", "8");
			AddCharacterExpToSkill(pchar, "Leadership", 200);//权威
			AddCharacterExpToSkill(pchar, "Fortune", 250);//运气
			AddCharacterExpToSkill(pchar, "Sneak", 300);//潜行
		break;
	
		case "ShadowTrader_6":
			dialog.text = "啊! mercy, 别杀我! 我会把我所有的都给你! ";
			link.l1 = "你所有的货物都会被当局没收。 在发生了刚才的事情后, 你真的认为我会对你仁慈吗? ";
			link.l1.go = "ShadowTrader_7";
		break;
	
		case "ShadowTrader_7":
			dialog.text = "我... 我会把我所有的钱和财物都给你! 让我走吧! 我今天就离开这个岛, 你不会再在这里见到我了! ";
			link.l1 = "很好。 把你身上所有的东西都给我, 然后滚蛋。 再也不要在这里做生意了 —下次我不会饶了你这条可怜的命, 你这个强盗。 ";
			link.l1.go = "ShadowTrader_free";
			link.l2 = "没门, 混蛋, 你收买不了我。 对付你这种人的唯一办法就是冷钢和热铅! ";
			link.l2.go = "ShadowTrader_killed";
		break;
		
		case "ShadowTrader_free"://释放
			AddMoneyToCharacter(pchar, 20550);
			TakeNItems(pchar, "jewelry1", rand(5));
			TakeNItems(pchar, "jewelry2", rand(20));
			TakeNItems(pchar, "jewelry5", rand(20));
			PlaySound("interface\important_item.wav");
			Log_Info("你收到了物品");
			LAi_SetPlayerType(pchar);
			sld = characterFromID("ShadowTrader"); 
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload3", "none", "", "", "", 5.0);
			DialogExit();
			DoQuestFunctionDelay("ShadowTrader_final", 7.0);
			pchar.questTemp.Shadowtrader.End.Free = "true";
			AddQuestRecord("Shadowtrader", "9");
			ChangeCharacterComplexReputation(pchar,"nobility", 5); 
			AddComplexSelfExpToScill(70, 70, 70, 70);
			AddCharacterExpToSkill(pchar, "Leadership", 100);//权威
			AddCharacterExpToSkill(pchar, "Fortune", 100);//运气
		break;
	
		case "ShadowTrader_killed":
			DialogExit();
			AddDialogExitQuestFunction("ShadowTrader_KillToTrader_kino");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
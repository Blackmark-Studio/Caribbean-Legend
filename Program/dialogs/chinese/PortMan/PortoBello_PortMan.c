// 城市相关对话
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	int i,n;
	string month;
	
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("什么问题? ", "你想要什么, " + GetAddress_Form(NPChar) + "? "), "你已经试过问我问题了, " + GetAddress_Form(NPChar) + "... ", "你今天已经第三次谈论某个问题了... ",
                          "听着, 如果你没有关于港口事务的事情告诉我, 就别用问题打扰我。 ", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了。 ", "我没什么可谈的。 "), "没关系。 ", "确实, 已经第三次了... ", 
						"抱歉, 但我现在对港口事务不感兴趣。 ", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatPortobello_1")
            {
                link.l1 = "日安。 我想知道弗朗索瓦.贡捷船长在哪里, 我有重要的事情找他。 ";
                link.l1.go = "Portobello_ratP_1";
            }
			// belamour legengary edition 与阿库拉联动任务 -->
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet"))
			{
				if(pchar.questTemp.SharkGoldFleet == "toPBPortOffice" || pchar.questTemp.SharkGoldFleet == "KillCurier")
				{
					link.l1 = "我是商人, 从加拉加斯来, 当地港务局的同事让我给你送些信件... ";
					link.l1.go = "SharkGoldFleet";
				}
				if(pchar.questTemp.SharkGoldFleet == "MoneySpeak")
				{
					link.l1 = "是的, 我来取报酬。 ";
					link.l1.go = "SharkGoldFleet_11";
				}
			}
			//< —与阿库拉联动任务
		break;

		case "Portobello_ratP_1":
			dialog.text = "你说有重要的事? 让我看看。 嗯... 弗朗索瓦.贡捷, 驾驶护卫舰‘" + pchar.questTemp.Slavetrader.ShipName + "’... 根据我的记录, 贡捷先生正前往牙买加。 ";
			link.l1 = "谢谢你! 你帮了大忙! ";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "FindRatJamaica";
			AddQuestRecord("Slavetrader", "21_3");
			AddQuestUserData("Slavetrader", "sShip", pchar.questTemp.Slavetrader.ShipName);
		break;
		// 与阿库拉联动任务 -->
		case "SharkGoldFleet":
			if(!bImCasual) pchar.quest.SharkGoldFleetToPB10.over = "yes"; 
			RemoveItems(PChar, "letter_1", 1);
			ChangeItemDescribe("letter_1", "itmdescr_letter_1");
			dialog.text = "啊, 终于来了! 你说你是商人? 他们又想在信使上省钱, 把运送拖到最后一刻... 是啊, 好吧! 确实是这样。 在这么短的时间内, 我该怎么用这些东西装备舰队? ... ";
			link.l1 = "听起来很不负责任... ";
			link.l1.go = "SharkGoldFleet_01";
		break;
		
		case "SharkGoldFleet_01":
			dialog.text = "你这么说也算一种方式! 好吧, 算了, 能怎么办呢。 我们会及时和你会合... 我是说我的时间, 别在意。 听着, 你有可能回去吗? ";
			link.l1 = "嗯, 其实我本来打算在这里卖货, 然后 —是的, 回加拉加斯... ";
			link.l1.go = "SharkGoldFleet_02";
		break;
		
		case "SharkGoldFleet_02":
			dialog.text = "太好了! 现在我写封回信, 请你带回去。 所以... 请在十天内送达, 否则他们来不及做任何事... 说说你的名字。 ";
			if(pchar.questTemp.SharkGoldFleet == "KillCurier")
			{
				link.l1 = "我叫" +GetFullName(pchar)+ "。 ";
				link.l1.go = "SharkGoldFleet_03";
			}
			else
			{
				link.l1 = "我叫安德烈亚斯.加西亚。 ";
				link.l1.go = "SharkGoldFleet_09";
			}
		break;
		
		case "SharkGoldFleet_03":
			TakeNItems(pchar, "letter_2", 1);
			ChangeItemDescribe("letter_2", "itmdescr_letter_SharkGoldFleet_2");
			dialog.text = "等一下... 记录好了。 给你。 记住: 十天! 同时我会仔细看看你带给我的东西。 ";
			link.l1 = "好的, 我记住了。 再见! ";
			link.l1.go = "SharkGoldFleet_04";
		break;

		case "SharkGoldFleet_04":
			dialog.text = "等一下... 我没明白... 再说一遍, 你说你叫什么名字? ";
			link.l1 = "我? ... 嗯... 为什么这么重要? ";
			link.l1.go = "SharkGoldFleet_05";
		break;
		
		case "SharkGoldFleet_05":
			n = GetAddingDataDay(0,0,21);
			if(n<21) i = GetAddingDataMonth(0,1,0);
			else i = GetDataMonth();
			month = XI_ConvertString("target_month_" + i);
			pchar.questTemp.SharkGoldFleet.Date = ""+n+" "+month+"";
			SetFunctionTimerCondition("SharkGoldFleet1269fail", 0, 0, 22, false);
			SetFunctionTimerCondition("SGF_FleetTime", 0, 0, 21, false);
			if(!bImCasual) SetFunctionTimerCondition("SharkGoldFleetToCPO10", 0, 0, 10, false);
			else NewGameTip("探索模式: 计时器已禁用。 ");
			dialog.text = "这很重要! 上面写着... 所以... "+n+" "+month+"... 不, 不是... 12,50,69,55... 但它在哪里... 啊, 找到了! 这封信必须由"+pchar.questTemp.SharkGoldFleet.CurierName+" "+pchar.questTemp.SharkGoldFleet.Curierlastname+"船长送达。 你说你叫... "+GetFullName(pchar)+"? ";
			link.l1 = "一定是哪里弄错了... ";
			link.l1.go = "SharkGoldFleet_06";
		break;
		
		case "SharkGoldFleet_06":
			DeleteAttribute(pchar,"questTemp.SharkGoldFleet.CurierName");
			DeleteAttribute(pchar,"questTemp.SharkGoldFleet.Curierlastname");
			dialog.text = "不, 不可能弄错。 把我给你的信还给我, 我得弄清楚这件事! ";
			link.l1 = "拜托... 我会送达的, 一切都会好的。 ";
			link.l1.go = "SharkGoldFleet_07";
		break;
		
		case "SharkGoldFleet_07":
			dialog.text = "不! 把信还给我! 卫兵!! ";
			link.l1 = "啊, 你想硬来, 是吗? ";
			link.l1.go = "SharkGoldFleet_08";
		break;
		
		case "SharkGoldFleet_08":
			DialogExit();
			pchar.questTemp.SharkGoldFleet = "DifficultVar";
			if (CheckCharacterItem(pchar, "HolTradeLicence"))
			{
				TakeNationLicence(HOLLAND);
				log_info("贸易许可证已取消! ");
			}
			for (i=1; i<=2; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Sold"+i, "sold_" + NationShortName(SPAIN) + "_" + (rand(1) + 1), "man", "man", sti(pchar.rank), SPAIN, 0, true, "soldier"));
				SetFantomParamFromRank(sld, sti(pchar.rank), true);         
				ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto3");
				LAi_SetWarriorType(sld); 
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				LAi_group_Attack(sld, Pchar);
			}
			LAi_group_Attack(NPChar, Pchar);
			SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
			SetFunctionExitFromLocationCondition("SharkGoldFleetExitPO", pchar.location, false);
		break; 
		
		case "SharkGoldFleet_09":
			dialog.text = "等一下... 好了。 那我在回信里记下你的名字。 给你。 记住: 你有十天时间! 同时我会仔细看看你带给我的东西。 ";
			link.l1 = "好的, 我记住了。 再见! ";
			link.l1.go = "SharkGoldFleet_10";
		break;
		
		case "SharkGoldFleet_10":
			DialogExit();
			pchar.questTemp.SharkGoldFleet = "MoneySpeak";
			TakeNItems(pchar, "letter_2", 1);
			ChangeItemDescribe("letter_2", "itmdescr_letter_SharkGoldFleet_2");
			AddQuestRecord("SharkGoldFleet", "17");
			chrDisableReloadToLocation = true;
			bDisableFastReload = true;
		break;
		
		case "SharkGoldFleet_11":
			dialog.text = "报酬? ..";
			link.l1 = "在加拉加斯, 你的同事告诉我你会支付送信的费用。 ";
			link.l1.go = "SharkGoldFleet_12";
		break;
		
		case "SharkGoldFleet_12":
			dialog.text = "不, 好吧, 那里的人完全疯了! 现在我得替他们付钱! ";
			link.l1 = "... ";
			link.l1.go = "SharkGoldFleet_13";
		break;
		
		case "SharkGoldFleet_13":
			dialog.text = "他们答应给你多少? ";
			link.l1 = "五千比索。 ";
			link.l1.go = "SharkGoldFleet_14";
			link.l2 = "一万比索。 ";
			link.l2.go = "SharkGoldFleet_15";
		break;
		
		case "SharkGoldFleet_14":
			pchar.questTemp.SharkGoldFleet = 5000;
			dialog.text = "显然, 他们打算靠我的钱过活... 他们不仅不想花钱雇信使, 把这种事交给过往商船, 还把费用甩给我! 我要向哈瓦那投诉他们! ";
			link.l1 = "我理解你的愤怒, 先生, 但我该怎么办? ";
			link.l1.go = "SharkGoldFleet_16";
		break;
		
		case "SharkGoldFleet_15":
			pchar.questTemp.SharkGoldFleet = 10000;
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			ChangeOfficersLoyality("bad", 1);
			dialog.text = "显然, 他们打算靠我的钱过活... 他们不仅不想花钱雇信使, 把这种事交给过往商船, 还把费用甩给我! 我要向哈瓦那投诉他们! ";
			link.l1 = "我理解你的愤怒, 先生, 但我该怎么办? ";
			link.l1.go = "SharkGoldFleet_16";
		break;
		
		case "SharkGoldFleet_16":
			dialog.text = "啊, 你不该为加拉加斯的新西班牙官员的贪婪负责。 但我现在身上没那么多钱。 预算明天才会到... 请在这里等一下, 我现在去找放债人, 很快就回来。 ";
			link.l1 = "... ";
			link.l1.go = "SharkGoldFleet_17";
		break;
		
		case "SharkGoldFleet_17":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload1");
			LAi_SetStayType(npchar);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto2");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "reload", "reload1","SGF_toUsurer", -1);
		break;
		
		case "SharkGoldFleet_18":
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.SharkGoldFleet));
			n = GetAddingDataDay(0,0,21);
			if(n<21) i = GetAddingDataMonth(0,1,0);
			else i = GetDataMonth();
			month = XI_ConvertString("target_month_" + i);
			pchar.questTemp.SharkGoldFleet.Date = ""+n+" "+month+"";
			SetFunctionTimerCondition("SharkGoldFleet1269fail", 0, 0, 22, false);
			SetFunctionTimerCondition("SGF_FleetTime", 0, 0, 21, false);
			if(!bImCasual) SetFunctionTimerCondition("SharkGoldFleetToCPO10", 0, 0, 10, false);
			else NewGameTip("探索模式: 计时器已禁用。 ");
			AddQuestRecord("SharkGoldFleet", "18");
			AddQuestUserData("SharkGoldFleet", "date", pchar.questTemp.SharkGoldFleet.Date);
			LAi_SetHuberType(npchar);
			Lai_SetPlayerType(pchar);
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			dialog.text = "抱歉让你久等了。 这是你的"+makeint(pchar.questTemp.SharkGoldFleet)+"枚八里亚尔银币。 这种情况下, 加拉加斯那边会自己支付回信的费用。 告诉他们是我这么说的。 ";
			link.l1 = "好的, 我会转告。 谢谢你, 祝你好运! ";
			link.l1.go = "exit";
			pchar.questTemp.SharkGoldFleet = "LightVar";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // 如果switch内部某处通过return退出, 别忘了进行卸载
}
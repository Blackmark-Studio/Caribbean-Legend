void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n, iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	bool ok;
    int iTest;
    ref rColony;
    string sFrom_sea = "";
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		//任务相关
		case "Regata_Cureer":
			dialog.text = "日安。 您是" +GetFullName(pchar)+ "船长吗? ";
			link.l1 = "是的, 是我。 有什么事吗? ";
			link.l1.go = "Regata_Cureer_1";
		break;
		
		case "Regata_Cureer_1":
			dialog.text = "我有一封牙买加总督爱德华.多伊利爵士给您的信。 ";
			link.l1 = "哇! 没想到... 总督找我有什么事? ";
			link.l1.go = "Regata_Cureer_2";
		break;
		
		case "Regata_Cureer_2":
			dialog.text = "读信吧, 先生。 简而言之, 邀请您参加横跨群岛的帆船赛。 关于您的航海技巧和卓越航速的传闻已广为人知。 ";
			link.l1 = "难以置信! 我... 我会考虑的。 ";
			link.l1.go = "Regata_Cureer_3";
			GiveItem2Character(pchar, "letter_open");
			ChangeItemDescribe("letter_open", "itmdescr_letter_open_Regata");
			AddQuestRecordInfo("RegataLetter", "1");
		break;
		
		case "Regata_Cureer_3":
			if (Pchar.BaseNation == SPAIN || Pchar.BaseNation == HOLLAND)
			{
				dialog.text = "另外, 我还为您提供皇家港的免费通行许可。 这是30天的许可证。 现在我的任务完成了。 再见, 船长。 ";
				link.l1 = "谢谢。 这许可证太有用了。 再会! ";
				link.l1.go = "Cureer_exit";
				GiveNationLicence(HOLLAND, 30);
			}
			else
			{
				dialog.text = "好的。 现在我的任务完成了。 再见, 船长。 ";
				link.l1 = "再会! ";
				link.l1.go = "Cureer_exit";
			}
		break;
		
		case "Cureer_exit":
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
			pchar.questTemp.Regata.ToPortRoyal = "true";
			SetQuestHeader("Regata");
			AddQuestRecord("Regata", "1");
		break;
		
		//帆船赛组织者
		case "Regata_Head":
			if (CheckAttribute(pchar, "questTemp.Regata.Begin"))
			{
				dialog.text = "日安。 我猜您正在参加帆船赛? ";
				link.l1 = "正是, 先生。 我叫" +GetFullName(pchar)+ "。 我收到了邀请。 ";
				link.l1.go = "Regata_Head_1";
			}
			else
			{
				dialog.text = "先生, 需要什么吗? ";
				link.l1 = "不, 没什么。 我这就走。 ";
				link.l1.go = "exit";
				NextDiag.TempNode = "Regata_Head";
			}
		break;
		
		case "Regata_Head_1":
			iTest = FindColony("PortRoyal"); 
			if (iTest != -1)
			{
				rColony = GetColonyByIndex(iTest);
			}
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//检查港口是否有船
			{
				dialog.text = "很高兴见到您, " +GetFullName(pchar)+ "船长。 那我们开始吧。 您已经从信中了解了基本要求, 对吗? 只能用小帆船, 且您的中队中只能有这一艘船才能参加帆船赛。 您满足这些要求吗? ";
				// belamour legendary edition 允许信使小帆船 
				ok = sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_LUGGER || sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_CAREERLUGGER;
				if((GetCompanionQuantity(pchar) > 1) || !ok)
				{
					link.l1 = "还没有。 我现在就去准备, 很快回来。 ";
					link.l1.go = "exit";
					NextDiag.TempNode = "Regata_Head_repeat";
				}
				else
				{
					link.l1 = "是的, 准备好了。 ";
					link.l1.go = "Regata_Head_2";
				}
			}
			else
			{
				dialog.text = "您来参加帆船赛, 但您的船呢, 船长? ";
				link.l1 = "抱歉, 先生。 我马上把船开到港口。 ";
				link.l1.go = "exit";
				NextDiag.TempNode = "Regata_Head_repeat";
			}
		break;
		
		case "Regata_Head_repeat":
			if (CheckAttribute(pchar, "questTemp.Regata.Begin"))
			{
				iTest = FindColony("PortRoyal"); 
				if (iTest != -1)
				{
					rColony = GetColonyByIndex(iTest);
				}
				ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
				if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//检查港口是否有船
				{
					ok = sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_LUGGER || sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_CAREERLUGGER;
					dialog.text = "啊, 又是您。 您完成帆船赛的要求了吗? ";
					// belamour legendary edition 允许信使小帆船 
					if ((GetCompanionQuantity(pchar) > 1) || !ok)
					{
						link.l1 = "还没有。 我现在就去准备, 很快回来。 ";
						link.l1.go = "exit";
						NextDiag.TempNode = "Regata_Head_repeat";
					}
					else
					{
						link.l1 = "是的, 准备好了。 ";
						link.l1.go = "Regata_Head_2";
					}
				}
				else
				{
					dialog.text = "船长, 在我看到您的船停泊在港口前, 我们没什么可谈的。 您明白我的意思吗? 还是需要我再重复一遍? ";
					link.l1 = "抱歉, 先生。 我马上把船开到港口。 ";
					link.l1.go = "exit";
					NextDiag.TempNode = "Regata_Head_repeat";
				}
			}
			else
			{
				dialog.text = "先生, 需要什么吗? ";
				link.l1 = "不... 没什么。 我这就走。 ";
				link.l1.go = "exit";
				NextDiag.TempNode = "Regata_Head";
			}
		break;
		
		case "Regata_Head_2":
			dialog.text = "很好。 接下来, 您的船叫什么名字? ";
			link.l1 = "'"+pchar.Ship.Name+"'。 ";
			link.l1.go = "Regata_Head_3";
		break;
		
		case "Regata_Head_3":
			dialog.text = "由于帆船赛由英国当局主办, 根据固定规则, 您的船名在赛事期间必须更改。 别担心, 每位参赛者都要这样做。 ";
			link.l1 = "据说改船名会带来厄运。 ";
			link.l1.go = "Regata_Head_4";
		break;
		
		case "Regata_Head_4":
			dialog.text = "赛后您可以改回原名。 所以, 您的小帆船将使用‘圣凯瑟琳’这个名字。 ";
			link.l1 = "我明白了, 先生, 我会改名字。 ";
			link.l1.go = "Regata_Head_5";
			pchar.Ship.Name = "Saint Catherine";
		break;
		
		case "Regata_Head_5":
			dialog.text = "现在我们来谈谈帆船赛本身。 仔细听。 我还会给您一份规则文件。 \n帆船赛从皇家港出发并结束。 您需要到达五个点\n第一个是皇家港到西大陆的伯利兹\n第二个是伯利兹到伊斯帕尼奥拉岛的太子港\n第三个是太子港到安提瓜的圣约翰\n第四个是圣约翰到巴巴多斯的布里奇敦\n最后一个是布里奇敦到皇家港\n清楚了吗? ";
			link.l1 = "非常清楚, 先生。 ";
			link.l1.go = "Regata_Head_6";
		break;
		
		case "Regata_Head_6":
			dialog.text = "太好了。 您必须在以下城市的每个港口办公室签到: 伯利兹。 太子港。 圣约翰。 布里奇敦。 如果您错过任何一个城市或打破正确顺序, 将被取消资格\n在帆船赛期间, 港口办公室24小时开放。 敲门, 他们会让您进去。 ";
			link.l1 = "明白了。 ";
			link.l1.go = "Regata_Head_7";
		break;
		
		case "Regata_Head_7":
			dialog.text = "禁止更换船只或在中队中添加更多船只。 每个城市都会对此进行核实, 请留意。 ";
			link.l1 = "我会留意的。 通常谁被认为是获胜者, 我们能谈谈奖品吗? ";
			link.l1.go = "Regata_Head_8";
		break;
		
		case "Regata_Head_8":
			dialog.text = "帆船赛只有一个获胜者 --第一个到达皇家港的船长。 奖品非常丰厚。 获胜者将获得一大笔钱 --25万比索。 此外, 还将获得一套珍贵的礼物。 ";
			link.l1 = "所以, 失败者什么也得不到? ";
			link.l1.go = "Regata_Head_9";
		break;
		
		case "Regata_Head_9":
			dialog.text = "没错。 另外, 英国殖民地的许多富人和穷人都会对帆船赛的获胜者下注。 您也可以押注... 自己。 通常每个船长都会这样做。 如果您赢了, 会赚得更多, 别忘了这也是动力。 通常我接受赌注\n您要押注自己获胜吗? ";
			link.l1 = "哈! 当然, 我押。 我能押多少? ";
			link.l1.go = "Regata_rate";
			link.l2 = "我会考虑的。 也许会押注。 ";
			link.l2.go = "Regata_Head_10";
		break;
		
		case "Regata_Head_10":
			if (CheckAttribute(pchar, "questTemp.Regata.Begin"))
			{
				dialog.text = "如果您想的话就想想吧。 帆船赛开始前您还有些时间。 ";
				link.l1 = "好的。 什么时候开始? ";
				link.l1.go = "Regata_Head_11";
				DeleteAttribute(pchar, "questTemp.Regata.Rate");
				pchar.questTemp.Regata.Ratenext = "true";
			}
			else
			{
				dialog.text = "如果您想的话就想想吧。 帆船赛开始前您还有些时间。 ";
				link.l1 = "好的。 ";
				link.l1.go = "exit";
			}
		break;
		
		case "Regata_Head_11":
			CreateRegataAdversaries();
			dialog.text = "三天后, 中午12点。 到码头来, 别迟到。 您将有五名竞争对手。 \n"+pchar.questTemp.Regata.AdversaryName.a+", 驾驶"+pchar.questTemp.Regata.AdversaryShipName.a+"号\n"+pchar.questTemp.Regata.AdversaryName.b+", 驾驶"+pchar.questTemp.Regata.AdversaryShipName.b+"号\n"+pchar.questTemp.Regata.AdversaryName.c+", 驾驶"+pchar.questTemp.Regata.AdversaryShipName.c+"号\n"+pchar.questTemp.Regata.AdversaryName.d+", 驾驶"+pchar.questTemp.Regata.AdversaryShipName.d+"号\n"+pchar.questTemp.Regata.AdversaryName.e+", 驾驶"+pchar.questTemp.Regata.AdversaryShipName.e+"号\n他们都是经验丰富的船长。 好了, 大概就是这样。 以防万一, 拿上规则文件。 起跑线上见! ";
			link.l1 = "再见, 先生。 ";
			if (Pchar.BaseNation == SPAIN || Pchar.BaseNation == HOLLAND) link.l1.go = "Regata_Head_13";
			else link.l1.go = "Regata_Head_12";
		break;
		
		case "Regata_Head_12":
			DialogExit();
			pchar.quest.RegataToPortRoyalTimeOver.over = "yes";//移除计时器
			SetFunctionTimerCondition("Regata_SetTime", 0, 0, 3, false);
			pchar.quest.Regata_Lost.win_condition.l1 = "Timer";
			pchar.quest.Regata_Lost.win_condition.l1.date.hour  = 13.0;
			pchar.quest.Regata_Lost.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 3);
			pchar.quest.Regata_Lost.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 3);
			pchar.quest.Regata_Lost.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 3);
			pchar.quest.Regata_Lost.function = "Regata_Lost";
			pchar.quest.Regata_Start.win_condition.l1 = "Timer";
			pchar.quest.Regata_Start.win_condition.l1.date.hour  = 12.0;
			pchar.quest.Regata_Start.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 3);
			pchar.quest.Regata_Start.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 3);
			pchar.quest.Regata_Start.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 3);
			pchar.quest.Regata_Start.win_condition.l2 = "locator";
			pchar.quest.Regata_Start.win_condition.l2.location = "Portroyal_town";
			pchar.quest.Regata_Start.win_condition.l2.locator_group = "reload";
			pchar.quest.Regata_Start.win_condition.l2.locator = "reload1_back";
			pchar.quest.Regata_Start.function = "Regata_Start";
			AddQuestRecordInfo("RegataRules", "1");
			NextDiag.CurrentNode = "Regata_Prepare";
			DeleteAttribute(pchar, "questTemp.Regata.Begin");
			pchar.questTemp.Regata.Prepare = "true";
			AddQuestRecord("Regata", "2");
		break;
		
		case "Regata_Head_13":
			dialog.text = "等等! 我给您30天访问英国和法国港口的许可证。 帆船赛不会超过一个月。 请收下。 ";
			link.l1 = "谢谢! ";
			link.l1.go = "Regata_Head_12";
			GiveNationLicence(HOLLAND, 30);
		break;
		
		case "Regata_rate":
			dialog.text = "您要押注多少? ";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "Regata_rate_1";
			link.l2 = "我想, 我还需要一些时间考虑。 ";
			link.l2.go = "Regata_Head_10";
		break;
		
		case "Regata_rate_1":
			int iQty = sti(dialogEditStrings[4]);
			pchar.questTemp.Regata.Rate = sti(iQty);
			if (iQty < 10000)
			{
				dialog.text = "先生, 这可不是开玩笑。 我不会处理这么小的金额。 ";
				link.l1 = "抱歉... 让我们重新考虑赌注。 ";
				link.l1.go = "Regata_rate";
				break;
			}
			if (iQty > 100000)
			{
				dialog.text = "先生, 根据帆船赛规则, 我不能接受这么高的赌注。 请降低到合理金额。 ";
				link.l1 = "太遗憾了。 让我们重新考虑金额。 ";
				link.l1.go = "Regata_rate";
				break;
			}
			dialog.text = ""+iQty+"? 这是个不错的赌注。 我准备接受。 先生, 请给钱? ";
			if (makeint(Pchar.money) >= sti(pchar.questTemp.Regata.Rate))
			{
				link.l1 = "请收下。 ";
				link.l1.go = "Regata_rate_2";
			}
			link.l2 = "我现在没有足够的钱。 我稍后再来押注。 也许我会重新考虑金额。 ";
			link.l2.go = "Regata_Head_10";
		break;
		
		case "Regata_rate_2":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Regata.Rate));
			pchar.questTemp.Regata.Advantage = sti(pchar.questTemp.Regata.Rate)*(1.5+frand(1.5)); // dlc
			dialog.text = "太好了! 现在您需要做的就是成为第一个到达的人, 奖金就是您的了。 最终价值可能会有所不同, 这取决于最后有多少人押注您。 ";
			if (!CheckAttribute(pchar, "questTemp.Regata.Ratenext"))
			{
				link.l1 = "我明白了。 帆船赛什么时候开始? ";
				link.l1.go = "Regata_Head_11";
			}
			else
			{
				link.l1 = "我明白了。 我会等待开始。 再见! ";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.Regata.Ratenext");
				NextDiag.TempNode = "Regata_Prepare";
			}
		break;
		
		case "Regata_Prepare":
			dialog.text = "啊, 又是您, " +GetFullName(pchar)+ "船长? 您想要什么? ";
			if (!CheckAttribute(pchar, "questTemp.Regata.Rate"))
			{
				link.l1 = "我想押注自己获胜。 ";
				link.l1.go = "Regata_rate";
			}
			link.l2 = "不, 没什么。 只是想问候您。 ";
			link.l2.go = "exit";
			NextDiag.TempNode = "Regata_Prepare";
		break;
		
		//帆船赛开始
		case "Regata_CitMan":
			dialog.text = RandPhraseSimple(LinkRandPhrase("船长, 您是第一次参加吗? 让我告诉您, 您应该小心。 您的竞争对手可能会给您设下一些非常不愉快的惊喜... ","船长, 我已经押注您了。 别让我失望! ","船长, 帆船赛港口的当地人可能会向您出售一些东西。 通常很有用。 考虑一下。 "), LinkRandPhrase("一路顺风, 船长! ","船长, 请小心, 卡斯蒂利亚人经常在西班牙水域猎杀参赛者的小帆船。 ","我听说一些可疑人物经常向帆船赛船长提供他们的'服务'。 接受与否由您决定。 "));
			link.l1 = "是的, 是的, 当然... 谢谢, 我想。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_CitMan";
		break;
		
		case "Regata_CitWom":
			dialog.text = LinkRandPhrase("船长, 我和我丈夫押了一万比索赌您获胜。 别让我们失望! 我会为您祈祷! ","船长! 祝您好运! ","嗯... 您真是一位勇敢无畏的船长... ");
			link.l1 = "... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_CitWom";
		break;
		
		case "Regata_CitHorse":
			dialog.text = LinkRandPhrase("嘿, 水手! 向美女挥手! 我会等您回来! ","嘿, 航海老手! 夫人说她会把我作为奖品免费送给帆船赛的获胜者... 努力赢吧, 你真帅! ","回来时别忘了拜访我们, 帅哥, 我们会以最高标准为您服务! ");
			link.l1 = "嗯, 哈... 我会考虑的, 谢谢! ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_CitHorse";
		break;
		
		case "Regata_Prepare_1":
			if (sti(environment.time) < 12.0)
			{
				dialog.text = "船长, 帆船赛12点开始。 您现在可以休息, 我们正在准备庆祝活动。 中午回来, 您的竞争对手也会到场。 ";
				link.l1 = "很好, 先生! 我会等待开始... ";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "您来了, 船长。 ";
				link.l1 = "我和我的船员准备好了, 先生! 我在等待开始... ";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Regata_Prepare_1";
		break;
		
		case "Regata_Start":
			dialog.text = "那么, 先生们, 我们到了。 我宣布帆船赛开始。 你们知道规则。 第一个回到这里的人将被誉为获胜者。 女士们, 先生们, 让我们为我们勇敢的船长们祝好运! \n先生们! 你们准备好了吗? 预备! 开始! ";
			link.l1 = "... ";
			link.l1.go = "Regata_Start_1";
		break;
		
		case "Regata_Start_1":
			DialogExit();
			PlaySound("people fight\mushketshot.wav");
			log_info("帆船赛已经开始! 上船! 前往伯利兹! ");
			for (i=1; i <=5; i++)
			{
				sld = characterFromId("Regata_Cap_F"+i);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
			}
			Island_SetReloadEnableGlobal("Jamaica", false);//不能去岛上
			SetFunctionTimerCondition("ReturnJamaicaNorm", 0, 0, 1, false);//返回正常的计时器
			LocatorReloadEnterDisable("Portroyal_town", "reload1_back", false);//打开出海通道
			DeleteAttribute(pchar, "questTemp.Regata.Prepare");
			pchar.questTemp.Regata.Go = "true";
			pchar.questTemp.Regata.Town = "Beliz";
			pchar.quest.Regata_PU.win_condition.l1 = "locator";
			pchar.quest.Regata_PU.win_condition.l1.location = "Beliz_town";
			pchar.quest.Regata_PU.win_condition.l1.locator_group = "reload";
			pchar.quest.Regata_PU.win_condition.l1.locator = "reload10_back";
			pchar.quest.Regata_PU.win_condition.l2 = "Night";
			pchar.quest.Regata_PU.function = "RegataPU_Open";//夜间进入港口
			//情况
			pchar.quest.Regata_ShYarder.win_condition.l1 = "location";
			pchar.quest.Regata_ShYarder.win_condition.l1.location = "Beliz_town";
			pchar.quest.Regata_ShYarder.function = "RegataShipyarder";
			sld = characterFromId("Beliz_shipyarder");
			LAi_RemoveLoginTime(sld);
			AddQuestRecord("Regata", "3");
		break;
		//帆船赛开始
		
		//船帆制造商
		case "Regata_Shipyarder":
			dialog.text = "问候您, 船长! 我得知您正在参加加勒比帆船赛。 ";
			link.l1 = "没错。 消息在群岛传播得比风还快。 ";
			link.l1.go = "Regata_Shipyarder_1";
		break;
		
		case "Regata_Shipyarder_1":
			dialog.text = "确实如此, 船长。 我有个提议给您。 与您的船和帆船赛有关。 ";
			link.l1 = "呵! 有趣。 我听着呢, 先生。 ";
			link.l1.go = "Regata_Shipyarder_2";
		break;
		
		case "Regata_Shipyarder_2":
			dialog.text = "我有一套适合小帆船的完美船帆, 由最好的棉花制成。 这些船帆将提高您的船的加速度, 让您在时间上比对手更有优势\n我准备把它们卖给您, 也就是说, 如果您想买的话。 ";
			link.l1 = "这些船帆您要多少钱? ";
			link.l1.go = "Regata_Shipyarder_3";
		break;
		
		case "Regata_Shipyarder_3":
			dialog.text = "只要15000比索。 您必须承认, 对于这种情况来说, 这是一个非常适中的价格。 ";
			if (makeint(Pchar.money) >= 15000)
			{
				link.l1 = "我同意。 我为我的小帆船购买这些新船帆。 给您钱, 先生。 我签到时请您费心把它们送到我的船上。 ";
				link.l1.go = "Regata_Shipyarder_4";
			}
			link.l2 = "我没有这么多钱。 所以无法购买您的船帆。 ";
			link.l2.go = "Regata_Shipyarder_exit";
		break;
		
		case "Regata_Shipyarder_4":
			AddMoneyToCharacter(pchar, -15000);
			dialog.text = "会办妥的, 先生。 我的人正等着指令, 我向您保证, 您不会后悔的。 此外, 这些船帆是漂亮的蓝色。 您的美人会喜欢的。 ";
			link.l1 = "好的! 那么, 我得走了, 您处理船帆吧。 ";
			link.l1.go = "Shipyarder_exit";
			for (i=1; i <=5; i++)
			{
				if (i==1) sTemp = "a";
				if (i==2) sTemp = "b";
				if (i==3) sTemp = "c";
				if (i==4) sTemp = "d";
				if (i==5) sTemp = "e";
				pchar.questTemp.Regata.AdversarySecondTransition.Time.(sTemp) = sti(pchar.questTemp.Regata.AdversarySecondTransition.Time.(sTemp))+12;//从所有人那里赢得12小时
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversarySecondTransition.Time.(sTemp)));
			}
			RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails = 3;
			SetSailsColor(Pchar, 5);
			AddQuestRecord("Regata", "28");
		break;
		
		case "Regata_Shipyarder_exit":
			dialog.text = "真遗憾。 好吧, 这是您的选择。 再见, 船长。 ";
			link.l1 = "再见! ";
			link.l1.go = "Shipyarder_exit";
			pchar.questTemp.Regata.AdversarySecondTransition.Time.d = sti(pchar.questTemp.Regata.AdversarySecondTransition.Time.d)-16;//第四个对手赢得16小时
			log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversarySecondTransition.Time.e));
			AddQuestRecord("Regata", "29");
		break;
		
		case "Shipyarder_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload5_back", "Beliz_Shipyard", "sit", "sit1", "ReturnRegataSYNorm", 5);
		break;
		//船帆制造商
		
		//走私者与加农炮
		case "Regata_Contra":
			dialog.text = "您好, " +GetFullName(pchar)+ "船长。 我们得和您谈谈... 实际上这只是一个... 商业提议。 ";
			link.l1 = "嗯。 有趣, 您怎么知道我是谁? ";
			link.l1.go = "Regata_Contra_1";
		break;
		
		case "Regata_Contra_1":
			dialog.text = "我能说什么呢, 他们总说我有天赋... 哈哈, 好吧, 帆船赛正如火如荼, 您正在参加, 您是著名的船长! ";
			link.l1 = "我明白了。 那么, 说吧。 ";
			link.l1.go = "Regata_Contra_2";
		break;
		
		case "Regata_Contra_2":
			if (sti(pchar.questTemp.Regata.Index != 1))
			{
				sTemp = pchar.questTemp.Regata.ContraIndex;
				dialog.text = "我们知道有一个参赛者在您前面 - " + pchar.questTemp.Regata.AdversaryName.(sTemp) + ", 驾驶" + pchar.questTemp.Regata.AdversaryShipName.(sTemp) + "号。 他不久前离开港口, 很快就会经过戈纳夫角。 ";
			}
			else
			{
				dialog.text = "我们知道有一个参赛者就在您后面 - " + pchar.questTemp.Regata.AdversaryName.b + ", 驾驶" + pchar.questTemp.Regata.AdversaryShipName.b + "号。 他几小时后就会到这里。 ";
			}
			link.l1 = "嗯... 你们消息很灵通。 ";
			link.l1.go = "Regata_Contra_3";
		break;
		
		case "Regata_Contra_3":
			if (sti(pchar.questTemp.Regata.Index != 1)) sTemp = "让您超过他并取代他的位置";
			else sTemp = "因此您将长期领先";
			dialog.text = "完全正确。 现在让我们切入正题。 我们为您提供帮助, 换取您的钱。 我们在戈纳夫湾后面的海角放置了四门来自我们船上的加农炮。 任何帆船赛船只都必须绕过它\n加农炮装有链弹。 如果我们达成协议, 我会告诉我们的加农炮手朋友弄坏您竞争对手的船帆, 这样他将被迫花费时间修理, " + sTemp + "。 ";
			link.l1 = "这项服务您要多少钱? ";
			link.l1.go = "Regata_Contra_4";
			link.l2 = "不。 我不会用这种方法获胜。 你们看错我了。 再见, 先生们。 ";
			link.l2.go = "Regata_Contra_exit";
		break;
		
		case "Regata_Contra_exit":
			dialog.text = "好吧, 船长, 这是您的选择。 再见。 ";
			link.l1 = "感谢您关于海角的信息。 我会远离那里。 ";
			link.l1.go = "Contra_exit";
			AddQuestRecord("Regata", "31");
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
		break;
		
		case "Regata_Contra_4":
			if (sti(pchar.questTemp.Regata.Index != 1)) iTemp = 50000;
			else iTemp = 30000;
			dialog.text = "不多。 只要" + iTemp + "比索。 您的一个竞争对手将因... 意外而损失近两天时间, 哈哈! ";
			if (makeint(Pchar.money) >= iTemp)
			{
				link.l1 = "呵! 你说话有道理, 朋友! 我付钱。 但我有什么保证您会履行职责? 以及您不会在我经过海角时向我的船开炮? ";
				link.l1.go = "Regata_Contra_5";
			}
			link.l2 = "我没有这么多钱。 所以无法使用您的服务。 ";
			link.l2.go = "Regata_Contra_exit";
		break;
		
		case "Regata_Contra_5":
			dialog.text = "船长, 拜托, 我们是走私者, 不是海盗。 我们都是诚实的人... 以我们的方式。 您以前一定用过我们的服务, 对吧? 我向您保证。 您可以信赖。 ";
			link.l1 = "说得好, 好吧, 拿钱。 ";
			link.l1.go = "Regata_Contra_6";
		break;
		
		case "Regata_Contra_6":
			AddQuestRecord("Regata", "30");
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
			dialog.text = "您会对这笔交易满意的, 船长。 我会立即让我的炮手们知道。 祝您好运! ";
			link.l1 = "你也一样... ";
			link.l1.go = "Contra_exit";
			if (sti(pchar.questTemp.Regata.Index != 1))
			{
				AddMoneyToCharacter(pchar, -50000);
				sTemp = pchar.questTemp.Regata.ContraIndex;
				pchar.questTemp.Regata.AdversaryThirdTransition.Time.(sTemp) = sti(pchar.questTemp.Regata.AdversaryThirdTransition.Time.(sTemp))+48;//延迟48小时
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversaryThirdTransition.Time.(sTemp)));
			}
			else
			{
				AddMoneyToCharacter(pchar, -30000);
				pchar.questTemp.Regata.AdversaryThirdTransition.Time.b = sti(pchar.questTemp.Regata.AdversaryThirdTransition.Time.b)+36;//延迟36小时
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversaryThirdTransition.Time.b));
			}
		break;
		
		case "Contra_exit":
			DialogExit();
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("RegataContra_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "quest", "quest2", "none", "", "", "", 10.0);
			}
		break;
		//走私者与加农炮
		
		//神父
		case "Regata_Padre":
			pchar.questTemp.Regata.BranderName = GenerateRandomNameToShip(ENGLAND);
			dialog.text = "日安, 我的孩子。 我想问候您, 并谦卑地问您: 您想作为英格兰和我们伟大主的忠实仆人向教区金库捐款吗? ";
			link.l1 = "神父, 人们做慈善是因为灵魂的召唤, 而不是因为强迫。 我开始认为群岛上的每个人都决定抢劫帆船赛的船长们... ";
			link.l1.go = "Regata_Padre_exit";
			link.l2 = "当然, 神父。 多少合适? ";
			link.l2.go = "Regata_Padre_1";
		break;
		
		case "Regata_Padre_1":
			dialog.text = "只要您的愿望和能力允许, 我的孩子。 我们教区即使是最小的金额也会很高兴。 ";
			Link.l1.edit = 4;			
			link.l1 = "";
			link.l1.go = "Regata_Padre_2";
		break;
		
		case "Regata_Padre_2":
			iTemp = sti(dialogEditStrings[4]);
			if (iTemp <= 0 || sti(pchar.money) < iTemp)
			{
				dialog.text = "这种态度是错误的, 我的孩子。 我们都有罪, 别忘了你的灵魂。 你将不得不出现在我们的造物主面前... 也许很快。 ";
				link.l1 = "我不需要您的说教, 神父。 再会。 ";
				link.l1.go = "Padre_exit";
				ChangeCharacterComplexReputation(pchar, "nobility", -3);
				AddQuestRecord("Regata", "35");
				break;
			}
			if (iTemp > 0 && iTemp <= 1000)//什么也不说
			{
				dialog.text = "我们教区和我感谢您的这份微薄礼物。 ";
				link.l1 = "不客气, 神父。 ";
				link.l1.go = "Padre_exit";
				AddMoneyToCharacter(pchar, -iTemp);
				AddQuestRecord("Regata", "35");
			}
			if (iTemp > 1000 && iTemp <= 5000)//第一类 - 不暗示
			{
				dialog.text = "我们教区和我感谢您的这份礼物。 我想警告您, 我的孩子, 有些罪恶的人打算伤害您。 在海上要小心! ";
				link.l1 = "神父, 每天都有人计划对我做些什么... 但感谢您对我命运的关心。 ";
				link.l1.go = "Padre_exit";
				AddMoneyToCharacter(pchar, -iTemp);
				AddQuestRecord("Regata", "34");
				AddQuestUserData("Regata", "sMoney", iTemp);
			}
			if (iTemp > 5000 && iTemp <= 10000)//第二类 - 会说
			{
				dialog.text = "我以我们教区的名义感谢您的这份珍贵礼物。 作为回报, 我想警告您, 一些非常坏的人正在密谋对付您。 我听说这些邪恶的叛徒打算在这个港口击沉您的船\n他们已经为此准备了一艘装满火药的船。 小心, 我的孩子, 这些迷失的灵魂对他们的邪恶意图是认真的... 愿上帝保佑您! ";
				link.l1 = "谢谢, 神父。 我会留意的。 ";
				link.l1.go = "Padre_exit";
				AddMoneyToCharacter(pchar, -iTemp);
				AddQuestRecord("Regata", "33");
				AddQuestUserData("Regata", "sMoney", iTemp);
			}
			if (iTemp > 10000)//第三类 - 完全告诉
			{
				dialog.text = "您非常慷慨, 我的孩子。 上帝谦卑仆人的谦逊不允许我接受您愿意为我们教堂的利益捐赠的全部金额。 我只拿10000比索\n作为回报, 我想警告您, 坏人正在密谋对付您。 我听说这些邪恶的叛徒打算就在这个港口击沉您的船\n他们准备了一艘名为‘" + pchar.questTemp.Regata.BranderName + "’的装满火药的小帆船, 她悬挂英国国旗以便毫无怀疑地接近您。 小心, 我的孩子, 这些迷失的灵魂对他们的邪恶意图是认真的\n摧毁他们, 我为这个罪给予您赦免。 上帝保佑您! 我会为您祈祷, 我的孩子。 ";
				link.l1 = "谢谢, 神父。 如果这些混蛋敢做坏事, 我会把他们直接送进地狱! ";
				link.l1.go = "Padre_exit";
				AddMoneyToCharacter(pchar, -10000);
				ChangeCharacterComplexReputation(pchar, "nobility", 2);
				AddQuestRecord("Regata", "32");
				AddQuestUserData("Regata", "sText", pchar.questTemp.Regata.BranderName);
			}
		break;
		
		case "Regata_Padre_exit":
			dialog.text = "别生气, 我的孩子。 愤怒是一种罪。 您有权不做慈善。 平安地走吧, 我的孩子。 ";
			link.l1 = "再会, 神父。 ";
			link.l1.go = "Padre_exit";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddQuestRecord("Regata", "35");					  
		break;
		
		case "Padre_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload7_back", "SentJons_church", "barmen", "stay", "ReturnRegataPadreNorm", 5);
		break;
		
		case "Regata_Spyglass":
			dialog.text = "日安, 船长! 我叫" + npchar.name+ ", 我想... ";
			link.l1 = "... 想给我提供什么... 对吗, 小姐? ";
			link.l1.go = "Regata_Spyglass_1";
		break;
		
		case "Regata_Spyglass_1":
			dialog.text = "当然, 船长! 您为什么这么惊讶? 您是个英俊的水手, 又在参加帆船赛, 当然每个人都想卖给您一些有用的航海用品。 ";
			link.l1 = "好吧, 美女, 你说得有道理。 你有什么给我? ";
			link.l1.go = "Regata_Spyglass_2";
		break;
		
		case "Regata_Spyglass_2":
			if(hrand(11) > 10)//出色的望远镜
			{
				pchar.questTemp.Regata.Spy = "spyglass4";
				sTemp = "一副出色的望远镜";
				pchar.questTemp.Regata.SpyPrice = 20000;
				pchar.questTemp.Regata.SpyIndex = 12;//获胜 - 12小时
			}
			else
			{
				if(hrand(11) < 6)//普通的望远镜
				{
					pchar.questTemp.Regata.Spy = "spyglass2";
					sTemp = "一副普通的望远镜";
					pchar.questTemp.Regata.SpyPrice = 1800;
					pchar.questTemp.Regata.SpyIndex = 4;//获胜 - 4小时
				}
				else//好的望远镜 - 如何有用
				{
					pchar.questTemp.Regata.Spy = "spyglass3";
					sTemp = "一副好的望远镜";
					pchar.questTemp.Regata.SpyPrice = 10000;
					pchar.questTemp.Regata.SpyIndex = 8;//获胜 - 8小时
				}
			}
			dialog.text = "看这里。 这是我从父亲那里继承的。 他也像您一样是名水手, 有很多航海用品。 我不需要它, 但您肯定会觉得有用。 我只要" + FindRussianMoneyString(sti(pchar.questTemp.Regata.SpyPrice)) + "比索。 ";
			if (sti(pchar.money) >= sti(pchar.questTemp.Regata.SpyPrice))
			{
				link.l1 = "嗯, 嗯... " + sTemp + "! 有趣! 我说, 我从你这里买了。 为了你美丽的眼睛。 那么, 你要" + FindRussianMoneyString(sti(pchar.questTemp.Regata.SpyPrice)) + "比索? 请收钱。 ";
				link.l1.go = "Regata_Spyglass_3";
			}
			link.l2 = "嗯... " + sTemp + "? 不, 姑娘, 抱歉, 我不需要。 我自己已经有一副很好的望远镜了。 所以... 唉! ";
			link.l2.go = "Regata_Spyglass_exit";
		break;
		
		case "Regata_Spyglass_3":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Regata.SpyPrice));
			GiveItem2Character(pchar, pchar.questTemp.Regata.Spy);
			dialog.text = "谢谢, 船长。 希望它对您有用。 我很高兴您觉得它有用。 帆船赛好运! ";
			link.l1 = "谢谢你, " + npchar.name+ "! 再会。 ";
			link.l1.go = "Spyglass_exit";
			for (i=1; i <=5; i++)
			{
				if (i==1) sTemp = "a";
				if (i==2) sTemp = "b";
				if (i==3) sTemp = "c";
				if (i==4) sTemp = "d";
				if (i==5) sTemp = "e";
				pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp) = sti(pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp))+sti(pchar.questTemp.Regata.SpyIndex);//买了望远镜 - 赢得时间
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp)));
			}
		break;
		
		case "Regata_Spyglass_exit":
			dialog.text = "真遗憾, 船长。 我本希望它对您有用。 好吧, 我会试着卖给别人。 再会! ";
			link.l1 = "再见, " + npchar.name+ "。 ";
			link.l1.go = "Spyglass_exit";
			pchar.questTemp.Regata.AdversaryFourthTransition.Time.c = sti(pchar.questTemp.Regata.AdversaryFourthTransition.Time.c)-sti(pchar.questTemp.Regata.SpyIndex);//第三个对手赢得时间
		break;
		
		case "Spyglass_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10);
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		case "Regata_SiegeOfficer":
			dialog.text = "问候您, 船长。 您不是帆船赛的参赛者吗? 我说得对吗? ";
			link.l1 = "是的。 怎么了, 军官? ";
			link.l1.go = "Regata_SiegeOfficer_1";
		break;
		
		case "Regata_SiegeOfficer_1":
			dialog.text = "您一定已经知道我们的殖民地正处于西班牙的围攻之下。 因此我们的总督想和您谈谈。 您能赏光拜访他吗? 现在事情非常紧急。 ";
			link.l1 = "嗯... 好吧, 我马上就去见总督阁下, 尽管我不太明白我怎么会卷入军事行动。 ";
			link.l1.go = "Regata_SiegeOfficer_2";
		break;
		
		case "Regata_SiegeOfficer_2":
			dialog.text = "您被卷入了, 船长。 我们不要浪费时间, 去官邸吧。 跟我来。 ";
			link.l1.go = "Regata_SiegeOfficer_3";
		break;
		
		case "Regata_SiegeOfficer_3":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "Bridgetown_townhall", "goto", "governor1", "RegataSiegeHover", -1);
		break;
		
		case "Regata_SiegeOfficer_4":
			dialog.text = "先生! 我准备把平民派到您的船上。 我们现在走吗? ";
			link.l1 = "是的, 当然。 我们立即起航。 告诉人们上长艇。 ";
			link.l1.go = "Regata_SiegeOfficer_5";
		break;
		
		case "Regata_SiegeOfficer_5":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "RegataSiegeOpen", -1);
			for (i=1; i <=9; i++)
			{
				sld = characterFromId("RegataBridgWom_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "quest", "quest1", "none", "", "", "", 30);
			}
		break;
		
		case "Regata_SiegeOfficer_6":
			dialog.text = "我们做到了... 看来这艘小帆船是中队的侦察船, 这些卡斯蒂利亚混蛋正在附近侦察。 船长, 请帮我把妇女们带到洞穴里, 可能还有更多的西班牙分队。 ";
			link.l1 = "好的。 走吧! ";
			link.l1.go = "Regata_SiegeOfficer_7";
		break;
		
		case "Regata_SiegeOfficer_7":
			DialogExit();
			sld = characterFromId("SiegeOfficer");
			LAi_ActorFollowEverywhere(sld, "", -1);
			pchar.quest.Regata_Siege3.win_condition.l1 = "location";
			pchar.quest.Regata_Siege3.win_condition.l1.location = "Barbados_cave";
			pchar.quest.Regata_Siege3.function = "RegataBarbadosCave";
		break;
		
		case "Regata_SiegeOfficer_8":
			dialog.text = "感谢您的帮助, 船长! 如果不是您和您的勇气... 您是真正的英雄, 您不顾所有危险和自身利益完成了这次行动。 我一直在想如何奖励您... 有一个提高您在帆船赛中胜算的方法。 ";
			link.l1 = "有趣。 是什么方法? ";
			link.l1.go = "Regata_skiper";
		break;
		
		case "Regata_Hovernor":
			dialog.text = "问候您, " +GetFullName(pchar)+ "船长。 您来真是太好了。 我们的城镇需要您的帮助。 ";
			link.l1 = "先生, 如果您说的是现在正在进攻您殖民地的西班牙中队, 那我不知道我能帮上什么忙。 我指挥的是小帆船, 不是战列舰... ";
			link.l1.go = "Regata_Hovernor_1";
		break;
		
		case "Regata_Hovernor_1":
			dialog.text = "听我说, 船长, 您会明白的。 我们处境艰难。 城市被西班牙围困。 与堡垒的决战即将开始。 此外, 几百名西班牙人已经登陆并封锁了城市的每个出口, 现在他们可以从海上和陆地攻击我们\n堡垒的驻军正在准备保卫城市免受中队攻击, 而定居点本身的士兵不足。 每个能使用武器的人都被动员起来了, 但其他人呢? \n布里奇敦有数百名妇女。 您能想象如果我们未能保护我们的殖民地, 她们会发生什么吗? 我相信您明白。 ";
			link.l1 = "先生, 我理解您, 但是, 再说一次, 我能帮什么忙? 您想让我做什么? 与战列舰作战还是让我的船员加入城镇民兵? ";
			link.l1.go = "Regata_Hovernor_2";
		break;
		
		case "Regata_Hovernor_2":
			switch (sti(Pchar.BaseNation))
			{
				case ENGLAND: sTemp = "您是英格兰人, 帮助我们拯救英格兰公民, 重要的是 - 妇女! " break;
				case FRANCE: sTemp = "您是法国人, 所以您基本上是我们的盟友, 帮助我们拯救英格兰公民, 更重要的是 - 妇女! " break;
				case SPAIN: sTemp = "我知道您是西班牙人, 海上那些是您的同胞, 所以我知道我已经要求很多了, 但这些妇女是无辜的, 与这场战斗无关。 所以我恳求您, 帮助她们! " break;
				case HOLLAND: sTemp = "我知道您是荷兰人, 我们两国处于战争状态, 但您在英国旗下参加英国帆船赛。 您不认为为无辜和平的人们, 为妇女而战是正确的吗? 请船长, 帮助她们! " break;
			}
			dialog.text = "都不是。 我只请求您一件事。 用您的船把妇女和儿童带离这里。 人数不多, 大约一百人。 把她们和马奥尼中尉带到哈里森角, 他会确保她们在洞穴里安全\n我相信西班牙人不会搜查她们。 我没有船可派, 我们所有的船都被西班牙中队击沉了。 您是我最后的希望。 您可以一次航行把她们带到海角, 尽管您的船会超载。 战列舰不会追您\n我不能要求别人做这件事。 " + sTemp + "";
			link.l1 = "先生, 抱歉, 但我的船已经超载了, 即使两次航行也无法容纳那么多人。 任何随机的炮弹即使落在附近也会把我的船和您的妇女们送入海底。 原谅我, 我帮不了您。 ";
			link.l1.go = "Regata_Hovernor_exit";
			link.l2 = "很好, 先生。 我会帮助您。 水手的荣誉要求我这样做。 ";
			link.l2.go = "Regata_Hovernor_3";
		break;
		
		case "Regata_Hovernor_3":
			dialog.text = "我很高兴您同意了。 您是真正的战士。 马奥尼中尉会把妇女和儿童带到您的船上。 上帝保佑您, 船长! ";
			link.l1 = "谢谢您, 先生。 我们不要浪费时间! ";
			link.l1.go = "Regata_Hovernor_4";
		break;
		
		case "Regata_Hovernor_wait":
			dialog.text = "快点, 船长。 时间紧迫。 ";
			link.l1 = "我已经在航行了! ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_Hovernor_wait";
		break;
		
		case "Regata_Hovernor_exit":
			dialog.text = "难以置信。 您甚至不打算试试? 好吧, 您有权这样做。 我不能要求您什么。 如果您只是一个普通船长, 为了一百名妇女, 我会没收您的船, 但您正在参加帆船赛, 因此您受到英国殖民地总督的保护\n我曾希望您的良心会占上风, 但我错了。 走吧, 愿上帝怜悯您的灵魂! ";
			link.l1 = "再会, 先生。 ";
			link.l1.go = "Hovernor_exit";
		break;
		
		case "Hovernor_exit":
			DialogExit();
			pchar.quest.Regata_TH.over = "yes"; // belamour 移除中断
			pchar.questTemp.Regata.AdversaryFifthTransition.Time.e = sti(pchar.questTemp.Regata.AdversaryFifthTransition.Time.e)-36;//第五个对手赢得36小时
			ChangeCharacterComplexReputation(pchar, "nobility", -8);
			ChangeCharacterNationReputation(pchar, ENGLAND, -5);
			//将总督恢复正常
			npchar.Dialog.Filename = "Common_Mayor.c";
			npchar.dialog.currentnode = "First time";
			//删除中尉
			sld = characterFromId("SiegeOfficer");
			sld.lifeday = 0;
			//打开大门和出海通道
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Bridgetown_town", "reload1_back", false);
			LocatorReloadEnterDisable("Bridgetown_town", "reload2_back", false);
			LocatorReloadEnterDisable("Bridgetown_town", "gate1_back", false);
			LocatorReloadEnterDisable("Bridgetown_town", "gate_back", false);
			LocatorReloadEnterDisable("Bridgetown_Exittown", "reload3", false);
			//岛屿恢复正常
			n = FindIsland("Barbados");	
			DeleteAttribute(Islands[n], "DontSetShipInPort");
			//5天后解除围攻
			SetFunctionTimerCondition("RegataSiegeDelete", 0, 0, 5, false);
			for (i=1; i <=9; i++)//清除妇女
			{
				sld = characterFromId("RegataBridgWom_"+i);
				sld.lifeday = 0; // patch-7
				LAi_CharacterDisableDialog(sld);
			}
			AddQuestRecord("Regata", "38");
			AddQuestUserData("Regata", "sName", GetFullName(npchar));
		break;
		
		case "Regata_Hovernor_4":
			DialogExit();
			pchar.quest.Regata_TH.over = "yes"; // belamour 移除中断
			NextDiag.CurrentNode = "Regata_Hovernor_wait";
			sld = characterFromId("SiegeOfficer");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "Bridgetown_town", "goto", "goto4", "", 10);
			pchar.quest.Regata_evacuation.win_condition.l1 = "location";
			pchar.quest.Regata_evacuation.win_condition.l1.location = "Bridgetown_town";
			pchar.quest.Regata_evacuation.function = "RegataSiegeEvacuation";
			AddQuestRecord("Regata", "36");
			AddQuestUserData("Regata", "sName", GetFullName(npchar));
		break;
		
		case "Regata_BridgWom":
			dialog.text = "西班牙人在追我们! 上帝, 救救我们! ";
			link.l1 = "... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_BridgWom";
		break;
		
		case "Regata_BridgWom_1":
			dialog.text = "马奥尼中尉死了... 这一定是噩梦。 他是个勇敢的军官。 船长, 请您带我们去洞穴好吗? 把我们带到那里, 我们会自己照顾自己。 ";
			link.l1 = "当然。 跟我来! ";
			link.l1.go = "Regata_BridgWom_2";
		break;
		
		case "Regata_BridgWom_2":
			DialogExit();
			for (i=1; i <=9; i++)
			{
				sld = characterFromId("RegataBridgWom_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			pchar.quest.Regata_Siege3.win_condition.l1 = "location";
			pchar.quest.Regata_Siege3.win_condition.l1.location = "Barbados_cave";
			pchar.quest.Regata_Siege3.function = "RegataBarbadosCave";
		break;
		
		case "Regata_BridgWom_3":
			dialog.text = "我们到了... 谢谢您, 船长! 您刚刚救了我们所有人! 我一直在想如何奖励您... 有一个提高您在帆船赛中胜算的方法。 ";
			link.l1 = "请说。 ";
			link.l1.go = "Regata_skiper";
		break;
		
		case "Regata_skiper":
			pchar.questTemp.Regata.Name = GetFullName(npchar);
			dialog.text = "您要去皇家港吗? 最短路线经过库拉索。 返回布里奇敦。 找到一个叫伍德罗.多尔蒂的人, 他是一位老水手和经验丰富的航海家。 他非常了解巴巴多斯和牙买加之间的区域, 对您会有很大帮助\n这将为您节省大量关键时间, 您迫切需要这些时间来获胜。 在当地教堂找到这个人, 告诉他" + GetFullName(npchar) + "派您来的, 他不会拒绝。 带他去皇家港, 他本来就打算航行到那里。 ";
			link.l1 = "很好! 一位好航海家对我会很有用。 再会。 ";
			link.l1.go = "Regata_skiper_1";
		break;
		
		case "Regata_skiper_1":
			dialog.text = "再会, 船长! 祝您好运! ";
			link.l1 = "也许, 我们会再见面... ";
			link.l1.go = "Regata_skiper_2";
		break;
		
		case "Regata_skiper_2":
			DialogExit();
			AddQuestRecord("Regata", "37");
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			ChangeCharacterNationReputation(pchar, ENGLAND, 10);
			LAi_SetStayType(npchar);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0; // patch-8
			for (i=1; i <=9; i++)
			{
				sld = characterFromId("RegataBridgWom_"+i);
				LAi_SetStayType(sld);
				LAi_CharacterDisableDialog(sld);
				sld.lifeday = 0; // patch-8
			}
			//将总督恢复正常
			sld = characterFromId("Bridgetown_Mayor");
			sld.Dialog.Filename = "Common_Mayor.c";
			sld.dialog.currentnode = "First time";
			//打开大门和出海通道
			LocatorReloadEnterDisable("Shore4", "boat", false);
			LocatorReloadEnterDisable("Bridgetown_town", "gate1_back", false);
			LocatorReloadEnterDisable("Bridgetown_town", "gate_back", false);
			LocatorReloadEnterDisable("Bridgetown_Exittown", "reload3", false);
			LocatorReloadEnterDisable("Barbados_cave", "reload1", false);
			bQuestDisableMapEnter = false;
			//5天后解除围攻
			SetFunctionTimerCondition("RegataSiegeDelete", 0, 0, 5, false);
			RegataSiegeSkiper();//将伍德罗放在教堂
		break;
		
		case "Regata_SiegeSkiper":
			dialog.text = "日安。 需要什么吗? ";
			link.l1 = "您叫伍德罗.多尔蒂, 对吗? ";
			link.l1.go = "Regata_SiegeSkiper_1";
		break;
		
		case "Regata_SiegeSkiper_1":
			dialog.text = "对。 我能为您做什么? ";
			link.l1 = "我知道您是经验丰富的航海家, 非常了解巴巴多斯和库拉索之间的水域。 我还知道您想去皇家港。 我是帆船赛的参赛者, 最后一站是皇家港。 我想请您作为航海家加入我的船员, 完成最后这段航程。 ";
			link.l1.go = "Regata_SiegeSkiper_2";
		break;
		
		case "Regata_SiegeSkiper_2":
			dialog.text = "有趣... 您为什么认为我会加入您的船员? ";
			link.l1 = "嗯, 因为我从" + pchar.questTemp.Regata.Name + "那里听说了您, 他保证您不会拒绝。 而且因为我在这个关键时刻帮助了布里奇敦... ";
			link.l1.go = "Regata_SiegeSkiper_3";
		break;
		
		case "Regata_SiegeSkiper_3"://这里 - 看情况
			if(hrand(2) != 2)
			{
				dialog.text = "从" + pchar.questTemp.Regata.Name + "那里? 我现在明白了, 当然。 好吧, 船长, 我会帮助您走最短路线到皇家港。 您现在起航吗? ";
				link.l1 = "是的。 ";
				link.l1.go = "Regata_SiegeSkiper_4";
			}
			else
			{
				dialog.text = "" + pchar.questTemp.Regata.Name + "? 我知道了。 但是, 船长, 我不能在这么危险的时候离开我的城市。 您必须理解我, 作为一名士兵, 您为我们提供了无私的帮助\n我不想让人们在背后议论老伍德罗在与西班牙的最后决战中逃跑。 我会留下。 请不要介意, 船长。 ";
				link.l1 = "这是您的最终决定吗? 但我帮助了您的殖民地... ";
				link.l1.go = "Regata_SiegeSkiper_6";
			}
		break;
		
		case "Regata_SiegeSkiper_4":
			dialog.text = "那我们不要浪费时间。 让我收拾一下东西, 就听您安排。 ";
			link.l1 = "我的水手会在码头等您, 把您送到‘圣凯瑟琳’号。 谢谢您, 伍德罗! ";
			link.l1.go = "SiegeSkiper_hire";
		break;
		
		case "Regata_SiegeSkiper_6":
			dialog.text = "船长, 帆船赛是运动, 而西班牙对我家乡的围攻是生活。 我不会跟您去任何地方。 我再说一遍, 您必须理解我 --荣誉和责任在这个世界上仍然有意义。 这是我的最终决定, 不会改变\n不过, 我可以给您一个建议, 如何以最快的时间通过最安全的路线到达那里, 向西北驶向多米尼加, 然后前往马提尼克或瓜德罗普, 由您和风向决定。 然后直接驶向皇家港, 或者您可以经过库拉索, 我不推荐, 但如果您和荷兰人关系好, 当然可以。 ";
			link.l1 = "好吧, 谢谢... 但我很失望。 再会, 伍德罗。 ";
			link.l1.go = "SiegeSkiper_exit";
		break;
		
		case "SiegeSkiper_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
		break;
		
		case "SiegeSkiper_hire":
			chrDisableReloadToLocation = true;//关闭地点
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 10.0);
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.OfficerWantToGo.DontGo = true; //不要尝试离开
			npchar.loyality = 25;
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			//重新计算第五阶段时间
			for (i=1; i <=5; i++)
			{
				if (i==1) sTemp = "a";
				if (i==2) sTemp = "b";
				if (i==3) sTemp = "c";
				if (i==4) sTemp = "d";
				if (i==5) sTemp = "e";
				pchar.questTemp.Regata.AdversaryFifthTransition.Time.(sTemp) = sti(pchar.questTemp.Regata.AdversaryFifthTransition.Time.(sTemp))+18+(rand(18));//赢得最多1.5天
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp)));
			}
			SetFunctionTimerCondition("SiegeSkiperOver", 0, 0, 15, false);//以免任命军官
			DialogExit();
		break;
		
		case "Regata_Finish":
		iTest = FindColony("Portroyal"); 
		if (iTest != -1)
		{
			rColony = GetColonyByIndex(iTest);
			sFrom_sea = rColony.from_sea;
		}
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//检查港口是否有船
		{
			//移除限制
			bQuestDisableMapEnter = false;//打开地图
			DeleteAttribute(pchar, "GenQuest.CannotWait");//可以加速时间
			bool bRegLugger = sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_LUGGER || sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_CAREERLUGGER;
			if (CheckAttribute(pchar, "questTemp.Regata.Breach") || !CheckAttribute(pchar, "questTemp.Regata.Bridgetown") || GetCompanionQuantity(pchar) > 1 || !bRegLugger || pchar.Ship.Name != "Saint Catherine")
			{
				dialog.text = "您在最后阶段违反了帆船赛规则。 您的成绩被取消资格。 我没什么可告诉您的了, 船长。 ";
				link.l1 = "呃... 真该死! 好吧, 没什么可做的了, 您太仔细了。 再会! ";
				link.l1.go = "exit";
				npchar.lifeday = 1;
				DeleteAttribute(pchar, "questTemp.Regata");
				AddQuestRecord("Regata", "45");
				CloseQuestHeader("Regata");
			}
			else
			{
				n=1;
				for (i=1; i <=5; i++)
				{
					if (i==1) sTemp = "a";
					if (i==2) sTemp = "b";
					if (i==3) sTemp = "c";
					if (i==4) sTemp = "d";
					if (i==5) sTemp = "e";
					if (pchar.questTemp.Regata.AdversaryFifthTransition.Time.(sTemp) < sti(pchar.questTemp.Regata.FifthTransitionTime)) n++;
					pchar.questTemp.Regata.Result = n;//帆船赛名次
				}
				if (n==1)
				{
					dialog.text = GetFullName(pchar) + "船长, 恭喜您! 您用了" + sti(pchar.questTemp.Regata.FifthTransitionTime) + "小时完成帆船赛, 将所有对手远远甩在后面。 这是一个非凡的成绩! ";
					link.l1 = "感谢您的美言, 先生! ";
					link.l1.go = "First_result";
				}
				else
				{
					if (n==6)
					{
						dialog.text = "船长, 遗憾的是您的成绩最差, 您用了" + sti(pchar.questTemp.Regata.FifthTransitionTime) + "小时。 别难过, 您的对手确实很强。 ";
						link.l1 = "我不难过, 先生。 我很高兴参加了帆船赛并尝试了我的技能。 ";
						link.l1.go = "Other_result";
						AddQuestRecord("Regata", "44");
						CloseQuestHeader("Regata");
					}
					else
					{
          				dialog.text = "船长, 您获得了第" + n + "名。 恭喜您取得成功, 您展示了值得称赞的时间 - " + sti(pchar.questTemp.Regata.FifthTransitionTime) + "小时。 虽败犹荣! ";
						link.l1 = "没关系, 先生。 我很高兴在这场激烈的比赛中取得了不错的成绩。 ";
						link.l1.go = "Other_result";
						if (n==2) AddQuestRecord("Regata", "40");
						if (n==3) AddQuestRecord("Regata", "41");
						if (n==4) AddQuestRecord("Regata", "42");
						if (n==5) AddQuestRecord("Regata", "43");
						CloseQuestHeader("Regata");
					}
				}
			}
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex("SiegeSkiper");
			sld = &Characters[sti(Pchar.questTemp.FiringOfficerIDX)];
			CheckForReleaseOfficer(sti(Pchar.questTemp.FiringOfficerIDX));
			RemovePassenger(Pchar, sld);
			DeleteAttribute(sld, "Payment");
			DeleteAttribute(Pchar, "questTemp.FiringOfficerIDX");//从军官中删除
			log_info("伍德罗.多尔蒂已上岸");
			pchar.quest.SiegeSkiperOver.over = "yes"; //移除计时器
		}
		else
		{
			dialog.text = "先生, 我问您一件事 - 您的船在哪里? 我没看到... ";
			link.l1 = "抱歉, 先生。 我马上把她开到港口。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_Finish";
		}
		break;
		
		case "First_result":
			if (CheckAttribute(pchar, "questTemp.Regata.Rate")) sTemp = "明天来我办公室, 我会给您赌注的奖金。 ";
			else sTemp = "如果您像我建议的那样押注自己获胜, 您还会得到额外奖金。 ";
			dialog.text = "明天拜访总督, 他会给您25万比索和珍贵的礼物。 " + sTemp + " 不要离开城镇, 根据传统, 如果获胜者一周内不领取奖金, 奖金将归入城镇金库。 ";
			link.l1 = "我知道了, 先生! 我明天去拜访他! ";
			link.l1.go = "First_result_1";
		break;
		
		case "First_result_1":
			DialogExit();
			//npchar.lifeday = 7;
			Achievment_Set("ach_09");
			npchar.dialog.currentnode = "Other_result_repeat";
			pchar.questTemp.Regata.Win = "true";
			pchar.quest.Regata_Final.win_condition.l1 = "Timer";
			pchar.quest.Regata_Final.win_condition.l1.date.hour  = 6.0;
			pchar.quest.Regata_Final.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Regata_Final.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Regata_Final.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Regata_Final.function = "RegataFinal";
			SetFunctionTimerCondition("RegataFinalOver", 0, 0, 8, false);//不移除计时器 - 8天后自动清理
			// 传闻
			AddSimpleRumour("啊, 您就是传奇船长, 帆船赛的获胜者! 亲眼见到您真是荣幸! ", ENGLAND, 60, 10);
			AddSimpleRumour("哈, 看啊, 风浪大师, 帆船赛的获胜者! 我敬佩您... ", ENGLAND, 60, 10);
			AddSimpleRumour("哦, 伟大的水手, 风浪之王, 帆船赛的获胜者来到了我们的城市! 我们很高兴见到您, 船长! ", ENGLAND, 60, 10);
			AddSimpleRumour("哦, 是的, 我很幸运能和一位活着的传奇聊天, 那位即使逆风也能在三天内穿越群岛的船长! 向您致敬, 船长! ", ENGLAND, 60, 10);
			AddSimpleRumour("啊, 所以您就是传奇船长, 帆船赛的获胜者! 很高兴见到您! ", FRANCE, 60, 10);
			AddSimpleRumour("哈, 您不是风浪大师, 帆船赛的获胜者吗! 我敬佩您... ", FRANCE, 60, 10);
			AddSimpleRumour("哦, 伟大的水手, 风浪之王, 帆船赛的获胜者来到了我们的城市! 我们很高兴见到您, 船长! ", FRANCE, 60, 10);
			AddSimpleRumour("哦, 是的, 我很幸运能和一位活着的传奇聊天, 那位即使逆风也能在三天内穿越群岛的船长! 向您致敬, 船长! ", FRANCE, 60, 10);
			// 经验
			AddComplexSeaExpToScill(2000, 300, 300, 0, 500, 500, 0);
			AddCharacterExpToSkill(pchar, "Leadership", 2000);//领导力
			AddCharacterExpToSkill(pchar, "Fortune", 1000);//运气
			AddCharacterExpToSkill(pchar, "Sneak", 300);//潜行
			ChangeCharacterComplexReputation(pchar, "authority", 10);
			ChangeCharacterComplexReputation(pchar, "fame", 15);
			ChangeOfficersLoyality("good_all", 3);
			AddQuestRecord("Regata", "39");
			CloseQuestHeader("Regata");
		break;
		
		case "Other_result":
			dialog.text = "很高兴听到您的可敬回应。 祝您好运, 船长! ";
			link.l1 = "再会, 先生。 ";
			link.l1.go = "Other_result_1";
		break;
		
		case "Other_result_1":
			DialogExit();
			npchar.dialog.currentnode = "Other_result_repeat";
			SetFunctionTimerCondition("RegataFinalOver", 0, 0, 1, false);
			// 经验
			AddComplexSeaExpToScill(500, 100, 100, 0, 100, 100, 0);
			AddCharacterExpToSkill(pchar, "Leadership", 200);//领导力
			AddCharacterExpToSkill(pchar, "Fortune", 100);//运气
			AddCharacterExpToSkill(pchar, "Sneak", 100);//潜行
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		case "Other_result_repeat":
			dialog.text = "还有别的事吗, 船长? ";
			link.l1 = "不... 没什么。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Other_result_repeat";
		break;
		
		case "Give_advantage":
			dialog.text = "啊, 您来了, " +GetFullName(pchar)+ "先生。 很高兴见到您。 您来拿奖金吗? 已经为您准备好了。 ";
			link.l1 = "很高兴听到! 我的额外奖金是多少? ";
			link.l1.go = "Give_advantage_1";
		break;
		
		case "Give_advantage_1":
			dialog.text = "考虑到所有赌注, 您的最终奖金是" + FindRussianMoneyString(makeint(pchar.questTemp.Regata.Advantage)) + "。 请拿好。 恭喜! ";
			link.l1 = "谢谢! ";
			link.l1.go = "Give_advantage_2";
		break;
		
		case "Give_advantage_2":
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.Regata.Advantage));
			dialog.text = "当然, 您在皇家港市民中的声望提高了。 我想您能看到... 但遗憾的是, 人们的记忆是短暂的。 所以趁荣耀还未褪去, 尽情享受吧! ";
			link.l1 = "您说得真好, 先生... 好吧, 让我们看看沐浴在荣耀中是什么感觉。 再会! 很荣幸。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Other_result_repeat";
		break;
		
		case "Regata_CitMan_1":
			if (CheckAttribute(pchar, "questTemp.Regata"))
			{
				if (CheckAttribute(pchar, "questTemp.Regata.Result"))
				{
					if (sti(pchar.questTemp.Regata.Result) == 1)
					{
						dialog.text = "恭喜您的胜利, 船长! 出色的成绩! ";
						link.l1 = "谢谢! ";
						link.l1.go = "exit";
					}
					else
					{
						dialog.text = "别难过, 船长。 赢得帆船赛并不容易, 甚至参加都是一种荣幸! ";
						link.l1 = "别担心我。 我对我的成绩很满意。 ";
						link.l1.go = "exit";
					}
				}
				else
				{
					dialog.text = "很高兴见到您, 船长! 您应该通过与史蒂文森先生交谈来登记自己。 ";
					link.l1 = "我知道了。 我这就去找他! ";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "啊, 船长, 您怎么会失败, 而且是在最后阶段! ";
				link.l1 = "是的, 我真蠢... ";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Regata_CitMan_1";
		break;
		
		case "Regata_CitWom_1":
			if (CheckAttribute(pchar, "questTemp.Regata"))
			{
				if (CheckAttribute(pchar, "questTemp.Regata.Result"))
				{
					if (sti(pchar.questTemp.Regata.Result) == 1)
					{
						dialog.text = "恭喜您的胜利, 船长! 出色的成绩! ";
						link.l1 = "谢谢您! ";
						link.l1.go = "exit";
					}
					else
					{
						dialog.text = "别难过, 船长。 赢得帆船赛并不容易, 甚至参加都是一种荣幸! ";
						link.l1 = "别担心我。 我对我的成绩很满意。 ";
						link.l1.go = "exit";
					}
				}
				else
				{
					dialog.text = "很高兴见到您, 船长! 您应该通过与史蒂文森先生交谈来登记自己。 ";
					link.l1 = "我知道了。 我这就去! ";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "啊, 船长, 您怎么会失败, 而且是在最后阶段! ";
				link.l1 = "是的, 我真蠢... ";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Regata_CitWom_1";
		break;
		
		case "Regata_CitHorse_1":
			if (CheckAttribute(pchar, "questTemp.Regata"))
			{
				if (CheckAttribute(pchar, "questTemp.Regata.Result"))
				{
					if (sti(pchar.questTemp.Regata.Result) == 1)
					{
						dialog.text = "恭喜您的胜利, 船长! 出色的成绩! ";
						link.l1 = "谢谢您! ";
						link.l1.go = "exit";
					}
					else
					{
						dialog.text = "别难过, 船长。 赢得帆船赛并不容易, 甚至参加都是一种荣幸! ";
						link.l1 = "别担心我。 我对我的成绩很满意。 ";
						link.l1.go = "exit";
					}
				}
				else
				{
					dialog.text = "很高兴见到您, 船长! 您应该通过与史蒂文森先生交谈来登记自己。 ";
					link.l1 = "我知道了。 我这就去! ";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "啊, 船长, 您怎么会失败, 而且是在最后阶段! ";
				link.l1 = "是的, 我真蠢... ";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Regata_CitHorse_1";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

void CreateRegataAdversaries()
{
	string sTemp;
	for (int i=0; i<=4; i++)
	{
	if (i==0) sTemp = "a";
	if (i==1) sTemp = "b";
	if (i==2) sTemp = "c";
	if (i==3) sTemp = "d";
	if (i==4) sTemp = "e";
	pchar.questTemp.Regata.AdversaryName.(sTemp) = GenerateRandomName_Generator(i, "man");
	pchar.questTemp.Regata.AdversaryShipName.(sTemp) = GenerateRandomNameToShip(ENGLAND);
	pchar.questTemp.Regata.AdversarySpeed.(sTemp) = 0.4+frand(0.9);
	log_testinfo(FindRussianDaysString(stf(pchar.questTemp.Regata.AdversarySpeed.(sTemp))));
	}
}
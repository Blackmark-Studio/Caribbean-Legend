void ProcessDialogEvent()
{
	ref NPChar, her;
	aref Link, NextDiag;
	bool bOk = false;
    bool bOk2;
    
	int Sum, nRel, nDay, iChurchQuest2_Summ;
	ref sld;
	
	// 教堂任务 #2 -->
	if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1") && !CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Summ_To_Contra"))
	{
		iChurchQuest2_Summ = sti(PChar.rank)*100 + (rand(3)+1)*100;
		PChar.GenQuest.ChurchQuest_2.Summ_To_Contra = sti(iChurchQuest2_Summ);
	}
	// <—— 教堂任务 #2
	
	string sColony;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
    string iDay, iMonth;
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;

	// belamour legendary edition
	bool MCGovernon = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE;
	bool MCAdmiral = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation);

	if (!CheckAttribute(npchar, "quest.trade_date"))
    {
        npchar.quest.trade_date = "";
    }

	//长时间后删除属性 (navy fix)
	if (CheckAttribute(pchar, "GenQuest.contraTravel.days") && GetQuestPastDayParam("contraTravel") > sti(PChar.GenQuest.contraTravel.days))
	{
		DeleteAttribute(pchar, "GenQuest.contraTravel");
		CloseQuestHeader("Gen_ContrabandTravel");
	}

	switch(Dialog.CurrentNode)
	{
        case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Smuggling_exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			PlaceSmugglersOnShore(Pchar.quest.contraband.CurrentPlace);
			Pchar.quest.Contraband.active = true;
			pchar.GenQuest.Contraband.GuardNation = npchar.nation;
			pchar.GenQuest.Contraband.SmugglerId  = npchar.id;				
			SetAllContraGoods(&Stores[sti(Pchar.GenQuest.Contraband.StoreIdx)], npchar);
			ReOpenQuestHeader("Gen_Contraband");
            if (GetIslandByCityName(npchar.city) == "Mein")
            {
            	AddQuestRecord("Gen_Contraband", "t1_1");
            }
            else
            {
	            AddQuestRecord("Gen_Contraband", "t1");
				if (Pchar.quest.contraband.CurrentPlace == "shore30" || Pchar.quest.contraband.CurrentPlace == "shore31")
				{
					AddQuestUserData("Gen_Contraband", "sIsland", "Marie Galante");
				}
				if (Pchar.quest.contraband.CurrentPlace == "shore59")
				{
					AddQuestUserData("Gen_Contraband", "sIsland", "Tobago");
				}
				AddQuestUserData("Gen_Contraband", "sIsland", XI_ConvertString(GetIslandByCityName(npchar.city)));
			}
			AddQuestUserData("Gen_Contraband", "sLoc", GetConvertStr(Pchar.quest.contraband.CurrentPlace, "LocLables.txt"));
				
			DialogExit();
		break;
		
		case "First time":											
			//--> Jason 如果正在进行查理任务的第一部分
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
            {
				dialog.text = "先生, 离开这个地方。 我怀疑我们没什么可谈的。 ";
				link.l1 = "哦, 真的吗? 你不喜欢我的脸吗? 好吧, 我走... ";
				link.l1.go = "exit";
				break;
			}
			//<—— 正在进行查理任务的第一部分
			//--> Addon-2016 Jason 封锁走私以避免与任务冲突
			if (CheckAttribute(pchar, "GenQuest.SmugglersBlock") && pchar.GenQuest.SmugglersBlock == npchar.location)
            {
				dialog.text = "今天不做生意。 ";
				link.l1 = "我明白了。 ";
				link.l1.go = "exit";
				break;
			}
			//--> 圣慈悲修道院检查团到来
			if (CheckAttribute(npchar, "quest.SantaMisericordia"))
			{
				dialog.text = "我和我的朋友们今天非常忙。 ";
				link.l1 = "但我需要... ";
				link.l1.go = "SantaMisericordia_1";
				break;
			}
			//<—— 圣慈悲修道院检查团到来
			//--> Jason 消耗品的价格
			if (CheckAttribute(pchar, "questTemp.Consumption.Contra"))
            {
				dialog.text = "你想要什么, 船长? ";
				link.l1 = "我们能谈谈吗? ";
				link.l1.go = "Consumption";
				break;
			}
			//<—— 消耗品的价格
			
			if(NPChar.quest.meeting == "0")
			{
				Dialog.Text = "你想要什么, 船长? 我不认识你, 也不能告诉你我的名字。 ";
				Link.l1 = "我是" +GetFullName(pchar)+ "船长。 ";
				Link.l1.go = "meeting";
				NPChar.quest.meeting = "1"; 
			}
			else
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour") && GetQuestPastDayParam("GenQuest.CaptainComission.GetRumour") < 1)
				{
					if(!CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakContra"))
					{
						pchar.GenQuest.CaptainComission.SpeakContra = true;
						dialog.text = "今天不做生意。 每个海湾都有巡逻队, 我们的总督在找一批货物, 被某个" + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")) + "船长" + pchar.GenQuest.CaptainComission.Name + "没收了, 他把货物藏在某个地方。 ";
						link.l1 = "那这个" + pchar.GenQuest.CaptainComission.Name + "船长在哪里? ";
						link.l1.go = "CapComission_1";
						break;
					}
					else
					{
						dialog.text = "今天不做生意。 ";
						link.l1 = "我明白了。 ";
						link.l1.go = "exit";					
						break;
					}
				}

				if(pchar.questTemp.Slavetrader == "FindMayak" && Islands[GetCharacterCurrentIsland(pchar)].id == pchar.questTemp.Slavetrader.EsIsland)
				{
					dialog.text = "今天不做生意。 ";
					link.l1 = "我明白了。 ";
					link.l1.go = "exit";
					break;
				}
				
				if(npchar.id == "Bridgetown_Smuggler" && CheckAttribute(pchar, "questTemp.BM_BlockSmuggler"))
				{
					dialog.text = "今天不做生意。 ";
					link.l1 = "我明白了。 ";
					link.l1.go = "exit";
					break;
				}

				Dialog.Text = "你想要什么, 船长? ";
				if (LAi_group_GetPlayerAlarm() > 0)
				{
	       			Dialog.Text = RandPhraseSimple("快点, " + GetSexPhrase("伙计","姑娘") + ", 你想要什么? 他们在追你! ", "说出你的事, 快点! 士兵在追你, 我们时间不多... ");
				}
				// belamour legendary edition
				bOk2 = MCGovernon || MCAdmiral;
				if(FindContrabandGoods(PChar) != -1 && !bOk2)
				{
					Link.l1 = "我想买卖点东西。 ";
					Link.l1.go = "Meeting_3";
				}

				if (CheckAttribute(pchar, "GenQuest.contraTravel.active") && sti(pchar.GenQuest.contraTravel.active) == true)
					Link.l2 = "关于旅行... ";
				else
					Link.l2 = "我需要去一个地方。 ";
				Link.l2.go = "Travel";
				if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakSmuggler"))
				{
					if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
					{
						link.l3 = "我有个'特殊'的东西, 我想你会感兴趣。 看看! ";
						link.l3.go = "SM_ShipLetters_1";
					}	
				}				

				//Jason --> 不公平竞争迷你任务
				if(CheckAttribute(PChar, "questTemp.Shadowtrader.seeksmugglers") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_tavern")
				{
					Link.l8 = "我有个不寻常的生意给你。 ";
					Link.l8.go = "Shadowtrader_smugglers";
				}
				// <—— 不公平竞争迷你任务
				//--> 合法贸易
				if(CheckAttribute(PChar, "questTemp.TPZ_ContraInfo") && NPChar.location == "BasTer_tavern")
				{
					Link.l8 = "听着, 朋友, 我需要一批葡萄酒和朗姆酒。 越多越快。 ";
					Link.l8.go = "TPZ_smugglers_1";
				}
				// <—— 合法贸易
				//Jason --> 巴考特销售生成器
				if(NPChar.location == "Marigo_tavern" && CheckAttribute(PChar, "GenQuest.Bakaut") && !CheckAttribute(PChar, "GenQuest.Bakaut.Info"))
				{
					Link.l9 = "我需要见迈克尔.罗森克拉夫特。 我有他感兴趣的货物。 ";
					Link.l9.go = "bakaut";
				}
				// <—— 巴考特销售生成器
				
				// 教堂生成器 #2 -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
				{
					Link.l4 = "我需要弄清楚一些事, 伙计。 ";
					Link.l4.go = "Contra_GenQuest_Church_2_1";
				}
				
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_2") && NPChar.location == PChar.GenQuest.ChurchQuest_2.Contra_Colony + "_tavern")
				{
					Link.l5 = "你的一个同事和我来自" + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_2.QuestTown + "Gen") + "的好朋友说你知道些生意。 ";
					Link.l5.go = "Contra_GenQuest_Church_2_Contra2_1";
				}
				// <—— 教堂生成器 #2
				
				Link.l7 = "没什么。 再见。 ";
				Link.l7.go = "Exit";				
			}
		break;
		
		case "CapComission_1":
			if(pchar.GenQuest.CaptainComission.variant == "A2")
			{
				dialog.text = "还能在哪儿, 堡垒的地下室? 那个船长随时可能向当局透露藏匿处, 到时候我们就什么都没有了。 在这场骚动结束前, 别想任何生意。 ";
				link.l1 = "听着, 你了解这个岛的每一个角落。 你真的不知道" + pchar.GenQuest.CaptainComission.Name + "船长把藏匿处藏在哪儿吗? ";
				link.l1.go = "CapComission_4";
			}
			if(pchar.GenQuest.CaptainComission.variant == "A3")
			{
				dialog.text = "我猜在天堂吧。 他和他的船员被绞死了。 但死刑判决中没说那是艘海盗船。 ";
				link.l1 = "你为什么这么确定那是艘海盗船? ";
				link.l1.go = "CapComission_2";
			}	
		break;
		
		case "CapComission_2":
			dialog.text = "我们从岩石上观看了战斗。 通过望远镜, 我们看到船上升着海盗旗。 然后, 大约五个小时后, 我们看到黑暗中一道闪光, 像是火药室爆炸。 有足够的时间把货物搬到岸上。 ";
			link.l1 = "你不知道" + pchar.GenQuest.CaptainComission.Name + "船长的藏匿处在哪儿吗? 你了解这个岛的每一个角落。 ";
			link.l1.go = "CapComission_3";
		break;
		
		case "CapComission_3":
			dialog.text = "不知道。 我们也在找, 但不是为了讨总督开心... ";
			link.l1 = "我明白了... 。 祝你愉快。 ";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission2", "38");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShipTypeQuest", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen")));
		break;
		
		case "CapComission_4":
			dialog.text = "不知道。 我们也在找, 但不是为了讨总督开心... 呵呵";
			link.l1 = "我明白了... 祝你愉快。 ";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission2", "19");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); // belamour gen
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
		break;
				
		case "SM_ShipLetters_1":
			pchar.questTemp.different.GiveShipLetters.speakSmuggler = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "你为什么这么想? 我是个诚实的沿海贸易商。 去找别的买家吧。 ";
				link.l1 = "谢谢... ";
				link.l1.go = "exit";
			}
			else
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					dialog.text = "为什么不呢? 也许我会发现你的'货物'有用。 拿" + sti(pchar.questTemp.different.GiveShipLetters.price2) + "个硬币, 忘了它。 ";
					link.l1 = "不, 谢谢。 ";
					link.l1.go = "SM_ShipLetters_2";	
					link.l2 = "你猜对了, 我开始忘了! ";
					link.l2.go = "SM_ShipLetters_3";
				}
				else
				{
					if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
					{
						dialog.text = "正是! 我现在真的很好奇。 我想如果我付你" + sti(pchar.questTemp.different.GiveShipLetters.price3) + "个硬币, 你就不会在乎那些文件了。 ";
						link.l1 = "不, 谢谢。 ";
						link.l1.go = "SM_ShipLetters_2";
						link.l2 = "你说得对。 我已经忘了它们。 ";
						link.l2.go = "SM_ShipLetters_3";
					}
					if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
					{
						dialog.text = "现在, 这是抓住那个傲慢家伙的机会! 我真的真的很好奇。 看, 我付你" + sti(pchar.questTemp.different.GiveShipLetters.price4) + "金币, 你会完全忘记桌上的文件吗? ";
						link.l1 = "我不会。 ";
						link.l1.go = "SM_ShipLetters_2";
						link.l2 = "好, 成交! ";
						link.l2.go = "SM_ShipLetters_3";
					}
				}
			}
		break;
		
		case "SM_ShipLetters_2":
			dialog.text = "好吧, 好吧, 但别再树敌了。 ";
			link.l1 = "你也是! ";
			link.l1.go = "exit";
		break;
		
		case "SM_ShipLetters_3":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2)); 
				}
				else
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price3)); 
				}
			}
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2)); 
				}
				else
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price4)); 
				}
			}
						
			if((sti(pchar.questTemp.different.GiveShipLetters.variant) == 0) || (sti(pchar.questTemp.different.GiveShipLetters.variant) == 2))
			{	
				ChangeCharacterComplexReputation(pchar,"nobility", -1); 
				OfficersReaction("bad"); 
			}	
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //移除定时器 
			AddQuestRecord("GiveShipLetters", "7");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Meeting":
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour") && GetQuestPastDayParam("GenQuest.CaptainComission.GetRumour") < 2)
			{
				if(!CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakContra"))
				{
					pchar.GenQuest.CaptainComission.SpeakContra = true;
					dialog.text = "今天不做生意。 每个海湾都有巡逻队, 我们的总督在找一批货物, 被某个" + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")) + "船长" + pchar.GenQuest.CaptainComission.Name + "没收了, 他把货物藏在某个地方。 ";
					link.l1 = "那这个" + pchar.GenQuest.CaptainComission.Name + "船长在哪里? ";
					link.l1.go = "CapComission_1";
					break;
				}
				else
				{
					dialog.text = "今天不做生意。 ";
					link.l1 = "我明白了。 ";
					link.l1.go = "exit";					
					break;
				}
			}
			
			if(pchar.questTemp.Slavetrader == "FindMayak" && Islands[GetCharacterCurrentIsland(pchar)].id == pchar.questTemp.Slavetrader.EsIsland)
			{
				dialog.text = "今天不做生意。 ";
				link.l1 = "我明白了。 ";
				link.l1.go = "exit";
				break;
			}
			
			if(npchar.id == "Bridgetown_Smuggler" && CheckAttribute(pchar, "questTemp.BM_BlockSmuggler"))
			{
				dialog.text = "今天不做生意。 ";
				link.l1 = "我明白了。 ";
				link.l1.go = "exit";
				break;
			}
			
			Dialog.Text = "我能帮你什么, 船长? ";
			
			bOk2 = MCGovernon || MCAdmiral;
			if(FindContrabandGoods(PChar) != -1 && !bOk2)
			{
				Link.l1 = "我想买卖东西。 ";
				Link.l1.go = "Meeting_1";
			}
			
			Link.l2 = "我需要去一个地方。 ";
			Link.l2.go = "Travel";				
			
			//Jason --> 不公平竞争迷你任务
			if(CheckAttribute(PChar, "questTemp.Shadowtrader.seeksmugglers") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_tavern")
			{
				Link.l8 = "我有个很不寻常的生意给你。 ";
				Link.l8.go = "Shadowtrader_smugglers";
			}
			// <—— 不公平竞争迷你任务
			//--> 合法贸易
				if(CheckAttribute(PChar, "questTemp.TPZ_ContraInfo") && NPChar.location == "BasTer_tavern")
				{
					Link.l8 = "听着, 朋友, 我需要一批葡萄酒和朗姆酒。 越多越快。 ";
					Link.l8.go = "TPZ_smugglers_1";
				}
			// <—— 合法贸易
			//Jason --> 巴考特销售生成器
			if(NPChar.location == "Marigo_tavern" && CheckAttribute(PChar, "GenQuest.Bakaut") && !CheckAttribute(PChar, "GenQuest.Bakaut.Info"))
			{
				Link.l9 = "我需要见迈克尔.罗森克拉夫特。 我有他感兴趣的货物。 ";
				Link.l9.go = "bakaut";
			}
			// <—— 巴考特销售生成器
			
			// 教堂生成器 #2 -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
			{
				Link.l3 = "我需要弄清楚一些事, 伙计。 ";
				Link.l3.go = "Contra_GenQuest_Church_2_1";
			}
			
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_2") && NPChar.location == PChar.GenQuest.ChurchQuest_2.Contra_Colony + "_tavern")
			{
				Link.l3 = "你的一个同事和我来自" + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_2.QuestTown + "Gen") + "的好朋友说你知道些生意。 ";
				Link.l3.go = "Contra_GenQuest_Church_2_Contra2_1";
			}
			// <—— 教堂生成器 #2

			Link.l5 = "没什么。 再见。 ";
			Link.l5.go = "Exit";				
		break;

		// 教堂生成器 #2 -->
		case "Contra_GenQuest_Church_2_1":
			iChurchQuest2_Summ = PChar.GenQuest.ChurchQuest_2.Summ_To_Contra;
			dialog.text = "我不是你的伙计。 这可能会让你付出代价。 ";
				link.l1 = "嗯。 我需要知道一些不超过" + FindRussianMoneyString(iChurchQuest2_Summ) + "的事。 ";
				link.l1.go = "Contra_GenQuest_Church_2_2";
			break;
			
		case "Contra_GenQuest_Church_2_2":
			iChurchQuest2_Summ = PChar.GenQuest.ChurchQuest_2.Summ_To_Contra;
			if(sti(PChar.money) >= iChurchQuest2_Summ)
			{
				dialog.text = "把你的硬币给我。 要知道你花这么点钱买不到多少信息。 ";
				link.l1 = "看, 我错过了我的朋友。 我开会迟到了, 他们没等我... ";
				link.l1.go = "Contra_GenQuest_Church_2_3";
				AddMOneyToCharacter(PChar, -iChurchQuest2_Summ);
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1");
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.Summ_To_Contra");
			}
			else
			{
				dialog.text = "哈, 你没钱! 等你有钱了再来。 ";
				link.l1 = "确实, 正在办。 ";
				link.l1.go = "exit";
			}
			break;
			
		case "Contra_GenQuest_Church_2_3":
				dialog.text = "你为什么需要我? ";
				link.l1 = "他们不在城里, 也没有船。 这就是为什么我想: 也许你的某个生意伙伴帮了他们? ";
				link.l1.go = "Contra_GenQuest_Church_2_4";
			break;
			
		case "Contra_GenQuest_Church_2_4":
			sColony = QuestGetColony(PChar.GenQuest.ChurchQuest_2.QuestTown);
			dialog.text = "我明白了... 见过几个家伙, 他们说需要离开这个岛, 不在乎去哪里。 这种情况我们不问原因, 只问报酬。 我们有一趟去" + XI_ConvertString("Colony" + sColony + "Acc") + ", " + XI_ConvertString(locations[FindLocation(sColony + "_Town")].IslandID + "Dat") + "的航行。 如果我们就钱达成一致, 我们可以带你去那里。 ";
			link.l1 = "谢谢, 但我有自己的船。 ";
			link.l1.go = "exit";
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "8");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + sColony + "Acc"));
			AddQuestUserData(sQuestTitle, "sIsland", XI_ConvertString(locations[FindLocation(sColony + "_Town")].IslandID + "Voc"));
			PChar.GenQuest.ChurchQuest_2.AskContra_2 = true;
			PChar.GenQuest.ChurchQuest_2.Contra_Colony = sColony;
		break;
			
		case "Contra_GenQuest_Church_2_Contra2_1":
			dialog.text = "从未和你有过生意往来。 ";
			link.l1 = "我们可以弥补。 你不久前把我的朋友带到了这里。 我错过了和" + GetSexPhrase("他们","他们") + "的会面。 ";
			link.l1.go = "Contra_GenQuest_Church_2_Contra2_2";
		break;
			
		case "Contra_GenQuest_Church_2_Contra2_2":
			string sGenLocation = IslandGetLocationFromType(locations[FindLocation(PChar.GenQuest.ChurchQuest_2.Contra_Colony + "_Town")].IslandID, "Shore");
			PChar.GenQuest.ChurchQuest_2.QuestGangShore = sGenLocation;
			PChar.GenQuest.ChurchQuest_2.BanditsInShore = true;
			dialog.text = "嗯, 我们让他们在" + XI_ConvertString(sGenLocation + "Gen") + "上岸... 你知道, 他们最好是你的朋友, 否则我不建议你去打扰他们。 ";
			link.l1 = "谢谢你的关心, 但我装备精良, 而且很有魅力。 ";
			link.l1.go = "exit";
			SetFunctionLocationCondition("Church_GenQuest2_GenerateBandits", sGenLocation, false);
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "9");
			AddQuestUserData(sQuestTitle, "sShore", XI_ConvertString(sGenLocation + "Gen")); // belamour gen
			locations[FindLocation(sGenLocation)].DisableEncounters = true;
			SetFunctionTimerCondition("Church_GenQuest2_TimeIsLeft", 0, 0, 1, false);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_2");
		break;
		// <—— 教堂生成器 #2

		case "Meeting_1":
			Dialog.Text = "嗯... 这和我有什么关系? 你可能迷路了, 船长。 去商店吧, 在那里买或卖你想要的东西。 ";
			Link.l1 = "不, 我需要你。 ";
			Link.l1.go = "Meeting_2";				
			Link.l2 = "谢谢你的建议。 祝你愉快。 ";
			Link.l2.go = "exit";				
		break;

		case "Meeting_2":
			Dialog.Text = "为什么? ";
			Link.l1 = "也许你会对一些特殊货物感兴趣? 或者也许你有什么可以提供给我? "
			Link.l1.go = "Meeting_3";				
		break;

		case "Meeting_3":
			int iTmp = false;
			int iChIdx, i;

			// 寻找最低等级以上的同伴
			for (i=0; i<COMPANION_MAX; i++)
			{
				iChIdx = GetCompanionIndex(GetMainCharacter(), i);
				if (iChIdx>=0)
				{
					sld = GetCharacter(iChIdx);
            		if (GetCharacterShipClass(sld) < ((MOD_SKILL_ENEMY_RATE/5.0) + 1.5)) iTmp = true;
				}
			}
			
			if (iTmp)
			{
				dialog.text = NPCStringReactionRepeat("下次为什么不租一艘皇家军舰呢。 你的船从堡垒很容易被发现。 我们不会冒这个险。 下次乘一艘小船来。 ", 
					"要我重复吗? 找一艘更小的船, 然后我们再谈。 ", 
					"你真的那么愚蠢吗? 给自己找一艘纵帆船或双桅横帆船。 只有这样我们才有生意。 ",
					"哦, 真是个白痴... ", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("好吧, 我明白了。 ", 
					"我知道了, 我只是想说明一些事情。 ",
					"不, 不是白痴, 只是个吝啬鬼。 以为情况有变。 我会多租几艘小船... ", 
					"照照镜子... ", npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);	
				break;
			}
			bOk  = CheckAttribute(pchar, "GenQuest.contraTravel.active") && (sti(pchar.GenQuest.contraTravel.active) == true);
			bOk2 = CheckAttribute(Pchar, "quest.Contraband.Active") && (sti(Pchar.quest.Contraband.Active) == true);
			bool bOk3 = CheckAttribute(Pchar, "questTemp.pirateStartQuest") && (Pchar.questTemp.pirateStartQuest == "3");
			if (bOk)
			{
			    if (GetQuestPastDayParam("contraTravel") > sti(PChar.GenQuest.contraTravel.days))
				{  // 逾期
					DeleteAttribute(PChar, "GenQuest.contraTravel");
					CloseQuestHeader("Gen_ContrabandTravel");
					bOk = false;
				}
			}

//navy --> PGG
			if (CheckFreeServiceForNPC(NPChar, "Smugglers") != -1)
			{
				Dialog.Text = "抱歉, " + GetSexPhrase("伙计","姑娘") + ", 我们已经很忙了。 几天后再来。 ";
				Link.l1 = "太糟糕了... ";
				Link.l1.go = "Exit";		
				break;
			}
//navy <--

			if (bOk || bOk2 || bOk3)
			{
				Dialog.Text = "我们先完成当前的生意如何? ";
				Link.l1 = "我想你是对的。 ";
				Link.l1.go = "Exit";				
			}
			else
			{
                if (npchar.quest.trade_date != lastspeak_date)
    			{
                    npchar.quest.trade_date = lastspeak_date;
                    
                    if (ChangeContrabandRelation(pchar, 0) > 5)
                    {
                        Pchar.quest.contraband.CurrentPlace = SelectSmugglingLocation();
						Pchar.quest.contraband.City = NPChar.city;
                        if (Pchar.quest.contraband.CurrentPlace != "None")//boal修复
                        {
                            if (ChangeContrabandRelation(pchar, 0) >= 70)
                            {
                                Dialog.Text = "我知道我们可以和你做生意。 我们将在" + GetConvertStr(Pchar.quest.contraband.CurrentPlace, "LocLables.txt") + "等你。 ";
                            }
                            else
                            {
            				    Dialog.Text = "嗯... 也许我们可以帮你找个买家。 我们将在" + GetConvertStr(Pchar.quest.contraband.CurrentPlace, "LocLables.txt") + "等你。 ";
            				}
            				Link.l1 = "好的。 在那里见。 ";
            				Link.l1.go = "Smuggling_exit";
        				}
        				else
        				{   //boal修复
                            Dialog.Text = "今天不做生意。 明天来。 ";
            				Link.l1 = "好吧。 ";
            				Link.l1.go = "Exit";
        				}
    				}
    				else
    				{
                        Dialog.Text = "你真以为在那之后有人会想和你合作吗? 你最好庆幸我们没有派赏金猎人去找你。 ";
        				Link.l1 = "太糟糕了。 我没机会当走私者了。 ";
        				Link.l1.go = "Exit";
    				}
				}
				else
				{
                    Dialog.Text = "今天不做生意。 明天来。 ";
    				Link.l1 = "好吧。 ";
    				Link.l1.go = "Exit";
				}
			}
		break;
////////////////////////////////////////////////////////////////////////////////
//	海盗地铁
////////////////////////////////////////////////////////////////////////////////
		case "Travel":
//navy --> PGG
			if (CheckFreeServiceForNPC(NPChar, "Smugglers") != -1)
			{
				Dialog.Text = "抱歉, " + GetSexPhrase("伙计","姑娘") + ", 我们已经很忙了。 几天后再来。 ";
				Link.l1 = "太糟糕了。 ";
				Link.l1.go = "Exit";		
				break;
			}
//navy <--
			//如果主角没有船且没有同伴一切正常
			if (sti(pchar.ship.type) == SHIP_NOTUSED && GetCompanionQuantity(pchar) == 1 && GetPassengersQuantity(pchar) == 0)
			{
				//如果已经有信息
				if (CheckAttribute(pchar, "GenQuest.contraTravel.active") && sti(pchar.GenQuest.contraTravel.active) == true)
				{
					//已经支付
					if (CheckAttribute(pchar, "GenQuest.contraTravel.payed") && sti(pchar.GenQuest.contraTravel.payed) == true)
					{
						Dialog.Text = "我以为我们已经达成协议了? ";
						Link.l2 = "确实! ";
					}
					//未支付, 意味着可以在期限内支付
					else
					{
						if(GetQuestPastDayParam("contraTravel") == sti(PChar.GenQuest.contraTravel.days))
						{
							Dialog.Text = "你带钱了吗? ";
							Link.l1 = "是的。 ";
							Link.l1.go = "Travel_pay";
							Link.l3 = "我改变主意了... ";
							Link.l3.go = "Travel_abort";
							Link.l2 = "还没有。 ";
						}
						else
						{
                            if (GetQuestPastDayParam("contraTravel") < sti(PChar.GenQuest.contraTravel.days))
							{
								Dialog.Text = "我已经告诉你一切了。 ";
								Link.l2 = "没错。 ";
								Link.l1 = "我改变主意了... ";
								Link.l1.go = "Travel_abort";
							}
							else // 逾期
							{
							    Dialog.Text = "今天帮不了你。 两天后再来, 也许我们能为你准备些东西。 ";
								Link.l2 = "太糟糕了。 ";
								DeleteAttribute(PChar, "GenQuest.contraTravel");
								CloseQuestHeader("Gen_ContrabandTravel");
							}
						}
					}
				}
				//如果没有协议, 协商条件
				else
				{
					nRel = ChangeContrabandRelation(pchar, 0);
					//如果关系正常且统计值小于20, 继续工作... .
					if (nRel > 0 && Statistic_AddValue(PChar, "contr_TravelKill", 0) < 20)
					{
						//海湾... 
						pchar.GenQuest.contraTravel.CurrentPlace = SelectSmugglingLocation();
						aref arTmp; makearef(arTmp, pchar.GenQuest.contraTravel);
						SetSmugglersTravelDestination(arTmp);
						//多久送达
						pchar.GenQuest.contraTravel.price = (sti(PChar.rank)*250 + (100 - nRel)*10 + rand(30)*20) + sti(arTmp.destination.days)*100;
						
						//如果地铁活跃, 主角没有乘客, 今天没见过面, 有可用海湾, 且随机... 
						bOk = !bPauseContrabandMetro && CheckNPCQuestDate(npchar, "Travel_Talk") && 
							Pchar.GenQuest.contraTravel.CurrentPlace != "None" && rand(50) < nRel;
                        bOk2 = CheckAttribute(Pchar, "quest.Contraband.Active") && (sti(Pchar.quest.Contraband.Active) == true);
						if (bOk && !bOk2)
						{
							nDay = 1 + rand(3);
							SetNPCQuestDate(npchar, "Travel_Talk");
							SaveCurrentQuestDateParam("contraTravel");

							Dialog.Text = "好吧, 我们可以把你送到" + GetConvertStr(locations[FindLocation(pchar.GenQuest.contraTravel.destination.loc)].id, "LocLables.txt") + "附近的" +
								XI_ConvertString("Colony" + pchar.GenQuest.contraTravel.destination + "Gen") + ", 费用为" + pchar.GenQuest.contraTravel.price + "金币。 请在" +
								FindRussianDaysString(nDay) + "内带钱来。 船将在24小时后准时在" +
								GetConvertStr(locations[FindLocation(Pchar.GenQuest.contraTravel.CurrentPlace)].id, "LocLables.txt") + "等你。 ";

							pchar.GenQuest.contraTravel.days = nDay;
							Link.l1 = "对我来说可行。 ";
							Link.l1.go = "Travel_agree";
							Link.l2 = "不, 谢谢。 ";
						}
						else
						{
							Dialog.Text = "今天帮不了你。 两天后再来, 也许我们能为你准备些东西。 ";
							Link.l2 = "太糟糕了。 ";
						}
					}
					//不, 送你走
					else
					{
                        Dialog.Text = "你真以为在那之后有人会想和你合作吗? 你最好庆幸我们没有派赏金猎人去找你。 走开! ";
        				Link.l2 = "哼, 又不走运。 ";
					}

				}
			}
			//有船, 送你走... 
			else 
			{
				if(GetPassengersQuantity(pchar) != 0)
				{
					Dialog.Text = "不, 我们不会带你们所有人。 只带你们中的一个。 ";
					Link.l2 = RandSwear() + "反正我也不需要! ";
				}
				else
				{
					Dialog.Text = "你为什么不用自己的船? 不, 我们不会带你。 ";
					Link.l2 = "好吧, 随你便。 ";
				}
			}
			Link.l2.go = "Exit";
			break;

		//取消
		case "Travel_abort":
			ChangeContrabandRelation(pchar, -2);
			DeleteAttribute(PChar, "GenQuest.contraTravel");
			CloseQuestHeader("Gen_ContrabandTravel");
			Dialog.Text = "随你便。 ";
			Link.l1 = "";
			Link.l1.go = "Exit";
			break;

		//主角同意出行
		case "Travel_agree":
			ReOpenQuestHeader("Gen_ContrabandTravel");
			AddQuestRecord("Gen_ContrabandTravel", "1");
			AddQuestUserData("Gen_ContrabandTravel", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Gen_ContrabandTravel", "sLoc", GetConvertStr(pchar.GenQuest.contraTravel.CurrentPlace, "LocLables.txt"));
			AddQuestUserData("Gen_ContrabandTravel", "sLocTo", GetConvertStr(pchar.GenQuest.contraTravel.destination.loc, "LocLables.txt"));
			AddQuestUserData("Gen_ContrabandTravel", "sPlaceTo", XI_ConvertString("Colony" + pchar.GenQuest.contraTravel.destination + "Gen"));
			AddQuestUserData("Gen_ContrabandTravel", "sDays", FindRussianDaysString(sti(pchar.GenQuest.contraTravel.days)));
			AddQuestUserData("Gen_ContrabandTravel", "sPrice", pchar.GenQuest.contraTravel.price);

			//激活任务
			pchar.GenQuest.contraTravel.active = true;
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			break;

		//主角同意支付
		case "Travel_pay":
			//钱够吗? 
			Sum = sti(pchar.GenQuest.contraTravel.price);
			if (sti(pchar.money) >= Sum)
			{
				AddMoneyToCharacter(pchar, -1*Sum);
				//设置支付标志
				pchar.GenQuest.contraTravel.payed = true;
				Dialog.Text = "很高兴和你做生意。 不要迟到。 ";
				Link.l1 = "我会尽量。 ";
				AddQuestRecord("Gen_ContrabandTravel", "2");
				AddQuestUserData("Gen_ContrabandTravel", "sSex", GetSexPhrase("",""));
				
				//设置走私者
				PlaceSmugglersOnShore(PChar.GenQuest.contraTravel.CurrentPlace);
				//船在海湾中... 
				Sum = sti(pchar.GenQuest.contraTravel.destination.days);
				sld = GetCharacter(NPC_GenerateCharacter("Abracham_Gray", "citiz_46", "man", "man", 5, PIRATE, Sum + 2, true, "hunter"));
				//复活... 
				sld.nation = PIRATE;
				SetRandomNameToCharacter(sld);
				SetMerchantShip(sld, rand(GOOD_PAPRIKA));
				SetFantomParamHunter(sld);
				SetCaptanModelByEncType(sld, "pirate");
				SetCharacterShipLocation(sld, PChar.GenQuest.contraTravel.CurrentPlace);

				SetTimerCondition("RemoveTravelSmugglers", 0, 0, 1, false);
			}
			//没有, 送你走... 
			else
			{
				Dialog.Text = "看来你钱不够。 "
				Link.l1 = "真遗憾, 我稍后再来。 ";
			}
			Link.l1.go = "Exit";
		break;  
////////////////////////////////////////////////////////////////////////////////
//	END OF海盗地铁
////////////////////////////////////////////////////////////////////////////////
				
		//Jason --> 不公平竞争迷你任务
		case "Shadowtrader_smugglers":
			dialog.text = "很有趣。 展示你有的东西。 ";
			link.l1 = "我听说有一家地下商店, 你可以用诱人的价格交易非常'特殊'的商品, 而且你帮助开了这家店。 我想和它的主人谈谈。 ";
			link.l1.go = "Shadowtrader_fail";
			link.l2 = "我听说有一家地下商店, 你可以用诱人的价格交易非常'特殊'的商品。 我几天后要航行, 在当地商店没有足够的钱买我需要的所有东西, 所以我需要也想节省一些硬币... 有人告诉我你可以帮助我。 ";
			link.l2.go = "Shadowtrader_smugglers_1";
			DeleteAttribute(pchar, "questTemp.Shadowtrader.seeksmugglers");
			DelLandQuestMark(npchar);
		break;
		
		case "Shadowtrader_fail":
			dialog.text = "你在说什么? 我不明白。 我们在这里没有开店, 这是胡说八道, 哈哈! 如果你想交易, 就带货物来, 我们用平常的方式谈... 开店, 哈! ";
			link.l1 = "嗯... ";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader = "true";
			AddQuestRecord("Shadowtrader", "3");
			CloseQuestHeader("Shadowtrader");
			DeleteAttribute(pchar, "questTemp.Shadowtrader_Block");
		break;
		
		case "Shadowtrader_smugglers_1":
			dialog.text = "想要折扣? 简单。 天黑时到港口主官的门口来。 我们的人会遇见你并带你去正确的地方。 ";
			link.l1 = "好的。 我会去那里! ";
			link.l1.go = "Shadowtrader_smugglers_2";		
		break;
		
		case "Shadowtrader_smugglers_2":
			pchar.questTemp.Shadowtrader.SeekTrader = "true";
			AddLandQuestMarkToPhantom("baster_prison", "basterJailOff");
			AddQuestRecord("Shadowtrader", "5");
			AddQuestUserData("Shadowtrader", "sCity", XI_ConvertString("Colony"+pchar.questTemp.Shadowtrader.City+"Gen"));
			SetFunctionTimerCondition("ShadowtraderTimeSmugglers_Over", 0, 0, 2, false);
			int iNation = pchar.questTemp.Shadowtrader.nation;
			int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+3;
			sld = GetCharacter(NPC_GenerateCharacter("ShadowAgent_1", "citiz_"+(rand(9)+41), "man", "man", iRank, iNation, 2, true, "quest"));
			SetFantomParamFromRank(sld, iRank, true);
			GiveItem2Character(sld, "blade_04");
			EquipCharacterbyItem(sld, "blade_04");
			LAi_SetCitizenType(sld);
			sld.dialog.Filename = "Common_citizen.c";
			sld.dialog.currentnode = "First time";	
			sld.greeting = "cit_common"; 
			sld.city = pchar.questTemp.Shadowtrader.City;
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, pchar.questTemp.Shadowtrader.City +"_town", "goto", "goto1");
			pchar.quest.Shadowtrader_SMG.win_condition.l1 = "locator";
			pchar.quest.Shadowtrader_SMG.win_condition.l1.location = pchar.questTemp.Shadowtrader.City + "_town";
			pchar.quest.Shadowtrader_SMG.win_condition.l1.locator_group = "reload";
			pchar.quest.Shadowtrader_SMG.win_condition.l1.locator = "reload10_back";
			pchar.quest.Shadowtrader_SMG.win_condition.l2 = "Night";
			pchar.quest.Shadowtrader_SMG.function = "ShadowAgent";
			DialogExit();
		break;
		// <—— 不公平竞争
		//--> 合法贸易
		case "TPZ_smugglers_1":
			dialog.text = "哈, 柜台后面的那个无赖派你来的, 不是吗? ";
			link.l1 = "这重要吗? 你能弄到吗, 还是我该找别人? ";
			link.l1.go = "TPZ_smugglers_2";
			DelLandQuestMark(npchar);
		break;
		
		case "TPZ_smugglers_2":
			dialog.text = "你想要什么我都能弄到, 明白吗? 只要报酬合适。 但那个该死的总督打击得很严。 我们不再碰酒了 --太吵了, 一英里外都能听到, 利润微薄, 被绞死的风险极高。 所以, 无意冒犯。 ";
			link.l1 = "嗯... 你说你什么都能弄到。 ";
			link.l1.go = "TPZ_smugglers_3";		
		break;
		
		case "TPZ_smugglers_3":
			dialog.text = "我能! 只是不想。 有这么个人, 就住在总督官邸旁边, 你信吗? 哈哈。 真是个傻瓜... 我刚才说什么来着? 哦, 对了。 他偷偷卖酒。 就在总督的假发底下, 哈哈。 问问他, 也许他能给你线索。 他的量很小, 真的是小打小闹, 但总比没有强。 ";
			link.l1 = "帮助不大, 但还是谢谢。 ";
			link.l1.go = "TPZ_smugglers_4";		
		break;
		
		case "TPZ_smugglers_4":
			DialogExit();
			AddQuestRecord("TPZ", "3");
			DeleteAttribute(pchar, "questTemp.TPZ_ContraInfo");
			
			// 引导到克里斯蒂安的家
			sld = GetCharacter(NPC_GenerateCharacter("TPZ_Kristian", "citiz_17", "man", "man", 1, FRANCE, -1, false, "quest"));
			sld.name = "Christian";
			sld.lastname = "Deluce";
			LAi_SetOwnerType(sld);
			sld.dialog.filename = "Quest\MiniEvents\TradingByLaw_dialog.c";
			sld.dialog.currentnode = "Kristian";
			ChangeCharacterAddressGroup(sld, "BasTer_houseF3", "barmen", "stay");
			sld.City = "BasTer";
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			AddLandQuestMark(sld, "questmarkmain");
		break;
		//<—— 合法贸易

		//--> 消耗品的价格
		case "Consumption":
			dialog.text = "这里有很多狂欢者, 如果你没有生意, 先生, 就喝酒或和他们聊聊。 这个地方很忙。 ";
			link.l1 = "再试一次。 我会为你的时间和我的好奇心付钱。 我需要答案。 ";
			link.l1.go = "Consumption_1";
		break;
		
		case "Consumption_1":
			if (sti(pchar.money) >= 3002)
			{
				dialog.text = "他会付钱, 哈! 我的时间不便宜, 先生, 要3000比索加上这杯被他们误称为朗姆酒的恶心饮料。 ";
				link.l1 = "成交! 现在告诉我关于你自己人里那个在当地监狱待了半年然后去世的人。 他发生了什么? ";
				link.l1.go = "Consumption_2";
			}
			else
			{
				dialog.text = "你最好在口袋里装满银币或金币, 那会更好。 然后再来谈, 我没时间和你免费聊天。 ";
				link.l1 = "... ";
				link.l1.go = "exit";
			}
		break;
		
		case "Consumption_2":
			AddMoneyToCharacter(pchar, -3002);
			dialog.text = "我记得, 虽然我不明白你为什么对这个感兴趣。 那孩子在那些铁栅栏后面真的发疯了。 他成了酒鬼, 总是说些胡话, 说什么消耗品把人带走了, 没人能幸免。 他说那消耗品有个名字, 甚至不敢大声说出来。 如果你说出来 --它就会来把你也带走。 ";
			link.l1 = "然后他发生了什么? ";
			link.l1.go = "Consumption_3";
		break;
		
		case "Consumption_3":
			dialog.text = "故事有个奇怪的结局, 长官。 起初, 当地人和水手喜欢他的故事, 但最终他们受够了。 任何寓言都是这样。 所以他们激怒他说出名字。 那家伙挣扎着反抗, 但无法忍受嘲笑, 几乎是哭着说出来的\n没人感觉到什么特别的, 蜡烛没有熄灭, 但第二天早上在酒馆后面发现那个可怜的灵魂死了, 喉咙被割开。 ";
			link.l1 = "我在这里没看到任何魔法。 告诉我名字。 ";
			link.l1.go = "Consumption_4";
		break;
		
		case "Consumption_4":
			dialog.text = "我记得那个名字, 但该死的, 我不会大声说出来。 这一切都有不祥之兆。 你没看出来吗? ";
			link.l1 = "嘿, 伙计, 你从我这里拿了一钱包硬币, 记得吗? 所以你能好心告诉我名字吗? ";
			link.l1.go = "Consumption_5";
		break;
		
		case "Consumption_5":
			dialog.text = "哦, 不会有好结果的, 先生, 相信我... (压低声音) 他说 --胡安... ";
			link.l1 = "去你的! 胡安? 这只是个普通名字, 在这里很流行。 为什么这么特别? ";
			link.l1.go = "Consumption_6";
		break;
		
		case "Consumption_6":
			dialog.text = "不知道, 但说这个名字的人被杀了。 相信我的直觉, 这个名字有很大问题。 这就是你想知道的全部吗? ";
			link.l1 = "我想是吧。 你可以自己买杯酒。 再见! ";
			link.l1.go = "Consumption_7";
		break;
		
		case "Consumption_7":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Consumption.Contra");
			pchar.questTemp.Consumption.AskJuan = 0;
			pchar.questTemp.Consumption = "current";
			AddQuestRecord("Consumption", "6");
		break;
		//<—— 消耗品的价格
		
		//Jason --> 巴考特销售生成器
		case "bakaut":
			dialog.text = "是这样吗? 好的。 罗森克拉夫特先生需要一批铁木, 但不少于" + FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value)) + "。 你有足够的货物吗? ";
			if (GetSquadronGoods(pchar, GOOD_SANDAL) >= sti(pchar.GenQuest.Bakaut.Value))
			{
				link.l1 = "我有。 我在哪里可以找到罗森克拉夫特先生? ";
				link.l1.go = "bakaut_1";
			}
			else
			{
				link.l1 = "嗯。 我现在没有那么多。 ";
				link.l1.go = "bakaut_no";
			}
		break;
		
		case "bakaut_no":
			dialog.text = "那就不要打扰罗森克拉夫特先生。 等你有足够的货物再来。 ";
			link.l1 = "好的。 ";
			link.l1.go = "exit";
		break;
		
		case "bakaut_1":
			dialog.text = "他的大帆船将在" + XI_ConvertString(pchar.GenQuest.Bakaut.Island+"Gen") + "海岸附近巡航几天。 所以不要迟到 --他可能会航行到群岛的另一个地方。 ";
			link.l1 = "好的, 我会加速。 谢谢! ";
			link.l1.go = "bakaut_2";
		break;
		
		case "bakaut_2":
			DialogExit();
			sld = characterFromId("Rozencraft");
			sld.DeckDialogNode = "bakaut";
			DeleteAttribute(sld, "DontDeskTalk"); // 可以派小船
			pchar.GenQuest.Bakaut.Info = "true";
			ReOpenQuestHeader("Bakaut");
			AddQuestRecord("Bakaut", "1");
			AddQuestUserData("Bakaut", "sIsland", XI_ConvertString(pchar.GenQuest.Bakaut.Island+"Gen"));
			AddQuestUserData("Bakaut", "sDays", FindRussianDaysString(sti(pchar.GenQuest.Bakaut.DaysQty)));
			AddQuestUserData("Bakaut", "sQty", FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value)));
			// 定时器
			pchar.quest.Bakaut_Rozencraft_Find.win_condition.l1 = "Timer";
			pchar.quest.Bakaut_Rozencraft_Find.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Bakaut_Rozencraft_Find.win_condition.l1.date.day   = GetAddingDataDay(0, 0, sti(pchar.GenQuest.Bakaut.DaysQty));
			pchar.quest.Bakaut_Rozencraft_Find.win_condition.l1.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.Bakaut.DaysQty));
			pchar.quest.Bakaut_Rozencraft_Find.win_condition.l1.date.year  = GetAddingDataYear(0, 0, sti(pchar.GenQuest.Bakaut.DaysQty));
			pchar.quest.Bakaut_Rozencraft_Find.function = "Bakaut_RozencraftRemove";
		break;
		// <—— 巴考特销售生成器
		
		//--> 圣慈悲修道院检查团到来
		case "SantaMisericordia_1":
			dialog.text = "我需要活到明天。 该死的'慈悲'在城里。 离开。 ";
			link.l1 = "这么戏剧性... ";
			link.l1.go = "exit";
		break;
		//<-- 圣慈悲修道院检查团到来
	}
}

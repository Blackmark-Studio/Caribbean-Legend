// 翻译: // 市长25/04/04的普通对话
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  // 翻译: // homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref aData;
	aref Link, NextDiag, arName;

	DeleteAttribute(&Dialog,"Links");

	ref FortChref; // 翻译: // 堡垒指挥官
	ref arItem;
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // 翻译: // 按城市调用对话 -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Mayor\" + NPChar.City + "_Mayor.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // 翻译: // 按城市调用对话 <--
    ProcessCommonDialogRumors(NPChar, Link, NextDiag);// 翻译: // homo 25/06/06

    FortChref = GetFortCommander(NPChar.City); // 翻译: // 将是堡垒指挥官或总督本人

    ref offref;
    int i, cn, iRank, iDay;
    int qty;
    string attrLoc, QuestName, sTemp;
	bool bOk, bOk1, bOk2;
	
    if (CheckNPCQuestDate(npchar, "Card_date"))
	{
		SetNPCQuestDate(npchar, "Card_date");
		npchar.money = 5000 + (rand(10)+1) * makeint(100 * sti(PChar.rank) * (10.0 / MOD_SKILL_ENEMY_RATE));
	}
	// 翻译: // 按案例生成IDX -->
	attrLoc   = Dialog.CurrentNode;
  	if (findsubstr(attrLoc, "GetPrisonerIdx_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	pchar.GenQuest.GetPrisonerIdx = strcut(attrLoc, i+1, strlen(attrLoc)-1); // 翻译: // 末尾的索引
 	    Dialog.CurrentNode = "sell_prisoner_2";
 	}
 	// 翻译: // 按案例生成IDX <--
 	
	switch (Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");
		break;
		
		case "fight":
            Pchar.quest.ArestInResidenceEnd.win_condition.l1          = "ExitFromLocation";
		    Pchar.quest.ArestInResidenceEnd.win_condition.l1.location = Pchar.location;
		    Pchar.quest.ArestInResidenceEnd.win_condition             = "ArestInResidenceEnd";
		    Pchar.quest.ArestInResidenceEnd.ResidenceLocation = Pchar.location;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;

			LAi_LockFightMode(Pchar, true); // 翻译: // 逃跑路线被封锁
		    LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		    LAi_group_Attack(NPChar, Pchar); // 翻译: // 对不朽的市长不起作用 :(
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // 翻译: // 幽灵士兵
			if (i != -1)
			{
			    LAi_group_Attack(&Characters[i], Pchar);
			}
		break;
		
		case "First time":
            NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase("你竟敢在我家露面? ! 真是勇敢, 或者说是愚蠢... ", "我的愚蠢守卫怎么会让敌人闯入我的宫殿? 我要让人为这掉脑袋。 ", "显然我的守卫一文不值, 如果某个无赖在我的住所里乱窜, 翻我的东西... "), 
					LinkRandPhrase("你需要什么, " + GetSexPhrase("无赖","魔鬼") + "? ! 我的士兵已经在追踪你" + GetSexPhrase(", 肮脏的海盗","") + "! ", "凶手, 立刻离开我的住所! 卫兵! ", "我不怕你, " + GetSexPhrase("无赖","老鼠") + "! 很快你就会在我们的堡垒被绞死! "));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("你的士兵毫无价值。 ", "试试看能不能抓住我。 "), 
					RandPhraseSimple("闭上你的嘴, " + GetWorkTypeOfMan(npchar, "") + ", 否则我就帮你闭上! ", "安静点伙计, 你就能活命。 "));
				link.l1.go = "fight";
				break;
			} 
			if (sti(NPChar.nation) == PIRATE)
            {
				if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar, "GenQuest.CaptainComission.PiratesCity") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
				{
					dialog.text = "你需要什么? ";
					link.l1 = "我想和你谈谈重要的工作。 ";
					link.l1.go = "quests";
					break;
				}
				if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin" && NPChar.city == "LeFransua")
				{
					dialog.text = "你需要什么? ";
					link.l1 = "我想和你谈谈重要的工作。 ";
					link.l1.go = "quests";
					break;
				}
					dialog.text = "没什么好谈的, 先生。 我很忙。 ";
					link.l1 = "抱歉。 ";
					link.l1.go = "Exit";
            }
			if (sti(NPChar.nation) != PIRATE && ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", 0) > 10)
            {
				iTotalTemp = ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", 0);
                dialog.text = "哦, 看看谁在那儿! 是" + GetSexPhrase("","") + " " + GetFullName(pchar) + "。 你知道吗, 我最近刚派出海盗猎人把你抓回来。 如果我知道你会大摇大摆地走进我的门, 我就省点钱了。 ";
                if (sti(pchar.Money) >= iTotalTemp*6000)
                {
                    link.l1 = "我正打算结算我们的账目。 ";
				    link.l1.go = "arestFree_1";
                }
				link.l2 = "我该赶紧离开了。 ";
				link.l2.go = "arest_1";
				break;
            }
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
    			dialog.text = "有人闯入! 卫兵! 警报! 杀人了! ";
				link.l1 = "该死! ";
				link.l1.go = "fight"; 
				break;
			}
			//--> 翻译: // Jason, 加斯科涅的负担
			if (CheckAttribute(pchar, "questTemp.Sharlie.Citcount") && npchar.city == "FortFrance")
			{
    			dialog.text = "你想要什么, 先生? ";
				link.l1 = "您好, 大人。 我是查尔斯.德.莫尔, 刚从巴黎来。 我在找米歇尔.德.蒙佩尔。 ";
                link.l1.go = "Sharlie";
				npchar.quest.meeting = "1"; // 翻译: // patch-6
				DelLandQuestMark(characterFromId("FortFrance_Mayor"));
				break;
			}
			
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock") && npchar.city == "FortFrance")
			{
				if (CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
				{
					dialog.text = "哦, 是你, 先生... 我必须为我的无礼道歉。 抱歉, 在殖民地这里我们远不如巴黎那样讲究礼仪。 ";
					link.l1 = "当然, 大人。 ";
					link.l1.go = "Sharlie_2";
				}
				else
				{
					dialog.text = "查尔斯, 你想要什么吗? ";
					link.l1 = "我有个问题... ";
					link.l1.go = "quests";
					link.l2 = "不, 没什么。 ";
					link.l2.go = "exit";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew"))
				{
					link.l3 = "先生, 我在丛林里发现了一具强盗的尸体。 他是被印第安人杀死的。 他身上有耳环, 看起来是从欧洲带来的。 也许它们属于你镇上的某个贵族? ";
					link.l3.go = "Sharlie_junglejew";
				}
				npchar.quest.meeting = "1"; // 翻译: // patch-6
				break;
			}			
			//<—— 翻译: // 加斯科涅的负担
			//--> 翻译: // Sinistra, 老鼠的折磨
			if (CheckAttribute(pchar, "questTemp.TK_TravlyaKrys") && npchar.city == "FortFrance")
			{
    			dialog.text = "欢迎来到加勒比, 德.莫尔船长。 这次是真的欢迎。 ";
				link.l1 = "谢谢您, 大人。 ";
                link.l1.go = "TK_TravlyaKrys";
				DelLandQuestMark(npchar);
				break;
			}
			// 翻译: // Jason 特殊任务
			// 翻译: // belamour legendary edition 修复检查带滑膛枪制服的问题
			if (CheckAttribute(pchar, "questTemp.Patria.Governor") && npchar.city == "Marigo" && IsUniformEquip())
			{
    			dialog.text = "很高兴见到您, 总督! 您近况如何? 圣马丁一切都在掌控之中。 ";
				link.l1 = "我没时间久留。 继续好好工作。 ";
				link.l1.go = "exit";
				link.l2 = "我想谈谈工作。 ";
				link.l2.go = "quests";   // 翻译: // (转发到城市文件)
				link.l8 = "来玩个机会游戏如何? ";
				link.l8.go = "Play_Game";
				break;
			}
			// 翻译: // belamour legendary edition 修复检查带滑膛枪制服的问题
			if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE && IsUniformEquip())
			{
    			dialog.text = "我的天, 很高兴见到您, 总督大人! 我们这个谦卑的小殖民地一切都很好! 请坐, 我让仆人摆好桌子... ";
				link.l1 = "不必了。 我不会待很久。 继续好好工作。 ";
				link.l1.go = "exit"; 
				link.l2 = "我想谈谈工作。 ";
				link.l2.go = "quests";   // 翻译: // (转发到城市文件)
				link.l8 = "来玩个机会游戏如何? ";
				link.l8.go = "Play_Game";
				break;
			}
			// 翻译: // belamour legendary edition 修复检查带滑膛枪制服的问题
			if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor") &&  IsUniformEquip())
			{
    			dialog.text = "我们这儿有谁来了! 法属殖民地的总督大人! 您想要什么, 大人? 坐下, 我让仆人拿酒和新鲜水果来。 ";
				link.l1 = "别担心, 我只是来岛上访问, 不能路过而不打个招呼。 ";
				link.l1.go = "exit"; 
				link.l2 = "我想谈谈工作。 ";
				link.l2.go = "quests";   // 翻译: // (转发到城市文件)
				link.l8 = "来玩个机会游戏如何? ";
				link.l8.go = "Play_Game";
				break;
			}		
			//--> 翻译: // Jason, 葡萄牙人
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "MartiniqueGovernor" && npchar.city == "FortFrance")
			{
    			dialog.text = "哦, 你来了, 船长! 我得说, 你花了不少时间。 ";
				link.l1 = "我尽快赶到了, 大人。 听说您有紧急事务? ";
				link.l1.go = "Portugal"; 
				break;
			}			
			//<—— 翻译: // 葡萄牙人
            
            if (npchar.quest.meeting == "0")
			{
				dialog.text = "我的人告诉我, 你非常坚持要请求接见。 我叫" + GetFullName(npchar) +
                              "。 我是" + GetCityName(NPChar.city) + "镇的总督, " + NationKingsName(npchar) +
                              "的臣民。 现在, 请告诉我, " + GetAddress_Form(NPChar) + "你想要什么? ";
				link.l1 = "我叫" + GetFullName(pchar) + "。 ";
				link.l1.go = "node_1";
				npchar.quest.meeting = "1";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_townhall")
				{
					dialog.text = TimeGreeting() +", 麦克阿瑟小姐。 ";
					link.l1 = TimeGreeting() +", 大人。 ";
					link.l1.go = "Helen_node_1"
				}
			}
			else
			{
               	//围攻 翻译: // homo
				if (CheckAttribute(&Colonies[FindColony(npchar.City)],"Siege"))
                {

                    makearef(aData, NullCharacter.Siege);
                    
                    if (CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                    {
                        dialog.text = "就这些吗? ";
                        link.l1 = "是的, 先生。 我不再耽误您了。 ";
                        link.l1.go = "exit";

                    }
                    else
                    {
                        dialog.text = "很抱歉打扰你, 但我现在没时间和你说话。 如你所知, 我们的殖民地遭到了" + NationNamePeople(sti(aData.nation)) + "的攻击。 我还在部署防御。 ";
                        link.l1 = "我想为堡垒的防御提供帮助。 ";
                        link.l1.go = "siege_task";
                        link.l2 = "那我就不再耽误您了。 ";
            			link.l2.go = "exit";
                    }
                }
                else
                {//->
                    makearef(aData, NullCharacter.Siege);
                    if (CheckAttribute(aData, "PlayerHelpMayor") && sti(aData.PlayerHelpMayor) == true
                    && CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                    {
                        AddMoneyToCharacter(Pchar,(sti(aData.iSquadronPower)*1500));
                        ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
                        ChangeCharacterComplexReputation(pchar,"nobility", 10);
                        AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 180);
                        AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 200);
                        AddCharacterExpToSkill(GetMainCharacter(), "Accuracy", 200);
                        AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 200);
                        //--> 翻译: // 谣言
                        SiegeRumour("他们说你帮助我们击退了" + NationNameSK(sti(aData.nation)) + "中队, 保卫了我们的殖民地! 我们感谢你, " + GetAddress_Form(NPChar) + "。 ", aData.Colony, sti(aData.conation), -1, 15, 3);
			            //<—— 翻译: // 谣言
                        DeleteAttribute(aData, "PlayerHelpMayor");
                        DeleteAttribute(aData, "HelpColony");
                        dialog.text = "哦, 是你, " + GetAddress_Form(NPChar) + " " + GetFullName(pchar) + ", 很高兴见到你。 给我们殖民地的好消息 - 我们成功击退了" + NationNameSK(sti(aData.nation)) + "入侵者。 你也有功劳, 所以这是你的奖励 - " + (sti(aData.iSquadronPower)*1500) + "八里亚尔。 给你。 ";
                        link.l1 = "谢谢您, " + GetAddress_FormToNPC(NPChar) + ", 很高兴与您合作! ";
                        link.l1.go = "exit";
                    }
                    else
                    {
   						//--> 翻译: // 发放任务在妓院找戒指
						if (rand(4) == 4 && pchar.questTemp.different == "free" && GetNpcQuestPastDayWOInit(npchar, "questTakeRing") > 365 && sti(pchar.questTemp.HorseQty) > 10)
						{// 翻译: // Addon-2016 Jason
							if (npchar.city == "Bridgetown" || npchar.city == "Charles" || npchar.city == "FortFrance" || npchar.city == "Marigo" || npchar.city == "Panama" || npchar.city == "PortRoyal" || npchar.city == "SantoDomingo" || npchar.city == "Tortuga")
							{
        						dialog.text = "我有个任务给你, 但有点不寻常。 ";
								link.l1 = "这些是我最擅长的任务。 ";
        						link.l1.go = "TakeRing_1";
								SaveCurrentNpcQuestDateParam(npchar, "questTakeRing");
								break;
							}
						}
						//<—— 翻译: // 发放任务在妓院找戒指    				
						dialog.text = RandPhraseSimple("哦, 又是你? 这次你想从我这里得到什么? ",
                                      "你在干扰我处理城市事务。 你想要什么, " + GetAddress_Form(NPChar) + "? ");
						if (npchar.city != "Panama") // 翻译: // Addon-2016 Jason
						{
							link.l1 = "我想和你谈谈为" + NationNameGenitive(sti(NPChar.nation)) + "工作的事。 ";
							link.l1.go = "work";
						}
						// 翻译: // Warship 生成器 "无人岛上的海盗" - 把海盗交给当局
						if(CheckAttribute(PChar, "Quest.PiratesOnUninhabited_OnShore") || CheckAttribute(PChar, "Quest.PiratesOnUninhabited_ShipSink"))
						{
							link.l11 = XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore + "Gen") + " 我发现了一些海盗。 所有" + PChar.GenQuest.PiratesOnUninhabited.PiratesCount + "目前都在船上。 我想把他们交给当局。 ";
							link.l11.go = "PiratesOnUninhabited_1";
						}
						
        				link.l2 = "我本来想和你谈一个重要的话题。 ";
						if(CheckAttribute(pchar,"questTemp.ReasonToFast") && !CheckAttribute(pchar,"questTemp.ReasonToFast.SpeakOther") && !CheckAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther") && (pchar.questTemp.ReasonToFast.city == NPChar.city))
						{
							link.l2.go = "ReasonToFast_Mayor1";
						}
						else
						{
							link.l2.go = "quests";   // 翻译: // (转发到城市文件)
						}	
						if(CheckAttribute(pchar,"GenQuest.CaptainComission") && (pchar.GenQuest.CaptainComission.variant == "A2") && (pchar.GenQuest.CaptainComission.City == NPChar.city))
						{
							if(pchar.GenQuest.CaptainComission == "Begin_1" && !CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor")) 
							{
								link.l12 = "有一位指挥巡逻船" + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")) + "名叫" + pchar.GenQuest.CaptainComission.Name + "的船长, 我怎么才能见到他? ";
								link.l12.go = "CapComission_Mayor1";
							}	
							if(CheckAttribute(pchar,"GenQuest.CaptainComission.PrisonFree"))
							{
								link.l12 = "前指挥巡逻船" + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")) + " " + pchar.GenQuest.CaptainComission.Name + "的船长同意向当局透露他的藏匿处。 ";
								link.l12.go = "CapComission_Mayor9";
							}
							if(pchar.GenQuest.CaptainComission == "GetGoodsSuccess")
							{
								link.l12 = "前指挥巡逻船" + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")) + " " + pchar.GenQuest.CaptainComission.Name + "的船长向我透露了他的藏匿处。 ";
								link.l12.go = "CapComission_Mayor13";
							}
						}
						if(CheckAttribute(pchar,"GenQuest.ShipWreck") && pchar.GenQuest.ShipWreck == "SailorsOnShore" && GetQuestPastDayParam("GenQuest.ShipWreck") < 25  && sti(npchar.nation) == sti(pchar.GenQuest.ShipWreck.Nation))
						{
							if(!CheckAttribute(pchar,"GenQuest.ShipWreck.SpeakMayor"))
							{
								iDay = GetQuestPastDayParam("GenQuest.ShipWreck");
								if(CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
								{
									link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Dat")) + " 我遇到了" + pchar.GenQuest.ShipWreck.Name + "船长和他的水手, 他们被海盗" + pchar.GenQuest.ShipWreck.BadName + "送上了岸。 " +
										"不幸的是, 我的船上已经有太多人, 无法让他们上船。 但我给他们留下了食物和武器。 如果救援船在" + (30 - iDay) + "天内没有找到他们, 那我不知道能否找到活着的他们。 ";
									link.l13.go = "ShipWreck1";
								}
								else
								{
									link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Gen")) + " 我遇到了失事船只'" + pchar.GenQuest.ShipWreck.ShipTypeName + "'的水手和他们的船长。 " + 
										"不幸的是, 我的船上已经有太多人, 无法让他们上船。 但我给他们留下了食物和武器。 如果救援船在" + (30 - iDay) + "天内没有找到他们, 那我不知道能否找到活着的他们。 ";
									link.l13.go = "ShipWreck1";							
								}
							}	
						}
        				if (GetPrisonerQty() > 0)
        				{
                            link.l3 = "我想移交一名囚犯。 ";
        				    link.l3.go = "sell_prisoner";
        				}
        				if (npchar.Default  == npchar.location) // 翻译: // 如果不在监狱
        				{
        					if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
        					{
        						link.l4 = "我需要和你解决一些财务问题。 ";
        						link.l4.go = "LoanForAll";// 翻译: // (转发到贷款生成器)
        					}
        				}
						//-->> 翻译: // 上交在妓院找到的戒指
						if (CheckCharacterItem(pchar, "MayorsRing"))
						{
							if (pchar.questTemp.different.TakeMayorsRing == "toBrothel")
							{
        						link.l5 = "我设法找到了你的戒指。 给你。 ";
        						link.l5.go = "TakeRing_S1";
							}
							else
							{
        						link.l5 = "我有你的结婚戒指。 其中一个... 妓院里的工作女孩拿着它。 ";
        						link.l5.go = "TakeRing_S3";
							}
						}
						//<<—— 翻译: // 上交在妓院找到的戒指 
						
						//--> 翻译: // Jason, 生成2级邮政快递员
						if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
						{
							if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
							{
							link.l14 = "我带来了来自" + XI_ConvertString("Colony" + pchar.questTemp.WPU.Postcureer.StartCity + "Gen") + "镇的消息。 ";
							link.l14.go = "Postcureer_LevelUp_ForAll";
							}
						}
						//<—— 翻译: // 生成2级邮政快递员
						
						// 翻译: // Warship, 16.05.11。 任务"正义待售" -->
						if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_townhall")
						{
							link.l15 = UpperFirst(GetAddress_FormToNPC(NPChar)) + ", 我找到了一群走私者, 他们的头目最近被卫兵抓住了。 现在他们正策划救他。 他们的船'" + PChar.GenQuest.JusticeOnSale.ShipName + "'停泊在" + XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId + "Dat") + "。 ";
							link.l15.go = "JusticeOnSale_1";
						}
						
						if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.ShipSink") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_townhall")
						{
							link.l15 = UpperFirst(GetAddress_FormToNPC(NPChar)) + ", 走私者团伙已经不存在了! ";
							link.l15.go = "JusticeOnSale_7";
						}
						// <--翻译: // 正义待售
						//Jason --> 翻译: // 赛船会
						if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
						{
							link.l16 = "我是来参加赛船会的。 这是我的邀请。 ";
							link.l16.go = "Regata";
						}
        				//link.l7 = "我想知道" + NationNameGenitive(sti(NPChar.nation)) + "的总督在哪里。 ";
        				link.l8 = "也许, 你想休息一下, 玩个机会游戏? ";
        			    link.l8.go = "Play_Game";
        				link.l10 = "请原谅, 但职责召唤。 ";
        				link.l10.go = "exit";
                    }
                }//<-
			}
		break;
		
		// 翻译: // Warship 生成器 "无人岛上的海盗"
		case "PiratesOnUninhabited_1":
			offref = CharacterFromID("PirateOnUninhabited_0");
			qty = makeint(sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) * (sti(offref.rank) * (800 + GetCharacterSPECIALSimple(NPChar, SPECIAL_L) * 100) + GetCharacterSkillToOld(offref, "Leadership") * 500 + GetCharacterSkillToOld(PChar, "commerce") * 500) / 20);
			
			PChar.GenQuest.PiratesOnUninhabited.MoneyForPirates = qty;
			
			dialog.text = "很好。 我们必须齐心协力对抗这一共同灾难。 我将立即派船去接他们。 放心, 不出一周他们就会被绞死在绞刑架上。 哦, 当然, 还有奖励 - " + FindRussianMoneyString(qty) + "。 ";
			link.l1 = "谢谢您, 大人。 总是很高兴。 ";
			link.l1.go = "PiratesOnUninhabited_2";
			link.l2 = "不。 仔细想想, 这不行。 ";
			link.l2.go = "exit";
		break;
		
		case "PiratesOnUninhabited_2":
			offref = CharacterFromID("PirateOnUninhabited_0");
			
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.MoneyForPirates));
			
			RemovePassenger(PChar, offref);
			RemoveCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
			
			sTemp = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTemp, "PiratesOnUninhabited", "12");
			AddQuestUserData(sTemp, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTemp, "mayorName", GetFullName(NPChar));
			CloseQuestHeader(sTemp);
			
			PChar.Quest.PiratesOnUninhabited_OnShore.over = "yes";
			PChar.Quest.PiratesOnUninhabited_OnMayak.over = "yes";
			
			if(CheckAttribute(PChar, "Quest.PiratesOnUninhabited_ShipSink"))
			{
				PChar.Quest.PiratesOnUninhabited_ShipSink.over = "yes";
				
				PChar.GenQuest.PiratesOnUninhabited.ClearShip = true;
				Map_ReleaseQuestEncounter("PiratesOnUninhabited_BadPirate"); // 翻译: // 从全局移除
			}
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
		break;
		
		// -----------------------—— 紧急原因 -----------------------------
		case "ReasonToFast_Mayor1":
			dialog.text = "我洗耳恭听, 船长。 ";
			link.l1 = "我想告诉你关于你的驻军一名军官和海盗之间的犯罪勾结... (解释情况) 。 ";
			if(sti(pchar.reputation.nobility) < 41)
			{
				link.l1.go = "ReasonToFast_BMayor";			
			}
			else
			{
				link.l1.go = "ReasonToFast_GMayor";	
			}
			pchar.questTemp.ReasonToFast.SpeakOther = true;			
		break;
		
		case "ReasonToFast_GMayor":
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_1") 
			{ 
				// 翻译: // 分支_A
				dialog.text = "谢谢你, " + GetSexPhrase("先生","小姐") + "! 我将立即下令逮捕那个叛徒。 \n你一定花了很多钱, 唉, 我们的国库是空的... ";
				link.l1 = "我不是为了钱, 大人。 ";
				link.l1.go = "ReasonToFast_GMayor_11";				
				if(pchar.questTemp.ReasonToFast.chain == "A0") ReasonToFast_RemoveVictim();
				if(pchar.questTemp.ReasonToFast.chain == "A1") pchar.quest.ReasonToFast_ClearLakey.over = "yes";
			}			
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_2") 
			{ 
				// 翻译: // 已获得地图
				dialog.text = "我感谢你! 我会逮捕那个无赖。 \n想想看! 我正要为他服役十年授予他一把金柄军刀! 你让我免于一些严重的尴尬! ";
				link.l2 = "正义本身就是奖励。 ";
				link.l2.go = "ReasonToFast_GMayor_21";			
			}
			if(pchar.questTemp.ReasonToFast == "PatrolDied") 
			{ 
				// 翻译: // 巡逻队被击败
				dialog.text = "德.莫尔先" + GetSexPhrase("生","生") + ", 你不能在没有任何证人的情况下就杀死嫌疑人! 现在我们甚至无法获得他犯罪的证据! 我只能尽力让你免于因过失杀人而被捕。 ";
				link.l3 = "住口, 这是自卫, 大人。 ";
				link.l3.go = "ReasonToFast_GMayor_31";
				pchar.questTemp.ReasonToFast.speakAfterPatrolDied = true;	
				pchar.quest.ReasonToFast_SpeakMayor.over = "yes";
			}			
		break;
		
		case "ReasonToFast_BMayor":
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_1") 
			{ 				
				dialog.text = "船长, 你意识到你他妈做了什么吗? ! 我设置这个陷阱已经一个多月了! 现在, 就为了你自己的娱乐, 你破坏了我们巡逻队与" + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN) + "的会面, 现在你还来这里吹嘘? ! 也许你现在可以告诉我, 我该如何解释这次行动的所有开支和费用? ! ";
				link.l1 = "大人, 我只是解决了你的问题, 如果你看看, 你应该一直给我付钱! ";
				link.l1.go = "ReasonToFast_BMayor_1";
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";				
				if(pchar.questTemp.ReasonToFast.chain == "A0") ReasonToFast_RemoveVictim();
				if(pchar.questTemp.ReasonToFast.chain == "A1") pchar.quest.ReasonToFast_ClearLakey.over = "yes";
			}
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_2") 
			{ 
				// 翻译: // 已获得地图
				dialog.text = "让我看看这张地图\n你现在是认真的吗? 这张破烂的纸就是证据? ";
				link.l2 = "得了吧, 大人, 理智点。 ";
				link.l2.go = "ReasonToFast_BMayor_1";
				TakeItemFromCharacter(pchar, "mapQuest");				
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_B";
			}
			if(pchar.questTemp.ReasonToFast == "PatrolDied") 
			{ 
				// 翻译: // 巡逻队被击败
				dialog.text = "好吧好吧, 现在我们知道我的巡逻队发生了什么。 至少你来到这里, 省去了我们寻找凶手的需要。 ";
				link.l3 = "大人! 你只是拒绝看到重点... ";
				link.l3.go = "ReasonToFast_BMayor_1";			
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";
				pchar.quest.ReasonToFast_SpeakMayor.over = "yes";
			}		
		break;
		
		case "ReasonToFast_GMayor_11":
			dialog.text = "你可能是个白痴, 但至少是个有用的白痴。 给你 - 拿这张地图;上周我们绞死的一个海盗身上找到的。 愿上帝保佑, 也许你会找到他的宝藏, 尽管我觉得不太可能... ";
			link.l1 = "谢谢你, 你真慷慨! ";
			link.l1.go = "exit";
			AddQuestRecord("ReasonToFast", "15");
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			GiveItem2Character(pchar, "mapQuest"); 
			arItem = ItemsFromID("mapQuest");
			ReasonToFast_GenerateTreasureMap(arItem);
			pchar.questTemp.ReasonToFast.state = "chain_A"; // 翻译: // 分支_A, 不生成提示
			pchar.questTemp.ReasonToFast = "GetMap";			
			ReasonToFast_SetHunterCoastal();
		break;
		
		case "ReasonToFast_GMayor_21":
			dialog.text = "你的热情值得称赞。 请接受这把剑作为奖励 - 这是我至少能做的。 哦, 你可以自己留着地图。 我确信加勒比海有很多这样的假货。 ";
			link.l1 = "谢谢你, 你真慷慨! ";
			link.l1.go = "exit";
			AddQuestRecord("ReasonToFast", "14");
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			GiveItem2Character(pchar, pchar.questTemp.ReasonToFast.p6);
			pchar.questTemp.ReasonToFast.state = "chain_B"; // 翻译: // 已获得地图
			pchar.questTemp.ReasonToFast = "GetMap";			
			ReasonToFast_SetHunterCoastal();
		break;
		case "ReasonToFast_GMayor_31":
			dialog.text = "也许, 也许... 好吧, 我们就说这笔交易是由神圣的正义和我们主的意志决定的。 ";
			link.l1 = "谢谢你, 你真慷慨! ";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			AddQuestRecord("ReasonToFast", "16");
			CloseQuestHeader("ReasonToFast");
			DeleteAttribute(pchar,"ReasonToFast");
		break;
		
		case "ReasonToFast_BMayor_1":
			dialog.text = "住口, 小子! 你要么是疯了, 要么就是和我们的敌人勾结! 卫兵, 抓住这个白痴! ";
			link.l1 = "把手放在我身上, 你就会失去它! ";
			link.l1.go = "fight";
		
			pchar.quest.ReasonToFast_ExitFromTown.win_condition.l1			= "EnterToSea";           	
            pchar.quest.ReasonToFast_ExitFromTown.function    				= "ReasonToFast_ExitFromTownFight";						
			pchar.questTemp.ReasonToFast.canSpeakSailor = true;
			pchar.TownEscape = true;
			Flag_PIRATE();
		break;
		
		// -----------------------—— 紧急原因 -----------------------------
		
		// --------------------------'大帆船'行动-----------------------------
		case "CapComission_Mayor1":
			dialog.text = "现在这不可能。 他正在被逮捕候审。 ";
			link.l1 = "是吗? 他被怀疑什么? ";			
			link.l1.go = "CapComission_Mayor2";
		break;
		
		case "CapComission_Mayor2":
			dialog.text = "不幸的是, 这不是怀疑, 而是确凿的事实。 我们有信息表明, 他以巡逻为幌子袭击船只。 他从商人那里没收货物, 然后卖给走私者和海盗。 真遗憾... 想想看, 他曾经被认为是王国拥有的最好的船长之一... ";
			link.l1 = "谁向你提供了证据? ";
			link.l1.go = "CapComission_Mayor3";				
		break;
		
		case "CapComission_Mayor3":
			dialog.text = "他的一个受害者写了一份报告, 详细描述了事件, 包括日期。 被袭击船只的名称和没收的货物数量。 " +
				"相信我, 数字相当可观。 那天巡逻船" + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name"))) + "船长" + pchar.GenQuest.CaptainComission.Name + "确实在值班。 船长在报告中将此事件描述为与海盗船相遇, 但根本没有提到任何货物。 ";
			link.l1 = "但到底有没有货物? ";
			link.l1.go = "CapComission_Mayor4";
			pchar.GenQuest.CaptainComission.SpeakMayor = true;
		break;
		
		case "CapComission_Mayor4":
			dialog.text = "这是毫无疑问的。 受害方是一个非常有名的人, 他不会用诽谤和中伤来贬低自己。 现在我们的巡逻队正在寻找船长的藏匿处。 " +
				"一旦找到, 船长就可以出庭\n如果你在这件事上帮助我们, 我们将非常感激你。 ";
			link.l1 = "可能不会。 我对当地不太熟悉, 无法寻找藏匿处。 抱歉, 我得走了。 ";
			link.l1.go = "CapComission_Mayor5";
			link.l2 = "也许... 我有多少时间? ";
			link.l2.go = "CapComission_Mayor6";	
		break;
		
		case "CapComission_Mayor5":
			AddQuestRecord("CaptainComission2", "49");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen")));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			pchar.GenQuest.CaptainComission = "MayorTalkBad";
			CaptainComission_GenerateCaptainInPrison();
			DialogExit();
		break;
		
		case "CapComission_Mayor6":
			dialog.text = "我相信, 在两天内, 巡逻队可以在没有你帮助的情况下找到藏匿处, 所以你应该快点。 "; 
			link.l1 = "是, 我这就去。 但我需要拜访一下" + pchar.GenQuest.CaptainComission.Name + "船长。 可以安排吗? ";
			link.l1.go = "CapComission_Mayor7";
		break;
		
		case "CapComission_Mayor7":
			dialog.text = "这没问题。 我会通知堡垒的指挥官你要来访。 ";
			link.l1 = "谢谢你。 现在, 请原谅我。 ";
			link.l1.go = "CapComission_Mayor8";
		break;
		
		case "CapComission_Mayor8":
			AddQuestRecord("CaptainComission2", "50");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen")));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);			
			AddQuestUserData("CaptainComission2", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			OfficersReaction("good");
			pchar.GenQuest.CaptainComission.MayorTalkGood = true;
			pchar.GenQuest.CaptainComission = "MayorTalkGood";
			pchar.quest.CaptainComission_TimeIsOver.over = "yes";
			SetFunctionTimerConditionParam("CaptainComission_GetSecretTimeIsOut", 0, 0, 2, MakeInt(24 - GetHour()), false);
			CaptainComission_GenerateCaptainInPrison();
			DialogExit();
		break;
		
		case "CapComission_Mayor9":
			dialog.text = "太好了! 宝藏在哪里? ";
			link.l1 = "我还不知道。 他没有告诉我确切的位置。 ";
			link.l1.go = "CapComission_Mayor10";
		break;
		
		case "CapComission_Mayor10":
			dialog.text = "嗯, 真巧! 你知道, 他也‘没有告诉我’确切的位置... ";
			link.l1 = "我正在努力。 ";
			link.l1.go = "CapComission_Mayor11";
		break;
		
		case "CapComission_Mayor11":
			dialog.text = "不再需要了\n卫兵! 把囚犯带回牢房\n你可以走了, " + GetFullName(pchar) + "。 ";
			link.l1 = "但是总督... ";
			link.l1.go = "CapComission_Mayor12";
		break;
		
		case "CapComission_Mayor12":
			sld = CharacterFromID("CapComission_1");
			sld.lifeDay = 0;
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetActorType(sld);
            LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);			
			pchar.quest.CapComission_DeletePrisonGroup.win_condition.l1 = "ExitFromLocation";
            pchar.quest.CapComission_DeletePrisonGroup.win_condition.l1.location = pchar.location;
            pchar.quest.CapComission_DeletePrisonGroup.win_condition = "CaptainComission_DeletePrisonGroup";									
			ChangeOfficersLoyality("bad_all", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", -4);			
			AddQuestRecord("CaptainComission2", "23");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("CaptainComission2");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CapComission_Mayor13":
			pchar.quest.CaptainComission_SpeakMayorGoods.over = "yes";
			dialog.text = "太好了! 我们要去哪里找他的宝藏? ";
			link.l1 = "在" + RandPhraseSimple(RandPhraseSimple("北","西"),RandPhraseSimple("东","南")) + "端" + XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen") + "悬崖脚下有一个大壁龛, 入口处堆满了石头。 那就是藏匿处。 ";
			link.l1.go = "CapComission_Mayor14";
		break;
		
		case "CapComission_Mayor14":
			dialog.text = "干得好! " + pchar.GenQuest.CaptainComission.Name + "本人在哪里? 有人告诉我你把他从堡垒的地牢里带走了。 ";
			link.l1 = "不幸的是, 他在与走私者的冲突中丧生了。 ";
			link.l1.go = "CapComission_Mayor15";
		break;
		
		case "CapComission_Mayor15":
			dialog.text = "这很糟糕... 非常糟糕, " + GetSexPhrase("先生","小姐") + " " + GetFullName(pchar) + "。 我本来打算公开处决他, ‘以儆效尤’。 " + 
				"无论如何, 他都无法逃避绞刑\n所以, 虽然你在技术上违反了法律, 非法释放了囚犯, 但你仍然没有救他, 我无法在报告中解决这个问题。 因此, 你得不到奖励... 但我想亲自感谢你。 接受我的礼物 - 对战斗船长非常有用的东西。 ";
			link.l1 = "谢谢你。 总是很高兴为您服务。 ";	
			link.l1.go = "CapComission_Mayor16";
		break;
		
		case "CapComission_Mayor16":
			AddQuestRecord("CaptainComission2", "30");
			AddQuestUserData("CaptainComission2", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			CloseQuestHeader("CaptainComission2");
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
			ChangeCharacterComplexReputation(pchar,"nobility", 4);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 10);
			OfficersReaction("good");
			DeleteAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
		// --------------------------'大帆船'行动-----------------------------
		
		// ------------------------—— 生成器 "遇难船员" ------------
		case "ShipWreck1":
			if(iDay > 15)
			{
				dialog.text = RandPhraseSimple("你是怎么做到的? 即使顺风航行, 到达那个地方至少也需要十五天! ","德.莫尔船" + GetFullName(pchar) + ", 你的不负责任让我震惊! 你为什么不早点告诉我? ");
				link.l1 = "嗯, 我甚至不知道该说什么... ";
				link.l1.go = "ShipWreck2";
			}
			else
			{
				dialog.text = "这是个好消息! 我们已经失去了再见到" + pchar.GenQuest.ShipWreck.Name + "活着的希望。 我将立即派出救援队。 哦, 请接受这个奖励, 感谢你的效率和参与他们的救援。 ";
				link.l1 = "谢谢您, 大人。 我很高兴能帮上忙。 我相信探险队会及时到达那里。 ";
				link.l1.go = "ShipWreck3";	
			}
			pchar.GenQuest.ShipWreck.SpeakMayor = true;
			pchar.quest.ShipWreck_MeetInShore.over = "yes";
			pchar.quest.ShipWreck_SaveSailors.over = "yes"; // 翻译: // belamour gen 也需要移除30天的计时器
		break;
		
		case "ShipWreck2":
			dialog.text = "哇... 有什么好说的? 去学习《海洋法》吧, 小子! 不管怎样, 我会尽力救这些人。 ";
			link.l1 = "大人, 但我给他们留下了足够的食物。 你有时间, 我保证... ";
			link.l1.go = "ShipWreck4";
		break;
		
		case "ShipWreck3":
			addMoneyToCharacter(pchar, sti(pchar.rank) * 300 + 3000 + rand(3000));
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			AddQuestRecord("ShipWrecked", "14");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "sCity", XI_ConvertString("Colony" + NPChar.city + "Gen")); // 翻译: // belamour gen 仅仅 NPChar.city 不会给出任何东西
			AddQuestUserData("ShipWrecked", "ShoreName", XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Gen")); // 翻译: // belamour gen
			CloseQuestHeader("ShipWrecked");
			DeleteAttribute(pchar, "GenQuest.ShipWreck.SpeakMayor");		
			DialogExit();
			AddDialogExitQuest("ShipWreck_RemoveSailorsFromShore");
		break;		
		
		case "ShipWreck4":
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			AddQuestRecord("ShipWrecked", "13");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "sCity", XI_ConvertString("Colony" + NPChar.city + "Gen")); // 翻译: // belamour gen 仅仅 NPChar.city 不会给出任何东西
			AddQuestUserData("ShipWrecked", "ShoreName", XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Gen")); // 翻译: // belamour gen
			CloseQuestHeader("ShipWrecked");
			DeleteAttribute(pchar, "GenQuest.ShipWreck.SpeakMayor");		
			DialogExit();
			AddDialogExitQuest("ShipWreck_RemoveSailorsFromShore");
		break;
		// ------------------------—— 生成器 "遇难船员" ------------
		
		// --------------------—— 在妓院找戒指 ----------------------------
		case "TakeRing_1":
			dialog.text = "我知道你, 怎么说呢... " + GetSexPhrase("是妓院的常客","喜欢时不时去妓院") + "。 因此决定向你求助\n" +
				"你知道, 不好意思承认, 但我最近在那里... ";
			link.l1 = "那有什么问题? 性是非常自然的事情, 你知道... ";
			link.l1.go = "TakeRing_2";
		break;
		case "TakeRing_2":
			dialog.text = "哦, 不, 我不是在说教, 没有。 问题是有一次我喝多了, 丢了我的结婚戒指... ";
			link.l1 = "那真是个问题。 我很抱歉。 ";
			link.l1.go = "TakeRing_3";
		break;
		case "TakeRing_3":
			dialog.text = "我不需要任何人同情我。 我需要我的戒指回来。 如果你能在午夜前把它拿回来, 我会非常慷慨。 如果你失败了, 我妻子会杀了我。 ";
			link.l1 = "我明白了... 你到底在哪里丢的? 你还记得什么特别的吗? ";
			link.l1.go = "TakeRing_4";
		break;
		case "TakeRing_4":
			dialog.text = "不幸的是, 不。 什么都不记得。 ";
			link.l1 = "我明白了。 好吧, 那我们去找吧。 ";
			link.l1.go = "TakeRing_5";
			link.l2 = "你知道, " + GetAddress_FormToNPC(NPChar) + ", 我想我会放弃这个。 请原谅我... ";
			link.l2.go = "TakeRing_6";
		break;	
		case "TakeRing_5":
			dialog.text = "太好了! 但记住 - 你必须在午夜前找到它。 ";
			link.l1 = "我记得。 我很快就回来。 ";
			link.l1.go = "exit";
			pchar.questTemp.different = "TakeMayorsRing";
			pchar.questTemp.different.TakeMayorsRing = "toBrothel";
			pchar.questTemp.different.TakeMayorsRing.Id = GetFullName(npchar);
			pchar.questTemp.different.TakeMayorsRing.city = npchar.city;	
			pchar.questTemp.different.TakeMayorsRing.price = sti(pchar.rank)*100+1000;
			sld = ItemsFromID("MayorsRing");
			sld.CityName = XI_ConvertString("Colony" + npchar.city + "Gen");
			//把戒指放在物品里
			if (rand(3) != 2)
			{				
				switch (rand(2))
				{
					case 0: sTemp = "_Brothel_room";  break;
					case 1: sTemp = "_Brothel";  break;
					case 2: sTemp = "_SecBrRoom";  break;
				}
				sld.shown = true;
				sld.startLocation = pchar.questTemp.different.TakeMayorsRing.city + sTemp;
				sld.startLocator = "item" + (rand(4)+1);
				pchar.questTemp.different.TakeMayorsRing.item = true; // 翻译: // 标志戒指掉在物品中
				Log_QuestInfo("戒指在" + sld.startLocation + ", 在定位器" + sld.startLocator + "中");
			}
			SetTimerFunction("TakeMayorsRing_null", 0, 0, 1); // 翻译: // 释放迷你任务的权限
			ReOpenQuestHeader("SeekMayorsRing");
			AddQuestRecord("SeekMayorsRing", "1");
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("SeekMayorsRing", "sName", pchar.questTemp.different.TakeMayorsRing.Id);
		break;	
		case "TakeRing_6":
			dialog.text = "哦? 嗯, 这真的出乎意料... 好吧, 祝你好运, 船长。 ";
			link.l1 = "再见。 ";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
		break;

		case "TakeRing_S1":
			dialog.text = "这是我的戒指! 你救了我的命! ";
			link.l1 = "没什么, 先生。 ";
			link.l1.go = "TakeRing_S2";
			TakeItemFromCharacter(pchar, "MayorsRing");
		break;
		case "TakeRing_S2":
			dialog.text = "这是给你的酬金, 干得漂亮! 我非常感激你! ";
			link.l1 = "很高兴能帮到您, 先生, 下次请多加小心。 ";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 10);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.different.TakeMayorsRing.price));
			pchar.questTemp.different = "free";
			pchar.quest.TakeMayorsRing_null.over = "yes"; //移除计时器
			AddQuestRecord("SeekMayorsRing", "7");
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			CloseQuestHeader("SeekMayorsRing");
			DeleteAttribute(pchar, "questTemp.different.TakeMayorsRing");
		break;
		case "TakeRing_S3":
			dialog.text = "上帝保佑! 我真的应该不再喝那么多了... ";
			link.l1 = "的确如此! 这是你的戒指。 ";
			link.l1.go = "TakeRing_S4";
		break;
		case "TakeRing_S4":
			dialog.text = "是的, 是的, 非常感谢。 我欠你一个人情! 这是给你的酬金, 干得漂亮! ";
			link.l1 = "谢谢" + GetAddress_FormToNPC(NPChar) + "。 ";
			link.l1.go = "exit";
			TakeItemFromCharacter(pchar, "MayorsRing");
			ChangeCharacterComplexReputation(pchar,"nobility", 3);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 3);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.different.TakeMayorsRing.price));
			pchar.questTemp.different = "free";
			pchar.quest.TakeMayorsRing_null.over = "yes"; //移除计时器
			AddQuestRecord("SeekMayorsRing", "7");
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			CloseQuestHeader("SeekMayorsRing");
			DeleteAttribute(pchar, "questTemp.different.TakeMayorsRing");
		break;
		// --------------------—— 在妓院找到戒指 ----------------------------

		case "node_1":
            //殖民地被围攻 homo
			if (CheckAttribute(&Colonies[FindColony(npchar.City)],"Siege"))
            {

                makearef(aData, NullCharacter.Siege);
                

                if (CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                {
                    dialog.text = "我们已经讨论过所有事情了, 不是吗? ";
                    link.l1 = "没错。 我不再耽误您了。 ";
                    link.l1.go = "exit";

                }
                else
                {
                    dialog.text = "很抱歉让您失望, 但我现在没有时间和您交谈。 如您所知, 我们的殖民地遭到了" + NationNamePeople(sti(aData.nation)) + "的袭击。 我必须去处理防御事务。 ";
                    link.l1 = "好吧, 我只是想提供帮助, 保卫堡垒。 ";
                    link.l1.go = "siege_task";
                    link.l2 = "那我不再耽误您了。 ";
        			link.l2.go = "exit";
                }
            }
            else
            {//->
                makearef(aData, NullCharacter.Siege);
                if (CheckAttribute(aData, "PlayerHelpMayor") && sti(aData.PlayerHelpMayor) == true
                && CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                {
                    AddMoneyToCharacter(Pchar,(sti(aData.iSquadronPower)*3000));
                    ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
                    ChangeCharacterComplexReputation(pchar,"nobility", 10);
                    AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 180);
                    AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 200);
                    AddCharacterExpToSkill(GetMainCharacter(), "Accuracy", 200);
                    AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 200);
                    //--> 谣言
                    SiegeRumour("据说您帮助我们击退了" + NationNameSK(sti(aData.nation)) + "的中队, 保卫了我们的殖民地! 我们感谢您, " + GetAddress_Form(NPChar) + "。 ", aData.Colony, sti(aData.conation), -1, 15, 3);
		            //<—— 谣言
                    DeleteAttribute(aData, "PlayerHelpMayor");
                    DeleteAttribute(aData, "HelpColony");
                    dialog.text = "哦, 是您, " + GetAddress_Form(NPChar) + " " + GetFullName(pchar) + ", 很高兴见到您。 好消息 - 我们成功击退了" + NationNameSK(sti(aData.nation)) + "的入侵者。 您也为此出了一份力, 这是您的奖励 - " + (sti(aData.iSquadronPower)*1500) + "八里亚尔。 给您。 ";
                    link.l1 = "谢谢您, " + GetAddress_FormToNPC(NPChar) + ", 很高兴与您合作! ";
                    link.l1.go = "exit";
                }
                else
                {
                    if (CheckAttribute(aData, "PlayerHelpMayor")) DeleteAttribute(aData, "PlayerHelpMayor");
                    dialog.text = "那么您来这里打扰我处理重要国家事务的原因是什么? ";
					if (npchar.city != "Panama") // Addon-2016 Jason
					{
						link.l1 = "我想为" + NationNameGenitive(sti(NPChar.nation)) + "效力。 ";
						link.l1.go = "work";
					}
					// Warship 生成器 "无人岛上的海盗" - 向当局交出海盗
					if(CheckAttribute(PChar, "Quest.PiratesOnUninhabited_OnShore") || CheckAttribute(PChar, "Quest.PiratesOnUninhabited_ShipSink"))
					{
						link.l11 = XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore + "Dat") + "我遇到了一些海盗。 目前所有" + PChar.GenQuest.PiratesOnUninhabited.PiratesCount + "人都在船上。 我想把他们交给当局。 ";
						link.l11.go = "PiratesOnUninhabited_1";
					}
					
        			link.l2 = "我想和您谈谈一件重要的事情。 ";
					if(CheckAttribute(pchar,"questTemp.ReasonToFast") && !CheckAttribute(pchar,"questTemp.ReasonToFast.SpeakOther") && !CheckAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther") && (pchar.questTemp.ReasonToFast.city == NPChar.city))
					{
						link.l2.go = "ReasonToFast_Mayor1";
					}
					else
					{					
						link.l2.go = "quests";
					}	
					if(CheckAttribute(pchar,"GenQuest.CaptainComission") && (pchar.GenQuest.CaptainComission.variant == "A2") && (pchar.GenQuest.CaptainComission.City == NPChar.city))
					{
						if(pchar.GenQuest.CaptainComission == "Begin_1" && !CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor")) 
						{
							link.l12 = "有一位指挥巡逻队" + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")) + "的船长, 名叫" + pchar.GenQuest.CaptainComission.Name + ", 我如何才能见到他? ";
							link.l12.go = "CapComission_Mayor1";
						}	
						if(CheckAttribute(pchar,"GenQuest.CaptainComission.PrisonFree"))
						{
							link.l12 = "前指挥巡逻队" + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")) + "的船长" + pchar.GenQuest.CaptainComission.Name + "同意向当局透露他的藏匿处。 ";
							link.l12.go = "CapComission_Mayor9";
						}
						if(pchar.GenQuest.CaptainComission == "GetGoodsSuccess")
						{
							link.l12 = "前指挥巡逻队" + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")) + "的船长" + pchar.GenQuest.CaptainComission.Name + "向我透露了他的藏匿处。 ";
							link.l12.go = "CapComission_Mayor13";
						}
					}
					if(CheckAttribute(pchar,"GenQuest.ShipWreck") && pchar.GenQuest.ShipWreck == "SailorsOnShore" && GetQuestPastDayParam("GenQuest.ShipWreck") < 25 && sti(npchar.nation) == sti(pchar.GenQuest.ShipWreck.Nation))
					{
						if(!CheckAttribute(pchar,"GenQuest.ShipWreck.SpeakMayor"))
						{
							iDay = GetQuestPastDayParam("GenQuest.ShipWreck");
							if(CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
							{
								link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Dat")) + "我遇到了船长" + pchar.GenQuest.ShipWreck.Name + "和他的水手, 他们被海盗" + pchar.GenQuest.ShipWreck.BadName + "送上了岸。 " +
									"不幸的是, 我的船上已经有太多人, 因此无法让他们上船。 但我给他们留下了食物和武器。 如果救援船在" + (30 - iDay) + "天内没有接他们, 那我不知道是否还能找到活着的他们。 ";
								link.l13.go = "ShipWreck1";
							}
							else
							{
								link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Dat")) + "我遇到了来自'" + pchar.GenQuest.ShipWreck.ShipTypeName + "'号遇难船只的水手和他们的船长。 " + 
									"不幸的是, 我的船上已经有太多人, 因此无法让他们上船。 但我给他们留下了食物和武器。 如果救援船在" + (30 - iDay) + "天内没有接他们, 那我不知道是否还能找到活着的他们。 ";
								link.l13.go = "ShipWreck1";							
							}	
						}	
					}					
					//--> Jason, 生成2级邮政信使
						if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
						{
							if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
							{
							link.l14 = "我有来自" + XI_ConvertString("Colony" + pchar.questTemp.WPU.Postcureer.StartCity + "Gen") + "镇的消息。 ";
							link.l14.go = "Postcureer_LevelUp_ForAll";
							}
						}
					//<—— 生成2级邮政信使
					
					// --> Warship, 16.05.11。 任务"正义待售"
					if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_townhall")
					{
						link.l15 = "大人, 我找到了一群走私者, 他们的头目最近被卫兵抓获。 现在他们正策划营救他。 他们的船'" + PChar.GenQuest.JusticeOnSale.ShipName + "'停泊在" + XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId + "Gen") + "。 ";
						link.l15.go = "JusticeOnSale_1";
					}
					//<—— 正义待售
					
        			if (GetPrisonerQty() > 0)
        			{
                        link.l3 = "我需要把被俘的船长交给当局。 ";
        			    link.l3.go = "sell_prisoner";
        			}
					//Jason --> 帆船赛
					if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
					{
						link.l4 = "我是来参加帆船赛的。 这是我的邀请。 ";
						link.l4.go = "Regata";
					}
        			link.l5 = "也许您想休息一下? ";
        			link.l5.go = "Play_Game";
        			link.l10 = "这只是一次礼节性拜访, " + GetAddress_FormToNPC(NPChar) + "。 ";
        			link.l10.go = "node_2";
                }
    		}//<-
		break;
		
		case "Helen_node_1":
            //殖民地被围攻 homo
			if (CheckAttribute(&Colonies[FindColony(npchar.City)],"Siege"))
            {

                makearef(aData, NullCharacter.Siege);
                

                if (CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                {
                    dialog.text = "我们已经讨论过所有事情了, 不是吗? ";
                    link.l1 = "没错。 我不再耽误您了。 ";
                    link.l1.go = "exit";

                }
                else
                {
                    dialog.text = "很抱歉让您失望, 但我现在没有时间和您交谈。 如您所知, 我们的殖民地遭到了" + NationNamePeople(sti(aData.nation)) + "的袭击。 我必须去处理防御事务。 ";
                    link.l1 = "好吧, 我只是想提供帮助, 保卫堡垒。 ";
                    link.l1.go = "siege_task";
                    link.l2 = "那我不再耽误您了。 ";
        			link.l2.go = "exit";
                }
            }
            else
            {//->
                makearef(aData, NullCharacter.Siege);
                if (CheckAttribute(aData, "PlayerHelpMayor") && sti(aData.PlayerHelpMayor) == true
                && CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                {
                    AddMoneyToCharacter(Pchar,(sti(aData.iSquadronPower)*3000));
                    ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
                    ChangeCharacterComplexReputation(pchar,"nobility", 10);
                    AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 180);
                    AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 200);
                    AddCharacterExpToSkill(GetMainCharacter(), "Accuracy", 200);
                    AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 200);
                    //--> 谣言
                    SiegeRumour("据说您帮助我们击退了" + NationNameSK(sti(aData.nation)) + "的中队, 保卫了我们的殖民地! 我们感谢您, " + GetAddress_Form(NPChar) + "。 ", aData.Colony, sti(aData.conation), -1, 15, 3);
		            //<—— 谣言
                    DeleteAttribute(aData, "PlayerHelpMayor");
                    DeleteAttribute(aData, "HelpColony");
                    dialog.text = "哦, 是您, " + GetAddress_Form(NPChar) + " " + GetFullName(pchar) + ", 很高兴见到您。 好消息 - 我们成功击退了" + NationNameSK(sti(aData.nation)) + "的入侵者。 您也为此出了一份力, 这是您的奖励 - " + (sti(aData.iSquadronPower)*1500) + "八里亚尔。 给您。 ";
                    link.l1 = "谢谢您, " + GetAddress_FormToNPC(NPChar) + ", 很高兴与您合作! ";
                    link.l1.go = "exit";
                }
                else
                {
                    if (CheckAttribute(aData, "PlayerHelpMayor")) DeleteAttribute(aData, "PlayerHelpMayor");
                    dialog.text = "什么风把您吹来了? 我以为您和您的...赞助人处理所有事情。 不过说吧, 我总是乐于倾听。 ";
					if (npchar.city != "Panama") // Addon-2016 Jason
					{
						link.l1 = "我想为" + NationNameGenitive(sti(NPChar.nation)) + "效力。 ";
						link.l1.go = "work";
					}
					// Warship 生成器 "无人岛上的海盗" - 向当局交出海盗
					if(CheckAttribute(PChar, "Quest.PiratesOnUninhabited_OnShore") || CheckAttribute(PChar, "Quest.PiratesOnUninhabited_ShipSink"))
					{
						link.l11 = XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore + "Dat") + "我遇到了一些海盗。 目前所有" + PChar.GenQuest.PiratesOnUninhabited.PiratesCount + "人都在船上。 我想把他们交给当局。 ";
						link.l11.go = "PiratesOnUninhabited_1";
					}
					
        			link.l2 = "我想和您谈谈一件重要的事情。 ";
					if(CheckAttribute(pchar,"questTemp.ReasonToFast") && !CheckAttribute(pchar,"questTemp.ReasonToFast.SpeakOther") && !CheckAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther") && (pchar.questTemp.ReasonToFast.city == NPChar.city))
					{
						link.l2.go = "ReasonToFast_Mayor1";
					}
					else
					{					
						link.l2.go = "quests";
					}	
					if(CheckAttribute(pchar,"GenQuest.CaptainComission") && (pchar.GenQuest.CaptainComission.variant == "A2") && (pchar.GenQuest.CaptainComission.City == NPChar.city))
					{
						if(pchar.GenQuest.CaptainComission == "Begin_1" && !CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor")) 
						{
							link.l12 = "有一位指挥巡逻队" + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")) + "的船长, 名叫" + pchar.GenQuest.CaptainComission.Name + ", 我如何才能见到他? ";
							link.l12.go = "CapComission_Mayor1";
						}	
						if(CheckAttribute(pchar,"GenQuest.CaptainComission.PrisonFree"))
						{
							link.l12 = "前指挥巡逻队" + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")) + "的船长" + pchar.GenQuest.CaptainComission.Name + "同意向当局透露他的藏匿处。 ";
							link.l12.go = "CapComission_Mayor9";
						}
						if(pchar.GenQuest.CaptainComission == "GetGoodsSuccess")
						{
							link.l12 = "前指挥巡逻队" + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")) + "的船长" + pchar.GenQuest.CaptainComission.Name + "向我透露了他的藏匿处。 ";
							link.l12.go = "CapComission_Mayor13";
						}
					}
					if(CheckAttribute(pchar,"GenQuest.ShipWreck") && pchar.GenQuest.ShipWreck == "SailorsOnShore" && GetQuestPastDayParam("GenQuest.ShipWreck") < 25 && sti(npchar.nation) == sti(pchar.GenQuest.ShipWreck.Nation))
					{
						if(!CheckAttribute(pchar,"GenQuest.ShipWreck.SpeakMayor"))
						{
							iDay = GetQuestPastDayParam("GenQuest.ShipWreck");
							if(CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
							{
								link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Dat")) + "我遇到了船长" + pchar.GenQuest.ShipWreck.Name + "和他的水手, 他们被海盗" + pchar.GenQuest.ShipWreck.BadName + "送上了岸。 " +
									"不幸的是, 我的船上已经有太多人, 因此无法让他们上船。 但我给他们留下了食物和武器。 如果救援船在" + (30 - iDay) + "天内没有接他们, 那我不知道是否还能找到活着的他们。 ";
								link.l13.go = "ShipWreck1";
							}
							else
							{
								link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Dat")) + "我遇到了来自'" + pchar.GenQuest.ShipWreck.ShipTypeName + "'号遇难船只的水手和他们的船长。 " + 
									"不幸的是, 我的船上已经有太多人, 因此无法让他们上船。 但我给他们留下了食物和武器。 如果救援船在" + (30 - iDay) + "天内没有接他们, 那我不知道是否还能找到活着的他们。 ";
								link.l13.go = "ShipWreck1";							
							}	
						}	
					}					
					//--> Jason, 生成2级邮政信使
						if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
						{
							if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
							{
							link.l14 = "我有来自" + XI_ConvertString("Colony" + pchar.questTemp.WPU.Postcureer.StartCity + "Gen") + "镇的消息。 ";
							link.l14.go = "Postcureer_LevelUp_ForAll";
							}
						}
					//<—— 生成2级邮政信使
					
					// --> Warship, 16.05.11。 任务"正义待售"
					if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_townhall")
					{
						link.l15 = "大人, 我找到了一群走私者, 他们的头目最近被卫兵抓获。 现在他们正策划营救他。 他们的船'" + PChar.GenQuest.JusticeOnSale.ShipName + "'停泊在" + XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId + "Gen") + "。 ";
						link.l15.go = "JusticeOnSale_1";
					}
					//<—— 正义待售
					
        			if (GetPrisonerQty() > 0)
        			{
                        link.l3 = "我需要把被俘的船长交给当局。 ";
        			    link.l3.go = "sell_prisoner";
        			}
					//Jason --> 帆船赛
					if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
					{
						link.l4 = "我是来参加帆船赛的。 这是我的邀请。 ";
						link.l4.go = "Regata";
					}
        			link.l5 = "也许您想休息一下? ";
        			link.l5.go = "Play_Game";
        			link.l10 = "这只是一次礼节性拜访, " + GetAddress_FormToNPC(NPChar) + "。 ";
        			link.l10.go = "node_2";
                }
    		}//<-
		break;
		
		case "Play_Game":
			//==> 圣米塞里科迪亚来了检查
			if (CheckAttribute(npchar, "quest.SantaMisericordia"))
			{
    			dialog.text = "现在不行! 我们有检查, 德阿拉米达先生在城里。 哦, 每年都是这样, 我做了什么才配得上这个...";
				link.l1 = "如您所说。 我不会打扰您。 ";
				link.l1.go = "exit"; 
				break;
			}
			//<== 圣米塞里科迪亚来了检查
			dialog.text = "嗯, 您更喜欢哪种游戏? ";
			link.l1 = "想玩一局赌大的纸牌游戏吗? ";
			link.l1.go = "Card_Game";
   			link.l2 = "玩扑克小丑掷骰子怎么样? ";
			link.l2.go = "Dice_Game";
			link.l10 = "请原谅, 但是职责在身。 ";
			link.l10.go = "exit";
		break;
		
		// 纸牌 -->
        case "Card_Game":
            if (!CheckNPCQuestDate(npchar, "Card_date_Yet") || sti(PChar.rank) < 4 || isBadReputation(pchar, 50) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(5))
            {
                SetNPCQuestDate(npchar, "Card_date_Yet");
				// belamour legendary edition 修复检查带有滑膛枪的制服
				if(IsUniformEquip()) dialog.text = "请原谅, 大人, 但我现在没有时间。 也许下次吧。 "; // Jason НСО
                else dialog.text = "我不与海盗赌博! ";
    			link.l1 = "如您所愿。 ";
    			link.l1.go = "exit";
			}
			else
			{
				if (CheckNPCQuestDate(npchar, "Card_date_begin"))
				{
					dialog.text = "为什么不呢! 放松对心脏有好处, 但对钱包没好处...";
	    			link.l1 = "太好了。 ";
	    			link.l1.go = "Cards_begin";
	    			link.l2 = "我们的游戏规则是什么? ";
	    			link.l2.go = "Cards_Rule";
    			}
    			else
    			{
					dialog.text = "不, 我今天玩够了。 我有事情要做。 ";
	    			link.l1 = "如您所愿。 ";
	    			link.l1.go = "exit";
				}
			}
		break;

		case "Cards_Rule":
   			dialog.text = CARDS_RULE;
			link.l1 = "好吧, 那我们开始吧! ";
			link.l1.go = "Cards_begin";
			link.l3 = "不, 这不适合我...";
			link.l3.go = "exit";
		break;

		case "Cards_begin":
			dialog.text = "首先, 我们来约定赌注。 ";
			link.l1 = "我们赌1000八里亚尔吧。 ";
			link.l1.go = "Cards_Node_100";
			link.l2 = "我们赌5000八里亚尔吧。 ";
			link.l2.go = "Cards_Node_500";
			link.l3 = "我想我得走了。 ";
			link.l3.go = "exit";
		break;

		case "Cards_Node_100":
			//belamour legendary edition 
			bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
			bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
			bOk = bOk1 || bOk2;
            if (!CheckCardsGameSmallRate() && !bOk)
		    {
                dialog.text = "您是个臭名昭著的骗子。 我不会和您赌博。 ";
                link.l1 = "都是谎言! ";
			    link.l1.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 3000)
		    {
                dialog.text = "您在开玩笑吗, " + GetAddress_Form(NPChar) + "? 您没有钱! ";
                link.l1 = "事情就是这样。 ";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 3000)
		    {
                dialog.text = "够了! 我玩牌玩够了 - 免得他们叫我败家子, 逼我离职。 ";
                link.l1 = "可惜。 ";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "好的, 我们赌1000八里亚尔。 ";
			link.l1 = "我们开始吧! ";
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 1000;
            pchar.GenQuest.Cards.SitType   = false;
		break;

		case "Cards_Node_500":
			//belamour legendary edition 
			bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
			bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
			bOk = bOk1 || bOk2;
            if (!CheckCardsGameSmallRate() && !bOk)
		    {
                dialog.text = "您是个臭名昭著的骗子。 我不会和您赌博。 ";
                link.l1 = "都是谎言! 好吧, 不管了。 ";
			    link.l1.go = "exit";
			    break;
		    }
			if (!CheckCardsGameBigRate())
		    {
                dialog.text = "据说您是个非常好的玩家。 我不会和您下大赌注。 ";
                link.l1 = "也许我们降低赌注? ";
			    link.l1.go = "Cards_Node_100";
				link.l2 = "对不起, 我得走了。 ";
			    link.l2.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 15000)
		    {
                dialog.text = "您在开玩笑吗, " + GetAddress_Form(npchar) + "? 您没有15000八里亚尔! ";
                link.l1 = "我会筹集的! ";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 15000)
		    {
                dialog.text = "不, 这些赌注会掏空城市财政。 ";
                link.l1 = "如您所愿。 ";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "好的, 我们赌5000八里亚尔。 ";
			link.l1 = "我们开始吧! ";
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 5000;
            pchar.GenQuest.Cards.SitType   = false;
		break;

		case "Cards_begin_go":
            SetNPCQuestDate(npchar, "Card_date_begin");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
            LaunchCardsGame();
		break;
	    // 纸牌 <--

	    // 骰子 -->
        case "Dice_Game":
            if (!CheckNPCQuestDate(npchar, "Dice_date_Yet") || sti(PChar.rank) < 4 || isBadReputation(pchar, 50) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(5))
            {
                SetNPCQuestDate(npchar, "Dice_date_Yet");
				// belamour legendary edition 修复检查带有滑膛枪的制服
				if(IsUniformEquip()) dialog.text = "请原谅, 大人, 但我现在没有时间。 也许下次吧。 "; // Jason НСО
                else dialog.text = "我不会与海盗赌博! ";
    			link.l1 = "如您所愿。 ";
    			link.l1.go = "exit";
			}
			else
			{
				if (CheckNPCQuestDate(npchar, "Dice_date_begin"))
				{
					dialog.text = "为什么不呢! 放松对心脏有好处... 但对钱包没好处...";
	    			link.l1 = "太好了。 ";
	    			link.l1.go = "Dice_begin";
	    			link.l2 = "我们的游戏规则是什么? ";
	    			link.l2.go = "Dice_Rule";
    			}
    			else
    			{
					dialog.text = "不, 我今天玩够了。 我有事情要做。 ";
	    			link.l1 = "如您所愿。 ";
	    			link.l1.go = "exit";
				}
			}
		break;

		case "Dice_Rule":
   			dialog.text = DICE_RULE;
			link.l1 = "好吧, 那我们开始吧! ";
			link.l1.go = "Dice_begin";
			link.l3 = "不, 这不适合我...";
			link.l3.go = "exit";
		break;

		case "Dice_begin":
			dialog.text = "首先, 我们来约定赌注。 ";
			link.l1 = "我们每颗骰子赌500八里亚尔吧。 ";
			link.l1.go = "Dice_Node_100";
			link.l2 = "我们每颗骰子赌2000八里亚尔吧。 ";
			link.l2.go = "Dice_Node_500";
			link.l3 = "我想我得走了。 ";
			link.l3.go = "exit";
		break;

		case "Dice_Node_100":
			//belamour legendary edition 
			bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
			bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
			bOk = bOk1 || bOk2;
            if (!CheckDiceGameSmallRate() && !bOk)
		    {
                dialog.text = "您是个臭名昭著的骗子。 我不会和您赌博。 ";
                link.l1 = "都是谎言! 好吧, 不管了。 ";
			    link.l1.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 3000)
		    {
                dialog.text = "您在开玩笑吗, " + GetAddress_Form(NPChar) + "? 您没有钱! ";
                link.l1 = "事情就是这样。 ";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 3000)
		    {
                dialog.text = "够了! 我赌博玩够了 - 免得他们叫我败家子, 逼我离职...";
                link.l1 = "可惜。 ";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "好的, 我们赌500八里亚尔。 ";
			link.l1 = "我们开始吧! ";
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
            pchar.GenQuest.Dice.iRate     = 500;
            pchar.GenQuest.Dice.SitType   = false;
		break;

		case "Dice_Node_500":
			//belamour legendary edition 
			bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
			bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
			bOk = bOk1 || bOk2;
            if (!CheckDiceGameSmallRate() && !bOk)
		    {
                dialog.text = "您是个臭名昭著的骗子。 我不会和您赌博。 ";
                link.l1 = "都是谎言! 好吧, 不管了。 ";
			    link.l1.go = "exit";
			    break;
		    }
			if (!CheckDiceGameBigRate())
		    {
                dialog.text = "据说您是个非常好的玩家。 我不会和您下大赌注。 ";
                link.l1 = "也许我们降低赌注? ";
			    link.l1.go = "Dice_Node_100";
				link.l2 = "对不起, 我得走了。 ";
			    link.l2.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 15000)
		    {
                dialog.text = "您在开玩笑吗, " + GetAddress_Form(NPChar) + "? 您没有15000八里亚尔! ";
                link.l1 = "我会筹集的! ";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 15000)
		    {
                dialog.text = "不, 这些赌注肯定会掏空城市财政。 ";
                link.l1 = "如您所愿。 ";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "好的, 我们每颗骰子赌2000八里亚尔。 ";
			link.l1 = "我们开始吧! ";
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
            pchar.GenQuest.Dice.iRate     = 2000;
            pchar.GenQuest.Dice.SitType   = false;
		break;

		case "Dice_begin_go":
            SetNPCQuestDate(npchar, "Dice_date_begin");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
            LaunchDiceGame();
		break;
	    // 骰子 <--
		case "node_2":
			dialog.text = "在这种情况下, 我请您离开我的书房, 不要再打扰我工作";
			link.l1 = "是的, 是的, 当然。 抱歉打扰您。 ";
			link.l1.go = "exit";
		break;

		//--------------------------—— 市长任务生成器 -------------------------------
		case "work": 
            dialog.text = "这是一个错误。 请通知开发人员。 ";
        	link.l1 = "谢谢, 这是一个很棒的游戏! ";
        	link.l1.go = "exit";
			
			//==> 圣米塞里科迪亚来了检查
			if (CheckAttribute(npchar, "quest.SantaMisericordia"))
			{
    			dialog.text = "现在不行! 我们有检查, 德阿拉米达先生在城里。 哦, 每年都是这样, 我做了什么才配得上这个...";
				link.l1 = "如您所说。 我不会打扰您。 ";
				link.l1.go = "exit"; 
				break;
			}
			//<== 圣米塞里科迪亚来了检查
			//==> 是否接受了任何任务
			if (CheckAttribute(pchar, "GenQuest.questName"))
			{		 				
				//--> 费多特, 不是那个
				QuestName = pchar.GenQuest.questName;
				if (pchar.GenQuest.(QuestName).MayorId != npchar.id) 
				{					
					dialog.text = RandPhraseSimple("据我所知, 您已经有了" + XI_ConvertString("Colony" + characters[GetCharacterIndex(pchar.GenQuest.(QuestName).MayorId)].city + "Gen") + "总督给您的任务。 完成您已有的工作, 我们再谈。 ", 
						"嗯, 您不是在" + XI_ConvertString("Colony" + characters[GetCharacterIndex(pchar.GenQuest.(QuestName).MayorId)].city + "Voc") + "从当地总督那里接受命令的吗? 是的, 没错。 先完成那个任务。 ");
					link.l1 = RandPhraseSimple("我明白...", "了解..."+ GetSexPhrase("","") +", "+ GetAddress_FormToNPC(NPChar) + "。 ");
					link.l1.go = "exit";					
					break;
				}
				//<--费多特, 不是那个
				//------—— 接受消灭帮派任务 ---------->>
				if (QuestName == "DestroyGang")
				{
					switch (pchar.GenQuest.DestroyGang)
					{
						makearef(arName, pchar.GenQuest.DestroyGang);
						case "":
							dialog.text = LinkRandPhrase("已经向您发出了定位强盗" + GetFullName(arName) + "的任务。 现在去完成它! ", 
								"您已经有了定位名叫" + GetFullName(arName) + "的强盗的任务。 我在等待结果! ", 
								"当您在我住所浪费时间时, " + GetFullName(arName) + "正在抢劫我们的殖民者! 去工作! ");
							link.l1 = RandPhraseSimple("好的, " + GetAddress_FormToNPC(NPChar) + "。 ", "我在忙于此事, " + GetAddress_FormToNPC(NPChar) + "。 ");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("给您定位和消灭那个强盗的时间已经结束。 您认为我收到的是什么报告? 我来告诉您 - " + GetFullName(arName) + "还活着! 现在解释一下, " + GetAddress_Form(NPChar) + "。 ",
								"给您消灭那个名叫" + GetFullName(arName) + "的恶棍的时间已经用完了。 但我被告知根本没有取得任何进展。 怎么回事? ");
							link.l1 = "我未能在指定时间内完成您的工作, " + GetAddress_FormToNPC(NPChar) + "。 ";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("那么, 您怎么说? 您设法消灭了提到的强盗吗? " + GetFullName(arName) + "终于死了? ", "告诉我一件事 - " + GetFullName(arName) + "是死是活? ");
							link.l1 = "不幸的是, 还活着, " + GetAddress_FormToNPC(NPChar) + "。 我设法找到了他, 但我寡不敌众, 被迫撤退。 那个强盗真的很厉害。 我很抱歉。 ";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("那么, 您怎么说? 您设法消灭了提到的强盗吗? " + GetFullName(arName) + "终于死了? ", "告诉我一件事 - " + GetFullName(arName) + "是死是活? ");
							link.l1 = "他死了, " + GetAddress_FormToNPC(NPChar) + "。 ";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 180);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
						break;
					}
				}
				//------—— 反信使 ---------->>
				if (QuestName == "TakePostcureer")
				{
					switch (pchar.GenQuest.TakePostcureer)
					{
						case "":
							dialog.text = LinkRandPhrase("已经向您发出了捕获信使船的任务。 现在去完成它! ", 
								"您已经有了捕获信使船的任务! 我在等待结果! ", 
								"当您在我住所浪费时间时, 我需要的文件正落入我们敌人手中! 去工作! ");
							link.l1 = RandPhraseSimple("好的, " + GetAddress_FormToNPC(NPChar) + "。 ", "我在忙于此事, " + GetAddress_FormToNPC(NPChar) + "。 ");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("给您定位和捕获那艘信使船的时间已经结束。 您认为我收到的是什么报告? 我来告诉您 - 我期待的文件落入了我们敌人手中! 现在请您解释一下, " + GetAddress_Form(NPChar) + "。 ",
								"给您从信使船上获取文件的所有期限都已过期。 但仍然没有任何进展。 这是什么情况? ");
							link.l1 = "我未能及时完成工作, " + GetAddress_FormToNPC(NPChar) + "。 ";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("那么, 您怎么说? 您设法捕获了文件吗? ", "告诉我一件事 - 您设法获取了信件吗? ");
							link.l1 = "不幸的是, 没有, " + GetAddress_FormToNPC(NPChar) + "。 我已经找到了船, 但文件从我手中溜走了。 ";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("那么, 您怎么说? 您设法捕获了文件吗? ", "告诉我一件事 - 您设法获取了信件吗? ");
							link.l1 = "是的, " + GetAddress_FormToNPC(NPChar) + "。 我拿到了。 给您。 ";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 200);
							AddCharacterExpToSkill(PChar, "Fortune", 300);
							AddCharacterExpToSkill(PChar, "Sneak", 150);
							RemoveItems(pchar, "ContraPostLetters", 1);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
						break;
					}
				}
				//------—— 反走私 - 军火运输 ---------->>
				if (QuestName == "TakeArsenalship")
				{
					switch (pchar.GenQuest.TakeArsenalship)
					{
						case "":
							dialog.text = LinkRandPhrase("已经向你下达了摧毁军事运输船的任务。 现在去完成它! ", 
								"你已经有摧毁军事运输船的任务了! 我在等结果! ", 
								"当你在我住所浪费时间时, 火药和弹药正被直接运送到敌人的大炮那里! 快去工作! ");
							link.l1 = RandPhraseSimple("好的, " + GetAddress_FormToNPC(NPChar) + "。 ", "我正在处理, " + GetAddress_FormToNPC(NPChar) + "。 ");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("你被给予定位和摧毁那艘军事运输船的时间已经结束了。 你觉得我收到的是什么报告? 我告诉你 - 敌人的护航队已经成功抵达目的地! 现在请你解释一下, " + GetAddress_Form(NPChar) + "。 ",
								"所有给予你摧毁敌人军事运输船的期限都已过期。 仍然完全没有进展。 怎么回事? ");
							link.l1 = "我未能在规定时间内执行你的任务, " + GetAddress_FormToNPC(NPChar) + "。 ";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("那么, 你怎么说? 你成功摧毁了敌人的运输船吗? ", "告诉我一件事 - 敌人的物资是否沉在海底了? ");
							link.l1 = "很遗憾, 没有, " + GetAddress_FormToNPC(NPChar) + "。 我已经定位到护航队, 但未能击沉所需的船只。 ";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("那么, 你怎么说? 你成功摧毁了那艘敌人的运输船吗? ", "告诉我一件事 - 敌人的军火是否沉在海底了? ");
							link.l1 = "是的, " + GetAddress_FormToNPC(NPChar) + "。 我们的敌人不会收到那些火药和弹药了。 ";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 220);
							AddCharacterExpToSkill(PChar, "Fortune", 300);
							AddCharacterExpToSkill(PChar, "Sneak", 150);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
						break;
					}
				}
				//------—— 海岸警卫队 - 海盗 ---------->>
				if (QuestName == "TakePirateship")
				{
					switch (pchar.GenQuest.TakePirateship)
					{
						case "":
							dialog.text = LinkRandPhrase("已经向你下达了消灭海盗的任务。 现在去完成它! ", 
								"你已经有摧毁海盗船的任务了! 我在等结果! ", 
								"当你在我住所浪费时间时, 那个肮脏的海盗正在掠夺另一个受害者! 快去工作! ");
							link.l1 = RandPhraseSimple("好的, " + GetAddress_FormToNPC(NPChar) + "。 ", "我正在处理, " + GetAddress_FormToNPC(NPChar) + "。 ");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("你被给予定位和消灭海盗的时间已经结束了。 你觉得我收到的是什么报告? 我告诉你 - 那个肮脏的海盗还在袭击我们的船只! 现在请你解释一下, " + GetAddress_Form(NPChar) + "。 ",
								"所有给予你摧毁海盗船的期限都已过期。 仍然完全没有进展。 怎么回事? ");
							link.l1 = "我未能及时完成你的工作, " + GetAddress_FormToNPC(NPChar) + "。 ";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("那么, 你怎么说? 你成功摧毁了海盗船吗? ", "告诉我一件事 - 那个肮脏的海盗终于沉在海底了吗? ");
							link.l1 = "很遗憾, 没有, " + GetAddress_FormToNPC(NPChar) + "。 我设法找到了那个恶棍, 但未能击沉他的船。 ";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("那么, 你怎么说? 你成功摧毁了海盗船吗? ", "告诉我一件事 - 那个肮脏的海盗终于沉在海底了吗? ");
							link.l1 = "是的, " + GetAddress_FormToNPC(NPChar) + "。 那个恶棍再也不会困扰我们的商船了。 ";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 250);
							AddCharacterExpToSkill(PChar, "Fortune", 300);
							AddCharacterExpToSkill(PChar, "Sneak", 150);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
						break;
					}
				}
					//------—— 海岸警卫队 - 乘客 ---------->>
				if (QuestName == "TakePassenger")
				{
					switch (pchar.GenQuest.TakePassenger)
					{
						case "":
							dialog.text = LinkRandPhrase("已经向你下达了搜寻罪犯的任务。 现在去完成它! ", 
								"你已经有搜寻罪犯的任务了! 我在等结果! ", 
								"当你在我住所浪费时间时, 那个肮脏的恶棍还在航行! 立即着手执行委托给你的任务! ");
							link.l1 = RandPhraseSimple("好的, " + GetAddress_FormToNPC(NPChar) + "。 ", "我正在处理, " + GetAddress_FormToNPC(NPChar) + "。 ");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("你被给予定位那个恶棍的时间已经结束了。 你觉得我收到的是什么报告? 我告诉你 - 他成功到达了目的地, 然后消失得无影无踪! 现在请你解释一下, " + GetAddress_Form(NPChar) + "。 ",
								"所有给予你寻找罪犯的期限都已过期。 仍然完全没有进展。 怎么回事? ");
							link.l1 = "我未能在上述时间内执行你的任务, " + GetAddress_FormToNPC(NPChar) + "。 ";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("那么, 你怎么说? 你抓住那个恶棍了吗? ", "告诉我一件事 - 那个肮脏的恶棍是否被堵嘴戴镣铐在你的船舱里? ");
							link.l1 = "很遗憾, 没有, " + GetAddress_FormToNPC(NPChar) + "。 我未能抓住那个恶棍。 他和他所在的船一起沉没了。 ";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("那么, 你怎么说? 你抓住那个恶棍了吗? ", "告诉我一件事 - 那个肮脏的恶棍是否被堵嘴戴镣铐在你的船舱里? ");
							link.l1 = "是的, " + GetAddress_FormToNPC(NPChar) + "。 请派你的士兵到码头, 我会把他交给你。 ";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 250);
							AddCharacterExpToSkill(PChar, "Fortune", 300);
							AddCharacterExpToSkill(PChar, "Sneak", 200);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
							sld = &Characters[sti(Pchar.GenQuest.TakePassenger.PrisonerIDX)];
							ReleasePrisoner(sld); //释放了囚犯
							sld.lifeday = 0;
						break;
					}
				}
				//------—— 海关巡逻 ---------->>
				if (QuestName == "CustomPatrol")
				{
					switch (pchar.GenQuest.CustomPatrol)
					{
						case "":
							dialog.text = LinkRandPhrase("已经向你下达了搜寻走私者的任务。 现在去完成它! ", 
								"你已经有搜寻走私者的任务了! 我在等结果! ", 
								"当你在我住所浪费时间时, 那些走私者正在准备进行另一笔交易! 立即着手执行委托给你的任务! ");
							link.l1 = RandPhraseSimple("好的, " + GetAddress_FormToNPC(NPChar) + "。 ", "我正在处理, " + GetAddress_FormToNPC(NPChar) + "。 ");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("你被给予定位走私者的时间已经结束了。 你觉得我收到的是什么报告? 我告诉你 - 他们已经愉快地卖掉了所有货物! 现在请你解释一下, " + GetAddress_Form(NPChar) + "。 ",
								"所有给予你寻找走私者的期限都已过期。 仍然完全没有进展。 怎么回事? ");
							link.l1 = "我未能及时执行你的任务, " + GetAddress_FormToNPC(NPChar) + "。 ";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("那么, 你怎么说? 你已经处理了走私者吗? ", "告诉我一件事 - 你已经破坏了那些走私者的交易吗? ");
							link.l1 = "很遗憾, 没有, " + GetAddress_FormToNPC(NPChar) + "。 我未能挫败那些恶棍的计划。 ";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("那么, 你怎么说? 你已经处理了走私者吗? ", "告诉我一件事 - 你已经破坏了那些走私者的交易吗? ");
							link.l1 = "是的, " + GetAddress_FormToNPC(NPChar) + "。 我追上了他们, 消灭了买卖双方的船只。 ";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 200);
							AddCharacterExpToSkill(PChar, "Fortune", 300);
							AddCharacterExpToSkill(PChar, "Sneak", 300);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
						break;
					}
				}
				//------—— 逃兵 ---------->>
				if (QuestName == "FindFugitive")
				{
					switch (pchar.GenQuest.FindFugitive)
					{
						case "":
							dialog.text = LinkRandPhrase("已经向你下达了搜寻逃兵的任务。 现在去完成它! ", 
								"你已经有搜寻逃兵的任务了! 我在等结果! ", 
								"当你在我住所浪费时间时, 那个逃兵可能正在背叛我们的国家机密! 立即着手执行委托给你的任务! ");
							link.l1 = RandPhraseSimple("好的, " + GetAddress_FormToNPC(NPChar) + "。 ", "我正在处理, " + GetAddress_FormToNPC(NPChar) + "。 ");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("你被给予定位逃兵的时间已经结束了。 你觉得我收到的是什么报告? 我告诉你 - 没有结果, 完全没有! 现在请你解释一下, " + GetAddress_Form(NPChar) + "。 ",
								"所有给予你寻找逃兵的期限都已过期。 仍然完全没有进展。 怎么回事? ");
							link.l1 = "我未能及时完成你的工作, " + GetAddress_FormToNPC(NPChar) + "。 ";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("那么, 你怎么说? 你已经抓住逃兵了吗? ", "告诉我一件事 - 那个逃兵是否被堵嘴戴镣铐在你的船舱里? ");
							link.l1 = "很遗憾, 没有, " + GetAddress_FormToNPC(NPChar) + "。 我未能抓住那个恶棍。 我在" + XI_ConvertString("Colony" + pchar.GenQuest.FindFugitive.City) + "的定居点找到了他的踪迹, 但就在我到达的前一天, 他乘海盗船向南去了。 我猜他现在和那些幸运的先生们在一起。 ";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("哦, 好吧... 这是我们的" + pchar.GenQuest.FindFugitive.Name + "... 干得好, 船长! 你搜寻得很辛苦吗? ", "哦, 我们有客人了! 你好, " + pchar.GenQuest.FindFugitive.Name + "! 干得好, 船长! 你在搜寻上花了很多精力吗? ");
							link.l1 = "怎么说呢, " + GetAddress_FormToNPC(NPChar) + "。 不管怎样 - 你的任务已经完成了。 ";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 300);
							AddCharacterExpToSkill(PChar, "Fortune", 300);
							AddCharacterExpToSkill(PChar, "Sneak", 200);
							ChangeCharacterComplexReputation(pchar, "authority", 1);
							sld = &Characters[sti(Pchar.GenQuest.FindFugitive.PrisonerIDX)];
							ReleasePrisoner(sld); //释放了囚犯
							LAi_SetActorType(sld);
							sld.lifeday = 0;
							pchar.quest.FindFugitive_Over.over = "yes"; //移除计时器
							chrDisableReloadToLocation = false;//打开位置
						break;
					}
				}
				//----—— 潜入敌对城市 ------------>>
				if (QuestName == "Intelligence")
				{
					switch (pchar.GenQuest.Intelligence)
					{
						case "":
							if (GetQuestPastDayParam("GenQuest.Intelligence") > sti(pchar.GenQuest.Intelligence.Terms))
							{
								dialog.text = RandPhraseSimple("你被给予送信的时间已经结束了。 我想你已经失败了。 ",
									"时间已经用完了。 仍然完全没有进展。 怎么回事? ");
								link.l1 = "我未能完成你的工作, " + GetAddress_FormToNPC(NPChar) + "。 ";
								link.l1.go = "All_Late";	
							}
							else
							{
								dialog.text = LinkRandPhrase("已经向你下达了给我送信的任务。 现在去完成它! ", 
									"你已经有直接给我送信的任务了! 我在等结果, 我急需那封信! ", 
									"当你在我住所浪费时间时, 我急需的信息还在应该寄给我的人手中! 立即着手执行委托给你的任务! ");
								link.l1 = RandPhraseSimple("好的, " + GetAddress_FormToNPC(NPChar) + "。 ", "我会马上处理, " + GetAddress_FormToNPC(NPChar) + "。 ");
								link.l1.go = "exit";	
							}
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("你把我期待的信送来了吗? ", "现在告诉我 - 你有吗? ! ");
							link.l1 = "是的, 我有。 正如我们约定的 - 亲自交给你。 ";
							if (GetQuestPastDayParam("GenQuest.Intelligence") > sti(pchar.GenQuest.Intelligence.Terms))
							{
								link.l1.go = "Intelligence_ExecuteLate";
								AddCharacterExpToSkill(PChar, "Sneak", 300);
							}
							else
							{
								link.l1.go = "All_Execute";		
								AddCharacterExpToSkill(PChar, "Leadership", 100);
								AddCharacterExpToSkill(PChar, "Sneak", 300);
							}
							TakeItemFromCharacter(pchar, "sicretLetter");
							DeleteAttribute(ItemsFromID("sicretLetter"), "City");
							DeleteAttribute(ItemsFromID("sicretLetter"), "Mayor");
						break;
					}
				}
				break;
			}
			sTemp = npchar.city;
			//占用市长任务
			i = CheckAvailableTaskForNPC(NPChar, PGG_TASK_WORKONMAYOR);
			if (i != -1)
			{
				dialog.text = "唉, 今天我没有给你的工作。 最后一个已经被" + GetFullName(&Characters[i])
					+ "完成了。 明天再来吧, 也许会有什么出现。 ";
				link.l1 = "哦, 该死! 运气不好...";
				link.l1.go = "exit";
				break;
			}
//海军 <--
			if (!CheckAttribute(npchar, "work_date") || GetNpcQuestPastDayParam(npchar, "work_date") > 2 || bBettaTestMode)
			{	
				SaveCurrentNpcQuestDateParam(npchar, "work_date");
				if(CheckAttribute(pchar, "questTemp.StatusCity") && pchar.questTemp.StatusCity == npchar.city)
				{
					dialog.text = "你来得正好, 船长。 我必须处理一个与向我们的殖民地走私货物有关的紧急问题。 我想你的船适航并且准备好战斗。 ";
					link.l1 = "我的船总是适航并准备好战斗。 请告诉我更多关于即将到来的任务的信息, 大人。 ";
					link.l1.go = "CustomPatrol";
					break;
				}
				if (rand(5) > 4 && !bBettaTestMode && pchar.location == "Panama_townhall") // patch-5
				{
					dialog.text = LinkRandPhrase("目前我没有给你的工作。 明天再来吧, 我想...", 
						"唉, 今天我没有给你的工作。 请在一两天后再来检查。 ", 
						"今天没有我能给你的提议。 改天我会很高兴见到你。 ");
					link.l1 = "我明白, " + GetAddress_FormToNPC(NPChar) + "。 ";
					link.l1.go = "exit";
				}
				else
				{
					sTemp = GetSpyColony(npchar);
					// 如果主角的国家没有敌人, 就不给予潜入敌对城市的任务
					if (sTemp == "none")
						i = 1 + hrand(6);
					else
						i = hrand(7);
					switch (i)
					{
						//========== 潜入敌对城市 ============//Jason: 保留, 因为合适
						case 0:
							pchar.GenQuest.Intelligence.Terms = hrand(10) + (42 - MOD_SKILL_ENEMY_RATE); //任务执行期限
							pchar.GenQuest.Intelligence.Money = ((hrand(4) + 6) * 2000) + (sti(pchar.rank) * 1000 + 10000); //报酬
							pchar.GenQuest.Intelligence.City = sTemp; //敌对殖民地
							sTemp = ", 位于" + XI_ConvertString(colonies[FindColony(pchar.GenQuest.Intelligence.City)].islandLable + "Dat");						 
							dialog.text = "我有一个任务给你, 这需要一些严重的风险。 我需要你潜入" + XI_ConvertString("Colony" + pchar.GenQuest.Intelligence.City + "Acc") + sTemp + ", 在那里会见某个人, 然后把他给你的任何东西交给我。 ";
							link.l1 = "嗯, 我认为在" + XI_ConvertString("Colony" + pchar.GenQuest.Intelligence.City + "Dat") + "我不会是受欢迎的客人...";
							link.l1.go = "Intelligence";
						break;
						//========== 摧毁帮派任务 ============ //Jason: 保留, 作为经典
						case 1:
							pchar.GenQuest.DestroyGang.Terms = hrand(2) + 2; //任务执行期限
							pchar.GenQuest.DestroyGang.Money = ((hrand(6)+4)*500)+(sti(pchar.rank)*300+2000); //报酬
							makearef(arName, pchar.GenQuest.DestroyGang);
							arName.nation = PIRATE;
							arName.sex = "man";
							SetRandomNameToCharacter(arName); //帮派成员名字存入任务结构
							dialog.text = "现在我有一个任务给你。 在" + XI_ConvertString("Colony" + npchar.city + "Gen") + "附近的丛林中出现了一伙强盗, 我知道其头目名叫" + GetFullName(arName) + "。 定位并消灭这伙暴徒。 ";
							link.l1 = "我在期限上有什么限制吗? ";
							link.l1.go = "DestroyGang";
						break;
						
						//========== 反信使 - 截取邮件 ============
						case 2:
							dialog.text = "是的, 我有一个任务给你。 要完成它, 你必须表现出敏捷性和一些海战技巧。 你准备好展示你的价值了吗? ";
							link.l1 = "大人, 你能透露更多关于任务的细节吗? ";
							link.l1.go = "TakePostcureer";
						break;
						
						//========== 反走私 - 击沉军火船 ============
						case 3:
							dialog.text = "是的, 我有一个任务给你。 要完成它, 你必须表现出卓越的勇气和一些海战技巧。 你准备好展示你的价值了吗? ";
							link.l1 = "大人, 你能透露更多关于即将到来的任务的细节吗? ";
							link.l1.go = "TakeArsenalship";
						break;
						//========== 海岸警卫队 - 海盗猎手 ============
						case 4:
							dialog.text = "是的, 我有一个重要的任务给你。 要完成它, 你必须运用你所有的技能。 这涉及到海盗...";
							link.l1 = "海盗? 那你能告诉我更多关于对我的期望吗? ";
							link.l1.go = "TakePirateship";
						break;
						//========== 海岸警卫队 - 乘客猎手 ============
						case 5:
							dialog.text = "你来得正好, 先生。 我有一个紧急任务, 非常适合你。 它涉及到寻找和捕捉某个人...";
							link.l1 = "追捕? 你能告诉我更多关于对我的期望吗? ";
							link.l1.go = "TakePassenger";
						break;
						//========== 巡逻 - 海关人员 ============
						case 6:
							dialog.text = "你来得正好, 船长。 我必须处理一个与向我们的殖民地走私货物有关的紧急问题。 我想你的船适航并且准备好战斗? ";
							link.l1 = "我的船总是适航并准备好战斗。 请告诉我更多关于即将到来的任务的信息, 大人。 ";
							link.l1.go = "CustomPatrol";
						break;
							//========== 寻找逃兵 ============
						case 7:
							dialog.text = "我有一个任务给你, 这需要访问加勒比海的几个定居点。 你准备好长途旅行了吗? ";
							link.l1 = "是的, 我和我的人准备好马上出发了? 我具体要做什么? ";
							link.l1.go = "FindFugitive";
						break;
					}
				}
			}
			else
			{
				dialog.text = LinkRandPhrase("今天我不能给你任何工作。 ", "今天没有更多的工作给你了。 ", "今天没有更多工作了, 抱歉。 明天再来, 我们会看看...");
				link.l1 = RandPhraseSimple("可惜...", "啊, 真可惜, " + GetAddress_FormToNPC(NPChar) + "。 ");
				link.l1.go = "exit";
			}
		//--------------------------—— 市长任务生成器 -------------------------------
		break;

		case "sell_prisoner":
			dialog.text = "你想赎回谁? ";

            qty = 1;
            for(i=0; i < GetPassengersQuantity(pchar); i++)
            {
                cn = GetPassenger(pchar,i);
                if(cn != -1)
                {
                    offref = GetCharacter(cn);
                    if(CheckAttribute(offref,"prisoned"))
                    {
						if(sti(offref.prisoned)==true && GetRemovable(offref)) // 只设置幻影
						{
                            attrLoc = "l"+qty;
							link.(attrLoc)	= GetFullName(offref) + " - " + NationNameMan(sti(offref.nation)) + "。 ";
                            link.(attrLoc).go = "GetPrisonerIdx_" + offref.index;
                            qty++;
                        }
                    }
                }
            }
			link.l99 = "没有人。 ";
			link.l99.go = "exit";
		break;
		
		case "sell_prisoner_2":
            offref = GetCharacter(sti(pchar.GenQuest.GetPrisonerIdx));
			attrLoc =  "那么, 这是" + GetFullName(offref) + "船长, " + NationNameMan(sti(offref.nation)) + "。 ";
			// 价格取决于总督
            qty = makeint(sti(offref.rank)*(800 + GetCharacterSPECIALSimple(NPChar, SPECIAL_L)*100) + GetCharacterSkillToOld(offref, "Leadership")*500 + GetCharacterSkillToOld(pchar, "commerce")*500);
			if(HasShipTrait(pchar, "trait14")) qty = makeint(qty * 1.35);
            if (sti(offref.nation) == sti(NPChar.nation))
            {
				attrLoc = attrLoc + " 我准备为我的同胞支付" + FindRussianMoneyString(qty) + "的赎金。 ";
            }
            else
            {
                if (sti(offref.nation) == PIRATE)
                {
                    qty = qty / 5;
					attrLoc = attrLoc + " 我可以为这个绞刑犯支付" + FindRussianMoneyString(qty) + "。 然后我们会立即处决这个恶棍。 ";

                }
                else
                {
                    qty = qty / 2;
					attrLoc = attrLoc + " " + FindRussianMoneyString(qty) + "买那个人, 不多一分钱。 ";
                }
            }
			dialog.text = attrLoc;
			pchar.PrisonerSellPrice =  qty;
			link.l1 = "成交。 他是你的了, " + GetAddress_FormToNPC(NPChar) + "。 ";
			link.l1.go = "sell_prisoner_3";
			link.l3 = "不。 那不行。 ";
			link.l3.go = "exit";
		break;


		case "sell_prisoner_3":
			dialog.text = "那很好。 ";
			link.l1 = "万事如意。 ";
			link.l1.go = "exit";
			OfficersReaction("bad");

			offref = GetCharacter(sti(pchar.GenQuest.GetPrisonerIdx));
			AddMoneyToCharacter(pchar, sti(pchar.PrisonerSellPrice));
			if (sti(offref.nation) == sti(NPChar.nation))
            {
                AddCharacterExpToSkill(pchar, "Commerce", 25);
            }
            else
            {
                if (sti(offref.nation) == PIRATE)
                {
                    ChangeCharacterComplexReputation(pchar,"nobility", -2);
                }
                else
                {
                    AddCharacterExpToSkill(pchar, "Commerce", 5);
                }
            }

			offref.location = "";
			ReleasePrisoner(offref); // 释放了囚犯
		break;
		////   占领 //////////
		case "CAPTURE_Main":
            NextDiag.TempNode = "CAPTURE_Main";
			AfterTownBattle();  // 一切, 所有人都自由了
			
			// --> 勒瓦瑟
			if (pchar.location == "Tortuga_townhall" && CheckAttribute(pchar, "questTemp.Sharlie.Hardcore_Tortuga"))
			{
				dialog.Text = "啊! 这是什么暴行, 德莫尔? 法国人什么时候开始攻击自己的同胞了? ! ";
				Link.l1 = "根据总督弗朗索瓦.隆维利耶.德波因西的命令, 你, 勒瓦瑟先生, 被免去托尔图加总督的职务并判处死刑! 而我就是执行这个判决的人! ";
                Link.l1.go = "levasser";
				break;
			}
			// <—— 勒瓦瑟
			// fix 从每天5次掠夺 -->
            if (!CheckNPCQuestDate(npchar, "GrabbingTownDate"))
			{
				dialog.Text = "你已经拿走了一切。 你还需要什么? ";
				Link.l1 = "是的, 对, 错了城市。 ";
                Link.l1.go = "Exit_City";

                NPChar.NoGiveMoney = true;

				ChangeCharacterHunterScore(GetMainCharacter(), NationShortName(sti(NPChar.nation)) + "hunter", 20);
				// 在对话后恢复并隐藏
                SetReturn_Gover_Dialog_Exit(NPChar);
				break;
			}
			SetNPCQuestDate(npchar, "GrabbingTownDate");
			// fix 从每天5次掠夺 <--

            if (CheckAttribute(FortChref, "Fort.Mode") && sti(FortChref.Fort.Mode) != FORT_DEAD)
			{ // 而堡垒是活的, 所以陆战通过
				dialog.Text = "前所未有的无礼! 堡垒的援军很快就会到达, 你会为此付出代价的! ";
				Link.l2 = "我不打算在这里等到他们到达。 只要付钱给我, 我们就会离开这个城镇。 ";
                Link.l2.go = "Summ";
				Pchar.HalfOfPaymentByCity = true; // 只付一半钱
            }
            else
            {
				dialog.Text = "你这次赢了, 但要知道我们的海盗猎手中队会追捕你, 把每一分钱都从你肮脏的海盗肉里榨出来! ";
				if (!bWorldAlivePause || bBettaTestMode)
				{
					int iColony = FindColony(npchar.city);
					if (!CheckAttribute(&colonies[iColony], "notCaptured")) //不可占领的城市
					{
						if (CheckAttribute(FortChref, "Default.Prison"))
						{
							Link.l1 = "安静! 从现在起这个城镇属于我;至于你的海盗猎手 - 我会把他们直接送到戴维.琼斯的储物柜。 嘿, 伙计们, 抓住这头猪, 把它关起来。 ";
						}
						else
						{
							Link.l1 = "这个城市现在属于我。 孩子们, 护送前总督到他的新'住所', 呵呵。 ";
						}
						Link.l1.go = "City";
					}
				}
				if (!isCityHasFort(NPChar.City))
				{
					Link.l2 = "来自堡垒的援军? 只要付给我一笔可观的赎金, 我们就会离开你的城镇。 ";
				}
				else
				{
					Link.l2 = "一支海盗猎手中队? 嗯... 只要付钱给我, 我们就会离开你的城镇。 ";
				}
				Link.l2.go = "Summ";

                bOk = !bWorldAlivePause || bBettaTestMode;
				if (isMainCharacterPatented() && bOk && !CheckAttribute(&colonies[iColony], "notCaptured")) //不让占领殖民地
				{
					// 恢复专利国家
					PChar.nation = GetBaseHeroNation();
					
					dialog.Text = "前所未有的无礼! 你怎么敢攻击属于" + NationNameGenitive(sti(NPChar.nation)) + "的殖民地? ! 你将为你洒下的鲜血和对我们国家造成的损害付出高昂的代价。 ";
					Link.l1 = "从现在起这个殖民地属于我。 任何质疑我权威的人都直接下地狱。 ";
					Link.l1.go = "City_patent";
					Link.l2 = "退后。 我以" + NationNameGenitive(sti(PChar.nation)) + "的名义行事。 从现在起这个殖民地属于" + NationKingsCrown(PChar) + "! ";
					Link.l2.go = "City_nation";
					Link.l3 = "你这里有个可爱的城镇。 如果它被烧成灰烬, 总督被吊死在城镇广场上, 那将是一场真正的悲剧。 我们应该讨论一下你愿意支付多少赎金来防止这种悲剧发生。 ";
					Link.l3.go = "Summ_patent";
				}
            }
        break;
		
		// --> 勒瓦瑟
		case "levasser":
			dialog.Text = "波因西? ! 该死的天主教混蛋! 我会处理他... 而你完蛋了, 恶棍! 你不会活着离开这里 - 我会亲自结果你! ";
			Link.l1 = "省省你的说教吧, 异教徒。 当我把你的胡格诺灵魂送到地狱时, 替我向路西法和让.加尔文问好。 接招吧! ";
			Link.l1.go = "levasser_1";
        break;
		
		case "levasser_1":
			chrDisableReloadToLocation = true;//关闭位置
            DialogExit();
			LAi_SetImmortal(npchar, false);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto6");
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LevasserDiedResidence");
			AddDialogExitQuest("MainHeroFightModeOn");	
        break;
		// <—— 勒瓦瑟
        
        case "City":
            ChangeCharacterHunterScore(GetMainCharacter(), NationShortName(sti(NPChar.nation)) + "hunter", 40);
            AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 400);

            Pchar.GenQuestFort.fortCharacterIdx = FortChref.index;
            AddDialogExitQuest("Residence_Captured_Any");

            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_TakeTown", 1);
			// 维修
            RepairAllShips();
			Log_Info("所有船只已维修。 ");
			// 成就 -->
			ReOpenQuestHeader("Gen_CityCapture");
			AddQuestRecordInfo("Gen_CityCapture", "t3");
			AddQuestUserData("Gen_CityCapture", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + NPChar.City));
			// 成就 <--
            NextDiag.CurrentNode = "Prison";
			DialogExit();
        break;

        case "City_patent":
			ChangeCharacterComplexReputation(GetMainCharacter(),"nobility", -20); // 我们是海盗, 但我们有专利
			dialog.Text = "你这次赢了, 但要知道我们的中队很快就会到达, 它会把你夷为平地! ";
			Link.l1 = "闭嘴。 从现在起这个城镇属于我;至于你的中队 - 我会把它直接送到地狱。 孩子们, 护送前总督到他的新'住所', 呵呵。 ";
			Link.l1.go = "City";
        break;

        case "Exit_for_pay":
			dialog.Text = "你还需要我做什么? ";
			Link.l1 = "只是检查一下我有没有漏掉什么...";
            Link.l1.go = "exit";

            NextDiag.TempNode = "Exit_for_pay";
		break;

        case "Exit_City":
			NextDiag.CurrentNode = "Exit_for_pay";
			Pchar.GenQuestFort.fortCharacterIdx = FortChref.index;
			if (sti(NPChar.NoGiveMoney) == false) // 自己拿
			{
				// 在对话后恢复并隐藏
				SetReturn_Gover_Dialog_Exit(NPChar);
				AddDialogExitQuestFunction("TWN_ExitForPay");
            }
            DialogExit();
        break;

        case "Summ":
			dialog.Text = "我别无选择, 只能同意你的条件。 拿走你那该死的钱, 立即离开我们的殖民地。 ";
			Link.l1 = "与你做生意很愉快。 ";
            Link.l1.go = "Exit_City";
            NPChar.NoGiveMoney = false;

            ChangeCharacterHunterScore(GetMainCharacter(), NationShortName(sti(NPChar.nation)) + "hunter", 30);
            AddCharacterExpToSkill(GetMainCharacter(), SKILL_FORTUNE, 300);
            AddCharacterExpToSkill(GetMainCharacter(), "Commerce", 300);

            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_GrabbingTown", 1);
			// 成就 -->
			ReOpenQuestHeader("Gen_CityCapture");
			AddQuestRecordInfo("Gen_CityCapture", "t2");
			AddQuestUserData("Gen_CityCapture", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + NPChar.City));
			// 成就 <--
        break;

        case "Summ_patent":
			dialog.Text = "好吧, 说出你的条件...";
			Link.l1 = "是的, 胜者为王! 开始数你的钱吧。 ";
            Link.l1.go = "Summ";
			ChangeCharacterComplexReputation(GetMainCharacter(),"nobility", -10); // 不在服务中
        break;

        case "City_nation":
			dialog.Text = "好吧, 我们向你投降。 ";
			Link.l1 = "我建议你尽快离开这个城镇 - 即将到来的变化可能对你的健康非常不利。 再见。 ";
			Link.l1.go = "Exit_City";
			NPChar.NoGiveMoney = true;

            ChangeCharacterComplexReputation(GetMainCharacter(),"nobility", 5);
            AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 600);
            AddCharacterExpToSkill(GetMainCharacter(), "Sneak", 400);
            SetNationRelationBoth(sti(PChar.nation), sti(NPChar.nation), RELATION_ENEMY);

			PChar.questTemp.DontSetNewDialogToMayor = true; // 否则可能会改变对话并出错
			PChar.questTemp.DontNullDeposit = true;	// 以免清空市长
            SetCaptureTownByNation(NPChar.City, sti(PChar.nation));
            DeleteAttribute(PChar, "questTemp.DontSetNewDialogToMayor");
			AddDialogExitQuestFunction("LaunchColonyInfoScreen"); // 表格
			// 成就 -->
			sTemp =  GetNationNameByType(sti(PChar.nation));
			ReOpenQuestHeader("Gen_CityCapture");
			AddQuestRecordInfo("Gen_CityCapture", "t1");
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + NPChar.City));
			AddQuestUserData("Gen_CityCapture", "sNation", XI_ConvertString(sTemp + "Gen"));
			// 成就 <--
			AddTitleNextRate(sti(PChar.nation), 1);  // 头衔计数器
			SetCharacterRelationBoth(sti(FortChref.index), GetMainCharacterIndex(), RELATION_FRIEND);// 没有任何作用, 因为OtherChar是总督, 但他已经是朋友了
            UpdateRelations();

			// 22.03.05  fix 恢复对话并隐藏
			// 在对话内不起作用
            SetReturn_Gover_Dialog_Exit(NPChar);

            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_TakeTown", 1);
		break;
	    
	    case "Prison":
			dialog.Text = "你还需要我做什么, 恶棍? ";
			Link.l3 = "大人觉得你的新房间怎么样? 足够宽敞吗? 好吧, 现在我得走了! ";
            Link.l3.go = "exit";
            NextDiag.TempNode = "Prison";
		break;
		
		case "arestFree_1":
			dialog.text = "解决? 你觉得那会是怎样的? ";
			link.l1 = "我认为" + iTotalTemp*6000 + "比索的金额仍然可以拯救我, 不是吗? ";
			link.l1.go = "arestFree_2";
			link.l2 = "不。 而且我该走了。 此致。 ";
			link.l2.go = "arest_1";
		break;

		case "arestFree_2":
            if (GetCharacterSkillToOld(PChar, SKILL_FORTUNE) >= hrand(7) && iTotalTemp < 21)
            {
				dialog.text = "我想我们可以用这种方式解决我们的事件。 你还没有走到不可挽回的地步。 ";
				link.l1 = "太好了。 我非常高兴。 请接受我的捐款。 ";
				link.l1.go = "Exit";
				AddMoneyToCharacter(pchar, -iTotalTemp*6000);
				ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", -iTotalTemp);
				AddCharacterExpToSkill(pchar, "Fortune", 100);
            }
            else
            {
				dialog.text = "你是在向我行贿吗? 哦不! 你的恶行只能用一种方式来弥补... 卫兵! 把" + GetSexPhrase("他","她") + "戴上镣铐! ";
				link.l1 = "等一下! ";
				link.l1.go = "arest_2";
				AddCharacterExpToSkill(pchar, "Fortune", 10);
            }
		break;

		case "arest_1":
			dialog.text = "当然, 是时候了。 我们会送你走的。 卫兵! 抓住" + GetSexPhrase("他","她") + "! ";
			link.l1 = "没门! ";
			link.l1.go = "fight";
		break;

		case "arest_2":
			dialog.text = "你已经有足够的时间思考了! 卫兵! ";
			link.l1 = "你不会轻易抓住我的! ";
			link.l1.go = "fight";
		break;	
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	摧毁帮派
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "DestroyGang":
			dialog.text = "当然。 为了完成这个任务, 我给你" + FindRussianDaysString(sti(pchar.GenQuest.DestroyGang.Terms)) + ", 如果你成功, 你的奖励将是" + FindRussianMoneyString(sti(pchar.GenQuest.DestroyGang.Money)) + "。 ";
			link.l1 = "好的, 我接受这个任务。 ";
			link.l1.go = "DestroyGang_agree";
			link.l2 = "嗯... 不, 我想我会拒绝。 ";
			link.l2.go = "All_disagree";
		break;
		case "DestroyGang_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.questName = "DestroyGang"; //任务类型
			pchar.GenQuest.DestroyGang.Location = GetGangLocation(npchar); //确定帮派所在的位置
			pchar.GenQuest.DestroyGang.MayorId  = npchar.id; //市长Id, 以便知道谁给的任务
			if (pchar.GenQuest.DestroyGang.Location == "none") //以防万一
			{
				dialog.text = "等一下, 我刚忘了昨天的报告。 问题是这个帮派已经离开了我们的岛屿。 所以我不得不取消任务。 ";
				link.l1 = "我明白了。 真可惜。 ";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "GenQuest." + pchar.GenQuest.questName);
				DeleteAttribute(pchar, "GenQuest.questName");
			}
			else
			{
				dialog.text = "好吧, 太好了! 我会在我的住所等你和你的报告。 ";
				link.l1 = "我不会让你等太久的, " + GetAddress_FormToNPC(NPChar) + "。 ";
				link.l1.go = "exit";
				pchar.quest.DestroyGang.win_condition.l1 = "location";
				pchar.quest.DestroyGang.win_condition.l1.location = pchar.GenQuest.DestroyGang.Location;
				pchar.quest.DestroyGang.win_condition = "DestroyGang_fight";
				pchar.quest.DestroyGang.again = true; //帮派不会只是等待他们的时间
				SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.DestroyGang.Terms), false);
				//==> 任务地点不会有遭遇战 
				locations[FindLocation(pchar.GenQuest.DestroyGang.Location)].DisableEncounters = true;
				ReOpenQuestHeader("MayorsQuestsList");
				AddQuestRecord("MayorsQuestsList", "1");
				AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
				AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
				makearef(arName, pchar.GenQuest.DestroyGang);
				AddQuestUserData("MayorsQuestsList", "GangName", GetFullName(arName));
				AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.DestroyGang.Terms)));
				AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.DestroyGang.Money)));
			}
		break;
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	反信使
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "TakePostcureer":
			//设置参数
			pchar.GenQuest.questName = "TakePostcureer"; //任务类型
			// belamour legendary edition 给任务发布者的敌对国家, 而不是主角 -->
			pchar.GenQuest.TakePostcureer.Nation = FindEnemyNation2Character(sti(npchar.index)); //敌对国家
			iTemp = 1;
			while (iTemp < 10 && sti(pchar.GenQuest.TakePostcureer.Nation) == PIRATE) {
				pchar.GenQuest.TakePostcureer.Nation = FindEnemyNation2Character(sti(npchar.index));
				iTemp += 1;
			}
			if (iTemp == 10 && sti(pchar.GenQuest.TakePostcureer.Nation) == PIRATE) {
				dialog.text = LinkRandPhrase("今天我不能给你任何工作。 ", "今天没有更多的工作给你了。 ", "今天没有更多工作了, 抱歉。 明天再来, 我们会看看...");
				link.l1 = RandPhraseSimple("可惜...", "啊, 真可惜, " + GetAddress_FormToNPC(NPChar) + "。 ");
				link.l1.go = "exit";
				
				if (CheckAttribute(pchar, "GenQuest.questName")) {
					QuestName = pchar.GenQuest.questName;
					DeleteAttribute(pchar, "GenQuest." + QuestName);
					DeleteAttribute(pchar, "GenQuest.questName");
				}
				
				break;
			}
			pchar.GenQuest.TakePostcureer.City = FindQuestCity(npchar, "enemy",sti(pchar.GenQuest.TakePostcureer.Nation), false, false);
			// <—— legendary edition
			pchar.GenQuest.TakePostcureer.Island = GetArealByCityName(pchar.GenQuest.TakePostcureer.City);
			pchar.GenQuest.TakePostcureer.Terms = GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(PChar)].id, pchar.GenQuest.TakePostcureer.Island)+5;
			pchar.GenQuest.TakePostcureer.LoginDay = sti(pchar.GenQuest.TakePostcureer.Terms)-1;
			pchar.GenQuest.TakePostcureer.ShipType = SelectCureerShipType();
			pchar.GenQuest.TakePostcureer.ShipName = GenerateRandomNameToShip(sti(pchar.GenQuest.TakePostcureer.Nation));
			pchar.GenQuest.TakePostcureer.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.TakePostcureer.ShipType));
			pchar.GenQuest.TakePostcureer.Money = ((hrand(5)+hrand(6, "1")+4)*2000)+(sti(pchar.rank)*500);
			dialog.text = "当然。 你需要找到一艘" + NationNameGenitive(sti(pchar.GenQuest.TakePostcureer.Nation)) + "的信使船, 名为'" + pchar.GenQuest.TakePostcureer.ShipName + "', 登上它并把你应该能在船长舱里找到的文件带给我。 这艘船大约在" + FindRussianDaysString(pchar.GenQuest.TakePostcureer.Terms) + "内会经过" + XI_ConvertString("Colony" + pchar.GenQuest.TakePostcureer.City + "Gen") + "附近。 ";
			link.l1 = "好的, 我接受这个任务。 我要找什么样的文件? ";
			link.l1.go = "TakePostcureer_agree";
			link.l2 = "嗯... 不, 我想我会拒绝。 ";
			link.l2.go = "All_disagree";
		break;
		
		case "TakePostcureer_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.TakePostcureer.MayorId  = npchar.id; //市长Id, 以便知道谁给的任务
			dialog.text = "邮件。 有非常重要的文件给我。 但你不需要在文件中搜索, 只要把整个包裹带给我。 我会付给你" + FindRussianMoneyString(sti(pchar.GenQuest.TakePostcureer.Money)) + "\n所以, 我会在我的住所等你和你的工作结果。 ";
			link.l1 = "我不会让你等太久的, " + GetAddress_FormToNPC(NPChar) + "。 ";
			link.l1.go = "exit";
			pchar.quest.TakePostcureer.win_condition.l1 = "location";
			pchar.quest.TakePostcureer.win_condition.l1.location = pchar.GenQuest.TakePostcureer.Island;
			pchar.quest.TakePostcureer.win_condition.l2 = "Timer";
			pchar.quest.TakePostcureer.win_condition.l2.date.hour  = sti(GetTime());
			pchar.quest.TakePostcureer.win_condition.l2.date.day   = GetAddingDataDay(0, 0, sti(pchar.GenQuest.TakePostcureer.LoginDay));
			pchar.quest.TakePostcureer.win_condition.l2.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.TakePostcureer.LoginDay));
			pchar.quest.TakePostcureer.win_condition.l2.date.year  = GetAddingDataYear(0, 0, sti(pchar.GenQuest.TakePostcureer.LoginDay));
			pchar.quest.TakePostcureer.function = "TakePostcureer_CreateShip";
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.TakePostcureer.Terms), false);
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "3");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.TakePostcureer.City+"Gen"));
			AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.TakePostcureer.Terms)));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.TakePostcureer.Money)));
			AddQuestUserData("MayorsQuestsList", "sNation", NationNameGenitive(sti(pchar.GenQuest.TakePostcureer.Nation)));
			AddQuestUserData("MayorsQuestsList", "sShipName", pchar.GenQuest.TakePostcureer.ShipName);
		break;
		
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	反走私 - 摧毁军火船
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "TakeArsenalship":
			//设置参数
			pchar.GenQuest.questName = "TakeArsenalship"; //任务类型
			// belamour legendary edition 给任务发布者的敌对国家, 而不是主角 -->
			pchar.GenQuest.TakeArsenalship.Nation = FindEnemyNation2Character(sti(npchar.index));
			iTemp = 1;
			while (iTemp < 10 && sti(pchar.GenQuest.TakeArsenalship.Nation) == PIRATE) {
				pchar.GenQuest.TakeArsenalship.Nation = FindEnemyNation2Character(sti(npchar.index));
				iTemp += 1;
			}
			if (iTemp == 10 && sti(pchar.GenQuest.TakeArsenalship.Nation) == PIRATE) {
				dialog.text = LinkRandPhrase("今天我不能给你任何工作。 ", "今天没有更多的工作给你了。 ", "今天没有更多工作了, 抱歉。 明天再来, 我们会看看...");
				link.l1 = RandPhraseSimple("可惜...", "啊, 真可惜, " + GetAddress_FormToNPC(NPChar) + "。 ");
				link.l1.go = "exit";
				
				if (CheckAttribute(pchar, "GenQuest.questName")) {
					QuestName = pchar.GenQuest.questName;
					DeleteAttribute(pchar, "GenQuest." + QuestName);
					DeleteAttribute(pchar, "GenQuest.questName");
				}
				
				break;
			}
			pchar.GenQuest.TakeArsenalship.City = FindQuestCity(npchar, "enemy",sti(pchar.GenQuest.TakeArsenalship.Nation), false, false);
			// <—— legendary edition
			pchar.GenQuest.TakeArsenalship.Island = GetArealByCityName(pchar.GenQuest.TakeArsenalship.City);
			pchar.GenQuest.TakeArsenalship.Terms = GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(PChar)].id, pchar.GenQuest.TakeArsenalship.Island)+5;
			pchar.GenQuest.TakeArsenalship.LoginDay = sti(pchar.GenQuest.TakeArsenalship.Terms)-1;
			pchar.GenQuest.TakeArsenalship.ShipType = SelectArsenalShipType(FLAG_SHIP_TYPE_RAIDER);
			pchar.GenQuest.TakeArsenalship.ShipTypeA = SelectArsenalShipType(FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_UNIVERSAL);
			pchar.GenQuest.TakeArsenalship.ShipName = GenerateRandomNameToShip(sti(pchar.GenQuest.TakeArsenalship.Nation));
			pchar.GenQuest.TakeArsenalship.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.TakeArsenalship.ShipType));
			pchar.GenQuest.TakeArsenalship.CannonA = SelectLevelCannonParameter(sti(pchar.GenQuest.TakeArsenalship.ShipTypeA)); // Addon 2016-1 Jason 海盗系列
			pchar.GenQuest.TakeArsenalship.Money = ((hrand(5)+hrand(6, "1")+4)*1800)+(sti(pchar.rank)*500);
			dialog.text = "当然。 你需要找到一艘"+NationNameGenitive(sti(pchar.GenQuest.TakeArsenalship.Nation))+"的军事运输船, 船上有火药和弹药;这艘船的名字是'"+pchar.GenQuest.TakeArsenalship.ShipName+"', 找到并摧毁它。 这样我们就能削弱我们的敌人\n运输船将有护航前往殖民地"+XI_ConvertString("Colony"+pchar.GenQuest.TakeArsenalship.City)+", 大约在"+FindRussianDaysString(pchar.GenQuest.TakeArsenalship.Terms)+"内, 所以你应该快点。 ";
			link.l1 = "好的, 我接受。 我是必须击沉军火船还是应该尝试捕获它? ";
			link.l1.go = "TakeArsenalship_agree";
			link.l2 = "嗯... 不, 我想我会拒绝。 ";
			link.l2.go = "All_disagree";
		break;
		
		case "TakeArsenalship_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.TakeArsenalship.MayorId  = npchar.id; //市长Id, 以便知道谁给的任务
			dialog.text = "我不在乎, 这取决于你。 重要的是这批货物不能到达目的地。 如果你成功了, 我会付给你"+FindRussianMoneyString(sti(pchar.GenQuest.TakeArsenalship.Money))+"... 我不再耽误你了, 船长。 ";
			link.l1 = "我不会让你等太久的, " + GetAddress_FormToNPC(NPChar) + "。 ";
			link.l1.go = "exit";
			pchar.quest.TakeArsenalship.win_condition.l1 = "location";
			pchar.quest.TakeArsenalship.win_condition.l1.location = pchar.GenQuest.TakeArsenalship.Island;
			pchar.quest.TakeArsenalship.win_condition.l2 = "Timer";
			pchar.quest.TakeArsenalship.win_condition.l2.date.hour  = sti(GetTime());
			pchar.quest.TakeArsenalship.win_condition.l2.date.day   = GetAddingDataDay(0, 0, sti(pchar.GenQuest.TakeArsenalship.LoginDay));
			pchar.quest.TakeArsenalship.win_condition.l2.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.TakeArsenalship.LoginDay));
			pchar.quest.TakeArsenalship.win_condition.l2.date.year  = GetAddingDataYear(0, 0, sti(pchar.GenQuest.TakeArsenalship.LoginDay));
			pchar.quest.TakeArsenalship.function = "TakeArsenalship_CreateShip";
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.TakeArsenalship.Terms), false);
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "8");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.TakeArsenalship.City));
			AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.TakeArsenalship.Terms)));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.TakeArsenalship.Money)));
			AddQuestUserData("MayorsQuestsList", "sNation", NationNameGenitive(sti(pchar.GenQuest.TakeArsenalship.Nation)));
			AddQuestUserData("MayorsQuestsList", "sShipName", pchar.GenQuest.TakeArsenalship.ShipName);
		break;
		
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	海岸警卫队 - 摧毁海盗船
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "TakePirateship":
			//设置参数
			pchar.GenQuest.questName = "TakePirateship"; //任务类型
			pchar.GenQuest.TakePirateship.City = FindQuestCity(npchar, "all", -1, true, true); // belamour legendary edition 
			pchar.GenQuest.TakePirateship.Island = GetArealByCityName(pchar.GenQuest.TakePirateship.City);
			pchar.GenQuest.TakePirateship.Terms = GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(PChar)].id, pchar.GenQuest.TakePirateship.Island)+5;
			pchar.GenQuest.TakePirateship.ShipType = SelectPirateShipType();
			pchar.GenQuest.TakePirateship.ShipName = GenerateRandomNameToShip(PIRATE);
			pchar.GenQuest.TakePirateship.Name = GenerateRandomName(PIRATE, "man");
			pchar.GenQuest.TakePirateship.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.TakePirateship.ShipType));
			pchar.GenQuest.TakePirateship.Money = ((hrand(5)+hrand(6, "1")+4)*2400)+(sti(pchar.rank)*500);
			dialog.text = "当然。 我真的被一个海盗船长的活动激怒了, 他的名字是" + pchar.GenQuest.TakePirateship.Name + "。 那个恶棍养成了袭击我们商船的习惯, 这极大地损害了殖民地之间的贸易。 现在是摆脱那个混蛋的最佳时机, 因为我刚巧知道他目前藏在哪里。 你准备好把这个无赖送到上帝的审判席了吗? ";
			link.l1 = "我很荣幸! 我在哪里可以找到这个海盗? ";
			link.l1.go = "TakePirateship_agree";
			link.l2 = "嗯... 不, 我想我会拒绝。 ";
			link.l2.go = "All_disagree";
		break;
		
		case "TakePirateship_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.TakePirateship.MayorId  = npchar.id; //市长Id, 以便知道谁给的任务
			dialog.text = "在最近的 "+FindRussianDaysString(pchar.GenQuest.TakePirateship.Terms)+" 内, 他名为 '"+pchar.GenQuest.TakePirateship.ShipName+"' 的船将在 "+XI_ConvertString("Colony"+pchar.GenQuest.TakePirateship.City+"Gen")+" 附近的海岸巡航。 找到他并杀了他。 把船送去喂鱼, 登上船 - 我不在乎。 我只关心那个该死的海盗将停止用他的存在玷污我们的海洋\n对于这个任务, 我愿意付给你 "+FindRussianMoneyString(sti(pchar.GenQuest.TakePirateship.Money))+"。 不要浪费时间, 船长: 这个恶棍不会在 "+XI_ConvertString("Colony"+pchar.GenQuest.TakePirateship.City+"Gen")+"等你。 去吧, 愿上帝帮助你! ";
			link.l1 = "已经起锚了, " + GetAddress_FormToNPC(NPChar) + "! 你不会等太久的。 ";
			link.l1.go = "exit";
			pchar.quest.TakePirateship.win_condition.l1 = "location";
			pchar.quest.TakePirateship.win_condition.l1.location = pchar.GenQuest.TakePirateship.Island;
			pchar.quest.TakePirateship.function = "TakePirateship_CreateShip";
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.TakePirateship.Terms), false);
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "9");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.TakePirateship.City+"Gen"));
			AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.TakePirateship.Terms)));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.TakePirateship.Money)));
			AddQuestUserData("MayorsQuestsList", "sName", pchar.GenQuest.TakePirateship.Name);
			AddQuestUserData("MayorsQuestsList", "sShipName", pchar.GenQuest.TakePirateship.ShipName);
		break;
		
/////////////////////////////////////////////////////////////////////////////////////////////////
		//	ОЗГ - 抓获乘客
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "TakePassenger":
			//设置参数
			pchar.GenQuest.questName = "TakePassenger"; //任务类型
			pchar.GenQuest.TakePassenger.Nation = FindEnemyNation2Character(sti(npchar.index));//敌对国家
			iTemp = 1;
			while (iTemp < 10 && sti(pchar.GenQuest.TakePassenger.Nation) == PIRATE) {
				pchar.GenQuest.TakePassenger.Nation = FindEnemyNation2Character(sti(npchar.index));
				iTemp += 1;
			}
			if (iTemp == 10 && sti(pchar.GenQuest.TakePassenger.Nation) == PIRATE) {
				dialog.text = LinkRandPhrase("今天我不能给你提供任何工作。 ", "今天已经没有更多工作给你了。 ", "今天没有更多工作了, 抱歉。 明天再来, 我们看看...");
				link.l1 = RandPhraseSimple("真遗憾...", "啊, 真遗憾, " + GetAddress_FormToNPC(NPChar) + "。 ");
        		link.l1.go = "exit";
				
				if (CheckAttribute(pchar, "GenQuest.questName")) {
					QuestName = pchar.GenQuest.questName;
					DeleteAttribute(pchar, "GenQuest." + QuestName);
					DeleteAttribute(pchar, "GenQuest.questName");
				}
				
				break;
			}
			pchar.GenQuest.TakePassenger.City = FindQuestCity(npchar, "enemy", sti(pchar.GenQuest.TakePassenger.Nation), false, false); // belamour legendary edition
			pchar.GenQuest.TakePassenger.CityA = SelectAnyColony(pchar.GenQuest.TakePassenger.City);
			pchar.GenQuest.TakePassenger.Terms1 = GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(PChar)].id, GetArealByCityName(pchar.GenQuest.TakePassenger.City));
			pchar.GenQuest.TakePassenger.Terms2 = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.GenQuest.TakePassenger.City), GetArealByCityName(pchar.GenQuest.TakePassenger.CityA))+1;
			pchar.GenQuest.TakePassenger.Terms = sti(pchar.GenQuest.TakePassenger.Terms1)+sti(pchar.GenQuest.TakePassenger.Terms2);
			pchar.GenQuest.TakePassenger.ShipType = SelectCureerShipType();
			pchar.GenQuest.TakePassenger.ShipName = GenerateRandomNameToShip(sti(pchar.GenQuest.TakePassenger.Nation));
			pchar.GenQuest.TakePassenger.Name = GenerateRandomName(sti(pchar.GenQuest.TakePassenger.Nation), "man");
			pchar.GenQuest.TakePassenger.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.TakePassenger.ShipType));
			pchar.GenQuest.TakePassenger.Money = ((hrand(5)+hrand(6, "1")+4)*2200)+(sti(pchar.rank)*500);
			string sText = SelectPassText();
			dialog.text = "当然。 我说的是一个名叫" + pchar.GenQuest.TakePassenger.Name + "的无赖。 " + sText + "我找他很久了, 现在终于得到可靠消息, 知道在哪里可以找到他。 我需要你无论如何把那个人活着带给我。 我要在我们镇广场公开绞死他。 你准备好接受这个任务了吗? ";
			link.l1 = "我准备好了, " + GetAddress_FormToNPC(NPChar) + "。 我在哪里可以找到那个无赖? ";
		    link.l1.go = "TakePassenger_agree";
			link.l2 = "嗯...不, 我想我还是算了。 ";
		    link.l2.go = "All_disagree";
		break;
		
		case "TakePassenger_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.TakePassenger.MayorId  = npchar.id; //市长Id, 以便知道谁给的任务
			dialog.text = "就在" + FindRussianDaysString(pchar.GenQuest.TakePassenger.Terms1) + "后, 他将作为一艘名为'" + pchar.GenQuest.TakePassenger.ShipName + "'的船上的乘客, 从" + XI_ConvertString("Colony" + pchar.GenQuest.TakePassenger.City + "Gen") + "起航, 前往" + XI_ConvertString("Colony" + pchar.GenQuest.TakePassenger.CityA + "Acc") + "。 你有" + FindRussianDaysString(pchar.GenQuest.TakePassenger.Terms) + "的时间在指定航段找到这艘船, 登船并抓住这个混蛋。 如果你按照这个指示做, 我会付给你" + FindRussianMoneyString(sti(pchar.GenQuest.TakePassenger.Money)) + "。 祝你好运, 船长! ";
			link.l1 = "我不会再浪费时间了, " + GetAddress_FormToNPC(NPChar) + "! 我马上起航。 ";
			link.l1.go = "exit";
			SetFunctionTimerCondition("TakePassenger_CreateShip", 0, 0, sti(pchar.GenQuest.TakePassenger.Terms1), false);
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.TakePassenger.Terms), false);
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "10");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.TakePassenger.City + "Gen"));
			AddQuestUserData("MayorsQuestsList", "sCityA", XI_ConvertString("Colony" + pchar.GenQuest.TakePassenger.CityA + "Acc"));
			AddQuestUserData("MayorsQuestsList", "sDay1", FindRussianDaysString(sti(pchar.GenQuest.TakePassenger.Terms1)));
			AddQuestUserData("MayorsQuestsList", "sDay2", FindRussianDaysString(sti(pchar.GenQuest.TakePassenger.Terms)));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.TakePassenger.Money)));
			AddQuestUserData("MayorsQuestsList", "sName", pchar.GenQuest.TakePassenger.Name);
			AddQuestUserData("MayorsQuestsList", "sShipName", pchar.GenQuest.TakePassenger.ShipName);
		break;
		
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	海关巡逻
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "CustomPatrol":
			//设置参数
			pchar.GenQuest.questName = "CustomPatrol"; //任务类型
			pchar.GenQuest.CustomPatrol.Nation = sti(npchar.nation);//国家
			pchar.GenQuest.CustomPatrol.Island = Islands[GetCharacterCurrentIsland(PChar)].id;
			pchar.GenQuest.CustomPatrol.LoginDay = rand(4)+1;
			pchar.GenQuest.CustomPatrol.Loginlocator = rand(3)+4;
			pchar.GenQuest.CustomPatrol.ShipType = SelectCustomPatrolShipType(FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_UNIVERSAL);
			pchar.GenQuest.CustomPatrol.ShipTypeA = SelectCustomPatrolShipType(FLAG_SHIP_TYPE_RAIDER);
			pchar.GenQuest.CustomPatrol.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.CustomPatrol.ShipType));
			pchar.GenQuest.CustomPatrol.Money = ((hrand(5)+hrand(6, "1")+4)*1400)+(sti(pchar.rank)*300);
			dialog.text = "我有可靠消息称, 某位船长与走私者安排了一笔关于出售奴隶的交易。 如你所知, 在我们的殖民地, 私人进行此类交易被视为走私货物\n问题在于, 我既不知道走私者会面的确切时间。 日期, 也不知道地点。 只知道这笔犯罪交易将在未来五天内于我们的岛上完成。 更糟糕的是, 我所有的巡逻船要么在维修, 要么在执行其他任务, 无法找到这些恶棍\n我建议你处理这个任务 - 追踪走私者并以最激进的方式对付他们, 让他们成为榜样。 你准备好执行这个任务了吗? ";
			link.l1 = "我准备好了, " + GetAddress_FormToNPC(NPChar) + "。 告诉我, 你有任何额外的信息吗? 比如船长的名字, 他的船名或类型? ";
		    link.l1.go = "CustomPatrol_agree";
			link.l2 = "嗯...不, 我想我还是算了。 ";
		    link.l2.go = "All_disagree";
		break;
		
		case "CustomPatrol_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.CustomPatrol.MayorId  = npchar.id; //市长Id, 以便知道谁给的任务
			dialog.text = "我的线人刚告诉我, 一笔交易正在准备中并将完成。 就是这样。 所以只要密切关注我们水域内所有可疑的船只。 如果你成功了, 我会付给你一笔" + FindRussianMoneyString(sti(pchar.GenQuest.CustomPatrol.Money)) + "\n此外, 鉴于这种情况, 我授权你没收你能找到的全部走私货物。 当然是非正式的, 前提是你不会在我们的城市出售。 ";
			link.l1 = "相当慷慨。 好吧, 我会开始巡逻你的殖民地水域, " + GetAddress_FormToNPC(NPChar) + "。 ";
			link.l1.go = "exit";
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, 6, false);
			pchar.quest.CustomPatrol.win_condition.l1 = "location";
			pchar.quest.CustomPatrol.win_condition.l1.location = pchar.GenQuest.CustomPatrol.Island;
			pchar.quest.CustomPatrol.win_condition.l2 = "Timer";
			pchar.quest.CustomPatrol.win_condition.l2.date.hour  = sti(GetTime()+rand(8));
			pchar.quest.CustomPatrol.win_condition.l2.date.day   = GetAddingDataDay(0, 0, sti(pchar.GenQuest.CustomPatrol.LoginDay));
			pchar.quest.CustomPatrol.win_condition.l2.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.CustomPatrol.LoginDay));
			pchar.quest.CustomPatrol.win_condition.l2.date.year  = GetAddingDataYear(0, 0, sti(pchar.GenQuest.CustomPatrol.LoginDay));
			pchar.quest.CustomPatrol.function = "CustomPatrol_CreateShip";
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "11");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.CustomPatrol.Money)));
		break;
		
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	寻找逃兵
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "FindFugitive":
			//设置参数
			pchar.GenQuest.questName = "FindFugitive"; //任务类型
			pchar.GenQuest.FindFugitive.Startcity = npchar.city;
			pchar.GenQuest.FindFugitive.City = SelectFugitiveCity();
			pchar.GenQuest.FindFugitive.Chance = rand(2);
			pchar.GenQuest.FindFugitive.Name = GenerateRandomName(sti(npchar.Nation), "man");
			pchar.GenQuest.FindFugitive.Money = ((hrand(5)+hrand(6, "1")+4)*2600)+(sti(pchar.rank)*600);
			sText = SelectFugitiveText();
			log_testinfo(pchar.GenQuest.FindFugitive.City);
			log_testinfo(FindRussianDaysString(sti(pchar.GenQuest.FindFugitive.Chance)));
			dialog.text = "我会详细告诉你一切。 发生了一件非常糟糕的事情 - " + sText + "。 通过采访他的同事和朋友, 我们有理由相信逃兵躲在海盗的某个定居点里\n我建议你访问海盗巢穴, 找到逃兵, 逮捕并送到这里。 逃兵是严重的罪行, 不能不受惩罚。 你准备好接受这个任务了吗? ";
			link.l1 = "我准备好了, " + GetAddress_FormToNPC(NPChar) + "。 你能告诉我逃兵的名字吗? ";
		    link.l1.go = "FindFugitive_agree";
			link.l2 = "嗯...不, 我想我还是算了。 ";
		    link.l2.go = "All_disagree";
		break;
		
		case "FindFugitive_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.FindFugitive.MayorId  = npchar.id; //市长Id, 以便知道谁给的任务
			dialog.text = "是的, 当然。 他的名字是" + pchar.GenQuest.FindFugitive.Name + "。 我非常怀疑他会穿着制服, 所以仔细看看各种败类。 我给你一个月的搜索时间, 因为恐怕之后再找他就没有意义了。 如果你成功了, 我会付给你一笔" + FindRussianMoneyString(sti(pchar.GenQuest.FindFugitive.Money)) + "。 ";
			link.l1 = "我不会再浪费时间了, " + GetAddress_FormToNPC(NPChar) + "! 我马上起航。 ";
			link.l1.go = "exit";
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, 30, false);
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "12");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.FindFugitive.Money)));
			AddQuestUserData("MayorsQuestsList", "sName", pchar.GenQuest.FindFugitive.Name);
			//创建逃兵
			sld = GetCharacter(NPC_GenerateCharacter("Fugitive", "citiz_" + (21+rand(9)), "man", "man", sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, sti(npchar.nation), 30, true, "soldier"));
			SetFantomParamFromRank(sld, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true);
			sld.name = pchar.GenQuest.FindFugitive.Name;
			sld.lastname = "";
			sld.dialog.FileName = "MayorQuests_dialog.c";
			sld.greeting = "marginal";
		break;
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	潜入敌城
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "Intelligence":
			dialog.text = "我明白了。 也许" + FindRussianMoneyString(sti(pchar.GenQuest.Intelligence.Money)) + "的奖励会是对你的一个很好激励。 ";
			link.l1 = "是的, 这是不错的钱...我接受这个任务。 ";
		    link.l1.go = "Intelligence_agree";
			link.l2 = "嗯...不, 我想我会拒绝。 这太危险了。 ";
		    link.l2.go = "All_disagree";
		break;
		case "Intelligence_agree":
			if (pchar.GenQuest.Intelligence.City == "none" || isBadReputation(pchar, 30)) //以防万一
			{
				dialog.text = "不过, 我不能说我完全信任你...我想我不会给你这个任务。 ";
				link.l1 = "哦, 好吧...真遗憾, 但我无能为力。 ";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "GenQuest." + pchar.GenQuest.questName);
			}
			else
			{
				npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
				pchar.GenQuest.questName = "Intelligence"; //任务类型
				sTemp = pchar.GenQuest.Intelligence.City;
				switch (rand(4))
				{
					case 0:	sTemp += "_Priest";		break;
					case 1:	sTemp += "_trader";		break;
					case 2:	sTemp += "_shipyarder"; break;
					case 3:	sTemp += "_usurer";	    break;
					case 4:	sTemp += "_PortMan";	break;
				}
				pchar.GenQuest.Intelligence.SpyId = sTemp; //我们在城市中的间谍Id
				dialog.text = "太好了! 现在言归正传。 在" + XI_ConvertString("Colony" + pchar.GenQuest.Intelligence.City + "Dat") + "你需要找到一个当地的" + GetWorkTypeOfMan(&characters[GetCharacterIndex(sTemp)], "Gen") + 
					", 他的名字是" + GetFullName(&characters[GetCharacterIndex(sTemp)]) + "。 你告诉他我的名字, 他会给你一包文件。 把这个包裹送到我手里, 我给你" + FindRussianDaysString(sti(pchar.GenQuest.Intelligence.Terms)) + "。 记住, 一切都要秘密进行。 如果你的身份暴露了, 特工不会冒险尝试联系。 清楚了吗? ";
				link.l1 = "是的, 我明白了, " + GetAddress_FormToNPC(NPChar) + "。 我马上开始。 ";
				link.l1.go = "exit";
				pchar.GenQuest.Intelligence.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квeст
				SaveCurrentQuestDateParam("GenQuest.Intelligence"); //запись даты получeния квeста
				ReOpenQuestHeader("MayorsQuestsList");
				AddQuestRecord("MayorsQuestsList", "6");
				AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
				AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
				AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Acc"));
				AddQuestUserData("MayorsQuestsList", "sIsland", XI_ConvertString(colonies[FindColony(pchar.GenQuest.Intelligence.City)].islandLable+"Dat"));
				AddQuestUserData("MayorsQuestsList", "sWho", GetWorkTypeOfMan(&characters[GetCharacterIndex(sTemp)], "Gen"));
				AddQuestUserData("MayorsQuestsList", "SpyName", GetFullName(&characters[GetCharacterIndex(sTemp)]));			
				AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.Intelligence.Terms)));
				AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Intelligence.Money)));
				AddQuestUserData("MayorsQuestsList", "sCity2", XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Dat"));
			}
		break;
		case "Intelligence_ExecuteLate":
			QuestName = pchar.GenQuest.questName;
			pchar.GenQuest.(QuestName).Money = sti(pchar.GenQuest.(QuestName).Money) / 2);
			dialog.text = RandPhraseSimple("不错。 但你没有按时完成, 因此我必须稍微削减你的奖励。 现在你的费用将是" + FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money)) + "。 给你。 ", 
				"很好。 但你没有按时完成, 我一直在等这些信件。 你破坏了我的计划, 因此我不得不稍微削减你的奖励。 不过, 我很高兴把你应得的奖励给你 - " + FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money))  + "。 给你。 ");
			link.l1 = "我不会说这对我来说很好, 但最终确实违反了最后期限。 所以我没有怨言, " + GetAddress_FormToNPC(NPChar) + "。 ";
		    link.l1.go = "All_Execute_1";
			//--> 谣言
			AddSimpleRumour(RandPhraseSimple("你知道吗, 总督" + GetFullName(npchar) + "对船长" + GetMainCharacterNameGen() + "的速度不太满意。 ", 
				"总督" + GetFullName(npchar) + "对船长" + GetMainCharacterNameDat() + "不太满意, " + GetSexPhrase("他","她") + "遵守了他的命令, 但没有及时..."), sti(npchar.nation), 5, 1);
			//<—— 谣言
		break;
		
		// ------------—— 市长所有任务的通用集合 ------------------
		case "All_disagree":
			dialog.text = "你让我失望! ";
			link.l1 = "对不起, " + GetAddress_FormToNPC(NPChar) + ", 但我不能接受这个工作。 ";
		    link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			
			if (CheckAttribute(pchar, "GenQuest.questName"))
			{
				QuestName = pchar.GenQuest.questName;
				DeleteAttribute(pchar, "GenQuest." + QuestName);
				DeleteAttribute(pchar, "GenQuest.questName");
			}
		break;
		case "All_Late":
			QuestName = pchar.GenQuest.questName;
			dialog.text = RandPhraseSimple("嗯, 非常糟糕 - 我还能说什么。 我指望你 - 结果发现我只是浪费了时间。 我很失望。 ", 
				"嗯, 我必须说我对你完全失望了...在我的住所里有很多人随时准备为我跑这样的差事 - 而我却在你身上浪费了时间。 哦, 好吧...");
			link.l1 = "对不起, " + GetAddress_FormToNPC(NPChar) + ", 我已经尽我所能了。 ";
		    link.l1.go = "exit";
			//--> 谣言
			AddSimpleRumour(LinkRandPhrase("你知道吗, 总督" + GetFullName(npchar) + "对船长" + GetMainCharacterNameDat() + "非常不满。 想象一下 - 他没有及时完成任务! ", 
				"总督" + GetFullName(npchar) + "有点生气, 因为船长" + GetFullName(pchar) + "努力了, 但未能及时完成任务。 太糟糕了...", 
				"我听说总督" + GetFullName(npchar) + "对你非常不满, 船长" + GetFullName(pchar) + ", 因为你在试图完成他的任务时没有赶上最后期限。 "), sti(npchar.nation), 5, 1);
			//<—— 谣言
			ChangeCharacterComplexReputation(pchar,"nobility", -4);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			DeleteAttribute(pchar, "GenQuest." + QuestName);
			DeleteAttribute(pchar, "GenQuest.questName");
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_common"; //切换回对话
			SaveCurrentNpcQuestDateParam(npchar, "work_date"); //立即再给一个不允许
			CloseQuestHeader("MayorsQuestsList");
		break;
		case "All_Found":
			QuestName = pchar.GenQuest.questName;
			dialog.text = RandPhraseSimple("我简直惊呆了! 你设法找到了目标, 但却不关心确保自己优势的手段 - 这是极端的鲁莽。 我很失望! ", 
				"嗯, 我必须说我对你很失望...找到目标是不够的 - 你必须有办法摧毁它。 在我的住所里有很多恶棍随时准备为我跑这样的差事。 我当初转向你时到底在想什么? ");
			link.l1 = "对不起, " + GetAddress_FormToNPC(NPChar) + ", 但我只是不愿意鲁莽地拿自己的生命冒险。 ";
		    link.l1.go = "exit";
			//--> 谣言
			AddSimpleRumour(LinkRandPhrase("你知道吗, 总督" + GetFullName(npchar) + "对船长" + GetMainCharacterNameDat() + "非常不满。 想象一下, " + GetSexPhrase("他原来是个彻头彻尾的懦夫","她原来是个彻头彻尾的懦夫") + "! ", 
				"总督" + GetFullName(npchar) + "有点生气, 因为船长" + GetFullName(pchar) + "接受了这份工作, 但由于自己的犹豫不决而未能完成。 嘿嘿, 船长们会怎么做! ", 
				"我听说总督" + GetFullName(npchar) + "对你非常不满, 船长" + GetFullName(pchar) + "。 他们说你只不过是个懦夫" + GetSexPhrase("","") + "..."), sti(npchar.nation), 5, 1);
			//<—— 谣言
			ChangeCharacterComplexReputation(pchar,"nobility", -6);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			DeleteAttribute(pchar, "GenQuest." + QuestName);
			DeleteAttribute(pchar, "GenQuest.questName");
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_common"; //切换回对话
			SaveCurrentNpcQuestDateParam(npchar, "work_date"); //立即再给一个不允许
			CloseQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "21");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
		break;
		case "All_Execute":
			QuestName = pchar.GenQuest.questName;
			dialog.text = RandPhraseSimple("好消息! 嗯, 是时候总结一下了。 你的费用将是" + FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money)) + "。 给你。 ", 
				"太棒了! 这样对每个人都是最好的...嗯, 我很高兴把你应得的奖励给你 - " + FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money))  + "。 给你。 ");
			link.l1 = "谢谢你, " + GetAddress_FormToNPC(NPChar) + ", " + RandPhraseSimple("很高兴与你合作! ", "我对结算的清晰度感到惊喜。 ");
		    link.l1.go = "All_Execute_1";
			//--> 谣言
			AddSimpleRumour(LinkRandPhrase("你知道吗, 总督" + GetFullName(npchar) + "一直在称赞" + GetSexPhrase("一位船长","一位年轻女士") + " " + GetMainCharacterNameGen() + "的勤奋。 ", 
				"总督" + GetFullName(npchar) + "在称赞船长" + GetMainCharacterNameGen() + ", " + GetSexPhrase("他","她") + "在处理总督的任务时总是表现完美。 我要说, 这是总督不可替代的人...", 
				"我听说总督" + GetFullName(npchar) + "对你非常满意, 船长" + GetFullName(pchar) + "。 他将你定义为一个非常细心和彻底的军官。 听到这个很高兴, 船长..."), sti(npchar.nation), 5, 1);
			//<—— 谣言
		break;
		case "All_Execute_1":
			QuestName = pchar.GenQuest.questName;
			dialog.text = RandPhraseSimple("非常好。 你可以再来看我 - 也许我会给你找另一份工作。 ", "嗯, 太好了! 我想我会再次给你提供这样的工作。 ");
			link.l1 = RandPhraseSimple("太好了。 ", "好的。 ");
		    link.l1.go = "exit";
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.(QuestName).Money));
			CloseQuestHeader("MayorsQuestsList");
			ChangeCharacterComplexReputation(pchar,"nobility", 4);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(PChar, "Leadership", 180);
			OfficersReaction("good"); // dlc
			
			DeleteAttribute(pchar, "GenQuest." + QuestName);
			DeleteAttribute(pchar, "GenQuest.questName");
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_common"; //切换回对话
			SaveCurrentNpcQuestDateParam(npchar, "work_date"); //立即再给一个不允许
			// 市长任务数据库中的增量
			sTemp = npchar.City;
			if (!CheckAttribute(pchar, "GenQuest.MayorQuestsList." + sTemp)) pchar.GenQuest.MayorQuestsList.(sTemp) = 0;
			pchar.GenQuest.MayorQuestsList.(sTemp) = sti(pchar.GenQuest.MayorQuestsList.(sTemp)) + 1;
		break;
//<—— homo围攻
		case "siege_task":
            makearef(aData, NullCharacter.Siege);
            aData.HelpColony = true;
			dialog.text = "在这危难时刻, 任何帮助都将非常受欢迎。 我们接受你的援助 - 帮助我们保卫我们的殖民地, 你将得到回报。 ";
			link.l1 = "那我们不要浪费时间了。 ";
		    link.l1.go = "exit";
		break;
		
		//Jason --> 加斯科涅人的负担
		case "Sharlie":
			dialog.text = "你在找米歇尔.德.蒙佩尔? 有趣...你需要他做什么? ";
			link.l1 = "我是他的兄弟。 我父亲告诉我米歇尔有麻烦需要帮助, 所以我...";
			link.l1.go = "Sharlie_1";			
		break;
		
		case "Sharlie_1":
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "First time";
			DelLandQuestMark(sld);
			dialog.text = "是吗? 我不记得蒙佩尔先生有任何兄弟...你知道, 先生, 你看起来对我很可疑...所以我要逮捕你作进一步调查。 中尉! 拘留这个人! ";
			link.l1 = "但是大人! ";
			link.l1.go = "exit";
			if (GetCharacterIndex("SharlieKnown") != -1)
			{
				sld = characterFromId("SharlieKnown");
				sld.lifeday = 0;
			}	
			AddDialogExitQuestFunction("Sharlie_enterSoldiers");
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Sharlie_2":
			QuestPointerDelLoc("Fortfrance_town", "reload", "reload3_back");
			dialog.text = "不过我还是想弥补一下。 来 - 请收下这把剑。 这把手枪和这件轻甲 - 这是我给你的礼物。 我相信你会发现这些东西非常有用。 ";
			link.l1 = "谢谢你, 先生。 考虑到你的卫兵拿走了我所有的东西, 这将非常方便。 ";
			// belamour legendary edition -->
			link.l1.go = "Sharlie_5";		
			link.l2 = "谢谢你, 先生。 你还有其他方式可以帮助我吗? 绅士对绅士? 你自己也可以看到我处境有多糟糕! ";
			link.l2.go = "Sharlie_3";	
		break;
		
		case "Sharlie_3":
			dialog.text = "好吧, 查尔斯... (在桌子里翻找) 给, 把这个神圣的护身符留着当作好运。 我不能再帮忙了, 抱歉。 在殖民地这里, 你将不得不只依靠自己。 ";
			link.l1 = "嗯, 至少有一些东西。 谢谢你的礼物, 先生。 ";
			link.l1.go = "Sharlie_4";
		break;
		
		case "Sharlie_4":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "Commerce", 10);
			Log_Info("你收到了装备");
			Log_Info("你收到了'圣水'护身符");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "amulet_7");
			TakeNItems(pchar, "blade_08", 1);
			if(GetCharacterEquipByGroup(pchar, BLADE_ITEM_TYPE) == "")
			{
				EquipCharacterbyItem(pchar, "blade_08");
			}
			TakeNItems(pchar, "pistol1", 1);
			TakeNItems(pchar, "cirass5", 1);
			pchar.quest.Sharlie_PardonOver.over = "yes";
			DeleteAttribute(pchar, "questTemp.Sharlie.Pardon");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Junglejew"))
			{
				DelLandQuestMark(npchar);
			}
			if(CheckAttribute(pchar,"systeminfo.tutorial.Amulet"))
			{
				DoQuestFunctionDelay("Tutorial_Amulet", 0.1);
			}
		break;
		
		case "Sharlie_5":
			// <—— legendary edition
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 10);
			Log_Info("你收到了装备");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "blade_08", 1);
			if(GetCharacterEquipByGroup(pchar, BLADE_ITEM_TYPE) == "")
			{
				EquipCharacterbyItem(pchar, "blade_08");
			}
			TakeNItems(pchar, "pistol1", 1);
			TakeNItems(pchar, "cirass5", 1);
			pchar.quest.Sharlie_PardonOver.over = "yes";
			DeleteAttribute(pchar, "questTemp.Sharlie.Pardon");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Junglejew"))
			{
				DelLandQuestMark(npchar);
			}
		break;
		//<—— 加斯科涅人的负担
		
		//Sinistra --> 折磨老鼠		
		case "TK_TravlyaKrys":
			dialog.text = "真是命运的转折, 查尔斯...我们很少看到有人在我们的世界里如此迅速地崛起。 我有一种感觉, 你和我会相处得很好。 ";
			link.l1 = "我很荣幸。 也许你有任务给我? ";
			link.l1.go = "TK_TravlyaKrys_2";
			DeleteAttribute(pchar, "questTemp.TK_TravlyaKrys");
			PChar.quest.TK_Timer.over = "yes";
		break;
		
		case "TK_TravlyaKrys_2":
			dialog.text = "当然! 特别是在你成功地在勒弗朗索瓦附近与巴巴松的一名海盗交战后...";
			link.l1 = "我不能说我对那次遭遇有美好的回忆。 巴巴松到底是谁? ";
			link.l1.go = "TK_TravlyaKrys_3";
		break;
		
		case "TK_TravlyaKrys_3":
			dialog.text = "雅克.巴巴松, 也被称为好人雅克, 领导着勒弗朗索瓦的匪巢。 他是所谓的海盗男爵之一, 在小安的列斯群岛从事海盗和走私活动, 制造麻烦。 他是一个臭名昭著的罪犯, 记住我的话, 他总有一天会在圣皮埃尔的绞刑架上结束生命! ";
			link.l1 = "对不起, 但你不是马提尼克真正的权威吗? 你不能就消灭那个巢穴吗? 我去过那里, 相信我, 没什么可看的。 ";
			link.l1.go = "TK_TravlyaKrys_4";
		break;
		
		case "TK_TravlyaKrys_4":
			dialog.text = "我劝你不要吹嘘你对我的岛屿上不那么体面的地方的了解, 查尔斯。 这不符合一个贵族的身份。 至于你的问题\n在我们的世界里, 不是所有的事情都可以用蛮力解决。 有政治和商业利益在起作用。 但我们不要深入不必要的细节: 我有一个需要一些蛮力的具体任务。 ";
			link.l1 = "请继续。 ";
			link.l1.go = "TK_TravlyaKrys_5";
		break;
		
		case "TK_TravlyaKrys_5":
			dialog.text = "巴巴松吸引了一些小团体, 渴望轻松的黄金。 有时他会给他们中的一个人一块骨头, 只是为了看他们都去争夺。 偶尔, 他会让幸存者工作, 但更多的时候, 他会把他们赶出去, 相信我, 没有什么比一个绝望的海盗在附近游荡更危险的了。 ";
			link.l1 = "我想我明白了, 但我不确定我是否准备好接受它。 我才刚刚开始指挥我的船, 我还在学习诀窍, 可以这么说...";
			link.l1.go = "TK_TravlyaKrys_6";
		break;
		
		case "TK_TravlyaKrys_6":
			dialog.text = "胡说! 你已经尝到了胜利的滋味 - 比我的大多数懒惰的军官都多! 城市将奖励你五千比索, 用于击沉另一艘巴巴松的老鼠, 免税。 如果你活捉海盗, 八千比索 - 当然是为了适当的处决。 ";
			link.l1 = "我当然可以用这笔钱。 我在哪里可以找到这个海盗? ";
			link.l1.go = "TK_TravlyaKrys_7";
			link.l2 = "对不起, 但我认为我还没有准备好接受这种任务。 ";
			link.l2.go = "TK_TravlyaKrys_Otkaz";
		break;
		
		case "TK_TravlyaKrys_Otkaz":
			dialog.text = "真遗憾, 查尔斯。 在这种情况下, 我不会再耽误你了。 ";
			link.l1 = "再见, 阁下。 ";
			link.l1.go = "exit";
		break;
		
		case "TK_TravlyaKrys_7":
			dialog.text = "我很高兴你加入, 查尔斯。 我们的情报报告显示,'仇恨者'号, 一艘小帆船, 目前正准备从勒弗朗索瓦出发。 我们不能再拖延了, 所以起航并交战。 别担心, 我的朋友, 你会成功的。 ";
			link.l1 = "愿上帝保佑, 阁下。 ";
			link.l1.go = "TK_TravlyaKrys_8";			
		break;
		
		case "TK_TravlyaKrys_8":
			DialogExit();
			SetQuestHeader("TravlyaKrys");
			AddQuestRecord("TravlyaKrys", "1");
			
			sld = GetCharacter(NPC_GenerateCharacter("TK_Heiter", "mercen_8", "man", "man", sti(PChar.rank), PIRATE, -1, true, "pirate"));
			sld.name = "丹尼尔";
			sld.lastname = "蒙特巴斯";
			FantomMakeSmallSailor(sld, SHIP_LUGGER, "Hater", CANNON_TYPE_CANNON_LBS3, 20, 40, 20, 25, 35);
			SetCharacterGoods(sld, GOOD_GOLD, 1);
			sld.AlwaysEnemy = true;
			sld.AlwaysSandbankManeuver = true;
			sld.DontRansackCaptain = true;
			
			Group_FindOrCreateGroup("HeiterAttack");
			Group_SetType("HeiterAttack", "pirate");
			Group_AddCharacter("HeiterAttack", "TK_Heiter");

			Group_SetGroupCommander("HeiterAttack", "TK_Heiter");
			Group_SetTaskAttack("HeiterAttack", PLAYER_GROUP);
			Group_SetAddress("HeiterAttack", "Martinique", "Quest_Ships", "Quest_Ship_6");
			Group_LockTask("HeiterAttack");
			
			PChar.quest.TK_Potopil.win_condition.l1 = "Character_sink";
			PChar.quest.TK_Potopil.win_condition.l1.character = "TK_Heiter";
			PChar.quest.TK_Potopil.win_condition = "TK_Potopil";
		break;
		//<—— 折磨老鼠
		
		//Jason --> 葡萄牙人
		case "Portugal":
			dialog.text = "当然可以, 船长! 这就是我打扰你的原因。 ";
			link.l1 = "那我洗耳恭听。 ";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "当地渔民昨晚在岛附近看到一艘奇怪的船。 正如他们所说, 那是一艘巨大的战船, 像一艘战列舰, 没有任何旗帜或信号灯。 我认为这艘船实际上不可能比护卫舰还大, 但即使那样也已经太多了! ";
			link.l1 = "恐惧把鼹鼠丘变成了大山, 这是肯定的...但重点是什么? ";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			dialog.text = "我只是转向你, 船长。 我的贸易伙伴被这些谣言吓坏了 - 他们认为这是海盗或西班牙私掠船, 这对贸易不利。 最糟糕的是 - 目前殖民地没有战舰, 只有几艘用于保护的小帆船和一艘旧纵帆船, 适合追捕走私者\n我不能置之不理...无论如何, 现在关于这艘神秘船的谣言已经被半个城市知道了! 请加入你的船来帮助我们找到它 - 我知道你是一个正派的船长, 即使真的只有一艘护卫舰, 你的大炮也可以说服它去别处寻找猎物! ";
			link.l1 = "先生...实际上, 我有不同的计划...";
			link.l1.go = "Portugal_3";
		break;
		
		case "Portugal_3":
			dialog.text = "请, 船长! 就几天, 直到这些不安的流言平息! 当然, 你会得到时间报酬。 一万八里亚尔适合你吗? ";
			link.l1 = "嗯...但是, 阁下, 我...";
			link.l1.go = "Portugal_4";
		break;
		
		case "Portugal_4":
			dialog.text = "如果你真的与这艘船交战, 我们会加倍, 如果你击沉它, 我们会三倍! 现在, 你怎么说? ";
			link.l1 = "好吧, 我本来就打算在这里呆几天。 ";
			link.l1.go = "Portugal_5";
		break;
		
		case "Portugal_5":
			dialog.text = "太好了, 我从未真正怀疑过你, 船长先生! 记住 - 只在我们的水域两天 - 钱就是你的了。 如果你被迫进入战斗, 你将根据结果获得报酬。 ";
			link.l1 = "我明白了, 阁下。 我们成交了, 我现在返回我的船。 ";
			link.l1.go = "Portugal_6";
		break;
		
		case "Portugal_6":
			dialog.text = "我会等你回来, 船长! ";
			link.l1 = "请允许我告辞。 ";
			link.l1.go = "Portugal_7";
		break;
		
		case "Portugal_7":
			DialogExit();
			AddQuestRecord("Portugal", "10");
			NextDiag.CurrentNode = "Portugal_8";
			LocatorReloadEnterDisable("Fortfrance_town", "reload1_back", false);
			LocatorReloadEnterDisable("Fortfrance_town", "reload2_back", false);
			LocatorReloadEnterDisable("Fortfrance_town", "gate_back", false);//打开城市出口
			bDisableFastReload = true;//关闭快速传送
			pchar.GenQuest.CannotWait = true;//禁止等待
			pchar.quest.Portugal_Seapatrol.win_condition.l1 = "location";
			pchar.quest.Portugal_Seapatrol.win_condition.l1.location = "Martinique";
			pchar.quest.Portugal_Seapatrol.function = "PortugalSeapatrolGo";
			pchar.quest.Portugal_SeapatrolAvendel.win_condition.l1 = "location";
			pchar.quest.Portugal_SeapatrolAvendel.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.Portugal_SeapatrolAvendel.function = "AvendelSpeach";
		break;
		
		case "Portugal_8":
			dialog.text = "船长, 我相信我们有一个协议, 你将在我们的沿海水域巡逻两天! ";
			link.l1 = "是的, 当然。 我记得。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Portugal_8";
		break;
		
		case "Portugal_9":
			dialog.text = "嗯, 你已经完成了你的部分交易。 这是你的奖励 - 一万比索, 正如我们所约定的。 ";
			link.l1 = "谢谢! 如你所见, 你的担忧是没有道理的。 祝你好运! ";
			link.l1.go = "Portugal_10";
		break;
		
		case "Portugal_10":
			DialogExit();
			AddMoneyToCharacter(pchar, 10000);
			NextDiag.CurrentNode = "First time";
			pchar.quest.MartiniqueGovernorOver.over = "yes"; //移除计时器
		break;
		//<—— 葡萄牙人
		
		// Warship, 16.05.11。 生成 "正义待售".
		case "JusticeOnSale_1":
			dialog.text = "哦" + GetAddress_Form(NPChar) + ", 你让我吃惊! 那些恶棍真的变得如此厚颜无耻了吗? 我必须立即通知指挥官并派一支沿海巡逻队到那里! ";
			link.l1 = "我很高兴能帮忙。 我现在可以走了吗? ";
			link.l1.go = "JusticeOnSale_2";
			
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait");
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale.PrisonWait");
			
			DeleteQuestCondition("JusticeOnSale_MapEnter");
		break;
		
		case "JusticeOnSale_2":
			dialog.text = "当然, 船长。 来 - 请接受这个来自我个人的微薄奖励。 ";
			link.l1 = "谢谢你。 ";
			link.l1.go = "JusticeOnSale_3";
		break;
		
		case "JusticeOnSale_3":
			AddQuestRecord("JusticeOnSale", "5");
			CloseQuestHeader("JusticeOnSale");
			
			AddMoneyToCharacter(PChar, 1000 + sti(PChar.rank) * 30 * hrand(10));
			
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale");
			
			DialogExit();
		break;
		
		case "JusticeOnSale_4":
			dialog.text = "你说得对, 船长! 我们不能就这样算了! 我想请你前往" + XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId + "Dat") + ", 找到他们的船并逮捕他们的整个团伙! 如果他们抵抗 - 动用武力, 不要犹豫! ";
			link.l1 = "请允许我告辞。 ";
			link.l1.go = "JusticeOnSale_5";
		break;
		
		case "JusticeOnSale_5":
			dialog.text = "现在走吧。 航行到那里, 确保没有人能逃脱正义。 我想你首先需要在岸边下船, 然后你就可以处理那艘船了。 ";
			link.l1 = "...";
			link.l1.go = "JusticeOnSale_6";
		break;
		
		case "JusticeOnSale_6":
			sld = GetCharacter(NPC_GenerateCharacter("JusticeOnSale_ShipPirate", "", "man", "man", sti(PChar.rank) + 5, PIRATE, -1, true, "quest"));
			sld.Ship.Type = GenerateShipExt(sti(PChar.GenQuest.JusticeOnSale.ShipType), true, sld);
			sld.Ship.Name = PChar.GenQuest.JusticeOnSale.ShipName;
			SetBaseShipData(sld);
			SetCrewQuantityFull(sld);
			Fantom_SetCannons(sld, "pirate");
			Fantom_SetBalls(sld, "pirate");
			Fantom_SetUpgrade(sld, "pirate");
			SetCaptanModelByEncType(sld, "pirate");
			SetRandGeraldSail(sld, PIRATE);
			
			Character_SetAbordageEnable(sld, false);
			
			Group_FindOrCreateGroup("JusticeOnSaleGroup");
			Group_AddCharacter("JusticeOnSaleGroup", "JusticeOnSale_ShipPirate");
			Group_SetGroupCommander("JusticeOnSaleGroup", "JusticeOnSale_ShipPirate");
			Group_SetAddress("JusticeOnSaleGroup", PChar.curislandid, "reload", Island_GetLocationReloadLocator(PChar.curislandid, PChar.GenQuest.JusticeOnSale.ShoreId));
			Group_SetTaskNone("JusticeOnSaleGroup");
			Group_LockTask("JusticeOnSaleGroup");
			
			sld.AlwaysFriend = true;
			SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_FRIEND);
			
			SetCharacterShipLocation(sld, PChar.GenQuest.JusticeOnSale.ShoreId);

			DeleteAttribute(sld, "SinkTenPercent");
			DeleteAttribute(sld, "SaveItemsForDead");
			DeleteAttribute(sld, "DontClearDead");
			DeleteAttribute(sld, "AboardToFinalDeck");
			
			sld.AlwaysSandbankManeuver = true;
			sld.AnalizeShips = true;
			sld.DontRansackCaptain = true;
			
			sld = &Locations[FindLocation(PChar.GenQuest.JusticeOnSale.ShoreId)];
			sld.DisableEncounters = true;
			
			PChar.Quest.JusticeOnSale_ShoreEnterFromMayor.win_condition.l1  = "location";
			PChar.Quest.JusticeOnSale_ShoreEnterFromMayor.win_condition.l1.location = PChar.GenQuest.JusticeOnSale.ShoreId;
			PChar.Quest.JusticeOnSale_ShoreEnterFromMayor.function = "JusticeOnSale_ShoreEnterFromMayor";
			
			PChar.Quest.JusticeOnSale_PirateShip_Sink.win_condition.l1 = "Character_sink";
			PChar.Quest.JusticeOnSale_PirateShip_Sink.win_condition.l1.character = "JusticeOnSale_ShipPirate";
			PChar.Quest.JusticeOnSale_PirateShip_Sink.function = "JusticeOnSale_PirateShip_Sink";
			
			DialogExit();
		break;
		
		case "JusticeOnSale_7":
			dialog.text = "谢谢你的帮助。 那些恶棍得到了应有的惩罚。 请允许我来自我个人向你赠送这个微薄的奖励。 我非常重视我镇的秩序与和平。 ";
			link.l1 = "...";
			link.l1.go = "JusticeOnSale_8";
		break;
		
		case "JusticeOnSale_8":
			AddMoneyToCharacter(PChar, sti(PChar.rank) * 300 + hrand(1000));
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale");
			DialogExit();
		break;
		//<—— 正义待售
		
			//--> Jason 帆船赛
		case "Regata":
			// belamour legendary edition -->
			if(sti(pchar.rank) < 20)
			{
				notification("需要20级", "None");
				dialog.text = "啊, 太好了, 很高兴见到你, 船长! 我听说过你的才能, 但等你真正准备好再来吧。 ";
				link.l1 = "是的, 当然。 如你所愿。 ";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "哦, 太好了, 很高兴见到你, 船长! 你来得正是时候 - 帆船赛几天后就要开始了。 你读过勤务兵一定给你的帆船赛规则了吗? ";
				link.l1 = "是的, 先生, 我读过了。 ";
				link.l1.go = "Regata_1";
				RemoveItems(PChar, "letter_open", 1);//移除信件
				DeleteAttribute(pchar, "questTemp.Regata.ToPortRoyal"); // patch-5
			}
		break;
		
		case "Regata_1":
			dialog.text = "你准备好五万比索了吗 - 你的参赛费, 将用于奖金? ";
			if (makeint(pchar.money) >= 50000)
			{
				link.l1 = "是的, 当然。 请接受我的费用。 ";
				link.l1.go = "Regata_2";
			}
			link.l2 = "我现在钱有点短缺。 但我一定会筹集到所需的金额。 ";
			link.l2.go = "Regata_nomoney";
		break;
		
		case "Regata_2":
			dialog.text = "非常好。 如果你赢了 - 你将得到五倍的钱。 现在你需要更好地了解帆船赛的规则\n你可以从亨利.斯蒂文森爵士那里了解所有细节, 他应该在官邸的一个房间里。 去找他 - 他会解释一切。 ";
			link.l1 = "好的。 我会的。 ";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -50000);
			pchar.quest.Regata_Guber.win_condition.l1 = "location";
			pchar.quest.Regata_Guber.win_condition.l1.location = "Portroyal_Roomtownhall";
			pchar.quest.Regata_Guber.function = "PrepareToRegataInPortroyal";
			pchar.questTemp.Regata.Begin = "true";
			NextDiag.TempNode = "First time";
		break;
		
		case "Regata_nomoney":
			dialog.text = "好吧, 但请不要太久, 船长。 帆船赛很快就要开始了。 ";
			link.l1 = "我明白。 我会尽量尽快把钱带给你。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_1";
			pchar.questTemp.Regata.nomoney = "true";
		break;
		
		//帆船赛-决赛
		case "Regata_Final":
			dialog.text = "啊哈! 这就是帆船赛的冠军! 日安, " + GetFullName(pchar) + "船长! 请允许我祝贺你取得这个当之无愧的成功! 帆船赛的冠军在英国殖民地一直很受欢迎 - 而且理由充分。 ";
			link.l1 = "谢谢你, 先生! ";
			link.l1.go = "Regata_complete";
		break;
		
		case "Regata_complete":
			dialog.text = "现在让我们跳到最愉快的部分 - 颁奖仪式。 第一名的奖金是25万比索。 恭喜! ";
			link.l1 = "谢谢! ";
			link.l1.go = "Regata_complete_1";
		break;
		
		case "Regata_complete_1":
			AddMoneyToCharacter(pchar, 250000);
			// belamour legendary edition 在帆船赛中只有一个奖项 -->
			GiveItem2Character(pchar, "blade_26");
			GiveItem2Character(pchar, "cirass4");
			GiveItem2Character(pchar, "bussol");
			
			dialog.text = "此外, 你还将获得一套有价值的奖品: 传奇的托莱多钢制细剑'阿索莱达', 一套米兰盔甲, 和一个精美的指南针。 都是你的了。 ";
			// <—— legendary edition
			link.l1 = "我很高兴, 先生。 真的, 我没想到会有这样的慷慨。 ";
			link.l1.go = "Regata_complete_2";
		break;
		
		case "Regata_complete_2":
			dialog.text = "我代表英国殖民地的所有臣民感谢你参加帆船赛, 并再次祝贺你的胜利! 如果你下了赌注, 去找亨利.斯蒂文森爵士, 如果你还没有的话, 领取你的奖金。 祝你好运, 船长! ";
			link.l1 = "谢谢你的客气话, 先生! 反过来, 请允许我感谢你为我提供了参加如此盛大活动的机会。 现在请允许我告辞。 ";
			link.l1.go = "Regata_complete_3";
		break;
		
		case "Regata_complete_3":
			DialogExit();
			NextDiag.CurrentNode = "First time";
		break;
		//<—— 帆船赛
	}
}

string GetGangLocation(ref npchar)
{
    int n;
	string island = GetArealByCityName(npchar.city);
	string LocationId, sAreal;
	int storeArray[2];
	SetArraySize(&storeArray, MAX_LOCATIONS);  
    int howStore = 0;

	for(n=0; n<MAX_LOCATIONS; n++)
	{				
		if (GiveArealByLocation(&locations[n]) == island)
		{			
			//==> 以防万一
			if (CheckAttribute(&locations[n], "DisableEncounters") && locations[n].DisableEncounters == true) continue;
			LocationId = locations[n].id;
			if (findsubstr(LocationId, "jungle" , 0) != -1 || findsubstr(LocationId, "Shore" , 0) != -1 || findsubstr(LocationId, "CaveEntrance" , 0) != -1)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	n = storeArray[hrand(howStore-1)];
	return locations[n].id;
}

string GetSpyLocation(ref npchar)
{
    aref	arCommon, arRld, arRld2;
    int	i, n, Qty, Qty2;
	string LocId; 
	string	storeArray [50];
	int howStore = 0;
    makearef(arRld, Locations[FindLocation(npchar.city + "_town")].reload);
	Qty = GetAttributesNum(arRld);
	if (CheckAttribute(pchar, "questTemp.jailCanMove.Deliver.locationId")) //如果接受了运送麻鸭的任务
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.questTemp.jailCanMove.Deliver.locationId)
    		{			
				storeArray[howStore] = LocId;
				howStore++; 
			}
			if (arCommon.label != "Sea")
			{	
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.questTemp.jailCanMove.Deliver.locationId && LocId != "CommonPackhouse_1" && LocId != "CommonPackhouse_2")
    				{
						storeArray[howStore] = LocId;
						howStore++; 					
					}
				}
			}	
		}
	}
	else
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1)
    		{			
				storeArray[howStore] = LocId;
				howStore++; 
			}
			if (arCommon.label != "Sea")
			{	
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1 && LocId != "CommonPackhouse_1" && LocId != "CommonPackhouse_2")
    				{
						storeArray[howStore] = LocId;
						howStore++; 					
					}
				}
			}	
		}
	}
	if (howStore == 0) return "none";
	LocId = storeArray[hrand(howStore-1)];
	SetOpenDoorCommonLoc(npchar.city, LocId); //打开门
	for(n=0; n<MAX_CHARACTERS; n++)
	{
		if (CheckAttribute(&characters[n], "locations") && characters[n].locations == LocId) 
		{			
			characters[n].lifeDay = 0;
		}
	}
	return LocId;
}

string GetSpyColony(ref NPChar)
{
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;
	string sChrId;

	for(int n=0; n<MAX_COLONIES; n++)
	{
		// Rebbebion, 稍微修改了函数, 以便原则上西班牙人不要求渗透到西班牙人那里, 法国人到法国人那里等
		if (colonies[n].nation != "none" && sti(colonies[n].nation) != PIRATE && GetRelation2BaseNation(sti(colonies[n].nation)) == RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != "LosTeques" && colonies[n].id != "SanAndres" && colonies[n].id != npchar.City && colonies[n].nation != npchar.nation)
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	return colonies[storeArray[Rand(howStore-1)]].id;
}

int SelectCureerShipType()
{
	int iClass = 6;
	int iRank = sti(pchar.rank);
	
	if(iRank < 6) iClass = 6;
	if(iRank >= 6 && iRank < 12) iClass = 6 - rand(1);
	if(iRank >= 12 && iRank < 21) iClass = 5 - rand(1);
	if(iRank >= 21) iClass = 4 - rand(1);
	
	return GetRandomShipType(GetClassFlag(iClass), FLAG_SHIP_TYPE_RAIDER + FLAG_SHIP_TYPE_UNIVERSAL, FLAG_SHIP_NATION_ANY);
}

int SelectPirateShipType()
{
	int iClass = 6;
	int iRank = sti(pchar.rank);
	
	if(iRank < 6) iClass = 6;
	if(iRank >= 6 && iRank < 12) iClass = 5;
	if(iRank >= 12 && iRank < 21) iClass = 4;
	if(iRank >= 21 && iRank < 30) iClass = 4 - rand(1);
	if(iRank >= 30) iClass = 2;
	
	return GetRandomShipType(GetClassFlag(iClass), FLAG_SHIP_TYPE_RAIDER + FLAG_SHIP_TYPE_UNIVERSAL + FLAG_SHIP_TYPE_WAR, FLAG_SHIP_NATION_ANY);
}

int SelectCustomPatrolShipType(int iFlagType)
{
	if(CheckAttribute(pchar, "questTemp.StatusCity"))
	{
		return SHIP_CAREERLUGGER;
	}
	
	int iClass = 6;
	int iRank = sti(pchar.rank);
	
	if(iRank < 6) iClass = 6;
	if(iRank >= 6 && iRank < 12) iClass = 6 - rand(1);
	if(iRank >= 12 && iRank < 21) iClass = 5 - rand(1);
	if(iRank >= 21) iClass = 4 - rand(1);
	
	return GetRandomShipType(GetClassFlag(iClass), iFlagType, FLAG_SHIP_NATION_ANY);
}

int SelectArsenalShipType(int iFlagType)
{
	int iClass = 6;
	int iRank = sti(pchar.rank);
	
	if(iRank < 6) iClass = 6;
	if(iRank >= 6 && iRank < 12) iClass = 6 - rand(1);
	if(iRank >= 12 && iRank < 21) iClass = 5 - rand(1);
	if(iRank >= 21 && iRank < 30) iClass = 4 - rand(1);
	if(iRank >= 30) iClass = 2;
	
	return GetRandomShipType(GetClassFlag(iClass), iFlagType, FLAG_SHIP_NATION_ANY);
}

string SelectPassText()
{
	string sText;
	switch (hrand(5))
	{
		case 0: sText = "那个犹大利用自己的职位, 向敌国出售了一个重要的国家机密。 "; break;
		case 1: sText = "那个卑鄙的恶棍为了继承他的财富, 杀死了他的一个知名贵族亲戚。 "; break;
		case 2: sText = "那个卑鄙的恶棍侮辱了我的家人和我本人。 "; break;
		case 3: sText = "这个盗窃的流氓从我们城市的国库中偷了一大笔钱。 "; break;
		case 4: sText = "那个恶棍对近十名我们的公民的死亡负有责任。 "; break;
		case 5: sText = "那个流氓利用他的关系占有了一艘商船, 然后他偷了它并在邻近的造船厂出售。 "; break;
	}
	return sText;
}

string SelectFugitiveCity()
{
	string sCity;
	switch (rand(3))
	{
		case 0: sCity = "拉维加"; break;
		case 1: sCity = "普林西比港"; break;
		case 2: sCity = "勒弗朗叙阿"; break;
		case 3: sCity = "奥兰治堡"; break;
	}
	return sCity;
}

string SelectFugitiveText()
{
	string sText;
	switch (hrand(5))
	{
		case 0: sText = "我们驻军中的一名初级军官开小差, 乘坐商船离开了殖民地。 "; break;
		case 1: sText = "我们的一名军官在执勤时开小差, 乘坐走私船逃跑了。 "; break;
		case 2: sText = "我们在巡逻双桅船上服役的一名海军军官因未知原因开小差, 劫持了一艘长艇并消失在上面。 "; break;
		case 3: sText = "我们的一名监狱看守因未知原因辞职, 乘坐私人船只离开了我们的殖民地。 "; break;
		case 4: sText = "我们驻军中的一名士兵在站岗时放弃了岗位, 前往海湾并乘坐未知船只离开了这个地方。 "; break;
		case 5: sText = "我们的一名军事军官, 巡逻小帆船的船长, 在公海上放弃了他的船, 乘坐渔船向南而去。 "; break;
	}
	return sText;
}
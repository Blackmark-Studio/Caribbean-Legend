// BOAL 俘虏对话 - 在囚室
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ref offref;
    int i, cn;
    int qty;
    string attrLoc, sTmp;
    
	switch(Dialog.CurrentNode)
	{
		// -----------------------------------首次对话 - 第一次见面
		case "First time":
		//--> Jason, 虚假线索
		if (CheckAttribute(pchar, "questTemp.FalseTrace.Prisoner") && GetFullName(npchar) == pchar.questTemp.FalseTrace.CapName)
		{
			dialog.text = "你想要什么, 船长? 讨论我的赎金吗? 我想让你知道我关心那个女孩的命运... ";
			link.l1 = "你说的是凯瑟琳.雷纳吗? 我已经知道了, " + pchar.questTemp.FalseTrace.CapName + "。 她让我来和你谈谈。 ";
			link.l1.go = "FalseTrace_Prisoner";
			break;	
		}
		//< —虚假线索
		
		// Addon-2016 Jason FMK-瓜德罗普
		if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG != "fail" && CheckAttribute(pchar, "questTemp.FMQG.Prisoner") && GetFullName(npchar) == pchar.questTemp.FMQG.Prisoner)
		{
			dialog.text = "";
			link.l1 = "现在明白了吧, 唐璜, 背叛是不好的... ";
			link.l1.go = "FMQG";
			break;	
		}
			if (sti(NPChar.nation) == PIRATE)
			{
				dialog.text = RandSwear() + "我是你的俘虏, " + GetAddress_Form(NPChar) + "。 但我想让你知道" + NationNameNominative(sti(NPChar.nation)) + "从不为自己人支付赎金。 我们都是为自己。 ";
				link.l1 = "好吧... 看来我从你身上赚不到钱。 至少我可以在任何殖民地把你作为罪犯赎出去。 ";
				link.l1.go = "offender";
				if (FindFreeRandomOfficer() > 0)
				{
					link.l2 = "看, 你是个熟练的战士, 我需要像你这样的人。 你愿意在我的指挥下服役吗? ";
					link.l2.go = "free_to_officer";
				}	
			}
			else
			{
				dialog.text = RandSwear() + "我是你的俘虏, " + GetAddress_Form(NPChar) + "。 " + NationNameNominative(sti(NPChar.nation)) + "会为我的自由支付高价。 ";
				if(NPChar.EncType == "trade" && FindFreeRandomOfficer() > 0 && CheckAttribute(NPChar, "Back.Ship.Mode") && NPChar.Back.Ship.Mode == "trade")
				{
					link.l1 = "看, 你是个熟练的水手, 我需要像你这样的人。 你愿意在我的指挥下服役吗? ";
					link.l1.go = "free_to_officer_trader";
				}
			}
			attrLoc = Sea_FindNearColony();
			if (attrLoc != "none") 
			{
                link.l3 = "我们离" + GetConvertStr(attrLoc +" Town", "LocLables.txt") + "不远。 我可以在这里放你走。 ";
			    link.l3.go = "free_withoutFee";
			}
			else
			{
                link.l3 = "去找水手长, 让他给你一个储物柜。 你可以在下一个港口上岸。 ";
			    link.l3.go = "free_withoutFee_2";
			}			
			link.l4 = "我想我会把你变成一个很棒的奴隶 - 强壮又尽职。 ";
			link.l4.go = "Slave_1";
			link.l5 = "你无视了降帆的命令并进行了抵抗。 你将因此被绞死。 水手长已经收到了我的命令。 ";
			link.l5.go = "PunishmentAction";
			link.l99 = "我知道。 ";
			link.l99.go = "exit";
			NextDiag.TempNode = "second time"; 
		break;
		
		case "second time":
			if(CheckAttribute(NPChar,"Hold_GenQuest") && !CheckAttribute(pchar,"GenQuest.Hold_GenQuest"))
			{
				switch(sti(NPChar.Hold_GenQuest.variant))
				{				
					case 0: // "情报"
						dialog.text = RandPhraseSimple("船长, 你想听听我关于赎金更有利方案的建议吗? ",
							"我知道在我这个位置没有讨价还价的余地, 但你想听听我的建议吗? ");
						link.l1 = "我在听。 ";	
						link.l1.go = "free_tip_off";
					break;
					
					case 1:
						dialog.text = "船长, 你为什么不直接释放我? 我对你没有价值。 如果你把我卖给奴隶贩子, 你只会得到几个硬币和不好的名声。 ";
						link.l1 = "如果我直接释放你, 我什么也得不到... ";
						link.l1.go = "free_by_hoard";
						attrLoc = Sea_FindNearColony();
						if (attrLoc != "none") 
						{
							link.l2 = "你无视了降帆的命令并进行了抵抗。 你将因此被绞死。 水手长已经收到了我的命令。 ";
							link.l2.go = "PunishmentAction";							
						}
						else
						{
							link.l2 = "你真的很坚持, 所以我想我可以给你想要的。 你现在自由了。 离开我的船。 ";
							link.l2.go = "free_in_sea";
						}
						link.l3 = LinkRandPhrase("别考验我的耐心。 你能活着已经很幸运了。 ",
							"我对你有自己的计划。 ", "我想你将来对我仍然有用。 ");
						link.l3.go = "exit";	
					break;
					
					case 2: // "赎金"
						dialog.text = "船长, 这种不确定性快把我逼疯了。 我可以知道你打算怎么处置我吗? ";
						link.l1 = "你有什么可以给我吗? ";
						link.l1.go = "free_buyout";
						link.l2 = RandPhraseSimple("我还没有任何关于你的想法。 ",
							RandPhraseSimple("计划? 你脖子上的炮弹? 我开玩笑的, 哈! ", "你是我的俘虏, 我有权对你做任何想做的事。 你的意见在这里没有价值。 "));
						link.l2.go = "exit";
					break;										
				}
				NextDiag.TempNode = "second time"; 
			}
			else
			{
				if (sti(NPChar.nation) == PIRATE)
				{
					dialog.text = "船长, 你为什么不直接放我走? 你不需要我。 选择当海盗是我唯一的选择, 因为我没有有价值的技能或教育。 我的愿望是赚些钱然后退休。 ";
					if (FindFreeRandomOfficer() > 0)
					{
						link.l2 = "看, 你是个熟练的战士, 我需要像你这样的亡命之徒。 你想成为我的军官吗? ";
						link.l2.go = "free_to_officer";
					}				
					link.l3 = LinkRandPhrase("不会对你仁慈。 海上有很多暴徒。 至少现在少了一个在那里航行的人。 ",
						"有什么问题吗,'海狼'? 待在这里保持安静。 ",
						"绞刑架在等待你们所有这类人。 我会把你卖给当局, 这将是对任何海盗的一个很好的教训。 ");	
					link.l3.go = "exit";
				}
				else
				{
					if(NPChar.EncType == "trade")
					{
						dialog.text = "船长, 我求你... 释放我。 我有家庭和孩子, 没有我他们活不下去。 ";
						if (FindFreeRandomOfficer() > 0 && CheckAttribute(NPChar, "Back.Ship.Mode") && NPChar.Back.Ship.Mode == "trade")
						{
							link.l2 = "看, 你是个熟练的水手, 我需要像你这样的人。 你愿意在我的指挥下服役吗? ";
							link.l2.go = "free_to_officer_trader";
						}
						link.l3 = LinkRandPhrase("我对你有自己的计划。 ", "我想你将来对我仍然有用。 ", "你是我的俘虏, 我有权对你做任何想做的事。 ");
						link.l3.go = "exit";
					}
					if(NPChar.EncType == "war")
					{
						dialog.text = RandPhraseSimple("船长, 我打输了, 求你仁慈。 ",
							"船长, 我请求你的慷慨。 我知道你没有理由把我当作战俘对待, 所以我请求你饶了我。 我向你保证我会避免在海上与你相遇。 ");
						link.l2 = LinkRandPhrase("别考验我的耐心。 你能活着已经很幸运了。 ", 
							RandPhraseSimple("我对你有自己的计划。 ", "我想你将来对我仍然有用。 "),
							RandPhraseSimple("你是我的俘虏, 我有权对你做任何想做的事。 你的意见在这里没有价值。 ",
							"你是... 嗯, 你曾是战船的船长, 你知道风险。 不要在这里把自己描绘成圣人。 "));
						link.l2.go = "exit";	
						if (isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 1)
						{
							if(sti(Items[sti(pchar.EquipedPatentId)].Nation) == sti(NPChar.nation) && FindFreeRandomOfficer() > 0)
							{
								link.l3 = "看, 你是个熟练的战士, 我需要像你这样的亡命之徒。 你想成为我的军官吗? ";
								link.l3.go = "free_to_officer";
							}
						}
					}
				}
				attrLoc = Sea_FindNearColony();
				if (attrLoc != "none") 
				{
					link.l4 = "我们离" + GetConvertStr(attrLoc +" Town", "LocLables.txt") + "不远。 我可以在这里放你走。 ";
					link.l4.go = "free_withoutFee";
				}
				else
				{
					if(NPChar.EncType == "trade" || NPChar.EncType == "pirate")
					{
						link.l4 = "去找水手长, 让他给你一个储物柜。 你可以在下一个港口上岸。 ";
						link.l4.go = "free_withoutFee_4";			
					}	
					else
					{
						link.l4 = "去你的! 去找水手长, 让他给你一个储物柜。 你可以在下一个港口上岸。 记住我们下次见面将是最后一次。 ";
						link.l4.go = "free_withoutFee_4";
					}
				}				
				link.l5 = "你无视了降帆的命令并进行了抵抗。 你将因此被绞死。 水手长已经收到了我的命令。 ";
				link.l5.go = "PunishmentAction";
				NextDiag.TempNode = "second time"; 
			}	
		break;
		
		case "offender":
			dialog.text = "罪犯? 你在开玩笑吗, " + GetAddress_Form(NPChar) + "! ";
			link.l1 = "不是开玩笑。 你是个海盗。 ";
			link.l1.go = "exit";
		break;
		
		case "free_to_officer":
			if ((GetSummonSkillFromName(pchar, "Leadership") + 20) <= GetSummonSkillFromName(npchar, "Leadership"))
			{
				dialog.text = "在你的指挥下服役? 我宁愿喂鲨鱼! ";
				link.l1 = "注意你的言辞, 否则你会喂它们。 ";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "成为你的军官, " + GetAddress_Form(NPChar) + "? 我同意。 我知道我的工作, 而且我没有什么可失去的。 ";
				link.l1 = "成交! 去做你的工作。 ";
				link.l1.go = "free_to_officer_Hire";
				link.l2 = "等一下, 我改变主意了。 ";
				link.l2.go = "exit";
			}
		break;

		case "free_to_officer_trader":
			if (GetSummonSkillFromName(pchar, "Leadership") <= GetSummonSkillFromName(npchar, "Leadership"))
			{
				dialog.text = LinkRandPhrase("这是一个诱人的提议... 但我必须拒绝。 原则上。 ",
					"抱歉, 但在你对我的朋友做了那些之后... 这是不可能的。 ",
					"不, 船长。 在经历了所有这些恐惧之后, 我不能再做这份工作了。 我发誓如果圣母听到我的祈祷并赐予我自由, 我就不再航行。 ");
				link.l1 = "这是你的选择。 我不会坚持。 ";	
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "为什么不呢? 我是个糟糕的船长, 失去了我的船, 岸上也没有什么留给我了。 除了账单和债务... ";
				link.l1 = "成交! 去找水手长领取你的津贴。 我稍后会在我的船上给你一个职位。 ";	
				link.l1.go = "free_to_officer_Hire";
				link.l2 = "等一下, 我改变主意了。 ";
				link.l2.go = "exit";
			}
		break;
		
		case "free_to_officer_Hire":
            NPChar.Dialog.Filename = "Enc_Officer_dialog.c";
            NPChar.greeting = "Gr_Officer";
            NPChar.loyality = 5 + rand(10);
		    if (sti(NPChar.reputation) > 41)
		    {
		        NPChar.alignment = "good";
		    }
		    else
		    {
		        NPChar.alignment = "bad";
		    }
            ReleasePrisoner(NPChar); // 释放了俘虏
            DeleteAttribute(NPChar, "LifeDay") // 永久
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			// 这里三个累积的弯刀和船只 290704 BOAL -->
			DeleteAttribute(Npchar, "Ship");
			Npchar.Ship.Type = SHIP_NOTUSED;
            DeleteAttribute(Npchar, "Fellows"); // 他的军官
            Npchar.Fellows.Passengers.id0 = Npchar.index; // 自己的乘客

			Npchar.Fellows.Passengers.boatswain = "-1";
			Npchar.Fellows.Passengers.navigator = "-1";
			Npchar.Fellows.Passengers.doctor = "-1";
			Npchar.Fellows.Passengers.cannoner = "-1";
			Npchar.Fellows.Passengers.treasurer = "-1";
			Npchar.Fellows.Passengers.carpenter = "-1";
            
			if(CheckAttribute(NPChar,"Hold_GenQuest")) DeleteAttribute(NPChar, "Hold_GenQuest");
			
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			DialogExit();
        break;
				
		case "Slave_1":
			dialog.text = "但是" + GetAddress_Form(NPChar) + ", 你不能这样做! 我已经投降了。 ";
            link.l1 = "闭嘴! ... 把他绑起来。 ";
			link.l1.go = "Slave_2";
			link.l99 = "好吧。 待在这里直到我决定... ";
			link.l99.go = "exit";
		break;
		
		case "Slave_2":
			OfficersReaction("bad");		
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
            if (rand(5) == 1)
            {
    			dialog.text = "没门! 我宁愿自杀也不愿成为奴隶! ";
                link.l1 = "住手! 这是命令! ... 水手长! 清理货物... ";
    			link.l1.go = "free_in_sea_4";
			}			
			else
			{
                if (rand(1) == 1)
                {
                    if (GetPrisonerQty() > 1)
                    {
                        dialog.text = "屠夫! 伙计们加入我, 我们没什么可失去的! ";
                        link.l1 = "错误的选择, 女士们。 我自己处理叛变, 而且速度很快... ";
            			link.l1.go = "free_in_sea_battle_all";
                    }
					else
					{
						dialog.text = "没门! 我宁愿在战斗中死去! ";
						link.l1 = "如你所愿... ";
						link.l1.go = "free_in_sea_battle_1";
					}	
    			}
    			else
    			{
					dialog.text = "哦, 我同意。 我别无选择。 ";
                    link.l1 = "太好了。 做一个活着的奴隶比做一个死去的英雄更好。 ";
        			link.l1.go = "Slave_3";				
    			}			
			}
		break;

		case "Slave_3":
            ReleasePrisoner(NPChar); // 俘虏成为奴隶
        	LAi_SetActorType(NPChar);
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
        	ChangeCharacterComplexReputation(pchar,"nobility", -6);
        	DialogExit();
        	AddCharacterGoodsSimple(pchar, GOOD_SLAVES, 1);
        break;

		case "free_withoutFee":
			dialog.text = "哦, " + GetAddress_Form(NPChar) + ", 你真的那么善良, 不收取赎金就释放我吗? ";
            link.l1 = "是的, 我是。 你现在自由了, " + GetFullName(NPChar);
			link.l1.go = "free_withoutFee_2";
			link.l99 = "嗯... 你有道理! 我需要更多时间来决定。 ";
			link.l99.go = "exit";
		break;

		case "free_withoutFee_2":
			dialog.text = "谢谢你, " +GetFullName(pchar)+ "! 我会为你祈祷。 ";
            link.l1 = "现在走吧, 尽量活下去, 否则我的慷慨就白费了。 ";
			link.l1.go = "free_withoutFee_3";
			OfficersReaction("good");
		break;
		
		case "free_withoutFee_3":
            ReleasePrisoner(NPChar); // 释放了俘虏
        	LAi_SetActorType(NPChar);
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
        	ChangeCharacterComplexReputation(pchar,"nobility", 2);
        	DialogExit();
        break;	

		case "free_withoutFee_4":	
			switch(NPChar.EncType)
			{
				case "pirate":
					dialog.text = RandPhraseSimple("谢谢你, 船长。 我永远不会忘记你的好意。 我打算离开这个工作, 在平静的港口修理小船。 我可以做到。 ",
						"谢谢你, 船长! 我发誓, 我会放弃这个忘恩负义的职业, 成为一名渔夫。 ");
					link.l1 = "如果你是诚实的, 那么祝你好运, 如果不是, 那就祈祷永远不要再见到我... ";	
				break;
				case "trade":
					dialog.text = "甚至不知道如何感谢你, 船长。 我已经失去了希望。 我会告诉每个人你的好意。 我向你保证我会为你点一支蜡烛! 只要让我到达教堂。 ";
					link.l1 = "再见。 下次甚至不要尝试抵抗。 向我开枪, 这将是你和你船员的死刑判决。 ";
				break;
				case "war":
					dialog.text = "谢谢你, 船长。 我会为你祈祷。 ";
					link.l1 = "祝你好运, 记住, 如果你决定追捕我, 那将是你的末日。 ";
				break;
			}
			link.l1.go = "free_withoutFee_3";
		break;
		
		case "free_in_sea_battle_1":
            ReleasePrisoner(NPChar); // 释放了俘虏        	
        	LAi_LocationFightDisable(&Locations[FindLocation("My_Deck")], false);
            LAi_SetFightMode(Pchar, true);
            LAi_SetWarriorType(NPChar);
            LAi_group_MoveCharacter(NPChar, LAI_GROUP_TmpEnemy);
            LAi_group_SetHearRadius(LAI_GROUP_TmpEnemy, 100.0);
            LAi_group_FightGroupsEx(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
            LAi_group_SetRelation(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_SetCheck(LAI_GROUP_TmpEnemy, "My_Deck_Battle_End");
            LAi_group_SetRelation(LAI_GROUP_TmpEnemy, "Prisoner", LAI_GROUP_NEITRAL);
        	DialogExit();
        break;		

		case "free_in_sea_battle_all":
			//ugeen --> 你好 西瓦尔德 !!! 释放俘虏后乘客数量减少, 循环不再触发
			for(int j = GetPassengersQuantity(pchar) - 1; j > -1; j--)
            {
                cn = GetPassenger(pchar, j);
                if(cn != -1)
                {
                    offref = GetCharacter(cn);
                    if (CheckAttribute(offref,"prisoned"))
                    {
        	            if(sti(offref.prisoned)==true && GetRemovable(offref)) // 只设置幽灵
        	            {
                        	ReleasePrisoner(offref); // 释放了俘虏
							LAi_SetWarriorType(offref);
							LAi_warrior_DialogEnable(offref, false);
                            LAi_group_MoveCharacter(offref, LAI_GROUP_TmpEnemy);
                        }
                    }
                }
            }
            LAi_LocationFightDisable(&Locations[FindLocation("My_Deck")], false);
            LAi_SetFightMode(Pchar, true);
			LAi_group_SetHearRadius(LAI_GROUP_TmpEnemy, 100.0);
            LAi_group_FightGroupsEx(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
            LAi_group_SetRelation(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_SetCheck(LAI_GROUP_TmpEnemy, "My_Deck_Battle_End");
        	DialogExit();
        break;
		
		case "free_in_sea_4":
        	ReleasePrisoner(NPChar); // 释放了俘虏
            NPChar.location = "";
	        LAi_KillCharacter(NPChar);
        	DialogExit();
        break;

		case "PunishmentAction":
			dialog.text = "但是" + GetAddress_Form(NPChar) + ", 你不能这样做! 我已经投降了。 ";
			link.l1 = "只是在你的人走了之后。 你背叛了他们... 水手长! 带他走。 ";
			link.l1.go = "PunishmentAction1";
			link.l2 = "嗯... 我需要时间考虑。 待在这里。 ";
			link.l2.go = "exit";
        break;

		case "PunishmentAction1":
			OfficersReaction("bad");		
			ChangeCharacterComplexReputation(pchar,"nobility", -2);			
			AddCharacterExpToSkill(Pchar, "Leadership", -150);
			if (rand(1) == 1)
            {
                if (GetPrisonerQty() > 1)
                {
                    dialog.text = "屠夫! 伙计们, 我们没什么可失去的! ";
                    link.l1 = "错误的选择, 女士们。 我自己处理叛变, 而且速度很快... ";
					link.l1.go = "free_in_sea_battle_all";
                }
				else
				{
					dialog.text = "没门! 我宁愿在战斗中死去! ";
					link.l1 = "如你所愿... ";
					link.l1.go = "free_in_sea_battle_1";
				}	
    		}
			else
    		{
				dialog.text = "至少给我一些时间祈祷... ";
                link.l1 = "如果你想的话, 祈祷吧。 ";
        		link.l1.go = "PunishmentAction2";				
    		}						
		break;
		
		case "PunishmentAction2":
        	ReleasePrisoner(NPChar); // 释放了俘虏
            NPChar.location = "";		
			NPChar.LifeDay = 0;
			LAi_CharacterDisableDialog(NPChar);
			DialogExit();
		break;
		
		case "free_tip_off":
			dialog.text = "我有一个有趣的信息, 可能对像你这样的人有用。 但我需要你保证作为交换我将获得自由。 ";
			link.l1 = "如果我甚至不知道你的提议, 我怎么给你保证? 我怀疑你的信息甚至不会给我带来任何东西。 ";
			link.l1.go = "free_tip_off_0";
			link.l2 = "我只能给你我的承诺。 ";
			link.l2.go = "free_tip_off_1";
		break;
		
		case "free_tip_off_0":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);			
			DeleteAttribute(NPChar, "Hold_GenQuest");
			DialogExit();
		break;
		
		case "free_tip_off_1":
			switch(NPChar.EncType)
			{
				case "trade":
					sTmp = "他向我提议运输货物, 但这家伙太贪婪了, 我拒绝了这个提议。 ";  
				break;
				case "war":
					sTmp = "我曾几次作为 convoy 的指挥官护送他。 ";
				break;
				case "pirate":
					sTmp = "我曾经有过抢劫他的想法, 但我从来没有机会这样做。 ";
				break;
			}
			dialog.text = "好的。 这对我来说足够了。 现在直奔主题, 在" + XI_ConvertString("Colony" + NPChar.Hold_GenQuest.City + "Voc") + "住着一位富有的商人" + NPChar.Hold_GenQuest.Name + "。 " + 
				"他在他的船'" + NPChar.Hold_GenQuest.ShipName + "上通过出售" + GetStrSmallRegister(XI_ConvertString(Goods[sti(NPChar.Hold_GenQuest.Goods)].Name + "Acc")) + "发了财, 航线是: " + XI_ConvertString("Colony" + NPChar.Hold_GenQuest.FromCity) + " - " + XI_ConvertString("Colony" + NPChar.Hold_GenQuest.ToCity) +"。 " + 
				"当他货物太多时, 他会支付护送费用。 " + sTmp + " 我相信这个信息对你来说比一个人的生命更有价值。 ";
			link.l1 = "怀疑这个信息对我有用。 我不会追捕和平的商人。 ";	
			link.l1.go = "free_tip_off_0";
			link.l2 = "不确定这个信息对我有用, 但我已经给了你我的承诺。 水手长会把你和我的船员放在一起, 并让你在最近的港口下船。 ";
			link.l2.go = "free_tip_off_2";			
		break;
		
		case "free_tip_off_2":
			dialog.text = "谢谢你, 船长! 我毫不怀疑你的诚实! ";
			link.l1 = RandPhraseSimple(RandPhraseSimple("我希望我能对你也这么说", "抱歉, 但我不能对你也这么说。 "),
				RandPhraseSimple("走吧, 记住下次我不会那么慷慨。 ", "走吧, 别挡我的路。 下次我不会那么容易相信你。 "));
			link.l1.go = "free_tip_off_3";
		break;
		
		case "free_tip_off_3":
			pchar.GenQuest.Hold_GenQuest.Goods 			= NPChar.Hold_GenQuest.Goods;			
			pchar.GenQuest.Hold_GenQuest.Nation 		= NPChar.Hold_GenQuest.Nation; 
			pchar.GenQuest.Hold_GenQuest.Name 			= NPChar.Hold_GenQuest.Name;
			pchar.GenQuest.Hold_GenQuest.ToCity 		= NPChar.Hold_GenQuest.ToCity;
			pchar.GenQuest.Hold_GenQuest.FromCity 		= NPChar.Hold_GenQuest.FromCity; 
			pchar.GenQuest.Hold_GenQuest.ShipName 		= NPChar.Hold_GenQuest.ShipName;				
			pchar.GenQuest.Hold_GenQuest.City 			= NPChar.Hold_GenQuest.City;
			pchar.GenQuest.Hold_GenQuest.CapName		= GetFullName(NPChar);
			pchar.GenQuest.Hold_GenQuest.Island			= GetArealByCityName(pchar.GenQuest.Hold_GenQuest.City); 
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern 	= true;
			
			ReOpenQuestHeader("HoldQuest");
			AddQuestRecord("HoldQuest", "1");
			AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.Hold_GenQuest.Goods)].Name + "Acc"))); 
			AddQuestUserData("HoldQuest", "sCityFrom", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.FromCity));
			AddQuestUserData("HoldQuest", "sCityTo", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.ToCity));
			AddQuestUserData("HoldQuest", "sShipName", pchar.GenQuest.Hold_GenQuest.ShipName);
			
			SetFunctionTimerCondition("Hold_GenQuest_SetMerchant_pre", 0, 0, 1+rand(2), false);
			SetFunctionTimerCondition("Hold_GenQuest_MerchantOver", 0, 0, 30, false);
			
            ReleasePrisoner(NPChar); // 释放了俘虏
        	LAi_SetActorType(NPChar);
			NPChar.LifeDay = 0;
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
        	DialogExit();			
		break;
	
		case "free_buyout":
			dialog.text = "我也有一个提议给你。 在" + XI_ConvertString("Colony" + NPChar.Hold_GenQuest.City + "Voc") + "住着我的朋友, 他的名字是" + NPChar.Hold_GenQuest.Name + "。 我们曾经一起做过生意。 " +
				"在那里找到他。 我相信他会给你一大笔钱。 他欠我, 我会亲自和他打交道。 ";
			link.l1 = "你的朋友, 嗯? 让我看看他。 ";	
			link.l1.go = "free_buyout1";
			link.l2 = "如果我可以在第一个港口获得赎金, 为什么我要找你的朋友? ";
			link.l2.go = "free_tip_off_0";
		break;
	
		case "free_buyout1":
			LAi_CharacterDisableDialog(NPChar);
			
			pchar.GenQuest.Hold_GenQuest.City 		= NPChar.Hold_GenQuest.City;			
			pchar.GenQuest.Hold_GenQuest.Nation 	= NPChar.Hold_GenQuest.Nation;
			pchar.GenQuest.Hold_GenQuest.Name 		= NPChar.Hold_GenQuest.Name;
			pchar.GenQuest.Hold_GenQuest.CapName	= GetFullName(NPChar);
			pchar.GenQuest.Hold_GenQuest.CapId		= NPChar.Id;
			pchar.GenQuest.Hold_GenQuest.TavernVariant = rand(1);
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern = false;
			
			ReOpenQuestHeader("HoldQuest");
			AddQuestRecord("HoldQuest", "6");
			AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.City + "Voc")); 
			AddQuestUserData("HoldQuest", "sNameChar", NPChar.Hold_GenQuest.Name);
			DialogExit();
		break;

		case "free_by_hoard":
			dialog.text = "实际上, 我认识一个人, 他有一笔可观的宝藏, 但他没有勇气使用它。 ";
			link.l1 = "你是什么意思? ";
			link.l1.go = "free_by_hoard1";
			link.l2 = " spared me of your stories。 You'd better worry about your soul.";
			link.l2.go = "free_tip_off_0";
		break;
		
		case "free_by_hoard1":
			dialog.text = "我告诉你一个通向巨大宝藏的故事。 作为回报, 我需要你保证在下一个港口让我走。 ";
			link.l1 = "我会自己决定什么时候以及如何处理你。 你的'故事'不会有什么不同。 ";
			link.l1.go = "free_tip_off_0";
			link.l2 = "我在听。 我保证。 ";
			link.l2.go = "free_by_hoard2";
		break;
		
		case "free_by_hoard2":
			dialog.text = "我信任这样一位可敬的" + GetSexPhrase("男人","女人") + "。 像你这样的人总是信守诺言! 不管世界是否在燃烧, 你都会信守诺言! 对吗, 船长? ";
			link.l1 = "告诉我你的故事, 否则我现在就让你走... 无头落水。 ";
			link.l1.go = "free_by_hoard4";
		break;
		
		case "free_by_hoard4":
			dialog.text = "哈哈, 不错的笑话... 现在听着。 在" + XI_ConvertString("Colony" + NPChar.Hold_GenQuest.City + "Voc") + 
				"有一个叫" + NPChar.Hold_GenQuest.Name + "的朋友, 他年轻时真的很鲁莽。 那些日子他有很多'交易'... " + 
				"所以有一次在酒馆里他告诉我, 他是" + GetName( NAMETYPE_VIP, NPChar.Hold_GenQuest.PirateName, NAME_ACC) + "帮派的成员, 他看到那些海盗如何埋葬宝藏。 " +
				"他有五个伙伴因为那笔宝藏被杀... 有传言说他被抓住并绞死了, 但事实是他退出了生意, 开始了家庭。 他记得宝藏的位置, 甚至画了一张地图。 他提议我陪他去找宝藏。 他是个迷信的人, 宝藏沾满了鲜血, 所以他不敢一个人去。 我承认, 我也因为同样的原因不敢去。 " + 
                "他准备卖地图, 但如果我永远不去那里, 我为什么需要它... \n这就是我的故事... 我认为像你这样勇敢的人会觉得它有用, 顺便说一下, 这张地图相当便宜。 ";
			link.l1 = "你真的建议我买那个吗? 你的故事不是真的, 所以我打破我们的交易。 ";
			link.l1.go = "free_tip_off_0";
			link.l2 = "有趣的故事, 虽然我并不真的相信。 但我保证, 去告诉水手长给你一个储物柜。 你自由了。 ";
			link.l2.go = "free_by_hoard5";
		break;
		
		case "free_by_hoard5":
			dialog.text = "谢谢你, 船长! 现在我明白了一个" + GetSexPhrase("绅士!","女士!") + "的承诺的价值。 ";
			link.l1 = "走吧, 别挡我的路。 下次我不会这么轻易让你走。 ";
			link.l1.go = "free_by_hoard6";
		break;
		
		case "free_by_hoard6":
			pchar.GenQuest.Hold_GenQuest.City 		= NPChar.Hold_GenQuest.City;			
			pchar.GenQuest.Hold_GenQuest.Nation 	= NPChar.Hold_GenQuest.Nation;
			pchar.GenQuest.Hold_GenQuest.Name 		= NPChar.Hold_GenQuest.Name;
			pchar.GenQuest.Hold_GenQuest.PirateName	= NPChar.Hold_GenQuest.PirateName;
			pchar.GenQuest.Hold_GenQuest.CapName	= GetFullName(NPChar);
			pchar.GenQuest.Hold_GenQuest.TavernVariant = rand(1) + 2;
			pchar.GenQuest.Hold_GenQuest.Sum		= 10000 + rand(10000);
			pchar.GenQuest.Hold_GenQuest.Treasure	= rand(1);
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern = false;
			
			ReOpenQuestHeader("HoldQuest");
			AddQuestRecord("HoldQuest", "12");
			AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.City + "Voc")); 
			AddQuestUserData("HoldQuest", "sNameChar", pchar.GenQuest.Hold_GenQuest.Name);
			AddQuestUserData("HoldQuest", "sPirateName", GetName( NAMETYPE_VIP, pchar.GenQuest.Hold_GenQuest.PirateName, NAME_ACC));
			
            ReleasePrisoner(NPChar); // 释放了俘虏
        	LAi_SetActorType(NPChar);
			NPChar.LifeDay = 0;
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
        	DialogExit();					
		break;
		
		case "free_in_sea":
			dialog.text = "但是, " + GetAddress_Form(NPChar) + ", 我们在公海上! 这和你处决我一样! ";
			link.l1 = "这就是你想要的。 再见。 水手长会执行我的命令。 ";
			link.l1.go = "PunishmentAction1";
			link.l2 = "好吧, 我还没有决定。 ";
			link.l2.go = "exit";
		break;		
		
		//--> Jason, 虚假线索
		case "FalseTrace_Prisoner":
			dialog.text = "凯瑟琳! 她真的让你到这里来吗? 多么好的女孩... ";
			link.l1 = "让我们远离诗意吧, 船长, 谈谈更严肃的事情。 我要告诉你当前的情况, 我期待你的回答。 你的回答将决定你和凯瑟琳的命运。 ";
			link.l1.go = "FalseTrace_Prisoner_1";
		break;
		
		case "FalseTrace_Prisoner_1":
			dialog.text = "我在听, 船长。 ";
			link.l1 = "我登上你的快速帆船是因为凯瑟琳的丈夫亚当.雷纳告诉我你的船上有很多银。 这个诡计让他能够带走一个曾经属于他, 后来逃到你这里的女人。 ";
			link.l1.go = "FalseTrace_Prisoner_2";
		break;
		
		case "FalseTrace_Prisoner_2":
			dialog.text = "亚当? 那个混蛋? 这都是他的计划! 现在我明白了... 是的, 我三个月前帮助凯瑟琳逃脱。 可怜的女孩, 你不知道他是如何对待她的... ";
			link.l1 = "她是他的妻子, 我不在乎发生了什么, 这不关我的事。 我犯了登上你的帆船的错误, 但现在谈论它已经太晚了。 亚当答应为我的帮助付钱。 ";
			link.l1.go = "FalseTrace_Prisoner_3";
		break;
		
		case "FalseTrace_Prisoner_3":
			dialog.text = "亚当做出了承诺? 哈哈! 你相信他? 船长, 你知道他是什么样的人吗? 他... ";
			link.l1 = "凯瑟琳已经告诉我很多关于他的事情, 并且为此付出了很大的努力。 但他的提议有道理, 虽然我没有理由相信这个混蛋, 但也许这次他说的是实话。 所以让我们直奔主题... ";
			link.l1.go = "FalseTrace_Prisoner_4";
		break;
		
		case "FalseTrace_Prisoner_4":
			dialog.text = "";
			link.l1 = "我本来打算把你赎给当局, 把亚当和凯瑟琳送到" + XI_ConvertString("Colony" + pchar.questTemp.FalseTrace.QuestCity + "Acc") + ", 然后从亚当那里获取关于斜眼索利的黄金的信息并航行到那里。 但凯瑟琳说服我先和你谈谈, 她说你可能会给我一些比亚当更好。 更可靠的东西, 以换取你和她的生命与自由。 ";
			link.l1.go = "FalseTrace_Prisoner_5";
		break;
		
		case "FalseTrace_Prisoner_5":
			dialog.text = "";
			link.l1 = "这就是为什么我站在这里和你说话。 我说完了。 现在轮到你了。 考虑一下我的话和凯瑟琳的话, 然后给我你的想法。 你没有多少时间。 ";
			link.l1.go = "FalseTrace_Prisoner_6";
		break;
		
		case "FalseTrace_Prisoner_6":
			dialog.text = "船长! 虽然我不认为你是个好人, 但你确实听取了一个可怜女孩的恳求并来到了这里。 这表明你可以是可敬的并有同情心。 我不需要时间, 我准备给你我的提议。 ";
			link.l1 = "真的吗? 太好了! 那么, 我在听。 ";
			link.l1.go = "FalseTrace_Prisoner_7";
		break;
		
		case "FalseTrace_Prisoner_7":
			dialog.text = "你将逮捕亚当.雷纳并给他戴上锁链。 然后你将带我和凯瑟琳到" + XI_ConvertString("Colony" + pchar.questTemp.FalseTrace.TargetCity) + "。 不要在城里靠岸, 毕竟是你击沉了我的帆船, 把我们三个人放在" + XI_ConvertString(pchar.questTemp.FalseTrace.TargetShore + "Gen") + "\n我还会向你要一件武器。 我们将穿过丛林前往城市, 我会确保那个混蛋不仅为他的罪行付出代价, 也为你的罪行付出代价。 他应得的\n我向你保证不会提到你的名字。 作为回报, 我会给你关于一艘载有敌国黄金的船只的真实信息\n这对你来说不是一个大挑战, 但确实有价值, 你将获得一笔可观的战利品。 比我的赎金和'所谓的'斜眼索利的宝藏好得多。 我们成交吗? ";
			link.l1 = "我不喜欢你的计划。 我认为, 一旦我离开" + XI_ConvertString(pchar.questTemp.FalseTrace.TargetShore + "Gen") + "的海岸, 当地当局就会组织对我的追捕。 不, 船长, 我不打算冒这个险。 我们的谈话结束了。 ";
			link.l1.go = "FalseTrace_Prisoner_8";
			link.l2 = "嗯, 看来凯瑟琳是对的。 我喜欢你的提议。 亚当.雷纳将被逮捕。 我现在就去做。 逮捕亚当后你将被释放。 再见, 船长! ";
			link.l2.go = "FalseTrace_Prisoner_9";
		break;
		
		case "FalseTrace_Prisoner_8":
			DialogExit();
			AddQuestRecord("FalseTrace", "9");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony" + pchar.questTemp.FalseTrace.QuestCity));
			AddDialogExitQuestFunction("SetCheckForSolly");
			bQuestDisableMapEnter = false;
			LAi_CharacterDisableDialog(npchar);
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
		break;
		
		case "FalseTrace_Prisoner_9":
			DialogExit();
			AddQuestRecord("FalseTrace", "10");
			pchar.quest.FalseTraceSollyOver.over = "yes"; // 移除定时器
			AddDialogExitQuestFunction("SetCheckForGoldShip");
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.FalseTrace.PrisonerID = npchar.id;
			Pchar.questTemp.FalseTrace.PrisonerIDX = GetCharacterIndex(npchar.id);
		break;
		//< —虚假线索
		
		// Addon-2016 Jason FMK-瓜德罗普
		case "FMQG":
			dialog.text = "你是来传教还是来做生意的? ";
			link.l1 = "来做生意。 我需要你的犯罪伙伴 - 贝特朗.皮内特。 因为他我陷入了大麻烦。 我在哪里可以找到他, 嗯? ";
			link.l1.go = "FMQG_1";
		break;
		
		case "FMQG_1":
			dialog.text = "你为什么认为我会告诉你这个? ";
			link.l1 = "这关系到你的屁股。 我会带你去巴斯特尔, 把你交给总督, 并因抓获安排卡洛斯.德.米利亚逃跑的逃兵而获得奖励。 这是你的选择。 要么你告诉我皮内特的位置, 要么我们都去瓜德罗普。 ";
			link.l1.go = "FMQG_2";
		break;
		
		case "FMQG_2":
			dialog.text = "所以你什么都知道... 好吧, 我会告诉你我所知道的关于贝特朗.皮内特的一切, 但作为回报你要释放我。 ";
			link.l1 = "那就告诉我。 我会把你送到蚊子湾, 就像我上次做的那样。 但如果你骗我, 我会回来把唐.卡洛斯送给你的那个种植园烧掉, 我还会通知巴斯特尔你的下落, 所以不止我一个人在追捕你。 ";
			link.l1.go = "FMQG_3";
		break;
		
		case "FMQG_3":
			dialog.text = "首先, 把我送到那里。 这会让我感觉更安全, 我发誓我会告诉你一切。 ";
			link.l1 = "好吧。 反正你也去不了哪里。 ";
			link.l1.go = "FMQG_4";
		break;
		
		case "FMQG_4":
			DialogExit();
			AddQuestRecord("FMQ_Guadeloupe", "16");
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.FMQG.PrisonerID = npchar.id;
			Pchar.questTemp.FMQG.PrisonerIDX = GetCharacterIndex(npchar.id);
			pchar.quest.FMQG_SailMoskitos.win_condition.l1 = "location";
			pchar.quest.FMQG_SailMoskitos.win_condition.l1.location = "Shore47";
			pchar.quest.FMQG_SailMoskitos.function = "FMQG_ArriveMoskitos";
			pchar.questTemp.FMQG = "to_moskitos";
			AddMapQuestMarkShore("Shore47", true);
			bDisableMapEnter = false; // Rebbebion, 现在可以
		break;
		
		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
	}
}
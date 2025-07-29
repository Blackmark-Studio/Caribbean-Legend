// boal 08/04/06 общий диалог верфи
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;
	string s2;
	
	int iShipClass = GetCharacterShipClass(PChar); // Если корабля нет, вернет 7 (лодка)
	int iRank = sti(PChar.rank);
	int iSumm, iType;
	
	ref rRealShip;
	ref shTo;
	aref refShip;
	string attr;
	float fTmp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Shipyard\" + NPChar.City + "_Shipyard.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06
    bool ok;
    int iTest = FindColony(NPChar.City); // город магазина
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	int Material, WorkPrice;
	int amount;
	int	iCannonDiff;
	
	// генератор парусов по кейсу -->
	string attrLoc   = Dialog.CurrentNode;
	int i;
  	if (findsubstr(attrLoc, "SailsColorIdx_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.SailsColorIdx = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "SailsColorDone";
 	}
 	if (findsubstr(attrLoc, "SailsTypeChooseIDX_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.SailsTypeChooseIDX = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "SailsTypeChoose2";
 	}
	if(!CheckAttribute(NPChar, "ExpMeeting"))
	{
		NPChar.ExpMeeting = true;
		notification("首次访问造船厂 " + XI_ConvertString("Colony" +NPChar.City + "Gen"), "Carpenter");
		AddCharacterExpToSkill(pchar, SKILL_REPAIR, 10.0);
	}
	// 按案例生成帆 <--
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "ship_tunning_not_now":  // 类似退出, 从旧版本来, 很多需要修改
            LockControl("DlgDown3", false);
			LockControl("DlgUp3", false);
			DialogExit();
			NextDiag.CurrentNode = "First time";  // 调整退出, 因为有LoadSegment
		break;
		
		case "ship_tunning_not_now_1":  
			LockControl("DlgDown3", false);
			LockControl("DlgUp3", false);
			DialogExit();
			NextDiag.CurrentNode = "First time";  
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "First time":
            if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase("镇上已经拉响警报, 所有人都在找你。 如果我是你, 就不会待在这里。 ", "所有城卫军都在城里搜寻你。 我不是傻瓜, 不会和你说话! ", "快跑, "+ GetSexPhrase("伙计","姑娘") +", 在士兵把你打成筛子之前... "), 
					LinkRandPhrase("你需要什么, "+ GetSexPhrase("恶棍","臭家伙") +"? ! 城卫军已经嗅到你的气味了, 你跑不远的, 肮脏的海盗! ", "凶手, 马上离开我的房子! 卫兵! ", "我不怕你, "+ GetSexPhrase("恶棍","老鼠") +"! 很快你就会在我们的堡垒被吊死, 你跑不远的... "));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("呵, 警报对我来说不是问题... ", "他们永远抓不到我。 "), 
					RandPhraseSimple("闭嘴, " + GetWorkTypeOfMan(npchar, "") + ", 不然我就把你的舌头扯出来! ", "呵, " + GetWorkTypeOfMan(npchar, "") + ", 那边也是 —抓海盗! 我告诉你, 伙计: 安静点, 就不会死! "));
				link.l1.go = "fight";
				break;
			}
			
//Jason ---------------------------------------加斯科涅人的负担------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock") && pchar.location == "Fortfrance_shipyard")
			{
				if (CheckAttribute(pchar, "questTemp.Sharlie.Rum") || CheckAttribute(pchar, "questTemp.Sharlie.Gigolo") || CheckAttribute(pchar, "questTemp.Sharlie.RescueDaughter"))
				{
					dialog.text = "你想要什么, 先生? ";
					Link.l1 = "我来看看你的船... 但现在我有点忙 - 还有件没完成的事。 等我处理完了再来。 ";
					Link.l1.go = "exit";
					break;
				}
				if (pchar.questTemp.Sharlie == "ship" || pchar.questTemp.Sharlie == "ship_fast") // Addon 2016-1 Jason 海盗线 1
				{
					dialog.text = "你想要什么, 先生? ";
					Link.l1 = "听着, 我想从你这里买艘船。 ";
					Link.l1.go = "Sharlie";
					break;
				}
				dialog.text = "你还想要别的吗, 先生? ";
				Link.l1 = "不, 我想不需要了。 ";
				Link.l1.go = "exit";
				NextDiag.TempNode = "First time";
				NPChar.quest.meeting = "1";
				break;
			}
	//< —加斯科涅人的负担
			// Addon-2016 Jason, 法国迷你任务 (FMK) FMK-马提尼克
			if (CheckAttribute(pchar, "questTemp.FMQM.Oil") && pchar.location == "Fortfrance_shipyard")
			{
				if (pchar.questTemp.FMQM == "remove_oil")
				{
					dialog.text = "好了, 船长。 工作完成。 现在是愉快的部分 - 硬币的声音。 稍等一下... ";
					link.l1 = "... ";
					link.l1.go = "FMQM_oil_1";
					break;
				}
				if (pchar.questTemp.FMQM == "remove_oil1")
				{
					dialog.text = "军官, 等等! 拜托! 这一定是个误会。 先生, 船长和这件事无关, 他只是来这里停泊修船。 他正要离开。 什么桶? 你在说什么? ";
					link.l1 = "";
					link.l1.go = "FMQM_oil_2";
					break;
				}
				if (pchar.questTemp.FMQM == "remove_oil2")
				{
					dialog.text = "军官, 我再说一遍: 船长来这里是为了支付修船费用。 这些桶是我的财产, 只用于生产目的。 我是造船大师, 这种树脂是为我造的船准备的。 ";
					link.l1 = "";
					link.l1.go = "FMQM_oil_3";
					break;
				}
				if (pchar.questTemp.FMQM == "remove_oil3")
				{
					dialog.text = "哦, 船长先生! 你不知道我有多惨。 在地牢里和老鼠。 害虫以及可悲的人待了两天! 我不得不动用所有关系才保释出来。 啊, 新鲜空气! ";
					link.l1 = "我很同情你, 大师。 我们的树脂呢? 还有我的硬币? ";
					link.l1.go = "FMQM_oil_4";
					DelLandQuestMark(npchar);
					break;
				}
			}
			// Addon 2016-1 Jason 海盗线
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_13" && pchar.location == "PortRoyal_shipyard")
			{
				dialog.text = "哦, 又是你! 我认出你了, 年轻人! 最近问起... 用丝绸帆布提高船速的就是你, 对吧? ";
				link.l1 = "你的记忆力真好, 大师。 "; 
				link.l1.go = "mtraxx_x";
				break;
			}
			
			if(NPChar.quest.meeting == "0") // 第一次见面
			{
				dialog.Text = GetNatPhrase(npchar, LinkRandPhrase("哈! 一个真正的老水手来到了我简陋的工坊! 你是本地水域的新手吗, 船长? ","欢迎, 先生! 如果你熟悉大海并有船 - 你就来对地方了! ","你好, 先生! 你很幸运 - 这是整个英属新世界最好的船舶工坊。 "), LinkRandPhrase("先生, 我猜你是位潇洒的船长, 对吧? 如果是, 访问我简陋的造船厂是正确的选择! ","第一次来吗, 船长先生? 进来认识一下这位老造船匠。 ","让我们有幸认识一下, 先生! 船需要呵护, 就像女人一样 - 而我们法国人是这方面的专家! 相信我, 你不会后悔来这里的! "), LinkRandPhrase("我以前没在这里见过你, 先生。 很高兴认识你! ","我向勇敢的海洋征服者致敬! 你是水手, 对吧? 我是本地造船匠, 我们应该认识一下。 ","你好, 绅士! 很高兴欢迎你来到我的工坊! "),LinkRandPhrase("下午好, 先生。 我以前没见过你, 对吧? 你找我有事吗? ","你好, 船长先生。 别惊讶, 我见过不少船长, 所以一眼就看出你也是船长。 ","进来吧, 先生。 我是本地造船匠。 很高兴认识你。 "));
				Link.l1 = LinkRandPhrase("我也很高兴认识你。 我叫"+GetFullName(pchar)+", 是这里的新人。 所以, 我决定顺道来看看。 ","不能错过 - 你知道, 新刨木板的味道... 我是"+GetFullName(pchar)+",'"+pchar.ship.name+"'号船长。 ","请允许我介绍自己 - "+GetFullName(pchar)+",'"+pchar.ship.name+"'号船长, 很高兴认识你。 那么, 你在这里造船和修船, 是吗? ");
				Link.l1.go = "meeting";
				NPChar.quest.meeting = "1";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_shipyard")
				{
					dialog.text = "问候你, 麦克阿瑟船长。 ";
					link.l1 = "你可以叫我海伦, "+npchar.lastname+"先生。 "+TimeGreeting()+"。 ";
					Link.l1.go = "Helen_meeting";
				}
			}
			else
			{
				dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("哦! 本地水域的恐怖, "+GetFullName(pchar)+"船长! 我能为你做什么? ","我们直截了当吧, "+GetAddress_Form(NPChar)+", 我没时间闲聊。 你需要修理还是只想换掉你的破船? ","哦, 这不是"+GetFullName(pchar)+"吗! 怎么了, "+GetAddress_Form(NPChar)+"? 你的破船出事了? "),LinkRandPhrase("你需要什么, 船长? 没有片刻安宁 - 总是这些无赖, 真是该死的一天... ","你好, "+GetAddress_Form(NPChar)+"。 我得说你的来访吓跑了我所有的顾客。 希望你的订单能弥补我的损失? ","和我有事吗, "+GetAddress_Form(NPChar)+"? 好吧, 说吧, 快点。 "),LinkRandPhrase("是什么风把你吹来的, "+GetFullName(pchar)+"先生? 考虑到你的生活方式, 我能理解你的船可能遇到了麻烦... ","我很高兴迎接一位贵族... 哦, 抱歉, "+GetAddress_Form(NPChar)+", 我把你认错了。 你想要什么? ","我不太喜欢你这种类型, 船长, 但无论如何我不会赶你走。 你想要什么? ")),LinkRandPhrase(LinkRandPhrase("很高兴见到你, "+GetFullName(pchar)+"先生! 那么, 她运行得如何? 需要修理或清理吗? ","欢迎, "+GetAddress_Form(NPChar)+"! "+GetFullName(pchar)+"船长在我的工坊总是受欢迎的! ","哦, "+GetAddress_Form(NPChar)+""+GetFullName(pchar)+"! 你又来拜访了! 希望你的宝贝没事, 是吗? "),LinkRandPhrase(""+GetAddress_Form(NPChar)+", 很高兴再次见到你! 你漂亮的船怎么样了? 需要帮助吗? ","哦, "+GetAddress_Form(NPChar)+", 问候! 你好吗? 也许桅杆在响或者需要清理舱底? 我的人会尽力为你服务! ","下午好, "+GetFullName(pchar)+"船长。 很高兴你再次来访, 我随时准备帮助你。 "),LinkRandPhrase("很高兴你能来, 船长! 你是个很好的顾客, "+GetAddress_Form(NPChar)+", 希望你保持下去。 ","哦, "+GetAddress_Form(NPChar)+""+GetFullName(pchar)+"! 我真的很高兴你能来! 我能为你做什么? ","船长, 你又访问了"+XI_ConvertString("Colony"+npchar.City+"Acc")+"! 相信我, 我们会很高兴帮助你。 ")));
				Link.l1 = pcharrepphrase(RandPhraseSimple(RandPhraseSimple("拿起工具, 大师, 保持安静, 好吗? 我没心情。 ","别唠叨了, 伙计! 我需要你的帮助, 不是听你废话。 "),RandPhraseSimple("我付钱 - 你工作。 安静。 明白了吗? ","嘿, 伙计, 把他们都赶走 - 是我, 你最喜欢的顾客! ")),RandPhraseSimple(RandPhraseSimple("我也很高兴见到你, 大师。 可惜我时间不多, 我们言归正传吧。 ","我也很高兴见到你, 伙计。 想帮你最喜欢的顾客吗? "),RandPhraseSimple("下午好, 伙计。 我们马上谈正事吧。 保证下次一定一起喝一杯。 ","很高兴见到你, 大师。 见到你总是很高兴, 但现在我需要你的帮助。 ")));
				Link.l1.go = "Shipyard";
				if (GetNationRelation2MainCharacter(sti(NPChar.nation)) != RELATION_ENEMY) 
				{
					link.l11 = "我需要为我的船配备大炮。 ";
					link.l11.go = "Cannons";					
				}	
				
				if(NPChar.city == "PortRoyal" || NPChar.city == "Havana" || NPChar.city == "Villemstad" || NPChar.city == "Charles" || NPChar.city == "PortoBello")
				{
					link.l22 = "你能提供一些特别的。 其他造船厂没有的东西吗? ";
					link.l22.go = "ship_tunning";
				}
				
				link.l15 = "你没有需要陌生人帮忙的工作吗? ";
				link.l15.go = "Tasks";
				// Jason 莫娜岛
				if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "tools" && !CheckAttribute(npchar, "quest.IslaMonaTools"))
				{
					link.l20 = "我想买一套欧洲质量的建筑。 锻造和测量工具。 你能帮我吗? ";
					link.l20.go = "IslaMona";
				}
				if (CheckAttribute(npchar, "quest.IslaMonaMoney"))
				{
					link.l20 = "我带来了购买建筑工具的达布隆。 ";
					link.l20.go = "IslaMona_7";
				}
				//Jason --> 生成器 囚犯
				if (CheckAttribute(pchar, "GenQuest.Findship.Shipyarder") && NPChar.location == pchar.GenQuest.Findship.Shipyarder.City + "_shipyard")
				{
					ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
					if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
					{
						for(i = 1; i < COMPANION_MAX; i++)
						{
							int iTemp = GetCompanionIndex(PChar, i);
							if(iTemp > 0)
							{
								sld = GetCharacter(iTemp);
								if(GetRemovable(sld) && sti(RealShips[sti(sld.ship.type)].basetype) == sti(pchar.GenQuest.Findship.Shipyarder.ShipType))
								{
									pchar.GenQuest.Findship.Shipyarder.CompanionIndex = sld.Index;
									pchar.GenQuest.Findship.Shipyarder.OK = 1;
									pchar.GenQuest.Findship.Shipyarder.ShipName = sld.Ship.Name;
									pchar.GenQuest.Findship.Shipyarder.Money = makeint(GetShipSellPrice(sld, CharacterFromID(NPChar.city + "_shipyarder"))*1.5);
								}
							}
						}
					}
					if (sti(pchar.GenQuest.Findship.Shipyarder.OK) == 1)
					{
						link.l16 = "我按你要求送来了"+pchar.GenQuest.Findship.Shipyarder.ShipBaseName+"。 ";
						link.l16.go = "Findship_check";
					}// < —生成器 囚犯
				}
				//Jason --> 生成器 不幸的小偷
				if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && CheckCharacterItem(pchar, "Tool") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_shipyard")
				{
					link.l17 = "我设法找到了小偷并拿到了"+pchar.GenQuest.Device.Shipyarder.Type+"。 ";
					link.l17.go = "Device_complete";
				}
				// < —生成器 不幸的小偷
				if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && RealShips[sti(Pchar.Ship.Type)].BaseType != SHIP_CURSED_FDM) // mitrokosta фикс ломаных диалогов
				{
					link.l12 = "我想改变帆的外观。 ";
					link.l12.go = "SailsGerald";
				}
				Link.l2 = "我只是想聊聊。 ";
				Link.l2.go = "quests"; //(转发到城市文件)
				// -->
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l3 = "我想和你谈谈财务问题。 ";
					link.l3.go = "LoanForAll";
				}
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && CheckAttribute(pchar, "GenQuest.Intelligence.SpyId") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квeст мэра - на связь с нашим шпионом
				{
					link.l7 = RandPhraseSimple("我是应一个人的要求来的。 他叫"+ GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) +"总督。 ", 
						GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) +"派我来你这里。 我应该拿点东西... ");
					link.l7.go = "IntelligenceForAll";
				}
				//Jason, 生成二级邮差
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
				{
					if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
					{
						link.l14 = "我从"+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+"带来了船的设计图。 ";
						link.l14.go = "Postcureer_LevelUp_ForAll";
					}
				} // patch-6
				if(CheckAttribute(pchar,"GenQuest.EncGirl"))
				{
					if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "shipyard_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
					{
						link.l7 = "你好, 我是应你儿子的邀请来的。 "; 
						link.l7.go = "EncGirl_4";
						pchar.quest.EncGirl_GetLoverFather.over = "yes";
					}	
					if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
					{
						if(pchar.GenQuest.EncGirl.Father == "shipyard_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
						{
							link.l8 = "这是关于你女儿的... ";
							link.l8.go = "EncGirl_1";
						}
					}
				}								
				Link.l9 = "我得走了。 ";
				Link.l9.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "Meeting":
				dialog.Text = "很高兴见到新顾客。 我的造船厂为你服务。 ";
				Link.l1 = "太好了, " + GetFullName(NPChar) + "。 让我们看看你能为我提供什么。 ";
				Link.l1.go = "Shipyard";
				if (GetNationRelation2MainCharacter(sti(NPChar.nation)) != RELATION_ENEMY) 
				{
					link.l13 = "我需要为我的船配备大炮。 ";
					link.l13.go = "Cannons";
				}									
				link.l15 = "你没有需要陌生人帮忙的工作吗? ";
			    link.l15.go = "Tasks";
				
				if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && RealShips[sti(Pchar.Ship.Type)].BaseType != SHIP_CURSED_FDM) // mitrokosta фикс ломаных диалогов
				{
					link.l12 = "我想改变帆的外观。 ";
					link.l12.go = "SailsGerald";
				}
				Link.l2 = "我只是想聊聊。 ";		
				link.l2.go = "quests";
				// -->
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l3 = "我想和你谈谈财务问题。 ";
					link.l3.go = "LoanForAll";//(转发到城市文件)
				}
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квeст мэра - на связь с нашим шпионом
				{
					link.l7 = RandPhraseSimple("我是应一个人的要求来的。 他叫"+ GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) +"总督。 ", 
						GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) +"派我来你这里。 我应该拿点东西... ");
					link.l7.go = "IntelligenceForAll";
				}
				//Jason, 生成二级邮差
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
				{
					if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
					{
						link.l14 = "我从"+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+"镇带来了船的设计图。 ";
						link.l14.go = "Postcureer_LevelUp_ForAll";
					}
				}

				if(CheckAttribute(pchar,"GenQuest.EncGirl"))
				{
					if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "shipyard_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
					{
						link.l8 = "你好, 我是应你儿子的邀请来的。 "; 
						link.l8.go = "EncGirl_4";
						pchar.quest.EncGirl_GetLoverFather.over = "yes";
					}	
					if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
					{
						if(pchar.GenQuest.EncGirl.Father == "shipyard_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
						{
							link.l9 = "这是关于你女儿的... ";
							link.l9.go = "EncGirl_1";
						}
					}
				}
				if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakShipyard"))
				{
					if(CheckAttribute(pchar, "questTemp.different.GiveShipLetters") && (pchar.questTemp.different.GiveShipLetters.city == npchar.city))
					{
						link.l10 = "你能告诉我关于这些文件主人的什么信息? ";
						link.l10.go = "ShipLetters_6";// 生成器 "找到的文件"
					}		
				}	
				Link.l11 = "我必须离开, 谢谢你。 ";
				Link.l11.go = "exit";
				NextDiag.TempNode = "First time";
		break;
		
		case "Helen_Meeting":
				dialog.Text = "当然, 麦克阿瑟船长, 如你所愿。 你今天需要什么? ";
				Link.l1 = "太好了, " + GetFullName(NPChar) + "。 让我们看看你能为我提供什么。 ";
				Link.l1.go = "Shipyard";
				if (GetNationRelation2MainCharacter(sti(NPChar.nation)) != RELATION_ENEMY) 
				{
					link.l13 = "我需要为我的船配备大炮。 ";
					link.l13.go = "Cannons";
				}									
				link.l15 = "你没有需要陌生人帮忙的工作吗? ";
				link.l15.go = "Tasks";
				
				if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && RealShips[sti(Pchar.Ship.Type)].BaseType != SHIP_CURSED_FDM) // mitrokosta фикс ломаных диалогов
				{
					link.l12 = "我想改变帆的外观。 ";
					link.l12.go = "SailsGerald";
				}
				Link.l2 = "我只是想聊聊。 ";		
				link.l2.go = "quests";
				// -->
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l3 = "我想和你谈谈财务问题。 ";
					link.l3.go = "LoanForAll";//(转发到城市文件)
				}
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квeст мэра - на связь с нашим шпионом
				{
					link.l7 = RandPhraseSimple("我是应一个人的要求来的。 他叫"+ GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) +"总督。 ", 
						GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) +"派我来你这里。 我应该拿点东西... ");
					link.l7.go = "IntelligenceForAll";
				}
				//Jason, 生成二级邮差
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
				{
					if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
					{
						link.l14 = "我从"+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+"镇带来了船的设计图。 ";
						link.l14.go = "Postcureer_LevelUp_ForAll";
					}
				}

				if(CheckAttribute(pchar,"GenQuest.EncGirl"))
				{
					if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "shipyard_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
					{
						link.l8 = "你好, 我是应你儿子的邀请来的。 "; 
						link.l8.go = "EncGirl_4";
						pchar.quest.EncGirl_GetLoverFather.over = "yes";
					}	
					if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
					{
						if(pchar.GenQuest.EncGirl.Father == "shipyard_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
						{
							link.l9 = "这是关于你女儿的... ";
							link.l9.go = "EncGirl_1";
						}
					}
				}
				if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakShipyard"))
				{
					if(CheckAttribute(pchar, "questTemp.different.GiveShipLetters") && (pchar.questTemp.different.GiveShipLetters.city == npchar.city))
					{
						link.l10 = "你能告诉我关于这些文件主人的什么信息? ";
						link.l10.go = "ShipLetters_6";// 生成器 "找到的文件"
					}		
				}	
				Link.l11 = "我必须离开, 谢谢你。 ";
				Link.l11.go = "exit";
				NextDiag.TempNode = "First time";
		break;

		case "ship_tunning":
			dialog.text = "我们的造船厂以改进船只而闻名。 你感兴趣吗, 船长? ";
			Link.l1 = LinkRandPhrase("太棒了! 也许你可以看看我的船, 告诉我如何改进? ",
					  "这很有趣, 大师! 你能为我的船做什么? ",
					  "嗯... 你知道, 我习惯了我的船, 但如果你提供真正有趣的东西, 我可以考虑。 你觉得呢? ");
			Link.l1.go = "ship_tunning_start";
		break;
				
		case "ship_tunning_start" :		
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if (sti(Pchar.Ship.Type) == SHIP_NOTUSED || ok)
			{				
				if (sti(RealShips[sti(pchar.Ship.Type)].Class) >= 7)
				{
					dialog.Text = "呃... 我不处理小船。 旧桶还是旧桶, 不管你投入多少努力。 ";
					Link.l1 = "我明白... ";
					Link.l1.go = "ship_tunning_not_now_1";
					break;
				}
				// belamour 传奇版 -->
				if(!TuningAvailable())
				{
					dialog.Text = "一般... 让我们看看这里有什么... 是的 - " + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) + "。 恐怕你的船已经有了最多的改进特性, 进一步工作没有意义, 只会有害。 ";
					Link.l1 = "我明白... ";
					Link.l1.go = "ship_tunning_not_now_1";
					break;
				}
				// < —传奇版							
				if(GetHullPercent(pchar) < 100 || GetSailPercent(pchar) < 100)
				{
					dialog.Text = "在改进船只之前, 必须先完全修复。 这也可以在我的造船厂完成。 ";
					Link.l1 = "明白了... ";
					Link.l1.go = "ship_tunning_not_now_1";
					break;
				}
				
				s2 = "好吧, 让我们看看... 啊哈 " + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) + "。 ";
				// belamour 传奇版 -->
				if(NPChar.city == "PortRoyal")
				{
					s2 = s2 + " 我们的造船厂以提高船只性能而闻名, 我们可以增加最大速度或逆风角度。 ";
				}
				if(NPChar.city == "Havana" || NPChar.city == "PortoBello")
				{
					s2 = s2 + " 在我们的造船厂, 我们可以增加最大炮数或船只的载货量。 ";
				}
				if(NPChar.city == "Villemstad")
				{
					s2 = s2 + " 我的人可以加固你船的船体或增加船员的最大数量。 ";
				}
				if(NPChar.city == "Charles")
				{
					s2 = s2 + " 在这个造船厂, 你可以提高机动性或减少船员的最小数量。 ";
				}	
				
				dialog.Text = s2;
				
				if(NPChar.city == "PortRoyal")
				{
					// belamour 传奇版 -->
					ok = (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.SpeedRate")) && 
						 (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.WindAgainst"));
					if(ok)
					{
						Link.l1 = "提高速度。 ";
						Link.l1.go = "ship_tunning_SpeedRate";
						Link.l2 = "增加逆风角度。 ";
						Link.l2.go = "ship_tunning_WindAgainst";
						Link.l3 = "等等! 我改变主意了。 ";
						Link.l3.go = "ship_tunning_not_now_1";
						break;
					}	
					else
					{
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.SpeedRate"))
						{
							Link.l1 = "提高速度。 ";
							Link.l1.go = "ship_tunning_SpeedRate";
							Link.l2 = "等等! 我改变主意了。 ";
							Link.l2.go = "ship_tunning_not_now_1";
							break;
						}
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.WindAgainst"))
						{
							Link.l1 = "增加逆风角度。 ";
							Link.l1.go = "ship_tunning_WindAgainst";
							Link.l2 = "等等! 我改变主意了。 ";
							Link.l2.go = "ship_tunning_not_now_1";	
							break;
						}
						Link.l1 = LinkRandPhrase("哦! 我的船已经这样改进过了。 好吧, 谢谢你的时间! ",
												 "谢谢你, 大师, 但我已经有了改进, 正是你提到的。 祝其他船只和它们的船长好运! ",
												 "呵! 我想我的船之前被前主人改装过 - 一定是在这个造船厂, 好吧, 我想我必须感谢他的远见, 以及你和你的人出色的工作! ");
						Link.l1.go = "ship_tunning_not_now_1";					
					}
						// < —传奇版
				}
				if(NPChar.city == "Havana" || NPChar.city == "PortoBello")
				{
					ok = (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.Cannon")) && 
						 (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.Capacity"));
					if(ok)
					{	
						if(GetPossibilityCannonsUpgrade(pchar, true) > 0)
						{	
							Link.l1 = "增加最大炮数。 ";
							Link.l1.go = "ship_c_quantity";
						}	
							Link.l2 = "增加载重量。 ";
							Link.l2.go = "ship_tunning_Capacity";
						Link.l3 = "等等! 我改变主意了。 ";
						Link.l3.go = "ship_tunning_not_now_1";
						break;
					}
					else
					{
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.Cannon"))
						{
							if(GetPossibilityCannonsUpgrade(pchar, true) > 0)
							{	
								Link.l1 = "增加最大炮数。 ";
								Link.l1.go = "ship_c_quantity";
								Link.l2 = "等等! 我改变主意了。 ";
								Link.l2.go = "ship_tunning_not_now_1";	
								break;
							}	
						}
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.Capacity"))
						{
							Link.l1 = "增加载重量。 ";
							Link.l1.go = "ship_tunning_Capacity";
							Link.l2 = "等等! 我改变主意了。 ";
							Link.l2.go = "ship_tunning_not_now_1";	
							break;
						}
						Link.l1 = LinkRandPhrase("哦! 我的船已经这样改进过了。 好吧, 谢谢你的时间! ",
												 "谢谢你, 大师, 但我已经有了改进, 正是你提到的。 祝其他船只和它们的船长好运! ",
												 "呵! 我想我的船之前被前主人改装过 - 一定是在这个造船厂, 好吧, 我想我必须感谢他的远见, 以及你和你的人出色的工作! ");
						Link.l1.go = "ship_tunning_not_now_1";	
					// < —传奇版
					}						
				}
				if(NPChar.city == "Villemstad")
				{
					ok = (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.HP")) && 
						 (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.MaxCrew"));
					if(ok)
					{
						Link.l1 = "增加船体耐用性。 ";
						Link.l1.go = "ship_tunning_HP";
						Link.l2 = "增加船员空间。 ";
						Link.l2.go = "ship_tunning_MaxCrew";
						Link.l3 = "等等! 我改变主意了。 ";
						Link.l3.go = "ship_tunning_not_now_1";
						break;
					}	
					else
					{
						// belamour 传奇版 -->
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.HP"))
						{
							Link.l1 = "增加船体耐用性。 ";
							Link.l1.go = "ship_tunning_HP";
							Link.l2 = "等等! 我改变主意了。 ";
							Link.l2.go = "ship_tunning_not_now_1";
							break;
						}
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.MaxCrew"))
						{
							Link.l1 = "增加船员空间。 ";
							Link.l1.go = "ship_tunning_MaxCrew";
							Link.l2 = "等等! 我改变主意了。 ";
							Link.l2.go = "ship_tunning_not_now_1";
							break;	
						}
						Link.l1 = LinkRandPhrase("哦! 我的船已经这样改进过了。 好吧, 谢谢你的时间! ",
												 "谢谢你, 大师, 但我已经有了改进, 正是你提到的。 祝其他船只和它们的船长好运! ",
												 "呵! 我想我的船之前被前主人改装过 - 一定是在这个造船厂, 好吧, 我想我必须感谢他的远见, 以及你和你的人出色的工作! ");
						Link.l1.go = "ship_tunning_not_now_1";	
						// < —传奇版
					}
				}
				if(NPChar.city == "Charles")
				{
					ok = (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.TurnRate")) && 
						 (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.MinCrew"));
					if(ok)
					{		
						Link.l1 = "提高机动性。 ";
						Link.l1.go = "ship_tunning_TurnRate";
						if(sti(RealShips[sti(pchar.Ship.Type)].Class) < 5)
						{
							Link.l2 = "减少最小船员数量。 ";
							Link.l2.go = "ship_tunning_MinCrew";
						}	
						Link.l3 = "等等! 我改变主意了。 ";
						Link.l3.go = "ship_tunning_not_now_1";
						break;
					}
					else
					{
						// belamour 传奇版 -->
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.TurnRate"))
						{
							Link.l1 = "提高机动性。 ";
							Link.l1.go = "ship_tunning_TurnRate";
							Link.l2 = "等等! 我改变主意了。 ";
							Link.l2.go = "ship_tunning_not_now_1";
							break;
						}
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.MinCrew"))
						{
							if(sti(RealShips[sti(pchar.Ship.Type)].Class) < 5)
							{
								Link.l1 = "减少最小船员数量。 ";
								Link.l1.go = "ship_tunning_MinCrew";
								Link.l2 = "等等! 我改变主意了。 ";
								Link.l2.go = "ship_tunning_not_now_1";
								break;
							}	
						}
						// < —传奇版				
					}
					Link.l1 = LinkRandPhrase("哦! 我的船已经这样改进过了。 好吧, 谢谢你的时间! ",
												 "谢谢你, 大师, 但我已经有了改进, 正是你提到的。 祝其他船只和它们的船长好运! ",
												 "呵! 我想我的船之前被前主人改装过 - 一定是在这个造船厂, 好吧, 我想我必须感谢他的远见, 以及你和你的人出色的工作! ");
					Link.l1.go = "ship_tunning_not_now_1";	
				}								
			}
			else
			{
				dialog.Text = "船在哪里? 你在耍我吗? ";
				Link.l1 = "哦, 我错了, 确实... 对不起。 ";
				Link.l1.go = "ship_tunning_not_now_1";
			}			
		break;
		
		////////////////////////////////////////// Capacity ////////////////////////////////////////////////////
		case "ship_tunning_Capacity":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar, 2 );			
			s2 = "好吧, 让我们看看能做什么。 目前你的船载重量是 " + sti(RealShips[sti(pchar.Ship.Type)].Capacity);			
			s2 = s2 + "。 对于更轻的舱壁, 我需要: 铁木 - " + Material + "。 ";
			s2 = s2 + " 作为我工作的报酬, 我要: " + WorkPrice + " 箱达布隆 - 以支付我的费用。 就这样。 哦, 还有预付现金。 ";			
            dialog.Text = s2;
			Link.l1 = "同意。 我接受你的条件。 我会给你带来所需的一切。 ";
			Link.l1.go = "ship_tunning_Capacity_start";
			Link.l2 = "不。 这不符合我的要求。 ";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_tunning_Capacity_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour 传奇版 跑来跑去 - 真是麻烦 -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)			
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("从船舱取出达布隆箱: " + iSumm+ " 个。 ");
				}
				// < —legendary edtion
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;			    
				NextDiag.TempNode = "ship_tunning_Capacity_again";
				dialog.text = "太好了。 我会等待材料。 ";
				link.l1 = LinkRandPhrase("我向你保证, 你不会等很久。 我能解决这些问题, 好吗? ",
										 "就当你已经有了, 给我留着码头。 我会像风一样快。 ",
										 "当然。 我只需要拜访几个有你需要东西的人, 哈哈! ");
			    link.l1.go = "Exit";			    
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "为了增加" + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + "'" + pchar.ship.name + "'" +
				" 船匠需要: 铁木 - " + NPChar.Tuning.Matherial + "。 已预付定金 " + NPChar.Tuning.Money + " 箱达布隆。 ");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
				dialog.text = "我没看到定金... ";
				link.l1 = "我稍后再来。 ";
				link.l1.go = "Exit";								
			}
		break;
				
		case "ship_tunning_Capacity_again":
			if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName && TuningAvailable())
			{
                NextDiag.TempNode = "ship_tunning_Capacity_again";
				dialog.Text = "时间在流逝, 船在等待。 你把我要的东西带来了吗? ";
				Link.l1 = "是的, 我设法找到了一些。 ";
				Link.l1.go = "ship_tunning_Capacity_again_2";
				Link.l2 = "不, 我还在找。 ";
				Link.l2.go = "Exit";
			}
			else
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = " "+ GetSexPhrase("先生","女士") +", 自从我们达成协议后, 你换船了吗? 你不应该这样做。 ";
				Link.l1 = "唉, 都是环境所迫! 可惜定金没了... ";
			    Link.l1.go = "Exit";
				DeleteAttribute(pchar,"achievment.Tuning");
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_Capacity_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_SANDAL);		
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.text = "太好了, 现在我需要的都齐了。 那我开始工作了。 ";
				link.l1 = "我等着。 ";
				link.l1.go = "ship_tunning_Capacity_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_Capacity_again";
				dialog.Text = "我还需要: 铁木 - " + sti(NPChar.Tuning.Matherial) + "。 ";
				link.l1 = "好的。 ";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "我需要带来: 铁木 - "+ sti(NPChar.Tuning.Matherial) + "。 ");
			}
		break;
		
		case "ship_tunning_Capacity_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
			if(!CheckAttribute(shTo, "Bonus_Capacity"))
			{
				if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
				{
					shTo.Capacity        = sti(shTo.Capacity) + makeint(sti(shTo.Capacity)* 0.35);
				}
				else
				{
					shTo.Capacity        = sti(shTo.Capacity) + makeint(sti(shTo.Capacity)/5);
				}
			}
			else
			{
				
				if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
				{
					shTo.Capacity        = makeint((sti(shTo.Capacity) - sti(shTo.Bonus_Capacity)) * 1.35 + sti(shTo.Bonus_Capacity));
				}
				else
				{
					shTo.Capacity        = makeint((sti(shTo.Capacity) - sti(shTo.Bonus_Capacity)) * 1.2 + sti(shTo.Bonus_Capacity));
				}
			}
	        shTo.Tuning.Capacity = true;

	        // finish <--
            NextDiag.TempNode = "First time";
			dialog.Text = "... 似乎就这样了... 你现在可以满载货物了, 我保证工作质量。 ";
			Link.l1 = "谢谢! 我会测试的。 ";
			Link.l1.go = "Exit";
			if(!CheckAttribute(pchar, "achievment.Tuning.stage2") && CheckAttribute(shTo,"Tuning.Cannon") && CheckAttribute(shTo,"Tuning.Capacity")) 
			
			{
				pchar.achievment.Tuning.stage2 = true;
			}	
			TuningAvailable();
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
			
			notification("你学到了很多关于造船的新知识! ", "none");
			AddCharacterExpToSkill(pchar, SKILL_COMMERCE, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;
		
////////////////////////////////////////// 速度 ////////////////////////////////////////////////////
		case "ship_tunning_SpeedRate":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar,  1 );			
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar,  2 );
			s2 = "那么, 让我们看看能做些什么。 目前你的船速是 " + stf(RealShips[sti(Pchar.Ship.Type)].SpeedRate);	
			s2 = s2 + " 节。 为了更换船帆, 我需要: 船用丝绸 - " + Material + "。 ";
			s2 = s2 + " 作为我工作的报酬, 我要: " + WorkPrice + " 箱达布隆 - 以支付我的费用。 就这样。 哦, 还有预付现金。 ";						
            dialog.Text = s2;
			Link.l1 = "同意。 我接受你的条件。 我会给你带来所需的一切。 ";
			Link.l1.go = "ship_tunning_SpeedRate_start";
			Link.l2 = "不。 这不符合我的要求。 ";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
			
		case "ship_tunning_SpeedRate_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour 传奇版 跑来跑去 - 真是麻烦 -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("从船舱取出达布隆箱: " + iSumm+ " 个。 ");
				}
				// < —传奇版	
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 			    
			    NPChar.Tuning.ShipType   	= Pchar.Ship.Type;
			    NPChar.Tuning.ShipName   	= RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_SpeedRate_again";
				dialog.text = "太好了。 我会等待材料。 ";
				link.l1 = LinkRandPhrase("我向你保证, 你不会等很久。 我能解决这些问题, 好吗? ",
										 "就当你已经有了, 给我留着码头。 我会像风一样快。 ",
										 "当然。 我只需要拜访几个有你需要东西的人, 哈哈! ");
			    link.l1.go = "Exit";
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "为了提高" + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + "'" + pchar.ship.name + "'" +
				" 的速度, 船匠需要: 船用丝绸 - " + NPChar.Tuning.Matherial + "。 已预付定金 " + NPChar.Tuning.Money + " 箱达布隆。 ");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
				dialog.text = "我没看到定金... ";
				link.l1 = "我稍后再来。 ";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_SpeedRate_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_SpeedRate_again";
				dialog.Text = "时间在流逝, 船在等待。 你把我要的东西带来了吗? ";
				Link.l1 = "是的, 我设法找到了一些。 ";
			    Link.l1.go = "ship_tunning_SpeedRate_again_2";
				Link.l2 = "不, 我还在找。 ";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = "  " + GetSexPhrase("先生","女士") + ", 自从我们达成协议后, 你换船了吗? 你不应该这样做。 ";
				Link.l1 = "唉, 都是环境所迫! 可惜定金没了... ";
			    Link.l1.go = "Exit";			    
				DeleteAttribute(pchar,"achievment.Tuning");	
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_SpeedRate_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_SHIPSILK);		    
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.text = "太好了, 现在我需要的都齐了。 那我开始工作了。 ";
				link.l1 = "我等着。 ";
			    link.l1.go = "ship_tunning_SpeedRate_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_SpeedRate_again";
				dialog.Text = "我还需要: 船用丝绸 - " + sti(NPChar.Tuning.Matherial) + "。 ";
				link.l1 = "好的。 ";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText",  "我需要带来: 船用丝绸 - " + sti(NPChar.Tuning.Matherial) + "。 ");
			}
		break;
		
		case "ship_tunning_SpeedRate_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
			// 更改
			if(!CheckAttribute(shTo, "Bonus_SpeedRate"))
			{
				if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
				{
					shTo.SpeedRate        = (stf(shTo.SpeedRate) + stf(shTo.SpeedRate) * 0.35);
				}
				else
				{
					shTo.SpeedRate        = (stf(shTo.SpeedRate) + stf(shTo.SpeedRate)/5.0);
				}
			}
			else
			{
				if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
				{
					shTo.SpeedRate        = (stf(shTo.SpeedRate) - stf(shTo.Bonus_SpeedRate)) * 1.35 + stf(shTo.Bonus_SpeedRate);
				}
				else
				{
					shTo.SpeedRate        = (stf(shTo.SpeedRate) - stf(shTo.Bonus_SpeedRate)) * 1.2 + stf(shTo.Bonus_SpeedRate);
				}
			}
	        shTo.Tuning.SpeedRate = true;
			
			if(!CheckAttribute(pchar, "achievment.Tuning.stage1") && CheckAttribute(shTo, "Bonus_SpeedRate") &&  CheckAttribute(shTo,"Tuning.WindAgainst")) 
			{
				pchar.achievment.Tuning.stage1 = true;
			}	
            TuningAvailable();
            NextDiag.TempNode = "First time";
			dialog.Text = "... 一切就绪, 船长。 让风满帆。 如果你愿意, 可以检查一下! ";
			Link.l1 = "谢谢! 我会测试的。 ";
			Link.l1.go = "Exit";			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
			notification("你学到了很多关于造船的新知识! ", "none");
			AddCharacterExpToSkill(pchar, SKILL_SAILING, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;
		
		////////////////////////////////////////// 机动性 ////////////////////////////////////////////////////
		case "ship_tunning_TurnRate":
			Material  = GetMaterialQtyUpgrade(pchar, NPChar, 1 );			
			WorkPrice = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			s2 = "那么, 让我们看看能做些什么。 目前你的船机动性是 " + stf(RealShips[sti(Pchar.Ship.Type)].TurnRate);			
			s2 = s2 + "。 为了添加新帆来改善它, 我需要: 绳索 - " + Material + "。 ";
			s2 = s2 + " 作为我工作的报酬, 我要: " + WorkPrice + " 箱达布隆 - 以支付我的费用。 就这样。 哦, 还有预付现金。 ";										
            dialog.Text = s2;
			Link.l1 = "同意。 我接受你的条件。 我会给你带来所需的一切。 ";
			Link.l1.go = "ship_tunning_TurnRate_start";
			Link.l2 = "不。 这不符合我的要求。 ";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_tunning_TurnRate_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour 传奇版 跑来跑去 - 真是麻烦
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("从船舱取出达布隆箱: " + iSumm+ " 个。 ");
				}
				// < —传奇版	
			    NPChar.Tuning.Money  		= amount;
				NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_TurnRate_again";
				dialog.text = "太好了。 我会等待材料。 ";
				link.l1 = LinkRandPhrase("我向你保证, 你不会等很久。 我能解决这些问题, 好吗? ",
										 "就当你已经有了, 给我留着码头。 我会像风一样快。 ",
										 "当然。 我只需要拜访几个有你需要东西的人, 哈哈! ");				
			    link.l1.go = "Exit";			    
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "为了提高" + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + "'" + pchar.ship.name + "'" +
				" 的机动性, 船匠需要: 绳索 - " + NPChar.Tuning.Matherial + "。 已预付定金 " + NPChar.Tuning.Money + " 箱达布隆。 ");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
				dialog.text = "我没看到定金... ";
				link.l1 = "我稍后再来。 ";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_TurnRate_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_TurnRate_again";
				dialog.Text = "时间在流逝, 船在等待。 你把我要的东西带来了吗? ";
				Link.l1 = "是的, 我设法带来了一些。 ";
			    Link.l1.go = "ship_tunning_TurnRate_again_2";
				Link.l2 = "不, 我还在找。 ";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = "  " + GetSexPhrase("先生","女士") + ", 自从我们达成协议后, 你换船了吗? 你不应该这样做。 ";
				Link.l1 = "唉, 都是环境所迫! 可惜定金没了... ";
			    Link.l1.go = "Exit";			    
				DeleteAttribute(pchar,"achievment.Tuning");	
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_TurnRate_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_ROPES);		
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.text = "太好了, 现在我需要的都齐了。 那我开始工作了。 ";
				link.l1 = "我等着。 ";
			    link.l1.go = "ship_tunning_TurnRate_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_TurnRate_again";
				dialog.Text = "我还需要: 绳索 - " + sti(NPChar.Tuning.Matherial) + "。 ";
				link.l1 = "好的。 ";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "我需要带来: 绳索 - " + sti(NPChar.Tuning.Matherial) + "。 ");
			}
		break;
		
		case "ship_tunning_TurnRate_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
			// 更改
			if(!CheckAttribute(shTo, "Bonus_TurnRate"))
			{
				shTo.TurnRate        = (stf(shTo.TurnRate) + stf(shTo.TurnRate)/5.0);
			}
			else
			{
				shTo.TurnRate        = (stf(shTo.TurnRate) - stf(shTo.Bonus_TurnRate)) * 1.2 + stf(shTo.Bonus_TurnRate);
			}	

	        shTo.Tuning.TurnRate = true;
			if(!CheckAttribute(pchar, "achievment.Tuning.stage4") && CheckAttribute(shTo,"Tuning.TurnRate") && CheckAttribute(shTo,"Tuning.MinCrew")) 
			{
				pchar.achievment.Tuning.stage4 = true;
			}	
            TuningAvailable();
			dialog.Text = "... 现在应该都准备好了... 现在试试方向盘吧, 船长! ";
			Link.l1 = "谢谢! 我会测试的。 ";
			Link.l1.go = "Exit";
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
			notification("你学到了很多关于造船的新知识! ", "none");
			AddCharacterExpToSkill(pchar, SKILL_SAILING, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;
		
		////////////////////////////////////////// 最大船员数 ////////////////////////////////////////////////////
		case "ship_tunning_MaxCrew":
			Material  = GetMaterialQtyUpgrade(pchar, NPChar, 1 );
			WorkPrice = GetMaterialQtyUpgrade(pchar, NPChar, 2 );				
			s2 = "那么, 让我们看看能做些什么。 目前你的船员最大人数, 包括超载, 是 " + sti(RealShips[sti(Pchar.Ship.Type)].MaxCrew) + " 人。 ";			
			s2 = s2 + " 我需要: 铁木 - " + Material + "。 ";
			s2 = s2 + " 作为我工作的报酬, 我要: " + WorkPrice + " 箱达布隆 - 以支付我的费用。 就这样。 哦, 还有预付现金。 ";									
            dialog.Text = s2;
			Link.l1 = "同意。 我接受你的条件。 我会给你带来所需的一切。 ";
			Link.l1.go = "ship_tunning_MaxCrew_start";
			Link.l2 = "不。 这不符合我的要求。 ";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_tunning_MaxCrew_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour 传奇版 跑来跑去 - 真是麻烦 -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("从船舱取出达布隆箱: " + iSumm+ " 个。 ");
				}
				// < —传奇版		
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_MaxCrew_again";
				dialog.text = "太好了。 我会等待材料。 ";
				link.l1 = LinkRandPhrase("我向你保证, 你不会等很久。 我能解决这些问题, 好吗? ",
										 "就当你已经有了, 给我留着码头。 我会像风一样快。 ",
										 "当然。 我只需要拜访几个有你需要东西的人, 哈哈! ");
			    link.l1.go = "Exit";			    
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "为了增加" + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + "'" + pchar.ship.name + "'" +
				" 的船员数量, 船匠需要: 铁木 - " + NPChar.Tuning.Matherial + "。 已预付定金 " + NPChar.Tuning.Money + " 箱达布隆。 ");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
				dialog.text = "我没看到定金... ";
				link.l1 = "我稍后再来。 ";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_MaxCrew_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName  && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_MaxCrew_again";
				dialog.Text = "时间在流逝, 船在等待。 你把我要的东西带来了吗? ";
				Link.l1 = "是的, 我设法找到了一些。 ";
			    Link.l1.go = "ship_tunning_MaxCrew_again_2";
				Link.l2 = "不, 我还在找。 ";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = "  " + GetSexPhrase("先生","女士") + ", 自从我们达成协议后, 你换船了吗? 你不应该这样做。 ";
				Link.l1 = "唉, 都是环境所迫! 可惜定金没了... ";				
			    Link.l1.go = "Exit";
				DeleteAttribute(pchar,"achievment.Tuning");
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_MaxCrew_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_SANDAL);		    
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.text = "太好了, 现在我需要的都齐了。 那我开始工作了。 ";
				link.l1 = "我等着。 ";
			    link.l1.go = "ship_tunning_MaxCrew_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_MaxCrew_again";
				dialog.Text = "我还需要: 铁木 - " + sti(NPChar.Tuning.Matherial) + "。 ";
				link.l1 = "好的。 ";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "我需要带来: 铁木 - " + sti(NPChar.Tuning.Matherial) + "。 ");
			}
		break;
		
		case "ship_tunning_MaxCrew_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    
	        if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
			{
				shTo.MaxCrew        = sti(shTo.MaxCrew) + makeint(sti(shTo.MaxCrew) * 0.35);
			}
			else
			{
				shTo.MaxCrew        = sti(shTo.MaxCrew) + makeint(sti(shTo.MaxCrew)/5);
			}
	        shTo.Tuning.MaxCrew = true;
			if(!CheckAttribute(pchar, "achievment.Tuning.stage3") && CheckAttribute(shTo,"Tuning.MaxCrew") && CheckAttribute(shTo,"Tuning.HP")) 
			
			{
				pchar.achievment.Tuning.stage3 = true;
			}	
            TuningAvailable();
            NextDiag.TempNode = "First time";
			dialog.Text = "... 完成了, 船长。 现在你可以雇佣更多船员了, 空间足够容纳所有人。 ";
			Link.l1 = "谢谢! 我会测试的。 ";
			Link.l1.go = "Exit";
			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
			notification("你学到了很多关于造船的新知识! ", "none");
			AddCharacterExpToSkill(pchar, SKILL_DEFENCE, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
			AddCharacterExpToSkill(pchar, SKILL_GRAPPLING, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;

		
		////////////////////////////////////////// 最小船员数 ////////////////////////////////////////////////////
		case "ship_tunning_MinCrew":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );			
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar, 2 );				
			s2 = "那么, 让我们看看能做些什么。 目前你的船员所需的最小人数是 " + sti(RealShips[sti(Pchar.Ship.Type)].MinCrew) + " 人。 ";			
			s2 = s2 + " 为了改善船的可控性并减少所需船员数量, 我需要: 绳索 - " + Material + "。 ";
			s2 = s2 + " 作为我工作的报酬, 我要: " + WorkPrice + " 箱达布隆 - 以支付我的费用。 就这样。 哦, 还有预付现金。 ";									
            dialog.Text = s2;
			Link.l1 = "同意。 我接受你的条件。 我会给你带来所需的一切。 ";
			Link.l1.go = "ship_tunning_MinCrew_start";
			Link.l2 = "不, 那不适合我.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_tunning_MinCrew_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour 传奇版 跑来跑去 - 真是麻烦 -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("从船舱取出达布隆箱: " + iSumm+ " 个。 ");
				}
				// < —传奇版		
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_MinCrew_again";
				dialog.text = "太好了。 我会等待材料。 ";
				link.l1 = LinkRandPhrase("我向你保证, 你不会等很久。 我能解决这些问题, 好吗? ",
										 "就当你已经有了, 给我留着码头。 我会像风一样快。 ",
										 "当然。 我只需要拜访几个有你需要东西的人, 哈哈! ");
			    link.l1.go = "Exit";			    
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "为了减少" + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + "'" + pchar.ship.name + "'" +			
				" 所需的最小船员数量, 船匠需要: 绳索 - " + NPChar.Tuning.Matherial + "。 已预付定金 " + NPChar.Tuning.Money + " 箱达布隆。 ");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
				dialog.text = "我没看到定金... ";
				link.l1 = "我稍后再来。 ";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_MinCrew_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName  && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_MinCrew_again";
				dialog.Text = "时间在流逝, 船在等待。 你把我要的东西带来了吗? ";
				Link.l1 = "是的, 我设法找到了一些。 ";
			    Link.l1.go = "ship_tunning_MinCrew_again_2";
				Link.l2 = "不, 我还在找。 ";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = "  " + GetSexPhrase("先生","女士") + ", 自从我们达成协议后, 你换船了吗? 你不应该这样做。 ";
				Link.l1 = "唉, 都是环境所迫! 可惜定金没了... ";
			    Link.l1.go = "Exit";			    
				DeleteAttribute(pchar,"achievment.Tuning");	
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_MinCrew_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_ROPES);		    
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.text = "太好了, 现在我需要的都齐了。 那我开始工作了。 ";
				link.l1 = "我等着。 ";
			    link.l1.go = "ship_tunning_MinCrew_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_MinCrew_again";
				dialog.Text = "我还需要: 绳索 - " + sti(NPChar.Tuning.Matherial) + "。 ";
				link.l1 = "好的。 ";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "我需要带来: 绳索 - " + sti(NPChar.Tuning.Matherial) + "。 ");
			}
		break;
		
		case "ship_tunning_MinCrew_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
			// 更改
	        if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
			{
				shTo.MinCrew        = sti(shTo.MinCrew) - makeint(sti(shTo.MinCrew) * 0.35);
			}
			else
			{
				shTo.MinCrew        = sti(shTo.MinCrew) - makeint(sti(shTo.MinCrew)/5);
			}
			if(sti(shTo.MinCrew) < 1) shTo.MinCrew = 1;
	        shTo.Tuning.MinCrew = true;
			
			if(!CheckAttribute(pchar, "achievment.Tuning.stage4")  && CheckAttribute(shTo,"Tuning.TurnRate") && CheckAttribute(shTo,"Tuning.MinCrew")) 
			{
				pchar.achievment.Tuning.stage4 = true;
			}	
            TuningAvailable();
            NextDiag.TempNode = "First time";
			dialog.Text = "... 准备好了, 船长! 现在更少的船员可以以相同的总体效果管理这艘船。 ";
			Link.l1 = "谢谢! 我会测试的。 ";
			Link.l1.go = "Exit";
			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
			notification("你学到了很多关于造船的新知识! ", "none");
			AddCharacterExpToSkill(pchar, SKILL_DEFENCE, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
			AddCharacterExpToSkill(pchar, SKILL_GRAPPLING, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;
		
		////////////////////////////////////////// 船体耐久 ////////////////////////////////////////////////////
		case "ship_tunning_HP":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar, 2 );			
			s2 = "那么, 让我们看看能做些什么。 目前船体耐久是 " + sti(RealShips[sti(Pchar.Ship.Type)].HP);			
			s2 = s2 + "。 为了加固船体, 我需要: 树脂 - " + Material + "。 ";
			s2 = s2 + " 作为我工作的报酬, 我要: " + WorkPrice + " 箱达布隆 - 以支付我的费用。 就这样。 哦, 还有预付现金。 ";									
            dialog.Text = s2;
			Link.l1 = "同意。 我接受你的条件。 我会给你带来所需的一切。 ";
			Link.l1.go = "ship_tunning_HP_start";
			Link.l2 = "不。 这不符合我的要求。 ";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_tunning_HP_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour 传奇版 跑来跑去 - 真是麻烦 -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("从船舱取出达布隆箱: " + iSumm+ " 个。 ");
				}
				// < —传奇版		
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_HP_again";
				dialog.text = "太好了。 我会等待材料。 ";
				link.l1 = LinkRandPhrase("我向你保证, 你不会等很久。 我能解决这些问题, 好吗? ",
										 "就当你已经有了, 给我留着码头。 我会像风一样快。 ",
										 "当然。 我只需要拜访几个有你需要东西的人, 哈哈! ");
			    link.l1.go = "Exit";
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "为了加固" + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + "'" + pchar.ship.name + "'" +			
				" 的船体, 船匠需要: 树脂 - " + NPChar.Tuning.Matherial + "。 已预付定金 " + NPChar.Tuning.Money + " 箱达布隆。 ");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
				dialog.text = "我没看到定金... ";
				link.l1 = "我稍后再来。 ";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_HP_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_HP_again";
				dialog.Text = "时间在流逝, 船在等待。 你把我要的东西带来了吗? ";
				Link.l1 = "是的, 我设法找到了一些。 ";
			    Link.l1.go = "ship_tunning_HP_again_2";
				Link.l2 = "不, 我还在找。 ";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = "  " + GetSexPhrase("先生","女士") + ", 自从我们达成协议后, 你换船了吗? 你不应该这样做。 ";
				Link.l1 = "唉, 都是环境所迫! 可惜定金没了... ";
			    Link.l1.go = "Exit";			    
				DeleteAttribute(pchar,"achievment.Tuning");	
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_HP_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_OIL);		
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.text = "太好了, 现在我需要的都齐了。 那我开始工作了。 ";
				link.l1 = "我等着。 ";
			    link.l1.go = "ship_tunning_HP_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_HP_again";
				dialog.Text = "我还需要: 树脂 - " + sti(NPChar.Tuning.Matherial) + "。 ";
				link.l1 = "好的。 ";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "我需要带来: 树脂 - " + sti(NPChar.Tuning.Matherial) + "。 ");
			}
		break;
		
		case "ship_tunning_HP_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
			// 更改
			if(!CheckAttribute(shTo, "Bonus_HP"))
			{
				if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
				{
					shTo.HP        = sti(shTo.HP) + makeint(sti(shTo.HP) * 0.35);
                    shTo.BaseHP    = sti(shTo.BaseHP) + makeint(sti(shTo.BaseHP) * 0.35);
				}
				else
				{
					shTo.HP        = sti(shTo.HP) + makeint(sti(shTo.HP)/5);
                    shTo.BaseHP    = sti(shTo.BaseHP) + makeint(sti(shTo.BaseHP)/5);
				}
			}
			else
			{
				if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
				{
					if(sti(shTo.HP) > sti(shTo.Bonus_HP)) // иначе апгрейд будет умножать отрицательное значение
					{
						shTo.HP    = makeint((sti(shTo.HP) - sti(shTo.Bonus_HP)) * 1.35 + sti(shTo.Bonus_HP));
					}
					shTo.BaseHP    = makeint((sti(shTo.BaseHP) - sti(shTo.Bonus_HP)) * 1.35 + sti(shTo.Bonus_HP));
				}
				else
				{
					if(sti(shTo.HP) > sti(shTo.Bonus_HP)) // иначе апгрейд будет умножать отрицательное значение
					{
						shTo.HP    = makeint((sti(shTo.HP) - sti(shTo.Bonus_HP)) * 1.2 + sti(shTo.Bonus_HP));
					}
					shTo.BaseHP    = makeint((sti(shTo.BaseHP) - sti(shTo.Bonus_HP)) * 1.2 + sti(shTo.Bonus_HP));
				}
			}
	        shTo.Tuning.HP = true;
			//shTo.BaseHP = sti(shTo.HP); этого не должно существовать
			ProcessHullRepair(pchar, 100.0); // у нпс при апгрейде есть, здесь тоже должно быть

			if(!CheckAttribute(pchar, "achievment.Tuning.stage3") && CheckAttribute(shTo,"Tuning.MaxCrew") && CheckAttribute(shTo,"Tuning.HP")) 
			{
				pchar.achievment.Tuning.stage3 = true;
			}	
			TuningAvailable();
            NextDiag.TempNode = "First time";
			
			dialog.Text = "... 应该可以了... 我保证从现在起, 你的敌人要撕裂你船的船体将困难得多! ";
			Link.l1 = "呵, 我相信你的话! 谢谢你, 大师。 ";
			Link.l1.go = "Exit";
			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
			notification("你学到了很多关于造船的新知识! ", "none");
			AddCharacterExpToSkill(pchar, SKILL_DEFENCE, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
			AddCharacterExpToSkill(pchar, SKILL_REPAIR, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;
		
		////////////////////////////////////////// WindAgainst ////////////////////////////////////////////////////
		case "ship_tunning_WindAgainst":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			fTmp = 180.0 - (acos(1 - stf(RealShips[sti(Pchar.Ship.Type)].WindAgainstSpeed)) * 180.0/PI);
			s2 = "那么, 让我们看看能做些什么。 目前逆风航行角度是 " + makeint(fTmp) + " 度。 ";
			// belamour 传奇版 如果顺风航行, 那是降级
			s2 = s2 + " 为了加速逆风航行, 我需要: 船用丝绸 - " + Material + ", ";
			s2 = s2 + " 作为我工作的报酬, 我要: " + WorkPrice + " 箱达布隆 - 以支付我的费用。 就这样。 哦, 还有预付现金。 ";									
            dialog.Text = s2;
			Link.l1 = "同意。 我接受你的条件。 我会给你带来所需的一切。 ";
			Link.l1.go = "ship_tunning_WindAgainst_start";
			Link.l2 = "不。 这不符合我的要求。 ";
			Link.l2.go = "ship_tunning_not_now_1";
		break;

		case "ship_tunning_WindAgainst_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour 传奇版 跑来跑去 - 真是麻烦 -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("从船舱取出达布隆箱: " + iSumm+ " 个。 ");
				}
				// < —传奇版		
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial    	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_WindAgainst_again";
				dialog.text = "太好了。 我会等待材料。 ";
				link.l1 = LinkRandPhrase("我向你保证, 你不会等很久。 我能解决这些问题, 好吗? ",
										 "就当你已经有了, 给我留着码头。 我会像风一样快。 ",
										 "当然。 我只需要拜访几个有你需要东西的人, 哈哈! ");
			    link.l1.go = "Exit";

			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "为了改变" + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + "'" + pchar.ship.name + "'" +			
				" 的逆风角度, 船匠需要: 船用丝绸 - " + NPChar.Tuning.Matherial + "。 已预付定金 " + NPChar.Tuning.Money + " 箱达布隆。 ");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
				dialog.text = "我没看到定金... ";
				link.l1 = "我稍后再来。 ";
				link.l1.go = "Exit";
			}
		break;

		case "ship_tunning_WindAgainst_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName  && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_WindAgainst_again";
				dialog.Text = "时间在流逝, 船在等待。 你把我要的东西带来了吗? ";
				Link.l1 = "是的, 我设法带来了一些。 ";
			    Link.l1.go = "ship_tunning_WindAgainst_again_2";
				Link.l2 = "不, 我还在找。 ";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = "  " + GetSexPhrase("先生","女士") + ", 自从我们达成协议后, 你换船了吗? 你不应该这样做。 ";
				Link.l1 = "唉, 都是环境所迫! 可惜定金没了... ";
			    Link.l1.go = "Exit";
				DeleteAttribute(pchar,"achievment.Tuning");
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;

		case "ship_tunning_WindAgainst_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_SHIPSILK);
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.text = "太好了, 现在我需要的都齐了。 那我开始工作了。 ";
				link.l1 = "我等着。 ";
			    link.l1.go = "ship_tunning_WindAgainst_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_WindAgainst_again";
				dialog.Text = "我还需要: 船用丝绸 - " + sti(NPChar.Tuning.Matherial) + "。 ";
				link.l1 = "好的。 ";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "我需要带来: 船用丝绸 - " + sti(NPChar.Tuning.Matherial) + "。 ");
			}
		break;

		case "ship_tunning_WindAgainst_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
			// 更改			
			// belamour 传奇版 WindAgainstSpeed 越大, 逆风性能越好
	        if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
			{
				shTo.WindAgainstSpeed   = stf(shTo.WindAgainstSpeed) + 0.35 * stf(shTo.WindAgainstSpeed);	
			}
			else
			{
				shTo.WindAgainstSpeed   = stf(shTo.WindAgainstSpeed) + 0.20 * stf(shTo.WindAgainstSpeed);
			}
			if (stf(shTo.WindAgainstSpeed) > 1.985) shTo.WindAgainstSpeed = 1.985;
	        shTo.Tuning.WindAgainst = true;

			if(!CheckAttribute(pchar, "achievment.Tuning.stage1") && CheckAttribute(shTo, "Bonus_SpeedRate") &&  CheckAttribute(shTo,"Tuning.WindAgainst")) 
			{
				pchar.achievment.Tuning.stage1 = true;
			}	
            TuningAvailable();
            NextDiag.TempNode = "First time";
			dialog.Text = "... 准备好了, 船长! ... 你的船现在逆风航行会快得多。 ";
			Link.l1 = "谢谢! 我会测试的。 ";
			Link.l1.go = "Exit";

			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
			notification("你学到了很多关于造船的新知识! ", "none");
			AddCharacterExpToSkill(pchar, SKILL_SAILING, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;
						
////////////////////////////////////////// 仅加农炮数量  ////////////////////////////////////////////////////	
		case "ship_c_quantity":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );			
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar, 2 );			
			s2 = "让我们看看能做些什么。 目前你船上的加农炮数量是 " + sti(RealShips[sti(Pchar.Ship.Type)].CannonsQuantity) + ", 最大可能数量是 - " + sti(RealShips[sti(Pchar.Ship.Type)].CannonsQuantityMax) + "。 ";			
			s2 = s2 + " 我可以直接告诉你, 这不会便宜。 我需要: 树脂 - " + Material + ", ";
			s2 = s2 + " 作为我工作的报酬, 我要: " + WorkPrice + " 箱达布隆 - 以支付我的费用。 就这样。 哦, 还有预付现金。 ";						
			dialog.Text = s2;		
			Link.l1 = "同意。 我接受你的条件。 我会给你带来所需的一切。 ";
			Link.l1.go = "ship_c_quantity_start";		
			Link.l2 = "不。 这不符合我的要求。 ";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_c_quantity_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour 传奇版 跑来跑去 - 真是麻烦 -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("从船舱取出达布隆箱: " + iSumm+ " 个。 ");
				}
				// < —传奇版		
			    NPChar.Tuning.Money  		= amount;
				NPChar.Tuning.Cannon 		= true;				
				NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 				
				NPChar.Tuning.ShipType      = Pchar.Ship.Type;
				NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;											    
				NextDiag.TempNode = "ship_c_quantity_again";
				dialog.text = "太好了。 我会等待材料。 ";
				link.l1 = LinkRandPhrase("我向你保证, 你不会等很久。 我能解决这些问题, 好吗? ",
										 "就当你已经有了, 给我留着码头。 我会像风一样快。 ",
										 "当然。 我只需要拜访几个有你需要东西的人, 哈哈! ");
				link.l1.go = "Exit";			    
				ReOpenQuestHeader("ShipTuning");
				AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "为了增加" + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + "'" + pchar.ship.name + "'" +						
				" 的加农炮数量, 船匠需要: 树脂 - " + NPChar.Tuning.Matherial + "。 已预付定金 " + NPChar.Tuning.Money + " 箱达布隆。 ");				
			}		
			else
			{ 
				NextDiag.TempNode = "ship_tunning_not_now_1";
				dialog.text = "我没看到定金... ";
				link.l1 = "我稍后再来。 ";
				link.l1.go = "Exit";
			}
		break;		
		
		case "ship_c_quantity_again":	
			if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName && TuningAvailable())
			{
				NextDiag.TempNode = "ship_c_quantity_again";
				dialog.Text = "时间在流逝, 船在等待。 你把我要的东西带来了吗? ";
				Link.l1 = "是的, 我设法找到了一些。 ";
				Link.l1.go = "ship_c_quantity_again_2";
				Link.l2 = "不, 我还在找。 ";
				Link.l2.go = "Exit";
			}		
			else
			{
				DeleteAttribute(NPChar, "Tuning");
				NextDiag.TempNode = "First time";
				dialog.Text = "  " + GetSexPhrase("先生","女士") + ", 自从我们达成协议后, 你换船了吗? 你不应该这样做。 ";
				Link.l1 = "唉, 都是环境所迫! 可惜定金没了... ";
				Link.l1.go = "Exit";
				DeleteAttribute(pchar,"achievment.Tuning");
				AddQuestRecord("ShipTuning", "Lose");
				CloseQuestHeader("ShipTuning");
			}		
		break;
		
		case "ship_c_quantity_again_2":		
			checkMatherial(Pchar, NPChar, GOOD_OIL);
			if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
				NextDiag.TempNode = "First time";
				dialog.text = "太好了, 现在我需要的都齐了。 那我开始工作了。 ";
				link.l1 = "我等着。 ";
				link.l1.go = "ship_c_quantity_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_c_quantity_again";
				dialog.Text = "我还需要: 树脂 - " + sti(NPChar.Tuning.Matherial) + "。 ";
				link.l1 = "好的。 ";
				link.l1.go = "Exit";
				AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "我需要带来: 树脂 - " + sti(NPChar.Tuning.Matherial) + "。 ");
			}		
		break;
		
		case "ship_c_quantity_complite":
			AddTimeToCurrent(6, 30);
			shTo = &RealShips[sti(Pchar.Ship.Type)];
			DeleteAttribute(NPChar, "Tuning");		
			makearef(refShip, pchar.Ship);
			
			iCannonDiff = sti(refShip.CannonDiff);
			iCannonDiff -= 1;
								
			for (i = 0; i < sti(shTo.cannonr); i++)
			{
				attr = "c" + i;										
					
				if(i < (sti(shTo.cannonr) - iCannonDiff) )	
				{
					if( stf(refShip.Cannons.Borts.cannonr.damages.(attr)) > 1.0 )
					{
						refShip.Cannons.Borts.cannonr.damages.(attr) = 1.0; 
					}	
				}					
			}	
			for (i = 0; i < sti(shTo.cannonl); i++)
			{
				attr = "c" + i;
				if(i < (sti(shTo.cannonl) - iCannonDiff) )	
				{
					if( stf(refShip.Cannons.Borts.cannonl.damages.(attr)) > 1.0 )
					{
						refShip.Cannons.Borts.cannonl.damages.(attr) = 1.0; 
					}	
				}										
			}	
			
			if(CheckAttribute(shTo,"CannonsQuantityMax")) 	shTo.Cannons = sti(shTo.CannonsQuantityMax) - iCannonDiff * 2;
			else											shTo.Cannons = sti(shTo.CannonsQuantity) - iCannonDiff * 2;
			
			shTo.CannonsQuantity = sti(shTo.Cannons);
		
			refShip.Cannons = sti(shTo.Cannons);
			refShip.CannonDiff = iCannonDiff;			

			shTo.Tuning.Cannon = true;
			
			if(!CheckAttribute(pchar, "achievment.Tuning.stage2") && CheckAttribute(shTo,"Tuning.Cannon") && CheckAttribute(shTo,"Tuning.Capacity")) 
			{
				pchar.achievment.Tuning.stage2 = true;
			}	
			TuningAvailable();
			NextDiag.TempNode = "First time";
			dialog.Text = "... 好了, 船长。 你可以使用额外的加农炮了 - 也就是说, 如果你有的话, 呵呵。 ";
			Link.l1 = "谢谢! ";
			Link.l1.go = "Exit";
			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
			notification("你学到了很多关于造船的新知识! ", "none");
			AddCharacterExpToSkill(pchar, SKILL_ACCURACY, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
			AddCharacterExpToSkill(pchar, SKILL_CANNONS, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;
		
		case "Tasks":
			//--> Jason генератор Поиск корабля
			if (hrand(4) == 2 && !CheckAttribute(pchar, "GenQuest.Findship.Shipyarder") && sti(pchar.rank) < 19)
			{
				if (!CheckAttribute(npchar, "Findship") || GetNpcQuestPastDayParam(npchar, "Findship") >= 60) 
				{
					SelectFindship_ShipType(); //выбор типа корабля
					pchar.GenQuest.Findship.Shipyarder.ShipBaseName =  GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Findship.Shipyarder.ShipType), "Name") + "Acc")); // new
					pchar.GenQuest.Findship.Shipyarder.City = npchar.city; //город квестодателя
					dialog.text = "我有个问题需要解决。 我有一个船只订单 - " + pchar.GenQuest.Findship.Shipyarder.ShipBaseName + "。 然而, 我的船厂里现在没有这样的船, 而且两个月内我也没有可能得到一艘。 \n如果你能给我这样一艘船 - 我会非常感激, 并会支付给你比它售价高一倍半的金额。 ";
					link.l1 = "一个有趣的提议。 我同意! ";
					link.l1.go = "Findship";
					link.l2 = "这引不起我的兴趣。 ";
					link.l2.go = "Findship_exit";
					SaveCurrentNpcQuestDateParam(npchar, "Findship");
					break;
				}
				
			}//< —生成器 寻找船只
			//Jason --> 生成器 不幸的小偷
			if (hrand(6) == 1 && !CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && sti(pchar.rank) < 10 && npchar.city != "Charles")
			{
				if (!CheckAttribute(npchar, "Device")) 
				{
					switch (hrand(4))
					{
						case 0:  
							pchar.GenQuest.Device.Shipyarder.Type = "内径规";
							pchar.GenQuest.Device.Shipyarder.Describe = "两条锤打钢带, 两端用未铆接的接头连接";
						break; 
						case 1:  
							pchar.GenQuest.Device.Shipyarder.Type = "瑞典宽斧";
							pchar.GenQuest.Device.Shipyarder.Describe = "一把长直柄。 薄半圆形刀刃的斧头";
						break; 
						case 2:  
							pchar.GenQuest.Device.Shipyarder.Type = "开槽器";
							pchar.GenQuest.Device.Shipyarder.Describe = "一把看起来像农民鹤嘴锄的小斧头";
						break; 
						case 3:  
							pchar.GenQuest.Device.Shipyarder.Type = "库存水平仪";
							pchar.GenQuest.Device.Shipyarder.Describe = "两根等长的木条, 由同一根第三根木条连接, 中间有一个带气泡的旋转充液板";
						break;
						case 4:  
							pchar.GenQuest.Device.Shipyarder.Type = "巴希克";
							pchar.GenQuest.Device.Shipyarder.Describe = "一种普通的连枷, 但链条是杆状的, 且只能单向移动";
						break; 
					}
					dialog.text = "你来得正好。 也许你能帮我。 昨天有人从我这里偷走了一件非常贵重的工具 - " + pchar.GenQuest.Device.Shipyarder.Type + "。 我无法再制作一个, 也没有时间或成本从欧洲订购。 没有它, 我就无法正常造船, 你知道吗? \n最令人恼火的是 - 除了造船匠, 没人需要这个东西, 而我是这个殖民地唯一的造船匠。 这个小偷不会卖给任何人, 只会把它扔掉。 也许你可以试着追踪小偷, 在镇上问问, 但我根本没有时间离开造船厂 - 我急需完成特殊订单。 ";
					link.l1 = "好吧, 我试试。 告诉我, 你那个... 工具是什么样子的? ";
					link.l1.go = "Device";
					link.l2 = "这对我没兴趣。 ";
					link.l2.go = "Device_exit";
					SaveCurrentNpcQuestDateParam(npchar, "Device");
					break;
				}//< —生成器 不幸的小偷
			}
			dialog.text = "我没有那样的事情。 ";
			link.l1 = "如你所说。 ";
			link.l1.go = "exit";
		break;
		
		case "Findship_exit":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Findship.Shipyarder");
		break;
		
		case "Device_exit":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
		break;
		
		//--> Jason 生成器 寻找船只
		case "Findship":
			pchar.GenQuest.Findship.Shipyarder = "begin";
			pchar.GenQuest.Findship.Shipyarder.Name = GetFullName(npchar);
			pchar.GenQuest.Findship.Shipyarder.City = npchar.city;
			ReOpenQuestHeader("Findship");
			AddQuestRecord("Findship", "1");
			AddQuestUserData("Findship", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Findship.Shipyarder.City+"Gen"));
			AddQuestUserData("Findship", "sName", pchar.GenQuest.Findship.Shipyarder.Name);
			AddQuestUserData("Findship", "sShip", pchar.GenQuest.Findship.Shipyarder.ShipBaseName);
			SetFunctionTimerCondition("Findship_Over", 0, 0, 60, false);
			DialogExit();
		break;
		
		case "Findship_check":
			dialog.text = "太好了! 我很高兴你这么快就成功了。 那艘船在哪里? ";
			link.l1 = "目前这艘船在锚地; 她的名字是'" + pchar.GenQuest.Findship.Shipyarder.ShipName + "'。 ";
				link.l1.go = "Findship_complete";
				break;
		
		case "Findship_complete":
			pchar.quest.Findship_Over.over = "yes";//снять прерывание
			sld = GetCharacter(sti(pchar.GenQuest.Findship.Shipyarder.CompanionIndex));
			RemoveCharacterCompanion(PChar, sld);
			AddPassenger(PChar, sld, false);
			dialog.text = "这是你的钱 - " + FindRussianMoneyString(sti(pchar.GenQuest.Findship.Shipyarder.Money)) + "。 谢谢你的工作。 别忘了再来找我。 再见! ";
			link.l1 = "再见, " + npchar.name+ "。 ";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Findship.Shipyarder.Money));
			AddQuestRecord("Findship", "3");
			AddQuestUserData("Findship", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Findship.Shipyarder.Money)));
			CloseQuestHeader("Findship");
			DeleteAttribute(pchar, "GenQuest.Findship.Shipyarder");
		break;
		//< —生成器 寻找船只
		
		//Jason --> 生成器 不幸的小偷
		case "Device":
			pchar.GenQuest.Device.Shipyarder.Chance1 = rand(6);
			pchar.GenQuest.Device.Shipyarder.Chance2 = rand(3);
			pchar.GenQuest.Device.Shipyarder.Chance3 = rand(2);
			pchar.GenQuest.Device.Shipyarder.Chance4 = rand(4);
			pchar.GenQuest.Device.Shipyarder.Money = 12000+rand(8000);
			//现在生成奖励船只类型, 以免丢失
			if (sti(pchar.rank) < 5) iType = sti(RandPhraseSimple(its(SHIP_BARKENTINE), its(SHIP_SLOOP)));
			if (sti(pchar.rank) >= 5 && sti(pchar.rank) < 11) iType = sti(RandPhraseSimple(its(SHIP_SHNYAVA), its(SHIP_BARQUE)));
			if (sti(pchar.rank) >= 11 && sti(pchar.rank) < 16) iType = sti(RandPhraseSimple(its(SHIP_BRIG), its(SHIP_FLEUT)));
			if (sti(pchar.rank) >= 16) iType = sti(LinkRandPhrase(its(SHIP_CORVETTE), its(SHIP_POLACRE), its(SHIP_GALEON_L)));
			pchar.GenQuest.Device.Shipyarder.Bonus = iType;
			dialog.text = "当然, 我会尽量用简单的话解释。 它看起来像 " + pchar.GenQuest.Device.Shipyarder.Describe + "。 这是独一无二的, 所以你会很容易认出它。 如果你把那个工具带给我, 我会给你丰厚的报酬。 ";
			link.l1 = "明白了。 我马上开始搜索! ";
			link.l1.go = "exit";
			pchar.GenQuest.Device.Shipyarder = "begin";
			pchar.GenQuest.Device.Shipyarder.Name = GetFullName(npchar);
			pchar.GenQuest.Device.Shipyarder.City = npchar.city;
			pchar.GenQuest.Device.Shipyarder.Nation = npchar.Nation;
			ReOpenQuestHeader("Device");
			AddQuestRecord("Device", "1");
			AddQuestUserData("Device", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Device.Shipyarder.City+"Voc"));
			AddQuestUserData("Device", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Device", "sName", pchar.GenQuest.Device.Shipyarder.Type);
			AddQuestUserData("Device", "sDesc", pchar.GenQuest.Device.Shipyarder.Describe);
			SetFunctionTimerCondition("Device_Over", 0, 0, 30, false);
		break;
		
		case "Device_complete":
			pchar.quest.Device_Over.over = "yes";//снять прерывание
			dialog.text = "你做到了! 你不知道我有多感激! 我已经不抱任何希望能再见到我的工具了。 ";
			link.l1 = "给你。 ";
			link.l1.go = "Device_complete_1";
		break;
		
		case "Device_complete_1":
			RemoveItems(PChar, "Tool", 1);
			dialog.text = "为了你的努力, 我将付给你 " + FindRussianMoneyString(sti(pchar.GenQuest.Device.Shipyarder.Money)) + "。 我希望这是一个值得的奖励。 ";
			link.l1 = "谢谢! ";
			link.l1.go = "Device_complete_2";
		break;
		
		case "Device_complete_2":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Device.Shipyarder.Money));
			ChangeCharacterComplexReputation(pchar,"nobility", 5); 
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			AddQuestRecord("Device", "10");
			AddQuestUserData("Device", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Device.Shipyarder.Money)));
			CloseQuestHeader("Device");
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance4) == 3)
			{
				dialog.text = "此外, 我想给你一个提议, 作为额外的感谢。 ";
				link.l1 = "这很有趣。 好吧, 继续 - 我喜欢惊喜。 ";
				link.l1.go = "Device_complete_3";
			}
			else
			{
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
			}
		break;
		
		case "Device_complete_3":
			iType = sti(pchar.GenQuest.Device.Shipyarder.Bonus);
			dialog.text = "我刚刚下水了一艘新船 - " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(iType, "Name") + "Acc")) + "。 已经有几个客户想要这艘船, 但我会给你优先权。 如果你喜欢这艘船, 并且不怕价格 - 你可以买它。 ";
			link.l1 = "呵! 当然, 让我看看! ";
			link.l1.go = "Device_complete_4";
			link.l2 = "谢谢你, 但我现在的船很适合我, 我不打算更换它。 ";
			link.l2.go = "Device_complete_5";
		break;
		
		case "Device_complete_4":
			iType = sti(pchar.GenQuest.Device.Shipyarder.Bonus);
			FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_TARTANE, NPChar), "ship1");
			FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_LUGGER, NPChar), "ship2");
			FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_LUGGER, NPChar), "ship3");
			FillShipParamShipyard(NPChar, GenerateStoreShipExt(iType, NPChar), "ship10");
			DialogExit();
			LaunchShipyard(npchar);
			DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
			SaveCurrentNpcQuestDateParam(npchar, "shipyardDate"); // лесник , митрокоста		   
		break;
		
		case "Device_complete_5":
			dialog.text = "好吧, 如你所愿。 再次感谢 - 祝你好运! ";
			link.l1 = "也祝你好运! ";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
		break;
		// < —генератор Неудачливый вор
		
		case "ShipLetters_6":
			pchar.questTemp.different.GiveShipLetters.speakShipyard = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "让我看看... 不, 没有像他这样的人。 我想你应该去问港口主管这件事。 ";
				link.l1 = "当然... ";
				link.l1.go = "exit";
			}
			else
			{
				sTemp = "让我看看, 船长! 啊哈! 这些是我一个好朋友的船舶文件, 我最喜欢的客户! 我相信他会因为你的发现而非常高兴, 并会给你应得的奖励。 ";
				sTemp = sTemp + "我想我可以代表他给你 " + sti(pchar.questTemp.different.GiveShipLetters.price2) + " 比索";
				dialog.text = sTemp;
				link.l1	= "不, 我不这么认为... ";
				link.l1.go = "exit";
				link.l2 = "谢谢你, " + GetFullName(NPChar) + "! 请代我向你的朋友问好。 ";
				link.l2.go = "ShipLetters_7";				
			}	
		break;

		case "ShipLetters_7":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2)); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "4");		
			AddQuestUserData("GiveShipLetters", "sSex", GetSexPhrase("",""));		
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters"); 		
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "EncGirl_1":
			dialog.text = "我在仔细听你说。 ";
			link.l1 = "我把你逃跑的人带来了。 ";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "哦, 船长, 太感谢你了! 她怎么样? 她受伤了吗? 她为什么跑? 为什么? \n她不明白吗? 新郎是个有钱有势的人! 年轻是天真愚蠢的... 甚至是残忍的。 记住! ";
			link.l1 = "嗯, 你是她的父亲, 最终决定在你, 但我不会急于举行婚礼... ";
			link.l1.go = "EncGirl_3";
		break;
		
		case "EncGirl_3":
			dialog.text = "你知道什么? 你有自己的孩子吗? 没有? 等你有了孩子, 再来找我, 我们再谈。 \n我答应过任何把她带回家的人会有奖励。 ";
			link.l1 = "谢谢。 你应该看好她。 我有一种预感, 她不会就此罢休。 ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;		
		
		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "哦, 所以你就是那个船长, 给我那浪子儿子带来了一个新娘? ";
				link.l1 = "是的, 是我。 ";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "哦, " + GetSexPhrase("他来了, 我们的恩人","她来了, 我们的女恩人") + "。 我想是来要奖励的吧? ";
				link.l1 = "嗯, 我不要奖励也行, 你的好话就够了。 ";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "我非常感激你没有在危急关头抛弃我的孩子, 并帮助他摆脱了困境。 请允许我感谢你, 并请接受这个微薄的礼物和我个人的一点心意。 ";
			link.l1 = "谢谢。 帮助这对年轻夫妇是我的荣幸。 ";
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = "感谢? 什么感谢? ! 你在说什么感谢? ! 感情... 你这个年纪怎么能这么轻率? ! 你纵容年轻人的任性, 还充当媒人, 真丢人! 你不仅把一个女孩从家里带走, 还毁了我那个傻儿子的生活。 不会有感谢给你。 再见。 ";
			link.l1 = "好吧, 你也一样... ";
			link.l1.go = "EncGirl_6_1";
		break;
		
		case "EncGirl_5_1":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.EncGirl.sum));
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item);
			AddQuestRecord("JungleGirl", "18");
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "EncGirl_6_1":
			dialog.text = "什么感情? 你在说什么感情? 感情... 你这个年纪怎么能如此轻率! 真羞耻, 你纵容年轻人的任性, 还充当媒人! 你不仅从家里带走了一个女孩, 还毁了我那新手的生活。 不会有感谢给你。 再见。 ";
			link.l1 = "好吧, 你也一样... ";
			link.l1.go = "EncGirl_6_2";
		break;
		
		case "EncGirl_6_2":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddQuestRecord("JungleGirl", "19");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("",""));
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();		
		break;
		
		case "shipyard":
			if(CheckAttribute(npchar, "TrialDelQuestMark"))
			{
				DeleteAttribute(npchar, "TrialDelQuestMark");
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("PortRoyal");
			}
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		    if (sti(Pchar.Ship.Type) == SHIP_NOTUSED || ok)
			{
			    NextDiag.CurrentNode = NextDiag.TempNode;
				DialogExit();
				LaunchShipyard(npchar);
			}
			else
			{
				dialog.text = NPCharRepPhrase(npchar, pcharrepphrase("你在开玩笑吗? 你的船在哪里? 我在港口没看到! ",
																	 "我对魔鬼发誓, 你骗不了我! 你的船不在港口! "),
													  pcharrepphrase("我在港口没看到你的船, " +GetFullName(pchar)+ "船长。 我希望她不是'飞翔的荷兰人'吧? ",
																	 "船长, 从码头装货容易得多。 把你的船开到港口再来。 "));
				link.l1 = NPCharRepPhrase(npchar, pcharrepphrase(RandSwear() + "真麻烦! 好吧, 老滑头, 回头见! ",
																 "我不想骗你, " + GetFullName(npchar) + ", 船在岛的另一边。 "),
												  pcharrepphrase("不。 我的船叫'黑珍珠'! 你的脸怎么了? 脸色苍白... 哈哈! 开玩笑的! ",
																 "谢谢你的建议, 我一定会这么做。 "));
			    link.l1.go = "exit";
			}
		break;
		
		case "Cannons":
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
			    NextDiag.CurrentNode = NextDiag.TempNode;
				DialogExit();
    			LaunchCannons(sti(rColony.StoreNum));
			}
			else
			{
				dialog.text = NPCharRepPhrase(npchar, pcharrepphrase("你在开玩笑吗? 你的船在哪里? 我在港口没看到! ",
																	 "我对魔鬼发誓, 你骗不了我! 你的船不在港口! "),
													  pcharrepphrase("我在港口没看到你的船, " +GetFullName(pchar)+ "船长。 我希望她不是'飞翔的荷兰人'吧? ",
																	 "船长, 从码头装货容易得多。 把你的船开到港口再来。 "));
				link.l1 = NPCharRepPhrase(npchar, pcharrepphrase(RandSwear() + "真麻烦! 好吧, 老滑头, 回头见! ",
																 "我不想骗你, " + GetFullName(npchar) + ", 船在岛的另一边。 "),
												  pcharrepphrase("不。 我的船叫'黑珍珠'! 你的脸怎么了? 脸色苍白... 哈哈! 开玩笑的! ",
																 "谢谢你的建议, 我一定会这么做。 "));
			    link.l1.go = "exit";
			}
		break;
		
		case "SailsGerald":
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				dialog.text = "更换帆的颜色需要 " +
				              FindRussianMoneyString(GetSailsTuningPrice(Pchar, npchar, SAILSCOLOR_PRICE_RATE))+
							  ", 绘制新徽章需要 " +
							  FindRussianMoneyString(GetSailsTuningPrice(Pchar, npchar, SAILSGERALD_PRICE_RATE)) +
							  ", 更换帆 - 取决于你的船。 ";
							  
				link.l1 = "选择新颜色。 ";
			    link.l1.go = "SailsColorChoose";
				link.l2 = "绘制新徽章。 ";
			    link.l2.go = "SailsGeraldChoose";
				link.l3 = "安装独特帆具。 "; 
				link.l3.go = "SailsTypeChoose";
				Link.l9 = "我改变主意了。 ";
				Link.l9.go = "exit";
			}
			else
			{
				dialog.text = NPCharRepPhrase(npchar, pcharrepphrase("你在开玩笑吗? 你的船在哪里? 我在港口没看到! ","我对魔鬼发誓, 你骗不了我! 你的船不在港口! "),pcharrepphrase("我在港口没看到你的船, " +GetFullName(pchar)+ "船长。 我希望她不是'飞翔的荷兰人'吧? ","船长, 从码头装货容易得多。 把你的船开到港口再来。 "));
				link.l1 = NPCharRepPhrase(npchar, pcharrepphrase(RandSwear() + "真麻烦! 好吧, 老滑头, 回头见! ","我不想骗你, " + GetFullName(npchar) + ", 船在岛的另一边。 "), pcharrepphrase("不。 我的船叫'黑珍珠'! 你的脸怎么了? 脸色苍白... 哈哈! 开玩笑的! ","谢谢你的建议, 我一定会这么做。 "));
			    link.l1.go = "exit";
			}
		break;
		
		case "SailsTypeChoose":
			dialog.text = "你想安装什么帆? 目前你有 " + GetSailsType(sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails)) + "。 ";
			Link.l6 = "我想安装 " + GetSailsType(6) + "。 ";
			Link.l6.go = "SailsTypeChooseIDX_6";
			Link.l7 = "我想安装 " + GetSailsType(7)  + "。 ";
			Link.l7.go = "SailsTypeChooseIDX_7";
			Link.l8 = "我想安装 " + GetSailsType(8)  + "。 ";
			Link.l8.go = "SailsTypeChooseIDX_8";
			Link.l9 = "我想安装 " + GetSailsType(9)  + "。 ";
			Link.l9.go = "SailsTypeChooseIDX_9";
			Link.l10 = "我想安装 " + GetSailsType(10)  + "。 ";
			Link.l10.go = "SailsTypeChooseIDX_10";
			Link.l11 = "我想安装 " + GetSailsType(11)  + "。 ";
			Link.l11.go = "SailsTypeChooseIDX_11";
			attrLoc = "l" + sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails);
			DeleteAttribute(Link, attrLoc);
			Link.l99 = "我改变主意了。 ";
			Link.l99.go = "exit";
		break;
		
		case "SailsTypeChoose2":
            NPChar.SailsTypeMoney = GetSailsTypePrice(sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails),
			                                          sti(NPChar.SailsTypeChooseIDX),
													  stf(NPChar.ShipCostRate),
													  sti(RealShips[sti(Pchar.Ship.Type)].Price));
													  
			dialog.text = "目前你有 " + GetSailsType(sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails)) + ", 你选择了 " + GetSailsType(sti(NPChar.SailsTypeChooseIDX)) + "。 更换的费用是 " + FindRussianMoneyString(sti(NPChar.SailsTypeMoney)) + "。 继续? ";

			if (sti(NPChar.SailsTypeMoney) <= sti(Pchar.Money))
			{
				Link.l1 = "是。 ";
				Link.l1.go = "SailsTypeChooseDone";
			}
			Link.l99 = "否。 ";
			Link.l99.go = "exit";
		break;
		
		case "SailsTypeChooseDone":
			AddMoneyToCharacter(Pchar, -sti(NPChar.SailsTypeMoney));
			dialog.text = "太好了! 一切都会好起来的。 ";
			Link.l9 = "谢谢。 ";
			Link.l9.go = "exit";

			RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails = sti(NPChar.SailsTypeChooseIDX);
			WaitDate("",0,0,0, 1, 30);
		break;
		
		case "SailsColorChoose":
			if (GetSailsTuningPrice(Pchar, npchar, SAILSCOLOR_PRICE_RATE) <= sti(Pchar.Money))
			{
				dialog.text = "我们选什么颜色? 价格是 " + FindRussianMoneyString(GetSailsTuningPrice(Pchar, npchar, SAILSCOLOR_PRICE_RATE)) + "。 ";
				for (i = 0; i < SAILS_COLOR_QUANTITY; i++)
				{
					if (CheckSailsColor(Pchar, i))
					{
						attrLoc = "l" + i;
						Link.(attrLoc) = XI_ConvertString(SailsColors[i].name);
						Link.(attrLoc).go = "SailsColorIdx_" + i;
					}
				}
				Link.l99 = "我改变主意了。 ";
				Link.l99.go = "exit";
			}
			else
			{
				dialog.text = "等你有钱了再来。 ";
				Link.l9 = "好的。 ";
				Link.l9.go = "exit";	
			}
		break;
		
		case "SailsColorDone":
			AddMoneyToCharacter(Pchar, -GetSailsTuningPrice(Pchar, npchar, SAILSCOLOR_PRICE_RATE));
			dialog.text = "同意。 我们将把帆涂成 " + GetStrSmallRegister(XI_ConvertString(SailsColors[sti(NPChar.SailsColorIdx)].name)) + " 色。 ";
			Link.l9 = "谢谢。 ";
			Link.l9.go = "exit";
			
			SetSailsColor(Pchar, sti(NPChar.SailsColorIdx));
			WaitDate("",0,0,0, 1, 30);
		break;
		
		case "SailsGeraldChoose":
			if(GetSailsTuningPrice(Pchar, npchar, SAILSGERALD_PRICE_RATE) <= sti(Pchar.Money))
			{
				if(CheckSailsGerald(Pchar) && CanSetSailsGerald(PChar)) // Warship fix 04.06.09
				{
					NextDiag.CurrentNode = NextDiag.TempNode;
					DialogExit();
					LaunchSailsGeraldScreen(npchar);
				}
				else
				{
					dialog.text = "不幸的是, 你的船不能佩戴徽章。 ";
					Link.l9 = "可惜。 ";
					Link.l9.go = "exit";
				}
			}
			else
			{
				dialog.text = "等你有钱了再来。 ";
				Link.l9 = "好的。 ";
				Link.l9.go = "exit";	
			}
		break;

//--> -------------------------------------------Бремя гасконца---------------------------------------------------
		case "Sharlie":
			dialog.text = "很抱歉让你失望了, 先生, 但现在我没有任何船出售。 ";
			link.l1 = "这真的很奇怪, 因为有人告诉我你的造船厂有一艘全新的小帆船。 ";
			link.l1.go = "Sharlie_1";
		break;
		
		case "Sharlie_1":
			if (GetQuestPastDayParam("questTemp.Sharlie_ship") > 3)
			{
				dialog.text = "你知道这可能是关于米歇尔.德.蒙佩尔用三千比索担保的那艘小帆船吗? 所以这艘船已经售出了, 因为根据合同, 总金额必须在船下水后不迟于一周内支付。 \n所有期限都过了, 我没有收到钱, 所以小帆船被卖掉了。 很抱歉, 先生。 ";
				link.l1 = "是的, 确实很不幸... 但你确定你没有其他船出售吗? ";
				link.l1.go = "Sharlie_6";
			}
			else
			{
			dialog.text = "嗯。 是的, 确实。 但是... ";
			link.l1 = "而且已经有了五千比索的定金。 米歇尔.德.蒙佩尔, 他存了钱, 把这艘船的所有权利都给了我。 ";
			link.l1.go = "Sharlie_2";
			}
		break;
		
		case "Sharlie_2":
			int iDay = 3-sti(GetQuestPastDayParam("questTemp.Sharlie_ship"));
			sTemp = "你只有 " + FindRussianDaysString(iDay) + "";
			if (iDay == 0) sTemp = "今天是最后一天";
			dialog.text = "好吧, 如果是这样的话, 先生, 让我们继续谈话。 正如你正确指出的, 我已经为这艘船收到了五千比索的定金。 但我认为这艘船的总价值, 包括弹药, 是一万五千比索。 所以付给我一万, 这艘船就是你的了。 \n根据合同, 你必须在船下水后不迟于一周内支付款项。 " + sTemp + ", 然后我就可以自由地把这艘船卖给另一个客户。 请注意, 已经有一个了, 所以你最好快点。 ";
			if (sti(Pchar.money) >= 10000)
			{
				link.l1 = "不必着急。 我现在身上有所需的金额。 给你。 ";
				link.l1.go = "Sharlie_4";
			}
			link.l2 = "好的, 好的。 你会拿到钱的, 先生。 我不会让你等很久的。 ";
			link.l2.go = "exit";
			NextDiag.TempNode = "Sharlie_3";
		break;
		
		case "Sharlie_3":
			if (CheckAttribute(pchar, "questTemp.Sharlie.Rum") || CheckAttribute(pchar, "questTemp.Sharlie.Gigolo") || CheckAttribute(pchar, "questTemp.Sharlie.RescueDaughter"))
			{
				dialog.text = "我能帮你吗, 先生? ";
				Link.l1 = "我只是来看看你有什么船... 但现在我有点忙 - 我有一件未完成的事要处理。 我一处理完就回来。 ";
				Link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.Sharlie == "ship" || pchar.questTemp.Sharlie == "ship_fast") // Addon 2016-1 Jason пиратская линейка 1
			{	
				if (GetQuestPastDayParam("questTemp.Sharlie_ship") > 3)
				{
					dialog.text = "先生, 我警告过你只有三天时间。 时间到了, 你仍然没有给我钱, 所以我们的交易到期了, 我把船卖给了另一个客户。 无意冒犯。 ";
					link.l1 = "是的, 确实很不幸... 但你确定你没有其他船出售吗? ";
					link.l1.go = "Sharlie_6";
				}
				else
				{
					dialog.text = "你给我带来一万了吗, 先生? ";
					if (sti(Pchar.money) >= 10000)
					{
						link.l1 = "当然有。 给你。 ";
						link.l1.go = "Sharlie_4";
					}
					link.l2 = "没有, 我还在努力。 ";
					link.l2.go = "exit";
					NextDiag.TempNode = "Sharlie_3";
				}
			}
		break;
		
		case "Sharlie_4":
			AddMoneyToCharacter(pchar, -10000);
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("fortfrance_town", "reload", "reload5_back");
			dialog.text = "那么请允许我祝贺你这次成功的购买。 这艘船是你的了。 我希望她能好好为你服务。 ";
			link.l1 = "谢谢! ";
			link.l1.go = "Sharlie_5";
		break;
		
		case "Sharlie_5":
			NextDiag.CurrentNode = "First time";
			DialogExit();
			pchar.questTemp.Sharlie.Ship = "lugger";
			pchar.questTemp.Sharlie = "crew";
			//стартовый люггер
			pchar.Ship.Type = GenerateShipHand(pchar, SHIP_LUGGER, 6, 800, 40, 610, 16000, 15.2, 58.8, 1.42);
			SetMaxShipStats(pchar);
			SetBaseShipData(pchar);
			ResetShipCannonsDamages(pchar);
			SetShipCannonsDamagesNull(pchar);
			NullCharacterGoods(pchar);
			SetCrewQuantityOverMax(PChar, 0);
			/* UpgradeShipParameter(pchar, "SpeedRate");
			UpgradeShipParameter(pchar, "TurnRate");
			UpgradeShipParameter(pchar, "WindAgainstSpeed");
			UpgradeShipParameter(pchar, "HP");
			UpgradeShipParameter(pchar, "MaxCrew");
			UpgradeShipParameter(pchar, "Capacity");
			//UpgradeShipParameter(pchar, "Cannons");
			pchar.ship.HP = 732; */
			//UpgradeShipFull(pchar);
			UpgradeShipParameter(pchar, "Capacity");
			RealShips[sti(pchar.Ship.Type)].ship.upgrades.hull  = "q"; // belamour особый скин
			AddLandQuestMark(characterFromId("FortFrance_tavernkeeper"), "questmarkmain");
			AddCharacterGoods(pchar, GOOD_BALLS, 100);
			AddCharacterGoods(pchar, GOOD_GRAPES, 100);
			AddCharacterGoods(pchar, GOOD_KNIPPELS, 100);
			AddCharacterGoods(pchar, GOOD_BOMBS, 100);
			AddCharacterGoods(pchar, GOOD_POWDER, 220);
			pchar.Ship.name = "Adeline";
			pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS6;
			AddQuestRecord("Sharlie", "6");
			bDisableFastReload = false;//открыть переход
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			if (GetCharacterIndex("GigoloMan") != -1)
			{
				sld = characterFromId("GigoloMan");
				sld.lifeday = 0;
			}
			pchar.GenQuest.StoreGoods.StoreIdx = Fortfrance_STORE;
			pchar.GenQuest.StoreGoods.Starting = true; // заполняем магазин
			bNoEatNoRats  = true; // отменяем еду и крыс
			GiveItem2Character(pchar, "map_normal");
		break;
		
		case "Sharlie_6":
			if (sti(Pchar.money) >= 15000)
				{
					dialog.text = "嗯... 其实我有一艘, 但不确定是否适合你。 ";
					link.l1 = "好吧, 我现在也不能太挑剔了。 给我看看你有什么! ";
					link.l1.go = "Sharlie_7";
				}
				else
				{
					dialog.text = "听着, 先生, 先赚点钱再来问船的事, 好吗? 这里没人会免费给你东西。 我说清楚了吗? ";
					link.l1 = "非常清楚, 虽然没必要这么粗鲁。 好吧, 等我有钱了再来。 ";
					link.l1.go = "exit";
					NextDiag.TempNode = "Sharlie_shipwait";
				}
		break;
		
		case "Sharlie_7":
			dialog.text = "那你看。 我最近以合理的价格买了一艘单桅帆船。 这是一艘前海盗船, 它的前主人已经因多项罪行被安全绞死了。 坦率地说, 这艘船不如小帆船好, 而且损坏严重, 但仍然可以出海。 \n我现在没有时间修理她 - 我所有的人都在忙着建造一艘被订购的双桅横帆船, 所以你可以按现状从我这里买走她。 考虑到这一点, 我会比平时便宜卖给你, 同时包括货舱里的货物 - 一万五千比索。 ";
			link.l1 = "成交。 她能航行, 这才是最重要的。 瓜德罗普就在附近 - 如果你没有这样的机会, 我会在那里修理它。 ";
			link.l1.go = "Sharlie_8";
		break;
		
		case "Sharlie_8":
			AddMoneyToCharacter(pchar, -15000);
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("fortfrance_town", "reload", "reload5_back");
			dialog.text = "那么请允许我祝贺你这次成功的购买。 这艘船是你的了。 我希望她能好好为你服务。 ";
			link.l1 = "谢谢! ";
			link.l1.go = "Sharlie_9";
		break;
		
		case "Sharlie_9":
			NextDiag.CurrentNode = "First time";
			DialogExit();
			pchar.questTemp.Sharlie.Ship = "sloop";
			pchar.questTemp.Sharlie = "crew";
			//стартовый шлюп
			pchar.Ship.Type = GenerateShipExt(SHIP_SLOOP, true, pchar);
			SetMaxShipStats(pchar);
			SetBaseShipData(pchar);
			ResetShipCannonsDamages(pchar);
			SetShipCannonsDamagesNull(pchar);
			NullCharacterGoods(pchar);
			SetCrewQuantityOverMax(PChar, 0);
			/* UpgradeShipParameter(pchar, "SpeedRate");
			UpgradeShipParameter(pchar, "TurnRate");
			UpgradeShipParameter(pchar, "WindAgainstSpeed");
			UpgradeShipParameter(pchar, "HP");
			UpgradeShipParameter(pchar, "MaxCrew"); */
			UpgradeShipParameter(pchar, "Capacity");
			AddCharacterGoods(pchar, GOOD_BALLS, 51);
			AddCharacterGoods(pchar, GOOD_GRAPES, 39);
			AddCharacterGoods(pchar, GOOD_KNIPPELS, 54);
			AddCharacterGoods(pchar, GOOD_BOMBS, 36);
			AddCharacterGoods(pchar, GOOD_POWDER, 231);
			pchar.Ship.name = "Black Hound";
			pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS3;
			AddQuestRecord("Sharlie", "6");
			bDisableFastReload = false;//открыть переход
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			if (GetCharacterIndex("GigoloMan") != -1)
			{
				sld = characterFromId("GigoloMan");
				sld.lifeday = 0;
			}
			pchar.GenQuest.StoreGoods.StoreIdx = Fortfrance_STORE;
			pchar.GenQuest.StoreGoods.Starting = true; // заполняем магазин
			bNoEatNoRats  = true; // отменяем еду и крыс
			GiveItem2Character(pchar, "map_normal");
		break;
		
		case "Sharlie_shipwait":
			dialog.text = "那么, 先生, 你带钱回来了吗? ";
			if (sti(Pchar.money) >= 15000)
			{
				link.l1 = "是的, 我想我有足够的钱买一艘破旧的船。 ";
				link.l1.go = "Sharlie_7";
			}
			else
			{
				link.l1 = "我还没有足够的钱。 只是顺便来看看... ";
				link.l1.go = "exit";
				NextDiag.TempNode = "Sharlie_shipwait";
			}
		break;
//< —-----------------------------------------Бремя гасконца-----------------------------------------------------
		// Addon-2016 Jason, французские миниквесты (ФМК) ФМК-Мартиника
		case "FMQM_oil_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto5", "FMQM_Looking", -1);
			pchar.questTemp.FMQM = "remove_oil1";
		break;
		
		case "FMQM_oil_2":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("FMQM_officer");
			sld.Dialog.currentnode = "officer_3";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
			pchar.questTemp.FMQM = "remove_oil2";
		break;
		
		case "FMQM_oil_3":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("FMQM_officer");
			sld.Dialog.currentnode = "officer_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
			pchar.questTemp.FMQM = "remove_oil3";
		break;
		
		case "FMQM_oil_4":
			dialog.text = "唉, 我的朋友, 但我们俩都在这里受苦了。 他们没收了树脂, 另外我为了保释浪费了一大笔钱。 他们到底是怎么知道我们的行动的? 一定是我的一个工人... 我会处理这件事的, 愿上帝怜悯有罪的人! ";
			link.l1 = "意味着我所有的努力都白费了... ";
			link.l1.go = "FMQM_oil_5";
		break;
		
		case "FMQM_oil_5":
			dialog.text = "非常抱歉, 船长。 我们在这里无能为力, 命运有时就是个婊子。 ";
			link.l1 = "我明白了。 好吧, 那我就告辞了。 再见! ";
			link.l1.go = "FMQM_oil_6";
		break;
		
		case "FMQM_oil_6":
			DialogExit();
			AddQuestRecord("FMQ_Martinique", "12");
			pchar.questTemp.FMQM = "officer";
			pchar.quest.FMQM_advice.win_condition.l1 = "location";
			pchar.quest.FMQM_advice.win_condition.l1.location = "FortFrance_town";
			pchar.quest.FMQM_advice.function = "FMQM_GuideAdvice";
			DeleteAttribute(pchar, "questTemp.FMQM.Oil");
		break;
		
		// Addon 2016-1 Jason пиратская линейка
		case "mtraxx_x":
			dialog.text = "我想回到那次谈话。 如果你给我一些额外的丝绸... 我愿意为你船上的任何工作提供一个不错的折扣... 一个非常可观的折扣。 ";
			link.l1 = "大师, 让我们直奔主题。 我保证我不是间谍, 也不是戴利上校的人。 此外, 我和马库斯.泰雷克斯合作, 你应该熟悉这个名字。 那么, 我们打开天窗说亮话吧。 我知道你需要稳定的丝绸帆布供应, 马库斯.泰雷克斯愿意为你带来。 也是稳定的。 然而, 只有在我们就价格达成一致的情况下。 那么我们直接谈价格吧, 大师? ";
			link.l1.go = "mtraxx_x_1";
		break;
		
		case "mtraxx_x_1":
			dialog.text = "好吧。 我似乎别无选择 - 要么你为戴利工作并把我送进监狱, 要么如果我不紧急找到大量丝绸 shipment, 我就会破产。 我愿意支付每块25达布隆, 但只接受大 shipment, 不少于100卷。 ";
			link.l1 = "那我们成交。 我相信泰雷克斯每月能为你提供100卷的 shipment。 ";
			link.l1.go = "mtraxx_x_2";
		break;
		
		case "mtraxx_x_2":
			dialog.text = "那太好了! 我可以马上购买第一批。 ";
			link.l1 = "现在不行, 但不会太久。 一艘载有你所需货物的船目前在卡普斯特维尔, 我马上前往那里, 我会把她派给你。 我们在哪里卸货? ";
			link.l1.go = "mtraxx_x_3";
		break;
		
		case "mtraxx_x_3":
			dialog.text = "我们这样安排吧。 每月10日至15日夜间, 我的人会在海湾等待你的访客... 不, 等等, 最好在内格里尔角。 这肯定是一段漫长的路程, 但巡逻队要少得多... 密码是:‘A merchant of Lyons’(里昂的商人)。 ";
			link.l1 = "成交, 大师。 我马上前往卡普斯特维尔。 ";
			link.l1.go = "mtraxx_x_4";
		break;
		
		case "mtraxx_x_4":
			dialog.text = "我希望你的船能快点到达, 我急需新丝绸。 ";
			link.l1 = "别担心, 一切都会好的。 祝你好运! ";
			link.l1.go = "mtraxx_x_5";
		break;
		
		case "mtraxx_x_5":
			DialogExit();
            AddQuestRecord("Roger_2", "21");
			pchar.questTemp.Mtraxx = "silk_10"; // покупатель найден
			sld = characterFromId("Jeffry");
			sld.DeckDialogNode = "Jeffry_9";
		break;
		// Jason Исла Мона
		case "IslaMona":
			if (CheckAttribute(pchar, "questTemp.IslaMona.Shipyarder") && pchar.questTemp.IslaMona.Shipyarder == npchar.id)
			{
				if (sti(NPChar.nation) != PIRATE && ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", 0) > 10)
				{
					dialog.text = "不, " +pchar.name+ "。 我对你没有意见, 但先解决你和我的国家之间的问题。 向王室的敌人出售如此有价值的库存可能会被误解。 ";
					link.l1 = "是啊, 当你把来源不明的走私货物走私到船上时, 你就是最好的朋友? 等着我来解决这个误解。 ";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "说说看。 为什么? 你在建造什么吗? ";
					link.l1 = "不, 我在做一个非常特殊的租船。 为一个种植园经理。 ";
					link.l1.go = "IslaMona_1";
				}
			}
			else
			{
				npchar.quest.IslaMonaTools = "true";
				dialog.text = "我帮不了你。 ";
				link.l1 = "真遗憾! ";
				link.l1.go = "exit";
			}
		break;
		
		case "IslaMona_1":
			dialog.text = "我明白了。 我希望这位经理给你提供了足够的东西, 因为我要为这样的一套工具收取很多费用。 你很幸运, 最近刚从大都市进口了一批。 ";
			link.l1 = "多少钱? ";
			link.l1.go = "IslaMona_2";
		break;
		
		case "IslaMona_2":
			pchar.questTemp.IslaMona.Shipyarder.Money = 1000;
			dialog.text = "一千枚金达布隆。 ";
			link.l1 = "你太贪心了, 我明白了。 好吧。 我买了。 ";
			link.l1.go = "IslaMona_7";
			link.l2 = "太贵了。 我怀疑像我这样的整套买家不会有另一个。 其中一些会卖掉, 一些会被当地流浪汉偷走。 打个折怎么样? ";
			link.l2.go = "IslaMona_3";
		break;
		
		case "IslaMona_3":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) < 60)
			{
				notification("技能检查失败 (60)", SKILL_COMMERCE);
				dialog.text = "我保证会出现的。 价格不变。 怎么样? 我不会等太久。 ";
				link.l1 = "好吧, 好吧, 好吧。 我买了。 ";
				link.l1.go = "IslaMona_7";
				AddCharacterExpToSkill(pchar, "Commerce", 200);
			}
			else
			{
				notification("技能检查通过", SKILL_COMMERCE);
				pchar.questTemp.IslaMona.Shipyarder.Money = 900;
				dialog.text = "好吧, 我们让一百。 九百。 我不能再低了。 别让我再让了。 ";
				link.l1 = "我也不会。 我同意。 ";
				link.l1.go = "IslaMona_7";
				link.l2 = "为什么不再给我一些? 作为批发商。 然后我会向你订购维修和油漆, 以及最漂亮的船首像。 ";
				link.l2.go = "IslaMona_4";
				AddCharacterExpToSkill(pchar, "Fortune", 100);
			}
		break;
		
		case "IslaMona_4":
            if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) < 85)
			{
				notification("技能检查失败 (85)", SKILL_COMMERCE);
				dialog.text = "我不在乎你是否订购一个活的 wench。 九百。 ";
				link.l1 = "好吧, 好吧, 好吧。 我买了。 ";
				link.l1.go = "IslaMona_7";
				AddCharacterExpToSkill(pchar, "Commerce", 400);
			}
			else
			{
				notification("技能检查通过", SKILL_COMMERCE);
				pchar.questTemp.IslaMona.Shipyarder.Money = 800;
				dialog.text = "你确定吗? 你不会忘记吧? 好吧, 再减一百。 但就这样了! ";
				link.l1 = "我不会忘记。 成交! ";
				link.l1.go = "IslaMona_7";
				link.l2 = "嗯, 我该怎么说呢... ";
				link.l2.go = "IslaMona_5";
				AddCharacterExpToSkill(pchar, "Fortune", 200);
			}
		break;
		
		case "IslaMona_5":
			dialog.text = "不可思议! " +pchar.name+ ", 他们忘了把你头骨里的铅弹取出来吗? 贪婪得像只蝎子! 我们都听说了你最近的 escapades! 你已经赚了一堆金子, 所以不要阻止别人赚钱。 再多说一个字, 我就不会低于一千出售。 ";
			link.l1 = "好的, 好的! 冷静点。 我同意。 ";
			link.l1.go = "IslaMona_7";
			link.l2 = "但是, " + npchar.name+ ", 我有小孩! 我也得为他们着想! 你知道, 诚实的货运报酬不够! ";
			link.l2.go = "IslaMona_6";
		break;
		
		case "IslaMona_6":
            if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) < 100)
			{
				notification("技能检查失败 (100)", SKILL_COMMERCE);
				pchar.questTemp.IslaMona.Shipyarder.Money = 1000;
				dialog.text = "妓院女孩的孩子不算数, " +pchar.name+ "。 我受够你了。 一千达布隆现金, 否则我们就道别。 ";
				link.l1 = "你是什么意思, 他们不算? 呃。 我同意, 你是个骗子。 ";
				link.l1.go = "IslaMona_7";
				AddCharacterExpToSkill(pchar, "Commerce", 800);
			}
			else
			{
				notification("技能检查通过", SKILL_COMMERCE);
				pchar.questTemp.IslaMona.Shipyarder.Money = 700;
				dialog.text = "我不知道你有孩子。 而且情况这么糟。 好吧, 别抱怨了。 七百。 这几乎是亏损了。 ";
				link.l1 = "我不会忘记。 成交! ";
				link.l1.go = "IslaMona_7";
				AddCharacterExpToSkill(pchar, "Fortune", 400);
				Achievment_SetStat(106, 1);
			}
		break;
		
		case "IslaMona_7":
			dialog.text = "那么, 你欠我 " + sti(pchar.questTemp.IslaMona.Shipyarder.Money) + " 达布隆。 ";
			if (GetCharacterItem(pchar, "gold_dublon") >= sti(pchar.questTemp.IslaMona.Shipyarder.Money))
			{
				link.l1 = "给你, 我把最后一点都给你了, 我什么都没有了。 ";
				link.l1.go = "IslaMona_8";
			}
			else
			{
				if (GetCharacterItem(pchar, "gold_dublon") < 1)
				{
					link.l1 = "等等, 我要去找高利贷借钱。 ";
					link.l1.go = "IslaMona_money_exit";
				}
				else
				{
					link.l1 = "我身上只有 " + FindRussianDublonString(GetCharacterItem(pchar, "gold_dublon")) + "。 拿着这个, 我去找高利贷。 ";
					link.l1.go = "IslaMona_money";
				}
			}
		break;
		
		case "IslaMona_money":
			pchar.questTemp.IslaMona.Shipyarder.Money = sti(pchar.questTemp.IslaMona.Shipyarder.Money)-GetCharacterItem(pchar, "gold_dublon");
			Log_Info("你给了 " + FindRussianDublonString(GetCharacterItem(pchar, "gold_dublon")) + "");
			RemoveItems(pchar, "gold_dublon", GetCharacterItem(pchar, "gold_dublon"));
			PlaySound("interface\important_item.wav");
			dialog.text = "不要为我感到难过, 你的船舱锁里装满了金子。 你还欠我 " + FindRussianDublonString(sti(pchar.questTemp.IslaMona.Shipyarder.Money)) + "。 ";
			link.l1 = "";
			link.l1.go = "IslaMona_money_exit";
		break;
		
		case "IslaMona_money_exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			npchar.quest.IslaMonaMoney = "true";
			pchar.questTemp.IslaMona = "dublon";
		break;
		
		case "IslaMona_8":
			Log_Info("你给了 " + FindRussianDublonString(sti(pchar.questTemp.IslaMona.Shipyarder.Money)) + "");
			RemoveItems(pchar, "gold_dublon", sti(pchar.questTemp.IslaMona.Shipyarder.Money));
			PlaySound("interface\important_item.wav");
			dialog.text = "太好了。 全部金额都到了。 工具将被送到你的船上。 这些是一些沉重的板条箱。 ";
			link.l1 = "谢谢你, " + npchar.name+ "! ";
			link.l1.go = "IslaMona_9";
		break;
		
		case "IslaMona_9":
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			GiveItem2Character(pchar, "islamona_toolbox");
			DeleteAttribute(pchar, "questTemp.IslaMona.Shipyarder");
			DeleteAttribute(npchar, "quest.IslaMonaMoney");
			AddQuestRecord("IslaMona", "2");
			pchar.questTemp.IslaMona = "get_tools";
		break;
	}
}

string findShipyardCity(ref NPChar)
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES); 
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (sti(colonies[n].nation) != PIRATE && colonies[n].id != "Panama" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //не на свой остров
		{
			if (GetCharacterIndex(colonies[n].id + "_shipyarder") != -1)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[rand(howStore-1)];
	return colonies[nation].id;
}

// проверка какой уже цвет есть
bool CheckSailsColor(ref chr, int col)
{
	int    st = GetCharacterShipType(chr);
	ref    shref;
	
	if (st != SHIP_NOTUSED)
	{
		shref = GetRealShip(st); 
		st = -1;
		if (!CheckAttribute(shref, "ShipSails.SailsColor"))  st = 0; // нету - это белый
		if (CheckAttribute(shref, "SailsColorIdx"))  st = sti(shref.SailsColorIdx);
		if (st == col) return false;
	}
	return true;		
}

bool CheckSailsGerald(ref chr)
{
    int    st = GetCharacterShipType(chr);
	ref    shref;
	if (st != SHIP_NOTUSED)
	{
		shref = GetRealShip(st);
		if (CheckAttribute(shref, "GeraldSails"))  return true;
	}
	return false;
}

string GetSailsType(int _type)
{
	string sSail;
	
	switch (_type)
	{
	    case 1 : sSail = ""+XI_ConvertString("sails_1")+""; break;
	    case 2 : sSail = ""+XI_ConvertString("sails_2")+""; break;
	    case 3 : sSail = ""+XI_ConvertString("sails_3")+""; break;
		case 4 : sSail = ""+XI_ConvertString("sails_4")+""; break;
		case 5 : sSail = ""+XI_ConvertString("sails_5")+""; break;
		case 6 : sSail = ""+XI_ConvertString("sails_6")+""; break;
		case 7 : sSail = ""+XI_ConvertString("sails_7")+""; break;
		case 8 : sSail = ""+XI_ConvertString("sails_8")+""; break;
		case 9 : sSail = ""+XI_ConvertString("sails_9")+""; break;
		case 10 : sSail = ""+XI_ConvertString("sails_10")+""; break;
		case 11 : sSail = ""+XI_ConvertString("sails_11")+""; break;
	}
	return sSail;
}

int GetSailsTypePrice(int _asis, int _tobe, float _shipCostRate, int _price)
{
	int ret;
	ret = _tobe - _asis;
	
	if (ret < 0) ret = 0;
	
	return makeint((ret*_price*0.05 + _price*0.05)*_shipCostRate / 10) * 10;
}

void SelectFindship_ShipType()
{
	int iRank;
	if (sti(pchar.rank) < 7) iRank = 0;
	if (sti(pchar.rank) >= 7 && sti(pchar.rank) < 11) iRank = 1;
	if (sti(pchar.rank) >= 11 && sti(pchar.rank) < 20) iRank = 2;
	if (sti(pchar.rank) >= 20 && sti(pchar.rank) <= 27) iRank = 3;
	
	int iShip = SHIP_WAR_TARTANE;
	switch (iRank)
	{
		case 0:
			iShip = sti(RandPhraseSimple(its(GetRandomShipType(FLAG_SHIP_CLASS_6, FLAG_SHIP_TYPE_ANY, FLAG_SHIP_NATION_ANY)), 
										 its(GetRandomShipType(FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_MERCHANT + FLAG_SHIP_TYPE_UNIVERSAL, FLAG_SHIP_NATION_ANY))));
		break;
		case 1:  
			iShip = sti(LinkRandPhrase(its(GetRandomShipType(FLAG_SHIP_CLASS_6, FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_RAIDER, FLAG_SHIP_NATION_ANY)), 
									   its(GetRandomShipType(FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_ANY, FLAG_SHIP_NATION_ANY)),
									   its(GetRandomShipType(FLAG_SHIP_CLASS_4, FLAG_SHIP_TYPE_MERCHANT + FLAG_SHIP_TYPE_UNIVERSAL, FLAG_SHIP_NATION_ANY))));
		break; 
		case 2:  
			iShip = sti(LinkRandPhrase(its(GetRandomShipType(FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_RAIDER, FLAG_SHIP_NATION_ANY)), 
									   its(GetRandomShipType(FLAG_SHIP_CLASS_4, FLAG_SHIP_TYPE_ANY, FLAG_SHIP_NATION_ANY)),
									   its(GetRandomShipType(FLAG_SHIP_CLASS_3, FLAG_SHIP_TYPE_MERCHANT + FLAG_SHIP_TYPE_UNIVERSAL, FLAG_SHIP_NATION_ANY))));
		break;
		case 3:  
			iShip = sti(LinkRandPhrase(its(GetRandomShipType(FLAG_SHIP_CLASS_4, FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_RAIDER, FLAG_SHIP_NATION_ANY)), 
									   its(GetRandomShipType(FLAG_SHIP_CLASS_3, FLAG_SHIP_TYPE_ANY, FLAG_SHIP_NATION_ANY)),
									   its(GetRandomShipType(FLAG_SHIP_CLASS_2, FLAG_SHIP_TYPE_MERCHANT + FLAG_SHIP_TYPE_UNIVERSAL, FLAG_SHIP_NATION_ANY))));
		break;
	}
	
	pchar.GenQuest.Findship.Shipyarder.ShipType = iShip;
}

// проверка количества материалов для корабельного тюнинга
void checkMatherial(ref Pchar, ref NPChar, int good)
{
    int amount;

    amount = GetSquadronGoods(Pchar, good) - sti(NPChar.Tuning.Matherial);
    if (amount < 0)
    {
       amount = amount + sti(NPChar.Tuning.Matherial);
    }
    else
    {
        amount = sti(NPChar.Tuning.Matherial);
    }
    RemoveCharacterGoods(Pchar, good, amount);
    NPChar.Tuning.Matherial = sti(NPChar.Tuning.Matherial) - amount;
}

/*
  _chr 		- ГГ
  NPChar 	- верфист
  MaterialNum -  номер материала для апгрейда 
	 1 - товар	 
	 2 - цена в дублонах(сундуки)
  Функция возвращает кол-во материала необходимого для данного типа апгрейда	  
*/

int GetMaterialQtyUpgrade( ref _chr, ref _nchar, int MaterialNum )
{
	if ( sti(_chr.Ship.Type) == SHIP_NOTUSED) return 0;
	
	float fQuestShip 	= 1.0;
	float LEcoeff       = 1.0; // legendary edition
		
	int   	shipClass     		= sti(RealShips[sti(_chr.Ship.Type)].Class);	
	int   	shipMinCrew   		= sti(RealShips[sti(_chr.Ship.Type)].MinCrew);	
	int 	shipPrice			= sti(RealShips[sti(_chr.Ship.Type)].Price);	
		
    if(shipClass == 4) LEcoeff = 0.38;
    if(shipClass > 4) LEcoeff = 0.25;
	if(CheckAttribute(&RealShips[sti(_chr.Ship.Type)], "QuestShip")) 	fQuestShip = 1.3;	

	if(MaterialNum == 1) 
	{
	int Material 	= makeint((40 * (8 - shipClass) + 25 * MOD_SKILL_ENEMY_RATE + hrand(shipMinCrew)) * fQuestShip * LEcoeff);
	if(Material < 1) 		Material 	= 1;
		return Material;
	}
	if(MaterialNum == 2)
	{
		int WorkPrice 	= 1;
		switch (shipClass)
		{
			case 1: 
				WorkPrice = 10;
			break;
			case 2: 
				WorkPrice = 7;
			break;
			case 3: 
				WorkPrice = 5;
			break;
			case 4: 
				WorkPrice = 3;
			break;
			case 5: 
				WorkPrice = 2;
			break;
			case 6: 
				WorkPrice = 1;
			break;
		}
		return WorkPrice;
	}
	
	return 0;
}
// belamour legendary edition тюнинг - проверка на сделанное
bool TuningAvailable()
{
	int num = 0;
    ref shTo = &RealShips[sti(Pchar.Ship.Type)];

	if(CheckAttribute(shTo, "Tuning.SpeedRate"))    num++;
	if(CheckAttribute(shTo, "Tuning.WindAgainst"))  num++;
	if(CheckAttribute(shTo, "Tuning.Cannon"))       num++;
	if(CheckAttribute(shTo, "Tuning.Capacity"))     num++;
	if(CheckAttribute(shTo, "Tuning.HP"))           num++;
	if(CheckAttribute(shTo, "Tuning.MaxCrew"))      num++;
	if(CheckAttribute(shTo, "Tuning.TurnRate"))     num++;
	if(CheckAttribute(shTo, "Tuning.MinCrew"))      num++;
	
	if(sti(shTo.Class) > 4 && num == 7 && !CheckAttribute(shTo, "Tuning.MinCrew"))
	{
		if(!CheckAttribute(shTo, "Tuning.All"))
        {
			if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_HIMERA) Achievment_Set("ach_CL_115");
			if(startHeroType == 4 && sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_SCHOONER_W)
			{
				if(pchar.ship.name == "Rainbow") Achievment_Set("ach_CL_126");
			}
            shTo.Tuning.All = true;
			Log_Info("船 " + pchar.ship.name + " 在世界地图上获得5%速度提升! ");
        }
        return false;
	}
	
	if(num < 8) return true;
	else
    {
        if(!CheckAttribute(shTo, "Tuning.All"))
        {
			if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_HIMERA) Achievment_Set("ach_CL_115");
			if(startHeroType == 4 && sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_SCHOONER_W)
			{
				if(pchar.ship.name == "Rainbow") Achievment_Set("ach_CL_126");
			}
            shTo.Tuning.All = true;
			Log_Info("船 " + pchar.ship.name + " 在世界地图上获得5%速度提升! ");
        }
        return false;
    }
}

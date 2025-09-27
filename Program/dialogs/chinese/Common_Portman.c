#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
string sProf;		//  без оффа hasert	
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag, arCapBase, arCapLocal;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// доп повека
	if (!CheckAttribute(NPChar, "Portman")) NPChar.Portman = 0;
	if (!CheckAttribute(NPChar, "PortManPrice")) NPChar.PortManPrice = (0.06 + frnd()*0.1);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\PortMan\" + NPChar.City + "_PortMan.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06

    int i, cn, iTemp;
    ref chref, compref; // без оффа hasert
	ref rRealShip;
    string attrL, sTitle, sCapitainId, s1;
	string sColony;
    
	String sLastSpeakDate = LastSpeakDate();
	
	// Warship 25.07.09 Генер "Сгоревшее судно"。 Даты отказа ГГ - если отказал, то предложит снова только на след сутки
	if(CheckAttribute(NPChar, "Quest.BurntShip.LastQuestDate") && NPChar.Quest.BurntShip.LastQuestDate != sLastSpeakDate)
	{
		DeleteAttribute(NPChar, "Quest.BurntShip");
	}
    
    bool ok;
    int iTest = FindColony(NPChar.City); // город магазина
    ref rColony;
    string sFrom_sea = "";
	npchar.quest.qty = CheckCapitainsList(npchar); //для списка кэпов

	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
		sFrom_sea = rColony.from_sea;
	}
	
	attrL = Dialog.CurrentNode;
	// hasert блок для сторожа ==>
	if(HasSubStr(attrL, "ShipStockManBack11_"))
	{
		i = findsubstr(attrL, "_" , 0);
		NPChar.StoreWithOff = 1;
		NPChar.ShipToStoreIdx = strcut(attrL, i+1, strlen(attrL)-1); // индех в конце
		Dialog.CurrentNode = "ShipStockManBack";
	}
	
	if(HasSubStr(attrL, "ShipStockManBack22_"))
	{
		i = findsubstr(attrL, "_" , 0);
		NPChar.StoreWithOff = 0;
		NPChar.ShipToStoreIdx = strcut(attrL, i+1, strlen(attrL)-1); // индех в конце
		Dialog.CurrentNode = "ShipStockManBack";
	}

	if(HasSubStr(attrL, "ShipStockManBack2_"))
	{
		i = findsubstr(attrL, "_" , 0);
		AddMoneyToCharacter(Pchar, -sti(NPChar.MoneyForShip));

		chref = GetCharacter(sti(NPChar.ShipToStoreIdx));//сторож

		////DownCrewExp(chref,GetNpcQuestPastDayParam(chref, "ShipInStockMan.Date"));

        int iChar = GetPassenger(PChar, sti(strcut(attrL, i+1, strlen(attrL)-1))); //выбранный пассажир
		compref = GetCharacter(iChar);

		DeleteAttribute(compref,"ship");//зачем-то стираем корабль офицера, хотя его там и не должно быть
		compref.ship = "";

		aref    arTo, arFrom;

		makearef(arTo, compref.ship);
		makearef(arFrom, chref.Ship);
		CopyAttributes(arTo, arFrom);

		// снимем пассажира -->
		CheckForReleaseOfficer(iChar);//увольнение офицера с должностей, если он не просто пассажир
		RemovePassenger(pchar, compref);
		// снимем пассажира <--
		SetCompanionIndex(pchar, -1, iChar);
		DelBakSkill(compref);
		DeleteAttribute(chref, "ShipInStockMan");
		if(CheckAttribute(chref, "DontNullShip"))
		{
			DeleteAttribute(chref, "DontNullShip");
			DeleteAttribute(NPChar, "DontNullShipBeliz");
		}
		chref.id = "ShipInStockMan";//сбрасываем индекс к стандартному, чтобы этот номер массива в следующий раз можно было занять
		DeleteAttribute(chref,"ship");//затираем данные корабля у сторожа
		chref.ship = "";
		LAi_SetCurHP(chref, 0.0);//ещё и убивать непися, чтоб точно очистился из массива?

		NPChar.Portman	= sti(NPChar.Portman) - 1;
		pchar.ShipInStock = sti(pchar.ShipInStock) - 1;
		Dialog.CurrentNode = "exit";//закрываем диалог, ещё одно подтверждение уже не справшиваем
	}
	
	if(HasSubStr(attrL, "ShipStockMan11_"))
	{
		i = findsubstr(attrL, "_" , 0);
		NPChar.StoreWithOff = 1;
		NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, sti(strcut(attrL, i+1, strlen(attrL)-1))); // индех в конце
		Dialog.CurrentNode = "ShipStock_2";
	}

	if(HasSubStr(attrL, "ShipStockMan22_"))
	{
		i = findsubstr(attrL, "_" , 0);
		NPChar.StoreWithOff = 0;
		NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, sti(strcut(attrL, i+1, strlen(attrL)-1))); // индех в конце
		Dialog.CurrentNode = "ShipStock_2";
	}
    //  <=== hasert
    
	if(HasSubStr(attrL, "BurntShip19_"))
	{
		i = findsubstr(attrL, "_" , 0);
	 	NPChar.Quest.BurntShip.ShipCompanionIndex = strcut(attrL, i + 1, strlen(attrL) - 1); // индех в конце
 	    Dialog.CurrentNode = "BurntShip19";
	}
    
	switch(Dialog.CurrentNode)
	{
        case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "fight":
			DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "First time":
			NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase("镇上拉响了警报, 现在所有人都在找你。 如果我是你, 就不会待在那里。 ", "所有的城市卫兵都在城里搜寻你。 我可不会傻到和你说话! ", "快跑, " + GetSexPhrase("伙计", "姑娘") + ", 在士兵把你打成筛子之前... "), 
					LinkRandPhrase("你需要什么, " + GetSexPhrase("恶棍", "臭家伙") + "? ! 城市卫兵已经嗅到了你的气味, 你跑不远的, 肮脏的海盗! ", "凶手, 马上离开我的房子! 卫兵! ", "我不怕你, " + GetSexPhrase("恶棍", "老鼠") + "! 很快他们就会在我们的堡垒里绞死你, 你跑不远的... "));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("呵, 警报对我来说从来不是问题... ", "他们永远抓不到我。 "), 
					RandPhraseSimple("闭上你的嘴, " + GetWorkTypeOfMan(npchar, "") + ", 也许我就不会把你肮脏的舌头扯出来! ", "呵, " + GetWorkTypeOfMan(npchar, "") + ", 还有那里的所有人 —抓海盗! 我告诉你, 伙计: 安静点, 你就能活下去... "));
				link.l1.go = "fight";
				break;
			}
			//Jason, фрахт
			if (CheckAttribute(pchar, "questTemp.WPU"))
			{
				if (pchar.questTemp.WPU.Fraht == "fail" && pchar.questTemp.WPU.Fraht.Nation == npchar.nation)
				{
					dialog.text = "哦, 我知道你是谁。 你签了运送货物的合同, 却反而偷了它! 卫兵, 卫兵! ";
					Link.l1 = "啊! ";
					Link.l1.go = "exit";
					LAi_group_Attack(NPChar, Pchar);
					break;
				}
			}
			//фрахт
			//--> Jason Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				dialog.text = "我能为你做什么, 先生? ";
				Link.l1 = "我和你有生意... ";
				Link.l1.go = "quests";
				Link.l2 = "抱歉, 我得走了。 ";
				Link.l2.go = "exit";
				NPChar.quest.meeting = "1"; // patch-6
				break;
			}			
			//< —Бремя гасконца
			if(NPChar.quest.meeting == "0")
			{
				
				dialog.text = "问候, " + GetAddress_Form(NPChar) + "。 我想我们之前没见过面。 我是"  + GetFullName(npchar) + " —港口主管。 ";
				Link.l1 = "你好, " + GetFullName(NPChar) + "。 我是" + GetFullName(PChar) + ", ‘" + PChar.ship.name + "’的船长。 ";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_portoffice")
				{
					dialog.text = "麦克阿瑟船长, 我总是提醒你 —没必要每次都来登记。 别担心。 ";
					link.l1 = "别说了, " + npchar.lastname + "先生, 我和其他人一样。 ";
					Link.l1.go = "node_2";
					break;
				}
				NPChar.quest.meeting = "1";
			}
			else
			{
				dialog.text = LinkRandPhrase("问候, " + GetAddress_Form(NPChar) + "。 你有什么事找我吗? ",
                                    "你好, " + GetFullName(Pchar) + "。 我看到你的船进入我们的港口, 就知道你会来见我。 ",
                                    "哦, " + GetFullName(Pchar) + "船长。 什么风把你吹到我这里来的? ");
				Link.l1 = "你好, " + GetFullName(NPChar) + "。 我想和你谈谈。 ";
			}
			Link.l1.go = "node_2";
		break;
		
		case "node_2":
			// Церковный генератор 1
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.AskPortMan") && PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony == NPChar.city)
			{
				dialog.text = "太好了。 我为你服务, " + GetFullName(PChar) + "。 ";
				if(!CheckAttribute(PChar, "GenQuest.ChurchQuest_1.CapFullInfo"))	// 获取完整信息
				{
					if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NoMoneyToPortMan"))
					{
						dialog.text = "那么, 钱怎么样了? 你至少有一千比索给我吗? ";
						if(sti(PChar.Money) >= 1000)
						{
							link.l1 = "是的, 我有" + GetSexPhrase(", ", "") + "。 正好一千比索。 现在, 给我信息! ";
							link.l1.go = "Church_GenQuest1_Node_FillFullInfo_3";
						}
						else
						{
							link.l1 = LinkRandPhrase("不, 还没有... ", "还没有... ", "还没有, 但很快就会带来... ");
							link.l1.go = "exit";
						}
					}
					else
					{
						link.l1 = "请允许我解释问题的核心。 我和我的老朋友, " + PChar.GenQuest.ChurchQuest_1.CapFullName + "船长, 刚好错过了几个小时, 我和他有紧急事务。 现在我得追上他, 但我" + GetSexPhrase(", ", "") + "不知道他的下落。 ";
						link.l1.go = "Church_GenQuest1_Node_FillFullInfo";
					}
				}
				else	// Полная инфа уже есть
				{
					link.l1 = "港口主管先生, 我需要一些关于" + PChar.GenQuest.ChurchQuest_1.CapFullName + "船长拥有的名为‘" + PChar.GenQuest.ChurchQuest_1.CapShipName + "’的船的信息。 ";
					if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NextColonyIsLast")) // 他在这个殖民地! 		
						link.l1.go = "Church_GenQuest1_Node_CapOnThisColony_1";
					else // Отправляет в рандомную колонию
						link.l1.go = "Church_GenQuest1_Node_FillInfoOfCapColony_1";
				}				
				break;
			}		
//-------------------------------------------//Jason, фрахт---------------------------------------------------
				if (CheckAttribute(PChar, "questTemp.WPU.Fraht.TargetPortmanID") && CheckAttribute(PChar, "questTemp.WPU.Fraht.LevelUp") && pchar.questTemp.WPU.Fraht.TargetPortmanID == npchar.id)
				{
					dialog.text = "太好了。 我为你服务, " + GetFullName(PChar) + "。 ";
					Link.l1 = "为你的殖民地运送的货物在我船的货舱里。 ";
					Link.l1.go = "Fraht_completeLevelUp";
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Fraht.TargetPortmanID") && pchar.questTemp.WPU.Fraht != "lost" && pchar.questTemp.WPU.Fraht.TargetPortmanID == npchar.id)
				{
					dialog.text = "太好了。 我为你服务, " + GetFullName(PChar) + "。 ";
					Link.l1 = "为你的殖民地运送的货物在我船的货舱里。 ";
					Link.l1.go = "Fraht_complete";
					break;
				}
			
				if (CheckAttribute(PChar, "questTemp.WPU.Fraht.TargetPortmanID") && pchar.questTemp.WPU.Fraht == "lost" && pchar.questTemp.WPU.Fraht.Nation == npchar.nation)
				{
					if (pchar.questTemp.WPU.Fraht.TargetPortmanID == npchar.id)
					{
						dialog.text = "哦, 你终于来了。 说实话, 我没指望你会回来。 我们已经请求当局将你列为通缉犯。 那么, 你有什么要说的? ";
						Link.l1 = "由于不可预见的情况, 我未能及时交付货物。 但我想以和平方式解决这场冲突。 我带来了你的货物, 希望我们能达成协议。 ";
						Link.l1.go = "Fraht_complete_bad";
					}
					else
					{
						dialog.text = "哦, 我知道你是谁。 你签了运送货物的合同, 却反而偷了它! 卫兵, 卫兵! ";
						Link.l1 = "啊! ";
						Link.l1.go = "exit";
						LAi_group_Attack(NPChar, Pchar);
					}
				}
// < —фрахт
//-------------------------------------------//Jason, 邮件---------------------------------------------------	
		
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.TargetPortmanID") && pchar.questTemp.WPU.Postcureer != "lost" && pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					dialog.text = "太好了。 我为你服务, " + GetFullName(PChar) + "。 ";
					Link.l1 = "我为你的殖民地送来了邮件。 ";
					Link.l1.go = "Postcureer_complete";
					break;
				}
			
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.TargetPortmanID") && pchar.questTemp.WPU.Postcureer == "lost" && pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					dialog.text = "哦, 你终于来了。 说实话, 我们都以为你死了... 好吧, 我想你只是个笨蛋, 不是死人, 这是件好事。 ";
					Link.l1 = "由于不可预见的情况, 我未能及时交付邮件。 但现在邮件在这里。 ";
					Link.l1.go = "Postcureer_complete_bad";
					break;
				}
			
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.fail") && pchar.questTemp.WPU.Postcureer.StartCity == npchar.city)
				{
					dialog.text = "发生了什么事? 你看起来像刚从鬼门关回来。 ";
					Link.l1 = "" + GetAddress_FormToNPC(NPChar) + ", 你警告我有危险是对的。 两个黑衣人就在港口管理局办公室门口袭击了我, ... 嗯, 他们把包裹抢走了。 ";
					Link.l1.go = "Postcureer_complete_fail";
					break;
				}
// < —почта
//-------------------------------------------//Jason, 护航---------------------------------------------------	
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_0") && pchar.questTemp.WPU.Escort.TargetPortmanID == npchar.id)
				{
					dialog.text = "太好了。 我为你服务, " + GetFullName(PChar) + "。 ";
					Link.l1 = "我是被" + XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen") + "的港口主管派来的。 我被要求护送一艘载有武器弹药的船。 这是我的文件。 ";
					Link.l1.go = "Escort_LUGo_0";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUpGo_0") && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "太好了。 我为你服务, " + GetFullName(PChar) + "。 ";
					Link.l1 = "我已经按约定护送了装有武器的船。 ";
					Link.l1.go = "Escort_LUGo_complete";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1WM") && pchar.questTemp.WPU.Escort == "current" && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "太好了。 我为你服务, " + GetFullName(PChar) + "。 ";
					Link.l1 = "我找到了失踪的船只, 并把它带到了你的港口。 船长应该已经向你报告过了。 ";
					Link.l1.go = "Escort_LU1WM_complete";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1VSP") && pchar.questTemp.WPU.Escort == "win" && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "太好了。 我为你服务, " + GetFullName(PChar) + "。 ";
					Link.l1 = "我找到了失踪的船只, 并把它带到了你的港口。 船长应该已经向你报告过了。 ";
					Link.l1.go = "Escort_LU1VSP_complete";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1VSP") && pchar.questTemp.WPU.Escort == "sink" && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "太好了。 我为你服务, " + GetFullName(PChar) + "。 ";
					Link.l1 = "我在" + XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID) + "岛的海岸发现了失踪的船只。 她的船长正在与压倒性的海盗力量进行一场不平等的战斗。 我尽我所能提供了帮助, 可惜徒劳无功: 该死的恶棍击沉了船。 那时我所能做的就是为她报仇。 ";
					Link.l1.go = "Escort_LU1VSP_completeSink";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1S") && pchar.questTemp.WPU.Escort == "win" && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "太好了。 我为你服务, " + GetFullName(PChar) + "。 ";
					Link.l1 = "我在" + XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID) + "岛的海岸找到了失踪的船只。 嗯, 实际上不是船, 而是大约五十名船员和船长。 他们现在安全了 —船员已经登上了我的船, 船长现在在你的镇上 —我想他已经拜访过你了。 ";
					Link.l1.go = "Escort_LU1S_complete";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_2") && pchar.questTemp.WPU.Escort == "win" && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "太好了。 我为你服务, " + GetFullName(PChar) + "。 ";
					Link.l1 = "我已经完成了你的任务。 袭击贸易护航队的海盗中队已被摧毁。 ";
					Link.l1.go = "Escort_LU2_complete";
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus") && pchar.questTemp.WPU.Escort.Bonus != "fail" && pchar.questTemp.WPU.Escort.TargetPortmanID == npchar.id)
				{
					dialog.text = "太好了。 我为你服务, " + GetFullName(PChar) + "。 ";
					Link.l1 = "我是护航船的船长。 我来报告我已将贸易船只带到港口。 ";
					Link.l1.go = "Escort_complete";
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus") && pchar.questTemp.WPU.Escort.Bonus == "fail" && pchar.questTemp.WPU.Escort.TargetPortmanID == npchar.id)
				{
					dialog.text = "太好了。 我为你服务, " + GetFullName(PChar) + "。 ";
					Link.l1 = "我是护航船的船长。 我被派去将两艘贸易船和货物带到港口, 但不幸的是, 两艘被护航的船在与敌人护航队的战斗中沉没了。 不过我还是设法交付了货物。 ";
					Link.l1.go = "Escort_fail";
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && pchar.questTemp.WPU.Escort.TargetPortmanID == npchar.id && !CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp"))
				{
					dialog.text = "太好了。 我为你服务, " + GetFullName(PChar) + "。 ";
					Link.l1 = "我是护航船的船长。 我来报告我已将贸易船只带到港口。 ";
					Link.l1.go = "Escort_complete";
					break;
				}
// < —эскорт
			if(startHeroType == 4 && NPChar.location == "SantaCatalina_portoffice" && NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = "1";
				dialog.text = "很高兴听到你这么说。 很多人在你这个位置会变得自负。 那么, 我和我的记录能为你做些什么? ";
			}
			else dialog.text = "太好了。 我为你服务, " + GetFullName(PChar) + "。 ";
			if (npchar.city != "Panama") // Captain Beltrop, 24.12.2020, запрет брать задания и ставить корабли в ПУ Панамы
			{
				Link.l2 = "你有什么我可以做的工作吗? 或者也许是一份合同? ";
				Link.l2.go = "Work_check"; //квесты
				Link.l3 = "我可以在这里停泊我的一艘船一段时间吗? ";
				Link.l3.go = "ShipStock_1";
			}
			if (sti(NPChar.Portman) > 0)
			{
                Link.l4 = "我想取回我的船。 ";
    			Link.l4.go = "ShipStockReturn_1";
			}
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l5 = "我来讨论财务业务。 ";
				link.l5.go = "LoanForAll";//(перессылка в кредитный генератор)	
			}
  			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
			{
				link.l7 = RandPhraseSimple("我是应某个人的要求来的。 他的名字是" + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + "总督。 ", 
					GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + "派我来你这里。 我应该来取些东西... ");
				link.l7.go = "IntelligenceForAll";
			}
			link.l6 = "我想了解更多关于在你港口管理局注册的船长的信息。 ";
			link.l6.go = "CapitainList";
			link.l61 = "你能分享一些关于独特的定制船只及其传奇船长的见解吗? ";
			link.l61.go = "UniqueShips";
			
			link.l8 = "我是为另一件事来的。 ";
			// Warship 26.07.09 Генер "Сгоревшее судно"
			if(CheckAttribute(NPChar, "Quest.BurntShip") && !CheckAttribute(NPChar, "Quest.BurntShip.LastQuestDate"))
			{
				if(CheckAttribute(NPChar, "Quest.BurntShip.TimeIsOver")) // Просрочено
				{
					link.l8.go = "BurntShip10";
				}
				else
				{
					if(CheckAttribute(NPChar, "Quest.BurntShip.TwoDaysWait"))
					{
						if(GetNpcQuestPastDayParam(NPChar, "Quest.BurntShip.TwoDaysWait") >= 2)
						{
							link.l8.go = "BurntShip17";
						}
						else
						{
							link.l8.go = "quests";
						}
					}
					else
					{
						link.l8.go = "BurntShip12";
					}
				}
			}
			else
			{
				link.l8.go = "quests";
			}
			if(CheckAttribute(pchar,"GenQuest.EncGirl"))
			{
				if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "portman_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
				{
					link.l9 = "你好, 我是应你儿子的邀请来的。 "; 
					link.l9.go = "EncGirl_4";
					pchar.quest.EncGirl_GetLoverFather.over = "yes";
				}	
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					if(pchar.GenQuest.EncGirl.Father == "portman_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
					{
						link.l9 = "这是关于你女儿的... ";
						link.l9.go = "EncGirl_1";
					}
				}
			}
			if (CheckCharacterItem(pchar, "CaptainBook"))
			{
				if(pchar.questTemp.different == "free")
				{
					link.l10 = "我偶然发现了这个船文件包裹。 ";
					link.l10.go = "ShipLetters_out1";				
				}
				else
				{
					if(pchar.questTemp.different.GiveShipLetters.city == npchar.city)
					{
						link.l10 = "我偶然发现了这个船文件包裹, 一定是有人弄丢了。 ";
						if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakPortman"))
						{
							link.l10.go = "ShipLetters_Portman1_1";						
						}
						else
						{
							link.l10.go = "ShipLetters_Portman2";
						}
					}
				}		
			}												
			Link.l15 = "谢谢你。 再见。 ";
			Link.l15.go = "exit";
		break;

		case "Church_GenQuest1_Node_FillFullInfo":
			dialog.text = "你的问题很容易解决。 去见航海服务官员, 他可以为你提供关于你朋友船只航线的所有信息。 ";
			link.l1 = "不幸的是, 没那么容易。 我的朋友在你的港口因为宗教原因重命名了他的船... ";
			link.l1.go = "Church_GenQuest1_Node_FillFullInfo_2";
		break;
			
		case "Church_GenQuest1_Node_FillFullInfo_2":
			dialog.text = "我明白了。 这让事情变得有点复杂。 我需要翻查船舶登记册的记录, 这需要一些时间。 而时间就是金钱, 你可能知道。 ";
			if(sti(pchar.money) >= 1000)
			{
				link.l1 = "我完全理解, " + GetFullName(NPChar) + "先生, 我准备充分评估你的时间... 比如说, 一千比索。 ";
				link.l1.go = "Church_GenQuest1_Node_FillFullInfo_3";
			}
			else
			{
				DeleteAttribute(pchar, "GenQuest.ChurchQuest_1.CurPortManColony"); // 可以再问。 
				link.l1 = "太糟糕了, 因为我现在身上没有钱... 我稍后再来... ";
				link.l1.go = "exit";
			}
		break;
			
		case "Church_GenQuest1_Node_FillFullInfo_3":
			sColony = GetColonyExpect2Colonies(NPChar.city, PChar.GenQuest.ChurchQuest_1.QuestTown);
			PChar.GenQuest.ChurchQuest_1.CapGoToColony = sColony;
			if(CheckAttribute(pchar, "GenQuest.ChurchQuest_1.NoMoneyToPortMan"))
			{
				dialog.text = "完美! 现在让我看看... 稍等... 这里... 对。 船只的重命名已经登记, 这艘从现在起被称为‘" + PChar.GenQuest.ChurchQuest_1.CapShipName + "’。 由" + PChar.GenQuest.ChurchQuest_1.CapFullName + "船长指挥的船, 今天已经起航前往" + XI_ConvertString("Colony" + sColony + "Gen") + "。 ";
				DeleteAttribute(pchar, "GenQuest.ChurchQuest_1.NoMoneyToPortMan");
			}
			else
				dialog.text = "哦! 你真的明白我是个非常忙碌的人, 我很高兴你能理解! 现在让我看看... 稍等... 这里... 对。 船只的重命名已经登记, 这艘从现在起被称为‘" + PChar.GenQuest.ChurchQuest_1.CapShipName + "’。 由" + PChar.GenQuest.ChurchQuest_1.CapFullName + "船长指挥的船, 今天已经起航前往" + XI_ConvertString("Colony" + sColony + "Gen") + "。 ";			
				link.l1 = "谢谢你, 先生, 你帮了我大忙。 ";
				link.l1.go = "Church_GenQuest1_Node_FillFullInfo_4";
				AddMoneyToCharacter(pchar, -1000);
		break;
			
		case "Church_GenQuest1_Node_FillFullInfo_4":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "4");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.CapGoToColony + "Gen"));
			AddQuestUserData(sQuestTitle, "sShipName", PChar.GenQuest.ChurchQuest_1.CapShipName);	
			PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = PChar.GenQuest.ChurchQuest_1.CapGoToColony;
			PChar.GenQuest.ChurchQuest_1.CapFullInfo = true;
		break;
			
		case "Church_GenQuest1_Node_FillInfoOfCapColony_1":
			dialog.text = "你具体想知道什么? ";
			link.l1 = "你能告诉我那艘船长的船是否访问过你的港口吗? ";
			link.l1.go = "Church_GenQuest1_Node_FillInfoOfCapColony_2";
		break;
						
		case "Church_GenQuest1_Node_FillInfoOfCapColony_2":
			PChar.GenQuest.ChurchQuest_1.CapGoToColony = GetColonyExpect2Colonies(NPChar.city, PChar.GenQuest.ChurchQuest_1.QuestTown);
			dialog.text = "嗯... 我可以知道你为什么问吗? ";
			link.l1 = "我和他有生意。 但如果他没到过你的港口, 或者你不知道... ";
			link.l1.go = "Church_GenQuest1_Node_FillInfoOfCapColony_3";
		break;
			
		case "Church_GenQuest1_Node_FillInfoOfCapColony_3":
			dialog.text = "他来过。 但感谢所有圣人, 就在今天早上, 他离开了我们, 前往" + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.CapGoToColony + "Acc") + "。 我真诚地为任何需要与他打交道的人感到遗憾。 ";
			link.l1 = "既然如此, 祝我好运 —谢谢你的帮助。 ";
			link.l1.go = "Church_GenQuest1_Node_FillInfoOfCapColony_4";
		break;
			
		case "Church_GenQuest1_Node_FillInfoOfCapColony_4":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "5");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.CapGoToColony + "Voc")); // belamour gen
			AddQuestUserData(sQuestTitle, "sName", PChar.GenQuest.ChurchQuest_1.CapFullName);
			PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = PChar.GenQuest.ChurchQuest_1.CapGoToColony; // 在船长前往的殖民地询问港口主管。 
			if(rand(2) == 1) 
			{
				Log_TestInfo("下一个殖民地是最后一个");
				PChar.GenQuest.ChurchQuest_1.NextColonyIsLast = true; // 标志 - 下一个殖民地将是最后一个
			}
		break;
			
		case "Church_GenQuest1_Node_CapOnThisColony_1":
			dialog.text = "你想知道什么, " + GetSexPhrase("先生", "小姐") + " " + GetFullName(PChar) + "? ";
			link.l1 = "你能告诉我这位船长是否到过你的港口吗? ";
			link.l1.go = "Church_GenQuest1_Node_CapOnThisColony_2";
		break;
			
		case "Church_GenQuest1_Node_CapOnThisColony_2":
			dialog.text = "嗯, 他当然来过。 我必须说, 我正急切地等待着他最终离开这个长期受苦的港口的那个幸福时刻。 ";
			link.l1 = "你是说他的船还在这里? ";
			link.l1.go = "Church_GenQuest1_Node_CapOnThisColony_3";
		break;
			
		case "Church_GenQuest1_Node_CapOnThisColony_3":
			dialog.text = "是的, 尊敬的" + GetSexPhrase("先生", "女士") + "。 整个港口, 从最低级的装卸工到领航服务主管, 都在祈祷他迅速离开。 他的船刚刚离开干船坞, 在那里它被迅速修复, 但那时她勇敢的船长已经与每个木匠闹翻, 并拒绝了三批为船身挑选的木板。 但明天我们最仁慈和全知的主将把我们从那个... 从那个瘟疫, 从那个眼中钉中拯救出来! ";
			link.l1 = "现在, 冷静点, " + NPChar.Name + "先生, 记住有人的日子会更难过。 你已经通过了这个考验, 而我还没有见到你的那位船长。 现在, 如果你们能原谅我... ";
			link.l1.go = "Church_GenQuest1_Node_CapOnThisColony_4";
		break;
			
		case "Church_GenQuest1_Node_CapOnThisColony_4":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "6");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
//			PChar.GenQuest.ChurchQuest_1.NeedToDialogWithSailors = true; // Спрашиваем моряков
			PChar.GenQuest.ChurchQuest_1.NeedToDialogWithCap = true; // Говорим с капитаном
//			SetFunctionLocationCondition("Church_GenQuest1_ChangeCapitanLocation", "Deck_Near_Ship", true);
			PChar.GenQuest.ChurchQuest_1.CurPortManColony = NPChar.city;
			Group_SetAddress("ChurchGenQuest1_CapGroup", colonies[FindColony(NPChar.City)].Island, "IslandShips1", "Ship_1"); // Ставим кэпа в порту колонии
			Characters[GetCharacterIndex("ChurchGenQuest1_Cap")].Nation = sti(NPChar.Nation); // Сменим нацию, чтоб вражды не было
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.AskPortMan"); // Больше не спрашиваем
//			if(rand(1) == 0) PChar.GenQuest.ChurchQuest_1.CapWaitOnTavern = true;
			sld = CharacterFromID("ChurchGenQuest1_Cap");
			sld.DeckDialogNode = "ChurchGenQuest_1_DeckDialog_1";
		break;
						
		case "ShipLetters_out1":
			dialog.text = "让我看看! 是的, 确实, 在我的文件中, 这一套被标记为无效。 你能抽出时间来看我并把这些文件交给我, 真是太好了。 一路顺风, 船长! ";
			link.l1 = "谢谢! ";
			link.l1.go = "exit";
			TakeItemFromCharacter(pchar, "CaptainBook"); 			
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; // 移除计时器 
			AddQuestRecord("GiveShipLetters", "10");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit(); 
		break;
				
		case "ShipLetters_Portman1_1":
			pchar.questTemp.different.GiveShipLetters.speakPortman = true;
			s1 = "让我看看! 是的, 这艘船和它的船长都在我的文件中登记了。 ";
			s1 = s1 + "你的认真负责, 船长, 为你自己增光! 当然, 你的努力不能没有回报。  ";
			dialog.text = s1 + "你觉得" + sti(pchar.questTemp.different.GiveShipLetters.price1) + "比索的金额合适吗? ";
			link.l1 = "当然不合适! ";
			link.l1.go = "exit";
			link.l2 = "嗯, 一笔 modest 的金额, 但话说回来, 这也不是什么大事。 是的, 我接受你的提议, "  + npchar.name+ "。 ";
			link.l2.go = "ShipLetters_Portman1_2";
		break;
		
		case "ShipLetters_Portman1_2" :
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price1)); 			
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; // 移除计时器 
			AddQuestRecord("GiveShipLetters", "5");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit(); 
		break;
		
		case "ShipLetters_Portman2":
			dialog.text = "你会接受我的提议吗? ";
			link.l1 = "当然不! ";
			link.l1.go = "exit";
			link.l2 = "也许吧。 尽管我确信这些文件价值更高。 ";
			link.l2.go = "ShipLetters_Portman2_1";
		break;
		
		case "ShipLetters_Portman2_1":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price1)); 			
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; // 移除计时器 
			AddQuestRecord("GiveShipLetters", "6");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit(); 		
		break;

		case "EncGirl_1":
			dialog.text = "我洗耳恭听。 ";
			link.l1 = "我把你逃跑的人带来了。 ";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "哦, 船长, 太感谢你了! 她怎么样? 她受伤了吗? 她为什么逃跑? 为什么? \n难道她不明白吗? 新郎是个富有而重要的人! 年轻人是天真愚蠢的... 甚至是残忍的。 记住这一点! ";
			link.l1 = "嗯, 你是她的父亲, 最终决定在你, 但我不会急于举行婚礼... ";
			link.l1.go = "EncGirl_3";
		break;
		
		case "EncGirl_3":
			dialog.text = "你知道什么? 你有自己的孩子吗? 没有? 等你有了孩子, 再来见我, 然后我们再谈。 \n我答应过任何把她带回给家人的人一笔奖励。 ";
			link.l1 = "谢谢。 你应该看好她。 我有一种预感, 她不会就此罢休。 ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;
		
		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "哦, 你就是那个" + GetSexPhrase("带来的船长", "带来的年轻女士") + "我那浪子儿子和一个年轻新娘的人? ";
				link.l1 = "是的, 我帮助他们逃跑了。 ";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "哦, 来啦, 恩人。 可能在等奖励吧? ";
				link.l1 = "嗯, 没有奖励我也很好, 你的感激之情就够了。 ";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "我非常感谢你没有在我孩子危难时抛弃他, 并帮助他摆脱了那个微妙的处境。 请允许我感谢你, 并请接受这笔 modest 的款项和我个人的礼物。 ";
			link.l1 = "谢谢。 帮助这对年轻夫妇是我的荣幸。 ";
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = "感谢? 什么感谢? ! 那个笨蛋已经闲逛了半年没有工作 —看看他, 他有足够的时间去谈恋爱! 我在他这个年纪时已经在经营自己的生意了! 呸! 总督有一个适婚的女儿 —而那个傻瓜却带了一个没有亲戚的荡妇到我家, 还敢要求我的祝福! ";
			link.l1 = "嗯... 显然, 你不相信真挚的感情? ";
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
			dialog.text = "什么感情? 你在说什么感情? 感情... 你这个年纪怎么能如此轻率? ! 你纵容年轻人的任性, 扮演皮条客的角色, 真为你感到羞耻! 你不仅从家里带走了一个女孩, 还毁了我那新手的生活。 不会有感谢给你。 再见。 ";
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
		
		case "node_4":
			//--> 港口主管的迷你任务生成
			if (rand(2) < 2 && pchar.questTemp.different == "free" && GetNpcQuestPastDayWOInit(npchar, "quest.meeting") > 7)
			{
				dialog.text = LinkRandPhrase("是的, 该死的! 我有工作给你! ", 
					"哈! 你来得正好! 我有个问题要解决。 ", 
					"当然! 当然我有工作给你! 你知道, 我最近问题太多了... ");
				link.l1 = "那么请说重点, " + GetAddress_FormToNPC(NPChar) + "。 ";
				link.l1.go = "PortmanQuest";
				SaveCurrentNpcQuestDateParam(npchar, "quest.meeting");
				break;
			}
			
			// Warship 25.07.09 生成器 "燃烧的船"
			if(hrand(4) == 2 && !CheckAttribute(NPChar, "Quest.BurntShip"))
			{
				dialog.text = "上帝! " + GetFullName(PChar) + "船长, 你来得正好! 发生了这样的不幸, 这样的灾难... 船在锚地被港口管理局看管时烧毁了! 由于安全措施的疏忽, 船燃烧了... 燃烧到了吃水线... \n" + "主啊, 我做了什么要受这样的惩罚? 我做了这么多年的忠实仆人... ";
				link.l1 = "那么, 有什么大不了的? 一艘船烧毁了? 保险合同是干什么用的? 或者你为了省钱决定不投保, 现在后悔了? ";
				link.l1.go = "BurntShip4";
				link.l2 = "造船厂比我更能帮助你。 几个月后他们会修复旧船, 甚至建造新船。 抱歉, 我不是造船师... ";
				link.l2.go = "BurntShip2";
				break;
			}
			//< —港口主管的迷你任务生成

			dialog.text = "总督关心他的公民的福祉, 因此他总是有一些工作要提供。 酒馆里可能有商人需要帮助, 商店也需要货运船长。 ";
			Link.l1 = "我还有一个问题。 ";
			Link.l1.go = "node_2";
			Link.l2 = "谢谢你。 再见。 ";
			Link.l2.go = "exit";
		break;

///Jason-----------------------новые генераторы накопительного типа для портмана----------------------------
		int iTime, idaysQty, iGoods, iGoodsQty, amount;
		case "Work_check"://фейс-контроль - общая проверка профпригодности ГГ и выбор задания
			//--> проверка миниквестов начальника порта。 
			if (npchar.quest == "PortmansJornal") //взят квест на судовой журнал
			{
				dialog.text = "你应该找到" + npchar.quest.PortmansJornal.capName + "船长, 并把他的航海日志还给他。 你成功了吗? ";
				link.l1 = "不, 还没有... ";
				link.l1.go = "PortmanQuest_NF";
				break;
			}
			if (npchar.quest == "PortmansSeekShip" || npchar.quest == "SeekShip_sink") // 接受了寻找被盗船只的任务
			{
				dialog.text = "你承诺寻找一艘被盗的" + GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName)) + "‘" + npchar.quest.PortmansSeekShip.shipName + "’。 在你完成之前, 不会有其他任务给你。 ";
				link.l1 = "我会继续我的搜索, 等着吧。 ";
				link.l1.go = "exit";
				link.l2 = "我想放弃这个任务。 ";
				link.l2.go = "SeekShip_break";
				break;
			}
			if (npchar.quest == "SeekShip_success") // 被盗船只被登船夺取
			{
				dialog.text = "你答应我寻找被盗的" + GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName)) + "‘" + npchar.quest.PortmansSeekShip.shipName + "’。 你做到了吗? ";
				bool bOk = false;
				for (i=0; i<=COMPANION_MAX; i++)
				{
					cn = GetCompanionIndex(pchar, i);
					if(cn != -1)
					{
						sld = &characters[cn];
						if (sld.ship.name == npchar.quest.PortmansSeekShip.shipName && 
							RealShips[sti(sld.ship.type)].BaseName == npchar.quest.PortmansSeekShip.shipTapeName &&
							RealShips[sti(sld.Ship.Type)].basetype == npchar.quest.PortmansSeekShip.shipTape)
						{
							if (i == 0)
							{	// 如果需要的船 - 在玩家那里
								sld.Ship.Type = GenerateShip(SHIP_TARTANE, true);
								SetBaseShipData(sld);
								SetCrewQuantityFull(sld);
							}
							else
							{
								RemoveCharacterCompanion(pchar, sld);
								AddPassenger(pchar, sld, false);
							}
							bOk = true;
						}
					}
				}				
				if (bOk)
				{
					link.l1 = "是的, 我找到了, 它现在在港口。 你可以拿走。 ";
					link.l1.go = "SeekShip_good";
				}
				else
				{
					link.l1 = "我会继续我的搜索, 等着吧。 ";
					link.l1.go = "exit";
				}
				link.l2 = "我想放弃这个任务。 ";
				link.l2.go = "SeekShip_break";
				break;
			}
			//< —проверка миниквестов начальника порта。 
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
			{
				if (!CheckAttribute(npchar, "work_date") || GetNpcQuestPastDayParam(npchar, "work_date") >= 2)//проверка повтора
				{
					if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)//проверка межнациональных отношений
					{
						dialog.text = RandPhraseSimple("那些悬挂" + NationNameGenitive(sti(pchar.nation)) + "旗帜航行的人没有工作可做! 立刻离开我的办公室! ", "我不会与" + NationNameAblative(sti(pchar.nation)) + "合作。 走开! ");
						link.l1 = RandPhraseSimple("好吧, 如你所愿...", "好吧, 随你喜欢...");
						link.l1.go = "exit";
						break;
					}
					if (isBadReputation(pchar,40)) // 检查主角与召唤者的信任度 belamour legendary edition
					{
						dialog.text = "你的声誉无法让我产生信任。 我不打算与你合作。 再会。 ";
						link.l1 = "什么! 全是谎言。 ";
						link.l1.go = "exit";
						break;
					}
					if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 5)//领导力不足时不给予
					{
						dialog.text = "我不想冒犯你, 船长, 但是... 恐怕你无法完成我的任务 - 你只是缺乏经验。 我不能和你签订合同。 ";
						link.l1 = "我明白了。 好吧, 如你所说。 ";
						link.l1.go = "exit";
						break;
					}
					dialog.Text = "嗯... 好吧, 这取决于你感兴趣的工作。 ";
					link.l1 = "我可以提议将我的船租给你用于运输货物。 ";
					Link.l1.go = "Fraht_begin";		//货运
					link.l2 = "我想通过护送商人或递送邮件来赚外快。 ";
					Link.l2.go = "Check_other";		//邮件递送。 护送
					Link.l3 = "好吧, 也许你可以提供一些什么? ";
					Link.l3.go = "node_4"; 			//船只租赁。 被劫持的船。 烧毁的船
				}
				else
				{
					dialog.Text = "今天没有剩余的工作了。 改天再来吧。 ";
					link.l1 = "好的。 ";
					Link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "我在港口没看到你的船。 离开港口然后再来见我 - 我们会尝试为你找些事情做。 ";
				link.l1 = "好的, 我会那么做的。 ";
				link.l1.go = "exit";
			}
		break;
	
		case "Check_other"://выбор между почтовым курьером, эскортом и ничем
		SaveCurrentNpcQuestDateParam(npchar, "work_date"); // mitrokosta безусловно сохраняем
		int nTask = 0;
		string tasks[10]; // mitrokosta сделал выбор задания расширяемым на тот случай если задания добавятся
		if (sti(RealShips[sti(pchar.Ship.Type)].Spec) == SHIP_SPEC_RAIDER) {
			tasks[nTask] = "cureer";
			nTask++;
		}
		if (GetCompanionQuantity(pchar) < 3 && sti(RealShips[sti(pchar.Ship.Type)].Class) >= 4 && or(sti(RealShips[sti(pchar.Ship.Type)].Spec) == SHIP_SPEC_WAR, sti(RealShips[sti(pchar.Ship.Type)].Spec) == SHIP_SPEC_RAIDER)) {
			tasks[nTask] = "escort";
			nTask++;
		}
		if (nTask > 0 && hrand(5) > 1) {
			string sTask = tasks[hrand(nTask - 1)];
			switch (sTask) {
				case "cureer":
					if (pchar.questTemp.WPU.Postcureer == "begin" || pchar.questTemp.WPU.Postcureer == "late" || pchar.questTemp.WPU.Postcureer == "lost" || pchar.questTemp.WPU.Postcureer == "fail" || CheckAttribute(pchar, "questTemp.WPU.Postcureer.LevelUp")) { // 如果已占用
						dialog.text = "不幸的是, 我无法为你提供此类工作。 过几天再来吧。 ";
						link.l1 = "好的, 我会那么做的。 ";
						link.l1.go = "exit";
					} else { // если не заняты
						if (sti(pchar.questTemp.WPU.Postcureer.count) > 3 && hrand(1) == 1) { //如果 2 级
							dialog.text = "所以... 据我所知, 你已经接过几份信使工作并且相当成功。 你或许能处理我即将交给你的任务。 ";
							link.l1 = "我洗耳恭听, " + GetAddress_FormToNPC(NPChar) + "。 ";
							link.l1.go = "Postcureer_LevelUp";
						} else { // первый уровень
							dialog.text = "我看你有一艘快船。 我可以给你提供一份信使工作 - 递送邮件和商业文件。 ";
							link.l1 = "这很有趣。 我同意。 我需要去哪里? ";
							link.l1.go = "Postcureer";
							link.l2 = "谢谢你, 但这不是我喜欢的工作。 ";
							link.l2.go = "exit";
						}
					}
				break;

				case "escort":
					if (pchar.questTemp.WPU.Escort == "begin" || pchar.questTemp.WPU.Escort == "late" || pchar.questTemp.WPU.Escort == "win" || CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp")) { // если заняты
						dialog.text = "不幸的是, 我无法为你提供此类工作。 过几天再来吧。 ";
						link.l1 = "好的, 我会那么做的。 ";
						link.l1.go = "exit";
					} else { // если не заняты
						if (sti(pchar.questTemp.WPU.Escort.count) > 3 && hrand(1) == 1) { // 2 级
							dialog.text = "你已经成功护送过几次商船了。 我想我有一个适合你的任务。 ";
							link.l1 = "我洗耳恭听。 ";
							link.l1.go = "Escort_LevelUp";
						} else { // 1 уровень
							if (sti(RealShips[sti(pchar.Ship.Type)].BaseType) == SHIP_GALEON_H && 2500 - makeint(GetCharacterFreeSpace(pchar, GOOD_RUM)) < 0 && !CheckAttribute(pchar, "questTemp.WPU.Fraht.TargetPortmanID")) { // 如果在 TG
								dialog.text = "我正好有个适合你的工作。 港口有两艘商船本应该已经上路了。 问题是它们的护航船受损了, 还在等待必要的维修, 所以短期内无法出发。 \n碰巧你的船非常适合这项工作 - 另外我还得在你的船舱里存放额外的货物。 当然, 报酬会是双倍的 - 既包括货运也包括护送。 ";
								link.l1 = "多么有趣的提议! 我接受! ";
								link.l1.go = "escort_bonus";
								link.l2 = "谢谢你, 但这不是我喜欢的工作。 ";
								link.l2.go = "exit";
							} else { // просто эскорт
								dialog.text = "我正好有个适合你的工作。 目前有两艘商船在我们港口外停泊 - 它们需要护航。 我提议你将这些船护送到目的地。 你愿意吗? ";
								link.l1 = "有趣的提议! 我接受! ";
								link.l1.go = "escort";
								link.l2 = "谢谢你, 但这不是我喜欢的工作。 ";
								link.l2.go = "exit";
							}
						}
					}
				break;
			}
			break;
		}
		//ничего не подошло
		dialog.text = "不幸的是, 我无法为你提供此类工作。 过几天再来吧。 ";
		link.l1 = "好的, 我会那么做的。 ";
		link.l1.go = "exit";
		break;

///--> ------фрахт со свободным выбором пункта назначения, оплаты и вида груза из предложенного списка---------

		case "Fraht_begin":
			if (hrand(4) < 4)
			{
				if (pchar.questTemp.WPU.Fraht == "begin" || pchar.questTemp.WPU.Fraht == "late" || pchar.questTemp.WPU.Fraht == "lost" || CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus"))//проверка на занятость
				{
					dialog.Text = "但我听说你的船已经被租用了。 我不能再给你任何货运任务。 履行你已经承担的承诺。 ";
					link.l1 = "是的, 你可能是对的。 ";
					Link.l1.go = "exit";
					break;
				}
				if (1500 - makeint(GetCharacterFreeSpace(pchar, GOOD_RUM)) > 0)//мало места - не даем
				{
					dialog.text = "你的船舱空间太少了。 我需要更宽敞的船来运货。 我建议你去商店看看 - 当地商人经常租用船只运送小批量货物。 ";
					link.l1 = "我明白了。 好吧, 如你所说。 ";
					link.l1.go = "exit";
					break;
				}
				if (pchar.questTemp.WPU.Fraht.count > 3 && rand(1) == 0)
				{
					dialog.text = "我目前没有合适的。 但你已经完成了几次成功的运送。 我有一个特定的工作想专门交给你。 ";
					link.l1 = "我在听。 什么样的工作? ";
					link.l1.go = "Fraht_LevelUp";
					break;
				}
				dialog.Text = "好吧, 我可以给你提供几个租赁机会。 ";
				link.l1 = "那么, 让我看看...";
				Link.l1.go = "Fraht_choise";
			}
			else
			{
				dialog.Text = "今天没有剩余的货运任务了。 改天再来吧。 ";
				link.l1 = "哦, 好吧。 ";
				Link.l1.go = "exit";
			}
		break;
	
		int iFrahtGoods1, iFrahtGoods2, iFrahtGoods3, iFrahtGoods;
		int iFrahtGoodsQty1, iFrahtGoodsQty2, iFrahtGoodsQty3;
		case "Fraht_choise":
			//выбираем города
			pchar.questTemp.WPU.Fraht.City1 = findCurrentCity1(npchar);
			pchar.questTemp.WPU.Fraht.City2 = findCurrentCity2(npchar);
			pchar.questTemp.WPU.Fraht.City3 = findCurrentCity3(npchar);
			//выбираем товары
			iFrahtGoods1 = hrand(GOOD_PAPRIKA);
			iFrahtGoods2 = hrand(GOOD_PAPRIKA-3);
			iFrahtGoods3 = hrand(GOOD_PAPRIKA-7);
			pchar.questTemp.WPU.Fraht.Goods1 = iFrahtGoods1;
			pchar.questTemp.WPU.Fraht.Goods2 = iFrahtGoods2;
			pchar.questTemp.WPU.Fraht.Goods3 = iFrahtGoods3;
			//определим количество
			iFrahtGoodsQty1 = makeint(GetCharacterFreeSpace(pchar, iFrahtGoods1))/(1+frand(0.5));
			iFrahtGoodsQty2 = makeint(GetCharacterFreeSpace(pchar, iFrahtGoods2))/(1+frand(0.5));
			iFrahtGoodsQty3 = makeint(GetCharacterFreeSpace(pchar, iFrahtGoods3))/(1+frand(0.5));
			if (sti(iFrahtGoodsQty1) > 10000) iFrahtGoodsQty1 = 10000 + rand(500);
			if (sti(iFrahtGoodsQty2) > 10000) iFrahtGoodsQty2 = 10000 + rand(500);
			if (sti(iFrahtGoodsQty3) > 10000) iFrahtGoodsQty3 = 10000 + rand(500);
			pchar.questTemp.WPU.Fraht.GoodsQty1 = iFrahtGoodsQty1;
			pchar.questTemp.WPU.Fraht.GoodsQty2 = iFrahtGoodsQty2;
			pchar.questTemp.WPU.Fraht.GoodsQty3 = iFrahtGoodsQty3;
			pchar.questTemp.WPU.Fraht.StartCity = npchar.city;//город квестодателя
			pchar.questTemp.WPU.Fraht.Chance = rand(4);//форс-мажор
			//определим сроки с учётом рандома
			int daysQty1 = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Fraht.StartCity), GetArealByCityName(pchar.questTemp.WPU.Fraht.City1));
			int daysQty2 = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Fraht.StartCity), GetArealByCityName(pchar.questTemp.WPU.Fraht.City2));
			int daysQty3 = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Fraht.StartCity), GetArealByCityName(pchar.questTemp.WPU.Fraht.City3));
			pchar.questTemp.WPU.Fraht.DaysQty1 = makeint(sti(daysQty1)*(frand(1.3)+0.7));
			pchar.questTemp.WPU.Fraht.DaysQty2 = makeint(sti(daysQty2)*(frand(1.3)+0.7));
			pchar.questTemp.WPU.Fraht.DaysQty3 = makeint(sti(daysQty3)*(frand(1.3)+0.7));
			//установим цену исходя из объёма груза, дальности и сроков
			pchar.questTemp.WPU.Fraht.Money1 = (makeint((sti(iFrahtGoodsQty1) * sti(Goods[iFrahtGoods1].Weight) / sti(Goods[iFrahtGoods1].Units))))*(sti(daysQty1)*2)*sti(daysQty1)/sti(pchar.questTemp.WPU.Fraht.DaysQty1);
			pchar.questTemp.WPU.Fraht.Money2 = (makeint((sti(iFrahtGoodsQty2) * sti(Goods[iFrahtGoods2].Weight) / sti(Goods[iFrahtGoods2].Units))))*(sti(daysQty2)*2)*sti(daysQty2)/sti(pchar.questTemp.WPU.Fraht.DaysQty2);
			pchar.questTemp.WPU.Fraht.Money3 = (makeint((sti(iFrahtGoodsQty3) * sti(Goods[iFrahtGoods3].Weight) / sti(Goods[iFrahtGoods3].Units))))*(sti(daysQty3)*2)*sti(daysQty3)/sti(pchar.questTemp.WPU.Fraht.DaysQty3);
			if (hrand(5) < 4)//три варианта
			{
				dialog.text = "有以下可用选项: \n" +
					"货物" + GetGoodsNameAlt(iFrahtGoods1)+ "数量" + FindRussianQtyString(iFrahtGoodsQty1) + "到" + XI_ConvertString("Colony" + pchar.questTemp.WPU.Fraht.City1) + "镇, " +  FindRussianDaysString(pchar.questTemp.WPU.Fraht.DaysQty1) + "内。 报酬 - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money1)) + "\n货物" + GetGoodsNameAlt(iFrahtGoods2)+ "数量" + FindRussianQtyString(iFrahtGoodsQty2) + "到" + XI_ConvertString("Colony" + pchar.questTemp.WPU.Fraht.City2) + "镇, " +  FindRussianDaysString(pchar.questTemp.WPU.Fraht.DaysQty2) + "内。 报酬 - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money2)) + "\n货物" + GetGoodsNameAlt(iFrahtGoods3)+ "数量" + FindRussianQtyString(iFrahtGoodsQty3) + "到" + XI_ConvertString("Colony" + pchar.questTemp.WPU.Fraht.City3) + "镇, " +  FindRussianDaysString(pchar.questTemp.WPU.Fraht.DaysQty3) + "内。 报酬 - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money3)) + "\n你选择什么? ";
				Link.l1 = "我选择第一个选项 - 租用船只将" + GetGoodsNameAlt(iFrahtGoods1)+ "运到" + XI_ConvertString("Colony" + pchar.questTemp.WPU.Fraht.City1) + "镇。 ";
				Link.l1.go = "Fraht_Choise_1";
				Link.l2 = "我选择第二个选项 - 租用船只将" + GetGoodsNameAlt(iFrahtGoods2)+ "运到" + XI_ConvertString("Colony" + pchar.questTemp.WPU.Fraht.City2) + "镇。 ";
				Link.l2.go = "Fraht_Choise_2";
				Link.l3 = "我选择第三个选项 - 租用船只将" + GetGoodsNameAlt(iFrahtGoods3)+ "运到" + XI_ConvertString("Colony" + pchar.questTemp.WPU.Fraht.City3) + "镇。 ";
				Link.l3.go = "Fraht_Choise_3";
			}
			else //два варианта
			{
				dialog.text = "有以下可用选项: \n" +
					"货物" + GetGoodsNameAlt(iFrahtGoods1)+ "数量" + FindRussianQtyString(iFrahtGoodsQty1) + "到" + XI_ConvertString("Colony" + pchar.questTemp.WPU.Fraht.City1) + "镇, " +  FindRussianDaysString(pchar.questTemp.WPU.Fraht.DaysQty1) + "内。 报酬 - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money1)) + "\n货物" + GetGoodsNameAlt(iFrahtGoods2)+ "数量" + FindRussianQtyString(iFrahtGoodsQty2) + "到" + XI_ConvertString("Colony" + pchar.questTemp.WPU.Fraht.City2) + "镇, " +  FindRussianDaysString(pchar.questTemp.WPU.Fraht.DaysQty2) + "内。 报酬 - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money2)) + "\n你选择什么? ";
				Link.l1 = "我选择第一个选项 - 租用船只将" + GetGoodsNameAlt(iFrahtGoods1)+ "运到" + XI_ConvertString("Colony" + pchar.questTemp.WPU.Fraht.City1) + "镇。 ";
				Link.l1.go = "Fraht_Choise_1";
				Link.l2 = "我选择第二个选项 - 租用船只将" + GetGoodsNameAlt(iFrahtGoods2)+ "运到" + XI_ConvertString("Colony" + pchar.questTemp.WPU.Fraht.City2) + "镇。 ";
				Link.l2.go = "Fraht_Choise_2";
			}
			Link.l4 = "不幸的是, 没有适合我的。 ";
			Link.l4.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
		break;
	
		case "Fraht_Choise_1":
			dialog.text = "好的, 太棒了! 我会处理必要的文件, 你可以准备好你的船装货了。 ";
			link.l1 = "我会尽力的! ";
			link.l1.go = "Fraht_Forcemajor";
			AddCharacterGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods1), sti(pchar.questTemp.WPU.Fraht.GoodsQty1));
			iFrahtGoods1 = pchar.questTemp.WPU.Fraht.Goods1;
			ReOpenQuestHeader("Fraht");
			AddQuestRecord("Fraht", "1");
			AddQuestUserData("Fraht", "sGoods", GetGoodsNameAlt(iFrahtGoods1));
			AddQuestUserData("Fraht", "sGoodQty", FindRussianQtyString(sti(pchar.questTemp.WPU.Fraht.GoodsQty1)));
			AddQuestUserData("Fraht", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Fraht.DaysQty1)));
			AddQuestUserData("Fraht", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money1)));
			AddQuestUserData("Fraht", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.StartCity+"Gen"));
			AddQuestUserData("Fraht", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City1+"Gen"));
			SetFunctionTimerCondition("FrahtTime_Over", 0, 0, sti(pchar.questTemp.WPU.Fraht.DaysQty1), false);
			pchar.questTemp.WPU.Fraht.TargetPortmanID = pchar.questTemp.WPU.Fraht.City1+"_portman";
			pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iFrahtGoods1].Cost);//цена единицы товара
			pchar.questTemp.WPU.Fraht.GoodsAverigeCost = sti(Goods[iFrahtGoods1].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty1);//средняя стоимость товара
			pchar.questTemp.WPU.Fraht.Goods = sti(pchar.questTemp.WPU.Fraht.Goods1);
			pchar.questTemp.WPU.Fraht.GoodsQty = sti(pchar.questTemp.WPU.Fraht.GoodsQty1);
			pchar.questTemp.WPU.Fraht.Money = sti(pchar.questTemp.WPU.Fraht.Money1);
		break;
	
		case "Fraht_Choise_2":
			dialog.text = "好的, 太棒了! 我会处理必要的文件, 你可以准备好你的船装货了。 ";
			link.l1 = "我会尽力的! ";
			link.l1.go = "Fraht_Forcemajor";
			AddCharacterGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods2), sti(pchar.questTemp.WPU.Fraht.GoodsQty2));
			iFrahtGoods2 = pchar.questTemp.WPU.Fraht.Goods2;
			ReOpenQuestHeader("Fraht");
			AddQuestRecord("Fraht", "1");
			AddQuestUserData("Fraht", "sGoods", GetGoodsNameAlt(iFrahtGoods2));
			AddQuestUserData("Fraht", "sGoodQty", FindRussianQtyString(sti(pchar.questTemp.WPU.Fraht.GoodsQty2)));
			AddQuestUserData("Fraht", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Fraht.DaysQty2)));
			AddQuestUserData("Fraht", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money2)));
			AddQuestUserData("Fraht", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.StartCity+"Gen"));
			AddQuestUserData("Fraht", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City2+"Gen"));
			SetFunctionTimerCondition("FrahtTime_Over", 0, 0, sti(pchar.questTemp.WPU.Fraht.DaysQty2), false);
			pchar.questTemp.WPU.Fraht.TargetPortmanID = pchar.questTemp.WPU.Fraht.City2+"_portman";
			pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iFrahtGoods2].Cost);//цена единицы товара
			pchar.questTemp.WPU.Fraht.GoodsAverigeCost = sti(Goods[iFrahtGoods2].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty2);//средняя стоимость товара
			pchar.questTemp.WPU.Fraht.Goods = sti(pchar.questTemp.WPU.Fraht.Goods2);
			pchar.questTemp.WPU.Fraht.GoodsQty = sti(pchar.questTemp.WPU.Fraht.GoodsQty2);
			pchar.questTemp.WPU.Fraht.Money = sti(pchar.questTemp.WPU.Fraht.Money2);
		break;
	
		case "Fraht_Choise_3":
			dialog.text = "好的, 太棒了! 我会处理必要的文件, 你可以准备好你的船装货了。 ";
			link.l1 = "我会尽力的! ";
			link.l1.go = "Fraht_Forcemajor";
			AddCharacterGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods3), sti(pchar.questTemp.WPU.Fraht.GoodsQty3));
			iFrahtGoods3 = pchar.questTemp.WPU.Fraht.Goods3;
			ReOpenQuestHeader("Fraht");
			AddQuestRecord("Fraht", "1");
			AddQuestUserData("Fraht", "sGoods", GetGoodsNameAlt(iFrahtGoods3));
			AddQuestUserData("Fraht", "sGoodQty", FindRussianQtyString(sti(pchar.questTemp.WPU.Fraht.GoodsQty3)));
			AddQuestUserData("Fraht", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Fraht.DaysQty3)));
			AddQuestUserData("Fraht", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money3)));
			AddQuestUserData("Fraht", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.StartCity+"Gen"));
			AddQuestUserData("Fraht", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City3+"Gen"));
			SetFunctionTimerCondition("FrahtTime_Over", 0, 0, sti(pchar.questTemp.WPU.Fraht.DaysQty3), false);
			pchar.questTemp.WPU.Fraht.TargetPortmanID = pchar.questTemp.WPU.Fraht.City3+"_portman";
			pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iFrahtGoods3].Cost);//цена единицы товара
			pchar.questTemp.WPU.Fraht.GoodsAverigeCost = sti(Goods[iFrahtGoods3].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty3);//средняя стоимость товара
			pchar.questTemp.WPU.Fraht.Goods = sti(pchar.questTemp.WPU.Fraht.Goods3);
			pchar.questTemp.WPU.Fraht.GoodsQty = sti(pchar.questTemp.WPU.Fraht.GoodsQty3);
			pchar.questTemp.WPU.Fraht.Money = sti(pchar.questTemp.WPU.Fraht.Money3);
		break;
	
		case "Fraht_Forcemajor":
			pchar.questTemp.WPU.Fraht = "begin";
			sld = characterFromId(pchar.questTemp.WPU.Fraht.TargetPortmanID);
			pchar.questTemp.WPU.Fraht.Nation = sld.nation;//нация получателя
			pchar.questTemp.WPU.Current.TargetIslandID = GetCharacterCurrentIslandId(sld);//ИД целевого ареала
			pchar.questTemp.WPU.Fraht.TargetCity = FindTownOnIsland(pchar.questTemp.WPU.Current.TargetIslandID);
			pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count)+1;//считаем сделанные фрахты
			if (pchar.questTemp.WPU.Fraht.Chance > 3) TraderHunterOnMap(false);//запуск ДУ на глобалке
			if (pchar.questTemp.WPU.Fraht.Chance == 2) FrahtHunterOnSea();//создание ДУ в акватории
			DialogExit();
		break;
	
		case "Fraht_complete":
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
		{
			iFrahtGoods = makeint(pchar.questTemp.WPU.Fraht.Goods);
			amount = sti(pchar.questTemp.WPU.Fraht.GoodsQty) - GetSquadronGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods));
			if (amount > 0)
			{
				dialog.text = "那么, 让我看看。 你应该运送一批" + GetGoodsNameAlt(iFrahtGoods)+ ", 数量为" + FindRussianQtyString(pchar.questTemp.WPU.Fraht.GoodsQty) + "。 但正如我所见, 你没有交付全部货物 - 你短缺了" + FindRussianQtyString(sti(amount)) + "。 ";
				link.l1 = "一千只鲨鱼! 一定是那些该死的老鼠! 但是别担心, " + GetAddress_FormToNPC(NPChar) + ", 我会购买缺少的数量并交付全部货物。 ";
				link.l1.go = "Fraht_complete_3";
				break;
			}
			dialog.text = "那么, 让我看看。 你应该运送一批" + GetGoodsNameAlt(iFrahtGoods)+ ", 数量为" + FindRussianQtyString(pchar.questTemp.WPU.Fraht.GoodsQty) + "。 对吗? ";
			link.l1 = "完全正确, " + GetAddress_FormToNPC(NPChar) + "。 ";
			link.l1.go = "Fraht_complete_1";
		}
		else
		{
			dialog.text = "我在港口没看到你的船。 离开港口然后再来见我 - 然后我们再谈。 ";
			link.l1 = "好的, 我会那么做的。 ";
			link.l1.go = "exit";
		}
		break;
	
		case "Fraht_complete_1":
			if (pchar.questTemp.WPU.Fraht == "late")//опоздали
			{
				iTime = makeint(GetQuestPastDayParam("questTemp.Fraht.Late"))+1;
				pchar.questTemp.WPU.Fraht.DayLate = iTime;
				pchar.questTemp.WPU.Fraht.PercentLate = iTime/0.2;
				pchar.questTemp.WPU.Fraht.Money = makeint(sti(pchar.questTemp.WPU.Fraht.Money) - sti(pchar.questTemp.WPU.Fraht.Money)*sti(pchar.questTemp.WPU.Fraht.PercentLate)/100);//снижаем оплату согласно числа дней опоздания
				dialog.text = "嗯... 但你迟到了" + FindRussianDaysString(iTime)+ "天。 因此我必须削减你的货运报酬。 根据合同, 每延迟一天, 罚款为总额的百分之五。 现在请拿上你的" + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money)) + ", 未来请尽量遵守合同。 ";
				link.l1 = "好吧, 至少还有一些。 ";
				link.l1.go = "Fraht_complete_2";
				break;
			}
			dialog.text = "感谢你的工作。 请拿上你的报酬 - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money)) + "。 ";
			link.l1 = "谢谢! ";
			link.l1.go = "Fraht_complete_2";
		break;
	
		case "Fraht_complete_2":
			if (pchar.questTemp.WPU.Fraht == "begin")
			{
				pchar.quest.FrahtTime_Over.over = "yes";
				AddQuestRecord("Fraht", "2");
			}
			else
			{
				pchar.quest.FrahtTime_FullOver.over = "yes";//снять второй таймер
				pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count)-1;//опоздавший рейс не засчитываем
				AddQuestRecord("Fraht", "4");
				AddQuestUserData("Fraht", "sDay", FindRussianDaysString(pchar.questTemp.WPU.Fraht.DayLate));
				AddQuestUserData("Fraht", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money)));
			}
			RemoveCharacterGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods), sti(pchar.questTemp.WPU.Fraht.GoodsQty));
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Fraht.Money));
			CloseQuestHeader("Fraht");
			DeleteAttribute(pchar, "questTemp.WPU.Fraht.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			pchar.questTemp.WPU.Fraht = "complete";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 100);//торговля
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Fraht.Nation), 2);
			Group_DeleteGroup("Fraht_Attack");
			DialogExit();
		break;
	
		case "Fraht_complete_bad":
			dialog.text = "你交付货物了吗? 太好了。 实际上, 我们不得不自己购买货物交给收货人! 而且这相当昂贵, 请注意。 所以, 如果你想重建你的信誉, 你将不得不补偿我们的费用并支付罚款。 至于货物, 你可以留着 - 我们不再需要它了。 ";
			link.l1 = "是的, 当然。 多少钱? ";
			link.l1.go = "Fraht_complete_bad_1";
		break;
	
		case "Fraht_complete_bad_1":
			pchar.questTemp.WPU.Fraht.GoodsAverigeCost = sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)*3;
			dialog.text = "货物成本的三倍。 这相当于" + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)) + "。 ";
			if (sti(Pchar.money) >= sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost))
			{
				link.l1 = "这可不少。 但生意就是生意。 好吧, 给你钱。 ";
				link.l1.go = "Fraht_complete_pay";
			}
			link.l2 = "你疯了吗? 要求如此离谱的金额是贪婪的极限! 你不会从我这里得到任何东西! ";
			link.l2.go = "Fraht_complete_fail";
		break;
	
		case "Fraht_complete_pay":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost));
			dialog.text = "明智的决定。 现在我可以看出你确实是个认真的人。 我想我们将来仍然可以合作。 ";
			link.l1 = "谢谢, 现在我得走了。 ";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", 12);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Fraht.Nation), 30);
			if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus"))
			{
				AddQuestRecord("Escort", "8");
				AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)));
				CloseQuestHeader("Escort");
				pchar.questTemp.WPU.Escort = "complete";
				DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
				DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			}
			else
			{
				AddQuestRecord("Fraht", "6");
				AddQuestUserData("Fraht", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)));
				CloseQuestHeader("Fraht");
				pchar.questTemp.WPU.Fraht = "complete";
				DeleteAttribute(pchar, "questTemp.WPU.Fraht.TargetPortmanID");
			}
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 50);//торговля
			AddCharacterExpToSkill(pchar, "Leadership", 70);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 70);//везение
		break;
	
		case "Fraht_complete_fail":
			dialog.text = "哦, 我明白了... 那么, 在这种情况下, 你永远不应该再在" + NationNameGenitive(sti(pchar.questTemp.WPU.Fraht.Nation)) + "的任何港口管理局露面! 滚出去! ";
			link.l1 = "我肯定没错过多少...";
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus"))
			{
				AddQuestRecord("Escort", "9");
				AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)));
				CloseQuestHeader("Escort");
				pchar.questTemp.WPU.Escort = "complete";
				DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
				DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			}
			else
			{
				AddQuestRecord("Fraht", "7");
				CloseQuestHeader("Fraht");
				DeleteAttribute(pchar, "questTemp.WPU.Fraht.TargetPortmanID");
			}
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			pchar.questTemp.WPU.Fraht = "fail";
			ChangeCharacterComplexReputation(pchar,"nobility", -10);
		break;
	
		case "Fraht_complete_3":
			dialog.text = "快点, 收货人已经知道你的船到了, 他很担心他的货物。 ";
			link.l1 = "既然如此, 我不再浪费时间了! ";
			link.l1.go = "exit";
		break;
	//фрахт <--
	
/// -------------------------------работа курьером по доставке почты-------------------------------------

		case "Postcureer":
			pchar.questTemp.WPU.Postcureer.City = findCurrentCity2(npchar);
			pchar.questTemp.WPU.Postcureer.StartCity = npchar.city;//город квестодателя
			pchar.questTemp.WPU.Postcureer.Chance = rand(4);//форс-мажор
			idaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Postcureer.StartCity), GetArealByCityName(pchar.questTemp.WPU.Postcureer.City));
			pchar.questTemp.WPU.Postcureer.DaysQty = makeint(sti(idaysQty)*(frand(0.3)+0.7)); 
			if (sti(pchar.questTemp.WPU.Postcureer.DaysQty) == 1) pchar.questTemp.WPU.Postcureer.DaysQty = 2;
			pchar.questTemp.WPU.Postcureer.Money = (sti(idaysQty)*1000)*sti(idaysQty)/sti(pchar.questTemp.WPU.Postcureer.DaysQty)*(1+frand(0.2));
			dialog.text = "这个包裹必须在" +  FindRussianDaysString(pchar.questTemp.WPU.Postcureer.DaysQty) + "内尽快送到" + XI_ConvertString("Colony" + pchar.questTemp.WPU.Postcureer.City) + "市的港口管理局。 报酬 - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))"。 ";
			link.l1 = "我同意! ";
			link.l1.go = "Postcureer_1";
			link.l2 = "嗯... 但我不会走那条路。 抱歉, 我不得不拒绝。 ";
			link.l2.go = "exit";
		break;
	
		case "Postcureer_1":
			dialog.text = "太好了! 我就指望你了。 这是包裹。 ";
			link.l1 = "我马上起航! ";
			link.l1.go = "exit";
			GiveItem2Character(pchar, "PostLetters");
			pchar.questTemp.WPU.Postcureer = "begin";
			pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City +"_portman";//ИД портмана
			sld = characterFromId(pchar.questTemp.WPU.Postcureer.TargetPortmanID);
			pchar.questTemp.WPU.Postcureer.Nation = sld.nation;//нация получателя
			pchar.questTemp.WPU.Current.TargetIslandID = GetCharacterCurrentIslandId(sld);//ИД целевого ареала
			pchar.questTemp.WPU.Postcureer.EnemyNation = GetEnemyNationToMainCharacter();//вражеская нация
			i = 0;
			while (sti(pchar.questTemp.WPU.Postcureer.EnemyNation) == PIRATE)
			{
				pchar.questTemp.WPU.Postcureer.EnemyNation = GetEnemyNationToMainCharacter();
				i++;
				if(i > 5) pchar.questTemp.WPU.Postcureer.EnemyNation = FindEnemyNation2NationWithoutPirates(sti(pchar.BaseNation));
			}
			pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count)+1;//считаем сделанные доставки
			//запустить регату при счетчике > 4
			if (!CheckAttribute(pchar, "questTemp.RegataGo") && sti(pchar.questTemp.WPU.Postcureer.count) > 4)
			{
				pchar.questTemp.RegataGo = "true";
				pchar.questTemp.Regata.CureerCity = FindFriendCityToMC(true);//город, в котором вестовой подойдет
				if (pchar.questTemp.Regata.CureerCity == "PortRoyal") pchar.questTemp.Regata.CureerCity = "SentJons";
				pchar.quest.Regata_Cureer.win_condition.l1 = "location";
				pchar.quest.Regata_Cureer.win_condition.l1.location = pchar.questTemp.Regata.CureerCity+"_town";
				pchar.quest.Regata_Cureer.function = "PrepareToRegata";
				log_testinfo(pchar.questTemp.Regata.CureerCity);
			}
			if (pchar.questTemp.WPU.Postcureer.Chance > 3) EnemyNationHunterOnMap(false);//запуск перехватчиков на глобалке
			if (pchar.questTemp.WPU.Postcureer.Chance == 2) FrahtHunterOnSea();//создание перехватчиков в акватории
			ReOpenQuestHeader("Postcureer");
			AddQuestRecord("Postcureer", "1");
			AddQuestUserData("Postcureer", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty)));
			AddQuestUserData("Postcureer", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)));
			AddQuestUserData("Postcureer", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen"));
			AddQuestUserData("Postcureer", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City)); // belamour gen
			AddQuestUserData("Postcureer", "sSex1", GetSexPhrase("",""));
			SetFunctionTimerCondition("PostcureerTime_Over", 0, 0, sti(pchar.questTemp.WPU.Postcureer.DaysQty), false);
		break;
	
		case "Postcureer_complete":
			if (pchar.questTemp.WPU.Postcureer == "late")//опоздали
			{
				iTime = makeint(GetQuestPastDayParam("questTemp.Postcureer.Late"))+1;
				pchar.questTemp.WPU.Postcureer.DayLate = iTime;
				pchar.questTemp.WPU.Postcureer.PercentLate = iTime/0.1;
				pchar.questTemp.WPU.Postcureer.Money = makeint(sti(pchar.questTemp.WPU.Postcureer.Money) - sti(pchar.questTemp.WPU.Postcureer.Money)*sti(pchar.questTemp.WPU.Postcureer.PercentLate)/100);//根据迟到天数降低报酬
				dialog.text = "嗯... 但你迟到了" + FindRussianDaysString(iTime)+ "天。 因此我必须削减你的工作报酬。 根据合同, 每延迟一天, 罚款为总额的百分之五。 现在请拿上你的" + FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)) + ", 未来请尽量遵守合同。 ";
				link.l1 = "好吧, 至少还有一些。 ";
				link.l1.go = "Postcureer_complete_1";
				break;
			}
			dialog.text = "感谢你的工作。 请拿上你的报酬 - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)) + "。 ";
			link.l1 = "谢谢! ";
			link.l1.go = "Postcureer_complete_1";
		break;
	
		case "Postcureer_complete_1":
			if (pchar.questTemp.WPU.Postcureer == "begin")
			{
				pchar.quest.PostcureerTime_Over.over = "yes";
				AddQuestRecord("Postcureer", "2");
			}
			else
			{
				pchar.quest.PostcureerTime_FullOver.over = "yes";//снять второй таймер
				pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count)-1;//опоздавший рейс не засчитываем
				AddQuestRecord("Postcureer", "4");
				AddQuestUserData("Postcureer", "sDay", FindRussianDaysString(pchar.questTemp.WPU.Postcureer.DayLate));
				AddQuestUserData("Postcureer", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)));
				AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
			}
			RemoveItems(PChar, "PostLetters", 1);
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Postcureer.Money));
			CloseQuestHeader("Postcureer");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			pchar.questTemp.WPU.Postcureer = "complete";
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Postcureer.Nation), 2);
			Group_DeleteGroup("Fraht_Attack");
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			Achievment_Set("ach_CL_118");
			DialogExit();
		break;
	
		case "Postcureer_complete_bad":
			dialog.text = "现在我们该怎么处理它? 人们不知道等了多久, 而你今天才把它带来。 好吧, 把它给我 - 也许它还有一些用处。 我希望你明白现在完全没有报酬。 ";
			link.l1 = "当然, 我明白。 拿上你的包裹。 再会。 ";
			link.l1.go = "exit";
			RemoveItems(PChar, "PostLetters", 1);
			CloseQuestHeader("Postcureer");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			Group_DeleteGroup("Fraht_Attack");
			pchar.questTemp.WPU.Postcureer = "fail";
		break;
	
/// ---------------------------работа в качестве эскорта для торговых кораблей----------------------------

		case "escort":
			pchar.questTemp.WPU.Escort.ShipName1 = GenerateRandomNameToShip(sti(npchar.nation));//имена кораблей
			pchar.questTemp.WPU.Escort.ShipName2 = GenerateRandomNameToShip(sti(npchar.nation));
			pchar.questTemp.WPU.Escort.Goods1 = rand(GOOD_PAPRIKA);
			pchar.questTemp.WPU.Escort.Goods2 = rand(GOOD_PAPRIKA);
			pchar.questTemp.WPU.Escort.City = findCurrentCity1(npchar);//целевой город
			pchar.questTemp.WPU.Escort.StartCity = npchar.city;//город квестодателя
			pchar.questTemp.WPU.Escort.Chance = rand(4);//форс-мажор
			idaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Escort.StartCity), GetArealByCityName(pchar.questTemp.WPU.Escort.City));
			pchar.questTemp.WPU.Escort.DaysQty = makeint(sti(idaysQty)*(frand(0.5)+1)); 
			pchar.questTemp.WPU.Escort.Money = (sti(idaysQty)*2000)*sti(idaysQty)/sti(pchar.questTemp.WPU.Escort.DaysQty)*(1+frand(0.2));
			dialog.text = "那么, 你需要将'" + pchar.questTemp.WPU.Escort.ShipName1 + "'和'" + pchar.questTemp.WPU.Escort.ShipName2 + "'号船护送到" + XI_ConvertString("Colony" + pchar.questTemp.WPU.Escort.City) + "市, 期限为" +  FindRussianDaysString(pchar.questTemp.WPU.Escort.DaysQty) + "。 报酬 - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))"。 两艘船都必须安全抵达目的地。 你将把船交给当地港口管理局的官员。 他也会是给你工作报酬的人。 ";
			link.l1 = "一切似乎都清楚了。 我可以开始了吗? ";
			link.l1.go = "escort_1";
			link.l2 = "嗯... 但我不会走那条路。 抱歉, 我不得不拒绝。 ";
			link.l2.go = "exit";
		break;
	
		case "escort_1":
			dialog.text = "开始吧。 从现在起, 那些船由你指挥。 ";
			link.l1 = "那么, 我起航了! ";
			link.l1.go = "escort_add_ships";
			pchar.questTemp.WPU.Escort = "begin";
			pchar.questTemp.WPU.Escort.ShipNation = npchar.nation;//нация отправителя
			pchar.questTemp.WPU.Escort.TargetPortmanID = pchar.questTemp.WPU.Escort.City +"_portman";//ИД портмана
			sld = characterFromId(pchar.questTemp.WPU.Escort.TargetPortmanID);
			pchar.questTemp.WPU.Escort.Nation = sld.nation;//нация получателя
			pchar.questTemp.WPU.Current.TargetIslandID = GetCharacterCurrentIslandId(sld);//ИД целевого ареала
			pchar.questTemp.WPU.Escort.EnemyNation = GetEnemyNationToMainCharacter();//вражеская нация
			i = 0;
			while (sti(pchar.questTemp.WPU.Escort.EnemyNation) == PIRATE)
			{
				pchar.questTemp.WPU.Escort.EnemyNation = GetEnemyNationToMainCharacter();
				i++;
				if(i > 5) pchar.questTemp.WPU.Escort.EnemyNation = FindEnemyNation2NationWithoutPirates(sti(pchar.BaseNation));
			}
			pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)+1;//считаем сделанные эскорты
			if (pchar.questTemp.WPU.Escort.Chance > 3) EnemyNationHunterOnMap(false);//запуск перехватчиков на глобалке
			if (pchar.questTemp.WPU.Escort.Chance == 3) TraderHunterOnMap(false);//запуск ДУ на глобалке
			if (pchar.questTemp.WPU.Escort.Chance < 2) FrahtHunterOnSea();//создание перехватчиков в акватории
			ReOpenQuestHeader("Escort");
			AddQuestRecord("Escort", "1");
			AddQuestUserData("Escort", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Escort.DaysQty)));
			AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)));
			AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
			AddQuestUserData("Escort", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.City)); // belamour gen
			SetFunctionTimerCondition("EscortTime_Over", 0, 0, sti(pchar.questTemp.WPU.Escort.DaysQty), false);
		break;
	
		case "escort_add_ships":
			int iGoods1, iGoods2, iSpace1, iSpace2, ShipType, Rank;
			int iNation = pchar.questTemp.WPU.Escort.ShipNation;
			int iLifeday = sti(pchar.questTemp.WPU.Escort.DaysQty)+10;
			string sTemp;
	        for (i=1; i<=2; i++)
	        {
				ShipType = GetRandomShipType(GetClassFlag(sti(RealShips[sti(pchar.Ship.Type)].Class)), FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
				Rank = 5 * (6 - sti(RealShips[sti(pchar.Ship.Type)].Class)) + rand(5);
				if (i == 1) sTemp = pchar.questTemp.WPU.Escort.ShipName1;
				if (i == 2) sTemp = pchar.questTemp.WPU.Escort.ShipName2;
				if (i == 2) ShipType = SHIP_FLEUT;//один всегда флейт
	            sld = GetCharacter(NPC_GenerateCharacter("EscortCaptain_"+i, "trader_"+(rand(15)+1), "man", "man", Rank, iNation, iLifeday, true, "citizen"));
				FantomMakeSmallSailor(sld, ShipType, sTemp, -1, 10+rand(10), 10+rand(10), 10+rand(10), 10+rand(10), 10+rand(10));
				DeleteAttribute(sld, "SaveItemsForDead");
				DeleteAttribute(sld, "DontClearDead");
				SetCharacterGoods(sld, GOOD_FOOD, 400+rand(200));
				SetCharacterGoods(sld, GOOD_MEDICAMENT, 60+rand(30));
	            iGoods1 = sti(pchar.questTemp.WPU.Escort.Goods1);
				iSpace1 = GetCharacterFreeSpace(sld, iGoods1);
				iSpace1 = makeint(iSpace1/2 + rand(iSpace1/2));
				iGoods2 = sti(pchar.questTemp.WPU.Escort.Goods2);
				iSpace2 = GetCharacterFreeSpace(sld, iGoods2);
				iSpace2 = makeint(iSpace2/2 + rand(iSpace2/2));
				if (i == 1) SetCharacterGoods(sld, iGoods1, iSpace1);
				if (i == 2) SetCharacterGoods(sld, iGoods2, iSpace2);
				sld.CompanionEnemyEnable = false; //всегда друзья
	            SetCompanionIndex(pchar, -1, sti(sld.index));
				sld.loyality = MAX_LOYALITY;
				SetCharacterRemovable(sld, false);
				sld.Dialog.Filename = "Common_portman.c";
				sld.dialog.currentnode = "Escort_companion";
				pchar.quest.Escort_fail.win_condition.l1 = "NPC_Death";
				pchar.quest.Escort_fail.win_condition.l1.character = "EscortCaptain_1";
				pchar.quest.Escort_fail.win_condition.l2 = "NPC_Death";
				pchar.quest.Escort_fail.win_condition.l2.character = "EscortCaptain_2";
				pchar.quest.Escort_fail.function = "Escort_failed";
	        }
			if (pchar.questTemp.WPU.Escort.Chance > 3) EnemyNationHunterOnMap(false);//запуск перехватчиков на глобалке
			if (pchar.questTemp.WPU.Escort.Chance == 3) TraderHunterOnMap(false);//запуск ДУ на глобалке
			if (pchar.questTemp.WPU.Escort.Chance < 2) FrahtHunterOnSea();//создание перехватчиков в акватории
			DialogExit();
		break;
	
		case "Escort_complete":
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
		{
			//проверяем, все ли корабли
			if (GetCharacterIndex("EscortCaptain_1") == -1 || GetCharacterIndex("EscortCaptain_2") == -1)
			{
				dialog.text = "Hmm... 我只在你的护卫队中看到一艘船。 这正确吗? ";
				link.l1 = "是的, " + GetAddress_FormToNPC(NPChar) + "。 另一艘在与敌人中队的战斗中沉没了。 ";
				if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus")) 
				{
				link.l1.go = "EscortBonus_complete_fail";
				}
				else
				{
					link.l1.go = "Escort_complete_fail";
				}
				break;
			}
			iGoods = pchar.questTemp.WPU.Escort.Goods;
			if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus")) 
			{
				//pchar.questTemp.WPU.Escort.Money = sti(pchar.questTemp.WPU.Escort.Money)+sti(pchar.questTemp.WPU.Escort.BonusMoney);
				pchar.questTemp.WPU.Escort.Money = sti(pchar.questTemp.WPU.Escort.TotalMoney);
				amount = sti(pchar.questTemp.WPU.Escort.GoodsQty) - GetSquadronGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods));
				if (amount > 0)
				{
					dialog.text = "好吧, 那么。 你本应护送船只并运送" + GetGoodsNameAlt(iGoods) + "货物, 数量为" + FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.GoodsQty)) + "。 但我发现你没有交付全部货物 - 你短缺了" + FindRussianQtyString(sti(amount)) + "。 ";
					link.l1 = "一千只鲨鱼! 一定是那些该死的老鼠! 但别担心, " + GetAddress_FormToNPC(NPChar) + ", 我会购买缺少的数量并上交整批货物。 ";
					link.l1.go = "Fraht_complete_3";
					break;
				}
			}
			if (pchar.questTemp.WPU.Escort == "late")//迟到了
			{
				iTime = makeint(GetQuestPastDayParam("questTemp.Escort.Late")) + 1;
				pchar.questTemp.WPU.Escort.DayLate = iTime;
				pchar.questTemp.WPU.Escort.PercentLate = iTime / 0.1;
				pchar.questTemp.WPU.Escort.Money = makeint(sti(pchar.questTemp.WPU.Escort.Money) - sti(pchar.questTemp.WPU.Escort.Money) * sti(pchar.questTemp.WPU.Escort.PercentLate) / 100);//根据迟到天数减少付款
				dialog.text = "嗯... 但你迟到了" + FindRussianDaysString(iTime) + "天。 因此, 我必须削减你这项工作的报酬。 根据合同, 每延迟一天, 罚款为总金额的5%。 现在, 请拿走你的" + FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)) + ", 以后尽量遵守合同。 ";
				link.l1 = "好吧, 至少还有点钱。 ";
				link.l1.go = "Escort_complete_1";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus")) 
			{
				dialog.text = "好吧, 那么。 你本应护送船只并运送" + GetGoodsNameAlt(iGoods) + "货物, 数量为" + FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.GoodsQty)) + "。 感谢你的工作。 请拿走你的报酬 - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)) + "。 ";
			}
			else
			{
				dialog.text = "感谢你的工作。 请拿走你的报酬 - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)) + "。 ";
			}
			link.l1 = "谢谢! ";
			link.l1.go = "Escort_complete_1";
		}
		else
		{
			dialog.text = "我在港口没看到你的船。 离开后再来见我 - 然后我们再谈。 ";
			link.l1 = "好的, 我会那样做。 ";
			link.l1.go = "exit";
		}
		break;
	
		case "Escort_complete_1":
			pchar.quest.Escort_fail.over = "yes";//снять прерывание
			if (pchar.questTemp.WPU.Escort == "begin")
			{
				pchar.quest.EscortTime_Over.over = "yes";//снять таймер
				AddQuestRecord("Escort", "2");
			}
			else
			{
				pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)-1;//опоздавший рейс не засчитываем
				pchar.quest.EscortTime_FullOver.over = "yes";//снять второй таймер
				if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus"))
				{
					pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count)-1;//опоздавший рейс не засчитываем
				}
				AddQuestRecord("Escort", "4");
				AddQuestUserData("Escort", "sDay", FindRussianDaysString(pchar.questTemp.WPU.Escort.DayLate));
				AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)));
			}
			RemoveCharacterCompanion(Pchar, characterFromID("EscortCaptain_1"));//удалим компаньонов
			RemoveCharacterCompanion(Pchar, characterFromID("EscortCaptain_2"));
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Escort.Money));
			if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus")) RemoveCharacterGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods), sti(pchar.questTemp.WPU.Escort.GoodsQty));
			CloseQuestHeader("Escort");
			DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			pchar.questTemp.WPU.Escort = "complete";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Defence", 100);//защита
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Escort.Nation), 2);
			Group_DeleteGroup("Fraht_Attack");
			DialogExit();
		break;
	
		case "escort_bonus":
			pchar.questTemp.WPU.Escort.ShipName1 = GenerateRandomNameToShip(sti(npchar.nation));//имена кораблей
			pchar.questTemp.WPU.Escort.ShipName2 = GenerateRandomNameToShip(sti(npchar.nation));
			pchar.questTemp.WPU.Escort.Goods = 	hrand(GOOD_PAPRIKA);//для ГГ
			pchar.questTemp.WPU.Escort.Goods1 = hrand(GOOD_PAPRIKA-3);
			pchar.questTemp.WPU.Escort.Goods2 = hrand(GOOD_PAPRIKA-5);
			iGoods = pchar.questTemp.WPU.Escort.Goods;
			iGoodsQty = makeint(GetCharacterFreeSpace(pchar, iGoods))-(50+rand(100));//количество груза
			pchar.questTemp.WPU.Escort.GoodsQty = iGoodsQty;
			pchar.questTemp.WPU.Escort.City = findCurrentCity1(npchar);//целевой город
			pchar.questTemp.WPU.Escort.StartCity = npchar.city;//город квестодателя
			pchar.questTemp.WPU.Escort.Chance = rand(4);//форс-мажор
			idaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Escort.StartCity), GetArealByCityName(pchar.questTemp.WPU.Escort.City));
			pchar.questTemp.WPU.Escort.DaysQty = makeint(sti(idaysQty)*(frand(0.5)+1));//дни
			pchar.questTemp.WPU.Escort.Money = (sti(idaysQty)*2000)*sti(idaysQty)/sti(pchar.questTemp.WPU.Escort.DaysQty)*(1+frand(0.2));//оплата за сопровождение
			pchar.questTemp.WPU.Escort.BonusMoney = (makeint((sti(iGoodsQty) * sti(Goods[iGoods].Weight) / sti(Goods[iGoods].Units))))*(sti(idaysQty)*2)*sti(idaysQty)/sti(pchar.questTemp.WPU.Escort.DaysQty);//оплата за фрахт
			pchar.questTemp.WPU.Escort.TotalMoney = sti(pchar.questTemp.WPU.Escort.Money)+sti(pchar.questTemp.WPU.Escort.BonusMoney); // общая сумма
			dialog.text = "那么, 你需要将船只'" + pchar.questTemp.WPU.Escort.ShipName1 + "'和'" + pchar.questTemp.WPU.Escort.ShipName2 + "'护送到" + XI_ConvertString("Colony" + pchar.questTemp.WPU.Escort.City) + "城, 为期" + FindRussianDaysString(pchar.questTemp.WPU.Escort.DaysQty) + "天。 报酬 - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)) + "\n此外, 我还在你的船上放置了" + GetGoodsNameAlt(iGoods) + "货物, 数量为" + FindRussianQtyString(iGoodsQty) + "。 送货报酬 - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney)) + "。 ";
			link.l1 = "一切似乎都清楚了。 我可以开始了吗? ";
			link.l1.go = "escort_bonus_1";
			link.l2 = "嗯... 但我不去那边。 抱歉, 我必须拒绝。 ";
			link.l2.go = "exit";
		break;
	
		case "escort_bonus_1":
			dialog.text = "太好了! 指挥舰队吧。 ";
			link.l1 = "那我起航了! ";
			link.l1.go = "escort_add_ships";
			iGoods = pchar.questTemp.WPU.Escort.Goods;
			AddCharacterGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods), sti(pchar.questTemp.WPU.Escort.GoodsQty));
			pchar.questTemp.WPU.Escort = "begin";
			pchar.questTemp.WPU.Escort.Bonus = "true";
			pchar.questTemp.WPU.Escort.ShipNation = npchar.nation;//нация отправителя
			pchar.questTemp.WPU.Escort.TargetPortmanID = pchar.questTemp.WPU.Escort.City +"_portman";//ИД портмана
			sld = characterFromId(pchar.questTemp.WPU.Escort.TargetPortmanID);
			pchar.questTemp.WPU.Escort.Nation = sld.nation;//нация получателя
			pchar.questTemp.WPU.Current.TargetIslandID = GetCharacterCurrentIslandId(sld);//ИД целевого ареала
			pchar.questTemp.WPU.Escort.EnemyNation = GetEnemyNationToMainCharacter();//вражеская нация
			i = 0;
			while (sti(pchar.questTemp.WPU.Escort.EnemyNation) == PIRATE)
			{
				pchar.questTemp.WPU.Escort.EnemyNation = GetEnemyNationToMainCharacter();
				i++;
				if(i > 5) pchar.questTemp.WPU.Escort.EnemyNation = FindEnemyNation2NationWithoutPirates(sti(pchar.BaseNation));
			}
			pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)+1;//считаем сделанные эскорты
			pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count)+1;//считаем сделанные фрахты
			if (pchar.questTemp.WPU.Escort.Chance > 3) EnemyNationHunterOnMap(false);//запуск перехватчиков на глобалке
			if (pchar.questTemp.WPU.Escort.Chance == 3) TraderHunterOnMap(false);//запуск ДУ на глобалке
			if (pchar.questTemp.WPU.Escort.Chance < 3) FrahtHunterOnSea();//создание перехватчиков в акватории
			ReOpenQuestHeader("Escort");
			AddQuestRecord("Escort", "6");
			AddQuestUserData("Escort", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Escort.DaysQty)));
			AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)));
			AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
			AddQuestUserData("Escort", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.City));
			AddQuestUserData("Escort", "sGoods", GetGoodsNameAlt(iGoods));
			AddQuestUserData("Escort", "sGoodQty", FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.GoodsQty)));
			AddQuestUserData("Escort", "sMoney1", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney)));
			pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iGoods].Cost);//цена единицы товара
			pchar.questTemp.WPU.Fraht.GoodsAverigeCost = sti(Goods[iGoods].Cost)*sti(pchar.questTemp.WPU.Escort.GoodsQty);//средняя стоимость товара
			SetFunctionTimerCondition("EscortTime_Over", 0, 0, sti(pchar.questTemp.WPU.Escort.DaysQty), false);
		break;
	
		case "Escort_complete_fail":
			dialog.text = "难以置信! 我们雇你是为了什么? 你怎么能允许这种情况发生? ! 我希望你明白, 现在不可能有奖励了。 ";
			link.l1 = "当然, 我明白... 好吧, 再见。 ";
			link.l1.go = "exit";
			pchar.quest.Escort_fail.over = "yes";//снять прерывание
			pchar.quest.EscortTime_Over.over = "yes";//снять прерывание // patch-2
			if (GetCharacterIndex("EscortCaptain_1") == -1) RemoveCharacterCompanion(pchar, characterFromID("EscortCaptain_2"));
			else RemoveCharacterCompanion(pchar, characterFromID("EscortCaptain_1"));
			AddQuestRecord("Escort", "11");
			CloseQuestHeader("Escort");
			pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)-1;//рейс не засчитываем
			DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			pchar.questTemp.WPU.Escort = "complete";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Defence", 150);//защита
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			Group_DeleteGroup("Fraht_Attack");
		break;
	
		case "EscortBonus_complete_fail":
			if (GetCharacterIndex("EscortCaptain_1") == -1) RemoveCharacterCompanion(pchar, characterFromID("EscortCaptain_2"));
			else RemoveCharacterCompanion(pchar, characterFromID("EscortCaptain_1"));//удалим компаньона
			pchar.quest.Escort_fail.over = "yes";//снять прерывание
			amount = sti(pchar.questTemp.WPU.Escort.GoodsQty) - GetSquadronGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods));
			pchar.questTemp.WPU.Escort.GoodsQty = GetSquadronGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods));
			if (pchar.questTemp.WPU.Escort == "begin")
			{
				pchar.quest.EscortTime_Over.over = "yes";//снять таймер
				pchar.questTemp.WPU.Escort.MinusMoney = makeint(sti(pchar.questTemp.WPU.Escort.BonusMoney) - sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice)*sti(amount));
				if (sti(pchar.questTemp.WPU.Escort.MinusMoney) < 0) amount = 101;
				if (amount > 0 && amount <= 100)
				{
					pchar.questTemp.WPU.Escort.BonusMoney = sti(pchar.questTemp.WPU.Escort.MinusMoney);
					dialog.text = "难以置信! 我们雇你是为了什么? 你怎么能允许这种情况发生? ! 我希望你明白, 现在任何护航奖励都是不可能的... 不仅如此, 你的货物也短缺了 - " + FindRussianQtyString(sti(amount)) + "\n总的来说, 我只会为以可接受状态交付的货物支付运费, 减去丢失物品的价值。 拿到你的" + FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney)) + ", 你可以去任何你想去的地方。 ";
					link.l1 = "好吧, 至少还有点钱。 ";
					link.l1.go = "EscortBonus_complete_fail_1";
					break;
				}
				if (amount > 100)
				{
					dialog.text = "不可思议! 我们雇你是为了什么? 你怎么能允许这种情况发生? ! 我希望你明白, 现在任何护航奖励都是不可能的... 不仅如此, 你的货物也有巨大的短缺。 \n我没有时间等你去购买缺失的货物。 所以你必须全额赔偿费用 - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)) + "。 至于货物, 你可以留着。 ";
					if (sti(pchar.money) >= sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost))
					{
						link.l1 = "好吧, 别太激动。 这是你的钱。 ";
						link.l1.go = "EscortBonus_complete_fail_2";
					}
					link.l2 = "你们都疯了吗? 这简直是敲诈! 我什么都不会给你! ";
					link.l2.go = "EscortBonus_complete_fail_3";
					break;
				}
				dialog.text = "不可思议! 我们雇你是为了什么? 你怎么能允许这种情况发生? ! 我希望你明白, 现在任何护航奖励都是不可能的。 \n总的来说, 我只会为你所携带的货物支付运费。 拿到你的" + FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney)) + ", 你可以去任何你想去的地方。 ";
				link.l1 = "好吧, 至少还有点钱。 ";
				link.l1.go = "EscortBonus_complete_fail_1";
				break;
		}
		if (pchar.questTemp.WPU.Escort == "late")
		{
				pchar.quest.EscortTime_FullOver.over = "yes";//取消第二个计时器
				iTime = makeint(GetQuestPastDayParam("questTemp.Escort.Late"))+1;
				pchar.questTemp.WPU.Escort.DayLate = iTime;
				pchar.questTemp.WPU.Escort.PercentLate = iTime/0.1;
				pchar.questTemp.WPU.Escort.BonusMoney = makeint(sti(pchar.questTemp.WPU.Escort.BonusMoney) - sti(pchar.questTemp.WPU.Escort.BonusMoney)*sti(pchar.questTemp.WPU.Escort.PercentLate)/100);//снижаeм оплату согласно числа днeй опоздания
				if (amount > 0)
				{
					dialog.text = "难以置信! 我们雇你是为了什么? 你怎么能允许这种情况发生? ! 我希望你明白, 现在任何护航奖励都是不可能的... 你损失了一艘船, 迟到了" + FindRussianDaysString(iTime) + "天, 除此之外, 你的货物也短缺了 - " + FindRussianQtyString(sti(amount)) + "\n我没有时间等你去购买缺失的货物。 所以你必须全额赔偿费用" + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)) + "。 至于货物, 你可以留着。 ";
					if (sti(pchar.money) >= sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost))
					{
						link.l1 = "好吧, 别太激动。 这是你的钱。 ";
						link.l1.go = "EscortBonus_complete_fail_2";
					}
					link.l2 = "你们都疯了吗? 这简直是敲诈! 我什么都不会给你! ";
					link.l2.go = "EscortBonus_complete_fail_3";
					break;
				}
				dialog.text = "难以置信! 我们雇你是为了什么? 你怎么能允许这种情况发生? ! 我希望你明白, 现在任何护航奖励都是不可能的... 此外, 你迟到了" + FindRussianDaysString(iTime) + "天。 \n所以我不得不减少货运的付款。 根据协议, 每延迟一天, 罚款为原始金额的10%。 现在, 拿走你的" + FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney)) + ", 你可以走了。 ";
				link.l1 = "好吧, 至少还有点钱。 ";
				link.l1.go = "EscortBonus_complete_fail_1";
				break;
			}
		break;
	
		case "EscortBonus_complete_fail_1"://потеряли корабль, время и груз в норме или частично
			AddQuestRecord("Escort", "12");
			AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney)));
			CloseQuestHeader("Escort");
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Escort.BonusMoney));
			RemoveCharacterGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods), sti(pchar.questTemp.WPU.Escort.GoodsQty));
			pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)-1;//рейс не засчитываем
			DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			pchar.questTemp.WPU.Escort = "complete";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Defence", 150);//защита
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddCharacterExpToSkill(pchar, "Commerce", 100);//торговля
			Group_DeleteGroup("Fraht_Attack");
			DialogExit();
		break;
	
		case "EscortBonus_complete_fail_2"://потеряли корабль и груз, время норма или нет, мир
			AddQuestRecord("Escort", "13");
			AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)));
			CloseQuestHeader("Escort");
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost));
			pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)-1;//рейс не засчитываем
			pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Fraht.count)-1;//рейс не засчитываем
			DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			pchar.questTemp.WPU.Escort = "complete";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Defence", 150);//защита
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddCharacterExpToSkill(pchar, "Commerce", 50);//торговля
			Group_DeleteGroup("Fraht_Attack");
			DialogExit();
		break;
	
		case "EscortBonus_complete_fail_3"://потеряли корабль и груз, время норма или нет, война
			dialog.text = "哦, 我明白了... 那么, 在这种情况下, 你永远不应该再出现在" + NationNameGenitive(sti(pchar.questTemp.WPU.Escort.Nation)) + "的任何港口当局! 滚吧! ";
			link.l1 = "我当然没错过太多...";
			link.l1.go = "exit";
			AddQuestRecord("Escort", "14");
			AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)));
			CloseQuestHeader("Escort");
			pchar.questTemp.WPU.Escort.count = 0;//计数器归零
			pchar.questTemp.WPU.Escort.count = 0;//计数器归零
			DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			pchar.questTemp.WPU.Escort = "complete";
			pchar.questTemp.WPU.Fraht = "fail";
			ChangeCharacterComplexReputation(pchar,"nobility", -10);
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.WPU.Escort.Nation)) + "hunter", 30);
			pchar.questTemp.WPU.Fraht.Nation = pchar.questTemp.WPU.Escort.Nation;
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			Group_DeleteGroup("Fraht_Attack");
		break;
	
		case "Escort_fail"://损失了2艘船
			dialog.text = "这非常非常糟糕! 我们雇你是为了什么, 你能告诉我吗? 是为了保护船只? 还是只是为了闲逛? ";
			link.l1 = "我明白。 敌人实在太强大了, 而且... 但争论有什么意义 - 发生的事情已经发生了。 但是货物 - 货物仍然完好无损! 所以让我们把它整理清楚。 ";
			link.l1.go = "Escort_fail_complete";
		break;

		case "Escort_fail_complete":
			iFrahtGoods = makeint(pchar.questTemp.WPU.Escort.Goods);
			amount = sti(pchar.questTemp.WPU.Escort.GoodsQty) - GetSquadronGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods));
			if (amount > 0)
			{
				dialog.text = "那么, 让我们看看。 你本应交付一批" + GetGoodsNameAlt(iFrahtGoods) + ", 数量为" + FindRussianQtyString(pchar.questTemp.WPU.Escort.GoodsQty) + "。 但我发现你没有交付全部货物 - 你短缺了" + FindRussianQtyString(sti(amount)) + "。 ";
				link.l1 = "一千只鲨鱼! 一定是那些该死的老鼠! 但别担心, " + GetAddress_FormToNPC(NPChar) + ", 我会购买缺失的数量并上交整批货物。 ";
				link.l1.go = "Fraht_complete_3";
				break;
			}
			dialog.text = "那么, 让我们看看。 你本应交付一批" + GetGoodsNameAlt(iFrahtGoods) + ", 数量为" + FindRussianQtyString(pchar.questTemp.WPU.Escort.GoodsQty) + "。 对吗? ";
			link.l1 = "完全正确, " + GetAddress_FormToNPC(NPChar) + "。 ";
			link.l1.go = "Escort_fail_complete_1";
		break;
	
		case "Escort_fail_complete_1":
			DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			pchar.questTemp.WPU.Escort.Money = makeint(sti(pchar.questTemp.WPU.Escort.BonusMoney)/2);
			if (pchar.questTemp.WPU.Escort == "late")//迟到了
			{
				iTime = makeint(GetQuestPastDayParam("questTemp.Escort.Late"))+1;
				pchar.questTemp.WPU.Escort.DayLate = iTime;
				pchar.questTemp.WPU.Escort.PercentLate = iTime/0.1;
				pchar.questTemp.WPU.Escort.Money = makeint(sti(pchar.questTemp.WPU.Escort.Money) - sti(pchar.questTemp.WPU.Escort.Money)*sti(pchar.questTemp.WPU.Escort.PercentLate)/100);//снижаeм оплату согласно числа днeй опоздания
				dialog.text = "嗯... 你不仅损失了委托给你的船只, 还迟到了" + FindRussianDaysString(iTime) + "天。 所以我不得不削减货运的付款。 由于你无法拯救船只, 我将货运付款减半, 这是我能提供的最多的了。 \n此外, 根据合同, 每延迟一天, 罚款为原始金额的10%。 现在, 拿走你的" + FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)) + ", 然后离开。 ";
				link.l1 = "好吧, 至少还有点钱。 ";
				link.l1.go = "Escort_fail_complete_2";
				break;
			}
			dialog.text = "好吧, 尽管我对你无法保护委托给你的船只感到非常不满, 但至少你交付了货物。 由于你无法拯救船只, 我将货运付款减半, 这是我能提供的最多的了。 现在, 拿走你的报酬 - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)) + ", 你可以去任何你想去的地方。 ";
			link.l1 = "好吧, 至少还有点钱。 ";
			link.l1.go = "Escort_fail_complete_2";
		break;
	
		case "Escort_fail_complete_2":
			if (pchar.questTemp.WPU.Escort == "begin")
			{
				pchar.quest.EscortTime_Over.over = "yes";
				AddQuestRecord("Escort", "17");
				AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)));
			}
			else
			{
				pchar.quest.EscortTime_FullOver.over = "yes";//снять второй таймер
				AddQuestRecord("Escort", "18");
				AddQuestUserData("Escort", "sDay", FindRussianDaysString(pchar.questTemp.WPU.Escort.DayLate));
				AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)));
			}
			pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count)-1;//фейловый рейс не засчитываем
			RemoveCharacterGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods), sti(pchar.questTemp.WPU.Escort.GoodsQty));
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Escort.Money));
			CloseQuestHeader("Escort");
			DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			pchar.questTemp.WPU.Escort = "complete";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 50);//торговля
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			Group_DeleteGroup("Fraht_Attack");
			DialogExit();
		break;
	
//-------------------------------------задания 2 уровня для курьера---------------------------------------------
		case "Postcureer_LevelUp":
			pchar.questTemp.WPU.Postcureer.City = findCurrentCity2(npchar);//целевой город
			pchar.questTemp.WPU.Postcureer.StartCity = npchar.city;//город квестодателя
			idaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Postcureer.StartCity), GetArealByCityName(pchar.questTemp.WPU.Postcureer.City));
			pchar.questTemp.WPU.Postcureer.DaysQty = makeint(sti(idaysQty)*(frand(0.3)+0.6));//дни
			pchar.questTemp.WPU.Postcureer.Money = (sti(idaysQty)*3000)*sti(idaysQty)/sti(pchar.questTemp.WPU.Postcureer.DaysQty)*(1+frand(0.2));//оплата
			pchar.questTemp.WPU.Postcureer.Chance = rand(4);//форс-мажор
			pchar.questTemp.WPU.Postcureer.StartNation = npchar.nation;//нация отправителя
			pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City +"_portman";//ИД портмана
			sld = characterFromId(pchar.questTemp.WPU.Postcureer.TargetPortmanID);
			pchar.questTemp.WPU.Postcureer.Nation = sld.nation;//нация получателя
			pchar.questTemp.WPU.Current.TargetIslandID = GetCharacterCurrentIslandId(sld);//ИД целевого ареала
			pchar.questTemp.WPU.Postcureer.EnemyNation = GetEnemyNationToMainCharacter();//вражеская нация
			i = 0;
			while (sti(pchar.questTemp.WPU.Postcureer.EnemyNation) == PIRATE)
			{
				pchar.questTemp.WPU.Postcureer.EnemyNation = GetEnemyNationToMainCharacter();
				i++;
				if(i > 5) pchar.questTemp.WPU.Postcureer.EnemyNation = FindEnemyNation2NationWithoutPirates(sti(pchar.BaseNation));
			}

			switch (rand(3))
			{
				case 0:
					dialog.text = "你需要将一份紧急官方急件送到" + XI_ConvertString("Colony" + pchar.questTemp.WPU.Postcureer.City + "Gen") + "镇的总督手中, 不得迟于" + FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty)) + "天。 要非常小心 - 我们的敌人可能也在寻找这份急件。 送货报酬 - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)) + "。 ";
					link.l1 = "我同意! ";
					link.l1.go = "Postcureer_LevelUp_Go";
					link.l2 = "不, 我想我会放弃。 ";
					link.l2.go = "Postcureer_LevelDown";
					pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City + "_Mayor";//总督ID
					if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == "Villemstad_Mayor") pchar.questTemp.WPU.Postcureer.TargetPortmanID = "hol_guber"; // 修复Matias Beka #717
					pchar.questTemp.WPU.Current.Add = "给总督的急件";
					pchar.questTemp.WPU.Current.Item = "letter_2";//物品
					pchar.questTemp.WPU.Current.Itemdescr = "itmdescr_letter_2_PortmanLevelUp1";//描述
				break;
			
				case 1:
					dialog.text = "你需要将这些文件送到" + XI_ConvertString("Colony" + pchar.questTemp.WPU.Postcureer.City + "Gen") + "的店主手中, 不得迟于" + FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty)) + "天。 这是群岛各地商店的最新价格汇总 - 一份有价值的商业文件。 应注意 - 竞争对手可能会安排拦截。 送货报酬 - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)) + "。 ";
					link.l1 = "我同意! ";
					link.l1.go = "Postcureer_LevelUp_Go";
					link.l2 = "不, 我想我会放弃。 ";
					link.l2.go = "Postcureer_LevelDown";
					pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City + "_trader";//商人ID
//					pchar.questTemp.WPU.Current.Add = "сводку цeн для хозяина магазина";
					pchar.questTemp.WPU.Current.Add = "给店主的价格表";	 // LDH 23Jan17 翻译
					pchar.questTemp.WPU.Current.Item = "letter_2";//物品
					pchar.questTemp.WPU.Current.Itemdescr = "itmdescr_letter_2_PortmanLevelUp2";//描述
				break;
			
				case 2:
					dialog.text = "你需要将这捆文件送到" + XI_ConvertString("Colony" + pchar.questTemp.WPU.Postcureer.City + "Gen") + "镇的放贷人手中, 不得迟于" + FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty)) + "天。 这是关于汇率和股票价格的非常重要的信息。 要非常小心 - 一些可疑人物已经对获得这个包裹感兴趣。 送货报酬 - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)) + "。 ";
					link.l1 = "我同意! ";
					link.l1.go = "Postcureer_LevelUp_Go";
					link.l2 = "不, 我想我会放弃。 ";
					link.l2.go = "Postcureer_LevelDown";
					pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City + "_usurer";//放贷人ID
					pchar.questTemp.WPU.Current.Add = "给放贷人的一包信息";   // LDH 23Jan17 翻译
					pchar.questTemp.WPU.Current.Item = "letter_2";//物品
					pchar.questTemp.WPU.Current.Itemdescr = "itmdescr_letter_2_PortmanLevelUp3";//描述
				break;
			
				case 3:
					dialog.text = "你应该将这捆文件送到" + XI_ConvertString("Colony" + pchar.questTemp.WPU.Postcureer.City + "Gen") + "镇的码头管理员手中, 不得迟于" + FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty)) + "天。 它包含新的" + RandPhraseSimple(LinkRandPhrase("brig", "corvette", "frigate"), LinkRandPhrase("flute", "pinnace", "galleon")) + "的蓝图, 采用独特的技术设计。 我希望你明白还有其他... 感兴趣的各方, 所以你必须谨慎行事。 送货报酬 - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)) + "。 ";
					link.l1 = "我同意! ";
					link.l1.go = "Postcureer_LevelUp_Go";
					link.l2 = "不, 我想我会放弃。 ";
					link.l2.go = "Postcureer_LevelDown";
					pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City + "_shipyarder";//造船厂ID
					pchar.questTemp.WPU.Current.Add = "给造船厂老板的新船设计图";
					pchar.questTemp.WPU.Current.Item = "ShipyardsMap";//物品
					pchar.questTemp.WPU.Current.Itemdescr = "itmdescr_ShipyardsMap_PortmanLevelUp4";//描述
				break;
			}
		break;
	
		case "Postcureer_LevelUp_Go":
			dialog.text = "那就拿上文件起航吧。 祝你好运... 愿全能的神保佑你。 ";
			link.l1 = "谢谢! ";
			link.l1.go = "Forsmajor_choose";
			pchar.questTemp.WPU.Postcureer = "begin";
			pchar.questTemp.WPU.Postcureer.LevelUp = "true";
			pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count) + 1;
			//当计数器 > 4 时启动赛船
			if (!CheckAttribute(pchar, "questTemp.RegataGo") && sti(pchar.questTemp.WPU.Postcureer.count) > 4)
			{
				pchar.questTemp.RegataGo = "true";
				pchar.questTemp.Regata.CureerCity = FindFriendCityToMC(true);//信使会去的城市
				if (pchar.questTemp.Regata.CureerCity == "PortRoyal") pchar.questTemp.Regata.CureerCity = "SentJons";
				pchar.quest.Regata_Cureer.win_condition.l1 = "location";
				pchar.quest.Regata_Cureer.win_condition.l1.location = pchar.questTemp.Regata.CureerCity+"_town";
				pchar.quest.Regata_Cureer.function = "PrepareToRegata";
				log_testinfo(pchar.questTemp.Regata.CureerCity);
			}
			GiveItem2Character(pchar, pchar.questTemp.WPU.Current.Item);
			ChangeItemDescribe(pchar.questTemp.WPU.Current.Item, pchar.questTemp.WPU.Current.Itemdescr);
			ReOpenQuestHeader("Postcureer");
			AddQuestRecord("Postcureer", "6");
			AddQuestUserData("Postcureer", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty)));
			AddQuestUserData("Postcureer", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)));
			AddQuestUserData("Postcureer", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen"));
			AddQuestUserData("Postcureer", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City)); // belamour gen
			AddQuestUserData("Postcureer", "sText", pchar.questTemp.WPU.Current.Add);
			AddQuestUserData("Postcureer", "sSex1", GetSexPhrase("",""));
			SetFunctionTimerCondition("PostcureerTime_Over", 0, 0, sti(pchar.questTemp.WPU.Postcureer.DaysQty), false);
		break;
	
		case "Postcureer_LevelDown":
			dialog.text = "真遗憾... 实际上, 这种报价通常不会轻易出现。 但无论如何, 这是你的选择。 ";
			link.l1 = "是的, 这是我的选择, " + GetAddress_FormToNPC(NPChar) + "。 ";
			link.l1.go = "exit";
			pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count) - 1;//因拒绝特殊任务计数器减一
		break;
	
		case "Forsmajor_choose":
			switch (sti(pchar.questTemp.WPU.Postcureer.Chance))
			{
				case 0://到达城市的猎人 + 贸易拦截者
					pchar.quest.Postcureer_Hunter.win_condition.l1 = "Location";
					pchar.quest.Postcureer_Hunter.win_condition.l1.location = pchar.questTemp.WPU.Postcureer.City + "_town";
					pchar.quest.Postcureer_Hunter.function = "PostcureerGopHuntersOnLand";
					TraderHunterOnMap(false);
				break;
		
				case 1://在全局地图上创建快速拦截者
					EnemyNationHunterOnMap(true);
				break;
		
				case 2://在全局地图和到达港口启动贸易拦截者
					TraderHunterOnMap(false);
					FrahtHunterOnSea();
				break;
		
				case 3://在起始城市的雇佣军
					pchar.quest.Postcureer_Hunter.win_condition.l1 = "Location";
					pchar.quest.Postcureer_Hunter.win_condition.l1.location = pchar.questTemp.WPU.Postcureer.StartCity + "_town";
					pchar.quest.Postcureer_Hunter.function = "PostcureerProfHuntersOnLand";
				break;
		
				case 4://特工
					pchar.quest.Postcureer_Hunter.win_condition.l1 = "Location";
					pchar.quest.Postcureer_Hunter.win_condition.l1.location = pchar.questTemp.WPU.Postcureer.StartCity + "_town";
					pchar.quest.Postcureer_Hunter.function = "PostcureerAgent";
				break;
			}
			DialogExit();
		break;

		case "Postcureer_complete_fail":
			dialog.text = "该死! 他们终究还是跟踪你了。 可惜你不是士兵, 船长 - 那样的话事情可能会有所不同... 他们长什么样? ";
			link.l1 = "两个强壮的彪形大汉, 穿着黑色衣服, 戴着半面罩, 手持长柄斧和双管枪...";
			link.l1.go = "Postcureer_complete_fail_1";
		break;

		case "Postcureer_complete_fail_1":
			dialog.text = "我会立即通知总督开始寻找他们。 好吧, 再见, " + GetAddress_Form(NPChar) + "。 再次遗憾你不是士兵...";
			link.l1 = "对于所发生的事情, 我真的很抱歉, " + GetAddress_FormToNPC(NPChar) + "。 那么, 再见。 ";
			link.l1.go = "exit";
			if (pchar.questTemp.WPU.Postcureer == "begin") pchar.quest.PostcureerTime_Over.over = "yes";//取消计时器
			if (pchar.questTemp.WPU.Postcureer == "late") pchar.quest.PostcureerTime_FullOver.over = "yes";//取消第二个计时器
			CloseQuestHeader("Postcureer");
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count)-3;//скрутим счeтчик
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.LevelUp");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.fail");
			pchar.questTemp.WPU.Postcureer = "complete";
		break;
	
//----------------------------------------2级货运任务------------------------------------------

	case "Fraht_LevelUp":
		rColony = GetColonyByIndex(FindColony(npchar.city));
		pchar.questTemp.WPU.Fraht.StartCity = npchar.city;//任务发布者的城市
		pchar.questTemp.WPU.Fraht.Nation = npchar.nation;//接收方国家
		switch (rand(4))//用于测试
		{
			case 0:
				pchar.questTemp.WPU.Fraht.Goods = GOOD_CHOCOLATE + hrand(makeint(GOOD_TOBACCO - GOOD_CHOCOLATE));
				iGoods = pchar.questTemp.WPU.Fraht.Goods;
				//iGoodsQty = 3000 + sti(pchar.rank)*30*(hrand(9)+1);
				iGoodsQty = 1000+sti(pchar.rank)*10*(hrand(9)+1); // min 1100 max 5000
				pchar.questTemp.WPU.Fraht.GoodsQty = iGoodsQty;
				pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iGoods].Cost)*2;//двойная цeна eдиницы товара
				pchar.questTemp.WPU.Fraht.Money = sti(Goods[iGoods].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty)*2;//двойная стоимость товара
				pchar.questTemp.WPU.Current.Add = "double";
				// 08Mar17 "month" was "moths"
				dialog.text = "我们殖民地最近对某种商品的需求急剧增加。 当地商店已经没有库存了。 因此, 我希望你能提供" + GetGoodsNameAlt(iGoods) + ", 数量为" + FindRussianQtyString(iGoodsQty) + ", 我愿意支付双倍价格 - 每件" + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice)) + "。 这将达到" + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money)) + "。 哦, 尽量在一个月内完成 - 我不能再等货物了。 ";
				link.l1 = "好的, 我接受这个任务。 ";
				link.l1.go = "Fraht_LevelUp_Go";
				link.l2 = "很抱歉让你失望, 但我现在无法做到。 ";
				link.l2.go = "Fraht_LevelDown";
				SetNull2StoreGood(rColony, sti(pchar.questTemp.WPU.Fraht.Goods));
			break;
		
			case 1:
				pchar.questTemp.WPU.Fraht.Goods = GOOD_EBONY + hrand(makeint(GOOD_CINNAMON - GOOD_EBONY));
				iGoods = pchar.questTemp.WPU.Fraht.Goods;
				//iGoodsQty = 1500 + sti(pchar.rank)*20*(hrand(9)+1);
				iGoodsQty = 600+sti(pchar.rank)*5*(hrand(6)+1); // min 630 max 2000
				pchar.questTemp.WPU.Fraht.GoodsQty = iGoodsQty;
				pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iGoods].Cost)*2;//двойная цeна eдиницы товара
				pchar.questTemp.WPU.Fraht.Money = sti(Goods[iGoods].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty)*2;//двойная стоимость товара
				pchar.questTemp.WPU.Current.Add = "double";
				// 08Mar17 "month" was "moths"
				dialog.text = "我们殖民地最近对某种商品的需求急剧增加。 当地商店已经没有库存了。 因此, 我希望你能提供" + GetGoodsNameAlt(iGoods) + ", 数量为" + FindRussianQtyString(iGoodsQty) + ", 我愿意支付双倍价格 - 每件" + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice)) + "。 这将达到" + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money)) + "。 哦, 尽量在一个月内完成 - 我不能再等货物了。 ";
				link.l1 = "好的, 我接受这个任务。 ";
				link.l1.go = "Fraht_LevelUp_Go";
				link.l2 = "很抱歉让你失望, 但我现在无法做到。 ";
				link.l2.go = "Fraht_LevelDown";
				SetNull2StoreGood(rColony, sti(pchar.questTemp.WPU.Fraht.Goods));
			break;
		
			case 2:
				//pchar.questTemp.WPU.Fraht.Goods = GOOD_BOMBS + hrand(makeint(GOOD_POWDER - GOOD_BOMBS));
				pchar.questTemp.WPU.Fraht.Goods = GOOD_BOMBS;
				iGoods = pchar.questTemp.WPU.Fraht.Goods;
				//iGoodsQty = 15000 + sti(pchar.rank)*300*(hrand(9)+1);
				iGoodsQty = 5000+sti(pchar.rank)*10*(hrand(9)+1); // min 5100 max 9000
				pchar.questTemp.WPU.Fraht.GoodsQty = iGoodsQty;
				pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iGoods].Cost)*3;//тройная цeна eдиницы товара
				pchar.questTemp.WPU.Fraht.Money = makeint((sti(Goods[iGoods].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty)*3)/20);//тройная стоимость товара
				pchar.questTemp.WPU.Current.Add = "triple";
				// 08Mar17 "month" was "moths"
				dialog.text = "我们殖民地的军火库严重缺乏" + GetGoodsNameAlt(iGoods) + "。 当地商店已经没有库存了。 因此, 我希望你能提供" + GetGoodsNameAlt(iGoods) + ", 数量为" + FindRussianQtyString(iGoodsQty) + ", 我愿意支付三倍价格 - 每件" + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice)) + "。 这将达到" + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money)) + "。 哦, 尽量在一个月内完成 - 我不能再等货物了。 ";
				link.l1 = "好的, 我接受这个任务。 ";
				link.l1.go = "Fraht_LevelUp_Go";
				link.l2 = "很抱歉让你失望, 但我现在无法做到。 ";
				link.l2.go = "Fraht_LevelDown";
				SetNull2StoreGood(rColony, sti(pchar.questTemp.WPU.Fraht.Goods));
			break;
		
			case 3:
				pchar.questTemp.WPU.Fraht.Goods = GOOD_MEDICAMENT;
				iGoods = pchar.questTemp.WPU.Fraht.Goods;
				iGoodsQty = 7000 + sti(pchar.rank)*300*(hrand(9)+1);
				pchar.questTemp.WPU.Fraht.GoodsQty = iGoodsQty;
				pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iGoods].Cost)*3;//тройная цeна eдиницы товара
				pchar.questTemp.WPU.Fraht.Money = makeint((sti(Goods[iGoods].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty)*3)/30);//тройная стоимость товара
				pchar.questTemp.WPU.Current.Add = "triple";
				// 08Mar17 "month" was "moths"
				dialog.text = "在我们殖民地最近爆发热病后, 我们缺乏医疗用品 - 商店里也没有任何东西了。 总督担心市民的安全。 因此, 我希望你能提供" + GetGoodsNameAlt(iGoods) + ", 数量为" + FindRussianQtyString(iGoodsQty) + ", 我愿意支付三倍价格 - 每包" + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice)) + "。 这将达到" + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money)) + "。 哦, 尽量在一个月内完成 - 我不能再等货物了。 ";
				link.l1 = "好的, 我接受这个任务。 ";
				link.l1.go = "Fraht_LevelUp_Go";
				link.l2 = "很抱歉让你失望, 但我现在无法做到。 ";
				link.l2.go = "Fraht_LevelDown";
				SetNull2StoreGood(rColony, sti(pchar.questTemp.WPU.Fraht.Goods));
			break;
		
			case 4:
				pchar.questTemp.WPU.Fraht.Goods = GOOD_FOOD;
				iGoods = pchar.questTemp.WPU.Fraht.Goods;
				iGoodsQty = 15000 + sti(pchar.rank)*300*(hrand(9)+1);
				pchar.questTemp.WPU.Fraht.GoodsQty = iGoodsQty;
				pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iGoods].Cost)*2;//двойная цeна eдиницы товара
				pchar.questTemp.WPU.Fraht.Money = makeint((sti(Goods[iGoods].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty)*2)/10);//двойная стоимость товара
				pchar.questTemp.WPU.Current.Add = "double";
				// 08Mar17 "month" was "moths"
				dialog.text = "由于收成不好, 我们的殖民地一直需要进口粮食。 目前我们的库存几乎耗尽, 商店货架上的东西也早就被抢购一空。 我想请你给我送来" + GetGoodsNameAlt(iGoods)+ ", 数量为" + FindRussianQtyString(iGoodsQty) + ", 我愿意支付双倍的价钱—每包" + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice)) + "。 这样算下来总共是" + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money)) + "。 哦, 尽量在一个月内交货—我不能再等了。 ";
				link.l1 = "好的, 我接受这个任务。 ";
				link.l1.go = "Fraht_LevelUp_Go";
				link.l2 = "很抱歉让你失望, 但我现在无法做到。 ";
				link.l2.go = "Fraht_LevelDown";
				SetNull2StoreGood(rColony, sti(pchar.questTemp.WPU.Fraht.Goods));
			break;
		}
	break;
		
	case "Fraht_LevelDown":
		DialogExit();
		pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count)-1;//скрутим счeтчик
	break;
		
	case "Fraht_LevelUp_Go":
		dialog.text = "太好了! 我很高兴你同意了。 希望很快能再见到你。 ";
		link.l1 = "当然, " + GetAddress_FormToNPC(NPChar) + "。 ";
		link.l1.go = "exit";
		pchar.questTemp.WPU.Fraht = "begin";
		pchar.questTemp.WPU.Fraht.LevelUp = "true";
		pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count) + 1;
		pchar.questTemp.WPU.Fraht.TargetPortmanID = pchar.questTemp.WPU.Fraht.StartCity +"_portman";//ИД портмана
		iGoods = pchar.questTemp.WPU.Fraht.Goods;
		ReOpenQuestHeader("Fraht");
		AddQuestRecord("Fraht", "8");
		AddQuestUserData("Fraht", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money)));
		AddQuestUserData("Fraht", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.StartCity+"Gen"));
		AddQuestUserData("Fraht", "sGoods", GetGoodsNameAlt(iGoods));
		AddQuestUserData("Fraht", "sGoodQty", FindRussianQtyString(sti(pchar.questTemp.WPU.Fraht.GoodsQty)));
		AddQuestUserData("Fraht", "sText", pchar.questTemp.WPU.Current1.Add);
		SetFunctionTimerCondition("FrahtTimeLevelUp_Over", 0, 0, 30, false);
	break;
	
	case "Fraht_completeLevelUp":
	ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
	if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//провeрка на наличиe корабля в порту
	{
		iGoods = makeint(pchar.questTemp.WPU.Fraht.Goods);
		amount = sti(pchar.questTemp.WPU.Fraht.GoodsQty) - GetSquadronGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods));
		if (amount > 0)
		{
			dialog.text = "你在开玩笑吗? 你没有我订购的货物数量! ";
			link.l1 = "对不起, 是我的错...";
			link.l1.go = "exit";
		}
		else
		{
			dialog.text = "好吧, 你本应交付一批" + GetGoodsNameAlt(iGoods) + ", 数量为" + FindRussianQtyString(pchar.questTemp.WPU.Fraht.GoodsQty) + "。 太好了, 非常感谢。 这是你的报酬 - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money)) + "。 ";
			link.l1 = "与你做生意很愉快, " + GetAddress_FormToNPC(NPChar) + "! ";
			link.l1.go = "Fraht_completeLevelUp_1";
		}
	}
	else
	{
		dialog.text = "我在港口没看到你的船。 现在离开, 以后再来见我 - 然后我们再谈。 ";
		link.l1 = "我会那样做的。 ";
		link.l1.go = "exit";
	}
	break;
	
	case "Fraht_completeLevelUp_1":
		pchar.quest.FrahtTimeLevelUp_Over.over = "yes";//снять таймер
		AddQuestRecord("Fraht", "2");
		CloseQuestHeader("Fraht");
		RemoveCharacterGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods), sti(pchar.questTemp.WPU.Fraht.GoodsQty));
		AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Fraht.Money));
		DeleteAttribute(pchar, "questTemp.WPU.Fraht.TargetPortmanID");
		DeleteAttribute(pchar, "questTemp.WPU.Current1"); // лесник  Current1 вместо Current
		DeleteAttribute(pchar, "questTemp.WPU.Fraht.LevelUp");
		pchar.questTemp.WPU.Fraht = "complete";
		AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
		AddCharacterExpToSkill(pchar, "Commerce", 200);//торговля
		AddCharacterExpToSkill(pchar, "Leadership", 150);//авторитет
		AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		ChangeCharacterComplexReputation(pchar,"nobility", 2);
		ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Fraht.Nation), 2);
		DialogExit();
	break;
	
//----------------------------------------задания 2 уровня эскорт ------------------------------------------

	case "Escort_LevelUp":
		pchar.questTemp.WPU.Escort.LevelUp = "true";//установим атрибут
		pchar.questTemp.WPU.Escort.StartCity = npchar.city;//город квестодателя
		pchar.questTemp.WPU.Escort.Nation = npchar.nation;//нация квестодателя
		pchar.questTemp.WPU.Escort.EnemyNation = GetEnemyNationToMainCharacter();//вражеская нация
		i = 0;
		while (sti(pchar.questTemp.WPU.Escort.EnemyNation) == PIRATE)
		{
			pchar.questTemp.WPU.Escort.EnemyNation = GetEnemyNationToMainCharacter();
			i++;
			if(i > 5) pchar.questTemp.WPU.Escort.EnemyNation = FindEnemyNation2NationWithoutPirates(sti(pchar.BaseNation));
		}
		switch (hrand(2))
		{
			case 0://приключения на необитаемых островах
				pchar.questTemp.WPU.Current.TargetIslandID = DesIsland();//выбор необитайки
				while (!isLocationFreeForQuests(pchar.questTemp.WPU.Current.TargetIslandID)) pchar.questTemp.WPU.Current.TargetIslandID = DesIsland();
				pchar.questTemp.WPU.Escort.ShipType = Escort_ShipType();//выбор корабля
				pchar.questTemp.WPU.Escort.ShipName = GenerateRandomNameToShip(sti(pchar.nation));//имя корабля
				pchar.questTemp.WPU.Escort.TargetPortmanID = pchar.questTemp.WPU.Escort.StartCity +"_portman";//ИД портмана
				pchar.questTemp.WPU.Escort.ShipBaseName = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.questTemp.WPU.Escort.ShipType), "Name") + "Gen"));
				dialog.text = "这场灾难发生在十天前...一支驶往我们殖民地的商船队遭到了海盗袭击。 狂风暴雨迫使海盗撤退, 但商船却四散开来, 彼此失去了联系。 最终, 除了一艘船外, 所有船只都抵达了不同的港口。 \n" + pchar.questTemp.WPU.Escort.ShipBaseName + "'"+ pchar.questTemp.WPU.Escort.ShipName +"'失踪了, 它的命运仍然未知。 据推测, 它可能在无人居住的 " + XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID) + " 岛附近被发现。 我请求你前往那里, 查明这艘失踪船只的情况, 如果它还幸存, 就把它带回我们的港口。 工作完成后, 我们会决定你的报酬, 但我向你保证, 这将是值得的。 ";
				link.l1 = "当然, 我同意! ";
				link.l1.go = "Escort_LevelUp_1";
				link.l2 = "对不起, 但这项工作不适合我。 恐怕我要拒绝。 ";
				link.l2.go = "Escort_LevelUp_exit";
			break;
			case 1://在当前岛屿附近保护商队免受海盗袭击
				pchar.questTemp.WPU.Current.TargetIslandID = Islands[GetCharacterCurrentIsland(PChar)].id;//当前岛屿
				pchar.questTemp.WPU.Escort.TargetPortmanID = pchar.questTemp.WPU.Escort.StartCity +"_portman";//港口管理员ID
				dialog.text = "一支贸易商队本应抵达我们的殖民地, 但就在进入港口之前, 它遭到了海盗的袭击。 战斗正在进行中。 它在堡垒大炮的射程之外, 而且我目前没有可用的护航船只, 因此无法为可怜的商人提供任何帮助。 你是一位勇敢的船长, 因此我请求你介入并帮助商人击退袭击! 你会这么做吗? ";
				link.l1 = "当然! 这是荣誉问题! ";
				link.l1.go = "Escort_LevelUp_2";
				link.l2 = "对不起, 但这项工作不适合我。 恐怕我要拒绝。 ";
				link.l2.go = "Escort_LevelUp_exit";
			break;
			case 2://встретить и довести
				pchar.questTemp.WPU.Escort.ShipName = GenerateRandomNameToShip(sti(pchar.nation));
				pchar.questTemp.WPU.Escort.ShipType = Escort_ShipType();
				pchar.questTemp.WPU.Escort.City = findCurrentCity1(npchar);//город, откуда забрать
				pchar.questTemp.WPU.Escort.TargetPortmanID = pchar.questTemp.WPU.Escort.City +"_portman";//ИД портмана
				sld = characterFromId(pchar.questTemp.WPU.Escort.TargetPortmanID);
				pchar.questTemp.WPU.Escort.Nation = sld.nation;//нация получателя
				pchar.questTemp.WPU.Current.TargetIslandID = GetCharacterCurrentIslandId(npchar);//ИД целевого ареала
				pchar.questTemp.WPU.Escort.DaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Escort.StartCity), GetArealByCityName(pchar.questTemp.WPU.Escort.City));//расстояние в днях
				pchar.questTemp.WPU.Escort.Money = sti(pchar.questTemp.WPU.Escort.DaysQty)*2000+20000;
				pchar.questTemp.WPU.Escort.Chance = rand(1);
				dialog.text = "我们殖民地订购的一艘载有武器和弹药的船只最近抵达了 " + XI_ConvertString(pchar.questTemp.WPU.Escort.City) + " 殖民地。 它的护航船触礁, 严重受损, 短期内无法离开港口。 我们不能冒险让一艘载有如此货物的贸易船单独航行。 \n你同意将它护送到我们的殖民地吗? 工作报酬定为 " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)) + "。 ";
				link.l1 = "当然, 我同意! ";
				link.l1.go = "Escort_LevelUp_0";
				link.l2 = "对不起, 但这项工作不适合我。 恐怕我要拒绝。 ";
				link.l2.go = "Escort_LevelUp_exit";
			break;
		}
	break;
	
	case "Escort_LevelUp_exit":
		dialog.text = "真遗憾, 确实。 我其实一直指望着你...";
		link.l1 = "我也很抱歉。 好吧, " + GetAddress_FormToNPC(NPChar) + ", 后会有期。 ";
		link.l1.go = "exit";
		pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)-1;//递减计数器
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
	break;
	
	case "Escort_LevelUp_0":
		dialog.text = "太好了! 我就知道我可以指望你。 请尽量快点。 我想 " + FindRussianDaysString(pchar.questTemp.WPU.Escort.DaysQty) + " 足够到达 " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Escort.City + "Gen") + "。 给你, 拿着这些能证明你身份的凭证。 一路顺风, 船长! ";
		link.l1 = "别担心, 我不会让你失望的。 ";
		link.l1.go = "Escort_LevelUp_0_go";
	break;
	
	case "Escort_LevelUp_0_go":
		ReOpenQuestHeader("Escort");
		AddQuestRecord("Escort", "19");
		AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)));
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.City));
		AddQuestUserData("Escort", "sDay", FindRussianDaysString(pchar.questTemp.WPU.Escort.DaysQty));
		SetFunctionTimerCondition("EscortArsenalShip_Over", 0, 0, sti(pchar.questTemp.WPU.Escort.DaysQty)+1, false);
		DialogExit();
		pchar.questTemp.WPU.Escort = "begin";
		pchar.questTemp.WPU.Escort.LevelUp_0 = "true";
		pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)+1;
	break;
	
	case "Escort_LUGo_0":
	ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
	if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//检查港口是否有船
	{
		pchar.quest.EscortArsenalShip_Over.over = "yes";
		dialog.text = "终于! 那艘船已经碍眼很久了。 那就接管吧。 船的名字是 " + pchar.questTemp.WPU.Escort.ShipName + ", 它的船长会立即通知你的到来。 ";
		link.l1 = "告诉他让他的船准备好航行 - 我会尽早离开。 ";
		link.l1.go = "Escort_LUGo_01";
	}
	else
	{
		dialog.text = "我在港口没看到你的船。 现在先离开, 以后再来找我 - 到时候我们再谈。 ";
		link.l1 = "我会照做的。 ";
		link.l1.go = "exit";
	}
	break;
	
	case "Escort_LUGo_01"://添加同伴
		int iShipType = sti(pchar.questTemp.WPU.Escort.ShipType);
		sTemp = pchar.questTemp.WPU.Escort.ShipName;
		sld = GetCharacter(NPC_GenerateCharacter("ArsenalShipCaptain", "citiz_41", "man", "man", 15, sti(pchar.nation), -1, true, "quest"));
		FantomMakeSmallSailor(sld, iShipType, sTemp, CANNON_TYPE_CANNON_LBS16, 65, 22, 24, 35, 33);
		SetFantomParamFromRank(sld, 15, true); 
		SetCaptanModelByEncType(sld, "war");
		SetCharacterGoods(sld, GOOD_FOOD, 500);
		SetCharacterGoods(sld, GOOD_BALLS, 5000);
		SetCharacterGoods(sld, GOOD_GRAPES, 3000);
		SetCharacterGoods(sld, GOOD_KNIPPELS, 3000);
		SetCharacterGoods(sld, GOOD_BOMBS, 5000);
		SetCharacterGoods(sld, GOOD_POWDER, 10000);
		SetCharacterGoods(sld, GOOD_WEAPON, 3000);
		sld.CompanionEnemyEnable = false; //永远是朋友
		SetCompanionIndex(pchar, -1, sti(sld.index));
		SetCharacterRemovable(sld, false);
		sld.loyality = MAX_LOYALITY;
		sld.Dialog.Filename = "Common_portman.c";
		sld.dialog.currentnode = "Escort_companion";
		DialogExit();
		AddQuestRecord("Escort", "20");
		AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
		pchar.quest.Escort_fail.win_condition.l1 = "NPC_Death";//护送对象沉没时中断
		pchar.quest.Escort_fail.win_condition.l1.character = "ArsenalShipCaptain";
		pchar.quest.Escort_fail.function = "EscortArsenalShip_failed";
		SetFunctionTimerCondition("EscortArsenalShipGo_Over", 0, 0, sti(pchar.questTemp.WPU.Escort.DaysQty)+6, false);
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_0");
		pchar.questTemp.WPU.Escort.LevelUpGo_0 = "true";
		if (sti(pchar.questTemp.WPU.Escort.Chance) == 0) EnemyNationHunterOnMap(true);//快速拦截者
		else FrahtHunterOnSea();
	break;
	
	case "Escort_LUGo_complete":
	ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
	if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//检查港口是否有船
	{
		pchar.quest.Escort_fail.over = "yes";
		pchar.quest.EscortArsenalShipGo_Over.over = "yes";
		dialog.text = "太棒了! 你再次证明了可以信赖。 谢谢你出色地完成了工作。 请接受你的报酬 - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)) + "。 别忘了偶尔来看我 - 像你这样的船长总是有工作可做的。 ";
		link.l1 = "很高兴听到你这么说, " + GetAddress_FormToNPC(NPChar) + "! 当然, 我们的合作会继续。 致以最美好的祝愿! ";
		link.l1.go = "Escort_LUGo_complete_1";
	}
	else
	{
		dialog.text = "我在港口没看到你的船。 现在先离开, 以后再来找我 - 到时候我们再谈。 ";
		link.l1 = "好吧, 我会照做的。 ";
		link.l1.go = "exit";
	}
	break;
	
	case "Escort_LUGo_complete_1":
		RemoveCharacterCompanion(Pchar, characterFromID("ArsenalShipCaptain"));
		sld = characterFromId("ArsenalShipCaptain");
		sld.lifeday = 0;//以防万一
		AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Escort.Money));
		ChangeCharacterComplexReputation(pchar,"nobility", 2);
		ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Escort.Nation), 2);
		AddQuestRecord("Escort", "24");
		AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
		CloseQuestHeader("Escort");
		DialogExit();
		pchar.questTemp.WPU.Escort = "complete";
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUpGo_0");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
		AddComplexSeaExpToScill(100, 100, 100, 0, 100, 0, 0);
		AddComplexSelfExpToScill(30, 30, 30, 30);
		AddCharacterExpToSkill(pchar, "Leadership", 100);//权威
		SaveCurrentNpcQuestDateParam(npchar, "work_date");
	break;
	
	case "Escort_LevelUp_1":
		dialog.text = "那我祝你一路平安。 请不要拖延你的搜索! 那艘船的船员可能需要立即帮助。 ";
		link.l1 = "知道了。 我今天就起航! ";
		link.l1.go = "Escort_LevelUp_1_select";
	break;
	
	case "Escort_LevelUp_1_select"://выберем приключение
		switch (rand(2))
		{
			case 0://весь побитый и остался без мачты
				pchar.quest.DisasterShip_WM.win_condition.l1 = "location";
				pchar.quest.DisasterShip_WM.win_condition.l1.location = pchar.questTemp.WPU.Current.TargetIslandID;
				pchar.quest.DisasterShip_WM.function = "CreateDisasterShip_WithoutMasts";
				pchar.questTemp.WPU.Escort.LevelUp_1WM = "true";
			break;
			case 1://ведет бой с пиратусами в шторме
				pchar.quest.DisasterShip_VSP.win_condition.l1 = "location";
				pchar.quest.DisasterShip_VSP.win_condition.l1.location = pchar.questTemp.WPU.Current.TargetIslandID;
				pchar.quest.DisasterShip_VSP.function = "CreateDisasterShip_VSPirate";
				for (i=0; i<MAX_ISLANDS; i++)//устроим шторм
				{				
					if (Islands[i].id == pchar.questTemp.WPU.Current.TargetIslandID)
					{
					Islands[i].alwaysStorm = true; 
					Islands[i].storm = true;
					Islands[i].tornado = true; 
					}
				}
				pchar.questTemp.WPU.Escort.LevelUp_1VSP = "true";
			break;
			case 2://потонул
				pchar.questTemp.WPU.Current.TargetIslandID.Shore = SelectQuestShoreLocationFromSea(pchar.questTemp.WPU.Current.TargetIslandID);
				pchar.quest.DisasterShip_S.win_condition.l1 = "location";
				pchar.quest.DisasterShip_S.win_condition.l1.location = pchar.questTemp.WPU.Current.TargetIslandID.Shore;
				pchar.quest.DisasterShip_S.function = "CreateDisasterShip_Crew";
				pchar.questTemp.WPU.Escort.LevelUp_1S = "true";
			break;
		}
		ReOpenQuestHeader("Escort");
		AddQuestRecord("Escort", "25");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sIsland", XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID));
		AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
		AddQuestUserData("Escort", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.City));
		SetFunctionTimerCondition("DesIsland_Over", 0, 0, 15, false);
		DialogExit();
		pchar.questTemp.WPU.Escort = "begin";
		pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)+1;
	break;
	
	case "Escort_LU1WM_complete":
	ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
	if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
	{
		dialog.text = "是的, 我已经接到通知。 干得好, " + GetAddress_Form(NPChar) + "! 你再次证明了你是我可以信赖的人。 领取你的奖励 - 30,000 比索。 \n记得时不时来看我 - 像你这样的人是无价的, 我总会为你找到合适的工作。 ";
		link.l1 = "很高兴听到你这么说, " + GetAddress_FormToNPC(NPChar) + "! 当然, 我们会进一步合作。 一切顺利! ";
		link.l1.go = "Escort_LU1WM_complete_1";
	}
	else
	{
		dialog.text = "我在港口没看到你的船。 现在先离开, 以后再来找我 - 到时候我们再谈。 ";
		link.l1 = "好吧, 我会照做的。 ";
		link.l1.go = "exit";
	}
	break;
	
	case "Escort_LU1WM_complete_1":
		sld = characterFromId("WMCaptain");
		sld.lifeday = 0;
		DialogExit();
		AddMoneyToCharacter(pchar, 30000);
		ChangeCharacterComplexReputation(pchar,"nobility", 5);
		ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Escort.Nation), 5);
		AddQuestRecord("Escort", "32");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sMoney", 30000);
		CloseQuestHeader("Escort");
		pchar.questTemp.WPU.Escort = "complete";
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1WM");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
		AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
		AddCharacterExpToSkill(pchar, "Repair", 300);//починка
		AddCharacterExpToSkill(pchar, "Commerce", 100);//торговля
		AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
		AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		SaveCurrentNpcQuestDateParam(npchar, "work_date");
	break;
	
	case "Escort_LU1VSP_complete":
	ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
	if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
	{
		dialog.text = "是的, 他已经告诉我与海盗的战斗以及你如何英勇地保卫他的船只。 干得好, " + GetAddress_Form(NPChar) + "! 你再次证明了你是我可以信赖的人。 领取你的奖励 - 50,000 比索。 \n记得时不时来看我 - 像你这样的人是无价的, 我总会为你找到合适的工作。 ";
		link.l1 = "很高兴听到你这么说, " + GetAddress_FormToNPC(NPChar) + "! 当然, 我们的合作会继续。 致以最美好的祝愿! ";
		link.l1.go = "Escort_LU1VSP_complete_1";
	}
	else
	{
		dialog.text = "我在港口没看到你的船。 现在先离开, 以后再来找我 - 到时候我们再谈。 ";
		link.l1 = "好吧, 我会照做的。 ";
		link.l1.go = "exit";
	}
	break;
	
	case "Escort_LU1VSP_complete_1":
		sld = characterFromId("WMCaptain");
		sld.lifeday = 0;
		DialogExit();
		AddMoneyToCharacter(pchar, 50000);
		ChangeCharacterComplexReputation(pchar,"nobility", 10);
		ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Escort.Nation), 6);
		AddQuestRecord("Escort", "32");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sMoney", 50000);
		CloseQuestHeader("Escort");
		pchar.questTemp.WPU.Escort = "complete";
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1VSP");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
		AddComplexSeaExpToScill(100, 150, 150, 100, 0, 0, 0);
		AddComplexSelfExpToScill(50, 50, 50, 50);
		AddCharacterExpToSkill(pchar, "Leadership", 100);//权威
		AddCharacterExpToSkill(pchar, "Fortune", 100);//运气
		SaveCurrentNpcQuestDateParam(npchar, "work_date");
	break;
	
	case "Escort_LU1VSP_completeSink":
		dialog.text = "多么悲惨的结局...愿上帝安息他们的灵魂。 ";
		link.l1 = "我已经尽我所能了, " + GetAddress_FormToNPC(NPChar) + "。 风暴让情况变得更糟。 ";
		link.l1.go = "Escort_LU1VSP_completeSink_1";
	break;
	
	case "Escort_LU1VSP_completeSink_1":
		dialog.text = "我相信, " + GetAddress_Form(NPChar) + ", 你已经尽了一切努力来拯救这艘船和那些不幸的水手。 但是唉...好吧, 请领取你的奖励 - 10000 比索 - 感谢你的服务。 ";
		link.l1 = "没什么可感谢我的, " + GetAddress_FormToNPC(NPChar) + "。 我真的很抱歉。 好吧, 再见。 ";
		link.l1.go = "Escort_LU1VSP_completeSink_2";
	break;
	
	case "Escort_LU1VSP_completeSink_2":
		DialogExit();
		AddMoneyToCharacter(pchar, 10000);
		ChangeCharacterComplexReputation(pchar,"nobility", 1);
		AddQuestRecord("Escort", "32");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sMoney", 10000);
		CloseQuestHeader("Escort");
		pchar.questTemp.WPU.Escort = "complete";
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1VSP");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
		AddComplexSeaExpToScill(50, 50, 50, 50, 0, 0, 0);
		AddCharacterExpToSkill(pchar, "Fortune", 50);//运气
		SaveCurrentNpcQuestDateParam(npchar, "work_date");
	break;
	
	case "Escort_LU1S_complete":
		dialog.text = "是的, 他已经告诉我你如何与红皮肤的异教徒战斗, 然后又与一艘海盗船战斗 - 像个真正的英雄。 干得好, " + GetAddress_Form(NPChar) + "! 你再次证明了你是我可以信赖的人。 \n领取你的奖励 - 40,000 比索。 记得时不时来看我 - 像你这样的人是无价的, 我总会为你找到合适的工作。 ";
		link.l1 = "很高兴听到你这么说, " + GetAddress_FormToNPC(NPChar) + "! 当然, 我们的合作会继续。 致以最美好的祝愿! ";
		link.l1.go = "Escort_LU1S_complete_1";
	break;
	
	case "Escort_LU1S_complete_1":
		sld = characterFromId("WMCaptain");
		sld.lifeday = 0;
		DialogExit();
		AddMoneyToCharacter(pchar, 40000);
		ChangeCharacterComplexReputation(pchar,"nobility", 8);
		ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Escort.Nation), 3);
		AddQuestRecord("Escort", "32");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sMoney", 40000);
		CloseQuestHeader("Escort");
		pchar.questTemp.WPU.Escort = "complete";
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1S");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
		AddComplexSeaExpToScill(100, 150, 150, 100, 0, 0, 0);
		AddComplexSelfExpToScill(100, 100, 100, 100);
		AddCharacterExpToSkill(pchar, "Leadership", 100);//权威
		AddCharacterExpToSkill(pchar, "Fortune", 100);//运气
		SaveCurrentNpcQuestDateParam(npchar, "work_date");
	break;
	
	case "Escort_LevelUp_2":
		dialog.text = "我就知道我可以指望你。 祝你好运, 船长! 整个殖民地都祝你胜利! ";
		link.l1 = "我会努力不辜负你的期望。 我现在就起航, 愿上帝帮助我们! ";
		link.l1.go = "Escort_LevelUp_2_go";
	break;
	
	case "Escort_LevelUp_2_go":
		ReOpenQuestHeader("Escort");
		AddQuestRecord("Escort", "41");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		SetFunctionTimerCondition("CaravanNearIsland_Over", 0, 0, 2, false);
		pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)+1;
		pchar.quest.CaravanNearIsland_Start.win_condition.l1 = "location";
		pchar.quest.CaravanNearIsland_Start.win_condition.l1.location = pchar.questTemp.WPU.Current.TargetIslandID;
		pchar.quest.CaravanNearIsland_Start.function = "CreateCaravanNearIsland";
		pchar.questTemp.WPU.Escort.LevelUp_2 = "true";
		pchar.questTemp.WPU.Escort = "begin";
		DialogExit();
	break;
	
	case "Escort_LU2_complete":
		switch (sti(pchar.questTemp.WPU.Escort.LevelUp_2.Qty))
		{
			case 1:
				pchar.questTemp.WPU.Escort.LevelUp_2.Money = 10000;
				dialog.text = "是的, 整个城镇都在观看你的战斗。 可怜的商人, 我真为他们感到难过。 好吧, 至少你设法拯救了一艘船, 所以你应得 10000 比索的奖励。 请接受它 - 感谢你的帮助。 ";
				link.l1 = "没什么可感谢我的...遗憾的是我没有决定性地赢得那场战斗, 但我已经尽了全力。 再见, " + GetAddress_FormToNPC(NPChar) + "。 ";
				link.l1.go = "Escort_LU2_complete_1";
			break;
			case 2:
				pchar.questTemp.WPU.Escort.LevelUp_2.Money = 25000;
				dialog.text = "是的, 整个城镇都在观看你进行的战斗 - 我必须说, 你打得非常熟练。 那个可怜的商人, 我真为他感到难过...但如果不是你, 他们谁也活不下来, 所以你应得 25000 比索的奖励。 请接受它 - 感谢你的帮助。 ";
				link.l1 = "好吧, 谢谢你对我行动的高度评价, 但我不认为那是我最好的战斗 - 我还是失去了一艘船。 唉, 命运就是命运, 对此无能为力。 再见, " + GetAddress_FormToNPC(NPChar) + "。 ";
				link.l1.go = "Escort_LU2_complete_1";
			break;
			case 3:
				pchar.questTemp.WPU.Escort.LevelUp_2.Money = 50000;
				dialog.text = "是的, 整个城镇都在观看你进行的战斗 - 你太棒了! 你刚刚摧毁了整个那群肮脏的海盗中队! 现在他们已经吸取了教训 - 可惜这对他们再也没有帮助了。 你的奖励是 50000 比索 - 请接受它。 ";
				link.l1 = "谢谢你对我行动的高度评价! 随时乐意帮忙。 现在, " + GetAddress_FormToNPC(NPChar) + ", 请允许我告辞。 ";
				link.l1.go = "Escort_LU2_complete_1";
			break;
		}
	break;
	
	case "Escort_LU2_complete_1":
		iTemp = sti(pchar.questTemp.WPU.Escort.LevelUp_2.Qty);
		DialogExit();
		Group_DeleteGroup("CaravanShip");
		AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Escort.LevelUp_2.Money));
		ChangeCharacterComplexReputation(pchar,"nobility", iTemp*2);
		ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Escort.Nation), iTemp);
		AddQuestRecord("Escort", "32");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sMoney", sti(pchar.questTemp.WPU.Escort.LevelUp_2.Money));
		CloseQuestHeader("Escort");
		AddCharacterExpToSkill(pchar, "Sailing", iTemp*35);//навигация
		AddCharacterExpToSkill(pchar, "Accuracy", iTemp*50);//меткость
		AddCharacterExpToSkill(pchar, "Cannons", iTemp*50);//орудия
		AddCharacterExpToSkill(pchar, "Grappling", iTemp*35);//абордаж
		AddCharacterExpToSkill(pchar, "Leadership", iTemp*40);//авторитет
		AddCharacterExpToSkill(pchar, "Fortune", iTemp*35);//везение
		AddCharacterExpToSkill(pchar, "FencingL", iTemp*35);//лёгкое оружие
		AddCharacterExpToSkill(pchar, "FencingS", iTemp*35);//среднее оружие
		AddCharacterExpToSkill(pchar, "FencingH", iTemp*35);//тяжелое оружие
		AddCharacterExpToSkill(pchar, "Pistol", iTemp*35); //пистоли
		pchar.questTemp.WPU.Escort = "complete";
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_2");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
		SaveCurrentNpcQuestDateParam(npchar, "work_date");
	break;
	
		case "PortmanQuest_NF":
			dialog.text = "嗯, 那很糟糕。 在这种情况下, 你为我工作是不可能的了。 ";
			link.l1 = "明白了。 这就是我想说的...";
			link.l1.go = "node_2";
		break;
		
		//烧毁的船
		case "BurntShip2":
			dialog.text = "真遗憾, 船长...很遗憾你不愿意帮助我。 ";
			link.l1 = "这不是我愿不愿意的问题, 我的朋友。 你必须理解。 再见。 ";
			link.l1.go = "exit";
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;
		break;
		
		case "BurntShip4":
			dialog.text = "你怎么了, 船长? ! 你不觉得羞耻吗? ! 你怎么能这样? ! 我知道我在做什么, 我已经服务多年了。 有保险合同, 保险公司愿意赔偿, 我向你保证, 保险金额相当可观。 ";
			link.l1 = "你有什么问题, 先生? 火药舱爆炸了, 有人员伤亡, 现在你必须为你的疏忽接受审判? ";
			link.l1.go = "BurntShip5";
		break;
		
		case "BurntShip5":
			sCapitainId = GenerateRandomName(sti(NPChar.nation), "man");
			
			dialog.text = "不! 当然不是! 上帝保佑我的灵魂, 否则我会掉脑袋的。 货舱完全是空的, 感谢上帝, 圣母玛利亚! \n" +
				"问题是这艘船属于...或者说曾经属于 " + sCapitainId + " 先生, 所有加勒比人都知道他。 它是在欧洲特别订购建造的, 具有非凡的性能。 " +
				"而这个船主太骄傲了, 到处吹嘘, 有点笨蛋, 上帝原谅我...我现在该怎么跟他说? 我最好自杀, 我发誓...";
			link.l1 = "哦, 现在我明白问题所在了。 这艘船有什么特别之处? 它有什么不寻常的特点让它的主人如此自豪? ";
			link.l1.go = "BurntShip6";
			
			NPChar.Quest.BurntShip.ShipOwnerName = sCapitainId;
		break;
		
		case "BurntShip6":
			BurntShipQuest_FillStartParams(NPChar);
			
			attrL = NPChar.Quest.BurntShip.ShipAttribute;
			iTest = sti(NPChar.Quest.BurntShip.ShipType);
			
			switch(attrL)
			{
				case "speedrate":
					attrL = "他的 " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].Name + "Acc")) + " 的风速超过 " + NPChar.Quest.BurntShip.ShipNeededValue + " 节。 那是私掠船的骄傲...现在他只会让他的手下在院子里把我吊死。 是什么魔鬼把他和那艘海盗船带到我们港口的...";
				break;
				
				case "turnrate":
					attrL = "他的 " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].Name + "Acc")) + " 的机动性超过 " + NPChar.Quest.BurntShip.ShipNeededValue + " 单位。 那是战士的骄傲...现在他只会把我鞭打到死。 是什么魔鬼建议他把船留在那里...";
				break;
				
				case "capacity":
					attrL = "他的 " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].Name + "Acc")) + " 的载重量超过 " + NPChar.Quest.BurntShip.ShipNeededValue + " 单位。 贪婪是不好的, 我告诉你。 现在他只会在法庭上把我分尸。 是什么魔鬼建议他把船留在那里...";
				break;
			}
			
			dialog.text = attrL;
			link.l1 = "码头的人怎么说? 真的不可能在这里再建一艘吗? ";
			link.l1.go = "BurntShip7";
		break;
		
		case "BurntShip7":
			dialog.text = "没人能。 我甚至去了附近的岛屿问当地人。 他们说在特雷索岛有一位著名的大师, 他几乎能在造船方面做到一切。 但特雷索岛太远了。 我只剩下指望像你这样的自由船长的帮助了。 也许你会碰巧为我找到这样一艘船。 剩下的我会处理\n" +
				"我会慷慨地感谢你, 保险公司也会同样感谢你。 你知道, 这件事很不寻常。 谁会想惹这样一个有权势的人呢? ";
			link.l1 = "是啊, 这可不容易。 我有多少时间? ";
			link.l1.go = "BurntShip8";
			link.l2 = "不, 朋友, 我不能卷入这样的事情。 更不用说根本无法保证存在具有这种参数的船只了。 对不起...";
			link.l2.go = "BurntShip2";
		break;
		
		case "BurntShip8":
			dialog.text = "感谢上帝, 还有时间。 船主航行到欧洲去了, 至少要半年后才会回来。 ";
			link.l1 = "好吧, 我想我能行。 我会给你带来一艘类似的船。 但请记住 - 如果你选择太吝啬, 我会在你眼前把它烧掉! ";
			link.l1.go = "BurntShip9";
		break;
		
		case "BurntShip9":
			dialog.text = "你这是什么意思, 船长? 当然, 我知道你需要时间 - 这不是在最近的水坑里找一艘随机的船...把船给我们, 我们会尽力而为, 你可以相信这一点...";
			link.l1 = "我希望如此...好吧, 等我好消息。 再见。 ";
			link.l1.go = "BurntShip9_exit";
		break;
		
		case "BurntShip9_exit":
			attrL = "BurntShipQuest_TimeIsOver_" + NPChar.Id;
			PChar.Quest.(attrL).win_condition.l1 = "Timer";
			PChar.Quest.(attrL).win_condition.l1.date.day = GetAddingDataDay(0, 6, 0);
			PChar.Quest.(attrL).win_condition.l1.date.month = GetAddingDataMonth(0, 6, 0);
			PChar.Quest.(attrL).win_condition.l1.date.year = GetAddingDataYear(0, 6, 0);
			PChar.Quest.(attrL).function = "BurntShipQuest_TimeIsOver";
			PChar.Quest.(attrL).PortmanId = NPChar.id;
			
			attrL = NPChar.Quest.BurntShip.ShipAttribute;
			
			iTest = sti(NPChar.Quest.BurntShip.ShipType);
			
			switch(attrL)
			{
				case "speedrate":
					attrL = "速度。 " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].name + "Gen")) + " 的风速必须至少为 " + NPChar.Quest.BurntShip.ShipNeededValue;
				break;
				
				case "turnrate":
					attrL = "机动性。 " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].name + "Gen")) + " 的机动性必须不低于 " + NPChar.Quest.BurntShip.ShipNeededValue;
				break;
				
				case "capacity":
					attrL = "货舱。 " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].name + "Gen")) + " 的货舱必须不小于 " + NPChar.Quest.BurntShip.ShipNeededValue;
				break;
			}
			
			sTitle = "BurntShipQuest" + NPChar.location;
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "BurntShipQuest", "1");
			AddQuestUserDataForTitle(sTitle, "cityName", XI_ConvertString("Colony" + NPChar.city + "Dat"));
			AddQuestUserData(sTitle, "portmanName", GetFullName(NPChar));
			AddQuestUserData(sTitle, "cityName", XI_ConvertString("Colony" + NPChar.city + "Gen"));
			AddQuestUserData(sTitle, "text", attrL);
			
			NPChar.Quest.BurntShip.LastPortmanName = GetFullName(NPChar); // 记住名字
			
			DialogExit();
		break;
		
		// 情况是没有按时完成
		case "BurntShip10":
			dialog.text = "你想谈什么? ";
			link.l1 = "前港口管理员, " + NPChar.Quest.BurntShip.LastPortmanName + " 先生在哪里? 我和他有生意。 ";
			link.l1.go = "BurntShip11";
		break;
		
		case "BurntShip11":
			dialog.text = "他已经不在了。 想象一下 - 他烧毁了属于一个知名人士的船, 还私吞了保险金。 当当局还在整理这一切时, 他辞职溜到欧洲去了。 真是个骗子, 不是吗? ";
			link.l1 = "是啊, 我听说过那个故事。 对不起, 我得走了。 ";
			link.l1.go = "BurntShip11_exit";
		break;
		
		case "BurntShip11_exit":
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			sTitle = "BurntShipQuest" + NPChar.location;
			AddQuestRecordEx(sTitle, "BurntShipQuest", "2");
			AddQuestUserData(sTitle, "portmanName", NPChar.Quest.BurntShip.LastPortmanName);
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(NPChar, "Quest.BurntShip");
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;
			
			DialogExit();
		break;
		
		// 未过期 - 检查船只
		case "BurntShip12":
			dialog.text = "你想谈什么? ";
			link.l1 = "我给你带来了一艘不寻常的船, 正是你要的。 现在我期待我的奖励。 ";
			link.l1.go = "BurntShip14";
			link.l2 = "你知道, " + GetFullName(NPChar) + ", 我仍然没有找到任何一艘类似于你需要的船。 我想我会放弃这份工作。 抱歉如果我让你失望了...";
			link.l2.go = "BurntShip13";
		break;
		
		case "BurntShip13":
			dialog.text = "真遗憾, 船长...很遗憾你不愿意帮助我。 ";
			link.l1 = "这不是我愿不愿意的问题, 我的朋友。 请理解。 再见。 ";
			link.l1.go = "BurntShip13_exit";
		break;
		
		case "BurntShip13_exit":
			sTitle = "BurntShipQuest" + NPChar.location;
			CloseQuestHeader(sTitle);
			
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			DeleteAttribute(NPChar, "Quest.BurntShip");
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;
			
			DialogExit();
		break;
		
		case "BurntShip14":
			dialog.text = "哦, 真的! 我们的新船叫什么名字? ";
			
			sTitle = NPChar.Quest.BurntShip.ShipAttribute;
			ok = (sFrom_sea == "") || (Pchar.location.from_sea == sFrom_sea);
			
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				for(i = 1; i < COMPANION_MAX; i++)
				{
					cn = GetCompanionIndex(PChar, i);
					
					if(cn > 0)
					{
						chref = GetCharacter(cn);
						
						sld = &RealShips[sti(chref.ship.type)];
						
						if(GetRemovable(chref) && sti(sld.basetype) == sti(NPchar.Quest.BurntShip.ShipType) &&
							stf(sld.(sTitle)) >= stf(NPChar.Quest.BurntShip.ShipNeededValue))
						{
							attrL = "l" + i;
							Link.(attrL) = chref.Ship.Name;
							Link.(attrL).go = "BurntShip15";
						}
					}
				}
			}
			
			link.l99 = "对不起, 我稍后再来。 ";
			link.l99.go = "exit";
		break;
		
		case "BurntShip15":
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Sailing", 300);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			dialog.text = "哦, 船长, 我很高兴你没有让我失望! 你是多么 " + GetSexPhrase("优秀的年轻人","优秀的年轻女士") + ", 你简直救了我的命...请你过几天来收钱好吗? 你知道, 我需要和保险公司办理手续...同时, 你可以对船进行次要的维修 - 你知道, 更换船帆, 修补漏洞, 倾斜也无妨...";
			link.l99 = "我答应过如果你想骗我, 我会对船做些 nasty 的事情。 你忘了吗? ";
			link.l99.go = "BurntShip16";
		break;
		
		case "BurntShip16":
			dialog.text = "不, 不, 当然没有! 我会信守诺言的, 别担心。 你看, 知道为了所谓的伪装新船会有更多费用, 我把旧船的保险金借出去收利息了。 希望你能理解...";
			link.l1 = "当钱进入我的箱子时, 我会更好地理解。 再见。 ";
			link.l1.go = "BurntShip16_exit";
		break;
		
		case "BurntShip16_exit":
			sTitle = "BurntShipQuest" + NPChar.location;
			AddQuestRecordEx(sTitle, "BurntShipQuest", "3");
			
			NPChar.Quest.BurntShip.TwoDaysWait = true;
			SaveCurrentNpcQuestDateParam(NPChar, "Quest.BurntShip.TwoDaysWait"); // 记住日期
			
			sTitle = "BurntShipQuest" + NPChar.Id;
			PChar.Quest.(sTitle).over = "yes"; // 结束时间中断
			
			DialogExit();
		break;
		
		case "BurntShip17":
			dialog.text = "你想谈什么? ";
			link.l1 = "我来领取我的奖励。 我仍然有你需要的船只。 ";
			link.l1.go = "BurntShip18";
		break;
		
		case "BurntShip18":
			dialog.text = "请你提醒我它的名字好吗? 我的记忆不像以前了 - 你知道, 所有这些麻烦...";
			
			sTitle = NPChar.Quest.BurntShip.ShipAttribute;
			ok = (sFrom_sea == "") || (Pchar.location.from_sea == sFrom_sea);
			
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				for(i = 1; i < COMPANION_MAX; i++)
				{
					cn = GetCompanionIndex(PChar, i);
					
					if(cn > 0)
					{
						chref = GetCharacter(cn);
						
						sld = &RealShips[sti(chref.ship.type)];
						
						if(GetRemovable(chref) && sti(sld.basetype) == sti(NPchar.Quest.BurntShip.ShipType) &&
							stf(sld.(sTitle)) >= stf(NPChar.Quest.BurntShip.ShipNeededValue))
						{
							attrL = "l" + i;
							Link.(attrL) = chref.Ship.Name;
							Link.(attrL).go = "BurntShip19_" + i;
						}
					}
				}
			}
			
			link.l99 = "对不起, 我稍后再来。 ";
			link.l99.go = "exit";
		break;
		
		case "BurntShip19":
			sld = &Characters[GetCompanionIndex(PChar, sti(NPChar.Quest.BurntShip.ShipCompanionIndex))];
			cn = GetShipSellPrice(sld, CharacterFromID(NPChar.city + "_shipyarder")) * 3;
			rRealShip = GetRealShip(GetCharacterShipType(sld));
			if (sti(rRealShip.Stolen)) cn *= 3;
			
			dialog.text = "是的, 完美。 我准备给你你的奖励, " + FindRussianMoneyString(cn) + " 箱。 不幸的是, 我不能支付更多。 ";
			link.l1 = "哦不, 这个金额不适合我。 我确定这艘船要贵得多。 ";
			link.l1.go = "BurntShip21";
			link.l2 = "对的。 我很高兴能帮助你。 再见。 ";
			link.l2.go = "BurntShip20_exit";
			NPChar.Quest.BurntShip.Money = cn;
		break;
		
		case "BurntShip20_exit":
			TakeNItems(pchar, "chest", makeint(sti(NPChar.Quest.BurntShip.Money)/12000));
			Log_Info("你收到了信用箱");
			PlaySound("interface\important_item.wav");
			sTitle = "BurntShipQuest" + NPChar.location;
			AddQuestRecordEx(sTitle, "BurntShipQuest", "4");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "money", NPChar.Quest.BurntShip.Money);
			CloseQuestHeader(sTitle);
			
			ChangeCharacterComplexReputation(pchar,"nobility", 3);
			
			sld = &Characters[GetCompanionIndex(PChar, sti(NPChar.Quest.BurntShip.ShipCompanionIndex))];
			RemoveCharacterCompanion(PChar, sld);
			AddPassenger(PChar, sld, false);
			
			DeleteAttribute(NPChar, "Quest.BurntShip");
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;
			
			DialogExit();
		break;
		
		case "BurntShip21":
			dialog.text = "你在说什么, 船长? ! 相信我, 我知道我在说什么。 那笔钱可以给你买两艘那样的船! ";
			link.l1 = "我想我会留着它。 你知道, 我只是喜欢它...再见。 ";
			link.l1.go = "BurntShip21_exit";
		break;
		
		case "BurntShip21_exit":
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			
			sTitle = "BurntShipQuest" + NPChar.location;
			AddQuestRecordEx(sTitle, "BurntShipQuest", "5");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "money", NPChar.Quest.BurntShip.Money);
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(NPChar, "Quest.BurntShip");
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;
			
			DialogExit();
		break;
		
		//--> 港口管理员的迷你任务
		case "PortmanQuest":
			if (hRand(5) == 2)
			{	//任务追上并交付航海日志
				dialog.text = "一位船长把他的航海日志忘在我的办公室了。 真是个粗心大意的人! 我需要你追上他并把它还给他。 ";
				link.l1 = "哦, 那很容易...我接了! ";
				link.l1.go = "PortmanQuest_1";
				link.l2 = "不, 我不会处理那个。 实际上, 这是他自己的问题。 ";
				link.l2.go = "node_2";
			}
			else
			{	//任务寻找被盗船只
				dialog.text = "一艘船从那里的系泊处被盗了。 我要你找出被盗的船只并把它带回来。 ";
				link.l1 = "嗯, 好吧, 我准备开始调查。 ";
				link.l1.go = "SeekShip_1";
				link.l2 = "对不起, 但我不参与寻找被盗船只。 ";
				link.l2.go = "node_2";
			}
		break;
//------------------------------ —交付航海日志到分散的船长的任务 ---------------------
		case "PortmanQuest_1":
			dialog.text = "太好了, 这是他的航海日志...你真的帮我卸下了一个重担! 丢失船舶日志是一件非常糟糕的事情。 我总是为那些船长感到难过...";
			link.l1 = "嗯, 这确实是一件值得担心的事情! 现在, 告诉我更多关于那个心不在焉的船长的事情。 ";
			link.l1.go = "PortmanQuest_2";
			pchar.questTemp.different = "PortmansJornal";
			SetTimerFunction("SmallQuests_free", 0, 0, 1); //释放迷你任务的许可
			SetJornalCapParam(npchar);
			GiveItem2Character(pchar, "PortmansBook");
			pchar.questTemp.PortmansJornal.gem = GenQuestPortman_GenerateGem();
		break;
		case "PortmanQuest_2":
			dialog.text = "是的, 当然! 他的名字是 " + npchar.quest.PortmansJornal.capName + ", 他是一艘名为'" + npchar.quest.PortmansJornal.shipName + "'的 " + GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansJornal.shipTapeName + "Gen")) + " 的船长。 他不久前起航, 前往 " + XI_ConvertString("Colony" + npchar.quest.PortmansJornal.city + "Acc") + "。 ";
			link.l1 = "我明白了。 好吧, 我会找到他。 现在, 报酬呢? ";
			link.l1.go = "PortmanQuest_3";
		break;
		case "PortmanQuest_3":
			dialog.text = npchar.quest.PortmansJornal.capName + " 自己会付钱给你, 这对他最有利。 你只需专注于尽快到达他那里, 一切都会好起来的。 ";
			link.l1 = "我明白了。 好吧, 我这就走...";
			link.l1.go = "exit";
			sTitle = npchar.id + "PortmansBook_Delivery";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "1");
			AddQuestUserDataForTitle(sTitle, "sCapName", npchar.quest.PortmansJornal.capName);
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansJornal.shipTapeName + "Gen")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.PortmansJornal.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.PortmansJornal.capName);
			AddQuestUserData(sTitle, "sCapName2", npchar.quest.PortmansJornal.capName);
			AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + npchar.quest.PortmansJornal.city + "Acc"));
			if (GetIslandByCityName(npchar.quest.PortmansJornal.city) != npchar.quest.PortmansJornal.city)
			{
				AddQuestUserData(sTitle, "sAreal", ", 它在 " + XI_ConvertString(GetIslandByCityName(npchar.quest.PortmansJornal.city) + "Dat"));
			}			
		break;
		// ------------------------------ —寻找被盗船只的任务 ----------------------------------
		case "SeekShip_1":
			dialog.text = "太好了! 你知道, 被盗的船属于一个有影响力的人, 所以这对我来说非常重要。 我会为这项工作慷慨地付钱给你...";
			link.l1 = "我明白了。 告诉我更多关于这艘船和它被盗时的情况。 ";
			link.l1.go = "SeekShip_2";
			pchar.questTemp.different = "PortmansSeekShip";
			SetTimerFunction("SmallQuests_free", 0, 0, 1); //释放迷你任务的许可
			SetSeekShipCapParam(npchar);
		break;
		case "SeekShip_2":
			dialog.text = XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName) + " 名为'" + npchar.quest.PortmansSeekShip.shipName + "'的船在 " + FindRussianDaysString(rand(5)+10) + " 前的夜间被盗。 看守被杀害了。 ";
			link.l1 = "嗯...他们现在一定已经走得很远了。 线索不再新鲜, 这就是问题所在。 ";
			link.l1.go = "SeekShip_3";
		break;
		case "SeekShip_3":
			dialog.text = "没错, 但我仍然认为立即报警没有意义。 军舰本可以追上他们, 但它只会把船炸成碎片 - 而这并不是我真正需要的。 ";
			link.l1 = "我明白了。 好吧, 我会开始我的搜索。 希望我能幸运。 ";
			link.l1.go = "exit";
			sTitle = npchar.id + "Portmans_SeekShip";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "Portmans_SeekShip", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName+"Acc")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.PortmansSeekShip.shipName);
		break;

		case "SeekShip_break":
			dialog.text = "真遗憾 - 但我们几乎不能指望成功。 ";
			link.l1 = "是的, 船被盗已经太久了。 ";
			link.l1.go = "SeekShip_break_1";
		break;
		case "SeekShip_break_1":
			dialog.text = "好吧, 无论如何还是谢谢你的帮助, 尽管你的努力没有我们希望的那么有成效。 ";
			link.l1 = "我已经尽我所能了...";
			link.l1.go = "exit";
			sTemp = "SeekShip_checkAbordage" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //移除对登船的中断
			cn = GetCharacterIndex("SeekCap_" + npchar.index);
			//如果船长还活着 - 移除他
			if (cn > 0)
			{
				characters[cn].LifeDay = 0; 
				Map_ReleaseQuestEncounter(characters[cn].id);
				group_DeleteGroup("SeekCapShip_" + characters[cn].index);
			}
			sTitle = npchar.id + "Portmans_SeekShip";
			AddQuestRecordEx(sTitle, "Portmans_SeekShip", "7");
			CloseQuestHeader(sTitle);
			DeleteAttribute(npchar, "quest.PortmansSeekShip");
			npchar.quest = ""; //为港口管理员释放个人任务标志
			ChangeCharacterComplexReputation(pchar,"nobility", -7);
		break;	

		case "SeekShip_good":
			if (npchar.quest == "SeekShip_sink")
			{
				dialog.text = "太棒了! 虽然我怀疑这并不完全是被盗的那艘船...哦, 谁在乎呢! 我收下了。 ";
				link.l1 = "是的, 确实...";
				//npchar.quest.money = makeint(sti(npchar.quest.money) / 4); //降低支付
				ChangeCharacterComplexReputation(pchar,"nobility", 5);
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 10);
                AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 10);
                AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 10);
                AddCharacterExpToSkill(GetMainCharacter(), "Commerce", 50);
                AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 20);
			}
			else
			{
				dialog.text = "太棒了! 你帮了我很大的忙。 我无法想象这有多难。 ";
				link.l1 = "是的, 确实...";
				ChangeCharacterComplexReputation(pchar,"nobility", 10);
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
                AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 100);
                AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 150);
                AddCharacterExpToSkill(GetMainCharacter(), "Grappling", 100);
			}
			link.l1.go = "SeekShip_good_1";
		break;
		case "SeekShip_good_1":
			dialog.text = "我准备支付你报酬。 它由 " + FindRussianMoneyString(makeint(sti(npchar.quest.chest)*15000)) + " 箱组成。 不幸的是, 我不能支付更多。 ";
			link.l1 = "嗯, 那足够了。 谢谢你和亲切的问候。 ";
			link.l1.go = "exit";
			TakeNItems(pchar, "chest", sti(npchar.quest.chest));
			sTitle = npchar.id + "Portmans_SeekShip";
			AddQuestRecordEx(sTitle, "Portmans_SeekShip", "6");
			CloseQuestHeader(sTitle);
			DeleteAttribute(npchar, "quest.PortmansSeekShip");
			npchar.quest = ""; //为港口管理员释放个人任务标志
		break;

		//------------------------------> 任务船长数据库信息
		//注意。 任务手册中应录入标准行, 例如   PortmansBook_Delivery  #TEXT   5
		//在港口管理员列表中录入标题。 抬头和quest_text.txt中的行号
		//示例: 在方法末尾  void SetCapitainFromCityToSea(string qName)
		case "CapitainList":
			if (sti(npchar.quest.qty) > 0)
			{
				dialog.text = "有几位注册船长。 你对特定某人感兴趣吗? ";
				makearef(arCapBase, npchar.quest.capitainsList); 
				for (i=0; i<sti(npchar.quest.qty); i++)
				{
    				arCapLocal = GetAttributeN(arCapBase, i);
					sCapitainId = GetAttributeName(arCapLocal);
					sld = characterFromId(sCapitainId);
					attrL = "l" + i;
					link.(attrL) = GetFullName(sld) + ", " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Gen")) + "‘" + sld.Ship.name + "’的船长。 ";
					link.(attrL).go = "CapList_"+attrL;
				}
			}
			else
			{
				dialog.text = "我的名单上没有你可能感兴趣的船长。 ";
				link.l1 = "明白了。 好吧, 谢谢你的信息。 ";
				link.l1.go = "node_2";
			}
		break;
		case "CapList_l0":
			makearef(arCapBase, npchar.quest.capitainsList);
    		arCapLocal = GetAttributeN(arCapBase,  0);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("嗯, 让我看看...啊哈! 在那里! ", "啊哈...啊哈! 在那里! ", "好的, 那么。 ") +
				"船长" + GetFullName(sld) + " " + arCapLocal.date + "年离开我们的港口, 航行至" + XI_ConvertString("Colony" + arCapLocal + "Acc") + "。 ";
			link.l1 = "谢谢你。 我想再查看一次名单...";
			link.l1.go = "CapitainList";
			link.l2 = "好的, 就这样。 我对其他船长都不感兴趣。 ";
			link.l2.go = "node_2";
			//记录到日志
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Voc")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", "位于" + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Dat"));
			}
			//从列表中移除
			DeleteAttribute(arCapBase, sCapitainId); 
		break;
		case "CapList_l1":
			makearef(arCapBase, npchar.quest.capitainsList);
    		arCapLocal = GetAttributeN(arCapBase,  1);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("嗯, 让我看看...啊哈! 在那里! ", "啊哈...啊哈! 在那里! ", "好的, 那么。 ") +
				"船长" + GetFullName(sld) + " " + arCapLocal.date + "年离开我们的港口, 航行至" + XI_ConvertString("Colony" + arCapLocal + "Acc") + "。 ";
			link.l1 = "谢谢你。 我想再查看一次名单...";
			link.l1.go = "CapitainList";
			link.l2 = "好的, 就这样。 我对其他船长都不感兴趣。 ";
			link.l2.go = "node_2";
			//记录到日志
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Dat")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", "位于" + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Dat"));
			}
			//从列表中移除
			DeleteAttribute(arCapBase, sCapitainId); 
		break;
		case "CapList_l2":
			makearef(arCapBase, npchar.quest.capitainsList);
    		arCapLocal = GetAttributeN(arCapBase,  2);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("嗯, 让我看看...啊哈! 在那里! ", "啊哈...啊哈! 在那里! ", "好的, 那么。 ") +
				"船长" + GetFullName(sld) + " " + arCapLocal.date + "年离开我们的港口, 航行至" + XI_ConvertString("Colony" + arCapLocal + "Acc") + "。 ";
			link.l1 = "谢谢你。 我想再查看一次名单...";
			link.l1.go = "CapitainList";
			link.l2 = "好的, 就这样。 我对其他船长都不感兴趣。 ";
			link.l2.go = "node_2";
			//记录到日志
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Dat")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", "位于" + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Dat"));
			}
			//从列表中移除
			DeleteAttribute(arCapBase, sCapitainId); 
		break;
		case "CapList_l3":
			makearef(arCapBase, npchar.quest.capitainsList);
    		arCapLocal = GetAttributeN(arCapBase,  3);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("嗯, 让我看看...啊哈! 在那里! ", "啊哈...啊哈! 在那里! ", "好的, 那么。 ") +
				"船长" + GetFullName(sld) + " " + arCapLocal.date + "年离开我们的港口, 航行至" + XI_ConvertString("Colony" + arCapLocal + "Acc") + "。 ";
			link.l1 = "谢谢你。 我想再查看一次名单...";
			link.l1.go = "CapitainList";
			link.l2 = "好的, 就这样。 我对其他船长都不感兴趣。 ";
			link.l2.go = "node_2";
			//记录到日志
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Dat")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", "位于" + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Dat"));
			}
			//从列表中移除
			DeleteAttribute(arCapBase, sCapitainId); 
		break;
		case "CapList_l4":
			makearef(arCapBase, npchar.quest.capitainsList);
    		arCapLocal = GetAttributeN(arCapBase,  4);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("嗯, 让我看看...啊哈! 在那里! ", "啊哈...啊哈! 在那里! ", "好的, 那么。 ") +
				"船长" + GetFullName(sld) + " " + arCapLocal.date + "年离开我们的港口, 航行至" + XI_ConvertString("Colony" + arCapLocal + "Acc") + "。 ";
			link.l1 = "谢谢你。 我想再查看一次名单...";
			link.l1.go = "CapitainList";
			link.l2 = "好的, 就这样。 我对其他船长都不感兴趣。 ";
			link.l2.go = "node_2";
			//记录到日志
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Dat")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", "位于" + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Dat"));
			}
			//从列表中移除
			DeleteAttribute(arCapBase, sCapitainId); 
		break;
		//<------------------------- —任务船长数据库信息

		case "ShipStock_1":
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "JacobTakeShip" && !CheckAttribute(npchar, "quest.HWICHoll"))
			{
			dialog.text = "我在听 - 哪艘船, 租期多久? ";
			Link.l1 = "卢卡斯.罗登伯格派我来的。 他说我可以免费在这里停泊我的船。 ";
    		Link.l1.go = "ShipStock_HWICHoll";
			DelLandQuestMark(npchar);
			break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoPortoffice" && !CheckAttribute(npchar, "quest.HWICEng"))
			{
			dialog.text = "我在听 - 哪艘船, 租期多久? ";
			Link.l1 = "理查德.弗利特伍德派我来的。 他说我可以以10000比索的价格在这里停泊我的旗舰。 ";
    		Link.l1.go = "ShipStock_HWICEng";
			break;
			}
            if (sti(NPChar.Portman) >= 3 || CheckAttribute(pchar, "questTemp.HWIC.TakeQuestShip"))
			{
				dialog.text = "嗯, 没错。 但不幸的是, 我现在无法接收你的船。 没有可用的码头空间。 ";
				Link.l1 = "真遗憾。 ";
    			Link.l1.go = "exit";
			}
            else
            {
    			ok = (sFrom_sea == "") || (Pchar.location.from_sea == sFrom_sea);
			    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
				{
					dialog.text = "你打算把哪艘船留在这里? ";
	    			for(i=1; i<COMPANION_MAX; i++)
					{
						cn = GetCompanionIndex(PChar, i);
						if(cn > 0)
						{ // 有带守卫的船员。 
							chref = GetCharacter(cn);
							if (!GetRemovable(chref)) continue;							
							attrL = "l"+i+COMPANION_MAX;
							Link.(attrL)	= XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + "‘" + chref.Ship.Name + "’。 ";
							Link.(attrL).go = "ShipStockMan22_" + i;

						}
					}
					Link.l17 = "没关系, 谢谢你。 ";
	    			Link.l17.go = "exit";
    			}
    			else
    			{
					dialog.text = "嗯...我没看到你的任何船只。 ";
					Link.l1 = "我只是想知道停泊的可能性。 ";
	    			Link.l1.go = "exit";
				}
			}
		break;

/*  //////////   hasert уже не надо но пусть висит ////////////////////////////////////
		case "ShipStockMan_1":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 1);
			dialog.text = "Let's take a look at that ship.";
			Link.l1 = "Fine.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "No, I've changed my mind.";
			Link.l2.go = "exit";
		break;

		case "ShipStockMan_2":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 2);
			dialog.text = "Let's take a look at that ship.";
			Link.l1 = "Fine.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "No, I've changed my mind.";
			Link.l2.go = "exit";
		break;

		case "ShipStockMan_3":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 3);
			dialog.text = "Let's take a look at that ship.";
			Link.l1 = "Fine.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "No, I've changed my mind.";
			Link.l2.go = "exit";
		break;
		
		case "ShipStockMan_4":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 4);
			dialog.text = "Let's take a look at that ship.";
			Link.l1 = "Fine.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "No, I've changed my mind.";
			Link.l2.go = "exit";
		break;
*/		
		case "ShipStock_2":
            chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			if (CheckAttribute(pchar, "questTemp.GS_BelizSkidka") && npchar.id == "Beliz_portman" && !CheckAttribute(npchar, "DontNullShipBeliz") && sti(RealShips[sti(chref.Ship.Type)].Class) > 1)	// В Белизе скидка 50%
			{
				NPChar.MoneyForShip = GetPortManPriceExt(NPChar, chref)/2;
			}
			else
			{
				if (MOD_SKILL_ENEMY_RATE >= 6) NPChar.MoneyForShip = MOD_SKILL_ENEMY_RATE/2*GetPortManPriceExt(NPChar, chref); // для высокой сложности - 5x цена
				else NPChar.MoneyForShip = GetPortManPriceExt(NPChar, chref);
			}
			dialog.Text = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + "‘" + chref.Ship.Name + "’, " + RealShips[sti(chref.Ship.Type)].Class + "级, " +
					 "停泊费用为每月" + FindRussianMoneyString(sti(NPChar.MoneyForShip)) + ", 需提前支付一个月的费用。 ";
			Link.l1 = "是的, 这适合我。 ";
			if (sti(Pchar.Money) >= sti(NPChar.MoneyForShip))
			{
			    Link.l1.go = "ShipStock_3";
			}
			else
			{
                Link.l1.go = "ShipStock_NoMoney";
			}
			Link.l2 = "不, 我改变主意了。 ";
			Link.l2.go = "exit";
		break;

		case "ShipStock_NoMoney":
			dialog.text = "一旦你凑齐所需金额, 这对我来说也合适。 ";
			Link.l1 = "哦...我稍后再来。 ";
			Link.l1.go = "exit";
		break;

		case "ShipStock_3": // hasert новый кейс выбора для оффов
			//AddMoneyToCharacter(pchar, -makeint(NPChar.MoneyForShip));
			if (sti(NPChar.StoreWithOff))
			{
				AddMoneyToCharacter(pchar, -makeint(NPChar.MoneyForShip));
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			chref.ShipInStockMan = NPChar.id;
			// Warship 22.03.09 fix Не перенеслось с КВЛ 1.2.3
			chref.ShipInStockMan.MoneyForShip = NPChar.MoneyForShip;
			chref.ShipInStockMan.AltDate = GetQuestBookDataDigit(); // для печати
			SaveCurrentNpcQuestDateParam(chref, "ShipInStockMan.Date"); // для расчёта
			chref.Ship.Crew.Quantity  = 0;
			RemoveCharacterCompanion(pchar, chref);
			}
			else
			{
				AddMoneyToCharacter(pchar, -makeint(NPChar.MoneyForShip));
			chref = GetCharacter(NPC_GenerateCharacter("ShipInStockMan_", "citiz_"+(rand(9)+31), "man", "man", 1, NPChar.nation, -1, false, "quest"));
			chref.id = "ShipInStockMan_" + chref.index; //меняем ID на оригинальный
			chref.loyality = MAX_LOYALITY; 
			chref.name = "";
			chref.lastname = "";
			 chref.Ship.Crew.Quantity  = 0;
			DeleteAttribute(chref,"ship");
			chref.ship = "";
			
			chref.ShipInStockMan = NPChar.id;
			chref.ShipInStockMan.MoneyForShip = NPChar.MoneyForShip;
			chref.ShipInStockMan.AltDate = GetQuestBookDataDigit(); // для печати
			SaveCurrentNpcQuestDateParam(chref, "ShipInStockMan.Date"); // для расчёта
			//  chref.Ship.Crew.Quantity  = 0;
			compref = GetCharacter(sti(NPChar.ShipToStoreIdx));//компаньон, у которого надо забрать корабль
			compref.Ship.Crew.Quantity  = 0;
            RemoveCharacterCompanion(pchar, compref);
			makearef(arTo, chref.ship);
			makearef(arFrom, compref.Ship);
			CopyAttributes(arTo, arFrom);

			compref.ship.type = SHIP_NOTUSED;
			RemoveCharacterCompanion(pchar, compref);
			AddPassenger(pchar, compref, false);
			DelBakSkill(compref);
			}

			chref.location = "";
			chref.location.group = "";
			chref.location.locator = "";
			NPChar.Portman	= sti(NPChar.Portman) + 1;
			pchar.ShipInStock = sti(pchar.ShipInStock) + 1;
			if(NPChar.id == "Beliz_portman" && CheckAttribute(pchar, "questTemp.GS_BelizSkidka") && !CheckAttribute(NPChar, "DontNullShipBeliz") && sti(RealShips[sti(chref.Ship.Type)].Class) > 1)
			{
				chref.DontNullShip = true;
				NPChar.DontNullShipBeliz = true;
			}

			dialog.text = "好的。 你可以随时取回你的船。 ";
			Link.l1 = "谢谢。 ";
			Link.l1.go = "exit";
		break;

		case "ShipStockReturn_1":
            ok = (sFrom_sea == "") || (Pchar.location.from_sea == sFrom_sea);
		    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				if (GetCompanionQuantity(pchar) < COMPANION_MAX)
	            {
					dialog.text = "你打算取回哪艘船? ";
	                cn = 1;
	                for(i=1; i<MAX_CHARACTERS; i++)
					{
						makeref(chref, Characters[i]);
						if (CheckAttribute(chref, "ShipInStockMan"))
						{    
							if (chref.ShipInStockMan == NPChar.id)
							{
								attrL = "l"+cn;
								if(HasSubStr(chref.id, "ShipInStockMan_"))											  
								{ 
								Link.(attrL)	= XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + "‘" + chref.Ship.Name + "’。 ";
								Link.(attrL).go = "ShipStockManBack22_" + i; 
								}
								else
								{  
								Link.(attrL)	= XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + "‘" + chref.Ship.Name + "’和我的军官" + GetFullName(chref) + "。 ";
								Link.(attrL).go = "ShipStockManBack11_" + i;
								}
								cn++;
							}
						}
					}
	
					Link.l99 = "不, 我改变主意了。 ";
	    			Link.l99.go = "exit";
				}
				else
				{
					dialog.text = "你有空间容纳另一艘船吗? ";
					Link.l1 = "哦, 对。 谢谢你。 ";
	    			Link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "嗯。 我在港口没看到你的旗舰。 而且你只能在这里取回你的船。 ";
				Link.l1 = "好的, 我稍后再来取。 ";
    			Link.l1.go = "exit";
			}
		break;

        case "ShipStockManBack":
            chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			// --> mitrokosta给把叛乱者放进PU的狡猾者的惊喜
			if (CheckAttribute(chref, "quest.Mutiny.date")) {
				dialog.text = "让我看看...这艘船于" + chref.quest.Mutiny.date + "离开港口。 ";
				link.l1 = "你说‘离开’是什么意思? 她一定在这里, 在码头! ";
				link.l1.go = "ShipStockManMutiny";
				break;
			}
			// <--
            NPChar.MoneyForShip =  GetNpcQuestPastMonthParam(chref, "ShipInStockMan.Date") * sti(chref.ShipInStockMan.MoneyForShip);
			if (sti(NPChar.MoneyForShip) > 0)
			{
				dialog.Text = "想取回你的船吗? 对于停泊, 你还欠" + FindRussianMoneyString(sti(NPChar.MoneyForShip)) + "。 ";
			}
			else
			{
				dialog.Text = "取回吗? ";
			}
			if (sti(NPChar.MoneyForShip) <= sti(pchar.Money))
			{
				Link.l1 = "是的。 ";
				Link.l1.go = "ShipStockManBack2";
			}
			Link.l2 = "不, 我改变主意了。 ";
			Link.l2.go = "exit";
		break;
		
		case "ShipStockManBack2": // hasert新的守卫案例
			if (sti(NPChar.StoreWithOff))
			{   
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();

			AddMoneyToCharacter(Pchar, -sti(NPChar.MoneyForShip));
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			DeleteAttribute(chref, "ShipInStockMan");
			if(CheckAttribute(chref, "DontNullShip"))
			{
				DeleteAttribute(chref, "DontNullShip");
				DeleteAttribute(NPChar, "DontNullShipBeliz");
			}
			SetCompanionIndex(pchar, -1, sti(NPChar.ShipToStoreIdx));

			NPChar.Portman	= sti(NPChar.Portman) - 1;
			pchar.ShipInStock = sti(pchar.ShipInStock) - 1;
			}
			else
			{   
			dialog.Text = "我应该把它交给你的哪位军官? ";
			int _curCharIdx;
			int q = 0;
			int nListSize = GetPassengersQuantity(pchar);
			for(i=0; i<nListSize; i++)
				{
				_curCharIdx = GetPassenger(pchar,i);
				sld = GetCharacter(_curCharIdx);
					if (_curCharIdx!=-1)
					{
						ok = CheckAttribute(&characters[_curCharIdx], "prisoned") && sti(characters[_curCharIdx].prisoned) == true;

						if (!CheckAttribute(sld, "CompanionDisable"))
					    {
							if (!ok && GetRemovable(&characters[_curCharIdx]))
							{
								attrL = "l"+i;
								sProf = "";
								if (IsOfficer(sld)) sProf += " (先锋) ";
								if (sti(pchar.Fellows.Passengers.navigator) == sti(sld.index)) sProf += " (领航员) ";
								if (sti(pchar.Fellows.Passengers.boatswain) == sti(sld.index)) sProf += " (水手长) ";
								if (sti(pchar.Fellows.Passengers.cannoner) == sti(sld.index)) sProf += " (炮手) ";
								if (sti(pchar.Fellows.Passengers.doctor) == sti(sld.index)) sProf += " (外科医生) ";
								if (sti(pchar.Fellows.Passengers.carpenter) == sti(sld.index)) sProf += " (木匠) ";
								if (sti(pchar.Fellows.Passengers.treasurer) == sti(sld.index)) sProf += " (司库) ";
								Link.(attrL)	= GetFullName(&characters[_curCharIdx]) + sProf;
								Link.(attrL).go = "ShipStockManBack2_" + i;
								q++;
							}
						}
					}
				}
			attrL = "l"+nListSize;
			if (q == 0)
				{
				Link.(attrL) = RandSwear() + "我忘了带一名军官来取这艘船。 ";
				Link.(attrL).go = "exit";
				}
			else
				{
				Link.(attrL) = "不, 我改变主意了。 ";
				Link.(attrL).go = "exit";
				}
			}
		break;
		
		//--> 杰森 荷兰策略
		case "ShipStock_HWICHoll":
			if (GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = "是的, 是的, 我知道。 但我只能为免费停泊接收一艘船。 所以, 请你和你的中队整理好事情, 然后再回来。 ";
				link.l1 = "好的, 我只带旗舰来。 ";
				link.l1.go = "exit";	
			}
			else
			{
				dialog.text = "是的, 是的, 我知道。 根据罗登伯格先生的命令, 我们接收你的船只进行存储, 并且在你的船停留在这里的整个期间, 我们将提供一名值班军官。 请在这里签名...和这里...";
				link.l1 = "好的...我明白所有手续现在都办妥了吗? ";
				link.l1.go = "ShipStock_HWICHoll_1";	
			}
		break;
		
		case "ShipStock_HWICHoll_1":
			dialog.text = "是的。 你再也不用担心你的船了 - 我们会照顾她。 你可以返回罗登伯格先生那里。 ";
			link.l1 = "谢谢你。 再见。 ";
			link.l1.go = "exit";	
			npchar.quest.HWICHoll = "done";
			pchar.Ship.Type = SHIP_NOTUSED;//反正都会烧毁
			AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
			AddMapQuestMarkCity("Villemstad", true);
		break;
		
		case "ShipStock_HWICEng":
			if (GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = "是的, 是的, 我知道。 但我只能为免费停泊接收一艘船。 所以, 请你和你的中队整理好事情, 然后再回来。 ";
				link.l1 = "好的, 我只带旗舰来。 ";
				link.l1.go = "exit";	
			}
			else
			{
				dialog.text = "是的, 当然。 你身上带钱了吗? ";
				if(makeint(Pchar.money) >= 10000)
				{
					link.l1 = "当然。 给你。 ";
					link.l1.go = "ShipStock_HWICEng_1";	
				}
				else
				{
					link.l1 = "没有。 我马上回来。 ";
					link.l1.go = "exit";	
				}
			}
		break;
		
		case "ShipStock_HWICEng_1":
			dialog.text = "好的。 我们会照顾你的船只, 并在你的船停留在这里的整个期间提供一名值班军官。 ";
			link.l1 = "谢谢! ";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -10000);
			npchar.quest.HWICEng = "done";
			pchar.Ship.Type = SHIP_NOTUSED;//反正都会烧毁
			DelLandQuestMark(npchar);
			AddLandQuestMark(characterFromId("Fleetwood"), "questmarkmain");
		break;
		//< —荷兰策略
		case "Escort_companion":
			dialog.text = "你想要什么吗, 船长? ";
			link.l1 = "不, 没什么。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Escort_companion";
		break;
		
		// --> mitrokosta给把叛乱者放进PU的狡猾者的惊喜
		case "ShipStockManMutiny":
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			DeleteAttribute(chref, "ShipInStockMan");
			NPChar.Portman    = sti(NPChar.Portman) - 1;
            pchar.ShipInStock = sti(pchar.ShipInStock) - 1;
			dialog.text = "你的军官" + GetFullName(chref) + "通知" + NPCharSexPhrase(chref, "", "") + "我, " + NPCharSexPhrase(chref, "他", "她") + "不得不按你的命令出海。 我没有反对" + NPCharSexPhrase(chref, "他", "她") + "。 ";
			link.l1 = "该死! 没有这样的命令! 不该把我的船托付给那个混蛋! 唉, 不管怎样, 我对我的损失也无能为力。 ";
			link.l1.go = "ShipStockManMutiny1";
			// 这里可以做个微任务
			//link.l2 = "真让人惊讶... " + NPCharSexPhrase(chref, "他", "她") + "有没有告诉你, 他们碰巧去了哪里? ";
			//link.l2.go = "ShipStockManMutiny2";
		break;
		
		case "ShipStockManMutiny1":
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			chref.lifeday = 0;

			dialog.text = "对不起, " + GetAddress_Form(NPChar) + "。 你应该更小心对待你的下属。 ";
			link.l1 = "我知道, 我是个傻瓜。 再见, " + GetAddress_Form(NPChar) + "。 ";
			link.l1.go = "exit";
		break;
		// <--
		
		// 独特船只和传奇船长 -->
		case "UniqueShips":
			dialog.text = "独特的船只和被委托使用它们的人在群岛内不可能不被注意到。 然而, 这些信息具有相当大的价值, 不会轻易给出。 ";
			if (sti(pchar.Money) >= 25000)
			{
				link.l1 = "我明白。 25000比索的金额是否足以表明我的真诚意图? ";
				link.l1.go = "UniqueShips_2";
			}
			else
			{
				link.l1 = "好吧, 那下次吧。 ";
				link.l1.go = "node_2";
			}
		break;
		
		case "UniqueShips_2":
			dialog.text = "确实, 那将是可以接受的。 你对哪艘特定的船感兴趣? ";
			if (GetDLCenabled(DLC_APPID_4) && !CheckAttribute(pchar, "questTemp.SantaMisericordia_InfoPU") && CharacterIsAlive("SantaMisericordia_cap"))
			{
				link.l1 = "盖伦帆船‘神圣慈悲’。 ";
				link.l1.go = "UniqueShips_SantaMisericordia";
			}
			if (GetDLCenabled(DLC_APPID_5) && !CheckAttribute(pchar, "questTemp.LadyBeth_InfoPU") && CharacterIsAlive("LadyBeth_cap"))
			{
				link.l2 = "巡逻雪船‘贝丝女士’。 ";
				link.l2.go = "UniqueShips_LadyBeth";
			}
			if (GetDLCenabled(DLC_APPID_6) && !CheckAttribute(pchar, "questTemp.Memento_InfoPU") && CharacterIsAlive("Memento_cap"))
			{
				link.l3 = "双桅船‘纪念品’。 ";
				link.l3.go = "UniqueShips_Memento";
			}
			link.l99 = "我想我知道的足够了。 ";
			link.l99.go = "node_2";
		break;
		
		case "UniqueShips_SantaMisericordia":
			AddMoneyToCharacter(pchar, -25000);
			AddQuestRecordInfo("LegendaryShips", "1");
			pchar.questTemp.SantaMisericordia_InfoPU = true;
			dialog.text = "神圣慈悲号由埃斯科里亚尔从欧洲派遣, 负责监督西班牙殖民地。 其船长唐.阿拉米达是西班牙王室的著名仆人, 一位与腐败和犯罪作斗争的无情战士, 也是天主教信仰的狂热分子。 神圣慈悲号在殖民地之间巡航, 从哈瓦那开始并结束其旅程, 只专注于其使命。 \n在每个港口, 阿拉米达会停留几天, 有时更长。 据说在这些时候, 他甚至可以在街上遇到, 但当地人并不特别渴望这样的相遇 - 这位先生在西班牙人中只激起恐惧和敬畏。 \n神圣慈悲号拥有一支经验丰富且忠诚的船员, 由阿拉米达亲自挑选。 每个水手都准备好以生命捍卫他们的祖国和船长。 据说唐.费尔南多已下令神圣慈悲号绝不能被捕获, 并且有传言称, 如果船员在登船时面临无法克服的困难, 他们宁愿将船沉入海底, 也不愿看到她被登船。 ";
			link.l1 = "非常感谢你。 ";
			link.l1.go = "node_2";
		break;
		
		case "UniqueShips_LadyBeth":
			AddMoneyToCharacter(pchar, -25000);
			AddQuestRecordInfo("LegendaryShips", "2");
			pchar.questTemp.LadyBeth_InfoPU = true;
			dialog.text = "贝丝女士号是真正的美人。 英国航海天才的奇迹, 由前皇家海军军官阿尔伯特.布莱克伍德指挥。 确实, 不是每个人都能如此壮观地叛逃! 他离开了军队, 毁掉了辉煌的职业生涯, 还偷了一艘战船 - 全都是为了寻宝! \n而且没有白费。 他已经找到了足够的财富来购买半个巴巴多斯, 但他仍然想要更多。 如果你在海上遇到他 - 甚至不要尝试拦截他。 船太好了, 船长经验丰富且谨慎。 最近, 布莱克伍德经常光顾开曼群岛 - 日夜挖掘, 把人累死。 如果你决定去看看 - 至少带六十个人和好的火器...实际上, 即使那样可能也不够\n我希望你知道如何射击, 因为有一群福克斯上校的前海军步兵跟着他叛逃了。 专业人士, 不像普通的无赖。 而且永远不要在法国港口攻击他 - 他在那里有保护和赞助人, 会收到他发现的一部分。 ";
			link.l1 = "非常感谢你。 ";
			link.l1.go = "node_2";
		break;
		
		case "UniqueShips_Memento":
			AddMoneyToCharacter(pchar, -25000);
			AddQuestRecordInfo("LegendaryShips", "3");
			pchar.questTemp.Memento_InfoPU = true;
			dialog.text = "‘纪念品’  -  真正的海盗传奇。 由莫蒂默.格里姆指挥的黑色双桅船。 \n"+
			"格里姆专门袭击奴隶贩子。 据说他释放奴隶, 用硬通货赎回被定罪的人。 崇高的事业  -  如果你不知道其余的故事。 \n"+
			"如果你不运输人类货物, 格里姆不会碰你。 他很奇怪, 但他有自己的原则。 但如果你的船舱里有奴隶...祈祷你不要在地平线上看到黑色的帆。 \n"+
			"‘纪念品’在海盗港口之间航行, 但很少靠岸。 船员在船上生活数月, 好像害怕踏上坚实的地面。 有传言说这艘船曾经在一场可怕的流行病中幸存下来  -  这就是为什么船员如此难以杀死。 \n"+
			"如果你打算对付他们, 多装些大炮。 登上‘纪念品’几乎是不可能的  -  船员战斗起来像着了魔, 好像不怕死。 打败他们的唯一方法是将船炸成碎片, 夺走他们的庇护所。 碎片吓不到他们, 但直接的葡萄弹命中  -  那是另一回事。 \n"+
			"祝你好运。 记住死亡。 ";
			link.l1 = "非常感谢你。 ";
			link.l1.go = "node_2";
		break;
		
		// уникальные корабли и легендарные капитаны <--
	}
}

float BurntShipQuest_GetMaxNeededValue(int iShipType, string _param)
{
	float NeededValue = makefloat(GetBaseShipParamFromType(iShipType, _param));
	switch (_param)
	{
		case "speedrate":
			NeededValue += ((0.72 + frandSmall(0.30)) * (NeededValue/10.0)); 
		break;
		case "turnrate":
			NeededValue += ((0.72 + frandSmall(0.30)) * (NeededValue/10.0)); 
		break;
		case "capacity":
			NeededValue += ((0.72 + frandSmall(0.30)) * (NeededValue/8.0)); 
		break;
	}
	return NeededValue;
}

// Warship 25.07.09 Генер "A burnt vessel"。 Начальные иниты для портмана - тип разыскиваемого судна, выдающаяся характеристика и т.д.
void BurntShipQuest_FillStartParams(ref _npchar)
{
	int rank = sti(PChar.rank);
	int shipType, temp;
	float neededValue;
	String shipAttribute;
	
	// TODO Пересмотреть зависимость от ранга
	if(rank <= 5)
	{
		shipType = SHIP_LUGGER + rand(1);
		
		switch(shipType)
		{
			case SHIP_LUGGER:
				shipAttribute = "speedrate";
			break;
			
			case SHIP_SLOOP:
				temp = rand(2);
				
				if(temp == 2)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;
		}
	}
	
	if(rank > 5 && rank <= 15)
	{
		shipType = SHIP_SCHOONER + rand(2);
		
		switch(shipType)
		{
			case SHIP_SCHOONER:
				if(rand(1) == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "turnrate";
				}
			break;
			
			case SHIP_BARKENTINE:
				shipAttribute = "capacity";
			break;
			
			case SHIP_SHNYAVA:
				shipAttribute = "capacity";
			break;
		}
	}
	
	if(rank > 15 && rank <= 25)
	{
		shipType = SHIP_FLEUT + rand(3);
		
		switch(shipType)
		{
			case SHIP_FLEUT:
				shipAttribute = "turnrate";
			break;
			
			case SHIP_CARAVEL:
				if(rand(1) == 1)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "turnrate";
				}
			break;
			
			case SHIP_PINNACE:
				shipAttribute = "capacity";
			break;
			
			case SHIP_BRIGANTINE:
				if(rand(1) == 1)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "turnrate";
				}
			break;
			
		}
	}
	
	if(rank > 25 && rank <= 35)
	{
		shipType = SHIP_SCHOONER_W + rand(2);
		
		switch(shipType)
		{
			case SHIP_SCHOONER_W:
				if(rand(1) == 1)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "turnrate";
				}
			break;
			
			case SHIP_GALEON_L:
				shipAttribute = "capacity";
			break;
			
			case SHIP_CORVETTE:
				if(rand(1) == 1)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			break;
		}
	}
	
	if(rank > 35)
	{
		shipType = SHIP_GALEON_H + rand(1);
		
		switch(shipType)
		{
			case SHIP_GALEON_H:
				temp = rand(2);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;
			
			case SHIP_FRIGATE:
				shipAttribute = "turnrate";
			break;
		}
	}
	
	neededValue = BurntShipQuest_GetMaxNeededValue(shipType, shipAttribute);
	
	Log_TestInfo("shipType == " + shipType);
	Log_TestInfo("ShipAttribute == " + shipAttribute);
	Log_TestInfo("ShipNeededValue == " + neededValue);
	
	_npchar.Quest.BurntShip.ShipType = shipType;
	_npchar.Quest.BurntShip.ShipAttribute = shipAttribute;
	
	if(shipAttribute != "capacity") // Чтобы трюм с десятичными не писался
	{
		_npchar.Quest.BurntShip.ShipNeededValue = FloatToString(neededValue, 2);
	}
	else
	{
		_npchar.Quest.BurntShip.ShipNeededValue = MakeInt(neededValue);
	}
}

void SetJornalCapParam(ref npchar)
{
	//созадем рассеянного кэпа
	ref sld = GetCharacter(NPC_GenerateCharacter("PortmansCap_" + npchar.index, "", "man", "man", 20, sti(npchar.nation), -1, true, "citizen"));
	SetShipToFantom(sld, "trade", true);
	sld.Ship.Mode = "trade";
	SetCaptanModelByEncType(sld, "trade");
	sld.dialog.filename = "Quest\ForAll_dialog.c";
	sld.dialog.currentnode = "PortmansCap";
	sld.DeckDialogNode = "PortmansCap_inDeck";
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "DontRansackCaptain");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	sld.DontRansackCaptain = true; //не сдаваться
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER_OWN);
	//в морскую группу кэпа
	string sGroup = "PorpmansShip_" + sld.index;
	Group_FindOrCreateGroup(sGroup);
	Group_SetType(sGroup,"trade");
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation)); 
	//записываем данные в структуры портмана и кэпа
	npchar.quest = "PortmansJornal"; //личный флаг квеста для портмана
	npchar.quest.PortmansJornal.capName = GetFullName(sld); //имя кэпа
	npchar.quest.PortmansJornal.shipName = sld.Ship.name; //имя корабля
	npchar.quest.PortmansJornal.shipTapeName = RealShips[sti(sld.Ship.Type)].BaseName; //название корабля
	npchar.quest.PortmansJornal.city = SelectNotEnemyColony(npchar); //определим колонию, куда ушел кэп
	sld.quest = "InMap"; //личный флаг рассеянного кэпа
	sld.quest.targetCity = npchar.quest.PortmansJornal.city; //продублируем колонию-цель в структуру кэпа
	sld.quest.firstCity = npchar.city; //капитану знать откуда вышел в самом начале
	sld.quest.stepsQty = 1; //количество выходов в море
	sld.quest.money = ((sti(RealShips[sti(sld.Ship.Type)].basetype)+1) * 150) + (sti(pchar.rank)*150); //вознаграждение
	Log_TestInfo("心不在焉的船长 " + sld.id + " 前往: " + sld.quest.targetCity);
	//определим бухту, куда ставить энкаунтер。 чтобы сразу не генерился перед ГГ у города
	string sTemp = GetArealByCityName(npchar.city);
	sld.quest.baseShore = GetIslandRandomShoreId(sTemp);
	//на карту
	sld.mapEnc.type = "trade";
	sld.mapEnc.worldMapShip = "ranger";
	sld.mapEnc.Name = XI_ConvertString(npchar.quest.PortmansJornal.shipTapeName) + " '" + npchar.quest.PortmansJornal.shipName + "'";
	int daysQty = GetMaxDaysFromIsland2Island(sTemp, GetArealByCityName(sld.quest.targetCity))+5; //дней доехать даем с запасом
	Map_CreateTrader(sld.quest.baseShore, sld.quest.targetCity, sld.id, daysQty);
	//заносим Id кэпа в базу нпс-кэпов
	sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).quest = "jornal"; //идентификатор квеста
	NullCharacter.capitainBase.(sTemp).questGiver = "none"; //запомним Id квестодателя для затирки в случае чего
	NullCharacter.capitainBase.(sTemp).Tilte1 = npchar.id + "PortmansBook_Delivery"; //заголовок квестбука
	NullCharacter.capitainBase.(sTemp).Tilte2 = "PortmansBook_Delivery"; //имя квеста в квестбуке
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}
//проверить список отметившихся квестовых кэпов
int CheckCapitainsList(ref npchar)
{
	int bResult = 0;
	if (!CheckAttribute(npchar, "quest.capitainsList")) return bResult;
	aref arCapBase, arCapLocal;
    makearef(arCapBase, npchar.quest.capitainsList);
    int	Qty = GetAttributesNum(arCapBase);
	if (Qty < 1) return bResult;
	string sCapitainId; 
	for (int i=0; i<Qty; i++)
    {
    	arCapLocal = GetAttributeN(arCapBase, i);
        sCapitainId = GetAttributeName(arCapLocal);
    	if (GetCharacterIndex(sCapitainId) > 0) //если еще жив
    	{
			bResult++;			
    	}
		else
		{
			DeleteAttribute(arCapBase, sCapitainId);
			i--;
			Qty--;
		}
    }
	if (bResult > 5) bResult = 5;
	return bResult;
}

void SetSeekShipCapParam(ref npchar)
{
	//создаем кэпа-вора
	int Rank = sti(pchar.rank) + 5;
	if (Rank > 30) Rank = 30;
	ref sld = GetCharacter(NPC_GenerateCharacter("SeekCap_" + npchar.index, "", "man", "man", Rank, PIRATE, -1, true, "soldier"));
	SetSeekCapShip(sld);
	sld.Ship.Mode = "pirate";
	SetCaptanModelByEncType(sld, "pirate");
	sld.dialog.filename = "Quest\ForAll_dialog.c";
	sld.dialog.currentnode = "SeekCap";
	sld.DeckDialogNode = "SeekCap_inDeck";
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "DontRansackCaptain");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	sld.DontRansackCaptain = true; //не сдаваться
	SetCharacterPerk(sld, "FastReload");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "LongRangeShoot");
	SetCharacterPerk(sld, "CannonProfessional");
	SetCharacterPerk(sld, "ShipDefenseProfessional");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "StormProfessional");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	//в морскую группу кэпа
	string sGroup = "SeekCapShip_" + sld.index;
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation)); 
	//записываем данные в структуры портмана и кэпа
	npchar.quest = "PortmansSeekShip"; //личный флаг квеста для портмана
	npchar.quest.PortmansSeekShip.capName = GetFullName(sld); //имя кэпа-вора
	npchar.quest.PortmansSeekShip.shipName = sld.Ship.name; //имя украденного корабля
	npchar.quest.PortmansSeekShip.shipTapeName = RealShips[sti(sld.Ship.Type)].BaseName; //название украденного корабля
	npchar.quest.PortmansSeekShip.shipTape = RealShips[sti(sld.Ship.Type)].basetype; //тип украденного корабля
	//npchar.quest.money = ((sti(RealShips[sti(sld.Ship.Type)].basetype)+1) * 1000) + (sti(pchar.rank)*500); //вознаграждение
	npchar.quest.chest = 12-sti(RealShips[sti(sld.Ship.Type)].Class); //в сундуках
	sld.quest = "InMap"; //личный флаг кэпа-вора
	sld.city = SelectAnyColony(npchar.city); //определим колонию, откуда кэп-вор выйдет
	sld.quest.targetCity = SelectAnyColony2(npchar.city, sld.city); //определим колонию, куда он придёт
	//Log_TestInfo("Thieving cap " + sld.id + " sailed out of: " + sld.city + " and went to: " + sld.quest.targetCity);
	sld.quest.cribCity = npchar.city; //город, откуда кэп-вор спер корабль
	//на карту
	sld.mapEnc.type = "trade";
	sld.mapEnc.worldMapShip = "Galleon_red";
	sld.mapEnc.Name = XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName) + " '" + npchar.quest.PortmansSeekShip.shipName + "'";
	int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(sld.quest.targetCity), GetArealByCityName(sld.city))+3; //дней доехать даем с запасом
	Map_CreateTrader(sld.city, sld.quest.targetCity, sld.id, daysQty);
	//прерывание на абордаж
	string sTemp = "SeekShip_checkAbordage" + npchar.index;
	pchar.quest.(sTemp).win_condition.l1 = "Character_Capture";
	pchar.quest.(sTemp).win_condition.l1.character = sld.id;
	pchar.quest.(sTemp).function = "SeekShip_checkAbordage";
	pchar.quest.(sTemp).CapId = sld.id;
	//прерывание на потопление без абордажа
	sTemp = "SeekShip_checkSink" + npchar.index;
	pchar.quest.(sTemp).win_condition.l1 = "Character_sink";
	pchar.quest.(sTemp).win_condition.l1.character = sld.id;
	pchar.quest.(sTemp).function = "SeekShip_checkSink";
	pchar.quest.(sTemp).CapId = sld.id;
	//заносим Id кэпа в базу нпс-кэпов
	sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).quest = "robber"; //идентификатор квеста
	NullCharacter.capitainBase.(sTemp).questGiver = "none"; //запомним Id квестодателя для затирки в случае чего
	NullCharacter.capitainBase.(sTemp).Tilte1 = npchar.id + "Portmans_SeekShip"; //заголовок квестбука
	NullCharacter.capitainBase.(sTemp).Tilte2 = "Portmans_SeekShip"; //имя квеста в квестбуке
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}

string GenQuestPortman_GenerateGem() // камни
{
	string itemID;
	switch(rand(5))
	{
		case 0:
			itemID = "jewelry1";	
		break;
		case 1:
			itemID = "jewelry2"; 
		break;
		case 2:
			itemID = "jewelry3"; 
		break;
		case 3:
			itemID = "jewelry3"; 
		break;
		case 4:
			itemID = "jewelry5"; 
		break;
		case 5:
			itemID = "jewelry6"; 
		break;
	}
	return itemID;
}

// --> Jason, новые мини-квесты
string findCurrentCity1(ref NPChar)//выбираем целевой город 1
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(pchar.nation), sti(colonies[n].nation));
		if (nation != RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != "LosTeques" && colonies[n].id != "SanAndres" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //на свой остров
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[hrand(howStore-1)];
	return colonies[nation].id;
}

string findCurrentCity2(ref NPChar)//выбираем целевой город 2
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(pchar.nation), sti(colonies[n].nation));
		if (nation != RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != "LosTeques" && colonies[n].id != "SanAndres" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //на свой остров
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[abs(hrand(howStore-1)-3)];
	return colonies[nation].id;
}

string findCurrentCity3(ref NPChar)//выбираем целевой город 3
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(pchar.nation), sti(colonies[n].nation));
		if (nation != RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != "LosTeques" && colonies[n].id != "SanAndres" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //на свой остров
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[abs(hrand(howStore-1)-7)];
	return colonies[nation].id;
}

int Escort_ShipType()
{
	int iShipType;
	switch (rand(2))
	{
		case 0: iShipType = SHIP_FLEUT; 	break;
		case 1: iShipType = SHIP_GALEON_L; 	break;
		case 2: iShipType = SHIP_PINNACE;	break;
	}
	return iShipType;
}
//< —новые мини-квесты

void DelBakSkill(ref _compref) // hasert
{
	DelBakSkillAttr(pchar);
	ClearCharacterExpRate(pchar);
	RefreshCharacterSkillExpRate(pchar);
	SetEnergyToCharacter(pchar);

	DelBakSkillAttr(_compref);
	ClearCharacterExpRate(_compref);
	RefreshCharacterSkillExpRate(_compref);
	SetEnergyToCharacter(_compref);
}

void SetSeekCapShip(ref _chr)
{
	int iRank;
	if (sti(pchar.rank) < 7) iRank = 0;
	if (sti(pchar.rank) >= 7 && sti(pchar.rank) < 11) iRank = 1;
	if (sti(pchar.rank) >= 11 && sti(pchar.rank) < 20) iRank = 2;
	if (sti(pchar.rank) >= 20 && sti(pchar.rank) < 27) iRank = 3;
	if (sti(pchar.rank) >= 27) iRank = 4;
	
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
		case 4:  
			iShip = sti(RandPhraseSimple(its(GetRandomShipType(FLAG_SHIP_CLASS_3, FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_RAIDER, FLAG_SHIP_NATION_ANY)), 
										 its(GetRandomShipType(FLAG_SHIP_CLASS_2, FLAG_SHIP_TYPE_ANY, FLAG_SHIP_NATION_ANY))));
		break;
	}
	
	_chr.Ship.Type = GenerateShipExt(iShip, true, _chr);
	SetRandomNameToShip(_chr);
    SetBaseShipData(_chr);
    SetCrewQuantityFull(_chr);
    Fantom_SetCannons(_chr, "pirate");
    Fantom_SetBalls(_chr, "pirate");
	Fantom_SetUpgrade(_chr, "pirate");
	Fantom_SetGoods(_chr, "pirate");
}
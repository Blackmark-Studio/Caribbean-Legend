// 与甲板上的船长对话  Boal
//homo 25/06/06
#include "DIALOGS\%language%\Rumours\Common_rumours.c"

int iEncPow = -1;
int iCapBattleDifficulty = -1; // Действует, пока не выгружен этот диалог

void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, Diag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	//belamour 渔船
	int i, iTemp, iQty;
	string sTemp;
    //homo 围攻
    aref aData;
    makearef(aData, NullCharacter.Siege);
    string sCap, sGroup;
    string fort;
	bool bOk, bOk1, bOk2;

    if (CheckAttribute(aData, "nation"))
    {
	    sCap = NationShortName(sti(aData.nation))+"SiegeCap_";
	    sGroup = "Sea_"+sCap+"1";
	    
	   // string myships  = GetCompanionQuantity(PChar);
       // string escships = Group_GetCharactersNum(sGroup);
        
        switch(sti(aData.conation))
        {
            case 0:  fort = "英国堡垒"; break;
            case 1:  fort = "法国堡垒"; break;
            case 2:  fort = "西班牙堡垒"; break;
            case 3:  fort = "荷兰堡垒"; break;
            case 4:  fort = "海盗堡垒"; break;
        }
        int ifortPower = sti(colonies[FindColony(aData.colony)].FortValue);
        int fortDamage = CheckFortInjuri();
        int SquadronDamage = CheckSquadronInjuri();
        
    }

    int iMoney;
	ref sld;
    
    if (CheckNPCQuestDate(npchar, "Card_date"))
	{
		SetNPCQuestDate(npchar, "Card_date");
		npchar.money = 3000 + rand(10) * makeint(100 * sti(PChar.rank) * (10.0 / MOD_SKILL_ENEMY_RATE));
	}
	else
	{
		if(sti(npchar.money) > CAP_MAX_MONEY || sti(npchar.money) < CAP_MIN_MONEY) 	
		{
			npchar.money = CAP_MIN_MONEY + rand(CAP_NORM);
		}
	}
    //homo 26/06/06
	ProcessCommonDialogRumors(NPChar, Link, Diag);
	switch(Dialog.CurrentNode)
	{
        case "Exit":
			DialogExit();
			Diag.CurrentNode = Diag.TempNode;
		break;
		
		case "First time":
			if (!bDisableMapEnter)
			{
				//--> Jason 护航 2 级别
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1WM") && pchar.questTemp.WPU.Escort == "begin" && NPChar.id == "WMCaptain")
				{
					dialog.text = "你好, 船长。 该死的, 你不知道我见到你有多高兴! ";
					link.l1 = "嗨。 请允许我介绍自己 - " +GetFullName(PChar)+ "。 我也很高兴看到你还活着, 我专门来找你 - 还有你的船。 ";
					link.l1.go = "WM_Captain";
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1WM") && pchar.questTemp.WPU.Escort == "wait" && NPChar.id == "WMCaptain")
				{
					dialog.text = "你把我要的材料带来了吗? ";
					if (sti(pchar.questTemp.WPU.Escort.Planks) - GetSquadronGoods(pchar, GOOD_PLANKS) <= 0 && sti(pchar.questTemp.WPU.Escort.Sailcloth) - GetSquadronGoods(pchar, GOOD_SAILCLOTH) <= 0 && sti(pchar.questTemp.WPU.Escort.Linen) - GetSquadronGoods(pchar, GOOD_COTTON) <= 0)
					{
						link.l1 = "是的。 我船舱里有你修理船只需要的所有东西。 ";
						link.l1.go = "WM_Captain_5";
					}
					else
					{
						link.l1 = "没有, 我还在准备。 ";
						link.l1.go = "exit";
					}
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1VSP") && pchar.questTemp.WPU.Escort == "toCap" && NPChar.id == "WMCaptain")
				{
					dialog.text = "啊哈, " + GetAddress_Form(NPChar) + "。 我叫" + GetFullName(NPChar) + ", 是这艘船的船长。 请允许我对您帮助我们与该死的海盗人渣战斗表示最诚挚的感谢 - 如果您没有干涉, 我们的情况可能会非常糟糕。 您实际上救了我们, 该死的! ";
					link.l1 = "没什么, " + GetAddress_FormToNPC(NPChar) + "。 请允许我介绍自己 - " +GetFullName(PChar)+ ", 我是应港口主管 " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Escort.StartCity + "Gen") + "的要求来找您的。 他向我介绍了您商队的不幸, 并派我来找您的船。 ";
					link.l1.go = "VSP_Captain";
					break;
				}
				//< —护航 2 级别
				
				if(CheckAttribute(NPChar, "surrendered"))
				{
                    CalcBattleDifficulty();
                    if(iEncPow == -1) iEncPow = 0;
					Pchar.GenQuest.MoneyForCaptureShip = (70 + hrand(60, "&CapSur"+NPChar.id)) * iEncPow;
					if(HasShipTrait(pchar, "trait14")) Pchar.GenQuest.MoneyForCaptureShip = makeint(sti(Pchar.GenQuest.MoneyForCaptureShip) * 1.35);
					dialog.text = "等等, 你这样可能会杀了我。 你想从我这里得到什么? ";
					//赎金
					link.l1 = "让我们和平解决这个问题。 我想, 赎金是最好的决定。 " + Pchar.GenQuest.MoneyForCaptureShip + " 比索对我来说就合适, " + GetAddress_FormToNPC(NPChar) + "。 之后你可以滚蛋了! ";
					link.l1.go = "surrender1";
					// 掠夺货物
					link.l2 = "我想看看你的船舱里有什么。 然后你和你的船员可以想去哪里就去哪里。 ";
					link.l2.go = "surrender2";
					break;
				}
				
				//荷兰人的 Gambit, 对抗所有人
				if (CheckAttribute(PChar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "MeetingStivesant" && NPChar.id == "Stivesant")
				{
					dialog.text = "你好, 先生。 很高兴见到你。 朗威船长可能稍后会登船, 对吧? ";
					link.l1 = "下午好, 斯特伊弗桑特先生。 请允许我介绍自己 - " +GetFullName(pchar)+ "。 朗威不会来, 他不在'美丰'号上。 ";
					link.l1.go = "Stivesant_1";
					pchar.quest.QuestShipsTerms_Over.over = "yes"; // 移除计时器
					break;
				}
				if (CheckAttribute(PChar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "FleutOnTrinidad" && NPChar.id == "Keller")
				{
					DelLandQuestMark(npchar);
					dialog.text = "啊哈, 船长。 什么风把你吹到我的快速帆船上的? ";
					link.l1 = "下午好, 凯勒先生。 请允许我介绍自己 - " +GetFullName(pchar)+ "。 我来是为了请您在一件不寻常的事情上帮忙。 ";
					link.l1.go = "Keller_1";
					break;
					// 荷兰人的 Gambit
				}
				// belamour 渔船 -->
				if(npchar.id == "FishingBoatCap")
				{
					if(!CheckAttribute(pchar, "GenQuest.FishingBoatSecondTime"))
					{
						Dialog.text = TimeGreeting() + ", " + GetAddress_Form(NPChar) + "! 我是" + GetFullName(NPChar) + "的船长。 什么风把您吹到我的船上的? ";
						link.l1 = "你也好。 你在这个海湾做什么? ";
						link.l1.go = "FishingBoat";
						break;
					}
					else
					{
						Diag.CurrentNode = "first time";
						dialog.text = "你还想讨论什么? ";
						link.l1 = "我想" + GetSexPhrase("", "") + "了解群岛的最新消息。 ";
						link.l1.go = "rumours_capitan";
						if(CheckAttribute(pchar,"GenQuest.FishingBoatDialogEnb"))
						{
							link.l2 = "请再给我看看你卖的小饰品。 ";
							link.l2.go = "Торговля";
							if(pchar.GenQuest.FishingBoatDialogEnb != "no special goods")
							{
								link.l3 = "嗯, 也许到船舱里再找找 - 也许能找到什么可卖的? ";
								link.l3.go = "Особые товары";
							}
						}
						link.l4 = "没什么特别的, 只是来问候你! ";
						link.l4.go = "exit";	
						break;
					}
				}
				// < —渔船
				
				//belamour legendary edition 对话, 如果英雄拥有军衔和国家功勋 -->
				// 总督将军
				if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
				{
					Dialog.text = "总督大人, 阁下, 您好! 我能为您做什么? ";
					link.l1 = "我有事情找你! ";
					link.l1.go = "quests";
					link.l2 = "没什么特别的, 只是来问候你! ";
					link.l2.go = "exit";
					break;
				}
				// 舰队副司令
				if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && sti(Items[sti(pchar.EquipedPatentId)].Nation) == npchar.nation)
				{
					Dialog.text = "欢迎登上我的船, 舰队副司令! 我能为您做什么? ";
					link.l1 = "我有事情找你! ";
					link.l1.go = "quests";
					link.l2 = "没什么特别的, 只是来问候你! ";
					link.l2.go = "exit";
					break;
				}
				// 有许可证的军官
				if(IsOfficerFullEquip() && sti(Items[sti(pchar.EquipedPatentId)].Nation) == npchar.nation)
				{
					Dialog.text = "很高兴见到同事, 船长! 我能帮什么忙? ";
					link.l1 = "我有事情找你! ";
					link.l1.go = "quests";
					link.l2 = "没什么特别的, 只是来问候你! ";
					link.l2.go = "exit";
					break;
				}			
				// < —legendary edition
                if (CheckAttribute(NPChar, "EncType")  && NPChar.EncType == "war")
                {
    			    Dialog.text = TimeGreeting() + ", " + GetAddress_Form(NPChar) + "! 我是" + GetFullName(NPChar) + " - 属于" + NationKingsName(NPChar) + "舰队的船长。 是什么风把您吹到我的船上的? ";
    			}
    			else
                {
    			    Dialog.text = TimeGreeting() + ", " + GetAddress_Form(NPChar) + "! 我是" + GetFullName(NPChar) + "船长。 是什么风把您吹到我的船上的? ";
    			}
    			link.l1 = "我叫" +GetFullName(Pchar)+ "。 我有点事找你! ";
    			link.l1.go = "quests";
                link.l2 = "哦, 没什么, 只是" + GetSexPhrase("来", "来") + "问候你! ";
    			link.l2.go = "exit";
            }
            else
            {
                Dialog.text = "您没注意到吗, " + GetAddress_Form(NPChar) + ", 我们正在战斗? 现在不是说话的时候! ";
    			link.l1 = "完全同意! 我回我的船去。 ";
    			link.l1.go = "exit";
            }
			Diag.TempNode = "first time";
 		break;

        case "quests":
			// belamour 渔船 -->
			if(npchar.id == "FishingBoatCap")
			{
				if(!CheckAttribute(pchar, "GenQuest.FishingBoatSecondTime"))
				{
					Dialog.text = TimeGreeting() + ", " + GetAddress_Form(NPChar) + "! 我是" + GetFullName(NPChar) + "的船长。 是什么风把您吹到我的船上的? ";
					link.l1 = "你也好。 你在这个海湾做什么? ";
					link.l1.go = "FishingBoat";
					break;
				}
				else
				{
					dialog.text = "你还想讨论什么? ";
					link.l1 = "我想" + GetSexPhrase("", "") + "了解群岛的最新消息。 ";
					link.l1.go = "rumours_capitan";
					if(CheckAttribute(pchar,"GenQuest.FishingBoatDialogEnb"))
					{
						link.l2 = "请再给我看看你卖的小饰品。 ";
						link.l2.go = "Торговля";
						if(pchar.GenQuest.FishingBoatDialogEnb != "no special goods")
						{
							link.l3 = "嗯, 也许到船舱里再找找 - 也许能找到什么可卖的? ";
							link.l3.go = "Особые товары";
						}
					}
					link.l4 = "没什么特别的, 只是来问候你! ";
					link.l4.go = "exit";	
					break;
				}
			}
			// < —渔船
            if (!CheckAttribute(NPChar, "MainCaptanId")  || NPChar.MainCaptanId == pchar.GenQuest.CaptainId)
            {
                Dialog.text = "我正专心听您说, " + GetAddress_Form(NPChar) + "。 ";
                link.l1 = "我想知道群岛的最新消息。 ";
                //homo 25/06/06
                link.l1.go = "rumours_capitan";
                //belamour legendary edition 
				bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
				bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
				bOk = bOk1 || bOk2;
                if (CheckAttribute(NPChar, "EncGroupName") && !bOk) // 仅用于幻影掠夺
                {
                    iCapBattleDifficulty = CalcBattleDifficulty();
                    link.l2 = "(威慑几率 " + iCapBattleDifficulty + "%%) " + RandPhraseSimple("你知道我是谁吗? 我的火炮能把你的破船打成筛子。 和平解决吧—赎金就够了。", "大海上……  只有我们……  为了你船员的安全, 何不打赏点东西安抚我的兄弟们?");
                    link.l2.go = "Talk_board";
                }
                if (CheckAttribute(NPChar, "Ship.Mode") && NPChar.Ship.Mode == "Trade")
                {
	           		link.l3 = "你从哪里来? ";
	    			link.l3.go = "price_1";
	    			link.l4 = "想交易吗? ";
	    			link.l4.go = "Trade_1";
    			}
				//--> 市长任务, 寻找海盗
				if (CheckAttribute(pchar, "GenQuest.DestroyPirate"))
				{
	    			link.l6 = "我在寻找一艘在这些水域活动的海盗船。 你见过什么可疑的吗? ";
	    			link.l6.go = "MQ_step_1";
				}
				//< —市长任务, 寻找海盗
    			link.l5 = "想放松一下吗? ";
			    link.l5.go = "Play_Game";
                link.l9 = "我想我该走了。 ";
    			link.l9.go = "exit";
			}
			else
			{
                Dialog.text = "我无权与您打交道。 请和我们中队的指挥官谈谈。 他的名字是" + GetFullName(characterFromID(NPChar.MainCaptanId)) +
                              ", 你可以在" + XI_ConvertString(RealShips[sti(characters[GetCharacterIndex(NPChar.MainCaptanId)].Ship.Type)].BaseName) + "'" + characters[GetCharacterIndex(NPChar.MainCaptanId)].Ship.Name + "'上找到他。 ";
                link.l1 = "谢谢。 我会照你说的做。 ";
                link.l1.go = "exit";
                Diag.TempNode = "Go_away_Good";
			}
        break;
        case "Trade_1":
			dialog.text = "为什么不呢? ";
			link.l1 = "我们去看看货物吧。 ";
			link.l1.go = "Trade_2";
			link.l2 = "我改变主意了。 ";
			link.l2.go = "exit";
		break;
		
		case "Trade_2":
            Partition_GetCargoCostCoeff("after");
			FillShipStore(NPChar);
	    	pchar.shiptrade.character = NPChar.id;
   			Diag.CurrentNode = Diag.TempNode;
		    DialogExit();
		    DeleteAttribute(pchar, "PriceList.StoreManIdx"); // 不记录船只日志
		    LaunchStore(SHIP_STORE);
		break;
		
        case "Play_Game":
			dialog.text = "你建议玩什么? ";
			link.l1 = "想玩牌赌点大的吗? ";
			link.l1.go = "Card_Game";
   			link.l2 = "玩骰子扑克怎么样? ";
			link.l2.go = "Dice_Game";
			link.l10 = "抱歉, 我有点事要做。 ";
			link.l10.go = "exit";
		break;
        // 卡片 -->
        case "Card_Game":
            if (!CheckNPCQuestDate(npchar, "Card_date_Yet") || isBadReputation(pchar, 30) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(3))
            {
                SetNPCQuestDate(npchar, "Card_date_Yet");
                dialog.text = "我不会和骗子赌博! ";
    			link.l1 = "如你所愿。 ";
    			link.l1.go = "exit";
			}
			else
			{
                dialog.text = "为什么不呢? 我当然不介意休息一下... ";
    			link.l1 = "太好了。 ";
    			link.l1.go = "Cards_begin";
    			link.l2 = "规则是什么? ";
    			link.l2.go = "Cards_Rule";
			}
		break;

		case "Cards_Rule":
   			dialog.text = CARDS_RULE;
			link.l1 = "那么, 开始吧! ";
			link.l1.go = "Cards_begin";
			link.l3 = "不, 这不适合我... ";
			link.l3.go = "exit";
		break;

		case "Cards_begin":
			Dialog.text = "我们先说好赌注。 ";
			link.l1 = "赌100比索。 ";
			link.l1.go = "Cards_Node_100";
			link.l2 = "赌500比索。 ";
			link.l2.go = "Cards_Node_500";
			link.l3 = "我想我该走了。 ";
			link.l3.go = "exit";
		break;

		case "Cards_Node_100":
		    if (sti(pchar.Money) < 300)
		    {
                dialog.text = "你在开玩笑吗? 你没钱! ";
                link.l1 = "确实。 ";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 300)
		    {
                dialog.text = "好吧, 够了, 否则我连维持船只的钱都不够了... ";
                link.l1 = "真遗憾。 ";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "好, 赌100枚硬币。 ";
			link.l1 = "开始吧! ";
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 100;
            pchar.GenQuest.Cards.SitType   = false;
		break;

		case "Cards_Node_500":
		    if (sti(pchar.Money) < 1500)
		    {
                dialog.text = "你在开玩笑吗? 你没有1500比索! ";
                link.l1 = "我会找到的! ";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 1500)
		    {
                dialog.text = "不, 这些赌注最终肯定会让我陷入困境。 ";
                link.l1 = "如你所愿。 ";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "好, 赌500枚硬币。 ";
			link.l1 = "开始吧! ";
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 500;
            pchar.GenQuest.Cards.SitType   = false;
		break;

		case "Cards_begin_go":
            Diag.CurrentNode = Diag.TempNode;
			DialogExit();
            LaunchCardsGame();
		break;
	    // 卡片 <--
	    // 骰子 -->
        case "Dice_Game":
            if (!CheckNPCQuestDate(npchar, "Dice_date_Yet") || isBadReputation(pchar, 30) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(3))
            {
                SetNPCQuestDate(npchar, "Dice_date_Yet");
                dialog.text = "我不会和骗子赌博! ";
    			link.l1 = "如你所愿。 ";
    			link.l1.go = "exit";
			}
			else
			{
				if (CheckNPCQuestDate(npchar, "Dice_date_begin"))
				{
					dialog.text = "为什么不呢! 放松总是对健康有好处... 但不总是对钱包有好处... ";
	    			link.l1 = "太好了。 ";
	    			link.l1.go = "Dice_begin";
	    			link.l2 = "我们的游戏规则是什么? ";
	    			link.l2.go = "Dice_Rule";
    			}
    			else
    			{
					dialog.text = "不, 我今天玩够了。 我还有事要做。 ";
	    			link.l1 = "如你所愿。 ";
	    			link.l1.go = "exit";
				}
			}
		break;

		case "Dice_Rule":
   			dialog.text = DICE_RULE;
			link.l1 = "那么, 开始吧! ";
			link.l1.go = "Dice_begin";
			link.l3 = "不, 这不适合我... ";
			link.l3.go = "exit";
		break;

		case "Dice_begin":
			Dialog.text = "我们先说好赌注。 ";
			link.l1 = "赌50比索。 ";
			link.l1.go = "Dice_Node_100";
			link.l2 = "赌200比索。 ";
			link.l2.go = "Dice_Node_500";
			link.l3 = "我想我该走了。 ";
			link.l3.go = "exit";
		break;

		case "Dice_Node_100":
			//belamour legendary edition 
			bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
			bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
			bOk = bOk1 || bOk2;
            if (!CheckDiceGameSmallRate() && !bOk)
		    {
                dialog.text = "你是出了名的" + GetSexPhrase("骗子", "骗子") + ".. 我永远不会和你掷骰子。 ";
                link.l1 = "都是谎言! 好吧, 就这样。 ";
			    link.l1.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 300)
		    {
                dialog.text = "你在开玩笑吗? 你没钱! ";
                link.l1 = "确实。 ";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 300)
		    {
                dialog.text = "够了! 我赌够了 - 免得他们说我是个贪污犯, 逼我下船。 ";
                link.l1 = "真遗憾。 ";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "好, 赌50枚硬币。 ";
			link.l1 = "开始吧! ";
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
            pchar.GenQuest.Dice.iRate     = 50;
            pchar.GenQuest.Dice.SitType   = false;
		break;

		case "Dice_Node_500":
			//belamour legendary edition 
			bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
			bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
			bOk = bOk1 || bOk2;
            if (!CheckDiceGameSmallRate() && !bOk)
		    {
                dialog.text = "你是出了名的" + GetSexPhrase("骗子", "骗子") + "。 我永远不会和你掷骰子。 ";
                link.l1 = "都是谎言! 好吧, 就这样。 ";
			    link.l1.go = "exit";
			    break;
		    }
			if (!CheckDiceGameBigRate())
		    {
                dialog.text = "我听说你是个很好的玩家。 我不会和你玩高赌注的。 ";
                link.l1 = "我们降低赌注, 好吗? ";
			    link.l1.go = "Dice_Node_100";
				link.l2 = "抱歉, 我得走了。 ";
			    link.l2.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 1500)
		    {
                dialog.text = "你在开玩笑吗? 你没有1500比索! ";
                link.l1 = "我会找到的! ";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 1500)
		    {
                dialog.text = "不, 这些赌注最终肯定会让我陷入困境。 ";
                link.l1 = "如你所愿。 ";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "好, 赌200枚硬币。 ";
			link.l1 = "开始吧! ";
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
            pchar.GenQuest.Dice.iRate     = 200;
            pchar.GenQuest.Dice.SitType   = false;
		break;

		case "Dice_begin_go":
            SetNPCQuestDate(npchar, "Dice_date_begin");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
            LaunchDiceGame();
		break;
	    // 骰子 <--
        case "price_1":
			if (CheckNPCQuestDate(npchar, "trade_date"))
			{
                SetNPCQuestDate(npchar, "trade_date");
				iMoney = findPriceStoreMan(NPChar);
	            if (iMoney == -1)
	            {
	                Dialog.Text = "你为什么想知道? 这是我的隐私。 ";
					Link.l1 = "如你所愿。 ";
					Link.l1.go = "exit";
	            }
	            else
	            {
                    sld = &Characters[iMoney];
                    pchar.PriceList.ShipStoreIdx = iMoney;
                    
					Dialog.Text = "我来自" + GetCityName(sld.City) + "市。 ";
					Link.l1 = "当地商店的商品价格是多少? ";
					Link.l1.go = "price_2";
					Link.l9 = "我该走了。 ";
					Link.l9.go = "exit";
				}
			}
			else
			{
                Dialog.Text = "我已经都告诉你了。 别没事打扰我。 ";
				Link.l1 = "是的, 你说得对。 再见。 ";
				Link.l1.go = "exit";
            }
		break;
		
		case "price_2":
            sld = &Characters[sti(pchar.PriceList.ShipStoreIdx)];
			SetPriceListByStoreMan(&Colonies[FindColony(sld.City)]);
			Dialog.Text = "给你... (你收到了价格表)..";
			Link.l1 = "非常感谢! ";
			Link.l1.go = "exit";
			PlaySound("interface\important_item.wav");
		break;
		
        case "Talk_board":
            bOk = iCapBattleDifficulty > hrand(98);
            //if ((Group_GetCharactersNum(NPChar.EncGroupName) - Group_GetDeadCharactersNum(NPChar.EncGroupName)) > GetCompanionQuantity(PChar) && rand(11) > GetCharacterSkillToOld(PChar, SKILL_FORTUNE))
            if(!bOk && iCapBattleDifficulty <= 33)
            {
                Dialog.text = "哈哈! 真是个笑话。 尤其是现在我明显占优。 回到你的船上, 与它一起沉没吧。";
                link.l1 = "...";
                link.l1.go = "Boarding";
            }
            else
            {
                if(!bOk)
                {
                    Dialog.text = "船长, 你不该在我的船上做这种肮脏的事。 但我会仁慈一点, 让你回到你的船上, 和它一起淹死。 ";
                    link.l1 = "我们走着瞧, 今天谁会成为鲨鱼的食物! ";
                    link.l1.go = "Boarding";
                }
                else
                {
                    if(iEncPow == -1) iEncPow = 0;
                    Pchar.GenQuest.MoneyForCaptureShip = (70 + hrand(60, "&CapSur"+NPChar.id)) * iEncPow;
					if(HasShipTrait(pchar, "trait14")) Pchar.GenQuest.MoneyForCaptureShip = makeint(sti(Pchar.GenQuest.MoneyForCaptureShip) * 1.35);
                    Dialog.text = RandSwear() + "是的, 我听说了很多关于你的暴行。 就这样吧, 但记住" +
                                  XI_ConvertString(NationShortName(sti(NPChar.nation)) + "hunter") + "不会就此罢休! ";
                    link.l1 = "太好了。 " + Pchar.GenQuest.MoneyForCaptureShip + "比索对我来说就合适, " + GetAddress_FormToNPC(NPChar) + "。 ";
                    link.l1.go = "Capture";
                    link.l2 = "哦, 没关系。 我只是开玩笑" + GetSexPhrase("", "") + "! ";
                    link.l2.go = "exit";
                }
            }
            // 这里需要考虑禁止重复登船
            Diag.TempNode = "Go_away";
			sld = characterFromId(pchar.GenQuest.CaptainId);
            sld.talk_date_Go_away =  lastspeakdate(); // boal 记仇 :)
        break;
		
		case "surrender1" :
			Diag.TempNode = "surrender_goaway";
            Dialog.Text = "给你 - 现在滚蛋! ";
			Link.l1 = "太好了! 你也保重, 朋友! ";
			Link.l1.go = "exit";
			sld = characterFromId(pchar.GenQuest.CaptainId);
            sld.talk_date_Go_away = lastspeakdate();
			AddMoneyToCharacter(pchar, sti(Pchar.GenQuest.MoneyForCaptureShip));
			ChangeCharacterComplexReputation(pchar,"nobility", -2); 		
			ChangeCharacterComplexReputation(pchar,"authority", 1.0); 							
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			ChangeCharacterHunterScore(pchar, NationShortName(sti(NPChar.nation)) + "hunter", GetIntByCondition(HasShipTrait(pchar, "trait23"), 7 + rand(10), 3 + rand(5)));
		break;
		
		case "surrender_goaway":
			Dialog.Text = "你还想从我这里得到什么? ";
			Link.l1 = "没什么。 ";
			Link.l1.go = "exit";
			Diag.TempNode = "surrender_goaway";
		break;
		
		case "surrender2":			
			dialog.text = "看来, 我别无选择, 只能向你屈服。 ";
			link.l1 = "现在走吧! ";
			link.l1.go = "surrender3";				
		break;
						
		case "surrender3":
			Diag.TempNode = "surrender_goaway";
			sld = characterFromId(pchar.GenQuest.CaptainId);
            sld.talk_date_Go_away = lastspeakdate();
			DialogExit(); 
			LaunchTransferMain(pchar, sld, "Transfer");
		break;
				
        case "rumours":
			Dialog.Text = SelectRumour(); // to_do
			Link.l1 = RandPhraseSimple(RandSwear() + "这很有趣。 另一个问题? ",
                                     "只是另一件事。 ");
			Link.l1.go = "quests";
			Link.l2 = RandPhraseSimple("谢谢, 我该走了。 ",
                                     "一切顺利。 ");
			Link.l2.go = "exit";
			Diag.TempNode = "quests";
		break;
		
		case "Go_away":
			Dialog.Text = "滚出我的船! ";
			Link.l1 = "我已经在离开了。 ";
			Link.l1.go = "exit";
			Diag.TempNode = "Go_away";
		break;
		
		case "Go_away_Good":
			Dialog.Text = "我们的谈话结束了。 我不会再告诉你什么新东西了" + GetAddress_Form(NPChar) + "。 ";
			Link.l1 = "好吧。 海上见! ";
			Link.l1.go = "exit";
			Diag.TempNode = "Go_away_Good";
		break;

        case "Capture":
            Diag.TempNode = "Go_away";
            Dialog.Text = "给你 - 现在滚出去! ";
			Link.l1 = "太好了! ";
			Link.l1.go = "exit";
			AddMoneyToCharacter(pchar, sti(Pchar.GenQuest.MoneyForCaptureShip));
			ChangeCharacterComplexReputation(pchar,"nobility", -5);			
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			ChangeCharacterHunterScore(pchar, NationShortName(sti(NPChar.nation)) + "hunter", GetIntByCondition(HasShipTrait(pchar, "trait23"), 7 + rand(10), 3 + rand(5)));
        break;

        case "Boarding":
            if (CheckAttribute(NPChar, "MainCaptanId"))
            {
                PChar.StartBattleAfterDeck = true;
                PChar.StartBattleMainCaptanId = NPChar.MainCaptanId;
                PChar.StartBattleEncGroupName = NPChar.EncGroupName;
            }
            DialogExit();
            Diag.CurrentNode = Diag.TempNode;
        break;
        
        case "QuestAboardCabinDialog":  // 测试对话, 在游戏中不起作用, 用于 SetQuestAboardCabinDialog 方法
			Diag.TempNode = "QuestAboardCabinDialog";
            Dialog.Text = "等等, 你这样可能会杀了我。 你想从我这里得到什么? ";
			Link.l1 = "杀了你! ";
			Link.l1.go = "QuestAboardCabinDialog_1";
			Link.l2 = "投降! ";
			Link.l2.go = "QuestAboardCabinDialog_2";
			Link.l3 = "把地图给我们, 比利 (c)";  // 物品, 之后不清楚是 QuestAboardCabinDialog_1 还是 QuestAboardCabinDialog_2
			Link.l3.go = "QuestAboardCabinDialog_3";  // 可以编码离开船, 但船员已经被移除等... 
        break;
        
        case "QuestAboardCabinDialog_1":
			Dialog.Text = "好吧, 我们走着瞧, 混蛋! ";
			Link.l1 = "我该看什么? ";
			Link.l1.go = "exit";
			// 这里可以恢复敌人的 NR (NPChar) 或为 GG 添加几个守卫
			LAi_SetCurHPMax(NPChar);
			AddDialogExitQuestFunction("QuestAboardCabinDialogExitWithBattle"); // 这里回骂
		break;
		
		case "QuestAboardCabinDialog_2":
			Dialog.Text = "好吧, 你赢了! ";
			Link.l1 = "明智的决定! ";
			Link.l1.go = "exit";
			AddDialogExitQuestFunction("QuestAboardCabinDialogSurrender");
		break;
		
		case "QuestAboardCabinDialog_3":
			Dialog.Text = "希望你被噎死! ";
			Link.l1 = "很好, 戴上镣铐, 闭上嘴, 囚犯。 ";
			if (rand(1) == 1)  // 示例!!!
			{
				Link.l1.go = "QuestAboardCabinDialog_2";
			}
			else
			{
			    Link.l1.go = "QuestAboardCabinDialog_3_1";
			}
			TakeNItems(NPChar, "Chest", -1);
			TakeNItems(pchar, "Chest", 1);
		break;
		
		case "QuestAboardCabinDialog_3_1":
			Dialog.Text = "" + GetSexPhrase("来到这里", "来到这里") + ", 弄得一团糟" + GetSexPhrase("", "") + ", 现在想让我当奴隶? 绝不! ";
			Link.l1 = "那准备死吧。 ";
			Link.l1.go = "QuestAboardCabinDialog_1";
		break;
		//eddy。 市长任务, 寻找海盗
		case "MQ_step_1":
			Dialog.Text = "不, 我没见过任何看起来像海盗的可疑船只。 ";
			Link.l1 = "我知道了。 ";
			Link.l1.go = "exit";
		break;
		
		//homo 引诱商人
		case "MerchantTrap_Abordage":

			Dialog.Text = "以" + NationKingsName(NPChar) + "的名义投降, " + GetSexPhrase("肮脏的海盗", "肮脏的荡妇! ") + "! 然后你的生命将被保留到公平的法庭, 在那里你将为你掠夺的所有" + NationNameSK(sti(NPChar.nation)) + "船只受到审判" + GetSexPhrase("", "") + "。 ";
			Link.l1 = "去你的! 你应该投降! ";
			Link.l1.go = "exit";
			LAi_SetCurHPMax(NPChar);
			AddDialogExitQuestFunction("QuestAboardCabinDialogExitWithBattleNoParam"); // 这里回骂
		break;
		
		case "Siegehelp":		
            ref rchar = Group_GetGroupCommander(sGroup);
            if (NPChar.id == rchar.id)
            {
    			if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
				{
					dialog.text = "大人, 总督将军! 我正仔细听您说, 但请您简短些: 我们正在与" + fort +
                          "战斗, 我需要指挥战斗进程。 ";
				}
				else
				{
					if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && sti(Items[sti(pchar.EquipedPatentId)].Nation) == npchar.nation)
					{
						dialog.text = "舰队副司令! 我仔细听您说, 但我时间不多: 我们正在与" + fort +
                          "战斗, 我需要指挥战斗进程。 ";
					}
					else
					{
						dialog.text = "我在听您说, 但让我们快速说明您来访的目的, 我们正在与" + fort +
                          "战斗, 我需要指挥战斗进程。 ";
					}
				}
                link.l1 = "这就是我来这里的原因, " + GetAddress_FormToNPC(NPChar) + "。 ";
                link.l1.go = "attack_fort";

                link.l2 = "既然如此, 我不再占用您的时间了。 再见, " + GetAddress_FormToNPC(NPChar) + "。 ";
                link.l2.go = "exit";
    			
            }
            else
            {
                Dialog.text = "我无权与您打交道。 请和我们中队的指挥官谈谈。 他的名字是" + GetFullName(rchar) +
                              ", 你可以在" + XI_ConvertString(RealShips[sti(rchar.Ship.Type)].BaseName) + "''" + rchar.Ship.Name + "''上找到他。 ";
                link.l1 = "谢谢。 我会照你说的做。 ";
                link.l1.go = "exit";
            
            }
            Diag.TempNode = "Siegehelp";
            
		break;
		
		case "attack_fort":
                dialog.text = "你是什么意思? ";
                link.l1 = "我可以协助你摧毁" + GetCityName(aData.Colony) + "殖民地的堡垒并占领城市, 如果我们成功, 战利品由我们平分。 ";
                link.l1.go = "Siegehelp_1";
                link.l2 = "实际上, 我的事不值得你花时间。 再见, " + GetAddress_FormToNPC(NPChar) + "。 ";
                link.l2.go = "exit";
                Diag.TempNode = "Siegehelp_0";
		break;
		
		case "Siegehelp_0":
            Dialog.text = "又是你? 我以为我们已经讨论过所有事情了。 ";
            link.l1 = "你说得对。 我想我忘了" + GetSexPhrase("", "") + "。 ";
			link.l1.go = "exit";
			NPChar.DeckDialogNode = "Siegehelp_0";
            Diag.TempNode = "Siegehelp_0";

		break;
		
		case "Siegehelp_1":
            SiegeResult("");
			// belamour legendary edition
			bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation);
			bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE;
			bOk = bOk1 || bOk2;
            if (sti(aData.win)==0 || bOk)
            {
                dialog.text = "你期望得到多少战利品? ";
                link.l1 = "一半。 ";
                link.l1.go = "Big_part";
                link.l2 = "三分之一。 ";
                link.l2.go = "Middle_part";
                link.l3 = "四分之一。 ";
                link.l3.go = "Small_part";
            }
            else
            {
                dialog.text = "我不需要你的服务, 船长! 我会自己夺取这个殖民地, 不需要任何帮助。 ";
                link.l1 = "你为什么这么确定, " + GetAddress_FormToNPC(NPChar) + ", 任何人都可能有运气不好的时候。 ";
                link.l1.go = "attack_fort_03";
                link.l2 = "既然如此, 我不再占用你的时间了, " + GetAddress_FormToNPC(NPChar) + "。 再见! ";
                link.l2.go = "exit";
            }
			Diag.TempNode = "Siegehelp_0";

		break;
		
		case "attack_fort_03":
            if((sti(aData.iSquadronPower)*SquadronDamage - (ifortPower)*fortDamage) < 4000)
            {
                dialog.text = "另一方面, 我的船在这场战斗中受损严重, 增援肯定不会有坏处。 如果你同意" + GetPart(4) + ", 那么, 我想我们可以达成协议。 ";
                link.l1 = "这对我很合适, " + GetAddress_FormToNPC(NPChar) + "。 我会尝试攻击堡垒, 你用你船上的炮火支援我们。 ";
                link.l1.go = "attack_fort_04";
                aData.PartAttaksFort = 4;
                link.l2 = "我没那么便宜, " + GetAddress_FormToNPC(NPChar) + "。 很抱歉打扰你" + GetSexPhrase("", "") + "处理紧急事务。 再见! ";
                link.l2.go = "exit";
            }else{
                dialog.text = "我的中队有足够的船只将这个堡垒化为灰烬 - 这只是时间问题。 现在, 请你离开我的船好吗? 胜利在等待我! ";
                link.l1 = "好吧, 既然如此, " + GetAddress_FormToNPC(NPChar) + ", 请允许我告辞。 再见! ";
                link.l1.go = "exit";
            }
		    Diag.TempNode = "Siegehelp_0";
		break;
		case "Big_part":
            if( (sti(aData.iSquadronPower) * SquadronDamage - (ifortPower) * fortDamage) <= -1500)
            {
                dialog.text = "堡垒的大炮严重损坏了我的船只, 我们在即将到来的战斗中肯定会失利。 我接受你的帮助, 并同意你的条件。 ";
                link.l1 = "太好了, " + GetAddress_FormToNPC(NPChar) + ", 在这种情况下, 我们将尝试攻击堡垒, 你用你船上的炮火支援我们。 ";
                link.l1.go = "attack_fort_04";
                aData.PartAttaksFort = 2;
            }
            else
            {
				// belamour legendary edition
				bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation);
				bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE;
				bOk = bOk1 || bOk2;
				if(bOk)
				{
					dialog.text = "大人, 我还需要报告行动进展... 至少" + GetPart(4) + "。 ";
				}
				else
				{
                dialog.text = "船长, 这是不是太多了? 你有" + GetNumShips(GetCompanionQuantity(PChar)) +
                              ", 我的中队有" + GetNumShips(Group_GetCharactersNum(sGroup)) + "。 我可以给你" + GetPart(4) +
                              "。 并认为这是公平的。 ";
				}
                aData.PartAttaksFort = 4;
                link.l1 = "我同意" + GetSexPhrase("", "") + ", " + GetAddress_FormToNPC(NPChar) + ", 在这种情况下, 我将攻击堡垒, 你用你船上的炮火支援我们。 ";
                link.l1.go = "attack_fort_04";
                link.l2 = "不幸的是, 我不这么认为, " + GetAddress_FormToNPC(NPChar) + "。 没什么可讨论的了。 再见。 ";
                link.l2.go = "exit";
            }
            Diag.TempNode = "Siegehelp_0";
        break;
        
        case "attack_fort_04":
            dialog.text = "一旦堡垒被攻占, 我们将开始在岸边部署登陆部队, 然后我们将继续在城内战斗, 我希望在那里与你会合。 ";
            link.l1 = "就这样吧。 很快见, " + GetAddress_FormToNPC(NPChar) + "! ";
            link.l1.go = "exit";
            Diag.TempNode = "Siegehelp_0";
            PChar.quest.Union_with_Escadra = "Yes";
        break;

        case "Middle_part":
            if((sti(aData.iSquadronPower) * SquadronDamage - (ifortPower) * fortDamage) <= -600)
            {
                dialog.text = "我想我会同意你的条件。 联合作战将增加我赢得这场战斗的机会。 如果一切按计划进行, 你将得到你的战利品份额。 ";
                link.l1 = "我们达成协议太好了, " + GetAddress_FormToNPC(NPChar) + "。 我将立即命令我的人开始攻击堡垒。 ";
                link.l1.go = "attack_fort_04";
                aData.PartAttaksFort = 3;
            }else{
				// belamour legendary edition
				bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation);
				bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE;
				bOk = bOk1 || bOk2;
				if(bOk)
				{
					dialog.text = "大人, 我还需要报告行动进展... 至少" + GetPart(4) + "。 ";
				}
				else
				{
                dialog.text = "船长, 这是不是太多了? 你有" + GetNumShips(GetCompanionQuantity(PChar)) + ", 我的中队有" + GetNumShips(Group_GetCharactersNum(sGroup)) + "。 我可以给你" + GetPart(4) + "。 并认为这是公平的。 ";
				}
                link.l1 = "我" + GetSexPhrase("同意", "同意") + ", " + GetAddress_FormToNPC(NPChar) + ", 在这种情况下, 我将攻击堡垒, 你用你船上的炮火支援我们。 ";
                link.l1.go = "attack_fort_04";
                aData.PartAttaksFort = 4;
                link.l2 = "不幸的是, 我不这么认为, " + GetAddress_FormToNPC(NPChar) + "。 没什么可讨论的了。 再见。 ";
                link.l2.go = "exit";
            }
            Diag.TempNode = "Siegehelp_0";
        break;

        case "Small_part":
            dialog.text = "我的船累了, 任何新鲜力量在这种情况下都是受欢迎的。 我接受你的帮助, 并同意你的条件。 ";
            link.l1 = "我很高兴" + GetSexPhrase("", "") + ", " + GetAddress_FormToNPC(NPChar) + "。 我将立即命令我的人开始攻击堡垒。 ";
            link.l1.go = "attack_fort_04";
            aData.PartAttaksFort = 4;
            Diag.TempNode = "Siegehelp_0";
        break;
		
		case "Talk_Capture_City":
            AfterTownBattle();  // 所有人都自由了
            LAi_LoginInCaptureTown(NPChar, false);
            aData.win = 1;
            EndOfTheSiege("End");
            NPChar.location = "";
            int ilt = makeint(sti(aData.loot)/sti(aData.PartAttaksFort));
            dialog.text = "你好, 船长! 那肯定是一场艰苦的战斗, 但我们设法打破了城镇防御者的激烈抵抗。 我们掠夺了" + sti(aData.loot) +
                          "比索。 根据我们的协议, 你的份额是" + ilt +
                          "。 请接受这笔钱; 你当然 deserve 每一分钱。 现在请原谅我, 但我必须回到我的事务中。 ";
            link.l1 = "既然如此, 我将离开你, " + GetAddress_FormToNPC(NPChar) + "。 再见! ";
            link.l1.go = "exit";
            //AddDialogExitQuest("End_Siege_and_Attaks_City");

            Diag.TempNode = "no_return_02";
            AddMoneyToCharacter(PChar, ilt);
            ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
            ChangeCharacterComplexReputation(PChar,"nobility", 10);
            AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 80);
            AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 100);
            AddCharacterExpToSkill(GetMainCharacter(), "Defence", 100);
            AddCharacterExpToSkill(GetMainCharacter(), "Accuracy", 100);
            AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 100);
            AddCharacterExpToSkill(GetMainCharacter(), "Fortune", 80);
            aData.loot = sti(aData.loot) - ilt;
            if (CheckAttribute(PChar, "quest.LeaveTown")) Pchar.quest.LeaveTown.over = "yes";
            //--> 传闻
            SiegeRumour("我听说你在攻击" + NationNameSK(sti(aData.conation)) + "殖民地 - " + GetCityName(aData.Colony) + "时帮助了我们的中队! 我们非常感谢你, " + GetAddress_Form(NPChar) + "。 ", "", sti(aData.nation), -1, 30, 3);
            //< —传闻
		break;

        case "no_return_02":
            dialog.text = "啊哈, 船长! 你找我有事吗? ";
            link.l1 = "不, " + GetAddress_FormToNPC(NPChar) + "。 再见! ";
            link.l1.go = "exit";
            Diag.TempNode = "no_return_02";
		break;
		
		case "GoldSquadron":
            ref rch = Group_GetGroupCommander("Sea_Head_of_Gold_Squadron");
            if (NPChar.id == rch.id)
            {
    			dialog.text = "我在听您说, 但请快速说明您的来意, 我时间不多。 我有一项重要且秘密的任务, 并且奉命在公海击沉所有可能对我们护航队构成危险的可疑船只。 ";                          
                link.l1 = "既然如此, 我不再占用您的时间了。 祝你好运, " + GetAddress_FormToNPC(NPChar) + "。 ";
                link.l1.go = "exit";

            }
            else
            {
                Dialog.text = "我无权与您打交道。 请和我们中队的指挥官谈谈。 他的名字是" + GetFullName(rch) +
                              ", 你可以在" + XI_ConvertString(RealShips[sti(rch.Ship.Type)].BaseName) + "''" + rch.Ship.Name + "''上找到他。 ";
                link.l1 = "谢谢。 我会照你说的做。 ";
                link.l1.go = "exit";

            }
            Diag.TempNode = "GoldSquadron";
		break;
		
		case "WM_Captain":
			dialog.text = "很高兴见到你, 我叫" + GetFullName(npchar) + "。 那么你是来帮助我们的? 如果是这样, 我特别高兴, 因为我们目前的情况确实很危急 - 我们独自在一个无人居住的岛屿岸边, 船几乎不能航行, 船员损失惨重... ";
			link.l1 = "正如我听说的, 你与海盗发生了战斗, 然后又遭遇了风暴... ";
			link.l1.go = "WM_Captain_1";
			pchar.quest.DesIsland_Over.over = "yes";//移除中断
		break;
		
		case "WM_Captain_1":
			dialog.text = "没错。 我的船在战斗中受损严重 - 我们甚至不得不抵御那些海盗混蛋发起的登船攻击。 后来, 我们遭遇了风暴... 哦, 我甚至不想去想它。 我们被冲到了这个荒凉的海岸。 我们已经修理了一个星期的船, 但你自己看看: 只剩下五十个人了, 而且我们还缺少木板 - 我们该从哪里弄来呢? 丛林吗? 显然是。 每天努力工作, 但我们只弄到了所需材料的五分之一\n带着这样的损伤航行无异于自杀。 现在你知道我们的情况了, 船长... ";
			link.l1 = "是啊... 你的处境令人同情。 让我们想想我们能做什么, 以及我如何帮助你。 ";
			link.l1.go = "WM_Captain_2";
		break;
		
		case "WM_Captain_2":
			dialog.text = "唉, 我希望我们有足够的木板和帆布 - 在这种情况下, 我们一周内就能修好船\n船长, 既然你是特意来这里的, 也许你可以访问最近的港口, 购买我们需要的材料? 这将解决我们的问题。 不用担心钱, 我会补偿所有费用。 ";
			link.l1 = "当然。 你具体需要运送什么, 多少? ";
			link.l1.go = "WM_Captain_3";
		break;
		
		case "WM_Captain_3":
			pchar.questTemp.WPU.Escort.Planks = 300 + hrand(5)*10;
			pchar.questTemp.WPU.Escort.Sailcloth = 150 + hrand(10)*10;
			pchar.questTemp.WPU.Escort.Linen = 70 + hrand(7)*10;
			dialog.text = "我已经算好了。 考虑到我们已经有的材料, 我需要" + FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Planks)) + "块木板, " + FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Sailcloth)) + "帆布和" + FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Linen)) + "棉花。 有了这些材料, 我们可以在一周内修好船, 然后就可以起航了。 ";
			link.l1 = "好的。 我会把你需要的所有材料都带来。 等着我 - 我不会超过十天回来。 ";
			link.l1.go = "WM_Captain_4";
		break;
		
		case "WM_Captain_4":
			dialog.text = "非常感谢, 船长! 现在我放心了。 我们会等待并祈祷你成功归来! ";
			link.l1 = "别担心。 很快你就会有修理所需的一切。 ";
			link.l1.go = "exit";
			AddQuestRecord("Escort", "27");
			AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
			AddQuestUserData("Escort", "sIsland", XI_ConvertString("Colony"+pchar.questTemp.WPU.Current.TargetIslandID));
			AddQuestUserData("Escort", "sQty1", FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Planks)));
			AddQuestUserData("Escort", "sQty2", FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Sailcloth)));
			AddQuestUserData("Escort", "sQty3", FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Linen)));
			Diag.TempNode = "WM_Captain_again";
			SetFunctionTimerCondition("WM_Captain_Over", 0, 0, 11, false);
			pchar.questTemp.WPU.Escort = "wait";
		break;
		
		case "WM_Captain_again":
			dialog.text = "我们热切期待您的归来, 船长! ";
			link.l1 = "起锚! ";
			link.l1.go = "exit";
			Diag.TempNode = "WM_Captain_again";
		break;
		
		case "WM_Captain_5":
			dialog.text = "太好了! 现在我们可以开始修船了! ";
			link.l1 = "我的人会帮你 - 这样会更快。 此外, 我必须陪你到" + XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity) + "的殖民地, 所以我们越早完成修理, 对我越好。 ";
			link.l1.go = "WM_Captain_6";
		break;
		
		case "WM_Captain_6":
			pchar.questTemp.WPU.Current.TargetIslandID.Shore = SelectQuestShoreLocationFromSea(pchar.questTemp.WPU.Current.TargetIslandID);
			dialog.text = "真的, 我不知道该如何正确感谢你, 船长... 请命令将材料卸到一个叫做" + XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID.Shore) + "的海湾 - 我们在那里已经准备好一切进行修理。 ";
			link.l1 = "好的。 我们岸上见。 ";
			link.l1.go = "exit";
			AddQuestRecord("Escort", "29");
			AddQuestUserData("Escort", "sShore", XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID.Shore+"Gen"));
			pchar.quest.DisasterShip_WMC.win_condition.l1 = "location";
			pchar.quest.DisasterShip_WMC.win_condition.l1.location = pchar.questTemp.WPU.Current.TargetIslandID.Shore;
			pchar.quest.DisasterShip_WMC.function = "RepairShip_Prepare";
			Diag.TempNode = "WM_Captain_repeat";
		break;
		
		case "WM_Captain_repeat":
			dialog.text = "我们什么时候开始修理, 船长? 我会在岸上等你。 ";
			link.l1 = "是的, 当然。 我现在就走。 ";
			link.l1.go = "exit";
			Diag.TempNode = "WM_Captain_repeat";
		break;
		
		case "Repair_start":
			dialog.text = "嗯, 一切似乎都准备好修理了。 我想我们大约五天就能完成。 ";
			link.l1 = "非常好! 反正我打算探索这个岛, 所以我会好好利用这段时间。 ";
			link.l1.go = "Repair_start_1";
		break;
		
		case "Repair_start_1":
			DialogExit();
			pchar.quest.WM_Captain_Over.over = "yes";//移除中断
			sld = characterFromId("WMCaptain");
			LAi_SetImmortal(sld, false);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			RemoveCharacterGoods(pchar, GOOD_PLANKS, sti(pchar.questTemp.WPU.Escort.Planks));
			RemoveCharacterGoods(pchar, GOOD_SAILCLOTH, sti(pchar.questTemp.WPU.Escort.Sailcloth));
			RemoveCharacterGoods(pchar, GOOD_COTTON, sti(pchar.questTemp.WPU.Escort.Linen));
			DoQuestFunctionDelay("RepairShip_WithoutMasts", 5.0);
		break;
		
		case "Repair_end":
			dialog.text = "好了, 就这样。 我们修好了, 船可以起航了。 我们什么时候出发, 船长? ";
			link.l1 = "如果你准备好了, 我觉得没有必要再拖延了。 起锚! ";
			link.l1.go = "Repair_end_1";
		break;
		
		case "Repair_end_1":
			DialogExit();
			sld = characterFromId("WMCaptain");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 5.0);
			AddQuestRecord("Escort", "30");
			AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
			AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity));
			SetFunctionTimerCondition("DisasterShipWM_Over", 0, 0, 25, false);
			log_info("你有25天时间将" + pchar.questTemp.WPU.Escort.ShipBaseName + "'" + pchar.questTemp.WPU.Escort.ShipName + "'护送到" + XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen") + "港");
			pchar.quest.DisasterShip_final.win_condition.l1 = "location";
			pchar.quest.DisasterShip_final.win_condition.l1.location = pchar.questTemp.WPU.Escort.StartCity +"_town";
			pchar.quest.DisasterShip_final.function = "WMShip_final";
		break;
		
		case "WMShip_final":
			pchar.quest.Escort_fail.over = "yes";
			pchar.quest.DisasterShipWM_Over.over = "yes";//移除两个中断
			RemoveCharacterCompanion(Pchar, characterFromID("WMCaptain"));//移除同伴
			pchar.questTemp.WPU.Escort.LevelUp_1Money = sti(pchar.questTemp.WPU.Escort.Planks)*15+sti(pchar.questTemp.WPU.Escort.Sailcloth)*9+sti(pchar.questTemp.WPU.Escort.Linen)*45;//材料费用
			dialog.text = "我想再次感谢你, 船长 - 你极大地帮助了我和我的船员摆脱了困境。 正如我承诺的, 我会补偿修理我船所需的材料费用。 这里是" + FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.LevelUp_1Money)) + ", 请收下。 这是我个人给你的礼物。 ";
			link.l1 = "我很高兴能帮助你。 ";
			link.l1.go = "WMShip_final_1";
		break;
		
		case "WMShip_final_1":
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Escort.LevelUp_1Money));
			TakeNItems(pchar, "obereg_"+(hrand(10)+1), 1);
			dialog.text = "现在, 是时候说再见了, 船长。 别忘了去港口管理局 - 他们在等你。 再见! ";
			link.l1 = "祝你今天愉快, " + npchar.name+ "! ";
			link.l1.go = "WMShip_final_2";
		break;
		
		case "WMShip_final_2":
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			DialogExit();
			sld = characterFromId("WMCaptain");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1WM")) AddQuestRecord("Escort", "31");
			if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1VSP")) AddQuestRecord("Escort", "37");
			if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1S")) AddQuestRecord("Escort", "40");
			AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.LevelUp_1Money)));
			AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
			AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
		break;
		
		case "VSP_Captain":
			dialog.text = "是这样吗? 我还以为他们把我们忘了。 是的, 我的船受损最严重。 风暴迫使海盗停止攻击我们的商队后, 我们只能与自然力量抗争。 我们被冲到了这个荒凉的海岸\n花了几天时间修理和休息。 我们刚要起航, 这些异教徒又袭击了我们\n然后风暴再次袭来 - 我们以为上帝终于决定结束我们, 但你来了。 感谢圣母玛利亚! 再次感谢你, 船长! ";
			link.l1 = "都过去了, " + GetAddress_FormToNPC(NPChar) + "。 现在我必须护送你到" + XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen") + ", 以保护它免受其他可能的麻烦。 你现在准备好出发了吗? 风暴已经开始减弱。 ";
			link.l1.go = "VSP_Captain_1";
		break;
		
		case "VSP_Captain_1":
			dialog.text = "当然! 我们离开这个地方越早, 我的人就越平静 - 他们已经受了太多苦。 我们起航吧! ";
			link.l1 = "跟着我的船 - 让你的船员冷静下来, 现在没什么可害怕的了。 ";
			link.l1.go = "VSP_Captain_2";
		break;
		
		case "VSP_Captain_2":
			pchar.quest.DisasterShip_GetOut.over = "yes";
			DialogExit();
			Group_DelCharacter("WMShip", "WMCaptain");//否则会有克隆
			sld = characterFromId("WMCaptain");
			LAi_SetImmortal(sld, false);
			SetCharacterRemovable(sld, false);
			sld.CompanionEnemyEnable = false; //永远是朋友
			SetCompanionIndex(pchar, -1, sti(sld.index));
			sld.loyality = MAX_LOYALITY;
			AddQuestRecord("Escort", "36");
			AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
			SetFunctionTimerCondition("DisasterShipWM_Over", 0, 0, 25, false);
			log_info("你有25天时间将" + pchar.questTemp.WPU.Escort.ShipBaseName + "'" + pchar.questTemp.WPU.Escort.ShipName + "'护送到" + XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen") + "港");
			pchar.questTemp.WPU.Escort = "win";
			pchar.quest.Escort_fail.win_condition.l1 = "NPC_Death";//护送对象沉没的中断
			pchar.quest.Escort_fail.win_condition.l1.character = "WMCaptain";
			pchar.quest.Escort_fail.function = "DisasterShipWM_failed";
			pchar.quest.DisasterShip_final.win_condition.l1 = "location";
			pchar.quest.DisasterShip_final.win_condition.l1.location = pchar.questTemp.WPU.Escort.StartCity +"_town";
			pchar.quest.DisasterShip_final.function = "WMShip_final";
			Diag.currentnode = "VSP_Captain_again";
			Delete_EscortStorm();//移除风暴
		break;
		
		case "VSP_Captain_again":
			dialog.text = "我们起航吗, 船长? ";
			link.l1 = "当然。 我现在回我的船。 ";
			link.l1.go = "exit";
			Diag.TempNode = "VSP_Captain_again";
		break;
		
		case "VSPShip_final":
			pchar.quest.Escort_fail.over = "yes";
			pchar.quest.DisasterShipWM_Over.over = "yes";//移除两个中断
			RemoveCharacterCompanion(Pchar, characterFromID("WMCaptain"));//移除同伴
			pchar.questTemp.WPU.Escort.LevelUp_1Money = 10000+sti(pchar.rank)*200;
			dialog.text = "我想再次感谢你, 船长 - 你极大地帮助了我和我的船员摆脱了这个困境。 这里是" + FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.LevelUp_1Money)) + "。 全体船员凑的, 所以别想拒绝。 这是我个人给你的礼物。 ";
			link.l1 = "我很高兴能帮助你! ";
			link.l1.go = "WMShip_final_1";
		break;
		
		case "SShip_final":
			pchar.questTemp.WPU.Escort.LevelUp_1Money = 5000+sti(pchar.rank)*100;
			RemovePassenger(Pchar, npchar);//移除乘客
			dialog.text = "我想再次感谢你, 船长, 感谢你把我们从这个烂摊子中拯救出来。 拿着这些硬币 - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.LevelUp_1Money)) + " 还有这个礼物。 虽然不多, 但这是我能做的一切来感谢你所做的一切。 请不要拒绝这个提议\n我以前的船员都对你和你与印第安人和海盗的战斗感到惊讶。 他们都希望加入你。 我希望你不会拒绝刚刚失去船只的水手们的忠诚服务申请? ";
			link.l1 = "当然不会。 我会很高兴收下它。 我很高兴能帮助你! ";
			link.l1.go = "WMShip_final_1";
		break;
		
		//荷兰人的 Gambit
		case "Stivesant_1":
			DelLandQuestMark(npchar);
			dialog.text = "好的。 但是, 先生, 你能解释一下这里发生了什么吗? 你怎么会指挥'美丰'号! 朗威发生了什么事? ";
			link.l1 = "我有你需要的所有解释 - 还有一些其他重要信息。 ";
			link.l1.go = "Stivesant_2";			
		break;
		
		case "Stivesant_2":
			dialog.text = "那我洗耳恭听。 ";
			link.l1 = "威廉斯塔德发生了政变。 卢卡斯.罗登堡取代了总督的位置, 并将马蒂亚斯.贝克投入监狱, 理由是荒谬的怀疑他与英国情报部门有联系。 ";
			link.l1.go = "Stivesant_3";			
		break;
		
		case "Stivesant_3":
			dialog.text = "嗯... 先生, 你告诉我的事情真的很令人惊讶。 我不久前收到了来自威廉斯塔德的消息, 里面没有这样的内容。 ";
			link.l1 = "请听我说完, 斯特伊弗桑特先生。 你一定是通过罗登堡得到的消息, 他一定确信你不会去库拉索。 ";
			link.l1.go = "Stivesant_4";			
		break;
		
		case "Stivesant_4":
			dialog.text = "先生, 我越来越不喜欢你说的话。 你到底是谁? ";
			link.l1 = "我只是一个船长, 一个关心荷兰殖民者命运的人。 卢卡斯.罗登堡命令朗威摧毁你的船并杀死你。 由于'美丰'号不会引起你的怀疑, 他本可以毫不费力地执行。 ";
			link.l1.go = "Stivesant_5";			
		break;
		
		case "Stivesant_5":
			dialog.text = "所以, 你的意思是说卢卡斯... ";
			link.l1 = "决定以最简单的方式让你失去权力 - 简单地消灭你。 除了你, 该地区没有其他人能够对罗登堡在群岛的影响力构成任何重大抵抗。 ";
			link.l1.go = "Stivesant_6";			
		break;
		
		case "Stivesant_6":
			dialog.text = "我不敢相信! ";
			link.l1 = "我不相信贝克与英国情报部门有关联的鬼话, 并进行了自己的调查。 我发现装满精选恶棍的'美丰'号前往菲利普斯堡。 我追上了他们并发起了战斗。 朗威被俘, 他给了我所有这些信息, 包括你的下落。 ";
			link.l1.go = "Stivesant_7";			
		break;
		
		case "Stivesant_7":
			dialog.text = "嗯... 这似乎是可能的。 除了罗登堡, 没有人知道或可能知道我的日程和路线! 该死的! 这是叛国! 朗威在哪里? ! ";
			link.l1 = "作为交换, 我释放了他, 以换取他自愿供认。 我必须说, 他不太愿意执行罗登堡的命令, 但他也不能无视它。 他还说他不会再为罗登堡服务 - 最后这件肮脏的事情让他忍无可忍。 ";
			link.l1.go = "Stivesant_8";			
		break;
		
		case "Stivesant_8":
			dialog.text = "好吧... " +GetFullName(pchar)+ "船长, 你将和我一起去威廉斯塔德。 你将乘坐'美丰'号在我的船前面航行。 如果你说的是真的, 卢卡斯必须被逮捕, 你将在这方面提供帮助。 但如果你骗了我... 你只能怪自己。 ";
			link.l1 = "对我来说, 骗你没有意义, 先生。 我们快点吧! ";
			link.l1.go = "Stivesant_9";			
		break;
		
		case "Stivesant_9":
			DialogExit();
			Diag.CurrentNode = "Stivesant_10";
			AddQuestRecord("Holl_Gambit", "3-52");
			pchar.questTemp.HWIC.Self = "WayWithStivesant";
			Group_DelCharacter("Stivesant_Halleon", "Stivesant");
			SetCharacterRemovable(npchar, false);
			npchar.CompanionEnemyEnable = false; //永远是朋友
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.loyality = 40;
			DeleteAttribute(npchar, "LifeDay");
			pchar.quest.Seek_Piter.win_condition.l1 = "location";
			pchar.quest.Seek_Piter.win_condition.l1.location = "Villemstad_town";
			pchar.quest.Seek_Piter.win_condition.l2 = "Day";
			pchar.quest.Seek_Piter.function = "StivesantOnStreet";
			pchar.quest.Terms_Over.win_condition.l1 = "Timer";
			pchar.quest.Terms_Over.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Terms_Over.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 15);
			pchar.quest.Terms_Over.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 15);
			pchar.quest.Terms_Over.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 15);
			pchar.quest.Terms_Over.function = "QuestShipsTerms_Over";
			AddMapQuestMarkCity("Villemstad", false);
		break;
		
		case "Stivesant_10":
			dialog.text = "船长, 去'美丰'号。 我们该起航了。 ";
			link.l1 = "是的, 先生, 当然。 ";
			link.l1.go = "exit";
			Diag.TempNode = "Stivesant_10";
		break;
		
		case "Keller_1":
			dialog.text = "非常有趣! 请告诉我你的故事。 我会尽力帮助你。 ";
			link.l1 = "凯勒先生, 你还记得几个月前你去威廉斯塔德的路上遇到一艘快速帆船的事吗? 上面有一家犹太难民。 你在那艘船上用餐, 然后继续你的旅程。 ";
			link.l1.go = "Keller_2";
		break;
		
		case "Keller_2":
			dialog.text = "是的, 我想是这样... 是的, 我现在记得很清楚。 那么, 怎么了? ";
			link.l1 = "那天那艘快速帆船被海盗击沉了。 只有两名难民设法自救 - 所罗门和他的女儿阿比盖尔。 他们在袭击发生地几英里外的一个岛上找到了避难所。 我需要找到那个岛。 你能回忆起你在哪里遇到那艘快速帆船吗? 这非常重要。 ";
			link.l1.go = "Keller_3";
		break;
		
		case "Keller_3":
			dialog.text = "这就是你需要的全部吗? 我知道这个岛。 它很近, 在特立尼达和库拉索之间。 一个小的荒芜无人岛。 那里甚至没有印第安人。 ";
			link.l1 = "你知道它的大概坐标吗? ";
			link.l1.go = "Keller_4";
		break;
		
		case "Keller_4":
			dialog.text = "我可以告诉你精确的坐标。 北纬12度48分, 西经64度41分。 在那里寻找。 这个岛相当小, 但你应该能轻松找到它。 ";
			link.l1 = "谢谢你, 凯勒先生! 你帮了我很大的忙。 再见。 ";
			link.l1.go = "Keller_5";
		break;
		
		case "Keller_5":
			DialogExit();
			Diag.CurrentNode = "Keller_6";
			pchar.quest.Keller_fail.over = "yes";
			pchar.questTemp.HWIC_Coordinates = "true"; //通过船舱寻找岛屿的坐标属性
			DeleteAttribute(pchar, "questTemp.HWICMC");
			AddQuestRecord("Holl_Gambit", "3-66");
		break;
		
		case "Keller_6":
			dialog.text = "你还想要什么吗, 船长? ";
			link.l1 = "不, 谢谢。 我已经在回我的船了。 ";
			link.l1.go = "exit";
			Diag.TempNode = "Keller_6";
		break;
		
		// belamour 渔船 -->
		case "FishingBoat":
			pchar.GenQuest.FishingBoatSecondTime = true;
			dialog.text = "没什么特别的, 这是一艘渔船, 我们在这里捕鱼。 你总得想办法谋生。 ";
			link.l1 = "是的, 我同意, 这就是时代... ";
			link.l1.go = "FishingBoat_1";			
		break;
		
		case "FishingBoat_1":
			Diag.TempNode = "FishingBoat_1";
			dialog.text = "那你想要什么? ";
			link.l1 = "我想" + GetSexPhrase("", "") + "了解群岛的最新消息。 ";
            link.l1.go = "rumours_capitan";
			link.l2 = "你今天的捕获量如何? 能卖吗? 食物对我有帮助... ";
			link.l2.go = "FishingBoat_2";
			link.l3 = "没什么特别的, 只是来问候你! ";
    		link.l3.go = "exit";	
	
		break;
		
		case "FishingBoat_2":
			if(GetDataDay() < 11) 
			{
				if(sti(RealShips[sti(npchar.ship.type)].basetype) == SHIP_TARTANE) iTemp = 100 + hrand(100);
				else iTemp = 200 + hrand(100);
				iMoney = sti(GetCurrentIslandGoodsPrice(GOOD_FOOD)*0.66);
				pchar.GenQuest.FishingBoatITemp = iTemp;
				pchar.GenQuest.FishingBoatIMoney = iMoney;
				
				dialog.text = "今天收获很好, 刚有时间拉出渔网。 我们可以卖给你, 甚至比商店便宜 - 反正我们把鱼卖给当地商人。 如果我们把这些都换算成食物... 我们现在有" + iTemp + ", 我们可以以每件" + iMoney + "比索的价格出售。 你要多少? ";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитого провианта";
				link.l2 = "你知道, 我改变主意了, 不想买你的食物了。 ";	
				link.l2.go = "exit";
				
			}
			if(GetDataDay() > 10 && GetDataDay() < 21) 
			{
				Diag.TempNode = "FishingBoat_1";
				dialog.text = "说实话, 是的, 根本没有鱼... 今天几乎什么都没钓到。 但鱼叉还多余 - 本想抓些大鱼或鲸鱼, 如果幸运的话... 也许你需要鱼叉? ";
				link.l1 = "不, 我对鱼叉不感兴趣。 ";
				link.l1.go = "exit";
				link.l2 = "嗯, 鱼叉在合适的人手中也是有用的东西。 我可能会买。 ";
				link.l2.go = "Гарпуны";
			}
			if(GetDataDay() > 20)
			{
				dialog.text = "说实话, 是的, 根本没有鱼... 今天几乎什么都没钓到。 所以没什么可卖的。 除非... 我有一些小饰品, 也许有什么会让你感兴趣。 想看看吗? ";
				link.l1 = "不, 我对小饰品不感兴趣。 ";
				link.l1.go = "exit";
				link.l2 = "真遗憾没有收获。 好吧, 至少看看你的小饰品 - 突然有什么会吸引... ";
				link.l2.go = "Торговля";
			}	
		break;
		
		case "Количество вбитого провианта":
			Diag.TempNode = "FishingBoat_1";
			iQty = sti(dialogEditStrings[3]);
			iTemp = makeint(pchar.GenQuest.FishingBoatITemp);
			pchar.GenQuest.FishingBoatIQty = iQty;
			iMoney = makeint(pchar.GenQuest.FishingBoatIMoney);
			if(iQty > iTemp)
			{
				dialog.text = "你要太多了... 我没有那么多! 你能少买些吗? ";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитого провианта повтор";	
				link.l2 = "你知道, 我改变主意了, 不想买你的食物了。 ";	
				link.l2.go = "exit";
			}	
			if(iQty < 1)
			{
				dialog.text = "你在开玩笑吗? 你需要食物吗? 如果需要, 多少? ";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитого провианта повтор";	
				link.l2 = "你知道, 我改变主意了, 不想买你的食物了。 ";	
				link.l2.go = "exit";
			}
			if(iQty > 0 && iQty <= iTemp)
			{
				dialog.text = "成交! " + sti(iQty*iMoney) + "比索。 ";
				if(sti(pchar.money) < iQty*iMoney)
				{
					link.l1 = "嗯, 我没有那么多钱。 下次吧。 ";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = "成交! 把货物拖到我的船上。 ";
					link.l1.go = "Удачная покупка";
					link.l2 = "你知道, 我改变主意了, 不想买你的食物了。 ";
					link.l2.go = "exit";
				}
			}
		break;
		
		case "Количество вбитого провианта повтор":
			Diag.TempNode = "FishingBoat_1";
			iQty = sti(dialogEditStrings[3]);
			iTemp = makeint(pchar.GenQuest.FishingBoatITemp);
			pchar.GenQuest.FishingBoatIQty = iQty;
			iMoney = makeint(pchar.GenQuest.FishingBoatIMoney);
			if(iQty > iTemp)
			{
				dialog.text = "你要太多了... 我没有那么多! 你能少买些吗? ";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитого провианта";	
				link.l2 = "你知道, 我改变主意了, 不想买你的食物了。 ";	
				link.l2.go = "exit";
			}	
			if(iQty < 1)
			{
				dialog.text = "你在开玩笑吗? 你需要食物吗? 如果需要, 多少? ";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитого провианта";	
				link.l2 = "你知道, 我改变主意了, 不想买你的食物了。 ";	
				link.l2.go = "exit";
			}
			if(iQty > 0 && iQty <= iTemp)
			{
				dialog.text = "成交! " + sti(iQty*iMoney) + "比索。 ";
				if(sti(pchar.money) < iQty*iMoney)
				{
					link.l1 = "嗯, 我没有那么多钱。 下次吧。 ";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = "成交! 把货物拖到我的船上。 ";
					link.l1.go = "Удачная покупка";
					link.l2 = "你知道, 我改变主意了, 不想买你的食物了。 ";
					link.l2.go = "exit";
				}
			}
		break;
		
		case "Удачная покупка":
			Diag.TempNode = "First time";
			Diag.CurrentNode = "First time";
			iQty = makeint(pchar.GenQuest.FishingBoatIQty);
			iMoney = makeint(pchar.GenQuest.FishingBoatIMoney);
			iTemp = iQty*iMoney;
			DialogExit();
			SetCharacterGoods(pchar, GOOD_FOOD, GetCargoGoods(pchar, GOOD_FOOD)+iQty);
			AddMoneyToCharacter(pchar, -iTemp);
		break;
		
		case "Гарпуны":
				Diag.TempNode = "FishingBoat_1";
				iTemp = 5+hrand(5);
				pchar.GenQuest.FishingBoatITemp = iTemp;
				dialog.text = "我们有" +iTemp+ "件。 我们可以以每把鱼叉一百比索的价格出售。 你需要多少? ";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитых гарпунов";
				link.l2 = "你知道, 我改变主意了, 我不需要鱼叉。 ";	
				link.l2.go = "exit";
		break;
		
		case "Количество вбитых гарпунов":
			iQty = sti(dialogEditStrings[3]);
			iTemp = makeint(pchar.GenQuest.FishingBoatITemp);
			pchar.GenQuest.FishingBoatIQty = iQty;
			Diag.TempNode = "FishingBoat_1";
			if(iQty > iTemp)
			{
				dialog.text = "你要太多了... 我没有那么多! 你能少买些吗? ";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитых гарпунов заново";	
				link.l2 = "你知道, 我改变主意了, 我不需要鱼叉。 ";	
				link.l2.go = "exit";
			}	
			if(iQty < 1)
			{
				dialog.text = "你在开玩笑吗? 你需要鱼叉吗? 如果需要, 多少? ";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитых гарпунов заново";	
				link.l2 = "你知道, 我改变主意了, 我不需要鱼叉。 ";	
				link.l2.go = "exit";
			}
			if(iQty > 0 && iQty <= iTemp)
			{
				dialog.text = "成交! " + sti(iQty*100) + "比索。 ";
				if(sti(pchar.money) < iQty*100)
				{
					link.l1 = "嗯, 我没有那么多钱。 下次吧。 ";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = "成交! 我会找到它们的用途。 ";
					link.l1.go = "Удачная покупка гарпунов";
					link.l2 = "你知道, 我改变主意了, 我不需要鱼叉。 ";
					link.l2.go = "exit";
				}
			}
		break;
		
		case "Количество вбитых гарпунов заново":
			iQty = sti(dialogEditStrings[3]);
			iTemp = makeint(pchar.GenQuest.FishingBoatITemp);
			pchar.GenQuest.FishingBoatIQty = iQty;
			Diag.TempNode = "FishingBoat_1";
			if(iQty > iTemp)
			{
				dialog.text = "你要太多了... 我没有那么多! 你能少买些吗? ";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитых гарпунов";	
				link.l2 = "你知道, 我改变主意了, 我不需要鱼叉。 ";	
				link.l2.go = "exit";
			}	
			if(iQty < 1)
			{
				dialog.text = "你在开玩笑吗? 你需要鱼叉吗? 如果需要, 多少? ";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитых гарпунов";	
				link.l2 = "你知道, 我改变主意了, 我不需要鱼叉。 ";	
				link.l2.go = "exit";
			}
			if(iQty > 0 && iQty <= iTemp)
			{
				dialog.text = "成交! " + sti(iQty*100) + "比索。 ";
				if(sti(pchar.money) < iQty*100)
				{
					link.l1 = "嗯, 我没有那么多钱。 下次吧。 ";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = "成交! 我会找到它们的用途。 ";
					link.l1.go = "Удачная покупка гарпунов";
					link.l2 = "你知道, 我改变主意了, 我不需要鱼叉。 ";
					link.l2.go = "exit";
				}
			}
		break;
		
		case "Удачная покупка гарпунов":
			DialogExit();
			Diag.TempNode = "First time";
			Diag.CurrentNode = "First time";
			iQty = makeint(pchar.GenQuest.FishingBoatIQty);
			TakeNItems(pchar, "slave_01", iQty);
			AddMoneyToCharacter(pchar, -iQty*100);
			
		break;
		
		case "Торговля":
			DialogExit();
			Diag.TempNode = "First time";
			Diag.CurrentNode = "First time";
			if(!CheckAttribute(pchar,"GenQuest.FishingBoatDialogEnb")) pchar.GenQuest.FishingBoatDialogEnb = true;
			LaunchItemsTrade(NPChar, 0);
		break;
		
		case "Особые товары":
			if(hrand(2, "&SpeGoo") == 0)
			{
				Diag.TempNode = "First time";
				Diag.CurrentNode = "First time";
				pchar.GenQuest.FishingBoatDialogEnb = "no special goods";
				dialog.text = "不, 没有别的了。 这是一艘渔船! 这里还能有什么? ";
				link.l1 = "好吧, 我知道了。 ";
				link.l1.go = "exit";
			}
			else if(hrand(2, "&SpeGoo") == 1)
			{
				if(ChangeContrabandRelation(pchar, 0) > 5)
				{
					
					dialog.text = "嗯... 我这里有一样小东西... 我留着, 想卖给某人。 但我会为此收很多钱! 而且我不会再提供第二次。 你要看吗? ";
					link.l1 = "给我看看, 看看是什么小东西。 ";
					link.l1.go = "Особые товары предметы";
				}
				else
				{
					Diag.TempNode = "First time";
					Diag.CurrentNode = "First time";
					pchar.GenQuest.FishingBoatDialogEnb = "no special goods";
					dialog.text = "不, 没有别的了。 这是一艘渔船! 这里还能有什么? ";
					link.l1 = "好吧, 我知道了。 ";
					link.l1.go = "exit";
				}
			}
			else
			{
				pchar.GenQuest.FishingBoatDialogEnb = "no special goods";
				Diag.TempNode = "First time";
				Diag.CurrentNode = "First time";
				if(ChangeContrabandRelation(pchar, 0) > 5)
				{
					if(GetDataDay() < 8)
					{	
						iMoney = GetStoreGoodsPrice(&Stores[SantaCatalina_STORE], GOOD_SANDAL, PRICE_TYPE_BUY, pchar, 1);
						iTemp = GOOD_SANDAL;
						sTemp = "单位的备用物资";
					}
					if(GetDataDay() > 7 && GetDataDay() < 15)
					{
						iMoney = GetStoreGoodsPrice(&Stores[PortSpein_STORE], GOOD_OIL, PRICE_TYPE_BUY, pchar, 1);
						iTemp = GOOD_OIL;
						sTemp = "桶船用焦油"; 
					}
					if(GetDataDay() > 14 && GetDataDay() < 22) 
					{
						iMoney = GetStoreGoodsPrice(&Stores[BasTer_STORE], GOOD_ROPES, PRICE_TYPE_BUY, pchar, 1);
						iTemp = GOOD_ROPES;
						sTemp = "船用绳索束"; 
					}
					if(GetDataDay() > 21) 
					{
						iMoney = GetStoreGoodsPrice(&Stores[Villemstad_STORE], GOOD_SHIPSILK, PRICE_TYPE_BUY, pchar, 1);
						iTemp = GOOD_SHIPSILK;
						sTemp = "船用丝绸卷";
					}
					iQty = 20 + sti(rand(6)*5);
					pchar.GenQuest.FishingBoatITemp = iTemp;
					pchar.GenQuest.FishingBoatIMoney = iMoney;
					pchar.GenQuest.FishingBoatIQty = iQty;
					
					dialog.text = "嗯... 我这里有一样货物... 纯粹是偶然在海湾岸边发现的。 这是" + iQty + " " + sTemp + "。 每件价格是" + iMoney + "。 但我只会一次性全部出售, 而且不会再提供第二次。 这样就不会有外人知道... 明白吗? ";
					link.l1 = "不, 我不想要可疑的货物, 谢谢。 我不会告诉任何人, 别担心。 ";
					link.l1.go = "exit";
					if(sti(pchar.money) >= iMoney*iQty)
					{
						link.l2 = "我明白你的意思。 但这货物值得。 我买了。 让他送到我的船上。 ";
						link.l2.go = "Купили стратегический товар";
					}
				}
			}
		break;
		
		case "Особые товары предметы":
			pchar.GenQuest.FishingBoatDialogEnb = "no special goods";
			Diag.TempNode = "First time";
			Diag.CurrentNode = "First time";
			if(ChangeContrabandRelation(pchar, 0) > 5)
			{
				switch(GetDataDay())
				{
					case 21: sTemp = "mushket1";  break;
					case 22: sTemp = "cirass5";   break;
					case 23: sTemp = "blade_16";  break;
					case 24: sTemp = "blade_04";  break;
					case 25: sTemp = "blade_06";  break;
					case 26: sTemp = "compass1";  break;
					case 27: sTemp = "clock2";    break;
					case 28: sTemp = "pistol4";   break;
					case 29: sTemp = "pistol2";   break;
					case 30: sTemp = "obereg_9";  break;
					case 31: sTemp = "obereg_10"; break;	
				}
				pchar.GenQuest.FishingBoatSTemp = sTemp;
				dialog.text = "这是" + GetItemName(sTemp) + "。 设法弄到... 嗯, 不管从哪里。 想卖给某个鉴赏家。 我只收10000比索就给你! 你要吗? ";
				if(sti(pchar.money) > 9999)
				{
					link.l1 = "我当然要! 这东西很值。 ";
					link.l1.go = "Купили особый товар";
				}
				link.l2 = "不, 我不需要。 我不要。 ";
				link.l2.go = "exit";
			}
		
		break;
		
		case "Купили особый товар":
			Diag.TempNode = "First time";
			Diag.CurrentNode = "First time";
			DialogExit();
			sTemp = pchar.GenQuest.FishingBoatSTemp;
			if(GetDataDay() != 23 || GetDataDay() != 24 || GetDataDay() != 25) 
			{
				TakeNItems(pchar, sTemp, 1);
			}
			else
			{
				sTemp = GetGeneratedItem(sTemp);
				GiveItem2Character(pchar, sTemp);
			}
			AddMoneyToCharacter(pchar, -10000);
		break;
		
		case "Купили стратегический товар":
			Diag.TempNode = "First time";
			Diag.CurrentNode = "First time";
			iQty = makeint(pchar.GenQuest.FishingBoatIQty);
			iMoney = makeint(pchar.GenQuest.FishingBoatIMoney);
			iTemp = makeint(pchar.GenQuest.FishingBoatITemp);
			DialogExit();
			SetCharacterGoods(pchar, iTemp, GetCargoGoods(pchar,iTemp)+iQty);
			AddMoneyToCharacter(pchar, -iMoney*iQty);
		break;
		// < —渔船
	}
}

string GetNumShips(int ship)
{
    string numships;
    switch(ship)
    {
       case 0: numships = "没有船"; break;
       case 1: numships = "一艘船";      break;
       case 2: numships = "两艘船";       break;
       case 3: numships = "三艘船";       break;
       case 4: numships = "四艘船";    break;
       case 5: numships = "五艘船";     break;
       case 6: numships = "六艘船";    break;
    }
    return numships;
}

string GetPart(int part)
{
    string numpart;
    switch(part)
    {
       case 0: numpart = ""; break;
       case 1: numpart = "所有战利品"; break;
       case 2: numpart = "一半战利品"; break;
       case 3: numpart = "三分之一战利品"; break;
       case 4: numpart = "四分之一战利品";      break;
    }
    return numpart;
}

int findPriceStoreMan(ref NPChar)
{
    ref ch;
	int n;
    int storeArray[40];
    int howStore = 0;

	for(n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(ch,Characters[n]);
		if (CheckAttribute(ch, "Dialog.Filename") && ch.Dialog.Filename == "Common_Store.c") // 商店
		{
            //if (sti(ch.nation) !=  sti(NPChar.nation)) continue;
            if (ch.location == "none") continue; // 修复新的。 不可见的岛屿
            storeArray[howStore] = n;
            howStore++;
            
            // homo 05/09/06
            if ( CheckAttribute(NPChar, "FromColony") && NPChar.FromColony == ch.City ) return n;
            //
		}
    }
    if (howStore == 0)
    {
        return -1;
    }
    else
    {
        return storeArray[rand(howStore-1)];
    }
}

int CalcBattleDifficulty()
{
    UpdatePlayerSquadronPower();

    float encPow = 0.0;
    float pchPow = stf(PChar.Squadron.RawPower);

    string sTemp;
    if(CheckAttribute(CharacterRef, "SeaAI.Group.Name"))
        sTemp = CharacterRef.SeaAI.Group.Name;
    else return 0;

    int	iGroupIndex = Group_FindGroup(sTemp);
    if (iGroupIndex < 0)
    {
        Log_TestInfo("НЕТ ГРУППЫ В CalcBattleDifficulty");
        trace("НЕТ ГРУППЫ В CalcBattleDifficulty");
        return 0;
    }

    ref rGroup = Group_GetGroupByIndex(iGroupIndex);
    if (!CheckAttribute(rGroup, "Quest")) return 0;

    aref aCompanions, aCharInfo;
    makearef(aCompanions, rGroup.Quest);
    int qty = GetAttributesNum(aCompanions);

    ref rChar, rShip;
    int iShipType, idx;
    for(int i = 0; i < qty; i++)
    {
        aCharInfo = GetAttributeN(aCompanions, i);
        idx = sti(aCharInfo.index);
        if(idx == -1) continue;
        rChar = GetCharacter(idx);
        if(!CheckAttribute(rChar, "index") || rChar.index == "none" || LAi_IsDead(rChar)) continue;
        iShipType = sti(rChar.Ship.Type);
        if(iShipType == SHIP_NOTUSED) continue;
        rShip = GetRealShip(iShipType);
        encPow += GetRealShipPower(rChar);
    }

    iEncPow = encPow;

    if(pchPow == 0.0)
    {
        if(encPow == 0.0) return 50;
        return 0;
    }

    float fRatio = (encPow * 0.9) / pchPow;

    if(fRatio >= 1.7) return 0; // Кирдык
    // От 50 шанс быстро падает к 0
    if(fRatio >= 1.0)
    {
        return MakeInt(100 * 0.5 * pow((1.7 - fRatio) / 0.7, 2.5));
    }
    // От 50 шанс медленно растёт к 100
    return MakeInt(100 * (0.5 + 0.5 * pow((1 - fRatio), 0.5)));
}

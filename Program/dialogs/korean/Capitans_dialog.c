// разговор с капитаном на палубе  Boal
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
	//belamour рыбацкое судно
	int i, iTemp, iQty;
	string sTemp;
    //homo Осады
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
            case 0:  fort = "English fort"; break;
            case 1:  fort = "French fort"; break;
            case 2:  fort = "Spanish fort"; break;
            case 3:  fort = "Dutch fort"; break;
            case 4:  fort = "Pirate fort"; break;
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
				//--> Jason эскорт 2 уровень
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1WM") && pchar.questTemp.WPU.Escort == "begin" && NPChar.id == "WMCaptain")
				{
					dialog.text = "안녕하십니까, 선장님. 젠장, 당신을 보게 되어 내가 얼마나 기쁜지 모릅니다!";
					link.l1 = "안녕하세요. 제 소개를 하겠습니다 - "+GetFullName(PChar)+". 나도 당신이 무사히 살아 있는 걸 보니 기쁩니다. 바로 당신과 당신의 배를 찾으려고 여기까지 온 것이오.";
					link.l1.go = "WM_Captain";
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1WM") && pchar.questTemp.WPU.Escort == "wait" && NPChar.id == "WMCaptain")
				{
					dialog.text = "내가 부탁한 재료를 가져왔나?";
					if (sti(pchar.questTemp.WPU.Escort.Planks) - GetSquadronGoods(pchar, GOOD_PLANKS) <= 0 && sti(pchar.questTemp.WPU.Escort.Sailcloth) - GetSquadronGoods(pchar, GOOD_SAILCLOTH) <= 0 && sti(pchar.questTemp.WPU.Escort.Linen) - GetSquadronGoods(pchar, GOOD_COTTON) <= 0)
					{
						link.l1 = "그래. 네 배를 수리하는 데 필요한 건 전부 내 창고에 있다.";
						link.l1.go = "WM_Captain_5";
					}
					else
					{
						link.l1 = "아니, 아직 작업 중이야.";
						link.l1.go = "exit";
					}
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1VSP") && pchar.questTemp.WPU.Escort == "toCap" && NPChar.id == "WMCaptain")
				{
					dialog.text = "이봐, "+GetAddress_Form(NPChar)+". 내 이름은 "+GetFullName(NPChar)+", 나는 이 배의 선장이오. 그 빌어먹을 해적 놈들과의 싸움에서 도와주신 데 대해 진심으로 감사의 말씀을 전하오. 당신이 끼어들지 않았다면 우리 처지가 정말로 암울해질 뻔했소. 정말 우리를 구해주셨소, 젠장!";
					link.l1 = "별일 아니었어,  "+GetAddress_FormToNPC(NPChar)+". 제 소개를 하겠습니다 - "+GetFullName(PChar)+", 항만 관리자 부탁으로 당신에게 왔소 "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen")+". 그는 당신의 캐러밴이 겪은 불운에 대해 말해주었고, 당신의 배를 찾으라고 나를 보냈습니다.";
					link.l1.go = "VSP_Captain";
					break;
				}
				//<-- эскорт 2 уровень
				
				if(CheckAttribute(NPChar, "surrendered"))
				{
                    CalcBattleDifficulty();
                    if(iEncPow == -1) iEncPow = 0;
					Pchar.GenQuest.MoneyForCaptureShip = (70 + hrand(60, "&CapSur"+NPChar.id)) * iEncPow;
					if(HasShipTrait(pchar, "trait14")) Pchar.GenQuest.MoneyForCaptureShip = makeint(sti(Pchar.GenQuest.MoneyForCaptureShip) * 1.35);
					dialog.text = "잠깐만, 이러다간 나 죽겠어. 나한테 뭘 원하는 거야?";
					//выкуп
					link.l1 = "이 문제를 평화롭게 해결합시다. 몸값이 아마도 최선의 선택일 것 같소. 금액은 "+Pchar.GenQuest.MoneyForCaptureShip+" 페소면 충분해, "+GetAddress_FormToNPC(NPChar)+". 그리고 나서 꺼져 버려라!";
					link.l1.go = "surrender1";
					// обираем до нитки
					link.l2 = "네가 선창에 뭘 실었는지 좀 보고 싶군. 그리고 나서, 너랑 네 선원들은 원하는 곳으로 가도 된다.";
					link.l2.go = "surrender2";
					break;
				}
				
				//Голландский Гамбит, против всех
				if (CheckAttribute(PChar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "MeetingStivesant" && NPChar.id == "Stivesant")
				{
					dialog.text = "안녕하세요, 나리. 만나서 반갑습니다. 롱웨이 선장님은 아마 나중에 배에 오시겠지요?";
					link.l1 = "안녕하십니까, Stuyvesant 나리. 제 소개를 드리겠습니다 - "+GetFullName(pchar)+". 롱웨이는 오지 않을 거야, 그는 '메이펑'에 없어.";
					link.l1.go = "Stivesant_1";
					pchar.quest.QuestShipsTerms_Over.over = "yes"; //снять таймер
					break;
				}
				if (CheckAttribute(PChar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "FleutOnTrinidad" && NPChar.id == "Keller")
				{
					DelLandQuestMark(npchar);
					dialog.text = "이봐, 선장. 내 플루트에 무슨 일로 온 거지?";
					link.l1 = "좋은 오후입니다, Keller 나리. 제 소개를 드리겠습니다 - "+GetFullName(pchar)+". 나는 색다른 일로 당신의 도움을 구하러 왔소.";
					link.l1.go = "Keller_1";
					break;
					//Голландский гамбит
				}
				// belamour рыбацкое судно -->
				if(npchar.id == "FishingBoatCap")
				{
					if(!CheckAttribute(pchar, "GenQuest.FishingBoatSecondTime"))
					{
						Dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"! 나는 선장이오 "+GetFullName(NPChar)+". 무슨 일로 내 배에 올라왔나?";
						link.l1 = "좋은 하루입니다. 이 만에는 무슨 일로 오셨습니까?";
						link.l1.go = "FishingBoat";
						break;
					}
					else
					{
						Diag.CurrentNode = "first time";
						dialog.text = "다른 이야기를 더 나누고 싶으신가요?";
						link.l1 = "원했어"+GetSexPhrase("","")+" 군도에서 최신 소식을 알아보기 위해.";
						link.l1.go = "rumours_capitan";
						if(CheckAttribute(pchar,"GenQuest.FishingBoatDialogEnb"))
						{
							link.l2 = "다시 한 번 보여줘, 어떤 잡동사니를 팔고 있는지. ";
							link.l2.go = "Торговля";
							if(pchar.GenQuest.FishingBoatDialogEnb != "no special goods")
							{
								link.l3 = "흠, 창고에서 더 찾아보는 게 어때 – 팔 만한 게 나올지도 모르지?";
								link.l3.go = "Особые товары";
							}
						}
						link.l4 = "별일 없어, 그냥 인사하러 왔어!";
						link.l4.go = "exit";	
						break;
					}
				}
				// <-- рыбацкое судно
				
				//belamour legendary edition диалоги, если герой имеет звания и заслуги перед отечеством -->
				// генерал губернатор
				if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
				{
					Dialog.text = "총독 각하, 안녕하십니까! 무엇을 도와드릴까요?";
					link.l1 = "너에게 맡길 일이 있다!";
					link.l1.go = "quests";
					link.l2 = "별일 없고, 그냥 인사하러 왔어!";
					link.l2.go = "exit";
					break;
				}
				// вице адмирал
				if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && sti(Items[sti(pchar.EquipedPatentId)].Nation) == npchar.nation)
				{
					Dialog.text = "내 배에 오신 것을 환영합니다, 부제독 나리! 무엇을 도와드릴까요?";
					link.l1 = "너에게 맡길 일이 있다!";
					link.l1.go = "quests";
					link.l2 = "별일 아니야, 그냥 인사하러 왔어!";
					link.l2.go = "exit";
					break;
				}
				// Офицер с патентом
				if(IsOfficerFullEquip() && sti(Items[sti(pchar.EquipedPatentId)].Nation) == npchar.nation)
				{
					Dialog.text = "동료 일꾼을 만나서 반갑소, 선장! 무엇을 도와드릴까?";
					link.l1 = "너에게 맡길 일이 있다!";
					link.l1.go = "quests";
					link.l2 = "별일 없어, 그냥 인사하러 왔어!";
					link.l2.go = "exit";
					break;
				}			
				// <-- legendary edition
                if (CheckAttribute(NPChar, "EncType")  && NPChar.EncType == "war")
                {
    			    Dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"! 나는 "+GetFullName(NPChar)+" - 소속된 배의 선장 "+NationKingsName(NPChar)+". 함대. 무슨 일로 내 배에 올라온 거지?";
    			}
    			else
                {
    			    Dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"! 내가 선장이야 "+GetFullName(NPChar)+". 무엇 때문에 내 배에 올라탔지?";
    			}
    			link.l1 = "내 이름은 "+GetFullName(Pchar)+". 너와 볼일이 있어!";
    			link.l1.go = "quests";
                link.l2 = "아, 아무것도 아니야, 그냥 "+GetSexPhrase("왔다","왔다")+" 당신을 맞이하게 되어!";
    			link.l2.go = "exit";
            }
            else
            {
                Dialog.text = "눈치채지 못했나, , "+GetAddress_Form(NPChar)+", 우리가 전투 중이라는 거 몰라? 지금 말할 때가 아니야!";
    			link.l1 = "전적으로 동의하오! 내 배로 돌아가겠소.";
    			link.l1.go = "exit";
            }
			Diag.TempNode = "first time";
 		break;

        case "quests":
			// belamour рыбацкое судно -->
			if(npchar.id == "FishingBoatCap")
			{
				if(!CheckAttribute(pchar, "GenQuest.FishingBoatSecondTime"))
				{
					Dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"! 나는 선장이오 "+GetFullName(NPChar)+". 무슨 일로 내 배에 올라왔나?";
					link.l1 = "안녕하시오. 이 만에서 무얼 하고 있소?";
					link.l1.go = "FishingBoat";
					break;
				}
				else
				{
					dialog.text = "더 이야기하고 싶은 것이 있습니까?";
					link.l1 = "원했어"+GetSexPhrase("","")+" 군도에서 최신 소식을 알아보기 위해.";
					link.l1.go = "rumours_capitan";
					if(CheckAttribute(pchar,"GenQuest.FishingBoatDialogEnb"))
					{
						link.l2 = "다시 한 번 보여줘, 어떤 잡동사니를 팔고 있는지. ";
						link.l2.go = "Торговля";
						if(pchar.GenQuest.FishingBoatDialogEnb != "no special goods")
						{
							link.l3 = "흠, 창고에서 더 찾아보는 게 어때 – 혹시 팔 만한 게 나올지도 모르잖아?";
							link.l3.go = "Особые товары";
						}
					}
					link.l4 = "별일 없어, 그냥 인사하러 왔어!";
					link.l4.go = "exit";	
					break;
				}
			}
			// <-- рыбацкое судно
            if (!CheckAttribute(NPChar, "MainCaptanId")  || NPChar.MainCaptanId == pchar.GenQuest.CaptainId)
            {
                Dialog.text = "당신 말씀을 아주 주의 깊게 듣고 있습니다,  "+GetAddress_Form(NPChar)+".";
                link.l1 = "군도에서 들려오는 최신 소식을 듣고 싶어.";
                //homo 25/06/06
                link.l1.go = "rumours_capitan";
                //belamour legendary edition 
				bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
				bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
				bOk = bOk1 || bOk2;
                if (CheckAttribute(NPChar, "EncGroupName") && !bOk) // только для фантомов грабеж
                {
                    iCapBattleDifficulty = CalcBattleDifficulty();
                    link.l2 = "(위협 성공 확률: " + iCapBattleDifficulty + "%%) " + RandPhraseSimple("너 내가 누군지나 아냐? 내 대포가 네 배를 벌집으로 만들 수 있다는 거 뻔히 알겠지. 평화롭게 끝내자. 몸값이면 충분하니까.", "보이지? 바로 여기, 망망대해 한가운데야... 어때, 우리 녀석들 기분 좀 풀어주라고 작은 성의를 베푸는 건? 네 부하들의 안전을 위해서 말이야.");
                    link.l2.go = "Talk_board";
                }
                if (CheckAttribute(NPChar, "Ship.Mode") && NPChar.Ship.Mode == "Trade")
                {
	           		link.l3 = "어디서 오는 거야?";
	    			link.l3.go = "price_1";
	    			link.l4 = "거래할래?";
	    			link.l4.go = "Trade_1";
    			}
				//--> квест мэра, поиски пирата
				if (CheckAttribute(pchar, "GenQuest.DestroyPirate"))
				{
	    			link.l6 = "이 근해에서 활동하는 해적선을 찾고 있어. 수상한 걸 본 적 있나?";
	    			link.l6.go = "MQ_step_1";
				}
				//<-- квест мэра, поиски пирата
    			link.l5 = "쉬고 싶어?";
			    link.l5.go = "Play_Game";
                link.l9 = "가야겠군.";
    			link.l9.go = "exit";
			}
			else
			{
                Dialog.text = "나는 너와 거래할 권한이 없다. 우리 함대의 지휘관에게 말해라. 그의 이름은  "+GetFullName(characterFromID(NPChar.MainCaptanId))+", 그를 에서 찾을 수 있어 "+XI_ConvertString(RealShips[sti(characters[GetCharacterIndex(NPChar.MainCaptanId)].Ship.Type)].BaseName)+" '"+characters[GetCharacterIndex(NPChar.MainCaptanId)].Ship.Name+"'.";
                link.l1 = "감사합니다. 말씀대로 하겠습니다.";
                link.l1.go = "exit";
                Diag.TempNode = "Go_away_Good";
			}
        break;
        case "Trade_1":
			dialog.text = "왜 안 되지?";
			link.l1 = "물건 좀 보러 가자.";
			link.l1.go = "Trade_2";
			link.l2 = "내 마음이 바뀌었어.";
			link.l2.go = "exit";
		break;
		
		case "Trade_2":
            Partition_GetCargoCostCoeff("after");
			FillShipStore(NPChar);
	    	pchar.shiptrade.character = NPChar.id;
   			Diag.CurrentNode = Diag.TempNode;
		    DialogExit();
		    DeleteAttribute(pchar, "PriceList.StoreManIdx"); // не вести лог по кораблям
		    LaunchStore(SHIP_STORE);
		break;
		
        case "Play_Game":
			dialog.text = "무슨 뜻이오?";
			link.l1 = "진짜 돈 걸고 카드 한 판 할래?";
			link.l1.go = "Card_Game";
   			link.l2 = "포커 조커에서 주사위나 한 번 굴려볼래?";
			link.l2.go = "Dice_Game";
			link.l10 = "미안하지만, 처리해야 할 일이 좀 있어.";
			link.l10.go = "exit";
		break;
        // карты -->
        case "Card_Game":
            if (!CheckNPCQuestDate(npchar, "Card_date_Yet") || isBadReputation(pchar, 30) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(3))
            {
                SetNPCQuestDate(npchar, "Card_date_Yet");
                dialog.text = "나는 사기꾼들이랑 도박 안 해!";
    			link.l1 = "원하시는 대로 하겠습니다.";
    			link.l1.go = "exit";
			}
			else
			{
                dialog.text = "왜 안 되겠어? 나도 잠깐 쉬는 거라면 전혀 상관없지...";
    			link.l1 = "훌륭하군.";
    			link.l1.go = "Cards_begin";
    			link.l2 = "규칙이 뭐지?";
    			link.l2.go = "Cards_Rule";
			}
		break;

		case "Cards_Rule":
   			dialog.text = CARDS_RULE;
			link.l1 = "자, 그럼 시작하자!";
			link.l1.go = "Cards_begin";
			link.l3 = "아니, 나한테 필요한 건 아니야...";
			link.l3.go = "exit";
		break;

		case "Cards_begin":
			Dialog.text = "먼저 내기부터 합의하자.";
			link.l1 = "100페소를 걸고 한 판 하자.";
			link.l1.go = "Cards_Node_100";
			link.l2 = "500페소로 한 판 하자.";
			link.l2.go = "Cards_Node_500";
			link.l3 = "가야겠군.";
			link.l3.go = "exit";
		break;

		case "Cards_Node_100":
		    if (sti(pchar.Money) < 300)
		    {
                dialog.text = "장난하는 거야 뭐야? 돈도 없잖아!";
                link.l1 = "그럴 수도 있지.";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 300)
		    {
                dialog.text = "이제 그만해야겠어, 아니면 배를 유지할 돈이 부족하겠군...";
                link.l1 = "안됐군.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "좋아, 100닢 걸고 한 판 하자.";
			link.l1 = "시작하자!";
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 100;
            pchar.GenQuest.Cards.SitType   = false;
		break;

		case "Cards_Node_500":
		    if (sti(pchar.Money) < 1500)
		    {
                dialog.text = "장난하는 거야 뭐야? 너 1,500페소도 없잖아!";
                link.l1 = "내가 찾아낼 거야!";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 1500)
		    {
                dialog.text = "아니, 이런 내기가 분명 내 최후가 될 거야.";
                link.l1 = "원하시는 대로 하겠습니다.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "좋아, 500닢 걸고 한 판 하자.";
			link.l1 = "시작하자!";
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
	    // карты <--
	    //  Dice -->
        case "Dice_Game":
            if (!CheckNPCQuestDate(npchar, "Dice_date_Yet") || isBadReputation(pchar, 30) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(3))
            {
                SetNPCQuestDate(npchar, "Dice_date_Yet");
                dialog.text = "나는 사기꾼들이랑 도박 안 해!";
    			link.l1 = "원하시는 대로 하겠습니다.";
    			link.l1.go = "exit";
			}
			else
			{
				if (CheckNPCQuestDate(npchar, "Dice_date_begin"))
				{
					dialog.text = "왜 안 되겠어! 쉬는 건 건강에 항상 좋지... 하지만 지갑에는 항상 좋은 건 아니야...";
	    			link.l1 = "훌륭하군.";
	    			link.l1.go = "Dice_begin";
	    			link.l2 = "우리 게임의 규칙이 뭐지?";
	    			link.l2.go = "Dice_Rule";
    			}
    			else
    			{
					dialog.text = "아니, 오늘은 여기까지야. 할 일이 좀 있거든.";
	    			link.l1 = "원하시는 대로 하겠습니다.";
	    			link.l1.go = "exit";
				}
			}
		break;

		case "Dice_Rule":
   			dialog.text = DICE_RULE;
			link.l1 = "자, 그럼 시작하자!";
			link.l1.go = "Dice_begin";
			link.l3 = "아니, 나한테 필요한 건 아니야...";
			link.l3.go = "exit";
		break;

		case "Dice_begin":
			Dialog.text = "먼저 내기부터 합의하자.";
			link.l1 = "50페소로 한 판 하자.";
			link.l1.go = "Dice_Node_100";
			link.l2 = "200페소로 한 판 하자.";
			link.l2.go = "Dice_Node_500";
			link.l3 = "가야겠군.";
			link.l3.go = "exit";
		break;

		case "Dice_Node_100":
			//belamour legendary edition 
			bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
			bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
			bOk = bOk1 || bOk2;
            if (!CheckDiceGameSmallRate() && !bOk)
		    {
                dialog.text = "그대는 ~로 잘 알려져 있소"+GetSexPhrase("사기꾼","사기꾼")+".. 나는 너랑 절대 주사위놀이 안 할 거야.";
                link.l1 = "전부 거짓말이야! 좋아, 그렇게 해.";
			    link.l1.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 300)
		    {
                dialog.text = "장난하는 거야 뭐야? 돈도 없잖아!";
                link.l1 = "그럴 수도 있지.";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 300)
		    {
                dialog.text = "이제 됐다! 도박은 그만둘 거야 - 날 횡령꾼이라고 부르고 배에서 쫓아내기 전에.";
                link.l1 = "안됐군.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "좋아, 50코인으로 한 판 하자.";
			link.l1 = "시작하자!";
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
                dialog.text = "당신은 ~로 잘 알려져 있습니다"+GetSexPhrase("속임수쟁이","사기꾼")+". 나는 너랑 절대 주사위 놀이 안 할 거야.";
                link.l1 = "전부 거짓말이야! 뭐, 그렇다면 어쩔 수 없지.";
			    link.l1.go = "exit";
			    break;
		    }
			if (!CheckDiceGameBigRate())
		    {
                dialog.text = "자네가 꽤 노련한 도박꾼이라 들었어. 나는 자네랑 큰돈 걸고 놀 생각 없어.";
                link.l1 = "내기를 좀 낮춰볼까?";
			    link.l1.go = "Dice_Node_100";
				link.l2 = "미안하지만, 나는 가야 해.";
			    link.l2.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 1500)
		    {
                dialog.text = "장난하는 거야 뭐야? 너 1,500페소도 없잖아!";
                link.l1 = "내가 찾아낼 거야!";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 1500)
		    {
                dialog.text = "아니, 이 내기들 때문에 정말 망하게 생겼군.";
                link.l1 = "원하시는 대로 하겠습니다.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "좋아, 200닢 걸고 한 판 하자.";
			link.l1 = "시작하자!";
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
	    // Dice <--
        case "price_1":
			if (CheckNPCQuestDate(npchar, "trade_date"))
			{
                SetNPCQuestDate(npchar, "trade_date");
				iMoney = findPriceStoreMan(NPChar);
	            if (iMoney == -1)
	            {
	                Dialog.Text = "왜 알고 싶지? 그건 내 사적인 일이야.";
					Link.l1 = "원하시는 대로 하겠습니다.";
					Link.l1.go = "exit";
	            }
	            else
	            {
                    sld = &Characters[iMoney];
                    pchar.PriceList.ShipStoreIdx = iMoney;
                    
					Dialog.Text = "나는 도시 출신이다"+GetCityName(sld.City)+".";
					Link.l1 = "현지 상점에서 물건 값이 얼마인가?";
					Link.l1.go = "price_2";
					Link.l9 = "가야겠다.";
					Link.l9.go = "exit";
				}
			}
			else
			{
                Dialog.Text = "나는 이미 다 말했어. 괜히 귀찮게 하지 마.";
				Link.l1 = "그래, 네 말이 맞아. 잘 가라.";
				Link.l1.go = "exit";
            }
		break;
		
		case "price_2":
            sld = &Characters[sti(pchar.PriceList.ShipStoreIdx)];
			SetPriceListByStoreMan(&Colonies[FindColony(sld.City)]);
			Dialog.Text = "여기 있습니다... (가격표를 받으셨습니다)..";
			Link.l1 = "정말 감사합니다!";
			Link.l1.go = "exit";
			PlaySound("interface\important_item.wav");
		break;
		
        case "Talk_board":
            bOk = iCapBattleDifficulty > hrand(98);
            //if ((Group_GetCharactersNum(NPChar.EncGroupName) - Group_GetDeadCharactersNum(NPChar.EncGroupName)) > GetCompanionQuantity(PChar) && rand(11) > GetCharacterSkillToOld(PChar, SKILL_FORTUNE))
            if(!bOk && iCapBattleDifficulty <= 33)
            {
                Dialog.text = "하하! 좋은 농담이군. 특히 내가 확실히 우위에 있으니 말이지. 네 배로 돌아가서 같이 침몰이나 해라.";
                link.l1 = "...";
                link.l1.go = "Boarding";
            }
            else
            {
                if(!bOk)
                {
                    Dialog.text = "선장, 내 배에서 더러운 짓을 저질렀어서는 안 됐지. 하지만 자비를 베풀어 네 배로 돌아가서 그 배와 함께 수장될 기회를 주겠다.";
                    link.l1 = "오늘 누가 상어 밥이 될지 두고 보자!";
                    link.l1.go = "Boarding";
                }
                else
                {
                    if(iEncPow == -1) iEncPow = 0;
                    Pchar.GenQuest.MoneyForCaptureShip = (70 + hrand(60, "&CapSur"+NPChar.id)) * iEncPow;
					if(HasShipTrait(pchar, "trait14")) Pchar.GenQuest.MoneyForCaptureShip = makeint(sti(Pchar.GenQuest.MoneyForCaptureShip) * 1.35);
                    Dialog.text = RandSwear()+"그래, 네가 저지른 만행에 대해 많이 들었지. 좋다, 하지만 명심해라 "+XI_ConvertString(NationShortName(sti(NPChar.nation))+"사냥꾼")+" 그냥 넘어가지 않겠어!";
                    link.l1 = "훌륭하군. 총액은 "+Pchar.GenQuest.MoneyForCaptureShip+" 페소면 충분해, "+GetAddress_FormToNPC(NPChar)+".";
                    link.l1.go = "Capture";
                    link.l2 = "아, 신경 쓰지 마. 그냥 농담한 거야"+GetSexPhrase("","")+"!";
                    link.l2.go = "exit";
                }
            }
            // тут нужен учёт запрета повторного наезда
            Diag.TempNode = "Go_away";
			sld = characterFromId(pchar.GenQuest.CaptainId);
            sld.talk_date_Go_away =  lastspeakdate(); // boal злопамятность :)
        break;
		
		case "surrender1" :
			Diag.TempNode = "surrender_goaway";
            Dialog.Text = "자, 받아라 - 이제 꺼져!";
			Link.l1 = "좋아! 너도 건강하게 지내라, 친구!";
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
			Dialog.Text = "나한테 또 뭘 원하는 거야?";
			Link.l1 = "아무것도 아니다.";
			Link.l1.go = "exit";
			Diag.TempNode = "surrender_goaway";
		break;
		
		case "surrender2":			
			dialog.text = "당신에게 굴복하는 수밖에 없겠군.";
			link.l1 = "어서 지나가!";
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
			Link.l1 = RandPhraseSimple(RandSwear()+"이거 참 흥미롭군. 또 다른 질문 있나?","그저 또 하나의 일이지.");
			Link.l1.go = "quests";
			Link.l2 = RandPhraseSimple("감사합니다, 이제 가봐야겠군요.","행운을 빌어.");
			Link.l2.go = "exit";
			Diag.TempNode = "quests";
		break;
		
		case "Go_away":
			Dialog.Text = "내 배에서 내려!";
			Link.l1 = "나는 이미 떠나고 있다.";
			Link.l1.go = "exit";
			Diag.TempNode = "Go_away";
		break;
		
		case "Go_away_Good":
			Dialog.Text = "우리 대화는 끝났어. 더 이상 새로 말해줄 건 없어 "+GetAddress_Form(NPChar)+".";
			Link.l1 = "좋아. 바다에서 보자!";
			Link.l1.go = "exit";
			Diag.TempNode = "Go_away_Good";
		break;

        case "Capture":
            Diag.TempNode = "Go_away";
            Dialog.Text = "자, 가져가라 - 이제 나가!";
			Link.l1 = "좋아!";
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
        
        case "QuestAboardCabinDialog":  // тестовый диалог, в игре не работает, для метода SetQuestAboardCabinDialog
			Diag.TempNode = "QuestAboardCabinDialog";
            Dialog.Text = "잠깐만, 이렇게 하면 나 죽을 수도 있어. 나한테 뭘 원하는 거야?";
			Link.l1 = "널 죽이려고!";
			Link.l1.go = "QuestAboardCabinDialog_1";
			Link.l2 = "항복해!";
			Link.l2.go = "QuestAboardCabinDialog_2";
			Link.l3 = "지도 내놔, Billy (c)";  // предмет, далее не ясно или  QuestAboardCabinDialog_1 или QuestAboardCabinDialog_2
			Link.l3.go = "QuestAboardCabinDialog_3";  // можно закодить покидание корабля, но экипаж уже вырезан и тп...
        break;
        
        case "QuestAboardCabinDialog_1":
			Dialog.Text = "그래, 두고 보자, 이 망할 놈아!";
			Link.l1 = "그래서 내가 뭘 봐야 하지?";
			Link.l1.go = "exit";
			// тут можно восстановить НР противника (NPChar) или добавить парочку гардов против ГГ
			LAi_SetCurHPMax(NPChar);
			AddDialogExitQuestFunction("QuestAboardCabinDialogExitWithBattle"); // тут ругань обратно
		break;
		
		case "QuestAboardCabinDialog_2":
			Dialog.Text = "좋아, 네가 이겼어!";
			Link.l1 = "현명한 결정이야!";
			Link.l1.go = "exit";
			AddDialogExitQuestFunction("QuestAboardCabinDialogSurrender");
		break;
		
		case "QuestAboardCabinDialog_3":
			Dialog.Text = "목에 걸려 죽어라!";
			Link.l1 = "아주 좋아, 족쇄 차고 입 다물고 있어라, 죄수.";
			if (rand(1) == 1)  // пример!!!
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
			Dialog.Text = ""+GetSexPhrase("여기에 왔다","여기로 왔다")+", 엉망으로 만들었어"+GetSexPhrase("","")+", 그리고 모든 것을 가져갔어"+GetSexPhrase("","")+", 이제 나를 노예로 만들겠다고? 절대 안 돼!";
			Link.l1 = "그럼 죽을 준비나 해라.";
			Link.l1.go = "QuestAboardCabinDialog_1";
		break;
		//eddy. квест мэра, поиски пирата
		case "MQ_step_1":
			Dialog.Text = "아니, 해적처럼 보이는 수상한 배는 본 적 없어.";
			Link.l1 = "알겠군.";
			Link.l1.go = "exit";
		break;
		
		//homo Наводка на купца
		case "MerchantTrap_Abordage":

			Dialog.Text = "~의 이름으로 "+NationKingsName(NPChar)+" 항복해, "+GetSexPhrase("더러운 해적","더러운 계집년!")+"! 그럼 네 목숨은 공정한 재판이 열릴 때까지는 살려두겠다. 그 자리에서 네 죄를 모두 심판받게 될 것이다 "+NationNameSK(sti(NPChar.nation))+"네가 약탈한 배들"+GetSexPhrase("","")+".";
			Link.l1 = "꺼져라! 항복하는 게 좋을 거다!";
			Link.l1.go = "exit";
			LAi_SetCurHPMax(NPChar);
			AddDialogExitQuestFunction("QuestAboardCabinDialogExitWithBattleNoParam"); // тут ругань обратно
		break;
		
		case "Siegehelp":		
            ref rchar = Group_GetGroupCommander(sGroup);
            if (NPChar.id == rchar.id)
            {
    			if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
				{
					dialog.text = "각하, 총독 나리! 저는 주의 깊게 듣고 있습니다만, 부디 간단히 말씀해 주십시오. 우리는 지금 싸우고 있습니다\n "+fort+", 그리고 나는 전투의 방향을 지휘해야 해.";
				}
				else
				{
					if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && sti(Items[sti(pchar.EquipedPatentId)].Nation) == npchar.nation)
					{
						dialog.text = "부제독님! 저는 주의 깊게 듣고 있지만, 시간이 많지 않습니다. 우리는 지금 싸우고 있습니다: "+fort+", 그리고 나는 전투의 방향을 지휘해야 해.";
					}
					else
					{
						dialog.text = "듣고 있소만, 방문 목적을 빨리 말하시오. 우리는 지금 전쟁 중이오, "+fort+", 그리고 내가 전투의 지휘를 맡아야 해.";
					}
				}
                link.l1 = "그래서 내가 여기 있는 거야,  "+GetAddress_FormToNPC(NPChar)+".";
                link.l1.go = "attack_fort";

                link.l2 = "그렇다면 더 이상 시간을 뺏지 않겠소. 안녕히 가시오, "+GetAddress_FormToNPC(NPChar)+".";
                link.l2.go = "exit";
    			
            }
            else
            {
                Dialog.text = "나는 너와 거래할 권한이 없다. 우리 함대의 지휘관에게 말해라. 그의 이름은  "+GetFullName(rchar)+", 그를 찾으려면 "+XI_ConvertString(RealShips[sti(rchar.Ship.Type)].BaseName)+" ''"+rchar.Ship.Name+"''.";
                link.l1 = "감사합니다. 말씀대로 하겠습니다.";
                link.l1.go = "exit";
            
            }
            Diag.TempNode = "Siegehelp";
            
		break;
		
		case "attack_fort":
                dialog.text = "그게 무슨 뜻이야?";
                link.l1 = "나는 그 식민지의 요새를 무너뜨리는 데 도와줄 수 있소 "+GetCityName(aData.Colony)+" 그리고 도시를 점령하고 전리품도 챙길 거야. 우리가 성공하면 그 전리품은 우리끼리 나눌 거다.";
                link.l1.go = "Siegehelp_1";
                link.l2 = "사실 제 일은 당신의 시간을 들일 가치도 없소. 그럼 이만, "+GetAddress_FormToNPC(NPChar)+".";
                link.l2.go = "exit";
                Diag.TempNode = "Siegehelp_0";
		break;
		
		case "Siegehelp_0":
            Dialog.text = "또 너냐? 우리는 이미 다 얘기한 줄 알았는데.";
            link.l1 = "맞아. 내가 잊고 있었던 것 같군"+GetSexPhrase("","")+".";
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
                dialog.text = "그럼 너는 전리품에서 얼마나 챙길 생각이냐?";
                link.l1 = "반.";
                link.l1.go = "Big_part";
                link.l2 = "삼분의 일.";
                link.l2.go = "Middle_part";
                link.l3 = "4분의 1.";
                link.l3.go = "Small_part";
            }
            else
            {
                dialog.text = "네 서비스는 필요 없어, 선장! 이 식민지는 내가 직접 점령할 거니, 아무런 도움도 필요하지 않아.";
                link.l1 = "왜 그렇게 확신하지, "+GetAddress_FormToNPC(NPChar)+", 누구나 운이 나쁠 때가 있지.";
                link.l1.go = "attack_fort_03";
                link.l2 = "그렇다면 더 이상 시간을 뺏지 않겠습니다, "+GetAddress_FormToNPC(NPChar)+". 잘 가시오!";
                link.l2.go = "exit";
            }
			Diag.TempNode = "Siegehelp_0";

		break;
		
		case "attack_fort_03":
            if((sti(aData.iSquadronPower)*SquadronDamage - (ifortPower)*fortDamage) < 4000)
            {
                dialog.text = "한편으로, 이번 전투에서 내 배들이 꽤 손상됐으니, 증원군이 오면 나쁠 것 없지. 만약 네가 동의한다면\n "+GetPart(4)+"그렇다면, 우리도 합의에 이를 수 있겠군.";
                link.l1 = "그거 마음에 드는군, "+GetAddress_FormToNPC(NPChar)+". 내가 요새를 공격해 볼 테니, 자네는 배의 대포로 우리를 지원하게.";
                link.l1.go = "attack_fort_04";
                aData.PartAttaksFort = 4;
                link.l2 = "나는 그렇게 싸구려가 아니야, "+GetAddress_FormToNPC(NPChar)+". 방해해서 미안하오"+GetSexPhrase("","")+" 바쁜 일에서 그대를 방해하지 않겠소. 안녕히 가시오!";
                link.l2.go = "exit";
            }else{
                dialog.text = "내 전대에는 이 요새를 먼지로 만들어버릴 만큼 충분한 배가 있다네 - 시간 문제일 뿐이지. 이제, 내 배에서 내려주겠나? 승리가 나를 기다리고 있네!";
                link.l1 = "그렇다면, "+GetAddress_FormToNPC(NPChar)+", 이만 물러가겠습니다. 안녕히 계십시오!";
                link.l1.go = "exit";
            }
		    Diag.TempNode = "Siegehelp_0";
		break;
		case "Big_part":
            if( (sti(aData.iSquadronPower)*SquadronDamage - (ifortPower)*fortDamage) <= -1500)
            {
                dialog.text = "요새 대포 때문에 내 배들이 심하게 손상됐고, 다가오는 전투에서 우리가 질 수도 있겠군. 네 도움을 받아들이고, 네 조건에 동의하겠다.";
                link.l1 = "훌륭하군, "+GetAddress_FormToNPC(NPChar)+", 그렇다면 우리가 요새를 공격할 테니, 당신은 배의 대포로 우리를 지원해 주시오.";
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
					dialog.text = "각하, 작전 진행 상황에 대해 아직 보고드릴 일이 있습니다... 적어도 제게 맡겨 주십시오\n "+GetPart(4)+".";
				}
				else
				{
                dialog.text = "너무 심한 거 아니오, 선장님? 당신은 "+GetNumShips(GetCompanionQuantity(PChar))+", 그리고 내 함대는 "+GetNumShips(Group_GetCharactersNum(sGroup))+". 내가 줄 수 있는 것은 "+GetPart(4)+". 그리고 그게 공정하다고 생각하시오.";
				}
                aData.PartAttaksFort = 4;
                link.l1 = "동의해"+GetSexPhrase("","")+", "+GetAddress_FormToNPC(NPChar)+"그렇다면 내가 요새를 공격할 테니, 자네는 배의 대포로 우리를 지원하게.";
                link.l1.go = "attack_fort_04";
                link.l2 = "유감이지만, 아닌 것 같소, "+GetAddress_FormToNPC(NPChar)+". 더 이상 할 말이 없소. 안녕히 가시오.";
                link.l2.go = "exit";
            }
            Diag.TempNode = "Siegehelp_0";
        break;
        
        case "attack_fort_04":
            dialog.text = "요새를 점령하자마자 상륙조를 해안에 투입할 것이고, 그 다음에는 마을 안에서 계속 전투를 이어갈 거요. 그곳에서 그대를 만나길 바라오.";
            link.l1 = "그러면 그렇게 하지. 곧 보자, "+GetAddress_FormToNPC(NPChar)+"!";
            link.l1.go = "exit";
            Diag.TempNode = "Siegehelp_0";
            PChar.quest.Union_with_Escadra = "Yes";
        break;

        case "Middle_part":
            if((sti(aData.iSquadronPower)*SquadronDamage - (ifortPower)*fortDamage) <= -600)
            {
                dialog.text = "네 조건에 동의할 생각이오. 함께 작전을 펼치면 이 싸움에서 이길 확률이 높아지겠지.\n모든 일이 계획대로 진행된다면, 전리품에서 몫을 받게 될 것이오.";
                link.l1 = "합의에 도달해서 다행이군, "+GetAddress_FormToNPC(NPChar)+". 즉시 내 부하들에게 요새를 공격하라고 명령하겠다.";
                link.l1.go = "attack_fort_04";
                aData.PartAttaksFort = 3;
            }else{
				// belamour legendary edition
				bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation);
				bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE;
				bOk = bOk1 || bOk2;
				if(bOk)
				{
					dialog.text = "각하, 아직 작전 진행 상황을 보고드려야 합니다... 적어도 제가 "+GetPart(4)+".";
				}
				else
				{
                dialog.text = "너무 심한 거 아니오, 선장님? 당신은 "+GetNumShips(GetCompanionQuantity(PChar))+", 그리고 내 함대는 "+GetNumShips(Group_GetCharactersNum(sGroup))+". 내가 줄 수 있는 것은 "+GetPart(4)+". 그리고 그게 공정하다고 생각해.";
				}
                link.l1 = "I "+GetSexPhrase("동의한다","동의한다")+", "+GetAddress_FormToNPC(NPChar)+", 그렇다면 내가 요새를 공격할 테니, 자네는 자네 배의 대포로 우리를 지원하게.";
                link.l1.go = "attack_fort_04";
                aData.PartAttaksFort = 4;
                link.l2 = "유감이지만, 그렇지 않은 것 같소. "+GetAddress_FormToNPC(NPChar)+"더 이상 할 말이 없소. 안녕히 가시오.";
                link.l2.go = "exit";
            }
            Diag.TempNode = "Siegehelp_0";
        break;

        case "Small_part":
            dialog.text = "내 배들은 지쳐 있고, 이런 상황에서는 새로운 지원이 반갑지. 네 도움을 받아들이고, 네 조건에도 동의하겠네.";
            link.l1 = "기쁘구나"+GetSexPhrase("","")+", "+GetAddress_FormToNPC(NPChar)+".. 곧바로 내 부하들에게 요새 공격을 시작하라고 명령하겠소.";
            link.l1.go = "attack_fort_04";
            aData.PartAttaksFort = 4;
            Diag.TempNode = "Siegehelp_0";
        break;
		
		case "Talk_Capture_City":
            AfterTownBattle();  // все, все свободны
            LAi_LoginInCaptureTown(NPChar, false);
            aData.win = 1;
            EndOfTheSiege("End");
            NPChar.location = "";
            int ilt = makeint(sti(aData.loot)/sti(aData.PartAttaksFort));
            dialog.text = "안녕하세요, 선장님! 정말 힘든 전투였지만, 우리는 마침내 마을 수비대의 거센 저항을 뚫었습니다. 우리는 약탈에 성공했습니다\n "+sti(aData.loot)+" 페소입니다. 우리 약속대로, 당신 몫은 "+ilt+". 이 돈을 받아 주십시오. 당신은 한 푼도 빠짐없이 받을 자격이 있습니다. 이제 실례하겠습니다. 제 일로 돌아가야 하거든요.";
            link.l1 = "그렇다면, 나는 그만 가보겠소, "+GetAddress_FormToNPC(NPChar)+". 잘 가라!";
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
            //--> слухи
            SiegeRumour("I've been told that you had helped our squadron in the assault of the "+NationNameSK(sti(aData.conation))+" colony - "+GetCityName(aData.Colony)+"! We're so thankfull to you, "+ GetAddress_Form(NPChar)+".", "", sti(aData.nation), -1, 30, 3);
            //<-- слухи
		break;

        case "no_return_02":
            dialog.text = "이봐, 선장! 나한테 볼일 있나?";
            link.l1 = "아니, "+GetAddress_FormToNPC(NPChar)+". 안녕히 가십시오!";
            link.l1.go = "exit";
            Diag.TempNode = "no_return_02";
		break;
		
		case "GoldSquadron":
            ref rch = Group_GetGroupCommander("Sea_Head_of_Gold_Squadron");
            if (NPChar.id == rch.id)
            {
    			dialog.text = "당신 말을 듣고 있소. 하지만 방문 목적을 빨리 말하시오, 시간이 많지 않으니. 나는 중요한 비밀 임무 중이며, 우리 호송대에 위협이 될 수 있는 수상한 배는 공해상에서 침몰시키라는 명령을 받았소.";                          
                link.l1 = "그렇다면 더 이상 시간을 뺏지 않겠소. 행운을 빕니다, "+GetAddress_FormToNPC(NPChar)+".";
                link.l1.go = "exit";

            }
            else
            {
                Dialog.text = "나는 너와 거래할 권한이 없다. 우리 함대의 지휘관에게 말해라. 그의 이름은 "+GetFullName(rch)+", 그를 찾으려면 "+XI_ConvertString(RealShips[sti(rch.Ship.Type)].BaseName)+" ''"+rch.Ship.Name+"''.";
                link.l1 = "고마워. 네 말대로 할게.";
                link.l1.go = "exit";

            }
            Diag.TempNode = "GoldSquadron";
		break;
		
		case "WM_Captain":
			dialog.text = "만나서 반갑소, 내 이름은 "+GetFullName(npchar)+". 그래서 우리를 도우러 온 건가? 그렇다면 정말 다행이네, 지금 상황이 아주 위급하거든. 우리는 무인도 해안에 홀로 남았고, 배는 간신히 떠 있을 뿐이며, 선원들도 큰 피해를 입었어...";
			link.l1 = "내가 들은 바로는, 자네가 해적들과 싸웠고, 그다음엔 그 폭풍이 있었다지...";
			link.l1.go = "WM_Captain_1";
			pchar.quest.DesIsland_Over.over = "yes";//снять прерывание
		break;
		
		case "WM_Captain_1":
			dialog.text = "맞아요. 내 배는 전투에서 심하게 손상됐어 - 그 해적 놈들이 이끄는 백병전까지 맞서 싸워야 했지. 나중엔 폭풍우까지 덮쳐서... 아, 생각하기도 싫군. 우리는 이 척박한 해안까지 떠밀려 왔어. 하루 종일 복되신 성모님께 폭풍에서 구해 달라고, 닻 사슬이 끊어지지 않게 해 달라고 기도했지\n그래서 이렇게 살아남았어. 일주일째 배를 수리하고 있지만, 직접 봐. 남은 인원은 겨우 쉰 명이고, 목재도 부족해 - 그걸 어디서 구해야 하지? 정글에서? 당연하지. 매일 죽어라 일해도 필요한 자재의 5분의 1밖에 못 모았어\n이런 상태로 항해하는 건 자살이나 다름없어. 이제 우리가 여기서 어떤 상황인지 알겠지, 선장...";
			link.l1 = "그래... 네 처지가 참 딱하구나. 우리가 뭘 할 수 있을지, 내가 어떻게 도와줄 수 있을지 한번 생각해보자.";
			link.l1.go = "WM_Captain_2";
		break;
		
		case "WM_Captain_2":
			dialog.text = "에이, 넉넉한 판자랑 돛천만 있었으면 우리 배를 일주일 안에 고칠 수 있었을 텐데\n선장님, 일부러 여기까지 오신 김에 가까운 항구에 들러 우리가 필요한 자재를 사다 주실 수 있겠습니까? 그러면 문제가 해결될 겁니다. 돈 걱정은 마십시오, 모든 비용은 제가 보상하겠습니다.";
			link.l1 = "물론이지. 정확히 무엇을 얼마나 배달해야 하지?";
			link.l1.go = "WM_Captain_3";
		break;
		
		case "WM_Captain_3":
			pchar.questTemp.WPU.Escort.Planks = 300 + hrand(5)*10;
			pchar.questTemp.WPU.Escort.Sailcloth = 150 + hrand(10)*10;
			pchar.questTemp.WPU.Escort.Linen = 70 + hrand(7)*10;
			dialog.text = "나는 이미 이 모든 걸 파악했어. 우리가 이미 가진 걸 고려하면, 나는 필요해 "+FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Planks))+" 널빤지, "+FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Sailcloth))+" 돛천과\n "+FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Linen))+" 면화지. 이 재료만 있으면 일주일 안에 배를 수리할 수 있고, 그다음엔 출항할 수 있겠어.";
			link.l1 = "좋아. 네가 필요한 모든 재료를 가져오겠다. 기다리고 있어라 - 열흘 안에 돌아올 테니.";
			link.l1.go = "WM_Captain_4";
		break;
		
		case "WM_Captain_4":
			dialog.text = "정말 감사합니다, 선장님! 이제 마음이 한결 놓입니다. 무사히 돌아오시길 기다리며 기도하겠습니다!";
			link.l1 = "걱정하지 마. 곧 수리에 필요한 모든 걸 갖게 될 거야.";
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
			dialog.text = "돌아오시기를 손꼽아 기다리겠습니다, 선장님!";
			link.l1 = "닻 올려라!";
			link.l1.go = "exit";
			Diag.TempNode = "WM_Captain_again";
		break;
		
		case "WM_Captain_5":
			dialog.text = "훌륭해! 이제 배를 수리하기 시작할 수 있겠군!";
			link.l1 = "내 부하들이 도와줄 거야 - 이렇게 하면 더 빨리 끝나지. 게다가, 내가 너를 식민지까지 직접 데려가야 하거든. "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity)+", 그러니 수리가 빨리 끝날수록 내게 더 좋지.";
			link.l1.go = "WM_Captain_6";
		break;
		
		case "WM_Captain_6":
			pchar.questTemp.WPU.Current.TargetIslandID.Shore = SelectQuestShoreLocationFromSea(pchar.questTemp.WPU.Current.TargetIslandID);
			dialog.text = "정말로, 어떻게 감사드려야 할지 모르겠습니다, 선장님... 자재를 라고 불리는 만에 하역하라고 명령해 주십시오\n "+XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID.Shore)+" - 거기에는 수리를 위한 모든 준비가 되어 있어.";
			link.l1 = "좋아. 해변에서 만나자.";
			link.l1.go = "exit";
			AddQuestRecord("Escort", "29");
			AddQuestUserData("Escort", "sShore", XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID.Shore+"Gen"));
			pchar.quest.DisasterShip_WMC.win_condition.l1 = "location";
			pchar.quest.DisasterShip_WMC.win_condition.l1.location = pchar.questTemp.WPU.Current.TargetIslandID.Shore;
			pchar.quest.DisasterShip_WMC.function = "RepairShip_Prepare";
			Diag.TempNode = "WM_Captain_repeat";
		break;
		
		case "WM_Captain_repeat":
			dialog.text = "언제 수리를 시작할 건가요, 선장님? 저는 해안에서 기다리고 있겠습니다.";
			link.l1 = "네, 물론입니다. 지금 떠나겠습니다.";
			link.l1.go = "exit";
			Diag.TempNode = "WM_Captain_repeat";
		break;
		
		case "Repair_start":
			dialog.text = "음, 수리 준비는 모두 끝난 것 같아. 한 다섯 날쯤이면 끝날 것 같군.";
			link.l1 = "아주 좋아! 어차피 이 섬을 탐험하려고 했으니, 시간을 잘 활용하겠어.";
			link.l1.go = "Repair_start_1";
		break;
		
		case "Repair_start_1":
			DialogExit();
			pchar.quest.WM_Captain_Over.over = "yes";//снять прерывание
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
			dialog.text = "자, 이제 끝났어. 수리는 다 마쳤고, 배도 출항 준비가 됐어. 언제 떠나실 건가요, 선장님?";
			link.l1 = "준비됐으면, 더 이상 지체할 이유가 없지. 닻 올려라!";
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
			log_info("You have 25 days to escort "+pchar.questTemp.WPU.Escort.ShipBaseName+" '"+pchar.questTemp.WPU.Escort.ShipName+"' to the port of "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen")+"");
			pchar.quest.DisasterShip_final.win_condition.l1 = "location";
			pchar.quest.DisasterShip_final.win_condition.l1.location = pchar.questTemp.WPU.Escort.StartCity +"_town";
			pchar.quest.DisasterShip_final.function = "WMShip_final";
		break;
		
		case "WMShip_final":
			pchar.quest.Escort_fail.over = "yes";
			pchar.quest.DisasterShipWM_Over.over = "yes";//снимаем оба прерывания
			RemoveCharacterCompanion(Pchar, characterFromID("WMCaptain"));//удаляем компаньона
			pchar.questTemp.WPU.Escort.LevelUp_1Money = sti(pchar.questTemp.WPU.Escort.Planks)*15+sti(pchar.questTemp.WPU.Escort.Sailcloth)*9+sti(pchar.questTemp.WPU.Escort.Linen)*45;//деньги за материалы
			dialog.text = "다시 한 번 감사드리고 싶습니다, 선장님 - 당신 덕분에 저와 제 선원들이 그 곤경에서 벗어날 수 있었습니다. 약속드린 대로, 제 배를 수리하는 데 필요한 자재에 대해 보상해 드리겠습니다. 여기 있습니다\n "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.LevelUp_1Money))+", 부디 가져가시오. 그리고 이것은 내 개인적인 선물이오.";
			link.l1 = "도와드릴 수 있어서 기뻤습니다.";
			link.l1.go = "WMShip_final_1";
		break;
		
		case "WMShip_final_1":
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Escort.LevelUp_1Money));
			TakeNItems(pchar, "obereg_"+(hrand(10)+1), 1);
			dialog.text = "이제 작별 인사를 할 시간이오, 선장. 항만청에 꼭 들르시오 - 거기서 기다리고 있소. 또 보시오!";
			link.l1 = "좋은 하루 보내시오, "+npchar.name+"!";
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
			dialog.text = "그런가? 이제야 우리를 잊은 줄 알았는데. 그래, 내 배가 가장 큰 피해를 입었지. 폭풍 때문에 해적들이 우리 호송대를 공격하다 포기하고, 우리는 자연과 맞서 싸워야 했네. 결국 이렇게 척박한 해안까지 밀려왔지\n며칠 동안 수리도 하고 쉬기도 했어. 그런데 이 이교도들이 우리가 막 출항하려던 참에 또다시 습격했지\n그리고 또다시 폭풍이 몰아쳤어—이제야 주님께서 우리를 끝장내려 하시는 줄 알았는데, 바로 그때 자네가 나타났지. 성모 마리아께 감사드리네! 다시 한 번 고맙네, 선장!";
			link.l1 = "모든 게 끝났어, "+GetAddress_FormToNPC(NPChar)+". 이제 당신을 호위해서 데려가야겠군 "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen")+", 더 이상의 문제를 막기 위해서지. 이제 출발할 준비가 되었나? 폭풍은 이미 잦아들기 시작했네.";
			link.l1.go = "VSP_Captain_1";
		break;
		
		case "VSP_Captain_1":
			dialog.text = "물론이지! 우리가 이곳을 빨리 떠날수록 내 부하들도 더 안심할 거야 – 이미 너무 많은 고생을 했거든. 출항하자!";
			link.l1 = "내 배만 따라오면 돼. 그리고 선원들 진정시켜, 이제 두려울 건 없어.";
			link.l1.go = "VSP_Captain_2";
		break;
		
		case "VSP_Captain_2":
			pchar.quest.DisasterShip_GetOut.over = "yes";
			DialogExit();
			Group_DelCharacter("WMShip", "WMCaptain");//иначе будет клон
			sld = characterFromId("WMCaptain");
			LAi_SetImmortal(sld, false);
			SetCharacterRemovable(sld, false);
			sld.CompanionEnemyEnable = false; //всегда друзья
			SetCompanionIndex(pchar, -1, sti(sld.index));
			sld.loyality = MAX_LOYALITY;
			AddQuestRecord("Escort", "36");
			AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
			SetFunctionTimerCondition("DisasterShipWM_Over", 0, 0, 25, false);
			log_info("You have 25 days to escort "+pchar.questTemp.WPU.Escort.ShipBaseName+" '"+pchar.questTemp.WPU.Escort.ShipName+"' to the port of"+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen")+"");
			pchar.questTemp.WPU.Escort = "win";
			pchar.quest.Escort_fail.win_condition.l1 = "NPC_Death";//прерывание на потопление сопровождаемого
			pchar.quest.Escort_fail.win_condition.l1.character = "WMCaptain";
			pchar.quest.Escort_fail.function = "DisasterShipWM_failed";
			pchar.quest.DisasterShip_final.win_condition.l1 = "location";
			pchar.quest.DisasterShip_final.win_condition.l1.location = pchar.questTemp.WPU.Escort.StartCity +"_town";
			pchar.quest.DisasterShip_final.function = "WMShip_final";
			Diag.currentnode = "VSP_Captain_again";
			Delete_EscortStorm();//уберем шторм
		break;
		
		case "VSP_Captain_again":
			dialog.text = "출항할까요, 선장님?";
			link.l1 = "알겠소. 이제 내 배로 돌아가겠소.";
			link.l1.go = "exit";
			Diag.TempNode = "VSP_Captain_again";
		break;
		
		case "VSPShip_final":
			pchar.quest.Escort_fail.over = "yes";
			pchar.quest.DisasterShipWM_Over.over = "yes";//снимаем оба прерывания
			RemoveCharacterCompanion(Pchar, characterFromID("WMCaptain"));//удаляем компаньона
			pchar.questTemp.WPU.Escort.LevelUp_1Money = 10000+sti(pchar.rank)*200;
			dialog.text = "다시 한 번 감사드리고 싶소, 선장님 – 당신 덕분에 나와 내 선원들이 이 곤경에서 벗어날 수 있었소. 여기 있소\n"+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.LevelUp_1Money))+". 선원 전원이 힘을 모았으니, 거절할 생각은 하지 마시오. 그리고 이건 내 개인적인 선물이오.";
			link.l1 = "도와드릴 수 있어서 기뻤습니다!";
			link.l1.go = "WMShip_final_1";
		break;
		
		case "SShip_final":
			pchar.questTemp.WPU.Escort.LevelUp_1Money = 5000+sti(pchar.rank)*100;
			RemovePassenger(Pchar, npchar);//удаляем пассажира
			dialog.text = "다시 한 번 감사드리고 싶소, 선장님, 이 난관에서 우리를 구해주셔서. 자, 이 동전을 받아주시오 - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.LevelUp_1Money))+"  그리고 여기, 이 선물을 받아주시오. 많지는 않지만, 당신이 해준 일에 감사하는 내 마음을 전할 수 있는 건 이것뿐이오. 제발, 이 제안을 거절하지 마시오\n내 예전 선원들은 당신과 인디언, 해적들과의 전투에 모두 감탄하고 있소. 그들 모두가 당신과 함께하고 싶어 하오. 방금 배를 잃은 충직한 선원들의 충성을 받아주지 않겠소?";
			link.l1 = "당연히 아니지. 기꺼이 보관할게. 도와줄 수 있어서 기뻤어!";
			link.l1.go = "WMShip_final_1";
		break;
		
		//Голландский Гамбит
		case "Stivesant_1":
			DelLandQuestMark(npchar);
			dialog.text = "좋소. 하지만, 나리, 여기서 무슨 일이 벌어지고 있는지 설명해 주시겠소? 어떻게 해서 당신이 '메이펑'을 지휘하게 되었소! 롱웨이에게 무슨 일이 있었던 것이오?";
			link.l1 = "필요한 설명은 모두 가지고 있어. 그리고 다른 중요한 정보도 있지.";
			link.l1.go = "Stivesant_2";			
		break;
		
		case "Stivesant_2":
			dialog.text = "그럼, 잘 듣고 있겠소.";
			link.l1 = "빌렘스타트에서 쿠데타가 일어났어. 루카스 로덴부르흐가 총독 자리를 차지했고, 마티아스 벡을 영국 정보국과 연관이 있다는 터무니없는 의심으로 감옥에 가뒀어.";
			link.l1.go = "Stivesant_3";			
		break;
		
		case "Stivesant_3":
			dialog.text = "흠... 마인헤르, 당신이 말하는 것은 정말 놀랍군요. 얼마 전에 빌렘스타트에서 소식을 받았는데, 그런 이야기는 전혀 없었습니다.";
			link.l1 = "제 말을 들어주십시오, Stuyvesant 나리. Rodenburg를 통해 소식을 받으셨을 테고, 그가 분명 당신이 Curaçao에 도착하지 못할 거라고 확신하고 있을 겁니다.";
			link.l1.go = "Stivesant_4";			
		break;
		
		case "Stivesant_4":
			dialog.text = "이봐, 네 말이 점점 마음에 안 들어. 도대체 넌 누구야?";
			link.l1 = "나는 그저 선장일 뿐이고, 네덜란드 식민지 주민들의 운명에 무관심하지 않은 평범한 인간일 뿐이오. 루카스 로덴부르크가 롱웨이에게 당신의 배를 파괴하고 당신까지 죽이라고 명령했소. 그리고 '메이펑'이 당신의 의심을 사지 않을 거라 생각했기에, 그는 아무런 어려움 없이 그 일을 해냈을 것이오.";
			link.l1.go = "Stivesant_5";			
		break;
		
		case "Stivesant_5":
			dialog.text = "그러니까, 네 말은 루카스가...";
			link.l1 = "가장 쉬운 방법으로 너를 권좌에서 끌어내리기로 했지, 그냥 없애버리는 거야. 너 말고는 이 지역에서 로덴부르크가 군도에 미치는 영향력에 제대로 맞설 수 있는 사람이 없어.";
			link.l1.go = "Stivesant_6";			
		break;
		
		case "Stivesant_6":
			dialog.text = "믿을 수가 없군!";
			link.l1 = "나는 베크가 영국 정보부와 연관되어 있다는 헛소리에 속지 않고 직접 조사를 했지. 내가 알아낸 바로는, 선별된 악당들로 가득 찬 '메이펑'이 필립스버그로 떠났더군. 나는 그들을 쫓아가서 전투를 벌였어. 롱웨이를 생포했고, 그가 네 행방을 포함한 이 모든 정보를 내게 털어놨지.";
			link.l1.go = "Stivesant_7";			
		break;
		
		case "Stivesant_7":
			dialog.text = "흠... 그럴 듯하군. 내 일정과 항로를 아는 사람은 로덴부르크 말고는 아무도 없었어, 알 수도 없었지! 젠장! 이건 반역이야! 롱웨이는 어디 있지?!";
			link.l1 = "나는 그의 자백을 자발적으로 받는 조건으로 그를 풀어주었네. 솔직히 말해서, 그는 로덴부르크의 명령을 그리 내키지 않게 수행했지만, 그렇다고 무시할 수도 없었지. 그리고 그는 다시는 로덴부르크의 밑에서 일하지 않겠다고 했네\n이번 마지막 더러운 일로 완전히 질려버렸다고 하더군.";
			link.l1.go = "Stivesant_8";			
		break;
		
		case "Stivesant_8":
			dialog.text = "좋아... 선장 "+GetFullName(pchar)+", 너는 나와 함께 윌렘스타드로 간다. 내 배보다 먼저 '메이펑'을 타고 항해하게 될 거야. 네 말이 사실이라면 루카스를 반드시 체포해야 하고, 너도 그 일에 협조해야 해. 하지만 나에게 거짓말을 했다면... 그땐 네 잘못이니 원망하지 마라.";
			link.l1 = "나리, 당신께 거짓말할 이유가 내겐 없소. 서두르지!";
			link.l1.go = "Stivesant_9";			
		break;
		
		case "Stivesant_9":
			DialogExit();
			Diag.CurrentNode = "Stivesant_10";
			AddQuestRecord("Holl_Gambit", "3-52");
			pchar.questTemp.HWIC.Self = "WayWithStivesant";
			Group_DelCharacter("Stivesant_Halleon", "Stivesant");
			SetCharacterRemovable(npchar, false);
			npchar.CompanionEnemyEnable = false; //всегда друзья
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
			dialog.text = "선장님, 'Meifeng'으로 가십시오. 이제 출항할 시간입니다.";
			link.l1 = "예, 나리, 물론입니다.";
			link.l1.go = "exit";
			Diag.TempNode = "Stivesant_10";
		break;
		
		case "Keller_1":
			dialog.text = "매우 흥미롭군! 자, 네 이야기를 들려줘. 내가 도울 수 있는 데까지 최선을 다할게.";
			link.l1 = "켈러 나리, 몇 달 전 빌렘스타트로 가는 길에 플루트선을 만난 일 기억하시오? 그 배에는 유대인 난민 가족이 타고 있었지. 그 배에서 식사를 하고는 여정을 계속했었소.";
			link.l1.go = "Keller_2";
		break;
		
		case "Keller_2":
			dialog.text = "그래, 그런 것 같군... 그래, 이제는 아주 또렷이 기억나. 그래서, 무슨 일이야?";
			link.l1 = "그 플루트선은 바로 그날 해적들에게 침몰당했소. 겨우 두 명의 난민만 살아남았는데, 솔로몬과 그의 딸 아비게일이었지. 그들은 공격이 일어난 곳에서 몇 마일 떨어진 섬에서 피신처를 찾았소. 나는 그 섬을 찾아야 하오. 혹시 그 플루트선을 어디서 보았는지 기억해낼 수 있겠소? 이건 매우 중요한 일이오.";
			link.l1.go = "Keller_3";
		break;
		
		case "Keller_3":
			dialog.text = "그게 다 필요한 거야? 나는 이 섬을 알아. 아주 가까워, 트리니다드와 퀴라소 사이에 있지. 작고, 버려진, 사람이 살지 않는 섬이야. 인디언조차 없어.";
			link.l1 = "그리고 그 대략적인 좌표를 알고 있소?";
			link.l1.go = "Keller_4";
		break;
		
		case "Keller_4":
			dialog.text = "정확한 좌표를 알려줄 수 있소. 북위 12도 48분, 서경 64도 41분이오. 그곳을 찾아보시오. 섬은 꽤 작지만 쉽게 찾을 수 있을 것이오.";
			link.l1 = "감사합니다, Keller 나리! 큰 도움을 주셨소. 안녕히 계시오.";
			link.l1.go = "Keller_5";
		break;
		
		case "Keller_5":
			DialogExit();
			Diag.CurrentNode = "Keller_6";
			pchar.quest.Keller_fail.over = "yes";
			pchar.questTemp.HWIC_Coordinates = "true"; //атрибут координат на поиск острова через каюту
			DeleteAttribute(pchar, "questTemp.HWICMC");
			AddQuestRecord("Holl_Gambit", "3-66");
		break;
		
		case "Keller_6":
			dialog.text = "다른 용무라도 있으십니까, 선장님?";
			link.l1 = "아니요, 괜찮습니다. 이제 막 제 배로 돌아가려던 참이었습니다.";
			link.l1.go = "exit";
			Diag.TempNode = "Keller_6";
		break;
		
		// belamour рыбацкое судно -->
		case "FishingBoat":
			pchar.GenQuest.FishingBoatSecondTime = true;
			dialog.text = "별거 없어, 여긴 그냥 어선이야. 여기서 물고기 잡고 살지. 어떻게든 먹고살아야 하잖아.";
			link.l1 = "그래, 나도 동의해, 이런 시대지...";
			link.l1.go = "FishingBoat_1";			
		break;
		
		case "FishingBoat_1":
			Diag.TempNode = "FishingBoat_1";
			dialog.text = "그래서 뭘 원하는 거야?";
			link.l1 = "원했다"+GetSexPhrase("","")+" 군도에서 최신 소식을 알아보기 위해.";
            link.l1.go = "rumours_capitan";
			link.l2 = "오늘은 어획이 어때? 팔 수 있나? 식량 좀 있으면 좋겠는데...";
			link.l2.go = "FishingBoat_2";
			link.l3 = "별일 없어, 그냥 인사하러 왔어!";
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
				
				dialog.text = "오늘은 어획이 좋네, 그물만 걷어들이면 돼. 당신에게 팔 수도 있지, 가게보다 더 싸게 말이야 – 어차피 우리는 이 고기를 동네 상인한테 넘기거든. 이걸 전부 식량으로 바꾼다면... 지금 우리가 가진 건 "+iTemp+" 그걸로, 우리는 가격을 받고 팔 수 있어 "+iMoney+" 한 개에 페소입니다. 얼마나 가져가시겠소?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитого провианта";
				link.l2 = "있잖아, 네 식량을 사려던 마음이 바뀌었어.";	
				link.l2.go = "exit";
				
			}
			if(GetDataDay() > 10 && GetDataDay() < 21) 
			{
				Diag.TempNode = "FishingBoat_1";
				dialog.text = "그래, 뭐랄까, 솔직히 말해서 물고기가 전혀 없어... 오늘은 거의 아무것도 못 잡았지. 그래도 작살은 남아 있어. 혹시 운이 좋으면 큰 물고기나 고래라도 잡을까 해서 말이야... 혹시 작살이 필요해?";
				link.l1 = "아니, 작살에는 관심 없어.";
				link.l1.go = "exit";
				link.l2 = "흠, 작살도 제대로 쓰면 쓸모가 있지. 아마 사야겠군.";
				link.l2.go = "Гарпуны";
			}
			if(GetDataDay() > 20)
			{
				dialog.text = "그래, 뭐랄까, 솔직히 말해서 오늘은 물고기가 하나도 없어... 오늘은 거의 아무것도 못 잡았지. 그래서 팔 것도 별로 없어. 그나마... 자질구레한 물건 몇 개 있는데, 혹시 관심 있을지 몰라. 한번 구경해 볼래?";
				link.l1 = "아니, 나는 장신구 따위엔 관심 없어.";
				link.l1.go = "exit";
				link.l2 = "잡은 게 없다니 아쉽군. 뭐, 적어도 네 장신구나 한번 보자꾸나 - 어쩌면 내 눈에 드는 게 있을지도 모르지 ...";
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
				dialog.text = "너무 비싸... 그만한 돈 없어! 좀 덜 살 수 있나?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитого провианта повтор";	
				link.l2 = "있잖아, 네가 가진 식량을 사려던 마음이 바뀌었어.";	
				link.l2.go = "exit";
			}	
			if(iQty < 1)
			{
				dialog.text = "농담하는 거야? 식량이 필요해, 안 필요해? 필요하다면, 얼마나?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитого провианта повтор";	
				link.l2 = "있잖아, 네 식량을 사려던 마음이 바뀌었어.";	
				link.l2.go = "exit";
			}
			if(iQty > 0 && iQty <= iTemp)
			{
				dialog.text = "거래 성사! "+sti(iQty*iMoney)+" 페소입니다.";
				if(sti(pchar.money) < iQty*iMoney)
				{
					link.l1 = "흠, 그 정도 돈은 없어. 다음에 하자.";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = "거래하자! 물건을 내 배로 가져와.";
					link.l1.go = "Удачная покупка";
					link.l2 = "있잖아, 네 식량을 사려던 마음이 바뀌었어.";
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
				dialog.text = "너무 많아... 그만한 돈 없어! 좀 덜 살 수 있겠어?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитого провианта";	
				link.l2 = "있잖아, 네 식량을 사려던 마음이 바뀌었어.";	
				link.l2.go = "exit";
			}	
			if(iQty < 1)
			{
				dialog.text = "장난하는 거야? 식량이 필요한 거야, 아닌 거야? 필요하면, 얼마나 필요한데?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитого провианта";	
				link.l2 = "있잖아, 네 식량을 사려던 마음이 바뀌었어.";	
				link.l2.go = "exit";
			}
			if(iQty > 0 && iQty <= iTemp)
			{
				dialog.text = "거래지! "+sti(iQty*iMoney)+" 페소입니다.";
				if(sti(pchar.money) < iQty*iMoney)
				{
					link.l1 = "흠, 나한텐 그만한 돈이 없어. 다음에 하지.";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = "거래 성사다! 내 배에 물건을 실어라.";
					link.l1.go = "Удачная покупка";
					link.l2 = "있잖아, 네 식량을 사려던 마음이 바뀌었어.";
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
				dialog.text = "우리에겐 "+iTemp+" 조각들이요. 작살 하나당 백 페소에 팔 수 있습니다. 몇 개나 필요하십니까?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитых гарпунов";
				link.l2 = "있잖아, 생각이 바뀌었어. 작살은 필요 없어.";	
				link.l2.go = "exit";
		break;
		
		case "Количество вбитых гарпунов":
   
			iQty = sti(dialogEditStrings[3]);
			iTemp = makeint(pchar.GenQuest.FishingBoatITemp);
			pchar.GenQuest.FishingBoatIQty = iQty;
			Diag.TempNode = "FishingBoat_1";
			if(iQty > iTemp)
			{
				dialog.text = "그건 너무 비싸... 나한텐 그만한 돈이 없어! 좀 덜 살 수 없겠어?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитых гарпунов заново";	
				link.l2 = "있지, 마음이 바뀌었어. 작살은 필요 없어.";	
				link.l2.go = "exit";
			}	
			if(iQty < 1)
			{
				dialog.text = "농담하는 거야? 작살이 필요해, 안 해? 필요하면 몇 개나 필요한데?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитых гарпунов заново";	
				link.l2 = "있잖아, 생각이 바뀌었어. 작살은 필요 없어.";	
				link.l2.go = "exit";
			}
			if(iQty > 0 && iQty <= iTemp)
			{
				dialog.text = "거래 성사! "+sti(iQty*100)+" 페소입니다.";
				if(sti(pchar.money) < iQty*100)
				{
					link.l1 = "흠, 나한텐 그만한 돈이 없어. 다음에 하자.";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = "좋아! 내가 쓸 데를 찾아보지.";
					link.l1.go = "Удачная покупка гарпунов";
					link.l2 = "있잖아, 생각이 바뀌었어. 작살은 필요 없어.";
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
				dialog.text = "너무 많아요... 그 정도 돈은 없어요! 좀 덜 살 수 없나요?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитых гарпунов";	
				link.l2 = "있잖아, 마음이 바뀌었어. 작살은 필요 없어.";	
				link.l2.go = "exit";
			}	
			if(iQty < 1)
			{
				dialog.text = "장난하는 거야? 작살이 필요해, 안 해? 필요하면 몇 개나 필요한데?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитых гарпунов";	
				link.l2 = "있잖아, 마음이 바뀌었어. 작살은 필요 없어.";	
				link.l2.go = "exit";
			}
			if(iQty > 0 && iQty <= iTemp)
			{
				dialog.text = "거래 성사! "+sti(iQty*100)+" 페소입니다.";
				if(sti(pchar.money) < iQty*100)
				{
					link.l1 = "흠, 나한텐 그 정도 돈이 없어. 다음에 하자.";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = "거래지! 내가 쓸 데를 찾아보지.";
					link.l1.go = "Удачная покупка гарпунов";
					link.l2 = "있잖아, 생각이 바뀌었어. 작살은 필요 없어.";
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
				dialog.text = "아니, 더는 없어. 그냥 어선이야! 여기 뭐가 더 있겠어?";
				link.l1 = "알겠어, 이해했어.";
				link.l1.go = "exit";
			}
			else if(hrand(2, "&SpeGoo") == 1)
			{
				if(ChangeContrabandRelation(pchar, 0) > 5)
				{
					
					dialog.text = "음... 여기 작은 물건이 하나 있지... 내가 보관하고 있었는데, 누군가에게 팔까 했어. 하지만 값비싸게 받을 거야! 그리고 두 번 다시 제안하지 않을 거다. 볼 건가?";
					link.l1 = "보여 줘, 어떤 꼬마 녀석인지 한번 보자.";
					link.l1.go = "Особые товары предметы";
				}
				else
				{
					Diag.TempNode = "First time";
					Diag.CurrentNode = "First time";
					pchar.GenQuest.FishingBoatDialogEnb = "no special goods";
					dialog.text = "아니, 더 이상 없어. 그냥 어선이야! 여기 뭐가 더 있겠어?";
					link.l1 = "알겠어. ";
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
						sTemp = "units of backout";
					}
					if(GetDataDay() > 7 && GetDataDay() < 15)
					{
						iMoney = GetStoreGoodsPrice(&Stores[PortSpein_STORE], GOOD_OIL, PRICE_TYPE_BUY, pchar, 1);
						iTemp = GOOD_OIL;
						sTemp = "barrels of ship tar"; 
					}
					if(GetDataDay() > 14 && GetDataDay() < 22) 
					{
						iMoney = GetStoreGoodsPrice(&Stores[BasTer_STORE], GOOD_ROPES, PRICE_TYPE_BUY, pchar, 1);
						iTemp = GOOD_ROPES;
						sTemp = "bays of ship ropes"; 
					}
					if(GetDataDay() > 21) 
					{
						iMoney = GetStoreGoodsPrice(&Stores[Villemstad_STORE], GOOD_SHIPSILK, PRICE_TYPE_BUY, pchar, 1);
						iTemp = GOOD_SHIPSILK;
						sTemp = "rolls of ship silk";
					}
					iQty = 20 + sti(rand(6)*5);
					pchar.GenQuest.FishingBoatITemp = iTemp;
					pchar.GenQuest.FishingBoatIMoney = iMoney;
					pchar.GenQuest.FishingBoatIQty = iQty;
					
					dialog.text = "음... 제가 여기 물건이 하나 있는데... 해변에서 우연히 발견한 거예요. 이것은 "+iQty+" "+sTemp+"입니다. 개당 가격은 "+iMoney+"입니다. 하지만 전부 한 번에만 팔 거고, 두 번은 제안하지 않을 거예요. 그리고 이 일을 다른 사람들이 알지 못하도록 해야 해요... 제 말 이해하시죠?";
					link.l1 = "아니, 수상한 물건은 필요 없어, 고마워. 아무한테도 말하지 않을 테니 걱정 마.";
					link.l1.go = "exit";
					if(sti(pchar.money) >= iMoney*iQty)
					{
						link.l2 = "이해하네. 하지만 그 물건은 그만한 가치가 있지. 내가 가져가겠네. 그를 내 배로 데려오게.";
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
				dialog.text = "그거야 "+GetItemName(sTemp)+". 손에 넣었지... 어디서인지는 묻지 마. 원래는 알아주는 감식가한테 팔려고 했어. 10,000페소에 넘길 테니, 살래?";
				if(sti(pchar.money) > 9999)
				{
					link.l1 = "당연히 내가 가져가지! 물건이 그대로 있잖아. ";
					link.l1.go = "Купили особый товар";
				}
				link.l2 = "아니, 필요 없어. 안 받을 거야. ";
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
		// <-- рыбацкое судно
	}
}

string GetNumShips(int ship)
{
    string numships;
    switch(ship)
    {
       case 0: numships = "no ships"; break;
       case 1: numships = "one ship";      break;
       case 2: numships = "two ships";       break;
       case 3: numships = "three ships";       break;
       case 4: numships = "four ships";    break;
       case 5: numships = "five ships";     break;
       case 6: numships = "six ships";    break;
    }
    return numships;
}

string GetPart(int part)
{
    string numpart;
    switch(part)
    {
       case 0: numpart = ""; break;
       case 1: numpart = "all loot"; break;
       case 2: numpart = "half of the loot"; break;
       case 3: numpart = "third of the loot"; break;
       case 4: numpart = "quarter of the loot";      break;
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
		if (CheckAttribute(ch, "Dialog.Filename") && ch.Dialog.Filename == "Common_Store.c") // магазин
		{
            //if (sti(ch.nation) !=  sti(NPChar.nation)) continue;
            if (ch.location == "none") continue; // фикс для новых, невидимых до поры островов
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

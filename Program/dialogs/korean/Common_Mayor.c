// boal 25/04/04 общий диалог мэры
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref aData;
	aref Link, NextDiag, arName;

	DeleteAttribute(&Dialog,"Links");

	ref FortChref; // фортовый командер
	ref arItem;
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Mayor\" + NPChar.City + "_Mayor.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
    ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06

    FortChref = GetFortCommander(NPChar.City); // будет или фортовик или сам губернатор

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
	// генератор ИДХ по кейсу -->
	attrLoc   = Dialog.CurrentNode;
  	if (findsubstr(attrLoc, "GetPrisonerIdx_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	pchar.GenQuest.GetPrisonerIdx = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "sell_prisoner_2";
 	}
 	// генератор ИДХ по кейсу <--
 	
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

			LAi_LockFightMode(Pchar, true); // ножками путь убегает
		    LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		    LAi_group_Attack(NPChar, Pchar); // не работает на бессмертного мера :(
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // фантом солдат
			if (i != -1)
			{
			    LAi_group_Attack(&Characters[i], Pchar);
			}
		break;
		
		case "First time":
            NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("내 집에 감히 얼굴을 들이밀다니?! 대단히 용감하군, 아니면 어리석거나...","어떻게 내 멍청한 경비병들이 적이 궁전에 침입하도록 놔뒀단 말이냐? 이 일로 누군가의 목이 날아갈 것이다.","분명 내 경비병들은 구리 한 푼 값어치도 없군, 어떤 악당이 내 관저를 돌아다니며 내 물건을 뒤지고 있으니..."),LinkRandPhrase("무엇이 필요하오, "+GetSexPhrase("악당","악마")+"?! 내 병사들이 이미 자네를 쫓고 있네"+GetSexPhrase(", 더러운 해적놈","")+"!",+"살인자, 당장 내 저택에서 나가라! 경비병들!","나는 너 따위 안 두렵다, "+GetSexPhrase("놈","쥐")+"! 곧 우리 요새에서 교수형을 당하게 될 거다!"));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("당신의 병사들은 쓸모없소.","날 잡아보시지."),RandPhraseSimple("입 다물어, "+GetWorkTypeOfMan(npchar,"")+", 아니면 내가 대신 닫아 주겠소!","조용히 해, 이봐. 그러면 목숨은 건질 거야."));
				link.l1.go = "fight";
				break;
			} 
			if (sti(NPChar.nation) == PIRATE)
            {
				if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar, "GenQuest.CaptainComission.PiratesCity") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
				{
					dialog.text = "무엇을 원하시오?";
					link.l1 = "중요한 일로 당신과 이야기하고 싶었습니다.";
					link.l1.go = "quests";
					break;
				}
				if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin" && NPChar.city == "LeFransua")
				{
					dialog.text = "무엇이 필요하오?";
					link.l1 = "중요한 일에 대해 당신과 이야기하고 싶었습니다.";
					link.l1.go = "quests";
					break;
				}
					dialog.text = "더 이상 논의할 일 없소, 이봐. 나는 바쁘니라.";
					link.l1 = "죄송하오.";
					link.l1.go = "Exit";
            }
			if (sti(NPChar.nation) != PIRATE && ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", 0) > 10)
            {
				iTotalTemp = ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", 0);
                dialog.text = "오, 저기 누가 있나! 바로"+GetSexPhrase("","")+" "+GetFullName(pchar)+". 있소, 사실 얼마 전에 자네를 잡아오라고 해적 사냥꾼들을 보냈었지. 자네가 이렇게 내 방에 느긋하게 들어올 줄 알았다면, 돈을 아꼈을 텐데.";
                if (sti(pchar.Money) >= iTotalTemp*6000)
                {
                    link.l1 = "막 우리 계산을 정산하려던 참이었소.";
				    link.l1.go = "arestFree_1";
                }
				link.l2 = "이제 나는 서둘러 떠나야겠군.";
				link.l2.go = "arest_1";
				break;
            }
			if (false)
			{
    			dialog.text = "침입이다! 경비병들! 경보를 울려라! 살인이다!";
				link.l1 = "젠장!";
				link.l1.go = "fight"; 
				break;
			}
			//--> Jason, Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Citcount") && npchar.city == "FortFrance")
			{
    			dialog.text = "무엇을 원하시오, 나리?";
				link.l1 = "안녕하십니까, 각하. 저는 샤를 드 모르라고 하며, 파리에서 막 도착했습니다. 미셸 드 몽페르를 찾고 있습니다.";
                link.l1.go = "Sharlie";
				npchar.quest.meeting = "1"; // patch-6
				DelLandQuestMark(characterFromId("FortFrance_Mayor"));
				break;
			}
			
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock") && npchar.city == "FortFrance")
			{
				if (CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
				{
					dialog.text = "오, 당신이었군요, 나리... 무례를 범해 사과드립니다. 죄송합니다, 이곳 식민지에서는 파리의 예절과는 거리가 멉니다.";
					link.l1 = "물론이옵니다, 각하.";
					link.l1.go = "Sharlie_2";
				}
				else
				{
					dialog.text = "무슨 일로 오셨습니까, Charles?";
					link.l1 = "질문이 있소...";
					link.l1.go = "quests";
					link.l2 = "아니, 아무것도 없소.";
					link.l2.go = "exit";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew"))
				{
					link.l3 = "나리, 정글에서 산적의 시신을 발견했습니다. 인디언들에게 살해당한 것 같습니다. 그의 시신에서 귀걸이가 나왔는데, 유럽에서 가져온 것처럼 보입니다. 혹시 이 귀걸이가 이 마을의 귀족 중 한 사람의 것일까요?";
					link.l3.go = "Sharlie_junglejew";
				}
				npchar.quest.meeting = "1"; // patch-6
				break;
			}			
			//<-- Бремя гасконца
			//--> Sinistra, Травля крысы
			if (CheckAttribute(pchar, "questTemp.TK_TravlyaKrys") && npchar.city == "FortFrance")
			{
    			dialog.text = "카리브에 오신 것을 환영하오, de Maure 선장. 이번에는 진짜요.";
				link.l1 = "감사합니다, 각하.";
                link.l1.go = "TK_TravlyaKrys";
				DelLandQuestMark(npchar);
				break;
			}
			// Jason НСО
			// belamour legendary edition фикс проверки мундира с мушкетом
			if (CheckAttribute(pchar, "questTemp.Patria.Governor") && npchar.city == "Marigo" && IsUniformEquip())
			{
    			dialog.text = "나리, 뵙게 되어 반갑습니다! 안녕하십니까? 신트마르턴에서는 모든 것이 잘 통제되고 있습니다.";
				link.l1 = "나는 머물 시간이 없어. 계속 수고해.";
				link.l1.go = "exit";
				link.l2 = "일에 대해 이야기하고 싶소.";
				link.l2.go = "quests";   //(перессылка в файл города)
				link.l8 = "도박 한 판 어떻소?";
				link.l8.go = "Play_Game";
				break;
			}
			// belamour legendary edition фикс проверки мундира с мушкетом
			if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE && IsUniformEquip())
			{
    			dialog.text = "맙소사, 다시 뵙게 되어 반갑습니다, 총독 나리! 우리 작은 식민지는 모든 것이 아주 훌륭합니다! 부디 앉으시지요, 하인들에게 상을 차리라고 하겠습니다...";
				link.l1 = "그럴 필요 없소. 오래 머무를 생각은 아니오. 계속 수고하시오.";
				link.l1.go = "exit"; 
				link.l2 = "일에 관해 이야기하고 싶소.";
				link.l2.go = "quests";   //(перессылка в файл города)
				link.l8 = "도박 한 판 어때?";
				link.l8.go = "Play_Game";
				break;
			}
			// belamour legendary edition фикс проверки мундира с мушкетом
			if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor") &&  IsUniformEquip())
			{
    			dialog.text = "여기 누가 오셨나! 프랑스 식민지의 총독 나리 아니신가! 어쩐 일로 이곳에 오셨습니까, 각하? 앉으시지요, 하인들에게 포도주와 신선한 과일을 가져오라 하겠소.";
				link.l1 = "걱정 마시오, 나는 그냥 이 섬에 들렀다가 인사라도 드리고 가야 할 것 같아서 온 것이오.";
				link.l1.go = "exit"; 
				link.l2 = "일에 대해 이야기하고 싶소.";
				link.l2.go = "quests";   //(перессылка в файл города)
				link.l8 = "도박 한 판 어때?";
				link.l8.go = "Play_Game";
				break;
			}		
			//--> Jason, Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "MartiniqueGovernor" && npchar.city == "FortFrance")
			{
    			dialog.text = "아, 거기 있었군요, 선장님! 정말 오래 걸리셨소.";
				link.l1 = "가장 이른 기회에 도착했습니다, 각하. 급한 일이 있으시다고 들었는데요?";
				link.l1.go = "Portugal"; 
				break;
			}			
			//<-- Португалец
            
            if (npchar.quest.meeting == "0")
			{
				dialog.text = "내 부하들이 자네가 면담을 매우 끈질기게 요청했다고 하더군. 내 이름은 "+GetFullName(npchar)+". 나는 이 도시의 총독이오 "+GetCityName(NPChar.city)+", 신하인 "+NationKingsName(npchar)+". 이제, 말씀해 보시지요. 무엇을 원하십니까\n "+GetAddress_Form(NPChar)+"?";
				link.l1 = "내 이름은 "+GetFullName(pchar)+".";
				link.l1.go = "node_1";
				npchar.quest.meeting = "1";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_townhall")
				{
					dialog.text = TimeGreeting()+", MacArthur 아가씨.";
					link.l1 = TimeGreeting()+", 각하.";
					link.l1.go = "Helen_node_1"
				}
			}
			else
			{
               	//ОСАДЫ homo
				if (CheckAttribute(&Colonies[FindColony(npchar.City)],"Siege"))
                {

                    makearef(aData, NullCharacter.Siege);
                    
                    if (CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                    {
                        dialog.text = "그게 전부요?";
                        link.l1 = "예, 나리. 더 이상 지체하지 않겠습니다.";
                        link.l1.go = "exit";

                    }
                    else
                    {
                        dialog.text = "불쾌하게 해서 미안하오만, 지금은 당신과 이야기할 시간이 없소. 알다시피, 우리 식민지가 공격을 받았소\n "+NationNamePeople(sti(aData.nation))+". 아직 우리 방어를 점검하고 있소.";
                        link.l1 = "요새 방어에 제 도움이 되고 싶소.";
                        link.l1.go = "siege_task";
                        link.l2 = "그럼 더 이상 지체하지 않겠소.";
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
                        //--> слухи
                        SiegeRumour("They say that you had helped us to repel the "+NationNameSK(sti(aData.nation))+" squadron and to defend our colony! We are grateful to you, "+ GetAddress_Form(NPChar)+".", aData.Colony, sti(aData.conation), -1, 15, 3);
			            //<-- слухи
                        DeleteAttribute(aData, "PlayerHelpMayor");
                        DeleteAttribute(aData, "HelpColony");
                        dialog.text = "오, 그대였군, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+", 다시 만나 반갑소. 우리 식민지에 좋은 소식이 있소 – 우리가 막아냈소 "+NationNameSK(sti(aData.nation))+" 침입자들이다. 너도 이 일에 한몫했으니, 여기 보상이다 - "+(sti(aData.iSquadronPower)*1500)+" 에잇 피스. 여기 있다.";
                        link.l1 = "감사합니다, "+GetAddress_FormToNPC(NPChar)+", 당신과 거래하게 되어 기쁩니다!";
                        link.l1.go = "exit";
                    }
                    else
                    {
   						//--> дача квеста найти кольцо в борделе
						if (rand(4) == 4 && pchar.questTemp.different == "free" && GetNpcQuestPastDayWOInit(npchar, "questTakeRing") > 365 && sti(pchar.questTemp.HorseQty) > 10)
						{// Addon-2016 Jason
							if (npchar.city == "Bridgetown" || npchar.city == "Charles" || npchar.city == "FortFrance" || npchar.city == "Marigo" || npchar.city == "Panama" || npchar.city == "PortRoyal" || npchar.city == "SantoDomingo" || npchar.city == "Tortuga")
							{
        						dialog.text = "그대에게 맡길 일이 있소, 하지만 다소 특이한 일이오.";
								link.l1 = "그런 일이라면 내가 제일 잘하지.";
        						link.l1.go = "TakeRing_1";
								SaveCurrentNpcQuestDateParam(npchar, "questTakeRing");
								break;
							}
						}
						//<-- дача квеста найти кольцо в борделе    				
						dialog.text = RandPhraseSimple("오, 또 너냐? 이번엔 나한테 뭘 원하는 거지?","그대는 내 도시의 일에서 나를 방해하고 있소. 무슨 일로 왔소, "+GetAddress_Form(NPChar)+"?");
						if (npchar.city != "Panama") // Addon-2016 Jason
						{
							link.l1 = "당신에게 일거리를 제안하고 싶소 "+NationNameGenitive(sti(NPChar.nation))+".";
							link.l1.go = "work";
						}
						// Warship Генер "Пираты на необитайке" - сдаём пиратов властям
						if(CheckAttribute(PChar, "Quest.PiratesOnUninhabited_OnShore") || CheckAttribute(PChar, "Quest.PiratesOnUninhabited_ShipSink"))
						{
							link.l11 = XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore+"Gen")+" 해적 몇 놈을 찾았소. 전부 "+PChar.GenQuest.PiratesOnUninhabited.PiratesCount+" 지금 배에 타 있습니다. 그들을 당국에 넘기고 싶습니다.";
							link.l11.go = "PiratesOnUninhabited_1";
						}
						
        				link.l2 = "중요한 이야기를 나누고 싶었습니다.";
						if(CheckAttribute(pchar,"questTemp.ReasonToFast") && !CheckAttribute(pchar,"questTemp.ReasonToFast.SpeakOther") && !CheckAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther") && (pchar.questTemp.ReasonToFast.city == NPChar.city))
						{
							link.l2.go = "ReasonToFast_Mayor1";
						}
						else
						{
							link.l2.go = "quests";   //(перессылка в файл города)
						}	
						if(CheckAttribute(pchar,"GenQuest.CaptainComission") && (pchar.GenQuest.CaptainComission.variant == "A2") && (pchar.GenQuest.CaptainComission.City == NPChar.city))
						{
							if(pchar.GenQuest.CaptainComission == "Begin_1" && !CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor")) 
							{
								link.l12 = "순찰대를 지휘하는 선장이 있다 "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" 이름이 붙은 "+pchar.GenQuest.CaptainComission.Name+", 내가 그를 어떻게 볼 수 있소?";
								link.l12.go = "CapComission_Mayor1";
							}	
							if(CheckAttribute(pchar,"GenQuest.CaptainComission.PrisonFree"))
							{
								link.l12 = "순찰대를 지휘하던 전직 선장 "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+" 그가 자신의 은닉처를 당국에 밝히기로 동의했다.";
								link.l12.go = "CapComission_Mayor9";
							}
							if(pchar.GenQuest.CaptainComission == "GetGoodsSuccess")
							{
								link.l12 = "순찰대를 지휘했던 전임 선장 "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+" 나에게 그의 은닉처를 드러냈소.";
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
									link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore+"Dat"))+" 나는 선장을 만났어 "+pchar.GenQuest.ShipWreck.Name+" 그리고 해적들에게 상륙당한 그의 선원들 "+pchar.GenQuest.ShipWreck.BadName+". "+"안타깝게도, 내 배에는 이미 사람이 너무 많아서 그들을 태울 수 없었소. 하지만 식량과 무기는 남겨두었지. 만약 구조선이 정해진 기간 내에 그들을 데려가지 않는다면\n "+(30 - iDay)+" 며칠이 지나면, 내가 그들을 살아서 찾을 수 있을지 없을지 모르겠소.";
									link.l13.go = "ShipWreck1";
								}
								else
								{
									link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore+"Gen"))+" 난 난파된 배에서 온 선원들을 만났어 '"+pchar.GenQuest.ShipWreck.ShipTypeName+"' 그들의 선장과 함께. "+"안타깝게도, 내 배에는 이미 사람이 너무 많아서 그들을 태울 수 없었소. 하지만 식량과 무기는 남겨두었지. 만약 구조선이 일정 기간 내에 그들을 데려가지 않는다면\n "+(30 - iDay)+" 며칠이 지나면, 내가 그들을 살아서 찾을 수 있을지 모르겠소.";
									link.l13.go = "ShipWreck1";							
								}
							}	
						}
        				if (GetPrisonerQty() > 0)
        				{
                            link.l3 = "포로를 인도하고 싶소.";
        				    link.l3.go = "sell_prisoner";
        				}
        				if (npchar.Default  == npchar.location) // если не в тюрьме
        				{
        					if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
        					{
        						link.l4 = "당신과 몇 가지 금전적인 문제를 정리해야 하오.";
        						link.l4.go = "LoanForAll";//(перессылка в кредитный генератор)
        					}
        				}
						//-->> сдача найденного в борделе кольца
						if (CheckCharacterItem(pchar, "MayorsRing"))
						{
							if (pchar.questTemp.different.TakeMayorsRing == "toBrothel")
							{
        						link.l5 = "당신의 반지를 찾아냈습니다. 여기 있습니다.";
        						link.l5.go = "TakeRing_S1";
							}
							else
							{
        						link.l5 = "당신의 결혼반지를 가지고 있소. 사창가의... 일하는 여자 중 한 명이 가지고 있었소.";
        						link.l5.go = "TakeRing_S3";
							}
						}
						//<<-- сдача найденного в борделе кольца 
						
						//--> Jason, генер почтового курьера 2 уровня
						if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
						{
							if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
							{
							link.l14 = "나는 마을에서 온 전갈을 가져왔소 "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
							link.l14.go = "Postcureer_LevelUp_ForAll";
							}
						}
						//<-- генер почтового курьера 2 уровня
						
						// Warship, 16.05.11. Квест "Правосудие на продажу" -->
						if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_townhall")
						{
							link.l15 = UpperFirst(GetAddress_FormToNPC(NPChar))+", 나는 최근 경비병들에게 붙잡힌 두목이 있는 밀수꾼 무리를 발견했소. 지금 그들은 그의 탈출을 꾸미고 있소. 그들의 배 '"+PChar.GenQuest.JusticeOnSale.ShipName+"'이(가) 정박해 있다 "+XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId+"Dat")+".";
							link.l15.go = "JusticeOnSale_1";
						}
						
						if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.ShipSink") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_townhall")
						{
							link.l15 = UpperFirst(GetAddress_FormToNPC(NPChar))+", 밀수꾼 무리는 이제 끝났소!";
							link.l15.go = "JusticeOnSale_7";
						}
						// <--Правосудие на продажу
						//Jason --> Регата
						if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
						{
							link.l16 = "저는 레가타 때문에 왔습니다. 여기 제 초대장이 있습니다.";
							link.l16.go = "Regata";
						}
        				//link.l7 = "…의 총독이 어디에 있는지 알고 싶소 "+NationNameGenitive(sti(NPChar.nation))+"입니다.";
        				link.l8 = "혹시 잠시 쉬면서 도박 한 판 하시겠소?";
        			    link.l8.go = "Play_Game";
        				link.l10 = "실례하오, 하지만 의무가 나를 부르오.";
        				link.l10.go = "exit";
                    }
                }//<-
			}
		break;
		
		// Warship Генер "Пираты на необитайке"
		case "PiratesOnUninhabited_1":
			offref = CharacterFromID("PirateOnUninhabited_0");
			qty = makeint(sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) * (sti(offref.rank) * (800 + GetCharacterSPECIALSimple(NPChar, SPECIAL_L) * 100) + GetCharacterSkillToOld(offref, "Leadership") * 500 + GetCharacterSkillToOld(PChar, "commerce") * 500) / 20);
			
			PChar.GenQuest.PiratesOnUninhabited.MoneyForPirates = qty;
			
			dialog.text = "아주 좋소. 우리는 힘을 합쳐 이 공통의 재앙에 맞서 싸워야 하오. 즉시 배를 보내 그들을 데려오게 하겠소. 일주일도 안 되어 교수대에 매달릴 테니 안심하시오. 아, 그리고 보상도 당연히 주어야겠지 - "+FindRussianMoneyString(qty)+".";
			link.l1 = "감사합니다, 각하. 언제나 영광입니다. ";
			link.l1.go = "PiratesOnUninhabited_2";
			link.l2 = "아니. 다시 생각해 보니, 그건 안 되겠군.";
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
				Map_ReleaseQuestEncounter("PiratesOnUninhabited_BadPirate"); // Убираем с глобалки
			}
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
		break;
		
		// ------------------------- Повод для спешки -----------------------------
		case "ReasonToFast_Mayor1":
			dialog.text = "듣고 있소, 선장.";
			link.l1 = "귀하의 주둔지 장교 중 한 명과 해적들 사이에 범죄적 공모가 있다는 사실을 말씀드리고 싶었습니다... (자초지종을 설명한다).";
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
				// вилка_А
				dialog.text = "감사합니다, "+GetSexPhrase("나리","아가씨")+"! 내가 즉시 그 반역자를 체포하라고 명령하겠소.\n자네도 돈을 많이 썼겠구려, 허나 우리 국고는 텅 비었소...";
				link.l1 = "돈 때문에 그런 것이 아니옵니다, 각하.";
				link.l1.go = "ReasonToFast_GMayor_11";				
				if(pchar.questTemp.ReasonToFast.chain == "A0") ReasonToFast_RemoveVictim();
				if(pchar.questTemp.ReasonToFast.chain == "A1") pchar.quest.ReasonToFast_ClearLakey.over = "yes";
			}			
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_2") 
			{ 
				// получена карта
				dialog.text = "감사하오! 그 악당을 곧 체포하게 하겠소.\n생각해 보시오! 나는 그자가 10년 근속을 기념해 금장 검을 수여할 참이었소! 자네 덕분에 큰 망신을 면했구려!";
				link.l2 = "정의는 그 자체로 보상이다.";
				link.l2.go = "ReasonToFast_GMayor_21";			
			}
			if(pchar.questTemp.ReasonToFast == "PatrolDied") 
			{ 
				// патруль перебит
				dialog.text = "Mis"+GetSexPhrase("터","s")+" 드 모르, 증인도 없이 용의자를 죽여버리면 안 되오! 이제는 그의 죄를 입증할 증거조차 구할 수 없게 되었소! 내가 그대가 과실치사로 체포되지 않게 막는 것만으로도 벅차오.";
				link.l3 = "정당방위였사옵니다, 각하.";
				link.l3.go = "ReasonToFast_GMayor_31";
				pchar.questTemp.ReasonToFast.speakAfterPatrolDied = true;	
				pchar.quest.ReasonToFast_SpeakMayor.over = "yes";
			}			
		break;
		
		case "ReasonToFast_BMayor":
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_1") 
			{ 				
				dialog.text = "선장, 자네 지금 무슨 짓을 저질렀는지 알고 있나?!! 내가 한 달 넘게 이 함정을 준비했는데! 그런데 자네 재미 좀 보자고 우리 순찰대와의 만남을 망쳐버렸군\n "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_GEN)+" 이제 와서 그걸 자랑하러 온 것이오?!! 그렇다면 이제 나에게 말해보시오, 이 작전의 모든 비용과 지출을 내가 어떻게 설명해야 하겠소?";
				link.l1 = "각하, 방금 전하의 문제를 해결했소. 가만히 생각해 보면, 애초에 내게 계속 보수를 주셨어야 했던 것 아니오!";
				link.l1.go = "ReasonToFast_BMayor_1";
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";				
				if(pchar.questTemp.ReasonToFast.chain == "A0") ReasonToFast_RemoveVictim();
				if(pchar.questTemp.ReasonToFast.chain == "A1") pchar.quest.ReasonToFast_ClearLakey.over = "yes";
			}
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_2") 
			{ 
				// получена карта
				dialog.text = "이 지도를 좀 보자\n지금 진심이오? 이 누더기 종잇조각이 증거란 말이오?";
				link.l2 = "이제 그만하시고, 각하, 이성적으로 생각하십시오.";
				link.l2.go = "ReasonToFast_BMayor_1";
				TakeItemFromCharacter(pchar, "mapQuest");				
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_B";
			}
			if(pchar.questTemp.ReasonToFast == "PatrolDied") 
			{ 
				// патруль перебит
				dialog.text = "음, 이제 내 순찰대에 무슨 일이 있었는지 알겠군. 적어도 네가 여기 온 덕분에 우리가 살인자를 찾으러 다닐 수고는 덜었소.";
				link.l3 = "각하! 분명히 요점을 보려 하지 않으시는군요...";
				link.l3.go = "ReasonToFast_BMayor_1";			
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";
				pchar.quest.ReasonToFast_SpeakMayor.over = "yes";
			}		
		break;
		
		case "ReasonToFast_GMayor_11":
			dialog.text = "넌 바보일지 몰라도 적어도 쓸모 있는 바보로군. 자, 이 지도를 가져가라; 지난주에 교수형에 처한 해적에게서 찾은 거다. 신의 뜻이라면 그놈의 보물을 네가 찾을지도 모르지, 물론 그럴 가능성은 별로 없다고 보지만...\n";
			link.l1 = "감사합니다, 정말 후하시군요!";
			link.l1.go = "exit";
			AddQuestRecord("ReasonToFast", "15");
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			GiveItem2Character(pchar, "mapQuest"); 
			arItem = ItemsFromID("mapQuest");
			ReasonToFast_GenerateTreasureMap(arItem);
			pchar.questTemp.ReasonToFast.state = "chain_A"; // вилка_А, наводки не генерим
			pchar.questTemp.ReasonToFast = "GetMap";			
			ReasonToFast_SetHunterCoastal();
		break;
		
		case "ReasonToFast_GMayor_21":
			dialog.text = "그대의 열정은 칭찬할 만하오. 이 검을 보상으로 받아주시오. 내가 할 수 있는 최소한의 일일 뿐이오. 아, 그리고 지도는 그대가 가져도 되오. 카리브에는 그런 가짜가 널렸을 것이 확실하니.";
			link.l1 = "감사합니다, 정말 후하시군요!";
			link.l1.go = "exit";
			AddQuestRecord("ReasonToFast", "14");
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			GiveItem2Character(pchar, pchar.questTemp.ReasonToFast.p6);
			pchar.questTemp.ReasonToFast.state = "chain_B"; // была получена карта
			pchar.questTemp.ReasonToFast = "GetMap";			
			ReasonToFast_SetHunterCoastal();
		break;
		case "ReasonToFast_GMayor_31":
			dialog.text = "아마도, 아마도... 뭐, 이 거래는 신의 정의와 우리 주님의 뜻에 따라 결정된 것이라 하겠소.";
			link.l1 = "감사합니다, 정말 후하시군요!";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			AddQuestRecord("ReasonToFast", "16");
			CloseQuestHeader("ReasonToFast");
			DeleteAttribute(pchar,"ReasonToFast");
		break;
		
		case "ReasonToFast_BMayor_1":
			dialog.text = "입 다물어라, 이 녀석! 네가 미쳤거나 우리 적들과 한패로군! 경비병들, 이 바보를 잡아라!";
			link.l1 = "나한테 손대면 그 손 잃게 될 거야!";
			link.l1.go = "fight";
		
			pchar.quest.ReasonToFast_ExitFromTown.win_condition.l1			= "EnterToSea";           	
            pchar.quest.ReasonToFast_ExitFromTown.function    				= "ReasonToFast_ExitFromTownFight";						
			pchar.questTemp.ReasonToFast.canSpeakSailor = true;
			pchar.TownEscape = true;
			Flag_PIRATE();
		break;
		
		// ------------------------- Повод для спешки -----------------------------
		
		// --------------------------Операция 'Галеон'-----------------------------
		case "CapComission_Mayor1":
			dialog.text = "지금은 불가능하오. 그는 체포되어 재판을 기다리고 있소.";
			link.l1 = "그런가? 그리고 그는 무슨 혐의를 받고 있지?";			
			link.l1.go = "CapComission_Mayor2";
		break;
		
		case "CapComission_Mayor2":
			dialog.text = "유감스럽게도, 이는 의심이 아니라 이미 입증된 사실이오. 우리는 그가 순찰을 가장해 선박을 습격했다는 정보를 입수했소. 그는 상인들의 물품을 압수한 뒤 밀수업자와 해적들에게 팔았소. 안타깝구려... 한때 그가 왕실 최고의 선장 중 한 명으로 여겨졌다는 것이...";
			link.l1 = "누가 그 증거를 주었소?";
			link.l1.go = "CapComission_Mayor3";				
		break;
		
		case "CapComission_Mayor3":
			dialog.text = "그의 희생자 중 한 명이 보고서를 작성했는데, 그 안에는 사건의 날짜, 습격당한 선박의 이름, 압수된 물품의 양 등 사건이 자세히 기록되어 있소. "+"저를 믿으십시오, 숫자가 꽤 인상적입니다. 그날 순찰에서\n "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")))+" 선장 "+pchar.GenQuest.CaptainComission.Name+" 확실히 근무 중이었습니다. 선장은 이 사건을 보고서에 해적선과의 조우로 기록했으나, 화물에 대해서는 전혀 언급하지 않았습니다.";
			link.l1 = "하지만 화물이 조금이라도 있었소?";
			link.l1.go = "CapComission_Mayor4";
			pchar.GenQuest.CaptainComission.SpeakMayor = true;
		break;
		
		case "CapComission_Mayor4":
			dialog.text = "의심의 여지가 없소. 피해자는 매우 유명한 인물이며, 그가 헛소문이나 비방으로 자신을 깎아내릴 사람은 아니오. 지금 우리 순찰대가 그 선장의 은닉처를 수색하고 있소. "+"찾아내면, 선장이 법정에 출두할 수 있소\n이 일에 협조해 주신다면, 진심으로 감사드리겠소.";
			link.l1 = "아마 아닐 거요. 나는 이 지역을 잘 몰라서 은닉처를 찾을 수 없소. 실례하오, 이만 가봐야겠소.";
			link.l1.go = "CapComission_Mayor5";
			link.l2 = "아마도... 시간이 얼마나 남았소?";
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
			dialog.text = "이틀 후면 순찰대가 네 도움 없이도 은닉처를 찾아낼 수 있을 것이라 생각하니, 서두르는 게 좋겠군."; 
			link.l1 = "알겠소, 내가 맡겠소. 하지만 선장에게 들러야 하오. "+pchar.GenQuest.CaptainComission.Name+". 이것이 가능하겠소?";
			link.l1.go = "CapComission_Mayor7";
		break;
		
		case "CapComission_Mayor7":
			dialog.text = "그것은 문제가 되지 않소. 당신의 방문에 대해 요새 사령관에게 알리겠소.";
			link.l1 = "감사합니다. 이제 실례하겠습니다.";
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
			dialog.text = "훌륭하군! 보물은 어디 있지?";
			link.l1 = "아직 잘 모르겠소. 그가 정확한 위치를 알려주지 않았소.";
			link.l1.go = "CapComission_Mayor10";
		break;
		
		case "CapComission_Mayor10":
			dialog.text = "흠, 참 우연이군! 있잖아, 그도 나한테 '정확한 위치'를 알려주진 않았어...";
			link.l1 = "지금 처리 중입니다.";
			link.l1.go = "CapComission_Mayor11";
		break;
		
		case "CapComission_Mayor11":
			dialog.text = "이제 더 이상 아니다\n경비병들! 죄수를 감방으로 데려가라\n너는 가도 된다, "+GetFullName(pchar)+".";
			link.l1 = "하지만 나리...";
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
			dialog.text = "훌륭하오! 그럼 그의 보물을 어디에서 찾을 것이오?";
			link.l1 = "안에 "+RandPhraseSimple(RandPhraseSimple("북쪽","서쪽"),RandPhraseSimple("동쪽","남쪽"))+" 끝 "+XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore+"Gen")+" 절벽 아래에는 큰 움푹 파인 곳이 있는데, 그 입구가 돌로 막혀 있소. 그곳이 바로 은신처요.";
			link.l1.go = "CapComission_Mayor14";
		break;
		
		case "CapComission_Mayor14":
			dialog.text = "훌륭한 일이오! 그리고 어디 있소\n "+pchar.GenQuest.CaptainComission.Name+" 그 자 말이오? 당신이 그를 요새 감옥에서 데려갔다고 들었소.";
			link.l1 = "유감스럽게도 그는 밀수업자들과의 충돌에서 목숨을 잃었습니다.";
			link.l1.go = "CapComission_Mayor15";
		break;
		
		case "CapComission_Mayor15":
			dialog.text = "이거 안 좋군... 정말 안 좋다, "+GetSexPhrase("나리","아가씨")+" "+GetFullName(pchar)+". 나는 다른 이들에게 본보기를 보이기 위해 공개 처형할 생각이었소."+"어쨌든 그는 교수대를 피하지 못했을 것이오\n그러니 자네가 법을 어기고 죄수를 불법으로 풀어주었으나 결국 그를 구하지도 못했으니, 내가 보고서에 이 일을 바로잡아 줄 수 없소. 따라서 보상은 받을 수 없네... 하지만 개인적으로 자네에게 감사를 표하고 싶소. 내 선물을 받으시오 – 싸우는 선장에게 아주 유용한 물건이오. ";
			link.l1 = "감사합니다. 언제나 기꺼이 봉사하겠습니다.";	
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
		// --------------------------Операция 'Галеон'-----------------------------
		
		// -------------------------- Генератор "Кораблекрушенцы" ------------
		case "ShipWreck1":
			if(iDay > 15)
			{
				dialog.text = RandPhraseSimple("어떻게 그렇게 하셨소? 순풍을 타고 항해해도 그곳까지는 최소한 열닷새는 걸리오!","Captain "+GetFullName(pchar)+", 그대의 무책임함에 놀랐소! 왜 진작 내게 말하지 않았소?");
				link.l1 = "글쎄, 뭐라고 해야 할지 모르겠군...";
				link.l1.go = "ShipWreck2";
			}
			else
			{
				dialog.text = "이거 정말 좋은 소식이오! 우리는 이미 다시 볼 희망을 잃었었소 "+pchar.GenQuest.ShipWreck.Name+"  다시 살아 돌아왔군. 즉시 구조대를 보내겠소. 아, 그리고 신속하게 구조에 참여해 준 것에 대한 보상도 받아 주시오.";
				link.l1 = "감사합니다, 각하. 도움이 될 수 있어 기쁩니다. 원정대가 제때 도착할 것이라 확신합니다.";
				link.l1.go = "ShipWreck3";	
			}
			pchar.GenQuest.ShipWreck.SpeakMayor = true;
			pchar.quest.ShipWreck_MeetInShore.over = "yes";
			pchar.quest.ShipWreck_SaveSailors.over = "yes"; // belamour gen таймер на 30 дней тоже нужно снять
		break;
		
		case "ShipWreck2":
			dialog.text = "이런 젠장... 뭐라 할 말이 있겠냐? 가서 해양법이나 공부해라, 이 녀석아! 어쨌든, 나는 이 사람들을 구하기 위해 최선을 다하겠다.";
			link.l1 = "각하, 하지만 저는 그들에게 충분한 식량을 남겨두었소. 시간은 있으니 안심하시오...";
			link.l1.go = "ShipWreck4";
		break;
		
		case "ShipWreck3":
			addMoneyToCharacter(pchar, sti(pchar.rank) * 300 + 3000 + rand(3000));
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			AddQuestRecord("ShipWrecked", "14");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "sCity", XI_ConvertString("Colony" + NPChar.city + "Gen")); // belamour gen просто NPChar.city ничего не даст
			AddQuestUserData("ShipWrecked", "ShoreName", XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Gen")); // belamour gen
			CloseQuestHeader("ShipWrecked");
			DeleteAttribute(pchar, "GenQuest.ShipWreck.SpeakMayor");		
			DialogExit();
			AddDialogExitQuest("ShipWreck_RemoveSailorsFromShore");
		break;		
		
		case "ShipWreck4":
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			AddQuestRecord("ShipWrecked", "13");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "sCity", XI_ConvertString("Colony" + NPChar.city + "Gen")); // belamour gen просто NPChar.city ничего не даст
			AddQuestUserData("ShipWrecked", "ShoreName", XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Gen")); // belamour gen
			CloseQuestHeader("ShipWrecked");
			DeleteAttribute(pchar, "GenQuest.ShipWreck.SpeakMayor");		
			DialogExit();
			AddDialogExitQuest("ShipWreck_RemoveSailorsFromShore");
		break;
		// -------------------------- Генератор "Кораблекрушенцы" ------------
		
		// ---------------------- найти кольцо в борделе ----------------------------
		case "TakeRing_1":
			dialog.text = "나는 자네가, 뭐랄까... 알고 있네 "+GetSexPhrase("사창가를 자주 드나드는 자요","가끔 사창가에 들르는 걸 좋아한다")+". 그래서 당신께 도움을 청하기로 결심했소\n"+"있지, 부끄럽지만 사실 나도 최근에 거기 있었어...";
			link.l1 = "그게 뭐가 문제야? 섹스는 아주 자연스러운 일이잖아...";
			link.l1.go = "TakeRing_2";
		break;
		case "TakeRing_2":
			dialog.text = "아, 아니오, 설교하는 게 아니오, 전혀. 사실은, 어느 날 술을 너무 많이 마셔서 결혼반지를 잃어버렸소...";
			link.l1 = "이거 참 곤란하군. 미안하오.";
			link.l1.go = "TakeRing_3";
		break;
		case "TakeRing_3":
			dialog.text = "나한테 동정 따위 필요 없어. 내 반지나 돌려줘. 자정 전에 그걸 되찾아오면 아주 후하게 보상하지. 실패하면, 내 아내가 날 죽일 거야.";
			link.l1 = "그렇군... 그런데 정확히 어디에서 잃어버렸소? 특별히 기억나는 것이 있소?";
			link.l1.go = "TakeRing_4";
		break;
		case "TakeRing_4":
			dialog.text = "유감스럽게도, 아니오. 아무것도 없습니다.";
			link.l1 = "알겠소. 그럼, 찾아봅시다.";
			link.l1.go = "TakeRing_5";
			link.l2 = "있잖아, "+GetAddress_FormToNPC(NPChar)+", 이 일은 사양하겠소. 실례하오...";
			link.l2.go = "TakeRing_6";
		break;	
		case "TakeRing_5":
			dialog.text = "훌륭하오! 하지만 기억하시오 - 자정 전에 반드시 찾아야 하오.";
			link.l1 = "기억하고 있소. 곧 돌아오겠소.";
			link.l1.go = "exit";
			pchar.questTemp.different = "TakeMayorsRing";
			pchar.questTemp.different.TakeMayorsRing = "toBrothel";
			pchar.questTemp.different.TakeMayorsRing.Id = GetFullName(npchar);
			pchar.questTemp.different.TakeMayorsRing.city = npchar.city;	
			pchar.questTemp.different.TakeMayorsRing.price = sti(pchar.rank)*100+1000;
			sld = ItemsFromID("MayorsRing");
			sld.CityName = XI_ConvertString("Colony" + npchar.city + "Gen");
			//ложим кольцо в итем
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
				pchar.questTemp.different.TakeMayorsRing.item = true; //флаг кольцо валяется в итемах
				Log_QuestInfo("The ring is at " + sld.startLocation + ", in locator " + sld.startLocator);
			}
			SetTimerFunction("TakeMayorsRing_null", 0, 0, 1); //освобождаем разрешалку на миниквесты 
			ReOpenQuestHeader("SeekMayorsRing");
			AddQuestRecord("SeekMayorsRing", "1");
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("SeekMayorsRing", "sName", pchar.questTemp.different.TakeMayorsRing.Id);
		break;	
		case "TakeRing_6":
			dialog.text = "오? 예상치 못한 일이군... 그럼, 행운을 빌겠소, 선장.";
			link.l1 = "안녕히 가십시오.";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
		break;

		case "TakeRing_S1":
			dialog.text = "이건 내 반지야! 내 목숨을 구해줬어!";
			link.l1 = "별일 아닙니다, 나리.";
			link.l1.go = "TakeRing_S2";
			TakeItemFromCharacter(pchar, "MayorsRing");
		break;
		case "TakeRing_S2":
			dialog.text = "수고에 대한 보수요! 정말 고맙소!";
			link.l1 = "기꺼이 도와드렸습니다, 나리. 다음에는 좀 더 조심하십시오.";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 10);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.different.TakeMayorsRing.price));
			pchar.questTemp.different = "free";
			pchar.quest.TakeMayorsRing_null.over = "yes"; //снимаем таймер
			AddQuestRecord("SeekMayorsRing", "7");
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			CloseQuestHeader("SeekMayorsRing");
			DeleteAttribute(pchar, "questTemp.different.TakeMayorsRing");
		break;
		case "TakeRing_S3":
			dialog.text = "주여, 자비를 베푸소서! 정말 술을 이렇게 많이 마시는 건 그만둬야겠군...";
			link.l1 = "그건 확실하지! 여기 네 반지야.";
			link.l1.go = "TakeRing_S4";
		break;
		case "TakeRing_S4":
			dialog.text = "예, 예, 정말 고맙소. 신세를 졌구려! 일을 잘 마무리했으니 여기 보수요!";
			link.l1 = "Thanks "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "exit";
			TakeItemFromCharacter(pchar, "MayorsRing");
			ChangeCharacterComplexReputation(pchar,"nobility", 3);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 3);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.different.TakeMayorsRing.price));
			pchar.questTemp.different = "free";
			pchar.quest.TakeMayorsRing_null.over = "yes"; //снимаем таймер
			AddQuestRecord("SeekMayorsRing", "7");
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			CloseQuestHeader("SeekMayorsRing");
			DeleteAttribute(pchar, "questTemp.different.TakeMayorsRing");
		break;
		// ---------------------- найти кольцо в борделе ----------------------------

		case "node_1":
            //ОСАДЫ homo
			if (CheckAttribute(&Colonies[FindColony(npchar.City)],"Siege"))
            {

                makearef(aData, NullCharacter.Siege);
                

                if (CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                {
                    dialog.text = "우리는 이미 모든 것을 논의했지 않소?";
                    link.l1 = "옳소. 더 이상 지체하지 않겠소.";
                    link.l1.go = "exit";

                }
                else
                {
                    dialog.text = "불쾌하게 해드려 죄송하지만, 지금은 당신과 대화할 시간이 없습니다. 아시다시피, 우리 식민지가 공격을 받았습니다. "+NationNamePeople(sti(aData.nation))+". 우리 방어를 점검해야 하오.";
                    link.l1 = "글쎄, 저는 그냥 요새 방어에 도움이 되고 싶어서 왔습니다.";
                    link.l1.go = "siege_task";
                    link.l2 = "그렇다면 더 이상 지체하지 않겠소.";
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
                    //--> слухи
                    SiegeRumour("They say that you had helped us to repel the "+NationNameSK(sti(aData.nation))+" squadron and defend our colony! We are grateful to you, "+ GetAddress_Form(NPChar)+".", aData.Colony, sti(aData.conation), -1, 15, 3);
		            //<-- слухи
                    DeleteAttribute(aData, "PlayerHelpMayor");
                    DeleteAttribute(aData, "HelpColony");
                    dialog.text = "오, 그대였군, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+", 다시 뵙게 되어 반갑습니다. 좋은 소식이 있소 – 우리가 그들을 물리치는 데 성공했소 "+NationNameSK(sti(aData.nation))+" 침입자들. 그대도 이 일에 한몫했으니, 여기 보상이 있소 - "+(sti(aData.iSquadronPower)*1500)+" 에잇 피스. 여기 있소.";
                    link.l1 = "감사합니다, "+GetAddress_FormToNPC(NPChar)+", 거래하게 되어 기쁩니다!";
                    link.l1.go = "exit";
                }
                else
                {
                    if (CheckAttribute(aData, "PlayerHelpMayor")) DeleteAttribute(aData, "PlayerHelpMayor");
                    dialog.text = "그래서 무엇 때문에 여기 와서 내 중요한 국정 업무를 방해하는 것이오?";
					if (npchar.city != "Panama") // Addon-2016 Jason
					{
						link.l1 = "나는 일하고 싶었소 "+NationNameGenitive(sti(NPChar.nation))+".";
						link.l1.go = "work";
					}
					// Warship Генер "Пираты на необитайке" - сдаём пиратов властям
					if(CheckAttribute(PChar, "Quest.PiratesOnUninhabited_OnShore") || CheckAttribute(PChar, "Quest.PiratesOnUninhabited_ShipSink"))
					{
						link.l11 = XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore+"Dat")+" 해적 몇을 만났소. 모두 "+PChar.GenQuest.PiratesOnUninhabited.PiratesCount+" 지금 배에 타고 있습니다. 나는 그들을 당국에 넘기고 싶습니다.";
						link.l11.go = "PiratesOnUninhabited_1";
					}
					
        			link.l2 = "중요한 일로 당신과 이야기하고 싶었습니다.";
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
							link.l12 = "순찰대를 지휘하는 선장이 있다 "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" 이름이 붙은 "+pchar.GenQuest.CaptainComission.Name+", 그를 어떻게 만날 수 있소?";
							link.l12.go = "CapComission_Mayor1";
						}	
						if(CheckAttribute(pchar,"GenQuest.CaptainComission.PrisonFree"))
						{
							link.l12 = "순찰을 지휘하던 전 선장 "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+" 그가 자신의 은닉처를 당국에 밝히기로 동의했다.";
							link.l12.go = "CapComission_Mayor9";
						}
						if(pchar.GenQuest.CaptainComission == "GetGoodsSuccess")
						{
							link.l12 = "순찰대를 지휘했던 전임 선장  "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+" 자신의 은닉처를 내게 드러냈소.";
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
								link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore+"Dat"))+" 나는 선장을 만났어 "+pchar.GenQuest.ShipWreck.Name+" 해적들에게 상륙당한 그의 선원들과 함께 "+pchar.GenQuest.ShipWreck.BadName+". "+"안타깝게도, 내 배에는 이미 사람이 너무 많아서 그들을 태울 수 없었소. 하지만 음식과 무기는 남겨두었소. 만약 구조선이 정해진 시간 안에 그들을 데려가지 않는다면\n "+(30 - iDay)+" 며칠이 지나면, 내가 그들을 아직 살아 있는 상태로 찾을 수 있을지 모르겠소.";
								link.l13.go = "ShipWreck1";
							}
							else
							{
								link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore+"Dat"))+" 난 난파된 배 '에서 온 선원들을 만났어"+pchar.GenQuest.ShipWreck.ShipTypeName+"' 그들의 선장과 함께. "+"안타깝게도, 내 배에는 이미 사람이 너무 많아서 그들을 태울 수 없었소. 하지만 나는 음식과 무기를 남겨두었소. 만약 구조선이 정해진 기간 내에 그들을 데려가지 않는다면\n "+(30 - iDay)+" 며칠이 지나면, 내가 그들을 아직 살아 있는 채로 찾을 수 있을지 모르겠소.";
								link.l13.go = "ShipWreck1";							
							}	
						}	
					}					
					//--> Jason, генер почтового курьера 2 уровня
						if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
						{
							if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
							{
							link.l14 = "나는 에서 온 전갈을 가지고 있소 "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
							link.l14.go = "Postcureer_LevelUp_ForAll";
							}
						}
					//<-- генер почтового курьера 2 уровня
					
					// --> Warship, 16.05.11. Квест "Правосудие на продажу".
					if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_townhall")
					{
						link.l15 = "나리, 밀수꾼 무리를 찾아냈습니다. 그들의 두목이 최근 경비병들에게 붙잡혔는데, 지금 그들은 그의 탈출을 모의하고 있습니다. 그들의 배 '"+PChar.GenQuest.JusticeOnSale.ShipName+"'이(가) 정박해 있다 "+XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId+"Gen")+".";
						link.l15.go = "JusticeOnSale_1";
					}
					//<-- Правосудие на продажу
					
        			if (GetPrisonerQty() > 0)
        			{
                        link.l3 = "포로로 잡은 선장을 당국에 넘겨야 하오.";
        			    link.l3.go = "sell_prisoner";
        			}
					//Jason --> Регата
					if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
					{
						link.l4 = "저는 레가타 때문에 왔습니다. 여기 제 초대장이 있습니다.";
						link.l4.go = "Regata";
					}
        			link.l5 = "잠시 쉬고 싶으신가요?";
        			link.l5.go = "Play_Game";
        			link.l10 = "단순한 예의상 방문이었소, "+GetAddress_FormToNPC(NPChar)+".";
        			link.l10.go = "node_2";
                }
    		}//<-
		break;
		
		case "Helen_node_1":
            //ОСАДЫ homo
			if (CheckAttribute(&Colonies[FindColony(npchar.City)],"Siege"))
            {

                makearef(aData, NullCharacter.Siege);
                

                if (CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                {
                    dialog.text = "우리는 이미 모든 것을 논의했지 않소?";
                    link.l1 = "옳소. 더 이상 지체하지 않겠소.";
                    link.l1.go = "exit";

                }
                else
                {
                    dialog.text = "불쾌하게 해드려 죄송하오만, 지금은 당신과 이야기할 시간이 없소. 아시다시피, 우리 식민지가 공격을 받았소\n "+NationNamePeople(sti(aData.nation))+". 우리 방어를 살펴봐야 하오.";
                    link.l1 = "음, 저는 그저 요새 방어에 제 도움이 필요하신지 여쭙고 싶었습니다.";
                    link.l1.go = "siege_task";
                    link.l2 = "그렇다면 더 이상 지체하지 않겠소.";
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
                    //--> слухи
                    SiegeRumour("They say that you had helped us to repel the "+NationNameSK(sti(aData.nation))+" squadron and defend our colony! We are grateful to you, "+ GetAddress_Form(NPChar)+".", aData.Colony, sti(aData.conation), -1, 15, 3);
		            //<-- слухи
                    DeleteAttribute(aData, "PlayerHelpMayor");
                    DeleteAttribute(aData, "HelpColony");
                    dialog.text = "오, 그대였군, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+", 다시 뵙게 되어 반갑습니다. 좋은 소식이 있소 – 우리가 그들을 물리쳤습니다 "+NationNameSK(sti(aData.nation))+" 침입자들. 너도 이 일에 한몫했으니, 여기 보상이 있네 - "+(sti(aData.iSquadronPower)*1500)+" 에잇 피스. 여기 있소.";
                    link.l1 = "감사합니다, "+GetAddress_FormToNPC(NPChar)+", 함께 거래해서 즐거웠소!";
                    link.l1.go = "exit";
                }
                else
                {
                    if (CheckAttribute(aData, "PlayerHelpMayor")) DeleteAttribute(aData, "PlayerHelpMayor");
                    dialog.text = "무슨 일로 나를 찾아왔소? 자네 일은 모두 그... 후원자와 처리하는 줄 알았는데. 하지만 말해보시오, 자네 얘기는 언제든 기꺼이 들어주겠소.";
					if (npchar.city != "Panama") // Addon-2016 Jason
					{
						link.l1 = "나는 일하고 싶었소 "+NationNameGenitive(sti(NPChar.nation))+".";
						link.l1.go = "work";
					}
					// Warship Генер "Пираты на необитайке" - сдаём пиратов властям
					if(CheckAttribute(PChar, "Quest.PiratesOnUninhabited_OnShore") || CheckAttribute(PChar, "Quest.PiratesOnUninhabited_ShipSink"))
					{
						link.l11 = XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore+"Dat")+" 해적 몇을 만났소. 전부 "+PChar.GenQuest.PiratesOnUninhabited.PiratesCount+" 현재 배에 타고 있습니다. 그들을 당국에 넘기고 싶습니다.";
						link.l11.go = "PiratesOnUninhabited_1";
					}
					
        			link.l2 = "중요한 일로 당신과 이야기하고 싶었습니다.";
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
							link.l12 = "순찰대를 지휘하는 선장이 있다 "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" 이름이 붙은 "+pchar.GenQuest.CaptainComission.Name+", 내가 그를 어떻게 만날 수 있소?";
							link.l12.go = "CapComission_Mayor1";
						}	
						if(CheckAttribute(pchar,"GenQuest.CaptainComission.PrisonFree"))
						{
							link.l12 = "순찰대를 지휘했던 전 선장 "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+" 그가 은닉처를 당국에 밝히기로 동의했다.";
							link.l12.go = "CapComission_Mayor9";
						}
						if(pchar.GenQuest.CaptainComission == "GetGoodsSuccess")
						{
							link.l12 = "순찰대를 지휘하던 전임 선장  "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+" 그가 나에게 그의 은닉처를 밝혔소.";
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
								link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore+"Dat"))+" 나는 선장을 만났어 "+pchar.GenQuest.ShipWreck.Name+" 해적들에게 상륙당한 그의 선원들과 함께 "+pchar.GenQuest.ShipWreck.BadName+". "+"안타깝게도 내 배에 이미 사람이 너무 많아서 그들을 태울 수 없었소. 하지만 식량과 무기는 남겨두었지. 만약 구조선이 정해진 시간 안에 그들을 데려가지 않는다면\n "+(30 - iDay)+" 며칠이 지나면, 내가 그들을 아직 살아 있는 채로 찾을 수 있을지 모르겠소.";
								link.l13.go = "ShipWreck1";
							}
							else
							{
								link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore+"Dat"))+" 난 난파된 배 '에서 온 선원들을 만났어"+pchar.GenQuest.ShipWreck.ShipTypeName+"' 그들의 선장과 함께. "+"안타깝게도, 내 배에는 이미 사람이 너무 많아서 그들을 태울 수 없었소. 하지만 음식과 무기는 남겨 두었소. 만약 구조선이 그들을 정해진 시간 안에 데려가지 않는다면\n "+(30 - iDay)+" 며칠이 지나면, 내가 그들을 아직 살아 있는 채로 찾을 수 있을지 모르겠소.";
								link.l13.go = "ShipWreck1";							
							}	
						}	
					}					
					//--> Jason, генер почтового курьера 2 уровня
						if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
						{
							if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
							{
							link.l14 = "나는 에서 온 전갈을 가지고 있소 "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
							link.l14.go = "Postcureer_LevelUp_ForAll";
							}
						}
					//<-- генер почтового курьера 2 уровня
					
					// --> Warship, 16.05.11. Квест "Правосудие на продажу".
					if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_townhall")
					{
						link.l15 = "나리, 밀수꾼 무리를 찾아냈습니다. 그 두목이 최근 경비병들에게 붙잡혔는데, 지금 그들은 그의 탈출을 모의하고 있습니다. 그들의 배 '"+PChar.GenQuest.JusticeOnSale.ShipName+"'이(가) 정박해 있다 "+XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId+"Gen")+".";
						link.l15.go = "JusticeOnSale_1";
					}
					//<-- Правосудие на продажу
					
        			if (GetPrisonerQty() > 0)
        			{
                        link.l3 = "포로로 잡은 선장을 당국에 넘겨야 하오.";
        			    link.l3.go = "sell_prisoner";
        			}
					//Jason --> Регата
					if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
					{
						link.l4 = "저는 레가타 때문에 왔습니다. 여기 제 초대장이 있습니다.";
						link.l4.go = "Regata";
					}
        			link.l5 = "잠시 쉬고 싶으신가요?";
        			link.l5.go = "Play_Game";
        			link.l10 = "그저 예의상 방문이었소, "+GetAddress_FormToNPC(NPChar)+".";
        			link.l10.go = "node_2";
                }
    		}//<-
		break;
		
		case "Play_Game":
			//==> прибыла инспекция на Святом Милосердии
			if (CheckAttribute(npchar, "quest.SantaMisericordia"))
			{
    			dialog.text = "지금은 안 돼! 검열이 있거든, 알라미다 나리가 도시에 와 있어. 아, 매년 똑같은 일이라니, 내가 뭘 잘못해서 이런 벌을 받는 거지...";
				link.l1 = "그러하오. 더 이상 방해하지 않겠소.";
				link.l1.go = "exit"; 
				break;
			}
			//<== прибыла инспекция на Святом Милосердии
			dialog.text = "흠, 어떤 놀이를 좋아하시오?";
			link.l1 = "큰돈을 걸고 카드 한 판 할래?";
			link.l1.go = "Card_Game";
   			link.l2 = "포커-조커에서 주사위 한 번 굴려볼래?";
			link.l2.go = "Dice_Game";
			link.l10 = "실례하오, 하지만 의무가 나를 부르오.";
			link.l10.go = "exit";
		break;
		
		//  карты -->
        case "Card_Game":
            if (!CheckNPCQuestDate(npchar, "Card_date_Yet") || sti(PChar.rank) < 4 || isBadReputation(pchar, 50) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(5))
            {
                SetNPCQuestDate(npchar, "Card_date_Yet");
				// belamour legendary edition фикс проверки мундира с мушкетом
				if(IsUniformEquip()) dialog.text = "실례합니다, 몬시뇰 나리, 하지만 지금은 그럴 시간이 없습니다. 다음 기회에 하도록 하지요."; // Jason НСО
                else dialog.text = "나는 해적들과 도박하지 않소!";
    			link.l1 = "그러하옵니다.";
    			link.l1.go = "exit";
			}
			else
			{
				if (CheckNPCQuestDate(npchar, "Card_date_begin"))
				{
					dialog.text = "왜 안 되겠어! 쉬는 건 마음에는 좋지만, 지갑에는 안 좋지...";
	    			link.l1 = "훌륭하오.";
	    			link.l1.go = "Cards_begin";
	    			link.l2 = "우리 게임의 규칙이 무엇이오?";
	    			link.l2.go = "Cards_Rule";
    			}
    			else
    			{
					dialog.text = "아니, 오늘은 여기까지다. 할 일이 좀 있거든.";
	    			link.l1 = "원하시는 대로 하겠습니다.";
	    			link.l1.go = "exit";
				}
			}
		break;

		case "Cards_Rule":
   			dialog.text = CARDS_RULE;
			link.l1 = "자, 그럼 시작하자!";
			link.l1.go = "Cards_begin";
			link.l3 = "아니, 나를 위한 게 아니오...";
			link.l3.go = "exit";
		break;

		case "Cards_begin":
			dialog.text = "먼저 내기부터 합의하자.";
			link.l1 = "1,000 에잇을 걸고 한 판 하자.";
			link.l1.go = "Cards_Node_100";
			link.l2 = "5,000에이트 동전을 걸고 한 판 하자.";
			link.l2.go = "Cards_Node_500";
			link.l3 = "가야겠군.";
			link.l3.go = "exit";
		break;

		case "Cards_Node_100":
			//belamour legendary edition 
			bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
			bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
			bOk = bOk1 || bOk2;
            if (!CheckCardsGameSmallRate() && !bOk)
		    {
                dialog.text = "너는 악명 높은 사기꾼이오. 나는 너와 도박하지 않겠소.";
                link.l1 = "전부 거짓말이야!";
			    link.l1.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 3000)
		    {
                dialog.text = "농담하시오, "+GetAddress_Form(NPChar)+"? 돈이 없잖아!";
                link.l1 = "그런 일도 있지.";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 3000)
		    {
                dialog.text = "이제 그만이야! 더 이상 카드 안 해—낭비꾼 소리 듣고 자리에서 쫓겨나기 전에.";
                link.l1 = "안타깝군.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "좋아, 1,000에이트 동전을 걸고 한 판 하자.";
			link.l1 = "시작하자!";
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
                dialog.text = "너는 악명 높은 사기꾼이오. 나는 너와 도박하지 않겠소.";
                link.l1 = "전부 거짓말이야! 뭐, 어쨌든.";
			    link.l1.go = "exit";
			    break;
		    }
			if (!CheckCardsGameBigRate())
		    {
                dialog.text = "당신이 아주 뛰어난 선수라더군. 나는 당신과 큰돈을 걸고 놀 생각 없어.";
                link.l1 = "내기를 좀 낮춰 볼까?";
			    link.l1.go = "Cards_Node_100";
				link.l2 = "미안하지만, 나는 가야 하오.";
			    link.l2.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 15000)
		    {
                dialog.text = "농담하시는 겁니까, "+GetAddress_Form(npchar)+"? 자네에겐 15,000에이트 동전이 없잖아!";
                link.l1 = "내가 올릴게!";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 15000)
		    {
                dialog.text = "아니오, 이런 내기는 도시 금고를 텅 비게 만들 것입니다.";
                link.l1 = "원하시는 대로 하겠습니다.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "좋아, 5,000 에잇 동전을 걸고 한 판 하자.";
			link.l1 = "시작하자!";
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
	    // карты <--

	    //  Dice -->
        case "Dice_Game":
            if (!CheckNPCQuestDate(npchar, "Dice_date_Yet") || sti(PChar.rank) < 4 || isBadReputation(pchar, 50) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(5))
            {
                SetNPCQuestDate(npchar, "Dice_date_Yet");
				// belamour legendary edition фикс проверки мундира с мушкетом
				if(IsUniformEquip()) dialog.text = "실례합니다, 몬시뇰 나리, 하지만 지금은 그럴 시간이 없습니다. 다음 기회에 뵙겠습니다."; // Jason НСО
                else dialog.text = "나는 해적들과 도박하지 않겠소!";
    			link.l1 = "원하시는 대로 하겠습니다.";
    			link.l1.go = "exit";
			}
			else
			{
				if (CheckNPCQuestDate(npchar, "Dice_date_begin"))
				{
					dialog.text = "왜 안 되겠소! 쉬는 건 심장에는 좋지... 하지만 지갑에는 안 좋지...";
	    			link.l1 = "훌륭하오.";
	    			link.l1.go = "Dice_begin";
	    			link.l2 = "우리 게임의 규칙이 무엇이오?";
	    			link.l2.go = "Dice_Rule";
    			}
    			else
    			{
					dialog.text = "아니, 오늘은 여기까지다. 할 일이 좀 있거든.";
	    			link.l1 = "원하시는 대로 하겠습니다.";
	    			link.l1.go = "exit";
				}
			}
		break;

		case "Dice_Rule":
   			dialog.text = DICE_RULE;
			link.l1 = "자, 그럼 시작하자!";
			link.l1.go = "Dice_begin";
			link.l3 = "아니, 나를 위한 건 아니오...";
			link.l3.go = "exit";
		break;

		case "Dice_begin":
			dialog.text = "먼저 내기부터 합의하자.";
			link.l1 = "주사위 하나당 500에이트씩 걸고 놀자.";
			link.l1.go = "Dice_Node_100";
			link.l2 = "주사위 하나당 2,000피스의 에잇을 걸고 놀자.";
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
                dialog.text = "너는 악명 높은 사기꾼이오. 나는 너와 도박하지 않겠소.";
                link.l1 = "전부 거짓말이야! 뭐, 어쨌든.";
			    link.l1.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 3000)
		    {
                dialog.text = "농담하시는 겁니까, "+GetAddress_Form(NPChar)+"? 돈이 없으시군요!";
                link.l1 = "그런 일도 있지.";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 3000)
		    {
                dialog.text = "그만이다! 이제 도박은 끝이야 - 사람들이 나를 낭비벽 있는 놈이라고 부르고 내 자리에서 쫓아내기 전에...";
                link.l1 = "안타깝군.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "좋아, 500에이트 동전을 걸고 한 판 하자.";
			link.l1 = "시작하자!";
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
                dialog.text = "너는 악명 높은 사기꾼이오. 나는 너와 도박하지 않겠소.";
                link.l1 = "다 거짓말이야! 뭐, 어쩌라고.";
			    link.l1.go = "exit";
			    break;
		    }
			if (!CheckDiceGameBigRate())
		    {
                dialog.text = "당신이 아주 뛰어난 선수라고들 하더군. 나는 당신과 큰 판은 안 벌이겠소.";
                link.l1 = "내기를 좀 낮춰 볼까요?";
			    link.l1.go = "Dice_Node_100";
				link.l2 = "미안하지만, 나는 가야 하오.";
			    link.l2.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 15000)
		    {
                dialog.text = "농담하시오, "+GetAddress_Form(NPChar)+"? 자네에겐 15,000에이트 동전이 없지 않나!";
                link.l1 = "내가 올릴게!";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 15000)
		    {
                dialog.text = "아니오, 이런 내기들은 분명히 도시 금고를 텅 비게 만들 것이오.";
                link.l1 = "원하시는 대로 하겠습니다.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "좋아, 주사위 하나당 2,000에이트씩 걸고 하자.";
			link.l1 = "시작하자!";
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
	    // Dice <--
		case "node_2":
			dialog.text = "그렇다면, 내 서재에서 나가 주고 더 이상 내 일을 방해하지 말아 주시오";
			link.l1 = "예, 예, 물론이지요. 귀찮게 해서 미안하오.";
			link.l1.go = "exit";
		break;

		//---------------------------- генератор квестов мэра -------------------------------
		case "work": 
            dialog.text = "이건 버그야. 개발자들에게 알려 줘.";
        	link.l1 = "고마워, 정말 멋진 게임이야!";
        	link.l1.go = "exit";
			
			//==> прибыла инспекция на Святом Милосердии
			if (CheckAttribute(npchar, "quest.SantaMisericordia"))
			{
    			dialog.text = "지금은 안 돼! 검열이 있거든, 알라미다 나리가 도시에 와 있어. 아, 매년 똑같은 일이 반복되니, 내가 뭘 잘못해서 이런 벌을 받는 건지...";
				link.l1 = "말씀대로 하십시오. 더 이상 방해하지 않겠소.";
				link.l1.go = "exit"; 
				break;
			}
			//<== прибыла инспекция на Святом Милосердии
			//==> взят ли какой-либо квест
			if (CheckAttribute(pchar, "GenQuest.questName"))
			{		 				
				//--> Федот, да не тот
				QuestName = pchar.GenQuest.questName;
				if (pchar.GenQuest.(QuestName).MayorId != npchar.id) 
				{					
					dialog.text = RandPhraseSimple("내가 알기로는, 이미 "+XI_ConvertString("Colony"+npchar.city+"Gen")+"의 총독에게 임무를 받은 상태요 "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.(QuestName).MayorId)].city+"Gen")+". 이미 맡은 일을 끝내시오, 그 후에 이야기하겠소.","흠, 그게 바로 너 아니었나 "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.(QuestName).MayorId)].city+"Voc")+" 현지 총독에게 명령을 받은 곳 말인가? 맞소. 그 임무부터 먼저 끝내시오.");
					link.l1 = RandPhraseSimple("그렇군...","알겠습니다..."+GetSexPhrase("","")+", "+GetAddress_FormToNPC(NPChar)+".");
					link.l1.go = "exit";					
					break;
				}
				//<--Федот, да не тот
				//-------- взят квест уничтожения банды ---------->>
				if (QuestName == "DestroyGang")
				{
					switch (pchar.GenQuest.DestroyGang)
					{
						makearef(arName, pchar.GenQuest.DestroyGang);
						case "":
							dialog.text = LinkRandPhrase("도적을 찾는 임무 "+GetFullName(arName)+" 이미 당신에게 발급되었소. 이제 그 임무를 완수하시오!","당신은 이미 이름이 알려진 도적을 찾는 임무를 받고 있소 "+GetFullName(arName)+". 결과를 기다리고 있소!","그대가 내 저택에서 시간을 허비하고 있는 동안, "+GetFullName(arName)+" 우리 식민지 주민들을 약탈하고 있소! 어서 일하시오!");
							link.l1 = RandPhraseSimple("좋아, "+GetAddress_FormToNPC(NPChar)+".","그 일로 바쁘오, "+GetAddress_FormToNPC(NPChar)+".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("그 산적을 찾아내어 처단하라고 준 시간이 이미 끝났소. 그런데 내가 지금 어떤 보고를 받고 있다고 생각하시오? 내가 말해주지 - "+GetFullName(arName)+" 아직도 멀쩡히 살아 있군! 이제 네가 무슨 짓을 했는지 말해 봐, "+GetAddress_Form(NPChar)+".","그 악당을 처치하라고 준 시간이 "+GetFullName(arName)+", 다 떨어졌소. 그런데도 아무런 진전이 없었다는 보고만 받고 있소. 대체 무슨 일이오?");
							link.l1 = "지정된 시간 안에 나리의 일을 수행하지 못했습니다, "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("자, 어떻게 되었소? 내가 말한 그 산적을 처치했소? "+GetFullName(arName)+" 드디어 죽었나?","한 가지만 말해 주시오 - "+GetFullName(arName)+" 죽었나, 살아 있나?");
							link.l1 = "유감스럽게도, 아직 살아 있소, "+GetAddress_FormToNPC(NPChar)+". 놈을 쫓아내는 데는 성공했지만, 상대가 되지 않아 물러설 수밖에 없었소. 그 도적놈, 정말 만만치 않은 악당이오. 미안하오.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("그래서, 어떻게 되었소? 내가 말한 그 산적을 처치했소? "+GetFullName(arName)+" 드디어 죽었나?","한 가지만 말해 주시오 - 과연 "+GetFullName(arName)+" 죽었든 살았든?");
							link.l1 = "그는 죽었소, "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 180);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
						break;
					}
				}
				//-------- контркурьер ---------->>
				if (QuestName == "TakePostcureer")
				{
					switch (pchar.GenQuest.TakePostcureer)
					{
						case "":
							dialog.text = LinkRandPhrase("전령선을 포획하는 임무는 이미 그대에게 맡겼소. 이제 실행하시오!","이미 사절선 나포 임무를 받고 있지 않소! 결과를 기다리고 있겠소!","그대가 내 관저에서 시간을 허비하는 동안, 내가 필요한 문서들이 적의 손에 넘어가고 있소! 어서 일하시오!");
							link.l1 = RandPhraseSimple("알겠소, "+GetAddress_FormToNPC(NPChar)+".","그 일로 바쁘오, "+GetAddress_FormToNPC(NPChar)+".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("그 사절선의 위치를 찾아 포획하라는 기한이 끝났소. 그런데 내가 어떤 보고를 받고 있는지 아시오? 말해 주지. 내가 기대했던 문서들이 적의 손에 넘어갔다는 소식이오! 이제 변명이나 해 보시오, "+GetAddress_Form(NPChar)+".","전령선에서 문서를 확보하라는 데 주어진 시간이 모두 끝났소. 그런데도 아무런 진전이 없었구려. 이게 대체 무슨 일이오?");
							link.l1 = "나는 제때 일을 끝내지 못했소, "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("자, 어찌 생각하시오? 문서를 손에 넣었소?","한 가지만 말해 주시오 - 그 서신을 확보했소?");
							link.l1 = "유감스럽게도, 아니오, "+GetAddress_FormToNPC(NPChar)+". 나는 배를 찾았으나, 문서들은 놓치고 말았소.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("그래서, 어떻게 되었소? 서류를 구해왔소?","한 가지만 말해 주시오 - 서신을 확보했소?");
							link.l1 = "예, "+GetAddress_FormToNPC(NPChar)+". 가지고 있소. 여기 있소.";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 200);
							AddCharacterExpToSkill(PChar, "Fortune", 300);
							AddCharacterExpToSkill(PChar, "Sneak", 150);
							RemoveItems(pchar, "ContraPostLetters", 1);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
						break;
					}
				}
				//-------- контрфрахт - арсенал ---------->>
				if (QuestName == "TakeArsenalship")
				{
					switch (pchar.GenQuest.TakeArsenalship)
					{
						case "":
							dialog.text = LinkRandPhrase("군사 수송선을 파괴하는 임무는 이미 그대에게 주어졌소. 이제 실행하시오!","당신은 이미 군수 수송선을 파괴하는 임무를 맡았소! 결과를 기다리고 있소!","그대가 내 관저에서 시간을 허비하는 동안, 화약과 탄약이 적의 대포로 곧장 전달되고 있소! 어서 일하시오!");
							link.l1 = RandPhraseSimple("좋소, "+GetAddress_FormToNPC(NPChar)+".","그 일로 바쁘오, "+GetAddress_FormToNPC(NPChar)+".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("그 군수 수송선을 찾아 파괴하라는 명령의 기한이 이미 지났소. 그런데 내가 지금 어떤 보고를 받고 있는지 아시오? 말해주지 - 적의 호송대가 무사히 목적지에 도착했다는 소식이오! 이제 그대가 직접 해명해 보시오, \n "+GetAddress_Form(NPChar)+".","적군 군수 수송선을 파괴하라고 준 시간이 모두 끝났소. 그런데도 아무런 진전이 없었소. 도대체 무슨 일이오?");
							link.l1 = "주어진 시간 안에 나리의 임무를 완수하지 못하였습니다, "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("그래서, 어떻게 되었소? 적의 수송선을 파괴하는 데 성공했소?","한 가지만 말해 주시오 - 그 적의 화물이 지금 바닷속에 가라앉아 있소?");
							link.l1 = "유감스럽게도, 아니오, "+GetAddress_FormToNPC(NPChar)+". 호송대를 찾았으나, 목표 선박을 침몰시키는 데 실패했습니다.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("그래서, 어떻게 되었소? 그 적의 수송선을 파괴하는 데 성공했소?","한 가지만 말해 주시오 - 적의 무기고가 바닷속에 잠겨 있소?");
							link.l1 = "예, "+GetAddress_FormToNPC(NPChar)+". 우리 적이 그 화약과 탄약을 받지 못할 것이오.";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 220);
							AddCharacterExpToSkill(PChar, "Fortune", 300);
							AddCharacterExpToSkill(PChar, "Sneak", 150);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
						break;
					}
				}
				//-------- ОЗГ - пират ---------->>
				if (QuestName == "TakePirateship")
				{
					switch (pchar.GenQuest.TakePirateship)
					{
						case "":
							dialog.text = LinkRandPhrase("해적을 처치하는 임무는 이미 너에게 주어졌소. 이제 그 임무를 완수하시오!","당신은 이미 해적선을 격침하는 임무를 맡았소! 결과를 기다리고 있겠소!","그대가 내 관저에서 시간을 허비하는 동안, 그 더러운 해적이 또 다른 희생자를 털고 있소! 어서 일하시오!");
							link.l1 = RandPhraseSimple("좋아, "+GetAddress_FormToNPC(NPChar)+".","그 일로 바쁘오, "+GetAddress_FormToNPC(NPChar)+".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("네게 주어진 시간은 끝났소. 그런데 내가 어떤 보고를 받고 있다고 생각하시오? 말해주지 - 그 더러운 해적이 아직도 우리 배를 습격하고 있다오! 이제 변명해 보시오, "+GetAddress_Form(NPChar)+".","해적선을 격침하라고 준 시간이 모두 끝났소. 그런데도 아무런 진전이 없었소. 무슨 일입니까?");
							link.l1 = "제가 맡기신 일을 제때 끝내지 못했습니다, "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("그래서, 어떻게 되었소? 해적선을 파괴하는 데 성공했소?","한 가지만 말해 주시오 - 그 더러운 해적이 드디어 바다 밑바닥에 잠들었소?");
							link.l1 = "유감스럽게도, 아니오, "+GetAddress_FormToNPC(NPChar)+". 그 악당을 쫓아내는 데는 성공했지만, 그의 배를 침몰시키는 데는 실패했소.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("그래서, 어떻게 되었소? 해적선을 파괴하는 데 성공했소?","한 가지만 말해 주시오 - 그 더러운 해적이 드디어 바다 밑바닥에 잠들었소?");
							link.l1 = "예, "+GetAddress_FormToNPC(NPChar)+". 저 악당은 더 이상 우리 상선들을 괴롭히지 못할 것이오.";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 250);
							AddCharacterExpToSkill(PChar, "Fortune", 300);
							AddCharacterExpToSkill(PChar, "Sneak", 150);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
						break;
					}
				}
					//-------- ОЗГ - пассажир ---------->>
				if (QuestName == "TakePassenger")
				{
					switch (pchar.GenQuest.TakePassenger)
					{
						case "":
							dialog.text = LinkRandPhrase("범죄자를 추적하는 임무는 이미 그대에게 주어졌소. 이제 실행하시오!","이미 범죄자를 찾는 임무를 받고 있지 않소! 나는 결과를 기다리고 있소!","그대가 내 저택에서 시간을 허비하는 동안, 그 더러운 악당은 계속 바다를 누비고 있소! 즉시 그대에게 맡긴 임무를 수행하시오!");
							link.l1 = RandPhraseSimple("좋아, "+GetAddress_FormToNPC(NPChar)+".","그 일로 바쁘오, "+GetAddress_FormToNPC(NPChar)+".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("그 악당을 찾으라고 준 시간이 끝났소. 그런데 내가 어떤 보고를 받고 있다고 생각하시오? 말해주지. 그자는 무사히 목적지에 도착한 뒤, 연기처럼 사라졌다는군! 이제 자네가 직접 해명해 보시오, "+GetAddress_Form(NPChar)+".","범인을 찾으라고 준 시간이 모두 끝났소. 그런데도 아무런 진전이 없구려. 도대체 무슨 일이오?");
							link.l1 = "말씀하신 기간 내에 임무를 완수하지 못했습니다, "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("그래서, 어떻게 되었소? 그 악당을 잡았소?","한 가지만 말해 주시오 - 그 더러운 악당이 당신의 선창에 재갈이 물리고 수갑이 채워져 있소?");
							link.l1 = "유감스럽게도, 아니오, "+GetAddress_FormToNPC(NPChar)+". 악당을 잡는 데 실패했소. 그 자는 타고 있던 배와 함께 침몰했소.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("그래서, 어찌 되었소? 그 악당을 잡았소?","한 가지만 말해 주시오 - 그 더러운 악당이 당신의 선창에 재갈이 물리고 수갑이 채워져 있는가?");
							link.l1 = "예, "+GetAddress_FormToNPC(NPChar)+". 부두로 병사들을 보내 주십시오, 그러면 제가 그를 넘기겠소.";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 250);
							AddCharacterExpToSkill(PChar, "Fortune", 300);
							AddCharacterExpToSkill(PChar, "Sneak", 200);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
							sld = &Characters[sti(Pchar.GenQuest.TakePassenger.PrisonerIDX)];
							ReleasePrisoner(sld); //освободили пленника
							sld.lifeday = 0;
						break;
					}
				}
				//-------- таможенный патруль ---------->>
				if (QuestName == "CustomPatrol")
				{
					switch (pchar.GenQuest.CustomPatrol)
					{
						case "":
							dialog.text = LinkRandPhrase("밀수업자들을 찾아내는 임무는 이미 그대에게 맡겼소. 이제 실행하시오!","당신은 이미 밀수업자들을 찾으라는 임무를 받았소! 나는 결과를 기다리고 있소!","그대가 내 저택에서 시간을 허비하는 사이에, 그 밀수꾼들은 또 다른 거래를 준비하고 있소! 즉시 그대에게 맡겨진 임무를 수행하시오!");
							link.l1 = RandPhraseSimple("좋아, "+GetAddress_FormToNPC(NPChar)+".","그 일로 바쁘오, "+GetAddress_FormToNPC(NPChar)+".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("밀수업자들을 찾으라고 준 시간이 끝났소. 그런데 내가 받고 있는 보고가 어떤 것 같소? 말해주지. 놈들이 물건을 모두 팔아치웠다고 하더군! 이제 변명이나 해 보시오, "+GetAddress_Form(NPChar)+".","밀수업자들을 찾으라고 준 시간이 모두 끝났소. 그런데도 아무런 진전이 없구려. 도대체 무슨 일입니까?");
							link.l1 = "제가 나리의 임무를 제때 완수하지 못했습니다, "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("자, 어찌 생각하시오? 밀수꾼들을 처리했소?","한 가지만 말해 주시오 - 밀수업자들과의 거래를 망쳐 놓았소?");
							link.l1 = "유감스럽게도, 아닙니다, "+GetAddress_FormToNPC(NPChar)+". 그 악당들의 계획을 저지하지 못했소.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("그래서, 어떻게 하겠소? 밀수꾼들을 처리했소?","한 가지만 말해 주시오 - 그 밀수업자들의 거래를 망쳐 놓았소?");
							link.l1 = "예, "+GetAddress_FormToNPC(NPChar)+". 나는 그들을 따라잡아 구매자와 판매자 양쪽의 배를 모두 파괴했소.";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 200);
							AddCharacterExpToSkill(PChar, "Fortune", 300);
							AddCharacterExpToSkill(PChar, "Sneak", 300);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
						break;
					}
				}
				//-------- Дезертир ---------->>
				if (QuestName == "FindFugitive")
				{
					switch (pchar.GenQuest.FindFugitive)
					{
						case "":
							dialog.text = LinkRandPhrase("탈영병을 찾는 임무는 이미 너에게 주어졌으니, 이제 실행하라!","이미 탈영병을 찾는 임무를 받고 있지 않소! 나는 결과를 기다리고 있네!","그대가 내 관저에서 시간을 허비하는 동안, 그 탈영병이 우리 국가의 비밀을 배신하고 있을 수도 있소! 즉시 그대에게 맡겨진 임무를 수행하시오!");
							link.l1 = RandPhraseSimple("좋아, "+GetAddress_FormToNPC(NPChar)+".","그 일로 바쁘오, "+GetAddress_FormToNPC(NPChar)+".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("탈영병을 찾으라고 준 시간이 끝났소. 그런데 내가 어떤 보고를 받고 있는지 아시오? 말해주지 – 아무것도, 전혀 없소! 이제, 자네가 직접 해명해 보시오. "+GetAddress_Form(NPChar)+".","탈영병을 찾으라고 준 시간이 모두 끝났소. 그런데도 아무런 진전이 없구려. 도대체 무슨 일입니까?");
							link.l1 = "제가 나리의 일을 제때 끝내지 못했습니다, "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("자, 어찌 생각하시오? 탈영병을 잡았소?","한 가지만 말해 주시오 - 그 탈영병이 당신의 선창에 재갈을 물리고 수갑을 찬 채 있는가?");
							link.l1 = "유감스럽게도, 아니오, "+GetAddress_FormToNPC(NPChar)+". 그 악당을 잡는 데 실패했소. 그의 흔적을 식민지에서 찾았소 "+XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.City)+", 하지만 내가 도착하기 바로 전날 그가 해적선 타고 남쪽으로 갔소. 이제는 아마 운 좋은 그 해적들과 함께 있겠지.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("뭐, 어쩔 수 없지... 여기 우리 "+pchar.GenQuest.FindFugitive.Name+"... 훌륭하오, 선장! 수색하느라 고생했소?","오, 이런 귀한 손님들이 오셨군! 안녕하시오, "+pchar.GenQuest.FindFugitive.Name+"! 훌륭하오, 선장! 수색에 많은 노력을 기울였소?");
							link.l1 = "어떻게 말하지, "+GetAddress_FormToNPC(NPChar)+". 무엇이었든, 임무는 완수되었소.";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 300);
							AddCharacterExpToSkill(PChar, "Fortune", 300);
							AddCharacterExpToSkill(PChar, "Sneak", 200);
							ChangeCharacterComplexReputation(pchar, "authority", 1);
							sld = &Characters[sti(Pchar.GenQuest.FindFugitive.PrisonerIDX)];
							ReleasePrisoner(sld); //освободили пленника
							LAi_SetActorType(sld);
							sld.lifeday = 0;
							pchar.quest.FindFugitive_Over.over = "yes"; //снимаем таймер
							chrDisableReloadToLocation = false;//открыть локацию
						break;
					}
				}
				//------ проникновение во враждебный город ------------>>
				if (QuestName == "Intelligence")
				{
					switch (pchar.GenQuest.Intelligence)
					{
						case "":
							if (GetQuestPastDayParam("GenQuest.Intelligence") > sti(pchar.GenQuest.Intelligence.Terms))
							{
								dialog.text = RandPhraseSimple("그대에게 편지를 전달하라고 준 시간이 끝났소. 그리고 그대가 실패한 것으로 보이오.","시간이 다 되었소. 그런데도 아무런 진전이 없구려. 무슨 일인가?");
								link.l1 = "당신의 일을 완수하지 못했습니다, "+GetAddress_FormToNPC(NPChar)+".";
								link.l1.go = "All_Late";	
							}
							else
							{
								dialog.text = LinkRandPhrase("나에게 편지를 전달하는 임무는 이미 너에게 주어졌소. 이제 그 임무를 완수하시오!","당신은 이미 나에게 직접 편지를 전달하는 임무를 맡았소! 나는 그 결과를 기다리고 있소, 그 편지가 최대한 빨리 필요하오!","그대가 내 관저에서 시간을 허비하고 있는 동안, 내가 절실히 필요한 정보는 아직도 나에게 보내기로 한 자의 손에 있소! 즉시 그대에게 맡긴 임무를 수행하시오!");
								link.l1 = RandPhraseSimple("좋아, "+GetAddress_FormToNPC(NPChar)+".","바로 시작하겠습니다, "+GetAddress_FormToNPC(NPChar)+".");
								link.l1.go = "exit";	
							}
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("내가 기다리던 편지를 전달했소?","지금 말해라 – 가지고 있나?!");
							link.l1 = "네, 그렇습니다. 약속한 대로 직접 나리께 전달했습니다.";
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
			else
			{
				if(sti(pchar.reputation.nobility) > 41) {dialog.text = "저는 제게 맡겨진 땅에서 무법을 막기 위해 모든 힘을 다하고 있소. 그리고 그대처럼 명예로운 선장들을 위한 임무도 항상 준비되어 있지. 어떤 임무를 맡고 싶은가?";}
				else {dialog.text = "나는 내 권한 아래 있는 땅의 질서를 유지하기 위해 온 힘을 다하고 있소, 그리고 그대처럼 명성이 자자한 자에게도 맡길 일이 있소. 어떤 임무에 그대의 재능을 발휘하고 싶은가?";}
				link.l1 = "식민지와 그 주변 지역의 내부 문제에 집중하고 싶소.";
				link.l1.go = "GovQuestGroup1";
				link.l2 = "저는 나리의 영지 밖에서 이루어지는 작전에 참여하는 것을 더 선호합니다.";
				link.l2.go = "GovQuestGroup2";
				link.l3 = "저는 국제 관계에 영향을 미치고 \n위치를 강화할 수 있는 고위험 임무에 관심이 있습니다 "+ NationNameGenitive(sti(NPChar.nation))+".";
				link.l3.go = "GovQuestGroup3";
				link.l4 = "죄송하오 — 지금은 아무런 약속도 하고 싶지 않소.";
				link.l4.go = "exit";
			}
			break;
			
			case "GovQuestGroup1":
			// Группа 1 - Местные
			if (CheckAttribute(npchar, "work_date") && GetNpcQuestPastDayParam(npchar, "work_date") <= 1)
			{
				dialog.text = RandPhraseSimple("오늘은 너에게 이런 일거리가 없네. 내일 다시 와 보게나...", 
						"유감스럽게도 지금은 이런 종류의 임무가 없소. 하루 이틀 뒤에 다시 와 보시오.", 
						"오늘은 그런 부탁을 드릴 수 없겠소. 다음에 다시 뵙게 되면 기쁘겠소.");
				link.l1 = "알겠습니다. "+GetAddress_FormToNPC(NPChar)+".";
				link.l1.go = "exit";
				break;
			}
			pchar.GenQuest.Governor.Group1.index = hrand(2);
			i = pchar.GenQuest.Governor.Group1.index;
			switch (i)
			{
				case 0: // Отказ
					dialog.text = RandPhraseSimple("오늘은 이런 종류의 일거리가 없소. 내일 다시 와 보시오...", 
							"유감스럽게도 지금은 이런 종류의 임무가 없소. 하루 이틀 뒤에 다시 와 보시오.", 
							"오늘은 그런 부탁을 드릴 수 없겠소. 다음에 다시 뵙게 되면 기쁘겠소.");
					link.l1 = RandPhraseSimple("안타깝군...","아, 참 안타깝군, "+GetAddress_FormToNPC(NPChar)+". ");
					link.l1.go = "exit";
				break;
						
				case 1: // Таможенный патруль
					if (CheckAttribute(pchar, "GenQuest.Governor.Group1.day") && sti(pchar.GenQuest.Governor.Group1.day) == GetDataDay())
					{
						dialog.text = "마음이 바뀌었소, 선장? 밀수꾼들은 여전히 활개치고 있고, 아마도 그들의 계획을 포기하지 않았을 것이오.";
						link.l1 = "이 임무의 세부 사항을 다시 말씀해 주시겠습니까, 각하.";
						link.l1.go = "CustomPatrol";
						link.l2 = RandPhraseSimple("죄송하지만, 지금은 이 임무를 맡을 준비가 되어 있지 않습니다.", 
						"지금은 이 임무를 수행할 수 없을 것 같소.", 
						"죄송하오 — 아직 이 임무를 맡을 준비가 되지 않았소.");
						link.l2.go = "exit";
						break;
					}
					dialog.text = "딱 맞춰 오셨군요, 선장. 우리 식민지로 밀수되는 물품과 관련된 긴급한 문제를 처리해야 하오. 자네 배는 항해에 이상 없고 전투 준비도 되어 있겠지?";
					link.l1 = "내 배는 언제나 바다에 나갈 준비가 되어 있고 전투도 문제없소. 부디, 다가오는 임무에 대해 더 말씀해 주시지요, 나리.";
					link.l1.go = "CustomPatrol";
				break;
						
				case 2: // Уничтожение банды
					if (CheckAttribute(pchar, "GenQuest.Governor.Group1.day") && sti(pchar.GenQuest.Governor.Group1.day) == GetDataDay())
					{
						dialog.text = "결국 산적들을 소탕하는 임무를 맡기로 하셨군요, 선장님? 유감스럽게도 그 자들은 여전히 우리 식민지의 안녕을 위협하고 있소.";
						link.l1 = "이 임무의 세부 사항을 다시 말씀해 주시겠습니까, 각하.";
						link.l1.go = "DestroyGang";
						link.l2 = RandPhraseSimple("죄송하지만, 지금은 이 임무를 맡을 준비가 되어 있지 않습니다.", 
						"지금은 이 임무를 수행할 수 없을 것 같소.", 
						"죄송하오 — 아직 이 임무를 맡을 준비가 되지 않았소.");
						link.l2.go = "exit";
						break;
					}
					pchar.GenQuest.DestroyGang.Terms = hrand(2) + 2;
					pchar.GenQuest.DestroyGang.Money = ((hrand(6)+4)*500)+5000+(sti(pchar.rank)*500);
					makearef(arName, pchar.GenQuest.DestroyGang);
					arName.nation = PIRATE;
					arName.sex = "man";
					SetRandomNameToCharacter(arName);
					dialog.text = "지금 너에게 맡길 임무가 있다. 근처 정글에서\n "+XI_ConvertString("Colony"+npchar.city+"Gen")+" 도적 무리가 나타났는데, 그 두목의 이름이 무엇인지 나는 알고 있소 "+GetFullName(arName)+". 이 깡패 무리를 찾아내어 소탕하시오.";
					link.l1 = "제가 어떤 조건에서 제한을 받는 것입니까?";
					link.l1.go = "DestroyGang";
				break;
			}
		break;

		case "GovQuestGroup2":
			// Группа 2 - За границами острова, но не государственные
			if (CheckAttribute(npchar, "work_date") && GetNpcQuestPastDayParam(npchar, "work_date") <= 1)
			{
				dialog.text = RandPhraseSimple("오늘은 이런 종류의 일거리가 없소. 내일 다시 와보시오...", 
						"유감스럽게도 지금은 이런 종류의 임무가 없소. 하루 이틀 뒤에 다시 와 보시오.", 
						"오늘은 그런 부탁을 드릴 수 없겠소. 다음에 다시 뵙게 되면 기쁘겠소.");
				link.l1 = RandPhraseSimple("안타깝군...","아, 참 안타깝군, "+GetAddress_FormToNPC(NPChar)+". ");
				link.l1.go = "exit";
				break;
			}
			pchar.GenQuest.Governor.Group2.index = hrand(3);
			i = pchar.GenQuest.Governor.Group2.index;
			switch (i)
			{
				case 0: // Нет заданий
					dialog.text = RandPhraseSimple("오늘은 이런 종류의 일거리가 없소. 내일 다시 와보는 게 어떻겠소...", 
							"유감스럽게도 지금은 이런 종류의 임무가 없소. 하루 이틀 뒤에 다시 와 보시오.", 
							"오늘은 그런 부탁을 드릴 수 없소. 다음에 다시 뵙게 되면 기쁘겠소.");
					link.l1 = RandPhraseSimple("안타깝군...","아, 참 안타깝군, "+GetAddress_FormToNPC(NPChar)+". ");
					link.l1.go = "exit";
				break;
						
				case 1:  // ОЗГ - захватить пассажира
					if (CheckAttribute(pchar, "GenQuest.Governor.Group2.day") && sti(pchar.GenQuest.Governor.Group2.day) == GetDataDay())
					{
						dialog.text = "자신을 증명할 기회를 놓치지 않기로 했나? 나는 그 악당이 살아서 잡혀오길 원하네 — 최대한 빨리 말이야.";
						link.l1 = "이 임무의 세부 사항을 다시 말씀해 주십시오, 각하.";
						link.l1.go = "TakePassenger";
						link.l2 = RandPhraseSimple("죄송하지만, 지금은 이 임무를 맡을 준비가 되어 있지 않습니다.", 
						"죄송하지만 지금은 이 임무를 수행할 수 없습니다.", 
						"죄송하오 — 아직 이 임무를 맡을 준비가 되지 않았소.");
						link.l2.go = "exit";
						break;
					}
					dialog.text = "마침 잘 오셨소, 나리. 당신에게 딱 맞는 긴급 임무가 있소. 어떤 인물을 찾아내어 포획하는 일이오...";
					link.l1 = "인간 사냥이라구? 내가 뭘 해야 하는지 좀 더 자세히 말해 줄 수 있나?";
					link.l1.go = "TakePassenger";
				break;
						
				case 2: // Найти дезертира
					if (CheckAttribute(pchar, "GenQuest.Governor.Group2.day") && sti(pchar.GenQuest.Governor.Group2.day) == GetDataDay())
					{
						dialog.text = "마음이 바뀌었소, 선장? 결국 도망자를 쫓기로 했나?";
						link.l1 = "이 임무의 세부 사항을 다시 말씀해 주십시오, 각하.";
						link.l1.go = "FindFugitive";
						link.l2 = RandPhraseSimple("죄송하지만, 지금은 이 임무를 맡을 준비가 되어 있지 않습니다.", 
							"죄송하지만 지금은 이 임무를 수행할 수 없습니다.", 
							"죄송합니다 — 아직 이 임무를 맡을 준비가 되어 있지 않습니다.");
						link.l2.go = "exit";
						break;
					}
					dialog.text = "카리브 해의 여러 정착지를 방문하는 임무가 있소. 긴 여정에 나설 준비가 되었소?";
					link.l1 = "예, 제 부하들과 저는 즉시 출항할 준비가 되어 있습니다. 정확히 무엇을 해야 합니까?";
					link.l1.go = "FindFugitive";
				break;
						
				case 3: // Уничтожить корабль пиратов
					if (CheckAttribute(pchar, "GenQuest.Governor.Group2.day") && sti(pchar.GenQuest.Governor.Group2.day) == GetDataDay())
					{
						dialog.text = "해적이 아직도 상인들을 약탈하고 있소, 선장님. 이번에는 그 자를 처리할 준비가 되었기를 바라오?";
						link.l1 = "이 임무의 세부 사항을 다시 한 번 말씀해 주시겠습니까, 각하.";
						link.l1.go = "TakePirateship";
						link.l2 = RandPhraseSimple("죄송하지만, 지금은 이 임무를 맡을 준비가 되어 있지 않습니다.", 
						"지금은 이 임무를 수행할 수 없을 것 같소.", 
						"죄송하오 — 아직 이 임무를 맡을 준비가 되지 않았소.");
						link.l2.go = "exit";
						break;
					}
					dialog.text = "예, 그대에게 중요한 임무가 있소. 이를 완수하려면 모든 능력을 발휘해야 하오. 해적들이 관련되어 있소...";
					link.l1 = "해적들 말이오? 그렇다면 내게 기대하는 바를 좀 더 자세히 말해 주겠소?";
					link.l1.go = "TakePirateship";
				break;
			}
		break;

		case "GovQuestGroup3":
			// Группа 3 - Государственные разборки, тяжелые бои
			if (CheckAttribute(npchar, "work_date") && GetNpcQuestPastDayParam(npchar, "work_date") <= 1)
			{
				dialog.text = RandPhraseSimple("오늘은 이런 종류의 일거리가 없소. 내일 다시 와보시오...", 
						"유감스럽게도 지금은 이런 종류의 임무가 없소. 하루 이틀 뒤에 다시 와 보시오.", 
						"오늘은 그런 부탁을 드릴 수 없겠소. 다음에 다시 뵙게 되면 기쁘겠소.");
				link.l1 = RandPhraseSimple("안타깝군...","아, 참 안타깝군, "+GetAddress_FormToNPC(NPChar)+". ");
				link.l1.go = "exit";
				break;
			}
			pchar.GenQuest.Governor.Group3.index = hrand(3);
			i = pchar.GenQuest.Governor.Group3.index;
			switch (i)
			{
				case 0: // Отказ
					dialog.text = RandPhraseSimple("오늘은 너에게 이런 일거리가 없네. 내일쯤 다시 와 보게나...", 
							"유감스럽게도 지금은 이런 종류의 임무가 없소. 하루 이틀 뒤에 다시 와 보시오.", 
							"오늘은 그런 부탁을 드릴 수 없겠소. 다음에 다시 뵙게 되면 기쁘겠소.");
					link.l1 = RandPhraseSimple("안타깝군...","아, 참 안타깝군, "+GetAddress_FormToNPC(NPChar)+". ");
					link.l1.go = "exit";
				break;
						
				case 1: // Контркурьер
					if (CheckAttribute(pchar, "GenQuest.Governor.Group3.day") && pchar.GenQuest.Governor.Group3.day == GetDataDay())
					{
						dialog.text = "시간이 얼마 남지 않았어. 할 건가, 아니면 또 수다 떨러 온 거냐?";
						link.l1 = "이 임무의 세부 사항을 다시 말씀해 주십시오, 각하.";
						link.l1.go = "TakePostcureer";
						link.l2 = RandPhraseSimple("죄송하지만, 지금은 이 임무를 맡을 준비가 되어 있지 않습니다.", 
						"죄송하지만 지금은 이 임무를 수행할 수 없소.", 
						"죄송하오 — 아직 이 임무를 맡을 준비가 되지 않았소.");
						link.l2.go = "exit";
						break;
					}
					dialog.text = "그래, 자네에게 맡길 임무가 있네. 그 임무를 완수하려면 민첩함과 해상 전투 실력 모두를 보여주어야 하네. 자네의 가치를 증명할 준비가 되었는가?";
					link.l1 = "각하, 임무에 대해 좀 더 자세히 말씀해 주시겠습니까?";
					link.l1.go = "TakePostcureer";
				break;
						
				case 2: // Контрфрахт - уничтожить корабль с арсеналом
					if (CheckAttribute(pchar, "GenQuest.Governor.Group3.day") && pchar.GenQuest.Governor.Group3.day == GetDataDay())
					{
						dialog.text = "그래, 마침내 용기를 냈군, 선장? 이제 적의 보급품을 공격할 준비가 되었나?";
						link.l1 = "이 임무의 세부 사항을 다시 말씀해 주시겠습니까, 각하.";
						link.l1.go = "TakeArsenalship";
						link.l2 = RandPhraseSimple("죄송하지만, 지금은 이 임무를 맡을 준비가 되어 있지 않습니다.", 
						"지금은 이 임무를 수행할 수 없을 것 같소.", 
						"죄송하오 — 아직 이 임무를 맡을 준비가 되지 않았소.");
						link.l2.go = "exit";
						break;
					}
					dialog.text = "그래, 자네에게 맡길 임무가 있네. 이 임무를 완수하려면 뛰어난 용맹함과 해상 전투 실력도 보여야 하네. 자네의 가치를 증명할 준비가 되었는가?";
					link.l1 = "각하, 곧 있을 임무에 대해 더 자세히 말씀해 주실 수 있습니까?";
					link.l1.go = "TakeArsenalship";;
				break;
						
				case 3: // Проникновение во враждебный город
					if (CheckAttribute(pchar, "GenQuest.Governor.Group3.day") && pchar.GenQuest.Governor.Group3.day == GetDataDay())
					{
						dialog.text = "이 임무에 대해서는 이미 문의하셨소, 선장님. 이번에는 단순한 호기심만은 아니길 바라오.";
						link.l1 = "이 임무의 세부 사항을 다시 말씀해 주십시오, 각하.";
						link.l1.go = "Intelligence";
						link.l2 = RandPhraseSimple("죄송하지만, 지금은 이 임무를 맡을 준비가 되어 있지 않습니다.", 
						"지금은 이 임무를 수행할 수 없을 것 같소.", 
						"죄송합니다 — 아직 이 임무를 맡을 준비가 되지 않았습니다.");
						link.l2.go = "exit";
						break;
					}
					sTemp = GetSpyColony(npchar);
					if (sTemp == "none")
					{
						dialog.text = RandPhraseSimple("오늘은 이런 일거리가 없소. 내일 다시 와보는 게 어떻겠소...", 
								"유감스럽게도 지금은 이런 종류의 임무가 없소. 하루 이틀 뒤에 다시 와 보시오.", 
								"오늘은 그런 부탁을 드릴 수 없겠소. 다음에 다시 뵙게 되면 기쁘겠소.");
						link.l1 = "알겠습니다. "+GetAddress_FormToNPC(NPChar)+".";
						link.l1.go = "exit";
						break;
					}
					pchar.GenQuest.Intelligence.Terms = hrand(10) + (42 - MOD_SKILL_ENEMY_RATE);
					pchar.GenQuest.Intelligence.Money = ((hrand(5)+11)*2000)+(sti(pchar.rank)*1500);
					pchar.GenQuest.Intelligence.City = sTemp;
					sTemp = ", which is on " + XI_ConvertString(GetIslandByColony(&colonies[FindColony(pchar.GenQuest.Intelligence.City)])+"Dat");
					dialog.text = "당신에게 맡길 임무가 있소, 상당한 위험이 따르오. 몰래 잠입해 주길 바라오\n "+XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Acc")+sTemp+", 그곳에서 어떤 사람을 만나 그가 건네주는 것을 나에게 가져오시오.";
					link.l1 = "음, 나는 그 안에서 그렇게 생각하지 않아 "+XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Dat")+" 환영받는 손님이 되겠지...";
					link.l1.go = "Intelligence";
				break;
			}
		break;
		//---------------------------- генератор квестов мэра -------------------------------

		case "sell_prisoner":
            dialog.text = "누구를 몸값으로 풀어주고 싶으십니까?";

            qty = 1;
            for(i=0; i < GetPassengersQuantity(pchar); i++)
            {
                cn = GetPassenger(pchar,i);
                if(cn != -1)
                {
                    offref = GetCharacter(cn);
                    if(CheckAttribute(offref,"prisoned"))
                    {
        	            if(sti(offref.prisoned)==true && GetRemovable(offref)) // ставим только фантомов
        	            {
                            attrLoc = "l"+qty;
                            link.(attrLoc)    = GetFullName(offref) + " - " + NationNameMan(sti(offref.nation)) + ".";
                            link.(attrLoc).go = "GetPrisonerIdx_" + offref.index;
                            qty++;
                        }
                    }
                }
            }
			link.l99 = "아무도 아니다.";
			link.l99.go = "exit";
		break;
		
		case "sell_prisoner_2":
            offref = GetCharacter(sti(pchar.GenQuest.GetPrisonerIdx));
            attrLoc =  "So, this is captain " + GetFullName(offref) + ", " + NationNameMan(sti(offref.nation))+ ".";
            // цена зависит от губернатора
            qty = makeint(sti(offref.rank)*(800 + GetCharacterSPECIALSimple(NPChar, SPECIAL_L)*100) + GetCharacterSkillToOld(offref, "Leadership")*500 + GetCharacterSkillToOld(pchar, "commerce")*500);
			if(HasShipTrait(pchar, "trait14")) qty = makeint(qty * 1.35);
            if (sti(offref.nation) == sti(NPChar.nation))
            {
                attrLoc = attrLoc + " I am ready to pay the ransom for my compatriot in the amount of  " + FindRussianMoneyString(qty) + ".";
            }
            else
            {
                if (sti(offref.nation) == PIRATE)
                {
                    qty = qty / 5;
                    attrLoc = attrLoc + " I can give " + FindRussianMoneyString(qty) + "  for this gallowsbird. And then we'll execute the scoundrel at once.";

                }
                else
                {
                    qty = qty / 2;
                    attrLoc = attrLoc + " " + FindRussianMoneyString(qty) + "for that man, not a peso more.";
                }
            }
			dialog.text = attrLoc;
			pchar.PrisonerSellPrice =  qty;
			link.l1 = "좋아. 이제 그자는 네 거다, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "sell_prisoner_3";
			link.l3 = "아니오. 그렇게는 안 되오.";
			link.l3.go = "exit";
		break;


		case "sell_prisoner_3":
			dialog.text = "좋군.";
			link.l1 = "행운을 빕니다.";
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
        	ReleasePrisoner(offref); // освободили пленника
		break;
		////   CAPTURE //////////
		case "CAPTURE_Main":
            NextDiag.TempNode = "CAPTURE_Main";
			AfterTownBattle();  // всё, все свободны
			
			// --> Левассер
			if (pchar.location == "Tortuga_townhall" && CheckAttribute(pchar, "questTemp.Sharlie.Hardcore_Tortuga"))
			{
                dialog.Text = "이런 젠장! 이게 무슨 망신이오, 드 모르 나리? 프랑스인들이 언제부터 자기 동포를 공격했단 말이오?!";
                Link.l1 = "총독 프랑수아 롱빌리에 드 푸앵시의 명령에 따라, 르바쇠르 나리, 그대는 토르투가 총독직에서 해임되고 사형을 선고받았소! 그리고 이 형을 집행할 이는 바로 나요!";
                Link.l1.go = "levasser";
				break;
			}
			// <-- Левассер
            // fix от грабежа 5 раз на дню -->
            if (!CheckNPCQuestDate(npchar, "GrabbingTownDate"))
			{
                dialog.Text = "이미 다 가져갔잖소. 더 뭘 바라는 것이오?";
                Link.l1 = "그래, 맞아, 도시가 잘못됐군.";
                Link.l1.go = "Exit_City";

                NPChar.NoGiveMoney = true;

            	ChangeCharacterHunterScore(GetMainCharacter(), NationShortName(sti(NPChar.nation)) + "hunter", 20);
                // вернём диалог после разговора и спрячем
                SetReturn_Gover_Dialog_Exit(NPChar);
				break;
			}
			SetNPCQuestDate(npchar, "GrabbingTownDate");
			// fix от грабежа 5 раз на дню <--

            if (CheckAttribute(FortChref, "Fort.Mode") && sti(FortChref.Fort.Mode) != FORT_DEAD)
            { // а форт-то ЖИВ, значит с суши прошли
                dialog.Text = "전례 없는 무례함이로군! 곧 요새에서 증원군이 도착할 것이니, 네놈 반드시 대가를 치르게 될 것이다!";
                Link.l2 = "나는 그들이 올 때까지 여기 머물 생각 없어. 그냥 돈이나 주면, 이 마을을 떠나겠어.";
                Link.l2.go = "Summ";
                Pchar.HalfOfPaymentByCity = true; // токо половина денег
            }
            else
            {
				dialog.Text = "이번에는 네가 이겼지만, 우리 해적 사냥꾼 함대가 널 끝까지 쫓아가 더러운 해적놈의 몸에서 페소 한 푼까지 다 뜯어낼 줄 알아라!";
	            if (!bWorldAlivePause || bBettaTestMode)
	            {
	                int iColony = FindColony(npchar.city);
					if (!CheckAttribute(&colonies[iColony], "notCaptured")) //незахватываемые города
					{
						if (CheckAttribute(FortChref, "Default.Prison"))
	    				{
	    					Link.l1 = "조용히 해라! 이제부터 이 도시는 내 거다. 네놈들 해적 사냥꾼들은 데이비 존스의 바다로 보내주지. 이봐, 녀석들아, 저 돼지 좀 잡아서 감옥에 쳐넣어라.";
	    				}
	    				else
	    				{
	    					Link.l1 = "이제 이 도시는 내 거다. 얘들아, 전임 총독을 새 '숙소'로 모셔다 드려라, 크크.";
	    				}
	    				Link.l1.go = "City";
					}
				}
				if (!isCityHasFort(NPChar.City))
	            {
	                Link.l2 = "요새에서 지원군이 온다고? 나한테 넉넉한 몸값만 주면, 우리가 네 도시에서 떠나주지.";
				}
				else
				{
	            	Link.l2 = "해적 사냥꾼 함대라고? 흠... 돈만 주면 우리가 네 도시를 떠나주지.";
	            }
				Link.l2.go = "Summ";

                bOk = !bWorldAlivePause || bBettaTestMode;
	            if (isMainCharacterPatented() && bOk && !CheckAttribute(&colonies[iColony], "notCaptured")) //не даем захватить колонию
	            {
					// восстановим нацию патента
					PChar.nation = GetBaseHeroNation();
					
					dialog.Text = "전례 없는 무례함이로다! 감히 누구의 식민지를 공격하다니! "+NationNameGenitive(sti(NPChar.nation))+"?! 그대가 흘린 피와 우리 국가에 입힌 피해에 대해 값비싼 대가를 치르게 될 것이오.";
	                Link.l1 = "지금부터 이 식민지는 내 것이다. 내 권위에 도전하는 자는 곧장 지옥으로 가게 될 것이다.";
	                Link.l1.go = "City_patent";
	                Link.l2 = "물러서라. 나는 ~의 이름으로 행동하고 있다 "+NationNameGenitive(sti(PChar.nation))+". 이제부터 이 식민지는 "+NationKingsCrown(PChar)+"!";
	                Link.l2.go = "City_nation";
	                Link.l3 = "참 멋진 마을이군. 만약 이곳이 잿더미가 되고, 이 마을의 총독이 광장에 매달린다면 정말 비극이겠지. 그런 비극을 막기 위해 얼마만큼의 몸값을 지불할 생각인지 논의해보자고. ";
	                Link.l3.go = "Summ_patent";
	            }
            }
        break;
		
		// --> Левассер
		case "levasser":
            dialog.Text = "포인시?! 젠장, 저 가톨릭 자식! 내가 직접 처리하겠다... 그리고 너, 이 악당아, 이제 끝장이야! 여기서 살아나가지 못할 거다 – 내가 직접 네 목숨을 거둬주지!";
			Link.l1 = "설교는 집어치워라, 이단자 놈. 네 위그노 영혼을 지옥으로 보내면, 루시퍼와 장 칼뱅에게 내 안부나 전해라. 각오해라!";
			Link.l1.go = "levasser_1";
        break;
		
		case "levasser_1":
			chrDisableReloadToLocation = true;//закрыть локацию
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
		// <-- Левассер
        
        case "City":
            ChangeCharacterHunterScore(GetMainCharacter(), NationShortName(sti(NPChar.nation)) + "hunter", 40);
            AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 400);

            Pchar.GenQuestFort.fortCharacterIdx = FortChref.index;
            AddDialogExitQuest("Residence_Captured_Any");

            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_TakeTown", 1);
            // ремонт
            RepairAllShips();
            Log_Info("All ships have been repaired.");
            //  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
	        AddQuestRecordInfo("Gen_CityCapture", "t3");
			AddQuestUserData("Gen_CityCapture", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + NPChar.City));
			//  СЖ <--
            NextDiag.CurrentNode = "Prison";
			DialogExit();
        break;

        case "City_patent":
            ChangeCharacterComplexReputation(GetMainCharacter(),"nobility", -20); // пираты мы, но у нас патент
            dialog.Text = "이번에는 네가 이겼지만, 우리 함대가 곧 도착해서 너희를 모조리 쓸어버릴 줄 알아라!";
			Link.l1 = "입 닥쳐라. 이제부터 이 도시는 내 거다. 네 함대는 곧바로 지옥으로 보내주지. 얘들아, 전임 총독을 새 '숙소'로 모셔라, 크크.";
			Link.l1.go = "City";
        break;

        case "Exit_for_pay":
			dialog.Text = "저에게 또 무엇을 원하십니까?";
            Link.l1 = "혹시 내가 뭔가 빠뜨린 게 있나 확인하는 중이야...";
            Link.l1.go = "exit";

            NextDiag.TempNode = "Exit_for_pay";
		break;

        case "Exit_City":
		    NextDiag.CurrentNode = "Exit_for_pay";
		    Pchar.GenQuestFort.fortCharacterIdx = FortChref.index;
		    if (sti(NPChar.NoGiveMoney) == false) // себе берем
		    {
				// вернём диалог после разговора и спрячем
				SetReturn_Gover_Dialog_Exit(NPChar);
				AddDialogExitQuestFunction("TWN_ExitForPay");
            }
            DialogExit();
        break;

        case "Summ":
            dialog.Text = "당신의 조건에 동의할 수밖에 없소. 이 피 묻은 돈을 가져가고 당장 우리 식민지에서 떠나시오.";
            Link.l1 = "당신과 거래하게 되어 기쁩니다.";
            Link.l1.go = "Exit_City";
            NPChar.NoGiveMoney = false;

            ChangeCharacterHunterScore(GetMainCharacter(), NationShortName(sti(NPChar.nation)) + "hunter", 30);
            AddCharacterExpToSkill(GetMainCharacter(), SKILL_FORTUNE, 300);
            AddCharacterExpToSkill(GetMainCharacter(), "Commerce", 300);

            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_GrabbingTown", 1);
            //  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
	        AddQuestRecordInfo("Gen_CityCapture", "t2");
			AddQuestUserData("Gen_CityCapture", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + NPChar.City));
			//  СЖ <--
        break;

        case "Summ_patent":
            dialog.Text = "좋소, 조건을 말해보시오...";
            Link.l1 = "아이, 패자에게 화가 있으라! 이제 돈이나 세어 보시지.";
            Link.l1.go = "Summ";
            ChangeCharacterComplexReputation(GetMainCharacter(),"nobility", -10); // не на службе
        break;

        case "City_nation":
			dialog.Text = "알겠다, 너의 자비에 항복하겠다.";
			Link.l1 = "가능한 한 빨리 이 도시를 떠나시길 권하오 - 곧 닥칠 변화가 당신 건강에 매우 해로울 수 있소. 안녕히 가시오.";
			Link.l1.go = "Exit_City";
			NPChar.NoGiveMoney = true;

            ChangeCharacterComplexReputation(GetMainCharacter(),"nobility", 5);
            AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 600);
            AddCharacterExpToSkill(GetMainCharacter(), "Sneak", 400);
            SetNationRelationBoth(sti(PChar.nation), sti(NPChar.nation), RELATION_ENEMY);

            PChar.questTemp.DontSetNewDialogToMayor = true; // иначе может сменить диалог и сбойнуть
            PChar.questTemp.DontNullDeposit = true;    // чтоб не нулили ростовщика
            SetCaptureTownByNation(NPChar.City, sti(PChar.nation));
            DeleteAttribute(PChar, "questTemp.DontSetNewDialogToMayor");
            AddDialogExitQuestFunction("LaunchColonyInfoScreen"); // табличка
            //  СЖ -->
	    	sTemp =  GetNationNameByType(sti(PChar.nation));
			ReOpenQuestHeader("Gen_CityCapture");
	        AddQuestRecordInfo("Gen_CityCapture", "t1");
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + NPChar.City));
			AddQuestUserData("Gen_CityCapture", "sNation", XI_ConvertString(sTemp + "Gen"));
			//  СЖ <--
			AddTitleNextRate(sti(PChar.nation), 1);  // счетчик звания
            SetCharacterRelationBoth(sti(FortChref.index), GetMainCharacterIndex(), RELATION_FRIEND);// нечего не даёт, тк работает OtherChar - а это губер, но он и так друг
            UpdateRelations();

            // 22.03.05  fix вернём диалог после разговора и спрячем
            //  внутри диалога не работало
            SetReturn_Gover_Dialog_Exit(NPChar);

            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_TakeTown", 1);
	    break;
	    
	    case "Prison":
			dialog.Text = "나한테 또 뭘 원하냐, 이 악당아?";
            Link.l3 = "각하께서는 새 방이 마음에 드십니까? 충분히 넓은지요? 그럼, 이제 저는 물러가겠습니다!";
            Link.l3.go = "exit";
            NextDiag.TempNode = "Prison";
		break;
		
		case "arestFree_1":
			dialog.text = "정착하라고? 그게 어떻게 가능하다고 생각하는 거지?";
            link.l1 = "내 생각에는 "+iTotalTemp*6000+" 페소만 있으면 아직도 내가 구원받을 수 있지, 안 그래?";
			link.l1.go = "arestFree_2";
			link.l2 = "아니. 이제 나는 가봐야겠군. 안녕히 계십시오.";
			link.l2.go = "arest_1";
		break;

		case "arestFree_2":
            if (GetCharacterSkillToOld(PChar, SKILL_FORTUNE) >= hrand(7) && iTotalTemp < 21)
            {
    			dialog.text = "이런 방식으로 우리 사건을 해결할 수도 있겠군. 아직 사태를 돌이킬 수 없을 만큼 망쳐 놓지는 않았으니.";
    		    link.l1 = "훌륭하오. 매우 기쁘오. 부디, 내 기부금을 받아주시오.";
    		    link.l1.go = "Exit";
    		    AddMoneyToCharacter(pchar, -iTotalTemp*6000);
    		    ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", -iTotalTemp);
    		    AddCharacterExpToSkill(pchar, "Fortune", 100);
            }
            else
            {
    			dialog.text = "나에게 뇌물을 주려는 건가? 이런! 네 악행은 오직 한 가지 방법으로만 속죄할 수 있지... 경비병들! 잡아라\n "+GetSexPhrase("그를","그녀")+" 족쇄에 묶어라!";
    		    link.l1 = "잠깐만!";
    		    link.l1.go = "arest_2";
    		    AddCharacterExpToSkill(pchar, "Fortune", 10);
            }
		break;

		case "arest_1":
			dialog.text = "물론이지, 때가 되었군. 우리가 배웅하겠소. 경비병들! 붙잡아라\n "+GetSexPhrase("그를","그녀")+"!";
		    link.l1 = "말도 안 돼!";
		    link.l1.go = "fight";
		break;

		case "arest_2":
			dialog.text = "생각할 시간은 충분히 줬다! 경비병들!";
			link.l1 = "날 쉽게 잡을 수는 없을 거다!";
		    link.l1.go = "fight";
		break;    
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Уничтожение банды
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "DestroyGang":
			pchar.GenQuest.Governor.Group1.day = GetDataDay();
			dialog.text = "물론이오. 이 임무를 완수하기 위해 내가 그대에게 주는 것은 "+FindRussianDaysString(sti(pchar.GenQuest.DestroyGang.Terms))+", 그리고 성공한다면 받을 보상은 "+FindRussianMoneyString(sti(pchar.GenQuest.DestroyGang.Money))+".";
			link.l1 = "예, 이 임무를 받아들이겠소.";
		    link.l1.go = "DestroyGang_agree";
			link.l2 = "흠... 아니, 나는 사양하겠소.";
		    link.l2.go = "All_disagree";
		break;
		case "DestroyGang_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.questName = "DestroyGang"; //тип квеста
			pchar.GenQuest.DestroyGang.Location = GetGangLocation(npchar); //определяем локацию,где банда
			pchar.GenQuest.DestroyGang.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			if (pchar.GenQuest.DestroyGang.Location == "none") //на всякий случай
			{
				dialog.text = "잠깐, 어제 보고가 생각났소. 요점은 이 무리가 이미 우리 섬을 떠났다는 것이오. 그러니 임무를 취소해야겠소.";
				link.l1 = "알겠소. 안타깝군.";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "GenQuest." + pchar.GenQuest.questName);
				DeleteAttribute(pchar, "GenQuest.questName");
			}
			else
			{
				dialog.text = "좋소, 아주 훌륭하군! 자네와 자네의 보고를 저택에서 기다리겠네.";
				link.l1 = "오래 기다리게 하지 않겠소, "+GetAddress_FormToNPC(NPChar)+".";
				link.l1.go = "exit";
				pchar.quest.DestroyGang.win_condition.l1 = "location";
				pchar.quest.DestroyGang.win_condition.l1.location = pchar.GenQuest.DestroyGang.Location;
				pchar.quest.DestroyGang.win_condition = "DestroyGang_fight";
				pchar.quest.DestroyGang.again = true; //тупо дожидаться своего часа бандиты не будут
				SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.DestroyGang.Terms), false);
				//==> энкаунтеров в квестовой локации не будет 
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
		//	Контркурьер
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "TakePostcureer":
			//установка параметров
			pchar.GenQuest.questName = "TakePostcureer"; //тип квеста
			// belamour legendary edition враждебную нацию квестодателя, а не героя -->
			pchar.GenQuest.TakePostcureer.Nation = FindEnemyNation2Character(sti(npchar.index)); //вражеская нация
			iTemp = 1;
			while (iTemp < 10 && sti(pchar.GenQuest.TakePostcureer.Nation) == PIRATE) {
				pchar.GenQuest.TakePostcureer.Nation = FindEnemyNation2Character(sti(npchar.index));
				iTemp += 1;
			}
			if (iTemp == 10 && sti(pchar.GenQuest.TakePostcureer.Nation) == PIRATE) {
				dialog.text = LinkRandPhrase("오늘은 당신께 드릴 일이 없소.","오늘은 더 이상 맡길 일이 없소.","오늘은 더 이상 줄 일이 없소, 미안하오. 내일 다시 오면, 그때 보도록 하지...");
				link.l1 = RandPhraseSimple("안타깝군...","아, 안타깝구나, "+GetAddress_FormToNPC(NPChar)+". ");
        		link.l1.go = "exit";
				
				if (CheckAttribute(pchar, "GenQuest.questName")) {
					QuestName = pchar.GenQuest.questName;
					DeleteAttribute(pchar, "GenQuest." + QuestName);
					DeleteAttribute(pchar, "GenQuest.questName");
				}
				
				break;
			}
			pchar.GenQuest.TakePostcureer.City = FindQuestCity(npchar, "enemy",sti(pchar.GenQuest.TakePostcureer.Nation), false, false);
			// <-- legendary edition
			pchar.GenQuest.TakePostcureer.Island = GetArealByCityName(pchar.GenQuest.TakePostcureer.City);
			pchar.GenQuest.TakePostcureer.Terms = GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(PChar)].id, pchar.GenQuest.TakePostcureer.Island)+5;
			pchar.GenQuest.TakePostcureer.LoginDay = sti(pchar.GenQuest.TakePostcureer.Terms)-1;
			pchar.GenQuest.TakePostcureer.ShipType = SelectCureerShipType();
			pchar.GenQuest.TakePostcureer.ShipName = GenerateRandomNameToShip(sti(pchar.GenQuest.TakePostcureer.Nation));
			pchar.GenQuest.TakePostcureer.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.TakePostcureer.ShipType));
			pchar.GenQuest.TakePostcureer.Money = ((hrand(5)+hrand(6, "1")+42)*600)+(sti(pchar.rank)*1600);
			pchar.GenQuest.Governor.Group3.day = GetDataDay();
			dialog.text = "물론이오. 당신은 다음의 연락선 위치를 찾아야 하오\n "+NationNameGenitive(sti(pchar.GenQuest.TakePostcureer.Nation))+" '라는 이름의"+pchar.GenQuest.TakePostcureer.ShipName+"', 그 배에 올라타서 선장 선실에서 찾을 수 있을 서류들을 가져오시오. 이 선박은 곧 근처를 지나갈 것이오' "+XI_ConvertString("Colony"+pchar.GenQuest.TakePostcureer.City+"Gen")+" 대략 "+FindRussianDaysString(pchar.GenQuest.TakePostcureer.Terms)+".";
			link.l1 = "좋습니다, 이 임무를 받아들이겠습니다. 그런데 어떤 서류를 찾아야 합니까?";
		    link.l1.go = "TakePostcureer_agree";
			link.l2 = "흠... 아니, 나는 사양하겠소.";
		    link.l2.go = "All_disagree";
		break;
		
		case "TakePostcureer_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.TakePostcureer.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = "우편이군. 내게 아주 중요한 서류들이 있네. 하지만 자네가 문서들을 일일이 뒤질 필요는 없네, 그냥 전체 꾸러미를 나에게 가져오게. 보수는 주겠네\n "+FindRussianMoneyString(sti(pchar.GenQuest.TakePostcureer.Money))+"\n그러면 나는 당신과 당신의 성과를 내 관저에서 기다리겠소.";
			link.l1 = "오래 기다리게 하지 않겠소, "+GetAddress_FormToNPC(NPChar)+".";
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
		//	Контрфрахт - уничтожить корабль с арсеналом
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "TakeArsenalship":
			//установка параметров
			pchar.GenQuest.questName = "TakeArsenalship"; //тип квеста
			// belamour legendary edition враждебную нацию квестодателя, а не героя -->
			pchar.GenQuest.TakeArsenalship.Nation = FindEnemyNation2Character(sti(npchar.index));
			iTemp = 1;
			while (iTemp < 10 && sti(pchar.GenQuest.TakeArsenalship.Nation) == PIRATE) {
				pchar.GenQuest.TakeArsenalship.Nation = FindEnemyNation2Character(sti(npchar.index));
				iTemp += 1;
			}
			if (iTemp == 10 && sti(pchar.GenQuest.TakeArsenalship.Nation) == PIRATE) {
				dialog.text = LinkRandPhrase("오늘은 당신께 드릴 일이 없소.","오늘은 더 이상 맡길 일이 없소.","오늘은 더 이상 일이 없소, 미안하오. 내일 다시 오면, 그때 보도록 하지...");
				link.l1 = RandPhraseSimple("안타깝군...","아, 참 안타깝군, "+GetAddress_FormToNPC(NPChar)+". ");
        		link.l1.go = "exit";
				
				if (CheckAttribute(pchar, "GenQuest.questName")) {
					QuestName = pchar.GenQuest.questName;
					DeleteAttribute(pchar, "GenQuest." + QuestName);
					DeleteAttribute(pchar, "GenQuest.questName");
				}
				
				break;
			}
			pchar.GenQuest.TakeArsenalship.City = FindQuestCity(npchar, "enemy",sti(pchar.GenQuest.TakeArsenalship.Nation), false, false);
			// <-- legendary edition
			pchar.GenQuest.TakeArsenalship.Island = GetArealByCityName(pchar.GenQuest.TakeArsenalship.City);
			pchar.GenQuest.TakeArsenalship.Terms = GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(PChar)].id, pchar.GenQuest.TakeArsenalship.Island)+5;
			pchar.GenQuest.TakeArsenalship.LoginDay = sti(pchar.GenQuest.TakeArsenalship.Terms)-1;
			pchar.GenQuest.TakeArsenalship.ShipType = SelectArsenalShipType(FLAG_SHIP_TYPE_RAIDER);
			pchar.GenQuest.TakeArsenalship.ShipTypeA = SelectArsenalShipType(FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_UNIVERSAL);
			pchar.GenQuest.TakeArsenalship.ShipName = GenerateRandomNameToShip(sti(pchar.GenQuest.TakeArsenalship.Nation));
			pchar.GenQuest.TakeArsenalship.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.TakeArsenalship.ShipType));
			pchar.GenQuest.TakeArsenalship.CannonA = SelectLevelCannonParameter(sti(pchar.GenQuest.TakeArsenalship.ShipTypeA)); // Addon 2016-1 Jason пиратская линейка
			pchar.GenQuest.TakeArsenalship.Money = ((hrand(5)+hrand(6, "1")+36)*700)+(sti(pchar.rank)*1600);
			pchar.GenQuest.Governor.Group3.day = GetDataDay();
			dialog.text = "물론이오. 군사 수송선을 찾아야 하오 "+NationNameGenitive(sti(pchar.GenQuest.TakeArsenalship.Nation))+", 화약과 탄약을 실은 채; 배의 이름은 '"+pchar.GenQuest.TakeArsenalship.ShipName+", 찾아서 파괴하시오. 그렇게 하면 적을 약화시킬 수 있소\n수송선은 호위와 함께 식민지로 항해할 것이오 "+XI_ConvertString("Colony"+pchar.GenQuest.TakeArsenalship.City)+", 그리고 대략 이곳에 있을 것이오 "+FindRussianDaysString(pchar.GenQuest.TakeArsenalship.Terms)+", 그러니 서두르십시오.";
			link.l1 = "좋소, 받아들이겠소. 무기고 함선을 침몰시켜야 하오, 아니면 나포를 시도해야 하오?";
		    link.l1.go = "TakeArsenalship_agree";
			link.l2 = "흠... 아니, 나는 사양하겠소.";
		    link.l2.go = "All_disagree";
		break;
		
		case "TakeArsenalship_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.TakeArsenalship.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = "나는 상관없네, 그건 자네에게 달렸지. 중요한 건 이 화물이 목적지에 도착해서는 안 된다는 것이네. 자네가 성공하면 보수를 주겠네 "+FindRussianMoneyString(sti(pchar.GenQuest.TakeArsenalship.Money))+"... 더 이상 붙잡지 않겠소, 선장.";
			link.l1 = "오래 기다리게 하지 않겠소, "+GetAddress_FormToNPC(NPChar)+".";
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
		//	ОЗГ - уничтожить корабль пиратов
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "TakePirateship":
			//установка параметров
			pchar.GenQuest.questName = "TakePirateship"; //тип квеста
			pchar.GenQuest.TakePirateship.City = FindQuestCity(npchar, "all", -1, true, true); // belamour legendary edition 
			pchar.GenQuest.TakePirateship.Island = GetArealByCityName(pchar.GenQuest.TakePirateship.City);
			pchar.GenQuest.TakePirateship.Terms = GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(PChar)].id, pchar.GenQuest.TakePirateship.Island)+5;
			pchar.GenQuest.TakePirateship.ShipType = SelectPirateShipType();
			pchar.GenQuest.TakePirateship.ShipName = GenerateRandomNameToShip(PIRATE);
			pchar.GenQuest.TakePirateship.Name = GenerateRandomName(PIRATE, "man");
			pchar.GenQuest.TakePirateship.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.TakePirateship.ShipType));
			pchar.GenQuest.TakePirateship.Money = ((hrand(5) + hrand(6, "1")+4)*800)+13000+(sti(pchar.rank)*1250);
			pchar.GenQuest.Governor.Group2.day = GetDataDay();
			dialog.text = "물론이오. 나는 어떤 해적 선장의 행동에 정말 분노하고 있소, 그 이름은 "+pchar.GenQuest.TakePirateship.Name+". 그 악당이 우리 상선들을 습격해서 식민지들 간의 무역에 엄청난 피해를 주고 있소. 지금이야말로 저 자식을 없앨 절호의 기회요. 마침 내가 그놈이 어디에 숨어 있는지 알고 있거든. 이 잡놈을 신의 심판대에 보낼 준비가 되었소?";
			link.l1 = "영광이오! 그 해적은 어디에서 찾을 수 있소?";
		    link.l1.go = "TakePirateship_agree";
			link.l2 = "흠... 아니, 나는 사양하겠소.";
		    link.l2.go = "All_disagree";
		break;
		
		case "TakePirateship_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.TakePirateship.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = "가장 가까운 "+FindRussianDaysString(pchar.GenQuest.TakePirateship.Terms)+" 그의 배 이름은 '"+pchar.GenQuest.TakePirateship.ShipName+"'는 근처 해안가를 따라 순찰할 것이오 "+XI_ConvertString("Colony"+pchar.GenQuest.TakePirateship.City+"Gen")+". 그를 찾아서 죽이시오. 그놈을 배와 함께 물고기 밥으로 보내든, 배를 나포하든, 나는 상관하지 않소. 내게 중요한 건 그 저주받은 해적이 더 이상 우리 바다를 더럽히지 못하게 하는 것이오\n이 일에 대해선 보수를 충분히 지급하겠소 "+FindRussianMoneyString(sti(pchar.GenQuest.TakePirateship.Money))+". 시간을 낭비하지 마시오, 선장. 이 악당이 에서 당신을 기다려주지 않을 것이오 "+XI_ConvertString("Colony"+pchar.GenQuest.TakePirateship.City+"Gen")+". 가거라, 신의 가호가 있기를!";
			link.l1 = "벌써 닻을 올리는군, "+GetAddress_FormToNPC(NPChar)+"! 오래 기다릴 필요 없을 거요.";
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
		//	ОЗГ - захватить пассажира
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "TakePassenger":
			//установка параметров
			pchar.GenQuest.questName = "TakePassenger"; //тип квеста
			pchar.GenQuest.TakePassenger.Nation = FindEnemyNation2Character(sti(npchar.index));//вражеская нация
			iTemp = 1;
			while (iTemp < 10 && sti(pchar.GenQuest.TakePassenger.Nation) == PIRATE) {
				pchar.GenQuest.TakePassenger.Nation = FindEnemyNation2Character(sti(npchar.index));
				iTemp += 1;
			}
			if (iTemp == 10 && sti(pchar.GenQuest.TakePassenger.Nation) == PIRATE) {
				dialog.text = LinkRandPhrase("오늘은 당신께 드릴 일이 없소.","오늘은 더 이상 맡길 일이 없소.","오늘은 더 이상 줄 일이 없소, 미안하오. 내일 다시 오면, 그때 보도록 하지...");
				link.l1 = RandPhraseSimple("안타깝군...","아, 참 안타깝군, "+GetAddress_FormToNPC(NPChar)+". ");
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
			pchar.GenQuest.TakePassenger.Money = ((hrand(5) + hrand(6, "1")+4)*500)+12500+(sti(pchar.rank)*1000);
			pchar.GenQuest.Governor.Group2.day = GetDataDay();
			string sText = SelectPassText();
			dialog.text = "물론이오. 내가 말하는 자는 이름이 "+pchar.GenQuest.TakePassenger.Name+". "+sText+" 나는 오랫동안 그를 찾아다녔소. 이제야 그가 어디에 있는지에 대한 확실한 정보를 얻었소. 그 자를 반드시 살아 있는 채로 내게 데려오시오. 우리 마을 광장에서 공개적으로 교수형에 처할 생각이오. 이 임무를 맡을 준비가 되었소?";
			link.l1 = "준비되었습니다, "+GetAddress_FormToNPC(NPChar)+". 그 악당을 어디서 찾을 수 있지?";
		    link.l1.go = "TakePassenger_agree";
			link.l2 = "흠... 아니, 나는 사양하겠소.";
		    link.l2.go = "All_disagree";
		break;
		
		case "TakePassenger_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.TakePassenger.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = "방금 들어온 "+FindRussianDaysString(pchar.GenQuest.TakePassenger.Terms1)+", 그는 '라는 배의 승객으로서\n"+pchar.GenQuest.TakePassenger.ShipName+"', 출항할 것이오 "+XI_ConvertString("Colony"+pchar.GenQuest.TakePassenger.City+"Gen")+" 그리고 가시오 "+XI_ConvertString("Colony"+pchar.GenQuest.TakePassenger.CityA+"Acc")+". 당신은 "+FindRussianDaysString(pchar.GenQuest.TakePassenger.Terms)+" 지정된 항로에서 이 배를 찾아서, 올라타 그 자식을 붙잡으시오. 이 지시대로 하면 보수를 주겠소\n "+FindRussianMoneyString(sti(pchar.GenQuest.TakePassenger.Money))+". 행운을 빕니다, 선장!";
			link.l1 = "더 이상 시간을 낭비하지 않겠소, "+GetAddress_FormToNPC(NPChar)+"! 즉시 출항하겠습니다.";
			link.l1.go = "exit";
			SetFunctionTimerCondition("TakePassenger_CreateShip", 0, 0, sti(pchar.GenQuest.TakePassenger.Terms1), false);
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.TakePassenger.Terms), false);
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "10");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.TakePassenger.City+"Gen"));
			AddQuestUserData("MayorsQuestsList", "sCityA", XI_ConvertString("Colony"+pchar.GenQuest.TakePassenger.CityA+"Acc"));
			AddQuestUserData("MayorsQuestsList", "sDay1", FindRussianDaysString(sti(pchar.GenQuest.TakePassenger.Terms1)));
			AddQuestUserData("MayorsQuestsList", "sDay2", FindRussianDaysString(sti(pchar.GenQuest.TakePassenger.Terms)));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.TakePassenger.Money)));
			AddQuestUserData("MayorsQuestsList", "sName", pchar.GenQuest.TakePassenger.Name);
			AddQuestUserData("MayorsQuestsList", "sShipName", pchar.GenQuest.TakePassenger.ShipName);
		break;
		
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Таможенный патруль
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "CustomPatrol":
			//установка параметров
			pchar.GenQuest.questName = "CustomPatrol"; //тип квеста
			pchar.GenQuest.CustomPatrol.Nation = sti(npchar.nation);//нация
			pchar.GenQuest.CustomPatrol.Island = Islands[GetCharacterCurrentIsland(PChar)].id;
			pchar.GenQuest.CustomPatrol.LoginDay = rand(2)+1;
			pchar.GenQuest.CustomPatrol.Loginlocator = rand(3)+3;
			pchar.GenQuest.CustomPatrol.ShipType = SelectCustomPatrolShipType(FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_UNIVERSAL);
			pchar.GenQuest.CustomPatrol.ShipTypeA = SelectCustomPatrolShipType(FLAG_SHIP_TYPE_RAIDER);
			pchar.GenQuest.CustomPatrol.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.CustomPatrol.ShipType));
			pchar.GenQuest.CustomPatrol.Money = ((hrand(5)+hrand(6, "1")+4)*450)+8200 + (sti(pchar.rank) * 750);
			pchar.GenQuest.Governor.Group1.day = GetDataDay();
			dialog.text = "나는 신뢰할 만한 정보를 입수했소. 어떤 선장이 밀수업자들과 노예 판매 거래를 주선했다고 하오. 알다시피, 우리 식민지에서 개인이 이런 거래를 하는 것은 밀수 행위로 간주되오.\n문제는 밀수업자들이 만날 정확한 시간도, 날짜도, 장소도 내가 알지 못한다는 것이오. 알려진 것은 이 범죄 행위가 앞으로 사흘 안에 우리 섬에서 일어난다는 사실뿐이오. 설상가상으로 내 모든 순찰선들이 수리 중이거나 다른 임무에 투입되어 이 악당들을 쫓을 수 없소.\n이 임무를 맡아 밀수업자들을 찾아내어 가장 단호한 방법으로 처리하고 본보기를 보여주길 제안하오. 이 임무를 맡을 준비가 되었소?";
			link.l1 = "준비되었습니다, "+GetAddress_FormToNPC(NPChar)+". 말씀해 보시오, 추가로 알고 있는 정보가 있소? 예를 들어 선장의 이름이나, 배의 이름 또는 종류 같은 것 말이오?";
		    link.l1.go = "CustomPatrol_agree";
			link.l2 = "흠... 아니, 나는 사양하겠소.";
		    link.l2.go = "All_disagree";
		break;
		
		case "CustomPatrol_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.CustomPatrol.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = "내 정보원이 방금 거래가 준비 중이며 곧 완료될 거라고 알려왔소. 그게 전부요. 그러니 우리 해역에 있는 수상한 선박들을 모두 좀 더 면밀히 살펴보시오. 성공한다면, 내가 당신에게 일정 금액을 지급하겠소\n "+FindRussianMoneyString(sti(pchar.GenQuest.CustomPatrol.Money))+"\n게다가, 상황을 고려하여 내가 그대에게 밀수품을 전부 수거할 권한을 주겠소. 물론 비공식적으로 말이오, 단 우리 도시에서 그것을 팔지만 않는다면.";
			link.l1 = "꽤 후하시군. 알겠소, 이제 당신 식민지 근해를 순찰하러 가지. "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "exit";
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, 4, false);
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
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.CustomPatrol.Money)));
		break;
		
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Найти дезертира
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "FindFugitive":
			//установка параметров
			pchar.GenQuest.questName = "FindFugitive"; //тип квеста
			pchar.GenQuest.FindFugitive.Startcity = npchar.city;
			pchar.GenQuest.FindFugitive.City = SelectFugitiveCity();
			pchar.GenQuest.FindFugitive.Chance = rand(2);
			pchar.GenQuest.FindFugitive.Name = GenerateRandomName(sti(npchar.Nation), "man");
			pchar.GenQuest.FindFugitive.Money = ((hrand(5)+hrand(6, "1")+4)*600)+9600+(sti(pchar.rank)*900);
			sText = SelectFugitiveText();
			log_testinfo(pchar.GenQuest.FindFugitive.City);
			log_testinfo(FindRussianDaysString(sti(pchar.GenQuest.FindFugitive.Chance)));
			pchar.GenQuest.Governor.Group2.day = GetDataDay();
			dialog.text = "자세히 말씀드리겠소. 아주 추악한 일이 벌어졌소 - "+sText+". 그의 동료들과 친구들을 심문해 본 결과, 우리는 탈영병이 해적들의 정착지 중 한 곳에 숨어들었다고 믿고 있소, 그럴 만한 이유도 있지요\n해적 소굴을 방문해 도망자를 찾아내어 체포한 뒤 이곳으로 데려오시오. 탈영은 중대한 범죄이니 반드시 처벌받아야 하오. 이 임무를 맡을 준비가 되었소?";
			link.l1 = "준비됐소, "+GetAddress_FormToNPC(NPChar)+". 탈영병의 이름을 말해 주시겠소?";
		    link.l1.go = "FindFugitive_agree";
			link.l2 = "흠... 아니오, 사양하겠소.";
		    link.l2.go = "All_disagree";
		break;
		
		case "FindFugitive_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.FindFugitive.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = "예, 물론이지요. 그의 이름은 "+pchar.GenQuest.FindFugitive.Name+". 그자가 제복을 입고 있을 것 같지는 않으니, 온갖 잡놈들을 잘 살펴보시오. 수색 기간은 한 달을 주겠소. 그 이후에는 찾아도 의미가 없을 것 같으니 말이오. 성공하면 당신에게 이 금액을 지불하겠소\n "+FindRussianMoneyString(sti(pchar.GenQuest.FindFugitive.Money))+".";
			link.l1 = "더 이상 시간을 낭비하지 않겠소, "+GetAddress_FormToNPC(NPChar)+"! 즉시 출항하겠습니다.";
			link.l1.go = "exit";
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, 30, false);
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "12");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.FindFugitive.Money)));
			AddQuestUserData("MayorsQuestsList", "sName", pchar.GenQuest.FindFugitive.Name);
			//создаем дезертира
			sld = GetCharacter(NPC_GenerateCharacter("Fugitive", "citiz_"+(21+rand(9)), "man", "man", sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, sti(npchar.nation), 30, true, "soldier"));
			SetFantomParamFromRank(sld, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true);
			sld.name = pchar.GenQuest.FindFugitive.Name;
			sld.lastname = "";
			sld.dialog.FileName = "MayorQuests_dialog.c";
			sld.greeting = "marginal";
		break;
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Проникновение во враждебный город
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "Intelligence":
			pchar.GenQuest.Governor.Group3.day = GetDataDay();
			dialog.text = "알겠소. 아마도 보상으로 "+FindRussianMoneyString(sti(pchar.GenQuest.Intelligence.Money))+" 당신에게 좋은 동기가 될 것이오.";
			link.l1 = "그래, 돈은 괜찮군... 이 임무 맡겠어.";
		    link.l1.go = "Intelligence_agree";
			link.l2 = "흠... 아니, 거절하겠소. 너무 위험하군.";
		    link.l2.go = "All_disagree";
		break;
		case "Intelligence_agree":
			if (pchar.GenQuest.Intelligence.City == "none" || isBadReputation(pchar, 30)) //на всякий случай
			{
				dialog.text = "비록 그대를 완전히 신뢰한다고는 할 수 없으나... 이 임무는 맡기지 않겠소.";
				link.l1 = "어쩔 수 없군... 아쉽지만 내가 할 수 있는 게 없네.";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "GenQuest." + pchar.GenQuest.questName);
			}
			else
			{
				npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
				pchar.GenQuest.questName = "Intelligence"; //тип квеста
				sTemp = pchar.GenQuest.Intelligence.City;
				switch (rand(4))
				{
					case 0:	sTemp += "_Priest";		break;
					case 1:	sTemp += "_trader";		break;
					case 2:	sTemp += "_shipyarder"; break;
					case 3:	sTemp += "_usurer";	    break;
					case 4:	sTemp += "_PortMan";	break;
				}
				pchar.GenQuest.Intelligence.SpyId = sTemp; //Id нашего шпиона в городе
				dialog.text = "좋소! 이제 본론으로 들어갑시다. In "+XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Dat")+" 현지인을 찾아야 해 "+GetWorkTypeOfMan(&characters[GetCharacterIndex(sTemp)],"Gen")+", 그의 이름은 "+GetFullName(&characters[GetCharacterIndex(sTemp)])+". 내 이름을 그에게 전하면, 그는 당신에게 서류 꾸러미를 줄 것이오. 이 꾸러미를 내 손에 전달해 준 대가로, 나는 당신에게\n "+FindRussianDaysString(sti(pchar.GenQuest.Intelligence.Terms))+". 그리고 모든 일은 비밀리에 진행해야 한다는 점을 명심하시오.\n만약 신분이 드러나면, 그 요원은 접촉을 시도하지 않을 것이오. 이해했소?";
				link.l1 = "그래, 알았어. "+GetAddress_FormToNPC(NPChar)+". 즉시 시작하겠습니다.";
				link.l1.go = "exit";
				pchar.GenQuest.Intelligence.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
				SaveCurrentQuestDateParam("GenQuest.Intelligence"); //запись даты получения квеста
				ReOpenQuestHeader("MayorsQuestsList");
				AddQuestRecord("MayorsQuestsList", "6");
				AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
				AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
				AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Acc"));
				AddQuestUserData("MayorsQuestsList", "sIsland", XI_ConvertString(GetIslandByColony(&colonies[FindColony(pchar.GenQuest.Intelligence.City)])+"Dat"));
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
			dialog.text = RandPhraseSimple("나쁘지 않소. 하지만 기한을 맞추지 못했으니 보수를 조금 줄여야겠군. 이제 그대의 보수는 "+FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money))+". 자, 여기 있소.","좋군. 하지만 기한을 맞추지 못했으니, 나는 이 편지들을 오래 기다렸소. 자네 때문에 내 계획이 어긋났으니 보상은 조금 깎을 수밖에 없겠군. 그래도 자네가 받아야 할 보상은 기꺼이 주겠소 - "+FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money))+". 자, 여기 있소.");
			link.l1 = "나에게 유쾌한 일이라고는 할 수 없지만, 결국 기한이 실제로 지켜지지 않았소. 그러니 불만은 없소. "+GetAddress_FormToNPC(NPChar)+".";
		    link.l1.go = "All_Execute_1";
			//--> слухи
			AddSimpleRumour(RandPhraseSimple("You know, governor " + GetFullName(npchar) + " are not very pleased with the quickness of a captain " + GetMainCharacterNameGen() + ".", 
				"Governor " + GetFullName(npchar) + " is not very pleased with captain " + GetMainCharacterNameDat() + ", "+ GetSexPhrase("who","who") +" complied with his orders, but did not in due time..."), sti(npchar.nation), 5, 1);
			//<-- слухи
		break;
		
		// -------------- общий набор для всех квестов мэра ------------------
		case "All_disagree":
			dialog.text = RandPhraseSimple(
				"흠. 그렇다면 내가 그대의 결의를 과대평가했나 보군, 선장.",
				"실망이로군, 선장. 이런 일에 필요한 자질이 정말로 부족한 것 같소.",
				"다음에는, 선장, 쓸데없는 말로 내 시간을 낭비하기 전에 두 번 생각하도록 하시오.");
			link.l1 = "죄송합니다, "+GetAddress_FormToNPC(NPChar)+", 하지만 이 일은 맡을 수 없습니다.";
		    link.l1.go = "exit";
			//ChangeCharacterComplexReputation(pchar,"nobility", -2);
			
			if (CheckAttribute(pchar, "GenQuest.questName"))
			{
				QuestName = pchar.GenQuest.questName;
				DeleteAttribute(pchar, "GenQuest." + QuestName);
				DeleteAttribute(pchar, "GenQuest.questName");
			}
		break;
		case "All_Late":
			QuestName = pchar.GenQuest.questName;
			dialog.text = RandPhraseSimple("음, 매우 나쁘구나 - 더 무슨 말을 하겠는가. 나는 자네를 믿었건만, 결국 내 시간만 허비했군. 실망이오.","글쎄, 정말 실망스럽군... 내 저택에는 이런 심부름을 언제든지 대신해 줄 사람이 얼마든지 있는데, 괜히 자네에게 시간을 허비했구먼. 뭐, 어쩔 수 없지...");
			link.l1 = "죄송합니다, "+GetAddress_FormToNPC(NPChar)+", 나는 할 수 있는 모든 것을 다 했소.";
		    link.l1.go = "exit";
			//--> слухи
			AddSimpleRumour(LinkRandPhrase("You know, governor " + GetFullName(npchar) + " is very displeased with captain " + GetMainCharacterNameDat() + ". Just imagine - he failed to fulfill his assignment in time!", 
				"Governor " + GetFullName(npchar) + " is slightly annoyed that a captain " + GetFullName(pchar) + " put his shoulder to the wheel, but fail to fulfill his assignment in time. That's too bad...", 
				"I heard that governor " + GetFullName(npchar) + " is very displeased with you, captain " + GetFullName(pchar) + ", since you failed to meet the deadline while trying to fulfill his assignment."), sti(npchar.nation), 5, 1);
			//<-- слухи
			ChangeCharacterComplexReputation(pchar,"nobility", -4);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			DeleteAttribute(pchar, "GenQuest." + QuestName);
			DeleteAttribute(pchar, "GenQuest.questName");
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_common"; //реплику вертаем
			SaveCurrentNpcQuestDateParam(npchar, "work_date"); //сразу ещё один не даем
			CloseQuestHeader("MayorsQuestsList");
		break;
		case "All_Found":
			QuestName = pchar.GenQuest.questName;
			dialog.text = RandPhraseSimple("정말 충격적이오! 목표를 찾아냈으면서도 우위를 확보하려는 노력조차 하지 않았다니, 그야말로 극도의 무모함이오. 실망스럽구려!","음, 실망스럽군... 목표를 찾는 것만으로는 충분하지 않소 - 그것을 파괴할 수단도 갖추어야 하오. 내 저택에는 언제든 이런 심부름을 해줄 악당들이 넘쳐나오. 내가 대체 무슨 생각으로 자네에게 맡겼던 것인가?");
			link.l1 = "죄송합니다, "+GetAddress_FormToNPC(NPChar)+", 하지만 내 목숨을 함부로 걸 생각은 없소.";
		    link.l1.go = "exit";
			//--> слухи
			AddSimpleRumour(LinkRandPhrase("You know, governor " + GetFullName(npchar) + " is very displeased with captain " + GetMainCharacterNameDat() + ". Imagine, "+ GetSexPhrase("he turned out to be a downright coward","she turned out to be a downright coward") +"!", 
				"Governor " + GetFullName(npchar) + " is slightly annoyed that a captain " + GetFullName(pchar) + " took the job, but failed to carry it out because of their own indecision. Hee-hee, what wilt captains!", 
				"I heard that Governor " + GetFullName(npchar) + " very displeased with you, Captain " + GetFullName(pchar) + ". They say you're nothing but a coward"+ GetSexPhrase("","") +"..."), sti(npchar.nation), 5, 1);
			//<-- слухи
			ChangeCharacterComplexReputation(pchar,"nobility", -6);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			DeleteAttribute(pchar, "GenQuest." + QuestName);
			DeleteAttribute(pchar, "GenQuest.questName");
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_common"; //реплику вертаем
			SaveCurrentNpcQuestDateParam(npchar, "work_date"); //сразу ещё один не даем
			CloseQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "21");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
		break;
		case "All_Execute":
			QuestName = pchar.GenQuest.questName;
			dialog.text = RandPhraseSimple("훌륭한 소식이오! 자, 이제 모든 것을 정리할 때가 되었군. 당신의 보수는 "+FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money))+". 자, 여기 있소.","훌륭하오! 모두에게 가장 좋은 결과지... 자, 당신께 마땅한 보상을 드리게 되어 기쁘오 - "+FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money))+". 자, 여기 있소.");
			link.l1 = "감사합니다, "+GetAddress_FormToNPC(NPChar)+", "+RandPhraseSimple("거래하게 되어 기쁩니다!","정착지들이 이렇게 명확하다니 기쁘게 놀랐소.");
		    link.l1.go = "All_Execute_1";
			//--> слухи
			AddSimpleRumour(LinkRandPhrase("You know, governor " + GetFullName(npchar) + "  was praising for diligence"+ GetSexPhrase("a captain","a young lady") +" " + GetMainCharacterNameGen() + ".", 
				"Governor " + GetFullName(npchar) + " is praising captain " + GetMainCharacterNameGen() + ", "+ GetSexPhrase("he","she") +" is always a flawless performer when it comes to governor's assignments. An irreplaceable person for the governor, I say...", 
				"I heard that governor " + GetFullName(npchar) + " is very much pleased with you, captain " + GetFullName(pchar) + ". He defines you as a very careful and thorough officer. That's very nice to hear, captain..."), sti(npchar.nation), 5, 1);
			//<-- слухи
		break;
		case "All_Execute_1":
			QuestName = pchar.GenQuest.questName;
			dialog.text = RandPhraseSimple("아주 좋소. 또 나를 찾아오시오 – 어쩌면 다른 일을 줄 수도 있겠군.","좋소, 훌륭하군! 앞으로도 이런 일거리를 또 맡기게 될 것 같소.");
			link.l1 = RandPhraseSimple("훌륭하오.","좋소.");
		    link.l1.go = "exit";
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.(QuestName).Money));
			CloseQuestHeader("MayorsQuestsList");
			ChangeCharacterComplexReputation(pchar,"nobility", 4);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(PChar, "Leadership", 180);
			OfficersReaction("good"); // dlc
			
			DeleteAttribute(pchar, "GenQuest." + QuestName);
			DeleteAttribute(pchar, "GenQuest.questName");
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_common"; //реплику вертаем
			SaveCurrentNpcQuestDateParam(npchar, "work_date"); //сразу ещё один не даем
			// инкремент в базу заданий мэров
			sTemp = npchar.City;
			if (!CheckAttribute(pchar, "GenQuest.MayorQuestsList." + sTemp)) pchar.GenQuest.MayorQuestsList.(sTemp) = 0;
			pchar.GenQuest.MayorQuestsList.(sTemp) = sti(pchar.GenQuest.MayorQuestsList.(sTemp)) + 1;
		break;
//<-- осады homo
		case "siege_task":
            makearef(aData, NullCharacter.Siege);
            aData.HelpColony = true;
			dialog.text = "이처럼 어려운 시기에는 어떤 도움이라도 정말 고맙소. 당신의 지원을 받아들이겠소 – 우리 식민지를 지켜 주면 반드시 보상을 내리겠소.";
			link.l1 = "그럼 시간 낭비하지 맙시다.";
		    link.l1.go = "exit";
		break;
		
		//Jason --> Бремя гасконца
		case "Sharlie":
			dialog.text = "미셸 드 몽페르를 찾고 있소? 흥미롭군... 그를 찾아서 무슨 용건이오?";
			link.l1 = "나는 그의 형제요. 아버지께서 미셸이 곤경에 처해 도움이 필요하다고 말씀하셔서, 그래서 나는...";
			link.l1.go = "Sharlie_1";			
		break;
		
		case "Sharlie_1":
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "First time";
			DelLandQuestMark(sld);
			dialog.text = "그래? 나는 몽페르 나리에게 형제가 있다는 말을 들은 적이 없는데... 그런데 말이오, 나리, 자네가 매우 수상해 보여서 말이오... 추가 조사를 위해 자네를 체포하겠소. 중위! 이 사람을 구금하라!";
			link.l1 = "하지만 나리!";
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
			dialog.text = "그래도 나는 사과하고 싶소. 여기 이 검과 권총, 그리고 이 가벼운 갑옷을 받아주시오. 내 선물이니, 분명 유용하게 쓰일 거라 믿소.";
			link.l1 = "감사합니다, 나리. 당신 경비병들이 내 모든 것을 가져간 걸 생각하면, 이게 정말 요긴하게 쓰이겠군요.";
			// belamour legendary edition -->
			link.l1.go = "Sharlie_5";		
			link.l2 = "감사합니다, 나리. 혹시 저를 도와주실 다른 방법이 있겠습니까? 신사 대 신사로서 말입니다. 제 처지가 얼마나 끔찍한지 직접 보실 수 있을 것입니다!";
			link.l2.go = "Sharlie_3";	
		break;
		
		case "Sharlie_3":
			dialog.text = "자, Charles... (책상 서랍을 뒤지며) 여기, 이 신성한 부적을 행운을 위해 가져가게. 더는 도와줄 수 없네, 미안하네. 이 식민지에서는 오직 자네 자신만을 믿고 살아가야 하네.";
			link.l1 = "그래도 뭔가 있군. 선물 고맙소, 나리.";
			link.l1.go = "Sharlie_4";
		break;
		
		case "Sharlie_4":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "Commerce", 10);
			Log_Info("You'have received equipment");
			Log_Info("You have received the 'Holy Water' amulet");
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
			// <-- legendary edition
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 10);
			Log_Info("You'have received equipment");
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
		//<-- Бремя гасконца
		
		//Sinistra --> Травля крысы		
		case "TK_TravlyaKrys":
			dialog.text = "참으로 운명의 장난이로군, Charles... 우리 세계에서 이렇게 빠르게 떠오르는 자는 드물지. 자네와 나는 잘 지낼 것 같은 예감이 드는군.";
			link.l1 = "영광입니다. 혹시 저에게 맡기실 일이 있으신가요?";
			link.l1.go = "TK_TravlyaKrys_2";
			DeleteAttribute(pchar, "questTemp.TK_TravlyaKrys");
			PChar.quest.TK_Timer.over = "yes";
		break;
		
		case "TK_TravlyaKrys_2":
			dialog.text = "물론이지요! 특히 당신이 르 프랑수아 근처에서 바르바존의 해적 중 한 명과 성공적으로 교전한 뒤라면 더욱 그렇소...";
			link.l1 = "그 만남에 대해 좋은 기억이 있다고는 할 수 없군. 바르바존이 정확히 누구지?";
			link.l1.go = "TK_TravlyaKrys_3";
		break;
		
		case "TK_TravlyaKrys_3":
			dialog.text = "자크 바르바종, 일명 '착한 자크'는 르 프랑수아의 도적 소굴을 이끌고 있소. 그는 이른바 해적 남작 중 한 명으로, 소앤틸리스에서 해적질과 밀수로 문제를 일으키고 있지. 악명 높은 범죄자라서, 내 장담하건대 언젠가 생피에르의 교수대에서 최후를 맞이할 것이오!";
			link.l1 = "실례합니다만, 마르티니크에서 진정한 권위자가 아니십니까? 그 소굴을 그냥 없애버릴 수는 없습니까? 제가 거기 가봤는데, 믿으십시오, 별로 볼 것도 없더군요.";
			link.l1.go = "TK_TravlyaKrys_4";
		break;
		
		case "TK_TravlyaKrys_4":
			dialog.text = "내 섬의 그리 고상하지 않은 장소들에 대해 아는 척 자랑하지 않는 것이 좋겠소, Charles. 그것은 귀족다운 태도가 아니오. 자네 질문에 대해 말하자면\n우리 세상의 모든 일이 힘만으로 해결되는 것은 아니오. 정치와 사업 이해관계도 얽혀 있지. 하지만 불필요한 세부사항까지 들어갈 필요는 없소. 이번엔 힘이 필요한 구체적인 임무가 있소.";
			link.l1 = "계속 말씀하십시오.";
			link.l1.go = "TK_TravlyaKrys_5";
		break;
		
		case "TK_TravlyaKrys_5":
			dialog.text = "바르바존은 쉬운 돈을 노리는 하찮은 선원들을 끌어모으지. 가끔은 그들 중 하나에게 미끼를 던져주고, 서로 싸우는 꼴을 구경하곤 해. 살아남은 자를 부려먹을 때도 있지만, 대개는 내쫓아버리지. 그런데 말이야, 절박한 해적이 배회하는 것만큼 위험한 일도 없다는 걸 명심해.";
			link.l1 = "이해는 가지만, 내가 그 일을 해낼 수 있을지는 잘 모르겠소. 나는 최근에야 내 배의 지휘를 맡았고, 아직 이것저것 배우는 중이오, 그러니까...";
			link.l1.go = "TK_TravlyaKrys_6";
		break;
		
		case "TK_TravlyaKrys_6":
			dialog.text = "말도 안 되는 소리! 자네는 이미 승리를 맛봤지 않나. 내 부하들 중 게으름뱅이들보다 훨씬 더 많이 말이야! 바르바존의 졸개 한 놈을 더 침몰시키면 시에서 오천 페소를 세금 없이 보상해 줄 걸세. 해적을 산 채로 데려오면 팔천 페소를 주겠네. 물론 제대로 처형하기 위해서지.";
			link.l1 = "돈이 꼭 필요하오. 그 해적은 어디서 찾을 수 있소?";
			link.l1.go = "TK_TravlyaKrys_7";
			link.l2 = "죄송하지만, 아직 이런 임무를 맡을 준비가 안 된 것 같습니다.";
			link.l2.go = "TK_TravlyaKrys_Otkaz";
		break;
		
		case "TK_TravlyaKrys_Otkaz":
			dialog.text = "안타깝군, Charles. 그렇다면 더 이상 붙잡지 않겠네.";
			link.l1 = "안녕히 계십시오, 각하.";
			link.l1.go = "exit";
		break;
		
		case "TK_TravlyaKrys_7":
			dialog.text = "네가 함께 타게 되어 기쁘네, Charles. 우리 정보에 따르면 Hater라는 러거선이 지금 Le François에서 출항 준비 중이라 하오. 지체할 여유가 없으니 곧장 출항하여 교전하게. 걱정 말게, 친구여, 반드시 성공할 것이오.";
			link.l1 = "신의 은총이 함께하길, 각하.";
			link.l1.go = "TK_TravlyaKrys_8";			
		break;
		
		case "TK_TravlyaKrys_8":
			DialogExit();
			SetQuestHeader("TravlyaKrys");
			AddQuestRecord("TravlyaKrys", "1");
			
			sld = GetCharacter(NPC_GenerateCharacter("TK_Heiter", "mercen_8", "man", "man", sti(PChar.rank), PIRATE, -1, true, "pirate"));
			sld.name = "Daniel";
			sld.lastname = "Montbars";
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
		//<-- Травля крысы
		
		//Jason --> Португалец
		case "Portugal":
			dialog.text = "물론이지요, 선장님! 그래서 일부러 귀찮게 한 것이오.";
			link.l1 = "그렇다면 경청하겠소.";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "어젯밤 섬 근처에서 동네 어부들이 이상한 배를 봤다고 하오. 그들이 말하길, 깃발도 신호등도 없는 거대한 전함, 마치 전열함 같았다고 하오. 내 생각엔 그 배가 실제로 프리깃보다 클 리는 없겠지만, 설령 그렇다 해도 이미 너무 큰 배일 것이오!";
			link.l1 = "두려움은 분명히 작은 언덕도 산처럼 보이게 만들지... 하지만 그게 무슨 소용이 있겠나?";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			dialog.text = "당신에게 부탁하오, 선장. 내 무역 파트너들이 이 소문에 겁을 먹고 있소 – 해적이나 스페인 사략선의 짓이라 생각하며, 이는 무역에 큰 악영향을 주고 있소. 무엇보다도, 지금 식민지에는 군함이 한 척도 없고, 보호용 슬루프 두 척과 밀수꾼 사냥에나 쓸 만한 낡은 스쿠너 한 척뿐이오.\n이대로 방치할 수는 없소... 어쨌든, 이제 그 수수께끼의 배에 대한 소문이 도시의 절반에 퍼졌소! 제발, 당신의 배로 우리와 함께 수색에 나서 주시오 – 나는 당신이 훌륭한 선장임을 알고 있소, 설령 그저 프리깃 한 척일지라도 당신의 대포라면 그 배가 다른 곳에서 먹잇감을 찾게 만들 수 있을 것이오!";
			link.l1 = "나리... 사실, 나는 다른 계획이 있었소...";
			link.l1.go = "Portugal_3";
		break;
		
		case "Portugal_3":
			dialog.text = "제발이오, 선장님! 불안한 소문이 잠잠해질 때까지만, 며칠만 머물러 주시오! 물론 시간에 대한 보수도 드릴 것이오. 만약 1만 에잇을 드린다면 만족하시겠소?";
			link.l1 = "흠... 하지만, 각하, 저는...";
			link.l1.go = "Portugal_4";
		break;
		
		case "Portugal_4":
			dialog.text = "그리고 그 배와 실제로 전투를 벌인다면 보수를 두 배로 주겠소, 침몰시키면 세 배로 주겠소! 이제, 어떻게 하겠소?";
			link.l1 = "알겠소, 어차피 며칠 동안 여기 머물 생각이었으니.";
			link.l1.go = "Portugal_5";
		break;
		
		case "Portugal_5":
			dialog.text = "훌륭하오, 나는 사실 "+pchar.lastname+" 선장 나리 를 한 번도 의심하지 않았소! 기억하시오 - 우리 해역에서 이틀만 머무르면 돈은 당신 것이오. 만약 전투에 휘말리게 된다면, 결과에 따라 보수를 받게 될 것이오.";
			link.l1 = "알겠습니다, 각하. 약속은 지켜졌으니 이제 제 배로 돌아가겠습니다.";
			link.l1.go = "Portugal_6";
		break;
		
		case "Portugal_6":
			dialog.text = "돌아오기를 기다리겠소, 선장!";
			link.l1 = "물러가도록 하겠습니다.";
			link.l1.go = "Portugal_7";
		break;
		
		case "Portugal_7":
			DialogExit();
			AddQuestRecord("Portugal", "10");
			NextDiag.CurrentNode = "Portugal_8";
			LocatorReloadEnterDisable("Fortfrance_town", "reload1_back", false);
			LocatorReloadEnterDisable("Fortfrance_town", "reload2_back", false);
			LocatorReloadEnterDisable("Fortfrance_town", "gate_back", false);//открыть выходы из города
			bDisableFastReload = true;//закрыть быстрый переход
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			pchar.quest.Portugal_Seapatrol.win_condition.l1 = "location";
			pchar.quest.Portugal_Seapatrol.win_condition.l1.location = "Martinique";
			pchar.quest.Portugal_Seapatrol.function = "PortugalSeapatrolGo";
			pchar.quest.Portugal_SeapatrolAvendel.win_condition.l1 = "location";
			pchar.quest.Portugal_SeapatrolAvendel.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.Portugal_SeapatrolAvendel.function = "AvendelSpeach";
		break;
		
		case "Portugal_8":
			dialog.text = "선장님, 우리가 해안 경비를 이틀 동안 맡기로 약속하지 않았소!";
			link.l1 = "예, 물론이지요. 그것을 기억하고 있소.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Portugal_8";
		break;
		
		case "Portugal_9":
			dialog.text = "자네는 약속한 대로 임무를 완수했군. 여기 보상이다 - 우리가 합의한 대로 1만 페소일세.";
			link.l1 = "감사합니다! 보시다시피, 당신의 걱정은 기우였소. 행운을 빕니다!";
			link.l1.go = "Portugal_10";
		break;
		
		case "Portugal_10":
			DialogExit();
			AddMoneyToCharacter(pchar, 10000);
			NextDiag.CurrentNode = "First time";
			pchar.quest.MartiniqueGovernorOver.over = "yes"; //снять таймер
		break;
		//<-- Португалец
		
		// Warship, 16.05.11. Генер "Правосудие на продажу".
		case "JusticeOnSale_1":
			dialog.text = "Oh "+GetAddress_Form(NPChar)+", 나를 놀라게 했구나! 그 악당들이 정말 그렇게 대담해졌단 말인가? 즉시 사령관에게 알리고 해안 순찰대를 보내야겠군!";
			link.l1 = "기꺼이 도와드렸습니다. 이제 물러가도 되겠습니까?";
			link.l1.go = "JusticeOnSale_2";
			
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait");
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale.PrisonWait");
			
			DeleteQuestCondition("JusticeOnSale_MapEnter");
		break;
		
		case "JusticeOnSale_2":
			dialog.text = "물론이지요, 선장님. 여기 있습니다 – 부디, 제 개인적으로 드리는 이 소박한 보상을 받아 주십시오.";
			link.l1 = "감사합니다.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("JusticeOnSale_DlgExitAfterMayor_1");
		break;
		
		case "JusticeOnSale_4":
			dialog.text = "맞습니다, 선장님! 이렇게 그냥 둘 수는 없지요! 당신께 부탁드리건대, 그곳으로 가주십시오 "+XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId+"Dat")+", 그들의 배를 찾아서 일당 전원을 체포하시오! 저항한다면 힘을 써도 주저하지 마시오!";
			link.l1 = "물러가도록 하겠습니다.";
			link.l1.go = "JusticeOnSale_5";
		break;
		
		case "JusticeOnSale_5":
			dialog.text = "이제 가시오. 그곳으로 항해해 아무도 정의를 피해 도망치지 못하게 하시오. 먼저 해안에 상륙해야 할 것이고, 그 다음에 배를 처리하면 되오.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("JusticeOnSale_DlgExitAfterMayor_2");
		break;
		
		case "JusticeOnSale_7":
			dialog.text = "도와주셔서 감사합니다. 그 악당들은 마땅한 벌을 받았소. 부디, 제가 직접 드리는 이 작은 보상을 받아주십시오. 저는 제 도시의 질서와 평화를 매우 소중히 여기오.";
			link.l1 = "...";
			link.l1.go = "JusticeOnSale_8";
		break;
		
		case "JusticeOnSale_8":
			AddMoneyToCharacter(PChar, sti(PChar.rank) * 300 + hrand(1000));
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale");
			DialogExit();
		break;
		//<-- Правосудие на продажу
		
			//--> Jason регата
		case "Regata":
			// belamour legendary edition -->
			if(sti(pchar.rank) < 15)
			{
				Notification_Level(false, 15);
				dialog.text = "아, 훌륭하군요, 만나서 반갑소, 선장! 자네의 재능에 대해 들었지만, 진정 준비가 되었을 때 다시 오시오.";
				link.l1 = "예, 물론이지요. 원하시는 대로 하겠습니다.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "오, 훌륭하오, 반갑소, 선장! 마침 잘 오셨소 – 며칠 뒤면 레가타가 시작될 것이오. 규칙은 읽어보셨소? 전령이 반드시 전해주었을 텐데.";
				link.l1 = "예, 나리, 했습니다.";
				link.l1.go = "Regata_1";
				RemoveItems(PChar, "letter_open", 1);//уберем письмо
				DeleteAttribute(pchar, "questTemp.Regata.ToPortRoyal"); // patch-5
			}
		break;
		
		case "Regata_1":
			dialog.text = "그리고 5만 페소, 즉 상금에 보탬이 될 입장료는 준비하였소?";
			if (makeint(Pchar.money) >= 50000)
			{
				link.l1 = "예, 물론입니다. 제 보수를 받아 주십시오.";
				link.l1.go = "Regata_2";
			}
			link.l2 = "지금은 돈이 좀 부족하오. 하지만 반드시 필요한 금액을 마련하겠소.";
			link.l2.go = "Regata_nomoney";
		break;
		
		case "Regata_2":
			dialog.text = "아주 좋소. 이기면 돈을 다섯 배로 돌려받게 될 것이오. 이제는 레가타 규칙을 더 잘 알아야 하오.\n자세한 내용은 헨리 스티벤슨 나리에게 들을 수 있소; 그는 관저의 방들 중 한 곳에 있을 것이오. 그에게 가면 모든 것을 설명해 줄 것이오.";
			link.l1 = "알겠소. 그대로 하겠소.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -50000);
			pchar.quest.Regata_Guber.win_condition.l1 = "location";
			pchar.quest.Regata_Guber.win_condition.l1.location = "Portroyal_Roomtownhall";
			pchar.quest.Regata_Guber.function = "PrepareToRegataInPortroyal";
			pchar.questTemp.Regata.Begin = "true";
			NextDiag.TempNode = "First time";
		break;
		
		case "Regata_nomoney":
			dialog.text = "좋소, 하지만 제발 너무 오래 걸리지 마시오, 선장님. 곧 레가타가 시작되오.";
			link.l1 = "알겠소. 가능한 한 빨리 돈을 가져오도록 하겠소.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_1";
			pchar.questTemp.Regata.nomoney = "true";
		break;
		
		//регата-финал
		case "Regata_Final":
			dialog.text = "아하! 여기 요트 경주의 우승자가 있구려! 좋은 하루요, 선장 "+GetFullName(pchar)+"! 이 정당한 성공을 진심으로 축하하오! 요트 경주에서 우승한 자들은 언제나 영국 식민지에서 인기가 많았지, 그럴 만한 이유가 있소.";
			link.l1 = "감사합니다, 나리!";
			link.l1.go = "Regata_complete";
		break;
		
		case "Regata_complete":
			dialog.text = "이제 가장 즐거운 부분, 시상식으로 넘어가겠습니다. 1등 상금은 25만 페소입니다. 축하합니다!";
			link.l1 = "고맙소!";
			link.l1.go = "Regata_complete_1";
		break;
		
		case "Regata_complete_1":
			AddMoneyToCharacter(pchar, 250000);
			// belamour legendary edition в регате только один приз -->
			GiveItem2Character(pchar, "blade_26");
			GiveItem2Character(pchar, "cirass4");
			GiveItem2Character(pchar, "bussol");
			
			dialog.text = "또한, 당신은 귀중한 상품 세트를 받게 됩니다: 전설적인 톨레도 강철 레이피어 '아솔레다', 밀라노제 갑옷 한 벌, 그리고 훌륭한 나침반이 있소. 모두 당신의 것이오.";
			// <-- legendary edition
			link.l1 = "정말 기쁩니다, 나리. 정말로, 이렇게 관대하실 줄은 몰랐습니다.";
			link.l1.go = "Regata_complete_2";
		break;
		
		case "Regata_complete_2":
			dialog.text = "영국 식민지의 모든 신민을 대표하여, 경기에 참가해 주신 데 감사드리며 다시 한 번 우승을 축하드립니다! 내기를 하셨다면, 헨리 스티븐슨 경을 찾아가 아직 상금을 받지 않으셨다면 수령하시기 바랍니다. 행운을 빕니다, 선장님!";
			link.l1 = "친절한 말씀 감사합니다, 나리! 저 또한 이렇게 큰 행사에 참여할 기회를 주셔서 감사드립니다. 이제 물러가도록 허락해 주십시오.";
			link.l1.go = "Regata_complete_3";
		break;
		
		case "Regata_complete_3":
			DialogExit();
			NextDiag.CurrentNode = "First time";
		break;
		//<-- регата
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
			//==> на всякий случай
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
    if (CheckAttribute(pchar, "questTemp.jailCanMove.Deliver.locationId")) //если взят квест по доставке малявы
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
	SetOpenDoorCommonLoc(npchar.city, LocId); //открываем дверь
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
		// Rebbebion, чуть изменил функцию, чтобы условно испанцы не просили пробраться к испанцам, французы к французам и т.д
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
		case 0: sText = "That Judas, using his position, sold an important state secret to an enemy power."; break;
		case 1: sText = "That foul scoundrel killed his relative, a well-known and noble man, in order to inherit his fortune."; break;
		case 2: sText = "That foul scoundrel insulted my family and me personally."; break;
		case 3: sText = "This thieving rogue stole a decent sum of money from our city's treasury."; break;
		case 4: sText = "That villain is guilty of deaths of nearly a dozen of our citizens."; break;
		case 5: sText = "That rogue used his connection to take possession of a merchant vessel, and then he stole it and sold at the neighboring shipyard."; break;
	}
	return sText;
}

string SelectFugitiveCity()
{
	string sCity;
	switch (rand(3))
	{
		case 0: sCity = "LaVega"; break;
		case 1: sCity = "PuertoPrincipe"; break;
		case 2: sCity = "LeFransua"; break;
		case 3: sCity = "FortOrange"; break;
	}
	return sCity;
}

string SelectFugitiveText()
{
	string sText;
	switch (hrand(5))
	{
		case 0: sText = "one of the junior officers in our garrison has deserted and left the colony on board of a merchant ship."; break;
		case 1: sText = "one of our officers deserted right on duty and escaped on board of a smuggler ship."; break;
		case 2: sText = "one of our naval officers serving on a patrol brig deserted for unknown reason, hijacked a long boat and disappeared on it."; break;
		case 3: sText = "one of our prison guards threw up his service for  unknown reason and left our colony aboard a private vessel."; break;
		case 4: sText = "one of the soldiers in our garrison abandoned his post while keeping guard, went to the cove and left this place aboard an unknown vessel."; break;
		case 5: sText = "one of our military officers, captain of a patrol lugger, abandoned his ship in the open sea and went south on a fishing long boat."; break;
	}
	return sText;
}

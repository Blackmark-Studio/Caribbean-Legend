#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
#include "interface\ship.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Tavern\" + NPChar.City + "_Tavern.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06
	
	int iTest, iTemp;
	string sTemp;
	string NPCCity = NPChar.City;
    iTest = FindColony(NPChar.City); // город 
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	bool ok;
	
	if(!CheckAttribute(pchar, "questTemp.TavernVisit."+(NPCCity) )) 
	{
		pchar.questTemp.TavernVisit.(NPCCity) = true;
		pchar.questTemp.TavernVisit.counter = sti(pchar.questTemp.TavernVisit.counter) + 1;
		notification("First Tavern Visit " + XI_ConvertString(NPCCity + "TavernName"), "Drunk");
		AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, 10.0);
	}	
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("마을에 경보가 울려서 모두가 자네를 찾고 있어. 내가 자네라면 여기 안 있겠어.","도시 경비병 전원이 너를 찾으려고 마을을 샅샅이 뒤지고 있어. 나 바보 아니니까 너랑 말 안 할 거야!","도망쳐, "+GetSexPhrase("동료","아가씨")+", 군인들이 널 갈아버리기 전에..."),LinkRandPhrase("무슨 일이오, "+GetSexPhrase("놈","냄새나는 놈")+"?! 도시 경비병들이 네 냄새를 맡았어, 멀리 못 갈 거다"+GetSexPhrase(", 더러운 해적 놈!","")+"","살인자야, 당장 내 집에서 나가라! 경비병!","나는 너 따위 안 무서워, "+GetSexPhrase("놈","쥐")+"! 곧 우리 요새에서 교수형을 당하게 될 거다, 멀리 못 갈 거야..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("헤, 경보 따위는 나한테 아무 문제도 아니지...","그놈들이 날 절대 못 잡을 거야."),RandPhraseSimple("입 닥쳐, "+GetWorkTypeOfMan(npchar,"")+", 아니면 네 혀를 뽑아버릴 거야!","헤헷, "+GetWorkTypeOfMan(npchar,"")+", 그리고 거기 있는 놈들 전부 해적 잡으러 온 거야! 내가 하는 말 잘 들어, 이봐: 조용히 있으면 죽지 않아..."));
				link.l1.go = "exit";
				break;
			}
			if (sti(pchar.GenQuest.Piratekill) > 20 && sti(npchar.nation) == PIRATE)
			{
				dialog.text = RandPhraseSimple("그리고 네놈이구나, 이 자식아! 우리가 여기서 네놈한테 럼을 따라줄 것 같아? 천만에! 얘들아! 무장해라! 이 악당을 죽여라!","술 한잔 할래, 해적? 하! 안 돼! 이제 우리가 누가 누군지 보여주지! 얘들아, 칼 뽑아!");
				link.l1 = RandPhraseSimple("어? 뭐라고?","멈춰!");
				link.l1.go = "fight";
				bDisableFastReload = true;//закрыть переход
				pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
				pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
				pchar.quest.pirate_in_town.function = "TownPirate_battle";
				break;
			}
			//Jason, Бремя гасконца
			if(NPChar.City == "FortFrance")
			{
				if (!CheckAttribute(npchar, "quest.Rum") && CheckAttribute(pchar, "questTemp.Sharlie.Lock") && pchar.questTemp.Sharlie == "ship" && makeint(environment.time) > 5.0 && makeint(environment.time) < 19.0)
				{
					link.l1 = "나리, 일거리를 찾고 있습니다. 혹시 맡길 일이 있습니까?";
					link.l1.go = "Sharlie_rum";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Rum") && pchar.questTemp.Sharlie.Rum == "regard")
				{
					link.l1 = "당신이 내린 임무를 완료했습니다. 럼주가 실린 보트는 르 프랑수아 만에 전달되어 당신 사람들에게 인계되었습니다.";
					link.l1.go = "Sharlie_rum_5";
					break;
				}
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "crew" && npchar.city == "FortFrance")
			{
				DelLandQuestMark(npchar);
				FreeSitLocator("FortFrance_tavern", "sit7");
				dialog.text = "무엇을 원하십니까, 나리?";
				Link.l1 = "이봐 주인장, 내 배에 탈 선원들을 구해야 하는데, 도와줄 수 있겠어?";
				Link.l1.go = "Sharlie_crew";
				break;
			}
			
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "skiper" && npchar.city == "FortFrance")
			{
				DelLandQuestMark(npchar);
				dialog.text = "또 뵙는군. 이번에는 무슨 일이오, 나리?";
				Link.l1 = ""+npchar.name+", 내가 귀찮게 하는 거 아는 데, 질문 하나만 더 할게. 항해사가 필요한데 어디서 구할 수 있는지 아나?";
				Link.l1.go = "Sharlie_skiper";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
    			dialog.text = "무엇을 원하시오, 나리?";
				Link.l1 = "질문 몇 가지에 답해 줄 수 있을까 기대했네.";
				Link.l1.go = "quests";
				if(!CheckAttribute(pchar,"questTemp.TimeLock"))
				{
					link.l2 = "방을 빌리고 싶소.";
					link.l2.go = "room";
				}
				break;
			}			
			//Бремя гасконца
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "tavern" && npchar.city == "Tortuga")
			{
				dialog.text = "뵙게 되어 정말 기쁩니다, 나리! 무엇을 도와드릴까요? 럼, 브랜디, 스카치 위스키 어떠십니까?";
				Link.l1 = "최고급 프랑스 와인 한 병과 방 열쇠를 주시오.";
				Link.l1.go = "mtraxx_tortuga";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "room" && npchar.city == "Tortuga")
			{
				dialog.text = "이미 지불하셨습니다, 나리. 방은 위층에 있습니다.";
				Link.l1 = "감사합니다.";
				Link.l1.go = "exit";
				break;
			}
			
			// Sinistra - Квест "Длинные тени старых грехов" ==>	
			if (CheckAttribute(pchar, "questTemp.DTSG_BasTerTavern") && npchar.city == "BasTer")
			{
				dialog.text = "무엇을 도와드릴까요, 선장님? 방금 있었던 일을 생각하면 한 잔 하고 싶으시겠지요.";
				Link.l1 = "그건 나중에 해도 돼. 사실 나는 무슨 일이 있었는지 이야기하고 싶어.";
				Link.l1.go = "DTSG_BasTerTavern_1";
				DelLandQuestMark(npchar);
				break;
			}
			// <== Квест "Длинные тени старых грехов" - Sinistra
			
			//--> Торговля по закону
			if (CheckAttribute(pchar, "questTemp.TPZ_Start") && !CheckAttribute(pchar, "questTemp.TPZ_Tavern_1") && npchar.city == "BasTer")
			{
				dialog.text = "실례합니다, "+GetAddress_Form(NPChar)+", 하지만 오늘은 술 한 방울도 줄 수 없습니다.";
				Link.l1 = "뭐라고? 럼 한 방울도 못 내주는 선술집이 어디 있나? 내가 네 술창고를 다 비워버린 대단한 잔치라도 놓친 건가?";
				Link.l1.go = "TPZ_Tavern_1";
				pchar.questTemp.TPZ_Tavern_1 = true;
				DelLandQuestMark(npchar);
				break;
			}
			//<-- Торговля по закону

			if(NPChar.quest.meeting == "0")
			{
				dialog.Text = GetNatPhrase(npchar,LinkRandPhrase("나의 소박한 선술집에 오신 것을 환영합니다 '"+XI_ConvertString(NPChar.City+"TavernName")+", 나리. 다시 뵙게 되어 기쁩니다.","명령만 내리십시오, 나리! 우리 선술집 '"+XI_ConvertString(NPChar.City+"TavernName")+"' 우리는 언제나 새로운 방문객을 환영합니다.","여기 처음이십니까, 나리? 망설이지 마십시오, 이곳 '"+XI_ConvertString(NPChar.City+"TavernName")+"' 언제나 집에 온 것처럼 느껴지지!'"),LinkRandPhrase("들어오시오, 선장 나리. 내가 아는 얼굴이 아니니, 이곳에 처음 오신 것이겠구려 '"+XI_ConvertString(NPChar.City+"TavernName")+"'.","처음 뵙겠습니다, 나리. 인사드리죠: 저는 "+GetFullName(npchar)+"", "'의 주점 주인"+XI_ConvertString(NPChar.City+"TavernName")+"'.","우리의 새로운 손님을 환영하게 되어 기쁩니다, 선장 나리! 제 선술집 '"+XI_ConvertString(NPChar.City+"TavernName")+"' 첫 잔은 항상 공짜야! 이곳의 주인은 나지, "+GetFullName(npchar)+", 당신을 환영합니다."),LinkRandPhrase("선장 나리! 선술집에 오신 것을 환영합니다 '"+XI_ConvertString(NPChar.City+"TavernName")+"'!'","오, 우리 선술집에 이렇게 빛나는 이달고 나리께서 찾아오셨군요 '"+XI_ConvertString(NPChar.City+"TavernName")+"! 여기가 처음이십니까, 나리?","좋은 아침이오, 나리! 나는 "+GetFullName(npchar)+", '의 소박한 주인"+XI_ConvertString(NPChar.City+"TavernName")+", 여기 오신 것을 환영합니다!"),LinkRandPhrase("안녕하세요, 카피텐 나리. 저는 선술집 '의 주인입니다"+XI_ConvertString(NPChar.City+"TavernName")+"'. 처음 우리와 함께 머무는 건가?","안녕하세요, 나리. 선술집 '"+XI_ConvertString(NPChar.City+"TavernName")+"'.","만나서 정말 반갑습니다, 카피텐 나리! 우리만의 선술집 '"+XI_ConvertString(NPChar.City+"TavernName")+"' 인사드립니다! 럼, 와인, 아니면 혹시 유혹해도 된다면, 새로 들어온 장난스러운 네덜란드 술 진도 있습니다?"));
				Link.l1 = LinkRandPhrase("아늑한 곳이군... 내 소개를 하지 - "+GetFullName(pchar)+", 만나서 반갑소.",""+GetFullName(pchar)+", 만나서 반갑군. 그래서, 나한테 뭘 제안할 수 있지?","내 이름은 "+GetFullName(pchar)+" 그리고 나는 이 항구에 처음 왔어. 말해 봐, 이 선술집은 뭐로 제일 유명하지?");
				Link.l1.go = "meeting";
				NPChar.quest.meeting = "1";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_tavern")
				{
					dialog.text = "이봐, 룸바! 항해에서 돌아온 거야, 아니면 새로 떠나는 거야?";
					link.l1 = "안녕하세요, "+npchar.name+". 그냥 들렀을 뿐이야.";
					Link.l1.go = "Helen_meeting";
					NPChar.quest.meeting = "1";
					break;
				}
				NPChar.quest.meeting = "1";
			}
			else
			{
				// Квестовый генератор священника. Квест №1. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_1.CurPortManColony + "_tavern")
		        {
		            if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NoMoneyToBarmen"))
		            {
		            	iTemp = sti(PChar.GenQuest.ChurchQuest_1.MoneyToBarmen);
		            	dialog.Text = "그래서, 선장님, 나에게 가져왔소 "+FindRussianMoneyString(iTemp)+".";
		            	if(sti(PChar.Money) >= iTemp)
		            	{
							link.l1 = "그래, 가지고 있지. 여기 있어...";
							link.l1.go = "Tavern_ChurchGenQuest1_Node_4_1";
						}
						else
						{
							link.l1 = "아니, 아직 못 했어...";
							link.l1.go = "exit";
						}
		            }
		            else
		            {
		            	dialog.Text = "무엇을 원하시오, 착한 "+GetSexPhrase("나리","숙녀")+"?";
						link.l1 = "저기 저 테이블에 있는 내 친구에게 럼 한 병 가져다줘.";
						link.l1.go = "Tavern_ChurchGenQuest1_Node_1";
					}
					break;
				}
				// <-- Квестовый генератор священника. Квест №1.
				dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("오, 귀한 손님들! 이봐, 너 거기 좀 비켜서 용감한 선장님 자리를 내줘라! 어서 안 그러면 내가 내쫓아 버릴 테니까, 하하!","자비로우신 하느님! 이게 누구야 "+GetFullName(pchar)+"! 최고의 와인이 막 들어왔소, 어서 들어오시오!","오, "+GetAddress_Form(NPChar)+", 무슨 문제라도 있나? 내가 치료해 주지. 이 병은 내가 쏘는 거야. 믿어, 이 근방에서 제일 좋은 와인이니까..."),LinkRandPhrase("오, 선장이군 "+GetFullName(pchar)+"! 이봐, 너! 훌륭하신 선장님께 예의를 좀 보여라! 여긴 헛간이 아니야! 선장님, 실례를 용서해 주십시오. 저 녀석들 어머니가 예절을 안 가르쳤나 봅니다.","오, 이런, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! 오늘 밤은 길겠구나, 하하! 아가씨들, 제일 멋진 드레스 입어야 할 거야!","좋은 오후입니다, "+GetFullName(pchar)+", 다시 뵙게 되어 기쁩니다! 제발, 나리, 부탁이 있습니다. 방금 새 탁자를 샀으니 오늘 밤에는 싸우지 말아 주십시오."),LinkRandPhrase("안녕하세요, 선장님. 편하게 계시되, 이곳에서는 샤프 선장조차도 예의를 지킨다는 점을 명심하십시오.","오호호! 이게 누구야! 바로 "+GetFullName(pchar)+" 자네가 직접 왔군! 자네 없는 동안 우리도 슬슬 심심해질 뻔했지! 내가 럼주 한 통 새로 따는 동안, 동료들에게 모험담 하나 들려주는 게 어때, 선장?","오-호-호! 이건 "+GetFullName(pchar)+" 자기 자신이군! 또다시 당신의 대단한 모험담으로 내 손님들을 바다로 끌고 가려는 건 아니겠지?")),LinkRandPhrase(LinkRandPhrase(""+GetFullName(pchar)+"! 이 늙은 뱃사람은 당신이 자기 가게에 와서 항상 반갑소! 자, 나리, 앉으시고 아가씨들이 곧 모실 겁니다!","편하게 앉으십시오, 선장님! 언제나 제일 좋아하는 손님을 맞이하게 되어 기쁩니다. 무엇을 드시겠습니까?","다시 만나서 반갑소, "+GetFullName(pchar)+"! 혼자만의 테이블을 원하십니까? 아니면 바에 앉으시겠습니까?"),LinkRandPhrase("안녕하세요, 선장님. 바람이 차가운데, 방금 만든 훌륭한 뱅쇼 한 잔을 대접하겠습니다. 공짜입니다!","안녕하세요, 선장님 "+GetFullName(pchar)+"! 다시 찾아와 주셔서 반갑소. 무엇을 원하시오?","당신이 와서 기쁩니다, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! 저희 누추한 가게를 찾아주셔서 정말 기쁩니다! 손님을 만족시키기 위해 최선을 다하고 있습니다."),LinkRandPhrase("선장님! 어서 오십시오, 어서 오십시오! 루이 왕께서도 드실 만한 훌륭한 단주 와인이 있는데, 특별히 선장님을 위해 아껴두었습니다!",""+GetFullName(pchar)+"! 와 주셔서 정말 기쁩니다. 이 바다 쥐들을 모두 쫓아낼까요, 아니면 그냥 두는 게 좋으신가요? 믿으십시오, 원하신다면 선생님을 위해 이 선술집을 전부 비워드릴 수 있습니다!","맙소사, 선장님이 오셨군\n "+GetFullName(pchar)+"! 이봐, 바람둥이들아 - 선장님 식탁에 제일 좋은 식탁보 가져와라!")));
				Link.l1 = pcharrepphrase(RandPhraseSimple(RandPhraseSimple("오, 여기서 내가 아직 기억되고 있군... 이봐, 내 잔 좀 채워 줘, 친구. 내가 좀 둘러보는 동안...","진정해, 친구야. 오늘은 기분이 좋거든. 우선 럼부터 시작하자, 어때?..."),RandPhraseSimple("오... 내가 여기 있어서 별로 반갑지 않은 거야? 내가 잘못 들은 거였으면 좋겠네, 하!","이봐. 네 인사보다 네 와인이 더 낫길 바란다. 아니면 나 화낼지도 몰라...")),RandPhraseSimple(RandPhraseSimple("늘 찾아와서 반갑다, 친구야. 짠내 나는 놈을 데워줄 만한 게 뭐 있냐?","아, 당신네 가게는 날이 갈수록 더 좋아지는군! 여기 올 때마다 항상 즐겁소..."),RandPhraseSimple("늙은 방랑자를 잊지 않았구나? 영광이야, 친구.","오랜 친구를 다시 보니 반갑군... 아직 럼 좀 남아 있나?")));
				Link.l1.go = "step_node";
			}
			break;
				
			case "step_node":
				dialog.Text = LinkRandPhrase("듣고 있소, 선장님.","내 주점 '"+XI_ConvertString(NPChar.City+"TavernName")+"선장님, 명령만 내리십시오!","듣고 있어, 선장! 오늘은 뭘 원해?");
				Link.l1 = "이 섬에 바다에서 운을 시험해 볼 준비가 된 소년들이 있나?";
				Link.l1.go = "crew hire";
				Link.l2 = "질문 몇 가지에 답해 줄 수 있을 거라 기대했소.";
				Link.l2.go = "int_quests";
				if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l21 = "재정 문제에 대해 상의하고 싶습니다.";
					link.l21.go = "LoanForAll";//(перессылка в кредитный генератор)
				}
				
				// Квестовый генератор священника. Квест №2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
		            	{
					link.l10 = LinkRandPhrase("최근 교회에서 일어난 도둑질에 대해 아는 게 있습니까?","최근 교회에서 일어난 강도 사건에 대해 뭐 알고 있나?","최근 교회에서 일어난 강도 사건에 대해 들은 거 있어?");
					link.l10.go = "Tavern_GenQuest_Church_2_1";
				}
				// <-- Квестовый генератор священника. Квест №2.
				
				//Jason --> генератор Неудачливый вор
				if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_tavern" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
				{
					link.l16 = "이 식민지에서 당신이 모르는 게 없다고들 하더군. 내가 사고 싶은 게 있어 "+pchar.GenQuest.Device.Shipyarder.Type+", 그리고 당신네 마을에서 그게 팔렸다고 들었소. 누군가가 길거리 시장에서 그것을 팔고 있었다고 하더군. 혹시 그 일에 대해 아는 게 있소?";
					link.l16.go = "Device_Tavern";
				}
				// <-- генератор Неудачливый вор
			
				//Jason --> генератор Место под солнцем
				if (CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && pchar.GenQuest.Sunplace.Trader == "continue" && NPChar.location == pchar.GenQuest.Sunplace.Trader.CityT + "_tavern")
				{
					link.l17 = "이름이 알려진 사기꾼을 찾고 있어 "+pchar.GenQuest.Sunplace.Trader.Enemyname+". 그를 어디서 찾을 수 있지?";
					link.l17.go = "Sunplace_Tavern";
				}
				// <-- генератор Место под солнцем
			
				// --> Голландский гамбит
				if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "JacobOnMain" && NPChar.location == pchar.questTemp.HWIC.Holl.JacobCity + "_tavern")
				{
					link.l18 = "안녕하세요, "+npchar.name+". 제이콥 반 베르흐를 찾아야 하는데, 어디 있지? 당신네 선술집에서는 안 보이는데...";
					link.l18.go = "HWICHollJacob_Tavern";
				}
				if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "start" && NPChar.nation == SPAIN && !CheckAttribute(npchar, "quest.HWICTalked"))
				{
					link.l18 = "안녕, "+npchar.name+". 나는 페르난도 로드리게스라는 카바예로를 찾고 있소. 그가 당신네 마을에 나타난 적 있소?";
					link.l18.go = "HWICSelfFernando_Tavern";
				}
				// <-- Голландский гамбит
			
				//Jason --> гонки на гидропланах
				if (CheckAttribute(pchar, "GenQuest.Racing.Go.Advantage") && NPChar.location == pchar.GenQuest.Racing.Go.StartCity + "_tavern")
				{
					link.l19 = "내가 맡겨둔 내 상금을 받으러 왔다네. "+npchar.name+".";
					link.l19.go = "Race_Advantage";
				}
				// <-- гонки на гидропланах
			
				//Jason --> захват пассажиров
				if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "take" && NPChar.location == pchar.GenQuest.Marginpassenger.Targetcity+"_tavern")
				{
					link.l20 = "나는 이름이 이런 사람을 어디서 찾을 수 있는지 궁금했소 "+pchar.GenQuest.Marginpassenger.q2Name+"? 그가 당신 마을에 살고 있어.";
					link.l20.go = "Marginpassenger";
				}
				// <-- захват пассажиров
				if(!CheckAttribute(pchar,"questTemp.TimeLock"))
				{
					link.l3 = pcharrepphrase("공짜 방 있냐, 이봐?","빈 방 있소? 여기서 잠시 머물고 싶소.");
					link.l3.go = "room";
				}
				Link.l4 = "아, 나는 이미 떠나고 있소, "+NPChar.name+". 또 보자.";
				Link.l4.go = "exit";
		break;
		
		case "Helen_meeting":
			dialog.Text = "아, 그래, 어서 들어와, 어서 들어와. 여긴 언제나 환영이야.";
			link.l1 = "네, 감사합니다. 만나서 반가웠습니다. 안녕히 가십시오.";
			link.l1.go = "exit";
			Link.l2 = "새로운 선원이 좀 필요해. 하지만 쓸만한 녀석들인지 꼭 확인해, 알겠지?";
			Link.l2.go = "crew hire";
			link.l3 = "단단한 땅에서 쉬면서 생각을 정리하고 싶지만, 어머니가 집 안을 분주히 돌아다니는 동안에는 그럴 수 없지.";
			link.l3.go = "Helen_room";
			Link.l4 = "뭐 좀 물어봐도 될까? ";
			Link.l4.go = "quests";
			link.l5 = " 너와 상의할 일이 있어, "+NPChar.name+".";
			link.l5.go = "Helen_rumours_tavern";
		break;
		
		case "Meeting":
			// Квестовый генератор священника. Квест №1. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_1.CurPortManColony + "_tavern")
	        {
	            dialog.Text = "무엇을 원하십니까, 은혜로운 분 "+GetSexPhrase("나리","아가씨")+"?";
				link.l1 = "저기 저 테이블에 있는 내 동료에게 럼주 한 병 갖다 주시오.";
				link.l1.go = "Tavern_ChurchGenQuest1_Node_1";
				break;
			}
			// <-- Квестовый генератор священника. Квест №1.
			dialog.Text = LinkRandPhrase("듣고 있소, 선장님.","무엇을 드릴까요, 선장님?","그래서, 선장님, 어떻게 하시겠습니까?");
			Link.l1 = "선원들이 필요해, "+NPChar.name+".";
			Link.l1.go = "crew hire";
			Link.l2 = NPChar.name+", 이야기 좀 하자...";
			Link.l2.go = "int_quests";
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l21 = "재정 문제에 대해 논의하고 싶습니다.";
				link.l21.go = "LoanForAll";//(перессылка в кредитный генератор)
			}
			// Квестовый генератор священника. Квест №2. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
	        {
				link.l10 = LinkRandPhrase("최근 교회에서 있었던 강도 사건에 대해 아는 게 있습니까?","최근 교회에서 일어난 강도 사건에 대해 아는 게 뭐지?","최근 교회에서 일어난 강도 사건에 대해 들은 소식 있나?");
				link.l10.go = "Tavern_GenQuest_Church_2_1";
			}
			// <-- Квестовый генератор священника. Квест №2.
			
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_tavern" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l16 = "이 식민지에서 당신이 모르는 게 없다고들 하더군. 내가 사고 싶은 게 있어\n "+pchar.GenQuest.Device.Shipyarder.Type+", 그리고 그게 당신네 마을에서 팔렸다고 들었소. 누군가 거리에서 그걸 팔고 있었다고 하더군. 혹시 그 일에 대해 아는 게 있소?";
				link.l16.go = "Device_Tavern";
			}
			// <-- генератор Неудачливый вор
			
			//Jason --> генератор Место под солнцем
			if (CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && pchar.GenQuest.Sunplace.Trader == "continue" && NPChar.location == pchar.GenQuest.Sunplace.Trader.CityT + "_tavern")
			{
   				link.l17 = "이름이 알려진 갈취범에 대해 말해 보시오 "+pchar.GenQuest.Sunplace.Trader.Enemyname+". 그를 어디서 찾을 수 있지?";
				link.l17.go = "Sunplace_Tavern";
			}
			// <-- генератор Место под солнцем
			
			//--> Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "JacobOnMain" && NPChar.location == pchar.questTemp.HWIC.Holl.JacobCity + "_tavern")
				{
					link.l18 = "안녕하세요, "+npchar.name+". 제이콥 반 베르흐를 찾아야 하는데, 어디 있지? 당신네 선술집엔 안 보이는데...";
					link.l18.go = "HWICHollJacob_Tavern";
				}
				if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "start" && NPChar.nation == SPAIN && !CheckAttribute(npchar, "quest.HWICTalked"))
				{
					link.l18 = "안녕하세요, "+npchar.name+". 나는 페르난도 로드리게스라는 카바예로를 찾고 있소. 그가 당신네 마을에 도착했소?";
					link.l18.go = "HWICSelfFernando_Tavern";
				}
				//<-- Голландский гамбит
				
				//Jason --> гонки на гидропланах
				if (CheckAttribute(pchar, "GenQuest.Racing.Go.Advantage") && NPChar.location == pchar.GenQuest.Racing.Go.StartCity + "_tavern")
				{
					link.l19 = "내가 딴 돈을 받으러 왔어, 네가 잘 보관하고 있던 그 돈 말이야. "+npchar.name+".";
					link.l19.go = "Race_Advantage";
				}
				// <-- гонки на гидропланах
				//Jason --> захват пассажиров
				if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "take" && NPChar.location == pchar.GenQuest.Marginpassenger.Targetcity+"_tavern")
				{
					link.l20 = "나는 이름이 이런 사람을 어디서 찾을 수 있을지 궁금했어 "+pchar.GenQuest.Marginpassenger.q2Name+"? 그가 당신 마을에 살고 있어.";
					link.l20.go = "Marginpassenger";
				}
				// <-- захват пассажиров
			if(!CheckAttribute(pchar,"questTemp.TimeLock"))
			{
				link.l3 = pcharrepphrase("공짜 방 있냐, 이 친구?","빈 방 있습니까? 잠시 여기 머물고 싶습니다.");
				link.l3.go = "room";
			}
			Link.l4 = "나중에 다시 오도록 하지.";
			Link.l4.go = "exit";
		break;
		
		case "crew hire":
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			ok = sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok;
			
			if (!ok)
			{
				Dialog.text = "선장, 선원들은 왜 필요하신 거요? 항구에 당신 배는 안 보이는데.";
				link.l1 = RandPhraseSimple("정말이지... 내가 잘못된 곳에 정박했었지.","항구에 들어가는 걸 깜빡했네...");
				link.l1.go = "exit";
				break;
			}
			
            if (makeint(environment.time) > 22.0 || makeint(environment.time) < 7.0)
			{
				Dialog.text = "보통은 선원이 되려는 사람들이 많지만, 지금은 너무 늦었소. 아침이 되면 그들이 나타나기 시작할 거요.\n혹시 방을 빌려서 그들을 기다릴 생각이오?";
				link.l1 = "알겠소. 빈 방이 있소?";
				link.l1.go = "room";
				link.l2 = "지금은 방에 관심 없어. 또 보자.";
				link.l2.go = "exit";
			}
			else
			{
                if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
                {
                    Dialog.text = "여기가 수배범을 대접하는 곳인 줄 아나? 내가 경비병을 부르지 않는 것만도 감사하게 생각해.";
					link.l1 = "고마워.";
					link.l1.go = "exit";
                }
                else
                {
					if (pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_tavern") // Блеквуд в городе
					{
						Dialog.text = "선장님, 오늘은 선술집에 사람 그림자도 없습니다. 갈 만한 사람들은 모두 블랙우드 선장과 함께 갔습니다.";
						link.l1 = "그거 안타깝군!";
						link.l1.go = "exit";
						break;
					}
					if (CheckAttribute(NPChar, "CrewHired.PGGId") && GetNpcQuestPastDayParam(NPChar, "CrewHired") < 3 && GetCrewQuantity(rColony) == 0)
					{
						Dialog.text = "아, 미안하오 선장님, 조금 늦으셨소. 항해하려던 녀석들은 모두 용감한 선장과 이미 배를 탔지. "+GetFullName(CharacterFromID(NPChar.CrewHired.PGGId))+".";
						link.l1 = "안타깝군!";
						link.l1.go = "exit_crew";
					}
					else
					{						
						if(bPartitionSet)
						{		
							if(GetPartitionAmount("CrewPayment") > 0)
							{
								if(IsEquipCharacterByArtefact(pchar, "totem_07"))
								{
									DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
									NextDiag.CurrentNode =  NextDiag.TempNode;
									DialogExit();
									LaunchHireCrew();							
								}
								else
								{
									dialog.text = "선장님, 사람들이 당신이 꽤 인색하다고들 하더군요. 여기서 당신 선원으로 들어가고 싶어 하는 사람은 아무도 없습니다.";
									link.l1 = "그렇군...";
									link.l1.go = "exit";
								}
							}
							else
							{
								DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
								NextDiag.CurrentNode =  NextDiag.TempNode;
								DialogExit();
								LaunchHireCrew();	
							}
						}	
						else
						{
							DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
							NextDiag.CurrentNode =  NextDiag.TempNode;
							DialogExit();
							LaunchHireCrew();							
						}						
					}
				}
			}
		break;
		
		case "exit_crew" :
			DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
			NextDiag.CurrentNode =  NextDiag.TempNode;
			DialogExit();
			LaunchHireCrew();
		break;
	////////////////////////////////////////////////////////=============================================///////////////////////////////////////////////////////	
        case "int_quests":
			dialog.text = "잘 듣고 있네.";
			//link.l1 = "일자리를 찾고 있어. 도와줄 수 있나?";
			//link.l1.go = "work";
			//homo 15/06/06 слухи
			link.l2 = LinkRandPhrase("최근 소식 좀 들려줄 수 있나?","이 땅에서는 무슨 일이 벌어지고 있지?","육지에는 무슨 소식이 있나?");
			link.l2.go = "rumours_tavern";
			//homo
			link.l3 = "나는 다른 일로 왔다.";
			link.l3.go = "quests";
			if(CheckAttribute(pchar,"GenQuest.EncGirl"))
			{
				if(pchar.GenQuest.EncGirl == "EncGirlFack_fighted")
				{
					link.l5 = "어디서 내가 찾을 수 있는지 아시오 "+pchar.GenQuest.EncGirl.name+"?";
					link.l5.go = "EncGirl_1";
				}	
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					link.l6 = "어디에서 찾아볼 수 있는지 말해줄 수 있나 "+pchar.GenQuest.EncGirl.sLoverId+"?";
					link.l6.go = "EncGirl_3";
				}
				if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "tavern_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
				{
					link.l7 = "이봐, 네 아들이 초대해서 왔다."; 
					link.l7.go = "EncGirl_4";
					pchar.quest.EncGirl_GetLoverFather.over = "yes";
				}
			}
			if(CheckAttribute(pchar,"GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.City && CheckAttribute(pchar,"GenQuest.CaptainComission.Speak_Tavern"))
			{
				if(pchar.GenQuest.CaptainComission.variant == "A0")
				{												
					if(pchar.GenQuest.CaptainComission.Speak_Tavern == true)
					{
						link.l9 = "그래서, 본 적 있나  "+pchar.GenQuest.CaptainComission.Name+"?";
						link.l9.go = "CaptainComission_3";
					}
					else
					{
						link.l9 = "어디에서 찾아봐야 하는지 알려줄 수 있습니까  "+pchar.GenQuest.CaptainComission.Name+"?";
						link.l9.go = "CaptainComission_1";
					}
				}	

				if(pchar.GenQuest.CaptainComission.variant == "A2" && pchar.GenQuest.CaptainComission == "Begin_1")
				{
					link.l9 = "순찰대 선장을 어디서 찾을 수 있는지 아시오 "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+"?";
					link.l9.go = "CaptainComission_Tavern7";					
				}				
				if(pchar.GenQuest.CaptainComission.variant == "A3" && pchar.GenQuest.CaptainComission == "Begin_1")
				{
					if(pchar.GenQuest.CaptainComission.Speak_Tavern == true)
					{
						link.l9 = "그래서, 본 적 있나 "+GetName(NAMETYPE_ORIG,pchar.GenQuest.CaptainComission.CanoneerName,NAME_NOM)+"?";
						link.l9.go = "CaptainComission_3";
					}
					else
					{					
						link.l9 = "순찰대 선장에 대해 아는 게 있나 "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+"?";
						link.l9.go = "CaptainComission_Tavern1";
						if(!CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour"))
						{
							pchar.GenQuest.CaptainComission.GetRumour = true;
							SaveCurrentQuestDateParam("GenQuest.CaptainComission.GetRumour");
						}	
					}	
				}					
			}
			if(CheckAttribute(pchar,"GenQuest.Hold_GenQuest") && NPChar.city == pchar.GenQuest.Hold_GenQuest.City && pchar.GenQuest.Hold_GenQuest.Speak_Tavern == false )
			{
				link.l10 = "혹시 이름이 이런 남자를 어디서 찾을 수 있는지 알려주실 수 있습니까 "+pchar.GenQuest.Hold_GenQuest.Name+"?";
				link.l10.go = "hold_genquest1";
			}
			if (CheckCharacterItem(pchar, "CaptainBook") && CheckAttribute(pchar, "questTemp.different.GiveShipLetters") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakTavern") && (pchar.questTemp.different.GiveShipLetters.city == npchar.city))
			{
				link.l11 = "나는 이 근처에서 우연히 어떤 선박 서류를 발견했어....";
				link.l11.go = "ShipLetters_4";			
			}

			// Jason --> квест губера на поиск дезертира
			if(CheckAttribute(pchar, "GenQuest.FindFugitive") && pchar.GenQuest.FindFugitive != "Late" && sti(NPChar.nation) == PIRATE)
			{
				link.l12 = "이봐, 내 오랜 친구를 찾고 있는데, "+pchar.GenQuest.FindFugitive.Name+" 그게 그의 이름이오. 다른 선장이 그가 당신네 정착지로 향한다고 말해 주었소. 혹시 그를 만난 적 있소?";
				link.l12.go = "FindFugitiveTav";
			}
			//<-- поиск дезертира

			link.l15 = "아니요, 괜찮습니다.";
			link.l15.go = "exit";
		break;
		
		case "hold_genquest1":
			switch(sti(pchar.GenQuest.Hold_GenQuest.TavernVariant))
			{
				case 0:
					dialog.text = LinkRandPhrase("뭐라고 했지? "+pchar.GenQuest.Hold_GenQuest.Name+"? 흠... 그런 사람은 들어본 적 없어.","그가 정말 우리 마을 출신이 맞소? 그런 사람은 들어본 적도 없는데.","우리 작은 식민지엔 그런 사람 없었어. 내가 여기 있는 동안 한 번도 들어본 적 없어.");
					link.l1 = "확실한가?";
					link.l1.go = "hold_genquest2";					
				break;
				
				case 1: 
					switch (hrand(3))
					{
						case 0:
							pchar.GenQuest.Hold_GenQuest.foundStr = "the church";						
							pchar.GenQuest.Hold_GenQuest.found = "church";
						break;
						case 1:
							if (npchar.city != "Panama")
							{
							pchar.GenQuest.Hold_GenQuest.foundStr = "the shipyard";						
							pchar.GenQuest.Hold_GenQuest.found = "shipyard";
							}
							else
							{
								pchar.GenQuest.Hold_GenQuest.foundStr = "the church";						
								pchar.GenQuest.Hold_GenQuest.found = "church";
							}
						break;
						case 2:
							pchar.GenQuest.Hold_GenQuest.foundStr = "the usurer";												
							pchar.GenQuest.Hold_GenQuest.found = "bank";
						break;
						case 3:
							pchar.GenQuest.Hold_GenQuest.foundStr = "the shop";						
							pchar.GenQuest.Hold_GenQuest.found = "store";
						break;
					} 
					dialog.text = "확인해봐 "+pchar.GenQuest.Hold_GenQuest.foundStr+", 그는 거기서 자주 볼 수 있어.";
					link.l1 = "고맙소, 바로 그렇게 하겠소.";
					link.l1.go = "hold_genquest3";				
				break;
				
				case 2:
					dialog.text = LinkRandPhrase(RandPhraseSimple("뭐라고 했지? "+pchar.GenQuest.Hold_GenQuest.Name+"? 흠... 그런 사람은 들어본 적이 없네. 정말 우리 마을 출신이 맞나? 그런 사람은 한 번도 들어본 적이 없어.","헤헤... 이제는 주님만이 그 자를 어디서 찾아야 할지 아실 거야 - 지옥일지 천국일지. 1년 넘게 전에 죽었는데도 아직도 사람들이 그에 대해 묻고 있지... 불쌍한 놈, 쉴 틈도 없구만..."),RandPhraseSimple("그를 거기서는 찾을 수 없을 거요 - 적어도 이승에서는 말이오. 얼마 전에 죽었소 - 황열병 때문이었지... 신이여, 그의 영혼을 편히 쉬게 하소서... 참으로 강인한 사내였는데! 젊었을 때는 위대한 모험가였소! 하지만 죽음이 찾아오면, 할 수 있는 게 별로 없지...","오, 그가 그리웠나? 그는 이곳을 오래전에 떠났지. 어디로 갔는지 아무도 몰라 — 북아메리카 식민지로 갔을 수도 있고, 유럽으로 돌아갔을 수도 있지. 그냥 짐을 챙겨서 훌쩍 떠나버렸어."),"오, 그걸 찾고 있나 "+pchar.GenQuest.Hold_GenQuest.Name+" 누가 부자가 돼서 뉴잉글랜드에 집을 샀는지 알아? 예전에 내가 그에게 럼주를 외상으로 팔던 시절이 있었지 - 아직도 내 돈을 안 갚았어. 사람들은 정말 고마움을 모른다니까.");
					link.l1 = "알겠소. 그래도 고맙소.";	
					link.l1.go = "hold_genquest4";
				break;
				
				case 3:
					dialog.text = "글쎄, 선술집 말고 어디서 그를 찾겠어? 거기 단골이거든 – 술로 죄를 씻는 놈이지, 허허. 좀 있다가 다시 와. 그가 나타나면 기다리라고 전해줄게.";	
					link.l1 = "고맙소, 그렇게 하겠소.";
					link.l1.go = "hold_genquest5";
				break;
			}
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern = true;
		break;
		
		case "hold_genquest2":
			dialog.text = "여기 있는 사람들을 다 직접 아는데 어떻게 모를 수가 있겠어. 내가 이 선술집을 운영한 지 벌써 몇 해째인데. "+"나는 그놈들을 별별 꼴로 다 봤지. 가끔은 아내가 남편을 데리러 오고, 때로는 지들끼리 나가고, 어떤 때는 내가 직접 내쫓아야 했어. '내가 확실하냐고?!' 당연히 확실하지!";
			link.l1 = "뭐, 어쨌든 고맙다...";	
			link.l1.go = "exit";
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			AddQuestRecord("HoldQuest", "7");
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName);
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;
		
		case "hold_genquest3":
			Hold_GenQuest_GenerateChar();		
			AddQuestRecord("HoldQuest", "8");
			AddQuestUserData("HoldQuest", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.City + "Gen")); 			
			AddQuestUserData("HoldQuest", "sFoundChar", pchar.GenQuest.Hold_GenQuest.foundStr);
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.Name);
			SetFunctionTimerConditionParam("Hold_GenQuest_FindCharTimeIsOver", 0, 0, 1, MakeInt(24 - GetHour()), false);
			DialogExit();
		break;
		
		case "hold_genquest4":
			AddQuestRecord("HoldQuest", "13");
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName);
			AddQuestUserData("HoldQuest", "sNameChar", pchar.GenQuest.Hold_GenQuest.Name);
			AddQuestUserData("HoldQuest", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("HoldQuest");
			DeleteAttribute(pchar,"GenQuest.Hold_GenQuest");			
			DialogExit();
		break;
		
		case "hold_genquest5":
			SetFunctionTimerConditionParam("Hold_GenQuest_GetMapTimeIsOver", 0, 0, 1, MakeInt(24 - GetHour()), false);
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_GenerateMapChar");			
		break;
		
		case "CaptainComission_1":
			dialog.text = LinkRandPhrase("여기는 자주 오는 사람이지만, 지금은 없네. 가끔씩 다시 와 보게나 - 그가 나타나면 여기서 기다리라고 전해주겠네.","그 사람은 여기 자주 오는 손님이오. 나중에 다시 오면 분명히 여기서 만날 수 있을 거요.","가끔씩 다시 오시오 - 그는 여기 자주 오는 손님이오. 당신이 그를 찾았다고 전해 주겠소.");
			link.l1 = "감사합니다, 나중에 다시 오겠습니다...";
			link.l1.go = "CaptainComission_2";
			pchar.GenQuest.CaptainComission.Speak_Tavern = true;
		break;
		
		case "CaptainComission_2":
			pchar.quest.CapComission_ExitFromTavern.win_condition.l1 = "ExitFromLocation";
			pchar.quest.CapComission_ExitFromTavern.win_condition.l1.location = pchar.location;
			pchar.quest.CapComission_ExitFromTavern.function = "CaptainComission_GenerateChar";

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "CaptainComission_3":
			dialog.text = "그가 이미 여기 왔으니, 근처 어딘가에 있을 거야...";
			link.l1 = "고맙다.";
			link.l1.go = "exit";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.Speak_Tavern");
		break;
		
		case "CaptainComission_Tavern1":
			pchar.GenQuest.CaptainComission.Speak_Tavern = true;
			dialog.text = "그를 모르는 사람이 있겠소? 온 마을이 벌써 며칠째 그에 대해 떠들고 있소.";
			link.l1 = "더 자세히 말해 줄 수 있겠소?";
			link.l1.go = "CaptainComission_Tavern2";
		break;
		
		case "CaptainComission_Tavern2":
			dialog.text = "조금요. 선장은 처형당했고, 그의 선원 중 몇몇도 마찬가지였소. 나머지는 계급과 지위를 빼앗긴 채 카리브 해 곳곳에 흩어졌지... 무엇 때문에? 판사 말로는, 순찰 중에 해적 한 놈을 침몰시키고 전리품을 혼자 챙겼다고 하더군\n"+"문제는 말이야, 이 배의 주인도 화물도 아직 못 찾았다는 거야 ... 현지 만과 작은 만들을 샅샅이 뒤지고 있지만, 아무 소득이 없어.";
			link.l1 = "뭐야, 선원들 중 아무도 은닉처 위치를 말하지 않았다고?";	
			link.l1.go = "CaptainComission_Tavern3";	
		break;
		
		case "CaptainComission_Tavern3":
			dialog.text = "한 놈도 없었소! 고문을 당해도 마찬가지였지! 아직도 왜 총독이 그 모함을 그렇게 쉽게 믿었는지 이해가 안 가오. 선장 "+pchar.GenQuest.CaptainComission.Name+" 평판이 좋았고, 그의 선원들은 잘 훈련되고 규율이 엄격했으니, 어느 제독이라도 부러워할 만한 일이었지.";
			link.l1 = "그럼 살아남은 선원들은 어디서 찾아야 하지?";
			link.l1.go = "CaptainComission_Tavern4";
		break;
		
		case "CaptainComission_Tavern4":
			dialog.text = "그건 나도 몰라 - 놈들이 사방으로 흩어졌거든... 하지만... 아직 한 놈 남아 있긴 해. 그렇지만 그 녀석한테서 뭘 알아낼 수 있을지는 의문이야. 머리를 심하게 다쳤거든. 있잖아, 그 녀석은 포수로 일했어 \n "+pchar.GenQuest.CaptainComission.Name+". 그 사고가 있은 지 이틀 뒤, 그는 한 만에서 의식을 잃은 채 발견되었소.\n처음에는 병원으로 보내져 영웅 대접을 받으며 치료를 받았지만, 사건이 복잡해지자 그를 감옥에 집어넣고 심문하려 했소.\n그러다 결국 우선 치료부터 받아야 한다고 판단했지.";
			link.l1 = "지금도 아직 여기 있나?";
			link.l1.go = "CaptainComission_Tavern5";
		break;
		
		case "CaptainComission_Tavern5":
			pchar.GenQuest.CaptainComission.CanoneerName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			dialog.text = "그래, "+GetName(NAMETYPE_ORIG,pchar.GenQuest.CaptainComission.CanoneerName,NAME_NOM)+" 그게 그의 이름이야. 가끔 들러서 구걸해서 번 푼돈을 럼주에 쓰지. 불쌍한 영혼이지. 내가 그를 보면 여기서 너를 기다리라고 말해줄게.";
			link.l1 = "고맙소, 나중에 다시 오겠소.";
			link.l1.go = "CaptainComission_Tavern6";
		break;
		
		case "CaptainComission_Tavern6":
			AddQuestRecord("CaptainComission2", "39");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); 
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sCharName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_ABL));
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);			
			SetFunctionExitFromLocationCondition("CaptainComission_GenerateCanoneer", pchar.location, false);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "CaptainComission_Tavern7":
			DeleteAttribute(pchar,"GenQuest.CaptainComission.Speak_Tavern");
			dialog.text = "내가 그를 아냐고? 물론 알지. 그런데 그 사람을 왜 찾는 거지?";
			link.l1 = "나는 그와 볼 일이 있어...";
			link.l1.go = "CaptainComission_Tavern8";
		break;
		
		case "CaptainComission_Tavern8":
			dialog.text = ""+GetAddress_Form(pchar)+", 그 '사업'은 조심해야 해. "+pchar.GenQuest.CaptainComission.Name+" 해적 혐의로 구금되어 있고, 지금 총독의 부하들이 섬 전체를 뒤지며 그의 공범들을 찾고 있다.";
			link.l1 = "정말이야! 그래서 그는 뭘 했지?";
			link.l1.go = "CaptainComission_Tavern9";
		break;
		
		case "CaptainComission_Tavern9":
			dialog.text = "그게 사실인지 아닌지는 모르겠지만, 지나가던 해적선에서 압수한 화물을 몰래 숨기고 보고하지 않았다는 소문이 돌고 있어. 그런데도 아직 그 해적도, 화물도 아무도 못 찾았지. 도대체 왜 총독이 그 중상모략을 그렇게 쉽게 믿는지 아직도 이해가 안 돼. 선장\n "+pchar.GenQuest.CaptainComission.CapName+"  평판도 괜찮았고, 훌륭한 군인이었지. 내 말을 믿어도 돼, "+GetAddress_Form(pchar)+".";
			link.l1 = "경고해 줘서 고맙다. 또 보자.";
			link.l1.go = "CaptainComission_Tavern10";
		break;
		
		case "CaptainComission_Tavern10":
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour"))
			{
				pchar.GenQuest.CaptainComission.GetRumour = true;
				SaveCurrentQuestDateParam("GenQuest.CaptainComission.GetRumour");
				SetFunctionTimerConditionParam("CaptainComission_TimeIsOver", 0, 0, 2, MakeInt(24 - GetHour()), false);
				AddQuestRecord("CaptainComission2", "19");
				AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); // лесник окончание
				AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			}			
			DialogExit();
		break;
				
		case "EncGirl_1":
			dialog.text = "그녀가 왜 필요하지?";
			link.l1 = "나는 그녀와 볼일이 있어...";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "우리 정착지 남자들 절반은 그 여자랑 볼일이 있는 것 같아. 우리 여자들이 그 여자를 잡으면, 벌거벗긴 채로 마을 문 밖에 내던져 버릴 거야.";
			link.l1 = "뭐, 그렇지 뭐... "+GetSexPhrase("그럼 내가 긴 줄에 합류한 셈이군. \n 뭐, 또 누가 그녀를 찾으러 오면 내 뒤에 줄 서라고 전해줘.","알겠어")+"...";
			link.l1.go = "exit";
			pchar.quest.EncGirl_SpeakTavernKeeper.over = "yes";
			DeleteAttribute(pchar, "GenQuest.EncGirl");
		break;
		
		case "EncGirl_3":
			dialog.text = "여기는 자주 오는 사람이야 - 보통 일거리를 찾으러 오는데, 지금은 없어. 가끔씩 다시 와 봐 - 그가 오면 여기서 기다리라고 전해줄게.";
			link.l1 = "감사합니다, 나중에 다시 오겠습니다...";
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "FindingLover";
			pchar.quest.EncGirl_ExitTavern.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_ExitTavern.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_ExitTavern.function = "EncGirl_GenerateLover";
		break;
		
		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "오, 그럼 네가 "+GetSexPhrase("데려온 그 선장","데려온 그 아가씨")+" 내 방탕한 아들이 어린 신부와 함께라니?";
				link.l1 = "그래, 내가 도왔지.";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "오, 거기 "+GetSexPhrase("그분이 바로 우리 은인이야","그녀가 바로 우리 은인이야")+". 보상을 기대하고 있는 거지?";
				link.l1 = "글쎄, 보상은 없어도 괜찮아. 네 고마움만으로도 충분해.";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "제 아들이 어려움에 처했을 때 버리지 않고, 난처한 상황에서 벗어날 수 있도록 도와주셔서 진심으로 감사드립니다. 감사를 표하고자 하오니, 이 소박한 금액과 제 작은 선물을 받아주십시오.";
			link.l1 = "감사합니다. 이 젊은 커플을 도운 건 제 기쁨이었습니다.";
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = "고맙다고? 무슨 고마움?! 저 멍청이가 백수로 빈둥거린 지 벌써 반년이나 됐어 - 그런데 바람 피울 시간은 있단 말이지! 내가 저 나이였을 땐 이미 내 사업을 하고 있었어! 푸흣! 총독한테는 혼기 찬 딸도 있는데, 저 얼간이는 혈육도 없는 계집애를 내 집에 데려와서는 감히 내 축복을 달라고 하다니!";
			link.l1 = "처음 보는 순간 사랑에 빠진다는 걸 믿지 않는 거지?";
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
			dialog.text = "사랑? 사랑이라고!? 나를 놀리는 거야, 아니면 멍청한 거야? 젊은 것들의 변덕을 받아주고 포주처럼 행동하다니, 부끄러운 줄 알아라! 네가 한 일은 그저 한 소녀를 집에서 데려온 것뿐만 아니라 내 아들의 인생까지 망쳐 놓은 거다. 너한테 고마울 일은 전혀 없어. 이만 가라.";
			link.l1 = "그쪽도 마찬가지군.";
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
				
		case "ShipLetters_4":
			pchar.questTemp.different.GiveShipLetters.speakTavern = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "내가 한번 볼게! 흠... 하지만 너도 선장이잖아. 이건 항만 관리인에게 직접 가서 물어보는 게 좋겠어.";
				link.l1 = "조언해 주셔서 감사합니다.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "내가 좀 볼게! 오! 이름을 보니, 이건 내 후원자 중 한 분의 것이네, 꽤 존경받는 신사지. 내가 직접 이 서류들을 주인에게 전달할 수 있네. 나에게 줄 생각인가?";
				link.l1 = "다시 생각해 보니...";
				link.l1.go = "exit";
				link.l2 = "가져가시오. 도움이 될 수 있어서 기쁩니다.";
				link.l2.go = "ShipLetters_end";				
			}	
		break;
		
		case "ShipLetters_end":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "3");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters"); 
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//zagolski. переделка
		case "work":
			if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
				dialog.text = RandPhraseSimple("나는 누구를 섬기든 상관없어, 돈에는 국적이 없으니까. 하지만 너는 그 깃발 아래에서 왔으니 도와주지 않겠다. "+NationNameGenitive(sti(pchar.nation))+".","나는 그저 평범한 선술집 주인일 뿐이지만, 함께 일하는 것은 "+NationNameAblative(sti(pchar.nation))+" 나한텐 별로 매력 없어 보여.");
				link.l1 = RandPhraseSimple("그래, 원하는 대로 하시지...","그래, 원하는 대로 해...");
				link.l1.go = "exit";
				break;
			}
			if (isBadReputation(pchar, 40))
			{
				dialog.text = RandPhraseSimple("여긴 보통 승객이 많지. 그래도 네 배를 타겠다고 할 얼간이 하나도 없을 거라고 본다. 네 악명은 이미 자자하거든. 그런 악당이랑 같이 항해할 바보만이 네 배에 오르겠지.","상인들이 호위를 부탁하러 자주 찾아오긴 하지. 하지만 네 악명이 이미 소문이 자자해서, 나는 누구에게도 너를 추천할 생각이 없어. 내 명성도 중요하거든. 누가 양치기 대신 이리에게 양을 맡기고 싶겠냐?");
				link.l1 = RandPhraseSimple("아, 정말로, 그런 소문 다 믿지 말아야 해...","알겠소. 모두를 조용히 시키는 건 쉽지 않지.","요즘 사람들은 너무 물러터졌어...");
				link.l1.go = "exit";
				break;
			}
			if (sti(Pchar.Ship.Type) == SHIP_NOTUSED)
        	{
				dialog.text = "그런데 네 배는 어디 있지? 아니면 승객들을 등에 업고 헤엄쳐 가려고 하는 거냐?";
				link.l1 = "이봐, 네 말도 일리가 있네...";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "해적 정착지나 적국의 항구에 가는 게 두렵지 않다면 일거리가 있을지도 몰라. 특별히 찾는 게 있나?";
			link.l1 = "그건 문제가 되지 않을 거요. 호위를 제공할 수 있을 것 같소.";
			link.l1.go = "work_1";
			link.l2 = "승객이 있소? 돈만 내면 원하는 곳 어디든 데려다 줄 수 있소.";
			link.l2.go = "work_2";
			link.l3 = "아니, 그런 일은 내 일이 아니야. 고마워.";
			link.l3.go = "exit";
		break;

		case "work_1":
				dialog.text = "보통 나한테 호위 임무를 묻진 않아. 선술집에 있는 상인들에게 물어봐 – 어쩌면 네 도움이 필요할지도 몰라.";
				link.l1 = "좋소, 말씀대로 하겠습니다.";
                link.l1.go = "exit";
		break;

		case "work_2":
			if (!CheckAttribute(npchar, "work_date") || GetNpcQuestPastDayParam(npchar, "work_date") >= 2 || bBettaTestMode)
    		{					
				if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 5)//при низком авторитете не даем
				{
					dialog.text = "죄송하지만, 당신과 함께 여행할 사람은 없습니다.";
					link.l1 = "알겠네.";
					link.l1.go = "exit";
					break;
				}
		         // пассажир
				if (hrand(6) > 1)
				{
					dialog.Text = "방금 들어온 남자가 있어 – 최근에 지나가는 배에 대해 묻고 있었지. 원하면 그와 이야기해 봐.";
					link.l1 = RandPhraseSimple("그 자가 누구지? 혹시 불한당인가? 아니면, 더 나쁘게는 수배 중인 해적이란 말인가?","그자는 누구지? 그 사람 때문에 문제 생길 일 있나?");
					Link.l1.go = "PassangerAreYouSure";
				}
				else
				{
					dialog.text = "아니, 오늘은 아무도 그것에 대해 묻지 않았어. 아마 다른 날에나 물어보겠지.";
					link.l1 = RandPhraseSimple("글쎄, 거기 없다면 없는 거지...","운도 지지리도 없군... 뭐, 그럼 이만 보자.");
					link.l1.go = "exit";
				}
            }
    		else
    		{
				dialog.text = "오늘은 아무도 없어. 며칠 뒤에 다시 와.";
				link.l1 = "좋소, 말씀대로 하겠소.";
                link.l1.go = "exit";
    		}
        break;

        case "ConvoyAreYouSure":
		    dialog.text = LinkRandPhrase("누가 알겠어? 네가 물었으니 내가 대답했지.","글쎄, 그건 네가 해결해야 할 일이야. 거기 있는 누구도 내가 보증하지 않아.","여긴 별별 인간들이 다 와. 여긴 선장님, 주점이지 총독 저택이 아니라고.");
			Link.l1 = "고맙다, 그럼 흥정하자.";
			Link.l1.go = "exit";
			pchar.quest.destination = findTraderCity(npchar);
			pchar.ConvoyQuest.City = npchar.city;
			AddDialogExitQuest("prepare_for_convoy_quest");
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
        break;

        case "PassangerAreYouSure":
		    dialog.text = LinkRandPhrase("누가 알겠어? 네가 물었고, 내가 대답했지.","글쎄, 이건 네가 해결해야 할 일이야. 거기 있는 누구도 내가 보증하지 않아.","여긴 별별 인간들이 다 와. 여긴 선장님, 주점이지 총독 저택이 아니야.");
			Link.l1 = "알겠어. 이 남자가 누구인지 알아보자...";
			Link.l1.go = "exit";
			sGlobalTemp = findPassangerCity(npchar);
			pchar.GenQuest.GetPassenger_City = npchar.city;
			AddDialogExitQuest("prepare_for_passenger_quest");
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
        break;

		 case "fight":
			DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Helen_room":
			dialog.text = "물론이지, 헬렌. 얼마나 머무를 거야? 그리고 뭐야, 또 그 늙은 글래디스랑 다퉜어?";
			if(!isDay())
			{
				link.l1 = "아침까지 그냥 자고 싶어. 지금 집에 가면 분명히 그녀를 깨울 거야.";
				link.l1.go = "Helen_room_day";
			}
			else
			{
				link.l1 = "아니, 아니야, 난 그냥 밤에 출항해야 해서 그녀를 깨우고 싶지 않아.";
				link.l1.go = "Helen_room_night";
				link.l2 = "푹 자고 천천히 일어나고 싶어. 오늘 하루 방을 빌릴게.";
				link.l2.go = "Helen_room_day_next";
			}
		break;

		case "room":
   			if (chrDisableReloadToLocation || CheckAttribute(pchar, "GenQuest.TavernClose")) //кто-то должен подойти к ГГ.
			{
				dialog.text = "방이 사용 중이오, "+GetAddress_Form(NPChar)+", 내가 너를 위해 해줄 수 있는 건 없어.";
				link.l1 = "글쎄, 그거 참 아쉽군...";
				link.l1.go = "exit";
				break;
			}
			// суп из черепахи
			if (CheckAttribute(pchar, "questTemp.Terrapin.Room_close") && npchar.location == "Tortuga_tavern")
			{
				dialog.text = "앙리 티보 나리께서 지금 그 방을 빌리고 계시고, 한 달 치를 미리 지불하셨으니, 선장님께 해드릴 수 있는 게 없습니다.";
				link.l1 = "음, 그거 안타깝군...";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "cave" && npchar.location == "Tortuga_tavern")
			{
				dialog.text = "방이 사용 중이오, "+GetAddress_Form(NPChar)+", 내가 너를 위해 해줄 수 있는 건 없어.";
				link.l1 = "음, 그거 참 아쉽군...";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "shore" && npchar.location == "Baster_tavern") // 070712
			{
				dialog.text = "방이 사용 중입니다, "+GetAddress_Form(NPChar)+", 내가 너를 위해 해줄 수 있는 건 없어.";
				link.l1 = "음, 그거 안됐군...";
				link.l1.go = "exit";
				break;
			}
			if (pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_tavern") // Блеквуд в городе
			{
				Dialog.text = "유감이지만, 아니오, 선장님. 모든 방은 블랙우드와 그의 부하들이 차지했습니다.";
				if (CheckAttribute(pchar, "questTemp.LadyBeth_TavernRoomDialog"))
				{
					link.l1 = "아, 정말 안타깝군!";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = "모든 방? 여기 방이 한 개 이상 있다는 거야?";
					link.l1.go = "LadyBeth_Room";
				}
				break;
			}
			//-->> квест официантки
			if (pchar.questTemp.different == "FackWaitress_toRoom")
			{
				dialog.text = "방을 빌리고 싶어? 문제없지. 100에잇만 내면 네 거야.";
				if (sti(pchar.money) >= 100)
				{
					link.l1 = "여기 네 돈이다.";
					link.l1.go = "exit";
					AddMoneyToCharacter(pchar, -100);
					LocatorReloadEnterDisable(npchar.city + "_tavern", "reload2_back", false);
					pchar.questTemp.different = "FackWaitress_toRoomUp";
				}
				else
				{
					link.l1 = "흠... 나중에 다시 오지...";
					link.l1.go = "exit";
				}
				break;
			}
			if (pchar.questTemp.different == "FackWaitress_toRoomUp")//квест официантки
			{
				dialog.text = "방은 전부 당신 차지요. 들어와서 편히 쉬세요.";
				link.l1 = "고마워, 친구.";
				link.l1.go = "exit";
				break;
			}
			//<<-- квест официантки
			// --> квест "A damsel in the jungle"
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && npchar.city == pchar.GenQuest.EncGirl.city)
			{
				if(pchar.GenQuest.EncGirl == "EncGirl_ToTavern")
				{
					dialog.text = "방을 빌리고 싶어? 문제없지. 100에이트만 내면 네 거야.";
					if (sti(pchar.money) >= 100)
					{
						link.l1 = "여기 네 돈이다.";
						link.l1.go = "exit";
						AddMoneyToCharacter(pchar, -100);
						LocatorReloadEnterDisable(npchar.city + "_tavern", "reload2_back", false);
						pchar.GenQuest.EncGirl = "EncGirl_toRoomUp";
					}
					else
					{
						link.l1 = "흠... 나중에 다시 오지...";
						link.l1.go = "exit";
					}
					break;
				}
				if (pchar.GenQuest.EncGirl == "EncGirl_toRoomUp")//квест  по спасению тетки в пампасах
				{
					dialog.text = "방은 전부 당신 겁니다. 들어와서 편히 쉬세요.";
					link.l1 = "고마워, 친구.";
					link.l1.go = "exit";
					break;
				}
			}
			// <-- квест "A damsel in the jungle"

			// belamour постоялец -->
			if (CheckAttribute(pchar, "GenQuest.Unwantedpostor") && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && abs(50-sti(pchar.reputation.nobility)) > 20)
			{
				if(pchar.GenQuest.Unwantedpostor == "start")
				{
					SetFunctionTimerCondition("Unwantedpostor_OneDay", 0, 0, 1, false);
					pchar.GenQuest.Unwantedpostor = "timer";
				}
				dialog.text = "실례합니다, 선장님, 안타깝게도 지금 빈 방이 없습니다. 손님이 나가지도 않고요. 아직 돈도 안 줬습니다...";
				link.l1 = "공용실에서 밤을 보내야 할 것 같군...";
				link.l1.go = "Unwantedpostor_hall_day_wait";
				link.l2 = "미안해. 다른 얘기하자.";
				link.l2.go = "int_quests";
				if(pchar.GenQuest.Unwantedpostor != "Lose")
				{
					link.l3 = "그럼 경비병을 불러. 이런 손님이 다 있나? 돈도 안 내고, 나가려고도 하지 않잖아...";
					link.l3.go = "Unwantedpostor";
				}
				break;
			}
			//<-- постоялец

			dialog.text = "여기 얼마나 머물 계획이오?";
			if(!isDay())
			{
				link.l1 = "아침까지.";
				link.l1.go = "room_day";
			}
			else
			{
				link.l1 = "밤이 될 때까지.";
				link.l1.go = "room_night";
				link.l2 = "다음 아침까지.";
				link.l2.go = "room_day_next";
			}
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1 && !CheckAttribute(pchar, "questTemp.MarySexBlock"))
			{
				pchar.questTemp.MarySexBlock = true;
				SetTimerFunction("Mary_DeleteSexBlock", 0, 0, 1);
			}
		break;

		case "room_day":
			if (CheckAttribute(pchar, "questTemp.OS_Tavern_FreeBuhlo") && npchar.id == "PuertoPrincipe_tavernkeeper")
			{
				dialog.text = "방은 마음껏 쓰십시오, 선장님. 완전히 무료입니다.";
				link.l1 = "고마워, 친구.";
				link.l1.go = "room_day_wait";
				link.l3 = "지금은 아니야. 다른 얘기하자.";
				link.l3.go = "int_quests";
				break;
			}
			dialog.text = "그건 8레알 5개가 들 거요.";
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = "거래지. 자, 여기 있어.";
				link.l1.go = "room_day_wait";
			}
			link.l2 = pcharrepphrase("그 가격에? 왕실 방이라도 빌리는 거야? 차라리 공용실에서 공짜로 자겠어.","아, 지금 내 형편으론 침대에서 잘 사치는 누릴 수 없겠군. \n공터 벤치에서 자야 할 모양이야.");
			link.l2.go = "hall_day_wait";
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				link.l3 = "지금은 아니야. 화제를 바꾸자.";
				link.l3.go = "int_quests";
			}
		break;

		case "room_day_next":
			if (CheckAttribute(pchar, "questTemp.OS_Tavern_FreeBuhlo") && npchar.id == "PuertoPrincipe_tavernkeeper")
			{
				dialog.text = "방은 선장님 마음대로 쓰십시오. 완전히 무료입니다.";
				link.l1 = "고마워, 친구.";
				link.l1.go = "room_day_wait_next";
				link.l3 = "지금은 아니야. 다른 얘기하자.";
				link.l3.go = "int_quests";
				break;
			}
			dialog.text = "그건 10에이트 동전이 들 거야.";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "거래 성사다. 자, 여기 있어.";
				link.l1.go = "room_day_wait_next";
			}
			link.l2 = pcharrepphrase("그 가격에? 왕실 방이라도 빌리는 거야? 차라리 공용실에서 공짜로 자겠어.","아, 침대에서 자는 호사는 지금 내 형편으로는 누릴 수 없겠군. \n이제는 그냥 공용실 벤치에서 자야 할 것 같아.");
			link.l2.go = "hall_day_wait";
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				link.l3 = "지금은 아니야. 화제를 바꾸자.";
				link.l3.go = "int_quests";
			}
		break;

		case "room_night":
			if (CheckAttribute(pchar, "questTemp.OS_Tavern_FreeBuhlo") && npchar.id == "PuertoPrincipe_tavernkeeper")
			{
				dialog.text = "방은 선장님 마음대로 쓰십시오. 완전히 무료입니다.";
				link.l1 = "고마워, 친구.";
				link.l1.go = "room_night_wait";
				link.l3 = "지금은 아니야. 다른 얘기하자.";
				link.l3.go = "int_quests";
				break;
			}
			dialog.text = "그건 8리알 5개가 들 거야.";
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = "거래 성사다. 자, 여기 있어.";
				link.l1.go = "room_night_wait";
			}
			link.l2 = pcharrepphrase("그 가격에? 왕실 방이라도 빌리는 거야? 차라리 공용실에서 공짜로 자겠어.","아아, 지금 내 형편으론 침대에서 자는 호사는 누릴 수 없겠군. \n이제 공용실 벤치에서 자야 할 모양이야.");
			link.l2.go = "hall_night_wait";
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				link.l3 = "지금은 아니야. 화제를 바꾸자.";
				link.l3.go = "int_quests";
			}
		break;

		case "room_night_wait":
			// belamour прерывание ночной приключенец -->
			if(CheckAttribute(pchar,"GenQuest.NightAdventureId"))
			{
				if(GetCharacterIndex(pchar.GenQuest.NightAdventureId) != -1)
				{
					sld = characterFromId(pchar.GenQuest.NightAdventureId);
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
				SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
			}
			// <-- прерывание ночного приключенца 
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -5);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_night");
		break;

		case "hall_night_wait":
			if (hRand(3) == 1)
            {
                Dialog.text = "어서 꺼져, 이 악당아! 공용실은 무료지만, 최소한의 예의는 지켜야 할 거 아니야!";
				link.l1 = "알았어, 알았어, 나 간다.";
				link.l1.go = "exit";
            }
            else
            {
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				TavernWaitDate("wait_night");
			}
		break;

		case "room_day_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -5);
			AddDialogExitQuest("sleep_in_tavern");
			// belamour прерывание ночной приключенец -->
			if(CheckAttribute(pchar,"GenQuest.NightAdventureId"))
			{
				if(GetCharacterIndex(pchar.GenQuest.NightAdventureId) != -1)
				{
					sld = characterFromId(pchar.GenQuest.NightAdventureId);
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
				SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
			}
			// <-- прерывание ночного приключенца 
			if (CheckAttribute(pchar, "GenQuest.LigaAttack") && hrand(1) == 1)
			{
				TavernWaitDate("wait_night");
				pchar.GenQuest.LigaAttack.Go = "true"; //атака киллеров
			}
			else TavernWaitDate("wait_day");
		break;

		case "room_day_wait_next":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -10);
			AddDialogExitQuest("sleep_in_tavern");
			// belamour прерывание ночной приключенец -->
			if(CheckAttribute(pchar,"GenQuest.NightAdventureId"))
			{
				if(GetCharacterIndex(pchar.GenQuest.NightAdventureId) != -1)
				{
					sld = characterFromId(pchar.GenQuest.NightAdventureId);
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
				SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
			}
			// <-- прерывание ночного приключенца 
			if (CheckAttribute(pchar, "GenQuest.LigaAttack") && hrand(1) == 1)
			{
				TavernWaitDate("wait_night");
				pchar.GenQuest.LigaAttack.Go = "true"; //атака киллеров
			}
			else TavernWaitDate("wait_day");
		break;

		case "hall_day_wait":
			if (hrand(1) == 1)
            {
                Dialog.text = "여기서 당장 꺼져, 이 악당아! 공동 거실은 공짜일지 몰라도, 최소한의 예의는 지켜야 할 거 아니야!";
				link.l1 = "알았어, 알았어, 나 간다.";
				link.l1.go = "exit";
            }
            else
            {
				// belamour прерывание ночной приключенец -->
				if(CheckAttribute(pchar,"GenQuest.NightAdventureId"))
				{
					sld = characterFromId(pchar.GenQuest.NightAdventureId);
					ChangeCharacterAddressGroup(sld, "none", "", "");
					SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
				}
				// <-- прерывание ночного приключенца
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				TavernWaitDate("wait_day");
			}
		break;
		
		case "tavern_keeper":
			NextDiag.TempNode = "First time";

			dialog.text = "지금 당장 내 선술집에서 이런 무례한 짓 그만두지 않으면 경비병을 부를 거야!";
			link.l1 = "알았어, 알았어, 나 간다.";
			link.l1.go = "exit_sit";
		break;

		case "exit_sit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");
		break;
		
		//******************* ноды квеста священника. поиск грабителей (квест № 2)**********************
		case "Tavern_GenQuest_Church_2_1":
			dialog.text = "나도 그건 잘 모르겠어... 손님들에게 직접 물어보는 게 좋을 거야.";
			link.l1 = "알겠소, 고맙소.";
			link.l1.go = "exit";
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen");
		break;
			
		//******************* ноды квеста священника. вернуть рукописи (квест № 1)**********************
		case "Tavern_ChurchGenQuest1_Node_1":
			dialog.text = "외상으로는 서비스를 제공하지 않아. "+GetSexPhrase("나리","아가씨")+".";
			link.l1 = "나는 좋은 돈으로 지불한다. 이제 금이나 은은 받지 않는 거야?";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_2";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_2":
			dialog.text = "미안하오, "+GetSexPhrase("나리","아가씨")+" 선장님, 하지만 당신 친구가 빚이 있어서, 저는 그게...";
			link.l1 = "덜 생각하고 더 빨리 일해. 이제, 내 용감한 친구가 너한테 얼마나 빚졌지?";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_3";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_3":
			iTemp = (rand(3)+1)*100;
			PChar.GenQuest.ChurchQuest_1.MoneyToBarmen = iTemp;
			if(rand(1) == 0) // "If he's a simple one and pays right away"
			{
				dialog.text = FindRussianMoneyString(iTemp)+", 아가씨"+GetSexPhrase("테르","s")+" 선장님, 그리고 그 자는 교회 책 몇 권도 전당포에 맡겼습니다 - 가진 것이라곤 그게 전부였고, 그나마 약간의 가치가 있었지요.";
				if(sti(PChar.money) >= iTemp)
				{
					link.l1 = "여기 네 돈이다. 원고를 내놔라. 그리고 조심히 다뤄라 - 이건 외설스러운 삽화책이 아니라 성서다!";
					link.l1.go = "Tavern_ChurchGenQuest1_Node_4_1";
				}
				else
				{
					link.l1 = "잠깐만 기다려... 금방 돈 가지고 올게\n";
					link.l1.go = "exit";
					PChar.GenQuest.ChurchQuest_1.NoMoneyToBarmen = true;
				}
			}
			else // "If he's not a simple one"
			{
				dialog.text = FindRussianMoneyString(iTemp)+", 아가씨"+GetSexPhrase("터","s")+" 선장.";
				link.l1 = "나는 그의 빚을 갚고 그가 담보로 남긴 것은 뭐든지 가져가겠다.";
				link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2";
			}
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_1":
			DialogExit();
			AddMoneyToCharacter(PChar, -sti(PChar.GenQuest.ChurchQuest_1.MoneyToBarmen));
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen");
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "8");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"));
			AddQuestUserData(sQuestTitle, "sName", GetFullName(CharacterFromID("ChurchGenQuest1_Cap")));
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 2, false);
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2":
			dialog.text = "아니요, 아가씨"+GetSexPhrase("테르","s")+", 그렇게는 안 될 거야.";
			link.l1 = "무슨 말이오 - '그렇게는 안 된다'니? 선장의 빚은 갚았으니 그 사람은 괜찮고, 자네는 돈을 돌려받았으니 괜찮고, 내가 그의 담보를 받았으니 나도 괜찮지. 모두 괜찮은데, 왜 '그렇게는 안 된다'는 거요?";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_1";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_1":
			dialog.text = "왜냐하면, 아가씨"+GetSexPhrase("테르","s")+" 선장님, 저는 돈이 필요 없습니다. 그 선장을 너무 잘 알기 때문에, 애초에 그가 제게 돈을 갚거나 이 원고들을 가져갈 거라고는 전혀 기대하지 않았습니다.";
			link.l1 = "돈이 필요 없다는 게 무슨 말이오? 애초부터 이 책들을 가질 생각이었단 말이오? 그런데 왜, 도대체 신의 이름으로 왜 그러는 거요?!";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_2";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_2":
			dialog.text = "신의 이름으로 - 바로 그거요, 그래서 그렇소, 아가씨"+GetSexPhrase("테르","s")+". 내 어린 아들이 심하게 아팠소, 그래서 아내와 나는 주님께서 아이의 열병을 고쳐 주신다면 교회에 헌금을 하겠다고 맹세했지요. 주님의 자비는 끝이 없어서, 내 아들은 지금 살아 있고 건강하오. 이제 우리는 맹세를 지켜야 하오. 그리고 딱 좋은 때군요, 선장님\n "+PChar.GenQuest.ChurchQuest_1.CapFullName+" 나타나서는 이 교회 책들을 전당포에 맡기더군. 나는 그런 불경함, 즉 하나님의 말씀으로 술값을 치르는 짓을 용납할 수 없었지. 그래서 이 책들을 우리 교구의 목사님께 넘기기로 결정했네.";
			link.l1 = "음, 분명 선한 일임에는 틀림없지만, 이 책들은 사실 다른 신부님의 소유라는 것도 알아두셔야 합니다. 사실 신부님일 뿐만 아니라, 주교님이자 저의 영적 지도자이기도 하지요. 그분께서 훔친 교회 재산을 기부하는 자가 있다면 노하시고 저주를 내릴 수도 있습니다. 제가 이 책들을 당신에게서 사서 안전하게 본국으로 가져가고 싶습니다. 당신은 그 돈을 본당에 기부하셔도 됩니다. 하나님께서도 똑같이 기뻐하실 겁니다.";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_3";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_3":
			dialog.text = "Mis"+GetSexPhrase("터","s")+"... 아가씨"+GetSexPhrase("테르","s")+" 선장님... 물론입니다, 저는 전혀 몰랐습니다! 당장 돌려드리겠습니다, 그리고 돈도 전혀 요구하지 않겠습니다. 주교님께 저희를 위해 한 말씀만 해주십시오 - 혹시 축복을 내려주시고 저희의 서약도 풀어주실 수 있을지...";
			link.l1 = "당연히 당신의 맹세는 지켜진 것으로 간주될 것이오! 결국, 당신은 이익을 포기하고 책을 정당한 주인에게 돌려주었으니 말이오. 어느 교회인지는 중요하지 않소, 신은 오직 한 분이고 거룩한 가톨릭 사도 교회도 하나뿐이니 그렇지 않소? 좋아요, 책을 내게 주시오. 행운을 빌겠소...";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_4";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_4":
			DialogExit();
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			AddMoneyToCharacter(PChar, -sti(PChar.GenQuest.ChurchQuest_1.MoneyToBarmen));
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen");
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "9");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown)); // belamour gen
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 2, false);
		break;
		
		//Jason --> генератор Неудачливый вор
		case "Device_Tavern":
			dialog.text = "흠, "+pchar.GenQuest.Device.Shipyarder.Type+"? 전에 들어본 적 없는데... 그게 대체 뭐지? 내가 살아오면서 그런 건 한 번도 들어본 적 없어.";
			link.l1 = "글쎄, 그건 조선공의 도구야, "+pchar.GenQuest.Device.Shipyarder.Describe+". 그런 제안을 한 사람이 있었소?";
			link.l1.go = "Device_Trader_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_Trader_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) == 6)
			{
				dialog.text = "흠... 그래, 이상한 녀석 하나가 분명히 그걸 나한테 가져왔지. 그게 뭔지는 말 안 하더군 – 그냥 술이랑 바꾸려고 했어. 물론 거절했지 – 그딴 장신구는 필요 없으니까.";
				link.l1 = "그 사람은 어떻게 생겼고, 어디로 갔지? 그 기구가 정말 꼭 필요하거든.";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "아니, 그런 건 아니야. 미안하지만 도와줄 수 없어. 주변에 물어봐.";
				link.l1 = "알겠어. 자, 이제 주변에 물어볼 시간이군!";
				link.l1.go = "exit";
			}
		break;
		// <-- генератор Неудачливый вор
		
		//Jason --> генератор Место под солнцем
		case "Sunplace_Tavern":
			if (makeint(environment.time) > 12.0 && makeint(environment.time) < 17.0)//в магазине
			{
				dialog.text = ""+pchar.GenQuest.Sunplace.Trader.Enemyname+"? 그가 최근에 거기 있었으니, 이제쯤이면 동료인 상인에게 갔을 거야. 상점에서 찾아봐. 분명히 거기 있을 거다.";
				link.l1 = "고마워! 네가 정말 큰 도움이 됐어!";
				link.l1.go = "Sunplace_Tavern_1";
			}
			else//ушел на рыбалку
			{
				dialog.text = ""+pchar.GenQuest.Sunplace.Trader.Enemyname+"? 오늘 아침 일찍, 그는 자신의 루거선을 타고 항해를 나갔어. 지금쯤이면 분명히 난간에 서서 경치를 감상하고 있을 거야. 그가 필요하다면 바다에서 찾아보거나 며칠 후 돌아올 때까지 기다려야 할 거야...";
				link.l1 = "고마워! 기다리지 않을게 - 바다에서 그를 찾는 게 더 쉬울 거야. 행운을 빌어!";
				link.l1.go = "Sunplace_Tavern_2";
			}
		break;
		
		case "Sunplace_Tavern_1"://магазин
			pchar.quest.Sunplace_Store.win_condition.l1 = "location";
			pchar.quest.Sunplace_Store.win_condition.l1.location = pchar.GenQuest.Sunplace.Trader.CityT + "_store";
			pchar.quest.Sunplace_Store.function = "Sunplace_CreateTrader";
			AddQuestRecord("Sunplace", "6");
			AddQuestUserData("Sunplace", "sName", pchar.GenQuest.Sunplace.Trader.Enemyname);
			AddQuestUserData("Sunplace", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Sunplace.Trader.CityT+"Gen"));
			DialogExit();
			pchar.GenQuest.Sunplace.Trader = "hunt";
		break;
		
		case "Sunplace_Tavern_2"://рыбалка
			pchar.GenQuest.Sunplace.Trader.IslandID = GetCharacterCurrentIslandId(npchar);
			pchar.GenQuest.Sunplace.Trader.EnemyNation = npchar.nation;
			pchar.quest.Sunplace_Sea.win_condition.l1 = "location";
			pchar.quest.Sunplace_Sea.win_condition.l1.location = pchar.GenQuest.Sunplace.Trader.IslandID;
			pchar.quest.Sunplace_Sea.function = "Sunplace_CreateTraderLugger";
			AddQuestRecord("Sunplace", "7");
			AddQuestUserData("Sunplace", "sName", pchar.GenQuest.Sunplace.Trader.Enemyname);
			AddQuestUserData("Sunplace", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Sunplace.Trader.CityT+"Gen"));
			DialogExit();
			pchar.GenQuest.Sunplace.Trader = "hunt";
		break;
		// <-- генератор Место под солнцем	
		
		// Jason --> Голландский гамбит
		case "HWICHollJacob_Tavern":
			dialog.text = "쉿... 왜 소리치고 있어? 그 사람은 한참이나 너를 기다렸어. 이미 럼주 한 쿼터를 다 마셨다구. 위층 방으로 올라가 봐, 거기서 그를 찾을 수 있을 거야.";
			link.l1 = "아, 그렇군. 아직 깨어 있길 바라지.";
			link.l1.go = "exit";
			LocatorReloadEnterDisable(pchar.questTemp.HWIC.Holl.JacobCity+"_tavern", "reload2_back", false);
			pchar.questTemp.HWIC.Holl = "JacobInRoom";
			AddDialogExitQuestFunction("Create_JacobVanBerg");
			DelLandQuestMark(npchar);
		break;
		
		case "HWICSelfFernando_Tavern":
			if (NPChar.location == pchar.questTemp.HWIC.Self.SpainCity +"_tavern")
			{
				//DelMapTonzagAllQM();
				dialog.text = "그래, 그 신사를 알아. 그 사람은 아마 마을 어딘가에 있을 거야 - 방금 전에 내 창문 앞을 지나가는 걸 봤거든.";
				link.l1 = "고마워! 내가 그를 찾아볼게!";
				link.l1.go = "Fernando_Land";
				/* if (makeint(environment.time) > 10.0 && makeint(environment.time) < 18.0)//на улице
				{
					dialog.text = "그래, 그 신사를 알아. 그 사람은 아마 마을 어딘가에 있을 거야 - 방금 전에 내 창문 앞을 지나가는 걸 봤거든.";
					link.l1 = "고마워! 내가 가서 그를 찾아볼게!";
					link.l1.go = "Fernando_Land";
				}
				else //в море
				{
					dialog.text = "그래, 그는 지금 우리 마을을 방문 중이야. 지금은 여기 없어 - 브리건틴을 타고 나갔거든. 아마 멀지 않은 곳, 우리 섬 주변 해역 어딘가에 있을 거야.";
					link.l1 = "고마워, 친구! 네 덕분에 정말 큰 도움 받았어!";
					link.l1.go = "Fernando_Sea";
				} */
				pchar.questTemp.HWIC.Self = "KillFernando";
			}
			else
			{
				dialog.text = "Fernando Rodriguez? 들어본 적 없어. 아니, 이 사람에 대해 아무것도 몰라.";
				link.l1 = "그렇군... 뭐, 수색은 계속된다...";
				link.l1.go = "exit";
			}
			npchar.quest.HWICTalked = "true";
		break;
		
		case "Fernando_Land":
			pchar.quest.HWIC_Fernando.win_condition.l1 = "location";
			pchar.quest.HWIC_Fernando.win_condition.l1.location = pchar.questTemp.HWIC.Self.SpainCity +"_town";
			pchar.quest.HWIC_Fernando.function = "CreateFernandoOnLand";
			AddQuestRecord("Holl_Gambit", "3-2");
			DialogExit();
		break;
		
		case "Fernando_Sea":
			pchar.questTemp.HWIC.Self.FernandoIslandID = GetCharacterCurrentIslandId(npchar);
			pchar.quest.HWIC_Fernando.win_condition.l1 = "location";
			pchar.quest.HWIC_Fernando.win_condition.l1.location = pchar.questTemp.HWIC.Self.FernandoIslandID;
			pchar.quest.HWIC_Fernando.function = "CreateFernandoOnSea";
			AddQuestRecord("Holl_Gambit", "3-3");
			DialogExit();
		break;
		//<-- Голландский гамбит
		
		//Jason --> гонки на гидропланах
		case "Race_Advantage":
			dialog.text = "네, 물론입니다. 축하합니다, 선장님. 이미 당신의 승리를 알고 있습니다. 여기 돈을 받으십시오.";
			link.l1 = "감사합니다, "+npchar.name+".";
			link.l1.go = "Race_Advantage_1";
		break;
		
		case "Race_Advantage_1":
			DialogExit();
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Racing.Go.Money)*2);
			AddQuestRecord("Racing", "4");
			AddQuestUserData("Racing", "sStartCity", XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.StartCity+"Gen"));
			CloseQuestHeader("Racing");
			DeleteAttribute(pchar, "GenQuest.Racing.Go");
		break;
		//<-- гонки на гидропланах
		
		//Jason --> захват пассажиров
		case "Marginpassenger":
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger.lose"))
			{
				dialog.text = "으으, 나리, "+pchar.GenQuest.Marginpassenger.q2Name+" 약 "+LinkRandPhrase("한 달","3주","두 달")+" 전에. "+LinkRandPhrase("갑작스레 열병으로 쓰러짐","그는 마을 입구에서 칼에 찔렸어 - 산적들이나 그 붉은 피부의 야만인들 짓이지\n","결투에서 총에 맞아 쓰러졌어")+"... 신께서 그의 영혼을 편히 쉬게 하시길...";
				link.l1 = "젠장!.. 그 사람의 그걸 내가 어쩌란 말이야... 뭐, 됐어. 정보 고마워. 또 보자, "+npchar.name+".";
				link.l1.go = "Marginpassenger_1";
			}
			else
			{
				dialog.text = ""+pchar.GenQuest.Marginpassenger.q2Name+"응, 그 사람 분명히 마을 어딘가에 있을 거야. 거리에서 찾아봐. 하지만 매일 정오까지는 총독 관저에 있고, 밤 아홉 시 이후에는 자기 집에 틀어박혀 있으니까 그 점 명심해.";
				link.l1 = "고마워! 내가 가서 그를 찾아볼게...";
				link.l1.go = "Marginpassenger_2";
			}
		break;
		
		case "Marginpassenger_1":
			DialogExit();
			AddQuestRecord("Marginpassenger", "7");
			AddQuestUserData("Marginpassenger", "sName2", pchar.GenQuest.Marginpassenger.q2Name);
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City));
			// belamour gen: Добряку недолго осталось -->
			if(CheckAttribute(pchar, "questTemp.LongHappy"))
			{
				AddQuestUserData("Marginpassenger", "sBaron", "to Puerto Principe, to the Black Pastor");
			}
			else
			{
				AddQuestUserData("Marginpassenger", "sBaron", "to Le Francois, to Kindly Jacques");
			}
			// <-- belamour gen
			pchar.GenQuest.Marginpassenger = "cabin";
		break;
		
		case "Marginpassenger_2":
			DialogExit();
			AddQuestRecord("Marginpassenger", "8");
			AddQuestUserData("Marginpassenger", "sName2", pchar.GenQuest.Marginpassenger.q2Name);
			pchar.GenQuest.Marginpassenger = "street";
		break;
		//<-- захват пассажиров
		
		//Jason --> поиск дезертира
		case "FindFugitiveTav":
			if (NPChar.city == pchar.GenQuest.FindFugitive.City && sti(pchar.GenQuest.FindFugitive.Chance) == 0)
			{
				dialog.text = NPCStringReactionRepeat("네 선장이 진실을 말한 것 같군. "+pchar.GenQuest.FindFugitive.Name+" 정말로 최근에 우리 정착지에 도착했소. 낮에는 거리에서 그를 찾아보시오 - 대개 빈둥거리며 시간을 보내고 있소.","그 남자에 대해 이미 나에게 물었고, 내가 아는 건 전부 말했잖아!","장난하는 거야, 아니면 진짜 바보야?! 같은 걸 벌써 세 번째나 묻고 있잖아!","어떻게 그런 바보가 선장이 될 수 있었는지, 생각만 해도 참...","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("고맙다, 친구야, 네가 큰 도움을 줬어!","그래, 그래, 알았어.","이런 젠장, 와, 그렇게 흥분하지 마라. 그냥 깜빡했을 뿐이야.","글쎄, 보다시피 그는 그렇게 했지...",npchar,Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("FindFugitiveTav_1", "exit", "", "", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = NPCStringReactionRepeat("아니, 친구야, 그 이름은 처음 듣는군. 여기저기 물어봐, 아는 놈이 있을지도 모르지...","그 남자에 대해 이미 나에게 물었고, 나는 말했잖아: 난 모른다고!","장난하는 거야, 아니면 진짜 바보인 거야?! 똑같은 걸 벌써 세 번째나 묻고 있잖아!","어떻게 그런 바보가 선장이 될 수 있었는지, 생각만 해도 어이가 없군...","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("알겠소. 그래도 고맙소.","그래, 그래, 알았어.","이런 젠장, 와, 그렇게 흥분하지 마. 그냥 깜빡했을 뿐이야.","글쎄, 보다시피 그는 그렇게 했지...",npchar,Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);	
			}
		break;
		
		case "FindFugitiveTav_1":
			DialogExit();
			AddQuestRecord("MayorsQuestsList", "12-1");
			sld = characterFromId("Fugitive");
			LAi_SetWarriorType(sld);
			LAi_warrior_DialogEnable(sld, true);
			sld.dialog.currentnode = "Fugitive_city";
			LAi_SetLoginTime(sld, 11.0, 18.0);
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.FindFugitive.City+"_town", "goto", "goto"+(rand(9)+1));
		break;
		//<-- поиск дезертира
		
		//--> Бремя гасконца
		case "Sharlie_crew":
			dialog.text = "안타깝지만, 지금은 도와줄 수 없네 - 내가 아는 사람 중에 자네 밑에서 일할 놈은 없어. 하지만 조언 하나 해주지 - 방금 자네 바로 뒤 테이블에 앉은 그 선원에게 말을 걸어보게. 그와 동료들은 방금 상선에서 막 내린 참이야. 어쩌면 자네와 함께 가겠다고 할지도 몰라.";
			link.l1 = "좋아, 그렇게 할게! 정말 고마워!";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "sailor";
			//усадим матроса Алонсо
			sld = GetCharacter(NPC_GenerateCharacter("SharlieSailor" , "Alonso", "man", "man", 10, FRANCE, -1, true, "quest"));
			sld.name = GetCharacterName("Alonso");
			sld.lastname = "";
			FantomMakeCoolFighter(sld, 10, 20, 20, "blade_05", "", "", 10);
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "Sharlie_sailor";
			sld.greeting = "town_sailor";
			AddLandQuestMark(sld, "questmarkmain");
			LAi_SetSitType(sld);
			LAi_SetImmortal(sld, true);
			FreeSitLocator("FortFrance_tavern", "sit7");
			ChangeCharacterAddressGroup(sld, "FortFrance_tavern", "sit", "sit7");
			AddQuestRecord("Sharlie", "6-1"); // mitrokosta
		break;
		
		case "Sharlie_skiper":
			dialog.text = "특별히 말해줄 수 있는 건 없어, 친구. 지금은 내 가게에 항해사들이 들르지 않아. 항구 쪽에서 물어봐 봐 – 아마 거기 사람들이 더 잘 알지도 몰라.";
			link.l1 = "알겠어. 좋아, 사람들이랑 이야기하러 갈게.";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "findskiper";
			//сгенерим наводчика
			sld = GetCharacter(NPC_GenerateCharacter("SharlieSkiperTalker", "citiz_"+(rand(19)+21), "man", "man", 10, FRANCE, -1, true, "marginal"));
			FantomMakeCoolFighter(sld, 10, 20, 20, RandPhraseSimple("blade_04","blade_06"), "", "", 10);
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "skipertalker";
			sld.greeting = "marginal";
			LAi_SetWarriorType(sld);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			ChangeCharacterAddressGroup(sld, "FortFrance_town", "patrol", "patrol"+(rand(13)+1));
			LAi_SetLoginTime(sld, 6.0, 21.99);
			AddLandQuestMark(sld, "questmarkmain");
		break;
		//<-- Бремя гасконца
		
		// Addon 2016-1 Jason пиратская линейка
		case "mtraxx_tortuga":
			sld = characterFromId("Tortuga_waitress");
            dialog.text = "곧바로 준비하겠습니다, 나리!.. 최고의 프랑스 와인입니다! "+sld.name+"! 제일 좋은 객실을 준비해라! 1000페소다, 나리.";
			link.l1 = "여기 있다.";
			link.l1.go = "mtraxx_tortuga_1";
		break;
		
		case "mtraxx_tortuga_1":
			AddMoneyToCharacter(pchar, -1000);
            DialogExit();
			pchar.questTemp.Mtraxx.Retribution = "room";
			pchar.quest.mtraxx_retribution_room.win_condition.l1 = "locator";
			pchar.quest.mtraxx_retribution_room.win_condition.l1.location = "Tortuga_tavern";
			pchar.quest.mtraxx_retribution_room.win_condition.l1.locator_group = "reload";
			pchar.quest.mtraxx_retribution_room.win_condition.l1.locator = "reload2_back";
			pchar.quest.mtraxx_retribution_room.function = "Mtraxx_RetributionToRoom";
		break;
		// belamour постоялец -->
		case "Unwantedpostor_hall_day_wait":
			if (hrand(1) == 1)
            {
                Dialog.text = "꺼져, 이 악당아! 돈 내고 오는 손님들 자리만 차지하고 있잖아!";
				link.l1 = "좋아, 알겠어... 나 간다.";
				link.l1.go = "exit";
            }
            else
            {
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				TavernWaitDate("wait_day");
			}
		break;
		
		case "Unwantedpostor":
				dialog.text = "그래, 그리고 내 경비병들이 사람들을 선술집에서 끌어내는 걸로 손님들 다 겁주라고? 그리고 내 손님들 중엔 군인들 근처에 있는 걸 싫어하는 사람들도 있어. 그런 거 보면 불안해하거든. 내 평판 망치고 싶지 않아...";
				link.l1 = "흠, 내가 네 문제를 해결해주면 어떨까?";
				link.l1.go = "Unwantedpostor_1";
		break;
		
		case "Unwantedpostor_1":
				dialog.text = "결정했어? 저 자식 무장했어, 뭔가 전문 용병 같은데...";
				link.l1 = "흠, 네 말이 맞아, 무장한 용병이랑 말싸움할 기분은 아니군...";
				link.l1.go = "Exit";
				link.l2 = "나도 수도원 수녀는 아니거든... 그래도 방을 빌리고 싶어.";
				link.l2.go = "Unwantedpostor_2";
		break;
		
		case "Unwantedpostor_2":
				dialog.text = "음, 만약 자네가, 에헴... 그를 나가게 설득할 수 있다면, 그 방은 아침까지 자네 것이네. 물론 공짜로 말이야.";
				link.l1 = "있잖아, 마음이 바뀌었어. 이제 누구를 설득하고 싶은 기분이 아니야.";
				link.l1.go = "Exit";
				link.l2 = "이거 꼭 봐야 할 거야. 네가 원치 않는 손님이 곧 거대한 갈매기처럼 네 선술집 밖으로 날아갈 테니까.";
				link.l2.go = "Unwantedpostor_kikcoff";
		break;
		
		case "Unwantedpostor_kikcoff":
				DialogExit();
				chrDisableReloadToLocation = true; //закрыть локацию
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location+"_upstairs")], true); //запретить драться
				iTemp = sti(pchar.rank) + rand(5);
				sld = GetCharacter(NPC_GenerateCharacter("Berglar_Unwantedpostor", "citiz_5"+(rand(3)+1), "man", "man", iTemp, PIRATE, -1, true, "quest")); // "mercen_"+(rand(14)+14)
				FantomMakeCoolFighter(sld, iTemp, 50 + rand(30), 50 + rand(30), "topor_04", "", "bullet", 50);
				sld.dialog.filename = "GenQuests_Dialog.c";
				sld.dialog.currentnode = "Unwantedpostor_room";	
				sld.greeting = "Enc_Raiders"; 
				if (findsubstr(locations[FindLocation(pchar.location)].id, "tavern_upstairs" , 0) == -1)
				{
					DoQuestReloadToLocation(pchar.location+"_upstairs", "quest", "quest4", "");
					ChangeCharacterAddressGroup(sld, pchar.location+"_upstairs", "quest", "quest3");
				} 
				LAi_SetActorType(sld);
				LAi_ActorDialogDelay(sld, pchar, "", 1.5);
		break;
		// <-- belamour постоялец
		
		case "Helen_room_night":
			dialog.text = "알겠소. 은화 다섯 냥이오.";
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = "물론이오, 여기 있습니다.";
				link.l1.go = "room_night_wait";
			}
			link.l2 = "사실 있잖아... 다음에 하자. 오늘은 남은 시간 동안 그냥 돌아다닐래.";
			link.l2.go = "Helen_night_exit";
		break;
		
		case "Helen_room_day":
			dialog.text = "현명한 결정이군. 은화 다섯 닢이야, 그리고 좋은 밤 보내.";
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = "자, 여기 있습니다. 그리고 고맙습니다 - 좋은 밤 되세요.";
				link.l1.go = "room_day_wait";
			}
			link.l2 = "다시 생각해 보니, 잠이 오지 않는군. 마을을 좀 돌아다니며 밤공기를 쐬고 오겠네.";
			link.l2.go = "Helen_day_exit";
		break;
		
		case "Helen_room_day_next":
			dialog.text = "물론이지, Helen. 10페소야.";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "물론이오, 여기 있습니다.";
				link.l1.go = "room_day_wait_next";
			}
			link.l2 = "사실... 하루 종일 뭔가 쓸모 있는 일을 할 수도 있겠지. 아마 다음에 하자.";
			link.l2.go = "Helen_Next_day_exit";
		break;
		
		case "Helen_night_exit":
			dialog.text = "원하시는 대로 하겠습니다, Helen.";
			link.l1 = "으음.";
			link.l1.go = "exit";
		break;
		
		case "Helen_day_exit":
			dialog.text = "좋은 산책을 하고 나면 졸음이 올 수도 있지.";
			link.l1 = "하하, 그럴지도.";
			link.l1.go = "exit";
		break;
		
		case "Helen_next_day_exit":
			dialog.text = "원하시는 대로 하십시오.";
			link.l1 = "그럼, 다음에 또 보자.";
			link.l1.go = "exit";
		break;
		
		case "Helen_rumours_tavern":
			dialog.text = "물론이지, Helen, 네 말에 귀 기울이고 있어.";
			link.l1 = "이 마을에 새로운 소식이나 흥미로운 소문이 있나?";
			link.l1.go = "rumours_tavern";
		break;
		
		// Леди Бет -->
		case "LadyBeth_Room":
			dialog.text = "그 사람은 평소보다 세 배나 더 지불하니까... 무슨 말인지 알겠지. 그리고 거절하는 건 추천하지 않아 – 성질이 고약하거든. 특히 요즘은 더 그래.";
			link.l1 = "쟤 왜 저래?";
			link.l1.go = "LadyBeth_Room_2";
		break;
		
		case "LadyBeth_Room_2":
			dialog.text = "집착이야, 그게 바로 문제지. 처음엔 그 사람 참 후하고 친절한 친구였어. 선원들은 선술집에서 돈을 펑펑 쓰고, 아가씨들에게 선물도 사주곤 했지. '레이디 베스'가 항구에 들어오면 진짜 축제가 벌어졌어. 그런데 지금은? 이제는 식량만 사고, 아무나 닥치는 대로 사람을 뽑아가. 마치 선원이 아니라 그냥 일손만 필요하다는 듯이 말이야. 뭐, 직접 가서 그 사람한테 이야기해 보라고.";
			link.l1 = "그럴지도 모르지. 고마워.";
			link.l1.go = "exit";
			pchar.questTemp.LadyBeth_TavernRoomDialog = true;
		break;
		// Леди Бет <--
	}
}

string findTraderCity(ref NPChar)
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES); 
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (colonies[n].id != "Panama" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != GetIslandByColony(&colonies[n])) //не на свой остров
		{
			if (nation == RELATION_ENEMY || sti(npchar.nation) == PIRATE)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[hRand(howStore-1)];
	return colonies[nation].id;
}

string findPassangerCity(ref NPChar)
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (colonies[n].nation != "none" && colonies[n].id != "Panama" && GetIslandByCityName(npchar.city) != GetIslandByColony(&colonies[n])) //не на свой остров
		{
			if (nation == RELATION_ENEMY || sti(npchar.nation) == PIRATE)
			{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	}
	if (howStore == 0) return "none";
	nation = storeArray[hRand(howStore-1)];
	return colonies[nation].id;
}

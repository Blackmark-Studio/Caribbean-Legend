// общий диалог ростовщиков
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, chr, sld;
	aref Link, NextDiag;
	string NPC_Area, sTemp, sTitle, sDepositType1, sDepositType2;
	int LoanSum, LoanInterest, LoanPeriod, LoanResult, iPastMonths, DepositSum, DepositInterest, DepositResult, iNum, iTemp, iTotalDublonQty;
	int iRes, iPer, iDep;
	float fPer;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	string iDay, iMonth, s1;
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;

	NPC_Area = Npchar.City;
	sDepositType1 = NPC_Area + "_Type1";
	sDepositType2 = NPC_Area + "_Type2";
 
	if(!CheckAttribute(npchar, "quest.item_date"))
	{
		npchar.quest.item_date = "";
	} 
 
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Usurer\" + NPChar.City + "_Usurer.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06

	if (!CheckAttribute(npchar, "quest.trade_date"))
    {
        npchar.quest.trade_date = "";
    }
    if (!CheckAttribute(npchar, "quest.FindCitizenNoShip"))
    {
        npchar.quest.FindCitizenNoShip = 0;
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
			if (LAi_group_GetPlayerAlarm() > 0)
			{
				//--> работорговец
				if(pchar.questTemp.Slavetrader == "After_enterSoldiers" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
				{
					dialog.text = " 끝났다. 이제 이곳을 떠나시오, "+pchar.name+". 이 모든 혼란을 내가 정리하겠소.";
					link.l1 = "좋아, 출항하겠다!";
					link.l1.go = "exit";
					break;
				}
				//<-- работорговец
			
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("마을이 경계 태세에 들어갔고, 그들은 너를 온 곳에서 찾고 있어! 내가 너라면 여기 오래 머무르지 않겠어.","모든 경비병들이 너를 찾고 있어. 내가 바보인 줄 알아? 너랑 이야기하다가 위험을 감수하진 않겠어!","도망쳐, "+GetSexPhrase("친구","소녀")+", 군인들이 너를 벌집으로 만들기 전에..."),LinkRandPhrase("무슨 용건이냐, 비열한 놈아?! 도시 경비병들이 네 위치를 이미 알고 있으니 도망칠 수 없을 것이다,\n "+GetSexPhrase("더러운 해적","이 해적 창녀야")+"!","더러운 살인자, 내 자리에서 꺼져라! 경비병!","나는 너 따위가 두렵지 않다, 비열한 놈아! 곧 우리 요새에서 목이 매달릴 테니, 도망칠 수 없을 거다..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("헤, 그건 나한텐 아무 문제도 아니지...","그들이 날 절대 잡지 못할 거야."),RandPhraseSimple("입 다물어, "+GetWorkTypeOfMan(npchar,"")+", 아니면 네 피투성이 혀를 뽑아버릴 거야!","헤헷, "+GetWorkTypeOfMan(npchar,"")+", 너도 해적을 잡고 싶어? 이봐, 얌전히 여기 앉아 있으면 목숨은 건질 거야..."));
				link.l1.go = "fight";
				break;
			}
		//Jason ---------------------------------------Бремя гасконца------------------------------------
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock") && pchar.location == "Fortfrance_bank")
			{
				dialog.text = "무엇이 필요하십니까, 나리?";
				Link.l1 = "정보가 좀 필요하오... 묻고 싶은 것이 있소.";
				Link.l1.go = "quests";
				Link.l2 = "작은 대출 하나 어떻소?";
				Link.l2.go = "sharlie_credit";
				Link.l3 = "아니, 마음이 바뀌었소.";
				Link.l3.go = "exit";
				if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
				{
					link.l4 = "이 귀걸이들을 한번 보시지요, 나리. 정글에서 산적의 주머니에서 발견한 것입니다. 분명 훌륭한 보석 세공인의 작품인데, 이 황야 출신은 아닐 것이라 확신합니다. 어떻게 생각하십니까?";
					link.l4.go = "Sharlie_junglejew";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskiper")
				{
					link.l1 = "저도 Folke Deluc라는 이름의 채무자가 있다는 것을 알고 있소. 그의... 연체가 얼마나 심각한지 말씀해 주시겠소?";
					link.l1.go = "Sharlie";
				}	
				if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskipermoney")
				{
					link.l1 = "저는 Folke Deluc의 빚 때문에 왔습니다.";
					link.l1.go = "Sharlie_repeat";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskipercaptive")
				{
					link.l1 = "당신의 의뢰를 완료했습니다, 나리. 여기 당신의... 스페인 친구가 있습니다.";
					link.l1.go = "Sharlie_14";
				}
				break;
			}			
		//<-- Бремя гасконца
			
			//--> работорговец
			if (pchar.questTemp.Slavetrader == "canTakeQuest" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "드디어 내 방에 어울리는 선장이 찾아왔군. 매달 이자를 주려고 내가 그들의 두블룬과 기니를 밭에 심고 거둬들이기만 한다고 생각하는 바보들 때문에 정말 지쳤소.\n그들은 한 푼 한 푼을 감시하면서, 불쌍한 고리대금업자가 굶어 죽지 않으려고 온갖 수단을 써야 하면서도, 동시에 그들에게 크리스마스 거위 한 마리 살 돈을 마련해 주는 고생을 전혀 모른다오.";
				Link.l1 = "자신들의 저축을 맡긴 사람에게서 그런 말을 듣는다면, 당신의 고객들이 기뻐하지는 않을 것 같군요.";
				Link.l1.go = "GiveTaskSlave";
				npchar.quest.slave = "current";//чтобы камнем не долбил
				break;
			}	
			
			if (pchar.questTemp.Slavetrader == "TakeShoreCap_end" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "...";
				Link.l1 = "이봐, 늙은 햄스터, 이제 정말 제대로 설명해야 할 거야! 그 배의 화물에는 노예가 없었고, 오직 병사들만 있었어! 그놈들 상대하는 임무가 얼마나 힘들었는지 알아? 나 지금 몹시 화가 났으니, 제대로 해명하는 게 좋을 거야!";
				Link.l1.go = "Slaveshore_5";
				break;
			}	
			if (pchar.questTemp.Slavetrader == "Win_HavanaFort" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "아, 드디어 오셨군요! 군도 전체가 당신의 대담한 공격에 대해 수군거리고 있습니다. 다시 뵙게 되어 반갑습니다!";
				Link.l1 = "저는 그런 명성보다는 무명이 더 낫겠소... 너무 위험하니까요.";
				Link.l1.go = "Win_Havana_Fort";
				break;
			}	
			if (pchar.questTemp.Slavetrader == "Havana_seekslaves" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "내 오천 명의 노예들을 데려왔는가?";
				if (GetSquadronGoods(Pchar, GOOD_SLAVES) >= 5000)
				{
					Link.l1 = "있소. 내 화물칸에 있소.";
					Link.l1.go = "Havana_Fort_yesA";
				}
				else
				{
					Link.l1 = "아니오, 아직 이 일에 매진하고 있습니다.";
					Link.l1.go = "exit";
				}
				break;
			}	
			
			if (pchar.questTemp.Slavetrader == "End_quest_bad" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "흠... 아직 살아 있군? 이상하네. 하지만 오래 가지 못할 거다. 군인들! 도와라! 여기 도적이 있다!";
				link.l1 = "이런 개자식!";
				link.l1.go = "exit";
				LAi_group_Attack(NPChar, Pchar);
				break;
			}
			
			if(pchar.questTemp.Slavetrader == "wait_6" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_6") > 6 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "안녕하십니까. 제 이름은 "+GetFullName(npchar)+". 무엇을 도와드릴까요?";
				link.l1 = "오! 여기서 뭐 하십니까, 나리?";
				link.l1.go = "Usurer_Escape";
				break;
			}
			//<-- работорговец
			// ФМК-Гваделупа
			if(CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "killers" && npchar.location == "BasTer_bank")
			{
				dialog.Text = "...";
				link.l1 = "이봐, 이 자식아. 기막힌 생각이라도 했나? 용병을 고용해서 날 죽이려고? 내 입을 막으려고 한 거야? 어서 말해!";
				link.l1.go = "FMQG_x";
				break;
			}
			// Леди Бет -->
			if (pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_Bank" && !CheckAttribute(pchar, "questTemp.LadyBeth_Usurer")) // Блеквуд в городе
			{
				dialog.Text = "오, 선장님! 오늘 제가 가져온 물건들을 좀 보십시오. 블랙우드의 부하들에게서 얻은 것들입니다. 그들은 새 원정을 위해 돈이 필요하고, 우리에게는... 이익이겠지요?";
				link.l1 = "블랙우드가 자기 부하들이 발견한 것들을 팔고 있다는 사실을 알고 있소?";
				link.l1.go = "LadyBeth_Usurer_1";
				break;
			}
			// Леди Бет <--
			if(NPChar.quest.meeting == "0")
			{
				dialog.Text = LinkRandPhrase(LinkRandPhrase("좋은 하루 되시길, "+GetAddress_Form(NPChar)+". 무엇을 도와드릴까요? 내가 당신을 아는 사람인가요?","들어오십시오, 선장님. 제 이름은 "+GetFullName(npchar)+" 그리고 나는 이곳의 은행가요.","만나서 반갑소, "+GetAddress_Form(NPChar)+"! 나는 이곳의 은행가요. 돈 문제가 있다면 내가 도와줄 수 있소."),LinkRandPhrase("전에 만난 적이 있습니까, 선장? 저는 "+GetFullName(npchar)+", 그리고 나는 이곳의 은행가요.","들어오십시오, 선장님. 제 이름은 "+GetFullName(npchar)+" 그리고 나는 이곳의 은행가요.","안녕하십니까, "+GetAddress_Form(NPChar)+". 나는 "+GetFullName(npchar)+", 이 지역 은행가요."),LinkRandPhrase("만나서 반갑소, "+GetAddress_Form(NPChar)+", 나는 "+GetFullName(npchar)+" 이 멋진 마을의 그저 소박한 은행가일 뿐입니다.","결정은 선장님이 하십시오! 저에게서 돈을 빌리시겠습니까, 아니면 이자를 받고 돈을 빌려주시겠습니까?","선장 나리! 이렇게 제 소박한 사무실을 찾아주셔서 정말 기쁩니다!"));
				link.l1 = RandPhraseSimple(LinkRandPhrase("기꺼이요! 마침 시내를 거닐다가 당신을 찾아오기로 했습니다.","기꺼이, 나는 "+GetFullName(pchar)+", 만나서 반갑소.",""+GetFullName(pchar)+" , 라는 이름의 배의 선장 "+pchar.ship.name+" , 만나서 반갑소. 여기가 은행이 맞지요?"),RandPhraseSimple("만나서 반갑소. 나는 "+GetFullName(pchar)+". "+배의 이름+"이라는 배의 선장 "+pchar.ship.name+". 나는 그냥 당신을 알고 싶었을 뿐이오.","아하, 여기에도 은행이 있군요? 만나서 반갑소, 나는 "+GetFullName(pchar)+", 내 배의 선장이오."));
				link.l1.go = "next";
				NPChar.quest.meeting = "1";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_bank")
				{
					dialog.text = "MacArthur 부인, 어서 오십시오, 들어오시지요.";
					link.l1 = "그리고 당신께도, "+npchar.lastname;
					link.l1.go = "Helen_next";
				}
			}
			else
			{
				dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("너였군! 뭐 원하는 거야, "+GetAddress_Form(NPChar)+"?","무슨 일로 오셨습니까, 선장님? 유감이지만, 선장님의 평판으로는 저희가 그다지 모시고 싶은 고객이 아니십니다.","아하, 또 다른 손님이군! 처음엔 강도인 줄 알았소... 하하, 농담이오."),LinkRandPhrase("오! 무엇을 원하시오? 여기는 은행이지, 선술집이 아니오.","안녕하십니까, 선장님. 저는 고객을 매우 신중하게 고르는 편임을 알려드려야겠습니다.","무엇을 원하시오, "+GetFullName(pchar)+"? 당신의 명성이 높지 않으면 큰 대출을 받을 수 없다는 사실을 기억하고 계시겠지요?"),LinkRandPhrase("투자에 관심이 있으시길 바랍니다, "+GetAddress_Form(NPChar)+"? 당신에게 대출을 내주기는 쉽지 않을 것입니다.","Captain "+GetFullName(pchar)+" 보잘것없는 은행가에게 무엇을 원하시오? 미안하오만, 대출을 마련해 드릴 수 없소. 오직 나만이 당신께 이자를 붙여 돈을 빌려줄 수 있소.","들어오시오, "+GetAddress_Form(NPChar)+". 유감스럽게도 당신이 가장 환영받는 손님은 아니라는 점을 알려드려야겠군요. 하지만 저는 보통 사람들을 바로 돌려보내지는 않습니다.")),LinkRandPhrase(LinkRandPhrase("안녕하십니까, 나리 "+GetFullName(pchar)+"! 언제든지 사업 문제라면 도와드릴 준비가 되어 있습니다.","안녕하십니까, 나리 "+GetAddress_Form(NPChar)+". 저는 언제든지 대출을 해드릴 준비가 되어 있으며, 어떤 투자도 기꺼이 받겠습니다.","Dear "+GetFullName(pchar)+"! 만나서 반갑소! 무슨 일로 왔소?"),LinkRandPhrase("Captain "+GetFullName(pchar)+"! 언제나 당신을 위해 준비되어 있습니다. 대출을 원하십니까, 아니면 이자를 받고 자금을 투자하시겠습니까?","안녕하십니까, 선장님! 이곳에서 언제나 환영받는 고객이십니다. 훌륭한 사업 평판을 가지고 계시군요!","안녕하십니까, "+GetFullName(pchar)+". 다시 찾아주셔서 기쁩니다. 이번에는 이익이 되는 거래를 하러 오신 것이겠지요?"),LinkRandPhrase("안녕하십니까, 선장님! 무엇을 원하십니까? 대출을 원하십니까, 아니면 투자를 하시겠습니까?","Captain "+GetFullName(pchar)+"! 이익이 되는 조건으로 돈을 빌리고 싶으신가요? 이렇게 훌륭한 손님을 언제나 반갑게 맞이합니다.","다시 뵙게 되어 반갑습니다, 선장님! 대출이든 투자인든 언제든 도와드릴 준비가 되어 있습니다.")));
				link.l1 = pcharrepphrase(RandPhraseSimple(LinkRandPhrase("농담 아니야, 은행가. 나도 여기서 장사해야 하거든.","말이 너무 많군, 이봐. 바로 본론으로 들어가자.","돈에는 냄새가 없다는 말 들어봤소? 그러니 코 막고 본론으로 들어갑시다."),LinkRandPhrase("이렇게 손님을 맞이하는 겁니까? 오늘은 내가 기분이 좋아서 다행이군요.","하! 나를 보니 반갑지 않아? 내가 너한테 좋은 인상을 줄 금화 한 닢만큼의 값어치도 없단 말이냐. 어쨌든, 거래나 하자, 고리대금업자.","이봐, 네게 예의를 좀 가르쳐주고 싶지만, 지금 그럴 시간 없어. 대신 돈 얘기나 하자.")),RandPhraseSimple(LinkRandPhrase("오랜 친구를 다시 만나서 반갑군!","여기에 올 때마다 항상 즐겁네, 친구. 바로 본론으로 들어가세.","나도 매우 기쁘네. 이제 사업 이야기를 해보세, 친구."),LinkRandPhrase("정말 만나서 반갑소. 금융의 바다에선 무슨 새 소식이 있소?","아직 나를 기억해 줘서 기쁘군. 나는 바쁘니, 바로 본론으로 들어가세.","안녕, 오랜 친구야! 다시 만나서 반갑다!")));
				link.l1.go = "next";
			}
			break;
			
			case "next":
			dialog.text = NPCStringReactionRepeat("무엇을 도와드릴까요?","이번에는 무슨 일로 왔소?","흠... 무슨 걱정이 있으십니까?","에, "+GetAddress_Form(npchar)+", 손님들이 얼마나 성가실 수 있는지 상상도 못 하실 겁니다...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("괜찮소, 그냥 둘러보며 이야기하고 있을 뿐이오.","또 나야. 그냥 너랑 얘기 좀 하고 싶어서.","네, 또 저입니다. 심각한 일은 아니고, 그냥 당신과 이야기하고 싶었습니다.","그래, 때로는 은행가도 그리 쉬운 일만은 아니오. 그냥 이야기나 좀 하고 싶었소...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			link.l2 = "우리의 재정 문제에 대해 상의하고 싶소.";
			link.l2.go = "LoanUsurer";//(на кредитный генератор)
			link.l3 = "나는 보석과 기묘한 우상, 혹은 진귀한 보석들에 관심이 있소.";
			if (!isMultiObjectKnown("gold_dublon"))
			{
				link.l3.go = "items_0";
			}
			else
			{
				link.l3.go = "items_1";
			}	
			link.l4 = "정보가 좀 필요하오. 음, 묻고 싶은 것이 있소.";
			link.l4.go = "quests";//(перессылка в файл города)
//Jason, генер почтового курьера 2 уровня
			if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
			{
				if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					link.l12 = "에서 온 사업 서류를 가져왔소 "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
					link.l12.go = "Postcureer_LevelUp_ForAll";
				}
			}
			//квесты мэра, проникновение во враждебный город
  			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
			{
				link.l7 = RandPhraseSimple("나는 한 사람의 명령을 받고 여기 왔소. 그는 총독이오 "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".",GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+" 여기로 보내셨소. 당신에게서 뭔가 받아야 하오.");
				link.l7.go = "IntelligenceForAll";
			}
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "usurer_keeper")
			{
				link.l9 = "안녕하십니까, 당신의 아드님께 초대를 받았습니다."; 
				link.l9.go = "EncGirl_4";
				pchar.quest.EncGirl_GetLoverFather.over = "yes";
			}	
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer"))
			{
				link.l10 = "나는 그 문서의 소유주가 누구인지 알고 싶소.";
				link.l10.go = "ShipLetters_Usurer1";			
			}
			
			//--> семейная реликвия // лесник переписал с нпчара на чара 
			if (CheckAttribute(pchar, "GenQuest.Noblelombard") && npchar.city == pchar.GenQuest.Noblelombard.City && !CheckAttribute(pchar, "quest.noblelombard"))// вот тут 
			{
				link.l11 = "당신 고객의 빚에 대해 이야기하고 싶소. 그의 이름은 "+pchar.GenQuest.Noblelombard.Name+". 그는 가보를 전당포에 맡겼소. 나는 여기서 그의 이익을 대변하는 사람으로, 그 물건의 반환에 대해 당신과 논의할 권리가 있소.";
				link.l11.go = "Noblelombard";			
			}
			if (CheckAttribute(pchar, "GenQuest.Noblelombard.Giveregard") && npchar.city == pchar.GenQuest.Noblelombard.City)
			{
				link.l11 = "우리는 석 달 전에 만남을 가졌고 한 남자의 유물에 대해 이야기했소. 그의 이름은 "+pchar.GenQuest.Noblelombard.Name+". 기억나시오? 그는 내 이름으로 예금을 개설해야 했소. 금액은  "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Regard))+"...";
				link.l11.go = "Noblelombard_5";			
			}
			//<-- семейная реликвия
			
			//-->работорговец
			if (pchar.questTemp.Slavetrader == "Seek_slaves" && pchar.questTemp.Slavetrader.UsurerId == npchar.id) 
			{
				link.l8 = "그것은 당신의... 노예 임무에 관한 일입니다.";
				link.l8.go = "Checkslaves";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goaway" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "안녕하십니까, "+NPChar.name+", 당신의 의뢰에 대해 이야기해 봅시다.";
				link.l8.go = "Takeslaves_4_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goaway_pinas" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "좋은 하루입니다, "+NPChar.name+", 당신의 의뢰에 대해 이야기합시다.";
				link.l8.go = "Pinas_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "died" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "좋은 하루입니다, "+NPChar.name+", 당신의 임무에 대해 이야기해 봅시다.";
				link.l8.go = "Takeslaves_4_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait") > 20 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "약속대로 왔소. 내게 맡길 일이 있소?";
				link.l8.go = "Takeslaves_3";
				break;
			}
			if(pchar.questTemp.Slavetrader == "waitship" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "약속대로 왔소. 일거리는 어떤가?";
				link.l8.go = "Takeslaves_3";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_1" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_1") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "안녕하십니까, "+npchar.name+". 어떻게 지내십니까? 저에게 새로운 의뢰가 있습니까?";
				link.l8.go = "EscapeSlave";
				break;
			}
			if(pchar.questTemp.Slavetrader == "escapeslave_win" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "임무는 끝났소. 도망자들을 찾아냈지. 하지만 그렇게 쉽지는 않았소.";
				link.l8.go = "Escape_slaves_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_2" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_2") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "좋은 하루입니다, "+npchar.name+". 새로운 이익이 될 만한 임무를 받으러 왔소.";
				link.l8.go = "Slaveshore";
				break;
			}			
			
			if(pchar.questTemp.Slavetrader == "goodbye" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "나쁜 소식이오,"+npchar.name+". 나는 브리건틴을 빼앗는 데 실패했다.";
				link.l8.go = "Brig_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goodbye_1" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "봐,  "+npchar.name+". 나는 브리건틴을 쫓아갔지만 서류는 찾지 못했소. 정말 그들이 거기 있었다는 것이 확실합니까?";
				link.l8.go = "Letter_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "winbrig" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "좋은 소식이오,"+npchar.name+". 내가 그 브리건틴을 추적해서 서류를 되찾았소. 여기 있소.";
				link.l8.go = "Brig_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_3" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_3") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "안녕하십니까, "+npchar.name+". 제게 줄 새로운 의뢰를 준비하셨습니까?";
				link.l8.go = "SlaveGalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wingalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", 내가 그 이른바 '갤리온'을 가로채는 데 성공했소.";
				link.l8.go = "Wingalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "lostgalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", 정말 유감이오만, 이 갤리온에 승선할 수 없었소.";
				link.l8.go = "Lostgalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_4" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_4") > 4 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "좋은 하루입니다, "+npchar.name+". 내 돈 받으러 왔다.";
				link.l8.go = "FindRat";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wincorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", 임무가 끝났소. 그 놈 곤티에와 그의 선원들도 모두 죽었소.";
				link.l8.go = "Wincorvette";
				break;
			}
			if(pchar.questTemp.Slavetrader == "lostcorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", 유감이오만, 나는 프랑수아 곤티에를 잡지 못했소. 토르투가까지 그를 쫓았지만, 그가 자신의 코르벳 함선을 타고 내게서 도망쳤소.";
				link.l8.go = "lostcorvette";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_5" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_5") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "안녕하십니까,"+npchar.name+". 이번에 저를 위해 준비한 새로운 임무에 대해 말씀해 주십시오.";
				link.l8.go = "Havana_fort";
				break;
			}
			//<--работорговец
			NextDiag.TempNode = "First time";
		break;
		
		case "Helen_next":
			dialog.text = NPCStringReactionRepeat("당신이 돈이 궁하거나 재산을 늘리려는 분이라고는 생각하지 않습니다. 무엇 때문에 제 사무실을 찾으셨습니까?","이번에는 무슨 일로 왔소?","흠... 무슨 걱정이 있으십니까?","에, "+GetAddress_Form(npchar)+", 손님들이 얼마나 성가실 수 있는지 상상도 못하실 겁니다...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("괜찮소, 그냥 둘러보며 이야기하고 있을 뿐이오.","또 나야. 그냥 너랑 얘기 좀 하려고.","네, 또 저입니다. 별일은 아니고, 그냥 당신과 이야기하고 싶어서요.","예, 은행가라는 게 때로는 그리 쉽지 않소. 그냥 이야기나 좀 하고 싶었을 뿐이오...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			link.l2 = "우리의 재정 문제에 대해 논의하고 싶습니다.";
			link.l2.go = "LoanUsurer";//(на кредитный генератор)
			link.l3 = "나는 보석, 특이한 우상, 혹은 귀한 보석에 관심이 있소.";
			if (!isMultiObjectKnown("gold_dublon"))
			{
				link.l3.go = "items_0";
			}
			else
			{
				link.l3.go = "items_1";
			}	
			link.l4 = "정보가 좀 필요하오. 음, 묻고 싶은 것이 있소.";
			link.l4.go = "quests";//(перессылка в файл города)
//Jason, генер почтового курьера 2 уровня
			if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
			{
				if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					link.l12 = "에서 온 사업 서류를 가져왔소 "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
					link.l12.go = "Postcureer_LevelUp_ForAll";
				}
			}
			//квесты мэра, проникновение во враждебный город
  			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
			{
				link.l7 = RandPhraseSimple("나는 한 사람의 명령을 받고 여기 왔다. 그는 총독이다 "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".",GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+" 저를 여기로 보냈습니다. 당신에게서 뭔가 받아야 합니다.");
				link.l7.go = "IntelligenceForAll";
			}
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "usurer_keeper")
			{
				link.l9 = "안녕하십니까, 당신의 아드님께 초대를 받았습니다."; 
				link.l9.go = "EncGirl_4";
				pchar.quest.EncGirl_GetLoverFather.over = "yes";
			}	
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer"))
			{
				link.l10 = "나는 그 문서의 소유주가 누구인지 알고 싶소.";
				link.l10.go = "ShipLetters_Usurer1";			
			}
			
			//--> семейная реликвия // лесник переписал с нпчара на чара 
			if (CheckAttribute(pchar, "GenQuest.Noblelombard") && npchar.city == pchar.GenQuest.Noblelombard.City && !CheckAttribute(pchar, "quest.noblelombard"))// вот тут 
			{
				link.l11 = "당신 고객의 빚에 대해 이야기하고 싶소. 그의 이름은 "+pchar.GenQuest.Noblelombard.Name+". 그는 가보를 전당잡혔소. 나는 여기서 그의 이해관계를 대변하는 자로서, 그 반환에 대해 당신과 논의할 권리가 있소.";
				link.l11.go = "Noblelombard";			
			}
			if (CheckAttribute(pchar, "GenQuest.Noblelombard.Giveregard") && npchar.city == pchar.GenQuest.Noblelombard.City)
			{
				link.l11 = "우리는 석 달 전에 만남을 가졌고 한 남자의 유물에 대해 이야기했지요. 그의 이름은 "+pchar.GenQuest.Noblelombard.Name+". 기억나시오? 그는 내 이름으로 예금을 개설해야 했소. 금액은  "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Regard))+"...";
				link.l11.go = "Noblelombard_5";			
			}
			//<-- семейная реликвия
			
			//-->работорговец
			if (pchar.questTemp.Slavetrader == "Seek_slaves" && pchar.questTemp.Slavetrader.UsurerId == npchar.id) 
			{
				link.l8 = "그것은 당신의... 노예 임무에 관한 일입니다.";
				link.l8.go = "Checkslaves";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goaway" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "좋은 하루입니다, "+NPChar.name+", 당신의 임무에 대해 이야기합시다.";
				link.l8.go = "Takeslaves_4_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goaway_pinas" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "안녕하십니까, "+NPChar.name+", 당신의 의뢰에 대해 이야기해 봅시다.";
				link.l8.go = "Pinas_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "died" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "안녕하십니까, "+NPChar.name+", 당신의 임무에 대해 이야기합시다.";
				link.l8.go = "Takeslaves_4_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait") > 20 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "약속대로 왔소. 내게 맡길 일 있소?";
				link.l8.go = "Takeslaves_3";
				break;
			}
			if(pchar.questTemp.Slavetrader == "waitship" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "약속한 대로 왔소. 일거리가 있소?";
				link.l8.go = "Takeslaves_3";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_1" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_1") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "안녕하십니까, "+npchar.name+". 어떻게 지내십니까? 저에게 새로운 의뢰가 있습니까?";
				link.l8.go = "EscapeSlave";
				break;
			}
			if(pchar.questTemp.Slavetrader == "escapeslave_win" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "임무는 끝났소. 도망자들을 찾아냈지. 하지만 그리 쉬운 일은 아니었소.";
				link.l8.go = "Escape_slaves_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_2" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_2") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "안녕하십니까, "+npchar.name+". 새로운 수익성 있는 임무를 받으러 왔소.";
				link.l8.go = "Slaveshore";
				break;
			}			
			
			if(pchar.questTemp.Slavetrader == "goodbye" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "나쁜 소식이오,"+npchar.name+". 나는 브리건틴을 구하지 못했소.";
				link.l8.go = "Brig_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goodbye_1" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "봐,  "+npchar.name+". 브리건틴을 쫓아갔으나, 아무런 서류도 찾지 못했소. 정말 그들이 거기 있었다는 것이 확실하오?";
				link.l8.go = "Letter_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "winbrig" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "좋은 소식이오,"+npchar.name+". 그 브리건틴을 찾아내서 서류를 되찾았소. 여기 있소.";
				link.l8.go = "Brig_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_3" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_3") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "안녕하십니까, "+npchar.name+". 저에게 줄 새 임무를 준비하셨습니까?";
				link.l8.go = "SlaveGalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wingalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", 내가 그 이른바 '갤리온'을 가로채는 데 성공했소.";
				link.l8.go = "Wingalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "lostgalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", 정말 유감이오만, 이 갤리온에 승선할 수 없었소.";
				link.l8.go = "Lostgalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_4" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_4") > 4 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "좋은 하루입니다, "+npchar.name+". 내 돈을 받으러 왔소.";
				link.l8.go = "FindRat";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wincorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", 임무를 완수하셨습니다. 그 자식 곤티에와 그의 선원들도 모두 죽었습니다.";
				link.l8.go = "Wincorvette";
				break;
			}
			if(pchar.questTemp.Slavetrader == "lostcorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", 죄송하지만, 프랑수아 곤티에를 잡지 못했습니다. 토르투가까지 그를 쫓아갔지만, 그는 자신의 코르벳 함선을 타고 제 손아귀에서 도망쳤습니다.";
				link.l8.go = "lostcorvette";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_5" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_5") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "안녕하십니까,"+npchar.name+". 저를 위해 준비한 이번 새 임무에 대해 말씀해 주십시오.";
				link.l8.go = "Havana_fort";
				break;
			}
			//<--работорговец
			NextDiag.TempNode = "First time";
		break;

		case "items_0":
			dialog.text = "황금 두블룬이나 그것들을 담을 상자를 좀 사시겠습니까? 믿으십시오, 아주 가치 있는 투자입니다.";
			link.l1 = "예, 매우 흥미롭군요.";
			link.l1.go = "items";
			AddQuestRecordInfo("Recipe", "Gold_dublon");
			SetAlchemyRecipeKnown("gold_dublon");
			SetAlchemyRecipeKnown("Chest");
			npchar.quest.meeting = "1"; 			
		break;
		
		case "items_1":
			dialog.text = "페소로 거래하시겠습니까, 아니면 두블룬으로 하시겠습니까?";
			link.l1 = "페소로.";
			link.l1.go = "items";
			link.l2 = "두블룬을 위해서지.";
			link.l2.go = "items_dub";
		break;
		
		case "items":
			if (npchar.quest.item_date != lastspeak_date)
			{
				GiveItemToTrader(npchar);
				npchar.quest.item_date = lastspeak_date;
			}
			if(CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu")) AddItems(npchar, "gold_dublon", 100);
			if(CheckAttribute(pchar, "questTemp.Del_Rostovshik_repeat")) AddItems(npchar, "gold_dublon", 100);
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
			LaunchItemsTrade(NPChar, 0);
		break;
		
		case "items_dub":
			if (npchar.quest.item_date != lastspeak_date)
			{
				GiveItemToTrader(npchar);
				npchar.quest.item_date = lastspeak_date;
			}
			if(CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu")) AddItems(npchar, "gold_dublon", 100);
			if(CheckAttribute(pchar, "questTemp.Del_Rostovshik_repeat")) AddItems(npchar, "gold_dublon", 100);
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
			LaunchItemsTrade(NPChar, 1);
		break;
		
		//<<<<----------генератор -"Shipping documents". ------		
		case "ShipLetters_Usurer1":
			pchar.questTemp.different.GiveShipLetters.speakUsurer = true;
			dialog.text = "이 서류들을 읽으려면 내 시간이 많이 들 것이오, 그리고 내 시간은 값비싼 것이오.";
			link.l1 = "아마도, "+sti(pchar.questTemp.different.GiveShipLetters.price1)+" 페소가 당신의 시간을 보상해 줄까요?";
			link.l1.go = "ShipLetters_Usurer2";
			link.l2 = "원하시는 대로 하겠습니다. 안녕히 가십시오!";
			link.l2.go = "exit";
		break;
		
		case "ShipLetters_Usurer2":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.GiveShipLetters.price1));
			pchar.questTemp.different.GiveShipLetters.speakUsurer_1 = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "한번 봅시다! 아니, 이 이름은 처음 보오. 우리 항만 관리자에게 보여 주시오.";
				link.l1 = "유감이오만, 우리 약속이 있었소! 이 선장에 대해 이야기해 주기로 했잖소!";
				link.l1.go = "ShipLetters_Usurer2_1";
			}
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
			{
				s1 = "Well... I know the owner of this ship. He is not a very rich man, but he has some wealth.";
				dialog.text = s1+" 그자가 성공한 밀수꾼이라 하더군. 그게 듣고 싶었던 말인가?";
				link.l1 = "그런 것 같군...";
				link.l1.go = "ShipLetters_Usurer2_2";
			}
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
			{
				s1 = "Well... I am not sure that I can congratulate you for your found.";
				dialog.text = s1+"이 서류들은 우리 식민지 순찰선에 서명된 것이며, 그 선장은 강직한 원칙으로 유명합니다.";
				link.l1 = "순찰대인가? 사령관의 명령으로?";
				link.l1.go = "ShipLetters_Usurer2_3";
			}
		break;
		
		case "ShipLetters_Usurer2_1":
			dialog.text = "나는 그 서류들을 살펴보겠다고만 약속했소. 더 이상은 없으니 가도 되오.";
			link.l1 = "고맙소... 그래야겠지.";
			link.l1.go = "exit";
		break;
		
		case "ShipLetters_Usurer2_2":
			dialog.text = "결정은 당신이 하시오. 우리 사령관이 이 한 사람에게 오랫동안 꽤나 ‘관심’을 보여 왔소. 이미 생각나는 게 있소? 그리고 여기에는 아무 표시도 없는 선하증권들이 있소...";
			link.l1 = "알겠습니다. 감사합니다!";
			link.l1.go = "exit";		
		break;
		
		case "ShipLetters_Usurer2_3":
			s1 = "Exactly. Our smugglers are bearing a grudge against this captain by the way.";
			dialog.text = s1+"그리고 앞서 말씀드렸듯이, 그 문서의 소유자는 원칙을 중시하는 분이라 이 지역의 범죄를 그다지 좋아하지 않으십니다.";
			link.l1 = "알겠습니다. 감사하오!";
			link.l1.go = "exit";		
		break;

		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "아, 내 방탕한 아들과 그의 어린 신부를 데려온 선장이 바로 당신이오?";
				link.l1 = "그래, 그들을 도망치게 도운 건 바로 나였소.";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "아, 여기 계셨군요, 제 은인이시여. 보상을 기다리고 계신 겁니까?";
				link.l1 = "감사 인사만으로도 충분하겠지만...";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "제 아이를 도와주시고 그 곤란한 상황에 내버려 두지 않으셔서 진심으로 감사드립니다.\n부디 제가 할 수 있는 한 최선을 다해 감사의 뜻을 전하게 해주십시오.\n이 조촐한 금액과 작은 선물을 받아 주시기 바랍니다.";
			link.l1 = "감사합니다. 이 젊은 부부를 도울 수 있어 기뻤습니다.";
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = "고맙다고? 뭐가 고마워? 이 멍청이는 반년이나 백수로 지냈으면서 벌써 여자까지 꼬셨다니! 나 그 나이 때는 내 장사 하느라 바빴다. 결혼감 되는 총독 딸도 있는데, 이놈은 여기 창녀를 데려와—주여, 이런 말을 하게 하시다니 용서하소서! 그리고 이제는 내 축복까지 바란다고?";
			link.l1 = "감정이라는 것을 믿지 않으시는군요?";
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
			dialog.text = "감정? 무슨 감정? 다 큰 어른이 감정 타령이나 하고 있나? 젊은 사람들 비위나 맞추려 하다니, 부끄러운 줄 아시오. 네가 그 처녀를 부모에게서 데려가 내 아들의 인생을 망쳐 놓았지. 나한테서 감사 인사 따윈 기대하지 마시오. 이만 가보시오.";
			link.l1 = "그럼 안녕히...";
			link.l1.go = "EncGirl_6_2";
		break;
		
		case "EncGirl_6_2":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddQuestRecord("JungleGirl", "19");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("saw","saw"));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("",""));
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();		
		break;
		
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////		Кредитный генератор Loan
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "LoanUsurer":
			if (npchar.id == "Panama_Usurer")
			{
				if (sti(pchar.reputation.nobility) > 70 && ChangeCharacterNationReputation(pchar, SPAIN, 0) >= 80 && !CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold"))
				{
					dialog.text = "이야기해 봅시다. 듣고 있소.";
				}
				else
				{
					dialog.text = "어, 어. 유감이오만 거절해야겠소. "+GetAddress_Form(NPChar)+". 죄송하지만, 저희 은행은 스페인의 적에게는 서비스를 제공하지 않습니다.";
					link.l1 = "돈에는 국적이 없소, 나리 은행가.";
					if (CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold"))
					{
						if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)) && makeint(Pchar.Quest.Deposits.(sDepositType1)) == true)
						{
							dialog.text = "음-흠, "+GetAddress_Form(NPChar)+". 귀하의 예금이 더 이상 유효하지 않음을 알려드려야겠습니다.";
							Link.l1 = "무슨 근거로?!";
							Link.l1.go = "Panama_Deposit_SgorelVklad";
							DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
							break;						
						}
						else
						{
							link.l1.go = "Panama_Deposit_Cartahena";
							break;
						}
					}
					if (sti(pchar.reputation.nobility) < 71 || ChangeCharacterNationReputation(pchar, SPAIN, 0) < 80)
					{
						link.l1.go = "Panama_Deposit_NoReputation";
						break;
					}
				}
			}
			dialog.text = "이야기해 봅시다. 듣고 있소.";
			//кредиты
            if(CheckAttribute(Pchar, "Quest.Loans." + (NPC_Area)) && makeint(Pchar.Quest.Loans.(NPC_Area)) == true)
			{
				iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Loans.(NPC_Area).StartYear),makeint(Pchar.Quest.Loans.(NPC_Area).StartMonth),makeint(Pchar.Quest.Loans.(NPC_Area).StartDay), makefloat(Pchar.Quest.Loans.(NPC_Area).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
				Pchar.Quest.Loans.(NPC_Area).Result = makeint(Pchar.Quest.Loans.(NPC_Area).Sum) + ((makeint(Pchar.Quest.Loans.(NPC_Area).Sum)/100)*makefloat(Pchar.Quest.Loans.(NPC_Area).Interest))*(iPastMonths+1);// boal 23.01.2004
				if(makeint(PChar.money) >= makeint(Pchar.Quest.Loans.(NPC_Area).Result))
				{
					Link.l5 = "당신에게 빚졌소 "+FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).Result))+LinkRandPhrase(", 나는 당신의 돈을 돌려줄 준비가 되어 있소",". 빚을 갚고 싶소.",".  드디어 결산할 시간이로군.");
					Link.l5.go = "loan_return";	
					sTemp = "credit";
				}					
			}
			else
			{
				Link.l6 = LinkRandPhrase("동전을 좀 빌리고 싶소.","정말 페소가 좀 필요해.","작은 대출은 어떠신가요?");
				Link.l6.go = "loan";					
				if(makeint(Pchar.money) >= 100)
				{
					Link.l7 = LinkRandPhrase("이자를 받기 위해 제 돈을 예치하고 싶습니다.","제 은화 자루 몇 개를 맡아 주시겠습니까?","비 오는 날을 대비해 은화를 좀 맡겨도 되겠습니까?"); // patch
					Link.l7.go = "deposit";				
				}			
				if(CheckUseDublons(NPChar))
				{
					Link.l8 = "이자 받으려고 두블룬을 예치하고 싶소.";
					Link.l8.go = "deposit_dub";				
				}
			}
			
			if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)) && makeint(Pchar.Quest.Deposits.(sDepositType1)) == true)
			{
				iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Deposits.(sDepositType1).StartYear),makeint(Pchar.Quest.Deposits.(sDepositType1).StartMonth),makeint(Pchar.Quest.Deposits.(sDepositType1).StartDay), makefloat(Pchar.Quest.Deposits.(sDepositType1).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
				if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)+ ".Rem"))
				{
					Pchar.Quest.Deposits.(sDepositType1).Result = makeint(Pchar.Quest.Deposits.(sDepositType1).Sum) + ((makeint(Pchar.Quest.Deposits.(sDepositType1).Sum)/100)*makefloat(Pchar.Quest.Deposits.(sDepositType1).Interest))*iPastMonths+sti(Pchar.Quest.Deposits.(sDepositType1).Rem);
				}
				else
				{
					Pchar.Quest.Deposits.(sDepositType1).Result = makeint(Pchar.Quest.Deposits.(sDepositType1).Sum) + ((makeint(Pchar.Quest.Deposits.(sDepositType1).Sum)/100)*makefloat(Pchar.Quest.Deposits.(sDepositType1).Interest))*iPastMonths;
				}
				Link.l9 = LinkRandPhrase("내 투자를 되찾으러 왔소, 페소로.","이제 나에게 빚진 은화를 돌려받을 때다.","내 투자금을 이자까지 모두 포함해서 페소로 돌려받아야 하오.");
				Link.l9.go = "Deposit_return";									
			}
			
			if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType2)) && makeint(Pchar.Quest.Deposits.(sDepositType2)) == true)
			{
				iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Deposits.(sDepositType2).StartYear),makeint(Pchar.Quest.Deposits.(sDepositType2).StartMonth),makeint(Pchar.Quest.Deposits.(sDepositType2).StartDay), makefloat(Pchar.Quest.Deposits.(sDepositType2).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
				if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType2)+ ".Rem"))
				{
					Pchar.Quest.Deposits.(sDepositType2).Result = makeint(Pchar.Quest.Deposits.(sDepositType2).Sum) + ((makeint(Pchar.Quest.Deposits.(sDepositType2).Sum)/100)*makeint(Pchar.Quest.Deposits.(sDepositType2).Interest))*iPastMonths+sti(Pchar.Quest.Deposits.(sDepositType2).Rem);
				}
				else
				{
					Pchar.Quest.Deposits.(sDepositType2).Result = makeint(Pchar.Quest.Deposits.(sDepositType2).Sum) + ((makeint(Pchar.Quest.Deposits.(sDepositType2).Sum)/100)*makeint(Pchar.Quest.Deposits.(sDepositType2).Interest))*iPastMonths;
				}
				Link.l10 = LinkRandPhrase("저는 제 투자금을 두블룬으로 회수하고 싶습니다.","이제 당신이 내게 빚진 금을 돌려받을 때다.","내가 투자한 두블룬과 모든 이자를 돌려받아야 하오.");
				Link.l10.go = "Deposit_return_dub";									
			}
/*			
			
*/			
			//выход
			if (sTemp == "credit")
			{
				link.l11 = "내 빚이 있다는 것은 기억하오, 하지만 아직 갚을 준비가 되어 있지 않소...";
				link.l11.go = "Loan_Remind";
			}
			else
			{
				link.l11 = "제 실수였군요, 당신과는 금전적으로 얽힌 일이 없습니다. 안녕히 가십시오.";
				link.l11.go = "exit";
			}
		break;
		
		//============== кредиты ===============
		case "loan":
            if (sti(NPChar.nation) == PIRATE)
            {
                dialog.text = "아니오, 도와드릴 수 없습니다. 이 골치 아픈 곳에서는 투자만 받을 수 있소. 은화 페소나 금화 두블룬으로 투자하실 수 있습니다.";				
                if(makeint(Pchar.money) >= 100)
				{
	                Link.l1 = "페소를 투자하고 싶으니, 금액에 대해 이야기해 봅시다.";
	                Link.l1.go = "deposit";
				}				
				if(CheckUseDublons(NPChar))
				{
					Link.l2 = "두블론을 투자하고 싶소. 금액을 명확히 합시다.";
					Link.l2.go = "deposit_dub";
				}
                Link.l3 = "관심 없소.";
				link.l3.go = "exit";
                break;
            }
			// проверка на проф пригодность -->
            if (isBadReputation(pchar, 42))
            {
                dialog.text = RandSwear()+"당신의 이름은 "+GetFullName(pchar)+", 맞지? 당신은 "+RandPhraseSimple("나쁜 평판 ","나쁜 평판 ")+" 그리고 나는 너와 거래하고 싶지 않아.";
				link.l1 = RandPhraseSimple("사람이 실수할 수도 있지 않소?",RandSwear()+"뭐든지 상관없어!");
				link.l1.go = "exit";
                break;
            }
            // проверка на проф пригодность <--
			Dialog.snd = "voice\USDI\USDI016";
			dialog.text = "오, 언제든 환영입니다. 얼마가 필요하십니까?";
			Link.l1 = "작은 것으로.";
			Link.l1.go = "Small";
			Link.l2 = "보통입니다.";
			Link.l2.go = "Medium";
			Link.l3 = "가능한 한 크게.";
			Link.l3.go = "Large";
		break;

		case "small":
			Pchar.Quest.Loans.(NPC_Area).Sum = 500*makeint(Pchar.rank)+125*GetSummonSkillFromName(pchar,SKILL_COMMERCE);
			Dialog.snd = "voice\USDI\USDI017";
			dialog.text = "훌륭합니다! 소액 거래가 항상 훨씬 수월하지요 – 양측 모두에게 위험이 적으니까요. 제가 제안드릴 수 있는 것은 "+FindRussianMoneyString(sti(Pchar.Quest.loans.(NPC_Area).sum))+"...";
			Link.l1 = "거래하겠소. 그리고 그대 몫은 어떻게 하겠소?";
			Link.l1.go = "Interest";
			Link.l2 = "나한테는 통하지 않아. 바꿔보자.";
			Link.l2.go = "Loan";
			Link.l3 = "저 때문에 빚을 지지 않는 게 낫겠지요. 안녕히 가십시오.";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "Medium":
			Pchar.Quest.Loans.(NPC_Area).Sum = 1500*makeint(Pchar.rank)+325*GetSummonSkillFromName(pchar,SKILL_COMMERCE);
			Dialog.snd = "voice\USDI\USDI018";
			dialog.text = "문제없소. 바라건대\n "+FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).sum))+" 당신의 문제를 해결하는 데 도움이 될 것입니다. 꽤 큰 금액이군요.";
			Link.l1 = "거래하겠소. 그리고 당신 몫은 어떻게 하겠소?";
			Link.l1.go = "Interest";
			Link.l2 = "나한텐 통하지 않아. 바꿔 보자.";
			Link.l2.go = "Loan";
			Link.l3 = "빚은 멀리하는 게 나을 것 같군. 안녕히 계시오.";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "Large":
			Pchar.Quest.Loans.(NPC_Area).Sum = 4000*makeint(Pchar.rank)+600*GetSummonSkillFromName(pchar,SKILL_COMMERCE);
			Dialog.snd = "voice\USDI\USDI019";
			dialog.text = "음... 위험하군요. 좋습니다, 당신에게 대출을 해드릴 준비가 되어 있습니다. "+FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).sum))+". 이해해 주시길 바랍니다, 선장님, 이것은 정말로 상당한 금액입니다. 신중히 받아들여 주시기 바랍니다.";
			Link.l1 = "좋소. 그리고 당신 몫은 어떻게 할 생각이오?";
			Link.l1.go = "Interest";
			Link.l2 = "나한텐 통하지 않아. 바꿔보자.";
			Link.l2.go = "Loan";
			Link.l3 = "빚은 멀리하는 게 좋겠군. 안녕히.";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "Interest":
			Pchar.Quest.Loans.(NPC_Area).Interest = 4.0 + (makeint((((6.0 - 4.0) * (GetSummonSkillFromName(pchar, "Commerce") + GetSummonSkillFromName(pchar, "Leadership")) / 200) ) / 0.5 + 0.5)) * 0.5;
			//Pchar.Quest.Loans.(NPC_Area).Interest = 16 - makeint(Pchar.skill.commerce);
			// Rebbebion, добавил фикс отображения знака процента
			Dialog.snd = "voice\USDI\USDI020";
			dialog.text = fts(stf(Pchar.Quest.Loans.(NPC_Area).Interest), 1)+"월 %%입니다. 내가 아는 한, 당신에게 더 나은 조건을 제시할 수는 없습니다."; 
			Link.l1 = "좋아. 이제 시간에 대해 이야기하자.";
			Link.l1.go = "Period";
			Link.l3 = "빚은 멀리하는 게 나을 것 같군. 안녕히 계시오.";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "Period":
			Pchar.Quest.Loans.(NPC_Area).Period = makeint(makeint(Pchar.reputation.nobility)/20) + 1;			
			Dialog.snd = "voice\USDI\USDI021";
			dialog.text = "내가 당신에 대해 아는 것을 고려하면, "+Pchar.name+", 이 대출의 상환을 위해 기다리겠소 "+FindRussianMonthString(sti(Pchar.Quest.Loans.(NPC_Area).Period))+". 그 후에 나는 적절한 조치를 취할 것이오. 이해해 주시길 바라오."; 
			Link.l1 = "기꺼이 당신의 조건을 받아들이겠소... 그리고 당신의 동전도 말이오.";
			Link.l1.go = "LoanGranted";
			Link.l3 = "실례지만, 그건 제게 맞지 않겠군요. 안녕히 가십시오.";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "LoanGranted":
			Dialog.snd = "voice\USDI\USDI022";
			dialog.text = "진심으로 반갑소. 하지만 경고 하나 하겠소. 나는 이 일을 오래 해왔고, 내 투자를 회수하는 방법을 잘 알고 있소. 그러니 어리석은 생각이 든다면 그냥 접는 것이 좋을 것이오\n기분 나쁘게 듣지 마시오, 단지 경고일 뿐이오.";
			Link.l1 = "흠... 그렇군. 안녕히 가시오.";
			Link.l1.go = "LoanGranted_exit";
		break;

		case "Loan_Remind":
			Dialog.snd = "voice\USDI\USDI023";
			dialog.text = "선장님, 선택은 당신의 몫이오. 내 이자는 계속 불어나고 있으니, 시간이 그리 많지 않소.";
			Link.l1 = "걱정하지 마시오. 또 봅시다.";
			Link.l1.go = "exit";
		break;

		case "loan_return":
			addMoneyToCharacter(Pchar, -(makeint(Pchar.Quest.Loans.(NPC_Area).Result)));
			// boal 27.01.2004 -->
            if (npchar.quest.trade_date != lastspeak_date) // дыра с прокачкой была
            {
    			AddCharacterExpToSkill(Pchar, "Commerce", makeint(Pchar.Quest.Loans.(NPC_Area).Result) / 350);
    			AddCharacterExpToSkill(Pchar, "Leadership", makeint(Pchar.Quest.Loans.(NPC_Area).Result) / 700);
			}
			// boal 27.01.2004 <--
			DeleteAttribute(PChar, "quest.Loans_" + NPC_Area); // bug fix
			DeleteAttribute(PChar, "quest.Loans." + NPC_Area);
			Dialog.snd1 = "voice\USDI\USDI024";
			Dialog.snd2 = "voice\USDI\USDI025";
			Dialog.snd3 = "voice\USDI\USDI026";
			dialog.text = LinkRandPhrase("훌륭합니다! 동전이 필요할 때 언제든 저를 찾아오십시오. 언제든 당신을 위해 봉사하겠습니다.","감사합니다. 제때 빚을 갚을 수 있는 분과 거래하는 것은 언제나 기쁜 일이지요. 때로는 일이 생기기도 하는 법이고, 저도 이해합니다만... 그래도 문제는 해결되는 편이 좋습니다.","오, 그대에게 믿음을 준 것이 옳았군, "+GetAddress_Form(NPChar)+"! 이번이 제 서비스를 마지막으로 이용하는 일이 아니길 바랍니다. 이제 당신이 정직한 분임을 알았으니, 앞으로는 더 좋은 거래를 성사시켜 드릴 수도 있겠군요.");
			Link.l1 = LinkRandPhrase("돈을 좀 빌리고 싶소.","정말 페소가 좀 필요해.","작은 대출 하나 어떠신가요?");
			Link.l1.go = "loan";			
			if(makeint(PChar.money) >= 100)
			{
				Link.l2 = LinkRandPhrase("제 돈을 투자하고 싶습니다.","해적 전리품을 좀 보관하시겠습니까?","혹시 만일을 대비해 은화를 조금 맡겨도 되겠습니까?");
				Link.l2.go = "deposit";				
			}		
			if(CheckUseDublons(NPChar))	
			{
				Link.l3 = "이자 목적으로 두블룬을 투자하고 싶소";
				Link.l3.go = "deposit_dub";				
			}
			Link.l4 = "안녕히 가십시오, "+NPchar.name+".";
			Link.l4.go = "ExitDelLoan1";
		break;

		case "deposit":
			dialog.text = LinkRandPhrase("현명한 분을 뵙는군요! 얼마를 투자하시겠습니까?","좋습니다. 믿으십시오, 이 금액은 이곳에서 안전하게, 이자까지 모두 포함해 당신을 기다릴 것입니다.","이 인생에서 진정으로 중요한 것이 무엇인지 아시는군요. 얼마나 투자하시겠습니까?");
			link.l1.edit = 3;
			link.l1 = "";	
			Link.l1.go = "result";
		break;
		
		case "result":
			Pchar.QuestTemp.Deposits.(sDepositType1).Interest = GetDepositRate();
			Pchar.QuestTemp.Deposits.(sDepositType1).Sum = dialogEditStrings[3];
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp <= 0)
			{
				dialog.text = "농담하는 거야?";
				link.l1 = "내 실수요.";
				link.l1.go = "exit";
				break;
			}
			if (iTemp > sti(pchar.money))
			{
				dialog.text = "흠, 안타깝게도 그 정도 돈은 없으시군요. 진지하게 말씀드리겠습니다...";
				link.l1 = "좋소.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "좋습니다. 제가 제안할 수 있는 것은... 그렇죠..."+fts(stf(Pchar.QuestTemp.Deposits.(sDepositType1).Interest), 1)+" %. 한 달 기준입니다, 물론.";
			Link.l1 = "저는 괜찮습니다.";
			Link.l1.go = "Deposit_placed";
			Link.l2 = "금액을 바꾸는 게 좋겠군.";
			Link.l2.go = "Deposit";
			Link.l3 = "이건 나쁜 생각이었던 것 같군... 작별이오.";
			Link.l3.go = "Exit";
		break;

		case "Deposit_placed":
			Dialog.snd = "voice\USDI\USDI033";
			if ( !CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)+".Result"))
			{
			    Pchar.Quest.Deposits.(sDepositType1).Result = 0;//fix
			}
			// boal limit
			if ( (sti(Pchar.Quest.Deposits.(sDepositType1).Result) + sti(Pchar.QuestTemp.Deposits.(sDepositType1).Sum)) > sti(NPChar.UsurerDeposit)*1000)
			{
			    dialog.text = "실례합니다, 선장님, 하지만 이 금액은 저희 식민지 은행에는 너무 큽니다. 이자로 드릴 돈을 지급할 수 없겠군요. 그리고 믿을 만한 경비도 부족하고요... 이해해 주시길 바랍니다. 아무튼, 제가 선장님께 받을 수 있는 최대 금액은 "+FindRussianMoneyString(MakeMoneyShow(sti(NPChar.UsurerDeposit)*1000,MONEY_SIGN,MONEY_DELIVER))+".";
				Link.l1 = "유감이군, 그럼 다른 은행가를 찾아야겠어.";
				Link.l1.go = "Exit";
			}
			else
			{
				dialog.text = "이제 가장 거센 폭풍이 몰아쳐도 당신이 한 푼도 없이 남겨지지는 않을 것이라 확신하셔도 됩니다.";
				Link.l1 = "알겠소. 또 봅시다.";
				Link.l1.go = "Deposit_Exit";
			}
		break;
		
		case "Deposit_return":
			Dialog.snd = "voice\USDI\USDI034";
			dialog.text = "약속한 이자와 지난 시간을 고려하면, 내가 당신에게 빚진 금액은 "+FindRussianMoneyString(sti(Pchar.Quest.Deposits.(sDepositType1).Result))+"... 정말로 그 돈을 가져가시겠습니까?";
			Link.l1 = "물론이지. 내게 줘.";			
			Link.l1.go = "Deposit_return_1";		
			Link.l2 = "제 돈의 일부를 찾고 싶습니다.";			
			Link.l2.go = "Deposit_return_part";
			Link.l3 = "옳은 말씀입니다. 잠시 당신께 맡기겠습니다. 좋은 하루 되십시오.";			
			Link.l3.go = "Exit";		
		break;		
		
		case "Deposit_exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)+ ".Rem"))
			{
				DeleteAttribute(Pchar,"Quest.Deposits." + (sDepositType1)+ ".Rem");
			}
			Pchar.Quest.Deposits.(sDepositType1).Interest = stf(Pchar.QuestTemp.Deposits.(sDepositType1).Interest);
			Pchar.Quest.Deposits.(sDepositType1).Sum      = sti(Pchar.QuestTemp.Deposits.(sDepositType1).Sum);
			Pchar.Quest.Deposits.(sDepositType1).city 	  = NPC_Area;	

			AddMoneyToCharacter(Pchar, -(makeint(Pchar.Quest.Deposits.(sDepositType1).Sum)));
			// общий долг
			Pchar.Quest.Deposits.(sDepositType1).Sum = sti(Pchar.Quest.Deposits.(sDepositType1).Result) + sti(Pchar.Quest.Deposits.(sDepositType1).Sum);
			Pchar.Quest.Deposits.(sDepositType1) = true;
			Pchar.Quest.Deposits.(sDepositType1).StartDay 	= getDataDay();
			Pchar.Quest.Deposits.(sDepositType1).StartMonth = getDataMonth();
			Pchar.Quest.Deposits.(sDepositType1).StartYear 	= getDataYear();
			Pchar.Quest.Deposits.(sDepositType1).StartTime 	= getTime();
			DialogExit();
		break;
		
		//--> Jason забор денег по частям
		case "Deposit_return_part":
			dialog.text = "얼마나 됩니까?";
			link.l1.edit = 4;
			link.l1 = "";	
			Link.l1.go = "result_part";
		break;

		case "result_part":
			iTemp = sti(dialogEditStrings[4]);
			if (iTemp <= 0)
			{
				dialog.text = "정말 어이없는 농담이었어요, 나리!";			
				link.l1 = "젠장! 정말 유감이오... 금액을 다시 정합시다.";	
				Link.l1.go = "Deposit_return_part";
				break;
			}
			if (iTemp > sti(Pchar.Quest.Deposits.(sDepositType1).Result))
			{
				dialog.text = "당신 계좌에는 그만한 돈이 없습니다.";			
				link.l1 = "젠장! 내 실수군. 금액을 바꾸자.";	
				Link.l1.go = "Deposit_return_part";
				break;
			}
			if (iTemp == sti(Pchar.Quest.Deposits.(sDepositType1).Result))
			{
				dialog.text = "전부 다? 좋소, 말씀대로 하겠습니다. 여기 돈이오.";			
				link.l1 = "감사합니다!";	
				Link.l1.go = "Deposit_return_all";
				break;
			}
			dialog.text = "좋소. 가져가시오. 여기 돈이오.";			
			link.l1 = "감사합니다!";	
			Link.l1.go = "result_part_1";
		break;
		
		case "result_part_1":
			DialogExit();
			iTemp = sti(dialogEditStrings[4]);
			addMoneyToCharacter(Pchar, iTemp);
			iRes = sti(Pchar.Quest.Deposits.(sDepositType1).Result)-iTemp; //остаток на счете
			fPer = stf(Pchar.Quest.Deposits.(sDepositType1).Interest);
			iDep = sti(Pchar.Quest.Deposits.(sDepositType1).Sum); //стартовая сумма
			if (iRes <= sti(Pchar.Quest.Deposits.(sDepositType1).Sum)) // стало меньше начальной суммы
			{
				DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
				Pchar.Quest.Deposits.(sDepositType1).Interest = fPer;
				Pchar.Quest.Deposits.(sDepositType1).Sum = iRes;
				Pchar.Quest.Deposits.(sDepositType1).Result = 0;
			}
			else // если остаток больше начальной суммы - проценты продолжаем считать с неё, а не с остатка, ибо нефиг, дельту приплюсуем к набежавшим процентам - банкир Jason :) 
			{
				DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
				Pchar.Quest.Deposits.(sDepositType1).Interest = fPer;
				Pchar.Quest.Deposits.(sDepositType1).Sum = iDep;
				Pchar.Quest.Deposits.(sDepositType1).Rem = iRes-iDep;
			}
			Pchar.Quest.Deposits.(sDepositType1).city 	  	= NPC_Area;	
			Pchar.Quest.Deposits.(sDepositType1) 			= true;
			Pchar.Quest.Deposits.(sDepositType1).StartDay 	= getDataDay();
			Pchar.Quest.Deposits.(sDepositType1).StartMonth = getDataMonth();
			Pchar.Quest.Deposits.(sDepositType1).StartYear 	= getDataYear();
			Pchar.Quest.Deposits.(sDepositType1).StartTime 	= getTime();
		break;
		
		case "Deposit_return_all":
			DialogExit();
			iTemp = sti(dialogEditStrings[4]);
			addMoneyToCharacter(Pchar, iTemp);
			DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
		break;
		//<-- забор денег по частям		
		
		case "Deposit_return_1":
			addMoneyToCharacter(Pchar, makeint(Pchar.Quest.Deposits.(sDepositType1).Result));
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = "아... 잃어버리니 정말 힘들군. 이 돈에 정말 익숙해졌었는데. 그래도 또 오시오.";			
			Link.l1 = "필요하면 그렇게 하겠소. 안녕히 계시오.";			
			Link.l1.go = "Exit";
			DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
		break;
		
		//  ugeen -> вклады в дублонах	
		case "deposit_dub":
			dialog.text = LinkRandPhrase("현명한 분을 뵙는군요! 얼마를 투자하시겠습니까?","좋습니다. 믿으십시오, 이 금액은 이곳에서 안전하게, 그리고 모든 이자와 함께 당신을 기다릴 것입니다.","이 인생에서 진정으로 중요한 것이 무엇인지 알고 계시는군요. 얼마를 투자하시겠습니까?");
			link.l1.edit = 3;
			link.l1 = "";	
			Link.l1.go = "result_dub";
		break;
		
		case "result_dub":		
			iTotalDublonQty = GetCharacterItem(pchar,"gold_dublon") + CheckItemMyCabin("gold_dublon");		
			Pchar.QuestTemp.Deposits.(sDepositType2).Interest = 1;
			Pchar.QuestTemp.Deposits.(sDepositType2).Sum = dialogEditStrings[3];
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp <= 0)
			{
				dialog.text = "농담이냐?";
				link.l1 = "흠, 내 실수로군...";
				link.l1.go = "exit";
				break;
			}						
			if (iTemp > iTotalDublonQty)
			{
				dialog.text = "흠, 안타깝게도 그 정도 돈은 없으시군요. 진지하게 생각해봅시다...";
				link.l1 = "흠... 좋군.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "좋습니다. 제가 드릴 수 있는 것은... 그렇죠..."+Pchar.QuestTemp.Deposits.(sDepositType2).Interest+" %. 물론 한 달 기준입니다.";
			Link.l1 = "나에게는 괜찮소.";
			Link.l1.go = "Deposit_placed_dub";
			Link.l2 = "금액을 바꾸는 게 좋겠군.";
			Link.l2.go = "Deposit_dub";
			Link.l3 = "내 금화를 그냥 두는 게 낫겠군. 안녕히 가시오.";
			Link.l3.go = "Exit";
		break;
		
		case "Deposit_placed_dub":
			Dialog.snd = "voice\USDI\USDI033";
			if ( !CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType2)+".Result"))
			{
			    Pchar.Quest.Deposits.(sDepositType2).Result = 0;//fix
			}
			// boal limit
			if ( (sti(Pchar.Quest.Deposits.(sDepositType2).Result) + sti(Pchar.QuestTemp.Deposits.(sDepositType2).Sum)) > sti(NPChar.UsurerDeposit)*10)
			{
			    dialog.text = "실례합니다, 선장님, 하지만 이 금액은 저희 식민지 은행에 너무 큽니다. 이자로 드릴 돈을 마련할 수 없겠군요. 그리고 믿을 만한 경비도 부족하니... 이해해 주시기 바랍니다. 아무튼, 제가 선장님께 받을 수 있는 최대 금액은 "+FindRussianDublonString(MakeMoneyShow(sti(NPChar.UsurerDeposit)*10,MONEY_SIGN,MONEY_DELIVER))+".";
				Link.l1 = "유감이군, 그럼 다른 은행가를 찾아야겠어.";
				Link.l1.go = "Exit";
			}
			else
			{
				dialog.text = "이제 아무리 거센 폭풍이 몰아쳐도 당신이 동전 한 푼 없이 남겨지지는 않을 것이라 확신할 수 있습니다.";
				Link.l1 = "좋군. 안녕히 가시오.";
				Link.l1.go = "Deposit_Exit_dub";
			}
		break;
		
		case "Deposit_return_dub":
			Dialog.snd = "voice\USDI\USDI034";
			dialog.text = "약속한 이자와 지난 시간을 고려하면, 내가 당신에게 빚진 금액은 "+FindRussianDublonString(sti(Pchar.Quest.Deposits.(sDepositType2).Result))+"... 정말로 돈을 가져가시겠습니까?";
			Link.l1 = "물론이지. 내게 주시오.";			
			Link.l1.go = "Deposit_return_dub_1";		
			Link.l2 = "제 돈의 일부를 찾고 싶습니다.";			
			Link.l2.go = "Deposit_return_dub_part";
			Link.l3 = "옳으십니다. 잠시 당신께 맡기지요. 좋은 하루 보내십시오.";			
			Link.l3.go = "Exit";		
		break;	

		case "Deposit_exit_dub":
			NextDiag.CurrentNode = NextDiag.TempNode;		
			if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType2)+ ".Rem"))
			{
				DeleteAttribute(Pchar,"Quest.Deposits." + (sDepositType2)+ ".Rem");
			}	
			Pchar.Quest.Deposits.(sDepositType2).Interest = sti(Pchar.QuestTemp.Deposits.(sDepositType2).Interest);
			Pchar.Quest.Deposits.(sDepositType2).Sum      = sti(Pchar.QuestTemp.Deposits.(sDepositType2).Sum);
			Pchar.Quest.Deposits.(sDepositType2).city 	  = NPC_Area;	
			
			iTemp = GetCharacterItem(pchar,"gold_dublon");
			if(iTemp > sti(Pchar.Quest.Deposits.(sDepositType2).Sum))
			{
				TakeNItems(pchar,"gold_dublon", -sti(Pchar.Quest.Deposits.(sDepositType2).Sum));
			}
			else
			{
				TakeNItems(pchar,"gold_dublon", -iTemp));
				iTemp = sti(Pchar.Quest.Deposits.(sDepositType2).Sum) - iTemp;
				GetItemMyCabin("gold_dublon", iTemp);
			}
						
			// общий долг
			Pchar.Quest.Deposits.(sDepositType2).Sum = sti(Pchar.Quest.Deposits.(sDepositType2).Result) + sti(Pchar.Quest.Deposits.(sDepositType2).Sum);
			Pchar.Quest.Deposits.(sDepositType2) = true;
			Pchar.Quest.Deposits.(sDepositType2).StartDay 	= getDataDay();
			Pchar.Quest.Deposits.(sDepositType2).StartMonth = getDataMonth();
			Pchar.Quest.Deposits.(sDepositType2).StartYear 	= getDataYear();
			Pchar.Quest.Deposits.(sDepositType2).StartTime 	= getTime();
			DialogExit();
		break;	
		
		//-->забор дублонов по частям
		case "Deposit_return_dub_part":
			dialog.text = "얼마입니까?";
			link.l1.edit = 4;
			link.l1 = "";	
			Link.l1.go = "result_dub_part";
		break;
		
		case "result_dub_part":
			iTemp = sti(dialogEditStrings[4]);
			if (iTemp <= 0)
			{
				dialog.text = "정말 어리석은 농담이군요, 나리!";			
				link.l1 = "젠장! 정말 죄송합니다... 금액을 다시 조정하지요...";	
				Link.l1.go = "Deposit_return_dub_part";
				break;
			}			
			if (iTemp > sti(Pchar.Quest.Deposits.(sDepositType2).Result))
			{
				dialog.text = "당신 계좌에 그만한 금화가 없소, 나리.";			
				link.l1 = "젠장! 내 실수군. 금액을 바꾸자...";	
				Link.l1.go = "Deposit_return_dub_part";
				break;
			}			
			if (iTemp == sti(Pchar.Quest.Deposits.(sDepositType2).Result))
			{
				dialog.text = "전부 다요? 좋습니다, 말씀하신 대로 하죠. 여기 돈입니다.";			
				link.l1 = "감사합니다!";	
				Link.l1.go = "Deposit_return_dub_all";
				break;
			}
			dialog.text = "좋소. 가져가시오. 여기 돈이오.";			
			link.l1 = "감사합니다!";	
			Link.l1.go = "result_dub_part_1";
		break;
		
		case "result_dub_part_1":
			DialogExit();
			iTemp = sti(dialogEditStrings[4]);
			TakeNItems(pchar,"gold_dublon", iTemp);
			iRes = sti(Pchar.Quest.Deposits.(sDepositType2).Result)-iTemp; //остаток на счете
			iPer = sti(Pchar.Quest.Deposits.(sDepositType2).Interest);
			iDep = sti(Pchar.Quest.Deposits.(sDepositType2).Sum); //стартовая сумма
			if (iRes <= sti(Pchar.Quest.Deposits.(sDepositType2).Sum)) // стало меньше начальной суммы
			{
				DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType2));
				Pchar.Quest.Deposits.(sDepositType2).Interest = iPer;
				Pchar.Quest.Deposits.(sDepositType2).Sum = iRes;
				Pchar.Quest.Deposits.(sDepositType2).Result = 0;
			}
			else // если остаток больше начальной суммы - проценты продолжаем считать с неё, а не с остатка, ибо нефиг, дельту приплюсуем к набежавшим процентам - банкир Jason :) 
			{
				DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType2));
				Pchar.Quest.Deposits.(sDepositType2).Interest = iPer;
				Pchar.Quest.Deposits.(sDepositType2).Sum = iDep;
				Pchar.Quest.Deposits.(sDepositType2).Rem = iRes-iDep;
			}
			Pchar.Quest.Deposits.(sDepositType2).city 	  	= NPC_Area;	
			Pchar.Quest.Deposits.(sDepositType2) 			= true;
			Pchar.Quest.Deposits.(sDepositType2).StartDay 	= getDataDay();
			Pchar.Quest.Deposits.(sDepositType2).StartMonth = getDataMonth();
			Pchar.Quest.Deposits.(sDepositType2).StartYear 	= getDataYear();
			Pchar.Quest.Deposits.(sDepositType2).StartTime 	= getTime();
		break;
		
		case "Deposit_return_dub_all":
			DialogExit();
			iTemp = sti(dialogEditStrings[4]);
			TakeNItems(pchar,"gold_dublon", iTemp);
			DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType2));
		break;
		//<-- забор денег по частям		
		
		case "Deposit_return_dub_1":
			TakeNItems(pchar,"gold_dublon", sti(Pchar.Quest.Deposits.(sDepositType2).Result));
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = "아... 이 돈을 잃으니 정말 힘들군요. 정말 정이 많이 들었는데. 그래도 또 오십시오.";			
			Link.l1 = "필요하면 그렇게 하겠소. 안녕히 계시오.";			
			Link.l1.go = "Exit";
			DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType2));
		break;
		//  ugeen <- вклады в дублонах	
		
		case "DeadMotherfucker":
			Dialog.TempNode = "DeadMotherFucker_1";
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = "아직도 살아 있나? 혹시 내 돈을 돌려주러 온 건가? 제기랄! 나는 네놈 때문에 도저히 갚을 수 없을 만큼 큰돈을 잃었어! 네놈의 시체를 보기 전엔 내 마음이 결코 편할 수 없을 거다!";
            Link.l1 = "나는 그저 평화롭게 일을 해결하고 싶을 뿐이오.";
			Link.l1.go = "LoanRestore_1";
			Link.l2 = LinkRandPhrase("좋아, 그럼 어디 한번 보자! 너도 죽음에서 안전하지 않다는 걸 알아둬!","위협이라고?! 어디 한번 뭘 할 건지 보자...","돈이 우리 인생에서 가장 중요한 것은 아니오. 너무 슬퍼하지 말고, 사람을 죽이지도 마시오. 자, 어서 해보시오.");
			Link.l2.go = "ExitDelLoan2";
		break;

		case "DeadMotherFucker_1":			
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = "나가! 다시는 너를 보고 싶지 않다.";			
			Link.l1 = "...";			
			Link.l1.go = "ExitDelLoan2";
            Dialog.TempNode = "DeadMotherFucker_1";
		break;
		// boal обратимость факапства -->
		case "LoanRestore_1":
            iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Loans.(NPC_Area).StartYear),makeint(Pchar.Quest.Loans.(NPC_Area).StartMonth),makeint(Pchar.Quest.Loans.(NPC_Area).StartDay), makefloat(Pchar.Quest.Loans.(NPC_Area).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
			Pchar.Quest.Loans.(NPC_Area).Result = makeint(Pchar.Quest.Loans.(NPC_Area).Sum) + ((makeint(Pchar.Quest.Loans.(NPC_Area).Sum)/100)*makefloat(Pchar.Quest.Loans.(NPC_Area).Interest))*(iPastMonths+1);
			dialog.text = "정말입니까? 무슨 걱정이 있으십니까?";
			Link.l1 = "오늘은 내가 당신에게 빚졌소 "+FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).Result))+". 그리고 이 돈을 당신께 드리오.";
			Link.l1.go = "DeadMotherFucker_1";
            if (sti(Pchar.Money) >= 2*sti(Pchar.Quest.Loans.(NPC_Area).Result))
            {
    			Link.l2 = "좋은 관계를 회복하기 위해 내 채무를 제안하오. 그것은 "+FindRussianMoneyString(2*sti(Pchar.Quest.Loans.(NPC_Area).Result))+".";
    			Link.l2.go = "LoanRestore_2";
			}
		break;
		
		case "LoanRestore_2":
			dialog.text = "이제야 말이 통하는군! 결국 당신과 거래할 수 있겠소.";
			Link.l1 = "감사합니다. 다시는 실망시키지 않겠습니다.";
			Link.l1.go = "ExitDelLoan2";
			NextDiag.TempNode = "First time";			
			addMoneyToCharacter(Pchar, -2*sti(Pchar.Quest.Loans.(NPC_Area).Result));
			DeleteAttribute(PChar, "quest.Loans_" + NPC_Area);
			DeleteAttribute(PChar, "quest.Loans." + NPC_Area);
			ChangeCharacterHunterScore(PChar, NationShortName(sti(NPChar.nation)) + "hunter", -30);
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
		break;

		case "ExitDelLoan1":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DeleteAttribute(Pchar, "quest.Loans." + (NPC_Area));
		break;

		case "ExitDelLoan2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DeleteAttribute(Pchar, "quest.Loans." + (NPC_Area));
			DeleteAttribute(Pchar, "quest.Deposits." + (NPC_Area));
		break;
		
        case "LoanGranted_exit":
			NextDiag.CurrentNode = NextDiag.TempNode;

			AddMoneyToCharacter(Pchar, makeint(Pchar.Quest.Loans.(NPC_Area).Sum));
			Pchar.Quest.Loans.(NPC_Area) = true;
			Pchar.Quest.Loans.(NPC_Area).StartDay = getDataDay();
			Pchar.Quest.Loans.(NPC_Area).StartMonth = getDataMonth();
			Pchar.Quest.Loans.(NPC_Area).StartYear = getDataYear();
			Pchar.Quest.Loans.(NPC_Area).StartTime = getTime();

			sTemp = "Loans_" + NPC_Area;			
			SetTimerCondition(sTemp, 0, makeint(Pchar.Quest.Loans.(NPC_Area).Period), 0, false);
			pchar.quest.(sTemp).CityId = NPC_Area;
			pchar.quest.(sTemp).win_condition = "LoansForAll";
			
			DialogExit();
			npchar.quest.trade_date = lastspeak_date; // дыра с прокачкой была
		break;
        
		//работорговец
		int iSlaveMoney;
		int amount;
		case "GiveTaskSlave":
			pchar.questTemp.Slavetrader.iSlaveQuantity = 100;
			pchar.questTemp.Slavetrader.iSlaveMoney = sti(pchar.questTemp.Slavetrader.iSlaveQuantity) * 250;
			dialog.Text = "아, 이봐! 우리 둘 다 진지한 사람들이잖아. 단 한 닢을 위해 목숨까지 내놓는 멍청이들보다는 훨씬 낫지. 그 돈으로 두 닢을 만들어볼 생각조차 안 하는 놈들이니까\n나는 진짜 사업을 제안할 만한 사람을 찾고 있네. 용감하고 적극적이며, 정직하고 시간을 잘 지키지만... 음... 도덕적 딜레마에 너무 얽매이지 않는 그런 사람 말이야. 그리고 내가 찾는 사람이 바로 자네이길 바라네.";
			Link.l1 = "그건 당신이 나에게 어떤 '거래'를 제안할지에 달려 있소.";
			Link.l1.go = "GiveTaskSlave_1";
		break;
			
		case "GiveTaskSlave_1":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity(npchar.city);
			dialog.Text = "좋소, 그럼 잘 들으시오. 요즘 카리브해에서 노예 무역만큼 이익이 큰 사업은 없소. 나는 플랜터는 아니지만 믿을 만한 고객들이 있지\n그래서 내가 필요한 노예 수는 다음과 같소 - "+pchar.questTemp.Slavetrader.iSlaveQuantity+" 머리 한 개당 250페소를 지불할 준비가 되어 있소. 믿으시오, 그건 공정한 가격이오. 총합으로 당신이 벌게 될 금액은\n "+FindRussianMoneyString(sti(pchar.questTemp.Slavetrader.iSlaveMoney))+".";
			Link.l1 = "아니오, 나는 노예상이 아니오. 양심을 저버리지 않는 다른 조수를 찾으시오.";
			Link.l1.go = "exit_slaves";
			Link.l2 = "매력적인 제안이군. 나도 그렇게 하고 싶어. 노예들은 언제까지 필요하지?";
			Link.l2.go = "GiveTaskSlave_2";
		break;
			
		case "exit_slaves":
			dialog.Text = "쳇, 아무도 자기 엉덩이를 움직여서 발밑의 금을 챙길 생각이 없는 것 같군. 정말 실망이야. 잘 가라, 그리고 우리 대화에 대해 소문낼 생각도 하지 마라. 내 팔은 길게 뻗으니까...";
			Link.l1 = "네 손길도 '더럽고'... 네 입도 마찬가지다. 작별이다.";
			Link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "End_quest";
			DeleteAttribute(npchar, "quest.slave");
		break;
			
		case "GiveTaskSlave_2":
			dialog.Text = "시간을 제한하지는 않겠소, 하지만 임무는 가능한 한 빨리 완수하도록 하시오. '흑상아'에 대한 수요가 매우 크오. 일을 잘 처리한다면 앞으로도 이런 일을 종종 맡기겠소.";
			Link.l1 = "좋군. 그럼, 좋은 소식 기다려.";
			Link.l1.go = "exit";						
			pchar.questTemp.Slavetrader = "Seek_slaves"; // это ввод имени квеста и состояния квеста
			AddQuestRecord("Slavetrader", "1");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("Slavetrader", "sQty", makeint(pchar.questTemp.Slavetrader.iSlaveQuantity));
			AddQuestUserData("Slavetrader", "sSum", makeint(pchar.questTemp.Slavetrader.iSlaveMoney));
			LAi_LocationDisableOfficersGen(&Locations[FindLocation(pchar.location)], true); // блокируем вход офицеров 2015
		break;
			
		case "Checkslaves":
			amount = GetSquadronGoods(Pchar, GOOD_SLAVES) - sti(pchar.questTemp.Slavetrader.iSlaveQuantity);
			dialog.Text = "'흑상아' 화물을 구하는 데 성공하셨습니까?";
            if (amount < 0)
			{
				Link.l1 = "아직 아닙니다. 우리의 합의가 여전히 유효한지 확인만 하고 있습니다.";
            	Link.l1.go = "exit";
			}
			else
			{
				Link.l1 = "있소. 전부 내 화물에 있소.";
            	Link.l1.go = "Takeslaves";
			}
		break;
		
		case "Takeslaves":
			amount = sti(pchar.questTemp.Slavetrader.iSlaveQuantity);
			dialog.Text = "훌륭하군. 내 부하들이 그것들을 가져갈 것이오... 세관이나 요새 사령관은 걱정하지 마시오. 나는 여기서 대규모 사업을 운영하고 있으니, 아무 문제도 없을 것이며 밀수 혐의로 누가 당신을 비난할 일도 없소.";
			Link.l1 = "여기서 입지가 꽤 단단해 보이는데... 그럼 내 보수는 어떻게 됩니까?";
            Link.l1.go = "Takeslaves_1";
			RemoveCharacterGoods(Pchar, GOOD_SLAVES, amount);
		break;
		
		case "Takeslaves_1":
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.Slavetrader.iSlaveMoney));
			dialog.Text = "여기 있습니다. 나는 허튼소리하지 않소. 나와 함께 하시오, 선장. 곧 금이 너무 많아 갤리온이 필요할 테니!";
			Link.l1 = "그거 참 좋겠군, 하하... 다음엔 뭐지?";
            Link.l1.go = "Takeslaves_2";
		break;
		
		case "Takeslaves_2":
			dialog.Text = "다음은? 3주 후에 다시 오시오. 지금 거래를 진행 중이니, 그때쯤이면 준비되어 있을 것이오.";
			Link.l1 = "좋소, 거래하겠소. 안녕히 가시오.";
            Link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "2");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			pchar.questTemp.Slavetrader = "wait";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait");//запомнить дату
		break;
		
		case "Takeslaves_3":
			if (4-sti(RealShips[sti(pchar.ship.type)].Class) < 0)//проверка класса корабля
			{
				dialog.Text = "일거리가 있소만, 당신 배가 너무 약하오. 임무를 실패하게 하고 싶지도 않고, 당신을 죽음으로 내몰고 싶지도 않소. 아직 시간이 있으니, 바커틴, 브리건틴, 브리그, 아니면 최소한 플루트 같은 더 큰 배를 구하시오. 시간 허비하지 마시오!";
				Link.l1 = "알겠소, 내가 처리하겠소. 또 봅시다.";
            	Link.l1.go = "Takeslaves_3_smallship";
			}
			else
			{
				dialog.Text = "드디어 왔군! 기다리고 있었소. 이제 바로 본론으로 들어가지. 알다시피, 어떤 사업이든 항상 경쟁자가 있기 마련이오... 나에게도 있지. 저 탐욕스럽고 파렴치한 놈들은 항상 내 고객을 빼앗으려고 혈안이 되어 있소! 사실, 그들 중 한 놈을 제거하고 동시에 돈도 좀 벌고 싶군.";
				Link.l1 = "경청하고 있소.";
            	Link.l1.go = "Takeslaves_4";
			}
		break;
		
		case "Takeslaves_3_smallship":
			pchar.questTemp.Slavetrader = "waitship";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Takeslaves_4":
			Slavetrader_GetRandomShore();//выбор бухты
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.questTemp.Slavetrader.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			dialog.text = "매우 훌륭하오. 이제 들으시오. 이 악당의 이름은 "+GetName(NAMETYPE_ORIG,pchar.questTemp.Slavetrader.UnknownPirateName,NAME_NOM)+", 아프리카에서 노예를 데려와서 정박했습니다 "+XI_ConvertString(pchar.questTemp.Slavetrader.Island.Shore+"Gen")+", 라는 섬에 있어 "+XI_ConvertString(pchar.questTemp.Slavetrader.Island)+". 그는 그곳에서 밀수업자들을 기다리고 있소. 그의 갤리언 이름은 '"+pchar.questTemp.Slavetrader.ShipName+". 그들의 거래는 어떤 대가를 치르더라도 반드시 깨야 하오!";
			link.l1 = "노예들은 어쩌지? 그들을 수장시키는 건 너무 아깝잖아!";
			link.l1.go = "Takeslaves_5";
		break;
		
		case "Takeslaves_5":
			dialog.Text = "왜 그러시겠소? 그럴 필요 없소. "+GetName(NAMETYPE_ORIG,pchar.questTemp.Slavetrader.UnknownPirateName,NAME_NOM)+" 평판이 나빠서 그가 사라져도 아무도 신경 쓰지 않을 것이오. 그의 갤리온에 올라타 그자를 죽이고 반드시 죽었는지 확인하시오, 그리고 화물을 가져오면 내가 팔겠소. 내 정보에 따르면 노예가 약 천오백 명 정도 있소.";
			Link.l1 = "이런 젠장. 꽤 큰 금액이군. 내 보수는 어떻게 되는 거지?";
            Link.l1.go = "Takeslaves_6";
			Link.l2 = "아니오, 나리, 이런 음모는 제 일이 아닙니다. 밀수업자들과의 관계를 굳이 망칠 이유가 있겠습니까?";
            Link.l2.go = "exit_slaves_1";
		break;
		
		case "exit_slaves_1":
			dialog.Text = "음... 내가 그대에 대해 오해했던 것 같군... 작별이오, 그리고 우리 대화는 잊으시오. 여기서 들은 이야기를 퍼뜨리지도 마시오. 이 도시는 내 소유요. 그리고 만약 그대가 '를 탈 생각이라면"+pchar.questTemp.Slavetrader.ShipName+" 너 자신을 위해서라도... 내가 반드시 그대를 교수대에 올려놓을 것이오. 명심하시오.";
			Link.l1 = "걱정 마시오, 관청에 신고하지도 않을 것이고 그대의 갈레온도 필요 없소. 안녕히 가시오.";
            Link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "8");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase(" agreed"," agreed"));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";//конец квеста
		break;
		
		case "Takeslaves_6":
			dialog.Text = "내가 화물 위치를 알려줬고, 그 덕분에 '전리품'을 찾아 항해할 필요도 없으니, 보수는 조금 낮아졌소 – 머리당 200페소요. 그래도 성공하면 30만 페소와 배 한 척이니, 상당한 금액이오.";
			Link.l1 = "좋소. 시간이 얼마나 있소?";
            Link.l1.go = "Takeslaves_7";
			Link.l2 = "호호! 당신 말투를 들어보니 마치 그 노예들이 스스로 내 배까지 헤엄쳐 와서 내 화물칸에 들어가려고 안달이 난 것 같군! 내 사람들이 그까짓 푼돈 때문에 목숨을 걸 거라 정말 생각하시오? 보수를 올리시오, 아니면 나 이 일에서 손 뗄 것이오.";
            Link.l2.go = "exit_slaves_1";
		break;
		
		case "Takeslaves_7":
			dialog.text = "2주일 시간이 있소. 늦으면 그는 화물을 옮길 것이고, 모든 것이 끝나고 말 것이오.";
			link.l1 = "서둘러야겠군. 좋은 소식을 들고 오겠소.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "3");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
			AddQuestUserData("Slavetrader", "sShoreName", XI_ConvertString(pchar.questTemp.Slavetrader.Island.Shore + "Dat")); // belamour gen
			AddQuestUserData("Slavetrader", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.questTemp.Slavetrader.Island) + "Voc")); // belamour gen
			pchar.quest.Slavetrader_ShipsAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_ShipsAttack.win_condition.l1.location = pchar.questTemp.Slavetrader.Island;
            pchar.quest.Slavetrader_ShipsAttack.function = "Slavetrader_CreateSlaveShips";//создание кораблей
			SetFunctionTimerCondition("Slavetrader_SlaveShipsOver", 0, 0, 15, false);	//таймер
			pchar.questTemp.Slavetrader = "wait1";	//это заглушка
		break;
		
		case "Takeslaves_4_lose":
			dialog.text = "음, "+GetFullName(pchar)+", 우리의 임무는 어찌 되었소? 그 어두운 얼굴을 보니 실패한 것 같구려.";
			link.l1 = "젠장, 네 말이 맞아... 나... 그러니까, 알잖아... 내가 늦었어. 이미 그 자는 자리를 떴던 것 같아, 거기엔 아무도 없었거든. 내내 바람 따라 항해해야 했지, 젠장할... ";
			link.l1.go = "Takeslaves_5_lose";
		break;
		
		case "Takeslaves_4_win":
			dialog.text = "음, "+GetFullName(pchar)+", 오늘 수확은 어떤가? 들었는데 "+GetName(NAMETYPE_ORIG,pchar.questTemp.Slavetrader.UnknownPirateName,NAME_NOM)+" 물고기 밥이 되는구나! 하하하!";
			link.l1 = "그래, 딱 맞춰 도착했군! "+GetName(NAMETYPE_ORIG,pchar.questTemp.Slavetrader.UnknownPirateName,NAME_NOM)+" 밀수업자의 배로 노예를 옮기고 있었소. 둘 다 직접 올라타서 데이비 존스에게 보내 버렸으니, 이제 경쟁자가 줄었겠군.";
			link.l1.go = "Takeslaves_5_win";
		break;
		
		case "Takeslaves_5_lose":
			dialog.text = "그래, 내가 너를 잘못 봤던 것 같군. 늦은 거냐? 아니면 싸우기 겁났던 거냐? 뭐, 이제 다 소용없다. 꺼져라. 너와는 끝이다. 여기서 본 것도 들은 것도 다 잊어버려.";
			link.l1 = "그럼 안녕히 가십시오.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "5_5");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
		
		case "Takeslaves_5_win":
			pchar.questTemp.Slavetrader.Nation = npchar.nation;
			amount = 1600 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*200;
			if (amount < 0)
			{
				dialog.text = "내가 너에 대해 맞게 판단했군 - "+GetSexPhrase(" 자네는 멋진 깡패로군"," 그대는 사나운 아가씨로군")+"! 나는 자네 같은 인재가 필요하네. 자네는 임무를 아주 훌륭하게 완수했네 – 무려 천오백 명이 넘는 노예를 데려왔군! 안타깝게도 나는 천육백 명 분의 대금만 줄 수 있네. 나머지에 대한 돈이 부족하니, 직접 팔아야 할 걸세. 자네의 보상은 320,000페소라네.";
				link.l1 = "감사합니다. 당신과 거래해서 즐거웠습니다, "+npchar.name+"!";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, 320000);
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, 1600);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", 1600);
				AddQuestUserData("Slavetrader", "sMoney", 320000);
				break;
			}
			if (amount >= 0 && amount < 200)
			{
				dialog.text = "내가 너에 대해 옳게 판단했군 - "+GetSexPhrase(" 너는 멋진 깡패구나"," 그대는 사나운 아가씨로군")+"! 나는 자네 같은 사람이 필요하네. 임무를 가장 훌륭하게 완수했군 - 나에게 가져왔으니 "+sTemp+" 노예들. 당신의 보상은 "+FindRussianMoneyString(iSlaveMoney)+".";
				link.l1 = "감사합니다. 함께 거래해서 즐거웠습니다, "+npchar.name+"!";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 200 && amount < 600)
			{
				dialog.text = "적어도 가장 힘든 상황을 명예롭게 극복하셨군요. 비록 보상이 내가 기대한 것보다는 적지만, 그래도 만족합니다. 당신이 가져온 것은 "+sTemp+" 노예들. 보상은 "+FindRussianMoneyString(iSlaveMoney)+"";
				link.l1 = "감사합니다. 함께 거래하게 되어 기뻤습니다, "+npchar.name+"!";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 600 && amount < 1100)
			{
				dialog.text = "알겠소... 이해는 하겠으나, 나는 훨씬 더 많은 것을 기대했소. 그런데 당신이 가져온 것은 고작 이것뿐이군. "+sTemp+" 노예들. 적어도 내 경쟁자들을 없애 주었으니 그건 나름대로 가치가 있지. 보상은\n  "+FindRussianMoneyString(iSlaveMoney)+".";
				link.l1 = "감사합니다. 이해해 주셔서 고맙습니다. "+npchar.name+"!";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 1100 && amount < 1600)
			{
				dialog.text = "좋군, 하지만... 흠. 내가 그대에 대해 착각했던 것 같군. 무엇을 가져왔소? "+sTemp+" 노예들? 그럼 나머지는 어쩌고? 설마 다 침몰시켰다고는 말하지 마라. 분명 밀수업자들에게 팔았거나, 아니면 더 나쁘게는 그 악랄한 라부아지에 놈한테 넘겼겠지. 당장 꺼져라, 더 이상 너랑은 엮이고 싶지 않으니까!";
				link.l1 = "원하시는 대로 하십시오, 안녕히 가십시오.";
				link.l1.go = "node_hanter_1";
				break;
			}
			dialog.text = "좋은 말이군, 하지만... 우리 노예들은 어디 있지? 화물은 어디 있나? 설마 그걸 가라앉혔다고는 말하지 마. 분명 밀수꾼들에게 팔았거나, 아니면 더 나쁘게는 그 망할 라부아지에 놈한테 넘겼겠지. 꺼져, 너랑은 끝이야.";
			link.l1 = "원하시는 대로 하겠습니다, 안녕히 가십시오.";
			link.l1.go = "node_hanter_1";
		break;
		
		case "node_hanter_1":
			dialog.text = "이 일은 끝나지 않았다. 감히 나를 속이려 들다니! 네가 시도한 대가를 치르게 될 것이다 – 반드시 문제를 겪게 만들어 주마. 이제 당장 꺼져라!";
			link.l1 = "네 놈과 그 더러운 노예 무역은 지옥에나 떨어져라! 지금 당장 여기서 베어버려도 되지만, 나는 네 놈보다 훨씬 더 나은 사람이니까 참아주지.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "9");
			CloseQuestHeader("Slavetrader");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 30);
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Takeslaves_6_win":
			dialog.text = "우리가 함께 잘 협력하고 있는 것 같군, "+pchar.name+". 매우 기쁘군. 한 달 후에 다시 찾아오게. 어쩌면 자네에게 딱 맞는 일을 찾아줄 수도 있겠네. 이미 몇 가지 아이디어가 있네.";
			link.l1 = "알겠습니다, 한 달 후에 뵙지요. 당신과 거래하면 정말 이익이 큽니다.";
			link.l1.go = "Takeslaves_7_win";
		break;
			
		case "Takeslaves_7_win":
			dialog.text = "그것으로 큰돈을 벌 수 있을 것이오... 마지막으로 한 가지 더 묻겠소,\n "+pchar.name+", 갤리온 선실에서 이상한 점을 발견하셨습니까?";
			link.l1 = "별일 없었어, 정말로... 내가 뭐 놓친 거라도 있어?";
			link.l1.go = "Nostatue";
			if (CheckCharacterItem(pchar, "talisman8"))
			{
				link.l2 = "이 낡은 버클, 무슨 '전갈' 부적을 말하는 건가?";
				link.l2.go = "Yestatue";
			}
		break;
			
		case "Nostatue":
			dialog.text = "어쩌면 그랬을 수도, 아닐 수도 있지... 이제는 중요하지 않소. 한 달 뒤에 봅시다. 안녕히 가시오!";
			link.l1 = "또 봅시다, "+npchar.name+".";
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "Yestatue":
			dialog.text = "정확합니다! 이건 메디치 브로치입니다... 들어본 적 있으신가요? 그렇다면 정말로 그 자식의 선실에 있었던 것이군요... 제가 좀 봐도 되겠습니까?";
			link.l1 = "물론이지, 가져가.";
			link.l1.go = "Yestatue_1";
			RemoveItems(PChar, "talisman8", 1);
		break;
			
		case "Yestatue_1":
			Log_Info("You gave a talisman");
			PlaySound("interface\important_item.wav");
			dialog.text = "오, 오... 정말 그렇군. 들어보시오, "+pchar.name+", 나에게 파시오. 나는 십만 페소를 지불할 준비가 되어 있소.";
			link.l1 = "십만이라고? 흠... 알겠소. 여기 있소!";
			link.l1.go = "Buystatue";
			link.l2 = "아니, 나는 이것을 팔지 않겠소. 이 브로치의 진정한 가치는 은이나 금으로는 따질 수 없소. 이런 것들이 어떻게 돌아가는지 나는 잘 알고 있소.";
			link.l2.go = "Nobuystatue";
		break;
			
		case "Buystatue":
			dialog.text = "완벽하군요! 거래가 성사되어 기쁩니다. 돈을 가져가십시오. 한 달 후에 다시 뵙기를 기대하겠습니다.";
			link.l1 = "안녕히 가십시오, "+npchar.name+".";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 100000);
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "Nobuystatue":
			dialog.text = "보시다시피, 나는 이 피불라가 정말 절실히 필요하오! 당신 말에 전적으로 동의하오, 돈으로는 그 가치를 매길 수 없지. 어리석은 상인이라면 오천조차 주지 않을 테니. 하지만 당신이 그 가치를 진정으로 아는 것 같소, 그런 금액에도 팔지 않으니 말이오.\n 돈이 싫다면, 거래를 제안해도 되겠소? 당신이 흥미로워할 만한 것이 있소. 자, 한번 보시오. 놀랍도록 가벼운 갑옷이오! 직접 확인해 보시오! 이 갑옷을 피불라와 맞바꾸고 싶소.\n 참고로, 이건 유일한 물건이 아니오. 당신 같은 선원들은 언제든 더 구할 수 있지만, 나는 그렇지 않소. 이제 동의하겠소?";
			link.l1 = "헤... 그렇겠지. 갑옷을 내게 주고 이 브로치를 가져가.";
			link.l1.go = "Nobuystatue_yes";
			link.l2 = "아니, 이 브로치는 내게 이 갑옷보다 훨씬 더 소중하오. 내가 직접 간직하겠소.";
			link.l2.go = "Nobuystatue_no";
		break;
			
		case "Nobuystatue_yes":
			dialog.text = "훌륭하군! 거래가 성사되어 기쁩니다. 이제 이 갑옷은 당신 것입니다. 가져가시오. 한 달 후에 봅시다. 안녕히 가십시오.";
			link.l1 = "또 봅시다, "+npchar.name+".";
			link.l1.go = "exit";
			TakeNItems(pchar, "cirass7", 1);
			Log_Info("You have received a Brigandine");
			PlaySound("interface\important_item.wav");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "Nobuystatue_no":
			dialog.text = "안타깝군... 정말 안 좋네. 자, 가져가. 내가 뭐라 하진 않겠어. 한 달 후에 보자. 잘 가.";
			link.l1 = "안녕히 가십시오.";
			link.l1.go = "exit";
			TakeNItems(pchar, "talisman8", 1);
			Log_Info("You have received a talisman");
			PlaySound("interface\important_item.wav");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "EscapeSlave":
			dialog.text = "딱 맞춰 오셨군, "+pchar.name+". 임무가 있소, 시작할 준비가 되었으면 말씀하시오.";
			link.l1 = "물론이오, 준비됐소.";
			link.l1.go = "EscapeSlave_1";
		break;
			
		case "EscapeSlave_1":
			dialog.text = "훌륭하군! 이제 본론으로 들어가지. 최근 소식 들었는가?";
			link.l1 = "흠, 무슨 말씀입니까? 매일 많은 소식이 들어오고 있습니다.";
			link.l1.go = "EscapeSlave_2";
		break;
			
		case "EscapeSlave_2":
			dialog.text = "이건 전적으로 우리 사업과 관련된 일입니다. 신세계 역사상 가장 큰 노예 탈주 사건이 있었소! 천 명이 넘는 이들이 탈출했고, 그 사이에 네덜란드의 전초기지 몇 곳을 파괴하고 불태웠소.";
			link.l1 = "흥미롭군. 계속하게.";
			link.l1.go = "EscapeSlave_3";
		break;
			
		case "EscapeSlave_3":
			dialog.text = "하지만 그들은 그냥 도망친 게 아니라, 어찌 된 일인지 섬을 떠나는 데까지 성공했소! 흔적도 남기지 않았지. 마티아스 벡이 분노하고 있소. 하지만 그게 중요한 게 아니오... 중요한 건, 내가 그대에게 큐라소로 항해해 무슨 일이 있었는지 알아보고, 도망자들을 추적해 붙잡아 달라고 부탁하는 것이오\n그리고 물론, 네덜란드 법정의 무자비한 심판에서 그들을 구해주시오. 머리 하나당 300페소를 지불하겠소 - 듣자 하니 그들은 아주 쓸만한 노예가 된다더군.";
			link.l1 = "알겠소. 나는 쿠라사오로 향하겠소. 좋은 소식 가지고 기다리시오.";
			link.l1.go = "EscapeSlave_yes";
			link.l2 = "있지, 나는 그 임무를 맡지 않겠소. 나는 그들의 자유를 빼앗지 않을 것이오. 그들은 자유를 얻기 위해 목숨을 걸었소. 그들은 그럴 자격이 있소.";
			link.l2.go = "EscapeSlave_no";
		break;
			
		case "EscapeSlave_no":
			dialog.text = "정말 유감이군... 당신에게서 이런 일을 겪을 줄은 몰랐소... 그것도 가장 부적절한 때에 말이오. 이제 우리 동업 관계가 끝났다는 건 분명히 알겠지. 안녕히 가시오.";
			link.l1 = "좋은 하루 보내십시오.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "8");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "EscapeSlave_yes":
			Slavetrader_GetEscapeShore();
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(HOLLAND);
			pchar.questTemp.Slavetrader = "EscapeSlave_Villemstad";
			AddQuestRecord("Slavetrader", "22_1");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			DialogExit();
		break;
			
		case "Escape_slaves_win":
			int iSlaveMoneyH;
			string sNum;
			amount = 1100 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*300;
			sNum = GetSquadronGoods(Pchar, GOOD_SLAVES) - 1100;
			iSlaveMoneyH = makeint(sNum)*100;
			if (amount < 0)
			{
				dialog.text = "하! 어려운 임무를 해냈을 뿐만 아니라, 내가 요청한 것보다 더 많은 노예를 데려왔군 - "+sTemp+" 노예들. 하지만 "+sNum+" 노예들이 퀴라소에서 도망치지 않았소. 머리당 100페소를 지불하겠소. 이 정도면 만족하리라 생각하오. 당신의 보상은 33만 페소이며\n "+FindRussianMoneyString(iSlaveMoneyH)+" 초과분에 대해서라네, 하하.";
				link.l1 = "하! 당신은 정말 속지 않는군. 뭐라 하시든 동의하오. "+npchar.name+"!";
				link.l1.go = "Escape_slaves_win_1";
				AddMoneyToCharacter(pchar, 330000);
				AddMoneyToCharacter(pchar, makeint(iSlaveMoneyH));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "22_5");
				AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoneyH));
				break;
			}
			if (amount < 101 && amount >= 0)
			{
				dialog.text = "그 어려운 임무를 가장 훌륭하게 완수하여 내게 가져왔소 "+sTemp+" 노예들. 보상은 "+FindRussianMoneyString(iSlaveMoney)+".";
				link.l1 = "감사합니다. 함께 거래하게 되어 기쁩니다, "+npchar.name+"!";
				link.l1.go = "Escape_slaves_win_1";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "22_6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 100 && amount < 600)
			{
				dialog.text = "그 어려운 임무를 성공적으로 완수하셨군요. 보상이 기대만큼 풍족하진 않지만, 그래도 만족스럽습니다. 그래서 그것을 여기로 가져오셨군요 "+sTemp+" 노예들입니다. 보상은 "+FindRussianMoneyString(iSlaveMoney)+".";
				link.l1 = "감사합니다. 당신과 거래해서 즐거웠습니다, "+npchar.name+"!";
				link.l1.go = "Escape_slaves_win_1";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "22_6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 600 && amount < 1100)
			{
				dialog.text = "찾아왔나? 흠... 뭘 가져왔지?"+sTemp+" 노예들? 나머지 화물은 어디 있지? 설마 바다에 가라앉혔다고 둘러대려는 건 아니겠지. 분명 밀수업자들에게 팔았거나, 아니면 더 나쁘게는 이슬라-테소로의 그 자식 라부아지에에게 넘긴 게 분명하군. 당장 꺼져라, 더 이상 너와는 일하고 싶지 않으니.";
				link.l1 = "안녕히 가십시오.";
				link.l1.go = "node_hanter_1";
				break;
			}
			dialog.text = "찾았나? 노예들은 어찌 되었지? 우리 화물은 어디 있나? 설마 침몰시켰다고 말할 생각은 하지도 마라. 분명 밀수업자들에게 팔았거나, 아니면 더 나쁘게는 이슬라-테소로의 그 악당 라부아지에에게 넘겼겠지. 당장 꺼져라, 이제 더는 너와 일하고 싶지 않다.";
			link.l1 = "안녕히 가십시오.";
			link.l1.go = "node_hanter_1";
		break;
		
		case "Escape_slaves_win_1":
			dialog.text = "정말로 감사드립니다, "+pchar.name+". 정말이오. 한 달 후에 다시 오면 우리 둘 다 이익이 되는 새로운 사업을 준비해 두겠소.";
			link.l1 = "나 또한 우리의 동업 관계에 만족하오, "+npchar.name+". 한 달 후에 뵙겠습니다.";
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_2");
			pchar.questTemp.Slavetrader = "wait_2";
		break;
			
		case "Slaveshore":
			dialog.text = "딱 맞춰 오셨군요, "+pchar.name+". 나는 용감하고 거리낌 없는 선원을 찾고 있소, 하하. 내 일을 맡을 준비가 되었소?";
			link.l1 = "경청하고 있소.";
			link.l1.go = "Slaveshore_1";
		break;
			
		case "Slaveshore_1":
			pchar.questTemp.Slavetrader.Island = Islands[GetCharacterCurrentIsland(pchar)].id;
			pchar.questTemp.Slavetrader.Island.Shore = GetIslandRandomShoreId(pchar.questTemp.Slavetrader.Island);
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.questTemp.Slavetrader.Nation = NPChar.nation;
			dialog.text = "이번에는 아주 간단합니다. 오늘, 피나스가 "+pchar.questTemp.Slavetrader.ShipName+"' 깃발 아래에서 "+NationNameGenitive(sti(npchar.nation))+" 에 정박했다 "+XI_ConvertString(pchar.questTemp.Slavetrader.Island.Shore+"Gen")+" 만이었소. 현지 밀수업자들의 도움으로 대량의 '에보니'가 실려 있었지. 무려 이천 명 분량이나 되오\n선원 중에 군인은 없고, 선장은 상인이오. 전혀 위협이 되지 않으니, 배를 나포해서 화물을 가져오시오. 평소처럼 한 명당 200페소를 주겠소.";
			link.l1 = "흠... 이번 일은 지난번과 다르군. 자네는 내게 자네 나라 배를 공격하라고 제안하는 건가!";
			link.l1.go = "Slaveshore_2";
		break;
			
		case "Slaveshore_2":
			dialog.text = "이해가 안 돼, "+pchar.name+"배의 깃발이 중요하오? 정말로 그게 그렇게 신경 쓰이오?";
			link.l1 = "내가 그런가? 아니, 난 신경도 안 써. 금은 국적 따윈 없으니까. 다만 좀 뜻밖이었을 뿐이지...";
			link.l1.go = "Slaveshore_3_yes";
			link.l2 = "나는 신경 쓴다. 나는 갖고 싶지 않다 "+NationNameAblative(sti(npchar.nation))+" 내 적들 중에서.";
			link.l2.go = "Slaveshore_3_no";
		break;
			
		case "Slaveshore_3_no":
			dialog.text = "진심이오? 농담하는 거겠지, 요즘은 아무도 믿을 수 없다네... 그렇다면, 당장 꺼지시오. 그리고 여기서 본 거나 들은 건 모두 잊어버리시오!";
			link.l1 = "또 봅시다,"+npchar.name+".";
			link.l1.go = "node_hanter_1";
		break;
			
		case "Slaveshore_3_yes":
			dialog.text = "왜 놀라시오? 내가 동전의 국적 따위에 신경 쓰지 않아서 그런가? 분명히 말씀드리지만, 정말로 신경 쓰지 않소. 솔직히 말해, 애국심은 전문 은행가에게 해로울 뿐이오. 언젠가 파산하고 싶지 않다면 말이오\n철학은 이쯤에서 그만두고 본론으로 들어갑시다. 배는 자정까지 여기 머물 것이니, 시간이 그리 많지 않소. 준비되었소?";
			link.l1 = "예, "+npchar.name+", 나는 가는 중이오.";
			link.l1.go = "Slaveshore_4";
		break;
			
		case "Slaveshore_4":
			dialog.text = "훌륭하군요. 그대라면 우리의 임무를 반드시 성공시킬 것이라 믿어 의심치 않소. 행운을 빕니다."+pchar.name+".";
			link.l1 = "감사합니다! 안녕히 가십시오.";
			link.l1.go = "exit";
            AddQuestRecord("Slavetrader", "10");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sShip", pchar.questTemp.Slavetrader.ShipName);
			pchar.quest.Slavetrader_ShoreAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_ShoreAttack.win_condition.l1.location = pchar.questTemp.Slavetrader.Island;//отправляем в локацию
            pchar.quest.Slavetrader_ShoreAttack.function = "Slavetrader_CreateShoreShips";//создание кораблей
			SetFunctionTimerCondition("Slavetrader_ShoreShipsOver", 0, 0, 1, false);	//таймер
			pchar.questTemp.Slavetrader = "wait1";	//заглушка
		break;
			
		case "Pinas_lose":
		dialog.text = "음, "+GetFullName(pchar)+", 임무는 어떻게 되었소? 그 어두운 얼굴을 보니 실패한 것 같구려.";
			link.l1 = "네 말이 맞아... 나... 그게... 내가 너무 늦었어. 선술집에 있었는데, 바다로 나갔을 땐 아무도 없더군.";
			link.l1.go = "Takeslaves_5_lose";
		break;
			
		case "Slaveshore_5":
			dialog.text = ""+pchar.name+", 제발 진정하십시오. 제 잘못이 아닙니다! 젠장, 보고를 너무 늦게 받았소... 배신이 있었소! 내가 믿던 부하 중 한 명이 나를 팔아넘겼소!";
			link.l1 = "좋아, 네가 진실을 말하고 있다는 건 알겠다. 네 운이 좋은 거다. 핀네이스 선장이 우리 '거래'가 들통났다고 내게 말해줬으니 말이지. 그가 입을 놀리지 않았다면 넌 이미 죽었을 거다. 그런데 너, 이 피에 절은 돈자루 녀석, 그동안 줄곧 '이 마을은 네 것'이라고 떠들어댔지!";
			link.l1.go = "Slaveshore_6";
		break;
			
		case "Slaveshore_6":
			dialog.text = "매복은 현지 당국이 조직한 것이 아니오, 그렇지 않았다면 내가 알았을 테니까... "+pchar.name+", 지금은 다툴 때가 아니오. 우리 둘 다 위험에 처했소; 내 예전 계약자 중 한 명이 우리를 함정에 빠뜨렸소\n내가 알아낸 바로는, 모든 증거 자료—서류 뭉치—가 우리 총독에게로 운반되고 있소. 그가 그것을 손에 넣는다면 우리는 끝장이오! 참고로, 그대가 가장 큰 피해를 입을 것이오.";
			link.l1 = "이제야 그 망할 선장이 무슨 뜻으로 말했는지 알겠군!";
			link.l1.go = "Slaveshore_7";
		break;
			
		case "Slaveshore_7": //выбор острова, куда бригантина пойдёт
			switch (sti(NPChar.nation))
            {
                case HOLLAND :
					pchar.questTemp.Slavetraderbrig.Island = "Curacao";
                break;
                case FRANCE :
					pchar.questTemp.Slavetraderbrig.Island = "Nevis";
                break;
                case SPAIN :
					pchar.questTemp.Slavetraderbrig.Island = "Cuba2";  
                break;
                case ENGLAND :
					pchar.questTemp.Slavetraderbrig.Island = "Jamaica";     
                break;
			}
			pchar.questTemp.Slavetraderbrig.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));//имя бригантины
			pchar.questTemp.Slavetrader.Nation = NPChar.nation;
			dialog.text = "잘 들으시오. 아직 기회가 있소. 그 소포는 브리건틴 '"+pchar.questTemp.Slavetraderbrig.ShipName+". 그것만은 내가 확실히 알고 있소. 서류들은 총독 관저로 전달되고 있소, "+XI_ConvertString(pchar.questTemp.Slavetraderbrig.Island)+". 그 배를 가로막아 승선한 뒤, 그 죄를 입증할 증거를 찾아야 하오.";
			link.l1 = "여기서는 선택의 여지가 별로 없군. 나와 자네 모두를 위해 기도하게. 내가 그걸 잡을 수 있기를 바라게나. 내가 돌아오면 이 모든 것에 대해 다시 이야기하세. 그냥 넘길 생각은 없으니 그렇게 알게.";
			link.l1.go = "Slaveshore_8";
			AddQuestRecord("Slavetrader", "14");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetraderbrig.ShipName);
			AddQuestUserData("Slavetrader", "sIsland", XI_ConvertString(GetIslandByArealName(pchar.questTemp.Slavetraderbrig.Island)));
			pchar.quest.Slavetrader_BrigAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_BrigAttack.win_condition.l1.location = pchar.questTemp.Slavetraderbrig.Island;//отправляем в локацию
            pchar.quest.Slavetrader_BrigAttack.function = "Slavetrader_CreateBrig";//создание бригантины
			SetFunctionTimerCondition("Slavetrader_BrigOver", 0, 0, 15, false);	//таймер
			pchar.questTemp.Slavetrader = "wait1";	//это нода ожидания, пустая
		break;
		
		case "Slaveshore_8":
			dialog.text = "이 소포를 받는 것이 네 최우선 임무다! 네가 이걸 나에게 가져다주기 전까진 마음이 놓이지 않아... 젠장..."+pchar.name+", 여기 문제가 생긴 것 같군...";
			link.l1 = "무슨 일이오?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Slavetrader_enterSoldiers");
			break;
			
		case "Brig_lose":
			dialog.text = "젠장... 나는 너를 믿고 있었는데. "+pchar.name+". 좋아. 하지만 우리 거래는 여기서 끝이야. 만약 내가 조사관을 매수하지 못하면 도망쳐야 할 거다. 그리고 너도 여기 머무르지 않는 게 좋겠어 – 언제든 군인들이 올 수 있으니. 잘 가라.";
			link.l1 = "안녕히 가십시오, "+npchar.name+".";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Letter_lose":
			dialog.text = "그들이 거기 있었소. 이제 우리 둘이 거래를 할 수 없겠군, 더 이상 안전하지 않으니. 안녕히 가시오.";
			link.l1 = "안녕히 가십시오, "+npchar.name+".";
			link.l1.go = "exit";
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Brig_win":
			dialog.text = "훌륭합니다! 나는 당신을 한 번도 의심하지 않았소, "+pchar.name+". 그 서류를 주십시오, 너무 긴장되어 있소.";
			link.l1 = "가져가시오.";
			link.l1.go = "Brig_win_1";
		break;
			
		case "Brig_win_1":
			RemoveItems(PChar, "letter_1", 1);
			dialog.text = "좋아... 이제 나는 안전하오. 총독께서는 아무것도 모르실 것이고, 현지 관리들과의 문제도 이미 모두 해결했소. 하지만 비용이 많이 들었음을 말씀드리오.";
			link.l1 = "좋은 말이긴 한데, 당신의 경솔한 행동 때문에 내가 겪은 고생에 대해 보상해줘야 한다고 생각하지 않소?";
			link.l1.go = "Brig_win_2";
		break;
			
		case "Brig_win_2":
			dialog.text = "물론이오, "+pchar.name+". 더 나아가, 나는 당신에게 큰 빚을 졌소. 그리고 앞으로도 우리의 거래가 계속되길 진심으로 바라오. 하지만 내 입장도 이해해 주길 바라오 – 나는 막대한 돈을 썼소 – 총독과 사령관의 충성심은 결코 싸지 않소. 게다가 내 은행에서 순찰대 전원이 살해된 사건도 처리해야 했으니...";
			link.l1 = "내 비용을 보상해 주지 않겠다는 말이오?!";
			link.l1.go = "Brig_win_3";
		break;
			
		case "Brig_win_3":
			dialog.text = "그렇게 심하게 굴지 마시오, "+pchar.name+". 지금 정말 돈이 궁해서, 다른 방식의 대가를 제안하겠소.";
			link.l1 = "그럼, 말씀을 듣고 있겠습니다.";
			link.l1.go = "Brig_win_4";
		break;
			
		case "Brig_win_4":
			dialog.text = "나와 동료는 1년 전 메인 남쪽 해안 근처에서 폭풍을 만났소. 우리 배들은 보카 데 라 세르피엔타 해안의 암초에 떠밀려 올라갔고, 곧 침몰했지만 우리는 화물을 간신히 해안으로 끌어냈지. 보석과 보석류로 가득 찬 궤짝들이었소. 그 만은 꽤 아늑해 보여서 우리는 아무런 문제 없이 보물을 숨겼지\n하지만 다음 날 아침, 폭풍이 가시자마자 인디언들에게 습격을 당했소. 그때 대부분의 생존자들이 죽었고, 내 동료도 그 중 하나였지. 몇몇 선원들과 나는 간신히 장정선으로 도망쳤소\n우리는 무사히 쿠마나에 도착했지만, 나는 감히 다시 보물을 찾으러 갈 수 없었소. 분명 그곳 야만인들이 아직도 해안을 지키고 있을 것이고, 내 궤짝들도 함께 있을 거요. 하지만 자네라면 그 붉은 피부 놈들을 상대할 수 있을 거라 믿소\n그곳에서 찾게 될 보석류는 자네의 모든 비용을 충당하고도 남을 것이오, 남부 메인으로의 탐험 경비까지도 말이오.";
			link.l1 = "흠... 좋소. 그럼 나는 쿠마나로 가겠소\n";
			link.l1.go = "Brig_win_5";
		break;
			
		case "Brig_win_5":
			dialog.text = "안심하셔도 됩니다, "+pchar.name+", 내가 한 말이 모두 진실임을 명심하시오. 한 달 후에 다시 뵙기를 기대하겠소. 이미 다른 거래를 염두에 두고 있으며, 내 어려운 사업을 어떻게 도울 수 있을지 생각하고 있소. 안녕히 가시오.";
			link.l1 = "또 봅시다, "+npchar.name+".";
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_3");
			pchar.questTemp.Slavetrader = "wait_3";
			Pchar.quest.Slavetrader_Bonanza.win_condition.l1 = "location";
            Pchar.quest.Slavetrader_Bonanza.win_condition.l1.location = "Shore18";
            Pchar.quest.Slavetrader_Bonanza.function = "Slavetrader_Bonanza";
		break;
			
		case "SlaveGalleon":
			dialog.text = "그리고 여기 계시는군요, "+pchar.name+". 좋군요, 언제나처럼 딱 맞춰 오셨습니다. 다음 임무를 드리기 전에 카리브 노예 시장에 대해 더 많은 정보를 알려드리고 싶습니다. '레파르티미엔토'라는 단어가 무슨 뜻인지 아십니까?";
			link.l1 = "음, 아니오, "+npchar.name+", 아니오. 하지만 누군가에게서 무언가를 빼앗는 일과 관련된 것 같군요. 맞습니까?";
			link.l1.go = "SlaveGalleon_1";
		break;
			
		case "SlaveGalleon_end":
			dialog.text = "놀랍군. 내가 뭘 해주길 바랐지? 가버려!";
			link.l1 = "불법 사업은 내 양심에 너무 큰 짐이오. 특히 노예 무역은 더더욱 그렇소.";
			link.l1.go = "node_hanter_1";
		break;
			
		case "SlaveGalleon_1":
			dialog.text = "거의 다 됐어,"+pchar.name+". 누군가의 자유를 빼앗는 것이지. 레파르티미엔토는 현지 인디언들을 교묘하게, 그리고 합법적으로 노예로 만드는 방법이네. 말하자면 그렇지. 스페인 당국이 본토 원주민들에게 사용하는 제도라오. 더 알고 싶은가?";
			link.l1 = "왜 안 되지?";
			link.l1.go = "SlaveGalleon_2";
		break;
			
		case "SlaveGalleon_2":
			dialog.text = "스페인 왕실의 대리인들이 인디언 정착지를 방문합니다. 냉소적인 기만과 노골적인 협박을 이용해 인디언들에게 썩은 고기나 낡은 면도칼 같은 온갖 잡동사니를 터무니없는 가격에 강제로 사게 하지요. 그것도 외상으로요\n얼마 후, 예를 들어 1년쯤 지나면, 그 대리인들이 다시 와서 대금을 요구합니다. 인디언들이 돈을 갚지 못하면—대부분 그런 일이 벌어지지요—스페인인들은 일할 수 있는 남자 몇 명을 데려갑니다. 명목상으로는 잠시 데려가서 ‘땅을 경작하는 법을 가르쳐주겠다’는 것이지요\n알다시피, 그들은 결코 정착지로 돌아오지 않습니다. 그렇게 우리의 순진한 붉은 피부 친구들은 설탕 플랜테이션이나 레드우드 공장으로 끌려가게 되는 것입니다.";
			link.l1 = "젠장... 정말로... 인디언들은 그런 일에 어떻게 대처하지? 스페인 놈들이 그들을 노예로 삼을 때 저항이라도 하나? 아니면 그냥 무슨 일이 벌어지는지조차 모르는 건가?";
			link.l1.go = "SlaveGalleon_3";
		break;
			
		case "SlaveGalleon_3":
			dialog.text = "아마 그들은 항상 이런 일이 닥칠 걸 알고 있겠지. 하지만 스페인 놈들이 추장의 지문이 찍힌 문서를 내밀 때, 대놓고 맞서는 자는 극히 드물다네. 물론 이런 수법은 아라와크족이나 미스키토족처럼 온순한 부족에게나 통하지. 전투적인 이차족이나 아카와이족에게는 이런 꼼수가 안 통하지\n자, 이제 그대 임무에 대해 이야기해 보세.";
			link.l1 = "벌써 동전 냄새가 진하게 나는군! 듣고 있지, "+npchar.name+".";
			link.l1.go = "SlaveGalleon_4";
		break;
			
		case "SlaveGalleon_4":
			Slavetrader_GetHispanShore();
			sTemp = pchar.questTemp.SlavetraderAreal.add; 
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(SPAIN);
			dialog.text = "곧 카라카스에서 대형 갤리온이 출항할 것이오. 이름은 "+pchar.questTemp.Slavetrader.ShipName+". 오리노코에서 온 인디언 노예가 약 3,000명이나 실려 있소. 모두 레파르티미엔토 정책에 따라 잡혀온 자들이오. 그 갤리온은 산티아고로 향하고 있소; 쿠바의 사탕수수 농장에는 많은 일꾼이 필요하오. 반드시 그 갤리온과 화물을 포획해야 하오. 내라면 최소한 두 척의 배를 데리고 가겠소; 그 갤리온이 동종 선박 중 최고라 하더이다. 보수는 변함없소 - 머리 하나당 200페소요. ";
			link.l1 = "헤헤! 괜찮게 들리는군. 나도 동의하네.";
			link.l1.go = "SlaveGalleon_5";
			link.l2 = "그대의 그 레파르티미엔토가 마음에 들지 않는다는 것 알지 않소. 너무 냉소적이오. 나는 이 일을 하지 않을 것이오.";
			link.l2.go = "SlaveGalleon_end";
		break;
			
		case "SlaveGalleon_5":
			sTemp = pchar.questTemp.SlavetraderAreal.add; 
			dialog.text = "그럼 행운을 빕니다. 이 갤리온의 선장은 전쟁에 능하고 경험 많은 항해사임을 알아두십시오. 쉽지 않은 싸움이 될 테니, 각오하시길. 시간을 낭비하지 마십시오, 그가 도착하려면 15일에서 20일 정도 걸릴 것입니다\n "+sTemp+" 산티아고. 놓치지 않도록 하시오, 이 갤리온은 정말 눈에 띄니 말이오\n아! 거의 잊을 뻔했군! 배 안에는 인디언 장신구가 아주 많소, 원주민들이 종종 그들의 신앙 물품이나 수공예품으로 빚을 갚거든. 특별한 물건을 발견하면 뭐든 가져오시오, 가치 있는 물건마다 후하게 보상하겠소.";
			link.l1 = "알겠습니다.";
			link.l1.go = "exit";
			SlavetraderGalleonInWorld();
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("Slavetrader_SlaveGalleonOver", 0, 0, 20, false);
			pchar.questTemp.Slavetrader = "wait1";
			AddQuestRecord("Slavetrader", "18");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
			AddQuestUserData("Slavetrader", "sAreal", sTemp);
		break;
			
		case "Lostgalleon":
			dialog.text = "음, "+pchar.name+", 이것이 내 마지막 희망이었소... 그래서 이 일을 그대에게 맡긴 것이오. 그대 말고는 할 수 있는 이가 없었으니... 그런데 이제 보니 그대도 해내지 못하는구려. 이제 작별 인사를 해야겠소. 마지막 실패와 온갖 소문들로 인해 내 모든 고객들이 떠나버렸소. 나는 거의 파산 지경이라, 아마 이 도시를 떠나야 할지도 모르오. 그대를 탓하지는 않소 - 이 일은 너무 어려웠으니. 에휴... 안녕히 가시오,\n"+pchar.name+".";
			link.l1 = "정말 죄송합니다, "+npchar.name+", 그건 너무 지나쳤군요. 진심으로 사과드립니다. 아마 모든 것이 곧 진정될 것입니다. 안녕히 가십시오.";
			link.l1.go = "exit";
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Wingalleon":
			pchar.questTemp.Slavetrader.Nation = npchar.nation;
			amount = 3000 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*200;
			if(amount < 1) 
			{
				dialog.text = "휴, 이제 좀 나아졌어... 너를 믿길 잘했군... 이 비꼼은 어디서 나온 거지? 무슨 문제라도 있어?";
				link.l1 = "나리, 그것은 갤리온이 아니었습니다... 아니, 아주 큰 갤리온도 아니었지요... 제기랄! 그것은 전열함이었습니다! 그런데 저에게 미리 경고도 안 해주셨군요! 그래도 제가 승선하는 데는 성공했습니다. 저는 "+sTemp+" 노예들이 준비되어 있으니 당신에게 넘기겠소. 우리 계약에 따라, 당신은 나에게 빚이 있소 - "+FindRussianMoneyString(iSlaveMoney)+". 그대의 잘못된 정보에 대해 보상을 받으면 좋겠군.";
				link.l1.go = "Wingalleon_1";
			}
			else
			{
			dialog.text = "갤리온을 찾았나? 노예들은 어찌 되었지? 삼천 명이나 있어야 하오, 그보다 적어서는 안 되오! 젠장, 모두 쥐새끼에 배신자뿐이군! 자네에게서만은 이런 일을 기대하지 않았는데... 자네가 내 마지막 희망이었소\n좋다... 맹세하건대, 남은 동전 한 푼까지 써서 자네를 파멸시키고, 죽이고 말겠소! 함대 전체가 "+NationNameGenitive(sti(npchar.nation))+" 널 사냥하러 올 거야! 여기서 나가!";
				link.l1 = "음...";
				link.l1.go = "Wingalleon_goaway";
			}
		break;
			
		case "Wingalleon_goaway":
			AddQuestRecord("Slavetrader", "9");
			CloseQuestHeader("Slavetrader");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 70);
			pchar.questTemp.Slavetrader = "End_quest";
			DialogExit();
		break;
			
		case "Wingalleon_1":
			dialog.text = "정말이요! 맹세코, 전혀 몰랐소. 원래는 무거운 갤리온이 출항할 예정이었지, 저런 전열함이 아니라! 마지막 순간에 계획을 바꾼 것 같군... 그래도, 자네는 해냈구려!\n자네가 말한 돈과 경비 보상에 대해 전적으로 동의하오. 하지만 문제는, 지금 내게 그런 거금이 없다는 것이오. 내 최근 곤경에 대해 자네도 알고 있지 않소... 하지만 너무 화내지 말게, "+pchar.name+", 제발요. 당신이 화물을 넘기면 내가 팔겠소, 내 고객이 이미 기다리고 있소\n다섯 날이면 전액을 마련하겠으니, 당신이 받아야 할 몫을 꼭 드리겠소. 나를 믿으시오. 자, 지금 내가 가진 현금은 모두 여기 있소.";
			link.l1 = "흠... 지금 돈을 받을 줄 알았는데. 내가 어떤 고생을 했는지 알았으면 좋겠군! 뭐, 됐다... 동정해 주지. 하지만 명심해라, 날 속이려 들면 유럽까지라도 찾아낼 테니!";
			link.l1.go = "Wingalleon_yes";
			link.l2 = "있지, "+npchar.name+", 엿이나 먹어! 그건 거래가 아니었어. 내가 어떤 싸움을 치렀는지 너는 상상도 못 할 거야. 노예들은 전부 내가 가져가서 네 중개 없이 팔 거다.";
			link.l2.go = "Wingalleon_no";
		break;
			
		case "Wingalleon_no":
			dialog.text = "그래, 이제야 말이 통하는군! 아무것도 모르는 "+npchar.name+" 나는 단순히 젖을 짜는 소에 불과했지, 너는 조금만 지체해도 나를 배신하고 혼자서 작전을 시작하려 들었어. 내가 너에게 이 일을 맡기고 전리품 정보를 흘려준 사람이라는 사실을 잊은 모양이군\n좋다... 맹세코, 내게 남은 마지막 동전까지 써서 너를 파멸시키고, 죽이고 말겠다! 전 함대가 "+NationNameGenitive(sti(npchar.nation))+" 내가 널 쫓아다닐 거다! 내 눈앞에서 꺼져라!";
			link.l1 = "빈 돈궤로 나를 겁주려 들지 마라. 네 함대를 전부 침몰시켜서 게밥으로 만들어 주지.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "9");
			CloseQuestHeader("Slavetrader");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 70);
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Wingalleon_yes":
			dialog.text = "이해해 주셔서 감사합니다, "+pchar.name+". 모든 것이 잘 될 것을 약속하오, 위협하실 필요 없소\n이것을 선금으로 받으시오. 상자 열다섯 개요. 그중 다섯 개는 정신적 피해에 대한 보상으로 드리겠소. 나머지를 받으려면 오일 후에 다시 오시오.\n배에서 발견한 인디언 물품이 있다면 꼭 가져오시오... 물론, 정말로 찾았다면 말이오. 하지만 그 물건들에 대해서는 드릴 돈이 없소.";
			link.l1 = "오일 후에,"+npchar.name+". 오일 뒤에...";
			link.l1.go = "Wingalleon_yes_1";
		break;
			
		case "Wingalleon_yes_1":
			TakeNItems(pchar, "chest", 15);
			Log_Info("You've received credit chests");
			PlaySound("interface\important_item.wav");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_4");
			pchar.questTemp.Slavetrader = "wait_4";
			AddQuestRecord("Slavetrader", "20");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			pchar.questTemp.Slavetrader.iSlaveMoney = makeint(sTemp)*200-120000;
			RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
			DialogExit();
		break;
	
		case "FindRat":
			dialog.text = "약속드린 대로, "+pchar.name+", 이제 당신에게 지불할 준비가 되었소. 노예들은 모두 팔렸고, 손님도 만족했으며, 우리도 그렇소. 선지급금을 제하고, 당신의 보상금은"+FindRussianMoneyString(sti(pchar.questTemp.Slavetrader.iSlaveMoney))+". 자, 돈을 가져가십시오.";
			link.l1 = "훌륭하군, "+npchar.name+"... 약속을 지키는 사람과 거래하는 건 좋은 일이오...";
			link.l1.go = "FindRat_1";
		break;
			
		case "FindRat_1":
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.Slavetrader.iSlaveMoney));
			dialog.text = "언제나 내 말을 믿어도 된다, "+pchar.name+". 나는 당신이 나를 의심할 만한 이유를 준 적이 없습니다. 동업자는 서로에게 정직해야 하오, 그것이 사업의 핵심이지요\n이제 인디언 유물에 대해 이야기해 봅시다. 내가 수집가라는 걸 생각해서, 가진 것을 보여주시오. 기다리게 하지 마시오.";
			link.l1 = "흠... 한번 보시오.";
			link.l1.go = "FindRat_2";
		break;
			
		case "FindRat_2":
			if (CheckCharacterItem(pchar, "talisman16"))
			{
				dialog.text = "예! 훌륭하군! 황금 의식용 단검이라니! 정말 희귀한 물건이오. 내 수집품에 꼭 갖고 싶던 거였소. 3만을 드리겠소, 아니면 '에에카틀'의 부적과 교환해도 되오. 어차피 그건 두 개나 가지고 있거든.";
				link.l1 = "돈을 받겠소.";
				link.l1.go = "BG_money";
				link.l2 = "나는 '에에카틀'의 부적과 맞바꾸겠소.";
				link.l2.go = "BG_change";
				link.l3 = "이 칼은 내가 가지고 있는 게 좋겠군.";
				link.l3.go = "BG_no";
			}
			else
			{
				dialog.text = "자, 어디 보자... 유감이지만, 당신에게서 흥미로운 것은 아무것도 없군.";
				link.l1 = "원하시는 대로 하십시오.";
				link.l1.go = "BG_PF";
			}
		break;
			
		case "BG_money":
			dialog.text = "훌륭하군. 3만을 가져가시오, 그리고 이 인디언 칼은 이제 내 것이오.";
			link.l1 = "좋소. 그리고 그게 전부 궁금하신 겁니까...";
			link.l1.go = "BG_PF";
			AddMoneyToCharacter(pchar, 30000);
			Log_Info("You've given a golden knife");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "talisman16", 1);
		break;
			
		case "BG_change":
			dialog.text = "훌륭하군! 여기 당신의 부적이오, 그리고 이 인디언 칼은 이제 내 것이오.";
			link.l1 = "좋소. 그리고 그게 전부 관심 있는 것입니까...";
			link.l1.go = "BG_PF";
			Log_Info("You've given a golden knife");
			Log_Info("You've received an amulet of 'Ehecatl'");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "talisman16", 1);
			TakeNItems(pchar, "obereg_9", 1);
		break;
			
		case "BG_no":
			dialog.text = "뭐, 알겠소. 그래도 정말 아쉽군...";
			link.l1 = "좋소. 그리고 그것만이 자네가 관심 있는 전부인가...";
			link.l1.go = "BG_PF";
		break;
			
		case "BG_PF":
			dialog.text = "잠깐! 다시 한 번 살펴보게...";
			link.l1 = "물론이오. 와서 직접 보고 원하는 것을 고르시오.";
			link.l1.go = "PF_check";
		break;
			
		case "PF_check":
			if (CheckCharacterItem(pchar, "mineral31"))
			{
				dialog.text = "이거군! 처음엔 나도 눈치채지 못했소. 나는 이 구리 고리가 달린 뼈에 관심이 있소. 참으로 흥미로운 물건이오, 정말로... 2만 페소를 지불하거나 '치마루타' 부적과 교환해 드릴 수 있소.";
				link.l1 = "나는 돈을 받겠소.";
				link.l1.go = "PF_money";
				link.l2 = "대신 'Cimaruta' 부적을 받겠소.";
				link.l2.go = "PF_change";
				link.l3 = "이 유물은 내가 가지고 있겠소.";
			link.l3.go = "PF_no";
			}
			else
			{
				dialog.text = "아니오... 여기에는 더 이상 흥미로운 것이 없소.";
				link.l1 = "뭐든지 상관없어!";
				link.l1.go = "FindRat_3";
			}
		break;
			
		case "PF_money":
			dialog.text = "훌륭하군! 여기 2만 페소를 주겠소, 그리고 이 뼈는 이제 내 것이오.";
			link.l1 = "좋군. 이번 거래, 마음에 들어.";
			link.l1.go = "FindRat_3";
			AddMoneyToCharacter(pchar, 20000);
			Log_Info("You've given a magic bone");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "mineral31", 1);
		break;
			
		case "PF_change":
			dialog.text = "훌륭합니다! 여기 당신의 부적이요, 이제 이 뼈는 내 것이오.";
			link.l1 = "좋군. 이번 거래, 마음에 들어.";
			link.l1.go = "FindRat_3";
			Log_Info("You've given a magic bone");
			Log_Info("I've received an amulet of 'Cimaruta'");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "mineral31", 1);
			TakeNItems(pchar, "amulet_11", 1);
		break;
			
		case "PF_no":
			dialog.text = "뭐, 알겠소. 그래도 참 아쉽구려...";
			link.l1 = "그 뼈는 내가 꼭 필요해서, 정말 미안하네.";
			link.l1.go = "FindRat_3";
		break;
			
		case "FindRat_3":
			dialog.text = "음... 갤리온, 아니, 전열함에 승선해 주셔서 저를 구해 주셨습니다. 우리 동업 관계에 진심으로 감사드립니다, "+pchar.name+". 그대는 내 최고의 대리인이오.";
			link.l1 = "과찬이십니다. 제 성과를 너무 높이 평가하시는군요...";
			link.l1.go = "FindRat_4";
		break;
			
		case "FindRat_4":
			dialog.text = "나는 전적으로 진지하오. 그리고 그대의 비범한 능력과 내가 그대를 신뢰하기에 또 다른 임무를 맡아 주길 부탁하겠소.";
			link.l1 = "헤! 놀랍군! 듣고 있소. 노예를 태운 다른 갈레온은 어디 있소?";
			link.l1.go = "FindRat_5";
		break;
			
		case "FindRat_5":
			dialog.text = "이번에는 노예 문제가 아니오. 놀랐소? 임무에 대한 보수는 충분히 드리겠소... 아주 충분히.";
			link.l1 = "바로 본론으로 들어가시지요.";
			link.l1.go = "FindRat_6";
		break;
			
		case "FindRat_6":
			dialog.text = "이 일은 당신도 연관된 최근 사건과 관련되어 있소... 아시다시피, 나는 다소 불법적인 사업, 즉 노예 무역에 관여하고 있소. 그리고 당신 같은 사략선장들을 여러 임무에 고용한다는 것도 알고 있을 것이오\n얼마 전 내 부하 중 한 명이 알 수 없는 이유로 나를 배신했소. 그는 증거를 모아 당국에 보고했지. 그 결과를 당신도 직접 목격했을 것이오. 병사들이 탄 배가 이곳에 도착했으니... 그 이후는 이미 알고 있겠지\n이 사태를 수습하는 데 꽤 많은 노력이 들었소. 이해하겠지만, 이런 배신을 그냥 넘어갈 수는 없소. 게다가 그 쥐새끼가 아직 살아 있다는 사실을 알면서는 마음 편히 살 수도, 일할 수도 없지. 현상금 사냥꾼들을 보냈으나 아직 아무런 성과가 없소\n이 문제를 직접 해결해 주길 바라오. 게다가 그의 행동은 당신에게도 영향을 주었으니 말이오.";
			link.l1 = "흠... 그 자식은 돛대에 매달아야 마땅하지! 그놈에 대해 더 말해 봐, 그리고 물론 내 보수도 말이야.";
			link.l1.go = "FindRat_7";
		break;
			
		case "FindRat_7":
			dialog.text = "그 점은 걱정하지 마시오. 그 자를 제거해 준다면 충분한 보상을 하겠소. 돈만이 아니라 내 소장품 중 가장 귀한 물건들도 아끼지 않겠소. 이제 그 남자에 대해 이야기해봅시다. 그의 이름은 프랑수아 곤티에르요\n내가 그를 쫓고 있다는 걸 알고 있어서, 그는 자신의 흔적을 감추려고 프리깃함을 팔아버렸소. 내 동료들이 파나마에서 그를 목격했다고 하더군요. 그곳에서 수색을 시작하는 것이 좋을 듯하오.";
			link.l1 = "그럼, 이제 가보겠소.";
			link.l1.go = "FindRat_8";
		break;
			
		case "FindRat_8":
			dialog.text = "그럼 행운을 빕니다. 이 곤티에르는 매우 노련한 선원이며, 무모한 악당들로 이루어진 선원을 거느리고 있다는 사실을 알아두십시오. 그는 잃을 것이 없으니, 필사적으로 싸울 것입니다.";
			link.l1 = "나는 그 같은 자를 두려워하지 않소. 하지만 그대 말은 새겨듣겠소. 작별이오. 지옥이라도 반드시 그를 잡아낼 테니 안심하시오.";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(SPAIN);
			AddQuestRecord("Slavetrader", "21");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			pchar.questTemp.Slavetrader = "FindRatPanama";
		break;
			
		case "Wincorvette":
			dialog.text = "훌륭하군! 이제 그는 해파리에게 보고서를 쓸 수 있겠지. 감히 나를 거스르는 자는 없어. 고맙소, "+pchar.name+", 당신은 없어서는 안 될 분이오.";
			link.l1 = "감사합니다, "+npchar.name+", 제 행동에 대해 그렇게 긍정적으로 평가해 주셔서 감사합니다. 제 보수는 어떻게 됩니까?";
			link.l1.go = "Wincorvette_1";
		break;
			
		case "Wincorvette_1":
			dialog.text = "물론이지. 그렇게 어려운 일이라면 정당한 값을 치르겠소. 우선, 이 훌륭한 망원경을 드리겠소.";
			link.l1 = "이런 젠장, 대단한 선물이군!";
			link.l1.go = "Wincorvette_2";
		break;
			
		case "Wincorvette_2":
			dialog.text = "게다가, 여기 기본 보수로 10만 페소와, 개인 경비 보상으로 5만 페소를 드리오.";
			link.l1 = "감사합니다, "+npchar.name+". 다시 한 번 말씀드리지만, 당신과 거래하게 되어 정말 기쁩니다.";
			link.l1.go = "Wincorvette_3";
			Log_Info("You've received an excellent spyglass");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "spyglass4", 1);
		break;
			
		case "Wincorvette_3":
			dialog.text = "한 달 뒤에 늘 그렇듯이 당신을 기다리겠소. 이번 일은 상당히 큰 건이니, 제대로 무장한 함대를 준비해야 하오. 그 점을 이해하고 철저히 대비해 주기를 바라오. 내 계획이 성공하면 우리 둘 다 부자가 될 것이오.";
			link.l1 = "좋습니다,"+npchar.name+". 준비가 되면 다시 오겠소.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 150000);
			AddQuestRecord("Slavetrader", "21_13");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_5");
			pchar.questTemp.Slavetrader = "wait_5";
		break;
			
		case "Lostcorvette":
			dialog.text = "안타깝군, 정말 유감이야... 뭐, 너무 속상해하지 마. 그 자식한테 속은 게 너만은 아니니까. 언젠가는 내가 반드시 그 놈을 잡을 거야\n그리고 너는 한 달 후에 나를 다시 찾아오도록 해. 이번 일은 규모가 크니, 장비와 무장이 잘 갖춰진 함대를 모아 오게. 제발, 진지하게 받아들이고 최선을 다해 준비해 줘. 내 계획이 성공하면 우리 둘 다 큰돈을 벌 수 있을 거야.";
			link.l1 = "좋소, "+npchar.name+". 준비가 되면 다시 오겠소.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_14");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_5");
			pchar.questTemp.Slavetrader = "wait_5";
		break;
		
		case "Havana_fort":
			dialog.text = "딱 맞춰 오셨군, "+pchar.name+"! 이제 막 걱정하려던 참이었소, 사람을 보내 자네를 찾으려 했었지\n시작하세! 이번 임무는 정말 크고 위험하오, 하지만 보상도 그에 걸맞소. 임무를 완수하면 백만 페소가 넘는 돈을 받게 될 것이오.";
			link.l1 = "이제야 말이 통하는군! 듣고 있소, "+npchar.name+".";
			link.l1.go = "Havana_fort_1";
		break;
		
		case "Havana_fort_1":
			dialog.text = "노예로 잡힌 인디언들은 본토 전역에서 작은 무리로 아바나로 이송되고 있었고, 몇몇 갤리온도 아프리카에서 도착해 하역되었습니다.\n지금쯤이면 아바나 요새의 높은 성벽 뒤에는 거의 오천 명에 달하는 노예들이 있습니다.";
			link.l1 = "왠지 이번 거래는 아바나를 습격하는 것과 관련된 것 같군.";
			link.l1.go = "Havana_fort_2";
		break;
		
		case "Havana_fort_2":
			dialog.text = "감이 제대로 왔군, "+pchar.name+". 바로 그것을 당신에게 부탁하고 싶소. 오직 당신만이 할 수 있소. 내 다른 어떤 대리인도 이 일을 해낼 수 있을지 의심스럽소\n당신이 참여할 것이라 믿어도 되겠소?";
			link.l1 = "솔직히 말해서, "+npchar.name+", 지금 좀 어리둥절하군요. 당신의 사업이 이렇게나 대규모일 줄은 전혀 몰랐습니다. 물론, 저도 참여하겠습니다. "+RandSwear()+"";
			link.l1.go = "Havana_fort_3";
			link.l2 = "있잖아, "+npchar.name+", 이건 너무 지나치군. 네가 주는 놀라움도 이제 지긋지긋하다. 다음번엔 네 탐욕 때문에 내가 스페인에 선전포고라도 하게 생겼으니, 그땐 나 혼자서 싸워야 할 거다. 정말로 그 노예들이 필요하다면, 네가 직접 아바나를 공격해라.";
			link.l2.go = "Havana_fort_not";
		break;
		
		case "Havana_fort_not":
			dialog.text = "너한테서 이런 반응이 나올 줄은 몰랐는데... 젠장, 내 고객한테 뭐라고 설명해야 하지? 좋아. 네 선택이니 나는 새로운 파트너를 찾아야겠군. 안녕히 가시오, "+pchar.name+". 그리고 앞으로는 당신의 서비스를 이용하지 않을 것이오. 당신이 일곱 대에 걸쳐 후손들을 부유하게 만들 수 있었던 거래를 스스로 놓쳤다는 것을 기억하시오.";
			link.l1 = "세상 모든 돈을 가질 수는 없소, 그리고 자네는 감당할 수 없는 일을 벌였구려. 작별이오, "+npchar.name+".";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "8");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
		
		case "Havana_fort_3":
			dialog.text = "동의할 줄 알았소. 이제 자세한 내용을 들으시오. 아바나 요새는 예전부터 공략하기 어려운 곳이었지만, 지금은 더더욱 어려워졌소.\n쿠바 해안에는 전열함 두 척이 경비 중이니, 요새를 습격하기 전에 먼저 그 배들을 처리해야 하오...";
			link.l1 = "알겠소. 라인쉽과 싸우는 게 이번이 처음은 아니니, 하하. 시간이 얼마나 남았소?";
			link.l1.go = "Havana_fort_4";
		break;
		
		case "Havana_fort_4":
			dialog.text = "별로 시간이 없소. 길어야 3주일, 그 후에는 노예들이 쿠바의 스페인 전초기지로 옮겨질 것이오. 서둘러야 하오. ";
			link.l1 = "그럼 시간 낭비하지 맙시다. 나는 이만 가보겠소!";
			link.l1.go = "Havana_fort_5";
		break;
		
		case "Havana_fort_5":
			dialog.text = "잠깐만!"+pchar.name+", 당신과 나는 지금까지 오해나 불화가 없었소. 그럼에도 불구하고, 여기서 무슨 일이 일어나고 있는지 알아두길 바라오. 나는 당신을 믿고 있고, 의뢰인은 나를 믿고 있소\n우리는 이번 작전에 막대한 노력과 자금을 투자했소. 노예 한 명 한 명, 전부 오천 명을 반드시 내게 인도해야 하오\n그렇지 않으면, 우리는 당신에게 매우 강경한 조치를 취할 수밖에 없소. 기분 나쁘게 듣지 마시오, 이것은 단지 경고일 뿐이오. ";
			link.l1 = "걱정하지 마시오, "+npchar.name+", 저는 장사라는 것이 어떤 것인지 잘 압니다. 그러니 제가 그것들을 전달하면 반드시 제게 대가를 지불해야 한다는 점을 기억하십시오. 안녕히 가십시오.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "24");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			pchar.quest.Slavetrader_HavanaAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_HavanaAttack.win_condition.l1.location = "Cuba2";//отправляем в локацию
            pchar.quest.Slavetrader_HavanaAttack.function = "Slavetrader_CreateLineShips";//создание линейных кораблей
			SetFunctionTimerCondition("Slavetrader_HavanaOver", 0, 0, 20, false);	//таймер
			characters[GetCharacterIndex("Havana_Mayor")].dialog.captureNode = "Slavetrader_HavanaAttack"; //капитулянтская нода мэра
			pchar.questTemp.Slavetrader = "wait1";
		break;
		
		case "Win_Havana_Fort":
			pchar.quest.Slavetrader_FiveTSlavesOver.over = "yes";
			amount = 5000 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			if (amount < 1)
			{
				dialog.text = "음... 그럼 당신의 승리에 대한 보상은 어떻게 되는 거요?";
				link.l1 = "나는 가지고 있다 "+sTemp+" 노예들.";
				link.l1.go = "Havana_Fort_yes";
				break;
			}
			if (amount < 4500 && amount >= 1)
			{
				dialog.text = "흠, 흠. 내가 한 말을 잊었나? 나에게 최소한 오천 명의 노예를 데려오기로 했었지, 그런데 네가 데려온 건 "+sTemp+". 그 이유가 무엇이오?";
				link.l1 = "흠... 그들 중 몇몇은 아바나에서 오는 길에 살아남지 못했소... 식량과 약품이 부족했지요.";
				link.l1.go = "Havana_Fort_no";
				break;
			}
			dialog.text = "흠, 흠... 나를 속이려는 건가? 내가 한 말을 잊었나? 내 노예들은 어디 있지, 묻겠네! 어디 있느냐?!";
			link.l1 = "흠... 그러니까...";
			link.l1.go = "Havana_Fort_no";
		break;
		
		case "Havana_Fort_no":
			dialog.text = "좋소. 설명 따위는 필요 없네. 우리 사이에 약조가 있었으니, 자네에게 일주일을 주겠네. 반드시 노예 오천 명 이상을 구해 오게. 그렇지 않으면 큰 곤란을 겪게 될 것이야.";
			link.l1 = "알겠어, 알겠어, 진정해. 내가 가져다줄게.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "29");
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("Slavetrader_HavanaSeekOver", 0, 0, 14, false);
			} 
			else SetFunctionTimerCondition("Slavetrader_HavanaSeekOver", 0, 0, 7, false);
			pchar.questTemp.Slavetrader = "Havana_seekslaves";
		break;
		
		case "Havana_Fort_yes":
			dialog.text = "훌륭하군! 언제나처럼 내 부탁을 완수했소. 매우 만족스럽구려.";
			link.l1 = "나도 그렇소... 하지만 화물 대금을 받게 된다면 더 기쁠 것이오.";
			link.l1.go = "Havana_Fort_yes_1";
		break;
		
		case "Havana_Fort_yesA":
		dialog.text = "그 점이 매우 기쁩니다. 늦기는 했지만, 제 부탁을 아주 훌륭하게 완수하셨군요.";
			link.l1 = "이제 화물 대금을 받고 싶소.";
			link.l1.go = "Havana_Fort_yes_1";
			pchar.quest.Slavetrader_HavanaSeekOver.over = "yes";
		break;
		
		case "Havana_Fort_yes_1":
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*200;
			dialog.text = "알겠소. 나는 노예들을 내 고객에게 팔 것이고, 그가 돈을 지불하면 자네도 돈을 받게 될 것이오. 지난번과 똑같이 말이오. 어디 보자, 자네가 여기 데려온 사람이... "+sTemp+" 노예들. 금액은 "+FindRussianMoneyString(iSlaveMoney)+". 일주일 후에 여기로 와서 대금을 받으시오.";
			link.l1 = "좋소, "+npchar.name+", 거래가 성사됐소. 일주일 후에 여기 오겠소. 하지만 매우 조심하시오...";
			link.l1.go = "Havana_Fort_yes_2";
			RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
		break;
		
		case "Havana_Fort_yes_2":
			dialog.text = ""+pchar.name+", 제발, 그러지 마시오. 우리는 동업자이니 서로 속이거나 의심할 여지는 없소. 내가 충분한 금화를 약속했고, 당신은 그것을 받았소. 흥미로운 일거리도 약속했고, 그것도 제공했소. 내 사업이 가장 어려웠던 시절에도 언제나 당신의 비용을 보상해 주었소. 내가 약속을 어긴 적이 있었소?";
			link.l1 = "흠... 아니오... 나는 그냥 돈만 받으면 돼, 그게 다야.";
			link.l1.go = "Havana_Fort_yes_3";
		break;
		
		case "Havana_Fort_yes_3":
			dialog.text = "이제 보게..."+pchar.name+", 당신은 내 최고의 거래처이니 앞으로도 계속 거래할 수 있기를 기대하오. ";
			link.l1 = "좋소, "+npchar.name+". 하지만 제 입장도 이해해 주셔야 합니다 - 백만 페소는 엄청난 금액입니다.";
			link.l1.go = "Havana_Fort_yes_4";
		break;
		
		case "Havana_Fort_yes_4":
			dialog.text = "당신 말씀은 잘 알겠습니다만, 먼저 노예들을 팔아야 하고, 그래야만 돈을 받을 수 있습니다.";
			link.l1 = "좋소. 이제 서로 이해한 것 같군.";
			link.l1.go = "Havana_Fort_yes_5";
		break;
		
		case "Havana_Fort_yes_5":
			dialog.text = "훌륭하군. 일주일 후에 보세. 이제 준비해서 내 거래처와 거래하러 가야겠군.";
			link.l1 = "그럼 더 이상 방해하지 않겠소. 일주일 후에 다시 뵙겠소,\n "+npchar.name+".";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader.Name = npchar.name;
			AddQuestRecord("Slavetrader", "32");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_6");
			SetFunctionTimerCondition("Slavetrader_UsurerEscape", 0, 0, 8, false);
			pchar.questTemp.Slavetrader = "wait_6";
			pchar.questTemp.Slavetrader.Cityname = npchar.city +"_town";
			LocatorReloadEnterDisable(npchar.city +"_town", "reload8_back", true);//чтобы не ходил неделю сюда вообще
		break;

		case "Usurer_Escape":
			dialog.text = "여기서 내가 뭘 하고 있냐고? 음... 이 은행이 내 은행이오. 이틀 전에 샀지. 당신이 내 첫 손님이니 아주 매력적인 신용 조건을 제안할 수 있소...";
			link.l1 = "빌어먹을 신용장 따위 필요 없어! 어디 있지 "+pchar.questTemp.Slavetrader.Name+"?";
			link.l1.go = "Usurer_Escape_1";
		break;

		case "Usurer_Escape_1":
			dialog.text = "진정하십시오! 그는 오래전에 도망쳤습니다.";
			link.l1 = "어떻게?";
			link.l1.go = "Usurer_Escape_2";
		break;
		
		case "Usurer_Escape_2":
			dialog.text = "모르셨나요? 그는 일주일 전에 사라졌습니다. 알고 보니 모든 고객의 투자금을 들고 도망쳤다더군요. 심지어 총독도 피해를 봤다고 합니다. 이 집만 남았길래 제가 식민지에서 샀습니다.";
			link.l1 = "사라졌다고? 어떻게?";
			link.l1.go = "Usurer_Escape_3";
		break;
		
		case "Usurer_Escape_3":
			dialog.text = "그가 우리 식민지에서 도망쳤다는 소문을 들었소... 당신에게도 빚을 졌겠지요? 많이?";
			link.l1 = "백만 이상이나! 그래도 저 쥐새끼는 반드시 잡고 말겠어! 어디로 간 거지? 그의 배 이름은?";
			link.l1.go = "Usurer_Escape_4";
		break;
		
		case "Usurer_Escape_4":
			dialog.text = "아무도 모릅니다. 정말입니다. 그는 그냥 사라졌습니다. 'Mauritius' 또는 'Maurdius'라는 배가 그날 떠났으니, 아마 그 배를 타고 도망쳤을지도 모릅니다.";
			link.l1 = "젠장! 내가 그 자식 믿었던 게 바보였지! 처음부터 배신자 냄새가 풀풀 났는데! 그래도 우리가 진짜 동료라고 착각하다니, 내가 바보였어! 언젠가 반드시 후회하게 만들어 주겠어... 좋아,"+npchar.name+", 제 행동을 사과하오... 당신이 훌륭한 분이라면 앞으로도 거래하겠소, 그 점은 확실하니, 지금은 이만 작별하겠소.";
			link.l1.go = "Usurer_Escape_5";
		break;
		
		case "Usurer_Escape_5":
			string sColony;
			sColony = npchar.city;
			SetNull2Deposit(sColony);
			dialog.text = "괜찮습니다. 이해하였습니다. 돈이 필요하시거나 투자를 원하신다면, 언제든 제게 말씀하십시오.";
			link.l1 = "감사하오. 하지만 내 돈은 내가 지키는 게 좋겠소. 또 봅시다.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "33");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "wait1";
			pchar.questTemp.SanBoxTarget.Slavetrader = true;
			ChangeCharacterComplexReputation(pchar, "fame", 25);
			LAi_LocationDisableOfficersGen(&Locations[FindLocation(pchar.location)], false); // разблокируем вход офицеров 2015
		break;
	//<--работорговец	

	//--> семейная реликвия
		case "Noblelombard":
			dialog.text = "오, 정말인가? 그가 직접 나와 이야기하고 싶지 않은 모양이군.... 좋아, 그럼 당신과 이 문제를 논의하지. "+pchar.GenQuest.Noblelombard.Name+" 나에게 빚이 있다 "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Summ))+": "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Money))+" 그리고 내 이자도 - "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Percent))+" 3개월 동안이오. 내일까지 돈을 못 받으면 그 유물을 팔겠소, 그에게 얼마나 소중하든 상관없소. 사업은 사업이니까.";
			if(sti(pchar.money) >= sti(pchar.GenQuest.Noblelombard.Summ))
			{
				link.l1 = "훌륭하군요! 그렇다면 지금 바로 원금과 이자를 모두 갚겠습니다 - "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Summ))+". 그는 자신의 유물을 직접 가져갈 것이오. 여기 돈이오.";
				link.l1.go = "Noblelombard_1";
			}
			if(sti(pchar.money) >= sti(pchar.GenQuest.Noblelombard.Percent)*2)
			{
				link.l2 = "제 의뢰인은 석 달 후에 돈을 준비할 것입니다. 거래를 합시다. 지난 석 달치 이자와 앞으로 석 달치 이자를 제가 드리겠습니다."+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Percent)*2)+". 그리고 그 빚 자체는 나중에 갚아드릴 것입니다.";
				link.l2.go = "Noblelombard_2";
			}
			if(sti(pchar.money) >= sti(pchar.GenQuest.Noblelombard.Percent))
			{
				link.l3 = "제 의뢰인이 석 달 후에 돈을 마련할 것입니다. 지난 석 달치 이자를 먼저 드릴 테니, 제 의뢰인이 충분한 돈을 마련할 때까지 기다려 주시는 건 어떻겠습니까?";
				link.l3.go = "Noblelombard_3";
			}
			link.l4 = "이 희귀품은 엄청난 값을 치러야 하오! 내 의뢰인이 직접 값을 치러야 할 것 같군.";
			link.l4.go = "Noblelombard_4";
			pchar.quest.noblelombard = "true";//лесник с нпчара на пчара
		break;
		
		case "Noblelombard_1":
			dialog.text = "훌륭하군! 모든 일이 잘 풀렸고, 나는 돈도 받았고\n "+pchar.GenQuest.Noblelombard.Name+" 그가 자신의 유물을 되찾게 될 것이오.";
			link.l1 = "거래하게 되어 기쁩니다, "+npchar.name+"! 그럼 이만.";
			link.l1.go = "exit";
			pchar.GenQuest.Noblelombard.Regard = sti(pchar.GenQuest.Noblelombard.Summ)*2;
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Noblelombard.Summ));
			pchar.GenQuest.Noblelombard = "full";
			AddCharacterExpToSkill(pchar, "Leadership", 150);
	
		break;
		
		case "Noblelombard_2":
			if(sti(pchar.GenQuest.Noblelombard.Chance) < 7)
			{
				dialog.text = "흠... 좋아. 이 정도면 괜찮네. 하지만 만약\n "+pchar.GenQuest.Noblelombard.Name+" 3개월 안에 돈을 찾지 못하면, 나는 더 이상 기한을 연장해 주지 않을 것이오. 반드시 그에게 이 사실을 알리시오.";
				link.l1 = "그러겠습니다! 우리가 거래를 성사시켜서 기쁩니다. 이제 안녕히 가십시오.";
				link.l1.go = "exit";
				pchar.GenQuest.Noblelombard.Regard = sti(pchar.GenQuest.Noblelombard.Percent)*4;
				AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Noblelombard.Percent)*2);
				pchar.GenQuest.Noblelombard = "maxpercent";
				AddCharacterExpToSkill(pchar, "Leadership", 50);
				AddCharacterExpToSkill(pchar, "Fortune", 70);
			
			}
			else
			{
				dialog.text = "아니오. 그렇게는 안 됩니다. 해 지기 전까지 전액이 필요합니다. 당신의 '의뢰인'에게 반드시 그렇게 전하십시오. 더 이상 드릴 말씀이 없습니다.";
				link.l1 = "흠... 알겠소. 타협할 생각이 없다니 아쉽군.";
				link.l1.go = "Noblelombard_4";
				AddCharacterExpToSkill(pchar, "Fortune", 30);
			
			}
		break;
		
		case "Noblelombard_3":
			if(sti(pchar.GenQuest.Noblelombard.Chance) < 3)
			{
				dialog.text = "흠... 좋소. 당신 고객을 존중하는 마음에서만 받아들이겠소. 하지만 만약\n "+pchar.GenQuest.Noblelombard.Name+" 3개월 안에 돈을 마련하지 못하면, 더 이상 기한 연장은 없다고 전하시오. 반드시 그에게 알리도록 하시오.";
				link.l1 = "그러겠습니다! 거래가 성사되어 기쁩니다. 이제 안녕히 가십시오.";
				link.l1.go = "exit";
				pchar.GenQuest.Noblelombard.Regard = sti(pchar.GenQuest.Noblelombard.Percent)*2;
				AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Noblelombard.Percent));
				pchar.GenQuest.Noblelombard = "minpercent";
				AddCharacterExpToSkill(pchar, "Leadership", 50);
				AddCharacterExpToSkill(pchar, "Fortune", 150);
			}
			else
			{
				dialog.text = "아니오. 그건 안 됩니다. 해 지기 전에 전액이 필요하오. 당신의 '의뢰인'에게 반드시 그렇게 전하시오. 더 이상 할 말 없소.";
				link.l1 = "흠... 좋소. 타협할 생각이 없다니 아쉽군.";
				link.l1.go = "Noblelombard_4";
				AddCharacterExpToSkill(pchar, "Fortune", 60);
	
			}
		break;
		
		case "Noblelombard_4":
			DialogExit();
			pchar.GenQuest.Noblelombard = "fail";
		break;
		
		case "Noblelombard_5":
			if(sti(pchar.GenQuest.Noblelombard.Chance) == 9)
			{
				dialog.text = "정말이군! "+pchar.GenQuest.Noblelombard.Name+" 당신 이름으로 예금을 개설하지 않았소. 그는 우리 식민지에 있지도 않고, 유럽으로 떠났소. 정말이지, 그렇게 부정직한 사람은 처음 봤소. 나를 속이려 했지만 실패했지요. 나도 나름대로 몇 가지 수완이 있거든요...";
				link.l1 = "이 자식! 분명 약속했었는데....";
				link.l1.go = "Noblelombard_6";
			}
			else
			{	// Addon-2016 Jason уменьшаем раздачу дублонов
				dialog.text = "맞습니다. "+pchar.GenQuest.Noblelombard.Name+" 당신 이름으로 예금을 했습니다. 부디, 받아 주십시오...";
				link.l1 = "훌륭하군! 안녕히 가시오, "+npchar.name+".";
				link.l1.go = "Noblelombard_9";
			}
		break;
		
		case "Noblelombard_6":
			dialog.text = "너 같은 사람들에게 그런 것은 없어 "+pchar.GenQuest.Noblelombard.Name+" 그들은 명예도 양심도 없으니 말이오. 그자가 당신을 속였다는 말이오?";
			link.l1 = "그랬겠지. 뭐,\n "+npchar.name+", 나도 여기 오래 머물 생각은 없으니, 유럽도 좁은 곳이오... 언젠가 다시 만날지도 모르겠군. 안녕히!";
			link.l1.go = "Noblelombard_7";
		break;
		
		case "Noblelombard_7":
			DialogExit();
			AddDialogExitQuestFunction("Noblelombard_Usurer_bad");
		break;
		
		case "Noblelombard_9":
			DialogExit();
			AddDialogExitQuestFunction("Noblelombard_Usurer_good");
		break;
//<-- семейная реликвия

		// Бремя гасконца
		case "sharlie_credit":
			dialog.text = "나리, 저는 당신을 모릅니다. 저는 현지 시민이나 선장들에게만 돈을 빌려줍니다. 용서하십시오...";
			link.l1 = "알겠소. 그래도 아쉽군.";
			link.l1.go = "exit";
		break;
		// Бремя гасконца
		
		// Addon-2016 Jason, французские миниквесты (ФМК)
		// ФМК-Гваделупа
		case "FMQG_x":
			DelLandQuestMark(npchar);
			dialog.text = "뭐, 뭐라고... 무슨 뜻이오?";
			link.l1 = "너는 빌어먹을 쥐새끼야! 이제 내 말 똑똑히 들어라. 내가 그렇게 멍청하지는 않아. 피네트가 편지를 두 통 썼지. 그중 하나는 네게 줬고, 다른 하나는 내가 신뢰하는 사람에게 맡겨두었다. 만약 내게 무슨 일이 생기면, 내 사람이 그 편지를 곧장 총독 손에 전달할 거다...\n";
			link.l1.go = "FMQG_x1";
		break;
		
		case "FMQG_x1":
			dialog.text = "";
			link.l1 = "그러니 내 건강을 위해 매일 아침 예배 때 교회에서 기도나 하시오. 암살자를 보내는 대신 말이오. 마지막 경고다! 나를 해치려 들면 끝장날 줄 알아. 알겠나? 좋아. 심호흡하고 금화나 계속 세고 있으시오.";
			link.l1.go = "FMQG_x2";
		break;
		
		case "FMQG_x2":
			DialogExit();
			pchar.questTemp.FMQG = "end";
			FMQ_Count();
			AddQuestRecord("FMQ_Guadeloupe", "27");
			CloseQuestHeader("FMQ_Guadeloupe");
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			AddCharacterExpToSkill(pchar, "Sneak", 400);
			AddCharacterExpToSkill(pchar, "Sailing", 200);
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		break;
		
		// Другое
		case "NeHochuRazgovarivat":
			dialog.text = "너랑 말하고 싶지 않아.";
			link.l1 = "...";
			link.l1.go = "exit";
		break;
		
		// Леди Бет -->
		case "LadyBeth_Usurer_1":
			dialog.text = "물론이지요! 많은 이들이 그저 돈만 받고 떠나길 원합니다. 특히 최근 소문을 생각하면 더욱 그렇지요...";
			link.l1 = "무슨 소문인가?";
			link.l1.go = "LadyBeth_Usurer_2";
		break;
		
		case "LadyBeth_Usurer_2":
			dialog.text = "선원들 사이의 상황이 점점 악화되고 있다고들 하더군요. 블랙우드 나리께서도 이제는 정기적인 손실을 그냥 넘기기 시작했다지요—전에는 결코 없던 일이었는데 말입니다. 하지만 그건 제 일이 아닙니다. 저는 그저 물건을 팔 뿐이죠. 그래서 무엇에 관심이 있으십니까?";
			link.l1 = "본론으로 들어갑시다.";
			link.l1.go = "next";
			npchar.quest.item_date = "LadyBeth";
			pchar.questTemp.LadyBeth_Usurer = true;
		break;
		// Леди Бет <--
	}	
}

// ugeen проверка, можем ли мы использовать дублоны в качестве вклада
bool CheckUseDublons(ref NPChar)
{
	int iTest 	= FindColony(NPChar.City); // город банка
	if(iTest == -1) return false;
	
	ref rColony = GetColonyByIndex(iTest);
	 	 
	bool bOk1 = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea); 
	bool bOk2 = (GetCharacterItem(pchar,"gold_dublon") > 10) || (CheckItemMyCabin("gold_dublon") > 10);
	
	if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && bOk1 && bOk2) return true;

	return false;
}

void SlavetraderGalleonInWorld()
{
	//создаем галеон с рабами
	ref sld;
	string sName;
	sName = pchar.questTemp.Slavetrader.ShipName;
	sld = GetCharacter(NPC_GenerateCharacter("GaleonCap", "", "man", "man", 45, SPAIN, 20, true, "quest"));
	FantomMakeCoolSailor(sld, SHIP_LINESHIP, sName, CANNON_TYPE_CANNON_LBS42, 100, 100, 100);
	FantomMakeCoolFighter(sld, 45, 100, 100, "blade_21", "pistol5", "bullet", 100);
	sld.Ship.Mode = "war";	
	SetCaptanModelByEncType(sld, "war");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;
	sld.DontRansackCaptain = true;
	sld.WatchFort = true;
	sld.AlwaysEnemy = true;


	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "MusketsShoot");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	SetCharacterGoods(sld, GOOD_SLAVES, 3000 + rand(200));//положить в трюм рабов
	sld.ship.Crew.Morale = 100;
	ChangeCrewExp(sld, "Sailors", 100);
	ChangeCrewExp(sld, "Cannoners", 100);
	ChangeCrewExp(sld, "Soldiers", 100);
	//в морскую группу кэпа
	string sGroup = "SlaveGalleon";
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation)); 
	pchar.quest.SlaveHalleon_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.SlaveHalleon_AfterBattle.win_condition.l1.group = "SlaveGalleon";
	pchar.quest.SlaveHalleon_AfterBattle.function = "Slavetrader_SlaveHalleon_AfterBattle";
	sld.city = pchar.questTemp.Slavetrader.Island; //определим колонию, из бухты которой выйдет
	sld.cityShore = pchar.questTemp.Slavetrader.Island.Shore;
	sld.quest.targetCity = "Santiago"; //определим колонию, в бухту которой он придёт
	sld.quest.targetShore = GetIslandRandomShoreId(GetArealByCityName(sld.quest.targetCity));
	//Log_TestInfo("Captain of the galleon sailed away from " + sld.city + "and heading to " + sld.quest.targetShore);
	//==> на карту
	sld.mapEnc.type = "trade";
	//выбор типа кораблика на карте
	sld.mapEnc.worldMapShip = "quest_ship";
	sld.mapEnc.Name = "Galleon '" + sName + " '";
	int daysQty = 20; //дней доехать даем с запасом
	Map_CreateTrader(sld.cityShore, sld.quest.targetShore, sld.id, daysQty);//вот он, сам запуск энкаунтера
}

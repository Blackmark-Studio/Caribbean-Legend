//Jason общий диалог уличных монахов
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp, iTest;
	string sTemp, sTitle;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	iTest = FindColony(NPChar.City);
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			//--> диалог первой встречи
			if (npchar.quest.meeting == "0")
			{
				if (CheckAttribute(npchar, "quest.donation"))//пожертвования
				{
					dialog.text = "좋은 하루구나, 아들아. 가난한 이들과 너의 영혼, 그리고 성스러운 교회를 위해 은화 몇 닢을 자비로이 내어주길 부탁하노라.";
					link.l1 = "글쎄요, 신부님, 우리 모두가 그리스도와 교회가 가르치듯 서로 도와야 한다고 생각합니다. 그 돈이 어디에 쓰일지 말씀해 주시겠습니까?";
					link.l1.go = "donation";
					link.l2 = "용서해 주십시오, 신부님, 하지만 지금 저는 교회 쥐만큼이나 가난합니다.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				bool ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
				if (ok && sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Monkpassenger") && 7-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0 && 7-sti(RealShips[sti(Pchar.Ship.Type)].Class) < 3)//монах-пассажир
				{
					dialog.text = "좋은 하루구나, 아들아. 부탁이 하나 있네. 물론 보수는 지불하겠네.";
					link.l1 = "듣고 있습니다, 신부님. 무엇이 필요하십니까?";
					link.l1.go = "passenger";
					link.l2 = "정말 죄송합니다, 신부님, 하지만 가야만 합니다.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.capellan") && !CheckAttribute(pchar, "questTemp.ShipCapellan"))//корабельный капеллан
				{
					dialog.text = "안녕하구나, 아들아. 네가 선장인 것 같구나. 그래서 너에게 제안을 하나 하려 한다.";
					link.l1 = "듣고 있습니다, 신부님.";
					link.l1.go = "capellan";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				dialog.text = PCharRepPhrase(LinkRandPhrase("안녕하냐, 아들아. 무슨 고민이 있느냐?","안녕하느냐, 아들아. 고해하고 싶으면 신부님을 찾아가거라.","안녕하냐, 아들아. '너의 젊은 날에 너의 창조주를 기억하라.'"),LinkRandPhrase("안녕하냐, 아들아. 무슨 고민이 있느냐?","좋은 하루 보내거라, 아들아, 신의 축복이 있기를!","좋은 하루구나, 아들아, 하나님의 은총이 너에게 함께하길 바란다!"));
				link.l1 = LinkRandPhrase("아버지께도 마찬가지입니다. 잘 지내고 계십니까?","안녕하십니까, 신부님. 본당은 평안하십니까?","안녕하십니까, 신부님?");
				link.l1.go = "check";//на возможную выдачу квестов
				link.l2 = RandPhraseSimple("아버지, 질문이 있습니다.","정보가 필요해.");
				link.l2.go = "quests";//(перессылка в файл города)
				if (GetSquadronGoods(pchar, GOOD_SLAVES) > 0 && sti(pchar.money) >= GetSquadronGoods(pchar, GOOD_SLAVES)*10)
				{
					link.l3 = "신부님, 제 배에 사람들이 있습니다. 그들은 노예들인데, 기독교인도 있고 세례받지 않은 이교도도 있습니다. 이교도들에게 세례를 주시고, 기독교인들에게는 성찬식을 집전해 주십시오. 그 후에 저는 모두를 하느님과 우리 교회의 영광을 위해 해방시키겠습니다.";
					link.l3.go = "slaves";
				}
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && sti(pchar.reputation.nobility) > 41 && !CheckAttribute(pchar, "GenQuest.Shipshine") && 7-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0)
				{
					link.l4 = "신부님, 제 배에 축복을 내려 주시고 제 선원들을 위해 미사를 올려 주셨으면 합니다. 비용이 얼마나 들까요?";
					link.l4.go = "shipshine";
				}
				link.l10 = LinkRandPhrase("실례합니다, 신부님, 하지만 저는 가봐야 합니다.","폐를 끼쳐 죄송합니다, 신부님.","아버지, 제 배로 돌아가야 합니다. 안녕히 계십시오!");
				link.l10.go = "exit";
				npchar.quest.meeting = "1";
			}
			else
			{
				//--> диалог второй встречи
				dialog.text = LinkRandPhrase("또 왔구나, 내 아이야? 무슨 일이냐?","더 할 말이 있느냐, 아들아?","다시 보게 되어 반갑구나, 아들아.");
				link.l1 = LinkRandPhrase("아버지께도 마찬가지입니다. 어떻게 지내십니까?","안녕하세요, 신부님. 본당은 평안하신가요?","안녕하십니까, 아버지?");
				link.l1.go = "check";//на возможную выдачу квестов
				link.l2 = RandPhraseSimple("아버지, 묻고 싶은 것이 있습니다.","정보가 필요하다.");
				link.l2.go = "quests";//(перессылка в файл города)
				if (GetSquadronGoods(pchar, GOOD_SLAVES) > 0 && sti(pchar.money) >= GetSquadronGoods(pchar, GOOD_SLAVES)*10 && !CheckAttribute(npchar, "quest.slaves"))
					{
						link.l3 = "신부님, 제 배에는 사람들이 있습니다. 그들은 노예들로, 기독교인도 있고 세례받지 않은 이교도도 있습니다. 이교도들에게는 세례를 베풀어 주시고, 기독교인들에게는 성찬식을 집전해 주시길 바랍니다. 그 후에는 모두를 하느님과 우리 교회의 영광을 위해 해방시키겠습니다.";
						link.l3.go = "slaves";
					}
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && sti(pchar.reputation.nobility) > 41 && !CheckAttribute(pchar, "GenQuest.Shipshine") && 7-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0)
				{
					link.l4 = "신부님, 제 배에 축복을 내려 주시고 선원들을 위해 미사를 올려 주셨으면 합니다. 비용이 얼마나 들까요?";
					link.l4.go = "shipshine";
				}
				link.l10 = LinkRandPhrase("실례합니다, 신부님, 하지만 저는 가봐야겠습니다.","폐를 끼쳐 죄송합니다, 신부님.","신부님, 제 배로 가야겠습니다. 안녕히 계십시오!");
				link.l10.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "check":
			if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && rand(8) < 3 && !CheckAttribute(npchar, "quest.monkletter") && !CheckAttribute(pchar, "GenQuest.Monkletter") && !CheckAttribute(npchar, "quest.passenger")) //церковная депеша
			{
				pchar.GenQuest.Monkletter.City = FindFriendCityToMC(false);
				pchar.GenQuest.Monkletter.StartCity = npchar.city;//город квестодателя
				dialog.text = "긴급한 일이 있구나, 아들아. 이 서류들을 그 목사님께 전달해 주었으면 한다.  "+XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.City+"Gen")+". 그쪽으로 항해하십니까? 서류는 2주 안에 전달되어야 합니다...";
				link.l1 = "쉽군요, 신부님. 그 서류들을 주시면 제가 전달하겠습니다 "+XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.City+"Gen")+".";
				link.l1.go = "Monkletter";
				link.l2 = "기꺼이 하겠습니다, 신부님, 하지만 저는 다른 방향으로 항해 중입니다.";
				link.l2.go = "exit_monkletter";
				npchar.quest.monkletter = "true";
				break;
			}
			if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && rand(8) > 5 && sti(pchar.rank < 11) && !CheckAttribute(npchar, "quest.churchbooks") && !CheckAttribute(pchar, "GenQuest.Churchbooks") && !CheckAttribute(npchar, "quest.passenger")) //привезти молитвенники
			{
				pchar.GenQuest.Churchbooks.StartCity = npchar.city;//город квестодателя
				pchar.GenQuest.Churchbooks.Nation = npchar.nation;
				dialog.text = "아들아, 급한 일에 나를 도와줄 수 있겠느냐? 우리 교회에 성경책과 기도서가 부족하구나. 우리는 필요한 이들에게 모두 나눠주고 있지\n가장 가까운 식민지로 항해해 줄 수 있겠느냐 "+NationNameGenitive(sti(npchar.nation))+", 근처 교회에서 성경책과 기도서를 몇 권 가져와 주겠나? 그리고 한 달 안에 해주게. 남은 게 얼마 없네.";
				link.l1 = "기꺼이 교회를 도와드리겠습니다. 이 책들을 아무 신부에게서나 받을 수 있습니까?";
				link.l1.go = "Churchbooks";
				link.l2 = "기꺼이 하겠습니다, 신부님. 하지만 지금은 할 수 없습니다.";
				link.l2.go = "exit_churchbooks";
				npchar.quest.churchbooks = "true";
				break;
			}
			
			dialog.text = RandPhraseSimple("괜찮다, 아들아. 따뜻한 말 고맙구나.","우리 본당은 괜찮다, 아들아. 염려해 주어 고맙구나.");
			link.l1 = "그럼 저는 가봐야겠습니다, 신부님.";
			link.l1.go = "exit";
		break;
		
//-------------------------------------------------пожертвования------------------------------------------------
		case "donation":
			sTemp = DonationType();
			dialog.text = "물론이지, 아들아. "+sTemp+"";
			link.l1 = "어느 정도의 기부가 충분하다고 볼 수 있겠습니까?";
			link.l1.go = "donation_1";
		break;
		
		case "donation_1":
			dialog.text = "모두 자네의 주머니 사정과 뜻에 달려 있네, 아들아. '하느님께서는 기쁜 마음으로 드리는 이를 사랑하신다네.' 어떤 헌금이든 진심으로 감사하게 받겠네.";
			link.l1 = "100 페소";
			link.l1.go = "donation_rate_1";
			link.l2 = "1000 페소";
			link.l2.go = "donation_rate_2";
			link.l3 = "5000페소";
			link.l3.go = "donation_rate_3";
			link.l4 = "10,000 페소";
			link.l4.go = "donation_rate_4";
		break;
		
		case "donation_rate_1"://никаких плюшек
			if (sti(pchar.money) >= 100)
			{
				AddMoneyToCharacter(pchar, -100);
				dialog.text = "동전 주어서 고맙구나, 내 아이야! 좋은 일에 쓰일 것이다!";
				link.l1 = "천주님, 별말씀을요.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "속지 말라, 하나님은 조롱받지 아니하시나니, 사람이 무엇을 심든지 그대로 거두리라. 자기 육체에 심는 자는 육체로부터 썩어질 것을 거두고, 성령에 심는 자는 성령으로부터 영생을 거두리라.";
				link.l1 = "하하! 설교는 집어치워. 자선 따위 안 해. 꺼져!";
				link.l1.go = "donation_exit";
			}
		break;
		
		case "donation_rate_2":
			if (sti(pchar.money) >= 1000)
			{
				AddMoneyToCharacter(pchar, -1000);
				dialog.text = "감사하네, 아들아. 이 금액은 우리 본당의 선교에 큰 도움이 될 것이네. 축복이 있기를!";
				link.l1 = "행운을 빕니다, 신부님!";
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 5);
				AddCharacterExpToSkill(pchar, "Leadership", 20);
				AddCrewMorale(pchar, 2);
			}
			else
			{
				dialog.text = "신의 징벌이 너를 기다리고 있다, 이놈아! 그리스도의 거룩한 교회의 종을 조롱하는 것은 신성모독이다!";
				link.l1 = "하하! 나는 자선 같은 건 안 해. 꺼져!";
				link.l1.go = "donation_exit";
			}
		break;
		
		case "donation_rate_3":
			if (sti(pchar.money) >= 5000)
			{
				AddMoneyToCharacter(pchar, -5000);
				dialog.text = "이렇게 관대할 줄은 상상도 못했구나, 아들아! 다음에 주교님께 편지 쓸 때 너를 꼭 언급하마, 그리고 매일 너를 위해 기도할 것이다! 내가 너를 축복하고, 네 돈도 감사히 받겠다!";
				link.l1 = "돈은 하나님의 뜻을 위해 쓰이지 않으면 아무 의미도 없습니다! 행운을 빕니다, 신부님!";
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 5);
				AddCharacterExpToSkill(pchar, "Leadership", 40);
				AddCrewMorale(pchar, 3);
				ChangeCharacterComplexReputation(pchar, "nobility", 1);
				ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 1);
			}
			else
			{
				dialog.text = "신의 징벌이 너를 기다린다, 이놈아! 그리스도의 거룩한 교회의 종을 조롱하는 것은 신성모독이다!";
				link.l1 = "하하! 나는 자선 따위 안 해. 꺼져!";
				link.l1.go = "donation_exit";
			}
		break;
		
		case "donation_rate_4":
			if (sti(pchar.money) >= 10000)
			{
				AddMoneyToCharacter(pchar, -10000);
				dialog.text = "뭐라고... 내가 제대로 들은 게요? 정말 만 페소를 기부하시겠다고요!? 신의 축복이 있기를 바라며, 감사히 돈을 받겠습니다. 다음에 주교님께 보내는 편지에 당신을 꼭 언급하겠고, 매일 당신을 위해 기도하겠습니다! 교회에 정말 큰 도움이 되는군요!";
				link.l1 = "많이 받은 자에게는 많은 것이 요구된다', 맞지요? 행운을 빕니다, 신부님.";
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 10);
				AddCharacterExpToSkill(pchar, "Leadership", 60);
				AddCrewMorale(pchar, 5);
				ChangeCharacterComplexReputation(pchar, "nobility", 1);
				ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
				ChangeCrewExp(pchar, "Sailors", 5);
				ChangeCrewExp(pchar, "Cannoners", 5);
				ChangeCrewExp(pchar, "Soldiers", 5);
			}
			else
			{
				dialog.text = "신의 징벌이 너를 기다리고 있다, 이놈아! 그리스도의 거룩한 교회의 종을 조롱하는 것은 신성모독이다!";
				link.l1 = "하하! 나는 자선 같은 건 안 해. 꺼져!";
				link.l1.go = "donation_exit";
			}
		break;
		
		case "donation_exit":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterHealth(pchar, -5);
			LAi_CharacterDisableDialog(npchar);
		break;
		
//-------------------------------------------отпустить рабов---------------------------------------------------
		case "slaves":
			dialog.text = "물론이지, 아들아. 이 불쌍하고 비참한 이들을 돕는 것은 우리의 신성한 의무란다. 네가 부탁한 대로 하겠다.";
			link.l1 = "감사합니다, 신부님. 세례와 성사를 받은 죄수 한 명마다 8리알 10닢씩 기부하겠습니다.";
			link.l1.go = "slaves_1";
		break;
		
		case "slaves_1":
			AddMoneyToCharacter(pchar, -GetSquadronGoods(pchar, GOOD_SLAVES)*10);
			dialog.text = "꼭 필요한 것은 아니지만, 도둑질한 사례비를 감사히 받겠소. 당신의 돈은 우리 본당의 여러 사명에 쓰일 것이오. 내게 당신의 배까지 안내해 주겠소?";
			link.l1 = "네, 신부님. 저를 따라오십시오.";
			link.l1.go = "slaves_2";
		break;
		
		case "slaves_2":
			npchar.quest.slaves = "true";
			DialogExit();
			SetLaunchFrameFormParam("Two hours later"+ NewStr() +"Slaves were freed", "Monk_RemoveSlaves", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 2, 10); //крутим время
			RecalculateJumpTable();
		break;
//<-- отпустить рабов

//----------------------------------------------освятить корабль------------------------------------------------
		case "shipshine":
			//поиск старшего класса
			iTemp = 7;
			for (i=0; i<COMPANION_MAX; i++)
			{
				int iIdx = GetCompanionIndex(GetMainCharacter(), i);
				if (iIdx >= 0)
				{
					sld = GetCharacter(iIdx);
					if (GetCharacterShipClass(sld) < iTemp) iTemp = GetCharacterShipClass(sld);
				}
			}
			switch (GetCompanionQuantity(pchar))
			{
				case 1: 
					sTemp = "I have only one ship in my squadron and it's "+iTemp+" rank.";
					pchar.GenQuest.Shipshine.Money = 5000*(7-iTemp);
				break;
				case 2:
					sTemp = "I have two ships in my squadron and the biggest one is "+iTemp+" rank.";
					pchar.GenQuest.Shipshine.Money = makeint(1.8*(5000*(7-iTemp)));
				break;
				case 3:
					sTemp = "I have three ships in my squadron and the biggest one is "+iTemp+" rank.";
					pchar.GenQuest.Shipshine.Money = makeint(2.6*(5000*(7-iTemp)));
				break;
				case 4:
					sTemp = "I have four ships in my squadron and the biggest one is "+iTemp+" rank.";
					pchar.GenQuest.Shipshine.Money = makeint(3.4*(5000*(7-iTemp)));
				break;
				case 5:
					sTemp = "I have five ships in my squadron and the biggest one is "+iTemp+" rank.";
					pchar.GenQuest.Shipshine.Money = makeint(4.2*(5000*(7-iTemp)));
				break;
			}
			dialog.text = "그것은 전적으로 당신 함대의 총 함선 수와 그 크기에 달려 있습니다.";
			link.l1 = ""+sTemp+"";
			link.l1.go = "shipshine_1";
		break;
		
		case "shipshine_1":
			dialog.text = "값을 치러야 할 거요 "+FindRussianMoneyString(sti(pchar.GenQuest.Shipshine.Money))+", 아들아.";
			if (sti(pchar.money) >= sti(pchar.GenQuest.Shipshine.Money))
			{
				link.l1 = "이 금액을 드릴 수 있습니다, 신부님. 돈을 받으십시오.";
				link.l1.go = "shipshine_2";
			}
			link.l2 = "안타깝게도, 지금 내게 그만한 돈은 없어.";
			link.l2.go = "shipshine_exit";
		break;
		
		case "shipshine_2":
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Shipshine.Money));
			dialog.text = "좋다, 아들아. 내가 성물을 챙기고 항구로 가자꾸나.";
			link.l1 = "따라오십시오, 신부님.";
			link.l1.go = "shipshine_3";
		break;
		
		case "shipshine_3":
			DialogExit();
			SetLaunchFrameFormParam("Several hours later"+ NewStr() +"The priest has held mass aboard your ship and blessed it", "Monk_Shipshine", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, GetCompanionQuantity(pchar), 10); //крутим время
			RecalculateJumpTable();
		break;
		
		case "shipshine_exit":
			DialogExit();
			DeleteAttribute(Pchar, "GenQuest.Shipshine");
		break;
//<-- освятить корабль

//------------------------------------------корабельный капеллан-----------------------------------------------
		case "capellan":
			dialog.text = "안녕하십니까, 선장님. 제 소개를 하겠습니다. 저는 신부이며 전함에서 함선 사목으로 꽤 오랜 경험이 있습니다. 지난 배에서는 선장과 저 사이에... 도덕적인 견해 차이가 있어 떠나게 되었습니다. 저를 선원으로 받아주시겠습니까?";
			link.l1 = "신부님이 배에 타셨군요? 말씀해 보시죠, 신부님, 배의 사제는 무슨 일을 하십니까?";
			link.l1.go = "capellan_1";
			pchar.questTemp.ShipCapellan = "true";
		break;
		
		case "capellan_1":
			dialog.text = "왜냐하면, 그 이유는 아주 명백하오. 나는 당신과 선원들을 위해 하느님께 기도하고, 매일 미사를 집전하며, 전투 전에 당신의 부하들에게 축복을 내리고 고해성사를 들어주오. 하느님의 말씀이 당신 선원들의 손과 영혼에 힘을 더해 주지. 당신의 선원들은 정기적으로 영성체와 고해성사를 받을 기회를 갖게 될 것이오. 믿으시오, 은총의 상태에 있는 선원은 불경한 자가 주저하는 상황에서도 굳건히 버틸 것이오.\n내가 바라는 것은 많지 않소. 내 고향 본당을 위한 오만 페소의 일시불, 선실 안에 간단한 침상 하나, 그리고 당신 장교들과 같은 식사만 있으면 충분하오. 그게 전부요.";
			if (sti(pchar.money) >= 50000)
			{
				link.l1 = "흥미롭군요... 맞는 말이오, 훌륭한 선장은 선원들의 몸뿐만 아니라 영혼도 돌봐야 하오. 배에 오신 것을 환영하오, 신부님!";
				link.l1.go = "capellan_2";
			}
			link.l2 = "아니요, 신부님. 죄송하지만, 신부님의 도움을 받을 형편이 못 됩니다.";
			link.l2.go = "capellan_exit";
		break;
		
		case "capellan_exit":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "capellan_2":
			AddMoneyToCharacter(pchar, -50000);
			chrDisableReloadToLocation = true;//закрыть локацию
			dialog.text = "신뢰해 주어서 고맙구나, 아들아. 자네는 돈을 현명하게 썼네. 하지만 미리 경고하마, 나는 오직 가치 있는 선장만을 섬기네. 상인이든 사략선장이든 상관없지. 하지만 해적선에서는 절대 설교하지 않을 걸세!\n그러니 만약 자네가 악마의 해적기를 올린다면, 나는 첫 번째 항구에서 즉시 자네 배를 떠날 것이네.";
			link.l1 = "그 점은 고려해 보겠소, 신부님, 실망시키지 않도록 노력하겠소. 배에 올라가셔서 선원들에게 자신을 소개해 주십시오!";
			link.l1.go = "capellan_3";
		break;
		
		case "capellan_3":
			DialogExit();
			pchar.questTemp.ShipCapellan.id = npchar.id;
			AddDialogExitQuestFunction("Monk_Capellan_DlgExit");
		break;
		
		case "capellan_4":
			dialog.text = "무슨 일 있느냐, 아들아?";
			link.l1 = "아닙니다, 아무것도 아닙니다, 신부님.";
			link.l1.go = "exit";
			link.l2 = "신부님, 다음 항구에서 배에서 내려 주셨으면 합니다. 더 이상 설명하지 않겠습니다.";
			link.l2.go = "capellan_5";
			NextDiag.TempNode = "capellan_4";
		break;
		
		case "capellan_5":
			dialog.text = "좋다, 아들아. 여기서는 네가 책임자다. 다음 정착지에서 네 배를 떠나겠다.";
			link.l1 = "이해해 주셔서 감사합니다, 신부님.";
			link.l1.go = "capellan_6";
		break;
		
		case "capellan_6":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			ShipCapellan_Remove();
		break;
		
		case "capellan_7":
			dialog.text = "이런, 선장님! 내가 해적 깃발을 올리면 당신을 떠나겠다고 경고했었지 않소! 다음 항구에서 당신의 배를 떠나겠소. 당신이 즉시 회개하고 성모 교회의 품으로 돌아오길 기도하겠소.";
			link.l1 = "젠장...";
			link.l1.go = "exit";
			NextDiag.TempNode = "capellan_7";
		break;
//<-- капеллан
	
//--------------------------------------------монах-пассажир---------------------------------------------------
		case "passenger":
			if (hrand(19) < 15) SetPassengerParameter("Monkpassenger", false);
			else SetPassengerParameter("Monkpassenger", true);
			if (!CheckAttribute(pchar, "GenQuest.Monkpassenger.Enemycity"))
			{
				dialog.text = "My "+GetSexPhrase("아들","딸")+", 나는 ~에 가야 해 "+XI_ConvertString("Colony"+pchar.GenQuest.Monkpassenger.City)+" 시작이다 "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Monkpassenger.City)+"Dat")+", 왜냐하면 "+FindRussianDaysString(sti(pchar.GenQuest.Monkpassenger.DaysQty))+". 내가 돈을 줄게 "+FindRussianMoneyString(sti(pchar.GenQuest.Monkpassenger.Money))+" 그 일에 대해서. 어떻게 생각하시오?";
			}
			else
			{
				dialog.text = "My "+GetSexPhrase("아들","딸")+", 주님의 뜻은 오묘하니, 그래서 나는 믿을 만한 선장을 찾고 있소. 나를 데려다줄 수 있겠소 "+XI_ConvertString("Colony"+pchar.GenQuest.Monkpassenger.City)+", 그것이 있는 "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Monkpassenger.City)+"Dat")+"? 적들의 잠 없는 감시 속에 불타는 게헨나로 여행을 가는 기분이라는 것도 이해합니다. 그리고 당신이 예수 그리스도가 아니라는 것도 알고 있지만, 저 역시 사도가 아니기에 약간의 저축은 있습니다. 그러니 "+FindRussianDublonString(sti(pchar.GenQuest.Monkpassenger.Money))+" 이 정도면 되겠소?";
			}
			link.l1 = "동의합니다, 신부님.";
			link.l1.go = "passenger_1";
			link.l2 = "죄송합니다, 신부님, 하지만 저는 다른 방향으로 항해하고 있습니다. 도와드릴 수 없습니다.";
			link.l2.go = "passenger_exit";
			npchar.quest.passenger = true;
		break;
		
		case "passenger_exit":
			dialog.text = "이 모든 것은 신의 뜻이니라, 아들아. 나는 다른 배를 기다리겠다. 평안이 함께하길!";
			link.l1 = "안녕히 계십시오, 신부님.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.Monkpassenger");
		break;
		
		case "passenger_1":
			dialog.text = "신의 가호가 있기를! 목적지에 도착하면 보수를 받게 될 것이오.";
			link.l1 = "아버지, 제 배로 가세요. 곧 출항합니다.";
			link.l1.go = "passenger_2";
		break;
		
		case "passenger_2":
			DialogExit();
			pchar.GenQuest.Monkpassenger.id = npchar.id;
			DeleteAttribute(npchar, "LifeDay");
			LAi_RemoveLoginTime(npchar);
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			LAi_SetImmortal(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sTitle = npchar.index+"Citizpassenger";

// LDH 13Sep17 - do not add to an existing Citizpassenger record -->
// "Rename" the quest record by copying it to a new name and deleting the old record
			if (CheckAttribute(pchar, "questinfo."+sTitle))
			{
				string sTempLDH = frand(1);
				sTempLDH = strcut(sTempLDH, 2, 5);    // 4 random digits
				string sTitle1 = sTitle+sTempLDH;

				aref arTo, arFrom;
				makearef(arFrom, pchar.questinfo.(sTitle));
				makearef(arTo,   pchar.questinfo.(sTitle1));
				CopyAttributes(arTo, arFrom);
				pchar.questinfo.(sTitle1) = "";

				DeleteAttribute(pchar, "questinfo."+sTitle);

				Trace("Duplicate Citizpassenger record "+sTitle+" copied to "+sTitle1+" **");
			}
// <--

			AddQuestRecordEx(sTitle, "Citizpassenger", "1");
			AddQuestUserDataForTitle(sTitle, "sType", "monk");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			sTemp = XI_ConvertString("Colony" +pchar.GenQuest.Monkpassenger.City+"Gen") + ", which is on " + XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Monkpassenger.City)+"Voc")+"."; // belamour gen
			AddQuestUserDataForTitle(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sDays", FindRussianDaysString(sti(pchar.GenQuest.Monkpassenger.DaysQty)));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
            if (!CheckAttribute(pchar, "GenQuest.Monkpassenger.Enemycity")) AddQuestUserData(sTitle, "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Monkpassenger.Money)));
			else AddQuestUserData(sTitle, "sMoney", FindRussianDublonString(sti(pchar.GenQuest.Monkpassenger.Money)));
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			pchar.quest.Monkpassenger.win_condition.l1 = "location";
			pchar.quest.Monkpassenger.win_condition.l1.location = pchar.GenQuest.Monkpassenger.City+"_town";
			pchar.quest.Monkpassenger.function = "Monkpassenger_complete";
			SetFunctionTimerCondition("Monkpassenger_Over", 0, 0, sti(pchar.GenQuest.Monkpassenger.DaysQty), false);
		break;
		
		case "passenger_3":
			pchar.quest.Monkpassenger_Over.over = "yes"; //снять таймер
			dialog.text = "감사합니다, 내 "+GetSexPhrase("아들","딸")+". 약속을 지켰으니, 이제 내 차례요. 약속대로 돈을 가져가시오.";
			link.l1 = "감사합니다. 행운을 빕니다, 신부님.";
			link.l1.go = "passenger_4";
		break;
		
		case "passenger_4":
			DialogExit();
			npchar.lifeday = 0;
			RemovePassenger(Pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
			OfficersReaction("good");				
			AddCharacterExpToSkill(pchar, "Sailing", 80);
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			if (CheckAttribute(pchar, "GenQuest.Monkpassenger.Enemycity"))
			{
				AddCharacterExpToSkill(pchar, "Sneak", 50);
				TakeNItems(pchar, "gold_dublon", sti(pchar.GenQuest.Monkpassenger.Money));
			}
			else AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Monkpassenger.Money));
			sTitle = npchar.index+"Citizpassenger";
			AddQuestRecordEx(sTitle, "Citizpassenger", "3");
			CloseQuestHeader(sTitle);
			DeleteAttribute(Pchar, "GenQuest.Monkpassenger");
		break;
//<-- монах-пассажир
		
//---------------------------------------------церковная депеша-------------------------------------------------
		case "exit_monkletter":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Monkletter");
		break;
		
		case "Monkletter":
			dialog.text = "여기 있다. 이 꾸러미를 받아라, 아들아. 기억해라, 이걸 전달할 시간은 오직 2주뿐이다. 목사님이 기다리고 계신다. 어서 가거라, 그리고 신의 가호가 함께하길!";
			link.l1 = "아버지, 실망시키지 않을게요. 안녕히 계세요.";
			link.l1.go = "Monkletter_1";
		break;
		
		case "Monkletter_1":
			DialogExit();
			GiveItem2Character(pchar, "letter_church");
			ReOpenQuestHeader("Monkletter");
			AddQuestRecord("Monkletter", "1");
			AddQuestUserData("Monkletter", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("Monkletter", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.City+"Gen"));
			AddQuestUserData("Monkletter", "sStartCity", XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.StartCity));
			SetFunctionTimerCondition("Monkletter_Over", 0, 0, 15, false);
			OfficersReaction("good");
		break;
//<-- Церковная депеша
		
//-------------------------------------------доставить молитвенники---------------------------------------------
		case "exit_churchbooks":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Churchbooks");
		break;

		case "Churchbooks":
			dialog.text = "그래. 어느 식민지에서든 구할 수 있어. "+NationNameGenitive(sti(npchar.nation))+". 찾은 모든 책을 교회에 계신 우리 목사님께 가져다드리시오. 신의 가호가 있기를!";
			link.l1 = "감사합니다! 곧 책을 받게 될 것입니다.";
			link.l1.go = "Churchbooks_1";
		break;
		
		case "Churchbooks_1":
			DialogExit();
			ReOpenQuestHeader("Churchbooks");
			AddQuestRecord("Churchbooks", "1");
			AddQuestUserData("Churchbooks", "sNation", NationNameGenitive(sti(pchar.GenQuest.Churchbooks.Nation)));
			AddQuestUserData("Churchbooks", "sStartCity", XI_ConvertString("Colony"+pchar.GenQuest.Churchbooks.StartCity));
			SetFunctionTimerCondition("Churchbooks_Over", 0, 0, 30, false);
			pchar.GenQuest.Churchbooks = "go";
			switch (rand(4))
			{
				case 0: pchar.GenQuest.Churchbooks.Item = "amulet_2"; break;
				case 1: pchar.GenQuest.Churchbooks.Item = "amulet_3"; break;
				case 2: pchar.GenQuest.Churchbooks.Item = "amulet_6"; break;
				case 3: pchar.GenQuest.Churchbooks.Item = "amulet_7"; break;
				case 4: pchar.GenQuest.Churchbooks.Item = "amulet_10"; break;
			}
			OfficersReaction("good");
		break;
//<-- доставить молитвенники
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

string DonationType()
{
	string sText;
	switch (hrand(9))
	{
		case 0: sText = "I am gathering money for building "+LinkRandPhrase("a chapel","an almshouse","a hospital")+". The local citizens give little in alms so I must ask prosperous men like you." break;
		case 1: sText = "I am gathering donations for our church. Sailors don't usually have much time to visit the house of God, but everyone must do his best in saving his own soul." break;
		case 2: sText = "I am gathering money to buy food and medicines for our poorhouse for the sick, widows, orphans, and infirm. Please donate sir, because there but for the grace of God go all of us." break;
		case 3: sText = "I am gathering money for new sacred vessels, the ones which we brought from Europe are battered with continual use. It's a duty for every Christian to take care of our Church." break;
		case 4: sText = "I am gathering money for our church's renovation, the roof is leaking terribly and the pews have to be repaired too. It's a duty for every Christian to take care of our Church." break;
		case 5: sText = "I am gathering money to pay the good artist who is able to paint the walls of our church and draw scenes from the Bible on them for those of our parish who cannot read. It's a duty for every Christian to take care about his Church." break;
		case 6: sText = "I am gathering money for a new high altar for our church. Our parish is poor and we would like a noble seat for the Blessed Sacrament. I do hope for your help." break;
		case 7: sText = "There are a lot of wounded sailors from pirate raids in our hospital. They need medicines and bandages. Pray help them, for you can really understand sufferings of the common sailors." break;
		case 8: sText = "I am trying to get money for clothes and food for our poorest citizens. The only hope they have is our holy church. Please help them." break;
		case 9: sText = "I am going to go deep in our island for missionary work to bring the light of Christ's Gospel to the lost souls of the pagan Indians. I am gathering funds for this expedition. Please help our good deed!" break;
	}
	return sText;
}

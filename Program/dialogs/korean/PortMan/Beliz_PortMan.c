// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	bool ok;
    int iTest;
    ref rColony;
    string sFrom_sea = "";
    switch (Dialog.CurrentNode)
	{
		case "quests":
			//регата
			if (CheckAttribute(pchar, "questTemp.Regata.Go") && !CheckAttribute(npchar, "quest.regatatalk"))
			{
				dialog.text = "무슨 일이오? 아, 그대가 바로 레가타 참가자구나! 맞소?";
				link.l1 = "그렇습니다, 나리. 규정에 따라 여기서 등록해야 합니다.";
				link.l1.go = "Regata_check";
				break;
			}
			//регата
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문인데?","무슨 일이오, "+GetAddress_Form(NPChar)+"?"),"이미 나에게 질문을 해봤잖소 "+GetAddress_Form(NPChar)+"...","오늘만 벌써 세 번째로 같은 질문을 하셨군요...","이봐, 항구 일에 대해 할 말이 없으면 쓸데없는 질문으로 귀찮게 하지 마라.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내 마음이 바뀌었소.","할 말이 없어."),"신경 쓰지 마.","정말, 벌써 세 번째군...","미안하지만, 지금은 항구 일에 관심 없소.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Грани справедливости
			if (CheckAttribute(pchar, "questTemp.GS_Portman"))
			{
				link.l1 = "당신의 목숨을 노린 자가 있었다고 하던데, 범인을 쫓고 있습니까?";
				link.l1.go = "GS_Portman_1";
			}
			if (CheckAttribute(pchar, "questTemp.GS_NaemnikMertv"))
			{
				link.l1 = "당신의 목숨을 노렸던 자가 쓰러졌습니다, 나리. "+npchar.lastname+". 이제 더 이상 당신을 위협하는 것은 없습니다.";
				link.l1.go = "GS_Portman_6";
			}
			//<-- Грани справедливости
		break;

		//регата
		case "Regata_check":
		iTest = FindColony(npchar.city); 
		if (iTest != -1)
		{
			rColony = GetColonyByIndex(iTest);
			sFrom_sea = rColony.from_sea;
		}
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
		{
			bool bRegLugger = sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_LUGGER || sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_CAREERLUGGER;
			if (CheckAttribute(pchar, "questTemp.Regata.Breach") || GetCompanionQuantity(pchar) > 1 || !bRegLugger || pchar.Ship.Name != "Saint Catherine")
			{
			dialog.text = "흠... 자네가 레가타 규칙을 어겼으니 내가 실격 처리해야겠군. 유감이네. 다음 항해에는 참가할 수 없을 걸세. 이미 포트 로얄로 보고서를 준비해 두었네.";
			link.l1 = "이런... 안타깝군! 하지만 여기서 내가 할 수 있는 건 없어, 네가 너무 경계했으니. 잘 가라!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Regata");
			pchar.quest.Regata_PU.over = "yes"; // mitrokosta снимаем прерывание
			AddQuestRecord("Regata", "45");
			CloseQuestHeader("Regata");
			}
			else
			{
			pchar.questTemp.Regata.FirstTransitionTime = GetPastTime("hour", sti(pchar.questTemp.Regata.StartYear), sti(pchar.questTemp.Regata.StartMonth), sti(pchar.questTemp.Regata.StartDay), stf(pchar.questTemp.Regata.StartTime), GetDataYear(), GetDataMonth(), GetDataDay(), GetTime());//истратил ГГ в часах на 1 переход
			dialog.text = "등록합시다: 선장 "+GetFullName(pchar)+", 배는 "+pchar.Ship.Name+"... 레가타의 지속 시간이 시간 단위로 "+sti(pchar.questTemp.Regata.FirstTransitionTime)+". 완료되었습니다, 결과가 기록되었으니 계속 가셔도 됩니다.";
			link.l1 = "내 계급을 말해 줘.";
			link.l1.go = "Regata_info";
			}
		}
		else
		{
			dialog.text = "여기 있긴 한데 네 배가 안 보여. 어디 있지?";
			link.l1 = "죄송합니다, 나리. 즉시 제 배를 항구로 옮기겠습니다.";
			link.l1.go = "exit";
		}
		break;
		
		case "Regata_info":
			int n=1;
			string sTemp, sName, sShip;
			for (int i=1; i <=5; i++)
			{
				if (i==1) sTemp = "a";
				if (i==2) sTemp = "b";
				if (i==3) sTemp = "c";
				if (i==4) sTemp = "d";
				if (i==5) sTemp = "e";
				if (pchar.questTemp.Regata.AdversaryFirstTransition.Time.(sTemp) < sti(pchar.questTemp.Regata.FirstTransitionTime))
				{
					n++;
					sName = pchar.questTemp.Regata.AdversaryName.(sTemp);//имя ближайшего противника
					sShip = pchar.questTemp.Regata.AdversaryShipName.(sTemp);//его корабль
				}
			}
			if (n==1)
			{
			dialog.text = "당신이 선두에 있습니다. 축하합니다! 계속 힘내세요!";
			link.l1 = "고맙소!";
			link.l1.go = "exit";
			AddQuestRecord("Regata", "4");
			}
			else
			{
				if (n==6)
				{
				dialog.text = "네가 마지막이다. 서둘러야 해.";
				link.l1 = "가는 중이오!";
				link.l1.go = "exit";
				AddQuestRecord("Regata", "9");
				}
				else
				{
					if (n==2)
					{
					dialog.text = "너는 두 번째다. 우두머리는 "+sName+" 배에서 "+sShip+". 아직은 그를 따돌릴 수 있겠군.";
					link.l1 = "고마워! 한번 해볼게!";
					link.l1.go = "exit";
					AddQuestRecord("Regata", "5");
					}
					else
					{
					dialog.text = "당신의 계급은 "+n+". 가장 가까운 상대는 "+sName+" 배에서 "+sShip+".";
					link.l1 = "고맙소!";
					link.l1.go = "exit";
					if (n==3) AddQuestRecord("Regata", "6");
					if (n==4) AddQuestRecord("Regata", "7");
					if (n==5) AddQuestRecord("Regata", "8");
					}
				}
			}
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			npchar.quest.regatatalk = "true";
			pchar.questTemp.Regata.Beliz = "true";//отметка Белиза
			pchar.quest.Regata_Check1.win_condition.l1 = "location";
			pchar.quest.Regata_Check1.win_condition.l1.location = "Cuba1";
			pchar.quest.Regata_Check1.function = "RegataCheck";//проверка 1
			pchar.quest.Regata_Check2.win_condition.l1 = "location";
			pchar.quest.Regata_Check2.win_condition.l1.location = "Cuba2";
			pchar.quest.Regata_Check2.function = "RegataCheck";//проверка 2
			pchar.quest.Regata_Check.win_condition.l1 = "location";
			pchar.quest.Regata_Check.win_condition.l1.location = "Hispaniola2";
			pchar.quest.Regata_Check.function = "RegataCheck";//проверка 3
			pchar.questTemp.Regata.AttackIsland = "Cuba1";
			pchar.questTemp.Regata.AttackNation = SPAIN;
			pchar.quest.Regata_Attack.win_condition.l1 = "location";
			pchar.quest.Regata_Attack.win_condition.l1.location = "Cuba1";
			pchar.quest.Regata_Attack.function = "RegataAttack_Lugger";//первая засада у Сантьяго
			pchar.quest.Regata_Hunter.win_condition.l1 = "location";
			pchar.quest.Regata_Hunter.win_condition.l1.location = "Cuba2";
			pchar.quest.Regata_Hunter.function = "RegataAttack_Hunter";//ДУ у Гаваны
			pchar.questTemp.Regata.Town = "Portpax";
			pchar.quest.Regata_PU.win_condition.l1 = "locator";
			pchar.quest.Regata_PU.win_condition.l1.location = "Portpax_town";
			pchar.quest.Regata_PU.win_condition.l1.locator_group = "reload";
			pchar.quest.Regata_PU.win_condition.l1.locator = "reload10_back";
			pchar.quest.Regata_PU.win_condition.l2 = "Night";
			pchar.quest.Regata_PU.function = "RegataPU_Open";//вход в ПУ ночью
		break;
		//регата
		
		//--> Грани справедливости
		case "GS_Portman_1":
			dialog.text = "내 암살 시도는 실제로 있었소, 그건 사실이오. 수색에 관해서는... 꼭 그런 건 아니오. 나는 도망자를 잡아오라는 게 아니라, 그의 목이 필요하오. 그래야만 내게 평안이 돌아올 것이오.";
			Link.l1 = "누가 당신을 공격했고, 왜 그런 짓을 했는지 짐작가는 바가 있습니까?";
			Link.l1.go = "GS_Portman_2";
			DelLandQuestMark(npchar);
		break;
		
		case "GS_Portman_2":
			dialog.text = "나... 나는 그가 누군지 몰라! 어디서 왔는지도, 왜 나를 공격했는지도 몰라. 하지만 한 가지는 분명해 — 그는 나를 죽이려 했어. 그리고 지금... 지금 나는 그 놈의 죽음을 똑같이 갈망하고 있어! 내 말 이해하겠나?\n그러니 쓸데없는 질문은 집어치워. 네 호기심 따위 내겐 아무 의미 없어 — 지금 필요한 건 행동뿐이야. 그 놈의 목에 이백 두블론을 걸겠어, 그게 내 값이야. 사냥을 시작하든가, 아니면 내 시간 낭비하지 마.";
			Link.l1 = "두려움과 분노가 그대의 이성을 흐린다는 것, 그리고 그 말투도 이해하고 넘어가겠소. 하지만 정신 좀 차리시오. 그대 문제를 해결하겠다고 줄 선 사람은 없어 보이니, 흥분은 가라앉히시오. 이백 두블룬이면 괜찮소. 하지만 내가 이 일을 맡기 전에 모든 것을 알아야 하오.";
			Link.l1.go = "GS_Portman_3";
			Link.l2 = "네 말은 허튼소리일 뿐이고, 아무런 단서도 없군. 정글에서 정체도 모르는 사람을 찾는 건 건초 더미에서 바늘 찾기나 다름없지. 쓸데없는 수색에 내 시간을 낭비하지 않겠다. 행운을 빌지. 분명 필요할 테니까.";
			Link.l2.go = "GS_Portman_End";
		break;
		
		case "GS_Portman_End":
			DialogExit();
			CloseQuestHeader("GS");
			DeleteAttribute(pchar, "questTemp.GS_Portman");
		break;
		
		case "GS_Portman_3":
			dialog.text = "아으... 용서해 주시오, "+GetAddress_Form(NPChar)+", 내 신경이 곤두서 있소... 도대체 무엇을 알고 싶은 것이오?";
			Link.l1 = "그를 식별할 만한 특징을 봤소? 혼자였소, 아니면 더 힘 있는 자가 뒤를 봐주고 있었소? 더 많이 말해 줄수록, 더 빨리 편히 잠들 수 있을 것이오.";
			Link.l1.go = "GS_Portman_4";
		break;
		
		case "GS_Portman_4":
			dialog.text = "무슨 적이란 말이오?! 나는 원수도 없소! 지금까지 한 번도 없었소! 내가 대낮 한복판 거리에서 죽을 만한 짓을 한 적도 없소\n그 악당... 그냥 이 식민지 마을 어디에나 있는 불만 많은 미치광이일 뿐이오\n어디서 찾아야 하느냐면... 내 생각엔 그자가 정글에 숨어 있을 거요. 저 저주받은 숲에서는 사라지기 쉽지만, 분명 동굴이나 만으로 갈 거요 — 거기가 더 숨기 쉽거든\n생김새라면, 얼굴은 스카프로 가렸고, 머리에는 모자를 썼으며, 무기는 국왕 친위대보다 더 많이 들고 있었소. 그 외엔 볼 틈도 없었소.";
			Link.l1 = "뭐, 많진 않지만 수색을 시작하기엔 충분하군. 바로 출발하지. 그 금은 잘 챙겨 두시오 — 곧 돌아올 테니.";
			Link.l1.go = "GS_Portman_5";
		break;
		
		case "GS_Portman_5":
			DialogExit();
			AddDialogExitQuestFunction("GS_Portman_5");
		break;
		
		case "GS_Portman_6":
			dialog.text = "훌륭하군, "+GetFullName(pchar)+"! 정말 훌륭하군! 그대의 실력은 누구도 따라올 수 없음을 증명했소. 여기 보상이 있소 – 이백 두블룬이오. 부디, 받아주시오!";
			Link.l1 = "감사하오! 그런데 자네, 혹시 그 살인범이 자네의 예전 의뢰인 중 누군가에게 고용된 것이라고 의심할 만한 이유가 있나?";
			Link.l1.go = "GS_Portman_7";
			AddItems(pchar, "gold_dublon", 200);
			DelLandQuestMark(npchar);
		break;
		
		case "GS_Portman_7":
			dialog.text = "예전 고객들?.. 무슨 헛소리요!... 나는 정직한 사람이고, 내 거래는 언제나 떳떳했소! 하지만 자네가 나를 도왔으니, 한 가지 알려주겠네. 얼마 전 해적들이 나를 찾아왔지\n상인선에 대한 정보를 주면 돈을 주겠다고 하더군. 나는 거절했고, 그놈들은 협박과 저주를 퍼붓다가 쫓기듯 나갔소. 암살자도 그자들의 짓이라 생각하오. 저놈들은 거절을 결코 가볍게 여기지 않지.";
			Link.l1 = "그렇다면 몸조심하게. 이 '해적'들이 또 얼마나 많은 용병 칼잡이들을 보낼지 누가 알겠는가?\n이만 실례하겠네 — 의무가 날 부르니.";
			Link.l1.go = "GS_Portman_8";
		break;
		
		case "GS_Portman_8":
			dialog.text = "잠깐만요, 선장님. 다시 한 번 감사 인사를 드리고 싶소. 금화 이상의 은혜를 입으셨소. 내가 이곳 항구장으로 있는 한, 선장님의 어떤 배든 얼마든지 여기 정박해도 정박료를 50퍼센트 할인해 드리겠소. 어떻소?";
			Link.l1 = "정말 후한 제안이군요! 다시 한 번 감사드립니다!";
			Link.l1.go = "GS_Portman_9";
		break;
		
		case "GS_Portman_9":
			dialog.text = "다시 한 번 당신의 노고에 감사드리오. 중요한 일에만 집중한다면 오늘처럼 앞으로도 당신의 일이 번창할 것이라 확신하오. 안녕히 가시오, 선장.";
			Link.l1 = "안녕히 가십시오.";
			Link.l1.go = "GS_Portman_10";
		break;
		
		case "GS_Portman_10":
			DialogExit();
			AddDialogExitQuestFunction("GS_Portman_10");
		break;
		//<-- Грани справедливости
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

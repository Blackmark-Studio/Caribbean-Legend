// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	bool bOk;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("어서 말해, 뭐 원하는가?","방금 그 얘기를 하고 있었소. 당신이 잊은 모양이군...","오늘만 세 번째로 이 질문을 꺼내는군...","이봐, 여긴 상점이야. 사람들은 여기서 물건을 사 간다네. 나를 방해하지 말게!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("있잖아, "+NPChar.name+", 다음 기회에.","맞아요, 무슨 이유에선지 잊고 있었군요...","그래, 정말로 이번이 세 번째야...","흠, 나는 안 하겠어...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				link.l1 = "들으시오, "+npchar.name+", 최근에 이슬라 테소로에서 미겔 디초소를 본 적 있소?";
				link.l1.go = "tieyasal";
			}
			// Addon 2016-1 Jason пиратскаЯ линейка
			if(CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "pasq_start")
			{
				link.l1 = ""+npchar.name+", 나는 마커스 타이렉스를 대신해 왔소. 그가 당신이 일을 맡길 사람이 필요하다고 하더군.";
				link.l1.go = "mtraxx";
			}
			if(CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "pasq_win")
			{
				link.l1 = ""+npchar.name+", 'Rosbohom'이 발견되어 포획되었습니다. 하역과 물품 계수를 시작할까요?";
				link.l1.go = "mtraxx_5";
			}
		break;
				
		// город майя
		case "tieyasal":
			dialog.text = "네, 맞아요. 그가 여기서 자기 배에 쓸 보급품을 샀습니다. 참고로, 아주 최근 일이에요. 며칠 차이로 서로 스쳤다 해도 과언이 아니죠. 그런데 아직 이 정착지에 있을지도 몰라요. 나는 남을 염탐하는 사람이 아니오. 좀 더 수소문해 보시오, 어쩌면 당신의 돈을 찾을 수 있을지도 모르니까.";
			link.l1 = "알겠소. 정보 고맙소!";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			DialogExit();
			npchar.quest.tieyasal = "true";
		break;
		
		// Addon 2016-1 Jason пиратскаЯ линейка
		case "mtraxx":
			pchar.quest.Mtraxx_PasqualeLate.over = "yes";
            dialog.text = "정확합니다! 제때 도착해서 다행이오. 이제 본론을 말씀드리겠소...";
			link.l1 = "귀 기울여 듣고 있소.";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
			string sTemp = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.questTemp.Mtraxx.Crdn.Ship), "Name")));
            dialog.text = "지금 이 순간에 "+sTemp+", 'Rosbohom'이라는 네덜란드 선박이 호위선 한 척과 함께 우리 해역에 들어오고 있소. 에보니 목재를 가득 실었으며, 윌렘스타드에서 출항해 다른 호위선과 합류하여 유럽까지 안전하게 항해하려는 것이오. 어느 항로를 택할지는 모르겠으나, 신트마르턴을 경유할지 에스파뇰을 경유할지 알 수 없지만, 그들의 합류 지점 좌표는 알고 있소\n그곳에서 네덜란드 배를 찾아 상인을 나포하고, 화물을 내게 가져오시오. 화물이 도착하는 즉시 대가를 지불하겠소.";
			link.l1 = "알겠습니다. 시간과 장소는?";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
			int i = sti(pchar.questTemp.Mtraxx.Crdn.minN2)-10;
			int n = sti(pchar.questTemp.Mtraxx.Crdn.minW2)-10;
            dialog.text = ""+sti(pchar.questTemp.Mtraxx.Crdn.degN)+" "+i+" 북쪽과 "+sti(pchar.questTemp.Mtraxx.Crdn.degW)+" "+n+" 서쪽이오. 분명 이슬라 테소로의 남쪽이나 남서쪽 어딘가일 것이오. 나는 이런 일에 서툴러서, 뱃사람도 아니오. 하지만 그대는 다르지. 일을 끝내려면 약 닷새 정도 시간이 있소.";
			link.l1 = "알겠소... 이해했소. 그럼 지체할 시간 없군!";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = "행운을 빕니다, 선장님. 당신과 화물을 기다리고 있겠습니다.";
			link.l1 = "...";
			link.l1.go = "mtraxx_4";
		break;
		
		case "mtraxx_4":
           DialogExit();
		   pchar.questTemp.Mtraxx = "pasq_convoy";
		   i = sti(pchar.questTemp.Mtraxx.Crdn.minN2)-10;
           n = sti(pchar.questTemp.Mtraxx.Crdn.minW2)-10;
		   AddQuestRecord("Roger_4", "3");
		   AddQuestUserData("Roger_4", "sShip", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.questTemp.Mtraxx.Crdn.Ship), "Name")+ "Gen")));
		   AddQuestUserData("Roger_4", "sdegN", sti(pchar.questTemp.Mtraxx.Crdn.degN));
		   AddQuestUserData("Roger_4", "sminN", i);
		   AddQuestUserData("Roger_4", "sdegW", sti(pchar.questTemp.Mtraxx.Crdn.degW));
		   AddQuestUserData("Roger_4", "sminW", n);
		   SetFunctionTimerCondition("Mtraxx_PasqualeTimeConvoy", 0, 0, 6, false);
		   SetFunctionTimerCondition("Mtraxx_PasqualeConvoyOver", 0, 0, 7, false);
		break;
		
		case "mtraxx_5":
			iTotalTemp = GetSquadronGoods(pchar, GOOD_EBONY);
			if (iTotalTemp < 1)
			{
				dialog.text = "장난하나, 젊은이? 네 화물창엔 흑단 한 조각도 없잖아! 이건 뻔뻔한 사기지! 당장 나가! 이 일은 마르쿠스에게 알릴 거다! 어서 꺼져!!!";
				link.l1 = "흠...";
				link.l1.go = "mtraxx_6";
				break;
			}
			if (iTotalTemp < makeint(sti(pchar.questTemp.Mtraxx.Crdn.Ebony)/4))
			{
				dialog.text = "장난하냐, 이 녀석? 네 화물칸엔 흑단 조각 몇 개밖에 없잖아! 이건 말도 안 되는 사기지! 당장 꺼져! 마르쿠스에게 이 사실을 알릴 거다! 나가!!!";
				link.l1 = "흠...";
				link.l1.go = "mtraxx_6";
				break;
			}
			if (iTotalTemp < sti(pchar.questTemp.Mtraxx.Crdn.Ebony)-20)
			{
				dialog.text = "로스보홈호에는 적어도 "+FindRussianQtyString(sti(pchar.questTemp.Mtraxx.Crdn.Ebony))+" 흑단이군. 왜 더 적게 가져왔소?";
				link.l1 = "음... 있잖아, 싸움 중에 일부는 어쩔 수 없이 버려야 했어. 게다가 쥐들까지, 젠장할 놈들...";
				link.l1.go = "mtraxx_7";
				break;
			}
            dialog.text = "좋소. 얼마나 가지고 있소? "+FindRussianQtyString(iTotalTemp)+"? 훌륭하군! 한 점당 150페소를 지불하겠소.";
			link.l1 = "에잇 150개라고? 흑단은 훨씬 비싸겠지.";
			link.l1.go = "mtraxx_10";
		break;
		
		case "mtraxx_6":
           DialogExit();
		   pchar.questTemp.Mtraxx = "pasq_angry";
		   DoQuestReloadToLocation("Pirates_town", "reload", "reload6", "");
		   AddQuestRecord("Roger_4", "8");
		   CloseQuestHeader("Roger_4");
		   QuestSetCurrentNode("Terrax", "mtraxx_34");
		break;
		
		case "mtraxx_7":
            dialog.text = "쥐라니? 허허... 뭐, 알겠다. 한 마리당 100페소씩 받고 보내주지.";
			link.l1 = "100페소뿐이라고? 대낮에 강도질이군!";
			link.l1.go = "mtraxx_8";
		break;
		
		case "mtraxx_8":
			AddMoneyToCharacter(pchar, iTotalTemp*100);
			RemoveCharacterGoods(pchar, GOOD_EBONY, iTotalTemp);
            dialog.text = "강도질이야 선장님의 업이지만, 나는 그저 평범한 상인일 뿐이오. 돈을 가져가시오, 더 이상 언쟁하지 맙시다. 이미 내 화물 일부를 다른 곳에 팔아 꽤 많은 돈을 벌었으니.";
			link.l1 = "그럼 지옥이나 가라!";
			link.l1.go = "mtraxx_9";
		break;
		
		case "mtraxx_9":
           DialogExit();
		   pchar.questTemp.Mtraxx = "pasq_fail";
		   AddQuestRecord("Roger_4", "8");
		   CloseQuestHeader("Roger_4");
		   QuestSetCurrentNode("Terrax", "mtraxx_34");
		break;
		
		case "mtraxx_10":
            dialog.text = "그리고 당신 말이 맞소, 선장. 하지만 먼저, 훔친 물건을 팔아보고 다른 상인들이 얼마를 주는지 직접 확인해 보시오. 내가 제시하는 가격이 아주 높소. 둘째, 그건 내 정보였소. 자네 혼자였으면 그 대상단을 절대 찾지 못했을 거요. 게다가 그 대상단에는 다른 귀중품과 물건들도 있었지만, 나는 그것들에 대해선 아무 말도 하지 않겠소. 셋째, 내가 마르쿠스 타이렉스의 눈에 자네에게 최고의 신용을 보장해 줄 것이니, 그건 정말 큰 가치가 있소. 마지막으로, 넷째, 가난한 상인도 어떻게든 살아가야 하지 않겠소.";
			link.l1 = "이런! 이런 논리에 맞서선 물러나야겠군 "+npchar.name+". 계산을 해봅시다.";
			link.l1.go = "mtraxx_11";
		break;
		
		case "mtraxx_11":
			AddMoneyToCharacter(pchar, iTotalTemp*150);
			RemoveCharacterGoods(pchar, GOOD_EBONY, iTotalTemp);
            dialog.text = "훌륭하군. 돈을 가져가시오. 즐거운 거래였소. 가끔 내 상점도 들러 보시게. 바다에서 행운이 함께하길 바라오!";
			link.l1 = "그리고 그대의 장사에서는...";
			link.l1.go = "mtraxx_12";
		break;
		
		case "mtraxx_12":
           DialogExit();
		   pchar.questTemp.Mtraxx = "pasq_complete";
		   AddQuestRecord("Roger_4", "9");
		   pchar.quest.mtr_pasq_fin.win_condition.l1 = "location";
		   pchar.quest.mtr_pasq_fin.win_condition.l1.location = "Pirates_town";
		   pchar.quest.mtr_pasq_fin.function = "Mtraxx_PasqualeJeffry";
		   bDisableFastReload = true;
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}

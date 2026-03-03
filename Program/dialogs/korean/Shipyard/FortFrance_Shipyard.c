// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문이 있소?","무엇을 도와드릴까요?"),"조금 전에 나한테 뭔가 물어보려고 했었지...","내 조선소나 이 마을 어디에서도 그렇게 호기심 많은 사람들은 본 적이 없어.","뭘 그렇게 캐묻는 거야? 내 일은 배를 만드는 거다. 그 일이나 처리하자.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내 마음이 바뀌었어...","지금은 할 말이 없어."),"으음, 내 기억이 다 어디로 갔지...","흠, 그래...","계속해...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Addon-2016 Jason ”ЊЉ-Њартиника
			if (CheckAttribute(pchar, "questTemp.FMQM") && pchar.questTemp.FMQM == "begin")
            {
                link.l1 = "네 부하가 당신이 나를 보자고 했다고 하더군. 무슨 일이든 들을 준비가 되어 있소.";
                link.l1.go = "FMQM";
            }
			if (CheckAttribute(pchar, "questTemp.FMQM") && pchar.questTemp.FMQM == "oil" && GetSquadronGoods(pchar, GOOD_OIL) >= 50)
            {
                link.l1 = "일을 끝냈다. "+FindRussianQtyString(GetSquadronGoods(pchar,GOOD_OIL))+" 내 화물창에 송진 통이 있다.";
                link.l1.go = "FMQM_9";
            }
		break;
		
		// Addon-2016 Jason ”ЊЉ-Њартиника
		case "FMQM":
			pchar.quest.FMQM_Denial.over = "yes";
			dialog.text = "그래, 그래, 선장님 "+GetFullName(pchar)+". 당신 배가 우리 항구에 들어오는 걸 보고 즉시 하인을 보냈소. 그럼 바로 본론으로 들어가지. 당신은 신참이지만, 이미 노련한 선원이 되었고 행운도 따르고 있다더군. 그래서 당신에게 사업 제안을 하려고 하오.";
			link.l1 = "흥미롭군! 계속 말해봐.";
			link.l1.go = "FMQM_1";
			DelLandQuestMark(npchar);
		break;
		
		case "FMQM_1":
			dialog.text = "스페인 놈들이 트리니다드 섬에서 만든 특별한 송진에 대해 들어본 적 있나? 이건 전략적으로 아주 귀한 자원이라 배의 선체를 강화하는 데 쓰이지. 스페인 놈들이 전부 해군에만 송진을 공급해서, 한 통 한 통 값이 만만치 않아. 모든 식민지 당국이 이 물건 거래를 엄격하게 통제하고 있지. 쉽게 말해, 완전 밀수품이란 소리야.  
나는 이 송진이 특별 주문에 꼭 필요하다. 물론 우리 창고에는 없고, 우리 군대 창고에도 없지—아니, 팔기 싫어서 그런 걸 수도 있겠지. 사실 그건 중요하지 않아. 중요한 건 내가 이 송진이 필요하고, 어디서 구할 수 있는지도 안다는 거야. 필요한 건 그냥, 승선에 거리낌 없는 선장 한 명뿐이지.";
			link.l1 = "네 말이 뭔지 이제 좀 알 것 같군...";
			link.l1.go = "FMQM_2";
		break;
		
		case "FMQM_2":
			dialog.text = "훌륭하군. 이제 잘 들어, 작은 무역 호송대가 트리니다드 근처, 정확히는 산호세 항구에서 목격됐어. 그 중 한 척이 내가 절실히 필요한 좋은 송진을 싣고 있지. 우리 나라의 적들을 약탈하는 게 마음에 든다면 더 자세히 이야기해 주지. 어때, 할 생각 있나?";
			link.l1 = "당신 제안이 마음에 드오. 한번 시도해 볼 준비가 되었소.";
			link.l1.go = "FMQM_3";
			link.l2 = "사양하겠소, 나리. 내 배와 선원들이 지금 상태가 좋지 않소.";
			link.l2.go = "FMQM_exit";
		break;
		
		case "FMQM_exit":
			dialog.text = "좋소, 원하는 대로 하는 건 선장님의 권리이니. 시간 뺏어서 미안하오, 선장님.";
			link.l1 = "안녕히 가십시오.";
			link.l1.go = "FMQM_exit_1";
		break;
		
		case "FMQM_exit_1":
			DialogExit();
			pchar.questTemp.FMQM = "fail";
			AddQuestRecord("FMQ_Martinique", "3");
			CloseQuestHeader("FMQ_Martinique");
		break;
		
		case "FMQM_3":
			string sTemp = "barquentine";
			if (MOD_SKILL_ENEMY_RATE < 7) sTemp = "barque";// Addon 2016-1 Jason пиратскаЯ линейка
			dialog.text = "그럼 잘 들어. 호송대는 배 세 척으로 이루어져 있고, 송진은 다른 화물들과 함께 한 척에 실려 있을 거야\n "+sTemp+" '벤세초'라고 불린다. 이게 네 주요 목표다. 전에 말했듯이, 스페인 놈들은 산호세-트리니다드에서 산후안-푸에르토리코로 항해 중이다.\n내일 출항할 거니, 어디서 공격할지는 네가 자유롭게 정해라.";
			link.l1 = "알겠소. 보상은 어떻게 되지?";
			link.l1.go = "FMQM_4";
		break;
		
		case "FMQM_4":
			dialog.text = "내가 관심 있는 건 송진뿐이네. 한 통당 금화 15두블룬을 지불하지. 내 정보에 따르면 '벤세초'에는 약 백 통 정도 실려 있다네.";
			link.l1 = "이런 맙소사! 그거 꽤 큰 돈이군!";
			link.l1.go = "FMQM_5";
		break;
		
		case "FMQM_5":
			dialog.text = "그래. 이 물건은 아주 비싸고 희귀하다고 이미 말했잖아.";
			link.l1 = "너는 이것도 밀수품이라고 했지.";
			link.l1.go = "FMQM_6";
		break;
		
		case "FMQM_6":
			dialog.text = "걱정 마시오, 그걸 상점이나 밀수업자에게 가져갈 필요는 없을 것이오. 일이 끝나면 나를 찾아오시오. 네 배를 내 조선소에 정박시키고, 밤에 몰래 모든 화물을 내릴 것이오. 아무도 눈치채지 못할 거요.";
			link.l1 = "나보다 한 발 앞서 생각하는군, 주인장. 좋아. 그럼 시간 낭비하지 말자고. 곧바로 출항 준비하러 가겠다.";
			link.l1.go = "FMQM_7";
		break;
		
		case "FMQM_7":
			dialog.text = "행운을 빕니다, 선장님.";
			link.l1 = "...";
			link.l1.go = "FMQM_8";
		break;
		
		case "FMQM_8":
			DialogExit();
			pchar.questTemp.FMQM = "convoy";
			AddQuestRecord("FMQ_Martinique", "4");
			SetFunctionTimerCondition("FMQM_ConvoyStart", 0, 0, 1, false);
		break;
		
		case "FMQM_9":
			dialog.text = "훌륭하군! 전에 약속한 대로 네 배를 도크에 넣자. 오늘 밤 거기서 배를 하역할 거야.\n네 배로 돌아가 있어. 내가 돈을 준비할 테니.";
			link.l1 = "해보자.";
			link.l1.go = "FMQM_10";
			DelLandQuestMark(npchar);
		break;
		
		case "FMQM_10":
			pchar.quest.FMQM_Late.over = "yes";
			DialogExit();
			InterfaceStates.Buttons.Save.enable = false;
			chrDisableReloadToLocation = true;
			pchar.GenQuest.FrameLockEsc = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
			pchar.questTemp.FMQM = "remove_oil";
			pchar.questTemp.FMQM.Oil = "true";
			pchar.questTemp.FMQM.Qty = GetSquadronGoods(pchar, GOOD_OIL);
			DoQuestFunctionDelay("FMQM_WaitTime", 1.0);
			RemoveCharacterGoods(pchar, GOOD_OIL, GetSquadronGoods(pchar, GOOD_OIL));
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

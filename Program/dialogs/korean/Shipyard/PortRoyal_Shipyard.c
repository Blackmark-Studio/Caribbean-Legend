// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문이 있소?","무엇을 도와드릴까요?"),"조금 전에 나한테 뭔가 물어보려고 했었지...","내 조선소나 이 마을 어디에서도 그렇게 호기심 많은 사람들은 본 적이 없소.","질문이 왜 이렇게 많아? 내 일은 배를 만드는 거야. 그 일부터 처리하자.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내 마음이 바뀌었어...","지금은 할 말이 없어."),"으음, 내 기억이 다 어디로 갔지...","흠, 그래...","계속해...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Addon 2016-1 Jason пиратскаЯ линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx"))
            {
				if (pchar.questTemp.Mtraxx == "silk_2" || pchar.questTemp.Mtraxx == "silk_3")
				{
					link.l1 = "이 조선소가 배의 항해 속도를 높이는 데 특화되어 있다고 들었소. 실크 돛감이 필요한데, 아주 희귀하지. 혹시... 이 일에 대해 이야기해 볼 생각이 있소?";
					link.l1.go = "mtraxx";
				}
			}
			if (CheckAttribute(npchar, "quest.upgradeship")) {
				link.l2 = "나는 미스 맥아더에게서 왔어, 그게...";
				link.l2.go = "helen_upgradeship";
			}
			
			if (CheckAttribute(npchar, "quest.upgradeship.money") && HelenCanUpgrade()) {
				link.l2 = "배 수리 작업을 시작하라!";
				link.l2.go = "helen_upgradeship_money";
			}
		break;
		
		// Addon 2016-1 Jason пиратскаЯ линейка
		case "mtraxx":
            dialog.text = "좀 더 분명히 말해 줄 수 있겠나, 젊은이? 대체 무슨 일로 여기 온 거지? 배를 개조하려는 거라면, 바로 본론으로 들어가자꾸나.";
			link.l1 = "완전히 그렇지는 않소. 그대가 하는 일에는 상점에서 쉽게 구할 수 없는 물자가 필요하오. 내가 그대가 필요로 할 만한 자재를 똑같이 제공해 주고 싶소.";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
            dialog.text = "흠, 흠... 자네, 이 식민지의 당국만이 이런 전략 물자를 다룰 수 있다는 걸 알고 있나? 자네가 직접 가져온 비단을 내게 맡겨서 배를 개조하는 데 쓰는 건 괜찮지만, 비단을 파는 건 엄격히 금지되어 있네. 내게서 사는 것도 마찬가지야—그런 행위는 무거운 벌금이 부과될 걸세.";
			link.l1 = "음, 여기는 상점도 아니고 세관도 아니오...";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = "나는 모든 비단 돛천을 직접 거래처에서 들여오거나, 총독의 특별 허가를 받아 소량만 구매하지. 더 이상 궁금한 게 없으면, 이제 내 일로 돌아가게 해주게.";
			link.l1 = "흠... 알겠습니다. 좋은 하루 보내십시오, 나리.";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            DialogExit();
			AddQuestRecord("Roger_2", "5");
			pchar.questTemp.Mtraxx = "silk_4";
		break;
		
		case "helen_upgradeship":
			dialog.text = "오, 알지! 운이 좋으시군, 선장님. 선박을 완전히 개조하려는 건가? 모든 건 우리가 맡아주지. 우리 조선소는 플리머스에 있는 곳들과 견줄 만하니까!";
			link.l1 = "이게 공짜 서비스는 아니겠지?";
			link.l1.go = "helen_upgradeship_1";
		break;
		
		case "helen_upgradeship_1":
			dialog.text = "물론입니다, 선장님, 이런 서비스는 크롬웰이라 해도 공짜는 아닙니다! 하지만 저는 약속을 지키는 사람이니 돈만 받겠습니다 – 밀수품을 운반할 필요는 없을 겁니다.";
			link.l1 = "이해했소. 얼마요?";
			link.l1.go = "helen_upgradeship_2";
		break;
		
		case "helen_upgradeship_2":
			dialog.text = "당신의 기함 크기에 따라 다릅니다, 선장님. 1등급 함선은 오천 두블룬이 들고, 5등급 함선은 천 두블룬이면 됩니다.";
			link.l1 = "알겠소, 결정하면 당신에게 오겠소.";
			link.l1.go = "exit";
			
			npchar.quest.upgradeship.money = true;
		break;
		
		case "helen_upgradeship_money":
			dialog.text = "좋아, 이제 필요한 건 다 모였군. 그럼 바로 작업 시작하지.";
			link.l1 = "기다리고 있소.";
			link.l1.go = "helen_upgradeship_money_1";
			
			iTemp = GetCharacterShipType(pchar);
			sld = GetRealShip(iTemp);
			iTemp = (7 - sti(sld.class)) * 1000;
			RemoveDublonsFromPCharTotal(iTemp);
		break;
		
		case "helen_upgradeship_money_1":
			AddTimeToCurrent(6, 30);
			dialog.text = "... 이걸로 끝인 것 같군... 품질은 보장하지.";
			link.l1 = "고마워! 내가 직접 확인해 볼게.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenUpgradeShip2");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

bool HelenCanUpgrade() {
	int shipIndex = GetCharacterShipType(pchar);
	if (shipIndex == SHIP_NOTUSED) {
		return false;
	}
	
	sld = GetRealShip(shipIndex);
	if (sti(sld.class) == 7) {
		return false;
	}
	
	int cost = (7 - sti(sld.class)) * 1000;
	return (PCharDublonsTotal() >= cost);
}

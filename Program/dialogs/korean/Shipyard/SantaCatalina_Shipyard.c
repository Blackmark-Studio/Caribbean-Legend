// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문이 있소?","무엇을 도와드릴까요?"),"조금 전에 나한테 뭔가 물어보려고 했었지...","이 조선소나 이 마을 어디에서도 그렇게 호기심 많은 사람들은 처음 봤소.","질문이 왜 이렇게 많아? 내 일은 배를 만드는 거야. 그 일이나 하자.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내 마음이 바뀌었어...","지금은 할 말이 없어."),"으음, 내 기억이 다 어디로 갔지...","흠, 그래...","계속해...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		
		case "helendrinking_buy_rainbow":
			dialog.text = "... 훌륭한 선택이오, 나리. 그럼, 거래를 하겠소?";
			link.l1 = "예-예! 건배! 포장해서 부두로 보내라. 그리고 서둘러라, 거리에서 숙녀가 나를 기다리고 있으니!";
			link.l1.go = "helendrinking_buy_rainbow_1";
			locCameraFromToPos(0.36, 1.86, 1.15, true, 2.06, -0.20, -4.38);
		break;
		
		case "helendrinking_buy_rainbow_1":
			dialog.text = "전부 해서 오만 실버입니다, 나리.";
			if (sti(pchar.money) >= 55000) {
				link.l1 = "얼, 얼마라고 했지? 오, 오만? 그래, 직접 세어 봐! 그리고 팁으로 오천 더 가져가. 가자!";
				link.l1.go = "helendrinking_buy_rainbow_yes";
			}
			
			link.l2 = "아니, 아니야, 내가 부자, 히익! ...놈이긴 해도 그 돈으론 안 사. 안 돼, 나리! 잘 가라, 뱃사공.";
			link.l2.go = "helendrinking_buy_rainbow_no";
		break;
		
		case "helendrinking_buy_rainbow_yes":
			dialog.text = "감사합니다, 나리. 그 배가 잘 봉사하길 바랍니다!";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "First time";
			
			AddMoneyToCharacter(pchar, -55000);
			pchar.questTemp.HelenDrinking.BoughtRainbow = true;
			
			AddDialogExitQuestFunction("HelenDrinking_GoToPerlas");
		break;
		
		case "helendrinking_buy_rainbow_no":
			dialog.text = "그래, 꺼져라, 부잣집 도련님. 우리는 세 시간 전에 문 닫았다.";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "First time";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToPerlas");
		break;
		
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문이 있소?","무엇을 도와드릴까요?"),"조금 전에 나한테 뭔가 물어보려고 했었지...","이 조선소나 이 마을 어디에서도 그렇게 호기심 많은 사람들은 처음 봤소.","왜 그렇게 질문이 많아? 내 일은 배를 만드는 거야. 그 일부터 처리하자.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내 마음이 바뀌었어...","지금은 할 말이 없어."),"으음, 내 기억이 다 어디로 갔지...","흠, 그래...","계속해...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "이봐, 요즘 여기 조아킴 메리만이라는 남자가 온 적 있나? 중년의 나리인데, 포르투갈 사람이고, 콧수염에 염소수염, 눈빛이 날카로운 자야. 혹시 배를 사려고 했을지도 모르지?";
				link.l1.go = "caleuche";
			}
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "아니오, 나리. 그런 손님은 본 적 없습니다.";
			link.l1 = "알겠소. 안타깝군. 그럼 계속해서 찾아보겠소...";
			link.l1.go = "exit";
			npchar.quest.caleuche = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문이 있으십니까?","무엇을 도와드릴까요?"),"그 질문을 얼마 전에 나에게 이미 하셨지 않습니까...","그래, 맞지... 또 빙빙 돌고 있는 거야?","이봐, 여기서 재정은 내가 맡고 있어, 질문엔 답하지 않아...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내 마음이 바뀌었소...","지금은 할 말이 없소."),"으음, 내 기억이 다 어디로 갔지...","맞췄군, 미안하네...","알겠습니다...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "이봐, 여기 요아킴 메리만이라는 남자가 온 적 있나? 중년의 나리인데, 포르투갈인이고, 콧수염에 염소수염, 날카로운 눈을 가진 사람 말이야. 혹시 대출을 받으려고 했을지도 모르지?";
				link.l1.go = "caleuche";
			}
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "유감이지만 도와줄 수 없네, 젊은이. 누구에 대해 말하는지 전혀 모르겠군.";
			link.l1 = "알겠습니다. 아쉽군요. 계속해서 찾아보겠습니다...";
			link.l1.go = "exit";
			npchar.quest.caleuche = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

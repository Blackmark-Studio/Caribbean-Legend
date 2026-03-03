// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문이 있소?","무엇을 도와드릴까요?"),"조금 전에 나한테 뭔가 물어보려고 했었지...","내 조선소나 이 마을 어디에서도 그렇게 호기심 많은 사람들은 본 적이 없어.","질문이 왜 이렇게 많아? 내 일은 배를 만드는 거야. 그 일부터 처리하자.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내 마음이 바뀌었어...","지금은 할 말이 없어."),"음, 내 기억이 다 어디로 갔지...","흠, 그래...","계속해...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatPortobello")
            {
                link.l1 = "이봐, 프랑수아 곤티에라는 이름의 사략선장이 혹시 너한테 들른 적 없나? 최근에 포르토 벨로에 있었다는 건 알고 있어.";
                link.l1.go = "Portobello_ratS_1";
            }
		break;
		
		case "Portobello_ratS_1":
			dialog.text = "그랬소. 내게서 코르벳을 구입하고 곧바로 바다로 떠났소.";
			link.l1 = "감사합니다! 그리고 그가 어디로 떠났는지 알고 있습니까?";
			link.l1.go = "Portobello_ratS_2";
		break;
			
		case "Portobello_ratS_2":
			dialog.text = "아니, 친구, 전혀 모르겠어. 나는 배를 고치고 팔 뿐이지, 어디로 가는지까지는 신경 안 써. 내 알 바 아니거든.";
			link.l1 = "그렇다면, 감사하네... 어디로 갔는지 알아보자고...";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "FindRatPortobello_1";
			AddQuestRecord("Slavetrader", "21_2");
		break;
			
			
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

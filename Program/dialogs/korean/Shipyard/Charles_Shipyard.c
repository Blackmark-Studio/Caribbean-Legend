// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문이 있소?","무엇을 도와드릴까요?"),"조금 전에 나한테 뭔가 물어보려고 했지...","이 조선소나 이 마을 어디에서도 그렇게 호기심 많은 사람들은 본 적이 없어.","왜 그렇게 질문이 많아? 내 일은 배를 만드는 거야. 그 일부터 처리하자.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내 마음이 바뀌었어...","지금은 할 말이 없어."),"음, 내 기억이 다 어디로 갔지...","음, 그래...","계속해...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Addon 2016-1 Jason пиратскаЯ линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_2")
            {
                link.l1 = "이봐, 주인장, 여기서 배를 짓지? .. 그리고 돛도 갈아주고... 혹시 말인데... 더 좋은 돛천 재질에 대해 생각해본 적 있어?";
                link.l1.go = "mtraxx";
			}
		break;
		
		// Addon 2016-1 Jason пиратскаЯ линейка
		case "mtraxx":
            dialog.text = "수수께끼처럼 말하는군, 나리... 솔직하게 말해, 무슨 일로 왔나? 걱정할 것 없어, 나는 서류나 만지는 사람이 아니고 여긴 세관도 아니야.";
			link.l1 = "아, 우리가 같은 생각이라니 다행이군! 비단 돛천이지, 나리. 내가 알기로는, 속도가 중요하다면 이것보다 더 좋은 돛감은 없어.";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
            dialog.text = "속도뿐만 아니라 바람을 맞서 항해하는 능력도 뛰어나지. 자네가 배 실크를 팔려고 하나? 정말 귀한 화물이군. 하지만 문제가 있어. 나는 그걸 생산에 어떻게 써야 할지 전혀 모르겠네. 이해하겠나? 이런 재료는 아주 특별한 능력과 기술이 필요한데, 내겐 그게 없어. 솔직히 말해서, 내 조선소는 전혀 다른 분야에 특화되어 있네. 만약 러시아 차르국에서 온 밧줄을 가져왔다면, 가격 상관없이 모두 샀을 걸세. 우리는 항상 밧줄이 필요하거든. 하지만 배 실크는 여기서 수요가 없어, 미안하네!\n";
			link.l1 = "흠. 알겠소. 시간 내줘서 고맙소, 주인장. 행운을 빌겠소!";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            DialogExit();
			AddQuestRecord("Roger_2", "4");
			pchar.questTemp.Mtraxx = "silk_3";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

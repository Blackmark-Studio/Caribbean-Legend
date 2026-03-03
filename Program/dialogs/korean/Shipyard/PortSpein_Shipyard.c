// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문이 있소?","무엇을 도와드릴까요?"),"조금 전에 나에게 뭔가 물어보려고 했었지...","이 조선소나 이 마을 어디에서도 그렇게 호기심 많은 사람들은 본 적이 없어.","질문이 왜 이렇게 많지? 내 일은 배를 만드는 거야. 그 일이나 하자.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내 마음이 바뀌었어...","지금은 할 말이 없어."),"으음, 내 기억이 다 어디로 갔지...","음, 글쎄...","계속해...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "말해 봐, 후안이라는 이름이 너한테 의미가 있나?";
				link.l1.go = "Consumption";
			}
			if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "나리, 1654년 4월에 미겔 디초소가 지휘하는 프리깃이 여기 있었습니다. 그 후 바로 사라졌지요. 아무것도 기억나지 않으십니까? 혹시 디초소가 수리를 위해 들렀다가 무슨 말을 하지 않았는지...";
				link.l1.go = "guardoftruth";
			}
		break;
		
		//Цена чахотки
		case "Consumption":
			dialog.text = "아니. 아무것도 없어.";
			link.l1 = "좋아. 귀찮게 해서 미안하다...";
			link.l1.go = "exit";
			npchar.quest.Consumption = "true";
		break;
		
		case "guardoftruth":
			dialog.text = "흠. 아니. 그는 수리를 위해 들르지도 않았고 나한테 아무 말도 하지 않았어. 그리고 그런 일이 있었다 해도 기억이 안 나네. 도와줄 수 없어 미안하네, 나리.";
			link.l1 = "알겠어. 고마워, 친구...";
			link.l1.go = "exit";
			npchar.quest.guardoftruth = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

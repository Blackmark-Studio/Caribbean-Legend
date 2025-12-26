// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("모든 소문이 "+GetCityName(npchar.city)+" 항상 대기 중이오. 무엇을 알고 싶으시오?","우리가 방금 그 얘기를 하고 있었지. 네가 잊어버린 모양이군...","오늘만 벌써 세 번째로 이 질문을 꺼내는군...","너, 앵무새처럼 똑같은 말만 반복하고 있잖아...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("있잖아, "+NPChar.name+", 다음에 하자.","그래, 뭔가 이유가 있었는지 내가 까먹었군...","그래, 이번이 정말 세 번째야...","그래...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문이 있습니까?","무엇을 도와드릴까요?"),"얼마 전에 나한테 그 질문을 하려고 했었지...","그래, 맞지... 또 빙빙 돌고 있는 거야?","들으시오, 나는 여기서 재정을 담당하오, 질문에는 답하지 않소...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내 마음이 바뀌었소...","지금은 할 말이 없소."),"으음, 내 기억이 다 어디로 갔지...","짐작하셨군요, 유감입니다...","알겠습니다...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

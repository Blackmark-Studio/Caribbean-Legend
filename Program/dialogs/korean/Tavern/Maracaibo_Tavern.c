// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문이 있소?","무엇을 도와드릴까요, "+GetAddress_Form(NPChar)+"?"),"얼마 전에 나한테 뭔가 물어보려고 했었지, "+GetAddress_Form(NPChar)+"...","오늘 하루 동안, 그 질문을 벌써 세 번째 꺼내는군...","질문이 더 있나 보군?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내 마음이 바뀌었어...","지금은 할 말이 없어."),"음, 내 기억이 다 어디로 갔지...","그래, 정말 이번이 세 번째야...","아니, 무슨 질문이야?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

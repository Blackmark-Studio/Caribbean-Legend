/// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문이 있으십니까?","무엇을 도와드릴까요?"),"얼마 전에 나에게 그 질문을 하려고 했었지...","그래, 맞지... 또 뱅뱅 돌고 있는 거냐?","듣게, 여기서 재정은 내가 맡고 있네, 질문에는 대답하지 않네...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내 마음이 바뀌었소...","지금은 할 말이 없소."),"으음, 내 기억이 다 어디로 갔지...","짐작하셨군요, 유감입니다...","알겠습니다...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

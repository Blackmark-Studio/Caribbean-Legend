// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문이 있으십니까?","무엇을 도와드릴까요?"),"얼마 전에 나에게 그 질문을 하려 했었지...","그래, 맞지... 또 빙빙 돌고 있는 거냐?","이봐, 여기서 재정은 내가 맡고 있어, 질문엔 답하지 않아...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("생각이 바뀌었소...","지금은 할 말이 없습니다."),"음, 내 기억이 다 어디로 갔지...","맞췄군요, 유감이오...","알겠습니다...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

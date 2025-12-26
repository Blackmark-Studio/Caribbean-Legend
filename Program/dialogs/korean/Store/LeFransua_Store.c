// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문이 있습니까?","무엇을 도와드릴까요?"),"얼마 전에 내 가게에서 나에게 질문하려고 했었지...","오늘만 세 번째 질문이오. 나는 쓸데없는 대화가 아니라 장사를 해야 하오...","질문이 더 있나? 대신 거래를 하는 게 어떻겠소?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내 마음이 바뀌었어...","지금은 할 말이 없소."),"그래, 맞아. 내가 해봤지... 가게에 있을 때...","그래, 세 번째 질문이네...","흠, 거래를 할 수도 있겠군...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}

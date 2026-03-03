// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문이 있소?","무엇을 도와드릴까요?"),"얼마 전에 가게에 있을 때 내게 뭔가 물어보려 했었지...","오늘만 세 번째 질문이오. 나는 장사를 해야지, 쓸데없는 대화에 시간을 낭비할 순 없소...","질문이 더 있나? 대신 거래를 하는 게 어떻겠소?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내 마음이 바뀌었어...","지금은 할 말이 없소."),"그래, 맞아. 내가 시도해 봤지... 가게에 있을 때...","그래, 세 번째 질문이네...","흠, 거래를 할 수도 있겠군...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;				
	}
	UnloadSegment(NPChar.FileDialog2);
}

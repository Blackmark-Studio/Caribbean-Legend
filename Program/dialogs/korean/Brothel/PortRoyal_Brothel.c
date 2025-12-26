// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문이오, "+GetSexPhrase("청년","아가씨")+"?","무엇이 필요하신가, "+GetSexPhrase("잘생긴","예쁜이")+"? 물어보시오."),"또 질문이오?","히히, 괜찮으시다면... 질문을 하시겠소...",""+GetSexPhrase("흠, 어째서 직접 미녀를 고르지 않으시오? 점점 그대가 수상해지기 시작하는군...","흠, 어여쁜 아가씨 하나 골라보시는 게 어떠신가요? 유감스럽게도 여기엔 남자아이는 없답니다, 히히...")+"","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("마음이 바뀌었소, 실례하오.","사실, 그냥 됐소..."),"저... 실례지만, 지금은 질문이 없습니다.","맞아요, 벌써 세 번째군요. 실례했습니다.","다음에 뵙지요, 마님.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

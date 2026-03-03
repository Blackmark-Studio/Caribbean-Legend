// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문이오, "+GetSexPhrase("젊은이","아가씨")+"?","무엇이 필요하신가, "+GetSexPhrase("잘생긴","예쁜이")+"? 물어보시오."),"또 질문이오?","히히, 괜찮으시다면... 질문이 있으신가요...",""+GetSexPhrase("흠, 어째서 직접 미인을 고르지 않으시오? 점점 의심이 가기 시작하는데...","흠, 어여쁜 아가씨 한 명 골라보는 게 어떠신가요? 안타깝게도 여기엔 사내아이는 없답니다, 히히...")+"","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("생각이 바뀌었소, 실례하오.","사실, 됐소..."),"저... 미안하오, 지금은 물어볼 것이 없소.","맞아요, 벌써 세 번째군요. 실례했습니다.","다음에 뵙지요, 마님.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

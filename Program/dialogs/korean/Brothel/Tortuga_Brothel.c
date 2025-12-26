// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문이오, "+GetSexPhrase("젊은이","아가씨")+"?","무엇이 필요하신가, "+GetSexPhrase("잘생긴","예쁜이")+"? 물어보시오."),"또 질문이오?","히히, 괜찮으시다면... 질문을 하시지요...",""+GetSexPhrase("흠, 어째서 자네는 스스로 미녀를 고르지 않는 거지? 점점 수상해지기 시작하는군...","흠, 자네도 한 미인을 골라보는 게 어때? 안타깝게도 여기엔 남자애들은 없어, 히히...")+"","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("마음이 바뀌었소, 실례하오.","사실, 그냥 됐소..."),"저... 미안하오, 지금은 질문이 없소.","옳으신 말씀입니다, 벌써 세 번째군요. 실례했습니다.","다음에 뵙지요, 마님.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

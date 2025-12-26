// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문이오?","무엇을 원하시오, "+GetAddress_Form(NPChar)+"?"),"또 질문이군, "+GetAddress_Form(NPChar)+"...","질문이 많군... 거래나 하지,  "+GetAddress_Form(NPChar)+"응?","이봐, 얼마나 더 말할 생각이야?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("지금은 질문이 없소...","죄송하지만, 지금은 드릴 말씀이 없습니다..."),"다시 한 번, 미안하오...","정말 이제 거래할 때가 된 것 같군...","죄송합니다, 거래합시다...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

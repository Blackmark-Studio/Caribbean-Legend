// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문인데?","무엇을 원하시오, "+GetAddress_Form(NPChar)+"?"),"또 질문이군, "+GetAddress_Form(NPChar)+"...","질문이 많군... 거래나 하지,  "+GetAddress_Form(NPChar)+"응?","이봐, 얼마나 오래 말할 생각이야?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("지금은 질문 없어...","죄송하지만, 지금은 드릴 말씀이 없군요..."),"다시 한 번, 미안하오...","정말로 이제 거래할 때가 된 걸까...","죄송합니다, 거래합시다...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Che tipo di domande, "+GetSexPhrase("giovane uomo","signorina")+"?","Di cosa hai bisogno, "+GetSexPhrase("affascinante","bella")+"? Chiedi pure."),"Di nuovo domande?","Hihi, se non ti dispiace - domande...",""+GetSexPhrase("Mmm, perché non scegli una bellezza per te? Sto cominciando ad avere sospetti su di te...","Mh, perché non scegli una bellezza per te? Temo che qui non abbiamo ragazzi, hi-hi...")+"","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea, scusami.","Veramente, non importa..."),"Mi... scuso, non ho domande, per ora.","Hai ragione, è già la terza volta. Mi scuso.","Forse la prossima volta, Madama.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

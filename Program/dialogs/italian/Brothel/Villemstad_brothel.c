// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Qual tipo di domande, "+GetSexPhrase("giovane uomo","giovane signora")+"?","Di cosa hai bisogno, "+GetSexPhrase("affascinante","bella")+"? Chiedi pure."),"Di nuovo domande?","Hihi, se non ti dispiace - domande...",""+GetSexPhrase("Mh, perché non scegli una bellezza per te stesso? Sto iniziando ad avere sospetti su di te...","Mh, perché non scegli una bellezza per te? Temo che qui non abbiamo ragazzi, hihi...")+"","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mi sono ricreduto, mi scuso.","Effettivamente, non importa..."),"Mi... scuso, non ho domande, per ora.","Hai ragione, è già la terza volta. Mi perdoni.","Forse la prossima volta, Signora.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

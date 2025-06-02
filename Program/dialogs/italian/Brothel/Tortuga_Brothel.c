// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Che tipo di domande, "+GetSexPhrase("giovane uomo","signorina")+"?","Cosa ti serve, "+GetSexPhrase("affascinante","bella")+"? Chiedi pure."),"Di nuovo domande?","Hi-hi, se per te è lo stesso - domande...",""+GetSexPhrase("Mh, perché non scegli una bellezza per te? Sto iniziando ad avere sospetti su di te...","Mh, perché non scegli una bellezza per te? Temo che qui non abbiamo ragazzi, tee-hee...")+"","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mi sono ricreduto, mi scusi.","Effettivamente, lascia perdere..."),"Io... mi scuso, non ho domande, per ora.","Hai ragione, è già la terza volta. Perdonami.","Forse la prossima volta, Signora.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Cosa ne pensi del nostro forte? Bella vista, vero? E la guarnigione non è male ancora, eh...","La vita del soldato di forte è piuttosto noiosa... Sorvegliare e pattugliare, dormire e riposare e poi tutto daccapo. Ma in città è diverso... Cosa vuoi, "+GetAddress_Form(NPChar)+"?"),"Disturbare un soldato con domande stupide non è gradito, "+GetAddress_Form(NPChar)+"...","È la terza volta che provi a chiedermelo oggi...","Non è facile essere un soldato eppure eccoti di nuovo qui"+GetSexPhrase(", pezzo di merda,  "," ")+" cercando di farmi arrabbiare. Stai attento o finirai in un seminterrato del forte...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea, scusa per il disturbo.","Non ho nulla da dire, mi scuso."),"Hai ragione, mi scuso.","Hai ragione, è già la terza volta. Mi scuso.","Scusa, non è niente.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

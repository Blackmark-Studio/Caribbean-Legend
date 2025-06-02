// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Cosa ne pensi del nostro forte? Sempre bello, vero? E la guarnigione non è da meno, eh...","La vita del soldato di forte è piuttosto monotona... Sorvegliare e pattugliare, dormire e riposarsi e poi tutto da capo. Ma in città è diverso... Cosa vuoi, "+GetAddress_Form(NPChar)+"?"),"Disturbare un soldato con domande stupide non è gradito, "+GetAddress_Form(NPChar)+"...","È la terza volta che provi a chiedermi oggi...","Non è facile essere un soldato eppure eccoti di nuovo qui"+GetSexPhrase(", mascalzone,  "," ")+" provando a farmi arrabbiare. Fai attenzione o finirai nella cantina del forte...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea, mi dispiace per il disturbo.","Non ho nulla da dire, mi scuso."),"Hai ragione, mi scuso.","Hai ragione, è già la terza volta. Mi scuso.","Scusa, non è niente.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

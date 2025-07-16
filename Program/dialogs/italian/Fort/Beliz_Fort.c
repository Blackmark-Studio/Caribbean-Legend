// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Cosa ne pensi del nostro forte? Sembra buono, vero? E la guarnigione non è ancora peggio, eh...","La vita del soldato del forte è abbastanza noiosa... Sorvegliare e pattugliare, dormire e riposare e poi tutto da capo. Ma in città è diverso... Cosa vuoi, "+GetAddress_Form(NPChar)+"?"),"Disturbare un soldato con domande stupide non è gradito, "+GetAddress_Form(NPChar)+"...","È la terza volta che provi a chiedermi oggi...","Non è facile essere un soldato eppure eccoti di nuovo qui"+GetSexPhrase(", cretino,  "," ")+" cerca di infastidirmi. Fai attenzione o finirai nel seminterrato del forte...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea, scusa per il disturbo.","Non ho nulla da dire, mi scuso."),"Hai ragione, mi scuso.","Hai ragione, è già la terza volta. Mi scuso.","Scusate, non è niente.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

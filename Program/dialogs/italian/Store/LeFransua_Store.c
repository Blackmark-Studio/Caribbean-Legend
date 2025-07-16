// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quali domande hai?","Come posso aiutarvi?"),"Hai cercato di farmi una domanda non molto tempo fa mentre eri nel mio negozio...","Questa è la terza domanda oggi. Ho bisogno di fare affari, non di impegnarmi in conversazioni inutili...","Altre domande? Che ne dici di fare un affare invece?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea...","Non ho nulla di cui parlare al momento."),"Sì, è vero. Ho provato... Mentre ero nel negozio...","Sì, è la terza domanda...","Mh, forse possiamo fare un affare...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}

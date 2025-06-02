// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Cosa vuoi?","Cosa vorresti sapere?"),"Cosa ti serve, "+GetAddress_Form(NPChar)+"?","Questa è la terza volta che provi a chiedermi...","Ne ho avuto abbastanza di te, sparisci!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Scusa, ho cambiato idea.","Non è niente, mi scuso."),"Ho dimenticato, mi scuso...","La terza volta è la volta buona, eh? Scusami...","Scusa, scusa! Allora me ne vado...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}

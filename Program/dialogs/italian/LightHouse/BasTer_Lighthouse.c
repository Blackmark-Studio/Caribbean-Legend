// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Cosa vuoi?","Cosa vorresti sapere?"),"Di che cosa hai bisogno, "+GetAddress_Form(NPChar)+"?","Questa è la terza volta che provi a chiedermi...","Ne ho avuto abbastanza di te, sparisci!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Scusa, ho cambiato idea.","Non è niente, mi scuso."),"Ho dimenticato, le mie scuse...","La terza volta è quella buona, eh? Scusami...","Scusa, scusa! Allora me ne vado da solo...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}

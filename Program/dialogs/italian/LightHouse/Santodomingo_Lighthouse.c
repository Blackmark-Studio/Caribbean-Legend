// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Cosa vuoi?","Cosa vorresti sapere?"),"Cosa ti serve, "+GetAddress_Form(NPChar)+"?","Questa è la terza volta che provi a chiedermi...","Ne ho abbastanza di te, sparisci!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Scusa, ho cambiato idea.","Non è niente, scuse."),"Ho dimenticato, le mie scuse...","La terza volta è la volta buona, eh? Scusatemi...","Scusa, scusa! Allora me ne vado da solo...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}

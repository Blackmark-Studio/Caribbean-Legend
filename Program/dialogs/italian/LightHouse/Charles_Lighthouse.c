// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Cosa vuoi?","Cosa vorresti sapere?"),"Di cosa hai bisogno, "+GetAddress_Form(NPChar)+"?","È la terza volta che provi a chiedermi...","Ne ho avuto abbastanza di te, vattene!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mi dispiace, ho cambiato idea.","Non è niente, scuse."),"Ho dimenticato, le mie scuse...","La terza volta è quella buona, eh? Scusami...","Scusa, scusa! Allora me ne vado da solo...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}

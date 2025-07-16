// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Come posso aiutarti?","Cosa posso fare per te?"),"Dimmi, cosa ti preoccupa, "+GetAddress_Form(NPChar)+"?","Per la terza volta, "+GetAddress_Form(NPChar)+", di cosa hai bisogno?","Ne ho abbastanza di te. Vattene!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mi sono ricreduto, le mie scuse.","Non è niente, mi scuso."),"Perdonami, non è nulla.","Hai ragione, è già la terza volta. Chiedo scusa...","Mi scuso.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}

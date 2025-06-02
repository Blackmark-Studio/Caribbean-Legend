// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Come posso assisterti?","Cosa posso fare per te?"),"Dimmi, cosa ti preoccupa, "+GetAddress_Form(NPChar)+"?","Per la terza volta, "+GetAddress_Form(NPChar)+", di cosa hai bisogno?","Ne ho avuto abbastanza di te. Vattene!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea, le mie scuse.","Non è niente, scusatemi."),"Perdonami, non è niente.","Hai ragione, è già la terza volta. Mi scuso...","Scuse.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}

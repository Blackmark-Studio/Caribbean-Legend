// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Como posso ajudar você?","O que posso fazer por você?"),"Me diga, o que te aflige? "+GetAddress_Form(NPChar)+"?","Pela terceira vez, "+GetAddress_Form(NPChar)+", o que você precisa?","Já cansei de você. Cai fora!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia, me desculpe.","Não é nada, com licença."),"Me perdoe, não é nada.","Você tem razão, já é a terceira vez. Me desculpe...","Desculpe.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}

// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quelles questions avez-vous?","Comment puis-je vous aider ?"),"Tu as essayé de me poser cette question il n'y a pas si longtemps...","Oui, laissez-moi deviner... Encore en train de tourner en rond ?","Ecoutez, je m'occupe des finances ici, je ne réponds pas aux questions...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("J'ai changé d'avis...","Je n'ai rien à dire pour le moment."),"Oumph, où est passée ma mémoire...","Vous l'avez deviné, je suis désolé...","Je comprends...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

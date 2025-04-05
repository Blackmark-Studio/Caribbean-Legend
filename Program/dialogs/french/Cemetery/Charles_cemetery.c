// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Comment puis-je vous aider ?","Que puis-je faire pour vous ?"),"Dites-moi, qu'est-ce qui vous tracasse, "+GetAddress_Form(NPChar)+"?","Pour la troisième fois, "+GetAddress_Form(NPChar)+", que désirez-vous ?","J'en ai assez de vous. Sortez d'ici !","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("J'ai changé d'avis, mes excuses.","Ce n'est rien, excusez-moi."),"Pardonnez-moi, ce n'est rien.","Vous avez raison, c'est déjà la troisième fois. Pardonnez-moi...","Mes excuses.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}

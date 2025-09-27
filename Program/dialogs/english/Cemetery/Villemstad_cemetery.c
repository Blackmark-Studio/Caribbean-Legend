// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("How can I assist you?","What can I do for you?"),"Tell me, what troubles you, "+GetAddress_Form(NPChar)+"?","For the third time, "+GetAddress_Form(NPChar)+", what do you need?","I've had enough of you. Get out!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind, my apologies.","It's nothing, excuse me."),"Forgive me, it's nothing.","You're right, it's the third time already. Pardon me...","Apologies.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}

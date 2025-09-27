// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What do you want?","What would you like to know?"),"What is it you need, "+GetAddress_Form(NPChar)+"?","That's the third time you've tried to ask me...","I've had enough of you, get lost!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Sorry, I've changed my mind.","It's nothing, my apologies."),"I forgot, my apologies...","Third time's the charm, eh? Excuse me...","Sorry, sorry! I'll see myself out then...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}

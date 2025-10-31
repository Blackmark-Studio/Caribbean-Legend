// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What do you want? Ask away.","I'm listening, what's the question?"),"This is the second time you've tried to ask...","This is the third time you've tried to ask...","When is this going to end?! I am a busy man, working on colonial matters and you are still bothering me!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind, sorry.","Not now. Wrong place and time."),"True, I have nothing to say now, sorry.","I'll ask later.","I am sorry, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple("You have already taken everything. What more do you want?","Is there anything left that you didn't take?");
            link.l1 = RandPhraseSimple("Just taking a look around...","Just checking, might have forgotten to take something...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

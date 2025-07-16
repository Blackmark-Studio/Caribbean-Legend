// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What kind of questions, "+ GetSexPhrase("my son","my daughter") +"?", "Ask away, I am listening..."), "I am listening, speak now, "+ GetSexPhrase("my son","my daughter") +"...", "For the third time, "+ GetSexPhrase("my son","my daughter") +", ask for what you need.",
                          "A clergyman has a lot of work and you are distracting me, "+ GetSexPhrase("my son","my daughter") +"...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind...", "Not at this time, padre..."), "I have nothing to say, my apologies.",
                      "I'll ask, but later. Forgive me, father.", "Pardon me, holy father...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

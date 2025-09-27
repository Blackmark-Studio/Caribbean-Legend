// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions do you have?","How can I help you, "+GetAddress_Form(NPChar)+"?"),"You tried to ask me a question not long ago, "+GetAddress_Form(NPChar)+"...","Throughout this entire day, this is the third time you've brought up that question...","More questions, I presume?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind...","I've got nothing to talk about at the moment."),"Umph, where has my memory gone...","Yes, it really is the third time...","No, what questions?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Jason Долго и счастливо
			if (CheckAttribute(pchar, "questTemp.LongHappy.Santiago"))
			{
				link.l1 = "I heard that the holy fathers arrived here from a French colony with some delegation, to agree on something? Probably to exchange prisoners after that bloody massacre in Martinique?";
				link.l1.go = "LH_tavern";
			}
		break;
		
		// Jason Долго и счастливо
		case "LH_tavern":
			dialog.text = "No señor, that story was settled a long time ago without any clerics. You see, you must be living under a palm tree, since you haven't heard that Pope Innocent X and Cardinal Mazarin finally came to an agreement. Europe with its wars is one thing, but all Christians should unite to fight against the pagan darkness at the end of the world. And yes, the frog-eaters came to us. But they didn't agree on anything - our honoured guests are sitting in the governor's mansion, under guard, drinking coffee and warming a seat. Almost a month already! The people gossiped, talked it over at length and got used to it - look, the French abbot holds a prayer service in the evenings at the church. Almost like a spectacle, ahah!";
			link.l1 = "Interesting! I should look at that Frenchman, at least it's more amusing than staring at a mug.";
			link.l1.go = "LH_tavern_1";
		break;
		
		case "LH_tavern_1":
			DialogExit();
			LongHappy_SantiagoBenua();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

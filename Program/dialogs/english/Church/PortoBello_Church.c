// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What kind of questions, "+GetSexPhrase("my son","my daughter")+"?","Ask away, I'm listening..."),"I am listening, speak now. "+GetSexPhrase("my son","my daughter")+"...","For the third time, "+GetSexPhrase("my son","my daughter")+", ask for what you need.","A clergyman has a lot of work, and you are distracting me. "+GetSexPhrase("my son","my daughter")+"...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind...","Not at this time, padre..."),"I have nothing to say, my apologies.","I'll ask, but later. Forgive me, father.","Pardon me, holy father...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Письмо от покойника
			if (CheckAttribute(pchar, "questTemp.LFD_Church_1"))
            {
                link.l1 = "Father, I’m looking for Marisa Caldera. I’ve heard she’s very devout and used to attend church regularly. Can you tell me how to find her?";
                link.l1.go = "LFD_Church_1_1";
            }
			//<-- Письмо от покойника
		break;
		
		//--> Письмо от покойника
		case "LFD_Church_1_1":
			dialog.text = "Marisa was one of our most devoted parishioners, truly the soul of our church. Her absence is a great loss to the congregation. What caused her to disappear, I do not know, but I am certain: she was unfairly tested, not without the Devil’s hand and his minions\nFrom time to time, I hear rumors that she’s been seen in town, but nothing more. All we can do is trust in the Lord’s will and hope that one day she returns and finds solace once again under the church’s roof.";
			link.l1 = "Perhaps you know someone who could tell me more about her?";
			link.l1.go = "LFD_Church_1_2";
			DelLandQuestMark(npchar);
		break;

		case "LFD_Church_1_2":
			dialog.text = ""+GetSexPhrase("My son","My daughter")+", tell me, why are you looking for Marisa? I know that from time to time people seek her out, and not all of them look like righteous men. The world is full of temptation, and not all who pursue her do so with good intent. Before I say a word, I must be sure you mean no harm—to her or anyone connected with her.";
			link.l1 = "I understand your concern, Father, but I assure you: I have no ill intent. I simply wish to deliver a letter that has taken too long to reach her. Who knows—there may be something important inside for her. Here, take a look.";
			link.l1.go = "LFD_Church_1_3";
			TakeItemFromCharacter(pchar, "LFD_letter");
			notification("Given: Letter for Marisa Caldera", "None");
		break;

		case "LFD_Church_1_3":
			dialog.text = "Yes, this letter seems to have weathered many storms before reaching your hands. Who knows what it contains, and what the consequences might be after it is read... But you act honorably, Captain, in returning it to its rightful recipient. If anyone knows where Marisa is now, it is her friend Dolores Monjo—the only one she may have trusted\nHer house is to the left of the port authority. I hope this letter brings no further pain to Marisa, for she has already endured more than enough.";
			link.l1 = "Thank you, Father. May the Lord watch over you.";
			link.l1.go = "LFD_Church_1_4";
			GiveItem2Character(PChar, "LFD_letter");
		break;

		case "LFD_Church_1_4":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Church_1");
		break;
		//<-- Письмо от покойника
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

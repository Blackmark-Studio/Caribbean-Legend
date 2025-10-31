// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What kind of questions, "+GetSexPhrase("my son","my daughter")+"?","Ask away, I'm listening..."),"I am listening, speak now. "+GetSexPhrase("my son","my daughter")+"...","For the third time, "+GetSexPhrase("my son","my daughter")+", ask for what you need.","A clergyman has a lot of work to do and you are distracting me, "+GetSexPhrase("my son","my daughter")+"...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind...","Not at this time, padre..."),"I have nothing to say, my apologies.","I'll ask, but later. Forgive me, father.","Pardon me, holy father...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Jason Долго и счастливо
			if (CheckAttribute(pchar, "questTemp.LongHappy") && pchar.questTemp.LongHappy == "choose" && !CheckAttribute(npchar, "quest.LongHappy"))
			{
				link.l1 = "Holy Father, I'm looking for Abbot Benoit, I have an urgent matter for him. Can you tell me where I can find him?";
				link.l1.go = "LH_church";
			}
		break;
		
		// Jason Долго и счастливо
		case "LH_church":
			dialog.text = "Abbot Benoit has left the city on church business with representatives of the Spanish Catholic mission in the New World. I don't know any details, but Abbot Benoit has been absent long enough to assume the negotiations have been prolonged, or something may have happened along the way. We are all ill at ease, but we can only pray and wait for news.";
			link.l1 = "Can't assume everything will be easy. Holy Father, can you tell me exactly where Abbot Benoit went? I need to find him as quickly as possible.";
			link.l1.go = "LH_church_1";
		break;
		
		case "LH_church_1":
			dialog.text = "I'm afraid I cannot, my son. As far as I know, Abbot Benoit went to negotiate with the Bishop of New Spain and the prelate of the Inquisition, Father Vincento Palotti, but he didn't specify where the meeting would be held.";
			link.l1 = "That should suffice, Holy Father, thank you. I know Father Palotti in some way... I'll look around in Santiago.";
			link.l1.go = "LH_church_2";
		break;
		
		case "LH_church_2":
			DialogExit();
			npchar.quest.LongHappy = "true";
			LongHappy_GoToSantiago();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

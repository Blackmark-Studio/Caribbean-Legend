// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What kind of questions, "+GetSexPhrase("my son","my daughter")+"?","Ask away, I'm listening..."),"I am listening, speak now. "+GetSexPhrase("my son","my daughter")+"...","For the third time, "+GetSexPhrase("my son","my daughter")+", ask for whatever you need.","A clergyman has a lot of work and you are distracting me, "+GetSexPhrase("my son","my daughter")+"...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind...","Not at this time, padre..."),"I have nothing to say, my apologies.","I'll ask, but later. Forgive me, father.","Pardon me, holy father...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";		
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "utensil" && !CheckAttribute(npchar, "quest.utensil"))
			{
				link.l1 = "I come to you regarding an unusual matter, holy father. A privateer named Guy Marchais recently presented a very valuable item to your parish. It was a golden pectoral cross with lazurite embedded in it. Is that true?";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Oh yes, my son!  It is the finest item in our parish. I haven't seen such magnificence in all my life! But why do you ask, my son? Why are you interested in this cross?";
			link.l1 = "Holy Father, I know this won't be to your liking, but this cross was stolen from another parish and the clergyman was murdered during the act. The man who has presented this item to you is a murderer.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "We all sin, my son, and murdering a clergyman is a serious accusation. Do you have any proof? From which parish was this cross stolen?";
			link.l1 = "Is my word not proof enough? This cross was stolen from the parish in Santiago and it must be returned.";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Santiago? Isn't that a Spanish city? My son, you surprise me...";
			link.l1 = "Holy Father, everyone is equal before God. The Spanish are Christians just like us, and disagreements between nations must not affect believers' feelings. I beg you to return this cross to the Santiago parish.";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "My son, don't you understand that this cross is a gift from the devoted Christians for our parish?! No, my son, I can't do what you ask.";
			link.l1 = "Don't you care that blood was spilled over this cross? The blood of a clergyman, Spanish or not, it doesn't matter.";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "My son, you haven't shown any proof and I can't blindly take your word for it. The cross will stay in our parish. This is my final decision. Besides, your effort in helping the Spanish in this matter troubles me greatly.";
			link.l1 = "So be it. Farewell then, holy father...";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			DialogExit();
			npchar.quest.utensil = "true";
			pchar.questTemp.Guardoftruth.Baster_church = "seek";
			AddQuestRecord("Guardoftruth", "27");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

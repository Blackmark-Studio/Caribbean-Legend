// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions do you have?","How can I help you?"),"You tried to ask me a question not long ago...","Nobody's asked questions like that in a Tortuga store for a long time...","Questions, questions, and more questions...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind...","I've got nothing to talk about at the moment."),"Umph, where has my memory gone...","All right, so it's been a long time.","Moooore questions, eh...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "tortuga2")
			{
				link.l1 = "Listen, I need to find Gaius Marchais. I've been told he's involved in privateering and has become quite the negotiator, having taken an excellent galleon from the Spanish. Has he happened to purchase any merchandise from you for trading?";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Gaius Marchais? Oh yes, of course I remember him! But he didn't buy anything. He offered his ship for freight. I just happened to need a ship with a spacious hold - a large batch of raw hides.";
			link.l1 = "And where was the unloading point?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Philipsburg, Saint Maarten.";
			link.l1 = "Fine. Thank you, you've helped me so much!";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Anytime, captain. Stop by my store whenever you like!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddQuestRecord("Guardoftruth", "10");
			pchar.questTemp.Guardoftruth = "maarten";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}

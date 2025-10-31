// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What do you want? Ask away.","I am listening, what's your question?"),"This is the second time you've tried to ask...","This is the third time you have tried to ask...","When is this going to end?! I am a busy man, working on colony matters, and you are still bothering me!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I changed my mind...","Not now. Wrong place and time"),"True... But later, not now...","I'll ask... But a bit later...","I am sorry, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Jason Дороже золота
			if (CheckAttribute(pchar, "questTemp.GoldenGirl") && pchar.questTemp.GoldenGirl == "antigua")
			{
				link.l1 = "Your Excellency, I would like to tell you that I possess a certain piece of information about the Mercury's disappearance.";
                link.l1.go = "G_Girl";
			}
		break;
		
		// Jason Дороже золота
		case "G_Girl":
			dialog.text = "Information? About what, again?";
			link.l1 = "The brigantine, your Excellency. Transporting mail. Documents of great importance and the like. I heard about the investigation and, naturally, as a loyal friend of the British Crown, I'd like to help.";
			link.l1.go = "G_Girl_1";
		break;
		
		case "G_Girl_1":
			dialog.text = "Splendid! Baronet Cortney will be delighted to receive you! I will arrange a meeting immediately.";
			link.l1 = "Thank you, Sir. I'm in a hurry here and I'd appreciate it if this goes quickly.";
			link.l1.go = "G_Girl_2";
		break;
		
		case "G_Girl_2":
			dialog.text = "Don't you worry, you'll have all the time in the world. Guards! Seize him!";
			link.l1 = "Thank... wait, what? Is this a joke?!";
			link.l1.go = "G_Girl_3";
		break;
		
		case "G_Girl_3":
			DialogExit();
			GoldenGirl_AntiguaArest();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

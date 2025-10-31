// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions do you have?","How can I help you?"),"You tried to ask me that question not long ago...","Yup, let me guess... Going around in circles again?","Listen, I handle the finances here, I don't answer questions...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind...","I've got nothing to talk about at the moment."),"Umph, where has my memory gone...","You've guessed it, I'm sorry...","I understand...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			
			// --> Sinistra Длинные тени старых грехов	
			if (CheckAttribute(pchar, "questTemp.DTSG_depozit"))
			{
				link.l1 = "Tell me, did the Colonel visit you? He said you had a reward prepared for me.";
				link.l1.go = "DTSG_depozit_1";
			}
			// <-- Длинные тени старых грехов
		break;
		
		// --> Sinistra Длинные тени старых грехов	
		case "DTSG_depozit_1":
			dialog.text = "What Colonel?";
			link.l1 = "Thomas Lynch.";
			link.l1.go = "DTSG_depozit_2";
		break;
		
		case "DTSG_depozit_2":
			dialog.text = "Speak quietly! I know the man. Yes, he came by. Your reward is waiting for you, Captain.";
			link.l1 = "And how much is there?";
			link.l1.go = "DTSG_depozit_3";
		break;
		
		case "DTSG_depozit_3":
			dialog.text = "Exactly ten thousand in gold. Not a single peso - all gold.";
			link.l1 = "At least it's not thirty pieces of silver...";
			link.l1.go = "DTSG_depozit_4";
			AddItems(pchar, "chest", 70);
			Log_Info("You have received 70 chests");
			PlaySound("interface\important_item.wav");
		break;
		
		case "DTSG_depozit_4":
			dialog.text = "What was that?";
			link.l1 = "Oh, nothing... Thank you. Goodbye.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.DTSG_depozit");
		break;
		// <-- Длинные тени старых грехов
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

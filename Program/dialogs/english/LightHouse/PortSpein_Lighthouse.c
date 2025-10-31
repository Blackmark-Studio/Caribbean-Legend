// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What do you want?","What would you like to know?"),"What is it you need, "+GetAddress_Form(NPChar)+"?","That's the third time you've tried to ask me...","I've had enough of you, get lost!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Sorry, I've changed my mind.","It's nothing, my apologies."),"I forgot, my apologies...","Third time's the charm, eh? Excuse me...","Sorry, sorry! I'll see myself out then...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "Listen, a frigate under the command of Miguel Dichoso was around here in April 1654, but it disappeared then. Can you tell me more about his ship? Maybe you saw what happened to it or where it went? Do you remember anything?";
				link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Oh-ho... Aye, Señor, that was a sight to behold! You don't forget things like that, ha!";
			link.l1 = "Can you tell me what happened?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Señor Dichoso's frigate cast anchor in the harbour of San Jose. I had a good view to see everything, aye. I tell you, it was an excellent frigate, a masterpiece, I swear on my bleeding heart! The crew boasted about her speed, she could reach up to sixteen knots! They spent a day here, then set sail straight for Tobago island. Then, you wouldn't believe it, strange things started happening with the weather as soon as they disappeared beyond the horizon. The weather had been fine for days back then, not a single cloud! And yet this terrible storm came out of nowhere. Looked like Neptune himself paid us a visit, it did! I went up to the top of my lighthouse to light it, but then I saw her... Santa Quiteria! She was surging upon huge waves, accompanied by a giant tornado! The frigate flew past my lighthouse like a spark and then was driven by the storm northwest! No one has seen Santa Quiteria since then. Just an hour later, the wind and the rain and the clouds were gone and the sun was shining, not a single sign of the storm! Never seen anything like it! Although I collected so much amber from my bay that day...";
			link.l1 = "So the storm has driven the frigate back to the Caribbean Sea?";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "It has! Way over yonder to Martinique. I doubt Dichoso could have survived that storm, he was doing his best though! The frigate wasn't sinking, but Santa Quiteria must be on the bottom of the sea among the corals by now... Actually, you are not the first person who has asked me about Dichoso and his frigate.";
			link.l1 = "Really? Who else was interested in Miguel?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Some dashing captain of the Spanish fleet, no less! He introduced himself as... oh... I've gone and forgotten it... Ah! Señor Diego. His name was Diego, but his surname... de Montagna or de Montoya. Something like that. He listened to me just like you did, thanked me and went away. Never seen him since then.";
			if (sti(Pchar.money) >= 5000)
			{
				link.l1 = "I see. Thank you very much for your story, you've helped me a lot. Please accept my gratitude in coins. Farewell.";
				AddMoneyToCharacter(pchar, -5000);
				AddCharacterExpToSkill(pchar, "Leadership", 250);
			}
			else
			{
				link.l1 = "I see. Thank you very much for your story, you've helped me a great deal. Farewell.";
			}
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			DialogExit();
			AddQuestRecord("Guardoftruth", "41");
			pchar.questTemp.Guardoftruth.Trinidad = "mayak";
			pchar.quest.GuardOT_setDiego.win_condition.l1 = "ExitFromLocation";
			pchar.quest.GuardOT_setDiego.win_condition.l1.location = pchar.location;
			pchar.quest.GuardOT_setDiego.function = "GuardOT_SetDiegoOnMayak";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}

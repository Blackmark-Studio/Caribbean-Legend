// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Questions, " + GetAddress_Form(NPChar) + "?", "How can I help you, " + GetAddress_Form(NPChar) + "?"), ""+ GetSexPhrase("Hm, what's the big idea, " + GetAddress_Form(NPChar) + "? ","Again with the strange questions? Toots, go have some rum or something...") +"", "Over this whole day, this is the third time you're talking about some question..."+ GetSexPhrase(" Are these some signs of attention?","") +"",
                          "More questions, I presume, " + GetAddress_Form(NPChar) + "?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind", "I've got nothing to talk about at the moment."), "No, no beautiful...",
                      "No way, dear...", "No, what questions?...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Старые счёты
			if (CheckAttribute(pchar, "questTemp.OS_Tavern_2"))
			{
				link.l1 = "I need to ask you a few questions. You were working in the tavern the day the barrel of gin disappeared, weren't you? What can you tell me about the goings-on here that day?";
				link.l1.go = "OS_Tavern2_1";
			}
			//<-- Старые счёты
		break;

		//--> Старые счёты
		case "OS_Tavern2_1":
			dialog.text = "I... I don't know what to say. Everything was normal, nothing out of the ordinary.";
			link.l1 = "Is that so? Nothing strange? What about that sailor from the 'Sea Beast' who was pestering you? He seemed convinced you'd welcome his company for the night.";
			link.l1.go = "OS_Tavern2_2";
			DelLandQuestMark(npchar);
		break;

		case "OS_Tavern2_2":
			dialog.text = "Oh, him! He... he just had a drop too much, that's all. It happens quite often here, you know. I certainly didn't encourage him, but he started making advances. So I put him in his place.";
			link.l1 = "No encouragement? He tells a different tale. Why did you raise such a commotion this time, but not on other occasions?";
			link.l1.go = "OS_Tavern2_3";
		break;

		case "OS_Tavern2_3":
			dialog.text = "I... I don't know what else to tell you! I truly don't know anything! I was... I was in plain sight all evening! Saw nothing, heard nothing! And about the barrel... I'm not privy to what happened to it! Why this interrogation? I was just... just doing my job as always!";
			link.l1 = "I suspect you're holding back. A night in the ship's hold without light or food works wonders on one's memory. Care to find out? Or shall we have a proper conversation?";
			link.l1.go = "OS_Tavern2_4_HO";
			link.l2 = "I believe you know far more than you're letting on. You have a rare opportunity now — tell me everything, and I'll keep your role in this little play to myself. But if you remain silent — it'll be worse for you. I'll uncover the truth with or without your help.";
			link.l2.go = "OS_Tavern2_4_harizma";
		break;

		case "OS_Tavern2_4_HO":
			dialog.text = "I... I... I'll tell you everything! It was all my... suitor, Jack. Jack Veils! He persuaded me to entice any sailor from the 'Sea Beast'. And when he would make his advances, I was to cause a scene to lure the tavern keeper from behind the counter. As the commotion began to settle, two sailors would start a brawl to keep him occupied in the main room. That's exactly what happened\nDuring that time, the captain of the 'Sea Beast' managed to steal the barrel. That's... that's all I know, "+GetSexPhrase("sir","madam")+"! Please, don't turn me in! I just... I was only... I simply... wanted Jack to finally treat me with some respect! I did help him after all...";
			link.l1 = "You helped one man while throwing another to the wolves without a moment's hesitation?! Nevertheless, I keep my word — I won't expose your part in this. But you'll have to live with what you've done! Your foolishness could have landed the innkeeper in grave danger. Where can I find this Jack of yours? And remember: lie to me, and I'll be back. Trust me, you won't enjoy the return visit.";
			link.l1.go = "OS_Tavern2_5";
			AddComplexSelfExpToScill(40, 40, 40, 0);
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
		break;

		case "OS_Tavern2_4_harizma":
			dialog.text = "I... I... I'll tell you everything! It was all my... suitor, Jack. Jack Veils! He persuaded me to entice any sailor from the 'Sea Beast'. And when he would make his advances, I was to cause a scene to lure the tavern keeper from behind the counter. As the commotion began to settle, two sailors would start a brawl to keep him occupied in the main room. That's exactly what happened\nDuring that time, the captain of the 'Sea Beast' managed to steal the barrel. That's... that's all I know, "+GetSexPhrase("sir","madam")+"! Please, don't turn me in! I just... I was only... I simply... wanted Jack to finally treat me with some respect! I did help him after all...";
			link.l1 = "You helped one man while throwing another to the wolves without a moment's hesitation?! Nevertheless, I keep my word — I won't expose your part in this. But you'll have to live with what you've done! Your foolishness could have landed the innkeeper in grave danger. Where can I find this Jack of yours? And remember: lie to me, and I'll be back. Trust me, you won't enjoy the return visit.";
			link.l1.go = "OS_Tavern2_5";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "OS_Tavern2_5":
			dialog.text = "I didn't realize it was so serious! It's just a barrel after all... Jack lives across the street. He rents the house there, I... I don't know anything more! Please forgive me! Captain, I swear I'll never do anything like this again!";
			link.l1 = "Get back to your duties, and don't you dare start weeping — the tavern keeper mustn't suspect a thing.";
			link.l1.go = "OS_Tavern2_6";
		break;
		
		case "OS_Tavern2_6":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.OS_Tavern_2");
			AddQuestRecord("OS", "4");
			
			//
			pchar.GenQuestBox.PuertoPrincipe_QuestHouse_1.box1.items.cask_gin = 1;
			pchar.GenQuestBox.PuertoPrincipe_QuestHouse_1.box1.items.map_full = 1;
			pchar.GenQuestBox.PuertoPrincipe_QuestHouse_1.box1.items.jewelry2 = 10;
			pchar.GenQuestBox.PuertoPrincipe_QuestHouse_1.box1.items.GunPowder = 50;
			pchar.GenQuestBox.PuertoPrincipe_QuestHouse_1.box1.items.bullet = 50;
			
			PChar.quest.OS_Zasada.win_condition.l1 = "item";
			PChar.quest.OS_Zasada.win_condition.l1.item = "cask_gin";
			PChar.quest.OS_Zasada.function = "OS_Zasada";
			
			SetFunctionLocationCondition("DWH_Close_House", "PuertoPrincipe_QuestHouse_1", false);
		break;
		//<-- Старые счёты
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

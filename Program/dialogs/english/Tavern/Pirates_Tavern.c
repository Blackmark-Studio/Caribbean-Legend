// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions do you have?", "How can I help you, " + GetAddress_Form(NPChar) + "?"), "You tried to ask me some question not long ago, " + GetAddress_Form(NPChar) + "...", "Over this whole day, this is the third time you're talking about some question...",
                          "More questions, I presume?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind...", "I've got nothing to talk about at the moment."), "Umph, where has my memory gone...",
                      "Yes, it really is the third time...", "No, what questions?...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(PChar, "questTemp.Guardoftruth.Archy") && pchar.questTemp.Guardoftruth.Archy == "islatesorotavern")
			{
				link.l1 = "Listen, "+npchar.name+", have you heard anything about a man named Miguel Dichoso? They say, his ship has been seen within waters of Isla Tesoro...";
				link.l1.go = "guardoftruth";
			}
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				link.l1 = "Listen, "+npchar.name+", haven't you seen Miguel Dichoso lately on Isla Tesoro?";
				link.l1.go = "tieyasal";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Aye, I have. That Spanish don sold Shark Dodson a remarkable ship, a frigate, when he still resided here. Ah that ship... She was an incredible...";
			link.l1 = "Let me guess: she had a modern sleek frame and was capable of reaching sixteen knots? And her name was 'Santa Quitaria'?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "As for the frame and the speed, you're absolutely correct, but she had a different name: 'San Martin'. Shark paid a whole heap of gold to that rogue for that ship.";
			link.l1 = "Are you sure it was 'San Martin' and not 'Santa Quiteria'? When did he buy it? And why did you call Dichoso a rogue?";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Damn my eyes, I'm absolutely sure that it was 'San Martin', because I personally witnessed Alexus's workers ripping a plate with that papist nonsense from the stern. Shark Dodson named her 'Fortune', a much more suitable name for such a beauty. (spits) He had bought in the winter of '54, not long before Blaze was murdered\nWhy did I call Don Miguel a rogue? Because he stole the damn ship from the Spanish navy out of Providence! Dodson set a performance with fire and smoke for St. Juan's fort and its garrison, as he was always telling me while he was drunk. Shark sacrificed two damaged luggers in order to make the fight with the frigate look real\nWhen the night came, he secretly sailed 'San Martin' to Isla Tesoro. Shark got the ship and Dichoso got the money. Sly bastard later told his higher-ups that the frigate was sunk during the fight with the pirate fleet, St. Juan's fort commandant confirmed it.";
			link.l1 = "Oh, how those Spanish dons line their pockets! What a dodger! Tell me, are you sure that happened in the winter of 1654? Could it have been during the spring? And didn't that frigate show signs of wear and tear from the storm?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "I'm pretty sure it was winter... Oh, who knows. Maybe it was spring. I don't remember for sure. I was probably drunk. The frigate wasn't worn down at all though it was brand spanking new.";
			link.l1 = "And where is that beauty of a frigate now?";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "A dark story, it is... When Blaze was murdered, everyone suspected Shark because his necklace, a shark's tooth, was found on the corpse. Plus, some people saw Shark in Blaze's residence that night\nShark escaped Isla Tesoro before they gave him the black mark. He paid a visit to Dark Pastor and exchanged his frigate for a brig. No clue where the man is now. Zachary sold the frigate to William Paterson later.";
			link.l1 = "Who is this Paterson?";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "What, you've never heard of Willie Paterson? He's a Scot, just arrived to the Caribbean. Reckons himself captain of the royal fleet, Colonel Fox's favorite himself! By the way, he just started twiddling some business with Jackman too. Patterson's flagship is 'Fortune' herself.";
			link.l1 = "I see. Do you know where Dichoso is right now?";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "I have no idea. After that jiggery pokery with 'Fortune' I haven't seen him on Isla Tesoro since and I haven't heard anything about him.";
			link.l1 = "All right, "+npchar.name+", thanks for the in-depth information! You're an excellent tavern keeper! I wish there were more people like you... Bye!";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "Good luck, "+pchar.name+"!";
			link.l1 = "...";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			DialogExit();
			AddQuestRecord("Guardoftruth", "60_1");
			pchar.questTemp.Guardoftruth.Archy = "guadeloupe";
			// маленькая развлекуха
			pchar.quest.GuardOT_cabinattack.win_condition.l1 = "EnterToSea";
			pchar.quest.GuardOT_cabinattack.function = "GuardOT_PrepareCreateBandosInCabin";
		break;
		
		case "tieyasal":
			dialog.text = "It looks as if both of you are chasing each other, mate. Yes, Dichoso was here right where you're standing. And in the exact way he was interrogating about you that last time you were in Sharptown.";
			link.l1 = "Damn it! That's the news... And where's Miguel right now?";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "I've got no idea. He's departed out to sea where... he said something about Blueweld. He probably went there just looking for you.";
			link.l1 = "Do you happen to be the one that sent him to Blueweld?";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = "No. All I told him was that I hadn't been seen you in for long time.";
			link.l1 = "I see. Alright, then. Thanks, mate!";
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			DialogExit();
			AddQuestRecord("Tieyasal", "3");
			npchar.quest.tieyasal = "true";
			pchar.quest.Tieyasal_ITAttack.win_condition.l1 = "location";
			pchar.quest.Tieyasal_ITAttack.win_condition.l1.location = "Bermudes";
			pchar.quest.Tieyasal_ITAttack.function = "Tieyasal_CreateITShips";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

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
			//--> Старые счёты
			if (CheckAttribute(pchar, "questTemp.OS_Tavern_1"))
			{
				link.l1 = "Word has it someone's relieved you of your precious gin. Or do the rumors speak falsely?";
				link.l1.go = "OS_Tavern1_1";
			}
			if (CheckAttribute(pchar, "questTemp.OS_Tavern_3"))
			{
				link.l1 = "Good tidings, "+npchar.name+"! I've recovered your barrel!";
				link.l1.go = "OS_Tavern3_1";
			}
		//<-- Старые счёты
		break;

		//--> Старые счёты
		case "OS_Tavern1_1":
			dialog.text = "God's wounds, it's true. What else have you heard? Do you know something? I implore you, say you know where to find it. If I don't recover it... I'll have to flee this town. Either by my own two feet or in a pine box.";
			link.l1 = "Indeed, your situation looks grim, friend. No, I've merely caught whispers of your misfortune. How did such valuable cargo slip through your fingers?";
			link.l1.go = "OS_Tavern1_2";
			DelLandQuestMark(npchar);
		break;

		case "OS_Tavern1_2":
			dialog.text = "Blast it all... What can I say? Stolen right from under my nose! The barrel was certainly here in the morning. It arrived two days past, and for safe keeping, I took it home overnight. Come morning, I brought it back, tucked it beneath the counter. By evening, it had vanished without a trace! Not a soul saw or heard a thing.";
			link.l1 = "Well, I'll be damned...";
			link.l1.go = "OS_Tavern1_3";
		break;

		case "OS_Tavern1_3":
			dialog.text = "Had I even the faintest clue, I'd already be hunting it down. But alas, nothing - as if that barrel was too fine for this mortal realm and the heavens simply claimed it. I'll pay one hundred and fifty doubloons to whoever brings it back. More than that, I'll mount a plaque with their name in my tavern so all will know of their heroic deed!";
			link.l1 = "I'll see what I can do. We'll revisit this plaque business later. Tell me instead who knew about this barrel? And who besides yourself might have been behind the counter?";
			link.l1.go = "OS_Tavern1_4";
			link.l2 = "One hundred and fifty doubloons for a barrel? Amusing. But your troubles aren't mine. Sort it out yourself.";
			link.l2.go = "OS_Tavern1_end";
		break;

		case "OS_Tavern1_end":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.OS_Tavern_1");
			CloseQuestHeader("OS");

			for (i=1; i<=3; i++)
			{
				if (CharacterIsAlive("OS_Matros_"+i))
				{
					sld = CharacterFromID("OS_Matros_"+i);
					sld.lifeday = 0;
				}
			}
			sld = CharacterFromID("OS_Pirate");
			sld.lifeday = 0;
		break;

		case "OS_Tavern1_4":
			dialog.text = "Practically no one! Save perhaps my serving girl, but that's impossible. The tavern was in rare form that day - the crew of the 'Sea Beast' had returned from the hunt with a handsome prize. She hadn't a moment's rest, let alone time to sneak behind my counter.";
			link.l1 = "You're certain of that?";
			link.l1.go = "OS_Tavern1_5";
		break;

		case "OS_Tavern1_5":
			dialog.text = "Without a doubt! Working without respite didn't suit her temperament, and by evening she was wound tight as a spring. When one of the sailors made advances, she raised such a commotion it near deafened the whole establishment. I had to abandon my post to restore order. Strange, though - she typically handles such advances with far more composure.";
			link.l1 = "Is that all? Nothing else unusual that day?";
			link.l1.go = "OS_Tavern1_6";
		break;

		case "OS_Tavern1_6":
			dialog.text = "While I was quelling that first disturbance, another flared up - two sailors came to blows in the far corner. The scuffle didn't last long, though; they appeared to be shipmates, and were quickly separated. After that, everything truly quieted down with nothing further worthy of mention.";
			link.l1 = "Very well, I'll begin the search. Wait. I think soon the barrel will be back under your, ahem... watchful eye.";
			link.l1.go = "OS_Tavern1_7";
		break;
		//<-- Старые счёты
		
		case "OS_Tavern1_7":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.OS_Tavern_1");
			AddQuestRecord("OS", "2");
			
			sld = GetCharacter(NPC_GenerateCharacter("OS_Matros_1", "citiz_31", "man", "man", sti(pchar.rank), PIRATE, -1, true, "pirate"));
			sld.dialog.filename = "Quest\MiniEvents\OldScores_dialog.c";
			sld.dialog.currentnode = "OS_Matros";
			LAi_SetImmortal(sld, true);
			sld.City = "PuertoPrincipe";
			ChangeCharacterAddressGroup(sld, "PuertoPrincipe_town", "goto", "goto14");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "OS_Tavern3_1":
			dialog.text = "You found it?! Can it truly be? Captain, you've saved my very life! Who was behind this? I must know the name of the scoundrel!";
			link.l1 = "It was a meticulously planned scheme by one Jack Veils, working in concert with the captain of the 'Sea Beast'. They enlisted their sailors and staged an elaborate diversion to draw you away. When you left your post, the barrel was unguarded, and they made off with it easily.";
			link.l1.go = "OS_Tavern3_2";
			DelLandQuestMark(npchar);
			pchar.questTemp.CameraDialogMode = true;
		break;

		case "OS_Tavern3_2":
			dialog.text = "Good heavens! Jack Veils! So he's returned... And it seems he thought to reclaim the tavern through such underhanded means. That fox never admits defeat!";
			link.l1 = "So he was once the proprietor of this establishment? Rest assured, he'll not be scheming again. I've sent him to meet his maker.";
			link.l1.go = "OS_Tavern3_3";
		break;

		case "OS_Tavern3_3":
			dialog.text = "Captain! This is extraordinary! You've... you've freed me from the constant dread that's been shadowing my days! I always knew he'd return sooner or later... A few years back, we were rivals for the ownership of this tavern, and he managed to best me\nBut the joy of victory proved his undoing - in his celebratory excess, he unwittingly gambled the place away to me over cards. Of course, come morning, he came running, begging to reclaim the tavern, promising anything and everything\nBut I'm no complete fool to agree to such terms. Then he vanished... I knew he wouldn't let the matter rest. I sensed he would return one day. And now, that day has come.";
			link.l1 = "Credit where it's due – he executed his scheme with cunning.";
			link.l1.go = "OS_Tavern3_4";
		break;

		case "OS_Tavern3_4":
			dialog.text = "Wait a moment! How did he even learn about the barrel? It seems... it seems I'm beginning to understand! The waitress! That's why she fled like a scalded cat, without so much as a farewell. She must have caught wind that you'd dealt with Jack. Now it all falls into place. Captain, I'm indebted to you beyond measure, you...";
			link.l1 = "...";
			link.l1.go = "OS_Tavern3_5";
		break;
		
		case "OS_Tavern3_5":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.OS_Tavern_3");
			ChangeShowIntarface();
			
			sld = GetCharacter(NPC_GenerateCharacter("OS_Zaharia", "Marlow", "man", "man", sti(pchar.rank), PIRATE, 0, true, "pirate"));
			sld.name = GetCharacterName("Zachary");
			sld.lastname = GetCharacterName("Marlow");
			ChangeCharacterAddressGroup(sld, "PuertoPrincipe_tavern", "reload", "reload1");
			TeleportCharacterToPosAy(sld, -1.30, 0.00, -0.67, 1.50);
			sld.dialog.filename = "Quest\MiniEvents\OldScores_dialog.c";
			sld.dialog.currentnode = "Zaharia_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		
		//<-- Старые счёты
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

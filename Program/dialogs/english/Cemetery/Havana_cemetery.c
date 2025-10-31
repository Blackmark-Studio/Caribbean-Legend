// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("How can I assist you?","What can I do for you?"),"Tell me, what troubles you, "+GetAddress_Form(NPChar)+"?","For the third time, "+GetAddress_Form(NPChar)+", what do you need?","I've had enough of you. Get out!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind, my apologies.","It's nothing, excuse me."),"Forgive me, it's nothing.","You're right, it's the third time already. Pardon me...","Apologies.",npchar,Dialog.CurrentNode);		
			link.l1.go = "exit";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "Listen, have you seen or met a man by the name of Joachim Merriman, here in Havana or its vicinity? He's a middle-aged señor, Portuguese, with a moustache, imperial beard and piercing eyes. Perhaps in a cove or out in the jungle? I'm looking for him.";
				link.l1.go = "caleuche";
				DelLandQuestMark(npchar);
			}
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "N-no, sailor, c-certainly not. I rarely get visitors down here, you see, uh... and I... I h-haven't seen anyone like the man you described, so...";
			link.l1 = "Truly? Then why are you stuttering and hiding your eyes? Don't lie to me now, you know the truth. You'd better tell me again - have you seen that man?";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "I-I am telling y-you, Señor, I h-haven't seen anyone! I-I've been s-stuttering s-since I w-was a child...";
			link.l1 = "Lies, all lies. I can see it in your eyes. Where is he, where is Merriman?! Tell me, NOW!";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			dialog.text = "I don't know any Merriman! I've never heard that name before either! And don't try to hurt me or the Commandant will have you hanged in the fort! So tread carefully, boy!";
			link.l1 = "Oh, you think so? Alright. Now, you listen to me very carefully: Joachim Merriman is a warlock. The Holy Inquisition is looking for him. Many years ago in Europe, he was sentenced to burn at the stake for grave digging, defiling the dead, and witchcraft. And I know for certain that now he's hiding somewhere, here, in the outskirts of Havana...";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			dialog.text = "...";
			link.l1 = "...recently I cleared the nearby cave of zombies and I know who is responsible! Surely, where else would Merriman go if not to the cemetery! You know where he is. But have it your way, I won't lay a finger on you, but I'll pay a visit to the Inquisitors in Santiago. Father Vincento will find it very intriguing that Joachim Merriman is hiding in Havana's cemetery with his accomplice, the local watchman...";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = "...";
			link.l1 = "...Has the colour already drained from your face? I give you a nobleman's word: one day after I report my findings, the whole island will be crawling with Spanish soldiers. And you will be stretched on the rack, pleading and weeping until you reveal where that warlock is hiding. No later than that, you will be burned at the stake as his accomplice while I watch the auto-da-fé. How would you like that?";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "P-please, señor! I am not partaking in any of this, I swear! I... I just couldn't do anything... How could I stand against him?! He's a terrible man, he can... you have no idea what he can do! Mercy, I beg of you!";
			link.l1 = "Trust me, I know what he can do. I've seen it with my own eyes. So? Where is he? Tell me and I promise I will not get you entangled in this affair.";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			dialog.text = "He... He is hiding in a cave beneath the cemetery. You can only get there through the chapel's door. When he goes out, I hide in my house and stay there. You have no idea how much I'd like to be rid of that horror!\nBut I wouldn't dare even approach. I... I saw him digging a fresh grave, and then... then the dead man rose up and wandered around the cemetery in the moonlight! I nearly lost my sanity then! But Merriman forbade me to leave. He threatened that if I left my house without his permission, even for half a day, he would find me and turn me into that abomination... a walking skeleton!";
			link.l1 = "How often does he leave his cave?";
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			dialog.text = "Well, I bring him food and healing potions from town and... whatever else he demands. He leaves once or twice a month... when the moon is full. He leaves a note at the door, writes what he needs... I-I deliver it and put it at the door, and he takes it once he has returned.";
			link.l1 = "I see. That door to his lair - is it locked in any way?";
			link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			dialog.text = "It is. It's always locked. It's very sturdy, and the lock is massive and complex.";
			link.l1 = "Hm... Merriman is no fool, surely he must have another exit from his lair, just like his house in Europe. If we were to force the door open, he'd slip away, never to be found again. Hmmm...";
			link.l1.go = "caleuche_9";
		break;
		
		case "caleuche_9":
			dialog.text = "Señor, will you swear that you won't turn me in to the Inquisition?";
			link.l1 = "I gave you my word, and the word of a nobleman is sacred. I swear that I won't turn you in.";
			link.l1.go = "caleuche_10";
		break;
		
		case "caleuche_10":
			dialog.text = "Oh bless you, Señor! I know how to get to the cave. There is a key, a second key... I have it. Merriman doesn't know that there are two keys to that lock. I would never dare to enter, but you...";
			link.l1 = "Hand me the key, and I will relieve you of this nightmare.";
			link.l1.go = "caleuche_11";
		break;
		
		case "caleuche_11":
			GiveItem2Character(pchar, "kaleuche_key");
			ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key_crypt");
			dialog.text = "Here you go, Señor. Are you seriously going into his lair?";
			link.l1 = "I am. Lock yourself in your house and wait there while I go inside. Should I not return, leave everything and run as fast as you can.";
			link.l1.go = "caleuche_12";
		break;
		
		case "caleuche_12":
			dialog.text = "But do be careful, Señor. Frightening sounds have been heard from his cave and I fear to even think who could inhabit it. But Merriman is not alone - that is for certain.";
			link.l1 = "I'll take all measures I can. Farewell.";
			link.l1.go = "caleuche_13";
		break;
		
		case "caleuche_13":
			DialogExit();
			AddQuestRecord("Caleuche", "30");
			pchar.questTemp.Caleuche = "merriman";
			pchar.quest.caleuche_merriman_cave.win_condition.l1 = "locator";
			pchar.quest.caleuche_merriman_cave.win_condition.l1.location = "Havana_CryptBig2";
			pchar.quest.caleuche_merriman_cave.win_condition.l1.locator_group = "reload";
			pchar.quest.caleuche_merriman_cave.win_condition.l1.locator = "reload2";
			pchar.quest.caleuche_merriman_cave.function = "Caleuche_OpenMerrimanCave";
			pchar.quest.caleuche_merriman_cave1.win_condition.l1 = "location";
			pchar.quest.caleuche_merriman_cave1.win_condition.l1.location = "Havana_CryptDungeon";
			pchar.quest.caleuche_merriman_cave1.function = "Caleuche_InMerrimanCave";
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("Caleuche_MerrimanCaveOver", 0, 0, 3, false); // таймер
			npchar.quest.caleuche = "true";
			// логово Мерримана
			int n = Findlocation("Havana_CryptDungeon");
			locations[n].id.label = "Merrimancave";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}

// Жоаким Мерриман - португальский сумрачный гений
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
			{
				if (pchar.questTemp.HWIC.Holl == "AbbySeekIsland" && !CheckAttribute(npchar, "quest.HWICHoll.Task"))
				{
					dialog.text = "Good day, sir! I am Doctor Joachim Merriman. Do I have the pleasure of addressing Captain "+GetFullName(pchar)+"?";
					link.l1 = "Aye, that's me. How the devil do you know my name? I don't recall meeting you before.";
					link.l1.go = "JoakimSeekSkull";
					break;
				}
				if (CheckCharacterItem(pchar, "SkullAztec"))
				{
					dialog.text = "I am glad to see you, captain. I can tell by the spring in your step that you are about to make me very happy. Do you have the skull of Yum Cimil?";
					link.l1 = "I have the skull you speak of. It fairly crackles with energy, like a roaring furnace.";
					link.l1.go = "JoakimFindSkull";
					break;
				}
				dialog.text = "Do you have anything else to say, captain?";
				link.l1 = "No, señor Merriman. I am leaving..";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				if (pchar.questTemp.HWIC.Self == "JoakimMeeting" && !CheckAttribute(npchar, "quest.HWICHoll.Task"))
				{
					dialog.text = "Good day, sir! I am Doctor Joachim Merriman. Do I have the pleasure of addressing Captain "+GetFullName(pchar)+"?";
					link.l1 = "Aye, that is me. How the devil do you know my name? I don't recall meeting you before.";
					link.l1.go = "JoakimSeekSkull";
					break;
				}
				if (CheckCharacterItem(pchar, "SkullAztec"))
				{
					DelLandQuestMark(npchar);
					DelMapQuestMarkCity("Villemstad");
					dialog.text = "I am glad to see you, captain. I can tell by the spring in your step that you are about to make me very happy. Do you have the skull of Yum Cimil?";
					link.l1 = "I have the skull you speak of. It fairly crackles with energy, like a roaring furnace.";
					link.l1.go = "JoakimFindSkull";
					break;
				}
				dialog.text = "Do you have anything else to add, captain?";
				link.l1 = "No, Doctor Merriman. I am leaving.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Good day. Do you want anything from me?";
			link.l1 = "No, sorry.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Landlady"://хозяйка дома
			dialog.text = "If you've come to see Doctor Merriman, he is not here. He doesn't live here anymore.";
			link.l1 = "I see.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Landlady";
		break;
		
		case "Landlady_1"://хозяйка дома
			dialog.text = "If you've come to see Doctor Merriman, then I have to tell you that he is not at home. He is out travelling at the moment and I do not know when he will return.";
			link.l1 = "I see.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Landlady_1";
		break;
		
		case "Landlady_2"://хозяйка дома
			dialog.text = "If you've come to see Doctor Merriman, he is not here. He doesn't live here anymore.";
			link.l1 = "I see.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Landlady_2";
		break;
		
		case "JoakimSeekSkull":
			PlaySound("Voice\English\hambit\Joakim Merriman-01.wav");
			dialog.text = "Your affairs are not as private as you may believe, captain! But don't be alarmed, I have a proposition for you! I am a man of science, a natural philosopher of sorts, studying the fascinating culture of the Indian pagans of the Spanish Main and the West Indies. Would you be so kind as to walk with me to my house and discuss the potentially very profitable details in my sitting room?";
			link.l1 = "You have my curiosity and my attention. Lead the way.";
			link.l1.go = "JoakimSeekSkull_1";
		break;
		
		case "JoakimSeekSkull_1":
			dialog.text = "You will not refuse this, sir! My house is not far from here. Follow me!";
			link.l1 = "...";
			link.l1.go = "JoakimSeekSkull_2";
		break;
		
		case "JoakimSeekSkull_2":
			DialogExit();
			AddLandQuestMark(npchar, "questmarkmain");
			LAi_ActorGoToLocation(npchar, "reload", "houseSp1", "Villemstad_houseSp1_room", "goto", "goto1", "JoakimInRoom", -1);
		break;
		
		case "JoakimSeekSkull_3":
			PlaySound("Voice\English\hambit\Joakim Merriman-01.wav");
			dialog.text = "We can talk here without fear of prying ears. You have recently visited my neighbour, Solomon Shneur. I was just passing by and, you must forgive me, Captain, accidentally overheard some details of your conversation with Solomon. It was all so fascinating that I had to listen to the whole thing!";
			link.l1 = "An eavesdropper who's afraid of other eavesdroppers, eh?";
			link.l1.go = "JoakimSeekSkull_4";
		break;
		
		case "JoakimSeekSkull_4":
			dialog.text = "Now, now, captain! It's not like that at all! Solomon is my neighbour and he often visits me. We are good friends despite our religious differences! I know about his misadventures... just like everyone else in Willemstad! Solomon proclaims his troubles to anyone who will listen morning, noon, and night. But enough about that. The old Jew must have already told you about an old jade skull which is stashed along with his gold on some unknown island. Did he tell you about it?";
			link.l1 = "He told me about a skull, but he didn't mention it was made of jade. He also said it was his grandfather's skull. To tell the truth, I thought it was either some Kabbalistic horror, or the old coot had some bats in the belfry.";
			link.l1.go = "JoakimSeekSkull_5";
		break;
		
		case "JoakimSeekSkull_5":
			dialog.text = "No, captain, Solomon is quite sane, just eccentric. The skull does exist. It is an ancient Indian treasure, the jade skull of Yum Cimil! I have no idea how the old Jew got his talons on it. I have been searching for it for half my life\nFind that island where Solomon stashed his family fortune. The skull must be there in his chest. Deliver that jade skull to me and I will pay you half a million pesos.";
			link.l1 = "Half a thousand? That's hardly worth my time- wait a minute...did you say half a million pieces of eight?! Are you kidding me? I've never seen all that money together in one place in my life!";
			link.l1.go = "JoakimSeekSkull_6";
		break;
		
		case "JoakimSeekSkull_6":
			dialog.text = "You're still a young man, captain... So, are you in? You give me the jade skull and I will give you five hundred thousand pieces of eight in return. Deal?";
			link.l1 = "Ha, a fortune for an old skull? Of course I'm in.";
			link.l1.go = "JoakimSeekSkull_7";
		break;
		
		case "JoakimSeekSkull_7":
			dialog.text = "Splendid. It is always a pleasure to work with a man who understands profit. You can find me here in my house if you need me further. Good luck!";
			link.l1 = "Thank you, Doctor Merriman. I won't keep you waiting too long.";
			link.l1.go = "exit";
			npchar.quest.HWICHoll.Task = "true";
			LAi_SetOwnerType(npchar);
			AddDialogExitQuestFunction("CheckIslandCoordinates");//вот тут-то мы и проверим, есть ли у нас координаты острова, и далее будем исходить из результата.
		break;
		
		case "JoakimFindSkull":
			PlaySound("Voice\English\hambit\Joakim Merriman-02.wav");
			dialog.text = "Oh, yes! You are absolutely right about its power... But enough talk, let me see it, I am shaking with impatience.";
			link.l1 = "Here, please, take it. I hope I wasn't mistaken?";
			link.l1.go = "JoakimFindSkull_1";
			DelLandQuestMark(npchar);
		break;
		
		case "JoakimFindSkull_1":
			RemoveItems(PChar, "SkullAztec", 1);
			dialog.text = "Ah, incredible! Yes, this is it. Excellent, captain, most excellent! At last! I have it with me, at last! I have been waiting for this moment for so many years!";
			link.l1 = "What about the money you promised, Doctor Merriman?";
			link.l1.go = "JoakimFindSkull_2";
		break;
		
		case "JoakimFindSkull_2":
			AddMoneyToCharacter(pchar, 500000);
			dialog.text = "Oh, yes, of course! Half a million pieces of eight. Take them, you've earned them.";
			link.l1 = "Pleasure doing business with you. Hard to believe that such a small thing could be worth so much...";
			link.l1.go = "JoakimFindSkull_3";
		break;
		
		case "JoakimFindSkull_3":
			dialog.text = "Small thing? You know not of what you speak. This is... bah, your Philistine mind can scarcely grasp the magnitude of the incredible power behind this precious skull. Truth be told, I don't have time to spare anyway\nThank you, captain, for what you have done. Now it's time to say farewell. I must go.";
			link.l1 = "Farewell, Doctor Merriman. Perhaps we will meet again.";
			link.l1.go = "JoakimFindSkull_4";
		break;
		
		case "JoakimFindSkull_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			sld = characterFromId("Landlady");
			sld.Dialog.Filename = "Quest\HollandGambit\Joakim.c";
			sld.dialog.currentnode = "Landlady_2";
			SetFunctionTimerCondition("Caleuche_StartTotal", 0, 0, 180, false); // таймер на Калеуче
		break;
		
		case "JoakimSeekSkull_8":
			PlaySound("Voice\English\hambit\Joakim Merriman-01.wav");
			DelLandQuestMark(npchar);
			dialog.text = "We can talk here, captain. I know that you are an intimate associate of Abigail Shneur, the daughter of my neighbour Solomon. She has sailed away on your ship to her lover... but that doesn't really matter.";
			link.l1 = "What are you getting at, Doctor?";
			link.l1.go = "JoakimSeekSkull_9";
		break;
		
		case "JoakimSeekSkull_9":
			dialog.text = "If you know Solomon, then you must know his story about the shipwreck and the lost treasures he stashed on some unknown island. He has already told this story to everyone in Willemstad.";
			link.l1 = "Why do you suppose that I have both heard something about that and care about the old Jew's misfortunes?";
			link.l1.go = "JoakimSeekSkull_10";
		break;
		
		case "JoakimSeekSkull_10":
			dialog.text = "Don't you like Solomon? I assure you, he's just a harmless old eccentric. Forget about him. Let's talk business\nI had several long conversations with Solomon. You can't even imagine how I felt when I discovered that this old Jew owns an ancient, priceless artifact I've been searching for for years! The crazy old man stashed it, along with his pathetic money, on some island and he can't even recall its location\nI need this artifact. Bring it to me and I will pay you half a million pieces of eight.";
			link.l1 = "Half a million pieces of eight? You must be joking, doctor. I've never seen that much money in one place in my life!";
			link.l1.go = "JoakimSeekSkull_11";
		break;
		
		case "JoakimSeekSkull_11":
			dialog.text = "You're still a young man. So, are you in? You give me the skull and I will give you five hundred thousand pieces of eight in return. On top of that, you can take Solomon's money too. According to the old man's words, there must be about two hundred thousand pesos... So, seven hundred thousand pieces of eight in total for you. Deal, captain?";
			link.l1 = "Strike me dead! Of course that's a deal! But how am I supposed to find this island?";
			link.l1.go = "JoakimSeekSkull_12";
		break;
		
		case "JoakimSeekSkull_12":
			dialog.text = "Talk to Abigail. Perhaps she remembers something. Ask Solomon. See, if I knew where to find the island I wouldn't ask for your help in the first place.";
			link.l1 = "I see. Sorry for my foolish question. Now, to find this island. Just be sure to be waiting with my payment.";
			link.l1.go = "JoakimSeekSkull_13";
		break;
		
		case "JoakimSeekSkull_13":
			dialog.text = "Exactly. I am glad that we understand each other, Captain. Good luck with your search. You can always find me here in my house.";
			link.l1 = "I won't keep you waiting too long, Doctor Merriman. Goodbye!";
			link.l1.go = "JoakimSeekSkull_14";
		break;
		
		case "JoakimSeekSkull_14":
			DialogExit();
			pchar.questTemp.HWIC.Self = "SeekAbiIsland";
			AddQuestRecord("Holl_Gambit", "3-55");
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload3", true);//закроем комнату Аби
			npchar.quest.HWICHoll.Task = "true";
			LAi_SetOwnerType(npchar);
			NextDiag.CurrentNode = "First time";
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
			AddMapQuestMarkCity("SentJons", false);
		break;
		
		// калеуче
		case "caleuche":
			PlaySound("Voice\English\LSC\Chymiset-03.wav");
			dialog.text = "Yesssss. The sacrificial stones run red with the blood of my enemies! Yum Cimil has granted me his power to command the dead! With this power, I will soon rule the living!";
			link.l1 = "Very melodramatic, Merriman. What are you planning to do with your army of walking corpses? Are you playing Caesar, trying to conquer the world?";
			link.l1.go = "caleuche_1";
			CreateLocationParticles("large_smoke", "goto", "goto37", 0.5, 0, 0, "");
		break;
		
		case "caleuche_1":
			dialog.text = "Silence, you fool! Did you really expect me to reveal my secret plan in a monologue?! Well, I see no reason not to, since you won't survive this encounter! My undead legions will first occupy all the dark caves and dungeons of the Caribbean. My outposts will be stationed in every village, awaiting my signal. And when the time comes, my walking corpses will march forth and overrun the lands of the living!\nPity you won't live to see it, you pathetic little goody two-shoes, you would-be protagonist! You have entered my sanctuary – and you will not leave it alive! I will lead my army of darkness!";
			link.l1 = "Listen mate, you're not leading anything except Jack and shit, and Jack just left town.";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			PlaySound("Types\warrior04.wav");
			dialog.text = "Oh ho ho! You dare to challenge me and my skeletal servants?! Then behold what I truly am, and tremble with fear!";
			link.l1 = "Come get some.";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			npchar.model = "Meriman_2";
			Characters_RefreshModel(npchar);
			PlaySound("Ambient\Teno_inside\teleporter.wav");
			dialog.text = "";
			link.l1 = "Ahhh! Sweet Jesus!";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			PlaySound("Voice\English\hambit\Joakim Merriman-04.wav");
			dialog.text = "Now do you understand who is standing in front of you, you mewling maggot?! I've got a bone to pick with you! Yum Cimil himself favours me! I will swallow your soul!";
			link.l1 = "Alright, bonehead. Let's dance.";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "goto", "goto37", "none", "", "", "Caleuche_MerrimanTeleport", -1);
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "goto", "goto37");
			pchar.questTemp.Caleuche.Merriman_hide = "true";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("You are a "+GetSexPhrase("Thief, mister! Guards, seize him","Thief, girl! Guards, seize her")+"!!!","Just look at that! As soon as my back was turned, you decided to check my chest! Thief! Catch the thief!!!","Guards! Robbery! Catch the thief!!!");
			link.l1 = "Damn it!";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}

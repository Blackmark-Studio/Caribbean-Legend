// колдун ривадос - Чимисет
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Want something?";
			link.l1 = "No, nevermind.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		//-------------------------------------в тюрьме на Тартарусе-----------------------------
		// вариант R
		case "KillChad":
			dialog.text = "Wait, stop! I beg you, listen to me, before you make a terrible mistake.";
			link.l1 = "I'm listening...";
			link.l1.go = "KillChad_1";
			LAi_RemoveCheckMinHP(npchar); //убираем проверяльщик, если ещё есть
		break;
		
		case "KillChad_1":
			dialog.text = "You've been told to kill me, right? I heard you talking with Chad upstairs. I don't blame you - he left you no choice - but you are wrong to think that Chad will let you go once I'm dead.";
			link.l1 = "Hm... and why won't he? All I know is that my future looks bleak if I don't kill you.";
			link.l1.go = "KillChad_2";
		break;
		
		case "KillChad_2":
			dialog.text = "You won't have any future at all if you kill me. Listen, the Narwhals and Chad wish me gone, but they are too scared of me to do the deed themselves - my killer will be cursed forever. So they want someone to do it for them.\nChad knows that you are not Rivados. He is crossing you. Once you kill me, they will do the same to you and use your corpse to fool Shark.";
			link.l1 = "Shark?! Shark Dodson? He's here? And for the love of God, tell me, who the hell are these Rivados?";
			link.l1.go = "KillChad_3";
		break;
		
		case "KillChad_3":
			dialog.text = "You weren't lying... you are new here... hmm... But now is not the time to explain! We have to escape. I have a plan, will you listen?";
			link.l1 = "No. You know what, wizard? I just made a trip through some mystical portal and survived, so your curses don't scare me. I'm sorry - I will try to make this painless.";
			link.l1.go = "KillChad_fightfail";
			link.l2 = "All right, I will listen. What is your plan?";
			link.l2.go = "KillChad_4";
		break;
		
		case "KillChad_fightfail":
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "afraid", "", -1);
			LAi_SetImmortal(npchar, false);
			pchar.quest.LSC_fightfail.win_condition.l1 = "NPC_Death";
			pchar.quest.LSC_fightfail.win_condition.l1.character = "Chimiset";
			pchar.quest.LSC_fightfail.function = "LSC_Fightfail_Final";
		break;
		
		case "KillChad_4":
			dialog.text = "There is a chest over there. It contains decent weapons and potions. It is locked, but the lock is old and damaged, so find a crowbar and break it.\nTake everything from the chest, arm yourself, and go to the stairs. It is a good defensive position; they will be forced to fight you one at a time - just watch out for the musketeers.\nI hope that you are good with a blade, I am too old to help you fight. If you manage to kill them all and survive, I guarantee you the protection of the Rivados - my family.";
			link.l1 = "Very well... pray to your gods for me; this fight will not be easy. Those lads upstairs don't look soft.";
			link.l1.go = "KillChad_5";
		break;
		
		case "KillChad_5":
			DialogExit();
			pchar.quest.LSC_fightfail.over = "yes"; //снять прерывание
			LAi_SetImmortal(npchar, true);
			ref location = &Locations[FindLocation(pchar.location)];
			location.private1.key = "crowbar";
			location.private1.key.delItem = true;
			NextDiag.CurrentNode = "KillChad_6";
		break;
		
		case "KillChad_6":
			dialog.text = "Don't waste time! Force the lock, quickly!";
			link.l1 = "Yes, yes, I'm doing it!";
			link.l1.go = "exit";
			NextDiag.TempNode = "KillChad_6";
		break;
		
		case "Chad_die":
			dialog.text = "Well done! You are truly a master warrior. My life is in your debt, stranger. Tell me, what is your name?";
			link.l1 = ""+pchar.name+". "+GetFullName(pchar)+". And what's yours?";
			link.l1.go = "Chad_die_1";
		break;
		
		case "Chad_die_1":
			dialog.text = "I am Chimiset, Rivados shaman and counsel to our chief, Black Eddie. He will be glad to know that you've set me free and saved my life. You are a friend to me, Black Eddie, and all Rivados. From now on you will always be a welcome guest on the Protector...";
			link.l1 = "Wait... Chimiset, in case you still don't understand, it's been only a few hours since I got here! Can you explain me where I am, who your Rivados are, and where I can find Shark Dodson?";
			link.l1.go = "Chad_die_2";
		break;
		
		case "Chad_die_2":
			dialog.text = "This place is called the City of Abandoned Ships - though that name is a mockery; it is not much of a city.\nThis place is an island formed out of hundreds of dead ships. The central wrecks form our dwelling space. The island's inhabitants are people who survived the shipwrecks caused by the storms and currents that circle the island.\nMy Rivados are a clan, a group of free blacks who have been living together for a long time. There are three other groups who live here: the Narwhal clan, descended from the men who brought our African ancestors here; Shark Dodson's pirates; and the commoners, who keep to themselves.\nShark may be considered chief of the island, calls himself 'Admiral.' He arrived quite recently and seized power violently. He captured the San Augustine, where the island stores its provisions. Now, we have to buy our own food back at the prices named by Shark. Based on what I overheard between you and Chad, it seems that you have already been in the pirate warehouse.\nChad Kapper was Shark's boatswain and prison warden. Together with Layton Dexter, Shark's first mate, these men and their pirates formed one of the three controlling powers on the island, together with my Rivados and the Narwhals.";
			link.l1 = "Why did Chad Kapper want me to kill you?";
			link.l1.go = "Chad_die_3";
		break;
		
		case "Chad_die_3":
			dialog.text = "Chad struck a bargain with the Narwhals, the sworn enemies of the Rivados. With their help, he was going to kill Shark and take his place.\nThe Narwhals hold a grudge against the Admiral for the murder of their leader, Alan Milrow. They believe that Shark is responsible, but they are wrong. Chad murdered Alan; I am the sole witness to this crime.\nThat is why Chad wished me dead, yet he feared to do it himself. Pirates are fearless in battle, but they respect big magic. So he tried to use you.\nChad and the Narwhals would have killed Shark and blamed the Rivados.";
			link.l1 = "Why blame you?";
			link.l1.go = "Chad_die_4";
		break;
		
		case "Chad_die_4":
			dialog.text = ""+pchar.name+", let's talk later. We have to hurry, before Shark's pirates show up. Search Chad's body and take his keys. And check his desk, he might have important papers there.\nGo to Shark Dodson, you will find him in the San Augustine, a large ship at the north end of the island. There is a rope bridge that stretches from her to the Pluto. Tell him that Chad was plotting to betray him, that the Narwhals are behind all of this, that we, the Rivados, have nothing to do with it.\nI will gladly tell you anything you want to know once you come see me on the Protector. Let's be gone!";
			link.l1 = "Fine, Chimiset. I will find you later at the... the Protector. Let's go!";
			link.l1.go = "Chad_die_5";
		break;
		
		case "Chad_die_5":
			dialog.text = "One last thing: our ships, including the Protector, are forbidden to strangers. You must be Rivados or know our password to enter. I would tell you, but it changes every week, and I've been here too long, so I don't know the current password.\nVisit the San Augustine first. I will tell our people who you are, while you talk to Shark. We will expect you. Stay away from the Protector until you've spoken to Shark!";
			link.l1 = "I understand. I'll head to the San Augustine. See you soon!";
			link.l1.go = "Chad_die_6";
		break;
		
		case "Chad_die_6":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Notsearchbody");
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			pchar.quest.LSC_LetterChad.win_condition.l1 = "item";
			pchar.quest.LSC_LetterChad.win_condition.l1.item = "letter_chad";
			pchar.quest.LSC_LetterChad.function = "LSC_LetterChad_Find";
			sld = characterFromId("SharkMush_17");
			sld.lifeday = 0;
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("SharkSold_1"+(i+3));
				sld.lifeday = 0;
			}
			AddSimpleRumourCityTip("They say that you are a friend of clan Rivados. Interesting... congratulations.", "LostShipsCity", 5, 1, "LSC", "");
			AddSimpleRumourCityTip("They say that you saved the Rivados wizard Chimiset from Tartarus. Now, you are a welcome guest on their ships.", "LostShipsCity", 5, 1, "LSC", "");
			AddSimpleRumourCityTip("So, it was you who set Chimiset free! Interesting. Now you are a friend of Rivados but an enemy of Narwhals. I'm not sure whether to congratulate or pity you...", "LostShipsCity", 5, 1, "LSC", "");
		break;
		
		// вариант N
		case "prisoner":
			dialog.text = "What do you want from me, stranger?";
			link.l1 = "Your name is Chimiset, right?";
			link.l1.go = "prisoner_1";
		break;
		
		case "prisoner_1":
			dialog.text = "Yes, it is. Do you have business with me?";
			link.l1 = "I do. I come from the Admiral, Shark Dodson, with an order to set you free, but on one condition: you must answer my questions.";
			link.l1.go = "prisoner_2";
		break;
		
		case "prisoner_2":
			dialog.text = "Dodson has decided to release me? I am glad to hear it - that is, if it isn't a trick.";
			link.l1 = "It's no trick, but I need your help. Tell me, Chimiset, is there an Indian idol on this island, that is stone during the day but turns to gold at midnight? Do not think me mad...";
			link.l1.go = "Friend_2";
		break;
		
		case "prisoner_3":
			dialog.text = "Any more questions?";
			link.l1 = "Yes. Do you know a man called 'White Boy'?";
			link.l1.go = "prisoner_4";
		break;
		
		case "prisoner_4":
			dialog.text = "White Boy? Sure, I know him. That is Ole Christiansen. He is grown, now, and doesn't look like a boy anymore, though his mind is still that of a child's.";
			link.l1 = "Is that so? Tell me, where can I find him?";
			link.l1.go = "prisoner_5";
		break;
		
		case "prisoner_5":
			dialog.text = "He can often be found in Axel Yost's shop, Carpentero's tavern, or simply walking the streets. He is pale, has white hair, and a simple manner about him. You will recognize him.";
			link.l1 = "Excellent! One more question: have you met a man here by the name of Nathaniel Hawk? He would've have shown up here some time ago and he might be seriously ill.";
			link.l1.go = "prisoner_6";
		break;
		
		case "prisoner_6":
			dialog.text = "I don't know any man by that name. I can assure you that he is not on the Rivados' ships, and neither have I seen him in the common areas.\nI can't say about the Narwhals' territories, though. Rivados don't go there.";
			link.l1 = "I see. Well, thanks for your help, Chimiset!";
			link.l1.go = "prisoner_7";
		break;
		
		case "prisoner_7":
			dialog.text = "And will Shark set me free, now?";
			link.l1 = "Yes. I have nothing else to ask you. Chad Kapper will free you. Well, I have to go...";
			link.l1.go = "prisoner_8";
		break;
		
		case "prisoner_8":
			dialog.text = "Stop! Come back.";
			link.l1 = "Yes? Thought of something more?";
			link.l1.go = "prisoner_9";
		break;
		
		case "prisoner_9":
			dialog.text = "Not exactly... (lowering his voice) I see that you are not one of Kapper's men. Do not trust him. He is a murderer.\nNot long ago, he killed Alan Milrow, unarmed, in cold blood. He was leader of the Narwhal clan. I saw it from my cell: Chad just walked in and stabbed him.\I have heard rumours that some of the Admiral's own men plan to assassinate him. Tell Shark - and tell him that I will say more when he and I talk face to face.";
			link.l1 = "Hm. Fine, I will tell Dodson about it. See you!";
			link.l1.go = "prisoner_10";
		break;
		
		case "prisoner_10":
			DialogExit();
			sld = characterFromId("Capper");
			sld.quest.chimiset_talk = "true"; // разговор с Чимисетом состоялся
			if (!CheckAttribute(npchar, "quest.capper_talk")) chrDisableReloadToLocation = true;//закрыть локацию
			else chrDisableReloadToLocation = false;//открыть локацию
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "entrance_10"; // ноду Акуле
			LSC_SetWhiteBoy(); // поставим белого мальчика
			NextDiag.CurrentNode = "prisoner_11";
			AddQuestRecord("SharkHunt", "20");
		break;
		
		case "prisoner_11":
			dialog.text = "Go to Shark and tell him everything I've told you. I hope they let me out of this cage soon...";
			link.l1 = "I am on my way.";
			link.l1.go = "exit";
			NextDiag.TempNode = "prisoner_11";
		break;
		
		//------------------------беседа на Протекторе, если был старт через Тартарус-----------------
		case "Friend":
			dialog.text = "There you are, my friend! Thank you again for saving me, and trusting me instead of Kapper.\nTake these amulets as compensation for your efforts. I am sure you will find them useful.";
			link.l1 = "Thank you! I didn't expect that...";
			link.l1.go = "Friend_1";
		break;
		
		case "Friend_1":
			GiveItem2Character(pchar, "indian_1");
			GiveItem2Character(pchar, "indian_11");
			GiveItem2Character(pchar, "amulet_1");
			PlaySound("interface\important_item.wav");
			dialog.text = "And now we can talk. You had questions for me, I believe?";
			link.l1 = "Right. I need your help. Chimiset, do not think me mad... but is there an Indian idol on this island, that is stone during the day, but which turns to gold at midnight?";
			link.l1.go = "Friend_2";
		break;
		
		// нода пересечения
		case "Friend_2":
			dialog.text = "I do not think you mad; there was such an idol.\nThough, it turns to gold under the morning sun's rays, and remains stone the rest of the day and night...\nMany times we brought wicked Narwhals to the idol, and it devoured each and every one. But no longer.";
			link.l1 = "No longer... are you saying the idol is gone?";
			link.l1.go = "Friend_3";
		break;
		
		case "Friend_3":
			dialog.text = "The idol was aboard the San Geronimo. That ship sank, taking the idol with it, several years ago.";
			link.l1 = "Fuck! I was counting on using the idol to leave this island... And where was that ship situated?";
			link.l1.go = "Friend_4";
		break;
		
		case "Friend_4":
			dialog.text = "Not far from Narwhal territory, near the wreck of the Phoenix. You can see the San Geronimo resting on the seabed on a clear day.";
			link.l1 = "Ah! So it's lying on the shoal? I can swim to it, then--";
			link.l1.go = "Friend_5";
		break;
		
		case "Friend_5":
			dialog.text = "You can't, my friend. First, it is too deep. Second, there are many giant crabs. They will tear you apart before you get to the San Geronimo.";
			link.l1 = "Argh... very well, I'll have to think on this. At least I know that the statue exists, and where it lies.";
			if (CheckAttribute(npchar, "quest.chimiset_die")) link.l1.go = "prisoner_3";
			else
			{	
				if (CheckAttribute(pchar, "questTemp.LSC.Mary")) link.l1.go = "freedom_1";
				else link.l1.go = "Friend_6";
			}
			AddQuestRecord("LSC", "4");
		break;
		// нода пересечения
		
		case "Friend_6":
			dialog.text = "I see that you have more questions. Ask, my friend.";
			link.l1 = "Shark Dodson asked me to find Chad's accomplices. I found a letter in Chad's chest. There is something about some marksman, and a rifle. It looks like they want to assassinate Shark from a great distance. What do you think, Chimiset?";
			link.l1.go = "Friend_7";
		break;
		
		case "Friend_7":
			dialog.text = "They are going to shoot the Admiral? Hmm, let me think... Thing is, the Admiral almost never leaves his residence, and when he does, he is protected by half a dozen pirates.\nBut... he likes to walk around the stern gallery late in the evening; it's his habit.\nThere are two places that provide an angle on the Admiral's residence: the bow of the Santa Florentina and the mast of the Fury. Even so, no marksman I know of could make such a shot.\nHe would have to be eagle-eyed indeed, and he would need an excellent rifle. You should ask around the island for people who have access to such firearms.";
			link.l1 = "The letter did mention a... a stutzen. Have you seen anyone with such a gun?";
			link.l1.go = "Friend_8";
		break;
		
		case "Friend_8":
			dialog.text = "No. I've never even heard of such a weapon. Ask people - perhaps, someone knows something we don't.";
			link.l1 = "All right. Your information has been valuable, thank you. Oh, a final question... do you know someone called 'White Boy'?";
			link.l1.go = "Friend_9";
		break;
		
		case "Friend_9":
			dialog.text = "White Boy? Sure, that is the nickname of Ole Christiansen. He is an adult now and doesn't look like a boy anymore, though his mind is still that of a child.";
			link.l1 = "So, he is a simpleton? Tell me, where can I find him?";
			link.l1.go = "Friend_10";
		break;
		
		case "Friend_10":
			dialog.text = "He can often be found in Axel Yost's shop, Carpentero's tavern, or walking the streets. He is pale, has white hair, and a simple manner about him. You will recognize him.";
			link.l1 = "Great. Thanks, Chimiset, you have been an enormous help!";
			link.l1.go = "Friend_11";
		break;
		
		case "Friend_11":
			dialog.text = "I am always glad to help a friend of the Rivados. Come and see me if you have more questions.";
			link.l1 = "I will - for now, I have to go now. Farewell!";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary")) link.l1.go = "freedom_2";
			else link.l1.go = "Friend_12";
		break;
		
		case "Friend_12":
			DialogExit();
			NextDiag.CurrentNode = "Chimiset_wait";
			LSC_SetWhiteBoy(); // ставим Белого Мальчика в магазин
			pchar.questTemp.Saga.SharkHunt = "search_mush_1"; // флаг на магазин - поиск мушкета
			AddQuestRecord("SharkHunt", "11");
		break;
		
		case "freedom":
			dialog.text = "And here is the one whom I owe my freedom and my life. Thank you for helping my brothers save me from that murderer, Kapper.\nTake these amulets as compensation for your efforts. I am sure you will find them useful.";
			link.l1 = "Thank you! I didn't expect that...";
			link.l1.go = "Friend_1";
		break;
		
		case "freedom_1":
			dialog.text = "What else can I do for you this day?";
			link.l1 = "Tell me, Chimiset, do you know someone called 'White Boy'?";
			link.l1.go = "Friend_9";
		break;
		
		case "freedom_2":
			DialogExit();
			NextDiag.CurrentNode = "Chimiset_wait";
			LSC_SetWhiteBoy(); // ставим Белого Мальчика в магазин
		break;
		
		//--> информационный блок
		case "Chimiset_wait": // стал другом
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "Oh! My friend "+pchar.name+"! I was told you'd drowned! Seems the loa have taken a liking to you...";
				link.l1 = "I am alive and well, Chimiset. Thank you for your concern. As for your loa, you may be right - they certainly looked after me when I travelled through Kukulcan...";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			dialog.text = "What brings you here, my friend?";
			/*if (!CheckAttribute(npchar, "quest.story"))
			{
				link.l1 = "Tell me how the leader of the Narwhals died. You were the only one who saw.";
				link.l1.go = "story";
			}*/
			if (!CheckAttribute(npchar, "quest.crab"))
			{
				link.l2 = "You mentioned crabs at the bottom near the San Geronimo. What are they?";
				link.l2.go = "crab";
			}
			link.l9 = "Nothing, Chimiset. Just wanted to see you, my friend.";
			link.l9.go = "exit";
			NextDiag.TempNode = "Chimiset_wait";
		break;
		
		case "story":
			dialog.text = "I will write it all down as I witnessed it.";
			link.l1 = "Thank you.";
			link.l1.go = "exit";
			npchar.quest.story = "true";
			NextDiag.TempNode = "Chimiset_wait";
		break;
		
		case "crab":
			dialog.text = "No one knows where they came from, or why they have reached such gigantic size. In fact we know little about these beasts.\nGroups of them can be found among the shipwrecks, living in shallow water, but most of them stalk the bottom of the sea, eating fish and any garbage we toss overboard.\nThey are a menace; their pincers can sever limbs and their jaws contain a dangerous poison, similar to that which saturates the bodies of barracuda. If left untreated, crab bites are lethal. Fortunately, the toxin can be counteracted by any common antidote or mixture.\nThere once was a crab hunter among us - a brave man who dove to the bottom to kill crabs in their own domain. He used to bring us their meat, which makes a delicious dish. He also brought me their poison, which formed a key ingredient in some of my potions.\nIt's a great pity he went to his creator - he was loved and envied by all.";
			link.l1 = "How did he die?";
			link.l1.go = "crab_1";
		break;
		
		case "crab_1":
			dialog.text = "Eaten by the very crabs he hunted. I warn you: be careful around those creatures.";
			link.l1 = "I will.";
			link.l1.go = "exit";
			npchar.quest.crab = "true";
			NextDiag.TempNode = "Chimiset_wait";
		break;
		//<-- информационный блок
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}

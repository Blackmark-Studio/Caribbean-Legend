// Даниэль Хоук - жена Натаниэля Хоука
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	bool bOk1, bOk2;
	string 	sTemp, sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time": //первая встреча - знакомство
			PlaySound("Voice\English\saga\Denny Hawk-02.wav");
			dialog.text = "Wait, handsome! I think we should talk.";
			link.l1 = "Do I know you? Anyway, I always have a few extra hours for a lady.";
			link.l1.go = "meeting";			
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			PlaySound("Voice\English\saga\Denny Hawk-01.wav");
			dialog.text = "Don't make plans just yet, Captain. Find yourself some younger, foolish looking girl for a few extra hours. I have got business for you. I am married actually. My husband's name is Nathaniel Hawk.";
			link.l1 = "Isn't that something! So you must be that bit... eh, Dannie Hawk, mister Svenson mentioned you.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "In the flesh. Yes, I am aware that the Forest Devil doesn't think much of me, the feeling is mutual, but he had to warn you that I wear my saber not just because it's pretty. So, cut to the chase, son!\nI have been shadowing Svenson and his visitors for a while because he was the one who sent my husband into the jungles to die. I thought that he was working with Jackman, but now I see that he is not. I was hiding under the window during your conversation. Couldn't eavesdrop everything, but learned a lot of useful information.\nAre you really willing to find my husband and kick Jackman's ass? Or were you only talking cheap?";
			link.l1 = "Eavesdropping is bad, Madame Hawk. But I will forgive you if you talk to me in a more respectful way. Looking for Hawk or not, that's only my concern. Speak if you have something useful to say or leave me alone if you don't. I won't ask twice.";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "A-ha, such a hothead! Come on, Captain... My temper is not really making you comfortable, that's for sure. I see that you are not a coward and you know your worth. So... let's familiarize ourselves. I promise you that I will be careful with what I am saying to you. I need you and you need me. We share goals. Take me to your crew and you won't regret it. I will serve you with good faith and fidelity until we find Nathan, you have my word.";
			link.l1 = "Consider yourself accepted... Dannie. Svenson told me that you have already been searching for your husband. Have you found anything of interest?";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Not much, but enough to accuse Jackman of lying. The bastard said that the mine's guards, those my Nathan faced, didn't take prisoners. And while it's true that no one has seen my husband's corpse at the bay, how could they, because he actually was taken to the mines as a prisoner. Snake Eye, a shaman of the Miskito people, found him there.\nHe also arranged his escape. But where my husband is now, that stays unknown. The shaman was mumbling something about some Kukulcan who ate him, but I didn't understand anything. Besides, the redskin made it pretty clear that white women are nothing but a joke for him. You should speak with him, maybe he will be more conversable";
			link.l1 = "That's something at least! Such news make me happier. Where can I find this Indian?";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "There is a village deep in the jungles. We need to land at Amatique Bay and go west trough the jungles. I will show you the way if you don't find it yourself. A stone idol can be found not far from the village and the savages revere it as their god. I have been there several times. Nothing special really. Just a simple stone covered by moss.";
			link.l1 = "Interesting. Fine, let's go. We will talk to the shaman and we will see what to do next. Ready?";
			link.l1.go = "meeting_5";
		break;
		
		case "meeting_5":
			dialog.text = "Sure! Of course, I am ready. I have been travelling all the time since I've left Maroon Town. Besides I don't want to be just another of your passengers.";
			link.l1 = "Fine. Let's go to my ship.";
			link.l1.go = "meeting_6";
		break;
		
		case "meeting_6":
			dialog.text = "Aye-aye, Captain!";
			link.l1 = "...";
			link.l1.go = "meeting_7";
		break;
		
		case "meeting_7":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.quest.OfficerPrice = sti(pchar.rank)*700;
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.CompanionDisable = true; //нельзя в компаньоны - чтобы не утонула
			LAi_SetImmortal(npchar, false);
			npchar.HalfImmortal = true; //чтобы не убили в сухопутном бою
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			npchar.DontClearDead = true;
			NextDiag.CurrentNode = "Danielle_officer";
			npchar.HoldEquip = true; // лесник -  не отдавать саблю и пистоль																					 
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			AddQuestRecord("BaronReturn", "2");
			Saga_CreateSnakeEye();
			//выбираем амулеты
			pchar.questTemp.Saga.BaronReturn.Indian = "indian_"+(rand(10)+1);
			pchar.questTemp.Saga.BaronReturn.Amulet = "amulet_"+(rand(10)+1);
			pchar.questTemp.Saga.BaronReturn.Obereg = "obereg_"+(rand(10)+1);
			// на локацию с истуканом
			npchar.quest.talk = "dolly";
			pchar.quest.Saga_Dolly.win_condition.l1 = "location";
			pchar.quest.Saga_Dolly.win_condition.l1.location = "Pearl_jungle_03";
			pchar.quest.Saga_Dolly.function = "Saga_DannyTalk";
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			npchar.greeting = "danny_1";
		break;
		
		// у истукана в джунглях
		case "Dolly":
			dialog.text = ""+pchar.name+"! Come on! I will show you the stone idol that the Indian shaman was talking about. Just a usual stone pillar. Let's go!";
			link.l1 = "...";
			link.l1.go = "Dolly_1";
		break;
		
		case "Dolly_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "item", "torch1", "Saga_ShowDolly", -1);
		break;
		
		case "Dolly_2":
			dialog.text = "Hey! Take a look, it is just a stone statue. Nothing special...";
			link.l1 = "I see... Though the figure at the top is a bit sinister, don't you think? ";
			link.l1.go = "Dolly_3";
		break;
		
		case "Dolly_3":
			dialog.text = "All Indian statues are scary and evil looking. I have seen something similar before. They are all the same. Anyway, let's go, the village is nearby!";
			link.l1 = "Let's go!";
			link.l1.go = "Dolly_4";
		break;
		
		case "Dolly_4":
			chrDisableReloadToLocation = false;//открыть локацию
			DialogExit();
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			npchar.dialog.currentnode = "Danielle_officer";
		break;
		
		// у мискито
		case "SnakeEye":
			dialog.text = "So, what do you say, "+pchar.name+"? What did that redskin ventriloquist tell you? Did you get anything from his philosophical words?";
			link.l1 = "Were you eavesdropping again, Dannie?";
			link.l1.go = "SnakeEye_1";
		break;
		
		case "SnakeEye_1":
			dialog.text = "Well... a bit. You know, we women are just like that. But you must understand - I just worry about my husband. I actually love him. So what if I am eavesdropping? Anyway, did you get anything useful?";
			link.l1 = "I am trying to think... it wasn't easy to understand Snake Eye. However, it seems that the idol which we've seen on our way into the village is some sort of magic portal that can teleport people.";
			link.l1.go = "SnakeEye_2";
		break;
		
		case "SnakeEye_2":
			dialog.text = "";
			link.l1 = "Don't look at me like that. It's not my idea and so far I've got no problems with my head. You asked me what shaman told me, so I am telling you.";
			link.l1.go = "SnakeEye_3";
		break;
		
		case "SnakeEye_3":
			dialog.text = "Please, excuse me. I won't look at you like that anymore. Go on.";
			link.l1 = "He said that when Nathan was almost caught by his pursuers, the Indian showed him the statue as a way of rescue, calling it Kukulcan and saying that it ate Nathan alive and spat him out somewhere. To put it simply, it seems that Nathan was teleported by the statue.";
			link.l1.go = "SnakeEye_4";
		break;
		
		case "SnakeEye_4":
			dialog.text = "God, what the... Me and Nathan have already been in a similar mess before and now it happens again. We had enough aventures with that Indian temple filled with Maya magic...";
			link.l1 = "What did you just say?";
			link.l1.go = "SnakeEye_5";
		break;
		
		case "SnakeEye_5":
			dialog.text = "Ah, it's nothing, "+pchar.name+", it doesn't matter. Just memories of my heated youth. But how was Nathan able to do that? I mean to teleport? We have just been near that idol, I was walking around it and touching it... it's only a stone!";
			link.l1 = "Snake Eye told me that the idol comes to life at midnight. Only then it starts to glow in a golden color, when the spirit of Kukulcan gets into it. That's the time when you shouldn't touch it. Or conversely should...";
			link.l1.go = "SnakeEye_6";
		break;
		
		case "SnakeEye_6":
			dialog.text = "Creepy... Now what? Let's wait until midnight and go to the jungle then?";
			link.l1 = "No. The shaman said that the idol not only teleports people but also eats their lives. As far as I understood him, me meant that it drains their health. Snake Eye has passed through these statues three times and has healed himself with some unique potion after every teleportation.";
			link.l1.go = "SnakeEye_7";
		break;
		
		case "SnakeEye_7":
			dialog.text = "Have you asked him for this potion?";
			link.l1 = "Sure. But firstly, there are only three flasks left and, secondly, he demanded three amulets in exchange for them.";
			link.l1.go = "SnakeEye_8";
		break;
		
		case "SnakeEye_8":
			dialog.text = "How about doing this without the potion? Let's go to the statue at night and touch it...";
			link.l1 = "Too risky. I am conceding that the Indian is a bit out of his mind and fooling us, but he doesn't look like a psychopath, so I believe he is telling the truth. I recall that you were telling me something about Indian magic... Do you doubt its existence?";
			link.l1.go = "SnakeEye_9";
		break;
		
		case "SnakeEye_9":
			dialog.text = "Yes, I was. I don't doubt it because I saw it with my own eyes. So, I suppose you are right, there is no point in risking it.";
			link.l1 = "Exactly. That is why we will find the amulets first, then get that wonderful potion from the shaman and go to the statue. I will go. Alone.";
			link.l1.go = "SnakeEye_10";
		break;
		
		case "SnakeEye_10":
			dialog.text = "Why is that? And what about me?";
			link.l1 = "You will stay on my ship and you'll be in charge while I am away. Don't even try to argue, Dannie. There are only three flasks of the potion. It is unknown where the portal leads to in case the shaman is right and this thing works for real. Perhaps, I won't be even able to find Nathan there.";
			link.l1.go = "SnakeEye_11";
		break;
		
		case "SnakeEye_11":
			dialog.text = "You are just like Nathan. All men are the same... Fine, I agree.";
			link.l1 = "It is good that we understand each other. Let's go now, we need to find the amulets.";
			link.l1.go = "Dolly_4";
			
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.GiveAmulets")) {
				DeleteAttribute(pchar, "questTemp.HelenDrinking.GiveAmulets");
				if (CheckAttribute(pchar, "questTemp.Saga.HelenRelation") && sti(pchar.questTemp.Saga.HelenRelation) > 6) {
					AddDialogExitQuestFunction("HelenDrinking_GivePotionsDlg");
				}
			}
		break;
		
		// перед походом к истукану
		case "teleport":
			dialog.text = "So what? Did you get the potions?";
			link.l1 = "Yes. I got the potions and some instructions. The one thing left to do is to go to the idol at midnight and touch it.";
			link.l1.go = "teleport_1";
		break;
		
		case "teleport_1":
			dialog.text = "Are you afraid?";
			link.l1 = "Yes. I am afraid that the shaman may turn out to just be crazy and no teleportation will happen.";
			link.l1.go = "teleport_2";
		break;
		
		case "teleport_2":
			dialog.text = "Well-well... Aren't you really scared? Not even a little bit?";
			link.l1 = "Dannie, don't push me... If you really want to know, then sure, I am not feeling too confident, I must confess.";
			link.l1.go = "teleport_3";
		break;
		
		case "teleport_3":
			dialog.text = "I will go with you.";
			link.l1 = "Are you going to start arguing again? I thought we had a deal...";
			link.l1.go = "teleport_4";
		break;
		
		case "teleport_4":
			dialog.text = "You got me wrong. I will only stay near you. I will have to make sure that the statue works... or that it doesn't.";
			link.l1 = "I have got no objections. But don't even think to follow me in case the statue 'eats' me. Do you hear me?";
			link.l1.go = "teleport_5";
		break;
		
		case "teleport_5":
			dialog.text = "I do. I promise that I won't follow you... Captain.";
			link.l1 = "Good. And, Dannie, it seems that you are not as much of a bitch as they say.";
			link.l1.go = "teleport_6";
		break;
		
		case "teleport_6":
			dialog.text = "You don't know me too well, "+pchar.name+". But let's not talk about that now.";
			link.l1 = "Let's not... Well, we should prepare ourselves for our nightly trip!";
			link.l1.go = "Dolly_4";
			npchar.quest.talk = "shadowstar";
			pchar.quest.Saga_Dolly1.win_condition.l1 = "location";
			pchar.quest.Saga_Dolly1.win_condition.l1.location = "Pearl_jungle_03";
			pchar.quest.Saga_Dolly1.win_condition.l2 = "Hour";
			pchar.quest.Saga_Dolly1.win_condition.l2.start.hour = 0.00;
			pchar.quest.Saga_Dolly1.win_condition.l2.finish.hour = 1.00;
			pchar.quest.Saga_Dolly1.function = "Saga_DannyTalk";
			
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.GiveAmulets")) {
				DeleteAttribute(pchar, "questTemp.HelenDrinking.GiveAmulets");
				if (CheckAttribute(pchar, "questTemp.Saga.HelenRelation") && sti(pchar.questTemp.Saga.HelenRelation) > 6) {
					AddDialogExitQuestFunction("HelenDrinking_GivePotionsDlg");
				}
			}
		break;
		
		// перед телепортацией
		case "shadowstar":
			dialog.text = "Look, "+pchar.name+"! I swear by all that's holy, there is an odd light above the statue!";
			link.l1 = "It seems that the shaman wasn't lying. And, if the dark doesn't deceive me, the top of the statue doesn't look that stony anymore.";
			link.l1.go = "shadowstar_1";
			QuestPointerDelLoc("Pearl_Jungle_02", "reload", "reload1_back");
			QuestPointerDelLoc("Pearl_Jungle_03", "camera", "dolly");
		break;
		
		case "shadowstar_1":
			dialog.text = "Exactly... It looks like it is made of pure gold! Incredible!";
			link.l1 = "The time has come, Dannie. Wish me luck and cross your fingers for me. Don't go close to the idol! Stay here.";
			link.l1.go = "shadowstar_2";
		break;
		
		case "shadowstar_2":
			dialog.text = "Good luck, "+pchar.name+". Let's hope that this will work... Have you prepared the shaman's potion?";
			link.l1 = "Yes, I have it here. All will be fine, Dannie. Well, here I go! (Press T to activate the idol)";
			link.l1.go = "shadowstar_3";
		break;
		
		case "shadowstar_3":
			DialogExit();
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			DoQuestReloadToLocation(pchar.location, pchar.location.group, pchar.location.locator, "");
		break;
		
		// прибыл назад 
		case "arrive":
			dialog.text = "A-a-ah?! Fuck! What kind of monster are you, god-damn it?! Screw you! I have seen worse creatures in my life including Van der Decken himself! Now I'll give you what you're asking for!";
			link.l1 = "(faintly) Dannie, wait! Stop it! Now!";
			link.l1.go = "arrive_1";
		// belamour legendary edition -->
			link.l2 = "(faintly) Van der Decken? Uh-ha-ha-ha! That worm already serves me! Now it's your turn! Bow before me, faithful servant! You will lead my army of the dead!";
			link.l2.go = "arrive_1a";
			SetMusic("music_jungle");
			if (CheckCharacterItem(pchar, "Ultimate_potion"))
			{
				pchar.systeminfo.NoNotifications = true;
				RemoveItems(pchar, "Ultimate_potion", 1);
				DeleteAttribute(pchar,"systeminfo.NoNotifications");
				notification("A Comanche potion is used", "None");
				LAi_SetCurHPMax(PChar);
				AddCharacterHealth(pchar, 50);
				DeleteAttribute(pchar, "chr_ai.poison");
				notification("You are feeling that your health is restored!", "None");
				//Log_Info("A Comanche potion is used");
				//Log_Info("You are feeling that your health is restored!");
				//PlaySound("Ambient\Tavern\glotok_001.wav");
				PlaySound("Ambient\Horror\Fear_breath_01.wav");
			}
		break;
		
		case "arrive_1a":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddCharacterExpToSkill(pchar, "Sneak", 100);
			dialog.text = "A-A-A-A-A-A-A-A-A-A-A-A-A! Go away! This can't be happening right now!";
			link.l1 = "(faintly) Dannie, wait! Stop it! Now!";
			link.l1.go = "arrive_1";
		break;
		// <-- legendary edition
		case "arrive_1":
			dialog.text = "Ah?! What did you say?! Dannie?";
			link.l1 = "(faintly) Stop it immediately! Hold your saber! Let me take this thing off!";
			link.l1.go = "arrive_2";
		break;
		
		case "arrive_2":
			dialog.text = "Damn, you monster sound like... "+pchar.name+"?!";
			link.l1 = "(faintly) Oh-oh... You don't say!";
			link.l1.go = "arrive_3";
		break;
		
		case "arrive_3":
			DialogExit();
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			DoQuestCheckDelay("Pearl_TeleportArrive_1", 1.5);
		break;
		
		case "arrive_4":
			dialog.text = "The fuck, you almost scared me to death! I was so close to chopping you down with my saber!";
			link.l1 = "I saw that... and why are you so fiery, huh?";
			link.l1.go = "arrive_5";
		break;
		
		case "arrive_5":
			dialog.text = "That is who I am... Oh, my heart is still beating right out of my chest...";
			link.l1 = "Dannie, where are we now? Not far from the Miskito village, right?";
			link.l1.go = "arrive_6";
		break;
		
		case "arrive_6":
			dialog.text = "Where else could we be! This is the statue that made you disappear. That was spectacular! I will remember that for the rest of my life.";
			link.l1 = "I see, you have been waiting for me here ever since?";
			link.l1.go = "arrive_7";
		break;
		
		case "arrive_7":
			dialog.text = "Tell me, what else was I supposed to do? After the statue had eaten you, I could only hope that one day it would spit you back out. Besides, Snake Eye said that this is what most likely would happen.\nI lived with the Miskito and watched the idol every day. Why are we even talking about such hogwash? Tell me! What happened out there? Where have you been?";
			link.l1 = "Dannie, this story is way too long, I have seen so much... But to get it off your chest, I'll tell you that I have found Nathaniel!";
			link.l1.go = "arrive_8";
		break;
		
		case "arrive_8":
			dialog.text = "Have you found Nathan? Where is he? And how is he?!";
			link.l1 = "I won't lie - he is alive but he is really badly feeling. He had no potion of the Comanche and the idol has drained all of his health. He is lying in a cabin of some old and broken vessel at the strange Island of the Abandoned Ships. I was teleported there too, so Snake Eye was right!";
			link.l1.go = "arrive_9";
		break;
		
		case "arrive_9":
			dialog.text = "Poor Nathan... Where is that damn island? How do we get there?! Through the idol only? I will try to buy every single health potion from the Miskito and go there this night! I will make it somehow...";
			link.l1 = "Stop! Wait! Nathan is ill but there is no threat to his life. One lad is looking after him and feeding him. If you go through the idol, you will ruin your health and the Island is really dangerous. It is too risky!";
			link.l1.go = "arrive_10";
		break;
		
		case "arrive_10":
			dialog.text = "So what are you suggesting? To do nothing while Nathan is suffering or dying perhaps?";
			link.l1 = "Stop being hysterical. Firstly, I told you that Nathan is ill but not dying. I have spoken to him. Secondly, I am going to sail to the Island and you will go with me.";
			link.l1.go = "arrive_11";
		break;
		
		case "arrive_11":
			dialog.text = "Do you know where that Island is?";
			link.l1 = "Sure, I do! I have found there not only Nathan but also Shark Dodson. I have got the approximate coordinates of the Island and sailing directions to bypass the reefs around it. And now we are going back to my ship and sail to Blueweld...";
			link.l1.go = "arrive_12";
		break;
		
		case "arrive_12":
			dialog.text = "For what purpose? Why can't we sail straight to the Island now?";
			link.l1 = "Dannie, I need to organize an expedition. There is a huge lack of provisions on the Island, so I will buy as much food as I can. Then I will have to choose a ship to sail there, not all ships will be able to bypass the Island's reefs. And I also want to talk with Svenson first...";
			link.l1.go = "arrive_13";
		break;
		
		case "arrive_13":
			dialog.text = "";
			link.l1 = "It won't take very long to prepare. The Island is not far from here, it's north-west from Havana, east to the Gulf of Mexico.";
			link.l1.go = "arrive_14";
		break;
		
		case "arrive_14":
			dialog.text = "Fine... let's do this then. You have found Nathan and that's the most important thing. Thank you! Is he feeling badly there?";
			link.l1 = "Well... he is ill. And in addition to that he is also depressed and desperate. He misses you. And yes, Nathan asked me to tell you that he loves you very much.";
			link.l1.go = "arrive_15";
		break;
		
		case "arrive_15":
			dialog.text = "(wiping away a tear) Old fool! He never listened to me... "+pchar.name+", let's head to your ship! I want to sail there as quickly as possible!";
			link.l1 = "Sure, Dannie. And I will tell you about my adventures. Let's go!";
			link.l1.go = "Dolly_4";
			AddQuestRecord("BaronReturn", "9");
			LAi_LocationDisableOfficersGen("Pearl_jungle_03", false); // пускать офицеров в локу телепорта
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			setCharacterShipLocation(pchar, "Shore9"); // калеуче
			setWDMPointXZ("Shore9"); // корабль в бухту Аматике
			bNoEatNoRats  = false; // еду и крыс включить
			
			AddDialogExitQuestFunction("HelenDrinking_JungleDialog");
		break;
		
		// в LSC у причала
		case "nathaniel":
			dialog.text = "I have never seen a place like this one before. The whole island is made of ships!";
			link.l1 = "I told you about it, Dannie...";
			link.l1.go = "nathaniel_1";
		break;
		
		case "nathaniel_1":
			dialog.text = "But now I can see it with my own eyes. Anyway, tell me where to find Nathaniel?";
			link.l1 = "He is inside one of the ships. But you must swim there.";
			link.l1.go = "nathaniel_2";
		break;
		
		case "nathaniel_2":
			dialog.text = "I don't care. Tell me how to get to this ship.";
			link.l1 = "Dannie, calm down. You and Nathan have been waiting for a long time so just have a bit more patience! I will lead you to him, you will never find him yourself. I don't want you to run into the Narwhals or Rivados, you will start to argue with them and it won't end well.";
			link.l1.go = "nathaniel_3";
		break;
		
		case "nathaniel_3":
			dialog.text = "Fine, let's go then. I will follow you.";
			link.l1 = "Don't forget that we will have to swim a lot.";
			link.l1.go = "nathaniel_4";
		break;
		
		case "nathaniel_4":
			dialog.text = "It's fine, I can handle it.";
			link.l1 = "Glad to hear that... You will see your husband soon!";
			link.l1.go = "nathaniel_5";
		break;
		
		case "nathaniel_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.LSC_Danny_Natan.win_condition.l1 = "location";
			pchar.quest.LSC_Danny_Natan.win_condition.l1.location = "FernandaDiffIndoor";
			pchar.quest.LSC_Danny_Natan.function = "LSC_DannyAndNatan";
			AddQuestRecord("LSC", "15");
			// следующая нода
			if (CheckCharacterItem(pchar, "keys_skel")) // идёт Оле
			{
				sld = characterFromId("Ole");
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else
			{
				if (GetCharacterIndex("Mary") != -1) // иначе Мэри
				{
					sld = characterFromId("Mary");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else // иначе завершение
				{
					chrDisableReloadToLocation = false;
					LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				}
			}
		break;
		
		case "nathaniel_6":
			dialog.text = "Nathaniel... Nathan! Damn it! My love...";
			link.l1 = "...";
			link.l1.go = "nathaniel_7";
		break;
		
		case "nathaniel_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			SetMusic("music_romantic");
			bDisableCharacterMenu = true;//лоченые интерфейсы
			locCameraRotateAroundHero(0.0, 2.0, 0.0, 0.005, 0.0, 2.0, 0.0, 1000);
			Pchar.FuncCameraFly = "";
			DoQuestCheckDelay("LSC_DanielleRomantic", 15.0);
		break;
		
		case "nathaniel_8":
			dialog.text = "Jesus, just look at yourself... Why did you do that to yourself?!..(crying) You never listen to me, never! I told you not to go into that selva! But you have gone there anyway! Why Nathan?!";
			link.l1 = "Dannie... I am sorry. I had no choice, you know that...";
			link.l1.go = "nathaniel_9";
		break;
		
		case "nathaniel_9":
			sld = characterFromId("Blaze");
			dialog.text = "I know that! Oh, God, darling... what has happened to you! (through tears) It is alright, darling, everything is gonna be alright... I am here. We will take you to the Miskito, to Snake Eye. "+sld.name+"  told me that the shaman will be able to heal you. We have got a ship... Everything is going to be fine!";
			link.l1 = "Dannie, dear... my love! Your presence only has half healed me. We will go wherever you say. If it is to Snake Eye, then to him.";
			link.l1.go = "nathaniel_10";
		break;
		
		case "nathaniel_10":
			dialog.text = "Pack up your things. Oh, I am so stupid... There are no things to pack except empty bottles. Nathan...";
			link.l1 = "Dannie...";
			link.l1.go = "nathaniel_11";
		break;
		
		case "nathaniel_11": // перекидываем pchar
			DialogExit();
			LAi_SetStayType(pchar);
			DeleteAttribute(pchar, "GenQuest.MusicContinue");
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "nathaniel_12";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "nathaniel_12":
			dialog.text = ""+pchar.name+" ... forgive me and Nathan for the scene.";
			link.l1 = "Dannie! Forgive you for what? It is alight. Are you ashamed of your feelings?";
			link.l1.go = "nathaniel_13";
		break;
		
		case "nathaniel_13":
			dialog.text = "No, I am not... It's just...";
			link.l1 = "No one will never know about this scene. I promise. And no one will know what happened to Nathan. The pirates of Maroon Town will see a strong and formidable Nathaniel Hawk!";
			link.l1.go = "nathaniel_14";
		break;
		
		case "nathaniel_14":
			dialog.text = "Thank you, "+pchar.name+"! I owe you... I will take my husband to the ship. Don't worry, I will manage to bring him there, I remembered the way. I will put him into a bed and I will stay with him. We'll sail to Snake Eye after you are done with everything you need to do here. I believe in his ability to heal Nathan.";
			link.l1 = "Fine, Dannie. We won't stay here for long anyway. Are you sure that you don't need help?";
			link.l1.go = "nathaniel_15";
		break;
		
		case "nathaniel_15":
			dialog.text = "I am sure. We will reach the ship. Don't worry, I won't let my husband die!";
			link.l1 = "Dannie, you are... wonderful!";
			link.l1.go = "nathaniel_16";
		break;
		
		case "nathaniel_16":
			dialog.text = "(brushing away a tear) Go... just go, "+pchar.name+"... and please don't waste any time here!";
			link.l1 = "...";
			link.l1.go = "nathaniel_17";
		break;
		
		case "nathaniel_17":
			chrDisableReloadToLocation = false;//открыть локацию
			bDisableCharacterMenu = false;//лоченые интерфейсы
			EndQuestMovie();
			DialogExit();
			pchar.quest.LSC_NatanPassenger.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LSC_NatanPassenger.win_condition.l1.location = pchar.location;
			pchar.quest.LSC_NatanPassenger.function = "LSC_SetNatanPassenger";
			pchar.quest.Saga_NatanTreatment.win_condition.l1 = "location";
			pchar.quest.Saga_NatanTreatment.win_condition.l1.location = "Miskito_village";
			pchar.quest.Saga_NatanTreatment.function = "Saga_NatanPrepareTreatment";
			pchar.questTemp.Saga.BaronReturn = "shamane";
			AddQuestRecord("BaronReturn", "11");
			// открываем вход к Мэри
			if (GetCharacterIndex("Mary") != -1)
			{
				for (i=0; i<=3; i++)
				{
					LocatorReloadEnterDisable("LostShipsCity_town", "reload6"+i, false);
				}
			}
			else
			{
				bQuestDisableMapEnter = false; //открыть карту
				DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			}
		break;
		
		case "treatment":
			dialog.text = "So what? Will he heal my husband? Tell me that he will heal him!";
			link.l1 = "Dannie, Nathan will have to stay here. Alone. The shaman asked to not bother his rites. That concerns you too. He has promised to heal Nathaniel within a month.";
			link.l1.go = "treatment_1";
		break;
		
		case "treatment_1":
			dialog.text = "You know, "+pchar.name+", now I can finally breath freely again. I strongly believe that the shaman will bring my husband back to his normal state. I will leave Nathan here unhesitatingly because if Snake Eye won't be able to heal him - no one will.";
			link.l1 = "Everything will be alright, Dannie. Snake Eye has never lied to me. I trust him.";
			link.l1.go = "treatment_2";
		break;
		
		case "treatment_2":
			dialog.text = "So do I. I will stay with you for a while, "+pchar.name+", are you fine about that? We still have to find that bastard Jackman, after all, he is responsible for all our troubles. He organized the ambush! He took Nathan's place in Maroon Town! He stole our frigate 'Centurion'!";
			link.l1 = "Agreed. We have to deal with Jackman. Not one of us is safe until Jackman is dead. It won't be easy to kill him though.";
			link.l1.go = "treatment_3";
		break;
		
		case "treatment_3":
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Shark Dodson";
			else sTemp = "Marcus Tyrex";
			dialog.text = "Got any plans, "+pchar.name+"?";
			link.l1 = "Not yet. I need to go to Jan Svenson and ask him for advice. Let's do one thing after another, we have to promote "+sTemp+" to head of the Brethren of the Coast first. So, we need to get a vote from every pirate baron to do that.";
			link.l1.go = "treatment_4";
		break;
		
		case "treatment_4":
			dialog.text = "Fine, Let's go to Svenson. Let's listen to what that old fogy says...";
			link.l1 = "You know, you shouldn't be so negative towards Jan. Actually, it would be a lot better if you made peace with him... after all, we all share the goal!";
			link.l1.go = "treatment_5";
		break;
		
		case "treatment_5":
			dialog.text = "But only because I respect you... Fine, "+pchar.name+", I am sorry. I didn't mean to insult Svenson, I am just nervous. It won't happen again.";
			link.l1 = "Good. Dannie, everything will be fine. I can promise you that!";
			link.l1.go = "treatment_6";
		break;
		
		case "treatment_6":
			dialog.text = "I absolutely trust you, "+pchar.name+". Let's go to Svenson?";
			link.l1 = "Let's go, Dannie!";
			link.l1.go = "Dolly_4";
			AddQuestRecord("BaronReturn", "13");
		break;
		
		case "islatesoro":
			dialog.text = "Yes? I am listening. How can I help you?";
			link.l1 = "Do you have any ideas where Jackman might hide? You know this bastard better than I do. Perhaps he has got some place, a base...";
			link.l1.go = "islatesoro_1";
		break;
		
		case "islatesoro_1":
			dialog.text = "Damned if I know! Jacob was always very secretive. I have never heard about a lair of his. It's probably better to try to think logically... Let's read the letter that you got from Knive again. We might find some clue in there.";
			link.l1 = "Let's try...";
			link.l1.go = "islatesoro_2";
		break;
		
		case "islatesoro_2":
			RemoveItems(pchar, "letter_chad", 1);
			dialog.text = "Well... it mentions Isla Tesoro and some testament... Does that sound familiar to you?";
			link.l1 = "Me and Jan think that Blaze Sharp was killed by Jackman on Isla Tesoro and Shark was blamed for it. And a testament... a bitch... it must be about Helen... Damn it, how didn't I get it before! This bastard must be sailing near Isla Tesoro!";
			link.l1.go = "islatesoro_3";
		break;
		
		case "islatesoro_3":
			dialog.text = "Let's not waste our time then, "+pchar.name+"?";
			link.l1 = "Yes. Let's go to Isla Tesoro. The old 'Marlin' will help us in this raid.";
			link.l1.go = "islatesoro_4";
		break;
		
		case "islatesoro_4":
			DialogExit();
			AddQuestRecord("BarbTemptation", "18");
			pchar.questTemp.Saga.BarbTemptation = "islatesoro";
			// ставим прерывание на Исла-Тесоро
			pchar.quest.Saga_AttackJackman.win_condition.l1 = "location";
			pchar.quest.Saga_AttackJackman.win_condition.l1.location = "Bermudes";
			pchar.quest.Saga_AttackJackman.function = "Saga_CheckJackmanBermudes";
		break;
		
		case "after_boarding":
			dialog.text = "That bastard is dead at last... I can't believe it - I am standing on the deck of the 'Centurion' again! I know every nail on here and it looks like the ship has recognized me too.";
			link.l1 = "She is yours again, Dannie. Yours and Nathaniel's.";
			link.l1.go = "after_boarding_1";
		break;
		
		case "after_boarding_1":
			PlaySound("Voice\English\saga\Denny Hawk-03.wav");
			dialog.text = "You can't even imagine how glad I am. Nathaniel used to talk about our ship often, he will be glad to know that she is ours once again.";
			link.l1 = "What are you going to do now, Dannie?";
			link.l1.go = "after_boarding_2";
		break;
		
		case "after_boarding_2":
			dialog.text = "Me? I will take the ship to Sharp town, hire at least the minimum crew and sail to Blueweld. I will ask Jan Svenson to look after the 'Centurion', go to the Miskito people and wait there until Snake Eye has healed my husband.";
			link.l1 = "Are you really going to visit Jan Svenson? I am surprised...";
			link.l1.go = "after_boarding_3";
		break;
		
		case "after_boarding_3":
			dialog.text = ""+pchar.name+", it is all your merit. I've been thinking about your words: 'we all share the same goal'. Remember? I want to make peace with Svenson, he has helped return Nathan back to me after all. It's time to stop arguing.";
			link.l1 = "Wise words, Dannie! Nathaniel will be able to retake his position in Maroon Town as soon as he feels better.";
			link.l1.go = "after_boarding_4";
		break;
		
		case "after_boarding_4":
			dialog.text = "Maybe... the thing is, pirate baron is an elective office. What if the others decide against it?";
			link.l1 = "Let Svenson deal with it. He can persuade anyone. The elimination of Jackman will play its role too.";
			link.l1.go = "after_boarding_5";
		break;
		
		case "after_boarding_5":
			dialog.text = "Fine. I need to make Svenson my friend anyway... "+pchar.name+"! I want to thank you for all that you have done for me and Nathan. You have saved my husband and gave us back everything we had lost. I owe you.";
			link.l1 = "Come on, Dannie. We are friends.";
			link.l1.go = "after_boarding_6";
		break;
		
		case "after_boarding_6":
			dialog.text = "I want you to know that we will always be glad to see you in Maroon Town. Find us there when you'll have some time. Nathaniel and me will find a way to reward you.";
			link.l1 = "Good heavens, Dannie! I accept your invitation with pleasure. We'll sit, drink and talk about how you and Nathan have sunk Van der Decken...";
			link.l1.go = "after_boarding_7";
		break;
		
		case "after_boarding_7":
			dialog.text = "Did he tell? Oh, don't remind me about it...";
			link.l1 = "Fine, Dannie. You've got a lot of work ahead of you and I have to visit our sworn friends - Marcus and Barbazon. I hope you will let me topsy-turvy this cabin, I am sure there are a lot of interesting things in Jackman's chests.";
			link.l1.go = "after_boarding_8";
		break;
		
		case "after_boarding_8":
			dialog.text = "Sure, do you really think that I would object?";
			link.l1 = "Nice. Actually it's a pity to part with you, Dannie... See you in Maroon Town!";
			link.l1.go = "after_boarding_9";
		break;
		
		case "after_boarding_9":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			LAi_SetHP(npchar, 280, 280); 
			LAi_SetImmortal(npchar, false); // если сработало
			pchar.GenQuest.CannotTakeShip = true; // нельзя захватить
			DoQuestFunctionDelay("Saga_CheckJackmanCabinItems", 5.0); // первая проверка через 5 сек
			AddCharacterExpToSkill(pchar, "Leadership", 300);
		break;
		
		// в Марун-Тауне
		case "marun_town":
			dialog.text = ""+pchar.name+", I am very glad to see you! We are back in Maroon Town and Nathan is at his rightful place again. Actually, everyone in the village is happy about it. Now all will go just as well as it used to! I am very grateful for your unselfish help!\nI want to give you a gift. Here, take it. This talisman can make a fight so much easier for you. And this formula will allow you to make more of them for yourself.";
			link.l1 = "Thanks, Dannie!";
			link.l1.go = "marun_town_1";
		break;
		
		case "marun_town_1":
			GiveItem2Character(pchar, "totem_12"); 
			GiveItem2Character(pchar, "recipe_totem_12"); 
			Log_Info("You have received a talisman");
			Log_Info("You have received the recipe of the talisman");
			PlaySound("interface\important_item.wav");
			dialog.text = "It's not all. I have also found two chests filled with gold here. They were Jackman's property no doubt. Take them as a token of my gratitude. And don't dare to refuse! I know how much money you have wasted to help me and Nathan.";
			link.l1 = "Fine, fine, Dannie, I accept them!";
			link.l1.go = "marun_town_2";
		break;
		
		case "marun_town_2":
			TakeNItems(pchar, "chest", 2); 
			Log_Info("You have received two chests with doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Excellent! "+pchar.name+", I want you to know that you are our best friend from now on. Nathan and me will always be glad to see you in Maroon Town! See us more often!";
			link.l1 = "Thanks! I will be glad to see you again, so expect me!";
			link.l1.go = "exit";
			NextDiag.TempNode = "marun_town_3";
		break;
		
		case "marun_town_3":
			if (CheckAttribute(pchar, "GenQuest.MaruntownSex"))
			{
				dialog.text = "What can we do for you, "+pchar.name+"?";
				link.l1 = "Alas, I'm just leaving... Goodbye, Danny.";
				link.l1.go = "exit";
				if (CheckAttribute(pchar, "GenQuest.MaruntownSex2"))
				{
					dialog.text = "And here is "+GetFullName(pchar)+". You can tell by your face that you haven't wasted any time!";
					link.l1 = "I must admit, you know how to have fun! Thank you, I had a great time.";
					link.l1.go = "marun_town_fuckgirl_3";
				}
				NextDiag.TempNode = "marun_town_3";
				break;
			}
			bOk1 = CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && IsOfficer(characterFromId("Mary"));
			bOk2 = CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && IsOfficer(characterFromId("Helena"));
			dialog.text = "I am glad to see you, "+pchar.name+"! Rum, wine? Or a girl?";
			link.l1 = "Thanks, Dannie! I just wanted to see you...";
			link.l1.go = "exit";
			if (bOk1 || bOk2)
			{
				link.l2 = "The girl? Quiet, Danny! You don't want to find me cut into pieces and neatly folded at your doorstep, do you? Ha-ha. My faithful lady, who is standing right outside the door, will not forgive me for such cantrips.";
				link.l2.go = "marun_town_fuckgirl_Otkaz_1";
			}
			else
			{
				link.l2 = "A girl? That sounds interesting, Danny. I've been yearning for... the woman's heartbeat... I think I should take a look - you wouldn't suggest just anyone, would you?";
				link.l2.go = "marun_town_fuckgirl_1";
			}
			NextDiag.TempNode = "marun_town_3";
		break;
		
		// Данни предлагает девочку
		case "marun_town_fuckgirl_Otkaz_1":
			dialog.text = "Really? Why are you so pale? Ha-ha, I was just kidding. Take care of her, do you hear?";
			link.l1 = "Of course. She is more precious to me than all the treasures in these parts!";
			link.l1.go = "marun_town_fuckgirl_Otkaz_2";
		break;
		
		case "marun_town_fuckgirl_Otkaz_2":
			dialog.text = "That's better, ha-ha. Come on, go already, your darling is probably getting nervous.";
			link.l1 = "Goodbye, Danny. And thank you for your concern, ha-ha.";
			link.l1.go = "exit";
		break;
		
		case "marun_town_fuckgirl_1":
			dialog.text = "I assure you, this young beauty definitely knows how to give you an unforgettable time, "+pchar.name+". Have fun! She'll be waiting for you in the tavern room.";
			link.l1 = "Thank you, Danny. I'm on my way. I don't want to waste a minute!";
			link.l1.go = "marun_town_fuckgirl_2";
		break;
		
		case "marun_town_fuckgirl_3":
			dialog.text = ""+pchar.name+", you are always welcome in Maroon Town. The best girls are yours!";
			link.l1 = "Oh, Danny. I swear, this is my second home.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.MaruntownSex2");
			
		break;
		
		case "marun_town_fuckgirl_2":
			DialogExit();
			pchar.GenQuest.MaruntownSex = "true";
			SetTimerCondition("MarunFuckGirl_4", 0, 0, 2, false);
			LocatorReloadEnterDisable("FortOrange_tavern", "reload2_back", false); //открыть комнату
			sld = GetCharacter(NPC_GenerateCharacter("MarunFuckGirl", "women_2"+(rand(6)), "woman", "woman", 1, PIRATE, 1, false, "quest"));
			sld.Dialog.Filename = "Quest\Saga\Danielle.c";
			sld.dialog.currentnode = "MarunFuckGirl";
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "FortOrange_tavern_upstairs", "goto", "goto1");
		break;
		
		// Диалог с проституткой
		case "MarunFuckGirl":
			dialog.text = "And here is my captain. Today you are only mine! Come to me, I have been waiting for you for so long...";
			link.l1 = "Oh, is that so? You can't wait any longer? Well, let's not waste time!";
			link.l1.go = "MarunFuckGirl_2";
			LocatorReloadEnterDisable("FortOrange_tavern", "reload2_back", true); //закрыть комнату
			chrDisableReloadToLocation = true;
		break;
		
		case "MarunFuckGirl_2":
			DialogExit();
			
			StartQuestMovie(true, false, true);
			LAi_SetActorType(pchar);
			LAi_Fade("MarunFuckGirl", "");
			pchar.GenQuest.MaruntownSex2 = "true";
		break;
		
		case "MarunFuckGirl_3":
			dialog.text = RandPhraseSimple("My captain... you really know how to conquer ladies! I've never had anything like that before! Maybe you'll stay for a couple hours more?", "Are you leaving already, my dear?");
			link.l1 = RandPhraseSimple("I knew you wouldn't want to let me go so easily. Goodbye, baby. Great things await me...", "Alas, work gets in the way. But perhaps we will meet again...");
			link.l1.go = "MarunFuckGirl_4";
		break;
		
		case "MarunFuckGirl_4":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
		break;
		
	// ------------------------------------------- провалы Саги ------------------------------------------------
		case "failcenturion":
			dialog.text = "At last me and Nathan can breath freely again! This damn bastard Jackman is dead! I feel bad for the 'Centurion' but I have already accepted her loss when that bastard had stolen her from me. So I don't worry too much.";
			link.l1 = "But I do. I am an idiot! All evidence has sunk to the bottom of the sea along with the ship. It could have helped us in the vote for the new head of the Brethren of the Coast. Now... it's all gone.";
			link.l1.go = "failcenturion_1";
		break;
		
		case "failcenturion_1":
			dialog.text = "Don't get too upset! It happens. Next time you will be more lucky... Whatever. I want to thank you for what you've done for me and Nathan. You have saved my husband's life. I owe you a great deal.\nI want you to know that Maroon Town will always be glad to see you. Check on me and Nate there, when you have the time. We will find a way to repay you.";
			link.l1 = "Fine, Dannie. I will visit you for sure. Are you leaving already?";
			link.l1.go = "failcenturion_2";
		break;
		
		case "failcenturion_2":
			dialog.text = "Yes, I will go to the Miskito, I hope that Snake Eye has already healed Nathan. Then we will return to Maroon Town.";
			link.l1 = "Heh, I'm already so used to you, it's too bad that I have to part with you... Good luck, Dannie!";
			link.l1.go = "failcenturion_3";
		break;
		
		case "failcenturion_3":
			DialogExit();
			RemovePassenger(pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "Saga_FailCenturion", 10.0);
			npchar.greeting = "danny_2";
		break;
		
		case "before_kiss":
			dialog.text = "Oh, don't play dumb, sweetheart. Charles, this love bug walked circles around that idol day and night, and kept pestering the poor Snake Eye with questions. And then she ran home and brought him something, isn't that right?";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JungleDialog2");
		break;
		
		case "after_kiss":
			dialog.text = "Oh, thanks for the show, Charles. The whole Maroon Town will be gossiping about it, ha-ha!";
			link.l1 = "I have no doubt that it's your new priority - to make sure it happens.";
			link.l1.go = "after_kiss_1";
		break;
		
		case "after_kiss_1":
			dialog.text = "At the very bottom of my list, actually. Don't be mad at the girl - it's her first time. When Nathan and I had our adventures, the whole archipelago was laughing at us too.";
			link.l1 = "Let's change the topic and the mood. I'm done with this idol, let's go.";
			link.l1.go = "after_kiss_2";
		break;
		
		case "after_kiss_2":
			dialog.text = "Agreed, let's go, hero.";
			link.l1 = "";
			link.l1.go = "Dolly_4";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterKiss3");
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Danielle_officer":
			dialog.text = "What do you want, Captain?";
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "danielle")
			{
				Link.l3 = "Dannie, I want to ask you for advice!";
				Link.l3.go = "islatesoro";
			}
			Link.l1 = "Listen to my order!";
            Link.l1.go = "stay_follow";
			link.l2 = "It's nothing. Dismissed!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Danielle_officer";
			sld = characterFromId("Danielle");
		    sld.HoldEquip = true; // лесник -  не отдавать саблю и пистоль для текущей игры. поэтому так . другого способа не нашёл						 
		break;
		
		case "stay_follow":
            dialog.Text = "Orders?";
            Link.l1 = "Stand here!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Follow me and keep up!";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Change the type of ammo for your firearms.";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Choosing the type of ammo:";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;		
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "There is change of disposition!";
            Link.l1 = "Dismissed.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "There is change of disposition!";
            Link.l1 = "Dismissed.";
            Link.l1.go = "Exit";
        break;
		//<-- ----------------------------------- офицерский блок ----------------------------------------
		
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

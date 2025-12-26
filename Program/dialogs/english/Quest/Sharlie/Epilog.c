void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk;
	int i, n, iTemp, addGold, NextMonth;
	string attrL, sStr, Month;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	attrL = Dialog.CurrentNode;
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Did you want something?";
			link.l1 = "No, nothing.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// диалоги в ПУ
		case "SharlieEpilog_Pikar_1":
			dialog.text = "Well, look who it is! "+GetTitle(NPChar,true)+" "+pchar.lastname+" in the flesh!";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarAlive"))
			{
				link.l1 = ""+npchar.name+"! Well, you’re the last person I expected to see... Honestly, I didn’t even think you were still alive!";
				link.l1.go = "SharlieEpilog_Pikar_2";
			}
			else
			{
				link.l1 = "I can't believe my eyes... Handsome? But... how?";
				link.l1.go = "SharlieEpilog_PikarResurrected_1";
			}
			PlaySound("Voice\" + LanguageGetLanguage() + "\LE\Rocur\Rocur_03.wav");
		break;
		
		case "SharlieEpilog_Pikar_2":
			if (IsStateTitle())
			  {
				dialog.text = "Ha-ha! Well, you shouldn't have worried. As you can see, I'm alive and kicking. Decided to treat myself to a nice, 'clean' ship. But what about you... tell me, how did you end up like this, my friend?";
			  }
			  else 
			  {
				dialog.text = "Ha-ha! Well, you shouldn't have worried. As you can see, I'm alive and kicking. Decided to treat myself to a 'spotless' little ship. And you... tell me, what brings you here, my friend?";
			  }
			link.l1 = "Not here. Let's go to the tavern—the business can wait.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_WithPikarToTavern");
		break;
		
		case "SharlieEpilog_PikarResurrected_1":
			dialog.text = "Shh... No need to shout. The pretty boy is gone, just like the Prince, I suppose. Isn't that right?";
			link.l1 = "But I saw it with my own eyes...";
			link.l1.go = "SharlieEpilog_PikarResurrected_2";
		break;

		case "SharlieEpilog_PikarResurrected_2":
			dialog.text = "How did I get finished off? If only it were that simple, my friend. Believe me.";
			link.l1 = "Let's go to the tavern. You can tell me everything.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_WithPikarToTavern");
		break;
		
		case "SharlieEpilog_Captain_1":
			dialog.text = "...";
			link.l1 = "So, you're the new owner of the pinnace '"+GetShipName("Ulysse")+"'?";
			link.l1.go = "SharlieEpilog_Captain_2";
			PlaySound("Voice\" + LanguageGetLanguage() + "\z_arest_02.wav");
		break;
		
		case "SharlieEpilog_Captain_2":
			dialog.text = "I. "+GetFullName(npchar)+", since you're so curious. And who might you be?";
			link.l1 = ""+UpperFirst(GetTitle(NPChar,false))+" "+pchar.lastname+", and I would like to buy this ship from you.";
			link.l1.go = "SharlieEpilog_Captain_3";
		break;
		
		case "SharlieEpilog_Captain_3":
			dialog.text = "Of course, of course, I've heard about you. I thought I'd finally shaken off everyone who wanted to get their hands on this ship. I'm afraid I'll have to disappoint you, "+GetTitle(NPChar,true)+" - '"+GetShipName("Ulysse")+"' is mine now, and very soon I'll be sailing her to Bordeaux. I didn't get into trade just to ruin my very first deal. It's bad luck, you know.";
			link.l1 = "Bordeaux, you say? Interesting... Perhaps I have a profitable offer for you. Shall we discuss it over a mug of rum?";
			link.l1.go = "SharlieEpilog_Captain_4";
		break;
		
		case "SharlieEpilog_Captain_4":
			dialog.text = "It's not in my nature to turn down rum or a good offer. Let's go.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_WithPikarToTavern");
		break;
		
		// диалоги в таверне
		case "SharlieEpilog_Pikar_5":
			if (IsStateTitle())
			  {
				dialog.text = "Well then, to you, "+GetTitle(npchar,false)+" "+pchar.lastname+". I knew a fellow like you wouldn't be running errands for Tirax for long. But to see you become such a big shot... you really know how to surprise me, damn it.";
				link.l1 = "Ha-ha. Look who's talking. So, you've decided to become a merchant?";
			  }
			  else 
			  {
				dialog.text = "To our meeting! I had a feeling we'd cross paths again.";
				link.l1 = "Ha-ha. To her! So, you've decided to become a merchant?";
			  }
			
			link.l1.go = "SharlieEpilog_Pikar_6";
		break;

		case "SharlieEpilog_Pikar_6":
			dialog.text = "Well, you can't spend your whole life risking your neck for a handful of doubloons. Grease the right palms, keep the wrong mouths shut—and just like that, I'm no thief or pirate, but a respectable merchant.";
			link.l1 = "Well, that's a twist. Now I don't even know how to offer you what I was going to propose to the newly minted pinnace captain '"+GetShipName("Ulysse")+"'.";
			link.l1.go = "SharlieEpilog_Pikar_7";
		break;

		case "SharlieEpilog_Pikar_7":
			dialog.text = "Oh, come on, just say it straight. We've known each other forever.";
			link.l1 = "You see... I came here to the Caribbean on the pinnace you bought out. When I heard it was up for auction, I wanted to bargain for it—and sail it back home to France.";
			link.l1.go = "SharlieEpilog_Pikar_8";
		break;

		case "SharlieEpilog_Pikar_8":
			dialog.text = "Ha-ha-ha-ha! Wait... ah-ha-ha-ha-ha!..";
			link.l1 = "So, what's so funny?";
			link.l1.go = "SharlieEpilog_Pikar_9";
		break;

		case "SharlieEpilog_Pikar_9":
			dialog.text = "And no sooner had I won the auction than this dandy comes up to me—a young, well-groomed fellow—asking me to take him and his belongings to Bordeaux for a tidy sum. And not just a sum—a whole damned sack of coins.";
			link.l1 = "Is that so? Ha-ha. That’s really amusing. So, what did you do? Did you agree?";
			link.l1.go = "SharlieEpilog_Pikar_10";
		break;

		case "SharlieEpilog_Pikar_10":
			dialog.text = ""+pchar.name+", well, I’m no fool to turn down a pile of gold for a simple trip across the Atlantic. Alright, I’ll have to gnaw on hardtack and chew salted meat for a couple of months. But you know, I’ve risked my neck for far less. So of course, I’m in.";
			link.l1 = "In that case, I can offer you the same deal. Take me to Bordeaux, and you'll get just as much coin.";
			link.l1.go = "SharlieEpilog_Pikar_11";
		break;

		case "SharlieEpilog_Pikar_11":
			dialog.text = "Are you ready to be a passenger? You know the rules – there’s only one captain on a ship. And on my ship, that’s me.";
			link.l1 = "Why not? I'll catch my breath, think about life. Maybe I really should settle down, calm my restless spirit. It's hard to imagine right now, but perhaps there's something to it. After all, even you decided to keep away from battles.";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l1.go = "SharlieEpilog_Pikar_12_wife";
			}
			else
			{
				link.l1.go = "SharlieEpilog_Pikar_12";
			}
		break;
		
		case "SharlieEpilog_Pikar_12_wife":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarAlive"))
			{
				dialog.text = "Ah, if I had a beautiful wife like you do, maybe I’d give up the sea myself and settle down somewhere quiet—build a house, trade a little wine. And I can afford it now—ever since you pulled me out of the Spaniards’ clutches, I haven’t wasted any time.";
			}
			else
			{
				dialog.text = "Ah, if I had a beautiful wife like yours, maybe I’d have left the sea myself, settled down somewhere quiet: built a house, traded a bit of wine. And with that planter’s widow’s inheritance, you’ve got more than enough to live on.";
			}
			link.l1 = "Wife! Damn, "+npchar.name+", I haven't talked to her about it yet.";
			link.l1.go = "SharlieEpilog_Pikar_13_wife";
		break;
		
		case "SharlieEpilog_Pikar_13_wife":
			dialog.text = "You've got plenty of time for that. I need to get my old tub properly fitted out. Once you've sorted out your business, haul your backside over here. We'll throw a feast before we set sail.";
			link.l1 = "That's more like it! Don't worry, you won't have to wait long.";
			link.l1.go = "SharlieEpilog_Pikar_14_wife";
		break;
		
		case "SharlieEpilog_Pikar_14_wife":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarAlive")) {AddQuestRecord("SharlieEpilog", "11_1");}
			else {AddQuestRecord("SharlieEpilog", "11_5");}
			AddDialogExitQuestFunction("SharlieEpilog_OutTavern");
		break;
		
		case "SharlieEpilog_Pikar_12":
			dialog.text = "Ah, if I had a wife, maybe I’d leave the sea behind and settle down somewhere quiet—build a house, sell a bit of wine. But for now... the sea is my home.";
			link.l1 = "Wine from my own plantations, ha-ha! In Bordeaux, "+npchar.name+", those girls are a real sight to behold! Maybe you'll even find yourself a sweetheart there – they're quite skilled in matters of love. You know, I was thinking: for the next few months, the only faces we'll be seeing are those of your sailors. We really ought to throw a proper feast at the local brothel before we set sail.";
			link.l1.go = "SharlieEpilog_Pikar_13";
		break;
		
		case "SharlieEpilog_Pikar_13":
			dialog.text = "And you, monsieur, know exactly what to offer. Once you’ve sorted out your affairs, haul your ass back here. Then we’ll make our way to the brothel—count on it.";
			link.l1 = "Well then, I won't waste any time. Let's get to it!";
			link.l1.go = "SharlieEpilog_Pikar_14";
		break;
		
		case "SharlieEpilog_Pikar_14":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarAlive")) {AddQuestRecord("SharlieEpilog", "11_2");}
			else {AddQuestRecord("SharlieEpilog", "11_6");}
			AddDialogExitQuestFunction("SharlieEpilog_OutTavern");
		break;
		
		case "SharlieEpilog_PikarResurrected_3":
			dialog.text = "For freedom!";
			link.l1 = "And to you, Jean! To your return from the dead! I still can't believe it. How?";
			link.l1.go = "SharlieEpilog_PikarResurrected_4";
		break;

		case "SharlieEpilog_PikarResurrected_4":
			dialog.text = "They dragged me off the battlefield—barely alive, covered in blood from head to toe. Threw me into a barrack and left me there to die like carrion. Among the slaves was a rather clever fellow—Moko. He saved my hide: tied off my wound with a piece of my own shirt and gave me water.";
			link.l1 = "You mean to say the Spaniards let you live after all that?";
			link.l1.go = "SharlieEpilog_PikarResurrected_5";
		break;

		case "SharlieEpilog_PikarResurrected_5":
			dialog.text = "As you can see. But it wasn’t out of the kindness of their hearts. They wanted revenge—interrogations, torture. They burned, beat, cut. Threatened to burn out my eyes—purely out of their deep affection for me. But then someone spread a rumor that pirates were planning to avenge me and were already sharpening their knives. The plantation owner started twitching with nerves. He didn’t wait for our brothers to pay him a visit and hurried off to his estates in Campeche. He took me, Moko, and the others with him, so there’d be no witnesses left. The rest were told I’d died—and that was the end of it.";
			link.l1 = "And then what? How did you get out? And how on earth did you end up here?";
			link.l1.go = "SharlieEpilog_PikarResurrected_6";
		break;

		case "SharlieEpilog_PikarResurrected_6":
			dialog.text = "Luck, my friend. Blind, filthy luck. They sent me to the plantation—and the torture went on. That bastard decided to savor every second of my suffering, but with each passing day, he grew weaker... until the fever finally killed him. After that, no one cared about me anymore. They drove me out to the fields like cattle, never missing a chance to lash me with the whip.";
			link.l1 = "I still don't understand how you managed to get out of there?";
			link.l1.go = "SharlieEpilog_PikarResurrected_7";
		break;

		case "SharlieEpilog_PikarResurrected_7":
			dialog.text = "Heard of Christopher Myngs?";
			link.l1 = "Alonso mentioned something... The raid on Campeche! They really gave the Spaniards a thrashing that time. So it was them who set you free?";
			link.l1.go = "SharlieEpilog_PikarResurrected_8";
		break;

		case "SharlieEpilog_PikarResurrected_8":
			dialog.text = "Not exactly. We freed ourselves. While the guards were fighting off the English buccaneers, Moko and I found a way out through the barracks roof and started a revolt. We seized the arsenal and the treasury of the late bastard planter's wife.";
			link.l1 = "The treasury?! Well, that's a twist.";
			link.l1.go = "SharlieEpilog_PikarResurrected_9";
		break;

		case "SharlieEpilog_PikarResurrected_9":
			dialog.text = "We didn't waste time thinking it over – we took our weapons and supplies and headed into the jungle. For two days we pushed through the undergrowth until we stumbled upon a village of the Kan Pech Indians. Their shaman pretended to obey the Spaniards, but he didn't care for them much. Moko quickly found common ground with him – they took us in, in exchange for half our arsenal and a promise to help them in whatever war might come. That's how I ended up living there for a year and a half.";
			link.l1 = "Jean, you're not the man you once were. From now on, you're Lucky.";
			link.l1.go = "SharlieEpilog_PikarResurrected_10";
		break;

		case "SharlieEpilog_PikarResurrected_10":
			dialog.text = "Ha-ha. I don’t mind. Well, after that, a French preacher ended up in our batabil. We quickly realized: this was our chance to get out of there without irons. We bribed his escort – and soon we were sailing to Tortuga.\nAnd then, as you’ve probably guessed, I decided I’d had enough of playing tag with death. I gave up my old trade… and, as luck would have it, bought myself a '"+GetShipName("Ulysse")+"'.\n"+"And you? How did you end up like this? I always knew a daring fellow like you wouldn’t stay Tyraks’s errand boy for long. But to see you become such a big shot... you never cease to surprise me, damn it.";
			link.l1 = "Ha-ha. Look who's talking. So, you've decided to become a merchant?";
			link.l1.go = "SharlieEpilog_Pikar_6";
		break;
		
		case "SharlieEpilog_Captain_5":
			dialog.text = "To those at sea!";
			link.l1 = "And to Lady Luck!";
			link.l1.go = "SharlieEpilog_Captain_6";
		break;

		case "SharlieEpilog_Captain_6":
			dialog.text = "Alright, let's get to the point. What did you want to offer me?";
			link.l1 = "You're heading to Bordeaux... You see, I'm going there as well.";
			link.l1.go = "SharlieEpilog_Captain_7";
		break;

		case "SharlieEpilog_Captain_7":
			dialog.text = "Do you want me to take you aboard? As far as I know, you should have your own ship. Maybe even a whole fleet. Yet you chose to sail on someone else's vessel. Am I right?";
			link.l1 = "That's right. Recent events have made me wonder if it's time to drop anchor, settle down... I think being just a passenger on your ship will help me see if I can get used to a new pace of life.";
			link.l1.go = "SharlieEpilog_Captain_8";
		break;

		case "SharlieEpilog_Captain_8":
			dialog.text = "Hmm... So, you've grown tired of risking your neck for nothing? I know the feeling. I myself... Well, never mind. There’s a place for you on the ship, and for your whole entourage too. The passage is already paid for by a certain young dandy—and he’s paying for speed, so I won’t be loading any cargo. As for payment...";
			link.l1 = "Don't worry, Captain. I'm just as generous as your employer and ready to pay the same amount.";
			link.l1.go = "SharlieEpilog_Captain_9";
		break;

		case "SharlieEpilog_Captain_9":
			dialog.text = "Excellent! So, do we have a deal?";
			link.l1 = "Deal! That's worth a drink!";
			link.l1.go = "SharlieEpilog_Captain_10";
		break;

		case "SharlieEpilog_Captain_10":
			dialog.text = "Yeah, that's some good rum... I'll need two weeks to get the ship in shape and stock up on everything we need. After that, we can set sail.";
			link.l1 = "Then let's meet here again in two weeks. Well, until next time, Captain.";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l1.go = "SharlieEpilog_Captain_11_wife";
			}
			else
			{
				link.l1.go = "SharlieEpilog_Captain_11";
			}
		break;
		
		case "SharlieEpilog_Captain_11_wife":
			DialogExit();
			AddQuestRecord("SharlieEpilog", "11_3");
			AddQuestUserData("SharlieEpilog", "sName", GetFullName(npchar));
			AddDialogExitQuestFunction("SharlieEpilog_OutTavern");
		break;
		
		case "SharlieEpilog_Captain_11":
			DialogExit();
			AddQuestRecord("SharlieEpilog", "11_4");
			AddQuestUserData("SharlieEpilog", "sName", GetFullName(npchar));
			AddDialogExitQuestFunction("SharlieEpilog_OutTavern");
		break;
		
		case "SharlieEpilog_Pikar_WaitInTavern":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "So, my friend, have you sorted everything out? Shall we show this henhouse how to have a good time?";
				link.l1 = "Not yet, "+npchar.name+", I still have a few things left to take care of.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Captain, are you ready to board the ship?";
				link.l1 = "Alas, my friend, I still have things to attend to.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "SharlieEpilog_Pikar_WaitInTavern";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_FarewellOfficers") && CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				// только если знаком с Пикаром и поговорил с женой
				link.l2 = "Hey, innkeeper! Drinks for everyone, on me! And not just any swill—bring out your finest!";
				link.l2.go = "SharlieEpilog_Pikar_WaitInTavern_2";
			}
		break;
		
		case "SharlieEpilog_Pikar_WaitInTavern_2":
			dialog.text = "...";
			link.l1 = "To us, my friend. To the salty wind, the endless sea, and the horizon—forever calling, forever out of reach...";
			link.l1.go = "SharlieEpilog_FrameInSea";
			DelLandQuestMark(npchar);
		break;
		
		case "SharlieEpilog_FrameInSea":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_FrameInSea");
		break;
		
		case "SharlieEpilog_Mary_1":
			dialog.text = "...";
			link.l1 = ""+npchar.name+", darling, I want to talk to you about my father.";
			link.l1.go = "SharlieEpilog_Mary_2";
			DelLandQuestMark(npchar);
		break;

		case "SharlieEpilog_Mary_2":
			dialog.text = "What happened, darling? I hope he's alright, yes?";
			link.l1 = "Well, not as well as one would hope. There’s reason to believe he doesn’t have much time left, and he’s deeply troubled by the thought that he might not see me before he sets out on his final journey.";
			link.l1.go = "SharlieEpilog_Mary_3";
		break;

		case "SharlieEpilog_Mary_3":
			dialog.text = ""+pchar.name+"...";
			link.l1 = "I know, my dear, I know... But that's life. I wish you could meet him. Let him see what a remarkable wife I have, and give us his blessing.";
			link.l1.go = "SharlieEpilog_Mary_4";
		break;

		case "SharlieEpilog_Mary_4":
			dialog.text = "And what if he doesn't like me, alright? I'm not of noble birth...";
			link.l1 = "Nonsense, "+npchar.name+", how could he not like you? You're wonderful! If you've won my heart, you'll win his too.";
			link.l1.go = "SharlieEpilog_Mary_5";
		break;

		case "SharlieEpilog_Mary_5":
			dialog.text = "Do you really think so, darling? Then we must go to him as soon as possible.";
			link.l1 = "That's exactly what I intend to do. I've even found us a ship. We set sail in two weeks.";
			link.l1.go = "SharlieEpilog_Mary_6";
		break;

		case "SharlieEpilog_Mary_6":
			dialog.text = "A ship? We're not sailing on our own vessel?";
			link.l1 = "No, my dear. We'll be sailing on the pinnace '"+GetShipName("Ulysse")+"'. I arrived in the Caribbean on this ship – and on this ship I shall leave.";
			link.l1.go = "SharlieEpilog_Mary_7";
		break;

		case "SharlieEpilog_Mary_7":
			dialog.text = "And you won't be a captain?";
			link.l1 = "Sooner or later, I would have had to give up this role anyway. I hope it’s only temporary. Still, it won’t hurt to get a sense of what the future holds for me.";
			link.l1.go = "SharlieEpilog_Mary_8";
		break;

		case "SharlieEpilog_Mary_8":
			dialog.text = "And what about our officers? We can't take all of them with us. And I doubt they'll wait for you here.";
			link.l1 = "Ahem... Yes, you're right. I'll have to speak with each of them, and most likely say goodbye for good. Even though it won't be easy—considering all we've been through together.";
			link.l1.go = "SharlieEpilog_Mary_9";
		break;
			
		case "SharlieEpilog_Mary_9":
			dialog.text = "Maybe we should throw a little farewell party at the tavern?";
			link.l1 = "I've thought about that too, my dear. You know... I think you're right. It's actually a good idea.";
			link.l1.go = "exit";
			link.l2 = "I don't think that's a good idea. Let's skip the grand farewells... It's probably better for everyone this way. Maybe we could just invite our closest friends...";
			link.l2.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_FarewellOfficers");
		break;
		
		case "SharlieEpilog_Helena_1":
			dialog.text = "...";
			link.l1 = "Darling, I'd like to talk to you about my father.";
			link.l1.go = "SharlieEpilog_Helena_2";
			DelLandQuestMark(npchar);
		break;

		case "SharlieEpilog_Helena_2":
			dialog.text = "Of course, "+pchar.name+". I hope he's alright?";
			link.l1 = "Not exactly. He's been ill for quite some time, and I'm afraid the sickness will soon get the better of him... Father bears it all with great courage. The only thing that truly troubles him is the thought that he might never see me again. I want to visit him... and introduce you to him. To receive his blessing for our marriage.";
			link.l1.go = "SharlieEpilog_Helena_3";
		break;

		case "SharlieEpilog_Helena_3":
			dialog.text = "I'll be happy to meet him, my love. When do we set sail?";
			link.l1 = "In two weeks. But that's not all. We won't be sailing on our own ship. A pinnace will take us to the Old World. "+GetShipName("Ulysse")+"' - the very one who once brought me here.";
			link.l1.go = "SharlieEpilog_Helena_4";
		break;

		case "SharlieEpilog_Helena_4":
			dialog.text = ""+pchar.name+", but changing ships before a long voyage is bad luck.";
			link.l1 = "We won't be changing the ship, my dear. We'll be passengers.";
			link.l1.go = "SharlieEpilog_Helena_5";
		break;

		case "SharlieEpilog_Helena_5":
			dialog.text = "But... darling, I don't understand...";
			link.l1 = "That's how it has to be, "+npchar.name+". Sooner or later, I'll have to step down as captain. And I want to know in advance what feelings I'll have to face.";
			link.l1.go = "SharlieEpilog_Helena_6";
		break;

		case "SharlieEpilog_Helena_6":
			dialog.text = "If that's your decision... But what about our officers? We can't take them all with us. And I doubt they'll want to wait for you here.";
			link.l1 = "Ahem... Yes, you're right. I'll have to speak with each of them, and most likely say goodbye for good. Though it won't be easy—considering all we've been through together.";
			link.l1.go = "SharlieEpilog_Helena_7";
		break;
			
		case "SharlieEpilog_Helena_7":
			dialog.text = "Maybe we should throw a little farewell party at the tavern?";
			link.l1 = "I've been thinking the same, my dear. You know... I think that's exactly what we'll do. It's truly a good idea.";
			link.l1.go = "exit";
			link.l2 = "I don't think that's a good idea. Let's skip the grand farewells... It's probably better for everyone this way. Maybe we could just invite our closest friends...";
			link.l2.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_FarewellOfficers");
		break;
		
		// Диалог с Алонсо в таверне Сен-Пьера
		case "SharlieEpilog_AlonsoInTavern":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
			{
				dialog.text = "Cap... I’ve already spoken to the innkeeper – he’s prepared the best drink he’s got. When do we start?";
				link.l1 = "Right now! Hey, innkeeper! Drinks for everyone, on me!";
				link.l1.go = "SharlieEpilog_AlonsoInTavern_1";
			}
			else
			{
				dialog.text = "Captain, you promised to tell me how you found out about the 'Ulysses'.";
				link.l1 = "I remember, I remember. Hey, innkeeper! Bring the finest rum to this table.";
				link.l1.go = "SharlieEpilog_AlonsoInTavern_3";
			}
			link.l2 = "Too early, "+npchar.name+". I still have urgent matters to attend to.";
			link.l2.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_AlonsoInTavern";
		break;
		
		case "SharlieEpilog_AlonsoInTavern_1":
			dialog.text = "...";
			link.l1 = "Well then, my friend, call the others – let's show Saint-Pierre how real sea dogs celebrate!";
			link.l1.go = "SharlieEpilog_AlonsoInTavern_2";
			DelLandQuestMark(npchar);
		break;
		
		case "SharlieEpilog_AlonsoInTavern_2":
			dialog.text = "Ha-ha! Cap, you won't believe it – I've already called them!";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_FrameInSea";
		break;
		
		case "SharlieEpilog_AlonsoInTavern_3":
			dialog.text = "...";
			link.l1 = "To us, "+npchar.name+". To Lady Luck, and to the wind that fills our sails!";
			link.l1.go = "SharlieEpilog_FrameInSea";
			DelLandQuestMark(npchar);
		break;
		
		// На пинасе Улисс
		case "SharlieEpilog_Alonso_1":
			dialog.text = "What a mess we made, Cap. Ha-ha. Looks like the only thing that saved the tavern from total ruin was the innkeeper's meager stash of rum.";
			link.l1 = "Don't remind me, "+npchar.name+", I’ve only just started to feel a little better.";
			link.l1.go = "SharlieEpilog_Alonso_2";
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "tutorial_4", "", -1);
			CharacterTurnByLoc(pchar, "quest", "quest6");
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "tutorial_5", "", -1);
			CharacterTurnByLoc(npchar, "quest", "quest7");
		break;
		
		case "SharlieEpilog_Alonso_2":
			dialog.text = "As you wish, sir "+pchar.lastname+". Ha-ha. But at least we left Martinique in royal fashion. They’ll be talking about your departure there for a long time.";
			link.l1 = "I think we may have gone a bit too far when we put the innkeeper in the dinghy and sent him off to Le François for more drink.";
			link.l1.go = "SharlieEpilog_Alonso_2_1";
		break;
		
		case "SharlieEpilog_Alonso_2_1":
			if (GetAttributeInt(pchar, "questTemp.SharlieEpilog_Friends") >= 2)
				{
					dialog.text = "Ha-ha-ha. Don't worry about him. In these few days, he's made enough gold to buy himself a plantation—maybe even a title to go with it.";
				}
			else
				{
					dialog.text = "Ha-ha-ha. Don't worry about him. In these past days, he's made enough gold to buy a plantation, and a title to go with it. It's just a shame you never spoke to any of the officers. We'll miss them.";
				}
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Alonso_3";
		break;
		
		case "SharlieEpilog_Alonso_3":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
				{
					sld = CharacterFromID("Helena");
					locCameraFromToPos(-8.97, 6.39, -12.78, true, -8.54, 4.94, -13.90);
				}
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
				{
					sld = CharacterFromID("Mary");
					locCameraFromToPos(-3.62, 4.03, 2.30, true, -4.98, 2.62, 3.26);
					// locCameraFromToPos(-4.13, 4.23, 2.55, true, -5.71, 2.54, 3.58);
				}
				dialog.text = "Seems like, "+sld.name+" still angry with you for disappearing for half the night.";
			}
			else
			{
				dialog.text = "And with that merchant... you really did go too far there, Captain.";
			}
			link.l1 = "Devil take it, why did Jean and I have to go poking around that local shop…";
			link.l1.go = "SharlieEpilog_Alonso_4";
		break;
		
		case "SharlieEpilog_Alonso_4":
			dialog.text = "And how did you manage not to get caught? That would have been a real laugh - "+GetTitle(PChar,true)+" caught trying to steal several bottles of wine.";
			link.l1 = "You find it funny, "+npchar.name+", and I can’t even remember half of it. The last time I drank this much was... well... never, actually.";
			link.l1.go = "SharlieEpilog_Alonso_5";
			locCameraFromToPos(-8.74, 6.30, 7.38, true, -14.34, 4.16, 6.56);
		break;
		
		case "SharlieEpilog_Alonso_5":
			dialog.text = "Well then, here's to a good start, Cap. Ha-ha. I quite enjoyed that. I'd do it again. So, when did you say we're heading back?";
			link.l1 = "Go check on our belongings, will you? Did we take everything? I’ll come down later—the air in the hold wouldn’t do me any good right now.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_UlysseInSea_8");
		break;
		
		// диалог с Алонсо у горы золота
		case "SharlieEpilog_Alonso_11": // этап 1
			dialog.text = "...";
			link.l1 = "Just look at that... the ship really took a beating.";
			link.l1.go = "SharlieEpilog_Alonso_12";
			SharlieEpilog_GoldInTheDeck_1_1();
		break;
		
		case "SharlieEpilog_Alonso_12":
			dialog.text = "There's a whole damn pile of gold here, Cap!";
			link.l1 = "I see, "+npchar.name+". We need to stash all this in the chests right away, before the crew sees it. They don't need such temptations.";
			link.l1.go = "SharlieEpilog_Alonso_13";
		break;
		
		case "SharlieEpilog_Alonso_13":
			dialog.text = "No, I can't resist...";
			link.l1 = "What?";
			link.l1.go = "exit";
			locCameraFromToPos(-1.28, 7.70, -10.26, true, 0.74, 5.42, -9.49);
			AddDialogExitQuestFunction("SharlieEpilog_GoldInTheDeck_2");
		break;
			
		case "SharlieEpilog_Alonso_21": // этап 2
			dialog.text = "...";
			link.l1 = "Hey, what's with you?";
			link.l1.go = "SharlieEpilog_Alonso_22";
			// SharlieEpilog_GoldInTheDeck_6();
		break;
		
		case "SharlieEpilog_Alonso_22":
			dialog.text = "...";
			link.l1 = "Come on, get up. You picked a fine time...";
			link.l1.go = "SharlieEpilog_Alonso_23";
		break;
		
		case "SharlieEpilog_Alonso_23":
			dialog.text = "Join us, Cap.";
			link.l1 = "Get up, stop fooling around.";
			link.l1.go = "SharlieEpilog_Alonso_24";
		break;
		
		case "SharlieEpilog_Alonso_24":
			dialog.text = "Relax. You just need to feel it.";
			link.l1 = "Alright, have it your way. Now, move over.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_GoldInTheDeck_7");
		break;
		
		case "SharlieEpilog_Alonso_31": // этап 3
			dialog.text = "I've always dreamed of doing this...";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Alonso_32";
			SharlieEpilog_GoldInTheDeck_10();
		break;
		
		case "SharlieEpilog_Alonso_32":
			dialog.text = "Magnificent feeling, isn't it, Cap?";
			link.l1 = "Ha-ha-ha. So much for just visiting the Caribbean to check on my dear brother. Father surely didn't expect things to turn out like this. Ha-ha!";
			link.l1.go = "SharlieEpilog_Alonso_33";
		break;
		
		case "SharlieEpilog_Alonso_33":
			dialog.text = "Sir "+GetTitle(NPChar,false)+" "+pchar.lastname+"... Ha-ha! Do you remember what you were like when you first arrived in the archipelago?";
			link.l1 = "Of course I remember. Ha-ha. Hard to believe I was once as much of a dandy as the one strutting around the deck now. So much has happened in these damned Caribbean seas… Intrigue, the undead, brother Kukulkan…";
			link.l1.go = "SharlieEpilog_Alonso_34";
		break;
		
		case "SharlieEpilog_Alonso_34":
			dialog.text = "You're damn lucky, Captain. To make a fortune like that—and live to tell the tale… not everyone manages that.";
			link.l1 = "Yeah, alright, enough lounging around. Wouldn’t want someone to actually notice us.";
			link.l1.go = "exit";
			locCameraSleep(true);
			AddDialogExitQuestFunction("SharlieEpilog_GoldInTheDeck_11");
		break;
		
		// диалоги в катсцене с брашпилем
		case "SharlieEpilog_windlass_1":
			dialog.text = "...";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				link.l1 = "Listen, my friend, I don't like the windlass safety on this ship. It's far too unreliable. Someone could easily knock it off by accident.";
			}
			else
			{
				link.l1 = "Listen, Captain, I don't like the windlass safety on this ship. It's far too unreliable. Someone could easily knock it off by accident.";
			}
			link.l1.go = "SharlieEpilog_windlass_2";
			locCameraFromToPos(-7.57, 9.68, -21.21, true, -9.79, 7.76, -20.01);
		break;
		
		case "SharlieEpilog_windlass_2":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "Oh, come on, "+pchar.name+", on a ship, everyone knows that…";
			}
			else
			{
				dialog.text = "Oh, come on, Captain. Who would ever think...";
			}
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_windlass_3");
		break;
		
		case "SharlieEpilog_windlass_3": // диалог Пикара и дворянина
			dialog.text = "Hey, you blockhead... What the devil do you think you're doing? Didn't anyone teach you not to stick your clumsy feet where they don't belong?";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_windlass_4";
			locCameraFromToPos(-10.28, 9.94, -22.90, true, -9.29, 7.86, -21.36);
			NPCsLookEachOther("SharlieEpilog_Pikar", "SharlieEpilog_Bernard_Clone");
			CharacterTurnByChr(pchar, CharacterFromID("SharlieEpilog_Bernard_Clone"));
		break;
		
		case "SharlieEpilog_windlass_4":
			dialog.text = "...";
			link.l1 = "Easy now, don't get carried away! I'm a nobleman, and I won't tolerate this…";
			link.l1.go = "SharlieEpilog_windlass_5";
		break;
		
		case "SharlieEpilog_windlass_5":
			dialog.text = "On my ship, you’re nobody. My crew have more rights here than you do. So either you keep quiet and stay out of the way, or I’ll personally throw you overboard.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_windlass_6";
		break;
		
		case "SharlieEpilog_windlass_6": // диалог Пикара и Шарля
			dialog.text = "...";
			link.l1 = "Ha-ha-ha. It's like I just saw myself from the outside.";
			link.l1.go = "SharlieEpilog_windlass_7";
			SharlieEpilog_windlass_9_1();
		break;
		
		case "SharlieEpilog_windlass_7":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "What are you talking about?";
				link.l1 = "Alright, it doesn't matter, "+npchar.name+". Don't be so hard on our passenger. All this is still new to him. After all, it didn't take us just one day to become old sea dogs either.";
			}
			else
			{
				dialog.text = "What are you talking about?";
				link.l1 = "Don't mind it, "+npchar.name+". And don’t judge your passenger too harshly. All this is new to him. After all, we weren’t born sea dogs either.";
			}
			link.l1.go = "SharlieEpilog_windlass_8";
		break;
		
		case "SharlieEpilog_windlass_8":
			dialog.text = "With his talent, he’s more likely to get tangled up in the capstan than ever become a sailor. Imagine coming up with that…";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				link.l1 = "Who knows, who knows. I arrived in the archipelago just as carefree, curious, and arrogant a youth as ever.";
			}
			else
			{
				link.l1 = "Who knows. When I first arrived in the archipelago, I was just as carefree, curious, and arrogant a youth.";
			}
			link.l1.go = "SharlieEpilog_windlass_9";
		break;
		
		case "SharlieEpilog_windlass_9":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "Yeah, right, what a comparison.\n"+"Wait\n"+"So you see yourself in him? Ha-ha-ha. Then take him under your wing. I won't be babysitting him.";
				link.l1 = "I'll keep an eye on him. At least until you skin him alive. But he should pay the full price for the anchor.";
			}
			else
			{
				dialog.text = "So you saw yourself in him? Ha-ha. Well then, Captain, he's your responsibility now. I won't be babysitting him.";
				link.l1 = "I'll keep an eye on him. At least until you've finished skinning him alive. But as for the anchor—let him pay for it properly.";
			}
			link.l1.go = "SharlieEpilog_windlass_10";
		break;
		
		case "SharlieEpilog_windlass_10":
			dialog.text = "Drop anchor. Wait for the wind. Hold our course.";
			link.l1 = "...";
			link.l1.go = "exit";
			SharlieEpilog_windlass_10();
			AddDialogExitQuestFunction("SharlieEpilog_AlonsoTrollingHighSailor_1");
		break;
		
		// диалоги Старшего матроса и Алонсо		
		case "SharlieEpilog_AlonsoTrollingHighSailor_2": // Алонсо
			dialog.text = "";
			link.l1 = "Raise anchor. Catch the wind. Set course northeast.";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_3";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_2();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_3": // Старший матрос
			dialog.text = "";
			link.l1 = "Raise the anchor! Lower the jib – let's catch the wind. Get to work...";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_4";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_1();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_4": // Алонсо
			dialog.text = "";
			link.l1 = "What are you doing?";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_5";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_2();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_5": // Старший матрос
			dialog.text = "";
			link.l1 = "What are you doing?";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_6";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_1();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_6": // Алонсо
			dialog.text = "";
			link.l1 = "No, what are you doing?";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_7";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_2();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_7": // Старший матрос
			dialog.text = "";
			link.l1 = "Argh... What are you doing? The senior sailor repeats the captain's orders.";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_8";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_1();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_8": // Алонсо
			dialog.text = "";
			link.l1 = "So the senior sailor just repeats after them.";
			link.l1.go = "exit";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_2();
			AddDialogExitQuestFunction("SharlieEpilog_AlonsoTrollingHighSailor_2");
		break;
		
		// Шарль ругает Алонсо
		case "SharlieEpilog_AlonsoTrollingHighSailor_9":
			dialog.text = "...";
			link.l1 = "Stand down, Alonso. We're just passengers here. Did you forget?";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_10";
			locCameraFromToPos(-8.00, 4.49, -1.91, true, -9.97, 2.64, -1.90);
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_10":
			dialog.text = "Ahem... Sorry, Cap. Couldn't help myself\nBut it was worth it. Felt like I was back in the past.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_AlonsoTrollingHighSailor_5");
		break;
		
		// Диалог Шарля с Пикаром о всяком (можно попасть в Поместье де Монпе)
		case "SharlieEpilog_PikarOnUliss":
			dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+pchar.lastname+"... What can I do for you?";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_A"))
				{
					link.l1 = "So, my friend, how are you feeling?";
					link.l1.go = "SharlieEpilog_PikarOnUliss_A_1";
				}
				if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_B"))
				{
					if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarAlive"))
					{
						link.l2 = "Admit it, "+npchar.name+", you were already planning to become a merchant back when you decided to break away from Tirax, weren't you?";
						link.l2.go = "SharlieEpilog_PikarOnUliss_B_1";
					}
					else
					{
						link.l2 = "Admit it, "+npchar.name+", you were already thinking of becoming a merchant back then, on the plantation?";
						link.l2.go = "SharlieEpilog_PikarOnUliss_B_1";
					}
				}
				if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_C"))
				{
					link.l3 = "I clearly remember that some messenger tried to speak with me. But for the life of me, I can't recall what it was about. Do you know anything about this?";
					link.l3.go = "SharlieEpilog_PikarOnUliss_C_1";
				}
			}
			else
			{
				if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_E"))
				{
					link.l1 = "Have you ever been to Bordeaux, Captain?";
					link.l1.go = "SharlieEpilog_PikarOnUliss_E_1";
				}
				if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_F"))
				{
					link.l2 = "Captain, to be honest, I can hardly remember how we left Martinique. I was supposed to receive some important mail from someone, but it seems I never got it. Has anyone spoken to you about this?";
					link.l2.go = "SharlieEpilog_PikarOnUliss_F_1";
				}
			}
			link.l4 = "Looks like a light breeze has picked up. Time to set sail. (Head out to sea)";
			link.l4.go = "SharlieEpilog_PikarOnUliss_D_1";
			link.l5 = "Nothing yet. I'll go.";
			link.l5.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_PikarOnUliss";
		break;
		
		case "SharlieEpilog_PikarOnUliss_A_1":
			dialog.text = "Ha-ha... Never better! Full of energy and health.";
			link.l1 = "Really? You look like you’ve just been chewed up by a shark.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_A_2";
			pchar.questTemp.SharlieEpilog_PikarOnUliss_A = true;
		break;

		case "SharlieEpilog_PikarOnUliss_A_2":
			dialog.text = "Look who's talking. You look like a whipped dog yourself.";
			link.l1 = "And I feel the same way. Ha-ha. Damn, I can't even remember how or when we set sail.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_A_3";
		break;

		case "SharlieEpilog_PikarOnUliss_A_3":
			dialog.text = "Ah, that was a fine party. Just devilishly expensive. My fools nearly burned down the brothel—I had to fork over a sack of coins to hush up the scandal. So now those idiots owe me for life.\nSo, how do you like being a passenger? Haven't started howling from boredom yet?";
			link.l1 = "I feel as if I no longer hold my own fate in my hands. Yet at the same time, I feel a strange sense of relief. As if I’ve just set down a crate of cannonballs from my shoulders.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_A_4";
		break;

		case "SharlieEpilog_PikarOnUliss_A_4":
			dialog.text = "Ha-ha. Well then, if you ever get bored, I'm ready to take you on as my officer.";
			link.l1 = "That's very generous of you, but I must decline. There isn't enough rum in all the Caribbean to fuel our revelry.";
			link.l1.go = "SharlieEpilog_PikarOnUliss";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_1":
			if (IsStateTitle()) 
			{
				dialog.text = "Not exactly, my friend. The thought crossed my mind from time to time, but I never paid it much attention. It came back to me a second time when I heard a rumor—that Tyrax’s whole pack of loyal dogs had vanished without a trace. Every last one of them—Cleaver, Baldy, and even that old stinking mutt Leprechaun.\nAnd when I heard about all the things you’d accomplished, I finally decided I’d had enough. You can’t keep risking your neck for coins forever.\nI’ve got enough gold now that I’ll never have to grovel before some powdered bastard. But leaving the sea behind... I wasn’t ready for that. So I chose a new line of work.";
			} 
			else 
			{
				dialog.text = "Not exactly, my friend. The thought crossed my mind from time to time, but I never paid it much attention. It came back to me again when I heard a rumor—that Tyrax’s whole pack of loyal dogs had vanished without a trace. Every last one of them—Cleaver, Baldy, and even that old stinking cur Leprechaun.\nAnd when enemy cannonballs nearly blew my brains out twice in one fight, I finally decided I’d had enough. You can’t keep risking your neck for coins forever.\nI’ve got enough gold to never have to bow and scrape before any bastard in a wig. But leaving the sea behind... I wasn’t ready for that. So I decided to try something new.";
			}
			link.l1 = "Cleaver, Baldy, Leprechaun... Do you know where they disappeared to?";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_2";
			pchar.questTemp.SharlieEpilog_PikarOnUliss_B = true;
		break;

		case "SharlieEpilog_PikarOnUliss_B_2":
			dialog.text = "No, I don't know. And to be honest – I couldn't care less where those bastards ended up. They could go straight to hell for all I care.";
			link.l1 = "That's more or less where I sent them.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_3";
		break;

		case "SharlieEpilog_PikarOnUliss_B_3":
			dialog.text = "So it was you who wiped out their whole crew? Well, I'll be damned! And Marcus forgave you for that?";
			link.l1 = "He doesn't know about it. And most likely, he never will.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_4";
		break;

		case "SharlieEpilog_PikarOnUliss_B_4":
			dialog.text = "So, damn it, I left them just in time, ha-ha. You probably wouldn't have spared my head either\nBut there's one thing I can't figure out—what the hell did you need all this for?";
			link.l1 = "You were right – these bastards would strangle each other for a measly piece of gold, betray or kill anyone. We were lured into one of the dungeons on the South Main, fed some tale about untold riches. It was a carefully laid trap, and those damned blockheads swallowed the bait without a second thought. Instead of splitting the loot evenly, they decided there was no point in sharing – easier just to finish me off and take everything for themselves.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_5";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_5":
			dialog.text = "And they didn't pull it off, not a chance, ha-ha! Wait a minute, who set up that trap in the first place?";
			if (CharacterIsAlive("Tonzag") && CheckPassengerInCharacter(pchar, "Tonzag"))
			{
				link.l1 = "Some Zorro, a Spanish folk avenger—seeking revenge for Cartagena. Anyone who survived that massacre was supposed to rot in the dungeon forever—all the exits were sealed. But the bastard wasn't so lucky—my officer outsmarted him.";
			}
			else
			{
				link.l1 = "A certain Zorro, a Spanish folk avenger—seeking revenge for Cartagena. Anyone who survived that hellish massacre was meant to remain in the dungeon forever—all the exits were sealed tight. I managed to escape. But at a terrible cost.";
			}
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_6";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_6":
			dialog.text = "At least you made it out alive. And I suppose you managed to grab all that gold you nearly paid for with your own hide?";
			link.l1 = "There was no gold there. It was just gilded lead...";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_7";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_7":
			dialog.text = "...";
			link.l1 = "After all that, I decided to leave Tirax. You're the first person I've told about it. Well, except for my officers.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_8";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_8":
			dialog.text = "I don't like to say 'I told you so', but... I did warn you.";
			link.l1 = "Knowing when to stop has never been my strong suit. So you'll have to give me a few lessons.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_9";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_9":
			dialog.text = "You know me – for a couple of mugs of good rum, I’ll even tell you where I keep my stash of gold, heh-heh.";
			link.l1 = "Well, don't expect such generosity from me, ha-ha-ha. Your own supplies will have to do.";
			link.l1.go = "SharlieEpilog_PikarOnUliss";
		break;
		
		case "SharlieEpilog_PikarOnUliss_C_1":
			dialog.text = "That's right. He tried to hand you some letters—either from some Ben or maybe Benedict. But you snapped that you didn't know any Ben and threatened to throw him out of the tavern if he kept ruining our fun.";
			link.l1 = "Devil... Looks like these were letters from Abbot Benoit. Important letters.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_C_2";
			pchar.questTemp.SharlieEpilog_PikarOnUliss_C = true;
		break;

		case "SharlieEpilog_PikarOnUliss_C_2":
			dialog.text = "Well, then it's a good thing I took them. Heh-heh.  I had a gut feeling that pup had picked the right person. Here you go.";
			link.l1 = "You really helped me out, "+npchar.name+", thank you.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_C_3";
		break;

		case "SharlieEpilog_PikarOnUliss_C_3":
			dialog.text = "One 'thank you' won't cut it, friend. You owe me a drink—and not just any drink, but the finest they have in Bordeaux.";
			link.l1 = "You'll get your drink, you beggar. Our rum may not compare to Caribbean rum, but the wine... Now that's something you've never tasted before.";
			link.l1.go = "SharlieEpilog_PikarOnUliss";
		break;
		
		case "SharlieEpilog_PikarOnUliss_E_1":
			dialog.text = "Never had to...";
			link.l1 = "I envy you. I wish I could see Bordeaux again for the first time. You probably prefer rum, but I still recommend visiting the wine fair near the town hall. Connoisseurs in the Caribbean would pay a fortune for our claret.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_E_2";
			pchar.questTemp.SharlieEpilog_PikarOnUliss_E = true;
		break;

		case "SharlieEpilog_PikarOnUliss_E_2":
			dialog.text = "Thank you for the advice. May I ask you something?";
			link.l1 = "Of course.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_E_3";
		break;

		case "SharlieEpilog_PikarOnUliss_E_3":
			dialog.text = "How does it feel to be a passenger after so many years at the helm? Have you gotten used to your new role yet?";
			link.l1 = "Hmm... I can't shake the feeling that I'm no longer in control of my own fate. Yet at the same time, I feel a strange sense of relief. As if I've just set down a crate of cannonballs from my shoulders. I suppose it's too soon to draw any conclusions.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_E_4";
		break;

		case "SharlieEpilog_PikarOnUliss_E_4":
			dialog.text = "Given this damned calm we've drifted into, you'll have more than enough time on your hands.";
			link.l1 = "In good company, even a calm sea is no burden. And I must admit, captain, I’ve been lucky with the company I keep.";
			link.l1.go = "SharlieEpilog_PikarOnUliss";
		break;
		
		case "SharlieEpilog_PikarOnUliss_F_1":
			dialog.text = "Yes, there was a messenger. Some abbot sent him. I keep forgetting to give you these letters. Here, take them.";
			link.l1 = "Excellent. You’ve really helped me out, Captain. Thank you.";
			link.l1.go = "SharlieEpilog_PikarOnUliss";
			pchar.questTemp.SharlieEpilog_PikarOnUliss_F = true;
		break;
		
		case "SharlieEpilog_PikarOnUliss_D_1":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_A")){dialog.text = "You're right.";}
			else {dialog.text = "You're right.";}
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_PikarOnUliss_D_2";
		break;
		
		case "SharlieEpilog_PikarOnUliss_D_2":
			dialog.text = "Wind off the starboard bow! Set every sail, from the foresail to the mizzen! Full speed ahead!";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_InEstateDeMonpe";
			locCameraFromToPos(-9.34, 8.28, -16.03, true, -9.33, 7.32, -20.48);
			CharacterTurnToLoc(CharacterFromID("SharlieEpilog_Pikar"), "quest", "quest10");
		break;
		
		case "SharlieEpilog_InEstateDeMonpe":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_InEstateDeMonpe");
		break;
		
		//Матрос 1 на верхней палубе
		case "SharlieEpilog_Sailor_1":
			dialog.text = "Fine blade, "+GetTitle(NPChar,true)+". May I have a look?";
			link.l1 = "Maybe some other time.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Sailor_1";
			PlaySound("Voice\" + LanguageGetLanguage() + "\officer05.wav");
		break;
		
		//Матрос 2 на верхней палубе
		case "SharlieEpilog_Sailor_2":
			dialog.text = "When will those hourglasses ring? I'm about to swallow my own tongue.";
			link.l1 = "Patience, sailor.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Sailor_2";
			PlaySound("Voice\" + LanguageGetLanguage() + "\other\Matrosi na Korablyah-07.wav");
		break;
		
		//Матрос 3 на орудийной палубе
		case "SharlieEpilog_Sailor_3":
			dialog.text = "Did you see that rat run by? I swear, I've never seen one that big in my life!";
			link.l1 = "Well...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Sailor_3";
			PlaySound("Voice\" + LanguageGetLanguage() + "\other\Matrosi na Korablyah-04.wav");
		break;
		
		//Матрос 4 на орудийной палубе
		case "SharlieEpilog_Sailor_4":
			dialog.text = "What am I supposed to do now, monsieur? I got so drunk, I can't even remember how I ended up on this ship. I'm no sailor... And back home, I've got a wife and two kids.";
			link.l1 = "Should've drunk less. Now it's too late – you'll have to become a sailor.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Sailor_4";
			PlaySound("Voice\" + LanguageGetLanguage() + "\Ransack_2.wav");
		break;
		
		//Старший матрос
		case "SharlieEpilog_HighSailor_1":
			dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+pchar.lastname+". It is an honor to have you aboard our ship.";
			link.l1 = "You are most courteous, monsieur senior sailor. Courtesy is not the most common trait among seasoned sea dogs. But let’s not embarrass the crew – we’re not at His Majesty’s court, after all. Just call me captain.";
			link.l1.go = "SharlieEpilog_HighSailor_2";
			PlaySound("Voice\" + LanguageGetLanguage() + "\YoungMan03.wav");
		break;

		case "SharlieEpilog_HighSailor_2":
			dialog.text = "Well, I haven’t been a sailor for very long. I used to be a clerk for Monsieur Levasseur. But when he was… ahem… removed, a new governor took over. Word quickly spread in certain circles about what a scoundrel Monsieur de René de Boisdufle de Lestre turned out to be. That’s when I realized: I’d never find honest work again. People would think I knew everything—and kept quiet.";
			link.l1 = "And was it not so?";
			link.l1.go = "SharlieEpilog_HighSailor_3";
		break;

		case "SharlieEpilog_HighSailor_3":
			dialog.text = "Of course not. I never had the habit of meddling in other people's business. Besides, Levasseur punished curiosity harshly.";
			link.l1 = "I can easily believe that.";
			link.l1.go = "SharlieEpilog_HighSailor_4";
		break;

		case "SharlieEpilog_HighSailor_4":
			dialog.text = "So, after you dealt with him, I signed up as a sailor on the first pirate ship I could find. And strangely enough, I adapted and changed pretty quickly. I even managed to earn the respect of the most ruthless cutthroats. But what they were doing... It just wasn't for me. That's how I ended up here.";
			link.l1 = "So, you knew about my involvement in Levasseur's fate?";
			link.l1.go = "SharlieEpilog_HighSailor_5";
		break;

		case "SharlieEpilog_HighSailor_5":
			dialog.text = "Of course, Captain. And I'm glad you rid the world of that monster. At the same time, you pulled me out of my stuffy little room. Made me see my life in a whole new light.";
			link.l1 = "Amazing how small this world is...";
			link.l1.go = "SharlieEpilog_HighSailor_6";
		break;

		case "SharlieEpilog_HighSailor_6":
			dialog.text = "It may sound contradictory, but the world is just as small as it is vast.";
			link.l1 = "Funny. I never really thought about that.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_HighSailor_7";
		break;
		
		case "SharlieEpilog_HighSailor_7":
			dialog.text = "Captain "+pchar.lastname+"... Isn't it a wonderful evening?";
			link.l1 = "Perhaps. The only thing that could make it better would be a gentle northwesterly breeze.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_HighSailor_7";
			PlaySound("Voice\" + LanguageGetLanguage() + "\YoungMan03.wav");
		break;
		
		//Диалог с боцманом Моко
		case "SharlieEpilog_Moko_1":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "Captain "+pchar.lastname+"...";
				link.l1 = "Actually... Well, never mind. I remember you! Your name is Moko. Weren't you the one who drained an entire barrel of rum in one go?";
				link.l1.go = "SharlieEpilog_Moko_2";
			}
			else
			{
				dialog.text = "What do you want... monsieur?";
				link.l1 = "You don't meet a giant like you every day. What's your name?";
				link.l1.go = "SharlieEpilog_Moko_4";
			}
			PlaySound("Voice\" + LanguageGetLanguage() + "\citizen\Kapitani Korabley-07.wav");
		break;

		case "SharlieEpilog_Moko_2":
			dialog.text = "I... And I only woke up two days later.";
			link.l1 = "Anyone else in your place wouldn't have lasted even a couple of hours. If you fight the way you drink—Jean is damn lucky to have you as his boatswain.";
			link.l1.go = "SharlieEpilog_Moko_3";
		break;

		case "SharlieEpilog_Moko_3":
			dialog.text = "Just as I was lucky with my captain. Thanks to him, I found my freedom. And thanks to you. I’d still be rotting on the plantations if you hadn’t helped Jean.";
			link.l1 = "It was quite an adventure. And I’m glad it ended better than it might have.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Moko_repeat";
		break;
		
		case "SharlieEpilog_Moko_4":
			dialog.text = ""+npchar.name+". I'm the boatswain on this ship.";
			link.l1 = "Ha-ha, I'd like to see the one who dares to cross you. Have you been serving under the captain for long?";
			link.l1.go = "SharlieEpilog_Moko_5";
		break;

		case "SharlieEpilog_Moko_5":
			dialog.text = "A few years. I owe him a lot. If not for him, I would have rotted in...";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Moko_6";
		break;

		case "SharlieEpilog_Moko_6":
			dialog.text = "...";
			link.l1 = "You meant on the plantation?";
			link.l1.go = "SharlieEpilog_Moko_7";
		break;

		case "SharlieEpilog_Moko_7":
			dialog.text = "...";
			link.l1 = "Come on, "+npchar.name+", of course, you don't have to tell me anything, but if you haven't noticed yet, I'm not one of those powdered wig dandies. Did the captain bail you out?";
			link.l1.go = "SharlieEpilog_Moko_8";
		break;

		case "SharlieEpilog_Moko_8":
			dialog.text = "We escaped together. From the plantation in Maracaibo. Without Jean, we wouldn't have made it. Since then, I've been on his crew. First as a sailor, and now—I'm the boatswain.";
			link.l1 = "The captain was a slave? Never would have guessed. Well, I've got a few skeletons in my own closet too. Glad you managed to escape the Spanish boot, "+npchar.name+". So, how does it feel to be a sailor?";
			link.l1.go = "SharlieEpilog_Moko_9";
		break;

		case "SharlieEpilog_Moko_9":
			dialog.text = "Feels like I never truly lived before. The sea is my home now.";
			link.l1 = "Here I understand you, my friend. Like no one else.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Moko_repeat";
		break;
		
		case "SharlieEpilog_Moko_repeat":
			dialog.text = "Captain "+pchar.lastname+"... How can I help you?";
			link.l1 = "Thank you, "+npchar.name+", I don't need anything right now.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Moko_repeat";
		break;
		
		//Диалог с дворянином Бернардом
		case "SharlieEpilog_Bernard_1":
			dialog.text = ""+UpperFirst(GetTitle(NPChar,true))+"! How glad I am to see at least one sensible face aboard this ship. These... sailors... they're savages.";
			link.l1 = "If I were you, I wouldn't speak like that on someone else's ship. I don't know how you ended up in the Caribbean, but things work differently here, you know. You'd do well to show some respect to the crew.";
			link.l1.go = "SharlieEpilog_Bernard_2";
			PlaySound("Voice\" + LanguageGetLanguage() + "\citizen\Dvoryane-06.wav");
		break;

		case "SharlieEpilog_Bernard_2":
			dialog.text = "Respect? For them? They're savages! I'm a nobleman, "+GetTitle(NPChar,true)+", I'm used to order, to being served, to... civilization! Let them just try to cross me—my father will...";
			link.l1 = "Your father will hear that you died of fever on the way. And he’ll hardly be able to prove otherwise.";
			link.l1.go = "SharlieEpilog_Bernard_3";
		break;

		case "SharlieEpilog_Bernard_3":
			dialog.text = "Curse that Colonel Fox! It's all his fault! For his daughter, I crossed the ocean, gave up my comforts, endured those sideways glances, that dreadful food, this... endless rocking! And now I'm sailing on someone else's ship!";
			link.l1 = "Colonel Fox…";
			link.l1.go = "SharlieEpilog_Bernard_4";
		break;

		case "SharlieEpilog_Bernard_4":
			dialog.text = "Are you acquainted with him, "+GetTitle(NPChar,true)+"?";
			link.l1 = "Ahem... I've heard about him.";
			link.l1.go = "SharlieEpilog_Bernard_5";
		break;

		case "SharlieEpilog_Bernard_5":
			dialog.text = "Well, then you haven't missed much. That man is the very embodiment of blind military stubbornness and prejudice.";
			link.l1 = "He's a soldier...";
			link.l1.go = "SharlieEpilog_Bernard_6";
		break;

		case "SharlieEpilog_Bernard_6":
			dialog.text = "Exactly! That says it all. When I came to ask for a meeting with his daughter, do you know what he did? Do you? He threw me out! Without a single word!";
			link.l1 = "But you didn't back down, did you?";
			link.l1.go = "SharlieEpilog_Bernard_7";
		break;

		case "SharlieEpilog_Bernard_7":
			dialog.text = "Of course! I spent a whole week trying to get an audience! I humbled myself! I even... tried to bribe the guards! In the end, I managed to slip in without an invitation. I just wanted to talk!";
			link.l1 = "I don't think he was too pleased about that.";
			link.l1.go = "SharlieEpilog_Bernard_8";
		break;

		case "SharlieEpilog_Bernard_8":
			dialog.text = "Happy to see me? Oh, he threw a real tantrum! I was thrown out, forbidden to approach the residence, my father's ship was confiscated, and then they even forbade all English captains from letting me on board! I had to look for a French ship on Martinique... It was a nightmare.";
			link.l1 = "Looks like you really made him angry.";
			link.l1.go = "SharlieEpilog_Bernard_9";
		break;

		case "SharlieEpilog_Bernard_9":
			dialog.text = "He was always against me. His favorite saying was: 'An officer's daughter is an officer's wife.' You, "+GetTitle(NPChar,true)+", he considered a far more suitable match.";
			link.l1 = "Perhaps this time he had other reasons as well...";
			link.l1.go = "SharlieEpilog_Bernard_10";
		break;

		case "SharlieEpilog_Bernard_10":
			dialog.text = "...";
			link.l1 = "So, you've come here to see your beloved.";
			link.l1.go = "SharlieEpilog_Bernard_11";
		break;

		case "SharlieEpilog_Bernard_11":
			dialog.text = "Yes. I haven't received a single letter from her since she left Europe. I'm sure her father is simply intercepting the mail. She couldn't have forgotten me! Of course, she was reserved with me... even cold... But I can't believe she's erased me from her life.";
			link.l1 = "My condolences, monsieur. Wounds of the heart heal far slower than those of the flesh. But wait... Why are you, an Englishman, heading to Bordeaux?";
			link.l1.go = "SharlieEpilog_Bernard_12";
		break;

		case "SharlieEpilog_Bernard_12":
			dialog.text = "I'm not about to return home in disgrace. I'll have to stay with my uncle in Bordeaux until things settle down. Still, his estate is far more spacious and elegant than ours. And his servants are much better trained.";
			link.l1 = "Well, I suppose this isn't the worst outcome. You might even find yourself another sweetheart. Bordeaux is full of young beauties, believe me.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Bernard_repeat";
		break;
		
		case "SharlieEpilog_Bernard_repeat":
			dialog.text = "When will we finally arrive, "+GetTitle(NPChar,true)+"? I am unbearably suffering surrounded by all these... gentlemen. I simply must take a bath at once.";
			link.l1 = "I'm afraid, for the next two months all you can do is dream about her.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Bernard_repeat";
			PlaySound("Voice\" + LanguageGetLanguage() + "\citizen\Dvoryane-06.wav");
		break;
		
		//Диалог с Книппелем на корабле Улисс
		case "SharlieEpilog_Knippel_1":
			dialog.text = "Curse this dead calm, may chain shot take it.";
			link.l1 = "Don't grumble, "+npchar.name+", sooner or later the wind will rise.";
			link.l1.go = "SharlieEpilog_Knippel_2";
		break;

		case "SharlieEpilog_Knippel_2":
			dialog.text = "And what am I supposed to do until then, sir? I can't even inspect the cannons... We're on someone else's ship, after all.";
			link.l1 = "Try to just relax. You don't have to work all the time.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Knippel_repeat";
		break;
		
		case "SharlieEpilog_Knippel_repeat":
			dialog.text = "Blasted calm...";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Knippel_repeat";
		break;
		
		//Диалог с Лонгвэем на корабле Улисс
		case "SharlieEpilog_Longway_1":
			dialog.text = "Not a bad ship, Captain. Do you think so too?";
			link.l1 = "Even better than Meifeng?";
			link.l1.go = "SharlieEpilog_Longway_2";
		break;

		case "SharlieEpilog_Longway_2":
			dialog.text = "For "+npchar.name+" there's no ship better than the Meifeng. This ship will never sail as close to the wind as she did.";
			link.l1 = "Calm down, "+npchar.name+", I was only joking. Of course, Meifeng is in a league of her own. But Ulysses is a fine ship too. Solid.";
			link.l1.go = "SharlieEpilog_Longway_3";
		break;

		case "SharlieEpilog_Longway_3":
			dialog.text = ""+npchar.name+" to take the helm. To feel the ship respond to your hand...";
			link.l1 = "Alas, my friend, this ship belongs to someone else. Better go ask that big fellow over there to spar with you. It’ll do you both some good.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Longway_repeat";
		break;
		
		case "SharlieEpilog_Longway_repeat":
			dialog.text = "How fast could we go if the wind is with us?";
			link.l1 = "I can't say for sure, "+npchar.name+". Better ask their navigator.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Longway_repeat";
		break;
		
		//Диалог с Тонзагом на корабле Улисс
		case "SharlieEpilog_Tonzag_1":
			dialog.text = "Did you see the giant they've got for a boatswain here? They say he can crush a coconut with one hand.";
			link.l1 = "Ha-ha. Looks like you’re a bit afraid of him, aren’t you?";
			link.l1.go = "SharlieEpilog_Tonzag_2";
		break;

		case "SharlieEpilog_Tonzag_2":
			dialog.text = "Why would that matter? Size isn't everything. I've handled much bigger ones before.";
			link.l1 = "Then maybe you should challenge him to a fistfight? One on one – fair and square.";
			link.l1.go = "SharlieEpilog_Tonzag_3";
		break;

		case "SharlieEpilog_Tonzag_3":
			dialog.text = "Argh...";
			link.l1 = "You've gone a bit pale. Ha-ha. Well, if not, then not. Let's spare your not-so-young bones.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Tonzag_repeat";
		break;
		
		case "SharlieEpilog_Tonzag_repeat":
			dialog.text = "There are so many fish in these waters you could scoop them up with a boat, but these layabouts couldn't even be bothered to cast a net.";
			link.l1 = "Go talk to their boatswain. I think he'll appreciate your comment, heh-heh.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Tonzag_repeat";
		break;
		
		//Диалог с Тичингиту, охраняющим золото
		case "SharlieEpilog_Tichingitu_21":
			dialog.text = "The gold is safe, Captain "+pchar.name+". Tichingitu will guard him well.";
			link.l1 = "Thank you, my friend. Alonso will relieve you soon.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Tichingitu_21";
		break;
		
		//Диалог с Книппелем, охраняющим золото
		case "SharlieEpilog_Knippel_21":
			dialog.text = "Blow me down, sir, there are more rats on this tub than I've seen in my entire life.";
			link.l1 = "The ship had been left in the harbor for too long, without proper care. The new crew will soon get rid of them.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Knippel_21";
		break;
		
		//Диалог с Лонгвэем, охраняющим золото
		case "SharlieEpilog_Longway_21":
			dialog.text = "Longway hears the rattle of chains. Captain, have you dropped anchor?";
			link.l1 = "It was our passenger who blew the fuse. The wind is still very weak for now, but I hope it won't last long.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Longway_21";
		break;
		
		//Диалог с Тонзагом, охраняющим золото
		case "SharlieEpilog_Tonzag_21":
			dialog.text = "Yeah, damn it... I wouldn't mind a mug of strong rum right now.";
			link.l1 = "Dinner will be ready soon, hang in there. Alonso will take over for you.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Tonzag_21";
		break;
		
		//Диалог с Мэри перед походом в каюту
		case "SharlieEpilog_Mary_11":
			dialog.text = "...";
			link.l1 = ""+npchar.name+", my love, how are you feeling?";
			link.l1.go = "SharlieEpilog_Mary_12";
			DelLandQuestMark(npchar);
		break;

		case "SharlieEpilog_Mary_12":
			dialog.text = "...";
			link.l1 = "Come on, darling, are you really upset with me just because I went to the shop for some wine?";
			link.l1.go = "SharlieEpilog_Mary_13";
		break;

		case "SharlieEpilog_Mary_13":
			dialog.text = "Off to the shop for wine, were you? You could have at least warned me! How am I supposed to know you weren’t at a brothel—with some woman… or with all of them at once?!";
			link.l1 = "Darling, would I really take such risks? I have the most beautiful, clever, and wildly jealous wife in the whole archipelago. Do you really think I'd waste my time on some cheap dockside girls?";
			link.l1.go = "SharlieEpilog_Mary_14";
		break;

		case "SharlieEpilog_Mary_14":
			dialog.text = "You could’ve at least said a word to me, alright! I was sitting there and…";
			link.l1 = "I promise, next time I won’t just tell you about it – I’ll take you with me. But right now… I suddenly got curious if everything’s alright with the furniture in the captain’s cabin. Especially the bed. Shall we check?";
			link.l1.go = "SharlieEpilog_Mary_15";
		break;

		case "SharlieEpilog_Mary_15":
			dialog.text = ""+pchar.name+"... And what if someone comes in?\nHmm... now I want it even more.";
			link.l1 = "Then let's not waste a single second.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_1");
		break;
		
		//Диалог с Элен перед походом в каюту
		case "SharlieEpilog_Helena_11":
			dialog.text = "...";
			link.l1 = ""+npchar.name+", my love, how are you feeling?";
			link.l1.go = "SharlieEpilog_Helena_12";
			DelLandQuestMark(npchar);
		break;

		case "SharlieEpilog_Helena_12":
			dialog.text = "...";
			link.l1 = "Come on, darling, are you really upset with me just because I went to the shop for some wine?";
			link.l1.go = "SharlieEpilog_Helena_13";
		break;

		case "SharlieEpilog_Helena_13":
			dialog.text = "You could have taken me with you. Or do you think I’d have done worse than your little partners in crime?";
			link.l1 = "I think you would easily outshine them. But then, wine would be the last thing on my mind.";
			link.l1.go = "SharlieEpilog_Helena_14";
		break;

		case "SharlieEpilog_Helena_14":
			dialog.text = "And what about?";
			link.l1 = "About slipping away with you right then and there… And I can’t get that thought out of my head right now.";
			link.l1.go = "SharlieEpilog_Helena_15";
		break;

		case "SharlieEpilog_Helena_15":
			dialog.text = "Is that so? And where exactly do you plan to hide from prying eyes?";
			link.l1 = "In the captain's cabin. I suppose we ought to test the sturdiness of his bed.";
			link.l1.go = "SharlieEpilog_Helena_16";
		break;

		case "SharlieEpilog_Helena_16":
			dialog.text = "Ha-ha. What if the captain catches us?\nAlthough… just the thought of it makes my heart beat faster.";
			link.l1 = "Then let's not waste any time!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_1");
		break;
		
		//Диалог с Мэри в каюте
		case "SharlieEpilog_Mary_21":
			dialog.text = "It was wonderful, my captain...\nI have some news for you.";
			link.l1 = "News? I'm all ears.";
			link.l1.go = "SharlieEpilog_Mary_22";
			SharlieEpilog_LoveInCabin_CameraDialog();
		break;

		case "SharlieEpilog_Mary_22":
			dialog.text = ""+pchar.name+"... We're going to have a child. I'm pregnant, alright.";
			link.l1 = "My love... Is it true?";
			link.l1.go = "SharlieEpilog_Mary_23";
		break;

		case "SharlieEpilog_Mary_23":
			dialog.text = "You're going to be a father, "+pchar.name+"!";
			link.l1 = ""+npchar.name+"... This is incredible!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_6");
		break;
		
		case "SharlieEpilog_Mary_31":
			dialog.text = "Are you happy, my love?";
			link.l1 = "Happy? Are you kidding? Damn it, I'm the happiest man alive! But... why didn't you tell me sooner?";
			link.l1.go = "SharlieEpilog_Mary_32";
		break;

		case "SharlieEpilog_Mary_32":
			dialog.text = "To delay our departure? I really want to meet your father, "+pchar.name+".";
			link.l1 = ""+npchar.name+"... I love you!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_9");
		break;
		
		//Диалог с Элен в каюте
		case "SharlieEpilog_Helena_21":
			dialog.text = "You were, as always, at your best, darling. I have some news for you.";
			link.l1 = "News? I'm all ears.";
			link.l1.go = "SharlieEpilog_Helena_22";
			SharlieEpilog_LoveInCabin_CameraDialog();
		break;

		case "SharlieEpilog_Helena_22":
			dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+GetFullName(pchar)+", Chevalier de Monpe - you are going to be a father.";
			link.l1 = "Is... is it true?";
			link.l1.go = "SharlieEpilog_Helena_23";
		break;

		case "SharlieEpilog_Helena_23":
			dialog.text = "As true as the name I bear "+npchar.name+". In less than six months, we'll have a child—a little Monsieur de Mor... or perhaps, a Mademoiselle.";
			link.l1 = "Hélène... This is incredible!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_6");
		break;
		
		case "SharlieEpilog_Helena_31":
			dialog.text = "...";
			link.l1 = "So that's why you didn't drink with us to celebrate our departure! But… why didn't you tell me before?";
			link.l1.go = "SharlieEpilog_Helena_32";
		break;

		case "SharlieEpilog_Helena_32":
			dialog.text = "I was afraid you’d decide not to risk it and stay in the archipelago. I wanted you to fulfill your father’s request. And… I really want to meet him myself.";
			link.l1 = ""+npchar.name+"… I love you!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_9");
		break;
		
		// Диалог с Пикаром
		case "SharlieEpilog_PikarInCabin_1":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "Well, well... And what are we doing here? Making little Gascons?";
				link.l1 = "Ha-ha-ha! I'm going to have a son, "+npchar.name+"! I'm going to be a father!";
				link.l1.go = "SharlieEpilog_PikarInCabin_1_1";
			}
			else
			{
				dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+pchar.lastname+". Don't you think using the captain's cabin without his knowledge is a bit much, even for someone of your rank?";
				link.l1 = "I'm sorry, Captain. But I have a good reason! I'm going to be a father!";
				link.l1.go = "SharlieEpilog_PikarInCabin_12";
			}
			SharlieEpilog_PikarInCabin_camera_2();
		break;
		
		case "SharlieEpilog_PikarInCabin_1_1":
			locCameraSleep(true);
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				StartInstantDialogTurnToNPC("Helena", "SharlieEpilog_PikarInCabin_2", "Quest\Sharlie\Epilog.c", "Blaze");
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				StartInstantDialogTurnToNPC("Mary", "SharlieEpilog_PikarInCabin_2", "Quest\Sharlie\Epilog.c", "Blaze");
			}
		break;

		case "SharlieEpilog_PikarInCabin_2":
			dialog.text = "Or a daughter!";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_PikarInCabin_2_1";
		break;
		
		case "SharlieEpilog_PikarInCabin_2_1":
			StartInstantDialogTurnToNPC("SharlieEpilog_Pikar", "SharlieEpilog_PikarInCabin_3", "Quest\Sharlie\Epilog.c", "Blaze");
		break;

		case "SharlieEpilog_PikarInCabin_3":
			dialog.text = "And you kept this from me, you scoundrel? I thought you were my friend!";
			link.l1 = "I just found out myself! Can you believe it? Me! I'm going to be a father!";
			link.l1.go = "SharlieEpilog_PikarInCabin_4";
		break;

		case "SharlieEpilog_PikarInCabin_4":
			dialog.text = "Ha-ha-ha! You really are happy, my friend! I've never seen you like this before\nWell, you two keep chatting, and I'll get the cannons ready for the celebratory salute. Let me know when you're ready to give the order.";
			link.l1 = "...";
			link.l1.go = "exit";
			locCameraSleep(false);
			SharlieEpilog_PikarInCabin_camera_1();
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_13");
		break;

		case "SharlieEpilog_PikarInCabin_12":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				sld = CharacterFromID("Helena");
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				sld = CharacterFromID("Mary");
			}
			dialog.text = "Ha... Believe me, I had a feeling why you came here.";
			link.l1 = "No, of course not! "+sld.name+" I'm pregnant! I'm going to have a son!";
			link.l1.go = "SharlieEpilog_PikarInCabin_12_1";
		break;
		
		case "SharlieEpilog_PikarInCabin_12_1":
			locCameraSleep(true);
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				StartInstantDialogTurnToNPC("Helena", "SharlieEpilog_PikarInCabin_13", "Quest\Sharlie\Epilog.c", "Blaze");
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				StartInstantDialogTurnToNPC("Mary", "SharlieEpilog_PikarInCabin_13", "Quest\Sharlie\Epilog.c", "Blaze");
			}
		break;

		case "SharlieEpilog_PikarInCabin_13":
			dialog.text = "Or a daughter!";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_PikarInCabin_13_1";
		break;
		
		case "SharlieEpilog_PikarInCabin_13_1":
			StartInstantDialogTurnToNPC("SharlieEpilog_Pikar", "SharlieEpilog_PikarInCabin_14", "Quest\Sharlie\Epilog.c", "Blaze");
		break;

		case "SharlieEpilog_PikarInCabin_14":
			dialog.text = "Ahem... Well, my heartfelt congratulations!\nI'll see to it—there will be a celebratory broadside from all the guns. Just let me know when you're ready to give the order.\nIn the meantime... the cabin is at your disposal.";
			link.l1 = "...";
			link.l1.go = "exit";
			locCameraSleep(false);
			SharlieEpilog_PikarInCabin_camera_1();
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_13");
		break;
		
		// Диалог с Пикаром после интима с женой
		case "SharlieEpilog_PikarZalp_1":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "Ahem... Well, father... I see you’re eager to make another heir right away, huh?";
				link.l1 = "Ha-ha! If it were up to me, I'd make a whole dozen at once! So, my friend, shall we fire a broadside with all guns?";
				link.l1.go = "SharlieEpilog_PikarZalp_2";
				link.l2 = "I'm afraid it doesn't work that way, my friend. But we did our best.";
				link.l2.go = "exit";
			}
			else
			{
				dialog.text = ""+UpperFirst(GetTitle(NPChar,true))+"...";
				link.l1 = "So, Captain, shall we fire a broadside with all guns?";
				link.l1.go = "SharlieEpilog_PikarZalp_3";
				link.l2 = "Not now.";
				link.l2.go = "exit";
			}
			NextDiag.TempNode = "SharlieEpilog_PikarZalp_1";
		break;
		
		case "SharlieEpilog_PikarZalp_2":
			dialog.text = "The crew is just waiting for your orders! Give the word, "+GetTitle(NPChar,true)+".";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_PikarZalp_final";
			DelLandQuestMark(npchar);
		break;
		
		case "SharlieEpilog_PikarZalp_3":
			dialog.text = "The crew is ready. Give the order.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_PikarZalp_final";
			DelLandQuestMark(npchar);
		break;
		
		case "SharlieEpilog_PikarZalp_final":
			dialog.text = "...";
			link.l1 = "Gunners! Fire all guns! Fire!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_ZalpInSea");
			locCameraFromToPos(-9.34, 8.28, -16.03, true, -9.33, 7.32, -20.48);
			CharacterTurnToLoc(pchar, "quest", "quest10");
			CharacterTurnToLoc(npchar, "quest", "quest10");
		break;
		
		// Диалог с отцом в поместье де Монпе
		case "SharlieEpilog_HenriDeMonper_1":
			NextMonth = GetDataMonth() + 2;
			if (NextMonth == 13) NextMonth = 1;
			else if (NextMonth == 14) NextMonth = 2;
			Month = XI_ConvertString("MonthVoc_" + NextMonth);
			dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+pchar.lastname+"... How glad I am to see you, my son!";
			if (GetDataMonth() >= 4 && GetDataMonth() <= 10)
			{
				link.l1 = "Father... I can't believe I'm home again... I'd almost forgotten what snow looks like. It feels like nothing has changed here at all...";
			}
			else
			{
				link.l1 = "Father... I can't believe I'm home again... Seems even the snow decided to fall for the occasion. "+month+". Nothing has changed here at all...";
			}
			link.l1.go = "SharlieEpilog_HenriDeMonper_2";
			locCameraFromToPos(-8.76, 7.86, 0.75, true, -7.41, 6.11, 0.18);
			Achievment_Set("ach_CL_202");
		break;
		
		case "SharlieEpilog_HenriDeMonper_2":
			dialog.text = "And the same can't be said about you! The way you carry yourself, your walk, those scars\n"+"No, standing before me is no longer the spoiled boy I once sent off to distant lands.";
			link.l1 = "You grow up fast in the Caribbean, Father. But we'll have time to talk about that later. Tell me, how is your health? I hope the illness has retreated, since you're standing before me in full regalia?";
			link.l1.go = "SharlieEpilog_HenriDeMonper_3";
		break;
		
		case "SharlieEpilog_HenriDeMonper_3":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				dialog.text = "Alas, "+pchar.name+", she only clung tighter to my neck. But could I really greet my beloved son in ordinary clothes? For me, this is a great day, "+pchar.name+"\n"+"Seems like you have someone to introduce me to.";
				link.l1 = "...";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("SharlieEpilog_InEstateDeMonpe_10");
			}
			else
			{
				dialog.text = "Alas, "+pchar.name+", her grip only grows stronger with the years. But could I really meet my beloved son in ordinary attire? For me, this is a great day, "+pchar.name+"\n"+"I see you haven't come alone\n"+"You must be hungry after your journey? Suzanne has prepared goose liver just the way you like it!\n"+"Come to the table – you can introduce us on the way!";
				link.l1 = "I must admit, I caught that scent even as I was approaching the estate!";
				link.l1.go = "SharlieEpilog_HenriDeMonper_8"; // заходят в поместье
			}
		break;
		
		case "SharlieEpilog_HenriDeMonper_4":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = CharacterFromID("Helena");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld = CharacterFromID("Mary");
			dialog.text = "...";
			link.l1 = "Father, allow me to introduce my wife - "+sld.name+" "+pchar.lastname+". "+sld.name+", this is my father - the chevalier "+GetCharacterName("Henri")+" "+GetCharacterName("de Monper")+".";
			link.l1.go = "SharlieEpilog_HenriDeMonper_5";
			SharlieEpilog_InEstateDeMonpe_11_1();
		break;
		
		case "SharlieEpilog_HenriDeMonper_5":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				sld = CharacterFromID("Helena");
				dialog.text = ""+pchar.name+", I am truly enchanted! Your bride is nothing like the spoiled society ladies we are used to here. I dare say she handles a ship just as skillfully as she does my son's heart.";
				link.l1 = "...";
				link.l1.go = "SharlieEpilog_HenriDeMonper_Helena_1";
				CharacterTurnByChr(npchar, sld);
			}
			else
			{
				sld = CharacterFromID("Mary");
				dialog.text = "It is a great pleasure to meet you, madam. I assure you, my son has excellent taste!";
				link.l1 = "...";
				link.l1.go = "SharlieEpilog_HenriDeMonper_Mary_1";
				CharacterTurnByChr(npchar, sld);
			}
		break;
		
		case "SharlieEpilog_HenriDeMonper_Helena_1":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_HenriDeMonper_Helena_1");
		break;
		
		case "SharlieEpilog_HenriDeMonper_Helena_2":
			dialog.text = "I am flattered, chevalier! You are right, I truly can hold the helm even in the fiercest storm. However, as for your son's heart—there is no need to steer it. We are united in our goals and aspirations.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_HenriDeMonper_Helena_2_1";
			SharlieEpilog_InEstateDeMonpe_11_2();
		break;
		
		case "SharlieEpilog_HenriDeMonper_Helena_2_1":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_HenriDeMonper_Helena_2_1");
		break;
		
		case "SharlieEpilog_HenriDeMonper_Helena_3":
			dialog.text = "Abbot Benoit described you as a wise and courageous young woman – and it seems he did not exaggerate. I am glad that "+pchar.name+" I found in you not just a wife, but a true companion in spirit\n"+"You must be hungry after your journey. Suzanne has prepared goose liver just the way you like it!\n"+"Well then, everyone, please join us at the table! And on the way, I hope we'll all get to know each other better.";
			link.l1 = "I must admit, I caught that scent even as I was approaching the estate!";
			link.l1.go = "SharlieEpilog_HenriDeMonper_6";
			SharlieEpilog_InEstateDeMonpe_11_1();
		break;
		
		case "SharlieEpilog_HenriDeMonper_Mary_1":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_HenriDeMonper_Mary_1");
		break;
		
		case "SharlieEpilog_HenriDeMonper_Mary_2":
			dialog.text = "Pleased to meet you, chevalier! "+pchar.name+" I've heard so much about you, and I imagined you just like this, alright!";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_HenriDeMonper_Mary_2_1";
			CharacterTurnByChr(pchar, npchar);
			SharlieEpilog_InEstateDeMonpe_11_2();
		break;
		
		case "SharlieEpilog_HenriDeMonper_Mary_2_1":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_HenriDeMonper_Mary_2_1");
		break;
		
		case "SharlieEpilog_HenriDeMonper_Mary_3":
			sld = CharacterFromID("Mary");
			dialog.text = ""+pchar.name+", I'm enchanted! Your bride is nothing like those powdered ladies of the salons – and that's her true worth\n"+"I think you chose a beautiful rose over pampered, fickle lilies.";
			link.l1 = "The Wild Rose, Father… "+sld.name+"  - a true treasure. I'm sure you'll agree with me once you get to know her better.";
			link.l1.go = "SharlieEpilog_HenriDeMonper_Mary_4";
			SharlieEpilog_InEstateDeMonpe_11_1();
		break;
		
		case "SharlieEpilog_HenriDeMonper_Mary_4":
			if (GetAttributeInt(pchar, "questTemp.SharlieEpilog_Friends") >= 2) sStr = "ты познакомишь меня с остальными";
			else sStr = "ты представишь меня нашему гостю";
			dialog.text = "Then let's not delay this moment! You must be hungry after your journey. Suzanne has prepared goose liver just the way you like it!\n"+"Everyone, to the table! And on the way, I hope "+sStr+"";
			link.l1 = "I must admit, I caught that scent even as I was approaching the estate!";
			link.l1.go = "SharlieEpilog_HenriDeMonper_6";
			CharacterTurnByChr(CharacterFromID("HenriDeMonper"), pchar);
		break;
		
		case "SharlieEpilog_HenriDeMonper_6":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_InEstateDeMonpe_14");
		break;
		
		case "SharlieEpilog_HenriDeMonper_7":
			dialog.text = "...";
			link.l1 = "Darling, you simply must try this—nothing can compare to goose liver prepared with our family recipe! It was passed down from our grandfather—he received it as a gift from some Mediterranean country.";
			link.l1.go = "SharlieEpilog_HenriDeMonper_8"; // заходят в поместье
			SharlieEpilog_InEstateDeMonpe_11_1();
		break;
		
		case "SharlieEpilog_HenriDeMonper_8":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_InEstateDeMonpe_15");
		break;
		
		// диалог на ужине в поместье де Монпе
		case "SharlieEpilog_InKitchenDeMonpe":
			dialog.text = "";
			link.l1 = "I don't want to begin our feast on a somber note, but as a family, we must remember those who came before us. I ask you to raise your glasses to Michel. May the Lord grant peace to his soul.";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_2";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_2":
			dialog.text = "";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_3";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_3":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				if (GetAttributeInt(pchar, "questTemp.SharlieEpilog_Friends") >= 2) sStr = "добрых друзей";
				else sStr = "соратника";
				dialog.text = "";
				link.l1 = "I have so many questions to ask you, "+pchar.name+"... But first, let your wife have her say and "+sStr+". Please, tell me how you met Charles.";
			}
			else
			{
				if (GetAttributeInt(pchar, "questTemp.SharlieEpilog_Friends") >= 2) sStr = "твоих добрых друзей";
				else sStr = "твоего друга";
				dialog.text = "";
				link.l1 = "I have so many questions to ask you, "+pchar.name+"... But first, let me say something "+sStr+". Please, tell me, how did you meet Charles?";
			}
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_4";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		// if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
		
		case "SharlieEpilog_InKitchenDeMonpe_4":
			dialog.text = "";
			link.l1 = "I’m just as eager to hear this as you are!";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_5";
			}
			else if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_6";
			}
			else if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7";
			}
			else
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_8";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_5":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				link.l1 = "My life was in mortal danger... "+pchar.name+", like a true gentleman, he didn't let anything bad happen! He stood up for me and dealt with those scoundrels, alright!";
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l1 = ""+pchar.name+" snatched me from the hands of an English scoundrel who dared... to kidnap me. If you had arrived even an hour later, we would never have met.";
			}
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_5_1";
			SharlieEpilog_InKitchenDeMonpe_camera_Wife();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_5_1":
			dialog.text = "";
			link.l1 = "I never doubted he would act as a true nobleman should. Honor is more than just a word for our family. I am proud of you, my son.";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_6";
			}
			else if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7";
			}
			else
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_8";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_6":
			sld = CharacterFromID("Tichingitu");
			dialog.text = "";
			link.l1 = ""+sld.name+" sneak into pale-face's house to find food. Pale-face catch "+sld.name+" - and thrown into prison. Captain "+pchar.name+" come and rescue "+sld.name+" from prison. Since then "+sld.name+" serve the captain "+pchar.name+" and be faithful until my last breath.";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_6_1";
			SharlieEpilog_InKitchenDeMonpe_camera_Tichingitu();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_6_1":
			sld = CharacterFromID("Tichingitu");
			dialog.text = "";
			link.l1 = "It warms my heart to know that my son is not only a nobleman, but also a man of kindness. I am glad he has such loyal friends by his side, like you, "+sld.name+".";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7";
			}
			else
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_8";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_7":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel"))
			{
				link.l1 = "The captain once came to my house looking for work. I gave him a task, and he did it well. The boss took a liking to him and kept pulling him deeper into his affairs, while I was sent to his ship—to keep an eye on things... And then that... mister quietly weighed anchor, cannonball to my beard, and left the archipelago without saying a word to the captain. Left him alone in the mess he’d stirred up himself. I offered the captain my services, and though Richard treated him foully—cannonball to his stern—the captain didn’t turn me away.";
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7_2";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway"))
			{
				link.l1 = "Longway and the good captain worked for the same man. But that man betrayed Longway. So Longway decided: never serve that man again. The good captain took me aboard his ship as an officer, and did a great deal for Longway.";
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7_2";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1 = "The first time we crossed paths was in the tavern at Bridgetown: "+pchar.name+" He was looking for a cause, and I needed a reliable hand. That meeting was just the beginning—soon after, events unfolded that bound our fates together. I became his officer, and now I can call him my friend without hesitation—a man I'd risk my life for.";
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7_2";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Gambitnik();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_7_2":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel"))
			{
				link.l1 = "To see the person behind the circumstances is a rare gift. I suppose this means my son is not without good sense.";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway"))
			{
				link.l1 = "I'm glad my son is not just a heartless soldier, but a true leader who knows how to look after his companions.";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1 = "It's not every day you hear words like that. I suppose it's the best proof that my son is not only a skilled sailor, but also a true friend.";
			}
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_8";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_8":
			dialog.text = "";
			link.l1 = "We met in Bordeaux. The Cap boarded our ship as a passenger, and we took him to Martinique. Ever since then—up until we were sent here—I remained the voice of his crew and watched as "+GetFullName(pchar)+" step by step, he became the man he is today.";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_8_1";
			SharlieEpilog_InKitchenDeMonpe_camera_Alonso();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_8_1":
			dialog.text = "";
			link.l1 = "So, you knew Charles back when he was that insufferable youngster I insisted leave our home? I believe, monsieur, you and I will have much to discuss.";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_9";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_9":
			dialog.text = "";
			link.l1 = "My dear "+pchar.name+", you have come a long and glorious way... You set out into the wild savannah just for a rabbit’s pelt, but ended up fighting a lion, and returned in triumph, carrying its skin on your shoulders. Now, more than ever, I am at peace about the fate of our estate and all our lands.";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_10";
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_10":
			dialog.text = "";
			link.l1 = "I can't wait to hand over the reins of our family's affairs to you as soon as possible. There will be no shortage of work, but I believe the Lord Himself looks upon you with favor, and you will not only preserve the legacy entrusted to you, but also increase the honor and fortune of the de Montpe family.";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_11";
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_11": //выбор Шарля
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l1 = "It is a great honor for me to be your son and heir. I will gladly take on all the responsibilities for our family. I am certain my wife will be a steadfast support to me in this. I promise to do everything in my power to bring even greater glory to our name... And the first step toward our family's prosperity will be the birth of a child!";
				link.l1.go = "SharlieEpilog_ChooseEstate_HaveWife_1";
			}
			else
			{
				link.l1 = "It is a great honor for me to be your son and heir. I will gladly take on all the responsibilities for our family, and I promise to do everything in my power to bring even greater glory to our name.";
				link.l1.go = "SharlieEpilog_ChooseEstate_Single_1";
			}
			link.l2 = "Father, my years in the New World have changed me. I'm afraid I can no longer settle into the measured pace of life here in Europe.";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l2.go = "SharlieEpilog_ChooseCaribbean_HaveWife_1";
			}
			else
			{
				link.l2.go = "SharlieEpilog_ChooseCaribbean_Single_1";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		// --> Выбрал остаться в поместье с женой
		case "SharlieEpilog_ChooseEstate_HaveWife_1":
			dialog.text = "";
			link.l1 = ""+pchar.name+", could it be...";
			link.l1.go = "SharlieEpilog_HaveWife_12";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
			pchar.questTemp.SharlieEpilog_ChooseEstate = true;
		break;
		
		case "SharlieEpilog_HaveWife_12":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = CharacterFromID("Helena");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld = CharacterFromID("Mary");
			dialog.text = "";
			link.l1 = "Yes, Father. "+sld.name+" pregnant.";
			link.l1.go = "SharlieEpilog_HaveWife_13";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_HaveWife_13":
			dialog.text = "";
			link.l1 = "These are truly wonderful news, my dear son! The Lord has heard my prayers! Let all present here bear witness: in honor of the newborn, I shall host the grandest ball our estate has ever seen! Let us raise our glasses—to the heir!";
			link.l1.go = "SharlieEpilog_HaveWife_14";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_HaveWife_14":
			dialog.text = "";
			link.l1 = "Or an heiress!";
			link.l1.go = "SharlieEpilog_HaveWife_15";
			SharlieEpilog_InKitchenDeMonpe_camera_Wife();
		break;
		
		case "SharlieEpilog_HaveWife_15":
			dialog.text = "";
			link.l1 = "To a new chapter in our family’s story!";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
			{
				link.l1.go = "SharlieEpilog_HaveWife_16";
			}
			else if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_HaveWife_17";
			}
			else
			{
				link.l1.go = "SharlieEpilog_HaveWife_18";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_HaveWife_16":
			dialog.text = "";
			link.l1 = "To a future warrior or a good daughter!";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_HaveWife_17";
			}
			else
			{
				link.l1.go = "SharlieEpilog_HaveWife_18";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Tichingitu();
		break;
		
		case "SharlieEpilog_HaveWife_17":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel"))
			{
				link.l1 = "To the robust health of the newborn!";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway"))
			{
				link.l1 = "To the chance that brought you together!";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1 = "To the bright future of your family!";
			}
			link.l1.go = "SharlieEpilog_HaveWife_18";
			SharlieEpilog_InKitchenDeMonpe_camera_Gambitnik();
		break;
		
		case "SharlieEpilog_HaveWife_18":
			dialog.text = "";
			link.l1 = "To the future Alonso de Mor or little Alonsita de Mor!";
			link.l1.go = "SharlieEpilog_HaveWife_19";
			SharlieEpilog_InKitchenDeMonpe_camera_Alonso();
		break;
		
		case "SharlieEpilog_HaveWife_19":
			dialog.text = "";
			link.l1 = "Ah-ha-ha!";
			link.l1.go = "SharlieEpilog_HaveWife_20";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_HaveWife_20":
			dialog.text = "";
			link.l1 = "Ha-ha!";
			link.l1.go = "SharlieEpilog_HaveWife_21";
			SharlieEpilog_InKitchenDeMonpe_camera_Wife();
		break;
		
		case "SharlieEpilog_HaveWife_21":
			dialog.text = "";
			link.l1 = "Ha-ha-ha!";
			link.l1.go = "SharlieEpilog_toast";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_toast":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_toast");
		break;
		// <-- Выбрал остаться в поместье с женой
		
		// --> Выбрал остаться в поместье будучи холостяком
		case "SharlieEpilog_ChooseEstate_Single_1":
			dialog.text = "";
			link.l1 = "It is a great honor for me to be your son and heir. I will gladly take on all the responsibilities for our family and promise to do everything in my power to bring even greater glory to our name.";
			link.l1.go = "SharlieEpilog_ChooseEstate_Single_2";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
			pchar.questTemp.SharlieEpilog_ChooseEstate = true;
		break;
		
		case "SharlieEpilog_ChooseEstate_Single_2":
			dialog.text = "";
			link.l1 = "Tell me, "+pchar.name+", have you given any thought to my proposal to marry Yvonne?";
			link.l1.go = "SharlieEpilog_Single_13";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_Single_13":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_ChooseCaribbean"))
			{
				link.l1 = "I’ll admit it, Father… Yvonne was never truly close to my heart. But there are many wonderful women in the New World. I promise you—when I meet the right one, I won’t hesitate.";
			}
			else
			{
				link.l1 = "I'll admit it, Father... Yvonne was never close to my heart. But there are plenty of wonderful girls in France. I promise you—when I meet someone truly worthy, I won't hesitate.";
			}
			link.l1.go = "SharlieEpilog_Single_14";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_Single_14":
			dialog.text = "";
			link.l1 = "I like your spirit, my dear son. Let us raise our glasses—to you, to your achievements, and to your worthy return home!";
			link.l1.go = "SharlieEpilog_Single_15";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_Single_15":
			dialog.text = "";
			link.l1 = "To true friends, without whom you can't survive in the New World!";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
			{
				link.l1.go = "SharlieEpilog_Single_16";
			}
			else if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_Single_17";
			}
			else
			{
				link.l1.go = "SharlieEpilog_Single_18";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_Single_16":
			dialog.text = "";
			link.l1 = "To Captain Charles and his big heart!";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_Single_17";
			}
			else
			{
				link.l1.go = "SharlieEpilog_Single_18";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Tichingitu();
		break;
		
		case "SharlieEpilog_Single_17":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel"))
			{
				link.l1 = "To the captain's iron will!";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway"))
			{
				link.l1 = "To the wisdom of our captain!";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1 = "To loyalty and the cause!";
			}
			link.l1.go = "SharlieEpilog_Single_18";
			SharlieEpilog_InKitchenDeMonpe_camera_Gambitnik();
		break;
		
		case "SharlieEpilog_Single_18":
			dialog.text = "";
			link.l1 = "To always come out unscathed!";
			link.l1.go = "SharlieEpilog_toast";
			SharlieEpilog_InKitchenDeMonpe_camera_Alonso();
		break;
		// <-- Выбрал остаться в поместье будучи холостяком
		
		// Шарль губернатор разговаривает с зелёным капитаном
		case "SharlieEpilog_GreenCaptain":
			dialog.text = "";
			link.l1 = "I heard you've been quite insistent about getting an audience. So, what brings you to the Governor of Martinique?";
			link.l1.go = "SharlieEpilog_GreenCaptain_1";
			locCameraFromToPos(-1.80, 3.84, -9.08, true, -2.38, 2.21, -7.33);
			PlaySound("Voice\" + LanguageGetLanguage() + "\officer_common_2.wav");
		break;
		
		case "SharlieEpilog_GreenCaptain_1":
			dialog.text = "I want to talk about serving the interests of the French Crown.";
			link.l1 = "Yes, I have a task for you that will require all your resourcefulness, as well as skill in naval combat. Are you ready to prove yourself?";
			link.l1.go = "SharlieEpilog_GreenCaptain_2";
		break;

		case "SharlieEpilog_GreenCaptain_2":
			dialog.text = "Your Excellency, could you elaborate on the nature of the upcoming assignment?";
			link.l1 = "Of course. You need to find the Spanish courier ship called 'Santa Esperanza', board her, and bring me any documents you find in the captain's cabin. The ship I mentioned will be passing near Trinidad in about twelve days.";
			link.l1.go = "SharlieEpilog_GreenCaptain_3";
		break;

		case "SharlieEpilog_GreenCaptain_3":
			dialog.text = "Alright, I'll take on this task. What kind of documents should I be looking for?";
			link.l1 = "The mail correspondence. Among other things, there will be some documents that are very important to me. But you don't need to go through the papers, just bring me the whole package as it is. For this service, I'll pay you fifteen thousand pesos... So, I'll be waiting for you at my residence with the results.";
			link.l1.go = "SharlieEpilog_GreenCaptain_4";
		break;

		case "SharlieEpilog_GreenCaptain_4":
			dialog.text = "I suppose I won't keep you waiting long, Your Excellency.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_GuberOnMartinique_5");
		break;
		
		//Шарль разговаривает с комендантом форта
		case "SharlieEpilog_KomendantFort":
			dialog.text = "Your Excellency... May I report?";
			link.l1 = "Report, "+GetAddress_Form(NPChar)+" "+npchar.lastname+".";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) link.l1.go = "SharlieEpilog_KomendantFort_1";
			else link.l1.go = "SharlieEpilog_KomendantFort_2";
			PlaySound("Voice\" + LanguageGetLanguage() + "\military02.wav");
		break;
		
		case "SharlieEpilog_KomendantFort_1":
			dialog.text = "Ahem...";
			link.l1 = "Speak freely. I have no secrets from my wife.";
			link.l1.go = "SharlieEpilog_KomendantFort_2";
		break;
		
		case "SharlieEpilog_KomendantFort_2":
			dialog.text = "Intelligence reports: a squadron has set sail from Willemstad. Leading the fleet is the second-rate ship of the line ‘Gouden Leeuw’, a true monster of the sea. The squadron boasts over two and a half hundred guns and more than fifteen hundred soldiers. Their target is Saint-Pierre.";
			link.l1 = "Hmm... So we have almost no time to prepare.";
			link.l1.go = "SharlieEpilog_KomendantFort_3";
		break;

		case "SharlieEpilog_KomendantFort_3":
			dialog.text = "What are your orders, Governor?";
			link.l1 = "We have several ships anchored in the roadstead, ready to strike at the enemy's rear...";
			link.l1.go = "SharlieEpilog_KomendantFort_4";
		break;

		case "SharlieEpilog_KomendantFort_4":
			dialog.text = "Are you planning to strike them from both sides?";
			link.l1 = "Exactly. The fort will draw their fire. And when night falls, the squadron under my command will strike from the sea. We’ll scatter their attention, and then fireships loaded with pitch and planks will be sent from the port. There won’t be a splinter left of their fleet.";
			link.l1.go = "SharlieEpilog_KomendantFort_5";
		break;

		case "SharlieEpilog_KomendantFort_5":
			dialog.text = "An excellent plan, Your Grace! Shall I give the order to begin preparations?";
			link.l1 = "Begin. And may the Lord be with us.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_GuberOnMartinique_11");
		break;
		
		// Стражник вызывает Алонсо
		case "SharlieEpilog_Guard":
			dialog.text = "";
			link.l1 = "Guards, call Alonso.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_AlonsoArrive");
		break;
		
		//Шарль разговаривает с Алонсо после коменданта
		case "SharlieEpilog_Alonso35":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")))
			{
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = CharacterFromID("Helena");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld = CharacterFromID("Mary");
				dialog.text = "Governor, sir...";
				link.l1 = ""+npchar.name+", the Dutch squadron will arrive any day now and begin the siege. Listen to my orders: take Philippe and "+sld.name+", and take them to the abbot at once. Let him gather all the women, children, and elders and see to their safety.";
				link.l1.go = "SharlieEpilog_Alonso36_Wife";
				break;
			}
			dialog.text = "Governor, sir...";
			link.l1 = ""+npchar.name+", the Dutch squadron will arrive any day now and lay siege to the city. Tell the abbot to gather all the women, children, and elders and see to their safety. As for you, I plan to put you in charge of the fireship. Details will follow. First and foremost, we must protect the civilians.";
			link.l1.go = "SharlieEpilog_Alonso37";
		break;

		case "SharlieEpilog_Alonso36_Wife":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = CharacterFromID("Helena");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld = CharacterFromID("Mary");
			dialog.text = "I don't think so "+sld.name+" will agree to join the other women. She is dying of boredom.";
			link.l1 = "Hmm... Then tell her to get ready for battle. You won't be sitting idle either — you'll be in command of the fireship. Details later. For now — look after my son.";
			link.l1.go = "SharlieEpilog_Alonso37";
		break;
		
		case "SharlieEpilog_Alonso37":
			dialog.text = "It would be an honor! Shall I proceed?";
			link.l1 = "I allow it. Go ahead. Every second counts for us.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_GuberOnMartinique_13");
		break;
		// --> Выбрал отправиться назад на Карибы с женой
		case "SharlieEpilog_ChooseCaribbean_HaveWife_1":
			dialog.text = "";
			link.l1 = "Well... I admit, I expected you to say that – though I was hoping for a different answer. But I respect your choice and won't try to persuade you otherwise.";
			link.l1.go = "SharlieEpilog_ChooseCaribbean_HaveWife_2";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
			pchar.questTemp.SharlieEpilog_ChooseCaribbean = true;
		break;
		
		case "SharlieEpilog_ChooseCaribbean_HaveWife_2":
			dialog.text = "";
			link.l1 = "I know I've let you down. But I have news that, I hope, will overshadow everything that's been said before.";
			link.l1.go = "SharlieEpilog_ChooseCaribbean_HaveWife_3";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_ChooseCaribbean_HaveWife_3":
			dialog.text = "";
			link.l1 = "I'm all ears.";
			link.l1.go = "SharlieEpilog_ChooseCaribbean_HaveWife_4";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_ChooseCaribbean_HaveWife_4":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = CharacterFromID("Helena");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld = CharacterFromID("Mary");
			dialog.text = "";
			link.l1 = "I'm planning to stay here for at least a year. "+sld.name+" in her condition, the rocking is out of the question.";
			link.l1.go = "SharlieEpilog_ChooseCaribbean_HaveWife_5";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_ChooseCaribbean_HaveWife_5":
			dialog.text = "";
			link.l1 = ""+pchar.name+", could it be...";
			link.l1.go = "SharlieEpilog_HaveWife_12";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		// <-- Выбрал отправиться назад на Карибы с женой
		
		// --> Выбрал отправиться назад на Карибы один
		case "SharlieEpilog_ChooseCaribbean_Single_1":
			dialog.text = "";
			link.l1 = "Well... I must admit, I expected you to say that – though I was hoping for a different answer. Still, I respect your choice and won't try to persuade you otherwise. But tell me, "+pchar.name+", have you given any thought to my proposal to marry Yvonne?";
			link.l1.go = "SharlieEpilog_Single_13";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
			pchar.questTemp.SharlieEpilog_ChooseCaribbean = true;
		break;
		// <-- Выбрал отправиться назад на Карибы один
		
		//Диалог Шарль и Мишеля на Рифе Скелета
		case "SharlieEpilog_Mishelle_1":
			dialog.text = "Couldn't help yourself, huh?";
			link.l1 = "You?! Is this a dream?";
			link.l1.go = "SharlieEpilog_Mishelle_2";
			SharlieEpilog_OnReefs_6();
			PlaySound("Voice\" + LanguageGetLanguage() + "\sharlie\mishelle-04.wav");
		break;

		case "SharlieEpilog_Mishelle_2":
			dialog.text = "The thirst for easy gain, power, the illusion of invincibility... Which of these destroyed you, brother? What clouded your mind, as it clouds the minds of all pale-faces?";
			link.l1 = "Get out! You're just a ghost! You don't belong here!";
			link.l1.go = "SharlieEpilog_Mishelle_3";
		break;

		case "SharlieEpilog_Mishelle_3":
			dialog.text = "So you still don't get it? Spectra sunt memoria peccatorum. You are the ghost... A Caribbean legend of a man consumed by greed and blind vanity. How many have you killed for gold, "+pchar.name+"?";
			link.l1 = "Well, dear brother, I don't mind killing you a second time! You brought this on yourself!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_OnReefs_9");
		break;
		
		
		
		
		
	}
}
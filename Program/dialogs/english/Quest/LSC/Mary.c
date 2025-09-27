// Мэри Каспер - взаимная любовь и офицер
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	int iTime, iAddTime;
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
		case "First time":
			dialog.text = "What do you need?";
			link.l1 = "No, it's nothing.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
	// ---------------------------------покушение на Акулу - вариант R --------------------------------
		// разговор в каюте Адольфа
		case "Cabin":
			dialog.text = "Marcello, I know him. He is a friend of the Rivados and the pirates. Adolf would never work with him. Hey... do you smell gun powder? And there's blood on the wall... He killed Adolf and now he's trying to trick us! He must be working for the Admiral! Kill him!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LSC_Cabin_fight");
		break;
		
		// на улице
		case "Town":
			dialog.text = "Oh, excuse me... can you help me?";
			link.l1 = "Hm. I am always ready to help a gorgeous lady. What's the problem?";
			link.l1.go = "Town_1";
		break;
		
		case "Town_1":
			dialog.text = "See, I bought a chest filled with bits of metal from Sessile Gallard. She lives on the Eva. Jurgen promised to forge me something good, all right... I bought it, aye, but I can't bring it to him. Damn me!\nCould you carry the chest from the Eva to the Narwhals' block on the Esmeralda? Please, I'd be very grateful!";
			link.l1 = "And that's it? Sure, miss, I will help you. No trouble.";
			link.l1.go = "Town_2";
		break;
		
		case "Town_2":
			dialog.text = "Thank you! I'll show you to the chest.";
			link.l1 = "Milady...";
			link.l1.go = "Town_3";
		break;
		
		case "Town_3":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "reload", "reload41", "LSC_EnterAevaWithMary", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
		break;
		
		case "Town_4":
			dialog.text = "And here we are... Now tell me, bastard, where is the key?!";
			link.l1 = "Shiver me timbers! Ha, it seems that no help is needed... Mary.";
			link.l1.go = "Town_5";
		break;
		
		case "Town_5":
			dialog.text = "Smartass, huh? Less talk, damn you! Where's the key? Give it to me or you'll regret it!";
			link.l1 = "So rude! Such a sharp tongue for such a beautiful girl. What key?";
			link.l1.go = "Town_6";
		break;
		
		case "Town_6":
			dialog.text = "The key you took from Adolf Barbier. Don't try to deny it, you were seen leaving his cabin. Adolf is dead and you killed him... Now, give me the key!";
			link.l1 = "So it was you after all... You've made a mistake, girl, a big mistake!";
			link.l1.go = "Town_7";
		break;
		
		case "Town_7":
			PlaySound("Voice\English\LSC\Mary Casper-04.wav");
			dialog.text = "What did you say...? Damn it, you're no ordinary robber! He's working for the Admiral! Put him down, lads!";
			link.l1 = "...";
			link.l1.go = "Cabin_fight";
		break;
		
	// ---------------------------------покушение на Акулу - вариант N --------------------------------
		case "caroline":
			dialog.text = "Chad, that's him! Damn it, he brought help! Lads, kill them all!";
			link.l1 = "...";
			link.l1.go = "caroline_1";
		break;
		
		case "caroline_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			// Акулу к бою
			sld = characterFromId("Dodson");
			LAi_SetImmortal(sld, false);
			LAi_SetWarriorType(sld);
			sld.cirassId = Items_FindItemIdx("cirass1");
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			// устанавливаем 4 толстых нарвалов
			int iRank = 20+MOD_SKILL_ENEMY_RATE*2;
			int iScl = 65;
			for (i=1; i<=4; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("MaryGuard_"+i, "citiz_5"+(i+4), "man", "man", iRank, PIRATE, -1, true, "soldier"));
				if(i == 4) 
				{
					FantomMakeCoolFighter(sld, iRank, iScl, iScl, "topor_07", "pistol11", "bullet", iScl*2);
					sld.DontClearDead = true;
					sld.SaveItemsForDead = true;
				}
				else FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_19", "pistol5", "bullet", iScl*2);
				if (i < 3) ChangeCharacterAddressGroup(sld, "CarolineBank", "reload", "reload3");
				else ChangeCharacterAddressGroup(sld, "CarolineBank", "reload", "reload2");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			// Мэри и Чада к бою
			sld = characterFromId("Capper");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LSC_MarynChadDie");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
	// ---------------------------------покушение на Акулу - вариант M --------------------------------
		case "mary":
			dialog.text = "You're just in time... I could never have dealt with them myself... Fuh! To be honest, I thought I was finished!";
			link.l1 = "You fought like a Valkyrie! I have never seen such a beautiful girl fight so vigorously...";
			link.l1.go = "mary_1";
		break;
		
		case "mary_1":
			dialog.text = "Ha-ha, aren't you a gentleman, making compliments with your sword still in your hand. Thanks for your help. You saved my life, all right! Introduce yourself, gentleman, I've never seen you before. Are you new here?";
			link.l1 = "My name is "+GetFullName(pchar)+", but beautiful girls can call me "+pchar.name+". . Am I new here? Hm... I suppose I am.";
			link.l1.go = "mary_2";
		break;
		
		case "mary_2":
			dialog.text = "I can tell. I would have noticed such a handsome man around. My name is Mary, Mary Casper. They call me Red Mary, because I am a redhead, all right.";
			link.l1 = "I am glad to meet you, Mary...";
			link.l1.go = "mary_3";
		break;
		
		case "mary_3":
			dialog.text = "Oh, I am glad twice over... considering I'd be dead if not for you! That bastard Chad wasn't bluffing. Such a rat! And I was a fool to leave the lower doors open. That is how you got inside, isn't it?";
			link.l1 = "Yes. I was swimming around the island trying to find a place to climb ashore.";
			link.l1.go = "mary_4";
		break;
		
		case "mary_4":
			dialog.text = "I see. That unlocked door almost got me killed. Jurgen himself forged the locks for me, you can't open them without the right key and lockpicking won't work. Besides, I wouldn't stay still while someone was trying to get inside - four barrels of my pistol will leave four holes on a door or a body, ha-ha!\nBut damned Chad won't leave me alone. If he sent cutthroats to 'persuade' me to take his side, he's definitely serious about it. If it wasn't for you, I would've had to say yes. I'll have to stay here under siege, "+pchar.name+", all right! Thank God I prepared for that; I have plenty of supplies and Jurgen is my neighbour, I've no quarrel with him.";
			link.l1 = "Mary, why don't you explain your problems fully? I see that you need my help, but I didn't understand a thing that came from your lips.";
			link.l1.go = "mary_5";
		break;
		
		case "mary_5":
			dialog.text = "Aye, I need help, all right! I'm alone now. I had a quarrel with Donald, then Chad turned out to be a villain... Oh, I'm sorry, I am babbling again. Fine, I'll tell you about the situation I've found myself in...";
			link.l1 = "Bear in mind that I am new here, so I don't understand much yet. Who is this Chad trying to 'persuade' or kill you? And who is Donald?";
			link.l1.go = "mary_6";
		break;
		
		case "mary_6":
			dialog.text = "Chad is a pirate from Admiral Shark Dodson's crew, a gaoler on Tartarus...";
			link.l1 = "Wait! Did you say Shark Dodson? Is he here?!";
			link.l1.go = "mary_7";
		break;
		
		case "mary_7":
			dialog.text = "You must've arrived tonight since you don't already know that. Where else would Shark be? My troubles began when he arrived here several months ago. Though, I admit, this is all the Narwhals' and Rivados' fault. When Shark came here with his crew, he wanted to establish a base, but our people and the Rivados didn't like the idea. We attacked Shark's brig at night and set it on fire.\nBad idea! Shark's crew are devils, not men, all right. First, they destroyed our boats, then landed and started slaughtering us. The Narwhals retreated and the Rivados ran away as fast as they could. Finally, the pirates captured the San Augustine where the most of the island's provisions are held, then they took the Tartarus.\nShark imprisoned our leader, Alan Milrow, who also was my... my dear friend, and the Rivados' wizard Chimiset. He sent them to rot in Tartarus's cages like beasts. It's easy to swim to Tartarus from here and I managed to visit Alan a few times. There, I met Chad Kapper. Shark assigned him as a gaoler. I asked Chad to release Alan, promised him money, but he was afraid to disobey the Admiral.\nAnd then Alan was murdered in prison.\nChad told me that Shark did this, all right. So I went to Donald, who was elected leader in Alan's place, and demanded he attack the pirates immediately, but he refused, said that those sea devils were too tough for us. I told him to fuck himself.\nMy people were useless, so I made a deal with Kapper, the scum that wanted to take Shark's place. We had a plan - lure the Admiral from his fortress to some shady place and kill him. We also found a sniper with a good rifle. He could shoot the Admiral from the Fury's mast.\nNow, the interesting part is, the day before yesterday I visited Tartarus at night to tell Chad something important about our plan. I swam to the ship and overheard Chad talking with two Narwhals. Turns out that Shark didn't kill Alan. Chad did. He spread a rumour that the Admiral was responsible.\nChad murdered Alan because of me - firstly to take me for a plaything in his bed, secondly to use me to get rid of Shark. Chad knew I wouldn't stop 'til I had revenge. Can you imagine? What scum!";
			link.l1 = "Yeah, I've met the likes of him...";
			link.l1.go = "mary_8";
		break;
		
		case "mary_8":
			dialog.text = "Fucker is worse! He... I don't have the words to describe that monster! After I swam away, I found him next morning and told him exactly what I thought of him. Aye, I told him I'd have nothing to do with his plot against the Admiral.";
			link.l1 = "And he didn't like that, obviously... That was rash, Mary. You should've been more cautious.";
			link.l1.go = "mary_9";
		break;
		
		case "mary_9":
			dialog.text = "I know, but I couldn't keep my mouth shut. The bastard killed Alan and tried to use me for his own ends! Scum! And sure, he got angry and promised that I'd regret it. I said I'd cut off his balls and feed them to the crabs!\nHe threatened to send his mates after me if I didn't change my mind. I laughed. I didn't think a Narwhal would dare raise a hand against me.";
			link.l1 = "Seems you were mistaken.";
			link.l1.go = "mary_10";
		break;
		
		case "mary_10":
			dialog.text = "Aye, "+pchar.name+", I underestimated Chad and overestimated myself. He found cutthroats who'd stoop to attacking a lone girl in her own cabin. What do I do now? I can't trust anyone, not even trust my own people; these two we've killed are Narwhals. I knew both of them, all  right. As long as Chad is alive, I'm in danger. He'll send more men, no doubt.\nI'm scared to walk out the door; the sniper we found to assassinate Shark may shoot me from Rivados territory and slip away. I won't go to Donald - he won't listen.\nAnd the Admiral? 'Please, sir, I know I helped plan your assassination, but could you see your way through to forgiving me and saving me from my former mates?'\nHe'd send me to rot in the cells of Tartarus, if he didn't put a bullet in my brain. Fuck, I'm trapped! I'm going to sit here with my guns loaded until the food runs out and then... I don't know!";
			link.l1 = "Well, in that case I have no choice but to help you, eh? Your situation falls in line with my plans here anyways...";
			link.l1.go = "mary_11";
		break;
		
		case "mary_11":
			dialog.text = "You want to help me? But how? Are you going to kill Chad?";
			link.l1 = "That's part of the plan, sure.";
			link.l1.go = "mary_12";
		break;
		
		case "mary_12":
			dialog.text = "Listen, "+pchar.name+", I appreciate the thought, but you're out of your depth. Chad is one of the Admiral's closest friends and even if you get to him, you'll never make it out alive. Shark's pirates will kill you. They don't know the truth, all right.";
			link.l1 = "Calm down. I have to talk to Shark anyway.";
			link.l1.go = "mary_13";
		break;
		
		case "mary_13":
			dialog.text = "So, you're a pirate too?! You'd best start talking. You broke into my place all handsome-looking, saved my life, promised to help, yet I don't know a thing about you!";
			link.l1 = "Fine... I'm not a pirate, but currently I work with a certain pirate baron: Jan Svenson. I came here to find Nathaniel Hawk. Have you heard of him?";
			link.l1.go = "mary_14";
		break;
		
		case "mary_14":
			dialog.text = "No, who's he?";
			link.l1 = "Another famous pirate. It's a pity you haven't met him, he must be here somewhere. I was looking for Shark as well, but I didn't expect to find him here.";
			link.l1.go = "mary_15";
		break;
		
		case "mary_15":
			dialog.text = "But how did you get here? You look too well for a survivor of a shipwreck.";
			link.l1 = "And why would you assume I was shipwrecked?";
			link.l1.go = "mary_16";
		break;
		
		case "mary_16":
			dialog.text = "That's the only way to get here. Shark's the only one to've sailed here.";
			link.l1 = "Well, Shark's not the 'only' one, as you can see.";
			link.l1.go = "mary_17";
		break;
		
		case "mary_17":
			dialog.text = "So, you've got a ship? Great!";
			link.l1 = "Don't get too excited, Mary. I got here through a... on a barque. I got here on a barque but it sank to the bottom.";
			link.l1.go = "mary_18";
		break;
		
		case "mary_18":
			dialog.text = "A-ah... Well, as I said: a shipwreck. You're trapped here with us now, all right.";
			link.l1 = "Mary, let me tell you my plan. You mentioned Chad was planning to kill Shark. I need Shark alive. Me and Jan are going to make him head of the pirates. That's why I have to warn him, because from your story, I am sure that Chad will attempt it with or without your help.";
			link.l1.go = "mary_19";
		break;
		
		case "mary_19":
			dialog.text = "Aye, probably. He has the men to make it happen...";
			link.l1 = "It means that my primary goal is to win over Shark's trust and save him. Then, I will get to Chad - officially. Have you got any evidence to prove his guilt?";
			link.l1.go = "mary_20";
		break;
		
		case "mary_20":
			dialog.text = "I have his letter which was brought here by one of these... idiots on the floor. There are threats and details in it which the Admiral might find interesting. Wait! What about me? Shark will find out I was working with Chad!";
			link.l1 = "Mary, are you going to sit here with your pistols forever hiding your sweet face from everyone? Do you really think I want a beautiful girl's death on my conscience? Show me the letter first, let's see what I can do...";
			link.l1.go = "mary_21";
		break;
		
		case "mary_21":
			GiveItem2Character(pchar, "letter_chad_1");
			RemoveItems(npchar, "letter_chad_1", 1);
			dialog.text = "Here. What do you think?";
			link.l1 = "Hold on... (reading). Yes, it appears Chad is one of that special breed of bastards to infest this Earth. This letter will be enough to make Shark eager to put a noose around Chad's neck himself. Don't you worry, milady, I'll make sure Shark never suspects you. He will be too busy with Chad, anyways.";
			link.l1.go = "mary_22";
		break;
		
		case "mary_22":
			dialog.text = "You'd really do this? Promise me, all right! Swear to me that you won't betray me!";
			link.l1 = "Mary, I swear to you, I won't betray you. I did not save you just to get you killed.\nChad won't leave you in peace, that's for sure. You know too much. Stay here until he is dead.";
			link.l1.go = "mary_23";
		break;
		
		case "mary_23":
			dialog.text = "Aye, I'll stay here. I'd rather not be shot by a sniper or knifed in the back.";
			link.l1 = "Good girl. Close all the doors, including the lower ones. Have you got the only key?";
			link.l1.go = "mary_24";
		break;
		
		case "mary_24":
			dialog.text = "No. There's another. Do you want it?";
			link.l1 = "Yes. Do you trust me?";
			link.l1.go = "mary_25";
		break;
		
		case "mary_25":
			dialog.text = "Well, if the handsome gentleman who just saved my life betrays me, there's not much reason to live at all... Take it.";
			link.l1 = "Don't be scared, beauty! I won't let you down. I'll see you as soon as I resolve this mess. Hopefully it won't take long.";
			link.l1.go = "mary_26";
		break;
		
		case "mary_26":
			GiveItem2Character(pchar, "key_mary");
			dialog.text = "It's all right, I can hold this place for a few weeks.";
			link.l1 = "Great. I won't waste time then. I'll take the corpses out and then talk to Shark. He's on the San Augustine, right?";
			link.l1.go = "mary_27";
		break;
		
		case "mary_27":
			dialog.text = "Yes, he's always there. And get out the same way you got in here - I won't let you set foot on the upper deck of the Ceres.";
			link.l1 = "And why is that?";
			link.l1.go = "mary_28";
		break;
		
		case "mary_28":
			dialog.text = "Because you won't be able to help me if you die. This is Narwhal territory and they'll kill you as an outsider.";
			link.l1 = "Hm... Got it. Well, Mary, see you. I will be back as soon as it is safe.";
			link.l1.go = "mary_29";
		break;
		
		case "mary_29":
			dialog.text = "You can see me anytime you like, I've no problem with that. (giggles)";
			link.l1 = "Goodbye, fair one!";
			link.l1.go = "mary_30";
		break;
		
		case "mary_30":
			DialogExit();
			LAi_SetOwnerType(npchar);
			NextDiag.CurrentNode = "mary_wait";
			npchar.greeting = "mary_3";
			AddQuestRecord("SharkHunt", "31");
			AddQuestRecordInfo("Chad_Mary_letter", "2");
			LocatorReloadEnterDisable("CeresSmithy", "reload6", false);
			LocatorReloadEnterDisable("CeresSmithy", "reload7", false); // открываем выходы
		break;
		
		case "mary_wait":
			dialog.text = "Hello, "+pchar.name+", any good news for me? Are you all right?";
			if (pchar.questTemp.Saga.SharkHunt == "mary_whiskey")
			{
				link.l1 = "Your conflict with Shark Dodson is resolved. He has no interest in hunting you down. Chad's treason is the only thing he cares about now.";
				link.l1.go = "letters";
			}
			else
			{
				link.l1 = "Not yet, Mary. But I will do everything I can.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "mary_wait";
		break;
		
		case "letters":
			dialog.text = "Oh, thank God! Thank you, I won't forget it, all right! At least I don't have to worry about the Admiral. And what about Chad? What did Shark do?";
			link.l1 = "We convinced the Rivados to go after him. Layton Dexter removed the guards from the Tartarus and gave the gaol key to Black Eddie. The blacks freed their wizard Chimiset, but they failed to kill Chad; they got two of his Narwhal friends, but Chad ran away and is hiding somewhere.";
			link.l1.go = "letters_1";
		break;
		
		case "letters_1":
			dialog.text = "Damn! That means I have to be even more careful now!";
			link.l1 = "Calm down, Mary. I'm sure he's more concerned about Shark than you. He probably knows who pitted the Rivados against him. He will do anything to kill Shark, not you.";
			link.l1.go = "letters_2";
		break;
		
		case "letters_2":
			dialog.text = "Don't count on it. Chad is not one to let things go so easily. Ah, I'm so tired of living in fear of him...";
			link.l1 = "Hm. I didn't take you for the kind of lady who gets spooked easily.";
			link.l1.go = "letters_3";
		break;
		
		case "letters_3":
			dialog.text = "Ha! I'm not scared of a proper fight, but to sit on my ass waiting to be killed? I am very scared "+pchar.name+", all right!...";
			link.l1 = "Trust me Mary: Kapper has his plate full with the Admiral. For now... I need your advice.";
			link.l1.go = "letters_4";
		break;
		
		case "letters_4":
			dialog.text = "My advice? What kind of advice?";
			link.l1 = "Eddie found two letters writen by Chad. Read them, perhaps you'll know what he is up to. You were in on the plan with Chad after all...";
			link.l1.go = "letters_5";
		break;
		
		case "letters_5":
			RemoveItems(pchar, "letter_chad", 1);
			RemoveItems(pchar, "letter_chad_1", 1);
			dialog.text = "Give them here... (reading). Axel is our merchant on the Esmeralda, all right. Chad wanted to buy whiskey from him? Strange. Chad only drinks rum, says whiskey is 'the moonshine of peasants'...";
			link.l1 = "And what about the second letter?";
			link.l1.go = "letters_6";
		break;
		
		case "letters_6":
			dialog.text = "'Marcello'? Marcello Cyclops, a former royal hunter. He's the reason I refuse to leave this cabin.";
			link.l1 = "Is he the sniper you hired?";
			link.l1.go = "letters_7";
		break;
		
		case "letters_7":
			dialog.text = "Yes. Despite missing an eye, Marcello can shoot a fly at forty feet, all right. His mission was to hit Shark using a long range stutzen from the bowsprit of Santa Florentina, or Fury's platform...";
			link.l1 = "So he's still part of Chad's plan to kill Shark. But... Eva? Cecille? Drinks?";
			link.l1.go = "letters_8";
		break;
		
		case "letters_8":
			dialog.text = "The Eva is a neutral ship and Cecille is Cecille Halard, a funny old woman who lives aboard. She moved there not long ago from the Santa Florentina. Orelie Bertine is a friend of hers. They've been on the island since before I was born, all right.";
			link.l1 = "Hm. Nonsense. Two large lads are hiding from an old woman to drink a barrel of whiskey together? Rubbish... Strange time and place for Chad to drink.";
			link.l1.go = "letters_9";
		break;
		
		case "letters_9":
			dialog.text = "I told you he doesn't drink whiskey, only rum... something doesn't add up.";
			link.l1 = "Fine, let's start with Cyclops. Do you know where to find him?";
			link.l1.go = "letters_10";
		break;
		
		case "letters_10":
			dialog.text = "No. He's very private. He shoots birds every day at the outer ring and no one knows where he sleeps. He often visits the Rivados.";
			link.l1 = "Not a lot to go on... Well, I'll go talk to Axel, then. Perhaps he can make sense of this. See you, Mary! Lock the door!";
			link.l1.go = "letters_11";
		break;
		
		case "letters_11":
			dialog.text = ""+pchar.name+", please find Chad quickly. I haven't slept since the last attack.";
			link.l1 = "Hold fast, darling. I'll do the best I can.";
			link.l1.go = "letters_12";
		break;
		
		case "letters_12":
			DialogExit();
			NextDiag.CurrentNode = "mary_wait";
			pchar.questTemp.Saga.SharkHunt = "trader_whiskey"; // флаг на магазин - поиск виски
			AddQuestRecord("SharkHunt", "35");
		break;
		
		case "happy":
			dialog.text = ""+pchar.name+"! How did he get here? Did he come to--?";
			link.l1 = "Yes, to kill you, Mary. He came here through Jurgen's cabin and used a rope to climb down here.";
			link.l1.go = "happy_1";
		break;
		
		case "happy_1":
			dialog.text = "Ah! I'm such an idiot! I forgot about that way! Chad told him about it, all right, I'm sure!";
			link.l1 = "Most likely. I barely made it.";
			link.l1.go = "happy_2";
		break;
		
		case "happy_2":
			dialog.text = "And I was sleeping. He would have killed me in a second... But how did you know that he was on his way here?";
			link.l1 = "Oh... I have my ways, Mary.";
			link.l1.go = "happy_3";
		break;
		
		case "happy_3":
			dialog.text = "You saved me again, handsome. You always show up just in time, all right. How do you do that?";
			link.l1 = "Well, I don't know. One of my many talents. Your siege is over - Chad Kapper is dead and so are all his friends. Cyclops was the last of his rotten crew.";
			link.l1.go = "happy_4";
		break;
		
		case "happy_4":
			dialog.text = "Really, "+pchar.name+"? You're not pulling my leg?";
			link.l1 = "Not at all. Eh, I need some rest after these past few days...";
			link.l1.go = "happy_5";
		break;
		
		case "happy_5":
			dialog.text = "I can finally breathe freely now! Thank you... thank you so much! You're my hero, all right!";
			link.l1 = "I love the sound of that - being your hero, that is. Just glad you're safe at last.";
			link.l1.go = "happy_6";
		break;
		
		case "happy_6":
			dialog.text = "So?";
			link.l1 = "What is it, pretty one?";
			link.l1.go = "happy_7";
		break;
		
		case "happy_7":
			dialog.text = "Why are you just standing there? Come here, gentleman.";
			link.l1 = "And do what?";
			link.l1.go = "happy_8";
		break;
		
		case "happy_8":
			dialog.text = "Come here and hug me, kiss me. You want this, I can tell, all right.";
			link.l1 = "Mary...";
			link.l1.go = "happy_9";
		break;
		
		case "happy_9":
			DialogExit();
			LAi_Fade("LSC_MaryRomantic_1", "");
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			StartQuestMovie(true, false, true);
			PlayStereoOGG("music_romantic");
			pchar.questTemp.LSC.MaryBye = "true"; // атрибут обязательного прощания перед телепортацией
			LocatorReloadEnterDisable("LostShipsCity_town", "reload62", false);
			LocatorReloadEnterDisable("LostShipsCity_town", "reload63", false); // открываем Церес снаружи
		break;
		
		case "happy_10":
			dialog.text = "Don't leave me...";
			link.l1 = "I'm here, Mary, darling...";
			link.l1.go = "happy_11";
		break;
		
		case "happy_11":
			dialog.text = "Everything can wait. Your Admiral can wait, your pirates can wait - this night is only for the two of us, all right?";
			link.l1 = "Yes.";
			link.l1.go = "happy_12";
		break;
		
		case "happy_12":
			dialog.text = "And all the nights after...";
			link.l1 = "Yes, Mary.";
			link.l1.go = "happy_13";
		break;
		
		case "happy_13":
			DialogExit();
			LSC_MaryLoveWaitTime();
			SetLaunchFrameFormParam("Next morning...", "", 0, 4);
			LaunchFrameForm();
			DoQuestCheckDelay("LSC_MaryRomantic_5", 4.0);
		break;
		
	// ----------------------------------вместе с Мэри на Церес Смити------------------------------------------
		case "LSC_love":
			if (pchar.questTemp.LSC.Mary == "return") // эта нода важнее даже ругани с нарвалами
			{
				dialog.text = ""+pchar.name+"! You're back... without her. So, she couldn't take you from me.";
				link.l1 = "Mary, your suspicions were unfounded. You are the only one for me. I was always with you in my thoughts and in my dreams.";
				link.l1.go = "adversary_hire_return";
				break;
			}
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = ""+pchar.name+", why are you fighting Narwhals? I live on their territory - am one of them, in case you've forgotten. Please, go to Fazio and make peace, I'm begging you.";
				link.l1 = "Alright, Mary, I will do as you ask.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.FindDolly")) // нашёл статую - прощается
			{
				dialog.text = ""+pchar.name+", something is troubling you. What's wrong?";
				link.l1 = "Mary, I need to talk to you.";
				link.l1.go = "dolly";
				break;
			}
			if (CheckAttribute(npchar, "quest.donald"))
			{
				dialog.text = ""+pchar.name+"! All the Narwhals are talking about you!";
				link.l1 = "Really, my darling?";
				link.l1.go = "donald";
				break;
			}
			if (CheckAttribute(npchar, "quest.talisman")) // подарок
			{
				dialog.text = ""+pchar.name+"! This broadsword is incredible! Thank you! I want to give you a present too. Of course, it doesn't compare to yours but I want you to take it, all right.";
				link.l1 = "Mary, I'd treasure any gift from you... thank you, my love.";
				link.l1.go = "talisman";
				break;
			}
			if (stf(environment.time) >= 5.0 && stf(environment.time) < 10.0) // утро
			{
				dialog.text = "Got a busy day ahead, "+pchar.name+"? Good luck!";
				if (CheckAttribute(npchar, "quest.narval_blade"))
				{
					link.l3 = "Mary, we need to go and see Jurgen today.";
					link.l3.go = "narval";
				}
				link.l1 = "Thanks, Mary! I've no doubt about that.";
				link.l1.go = "exit";
				link.l2 = "Not today, Mary. I want to get some rest here. Are you all right with that?";
				link.l2.go = "rest_morning"; // отдых
			}
			else
			{
				dialog.text = "Well, "+pchar.name+", how are you doing? Running around the island as usual?";
				link.l1 = "Yes, Mary. There are a lot of things to be done...";
				link.l1.go = "LSC_love_1";
			}
			NextDiag.TempNode = "LSC_love";
		break;
		
		case "LSC_love_1":
			if (stf(environment.time) >= 18.0 && stf(environment.time) < 22.0) //вечер
			{
				dialog.text = ""+pchar.name+", it's evening already, what things are you talking about? Stay here, let's have some drinks and relax, all right? Everything else can wait until morning!";
				link.l1 = "(laughing) Of course, love, say less...";
				link.l1.go = "LSC_love_evening";
				if (sti(pchar.money) >= 500)
				{
					link.l2 = "Mary, let's go to the tavern today!";
					link.l2.go = "LSC_tavern";
				}
				link.l3 = "Mary, darling, I am very busy now. I'll be back a bit later.";
				link.l3.go = "LSC_love_2";
				break;
			}
			if (stf(environment.time) >= 10.0 && stf(environment.time) < 18.0) //день
			{
				dialog.text = "Don't forget to visit me in the evening. And don't you dare avoid me, all right?";
				if (CheckAttribute(npchar, "quest.narval_blade"))
				{
					link.l3 = "Mary, we have to go and see Jurgen today.";
					link.l3.go = "narval";
				}
				link.l1 = "Sure, Mary, how could I? Of course I'll visit you.";
				link.l1.go = "exit";
				link.l2 = "Mary, I want to rest here tonight. Are you fine with that?";
				link.l2.go = "rest_afternoon"; // отдых
				NextDiag.TempNode = "LSC_love";
				break;
			}
			dialog.text = "What are you talking about? It is already nighttime! You aren't going anywhere, you'll stay here, with me, all right?";
			link.l1 = "(laughing) Your wish is my command, honey...";
			link.l1.go = "LSC_love_night";
			NextDiag.TempNode = "LSC_love";
		break;
		
		case "LSC_love_2":
			dialog.text = "Don't even...";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "LSC_love";
		break;
		
		// сходить в таверну
		case "LSC_tavern":
			dialog.text = LinkRandPhrase("A great idea, "+pchar.name+", all right! I agree!","Aye, let's go, "+pchar.name+"! Sancho has a fine collection of wines, there is much to choose from!","Oh, I would be glad, alright! It's always fun in Sancho's tavern and he has a great selection of wines!");
			link.l1 = "Let's go!";
			link.l1.go = "LSC_love_tavern";
		break;
		
		// --> отдых
		case "rest_morning":
			dialog.text = "Of course, "+pchar.name+", how long will you stay?";
			link.l1 = "I will stay until midday...";
			link.l1.go = "rest_day";
			link.l2 = "I will stay until evening...";
			link.l2.go = "rest_evening";
		break;
		
		case "rest_afternoon":
			dialog.text = "Of course, "+pchar.name+", how long will you stay?";
			link.l1 = "I will stay until evening...";
			link.l1.go = "rest_evening";
		break;
		
		case "rest_day":
			DialogExit();
			iTime = sti(environment.time);
			iAddTime = 13 - iTime;
			WaitDate("",0,0,0,iAddtime,5);
			RecalculateJumpTable();
			LAi_Fade("", "");
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye")) NextDiag.CurrentNode = "LSC_love";
			else NextDiag.CurrentNode = "LSC_love_3";
		break;
		
		case "rest_evening":
			DialogExit();
			iTime = sti(environment.time);
			iAddTime = 18 - iTime;
			WaitDate("",0,0,0,iAddtime,5);
			RecalculateJumpTable();
			LAi_Fade("", "");
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye")) NextDiag.CurrentNode = "LSC_love";
			else NextDiag.CurrentNode = "LSC_love_3";
		break;
		// <-- отдых
		
	//--> если скоро уходит через портал
		case "LSC_love_3": 
			if (pchar.questTemp.LSC.Mary == "return") // эта нода важнее даже ругани с нарвалами
			{
				dialog.text = ""+pchar.name+"! You're back... without her. So she couldn't take you away from me!";
				link.l1 = "Mary, your suspicions were unfounded. You're the only one to me. I was always with you in my thoughts and in my dreams.";
				link.l1.go = "adversary_hire_return";
				break;
			} // 291112
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = ""+pchar.name+", why are you fighting Narwhals? I live on their territory - am one of them, in case you've forgotten. Please, go to Fazio and make peace, I'm begging you.";
				link.l1 = "All right, Mary, I will do as you ask.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(npchar, "quest.talisman")) // подарок
			{
				dialog.text = ""+pchar.name+"! This broadsword is incredible! Thank you! I want to give you a present too. Of course, it doesn't compare to yours but I want you to take it, all right.";
				link.l1 = "Mary, I'd treasure any gift from you... thank you, my love.";
				link.l1.go = "talisman";
				break;
			}
			if (stf(environment.time) >= 5.0 && stf(environment.time) < 10.0) // утро
			{
				dialog.text = "Leaving already, "+pchar.name+"? Good luck and don't you forget about me...";
				if (CheckAttribute(npchar, "quest.narval_blade"))
				{
					link.l3 = "Mary, we should go and see Jurgen today.";
					link.l3.go = "narval";
				}
				link.l1 = "Thanks, Mary!";
				link.l1.go = "exit";
				link.l2 = "Mary, I want to get some rest here. Are you ok with that?";
				link.l2.go = "rest_morning"; // отдых
			}
			else
			{
				dialog.text = "Aren't you going to your Kukulcan, "+pchar.name+"?";
				link.l1 = "Not yet, still preparing.";
				link.l1.go = "LSC_love_4";
			}
			NextDiag.TempNode = "LSC_love_3";
		break;
		
		case "LSC_love_4":
			if (stf(environment.time) >= 18.0 && stf(environment.time) < 22.0) //вечер
			{
				dialog.text = "It's evening already, "+pchar.name+". Why don't you stay here? I want to be with you.";
				link.l1 = "All right, darling, I am staying...";
				link.l1.go = "LSC_love_evening";
				if (sti(pchar.money) >= 500)
				{
					link.l2 = "Mary, let's go to the tavern today!";
					link.l2.go = "LSC_tavern";
				}
				break;
			}
			if (stf(environment.time) >= 10.0 && stf(environment.time) < 18.0) //день
			{
				dialog.text = "Good luck and don't forget about me... Come and see me in the evening if you can, all right!";
				if (CheckAttribute(npchar, "quest.narval_blade"))
				{
					link.l3 = "Mary, we should see Jurgen today.";
					link.l3.go = "narval";
				}
				link.l1 = "Very well, darling.";
				link.l1.go = "exit";
				link.l2 = "Mary, I want to get some rest here. Are you ok with that?";
				link.l2.go = "rest_afternoon"; // отдых
				NextDiag.TempNode = "LSC_love_3";
				break;
			}
			dialog.text = "What are you talking about? It's night time! No, you aren't going anywhere, you'll stay here, all right!";
			link.l1 = "(laughing) Alright, I'll stay...";
			link.l1.go = "LSC_love_night";
			NextDiag.TempNode = "LSC_love_3";
		break;
		// <-- скоро уходит через портал
		
	// --> взаимоотношения - секс и прочее
		case "LSC_love_tavern":
			DialogExit();
			sld = ItemsFromID("potionrum");
			sld.shown = true;
			sld.startLocation = "FleuronTavern";
			sld.startLocator = "bottle";
			DoQuestReloadToLocation("FleuronTavern", "quest", "sit2", "LSC_MaryTavern");
		break;
		
		case "LSC_love_evening":
			DialogExit();
			//if(CheckAttribute(PChar, "IsMushketer")) SetMainCharacterToMushketer("", false);
			LSC_MaryEveneng();
		break;
		
		case "LSC_love_night":
			DialogExit();
			LSC_MaryLove();
		break;
		
		case "LSC_love_morning":
			if (CheckAttribute(npchar, "quest.hire"))
			{
				dialog.text = "Captain "+pchar.name+"! Officer Mary Casper is ready to serve under your command!";
				link.l1 = "Well done, officer! I order you to get aboard the ship immediately. But first... kiss your captain!";
				link.l1.go = "LSC_mary_hire";
			}
			else
			{
				dialog.text = "That was amazing, love... Good morning!";
				link.l1 = "Good morning, honey! You're wonderful!";
				link.l1.go = "LSC_love_morning_1";
			}
		break;
		
		case "LSC_love_morning_1":
			DialogExit();
			LAi_SetOwnerType(npchar);
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye")) NextDiag.CurrentNode = "LSC_love";
			else NextDiag.CurrentNode = "LSC_love_3";
		break;
		// <-- взаимоотношения
		
		// стал другом нарвалам
		case "donald":
			dialog.text = "Have you spoken to Donald? Is it true that the Admiral wanted to make an alliance with the Rivados and fight against the Narwhals? Is it true that you talked him out of it? There will be peace between the pirates and Narwhals?";
			link.l1 = "Yes, Mary. That is so.";
			link.l1.go = "donald_1";
		break;
		
		case "donald_1":
			dialog.text = ""+pchar.name+", I can't find the words... They also say that Donald considers you a friend. You might become one of the Narwhals, all right!";
			link.l1 = "See Donald when you can - he wants to make peace with you, too. He asks you to forgive him for his words and for failing to protect you from Chad.";
			link.l1.go = "donald_2";
		break;
		
		case "donald_2":
			dialog.text = "To hell with Donald! Though... I am glad to hear that, of course. I will see him. But you! I... I'm proud of you, all right!";
			link.l1 = "Good Lord, Mary, you... ah, you make my heart race!";
			link.l1.go = "exit";
			NextDiag.TempNode = "LSC_love";
			DeleteAttribute(npchar, "quest.donald");
		break;
		
		// ноды прощания
		case "dolly":
			dialog.text = "Let's talk! Are you in trouble?";
			link.l1 = "No. Mary... do you remember the night we first met? After we dealt with those two bastards, I told you that I'd arrived here on a ship.";
			link.l1.go = "dolly_1";
		break;
		
		case "dolly_1":
			dialog.text = "I remember, aye. Your barque was sunk and you had to swim your way here... all right?";
			link.l1 = "I lied. You would've thought me crazy if I told you the truth then. There was no barque. I used the magic idol of an Indian god, Kukulcan, on the Spanish Main, to get here.";
			link.l1.go = "dolly_2";
		break;
		
		case "dolly_2":
			dialog.text = ""+pchar.name+"... what are you talking about? Kukulcan?";
			link.l1 = "Mary, dear, you must believe me, because there is nothing rational about it, and I cannot share this with anyone, except you. Nathaniel Hawk disappeared by touching the Indian idol. He was being chased and it sent him here...";
			link.l1.go = "dolly_3";
		break;
		
		case "dolly_3":
			dialog.text = "...";
			link.l1 = "I was looking for Nathaniel. I spoke to Indian shaman and touched the idol, as Hawk did. I was teleported inside the cargo hold of the San Augustine, got out through a hole in its hull... and fate brought me to you.";
			link.l1.go = "dolly_4";
		break;
		
		case "dolly_4":
			dialog.text = "Is this supposed to be a funny story we tell our children one day, or have you gone mad?";
			link.l1 = "I'm not mad, Mary! I understand that it is difficult to believe - and it must seem crazy to you - but please... trust me.";
			link.l1.go = "dolly_5";
		break;
		
		case "dolly_5":
			dialog.text = "It seems Eric's stories were true...";
			link.l1 = "Who's Eric? What stories?";
			link.l1.go = "dolly_6";
		break;
		
		case "dolly_6":
			dialog.text = "Eric was one of the locals, an old sailor, long dead now. When I was a kid, he used to tell me stories about an Indian idol, a shrine where the Rivados sacrificed men here on the island.\nThose who touched it... vanished... and were never seen again. I thought they were just tales meant to frighten children.";
			link.l1 = "It's true, Mary. Eric wasn't lying.";
			link.l1.go = "dolly_7";
		break;
		
		case "dolly_7":
			dialog.text = "Fortunately, the ship with that terrible idol sank. I've never seen it with my own eyes.";
			link.l1 = "I found it, resting at the bottom.";
			link.l1.go = "dolly_8";
		break;
		
		case "dolly_8":
			dialog.text = "Did you dive there?! Did that blasted inventor Vedecker give you his suit? There are crabs crawling down there, all right! Bastard! putting you in danger like that--!";
			link.l1 = "Mary, don't worry about me. I can deal with the crabs. They are not as threatening as people say. I have been searching for the statue since my first day on this island and, at last, I've found it.";
			link.l1.go = "dolly_9";
		break;
		
		case "dolly_9":
			dialog.text = "And what will happen now?";
			link.l1 = "The idol is the only way out of here. I came to this island through an idol just like the one on the sea floor, and I shall use it again to get back... Mary! Are you crying? Oh Mary, please don't...";
			link.l1.go = "dolly_10";
		break;
		
		case "dolly_10":
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Shark, ";
			else sTemp = "";
			dialog.text = "Why shouldn't I? I'll cry if I want to, all right... (sobbing) These things always happen to my men! I'll be alone again!";
			link.l1 = "What do you think will happen to me? Do you really think I'd just leave you here?! I'll be back for you, on a ship. I need to take both you and "+sTemp+"Nathaniel back with me. Will you follow me out into the world?";
			link.l1.go = "dolly_11";
		break;
		
		case "dolly_11":
			dialog.text = "(in tears) Of course.... of course, I will... You will come back for me, right? How the hell do you plan to get back to the island? Only Shark knows how to sail here - and don't you dare forget about me, or I will beat you when I find you!";
			link.l1 = "Mary, enough! Of course I will come back for you! Who else could make my heart race the way it has since meeting you? Don't worry my love, Shark has shared the coordinates and directions to the island with me. I will find you again.";
			link.l1.go = "dolly_12";
		break;
		
		case "dolly_12":
			dialog.text = "You said the idol on the Spanish Main sent you here, but what if the one below takes you elsewhere, to Africa maybe? What am I supposed to do then?!";
			link.l1 = "Kukulcan is an Indian god; it will take me somewhere in the Caribbean or the Spanish Main. I only need to find a settlement; then it will be easy for me to find my ship and crew.";
			link.l1.go = "dolly_13";
		break;
		
		case "dolly_13":
			dialog.text = "(cries) Promise me... no, swear to me that you will be back, all right?!";
			link.l1 = "Mary, dear, I swear to you that I will be back. And I will take you away from this wretched place. You need not miss me for long. Enough with these tears.";
			link.l1.go = "dolly_14";
		break;
		
		case "dolly_14":
			dialog.text = "Fine, "+pchar.name+"... ... Come back to me, I'll be waiting, all right! When are you going to leave?";
			link.l1 = "I don't know yet. I need to prepare myself first, then I will dive and touch the statue. They will tell you that I have drowned - don't believe them. All will be well.";
			link.l1.go = "dolly_15";
		break;
		
		case "dolly_15":
			dialog.text = "I got it. "+pchar.name+", dear, hug me... kiss me...";
			link.l1 = "Mary... my dear Mary...";
			link.l1.go = "dolly_16";
		break;
		
		case "dolly_16":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.LSC.MaryBye"); // можно телепортироваться
			DeleteAttribute(pchar, "questTemp.LSC.FindDolly");
			SetMusic("music_romantic");
			SetLaunchFrameFormParam("", "", 0, 15);
			SetLaunchFrameFormPic("loading\inside\kiss.tga");
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 10); //крутим время
			RecalculateJumpTable();
			NextDiag.CurrentNode = "LSC_love_3";
			npchar.greeting = "mary_5"; 
		break;
		
		// дарим Мэри палаш Нарвал
		case "narval":
			dialog.text = "Jurgen? Why?";
			link.l1 = "You'll see. This is going to be a pleasant surprise.";
			link.l1.go = "narval_1";
		break;
		
		case "narval_1":
			dialog.text = "Oh, how interesting! Pleasant? All right, let's go, before I die of curiosity!";
			link.l1 = "You're going to love it, I'm sure. Let's go!";
			link.l1.go = "narval_2";
		break;
		
		case "narval_2":
			DialogExit();
			NextDiag.CurrentNode = "narval_wait";
			LocatorReloadEnterDisable("CeresSmithy", "reload6", true);
			LocatorReloadEnterDisable("CeresSmithy", "reload7", true);
			pchar.quest.LSC_PresentMary.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LSC_PresentMary.win_condition.l1.location = pchar.location;
			pchar.quest.LSC_PresentMary.function = "LSC_GotoPresentMary";
		break;
		
		case "narval_wait":
			dialog.text = "Let's go, "+pchar.name+"!";
			link.l1 = "Sure...";
			link.l1.go = "exit";
			NextDiag.TempNode = "narval_wait";
		break;
		
		case "narval_3":
			dialog.text = "Well, "+pchar.name+", what surprise have you got for me?";
			link.l1 = "Mary! Jurgen and I decided to make you a present from us both. This is a unique blade, a broadsword carrying the Narwhal name. There are only two of such swords in the world: the first was owned by Alan Milrow; this one will be yours. It is made of special iron, forged by Jurgen's masterful touch, which will never go dull or rust.";
			link.l1.go = "narval_4";
		break;
		
		case "narval_4":
			DialogExit();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Schmidt"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Mary");
			sld.dialog.currentnode = "narval_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "narval_5":
			dialog.text = "";
			link.l1 = "My dear girl... The Narwhals all know how you've suffered. You deserve to carry this broadsword, symbol of the Narwhal clan. Wear it with pride. This blade will be a terror to your enemies and guard you well in battle.";
			link.l1.go = "narval_6";
		break;
		
		case "narval_6":
			PlaySound("interface\important_item.wav");
			sld = characterFromId("Mary");
			RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
			RemoveItems(sld, "blade_17", 1);
			sTemp = GetBestGeneratedItem("blade_31");
			GiveItem2Character(sld, sTemp);
			EquipCharacterbyItem(sld, sTemp);
			sld = characterFromId("Blaze");
			dialog.text = "Jurgen? This... is for me?...";
			link.l1 = "Yes, Mary. "+sld.name+"  asked me to make it for you, and brought some unique iron from the bottom of the sea. No steel will match this material's weight and strength. I've put my soul into this sword, just as I once did with Alan's.";
			link.l1.go = "narval_7";
		break;
		
		case "narval_7":
			dialog.text = "I don't know what to say... Thank you, Jurgen, thank you! I'll carry it with pride, and be worthy of it, I swear, all right! I don't train with broadswords often; I will now!";
			link.l1 = "I have no doubt, lassie.";
			link.l1.go = "narval_8";
		break;
		
		case "narval_8":
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Mary");
			sld.dialog.currentnode = "narval_9";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "narval_9":
			dialog.text = ""+pchar.name+"... wait... you are the best man I've ever met! You're amazing, all right. D'you know what this means to me? This sword is the best gift I've ever gotten! You've done so much for me already, saved my life twice over, and yet you still surprise me! Thank you, my love!";
			link.l1 = "You deserve this, Mary. And I will continue to surprise you every day, till my last breath! Your smile fills me with joy and I'm glad you like the gift.";
			link.l1.go = "narval_10";
		break;
		
		case "narval_10":
			dialog.text = "(giggles) Thank you! Such a wonderful blade, all right! It needs a strong hand to wield it... I can't wait to start training with it!";
			link.l1 = "I imagine you'll master it in no time. Hurry to your cabin and try it out!";
			link.l1.go = "narval_11";
		break;
		
		case "narval_11":
			dialog.text = "That's what I'm going to do. Thank you again, gentleman! "+pchar.name+"... Come and see me tonight, when you're ready... (giggles)";
			link.l1 = "Of course, m'lady. I will see you in the evening.";
			link.l1.go = "narval_12";
		break;
		
		case "narval_12":
			DialogExit();
			EndQuestMovie();
			sld = characterFromId("Schmidt");
			sld.dialog.currentnode = "Jurgen";
			DeleteAttribute(sld, "quest.narval_blade");
			DeleteAttribute(npchar, "quest.narval_blade");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "CeresSmithy", "goto", "goto10", "LSC_MaryReturnNormal", -1);
			LocatorReloadEnterDisable("CeresSmithy", "reload6", false);
			LocatorReloadEnterDisable("CeresSmithy", "reload7", false); // открываем проход через трюм
			// владение Нарвалом повышает скилл ТО у Мэри и открывает перк тяжелой руки
			SetSelfSkill(npchar, 95, 50, 90, 90, 50);
			SetCharacterPerk(npchar, "HardHitter");
			npchar.quest.talisman = "true";
			npchar.quest.blade31 = "true";
		break;
		
		// Мэри дарит талисман
		case "talisman":
			dialog.text = "Here, take a look. I found it in one of the ships on the outer ring, inside a captain's chest. Every experienced sailor says that this amulet is extremely valuable for a navigator. It can protect a ship from the worst storms. Many were eager to buy it, but I wasn't selling it... I wanted you to have it, darling. Use this amulet to keep you safe at sea.";
			link.l1 = "Thank you, Mary! Very thoughtful of you, I love you!";
			link.l1.go = "talisman_1";
		break;
		
		case "talisman_1":
			GiveItem2Character(pchar, "talisman2"); 
			PlaySound("interface\important_item.wav");
			Log_Info("You have received a talisman of 'Jonah'");
			dialog.text = "Really? You like it? Oh, that's great! I'm so glad, all right.";
			link.l1 = "This is a very rare and valuable talisman. Of course I like it! Thank you, darling!";
			link.l1.go = "talisman_2";
		break;
		
		case "talisman_2":
			DialogExit();
			DeleteAttribute(npchar, "quest.talisman");
		break;
		
	// --------------------------------------вернулся на Остров---------------------------------------------
		case "return":
			dialog.text = ""+pchar.name+"... you're back. I've been waiting for you, watching the horizon every day, all right! You came back to me...";
			link.l1 = "Yes, Mary. I'm here as promised. Let me hug you, darling!";
			link.l1.go = "return_1";
		break;
		
		case "return_1":
			dialog.text = "Ah, "+pchar.name+"... You can't imagine what it's been like! The Narwhals said you drowned. They were all so sure you were dead. I kept telling them that you were alive... Of course, nobody believed me; they thought I'd gone mad after all that's happened.";
			link.l1 = "Mary... My dear! What's wrong? You're trembling... are you cold?";
			link.l1.go = "return_2";
		break;
		
		case "return_2":
			dialog.text = "No, I'm not cold. I'm just... I don't want to talk about it here. Come to my cabin later. I want to talk with you alone, all right? Are you going to see the Admiral and Nathaniel now?";
			link.l1 = "Yes. I have to talk to Shark and, of course, take Danielle to Nathaniel. I won't be long. I'll see you soon, Mary.";
			link.l1.go = "return_3";
		break;
		
		case "return_3":
			dialog.text = "I'm... I'm looking forward to seeing you. Come as soon as possible, all right?";
			link.l1 = "...";
			link.l1.go = "return_4";
		break;
		
		case "return_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload62", "CeresSmithy", "goto", "goto11", "LSC_MaryWaitInCabin", 20.0);
		break;
		
		case "adversary":
			dialog.text = ""+pchar.name+"! At last. We have to talk, all right!";
			link.l1 = "What's wrong, Mary? Something is troubling you. What happened?";
			link.l1.go = "adversary_1";
		break;
		
		case "adversary_1":
			dialog.text = "She happened... "+pchar.name+", who is that whore on your ship?";
			link.l1 = "Whore? Are you talking about Danielle? But you already kn--";
			link.l1.go = "adversary_2";
		break;
		
		case "adversary_2":
			dialog.text = "No, not Danielle. I mean that half-naked blonde strutting about your ship's deck! I saw her through the spyglass, all right!";
			link.l1 = "A-ah! That's Helen McArthur. She's involved in this odd story just like Danielle. She's serving as my officer - temporarily, of course.";
			link.l1.go = "adversary_3";
		break;
		
		case "adversary_3":
			dialog.text = "Officer? She's your officer?!";
			link.l1 = "Well, yes. What's wrong with that? Mary... damn me, you're jealous!";
			link.l1.go = "adversary_4";
		break;
		
		case "adversary_4":
			dialog.text = "Is it any wonder?!... (in tears) I've been waiting for you all this time. I didn't sleep because of you, and you come back here with some slut--";
			link.l1 = "Mary! Stop crying! What's wrong with you? You can gut a man without hesitation, and yet your eyes are always wet... Mary, dear, Helen is just an officer, serving temporarily until our common goals are achieved, nothing more.";
			link.l1.go = "adversary_5";
		break;
		
		case "adversary_5":
			if (CheckAttribute(npchar, "quest.blade31")) 
			{
				sTemp = "I've been training hard with the broadsword you gave me, and I've mastered it perfectly!";
				notification("Heavy Weapons +", "Mary");
			}
			else sTemp = "I've been training hard with rapiers and I've mastered them perfectly.";
			dialog.text = "(sobbing) Officer... Then I also want to be your officer, all right? I can fight, you know that! "+sTemp+" And I shoot well! I may not have any naval skills but I learn fast. I'm talented, all right!";
			// проход первый - ГГ либо соглашается, либо нет, отказ ведет к полному разрыву
			link.l1 = "(agree) Mary... I was going to offer you the position myself. There is no more fiery or skilled lass than you! I want you by my side!";
			link.l1.go = "adversary_hire";
			link.l2 = "(deny) Mary! Being a boarding officer is dangerous! You don't understand what you're asking for. I can't risk your life.";
			link.l2.go = "adversary_fail";
		break;
		
		// отказ
		case "adversary_fail":
			dialog.text = "Can't you? So that blonde whore can be an officer and I can't? You're lying, "+pchar.name+", you just don't want to be with me! (crying) So that girl's better than me, eh?";
			link.l1 = "Mary, you don't understand!";
			link.l1.go = "adversary_fail_1";
		break;
		
		case "adversary_fail_1":
			dialog.text = "I do! I saw her eyes gleam when she looked at you! She's not just an officer, all right! I understand that. (sobbing) Of course, I can't compete with her - she knows how to run a ship...";
			link.l1 = "Mary, what are you talking about?";
			link.l1.go = "adversary_fail_2";
		break;
		
		case "adversary_fail_2":
			dialog.text = "It's over... (crying) Go away! Go back to your whore! And I'll stay here...! Give me my key!";
			link.l1 = "But Mary...";
			link.l1.go = "adversary_fail_3";
		break;
		
		case "adversary_fail_3":
			RemoveItems(pchar, "key_mary", 1);
			dialog.text = "Go away...";
			link.l1 = "...";
			link.l1.go = "adversary_fail_4";
		break;
		
		case "adversary_fail_4": // обидел Мэри - больше от неё ничего не получишь
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			for (i=0; i<=3; i++)
			{
				LocatorReloadEnterDisable("LostShipsCity_town", "reload6"+i, true); // закрываем вход к Мэри
			}
			DoQuestReloadToLocation("LostShipsCity_town", "reload", "reload62", "");
			pchar.questTemp.LSC.Mary = "fail";
			AddQuestRecord("LSC", "23");
			bQuestDisableMapEnter = false; //открыть карту
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
		break;
		
		// соглашаемся
		case "adversary_hire":
			// проход второй - смотрим, Элен может стать подругой или нет
			bOk = (CheckAttribute(pchar, "questTemp.HelenDrinking.GaveCutlass")) && (sti(pchar.questTemp.Saga.HelenRelation) >= 6);
			if (bOk || sti(pchar.questTemp.Saga.HelenRelation) >= 5 || CharacterIsAlive("Longway"))
			{
				dialog.text = "Really? Did you really want me as your officer? "+pchar.name+", damn it, you can't imagine how happy that'd make me! I want to be your officer so much... but not on the same ship as that blonde!";
				link.l1 = "Mary, but why?!";
				link.l1.go = "adversary_hire_no";
			}
			else
			{
				dialog.text = "Really? Did you really want me as your officer? "+pchar.name+", damn it, you can't imagine how happy I am! I swear, I won't let you down, you'll see!";
				link.l1 = "Jesus, Mary, darling, you are precious. You were crying a minute ago and now your face is all lit up! And, Mary, you are not just another officer to me. You are more than that and I doubt you could ever let me down.";
				link.l1.go = "adversary_hire_yes";
			}
		break;
		
		case "adversary_hire_no": // Мэри не пойдёт, пока не ГГ не расстанется с Элен. Выбирай, кто тебе милее...
			dialog.text = "You may only see her as your officer, but I doubt she only sees you as her captain. I saw the look she gave you, I know that look, all right! But I'm the only one who gets to give them to you.";
			link.l1 = "Mary, darling, I have already told you, I do not have feelings for her, and that's it! There is nothing between us! I swear, damn it! I need her help to deal with the mess that is the Brethren of the Coast. If I don't help her, Jan Svenson won't help me to capture Tortuga, and I need him!";
			link.l1.go = "adversary_hire_no_1";
		break;
		
		case "adversary_hire_no_1":
			dialog.text = ""+pchar.name+", dear, hug me... I'm sorry. I believe you. But I won't be able stay close to her and watch her flirt with you, alright! Eventually I will take my sword and split her in half!";
			link.l1 = "I believe you would... You've got quite the temper, eh?";
			link.l1.go = "adversary_hire_no_2";
		break;
		
		case "adversary_hire_no_2":
			dialog.text = "And if I killed her - you'd leave me... and for that, I'd never forgive myself.";
			link.l1 = "So what do you propose, Mary? What should I do with her?";
			link.l1.go = "adversary_hire_no_3";
		break;
		
		case "adversary_hire_no_3":
			dialog.text = "You've said she's a temporary officer. I'll join you as soon as you turn her ashore - preferably on some uninhabited island. (giggles) I'll follow you to the ends of the Earth, all right!\nSo tell me, "+pchar.name+" dear... is she really better than me?";
			link.l1 = "Rubbish! Quit talking like that, Mary, there is no woman better than you!...";
			link.l1.go = "adversary_hire_no_4";
		break;
		
		case "adversary_hire_no_4":
			dialog.text = "Prove it, then. I won't share you, "+pchar.name+"! I'd rather let you go than share you with another, all right?";
			link.l1 = "Fine, Mary. Let's make a deal. I can't get rid of Helen now - she is critical to my quest. I will assist her in her problems, make her the queen of Isla Tesoro, then let her go, and there will be nothing left to keep you and me apart. Hopefully, it won't take longer than a month or two. Will you wait for me that long?";
			link.l1.go = "adversary_hire_no_5";
		break;
		
		case "adversary_hire_no_5":
			dialog.text = "I will, all right! Let me be clear... If you return to me, that means you've chosen me instead of her. And if you don't return... then that's that. I'll stay here and found my own clan - the Casper clan!";
			link.l1 = "Tears again? Mary, come now. Enough of that! 'Found my own clan'... You silly lass, of course I'll return! I wouldn't dare leave you amongst these rotten old ships! You would flood the island with your tears!";
			link.l1.go = "adversary_hire_no_6";
		break;
		
		case "adversary_hire_no_6":
			dialog.text = "Return as soon as possible then... "+pchar.name+", kiss me, please...";
			link.l1 = "I'll be back. I promise!"; // ага, а мы посмотрим, обманешь или нет
			link.l1.go = "adversary_hire_no_7";
		break;
		
		case "adversary_hire_no_7":
			DialogExit();
			SetMusic("music_romantic");
			SetLaunchFrameFormParam("", "", 0, 15);
			SetLaunchFrameFormPic("loading\inside\kiss.tga");
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 10); //крутим время
			RecalculateJumpTable();
			NextDiag.CurrentNode = "LSC_love"; // оставляем штучки с Мэри на Острове в силе
			pchar.questTemp.LSC.MaryWait = "true";
			AddQuestRecord("LSC", "22");
			bQuestDisableMapEnter = false; //открыть карту
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
		break;
		
		// повторный разговор после расставания с Элен
		case "adversary_hire_return":
			dialog.text = ""+pchar.name+", have you come back for me?";
			link.l1 = "Of course! Have I ever lied to you? I couldn't stand being separated from you and I've no intention of parting with you again... my love.";
			link.l1.go = "adversary_hire_yes";
			DeleteAttribute(pchar, "questTemp.LSC.MaryWait");
		break;
		
		case "adversary_hire_yes": // Элен заведомо не друг - Мэри идёт сразу, либо если выбрал Мэри
			dialog.text = "Really? "+pchar.name+"! I'll follow you anywhere! I'll never lie to you, I'll never betray you, I swear!";
			link.l1 = "I believe you, my dear... Neither will I."; // а куда же ты денешься )
			link.l1.go = "adversary_hire_yes_1";
		break;
		
		case "adversary_hire_yes_1":
			dialog.text = ""+pchar.name+", darling, hug me... We will be together, right? Promise me!";
			link.l1 = "Yes, we will be together, Mary. Forever.";
			link.l1.go = "adversary_hire_yes_2";
		break;
		
		case "adversary_hire_yes_2":
			dialog.text = "Just like Danielle and Nathaniel?";
			link.l1 = "(laughing) Yes, just like them.";
			link.l1.go = "adversary_hire_yes_3";
		break;
		
		case "adversary_hire_yes_3":
			dialog.text = ""+pchar.name+"... I love you! I think I'd marry you if you asked...";
			link.l1 = "Dear Mary... Of course - we'll talk about it later. Your life on this cemetery of ships is over. Let's get you out of here. Welcome aboard my vessel... and to the wide world, my love!";
			link.l1.go = "adversary_hire_yes_4";
		break;
		
		case "adversary_hire_yes_4":
			dialog.text = "Let's spend one last night on this island together, on the Ceres. Just the two of us. I won't let you go anywhere until the morning comes, all right.";
			link.l1 = "Well, we're currently on your ship, not mine... so I will follow your command, Captain Casper.";
			link.l1.go = "adversary_hire_yes_5";
		break;
		
		case "adversary_hire_yes_5":
			DialogExit();
			npchar.quest.hire = "true";
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			SetMusic("music_romantic");
			DoQuestCheckDelay("LSC_LastNight_CS", 3.0);
			bQuestDisableMapEnter = false; //открыть карту
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
		break;
		
		case "LSC_mary_hire":
			dialog.text = "Aye-aye, sir!";
			link.l1 = "...";
			link.l1.go = "LSC_mary_hire_1";
		break;
		
		case "LSC_mary_hire_1":
			DialogExit();
			DoQuestReloadToLocation("LostShipsCity_town", "reload", "reload62", "LSC_Mary_hire");
			if (pchar.questTemp.LSC.Mary != "return") AddQuestRecord("LSC", "24");
			pchar.questTemp.LSC.Mary = "officer";
			RemoveItems(pchar, "key_mary", 1);
		break;
		
	// --> консультации по морским сражениям
		case "sea_bomb":
			dialog.text = ""+pchar.name+"! I have an idea...";
			link.l1 = ""+npchar.name+"? It's not safe here. I ordered you to stay on the ship--";
			link.l1.go = "sea_bomb_1";
		break;
		
		case "sea_bomb_1":
			dialog.text = ""+pchar.name+", fuck me, it's not safe anywhere! There's enough gunpowder on this tub to wipe the whole island off the map! Just listen, all right?";
			link.l1 = "I'm listening, but please make it quick.";
			link.l1.go = "sea_bomb_2";
		break;
		
		case "sea_bomb_2":
			dialog.text = "The pirate corvette and the frigate. They still think we're one of theirs... that Knave bloke, all right? So let's take a few barrels of gunpowder, a fuse, and sail the frigate.\nOnce we're alongside, we light the fuse, toss them the barrel, and sail away as fast as we can. Blow their arses to matchwood, then we board the corvette.";
			link.l1 = "Risky... although... your plan just might work. But only if we can fool them until we're close enough.";
			link.l1.go = "sea_bomb_3";
		break;
		
		case "sea_bomb_3":
			dialog.text = "I say we try it, "+pchar.name+"";
			link.l1 = "All right. Let's try it. Lads! Take three barrels of gunpowder! Ha-ha, I love your mind, "+npchar.name+"! I would have never have thought of this myself.";
			link.l1.go = "sea_bomb_4";
		break;
		
		case "sea_bomb_4":
			dialog.text = "You can thank me later... (wink)";
			link.l1 = "...";
			link.l1.go = "sea_bomb_5";
		break;
		
		case "sea_bomb_5":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			npchar.dialog.currentnode = "Mary_officer";
			pchar.questTemp.Saga.BarbTemptation.Bomb = "true";
			AddQuestRecord("BarbTemptation", "15");
			AddQuestUserData("BarbTemptation", "sName", "Mary");
			pchar.questTemp.Saga.BarbTemptation.adviser = "Mary";
		break;
		
		case "fugas":
			dialog.text = "Reporting as ordered, sir! (giggle) What's the matter?";
			link.l1 = "Jackman's ship is at Sabo-Matila Cove: the heavy frigate Centurion. This ship was once the property of the Hawkes, so there must be important items and documents in the captain's cabin... We must board her.";
			link.l1.go = "fugas_1";
		break;
		
		case "fugas_1":
			dialog.text = "Damn me... How are you going to do that with our little bird? I looked through the spyglass; I've seen how many men and cannon Centurion's got, all right!";
			link.l1 = "You're right. Jackman has at least twice our number, all of them skilled cutthroats and mercenaries. It would be madness to board without whittling them down first. And with Centurion's calibre of guns, a prolonged sea battle isn't an option either. I don't know what to do...";
			link.l1.go = "fugas_2";
		break;
		
		case "fugas_2":
			dialog.text = ""+pchar.name+", they haven't recognized us as an enemy yet, have they? Liike those idiots back at Turks? We can use our gunpowder trick again...";
			link.l1 = "Mary, I just told you we have to board the frigate, not sink her!";
			link.l1.go = "fugas_3";
		break;
		
		case "fugas_3":
			dialog.text = "I know that, "+pchar.name+"! We won't sink her. We'll take a few empty rum barrels and fill them with gunpowder, grapeshot, and short fuses. Then we'll lay alongside Centurion and throw the bomb onto her deck.";
			link.l1 = "Ha! Do you really think it'll work?";
			link.l1.go = "fugas_4";
		break;
		
		case "fugas_4":
			dialog.text = "Why not? Their freeboard is higher than ours but two or three men - aided by block and tackle - could hoist and throw a fully loaded barrel easily. We'll call out - 'Here's some free rum from Knave!' The barrel will explode before they can even react.";
			link.l1 = "The exploding grapeshot will mince everyone on deck... Damn, it sounds tempting.";
			link.l1.go = "fugas_5";
		break;
		
		case "fugas_5":
			dialog.text = "Use five barrels, "+pchar.name+". We have the element of surprise. They won't suspect a thing! But we've got to sail away after throwing the bomb so they don't board us though; once it blows, then we move back in and board them.";
			link.l1 = "And they must not identify us before we toss the barrels... Damn, it won't be easy to get close to them. Jackman is not an idiot like Ghoul was.";
			link.l1.go = "fugas_6";
		break;
		
		case "fugas_6":
			dialog.text = "So you'd better grab your best amulets, "+pchar.name+". Trust Red Mary. It's worth a try.";
			link.l1 = "Good point, we have nothing to lose... Why don't you prepare the fuses?";
			link.l1.go = "fugas_7";
		break;
		
		case "fugas_7":
			dialog.text = "Aye aye, captain! You can count on me.";
			link.l1 = "Mary, you are wonderful!";
			link.l1.go = "fugas_8";
		break;
		
		case "fugas_8":
			dialog.text = "Thank you, "+pchar.name+"! I won't let you down!";
			link.l1 = "I know you won't; I hope we're the ones that don't let you down by fucking up this plan of yours... To arms!";
			link.l1.go = "fugas_9";
		break;
		
		case "fugas_9":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			pchar.questTemp.Saga.BarbTemptation.Fugas = "true";
			AddQuestRecord("BarbTemptation", "21");
			DeleteAttribute(npchar, "quest.fugas");
		break;
		// <-- консультации по морским сражениям
		
		// --> суп из черепахи
		case "terrapin_grot":
			dialog.text = "There you are! Took some effort to find you... That was amazing, Cap'n! I've never seen such a breathtaking leap before! What a hero! Though I admit, you nearly gave me a heart attack. One day you'll kill me with these tricks of yours, dear...\nNow, who the fuck would she be? I let you out of my sight for one minute, and the next I know, you find yourself a slag.";
			link.l1 = "Mary! This 'slag' is Catherine Fox, daughter of Colonel Fox, the commander of the Sea Foxes. We must take her to Antigua.";
			link.l1.go = "terrapin_grot_1";
		break;
		
		case "terrapin_grot_1":
			dialog.text = "Oh, really? How delightful. Fine, you can tell me about her... tonight. In our cabin. With me. Alone. Now, let's go, we have to hurry!";
			link.l1 = "(sigh) What would I do without you, Mary? Catherine, come on!";
			link.l1.go = "terrapin_grot_2";
		break;
		
		case "terrapin_grot_2":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			Terrapin_GotoShip();
		break;
		// <-- суп из черепахи
		
		// --> калеуче
		case "on_coast":
			dialog.text = "Oh God, you're awake! Bastard! Don't ever scare me like that again!";
			link.l1 = "Mary... dear, what happened? My head is... ugh...";
			link.l1.go = "on_coast_1";
		break;
		
		case "on_coast_1":
			dialog.text = "When we entered the captain's cabin, you were lying on the floor still as a corpse. We picked you up and dragged you to our ship - just in time, because the skeletons lying on the deck began to rise again.\n God, it was terrifying! We couldn't do anything about them! We cut the lines and tried to sail away, but a broadside from their guns severely damaged our ship and we lost control. They were some real devils, all right! And then they hoisted sails and were over the horizon in the blink of an eye.\nOur ship ran aground, so we took the longboats to this beach before the storm could destroy her. Lotta lads died today, but the ship survived in the end... barely.";
			link.l1 = "Good work, Mary... What would I do without you?";
			link.l1.go = "on_coast_2";
		break;
		
		case "on_coast_2":
			dialog.text = "Oh let's see... maybe drowned? Trapped on that ship? Torn apart by the dead? Fuck me... and fuck you too, "+pchar.name+", for giving me such a scare!";
			link.l1 = "Hush, Mary, hush. Thank you for saving me, love. How long have I been out?";
			link.l1.go = "on_coast_3";
		break;
		
		case "on_coast_3":
			dialog.text = "A day. I cleaned your wounds, gave you medicine, and poured some rum into you. You should get well soon; don't you dare die on me!";
			link.l1 = "I promise I won't, darling. Though... I've felt better...";
			link.l1.go = "on_coast_4";
		break;
		
		case "on_coast_4":
			dialog.text = "You've looked better... Was it her, "+pchar.name+"? Was it the 'Flying Dutchman'? I've heard stories, but I never imagined...\nWhy did they run us down? And why didn't they fire at us before boarding?";
			link.l1 = "Their captain wanted the amulet, the one I talked to Tuttuathapak about - the Indian shaman. That's why they boarded us, but as soon as their captain had the amulet, they didn't need us in one piece anymore...\nWhat a nightmare! A ship manned by the dead! Unbelievable... I thought I'd seen the worst the Caribbean had to offer.";
			link.l1.go = "on_coast_5";
		break;
		
		case "on_coast_5":
			dialog.text = "It figures the 'Flying Dutchman' would come for you, of all people, sooner or later. Christ, that was enough to scare me back into going to Church!";
			link.l1 = "I know how you feel. I need to go back to that Indian village, tell Tuttuathapak what happened. That ship attacked us because of the amulet! I hope that red-skinned devil has an explanation as to why the hell those living dead wanted it in the first place.";
			link.l1.go = "on_coast_6";
		break;
		
		case "on_coast_6":
			dialog.text = "All right, But be careful - you're still a mess.";
			link.l1 = "You're all the medicine I need. And... Mary, I love you...";
			link.l1.go = "on_coast_7";
		break;
		
		case "on_coast_7":
			dialog.text = "I love you too, my darling... thank God we're alive!";
			link.l1 = "...";
			link.l1.go = "on_coast_8";
		break;
		
		case "on_coast_8":
			chrDisableReloadToLocation = false;//открыть локацию
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			AddQuestRecord("Caleuche", "5");
		break;
		// <-- калеуче
		
	// --> Мэри вне LSC
		// секс - Мэри не отказывает никогда
		case "cabin_sex":
			dialog.text = RandPhraseSimple(""+pchar.name+", nothing makes me happier than being in your arms, all right... Let's go!",""+pchar.name+", I'd be with you every waking moment if it were possible. Let's go!");
			link.l1 = RandPhraseSimple("You are the best, my love...","You are wonderful, my darling...");
			link.l1.go = "exit";
			pchar.quest.sex_partner = Npchar.id;
			AddDialogExitQuestFunction("LoveSex_Cabin_Go");
		break;
		
		case "sex_after":
			dialog.text = RandPhraseSimple("Mmm, you were amazing... you always are!","That was great!");
			link.l1 = RandPhraseSimple("I'm glad I could please you, my love...","I love you Mary...");
			link.l1.go = "exit";
			NextDiag.TempNode = "Mary_officer";
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.quest.daily_sex = true;
			DeleteAttribute(npchar, "quest.iwantsex"); // belamour для бесконфликтности квестов							
			SetFunctionTimerCondition("Mary_SexReady", 0, 0, 1, false);
		break;
		
		case "room_sex":
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "tavern")
			{
				dialog.text = ""+pchar.name+", I'd love nothing better than to be in your arms, all right... But this is not the best time - we have to catch that scum Thibaut before he gets away.";
				link.l1 = "You're right as always, my girl...";
				link.l1.go = "exit";
				break;
			}
			dialog.text = RandPhraseSimple(""+pchar.name+", nothing makes me happier than being in your arms, all right... Let's go!",""+pchar.name+", I'd be with you every moment if it were possible. Let's go!");
			link.l1 = RandPhraseSimple("You are the best, my girl...","You are wonderful, my fiery-haired beauty...");
			link.l1.go = "room_sex_go";
		break;
		
		case "room_sex_go":
			DialogExit();
			pchar.quest.sex_partner = Npchar.id;
			chrDisableReloadToLocation = true;//закрыть локацию
			if (sti(pchar.money) >= 10) AddMoneyToCharacter(pchar, -10);
			if (npchar.chr_ai.type == "actor")
			{
				LAi_SetOfficerType(npchar);
				LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			}
			if (findsubstr(locations[FindLocation(pchar.location)].id, "tavern_upstairs" , 0) == -1)
			{
			//DoQuestReloadToLocation(pchar.location+"_upstairs", "quest", "quest4", "");
			DoFunctionReloadToLocation(pchar.location+"_upstairs", "quest", "quest4", "LoveSex_Room_Go");
			ChangeCharacterAddressGroup(npchar, pchar.location+"_upstairs", "quest", "quest3");
			} // patch-8
			//DoQuestFunctionDelay("LoveSex_Classic", 2.5);
			NextDiag.CurrentNode = "sex_after";
			npchar.greeting = "mary_hire";
		break;
		
		// требует секса, если давно не давал
		case "givemesex":
			dialog.text = RandPhraseSimple(""+pchar.name+", it's been too long since we had sex... You've completely forgotten about me, all right! Let's get a room for the night and leave our troubles for another day.",""+pchar.name+", I'm starting to think you've completely forgotten about me! Darling, I want to have some... private time with you. Let's get a room for the night, all right?",""+pchar.name+", where've you been? I'm dying to spend the night with you, have some wine, and relax. You've been all this time at sea and completely forgotten about me!");
			link.l1 = "Mary, dear, what are you saying, 'completely forgotten about me'? Silly girl... But I really have been too occupied - the problems that require my attention are endless. Forgive me, my love. Let's go upstairs, I am all yours for the night. The world can wait!";
			link.l1.go = "room_sex_go";
		// belamour legendary edition -->
			link.l2 = RandPhraseSimple(RandPhraseSimple("Not today, dear. I've got too much to do.","Mary, honey, how can you think I've forgotten about you? We'll spend some time together, later - right now, we have work to do."),RandPhraseSimple("You're always on my mind, Mary, but we can't afford to relax right now.","Mary "+npchar.lastname+", we have no time for this today."));
			link.l2.go = "room_sex_goNS";
		break;
		
		case "room_sex_goNS":
		if(sti(pchar.reputation.fame) > 60)
		{
			ChangeCharacterComplexReputation(pchar,"authority", 2);
			if (npchar.chr_ai.type == "actor")
			{
				LAi_SetOfficerType(npchar);
				LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			}
			NextDiag.TempNode = "Mary_officer";
			chrDisableReloadToLocation = false;
			npchar.quest.daily_sex = true;
			DeleteAttribute(npchar, "quest.iwantsex"); 
			SetFunctionTimerCondition("Mary_SexReady", 0, 0, 1, false);
			pchar.quest.Mary_giveme_sex.over = "yes"; 
			pchar.quest.Mary_giveme_sex1.over = "yes";
			dialog.text = "(sigh) Fine, I suppose I'll just play with myself in my cabin... Aye, captain.";
			link.l1 = "...";
			link.l1.go = "exit";
		}
		else
		{
			if(bImCasual) Log_Info("To refuse Mary become more famous");
			ChangeCharacterComplexReputation(pchar,"authority", -2);
			dialog.text = "Charles...";
			link.l1 = "Mary, dear, what are you saying, 'completely forgotten about me'? Silly girl... But I really have been too occupied - the problems that require my attention are endless. Forgive me, my love. Let's go upstairs, I am all yours for the night. The world can wait!";
			link.l1.go = "room_sex_go";
		}
		break;
		// <-- legendary edition
		// ругается за то, что ходил по борделям, ГГ изворачивается
		case "brothel":
			dialog.text = "Ah, there he is! You don't like me anymore, do you? Tell me!";
			link.l1 = "What?! Mary, what nonsense is this? Why do you think that?";
			link.l1.go = "brothel_1";
		break;
		
		case "brothel_1":
			dialog.text = "Then why've you been visiting those doxies, those brothel whores? I know you have, don't lie to me! You don't like something in me when we are making love, eh? (crying) Tell me...";
			link.l1 = "Mary, Mary... calm down, please, my girl. Yes, I've been to the brothel a few times but only on business matters. I wasn't looking to have any fun!";
			link.l1.go = "brothel_2";
		break;
		
		case "brothel_2":
			dialog.text = "And what kind of 'business matters' did you have in the upstairs bedroom? (sobbing) You're lying, "+pchar.name+"!";
			link.l1 = "Mary, dear, stop this, please... I really did have some business matters with the mistress of the brothel.  And yes, I did upstairs a few times - last time on a personal matter of the governor: he asked me to find his wedding ring. How could I refuse His Excellency?";
			link.l1.go = "brothel_3";
		break;
		
		case "brothel_3":
			dialog.text = "...";
			link.l1 = "And how could I explain to the mistress that I needed to look underneath the bed upstairs? I couldn't. So I had to buy a whore for the night to be allowed upstairs...\nThe second time, I was told that a merchant has lost his ship documents there. I had to pay for a girl again, in order to search the room - and I did find the documents, was paid very well for them, in fact...";
			link.l1.go = "brothel_4";
		break;
		
		case "brothel_4":
			dialog.text = "...";
			link.l1 = "And the third time I was helping the local commandant: I had to ask the whores about an officer from the garrison. That officer was suspected of espionage and treating with pirates. Eventually we caught him and I received a handsome reward...";
			link.l1.go = "brothel_5";
		break;
		
		case "brothel_5":
			dialog.text = "...";
			link.l1 = "See now? I'm telling you, it was all business. Mary, you are the one I love and need. I'm faithful to you, I swear! Do you really think I could sleep with some dirty harbour whore, when I have you? How could you even think that!";
			link.l1.go = "brothel_6";
		break;
		
		case "brothel_6":
			dialog.text = "... That sounds like the biggest load of horseshit I've ever heard in my life. But... "+pchar.name+"... are you telling me the truth? You didn't fuck another woman behind my back?";
			link.l1 = "Mary, dear, no, I promise I haven't. You are the only woman I love, it is true. Come closer, dear. Let me hug you... Dry your eyes and, please, stop being jealous! I won't even look at a brothel again, if that's what you want!";
			link.l1.go = "brothel_7";
		break;
		
		case "brothel_7":
			dialog.text = "Aye, that's what I want!... "+pchar.name+", I'm jealous because I love you... and I don't want to lose you, all right? If a slag so much a smiles at you, it's my sword that'll be inside her next!";
			link.l1 = "Jesus, Mary, calm yourself... there is no need to kill anybody! You won't lose me, I promise. It's all right, calm down. You are my only woman - and the best one in the world, at that! Trust me.";
			link.l1.go = "brothel_8";
		break;
		
		case "brothel_8":
			DialogExit();
			SetLaunchFrameFormParam("", "", 0, 5);
			SetLaunchFrameFormPic("loading\inside\kiss.tga");
			LaunchFrameForm();
			pchar.GenQuest.BrothelLock = true; // все, больше не походишь по борделям :)
			DeleteAttribute(pchar, "GenQuest.BrothelCount");
		break;
		
		// на Тайясаль
		case "tieyasal":
			dialog.text = ""+pchar.name+", what an odd question? I love you. You saved me. D'you really think I'd let you go there alone? Don't even think it, all right! I'm with you! When do we go?";
			link.l1 = "You're right, dear. How could I even question it? I'll tell you when we go. We need to prepare ourselves well, first.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "I'm ready, "+pchar.name+". I'll follow you to Hell and beyond!";
			link.l1 = "Thank you, my love...";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "19");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		// Jason Дороже золота
		case "GoldenGirl":
			pchar.quest.Mary_giveme_sex1.over = "yes"; // fix 22-03-20
			pchar.questTemp.GoldenGirl.MaryBlock = "true"; // fix 22-03-20
			dialog.text = "What've we got this time, Captain? Spanish? Pirates? Or worse?";
			link.l1 = "It's worse, Mary, much worse. The governor intends to pay a visit to a notorious courtesan and I'm supposed to accompany him as a person of interest. Boring talks, overpriced wine and dull nobles.";
			link.l1.go = "GoldenGirl_1";
			link.l2 = "Quite the opposite: an invitation to a social event, run by a noble lady. His Excellency took me by surprise when he asked me to accompany him, but to be honest, I look forward to the diversion.";
			link.l2.go = "GoldenGirl_3";
		break;
		
		case "GoldenGirl_1":
			dialog.text = "O-ho! Indeed it is worse! A courtesan! Fortified wine! Sociality! Yes, it sounds like pure torture, "+pchar.name+", you fu--";
			link.l1 = "Mary, calm down, please. It's not like I am going there to... it's not a brothel! Well... it is a brothel, but damn me if I'm not a nobleman and a man of his word. Do you really not trust me, after all we've been through? The governor only asked me for a small favor and I must oblige him, that's all!";
			link.l1.go = "GoldenGirl_2";
		break;
		
		case "GoldenGirl_2":
			dialog.text = "Yes, I've heard of a couple 'noblemen' like that, all right. I've seen them in your company too. Courtesanship is their daily bread. 'High' societies, 'dignified' entertainment my arse! Marriage doesn't stop them visiting these... ugh... 'ladies.' I thought better of you, "+pchar.name+". Well, you 'noblemen' can lick my unwashed arsehole.";
			link.l1 = "Mary, wait! Fuck...";
			link.l1.go = "GoldenGirl_6";
		break;
		
		case "GoldenGirl_3":
			dialog.text = "We've both earned a vacation. Heh, think they can handle seeing a dame dressed in a red coat? Imagine all the whispers in the corners! Someone will surely faint - that'd be fun, right?";
			link.l1 = "Mary, my dear, this is not the kind of party where you take a lady... at least not a lady like you. It's a bit complicated but let me explain--";
			link.l1.go = "GoldenGirl_4";
		break;
		
		case "GoldenGirl_4":
			dialog.text = "A lady like me? Speak plainly: I'm not good enough for those bewigged pricks. Too simple, too lowborn, all right? Not good enough for fancy parties, honourable monsieur Charles de Maure?";
			link.l1 = "No, not at all. You're amazing and I don't care about the kind of impressions we make on the people around us. The governor is trying to solve his problems with my help, as always. I will be like a valuable trophy for him; an interesting guest to impress the noble good-for-nothings.";
			link.l1.go = "GoldenGirl_5";
		break;
		
		case "GoldenGirl_5":
			dialog.text = "No, "+pchar.name+", it's fine, I get it. Nobles with nobles - and keep the riffraff outside. (bows) I sincerely hope you enjoy your sociable, My Lord Arsehole. I'll talk to you when you're back on humble soil, eh?";
			link.l1 = "Mary, wait! Ah, fuck...";
			link.l1.go = "GoldenGirl_7";
		break;
		
		case "GoldenGirl_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlExit", 10.0);
			pchar.questTemp.GoldenGirl.Angry1 = "true";
		break;
		
		case "GoldenGirl_7":
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlExit", 10.0);
			pchar.questTemp.GoldenGirl.Angry2 = "true";
		break;
		
		case "GoldenGirl_10":
			dialog.text = "I sincerely hope you enjoy your sociable, My Lord Arsehole. I'll talk to you when you're back on humble soil.";
			link.l1 = "Mary oh, come on!";
			link.l1.go = "GoldenGirl_11";
		break;
		
		case "GoldenGirl_11":
			DialogExit();
			NextDiag.CurrentNode = "GoldenGirl_10";
		break;
		
		case "GoldenGirl_12":
			dialog.text = "Look at this, all right! Our lost-in-high-society captain!";
			link.l1 = "...";
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angry1")) link.l1.go = "GoldenGirl_13";
			else link.l1.go = "GoldenGirl_17";
		break;
		
		case "GoldenGirl_13":
			dialog.text = "You disappear into the whorehouse for a day and now the whole town is talking. Charles, give me just one good reason why I shouldn't shove the Narwhal up your arse.";
			link.l1 = "Mary, I'll explain everything, but later. I need to prepare for a duel - feel free to kill me if I survive it. Meanwhile, please take care of our new ship, all right? I won her as a prize in a card game last night.";
			link.l1.go = "GoldenGirl_14";
		break;
		
		case "GoldenGirl_14":
			dialog.text = "Fuck the ship, what's this duel? To listen to the locals, you're either going to fight either the king's son or the Pope himself. Tell me what the fuck is going on!";
			link.l1 = "This man is the bastard of a very influential nobleman, Count de Levi Vantadur. It was he who challenged me, and I must win the duel without harming him - to avoid his father's wrath.";
			link.l1.go = "GoldenGirl_15";
		break;
		
		case "GoldenGirl_15":
			dialog.text = "While I'll be sitting on my arse on the tub your just won. Have you gone mad, Charles?";
			link.l1 = "I am afraid it has to be this way. The governor provided me with a couple of noble officers to be my seconds in order to avoid any confusion afterwards. I can't take you or any of the crew with me for the sake of the official integrity of the duel. This is too serious, I'm sorry.";
			link.l1.go = "GoldenGirl_16";
		break;
		
		case "GoldenGirl_16":
			dialog.text = "... You know what I'm gonna do now? I'm going to get aboard that blasted ship and get properly drunk. Do whatever you like, but you've got one thing right: if that noble whoreson fails to kill you, I'll do it myself.";
			link.l1 = "Mary, everything will be just fine, trust me. Now, wait... Fuck! Here we go again!";
			link.l1.go = "GoldenGirl_21";
		break;
		
		case "GoldenGirl_17":
			dialog.text = "There he is! We haven't gotten a single word from you all day! We heard the gossip in the market and got worried. They say you've been gambling for ships and women, and even got into a duel with some crown prince or even the Pope himself! What the fuck is going on?";
			link.l1 = "It's complicated, Mary. It'll take a while to explain. I did manage to win a frigate, though. You'll have to take care of her while I settle my dispute with her previous owner.";
			link.l1.go = "GoldenGirl_18";
		break;
		
		case "GoldenGirl_18":
			dialog.text = "So there is a duel?! Who's the previous owner? Why are you fighting him?";
			link.l1 = "It's complicated, but in short: I won his ship and his... dame. He publicly accused me of cheating and challenged me to a duel. This man is the bastard of a very influential nobleman, Count de Levi Vantadur. I will have to somehow win the duel without hurting him.";
			link.l1.go = "GoldenGirl_19";
		break;
		
		case "GoldenGirl_19":
			dialog.text = "So the rumours are true? I can understand gambling for a ship, but... a woman, really?";
			link.l1 = "Damn it, Mary, it's not like that at all! He won her from the governor; I won her back from him to release her, that's it. There is nothing more to it, I swear!";
			link.l1.go = "GoldenGirl_20";
		break;
		
		case "GoldenGirl_20":
			dialog.text = "Well, maybe this is normal for you nobles, but not for me, all right! Do what you like, say what you like... go die for her if you like! As for me, I'd like to go to the fucking ship you won and get my attic thoroughly disordered with rum. Damn you, "+pchar.name+", I believed what we had was real and would... and would last forever. Guess I expected too much!";
			link.l1 = "Mary, I don't give a damn about that woman! Just wait, please... Fuck! Here we go again...";
			link.l1.go = "GoldenGirl_21";
		break;
		
		case "GoldenGirl_21":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlToFregat", 15.0);
		break;
		
		case "GoldenGirl_24":
			dialog.text = "Charles, you came for me! I knew it, never doubted it, all right! I'm so happy to see you!";
			link.l1 = "Me too, Mary! It's been killing me, this whole affair... Thank God you're all right!";
			link.l1.go = "GoldenGirl_25";
		break;
		
		case "GoldenGirl_25":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "By the way, what exactly did you do to make them set me free so easily? Without a proper dustup or shootout, either! Oh, and I saw this lady on deck as they were dragging me out. What happened, Charles?";
			}
			else
			{
				dialog.text = "What exactly did you do to make them to release me like that? No fight, no shots fired, nothing! I saw some British peacocks on deck when they were bringing me out. What's all that about, Charles?";
			}
			link.l1 = "All that matters is you are back with me. I failed you, Mary. I am so sorry! I hope you can find it in your heart to forgive me. I hate how we left things between us.";
			link.l1.go = "GoldenGirl_26";
		break;
		
		case "GoldenGirl_26":
			dialog.text = "I already have. I'm sorry too, all right. I shouldn't have taken your dealings with that dame so personally... I should've set a proper watch that night - they would never take us so easily! I was such an idiot!";
			link.l1 = "The past is the past. I love you and I will never leave you like that again. I promise!";
			link.l1.go = "GoldenGirl_27";
		break;
		
		case "GoldenGirl_27":
			dialog.text = "I'm sorry for doubting you, Charles. Maybe... it's better I don't know what exactly it is you did, all right? We're together again and that's all that matters.";
			link.l1 = "I have no secrets from you. I'll tell you...";
			link.l1.go = "GoldenGirl_28";
		break;
		
		case "GoldenGirl_28":
			DialogExit();
			SetLaunchFrameFormParam("Some time has passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			npchar.dialog.currentnode = "GoldenGirl_28_1";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "GoldenGirl_28_1":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "What a story... doubt anyone else would believe it, all right! I knew it! I knew your 'social' night was funny business! All them noble peacocks... heartless pricks! At least I wasn't wrong about you - I knew you were different, all right!";
				link.l1 = "I'm pretty sure a lot of people out there consider me to be far worse. A proper monster out of fairy tales.";
			}
			else
			{
				dialog.text = "What a story... doubt anyone else would believe it, alright! I knew it! I knew your 'social' night was funny business! Politics, spies, con-spi-ra-cies - and yet you, once again, saved us all, all right! My hero.";
				link.l1 = "I'm not so sure about that... chances are, war with Britain will start in a few weeks. But I did what had to, Mary. You mean everything to me.";
			}
			link.l1.go = "GoldenGirl_29";
		break;
		
		case "GoldenGirl_29":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "I don't care what people think; if that's the case, you'll be my monster, Charles! And if people don't like it, let me talk to 'em. I'll always be by your side, all right!";
			}
			else
			{
				dialog.text = "I know, Charles. I always knew... but it is good to hear you say it. And I'll always be by your side, too, all right!";
			}
			link.l1 = "I never doubted it, Mary. Let's go, the lads are worried. Time to set sail and get the hell out of here. You are by my side again, and that horizon is waiting...";
			link.l1.go = "GoldenGirl_30";
		break;
		
		case "GoldenGirl_30":
			dialog.text = "Aye, aye, Captain!";
			link.l1 = "";
			link.l1.go = "GoldenGirl_31";
		break;
		
		case "GoldenGirl_31":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "GoldenGirl_GirlGoOnBoard", 10.0);
			GoldenGirl_MaryBlockDelete(); // fix 22-03-20
		break;
		
		case "GoldenGirl_32":
			dialog.text = "Charles, is it really you? I almost lost all hope, all right! God, I missed you so much! Please, please forgive me!";
			link.l1 = "No, forgive me, I didn't see it coming... Thank God you've made it, Mary! I am so happy!";
			link.l1.go = "GoldenGirl_33";
		break;
		
		case "GoldenGirl_33":
			dialog.text = "Speaking of forgiveness... to be completely honest, I'm debating whether I should shoot you or hug you. You better tell me what the hell is going on, all right?";
			link.l1 = "I love you, Mary. This is all I wanted to tell you.";
			link.l1.go = "GoldenGirl_34";
		break;
		
		case "GoldenGirl_34":
			dialog.text = "Well, that hardly explains things, but... Damn it, Charles. I love you too, all right. God, finally, I have you with me at last!";
			link.l1 = "And I don't want to spend the time we have talking about things that don't matter. Come with me and I won't dare leave you tonight, even if the sky starts falling on this miserable town. I will never leave you again. Ever.";
			link.l1.go = "GoldenGirl_35";
		break;
		
		case "GoldenGirl_35":
			dialog.text = "Maybe... it's best I'd don't know what exactly it is you did, eh? We're together again and that's all that matters...";
			link.l1 = "I have no secrets from you. I will tell you...";
			link.l1.go = "GoldenGirl_36";
		break;
		
		case "GoldenGirl_36":
			DialogExit();
			SetLaunchFrameFormParam("Some time has passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			npchar.dialog.currentnode = "GoldenGirl_36_1";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "GoldenGirl_36_1":
			dialog.text = "Are you saying this... marquise helped you bring me back? And you almost started a war between England and France? Don't get me wrong - this is all very romantic, but what'll happen now?";
			link.l1 = "I've no idea, Mary. We are together again, nothing else matters. If those in power fail to sweep it all under the rug... well, I am prepared to do my duty before the Crown.";
			link.l1.go = "GoldenGirl_37";
		break;
		
		case "GoldenGirl_37":
			dialog.text = "And that marquise of yours? Did you bring her back too? The Portuguese spoke highly of her. He assured me you withstood her advances like the Bastille castle. I want to believe him, all right, but I want to hear it from your lips.";
			link.l1 = "There is nothing going on between Madame Botot and me, Mary. I helped her, she helped me, that's all. Speaking of Bartholomew, where is he?";
			link.l1.go = "GoldenGirl_38";
		break;
		
		case "GoldenGirl_38":
			dialog.text = "Long gone, all right. Set sails right after he brought me here. I swore I wouldn't go to that damned whorehouse, so he rented a room for me, paid in advance for a couple of weeks, and just... left. Oh, I almost forgot! I've got a letter for you!";
			link.l1 = "A letter? From Bartholomew the Portuguese? I don't like where this is going...";
			link.l1.go = "GoldenGirl_39";
		break;
		
		case "GoldenGirl_39":
			dialog.text = "Go on, read it. I'll go see the lads. They're probably worried. Did everyone make it? Hope you don't mind us having a glass or two downstairs. Don't get yourself into another mess 'til I get back, all right?";
			link.l1 = "All right, but please be careful with them, Mary? I'd rather spend time with you tonight, instead of having to carry drunk bodies back to the ship. God, I still can't believe I got you back!";
			link.l1.go = "GoldenGirl_40";
		break;
		
		case "GoldenGirl_40":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_SPGirlReturn", 10.0);
			GoldenGirl_MaryBlockDelete(); // fix 22-03-20
		break;
		
		// Jason Долго и счастливо
		case "LongHappy":
			RemoveItems(pchar, "potionwine", 2);
			dialog.text = "You, me, the beach, and good wine - Charles, this is so romantic! We should do this more often, all right.";
			link.l1 = "Glad you like it. I think we'll make more time for each other from now on for occasions like this.";
			link.l1.go = "LongHappy_1";
		break;
		
		case "LongHappy_1":
			dialog.text = "What d'you mean? Something happen to the ship? Why are you on your knees?";
			link.l1 = "Because I love you, Mary. You know that, I know that, the whole world knows that. So here and now, in the face of the sea and the sky, I ask you, Mary Casper, to give me the honor of standing with me before our people and God for as many days as we are given. I, Charles de Maure, Chevalier de Monper, ask you... will you become my wife?";
			link.l1.go = "LongHappy_2";
		break;
		
		case "LongHappy_2":
			if (pchar.location == "Shore36")
			{
				dialog.text = "I dreamed of this, all right, but to actually... I... you know my answer Charles - oh, shit!";
				link.l1 = "Ha-ha! Nevermind, it is only wine, and I've never loved this shirt.";
				link.l1.go = "LongHappy_3";
			}
			else
			{
				dialog.text = "Charles, of course yes! Yes, yes, a thousand times yes!!! You... this place... nothing could make me happier!!! Oh God, I feel like my cheeks will split from smiling, all right!";
				link.l1 = "You make me happy, Mary. I drink to you, my burning Caribbean Sun!";
				link.l1.go = "LongHappy_4";
			}
		break;
		
		case "LongHappy_3":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			DoQuestFunctionDelay("LoveSex_Classic", 1.0);
			npchar.dialog.currentnode = "LongHappy_5";
			LAi_SetStayType(npchar);
		break;
		
		case "LongHappy_4":
			dialog.text = "Drink to you, my captain and future husband, all right. You're the best thing that's ever happened to me!";
			link.l1 = "But this is only the beginning - to us! And to our future together! There's so much ahead of us!";
			link.l1.go = "LongHappy_6";
		break;
		
		case "LongHappy_5":
			dialog.text = "Drink to you, my captain and future husband, all right. You're the best thing that's ever happened to me!";
			link.l1 = "But this is only the beginning - to us! And to our future together! There's so much ahead of us!";
			link.l1.go = "LongHappy_6";
		break;
		
		case "LongHappy_6":
			DialogExit();
			chrDisableReloadToLocation = false;
			npchar.dialog.currentnode = "Mary_officer";
			LongHappy_MarryToSenPierre();
		break;
		
		case "LongHappy_7":
			dialog.text = "Charles, speak to Abbot Benoit so we can proceed, all right? But I won't wear a dress. I hope you won't be offended.";
			link.l1 = "Mary, I love you in any outfit and ... well, you know. You can wear anything you like; anyone who has a problem with that can speak to me! But, I do want to consult you about the guests and the ceremony.";
			link.l1.go = "LongHappy_8";
		break;
		
		case "LongHappy_8":
			if (LongHappy_CheckSaga())
			{
				dialog.text = "You know, most of the people who'd sincerely rejoice at our happiness won't even be allowed within sight of this island, all right, nevermind the church. So... let's get married here with all the good burghers, as expected, and then we'll sail to Isla Tesoro and celebrate properly, with real friends! What d'you think?";
				link.l1 = "Great idea! Let's do it. I'll talk to Abbot Benoit. We'll need to figure out who's coming, send out invitations... so much to do!";
				link.l1.go = "LongHappy_9";
			}
			else // Сага провалена по времени или утоплен Центурион
			{
				dialog.text = "You know, I don't have many friends except the lads from the crew. So, invite those of 'em you like, and I'll be happy, all right?";
				link.l1 = "As you say, sweetheart. I'll talk to Abbot Benoit and organize everything. You're worthy of a magnificent ceremony.";
				link.l1.go = "LongHappy_9a";
			}
		break;
		
		case "LongHappy_9":
			dialog.text = "Don't worry about the guests, I'll take care of that, all right. I'll write to our friends and arrange everything. But first, tell me: who d'you want at our wedding?";
			link.l1 = "My ideal is you, me, and our closest friends. After all the official faces here in Martinique, we will want some sincerity.";
			link.l1.go = "LongHappy_10";
			link.l2 = "Let's make this a day to remember. Call everyone! No one will be left out!";
			link.l2.go = "LongHappy_11";
		break;
		
		case "LongHappy_9a":
			dialog.text = "You know, a shipboard ceremony with a chaplain on the quarterdeck at sunset on the open water would be enough for me, all right. But, if this is what you want, we'll celebrate! Charles ... I'm going to cry. Hug me, all right ...";
			link.l1 = "Mary...";
			link.l1.go = "LongHappy_9b";
		break;
		
		case "LongHappy_9b":
			dialog.text = "All right, I'm calm. Sorry, this is all new. But Charles, I want to take part in the organization. We also need to arrange a party for the lads, all right, but I don't think the whole crew will fit in the church. I'll make arrangements with the tavern, but we'll need booze and money - you know how sailors like to party.";
			link.l1 = "All right, that 's what we'll do. What do I have to prepare?";
			link.l1.go = "LongHappy_9c";
		break;
		
		case "LongHappy_9c":
			pchar.questTemp.LongHappy.MarryMoney = 100000;
			pchar.questTemp.LongHappy.MarryRum = 100;
			if (sti(RealShips[sti(pchar.ship.type)].Class) < 2)
			{
				pchar.questTemp.LongHappy.MarryMoney = 200000;
				pchar.questTemp.LongHappy.MarryRum = 150;
			}
			if (GetCompanionQuantity(pchar) > 1)
			{
				pchar.questTemp.LongHappy.MarryMoney = 300000;
				pchar.questTemp.LongHappy.MarryRum = 200;
			}
			dialog.text = "I think, "+sti(pchar.questTemp.LongHappy.MarryMoney)+" pesos will be enough, all right. "+sti(pchar.questTemp.LongHappy.MarryRum)+" barrels of rum - nothing worse than running out of drink! As soon as you collect everything, come to the tavern. I'll figure out the rest.";
			link.l1 = "Fine, honey, see you there.";
			link.l1.go = "LongHappy_9d";
		break;
		
		case "LongHappy_9d":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "10_1");
			AddQuestUserData("LongHappy", "sName", "Mary");
			LongHappy_MarryGoToBenua();
		break;
		
		case "LongHappy_10":
			pchar.questTemp.LongHappy.SmallMarry = "true";
			dialog.text = "Got it. But we'll also have to visit Sharptown and prepare things there. I think fifty barrels of rum and a couple dozen barrels of wine will do just fine, all right. But, just in case, I'll need three hundred thousand pesos.";
			link.l1 = "That's a lot, but the occasion's worth it. I'll scrape it together, don't worry. Now, I'm going to visit the abbot and then go to Sharptown.";
			link.l1.go = "LongHappy_12";
		break;
		
		case "LongHappy_11":
			pchar.questTemp.LongHappy.BigMarry = "true";
			dialog.text = "Great, we'll get everyone together, all right! But we'll have to visit Sharptown and prepare everything - we'll need a galleon's worth of booze!  I think a hundred barrels of rum and fifty barrels of wine will do just fine. But, just in case, I will add five hundred thousand pesos. No good if the party ends for lack of drink, right?";
			link.l1 = "Yes, our friends must not die of thirst -  I'll get everything, don't worry! Now, I'm going to visit the abbot and then go to Sharptown.";
			link.l1.go = "LongHappy_12";
		break;
		
		case "LongHappy_12":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "10");
			AddQuestUserData("LongHappy", "sName", "Mary");
			LongHappy_MarryGoToBenua();
		break;
		
		case "LongHappy_13":
			dialog.text = "Everything's ready, Charles. I'll arrange for the drink to be unshipped, then I'll go to the local tavern, meet the baron, and hand over the invitations. Wait here, all right?";
			link.l1 = "You're at the helm, dear! I'll just mess around somewhere. I never imagined expeditions to the jungle of the Spanish Main would be easier than preparing for a wedding!";
			link.l1.go = "LongHappy_14";
		break;
		
		case "LongHappy_14":
			DialogExit();
			SetLaunchFrameFormParam("Several hours have passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 4, 0);
			LongHappy_IslaTesoroRemoveGoods();
			npchar.dialog.currentnode = "LongHappy_15";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "LongHappy_15":
			dialog.text = "We're done here, Charles, all right! I arranged everything. Believe me - it'll be wonderful! Only, just one thing... the local tavern burned down during some feast a week ago. But it's almost rebuilt, bigger and better than before! We should all be able to fit.";
			link.l1 = "I sure hope we don't burn it down again. I really liked the Old Woodpecker! Anyway, we still have a lot to do. It's time to set sail. Mary... you're the best, you know that, right?";
			link.l1.go = "LongHappy_16";
		break;
		
		case "LongHappy_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "12");
			pchar.questTemp.LongHappy = "marry_wait";
			pchar.questTemp.LongHappy.DrinkReady = "true";
		break;
		
		case "LongHappy_17":
			dialog.text = "So... here we go? The guests've arrived, the church is ready. I know we're closer than most spouses, and these are just a few big words in a beautiful hall, but damn me - I was less nervous in that ancient Indian city, all right!";
			link.l1 = "I'm sure it's absolutely normal, my love; I'm nervous too. I think Abbot Benoit is waiting, I'll go to him and find out when the service will begin.";
			link.l1.go = "LongHappy_18";
		break;
		
		case "LongHappy_18":
			dialog.text = "Fine, I'll walk around town for a while, need to clear my head, all right! Charles... d'you understand there's no turning back?";
			link.l1 = "Mary, dear, for me, there was no turning back from the moment we met. I've longed for this day with all my heart. Don't worry, everything will be fine.";
			link.l1.go = "LongHappy_19";
		break;
		
		case "LongHappy_19":
			DialogExit();
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0);
			AddQuestRecord("LongHappy", "14");
			AddQuestUserData("LongHappy", "sName", "Mary");
		break;
		
		case "LongHappy_20":
			dialog.text = "Yes.";
			link.l1 = "";
			link.l1.go = "LongHappy_21";
		break;
		
		case "LongHappy_21":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_27";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_22":
			dialog.text = "Yes.";
			link.l1 = "";
			link.l1.go = "LongHappy_23";
		break;
		
		case "LongHappy_23":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_29";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_24":
			dialog.text = "Yes.";
			link.l1 = "";
			link.l1.go = "LongHappy_25";
		break;
		
		case "LongHappy_25":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_31";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_26":
			dialog.text = "";
			link.l1 = "I, Charles Henry de Maure, Chevalier de Monper, take you, Mary Casper, to be my wife, to have and to hold, from this day forward, for better and for worse, for richer and for poorer, in sickness and in health, until death do us part. According to God's Holy Law, in the presence of our Lord, I make this vow.";
			link.l1.go = "LongHappy_27";
		break;
		
		case "LongHappy_27":
			dialog.text = "I, Mary Casper, take you, Charles de Maure, to be my husband, to have and to hold, from this day forward, for better and for worse, for richer and for poorer, in sickness and in health, until death do us part. According to God's Holy Law, in the presence of our Lord, I make this vow.";
			link.l1 = "";
			link.l1.go = "LongHappy_28";
		break;
		
		case "LongHappy_28":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_33";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_29":
			dialog.text = "Amen.";
			link.l1 = "";
			link.l1.go = "LongHappy_30";
		break;
		
		case "LongHappy_30":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_35";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_31":
			dialog.text = "This is unbelievable, all right! I'm... I'm crying, I'm sorry Charles, I will... my nose has turned red, hasn't it?";
			link.l1 = "Mary de Maure, my wife, you are as beautiful on this day as you are every other day!";
			link.l1.go = "LongHappy_32";
		break;
		
		case "LongHappy_32":
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) dialog.text = "Thank you, Charles, thank you... Everything was so solemn and wonderful! This is the best day of my life, all right!!! Look, how happy everyone is! But, it's time for you to hobnob with our guests and accept their congratulations! When you're done - come back - let's check on the lads at the tavern.";
			else dialog.text = "Thank you, Charles, thank you... Everything was so solemn and wonderful! This is the best day of my life, all right!!! Look, how happy everyone is! But, it's time for you to hobnob with our guests and accept congratulations! When you're done, come back - we're expected in Sharptown.";
			link.l1 = "I'll do so right away, sweetheart. One kiss and I'm off!";
			link.l1.go = "LongHappy_33";
		break;
		
		case "LongHappy_33":
			DialogExit();
			LongHappy_MarryKiss();
		break;
		
		case "LongHappy_34":
			dialog.text = "Charles, my love, have you talked to our guests?";
			link.l1 = "Not yet, sweetheart, I'll be back soon.";
			link.l1.go = "LongHappy_34_1";
			link.l2 = "Yes, I've never had so many 'congratulations' heaped upon me at once. And you know what? Most of them were sincere!";
			link.l2.go = "LongHappy_35";
		break;
		
		case "LongHappy_34_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_34";
		break;
		
		case "LongHappy_35":
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) 
			{
				dialog.text = "Yes, yes! It's been the same for me! Of course, some people are clearly surprised by my outfit, all right! And I'm so giddy that half the things people've said have just passed me by. Charles, the lads in the tavern are expecting us - we should go to 'em. They'll be happy to congratulate their captain, all right!";
				link.l1 = "We're going right now. But... I would like to end this day in a more romantic place than a room in the tavern. I hope, my wife, you don't mind spending this night in our cabin? More so, now there's no watch aboard ship...";
			}
			else
			{
				dialog.text = "Yes, yes! It's been the same for me! Of course, some people are clearly surprised by my outfit, all right! And I'm so giddy that half the things people've said have just passed me by. But Charles, we're expected in Sharptown. When do we set sail?";
				link.l1 = "Right now. We can't allow our guests to drink our supplies dry! I hope, my wife, you don't mind spending this night in our cabin?";
			}
			link.l1.go = "LongHappy_36";
		break;
		
		case "LongHappy_36":
			dialog.text = "I wouldn't mind if we spent it in a mosquito-infested hut on a desert island, so long as I have you.";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) link.l1 = "I feel the same. Let's go, before the boys drink all the rum and set the tavern on fire.";
			else link.l1 = "I love you too. Then... let's set sail!";
			link.l1.go = "LongHappy_37";
		break;
		
		case "LongHappy_37":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_38";
			LongHappy_MarryComplete();
		break;
		
		case "LongHappy_38":
			dialog.text = "Oh my dear, I'm so happy! Today is such a wonderful day...";
			link.l1 = "";
			link.l1.go = "LongHappy_38_1";
		break;
		
		case "LongHappy_38_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_38";
		break;
		
		case "LongHappy_39":
			dialog.text = "Tear off his unwashed head, Charles!";
			link.l1 = "";
			link.l1.go = "LongHappy_40";
		break;
		
		case "LongHappy_40":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angerran") && CharacterIsAlive("Angerran")) // fix 02-04-20
			{
				sld = characterFromId("Angerran");
				sld.dialog.currentnode = "Shivo_6";
			}
			else 
			{
				sld = characterFromId("LH_Dussak");
				sld.dialog.currentnode = "Dussak_5";
			}
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "LongHappy_41":
			dialog.text = "I'm fine, all right! How is Nathaniel, is he alive?";
			link.l1 = "So much blood... Dannie, is he breathing? I see him breathing!";
			link.l1.go = "LongHappy_42";
		break;
		
		case "LongHappy_42":
			DialogExit();
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_9";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "LongHappy_43":
			dialog.text = "Faster, dear, don't waste time!";
			link.l1 = "";
			link.l1.go = "LongHappy_43_1";
		break;
		
		case "LongHappy_43_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_43";
		break;
		
		case "LongHappy_44":
			dialog.text = "We won, all right! Sorry I'm late. We got stuck upstairs with a dozen of these bastards. Had my hands full.";
			link.l1 = "It's fine, I took care of things here. I'm happy to have finally finished this story with Jacques... At last, he got what he deserved.";
			link.l1.go = "LongHappy_45";
		break;
		
		case "LongHappy_45":
			dialog.text = "Then lets get back to Sharptown, all right? We should check on Nathaniel. The madman risked his life for us!";
			link.l1 = "You're right, my love. Go, I'm right behind you.";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner")) link.l1.go = "LongHappy_46";
			else link.l1.go = "LongHappy_48";
		break;
		
		case "LongHappy_46":
			dialog.text = "By the way, honey, we've found Marcus! He was in the cargo hold, bound and unconscious.";
			link.l1 = "Alive?";
			link.l1.go = "LongHappy_47";
		break;
		
		case "LongHappy_47":
			dialog.text = "Bloody, but he'll heal. You can't break our baron, all right; barely awake and already craving a scrap!.";
			link.l1 = "Good old Marcus! Well, to the shore.";
			link.l1.go = "LongHappy_48";
		break;
		
		case "LongHappy_48":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LongHappy_BarbExit", -1);
		break;
		
		case "LongHappy_49":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") && CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "I'm sorry, Charles, all right, I... I went for a walk. I saw that you were back, I heard everyone was alive and had won, but I... what's wrong with me, all right?!";
				link.l1 = "All is going to be well, love, all is going to be well. I'm sad too. But we won, and Jacques Barbazon paid for his crimes.";
				link.l1.go = "LongHappy_50";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
				{
					dialog.text = "I feel awful about Gino, Charles, all right! When I heard, I couldn't believe it!";
					link.l1 = "I can't believe it either... I never imagined the day would end like this.";
				}
				else
				{
					dialog.text = "We won again, all right! My husband is a storm on the upstart barons of the Brethren of the Coast! Friends are alive, enemies are dead - that's the way it ought to be, all right.";
					link.l1 = "We made it, my love. We made it.";
				}
				link.l1.go = "LongHappy_50";
			}
		break;
		
		case "LongHappy_50":
			dialog.text = "You can barely stand on your feet, all right! Come on, Dannie found us a house on the outskirts, I don't want to go back to the ship right now. We'll sit and drink to our fallen friends - this all is too much for a sober head to handle, all right.";
			link.l1 = "Yes, Mary, let's go.";
			link.l1.go = "LongHappy_51";
		break;
		
		case "LongHappy_51":
			DialogExit();
			LongHappy_LogBook();
			DoQuestCheckDelay("LongHappy_MarryFinalizing", 0.5);
		break;
		
		case "LongHappy_52":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "I feel awful about Gino, Charles, all right! When I heard, I couldn't believe it!";
				link.l1 = "I can't believe it either... I never imagined the day would end like this.";
			}
			else
			{
				dialog.text = "Sorry I'm late, my dear. I went for a walk, then I saw you and ran as fast as I could! Danielle stopped me when Gino said the danger was over. I'm so glad you're all right!";
				link.l1 = "Me too, darling. And we won. Barbazon's dead, and the barons are gathering what's left of their crews. The battle is over.";
			}
			link.l1.go = "LongHappy_53";
		break;
		
		case "LongHappy_53":
			dialog.text = "Charles, you can barely stand! And no one can find Tichingitu.";
			link.l1 = "Jan gave me a tip... Let's take a walk to Sabo-Matila Cove; a few people saw him heading in that direction.";
			link.l1.go = "LongHappy_54";
		break;
		
		case "LongHappy_54":
			DialogExit();
			LongHappy_LogBook();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.longhappy_shoregirl.win_condition.l1 = "location";
			pchar.quest.longhappy_shoregirl.win_condition.l1.location = "Shore_ship1";
			pchar.quest.longhappy_shoregirl.function = "LongHappy_SetShoreGirl";
		break;
		
		case "LongHappy_55":
			dialog.text = "Well, there's our stoic Indian, all right! Come on, Dannie found us a house here on the outskirts - you're dead on your, Charles.";
			link.l1 = "There it is ... kidnap me, my beauty. And let it all seem like a bad dream come the morning.";
			link.l1.go = "LongHappy_56";
		break;
		
		case "LongHappy_56":
			DialogExit();
			DoQuestCheckDelay("LongHappy_MarryFinalizing", 0.5);
		break;
		
		case "LongHappy_57":
			dialog.text = "Don't get me wrong, husband; the church was luxurious, but here the atmosphere is so much more soulful, all right. Well... that's all, Charles. All our troubles are behind us. We can relax.";
			link.l1 = "Well, not quite 'all', my wife - our life goes on together! Hard to say what the future holds. So, let's go, have a drink with our lads, and then - well, you remember: the cabin, the wine, and us...";
			link.l1.go = "LongHappy_58";
		break;
		
		case "LongHappy_58":
			DialogExit(); // телепорт в каюту
			DoQuestReloadToLocation("My_Cabin", "rld", "loc1", "LongHappy_InSPcabin");
		break;
		
		case "LongHappy_59":
			dialog.text = "My husband... the word sounds so sweet, all right. Now you're mine, forever.";
			link.l1 = "I've been yours for a long time already, and now I will be forever, my love...";
			link.l1.go = "LongHappy_60";
		break;
		
		case "LongHappy_60":
			DialogExit();
			DoQuestFunctionDelay("LoveSex_Classic", 1.0);
			npchar.dialog.currentnode = "LongHappy_61";
			LAi_SetStayType(npchar);
		break;
		
		case "LongHappy_61":
			dialog.text = "I'm so happy, Charles! And now, everything we do, we do together, right?";
			link.l1 = "Sure, sweetheart! Side by side, together forever!";
			link.l1.go = "LongHappy_62";
		break;
		
		case "LongHappy_62":
			DialogExit();
			LAi_SetOfficerType(npchar);
			npchar.dialog.currentnode = "Mary_officer";
			DoQuestReloadToLocation("FortFrance_town", "reload", "reload1", "LongHappy_InSPComplete");
		break;
		
		// Jason Исла Мона
		case "IslaMona":
			dialog.text = "I'm afraid this sickness is taking its toll on your girls, Rodrigo. Keep 'em busy with knitting or something!";
			link.l1 = "This conversation's going nowhere. We agreed that we will go to church tomorrow - to pray, of course.";
			link.l1.go = "IslaMona_1";
		break;
		
		case "IslaMona_1":
			DialogExit();
			LAi_SetOfficerType(npchar);
			npchar.dialog.currentnode = "Mary_officer";
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_26";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_2":
			dialog.text = "I'm proud of you, my love!";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
		break;
		
		case "IslaMona_3":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			sld = characterFromId("Himenes_companion_1");
			sld.dialog.currentnode = "island_man_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_4":
			dialog.text = "Charles...";
			link.l1 = "What's on your mind, Mary?";
			link.l1.go = "IslaMona_5";
		break;
		
		case "IslaMona_5":
			dialog.text = "(laughs) The fact that me and Alan, we wanted to do the same thing on the island you've done here";
			link.l1 = "Your... Alan?";
			link.l1.go = "IslaMona_6";
		break;
		
		case "IslaMona_6":
			dialog.text = "One hell of a dreamer he was - the two of you would've been great friends if he'd lived.";
			link.l1 = "Our tastes are certainly the same in one regard...";
			link.l1.go = "IslaMona_7";
		break;
		
		case "IslaMona_7":
			dialog.text = "What? Ha-ha-ha! Oh, shut up, Charles!\nEither way, this is amazing... We've given these people so much joy!";
			link.l1 = "We gave them a chance; the rest, they've done on their own. So... what are you thinking?";
			link.l1.go = "IslaMona_8";
		break;
		
		case "IslaMona_8":
			dialog.text = "See me later and you'll find out...";
			link.l1 = "Oh I will!";
			link.l1.go = "IslaMona_9";
		break;
		
		case "IslaMona_9":
			DialogExit();
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			DoQuestFunctionDelay("IslaMona_ChurchReloadToRoom", 0.5);
			ChangeCharacterAddressGroup(npchar, "IslaMona_TwoFloorRoom", "goto", "goto4");
			DoQuestFunctionDelay("LoveSex_Classic", 2.0);
			NextDiag.CurrentNode = "sex_after";
			npchar.greeting = "mary_hire";
			pchar.questTemp.IslaMona.Doorlock = "true";
		break;
		
		case "tonzag_jailed":
			dialog.text = "I like dark and tight spaces. Makes me feel calm. Finally, I can gather my thoughts\nIt's as if all my cares... are simply gone! I've missed this feeling...";
			link.l1 = "You need to see a doctor.";
			link.l1.go = "tonzag_jailed_1";
			link.l2 = "It's as if you're back on the Ceres.";
			link.l2.go = "tonzag_jailed_2";
			locCameraFromToPos(-15.50, 2.28, -1.23, true, -27.00, -10.60, -22.70);
		break;

		case "tonzag_jailed_1":
			dialog.text = "... Too bad I'm not alone. In silence, in darkness, in solitude, aye; that would be perfect.";
			link.l1 = "Keep dreaming, Mary Casper.";
			link.l1.go = "exit";
		break;

		case "tonzag_jailed_2":
			dialog.text = "One time a crab crawled into my bed - I cut it up, and ate it.";
			link.l1 = "Keep dreaming, Mary Casper.";
			link.l1.go = "exit";
		break;
		
		case "tonzag_aftershot":
			dialog.text = "Masked arsehole! Ouch! Help me, my dear - got to break the bars!";
			link.l1 = "Quiet! I'm trying to figure out what to do!";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Mary_officer";
			AddDialogExitQuestFunction("Tonzag_TichingituAfterShot");
		break;
		
		case "tonzag_after_boarding":
			dialog.text = "Darling, these masked arseholes are everywhere! They breached the hull and are crawling through it like crabs! We've got to cut 'em all down, all right!";
			link.l1 = "Mary, stay here, take command! Take the ship away from the battle - we won't survive another boarding action!";
			link.l1.go = "tonzag_after_boarding_1";
			DelLandQuestMark(npchar);
		break;
		
		case "tonzag_after_boarding_1":
			dialog.text = "And where are you off to? I'm not about to let you go!";
			link.l1 = "I need to help Hercule and our crew! Trust me, Mary!";
			link.l1.go = "tonzag_after_boarding_2";
		break;

		case "tonzag_after_boarding_2":
			dialog.text = "Aye aye, darling!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_GoToGunDeck");
		break;
		
		case "tonzag_after_victory":
			dialog.text = "Victory! Come to me, dear! I want you for an hour or two.";
			link.l1 = "Ah...";
			link.l1.go = "tonzag_after_victory_1";
			link.l2 = "Let's go!";
			link.l2.go = "tonzag_after_victory_1";
		break;

		case "tonzag_after_victory_1":
			dialog.text = "Hey, Hercule! I'm so glad to see you, grey beard!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_MaryBoardingDialog");
		break;

		case "tonzag_after_victory_2":
			dialog.text = "";
			link.l1 = "Mary! Mary, wait! I need your report!";
			link.l1.go = "tonzag_after_victory_3";
		break;

		case "tonzag_after_victory_3":
			dialog.text = "Huh? Well, we won, aye! That damn ship fled. I split one bastard's skull in two!\nPhew, damn buttons!";
			link.l1 = "Oh, Mary...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ShowFrame");
		break;
		
		case "tonzag_dead":
			dialog.text = "Oh God, don't look at me, dear! I'm going to... phew!";
			link.l1 = "Hang in there, girl. I'm here!";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Mary_officer";
		break;

		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Mary_officer":
			// если шлялся по борделям - устроит небольшой скандал 
			if (sti(pchar.GenQuest.BrothelCount) >= 3 && LAi_grp_playeralarm == 0)
			{
				dialog.Text = ""+pchar.name+"! I need to talk to you, all right? Seriously!";
				Link.l1 = "What happened, Mary? Is there a problem?";
				Link.l1.go = "brothel";
				break;
			}
			ref rLoc = &Locations[FindLocation(pchar.location)];
			dialog.text = LinkRandPhrase("I am listening, my dear captain!","Yes, "+pchar.name+", All ears!","Have a job for me, "+pchar.name+"?");
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Mary, I'm going to visit the old Indian city Tayasal. I won't lie to you: this trip is very dangerous and more - it involves using that idol I told you about. Will you... follow me?";
				Link.l4.go = "tieyasal";
			}
			////////////////////////казначей///////////////////////////////////////////////////////////
			// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Mary, give me a full report.";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "I want you to purchase certain goods every time we are docked.";
				Link.l12.go = "QMASTER_2";
			}

			if (CheckAttribute(npchar, "quest.fugas"))
			{
				Link.l3 = "Mary, I need your advice.";
				Link.l3.go = "fugas";
			}
			Link.l1 = "Mary, I have an order for you...";
            Link.l1.go = "stay_follow";
			if (pchar.location == Get_My_Cabin() && !CheckAttribute(npchar, "quest.daily_sex"))
			{
				Link.l2 = RandPhraseSimple("Dear, I want you right now. Are you all right with that?","Mary, how about we... stay together for a while? Just the two of us.");
				Link.l2.go = "cabin_sex";
			}
			if (rLoc.type == "tavern" && !CheckAttribute(npchar, "quest.daily_sex") && sti(pchar.money) >= 10)
			{
				Link.l2 = RandPhraseSimple("Mary, let's rent a room and stay together?","Love, I want to stay with you in private... how about we rent a room and forget about everything for a few hours?");
				Link.l2.go = "room_sex";
			}
			link.l9 = "It's nothing, Mary.";
			link.l9.go = "exit";
			NextDiag.TempNode = "Mary_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Charles, she's a beauty, alright! We fixed that hole below the waterline and dried the sails. Wha--What did you expect? Don't look at me like that, I never studied to be a purser.";
			Link.l1 = "Sorry, Mary, I really didn't think it through.";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "Charles, I'm fine! I already got my coat and my blade. But thanks for asking, it's so nice of you, all right!";
			link.l1 = "But I don't even... Whatever, forget about it, dear, we're good.";
			link.l1.go = "exit";
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
					Link.l3 = "Mary, change ammo for firearms.";
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
            dialog.Text = "At once, my love!";
            Link.l1 = "...";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "At once, my love!";
            Link.l1 = "...";
            Link.l1.go = "Exit";
        break;
		//<-- ----------------------------------- офицерский блок ----------------------------------------
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

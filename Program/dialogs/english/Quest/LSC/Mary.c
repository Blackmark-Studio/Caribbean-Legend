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
			dialog.text = "Marcello, I know him. He is a friend of Rivados and the pirates. Adolf would never work with him. Smell the air... do you sense the smell of gun powder? And there is blood on the wall... He killed Adolf and is now trying to fool us! He must be working for the admiral! Kill him!";
			link.l1 = "...";
			link.l1.go = "Cabin_fight";
		break;
		
		case "Cabin_fight":
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			DialogExit();
			sld = characterFromId("Marchello");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt.TownAttack"))
			{
				for (i=1; i<=3; i++)
				{
					sld = characterFromId("CyclopGuard_"+i);
					LAi_SetWarriorType(sld);
					LAi_group_MoveCharacter(sld, "EnemyFight");
				}
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LSC_CyclopNMaryDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// на улице
		case "Town":
			dialog.text = "Oh, excuse me... Can I ask you to help me?";
			link.l1 = "Hm. I am always ready to help a gorgeous lady. What's the problem?";
			link.l1.go = "Town_1";
		break;
		
		case "Town_1":
			dialog.text = "See, I bought a chest filled with all kinds of metal pieces from Sessile Gallard. She lives on the 'Eva'. Jurgen promised to forge a good thing for me, alright... I bought it, aye, but I can't bring it to him. So foolish of me!\nPerhaps you could help me carry the chest from 'Eva' to Narwhal's block on 'Esmeralda'? Please, I'd be very grateful!";
			link.l1 = "And that's it? Sure, miss, I will help you. Not much of a trouble.";
			link.l1.go = "Town_2";
		break;
		
		case "Town_2":
			dialog.text = "Thank you! I will show you to the chest.";
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
			link.l1 = "Wow! Ha, it seems that no help is needed... Mary.";
			link.l1.go = "Town_5";
		break;
		
		case "Town_5":
			dialog.text = "Smart boy, huh? Less talking, damn you! Where is the key? Give it or you will regret!";
			link.l1 = "So rude! Such a bad tongue of such a beautiful girl. What key?";
			link.l1.go = "Town_6";
		break;
		
		case "Town_6":
			dialog.text = "The key which you have taken from Adolf Barbier. And don't you deny it- You were seen leaving his cabin. Adolf is dead and it was your work... Now, give me the key!";
			link.l1 = "So it was you after all... That was a mistake, girl, a very big mistake!";
			link.l1.go = "Town_7";
		break;
		
		case "Town_7":
			PlaySound("Voice\English\LSC\Mary Casper-04.wav");
			dialog.text = "What did you say?... Damn it, you are not an ordinary robber! He is working for the admiral! Take him down, lads!";
			link.l1 = "...";
			link.l1.go = "Cabin_fight";
		break;
		
	// ---------------------------------покушение на Акулу - вариант N --------------------------------
		case "caroline":
			dialog.text = "Chad, that's him! Damn it, he has brought a helper here! Lads, kill them all!";
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
			dialog.text = "You are just in time... I would have never dealt with them myself... Fuh! To be honest, I thought that I am finished!";
			link.l1 = "You fought like a Valkyrie! I have never seen such a beautiful gal fight so vigorously...";
			link.l1.go = "mary_1";
		break;
		
		case "mary_1":
			dialog.text = "Ha-ha, you are a gentleman, aren't you: making compliments with a sword still in your hand. Thanks for your help. You have saved my life, alright! Introduce yourself, gentleman, I have never seen you before. Are you new here?";
			link.l1 = "My name is "+GetFullName(pchar)+", but beautiful ladies can call me "+pchar.name+". . Am I new here? Hm... I am.";
			link.l1.go = "mary_2";
		break;
		
		case "mary_2":
			dialog.text = "I can tell, surely I would have noticed such a handsome man around. My name is Mary, Mary Casper. Though they call me Red Mary. That is because I am a redhead, alright.";
			link.l1 = "I am glad to meet you, Mary...";
			link.l1.go = "mary_3";
		break;
		
		case "mary_3":
			dialog.text = "Oh, I am glad twice over... considering I'd have been dead was it not for you! That bastard Chad wasn't bluffing. Such a vermin! And I was a fool to leave the lower doors open. That is how you got inside, is it not?";
			link.l1 = "Yes. I was swimming around the island trying to find a place to get out.";
			link.l1.go = "mary_4";
		break;
		
		case "mary_4":
			dialog.text = "I see. This unlocked door almost got me killed. Jurgen himself forged the locks for me, you can't open them without the right key and lock picking won't help. Besides, I won't stay still while someone is trying to get inside - four barrels of my pistol will leave four holes on a door or a body, ha-ha!\nBut damned Chad won't leave me alone. He had already sent cutthroats to 'persuade' me to take his side, he is definitely serious about it. If it wasn't for you, I would have said yes. I'll have to stay here under the siege, "+pchar.name+", alright! Thank God I have predicted that, I have enough supplies and Jurgen is my neighbour, I didn't quarrel with him.";
			link.l1 = "Mary, why won't you tell me more about your problems? I see that you need my help, but I didn't understand a thing that came from your lips.";
			link.l1.go = "mary_5";
		break;
		
		case "mary_5":
			dialog.text = "Aye, I need help, alright! I am alone now. I had a quarrel with Donald, then Chad turned out to be a villain. Oh, I am sorry, I am bubbling again. Fine, I will tell you about the situation I've found myself in...";
			link.l1 = "Bear in mind that I am new here, so I don't understand much yet. Who is this Chad trying to 'persuade' or to kill you? Who is Donald?";
			link.l1.go = "mary_6";
		break;
		
		case "mary_6":
			dialog.text = "Chad is a pirate from admiral Shark Dodson's crew, a jailer on 'Tartarus'...";
			link.l1 = "Wait! What did you say? Shark Dodson? Is he here?";
			link.l1.go = "mary_7";
		break;
		
		case "mary_7":
			dialog.text = "You must have arrived tonight since you don't already know that. Where else would Shark be, but here? My troubles began when he arrived here several months ago. Though, I admit, this is all Narwhals' and Rivados' fault. When Shark came here with his crew, he wanted to establish a base, but our people and Rivados really disliked the idea. They attacked Shark's brig at night and set it on fire\nThey better didn't! Shark's crew is full of devils, not men, alright. First, they destroyed hostile boats, then landed and started a real slaughter. Narwhals retreated and Rivados ran away as fast as they could. Finally, pirates captured San Augustine where the most of Island's provisions and supplies are held, then they took Tartarus\nShark imprisoned our leader Alan Milrow, who also was my... my close friend, and the Rivados wizard Chimiset. He sent them to rot in Tartarus's cages like beasts. It's easy to swim to Tartarus from here and I managed to visit Alan a few times. There I met Chad Kapper, Shark assigned him as a jailer. I asked Chad to release Alan, promised him money, but he was afraid to confront the admiral\nAnd then Alan was murdered in prison. Chad told me that Shark did this, alright. So I went to Donald, who was elected leader in Alan's place, and demanded to attack the pirates immediately, yet he refused, said that those sea devils are too tough for us. That was when I told him to fuck himself\nMy people were worthless in this matter, so I made a deal with Kapper, the scum wanted to take Shark's place. We had a plan - to lure admiral from his fortress to some shady place and kill him there. We also found a sniper with a good rifle. He could shoot admiral from the Fury's mast\nNow the interesting part is, the day before yesterday I visited Tartarus at night, wanted to say something important to Chad concerning our plan. Swam to the boat and accidentally overheard Chad talking with two Narwhals. Turned out that Shark didn't kill Alan. Chad did. He then secretly spread gossips about admiral's involvement\nHe murdered him because of me. First, he wanted to take me for a plaything in his bed. Second, he wanted to use me in order to get rid of Shark - he knew that I would always seek vengeance. Can you imagine? What a coward!";
			link.l1 = "Yeah, I've met the likes of him...";
			link.l1.go = "mary_8";
		break;
		
		case "mary_8":
			dialog.text = "Fucker is worse! He... I lack the words to describe that monster! I went away that time, found him next morning and told him everything I thought of him. Aye, I told him I will have nothing to do with his plot against the admiral.";
			link.l1 = "And he didn't like it, obviously... That was done in anger, Mary. You should be more cautious.";
			link.l1.go = "mary_9";
		break;
		
		case "mary_9":
			dialog.text = "I can't, I couldn't keep my mouth shut. The bastard killed Alan and tried to use me in order to achieve his dirty goals! Scum! Yes, sure, he got angry and promised that I would regret that. I said I would cut off his balls and feed them to the crabs!\nHe threatened to send his Narwhal pals after me if I didn't change my mind. I laughed, didn't think a Narwhal would dare to raise a hand on me.";
			link.l1 = "It seems, you were mistaken.";
			link.l1.go = "mary_10";
		break;
		
		case "mary_10":
			dialog.text = "Aye, "+pchar.name+", I have underestimated Chad and overestimated myself. He found the bastards who would dare attack a lone girl in her own cabin. And what should I do now? I can't trust anyone. I can't trust even my own people. These two are Narwhals, I knew both of them, alright. As long as Chad is alive - I am in danger, he will send more, no doubt\nI am scared to walk out, the sniper we found to assassinate Shark may shoot me from Rivados territory and escape easily. I won't go to Donald, he will not listen\nAdmiral? I cant explain my role in preparations of his assassination! He will send me to rot in the cells of 'Tartarus', I am sure! Fuck, I am trapped. I am going to sit here with my guns loaded until the supplies run out and then... I have no idea what will be of me!";
			link.l1 = "Well, in that case I have no choice, but to help you, eh? Your situation falls in line with my plans here anyways...";
			link.l1.go = "mary_11";
		break;
		
		case "mary_11":
			dialog.text = "You intend to help me? But how? Are you going to kill Chad?";
			link.l1 = "That part of the plan, sure.";
			link.l1.go = "mary_12";
		break;
		
		case "mary_12":
			dialog.text = "Listen, "+pchar.name+", , I appreciate your intentions, but Chad is out of your zone. He is one of the most trusted friends of the admiral and even if you get to him - Shark's pirates will kill you, they don't know the truth, alright.";
			link.l1 = "Calm down. I will have to talk to Shark anyway.";
			link.l1.go = "mary_13";
		break;
		
		case "mary_13":
			dialog.text = "So you are a pirate too?! Tell me about yourself, look at you: broke into my place, saved my life, promised to help all handsome looking, yet I don't know a thing about you!";
			link.l1 = "Fine... I am not a pirate, but currently I work with a certain pirate baron Jan Svenson. I came here to find Nathaniel Hawk. Have you heard of him?";
			link.l1.go = "mary_14";
		break;
		
		case "mary_14":
			dialog.text = "No, who is he?";
			link.l1 = "He is another famous pirate. It's a pity that you haven't met him, he must be here somewhere. I was looking for Shark as well, but I didn't expect to find him here.";
			link.l1.go = "mary_15";
		break;
		
		case "mary_15":
			dialog.text = "But how did you get here? You look too well for a survivor of a shipwreck.";
			link.l1 = "And why would you think that I was shipwrecked?";
			link.l1.go = "mary_16";
		break;
		
		case "mary_16":
			dialog.text = "That is the only way to get here. Only Shark somehow sailed here.";
			link.l1 = "Well, Shark was not the only one as you can see.";
			link.l1.go = "mary_17";
		break;
		
		case "mary_17":
			dialog.text = "So, have you got a ship? Great!";
			link.l1 = "Don't get excited so soon, Mary. I got here through... on a barque, but it sunk to the bottom.";
			link.l1.go = "mary_18";
		break;
		
		case "mary_18":
			dialog.text = "A-ah... Well, as I said - a shipwreck. You are trapped here with us now, alright.";
			link.l1 = "Mary, let me tell you my plan. You mentioned that Chad was planning to kill Shark. I need Shark alive, Jan and me are going to make him head of the pirates. That is why I have to warn him, because from your story, I am sure that Chad will attempt it with or without your help.";
			link.l1.go = "mary_19";
		break;
		
		case "mary_19":
			dialog.text = "Aye, probably. He has the men to make it happen...";
			link.l1 = "It means that my primary goal is to win over Shark's trust and save him. Then, I will get to Chad, officially. Have you got any evidence to prove his intentions?";
			link.l1.go = "mary_20";
		break;
		
		case "mary_20":
			dialog.text = "I have got his letter which was brought here by one of these... idiots on the floor. There are threats and details which admiral might find interesting. Wait! And what about me? Shark will find out I was working with Chad!";
			link.l1 = "Mary, are you going to sit here forever armed with pistols and hide your sweet face from everyone? Do you really think me to be one of the idiots who want a beautiful lady dead? Show me the letter first, Let's see what I can do...";
			link.l1.go = "mary_21";
		break;
		
		case "mary_21":
			GiveItem2Character(pchar, "letter_chad_1");
			RemoveItems(npchar, "letter_chad_1", 1);
			dialog.text = "Here. What do you think?";
			link.l1 = "Hold on... (reading). Yes, it appears Chad is a special sort of bastards to infest this Earth. This letter will be enough to make Shark eager to put a noose around Chad's neck himself. Don't you worry milady, I will make sure that Shark does not suspect a thing about you. He will be too busy with Chad anyways.";
			link.l1.go = "mary_22";
		break;
		
		case "mary_22":
			dialog.text = "Will you do that? Promise me, alright! Swear to me that you won't betray me!";
			link.l1 = "Mary, I swear to you, I won't betray you. Don't worry about that, I did not save you just to see that happen\nChad won't leave you in peace, that's for sure, you know too much. Stay here until he is dead.";
			link.l1.go = "mary_23";
		break;
		
		case "mary_23":
			dialog.text = "Aye, I will stay here. I don't want to be shot by a sniper or to be stabbed in the back.";
			link.l1 = "Good girl. Close all doors, including the lower ones. Have you only got one key?";
			link.l1.go = "mary_24";
		break;
		
		case "mary_24":
			dialog.text = "No. There is another. Do you want it?";
			link.l1 = "Yes. Do you trust me?";
			link.l1.go = "mary_25";
		break;
		
		case "mary_25":
			dialog.text = "Well, if the gentleman who just saved my life betrays me, there is no reason to live at all... Take it.";
			link.l1 = "Don't be scared, beauty! I won't let you down. I will see you as soon as I resolve this mess. I hope it doesn't take too long.";
			link.l1.go = "mary_26";
		break;
		
		case "mary_26":
			GiveItem2Character(pchar, "key_mary");
			dialog.text = "It's alright, I will can hold this place for a few weeks.";
			link.l1 = "Great. I won't waste time then. I will take the corpses out and talk to Shark. He is on the 'San Augustine', right?";
			link.l1.go = "mary_27";
		break;
		
		case "mary_27":
			dialog.text = "Yes, he is always there. And get out the same way you got here - I won't let you step on the upper deck of 'Ceres Smithy'.";
			link.l1 = "Interesting, and why is that?";
			link.l1.go = "mary_28";
		break;
		
		case "mary_28":
			dialog.text = "Because you won't be able to do help me if you die. This is Narwhals' territory and they will kill you as an outsider.";
			link.l1 = "Hm... Got it. Well, Mary, see you. I will be back as soon as it is safe.";
			link.l1.go = "mary_29";
		break;
		
		case "mary_29":
			dialog.text = "You can see me anytime you like, I have no problem with that. (giggles)";
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
			dialog.text = "Hello, "+pchar.name+", any good news for me? Are you alright?";
			if (pchar.questTemp.Saga.SharkHunt == "mary_whiskey")
			{
				link.l1 = "The problem with admiral is resolved. He has no interest in hunting you down, Chad's treason is the only thing that troubles him.";
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
			dialog.text = "Oh, thank God! Thank you, I won't forget it, alright! At least there is no threat from the admiral. And what about Chad? What did Shark do?";
			link.l1 = "We have convinced the Rivados to attack him. Layton Dexter has taken guards out of 'Tartarus' and gave the key to Black Eddie. Black guys freed their wizard Chimiset, but they have failed to kill Chad. They killed two of his Narwhal friends, but he ran away and is hiding somewhere.";
			link.l1.go = "letters_1";
		break;
		
		case "letters_1":
			dialog.text = "Damn! That means that I must be even more careful now...";
			link.l1 = "Calm down, Mary. I am sure he has more threatening people to be conserned with. He probably knows who pitted the Rivados to attack him. He will do anything to kill Shark, not you.";
			link.l1.go = "letters_2";
		break;
		
		case "letters_2":
			dialog.text = "Do you really belileve that? Chad is not one to let things go so easily. Ah, I am too tired to be afraid any longer...";
			link.l1 = "Hm. I didn't think you are the kind of lady to get spooked easily.";
			link.l1.go = "letters_3";
		break;
		
		case "letters_3":
			dialog.text = "Ha! Am I not? I am not scared of fighting face to face, but to sit on my ass waiting to be killed? I am very scared "+pchar.name+", alright!...";
			link.l1 = "Trust me Mary: Kapper has his plate full with the admiral, as of the moment... I need your advice.";
			link.l1.go = "letters_4";
		break;
		
		case "letters_4":
			dialog.text = "My advice? What kind of advice?";
			link.l1 = "Eddie found two letters writen by Chad. Read them, perhaps you know what he is up to. You were in on the plan with Chad after all...";
			link.l1.go = "letters_5";
		break;
		
		case "letters_5":
			RemoveItems(pchar, "letter_chad", 1);
			RemoveItems(pchar, "letter_chad_1", 1);
			dialog.text = "Give them here... (reading). Axel is our merchant on 'Esmeralda', alright. Chad wanted to buy whiskey from him for some reason. Strange! Chad only drinks rum, he says whiskey is 'the moonshine of peasants'...";
			link.l1 = "And what about the second letter?";
			link.l1.go = "letters_6";
		break;
		
		case "letters_6":
			dialog.text = "Marcello? Marcello Cyclops, a former royal hunter. He is the main reason I refuse to leave this cabin.";
			link.l1 = "Is he the sniper you've hired?";
			link.l1.go = "letters_7";
		break;
		
		case "letters_7":
			dialog.text = "Yes. Marcello can shoot a fly at forty feet, despite him missing an eye, alright. His mission was to take down Shark using a long range stutzen from the bowsprit of Santa Florentina, or Fury's platform...";
			link.l1 = "So it seems that Chad decided to take out Shark. But what's the point of Eva then? Cecille? Drinks?";
			link.l1.go = "letters_8";
		break;
		
		case "letters_8":
			dialog.text = "Eva is a neutral ship and Cecille is Cecille Halard, a funny old woman who lives there. She moved in there not long ago from the Santa Florentina. Orelie Bertine is a friend of hers. They lived here together before the time I was even born, alright.";
			link.l1 = "Hm. Nonsense. Two large lads are hiding from an old woman to drink a barrel of whiskey together. Rubbish... Not the best time to drink, Chad!";
			link.l1.go = "letters_9";
		break;
		
		case "letters_9":
			dialog.text = "I already told you that he doesn't drink whiskey. Only rum, something does not add up.";
			link.l1 = "Fine, whatever. Do you know where to find Cyclops?";
			link.l1.go = "letters_10";
		break;
		
		case "letters_10":
			dialog.text = "No. He is very private. He shoots birds every day at the outer ring and no one knows where he sleeps. He often visited Rivados before.";
			link.l1 = "Such bad luck... Well, I will go and talk to Axel then. Perhaps he will make more sense of this. See you, Mary! Close the door!";
			link.l1.go = "letters_11";
		break;
		
		case "letters_11":
			dialog.text = ""+pchar.name+"! Please find Chad. Hurry, I haven't slept since the last attack.";
			link.l1 = "Hold on, darling. I will do the best I can.";
			link.l1.go = "letters_12";
		break;
		
		case "letters_12":
			DialogExit();
			NextDiag.CurrentNode = "mary_wait";
			pchar.questTemp.Saga.SharkHunt = "trader_whiskey"; // флаг на магазин - поиск виски
			AddQuestRecord("SharkHunt", "35");
		break;
		
		case "happy":
			dialog.text = ""+pchar.name+"! How did he get here? Did he come to...";
			link.l1 = "Yes, to kill you, Mary. He came here through Jurgen's cabin and used a rope to climb down here.";
			link.l1.go = "happy_1";
		break;
		
		case "happy_1":
			dialog.text = "Ah! I am such a fool to have forgotten about that way! Chad taught him, I am sure, alright!";
			link.l1 = "Most likely. I barely made it. He was coming after you.";
			link.l1.go = "happy_2";
		break;
		
		case "happy_2":
			dialog.text = "And I was sleeping. He would have killed me in a second... But how did you know that he was on the way here?";
			link.l1 = "I did... I just did, Mary.";
			link.l1.go = "happy_3";
		break;
		
		case "happy_3":
			dialog.text = "You saved me again, handsome. You always come at the perfect time, alright. How do you do this?";
			link.l1 = "Well, I don't know. One of my many talents. Your siege is over - Chad Kapper is dead and so are all of his friends. Cyclops was the last of his rotten crew.";
			link.l1.go = "happy_4";
		break;
		
		case "happy_4":
			dialog.text = "Really? Is it true, "+pchar.name+"? You aren't fooling me, right?";
			link.l1 = "Not at all. Eh, I need some rest after the events of the past few days...";
			link.l1.go = "happy_5";
		break;
		
		case "happy_5":
			dialog.text = "I can finally breathe freely now! Thank you... Thank you so much! You are my hero, alright!";
			link.l1 = "I love the sound of that, being your hero, that is. Just glad you are safe at last.";
			link.l1.go = "happy_6";
		break;
		
		case "happy_6":
			dialog.text = "So?";
			link.l1 = "What is it, pretty one?";
			link.l1.go = "happy_7";
		break;
		
		case "happy_7":
			dialog.text = "Why are you standing there? Come on, gentleman.";
			link.l1 = "And do what?";
			link.l1.go = "happy_8";
		break;
		
		case "happy_8":
			dialog.text = "You really are a gentleman... Come here and hug me, kiss me at last, you want this, I see that, alright!";
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
			link.l1 = "I am here, Mary, darling...";
			link.l1.go = "happy_11";
		break;
		
		case "happy_11":
			dialog.text = "Everything can wait. Admiral will wait, your pirates will wait. This night is only for the two of us, alright?!";
			link.l1 = "Of course...";
			link.l1.go = "happy_12";
		break;
		
		case "happy_12":
			dialog.text = "And all the next nights after that too...";
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
				dialog.text = ""+pchar.name+"! You are back... without her. So she could not take you from me!";
				link.l1 = "Mary, your suspicions were unreasonable. You are the only one for me. I was always with you in my thoughts and in my dreams.";
				link.l1.go = "adversary_hire_return";
				break;
			}
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = ""+pchar.name+", , why are you fighting with Narwhals? I live on their territories, actually, I am one of them in case you've forgotten. Please, go to Fazio and make peace, I'm begging you.";
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
				dialog.text = ""+pchar.name+"! All Narwhals are talking about you!";
				link.l1 = "Really, my darling?";
				link.l1.go = "donald";
				break;
			}
			if (CheckAttribute(npchar, "quest.talisman")) // подарок
			{
				dialog.text = ""+pchar.name+"! This broadsword is incredible! Thank you again!.. I want to give you a present too. Of course, it does not compare to yours but I want you to take it, alright.";
				link.l1 = "Mary, the value of a present doesn't matter... Thank you, my love";
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
				link.l1 = "Thanks, Mary! I have no doubt about that.";
				link.l1.go = "exit";
				link.l2 = "No, Mary. I want to get some rest here. Are you ok with that?";
				link.l2.go = "rest_morning"; // отдых
			}
			else
			{
				dialog.text = "Well, "+pchar.name+", how are you doing? Running around the Island as usual?";
				link.l1 = "Yes, Mary. There are a lot of things to be done...";
				link.l1.go = "LSC_love_1";
			}
			NextDiag.TempNode = "LSC_love";
		break;
		
		case "LSC_love_1":
			if (stf(environment.time) >= 18.0 && stf(environment.time) < 22.0) //вечер
			{
				dialog.text = "It is evening already, "+pchar.name+", what things are you talking about? Stay here, let's have some drinks and relax, alright! It can wait until morning!";
				link.l1 = "(laughing) Of course, love, say less...";
				link.l1.go = "LSC_love_evening";
				if (sti(pchar.money) >= 500)
				{
					link.l2 = "Mary, let's got to the tavern today!";
					link.l2.go = "LSC_tavern";
				}
				link.l3 = "Mary, darling, I am very busy now. I will be back a bit later.";
				link.l3.go = "LSC_love_2";
				break;
			}
			if (stf(environment.time) >= 10.0 && stf(environment.time) < 18.0) //день
			{
				dialog.text = "Don't forget to visit me in the evening. And don't you dare avoid me, alright!";
				if (CheckAttribute(npchar, "quest.narval_blade"))
				{
					link.l3 = "Mary, we have to go and see Jurgen today.";
					link.l3.go = "narval";
				}
				link.l1 = "Sure, Mary, how can I? Surely i'll visit you.";
				link.l1.go = "exit";
				link.l2 = "No, Mary. I want to rest here tonight. Are you fine with that?";
				link.l2.go = "rest_afternoon"; // отдых
				NextDiag.TempNode = "LSC_love";
				break;
			}
			dialog.text = "What are you talking about? It is already night time! No, you ain't going anywhere, you will stay here, with me, alright!";
			link.l1 = "(laughing) as you will, honey...";
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
			dialog.text = LinkRandPhrase("A great idea, "+pchar.name+", alright! I agree!","Aye, let's go, "+pchar.name+"! Sancho has a fine collection of wines, there is much to choose from!","Oh, I would be glad, alright! It is always fun in Sancho's tavern and he has a great selection of wines!");
			link.l1 = "Let's go!";
			link.l1.go = "LSC_love_tavern";
		break;
		
		// --> отдых
		case "rest_morning":
			dialog.text = "Of course, "+pchar.name+"? Sure, have some rest, alright!";
			link.l1 = "I will stay until the midday...";
			link.l1.go = "rest_day";
			link.l2 = "I will stay until the evening...";
			link.l2.go = "rest_evening";
		break;
		
		case "rest_afternoon":
			dialog.text = "Of course, "+pchar.name+"? Sure, have some rest, alright!";
			link.l1 = "I will stay until the evening...";
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
				dialog.text = ""+pchar.name+"! You are back... without her. So she he couldn't take you away from me!";
				link.l1 = "Mary, your suspicions were unreasonable. You are the only one to me. I was always with you in my thoughts and in my dreams.";
				link.l1.go = "adversary_hire_return";
				break;
			} // 291112
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = ""+pchar.name+", why are you fighting with Narwhals? I live on their territories, actually, I am one of them, in case you forgot. Please, go to Fazio and make peace, I'm begging you.";
				link.l1 = "Alright, Mary, I will do ask you ask.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(npchar, "quest.talisman")) // подарок
			{
				dialog.text = ""+pchar.name+"! This broadsword is incredible! Thank you again!.. I want to give you a present as well. Of course, it does not compare to yours in value, but I want you to take it, alright.";
				link.l1 = "Mary, the value of a present doesn't matter... Thank you, my love";
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
				link.l1 = "Of course, Mary.";
				link.l1.go = "exit";
				link.l2 = "No, Mary. I want to get some rest here. Are you ok with that?";
				link.l2.go = "rest_morning"; // отдых
			}
			else
			{
				dialog.text = "Aren't you going to your Kukulcan thingy, "+pchar.name+"?";
				link.l1 = "Not yet, still preparing.";
				link.l1.go = "LSC_love_4";
			}
			NextDiag.TempNode = "LSC_love_3";
		break;
		
		case "LSC_love_4":
			if (stf(environment.time) >= 18.0 && stf(environment.time) < 22.0) //вечер
			{
				dialog.text = "It is evening already, "+pchar.name+". Why won't you stay here? I want to be with you.";
				link.l1 = "Alright, darling, I am staying...";
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
				dialog.text = "Good luck and don't forget about me... Come and see me in the evening if you can, alright!";
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
			dialog.text = "What are you talking about? It is night time! No, you ain't going anywhere, you will stay here, alright!";
			link.l1 = "(laughing) Alright, I will stay...";
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
				link.l1 = "Well done, officer! I order you to get on board of the ship immediately. But first: kiss your captain!";
				link.l1.go = "LSC_mary_hire";
			}
			else
			{
				dialog.text = "That was amazing, love... Good morning!";
				link.l1 = "Good morning, honey! You are wonderful!";
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
			dialog.text = "Have you spoken to Donald? Is it true that the admiral wanted to make an alliance with Rivados and fight against Narwhals? Is it true that you have dissuaded him from it? There will be peace between the pirates and Narwhals, right?";
			link.l1 = "Yes, Mary. That is so.";
			link.l1.go = "donald_1";
		break;
		
		case "donald_1":
			dialog.text = ""+pchar.name+", I can't find the words... They also say that Donald considers you a friend. You might become one of Narwhals, alright!";
			link.l1 = "See Donald when you can - he wants to make peace with you, too. He asks you to forgive him for his words and for failing to protect you from those two bastards.";
			link.l1.go = "donald_2";
		break;
		
		case "donald_2":
			dialog.text = "To hell with Donald! Though I am glad to hear that of course. I will see him. But you! I... no, not like that... I am proud of you, alright!";
			link.l1 = "Good Lord, Mary... you are... ah, you make my heart race!";
			link.l1.go = "exit";
			NextDiag.TempNode = "LSC_love";
			DeleteAttribute(npchar, "quest.donald");
		break;
		
		// ноды прощания
		case "dolly":
			dialog.text = "Let's talk! Are you in trouble?";
			link.l1 = "No. Mary, do you remember the night we first met? After we dealt with those two bastards, I told you that I had arrived here on a ship.";
			link.l1.go = "dolly_1";
		break;
		
		case "dolly_1":
			dialog.text = "I remember, aye. Your barque was sunk and you had to swim your way here... alright!";
			link.l1 = "I lied. You would have thought me crazy if I told you the truth then. There was no barque. I used an unexplicable force of an Indian god 'Kukulcan' to get to this place.";
			link.l1.go = "dolly_2";
		break;
		
		case "dolly_2":
			dialog.text = ""+pchar.name+"... What are you talking about? Kukulcan?";
			link.l1 = "Mary, dear, you must believe me, because there is nothing rational about it, and I cannot share this with anyone, but you. Nathaniel Hawk disappeared by touching the Indian idol, he was being chased and it saved him...";
			link.l1.go = "dolly_3";
		break;
		
		case "dolly_3":
			dialog.text = "";
			link.l1 = "I was looking for Nathaniel. I had a talk with an Indian shaman and had to do the same as Hawk. I was teleported inside the cargo hold of the 'San Augustine', got out through a hole in its hull, and fate brought me to you.";
			link.l1.go = "dolly_4";
		break;
		
		case "dolly_4":
			dialog.text = "Is this supposed to be a funny story of our first encounter, that we tell our children one day? Or have you gone mad?";
			link.l1 = "I am serious, Mary. I understand that it is difficult to believe, and it must seem crazy to you, but please, trust me.";
			link.l1.go = "dolly_5";
		break;
		
		case "dolly_5":
			dialog.text = "It seems that Eric's stories were true...";
			link.l1 = "Who is Eric? And what did he tell you?";
			link.l1.go = "dolly_6";
		break;
		
		case "dolly_6":
			dialog.text = "Eric was one of the locals, an old sailor. He is dead already. When I was a kid, he used to tell me stories about a golden idol, a shrine where Rivados sacrificed men. Here, on the Island\nThose who touched it, vanished, and were never seen again. I thought they were just tales, meant to scare the children.";
			link.l1 = "It is true, Mary. Eric wasn't lying.";
			link.l1.go = "dolly_7";
		break;
		
		case "dolly_7":
			dialog.text = "Fortunately, the ship with that terrible idol had sunk. I've never seen it with my own eyes.";
			link.l1 = "I have found it, resting at the bottom.";
			link.l1.go = "dolly_8";
		break;
		
		case "dolly_8":
			dialog.text = "Did you dive there?! Did that blasted inventor Vedecker give you his suit? There are crabs, crawling down there, alright! Bastard! putting you in danger like that!";
			link.l1 = "Mary, don't worry about me. I can deal with the monsters. They are not as threatening as people say. I have been searching for the statue since my first day on this island and, at last, I have found it.";
			link.l1.go = "dolly_9";
		break;
		
		case "dolly_9":
			dialog.text = "And what will happen now?";
			link.l1 = "This is the only way out of here. I came to this place through an idol just like this one, and I shall use it again to get back... Mary! Are you crying? Mary! Stop that!";
			link.l1.go = "dolly_10";
		break;
		
		case "dolly_10":
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Shark, ";
			else sTemp = "";
			dialog.text = "Why should I? I will cry, I want to cry, alright... (sobbing) Such things always happen to my men! I will be alone again!";
			link.l1 = "What do you think will happen to me? Do you really think I would leave you here?! I will be back for you, on a ship. I need to take both you and "+sTemp+"Nathaniel back with me. Will you follow me to the outer world?";
			link.l1.go = "dolly_11";
		break;
		
		case "dolly_11":
			dialog.text = "(in tears) Of course.... Sure, I will... You will come back for me, yes? How the hell do you plan to get back to the island? Only Shark knows how to sail here. And don't you dare forget about me, or I will beat you when I find you!";
			link.l1 = "Mary, enough with those wild thoughts of yours! Of course I will come back for you, who else is to keep my heart beating the same way it has since the day I met you? Don't worry my love, Shark has shared the coordinates and directions with me. I will find my way to you.";
			link.l1.go = "dolly_12";
		break;
		
		case "dolly_12":
			dialog.text = "You said that a statue has taken you here directly from Main, but what if this statue takes you elsewhere, to Africa maybe? What am I to do without you then?!";
			link.l1 = "Kukulcan is an Indian god, it will take me somewhere within the Caribbean or Main. I only need to find a settlement, then it will be easy for me to find my ship and crew.";
			link.l1.go = "dolly_13";
		break;
		
		case "dolly_13":
			dialog.text = "(cries) Promise me... no, swear to me that you will be back, alright!";
			link.l1 = "Mary, dear, I swear to you that I will be back. And I will take you away from this wretched place. You need not miss me for too long. Enough with the tears.";
			link.l1.go = "dolly_14";
		break;
		
		case "dolly_14":
			dialog.text = "Fine, "+pchar.name+"... ... Come back to me, I will be waiting, alright! When are you going to leave?";
			link.l1 = "I don't know yet. I need to prepare myself first, then I will dive and touch the statue. They will tell you that I have drowned - don't believe them. All will be well.";
			link.l1.go = "dolly_15";
		break;
		
		case "dolly_15":
			dialog.text = "I got it. "+pchar.name+", dear, hug me... Kiss me...";
			link.l1 = "Mary... My dear Mary...";
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
			dialog.text = "Oh, how interesting! Pleasant? This is great, alright! Let's go, before I die of curiosity!";
			link.l1 = "You are going to like it, I am sure. Let's go!";
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
			dialog.text = "Well, "+pchar.name+", , what surprise have you got for me?";
			link.l1 = "Mary! Jurgen and I decided to make you a present from us both. This is a unique blade, a broadsword carrying the Narwhal name. There are only two of such swords in the world: the first was owned by Alan Milrow, this one will be yours. It is made of special steel, forged by Jurgen's masterful touch, which will never go dull or rust.";
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
			link.l1 = "Our dear girl... All Narwhals know how have you suffered. I suppose that you deserve to carry this broadsword, a symbol of the Narwhal clan. Wear it with pride. This blade will be a threat to your enemies and protect you in battle.";
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
			link.l1 = "Yes, Mary. "+sld.name+"  asked me to make it for you, and brought some unique iron from the bottom of the sea, no steel will match this material's weight nor strength. I've put my soul into this sword, just as I did once with Alan's.";
			link.l1.go = "narval_7";
		break;
		
		case "narval_7":
			dialog.text = "I don't know what to say... Thank you, Jurgen! Thank you, alright! I will carry it with pride, and match the blade's worth, I swear, alright! I haven't been training with broadswords enough, but I will train hard now!";
			link.l1 = "In that, I have no doubt, lassie.";
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
			dialog.text = ""+pchar.name+"... wait, no... You are the best man I've ever met! You are amazing, alright! Do you know how much this means to me? This sword is the best gift I could have possibly ever got! You've done so much for me already, saved my life twice over, and yet you never cease to surprise me! Thank you, my love!";
			link.l1 = "Could not have been any other way, Mary. I will continue to surprise you every day, till my last breath! Your smile brings me joy and I am glad you like the gift.";
			link.l1.go = "narval_10";
		break;
		
		case "narval_10":
			dialog.text = "(giggles) Thank you! Such a wonderful blade, alright! It needs a strong hand to wield it... I can't wait to start training with it!";
			link.l1 = "I do not see a problem. Hurry to your cabin and try your new broadsword!";
			link.l1.go = "narval_11";
		break;
		
		case "narval_11":
			dialog.text = "That is what I am going to do. Thank you again, gentleman! "+pchar.name+"... Come and see me tonight, when you are ready... (giggles)";
			link.l1 = "Of course, milady. I will see you in the evening.";
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
			dialog.text = "Here, take a look. I have found it in one of the ships in the outer ring inside a captain's chest. Every experienced sailor says that this item is extremely valuable for a navigator, it can protect a ship from the worst storms. Some of them were even eager to buy it, but I haven't sold it... I want you to have this amulet, darling. Use it to keep you safe in the sea.";
			link.l1 = "Thank you, Mary! Very thoughful of you, I love you!";
			link.l1.go = "talisman_1";
		break;
		
		case "talisman_1":
			GiveItem2Character(pchar, "talisman2"); 
			PlaySound("interface\important_item.wav");
			Log_Info("You have received a talisman of 'Jonah'");
			dialog.text = "Really? Do you like it? Oh, that is great! I am so glad, alright!";
			link.l1 = "This is a very rare and valuable talisman. Of course I like it! Thank you, darling!";
			link.l1.go = "talisman_2";
		break;
		
		case "talisman_2":
			DialogExit();
			DeleteAttribute(npchar, "quest.talisman");
		break;
		
	// --------------------------------------вернулся на Остров---------------------------------------------
		case "return":
			dialog.text = ""+pchar.name+"... You are back. I have been waiting for you, I was looking out to the horizon every day, alright! You came back to me...";
			link.l1 = "Yes, Mary. I am here as I promised. Let me hug you, darling!";
			link.l1.go = "return_1";
		break;
		
		case "return_1":
			dialog.text = "Ah, "+pchar.name+"... You can't even imagine how I felt! Narwhals were talking about your death, they said that you drowned. They were all sure you were dead. I kept telling them that you are alive... Of course, nobody believed me, they thought I have gone crazy after all that has happened.";
			link.l1 = "Mary... My dear! What is wrong with you? You are trembling... Are you cold?";
			link.l1.go = "return_2";
		break;
		
		case "return_2":
			dialog.text = "No, I am not cold. I am just... I don't want to talk about it here. Come to my cabin when you are done. I want to stay with you alone, alright... Aren't you going to see the admiral and Nathaniel now?";
			link.l1 = "Yes. I have to talk to Shark and, of course, take Danielle to Nathaniel. It won't take too much time. I will see you soon, Mary.";
			link.l1.go = "return_3";
		break;
		
		case "return_3":
			dialog.text = "I am looking forward to... see you. Come as soon as possible, alright!";
			link.l1 = "...";
			link.l1.go = "return_4";
		break;
		
		case "return_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload62", "CeresSmithy", "goto", "goto11", "LSC_MaryWaitInCabin", 20.0);
		break;
		
		case "adversary":
			dialog.text = ""+pchar.name+"! At last. We have to talk, alright!";
			link.l1 = "What is wrong, Mary? I see that something is troubling you! What happened?";
			link.l1.go = "adversary_1";
		break;
		
		case "adversary_1":
			dialog.text = "She happened... "+pchar.name+", who is that whore on your ship?";
			link.l1 = "Who? Are you talking about Danielle? But you already kn...";
			link.l1.go = "adversary_2";
		break;
		
		case "adversary_2":
			dialog.text = "No, not Danielle. I mean that blonde, barely covered with clothes, who is walking around your ship's deck! I saw her through the spyglass, alright!";
			link.l1 = "A-ah! That is Helen McArthur. She is involved in this odd story just like Danielle is. She is serving as my officer. Temporarily, of course.";
			link.l1.go = "adversary_3";
		break;
		
		case "adversary_3":
			dialog.text = "Officer? She is an officer?!";
			link.l1 = "Well, yes. What is wrong with that?.. Mary, damn it! You are jealous!";
			link.l1.go = "adversary_4";
		break;
		
		case "adversary_4":
			dialog.text = "What did you think?!... (in tears) I had been waiting for you this whole time, I didn't sleep because of you, and you dare come back here with some hag...";
			link.l1 = "Mary! Stop crying! What's wrong with you? You can gut any man without hesitation, and yet your eyes are always wet... Mary, dear, Helen is just an officer, serving temporarily until justice is served, and our common goals are achieved, nothing more.";
			link.l1.go = "adversary_5";
		break;
		
		case "adversary_5":
			if (CheckAttribute(npchar, "quest.blade31")) 
			{
				sTemp = "I have been training hard with the broadsword you gave me, and in your absense I have mastered it perfectly.";
				notification("Heavy Weapons +", "Mary");
			}
			else sTemp = "I have been training hard with rapiers and I have mastered them perfectly.";
			dialog.text = "(sobbing) Officer... Then I also want to be your officer, alright! I can fight, you know that! "+sTemp+" And I shoot well! I may not have any naval skills but I learn fast, I am talented, alright!";
			// проход первый - ГГ либо соглашается, либо нет, отказ ведет к полному разрыву
			link.l1 = "(agree) Mary... I wanted to offer you the position myself. There is no better, more skilled, fiery lass than you! I want you by my side!";
			link.l1.go = "adversary_hire";
			link.l2 = "(deny) Mary! Being a boarding officer is too dangerous! You don't understand what you are asking for. I can't risk your life.";
			link.l2.go = "adversary_fail";
		break;
		
		// отказ
		case "adversary_fail":
			dialog.text = "Can't you? So that blonde whore can be an officer and I can't? You are lying to me, "+pchar.name+", you simply don't want to be with me! (crying) Is that girl better than me, aye?";
			link.l1 = "Mary, you don't understand!";
			link.l1.go = "adversary_fail_1";
		break;
		
		case "adversary_fail_1":
			dialog.text = "I do! I saw her glowing eyes set upon you! She is not just an officer, alright! I understand that (sobbing). Of course, I can't compete with her - she knows how to run a ship...";
			link.l1 = "Mary, what are you talking about!";
			link.l1.go = "adversary_fail_2";
		break;
		
		case "adversary_fail_2":
			dialog.text = "It's over... (crying) Go away! Go away to your whore! And I will stay here... I ain't going anywhere! Give me my key!";
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
				dialog.text = "Really? Did you really want me as your officer? "+pchar.name+", damn it, you can't imagine how happy I am! I want to be your officer so much... but not on the same ship with that blonde!";
				link.l1 = "Mary, but why?!";
				link.l1.go = "adversary_hire_no";
			}
			else
			{
				dialog.text = "Really? Did you really want me as your officer? "+pchar.name+", damn it, you can't imagine how happy I am! I swear, I won't let you down, you'll see!";
				link.l1 = "Jesus, Mary, darling, you are precious. You were crying a minute ago and now your face is lit up! And, Mary, you are not just another officer to me. You are more than that and I doubt you can, in any way, let me down.";
				link.l1.go = "adversary_hire_yes";
			}
		break;
		
		case "adversary_hire_no": // Мэри не пойдёт, пока не ГГ не расстанется с Элен. Выбирай, кто тебе милее...
			dialog.text = "You may only consider her as your officer, though I doubt she only sees you as her captain. I saw the looks she gave you, I know that look, alright! Only I can give you those looks!";
			link.l1 = "Mary, darling, but I have already told you, I do not have feelings for her, and that is it! There is nothing between us! I swear, damn it! I need her help to deal with mess within the Brethren of the Coast. Jan Svenson will not help me to capture Tortuga, if I don't help her, and I need him!";
			link.l1.go = "adversary_hire_no_1";
		break;
		
		case "adversary_hire_no_1":
			dialog.text = ""+pchar.name+", dear, hug me... I'm sorry. I believe you. But I won't be able stay close to her and watch her trying to flirt with you, alright! Eventually I will take my sword and split her in half!";
			link.l1 = "Yeah, you definitely can do that... You've got quite the temper, huh?";
			link.l1.go = "adversary_hire_no_2";
		break;
		
		case "adversary_hire_no_2":
			dialog.text = "And if I kill her - you will leave me, alright... I'd never forgive myself.";
			link.l1 = "So what do you propose, Mary? What should I do with her?";
			link.l1.go = "adversary_hire_no_3";
		break;
		
		case "adversary_hire_no_3":
			dialog.text = "You've said that she is a temporary officer. I will join you as soon as you leave her on land. Stranded on some uninhabited island, I hope (giggles) I will follow you to the end of the world, alright! "+pchar.name+", dear, is she really better than me?";
			link.l1 = "Rubbish! Quit talking like that, Mary, dear, there is no woman better than you!...";
			link.l1.go = "adversary_hire_no_4";
		break;
		
		case "adversary_hire_no_4":
			dialog.text = "Prove it to me then. I don't want to share you, "+pchar.name+"! I'd better be alone than share you with another, alright...";
			link.l1 = "Fine, Mary. Let's make a deal. I can't get rid of Helen now, she is important for this pursuit. I will assist her in her problems, make her a mistress of Isla Tesoro, let her go, and there will be nothing left between us. Hopefully, it does not take longer than a month or two. Will you wait for me that long?";
			link.l1.go = "adversary_hire_no_5";
		break;
		
		case "adversary_hire_no_5":
			dialog.text = "Of course I will, alright! It is my decision... If you return to me, that means you've chosen me instead of her. And if you don't return... it is my fate then. I will stay here and found my own clan. Casper clan...";
			link.l1 = "Crying again? Mary, come on. Enough with that nonsense! What are you talking about? What clan... Silly lass, of course I will return, I wouldn't dare leave you amongst these rotten old ships! You would flood the island with your tears!";
			link.l1.go = "adversary_hire_no_6";
		break;
		
		case "adversary_hire_no_6":
			dialog.text = "Return as soon as possible then... "+pchar.name+", honey, kiss me, please...";
			link.l1 = "I will be back. I promise!"; // ага, а мы посмотрим, обманешь или нет
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
			dialog.text = "Are you messing with me? "+pchar.name+", have you really not forgotten about me?";
			link.l1 = "Of course! Have I ever cheated on you? I've been through a lot during our separation and I have no intention on parting with you again... my talisman.";
			link.l1.go = "adversary_hire_yes";
			DeleteAttribute(pchar, "questTemp.LSC.MaryWait");
		break;
		
		case "adversary_hire_yes": // Элен заведомо не друг - Мэри идёт сразу, либо если выбрал Мэри
			dialog.text = "Really? "+pchar.name+"! I will always follow you! I will never lie to you, I will never betray you, I swear!";
			link.l1 = "I believe you, my dear... Neither will I."; // а куда же ты денешься )
			link.l1.go = "adversary_hire_yes_1";
		break;
		
		case "adversary_hire_yes_1":
			dialog.text = ""+pchar.name+", darling, hug me... We will be together, right? Tell me!";
			link.l1 = "Yes, we will be together, Mary. Forever.";
			link.l1.go = "adversary_hire_yes_2";
		break;
		
		case "adversary_hire_yes_2":
			dialog.text = "Just like Danielle and Nathaniel?";
			link.l1 = "(laughing) Yes, just like them.";
			link.l1.go = "adversary_hire_yes_3";
		break;
		
		case "adversary_hire_yes_3":
			dialog.text = ""+pchar.name+"... I love you! I will marry you if you want, alright...";
			link.l1 = "Dear Mary... Of course - we will talk about it later. Your life on this cemetery of ships is over, let's get you out of here first - welcome aboard my vessel and to the big world, my love!";
			link.l1.go = "adversary_hire_yes_4";
		break;
		
		case "adversary_hire_yes_4":
			dialog.text = "Let's spend our last night on this island together, on 'Ceres Smithy'. Just the two of us. Only you and me... I won't let you go anywhere until the morning comes, alright!";
			link.l1 = "Well, we are not on my ship, so I will follow your command... My dear Mary!";
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
			link.l1 = ""+npchar.name+"? It's not safe here and I have ordered you to stay on the ship...";
			link.l1.go = "sea_bomb_1";
		break;
		
		case "sea_bomb_1":
			dialog.text = ""+pchar.name+", there is so much gunpowder on this old tub, if it explodes, the whole island will fly sky high. It makes no difference where to stay now. Just listen to me!";
			link.l1 = "I am listening, please make it quick.";
			link.l1.go = "sea_bomb_2";
		break;
		
		case "sea_bomb_2":
			dialog.text = "The pirate corvette and the frigate. They are fooled into thinking that we are one of theirs... Knive, alright. This could be an opportunity for us. Let's take a few barrels of gunpowder, a fuse, and sail towards them.\nWhen they let us get closer, we light the fuse, toss the barrel to one of the ships and sail away as fast as we can. Must be a perfect chance to see some fireworks... What do you think?";
			link.l1 = "Risky, though, you plan just might work... Only if they fail to recognize us.";
			link.l1.go = "sea_bomb_3";
		break;
		
		case "sea_bomb_3":
			dialog.text = "Let's risk it, "+pchar.name+"?";
			link.l1 = "Fine. Let's get on with this! Lads! Take three barrels of gunpowder! We are going to get the hell out of here! I love your imagination, "+npchar.name+"... I would have never come to this idea myself.";
			link.l1.go = "sea_bomb_4";
		break;
		
		case "sea_bomb_4":
			dialog.text = "Told you, I have my talents!";
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
			dialog.text = "Yes, sure, darling. I am always ready to help, alright! What is the matter?";
			link.l1 = "Jackman's ship is at Sabo-Matila Cove, the heavy frigate 'Centurion'. This ship was once property of the Hawkes, so there must be important items and documents in Jackman's cabin...we must board it.";
			link.l1.go = "fugas_1";
		break;
		
		case "fugas_1":
			dialog.text = "I see. How are you going to perform that on our little bird? They have more men and cannons. I have looked through the spyglass, alright!";
			link.l1 = "You are right. Jackman has at least twice more men than we do, and all of them are skilled cutthroats and mercenaries. It would be madness to board without the proper preparations. A prolonged battle at sea is not an option either. So I've been thinking of other options to accomplish the task.";
			link.l1.go = "fugas_2";
		break;
		
		case "fugas_2":
			dialog.text = ""+pchar.name+", they haven't recognized us as an enemy yet, just like those idiots back at Turks... We can try our trick again...";
			link.l1 = "Mary, I have just told you that we must board the frigate, sinking her is not an option.";
			link.l1.go = "fugas_3";
		break;
		
		case "fugas_3":
			dialog.text = "I know that, "+pchar.name+". we won't sink her. Listen, we are going to take a few empty rum barrels and fill them with gunpowder, grapeshot, and short fuses. Then we will sail closer to their frigate and throw the improvised explosives onto their deck.";
			link.l1 = "Ha! Do you really think it will work?";
			link.l1.go = "fugas_4";
		break;
		
		case "fugas_4":
			dialog.text = "And why not? Their freeboard is higher than ours but two or three men aided by a pulley could hoist and throw a fully loaded barrel easily. We'll call out - 'Here's some free rum from Knive! And the barrels will explode before they can even react.";
			link.l1 = "The exploding grapeshot will turn his best men on deck into mince... Damn, it sounds tempting.";
			link.l1.go = "fugas_5";
		break;
		
		case "fugas_5":
			dialog.text = "Let's use five barrels. "+pchar.name+", we have the element of surprise. They won't suspect a thing! We must immediately sail away before they board us though.";
			link.l1 = "Well, let's try. They must not identify us before we toss the barrels... Damn it, it won't be easy to get close to them. Jackman is not an idiot like Ghoul was.";
			link.l1.go = "fugas_6";
		break;
		
		case "fugas_6":
			dialog.text = "Let's risk it, "+pchar.name+"! It won't hurt anyway.";
			link.l1 = "Good point, we have nothing to lose... Prepare the fougasses!";
			link.l1.go = "fugas_7";
		break;
		
		case "fugas_7":
			dialog.text = "I will, my captain! I will prepare them perfectly, alright!";
			link.l1 = "Hey, they didn't let you stun those crabs back on the island, so here I am letting you blast some pirate ass here eh... Mary, you are wonderful!";
			link.l1.go = "fugas_8";
		break;
		
		case "fugas_8":
			dialog.text = "Thank you, "+pchar.name+"! I won't let you down!";
			link.l1 = "In that, I have no doubt. I hope we are the ones that don't let you down by fucking up this plan of yours... To arms!";
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
			dialog.text = "There you are! Took some effort to find you... That was amazing, cap! I've never seen such a breathtaking jump before! You are always my hero! Though I admit, you nearly gave me a heart attack\nOne day you will kill me with these tricks of yours, dear... Well now, who the fuck would she be? Oh "+pchar.name+", I let you slip away from me for just a moment, and the next I know, you are surrounded with hordes of slags!";
			link.l1 = "Mary, this 'slag' is Catherine Fox, daughter of colonel Fox, the commander of Sea Foxes. We must take her to Antigua.";
			link.l1.go = "terrapin_grot_1";
		break;
		
		case "terrapin_grot_1":
			dialog.text = "Oh, really? Such delight! Fine, you are going to tell me about her... tonight, when we spend the night together, alone. Now, let's go, we have to hurry!";
			link.l1 = "You are the best, Mary. What would I do without you? Catherine, come on!";
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
			dialog.text = "Finally you are awake, my darling... Bastard! Don't ever scare me like that again!";
			link.l1 = "Mary... dear, what happened? My head is splitting...";
			link.l1.go = "on_coast_1";
		break;
		
		case "on_coast_1":
			dialog.text = "When we entered the captain's cabin, you were lying on the floor still as a corpse. My heart was racing! The guys picked you up, and dragged you to our ship - just in time, because the dead men lying on the deck began to rise again\n What a nightmare! We couldn't do anything about them! We quickly cut the lines and tried to sail away, but a volley from their ship severely damaged our ship and we lost control. They were some real devils, alright! And then they hoisted sails and were gone in the blink of an eye\nOur ship ran aground, so we had to flee to this shore before the storm could destroy her. Many good people died today, but the ship survived in the end...";
			link.l1 = "Good work, Mary... What would I do without you?";
			link.l1.go = "on_coast_2";
		break;
		
		case "on_coast_2":
			dialog.text = "Perhaps you'd have drowned, or you would've stayed on that ship, and the dead would tear you apart... My hands are still shaking!";
			link.l1 = "Thank you, love. How long have I been out?";
			link.l1.go = "on_coast_3";
		break;
		
		case "on_coast_3":
			dialog.text = "For an entire day. I cleaned your wounds, gave you medicine and poured some rum into you. You should get well soon. And don't you dare die on me!";
			link.l1 = "I promise I won't die this time, darling. Though I don't feel too well...";
			link.l1.go = "on_coast_4";
		break;
		
		case "on_coast_4":
			dialog.text = "That's for sure... Was it the 'Flying Dutchman', cap? Why did they attack us? And why didn't they shoot before boarding?";
			link.l1 = "Their captain needed the amulet, the one I talked to Tuttuathapak about, the Indian shaman. That's why they needed to board us, but as soon as their captain took the amulet, they did not need us anymore... What a nightmare! A ship manned by the dead! Unbelievable...";
			link.l1.go = "on_coast_5";
		break;
		
		case "on_coast_5":
			dialog.text = "Yeah, seems the 'Flying Dutchman' would come for us sooner or later. When I have the chance, I'll go to church, light a candle for our miraculous delivery, and pray to our Lord...";
			link.l1 = "Me too, Mary, I guess. I need to go back to that village. Let Tuttuathapak know what happened. That ship attacked us because of the amulet! I hope that red-skinned devil has an explanation as to why the hell those living dead had a need for it in the first place.";
			link.l1.go = "on_coast_6";
		break;
		
		case "on_coast_6":
			dialog.text = "Alright. But be careful - your wounds have barely healed.";
			link.l1 = "You are all the medicine I need. And... Mary, I love you...";
			link.l1.go = "on_coast_7";
		break;
		
		case "on_coast_7":
			dialog.text = "I love you too, my darling...";
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
			dialog.text = RandPhraseSimple(""+pchar.name+", there is no a greater happiness to me than being in your arms, alright... Let's go!",""+pchar.name+", I'd like to be with you every waking moment if it were possible. Let's go!");
			link.l1 = RandPhraseSimple("You are the best, my love...","You are wonderful, my talisman...");
			link.l1.go = "exit";
			AddDialogExitQuest("cabin_sex_go");
		break;
		
		case "sex_after":
			dialog.text = RandPhraseSimple("Dear, you were amazing... you always are!","It was great!");
			link.l1 = RandPhraseSimple("I am glad that you are happy, my love...","I love you Mary...");
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
				dialog.text = ""+pchar.name+", there is no a greater happiness to me than being in your arms, alright... But this is not the best time - we have to catch that scum Thibaut before he runs away.";
				link.l1 = "You are right as always, my girl...";
				link.l1.go = "exit";
				break;
			}
			dialog.text = RandPhraseSimple(""+pchar.name+", there is no greater happiness to me than being in your arms, alright... Let's go!",""+pchar.name+", I'd like to be with you every moment if it were possible. Let's go!");
			link.l1 = RandPhraseSimple("You are the best, my girl...","You are wonderful, my red-haired talisman...");
			link.l1.go = "room_sex_go";
		break;
		
		case "room_sex_go":
			DialogExit();
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
			DoFunctionReloadToLocation(pchar.location+"_upstairs", "quest", "quest4", "GiveKissInRoom");
			ChangeCharacterAddressGroup(npchar, pchar.location+"_upstairs", "quest", "quest3");
			} // patch-8
			//DoQuestCheckDelay("Mary_LoveSex", 2.5);
			NextDiag.CurrentNode = "sex_after";
			npchar.greeting = "mary_hire";
		break;
		
		// требует секса, если давно не давал
		case "givemesex":
			dialog.text = RandPhraseSimple(""+pchar.name+", it's been too long since we had sex... You have completely forgotten about me, alright! Darling, I want to relax, let's get a room for the night and leave our troubles for another day!",""+pchar.name+", you have been too busy and I am starting to think that you have completely forgotten about me! Darling, I want to... stay with you in private. Let's get a room for the night, alright!",""+pchar.name+", have you lost your mind? I want to spend the night together with you, have some wine, and relax. You've been too busy at sea and completely forgot about me!");
			link.l1 = "Mary, dear, what are you talking about - 'completely forgotten about me'? Silly girl... But I really have been too occupied, problems that require my attention are endless. Forgive me, my love. Let's go upstairs, I am all yours for the night, the world can wait!";
			link.l1.go = "room_sex_go";
		// belamour legendary edition -->
			link.l2 = RandPhraseSimple(RandPhraseSimple("Not today, dear. I've got a headache.","Mary, honey, how could I forget about you? Come on, later - we have some work to do..."),RandPhraseSimple("You're always on my mind, Mary, but we can't afford to relax right now.","Mary "+npchar.lastname+", we have no time for nonsense today"));
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
			dialog.text = "Well ... What else can I say ... Aye, captain!";
			link.l1 = "...";
			link.l1.go = "exit";
		}
		else
		{
			if(bImCasual) Log_Info("To refuse Mary become more famous");
			ChangeCharacterComplexReputation(pchar,"authority", -2);
			dialog.text = "Charles...";
			link.l1 = "Mary, dear, what are you talking about - 'completely forgotten about me'? Silly girl... But I really have been busy, those problems are endless. Forgive me, my girl. Let's go upstairs, the world can wait!";
			link.l1.go = "room_sex_go";
		}
		break;
		// <-- legendary edition
		// ругается за то, что ходил по борделям, ГГ изворачивается
		case "brothel":
			dialog.text = "Aye, there he is! You don't like me anymore, do you? Tell me!";
			link.l1 = "What?! Mary, what nonsense are you talking about? Why do you think that?";
			link.l1.go = "brothel_1";
		break;
		
		case "brothel_1":
			dialog.text = "Then why have you been visiting those slags, those brothel whores? I know you did, don't you lie to me! You don't like something in me when we are making love, aye? (crying) Tell me...";
			link.l1 = "Mary, Mary... calm down, please, my girl. Yes, I have been at the brothel a few times but only on business matters. I wasn't looking to have any fun!";
			link.l1.go = "brothel_2";
		break;
		
		case "brothel_2":
			dialog.text = "And what kind of 'business matters' had brought you upstairs to the fuck room? (sobbing) You are lying, "+pchar.name+"!";
			link.l1 = "Mary, dear, stop that at last... I really did have some business matters with the mistress of the brothel.  And I had gone upstairs a few times. Last time on a personal matter of the governor - he asked me to find his wedding ring. How could I refuse His Excellency?";
			link.l1.go = "brothel_3";
		break;
		
		case "brothel_3":
			dialog.text = "";
			link.l1 = "And how could I explain the mistress that I need to look underneath the bed upstairs? I couldn't. So I had to buy a whore for the night to be allowed upstairs... The second time, I was told that a merchant has lost his ship documents there. I had to pay for a girl again, in order to search the room, and I was paid well for the documents...";
			link.l1.go = "brothel_4";
		break;
		
		case "brothel_4":
			dialog.text = "";
			link.l1 = "Third time I was helping the local commandant: I had to ask the whores about an officer from the garrison. That officer was suspected in espionage and connections with pirates. Finally, we caught him and I received a handsome reward...";
			link.l1.go = "brothel_5";
		break;
		
		case "brothel_5":
			dialog.text = "";
			link.l1 = "See now? I am telling you, it was all about business. Mary, you are the one I love and need. You are the best, I swear! Do you really think that I will do some dirty harbour whore, when I have you? How could you even think of me like that!";
			link.l1.go = "brothel_6";
		break;
		
		case "brothel_6":
			dialog.text = ""+pchar.name+"... Is it all true? Are you honest with me? You have not been with them?";
			link.l1 = "Mary, dear, you are the only woman I love, it is true. Come closer, dear. Let me hug you... Wipe your tears and, please, stop being jealous! I will never visit the brothels again, if that is what you want!";
			link.l1.go = "brothel_7";
		break;
		
		case "brothel_7":
			dialog.text = "Aye, that is what I want!... "+pchar.name+", I am jealous because I love you... And I don't want to lose you, alright! You hear me? I will kill any bitch who dares to come an inch too close to you!";
			link.l1 = "Calm down... There is no need to kill anybody. And you won't lose me, I promise. It's all right, calm down. You are my only one and the best girl in the world... Trust me, that you are.";
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
			dialog.text = ""+pchar.name+", what an odd question? I love you. You saved me. I am your red-headed talisman - do you really think that I will let you go there alone? Don't even count on it, alright! I am with you! When shall we go?";
			link.l1 = "You are right, dear, it was an odd question... I will tell you later when we go. We need to prepare ourselves first.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "I am ready, my captain! I will follow you to the back of beyond!";
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
			dialog.text = "What's all the ruckus this time, Captain? Spanish, pirates or worse?";
			link.l1 = "It's worse, Mary, much worse. The governor is intending to pay a visit to an extremely expensive courtesan and I am supposed to accompany him as a person of interest, as promised to the mistress. Boring talks, overpriced wine and dull nobles.";
			link.l1.go = "GoldenGirl_1";
			link.l2 = "Quite the opposite, an burden of an invitation to a social event, run by a noble lady. His Excellency took me by surprise when he asked me to accompany him, but to be honest, I look forward to get my mind off things.";
			link.l2.go = "GoldenGirl_3";
		break;
		
		case "GoldenGirl_1":
			dialog.text = "Is that so?! A courtesan? You sayin' that like it's not a big deal, huh? Just having a bit of fun with His Excellency? Charles, are you fu...";
			link.l1 = "Mary, calm down, please! It's not like I am going there to... it's not a brothel! Well, it is a brothel, but damn me if I am not a nobleman and a man of his word. Do you really not trust me? The governor only asked me for a small favor and I must oblige him, that's all!";
			link.l1.go = "GoldenGirl_2";
		break;
		
		case "GoldenGirl_2":
			dialog.text = "Yeah, I heard of a couple 'noblemen' like that alright. I've seen them in your company too. Courtesanship are a daily need to them! 'High' societies, 'Dignified' entertainment my ass! Even a marriage does not stop them from visiting these... ladies. Damn, I had no idea that you are just like them. We are not even... Screw you, all of you!";
			link.l1 = "Mary, wait! Fuck...";
			link.l1.go = "GoldenGirl_6";
		break;
		
		case "GoldenGirl_3":
			dialog.text = "We earned a vacation alright. You think they can handle seeing a dame dressed in a red coat? Imagine all the whispers in the corners? Someone will surely faint, that'd be fun, right?";
			link.l1 = "Mary, my dear, this is not the kind of party where you take a lady... at least not a lady like you. Well, it is a bit complicated but let me explain...";
			link.l1.go = "GoldenGirl_4";
		break;
		
		case "GoldenGirl_4":
			dialog.text = "Wow, don't bother. Just tell me straight: I am not good enough for those pricks in wigs. A simple girl, for fun, huh? Are you too embarrassed to show yourself with me around? Not good enough for fancy parties, right, honorable monsieur Charles de Maure?";
			link.l1 = "No, not at all. You are amazing and I don't care about the kind of impressions we make on the people around us. The governor is trying to solve his problems with my help, as always. I will be like a valuable trophy in the room. An interesting guest to impress the noble good-for-nothings.";
			link.l1.go = "GoldenGirl_5";
		break;
		
		case "GoldenGirl_5":
			dialog.text = "So I am not good for you then, aye? I see, it's alright, nobles are for nobles, peasants are for simple amusement. Best of luck with your upper class. I'll talk to you when you are back on our humble soil, aye?";
			link.l1 = "Mary, wait! Fuck...";
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
			dialog.text = "Best of luck with your upper class. I'll talk to you when you are back on our humble soil, yes.";
			link.l1 = "Mary oh, come on!";
			link.l1.go = "GoldenGirl_11";
		break;
		
		case "GoldenGirl_11":
			DialogExit();
			NextDiag.CurrentNode = "GoldenGirl_10";
		break;
		
		case "GoldenGirl_12":
			dialog.text = "Look at this, yes! Our lost in high society captain!";
			link.l1 = "...";
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angry1")) link.l1.go = "GoldenGirl_13";
			else link.l1.go = "GoldenGirl_17";
		break;
		
		case "GoldenGirl_13":
			dialog.text = "You disappeared in the whorehouse for the whole day and now people around the town are talking. Charles, give me just one good reason why I should talk to you now instead of say, showing the Narwal up your... belly? You don't care much for me, aye?!";
			link.l1 = "Mary, I'll explain everything, only later. I should get myself prepared and go to a duel. Feel free to kill me if I live through this. Meanwhile, please take care of our new ship, alright? I won her as a prize in a card game last night.";
			link.l1.go = "GoldenGirl_14";
		break;
		
		case "GoldenGirl_14":
			dialog.text = "Forget the ship, you said something about a duel, yes? Locals tell all kinds of bullshit stories that I do not listen to. They say you are meant to fight either the king's son or the fucking Pope himself. Tell me, now, what the fuck is going on?!";
			link.l1 = "This man is a bastard of a very influential nobleman, Count de Levi Vantadur. It was he, who challenged me in the first place, and I must win the duel without harming him, to avoid his father's wrath.";
			link.l1.go = "GoldenGirl_15";
		break;
		
		case "GoldenGirl_15":
			dialog.text = "While I'll be sitting on my ass on the tub your just won? Have you gone mad, Charles?";
			link.l1 = "I am afraid it has to be that way. The governor provided me with a couple of noble officers to be my seconds in order to avoid any confusion afterwards. I cant take you or any of the guys with me for the sake of official integrity of the duel. This is too serious, I am sorry.";
			link.l1.go = "GoldenGirl_16";
		break;
		
		case "GoldenGirl_16":
			dialog.text = "You know what I am gonna do now? I will go to that blasted ship and get properly drunk, aye! Do whatever you like, but if the noble whoreson will fail to kill you, I swear I will do it myself!";
			link.l1 = "Mary, everything will be just fine, trust me. Now, wait... Fuck! Here we go again!";
			link.l1.go = "GoldenGirl_21";
		break;
		
		case "GoldenGirl_17":
			dialog.text = "There he is! We haven't received a single word from you all day! We were worried upon hearing the gossip circulating at the market. They say you've been gambling for ships and women, and even got into a duel with some kind of crowned prince or even the Pope himself! What the fuck is going on?";
			link.l1 = "It's complicated, Mary. It'll take a while to explain. I did manage to win a frigate, though. You'll have to take care of her while I settle my dispute with her previous owner.";
			link.l1.go = "GoldenGirl_18";
		break;
		
		case "GoldenGirl_18":
			dialog.text = "So they were right about the duel, aye? Who is that entitled noble fuck? Why are you fighting him?";
			link.l1 = "I have to. It's complicated, but in short: I won his ship and his... dame. He publicly accused me of cheating and challenged me to a duel. This man is a bastard of a very influential nobleman, Count de Levi Vantadur. I will have to do my best to avoid hurting him.";
			link.l1.go = "GoldenGirl_19";
		break;
		
		case "GoldenGirl_19":
			dialog.text = "A dame? I can understand gambling for a ship, but... a woman, really? They were speaking the truth in the streets, huh? You admit it just like that?! Like I'm... one of your idiot sailors?";
			link.l1 = "Damn it, Mary, it's not like that at all! He won her from the governor, I won her back from him to release her, that's it. There is nothing more to it, I swear!";
			link.l1.go = "GoldenGirl_20";
		break;
		
		case "GoldenGirl_20":
			dialog.text = "Well, maybe it is normal among you nobles, but I am not like that, alright! Do what you like, say what you like... go and die for her if you want! I will go to the fucking ship you won and get wasted. I believed this was real and... would last forever. Guess I expected too much!";
			link.l1 = "Mary, I don't give a damn about that woman! Just wait, please... Fuck! Here we go again...";
			link.l1.go = "GoldenGirl_21";
		break;
		
		case "GoldenGirl_21":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlToFregat", 15.0);
		break;
		
		case "GoldenGirl_24":
			dialog.text = "Charles, you came for me, alright! I knew it, never doubted it! I am so happy to see you!";
			link.l1 = "Me too, Mary! It's been killing me, this whole time. Thank God you are alright!";
			link.l1.go = "GoldenGirl_25";
		break;
		
		case "GoldenGirl_25":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "By the way, what exactly did you do to make them set me free so easily? Without a proper brawl or shooting, alright! Oh, and I saw this beautiful lady on deck when they were dragging me out. What happened, Charles?";
			}
			else
			{
				dialog.text = "What exactly did you do to make them to release me just like that? No fight, no shots fired, alright! I saw some British peacocks on deck when they were bringing me out. What was all that about, Charles?";
			}
			link.l1 = "All that matters is you are back with me. I failed you, Mary. I am so sorry! I hope you can find it in your heart to forgive me! I hate how we last left things between us.";
			link.l1.go = "GoldenGirl_26";
		break;
		
		case "GoldenGirl_26":
			dialog.text = "Already did. I am sorry too, alright! If only I didn't take your dealings with that dame so personally... I would had set a proper watch that night. They would never take us down so easily! It was so stupid of me!";
			link.l1 = "The past is the past. I love you and I will never leave you like that again. I promise!";
			link.l1.go = "GoldenGirl_27";
		break;
		
		case "GoldenGirl_27":
			dialog.text = "I knew you'd never abandon me, alright. Sorry for ever doubting you, Charles! It seems, I best not know what exactly it is you did, aye? We are together again and that is all that matters.";
			link.l1 = "I have no secrets from you. I will tell you...";
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
				dialog.text = "What a story... doubt anyone else would believe it, alright! I knew it from the start! I knew your 'playful' night was funny business! All them noble peacocks... heartless beasts! At least i wasn't wrong about you, I knew you were different, alright!";
				link.l1 = "I am pretty sure a lot of people out there consider me to be far worse. A proper monster out of fairy tales.";
			}
			else
			{
				dialog.text = "What a story... doubt anyone else would believe it, alright! I knew it from the start! I knew your 'playful' night was funny business! Politics, spies, con-spi-ra-cies. And you once again, saved us all, alright! My hero!";
				link.l1 = "Not sure about that. Chances are, war with Britain will start in a few weeks. But I did what had to, Mary. You mean everything to me.";
			}
			link.l1.go = "GoldenGirl_29";
		break;
		
		case "GoldenGirl_29":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "I don't care what people think, if that is the case, you will be my monster, Charles! Others should either go and cry about it or deal with me! Remember that I will always stay by your side, alright!";
			}
			else
			{
				dialog.text = "I know, Charles. I always knew, but it is so nice to hear you say it. Know this - I will always remain by your side, alright!";
			}
			link.l1 = "Never doubted that, Mary. Let's go, boys are worried. Time to set sails and get the hell out of here. You are by my side again, and the horizon won't go anywhere on its own.";
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
			dialog.text = "Charles, is this really you?! I almost lost all hope, alright! God, I missed you so much! Please, please forgive me, aye!";
			link.l1 = "No, forgive me, I didn't see it coming... Thank God you've made it, Mary! I am so happy!";
			link.l1.go = "GoldenGirl_33";
		break;
		
		case "GoldenGirl_33":
			dialog.text = "Speaking of forgiveness - to be completely honest, I am debating whether I should shoot you or hug you. You better tell me what the hell is going on, alright?";
			link.l1 = "I love you, Mary. This is all I wanted to tell you.";
			link.l1.go = "GoldenGirl_34";
		break;
		
		case "GoldenGirl_34":
			dialog.text = "Yeah, as if that was helpful, but... Damn, me too, Charles. I love you too, aye. God, finally, we are together!";
			link.l1 = "And I don't want to spend the time we have talking about things that don't matter. Come with me and I won't dare leave you tonight. Even if the sky starts falling on this miserable town. I will never leave you again. Ever.";
			link.l1.go = "GoldenGirl_35";
		break;
		
		case "GoldenGirl_35":
			dialog.text = "It seems, I best not know what exactly it is you did, aye? We are together again and that is all that matters.";
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
			dialog.text = "Are you saying this... marquise helped you bring me back? And you almost started a war between England and France, aye? Don't get me wrong - this is so romantic and all, but what will happen now? ";
			link.l1 = "I have no idea, Mary. We are together again, the rest is irrelevant. If those in power will fail to sweep it under the rug... well, I am ready to do my duty before the Crown.";
			link.l1.go = "GoldenGirl_37";
		break;
		
		case "GoldenGirl_37":
			dialog.text = "And that marquise of yours? Did you bring her back too? The Portuguese spoke highly of her. He assured me that you withstood her advances like the Bastille castle. I want to believe him, alright, but I must hear it coming from you!";
			link.l1 = "There is nothing going on between madam Botot and me, Mary. I helped her, she helped me, that's all. Speaking of Bartholomew, where is he?";
			link.l1.go = "GoldenGirl_38";
		break;
		
		case "GoldenGirl_38":
			dialog.text = "He is gone, alright. Set sails immediately after he brought me here. I would never go to that blasted whorehouse, so he rented a room for me, paid in advance for a couple of weeks and just left. Oh, I almost forgot, alright! I've got a letter for you!";
			link.l1 = "A letter? From Bartholomew the Portuguese? This is something new. I don't like where this is going...";
			link.l1.go = "GoldenGirl_39";
		break;
		
		case "GoldenGirl_39":
			dialog.text = "Go ahead, read it. I'll go see the boys. They were probably worried. Did everyone make it? Hope you don't mind us having a glass or two downstairs. Don't get yourself into another mess, alright!";
			link.l1 = "Sure thing, but please be careful with them, Mary. I'd rather spend time with you tonight, instead of having to carry drunk bodies back to the ship. God, I still can't believe I got you back!";
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
			dialog.text = "The beach, you, me, and good wine - Charles, that is so romantic! We should do this more often, alright!";
			link.l1 = "Glad you like it. I think we will make more time for each other from now on for occasions like this.";
			link.l1.go = "LongHappy_1";
		break;
		
		case "LongHappy_1":
			dialog.text = "What are you talking about? Something happened to the ship, huh? Why are you on your knees my love?";
			link.l1 = "Because I love you, Mary. You know that, I know that, everybody knows that. So here and now, in face of the sea and the sky, I ask you, Mary Casper - to give me the honor to stand with me before people and God for as many days as we are given from above. I, Charles de Maure, chevalier de Monper, ask you - will you become my wife?";
			link.l1.go = "LongHappy_2";
		break;
		
		case "LongHappy_2":
			if (pchar.location == "Shore36")
			{
				dialog.text = "I dreamed to hear it, alright! I... you know my answer Charles... oh, sorry!";
				link.l1 = "Nevermind, this is just wine and I never loved this shirt...";
				link.l1.go = "LongHappy_3";
			}
			else
			{
				dialog.text = "Charles, of course yes! Yes, yes, a thousand times yes!!! You... this place... nothing can make me happier!!! Oh god, I'm so happy, alright!";
				link.l1 = "You made me happy, Mary. And I want to drink to you, my burning Carib Sun!";
				link.l1.go = "LongHappy_4";
			}
		break;
		
		case "LongHappy_3":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			DoQuestCheckDelay("Mary_LoveSex", 1.0);
			npchar.dialog.currentnode = "LongHappy_5";
			LAi_SetStayType(npchar);
		break;
		
		case "LongHappy_4":
			dialog.text = "Drink to you, my captain and future husband, alright! You are the best that has ever happened to me!";
			link.l1 = "But this is only the beginning - to us! And to our future together! There's so much ahead of us!";
			link.l1.go = "LongHappy_6";
		break;
		
		case "LongHappy_5":
			dialog.text = "Drink to you, my captain and future husband, alright! You are the best that has ever happened to me!";
			link.l1 = "But this is only the beginning - to us! And to our future together! There's so much aheadof us!";
			link.l1.go = "LongHappy_6";
		break;
		
		case "LongHappy_6":
			DialogExit();
			chrDisableReloadToLocation = false;
			npchar.dialog.currentnode = "Mary_officer";
			LongHappy_MarryToSenPierre();
		break;
		
		case "LongHappy_7":
			dialog.text = "Charles, Abbot Benoit in Martinique again, so we can proceed, right? But I will not wear a dress, even for the sake of a church service, I hope you won't be offended?";
			link.l1 = "Mary, I love you in any outfit and ... well, you know. You can wear anything you like, I'll deal with anyone that has a problem with that! But, I just wanted to consult with you about the guests and the ceremony.";
			link.l1.go = "LongHappy_8";
		break;
		
		case "LongHappy_8":
			if (LongHappy_CheckSaga())
			{
				dialog.text = "You know, most of those, who can sincerely rejoice at our happiness, won't even be allowed to enter this city, let alone the church, alright. Therefore - let's get married here with all the important people, as expected, and then we'll sail to Isla Tessoro and properly celebrate with real friends! What do you think, alright?";
				link.l1 = "Great option! So let's do it. I'll talk to Abbot Benoit, but we need to send out invitations and more...";
				link.l1.go = "LongHappy_9";
			}
			else // Сага провалена по времени или утоплен Центурион
			{
				dialog.text = "You know, I don't have many friends except our guys from the crew. So invite those whom you consider necessary, and I will just be happy with what is, alright!";
				link.l1 = "As you say, sweetheart. I'll talk to Abbot Benoit and organize everything, you are worthy of the most magnificent ceremony.";
				link.l1.go = "LongHappy_9a";
			}
		break;
		
		case "LongHappy_9":
			dialog.text = "Don't worry, as a good wife, I will take part of the preparation on myself, alright. I will write to our friends and arrange everything, but first, tell me: how do you see this wedding?";
			link.l1 = "My ideal is you, me and our closest friends. After all the official faces here in Martinique, we will want some sincerity.";
			link.l1.go = "LongHappy_10";
			link.l2 = "We must remember this day. Call everyone! No one will be left out!";
			link.l2.go = "LongHappy_11";
		break;
		
		case "LongHappy_9a":
			dialog.text = "With you, having a ceremony with a ship chaplain on the quarterdeck, under the sunset in the sea, would be enough, alright. But, if this is what you want - we will celebrate! Charles ... I'm going to cry now, hug me, alright ...";
			link.l1 = "Mary...";
			link.l1.go = "LongHappy_9b";
		break;
		
		case "LongHappy_9b":
			dialog.text = "That's it, I'm calm, alright. Sorry, this is all so unusual. But Charles, as a good wife, I will take over the organization. We also need to arrange a party for guys, alright, but it is unlikely that the whole crew will fit in the church. I will make arrangements with the tavern, but we will need booze and money - you know how sailors like to party.";
			link.l1 = "All right, that 's what we 're gonna do. What do I have to prepare?";
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
			dialog.text = "I think, "+sti(pchar.questTemp.LongHappy.MarryMoney)+" pesos will be enough, alright. "+sti(pchar.questTemp.LongHappy.MarryRum)+" barrels of rum, there is nothing worse than be left out of drinks. As soon as you collect everything we need, come to the tavern, I will figure out the rest.";
			link.l1 = "Fine, honey, I'll do it.";
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
			dialog.text = "Got it, let's do it. But we will have to visit Sharptown and prepare everything. I think fifty barrels of rum and a couple dozen barrels of wine will do just fine, alright. But, just in case, I will need three hundred thousand pesos.";
			link.l1 = "That's a lot, but the occasion is worth it. I will scrape it up, don't worry. Now, I'm going to drop by to the abbot and go to Sharptown.";
			link.l1.go = "LongHappy_12";
		break;
		
		case "LongHappy_11":
			pchar.questTemp.LongHappy.BigMarry = "true";
			dialog.text = "Great, we'll get everyone together, alright! But we will have to visit Sharptown and prepare everything - we will need a galleon full of booze!  I think a hundred barrels of rum and fifty barrels of wine will do just fine. But, just in case, I will add five hundred thousand pesos. If the celebration ends quickly, what kind of celebration is that, am I right?";
			link.l1 = "Yes, our friends must not die of thirst -  I will get everything, don't worry! Now, I'm going to drop by to the abbot and go to Sharptown.";
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
			dialog.text = "Everything is ready, Charles, right? I will arrange for the drink to be unloaded, go to the local tavern, meet the baron and hand the invitations. Wait here, alright?";
			link.l1 = "You are at the helm, dear! Then I'll just mess around somewhere. I really didn't think that expeditions to the Maine jungle would be easier to prepare for than a wedding.";
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
			dialog.text = "We are done here, Charles, alright! I arranged everything, believe me - it will be wonderful! One thing is embarrassing: the local tavern burned down during some feast a week ago. But it's almost rebuilt, bigger and better than the old one, alright! We should all be able to fit.";
			link.l1 = "I sure hope we don't burn this one. I really liked the 'Old Woodpecker'! Anyway, we still have a lot to do. It's time to set sail. And yes, Mary - you're the best, you know that, right?";
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
			dialog.text = "So here we go, huh? The guests arrived, the church is ready. I know that we're closer than many spouses, and these are just a few important words in a beautiful hall, but damn me - in that ancient, aboriginal city I was less worried, alright!";
			link.l1 = "It's absolutely normal, my love, absolutely normal. I'm nervous too. I think, father Benoit is already waiting, I'll go to him and find out when the service will begin.";
			link.l1.go = "LongHappy_18";
		break;
		
		case "LongHappy_18":
			dialog.text = "Fine, I'll walk around town for a while, want to get ready, alright! Charles, you do understand that there is no turning back?";
			link.l1 = "Mary, dear, for me, there was no turning back since we've met. I've been waiting for this day with all my heart. Don't worry, everything will be fine.";
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
			link.l1 = "I, Charles Henry de Maure, chevalier de Monper, take you, Mary Casper, to be my wife, to have and to hold, from this day forward, for better and for worse, for richer and for poorer, in sickness and in health, until death do us apart. According to God's Holy Law, in the presence of God, I make this vow.";
			link.l1.go = "LongHappy_27";
		break;
		
		case "LongHappy_27":
			dialog.text = "I, Mary Casper, take you, Charles de Maure, to be my husband, to have and to hold, from this day forward, for better and for worse, for richer and for poorer, in sickness and in health, until death do us apart. According to God's Holy Law, in the presence of God, I make this vow.";
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
			dialog.text = "This is unbelievable, alright! I'm... I'm crying, I'm sorry Charles, I will... my nose has turned red, right?";
			link.l1 = "Mary de Maure, my wife, you are beautiful on this day as well as every other day!";
			link.l1.go = "LongHappy_32";
		break;
		
		case "LongHappy_32":
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) dialog.text = "Thank you, Charles, thank you... Everything is so solemn and wonderful! This is the best day of my life, alright!!! Look, how happy everyone is! But, it's time for you to walk around the guests and accept congratulations! When you're done - come back - let's check on the guys at the tavern.";
			else dialog.text = "Thank you, Charles, thank you... Everything is so solemn and wonderful! This is the best day of my life, alright!!! Look, how happy everyone is! But, it's time for you to walk around the guests and accept congratulations! When you're done, come back, we are excpected in Sharptown.";
			link.l1 = "I'll do so right away, sweetheart. One kiss and I go!";
			link.l1.go = "LongHappy_33";
		break;
		
		case "LongHappy_33":
			DialogExit();
			LongHappy_MarryKiss();
		break;
		
		case "LongHappy_34":
			dialog.text = "Charles, my love, have you already talked to the guests?";
			link.l1 = "Not yet, be patient, sweetheart, I'll be back soon.";
			link.l1.go = "LongHappy_34_1";
			link.l2 = "Yes, I've never listened to so many congratulations at once. And you know what - most of them spoke sincerely!";
			link.l2.go = "LongHappy_35";
		break;
		
		case "LongHappy_34_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_34";
		break;
		
		case "LongHappy_35":
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) 
			{
				dialog.text = "Yes, Yes! They also told me so many pleasant things! Not everyone, of course, some people are clearly surprised by my outfit, alright! But I am so happy, that half the things people say just pass by me. And in general, everyone is so cute. Charles, guys in the tavern are already expecting us - will should go to them. They will be happy to congratulate their captain, alright!";
				link.l1 = "We are going right now. But I would like to end this day in a more romantic place than the room in the port tavern. I hope, my wife, you don't mind spending this night in our cabin? Moreover, now there is no watch on a ship...";
			}
			else
			{
				dialog.text = "Yes, Yes! They also told me so many pleasant things! Not everyone, of course, some people are clearly surprised by my outfit, alright! But I am so happy, that half the things people say just pass by me. And in general, everyone is so cute. Charles! But we are expected in Sharptown, when do we set sail?";
				link.l1 = "Right now. We can't allow our guests to drink all the supplies! I hope, my wife, that you don't mind spending this night in our cabin?";
			}
			link.l1.go = "LongHappy_36";
		break;
		
		case "LongHappy_36":
			dialog.text = "Even in a hut on a desert island, but only with you, of course!";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) link.l1 = "I know. I love you too. Let's go, before the boys drink all our rum and set the tavern on fire.";
			else link.l1 = "I do. I love you too. Then - let's set sail!";
			link.l1.go = "LongHappy_37";
		break;
		
		case "LongHappy_37":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_38";
			LongHappy_MarryComplete();
		break;
		
		case "LongHappy_38":
			dialog.text = "Oh my dear, I'm so happy! Today is a wonderful day...";
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
			dialog.text = "I'm fine, alright! How is Nathan, is he alive?";
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
			dialog.text = "Faster, dear, do not waste time!";
			link.l1 = "";
			link.l1.go = "LongHappy_43_1";
		break;
		
		case "LongHappy_43_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_43";
		break;
		
		case "LongHappy_44":
			dialog.text = "We won, alright! Forgive me, I'm late. We were stuck upstairs, there was a dozen of these bastards, so I was a bit busy!";
			link.l1 = "It's fine, I handled it. I'm happy I was able to finish that story with Jacques... finally. He's got what he deserved.";
			link.l1.go = "LongHappy_45";
		break;
		
		case "LongHappy_45":
			dialog.text = "Then finish here and go back to Sharptown! We should check on Nathan, alright! He risked his life for us!";
			link.l1 = "You're right, my love. Go, I'm right behind you.";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner")) link.l1.go = "LongHappy_46";
			else link.l1.go = "LongHappy_48";
		break;
		
		case "LongHappy_46":
			dialog.text = "By the way, honey, we found Marcus, alright! He was in the cargo hold, bound and unconscious.";
			link.l1 = "He's alive?";
			link.l1.go = "LongHappy_47";
		break;
		
		case "LongHappy_47":
			dialog.text = "He is wounded, but he will be alright. You can't break our baron, alright! He's just woken up and is already eager for battle.";
			link.l1 = "This is our good old Marcus! Well, finish here and to the shore.";
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
				dialog.text = "I'm so sorry, Charles, alright, I... I went for a walk. I saw that you were back, I heard that everyone was alive with a victory, but I... But what's wrong with me, alright!";
				link.l1 = "All is going to be alright, love, all is going to be alright. I'm sad too. But we won, and Jacques Barbazon paid for everything he's done.";
				link.l1.go = "LongHappy_50";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
				{
					dialog.text = "I feel so bad about Gino, Charles, alright! When I found out, I didn't believe it! How are you?";
					link.l1 = "I can't believe it too... it turned out so stupid, I didn't imagine this day like that.";
				}
				else
				{
					dialog.text = "We won again, alright! My husband is a storm for rebellious barons of the Brethren of the Coast! Friends are alive and enemies are dead - a glorious gift, alright!";
					link.l1 = "Yeah, such a celebration, but we made it, my love. We made it.";
				}
				link.l1.go = "LongHappy_50";
			}
		break;
		
		case "LongHappy_50":
			dialog.text = "You barely stand on your feet, alright! Come on, Dannie found us a house here on the outskirts, I don't want to return to the ship now. We'll sit and drink to our fallen friends. This all is too much on a sober head, alright.";
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
				dialog.text = "I feel so bad about Gino, Charles, alright! When I found out, I couldn't believe it! How are you?";
				link.l1 = "I can't believe it too... it turned out so stupid, I didn't imagine this day like that.";
			}
			else
			{
				dialog.text = "Sorry that I'm late, my dear, alright! I went for a walk, then I saw how you approached and ran as fast as I could! Dannielle put me out when Gino said 'the danger is over', alright! I'm so glad that everything is fine now!";
				link.l1 = "Me too, darling. And we won. Barbazon is dead, barons are gathering what's left of their crews. The fight is over.";
			}
			link.l1.go = "LongHappy_53";
		break;
		
		case "LongHappy_53":
			dialog.text = "Charles, I see you barely standing on your feet, but no one can find Tichingitu.";
			link.l1 = "Jan gave me some kind of tip... It seems to me that our harsh maskogue went on the razzle-dazzle. Let's take a walk to Sabo-Matila Cove, a few people saw him leaving in that direction.";
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
			dialog.text = "Well, that's our stern native, alright! Come on, Dannie found us a house here on the outskirts - you are sleepwalking at this point, Charles, alright!";
			link.l1 = "There it is ... kidnap me, my beautiful squaw. And let it all seem like a bad dream tomorrow.";
			link.l1.go = "LongHappy_56";
		break;
		
		case "LongHappy_56":
			DialogExit();
			DoQuestCheckDelay("LongHappy_MarryFinalizing", 0.5);
		break;
		
		case "LongHappy_57":
			dialog.text = "Don't get me wrong, my husband, in the church everything was just luxurious, but here the atmosphere is clearly more soulful, alright! Well, that's all, Charles, now that all the troubles are behind us, we can relax.";
			link.l1 = "Well, it's not quite 'all', my wife - our life goes on together! It can generally be said  that it just has begun today. So, let's go, have a drink with our guys, and then - well, you remember: the cabin, the wine, and us...";
			link.l1.go = "LongHappy_58";
		break;
		
		case "LongHappy_58":
			DialogExit(); // телепорт в каюту
			DoQuestReloadToLocation("My_Cabin", "rld", "loc1", "LongHappy_InSPcabin");
		break;
		
		case "LongHappy_59":
			dialog.text = "My husband... It sounds so sweet, alright! Now you are mine, forever!";
			link.l1 = "I've been yours for a long time already, and will be forever, my love...";
			link.l1.go = "LongHappy_60";
		break;
		
		case "LongHappy_60":
			DialogExit();
			DoQuestCheckDelay("Mary_LoveSex", 1.0);
			npchar.dialog.currentnode = "LongHappy_61";
			LAi_SetStayType(npchar);
		break;
		
		case "LongHappy_61":
			dialog.text = "I am so happy, Charles! And now, we have to keep moving again, right?";
			link.l1 = "Sure, sweetheart! Side by side, together and forever!";
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
			dialog.text = "I'm afraid this pandemic is taking its toll on your girls, Rodrigo. Keep them busy with knitting or something!";
			link.l1 = "This conversation is clearly going nowhere. We agreed that we will go to church tomorrow. To pray... of course.";
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
			dialog.text = "Well, Charles...";
			link.l1 = "What's on your mind again, Mary?";
			link.l1.go = "IslaMona_5";
		break;
		
		case "IslaMona_5":
			dialog.text = "(laughs) The fact that me and Alan, wanted to do the same thing on the island as you have done here";
			link.l1 = "Your... Alan?";
			link.l1.go = "IslaMona_6";
		break;
		
		case "IslaMona_6":
			dialog.text = "Yes, one hell of a dreamer he was, the two of you could be great friends if he were alive!";
			link.l1 = "Well, our tastes crossed paths on one thing for sure!";
			link.l1.go = "IslaMona_7";
		break;
		
		case "IslaMona_7":
			dialog.text = "What? Ha-ha-ha! Stop it Charles!\nEither way, this is amazing, we have given these people so much joy!";
			link.l1 = "We gave them a chance at happiness, but the rest, they have done on their own. So, what are you thinking?";
			link.l1.go = "IslaMona_8";
		break;
		
		case "IslaMona_8":
			dialog.text = "Come find me later and you will find out...";
			link.l1 = "Hell yeah I will!";
			link.l1.go = "IslaMona_9";
		break;
		
		case "IslaMona_9":
			DialogExit();
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			DoQuestFunctionDelay("IslaMona_ChurchReloadToRoom", 0.5);
			ChangeCharacterAddressGroup(npchar, "IslaMona_TwoFloorRoom", "goto", "goto4");
			DoQuestCheckDelay("Mary_LoveSex", 2.0);
			NextDiag.CurrentNode = "sex_after";
			npchar.greeting = "mary_hire";
			pchar.questTemp.IslaMona.Doorlock = "true";
		break;
		
		case "tonzag_jailed":
			dialog.text = "I like darkness and tight spaces. It makes me feel calm. Finally, I can gather my thoughts\nIt's as if all worries and troubles... are gone, yes! I really miss this feeling...";
			link.l1 = "You need to see a doctor.";
			link.l1.go = "tonzag_jailed_1";
			link.l2 = "Right. It's as if you're back on 'Ceres Smithy'.";
			link.l2.go = "tonzag_jailed_2";
			locCameraFromToPos(-15.50, 2.28, -1.23, true, -27.00, -10.60, -22.70);
		break;

		case "tonzag_jailed_1":
			dialog.text = "...Too bad I'm not alone. In silence, in darkness, and in solitude, aye. That would be perfect.";
			link.l1 = "Keep it up, Mary Casper.";
			link.l1.go = "exit";
		break;

		case "tonzag_jailed_2":
			dialog.text = "One time a crab crawled into my bed -I cut it up, and ate it. Aye.";
			link.l1 = "Keep it up, Mary Casper.";
			link.l1.go = "exit";
		break;
		
		case "tonzag_aftershot":
			dialog.text = "Masked asshole! Ouch! Help me my dear - we need to break the bars!";
			link.l1 = "Quiet! I'm trying to figure out what to do!";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Mary_officer";
			AddDialogExitQuestFunction("Tonzag_TichingituAfterShot");
		break;
		
		case "tonzag_after_boarding":
			dialog.text = "Darling, these masked devils are everywhere! They made a huge breach in the hull and are crawling through it like those crabs! We gotta to cut them all down, aye!";
			link.l1 = "Mary, stay here, find the senior officer, and take command! Take the ship out of the battle; we won't withstand another boarding!";
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
			dialog.text = "Victory, aye! Come to me, dear! I want you for an hour or two!";
			link.l1 = "Uh...";
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
			link.l1 = "Mary, Mary, wait! I need your report!";
			link.l1.go = "tonzag_after_victory_3";
		break;

		case "tonzag_after_victory_3":
			dialog.text = "Huh? Well, we won, aye! That damn ship fled. I split one bastard's skull in two!\nPhew, damn buttons!";
			link.l1 = "Oh, Mary...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ShowFrame");
		break;
		
		case "tonzag_dead":
			dialog.text = "Oh God, don't look at me, dear! I'm gonna... phew!";
			link.l1 = "Hang in there, girl. I'm here!";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Mary_officer";
		break;

		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Mary_officer":
			// если шлялся по борделям - устроит небольшой скандал 
			if (sti(pchar.GenQuest.BrothelCount) >= 3 && LAi_grp_playeralarm == 0)
			{
				dialog.Text = ""+pchar.name+"! I need to talk with you, alright! Seriously!";
				Link.l1 = "What happened, Mary? Is there a problem?";
				Link.l1.go = "brothel";
				break;
			}
			ref rLoc = &Locations[FindLocation(pchar.location)];
			dialog.text = LinkRandPhrase("I am listening, my dear captain!","Yes, "+pchar.name+", I am all ears!","Do you have any assignment for me, "+pchar.name+"?");
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Mary, I am going to visit the old Indian city Tayasal. I won't lie to you: this trip is very dangerous and more - it includes teleportation through the idol I told you about. Will you... follow me?";
				Link.l4.go = "tieyasal";
			}
			////////////////////////казначей///////////////////////////////////////////////////////////
			// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Mary, give me a full ship report.";
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
				Link.l2 = RandPhraseSimple("Dear, I want you right now. Are you alright with that?","Mary, how about we... stay together for a while? Just the two of us.");
				Link.l2.go = "cabin_sex";
			}
			if (rLoc.type == "tavern" && !CheckAttribute(npchar, "quest.daily_sex") && sti(pchar.money) >= 10)
			{
				Link.l2 = RandPhraseSimple("Mary, let's rent a room and stay together?","Love, I want to stay with you in private... how about we rent a room and forget about everything for a few hours?");
				Link.l2.go = "room_sex";
			}
			link.l9 = "It's nothing so far, Mary.";
			link.l9.go = "exit";
			NextDiag.TempNode = "Mary_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Charles, she's a beauty, alright! We fixed that teeny-tiny hole below the waterline and dried the sails. Wha- What did you expect? Don't look at me like that, I've never studied to be a purser.";
			Link.l1 = "Sorry, Mary, I really didn't think it through.";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "Charles, but I am all good! I already got my wardrobe and my blade. But thanks for asking, it's so nice of you, alright!";
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
            dialog.Text = "At once, my captain!";
            Link.l1 = "...";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "At once, my captain!";
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

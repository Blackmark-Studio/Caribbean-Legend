// Оле Кристиансен - Белый Мальчик
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "What do you want?";
			link.l1 = "Nothing.";
			NextDiag.TempNode = "First time";
		break;
		
		// в магазине - первая встреча
		case "store":
			dialog.text = "Oops... Hello, uncle. Do you have a white bead? Give me the white bead...";
			link.l1 = "Hm. Good day. Are you... the White Boy?";
			link.l1.go = "store_1";
		break;
		
		case "store_1":
			dialog.text = "Bead! White bead for the white boy! Do you have a white bead, uncle?";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "Hm, I don't have any beads, but I can give you this pearl. It's white and just like a bead. Are you alright with that?";
				link.l1.go = "store_2";
			}
			link.l2 = "No, I don't have any beads, neither white nor red. I'm not a girl or an Indian to wear beads. Tell me...";
			link.l2.go = "pearl";
			sld = characterFromId("Axel");
			sld.quest.ole_pearl = "true";
		break;
		
		case "pearl":
			dialog.text = "Bead! White bead! No bead, no talk. Bad uncle... Give me a bead!";
			link.l1 = "Damn! What a madman! Snake Eye and Chimiset were right – he's soft in the head... What kind of bead does he need?";
			link.l1.go = "exit";
			NextDiag.TempNode = "pearl_repeat";
		break;
		
		case "pearl_repeat":
			dialog.text = "Give me a bead, uncle. Good uncle... A white bead!";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "Here, take your bead. Is that what you want?";
				link.l1.go = "store_2";
			}
			link.l2 = "Oh, damn it...";
			link.l2.go = "exit";
			NextDiag.TempNode = "pearl_repeat";
		break;
		
		case "store_2":
			RemoveItems(pchar, "jewelry52", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Yes, yes! It is! Uncle gave me a bead! Thank you, good man! Now Ole has one more bead. Soon I will see mama...";
			link.l1 = "I am glad for you. Well, can we talk now?";
			link.l1.go = "store_3";
			sld = characterFromId("Axel");
			DeleteAttribute(sld, "quest.ole_pearl");
		break;
		
		case "store_3":
			dialog.text = "Sure, good man. Are you a good man, uncle? We will be friends. Ole will be glad to talk. What is your name?";
			link.l1 = "My name is "+pchar.name+". Ole, a man once told me about you, but he is no longer here. He said you had helped him, and that you could help me.";
			link.l1.go = "store_4";
		break;
		
		case "store_4":
			dialog.text = "Uncle gave a bead to Ole - he is a good uncle. Ole likes to help good people. There are not many good people - bad uncles are all around. I will help you, for sure. I like to help.";
			link.l1 = "Nice! Well, we are friends now. Ole, tell me, do you remember a man with red skin and a gorgeous feathered hat? He told me that you saved him a long time ago.";
			link.l1.go = "store_5";
		break;
		
		case "store_5":
			dialog.text = "I remember that uncle. He is a good man. I saved him. I brought him to the statue. And recently I saved another good man from the cargo hold with food. I saved him from the bad admiral's uncles. They would have killed him. I wanted to take him to the statue too, but he refused. Completely.";
			link.l1 = "From the cargo hold? Heh, I suppose I know who you mean... And I know this uncle. Tell me, Ole, who is that man you have saved?";
			link.l1.go = "store_6";
		break;
		
		case "store_6":
			dialog.text = "His name is Uncle Nathan. He is ill, very, very ill. He could barely walk when Ole found him.";
			link.l1 = "Sure... It is strange that he could even do it.";
			link.l1.go = "store_7";
		break;
		
		case "store_7":
			dialog.text = "No, it's not strange. I found him and gave him some fire rum. I swam inside the hole because there is food on that ship. Bad men lock the door, but I always open it. He-he-he... Silly bad men. They lure crabs, I know that. Bad men I got there and found Nathan. He wasn't feeling well. I had fire rum - I gave it to him to drink, so he got better. Then I gave him the tincture, I always carry one of those, in case a scary crab bites Ole. Good uncle Chimiset told me to do so...";
			link.l1 = "Did you give him the antidote and rum? Heh, you’re not as much of a fool as they all think. Well done, Ole.";
			link.l1.go = "store_8";
		break;
		
		case "store_8":
			dialog.text = "Evil uncles think Ole is a fool and they tease him: Ole the fool... Ole is not a fool, he just needs to collect all the white beads or his mother will send him away. Will you give me another bead later?";
			link.l1 = "Hm... Sure, Ole, we are friends. Tell me, how were you going to send Hawk... Uncle Nathan to the statue? Uncle Chimiset told me that it was sunk with the ship...";
			link.l1.go = "store_9";
		break;
		
		case "store_9":
			dialog.text = "The statue is at the bottom. Ole knows. But it is not deep, and good uncle Henrik can send uncle Nathan there. Uncle Henrik knows how to walk underwater. But there are a lot of scary crabs. Ole is afraid of them. They bite painfully.";
			link.l1 = "Uncle Henrik? Who is he?";
			link.l1.go = "store_10";
		break;
		
		case "store_10":
			dialog.text = "Uncle Henrik lives among the wicked Narwhal uncles. Everybody knows him. He can walk underwater, and he teaches the Narwhal uncles how to dive there. Uncle Henrik is kind; he gave a white bead to Ole.";
			link.l1 = "And how do the Narwhals let you in? Or is their territory open to you?";
			link.l1.go = "store_11";
		break;
		
		case "store_11":
			dialog.text = "Tee-hee... Evil uncles don't let Ole come in, but Ole can enter any room on their ships at night. They are big and noisy, but Ole is silent and careful. And I met uncle Henrik while swimming around the ship that uncle Henrik uses to dive from. Uncle Henrik gave a white bead to Ole and we are friends now.";
			link.l1 = "Interesting... I also want to be friends with uncle Henrik.";
			link.l1.go = "store_12";
		break;
		
		case "store_12":
			dialog.text = "You want to dive down to the statue? It's there, in the wreck of the old ship. There are a lot of big, scary crabs. Aren't you afraid of them? They can bite.";
			link.l1 = "No, I don't fear them. I've already killed one, so they'd better be afraid of me.";
			link.l1.go = "store_13";
		break;
		
		case "store_13":
			dialog.text = "Oh, "+pchar.name+" is very brave! Then you should go to Uncle Henrik, he will teach you how to walk on the bottom and you will kill every crab there. You will also find one more big bead for Ole there. Right?";
			link.l1 = "Sure, I will. But I need to find Uncle Henrik first.";
			link.l1.go = "store_14";
		break;
		
		case "store_14":
			dialog.text = "And why do you want to find him? He lives on the ship called 'San Gabriel', in the workshop. But the wicked Narwhal uncles may not welcome you.";
			link.l1 = "I will deal with the evil uncles myself. And one last question, where is Uncle Nathan now? I have been looking for him, and he is the reason I am here.";
			link.l1.go = "store_15";
		break;
		
		case "store_15":
			dialog.text = "I hid Uncle Nathan in my sanctuary on the 'Fernanda'. It is far away and no one lives there. Everybody thinks that it will sink soon, but Ole knows otherwise. I saved Uncle Nathan and brought him there\nHe is still very ill and drinks fire rum all the time. He can barely walk and is unable to lift anything heavier than five pounds. I feel bad for Uncle Nathan, I bring him fire rum from chests and food from the hold of the admiral's bad men. I also cook him rats I catch. Very tasty rats!";
			link.l1 = "Tasty rats? I see. So is Nathan on the ship called... what did you say - the 'Fernanda'? I don't know her...";
			link.l1.go = "store_16";
		break;
		
		case "store_16":
			dialog.text = "Uncle "+pchar.name+", I have just told you that it is not far from here. You have to swim to reach her. There is a door at her rear, but uncle Nathan doesn't open it. Ole told him not to. But if you are a friend of uncle Nathan, I will tell you how to open it. Knock on the door like this: knock-knock... knock-knock. He will open it then.";
			link.l1 = "I will remember that. Thank you, Ole! You've really helped me out! I don't know how to thank you properly.";
			link.l1.go = "store_17";
		break;
		
		case "store_17":
			dialog.text = "Bring me one more white bead. If you find it, of course.";
			link.l1 = "Ah, yes! White beads! Good. See you, Ole!";
			link.l1.go = "store_18";
		break;
		
		case "store_18":
			DialogExit();
			LAi_SetLoginTime(npchar, 12.0, 21.99);
			LAi_SetCitizenType(npchar);
			LAi_group_MoveCharacter(npchar, "LSC_CITIZEN");
			sld = characterFromId("Nathaniel");
			sld.dialog.currentnode = "diffindoor";
			sld.greeting = "Nathaniel_ill"; // ноду и вякалку Натану
			pchar.questTemp.LSC.DiffIndoor = "true"; //атрибут прохода к Натану
			pchar.questTemp.LSC = "mechanic"; // флаг на разговор с Механиком
			NextDiag.CurrentNode = "ole";
			AddQuestRecord("LSC", "6");
		break;
		
		case "ole":
			dialog.text = "Ah, uncle "+pchar.name+"! Glad to see you! How are you?";
			link.l1 = "Thanks, Ole, I'm fine. I'm glad to see you too.";
			link.l1.go = "exit";
			link.l2 = "Listen, Ole, you said that the admiral's pirates close the door to the cargo hold and you always open it... All the chests there are locked, and you said you take rum for Uncle Nathan from them. How do you manage that?";
			link.l2.go = "lock";
			NextDiag.TempNode = "ole";
		break;
		
		case "lock":
			dialog.text = "Ole has a set of fine keys. They open any door or chest. Well, not all of them. Some can't be opened, but most of them can. Ole found them in the evil uncle Jurgen's cabin. He works with his hammer every day near his oven. He makes locks and keys. And he also makes big and scary muskets for the evil Narwhals.";
			link.l1 = "I see. Ole, can you sell me those keys? I can pay for them...";
			link.l1.go = "lock_1";
		break;
		
		case "lock_1":
			dialog.text = "Fine, uncle "+pchar.name+", I will sell you the keys. I'll just keep the one for myself. It opens the admiral's room. There's plenty of food and rum for Uncle Nathan. There are no more beads or rum left in the chests anyway.";
			link.l1 = "How much do you want for them?";
			link.l1.go = "lock_2";
		break;
		
		case "lock_2":
			dialog.text = "First, tell me, uncle "+pchar.name+", do you have a large ship?";
			link.l1 = "Yes, I have. But she is not here, she is at the outer ring. But I will leave the island soon and I will come back here on my big ship for Uncle Nathan.";
			link.l1.go = "lock_3";
		break;
		
		case "lock_3":
			dialog.text = "For uncle Nathan? Oh, that's wonderful! Listen, promise me you'll take me away from here on your big ship and let me sail with you for as long as I need. I can be useful. I can catch and cook rats... Also, give me five white beads. And I'll give you the keys.";
			if (GetCharacterItem(pchar, "jewelry52") >= 5)
			{
				link.l1 = "Sure! Here are your beads. Take them.";
				link.l1.go = "lock_4";
			}
			link.l2 = "To catch and cook rats? Heh! An interesting skill. Sure, Ole, we have a deal. I will bring you five beads and my word.";
			link.l2.go = "exit";
			NextDiag.TempNode = "ole_1";
		break;
		
		case "ole_1":
			dialog.text = "Ah, uncle "+pchar.name+"! Glad to see you! How are you?";
			link.l1 = "Thanks, Ole, I'm fine. I'm glad to see you too.";
			link.l1.go = "exit";
			if (GetCharacterItem(pchar, "jewelry52") >= 5)
			{
				link.l2 = "I have brought you five white beads for your keys.";
				link.l2.go = "lock_4";
			}
			NextDiag.TempNode = "ole_1";
		break;
		
		case "lock_4":
			RemoveItems(pchar, "jewelry52", 5);
			PlaySound("interface\important_item.wav");
			dialog.text = "Beads! White beads! Uncle "+pchar.name+"  has given beads to Ole! Soon I will see you, Mum!... Uncle "+pchar.name+", do you promise that you will take me from here when you come back?";
			link.l1 = "I do, Ole. I haven't eaten rats yet. I'll take you with me.";
			link.l1.go = "lock_5";
		break;
		
		case "lock_5":
			GiveItem2Character(pchar, "keys_skel");
			AddCharacterExpToSkill(pchar, "Sneak", 200);
			dialog.text = "Thank you, thank you, dear uncle "+pchar.name+"! Take your keys. They are easy to use, just insert them one by one and try. One of them will eventually open the lock you need. If it doesn't, then the lock is too tricky and you will definitely need a special key.";
			link.l1 = "I see. I suppose I will handle it.";
			link.l1.go = "lock_6";
		break;
		
		case "lock_6":
			dialog.text = "Wait, uncle "+pchar.name+"! I have got another key. It's quite pretty and clever. Evil uncle Jurgen doesn't make keys like this one. I don't know what it opens, but perhaps you'll find out. Look, it's a very pretty key, you surely haven't seen anything like it before.";
			link.l1 = "Show me... Yes, the key is very interesting. But what's the use of it if you don't know what it opens?";
			link.l1.go = "lock_7";
		break;
		
		case "lock_7":
			dialog.text = "Uncle "+pchar.name+", , you are very strange. What's the use? If there is a key, then somewhere there is a lock. If there is a lock, then somewhere there is a coin. I found the key on the island. That means the lock is here too. No doubt about it. It's a clever key, and only very valuable items are locked with such a key. Ole knows.";
			link.l1 = "To be honest, you are funny, Ole. Fine, I'll buy it. Do you want beads for it?";
			link.l1.go = "lock_8";
		break;
		
		case "lock_8":
			dialog.text = "Yes, Ole wants five beads. Will you give them, uncle "+pchar.name+"?";
			if (GetCharacterItem(pchar, "jewelry52") >= 5)
			{
				link.l1 = "Here, take your beads.";
				link.l1.go = "key";
			}
			link.l2 = "I don't have them, but I will bring you beads for sure.";
			link.l2.go = "exit";
			NextDiag.TempNode = "ole_2";
		break;
		
		case "key":
			RemoveItems(pchar, "jewelry52", 5);
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "sant_anna_key");
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			dialog.text = "Beads! White beads for the white boy! For his mama! Here, uncle "+pchar.name+", take the key. And you will find the lock, Ole knows. You are brave, you don't even fear fierce crabs.";
			link.l1 = "Oh, don't make me laugh, Ole! Thanks for the key. See you around!";
			link.l1.go = "exit";
			NextDiag.TempNode = "ole_3";
		break;
		
		case "ole_2":
			dialog.text = "Ah, uncle "+pchar.name+"! Glad to see you! How are you?";
			link.l1 = "Thanks, Ole, I'm fine. I'm glad to see you too.";
			link.l1.go = "exit";
			if (GetCharacterItem(pchar, "jewelry52") >= 5)
			{
				link.l2 = "I have brought you five white beads for your key.";
				link.l2.go = "key";
			}
			NextDiag.TempNode = "ole_2";
		break;
		
		case "ole_3":
			dialog.text = "Ah, uncle "+pchar.name+"! Glad to see you! How are you?";
			link.l1 = "Thanks, Ole, I'm fine. I'm glad to see you too.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ole_3";
		break;
		
		case "return":
			dialog.text = "Oh, uncle "+pchar.name+", you are back! You are back on the big ship! Will you take me away from here? Uncle "+pchar.name+", you promised me, remember?";
			link.l1 = "Sure, I do, Ole. Welcome aboard! I suppose the rats are in trouble, ha-ha!";
			link.l1.go = "return_1";
			link.l2 = "Really? And when did I promise you? I don't remember making any promises like that...";
			link.l2.go = "return_3";
		break;
		
		case "return_1":
			dialog.text = "Thanks, uncle! Ole will be useful, you'll see! Oh, perhaps I'll see mum? I'm on my way now!";
			link.l1 = "Don't rush like this, Ole. You can pack your things. I'm not going to set sail immediately.";
			link.l1.go = "return_2";
		break;
		
		case "return_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LSC_SetOlePassenger", 10.0);
		break;
		
		case "return_3":
			dialog.text = "You promised me, you did! You promised to take Ole away from here! Evil uncle! You cheated Ole! Bad uncle!";
			link.l1 = "...";
			link.l1.go = "return_4";
		break;
		
		case "return_4":
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorRunToLocation(npchar, "reload", "reload45", "none", "", "", "", 20.0);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			ChangeCharacterComplexReputation(pchar, "authority", -3);
			if (GetCharacterIndex("Mary") != -1) // Мэри
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
		break;
		
		// Блудный сын
		case "givemepearl":
			dialog.text = "Uncle, uncle... I need one more white bead. Please, give Ole a white bead!";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "I knew you would ask for it. Here, take your bead. Satisfied?";
				link.l1.go = "givemepearl_yes";
			}
			link.l2 = "Oh, and what a pain in the neck... I don't have any more beads, Ole, I don't!";
			link.l2.go = "givemepearl_no";
			DeleteAttribute(npchar, "pearl_date");
		break;
		
		case "givemepearl_yes":
			RemoveItems(pchar, "jewelry52", 1);
			PlaySound("interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			dialog.text = "Thank you! Good, good uncle "+pchar.name+"! Ole has one more bead and there aren't many beads left! And I will go to mum...";
			link.l1 = "Oh, and why are you so strange...";
			link.l1.go = "givemepearl_yes_1";
		break;
		
		case "givemepearl_yes_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5.0);
			SaveCurrentNpcQuestDateParam(npchar, "pearl_date");
			npchar.quest.pearlqty = sti(npchar.quest.pearlqty)+1;
			NextDiag.CurrentNode = "givemepearl_repeat";
		break;
		
		case "givemepearl_repeat":
			dialog.text = "Thank you for the bead, good uncle "+pchar.name+"!";
			link.l1 = "You are welcome...";
			link.l1.go = "exit";
			NextDiag.TempNode = "givemepearl_repeat";
		break;
		
		case "givemepearl_no":
			dialog.text = "No bead? But how can that be, uncle "+pchar.name+"?! Just a few more beads left... I have to collect them. In that case, I'll go ashore. I'll look for beads...";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "And where are you going to go? What will you do alone? No, I don't want to be responsible for your fate. Wait, I will check my pockets... Here! Take your bead and stay with me. Satisfied?";
				link.l1.go = "givemepearl_yes";
			}
			link.l2 = "It is your right, Ole. If you are bored of sailing with me, then I won't stop you. We had a deal. You have been catching those rates fine though...";
			link.l2.go = "givemepearl_no_1";
		break;
		
		case "givemepearl_no_1":
			dialog.text = "Farewell, uncle "+pchar.name+". Ole needs white beads or he'll never return to his mother...";
			link.l1 = "Oh, I am so sorry for you, but what can I do? Go, Ole. Good luck.";
			link.l1.go = "givemepearl_exit";
		break;
		
		case "givemepearl_exit": // Оле уходит - квест не довели до конца
			DialogExit();
			RemovePassenger(Pchar, npchar);
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5.0);
			DeleteAttribute(pchar, "GenQuest.Ole");
		break;
		
		case "mother":
			dialog.text = "Uncle "+pchar.name+"! I need one more white bead. The last one. Please, give it to Ole!";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "I knew you would ask for it. Here, take your bead. Satisfied?";
				link.l1.go = "mother_1";
			}
			link.l2 = "Oh, and what a pain in the neck... I don't have any more beads, Ole, I don't!";
			link.l2.go = "givemepearl_no_1";
		break;
		
		case "mother_1":
			RemoveItems(pchar, "jewelry52", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Thank you, thank you, dear uncle "+pchar.name+"! Now Ole has all the beads. Yes, every single one! Now Ole can bring them to Mum and she won't send Ole away...";
			link.l1 = "Listen, who is that mum you are always talking about? And finally, explain to me why you need those pearls... white beads? And what does it mean - you have them all?";
			link.l1.go = "mother_2";
		break;
		
		case "mother_2":
			dialog.text = "Good uncle "+pchar.name+" has helped Ole to collect beads for his mama... Ole was small when he tore his mama's necklace of white beads. They all fell into the water. Mama was so angry at Ole, and he cannot return home until he collects all of the lost beads\nI remember how many there were. Five times ten beads. Now Ole has them all. Uncle "+pchar.name+", please, take me home! I want to make Mama happy, to return the beads. Take me home!";
			link.l1 = "Jesus, what an incredible story... You made it to the Island as a child. Were you driven away from your home because you broke your mum's pearl necklace? Creepy...";
			link.l1.go = "mother_3";
		break;
		
		case "mother_3":
			dialog.text = "Take me to my mother, good uncle "+pchar.name+". I want to see her. She will be pleased to see the beads.";
			link.l1 = "I'd like to, but do you know where your home is? Where does your mother live?";
			link.l1.go = "mother_4";
		break;
		
		case "mother_4":
			dialog.text = "She lives on the island, in the house with a red roof.";
			link.l1 = "Really! Do you even know how many islands there are here and how many houses have a red roof? What's the name of that island? Give me details...";
			link.l1.go = "mother_5";
		break;
		
		case "mother_5":
			dialog.text = "I don't know its name. I know it was an island, mama was telling father that we were on the island! And we were living in a house with a red roof. Pretty house, a big one. Take me to mom, uncle "+pchar.name+". Please...";
			link.l1 = "Oh, fine. We will search for such a house on every island and we will ask for your mother. What is her name?";
			link.l1.go = "mother_6";
		break;
		
		case "mother_6":
			dialog.text = "Her name? You're so strange, uncle "+pchar.name+". Mother's name is Mother. Is your mother's name different?";
			link.l1 = "Oh, God, please, grant me some patience... Fine, Ole. We will try to find your home. Now go to the ship.";
			link.l1.go = "mother_7";
		break;
		
		case "mother_7":
			dialog.text = "Thank you, uncle "+pchar.name+". You are very, very kind and good! Soon Ole will see Mama!";
			link.l1 = "Oh...";
			link.l1.go = "mother_8";
		break;
		
		case "mother_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5.0);
			DeleteAttribute(npchar, "pearl_date");
			// ставим Агнес Кристиансен и открываем ее дом в Мариго
			LocatorReloadEnterDisable("Marigo_town", "houseSp2", false);
			sld = GetCharacter(NPC_GenerateCharacter("Agnes", "women_18", "woman", "towngirl", 10, HOLLAND, -1, true, "quest"));
			SetFantomParamFromRank(sld, 10, true);
			sld.name = "Agnes";
			sld.lastname = "Christiansen";
			sld.dialog.FileName = "Quest\LSC\OtherNPC.c";
			sld.dialog.currentnode = "agnes";
			//sld.greeting = "";
			LAi_SetOwnerType(sld);
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "Marigo_houseSp2", "barmen", "stay");
			LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
		break;
		
		case "home":
			dialog.text = "Mother... Mother, Mama! I am back!";
			link.l1 = "Son...";
			link.l1.go = "home_1";
		break;
		
		case "home_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			SetMusic("music_romantic");
			bDisableCharacterMenu = true;//лоченые интерфейсы
			locCameraRotateAroundHero(0.0, 2.0, 0.0, 0.005, 0.0, 2.0, 0.0, 1000);
			Pchar.FuncCameraFly = "";
			DoQuestFunctionDelay("LSC_OleReturnHome", 18.0);
		break;
		
		case "home_2":
			dialog.text = "Mama, I have brought you white beads! I have collected them all! You will have a necklace again. Are you still angry with me?";
			link.l1 = "God... (crying) Ole! Son, why? Why did you go away? I don't care about those pearls!";
			link.l1.go = "home_3";
		break;
		
		case "home_3":
			sld = characterFromId("Blaze");
			dialog.text = "Mama, here... take them. I've been collecting them for a long time. Kind uncles have helped me, especially uncle "+sld.name+". He took me on his big ship, helped me collect beads, and brought me home...";
			link.l1 = "Ole... You have really grown up, but you are still a child... Let me hug you, son! I am sorry, please forgive me for that damned necklace! I will never leave you alone, never! We will live together and I will take care of you... I will atone, I promise!...";
			link.l1.go = "home_4";
		break;
		
		case "home_4":
			dialog.text = "Mama, I missed you... I want to stay with you. Are you still angry with me? Why are you crying?";
			link.l1 = "(crying) No, no... I am so sorry, please forgive me, son!...";
			link.l1.go = "home_5";
		break;
		
		case "home_5": // перекидываем pchar
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Agnes");
			sld.dialog.currentnode = "agnes_11";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "final":
			dialog.text = "Uncle "+pchar.name+"! I'm so glad you've come! Thank you for bringing me to my mother. It's wonderful to be here with her... Isn't it great to be home, uncle? "+pchar.name+"?";
			link.l1 = "Yes. Ole. It is. I am glad that you are happy.";
			link.l1.go = "exit";
			NextDiag.TempNode = "final";
		break;
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Listen, you'd better put your weapon away. It makes me nervous.","You know, running around with a blade is not tolerated here. Put it away.","Listen, don't act like a medieval knight running around with a sword. Put it away, it doesn't suit you...");
			link.l1 = LinkRandPhrase("Fine.","Fine.","As you say...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Listen, I am a citizen of this city and I'd ask you to lower your blade.","Listen, I am a citizen of this city and I'd ask you to lower your blade.");
				link.l1 = LinkRandPhrase("Fine.","Fine.","As you say...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Be careful, pal, running around with a weapon. I might get nervous...","I don't like it when men walk in front of me with their weapons drawn. It frightens me...");
				link.l1 = RandPhraseSimple("Got it.","I am taking it away.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

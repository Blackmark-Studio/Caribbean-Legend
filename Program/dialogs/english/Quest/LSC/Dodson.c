// Акула: Стивен Додсон
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			// Jason НСО
			if(CheckAttribute(pchar, "questTemp.Patria.DodsonFail"))
			{
				dialog.text = "Charles, what the hell?";
				link.l1 = "Steven, there was a problem. I could neither come nor inform you about my absence...";
				link.l1.go = "patria_33";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.DodsonAgain"))
			{
				dialog.text = "Good to see you, pal! How can I help you? ";
				link.l1 = "Good to see you too, Steve. I want to thank you for that perfectly conducted spectacle!";
				link.l1.go = "patria_29";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Saga.Shark") && pchar.questTemp.Patria == "epizode_12_pirates")
			{
				dialog.text = "Good to see you, pal! How can I help you?";
				link.l1 = "I have a proposal for you, Steven. A piratical one.";
				link.l1.go = "patria";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Saga.Shark") && pchar.questTemp.Patria == "epizode_12_talk")
			{
				dialog.text = "There's our man! The job is done; your baron is sitting in a well-guarded dungeon. Perhaps you'd like to take a look? He-he!";
				link.l1 = "Ha, plenty of time for that later. Is he being well-treated?";
				link.l1.go = "patria_10";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				dialog.text = "Good to see you, pal! How can I help you?";
				link.l1 = "I need something, Steven...";
				link.l1.go = "tieyasal";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Guardoftruth.Archy") && pchar.questTemp.Guardoftruth.Archy == "islatesoro")
			{
				dialog.text = "Good to see you, pal! How can I help you?";
				link.l1 = "Steven, I've got something for you.";
				link.l1.go = "guardoftruth";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Saga.Shadows") && pchar.questTemp.Saga.Shadows == "islatesoro")
			{
				dialog.text = "Good to see you, pal! How can I help you?";
				link.l1 = "Steven, I have to ask you something. You might not like it... but I need your help.";
				link.l1.go = "shadows";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "islatesoro")
			{
				dialog.text = "Ah, there you are, "+pchar.name+". I was expecting you; Forest Devil told me about your trouble with Tortuga...";
				link.l1 = "He also told me that you've already found a solution. Is it true?";
				link.l1.go = "terrapin";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Terrapin.Catherina") && pchar.questTemp.Terrapin == "tortuga")
			{
				dialog.text = "How are we doing, "+pchar.name+"?";
				link.l1 = "Secrets everywhere... I need your advice, Steven.";
				link.l1.go = "terrapin_8";
				break;
			}
			// belamour legendary edition хвастовство "Фортуной"
			if(CheckShipTypeInSquadron(SHIP_FRIGATE_L) > 0 && !CheckAttribute(pchar,"questTemp.SharkFrigate"))
			{
				link.l2 = "I want to show you something... Would you walk with me to the pier?";
				link.l2.go = "check_out_my_frigate";
			}
			
			// belamour legendary edition на пару с Акулой
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet") && pchar.questTemp.SharkGoldFleet == "toDodson")
			{
				dialog.text = "Ah, my friend "+GetFullName(pchar)+"! Come in, come in, it's good to see you!";
				link.l1 = "Hello, Steven! Well, I'm here as promised. Is your ship ready?";
				link.l1.go = "SharkGoldFleet";
				break;
			}
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet") && pchar.questTemp.SharkGoldFleet == "RUinDeal")
			{
				link.l2 = "So, how's your business? Still after the 'Golden Fleet'?";
				link.l2.go = "SharkGoldFleet_10";
			}
			dialog.text = "Ah, my friend "+GetFullName(pchar)+"! Come in, come in, it's good to see you!";
			link.l1 = "Hello, Steven. I'm in Sharptown on business and I decided to drop by for a minute.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		// --------------------------------------вариант R-----------------------------------------------
		case "Chad_die":
			dialog.text = "Ha! I take it you're our night visitor? I was informed about this incident only a moment ago. I checked you belongings and found the letter from Forest Devil. Hell, it almost smelled of New Spain's jungles!\nYour name is "+GetFullName(pchar)+"? I'm Steven Dodson, better known to some as Shark. Svenson must've told you about me. Around Justice Island, however, I'm known as the Admiral.\nI apologize for the actions of my men last night. They were acting on orders from me to capture anyone who snuck into the hold; the Narwhals and Rivados routinely send thieves to steal provisions from us.\nChad let you go, I assume? Odd... I was just about to order him to release you.\nWhere's your ship? Is she intact?";
			link.l1 = "Chad? As far as I understand, your boatswain would never have let me leave the prison alive. I freed myself, along with one of those... those Rivados.";
			link.l1.go = "Chad_die_1";
		break;
		
		case "Chad_die_1":
			dialog.text = "Now that's interesting. And how did you make it out of Tartarus? Seems I'll have to have a chat with Chad and his lads...";
			link.l1 = "It'll be a one-sided conversation, I'm afraid. They're all dead. Chad threatened to leave me in the cage forever. He called me a Rivados, said the only way I could prove otherwise to him was by killing the black wizard Chimiset.";
			link.l1.go = "Chad_die_2";
		break;
		
		case "Chad_die_2":
			dialog.text = "What?! Oh, Kapper you stupid fuck...\nWe needed Chimiset alive, and Chad knew that! And why would he assume that you were Rivados, when all of them are black?!";
			link.l1 = "Chimiset's not dead, Steven. The old wizard convinced me that even if I killed him, Chad would never let me leave Tartarus alive...";
			link.l1.go = "Chad_die_3";
		break;
		
		case "Chad_die_3":
			dialog.text = "";
			link.l1 = "Instead of killing Chimiset, I broke open a chest of weapons and ammunition and cut down Chad and his buddies.";
			link.l1.go = "Chad_die_4";
		break;
		
		case "Chad_die_4":
			dialog.text = "Great! That is just fucking great! But I still can't figure... why would Chad do all this?";
			link.l1 = "I'm getting there! Chimiset told me that Chad made a deal with the Narwhals - another clan, I understand - to kill you and take your place as head of the pirates. The Narwhals want you dead, because they're certain that you murdered their leader Alan... Alan Milton? Miller?";
			link.l1.go = "Chad_die_5";
		break;
		
		case "Chad_die_5":
			dialog.text = "Bullshit! I didn't kill Alan Milrow! Someone else did that - maybe even one of the Narwhals! I thought it might even be their current leader, Donald Greenspan.";
			link.l1 = "No. Chad murdered him. Chimiset witnessed the crime - that's why Chad wanted to kill him, too. He didn't want to do it himself because he was afraid Chimiset would haunt him, or... or something, I don't know. Anyway, that's why he wanted me to do the job.";
			link.l1.go = "Chad_die_6";
		break;
		
		case "Chad_die_6":
			dialog.text = "And... why would Chad kill Alan?";
			link.l1 = "To frame you and make you an enemy of the Narwhals. He spread rumours that ensured the blame would land at your doorstep, and make it unsafe for you to show your face in public. And once you were dead, he was going to blame the Rivados for your murder, so your pirates would turn on them.";
			link.l1.go = "Chad_die_7";
		break;
		
		case "Chad_die_7":
			dialog.text = "";
			link.l1 = "I found this letter in Chad's chest. Read it. It looks like solid proof, however indirect.";
			link.l1.go = "Chad_die_8";
		break;
		
		case "Chad_die_8":
			RemoveItems(pchar, "letter_chad", 1);
			dialog.text = "...(reading)... heh! In hindsight I'm not surprised at Chad's betrayal. The whoreson always wanted more power.\nBut the Narwhals! To seriously think I killed Alan! This will cost them double their current price on provisions!\nAs for Chimiset... I was planning to release him anyway; it's high time we made peace with the Rivados. You have shocked me, mate, truly...";
			link.l1 = "I understand, Steven. I don't like it, either. I didn't come here to be part of these political intrigues, I came here to find you and Nathaniel Hawk--";
			link.l1.go = "Chad_die_9";
		break;
		
		// ноды пересечения
		case "Chad_die_9":
			dialog.text = "Hawk? Isn't he on Jamaica?";
			link.l1 = "No. Jackman rules Maroon Town, now. I learned that Hawk arrived here the same way I did: the idol of Kukulcan.";
			link.l1.go = "Chad_die_10";
		break;
		
		case "Chad_die_10":
			dialog.text = "... What the fuck are you talking about?";
			link.l1 = "I didn't get here via ship, Steven. I know this is hard to believe, but there is an Indian idol on the Spanish Main that acts as some kind of doorway - don't look at me like that, I am not mad, or drunk! I don't understand how any of this is possible, but it is!";
			link.l1.go = "Chad_die_11";
		break;
		
		case "Chad_die_11":
			dialog.text = "...";
			link.l1 = "A shaman called Snake Eye in the Miskito village south of Amatique Cove helped Hawk escape some men who were trying to kill him. He showed Hawk the Indian idol - an icon of Kukulcan - and it transported him to this island. Snake Eye told me that he'd once travelled to this island himself the exact same way, and told me how I could do it myself.";
			link.l1.go = "Chad_die_12";
		break;
		
		case "Chad_die_12":
			dialog.text = "...";
			link.l1 = "I came to the idol at midnight, just as he told me. And this idol, which had been made of ordinary stone all day, had turned solid gold! And a weird light shone from it.";
			link.l1.go = "Chad_die_13";
		break;
		
		case "Chad_die_13":
			dialog.text = "...";
			link.l1 = "When I touched the idol, a circle of light formed around the idol, fire blazed everywhere, and then I was drawn into the idol. I was thrown out here, in your ship's cargo hold, downstairs near the bow, at the breach...";
			link.l1.go = "Chad_die_14";
		break;
		
		case "Chad_die_14":
			dialog.text = "...";
			link.l1 = "It was horrible, though - I felt sick and worn out after the crossing. Snake Eye gave me a special potion to counteract that effect, though. And to cap everything off, I was attacked by a giant fucking crab! (deep breath) ";
			link.l1.go = "Chad_die_15";
		break;
		
		case "Chad_die_15":
			dialog.text = "... All right, I believe you.\nThat is, I believe the part about the crab. There are lot of those monsters around the island. We bait them with dead fish, so they hang around the submerged breaches in the hull.\nWonderful guards - scare thieves shitless. But all this about the idol...\nI won't reject that part of your story out of hand; I've heard about the strange rituals the Rivados used to conduct aboard their ships... There was talk of human sacrifices to a... to an Indian idol...";
			link.l1 = "I swear it's all true.";
			link.l1.go = "Chad_die_16";
		break;
		
		case "Chad_die_16":
			dialog.text = "I believe that you believe it. But let's set aside magical idols for now.\nAccording to Jan's letter, you want me to become head of the Brethren of the Coast?";
			link.l1 = "Exactly. Many things changed after you and Hawk disappeared. Jackman wants to become leader of the Brethren, and he will be, if Jan and I don't stop him.";
			link.l1.go = "Chad_die_17";
		break;
		
		case "Chad_die_17":
			dialog.text = "";
			link.l1 = "Jackman is up for a serious and bloody game. I am sure that it was him who organized Hawk's ambush. I also think he killed Blaze Sharp. Making you the leader of the Brethren is the only way to stop him.";
			link.l1.go = "Chad_die_18";
		break;
		
		case "Chad_die_18":
			dialog.text = "Hey, I'd be glad to take up the crown, but we need to leave this island first.\nI've had enough of it. The plan was to leave Dexter in charge of our base here - I never intended to stay here for long - but my ship was burnt in a battle with the clans.\nAnd don't even think about suggesting we use some mystic Indian bullshit to get off the island. It's a ship or nothing, for me.";
			link.l1 = "Steven... (sigh) I still need to find that idol! Snake Eye swore it would be here. Now, you said you knew something about the Rivados conducting rituals using an idol. What else can you tell me?";
			link.l1.go = "Chad_die_19";
		break;
		
		case "Chad_die_19":
			dialog.text = "Nothing. That was all before I arrived here - long before.";
			link.l1 = "Taking a trip through these... these portals of Kukulcan doesn't scare me anymore - and it'll be the fastest way for me to get off the island, get a ship, and get you home. If you believe nothing else, believe that I want to help you.";
			if (pchar.questTemp.LSC == "entrance" || pchar.questTemp.LSC == "mary") link.l1.go = "entrance_4";
			else link.l1.go = "Chad_die_20";
		break;
		// ноды пересечения
		
		case "Chad_die_20":
			dialog.text = "I understand... but I. Can't. Help. You. Aside from the rumours, I know sweet fuck-all about this idol.\nAnd you know, call me selfish, but I'm a little more preoccupied with this assassination business; Chad is dead, but I doubt the Narwhals will give up on trying to kill me.\nSince you need me alive and you're already involved in this mess, I want you to investigate this conspiracy.\nAs a newcomer, you can go places and talk to people that my lads could never reach. Find Chad's partners and bring them to me - or kill them, I don't care.\nTalk to Chimiset; the old black knows more than he lets on. And he may know more about your idol...\nBe careful with the Narwhals, and don't cross their borders unless you have the current password - they change it every week.\nOnce this whole thing's put to bed, I'll give you my rutters. They contain sailing directions and information you'll need to sail to and from Justice Island.\nGo. Find the conspirators. Restore order. Keep me alive.\nNow... Dexter needs to clean the bodies out of the gaol... Tartarus needs a new gaoler... and I need some rum. Fuck me, what a day.";
			link.l1 = "...";
			link.l1.go = "Chad_die_21";
		break;
		
		case "Chad_die_21":
			DialogExit();
			NextDiag.CurrentNode = "Total_wait";
			pchar.questTemp.LSC.rvd_friend = "true"; //флаг на проход по кораблям ривадос
			// // ривадосы не будут останавливать где просят пароль
			sld = characterFromId("Chimiset");
			sld.dialog.currentnode = "Friend"; //ноду Чимисету
			pchar.quest.LSC_Eddy.win_condition.l1 = "location";
			pchar.quest.LSC_Eddy.win_condition.l1.location = "ProtectorFisher";
			pchar.quest.LSC_Eddy.function = "LSC_EddyTalk"; //на разговор с Эдди
			AddQuestRecord("SharkHunt", "10");
			sld = characterFromId("Facio");
			sld.quest.parol = true;
			for (i=7; i<=12; i++)
			{
				sld = CharacterFromID("RivadosSold_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			for (i=4; i<=8; i++)
			{
				sld = CharacterFromID("RivadosProt_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			AddSimpleRumourCityTip("Would you believe it? Someone has killed the Admiral's gaoler, Chad Kapper! No doubt the work of that Rivados wizard he locked up, Chimiset...", "LostShipsCity", 7, 2, "LSC", "");
			AddSimpleRumourCityTip("I heard that Chad Kapper is dead, but there's been no official statement and his body hasn't turned up. Perhaps, the Admiral simply gave him a secret mission...?", "LostShipsCity", 7, 2, "LSC", "");
			AddSimpleRumourCityTip("I haven't seen our gaoler, Chad Kapper, lately. Some say he was killed, some say he's still alive. The only thing people agree on is that no one has seen him...", "LostShipsCity", 7, 2, "LSC", "");
			AddSimpleRumourCityTip("They say that the Admiral doubled provision prices for the Narwhals! That pirate is truly reckless!", "LostShipsCity", 7, 3, "LSC", "");
		break;
		
			case "Mary_Die":
			dialog.text = "Well, what do you have, "+pchar.name+"? Any news about the Narwhals?";
			link.l1 = "Yes. You'll be glad to know, Steven, that the conspiracy was unveiled and the conspirators are dead. I know everything, now.";
			link.l1.go = "Mary_Die_1";
		break;
		
		case "Mary_Die_1":
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt.TownAttack")) dialog.text = "I thought so when I heard the gunfight... Talk to me.";
			else dialog.text = "Is that so? Well, that's a relief! Tell me.";
			link.l1 = "It was all planned by your boatswain, Chad Kapper. He murdered Alan Milrow in the cells of Tartarus and spread a lie that you did it. The Narwhals were furious - especially Alan's girlfriend, Red Mary...";
			link.l1.go = "Mary_Die_2";
		break;
		
		case "Mary_Die_2":
			dialog.text = "";
			link.l1 = "Mary was hungry for revenge and Chad Kapper preyed upon her anger. They made a plan to assassinate you. I understand you have a habit of walking around the stern gallery of the San Augustine every evening...";
			link.l1.go = "Mary_Die_3";
		break;
		
		case "Mary_Die_3":
			dialog.text = "Heh! That's one habit I'll have to break... Go on.";
			link.l1 = "They needed a long-range and accurate rifle to perform their plan, and so one Adolf Barbier provided it. But his stutzen was pawned to Giuseppe Fazio, so Mary and Chad had to buy it back - Adolf redeemed the stutzen...";
			link.l1.go = "Mary_Die_4";
		break;
		
		case "Mary_Die_4":
			dialog.text = "";
			link.l1 = "They hired Marcello Cyclops, a former royal hunter, to take the shot. After that, Mary would kill him and use his corpse and rifle as proof the Rivados were responsible for the attack; Cyclops was a mulatto.";
			link.l1.go = "Mary_Die_5";
		break;
		
		case "Mary_Die_5":
			dialog.text = "And all from Chad's devious mind... clever fucker!";
			link.l1 = "And finally, the Narwhals and pirates would attack the Rivados clan and destroy them. Chad would become Admiral and Mary would be his lover. Although... after a few tumbles he'd probably have just cut her throat, since she knew too much.";
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt.TownAttack")) link.l1.go = "Mary_Die_6a";
			else link.l1.go = "Mary_Die_6";
		break;
		
		case "Mary_Die_6":
			dialog.text = "";
			link.l1 = "Anyway, it's over now. Adolf wasn't very talkative, so I had to kill him right in his cabin. I also dealt with Mary and Cyclops when they came to get the stutzen from Adolf.";
			link.l1.go = "Mary_Die_7";
		break;
		
		case "Mary_Die_7":
			dialog.text = "So, they're all lying dead inside the Santa Florentina, then? And no one knows?";
			link.l1 = "Yes. All three of them - and no one knows except us.";
			link.l1.go = "Mary_Die_8";
		break;
		
		case "Mary_Die_8":
			dialog.text = "Good. Witnesses would complicate things. I'll take care of the bodies. You did a good job, "+pchar.name+"! Were you in my crew, I'd make you first mate.";
			link.l1 = "High praise, Shark. Thank you. Oh, take a look at these letters. I took them from the bodies of Cyclops and Mary...";
			link.l1.go = "Mary_Die_9";
			AddSimpleRumourCityTip("Have you heard that? Our scrappy madcap Red Mary has disappeared. I wouldn't be surprised if she's dead...", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("They say that Red Mary has disappeared. You heard about that?", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("Mary Casper has vanished. Some people say that she's still inside her cabin, but I don't believe it; it's been a long time since I saw a light in her window.", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("They say that Red Mary was murdered. Poor girl! Yes, she was a tough sort, but everybody loved her. Who could have done such a thing?", "LostShipsCity", 10, 1, "LSC", "");
		break;
		
		case "Mary_Die_6a":
			dialog.text = "";
			link.l1 = "Anyway, it's over now. Adolf wasn't very talkative, so I had to kill him right in his cabin. I also dealt with Mary and Cyclops when they came to get the stutzen from Adolf.";
			link.l1.go = "Mary_Die_7a";
		break;
		
		case "Mary_Die_7a":
			dialog.text = "Too bad you started a fight on the Eva. You'll be in shit with the Narwhals for killing their people. Stay away from them until you can make peace.\nIn general, you did all right, "+pchar.name+"! Were you in my crew, I'd make you my first mate.";
			link.l1 = "High praise, Shark. Thank you. Oh, take a look at these letters. I took them from the bodies of Cyclops and Mary...";
			link.l1.go = "Mary_Die_9";
			AddSimpleRumourCityTip("Such a massacre you've committed! The Narwhals won't forget it!", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("I understand killing Cyclops and two Narwhal bandits, but... the girl. Why did you have to kill poor Mary?", "LostShipsCity", 7, 5, "LSC", "");
		break;
		
		case "Mary_Die_9":
			RemoveItems(pchar, "letter_chad", 1);
			RemoveItems(pchar, "letter_chad_1", 1);
			dialog.text = "Poor Mary? Don't tell me you feel sorry for that whore.";
			link.l1 = "I do. Chad deceived her, manipulated her feelings and natural hotheadedness... She shouldn't have had to die for his ambitions.";
			link.l1.go = "Mary_Die_10";
		break;
		
		case "Mary_Die_10":
			TakeNItems(pchar, "gold_dublon", 500);
			Log_Info("You have received 500 doubloons");
			PlaySound("interface\important_item.wav");
			CloseQuestHeader("SharkHunt");
			bDisableFastReload = false; // belamour legendary edition
			dialog.text = "Well, go see Brother Julian and light a candle, if you feel that badly about it. Personally, I'm damn glad the bitch is dead.\nAlright, let's drop the subject. I'm grateful for your help, "+pchar.name+". You can count on my support now. I want to pay you for your excellent work. Here's five hundred doubloons.";
			link.l1 = "Thanks, Steven...";
			link.l1.go = "LSC_navy";
			AddSimpleRumourCityTip("They say the Admiral respects you, mister...", "LostShipsCity", 15, 2, "LSC", "");
			AddSimpleRumourCityTip("They say that you're the Admiral's loyal friend. Is that true?", "LostShipsCity", 15, 2, "LSC", "");
		break;
		
		// ----------------------------------------вариант N---------------------------------------------------
		case "entrance":
			dialog.text = "I don't know you. What do you want?";
			link.l1 = "Of course, you don't. We've never met, and I've only just arrived. Hello, Steven. I've been looking for you.";
			link.l1.go = "entrance_1";
		break;
		
		case "entrance_1":
			dialog.text = "A lot of people have come looking for me. Most of them are in cemetaries now. If you don't want to join them, maybe try telling me why you've been looking for me.";
			link.l1 = "We have a friend in common. Here, take this letter. It was written by Jan Svenson. Old Forest Devil can explain things far better than me.";
			link.l1.go = "entrance_2";
		break;
		
		case "entrance_2":
			RemoveItems(pchar, "letter_svenson", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "(reading)... Hm. That does explain things. And here I thought you'd come to give me a black spot for killing Blaze - recently there've been many pirates eager to do that.\nDid you leave your ship at the outer ring? And how'd you know I was here?";
			link.l1 = "I didn't. That was pure chance. And about Blaze... me and Jan don't think you're responsible for his death.";
			link.l1.go = "entrance_3";
		break;
		
		case "entrance_3":
			dialog.text = "You're right, I'm not. But someone wants the Brethren to think I did.";
			link.l1 = "Interesting... you know, I came here to find Nathaniel Hawk, but here you are instead, heh!";
			link.l1.go = "Chad_die_9";
		break;
		
		case "entrance_4":
			dialog.text = "You'll have to talk about it with the old-timers of the island. Try the Rivados wizard, Chimiset. The old black knows much more than he lets on.";
			link.l1 = "And where can I find this wizard?";
			if (pchar.questTemp.LSC == "mary") link.l1.go = "mary";
			else link.l1.go = "entrance_5";
		break;
		
		case "entrance_5":
			dialog.text = "In my prison, aboard the Tartarus. I was planning to release him soon; it's time to improve our relations with the Rivados.\nYou can deliver the order yourself! Go to the Tartarus, tell Chad Kapper, the gaoler, that I want Chimiset freed.\nBetter yet, ask to see Chimiset first. Tell him I sent you, that I'll release him if he's talkative enough. I'm sure he'll tell you what you want to know.";
			link.l1 = "Hmm... where is the Tartarus?";
			link.l1.go = "entrance_6";
		break;
		
		case "entrance_6":
			dialog.text = "Leave my residence, cross the bridge, turn left, go through the frigate Caroline to the galleon Gloria and arrive at the Esmeralda. Look for sign that says 'store' and enter the doors beneath. Go through the door in the bow of the ship and you'll reach Tartarus.\nBe careful at the Esmeralda, that's Narwhal territory, even though others can visit it. Do not piss off their guards and don't make trouble.";
			link.l1 = "Who are these Rivados and Narwhals?";
			link.l1.go = "entrance_7";
		break;
		
		case "entrance_7":
			dialog.text = "They're clans who're descended from the first settlers of Justice Island. The Narwhals are of mostly English, Dutch, and French stock. The Rivados are all Negroes.\nEach clan has a leader, and each holds several ships that constitute a territory which is restricted to outsiders.\nYou must know the correct passwords in order to visit either Narwhal or Rivados territory, and they change the passwords every week.";
			link.l1 = "Good to know, but will they let me inside the prison?";
			link.l1.go = "entrance_8";
		break;
		
		case "entrance_8":
			dialog.text = "They will. Here's the key, so Chad will know I sent you. Don't lose it.";
			link.l1 = "Thanks. I'll talk with that... that Chimiset and be back with the results.";
			link.l1.go = "entrance_9";
		break;
		
		case "entrance_9":
			DialogExit();
			GiveItem2Character(pchar, "key_capper");
			NextDiag.CurrentNode = "Total_wait";
			sld = characterFromId("Chimiset");
			sld.dialog.currentnode = "prisoner"; //даем ноду Чимисету
			sld.quest.chimiset_die = "true";
			ChangeCharacterAddressGroup(sld, "Tartarusprison", "quest", "prison2"); // в закрытую клетку
			LAi_SetGroundSitTypeNoGroup(sld);
			sld = characterFromId("Capper");
			sld.dialog.currentnode = "prisoner"; //даем ноду Капперу
			LAi_LocationFightDisable(&Locations[FindLocation("Tartarusprison")], true);//запретить драться
			// прерывания на локаторы тартаруса
			pchar.quest.LSC_TartarusEntrance1.win_condition.l1 = "locator";
			pchar.quest.LSC_TartarusEntrance1.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_TartarusEntrance1.win_condition.l1.locator_group = "reload";
			pchar.quest.LSC_TartarusEntrance1.win_condition.l1.locator = "reload51";
			pchar.quest.LSC_TartarusEntrance1.win_condition.l2 = "item";
			pchar.quest.LSC_TartarusEntrance1.win_condition.l2.item = "key_capper";
			pchar.quest.LSC_TartarusEntrance1.function = "LSC_TartarusEntrance1_Open";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l1 = "locator";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l1.locator_group = "reload";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l1.locator = "reload52";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l2 = "item";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l2.item = "key_capper";
			pchar.quest.LSC_TartarusEntrance2.function = "LSC_TartarusEntrance2_Open";
			AddQuestRecord("SharkHunt", "19");
		break;
		
		case "entrance_10":
			dialog.text = "You've been to Tartarus?";
			link.l1 = "Yes. I gave your orders to Chad and talked with Chimiset.";
			link.l1.go = "entrance_11";
		break;
		
		case "entrance_11":
			dialog.text = "Did the wizard tell you anything?";
			link.l1 = "Oh, yes. He told me where to find the idol I'm looking for. It was on the San Geronimo, near Narwhal territory, which sank some years ago.";
			link.l1.go = "entrance_12";
		break;
		
		case "entrance_12":
			dialog.text = "Ha-ha-ha! So, your magic idol's now on the seabed, huh? Well, pal, looks like you're stuck with us.";
			link.l1 = " I'll figure out a way to get to the idol. Now, Chimiset said you shouldn't trust Kapper, because he saw Chad murder someone named Alan Milrow--";
			link.l1.go = "entrance_13";
		break;
		
		case "entrance_13":
			dialog.text = "What?! Chad killed Alan? Chimiset's lying, it can't be true!";
			link.l1 = "Steve, Chimiset was terrified. If he was lying, he did a bloody good job of it...";
			link.l1.go = "entrance_14";
		break;
		
		case "entrance_14":
			dialog.text = "Damn it all, now that's just terrific!\nAlan's murder soured my relationship with the Narwhals - some of them even think that I was responsible for it - and now it turns out that one of my own officers committed the murder?!";
			link.l1 = "You seem to attract a lot of blame for things you didn't do.";
			link.l1.go = "entrance_15";
		break;
		
		case "entrance_15":
			dialog.text = "I've noticed.";
			link.l1 = "Well, I'm afraid it gets better: Chimiset overheard that some of your men were planning to kill you. He'll only tell you more after you release him, and only in private.";
			link.l1.go = "entrance_16";
		break;
		
		case "entrance_16":
			dialog.text = "Great. I knew this day was going too smoothly.\nDid Chimiset give you any details?";
			link.l1 = "No. He fears Chad too much. He wants his own safety guaranteed first.";
			link.l1.go = "entrance_17";
		break;
		
		case "entrance_17":
			dialog.text = "All right. Let's tell the Rivados that I want to meet with Chimiset. We'll see what he has to say. And concerning the attempt on my life... nothing for it but to be careful.\nSo, what are you going to do now, "+pchar.name+"?";
			link.l1 = "Nothing in particular yet. I'll walk around the island and get to know the locals - perhaps I'll come up with some idea how to get out of here. And I need to find Nathaniel Hawk, he's the reason I came here.";
			link.l1.go = "entrance_18";
		break;
		
		case "entrance_18":
			dialog.text = "Right. Don't forget to see me once you find a way off this island, I'll give you the rutters with my sailing directions so you can sail a ship back here. I'll also have other information you'll need.";
			link.l1 = "Fine. I will visit you for sure, Steve!";
			link.l1.go = "entrance_19";
		break;
		
		case "entrance_19":
			DialogExit();
			NextDiag.CurrentNode = "Total_wait";
			sld = characterFromId("Facio");
			sld.quest.parol = true;
			// прерывание на вызов к Акуле
			pchar.quest.LSC_GotoShark.win_condition.l1 = "Timer";
			pchar.quest.LSC_GotoShark.win_condition.l1.date.hour  = 9.00;
			pchar.quest.LSC_GotoShark.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.LSC_GotoShark.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.LSC_GotoShark.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.LSC_GotoShark.win_condition.l2 = "location";
			pchar.quest.LSC_GotoShark.win_condition.l2.location = "LostShipsCity_town";
			pchar.quest.LSC_GotoShark.function = "LSC_GotoShark";
			AddQuestRecord("SharkHunt", "21");
		break;
		
		case "entrance_20":
			dialog.text = ""+pchar.name+", bad news: Chimiset's dead and Chad Kapper has vanished.";
			link.l1 = "Damnation! So, Chad finally killed the old wizard...";
			link.l1.go = "entrance_21";
		break;
		
		case "entrance_21":
			dialog.text = "Seems so. This situation's getting worse by the hour. I had a truce all ready to go with Black Eddie, and now...\nWell, we can forget about peace with the Rivados. By the way, they know you talked to Chimiset before he died, and they consider you to be one of my men, so stay away from them.";
			link.l1 = "Wonderful.";
			link.l1.go = "entrance_22";
		break;
		
		case "entrance_22":
			dialog.text = "There's more. I received a letter from the island's mediator and diplomat, Giuseppe Fazio. He invited me to visit his cabin aboard the Caroline at midnight.\nHe also said I must come alone, because my life is at stake and my men can't be trusted.\nThis would make sense - Chimiset warned us about a traitor in our crew - yet it still smells so suspicious. Alone, at midnight...\nNormally, the fat man comes to me. I'm going to ask for your help, "+pchar.name+". Jan called you as a resourceful and brave man, and an excellent fighter. I want you to escort me to the meeting at midnight.";
			link.l1 = "No need to ask, Steven; I'm in. I don't like this invitation either - it's almost certainly a trap.";
			link.l1.go = "entrance_23";
		break;
		
		case "entrance_23":
			dialog.text = "Maybe. I hope I'm wrong but I'd rather be ready. I'm glad to have you with me\nCome to the main deck of the San Augustine at midnight and we'll go see Fazio. It's a short walk to the Caroline.";
			link.l1 = "Midnight, then. And I'll be well-armed.";
			link.l1.go = "entrance_24";
		break;
		
		case "entrance_24":
			DialogExit();
			NextDiag.CurrentNode = "Total_wait";
			pchar.quest.LSC_GotoShark.win_condition.l1 = "Timer";
			SetFunctionTimerCondition("LSC_MeetingSharkAugustine", 0, 0, 1, false); // таймер
			AddQuestRecord("SharkHunt", "22");
		break;
		
		case "caroline":
			dialog.text = "All right, "+pchar.name+", let's not waste any time. Let's see what old fat Fazio has to say. Stay close to me.";
			link.l1 = "I'm with you, Steve. Keep your weapon ready...";
			link.l1.go = "caroline_1";
		break;
		
		case "caroline_1":
			DialogExit();
			sld = characterFromId("Dodson");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload25", "CarolineBank", "barmen", "bar2", "LSC_CarolineOpen", -1);
		break;
		
		case "caroline_2":
			dialog.text = "Where's that fat man? Where did he go? What a way to treat one's guests! Do you see him, "+pchar.name+"? I don't.\nPerhaps, we should check his chests, he might be in them... if nothing else we'll get compensation for our troubles, ha-ha!";
			link.l1 = "Heh, I doubt there's a chest in the world he'd be able to fold himself into - hush! Steven! I heard something...";
			link.l1.go = "caroline_3";
		break;
		
		case "caroline_3":
			dialog.text = "... get ready, "+pchar.name+".";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LSC_Caroline_DlgExit_3");
		break;
		
		case "caroline_5":
			dialog.text = "Argh! We did it... God damn, I thought they had us.";
			link.l1 = "I've been in scrapes worse than this, but even I'll admit, that was too close. Chimiset was right: Chad was a traitor. Who was that girl commanding them?";
			link.l1.go = "caroline_6";
		break;
		
		case "caroline_6":
			dialog.text = "Mary Casper, also known as Red Mary. The late Alan Milrow's lover.\nI understand why Chad was here - he wanted to take over my position - but what was Mary doing here?";
			link.l1 = "If she was Alan's lover, then it's obvious: she wanted revenge for his death. Poor girl didn't realize she was fighting alongside the very man who murdered Alan...";
			link.l1.go = "caroline_7";
		break;
		
		case "caroline_7":
			dialog.text = "Makes sense. Oh, I'm going to make the Narwhals pay for this! I'll stop selling them provisions, let them starve to death!\nAnd what can they do about it? If they attack us, the San Augustine can withstand any siege! They're going to regret this. And I'll nail Fazio's fat ass to the wall behind my chair!";
			link.l1 = "Steve, Steve, wait! What if... what if the Narwhals had no part in this? Chad was one of your pirates, not the Narwhals. Chad murdered Alan, Chad murdered Chimiset, and Chad spread the rumours about you. What if all this begins and ends with Chad?";
			link.l1.go = "caroline_8";
		break;
		
		case "caroline_8":
			dialog.text = "... Damn you, "+pchar.name+", but... you may have a point.\nFine, I owe you, so I'll give you a chance to look into this. If you can prove the Narwhals played no part in this, I'll call off the war.\nYou've earned my trust, and you can count on my help in anything you do. I'd make you my boatswain, if I still had a ship.";
			link.l1 = "You can repay me by taking up the leadership of the Brethren of the Coast, when we get out of here. Go get some rest, I'll look around this cabin for any more clues - and don't go dying on me in my absence!";
			link.l1.go = "caroline_9";
		break;
		
		case "caroline_9":
			dialog.text = "Heh, wouldn't dream of it. I'll send someone to clean up these bodies. The crabs will eat well tonight! (spits) 'Bye, my friend.";
			link.l1 = "Goodnight.";
			link.l1.go = "caroline_10";
		break;
		
		case "caroline_10":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "SanAugustineResidence", "sit", "sit1", "LSC_SharkReturnSit", 10.0);
			AddQuestRecord("SharkHunt", "24");
		break;
		
		case "narval":
			dialog.text = "Well, "+pchar.name+", learn anything new?";
			link.l1 = "You can call off your vendetta, Steven. The Narwhals weren't involved in the plot against you, with the exception of Mary and the lads we fought on the Caroline - I think she talked them into attacking us. Fazio was forced to send you the invitation. I have found a letter in his cabin which explains a lot. Read it.";
			link.l1.go = "narval_1";
		break;
		
		case "narval_1":
			RemoveItems(pchar, "letter_chad_1", 1);
			dialog.text = "(reading)... Hmm... that's Fazio all over: saving his own skin. So, it was really all Chad, beginning to end...";
			link.l1 = "And all because he wanted to be Admiral. I visited Donald Greenspan. He swore that neither him nor anyone of his men were plotting against you.";
			link.l1.go = "narval_2";
		break;
		
		case "narval_2":
			dialog.text = "Do you trust him?";
			link.l1 = "I do. Donald will clear you of Alan's murder. He's ready to visit you personally and talk things out.";
			link.l1.go = "narval_3";
		break;
		
		case "narval_3":
			dialog.text = "Good. Much as I love a dustup, a war at this stage would be pointless. Too many have died already, and the ones who set all this in motion are crab food.\nYou say Donald is ready to apologize? Fine, let's salvage what relations we can with the Narwhals; I think the Rivados are lost to us because of Chimiset.";
			link.l1 = "This may be the only chance you get for peace.";
			link.l1.go = "narval_4";
		break;
		
		case "narval_4":
			dialog.text = "You've already convinced me. Tell Donald I'm ready to see him and make peace.";
			link.l1 = "I am on my way.";
			link.l1.go = "narval_5";
		break;
		
		case "narval_5":
			dialog.text = "Wait, "+pchar.name+". You did well and you should be paid well. Here's five hundred doubloons.";
			link.l1 = "Thank you!";
			link.l1.go = "LSC_navy";
			TakeNItems(pchar, "gold_dublon", 500);
			Log_Info("You have received 500 doubloons");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("SharkHunt", "27");
			pchar.questTemp.Saga.SharkHunt = "find"; //флаг - покушение предотвращено
			sld = characterFromId("Grinspy");
			sld.dialog.currentnode = "shark_16"; // ноду Дональду Гринспи
			SetFunctionTimerCondition("LSC_FacioReturn", 0, 0, 1, false); // вертаем на место Фацио через сутки
			AddSimpleRumourCityTip("They say that the Admiral respects you, mister...", "LostShipsCity", 15, 2, "LSC", "");
			AddSimpleRumourCityTip("They say that you are the Admiral's loyal friend. Is that true?", "LostShipsCity", 15, 2, "LSC", "");
		break;
		
		// ----------------------------------------вариант M----------------------------------------------------
		case "mary":
			dialog.text = "In my prison Tartarus. You can go there and see him. I'll give you the key. Talk to Chad Kapper, our gaoler--";
			link.l1 = "Wait, Steven. There's something you need to know about Kapper...";
			link.l1.go = "mary_1";
		break;
		
		case "mary_1":
			dialog.text = "... I'm listening...";
			link.l1 = "I don't know how else to say this, but... Kapper is plotting to kill you.";
			link.l1.go = "mary_2";
		break;
		
		case "mary_2":
			dialog.text = "... You'd better have a damn good reason for accusing one of my oldest mates of treachery.";
			link.l1 = "Let me tell you the whole story--";
			link.l1.go = "mary_3";
		break;
		
		case "mary_3":
			dialog.text = "Talk fast.";
			link.l1 = "After I found myself in the flooded cargo hold, I got out through a hole in the hull and swam among the shipwrecks looking for a place to climb out. I finally found a wreck where I could get through a door in the bow. There was a fight between some girl in a red jacket and two tough lads--";
			if (pchar.questTemp.LSC.Mary == "alive") link.l1.go = "mary_4"; // Мэри жива
			else link.l1.go = "mary_15";
		break;
		
		case "mary_4":
			dialog.text = "Someone was trying to kill Red Mary?";
			link.l1 = "Apparently. I helped her finish off those bastards and we had an interesting chat afterwards... Tell me, Steve, who are the 'Narwhals' and 'Rivados'? She mentioned them several times.";
			link.l1.go = "mary_5";
		break;
		
		case "mary_5":
			dialog.text = "They're clans who're descended from the first settlers of Justice Island. The Narwhals are of mostly English, Dutch, and French stock. The Rivados are all Negroes.\nEach clan has a leader, and each holds several ships that constitute a territory which is restricted to outsiders.\nYou must know the correct passwords in order to visit either Narwhal or Rivados territory, and they change the passwords every week.";
			link.l1 = "A-ah, I see... and Mary is a Narwhal?";
			link.l1.go = "mary_6";
		break;
		
		case "mary_6":
			dialog.text = "Yes. So, what did she tell you?";
			link.l1 = "Chad Kapper killed Alan Milrow, her lover, who was captured by you. After that, he spread a rumour that you committed the murder. He tried to manipulate Mary's lust for revenge for his own ends.";
			link.l1.go = "mary_7";
		break;
		
		case "mary_7":
			dialog.text = "Chad killed Alan?! But why?";
			link.l1 = "To leave the blame at your doorstep and make the Narwhals hostile to you. Kapper's ultimate goal is to eliminate you and take your place as Admiral. Mary refused to take part in his plan - and to become his lover - so he ordered his men to kill her.";
			link.l1.go = "mary_8";
		break;
		
		case "mary_8":
			dialog.text = "And she told you all this?";
			link.l1 = "Yes. I don't think she was lying. Besides, she gave me a letter from Chad Kapper. I've already read it. Here.";
			link.l1.go = "mary_9";
		break;
		
		case "mary_9":
			RemoveItems(pchar, "letter_chad_1", 1);
			dialog.text = " (reading) ... Yes, this is Chad's handwriting, all right. Argh! Unbelievable! Bastard! Traitor!\nI'm going to hang him by his own entrails! Layton! Get five men and--\nOn second thought... belay that, Layton. Dismissed! We'll do this smart-like.\nI've been looking for a way to improve our relations with the Rivados, and this could be it.\nTheir wizard, Chimiset, is being held in Tartarus, the local prison. We're going to let the Rivados free their man, and in the act, they'll kill Chad for us.\nLayton! Go to Tartarus and take all our guards off her upper deck! "+pchar.name+", I have an important job for you. Find the leader of the Rivados, Black Eddie, and negotiate with him--";
			link.l1 = "Me? But I don't know anyone here!";
			link.l1.go = "mary_10";
		break;
		
		case "mary_10":
			dialog.text = "You're about to, starting with Eddie: he's the head of the entire Rivados clan.\nYou're the best man to do diplomacy on our behalf. None of my pirates would be granted an audience with Eddie... and to be perfectly honest, none of them have great oratory skills.";
			link.l1 = "(sigh) All right, I'll go see this... Black Eddie.";
			link.l1.go = "mary_11";
		break;
		
		case "mary_11":
			GiveItem2Character(pchar, "key_capper");
			Log_Info("You have received 50 doubloons");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "gold_dublon", 50);
			dialog.text = "Take this key and give it to him. It opens every door on the Tartarus - the Negroes will need it if they're to rescue Chimiset.\nAlso, take these fifty doubloons. Another local you're about to know is Giuseppe Fazio, a mediator and diplomat on the Caroline. Take the doubloons and buy this week's password to Rivados territory - Fazio makes it his business to acquire the passwords as they're selected.\nNext, go to the Protector. It's Black Eddie's residence. Tell him that Chad Kapper has joined the Narwhals, stopped following my orders, and is going to murder Chimiset today.\nGive him the key, tell him to take a strong force and attack the Tartarus.\nWe'll kill two birds with one stone: the Rivados will consider us their allies and Kapper will die at the hands of Negroes. Got everything?";
			if (pchar.questTemp.LSC.Mary == "alive")// Мэри жива
			{
				link.l1 = "I think so, but where do I find the Protector and Caroline?";
				link.l1.go = "mary_12";
			}
			else
			{
				link.l1 = "Listen, Steve, tell me who these Rivados and Narwhals are. I still don't know anything about them.";
				link.l1.go = "mary_12_1";
			}
		break;
		
		case "mary_12_1":
			dialog.text = "They're clans who're descended from the first settlers of Justice Island. The Narwhals are of mostly English, Dutch, and French stock. The Rivados are all Negroes.\nEach clan has a leader, and each holds several ships that constitute a territory which is restricted to outsiders.\nYou must know the correct passwords in order to visit either Narwhal or Rivados territory, and they change the passwords every week.";
			link.l1 = "Now I see. But where do I find the Protector and Caroline?";
			link.l1.go = "mary_12";
		break;
		
		case "mary_12":
			dialog.text = "Leave my residence, cross the rope bridge, and turn left. This will be the Caroline.\Getting to the Protector is a bit trickier: after you cross the bridge, turn right and go to the Santa Florentina - other side of the board bridge.\nFind the Rivados soldiers - as I said, they're all black. They'll ask for the password. Say it loud and clear. Then go inside the Fury and enter the Protector through the stern.";
			link.l1 = "All right... I think I've got it.";
			link.l1.go = "mary_13";
		break;
		
		case "mary_13":
			dialog.text = "Well, then get to it, friend!";
			link.l1 = "I'll be back soon.";
			link.l1.go = "mary_14";
		break;
		
		case "mary_14":
			DialogExit();
			NextDiag.CurrentNode = "dodson_warwait";
			AddQuestRecord("SharkHunt", "32");
			sld = characterFromId("Eddy");
			sld.dialog.currentnode = "capper"; // ноду Эдди
			sld = characterFromId("Facio");
			sld.quest.parol = true;
			pchar.questTemp.LSC = "mary_go"; //меняем флаг
		break;
		
		case "dodson_warwait":
			dialog.text = "Are you still here? Go see Black Eddie right now!";
			link.l1 = "I am on my way.";
			link.l1.go = "exit";
			NextDiag.TempNode = "dodson_warwait";
		break;
		
		case "mary_15":
			dialog.text = "Someone was trying to kill Red Mary?.";
			link.l1 = "Was that her name? I tried to save her, but one of her attackers got her with a sabre cut.";
			link.l1.go = "mary_16";
		break;
		
		case "mary_16":
			dialog.text = "I'm sorry for the girl, but I'm not surprised. Mary was always a troublemaker.\nAnd what about Chad? He's my boatswain.";
			link.l1 = "Your boatswain? Oh... um, here, read this letter. I found it on the girl's body. Kapper is planning an attempt on your life, Steven.";
			link.l1.go = "mary_9";
		break;
		
		// Каппер сбежал
		case "Chad_escape":
			dialog.text = "Where have you been?! I've been told the Rivados freed their wizard, but no one's seen you in hours!";
			link.l1 = "I'm sorry, Steven. The blacks held me hostage on the Protector to ensure their safety in case you double-crossed them. They freed Chimiset, yes, but Chad escaped.";
			link.l1.go = "Chad_escape_1";
		break;
		
		case "Chad_escape_1":
			dialog.text = "Shit! Never trust a Negro to do a white man's job... Fucking up even a simple task... God damn those Rivados!";
			link.l1 = "Chad's hidden among the Narwhals...";
			link.l1.go = "Chad_escape_2";
		break;
		
		case "Chad_escape_2":
			dialog.text = "Of course he has! He's no fool - he knows the Rivados couldn't have got inside the Tartarus without my help! Now he'll hide and plot from the shadows.\nLayton! Double the guards! Keep your eyes open at all times! A fortune goes to the man who sends Chad Kapper to hell!!";
			link.l1 = "Steven, I'm going to go. Maybe I'll be able to track Chad down. I'll come back when I've news.";
			link.l1.go = "Chad_escape_3";
			NextDiag.TempNode = "Total_wait";
		break;
		
		case "Chad_escape_3":
			DialogExit();
			if (pchar.questTemp.LSC.Mary == "alive") 
			{
				pchar.questTemp.Saga.SharkHunt = "mary_whiskey"; // к Мэри
				AddQuestRecord("SharkHunt", "34");
			}
			else
			{ // не уберег Мэри - допетривай сам, куда идти
				pchar.questTemp.Saga.SharkHunt = "trader_whiskey"; // флаг на магазин - поиск виски
			}
			NextDiag.CurrentNode = "Total_wait";
			// добавим немного атмосферы - уберем Акселя до утра
			sld = characterFromId("Axel");
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "EsmeraldaStoreBig", "goto", "goto5");
			sld = GetCharacter(NPC_GenerateCharacter("AxelHelper", "citiz_52", "man", "man", 35, PIRATE, 1, true, "quest"));
			FantomMakeCoolFighter(sld, 35, 100, 100, "blade_21", "pistol4", "bullet", 200);
			sld.dialog.Filename = "Quest\LSC\OtherNPC.c";
			sld.dialog.currentnode = "AxelHelper";
			LAi_SetOwnerType(sld);
			ChangeCharacterAddressGroup(sld, "EsmeraldaStoreBig", "barmen", "stay");
			LAi_group_MoveCharacter(sld, "LSC_NARVAL");
			SetFunctionTimerCondition("LSC_AxelReturnStore", 0, 0, 1, false); // таймер на возврат Акселя
		break;
		
		case "whiskey":
			dialog.text = "What happened, "+pchar.name+"? You look like you're being chased by the Devil himself!";
			link.l1 = "Did you get a barrel of whiskey?";
			link.l1.go = "whiskey_1";
		break;
		
		case "whiskey_1":
			dialog.text = "What whiskey--?";
			link.l1 = "Did you get a barrel of whiskey?!";
			link.l1.go = "whiskey_2";
		break;
		
		case "whiskey_2":
			dialog.text = "Lower your voice, man! I haven't got any whiskey! What's wrong?";
			link.l1 = "Thank God I've come in time... Chad Kapper bought a barrel of Bushmills from Axel Yost--";
			link.l1.go = "whiskey_3";
		break;
		
		case "whiskey_3":
			dialog.text = "Bushmills? That's my favourite drop! I haven't drunk it for ages!";
			link.l1 = "Yes-yes, and Kapper knows that; he asked his pal, Marcello Cyclops, to buy some arsenic from Sancho Carpentero. You get it now?";
			link.l1.go = "whiskey_4";
		break;
		
		case "whiskey_4":
			dialog.text = "He was going to poison me...?";
			link.l1 = "Yes! That's why I was in such a hurry. Fuck, my heart... Listen, if anyone brings you a barrel of whiskey, don't drink it! It'll be poisoned.";
			link.l1.go = "whiskey_5";
		break;
		
		case "whiskey_5":
			dialog.text = ""+pchar.name+", thanks for the warning, I will be careful - wait, where are you off to now?";
			link.l1 = "I need to find Kapper and Cyclops. I think I know where they are. I'll talk to you soon!";
			link.l1.go = "whiskey_6";
		break;
		
		case "whiskey_6":
			DialogExit();
			pchar.questTemp.LSC.Dodson_warning = "true"; // Акула предупрежден
			LAi_CharacterDisableDialog(npchar);//запрещаем диалог
			AddQuestRecord("SharkHunt", "45");
		break;
		
		case "whiskey_7":
			dialog.text = "Ha! Just the man I was looking for! Seems like I owe you my life.";
			link.l1 = "Did the whiskey show up?";
			link.l1.go = "whiskey_8";
		break;
		
		case "whiskey_8":
			dialog.text = "It did! Bushmills, just as you said. Our dear Fazio was so kind - presented it as a gift. Naturally, I arrested him.";
			link.l1 = "Has he confessed?";
			link.l1.go = "whiskey_9";
		break;
		
		case "whiskey_9":
			dialog.text = "He has. Says Kapper forced him into this, told him to tell me that the whiskey was a present from the Narwhals..";
			link.l1 = "Kapper is dead. So are his Narwhal friends. Now there's just one bastard left - Marcello Cyclops... I'm sure Fazio knows his whereabouts. Let me push him a bit!";
			link.l1.go = "whiskey_10";
		break;
		
		case "whiskey_10":
			dialog.text = "Be my guest - but take care not to kill him, our dear Fazio is in rather poor health.";
			link.l1 = "I will be gentle... mostly.";
			link.l1.go = "whiskey_11";
		break;
		
		case "whiskey_11":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//запрещаем диалог
			chrDisableReloadToLocation = true;//закрыть локацию
			sld = CharacterFromID("Facio");
			LAi_CharacterEnableDialog(sld);
		break;
		
		case "poison":
			pchar.questTemp.LSC.Dodson_poison = "true"; // разговор состоялся
			dialog.text = "Argh... "+pchar.name+", friend, something is very wrong with me...";
			link.l1 = "Steven! Did you drink this whiskey?!";
			link.l1.go = "poison_1";
		break;
		
		case "poison_1":
			dialog.text = "Yes... Bushmills... Giuseppe Fazio brought it for me today, said it was a present from the Narwhal leader... a token of peace...\nAck, fuck it hurts!";
			link.l1 = "That whiskey was poisoned with arsenic!! Chad and Cyclops did it!";
			link.l1.go = "poison_2";
		break;
		
		case "poison_2":
			dialog.text = "Argh... fucker finally got me...";
			if (CheckCharacterItem(pchar, "ultimate_potion"))
			{
				link.l1 = "You are not going to die! Hear me? You're not! Quickly, take this flask. This is the most powerful healing potion in the world, it cures everything. Drink it... now!";
				link.l1.go = "poison_3";
			}
			else
			{
				link.l1 = "Steven...!";
				link.l1.go = "dodson_poison";
			}
		break;
		
		case "dodson_poison": // Акула умирает
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_KillCharacter(npchar);
			SetFunctionTimerCondition("LSC_SetDexterAdmiral", 0, 0, 1, false); // через день Декстера в адмиралы
			if (CheckAttribute(pchar, "questTemp.LSC.CapperDie_Aeva"))
			{
				AddQuestRecord("SharkHunt", "41");
				sld = CharacterFromID("Facio");
				sld.dialog.currentnode = "whiskey";
				sld.greeting = "facio_2";
				sld.quest.poisonnode = 1;
			}
			else AddQuestRecord("SharkHunt", "42");
			pchar.questTemp.Saga.DodsonDie = "true"; // атрибут Саге что Акула погиб
		break;
		
		case "poison_3":
			RemoveItems(pchar, "ultimate_potion", 1);
			Log_Info("Comanche potion was used");
			Log_Info("Poison was cured!");
			PlaySound("interface\notebook.wav");
			dialog.text = "Oh... "+pchar.name+", that stuff's incredible. Still feeling a bit sick, but the pain is almost gone...";
			link.l1 = "An Indian shaman gave it to me. Drink it all, quickly! There we go...";
			link.l1.go = "poison_4";
		break;
		
		case "poison_4":
			LAi_SetStayType(npchar);
			dialog.text = "A miracle... I feel fine! Thank you, friend... I'll remember this!";
			if (CheckAttribute(pchar, "questTemp.LSC.CapperDie_Aeva"))
			{
				link.l1 = "You'd better rest now. You look like Death. That bastard Kapper won't be able to threaten you anymore - I've dealt with him and some of his Narwhal friends, too. Only Marcello Cyclops is left. You said that Fazio brought you the whiskey, right?";
				link.l1.go = "poison_5";
			}
			else
			{
				link.l1 = "You'd better rest now. You look like a dead man. You said Fazio brought you the whiskey?";
				link.l1.go = "poison_7";
			}
		break;
		
		case "poison_5":
			dialog.text = "Yes. I wondered why he looked nervous... thought it was just because he was standing in my august presence, he-he...";
			link.l1 = "Kapper must've forced him into this. All right, I'm going to pay that fat pig a visit and get some information out of him. Rest now, Steven!";
			link.l1.go = "poison_6";
		break;
		
		case "poison_6":
			DialogExit();
			sld = CharacterFromID("Facio");
			sld.dialog.currentnode = "whiskey";
			sld.greeting = "facio_2";
			sld.quest.poisonnode = 1;
			LAi_CharacterDisableDialog(npchar);//запрещаем диалог
			AddQuestRecord("SharkHunt", "40");
		break;
		
		case "poison_7":
			dialog.text = "Yes. I wondered why he looked nervous... thought it was just because he was standing in my august presence, he-he...";
			link.l1 = "Kapper must've forced him into this. I'll get that fat pig eventually, but right now I have to deal with Kapper and Cyclops. I know where they're hiding. Rest now, Steven!";
			link.l1.go = "poison_8";
		break;
		
		case "poison_8":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//запрещаем диалог
			AddQuestRecord("SharkHunt", "43");
		break;
		
		case "clear":
			dialog.text = "Ahoy, "+pchar.name+"! I heard about your dustup with Kapper on the Eva, ha-ha! I'm amazed! To kill Chad and his men, all by yourself... Jan was right about your fighting skills.";
			link.l1 = "Not only have I dealt with Kapper, I also prevented an attempt on your life. You were going to be poisoned, Steven. But it's all right, I took care of it.";
			link.l1.go = "clear_1";
		break;
		
		case "clear_1":
			dialog.text = "Poison me? How?";
			link.l1 = "Chad bought a barrel of Irish Bushmills whiskey from Axel--";
			link.l1.go = "clear_2";
		break;
		
		case "clear_2":
			dialog.text = "Bushmills? This is my favorite one! I haven't drunk it for ages!";
			link.l1 = "And Kapper knew that. He asked his pal, Marcello Cyclops, to buy some arsenic from Sancho Carpentero. Then he and his friends grabbed Fazio and went down into the cargo hold of the Eva. He was going to poison the whiskey and force Fazio to bring it to you as a 'gift from the Narwhals'.";
			link.l1.go = "clear_3";
		break;
		
		case "clear_3":
			dialog.text = "Damn... it would've worked, too; I'd have drink a pint of that whiskey in a heartbeat.";
			if (CheckCharacterItem(pchar, "cask_whisky"))
			{
				link.l1 = "Chad was counting on that. But he failed - he didn't even have time to put the arsenic in it. So... I took the barrel with me. You can have it, unspoiled.";
				link.l1.go = "clear_4";
			}
			else
			{
				link.l1 = "Chad was counting on that. But he failed - he didn't even have time to put the arsenic in it.";
				link.l1.go = "clear_7";
			}
		break;
	
		case "clear_4":
			RemoveItems(pchar, "cask_whisky", 1);
			PlaySound("interface\notebook.wav");
			dialog.text = "Show me... "+pchar.name+", this is real Bushmills! The best Irish whiskey! Argh, I've been a dreaming of it for years!\nYou, my friend.. Damn it, you're a miracle worker! You eliminate Chad, save my life, and bring me a barrel of my favourite whiskey as if it's nothing!\nThis demands a suitable reward.\n (rummaging around) The fuck is it...? Ah! Here, take this. It's called Thor's Hammer, and it's everlasting. Nevermore need you fear your cannons exploding in your face! Your cannoneer is going to love it!";
			link.l1 = "Good God, Steven... thank you! I'm sure he will.";
			link.l1.go = "clear_5";
		break;
		
		case "clear_5":
			GiveItem2Character(pchar, "talisman3"); 
			PlaySound("interface\notebook.wav");
			Log_Info("You have received a 'Thor's hammer' amulet");
			dialog.text = "Now, if you'll excuse me, it's time for me to get friendly with this magnificent whiskey... "+pchar.name+", come and see me tomorrow. In the meantime, I have some thinking to do...";
			link.l1 = "Fine, Steven, I won't keep you from your whiskey, ha-ha!";
			link.l1.go = "clear_6";
			AddQuestRecord("SharkHunt", "53");
		break;
		
		case "clear_6":
			DialogExit();
			NextDiag.CurrentNode = "Total_wait";
			DeleteAttribute(pchar, "questTemp.LSC.Whiskey_clear");
			if (CheckAttribute(pchar, "questTemp.LSC.CyclopDie"))
			{
				SetFunctionTimerCondition("LSC_WhiskeyStoryFinal_1", 0, 0, 1, false); // адмирал зовет
				DeleteAttribute(pchar, "questTemp.LSC.CyclopDie");
			}
		break;
		
		case "clear_7":
			dialog.text = "You did me a good turn, telling me all this. I need to think about your words and Chad's actions... and then I'll call you.";
			link.l1 = "I'll be waiting!";
			link.l1.go = "clear_6";
			AddQuestRecord("SharkHunt", "54");
		break;
		
		case "whyskey_final":
			dialog.text = "Ha, there you are, "+pchar.name+". Now that everybody's here, we can start. I summoned you and Layton to discuss the situation and to decide what to do about the Narwhals.";
			link.l1 = "What do you mean, 'what to do about the Narwhals'?";
			link.l1.go = "whyskey_final_1";
		break;
		
		case "whyskey_final_1":
			dialog.text = "What do you mean, 'what do you mean?' Chad made an attempt on my life with the help of the Narwhals.\nI recognize this as an open act of aggression. That can't go unanswered. Considering that we're on friendly terms with the Rivados, I suggest the following...\nWe formalize our alliance with the Negroes, get our lads together, and wipe out the Narwhals for good and all.\nYou, "+pchar.name+", are going to be our diplomat once again. Talk to Black Eddie and Chimiset, convince them to accept my offer of friendship. Dexter will formulate our battleplans, he knows the island better than anyone. Layton?";
			link.l1 = "";
			link.l1.go = "whyskey_final_2";
		break;
		
		case "whyskey_final_2": // перекидываем ноду Декстеру
			DialogExit();
			sld = characterFromId("Dexter");
			sld.greeting = "";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_CharacterEnableDialog(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "whyskey_final_3":
			dialog.text = "No need to exterminate the Narwhals at the first stroke; we control the island's food.\nForce them to retreat to the San Gabriel, and we can pen them up and starve them. What do you say, "+pchar.name+"?";
			link.l1 = "What do I say? ... I say that you should let the Narwhals off the hook, Steven.";
			link.l1.go = "whyskey_final_4";
		break;
		
		case "whyskey_final_4":
			dialog.text = "... did you get hit on the head before coming here? Did you forget that the men who fought with Chad were Narwhals?";
			link.l1 = "Not all of them. Marcello Cyclops wasn't. Actually, he was loyal to the Rivados - he was a mulatto, after all. I think the only Narwhals that joined Chad were those he could buy with money, or with the lie that you murdered Alan Milrow.";
			link.l1.go = "whyskey_final_5";
		break;
		
		case "whyskey_final_5":
			dialog.text = "And what do you suggest, that I ignore all this?";
			link.l1 = "I suggest I play my role of diplomat... but with the head of the Narwhals, Donald Greenspan. Will you hear me out, Steven?";
			link.l1.go = "whyskey_final_6";
		break;
		
		case "whyskey_final_6":
			dialog.text = "... Go on...";
			link.l1 = "I've learned a lot about the City of Abandoned Ships since I arrived here. The townsfolk made it clear that when it was just the two clans on the island, war was constant. The arrival of your pirates introduced a third power to the island, creating balance and peace for the first time ever. But the Narwhals and Rivados remain strong and a victory will be extremely costly.";
			link.l1.go = "whyskey_final_7";
		break;
		
		case "whyskey_final_7":
			dialog.text = "";
			link.l1 = "The price of the Narwhals' destruction will be the lives of many pirates and Rivados. Besides, Layton said that the siege of San Gabriel will take a long time, and if the Rivados began to feel as if they'd lost too much on the campaign, they'd back out... possibly even turn on us.";
			link.l1.go = "whyskey_final_8";
		break;
		
		case "whyskey_final_8":
			dialog.text = "";
			link.l1 = "Don't forget that both clans are still eager to dominate the island, and not long ago, they were united in fighting you. This war may not end as quickly or predictably as you think. And in the middle of it all are the common folk. Do you truly want to rule over a graveyard?";
			link.l1.go = "whyskey_final_9";
		break;
		
		case "whyskey_final_9":
			dialog.text = "... You make some good points... but you haven't persuaded me yet.";
			link.l1 = "I also need to leave the island somehow; I have to reach the idol of Kukulcan on the seabed. The Rivados can't help me... but maybe the Narwhals can. I've heard they have some smart, talented men among them. They won't help me if they're at war with me.";
			link.l1.go = "whyskey_final_10";
		break;
		
		case "whyskey_final_10":
			if (pchar.questTemp.LSC.Mary != "die") sTemp = "A-ha! I knew you had selfish reasons for wanting peace! And I guess that one of them is that redhead on the Ceres, eh, my friend? Am I right? Don't worry about her, "+pchar.name+", we'll find a safe place for her before the fighting starts.\n";
			else sTemp = "";
			dialog.text = ""+sTemp+" But if you're so determined, fine. Go and see Donald. His residence is in the rear of the Esmeralda. See what the scoundrel has to say.\nIf you're convinced that he and his clan had no part of Chad's scheme... I'll consider peace.";
			link.l1 = "Thank you, Steven. I'm sure this is the right decision.";
			link.l1.go = "whyskey_final_11";
		break;
		
		case "whyskey_final_11":
			DialogExit();
			sld = characterFromId("Grinspy");
			sld.dialog.currentnode = "negotiations"; // ноду Гринспи
			sld = characterFromId("Dexter");
			LAi_SetHuberType(sld);
			LAi_SetHuberType(npchar);
			NextDiag.CurrentNode = "negotiations_wait";
			pchar.questTemp.LSC.Donald_enter = "true";
			AddQuestRecord("SharkHunt", "55");
		break;
		
		case "negotiations_wait":
			dialog.text = "But don't let him off the hook too easily, eh! Those were still his lads with Chad - still Narwhals! Make him lick your boots, get his contrition good and proper!";
			link.l1 = "I will, I will.";
			link.l1.go = "exit";
			NextDiag.TempNode = "negotiations_wait";
		break;
		
		case "peace":
			dialog.text = "So, have you spoken to Donald?";
			link.l1 = "I have, and he confirmed my suspicions. Neither he, nor the clan at large, had anything to do with Chad's plan. All the Narwhals who participated in it were recruited by Kapper. He's very upset and he assures me that he holds you blameless for Alan Milrow's murder, and all that happened after.";
			link.l1.go = "peace_1";
		break;
		
		case "peace_1":
			dialog.text = "Is he prepared to stand before me and say all this to my face?";
			link.l1 = "He swore on the Bible that he would.";
			link.l1.go = "peace_2";
		break;
		
		case "peace_2":
			dialog.text = "Heh, well I'll be damned... So it really does seem like the only bastard to be blamed is my traitorous boatswain...";
			link.l1 = "I am convinced of that, Steven. We don't need this war, nobody does. It'd be no good for business.";
			link.l1.go = "peace_3";
		break;
		
		case "peace_3":
			dialog.text = "(slaps the table) All right, then! It's a deal. If Greenspan comes and kisses my arse, all is forgiven... and there'll be peace.";
			link.l1 = "I'll tell him at once. Steven... I'm glad we averted this war.";
			link.l1.go = "peace_4";
		break;
		
		case "peace_4":
			if (pchar.questTemp.LSC.Mary == "alive") sTemp = "Feel free to bring your Mary over to the San Augustine, I can set aside some quarters for the two of you.";
			else sTemp = "";
			dialog.text = "Wait... "+pchar.name+", I am very glad you showed up here, on this godforsaken Island.\nJan spoke highly of you in his letter... but any expectations I had of you have been well and truly surpassed.\nIf you were in my crew... actually! I offer you Kapper's position, while you're here. You will command my garrison on the Tartarus. "+sTemp+".";
			if (pchar.questTemp.LSC.Mary == "alive") link.l1 = "No, Steven, thank you, but I'm not going to be here much longer. Give the job to some trustworthy lad who's more deserving. And concerning Mary... we're doing fine on the Ceres.";
			else link.l1 = "No, Steven, thank you, but I'm not going to be here much longer. Give the job to some trustworthy lad who's more deserving.";
			link.l1.go = "peace_5";
		break;
		
		case "peace_5":
			TakeNItems(pchar, "gold_dublon", 500);
			Log_Info("You have received 500 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Hard to think of a more deserving or trustworthy lad than you, and despite what you say, I don't think getting off this island will be as easy as you hope.\nBut so be it. Now, I can't let you walk out of here without some reward, so shut up and take these five hundred doubloons.";
			link.l1 = "Thanks!";
			link.l1.go = "LSC_navy";
			AddQuestRecord("SharkHunt", "57");
			pchar.questTemp.Saga.SharkHunt = "find"; //флаг - покушение предотвращено
			sld = characterFromId("Grinspy");
			sld.dialog.currentnode = "negotiations_17"; // ноду Дональду Гринспи
			AddSimpleRumourCityTip("They say that the Admiral respects you, mister...", "LostShipsCity", 15, 2, "LSC", "");
			AddSimpleRumourCityTip("They say that you are the Admiral's loyal friend. Is that true?", "LostShipsCity", 15, 2, "LSC", "");
		break;
		
		case "LSC_navy":
			dialog.text = "Let's talk about our business... Take my rutters. They contain sailing directions that'll let you sail a ship to the island in one piece.\nDon't lose them! Without them, your ship will founder on the reefs or get ripped apart by storms. And remember that you can only approach the island with a relatively small vessel! Longboat, tartane, lugger, schooner, nothing bigger.\nOnce you come back for me, I'll join you and Svenson in your game.\nI still don't believe some sunken Indian idol is going to help you, but... Godspeed, my friend.";
			link.l1 = "It's not God we need to count on, Steven, but Kukulcan. Until we meet again.";
			link.l1.go = "LSC_navy_1";
		break;
		
		case "LSC_navy_1":
			GiveItem2Character(pchar, "LSC_navigation_map");
			dialog.text = ""+pchar.name+"... return as quickly as you can. My storehouses are running low; soon there will be no provision at all. You know what armed, hungry men are capable of?";
			link.l1 = "I have some idea. Farewell.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Dodson_wait";
			AddQuestRecord("LSC", "5");
			// убираем квестовые предметы
			sld = ItemsFromID("key_capper");
			sld.price = 10;
			if (CheckCharacterItem(pchar, "letter_chad")) RemoveItems(pchar, "letter_chad", 1);
		break;
		
		case "Dodson_wait":
			dialog.text = "Have you found a way off the island, "+pchar.name+"?";
			link.l1 = "Not yet, Steven, I'm still working on it.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Dodson_wait";
		break;
		
		// --> информационный блок
		case "Total_wait":
			dialog.text = "Well, what do you have, "+pchar.name+"? Got any interesting news?";
			
			if (!CheckAttribute(npchar, "quest.items") && CheckAttribute(npchar, "quest.takeitems"))
			{
				link.l1 = "Steven, I'd like to ask you to give me back my belongings you confiscated.";
				link.l1.go = "Items";
			}
			if (!CheckAttribute(npchar, "quest.story"))
			{
				link.l2 = "Steven, tell me more about this island.";
				link.l2.go = "Story_island";
			}
			if (!CheckAttribute(npchar, "quest.natan"))
			{
				link.l3 = "Are you sure that Hawk isn't on the island? He came through the idol, so he must be here.";
				link.l3.go = "Natan";
			}
			if (!CheckAttribute(npchar, "quest.whiteboy"))
			{
				link.l4 = "Do you know a man named White Boy?";
				link.l4.go = "Whiteboy";
			}
			if (!CheckAttribute(npchar, "quest.ships"))
			{
				link.l5 = "What territories belong to the Narwhals and Rivados?";
				link.l5.go = "ships";
			}
			if (!CheckAttribute(npchar, "quest.parol"))
			{
				link.l6 = "How can I learn the passwords to get on board the clans' ships?";
				link.l6.go = "parol";
			}
			if (!CheckAttribute(npchar, "quest.map"))
			{
				link.l7 = "Listen, is there a map of the island?";
				link.l7.go = "map";
			}
			if (!CheckAttribute(npchar, "quest.blade"))
			{
				link.l8 = "You have such a beautiful broadsword. I've never seen anything like it before...";
				link.l8.go = "blade";
			}
			link.l9 = "No questions yet. Maybe soon...";
			link.l9.go = "exit";
			NextDiag.TempNode = "Total_wait";
		break;
		
		case "Items":
			dialog.text = "Ah, yes! Completely forgot about them... Your things are upstairs in a chest. You can get them, Layton won't stop you.";
			link.l1 = "Thanks!";
			link.l1.go = "exit";
			npchar.quest.items = "true";
			NextDiag.TempNode = "Total_wait";
			ref location = &Locations[FindLocation(pchar.location)];
			DeleteAttribute(location, "private1.key");
			for (i=1; i<=10; i++) // можно лезть в сундук
			{
				sld = characterFromId("SharkSoldInside_"+i);
				DeleteAttribute(sld, "watchBoxes");
			}
		break;
		
		case "Story_island":
			dialog.text = "This island is over a hundred years old; I've seen caravels on the outer ring whose keels must've been laid in 1550 or earlier.\nThere's a shoal beneath our feet that buttresses the wrecks that founder here, keeps them above water. And even though many ships rot to dust each year, storms and a powerful sea current bring more.\nJustice Island shits, eats, and grows like a thing alive.\nThe first settlers arrived here on de Betancourt's expedition, of which the San Augustine and Tartarus were part. The Tartarus carried a lot of black slaves in her hold, one of whom was a man named Pedro Rivados. He led an uprising against his Spanish captors which failed, and he was sentenced to a slow death: tied to a mast and left to cook in the sun.\nBut his attempt at freedom weakened de Betancourt's crews such that a second uprising succeeded, and they formed the Rivados clan in his honour.\nFearing Rivados dominance of the island, with their savage African ways, the white Christian settlers miraculously managed to rise above their various nationalities and united to form the Narwhal clan.\nHeh, few things'll make white men set aside their differences faster than the threat of playing second fiddle to Negroes.\nThe Narwhals have a lot of mercenaries, soldiers, officers and adventurers in their ranks. Year on year they gather supplies and selectively recruit new men from the shipwrecks that arrive here. You can see the results today: they are a disciplined, professional army - and that's been enough to curb Rivados ambitions about ruling the island.";
			link.l1 = "Are there any connections between the island and the rest of the Caribbean?";
			link.l1.go = "Story_island_1";
		break;
		
		case "Story_island_1":
			dialog.text = "None for the last ten years. To hear people around here tell it, it seems like the weather surrounding the island changed: storms grew more frequent, and the current grew more powerful.\nIt's as if, one day, the island was sealed off from the rest of the Caribbean.\nThe islanders used to trade with the buccaneers of Cuba, buying food with gold and valuables salvaged from the shipwrecks, but no buccaneer has visited Justice Island for a decade.\nWell, none that ever returned, anyway.";
			link.l1 = "Hm. So it seems that Forest Devil and Black Pastor were both right... And why didn't people leave the island when they had the chance?";
			link.l1.go = "Story_island_2";
		break;
		
		case "Story_island_2":
			dialog.text = "Some did, but the majority wanted to stay. A lot of them have made a home here, others were born here and know nothing else.\nSome folks want to leave but are too scared to risk sailing the zone of storms on old, cobbled-together boats.\nAs for the Rivados... well, they're Negroes, and last I checked, it's a white man's world out there. Can you blame them for wanting to stay?";
			link.l1 = "And why did you come here, Dodson? You had a frigate, you were a respected pirate--";
			link.l1.go = "Story_island_3";
		break;
		
		case "Story_island_3":
			dialog.text = "(slams the table) I was being hunted!!\nI was blamed for the murder of Blaze Sharp! By whom, or for what reason, I've no idea.\nSomeone made me a pawn in their game and I was surrounded by enemies, abandoned by my friends, so I had to leave Isla Tesoro and lay low.\nI'd known of this island for a long time, but I couldn't reach it on my frigate; she was too big to bypass the reefs. So, I traded her for a brig.\nI was attacked by the Narwhals and Rivados as soon as I got here - guess the only people Negroes and white men hate more than each other are pirates, he-he. They rowed longboats to my ship at night and fired her.\nWe blasted their tubs to matchwood with our cannons, but the fire did its work - my poor brig was burnt to her frames.\nWe got mad as hell and struck back: we stormed the San Augustine and showed them how corsairs fight! They couldn't hold her and showed us their cowardly backs.\nWe captured San Augustine and discovered that the whole island used her as their storehouse! Overnight, we became the most important clan on the island.\nNow, every fucking Justice Islander has to buy back their own food at a price we name, ha-ha-ha!\nWe also captured two of the clan leaders: Alan Milrow of the Narwhals and a Rivados voodoo man name of Chimiset. My mate Layton spent the next few days scouting the island and then we attacked the Tartarus, the old slave ship.\nNow we hold two vessels and the clans have to deal with us... or starve. Nowadays, we have something like peace, here.\nAs for the citizens... we sell food to them proper cheap - they didn't take up arms against us. Anyway, they seem to like the fact that we balance out the other two clans, somewhat.";
			link.l1 = "Incredible... that's quite a tale!";
			link.l1.go = "exit";
			npchar.quest.story = "true";
			NextDiag.TempNode = "Total_wait";
		break;
		
		case "Natan":
			dialog.text = "I haven't seen him. This is the first I've heard that Hawk is anywhere but Maroon Town.\nIt's possible he could be somewhere on the island or the outer ring without having been seen - certainly enough places to hide - but you'd think he'd have come see me by now...";
			link.l1 = "I see...";
			link.l1.go = "exit";
			npchar.quest.natan = "true";
			NextDiag.TempNode = "Total_wait";
		break;
		
		case "Whiteboy":
			dialog.text = "White boy? Hm... no, I haven't heard the name. But it doesn't mean he's not here - is it my job to know all the local muck?";
			link.l1 = "No, no. All right, I'll ask someone else.";
			link.l1.go = "exit";
			npchar.quest.whiteboy = "true";
			NextDiag.TempNode = "Total_wait";
		break;
		
		case "ships":
			dialog.text = "The island is divided between the Narwhals, Rivados and my pirates, with a neutral area between us.\nI control the San Augustine and Tartarus.\nRivados hold Protector, which is their leader's residence, Fury, their barracks, and Velasco, their warehouse. Strangers are forbidden to pass, you must say a special password in order to get there.\nNarwhals hold a lot of ships: Esmeralda is a shop and the residence of their leader; the San Gabriel and Phoenix, run by some kind of scientist; and the Ceres, their smithy.\nEvery ship except the Esmeralda is a restricted area; you must say a password before they let you in. Same goes for the Rivados. And the passwords change every week.\nThe rest of the ships are considered neutral territory, and are where the citizens live.\nWho am I forgetting...? Oh, the Fleuron is a tavern run by a man named Sancho Carpentero, and the Gloria is the local church - Brother Julian is the pastor there.";
			link.l1 = "That's a lot to remember... I guess I'll have to learn the city by walking it.";
			link.l1.go = "exit";
			npchar.quest.ships = "true";
			NextDiag.TempNode = "Total_wait";
			AddQuestRecord("LSC", "2");
		break;
		
		case "parol":
			dialog.text = "By getting in bed with the clans. But since you're not tough enough for the Narwhals or black enough for the Rivados, go to an old frigate called the Caroline and find a fat bastard named Giuseppe Fazio. He's some sort of diplomat here.\nI don't know what he did before arriving on the island, but the man's a proper scoundrel. He does business with everyone. The clans use him as a mediator, so he's always given the weekly passwords.\nFazio's greedy, ready to eat himself for a single doubloon. You can ask him for the current password to either Rivados or Narwhal territory, but be prepared to pay with gold.";
			link.l1 = "Caroline... Fazio... all right, thanks.";
			link.l1.go = "exit";
			npchar.quest.parol = "true";
			NextDiag.TempNode = "Total_wait";
			AddQuestRecord("LSC", "3");
		break;
		
		case "map":
			dialog.text = "Dexter owns one. He's my first mate. He made a detailed map right after our arrival. Go upstairs and talk to him, see if he'll sell it to you.";
			link.l1 = "Got it. Thanks!";
			link.l1.go = "exit";
			npchar.quest.map = "true";
			NextDiag.TempNode = "Total_wait";
			sld = characterFromId("Dexter");
			sld.quest.map = "true";
		break;
		
		case "blade":
			dialog.text = "Ha! A trophy from Alan Milrow, head of the Narwhal clan.\nJurgen, the Narwhal smith, made it from some rare iron they found at the bottom of the sea. It doesn't rust, never grows blunt, and can cut two bodies in half with a single swing.\nThis sword's one of the few good things to come of this expedition, and for that reason, I'll not part with it. Not for any price.";
			link.l1 = "Is Jurgen able to make another broadsword like this?";
			link.l1.go = "blade_1";
		break;
		
		case "blade_1":
			dialog.text = "Pfft! Not likely. Jurgen is a Narwhal; he's loyal to his clan and never makes weapons for outsiders.\n Besides, you'd need some of that special iron to make a second sword. That iron can only be found at the bottom of the sea, and unless you've got gills, how are you going to reach it? So, forget about it.";
			link.l1 = "I see... pity...";
			link.l1.go = "exit";
			npchar.quest.blade = "true";
			NextDiag.TempNode = "Total_wait";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive")
			{
				sld = characterFromId("Schmidt");
				sld.quest.narval_blade = "begin"; // возможность сделать 'Нарвал' для Мэри
			}
		break;
		// <-- информационный блок
		
		case "return":
			chrDisableReloadToLocation = true;//закрыть локацию
			dialog.text = ""+pchar.name+"! You mad bastard, ha-ha-ha, you made it!! I saw your sails on the horizon! How are you, friend? How was the trip?";
			link.l1 = "Heh, good to see you too, Steven. I lived.";
			link.l1.go = "return_1";
		break;
		
		case "return_1":
			dialog.text = "Good! God's teeth, I'm ready to be off this island and share a drink with Forest Devil.\nLayton will stay on as Admiral - he has already taken my chair, ha-ha! I think he genuinely likes this place.";
			link.l1 = "You once said that many people who land here end up preferring life here to the outside world. Are you surprised Dexter's no different?";
			link.l1.go = "return_2";
		break;
		
		case "return_2":
			dialog.text = "Eh, not 'surprised'... just sad to lose him. You couldn't ask for a finer first mate.\nWell... when do you plan to weigh anchor?";
			link.l1 = "Soon. Get on my ship, Steven. We'll set sail as soon as I finish my business here.";
			link.l1.go = "return_3";
		break;
		
		case "return_3":
			dialog.text = "You're the skipper! Oh it'll be good to feel the swaying of a deck beneath my feet again!";
			link.l1 = "...";
			link.l1.go = "return_4";
		break;
		
		case "return_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LSC_SetDodsonPassenger", -1);
		break;
		
		case "return_5":
			dialog.text = "Blueweld... strange... part of me thought I'd never see green trees and fields again...\n...\n ... Ahem, well... I'll go see Svenson. You should also see him and talk about the future. Hot days await us, eh?";
			link.l1 = "No doubt, Steven. Fair winds to you!";
			link.l1.go = "return_6";
		break;
		
		case "return_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "houseS1", "none", "", "", "OpenTheDoors", -1);
			sld = ItemsFromID("LSC_navigation_map");
			sld.price = 1000; // лоцию можно выкладывать 270912
			sld = ItemsFromID("keys_skel");
			sld.price = 3000; // отмычки можно выкладывать 270912 
			pchar.questTemp.LSC.Dios = "true"; // можно отдать лоцию Диосу
			CloseQuestHeader("LSC"); // 280313
		break;
		
		// Тени прошлого
		case "shadows":
			dialog.text = "Sure, I'll do what I can! Go on.";
			link.l1 = "Steve, take a look... A shark's tooth. Don't tell me that it's unfamiliar to you!";
			link.l1.go = "shadows_1";
		break;
		
		case "shadows_1":
			RemoveItems(pchar, "shark_teeth", 1);
			dialog.text = "Ha! You're right, it is my tooth - or rather, it's the tooth of a shark I killed to impress a girl. That's why they call me 'Shark' Dodson.\nFew are able to accomplish such a feat underwater with a simple sabre, but I was young and stupid, and Beatrice Sharp was the most beautiful girl in the Caribbean...\nHow did you get it?";
			link.l1 = "A former executioner of St. John's gave it to me. A man was butchered with it; his name was Joshua Leadbeater.";
			link.l1.go = "shadows_2";
		break;
		
		case "shadows_2":
			dialog.text = "Mm-hmm, you've found your butcher; I cut his throat with this tooth.\nI was heartbroken by Beatrice's death, and I believed Leadbeater to be the only guilty man within my reach.\nI found some papers on him after he'd gurgled his last that clarified a few things. He had every right to crave revenge.\nBlaze's sister was just in the wrong place at the wrong time. Mask shouldn't have been blamed for her death - he was only interested in Butcher. Truthfully... I regret murdering him.\nThat bitch Jessica set the whole thing up.";
			link.l1 = "You still have those papers?";
			link.l1.go = "shadows_3";
		break;
		
		case "shadows_3":
			dialog.text = "Of course not. I had no need of them. But I can tell you why Mask was chasing Butcher, if you're interested.";
			link.l1 = "I am, very much so. Here, give me ink and a quill and I'll write it all down.";
			link.l1.go = "shadows_4";
		break;
		
		case "shadows_4":
			dialog.text = "Sure. Listen, then. Joshua Leadbeater was a British captain in command of the frigate Neptune, which has since become legend...";
			link.l1 = "...";
			link.l1.go = "shadows_5";
		break;
		
		case "shadows_5":
			DialogExit();
			SetLaunchFrameFormParam("One hour later...", "Saga_FinalLedbitterStory", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 10); //крутим время
			RecalculateJumpTable();
		break;
		
		case "shadows_6":
			AddQuestRecordInfo("Mask", "1");
			dialog.text = "... however, Leadbeater survived and was saved by a passing ship - albeit disfigured by his wounds.\nHe wore a mask ever since, and finding and punishing the author of his misfortunes became his life's goal.";
			link.l1 = "I see... all right, I think I've gotten every word down. I'll re-read later. It's a sad story. Did you know Jessica?";
			link.l1.go = "shadows_7";
		break;
		
		case "shadows_7":
			dialog.text = "Sure! She accompanied Butcher on all his voyages until he dumped her for Beatrice. Jess never forgave him.\nThey called her Butcher's talisman, because as long as she was with him, she brought him luck.\nAs soon as he left her on Barbados, his business went bad; the booty dried up and the Neptune became a frequent guest at the Isla Tesoror shipyard. Though that can be better explained by the fact that Butcher spent all his time in his cabin with Beatrice instead of on his quarterdeck.\nBeatrice wasn't like Jessica: she didn't crave adventure and battle- though Nicolas taught her fencing and seamanship. She was a romantic, wasn't hard enough to be a pirate.\nThis life wasn't for her, and in the end, it killed her.";
			link.l1 = "And what about Jessica?";
			link.l1.go = "shadows_8";
		break;
		
		case "shadows_8":
			dialog.text = "Oh, she was something! Every sailor on the Neptune obeyed her orders without question, and not just because she was the captain's girl.\nJess was a master fencer and navigator - learned everything she knew from Butcher, and even exceeded him. She was tough and fearless, and blessed with looks that would make angels blush.\nA lot of men wanted her, but she only wanted Butcher. Chasing her was risky; she was likely to reward unwanted interest with a free fencing lesson, and for many, it was the last they ever received.\nJess owned a very special sword, the only one of it's kind in the Caribbean. I have no clue where she got it. The flame-bladed sword. The slightest touch of its blade leaves the most terrible wound.\nJess was an adventurer - not by birth, but by vocation. If you want to learn more about her, there's a friend of yours can tell you much more about her than.";
			link.l1 = "Really? And who is that man?";
			link.l1.go = "shadows_9";
		break;
		
		case "shadows_9":
			dialog.text = "Jan Svenson.\nOld Forest Devil will never admit it, but he had plans for Jessica. This was just after he'd claimed the Spanish Main for himself and his fame was known throughout the Caribbean, so he figured the tigress was as good as his.\nAfter Butcher got rid of Jess, Jan started visiting Barbados on a regular basis. That set the Englanders' nerves on edge; as you know, Jessica was the daughter of a Bridgetown planter.\nWe all knew what he intended, and we knew it could end very badly, but we didn't say anything. Jan may sit on his arse in Blueweld these days, but speak the slightest ill of him back then and he'd turn up at your door with a poison blade and a band of hard buccaneers, he he...\nJan's plans came to naught: Jess couldn't live with the way Butcher treated her, so she took her revenge a year later with a help of Mask.\nIn the end, her vengeance destroyed her, along with Mask, Beatrice, and Butcher.";
			link.l1 = "Butcher's still alive.";
			link.l1.go = "shadows_10";
		break;
		
		case "shadows_10":
			dialog.text = "... Bullshit...";
			link.l1 = "Steven, Captain Butcher is still alive. Jacob Jackman and Henry the Hangman paid the executioner a visit. The hanging was faked. I have proof.";
			link.l1.go = "shadows_11";
		break;
		
		case "shadows_11":
			dialog.text = "Faked... So, where's Butcher now?!";
			link.l1 = "He calls himself Lawrence Beltrope now, and he lives in Port Royal. He's still dangerous though; Jackman, who caused so much trouble for the Brethren, was acting under Butcher's command.";
			link.l1.go = "shadows_12";
		break;
		
		case "shadows_12":
			dialog.text = "Damn me! The quartermaster rejoined his captain at long last!\nBeltrope, you say... wait! Now I see why there was a strange record of an interrogation among Blaze's papers... It looks like Blaze also found out about Butcher-Beltrope...";
			link.l1 = "What are you talking about?";
			link.l1.go = "shadows_13";
		break;
		
		case "shadows_13":
			dialog.text = "After I took this residence, I rummaged through Blaze's old papers. I found the record of an interrogation of some Samuel Brooks.\nThere was mention of the 'adventures of Thomas Beltrope,' and that he was known as a pirate and a close friend of Nicolas Sharp!\nIt seems that Thomas was Butcher's father.";
			link.l1 = "Interesting... looks like Sharp's and Beltrope's children continued their parents' line of work...";
			link.l1.go = "shadows_14";
		break;
		
		case "shadows_14":
			dialog.text = "Seems so... But tell me, my friend, why are you so interested in the deeds of the dead?";
			link.l1 = "I need papers - papers which would confirm that Helen MacArthur is the daughter of Beatrice Sharp and that she has all rights to her estate. I don't care that she is also Beltrope's daughter.";
			link.l1.go = "shadows_15";
		break;
		
		case "shadows_15":
			dialog.text = "There's nothing about Helen MacArthur in either Leadbeater's papers or Blaze's archives.\nIt's strange that Beatrice didn't tell Blaze about the birth of his niece, that's not like her...";
			link.l1 = "Listen, perhaps there's something else in Sharp's papers? I need every detail!";
			link.l1.go = "shadows_16";
		break;
		
		case "shadows_16":
			dialog.text = "Hm, I guess... According to Blaze's notes, he'd been trying to find the island where his sister died.\nThere're papers concerning Leadbeater's punitive expedition... Nothing interesting, except for latitude numbers.\nThis parallel crosses the northern Caribbean sea. But there's no longitude.\nObviously, Blaze's search failed; you can't imagine how many small islands there are along that latitude.";
			link.l1 = "Tell me the numbers.";
			link.l1.go = "shadows_17";
		break;
		
		case "shadows_17":
			dialog.text = "Let's see... here: latitude 21 degrees 32 minutes North.\nBut I don't see what use it is without a longitude.";
			link.l1 = "Let me worry about that. Thank you, Steven, for your story. 'Till next time!";
			link.l1.go = "shadows_18";
		break;
		
		case "shadows_18":
			DialogExit();
			pchar.questTemp.Saga.Shadows = "jessika";
			AddQuestRecord("Shadows", "6");
			LAi_SetHuberType(npchar);
			NextDiag.CurrentNode = "First time";
			sld = characterFromId("Svenson");
			sld.quest.jessika = "true";
			// рифы доступны для посещения
			i = FindIsland("RockIsland");
			Islands[i].visible = true;
			Islands[i].reload_enable = true;
			// для любителей самостоятельно добавлять локаторы
			LAi_LocationDisableOfficersGen("Shore67", true);//офицеров не пускать
			// и сразу прерывание
			pchar.quest.Saga_Jess_Island.win_condition.l1 = "location";
			pchar.quest.Saga_Jess_Island.win_condition.l1.location = "Shore67";
			pchar.quest.Saga_Jess_Island.function = "Saga_JessikaIsland"; 
			// активируем квест хронометра Алекса
			pchar.questTemp.AlexClock = "dodson"; // 280912
		break;
		
		// суп из черепахи
		case "terrapin":
			dialog.text = "You could say that. Now, about Tortuga.\nThe island was named such because it resembles a turtle. Well, Levasseur's been thickening turtle's shell for twelve years.\nHis crowning achievement is Fort La Roche. A frontal attack is suicidal; the fort's heavy cannons can smash even ships-of-the-line.\nMaking a soup out of this beauty won't be easy. The Spanish have been trying for a very long time and they've not yet succeeded.";
			link.l1 = "Svenson promised me his aid in taking down Levasseur. He said you'd have a plan so what is is?";
			link.l1.go = "terrapin_1";
		break;
		
		case "terrapin_1":
			dialog.text = "I've had men walking the streets of Tortuga for the last few weeks and they've obtained a lot of interesting information. I have good news for you, pal: it seems you won't have to face the cannons of La Roche. We're not the only ones fed up with Levasseur; he has friends who want him dead.";
			link.l1 = "Go on...";
			link.l1.go = "terrapin_2";
		break;
		
		case "terrapin_2":
			dialog.text = "It's pretty well known that Levasseur is fond of young girls. Once he's had his fun, they disappear.\nThe main supplier of slaves on Tortuga is Robert Marten of the galleon Voltigeur. His mate, Levasseur's nephew Henri Thibaut, picks out the prettiest girls in the port for his patron.\nNot long ago, Marten got his hands on a beauty from an English brig name of Molly Jones. He delivered her to Levasseur's nephew, Thibaut, at night in some secret grotto on Tortuga.\nThe crew was told that the girl died of a heart attack and her body was thrown overboard, though of course that body probably belonged to some poor harbour doxy they paid for and then murdered.\nAll in all, it looks like Marten and Thibaut decided to keep Molly to themselves instead of handing her over to Levasseur. If Levasseur finds out, there'll be hell to pay.";
			link.l1 = "Are you sure we can exploit this? I'm sure Marten and Thibaut realize the risk they're running; they'll have taken precautions.";
			link.l1.go = "terrapin_3";
		break;
		
		case "terrapin_3":
			dialog.text = "True. But every chain has a weak link.\nThree days ago, a former Voltigeur crewman named Fernand Lucas drank too much in Basse-Terre's tavern and said a lot of interesting things...\nTurns out Molly Jones asked him to ask her brother in St John's for help. But Lucas never reached him.\nHe escaped his captain and is now in Guadeloupe drinking to forget his cowardice.\nAntigua is not a safe place for French pirates - remember that! Colonel Fox swore to hang one on every palm tree on the island after his wife died at the hands of a French corsair, and his marines will do everything in their power to fulfill that desire.";
			link.l1 = "Stay focused, Steven... Tell me about Marten and Thibaut. Why would they take such a risk? Were Molly's charms so strong, or did these slavers actually show mercy for a change?";
			link.l1.go = "terrapin_4";
		break;
		
		case "terrapin_4":
			dialog.text = "I know that scum Marten very well. If he's taking this risk, that means there's either gold or self-preservation involved.\nMaybe Marten thinks he can get a huge ransom for her - which is unlikely; the girl arrived on Tortuga in servant's garb.\nOr maybe... Ha! I wonder who Marten would be more afraid of than Levasseur...?";
			link.l1 = "Hmm... tell me more about Thibaut.";
			link.l1.go = "terrapin_5";
		break;
		
		case "terrapin_5":
			dialog.text = "Don't know much about the man, only that Levasseur trusts him enough to make him his heir.\nIt's unclear where the girl is being held and why Thibaut allows Marten such a long leash, but the answer to this little riddle might help us win this game without storming Tortuga. You are French, so I guessed you would prefer it this way.\nBut you should hurry, there's no telling when Lucas's drunken ramblings will catch a ship bound for Tortuga, and if Levasseur gets wind of this before we can act on it... we're fucked!";
			link.l1 = "I'll leave immediately.";
			link.l1.go = "terrapin_6";
		break;
		
		case "terrapin_6":
			dialog.text = "Here's what you do: visit Antigua first. Molly sent Lucas there to find her brother; maybe the brother has information that can help you.\nAfter that, get your arse to Guadaloupe. Find Lucas and learn everything you can about Marten, Thibaut, Voltigeur, and Molly.";
			link.l1 = "Thanks, Steven. Antigua, then Guadaloupe.";
			link.l1.go = "terrapin_7";
		break;
		
		case "terrapin_7":
			DialogExit();
			AddMapQuestMarkCity("SentJons", true);
			AddMapQuestMarkCity("BasTer", true);
			AddQuestRecord("Terrapin", "1");
			pchar.questTemp.Terrapin = "baster";
			pchar.questTemp.Terrapin.SJ_count = 0;
			// прячем Фокса
			sld = characterFromId("Fox");	
			ChangeCharacterAddressGroup(sld, "none", "", "");
			// садим в таверну Робера Мартэна
			float fMft = MOD_SKILL_ENEMY_RATE/10;
			sld = GetCharacter(NPC_GenerateCharacter("Rober", "Marten", "man", "man", 30, FRANCE, -1, true, "quest"));
			FantomMakeCoolSailor(sld, SHIP_GALEON_L, "Voltigeur", CANNON_TYPE_CANNON_LBS20, 90, 90, 90);
			FantomMakeCoolFighter(sld, 30, 80, 80, "blade_19", "pistol5", "bullet", 150);
			sld.name = "Rober";
			sld.lastname = "Marten";
			sld.dialog.FileName = "Quest\Sharlie\Terrapin.c";
			sld.dialog.currentnode = "Rober";
			sld.greeting = "pirat_common";
			TakeNItems(sld, "potion2", 1);
			TakeNItems(sld, "potion3", 2);
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "Tireless");
			SetCharacterPerk(sld, "HardHitter");
			SetCharacterPerk(sld, "Sliding");
			SetCharacterPerk(sld, "BladeDancer");
		
			SetCharacterPerk(sld, "Gunman");
			SetCharacterPerk(sld, "GunProfessional");
			SetCharacterPerk(sld, "MusketsShoot");
			SetCharacterPerk(sld, "LongRangeGrappling");
			SetCharacterPerk(sld, "GrapplingProfessional");
			SetCharacterPerk(sld, "HullDamageUp");
			SetCharacterPerk(sld, "SailsDamageUp");
			SetCharacterPerk(sld, "CrewDamageUp");
			SetCharacterPerk(sld, "CriticalShoot");
			SetCharacterPerk(sld, "LongRangeShoot");
			SetCharacterPerk(sld, "BasicBattleState");
			SetCharacterPerk(sld, "AdvancedBattleState");
			SetCharacterPerk(sld, "ShipDefenseProfessional");
			SetCharacterPerk(sld, "ShipSpeedUp");
			SetCharacterPerk(sld, "ShipTurnRateUp");
			SetCharacterPerk(sld, "WindCatcher");
			SetCharacterPerk(sld, "SailsMan");
			SetCharacterPerk(sld, "Doctor1");
			SetCharacterPerk(sld, "Doctor2");
			sld.MultiFighter = 1.0+fMft; // мультифайтер
			LAi_SetSitType(sld);
			UpgradeShipParameter(sld, "SpeedRate");//апгрейдить скорость
			UpgradeShipParameter(sld, "TurnRate");//манёвренность
			FreeSitLocator("Baster_tavern", "sit1");
			ChangeCharacterAddressGroup(sld, "Baster_tavern", "sit", "sit1");
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("Terrapin_LateBaster", 0, 0, 20, false); // таймер
			}
			else SetFunctionTimerCondition("Terrapin_LateBaster", 0, 0, 10, false); // таймер
			
			// Квест "Погасшая Звезда" провалена, всё удаляем
			if (GetCharacterIndex("Longway") != -1 && CheckPassengerInCharacter(pchar, "Longway"))
			{
				CloseQuestHeader("PZ");
				DeleteAttribute(pchar, "questTemp.PZ_Etap5_Start");
				DeleteAttribute(pchar, "questTemp.PZ_Etap4_Start");
				DeleteQuestCondition("PZ_Etap5_Start");
				DeleteQuestCondition("PZ_LongwayCapstervilleDialog");
				DeleteQuestCondition("PZ_OhotaNaZvezdu_Kapstervil");
				DeleteQuestCondition("PZ_OhotaNaZvezdu_Yamaika");
				DeleteQuestCondition("PZ_Beliz_PoterpKrushenie");
				pchar.questTemp.PZ_ProvalFinal = true;
			}
		break;
		
		case "terrapin_8":
			dialog.text = "Go on!";
			link.l1 = "I found Molly's brother in St. John's. It's Colonel Fox's clerk. But something's strange... He described his sister Molly as a well known hag about as tall as you - but not as pretty. She is the maid of Fox's daughter, Catherine, and she was with her in England until recently...";
			link.l1.go = "terrapin_9";
		break;
		
		case "terrapin_9":
			dialog.text = "";
			link.l1 = "As for Catherine, she's indeed known for her beauty and she was going to visit her father on his birthday, but the squadron carrying her was delayed...";
			link.l1.go = "terrapin_10";
		break;
		
		case "terrapin_10":
			dialog.text = "";
			link.l1 = "Colonel Fox forbade her from leaving England without an escort squadron, so Molly Jones can't be Thibaut's prisoner. So who is she...?";
			link.l1.go = "terrapin_11";
		break;
		
		case "terrapin_11":
			dialog.text = "Hm... Damned if I know. Maybe she's some other Molly Jones - not the one you've been asking about.\nThough... there are too many coincidences. I don't believe this is all an accident!\nYou know... I have a suspicion, but...";
			link.l1 = "What do you mean? Tell me!";
			link.l1.go = "terrapin_12";
		break;
		
		case "terrapin_12":
			dialog.text = "... What if Catherine disobeyed her father's orders and set sail without an escort? Last month was quite stormy, the Albatross could've gotten damaged and became easy prey for Marten.\nI suspect Catherine withheld her real name from Marten - you can understand why - and gave him Molly's name instead!";
			link.l1 = "Damnation! If that's the case, then everything adds up... but it's a hell of a supposition!";
			link.l1.go = "terrapin_13";
		break;
		
		case "terrapin_13":
			dialog.text = "That's what I mean, pal. I could be wrong, but...";
			link.l1 = "... but if it's true, it changes everything! We could ask the English for support, let the bayonets of the Sea Foxes clear the way for us!";
			link.l1.go = "terrapin_14";
		break;
		
		case "terrapin_14":
			dialog.text = "Calm down, "+pchar.name+"! We need proofs. As I said, I could be wrong, and Catherine could still be in London, waiting for an escort to set sail.\nThe English have problems of their own; they won't risk attacking La Roche. But if we're right, and Colonel Fox finds out what's happened to his daughter...\nHe'll set up a blockade around Tortuga and wait for reinforcements. Then he'll attack the city. Sea Foxes are fearsome in close-quarters, so there'll be lots of casualties - army and civilian.\n And in the end, I'm sure he'll raise the English flag above the ruins of Tortuga three days later. Do you really want that?";
			link.l1 = "No... no I don't. Now I see what ransom Marten is talking about.";
			link.l1.go = "terrapin_15";
		break;
		
		case "terrapin_15":
			dialog.text = "We need to be careful. We're not even sure Marten is aware of Catherine's true identity. Blackmailing Colonel Fox would be suicide, especially with Cromwell's squadron arriving in the Caribbean.\nIf Catherine dies because of us, we would be in the deepest of shit. Colonel Fox could destroy the Brethren of the Coast if he believed we killed his daughter.\nBut if, in the end, Catherine has to die, we need to make sure it doesn't look like our doing, and that she helps us achieve our goals.\nThe best outcome would be to deliver the girl to her father. Her saviour will be well rewarded, he-he...";
			link.l1 = "Steven, you're a genius! I'm off to Tortuga. I'll confirm whether Molly is Catherine Fox.";
			link.l1.go = "terrapin_16";
		break;
		
		case "terrapin_16":
			dialog.text = "Don't waste time, "+pchar.name+". And if it turns out I'm right, make sure that girl stays alive.";
			link.l1 = "I'll do all I can.";
			link.l1.go = "terrapin_17";
		break;
		
		case "terrapin_17":
			DialogExit();
			AddQuestRecord("Terrapin", "7");
			pchar.questTemp.Terrapin = "tortuga1";
			pchar.questTemp.Terrapin.Room_close = "true": // не пускать в комнату таверны
		break;
		
		case "guardoftruth":
			dialog.text = "Ho-Ho! Spit it out, friend! We will solve any problem for damn sure!";
			link.l1 = "I will get straight to the point, then. Do you know Miguel Dichoso?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "I know him. That Spanish don sold me a great ship - a frigate. Eh, what a vessel she was, just imagine...";
			link.l1 = "Let me guess, a unique hull, sixteen knots max speed? 'Santa Quiteria'?";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "You are right about her hull and speed, but the name was different - 'San Martin'. I paid him a huge amount of gold, it was everything I had. All my savings went straight into that rogue's pockets.";
			link.l1 = "Are you sure that her name was San Martin and not Santa Quiteria? And when did you buy it? And why are you calling him a rogue?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "So many questions! I will answer them all in the order: I am sure that it was San Martin. I personally had helped Alexus's workers to get rid of a plank with that papist name from the stern. I named her 'Fortune' - a much more suitable name for such princess\nI bought her not long before Blaze Sharp was murdered in winter 1654. Why did I call Miguel like that? Because that son of a bitch had managed to steal the ship from Spanish military base of Providence. We had arranged quite a show for them, right in front of San Juan's fort. I sacrificed two half-dead luggers in order to make the fight more trustworthy. we burned and flooded the ships, simulating the battle with the frigate. And as the darkness descended - we drove the San Martin to Isla Tesoro.. I got the ship and Dichoso got money. He told his high command that the frigate was sunk in a battle with pirates, San Juan's commandant verified that.";
			link.l1 = "So that is how Spanish dons fill their pockets! What a scoundrel! Tell me, had it really happened in winter 1654? Maybe in spring? And was the frigate damaged by storms?";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "In winter... Damn it, I am not totally sure - could be in spring, too. I don't remember really. The frigate wasn't damaged, she was all new. She looked newly built. When I think of her, I just want to cry with vexation...";
			link.l1 = "Why? Yeah, and where is your beautiful frigate now?";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "Because she is gone from me. They set me up, put my talisman on Blaze's corpse and spread the word that I was the murderer. Then I heard that Marcus Tyrex - our code keeper - is going to hand me a black mark. So I decided to escape from that mess for a while at the Island of Justice, where you had found me\nI couldn't get there on a frigate, so I pledged her to Black Pastor in exchange for a brig filled with provision, I didn't have much coin after my deal with that sly Dichoso. I was hoping to sell provision and to return to Isla Tesoro in a month or two... Well, you know the rest.";
			link.l1 = "And Black Pastor didn't wait for you, so he sold her";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "Precisely. She was bought by one English, or to be more specific, by one Scot, William Paterson. I could try to return the girl, sure, but this highlander is a serious bird, a captain of Royal Navy, a good friend of colonel Fox. Besides, he was doing business with Jackman same way you were with Svenson\nThe Scot has a squadron... screw it, I will not see my ship again.";
			link.l1 = "I see. Don't you know where is that Dichoso now?";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "I have no idea. I have never seen him after I bought my Fortune.";
			link.l1 = "And why didn't Miguel offer to buy it to someone else? How about Tyrex, Barbazon, Sharp? Or Paterson?";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = "I have no idea. Paterson wasn't here that time as far as I remember. Zachariah, Jacques and Marcus would have never agreed and I... I really liked the frigate!";
			link.l1 = "I understand that... I don't understand a thing. Puzzles everywhere...";
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			dialog.text = "Delving in the past again? What island do you want to take this time? Ha-ha-ha!";
			link.l1 = "There is one island... Though I can't find a way to it yet. Fine, Steven, thanks for your information! Farewell!";
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			dialog.text = "Good luck, "+pchar.name+"!";
			link.l1 = "...";
			link.l1.go = "guardoftruth_11";
		break;
		
		case "guardoftruth_11":
			DialogExit();
			AddQuestRecord("Guardoftruth", "60");
			pchar.questTemp.Guardoftruth.Archy = "guadeloupe";
			// маленькая развлекуха
			pchar.quest.GuardOT_cabinattack.win_condition.l1 = "EnterToSea";
			pchar.quest.GuardOT_cabinattack.function = "GuardOT_PrepareCreateBandosInCabin";
		break;
		
		case "tieyasal":
			dialog.text = "And I am glad to help you, as always. What do you want this time, "+pchar.name+"?";
			link.l1 = "It's again about your old friend Miguel Dichoso. I am aware that he was seen on Isla Tesoro again. Can't you help me to find him?";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Ho, friend, I didn't know that, actually. I haven't seen him here. I haven't seen him since I bought 'Fortune' from him. And why do you need that Spanish don?";
			link.l1 = "I need him. Miguel knows the way to an old Indian city. I am really eager to get there.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = "Just as always, my friend, you are going to drag yourself into the mess. Alas, I can't help you. I advice you to walk around the settlement and ask people, perhaps someone had seen him. He is a famous man here, you know.";
			link.l1 = "Hey, Steven, can you at least tell me how he looks like?";
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			dialog.text = "Well, he is twenty five - twenty eight years old, about as tall as you, dark eyes, no wig. There is a saber scar on his right cheek.";
			link.l1 = "Hm. You know, there are many people who would fit that description.";
			link.l1.go = "tieyasal_4";
		break;
		
		case "tieyasal_4":
			dialog.text = "There are no other unique details about him. He is self-confident, insolent and very dangerous. There were gossips about him...";
			link.l1 = "I see. Fine, I will ask around about him. Good luck, Steven!";
			link.l1.go = "tieyasal_5";
		break;
		
		case "tieyasal_5":
			DialogExit();
			AddQuestRecord("Tieyasal", "2");
			npchar.quest.tieyasal = "true";
		break;
		
		// Jason НСО
		case "patria":
			dialog.text = "Ho-ho! You've come to the right place! Spit it out!";
			link.l1 = "There is a fella that has no fear of pirates. He doesn't take them seriously. He needs to be taught a lesson om respect. Remember, don't kill him.";
			link.l1.go = "patria_1";
		break;
		
		case "patria_1":
			dialog.text = "Huh! It's noone else than the old man Charles! I bet you got yourself into some affair again! Let's get to the details, who's the target this time and what shall we teach him";
			link.l1 = "A guest from Europe, an inspector of the French Ministry of Finance - baron Noel Forget. He wants to establish a French Trading Company here, but me and a close friend of mine object against it. We tried to convince the Baron, that trading here would be very risky because of the Dutch, English and especially pirates after Levasseur was defeated, but he didn't listen. We need to strike fear into him, to make him feel it on his own skin.";
			link.l1.go = "patria_2";
		break;
		
		case "patria_2":
			dialog.text = "Yes-yes... An actual baron!.. Will we assault his ship?";
			link.l1 = "Here's the plan: his vessel will depart to Capsterville from Port-au-Prince soon. You have to intercept the Baron after his departing and take him as a hostage. It would be better if you didn't sink the ship and avoided killing crew. The French are our friends, after all. Will you be able handle that?";
			link.l1.go = "patria_3";
		break;
		
		case "patria_3":
			dialog.text = "Well, I can't promise anything. But I'll try. What ship is it?";
			link.l1 = "A brig called 'Favory'.";
			link.l1.go = "patria_4";
		break;
		
		case "patria_4":
			dialog.text = "A brig is no match for my frigate. We'll easily deal with them. If it surrenders, I'll let everyone live.";
			link.l1 = "Perfect. Strike fear and offer them to yield. Afterwards, send the Baron to the rat-infested hold. Try to find the filthiest place you can, but keep him there no longer than a day, or else he could get sick and die. Then accomodate him in the cabin, go to the Isla Tesoro, and lock in some secluded place. Dress some of your men as captured French merchants and make them to act like ones. For three days straight, they should tell him all about how the ruthless pirates chase them, rob them, demand ransoms, torture them... with all the details required.";
			link.l1.go = "patria_5";
		break;
		
		case "patria_5":
			dialog.text = "Ha-ha-ha! This must be the funniest job I've ever taken on since a very long time! Well then, I will find such actors, pal. Have no doubt, after their stories your baron will crap his pants! They will show him scars from cutlasses and heated ramrods... ";
			link.l1 = "Nailed it. Then you will force him to write a letter to Poincy, asking for ransom. Thirty five hundred thousand for such a big shot is not that much.";
			link.l1.go = "patria_6";
		break;
		
		case "patria_6":
			dialog.text = "Good. What will we do next?";
			link.l1 = "And then you'll bring the Baron to Turks. There you will take the ransom, and you will give me the Baron. And additionally you should mention, that all French will answer for Tortuga and Levasseur.";
			link.l1.go = "patria_7";
		break;
		
		case "patria_7":
			dialog.text = "Ha-ha-ha! That's one hell of a trick! We personally, well, you know what we did to Levasseur, and now... ha-ha-ha!.. Fine, pal. It will be done! You say that the ship will arrive soon?";
			link.l1 = "Soon. We need to be on lookout.";
			link.l1.go = "patria_8";
		break;
		
		case "patria_8":
			dialog.text = "Don't be bothered , I won't let you down. I will handle this personally. When you hear rumor that this baron was captured, come to me.";
			link.l1 = "Good. My thanks, Steven.";
			link.l1.go = "patria_9";
		break;
		
		case "patria_9":
			DialogExit();
			AddQuestRecord("Patria", "70");
			pchar.questTemp.Patria = "epizode_12_wait";
			pchar.questTemp.Patria.Condotier.Success = "true";
			LocatorReloadEnterDisable("Pirates_town", "reload3_back", true);
		break;
		
		case "patria_10":
			dialog.text = "Of course, pal. As agreed. Scary tales about evil pirates, slaughtering innocent French merchants, The sounds of a whip, moans and screams. Brazier with coal and scorched handcuffs. Just like it should be.";
			link.l1 = "Well now! Hold your horses. I need him alive.";
			link.l1.go = "patria_11";
		break;
		
		case "patria_11":
			dialog.text = "Don't worry, he will stay live. He wrote that letter with a shaky hand. Here it is.";
			link.l1 = "What is written there? Is he begging Poincy to get him out of this?";
			link.l1.go = "patria_12";
		break;
		
		case "patria_12":
			dialog.text = "Spot on, pal! He's begging!";
			link.l1 = "Throw this letter away, or better - burn it. We'll meet on Turks in a week. It must look as if we need time to collect the ransom.";
			link.l1.go = "patria_13";
		break;
		
		case "patria_13":
			dialog.text = "Got it. In a week time, Northern gulf. Don't forget to take the money: this must look pretty. Afterwards, come to me, well settle this.";
			link.l1 = "Of course, I bet even the echinus would have figured that out. See you later! ";
			link.l1.go = "patria_14";
		break;
		
		case "patria_14":
			DialogExit();
			AddQuestRecord("Patria", "73");
			pchar.questTemp.Patria = "epizode_12_terks";
			SetFunctionTimerCondition("Patria_CondotierTerks", 0, 0, 7, false);
			SetFunctionTimerCondition("Patria_CondotierTerksOver", 0, 0, 14, false);
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
		break;
		
		case "patria_15":
			pchar.quest.Patria_CondotierTerksOver.over = "yes"; //снять таймер
			dialog.text = "Hey, frog eater! Halt!";
			link.l1 = "I'm not moving.";
			link.l1.go = "patria_16";
		break;
		
		case "patria_16":
			dialog.text = "Here's your baron. A bit worn, but in one piece. Is it him?";
			link.l1 = "Yes.";
			link.l1.go = "patria_17";
		break;
		
		case "patria_17":
			dialog.text = "Perfect. Now, hand over the money or he is done! And don't try to trick us, we've got you in the sights!";
			if (sti(pchar.money) >= 350000)
			{
				link.l1 = "Here.";
				link.l1.go = "patria_18";
			}
			else
			{
				link.l1 = "Damn! I forot it on the ship...";
				link.l1.go = "patria_22";
			}
		break;
		
		case "patria_18":
			AddMoneyToCharacter(pchar, -350000);
			dialog.text = "Ha-ha-ha! You're a smart kid, frenchie. Take thine holiness. And tell Poincy that he should prepare the money: all French bastards will have to pay up for what you did to Levasseur and Tortuga. And your traders will pay us with their, goods and ships. Ha-ha-ha! Don't forget to bring us some more barons to the archipelago, they bring us a lot of profit! Ha-ha-ha!";
			link.l1 = "Please go to my boat, Baron.";
			link.l1.go = "patria_19";
		break;
		
		case "patria_19":
			sld = CharacterFromID("Noel");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
			dialog.text = "And don't even think about chasing us, captain. You know who I am. I hold more frog eater captives, and if I don't return home in time, they all be killed by my men. Got it?";
			link.l1 = "The time will come and we'll deal with you, cursed blasphemers!";
			link.l1.go = "patria_20";
		break;
		
		case "patria_20":
			dialog.text = "Ha-ha-ha-ha!";
			link.l1 = "...";
			link.l1.go = "patria_21";
		break;
		
		case "patria_21":
			DialogExit();
			LAi_SetPlayerType(pchar);
			AddQuestRecord("Patria", "74");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierDodsonNorm", 10.0);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 8.0);
			pchar.questTemp.Patria = "epizode_12_baronalive";
			pchar.questTemp.Patria.DodsonAgain = "true";
			Island_SetReloadEnableGlobal("Bermudes", false); // закрыть остров до отвоза барона
			sld = CharacterFromID("Noel");
			AddPassenger(pchar, sld, false);//добавить пассажира
			SetCharacterRemovable(sld, false);
			pchar.quest.Patria_Condotier_toPuancie.win_condition.l1 = "location";
			pchar.quest.Patria_Condotier_toPuancie.win_condition.l1.location = "Charles_town";
			pchar.quest.Patria_Condotier_toPuancie.function = "Patria_CondotierEnCapstervil";
			// Теркс в норму
			LAi_LocationFightDisable(&Locations[FindLocation("Shore56")], false);
			LAi_LocationDisableOfficersGen("Shore56", false);
		break;
		
		case "patria_22":
			dialog.text = "Are you messing with me?";
			link.l1 = "One minute, I'll bring it...";
			link.l1.go = "patria_23";
		break;
		
		case "patria_23":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Shot", "Patria_CondotierBaronDie", 1.0);
		break;
		
		case "patria_24":
			dialog.text = "";
			link.l1 = "Argh, Steven, what has your dullard done!";
			link.l1.go = "patria_25";
		break;
		
		case "patria_25":
			dialog.text = "Charles, what were you doing? Where's the money? I didn't tell my boys that this wasn't real... and so this idiot decided that you wanted to trick them...";
			link.l1 = "What a pity! Baron is dead... What will Poincy do now?";
			link.l1.go = "patria_26";
		break;
		
		case "patria_26":
			dialog.text = "Well, pal, It's your fault, I hope you understand that. Perhaps, it will be all the better for you.";
			link.l1 = "What an idiot I am! Messed everything up. Fine, I'll go to Poincy... Forgive me for being a fool, Steven, see you.";
			link.l1.go = "patria_27";
		break;
		
		case "patria_27":
			dialog.text = "You need to rest, you're losing your touch. Come to me sometime, I'll get you some rum and fine maidens.";
			link.l1 = "Thank you, I'll play you a visit when I can.";
			link.l1.go = "patria_28";
		break;
		
		case "patria_28":
			DialogExit();
			AddQuestRecord("Patria", "75");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierDodsonNorm", 10.0);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 8.0);
			pchar.questTemp.Patria = "epizode_12_barondie";
			// Теркс в норму
			LAi_LocationFightDisable(&Locations[FindLocation("Shore56")], false);
			LAi_LocationDisableOfficersGen("Shore56", false);
		break;
		
		case "patria_29":
			dialog.text = "You're welcome, pal. For me this was the most fun I've had this year! We laughed so much, me and my lads!.. So I'd like to thank you for this. Here's your money.";
			link.l1 = "You should keep yourself a share.";
			link.l1.go = "patria_30";
		break;
		
		case "patria_30":
			AddMoneyToCharacter(pchar, 350000);
			dialog.text = "Forget it. I did this for the sake of our friendship. The Brotherhood of the Coast owes you much more, yet you didn't ask for a single dubloon.";
			link.l1 = "Still, take at least fifty thousand for the services and compensation. Thank you, Steven! I'm glad that I once met you on that strange island of the lost ships.";
			link.l1.go = "patria_31";
		break;
		
		case "patria_31":
			AddMoneyToCharacter(pchar, -50000);
			dialog.text = "And so am I. Charles, pay me a visit whenever you have some time!";
			link.l1 = "With pleasure!";
			link.l1.go = "patria_32";
		break;
		
		case "patria_32":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Patria.DodsonAgain");
		break;
		
		case "patria_33":
			dialog.text = "You're late by a week! I didn't tell my boys that this wasn't real... ! They refused to wait any longer, and decided to end your baron!";
			link.l1 = "What an idiot I am! Messed everything up! What am I going to tell Poincy?";
			link.l1.go = "patria_34";
		break;
		
		case "patria_34":
			dialog.text = "Well, pal, It's your fault, I hope you understand that. Perhaps, it will be all the better for you.";
			link.l1 = "Fine, I'll go to Poincy... Forgive me for being a fool, Steven, see you..";
			link.l1.go = "patria_35";
		break;
		
		case "patria_35":
			dialog.text = "You need to rest, you're losing your touch. Come to me sometime, I'll get you some rum and fine maidens";
			link.l1 = "Thank you, I'll play you a visit when I can.";
			link.l1.go = "patria_36";
		break;
		
		case "patria_36":
			DialogExit();
			AddQuestRecord("Patria", "75");
			pchar.questTemp.Patria = "epizode_12_barondie";
			DeleteAttribute(pchar, "questTemp.Patria.DodsonFail");
		break;
		// belamour legendary edition хвастаемся Фортуной
		case "check_out_my_frigate":
			dialog.text = "Interesting, intrigued. Well, let's go for a walk.";
			link.l1 = "...";
			link.l1.go = "check_out_my_frigate_01";
		break;
		
		case "check_out_my_frigate_01":
			DialogExit();
			chrDisableReloadToLocation = true;
			bDisableFastReload = true;
			DoQuestReloadToLocation("pirates_town", "reload", "reload3_back", "SharkFrigateToTown");
			pchar.questTemp.SharkFrigate = true;
		break;
		
		case "check_out_my_frigate_02":
			dialog.text = "Pop my spleen! I don't believe my eyes! Is it really her? Tell me is it her? Is this 'Fortune'?!";
			link.l1 = "Yes, my friend, your eyes don't deceive you. That's her. Did you miss her?";
			link.l1.go = "check_out_my_frigate_03";
		break;
		
		case "check_out_my_frigate_03":
			dialog.text = "Ha ha ha, I can't believe it! Thousand of devils! But where did you get it from?";
			link.l1 = "From a certain Scot named William Paterson. Yes, yes, from the one who bought it from the Black Pastor.";
			link.l1.go = "check_out_my_frigate_04";
		break;
		
		case "check_out_my_frigate_04":
			dialog.text = "Blow me down... And what, he sold you 'Fortune'? Such a beautiful ship? After you bought it?";
			link.l1 = "Hehe, well, almost. Let's put it this way: we didn't get along a bit, and I took the ship as compensation for the costs that I incurred as a result of our conflict. He doesn't need a ship anyway.";
			link.l1.go = "check_out_my_frigate_05";
		break;
		
		case "check_out_my_frigate_05":
			dialog.text = "You surprise me even more ... He's a military captain in the service of England. His squadron of the colony can rob if desired. Even I didn't risk breaking my teeth on him. And how did you check it? Managed to tear off the 'Fortune' from the squadron?";
			link.l1 = "No, the squadron sank. Actually, it wasn't easy. The battle was serious, but it took place far from inhabited places, and only my sailors and officers were among the witnesses. In general, I am not afraid of persecution by the British authorities. William Paterson simply disappeared during some regular adventure ...";
			link.l1.go = "check_out_my_frigate_06";
		break;
		
		case "check_out_my_frigate_06":
			dialog.text = "Shiver me timbers... I have long lost hope of seeing my swallow again. Well, I hope this ship will serve you faithfully. Really happy for you, friend!";
			link.l1 = "What? Don't you need him? I wanted to return it to its rightful owner...";
			link.l1.go = "check_out_my_frigate_07";
		break;
		
		case "check_out_my_frigate_07":
			if(CheckAttribute(pchar, "questTemp.SharkGoldFleet"))
			{
				dialog.text = "Ha-ha-ha, my friend, keep 'Fortune' to yourself. First, you are its rightful owner. You honestly got it in battle. It is not good to abandon the ship after this. And secondly, I already have a new vessel. Of course, when I bought 'Fortune', I did not think that I would ever change it for something else. But, since I already did not expect to see her again, I ordered a new frigate from Alexus. And you know... He's damn good. I heard, and in this case it was not without your participation, ha ha!";
			}
			else
			{
				dialog.text = "Ha-ha-ha, my friend, keep 'Fortune' to yourself. First, you are its rightful owner. You honestly got it in battle. It is not good to abandon the ship after this. And secondly, a new ship is already being built for me. Of course, when I bought 'Fortune', I did not think that I would ever change it for something else. But, since I already did not expect to see her again, I ordered a new frigate from Alexus. And I look forward to when I can set foot on its deck.";
			}
			link.l1 = "Well, then I have no choice but to keep this beautiful ship for myself, Steven!";
			link.l1.go = "check_out_my_frigate_08";
		break;
		
		case "check_out_my_frigate_08":
			dialog.text = "Exactly. The only thing I ask you is to take care of 'Fortune'. Believe me, you will not find such a ship anywhere else. He is unique. And I love it as a memory. And I would be glad to know that my friend owns this ship, and not some scoundrel.";
			link.l1 = "Fine Steven. I promise that I will protect 'Fortune'.";
			link.l1.go = "check_out_my_frigate_09";
		break;
		
		case "check_out_my_frigate_09":
			dialog.text = "Yes, and one more thing...";
			link.l1 = "Listening.";
			link.l1.go = "check_out_my_frigate_10";
		break;
		
		case "check_out_my_frigate_10":
			dialog.text = "Since you now have 'Fortune', I want to offer you one business.";
			link.l1 = "I'm listening to you VERY carefully.";
			link.l1.go = "check_out_my_frigate_11";
		break;
		
		case "check_out_my_frigate_11":
			if(!CheckAttribute(pchar, "questTemp.SharkGoldFleet.KGBB"))
			{
				dialog.text = "As I said, Alexus is currently building a new frigate for me. He, of course, is unlikely to surpass the 'Fortune' in speed, but he will also not yield much. And just for one thing I need a couple of powerful, but fast ships. I might be able to do it alone, but two are much better.";
				link.l1 = "Great. And what kind of business is this?";
				link.l1.go = "check_out_my_frigate_12";
			}
			else
			{
				dialog.text = "As I said, Alexus recently made a new frigate for me. He, of course, is unlikely to surpass the 'Fortune' in speed, but he will also not yield much. And just for one thing I need a couple of powerful, but fast ships. I might be able to do it alone, but two are much better.";
				link.l1 = "Great. And what kind of business is this?";
				link.l1.go = "check_out_my_frigate_13";
			}
		break;
		// Фрегат Акулы не построен
		case "check_out_my_frigate_12":
			dialog.text = "It's too early to talk about it, because I don't know yet when my new ship will leave the stocks. Alexus seems to have some difficulties with the extraction of materials. By the way, if you have the opportunity, you could help him. I am sure that he will pay decently: I gave him a very serious advance. After he finds all the materials, I think in a month my ship will be ready. Then I'm waiting for you. But be sure to come on the 'Fortune' and equip it in advance, then there will be little time! Yes, and make sure the Spaniards don't want to see your head on a silver platter. I'll tell you all the details later.";
			link.l1 = "Well, I'll ask our shipbuilder what help he might need. And we will return to our conversation then a month after I help Alexus, when you will be sailing again.";
			link.l1.go = "check_out_my_frigate_14";
		break;
		
		// Фрегат Акулы построен
		case "check_out_my_frigate_13":
			dialog.text = "It's too early to talk about it, because my ship hasn't even left the stocks yet. I still need to equip it. So I'm waiting for you not earlier than in a month. But be sure to come on the 'Fortune' and equip it in advance, then there will be little time! Yes, and make sure the Spaniards don't want to see your head on a silver platter. I'll tell you all the details later.";
			link.l1 = "Fine, then we'll come back to our conversation later, when you're under sail again.";
			link.l1.go = "check_out_my_frigate_14";
		break;
		
		case "check_out_my_frigate_14":
			dialog.text = "Well, fine. Now I'm going to the residence, if you don't mind. Things, as they say, do not wait.";
			link.l1 = "See you soon, Shark! Not saying goodbye.";
			link.l1.go = "check_out_my_frigate_15";
		break;
		
		case "check_out_my_frigate_15":
			DialogExit();
			sld = characterFromId("Dodson");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "reload", "reload3_back","SharkFrigateEnd", -1);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		// belamour legendary edition на пару с Акулой
		case "SharkGoldFleet":
			if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_FRIGATE_L)
			{
				dialog.text = "Mine is ready, how about yours? I told you to come on 'Fortune'. I don't know where you left it, but it's too risky to embark on such a gamble on any other ship. So I'm waiting for you on the ship on which we agreed. And don't over tighten.";
				link.l1 = "Damn, I completely forgot, scumbag! Wait: I'll be back on the right ship.";
				link.l1.go = "exit";
				break;
			}
			if(GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = "Charles, I told you to come without a squadron. In the case that I want to do with you, extra ships are definitely not needed. Move your flotilla somewhere and come back.";
				link.l1 = "Yes, I completely forgot. Wait: I'll be back soon without a squadron.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Ah, there you are, friend! Finally! And then I started to worry. My ship is almost ready. Now I sent him to Tirax: he must equip him with the thirty-second caliber, which he took from the prize heavy galleon last month. I've already ridden it to the Turks and back, and I must say that Alexus did a great job. By the way, I have not yet chosen a suitable name for it, although there are several options. Can you help me choose?";
			link.l1 = "Of course I'll help! Whatever you call a ship, that's how it will fly, right? What are your options?";
			link.l1.go = "SharkGoldFleet_01";
		break;
		
		case "SharkGoldFleet_01":
			dialog.text = "I've settled on three options so far.";
			link.l1 = "...";
			link.l1.go = "SharkGoldFleet_02";
		break;
		
		case "SharkGoldFleet_02":
			dialog.text = "The first option is 'Phantom'. The frigate is fast and powerful, and with that name, all the misers from Havana to Cumana will tremble at the mere mention of it!";
			link.l1 = "Yeah, and you also need to appear and disappear in the fog so that the sailors definitely begin to be baptized, ha ha! Good name, I like it.";
			link.l1.go = "SharkGoldFleet_03";
		break;
		
		case "SharkGoldFleet_03":
			dialog.text = "I like it too. The second option is 'Shark'. And what? Why don't I give my ship its own nickname? Let's be namesakes with him, ha!";
			link.l1 = "There is a Shark on the 'Shark'... Ironic. But everyone will know exactly who owns the ship.";
			link.l1.go = "SharkGoldFleet_04";
		break;
		
		case "SharkGoldFleet_04":
			dialog.text = "Here I am about the same. And the third option is 'Flurry'. To make everyone afraid to even come close to my ship, ha ha ha!";
			link.l1 = "Because you can run into a flurry of balls from the side? And what, not bad.";
			link.l1.go = "SharkGoldFleet_05";
		break;
		
		case "SharkGoldFleet_05":
			dialog.text = "Exactly! But now I can not decide between these three names. So come on, help. As you wish.";
			link.l1 = "I suggest name it 'Phantom'. Then all the merchants will throw out the white flag as soon as they see you on the horizon!";
			link.l1.go = "SharkGoldFleet_05f";
			link.l2 = "I like the name 'Shark'. Everyone should know that the ship is not some newcomer, but the head of the Brethren of the Coast himself!";
			link.l2.go = "SharkGoldFleet_05a";
			link.l3 = "I think 'Flurry' is a good name. Any warrior, privateer or merchant should know what will happen if he decides to fight this ship.";
			link.l3.go = "SharkGoldFleet_05s";
		break;
		
		case "SharkGoldFleet_05f":
			pchar.questTemp.SharkGoldFleet.KGBB = "Phantom";
			dialog.text = "You look - even the military will start doing the same, ha! So, it's decided. Hold the mug, friend. Let's drink to my new ship. For 'Phantom!'";
			link.l1 = " For 'Phantom!'";
			link.l1.go = "SharkGoldFleet_06";
		break;
		
		case "SharkGoldFleet_05a":
			pchar.questTemp.SharkGoldFleet.KGBB = "Shark";
			dialog.text = "And let them think three times before crossing my path! So, it's decided. Hold the mug, friend. Let's drink to my new ship. For 'Shark'!";
			link.l1 = "For 'Shark'!";
			link.l1.go = "SharkGoldFleet_06";
		break;
		
		case "SharkGoldFleet_05s":
			pchar.questTemp.SharkGoldFleet.KGBB = "Flurry";
			dialog.text = "And if he still decides, such a flurry will cover him that tropical storms will seem like a light breeze! So, it's decided. Hold the mug, friend. Let's drink to my new ship. For 'Flurry!'";
			link.l1 = "For 'Flurry!'";
			link.l1.go = "SharkGoldFleet_06";
		break;
		
		case "SharkGoldFleet_06":
			dialog.text = "And may this ship serve faithfully and not know the bitterness of defeat! Well, now to the point.";
			link.l1 = "I listen to you carefully.";
			link.l1.go = "SharkGoldFleet_07";
		break;
		
		case "SharkGoldFleet_07":
			dialog.text = "Tell me, Charles, do you know what the 'Golden Fleet' is?";
			link.l1 = "Kha-kha! .. I already choked on rum. Steven, don't tell me you're on two frigates to rob the most heavily armed convoy in the Caribbean.";
			link.l1.go = "SharkGoldFleet_08";
		break;
		
		case "SharkGoldFleet_08":
			dialog.text = "Well, no, of course, I'm not suicidal. We will definitely not rob the entire convoy. But here we can snatch something from there.";
			link.l1 = "Steven, I'm sorry, of course, but I'm not ready for this. Yes, the Spaniards will burn us alive if we stick ourselves in their fleet! Come on without me.";
			link.l1.go = "SharkGoldFleet_09";
			link.l2 = "Fine, where we did not disappear ... I'm ready to participate!";
			link.l2.go = "SharkGoldFleet_11";
		break;
		
		case "SharkGoldFleet_09":
			pchar.questTemp.SharkGoldFleet = "RUinDeal";
			dialog.text = "Argh! It's a pity. I'm too risky without you. Fine, now I won't persuade, but think about it, alright? If you ever decide to do so, please let me know.";
			link.l1 = "If I do, then sure. Sorry Steven.";
			link.l1.go = "exit";
		break;
		
		case "SharkGoldFleet_10":
			dialog.text = "Such ventures do not give up! Well, what about you? Maybe changed your mind?";
			link.l1 = "No, friend, I'm sorry, but I still pass.";
			link.l1.go = "exit";
			link.l2 = "Fine, where we did not disappear ... I'm ready to participate!";
			link.l2.go = "SharkGoldFleet_11";
		break;
		
		case "SharkGoldFleet_11":
			if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_FRIGATE_L)
			{
				dialog.text = "You may be ready, but your ship is not. I told you to come on 'Fortune'. I don't know where you left it, but it's too risky to embark on such a gamble on any other ship. So I'm waiting for you on the ship on which we agreed. And don't over tighten.";
				link.l1 = "Damn, I completely forgot, bungler! Wait: I'll be back on the right ship.";
				link.l1.go = "exit";
				break;
			}
			if(GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = "But no: you are not ready, Charles. I told you to come without a squadron. In the case that I want to do with you, extra ships are definitely not needed. Move your fleet somewhere and come back.";
				link.l1 = "Yes, I completely forgot. Wait: I'll be back soon without a squadron.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Thousand of devils, that's exactly what I wanted to hear! So, I suggest that you and I snatch a piece from the convoy. Lots of loot...";
			link.l1 = "Snatch, you mean? Without getting caught by the guard ships?";
			link.l1.go = "SharkGoldFleet_12";
		break;
		
		case "SharkGoldFleet_12":
			dialog.text = "Exactly. Look, as you probably know, the 'Golden Fleet' gathers in Porto Bello and then goes from there to Havana. After Havana, it is already useless to intercept him: he goes across the Atlantic to Spain with such guards that only a complete cretin will stick his head up to him. At the time of the transition from Porto Bello to Havana, the situation is not much better. Of course, you can try, but for this you need to assemble a squadron capable of even cracking forts like nuts. But in Porto Bello, ships converge from all over Maine, and there they are no longer particularly protected.";
			link.l1 = "Only now the time of the transition and the names of such ships are strictly classified. We won't hang around Porto Bello somewhere for half a year and intercept all the Spanish ships going to the port.";
			link.l1.go = "SharkGoldFleet_13";
		break;
		
		case "SharkGoldFleet_13":
			dialog.text = "Of course we won't. From Cartagena, for example, the ships go by themselves, and, as you correctly noted, only God knows what kind of ships they are and when they will go. But from Caracas, next to which there is a Spanish mine, and which is located quite far from Porto Bello, the ships are not completely alone.";
			link.l1 = "How is it not completely alone?";
			link.l1.go = "SharkGoldFleet_14";
		break;
		
		case "SharkGoldFleet_14":
			dialog.text = "I was able to find out that a ship loaded with goods leaves Caracas alone or with a small guard, but somewhere in the longitude of the Gulf of Maracaibo, Spanish warships meet it to ensure its further safety. How do you think they know when and who they need to meet there?";
			link.l1 = "They must have been told something...";
			link.l1.go = "SharkGoldFleet_15";
		break;
		
		case "SharkGoldFleet_15":
			dialog.text = "Right. Before the main ship departs, a courier ship goes from Caracas to Porto Bello, reporting the place and date of the meeting, as well as the name of the Spanish ship. Then it goes back and carries confirmation that the ship will be met at the right time and in the right place. Only after that, our goal with you is put forward from Caracas.";
			link.l1 = "But if we intercept the courier, then the ship in Caracas will not receive confirmation and will not leave the harbor. Do you have any ideas about this? Besides, how are we going to catch the courier himself? We don't know when he will leave either.";
			link.l1.go = "SharkGoldFleet_16";
		break;
		
		case "SharkGoldFleet_16":
			dialog.text = "And here there is a small snag. The Spaniards, of course, use courier luggers for these purposes, but this is risky: the chance is too great that they will be intercepted by the first counter pirate. So you can wait a long time before sending the ship. Therefore, if there is an opportunity, they transmit instructions along with good powerful, but high-speed ships - merchants, for example, or privateers that go the right route. \nJust as a sealed mail. Moreover, it is much cheaper than sending a separate courier ship, even a lugger. And greedy Spanish officials like to save money while putting something in their pocket, hehe.";
			link.l1 = "I think I understand! Do I need to become such a merchant?";
			link.l1.go = "SharkGoldFleet_17";
		break;
		
		case "SharkGoldFleet_17":
			dialog.text = "Exactly! And we were lucky: I managed to find out from a reliable source that in Caracas they are now looking for such a courier to send him with a letter in the next three weeks. And you just have a powerful and fast ship, and even built by the Spaniards! Get a GVIK license, for greater plausibility - for six months at once, buy enough of some goods in Caracas for a profitable resale in Porto Bello, and then go to the local head of the port authority and ask if you need to take something along the way. \nIf the Port Authority asks, introduce yourself as a Spaniard. And yes - do not even think of dragging a squadron with you. There is no need for us to draw too much attention, otherwise the whole enterprise may be covered.";
			link.l1 = "And from the documents that they will give me, I will find out the date and place of the meeting of the ship and the convoy?";
			link.l1.go = "SharkGoldFleet_18";
		break;
		
		case "SharkGoldFleet_18":
			dialog.text = "Not so simple. I'm telling you: the documents are sealed. And you can't open them yourself. They will open them at the port authority of Porto Bello, and then they will write a reply and, if you will be kind enough to say that you are going back to Caracas, they will ask you to take him there. The answer, of course, will also be sealed.";
			link.l1 = "And how can I find out then the place and date of the meeting?";
			link.l1.go = "SharkGoldFleet_19";
		break;
		
		case "SharkGoldFleet_19":
			dialog.text = "You will have to be smart and somehow peep it ... For example, at the moment when documents are opened in Porto Bello and they write the answer. Or just steal them when they give you a confirmation, which will need to be taken to Caracas. But this is not a good option: after this, everything can go wrong.";
			link.l1 = "It's difficult, of course ... But I think I can handle it.";
			link.l1.go = "SharkGoldFleet_20";
		break;
		
		case "SharkGoldFleet_20":
			dialog.text = "I, in turn, will take my ship from Marcus and wait for you at anchor off Cape Santa Maria in Curacao. When you're done, just move to me. We intercept the ship at the indicated coordinates, and then immediately dump the hell out of there. Now you understand why ships are needed powerful, but fast? I don't want to fight the Spanish military squadron at all. You'll have to get away from them.";
			link.l1 = "Understand. Well, then I'm moving out. Meet me at Cape Santa Maria!";
			link.l1.go = "SharkGoldFleet_21";
		break;
		
		case "SharkGoldFleet_21":
			dialog.text = "That's right, we'll meet there. Well, good luck friend! Hope our business works out.";
			link.l1 = "I hope so too. Anyway, I'm leaving.";
			link.l1.go = "SharkGoldFleet_22";
		break;
		
		case "SharkGoldFleet_22":
			DialogExit();
			AddQuestRecord("SharkGoldFleet", "1");
			pchar.questTemp.SharkGoldFleet = "start";
			SetFunctionExitFromLocationCondition("SharkGoldFleetStart", pchar.location, false);
			if(!bImCasual) SetFunctionTimerCondition("SharkGoldFleet21", 0, 0, 21, false);
			if(!bImCasual) SetFunctionTimerCondition("SharkGoldFleet30", 0, 0, 30, false);
			else NewGameTip("Exploration mode: timer is disabled.");
		break;
		// провал
		case "SharkGoldFleet_23":
			dialog.text = "Damn Charles! I thought I'd never see you again! Where have you been? I was waiting for you at the appointed place, but I never did. And there was no news from you.";
			link.l1 = "Sorry Steven. I was unable to complete my task.";
			link.l1.go = "SharkGoldFleet_24";
		break;
		
		case "SharkGoldFleet_24":
			NextDiag.CurrentNode = "First time";
			dialog.text = "Eh, they missed such a fish ... Fine, don't be upset. Better luck next time.";
			link.l1 = "Hope so.";
			link.l1.go = "exit";
		break;
		
		case "SharkGoldFleet_25":
			if(GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = pchar.name+", what the heck? I told you to be without a squadron! Understand: we do not need any ballast, otherwise the whole operation may fail! I don't know what came over you, but it won't work like that. Urgently send your caravan somewhere and return on one ship. I'm waiting for you here.";
				link.l1 = "Yes, I just thought that this is more likely ... Fine, I understand you. Wait here: I'll be right back!";
				link.l1.go = "exit";
				NextDiag.TempNode = "SharkGoldFleet_25";
				break;
			}
			if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_FRIGATE_L)
			{
				dialog.text = pchar.name+", what the heck? I told you to be on the 'Fortune'! Understand: we need two fast and powerful ships, otherwise the whole operation may fail! I don't know what came over you, but it won't work like that. Urgently change your trough to 'Fortune' and come back. I'm waiting for you here.";
				link.l1 = "Yes, I just thought that this ship is better ... Fine, I understand you. Wait here: I'll be right back!";
				link.l1.go = "exit";
				NextDiag.TempNode = "SharkGoldFleet_25";
				break;
			} 
			dialog.text = "And here you are, my friend! Well, how do you like my handsome?";
			link.l1 = "Gorgeous frigate, Steven! I wouldn't refuse this...";
			link.l1.go = "SharkGoldFleet_26";
		break;
		
		case "SharkGoldFleet_26":
			dialog.text = "No, you now have 'Fortune', haha! Well, tell me how it went.";
			if(pchar.questTemp.SharkGoldFleet == "LightVarToShark")
			{
				link.l1 = "Everything went flawlessly: I managed to impersonate an honest and reliable merchant. I took the documents to Porto Bello, where I managed to distract the local head of the port authority for five minutes and rewrite for myself the date and coordinates of the meeting of the ships with the cargo and the military squadron.";
				link.l1.go = "SharkGoldFleet_27";
			}
			else
			{
				link.l1 = "There were some minor complications. The letter was sent to Porto Bello by courier. I intercepted it, delivered it to the addressee and even received an answer, but the head of the port authority guessed that I was not the person who was supposed to bring the documents. I had to break out of there with a fight. But I found out the date and coordinates of the meeting of the ship with the cargo and the military squadron, and delivered the answer to Caracas, so the production is waiting for us!";
				link.l1.go = "SharkGoldFleet_30";
			}
		break;
		
		case "SharkGoldFleet_27":
			dialog.text = "Wait a second. Did you say 'ships'?";
			link.l1 = "Yes, Shark! There will be two of them!";
			link.l1.go = "SharkGoldFleet_28";
		break;
		
		case "SharkGoldFleet_28":
			dialog.text = "Ha-ha-ha, yes, we'll hit the jackpot! Well, my beast is ready to go through a baptism of fire. But he has not participated in the battles yet, so let's lead the battle. And for now, I'll join your squadron.";
			link.l1 = "Am I to command Steven Dodson himself, head of the Brethren of the Coast? In business!";
			link.l1.go = "SharkGoldFleet_29";
		break;
		
		case "SharkGoldFleet_29":
			NextDiag.TempNode = "SharkGoldFleet_33";
			pchar.questTemp.SharkGoldFleet.talk = true;
			AddQuestRecord("SharkGoldFleet", "22");
			AddQuestUserData("SharkGoldFleet", "date", pchar.questTemp.SharkGoldFleet.Date);
			SGF_SharkCompanion();
			pchar.quest.SGF_SharkDelGroup1.win_condition.l1 = "ExitFromSea";
			pchar.quest.SGF_SharkDelGroup1.function = "SGF_SharkDelGroup";
			if(bImCasual)
			{
				pchar.GenQuest.SeaHunter2Pause = true;
				SeaHunter_Delete();
			}
			dialog.text = "Well, don't be too arrogant: it's only because I will fight on my ship for the first time. And take care of the availability of free officers for prize ships. Because their holds will be packed, and none of my team will be able to manage the ship on their own ... Fine, enough scratching your tongue. The booty is waiting for us!";
			link.l1 = "Exactly! I'm going to my ship.";
			link.l1.go = "exit";
		break;
		
		case "SharkGoldFleet_30":
			dialog.text = "Yes, you inherited ... Then we need to prepare for the fact that the squadron will arrive there before the agreed date, and we will have to fight with everyone at once.";
			link.l1 = "Why do you say that?";
			link.l1.go = "SharkGoldFleet_31";
		break;
		
		case "SharkGoldFleet_31":
			dialog.text = "And you brainstorm. In Porto Bello they know that the ship with the cargo will definitely leave Caracas, because you took the return letter there. But since you've given yourself away, they will try their best to prevent us from intercepting this ship. I think that the squadron will arrive there earlier. That's what I would do. So, let's get ready for a tough fight. Retreating late.";
			link.l1 = "Don't you worry. You and I are two sea wolves, we didn't go through this!";
			link.l1.go = "SharkGoldFleet_32";
		break;
		
		case "SharkGoldFleet_32":
			dialog.text = "Your truth. Well, my beast is ready to undergo a baptism of fire. But he has not yet participated in the battles, so let's you lead the battle. In the meantime, I'll join your squadron.";
			link.l1 = "Am I to command Stephen Dodson himself, head of the Brethren of the Coast? In business!";
			link.l1.go = "SharkGoldFleet_29";
		break;
		
		case "SharkGoldFleet_33":
			NextDiag.TempNode = "SharkGoldFleet_33";
			dialog.text = "No time to chat, "+pchar.name+"! Let's go for the loot!";
			link.l1 = "And may luck be with us!";
			link.l1.go = "exit";
		break;
		// делим добычу на берегу
		case "SharkGoldFleet_34":
			if(makeint(pchar.questTemp.SharkGoldFleet) > 74)
			{
				dialog.text = "Thousand of devils! Great job, Charles! The loot turned out to be much richer than I originally thought! I think this whole trip was definitely worth it.";
				link.l1 = "I totally agree with you Steven! Today is definitely our day!";
				link.l1.go = "SharkGoldFleet_35";
			}
			else
			{
				if(makeint(pchar.questTemp.SharkGoldFleet) > 24)
				{
					dialog.text = "Good job, friend. Although, we must admit that we have lost a lot of prey.";
					link.l1 = "I agree, Steven, we could do better. But what is there is also good!";
					link.l1.go = "SharkGoldFleet_35";
				}
				else
				{
					dialog.text = "Damn! It was such a good idea ... And as a result, the expenses from this campaign are more than profits. Charles, I actually gave you command, and you managed to lose everything!";
					link.l1 = "Don't say anything... I'm damned angry myself. How much prey has gone out of hand!..";
					link.l1.go = "SharkGoldFleet_37";
				}
			}
		break;
		
		case "SharkGoldFleet_35":
			dialog.text = "Well, we both did a good job. I came up with a plan and got the information on the courier, and you brilliantly put that plan into action. And we both fought on equal terms for our prey. Therefore, I propose to divide it according to the laws of Brethren of the Coast: equally!";
			link.l1 = "We'll do it!";
			link.l1.go = "SharkGoldFleet_36";
		break;
		
		case "SharkGoldFleet_36":
			dialog.text = "Well, now I'm off to Isla Tesoro. I need to repair the ship and properly wash the first successful trip on my new ship. Good luck friend! Always glad to see you at my residence!";
			link.l1 = "I'm glad our business turned out to be so profitable. I will definitely visit you sometime. Good luck!";
			link.l1.go = "SharkGoldFleet_39";
		break;
		
		case "SharkGoldFleet_37":
			dialog.text = "Fine, keep it all to yourself. If there is anything left at all. I don't care for these little ones. After all, I got you involved in this whole thing.";
			link.l1 = "Yes, my bad too... Sorry, Steven.";
			link.l1.go = "SharkGoldFleet_38";
		break;
		
		case "SharkGoldFleet_38":
			dialog.text = "Don't apologize, I still owe you my life, and I won't forget it. And now I'm off to Isla Tesoro. We need to repair the ship and wash it ... Although, what is there to wash ... Good luck, mate! Always glad to see you at my residence!";
			link.l1 = "Fine, anything can happen, defeats happen. The main thing is that we are alive. I'll definitely visit you sometime, friend! Good luck!";
			link.l1.go = "SharkGoldFleet_39";
		break;
		
		case "SharkGoldFleet_39":
			if(makeint(pchar.questTemp.SharkGoldFleet) > 74)
			{
				AddQuestRecord("SharkGoldFleet", "34");	
				ChangeCharacterComplexReputation(pchar, "fame", 10);
				ChangeCharacterComplexReputation(pchar, "authority", 5);
				ChangeOfficersLoyality("good_all", 2);
				AddComplexSeaExpToScill(150, 150, 150, 150, 150, 150, 0);
				AddCharacterExpToSkill(pchar, "Leadership", 300);
				AddCharacterExpToSkill(PChar, "Fortune", 300);
				AddCharacterExpToSkill(PChar, "Sneak", 300);
			}
			else
			{
				if(makeint(pchar.questTemp.SharkGoldFleet) > 24)
				{
					AddQuestRecord("SharkGoldFleet", "35");
					ChangeCharacterComplexReputation(pchar, "fame", 1);
					ChangeCharacterComplexReputation(pchar, "authority", 1);
					AddComplexSeaExpToScill(50, 50, 50, 50, 50, 50, 0);
					AddCharacterExpToSkill(pchar, "Leadership", 200);
					AddCharacterExpToSkill(PChar, "Fortune", 200);
					AddCharacterExpToSkill(PChar, "Sneak", 200);
				}
				else
				{
					AddQuestRecord("SharkGoldFleet", "36");
					AddCharacterExpToSkill(pchar, "Leadership", 100);
					AddCharacterExpToSkill(PChar, "Fortune", 100);
					AddCharacterExpToSkill(PChar, "Sneak", 100);
				}
			}
			if(makeint(pchar.questTemp.SharkGoldFleet) > 24)
			{
				if(GetSquadronGoods(pchar, GOOD_GOLD)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_GOLD, sti(makeint(pchar.questTemp.SharkGoldFleet.Gold)/2));
				}
				if(GetSquadronGoods(pchar, GOOD_SILVER)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_SILVER, sti(makeint(pchar.questTemp.SharkGoldFleet.Silver)/2));
				}
				if(GetSquadronGoods(pchar, GOOD_SANDAL)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_SANDAL, sti(makeint(pchar.questTemp.SharkGoldFleet.Sandal)/2));
				}
				if(GetSquadronGoods(pchar, GOOD_SHIPSILK)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_SHIPSILK, sti(makeint(pchar.questTemp.SharkGoldFleet.Silk)/2));
				}
				if(GetSquadronGoods(pchar, GOOD_ROPES)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_ROPES, sti(makeint(pchar.questTemp.SharkGoldFleet.Ropes)/2));
				}
				if(GetSquadronGoods(pchar, GOOD_OIL)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_OIL, sti(makeint(pchar.questTemp.SharkGoldFleet.Gold)/2));
				}
			}
			SGF_GoodSwimReturn();
			SGF_DelAllSubAttributes(); // убираем все лишнее, чтобы не болталось
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "SGF_SharkToIT", -1);
			CloseQuestHeader("SharkGoldFleet");
			DialogExit();
		break;
	}
}

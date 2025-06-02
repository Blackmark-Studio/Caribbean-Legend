// диалоги персонажей по пиратской линейке // Addon 2016-1 Jason пиратская линейка
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp, attrL;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	attrL = Dialog.CurrentNode;
	
	if(HasSubStr(attrL, "ShipStockManBack_"))
 	{
        i = findsubstr(attrL, "_" , 0);
	 	NPChar.ShipToStoreIdx = strcut(attrL, i+1, strlen(attrL)-1); // индех в конце
 	    Dialog.CurrentNode = "ShipStockManBack";
 	}

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "First time":
			dialog.text = "What do you want?";
			link.l1 = "I should go...";
			link.l1.go = "exit";
		break;
		
		// Лопе Монторо
		case "Mtr_officer":
			if (pchar.questTemp.Mtraxx != "fail" && pchar.questTemp.Mtraxx == "jewelry_5")
			{
				pchar.quest.Mtraxx_JewelryHavanaOver.over = "yes"; //снять таймер
				dialog.text = "For fuck's sake, who the hell are you?";
				link.l1 = "Good day, don Lope. Though we haven't been acquainted yet, now would be as good time as any. Especially now that I'm so eager to help you get out of this difficult situation...";
				link.l1.go = "Mtr_officer_1";
			}
			else
			{
				dialog.text = "What do you want?";
				link.l1 = "I should go...";
				link.l1.go = "exit";
			}
		break;
		
		case "Mtr_officer_1":
            dialog.text = "Help? Me? What a turn of events! Would you enlighten me, senor, where such generosity comes from?";
			link.l1 = "Certainly. I am looking for your former captain, Esberdo Cabanas, and I don't have much time... preferably, I would like to meet him in that place which he keeps a secret. Even better if I'd arrive there before he does.";
			link.l1.go = "Mtr_officer_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Mtr_officer_2":
            dialog.text = "Ha-ha! I told this pathetic idiot to keep his mouth shut! The blue amber, am I right?";
			link.l1 = "You are thinking in the right direction, my good sir.";
			link.l1.go = "Mtr_officer_3";
		break;
		
		case "Mtr_officer_3":
            dialog.text = "Then let us make haste. I would love to tell you every last detail if you find a way to get me out of here. You know how I ended up in this hole?";
			link.l1 = "In overall, yes I do.";
			link.l1.go = "Mtr_officer_4";
		break;
		
		case "Mtr_officer_4":
            dialog.text = "I was dead drunk when that happened. Fuck that bloody bartender! I don't remember a thing. I was told everything only when I woke up in a hold of the 'Cantavro'. It would all be behind us if we just sailed away, both the commandant and the alcalde were willing to turn the other way. But that damned don Esberdo simply put me in jail. You think he's done that 'to do the right thing'? If only, this scoundrel just wanted to keep my share of the ambers\nIt was me who mentioned there can be more ambers under the water, than what we found on the beach. It was me, who found a way to get it. I was to receive a hefty cut, but... oh, that son of a bitch! Ugh, but enough about that. Neither the alcalde, nor the commandant, nor the don de Toledo are happy about me being kept here to rot. If it wasn't for that peasant and his cow wife, who fluttered the dovecotes... either way, they won't object you helping me\nTalk to the governor, pretend to be my old friend from Europe - I will confirm that myself. What is your name, by the way?";
			link.l1 = ""+GetFullName(pchar)+".";
			link.l1.go = "Mtr_officer_5";
		break;
		
		case "Mtr_officer_5":
            dialog.text = ""+GetFullName(pchar)+", wonderful. Go see don Diego de Toledo and ask him for advice. Remember, you only have three days, chasing the 'Cantavro' would be pointless after that. Set me free and I will give you everything you need to deal with that bastard, Cabanas.";
			link.l1 = "I'll go see the governor at once, don Lope. I will do my best to resolve this situation for both of our sakes.";
			link.l1.go = "Mtr_officer_6";
		break;
		
		case "Mtr_officer_6":
            DialogExit();
			pchar.questTemp.Mtraxx = "jewelry_6";
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("Roger_1", "8");
			SetFunctionTimerCondition("Mtraxx_TimeclearPrison", 0, 0, 4, false); // таймер
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			AddLandQuestMark(characterFromId("Havana_Mayor"), "questmarkmain");
		break;
		
		case "Mtr_officer_7":
			pchar.quest.Mtraxx_TimeclearPrison.over = "yes"; //снять таймер
            dialog.text = "So, the huckster and his clocking hen got their revenge, and I am finally done with this hole. You have my gratitude senor, you have done your part. Now allow me to do mine.";
			link.l1 = "I am all ears!";
			link.l1.go = "Mtr_officer_8";
			DelLandQuestMark(npchar);
		break;
		
		case "Mtr_officer_8":
            dialog.text = "Good. During our previous patrol we got hit by a storm which made us abandon our course. We landed on the beach of the Western Main, not far from Mosquitoes Coast, in order to get some fresh water. We found a good deposit of blue amber there. I did some prospecting and found a pile of it under water. We needed better equipment to gather it, that's why we decided to return later\nEsberdo had bought five long boats in Havana for Indians to dive and gather the amber. You know the rest of the story - the scum got rid of me and sailed away. Find him at Mosquitoes Coast North of the Blueweld, and make haste - according to my calculations, all you have is about seven days to get there. Hope you catch the fucker in the middle of the gathering, take away all his amber and stab his belly for numerous times. Be careful though, my former captain is a skilled fighter and a seaman. Godspeed, senor.";
			link.l1 = "Same to you, Lope. Farewell!";
			link.l1.go = "Mtr_officer_9";
		break;
		
		case "Mtr_officer_9":
            DialogExit();
			pchar.questTemp.Mtraxx = "jewelry_10";
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Roger_1", "12");
			SetFunctionTimerCondition("Mtraxx_TimeclearGulf", 0, 0, 7, false); // таймер
			pchar.quest.mtr_jewelry_gulf.win_condition.l1 = "location";
			pchar.quest.mtr_jewelry_gulf.win_condition.l1.location = "Santacatalina";
			pchar.quest.mtr_jewelry_gulf.function = "Mtraxx_JewelryGulf";
			DeleteAttribute(pchar, "GenQuest.PrisonQuestLock");
			DelMapQuestMarkCity("Havana");
			AddMapQuestMarkShore("Shore53", true);
		break;
		
		// Росарио Гусман
		case "Mtr_rosario":
            dialog.text = "Want to ask anything, sir?";
			link.l1 = "Concerning don Montoro. We are old acquaintances and I was really upset when I learnt about his misfortunes. Don Diego de Toledo has sent me to you, said that you had already tried to set our mutual friend free...";
			link.l1.go = "Mtr_rosario_1";
		break;
		
		case "Mtr_rosario_1":
            dialog.text = "Hm... senor, this is a bit... unexpected, but I am glad to meet a friend of Lope! He has been unlucky for quite a while already and now this...";
			link.l1 = "What can we do for him? No way for a noble hidalgo to rot among the scum of the society!";
			link.l1.go = "Mtr_rosario_2";
		break;
		
		case "Mtr_rosario_2":
            dialog.text = "A man of business! It is both easy and difficult to help poor Lope. I had a talk with the profiteer poor Lope was unlucky to have an argument with. He has agreed to meet us halfway for five hundred doubloons. Quite a sum for his and his wife's 'sufferings'. Alas, I have only managed to gather a half of the required sum - two hundred and fifty doubloons.";
			link.l1 = "So, if I get you another two hundred and fifty doubloons then don Lope will be set free?";
			link.l1.go = "Mtr_rosario_3";
		break;
		
		case "Mtr_rosario_3":
            dialog.text = "Yes. The greedy bastard promised me to spread the word that Lope compensated him all the damage. He will also ask the governor to pardon him.";
			if (PCharDublonsTotal() >= 250) // belamour legendary edition
			{
				link.l1 = "I have the sum required with me right now. Here, let this greedy bourgeois choke on it.";
				link.l1.go = "Mtr_rosario_4";
			}
			link.l2 = "I'll do my best to get money as soon as possible.";
			link.l2.go = "Mtr_rosario_5";
		break;
		
		case "Mtr_rosario_4":
			RemoveDublonsFromPCharTotal(250); // belamour legendary edition
			PlaySound("interface\important_item.wav");
            dialog.text = "I can't believe my own ears! Senor, you must have been sent by the Lord!";
			link.l1 = "When will they set our man free?";
			link.l1.go = "Mtr_rosario_8";
			DelLandQuestMark(npchar);
		break;
		
		case "Mtr_rosario_5":
            dialog.text = "Glad to hear it, senor. You are a true friend of Lope and a true nobleman.";
			link.l1 = "Goodbye!";
			link.l1.go = "Mtr_rosario_6";
		break;
		
		case "Mtr_rosario_6":
            DialogExit();
			AddQuestRecord("Roger_1", "10");
			npchar.dialog.currentnode = "Mtr_rosario_7";
		break;
		
		case "Mtr_rosario_7":
            dialog.text = "Did you bring the money?";
			if (PCharDublonsTotal() >= 250) // belamour legendary edition
			{
				link.l1 = "I have the sum required with me right now. Here, let this greedy bourgeois choke on it.";
				link.l1.go = "Mtr_rosario_4";
			}
			link.l2 = "I am still on it.";
			link.l2.go = "Mtr_rosario_7_1";
		break;
		
		case "Mtr_rosario_7_1":
            DialogExit();
			npchar.dialog.currentnode = "Mtr_rosario_7";
		break;
		
		case "Mtr_rosario_8":
            dialog.text = "I'll bring the money to the sly bastard tonight. I believe they will have an order of our friend's release by the midday. And I hope we'll gather together to celebrate later?";
			link.l1 = "Sure thing, don Rosario. I should go now. See you!";
			link.l1.go = "Mtr_rosario_9";
		break;
		
		case "Mtr_rosario_9":
            DialogExit();
			AddQuestRecord("Roger_1", "11");
			npchar.lifeday = 1;
			SaveCurrentNpcQuestDateParam(NPChar, "LifeTimeCreate");
			npchar.dialog.currentnode = "Mtr_rosario_10";
			pchar.quest.mtr_prisoner.win_condition.l1 = "Timer";
			pchar.quest.mtr_prisoner.win_condition.l1.date.hour  = 12;
			pchar.quest.mtr_prisoner.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtr_prisoner.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtr_prisoner.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtr_prisoner.function = "Mtraxx_PrisonerFree";
		break;
		
		case "Mtr_rosario_10":
            dialog.text = "Soon our friend will be free!";
			link.l1 = "...";
			link.l1.go = "exit";
			npchar.dialog.currentnode = "Mtr_rosario_10";
		break;
		
		// Лысый Джеффри
		case "Jeffry":
			pchar.quest.Mtraxx_SilkCPVOver.over = "yes"; //снять прерывание
            dialog.text = "Hey, what the hell are you doing on my ship? I don't think you have got my invitation, huh?";
			link.l1 = "Calm down, Geffrey. I am from Tyrex regarding the ship silk business.";
			link.l1.go = "Jeffry_1";
		break;
		
		case "Jeffry_1":
            dialog.text = "A-ah, well, let's talk then. What's he planning? I've had a talk with smugglers already, if you ask me they offer a fine price for the goods...";
			link.l1 = "And how much, if I may ask?";
			link.l1.go = "Jeffry_2";
		break;
		
		case "Jeffry_2":
            dialog.text = "1300 pesos for a roll. I think it's a good price.";
			link.l1 = "Yeah, and Tyrex wants twenty golden pieces for a roll. Not a coin less. And I mean doubloons. He gave me a job to find a right buyer for that price.";
			link.l1.go = "Jeffry_3";
		break;
		
		case "Jeffry_3":
            dialog.text = "Ha-ha-ha, boy, aren't you lucky! Marcus does have an appetite! Well, go find such a buyer then, it'd be glorious to watch you try.";
			link.l1 = "Yeah, this is all very fucking funny and hilarious. Do I look happy? I don't. So I suggest you to stop laughing and help me out.";
			link.l1.go = "Jeffry_4";
		break;
		
		case "Jeffry_4":
            dialog.text = "Fine, fine, pal... Jesus, you are not very fond of jokes, huh? But I understand, you are not to be blamed for Tyrex's fantasies, we will all get our share of this, trust me. And how can I possibly help you? You can't sell it in stores, customs are not an option either, only smugglers left. Who else needs it? Got any ideas?";
			link.l1 = "I've been thinking about it since Hispaniola... Whatever. I have only two months to find a regular buyer. Something must be done about this. Your orders are to land in the nearest bay and do repairs.";
			link.l1.go = "Jeffry_5";
		break;
		
		case "Jeffry_5":
            dialog.text = "Two months?! What the hell? Ah, screw it. The 'Snake' does need a repair and cleaning or she won't be able to chase down even a barque. Hey, French whores! Bald Geffrey's crew is staying in Capsterville for two months! Ha-ha-ha!... Well good luck to you pal, in those pointless searches of yours. If you find an idiot ready to pay Marcus's price for this damn silk - you know where to find me.";
			link.l1 = "Wait! Give me one roll of this silk. I need to show the goods to potential buyers.";
			link.l1.go = "Jeffry_6";
		break;
		
		case "Jeffry_6":
            dialog.text = "Sure, no problem. You can take it with you on a longboat... Hey Boys! Toss one bale of silk onto the captain's boat!";
			link.l1 = "Good. Well, I will see you when I find the buyer!";
			link.l1.go = "Jeffry_7";
		break;
		
		case "Jeffry_7":
            DialogExit();
			AddQuestRecord("Roger_2", "3");
			npchar.DeckDialogNode = "Jeffry_8";
			npchar.dialog.currentnode = "Jeffry_8";
			pchar.questTemp.Mtraxx = "silk_2";
			AddCharacterGoods(pchar, GOOD_SHIPSILK, 1);
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("Mtraxx_SilkTimeOver", 0, 0, 61, false); // таймер
		break;
		
		case "Jeffry_8":
            dialog.text = "Anything else, pal?";
			link.l1 = "Nothing at the moment...";
			link.l1.go = "Jeffry_8_1";
		break;
		
		case "Jeffry_8_1":
            DialogExit();
			npchar.DeckDialogNode = "Jeffry_8";
			npchar.dialog.currentnode = "Jeffry_8";
		break;
		
		case "Jeffry_9":
			pchar.quest.Mtraxx_SilkTimeOver.over = "yes";
            dialog.text = "How are you doing, pal?";
			link.l1 = "Doing great. I have found us a buyer. Twenty five doubloons for a roll. I believe Tyrex will like it.";
			link.l1.go = "Jeffry_10";
		break;
		
		case "Jeffry_10":
            dialog.text = "No way! You are the resourceful son of a devil! How did you manage that, huh?";
			link.l1 = "It's a long story, Geffrey. Now listen. You should arrive to Cape Negril of Jamaica between 10th and 15th. They will be waiting for you there at nights. Password is 'A merchant of Lyons'. Got it? Repeat.";
			link.l1.go = "Jeffry_11";
		break;
		
		case "Jeffry_11":
            dialog.text = "A merchant of Lyons. I got it. I should tell my purser to write it down, he is the only man here who can write. Ha-ha!";
			link.l1 = "Do you have one hundred rolls in a cargo hold?";
			link.l1.go = "Jeffry_12";
		break;
		
		case "Jeffry_12":
            dialog.text = "I've got even more.";
			link.l1 = "Splendid. It's time for you to set sails then. Don't let me down!";
			link.l1.go = "Jeffry_13";
		break;
		
		case "Jeffry_13":
            dialog.text = "Relax, pal, everything will be done as it should be done.";
			link.l1 = "Godspeed, Geffrey. Perhaps, we'll meet again.";
			link.l1.go = "Jeffry_14";
		break;
		
		case "Jeffry_14":
            DialogExit();
            AddQuestRecord("Roger_2", "22");
			pchar.questTemp.Mtraxx = "silk_14"; // к Тираксу
			sld = characterFromId("Terrax");
			sld.dialog.currentnode = "mtraxx_12";
			pchar.quest.mtraxx_hide_jeffry.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_hide_jeffry.function = "Mtraxx_SilkHideJeffry";
		break;
		
		case "Jeffry_15":
            dialog.text = "Ho-ho-ho! Cunning Charlie Prince, in flesh! Nice seeing you again pal!";
			link.l1 = "Bald Geffrey! Charlie Prince you said? Ha!";
			link.l1.go = "Jeffry_15x";
		break;
		
		case "Jeffry_15x":
            dialog.text = "Never heard your second name before? That's how they call you in La Vega now.";
			link.l1 = "I see where Charlie came from, but why Prince?";
			link.l1.go = "Jeffry_15y";
		break;
		
		case "Jeffry_15y":
            dialog.text = "Well, you are the only noble son of the bitch in La Vega! Ha-ha-ha! How are you doing? Have you been at Pasquale's shop? Bought supplies from the old scumbag?";
			link.l1 = "Never again!";
			link.l1.go = "Jeffry_16";
		break;
		
		case "Jeffry_16":
            dialog.text = "K-ha! Why, you didn't like him? Did he sell you salt beef for the price of the rum?";
			link.l1 = "Worse! I got a lead from him on a Dutch caravan loaded with ebony. It wasn't easy to find it, to board the merchant and then to protect that fucking wood from a few dozens of rats! And guess what, the bastard paid me 150 pesos for a piece. For a piece of fucking ebony, Geffrey!";
			link.l1.go = "Jeffry_17";
		break;
		
		case "Jeffry_17":
            dialog.text = "It happens all the time pal, I assure you. Lavoisier has already screwed a dozen of good lads like you. He actually paid you something which is rare for him. We don't take his 'leads' even if we are starving.";
			link.l1 = "Thank you my friend, at least now I know that I wasn't the first and the only idiot! But this time the bastard has screwed himself. I'll make sure that he regrets the day he saw me.";
			link.l1.go = "Jeffry_18";
		break;
		
		case "Jeffry_18":
            dialog.text = "Hey-hey-hey! Wait Prince, calm down a bit. The huckster is untouchable here. Dare to plunder him - Marcus will be there for your ass. Tell me, was it Tyrex who sent you to Lavoisier?";
			link.l1 = "Hm. Yeah... Why?";
			link.l1.go = "Jeffry_19";
		break;
		
		case "Jeffry_19":
            dialog.text = "Listen... (lowering his voice) They say that the four-eyes shares with Marcus. Do you undestand me now? This is why no pirate will ever dare to attack Lavoisier's ships, othewise they are done for.";
			link.l1 = "Noted. Thanks for the warning Geffrey. Farewell and Godspeed!";
			link.l1.go = "Jeffry_20";
		break;
		
		case "Jeffry_20":
            dialog.text = "Same to you pal.";
			link.l1 = "...";
			link.l1.go = "Jeffry_21";
		break;
		
		case "Jeffry_21":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 15.0);
			AddQuestRecord("Roger_4", "10");
			CloseQuestHeader("Roger_4");
			QuestSetCurrentNode("Terrax", "mtraxx_34"); // релиз-правка
			bDisableFastReload = false;
			pchar.questTemp.Mtraxx.CharleePrince = "true"; // атрибут - ГГ известный пират
			pchar.questTemp.CharleePrince = true; // атрибут для найма команды 
		break;
		
		case "Jeffry_22":
            dialog.text = "Ho-ho-ho Prince! I was wondering who made the fireworks! Brought a squad of musketeers in case it was the Spanish.";
			link.l1 = "Geffrey? You are here too? But how? Did you buy the treasure map as well?";
			link.l1.go = "Jeffry_23";
			QuestPointerDelLoc("Judgement_dungeon_05", "reload", "reload1");
			QuestPointerDelLoc("Judgement_dungeon_04", "reload", "reload1");
		break;
		
		case "Jeffry_23":
            dialog.text = "Pal, I don't waste my money on shit like that. They delivered me a diary of some traveler who wrote about a safe passage to these dungeons.";
			link.l1 = "Who brought it to you?";
			link.l1.go = "Jeffry_24";
		break;
		
		case "Jeffry_24":
            dialog.text = "Some junkie. All he needed was a hundred pesos for a drink.";
			link.l1 = "Did it happen on Tortuga?";
			link.l1.go = "Jeffry_25";
		break;
		
		case "Jeffry_25":
            dialog.text = "Nah. It was Barbados? Prince why are you worried so much? The more of us there is the faster it will be to carry the treasures!";
			link.l1 = "I don't like this. I don't believe in coincidences like this. Could it be Camilla's father who wrote this diary?";
			link.l1.go = "Jeffry_26";
		break;
		
		case "Jeffry_26":
            dialog.text = "Who's Camilla?";
			link.l1 = "The wench who sold me a map to this place for two hundred pesos!";
			link.l1.go = "Jeffry_27";
		break;
		
		case "Jeffry_27":
            dialog.text = "Heh... Prince you think too much. Let's go treasure hunting. Come on!";
			link.l1 = "No need. I have found them already... They are below in dungeon, behind iron bars. We'll have to break them. Listen Geffrey, there's on more thing! Pelly the Cutlass was here too!";
			link.l1.go = "Jeffry_28";
		break;
		
		case "Jeffry_28":
            dialog.text = "Cutlass? Well then it's our lucky day! But where is he now?";
			link.l1 = "Below... dead. I met him near the treasure. He got mad, started screaming of greed. Then he and his companions attacked me.";
			link.l1.go = "Jeffry_29";
		break;
		
		case "Jeffry_29":
            dialog.text = "Hm... Pelly always had a bad luck with money. He must had gone mad seeing the load of gold.";
			link.l1 = "It may be so... but Geffrey you don't get it! All three of us got here! And we all got the same lead! You think it was by chance? Someone clearly wants us all in one place, and this place does feel like a tomb.";
			link.l1.go = "Jeffry_30";
		break;
		
		case "Jeffry_30":
            dialog.text = "Did you see the gold though?";
			link.l1 = "I did with my very own eyes. Several giant chests filled with coins and ingots.";
			link.l1.go = "Jeffry_31";
		break;
		
		case "Jeffry_31":
            dialog.text = "Then why do you worry Prince? Lead the way, let's take a look on these bars of yours. Then we will share the gold.";
			link.l1 = "Ah you might be right, whatever... Let's go.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionWithJeffry");
		break;
		
		case "Jeffry_32":
            PlaySound("Voice\English\LE\Jeffry\Jeffry_gold.wav");
			dialog.text = "What a spectacular! That's a big pile of gold! I can see now why Cutlass had gone mad. We are very fortunate Prince! What do you think, how much gold will we find here?";
			link.l1 = "Plenty. We'll know for sure when we take care of these bars.";
			link.l1.go = "Jeffry_33";
		break;
		
		case "Jeffry_33":
            dialog.text = "Yes, the lattice is very strong, we won't break it with bare hands nor with swords. You are right, mate - we need to find some tools or a lot of gunpowder. Hey look! What is that!?";
			link.l1 = "...";
			link.l1.go = "Jeffry_34";
		break;
		
		case "Jeffry_34":
            DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Mtraxx_RetributionJeffryMushketer", 0.1);
		break;
		
		case "Jeffry_35":
            PlaySound("Voice\English\LE\Jeffry\Jeffry_mozila.wav");
			dialog.text = RandSwear()+"What a fucking muff!";
			link.l1 = "You fucking snake!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionJeffryFight");
		break;
		
		// Билли Сипатый
		case "Billy":
			pchar.quest.Mtraxx_BillySeaTimeOver.over = "yes"; //снять таймер
			PlaySound("VOICE\English\LE\Billy\Billy_01.wav");
            dialog.text = "Shark swallow me if it has happened on the 'Fly Fish' this year... boys we have a guest here! What is so wrong in your life pal, that you decided to pay a visit to my old tub?";
			link.l1 = "Greetings! You are the one they Husky Billy, are you not?";
			link.l1.go = "Billy_1";
		break;
		
		case "Billy_1":
            dialog.text = "Can't you guess by my voice, captain? Long ago it could make British and Spanish merchants to shit themselves. Glorious times they were!... Now old Billy is waiting for his life to end near the shores of his favorite island on his precious long boat...";
			link.l1 = "I have a business for you, Billy. I was told that you know everything about what's going on here around Jamaica. Is that so?";
			link.l1.go = "Billy_2";
		break;
		
		case "Billy_2":
            dialog.text = "If you were told so, then it must be so, don't you think? Don't pull a crab by its balls, talk. What business do you have for me?";
			link.l1 = "Very well. There is shipbuilder in Port Royal. He provides his customers with special services, and he needs ship silk for his production and the said services. Since trading this merchandise is illegal here, he has found himself an illegal seller. I want to know who and how, is providing him with ship silk.";
			link.l1.go = "Billy_3";
		break;
		
		case "Billy_3":
            dialog.text = "Ho-ho-ho, look at this! Working for colonel D'Oyley, son?";
			link.l1 = "Here we go again! No, I work with Marcus Tyrex. He wants some share in ship silk market and this ship builder is sacred shitless to deal with 'unfamiliar' people...";
			link.l1.go = "Billy_4";
		break;
		
		case "Billy_4":
            dialog.text = "Oh, you are working for the Code Keeper! These are great news... if you are not lying of course. I don't give a damn about shipbuilders, arrest one - another will come. I do give a damn about my old girl. The 'Flying Fish' is in a bad shape. Do you understand me?\nBring me another long boat, a new one, and a roll of ship silk, the same kind of which you are talking about - Billy will make a decent sail of it so he could screw with patrols, ha-ha-ha! In return Billy will tell everything about the shipbuilder and his source of silk. Trust me son I know everything that you want to know, I just have to make sure that you are an honest pirate and not some ass licking red coat!";
			link.l1 = "A new long boat? How about I give you enough money to buy it yourself? I will even add extra.";
			link.l1.go = "Billy_5";
		break;
		
		case "Billy_5":
            dialog.text = "He-eh, captain, old Billy is not welcome in the city. They remember me too well in Port Royal and I don't fancy the idea to be hanged among my old friends on that rock. So, son, I am waiting for you to deliver me a fresh new long boat. I'll be waiting for three days at Negril Cape. And don't forget about the silk!";
			link.l1 = "Very well, Billy. You'll have your long boat and a roll of ship silk. I'll be back soon.";
			link.l1.go = "Billy_6";
		break;
		
		case "Billy_6":
            dialog.text = " Very well, Billy will be waiting for you on a shore, captain. See you soon!";
			link.l1 = "...";
			link.l1.go = "Billy_7";
		break;
		
		case "Billy_7":
            DialogExit();
			AddQuestRecord("Roger_2", "8");
			npchar.dialog.currentnode = "Billy_8";
			pchar.questTemp.Mtraxx = "silk_7";
			SetFunctionTimerCondition("Mtraxx_BillyTimeOver", 0, 0, 3, false); // таймер
			pchar.quest.mtr_billy_coast.win_condition.l1 = "ExitFromLocation";
			pchar.quest.mtr_billy_coast.win_condition.l1.location = pchar.location;
			pchar.quest.mtr_billy_coast.function = "Mtraxx_BillyOnCoast";
			locations[FindLocation("shore35")].DisableEncounters = true; //энкаутеры закрыть
			npchar.DontDeskTalk = true;
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
		break;
		
		case "Billy_8":
			PlaySound("VOICE\English\LE\Billy\Billy_02.wav");
            dialog.text = "What? Have you brought me a long boat already?";
			link.l1 = "You are a joker boy, huh, Billy?";
			link.l1.go = "exit";
		break;
		
		case "Billy_9":
            dialog.text = "So, captain, what about my fresh new long boat?";
			if(Companion_CheckShipType(SHIP_TARTANE) && GetSquadronGoods(pchar, GOOD_SHIPSILK) > 0)
			{
				link.l1 = "It's done, Husky. She is delivered along with a roll of ship silk in her cargo hold. You are free to sink your old tub.";
				link.l1.go = "Billy_11";
			}
			else
			{
				PlaySound("VOICE\English\LE\Billy\Billy_02.wav");
				link.l1 = "I am still on it. Wait.";
				link.l1.go = "Billy_10";
			}
		break;
		
		case "Billy_10":
			DialogExit();
			npchar.dialog.currentnode = "Billy_9";
		break;
		
		case "Billy_11":
			PlaySound("VOICE\English\LE\Billy\Billy_03.wav");
			pchar.quest.Mtraxx_BillyTimeOver.over = "yes"; //снять прерывание
            dialog.text = "Fuck me sideways! This is the very best news for the last five years of old Billy's life! Heh, a good reason to crack this bottle...";
			link.l1 = "I'll pass. So about the silk supplier?";
			link.l1.go = "Billy_12";
		break;
		
		case "Billy_12":
            dialog.text = "Pity, we could drink for my fresh new 'Flying Fish'! Whatever... Listen here, son\nA brigantine under the English flag arrives to Portland Cove in the middle of each month, somewhere between 10th and 15th. No rum for me until I am dead if she is really English! Her name is the 'Utrecht' and she arrives from South-West where Curacao lies. It's clearly a Dutch ship captain, you can see that\nAlways the same group of people meet them on the shore, lead by a head master of that sly shipbuilder. He is a receiver of ship silk which Dutch unload there. I am sure it's the ship silk, since only the Dutch pack it like that.";
			link.l1 = "Every month you said?";
			link.l1.go = "Billy_13";
		break;
		
		case "Billy_13":
            dialog.text = "Indeed my boy, not a single month missed for the last year. If you want to chat with this gloomy bearded company I suggest you wait for them at Portland Cove from 10th to 15th every month at nights. I swear on this by the fresh new silk sail of my long boat!";
			link.l1 = "Heh! Looks like my money was spent for reason. Godspeed, Billy, make sure to keep your old ass safe from patrols, otherwise you will make me really upset.";
			link.l1.go = "Billy_14";
		break;
		
		case "Billy_14":
            dialog.text = "Ha, old Billy is about to make some real fun around the shores of Jamaica! Godspeed, captain! Good hunting!";
			link.l1 = "Same to you, Billy!";
			link.l1.go = "Billy_15";
		break;
		
		case "Billy_15":
            DialogExit();
			npchar.lifeday = 0;
			pchar.questTemp.Mtraxx = "silk_8";
			chrDisableReloadToLocation = true;//закрыть локацию
			locations[FindLocation("shore35")].DisableEncounters = false; //энкаутеры открыть
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "OpenTheDoors", 20.0);
			AddDialogExitQuestFunction("Mtraxx_BillyTakeShip");
			AddQuestRecord("Roger_2", "9");
			//
			if (GetDataDay() >= 1 && GetDataDay() <= 9)
			{
				DoQuestFunctionDelay("Mtraxx_SilkCreateSmuggler", 1.0);
			}
			
			if (GetDataDay() >= 10 && GetDataDay() <= 15)
			{
				int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+2;
				if (iRank > 45) iRank = 45;
				Group_FindOrCreateGroup("Mtr_Utreht");
				sld = GetCharacter(NPC_GenerateCharacter("Cap_Utreht", "mercen_19", "man", "man", iRank, ENGLAND, -1, true, "quest"));
				FantomMakeCoolSailor(sld, SHIP_BRIGANTINE, "Utrecht", CANNON_TYPE_CULVERINE_LBS18, 50, 50, 50);
				FantomMakeCoolFighter(sld, iRank, 50, 50, "blade_13", "pistol5", "bullet", 100);
				sld.name = "Joachim";
				sld.lastname = "Gusen";
				sld.DontRansackCaptain = true;
				sld.AnalizeShips = true;
				sld.Coastal_Captain = true; // правки прогона 3
				DeleteAttribute(sld, "SaveItemsForDead");
				sld.Ship.Mode = "pirate";
				SetSailsColor(sld, 2);
				sld.ship.Crew.Morale = 40+MOD_SKILL_ENEMY_RATE*4;
				sld.Ship.Crew.Exp.Sailors = 60+MOD_SKILL_ENEMY_RATE*4;
				sld.Ship.Crew.Exp.Cannoners = 40+MOD_SKILL_ENEMY_RATE*4;
				sld.Ship.Crew.Exp.Soldiers = 40+MOD_SKILL_ENEMY_RATE*4;
				if (MOD_SKILL_ENEMY_RATE > 4) SetCharacterPerk(sld, "MusketsShoot");
				SetCharacterGoods(sld, GOOD_SHIPSILK, 80);

				Group_AddCharacter("Mtr_Utreht", "Cap_Utreht");
				Group_SetGroupCommander("Mtr_Utreht", "Cap_Utreht");
				Group_SetTaskAttackInMap("Mtr_Utreht", PLAYER_GROUP);
				Group_SetAddress("Mtr_Utreht", "Jamaica", "Quest_Ships", "Quest_Ship_4");
				Group_SetTaskRunaway("Mtr_Utreht", PLAYER_GROUP);
				Group_LockTask("Mtr_Utreht");
				
				pchar.quest.mtr_silksmuggler_AfterBattle.win_condition.l1 = "Group_Death";
				pchar.quest.mtr_silksmuggler_AfterBattle.win_condition.l1.group = "Mtr_Utreht";
				pchar.quest.mtr_silksmuggler_AfterBattle.function = "Mtraxx_SilkSmugglerAfterBattle";
				
				SetTimerFunction("Mtraxx_SilkSmugglerFail", 0, 0, 2);
			}
			
			if (GetDataDay() >= 16 && GetDataDay() <= 20)
			{
				SetTimerFunction("Mtraxx_SilkCreateSmuggler", 0, 0, 15);
			}
			if (GetDataDay() >= 21 && GetDataDay() <= 26)
			{
				SetTimerFunction("Mtraxx_SilkCreateSmuggler", 0, 0, 10);
			}
			if (GetDataDay() >= 27 && GetDataDay() <= 31)
			{
				SetTimerFunction("Mtraxx_SilkCreateSmuggler", 0, 0, 5);
			}
		break;
		
		// мастеровой с верфи Порт-Ройаля
		case "Mtr_acceptor_fight":
            LAi_group_Delete("EnemyFight");
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation("shore36")], false);
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("Mtr_acceptor_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Mtraxx_SilkWrongTalk");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Mtr_acceptor":
            dialog.text = "Hey, sailor, you have just arrived to Jamaica, eh?";
			link.l1 = "Hm. Correct. What's the matter?";
			link.l1.go = "Mtr_acceptor_1";
		break;
		
		case "Mtr_acceptor_1":
            dialog.text = "Seen anything happened at the sea nearby?";
			link.l1 = "Aye, I have. Some brigantine engaged into combat with English patrol corvette. Brits hit them hard, the Dutch got rid of their cargo in an attempt to flee.";
			link.l1.go = "Mtr_acceptor_2";
		break;
		
		case "Mtr_acceptor_2":
            dialog.text = "Why are you so certain she was a Dutch? No Dutch in sane mind will even think of approaching this close to Port Royal...";
			link.l1 = "She had English colors yet the name... The 'Utrecht'. Not very British, eh? They were Dutch I tell you, perhaps smugglers even. The patrol surely expected them.";
			link.l1.go = "Mtr_acceptor_3";
		break;
		
		case "Mtr_acceptor_3":
            dialog.text = "Fuck!";
			link.l1 = "Looks like you are not exactly happy about this...";
			link.l1.go = "Mtr_acceptor_4_1";
			link.l2 = "Had you been waiting for this brigantine here?";
			link.l2.go = "Mtr_acceptor_7";
		break;
		
		case "Mtr_acceptor_4_1":
            dialog.text = "Why would I be?";
			link.l1 = "Come on. I know who you are. You are a foreman of Port Royal's shipyard and you are waiting for the very special cargo to be delivered by the brigantine.";
			link.l1.go = "Mtr_acceptor_wrong";
			link.l2 = "You have it written on your face, right there!";
			link.l2.go = "Mtr_acceptor_4_2";
		break;
		
		case "Mtr_acceptor_wrong":
            dialog.text = "Argh! Boys, this is a patrol in disguise! Finish them off and get the hell out of here!";
			link.l1 = "Shit! Wait you are wr...";
			link.l1.go = "Mtr_acceptor_fight";
		break;
		
		case "Mtr_acceptor_4_2":
            dialog.text = "Being rude, 'sea wolf'? Watch your mouth or...";
			link.l1 = "Come on. You obviously look upset. Were you actually waiting for these Dutch to arrive?";
			link.l1.go = "Mtr_acceptor_4_3";
			link.l2 = "Or what? Will you teach me a life lesson?";
			link.l2.go = "Mtr_acceptor_6";
		break;
		
		case "Mtr_acceptor_4_3":
            dialog.text = "And what if I was? Why do you care?";
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l1 = "I don't, really. You are the waiting party here, not me. You have an eternity ahead.";
				link.l1.go = "Mtr_acceptor_4_4";
			}
			link.l2 = "Oh, I have every reason to care. I know what was inside the brigantine's cargo hold. Ship silk. You are here because of it, right?";
			link.l2.go = "Mtr_acceptor_wrong";
		break;
		
		case "Mtr_acceptor_4_4":
            dialog.text = "Hm... Eternity?";
			link.l1 = "It takes eternity to come back from the bottom of the sea. Your brigantine was sunk by a patrol corvette, pal. Just like that. Although, war brings both prizes and losses. I will make a good coin on that sunk Dutchman.";
			link.l1.go = "Mtr_acceptor_4_5";
		break;
		
		case "Mtr_acceptor_4_5":
            dialog.text = "And how exactly, I wonder?";
			link.l1 = "I will sell what they had thrown overboard while trying to flee. Almost everything is lost but precious ship silk was floating like... cork. I have salvaged most of it, so I am heading to the city tomorrow to find a buyer. One never knows where one will gain and where one will lose.";
			link.l1.go = "Mtr_acceptor_4_6";
		break;
		
		case "Mtr_acceptor_4_6":
            dialog.text = "Wait!";
			link.l1 = "Caramba! What now?";
			link.l1.go = "Mtr_acceptor_4_7";
		break;
		
		case "Mtr_acceptor_4_7":
            dialog.text = "How much silk did you manage to gather?";
			link.l1 = "And why do you care? This is my silk! Or are you the governor's dog? You are de...";
			link.l1.go = "Mtr_acceptor_4_8";
		break;
		
		case "Mtr_acceptor_4_8":
            dialog.text = "Keep your sword sheathed, sailor. I am not a dog and I am not a snitch. We work at the local shipyard... This silk was for us and as far as I understand, you have it now. I will buy all of it from you, we need this silk, pal.";
			link.l1 = "Really? Interesting... How much?";
			link.l1.go = "Mtr_acceptor_4_9";
		break;
		
		case "Mtr_acceptor_4_9":
			i = GetSquadronGoods(pchar, GOOD_SHIPSILK);
            dialog.text = "Two thousand and a half for a roll. That's a good price, you won't find better.";
			link.l1 = "Looks like I got lucky! I have "+FindRussianQtyString(i)+". Show me the money and I will order to deliver it ashore right now.";
			if (i > 80) link.l1.go = "Mtr_acceptor_4_11";
			else link.l1.go = "Mtr_acceptor_4_10";
		break;
		
		case "Mtr_acceptor_4_10":
            dialog.text = "Deal!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CargoSilk");
			AddCharacterExpToSkill(pchar, "Fortune", 300);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
		break;
		
		case "Mtr_acceptor_4_11":
            dialog.text = "Hm... Joachim was supposed to deliver only eighty rolls - no way you could salvage that much... what means you are either trying to play a dirty game here or... you are a snitch! Boys, kill him and get the hell out of here!";
			link.l1 = "Fuck!";
			link.l1.go = "Mtr_acceptor_fight";
		break;
		
		case "Mtr_acceptor_5":
            dialog.text = "";
			link.l1 = "A splendid deal, pal! Why so gloomy? Worried about the Dutch at the bottom of the sea? Shit happens, don't worry about it!";
			link.l1.go = "Mtr_acceptor_5_1";
		break;
		
		case "Mtr_acceptor_5_1":
            dialog.text = "Yeah, right... They were our regular supplier. Where are we supposed to get the silk now? We are always in shortage of it and the whole trade is under direct control of colonel D'Oyley. Bah dammit...";
			link.l1 = "Hm... Listen, friend, I suppose I can help you with that.";
			link.l1.go = "Mtr_acceptor_5_2";
		break;
		
		case "Mtr_acceptor_5_2":
            dialog.text = "Oh really? And how do you imagine to help us? Will you be delivering us a batch of hundred rolls every month?";
			link.l1 = "Me? Hmm, probably not, but Marcus Tyrex would. Have you heard about him?";
			link.l1.go = "Mtr_acceptor_5_3";
		break;
		
		case "Mtr_acceptor_5_3":
            dialog.text = "K-ha! So, you are a pirate?";
			link.l1 = "No, I just do business with them on, special occasions. I know for sure that Marcus receives batches of ship silk on a constant basis and he sells it to anyone who can afford it. And I am not talking about 2500 pesos for a roll here, I'd say if you can pay him 25 doubloons in gold for every roll, he will drown you in them, you can count on that.";
			link.l1.go = "Mtr_acceptor_5_4";
		break;
		
		case "Mtr_acceptor_5_4":
            dialog.text = "These are interesting news... Marcus Tyrex you say? In doubloons only?..";
			link.l1 = "Come on pal, does it really matter to you from whom you get your silk? And money is money, you can always exchange pesos for doubloons in a bank. So what, should I whisper a word or two about you in the ears of the code keeper? I am going to La Vega anyway.";
			link.l1.go = "Mtr_acceptor_5_5";
		break;
		
		case "Mtr_acceptor_5_5":
            dialog.text = "Very well. Let's make a deal. These are our terms: a batch of hundred rolls every month between 10th and 15th. We will be waiting here... wait let's change the meeting point, this place is compromised now. We will be waiting at Cape Negril, near Maroon town, it should be safer there. The password - 'A merchant of Lyons'.";
			link.l1 = "Deal, friend. Hell of voyage it was! Tyrex will pay me a doubloon or two for such a buyer! Ha-ha! Very well, I should go. Wait for Tyrex's vessel next month. Best of luck to you and to your family!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CargoSilkWin");
		break;
		
		case "Mtr_acceptor_6":
            dialog.text = "You won't need any life lessons after we teach you about being polite.";
			link.l1 = "Acting tough, carpenter? Fine, keep waiting for that brigantine of yours, though it will take a while.";
			link.l1.go = "Mtr_acceptor_6_1";
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l2 = "Hey, teacher, I have a few lessons for you too!";
				link.l2.go = "Mtr_acceptor_6_2";
			}
		break;
		
		case "Mtr_acceptor_6_1":
            dialog.text = "Carpenter? Bloody hell, how do you know? K-ha! Fuck, boys, this is a patrol in disguise! Kill him and get the hell out of here!";
			link.l1 = "Shit!";
			link.l1.go = "Mtr_acceptor_fight";
		break;
		
		case "Mtr_acceptor_6_2":
            dialog.text = "Leave us be, you fish scale, we ain't got any time. Get lost!";
			link.l1 = "Are you busy waiting for a certain Dutch vessel? Good luck with that. You have an eternity ahead.";
			link.l1.go = "Mtr_acceptor_4_4";
		break;
		
		case "Mtr_acceptor_7":
            dialog.text = "What the hell are you talking about?";
			link.l1 = "I see. But, just in case you are, forget it. She ain't coming thanks to a patrol corvette. I saw through a spyglass the end of a fight. Happened so fast and not far from here";
			link.l1.go = "Mtr_acceptor_7_1";
		break;
		
		case "Mtr_acceptor_7_1":
            dialog.text = "Again, we are not waiting for anything or anyone and...";
			link.l1 = "Look, I don't give a fuck really. I don't belong to the city patrol and don't care about your doings, I am no angel myself. If you are smuggling - it's your business. All I wanted to do is to warn you. Best of luck to you, pal.";
			link.l1.go = "Mtr_acceptor_7_2";
		break;
		
		case "Mtr_acceptor_7_2":
            dialog.text = "Wait... Are you sure the 'Utrecht' is sunk?";
			link.l1 = "Absolutely. She tried to flee, threw away everything she had in her cargo holds, they didn't even spare precious ship silk but such drastic measures couldn't help against a corvette's advantage in speed.";
			link.l1.go = "Mtr_acceptor_7_3";
		break;
		
		case "Mtr_acceptor_7_3":
            dialog.text = "What a pity... and what are we supposed to do without the silk? Damn it!";
			link.l1 = "Are you in a need of ship silk?";
			link.l1.go = "Mtr_acceptor_7_4";
		break;
		
		case "Mtr_acceptor_7_4":
            dialog.text = "Why are you asking, are you selling it?";
			link.l1 = "I am not, but I know a man who is. He is looking for a generous and a regular buyer. Think you can fit in?";
			link.l1.go = "Mtr_acceptor_7_5";
		break;
		
		case "Mtr_acceptor_7_5":
            dialog.text = "And who is that man?";
			link.l1 = "Marcus Tyrex, the baron of La Vega, better known as the Code Keeper. He receives batches of ship silk on a constant basis, so he always has some to sell. I suppose he will consider selling it to you too if your price is hefty enough.";
			link.l1.go = "Mtr_acceptor_7_6";
		break;
		
		case "Mtr_acceptor_7_6":
            dialog.text = "So you are a pirate?";
			link.l1 = "Why do you care? I can arrange a deal between you and Tyrex if you got balls for that. If you don't - goodbye then.";
			link.l1.go = "Mtr_acceptor_7_7";
		break;
		
		case "Mtr_acceptor_7_7":
            dialog.text = "Fine-fine, don't get angry. Sure, I do. I want to make a deal with Tyrex. But what's in it for you?";
			link.l1 = "If you offer a good price for the cargo, I will probably get from Marcus a decent sum for my assistance. So what will it be?";
			link.l1.go = "Mtr_acceptor_7_8";
		break;
		
		case "Mtr_acceptor_7_8":
            dialog.text = "Twenty five doubloons for a roll. That is the best price you can get, trust me on that.";
			link.l1 = "Twenty five golden coins? Hm. Not bad. I believe Tyrex will owe me a lot for such a buyer. Very well deal, I'll let him know. However, if you lied to me about the price then it's your ass on the line.";
			link.l1.go = "Mtr_acceptor_7_9";
		break;
		
		case "Mtr_acceptor_7_9":
            dialog.text = "Don't worry, we are honest folks. These are our terms: a batch of hundred rolls every month between 10th and 15th. We will be waiting here... wait let's change the meeting point, this place is compromised now. We will be waiting at Cape Negril, near Maroon town, it should be safer there. The password - 'A merchant of Lyons'.";
			link.l1 = "Got it. Wait for the first batch next month.";
			link.l1.go = "Mtr_acceptor_7_10";
		break;
		
		case "Mtr_acceptor_7_10":
            dialog.text = "Let Tyrex know that he may bring more cargo this time, we are left without silk for this month.";
			link.l1 = "I will. Godspeed, friend.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CargoSilkWin");
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
		break;
		
		// Тесак Пелли
		case "Pelly":
            dialog.text = "Ahoy! What brought you aboard of my vessel, friend?";
			link.l1 = "Hey, Cutlass. Marcus Tyrex sent me. A march to Maracaibo awaits us.";
			link.l1.go = "Pelly_1";
		break;
		
		case "Pelly_1":
            dialog.text = "A-ah, at last. So you must be my new boss for this voyage. Good. What's my new admiral's name?";
			link.l1 = "Captain "+GetFullName(pchar)+".";
			link.l1.go = "Pelly_2";
		break;
		
		case "Pelly_2":
            dialog.text = "Orders, Admiral "+GetFullName(pchar)+"?";
			link.l1 = "We will sail to Maracaibo Lake apart. You should get there at night and secretly land at Guajira Bay. Wait for me there and in the meanwhile set up a small camp. As for myself, I will land in the Spanish port.";
			link.l1.go = "Pelly_3";
		break;
		
		case "Pelly_3":
            dialog.text = "Aye-aye, Admiral!";
			link.l1 = "How long will it take for you to get there?";
			link.l1.go = "Pelly_4";
		break;
		
		case "Pelly_4":
            dialog.text = "Hmmm... It should be around a week. A day less, a day more, all depends on the wind.";
			link.l1 = "Good. Let's not waste time then. I'll see you at Guajira Bay, friend.";
			link.l1.go = "Pelly_5";
		break;
		
		case "Pelly_5":
            dialog.text = "Aye-aye, admiral!";
			link.l1 = "...";
			link.l1.go = "Pelly_6";
		break;
		
		case "Pelly_6":
            DialogExit();
			AddQuestRecord("Roger_3", "3");
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true;
			Mtraxx_PlantContinue();
		break;
		
		case "Pelly_7":
            dialog.text = "Orders, admiral?";
			link.l1 = "Nothing at the moment. I am busy with our operation.";
			link.l1.go = "Pelly_wait";
			if (pchar.questTemp.Mtraxx == "plant_3")
			{
				link.l1 = "Prepare a capacious chest on the shore. We will be collecting weapons, for our imprisoned brethren, in it.";
				link.l1.go = "Pelly_7_1";
			}
			if (pchar.questTemp.Mtraxx == "plant_6" && CheckAttribute(pchar, "questTemp.mtraxx_PlantInfoTovar"))
			{
				dialog.text = "So, what's the deal with Handsome? My hands are itching to spill some Don blood!";
				link.l1 = "It's more complicated than we thought. He said the guards on the plantation are too alert. The only way to sneak in weapons is hidden in goods. We'll need to urgently get a shipment of coffee, copra, or vanilla - the local planter deals in those and nothing else.";
				link.l1.go = "Pelly_70";
				DelLandQuestMark(npchar);
			}
			if (pchar.questTemp.Mtraxx == "plant_8" && pchar.location.from_sea == "Shore37")
			{
				link.l1 = "Leave the camp and gather a storm squad. It's time to march, we attack under the cover of darkness.";
				link.l1.go = "Pelly_11";
				DelLandQuestMark(npchar);
			}
		break;
		
		case "Pelly_wait":
             DialogExit();
			 npchar.dialog.currentnode = "Pelly_7";
		break;
		
		case "Pelly_7_1":
            dialog.text = "Listen, Admiral, I've been thinking...";
			link.l1 = "What's this, Terrax pays you to think instead of swinging that saber of yours, eh, Cutlass?";
			link.l1.go = "Pelly_35";
		break;
		
		case "Pelly_8":
            dialog.text = "Ho! A rebellion on the plantation, am I right, admiral? Flames! We are to get some gold out of this!..";
			link.l1 = "I need a chest on the shore, Cutlass.";
			link.l1.go = "Pelly_9";
		break;
		
		case "Pelly_9":
            dialog.text = "At once, Admiral!";
			link.l1 = "...";
			link.l1.go = "Pelly_10";
		break;
		
		case "Pelly_10":
            DialogExit();
			npchar.dialog.currentnode = "Pelly_7";
			pchar.questTemp.Mtraxx = "plant_4";
			pchar.questTemp.Mtraxx.Chest = "true";
			// подгружаем сундук в локу и меняем локаторы
			int n = Findlocation("Shore37");
			Locations[n].models.always.locators = "shore03_q_locators";
			locations[n].models.always.chest = "chest_quest";
			Locations[n].models.always.chest.locator.group = "box";
			Locations[n].models.always.chest.locator.name = "private1";
			Locations[n].models.always.chest.tech = "DLightModel";
			DoQuestReloadToLocation("Shore37", "goto", "goto5", "Mtraxx_PlantChestReady");
		break;
		
		case "Pelly_11":
            dialog.text = "At once, Admiral!..";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantPrepareMarch");
		break;
		
		case "Pelly_12":
            dialog.text = "Men are ready and prepared, Admiral!";
			link.l1 = "Onward!";
			link.l1.go = "Pelly_13";
		break;
		
		case "Pelly_13":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			chrDisableReloadToLocation = false;
		break;
		
		case "Pelly_14":
            dialog.text = "Admiral it looks like the friend of Tyrex we were supposed to save is... somewhat dead.";
			link.l1 = "Yeah but nothing could be done there. You saw the guards, we were lucky to stay alive.";
			link.l1.go = "Pelly_15";
		break;
		
		case "Pelly_15":
            dialog.text = "Admiral, Marcus will be mad at you. Don't go to him right now. I am leaving. You should too.";
			link.l1 = "Yeah...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantFailFinal");
		break;
		
		case "Pelly_16":
            dialog.text = "Bad news Admiral. There is a Spanish squadron coming at us from the East. We have no time to flee.";
			link.l1 = "How many of them?";
			link.l1.go = "Pelly_17";
		break;
		
		case "Pelly_17":
            dialog.text = "Three ships. Lots of guns. We are fucked."; // лесникПОСЛЕДНЕЕ
			link.l1 = "We shall see.";// Жан, ты отправляйся на борт к Тесаку. Тесак, поднимешь испанский флаг и на всех парусах прочь отсюда - глядишь, за торговца сойдёшь. А я пойду прямо на испанцев - отвлеку их от вас. Увидимся в Ла Веге у Тиракса.";
			link.l1.go = "Pelly_181";
		break;
		case "Pelly_181":
	    	DialogExit();
		   sld = characterFromId("Mrt_Rocur");
		   sld.Dialog.currentnode = "Pelly_182";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		case "Pelly_182":
		   dialog.text = ""; 
		   link.l1 = "Jean you go to Cutlass's ship.";
		   link.l1.go = "Pelly_183"; 
		break;
		case "Pelly_183":
		     DialogExit();
			sld = characterFromId("Pelly");
			sld.Dialog.currentnode = "Pelly_18";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		case "Pelly_18":
            dialog.text = "";//"Но...";
			link.l1 = "Cutlass you should rise the Spanish flag and get the hell out of here. I will distract them from you. See you all in La Vega.";//"Отставить! Тесак, за Жана Пикара отвечаешь головой перед Тираксом. Все на борт!";
			link.l1.go = "Pelly_19";
		break;
		
		case "Pelly_19":
            dialog.text = "But...";
			link.l1 = "No buts! Cutlass it's your ass on the line if Picard does not get to Tyrex's place. All aboard!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantSeaEscape");
		break;
		
		case "Pelly_20":
            dialog.text = "Orders Admiral?";
			link.l1 = "Get ready to fight. Engage them on my command!";
			link.l1.go = "Pelly_21";
		break;
		
		case "Pelly_21":
            dialog.text = "Aye-aye Admiral... on your command!";
			link.l1 = "...";
			link.l1.go = "Pelly_22";
		break;
		
		case "Pelly_22":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;
		break;
		
		case "Pelly_23":
            dialog.text = "Ho-ho! Hello Prince. What brought you to Tortuga?";
			link.l1 = "Marcus's task again. Listen Cutlass, why is the bastard living in this house not letting me in?";
			link.l1.go = "Pelly_24";
		break;
		
		case "Pelly_24":
            dialog.text = "Gaspard Goldenteeth? He works only with trusted fellows. Others would need a recommendations to work with him. Wanna sell some shiny trinkets? I could vouch for you if you want...";
			link.l1 = "So he is a usurer? What is his interest?";
			link.l1.go = "Pelly_25";
		break;
		
		case "Pelly_25":
            dialog.text = "Brother you are missing something. Gaspard is no usurer, you should go to "+GetFullName(characterFromId("Tortuga_usurer"))+" if you need one. Goldenteeth is buying precious stones and jewelry of all kinds. By the way, he pays well and never asks dumb questions. Every pirate captain is a client of his.";
			link.l1 = "I see... I was told that some of them even trust their money to him...";
			link.l1.go = "Pelly_26";
		break;
		
		case "Pelly_26":
            dialog.text = "Ha-ha! It was a liar who told you that, go and spit in his shameless eyes. Gaspard works only with jewelry, he always did. Why would he need problems with other people's money?";
			link.l1 = "I see. Thank you Cutlass, see you in the sea!";
			link.l1.go = "Pelly_27";
			link.l2 = "Hmm, indeed. So, he purchases trinkets? Interesting... You say you can put in a good word for me?";
			link.l2.go = "Pelly_27z";
		break;
		
		case "Pelly_27":
            dialog.text = "See you, Prince.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekReadLogbookThird");
		break;
		
		case "Pelly_27z":
            dialog.text = "Of course! You're one of us now, hehe! Wait here a moment.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekPellyTalkGems");
		break;
		
		case "Pelly_28z":
            dialog.text = "Everything is settled! Now Goldentooth knows that Charlie Prince may come to him to sell trinkets. Just keep in mind that his price, while good, is still lower than what those stingy usurers pay. But he buys everything by the ton! And without unnecessary questions, as I already said.";
			link.l1 = "That's my handsome lad! Well done Paul! Now I have a place to unload all the loot!";
			link.l1.go = "Pelly_29z";
		break;
		
		case "Pelly_29z":
            dialog.text = "No, Jean Picard is the 'Handsome', I'm the 'Cutlass', haha! So long, Prince!";
			link.l1 = "Thanks, Cutlass, good luck at sea!";
			link.l1.go = "Pelly_27";
		break;
		
		case "Pelly_28":
			PlaySound("VOICE\English\LE\Pelly\Pelly_03.wav");
            dialog.text = "I have got three birds for you Prince. Found them hiding in wardrobes and beneath a bed. Pretty things, hey? Ha-ha-ha!";
			link.l1 = "I say they indeed are. And they are well-groomed too. Don Stubborn must care deeply of them.";
			link.l1.go = "Pelly_29";
		break;
		
		case "Pelly_29":
            DialogExit();
			sld = CharacterFromID("Mtr_CartahenaMayorClone");
			sld.dialog.currentnode = "CartahenaMayor_8";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Pelly_30":
			PlaySound("VOICE\English\LE\Pelly\Pelly_04.wav");
            dialog.text = "Alle hagel! What the fuck are you doing here Prince?";
			link.l1 = "Cutlass?.. I was following the voices and the noise, but never did I think it would be you. How on earth did you end up here?";
			link.l1.go = "Pelly_31";
			QuestPointerDelLoc("Judgement_dungeon_01", "reload", "reload2_back");
			QuestPointerDelLoc("Judgement_dungeon_02", "reload", "reload2");
			QuestPointerDelLoc("Judgement_dungeon_03", "reload", "reload2");
			QuestPointerDelLoc("Judgement_dungeon_04", "reload", "reload2");
			QuestPointerDelLoc("Judgement_dungeon_05", "quest", "pelly");
		break;
		
		case "Pelly_31":
            dialog.text = "No, why are you here! You are always around! Tyrex must had sent you for this treasure, right? Caramba, I am late, again...";
			link.l1 = "Tyrex? No... I bought a map from one wench. She probably had sold a copy to you, huh? On Tortuga? What a cunning bitch. She didn't lie though - look at this pile of gold! I will come back with more people to carry all thi...";
			link.l1.go = "Pelly_32";
		break;
		
		case "Pelly_32":
            dialog.text = "Hell yeah it's a pile of gold! But it not yours or Tyrex's! I have found it first! It's mine! It doesn't matter how I have learnt of it! It's none of your business!";
			link.l1 = "Calm down Cutlass, why are you so mad? Look at this pile - must be a million there. Even more maybe! Enough for both of us!";
			link.l1.go = "Pelly_33";
		break;
		
		case "Pelly_33":
            dialog.text = "You always get a better slice of a pie, Prince! But not this time! The treasure is mine! I have found it first!";
			link.l1 = "Damn it, Paul, what's wrong with you? Can't we make a deal here? Even a half of this gold is a fortune. You've never had such a sum in your hands before. Besides I could find a profitable lead one day and tell you about it.";
			link.l1.go = "Pelly_34";
		break;
		
		case "Pelly_34":
            dialog.text = "Want to fuck me up, Prince? No way! I am not gonna give you a single coin, not a single guinea! You are late!\nA-ah, I see what you are up to! No way you get this gold!!!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionPellyFight");
		break;
		
		case "Pelly_35": //
            dialog.text = "Hilarious. Truly. You're a comedian, Admiral. But it's true - Marcus doesn't like those who try to outsmart him, like you. But he values clever men.";
			link.l1 = "Alright, alright. So, what's on your mind?";
			link.l1.go = "Pelly_36";
		break;
		
		case "Pelly_36":
            dialog.text = "Something you and Handsome clearly didn't consider. You're planning a revolt on the plantation. Great idea - if the goal was looting or making a chaos. But...";
			link.l1 = "But what? You against the revolt? Scaring?";
			link.l1.go = "Pelly_37";
		break;
		
		case "Pelly_37":
            dialog.text = "Me? Ha! Never. But think about what happens if Handsome meets his end during the slaughter. What do we tell Marcus? I'll tell you what - it won't matter what we say. He'll have our hides anyway.";
			link.l1 = "Hmm. So what's your brilliant plan? We need to get him out somehow.";
			link.l1.go = "Pelly_38";
		break;
		
		case "Pelly_38":
            dialog.text = "We do. Which is why... why not buy him? Off... Officially, that is. A handful of gold can buy anyone from these bastards - even their own mothers. What to say about poor Jean?";
			link.l1 = "Ha! Cutlass, are you seriously suggesting I walk into a plantation and ask to buy Picard? Should I also tell them who I work for, just for kicks? You've lost your mind?";
			link.l1.go = "Pelly_39";
		break;
		
		case "Pelly_39":
            dialog.text = "No need to say that. In fact, quite the opposite - pretend you're a merchant. Sure, you don't have the gut for the part, but you don't look like pirate either. No offense, Admiral, but it's the truth. Just stride onto that plantation, act confident, and ask for Jean. The owner might suspect who you are, but he won't show it. As I said - a handful of gold seals mouths.";
			link.l1 = "And how much would this... hand of gold cost us? The whole mountain?";
			link.l1.go = "Pelly_40";
		break;
		
		case "Pelly_40":
            dialog.text = "Maybe so. But better parting with gold than your head. I haven't been idle while you've been ashore - I changed into something less piratey and asked around about the plantation and its humble owner.";
			link.l1 = "And what did you find, Cutlass?";
			link.l1.go = "Pelly_41";
		break;
		
		case "Pelly_41":
            dialog.text = "Market prices, so to say. This isn't the first time a valuable prisoner has landed in his lap. Usually, they wind up on the gallows or worse - in the dungeons of the Inquisition.";
			link.l1 = "And how much does he sell them for?";
			link.l1.go = "Pelly_42";
		break;
		
		case "Pelly_42":
            dialog.text = "For someone important? Five hundred coins. In doubloons, of course.";
			link.l1 = "FIVE HUNDRED?!";
			link.l1.go = "Pelly_43";
		break;
		
		case "Pelly_43":
            dialog.text = "Planters, what did you expect?";
			link.l1 = "For that price, I could outfit a small army! Why the hell am I stockpiling an arsenal on my ship for a revolt then? That`s will be enough for little war.";
			link.l1.go = "Pelly_44";
		break;
		
		case "Pelly_44":
            dialog.text = "The weapons will come in handy for your crew later, regardless. So, what do you say?";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				if (PCharDublonsTotal() >= 500)
				{
					link.l1 = "(Trustworthy) I'll just say it'll be funny if Terrax' reward is less than what we spend here. But you're right - our lives are worth more. I've got the doubloons.";
					link.l1.go = "Pelly_45";
				}
				link.l2 = "I don't have that kind of golden mountain right now.";
				link.l2.go = "Pelly_44_1";
				notification("Trustworthy", "Trustworthy");
			}
			else notification("Perk Check Failed", "Trustworthy");
			link.l3 = "You know what, Cutlass? Forget it. Are we pirates or what? And Jean? Or is his pretty face his only asset? Get a chest ready - we'll stick to the original plan.";
			link.l3.go = "Pelly_62";
		break;
		
		case "Pelly_44_1":
            dialog.text = "I'd be surprised if you did - it's a huge sum. Fine, when you're ready, or if you come up with something better, come find me.";
			link.l1 = "Will do. Wait here.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Pelly_44_2";
		break;
		
		case "Pelly_44_2":
			dialog.text = "Well, Admiral, have you scraped together enough gold to save Picard?";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "Yes, I've finally did it. Let's hope this works.";
				link.l1.go = "Pelly_45";
			}
			link.l2 = "I'm still working on it, Cutlass.";
			link.l2.go = "exit";
			link.l3 = "I'm not giving my hard-earned money to those greedy planters! Get the chest ready - we'll act like Gentlemen of Fortune. That's my decision.";
			link.l3.go = "Pelly_9";
			NextDiag.TempNode = "Pelly_44_2";
		break;
		
		case "Pelly_45":
            dialog.text = "Whoa. You're new to our crew and already tossing around that kind of money!";
			link.l1 = "Money isn't everything. But basking in Terrax' glory? Priceless.";
			link.l1.go = "Pelly_46";
			pchar.questTemp.mtraxx_PlantVykup = true;
		break;
		
		case "Pelly_46":
            dialog.text = "Can't argue with that. But as you said, it's not just about money - there's something else important, Admiral.";
			link.l1 = "I'm curious now. What?";
			link.l1.go = "Pelly_47";
		break;
		
		case "Pelly_47":
            dialog.text = "I told you I've scoped out everything about the plantation. Including what goods are in demand here and circulating on the market. If you want to pass yourself off as a legitimate trader, you'd better stock up on those instead of just slamming a pile of gold on the planter's desk.";
			link.l1 = "Makes sense. What kind of goods are we talking about?";
			link.l1.go = "Pelly_48";
		break;
		
		case "Pelly_48":
            dialog.text = "Well, aside from living goods, heh-heh, the local plantation owner buys, trades, and resells coffee, copra, and vanilla. So...";
			link.l1 = "I need to quickly stock up on those somewhere. Or hit a caravan and hope it's carrying what I need.";
			link.l1.go = "Pelly_49";
		break;
		
		case "Pelly_49":
            dialog.text = "Not just any caravan. I hate to part with it, but I've got a lead saved for myself. A caravan carrying exactly what you need will be showing up soon. But there's a caveat...";
			link.l1 = "Oh, what now?";
			link.l1.go = "Pelly_50";
		break;
		
		case "Pelly_50":
            dialog.text = "It's under the French flag.";
			link.l1 = "What?!";
			link.l1.go = "Pelly_51";
		break;
		
		case "Pelly_51":
            dialog.text = "I understand your frustration, ha-ha. The decision is yours... Admiral. Want the details?";
			link.l1 = "Damn it... Alright, spill it. We don't have much time - if you or I don't nibble at them, someone else will.";
			link.l1.go = "Pelly_52";
			link.l2 = "I don't touch the French unless I have no choice. End of discussion.";
			link.l2.go = "Pelly_51_1";
		break;
		
		case "Pelly_51_1":
            dialog.text = "Then you'd better start gathering all those goods on your own and fast before Pretty Boy is sold to someone. I can't hang around here forever either.";
			link.l1 = "Figured as much.";
			link.l1.go = "Pelly_51_2";
		break;
		
		case "Pelly_51_2": // добываем товары сами
            DialogExit();
			
			LAi_SetActorType(npchar);
			AddQuestRecord("Roger_3", "28");
			SetTimerCondition("Mtraxx_PlantCaravanGuadeloupe", 0, 0, 14, false);
			SetTimerCondition("Mtraxx_PlantCaravanGuadeloupe_time", 0, 0, 45, false);
			//DoQuestCheckDelay("Mtraxx_PlantCaravanGuadeloupe", 1.0);
		break;
		
		case "Pelly_52":
            dialog.text = "That's more like it! I knew you had it in you... Admiral. So, here's the deal: my reliable contact reported recently that in about two weeks, a French caravan carrying coffee and spices will appear in the waters of Guadeloupe. It's big and well-armed, so prepare thoroughly.";
			link.l1 = "What other choice do I have.";
			link.l1.go = "Pelly_53";
		break;
		
		case "Pelly_53": // наводка на караван с нужными товарами
            DialogExit();
			
			LAi_SetActorType(npchar);
			AddQuestRecord("Roger_3", "28");
			//if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup")) AddQuestUserData("Roger_3", "sText", "Who would've thought that among the captains of Terrax, there'd be someone with at least the spark of a negotiator or a true entrepreneurial streak? That person turned out to be my temporary companion, Paul "Cutlass." Understanding the consequences of Marcus's wrath if we fail his assignment, Cutlass suggested... officially buying Picard from the plantation owner. While I scouted the situation and spoke with Jean, Cutlass didn't waste time either. He discovered that the plantation owner frequently sells valuable captives, with the average price for such transactions being around 500 doubloons - a small fortune. But Paul is right - it's better to do this than risk Picard being killed by a stray bullet or blade. Now all that's left is to load up on the plantation's usual trade goods - be it coffee, copra, or vanilla - in large quantities.");
			SetTimerCondition("Mtraxx_PlantCaravanGuadeloupe", 0, 0, 14, false);
			SetTimerCondition("Mtraxx_PlantCaravanGuadeloupe_time", 0, 0, 45, false);
			//DoQuestCheckDelay("Mtraxx_PlantCaravanGuadeloupe", 1.0);
		break;
		
		case "Pelly_54": // провал выкупа Красавчика
            dialog.text = "You're looking down, Admiral. Where's Handsome? Is it all gone down the drain?";
			link.l1 = "Indeed. I made decent money, but that stubborn mule refused to sell me Picard - even for a heap of doubloons!";
			link.l1.go = "Pelly_55";
		break;
		
		case "Pelly_55":
            dialog.text = "What a fool! What now?";
			link.l1 = "I've already arranged with the planter to unload the goods. We'll have to go back to the original plan - it's now or never!";
			link.l1.go = "Pelly_56";
		break;
		
		case "Pelly_56":
            dialog.text = "But we haven't even prepared anything for Handsome and the others!";
			link.l1 = "No time! Get aboard the ships - we'll sneak weapons and medicine from our holds into the sacks of goods. And don't forget to raise the Spanish flag!";
			link.l1.go = "Pelly_57";
		break;
		
		case "Pelly_57":
            dialog.text = "Sounds like a plan.";
			link.l1 = "Anyway we don't have time for anything else. Move! The unload happens soon.";
			link.l1.go = "Pelly_58";
		break;
		
		case "Pelly_58":
            DialogExit();
			DoQuestFunctionDelay("Mtraxx_PlantWaitDay", 1.0);
		break;
		
		case "Pelly_59":
            dialog.text = "Look who it is! Handsome! And judging by your intact face and cool stride, I take it everything went smoothly?";
			link.l1 = "Smoothly is an understatement - not only did I avoid a fight and buy back Jean, but I made some money too. Your plan worked flawlessly, Paul. All quiet on the horizon?";
			link.l1.go = "Pelly_60";
		break;
		
		case "Pelly_60":
            dialog.text = "Quiet as can be. Heading back to Marcus?";
			link.l1 = "Right.";
			link.l1.go = "Pelly_61";
		break;
		
		case "Pelly_61":
            DialogExit();
			DeleteAttribute(pchar,"questTemp.Mtraxx.MagicBox");
			chrDisableReloadToLocation = true;
			LocatorReloadEnterDisable("shore37", "boat", false);
			bQuestDisableMapEnter = false;
			AddQuestRecord("Roger_3", "29");
			pchar.questTemp.Mtraxx = "plant_success";
			QuestSetCurrentNode("Terrax", "mtraxx_27");
			//SetFunctionTimerCondition("Mtraxx_PlantGoHomeOver", 0, 0, 40, false);
			SetFunctionTimerCondition("Mtraxx_PlantOpenMaracaibo", 0, 0, 5, false);
			
			sld = characterFromId("Mtr_plantation_boss");
			sld.lifeday = 0;
			
			sld = &Locations[FindLocation("shore37")];
			sld.DisableEncounters = false;
			sld = ItemsFromID("fire");
			sld.shown = false;
			DeleteAttribute(sld, "fire");
			for (i=1; i<=4; i++)
			{
				if (GetCharacterIndex("Pelly_sailor_"+i) != -1)
				{
					sld = characterFromId("Pelly_sailor_"+i);
					sld.lifeday = 0;
					LAi_SetActorType(sld);
					LAi_ActorRunToLocation(sld, "reload", "sea", "none", "", "", "", 5);
				}
			}
			sld = characterFromId("Pelly");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "sea", "none", "", "", "OpenTheDoors", 5);
			sld = characterFromId("mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "sea", "none", "", "", "", 5);
		break;
		
		case "Pelly_62":
            dialog.text = "Hmm, as you wish, Admiral. But if something happens to Handsome, I'll make sure Terrax knows you ignored my advice. Got everything ready for the breakout?";
			link.l1 = "Let me double-check and count what I have in the chest.";
			link.l1.go = "Pelly_63";
		break;
		
		case "Pelly_63":
            dialog.text = "Be sure of it. I can help for a modest fee and to cover my efforts, heh-heh.";
			link.l1 = "How's that?";
			link.l1.go = "Pelly_64";
		break;
		
		case "Pelly_64":
            dialog.text = "I've got a contact, a gunrunner in Maracaibo. I'll disguise myself, sneak in, pay him, and arrange to have the weapons smuggled here. But it'll cost you - gold doubloons, to be exact.";
			link.l1 = "And why haven't you introduced me to this guy sooner? How much will this set me back?";
			link.l1.go = "Pelly_65";
		break;
		
		case "Pelly_65":
            dialog.text = "Should I introduce you to all my informants too? Fine. With expenses, risks, and my cut... it'll cost about the same as the ransom for Handsome.";
			link.l1 = "Cutlass, fear God...";
			link.l1.go = "Pelly_66";
		break;
		
		case "Pelly_66":
            dialog.text = "I fear neither God nor you, Admiral. But Marcus' wrath if we fail to save Jean? That's another story. So, what'll it be? Need help with the chest?";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "Alright, go ahead - enough time's been wasted already. Here, this should be the right amount.";
				link.l1.go = "Pelly_68";
			}
			link.l2 = "That's a lot of money, Paul. I need to think about it.";
			link.l2.go = "Pelly_67";
			link.l3 = "That's way too expensive for a small batch of weapons I can buy wholesale much cheaper! No thanks, I'll handle this myself.";
			link.l3.go = "Pelly_67_1";
		break;
		
		case "Pelly_67":
            dialog.text = "Well, think away. But remember-while you're thinking, the number of bruises on Handsome's face and body is increasing by the hour, heh-heh-heh.";
			link.l1 = "I'll get you the doubloons...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Pelly_67_2";
		break;
		
		case "Pelly_67_1":
            dialog.text = "It's not about the size of the shipment-it's about the timing and risks. But suit yourself.";
			link.l1 = "Trust me, I know. Just get the chest ready - I'll take it from here.";
			link.l1.go = "Pelly_10";
		break;
		
		case "Pelly_67_2":
            dialog.text = "Ready, Admiral? Need help with weapons, or are you still short on gold?";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "Finally got enough! Take it and settle this already - it's getting on my nerves.";
				link.l1.go = "Pelly_68";
			}
			link.l2 = "Watch your tone, Cutlass. I`m ready, but I need more time to raise the money.";
			link.l2.go = "Pelly_67";
			link.l3 = "That's way too expensive for a small batch of weapons I can buy wholesale much cheaper! No thanks, I'll handle this myself.";
			link.l3.go = "Pelly_67_1";
		break;
		
		case "Pelly_68":
            dialog.text = "Oh, what a load of doubloons this is! But don't worry - every coin will go toward the plan. Otherwise, Marcus would dig me up from the grave later, heh-heh. Now, off you go to Handsome, Admiral, and tell him everything's set.";
			link.l1 = "I'm the one giving orders here. Now, get moving.";
			link.l1.go = "Pelly_69";
			RemoveDublonsFromPCharTotal(500);
		break;
		
		case "Pelly_69":
            DialogExit();
			sld = characterFromId("Pelly");
			sld.dialog.currentnode = "Pelly_7";
			pchar.questTemp.Mtraxx = "plant_5";
			AddQuestRecord("Roger_3", "30");
			sld = characterFromId("Mrt_Rocur");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "rocur_wait";
			sld.greeting = "Rocur_02";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "Pelly_70":
            dialog.text = "Yeah, that's a problem. What's your plan, Admiral?\nI've scoped out everything about the plantation. Including what goods are in demand here and circulating on the market. If you want to pass yourself off as a legitimate trader, you'd better stock up on those instead of just slamming a pile of gold on the planter's desk.";
			link.l1 = "Makes sense. What kind of goods are we talking about?";
			link.l1.go = "Pelly_48";
			DeleteAttribute(pchar, "questTemp.mtraxx_PlantInfoTovar");
		break;
		
		// Жан Пикар
		case "rocur":
            dialog.text = "What do you want from me?";
			link.l1 = "My friend, I am looking for Jean Picard. Any chance you bear the same name?";
			link.l1.go = "rocur_1";
		break;
		
		case "rocur_1":
            dialog.text = "There is a chance. However, I don't recall your face.";
			link.l1 = "Don't get too rough, Jean. I was sent here by Marcus Tyrex. My orders are to get you out of here.";
			link.l1.go = "rocur_2";
		break;
		
		case "rocur_2":
            dialog.text = "Marcus? Tsh-sh... Hush. I am sorry, friend, I didn't know that. But we shouldn't talk here, fucking guards are everywhere and they are always listening... I see you are a welcome guest among the Spanish, find me in one of the huts at night and we'll talk. I'll be waiting for you, brother.";
			link.l1 = "...";
			link.l1.go = "rocur_3";
		break;
		
		case "rocur_3":
            DialogExit();
			AddQuestRecord("Roger_3", "6");
			LAi_CharacterDisableDialog(npchar);
			Mtraxx_PlantMakeMaxRocurClone();
		break;
		
		case "rocur_4":
            dialog.text = "Well, it's safe here... What's your name, brother?";
			link.l1 = "Captain "+GetFullName(pchar)+". Now tell me, how did you end up in this shit. Tyrex wants to know everything.";
			link.l1.go = "rocur_5";
		break;
		
		case "rocur_5":
            dialog.text = "I was approached by a stranger in a tavern of Willemstad... He asked me to be his companion for plundering some Dutch caravan. I had a brigantine, he had a polacre, a very unique one too. So we chased down a caravan not far from Caracas and plundered it... It was night, we were splitting the plunder when a massive Spanish galleon appeared in the darkness\nMy companion fled and so did I. But there was no way for my damaged brigantine to escape from a galleon and two other ships. They had boarded us and sold all survivors to this place like cattle.";
			link.l1 = "I see. You think it was an accident? I am talking about the galleon.";
			link.l1.go = "rocur_6";
		break;
		
		case "rocur_6":
            dialog.text = "Hell if I knew. They might have heard a gunfight, it was not far from the Main.";
			link.l1 = "Hmm. It's possible. Did you meet your former companion before? Who is he?";
			link.l1.go = "rocur_7";
		break;
		
		case "rocur_7":
            dialog.text = "Never met him before. Said his name was Ignacio Marco, a privateer of England. He made an impression of a serious man, that's why I agreed to participate in this endeavor. He is a seasoned sailor and a captain, that's for sure, he has a dashing crew behind him and his polacre is a beauty, not every day can you see a ship like that one.";
			link.l1 = "Ignacio Marco? An English privateer? Is he Spanish?";
			link.l1.go = "rocur_8";
		break;
		
		case "rocur_8":
            dialog.text = "He is a Portuguese, not a Spanish. What's wrong with a British letter of marque? We have a plenty of the Spanish among our kind, you know that.";
			link.l1 = "I see. Fine, let's talk about your escape from here. Any ideas?";
			link.l1.go = "rocur_9";
		break;
		
		case "rocur_9":
            dialog.text = "What are your numbers?";
			link.l1 = "My ship, a barquentine and men of Pelly the Cutlass. My vessel is stationed in port of Maracaibo. Cutlass has landed at Guajira Bay and set up a camp there.";
			link.l1.go = "rocur_10";
		break;
		
		case "rocur_10":
            dialog.text = "Hmm...";
			link.l1 = "What, did you expect Tyrex to send a ship of the line here?";
			link.l1.go = "rocur_11";
		break;
		
		case "rocur_11":
            dialog.text = "I didn't expect anything. Actually, I am surprised Marcus didn't forget about me.";
			link.l1 = "He didn't, obviously. So, any ideas?";
			link.l1.go = "rocur_12";
		break;
		
		case "rocur_12":
            dialog.text = "No chance to escape from here - this plantation is too well guarded and there are wild jungles around. No point to storm it either, you don't have enough men, plus there is a fort nearby.";
			link.l1 = "Perhaps, you and your boys can help us from inside? Hit them hard from behind.";
			link.l1.go = "rocur_13";
		break;
		
		case "rocur_13":
            dialog.text = "With what? Bare hands and rusty machetes?";
			link.l1 = "And what if you had weapons?";
			link.l1.go = "rocur_14";
		break;
		
		case "rocur_14":
            dialog.text = "Well in that case we would have given them hell. There is a problem though, they check everything you bring inside, there is no way you can smuggle weapons. So I suggest forgeting about this.";
			link.l1 = "And still, that is our best option at the moment. I will think of how to deliver you and your men weapons... Tell me, how many of you are capable of fighting?";
			link.l1.go = "rocur_15";
		break;
		
		case "rocur_15":
            dialog.text = "Thirty heads, I'd say.";
			link.l1 = "Thirty sabers then... Handguns would make a difference too, I believe.";
			link.l1.go = "rocur_16";
		break;
		
		case "rocur_16":
            dialog.text = "Captain, are you serious about this?";
			link.l1 = "I am. I have arrived here on purpose, joking around is not a part of it. What else could you use?";
			link.l1.go = "rocur_17";
		break;
		
		case "rocur_17":
            dialog.text = "Very well... Let's give it a try at least. We need simple cold steel - my boys are not trained to work with fancy rapiers and such. Same can be said about handguns, the cheapest will do just fine. If you get us a musket or two that would help us a lot too, I have a couple of boys who are good with muskets. Bullets, gunpowder. Healing potions are the most welcome.";
			link.l1 = "Got it. Blades and axes can be taken from the ship's arsenal. The rest is more tricky to get. I will let you know when I have it all.";
			link.l1.go = "rocur_18";
		break;
		
		case "rocur_18":
            dialog.text = "Please hurry up, brother. We don't have a half a year here, this fucking cattle work is killing us one by one. If you'll need me - come see me at nights.";
			link.l1 = "Got it, pal. Hold on, I'll try not to keep you waiting. And be careful, don't give them a reason to write you off, yet.";
			link.l1.go = "rocur_19";
		break;
		
		case "rocur_19":
            DialogExit();
			AddQuestRecord("Roger_3", "7");
			npchar.dialog.currentnode = "rocur_wait";
			pchar.questTemp.Mtraxx = "plant_3";
			pchar.questTemp.Mtraxx.MagicBox = "Baster";
			AddLandQuestMark(characterFromId("Fadey"), "questmarkmain");
			AddMapQuestMarkCity("baster", false);
			pchar.quest.Mtraxx_PlantPrepareTimeOver.over = "yes"; //снять таймер
			SetFunctionTimerCondition("Mtraxx_SeekWeaponOver", 0, 0, 30, false); // таймер
		break;
		
		case "rocur_wait":
            dialog.text = "Any news, pal? Have you gathered weapons?";
			if (pchar.questTemp.Mtraxx == "plant_5")
			{
				link.l1 = "Yes. A chest with munitions is at Guajira Bay. All that left is to find a way to sneak it inside the plantation.";
				link.l1.go = "rocur_20";
			}
			else
			{
				link.l1 = "I am on it. Wait.";
				link.l1.go = "rocur_wait_1";
			}
		break;
		
		case "rocur_wait_1":
            DialogExit();
			npchar.dialog.currentnode = "rocur_wait";
		break;
		
		case "rocur_20":
            dialog.text = "Very well, captain. I have been thinking on how to perform that already.";
			link.l1 = "Glad to hear it. What's on your mind?";
			link.l1.go = "rocur_21";
			DelLandQuestMark(npchar);
		break;
		
		case "rocur_21":
            dialog.text = "They produce sugar and grow cocoa beans on this plantation. Sometimes its head sells the goods himself, it's more profitable that way. Make him an offer. Pay him not with money but with goods. Something you can put into boxes like copra, vanilla or coffee. Put some effort in bargaining but don't overdo it\nStash weapons in one or two boxes and put marks on them. Arrange an exchange at evening so they will have to leave the boxes outside for a night\nAt night we will find your marked boxes, arms ourselves and give hell to the Spanish. With your help of course.";
			link.l1 = "Nice thinking here, brother! Very good, I like this plan. Let's stick to it.";
			link.l1.go = "rocur_22";
		break;
		
		case "rocur_22":
            dialog.text = "One last thing - offer only one type of goods to exchange. More types of goods - more boxes checked by the guards.";
			link.l1 = "I agree. I'll pick only one type then. Coffee, vanilla and copra, you said?";
			link.l1.go = "rocur_23";
		break;
		
		case "rocur_23":
            dialog.text = "Yes. This will sound like a good deal to the head of plantation.";
			link.l1 = "Got it. I'll let you know when the deal is stuck.";
			link.l1.go = "rocur_24";
		break;
		
		case "rocur_24":
            DialogExit();
			AddQuestRecord("Roger_3", "9");
			npchar.dialog.currentnode = "rocur_wait_2";
			pchar.questTemp.Mtraxx = "plant_6";
			pchar.questTemp.mtraxx_PlantInfoTovar = true;
			AddLandQuestMark(characterFromId("Pelly"), "questmarkmain");
		break;
		
		case "rocur_wait_2":
            dialog.text = "Go my friend, time is golden and we got none...";
			link.l1 = "";
			link.l1.go = "rocur_wait_3";
		break;
		
		case "rocur_wait_3":
            DialogExit();
			npchar.dialog.currentnode = "rocur_wait_2";
		break;
		
		case "rocur_25":
            dialog.text = "...";
			link.l1 = "(quietly) The deal is struck. The boxes will be delivered to the plantation tomorrow evening. The boxes you need are marked with a 'W' letter. Others have the rest of the alphabet on them. Get you men ready. We shall attack before dawn somewhere around three o'clock.";
			link.l1.go = "rocur_25x";
			DelLandQuestMark(npchar);
		break;
		
		case "rocur_25x":
            dialog.text = "We will start with your signal...";
			link.l1 = "";
			link.l1.go = "rocur_26";
		break;
		
		case "rocur_26":
            DialogExit();
			LAi_CharacterDisableDialog(npchar);
			DoQuestFunctionDelay("Mtraxx_PlantWaitDay", 3.0);
		break;
		
		case "rocur_27":
            dialog.text = "Finally! I am about to see the sea again! I have already forgotten its look and its smell. Nicely done captain! I owe you.";
			link.l1 = "Don't worry about it, we'll settle it later... Now let's embark and get out of here!";
			link.l1.go = "rocur_28";
		break;
		
		case "rocur_28":
            DialogExit();
			sld = characterFromId("Pelly");
			sld.Dialog.currentnode = "Pelly_16";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "rocur_29":
            dialog.text = "Greetings "+pchar.name+". Glad to see you again, also glad to have you as my companion in this adventure. This job is gonna be tough but I am sure we'll make it through.";
			link.l1 = "Nice seeing you again Picard. I am all ears, tell me about this adventure of yours.";
			link.l1.go = "rocur_30";
		break;
		
		case "rocur_30":
            dialog.text = "I've already told Marcus, now I will tell you. When I was a slave on the plantation in Maracaibo I learnt something from the Spanish. They are quite talkative when they are drunk... Listen, South-East from Maracaibo bay there is a small village. It's hidden between two mountains deep in the jungles. Hell of name it has: Santiago-de-Los-Caballeros-de-Merida. Let's call it Merida\nDoesn't sound very interesting yet, huh? The mountains surrounding the village turned out to be rich with gems. Emeralds, opals and legendary fire opals\nAs far as I understand, Merida's settlers didn't tell the general-governor about these gems. However soon he will learn about it, this is why we should visit Merida before the arrival of Spanish colonial officers.";
			link.l1 = "Do you wanna to plunder the settlement?";
			link.l1.go = "rocur_31";
		break;
		
		case "rocur_31":
            dialog.text = "Exactly. It is lost among jungles and mountains with a small garrison - an easy pray for a corsair unit. Besides, they are long way from the sea, they don't expect anybody to attack them except savages with spears and bows.";
			link.l1 = "How much are you sure that the settlement does have precious stones?";
			link.l1.go = "rocur_32";
		break;
		
		case "rocur_32":
            dialog.text = "If our adventures turns to be a false trace I myself will serve on your vessel as an officer or as a sailor, I will be cleaning decks and fight in countless boardings until my debt to you and Marcus is wiped away.";
			link.l1 = "I see... Very well, do you know how to get to Merida?";
			link.l1.go = "rocur_33";
		break;
		
		case "rocur_33":
            dialog.text = "Of course I don't know the exact path through the jungles, but we will hire a guide from Indian folk. We should land South of Maracaibo lake, find an Indian village and find those who know how to get there.";
			link.l1 = "...";
			link.l1.go = "rocur_34";
		break;
		
		case "rocur_34":
            DialogExit();
			sld = characterFromId("Terrax");
			sld.Dialog.currentnode = "mtraxx_38";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rocur_35":
            dialog.text = "Captain I am deeply sorry for my language but why the actual fuck are we not in Merida yet? Huh? You had spit on our common cause! Leprechaun and I are leaving without you. I will explain everything to Tyrex and you should go. Here, take 50 000 pesos for your help in Maracaibo, I borrowed them from friends. Farewell, damn shame, I thought better of you.";
			link.l1 = "Hmm... I'm sorry.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_MeridaTimeOverFail");
		break;
		
		case "rocur_36":
            dialog.text = "Here we are. Jungles ahead. First, we should find an Indian village and ask around for a guide.";
			link.l1 = "Let's do it. Luke, do you have anything to say... or perhaps an advice?";
			link.l1.go = "rocur_37";
		break;
		
		case "rocur_37":
            DialogExit();
			sld = characterFromId("Lepricon");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rocur_38":
            dialog.text = "Merida's garrison is finished. I don't expect any serious resistance inside the village. Let's go!";
			link.l1 = "Charge!!!";
			link.l1.go = "rocur_39";
		break;
		
		case "rocur_39":
            DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Merida_ExitTown", "reload1_back", true);
			pchar.quest.mtraxx_merida_town.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_town.win_condition.l1.location = "Merida_Town";
			pchar.quest.mtraxx_merida_town.function = "Mtraxx_MeridaTown";
			Mtraxx_MeridaCheckOurWarriors();
			AddQuestRecord("Roger_5", "16");
		break;
		
		case "rocur_40":
            dialog.text = "It's done! No heroes left. Now we should talk to a governor of this 'city'. I hope he is a persuadable type.";
			link.l1 = "I agree let's 'persuade' him!.. Jean! Follow me!";
			link.l1.go = "rocur_41";
		break;
		
		case "rocur_41":
            DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Merida_Town", "gate_back", true);
			pchar.quest.mtraxx_merida_townhall.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_townhall.win_condition.l1.location = "Merida_townhall";
			pchar.quest.mtraxx_merida_townhall.function = "Mtraxx_MeridaTownhall";
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			sld = characterFromId("Lepricon");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			AddQuestRecord("Roger_5", "17");
		break;
		
	case "rocur_42": //злой вариант
            DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Merida_Town", "reload3", true); 
			pchar.questTemp.Mtraxx = "merida_success";
			pchar.quest.mtraxx_merida_exit.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_exit.win_condition.l1.location = "Merida_Town";
			pchar.quest.mtraxx_merida_exit.function = "Mtraxx_MeridaExit";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			
			sld = characterFromId("Merida_Head");
			LAi_SetActorType(sld);
			
			pchar.questTemp.Mtraxx_MeridaZloVariant = true;
			
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "reload", "reload1", "Mtraxx_MeridaExitResidensia", -1);
		break;
		
		case "rocur_43": //мирный вариант
            DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Merida_Town", "reload3", true); 
			pchar.questTemp.Mtraxx = "merida_success";
			pchar.quest.mtraxx_merida_exit.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_exit.win_condition.l1.location = "Merida_Town";
			pchar.quest.mtraxx_merida_exit.function = "Mtraxx_MeridaExit";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			
			sld = characterFromId("Merida_Head");
			LAi_SetActorType(sld);
			
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto2", "Mtraxx_MeridaGiveJewelry", -1);
			
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "reload", "reload1", "Mtraxx_MeridaExitResidensia", -1);
		break;
		
		case "rocur_44":
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaKamushki"))
			{
            	dialog.text = "Nicely done, "+pchar.name+"! Time to split shares. I already have the numbers. There were almost 2000 gems in the chest: 1560 emeralds, 1032 opals and 363 fire opals. Your cut is the third: 350 emeralds, 244 opals and 63 fire opals. Here, take them.";
            }
            else
           	{
           	dialog.text = "Nicely done, "+pchar.name+"! Time to split shares. I already have the numbers. There were almost 2000 gems in the chest: 1050 emeralds, 732 opals and 189 fire opals. Your cut is the third: 350 emeralds, 244 opals and 63 fire opals. Here, take them.";
           	}
			link.l1 = "Nice!";
			link.l1.go = "rocur_45";
		break;
		
		case "rocur_45":
			PlaySound("interface\important_item.wav");
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaKamushki"))
			{
				TakeNItems(pchar, "jewelry4", 520);
				TakeNItems(pchar, "jewelry16", 334);
				TakeNItems(pchar, "jewelry14", 121);
			}
			else
			{
				TakeNItems(pchar, "jewelry4", 350);
				TakeNItems(pchar, "jewelry16", 244);
				TakeNItems(pchar, "jewelry14", 63);
			}
            dialog.text = "Now let's talk about my debt to you for my rescue. I understand you had serious expenses. What compensation will you consider to be fair? I am paying from my share of gems.";
			link.l1 = "A third of your share will suffice. You need money too - to buy and supply a ship, to pay your crew...";
			link.l1.go = "rocur_46";
		break;
		
		case "rocur_46":
			PlaySound("interface\important_item.wav");
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaKamushki"))
			{
				TakeNItems(pchar, "jewelry4", 173);
				TakeNItems(pchar, "jewelry16", 111);
				TakeNItems(pchar, "jewelry14", 40);
			}
			else
			{
				TakeNItems(pchar, "jewelry4", 116);
				TakeNItems(pchar, "jewelry16", 81);
				TakeNItems(pchar, "jewelry14", 21);
			}
            dialog.text = "Thank you friend! I thought you would ask no less than a half. I do need money now. Here, take the gems.";
			link.l1 = "What a raid Jean! Let's head to Hispaniola, to Tyrex.";
			link.l1.go = "rocur_47";
		break;
		
		case "rocur_47":
            DialogExit();
			chrDisableReloadToLocation = false;
			pchar.questTemp.Mtraxx = "merida_gohome";
			AddQuestRecord("Roger_5", "18");
			sld = characterFromId("Mrt_Rocur");
			LAi_SetWarriorType(sld);
			LAi_CharacterDisableDialog(sld); // релиз-правка
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			sld = characterFromId("Lepricon");
			LAi_SetWarriorType(sld);
			LAi_CharacterDisableDialog(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			sld = characterFromId("Terrax");
			sld.dialog.currentnode = "mtraxx_40";
			pchar.quest.mtraxx_merida_lavega.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_lavega.win_condition.l1.location = "Hispaniola1";
			pchar.quest.mtraxx_merida_lavega.function = "Mtraxx_IgnasioKitty";
			// таймер на доплыть домой 40 дней
			SetFunctionTimerCondition("Mtraxx_MeridaReturnLate", 0, 0, 40, false);
			DeleteAttribute(pchar, "GenQuest.HunterLongPause");
		break;
		
		case "rocur_48":
            dialog.text = "Oh, what a meeting! Pleasure to see you, "+pchar.name+". How are you doing?";
			link.l1 = "Pretty good. Found Red Wolf's treasures just recently. Now heading to Martinique to meet one common friend of ours. You want to see Tyrex?";
			link.l1.go = "rocur_49";
		break;
		
		case "rocur_49":
            dialog.text = "Yeah. Want to talk with him regarding Pasquale Lavoisier. Marcus sent me to that half bandit-half merchant. I did what he asked and he paid with some shit claiming it to be a bloody good payment. I would kill the fucker right where he was standing, but Marcus asked to treat him with respect... then it is him to deal with this trouble.";
			link.l1 = "I'm sorry but Marcus will do nothing. Four-eyes is in business with him.";
			link.l1.go = "rocur_50";
		break;
		
		case "rocur_50":
            dialog.text = "What the fuck?";
			link.l1 = "Yeah, but I didn't tell you about this, alright? Lavoisier screwed me too not too long ago. Tyrex asked me to help him, just like he asked you. I was warned at Isla Tesoro that crossing the four-eyes is the same as crossing Marcus. So I suggest you forgeting about this. You are neither the first nor the last in this.";
			link.l1.go = "rocur_51";
		break;
		
		case "rocur_51":
            dialog.text = "I see. You too got screwed by those two then?";
			link.l1 = "Well, yes. I was thinking to make some troubles to the four-eyes too before I learnt more about him. It's not worth it.";
			link.l1.go = "rocur_52";
		break;
		
		case "rocur_52":
            dialog.text = "Would you try to repay the bastard if you knew that no one will ever find out?";
			link.l1 = "Ha! Sure I would! Although I don't know how. Attack the flutes of Lavoisier and one shiny day your sailors will get drunk and blab everything out. Don't you know how it works?";
			link.l1.go = "rocur_53";
		break;
		
		case "rocur_53":
            dialog.text = "Are you heading to Martinique now? When will you arrive to La Vega again?";
			link.l1 = "Marcus gave me three weeks.";
			link.l1.go = "rocur_54";
		break;
		
		case "rocur_54":
            dialog.text = "Try to make it in two. I'll think it through... Find me in Gonaives Bay in 14 days. Head right there, and don't enter La Vega.";
			link.l1 = "I can see you are up to something, ha-ha. Fine. I'll try.";
			link.l1.go = "rocur_55";
		break;
		
		case "rocur_55":
            dialog.text = "You'd better do that. See you!";
			link.l1 = "...";
			link.l1.go = "rocur_56";
		break;
		
		case "rocur_56":
            DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3", "none", "", "", "", 10.0);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			ReOpenQuestHeader("Roger_4");
			AddQuestRecord("Roger_4", "11");
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1.date.hour  = 1.0;
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 14);
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 14);
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 14);
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l2 = "location";
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l2.location = "Shore34";
			pchar.quest.mtraxx_pasq_gonaiv.function = "Mtraxx_PasqualeJanGonaiv";
			SetFunctionTimerCondition("Mtraxx_PasqualeJanTimer", 0, 0, 10, false); // правки прогона 3
			SetFunctionTimerCondition("Mtraxx_PasqualeJanTimeOver", 0, 0, 15, false);
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			pchar.questTemp.Mtraxx.Pasquale.Grabbing = "true";
		break;
		
		case "rocur_57":
			if (pchar.location.from_sea != "Shore34")
			{
				dialog.text = RandSwear()+"Where is your ship? Did you arrive here from La Vega? Merde! I asked you to come here unnoticed and in secret. My plan is ruined now. Damn it!..";
				link.l1 = "Hm...";
				link.l1.go = "rocur_58";
			}
			if (GetOfficersQuantity(pchar) > 0)
			{
				dialog.text = "There you are , "+pchar.name+". It's good you are here. Send your mates back to the ship. It's a private conversation.";
				link.l1 = "Very well.";
				link.l1.go = "rocur_59";
			}
			else
			{
				dialog.text = "There you are , "+pchar.name+". It's good you are here.  I have a business for you. Ready to hear it?";
				link.l1 = "Sure!";
				link.l1.go = "rocur_61";
			}
		break;
		
		case "rocur_58":
            DialogExit();
			Group_DelCharacter("RocurSeaGroup", "Mrt_Rocur");
			Group_DeleteGroup("RocurSeaGroup");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "OpenTheDoors", 10.0);
			AddQuestRecord("Roger_4", "14");
			CloseQuestHeader("Roger_4");
		break;
		
		case "rocur_59":
            DialogExit();
			LAi_SetStayType(npchar);
			npchar.dialog.currentnode = "rocur_60";
		break;
		
		case "rocur_60":
            if (GetOfficersQuantity(pchar) > 0)
			{
				dialog.text = "I told you already - send your officers away!";
				link.l1 = "Yes-yes, I got it.";
				link.l1.go = "rocur_59";
			}
			else
			{
				dialog.text = "Great. Now we can talk freely. I have a business for you. Ready to hear it out?";
				link.l1 = "Sure!";
				link.l1.go = "rocur_61";
			}
		break;
		
		case "rocur_61":
            dialog.text = "Do you know La Vega well?";
			link.l1 = "Well... I think I do. Why are you asking?";
			link.l1.go = "rocur_62";
			npchar.greeting = "";
		break;
		
		case "rocur_62":
            dialog.text = "Ever noticed the store house on the right from the local store? The only big house among the shacks.";
			link.l1 = "The always closed one? Yeah, I have seen it. What about it?";
			link.l1.go = "rocur_63";
		break;
		
		case "rocur_63":
            dialog.text = "Nicely noticed - it's always closed. While you were on your mission at Martinique, our common friend Lavoisier had been here for a three days as guest of Marcus Tyrex. They were spending their time in this house drinking rum and having fun.";
			link.l1 = "Hm...";
			link.l1.go = "rocur_64";
		break;
		
		case "rocur_64":
            dialog.text = "Then Lavoisier's men dragged some boxes and packages into the house. Then he left. As for Marcus, he stays in that place every day for several hours.";
			link.l1 = "Any suggestions?";
			link.l1.go = "rocur_65";
		break;
		
		case "rocur_65":
            dialog.text = "What suggestions? I'm sure this house must be a base of Lavoisier in La Vega. I didn't see much through the window but there are goods stored there. I think that the four-eyes has the means to repay what he owes us.";
			link.l1 = "Well-well... Do you want to break in? What about the closed door? It's heavy and sturdy, no way we are breaking in quietly.";
			link.l1.go = "rocur_66";
		break;
		
		case "rocur_66":
            dialog.text = ""+pchar.name+", do you think of me as an idiot? I have already sorted it out. I have made the key using a wax mask of the lock. Costed my quite a penny, but it's my problem.";
			link.l1 = "Heh! Why wait for me then?";
			link.l1.go = "rocur_67";
		break;
		
		case "rocur_67":
            dialog.text = "It will be safer that way, besides you are the only one I could trust. One head is good, two heads are better, and four eyes are better than two.";
			link.l1 = "Well yeah, crossing Lavoisier will take as many eyes as he has, ha-ha-ha! But what of Tyrex? What if he enters the house while we are checking Pasquale's belongings?";
			link.l1.go = "rocur_68";
		break;
		
		case "rocur_68":
            dialog.text = "He won't. He is always back to his own house by the midnight. Ready to go to La Vega next night? They won't ever realize who fucked them up: you are still at Martinique and I left La Vega a week ago.";
			link.l1 = "I'd love to screw the four-eyed enculé. But tell me Jean, how are we supposed to carry barrels and chests from the house?";
			link.l1.go = "rocur_69";
		break;
		
		case "rocur_69":
            dialog.text = "I am sure we will find there more valuable items than chests and barrels with goods, which will be much lighter. So, are you in?";
			link.l1 = "Hell yeah I am!";
			link.l1.go = "rocur_70";
		break;
		
		case "rocur_70":
            dialog.text = "Great, glad I wasn't wrong about you. Let's take a rest now, we are heading to La Vega at midnight.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNight");
		break;
		
		case "rocur_71":
            dialog.text = "Time to go. We should rob this bastard and get the hell out of there before dawn.";
			link.l1 = "Onwards!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNightMarch");
			SetLocationCapturedState("LaVega_town", true);
			LAi_LoginInCaptureTown(npchar, true);
		break;
		
		case "rocur_72":
            dialog.text = "Hush... Now move, quietly, to Pasquale's house. Follow me.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNightToHouse");
		break;
		
		case "rocur_73":
            dialog.text = "Look at this - so much stuff lying around. Let's begin. Check a chest near the door, then go upstairs and take of a room. I will stay here: I know the tricks of hiding valuables among the junk. Keep your eyes and ears open and stay away from the windows.";
			link.l1 = "Alright...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNightInHouse");
		break;
		
		case "rocur_74":
            dialog.text = ""+pchar.name+", what do you have? Anything of interest?";
			link.l1 = "Come and look. This is something.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeJanSeeGirl");
		break;
		
		case "rocur_75":
            dialog.text = "Damn it! Now I see why Tyrex comes to this place every day. It's not only the four-eyed's storehouse but also a brothel.";
			link.l1 = "Looks like she is a slave here.";
			link.l1.go = "rocur_76";
		break;
		
		case "rocur_76":
            dialog.text = "Sure thing. Look at her - she is an obvious port whore... Bad luck for us. We have to kill her.";
			link.l1 = "Do we really?";
			link.l1.go = "rocur_77";
		break;
		
		case "rocur_77":
            dialog.text = "She saw our faces and heard your name. She will tell everything to Tyrex.";
			link.l1 = "Hm...";
			link.l1.go = "rocur_78";
		break;
		
		case "rocur_78":
            dialog.text = "It's your choice. Her life may cost you yours.";
			link.l1 = "";
			link.l1.go = "rocur_79";
		break;
		
		case "rocur_79":
            DialogExit();
			sld = characterFromId("Mirabella");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rocur_80":
            dialog.text = "Don't even think of trusting this whore. Tomorrow Tyrex will know everything. Do you want to receive a black mark?";
			link.l1 = "No, I don't. And I don't want to kill the wench - I have a use for her. She is coming with me.";
			link.l1.go = "rocur_81";
		break;
		
		case "rocur_81":
            dialog.text = "Don't be an idiot! She will run away as soon as she gets a chance. Look at her forehead, do you see the brand? She is a thief.";
			link.l1 = "Hm. You are probably right, Jean. Very well, finish her and let's get away from here.";
			link.l1.go = "rocur_82";
			link.l2 = "I am not planning to keep her on my ship. I have a place for her from where she will never escape from, and there are no ears to hear her screams either. She will also keep doing her line of work there... A personal whore, free of charge, he-he!";
			link.l2.go = "rocur_84";
		break;
		
		case "rocur_82":
            DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto6", "", 5);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto7", "Mtraxx_PasqualeJanKillGirl", 5);
		break;
		
		case "rocur_83":
			ChangeCharacterComplexReputation(pchar, "nobility", -10);
            dialog.text = "That's it, there is no way that she will say anything to Marcus now...";
			link.l1 = "Poor girl... hah well as they say, lady luck is a bitch...";
			link.l1.go = "rocur_86";
		break;
		
		case "rocur_84":
            DialogExit();
			sld = characterFromId("Mirabella");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rocur_85":
            dialog.text = "You are a kind man, "+pchar.name+". Why do you wanna bother yourself with her? Ah, whatever, it's your choice. Make sure she is silent while we are leaving.";
			link.l1 = "If she won't be - she is dead.";
			link.l1.go = "rocur_86";
		break;
		
		case "rocur_86":
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Pasquale.Grabbing.Chest")) sTemp = "A bit. A chest full of doubloons, a handful of rubies, a map of Hispaniola and some rum.";
			else sTemp = "Nothing of value.";
            dialog.text = "What did you find?";
			link.l1 = sTemp;
			link.l1.go = "rocur_87";
		break;
		
		case "rocur_87":
			Log_Info("You have received two treasure collections.");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "icollection", 2);
            dialog.text = "More luck on my side. Here, take your cut. I would never manage to take it all with me to the shore. The four-eyes paid us in full.";
			link.l1 = "Splendid! Well done, Jean!";
			link.l1.go = "rocur_88";
		break;
		
		case "rocur_88":
            dialog.text = "Now go!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNightOutHouse");
		break;
		
		case "rocur_89":
			PlaySound("VOICE\English\LE\Rocur\Rocur_04.wav");
            dialog.text = "Great. It's done. Nice and quiet. Now, let's head back to the ships.";
			link.l1 = "Hah, good idea.";
			link.l1.go = "rocur_89_1";
			//AddDialogExitQuestFunction("Mtraxx_PasqualeNightGulf");
		break;
		
		case "rocur_89_1":
			DialogExit();
			DoFunctionReloadToLocation("shore34", "goto", "goto13", "Mtraxx_PasqualeFinal");
		break;
		
		case "rocur_90":
			PlaySound("VOICE\English\LE\Rocur\Rocur_05.wav");
            dialog.text = "Well, "+pchar.name+". It's time we part our ways. I am not sure we will ever meet again but know that it was a pleasure knowing you friend.";
			link.l1 = "Ah come now, we will see each other often in La Vega.";
			link.l1.go = "rocur_91";
			SetLocationCapturedState("LaVega_town", false);
			LAi_LoginInCaptureTown(npchar, false);
		break;
		
		case "rocur_91":
            dialog.text = "No. I am done with Tyrex. This mess with Lavoisier was the last straw.";
			link.l1 = "Hmm... I see, just forget about it. We've got what was ours by right. Tyrex gives profitable leads, doesn't he? Last time I made more than a half a million from Red Wolf's treasure.";
			link.l1.go = "rocur_92";
		break;
		
		case "rocur_92":
            dialog.text = "Tell me then, did you put a lot of effort for finding it?";
			link.l1 = "Well... It wasn't easy. Did plenty of thinking, travelling and fighting. It was worth it, I think.";
			link.l1.go = "rocur_93";
		break;
		
		case "rocur_93":
            dialog.text = "How much did you pay to Tyrex?";
			link.l1 = "A third.";
			link.l1.go = "rocur_94";
		break;
		
		case "rocur_94":
            dialog.text = "What was his part in this business? What did Marcus do exactly?";
			link.l1 = "Hm... He has given me Red Wolf's log...";
			link.l1.go = "rocur_95";
		break;
		
		case "rocur_95":
            dialog.text = "And that's all? Right?";
			link.l1 = "Well... I would never had learnt about captain Wulfric otherwise...";
			link.l1.go = "rocur_96";
		break;
		
		case "rocur_96":
            dialog.text = ""+pchar.name+", don't you see that Tyrex makes others to do the dirty work? You think that he would give you a task to find that treasure if he could do it on his own? Hell no! I bet that he tried to do it himself first and when he fucked it all up, he called you to do the job. And while you were doing the thinking, spending weeks in the sea, fighting and risking your own life, this bastard along his disgusting four-eyed friend were fucking the whore in La Vega. And for this he also got a quarter of million pesos. Just like that\nYou think he sent his dog Leprechaun to help us in our raid for Merida? No, he wanted to make sure that his interests are safe. Everything Marcus can do on his own, he does, either alone or with the help from Cutlasses, Balds, Leprechauns and other dumb idiots who work for him for pennies. People like you and I we get leads that Marcus is too stupid to execute on his own\nRemember all tasks you did for him? Count how much did he make on you. I've had enough of this. Now I have the money, a great corvette, and loyal crew... from now on I am a freelancer. I'm heading to Jamaica, perhaps I will receive a letter of marque there.";
			link.l1 = "I don't think you are quite right about Tyrex... But I wish you luck Jean! Hope you'll find success in Jamaica.";
			link.l1.go = "rocur_97";
		break;
		
		case "rocur_97":
            dialog.text = "I will. Best of luck to you too and think of what I've said. Being Marcus' bitch is not the best role for you, I know that you are capable of much more. Well... farewell brother! Godspeed!";
			link.l1 = "Good hunting, Jean!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeAddComplete");
		break;
		
		case "rocur_98":
            dialog.text = ""+pchar.name+", tell me, how did we spend so much time in the jungles? Now my plan is screwed. Eh... Bye, pal...";
			link.l1 = "Heh...";
			link.l1.go = "rocur_99";
		break;
		
		case "rocur_99":
            DialogExit();
		    LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 10.0);
			sld.lifeday = 0;
			Group_DeleteGroup("RocurSeaGroup");
			AddQuestRecord("Roger_4", "18");
			CloseQuestHeader("Roger_4");
		break;
		
		case "rocur_100":
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaZloVariant"))
			{
				dialog.text = "Time to leave, boys. Damn, Prince, you surprised me. Burned a whole city, but refused to get your hands dirty when it mattered.";
				link.l1 = "I didn't order the city burned!";
				link.l1.go = "rocur_101";
			}
			else
			{
				dialog.text = "Time to leave, boys. Lucas, you missed out. The Prince handled it brilliantly – and turned a good profit!";
				link.l1 = "What about the city, Handsome?! I gave my word!";
				link.l1.go = "rocur_102";
			}
			sld = CharacterFromID("Lepricon");
			CharacterTurnToLoc(sld, "reload", "reload3");
		break;
		
		case "rocur_101":
            dialog.text = "At least you didn't try to save it. Otherwise, our men would've gutted you first. It's been a tough day for them. They deserved to let off some steam. You'll get used to it. You've got all the makings for it.";
			link.l1 = "Thanks for the advice, but I don't recall asking for it. Let's go.";
			link.l1.go = "rocur_103";
		break;
		
		case "rocur_102":
            dialog.text = " I thought you were joking. Well... you were too hasty. The city's finished. That's how it always is when the Brethren of the Coast get to work. You'll get used to it.";
			link.l1 = "I'm not sure I will. Fine, let's go.";
			link.l1.go = "rocur_103";
		break;
		
		case "rocur_103":
            DialogExit();
			LAi_SetPlayerType(pchar);
			DeleteAttribute(pchar, "questTemp.lockedMusic");
			EndQuestMovie();
			locCameraTarget(PChar);
			locCameraFollow();
			sld = characterFromId("Tagofa");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			Mtraxx_MeridaCheckOurWarriors();
			AddQuestRecord("Roger_5", "12");
		break;
		
		case "rocur_104":
            dialog.text = "Mate... what was that just now?";
			link.l1 = "What, didn't you get it? I bought you. You once said I had access to the Spaniards, so I made use of it.";
			link.l1.go = "rocur_105";
		break;
		
		case "rocur_105":
            dialog.text = "I got that - I'm not an idiot. But weren't we working on a different plan?";
			link.l1 = "Well, Cutlass and I figured it wouldn't sit right if you ended up dead during an uprising or a chase, so we decided to buy you outright.";
			link.l1.go = "rocur_106";
		break;
		
		case "rocur_106":
            dialog.text = "Hah, don't insult me. I'm one of Terrax's captains, after all. I know how to hold a blade.";
			link.l1 = "I don't doubt that, but are you seriously upset about being free?";
			link.l1.go = "rocur_107";
		break;
		
		case "rocur_107":
            dialog.text = "No, no - I'm grateful. It's just... wasn't it a bit much to spend all that gold? I feel sick just thinking about it. The planter, on the other hand, looked as shiny as a polished silver tray.";
			link.l1 = "Yeah, 'The Deal of the Century,' indeed. It stings a bit, sure. But time is more precious than gold, Jean. Searching pistols and medicine for all of you...";
			link.l1.go = "rocur_108";
		break;
		
		case "rocur_108":
            dialog.text = "I'm grateful, but mate, you're a fool - -no offense. I told you my lads aren't great with swords. But anyone can pull a trigger. You could've brought any pistols and medicine from the hold, like with the cutlasses and axes - they're not picky.";
			link.l1 = "Hmm, honestly, I hadn't thought of that... Anyway, let's go - Cutlass's probably getting impatient.";
			link.l1.go = "rocur_109";
		break;
		
		case "rocur_109":
			DialogExit();
			DoFunctionReloadToLocation("Shore37", "goto", "goto6", "Mtraxx_PlantPlantVykup_3");
		break;
		
		// Люк Лепрекон
		case "lepricon":
            dialog.text = "Greetings, captain "+GetFullName(pchar)+". Luke the Leprechaun is at your service! I've been told we are going to the jungles of Southern Main.";
			link.l1 = "Precisely. Embark on long boats, we are leaving at once.";
			link.l1.go = "lepricon_1";
		break;
		
		case "lepricon_1":
            dialog.text = "Let an old buccaneer to give you some advice, captain. Since we are heading to the selva - we will surely meet the Indians. Take presents for them with you. Indian warriors adore beautiful pistols, especially the dueling ones. They also like compasses and spy glasses. They treat them as magic items\nTheir women prefer cheap jewels and trinkets like mirrors and scallops. If we run into a fight with them use trombones and arquebuses: grapeshot in general is very good against enemies that don't wear armors. As for the settlement itself, I suggest guns that can use paper cartirges.";
			link.l1 = "Very good, Luke. Your words are noted. Welcome aboard.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_MeridaSail");
		break;
		
		case "lepricon_2":
            dialog.text = "See the chieftain as soon as we get to the village. And bring gifts, it's pointless otherwise. Make sure to ask about anyone among his people if they know about secret passages in the jungles ahead, and ask for those that have no fear of travelling. I am coming with you, address me in case you face any difficulties.";
			link.l1 = "Let's go! Jean, Luke - follow me!";
			link.l1.go = "exit";
			npchar.greeting = "Lepricon_02";
			AddDialogExitQuestFunction("Mtraxx_MeridaSeekVillage");
		break;
		
		case "lepricon_3":
            dialog.text = "Any questions, captain?";
			link.l1 = "None for now, Luke.";
			link.l1.go = "lepricon_3x";
			if (pchar.questTemp.Mtraxx == "merida_advice")
			{
				link.l1 = "Yes! I had a talk with their chieftain, I gifted him and later he summoned his redskins for a meeting. There are those among them who know how to get to Merida yet nobody is eager to go - they fear another tribe called Capongs. Those scare the locals shitless. The redskin bastard claims that we have no chances to find the path on our own and that there is no guide for us to hire. So what are we supposed to do now, huh?!";
				link.l1.go = "lepricon_4";
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Merida.Potion") && GetCharacterItem(pchar, "potion3") >= 12)
			{
				link.l2 = "I have antidotes with me.";
				if (GetCharacterItem(pchar, "potion3") > 42) link.l2.go = "lepricon_7";
				else link.l2.go = "lepricon_6";
			}
		break;
		
		case "lepricon_3x":
           DialogExit();
		   npchar.dialog.currentnode = "lepricon_3";
		break;
		
		case "lepricon_4":
            dialog.text = "Hmm, I see... Captain you must know that cowardice is often beaten by a greed. Promise a reward so generous that a man will take the job... You know what actually? Try a more cunning option - their women. Gift them and ask about their men and chances are that you will find the guide we need. Promise her piles of beads and mirrors for her husband's assistance. Be generous and promise a lot, persuade them.";
			link.l1 = "Heh! Well the least I can do is try, although I am not sure if it will work...";
			link.l1.go = "lepricon_5_1";
			DelLandQuestMark(npchar);
		break;
		
		case "lepricon_5_1":
            dialog.text = "Well, there's another option... But it's not exactly a great one, if you catch my drift.";
			link.l1 = "Another option? Lay it on me! I'm not too keen on trotting over to the Indian women and begging them to convince their husbands to join us.";
			link.l1.go = "lepricon_5_2";
		break;
		
		case "lepricon_5_2":
            dialog.text = "This option is as old as time. Show them that they should fear you more than they should fear the Kapongs. You know... You could tell the chief what your pirates could do to all the women in the village, especially his wife and daughters. You could even throw in some threats of torturen\Anyway, I'm sure you'll figure out something to make these Indians fear you. Personally, I'm not a fan of this route, and there are reasons for that.";
			link.l1 = "Reasons? Such as? In my book, it seems like a pretty effective and straightforward solution.";
			link.l1.go = "lepricon_5_3";
		break;
		
		case "lepricon_5_3":
            dialog.text = "For starters, we won't exactly be the toast of the town after that. We might end up walking into a trap or some other nasty situation. And secondly, well... it just doesn't feel right. It's one thing to take out armed opponents, but it's another thing entirely to threaten women. I'd suggest finding a way to handle the Indians more... diplomatically.";
			link.l1 = "Got it, I'll think it over. Maybe I'll try wooing some lady with beads... Or perhaps I'll brainstorm some imaginative ways of torture for the chief's daughters, haha!";
			link.l1.go = "lepricon_5";
		break;
		
		case "lepricon_5":
            dialog.text = "One more thing captain, according to the chief, we may face a hostile tribe of Indians in the jungles, it is very likely that they are just a small group of cannibals but it's better to be safe than sorry. If it's a warlike tribe they will poison their weapons, so make sure to supply your men with antidotes\nMe and my men always have plenty of potions with us. As for your pirates... Just bring me the antidotes and I will see them distributed among your men. I need at least a dozen of potions for this. Make sure you bring some for yourself and your officers as well.";
			link.l1 = "Fine. I'll bring the antidotes.";
			link.l1.go = "lepricon_5x";
		break;
		
		case "lepricon_5x":
           DialogExit();
		   npchar.dialog.currentnode = "lepricon_3";
		   pchar.questTemp.Mtraxx = "merida_advice2";
		   pchar.questTemp.Mtraxx.Merida.Women = "true";
		   pchar.questTemp.Mtraxx.Merida.Potion = "true";
		   AddQuestRecord("Roger_5", "8");
		   sld = characterFromId("Hayamee");
		   LAi_CharacterEnableDialog(sld);
		   AddLandQuestMark(sld, "questmarkmain");
		  // LocatorReloadEnterDisable("Shore_ship3", "boat", false); 
		   bQuestDisableMapEnter = false;
		   DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");// выпустим в море
		   SetFunctionTimerCondition("Mtraxx_MeridaPotionLate", 0, 0, 10, false); // таймер, чтобы не ходил долго
		break;
		
		case "lepricon_6":
			i = GetCharacterItem(pchar, "potion3");
			RemoveItems(pchar, "potion3", i);
			pchar.questTemp.Mtraxx.Merida.Antidote = i;
            dialog.text = "Very well. Give them to me. I'll do the rest.";
			link.l1 = "There...";
			link.l1.go = "lepricon_8";
		break;
		
		case "lepricon_7":
			RemoveItems(pchar, "potion3", 42);
			pchar.questTemp.Mtraxx.Merida.Antidote = 42;
            dialog.text = "Forty-two potions will be enough. The rest you should keep to yourself.";
			link.l1 = "Alright...";
			link.l1.go = "lepricon_8";
		break;
		
		case "lepricon_8":
            DialogExit();
		    npchar.dialog.currentnode = "lepricon_3";
			DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Potion");
		break;
		
		case "lepricon_9":
            dialog.text = "Captain, your Indians - Hayami and Tagofa had been waiting for you to deliver the gifts you'd promised to them too long and left to another village to dance and drink kasheeri. I have a feeling that your manner of doing business will do us no good. I am sorry, but you are out of this. Picard will lead the expedition.";
			link.l1 = "Screw you all then!";
			link.l1.go = "exit";
			AddQuestRecord("Roger_5", "19");
			AddDialogExitQuestFunction("Mtraxx_MeridaHayameeFail");
		break;
		
		case "lepricon_10":
            dialog.text = "Captain, what the hell? We've lost too much time for nothing! I have a feeling that your manner of doing business will do us no good. I am sorry, but you are out of this. Picard will lead the expedition.";
			link.l1 = "Screw you all then!";
			link.l1.go = "exit";
			AddQuestRecord("Roger_5", "20");
			AddDialogExitQuestFunction("Mtraxx_MeridaHayameeFail");
		break;
		
		case "lepricon_11":
            dialog.text = "Captain what the hell? You had ten days to find leather and planks. There is Maracaibo town not far from here! I have a feeling that your manner of doing business will do us no good. I am sorry, but you are out of this. Picard will lead the expedition.";
			link.l1 = "Screw you all then!";
			link.l1.go = "exit";
			AddQuestRecord("Roger_5", "20");
			AddDialogExitQuestFunction("Mtraxx_MeridaHayameeFail");
		break;
		
		case "lepricon_12":
            dialog.text = "Captain, I am sorry but I was supposed to be in La Vega long ago as were you actually. You must had forgotten about the existence of me and Marcus. Anyway, I am leaving. You should keep doing whatever you are doing and I will explain everything to Marcus. Farewell, it's a pity, I thought better of you.";
			link.l1 = "Hmph...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_MeridaReturnFail");
		break;
		
		case "lepricon_13":
			PlaySound("VOICE\English\LE\Leprikon\Lepricon_03.wav");
            dialog.text = "So, as far as I understand, you guys had a fight. Failed to split the booty, right Charlie Prince?";
			link.l1 = "Leprechaun? You are here... No big surprise though. Yeah the greedy bastards had spit on the Code and tried to kill me.";
			link.l1.go = "lepricon_14";
			QuestPointerDelLoc("Judgement_dungeon_05", "reload", "reload1");
			QuestPointerDelLoc("Judgement_dungeon_04", "reload", "reload1");
			QuestPointerDelLoc("Judgement_dungeon_03", "reload", "reload1");
			QuestPointerDelLoc("Judgement_dungeon_02", "reload", "reload1");
			QuestPointerDelLoc("Judgement_dungeon_01", "quest", "lepricon");
		break;
		
		case "lepricon_14":
            dialog.text = "Yeah, they did you quite a beating Prince. You look like wet shit\nWhat did you say about the Code? Let me enlighten you: I had been working with Marcus who is supposedly the Keeper of this Code, I have seen men spit on it so many times I wouldn't dare to count. Some of those men paid a terrible price. Some of them didn't\nYou can do anything you want, if the prize will cover it. Especially if no one is watching.";
			link.l1 = "So... you are here for the treasure as well?";
			link.l1.go = "lepricon_15";
		break;
		
		case "lepricon_15":
            dialog.text = "Such a stupid question. What else would I be doing here, so far from my homeland on Hispaniola? Although after all I am smarter than you all: knowing yours rotten pirate nature. I just waited, letting you rats to tear each other apart leaving only one enemy alive, but wounded and tired.";
			link.l1 = "Enemy? This is how you follow your patron's Code?! He kills people for this!";
			link.l1.go = "lepricon_16";
		break;
		
		case "lepricon_16":
            dialog.text = "I am not a subject to the Code Prince, I am not a pirate. I don't even own a ship - I had to rent a tub to get here. I am nothing more but a buccaneer in a nutshell. I am a hunter, I hunt buffalos and make buccan. Fucking Spanish who claim that we, the French buccaneers, spoil their living, made me seek support and protection from Marcus. I help him in his business for that sometimes\nAlthough I am not a pirate, me and my men fight well, you have seen us in action.";
			link.l1 = "We were raiding and fighting together Leprechaun. We covered each others backs, risking our lives to save another. Is it all but nothing to you?";
			link.l1.go = "lepricon_17";
		break;
		
		case "lepricon_17":
			PlaySound("VOICE\English\LE\Leprikon\Lepricon_04.wav");
            dialog.text = "I'll be honest with you Prince: I never liked you. You are an upstart. An insolent youngster, a fan of drinks and fallen women, who did a few profitable jobs for Tyrex and thought of himself as a great pirate\nBesides, you are butcher by nature. You think Cartagena gave you more weight within the Brethren? Ho-ho, oh hell no, only among the monsters such as you are.";
			link.l1 = "Oh this is hilarious! Ha-ha-ha spoken by a true angel himself! You old bastard!";
			link.l1.go = "lepricon_18";
		break;
		
		case "lepricon_18":
            dialog.text = "I think we have cleared everything out by now. Time to end this comedy. Devils have been waiting for you for far too long in hell.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionLepriconFight");
		break;
		
		case "lepricon_19":
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaZapugivanieIndeets"))
			{
				dialog.text = "Do you like it, huh?";
				link.l1 = "Back off!";
				link.l1.go = "lepricon_20";
			}
			else
			{
				dialog.text = "Well, what do you think?";
				link.l1 = "This isn't funny, Leprechaun. What the hell?! I didn't order a massacre! Don't you think this is too much?! Terrax won't be pleased!";
				link.l1.go = "lepricon_24";
			}
		break;
		
		case "lepricon_20":
            dialog.text = "Why the guilty look, then? Not enjoying it? Let me tell you - things will only get worse. Think today's massacre happened just because it's that kind of day? Hah, sure. This is routine. Picard didn't even flinch. For them, it's just another day doing what they love.";
			link.l1 = "And what about you? Just passing through?";
			link.l1.go = "lepricon_21";
		break;
		
		case "lepricon_21":
            dialog.text = "I'm no pirate. And I'd rather not have been part of today's events. And... if you're so upset by the sight of women's bodies on Merida's blackened soil, why did you act the way you did with the Indians, Prince?";
			link.l1 = "What was I supposed to do? Drop everything and crawl to Marcus with an apology?";
			link.l1.go = "lepricon_22";
		break;
		
		case "lepricon_22":
            dialog.text = "I just thought you'd fully embraced it, started thinking and acting like Tirax's captains. But no, ha! You're too soft for this kind of work. You'd be better off giving your share to Marcus and leaving with your tail between your legs. This isn't your calling.";
			link.l1 = "It's not for you to decide for me, Leprechaun. And you certainly have no right to insult me. I won't give up my share to anyone. I'll split it fairly with Terrax.";
			link.l1.go = "lepricon_23";
		break;
		
		case "lepricon_23":
            dialog.text = "Sure. But we'd better leave before you faint.";
			link.l1 = "That's not funny, damn it.";
			link.l1.go = "lepricon_30";
		break;
		
		case "lepricon_24":
            dialog.text = "Then you don't know him well. Still, since today's events don't bring you joy, listen to what I have to offer.";
			link.l1 = "What could you possibly offer after this?!";
			link.l1.go = "lepricon_25";
		break;
		
		case "lepricon_25":
            dialog.text = "You'd better make an effort to listen, boy.";
			link.l1 = "Hmm, I don't like your tone, Lucas, but fine, go ahead.";
			link.l1.go = "lepricon_26";
		break;
		
		case "lepricon_26":
            dialog.text = "I can afford it - I've lived longer than you, Prince. So I've got a sharp eye, not just for shooting. Want to know what I've noticed?";
			link.l1 = "Just say it!";
			link.l1.go = "lepricon_27";
		break;
		
		case "lepricon_27":
            dialog.text = "You're out of place. Yes, you're good. You're making progress. But only because you're a strong captain, not because this is truly your calling. I don't know how you turned to Terrax, or why, but trust me, this isn't your thing.";
			link.l1 = "I have... a goal. I can't tell you what it is.";
			link.l1.go = "lepricon_28";
		break;
		
		case "lepricon_28":
            dialog.text = "And have you gotten any closer to it?";
			link.l1 = "Not yet.";
			link.l1.go = "lepricon_29";
		break;
		
		case "lepricon_29":
            dialog.text = "Well, if even today didn't bring you closer, there's nothing more to gain here. You're a good guy, Prince. You treated the Indians like humans. It's ironic you ended up here with us. My advice: give your share to Terrax to avoid any issues, and steer clear of all this - save your soul while you can.";
			link.l1 = "I'll think about it.";
			link.l1.go = "lepricon_30";
		break;
		
		case "lepricon_30":
			DialogExit();
			locCameraFromToPos(21.35, 1.54, 0.05, true, 25.55, 0.46, -0.91);
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaZloVariant"))
			{
				PlaySound("People Fight\PistolShot.wav");
				DoQuestFunctionDelay("Mtraxx_MeridaGorit_5", 2.0);
			}
			else
			{
				DoQuestFunctionDelay("Mtraxx_MeridaGorit_5", 0.5);
			}
		break;
		
		// Тагофа - проводник к Мериде
		case "tagofa":
            dialog.text = "Tagofa greets you, son of the sea. Do you want me to show you a way to the Spanish settlement at mountains?";
			link.l1 = "Correct. I see that you are good with our language unlike the rest of your people.";
			link.l1.go = "tagofa_1";
		break;
		
		case "tagofa_1":
            dialog.text = "Tagofa often had dealings with yalanaui... Most of our way we will travel on a river. You will need long boats. Do you have them?";
			link.l1 = "Do you? We could borrow them for little while...";
			link.l1.go = "tagofa_2";
		break;
		
		case "tagofa_2":
            dialog.text = "Our village is small, we have got a very few longboats and all of them are usefull only for fishing. Now, we need good long boats, the ones that will endure a long voyage, like the ones on your ships.";
			link.l1 = "Hmm... We'll need six long boats then. The ship doesn't have that many.";
			link.l1.go = "tagofa_3";
		break;
		
		case "tagofa_3":
            dialog.text = "Build them then. You, white folk, can repair your giant vessels ashore, surely you can make few long boats.";
			link.l1 = "Heh, seems like you are right, Tagofa. Get us to the river, I hope it is not far from here?";
			link.l1.go = "tagofa_4";
		break;
		
		case "tagofa_4":
            dialog.text = "It's not. Follow me.";
			link.l1 = "...";
			link.l1.go = "tagofa_5";
		break;
		
		case "tagofa_5":
           DialogExit();
		   chrDisableReloadToLocation = true;
		   npchar.dialog.currentnode = "tagofa_6";
		   LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Mtraxx_MeridaGotoRiver", 5.0);
		break;
		
		case "tagofa_6":
            dialog.text = "Here is the river I told you about. We will start our journey from here. You build the boats and then we will begin.";
			link.l1 = "Got it, Tagofa. I will tell you when it's done.";
			link.l1.go = "tagofa_7";
		break;
		
		case "tagofa_7":
            DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.dialog.currentnode = "tagofa_8";
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.questTemp.Mtraxx = "merida_boats";
			pchar.questTemp.Mtraxx.Boats = "true";
			chrDisableReloadToLocation = false;
			DoQuestCheckDelay("TalkSelf_Quest", 2.0);
			// Лепрекона - гулять
			sld = characterFromId("Lepricon");
			sld.dialog.currentnode = "lepricon_3";
			LAi_SetWarriorType(sld);
			LAi_warrior_DialogEnable(sld, true);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			SetFunctionTimerCondition("Mtraxx_MeridaBoatLate", 0, 0, 10, false); // таймер, чтобы не ходил долго
		break;
		
		case "tagofa_8":
            dialog.text = "Are the boats ready, white chieftain?";
			link.l1 = "Yes. My men are about to get on them.";
			link.l1.go = "tagofa_9";
		break;
		
		case "tagofa_9":
            dialog.text = "Very good. Get on the first one along with me. Tagofa will show the way.";
			link.l1 = "";
			link.l1.go = "tagofa_10";
		break;
		
		case "tagofa_10":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "none", "", "", "Mtraxx_MeridaRiverTrip", -1);
			chrDisableReloadToLocation = true;
		break;
		
		case "tagofa_11":
            dialog.text = "The river part is done. We not be far from the Spanish settlement from here. There is the pathway, stick to it and we won't get lost. We have managed to round a forest filled with Capong hunters, but here is also their land. We must be careful.";
			link.l1 = "Don't worry. We'll wipe them out as soon as they show us their ugly painted faces.";
			link.l1.go = "tagofa_12";
		break;
		
		case "tagofa_12":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.quest.mtraxx_merida_warning.win_condition.l1 = "locator";
			pchar.quest.mtraxx_merida_warning.win_condition.l1.location = "Serpentine2";
			pchar.quest.mtraxx_merida_warning.win_condition.l1.locator_group = "quest";
			pchar.quest.mtraxx_merida_warning.win_condition.l1.locator = "detector1";
			pchar.quest.mtraxx_merida_warning.function = "Mtraxx_MeridaWarning";
			chrDisableReloadToLocation = false;
		break;
		
		case "tagofa_13":
			StartQuestMovie(true, false, true);
            dialog.text = "";
			link.l1 = "Hey! Tagofa! Look! What is that... in the middle of the pathway? Some Indian thingy.";
			link.l1.go = "tagofa_14";
			locCameraFromToPos(7.63, 9.07, 11.73, true, 2.97, 9.02, 7.70);
			CharacterTurnToLoc(pchar, "quest", "quest1");
		break;
		
		case "tagofa_14":
            DialogExit();
			LAi_SetActorType(pchar);
			LAi_FadeLong("Mtraxx_MeridaWarningCutscene", "");
			locCameraSleep(true);
		break;
		
		case "tagofa_15":
            dialog.text = "It is a sign of Capongs. A warning. It tells you to stop and go no further. Capongs have already spotted us.";
			link.l1 = "And what if we go further? Will they attack us?";
			link.l1.go = "tagofa_16";
		break;
		
		case "tagofa_16":
            dialog.text = "Yes, white chieftain. You must be looking threatening to them since they didn't attack us already. And yet they put a sign for you.";
			link.l1 = "Fuck the sign. We are moving forward... Everyone listen up! At arms! Make ready! Be alerted! If these savages show us their ugly faces we shall kill them all!";
			link.l1.go = "tagofa_17";
		break;
		
		case "tagofa_17":
            DialogExit();
			EndQuestMovie();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.quest.mtraxx_merida_capong.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_capong.win_condition.l1.location = "Merida_jungle_01";
			pchar.quest.mtraxx_merida_capong.function = "Mtraxx_MeridaPrepareCapongAttack";
		break;
		
		case "tagofa_18":
            dialog.text = "White chief and his men crushed the capongas, Tagofa is impressed. Spanish city is close. There is a valley where you will see a waterfall. Tagofa will not go to the Spanish. I'll be waiting for you near the waterfall.";
			link.l1 = "Very well. Onwards!";
			link.l1.go = "tagofa_19";
		break;
		
		case "tagofa_19":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			chrDisableReloadToLocation = false;
			pchar.quest.mtraxx_merida_exittown.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_exittown.win_condition.l1.location = "Merida_ExitTown";
			pchar.quest.mtraxx_merida_exittown.function = "Mtraxx_MeridaExitTown";
			Mtraxx_MeridaCheckOurWarriors();
			AddQuestRecord("Roger_5", "15");
		break;
		
		case "tagofa_20":
            dialog.text = "We have returned, white chief. Tagofa did what he promised.";
			link.l1 = "Gratitude, Tagofa. You did well.";
			link.l1.go = "tagofa_21";
		break;
		
		case "tagofa_21":
            dialog.text = "Tagofa should go. Hayami is waiting for me very much. Good bye son of the sea.";
			link.l1 = "Good luck son of the selva. Send my regards to your wife. And thank you for helping us.";
			link.l1.go = "tagofa_22";
		break;
		
		case "tagofa_22":
            DialogExit();
			chrDisableReloadToLocation = false;
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.quest.mtraxx_merida_final.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_final.win_condition.l1.location = "Shore_ship3";
			pchar.quest.mtraxx_merida_final.function = "Mtraxx_MeridaFinal";
			ChangeIndianRelation(7.0);
		break;
		
		// дозорный у Мериды
		case "merida_guard":
            dialog.text = "Hey! Who are you and what do you want?";
			link.l1 = "We need to get to Merida and have a chat with your governor or whoever you have instead of him...";
			link.l1.go = "merida_guard_1";
		break;
		
		case "merida_guard_1":
            dialog.text = "We don't let strangers to Merida. Leave!";
			link.l1 = "Pal we were rowing hard for two days and then fighting hordes of Indians not to leave just like that. I repeat, I want to talk to the head of your village! We have a... business proposal for him, yes! And if we all agree, your village will stay intact.";
			link.l1.go = "merida_guard_2";
		break;
		
		case "merida_guard_2":
            dialog.text = "Are you making threats ladron?";
			link.l1 = "How did figure that out? Ah yes indeed, I am making threats. Either we are getting what we are here for with peace or by force, and you have the honor of deciding the fate of your village.";
			link.l1.go = "merida_guard_3";
		break;
		
		case "merida_guard_3":
            dialog.text = "You will never enter Merida you fucking pirate! Alarm! Enemy at the gates!";
			link.l1 = "Such an unreasonable gentleman...";
			link.l1.go = "merida_guard_4";
		break;
		
		case "merida_guard_4":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "none", "", "", "", 10.0);
			DoQuestFunctionDelay("Mtraxx_MeridaHouseGuards", 5.0);
		break;
		
		// мэр Мериды
		case "merida_head":
            dialog.text = "Damn ladrons! What do you want from us?! This is a small, modest settlement. We have neither gold nor silver! How did you even find out about us?";
			link.l1 = "Oh, don't play innocent and clueless, Your Excellency. The whole world is already filled with rumors about your opals.";
			link.l1.go = "merida_head_1";
		break;
		
		case "merida_head_1":
            dialog.text = "And you caused this godless massacre over... rumors?! Spared no one! Beasts... Let it be known to you: the deposits are far away from here. There's nothing for you to gain here. Leave.";
			link.l1 = "You started this godless massacre. The civilians fought alongside your soldiers. I'll never believe such senseless heroism is possible just to protect a few bare walls.";
			link.l1.go = "merida_head_2";
		break;
		
		case "merida_head_2":
            dialog.text = "Do you know how much effort went into building these walls? We didn't hire outside builders-we built them ourselves, brick by brick. Every single resident. Even I, with these very hands.";
			link.l1 = "So touching story... And what about the furniture? Did you make that yourselves, too? What a fine carved chair. And table. And cabinets. Is this stained oak? Or ebony? A bit too luxurious for a 'modest settlement,' don't you think?";
			link.l1.go = "merida_head_3";
		break;
		
		case "merida_head_3":
            dialog.text = "EGreed has clouded your mind, ladron.";
			link.l1 = "No need to complicate things, Senor Governor. Or you'll regret it.";
			link.l1.go = "merida_head_4";
		break;
		
		case "merida_head_4":
            dialog.text = "Are you going to torture me, you damned pirate? Too bad for you - I believe in God Almighty. And I'll ascend as a martyr if you overdo it.";
			link.l1 = "Hm-m...";
			link.l1.go = "merida_head_5";
		break;

		case "merida_head_5":
			StartInstantDialog("Mrt_Rocur", "merida_head_6", "Quest\Roger.c");
		break;
		
		case "merida_head_6":
            dialog.text = "My friend, he's not going to talk this way. Let me handle it.";
			link.l1 = "Oh?";
			link.l1.go = "merida_head_7";
		break;
		
		case "merida_head_7":
            dialog.text = "I remember everything those puffed-up Spaniards did to me on that cursed plantation. I'd be happy to show you, Prince. And I'll tell you a few stories while I'm at it. You won't get bored.";
			link.l1 = "And what if you get carried away?";
			link.l1.go = "merida_head_8";
		break;
		
	case "merida_head_8":
            dialog.text = "He won't talk nicely. I know his kind.";
			if (IsCharacterPerkOn(pchar, "Trustworthy") && sti(pchar.reputation.nobility) >= 50 && GetSummonSkillFromName(pchar, SKILL_Leadership) >= 50)
			{
				link.l1 = "(Trustworthy) (Honor) (Leadership) That's enough blood for today, Jean. I'll handle this myself.";
				link.l1.go = "merida_head_dobro_1";
				notification("Trustworthy", "Trustworthy");
				notification("Reputation Check Passed", "None");
				notification("Skill Check Passed", SKILL_Leadership);
			}
			else
			{
				if (!IsCharacterPerkOn(pchar, "Trustworthy")) notification("Perk Check Failed", "Trustworthy");
				if (sti(pchar.reputation.nobility) < 50) notification("Reputation Too Low! ("+XI_ConvertString(GetReputationName(50))+")", "None");
				if (GetCharacterSkill(pchar, SKILL_LEADERSHIP) < 50) notification("Skill Check Failed (50)", SKILL_LEADERSHIP);
			}
			link.l2 = "Do it. I'm not getting involved. And I'm not watching, either.";
			link.l2.go = "merida_head_zlo_1";
		break;
		
		case "merida_head_zlo_1":
            dialog.text = "If I weren't in your debt, I'd have a few choice words for you... Damn it. Go on. Now it`s time for the real work.";
			link.l1 = "Don't overexert yourself.";
			link.l1.go = "rocur_42";
		break;
		
		case "merida_head_dobro_1":
            dialog.text = "As you wish, my friend. It'll be fun to watch.";
			link.l1 = "Don't smirk too soon.";
			link.l1.go = "merida_head_dobro_2";
		break;
		
		case "merida_head_dobro_2":
			StartInstantDialog("Merida_Head", "merida_head_dobro_3", "Quest\Roger.c");
		break;
		
		case "merida_head_dobro_3":
            dialog.text = "You say you'll handle this yourself, without bloodshed, you damned ladron? There's nothing you can say to make stones appear out of thin air!";
			link.l1 = "etter they appear, Governor. Otherwise, we'll raze the city to the ground and kill everyone but you. I dislike this solution, but I'm willing to compromise my honor for my cause. Your duty, on the other hand, is to protect the civilians, surviving soldiers, and workers of Merida. Or would you prefer to 'ascend as a martyr' at the cost of their suffering? That doesn't sound very godly to me.";
			link.l1.go = "merida_head_dobro_4";
		break;
		
		case "merida_head_dobro_4":
            dialog.text = "Damn you...\nThere... in the chest. Just spare the townsfolk!";
			if (GetSummonSkillFromName(pchar, SKILL_Sneak) >= 50)
			{
				link.l1 = "(Sneak) Is everything in the chest?";
				link.l1.go = "merida_head_dobro_vnimatelnost_1";
				notification("Skill Check Passed", SKILL_Sneak);
			}
			else
			{
				link.l1 = "I keep my word. Farewell, Governor.";
				link.l1.go = "merida_head_dobro_5";
				notification("Skill Check Failed (50)", SKILL_SNEAK);
			}
		break;
		
		case "merida_head_dobro_vnimatelnost_1":
            dialog.text = "Damn you to hell!\nThe chest has a false bottom also. Take everything!!";
			link.l1 = "...";
			link.l1.go = "merida_head_dobro_vnimatelnost_2";
			pchar.questTemp.Mtraxx_MeridaKamushki = true;
		break;
		
		case "merida_head_dobro_vnimatelnost_2":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto2", "Mtraxx_MeridaOpenChest", -1);
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
		break;
		
		case "merida_head_dobro_vnimatelnost_3":
            dialog.text = "Smooth, Prince. Sorry for underestimating you.";
			link.l1 = "Satisfied?";
			link.l1.go = "merida_head_dobro_7";
		break;
		
		case "merida_head_dobro_5":
			StartInstantDialog("Mrt_Rocur", "merida_head_dobro_6", "Quest\Roger.c");
		break;
		
		case "merida_head_dobro_6":
            dialog.text = "Smooth, Prince.";
			link.l1 = "Satisfied?";
			link.l1.go = "merida_head_dobro_7";
		break;
		
		case "merida_head_dobro_7":
            dialog.text = "More than. But... you'll see for yourself. You go ahead; I'll dig around a little more.";
			link.l1 = "...";
			link.l1.go = "rocur_43";
		break;
		
		/*case "merida_head_99999":
            DialogExit();
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto2", "Mtraxx_MeridaGiveJewelry", -1);
		break;*/
		
		case "merida_head_sleep":
            dialog.text = "You promised to leave the town once you have the gems... You have them now and your ladrones had set our houses on fire! You are a liar and a wicked pirate! I hope the flames of hell will be this hot for you!!!";
			link.l1 = "";
			link.l1.go = "exit";
			locCameraFromToPos(19.18, 1.28, -0.28, true, 24.88, 1.62, -1.19);
			AddDialogExitQuest("Mtraxx_RetributionSleep2");
		break;
		
		// капитан пинаса Китти
		case "kittycap":
            dialog.text = TimeGreeting()+", kind sir. What's your purpose here?";
			link.l1 = "I am from Tyrex. I was told to escort your vessel to Bridgetown. Are you ready?";
			link.l1.go = "kittycap_1";
		break;
		
		case "kittycap_1":
            dialog.text = "Well, finally! Yes, my crew is ready to set sail immediately!";
			link.l1 = "Splendid. Ready the sails captain. Get us underway!";
			link.l1.go = "kittycap_2";
		break;
		
		case "kittycap_2":
		    DialogExit();
            LAi_CharacterDisableDialog(npchar);
			Group_DelCharacter("Mtr_Kitty", "Mtr_KittyCap");
			SetCharacterRemovable(npchar, false);
			npchar.CompanionEnemyEnable = false; //всегда друзья
			LAi_SetImmortal(npchar, false);
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.loyality = MAX_LOYALITY;
		    pchar.quest.mtraxx_ignasio_sail.win_condition.l1 = "location";
			pchar.quest.mtraxx_ignasio_sail.win_condition.l1.location = "Bridgetown_town";
			pchar.quest.mtraxx_ignasio_sail.function = "Mtraxx_IgnasioArrive";
			SetFunctionTimerCondition("Mtraxx_IgnasioTimeOver", 0, 0, 30, false);
			pchar.quest.mtraxx_ignasio_sinkkitty.win_condition.l1 = "NPC_Death";
			pchar.quest.mtraxx_ignasio_sinkkitty.win_condition.l1.character = "Mtr_KittyCap";
			pchar.quest.mtraxx_ignasio_sinkkitty.function = "Mtraxx_IgnasioKittySink";
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		break;
		
		case "kittycap_3":
            dialog.text = "Thank you for helping me, captain! With you on my side I was as safe as if I was behind the fort's walls.";
			link.l1 = "Hah, don't mention it pal! Everything is on Marcus. Good luck to you mate!";
			link.l1.go = "kittycap_4";
		break;
		
		case "kittycap_4":
            DialogExit();
			npchar.lifeday = 0;
			RemoveCharacterCompanion(pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 30.0);
			Mtraxx_IgnasioCreateMarko();
			AddCharacterExpToSkill(pchar, "Sailing", 200);
		break;
		
		// Игнасио Марко
		case "ignasio":
            PlaySound("Voice\English\LE\Ignasio_Marko\Ignasio_01.wav");
			dialog.text = "Greetings to the brave captain! Let me introduce myself - a privateer of England, Ignacio Marco of the Torero.";
			link.l1 = TimeGreeting()+", friend. Captain "+GetFullName(pchar)+" at your service. How can I help you?";
			link.l1.go = "ignasio_1";
		break;
		
		case "ignasio_1":
            PlaySound("Voice\English\LE\Ignasio_Marko\Ignasio_02.wav");
			dialog.text = "Oh, I know you! Monseniour "+GetFullName(pchar)+"! Rumors of your resources and patrons had been reaching me throughout the Archipelago. I believe my offer will be quite interesting for you.";
			link.l1 = "What offer?";
			link.l1.go = "ignasio_2";
		break;
		
		case "ignasio_2":
            dialog.text = "Let's go to a tavern for a drink. I will tell you everything. It's not a street talk.";
			link.l1 = "Very well... Let's go!";
			link.l1.go = "ignasio_3";
		break;
		
		case "ignasio_3":
            DialogExit();
			FreeSitLocator("Bridgetown_tavern", "sit_front2");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "Bridgetown_tavern", "sit", "sit_front2", "Mtraxx_IgnasioInTavern", -1);
		break;
		
		case "ignasio_4":
			LAi_SetSitType(pchar);
            dialog.text = "A round, captain?";
			link.l1 = "Sure!";
			link.l1.go = "ignasio_5";
		break;
		
		case "ignasio_5":
			LAi_Fade("", "");
            dialog.text = "Heh, they actually don't mix rum with water here...";
			link.l1 = "And don't treat customers with rotten fish, yes-yes. So what's the deal?";
			link.l1.go = "ignasio_6";
		break;
		
		case "ignasio_6":
            dialog.text = "I like your straightforwardness, monsieur. Tell me, are you aware of the trade war between the English and the Dutch?";
			link.l1 = "I am. Had a pleasure to take a part in it.";
			link.l1.go = "ignasio_7";
		break;
		
		case "ignasio_7":
            PlaySound("Voice\English\LE\Ignasio_Marko\Ignasio_02.wav");
			dialog.text = "No need to explain it then. Being an English privateer I am fighting this war on their side. You are a freelancer mostly. Which makes you indifferent in what side to fight against...";
			link.l1 = "Almost. I don't cross France, I am sorry.";
			link.l1.go = "ignasio_8";
		break;
		
		case "ignasio_8":
            dialog.text = "By all means, captain! So, straight to the point: there is a small inhabited island between Curacao and Trinidad, it's not on the maps... Since recent times, I'd say very recent times, the Dutch have started to use it as a temporary stop to resupply and repair. It seems that they believe that only they are aware of this island. Wrong. He-he\nCouple of days ago a silver caravan was hit by a... storm, and now the Dutch are repairing their vessels on this island. The flagship lost her mast, so it will take some time to repair it. The Dutch are busy with repairing, and the crews are mostly dispersed across the island...";
			link.l1 = "And then suddenly we show up to save the day?";
			link.l1.go = "ignasio_9";
		break;
		
		case "ignasio_9":
            dialog.text = "Exactly, captain. I can't do this alone but with you - it's a totally different story. Will you risk it? I have a great ship, the crew is great and I have a good amount of experience. Your skills... are commendable as well.";
			link.l1 = "How much time do we have?";
			link.l1.go = "ignasio_10";
		break;
		
		case "ignasio_10":
            dialog.text = "Plenty if we are not wasting it and getting underway immediately.";
			link.l1 = "Then let's resupply with munitions and weapons, captain Ignacio Marco, and let's set sails. What are the island's exact coordinates?";
			link.l1.go = "ignasio_11";
		break;
		
		case "ignasio_11":
            dialog.text = "12'40 North, 64'11 West. Got it?";
			if (CheckAttribute(pchar, "questTemp.HWIC.Isladecoche")) link.l1 = "Ha! Deja vu... Got it.";
			else link.l1 = "Got it.";
			link.l1.go = "ignasio_12";
		break;
		
		case "ignasio_12":
            dialog.text = "Heading to the 'Torero'. Will be waiting for you, captain!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioAddMarko");
		break;
		
		case "ignasio_13":
            PlaySound("Voice\English\LE\Ignasio_Marko\Ignasio_03.wav");
			dialog.text = "Hell of a fight right, captain? Now the pleasant part: let's split our shares. A half goes to me and my men.";
			link.l1 = "Very well, let's do it...";
			link.l1.go = "ignasio_14";
		break;
		
		case "ignasio_14":
			LAi_Fade("", "");
			WaitDate("", 0, 0, 0, 3, 10); 
			pchar.questTemp.Mtraxx.Silver = GetSquadronGoods(pchar, GOOD_SILVER)-sti(pchar.questTemp.Mtraxx.Silver);
			pchar.questTemp.Mtraxx.Mahogany = GetSquadronGoods(pchar, GOOD_MAHOGANY)-sti(pchar.questTemp.Mtraxx.Mahogany);
			if (sti(pchar.questTemp.Mtraxx.Silver) < 100)
			{
				dialog.text = "Captain, what is it? Where is our silver? Did you sink our prize?";
				if (sti(pchar.questTemp.Mtraxx.Mahogany) < 200) 
				{
					link.l1 = "Hm...";
					link.l1.go = "ignasio_15_1";
				}
				else
				{
					link.l1 = "Silver was wasted somehow although we got some redwood. Let's split it.";
					link.l1.go = "ignasio_15_11";
				}
				break;
			}
			if (sti(pchar.questTemp.Mtraxx.Silver) < 300 && sti(pchar.questTemp.Mtraxx.Silver) > 100)
			{
				dialog.text = "Hm.. This is poor. I thought there'd be much more.";
				link.l1 = "We've got what we've got.";
				link.l1.go = "ignasio_15_2";
				break;
			}
			if (sti(pchar.questTemp.Mtraxx.Silver) < 700 && sti(pchar.questTemp.Mtraxx.Silver) > 300)
			{
				dialog.text = "Not bad, not bad. Although, I thought there'd be more.";
				link.l1 = "We've got what we've got.";
				link.l1.go = "ignasio_15_3";
				break;
			}
            dialog.text = "Nicely done, Monseniour. This is a fine prize...";
			link.l1 = "Can't disagree with you on this, captain.";
			link.l1.go = "ignasio_15_4";
		break;
		
		case "ignasio_15_1":
			dialog.text = "Looks like you have a serious trouble with your head. We are leaving! Boys!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_15_11":
			RemoveCharacterGoods(pchar, GOOD_MAHOGANY, makeint(sti(pchar.questTemp.Mtraxx.Mahogany)/2));
			dialog.text = "At least we get something from this... Boys! Let's go!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_15_2":
			RemoveCharacterGoods(pchar, GOOD_SILVER, makeint(sti(pchar.questTemp.Mtraxx.Silver)/2));
			RemoveCharacterGoods(pchar, GOOD_MAHOGANY, makeint(sti(pchar.questTemp.Mtraxx.Mahogany)/2));
            dialog.text = "It's something. Let's part our ways.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_15_3":
            RemoveCharacterGoods(pchar, GOOD_SILVER, makeint(sti(pchar.questTemp.Mtraxx.Silver)/2));
			RemoveCharacterGoods(pchar, GOOD_MAHOGANY, makeint(sti(pchar.questTemp.Mtraxx.Mahogany)/2));
            dialog.text = "It's something. Let's part our ways. It's a success after all, heh!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_15_4":
			RemoveCharacterGoods(pchar, GOOD_SILVER, makeint(sti(pchar.questTemp.Mtraxx.Silver)/2));
			RemoveCharacterGoods(pchar, GOOD_MAHOGANY, makeint(sti(pchar.questTemp.Mtraxx.Mahogany)/2));
            dialog.text = "We had a very profitable meeting. Perhaps, it's not the last time we do business together, captain!";
			link.l1 = "Call me if you find more fat traders, he-he!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_boarding":
			PlaySound("Voice\English\LE\Ignasio_Marko\Ignasio_04.wav");
            dialog.text = "I assume this is not an accident, captain?";
			link.l1 = "You wouldn't be smart if you didn't see it. You owe me for the setup. You know what I am talking about. Also, you owe me for setting up my friend Jean Picard. He was sold to plantation after your scheme... You lost Ignacio. I am going to hang you but you can ease your punishment...";
			link.l1.go = "ignasio_boarding_1";
		break;
		
		case "ignasio_boarding_1":
            dialog.text = "I am wondering even - what is it I could do to make you pity me?";
			link.l1 = "I need information. I will put you into my cargo hold where we will talk about your agenda in Havana...";
			link.l1.go = "ignasio_boarding_2";
		break;
		
		case "ignasio_boarding_2":
            dialog.text = RandSwear()+" I didn't see this coming! Don't even think of it. Barbazon will learn about my treason in no time. You better don't know what he does to people who betrayed him. I saw it.";
			link.l1 = "So being hanged is a better option?";
			link.l1.go = "ignasio_boarding_3";
		break;
		
		case "ignasio_boarding_3":
            dialog.text = "I'd rather die in combat!";
			link.l1 = "...";
			link.l1.go = "ignasio_boarding_4";
		break;
		
		case "ignasio_boarding_4":
            DialogExit();
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "spy_sailor":
            dialog.text = "Captain! Captain! Hurry! The Spanish military squadron is after us!";
			link.l1 = RandSwear()+"I expected this... Same story happened to Picard. Did you see how many of them were out there?";
			link.l1.go = "spy_sailor_1";
		break;
		
		case "spy_sailor_1":
            dialog.text = "Yes, captain. Three ships. Their flagship is a galleon the largest one I have ever seen and it's moving fast, the other two are a corvette and a xebec.";
			link.l1 = "All aboard. We might still be in position to flee.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioOurEscape");
		break;
		
		// индей-кариб в гроте Порто-Белло
		case "grot_canib":
            dialog.text = "Haya! Damn yalanaui come our forest! Kill him! Haya!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekGrotFight");
		break;
		
		// бандит у пещеры Панамы
		case "cave_bandit":
            dialog.text = "Hey! What the hell are you doing here? A-ah, stealing others' belongings? Well, you are screwed!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekCaveFight");
		break;
		
		case "carpenter":
            dialog.text = "Hey! Everyone hold right there! Or I will take you all with a grapeshot volley! "+RandSwear()+"";
			link.l1 = "We are not moving anywhere right now. But listen pal - there is no way that you'll kill all of us in one shot. Some of us will cut you to pieces while you are reloading. We'd better have a talk right now.";
			link.l1.go = "carpenter_1";
			locCameraFromToPos(-71.57, 14.57, -130.20, true, -63.78, 11.36, -125.50);
		break;
		
		case "carpenter_1":
            dialog.text = "Are you in charge here? Answer me!";
			link.l1 = "I am captain "+GetFullName(pchar)+". And you must be Red Wolf's second in command while he is away from here, am I right?";
			link.l1.go = "carpenter_2";
		break;
		
		case "carpenter_2":
            dialog.text = "What are you doing here captain "+GetFullName(pchar)+"? We don't invite guests to this place!";
			link.l1 = "What's your name? I want to know who am I talking to.";
			link.l1.go = "carpenter_3";
		break;
		
		case "carpenter_3":
            dialog.text = "Name's Rodgar Janssen.";
			link.l1 = "I can see that you fellas are in dark here. You don't have a captain any more. And your corvette is gone too. The 'Freyja' was bombed the hell out by the Spanish not far from Hispaniola. Her crew was slain to the last...";
			link.l1.go = "carpenter_4";
		break;
		
		case "carpenter_4":
            dialog.text = RandSwear()+" Wulfric... Aahhh-ghhhhh!!! ... But how can I know your are telling the truth?";
			link.l1 = "I have your ex-captain's log! We've got a few items from Freyja's wreckage. Thanks to the log I have found this island and this... gordes of yours.";
			link.l1.go = "carpenter_5";
		break;
		
		case "carpenter_5":
            dialog.text = "Heh! You still owe me an answer: why are you here on this unknown land?";
			link.l1 = "I'm not gonna lie, pal. They say Red Wolf possessed quite a fortune. I am here to find it since no such treasure was found on his ship. I believe they should belong to the good people, they have no use to Wulfric now anyway.";
			link.l1.go = "carpenter_6";
		break;
		
		case "carpenter_6":
            dialog.text = "Ha! Mate, I am going to disappoint you: neither me nor anyone else of the crew ever saw Wolf's treasures. It was too risky to ask him.";
			link.l1 = "Then I should probably search for them in your village. Will you take away your gun or should I start storming the village? You have no chance Rodgar. I will bring guns and more men if I need.";
			link.l1.go = "carpenter_7";
		break;
		
		case "carpenter_7":
            dialog.text = "Before we die we will take along a plenty of you bastards to hell! Maybe you too!";
			link.l1 = "Are you sure? You have no captain, no ship and no one will come to save you. Even if I just leave, you all will starve to death soon enough!";
			link.l1.go = "carpenter_8";
		break;
		
		case "carpenter_8":
            dialog.text = "Hmm... got any suggestions?";
			link.l1 = "Yes, I do. Take a step back from the gun and keep your men in check. I swear I will not do any harm to you or your men. If you want you can join my crew or we will take you to some civilization.";
			link.l1.go = "carpenter_9";
		break;
		
		case "carpenter_9":
            dialog.text = "Swear it before your men loud and clear!";
			link.l1 = "I swear! You have my word: you and your men will not be harmed.";
			link.l1.go = "carpenter_10";
		break;
		
		case "carpenter_10":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_11";
			LAi_SetActorType(npchar);
			LAi_ActorDialog(npchar, pchar, "", -1, 0);
			for (i=1; i<=2; i++) // 
			{
				sld = CharacterFromID("Islamona_fort_pirate_"+i);
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
		break;
		
		case "carpenter_11":
            dialog.text = "I hope you will keep your word, captain.";
			link.l1 = "I always do. How many of you are left?";
			link.l1.go = "carpenter_12";
		break;
		
		case "carpenter_12":
            dialog.text = "You see us all. Three. The rest died in the jungles attacking you. I told them not to but they didn't listen...";
			link.l1 = "I see...";
			link.l1.go = "carpenter_13";
		break;
		
		case "carpenter_13":
            dialog.text = "Food was running out. We started hunting parrots. The 'Freyja' was absent for too long. We had our suspicions and they came true.";
			link.l1 = "Thank God for me deciding to go treasure hunting. Where do you think he stashed them?";
			link.l1.go = "carpenter_14";
		break;
		
		case "carpenter_14":
            dialog.text = "I told you already: no one has ever seen them. Wulfric was careful with his share, never let it go to waste. He was fair with us but everyone who tried to find his stash had gone missing. You are free to search the village if you wish.";
			link.l1 = "That's my plan. Where is Red Wolf's house?";
			link.l1.go = "carpenter_15";
		break;
		
		case "carpenter_15":
            dialog.text = "The only double-floored building we have here.";
			link.l1 = "Good. By the way, what's your occupation?";
			link.l1.go = "carpenter_16";
		break;
		
		case "carpenter_16":
			worldMap.labels.islamona.icon = 5;
			worldMap.labels.islamona.text = CheckingTranslate(LanguageOpenFile("LocLables.txt"),"Islamona");
            dialog.text = "I am a carpenter and these two are my assistances. We used to repair and crook the 'Freyja' before. We could be of use in your crew.";
			link.l1 = "I see. Very well, you are in, we'll talk details later. Get this gun from the entrance. And Rodgar don't leave the village while I am searching for the stash.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekInFort");
		break;
		
		case "carpenter_17":
            dialog.text = "Orders, captain?";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.WolfreekGord"))
			{
				link.l1 = "Yes. Your captain's treasures have been found. He did hide them well but I have outsmarted him!";
				link.l1.go = "carpenter_18";
				break;
			}
			// Jason Исла Мона -->
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "start")
			{
				link.l1 = "Rodgar, what do you think, is there anything else we can do with this base?";
				link.l1.go = "IslaMona";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "get_tools")
			{
				link.l1 = "Rodgar, I brought the tools. They should have already been delivered to you.";
				link.l1.go = "IslaMona_8";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "himenes")
			{
				link.l1 = "Welcome! This is Rodrigo Jimenez, the leader of a small but very hardworking community from Cadiz. Senor Jimenez kindly agreed to temporarily settle in our land and help us with construction.";
				link.l1.go = "IslaMona_12";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "nextday")
			{
				link.l1 = "Rodgar, how are you? Do you have any good advice for me?";
				link.l1.go = "IslaMona_18";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "stalk")
			{
				link.l1 = "Rodgar, I need a favor.";
				link.l1.go = "IslaMona_20";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "dublon_wait" && GetCharacterItem(pchar, "gold_dublon") >=600)
			{
				link.l1 = "I brought the doubloons for you, just dont waste it all on booze right away.";
				link.l1.go = "IslaMona_24";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "storage" && !CheckAttribute(pchar, "questTemp.IslaMona.Food") && IslaMona_CheckFood())
			{
				link.l1 = "Rodgar, check the warehouse. I brought the medicine and provisions.";
				link.l1.go = "IslaMona_30";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "village")
			{
				link.l1 = "Hello, Rodgar, how are things in the new settlement?";
				link.l1.go = "IslaMona_32";
				break;
			}
			if (!CheckAttribute(npchar, "quest.stalk")) // ремонт кораблей
			{
				link.l2 = "Rodgar, my ship needs repairs. Are you and your guys ready?";
				link.l2.go = "repair";
			}
			link.l3 = "Rodgar, I'd like to leave one of my ships here.";
			if (CheckAttribute(npchar, "portman.info")) link.l3.go = "shipstock";
			else link.l3.go = "shipstock_info";
			if (CheckAttribute(npchar, "portman") && sti(npchar.portman > 0))
			{
				link.l4 = "Rodgar, I'd like to take one of my ships back.";
				link.l4.go = "shipstockreturn";
			}
			if (!CheckAttribute(npchar, "storadge"))
			{
				link.l5 = "Look, is there any empty building I could use as a storehouse?";
				link.l5.go = "storadge";
			}
			if (CheckAttribute(npchar, "storadge"))
			{
				link.l5 = "Rodgar, I want to see a storehouse.";
				link.l5.go = "storadge_3";
			}
			if (CheckAttribute(npchar, "crew"))
			{
				link.l6 = "Rodgar, I want to leave a part of the team on the island.";
				link.l6.go = "crew";
			}
			if (CheckAttribute(npchar, "crew") && sti(npchar.crew.qty) > 0)
			{
				link.l7 = "Rodgar, I want to take my sailors with me back out to the sea.";
				link.l7.go = "crew_3";
			}// <-- Исла Мона
			link.l99 = "Nothing yet...";
			link.l99.go = "carpenter_exit";
		break;
		
		case "Crew":
			DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			LaunchHireCrew();
		break;
		
		case "carpenter_exit":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
		break;
		
		case "carpenter_18":
            dialog.text = "Congratulations cap. What do we do next? Are we leaving?";
			link.l1 = "Have you been here for long?";
			link.l1.go = "carpenter_19";
		break;
		
		case "carpenter_19":
            dialog.text = "For far too long. It's been a year since Wulfric put me in charge here.";
			link.l1 = "I have decided that this secret base is too good to be wasted. The village is mine now. I can leave you and your men here if you want. Rum, provisions, medicine - all yours.";
			link.l1.go = "carpenter_20";
		break;
		
		case "carpenter_20":
            dialog.text = "That would be great captain. I got used to the life on this beach, this island.";
			link.l1 = "Splendid. By the way, what's the island's name?";
			link.l1.go = "carpenter_21";
		break;
		
		case "carpenter_21":
            dialog.text = "Isla Mona.";
			link.l1 = "Isla Mona... Perhaps one day we will build more houses and structures here... But later. Right now you will keep the same role here but under a new captain.";
			link.l1.go = "carpenter_22";
		break;
		
		case "carpenter_22":
            dialog.text = "Deal. You just take care of yourself captain and don't forget supplying us with provisions.";
			link.l1 = "Sure thing Rodgar. Good luck, I should sail to La Vega.";
			link.l1.go = "carpenter_exit";
			npchar.portman = 0;
			AddDialogExitQuestFunction("Mtraxx_WolfreekComplete");
		break;
		//------------------------------------------------------------ Исла Мона ------------------------------------
		case "IslaMona":
			sTemp = "";
			if (GetCharacterIndex("Mirabella") != -1) sTemp = ", not accounting for your woman";
            dialog.text = "It's hard to say, Cap. The late Wulfric never left more than two dozen people here. Right now, there are only three of us,"+sTemp+". There's not a lot we can do.";
			link.l1 = "Do you mean to say that if more people lived here, you could turn this place into a full-fledged settlement?";
			link.l1.go = "IslaMona_1";
		break;
		
		case "IslaMona_1":
            dialog.text = "The island is small, so you can't build a colony on it, but a settlement is entirely possible! You can fish, hunt birds and goats, gather fruits. We can sustain ourselves, but we won't get rich off of it.\nBut there's one thing I don't quite understand, Cap. Why do you need this?";
			link.l1 = "This is my home and my land, my people. What does it make me if I don't take care of them?";
			link.l1.go = "IslaMona_2_1";
			link.l2 = "I want to invest money into a worthwhile business.";
			link.l2.go = "IslaMona_2_2";
			link.l3 = "This little island is right in the heart of this region. It would be wise to turn it into a full-fledged and secret military base.";
			link.l3.go = "IslaMona_2_3";
			link.l4 = "I'm worried about you, Rodgar, the lot of you have gone completely wild at this point.";
			link.l4.go = "IslaMona_2_4";
		break;
		
		case "IslaMona_2_1":
            dialog.text = "You're a strange one. Well, never mind. At least there will be something to do...";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
			AddCharacterExpToSkill(pchar, "Defence", 2000);//защита
		break;
		
		case "IslaMona_2_2":
            dialog.text = "You're a strange one. Well, never mind. At least there will be something to do...";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
			AddCharacterExpToSkill(pchar, "Commerce", 1500);//торговля
		break;
		
		case "IslaMona_2_3":
            dialog.text = "You're a strange one. Well, never mind. At least there will be something to do...";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
			AddComplexSelfExpToScill(250, 250, 250, 250);//оружие
		break;
		
		case "IslaMona_2_4":
            dialog.text = "You're a strange one. Well, never mind. At least there will be something to do...";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
			AddCharacterExpToSkill(pchar, "Leadership", 1000);//авторитет
		break;
		
		case "IslaMona_3":
            dialog.text = "First of all, you'll have to find very special individuals. Those who could be persuaded to move to this wilderness to live and work in it for years, in complete isolation from the outside world. That's the kind of special people you'll have to look for. Hopefully, not just one. After all, you can't order your crew to live here, at least not yet. Colonists wouldn't want to leave their established homes and stable jobs. And we don't need drifters and other misfits here ourselves.\nMoreover, the issue of secrecy surrounding this island will always be present. If you tell someone, there will immediately be the threat of hunters looking to investigate.";
			link.l1 = "I understand, any suggestions?";
			link.l1.go = "IslaMona_4";
		break;
		
		case "IslaMona_4":
            dialog.text = "No, Captain. I've been here for far too long and have completely fallen out of touch with civilized life.";
			link.l1 = "Great, thats helpful!";
			link.l1.go = "IslaMona_5";
		break;
		
		case "IslaMona_5":
            dialog.text = "I work with wood, not with people. And I'm very happy about that, ha-ha! By the way, besides people, you will also need to bring a set of high-quality forging and construction tools here. They are only made in old Europe, so they will cost you a pretty penny. Ask the owners of the shipyards, the bigger ones.";
			link.l1 = "Everything is clear. Let's summarize: if I want to turn this base into something bigger, I need to bring back here more settlers and tools?";
			link.l1.go = "IslaMona_6";
		break;
		
		case "IslaMona_6":
            dialog.text = "That is correct!";
			link.l1 = "I'll see what I can do.";
			link.l1.go = "IslaMona_7";
		break;
		
		case "IslaMona_7":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			AddQuestRecord("IslaMona", "1");
			pchar.questTemp.IslaMona = "tools";
			IslaMona_SelectShipyard();
		break;
		
		case "IslaMona_8":
            dialog.text = "Aye, Captain! Top-notch set, we are ready to build a colony! Was it pricey?";
			link.l1 = "Cost me a fortune, I sure hope it was worth it!";
			link.l1.go = "IslaMona_9_1";
			link.l2 = "A couple of years ago, I would have said it was very expensive. But now... I don't even know.";
			link.l2.go = "IslaMona_9_2";
		break;
		
		case "IslaMona_9_1":
			AddCharacterExpToSkill(pchar, "Commerce", 600);
            dialog.text = "You couldn't settle for what you already had, could you? In any case, be prepared for your expenses to only grow. Have you sorted out the issue with the settlers?";
			link.l1 = "No, Rodgar. I haven't figured out where to find them yet. After all, I don't have the sovereign rights to establish settlements in these waters.";
			link.l1.go = "IslaMona_10";
		break;
		
		case "IslaMona_9_2":
			AddCharacterExpToSkill(pchar, "Leadership", 300);
            dialog.text = "You couldn't settle for what you already had, could you? In any case, be prepared for your expenses to only grow. Have you sorted out the issue with the settlers?";
			link.l1 = "No, Rodgar. I haven't figured out where to find them yet. After all, I don't have the sovereign rights to establish settlements in these waters.";
			link.l1.go = "IslaMona_10";
		break;
		
		case "IslaMona_10":
            dialog.text = "In these waters, Captain, chaos reigns every day. Listen to what people are saying, you might just see a hidden opportunity. I'll take care of the tools for now.";
			link.l1 = "Alright, I'll be on a lookout for that sort of information.";
			link.l1.go = "IslaMona_11";
		break;
		
		case "IslaMona_11":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			AddQuestRecord("IslaMona", "3");
			RemoveItems(pchar, "islamona_toolbox", 1);
			pchar.questTemp.IslaMona = "rumours";
			AddRumor("They say some criminals have been cast out to one of the uninhabited islands! It seems they're such fierce monsters that even the executioner and the holy fathers wouldn't want to deal with them! But why do they always bring such people to us?!", 1, "all", "none", 0, (2022 - STARTGAME_YEAR) * 365, "IslaMona_TerksRumour", "none");
		break;
		
		case "IslaMona_12":
            dialog.text = "Spaniards? You've got to be kidding, Captain. I thought you'd bring idlers from Le Francois, not these...";
			link.l1 = "";
			link.l1.go = "IslaMona_13";
		break;
		
		case "IslaMona_13":
            DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_18";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "IslaMona_14":
            dialog.text = "Are you from Europe? Hehe, its not hard to tell. No worries, you'll get used to it.";
			link.l1 = "Jimenez, you'll stay at my house for a while. There's a basement there, plenty of space. Rodgar, I brought the tools, and the settlers too. What's next?";
			link.l1.go = "IslaMona_15";
		break;
		
		case "IslaMona_15":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_20";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "IslaMona_16":
            dialog.text = "See you tomorrow, Captain. We'll talk in a day, once these... settlers settle in with their treasures..";
			link.l1 = "Alright, we'll continue tomorrow.";
			link.l1.go = "IslaMona_17";
		break;
		
		case "IslaMona_17":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			LAi_SetWarriorType(npchar);
			IslaMona_HimenesWait();
		break;
		
		case "IslaMona_18":
            dialog.text = "Captain, talk to the Spaniard. He's already fully engaged in his work.";
			link.l1 = "Got it, will do.";
			link.l1.go = "IslaMona_19";
			link.l2 = "Is something wrong?";
			link.l2.go = "IslaMona_18_1";
		break;
		
		case "IslaMona_18_1":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
            dialog.text = "Captain, I've been idling with the guys here for a few years. Now, the bustling activity of the Spaniards is getting on my nerves.";
			link.l1 = "No conflicts! And I forbid you and your guys even to look in the direction of their women! At least, for now... If things get heated, take a skiff and go... fishing for a couple of days.";
			link.l1.go = "IslaMona_18_2";
		break;
		
		case "IslaMona_18_2":
            dialog.text = "Aye, aye, sir!";
			link.l1 = "Perfect. Alright, I'll go see what he is up to.";
			link.l1.go = "IslaMona_19";
		break;
		
		case "IslaMona_19":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			IslaMona_SetHimenesNextDay();
		break;
		
		case "IslaMona_20":
            dialog.text = "I already know, Captain. Spaniard wants us to explore the island? Jump around on the rocks with a map like a bunch of idiots?";
			link.l1 = "That is correct, Rodgar.";
			link.l1.go = "IslaMona_21";
		break;
		
		case "IslaMona_21":
            dialog.text = "Six hundred doubloons and I'll do it.";
			link.l1 = "Are you crazy? Did you get bit by a local spider or a venomous snake? What are you going to do with a chest of gold on an uninhabited island? Bury it?";
			link.l1.go = "IslaMona_22";
		break;
		
		case "IslaMona_22":
            dialog.text = "Come on, Captain. One day we'll leave this place, and who will need us in the big world without coin? Of course, we've got a small stash hidden away, but it's not nearly enough. Wulfric never settled his debts with me and the lads for his last ventures.\nIt's one thing to laze around on the beach for months and service your fleet once every six months. But to work hard on solid ground every day, like a cursed buccaneer - that's a whole different story! That's a job, and jobs pay. You do pay your crew, don't you, Captain?";
			link.l1 = "Sounds reasonable. I'll get you the 600 doubloons. I hope you don't expect the payment in advance, right?";
			link.l1.go = "IslaMona_23";
			link.l2 = "I have another proposal. You work on the land, not scraping barnacles off ships at sea. Right now, we're in dire need of that kind of work.";
			link.l2.go = "IslaMona_25";
		break;
		
		case "IslaMona_23":
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			AddCharacterExpToSkill(pchar, "Leadership", 500);
			AddQuestRecord("IslaMona", "7");
            dialog.text = "Captain, I'm ready to start right now, but my men will work much harder when they see doubloons in their hands. I promise we won't leave a single patch of unexplored land on this island.";
			if (PCharDublonsTotal() >= 600)
			{
				link.l1 = "Alright. Here's your gold. Just don't waste it on drinks right away.";
				link.l1.go = "IslaMona_24";
			}
			else
			{
				link.l1 = "Fine, I will bring you your doubloons.";
				link.l1.go = "IslaMona_24_1";
			}
		break;
		
		case "IslaMona_24_1":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			pchar.questTemp.IslaMona = "dublon_wait";
		break;
		
		case "IslaMona_24":
			RemoveDublonsFromPCharTotal(600);
			Log_Info("You gave away 600 doubloons");
			PlaySound("interface\important_item.wav");
            dialog.text = "Ha-ha! You've got a point there, Captain! Oh, and I almost forgot. Now there are quite a few people living here, and they need something to eat. Have you seen those ladies? They're not accustomed to survival and feeding off the land. They won't be of any help.";
			link.l1 = "Just don't tell me I'll have to find more buccaneers to help you out.";
			link.l1.go = "IslaMona_26";
		break;
		
		case "IslaMona_25":
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			ChangeCharacterComplexReputation(pchar, "authority", 5);
			pchar.questTemp.IslaMona.Nodublon = "true"; // дублоны не заплатил
			AddQuestRecord("IslaMona", "8");
            dialog.text = "Aye-aye, Captain! We're ready to work on the land! Oh, and one more thing, I almost forgot. Now there are quite a few people living here, and they need something to eat. Have you seen those ladies? They're not accustomed to survival and feeding off the land. They won't be of any help.";
			link.l1 = "Don’t tell me I’ll have to go look for buccaneers to help you too...";
			link.l1.go = "IslaMona_26";
		break;
		
		case "IslaMona_26":
            dialog.text = "No, why would we? We will train and prepare the most capable among them for livelihood. But until that wonderful moment arrives, you'll have to provide us with food. A couple thousand sets of ship's provisions will suffice. And a centner of medicines for the future. Unload all of this from the ships into our warehouse on the island.";
			link.l1 = "Will do. How much time do you need for the scouting mission?";
			link.l1.go = "IslaMona_27";
		break;
		
		case "IslaMona_27":
            dialog.text = "We will wrap up in two to three days, we've already found some interesting things.";
			link.l1 = "Great!";
			link.l1.go = "IslaMona_28";
		break;
		
		case "IslaMona_28":
            dialog.text = "As soon as we finish, head straight to that laughing Spaniard. The crazy one needs to draw conclusions from our work.";
			link.l1 = "I see you're almost friends already. I'll visit him in three days then. Well, here's to the work. Good luck to all of us!";
			link.l1.go = "IslaMona_29";
		break;
		
		case "IslaMona_29":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			npchar.quest.stalk = "true";
			AddQuestRecord("IslaMona", "9");
			pchar.questTemp.IslaMona = "storage";
			SetFunctionTimerCondition("IslaMona_StalkFin", 0, 0, 3, false);
		break;
		
		case "IslaMona_30":
            dialog.text = "Wow! Thanks, Captain. Now we have time to prepare the ladies for this crazy life in the wild.";
			link.l1 = "Just be careful not to make pirates out of them! Thank you, Rodgar";
			link.l1.go = "IslaMona_31";
		break;
		
		case "IslaMona_31":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			pchar.questTemp.IslaMona.Food = "true";
			AddQuestRecord("IslaMona", "10");
			IslaMona_RemoveFood();
		break;
		
		case "IslaMona_32":
            dialog.text = "Captain! I must say, I've started feeling rather uncomfortable living here.";
			link.l1 = "Why is that, Rodgar? Missing the charm of poverty and ruin?";
			link.l1.go = "IslaMona_33";
		break;
		
		case "IslaMona_33":
            dialog.text = "You could say that. Now civilization is reaching even here. And people like me have no place in it.";
			link.l1 = "Buy yourself a jabot and a cane. You'll fit right in.";
			link.l1.go = "IslaMona_34";
		break;
		
		case "IslaMona_34":
            dialog.text = "Rather, let's go see your Spaniard and discuss the results of the reconnaissance. I have one more crazy idea...";
			link.l1 = "I just talked to him! Fine, let's go, Rodgar.";
			link.l1.go = "IslaMona_37";
			link.l2 = "How do you enjoy working with him?";
			link.l2.go = "IslaMona_35";
		break;
		
		case "IslaMona_35":
            dialog.text = "Highly educated and hardworking people! And Jimenez is truly a master. In the old days, one could have fetched a good amount of gold for such people. And their girls are beautiful, too...";
			link.l1 = "I will hear none of it, Rodgar! Let's go speak to that master of ours";
			link.l1.go = "IslaMona_36_1";
			link.l2 = "If they can't handle the job, we'll sell them. But keep the girls, ha-ha! Let's go see the master.. ";
			link.l2.go = "IslaMona_36_2";
		break;
		
		case "IslaMona_36_1":
			ChangeCharacterComplexReputation(pchar, "nobility", 6);
            dialog.text = "Seriously, Captain? I was only joking, let's go...";
			link.l1 = "";
			link.l1.go = "IslaMona_37";
		break;
		
		case "IslaMona_36_2":
			ChangeCharacterComplexReputation(pchar, "nobility", -6);
            dialog.text = "I knew you would support me, Captain! Let's go...";
			link.l1 = "";
			link.l1.go = "IslaMona_37";
		break;
		
		case "IslaMona_37":
            DialogExit();
			DoQuestReloadToLocation("IslaMona_TwoFloorHouse", "goto", "goto5", "IslaMona_HouseDialog");
		break;
		
		case "IslaMona_38":
            dialog.text = "He's not laughing, cap...";
			link.l1 = "";
			link.l1.go = "IslaMona_39";
		break;
		
		case "IslaMona_39":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_48";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_40":
            dialog.text = "That too, cap. We'll discuss it later...";
			link.l1 = "";
			link.l1.go = "IslaMona_41";
		break;
		
		case "IslaMona_41":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_52";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_42":
            dialog.text = "The gentleman has a point, Captain. None of us will be breaking our backs in the jungle. The business may be dirty, but you won't make anything more out of this place than a pirate's nest any other way.";
			link.l1 = "";
			link.l1.go = "IslaMona_43";
		break;
		
		case "IslaMona_43":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_58";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_44":
            dialog.text = "Captain, when you build the factory, the slaves will need protection. My guys will take care of that. One of them even shoots like Thor with lightning. Nothing motivates work like a hunting scope. We already have one gun; now we need a second. Any musket will do.";
			link.l1 = "";
			link.l1.go = "IslaMona_45";
		break;
		
		case "IslaMona_45":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_60";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_46":
            dialog.text = "And my guys will need the same amount of gold and another dozen bottles of good rum.";
			link.l1 = "How much wood will you be able to provide in each batch? And why do you need gold?";
			link.l1.go = "IslaMona_47";
		break;
		
		case "IslaMona_47":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_62";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_48":
            dialog.text = "Well, first of all, life without leisure is meaningless, and soon even the pious, hehe, Catholics will start climbing the walls. And secondly, if there's a tavern on the island, you'll be able to leave part of the crew here on standby. You see, convincing people to live like savages for free in huts on the beach for a whole year is quite difficult. But if there's a settlement with a tavern, hot food, music, and entertainment nearby... What else does a sailor need on shore leave?";
			link.l1 = "Whores?";
			link.l1.go = "IslaMona_49";
			link.l2 = "Drinks?";
			link.l2.go = "IslaMona_49";
		break;
		
		case "IslaMona_49":
            dialog.text = "You're right, but let's solve the problems one at a time. First, we'll rebuild your house...";
			link.l1 = "...";
			link.l1.go = "IslaMona_50";
		break;
		
		case "IslaMona_50":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_65";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_51":
            dialog.text = "He didn't even think of it, cap.";
			link.l1 = "Thank you, Rodgar. I understand that now I'll be able to service more ships in this little bay, right?";
			link.l1.go = "IslaMona_52";
		break;
		
		case "IslaMona_52":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_harbour_4";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_53":
            dialog.text = "Greetings, Captain! Have you come to discuss the work?";
			link.l1 = "No, not at all. I just missed your northern physiognomy.";
			link.l1.go = "IslaMona_54";
		break;
		
		case "IslaMona_54":
            dialog.text = "Shall we walk? I'll show you your factory.";
			link.l1 = "Lead the way.";
			link.l1.go = "IslaMona_55";
		break;
		
		case "IslaMona_55":
            DialogExit();
			IslaMona_PlantationGo();
		break;
		
		case "IslaMona_56":
            dialog.text = "H-hic! Cap, we are celebrating!";
			link.l1 = "Rodgar! Rodrigo! Well shit!";
			link.l1.go = "IslaMona_57";
		break;
		
		case "IslaMona_57":
            dialog.text = "What's the matter, c-c-captain? Do you not like the color of the walls?";
			link.l1 = "Just now did I realize that you two share the same name! Ha-ha-ha! A Spaniard and a pirate, with the same name, built a tavern on a deserted island and drinking together as if the Indian gods will devour everyone and end the world by sunrise! Ha-ha! I'm with you!";
			link.l1.go = "IslaMona_58";
		break;
		
		case "IslaMona_58":
            dialog.text = "Ha-ha-ha! So true! Cheers!";
			link.l1 = "Cheers!";
			link.l1.go = "IslaMona_59";
		break;
		
		case "IslaMona_59":
            DialogExit();
			npchar.dialog.currentnode = "IslaMona_60";
			IslaMona_ReloadTavern();
		break;
		
		case "IslaMona_60":
            dialog.text = "Want a drink, cap?";
			link.l1 = "Are you becoming a tavern keeper, Rodgar?";
			link.l1.go = "IslaMona_61";
		break;
		
		case "IslaMona_61":
            dialog.text = "Temporarily! The Spaniards especially appreciate having a pirate tending to the bar - this is the true exotics and adventure for them. But overall, it's nice here. If you decide to leave any of your crew in reserve in this settlement, just let me know - I'll arrange it.";
			link.l1 = "Where will they live though?";
			link.l1.go = "IslaMona_62";
		break;
		
		case "IslaMona_62":
            dialog.text = "Simple - we'll build some huts on the beach. That way, they'll be running from the tavern to the shore. Just a reminder, this island won't accommodate more than three hundred people, so keep that in mind for the future. Sometimes we'll ask you to bring rum and wine, so it would be great if you, Captain, could stock the goods in the warehouse in advance.";
			link.l1 = "I'll remember that. Well then, compadre. Entertain the Spaniards and take a break. Just please, don't drink until the whole village burns down - I couldn't bear the sight of that!";
			link.l1.go = "IslaMona_63";
		break;
		
		case "IslaMona_63":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			//LocatorReloadEnterDisable("IslaMona_TwoFloorHouse", "reload1", false);
			//LocatorReloadEnterDisable("IslaMona_TwoFloorHouse", "reload3", false);
			npchar.crew = "true"; // можно оставлять матросов
			npchar.crew.qty = 0;
			pchar.questTemp.IslaMona.Tavern = "done"; // флаг - таверна построена и сдана
			// belamour обнулим матросов-->
			ref rTown = GetColonyByIndex(FindColony(loadedLocation.fastreload));
			rTown.Ship.crew.quantity = 0;
			rTown.Ship.crew.morale = 0;
			rTown.Ship.Crew.Exp.Sailors   = 0;
			rTown.Ship.Crew.Exp.Cannoners = 0;
			rTown.Ship.Crew.Exp.Soldiers  = 0;
			ChangeCrewExp(rTown, "Sailors", 0);  // приведение к 1-100
			ChangeCrewExp(rTown, "Cannoners", 0);
			ChangeCrewExp(rTown, "Soldiers", 0);
			
		break;
		
		case "IslaMona_64":
            dialog.text = "Captain! I'm damn glad to see you! Thank Freyja, you arrived just in time!";
			link.l1 = "Aye, we've gotten ourselves into another fine mess. Hola, Rodrigo!";
			link.l1.go = "IslaMona_65";
		break;
		
		case "IslaMona_65":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_13";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_66":
            dialog.text = "No casualties. The surviving Spaniards reached us first, reported that there's a possiblity of encountering more guests, and we managed to bring almost all the provisions and equipment from the area to the settlement. The situation with the slaves didn't turn out very well, of course.";
			link.l1 = "";
			link.l1.go = "IslaMona_67";
		break;
		
		case "IslaMona_67":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_16";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_68":
            dialog.text = "What if they drag us out into an open assault?";
			link.l1 = "Then we work without guns. Like on a parade, we march together to the gates and then just hit them from behind. You hold the gates and provide support. That's it, good luck to us!";
			link.l1.go = "IslaMona_69";
		break;
		
		case "IslaMona_69":
            DialogExit();
			AddQuestRecord("IslaMona", "21");
			pchar.quest.islamona_def_jungle1.win_condition.l1 = "locator";
			pchar.quest.islamona_def_jungle1.win_condition.l1.location = "IslaMona_jungle_01";
			pchar.quest.islamona_def_jungle1.win_condition.l1.locator_group = "encdetector";
			pchar.quest.islamona_def_jungle1.win_condition.l1.locator = "enc04";
			pchar.quest.islamona_def_jungle1.function = "IslaMona_DefSoldiersInJungle"; // встреча с французами
			LAi_LocationFightDisable(&Locations[FindLocation("IslaMona_jungle_01")], true);//запретить драться
		break;
		
		case "IslaMona_70":
            dialog.text = "Hoorah, Captain!";
			link.l1 = "Agreed! That was such a blast, I felt like lying down myself. Guys, what did you load in there?";
			link.l1.go = "IslaMona_71";
		break;
		
		case "IslaMona_71":
            dialog.text = "Double load, Captain. So that one blast discourages them from fighting anymore!";
			link.l1 = "Weren't you concerned that the gun would blow up from such tender handling?";
			link.l1.go = "IslaMona_72";
		break;
		
		case "IslaMona_72":
            dialog.text = "I have a special talisman left from Wulfric. Some memory of our native Denmark. Shall we all go to the tavern, Captain? We're all tired after today.";
			link.l1 = "Yes, that would be great. Let's play some cards - we'll gamble on your miraculous talisman.";
			link.l1.go = "IslaMona_73";
		break;
		
		case "IslaMona_73":
            dialog.text = "Ha-ha, after such divine performance today, Captain, I might even consider that option!";
			link.l1 = "";
			link.l1.go = "IslaMona_74";
		break;
		
		case "IslaMona_74":
            DialogExit();
			sld = characterFromId("IM_fraofficer");
			sld.dialog.currentnode = "FraOfficer_18";
			LAi_CharacterEnableDialog(sld);
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_75":
            dialog.text = "Captain, did you hear that? I still have ringing in my ears. Whose mournful voice is that?";
			link.l1 = "That, Rodgar, is a live issue. Take him to the factory, put him on a chain, and await further instruction.";
			link.l1.go = "IslaMona_76";
		break;
		
		case "IslaMona_76":
            dialog.text = "Aye-aye, captain!";
			link.l1 = "";
			link.l1.go = "IslaMona_77";
		break;
		
		case "IslaMona_77":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);
			sld = characterFromId("IM_fraofficer");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			for (i=1; i<=5; i++) 
			{
				sld = characterFromId("IM_soldier_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			}
			for(i=4; i<=7; i++)
			{
				sld = characterFromId("IM_fra_sailor_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			}
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_20";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "IslaMona_78":
            dialog.text = "Captain, have you come to resolve the issue with the prisoner? I'm tired of standing here on guard.";
			link.l1 = "We'll have to kill him. The risk is too great, so we have no choice. Otherwise, I'd better not show my face in French colonies.";
			link.l1.go = "IslaMona_79";
			link.l2 = "I can't let him go, otherwise I'd better not show my face in French colonies. Put him in shackles and let him work at the factory. It's better than killing him.";
			link.l2.go = "IslaMona_80";
		break;
		
		case "IslaMona_79":
            dialog.text = "Got it! Let's get it done quickly. Go ahead, Captain. See you tomorrow.";
			link.l1 = "";
			link.l1.go = "IslaMona_81";
		break;
		
		case "IslaMona_80":
            dialog.text = "Wow. You're quite the evil genius. I wouldn't want to be your enemy. Well then, we'll have to conduct some explanatory work with him first. Go ahead, Captain. See you tomorrow.";
			link.l1 = "";
			link.l1.go = "IslaMona_81";
			pchar.questTemp.IslaMona.Fraprisoner = "true";
		break;
		
		case "IslaMona_81":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "IslaMona_DefFraPrisonerFin", 10.0); /// идёт внутрь фактории - УСТАНОВИТЬ ЛОКАТОР
		break;
		
		case "IslaMona_82":
            dialog.text = "What a slaughter! Too bad we couldn't shoot from the cannon, but they rushed right into your ambush - it was nice to watch!";
			link.l1 = "Yeah, we spilled a lot of blood on this land. But apparently, there's no other way to build a home in this world.";
			link.l1.go = "IslaMona_83";
		break;
		
		case "IslaMona_83":
            dialog.text = "Don't dwell on it too much, Captain. Fate itself brought them to Isla Mona. And let me tell you, fate can be quite the bitch!";
			link.l1 = "Fate, or the island?";
			link.l1.go = "IslaMona_84";
		break;
		
		case "IslaMona_84":
            dialog.text = "Both played their role.";
			link.l1 = "Haha! And both are beautiful! Alright, brave Viking. Collect the trophies and remove these bodies. Bury them with dignity. They are our own, after all...";
			link.l1.go = "IslaMona_85";
		break;
		
		case "IslaMona_85":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_20a";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "IslaMona_86":
            dialog.text = "Yes, Captain. That's right! Rodrigo said it so beautifully that it brought a tear to my eye. It's clear why the holy fathers want to put his arse on a stake!";
			link.l1 = "";
			link.l1.go = "IslaMona_87";
			locCameraFromToPos(1.36, 1.32, 0.31, true, 3.44, 0.20, -0.50);
		break;
		
		case "IslaMona_87":
            DialogExit();
			if (GetCharacterIndex("Mirabella") != -1)
			{
				sld = characterFromId("Mirabella");
				sld.dialog.currentnode = "mirabelle_46";
				LAi_SetActorType(sld);
				LAi_ActorDialogDelay(sld, pchar, "", 0.0);
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					sld = characterFromId("Mary");
					sld.dialog.currentnode = "IslaMona_2";
					LAi_SetActorType(sld);
					LAi_ActorDialogDelay(sld, pchar, "", 0.0);
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
					{
						sld = characterFromId("Helena");
						sld.dialog.currentnode = "IslaMona_2";
						LAi_SetActorType(sld);
						LAi_ActorDialogDelay(sld, pchar, "", 0.0);
					}
					else
					{
						sld = characterFromId("Himenes_companion_1");
						sld.dialog.currentnode = "island_man_2";
						LAi_SetActorType(sld);
						LAi_ActorDialogDelay(sld, pchar, "", 0.0);
					}
				}
			}
		break;
		
		case "IslaMona_88":
            dialog.text = "Rodrigo, and here I bumped right into our prelate in the boudoir... And let me tell you, it's the best establishment in Santiago!";
			link.l1 = "The best place if you fancy prelates too.";
			link.l1.go = "IslaMona_89";
		break
		
		case "IslaMona_89":
            DialogExit();
			sld = characterFromId("Himenes");
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_90":
            dialog.text = "Yeah, turned that scoundrel and heretic Rodrigo into a real pirate, indeed.";
			link.l1 = "By the way, enlighten me, Rodgar. Why are there so few Spanish pirates?";
			link.l1.go = "IslaMona_91";
		break;
		
		case "IslaMona_91":
            dialog.text = "Why so few? Ah, you mean pirate captains? Well, there are plenty of them, they just mostly operate under the Casa de Contratación in Seville. It's like military intelligence, but for some reason they call it a trading house...";
			link.l1 = "";
			link.l1.go = "IslaMona_92";
		break;
		
		case "IslaMona_92":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_77";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_93":
            dialog.text = "Yeah, why not send them a message and invite them over. Well, they all have patents, and they're idealistic too. They usually don't rob their own kind, only if the raid wasn't successful, ha-ha! They only drop by Puerto Principe and constantly clash with Pastor.\nRecently, one stood out... Diego de Montoya. Just when I last went on a campaign with Wulfric, I heard a lot about his adventures. You, captain, have something in common with him. And at the same time, you're very different... Anyway, what am I talking about? Let's have another round and play some cards.";
			link.l1 = "You don't have any money. You're not gambling on doubloons, are you?";
			link.l1.go = "IslaMona_94";
		break;
		
		case "IslaMona_94":
            dialog.text = "We bet one peso each. Shall we play until twenty? Hymenes, are you in?";
			link.l1 = "";
			link.l1.go = "IslaMona_95";
		break;
		
		case "IslaMona_95":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_79";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_96":
            dialog.text = "Let's play, cap?";
			if (sti(pchar.money) >= 20)
			{
				link.l1 = "Start it!";
				link.l1.go = "IslaMona_97";
			}
			link.l2 = "I'll pass too, Rodgar. Pesos or not, people lose ships like this. With islands. You have fun here, and I'll look around some more.";
			link.l2.go = "IslaMona_98";
		break;
		
		case "IslaMona_97": // игра в карты
            DialogExit();
			pchar.questTemp.GoldenGirl.Game.IslaMona = "true"; // атрибут квестовой игры
			npchar.money = 20;
			pchar.questTemp.IslaMona.Money = sti(pchar.money);
			pchar.money = 20;
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 1; // ставка
			LaunchCardsGame();
		break;
		
		case "IslaMona_98": // выход из-за стола
            DialogExit();
			IslaMona_ChurchTavernStandUp();
		break;
		
		case "IslaMona_99":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win"))
			{
				dialog.text = "Pass! Well, well, I'm not playing with you anymore! I'm sure you cheated, Captain! And letting a cheat go just like that wouldn't be right!";
				link.l1 = "I'm listening to you, Rodgar.";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Fail"))
				{
					dialog.text = "I won, cap. But I can't just have you leave empty handed like that, haha!";
					link.l1 = "Alright, you scoundrel. It'll be a lesson for me...";
				}
				else
				{
					dialog.text = "I won, cap. But I can't just have you leave empty handed like that, haha!";
					link.l1 = "Alright, you scoundrel. It'll be a lesson for me...";
				}
			}
			link.l1.go = "IslaMona_100";
		break;
		
		case "IslaMona_100":
            dialog.text = "Ah, come on! You've given me and my crew a chance for a real life away from cramped quarters, stale water, and the risk of getting a shard in... the skull. Here. This charm was brought by Wulfric from distant Denmark and then handed to me so I... heh, wouldn't have to delve into his basement too much. I don't need it anymore, but you - oh, you'll find it quite handy.";
			link.l1 = "Thank you, Rodgar. Indeed, a useful item. And beautiful too...";
			link.l1.go = "IslaMona_101_1";
			link.l2 = "Keep it, Rodgar. Without you, this place wouldn't exist. Let it be a reminder of your homeland.";
			link.l2.go = "IslaMona_101_2";
		break;
		
		case "IslaMona_101_1":
			GiveItem2Character(pchar, "talisman3");
			Log_Info("You received 'Thor's Hammer'");
			PlaySound("interface\important_item.wav");
            dialog.text = "I'm glad you enjoyed it, Captain. Another round?";
			link.l1 = "You guys relax here, and I'll take a look around some more.";
			link.l1.go = "IslaMona_102";
		break;
		
		case "IslaMona_101_2":
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			AddCharacterExpToSkill(pchar, "Fortune", 2000);
            dialog.text = "As you wish! Then I'll give one to a lady luck, haha! Another round?";
			link.l1 = "You guys relax here, and I'll take a look around some more.";
			link.l1.go = "IslaMona_102";
		break;
		
		case "IslaMona_102":
            DialogExit();
			DeleteAttribute(pchar, "questTemp.GoldenGirl.Game");
			DeleteAttribute(pchar, "GenQuest.Cards");
			pchar.money = sti(pchar.money)+sti(pchar.questTemp.IslaMona.Money);
			DeleteAttribute(pchar, "questTemp.IslaMona.Money");
			IslaMona_ChurchTavernStandUp();
		break;
		
		case "IslaMona_103":
            dialog.text = "Well, Captain. You've settled matters with the Spaniard, we've had our celebration, and the headache has subsided a bit. Life is good!";
			link.l1 = "What are you up to, Rodgar?";
			link.l1.go = "IslaMona_104";
		break;
		
		case "IslaMona_104":
			sTemp = "";
            if (CheckAttribute(pchar, "questTemp.IslaMona.MiraRodgar")) sTemp = "I'll get along with the woman. ";
			dialog.text = "I'll be hunting as usual, keeping an eye on my... our tavern, kicking the slaves at the factory. Perfect retirement.";
			link.l1 = "You are only five years older than me, Rodgar. And what about you, Rodrigo? How's it going?";
			link.l1.go = "IslaMona_105";
		break;
		
		case "IslaMona_105":
            DialogExit();
			sld = characterFromId("Himenes");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		// <-- Исла Мона
		
		case "repair":
			if (CheckSelfRepairConditions())
			{
				dialog.text = "By all means, captain! All we need are planks and sailcloth. Go to your landing location and order the crew to prepare materials.";
				link.l1 = "On my way. Do it fast.";
				link.l1.go = "repair_1";
			}
			else
			{
				dialog.text = "Sure, captain, but as I see it, your ship doesn't need a repair now.";
				link.l1 = "Just asked...";
				link.l1.go = "carpenter_exit";
			}
		break;
		
		case "repair_1":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			chrDisableReloadToLocation = true;
			DoQuestReloadToLocation(Pchar.location.from_sea, "reload", "sea", "Mtraxx_WolfreekRepairShore");
		break;
		
		case "shipstock_info":
			npchar.portman.info = "true";
            dialog.text = "It's possible, captain. A few limitations though: there are only two places on this island suitable for this. Also you can't leave here anyone but a single officer for each ship. We simply don't have enough resources to keep crews here. Yet. Finally, there is no room for first ranked ships.";
			link.l1 = "Got it. I am ready to leave a ship here.";
			link.l1.go = "shipstock";
			link.l2 = "Very well, I will get her ready.";
			link.l2.go = "carpenter_exit";
		break;
		
		case "shipstock":
			if(CheckAttribute(pchar,"questTemp.IslaMona.Harbour") && pchar.questTemp.IslaMona.Harbour == "done")
			{
				if(sti(npchar.portman) == 3)
				{
					dialog.text = "Captain, there are already three of your ships anchored at the dock. There's no more space available.";
					link.l1 = "You are right, I forgot.";
					link.l1.go = "carpenter_exit";
					break;
				}
				else
				{
					if(CheckAttribute(npchar,"FstClassInHarbour") && sti(npchar.portman) > 0)
					{
						dialog.text = "Captain, there's already a first-rate ship anchored at the dock. There's no more space available.";
						link.l1 = "You are right, I forgot.";
						link.l1.go = "carpenter_exit";
						break;
					}
				}
			}
			else
			{
				if (sti(npchar.portman) == 2)
				{
					dialog.text = "Captain, two of your ships are already anchored at the dock. There's no more space available.";
					link.l1 = "You are right, I forgot.";
					link.l1.go = "carpenter_exit";
					break;
				}
			}
			if (GetCompanionQuantity(pchar) < 2)
			{
				dialog.text = "Captain, you have only one ship.";
				link.l1 = "Hm... I should drink less...";
				link.l1.go = "carpenter_exit";
				break;
			}
            dialog.text = "What ship do you want to leave here?";
			for(i=1; i<COMPANION_MAX; i++)
			{
				int cn = GetCompanionIndex(PChar, i);
				if( cn > 0 )
				{
					ref chref = GetCharacter(cn);
					if (!GetRemovable(chref)) continue;

					attrL = "l"+i;
					Link.(attrL) = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
					Link.(attrL).go = "ShipStockMan_" + i;
				}
			}
			Link.l9 = "Wait, I have changed my mind.";
			Link.l9.go = "carpenter_exit";
		break;
		
		case "ShipStockMan_1":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 1);
			dialog.text = "Let's see...";
			Link.l1 = "Very good.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Wait, I have changed my mind.";
			Link.l2.go = "carpenter_exit";
		break;

		case "ShipStockMan_2":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 2);
			dialog.text = "Let's see...";
			Link.l1 = "Very good.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Wait, I have changed my mind.";
			Link.l2.go = "carpenter_exit";
		break;

		case "ShipStockMan_3":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 3);
			dialog.text = "Let's see...";
			Link.l1 = "Very good.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Wait, I have changed my mind.";
			Link.l2.go = "carpenter_exit";
		break;
		
		case "ShipStockMan_4":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 4);
			dialog.text = "Let's see...";
			Link.l1 = "Very good.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Wait, I have changed my mind.";
			Link.l2.go = "carpenter_exit";
		break;
		
		case "ShipStock_2":
            chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			if(CheckAttribute(pchar,"questTemp.IslaMona.Harbour") && pchar.questTemp.IslaMona.Harbour == "done")
			{
				if(sti(RealShips[sti(chref.Ship.Type)].Class) < 2 && sti(npchar.portman) > 0)
				{
					dialog.text = "Captain, I've mentioned before that our anchorage can only accommodate one first-rate ship. It's too large for the available space.";
					Link.l1 = "You are right, I forgot.";
					Link.l1.go = "carpenter_exit";
					break;
				}
			}
			else
			{
				if (sti(RealShips[sti(chref.Ship.Type)].Class) < 2)
				{
					dialog.text = "Captain, first-rate ships are too big for our shores. I've told you that already.";
					Link.l1 = "You are right, I forgot.";
					Link.l1.go = "carpenter_exit";
					break;
				}
			}
			if (sti(chref.Ship.Crew.Quantity) > 0)
			{
				dialog.text = "Captain, take all of her crew to your flagship except an officer.";
				Link.l1 = "Ah, right! I'll do that!";
				Link.l1.go = "carpenter_exit";
				break;
			}
			dialog.Text = "So, we are to keep here a"+XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName+"Acc")+" named '"+chref.Ship.Name+"'. Right?";
			Link.l1 = "Right.";
			Link.l1.go = "ShipStock_3";
			Link.l2 = "Wait, I have changed my mind.";
			Link.l2.go = "carpenter_exit";
		break;
		
		case "ShipStock_3":
            chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
            chref.ShipInStockMan = NPChar.id;
			chref.ShipInStockMan.MoneyForShip = 0;
            chref.ShipInStockMan.AltDate = GetQuestBookDataDigit();
            SaveCurrentNpcQuestDateParam(chref, "ShipInStockMan.Date");
            RemoveCharacterCompanion(pchar, chref);
            chref.location = "";
            chref.location.group = "";
            chref.location.locator = "";
			if(sti(RealShips[sti(chref.Ship.Type)].Class) < 2)
			{
				npchar.FstClassInHarbour = 1;
			}
            npchar.portman = sti(npchar.portman)+1;
            pchar.ShipInStock = sti(pchar.ShipInStock)+1;
			dialog.text = "Very well, we'll see her delivered to a safe harbor.";
			Link.l1 = "Excellent!";
			Link.l1.go = "carpenter_exit";
		break;
		
		case "shipstockreturn":
            if (GetCompanionQuantity(pchar) < COMPANION_MAX)
			{
				dialog.text = "Which ship are you going to take, captain?";
				cn = 1;
				for (i=1; i<MAX_CHARACTERS; i++)
				{
					makeref(chref, Characters[i]);
					if (CheckAttribute(chref, "ShipInStockMan"))
					{
						if (chref.ShipInStockMan == NPChar.id)
						{
							attrL = "l"+cn;
							Link.(attrL)    = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
							Link.(attrL).go = "ShipStockManBack_" + i;
							cn++;
						}
					}
				}
				link.l9 = "Wait, I have changed my mind.";
				link.l9.go = "carpenter_exit";
			}
			else
			{
				dialog.text = "Captain, you don't have room in your squadron for one more ship.";
				link.l1 = "Hm. It seems you're right.";
				link.l1.go = "carpenter_exit";
			}
		break;
		
		 case "ShipStockManBack":
            chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			dialog.Text = "Are you taking her?";
			link.l1 = "Yes.";
			link.l1.go = "ShipStockManBack2";
			link.l2 = "Wait, I have changed my mind.";
			link.l2.go = "carpenter_exit";
		break;
		
		case "ShipStockManBack2":
			DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			if(CheckAttribute(npchar,"FstClassInHarbour")) DeleteAttribute(npchar,"FstClassInHarbour");
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			DeleteAttribute(chref, "ShipInStockMan");
			SetCompanionIndex(pchar, -1, sti(NPChar.ShipToStoreIdx));
			npchar.portman = sti(npchar.portman)-1;
            pchar.ShipInStock = sti(pchar.ShipInStock)-1;
		break;
		
		case "storadge":
            dialog.text = "Here? No. But Wulfric had built a huge barn not far from here. A solid building, well covered with palm leaves and tarred sailcloth. It has a lock and a room for a cargo enough to fill a dozen of trade ships\nIt's empty now, but I have a key if you want to examine it. Shall we?";
			link.l1 = "Sure! By the way: what of rats on this island? Will they spoil my goods in the barn?";
			link.l1.go = "storadge_1";
		break;
		
		case "storadge_1":
            dialog.text = "Wolf had it covered it too: he brought two cats here from the mainland. He forgot about males though, so these crazy furred bitches make lousy sounds every time their season comes. But they hunt mice and rats pretty well. Don't worry about it, captain. Your goods will be safe from pest and winds.";
			link.l1 = "Great! I will make a good use of it. Keep your key to yourself and show me this storehouse.";
			link.l1.go = "storadge_2";
		break;
		
		case "storadge_2":
			DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			npchar.city = "islamona";
			npchar.Storage.Activate = true;
			SaveCurrentNpcQuestDateParam(npchar, "Storage.Date");
			npchar.MoneyForStorage = 0;
			npchar.storadge = true;
			LaunchStorage(29);
		break;
		
		case "storadge_3":
            dialog.text = "Follow me, captain.";
			link.l1 = "...";
			link.l1.go = "storadge_4";
		break;
		
		case "storadge_4":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			LaunchStorage(29);
		break;
		
		// Мирабель
		case "mirabelle":
			PlaySound("Voice\English\Girl_Q.wav");
            dialog.text = "Ah...";
			link.l1 = "Well now... A girl... What are you doing here?";
			link.l1.go = "mirabelle_1";
		break;
		
		case "mirabelle_1":
			PlaySound("Voice\English\Girl_Q.wav");
            dialog.text = "Oh...";
			link.l1 = "...";
			link.l1.go = "mirabelle_2";
		break;
		
		case "mirabelle_2":
            DialogExit();
			npchar.dialog.currentnode = "mirabelle_3";
			sld = characterFromId("Mrt_Rocur");
			sld.dialog.currentnode = "rocur_74";
			ChangeCharacterAddressGroup(sld, "LaVega_TwoFloorHouse", "goto", "goto8");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
		break;
		
		case "mirabelle_3":
			PlaySound("Voice\English\LE\Mirabel\Mirabel_01.wav");
            dialog.text = "Senor! Senor "+pchar.name+" don't kill me please! I beg you! I will say Tyrex nothing! I hate that beast! I beg you, por favor!";
			link.l1 = "...";
			link.l1.go = "mirabelle_4";
		break;
		
		case "mirabelle_4":
			DialogExit();
            npchar.dialog.currentnode = "mirabelle_5";
			npchar.greeting = "mirabella_goodgirl";
			sld = characterFromId("Mrt_Rocur");
			sld.dialog.currentnode = "rocur_80";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "mirabelle_5":
            dialog.text = "";
			link.l1 = "Hey lass! Heard that? You will go with me or this tough bastard will kill you.";
			link.l1.go = "mirabelle_6";
		break;
		
		case "mirabelle_6":
            dialog.text = "I will go with you, senor, wherever you are taking me!";
			link.l1 = "Good then. Keep your mouth shut, or I will kill you if you start yelling or calling for Tyrex. What's your name?";
			link.l1.go = "mirabelle_7";
		break;
		
		case "mirabelle_7":
            dialog.text = "Mirabelle...";
			link.l1 = "Behave well Mirabelle and this will end nice for you. Keep close to me and don't make any noise.";
			link.l1.go = "mirabelle_8";
		break;
		
		case "mirabelle_8":
            dialog.text = "I swear I won't, senor.";
			link.l1 = "...";
			link.l1.go = "mirabelle_9";
		break;
		
		case "mirabelle_9":
            DialogExit();
            npchar.dialog.currentnode = "mirabelle_10";
			LAi_SetImmortal(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			sld = characterFromId("Mrt_Rocur");
			sld.dialog.currentnode = "rocur_85";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
			pchar.questTemp.Mtraxx.Mirabella = "true";
		break;
		
		case "mirabelle_10":
            dialog.text = "Senor?";
			link.l1 = "You did well girl, I like you for that. Now we are going to my ship where you will be put in a small cabin for some time. I am sorry but I don't want you to run to Tyrex and tell him anything.";
			link.l1.go = "mirabelle_11";
		break;
		
		case "mirabelle_11":
            dialog.text = "No way senor! I would never go to Tyrex, este bastardo! I hate him! Lo odio!!!";
			link.l1 = "Woah! What did he do to you?";
			link.l1.go = "mirabelle_12";
		break;
		
		case "mirabelle_12":
            dialog.text = "A lot... I hate him, I hate him!";
			link.l1 = "I see. Once we arrive you will be living in quite a fancy house. Alone. Keep me in good mood and no one will ever hurt you. Now go to a longboat... Mirabelle.";
			link.l1.go = "mirabelle_13";
		break;
		
		case "mirabelle_13":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "OpenTheDoors", 20.0);
			pchar.quest.mtraxx_pasq_mirabella.win_condition.l1 = "location";
			pchar.quest.mtraxx_pasq_mirabella.win_condition.l1.location = "Shore75";
			pchar.quest.mtraxx_pasq_mirabella.function = "Mtraxx_PasqualeMirabella";
			pchar.quest.mtraxx_pasq_mirabella1.win_condition.l1 = "location";
			pchar.quest.mtraxx_pasq_mirabella1.win_condition.l1.location = "Shore77";
			pchar.quest.mtraxx_pasq_mirabella1.function = "Mtraxx_PasqualeMirabella";
			AddPassenger(pchar, npchar, false);//добавить пассажира
			SetCharacterRemovable(npchar, false);
			SetFunctionTimerCondition("Mtraxx_MirabellaSailOver", 0, 0, 30, false); // месяц на доплыть до Исла Моны
		break;
		
		case "mirabelle_14":
            dialog.text = "Have we arrived senor?";
			link.l1 = "Yes, sweetheart. This is my village and my house. I own the place. I am a rare guest here though - too much work to do out there. Make sure you keep my house clean while you live in it or I will give you to Rodgar and his carpenters. Feel free to walk around the island it is very beautiful, but there is no escape from it anyway.";
			link.l1.go = "mirabelle_15";
			// belamour legendary edition -->
			link.l2 = "Well here we are. This is my home. Everything on this island belongs to me. I don't come here often - I live on the ship after all, but still someone needs to look after the house. Rodgar graciously agreed to hand over this honorary role to you. You can walk around all you want, even in jungles, or on the beaches, but make sure to have someone as a companion there are still wild animals around. Anyway, you can't leave from here without a ship.";
			link.l2.go = "mirabelle_15a";
		break;
		
		case "mirabelle_15a":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
            dialog.text = "I have nowhere to run, senor "+pchar.name+". I have no one, and no one needs me. Unless you sell me to a brothel...";
			link.l1 = "At the hearth there is a hatch which leads to the underground, do not go there, you will fall into the cave and break your bones, or you will not be able to get back and you might die of hunger. And then it will be a pity that I saved you in vain.";
			link.l1.go = "mirabelle_16";
		break;
		
		case "mirabelle_15":
			ChangeCharacterComplexReputation(pchar,"nobility", -10);
			// <-- legendary edition
            dialog.text = "I have nowhere to leave senor "+pchar.name+". I have no family and no use. I might end up in a brothel again.";
			link.l1 = "There a hatch that leads to the cave, stay away from it. It's dark and dangerous down there.";
			link.l1.go = "mirabelle_16";
		break;
		
		case "mirabelle_16":
            dialog.text = "I will stay away senor.";
			link.l1 = "There is also a bedroom upstairs. Follow me.";
			link.l1.go = "mirabelle_17";
		break;
		
		case "mirabelle_17":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			pchar.quest.mtraxx_islamona_mirabella1.win_condition.l1 = "location";
			pchar.quest.mtraxx_islamona_mirabella1.win_condition.l1.location = "IslaMona_TwoFloorRoom";
			pchar.quest.mtraxx_islamona_mirabella1.function = "Mtraxx_PasqualeMirabellaRoom";
		break;
		
		case "mirabelle_18":
            dialog.text = "";
			link.l1 = "There. I have shown you the whole house. It is not worse than Tyrex's place you lived in before. I hope you like it.";
			link.l1.go = "mirabelle_19";
		break;
		
		case "mirabelle_19":
            dialog.text = "Yes senor. You have a great house. I promise to look after it well in your absence.";
			link.l1 = "I am glad you are so cooperative towards me. I hope you are being honest. Be honest with me or you'll regret being not. Be a good girl and don't make me sad and I will be good for you. Charlie Prince honors his word!";
			link.l1.go = "mirabelle_20";
			// belamour legendary edition -->
			link.l2 = "I believe you dear. I think you'll be safer here than being tied in shackles in that dark storage room where Tyrex kept you.";
			link.l2.go = "mirabelle_20a";
		break;
		
		case "mirabelle_20a":
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
            dialog.text = "Thank you senor "+pchar.name+". Thank you for not letting your... companero kill me. You are so kind to me...";
			link.l1 = "Heh, and you're funny,... And your face is pretty too, even with a brand on your forehead. I hope everything else is in place too... Well, now show your captain what you can do. Let's relax for a couple of hours after the sea roll.";
			link.l1.go = "mirabelle_21";
			link.l2 = "Very well. That's it, I have - a lot of work to do. And you settle down, meet Rodgar and the guys. When I get back, we'll chat some more.";
			link.l2.go = "mirabelle_21a";
		break;
		
		case "mirabelle_20":
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			// <-- legendary edition
            dialog.text = "Thank you senor "+pchar.name+". Thank you for not allowing your... companero to kill me. You are very kind.";
			link.l1 = "Heh, you are a funny little sweetheart... A pretty face too despite the mark. Hope the rest is in place too.. Now show your captain what you can do.";
			link.l1.go = "mirabelle_21";
			// belamour legendary edition -->
			link.l2 = "Very well. That's it, I have - a lot of work to do. And you settle down, meet Rodgar and the guys. When I get back, we'll chat some more.";
			link.l2.go = "mirabelle_21a";
		break;
		
		case "mirabelle_21a":
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			AddCharacterExpToSkill(pchar, "Fortune", 400);
			pchar.questTemp.Mtraxx.MirabellaFirstTimeSex = true;
            DialogExit();
			npchar.InOurHouse = true;
		    npchar.dialog.currentnode = "mirabelle_26";
		    chrDisableReloadToLocation = false;
			pchar.quest.mtraxx_mirabella_setlife.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_mirabella_setlife.function = "Mtraxx_MirabellaSetLife";
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		break;
		
		case "mirabelle_21":
			DialogExit();
			
			pchar.questTemp.Mtraxx.MirabellaFirstTimeKiss = true;
			sld = characterFromId("Mirabella");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			StartQuestMovie(true, false, true);
			LAi_SetActorType(pchar);
			LAi_Fade("IslaMona_MirabelleKiss", "");
		break;
		
		case "mirabelle_22":
			PlaySound("Voice\English\LE\Mirabel\Mirabel_07.wav");
            dialog.text = "Senor "+pchar.name+" you are so sweet... You are a real gentleman. Must have arrived from Europe not long ago.";
			link.l1 = "Do flatter me you little liar, I am buying it. Heh, your are good, Mirabelle! Tyrex has a good taste, he-he...";
			link.l1.go = "mirabelle_23";
			locCameraFromToPos(0.55, 1.64, -1.09, true, 0.63, -0.30, -3.12);
		break;
		
		case "mirabelle_23":
            dialog.text = "I am not. You are a gentleman. But you are pretending to be rude for some reason. Mhmm... I liked it very much. I'll be waiting to see you again...";
			link.l1 = "Ah yes, a gentleman... a gentleman of fortune, ha-ha! Very well sweetheart, settle down here for now.";
			link.l1.go = "mirabelle_24";
		break;
		
		case "mirabelle_24":
            dialog.text = "Goodbye, senor.";
			link.l1 = "...";
			// belamour legendary edition -->
			if(CheckAttribute(pchar,"questTemp.Mtraxx.MirabellaFirstTimeSex"))
			{
				link.l1.go = "mirabelle_28";
				DeleteAttribute(pchar,"questTemp.Mtraxx.MirabellaFirstTimeSex");
			}
			else link.l1.go = "mirabelle_25";
			// <-- legendary edition
		break;
		
		case "mirabelle_25":
            DialogExit();
			npchar.InOurHouse = true;
		    npchar.dialog.currentnode = "mirabelle_26";
			LAi_SetStayType(npchar);
		    chrDisableReloadToLocation = false;
			pchar.quest.mtraxx_mirabella_setlife.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_mirabella_setlife.function = "Mtraxx_MirabellaSetLife";
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		break;
		
		case "mirabelle_26":
            dialog.text = TimeGreeting()+", senor "+pchar.name+"! I am very glad to see you. How are you?";
			link.l1 = RandSwear()+""+RandPhraseSimple("Shiver me Timbers, shiver me Soul!","Oh, better to live and die, under the brave black flag that I fly!")+" Charlie Prince is fine, sweetheart.";
			link.l1.go = "mirabelle_26x";
			if (!CheckAttribute(pchar, "questTemp.MirabelleBlock")) {
				if (!CheckAttribute(npchar, "sex_date") || GetNpcQuestPastDayParam(npchar, "sex_date") >= 1)
				{
					link.l2 = "Sweetheart, how about you make a captain a bit happier?";
					link.l2.go = "mirabelle_sex";
				}
			}
		break;
		
		case "mirabelle_26x":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_26";
		break;
		
		case "mirabelle_sex":
            dialog.text = "Anything for you, senor!";
			link.l1 = RandPhraseSimple("Ready the grappels!","Board 'em!");
			link.l1.go = "mirabelle_sex_1";
		break;
		
		case "mirabelle_sex_1":
            DialogExit();
			
			StartQuestMovie(true, false, true);
			LAi_SetActorType(pchar);
			LAi_Fade("", "");
			
			LAi_SetActorType(npchar);
			// belamour legendary edition -->
			if(CheckAttribute(pchar,"questTemp.Mtraxx.MirabellaFirstTimeSex")) npchar.dialog.currentnode = "mirabelle_22";
		    else npchar.dialog.currentnode = "mirabelle_27";
			// <-- legendary edition
			if (pchar.location == "IslaMona_TwoFloorRoom") DoQuestCheckDelay("IslaMona_MirabelleKiss", 0.5);
			else DoQuestReloadToLocation("IslaMona_TwoFloorRoom", "goto", "goto2", "IslaMona_MirabelleKiss");
		break;
		
		case "mirabelle_27":
            dialog.text = "Mhm... Senor you are a magician! I hope you liked it too? I was doing my best.";
			link.l1 = "You did great sweetheart.";
			link.l1.go = "mirabelle_28";
			locCameraFromToPos(0.55, 1.64, -1.09, true, 0.63, -0.30, -3.12);
		break;
		
		case "mirabelle_28":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_26";
			LAi_SetStayType(npchar);
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
		break;
		
		case "mirabelle_sleep":
            dialog.text = "This not true, not true! Senor "+pchar.name+" is good and kind! He is only pretending to be an evil pirate! You are, senor "+pchar.name+"?";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep6_1");
		break;
		
		case "mirabelle_29":
            dialog.text = TimeGreeting()+", senor "+pchar.name+"! I am very happy to see you. How are you doing? Why are you so sad?";
			link.l1 = "Hello, Mirabelle. Why do you think that I am sad?";
			link.l1.go = "mirabelle_30";
		break;
		
		case "mirabelle_30":
            dialog.text = "Well, I can see it. You are not the usual you. Do you want me to cheer you up? Come on! I have picked some really sweet fruits from the jungles and the fish that Rodgar and his boys caught yesterday is roasted and still warm.";
			link.l1 = "Wait. I want to talk with you.";
			link.l1.go = "mirabelle_31";
		break;
		
		case "mirabelle_31":
            dialog.text = "Of course, senor, whatever you say. I am all ears";
			link.l1 = "Tell me how did you get into the hands of Tyrex and why is there a mark of a thief on your forehead. Don't be afraid, I will never hurt you. I only need to hear your story.";
			link.l1.go = "mirabelle_32";
		break;
		
		case "mirabelle_32":
            dialog.text = "Ah, senor! My story is brief and boring. I was born in Puerto Rico, my father was a white gentleman, my mother - an Indian. I've never seen my pa. When I was a kid I was a servant and when I grew up I had made a folly to steal my master's jewelry. I have never had my own and I wanted one so badly, just to try wearing it for a day. Of course, they had found out everything\nThere was a trial, I was whipped, branded and put in jail of San Juan. I did stay there for too long: one of officers made a deal with a chief and I was sold to a brothel of Philipsburg for handful of golden doubloons\nI had spent there a year or so. One unfortunate day we were paid a visit by Tyrex and his lousy friend with glasses.";
			link.l1 = "Pasquale Lavoisier...";
			link.l1.go = "mirabelle_33";
		break;
		
		case "mirabelle_33":
            dialog.text = "Yes-yes, his name was senor Pasquale Lavoisier. I have no clue what did they see in me, but shortly after their visit, Tyrex had bought me from Madame Johanna and put me inside a locked house full of chests and goods. It was the worst time in my life, even worse then days spent in San Juan prison. Tyrex had been visiting me every day unless he was in the sea and then I could breathe freely, but every time senor Lavoisier came I... I.... It was the worst of all. Senor "+pchar.name+", por favor, may I not speak of this?\nI don't know how long I was there. And then you came and taken me away from that awful house. I was very lucky that you were so kind.";
			link.l1 = "Kind? Mirabelle, but I did the very same thing to you: I took you to an island and locked you inside a house.";
			link.l1.go = "mirabelle_34";
		break;
		
		case "mirabelle_34":
            dialog.text = "No, senor, it is not true. Am I locked in here? I take a walk around the island every day. It is a wonderful and peaceful place. Do I have to do a lot of house work? Not at all, and I get used to it anyway. And you are not like Tyrex, not like his merchant friend. I am always happy to see you, you are so young and handsome. And a gentleman too...";
			link.l1 = "Mirabelle, do you want me to take you to any city? I will give you enough money. Where to? Choose any colony.";
			link.l1.go = "mirabelle_35";
		break;
		
		case "mirabelle_35":
            dialog.text = "Senor, do you want to shoo me away? Please don't, te lo ruego!";
			link.l1 = "Well... I thought you'd want to return back to normal life...";
			link.l1.go = "mirabelle_36";
		break;
		
		case "mirabelle_36":
            dialog.text = "Ah, senor "+pchar.name+", and what is there for me? How will I marry being a marked half-blood? I will be sold to a brothel again. Please, don't send me away. I like this place, I haven't felt so peaceful and secure anywhere but here. Rodgar and his boys are good guys, we are friends and they never hurt me each of them would risk his life for me. I like spending time with them and it's fun! Sometimes we make a fire on a beach and I dance samba. Please, senor, I will do anything for you, just let me stay!";
			link.l1 = "Fine, Mirabelle, stay here since you like this place that much. Just know that you are not a prisoner here, you can always ask me to take you away from here.";
			link.l1.go = "mirabelle_37";
		break;
		
		case "mirabelle_37":
            dialog.text = "My dear good senor, thank you! Thank you! Thank you! I will never ask you for anything like this - I want to stay a prisoner of this island... and your prisoner, tee-hee... You are so kind but sad today! You don't sing and swear as you usually do.";
			link.l1 = "I might sing but no more swearing, Mirabelle. And... I am sorry if I was ever rude to you.";
			link.l1.go = "mirabelle_38";
		break;
		
		case "mirabelle_38":
            dialog.text = "Will you be stern and strict just like an English lord?.. Ah... senor, do you want me to dance and sing tonight? Just for you. Now come with me! There is no a better cure for sadness than love. I have missed you so much.";
			link.l1 = "Hah! Good point, my dear girl... Let's go.";
			link.l1.go = "mirabelle_39";
		break;
		
		case "mirabelle_39":
            DialogExit();
			LAi_SetActorType(npchar);
		    npchar.dialog.currentnode = "mirabelle_40";
			if (pchar.location == "IslaMona_TwoFloorRoom") DoQuestCheckDelay("IslaMona_MirabelleKiss", 0.5);
			else DoQuestReloadToLocation("IslaMona_TwoFloorRoom", "goto", "goto2", "IslaMona_MirabelleKiss");
		break;
		
		case "mirabelle_40":
			PlaySound("Voice\English\LE\Mirabel\Mirabel_07.wav");
            dialog.text = "Ah, senor "+pchar.name+", you were so gentle today, mhm... Are you pleased with me, my dear capitán?";
			link.l1 = "Everything was delightful, Mirabelle.";
			link.l1.go = "mirabelle_41";
			locCameraFromToPos(0.55, 1.64, -1.09, true, 0.63, -0.30, -3.12);
		break;
		
		case "mirabelle_41":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_42";
			LAi_SetStayType(npchar);
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
		break;
		
		case "mirabelle_42":
			bool bMary = GetCharacterIndex("Mary") != -1 && CheckAttribute(pchar, "questTemp.LSC.Mary_officer");
			bool bHelena = GetCharacterIndex("Helena") != -1 && CheckAttribute(pchar, "questTemp.Saga.Helena_officer");
            dialog.text = TimeGreeting()+", senor "+pchar.name+"! I am so happy to see you! How are you doing?";
			link.l1 = ""+LinkRandPhrase("Glad to see you too, my girl.", "Hi, Mirabelle. You are always the same - joyful and beautiful, what a pleasant sight.","Hello, pretty one. You look stunning!")+"I am doing just fine. Hope you are well too.";
			link.l1.go = "mirabelle_42x";
			if (!bMary && !bHelena && !CheckAttribute(npchar,"quest.rodgar")) // прогона 3
			{
				if (!CheckAttribute(npchar, "sex_date") || GetNpcQuestPastDayParam(npchar, "sex_date") >= 1)
				{
					link.l2 = "Mirabelle, I have already started missing you and your weasel. Will you kiss your sea wolf?";
					link.l2.go = "mirabelle_43";
				}
			}
		break;
		
		case "mirabelle_42x":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_42";
		break;
		
		case "mirabelle_43":
            dialog.text = "Ah, my sweet captain, I have missed you too! Come on, I am at the edge!";
			link.l1 = "...";
			link.l1.go = "mirabelle_39";
		break;
		
		// Jason Исла Мона
		case "mirabelle_44":
			dialog.text = "Senor Captain! Captain "+pchar.name+"! I'm so happy! You'll save us!";
			link.l1 = "I'm glad to see you too, Mirabelle. So, what of the losses?";
			link.l1.go = "mirabelle_45";
		break;
		
		case "mirabelle_45":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_42";
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_66";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "mirabelle_46":
			dialog.text = "Captain, Captain, thank you! You are the best, the kindest! You not only saved me from monsters, but also gave me a new life! To all of us!";
			link.l1 = "";
			link.l1.go = "mirabelle_47";
			locCameraFromToPos(1.25, 1.28, 0.71, false, 2.28, -0.20, 1.91);
		break;
		
		case "mirabelle_47":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_42";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				sld = characterFromId("Mary");
				sld.dialog.currentnode = "IslaMona_2";
				LAi_SetActorType(sld);
				LAi_ActorDialogDelay(sld, pchar, "", 0.0);
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					sld = characterFromId("Helena");
					sld.dialog.currentnode = "IslaMona_2";
					LAi_SetActorType(sld);
					LAi_ActorDialogDelay(sld, pchar, "", 0.0);
				}
				else
				{
					sld = characterFromId("Himenes_companion_1");
					sld.dialog.currentnode = "island_man_2";
					LAi_SetActorType(sld);
					LAi_ActorDialogDelay(sld, pchar, "", 0.0);
				}
			}
		break;
		
		case "mirabelle_48":
			dialog.text = "Senor Captain!";
			link.l1 = "Hello to you too, beauty. Not bored, are you?";
			link.l1.go = "mirabelle_49";
		break;
		
		case "mirabelle_49":
			dialog.text = "Ah, Captain! Ever since you rescued me from that dreadful house, my life has gained color and joy.";
			link.l1 = "Are you happy?";
			link.l1.go = "mirabelle_50";
		break;
		
		case "mirabelle_50":
			dialog.text = "Of course! And I would like to share this happiness with you... I'll be waiting for you in your room, upstairs.";
			link.l1 = "What a woman...";
			link.l1.go = "mirabelle_51";
		break;
		
		case "mirabelle_51":
			DialogExit();
			LAi_SetActorType(npchar);
		    npchar.dialog.currentnode = "mirabelle_40";
			DoQuestFunctionDelay("IslaMona_ChurchReloadToRoom", 0.5);
			pchar.questTemp.IslaMona.Mirabelle = "true";
		break;
		
		case "mirabelle_52":
			dialog.text = "Senor Captain!";
			link.l1 = "Hello to you too, beauty. Not bored, are you?";
			link.l1.go = "mirabelle_53";
		break;
		
		case "mirabelle_53":
			dialog.text = "Ah, Captain! Ever since you rescued me from that dreadful house, my life has gained color and joy.";
			link.l1 = "Are you happy?";
			link.l1.go = "mirabelle_54";
		break;
		
		case "mirabelle_54":
			dialog.text = "Very! Except...";
			link.l1 = "I see, you want to ask something of me?";
			link.l1.go = "mirabelle_55";
		break;
		
		case "mirabelle_55":
			dialog.text = "Yes, Captain! I would like to... share my happiness with a certain man...";
			link.l1 = "Will he mind?";
			link.l1.go = "mirabelle_56";
		break;
		
		case "mirabelle_56":
			dialog.text = "No, no, Captain. We would be happy together, I know it for sure. Just... will you allow it?";
			link.l1 = "You more than anyone else deserve this. But I won't be marrying the two of you, don't even ask!";
			link.l1.go = "mirabelle_57";
		break;
		
		case "mirabelle_57":
			dialog.text = "Ha-ha! My gentleman! Thank you, Senor Captain. I don't know what they say about you in the big world, but I always saw in you the kindest and brightest person.";
			link.l1 = "Good luck to you, Mirabelle.";
			link.l1.go = "mirabelle_58";
		break;
		
		case "mirabelle_58":
			DialogExit();
			npchar.quest.rodgar = true;
		    npchar.dialog.currentnode = "mirabelle_42";
		break;
		
		// губернатор Картахены
		case "CartahenaMayor":
            dialog.text = "Fucking ladrones! Whatever, our courier is already on the way to Porto Bello. Soon our squadron will arrive and...";
			link.l1 = TimeGreeting()+", your Highness. Pleasure to see you in such a beautiful mansion. I hope you will keep it after we leave. If I were you I wouldn't count on the squadron, plus we are not staying here for more than three days. I bet you understand that noble dons of Porto Bello won't arrive here to help you that soon. So, let's get straight to business, shall we?";
			link.l1.go = "CartahenaMayor_1";
		break;
		
		case "CartahenaMayor_1":
            dialog.text = "Talking business already? Look at the window! Look what your cutthroats are doing in the streets and in houses!";
			link.l1 = "Oh, your Highness, this is nothing compared to what they will be doing if you aren't cooperative enough. I hope you understand who are these men...";
			link.l1.go = "CartahenaMayor_2";
		break;
		
		case "CartahenaMayor_2":
            dialog.text = "I know what an arrant evil man pirate Charlie Prince is capable of! I know who is his boss! In time, we will burn out your bandit lair on Hispaniola! How much?";
			link.l1 = "Don't waste words, my dear governor. You'd better get me 250 000 pesos.";
			link.l1.go = "CartahenaMayor_3";
		break;
		
		case "CartahenaMayor_3":
            dialog.text = "What?! Your insolence is limitless! This is a robbery!";
			link.l1 = "It is robbery, of course. What else could it be? Gather your elites, your merchants and traders, gather gold into a big chest because otherwise... I will make it much worse for you and your people.";
			link.l1.go = "CartahenaMayor_4";
		break;
		
		case "CartahenaMayor_4":
            dialog.text = "Fucking pirate! Bastardo! Heretic! Vete a la mierda!";
			link.l1 = "Because of your dirty tongue I increase the ransom up to 300 000.";
			link.l1.go = "CartahenaMayor_5";
		break;
		
		case "CartahenaMayor_5":
            dialog.text = "QUEMAR EN EL INFIERNO, HIJO DE PUTA!!!";
			link.l1 = "350 000. Do you want to keep on?";
			link.l1.go = "CartahenaMayor_6";
		break;
		
		case "CartahenaMayor_6":
            dialog.text = "There is no such money in the city!";
			link.l1 = "You lie. It just can't be. We are able to gather at least a million here, but I am afraid we don't have enough time to do it. Therefore I will be kind and generous. You know the sum. Go get it.";
			link.l1.go = "CartahenaMayor_7";
		break;
		
		case "CartahenaMayor_7":
            dialog.text = "I am telling you again, Charlie Prince: there is no such money in Cartagena!";
			link.l1 = "Oh... how can you be so boring. Cutlass! Search around and bring here everyone you find. Search well! And we will wait here for now, you grace...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CartahenaInResidence");
		break;
		
		case "CartahenaMayor_8":
            dialog.text = "";
			link.l1 = "Hey, senor 'Stubborn'! Haven't you changed your mind concerning the money gathering in good city Cartagena?... What happened, why are you so serious all of a suden?! Are you well? Should I bring you some water?";
			link.l1.go = "CartahenaMayor_9";
		break;
		
		case "CartahenaMayor_9":
            dialog.text = "";
			link.l1 = "As far I as I understand, these two ladies are your wife and your daughter, am I right? The third girl looks like a servant, you seem to be not giving a shit about her so we won't do her any harm, but these two beauties may get some attention from my brother in arms, senor Cutlass. He seems to like them, senor. So what? Are you going to handle the ransom?";
			link.l1.go = "CartahenaMayor_10";
		break;
		
		case "CartahenaMayor_10":
            dialog.text = "I... I will need time.";
			link.l1 = "Aha! Now you are talking! So who is the bastardo here? You didn't give a fuck about my men terrorizing your citizens but your two women are a completely different matter, right? Did you dare to fucking bargain with me, jerk? I will show what it means to cross Charlie Prince!";
			link.l1.go = "CartahenaMayor_10x";
		break;
		
		case "CartahenaMayor_10x":
            dialog.text = "";
			link.l1 = "Go and gather the fucking ransom. 350 000 and not a peso less. You have one day. We'll stay here to drink some wine and mingle with these sweet women... Be swift amigo, or me and my friend here, senor Cutlass, might fall in love with your beauties and then you will have to ransom them too. Forward! March!";
			link.l1.go = "CartahenaMayor_11";
		break;
		
		case "CartahenaMayor_11":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Mtraxx_CartahenaResidenceWait", 5.0);
		break;
		
		case "CartahenaMayor_12":
			AddMoneyToCharacter(pchar, 350000);
            dialog.text = "Take your blood money, Charlie Prince!";
			link.l1 = "Did you gather a ransom? Splendid! But you are late for an hour, my dear governor. This extra hour gave me and the Cutlass an understanding that our lives will be way too boring without these beauties who were so kind and talkative with us...";
			link.l1.go = "CartahenaMayor_13";
		break;
		
		case "CartahenaMayor_13":
            dialog.text = "You... you!";
			link.l1 = "Ah, you are too nervous because of your work, my friend. I was joking... Cutlass! Let's go, we are leaving!";
			link.l1.go = "CartahenaMayor_14";
		break;
		
		case "CartahenaMayor_14":
            DialogExit();
			AddQuestRecord("Roger_9", "7");
			AddDialogExitQuestFunction("Mtraxx_CartahenaToFort");
		break;
		
		// Камилла
		case "camilla":
			PlaySound("Voice\English\hambit\Girls_3.wav");
            dialog.text = "Oh, so this is The Charlie Prince, the famous pirate, the terror of the Spanish South Main!";
			link.l1 = RandSwear()+"Heh, I had no idea I am that popular in Tortuga. What's your name, sweet girl?";
			link.l1.go = "camilla_1";
		break;
		
		case "camilla_1":
            dialog.text = "My name is Camilla.";
			link.l1 = "Camilla... I used to know a girl with the same name back in France. It was so long ago!";
			link.l1.go = "camilla_2";
		break;
		
		case "camilla_2":
			PlaySound("ambient\tavern\orijka_003.wav");
            dialog.text = "";
			link.l1 = "(puking) ... fuck... I am sorry princess, but Prince is kinda drunk tonight. So... hum.. why did you come to me?";
			link.l1.go = "camilla_3";
		break;
		
		case "camilla_3":
            dialog.text = "For various reasons. Or maybe for no reason.";
			link.l1 = "God, this is too complicated. You seem to be a mystery, lass.";
			link.l1.go = "camilla_4";
		break;
		
		case "camilla_4":
            dialog.text = "Every lass must have a mystery.";
			link.l1 = "Seems like you want me to solve this mystery. No? I am a master of solving girls' mysteries, I swear it! Should we go to a tavern and drink some wine? I will get you the best treat!";
			link.l1.go = "camilla_5";
		break;
		
		case "camilla_5":
            dialog.text = "Mmm... I like tough guys. But I won't be drinking wine downstairs close to drunk low lives. Get us a room, we will drink and talk there.";
			link.l1 = RandSwear()+"You are hot! Follow me!";
			link.l1.go = "camilla_6";
		break;
		
		case "camilla_6":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.mtraxx_retribution_tavern.win_condition.l1 = "locator";
			pchar.quest.mtraxx_retribution_tavern.win_condition.l1.location = "Tortuga_town";
			pchar.quest.mtraxx_retribution_tavern.win_condition.l1.locator_group = "reload";
			pchar.quest.mtraxx_retribution_tavern.win_condition.l1.locator = "reload4_back";
			pchar.quest.mtraxx_retribution_tavern.function = "Mtraxx_RetributionToTavern";
		break;
		
		case "camilla_7":
			PlaySound("Voice\English\hambit\Gr_officiant_1.wav");
            dialog.text = "Come on... Pour it up, don't keep the lady waiting!";
			link.l1 = "Sure, my sweetie!";
			link.l1.go = "camilla_8";
		break;
		
		case "camilla_8":
			LAi_Fade("", "");
			PlaySound("ambient\tavern\krujki_005.wav");
			PlaySound("ambient\tavern\naliv_003.wav");
			PlaySound("ambient\tavern\glotok_001.wav");
			WaitDate("", 0, 0, 0, 1, 5);
            dialog.text = "Mmm... Just to think of it, I am here all alone with Charlie Prince, drinking an excellent wine...";
			link.l1 = "You are going to enjoy this ride with me, oh I promise! Charlie Prince is gentle and kind to ladies who submit themselves to him. Will you submit, princess?";
			link.l1.go = "camilla_9";
		break;
		
		case "camilla_9":
            dialog.text = "Tee-hee... Of course, sweetie! Your promises sound so tempting, you know...";
			link.l1 = "Well, let's not waste time then, beauty?";
			link.l1.go = "camilla_10";
		break;
		
		case "camilla_10":
            dialog.text = "Oh! I love! Real men!..";
			link.l1 = "...";
			link.l1.go = "camilla_11";
		break;
		
		case "camilla_11":
            DialogExit();
			pchar.GenQuest.FrameLockEsc = true;
			bDisableCharacterMenu = true;
			ResetSound();
			WaitDate("", 0, 0, 0, 2, 30);
			SetLaunchFrameFormParam("", "", 0, 5.1);
			SetLaunchFrameFormPic("loading\inside\censored1.tga");
			PlayStereoSound("sex\sex2.wav");
			LaunchFrameForm();
			if(IsEquipCharacterByArtefact(pchar, "totem_03")) 	
			{
				AddCharacterHealth(pchar, 6);
				AddCharacterMaxHealth(pchar, 1.0);
			}
			else AddCharacterHealth(pchar, 3);
			LAi_SetCurHPMax(pchar);
			DoQuestCheckDelay("Mtraxx_RetributionRoomSex", 5.1);
		break;
		
		case "camilla_12":
            dialog.text = "Mmm...";
			link.l1 = "Did you like it, my princess?";
			link.l1.go = "camilla_13";
		break;
		
		case "camilla_13":
            dialog.text = "Sure thing! I hope you liked me too.";
			link.l1 = "Heh! Even my head is crystal clear now!";
			link.l1.go = "camilla_14";
		break;
		
		case "camilla_14":
            dialog.text = "Prince, I have an ask for you. Will you help me?";
			link.l1 = "I will get a star from the sky for you, ha-ha! Go ahead.";
			link.l1.go = "camilla_15";
		break;
		
		case "camilla_15":
            dialog.text = "I need to get to La Vega, to see Tyrex. I am afraid of him, but you do business together. Please get me to him.";
			link.l1 = "Look at this! And why would such a sweet, fragile girl want to see the Code's Keeper?";
			link.l1.go = "camilla_16";
		break;
		
		case "camilla_16":
            dialog.text = "This sweet, fragile girl would like to make some coin. My late father and brothers didn't leave me much cash. Tyrex can fix this.";
			link.l1 = "Oh really? And how? Want a lead for a Spanish galleon? Ha-ha!";
			link.l1.go = "camilla_17";
		break;
		
		case "camilla_17":
            dialog.text = "Plundering caravans and cities is a tough guys' business, just like you, honey. I have another business for Marcus. He buys and sells information, right? I have something... No way that I can use it myself, but he could. I will be happy enough just to get a small interest out of it.";
			link.l1 = "Interesting! Tell me more.";
			link.l1.go = "camilla_18";
		break;
		
		case "camilla_18":
            dialog.text = "Hm... I don't know...";
			link.l1 = "Oh, come on. Consider me a right hand of Tyrex, I did a lot of digging for him by now, trust me. If your information is worth it - I will buy it myself.";
			link.l1.go = "camilla_19";
		break;
		
		case "camilla_19":
            dialog.text = "Fine. I will tell you more, but no details until I receive the money. Deal, honey?";
			link.l1 = "Sure thing, pretty one. Charlie Prince doesn't fuck his partners up... you know what I mean, ha-ha-ha! Go ahead, I am all ears.";
			link.l1.go = "camilla_20";
		break;
		
		case "camilla_20":
            dialog.text = "... My pa was a skipper on a merchant schooner. One day he somehow learnt about an old Spanish mining settlement lying deep in Main's jungles. Twenty years ago it was destroyed by an earthquake. Miners abandoned it and secret passages were forgotten. Except one. My father found it\nHe took my brothers and a guide there and they had found the place filled with gold mined and smelted years ago. A lot of gold. One million pesos at least. Father had returned to a ship so he could get men to transport the gold but he was shocked to find out that she was gone. Seems like his first mate had started a mutiny and they left him and my brothers on deserted shores\nThey built a long boat and sailed along the shore desperately looking for an inhabited place, but... (sobs) a storm hit them and my (sobs) brothers died. Father made it alive but he didn't live long after he returned home - deaths of my brothers were slowly killing him day by day. Before he passed away, he'd made a map and gave it to me\nHe told me that when I got married, my husband should go there, get the gold and we shall live our lives like kings. Sure we will, but I will not let my man go inside those cursed jungles. Not again! One million pesos, my father said, but it's just not my league. Such prize, only the best and toughest of men can get it - men like Marcus Tyrex. This is why I'm going to meet him.";
			link.l1 = "How much do you want for the map?";
			link.l1.go = "camilla_21";
		break;
		
		case "camilla_21":
            dialog.text = "Two hundred golden doubloons. It's nothing compared to the prize. Tyrex will agree to this, I am sure. He is as rich as Crassus.";
			link.l1 = "Heh! And what if this is all a trickery?";
			link.l1.go = "camilla_22";
		break;
		
		case "camilla_22":
            dialog.text = "Do I look suicidal? Trying to cross Tyrex? Sweetie, better live in poverty than not live at all. So will you take me there? Please...";
			link.l1 = "Where is the map? Will you show it to me?";
			link.l1.go = "camilla_23";
		break;
		
		case "camilla_23":
            dialog.text = "My priest keeps it safe. I will show it to you for 200 doubloons.";
			link.l1 = "Very well! I am buying it. Strangers in taverns sometimes ask much more for garbage.";
			link.l1.go = "camilla_24";
		break;
		
		case "camilla_24":
            dialog.text = "Are you? Is it true, honey? I am so happy I am not going to La Vega! To be honest, I fear Marcus. I fear you too, by the way... but a bit less.";
			link.l1 = "Such sweet little girl doesn't need to fear me. Where should I bring the money?";
			link.l1.go = "camilla_25";
		break;
		
		case "camilla_25":
            dialog.text = "Let's make a deal: find me in our church any day from ten o'clock in the morning till one o'clock in the afternoon. I will be feeling much safer under protection of this sacred place. We will conclude our deal there.";
			link.l1 = "Do you still fear me? Ha-ha! Don't Camilla, I won't cheat on you. Charlie Prince won't do such a low thing for two hundred doubloons, besides I want to help you out.";
			link.l1.go = "camilla_26";
		break;
		
		case "camilla_26":
            dialog.text = "Wonderful. Very well then handsome, I will be waiting for you... Thank you for an amazing time we had together tonight! I am so happy that we have met!";
			link.l1 = "See you soon, pretty one.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionOutRoom");
		break;
		
		case "camilla_27":
			PlaySound("Voice\English\hambit\Girls_3.wav");
            dialog.text = "So? Did you bring the money, sweetie?";
			if (PCharDublonsTotal() >= 200) // belamour legendary edition
			{
				link.l1 = "Yes. Have your gold and now give me the map.";
				link.l1.go = "camilla_28";
			}
			else
			{
				link.l1 = "I am right after it.";
				link.l1.go = "camilla_27x";
			}
		break;
		
		case "camilla_27x":
            DialogExit();
			npchar.dialog.currentnode = "camilla_27";
		break;
		
		case "camilla_28":
			RemoveDublonsFromPCharTotal(200); // belamour legendary edition
			GiveItem2Character(pchar, "mapEnrico"); 
            dialog.text = "Thank you, honey... Here, have it. I swear by my father's memory - this map is not a fake, it will lead you straight where you should go...";
			link.l1 = "Good, sweetie. How about we celebrate our deal just like the last time?";
			link.l1.go = "camilla_29";
		break;
		
		case "camilla_29":
            dialog.text = "I'd like to, Prince, but I am preparing myself for a confession before my priest, therefore I am obliged to stay far from any temptations right now. Let's do it next time.";
			link.l1 = "Uh, you are teasing me, lass. Fine! No time to waste: we are about to set sails. I swear I will double your interest if your daddy's map will indeed lead me to the gold.";
			link.l1.go = "camilla_30";
		break;
		
		case "camilla_30":
            dialog.text = "You are so generous, darling. Bon voyage!";
			link.l1 = "Yo-ho-ho!";
			link.l1.go = "camilla_31";
		break;
		
		case "camilla_31":
            DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("Roger_10", "2");
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			pchar.quest.mtraxx_retribution_carataska.win_condition.l1 = "location";
			pchar.quest.mtraxx_retribution_carataska.win_condition.l1.location = "shore10";
			pchar.quest.mtraxx_retribution_carataska.function = "Mtraxx_RetributionCarataska";
			pchar.questTemp.Mtraxx.Retribution = "carataska";
		break;
		
		case "camilla_sleep":
            dialog.text = "Your bastards had slain my father and my brothers. Your attack on Cartagena has brought grief to every family there. I hope you are scared now, scared as much as we, citizens of Cartagena were, when your brutes were enjoying themselves on the streets and in the houses. You will burn in hell, Charlie Prince.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep4");
		break;
		
		// дон Энрико - народный мститель
		case "enrico":
			PlaySound("Voice\English\LE\Zorro\Don_Enriko_01.wav");
            dialog.text = "So few things in this world joy me as much as watching rats in the box tearing each other apart!\nOnly the strongest and the most disgusting rat survives. Then all you have to do is to squeeze it...";
			link.l1 = "Argh! Who are you?!";
			link.l1.go = "enrico_1";
		break;
		
		case "enrico_1":
			PlaySound("Voice\English\LE\Zorro\Don_Enriko_02.wav");
            dialog.text = "I am don Enrico. English scum call me Fox, Dutch call me Vos, French call me Renaud. But I prefer my Spanish home nickname - Zorro. I punish the evil that tortures and terrorizes the common folk, the least protected part of the people\nThis trial today will judge four pirates of Marcus Tyrex: Bold Jeffry, Pelly the Cutlass, Luke the Leprechaun and Charlie Prince - these bandits are responsible for a massacre in Merida and Cartagena. The last bastard called Handsome Jean didn't show up here, he must be the smartest of your lot.";
			link.l1 = "What?!";
			link.l1.go = "enrico_2";
		break;
		
		case "enrico_2":
            dialog.text = "You are a scumbag, Charlie Prince, but you are not an idiot. I have figured it out already, I think. It's a trap for you all set by me with a help of fake maps, documents, words and promises of gold and silver. I have lured you all into these dungeons where you destroyed each other driven by your disgusting traits: envy, greed, meanness and unscrupulousness. It was a truly just a nemesis!";
			link.l1 = "Camilla... I should had known there was something wrong about that girl!";
			link.l1.go = "enrico_3";
		break;
		
		case "enrico_3":
            dialog.text = "A girl named Camilla had been living a peaceful life in Cartagena with her father and brothers, she was about to get married when you and your devils attacked the city. Your pirates had slain everyone close to her, so she swore to do whatever it takes to avenge them. It was a tough role to play for her. She even had to sleep with a bastard responsible for the deaths of her family. I fear to imagine what were she feeling during the act\nThe poor girl had spent days in church praying for forgiveness. She donated the bloody doubloons you gave her to the victims who suffered most from your attack. She is now in a monastery, poor soul. You have broken her life, scum! Think about it! Think of how many Camillas, Isabelas, Rositas you had raped and made widows! How many Juans, Carloses, Pedros you bastards had slain and tortured!\nRemember Merida! Remember how you promised to the head of the town not to set it on fire and then burnt entire place to the ground!";
			link.l1 = "I never meant to do it! When I had left the residence the fire was already everywhere. I didn't order this...";
			link.l1.go = "enrico_4";
		break;
		
		case "enrico_4":
            dialog.text = "You are responsible for the acts of your pirates. Dead men are hanging on your neck and soon they will drag you to hell!";
			link.l1 = "Come then! Huh? Fight me! This is what you want, right?! Let's do it then!";
			link.l1.go = "enrico_5";
		break;
		
		case "enrico_5":
            PlaySound("Voice\English\LE\Zorro\Don_Enriko_03.wav");
            if (CharacterIsAlive("Tonzag") && CheckPassengerInCharacter(pchar, "Tonzag"))
			{
				dialog.text = "No, Charlie Prince. Don't grab for your weapon, it's pointless... I could kill you easily, however quick death is not enough for a bastard like you. You will stay in this dungeon forever. The door you used to enter here is blocked by a stone outside, the door behind me will be blocked too, besides there are also sturdy bars protecting it. This is it, there is no way out except for these two doors\nWhat the... I locked all the doors!";
				link.l1 = "What's going on...";
				link.l1.go = "exit";
				AddDialogExitQuest("Mtraxx_RetributionEnricoAndTonzag");
			}
			else
			{
				dialog.text = "No, Charlie Prince. Don't grab for your weapon, it's pointless... I could kill you easily, however quick death is not enough for a bastard like you. You will stay in this dungeon forever. The door you used to enter here is blocked by a stone outside, the door behind me will be blocked too, besides there are also sturdy bars protecting it. This is it, there is no way out except for these two doors\nThere is water below, so you will have enough time to think about your deeds. All alone here, in the darkness, perhaps, you will repent what you have done before you starve to the death or go insane\nOne last thing - the treasure below is a fake. Golden ingots are nothing but a colored lead. Doubloons are real though, but there are only few of them enough to cover rocks inside chests. A worthy end for pirates, huh? You killed each other for a fake treasure, Prince. Farewell now. Pray for your sinner soul, Charlie Prince, if you still remember how...";
		// belamour legendary edition -->
				link.l1 = "I just killed the entire vanguard of Marcus Tyrex! You think these rusty bars will stop me?! I'll break it with your own head!";
				link.l1.go = "enrico_5a";
				link.l2 = "Maybe I deserved it. But I won't give up, you hear?! I will find a way, I always do!";
				link.l2.go = "enrico_5b";
			}
		break;
		
		case "enrico_5a":
			AddCharacterHealth(pchar, 5);
			AddCharacterExpToSkill(pchar, "FencingL", 400);
			AddCharacterExpToSkill(pchar, "FencingS", 400);
			AddCharacterExpToSkill(pchar, "FencingH", 400);
			AddCharacterExpToSkill(pchar, "Pistol", 400);
            DialogExit();
			AddDialogExitQuestFunction("Mtraxx_RetributionEnricoGo");
		break;
		
		case "enrico_5b":
			AddCharacterExpToSkill(pchar, "Leadership", 1200);
			ChangeCharacterComplexReputation(pchar, "nobility", 15);
            DialogExit();
			AddDialogExitQuestFunction("Mtraxx_RetributionEnricoGo");
		break;
		// <-- legendary edition
		
		case "enrico_Tonzag_1":
			dialog.text = "You're right, the door is reliable, even if old. Thanks for not lowering the gate-it would've delayed me. But not for long.";
			link.l1 = "Hercule Tonzag, Bald Gaston! I should have guessed that someone like you would side with the Prince and all his ilk. Lucky me to meet you here, too.";
			link.l1.go = "enrico_Tonzag_2";
			sld = CharacterFromID("Zorro");
			CharacterTurnToLoc(sld, "quest", "door");
		break;
		
		case "enrico_Tonzag_2":
			dialog.text = "Lucky, you say? Well, if you're in a hurry to die... Although I thought you weren't, seeing as you left him to starve instead of facing him.";
			link.l1 = "Accusing me of cowardice? How foolish of you. As I told the Prince, death is too easy a punishment for him. He's no match for me.";
			link.l1.go = "enrico_Tonzag_3";
		break;
		
		case "enrico_Tonzag_3":
			dialog.text = "And you're no match for me, Don.";
			link.l1 = "Ten years ago? Certainly. Now? Hardly. Moreover...";
			link.l1.go = "enrico_Tonzag_4";
		break;
		
		case "enrico_Tonzag_4":
			dialog.text = "Moreover what? What's with the dramatic pause? Though, considering your carnival mask... A little early to count me out, isn't it?";
			link.l1 = "You broke the door, but brute force alone won't suffice with me. How are your reflexes? Your vision? With one eye only. I still have both.";
			link.l1.go = "enrico_Tonzag_5";
		break;
		
		case "enrico_Tonzag_5":
			dialog.text = "Well, for now, anyway. Heh-heh.";
			link.l1 = "For Porto Bello, you deserve worse torment than the Prince!";
			link.l1.go = "enrico_Tonzag_6";
		break;
		
		case "enrico_Tonzag_6":
			dialog.text = "Oh, so you've heard what I did? Guess they'll keep gossiping about it among your lot for a while. Then you know what I've been through.";
			link.l1 = "You`re old, Tonzag, and this time your arrogance will be your downfall. And yes, I didn't just hear about it - Cartagena, Merida are your handiwork. Much like Porto Bello.";
			link.l1.go = "enrico_Tonzag_7";
		break;
		
		case "enrico_Tonzag_7":
			dialog.text = "Would've taken it as flattery, but no, not my doing. Though it may look similar, from afar. Too amateurish. Then again, even in Porto Bello, there were... incidents.";
			link.l1 = "Incidents?! That day, one person died... And considering you started that massacre, I still blame you for it, even if you didn't kill everyone yourself. I blame you for every 'incident.'";
			link.l1.go = "enrico_Tonzag_8";
		break;
		
		case "enrico_Tonzag_8":
			dialog.text = "One person, you say... Many died that day. Be specific.";
			link.l1 = "Truly, you have no heart if you can say that! But I'll answer: the one you should not have killed. My father, Don de la Vega. Were he alive, I wouldn't have taken this path, and you all would still be alive.";
			link.l1.go = "enrico_Tonzag_9";
		break;
		
		case "enrico_Tonzag_9":
			dialog.text = "Shut your mouth, whelp. My dear wife... also died there.";
			link.l1 = "Expecting condolences? You won't get them. That's Lord`s punishment for you. Seems like you do have a heart - tiny and black. And I'll find it with my blade.";
			link.l1.go = "enrico_Tonzag_10";
		break;
		
		case "enrico_Tonzag_10":
			dialog.text = "Oh, the dramatics about my heart. You're mistaken if you think you've seen worse than I have.";
			link.l1 = "Do you think I'm just a spoiled rich youth squandering money? Know this: I've spent not a doubloon on gambling or women! I've thrown it all into the fight against the likes of you and devoted my life to it!";
			link.l1.go = "enrico_Tonzag_11";
		break;
		
		case "enrico_Tonzag_11":
			dialog.text = "And for what? Doesn't seem very successful. Trade routes are still teeming with pirates. You're alone in your crusade. And they're a whole legion.";
			link.l1 = "Someone has to. At least someone. And maybe, by killing just one pirate captain, I'll save a few lives.";
			link.l1.go = "enrico_Tonzag_12";
		break;
		
		case "enrico_Tonzag_12":
			dialog.text = "Foolish. Idealistic. And... in a way, noble, I'd say, if not for your methods. Dishonorable, like your enemies. In the end, you're... no better.";
			link.l1 = "Don't you preach to me! Honor is for those who follow its laws. I understand you. I think like you. And I punish.";
			link.l1.go = "enrico_Tonzag_13";
		break;
		
		case "enrico_Tonzag_13":
			dialog.text = "You're right. Teaching you is pointless. So, we won't part peacefully. But I couldn't care less about you, Don Enrico. You're not even worth my time.";
			link.l1 = "What do you mea...";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionEnricoAndTonzag2");
		break;
		
		case "enrico_Tonzag_14": // после выстрела в Зорро в подземелье
            dialog.text = "Are you all right, Captain? I warned you to be careful. Should've listened to my gut feeling.";
			link.l1 = "Yeah, I'm fine. Thanks, Hercule. Just a bit...";
			link.l1.go = "enrico_Tonzag_15";
		break;
		
		case "enrico_Tonzag_15":
            dialog.text = "...shocked? Don't be afraid to admit it - it's normal for someone your age and in a situation like this. Besides, that Don is a good manipulator.";
			link.l1 = "Uh-huh. Though, he seemed afraid of you. That surprised me. But it also brought me back to my senses. By the way, is he still alive? Seems so. You shouldn't be standing with your back to him.";
			link.l1.go = "enrico_Tonzag_16";
		break;
		
		case "enrico_Tonzag_16":
            dialog.text = "Alive, but stunned. Coming to his senses. Should've aimed for the head, not the torso - turns out our noble hidalgo is wearing a light but sturdy cuirass under his coat. Heh, even Fleetwood stuck to a simple pourpoint. Otherwise, there'd already be a pool of blood here.";
			link.l1 = "And how did you end up here? Same place as him?";
			link.l1.go = "enrico_Tonzag_17";
		break;
		
		case "enrico_Tonzag_17":
            dialog.text = "No time for that now. He'll be back on his feet soon. For now, we'll lift this gate.";
			link.l1 = "We... what?? Sure, you might be Hercules, but...";
			link.l1.go = "enrico_Tonzag_18";
		break;
		
		case "enrico_Tonzag_18":
            dialog.text = "Men of my youth were forged tough. These hinges have short pins. Come on, give me a hand, Captain - I might be Hercules, but I'm getting on in years.";
			link.l1 = "All right, on three! And lift!";
			link.l1.go = "enrico_Tonzag_19";
		break;
		
		case "enrico_Tonzag_19":
            DialogExit();
			locCameraSleep(true);
			LAi_FadeLong("Mtraxx_RetributionEnricoAndTonzag6", "");
		break;
		
		case "enrico_Tonzag_20": // окружили Зорро
            dialog.text = "Do you think you've ruined all my plans and won? That was unexpected, of course, but I've still accounted for a lot!";
			link.l1 = "Like that light cuirass under your clothes. Why that and not a full one on top? Just to flaunt your coat?";
			link.l1.go = "enrico_Tonzag_21";
		break;
		
		case "enrico_Tonzag_21":
            dialog.text = "I'm no maiden, Prince. My reasons are purely practical - a full cuirass restricts my movement too much. Everyone has their own approach.";
			link.l1 = "Yet here I am, a Frenchman, already accustomed to wearing cuirasses, unlike a Spaniard. The irony. So, what now? You couldn't trap us. You've prepared for everything... Did a duel figure into the possibilities? Or is the blade - and even the cuirass - for everything except real fights?";
			link.l1.go = "enrico_Tonzag_22";
		break;
		
		case "enrico_Tonzag_22":
            dialog.text = "Are you trying to call me a coward as well? As I said, you deserve long suffering, not death in a duel. What's the point if your souls won't have time to endure and comprehend all your sins here, on Earth?";
			link.l1 = "The road to hell is paved with good intentions, as they say... And wouldn't tormenting your victims tarnish your own soul?";
			link.l1.go = "enrico_Tonzag_23";
		break;
		
		case "enrico_Tonzag_23":
            dialog.text = "Never. Not ever. For I remain true to myself and my principles.";
			link.l1 = "Aha, not like us. You've said so much about how we're vile scum without a shred of honor, so... why not live up to your expectations? We'll deal with you ourselves. Together.";
			link.l1.go = "enrico_Tonzag_24";
			link.l2 = "I have a proposition for you, Don Enrico. I challenge you to a duel, here and now. As a noble to a noble.";
			link.l2.go = "enrico_Tonzag_26";
		break;
		
		case "enrico_Tonzag_24":
            dialog.text = "Hm-m. You wouldn't stand a chance otherwise. Tonzag will be tricky, of course... So I'll take care of you first.";
			link.l1 = "As if he'd let you do that.";
			link.l1.go = "enrico_Tonzag_25";
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;
		
		case "enrico_Tonzag_25":
            DialogExit();
			EndQuestMovie();
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Tonzag");
			LAi_SetImmortal(sld, false);
			LAi_SetCheckMinHP(sld, 1, true, "TonzagRanen");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			sld = CharacterFromID("Zorro");
			LAi_SetImmortal(sld, false);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "Mtraxx_RetributionEnricoAndTonzag7");
		break;
		
		case "enrico_Tonzag_26":
            dialog.text = "You? A noble? Perhaps you're a “prince,” but I doubt there's a drop of noble blood in you.";
			link.l1 = "You revealed your true name to me. I'll reveal mine. I am Charles de Maure. And we've insulted each other's honor enough that each of us has the right to demand satisfaction. Defend yourself, Don Enrico.";
			link.l1.go = "enrico_Tonzag_27";
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			AddCharacterExpToSkill(pchar, "Leadership", 300);
		break;
		
		case "enrico_Tonzag_27":
            dialog.text = "But don't regret your decision later.";
			link.l1 = "I've regretted many decisions in my life, but this won't be one of them. En garde!";
			link.l1.go = "enrico_Tonzag_28";
		break;
		
		case "enrico_Tonzag_28":
			DialogExit();
			EndQuestMovie();
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Tonzag");
			LAi_SetImmortal(sld, true);
			LAi_SetActorType(sld);
			
			sld = CharacterFromID("Zorro");
			LAi_SetImmortal(sld, false);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "Mtraxx_RetributionEnricoAndTonzag7");
		break;
		
		case "enrico_Tonzag_29": // после победы над Зорро
            dialog.text = "Are you all right, Captain? Our noble hidalgo wasn't just wearing a cuirass - he also poisoned his blade. Here, take this. I always carry a couple with me when walking through the jungle - you never know when a snake might bite or a red-skin might throw a poisoned dart.";
			link.l1 = "Thanks, Hercule. I'm fine. Your timely arrival helped me pull myself together.";
			link.l1.go = "enrico_Tonzag_30";
			GiveItem2Character(PChar, "potion3");
			LAi_UseAtidoteBottle(pchar);
			LAi_UseAtidoteBottle(npchar);
		break;
		
		case "enrico_Tonzag_30":
            dialog.text = "Don't mention it. Let's go, I'll get you out of here - he mentioned blocking the entrance with stones. I found another passage, a shortcut.";
			link.l1 = "Tell me, Hercule... what exactly happened in Porto Bello? And when?";
			link.l1.go = "enrico_Tonzag_31";
		break;
		
		case "enrico_Tonzag_31":
            dialog.text = "I'm not in the mood to talk about it today. But maybe someday, over a glass of wine or something stronger. For now, let's get out of here - the brat was right, I am getting old. I want to rest on the ship.";
			link.l1 = "Then lead the way.";
			link.l1.go = "enrico_Tonzag_32";
		break;
		
		case "enrico_Tonzag_32":
            DoQuestReloadToLocation("Shore10", "goto", "goto2", "Mtraxx_RetributionEnricoAndTonzag8");
		break;
		
		case "mishelle_sleep":
            dialog.text = "Tell me, brother - how did you turn into such abomination? When I told you to get familiar with pirates, I didn't mean burning cities, killing innocent civilians and torturing women. Even a war can be fought with honor and dignity\nYou are a shame of our family. It's good our father is not here: he would have died of shame knowing his son had become a pirate and bandit!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep5");
		break;
		
		case "mishelle_sleep_1":
            dialog.text = "Brother! Brother!\nCan you hear me?\nThere is a passage behind one of two doors. The door can be opened. A key is close to you!\nFind it on the stairs. On the stairs!..";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep7");
		break;
		
		case "terrax_sleep":
            dialog.text = "Ha-ha-ha, hello there my brave cutthroat! Why are you so sad? The sea, gold, rum and women - what else do you lack? Remember our first meeting? I told you back then - I need men who don't fear the smell of gunpowder or to bleed the red rivers dry. You have over exceed my every hope! You have become a real pirate, Charlie Prince! Ha-ha-ha!";
			link.l1 = "";
			link.l1.go = "terrax_sleep_1";
			locCameraSleep(false);
		break;
		
		case "terrax_sleep_1":
            dialog.text = "A real fucking pirate! Ah-ah-ha-ha!";
			link.l1 = "";
			link.l1.go = "terrax_sleep_2";
		break;
		
		case "terrax_sleep_2":
			Mtraxx_RetributionSleepSkeletons();
            dialog.text = "Ua-ha-ha-ha-ha-ha!!!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep6");
		break;

		// belamour legendary edition -->
		case "SlavesTrader":
            dialog.text = "Who are you? What are you doing here? Answer quickly!";
			link.l1 = "I'm from Fadey, I came for a batch of black bones. He should have warned you.";
			link.l1.go = "SlavesTrader_1";
		break;
		
		case "SlavesTrader_1":
            dialog.text = "Hah! Don't sweat the skin, friend. We recognized you, Moscovit gave a description in great detail. He also asked not to be offended by the price. So, taking into account the advance payment already made from you 10 000 silver. Or, if you pay in gold, then only 50 doubloons. Well, what did you decide? Don't pull the cat's tail!";
			if(PCharDublonsTotal() >= 50)
			{
				link.l1 = "I will pay 50 doubloons. It's more profitable.";
				link.l1.go = "SlavesTrader_Dub";
			}
			if(sti(Pchar.money) >= 10000)
			{
				link.l2 = "I will pay 10 000 pesos.";
				link.l2.go = "SlavesTrader_P";
			}
			link.l3 = "I'm sorry, but I can't afford slaves right now.";
			link.l3.go = "SlavesTrader_X";
		break;
		
		case "SlavesTrader_Dub":
			RemoveDublonsFromPCharTotal(50);
            dialog.text = "That is great. Signal your men to take the goods.";
			link.l1 = "Certainly.";
			link.l1.go = "SlavesTrader_End";
		break;
		
		case "SlavesTrader_P":
			AddMoneyToCharacter(pchar, -10000);
            dialog.text = "That is great. Signal your men to take the goods.";
			link.l1 = "Certainly.";
			link.l1.go = "SlavesTrader_End";
		break;
		
		case "SlavesTrader_End":
			DialogExit();
			AddQuestRecord("Roger_3", "25");
            pchar.questTemp.Mtraxx.GiveMeSlaves = "Deal";
			SetCharacterGoods(pchar, GOOD_SLAVES, (GetCargoGoods(pchar, GOOD_SLAVES) + 50));
			Log_Info("Fifty slaves shipped to "+PChar.Ship.Name);
			for(i=1; i<=3; i++)
			{
				sld = characterFromId("Mtraxx_SlavesSeller"+i);
				ChangeCharacterAddressGroup(sld, "none", "", "");
				sld.lifeday = 0;
			}
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation("Shore29")], false); 
			DeleteAttribute(&locations[FindLocation("Shore29")],"DisableEncounters"); //энкаунтеры открыть
		break;
		
		case "SlavesTrader_X":
            dialog.text = "Well as you wish. There will always be a buyer for this product. See you, friend.";
			link.l1 = "Goodbye.";
			link.l1.go = "SlavesTrader_EndX";
		break;
		
		case "SlavesTrader_EndX":
			DialogExit();
			AddQuestRecord("Roger_3", "26");
			pchar.questTemp.Mtraxx.GiveMeSlaves = "WithoutSlaves";
			for(i=1; i<=3; i++)
			{
				sld = characterFromId("Mtraxx_SlavesSeller"+i);
				ChangeCharacterAddressGroup(sld, "none", "", "");
				sld.lifeday = 0;
			}
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation("Shore29")], false); 
			DeleteAttribute(&locations[FindLocation("Shore29")],"DisableEncounters"); //энкаунтеры открыть
		break;
		// диалог Гаспара Златозубого Xenon
		case "GasparGold_meeting":
            dialog.text = "Greetings, Captain. You are Charlie Prince if I'm not mistaken? Don't worry, my walls have no ears. Honestly, I don't care what your name is. What matters is that you were recommended to me, which means we can do business.";
			link.l1 = "Greetings to you too, Gaspard ‘Goldentooth.' Then again, I don't really care what you're called either. I heard you might be interested in buying some trinkets?";
			link.l1.go = "GasparGold_meeting_01";
		break;
		
		case "GasparGold_meeting_01":
            dialog.text = "That's correct. No one will offer you a better price than me. Well, except maybe the pawnbrokers, but they don't buy much. I'm ready to buy everything you offer. You don't even have to carry the valuables to me personally: I have a back door leading to a secluded pier. Feel free to sell me all the trinkets you've got stored in the chests on your ship.";
			link.l1 = "Well, that's excellent! Glad to make your acquaintance.";
			link.l1.go = "GasparGold";
		break;
		
		case "GasparGold_story":
			npchar.mtraxx.story = true;
            dialog.text = "Now that's my personal business. I'd prefer you not to pry into it. I'll just say that I've got everything under control, so you can trade with me risk-free. The rest is none of your concern.";
			link.l1 = "Well, risk-free is what matters the most! There's something else I wanted to ask...";
			link.l1.go = "GasparGold";
		break;
		
		case "GasparGold":
			NextDiag.TempNode = "GasparGold";
            dialog.text = "How can I help? Want to get rid of some extra pearls or jems? Maybe gold, silver, jewelry? I'll buy it all.";
			if(!CheckAttribute(npchar,"mtraxx.story"))
			{
				link.l1 = "Say, what's it like being a buyer of stolen goods? Aren't you afraid of the authorities?";
				link.l1.go = "GasparGold_story";
			}
			link.l2 = "I've got something here... I want to exchange it for some hard coin.";
			link.l2.go = "GasparGold_01";
		break;
		
		case "GasparGold_01":
            dialog.text = "Well, let's make the exchange. Doubloons or pesos?";
			link.l1 = "Let's go with pesos - no need for doubloons. Regular money is widely accepted everywhere.";
			link.l1.go = "GasparGold_peso";
			link.l2 = "You guessed it - I specifically need doubloons. So I'll only be selling for them.";
			link.l2.go = "GasparGold_dub";
			link.l3 = "I don't have anything for sale right now. I just wanted to make sure you're ready to buy precious items when I have them. Until next time!";
			link.l3.go = "exit";
		break;
		
		// окно торговли
		case "GasparGold_peso":
            Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
			LaunchItemsTrade(NPChar, 0);
		break;
		
		case "GasparGold_dub":
            Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
			LaunchItemsTrade(NPChar, 1);
		break;
		
		// Диалоги после угроз вождю индейцев Кумване
		case "MeridaObsuzhdenie_Bad_1":
            dialog.text = "Have you still resorted to intimidation, Cap? I heard threats even from outside.";
			link.l1 = "They left me no choice. I offered this Tagofa's wife gifts for his help. She wouldn't even listen to me. Now let the chief talk to them. And if he fails to bring these stubborn fellows to their senses, I'll tear his heart out of his chest with my own hands. And by the way, who is Yahahu?";
			link.l1.go = "MeridaObsuzhdenie_Bad_2";
			ChangeShowIntarface();
		break;
		
		case "MeridaObsuzhdenie_Bad_2":
            dialog.text = "You shouldn't have spoiled relations with the Indians. We pirates have only a sword and a ship as allies. But since this is your decision, then so be it. And Yahahu is an evil demon. I don't know anything else about him.";
			link.l1 = "...";
			link.l1.go = "MeridaObsuzhdenie_Bad_3";
		break;
		
		case "MeridaObsuzhdenie_Bad_3":
            StartInstantDialog("Mrt_Rocur", "MeridaObsuzhdenie_Bad_4", "Quest\Roger.c");
		break;
		
		case "MeridaObsuzhdenie_Bad_4":
            dialog.text = "Wasting time on persuasion, Leprechaun - it's unwise. Or would you prefer to give up the rich booty and maintain good relations with the Indians?";
			link.l1 = "...";
			link.l1.go = "MeridaObsuzhdenie_Bad_5";
		break;
		
		case "MeridaObsuzhdenie_Bad_5":
            StartInstantDialog("Lepricon", "MeridaObsuzhdenie_Bad_6", "Quest\Roger.c");
		break;
		
		case "MeridaObsuzhdenie_Bad_6":
            dialog.text = "I'd prefer to get both.";
			link.l1 = "It won't work to have a foot in both camps. Not this time. Enough arguing, everything has already been done. Tomorrow the chief will inform us of Tagofa's decision, and I hope he will not disappoint me. Otherwise... I will have to take extreme measures. Which I would like to avoid, of course.";
			link.l1.go = "MeridaObsuzhdenie_Bad_7";
		break;
		
		case "MeridaObsuzhdenie_Bad_7":
			DialogExit();
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "GenQuest.CannotWait"); //разрешить отдыхать
			ChangeShowIntarface();
			
            sld = characterFromId("Lepricon");
			sld.dialog.Filename = "Quest\Roger.c";
			sld.dialog.currentnode = "lepricon_3";
			LAi_SetWarriorType(sld);
			
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
		break;
		
		case "MeridaObsuzhdenie_Good_1":
            dialog.text = "Well, how are things going? Will we have a guide?";
			link.l1 = "No, Jean, we won't. The chief and the entire tribe fear the Kapongs like the devil fears incense. It looks like we'll have to abandon our plan.";
			link.l1.go = "MeridaObsuzhdenie_Good_2";
			ChangeShowIntarface();
		break;
		
		case "MeridaObsuzhdenie_Good_2":
            StartInstantDialog("Lepricon", "MeridaObsuzhdenie_Good_3", "Quest\Roger.c");
		break;
		
		case "MeridaObsuzhdenie_Good_3":
            dialog.text = "Terrax won't be happy about this turn of events.";
			link.l1 = "Do you think I'm incredibly happy that things turned out this way? The cowardly Lokono don't want to mess with the Kapongs. They're not tempted by either persuasion or rewards.";
			link.l1.go = "MeridaObsuzhdenie_Good_4";
		break;
		
		case "MeridaObsuzhdenie_Good_4":
            StartInstantDialog("Mrt_Rocur", "MeridaObsuzhdenie_Good_5", "Quest\Roger.c");
		break;
		
		case "MeridaObsuzhdenie_Good_5":
            dialog.text = "Then we'll have to use threats. Tell them that you'll burn their damned village to the ground and torture those who survive until someone agrees to lead us.";
			link.l1 = "Jean, have you completely lost your mind? I'm not going to burn down the homes of innocent people. And certainly not torture them.";
			link.l1.go = "MeridaObsuzhdenie_Good_6";
		break;
		
		case "MeridaObsuzhdenie_Good_6":
            dialog.text = "Charles Prince is a model of benefactor. I never expected such outbursts of tenderness from you.";
			link.l1 = "This is not tenderness, Handsome. Well, we'll torture some Indian half to death. Out of revenge, he'll lead us straight into the hands of the Kapongs and he'll disappear along paths known only to him. I won't risk the lives of my people like that.";
			link.l1.go = "MeridaObsuzhdenie_Good_7";
		break;
		
		case "MeridaObsuzhdenie_Good_7":
            dialog.text = "In that case, Leprechaun and I are leaving. Here's fifty thousand silver for freeing me from the Maracaibo plantations. I was saving it for a new ship. And my advice to you: stay out of Marcus' sight for a while. Goodbye, Charles Prince.";
			link.l1 = "Goodbye, Jean.";
			link.l1.go = "MeridaObsuzhdenie_Good_8";
			AddMoneyToCharacter(pchar, 50000);
		break;
		
		case "MeridaObsuzhdenie_Good_8":
            DialogExit();
			chrDisableReloadToLocation = false;
			ChangeShowIntarface();
			AddQuestRecord("Roger_5", "8b");
			CloseQuestHeader("Roger_5");
			
			sld = characterFromId("Lepricon");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "", "", "", "", -1);
			sld.location = "None";
			RemovePassenger(pchar, sld);
			
			sld = characterFromId("Mrt_Rocur");
			LAi_type_actor_Reset(sld);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "", "", "", "", -1);
			sld.location = "None";
			RemovePassenger(pchar, sld);
			
			sld = characterFromId("Terrax");
			sld.dialog.currentnode = "First time";
		break;
		
		// Немезида. Диалоги с офицерами после взрыва бочонков с порохом
		// Тонзаг
		case "Nemezida_Tonzag_1":
            dialog.text = "Everyone from the area will be rushing here now! Are you sure blowing up those trees was a good idea, Captain?";
			link.l1 = "Damn! Maybe it would've been better if everyone worked with axes... But it's too late for that now.";
			link.l1.go = "Nemezida_Tonzag_2";
		break;
		
		case "Nemezida_Tonzag_2":
            dialog.text = "True. We'll have to deal with what we've got. Get ready.";
			link.l1 = "You too, Hercule.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Tonzag_3":
            dialog.text = "They're still coming this way. So, should we deal with these too?";
			link.l1 = "What if there's no end to them? We're not here for this kind of trouble.";
			link.l1.go = "Nemezida_Tonzag_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Tonzag_4":
            dialog.text = "Well, everything has an end... But you're right. Let's retreat. And quickly.";
			link.l1 = "Let's hurry!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Tonzag_5":
            dialog.text = "So relentless, they've caught up with us. There's a path here, should we go in? It'll be easier to hold the line.";
			link.l1 = "Wait, Hercule. Do you hear that? There's someone already in there. You and the guys handle things here. I'll go inside, before they take the treasure - I doubt anyone stumbled in there randomly.";
			link.l1.go = "Nemezida_Tonzag_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Tonzag_6":
            dialog.text = "Alright. But be careful, I have a bad feeling about this.";
			link.l1 = "You too! I'm going over there.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
		
		case "Nemezida_Tonzag_7": // на берегу
            dialog.text = "You want to say something, Captain? You've been deep in thought our entire walk to the ship.";
			link.l1 = "That's right. I've been thinking about what I've been doing recently. About Terrax and... where it's led me. Have I come any closer to saving my brother? Or going home?..";
			link.l1.go = "Nemezida_Tonzag_8";
		break;
		
		case "Nemezida_Tonzag_8":
            dialog.text = "Hm-m. Good questions. And what are your answers?";
			link.l1 = "Just another question. If it was pointless before, will it be pointless again? Terrax won't help me. Not with my brother, nor Tortuga.";
			link.l1.go = "Nemezida_Tonzag_9";
		break;
		
		case "Nemezida_Tonzag_9":
            dialog.text = "Probably not. He has no use for that. Surprising you've only just realized it. But what's your next question?";
			link.l1 = "Why the hell was I running after Terrax like a lapdog, pulling chestnuts out of the fire for him all this time?!";
			link.l1.go = "Nemezida_Tonzag_10";
		break;
		
		case "Nemezida_Tonzag_10":
            dialog.text = "Now, that's a good question. A proper one. Do you have an answer this time?";
			link.l1 = "More like a resolution. I was lucky today. But will I be lucky again? It's important to know when to stop. And... to respect yourself. I've had enough.";
			link.l1.go = "Nemezida_Tonzag_11";
		break;
		
		case "Nemezida_Tonzag_11":
            dialog.text = "Decided to end your partnership with Terrax?";
			link.l1 = "Yes. I have more important things to do. Family, friends. With them, I'll achieve my goals. And not in this way. And even if I do... it won't be with Marcus. I'll be my own master. I'll make my own decisions.";
			link.l1.go = "Nemezida_Tonzag_12";
		break;
		
		case "Nemezida_Tonzag_12":
            dialog.text = "The man I once followed is speaking again. Don't get tangled up with the wrong people again. Don't waste the potential that once intrigued me.";
			link.l1 = "Got it, Hercule. And thanks again. This time, for helping me fully realize it. I'm no longer the Prince, a lackey. I'm Charles de Maure, a proud nobleman. Let's board the ship - we're both tired.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionFinal_Tonzag");
		break;
		
		// Книппель
		case "Nemezida_Knippel_1":
            dialog.text = "That was one heck of a blast, sir - knippel to my stern! Sounded just like a broadside from the Valkyrie. But I'm afraid those fellows over there noticed it too...";
			link.l1 = "If they noticed, that's their problem. Nobody invited them here. Ready to teach them a lesson, Charlie?";
			link.l1.go = "Nemezida_Knippel_2";
		break;
		
		case "Nemezida_Knippel_2":
            dialog.text = "Always ready, sir!";
			link.l1 = "Excellent. Let's get to it.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Knippel_3":
            dialog.text = "I'm afraid we're about to have more company, Captain. What are your orders?";
			link.l1 = "We'll head deeper into the jungle and hide - there's no way to fend them all off, and we're not here for that anyway.";
			link.l1.go = "Nemezida_Knippel_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Knippel_4":
			PlaySound("VOICE\English\hambit\Charlie Knippel-05.wav");
            dialog.text = "Aye, sir.";
			link.l1 = "Then let's move out!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Knippel_5":
            dialog.text = "They've tracked us down, Captain! But we can take shelter here - looks like this path leads somewhere, though I think there's already someone there.";
			link.l1 = "We're not taking shelter! Seems someone else caught wind of the treasure. Here's the plan: I'll go see what's happening before they make off with it all, and you hold them off here with the lads!";
			link.l1.go = "Nemezida_Knippel_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Knippel_6":
			PlaySound("VOICE\English\hambit\Charlie Knippel-05.wav");
            dialog.text = "Yes, sir.";
			link.l1 = "Excellent. I'm heading down now! I trust you'll handle things here.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
		
		case "Nemezida_Knippel_7": // на берегу
            dialog.text = "Khe-khe... Are you... alright, sir?";
			link.l1 = "Charlie! You've chosen the perfect time to worry about me. Save your words. Are you holding up? I should have left you on the ship and taken more men instead...";
			link.l1.go = "Nemezida_Knippel_8";
		break;
		
		case "Nemezida_Knippel_8":
            dialog.text = "Ah, just a scratch, sir. A bit tired. Never fought like that, not even in my younger days! But I gave them such a beating they'll be hearing knippels for eternity!";
			link.l1 = "Royal Navy, old school! Seems like you fought like a lion, Charlie. But still, you can barely stand. Don't bluff - how bad is the wound?";
			link.l1.go = "Nemezida_Knippel_9";
		break;
		
		case "Nemezida_Knippel_9":
            dialog.text = "It's nothing serious, Captain, just exhaustion. The entrance behind you collapsed almost immediately, and we kept fending off all those men for ages. In the end, I was left alone, wounded. So, I made my way here to clear the path and get some first aid.";
			link.l1 = "I see. Well, you did your part today. As for me... I failed. We were all deceived and set against each other for someone's amusement-there wasn't even any treasure. And I wasn't the only fool there.";
			link.l1.go = "Nemezida_Knippel_10";
		break;
		
		case "Nemezida_Knippel_10":
            dialog.text = "You failed?.. But you're alive, sir. What happened? Did you escape?";
			link.l1 = "No, but there was still some running involved. Sorry, old friend, but what happened in there, I won't tell anyone - not even my closest friends. However, I've made the necessary conclusions.";
			link.l1.go = "Nemezida_Knippel_11";
		break;
		
		case "Nemezida_Knippel_11":
            dialog.text = "What kind of conclusions, sir? I don't always understand your reasoning. My philosophy is simple - a good culverin and knippels at the mast.";
			link.l1 = "Tell me, you must have killed Spaniards before, as I recently did. Back in your Royal Navy days. And later, with Fleetwood.";
			link.l1.go = "Nemezida_Knippel_12";
		break;
		
		case "Nemezida_Knippel_12":
            dialog.text = "I did. Spaniards, Dutchmen-a lot of others too. As Dick once told me, our service is dangerous and demanding. But why are you asking? What's your point?";
			link.l1 = "I'll explain. But first, another question. Did you ever doubt what you were doing and why you were doing it, Charlie?";
			link.l1.go = "Nemezida_Knippel_13";
		break;
		
		case "Nemezida_Knippel_13":
            dialog.text = "Hm-m. I told myself I was acting for the good of the Crown. Worrying about orders is a thankless job - you have to follow them anyway.";
			link.l1 = "The Crown... Well, you had your reasons. I didn't even have that - Michel told me to get close to Terrax. But was it worth all the sacrifices? Did it help me or him? Yes, yes, we don't like dons... but we're all human.";
			link.l1.go = "Nemezida_Knippel_14";
		break;
		
		case "Nemezida_Knippel_14":
            dialog.text = "I think I'm starting to understand what you're getting at, sir.";
			link.l1 = "Good. Tell me, when Fleetwood left, were you glad you no longer had to fire on Dutch merchants? Some of them were honest people.";
			link.l1.go = "Nemezida_Knippel_15";
		break;
		
		case "Nemezida_Knippel_15":
            dialog.text = "I never thought about it, Captain. But I'll say this - I've always enjoyed serving with you, sir. May I be damned with a knippel around my neck if I'm lying!";
			link.l1 = "Ha-ha-ha, alright. But tell me this - who do you think had it worse? You, following orders? Or me, who wasn't forced to do what I did?";
			link.l1.go = "Nemezida_Knippel_16";
		break;
		
		case "Nemezida_Knippel_16":
            dialog.text = "I don't know, sir...";
			link.l1 = "Neither do I. But it doesn't matter. What matters is that I no longer want anything to do with Terrax. Enough is enough. No more Charlie Prince. Only Charles de Maure.";
			link.l1.go = "Nemezida_Knippel_17";
		break;
		
		case "Nemezida_Knippel_17":
            dialog.text = "But wasn't this part of your plan to save your brother?";
			link.l1 = "It was. But in the end, it didn't help me at all. So if I ever have to do something like that again - it will only be my decision. And only if it truly brings me closer to my goal.";
			link.l1.go = "Nemezida_Knippel_18";
		break;
		
		case "Nemezida_Knippel_18":
            dialog.text = "I hope you know what you're doing, Captain. And that you won't end up like Terrax. Or on a gallows.";
			link.l1 = "I hope so too. But what I am certain of is that my goals and interests will come first from now on. Now, let's take care of your wounds.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionFinal_Officers");
		break;
		
		// Лонгвэй
		case "Nemezida_Longway_1":
            dialog.text = "Your explosion draw attention, Lord Captain. An enemy squad seems to be approaching us.";
			link.l1 = "Damn it! ...You think there was a better way to deal with those trees? And what would you have done?";
			link.l1.go = "Nemezida_Longway_2";
		break;
		
		case "Nemezida_Longway_2":
            dialog.text = "I do not know. But I do know what to do now - deal with those people.";
			link.l1 = "Well, fair enough. I suppose that's exactly what we'll do.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Longway_3":
            dialog.text = "New people come, Lord Captain.";
			link.l1 = "Yes, I've noticed, thank you, Longway. But we don't have time for these ones, so let's retreat into the jungle - maybe they'll lose us.";
			link.l1.go = "Nemezida_Longway_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Longway_4":
            dialog.text = "Hmm, we could handle them, of course, but as you say.";
			link.l1 = "We don't need this fight, so let's move.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Longway_5":
            dialog.text = "They won't let up and will catch us, Lord Captain! I told you, we should've killed them earlier. Should we set up an ambush in that cave? Although it seems someone is already there.";
			link.l1 = "Better set up an ambush here with the lads! What I'm not going to miss is that treasure. Looks like someone else got wind of the hoard... So I'll go check it out myself.";
			link.l1.go = "Nemezida_Longway_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Longway_6":
            dialog.text = "Be cautious, Lord Captain. Remember, even a great dragon once died atop a mountain of gold.";
			link.l1 = "I'll keep that in mind, Longway. Let's all try not to die today.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
		
		case "Nemezida_Longway_7": // на берегу
            dialog.text = "Lord Captain, it seems your managed to escape from there.";
			link.l1 = "Surprised, Longway? Though I must admit, I'm somewhat surprised myself. Looks like you're the only one who made it out alive. But how did you manage?";
			link.l1.go = "Nemezida_Longway_8";
		break;
		
		case "Nemezida_Longway_8":
            dialog.text = "A pack of scrappy cats cannot defeat a tiger. A nest of snakes cannot bring down a dragon. Among white men, few are worthy opponents for mine.";
			link.l1 = "But remember, Longway, a pack of dogs can tear apart a lion.";
			link.l1.go = "Nemezida_Longway_9";
		break;
		
		case "Nemezida_Longway_9":
            dialog.text = "Now Lord Captain share his wisdom with Longway? Pity your didn't heed my advice earlier.";
			link.l1 = "About the dragon on the mountain of gold? True, I almost became one - nearly died, in fact. But not on a mountain of gold - there was none of that. What I found instead was something else, equally important.";
			link.l1.go = "Nemezida_Longway_10";
		break;
		
		case "Nemezida_Longway_10":
            dialog.text = "Next time, 'almost' might not happen. What did you find, Lord Captain?";
			link.l1 = "Yes, I see that now. What I found was... wisdom. Experience. Understanding. A decision. Tell me, Longway, what have we been doing lately?";
			link.l1.go = "Nemezida_Longway_11";
		break;
		
		case "Nemezida_Longway_11":
            dialog.text = "Our be pirates. Working for your new master, Lord Terrax. Smuggling, looting towns, killing, saving, and helping his people.";
			link.l1 = "He's not my master, you know. But damn it, you've described it all so perfectly! I forgot pride, self-respect, and followed him around like a lapdog.";
			link.l1.go = "Nemezida_Longway_12";
		break;
		
		case "Nemezida_Longway_12":
            dialog.text = "Longway understand you, Lord Captain. I too worked for van Merden and Rodenburg, forgetting honor, pride, and respect for the sake of a cherished goal.";
			link.l1 = "Tell me, do you condemn yourself for it? Do you hate yourself?";
			link.l1.go = "Nemezida_Longway_13";
		break;
		
		case "Nemezida_Longway_13":
            dialog.text = "Condemn? Sometimes. Hate? No. I know and remember who I am. I remember my goal, my guiding star. Nothing is more important in life. And do your have a goal?";
			link.l1 = "Not a guiding star like you, but still an important goal, yes - to rescue my brother. But I strayed from that goal. And that's something I can't afford to repeat.";
			link.l1.go = "Nemezida_Longway_14";
		break;
		
		case "Nemezida_Longway_14":
            dialog.text = "Let me share another piece of wisdom from the Celestial Empire with you. There are no wholly good or bad people. Each person possesses both Yin - darkness and ignorance - and Yang - light and wisdom. The balance shift within everyone.";
			link.l1 = "So, my Yang is Charles de Maure. And my Yin is Charlie Prince. Though perhaps even Charles de Maure will have to make dark and difficult decisions one day.";
			link.l1.go = "Nemezida_Longway_15";
		break;
		
		case "Nemezida_Longway_15":
            dialog.text = "That be life, Lord Captain. Every person is bound to make both dark and bright choices.";
			link.l1 = "Yet the mask of Prince almost fused with me. But I'll cast it off. Charles de Mort is a nobleman, not an errand boy. From now on, it will only be so. I reclaim my pride and dignity. From now on, I am my own master.";
			link.l1.go = "Nemezida_Longway_16";
		break;
		
		case "Nemezida_Longway_16":
            dialog.text = "Longway approve of your decision, Lord Captain.";
			link.l1 = "Thank you, Longway. By the way, don't you regret not being a free captain? Serving me, as you say, 'your master'?";
			link.l1.go = "Nemezida_Longway_17";
		break;
		
		case "Nemezida_Longway_17":
            dialog.text = "Hm-m. Longway miss commanding his own ship. But mine recognize your. For showing respect and wisdom to mine, unlike the typical white barbarian. Perhaps mine would like a different life. But mine do not regret helping your.";
			link.l1 = "I'm glad to hear that, Longway. Now... let's leave this place and the path of Yin. And bring more Yang into our lives. Did I get that right?";
			link.l1.go = "Nemezida_Longway_18";
		break;
		
		case "Nemezida_Longway_18":
            dialog.text = "Yes, that's correct. I hope your follow a much better Dao from now on.";
			link.l1 = "Dao?";
			link.l1.go = "Nemezida_Longway_19";
		break;
		
		case "Nemezida_Longway_19":
            dialog.text = "The Way, Lord Captain. Or the Essence. But in our case - the Way.";
			link.l1 = "Whatever my future path may hold, I won't stray again from what truly matters. Let's leave this place, Longway.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionFinal_Officers");
		break;
		
		// Тичингиту
		case "Nemezida_Tichingitu_1":
            dialog.text = "Captain Charles, many people coming this way. Your smoke signal has attracted them. And they're clearly not friends to us.";
			link.l1 = "Oh, if only it were just a 'smoke signal,' as you called it - it echoed through the entire jungle. There's no choice - let's defend ourselves. We definitely don't need a strike from behind by an entire squad.";
			link.l1.go = "Nemezida_Tichingitu_2";
		break;
		
		case "Nemezida_Tichingitu_2":
            dialog.text = "Yes, Captain Charles. Strike first!";
			link.l1 = "Attack! Don't spare the bullets!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Tichingitu_3":
            dialog.text = "More coming! Even more people.";
			link.l1 = "Retreat into the jungle, Tichingitu! We'll hide and wait it out. I came here for treasure, not for a fight!";
			link.l1.go = "Nemezida_Tichingitu_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Tichingitu_4":
            dialog.text = "If needed, we can set an ambush in the jungle.";
			link.l1 = "True enough. Now, let's move - quickly, but silently.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Tichingitu_5":
            dialog.text = "Captain Charles, look! There's a passage ahead. And I can hear footsteps and voices from there.";
			link.l1 = "Someone else found out about the treasure? Damn it! Do you hear that noise behind us too? Looks like they've caught up. Tichingitu! I'll go check what's ahead. You hold them off with the lads!";
			link.l1.go = "Nemezida_Tichingitu_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Tichingitu_6":
            dialog.text = "We try! You go!";
			link.l1 = "I'm counting on you!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
			
		case "Nemezida_Tichingitu_7": // на берегу
            dialog.text = "Captain Charles! You survive! Tichingitu be happy about this.";
			link.l1 = "Thank you, my friend. I'm happy too. I'm glad I survived, and that you're okay. Looks like you're the only one left from the whole squad. Were there many of them? You really held them off well.";
			link.l1.go = "Nemezida_Tichingitu_8";
		break;
		
		case "Nemezida_Tichingitu_8":
            dialog.text = "Many. But mine be one of the best warriors from our Maskog village. What happen to you there? Did you find the treasure you were looking for?";
			link.l1 = "No, Tichingitu. We were deceived - there was no treasure. Tell me, what do you think about what we've all been doing lately?";
			link.l1.go = "Nemezida_Tichingitu_9";
		break;
		
		case "Nemezida_Tichingitu_9":
            dialog.text = "What have we been doing, Captain Charles? Sail. Beat your enemies.";
			link.l1 = "It seems you don't understand me. Tell me then, are you sad about being exiled from your tribe? Do you want to go back, do you miss your brothers?";
			link.l1.go = "Nemezida_Tichingitu_10";
		break;
		
		case "Nemezida_Tichingitu_10":
            dialog.text = "Of course, I miss my friends and family. But go back? My home do not exist anymore without... her. Besides, there's that evil coyote, the shaman!";
			link.l1 = "I'm sorry, I didn't mean to bring that up. You know, I recently joined a tribe, so to speak. A tribe of captains like me. But in the end, I realized it was just a pack of jackals who think of themselves as sea wolves...";
			link.l1.go = "Nemezida_Tichingitu_11";
		break;
		
		case "Nemezida_Tichingitu_11":
            dialog.text = "And what happen? What do we do now?";
			link.l1 = "Good question. I almost became a jackal myself with those jackals. So, that's enough for me. My friends and my crew - that's my 'tribe.'";
			link.l1.go = "Nemezida_Tichingitu_12";
		break;
		
		case "Nemezida_Tichingitu_12":
            dialog.text = "Tichingitu is happy that you found your tribe, Captain Charles.";
			link.l1 = "Thanks, my friend. I needed to say that. You and I are both our own leaders and tribe. And now it's time to get back to really important matters.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionFinal_Officers");
		break;
		
		// Айронс
		case "Nemezida_Irons_1":
            dialog.text = "Someone's coming! And, judging by the sound of it, not to join us in celebrating Thanksgiving.";
			link.l1 = "Damn roots! Alright, we'll have to deal with these scoundrels now - better now than when we're hauling the treasure to the ship.";
			link.l1.go = "Nemezida_Irons_2";
		break;
		
		case "Nemezida_Irons_2":
            dialog.text = "You've got that right. Ready?";
			link.l1 = "You didn't have to ask. It's not like we have a choice.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Irons_3":
            dialog.text = "They're everywhere, like rats in London slums, Your Honor! What's the plan - should we hold our ground and shoot it out with the lads?";
			link.l1 = "Not now, fall back! We're here for the treasure, not to fight!";
			link.l1.go = "Nemezida_Irons_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Irons_4":
            dialog.text = "Heh, no objections here.";
			link.l1 = "Then pick up the pace!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Irons_5":
            dialog.text = "Hey, Captain, look - seems like this path leads somewhere. And it sounds pretty lively over there, judging by the noise!";
			link.l1 = "Could it be that someone else got wind of the treasure? Tommy, do you hear that? They've caught up with us. Alright, I'll head forward, and you all give them a proper welcome here!";
			link.l1.go = "Nemezida_Irons_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Irons_6":
            dialog.text = "Now I hear it! Whoever they are, you'd better hurry, he-he. Otherwise, what was the point of us trekking all the way out here?!";
			link.l1 = "Oh, I'd hate for that to be the case.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
		
		case "Nemezida_Irons_7": // на берегу
            dialog.text = "Ah, it's you, captain! Wow, you survived. I won't lie - I didn't expect it. But I'm glad, don't get me wrong, heh-heh.";
			link.l1 = "I didn't expect it either, I won't lie too. But the fact that you survived – I'm not surprised at all. Did you run away?";
			link.l1.go = "Nemezida_Irons_8";
		break;
		
		case "Nemezida_Irons_8":
            dialog.text = "You do me wrong! Tommy Irons never runs away! He just comes back for reinforcements. But it wasn't necessary – my guys and I handled it on our own, though, once again, I'm the only one who made it out alive, heh...";
			link.l1 = "Maybe this time you should have gone for reinforcements. But I... I ran away.";
			link.l1.go = "Nemezida_Irons_9";
		break;
		
		case "Nemezida_Irons_9":
            dialog.text = "You ran away? Heh, you've surprised me again. But I actually wanted to rush to you as soon as I was done! I'm better than any reinforcements, you know. It's just that...";
			link.l1 = "What's wrong, Tom?";
			link.l1.go = "Nemezida_Irons_10";
		break;
		
		case "Nemezida_Irons_10":
            dialog.text = "Damn, while I was messing around, the entrance behind you got blocked with rocks. I couldn't get through. It's even embarrassing that I took so long clearing it and couldn't help you there. I got a little lost by myself while finding my way back to get the guys and help move the rocks... By the time I got back, you were already back.";
			link.l1 = "Yeah, maybe I'll be ashamed to admit what happened to me today.";
			link.l1.go = "Nemezida_Irons_11";
		break;
		
		case "Nemezida_Irons_11":
            dialog.text = "And what happened? Don't be afraid, tell me. But if it's something funny, I'm going to laugh, just so you know. How else should it be? A friend offers his shoulder and nudges you with his elbow in laughter.";
			link.l1 = "Well, you sure know how to comfort. Tell me, Tommy. You said you liked pirating. Were you glad you got back to it with me?";
			link.l1.go = "Nemezida_Irons_12";
		break;
		
		case "Nemezida_Irons_12":
            dialog.text = "I'll put it like this. Whether I'm a pirate or not, what I've always damn well loved is adventure! I see my answer doesn't satisfy you. This stuff, the big matters, isn't my thing.";
			link.l1 = "It's not that it doesn't satisfy me. But that's not what I wanted to discuss. You know... I realized that with Tiraqs, I completely strayed from my goals. Also... Charlie Prince was some kind of lackey, not a brave pirate captain, do you get it, Tom? That's enough for me.";
			link.l1.go = "Nemezida_Irons_13";
		break;
		
		case "Nemezida_Irons_13":
            dialog.text = "I get it. That's why I was surprised you let Terrax control you like that. It didn't even seem like you.";
			link.l1 = "Maybe I really was Charlie Prince back then. But whether we go back to piracy or not, I'll decide! And only if it really serves my interests and brings me closer to my goal!";
			link.l1.go = "Nemezida_Irons_14";
		break;
		
		case "Nemezida_Irons_14":
            dialog.text = "Now that's more like it! But I want to say, whether it's Charlie Prince or Charles de Maure - it's still you. So with you, it was always damn interesting!";
			link.l1 = "Glad to hear that, Tommy.";
			link.l1.go = "Nemezida_Irons_15";
		break;
		
		case "Nemezida_Irons_15":
            dialog.text = "Remember, almost no one will help except yourself. It's better to do what you love, even alone, than to let others make decisions for you!";
			link.l1 = "True. That's exactly what I felt with Terrax. Even if I do end up following someone again, it'll only be under worthy terms, not like some damn errand boy!";
			link.l1.go = "Nemezida_Irons_16";
		break;
		
		case "Nemezida_Irons_16":
            dialog.text = "You're right! Now, let's get out of here - my legs are already wobbly.";
			link.l1 = "Hey, I was about to say that, ha-ha. But you're right, let's go. We have a lot of important work ahead, Tom. Not this kind of stuff.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionFinal_Officers");
		break;
		
		// Алонсо
		case "Nemezida_Alonso_1":
            dialog.text = "Captain, looks like we've got company! We're not alone here.";
			link.l1 = "Just what we needed... Alright, let's deal with them now. Later, they'll only be more trouble.";
			link.l1.go = "Nemezida_Alonso_2";
		break;
		
		case "Nemezida_Alonso_2":
            dialog.text = "Aye, Captain.";
			link.l1 = "Get ready!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Alonso_3":
            dialog.text = "There are more and more of them!";
			link.l1 = "Then there's no point in continuing this! Fall back! We'll lose them and head straight for the treasure!";
			link.l1.go = "Nemezida_Alonso_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Alonso_4":
            dialog.text = "Aye, Captain!";
			link.l1 = "Move it, move it!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Alonso_5":
            dialog.text = "Captain, looks like there's an entrance here! And someone's already inside.";
			link.l1 = "Listen closely - we've been tracked. I'll head in and check it out while you hold this spot. Cover me, lads!";
			link.l1.go = "Nemezida_Alonso_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Alonso_6":
            dialog.text = "Aye, Captain!";
			link.l1 = "Hold your ground. Good luck to you - to all of us!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("You're "+ GetSexPhrase("a thief, I see! Guards, seize him","a thief, I see! Guards, seize her") +"!!!", "I can't believe it! I turned away for a second - and you're diving into my belongings! Stop a thief!!!", "Guards! Robbery! Stop a thief!!!");
			link.l1 = "Aaaah, devil!!!";
			link.l1.go = "fight";
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//<-- блок реагирования на попытку залезть в сундук
		
		// <-- legendary edition
	}
}

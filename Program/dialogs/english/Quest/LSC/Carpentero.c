// Санчо Карпентеро - бармен
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
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "Get out! I won't serve bastards who attack innocent people in the streets!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = ""+pchar.name+"! I'm damn glad to see you! I knew - I knew! - the rumours weren't true! Damn it, share a drink with me!";
				link.l1 = "Let's drink, Sancho! I'm damn glad to see you, too!";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			// пей до дна
			if (CheckAttribute(npchar, "quest.drink") && npchar.quest.drink == "fail")
			{
				dialog.text = ""+pchar.name+", I'm sorry you lost. Few are able to outdrink that fat man. How is your head?";
				link.l1 = "You... you've serve some damn strong rum, Sancho. I owe you for the drinks... how much?";
				link.l1.go = "drunk_fail";
				break;
			}
			if (CheckAttribute(npchar, "quest.drink") && npchar.quest.drink == "win")
			{
				dialog.text = "You beat Fazio, "+pchar.name+"! I'm gobsmacked! Only one or two have ever outdrunk him. Here, take your two hundred doubloons.";
				link.l1 = "Thank you for kind words, Sancho!";
				link.l1.go = "drunk_win";
				break;
			}
			// крабовый салат
			if (CheckAttribute(npchar, "quest.crab") && npchar.quest.crab == "begin")
			{
				dialog.text = ""+pchar.name+"? They say you dove to the bottom in a suit made by that Narwhal mechanic. Is it true?";
				link.l1 = "It's true, pal. I've seen the bottom of the sea!";
				link.l1.go = "crab";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Greetings! Always glad to see a new face in my tavern! Welcome! You will always find good drink in my tavern - we're filled to the gunwales with European wine!\nCan't say the the same about food, though. Ha... kidding. My name is Sancho Carpentero this is my place.";
				link.l1 = TimeGreeting()+", Sancho. My name is "+GetFullName(pchar)+". Nice to meet you.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, my friend "+pchar.name+"! Good to see you! What'll it be?";
				// квестовые ветки
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "search_mush_1" && !CheckAttribute(npchar, "quest.mushket"))
				{
					link.l6 = "Listen, Sancho, do you know where can I get a good rifle? Not a common infantry musket, but something accurate and long-range - for hunting, maybe.";
					link.l6.go = "mushket";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "search_mush_2")
				{
					link.l6 = "Listen, Sancho, I've got a few questions for you. I'm looking for a man named Adolf Barbier. I've heard he often drinks here...";
					link.l6.go = "adolf";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "barmen_whiskey")
				{
					link.l6 = "Listen, Sancho, they say that Chad Kapper bought some arsenic from you...";
					link.l6.go = "whiskey";
				}
				if (CheckCharacterItem(pchar, "talisman1") && CheckAttribute(npchar, "quest.rat"))
				{
					link.l7 = "Sancho, I want to show you something. Is this the bat mask you've been trying to get your hands on?";
					link.l7.go = "rat";
				}
				if (CheckCharacterItem(pchar, "talisman1") && CheckAttribute(npchar, "quest.ratmoney") && PCharDublonsTotal() >= 1)
				{
					if (PCharDublonsTotal() >= sti(npchar.quest.ratmoney))
					{
						if(!CheckAttribute(npchar, "quest.ratmoneyagain")) ChangeCharacterComplexReputation(pchar, "fame", 5);
						link.l7 = "Sancho, I've come for my cuirass. Here's the money.";
						link.l7.go = "rat_3";
					}
					else
					{
						npchar.quest.ratmoneyagain = true;
						link.l7 = "Sancho, I've come for my cuirass. Here's the money.";
						link.l7.go = "rat_take_money_not_all";
					}
				}
				if (makeint(pchar.money) >= 25)
				{
					link.l1 = "Pour me some rum, Sancho.";
					link.l1.go = "drink";
				}
				if (makeint(pchar.money) >= 20)
				{
					link.l2 = "I want to rent a room.";
					link.l2.go = "room";
				}
				if (stf(environment.time) >= 6.0 && stf(environment.time) <= 18.0 && makeint(pchar.money) >= 300)
				{
					link.l9 = "I'm bored, Sancho. I want to pass some time here with a bottle of wine until evening comes...";
					link.l9.go = "drink_sit";
				}
				link.l3 = LinkRandPhrase("What do people talk about these days, Sancho?", "What's been happening on the island recently?", "Any gossip?");
				link.l3.go = "rumours_LSC";
				if (CheckAttribute(npchar, "quest.crab") && npchar.quest.crab == "current" && CheckCharacterItem(pchar, "crab_pincers"))
				{
					link.l10 = "I have crab claws to sell you, Sancho.";
					link.l10.go = "crab_trade";
				}
				link.l4 = "Sancho, I want to ask you something about the island.";
				link.l4.go = "int_quests"; //информационный блок
				link.l5 = "No, pal. Just wanted to see how you're doing. 'Bye!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "So am I. I hope I will see you at least once an evening, ha-ha! I'm sincerely happy to have a new visitor in my tavern.";
			if (makeint(pchar.money) >= 25)
			{
				link.l1 = "Pour me some rum, Sancho.";
				link.l1.go = "drink";
			}
			if (makeint(pchar.money) >= 20)
			{
				link.l2 = "I want to rent a room.";
				link.l2.go = "room";
			}
			link.l3 = "Sancho, I want to ask you something about the island.";
			link.l3.go = "int_quests"; //информационный блок
			link.l4 = "See you, Sancho!";
			link.l4.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "mushket":
			dialog.text = "No, friend, I can't help you. My specialty is beer and wine, not muskets, ha-ha! Go to the shop, I heard Axel sells interesting weapons sometimes. You might find what you need there.";
			link.l1 = "Thanks for the advice.";
			link.l1.go = "exit";
			npchar.quest.mushket = "true";
		break;
		
		case "adolf":
			dialog.text = "Adolf? Yes, he visits me occasionally, though I've not seen him for a few days, now. He's been missing since his chat with that fat man, Giuseppe.";
			link.l1 = "Giuseppe... you mean Giuseppe Fazio?";
			link.l1.go = "adolf_1";
		break;
		
		case "adolf_1":
			dialog.text = "Only one Giuseppe on the island. Aye, that's him. They sat for a few hours, shared a bottle of rum, and had a very lively conversation.";
			link.l1 = "Were they arguing?";
			link.l1.go = "adolf_2";
		break;
		
		case "adolf_2":
			dialog.text = "No. They talked like old friends. Look, just visit Fazio on the Caroline and ask him.";
			link.l1 = "Fine, I'll do that.";
			link.l1.go = "adolf_3";
		break;
		
		case "adolf_3":
			dialog.text = "Is that all? You said you had a few questions...";
			link.l1 = "Yes. Tell me, who's Red Mary and Marcello Cyclops?";
			link.l1.go = "adolf_4";
		break;
		
		case "adolf_4":
			dialog.text = "Red Mary is one of the Narwhals. Beautiful young girl, but absolutely wild. She wields her blade and a handgun as good as any man. Used to be the girlfriend of Alan Milrow, a former leader of the Narwhal clan, before the Admiral killed him\nAlan's death hit her hard. She spends her days crying and cursing Shark in her cabin on the Ceres... But she will get over it; life goes on, after all.\nI don't know much about Marcello, only seen him a couple of times. Scary fellow. They say he used to be a royal hunter, lost an eye in a fight, and went sailing on a merchantman as a mercenary - spent his days at sea repelling hostile boarding actions.\nUnsurprisingly... he hates pirates.";
			link.l1 = "I see... Thanks a lot, Sancho, you've been a great help.";
			link.l1.go = "adolf_5";
		break;
		
		case "adolf_5":
			dialog.text = "You're welcome, pal. Come see me again, and we'll have some ale together.";
			link.l1 = "Sure!";
			link.l1.go = "adolf_6";
		break;
		
		case "adolf_6":
			DialogExit();
			pchar.questTemp.Saga.SharkHunt = "search_mush_3"; //флаг на Джузеппе
			AddQuestRecord("SharkHunt", "13");
		break;
		
		// виски для Акулы
		case "whiskey":
			dialog.text = "Kapper? No. He hasn't visited the tavern recently. Marcello Cyclops bought a flask of arsenic just fifteen minutes ago - guess he's also plagued by rats. I understand perfectly... damn rats.";
			link.l1 = "The Cyclops was here?!";
			link.l1.go = "whiskey_1";
		break;
		
		case "whiskey_1":
			dialog.text = "Well, yes. Why?";
			link.l1 = "I've been looking for him for a few days. Do you know where he went?";
			link.l1.go = "whiskey_2";
		break;
		
		case "whiskey_2":
			dialog.text = "He was in the company of Adolf Barbier, who lives on the Santa Florentina. Perhaps they were headied there?";
			link.l1 = "Thanks!";
			link.l1.go = "whiskey_3";
		break;
		
		case "whiskey_3":
			dialog.text = "If you need some arsenic, I can sell a flask for twenty doubloons--!";
			link.l1 = "We'll talk about it later, Sancho, 'bye!";
			link.l1.go = "whiskey_4";
		break;
		
		case "whiskey_4":
			DialogExit();
			pchar.questTemp.Saga.SharkHunt = "whiskey_poison"; // флаг - виски травят
			AddQuestRecord("SharkHunt", "37");
			sld = CharacterFromID("LSC_Adolf");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "SantaFlorentinaShipInside4", "goto", "goto2");
			sld = CharacterFromID("Dodson");
			sld.dialog.currentnode = "whiskey"; // ноду Акуле
			// важный момент! От дальнейшего поведения геймера зависит результат
			pchar.quest.LSC_Whiskeypoison_SF.win_condition.l1 = "location";
			pchar.quest.LSC_Whiskeypoison_SF.win_condition.l1.location = "SantaFlorentinaShipInside4";
			pchar.quest.LSC_Whiskeypoison_SF.function = "LSC_WhiskeyPoison_SF"; // прерывание на Санта-Флорентину
			pchar.quest.LSC_Whiskeypoison_AE.win_condition.l1 = "location";
			pchar.quest.LSC_Whiskeypoison_AE.win_condition.l1.location = "AvaShipInside3";
			pchar.quest.LSC_Whiskeypoison_AE.function = "LSC_WhiskeyPoison_AE"; // прерывание на Эву
			pchar.quest.LSC_Whiskeypoison_exit.win_condition.l1 = "location";
			pchar.quest.LSC_Whiskeypoison_exit.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_Whiskeypoison_exit.function = "LSC_Whiskeypoison_exit"; // прерывание на выход из таверны
			// закрываем вход к Фацио
			LocatorReloadEnterDisable("LostShipsCity_town", "reload20", true);
			LocatorReloadEnterDisable("LostShipsCity_town", "reload24", true);
		break;
		
		// пей до дна
		case "drunk_fail":
			dialog.text = "Come on, pal, you don't owe me a thing.  You've already lost a hundred doubloons. That's what you get for trying to drink Fazio under the table...";
			if (sti(pchar.money) >= 500)
			{
				link.l1 = "No, no, Sancho, please! Take these five hundred pesos. That should cover the cost of the drinks, as far as I remember. I don't want to be in your debt.";
				AddMoneyToCharacter(pchar, -500);
			}
			else link.l1 = "Eh.. thanks, Sancho. You're right.";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "quest.drink");
		break;
		
		case "drunk_win":
			DialogExit();
			TakeNItems(pchar, "gold_dublon", 200);
			Log_Info("You have received 200 doubloons");
			PlaySound("interface\important_item.wav");
			DeleteAttribute(npchar, "quest.drink");
		break;
		
		// крабовый салат
		case "crab":
			dialog.text = "Hm... then I have a proposal for you. Did you see any giant crabs down there?";
			link.l1 = "Are you kidding? There were hordes of them! What did you have in mind?";
			link.l1.go = "crab_1";
		break;
		
		case "crab_1":
			dialog.text = "If you kill any of them, be sure to bring the claws to me. I'll pay you well in doubloons: five coins apiece! Axel Yost won't pay that much, I assure you.\nI'm not asking that you go hunting... but if you happen to kill one or two, please keep my offer in mind...";
			link.l1 = "Why claws? What about the other parts of the crab?";
			link.l1.go = "crab_2";
		break;
		
		case "crab_2":
			dialog.text = "Because most of the meat is on the claws. Crabs don't have much meat on their legs and their bodies are covered with a solid shell. Crab meat is a delicacy here. It has an exquisite taste and is very nourishing!\nI have a special recipe for it, so I'll pay you five doubloons for each nipper.";
			link.l1 = "All right, I'll keep that in mind...";
			link.l1.go = "crab_3";
		break;
		
		case "crab_3":
			DialogExit();
			npchar.quest.crab = "current";
		break;
		
		case "crab_trade":
			iTotalTemp = GetCharacterItem(pchar, "crab_pincers")
			dialog.text = "Splendid! How many do you have?";
			link.l1 = ""+FindRussianQtyString(iTotalTemp)+".";
			link.l1.go = "crab_trade_1";
			link.l2 = "I've changed my mind.";
			link.l2.go = "exit";
		break;
		
		case "crab_trade_1":
			dialog.text = "All right. Here, take your doubloons - "+FindRussianQtyString(iTotalTemp*5)+". Thanks, pal, if you get more, bring them to me.";
			link.l1 = "Sure, friend.";
			link.l1.go = "crab_trade_2";
		break;
		
		case "crab_trade_2":
			DialogExit();
			RemoveItems(pchar, "crab_pincers", iTotalTemp);
			TakeNItems(pchar, "gold_dublon", iTotalTemp*5);
			PlaySound("interface\important_item.wav");
			Log_Info("You have received "+iTotalTemp*5+" doubloons");
		break;
		
		// крыс
		case "rat":
			dialog.text = "What?! Show me! Let me see it!";
			link.l1 = "All right, all right, ha-ha!";
			link.l1.go = "rat_1";
		break;
		
		case "rat_1":
			PlaySound("interface\important_item.wav");
			dialog.text = "This... this is it! It's exactly the same as the one in the picture the sailor drew for me!\nFriend... would you sell this to me?";
			link.l1 = "That depends. As I recall, you promised a king's ransom for this thing.";
			link.l1.go = "rat_2";
			link.l2 = "Sorry, pal, it's not for sale. I need it for my ship. Just wanted you to confirm that this really is the talisman you were talking about.";
			link.l2.go = "rat_exit";
		break;
		
		case "rat_exit":
			PlaySound("interface\important_item.wav");
			dialog.text = "Eh, what a shame... Yes, my friend, this is that talisman. Lucky devil! Now you'll never again have to worry about rats! And I'll have to keep exterminating them with arsenic...";
			link.l1 = "I am sorry for getting your hopes up, Sancho. I wasn't sure what this thing looked like, so I needed to be sure. I'm sorry.";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "quest.rat");
		break;
		
		case "rat_2":
			dialog.text = "For this,"+pchar.name+", I'll... I'll offer you the chance to purchase the finest and most valuable item I possess! Let me fetch it for you...\nTake a look. Here is a unique, resplendent Milano Cuirass, masterfully crafted! It provides exceptional protection in battle, allows full range of movement, and is lightweight and comfortable. Armour of this quality is exceptionally rare, both in the Caribbean and Europe.\nI stumbled upon this cuirass in the captain's quarters of a Spanish man-o'-war several years ago and kept it precisely for an occasion like this. I'm willing to sell it to you for two thousand gold coins plus the Rat God!";
			link.l1 = "Hmm... My, this is indeed a masterwork cuirass! I think this exchange suits me. There are many ways to deal with rats, but finding another cuirass like this would be next to impossible. I've never seen one quite like it before. Truly, it's a unique piece of armour.";
			link.l1.go = "rat_yes";
			link.l2 = "How much?! Sancho, have your rats already bitten you a few times this morning? What do you mean, two thousand? Do you even know what it took to find this idol?! Drop the price right now!";
			link.l2.go = "rat_torg";
			link.l3 = "How much?! You're a shark, you know that, Sancho? 'Offer the chance to purchase' - ha! For that kind of money, I could order my own suit of armour on the mainland that would deflect bullets and let me walk on water! And why would you need so much gold, to have Jurgen cast a statue of you and display it on the deck of the San Agustine?";
			link.l3.go = "rat_no";
		break;
		
		case "rat_yes":
			dialog.text = "I'm glad you're on board, my friend. Thanks for not forgetting about my problem! So, I'll be expecting my doubloons. The armour will be waiting for you!";
			link.l1 = "I'll bring them over shortly!";
			link.l1.go = "rat_yes_1";
		break;
		
		case "rat_yes_1":
			DialogExit();
			DeleteAttribute(npchar, "quest.rat");
			npchar.quest.ratmoney = 2000;
		break;
		
		case "rat_torg":
			if(GetSummonSkillFromName(pchar, SKILL_COMMERCE) < 60)
			{
				Notification_Skill(false, 60, SKILL_COMMERCE);
				dialog.text = ""+pchar.name+", under different circumstances, I would demand five thousand. The Admiral himself has shown interest - and he is not the only one, believe me. But take your time deciding; the armor will be waiting for you for as long as you need. I'll only sell it to you.";
				link.l1 = "I'll think about it, Sancho.";
				link.l1.go = "rat_yes_1";
				AddCharacterExpToSkill(pchar, "Commerce", 400);
			}
			else
			{
				Notification_Skill(true, 60, SKILL_COMMERCE);
				dialog.text = ""+pchar.name+", under different circumstances, I would demand five thousand. The Admiral himself has shown interest - and he is not the only one, believe me.\nFine, I'll knock off five hundred, considering you didn't forget about me and my problem. It must've been a difficult adventure.";
				link.l1 = "That's better... but I still don't get why I should pay extra in this trade of equally unique items. Maybe you should be the one paying me, eh Sancho, he-he?";
				link.l1.go = "rat_yes_1500";
				AddCharacterExpToSkill(pchar, "Commerce", 100);
			}
		break;
		
		case "rat_yes_1500":
			if(GetSummonSkillFromName(pchar, SKILL_COMMERCE) < 90)
			{
				Notification_Skill(false, 90, SKILL_COMMERCE);
				dialog.text = "No, "+pchar.name+", not a chance. I can deal with rats using arsenic, but this armour could save your life one day. And you'll look like an Italian duke wearing it! One thousand five hundred, that's my final offer. Take your time to think about it, and let me know. The armour will be waiting for you as long as you need, I'll only sell it to you.";
				link.l1 = "Sancho, if you weren't the only tavern keeper in this dreary graveyard... I'll think about your offer.";
				link.l1.go = "rat_yes_1500exit";
				AddCharacterExpToSkill(pchar, "Commerce", 600);
			}
			else
			{
				Notification_Skill(true, 60, SKILL_COMMERCE);
				dialog.text = "For a military captain and a pirate, you sure know how to negotiate! Remember Jost? He once managed to buy all my arsenic at a discount, while the rats were already tormenting me.\nAlright, "+pchar.name+", you win. I'll knock off another five hundred for you! But that's my final offer!";
				link.l1 = "This still feels like a rip-off, but at least now I won't feel like a typical damsel in distress in the jungle. Wait for me, I'll bring the money soon.";
				link.l1.go = "rat_yes_1000exit";
				AddCharacterExpToSkill(pchar, "Commerce", 200);
			}
		break;
		
		case "rat_no":
			dialog.text = "Calm down, "+pchar.name+". From anyone else, I would demand five thousand! The Admiral himself has shown interest - and he is not the only one, believe me.\nThe armour will be waiting for you - I won't sell it to anyone else in the meantime.";
			link.l1 = "What an honour! I'll be back soon. Two thousand!";
			link.l1.go = "rat_yes_1";
		break;
		
		case "rat_yes_1500exit":
			DialogExit();
			DeleteAttribute(npchar, "quest.rat");
			npchar.quest.ratmoney = 1500;
		break;
		
		case "rat_yes_1000exit":
			Achievment_SetStat(106, 1);
			DialogExit();
			DeleteAttribute(npchar, "quest.rat");
			npchar.quest.ratmoney = 1000;
		break;
		case "rat_3":
			dialog.text = "Done! I'm glad you agree, mate. Thanks for not forgetting about my problem! Take the cuirass, and may it serve you well in battle.";
			link.l1 = "Here, take your talisman - looks like dark days are coming for the rats in your tavern, ha-ha!";
			link.l1.go = "rat_4";
		break;
		
		case "rat_4":
			DialogExit();
			GiveItem2Character(pchar, "cirass4");
			RemoveItems(pchar, "talisman1", 1);
			RemoveDublonsFromPCharTotal(sti(npchar.quest.ratmoney));
			Log_Info("You have given away the talisman 'God of rats'");
			Log_Info("You have received a Milanese armor");
			Log_Info("You gave "+FindRussianDublonString(sti(npchar.quest.ratmoney))+"");
			PlaySound("interface\important_item.wav");
			DeleteAttribute(npchar, "quest.ratmoney");
			if(CheckAttribute(npchar, "quest.ratmoneyagain"))
				DeleteAttribute(npchar, "quest.ratmoneyagain");
		break;
		
		case "rat_take_money_not_all":
			npchar.quest.ratmoney = sti(npchar.quest.ratmoney) - PCharDublonsTotal();
			Log_Info("You gave "+FindRussianDublonString(PCharDublonsTotal())+"");
			RemoveDublonsFromPCharTotal(PCharDublonsTotal());
			PlaySound("interface\important_item.wav");
			dialog.text = "You still awe me "+FindRussianDublonString(sti(npchar.quest.ratmoney))+", "+pchar.name+".";
			link.l1 = "Don't remind me!";
			link.l1.go = "exit";
		break;
		
		//--> информационный блок
		case "int_quests":
			dialog.text = "I'm listening, friend.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "What is this island? Can you tell me more about it?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "How would I leave the island?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "What should I know about the island?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "And how are you doing here? How is your tavern?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "I have no questions, never mind...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "This island? Well, they call it Justice Island, the Island of Justice, or the City of Abandoned Ships - but we just call it the island. It's formed out of shipswrecks, which are stuck on a shoal at the centre of the reefs.\nThis central part of the island is our living space; the outer ring of wrecks is uninhabited. There's been no connection with the outside world for ten years.";
			link.l1 = "Incredible!";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Build a long boat or a raft - but it won't end well for you. Storms and powerful currents circle the island, and if you go beyond the outer ring, you take your life into your hands.\nYou'd need a team of prime sailors to have even the slightest chance of survival, and very few locals are willing to leave this place. Even fewer are willing to take the risk of venturing beyond the outer ring.\nPeople like living here. Ask around if you don't believe me.";
			link.l1 = "I see...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "First, you should remember that there are several restricted areas on the island. Two clans, the Narwhals and the Rivados, have been living here for a long time, fighting each other ceaselessly and guarding the territories they each consider their own. Pay them a visit uninvited, and you're a dead man.\nYou must know the current password if you want to enter their territory. Don't worry about trespassing accidentally, guards will give you several warnings before they start shooting.";
			link.l1 = "I'll keep that in mind...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "You know, my friend, it's fine. I'm used to working with food and drink. I served as a cook lots of places in Europe - garrisons, grog houses, ships - so the first thing I did here was establish a tavern.\nI like my job and my life is satisfying. Everybody needs food and drink, and I enjoy serving them. Folks are friendly, here, and mostly peaceful. I can't remember the last time I had to clean up after a drunken brawl. And the clans don't bother me.\nAll in all, this the best place I've had in my life. I'm free here, and no one tells me what to do.\nThe only thing driving me mad is the rats. They torture me; eating my provisions and ruining my tableware. And they're impossible to get rid of.";
			link.l1 = "Oh yes, I know firsthand how troublesome the little shits are...";
			link.l1.go = "ansewer_4_1";
		break;
		
		case "ansewer_4_1":
			dialog.text = "Seems I'm the most unfortunate person in the city when it comes up to rats. Other ships are not terrorized nearly as badly as my Fleuron. Axel Yost somehow managed to get rid of his rats once and for all, but me, I've got armies of the furry bastards crawling around.\nYou know, I once heard tell of a special amulet called the Rat God. It looks like a bat's face. Supposedly this amulet scares rats away completely.\nMust be how Axel dealt with his rats; he buys and re-sells every piece of garbage people bring him from the outer ring.\nIf someone offered me that amulet, I'd pay a king's ransom for it!";
			link.l1 = "I'll remember that...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
			npchar.quest.rat = "true";
		break;
		//<-- информационный блок
		
		//--> выпивка
		case "drink":
			if (CheckAttribute(pchar, "questTemp.Rum") && sti(pchar.questTemp.Rum) > 4)
			{
				dialog.text = ""+pchar.name+", I think you've had enough, pal. God forbid you get robbed or fall overboard to feed the crabs. It's not a good idea to drink too much around here, it can get you killed.";
				link.l1 = "Hm... I suppose you're right, Sancho - hic! - I have had enough. Thanks for your concern.";			
				link.l1.go = "exit";
			}
			else
			{
				AddMoneyToCharacter(pchar, -25);
				if(!IsEquipCharacterByArtefact(pchar, "totem_01"))
				{
					if (CheckAttribute(pchar, "questTemp.Rum"))
					{
						pchar.questTemp.Rum = sti(pchar.questTemp.Rum) + 1;
					}
					else pchar.questTemp.Rum = 1;
				}
				else 
				{
					if(CheckAttribute(pchar, "questTemp.Rum")) DeleteAttribute(pchar, "questTemp.Rum");
				}				
				WaitDate("",0,0,0, 0, 30);
				
				dialog.text = "You're welcome, pal. Only twenty-five pesos for a pint of my best rum!";
				link.l1 = RandPhraseSimple(LinkRandPhrase("To your health and your tavern's prosperity, pal!","To all sea folk, wherever they may be!","To the people of Justice Island!"), LinkRandPhrase("To the island, and may it be around forever!","May the wind always be favorable, whatever course we set!","To luck, happiness... and women!"));		
				link.l1.go = "drink_1";
			}
		break;
		
		case "drink_1":
			DialogExit();
			LAi_Fade("", "");
			if (CheckAttribute(pchar, "questTemp.Rum"))
			{
				if (sti(pchar.questTemp.Rum) < 3) LAi_AlcoholSetDrunk(pchar, 51, 5600);
				else LAi_AlcoholSetDrunk(pchar, 71, sti(pchar.questTemp.Rum)*2800);
			}
		break;
		
		case "drink_sit":
			if (chrDisableReloadToLocation || pchar.questTemp.Saga.SharkHunt == "barmen_whiskey" || pchar.questTemp.Saga.SharkHunt == "whiskey_poison") //идёт квест
			{
				dialog.text = "I dont think you should be drinking right now. Trust me...";
				link.l1 = "All right...";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye") || CheckAttribute(pchar, "questTemp.LSC.MaryWait")) // подружился с Мэри
			{
				dialog.text = "Heh, you are a strange man... Don't you have someone to pass the time with here, on the island? Mary will kill me if I let you stay here and drink alone. Come here together in the evening and have fun 'til dawn, if you wish.";
				link.l1 = "Good idea!";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "No problem, mate. For just three hundred pesos you'll have a fine bottle of "+LinkRandPhrase("Spanish","Italian","French")+" wine - and a table for as long as you want.";
				link.l1 = "Thanks!";
				link.l1.go = "drink_sit_1";
			}
		break;
		
		case "drink_sit_1":
			DialogExit();
			sld = ItemsFromID("potionrum");
			sld.shown = true;
			sld.startLocation = "FleuronTavern";
			sld.startLocator = "bottle";
			DoQuestReloadToLocation("FleuronTavern", "quest", "sit2", "LSC_DrinkSit");
		break;
		//<-- выпивка
		
		//--> сон в таверне
		case "room":
   			if (chrDisableReloadToLocation || pchar.questTemp.Saga.SharkHunt == "barmen_whiskey" || pchar.questTemp.Saga.SharkHunt == "whiskey_poison") //идёт квест
			{
				dialog.text = "I dont think you should sleep right now. Trust me...";
				link.l1 = "Fine.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye") || CheckAttribute(pchar, "questTemp.LSC.MaryWait")) // подружился с Мэри
			{
				if(!isDay())
				{
					dialog.text = "I can't understand you, pal. There is a beautiful girl waiting for you on the Ceres and you want to spend the night at the tavern alone? I can't let you do that, Mary would kill me.";
					link.l1 = "You're probably right...";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "You can rest upstairs until the evening, but I won't let you spend the night here; Mary would kill me. Sorry...";
					link.l1 = "Fine, I'll stay here until the evening...";
					link.l1.go = "hall_night_wait";
					link.l2 = "Fine... I'll manage without sleeping.";
					link.l2.go = "exit";
				}
				break;
			}
			dialog.text = "For twenty pesos, you can sleep in the bed upstairs. When should I wake you?";
			if(!isDay())
			{
				link.l1 = "In the morning.";
				link.l1.go = "hall_day_wait";
			}
			else
			{
				link.l1 = "Before nightfall.";
				link.l1.go = "hall_night_wait";
				link.l2 = "Next morning.";
				link.l2.go = "hall_day_wait";
			}
			link.l3 = "I've changed my mind. I don't want to sleep.";
			link.l3.go = "exit";
		break;
		
		case "hall_night_wait":
			AddMoneyToCharacter(pchar, -20);
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			TavernWaitDate_LSC("wait_night");
		break;
		
		case "hall_day_wait":
			AddMoneyToCharacter(pchar, -20);
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			TavernWaitDate_LSC("wait_day");
		break;
		//<-- сон в таверне
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}

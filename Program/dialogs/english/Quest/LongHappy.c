// диалоги персонажей по квесту Долго и счастливо
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "What do you need?";
			link.l1 = "Nothing.";
			link.l1.go = "exit";
		break;
		
		// вестовой капитан в порту
		case "cureer":
			dialog.text = "Monsieur de Maure, what luck! I've been looking for you for months!";
			link.l1 = "My dear, I don't buy fake maps, dubious information, or homemade rum - thank you! Or are you a bounty hunter? And how much is my head worth now?";
			link.l1.go = "cureer_1";
		break;
		
		case "cureer_1":
			dialog.text = "Oh, monsieur, I... I don't deal in junk and I don't kill people - don't touch your sword, you won't need it, I mean no harm! Everything is much more prosaic - I'm the captain of a courier ship. I deliver mail. And for you, I have an important letter!";
			link.l1 = "A letter? Who is the sender, may I ask?";
			link.l1.go = "cureer_2";
		break;
		
		case "cureer_2":
			dialog.text = "An abbot handed it to me and asked me to deliver it to Captain de Maure personally, from hand to hand. I had already lost all hope of finding you and was about to leave it at the harbour office in Saint Pierre, but what luck - here you are!";
			link.l1 = "Yes, here I am, I'm waiting - give me the letter.";
			link.l1.go = "cureer_3";
		break;
		
		case "cureer_3":
			dialog.text = "There is one problem... The abbot said that the delivery would be paid by the recipient. So you owe nine thousand and two hundred pesos.";
			link.l1 = "For that kind of money, it should have been brought to me on the open sea, right to my cabin, along with my morning coffee! You can keep the letter for yourself.";
			link.l1.go = "cureer_6";
			if (sti(pchar.money) >= 9200)
			{
				link.l2 = "And why didn't I go into mail delivery?! It's more profitable than piracy! Here is your silver, my dear, hand over the envelope.";
				link.l2.go = "cureer_4";
			}
		break;
		
		case "cureer_4":
			AddMoneyToCharacter(pchar, -9200);
			dialog.text = "Nice doing business with you! Abbot Benoit sends his best wishes! Farewell, Monsieur de Maure!";
			link.l1 = "";
			link.l1.go = "cureer_5";
		break;
		
		case "cureer_5":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			LongHappy_RecibeLetter();
		break;
		
		case "cureer_6":
			dialog.text = "As you wish. I will leave the envelope at the harbour office. But it will affect the price, I warn you. And yes - Abbot Benoit sends you his best wishes.";
			link.l1 = "The letter from Abbot Benoit? Why didn't you say so from the start! It must be important!";
			link.l1.go = "cureer_7";
		break;
		
		case "cureer_7":
			dialog.text = "So pick it up from the harbourmaster. Don't forget to take a loan in advance. Farewell, Captain de Maure.";
			link.l1 = "I've known pirates more sincere than you. Good luck, my dear.";
			link.l1.go = "cureer_8";
		break;
		
		case "cureer_8":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			pchar.questTemp.LongHappy = "portman";
		break;
		
		// испанский офицер в Сантьяго
		case "spa_officer":
			dialog.text = "Holy Father, you are earlier than usual today. Please, your escort is waiting. And you, señor de Maure - Father Vincento has learned that you are in the city and urges you to join him for dinner.";
			link.l1 = "I'm afraid the Inquisitor will have to dine alone. I hope this won't spoil his appetite. And Abbot Benoit will also deprive him of his company. You know who I am, so I advise you: let us pass without any trouble, and give my regards to Father Palotti.";
			link.l1.go = "spa_officer_1";
		break;
		
		case "spa_officer_1":
			if(sti(pchar.reputation.nobility) > 80 || sti(pchar.reputation.nobility) < 20) // провести учёт чести и известности
			{
				Notification_Reputation(true, 81, "low");
				dialog.text = "Yes, I have heard a lot about you, and I have clear instructions not to turn the city into a bloodbath if you are stubborn. You may go through. But Father Vincento will be... dissatisfied. Keep this in mind.";
				link.l1 = "You acted reasonably, monsieur. I'll survive somehow, though my heart aches with the disappointment of the father-inquisitor. Have a pleasant evening!";
				link.l1.go = "spa_officer_2";
			}
			else
			{
				Notification_Reputation(false, 81, "low");
				Notification_Reputation(false, 19, "high");
				dialog.text = "Yes, I have heard about you... a lot of interesting things. However, rejecting such invitations is dangerous to your health, señor. As is kidnapping the guests of Father Vincento. Seize them!";
				link.l1 = "Everyone has made his choice. I am sorry it had to come to this. To arms, caballero!";
				link.l1.go = "spa_officer_3";
			}
		break;
		
		case "spa_officer_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("LH_escort_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload3_back", "none", "", "", "", 15.0);
			}
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			pchar.quest.longhappy_santiago2.win_condition.l1 = "location";
			pchar.quest.longhappy_santiago2.win_condition.l1.location = "Cuba1";
			pchar.quest.longhappy_santiago2.function = "LongHappy_SantiagoSail";
			pchar.quest.longhappy_santiago3.win_condition.l1 = "location";
			pchar.quest.longhappy_santiago3.win_condition.l1.location = "Cuba2";
			pchar.quest.longhappy_santiago3.function = "LongHappy_SantiagoSail";
		break;
		
		case "spa_officer_3":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("LH_escort_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
				LAi_group_Attack(sld, Pchar);
			}
			SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
			LAi_SetFightMode(pchar, true);
			ChangeCharacterNationReputation(pchar, SPAIN, -20);
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
			pchar.quest.longhappy_santiago2.win_condition.l1 = "location";
			pchar.quest.longhappy_santiago2.win_condition.l1.location = "Cuba1";
			pchar.quest.longhappy_santiago2.function = "LongHappy_SantiagoSail";
			pchar.quest.longhappy_santiago3.win_condition.l1 = "location";
			pchar.quest.longhappy_santiago3.win_condition.l1.location = "Cuba2";
			pchar.quest.longhappy_santiago3.function = "LongHappy_SantiagoSail";
		break;
		
		case "Guests_block":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;
		
		// Ян Свенсон патер
		case "Svenson":
			dialog.text = "Charles, congratulations! You know, I've always liked you, and Helen is like a daughter to me, so I'm happy for you both. Damn... to shed a tear in a church is all I've ever wanted. Am I getting old or what?";
			link.l1 = "Everything is fine, Jan, I almost cried at the altar. Incense, probably?";
			link.l1.go = "Svenson_1";
		break;
		
		case "Svenson_1":
			dialog.text = "Right, camphor, damn it. I've been wondering why my eyes are stinging and my nose is itching! Fine, we'll have a talk in Sharptown, hug Gladys and go to the others. They've got faces as if we're signing the Peace of Westphalia.";
			link.l1 = "Thank you for coming, Jan. I'm glad to see you, and it means a lot to Helen.";
			link.l1.go = "Guests_block";
		break;
		
		// Ян Свенсон на Исла Тесоро
		case "Svenson_2":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Here you are at last, Charles! My corvette overtook you by almost a day – quite an occasion for pride.";
			link.l1 = "You're welcome, Jan, but where's Gladys, and your wife?";
			link.l1.go = "Svenson_3";
		break;
		
		case "Svenson_3":
			dialog.text = "I sent Gladys back to Blueveld on a merchant ship - she doesn't approve of all these dashing parties. Joanna couldn't come - oh, I had no time to tell you on Martinique! Just imagine - in my old age, I am to become a legitimate father, how about that? Look, if you hurry, our offspring will be almost the same age, hahaha!";
			link.l1 = "Jan, my congratulations, that's good news! We should drink to it!";
			link.l1.go = "Svenson_4";
		break;
		
		case "Svenson_4":
			dialog.text = "Definitely! But first, to you and your better half! Hey, you there, quiet!!! The old Forest Devil must give a speech!\nAhem... So, our dear Monsieur and Madame de Maure... Blast it! I can't speak like this! Charles, Helen - you two, to me, are like my own children, and I know that in this room there is no one who wouldn't be happy for your union! So let us drink, my brethren, to the happiness of our faithful friends, to a fair wind in their sails and to the love of Lady Fortune, as strong as their feelings for each other!!! Cheers!";
			link.l1 = "Cheers! Thanks Jan... oh, this rum is much stronger than usual... What did Nathan mix in it?";
			link.l1.go = "Svenson_5";
		break;
		
		case "Svenson_5":
			dialog.text = "I have no idea, but it strikes me as right. Old Hawk is generally an expert on drinks. Come on, go to the others, I need to make drinks for a good hundred souls greedy to get their fill.";
			link.l1 = "The Forest Devil pouring drinks - what a sight! Thank you for taking charge of organising the party. I'll definitely be back as soon as I've made the rounds - perhaps someone else needs help.";
			link.l1.go = "Svenson_6";
		break;
		
		case "Svenson_6":
			DialogExit();
			npchar.dialog.currentnode = "Svenson_6_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Svenson_6_1":
			dialog.text = "Everything all right, Charles?";
			link.l1 = "Perfect, Jan!";
			link.l1.go = "Svenson_6";
		break;
		
		case "Svenson_7":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "And here you are, at last! How did it go on Martinique? Do you feel that your life has changed forever?";
			link.l1 = "It changed much earlier, Jan. But everything went surprisingly well. Where is Johanna and...";
			link.l1.go = "Svenson_8";
		break;
		
		case "Svenson_8":
			dialog.text = "Helen? The girl set sail as soon as she found out what we were up to, and headed for the horizon. She sent you all sorts of warm congratulations, but still... you broke her heart, you truly did. However, everything will be fine, it's just youth.";
			link.l1 = "Well, the heart wants what it wants, you understand.";
			link.l1.go = "Svenson_9";
		break;
		
		case "Svenson_9":
			dialog.text = "I do. Well, Johanna couldn't make it, just imagine – in my old age, I'll become a legal father, how about that? Look, if you hurry, our children will be almost the same age, hahaha!";
			link.l1 = "Jan, my congratulations, that's good news! We should drink to it!";
			link.l1.go = "Svenson_10";
		break;
		
		case "Svenson_10":
			dialog.text = "Definitely! But first, to you and your better half! Hey, you there, quiet!!! The old Forest Devil must give a speech!\nCharles and Mary, the entire Brethren are raising goblets in your honour now! The happiness of true friends delights the soul of any sea wolf, almost as much as the splendour of Spanish gold, ha-ha! Sail well, and may fair winds follow you on your family journey!!! Cheers!";
			link.l1 = "Cheers! Thanks Jan... oh, this rum is much stronger than usual... What did Nathan mix in it?";
			link.l1.go = "Svenson_11";
		break;
		
		case "Svenson_11":
			dialog.text = "I have no idea, but it strikes me as quite right. Old Hawk is generally an expert on drinks. Come on, go to the others, I need to make drinks for a good hundred souls greedy to get their fill.";
			link.l1 = "This tavern definitely needs to be renamed - 'The Forest Devil himself was standing here behind the counter'! Thank you, Jan, I will definitely be back as soon as I've spoken to everyone - perhaps someone needs help.";
			link.l1.go = "Svenson_6";
		break;
		
		case "Svenson_12":
			dialog.text = "How are you doing, Charles? How is the wedding?";
			link.l1 = "Very heartwarming, Jan. I'm glad we managed to bring all of us here. Looks like Hawk's barrels of rum are starting to show their bottoms, aren't they?";
			link.l1.go = "Svenson_13";
		break;
		
		case "Svenson_13":
			dialog.text = "Yes, they are! So, it's time to open what you brought here. And another thing - those fellows who helped me at first have got far too drunk in the back room. You seem to still be on your feet, bridegroom - could you bring a box of sherry?";
			link.l1 = "Sure, just tell me where to go. Maybe I'll find a few sober heads along the way to help me. Although, most of my guys are probably already drunk as a skunk.";
			link.l1.go = "Svenson_14";
		break;
		
		case "Svenson_14":
			dialog.text = "The wine was stored in the cellars beneath the shipyard, remember them? Hawk said to keep it in the far corridor, ''to save until the holiday'' - he says. He also says that the temperature and humidity there are perfect, says it would make an ideal place for a wine cellar. Well, he is a real snob.";
			link.l1 = "He made the right decision, Jan. I'll go, but first, tell me - did you see my wife?";
			link.l1.go = "Svenson_15";
		break;
		
		case "Svenson_15":
			dialog.text = "She and Dannie went somewhere. Let the girls talk, Charles, and we have to start a real party. Go into the cellars while I deal with the food. Because it smells like soon we'll be eating coal instead of sheep ribs!";
			link.l1 = "Alright, go save the meat, I'll fetch our wine.";
			link.l1.go = "Svenson_16";
		break;
		
		case "Svenson_16":
			DialogExit();
			npchar.dialog.currentnode = "Svenson_6_1";
			LongHappy_IslaTesoroToVineGo();
		break;
		
		case "Svenson_17":
			dialog.text = "Charles, Nathan, what happened, did you start a drunken fight?!";
			link.l1 = "No, Jan, we fought together against some armed cutters in the dungeons. We dealt with them, but they were only scouts - the main squad is right behind us!";
			link.l1.go = "Svenson_18";
		break;
		
		case "Svenson_18":
			dialog.text = "Squad? What are you talking about?! Marcus, come here! Charles, come on, tell us everything.";
			link.l1 = "Like I said: there are some bastards in the dungeons under the shipyard. Well-armed. Nathan and I fought them and miraculously took everyone down. But there are more of them on the way - I heard one of them was sent for help. And yes, one of them mentioned someone called Jacques.";
			link.l1.go = "Svenson_19";
		break;
		
		case "Svenson_19":
			DialogExit();
			sld = characterFromId("Terrax");
			sld.dialog.currentnode = "Terrax_7";
			ChangeCharacterAddressGroup(sld, "Pirates_tavern", "tables", "stay8");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Svenson_20":
			dialog.text = "I recognise their faces... this one, and that bastard lying by the door. They're thugs of Jacques the Kindman. I don't remember their names, but I'm certain of it.";
			link.l1 = "So this is Barbazon's fault? Is he out of his mind or what?!";
			link.l1.go = "Svenson_21";
		break;
		
		case "Svenson_21":
			dialog.text = "I don't know, but it seems that the Kindman decided to seize the opportunity and orchestrate a radical reshuffle among the barons of the Brethren.";
			link.l1 = "In this case, I hope he shows up himself - I've been dreaming for so long of putting a couple of holes in his body. Bastard, ruined my wedding, just think about it! Let's move, to the streets! We'll give our guests a proper welcome!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_TavernReload");
		break;
		
		case "Svenson_22":
			dialog.text = "And here is our weary hero! Hah, Charles, that was something! Jacques, what a rat! Look how he set everything up - he almost pulled it off!";
			link.l1 = "Yes, perhaps we should have killed that bastard when we had finished with Jackman. However, it is over. Barbazon is dead.";
			link.l1.go = "Svenson_23";
		break;
		
		case "Svenson_23":
			if (CheckAttribute(pchar, "questTemp.LongHappy.SvensonsShipSink")) dialog.text = "Well, can't say it's over at all - our life goes on! Although I feel completely wrecked. I'm too old to jump into the sea from a ship covered in flames and swim for an hour to the shore, keeping an eye out for sharks. I hope we still have some rum...";
			else dialog.text = "Well, can't say it's over at all - our life goes on! Damn it, I feel ten years younger! It's been a long time since I last fought like that! I hope your stocks of rum and wine weren't stolen during the mess - we need to drink to that properly!";
			link.l1 = "Yup, I would drink too, but first I have to check the residence, I don't know if you've been told or not...";
			link.l1.go = "Svenson_24";
		break;
		
		case "Svenson_24":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim"))
			{
				dialog.text = "It's about your Indian friend? Yes, I heard, how did it happen?";
				link.l1 = "He jumped to shield my wife and Dannielle from a bullet fired by one bastard. We should go, I'll explain as we walk.";
			}
			else
			{
				dialog.text = "It's about Nathan? Yes, I heard, just didn't understand how it happened?";
				link.l1 = "He jumped in to shield our wives from a bullet fired by some bastard. We should go, I'll tell you along the way.";
			}
			link.l1.go = "Svenson_25";
		break;
		
		case "Svenson_25":
			DialogExit();
			DoQuestReloadToLocation("Pirates_townhall", "goto", "goto4", "LongHappy_DannyInResidence");
		break;
		
		case "Svenson_26":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") && CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "Stay strong, Charles. I'm truly sorry for your boys. Today, many good men have fallen, and for each of them, Barbazon will have more oil in his boiler in hell.";
				link.l1 = "It makes no sense... damn it! It's hard, Jan... I've already lost friends, but I can't get used to it. I don't know if I can go on anymore.";
				link.l1.go = "Svenson_28";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
				{
					dialog.text = "So that quiet medic? I'm sorry, Charles, truly. He was a good man.";
					link.l1 = "Yes, Jan, me too. But I am afraid the world of science has lost far more than I have. He was a genius... sophisticated, like all of them, but... fuck...";
					link.l1.go = "Svenson_27";
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim")) sTemp = "your Indian guy";
					else sTemp = "Nathan";
					dialog.text = "Well, it seems to be over. Today, many good men have gone, and for each of them, in hell, Barbazon will get more oil in his boiler, but "+sTemp+" will be fine, and that's the main thing.";
					link.l1 = "You're right, Jan, and it's a great weight off my mind. How are the other barons? Are they all right?";
					link.l1.go = "Svenson_32";
				}
			}
		break;
		
		case "Svenson_27":
			dialog.text = "The last filth of Jacques Barbazon. You're right, if we had killed him earlier, everything could have been different.";
			link.l1 = "But what's the use of regretting the past? The past cannot be changed. How are the other barons? Did everyone survive?";
			link.l1.go = "Svenson_32";
		break;
		
		case "Svenson_28":
			dialog.text = "No one can get used to it. Let's drink to our lads? I found a bottle on the table, it miraculously survived this mess.";
			link.l1 = "Pour, I... Damn... a thousand damnations!";
			link.l1.go = "Svenson_29";
		break;
		
		case "Svenson_29":
			dialog.text = "Tell me about them. This medic seemed clever. He expressed himself so wisely.";
			link.l1 = "He did. But, I am afraid, the world of science has lost far more than just me. He was a genius... sophisticated, like all of them. The master of miracles!";
			link.l1.go = "Svenson_30";
		break;
		
		case "Svenson_30":
			dialog.text = "About the Indian man? Where did you find him?";
			link.l1 = "Rescued him from prison on Guadeloupe almost immediately after my arrival. Really funny and stupid story. So, he stayed with me. He chose to; I gave him freedom, but he stayed by my side – I saved him, and he thought he owed me till the end of his life. Terse, dressed oddly, but more loyal than any knight, he had a talent too – he could hit a coin with a musket mid-air at any distance.";
			link.l1.go = "Svenson_31";
		break;
		
		case "Svenson_31":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Well, he paid you the debt, what can I say. Saved "+sld.name+" and Dannielle from that bastard. It seems to me this is a fitting end for such a brave warrior.";
			link.l1 = "It is, Jan. Let's drink to the memory of the fallen... May they find peace. How are the other barons? Are they all right?";
			link.l1.go = "Svenson_32";
		break;
		
		case "Svenson_32":
			dialog.text = "This night has cost us dearly. I don't even know when the Brethren will recover from this massacre. Kindman chose the time and place to strike perfectly. He almost succeeded - just a little more and all would have been lost. But we lost much less than we could have.";
			link.l1 = "";
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) link.l1.go = "Svenson_33";
			else link.l1.go = "Svenson_35";
		break;
		
		case "Svenson_33":
			dialog.text = "The Shark is in the infirmary, his ship took a volley from twenty-four pounders. He was thrown overboard, broke a couple of ribs, swallowed seawater, but he lives; in a few days he will be as good as new.";
			link.l1 = "";
			if (CheckAttribute(pchar, "questTemp.LongHappy.BigMarry")) link.l1.go = "Svenson_34"; // был Венсан
			else link.l1.go = "Svenson_36"; // на завершение
		break;
		
		case "Svenson_34":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Vensan_alive")) dialog.text = "Bernard got just a couple of scratches - he was defending the shore and clearing out the catacombs. Now, he's in the harbour, organising hospitals for the wounded and funerals for those who were less fortunate.";
			else dialog.text = "Bernard was unlucky. He was clearing out the houses after the attack from the catacombs and ran into a bunch of those bastards in the storehouses. He caught a bullet, straight in the head. It's a pity, he was a good captain... Tyrex will be furious when he finds out.";
			link.l1 = "";
			link.l1.go = "Svenson_36"; // на завершение
		break;
		
		case "Svenson_35":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Vensan_alive")) dialog.text = "Bernard got just a couple of scratches – he was defending the shore and clearing out the catacombs. Now, he's in the harbour, organising hospitals for the wounded and funerals for those who were less fortunate.";
			else dialog.text = "Bernard was unlucky. He was clearing out the houses after the attack from the catacombs and ran into a bunch of those bastards in the storehouses. He caught a bullet, straight in the head. It is a pity, he was a good captain... Tyrex will be furious when he finds out.";
			link.l1 = "";
			link.l1.go = "Svenson_36"; // на завершение
		break;
		
		case "Svenson_36":
			dialog.text = "About Hawk, you know. Dannie won't allow him to leave the island for at least a month, that's for sure. He had one thing on his mind... oh, well.";
			link.l1 = "";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner")) link.l1.go = "Svenson_37";
			else link.l1.go = "Svenson_38";
		break;
		
		case "Svenson_37":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Free"))
			{
				dialog.text = "Marcus is as steadfast as ever. As soon as he went ashore, he immediately began to shake the souls out of the sentries who had allowed all this filth. He still manages to command the restoration of order in the town. An iron man, without a doubt.";
				link.l1 = "Iron is softer. I suppose our baron is made of a metal still unknown to science, haha!";
			}
			else
			{
				pchar.questTemp.LongHappy.Terrax.Lost = "true";
				dialog.text = "Only Marcus's situation is unclear; his ship was boarded, but the survivors claim he managed to jump overboard. I've already sent the longboats to search the bay. I hope it turns out our baron is tough enough not to give up so easily.";
				link.l1 = "That's bad, but it's too early to mourn him. Marcus wouldn't give up on us that easily. Let's wait for the results of the search.";
			}
			link.l1.go = "Svenson_39";
		break;
		
		case "Svenson_38":
			if (CheckAttribute(pchar, "questTemp.LongHappy.TerraxShipSink"))
			{
				dialog.text = "Marcus swam to shore after his ship was sunk. Well, you know, Tyrex is not one to drown over such a trifle. Now he's somewhere in the town. Probably shaking the souls out of the sentries who overlooked all this filth. An iron man, no doubt.";
				link.l1 = "Iron would sink. I suppose our baron is made of a material still unknown to science, haha!";
			}
			else
			{
				dialog.text = "Marcus is as steady as ever. As soon as he went ashore, he immediately began to shake the souls out of the sentries who had overlooked all this filth. He still manages to command the restoration of order in the town. An iron man, no doubt.";
				link.l1 = "Iron is softer. I suppose our baron is made of a metal still unknown to science, haha!";
			}
			link.l1.go = "Svenson_39";
		break;
		
		case "Svenson_39":
			dialog.text = "That's all. Well, it could have been worse. Even your wedding, Charles, turned out... combative. The important thing is that you are both alive. A small piece of advice, in general... love... and don't you dare give up fighting for it!";
			link.l1 = "Thank you, Jan. Thank you, all of you... I must admit, I forgot that we began with a celebration.";
			link.l1.go = "Svenson_40";
		break;
		
		case "Svenson_40":
			dialog.text = "So, here is a reminder.";
			link.l1 = "Yeah, that was a... wild party.";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Rum")) link.l1.go = "Svenson_41";
			else link.l1.go = "Svenson_43";
		break;
		
		case "Svenson_41":
			dialog.text = "Oh yes, it certainly was, wait a minute. There is something - you seemed to have an Indian man with you, right, always by your side or looking around as if someone was aiming at you. Strangely dressed, and very noticeable in big crowds.";
			link.l1 = "Yes, Tichingitu, he disappeared at the very beginning of this mess. I'm starting to worry, to be honest. Do you know anything?";
			link.l1.go = "Svenson_42";
		break;
		
		case "Svenson_42":
			pchar.questTemp.LongHappy.Tichingitu_Wife = "true";
			dialog.text = "Seems so. Our bartender was making a fuss that his niece had been abducted, supposedly before the attack. He says they saw her with some sort of Indian, who carried her on his shoulder along the shore east of the town. I didn't notice any Indians among Kindman's scum, but I remembered yours when I heard it, so I kept quiet. You should go and look for him or something, before he gets into trouble. Because the bartender threatens to kill him if he finds him first. He's a good fellow, but for his niece he'd tear off anyone's head.";
			link.l1 = "Yup, I know the kind, don't you worry, and thanks, Jan, I'll go and search for him right away.";
			link.l1.go = "Svenson_43";
		break;
		
		case "Svenson_43":
			dialog.text = "Well, in general, something like this... Sorry, I'm rubbish at speeches. And now it's even worse - this night has drained everyone dry. We all should rest at least a day - then we will decide how to proceed.";
			link.l1 = "You're right, Jan. I should go, I need to clear my head.";
			link.l1.go = "Svenson_44";
		break;
		
		case "Svenson_44":
			DialogExit();
			DoQuestReloadToLocation("Pirates_town", "reload", "reload3", "LongHappy_WifeInTown");
		break;
		
		case "Svenson_45":
			dialog.text = "Looking good, Charles. Did you sleep well?";
			link.l1 = "Yes, we were given a cosy house on the outskirts of town. I even thought I had dreamed all the madness that happened yesterday. And here you are, Jan, you look dreadful. What else has happened?";
			link.l1.go = "Svenson_46";
		break;
		
		case "Svenson_46":
			dialog.text = "Oh no, it's nothing, I just haven't slept yet. You know... tidying up the city after everything that happened here is a hard task.";
			link.l1 = "How are Dannie and Nathan? Where is everyone?";
			link.l1.go = "Svenson_47";
		break;
		
		case "Svenson_47":
			dialog.text = "Resting. Don't disturb them, Dannie warned everyone that she's taken guns to bed today... Dodson is at sea, gone to find more ships to secure the island so this won't happen again, others are burying the departed in the north of the island.";
			link.l1 = "";
			link.l1.go = "Svenson_48";
		break;
		
		case "Svenson_48":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner") && !CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Free")) dialog.text = "Marcus hasn't been found yet, but we can handle it, don't worry. You have done so much for all of us, so don't trouble yourself. Tyrax will return sooner or later - we will find him.";
			else dialog.text = "Marcus finished here and sped off on someone’s lugger to Hispaniola. He needs to resolve some issues that arose after Barbazon’s death. He sends his regards and best wishes to you and your wife.";
			link.l1 = "";
			link.l1.go = "Svenson_49";
		break;
		
		case "Svenson_49":
			dialog.text = "Well, the Brethren have withstood this blow. Soon, we shall rise even stronger than before. Kindman and Jackman have been undermining our unity for too long; now they're gone, and I feel in my heart that we shall make the Caribbean tremble more than once. The Golden Age is coming for those to whom laws and kings are no friends, remember my words.";
			link.l1 = "That would be nice. I'm not sure I could endure the Old World any longer. I never imagined, when I came here, that I would fall in love with the freedom of the sea, these wild colours of sunsets and sunrises, that I would find the best woman in the world and... friends I would trust with my life.";
			link.l1.go = "Svenson_50";
		break;
		
		case "Svenson_50":
			dialog.text = "Well, you know the course, just make up your mind. In our homes, you are always welcome.";
			link.l1 = "Thanks, Jan. It means a lot to me.";
			if (CheckAttribute(pchar, "questTemp.Mtraxx")) 
			{
				if (pchar.questTemp.Mtraxx == "full_complete_end" || pchar.questTemp.Mtraxx == "full_complete") link.l1.go = "Svenson_51";
				else link.l1.go = "Svenson_54";
			}		
			else link.l1.go = "Svenson_54";
		break;
		
		case "Svenson_51":
			pchar.questTemp.LongHappy.Baron = "true";
			dialog.text = "But first, there's something important left. Charles, while you were sleeping, we got together and decided\nSince Barbazon is dead, the Brethren needs a new baron. Since there was a clear majority of us here, and the decision was made unanimously, here it is. Congratulations - you are the new Baron of Le François. But wait ... I understand - you are a worldly man, and you have no time to manage affairs in this fine place, so we've put a trusted person there, and you can do as you please. Just remember - your voice now counts in the Brethren.";
			link.l1 = "Jan, I... I am speechless... This is a great honour, I don't even know...";
			link.l1.go = "Svenson_52";
		break;
		
		case "Svenson_52":
			dialog.text = "C'mon! You proved yourself perfectly back then with Tyrex, and then with the whole story of Sharp's legacy. You are a blessing from God himself. For you, nothing will change – do as planned, and in your absence, your man will take charge of all affairs.\nThere is one promising fellow, Jan David, he's one of the Buccaneers. A Frenchman, an honest chap, with a brilliant mind and he knows how to use it, just like you. But it will take some time for me to find him – it seems he was captured by the Spaniards, but this can be solved, don't worry. I will make sure that he sends your share to you as soon as he gets comfortable with the business.";
			link.l1 = "I really didn't expect things to turn out this way. Well, since you've already decided, so be it. The Pirate Baron Charles de Maure!";
			link.l1.go = "Svenson_53";
		break;
		
		case "Svenson_53":
			dialog.text = "Long live the baron! If anyone deserves the name, it should be you. Wear it with pride, and don't forget – you are one of us now, no matter how beautiful the uniform you wear, here, right beneath it, beats the heart of a true pirate.";
			link.l1 = "I don't know, perhaps you're exaggerating... But I will do everything I can to justify your trust.";
			link.l1.go = "Svenson_54";
		break;
		
		case "Svenson_54":
			dialog.text = "What are you going to do now? Go back to Europe, back to your father, to introduce him to your wife?";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") || CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				link.l1 = "Yes, but first I must say farewell to someone... You know what I mean.";
				link.l1.go = "Svenson_56";
			}
			else	
			{
				link.l1 = "Maybe not so soon. Once again I'll sail through the archipelago, I want to breathe this air of freedom for the last time.";
				link.l1.go = "Svenson_55";
			}
		break;
		
		case "Svenson_55":
			dialog.text = "Well, you've got a ship, you can sail home whenever you wish.";
			link.l1 = "I hope so. Thanks Jan, thanks to all of you and see you later, my old friend! Say hello to the Hawks and Shark!";
			link.l1.go = "Svenson_58";
		break;
		
		case "Svenson_56":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") && CheckAttribute(pchar, "questTemp.LongHappy.Jino_died")) sTemp = "They deserve";
			else sTemp = "He deserve";
			dialog.text = "Yes, it's hard, but we have to do this. To the sea?";
			link.l1 = "No, I will sail to Antigua. "+sTemp+" to rest in peace in a place that became our home, for a while.";
			link.l1.go = "Svenson_57";
		break;
		
		case "Svenson_57":
			dialog.text = "Say a few kind words from me too. And don't worry - we can handle it on our own from now on. All is going to be fine.";
			link.l1 = "Thanks, Jan. See you soon, my old friend! Give my best to the Hawks and the Shark!... Well, Antigua it is.";
			link.l1.go = "Svenson_58";
		break;
		
		case "Svenson_58":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_IslaMarryComplete", 10.0);
		break;
		
		case "Svenson_":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "Svenson_";
		break;
		
		// Глэдис
		case "Gladis":
			dialog.text = "Young man, you have grown even more in my eyes today. You have done so much for Helen that no words of gratitude will be enough. I only hope that you will continue to take care of her. If her father were alive and saw this, how happy he would have been... oh, I am sorry.";
			link.l1 = "It's all right, Gladys. You crossed the archipelago to support Helen today. We both truly appreciate your visit with Jan, thank you.";
			link.l1.go = "Guests_block";
		break;
		
		// Форже - патер Мэри
		case "forge":
			dialog.text = "Monsieur de Maure, I apologise for the familiarity, but I shall say it this way - Charles, my friend, I am sincerely happy for you! If there is anything I can do for you or your bride, just say the word!";
			link.l1 = "I thank you, Baron, I am so happy, and as for the vineyards my father wanted as a dowry, I believe I can redeem myself – fortunately, my financial situation during my time in the New World has considerably improved.";
			link.l1.go = "forge_1";
		break;
		
		case "forge_1":
			dialog.text = "Yes, I suppose you can afford just about anything you want, Charles. Excuse me, but I shall make my contribution as the representative father - Today, I am going to write to my good friend, the Minister of Finance. Your chosen one will be granted a title of nobility, and, I think, we shall find a good estate for her, let us say in Gascony, among those which were seized for debts, and assign it to her retroactively. So no one will dare to say that the Chevalier de Monper found a wife of low position!";
			link.l1 = "I don't think I am concerned about such gossip, but thanks, Baron. Still, you shouldn't";
			link.l1.go = "forge_2";
		break;
		
		case "forge_2":
			dialog.text = "I most certainly should! Now go, Charles, share your attention with the rest of the guests. And once again, accept my most sincere congratulations!";
			link.l1 = "My wife and I thank you. See you, Baron.";
			link.l1.go = "Guests_block";
		break;
		
		// Форже - патер ГГ
		case "forge_3":
			dialog.text = "Monsieur de Maure, I apologise for the familiarity, but I shall say it this way – Charles, my friend, I am sincerely happy for you! If there is anything I can do for you or your bride, just say the word!";
			link.l1 = "Thank you, Baron, but you've already done so much for me. It is enough for us that you have responded to the invitation.";
			link.l1.go = "forge_4";
		break;
		
		case "forge_4":
			dialog.text = "How could I not have responded, Charles! But listen – I want to give you and your beautiful bride a worthy gift, but I can't think of anything you couldn't obtain yourself with money or a sword. Therefore, I shall write to my friend, the Minister of Finance in Paris, and by the time you arrive in Europe, you will be awaited to sign the royal rescript elevating the name of de Monper to the title of Barons de Monper! No, not a word, this is the least I can do for you.";
			link.l1 = "I don't even know what to say, Baron... Father will be so pleased. Thank you, truly.";
			link.l1.go = "Guests_block";
		break;
		
		// Форже гость
		case "forge_5":
			dialog.text = "Charles, please, accept my sincere congratulations! Your chosen one is truly a marvel! I believe today colonial fashion has received a strong ... jab in a new direction. Your originality has always fascinated me! May you and your beautiful half live happily ever after!";
			link.l1 = "Thank you, Baron. You have honoured us with your visit.";
			link.l1.go = "forge_6";
		break;
		
		case "forge_6":
			dialog.text = "How could I stay away, my friend? We've been through a lot together and I'm proud to call you my friend, Charles. Remember - my doors are always open to you, no matter what happens.";
			link.l1 = "As the doors of the de Monper family will always be open to you, Baron.";
			link.l1.go = "Guests_block";
		break;
		
		// Пуанси патер Мэри
		case "puancie":
			dialog.text = "Charles, my friend, this is a very important day, and I am glad that you have invited me to share it with you. You and I have come a long and difficult way, and to become the representative father of mademoiselle... please, forgive me - Madame de Maure, it is an honour for me, believe me. With all my heart, I wish you happiness! And please, let me know when you are going to Europe – I, as the representative father of your chosen one, will send your father all the necessary wedding gifts. Believe me, no one will say that the Chevalier de Monper's bride is poor or unworthy!";
			link.l1 = "If I may ask, Chevalier, a couple of miles north of the Monper estate, there are good vineyards, they belong to the La Brigne family and I...";
			link.l1.go = "puancie_1";
		break;
		
		case "puancie_1":
			dialog.text = "Not another word, my friend, not another word! I will immediately write to my authorised representative in Lyon – by the time you arrive, these vineyards will be given to your chosen one.";
			link.l1 = "Thank you, Chevalier. You are right – our... friendship has been through... a lot. But I'm truly glad that you shared this day with us. See you, and thanks again!";
			link.l1.go = "Guests_block";
		break;
		
		// Пуанси патер ГГ
		case "puancie_2":
			dialog.text = "Charles, my friend, this is a very important day, and I am glad that you have invited me to share it with you. We have come a long and difficult way, and to stand witness today at your wedding is an honour for me. With all my heart, I wish you happiness! And let me know when you are going to Europe – I will send your father fitting wedding gifts.";
			link.l1 = "There is no need for this, Chevalier. Thank you for responding to my invitation.";
			link.l1.go = "puancie_3";
		break;
		
		case "puancie_3":
			Log_Info("You have got gems");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "jewelry2", 50);
			TakeNItems(pchar, "jewelry3", 50);
			TakeNItems(pchar, "jewelry4", 50);
			dialog.text = "As I said - it's an honour for me! But wait, my friend, I would like to present something to you on this occasion - I am sure this will please both you and your chosen one. Beautiful stones from our mines in New Guiana - have them set in a fine frame and Madame de Maure will shine even at the royal reception! If you can persuade her to wear a dress, of course...";
			link.l1 = "Oh, you really shouldn't, chevalier. Thank you again.";
			link.l1.go = "Guests_block";
		break;
		
		// Пуанси гость
		case "puancie_4":
			dialog.text = "Charles, my friend, let me congratulate you! We have come a long and difficult way, and I am sincerely glad to be here today. Our Lord is witness – you deserve your happiness! Cherish it and protect it – wishing you many happy years to come!";
			link.l1 = "Thank you, Chevalier, my wife and I are very grateful.";
			link.l1.go = "Guests_block";
		break;
		
		// Фадей патер
		case "fadey":
			dialog.text = "Charles, what a celebration, and so many important people! Let me wholeheartedly wish you happiness, good health, and children to bring you joy! As we say - 'gor'ko'!";
			link.l1 = "Thank you, Fadey, you have honoured me by agreeing to come.";
			link.l1.go = "fadey_1";
		break;
		
		case "fadey_1":
			dialog.text = "But I don't quite understand why there are so many people here, as if we're not getting married but striking some grand trade deal, and still not enough beer or vodka for my liking... haha! Well, I'm joking, Charles, why have you gone completely pale? Give me a hug, you married captain!";
			link.l1 = "Shiver me timbers... Fadey, you're as strong as a bear!";
			if (CheckAttribute(pchar, "questTemp.Persian"))
			{
				if (pchar.questTemp.Persian == "time" || pchar.questTemp.Persian == "end") link.l1.go = "fadey_2";
				else link.l1.go = "Guests_block";
			}
			else link.l1.go = "Guests_block";
		break;
		
		case "fadey_2":
			GiveItem2Character(pchar, "blade_22");
			GiveItem2Character(pchar, "blade_23");
			GiveItem2Character(pchar, "blade_24");
			Log_Info("You got three Persian sabres");
			PlaySound("interface\important_item.wav");
			dialog.text = "Wait, Charles, don't go just yet - it's not right for a guest to attend a wedding without gifts. Here, take these. I know you tried to find all these blades, and some of them you clearly liked. So accept them - hang them in your family estate and remember Fadey Moskovit with a kind word!";
			link.l1 = "This is a real gift! Thank you, Fadey. These are indeed wonderful weapons, and they will take their rightful place in the de Monper estate, I promise!";
			link.l1.go = "Guests_block";
		break;
		
		// Фадей гость
		case "fadey_3":
			dialog.text = "Charles, what a celebration, and so many important people! Let me wholeheartedly wish you happiness and good health, and children to bring you joy! As we say - 'gor'ko'! Give me a hug, you married captain!";
			link.l1 = "Shiver me timbers... Fadey, you're as strong as a bear!";
			link.l1.go = "Guests_block";
		break;
		
		// Проспер Трубаль
		case "Prosper":
			dialog.text = "Charles, I couldn't miss it, I congratulate you and your chosen one with all my heart! Be happy! You know, a couple of months ago I married my daughter to a good man, and they are in love, but honestly, I was upset that it wasn't you... Well, alright... what am I even talking about - congratulations! May you live happily ever after!";
			link.l1 = "Thanks, Prosper, I'm glad you came.";
			link.l1.go = "Guests_block";
		break;
		
		// Тичингиту
		case "Tichingitu":
			dialog.text = "Congratulations, captain! A strange rite, but beautiful – Tichingitu liked it. Although, the captain should simply abduct his squaw and send a ransom to her relatives.";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) link.l1 = "Well, in a way, I did, and it's just a formality. Thank you, my friend!";
			else link.l1 = "Well, in a way, I did, and it's just a formality. Thank you, my friend! You and I will talk more in Sharptown - there will be much less official business and more genuine fun, I promise!";
			link.l1.go = "Tichingitu_1";
		break;
		
		case "Tichingitu_1":
			dialog.text = "Fire water again? Tichingitu can't say he likes it. Maybe a celebratory boarding would be better, or at least dancing around a bonfire?";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) link.l1 = "I do hope it won't come to dancing around bonfires long before the end, and I'd rather avoid boarding. Fine, be patient – just a bit left, and we'll head straight to the tavern.";
			else link.l1 = "I'm afraid it will come to dancing around bonfires long before the end, and I would rather avoid boarding. Fine, be patient – just a bit left, and we will sail to Sharptown immediately.";
			link.l1.go = "Guests_block";
		break;
		
		case "Tichingitu_2":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Captain, congratulations again! Tichingitu enjoys this celebration more than the last one. The captain knows how to choose friends - there is more sincerity here, less hypocrisy, and less false hair.";
			link.l1 = "Thank you, my friend! Just don't drink the firewater – it's very strong here.";
			link.l1.go = "Tichingitu_4";
			link.l2 = "Thank you, my friend! Shall we have a drink? I know you don't like it, but today you should give it a try!";
			link.l2.go = "Tichingitu_3";
		break;
		
		case "Tichingitu_3":
			pchar.questTemp.LongHappy.Tichingitu_Rum = "true";
			dialog.text = "Tichingitu doesn't like firewater, but if the captain insists, today it is possible. To your happiness, and your squaw!";
			link.l1 = "And to you, Tichingitu! To your friendship and loyalty!";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_4":
			DialogExit();
			npchar.dialog.currentnode = "Tichingitu_4_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				sld = characterFromId("Mary");
				sld.dialog.currentnode = "LongHappy_57";
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else 
			{
				if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
			}
		break;
		
		case "Tichingitu_4_1":
			dialog.text = "Nice party, captain.";
			link.l1 = "I'm glad you're satisfied.";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_5":
			dialog.text = "Captain, have you come out to look at the stars? The night promises to be very beautiful. Tichingitu loves the night over the sea. It is very peaceful.";
			link.l1 = "Glad to see you’re still standing, my friend! Nathaniel and I need your help – the lads at the tavern are out of drinks, and we need to bring a few crates of liquor from the stock under the shipyard.";
			link.l1.go = "Tichingitu_6";
		break;
		
		case "Tichingitu_6":
			dialog.text = "Lead on, captain. Tichingitu follows you, as always.";
			link.l1 = "Alright, let's go!";
			link.l1.go = "Tichingitu_7";
		break;
		
		case "Tichingitu_7":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
		break;
		
		case "Tichingitu_8":
			dialog.text = "Captain, there are people, and they are armed. Tichingitu hears the rattling of their weapons, and it's getting louder by the second. I don't like it. Let's hide.";
			link.l1 = "Come on, mate - this is Sharptown, here even people go to the restroom armed with pistols. Hey Nathan... well, damn! That's one bottle gone. If it goes on like this, you'll break all the bottles! Stand on your feet, damn you! Ha-ha!";
			link.l1.go = "Tichingitu_9";
		break;
		
		case "Tichingitu_9":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LongHappy_SetBandosInDungeon();
		break;
		
		case "Tichingitu_10":
			dialog.text = "Captain... you... Tichingitu's head is spinning like a mast in a storm. What happened?";
			link.l1 = "I was about to ask you the same! Where have you been all this time?!";
			link.l1.go = "Tichingitu_11";
		break;
		
		case "Tichingitu_11":
			dialog.text = "Tichingitu woke up an hour ago because of the cries of this girl. She ran along the beach almost naked, screaming something about abductors and savages... But there is nobody here except us. Do you have any water? Not the fiery kind again, Tichingitu hates it now?";
			link.l1 = "There was a flask somewhere, if I didn't lose it in battle... here you go. How did you manage to do this? Her uncle, a local bartender, is looking for the Indian who abducted his niece, and is threatening to tear him apart, feathered empty head and all. Who do you think he's talking about?";
			link.l1.go = "Tichingitu_12";
		break;
		
		case "Tichingitu_12":
			dialog.text = "Tichingitu remembered. She was helping the Forest Devil at the tavern with the wedding. We drank firewater with you, and Tichingitu wanted more. And then, this squaw... she was so pretty and... Captain, I think I remembered! Tichingitu wanted to marry her... He wanted to build a canoe and take her away... Spirits of mercy! Very bad people came up with firewater. Perhaps demons or evil spirits! Tichingitu will never again ...";
			link.l1 = "To take her away? Build a canoe?! Ahah, you are a romantic, my friend... Ha-ha... ha-ha-ha-ha-ha-ha oh, I can't stop... I can't stop laughing!";
			link.l1.go = "Tichingitu_13";
		break;
		
		case "Tichingitu_13":
			dialog.text = "Captain, Tichingitu has stolen the squaw, yes... but, could we, well... not get married now? She is... loud, like a parrot, and... not so beautiful.";
			link.l1 = "Yes, my friend, women who have fun all night long are a miserable sight in the morning. Don't worry, hero-lover, we'll come up with something. Come on, we have to go back to Sharptown, you missed your holiday boarding...";
			link.l1.go = "Tichingitu_14";
		break;
		
		case "Tichingitu_14":
			dialog.text = "A boarding? The captain mentioned a battle before. Thoughts still don't obey Tichingitu. What happened in the town?";
			link.l1 = "A real battle on land and at sea. The guns were firing all night, I suppose, they were probably heard even in San Jose. However, you were busy with another 'battle', it's all right, I understand... Come on, I'll tell you everything along the way.";
			link.l1.go = "Tichingitu_15";
		break;
		
		case "Tichingitu_15":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			sld = characterFromId("LH_waitress");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			pchar.quest.longhappy_shoregirl1.win_condition.l1 = "location";
			pchar.quest.longhappy_shoregirl1.win_condition.l1.location = "Pirates_town";
			pchar.quest.longhappy_shoregirl1.function = "LongHappy_ReturnShoreGirl";
		break;
		
		case "Tichingitu_16":
			dialog.text = "Thank you, captain... Tichingitu will never...";
			link.l1 = "Yeah, 'the stallion from the distant plains', you definitely shouldn't drink any more. Go get some sleep. I'm already about to drop from exhaustion myself.";
			link.l1.go = "Tichingitu_17";
		break;
		
		case "Tichingitu_17":
			DialogExit();
			npchar.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
			LAi_SetImmortal(npchar, false);
			npchar.OfficerWantToGo.DontGo = true;
			npchar.CompanionDisable = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			LAi_SetOfficerType(npchar);
			npchar.Payment = true;
			npchar.DontClearDead = true;
			npchar.dialog.currentnode = "Tichingitu_officer";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_55";
			ChangeCharacterAddressGroup(sld, "Pirates_town", "goto", "goto2");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Tichingitu_18":
			dialog.text = "Captain, congratulations once again! Tichingitu enjoys this celebration more than the last. The captain knows how to choose friends – there is more sincerity here, less hypocrisy, and fewer wigs.";
			link.l1 = "And much more firewater. By the way, will you have a drink with me? I know you don't like it, but we have an unusual occasion!";
			link.l1.go = "Tichingitu_19";
		break;
		
		case "Tichingitu_19":
			dialog.text = "Tichingitu doesn't like firewater, but if the captain insists, today it can be done. To your happiness, and your squaw! May you walk the same path, and may the sun and moon always shine upon it.";
			link.l1 = "Thank you, my friend. Cheers to you, Tichingitu! To our friendship!";
			link.l1.go = "Tichingitu_4";
		break;
		
		// губернаторы
		// Сен Пьер
		case "FortFrance_Mayor":
			if (pchar.questTemp.GoldenGirl == "end")
			{
				dialog.text = "Great ... celebration, I'm very happy for you, Charles. Although, I still don't understand you... To hold a priceless rose in your hands and exchange it for... a wildflower. But the heart wants what it wants... Be happy, my friend. May you live happily ever after!";
				link.l1 = "In the flower that you hold, the most beautiful thing is your feeling for it. Without it, it's just a lump of fading flesh. Glad you came in, Your Grace.";
				link.l1.go = "FortFrance_Mayor_1";
			}
			else
			{
				dialog.text = "A wonderful day, my friend, and a wonderful occasion! Accept my sincere congratulations! I was married three times, and each time I trembled as if it were the first, ah, youth...";
				link.l1 = "Monsieur, you are still far from old age, do not be discouraged. Thanks for coming, Jacques!";
				link.l1.go = "Guests_block";
			}
		break;
		
		case "FortFrance_Mayor_1":
			dialog.text = "Wait, Charles. You misunderstood me, I am sincerely happy with all my heart! And yes... here, take it. Our mutual... friend specifically requested that you receive it today.";
			link.l1 = "I suspect I know who it's from. Thank you, and see you soon.";
			link.l1.go = "Guests_block";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
				{
					if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex")) AddQuestRecordInfo("Letter_Marquesa", "2-1");
					else AddQuestRecordInfo("Letter_Marquesa", "1-1");
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex")) AddQuestRecordInfo("Letter_Marquesa", "4-1");
					else AddQuestRecordInfo("Letter_Marquesa", "3-1");
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
				{
					if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex")) AddQuestRecordInfo("Letter_Marquesa", "2");
					else AddQuestRecordInfo("Letter_Marquesa", "1");
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex")) AddQuestRecordInfo("Letter_Marquesa", "4");
					else AddQuestRecordInfo("Letter_Marquesa", "3");
				}
			}
		break;
		
		// Бас Тер
		case "BasTer_Mayor":
			dialog.text = "A delightful ceremony, isn't it, Charles? I am sincerely happy for you! On behalf of myself and all the citizens of Basse-Terre, I offer our congratulations to you and your... charming wife. You make a wonderful couple! May you live happily ever after!";
			link.l1 = "Thank you, Your Grace. I'm glad you liked it.";
			link.l1.go = "Guests_block";
		break;
		
		// Порт Принс
		case "PortPax_Mayor":
			dialog.text = "Such wonderful service, monsieur de Maure, simply wonderful! And the bride is so... original in this attire. On behalf of all the residents of our city - accept my most sincere congratulations! Wishing you many happy years to come!";
			link.l1 = "Thank you, Your Grace.";
			link.l1.go = "Guests_block";
		break;
		
		// Тортуга
		case "Tortuga_Mayor":
			dialog.text = "So charming – you and your bride, monsieur de Maure, looked so unique! However, you are an extraordinary man. I wish you a long and happy married life. May you live happily ever after!";
			link.l1 = "I am very grateful to you, Your Grace.";
			link.l1.go = "Guests_block";
		break;
		
		// д'Ойли
		case "PortRoyal_Mayor":
			PlaySound("Voice\English\LE\Doily\Edvard_Doily_03.wav");
			dialog.text = "For the sake of your wedding, it was worth crossing the Caribbean! Congratulations, captain, on behalf of the inhabitants of all the English colonies! You and your bride—sorry, your wife now—make a wonderful couple!";
			link.l1 = "Thank you for your visit and your kind words, Colonel!";
			link.l1.go = "Guests_block";
		break;
		
		// Исла Тесоро
		// Тиракс
		case "Terrax":
			if (CheckAttribute(pchar, "questTemp.Mtraxx")) 
			{
				if (pchar.questTemp.Mtraxx == "full_complete_end" || pchar.questTemp.Mtraxx == "full_complete")
				{
					dialog.text = "And what is this married dandy doing on my pirate beach, huh?! Tell me, monsieur, what have you done with my old friend - the harsh Pirate Charlie Prince?";
					link.l1 = "Charlie Prince is dead, you remember it, Marcus... Ha-ha-ha, come here, you sea devil! I'm glad to see you! How are you guys doing here, has everyone gathered?";
					link.l1.go = "Terrax_1_1";
				}
				else // 28-03-20
				{
					dialog.text = "And what is this married dandy doing on my pirate beach, huh?! Tell me, monsieur, what have you done with my old friend - the harsh Captain Charles de Maure?";
					link.l1 = "Ah, Marcus, I'm glad to see you too! How are you all doing here, has everyone gathered?";
					link.l1.go = "Terrax_1";
				}
			}
			else
			{
				dialog.text = "And what is this married dandy doing on my pirate beach, huh?! Tell me, monsieur, what have you done with my old friend - the harsh Captain Charles de Maure?";
				link.l1 = "Ah, Marcus, I'm glad to see you too! How are you all doing here, has everyone gathered?";
				link.l1.go = "Terrax_1";
			}
		break;
		
		case "Terrax_1":
			dialog.text = "Yes, the Forest Devil arrived just yesterday and immediately started giving orders - so the guests are here and everything is ready for the celebration. Your vessel was spotted near the reefs, and the lads couldn't resist - they rushed into the tavern and, most likely, have already opened that Hawk's barrel. Hurry up, maybe we still have a chance to share a glass - Nathaniel boasted that this was some kind of special rum!";
			link.l1 = "Now this is how we're doing it - straight from the ship to the party! I'll wait for my better half and we're right behind you, Marcus!";
			link.l1.go = "Terrax_2";
		break;
		
		case "Terrax_1_1":
			dialog.text = "Yes, the Forest Devil arrived just yesterday and immediately started giving orders - so the guests are here and everything is ready for the celebration. Your vessel was spotted near the reefs, and the lads couldn't resist - they rushed into the tavern and, most likely, have already opened that Hawk's barrel. Hurry up, maybe we still have a chance to drink a glass - Nathaniel boasted that this was some kind of special rum!";
			link.l1 = "Now this is how we're doing it - from the ship straight to the party! I'll wait for my better half and we're right behind you, Marcus!";
			link.l1.go = "Terrax_2";
		break;
		
		case "Terrax_2":
			DialogExit();
			DoQuestReloadToLocation("Pirates_tavern", "reload", "reload1", "LongHappy_IslaTesoroTavern");
		break;
		
		case "Terrax_3":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Married Charles de Maure - still can't get used to it... First Svenson, now you - then what? Pastor Marlow, or Jacques the Kindman?";
			link.l1 = "You forgot about the Hawks. And what about you, Marcus? Aren't you tired of being a lone sea wolf?";
			link.l1.go = "Terrax_4";
		break;
		
		case "Terrax_4":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				dialog.text = "Dannie and Nathan are a long-standing case - I have already come to terms with it, but you surprised me, I must say! However, the pupil of the Forest Devil is a beauty - truly, always ready with both words and a pistol, and she can weather any storm. It's unlikely you could find yourself a more worthy woman. You're a lucky one, captain - take care of her!";
			}
			else
			{
				dialog.text = "Dannie and Nathan are a long-standing case - I have already come to terms with this, but you surprised me, I must say! Although, as I have heard, your Mary knows a lot about swords and clearly knows how to use them - my respects! A true companion in arms. I'll tell you a secret, for the sake of such a girl, I myself might reconsider my convictions as a bachelor. You are a lucky man, captain - take care of her!";
			}
			link.l1 = "I know, she is a miracle and I am once again in seventh heaven with happiness - just like in those days when we first met!";
			link.l1.go = "Terrax_5";
		break;
		
		case "Terrax_5":
			dialog.text = "Well then, a toast!... To love!... But not to the one that drives us across the threshold and to the horizon!... But to the one that awaits us at this threshold! To the love that draws us back, even from the ends of the earth and from the golden mountains! Live with it and be happy!";
			link.l1 = "Great toast, Marcus, thank you!";
			link.l1.go = "Terrax_6";
		break;
		
		case "Terrax_6_1":
			dialog.text = "Cheers, to your wedding, mate!";
			link.l1 = "Thank you, Marcus...";
			link.l1.go = "Terrax_6";
		break;
		
		case "Terrax_6":
			DialogExit();
			npchar.dialog.currentnode = "Terrax_6_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Terrax_7":
			dialog.text = "Jacques? This is definitely not good...";
			link.l1 = "Marcus, do you think...";
			link.l1.go = "Terrax_8";
		break;
		
		case "Terrax_8":
			dialog.text = "There's no time! They're behind the doors! Everyone, to arms!";
			link.l1 = "Here we go!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_TavernFight");
		break;
		
		case "Terrax_9":
			dialog.text = "I don't remember the last time I had so much fun at a party! It's not over yet! Do you hear that? Someone's shooting outside! Let us litter the streets with their blood!";
			link.l1 = "Wait! Who the hell are they!? And what the bloody hell do they even want?!";
			link.l1.go = "Terrax_10";
		break;
		
		case "Terrax_10":
			DialogExit();
			sld = characterFromId("Svenson");
			sld.dialog.currentnode = "Svenson_20";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		// Натаниэль Хоук
		case "Nathaniel":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Married Captain de Maure, rarely have I encountered more genuine reasons for a toast. Raise a glass – this is no ordinary cabbage drink. It's infused with black tea from East India and seasoned with real Persian spices!";
			link.l1 = "And I've been wondering why it burns in my throat as if I drank molten lead. Well, Nathan, cheers...";
			link.l1.go = "Nathaniel_1";
		break;
		
		case "Nathaniel_1":
			dialog.text = "Wait, first a toast! Hey, gentlemen, raise your mugs! Today, our friend and associate Charles de Maure is setting out on the path of family life. Accept from us our deepest condolen... oh, Dannie, please, put down the gun! Congratulations, of course! Now, you are the sails of the same ship, so steer her through any storms to the most fertile shores!";
			link.l1 = "Thank you, Nathan, sincerely. You and Danielle are an example for us to follow.";
			link.l1.go = "Nathaniel_2";
		break;
		
		case "Nathaniel_2":
			dialog.text = "Nice to hear. My wife and I may not be the best couple in the world, but we are happy together, and you have done so much for us, so if you ask me, you are a part of my family, and I will be here for you whenever you need me. Be happy, and please have a drink!";
			link.l1 = "Let's drink then! Oh... this rum should have its place in the arsenal of the Holy Inquisition. Damn! It burns all the way... aghhh! Whew!... I like it!";
			link.l1.go = "Nathaniel_3";
		break;
		
		case "Nathaniel_3":
			DialogExit();
			npchar.dialog.currentnode = "Nathaniel_3_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Nathaniel_3_1":
			dialog.text = "You look so much like Dannie and me twenty years ago!";
			link.l1 = "One more cup, Nathan!";
			link.l1.go = "Nathaniel_3";
		break;
		
		case "Nathaniel_4":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "What!? Did Jan send you down to the cellars to fetch wine? Let's take a walk, I'll give you a hand, and a bit of fresh air will do us good.";
			link.l1 = "But where are Dannie and "+sld.name+"? Jan told me they had gone to have a talk.";
			link.l1.go = "Nathaniel_5";
		break;
		
		case "Nathaniel_5":
			dialog.text = "Yes, Dannie knows that the presence of even the best girl-in-arms still will not give the gentlemen of fortune time to relax to the fullest. So they listened to all the compliments they received and went to the residence to let the men have their fun.";
			link.l1 = "Well then, let's move! I managed to drink a couple of mugs, but damn me, now it's really time to get properly drunk!";
			link.l1.go = "Nathaniel_6";
		break;
		
		case "Nathaniel_6":
			DialogExit();
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;//открыть локацию
			bDisableFastReload = true;//закрыть переход
			pchar.quest.longhappy_isla_vine.win_condition.l1 = "location";
			pchar.quest.longhappy_isla_vine.win_condition.l1.location = "Pirates_town";
			pchar.quest.longhappy_isla_vine.function = "LongHappy_IslaTesoroToAlexus";
		break;
		
		case "Nathaniel_7":
			PlaySound("ambient\jail\jail_door2.wav");
			dialog.text = "So, here is the chest. We take as much as we can carry and then we go back, before this old grouch locks us in here.";
			link.l1 = "You exaggerate, Nathan. He's not so bad... Wait, did you hear that?";
			link.l1.go = "Nathaniel_8";
		break;
		
		case "Nathaniel_8":
			PlaySound("ambient\jail\jail_door2.wav");
			dialog.text = "Jan has probably found more men and sent them to help us. Damn!";
			link.l1 = "Come on, the bottles break for good luck. Take one more and let's go.";
			link.l1.go = "Nathaniel_9";
		break;
		
		case "Nathaniel_9":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Rum") && GetCharacterIndex("Tichingitu") != -1)
			{
				sld = characterFromId("Tichingitu");
				sld.dialog.currentnode = "Tichingitu_8";
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else LongHappy_SetBandosInDungeon();
		break;
		
		case "Nathaniel_10":
			dialog.text = "What the hell is going on, who are these bastards? Do you understand any of this, Charles?";
			link.l1 = "I don't know, Nathan, but one of them has run off to get help, and it sounds like I hear more footsteps. We have to get back to the tavern!";
			link.l1.go = "Nathaniel_11";
		break;
		
		case "Nathaniel_11":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;
			pchar.quest.longhappy_totavern.win_condition.l1 = "location";
			pchar.quest.longhappy_totavern.win_condition.l1.location = "Pirates_tavern";
			pchar.quest.longhappy_totavern.function = "LongHappy_TavernAlarm";
		break;
		
		case "Nathaniel_12":
			LongHappy_TownRepose();
			dialog.text = "We put these bastards down, but the guns are rumbling from the sea, do you hear? We've only got two crews ready for battle, on Marcus' frigate and Jan's corvette. Me, Dannie and the others have landed our men – wedding, after all – so Centurion is out. What about your ship? We have to decide what to do, and quickly!";
			link.l1 = "I've landed half the crew, I hope the rest are sober. But first, I have to find my wife and make sure she is all right.";
			link.l1.go = "Nathaniel_13";
		break;
		
		case "Nathaniel_13":
			dialog.text = "Yes, Dannie is also nowhere to be seen. Then here's what we'll do - Tyrex and Svenson have already rushed to the harbour, they'll reach their ships by boat. We're going to the residence for the wives, the rest should organise the defence on the shore. Can you send a few of your officers to gather people on your ship? Help there certainly won't hurt.";
			link.l1 = "Fine, everyone, let's move! Every second counts!";
			link.l1.go = "Nathaniel_14";
		break;
		
		case "Nathaniel_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Pirates_town", "reload3_back", false);
		break;
		
		case "Nathaniel_15":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Faster, upstairs! Dannie and "+sld.name+" must be there! And if these bastards hurt them...";
			link.l1 = "Don't even think about it! Upstairs! Let's go!";
			link.l1.go = "Nathaniel_16";
		break;
		
		case "Nathaniel_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Pirates_townhall", "reload1_back", true);
			pchar.quest.longhappy_isla_bedroom.win_condition.l1 = "location";
			pchar.quest.longhappy_isla_bedroom.win_condition.l1.location = "Location_reserve_04";
			pchar.quest.longhappy_isla_bedroom.function = "LongHappy_IslaTesoroBedroom";
		break;
		
		case "Nathaniel_17":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Damn it! Your friend rushed straight at the gun so that bastard wouldn't shoot the girls!";
			link.l1 = "And he took a bullet... Wait, Nathan... he's breathing! He's still alive! Damn it, I need Gino! "+sld.name+", honey, how are you?";
			link.l1.go = "Nathaniel_18";
		break;
		
		case "Nathaniel_18":
			DialogExit();
			npchar.dialog.currentnode = "Nathaniel_19";
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_7_1";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Nathaniel_18":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "We're fine, Charles! I'm going to untie her. I hear gunfire in the harbour - you and Nathan need to go there, otherwise Barbazon will destroy all our ships. Don't waste time!";
			link.l1 = "I will find Gino and send him here, he will help ... he must! "+sld.name+", dear, stay here, look after him, both of you.";
			link.l1.go = "Nathaniel_19";
		break;
		
		case "Nathaniel_19":
			dialog.text = "Charles, hurry up! Whatever you decide, time is now worth its weight in gold! If Jacques' ships break through to the shore, everything will be in vain!";
			link.l1 = "Yes, I know. Bloody bastard!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_OutOfBedroom");
		break;
		
		case "Nathaniel_20":
			dialog.text = "Faster, we have no time to talk!";
			link.l1 = "";
			link.l1.go = "Nathaniel_20_1";
		break;
		
		case "Nathaniel_20_1":
			DialogExit();
			npchar.dialog.currentnode = "Nathaniel_20";
		break;
		
		case "Nathaniel_21":
			dialog.text = "Crap! Forgive me, Charles. We were stuck upstairs, there were a dozen of those bastards... It's a pity I didn't get here in time, but I see you dealt with the situation in the best possible way.";
			link.l1 = "I can't say it was easy, but, damn, I took great pleasure in killing that 'kind man'! It's time to go ashore, Nathan. Our people are waiting for us there!";
			link.l1.go = "Nathaniel_22";
		break;
		
		case "Nathaniel_22":
			dialog.text = "Yes, we need to visit your Indian boy, finish here and then go to Sharptown.";
			link.l1 = "You are right, I'm right behind you.";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner")) link.l1.go = "Nathaniel_23";
			else link.l1.go = "Nathaniel_25";
		break;
		
		case "Nathaniel_23":
			dialog.text = "By the way, we found Marcus! He was in the cargo hold, bound and unconscious.";
			link.l1 = "He's alive?";
			link.l1.go = "Nathaniel_24";
		break;
		
		case "Nathaniel_24":
			dialog.text = "He's in rough shape, but he'll be all right. Tyrex is tougher than nails, so don't worry, he's already been transferred to your ship and has asked for a sabre.";
			link.l1 = "Finally, some good news! Fine, let's finish here and head back.";
			link.l1.go = "Nathaniel_25";
		break;
		
		case "Nathaniel_25":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LongHappy_BarbExit", -1);
		break;
		
		// Даниэль Хоук
		case "Danielle":
			dialog.text = "Hello, Charles. Let me have a look at you – you've grown even more handsome, I can't complain! Almost like Nathan, about ten years ago! Come in, don't stand on the doorstep, everyone's been waiting for you!";
			link.l1 = "Thank you, Dannie, I'm very glad to see you! I'll come to you and Nathan a little later, and then we'll talk!";
			link.l1.go = "Danielle_1";
		break;
		
		case "Danielle_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "tables", "stay1", "LongHappy_DannyNorm", -1); 
		break;
		
		case "Danielle_2":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Charles, take a seat - Nathan and I are so happy for you! Marcus, Jan and my husband have prepared something for you - but gifts will wait. For now, let me congratulate you and wish you happiness! Your beloved is truly a marvel! Tell me, you didn't manage to get her to wear a white dress there on Martinique, did you?";
			link.l1 = "Thanks, Dannie. Yes, the whole thing with the dress turned out rather amusing – I'm sure our wedding sparked plenty of scandalous rumours in high society. Everyone politely averted their eyes and pretended nothing out of the ordinary was happening. Manners and all that – but I don't care about gossip, I love her, and that's what matters most.";
			link.l1.go = "Danielle_3";
		break;
		
		case "Danielle_3":
			dialog.text = "You're absolutely right! I, too, walked to the altar, with a sword and a pair of pistols behind my sash. But it was in Port Royal, even before it became a respectable colonial residence. There was so much fun in those days, even more than on Tortuga under Levasseur, and no one was surprised... eh. However, I'm chatting all the time - go around the guests, everyone has been waiting for you here, just give me a hug!";
			link.l1 = "Ah Dannie, how could I possibly refuse you, ha-ha! You can't imagine how glad my wife and I are to see you all!";
			link.l1.go = "Danielle_4";
		break;
		
		case "Danielle_4":
			DialogExit();
			npchar.dialog.currentnode = "Danielle_4_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Danielle_4_1":
			dialog.text = "You make a lovely couple, Charles!";
			link.l1 = "Thanks, Dannie...";
			link.l1.go = "Danielle_4";
		break;
		
		case "Danielle_5":
			dialog.text = "Charles, he's right... you have no choice. I don't believe in the mercy of Jacques the Kindman if he deals with Tyrex and the rest. You know what must be done.";
			link.l1 = "";
			link.l1.go = "Danielle_6";
		break;
		
		case "Danielle_5_1":
			dialog.text = "Don't listen to him! If the Kingman has decided to do such madness, he won't spare anyone!";
			link.l1 = "";
			link.l1.go = "Danielle_6_1";
		break;
		
		case "Danielle_6":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.Dialog.currentnode = "LongHappy_39";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Danielle_6_1":
			DialogExit();
			sld = characterFromId("LH_Dussak");
			sld.dialog.currentnode = "Dussak_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Danielle_7_1":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "We're fine, Charles! I'll untie her. I hear cannons in the harbour, you and Nathan need to go there, otherwise Barbazon will sink our ships like ducklings in a barrel. You mustn't waste a minute!";
			link.l1 = "I will find Gino and send him here, he will help ... he must, damn it! "+sld.name+", dear, stay here and look after Tichingitu.";
			link.l1.go = "Danielle_8_1";
		break;
		
		case "Danielle_7":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Nathan, no!!!";
			link.l1 = "He seized the moment and rushed to the gun to cover you, Dannie... "+sld.name+", honey, how are you?";
			link.l1.go = "Danielle_8";
		break;
		
		case "Danielle_8":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.Dialog.currentnode = "LongHappy_41";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Danielle_8_1":
			DialogExit();
			sld = characterFromId("Nathaniel");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Danielle_9":
			dialog.text = "Yes, Charles, he is alive! His heart is barely beating, but he is alive! What should we do?!";
			link.l1 = "We need Gino, immediately! I'll find him and send him here, he will help... he must!";
			link.l1.go = "Danielle_10";
		break;
		
		case "Danielle_10":
			dialog.text = "Charles, we have no time! If Jacques' ships break through to the shore, everything will be in vain! My husband... he did what he had to. Now it is your turn. I will stay with him. You two should go and find Gino!";
			link.l1 = "Yes, I know. Bloody bastard, he will pay for this!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_OutOfBedroom");
		break;
		
		case "Danielle_11":
			dialog.text = "Here you are at last! Is everyone all right?";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim"))
			{
				link.l1 = "We are fine, Dannie, don't worry. Jacques is dead, his ships are at the bottom. How is Tichingitu?";
				link.l1.go = "Danielle_17";
			}
			else
			{
				link.l1 = "We are fine, Dannie, don't worry. Jacques is dead, his ships are at the bottom. How is Nathan?";
				link.l1.go = "Danielle_12";
			}
		break;
		
		case "Danielle_12":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_alive"))
			{
				dialog.text = "He's fine! Your Italian doctor is a genius! Nathan is sleeping upstairs, but, according to Gino, nothing threatens him. A week or two in bed, red wine, and, as he said, 'the visit of a lady well disposed towards him' ahem... In general - everything is fine, you saved us again, Charles, how can I thank you?";
				link.l1 = "It was Nathaniel who saved my wife and you. And I'll forever owe him for this. You can't even imagine how glad I am to hear that he is recovering. Let him rest, I'll check on you later.";
				link.l1.go = "Danielle_13";
			}
			else
			{
				dialog.text = "He's fine, the bullet passed right through, and our surgeon from the 'Centurion' was not far away. He was hiding from all this mess. So Nathan will live, a couple of weeks in bed - little trouble!";
				link.l1 = "Dannie, he shielded my wife and you from a bullet and I'll forever owe him for this. You can't even imagine how glad I am to hear that he is recovering. Let him rest, I'll check on you later.";
				link.l1.go = "Danielle_14";
			}
		break;
		
		case "Danielle_13":
			dialog.text = "Of course! But I must leave you, I have to go to my husband... Do you mind if we borrow your friend? When Nathan gets better, I will personally bring him to Antigua. The Centurion somehow miraculously survived, she only needs to recruit a new crew.";
			link.l1 = "Fine, Dannie, say hello to Gino and Nathan. I should be going.";
			link.l1.go = "Danielle_23";
		break;
		
		case "Danielle_14":
			dialog.text = "Of course, Charles, but... I have bad news. That Italian, Guineili, who was at your wedding... His body was found in a room at the tavern. I'm... I'm sorry, Charles.";
			link.l1 = "What? Gino?! No! How?";
			link.l1.go = "Danielle_15";
		break;
		
		case "Danielle_15":
			dialog.text = "I don't know, probably one of those bastards who went through the catacombs and attacked the town. Apparently, they were hiding there, waiting for a chance to escape, and found him...";
			link.l1 = "Blast! No, I don't believe it...";
			link.l1.go = "Danielle_16";
		break;
		
		case "Danielle_16":
			pchar.questTemp.LongHappy.Jino_died = "true";
			dialog.text = "I'm sorry, Charles. It was a bloody massacre, and he wasn't a fighter... If you wish, we will send his body to your ship, so you can take him home and give him a proper burial. I'm truly sorry...";
			link.l1 = "Thank you, Dannie. Give the order to have the body loaded onto a ship. I must go now... I need to think. And say hello to Nathan.";
			link.l1.go = "Danielle_23";
		break;
		
		case "Danielle_17":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_alive"))
			{
				dialog.text = "He's fine! Your Italian doctor is a genius! He's sleeping in the room upstairs, and Gino is looking after him. He says 'a week or two and he'll be fine'.";
				link.l1 = "Great news! I suppose I can't visit him just yet?";
				link.l1.go = "Danielle_18";
			}
			else
			{
				dialog.text = "I'm so sorry, Charles. I found our surgeon from the Centurion, but he couldn't do anything... Your friend died a couple of hours ago.";
				link.l1 = "Tichingitu?! No! I don't believe it!!!";
				link.l1.go = "Danielle_19";
			}
		break;
		
		case "Danielle_18":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "No, the Italian strictly forbade disturbing him, let him rest, and Gino should rest after all the worries. I even told "+sld.name+" to go out for a walk when we found out that everything was going to be fine\nAnd one more thing... your friend, he shielded me from the bullet. I don't even know how to thank him. Tell him that from now on, he is also a part of our family. And you – you saved us again, Charles!";
			link.l1 = "All is well that ends well, Dannie. Go to Nathan, he's been waiting for you, and I will take a little break here and look for my "+sld.name+".";
			link.l1.go = "Danielle_23";
		break;
		
		case "Danielle_19":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Sorry, I did everything I could, and "+sld.name+", too. He shielded us from that bullet, and I will never forget it, believe me.";
			link.l1 = "... Long ago he said that he would die for me... I suppose he never realised that he would sacrifice his life for all of us... and now he is a hero, and I shall remember him as nothing less... Where's "+sld.name+"? Is she all right?";
			link.l1.go = "Danielle_20";
		break;
		
		case "Danielle_20":
			dialog.text = "I can't say so... I mean, physically, yes. But... you know... She said she went out for a walk, to clear her mind. She probably saw you moored and will be back soon.";
			link.l1 = "Curse you, Jacques Barbazon... We should have killed him before!";
			link.l1.go = "Danielle_21";
		break;
		
		case "Danielle_21":
			dialog.text = "Wait... that's not all yet. That Italian, Guineili, yes? That quiet young man. He was... his body was found in a tavern... I don't know, probably one of those bastards who went through the catacombs and attacked the town. Apparently, they were hiding there, waiting for a chance to escape, and found him...";
			link.l1 = "And Gino too?! Today truly is a rainy day...";
			link.l1.go = "Danielle_22";
		break;
		
		case "Danielle_22":
			pchar.questTemp.LongHappy.Tichingitu_died = "true";
			dialog.text = "I'm sorry, Charles... If you wish, we will send their bodies to your ship, take the men home, and bury them as they deserve. I'm truly sorry...";
			link.l1 = "Thanks, Dannie. Do it... I should go... I need... to think.";
			link.l1.go = "Danielle_23";
		break;
		
		case "Danielle_23":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", 10.0);
			sld = characterFromId("Svenson");
			sld.dialog.currentnode = "Svenson_26";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		// Додсон
		case "Dodson":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Charles, can you even imagine how many girls' hearts you broke with this wedding of yours? Yes, half the girls in the archipelago must have mourned after your wedding, haha!";
			link.l1 = "What can I do - I only needed one and I got her. But it's too soon for the girls to be upset, because they still have you, Stiven.";
			link.l1.go = "Dodson_1";
		break;
		
		case "Dodson_1":
			dialog.text = "And that's true! We'll finish here and I'll take care of them straight away, damn it! Come on, Charles, let's drink to your luck and family life. So, as they say, happily ever after!";
			link.l1 = "Thank you, my friend!";
			link.l1.go = "Dodson_2";
		break;
		
		case "Dodson_2":
			DialogExit();
			npchar.dialog.currentnode = "Dodson_2_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Dodson_2_1":
			dialog.text = "To a happy family life, ha-ha!";
			link.l1 = "Cheers!";
			link.l1.go = "Dodson_2";
		break;
		
		// Венсан
		case "Vensan":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Charles, can you even imagine how many girls' hearts you broke with this wedding of yours? Yes, half the girls in the archipelago must have mourned after your wedding, haha!";
			link.l1 = "What can I do - I only needed one and I got her. But it's too soon for the girls to be upset, because they still have you, Bernard.";
			link.l1.go = "Vensan_1";
		break;
		
		case "Vensan_1":
			dialog.text = "And that's true! We'll finish here and I'll take care of them straight away, damn it! Come on, Charles, let's drink to your luck and family life. So, as they say, happily ever after!";
			link.l1 = "Happily ever after!";
			link.l1.go = "Vensan_2";
		break;
		
		case "Vensan_2":
			DialogExit();
			npchar.dialog.currentnode = "Vensan_2_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Vensan_2_1":
			dialog.text = "For a happy family life, ha ha!";
			link.l1 = "Great toast!";
			link.l1.go = "Vensan_2";
		break;
		
		case "Vensan_3":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Ha, Charles, so you too have become married and boring, like our old Nathan! Wild affairs and everything else are now in the past, eh? Proper family man!";
			link.l1 = "Keep waiting, Bernard! My wife is not one of those who would be bored sitting under the window of a family ruin! The only thing that will change is the fullness of the purses of the brothel girls from here to Curaçao!";
			link.l1.go = "Vensan_4";
		break;
		
		case "Vensan_4":
			dialog.text = "Not a great loss, I say! Better to have one gold coin than a bag of nickels. Let's have a drink! Cheers to you and your wife! Keep your gold safe and be happy!";
			link.l1 = "Thank you, Bernard. Oh, this is really strong rum. Whew!";
			link.l1.go = "Vensan_5";
		break;
		
		case "Vensan_5":
			DialogExit();
			npchar.dialog.currentnode = "Vensan_5_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Vensan_5_1":
			dialog.text = "To your bride, I mean, already your wife!";
			link.l1 = "Thank you!";
			link.l1.go = "Vensan_5";
		break;
		
		case "Vensan_6":
			dialog.text = "You're just in time, Charles, thank you!";
			link.l1 = "What's the fun here? I thought you were already loading onto the ships in the harbour.";
			link.l1.go = "Vensan_7";
		break;
		
		case "Vensan_7":
			dialog.text = "Marcus left me to organise a defence on the shore. We're short of men, the lads in the port need gunpowder. Thought I'd drop in, take a couple of barrels ... and then these thugs showed up. Hah, they were hiding, I suppose, hoping to wait it out or rob someone. And I'm still full of Hawk's rum, so without you, I don't know if I'd still be alive or not.";
			link.l1 = "You're always welcome. Fine, Bernard, you make sure that the town is secure, and I should go. Stay safe!";
			link.l1.go = "Vensan_8";
		break;
		
		case "Vensan_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 10.0);
			pchar.questTemp.LongHappy.Vensan_alive = "true";
		break;

		// Джино
		case "Jino":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Captain, let me heartily congratulate you and your beloved on this auspicious day! Be happy and take care of each other!";
			link.l1 = "Thanks, Gino. I'm glad you decided to come! I hope the local... colour, does not bother you?";
			link.l1.go = "Jino_1";
		break;
		
		case "Jino_1":
			dialog.text = "This is... a very educational trip. I must say - I haven't been out of Antigua for a long time, and in this society it's not easy for me to feel comfortable. But you always knew how to understand people, so I will try to stay calm, since I trust you.";
			link.l1 = "Maybe you need to drink something stronger? Relax and find someone to talk to?";
			link.l1.go = "Jino_2";
		break;
		
		case "Jino_2":
			dialog.text = "Thank you, captain, I've had enough watered wine. Alcohol, I must warn you, is not very good for the liver and possibly the heart. As for conversation, I tried to discuss the healing properties of Chirik-Sanango with that gentleman over there; it is also called Manaka. The natives of Maine use it for...";
			link.l1 = "Let me guess - that gentleman couldn't handle the discussion? Gino, for my sake and just for today - try the rum that Jan over there is pouring at the counter. If you can guess all its ingredients, Nathaniel Hawk, over there, will be extremely impressed. I am sure he will be glad to have your company, as will Svenson, the man at the counter; both of them respect educated people.";
			link.l1.go = "Jino_3";
		break;
		
		case "Jino_3":
			DialogExit();
			npchar.dialog.currentnode = "Jino_3_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (CheckAttribute(pchar, "questTemp.LongHappy.HambitOfficer"))
				{
					sld = characterFromId(pchar.questTemp.LongHappy.HambitOfficer);
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					if (GetCharacterIndex("Baker") != -1)
					{
						sld = characterFromId("Baker");
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
					else
					{
						if (GetCharacterIndex("Tichingitu") != -1)
						{
							sld = characterFromId("Tichingitu");
							LAi_SetActorType(sld);
							LAi_ActorDialog(sld, pchar, "", -1, 0);
						}
						else
						{
							sld = characterFromId("Mary");
							sld.dialog.currentnode = "LongHappy_57";
							LAi_SetActorType(sld);
							LAi_ActorDialog(sld, pchar, "", -1, 0);
						}
					}
				}
			}
			else if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Jino_3_1":
			dialog.text = "To your health, and to the health of your charming spouse!";
			link.l1 = "Thank you, friend!";
			link.l1.go = "Jino_3";
		break;
		
		case "Jino_4":
			dialog.text = "Captain, it's you, thank God! Those masked people, I saw them and hid here, and they tried to break down the door...";
			link.l1 = "It's alright, Gino, nobody's going to hurt you anymore. It's very fortunate that I found you, I need your help. My friend is injured - he has been shot, and he has lost a lot of blood. We must hurry!";
			link.l1.go = "Jino_5";
		break;
		
		case "Jino_5":
			dialog.text = "Shot... blood... I'm fine, captain. On my way here, I grabbed my medical chest with all the tools in case of injury. Lead me to him, I'll see what can be done. And those... masked men, perhaps they've hidden somewhere else?";
			link.l1 = "I'm sure they were the last. Gino, there's a battle in the harbour and I need to go there right now. You have to get to the residence on your own, it's not far. The big house is around the corner - you won't miss it. Don't be afraid - the streets are full of our people, and hurry up, I'm begging you!";
			link.l1.go = "Jino_6";
		break;
		
		case "Jino_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 7.0);
			LocatorReloadEnterDisable("Pirates_tavern", "reload1_back", false);
			pchar.questTemp.LongHappy.Jino_alive = "true";
			AddQuestRecord("LongHappy", "18");
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim")) sld = characterFromId("Tichingitu");
			else sld = characterFromId("Nathaniel");
			sTemp = sld.name;
			AddQuestUserData("LongHappy", "sName1", sTemp);
		break;
		
		case "Jino_7":
			dialog.text = "Captain, let me heartily congratulate you and your beloved on this auspicious day! Be happy and take care of each other.";
			link.l1 = "Thanks, Gino. I'm glad you decided to come! I hope the journey went smoothly?";
			link.l1.go = "Jino_8";
		break;
		
		case "Jino_8":
			dialog.text = "Everything is fine, captain, thank you for your concern. I must say - I haven't been out of Antigua for a long time, and among the elite I... don't feel very comfortable. But the reason for coming left me no choice. By the way - the service was excellent, I'm very happy for both of you! The bride in this outfit is charming - is this a new fashion? It seems I've fallen behind in living life, but I like it, truly.";
			link.l1 = "Fashion... In some way, yes, or at least, it will be soon. Fine, have fun, Gino, and if the noble interlocutors become a bore to you, then come to the port. The whole crew is in the tavern. The lads will be happy to see you.";
			link.l1.go = "Guests_block";
		break;
		
		case "Jino_9":
			dialog.text = "Captain, once more, I congratulate you and your beautiful wife! Wishing you many long and happy years together!";
			link.l1 = "Thanks, Gino. I'm glad you came! I hope the local... colour, does not bother you?";
			link.l1.go = "Jino_10";
		break;
		
		case "Jino_10":
			dialog.text = "This society is not easy for me to feel comfortable in. But, you always knew how to choose people, so I will try to stay calm, since I trust you.";
			link.l1 = "Maybe you need to drink something stronger? Relax and find someone to talk to?";
			link.l1.go = "Jino_11";
		break;
		
		case "Jino_11":
			dialog.text = "Thank you, captain, I've had enough watered wine. Alcohol, I must warn you, is not very good for the liver and possibly the heart. As for conversation, I tried to discuss the healing properties of Chirik-Sanango with that gentleman, it is also called Manaka. The natives of Maine use it for...";
			link.l1 = "Let me guess - that gentleman couldn't handle the discussion? Gino, for my sake and just for today - try the rum that Jan over there is pouring at the counter. If you can guess all of its ingredients, Nathaniel Hawk, over there, will be extremely impressed. I am sure he will be glad to be in your company, as will Svenson, the man at the counter; both of them respect educated people.";
			link.l1.go = "Jino_3";
		break;
		
		// Лонгвэй
		case "Longway":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "'Alone now in a strange land, feeling myself a stranger, on this bright festival day I long all the more for my kinsfolk'";
			link.l1 = "Longway, I never thought you were a master of words!";
			link.l1.go = "Longway_1";
		break;
		
		case "Longway_1":
			dialog.text = "Sorry, Captain, I've been doing a lot of thinking. These are the words of Wang Wei - a poet who lived during the Tang dynasty, which ruled a long time ago in my homeland.";
			link.l1 = "These words are so beautiful. I hope one day you'll see your homeland again...";
			link.l1.go = "Longway_2";
		break;
		
		case "Longway_2":
			dialog.text = "''Is it possible to vouch and know that beneath the arch of mysterious stone slabs, it is impossible, when trying to pass through, to find a passage beyond which the U-lin valley lies?'\nNo, Captain, you know it - Longway is not going to return home. Now, here is my home and we have a great event here today! I'm sending my best to you and your beautiful bride! May your happiness be as long as the Yangtze River, studded with diamonds of stars, between the pearls of the lotus.";
			link.l1 = "Thank you, my old friend. Your words are no less beautiful than Wang Wei's.";
			link.l1.go = "Longway_3";
		break;
		
		case "Longway_3":
			dialog.text = "Let's have a drink, Captain! This rum chases away sorrow and revives joy just as well as maotai.";
			link.l1 = "To your health, Longway!";
			link.l1.go = "Longway_4";
		break;
		
		case "Longway_4":
			DialogExit();
			npchar.dialog.currentnode = "Longway_4_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (GetCharacterIndex("Baker") != -1)
				{
					sld = characterFromId("Baker");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					if (GetCharacterIndex("Tichingitu") != -1)
					{
						sld = characterFromId("Tichingitu");
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
					else
					{
						sld = characterFromId("Mary");
						sld.dialog.currentnode = "LongHappy_57";
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
				}
			}
			else 
			{
				if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
			}
		break;
		
		case "Longway_4_1":
			dialog.text = "Great wedding, captain!";
			link.l1 = "Drink and have fun!";
			link.l1.go = "Longway_4";
		break;
		
		// Книппель
		case "Knippel":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				dialog.text = "Fire a chain shot! All our men congratulate you! How did the shot go?";
				link.l1 = "Everything is fine, Charlie! Now I am officially married and respectable, and my first mate is Madame de Monper now.";
			}
			else
			{
				dialog.text = "Hit me with a chain shot, what an event, captain! Almost every baron of the Brethren is here! I suppose every Spanish puritan imagines Hell like this! And the rum, it's something special, a chain shot to my barrel!";
				link.l1 = "Yes, people here are not the most law-abiding, but we ourselves are no angels, Charlie, and each of these people is dear to me in their own way.";
			}
			link.l1.go = "Knippel_1";
		break;
		
		case "Knippel_1":
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				dialog.text = "It's wonderful, chain shot to my butt! Captain, I mean, this celebration is in your honour, well, I... I congratulate, I mean... also... Happiness and... this, I am not good at speeches. But you must know that we all love you both and we will follow you even to hell, captain!";
				link.l1 = "Thank you, old friend.";
			}
			else
			{
				dialog.text = "Wait, I mean... What do I even mean, chain shot to my arse?! Captain, I meant that this day is in your honour, well, I... I congratulate you... and also... I wish you happiness and... and sorry, Cap, I might be a bit too drunk to hold a speech, chain shot to my neck, I haven't been sober in a while ha-ha-ha!";
				link.l1 = "Hah! It's all right... thank you, old friend.";
			}
			link.l1.go = "Knippel_2";
		break;
		
		case "Knippel_2":
			Log_Info("You have got gems");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "jewelry4", 20);
			dialog.text = "Ah! And yes, captain, please accept this. For you and your lady. I've kept these stones for a rainy day... I understand you have no shortage of gold, but they won't be superfluous, will they?";
			link.l1 = "Charlie, you are truly a generous soul, and these emeralds will look splendid in Madame de Monper's family earrings!";
			link.l1.go = "Knippel_3";
		break;
		
		case "Knippel_3":
			dialog.text = "Well, let's drink to that, chain shot to my... hm. Just be happy, both you and your beauty, captain!";
			link.l1 = "We will, Charlie!";
			link.l1.go = "Knippel_4";
		break;
		
		case "Knippel_4":
			DialogExit();
			npchar.dialog.currentnode = "Knippel_4_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (GetCharacterIndex("Baker") != -1)
				{
					sld = characterFromId("Baker");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					if (GetCharacterIndex("Tichingitu") != -1)
					{
						sld = characterFromId("Tichingitu");
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
					else
					{
						sld = characterFromId("Mary");
						sld.dialog.currentnode = "LongHappy_57";
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
				}
			}
			else 
			{
				if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
			}
		break;
		
		case "Knippel_4_1":
			dialog.text = "Great wedding, captain!";
			link.l1 = "Drink and have fun!";
			link.l1.go = "Knippel_4";
		break;
		
		// Тонзаг
		case "Tonzag":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "I never thought, captain, that I would see you married. Usually, the path we have chosen leads down a lonely road straight to a solitary grave. In my memory, you are the first to have managed to escape it. That deserves an extra toast, doesn't it?";
			link.l1 = "This is it, mate! And truly, I'm glad that this part of my life is behind me. Cheers!";
			link.l1.go = "Tonzag_1";
		break;
		
		case "Tonzag_1":
			dialog.text = "Cheers to you and your long and happy life together! Damn, looking at you, I recall that I myself was once married.";
			link.l1 = "You? Married? That's interesting news! But what happened?";
			link.l1.go = "Tonzag_2";
		break;
		
		case "Tonzag_2":
			dialog.text = "What, do you think I was always an old cyclops reeking of gunpowder and blood, captain? But no. Madame Tonzag, she... she loved me, I suppose. But then, an unpleasant story happened. In which the Tonzag couple died, and only Bald Gaston, with a set of scars, managed to survive.";
			link.l1 = "I'm sorry, Hercule, I didn't know...";
			link.l1.go = "Tonzag_3";
		break;
		
		case "Tonzag_3":
			dialog.text = "Forget it, captain, that story happened a long time ago. But now, looking at you, I think my story could still have a happy ending. So, let us drink to that!";
			link.l1 = "Let us, mate. You know - since the day I met you, I've always looked at you as I would my own father, so maybe one day you'll have the chance to be a great-grandfather. Anyway, cheers! I must see to the rest, we'll talk later.";
			link.l1.go = "Tonzag_4";
		break;
		
		case "Tonzag_4":
			DialogExit();
			npchar.dialog.currentnode = "Tonzag_4_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (GetCharacterIndex("Baker") != -1)
				{
					sld = characterFromId("Baker");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					if (GetCharacterIndex("Tichingitu") != -1)
					{
						sld = characterFromId("Tichingitu");
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
					else
					{
						sld = characterFromId("Mary");
						sld.dialog.currentnode = "LongHappy_57";
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
				}
			}
			else 
			{
				if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
			}
		break;
		
		case "Tonzag_4_1":
			dialog.text = "Great celebration, Captain!";
			link.l1 = "Drink and have fun!";
			link.l1.go = "Tonzag_4";
		break;
		
		// Бейкер
		case "Baker":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Here's our captain! Congratulations, you and your wife make a beautiful couple! May you live happily ever after!";
			link.l1 = "Thank you, Raymond.";
			link.l1.go = "Baker_1";
		break;
		
		case "Baker_1":
			sTemp = "Sharptown";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) sTemp = "Sent Pierre";
			dialog.text = "Looks like you're too sober for your own wedding, captain. Would you like to remedy that? I've picked up a bottle of excellent sherry at the bar. Mixing it with the local rum works just fine!";
			link.l1 = "I'd like to, but someone has to keep an eye on things here. Otherwise, in "+sTemp+" not only the tavern will be missed when morning comes.";
			link.l1.go = "Baker_2";
		break;
		
		case "Baker_2":
			DialogExit();
			npchar.dialog.currentnode = "Baker_2_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (GetCharacterIndex("Tichingitu") != -1)
				{
					sld = characterFromId("Tichingitu");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					sld = characterFromId("Mary");
					sld.dialog.currentnode = "LongHappy_57";
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
			}
			else 
			{
				if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
			}
		break;
		
		case "Baker_2_1":
			dialog.text = "Excellent food and excellent rum, captain! Cheers to you and your young wife!";
			link.l1 = "Thanks!";
			link.l1.go = "Baker_2";
		break;
		
		// Алексус
		case "Alexus":
			dialog.text = "Young people, why are you breaking in, may I ask? The shipyard is closed, isn't it obvious? Come back tomorrow.";
			link.l1 = "Master, I'm sorry to trouble you, we'll just pass through the dungeons. There are supplies for the wedding, and the tavern is almost out of drinks.";
			link.l1.go = "Alexus_1";
		break;
		
		case "Alexus_1":
			dialog.text = "Oh, Charles de Maure and Nathan Hawk themselves! You're here to celebrate someone's wedding, aren't you? Fine - go get your drink. Young people should have fun - that's the law at any time. Just don't rattle the bottles on your way back - I'm going to sleep!";
			link.l1 = "Thank you, master, we will be as silent as the calmest river.";
			link.l1.go = "Alexus_2";
		break;
		
		case "Alexus_2":
			DialogExit();
			npchar.dialog.currentnode = "Alexus_2_1";
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", false);
			pchar.GenQuestBox.Bermudes_Dungeon = true;
			pchar.GenQuestBox.Bermudes_Dungeon.box3.items.potionwine = 100;
			pchar.quest.longhappy_isla_box.win_condition.l1 = "locator";
			pchar.quest.longhappy_isla_box.win_condition.l1.location = "Bermudes_Dungeon";
			pchar.quest.longhappy_isla_box.win_condition.l1.locator_group = "box";
			pchar.quest.longhappy_isla_box.win_condition.l1.locator = "box3";
			pchar.quest.longhappy_isla_box.function = "LongHappy_IslaTesoroDungeon";
		break;
		
		case "Alexus_2_1":
			dialog.text = "C'mon, don't just stand there, go! Well, captain, are you satisfied with everything?";
			link.l1 = "...";
			link.l1.go = "Alexus_2_2";
		break;
		
		case "Alexus_2_2":
			DialogExit();
			npchar.dialog.currentnode = "Alexus_2_1";
		break;
		
		// пиратус в подземелье
		case "DungeonPirate":
			dialog.text = "What the hell?! Jacques said 'No one comes down here'! Hugo - run back, call the others, we'll clear the way. Kill them, lads!";
			link.l1 = "Shit!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_BandosInDungeonFight");
		break;
		
		// киллеры
		case "killer":
			dialog.text = "Lads, forget about the chests, we've got guests!";
			link.l1 = "I thought bastards like you were killed along with Jackman. Fine, let's finish this!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_ResidenceFight");
		break;
		
		case "killer_1":
			dialog.text = "Blast... We've been found! Alarm!";
			link.l1 = "Get out of my way, arsehole!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_TavernKillerFight");
		break;
		
		// Ангерран
		case "Shivo":
			dialog.text = "Monsieur de Maure, good evening, or is it almost morning already? Come in, have a seat.";
			link.l1 = "Angerran De Chievous! I'm not at all surprised to see you! The insignificant man, only capable of fighting women! Did you tie them up as well?! Now I'll finish what I started in that duel on Martinique!";
			link.l1.go = "Shivo_1";
		break;
		
		case "Shivo_1":
			dialog.text = "Calm down, young man, see this gun? There are two barrels. Maybe I'm not much of a fencer, but I'm a rather good shot – put down your sword, or you'll miss out on a couple of beautiful ladies, I assure you.";
			link.l1 = "Bastard... Damn you.";
			link.l1.go = "Shivo_2";
		break;
		
		case "Shivo_2":
			dialog.text = "And you, monsieur pirate, put down your weapon as well, just like that, yes. And now - sit down, you may pour the wine - it's over there on the table. We shall have to wait a bit until monsieur Barbazon finishes smashing the ships of your friends, the pirate barons. Then we'll decide how you and I will settle our... hm, disagreements.";
			link.l1 = "Settle disagreements? And how? Do you want a duel?";
			link.l1.go = "Shivo_3";
		break;
		
		case "Shivo_3":
			dialog.text = "Don't be so funny, Charles. You and Madame Botot have caused me a great deal of trouble, and I intend to repay you in full. Although she caused me far more problems than you did... however, if you and the imposing Monsieur Pirate sit quietly, then I give you my word of honour – your wives will stay alive. I believe that in the Spanish colonies on the Main, such slaves are valued. Even unofficially. But it is still life, isn't it?";
			link.l1 = "Angerran, you are a coward, a bastard and... Blast, there are no suitable words for you yet in any language!";
			link.l1.go = "Shivo_4";
		break;
		
		case "Shivo_4":
			dialog.text = "You know it, you have no choice. I can only promise it will be quick. So, if you care for these women - behave yourself, spare their lives and ease your fate. And yes - lock the door if it's not too much trouble. Thank you.";
			link.l1 = "";
			link.l1.go = "Shivo_5";
		break;
		
		case "Shivo_5":
			DialogExit();
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Shivo_6":
			dialog.text = "Such warlike ladies. I must still ask you to be prudent. I have never liked killing women.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_BedroomShot");
		break;
		
		case "Shivo_7":
			dialog.text = "Shit...";
			link.l1 = "Die, bastard!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_BedroomFight");
		break;
		
		// Дюссак
		case "Dussak":
			dialog.text = "Captain Charles de Maure, Baron Hawk - what a pleasant surprise! Let me introduce myself - Mauritz Dussak, that's my name.";
			link.l1 = "Get out of my way, bastard! Where is my wife?!";
			link.l1.go = "Dussak_1";
		break;
		
		case "Dussak_1":
			dialog.text = "Calm down, gentlemen! See this gun? There are two barrels. I was nicknamed that for a reason – I love sabres, sure... but I can shoot well too, believe me. Lay down your swords, or you might lose a couple of your fingers!";
			link.l1 = "I'm going to slaughter you like a pig, scum...";
			link.l1.go = "Dussak_2";
		break;
		
		case "Dussak_2":
			dialog.text = "But you'll already be a widower. Don't you want that? Then calm down and lay down your weapon. Baron Hawk, please, lock the door. We'll settle down and wait a while, while Jacques Barbazon out there in the harbour finishes off the leaders of the Brethren.";
			link.l1 = "And what's next? Shall we embrace and ride off into the sunset together?";
			link.l1.go = "Dussak_3";
		break;
		
		case "Dussak_3":
			dialog.text = "I don't think so. For your capture, Jacques will shower me with gold. With luck, perhaps I'll become a baron. As for your women, perhaps we'll let them go, but as for you - alas... If you're lucky, I'll ask for the right to kill you myself, captain. You are a famous fencer - it would be interesting to test you. You know, I also consider myself a master.";
			link.l1 = "A master of breaking into houses at night and tying up half-asleep women? You are a worm, moreover - a pathetic worm!";
			link.l1.go = "Dussak_4";
		break;
		
		case "Dussak_4":
			DialogExit();
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Dussak_5":
			dialog.text = "Listen, madam, I've never killed women, don't make me start, alright? You're unnerving the captain and your husband... Damn!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_BedroomShot");
		break;
		
		case "Dussak_6":
			dialog.text = "Merdo...";
			link.l1 = "Die, bastard!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_BedroomFight");
		break;
		
		// Барбазон
		case "Barbazon_boarding":
			dialog.text = "Fucking Frenchman, was there not a sabre or a bullet?!";
			link.l1 = "You know, Jacques, I have both for you. Honestly, I almost regret leaving you alive when I found out about your tricks with Jackman. But now, I am going to fix that.";
			link.l1.go = "Barbazon_boarding_1";
		break;
		
		case "Barbazon_boarding_1":
			dialog.text = "You're only brave when you're surrounded by your own men? Let's change that! I'll deal with the barons later, but you won't leave here alive, rat!";
			link.l1 = "Expected...";
			link.l1.go = "Barbazon_boarding_2";
		break;
		
		case "Barbazon_boarding_2":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			AddItems(npchar, "potion2", 1);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "LongHappy_BarbAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");
			// подкрепление
			sld = GetCharacter(NPC_GenerateCharacter("LH_BarbCabinHelper", "citiz_57", "man", "man", 35, PIRATE, 0, true, "quest"));
			FantomMakeCoolFighter(sld, 35, 70, 70, "blade_21", "pistol4", "bullet", 300);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_BRDENEMY);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			AddItems(sld, "potion2", 2);
		break;
		
		// официантка
		case "waitress":
			dialog.text = "Captain, help, this savage, he has abducted me! I... I need to go home - my uncle has probably already turned the whole town upside down!";
			link.l1 = "Calm down, beauty, everything will be fine. Step aside, I need to talk to your 'savage'.";
			link.l1.go = "waitress_1a";
		break;
		
		case "waitress_1a":
			DialogExit();
			sld = characterFromId("Tichingitu");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "waitress_1":
			dialog.text = "Thank you, captain! You saved me! When I woke up this morning on this beach, I... can't believe that I was going to marry this savage, he...";
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 94)
			{
				link.l1 = "Yes, morning is a stern hammer for the night's crystal of hope. I understand. But he is from the Muscogee tribe, and lives according to the harsh laws of his land. He stole you with your consent, and you spent the night together. So now, in the eyes of his gods, you are husband and wife. Let's go and pack your things, and I'll settle the ransom issue with your uncle.";
				link.l1.go = "waitress_2";
			}
			link.l2 = "I'm sorry about this. Tichingitu lives by the laws of his tribe, but he is a good person. Please, forget about this abduction story.";
			link.l2.go = "waitress_5";
		break;
		
		case "waitress_2":
			dialog.text = "Wife? In the eyes of his gods?! No, captain, I beg you, save me from this! It was just... an adventure, he was so gallant and kind, not like these bumpkins... But marriage? I am too young to move into a hut with a savage!";
			link.l1 = "He is my officer and my best friend, so don't worry, I pay him well, and you will have the finest hut you could wish for. Tichingitu is a skilled hunter, he will provide food for you, and you will give birth and look after the children.";
			link.l1.go = "waitress_3";
		break;
		
		case "waitress_3":
			dialog.text = "Children? Procure food?! No, captain, please don't do this to me, I beg you!";
			link.l1 = "Well, maybe I can convince him. But it won't be easy. The Muskogue tribe is very serious about such things; if someone finds out that he stole a squaw and didn't get married...";
			link.l1.go = "waitress_4";
		break;
		
		case "waitress_4":
			dialog.text = "You have to try, please! I won't tell anyone, no one will know! I'll lie to uncle, it's not the first time!";
			link.l1 = "Fine, you should go, beautiful squaw. I will try to keep my friend away.";
			link.l1.go = "waitress_7";
		break;
		
		case "waitress_5":
			dialog.text = "He stole me like... like a goat from a barn! I will tell everyone! My uncle will kill him! He is terrible when angry! He used to rob Spanish ships – it's no laughing matter with him!";
			link.l1 = "Alright, hush, beautiful lady, hush. Perhaps twenty thousand 'reasons' to forgive him would be more eloquent than my words? Or should I give them to your uncle, like a ransom for a wife? After all, everyone is on the island, aren't they? Tomorrow we can organise another wedding...";
			link.l1.go = "waitress_6";
		break;
		
		case "waitress_6":
			if (sti(Pchar.money) >= 20000) AddMoneyToCharacter(pchar, -20000); 
			dialog.text = "No, no, captain, wait! You've convinced me. I'll come up with something so my uncle won't be angry. Farewell! And goodbye to you, my stallion from the distant plains! See me next time you visit...";
			link.l1 = "That's right. Glad we agree. Run home, beauty.";
			link.l1.go = "waitress_7";
		break;
		
		case "waitress_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			sld = characterFromId("Tichingitu");
			sld.dialog.currentnode = "Tichingitu_16";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		// тавернщик Сен Пьер
		case "tavernkeeper":
			dialog.text = "Well, Captain, are you satisfied with everything? The finest rum, lamb ribs, pork hams, and even excellent wine from my personal stock for your scientist friend! And - my congratulations to you and your beautiful wife!";
			link.l1 = "Thanks! I must admit, you organised everything perfectly. I hope you have enough rum stocked in your cellars, morning is far off.";
			link.l1.go = "tavernkeeper_1";
		break;
		
		case "tavernkeeper_1":
			dialog.text = "Don't worry about it, if the barrels run dry, I'll send an assistant to the port warehouse. Enjoy yourself, monsieur, and don't worry about a thing.";
			link.l1 = "Fine, "+npchar.name+". Then I shall go to my guests.";
			link.l1.go = "tavernkeeper_2";
		break;
		
		case "tavernkeeper_2":
			DialogExit();
			npchar.dialog.currentnode = "tavernkeeper_3";
		break;
		
		case "tavernkeeper_3":
			dialog.text = "What would you like, captain? Fried ribs, smoked ham, or brisket? Perhaps some wine for your better half?";
			link.l1 = "";
			link.l1.go = "tavernkeeper_2";
		break;
		
		// моряки в таверне Сен Пьер
		case "sailor":
			dialog.text = RandPhraseSimple(LinkRandPhrase("To the health of the captain and his wife!","May you live happily ever after, Captain!","Long life and happiness to you both!"),LinkRandPhrase("Hooray for the captain and his beauty!","May luck follow the captain and his spouse throughout their lives!","Fair winds to your family life, cap!"));
			link.l1 = LinkRandPhrase("Thanks!","Thank you!","Cheers!");
			link.l1.go = "sailor_1";
		break;
		
		case "sailor_1":
			DialogExit();
			npchar.dialog.currentnode = "sailor";
		break;
		
		// босс Ле Франсуа
		case "JanDavid":
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Are you insane? Did you want to play the butcher? All the pirates are angry with you, pal, so you'd better leave this place.","It seems, pal, you've gone mad. Wanted to stretch your hands a bit? No offence, but you have nothing to do here. Get lost!");
				link.l1 = RandPhraseSimple("Listen, I want to set things right...","Help me solve the problem...");
				link.l1.go = "pirate_town";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LongHappy.Baron"))
			{
				if (!CheckAttribute(npchar, "quest.Baron"))
				{
					dialog.text = "Ah, I've been waiting for your visit, boss. Jan Svenson warned me that you would definitely come to check how things are going in Le Francois. I've taken everything into my own hands, and swear by thunder, this village will thrive better than it ever did under that damned Kindman. May the devils amuse themselves with him in the darkest cellars of hell!";
					link.l1 = "You are Jean David, right? Svenson mentioned something about my share...";
					link.l1.go = "JanDavid_2";
				}
				else
				{
					dialog.text = TimeGreeting()+" boss. Everything is fine in Le François, as always. Why have you come? Can I help you with something?";
					link.l1 = "Just dropped by to see how things are going.";
					link.l1.go = "JanDavid_1";
					if (sti(pchar.questTemp.LongHappy.BaronMoney) > 0)
					{
						link.l2 = "What about my share?";
						link.l2.go = "JanDavid_5";
					}
				}
			}
			else
			{
				dialog.text = TimeGreeting()+" mate. Why have you come? Can I help you with something?";
				link.l1 = "Just dropped by to say hello.";
				link.l1.go = "JanDavid_1";
			}
		break;
		
		case "JanDavid_1":
			DialogExit();
			npchar.dialog.currentnode = "JanDavid";
		break;
		
		case "JanDavid_2":
			npchar.quest.Baron = "true";
			dialog.text = "At your service, boss! As for your share - on the fifth of every month, a portion of the gold coins from our lads' deeds will be set aside for you, and it will wait for you as long as you need. Starting next month, you can come to collect it.";
			link.l1 = "Nice!";
			link.l1.go = "JanDavid_3";
		break;
		
		case "JanDavid_3":
			dialog.text = "And I'll take care of the rest. The Forest Devil said that you wouldn't have time to bother with such trivial matters as Le Francois...";
			link.l1 = "You were told correctly. Fine, Jean, I'm counting on you, I hope you won't let me down.";
			link.l1.go = "JanDavid_4";
		break;
		
		case "JanDavid_4":
			dialog.text = "All will be well, boss. Everything is under control here, ha-ha, and may I never drink rum again until the end of days if I mess something up!";
			link.l1 = "Fine, see you!";
			link.l1.go = "JanDavid_1";
			// запуск отчисления доли
			pchar.questTemp.LongHappy.BaronPart = "true";
			pchar.questTemp.LongHappy.BaronMoney = 0;
		break;
		
		case "JanDavid_5":
			dialog.text = "Waiting for you, boss. In the meantime, we have gathered for you "+FindRussianMoneyString(sti(pchar.questTemp.LongHappy.BaronMoney))+". Take it.";
			link.l1 = "Ha, not bad. Well done, Jean.";
			link.l1.go = "JanDavid_6";
		break;
		
		case "JanDavid_6":
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.LongHappy.BaronMoney));
			pchar.questTemp.LongHappy.BaronMoney = 0;
			dialog.text = "I do my best, boss. Come back next month or whenever you wish - your money will be safe with me.";
			link.l1 = "Fine, see you, Jean.";
			link.l1.go = "JanDavid_1";
		break;
		
		case "pirate_town":
             dialog.text = "Solve the problem? Do you have any idea what you have done? Anyway, bring me a million pesos and I will persuade the lads to forget your deed. If you don't like the idea then you may go to hell.";
			if (sti(Pchar.money) >= 1000000)
			{
				link.l1 = "Fine, I am ready to pay.";
				link.l1.go = "pirate_town_pay";
			}
			link.l2 = "Got it. I'm leaving.";
			link.l2.go = "pirate_town_exit";
		break;
		
		case "pirate_town_exit":
			DialogExit();
            bDisableFastReload = true;//закрыть переход
			pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
			pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
			pchar.quest.pirate_in_town.function = "TownPirate_battle";
		break;
		
		case "pirate_town_pay":
            dialog.text = "Good! Consider yourself clean again. But I hope you won't do such disgusting things again.";
			link.l1 = "I won't. Far too expensive for me. Farewell...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000000);
			pchar.GenQuest.Piratekill = 0;
		break;
	}
} 

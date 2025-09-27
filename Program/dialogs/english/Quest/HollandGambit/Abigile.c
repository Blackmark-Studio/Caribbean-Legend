// Абигайль Шнеур
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
			{
				if (pchar.questTemp.HWIC.Holl == "AbbyInHouse")
				{
					dialog.text = "Good day, mynheer. What brings you to our home?";
					link.l1 = "Good day, Abigail. My name is "+GetFullName(pchar)+". I am a captain serving the interests of the Republic and the Dutch West India Company.";
					link.l1.go = "AbbyAndLucas";
					DelLandQuestMark(npchar);
					break;
				}
				if (pchar.questTemp.HWIC.Holl == "AbbyFindScull" && makeint(Pchar.money) >= 200000)
				{
					dialog.text = "My God, have you found my father's money? Is it true? Ah, I am so glad! Quickly, go to my father, he wants to talk with you. Go and see him!";
					link.l1 = "I am on my way, madam.";
					link.l1.go = "exit";
					DelLandQuestMark(npchar);
					break;
				}
				if (pchar.questTemp.HWIC.Holl == "AbbyLeavesMarried")
				{
					dialog.text = "You have saved us from utter despair, captain! I am so grateful to you! Now the good name of the Shneur family can be restored!";
					link.l1 = "Merely doing my duty as a gentleman, madam. I hope that there is nothing left to keep you from marrying my patron.";
					link.l1.go = "AbbyAndLucas_8";
					DelLandQuestMark(npchar);
					break;
				}
				dialog.text = "Do you need something, captain?";
				link.l1 = "Not right now, madam.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
			{
				if (pchar.questTemp.HWIC.Eng == "AbigileInChurch")
				{
					dialog.text = "Hail, Holy Queen, our life, our sweetness, and our hope. To you do we cry, poor banished children of Eve. To you do we send up our sighs, mourning and weeping in this valley of tears... oh mynheer, you startled me! What brings you here?";
					link.l1 = "I beg your pardon, Abigail, I presume? Richard Fleetwood sent me...";
					link.l1.go = "Seek_Island";
					DelLandQuestMark(npchar);
					break;
				}
				dialog.text = "Do you want something, captain?";
				link.l1 = "Not right now, madam.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				if (pchar.questTemp.HWIC.Self == "toVillemstad")
				{
					dialog.text = "What is going on here? What is this noise? Papa, who is this strange man?";
					link.l1 = "Good day, madame. Abigail Schneur, I presume? I am glad to see you. You must forgive my impudence, but I have here an urgent letter addressed to you from... well, I would love to tell you, but your dear father refuses to even let me stand inside your house, let alone deliver this message to you.";
					link.l1.go = "Abigile_kidnapping";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileNextDay")
				{
					dialog.text = "Ah, here you are, Charles. I am ready to follow you anywhere!";
					link.l1 = "Let's go then.";
					link.l1.go = "Abigile_kidnapping_7";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileInCabin")
				{
					dialog.text = "Are we at St. John's yet, Charles? Will I see Richard soon?";
					link.l1 = "Yes, madam, we are in St. John's. Unfortunately, Richard is not in town at the moment; he was ordered to patrol near Barbados two days ago. Don't worry, he should return in a week.";
					link.l1.go = "Abigile_kidnapping_8";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileLie")
				{
					dialog.text = "Charles! I am so glad to see you! Any news from Richard?";
					link.l1 = "Alas, my dear madame. Richard had to stay in Bridgetown for a while on a secret and important mission; it has something to do with the Dutch. I take it Richard has told you what he does for a living, right?";
					link.l1.go = "Abigile_kidnapping_13";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbiReturnHome")
				{
					DelLandQuestMark(npchar);
					dialog.text = "Charles! It's you! You're finally back!";
					link.l1 = "Greetings, madam. I am glad to see you.";
					link.l1.go = "Abigile_return";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbiReturnHomeGo")
				{
					dialog.text = "Ah, I am finally home! I am so glad to see Papa again! Charles, thank you for everything you have done for me!";
					link.l1 = "Please, there is no need for such talk, madam. Just doing my duty as a gentleman for a lady in distress.";
					link.l1.go = "Abigile_return_6";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SolomonHistoryNext")
				{
					dialog.text = "Papa, if you remember anything, please say it! Charles, he is... he can be trusted. I dare say, he is the only one who can help us!";
					link.l1 = "";
					link.l1.go = "Abigile_return_12";
					pchar.questTemp.HWIC.Self = "SolomonHistoryAfter";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SolomonHistoryEnd")
				{
					dialog.text = "I will pray for you night and day! Tell me... tell me that you will do it! That you will find the island!";
					link.l1 = "I will do what I can, madam.";
					link.l1.go = "Abigile_return_13";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "final" || pchar.questTemp.HWIC.Self == "VanbergDestroyed")
				{
					DelLandQuestMark(npchar);
					dialog.text = "Ah, Charles! You're back! Tell me quickly, have you found the island? I can scarcely wait any longer!";
					if (makeint(Pchar.money) >= 200000)
					{
						link.l1 = "Yes, Abi. I have found the island and your father's money. I am here to return it to you.";
						link.l1.go = "Abigile_GiveMoney";
					}
					link.l2 = "Alas, madam. I failed to find either Captain Keller or your island. I did what I could, but...";
					link.l2.go = "Abigile_NoMoney";
				break;
				}
				dialog.text = "Ah, it's you, Charles! Need anything? Can I offer you some coffee?";
				link.l1 = "No, nothing. Please don't trouble yourself.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Good day, mynheer. What is it?";
			link.l1 = "Nothing, madam. I must beg your pardon. Farewell.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

//-------------------------------------------------за Голландию-----------------------------------------------
		case "AbbyAndLucas":
			dialog.text = "I'm honoured to meet you, Captain "+GetFullName(pchar)+". I've heard all sorts of stories about you from the other ladies in town. You are the man who captured the pirate ghost ship and brought it as a prize to Willemstad. Tell me, captain... is it true that this ship was under the command of... Richard Fleetwood?";
			link.l1 = "Everything you heard is true, madame. I was as shocked as anyone to discover the truth. It's a scandal! A naval officer of the English Commonwealth plundering merchants of his own nation like a common pirate! That scoundrel tried to cloak his dastardly deeds by pretending to be a renegade 'ghost ship' under the backing of the Dutch West India Company. He used this cover to blame the Company and to attack Dutch ships as well.";
			link.l1.go = "AbbyAndLucas_1";
		break;
		
		case "AbbyAndLucas_1":
			dialog.text = "My head is spinning... It's hard to hear such horrible things, captain. I knew Richard Fleetwood personally, I'd never have thought that he...";
			link.l1 = "Madame, I have been informed by my patron Lucas Rodenburg about your voyage to Curacao from Recife. Now it is clear. Fleetwood sank your ship and then returned to 'save' you and your father from being marooned on that lost island. I read the pirate's journal myself; he recorded every detail in his logbook.";
			link.l1.go = "AbbyAndLucas_2";
		break;
		
		case "AbbyAndLucas_2":
			dialog.text = "What a nightmare... It seems my papa was right after all. He kept telling me that Richard was the pirate behind all our misfortunes. I suppose I should be glad the truth has come out... ah, I am sorry, captain. It's just so much for my poor head to take in... what could a man as important as you want with a common girl like me?";
			link.l1 = "Abigail, I am here because of a very complicated and delicate matter. Will you listen to me?";
			link.l1.go = "AbbyAndLucas_3";
		break;
		
		case "AbbyAndLucas_3":
			dialog.text = "Of course, mynheer. I am all ears.";
			link.l1 = "As I have said, I serve the Company. Lucas Rodenburg is not only my military commander, but also a good friend. He sent me to you with a message. It would bring him the greatest happiness if you were to accept his proposal of marriage. I am here to ask you to marry my patron. He is ready to do anything in the world for your happiness.";
			link.l1.go = "AbbyAndLucas_4";
		break;
		
		case "AbbyAndLucas_4":
			dialog.text = "Oh, captain! I see now why Mynheer Rodenburg wasn't ready to do it himself... My poor papa would be overjoyed, but I...";
			link.l1 = "Madame, I can see that something is troubling you. Do you doubt Mynheer Rodenburg's sincerity? Perhaps I could help you reconsider?";
			link.l1.go = "AbbyAndLucas_5";
		break;
		
		case "AbbyAndLucas_5":
			dialog.text = "Oh no captain, I have no doubt of Mynheer Rodenburg's sincerity. Lucas has done so much for me and my papa, I don't know what would happen to us if he weren't looking out for us. But please, you must understand my position!\nMy family are no Rothschilds, but we've never been poor. The Shneur family is well-known among the banking houses of Europe for our fortune... but now this dreadful pirate has ruined us! I can't abide this nasty gossip that I know goes on behind our backs, not any longer. Every chattering housewife and servant girl in this town thinks that I'm only after Mynheer Rodenburg for his money. 'How much like a Jewess,' they say. The cruel wretches! If only my father remembered the location of the island! He stashed what remains of our family fortune there to save it from the hands of those wicked pirates who murdered my sisters and my brother!\nBut my poor father is no sailor, he simply can't remember where that island and our family's money are! Please talk to my father, captain! Maybe he can recall something that could be useful to your seasoned senses. Please find that island and our fortune! You will have saved a poor girl from shame and ignominy!";
			link.l1 = "Very well, Abigail. I will speak with your father. Have faith, girl, I will do what I can.";
			link.l1.go = "AbbyAndLucas_6";
		break;
		
		case "AbbyAndLucas_6":
			dialog.text = "Thank you, mynheer. I will pray for you night and day. May the God of our fathers be with you!";
			link.l1 = "Farewell, Abigail. I'll return with good news, I swear.";
			link.l1.go = "AbbyAndLucas_7";
		break;
		
		case "AbbyAndLucas_7":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "1-27");
			pchar.questTemp.HWIC.Holl = "AbbyFather";
			AddLandQuestMark(characterFromId("Solomon"), "questmarkmain");
		break;
		
		case "AbbyAndLucas_8":
			dialog.text = "Oh, yes! Mynheer Rodenburg is an honourable and kind man. I shall give him my consent without hesitation, and I will be happy to call him my husband.";
			link.l1 = "Then I consider my errand complete. I must go now to Mynheer Rodenburg and tell him the good news. I sincerely wish you happiness, madam.";
			link.l1.go = "AbbyAndLucas_9";
		break;
		
		case "AbbyAndLucas_9":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "1-33");
			pchar.questTemp.HWIC.Holl = "AbbyAgreeMarried";//теперь к Лукасу
			AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
		break;
		
//-------------------------------------------------за Англию-----------------------------------------
		case "Seek_Island":
			dialog.text = "Richard sent you?! Blessed Mary, thank you! Ah, mynheer! I've heard that poor Richard was wounded and close to death. Is it true? Tell me, is he alive?! Is he well?!";
			link.l1 = "Richard is alive and... mostly healthy. Here's the bad news first: he's a little worse for wear and he's been temporarily blinded, but he's on the mend. Now the good news: Richard wants you to sail away with him to England where you will wed. His time in the Caribbean is over and he is waiting for your answer.";
			link.l1.go = "Seek_Island_1";
		break;
		
		case "Seek_Island_1":
			dialog.text = "Ah, my dear messenger, tell Richard that for our happiness I am ready to go with him wherever he wishes. But I fear that our elopement will kill my poor father... Sir, I am desperate and I don't know what to do. I wish Richard could find that cursed island and the chest with our family gold... Perhaps it would somehow comfort my papa in my absence.";
			link.l1 = "I see... My mission was to deliver you to Antigua, but this complicates things somewhat. If I find the island and the chest and bring them to you, will you then go with me to St. John's and Richard?";
			link.l1.go = "Seek_Island_2";
		break;
		
		case "Seek_Island_2":
			dialog.text = "Oh yes sir, I will remember you in our family prayers! I'll name our firstborn son after you! Thank you very much, captain! I will pray for you! Go, and may Christ and the Blessed Mother be with you!";
			link.l1 = "I won't keep you waiting too long, madame. I shall return soon.";
			link.l1.go = "Seek_Island_3";
		break;
		
		case "Seek_Island_3":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "2-18");
			pchar.questTemp.HWIC.Eng = "SeekIsland";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "Villemstad_houseSp2_bedroom", "goto", "goto1", "", -1);//Аби домой
			pchar.questTemp.HWIC_Coordinates = "true"; //атрибут координат на поиск острова через каюту
			DelMapQuestMarkCity("Villemstad");
		break;
		
//--------------------------------------------против всех------------------------------------------------
		case "Abigile_kidnapping":
			dialog.text = "Oh... You have a letter from him? Oh papa, don't be so harsh on our guests! You're embarrassing me with your neurotic fantasies! Mynheer, please, follow me, I want to talk with you.";
			link.l1 = "Thank you, miss. Glad to see someone in this house speaking sense.";
			link.l1.go = "Abigile_kidnapping_1";
		break;
		
		case "Abigile_kidnapping_1":
			DialogExit();
			npchar.greeting = "abigile_3";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "Villemstad_houseSp2_bedroom", "goto", "goto1", "Abigile_Stay", -1);
			NextDiag.CurrentNode = "Abigile_kidnapping_2";
			pchar.questTemp.HWIC.Self = "AbigileTalk";
			AddLandQuestMark(npchar, "questmarkmain");
		break;
		
		case "Abigile_kidnapping_2":
			DelLandQuestMark(npchar);
			dialog.text = "Forgive my father, mynheer. He is truly a good and kind man, but our... misfortunes have broken him.";
			link.l1 = "It is all right, mistress, I understand. Let me introduce myself, I am Charlie the... Knippel. I am here on the orders of Richard Fleetwood; he wants me to bring you to him. Here, please, read the letter.";
			link.l1.go = "Abigile_kidnapping_3";
		break;
		
		case "Abigile_kidnapping_3":
			RemoveItems(PChar, "NPC_Letter", 1);
			dialog.text = "Oh Richard...(reading). Oh, God! He has decided... to return all of my father's lost money! Such generosity! Dear, sweet Richard! Mynheer, you bring good news like Gabriel himself! Richard, where is he? Is he on Curacao?";
			link.l1 = "No, miss. There was an attempt on his life and he has been gravely wounded. He is on Antigua now... you haven't finished the letter.";
			link.l1.go = "Abigile_kidnapping_4";
		break;
		
		case "Abigile_kidnapping_4":
			dialog.text = "Holy Mary, conceived without sin, pray for us who have recourse to thee! Tell me, is he safe? Is his wound bad?";
			link.l1 = "Don't worry like that, miss! Richard is not the kind of man who would let some bastards kill him just like that. He is resting and recovering now. He wants me to take you to him. Then you two will sail to London... please, finish the letter, miss, you're rushing ahead.";
			link.l1.go = "Abigile_kidnapping_5";
		break;
		
		case "Abigile_kidnapping_5":
			dialog.text = "Ah, yes... I'm sorry (reading). Myheer Knippel, I am ready to sail with you. I need one day to pack my things and to talk with my papa. Come back tomorrow and I will go with you.";
			link.l1 = "Alright, lady. I'll be here tomorrow. Don't worry, my crew and I will protect you from any dangers during our voyage.";
			link.l1.go = "Abigile_kidnapping_6";
		break;
		
		case "Abigile_kidnapping_6":
			DialogExit();
			npchar.greeting = "abigile_2";
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Holl_Gambit", "3-22");
			pchar.quest.Abigile_Kidnap.win_condition.l1 = "Timer";
			pchar.quest.Abigile_Kidnap.win_condition.l1.date.hour  = 7.0;
			pchar.quest.Abigile_Kidnap.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Abigile_Kidnap.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Abigile_Kidnap.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Abigile_Kidnap.win_condition.l2 = "location";
			pchar.quest.Abigile_Kidnap.win_condition.l2.location = "Villemstad_houseSp2";
			pchar.quest.Abigile_Kidnap.function = "AbigileGoToShip";
			pchar.questTemp.HWIC.Self = "AbigileWaitNextDay";
			SetFunctionTimerCondition("AbigileGoToShipOver", 0, 0, 3, false);//таймер 3 дня, ибо нефиг
		break;
		
		case "Abigile_kidnapping_7":
			DialogExit();
			chrDisableReloadToLocation = true;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "SetAbigileToCabin", -1);//Аби в каюту к ГГ поставим
			AddQuestRecord("Holl_Gambit", "3-23");
			pchar.questTemp.HWIC.Self = "AbigileOnShip";
			pchar.quest.AbigileGoToShipOver.over = "yes";//снять таймер
			SetFunctionTimerCondition("RemoveAbigileOver", 0, 0, 30, false);//таймер на 1 месяц, ибо нефиг
			pchar.quest.Abigile_died.win_condition.l1 = "NPC_Death";
			pchar.quest.Abigile_died.win_condition.l1.character = "Abigile";
			pchar.quest.Abigile_died.function = "AbigileDied";//специально для особо упоротых
			AddMapQuestMarkCity("SentJons", false);
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
		break;
		
		case "Abigile_kidnapping_8":
			DelLandQuestMark(npchar);
			dialog.text = "Ah, what a pity. But I think I can wait another week, as I have waited before...";
			link.l1 = "Well said, miss. And to ease your wait, I propose we exchange this rather austere cabin for my friend's house. There will be a soft bed and fine food prepared for you.";
			link.l1.go = "Abigile_kidnapping_9";
		break;
		
		case "Abigile_kidnapping_9":
			dialog.text = "You are so kind, Charlie. Thank you. It will be good to have land under my feet... I feel quite queasy after all this tossing about on the waves.";
			link.l1 = "Follow me, please, miss.";
			link.l1.go = "Abigile_kidnapping_10";
		break;
		
		case "Abigile_kidnapping_10":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.questTemp.HWIC.Self = "AbigileInHouse";
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
		break;
		
		case "Abigile_kidnapping_11":
			dialog.text = "I am glad to meet you, John. Thank you for your kind hospitality, gentlemen!";
			link.l1 = "...";
			link.l1.go = "Abigile_kidnapping_12";
		break;
		
		case "Abigile_kidnapping_12":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "SentJons_HouseF3_Room2", "barmen", "bar1", "ContinueWithMerdok", -1);
			pchar.questTemp.HWIC.Self = "AbigileInRoom";
			NextDiag.CurrentNode = "First time";
			RemovePassenger(Pchar, npchar);
			pchar.quest.RemoveAbigileOver.over = "yes";//снять таймер
			sld = characterFromId("Merdok");
			LAi_SetActorType(sld);//чтобы геймер сам с ним не заговорил
		break;
		
		case "Abigile_kidnapping_13":
			DelLandQuestMark(npchar);
			dialog.text = "Oh Charlie, I've only seen Richard a few times and he didn't tell me much about what he does.";
			link.l1 = "I'm quite surprised that he would hide such a great secret from the woman he loves... Miss, Richard is not just an ordinary captain. He is also a special agent of the English Privy Council. A very important man who deals with delicate assignments directly ordered by the Lord Protector himself. Right now, his duty is concerned with destroying the trading power of the Dutch West India Company in the Caribbean.";
			link.l1.go = "Abigile_kidnapping_14"
		break;
		
		case "Abigile_kidnapping_14":
			dialog.text = "Sir, what are you talking about?";
			link.l1 = "Yes, miss. Your beloved Richard - my friend - is a very important man. I was always proud to be his friend, but he has become very secretive, even with me. It is obvious that he is on some secret mission. I am very sorry that this mission doesn't allow him to meet you.";
			link.l1.go = "Abigile_kidnapping_15";
		break;
		
		case "Abigile_kidnapping_15":
			dialog.text = "Charlie, you're scaring me. Are you sure he's alright?";
			link.l1 = "I am sure of that. I just... I don't approve of how he's treating you right now. I understand that his assignment is vital and he can't betray his duty, even for you.";
			link.l1.go = "Abigile_kidnapping_16";
		break;
		
		case "Abigile_kidnapping_16":
			dialog.text = "Oh, my dear Charlie... I will wait for Richard until the Second Coming if need be. Perhaps I could stay above the tavern... I can't keep taking advantage of John's hospitality for so long.";
			link.l1 = "Stop speaking nonsense, lady! Your presence honours us and my name's not Charlie the Knippel if I turn the fiancée of my dear friend Richard Fleetwood out of house and home!";
			link.l1.go = "Abigile_kidnapping_17";
		break;
		
		case "Abigile_kidnapping_17":
			dialog.text = "Charlie... I am truly touched by your feelings for me. I am just a common girl, and a Jewess at that...";
			link.l1 = "Miss! I know that's foolhardy talk, you're a fine Christian young woman! And don't even think about taverns! I would never forgive myself if I failed you in my service to Richard.";
			link.l1.go = "Abigile_kidnapping_18";
		break;
		
		case "Abigile_kidnapping_18":
			dialog.text = "Thank you, Charlie. I'm glad that you are such a... good man.";
			link.l1 = "It is my duty, miss. Now, I am sorry, but I have to go. You are free to walk around the town now; you must feel quite lonely confined in this house, am I right?";
			link.l1.go = "Abigile_kidnapping_19";
		break;
		
		case "Abigile_kidnapping_19":
			dialog.text = "Well... John is very interesting company. He can talk about his powders, mixtures, and various... diseases for hours. He is a polite and gracious man as well. Also, I go regularly to church, the local priest is quite kind... but, of course, I really miss Richard.";
			link.l1 = "I think he'll be back soon. Charlie the Knippel is at your service if you need anything.";
			link.l1.go = "Abigile_kidnapping_20";
		break;
		
		case "Abigile_kidnapping_20":
			DialogExit();
			pchar.questTemp.HWIC.Self = "MeetTonzag";
			pchar.quest.Meet_Tonzag.win_condition.l1 = "location";
			pchar.quest.Meet_Tonzag.win_condition.l1.location = "SentJons_TownCave";
			pchar.quest.Meet_Tonzag.function = "TonzagMeetingInDange";
		break;
		
		case "Abigile_return":
			dialog.text = "I've heard rumours about Richard... that he's disappeared. Do you know anything about it, Charlie?";
			link.l1 = "I do, Abigail. I'm sorry... Richard Fleetwood has gone off to England and he won't be back. He got a promotion or transfer, something like that... anyway, after what he's done to you, I don't want to know him.";
			link.l1.go = "Abigile_return_1";
		break;
		
		case "Abigile_return_1":
			dialog.text = "Ah, I knew it would end like this....(sobs) Why didn't I listen to Papa! At least, he would have been glad if I'd married Lucas Rodenburg.";
			link.l1 = "Forgive me again, miss...";
			link.l1.go = "Abigile_return_2";
		break;
		
		case "Abigile_return_2":
			dialog.text = "For what, Charlie? You are not guilty at all. You've been nothing but kind to me!";
			link.l1 = "For me to tell you even more bad news. I've just returned from Curacao; Lucas Rodenburg has been arrested for sedition and treason against the Republic. He is being sent back to Amsterdam in chains to stand trial. He tried to murder Peter Stuyvesant, director of the Company. On top of that, he attempted to overthrow the governor of Willemstad and is suspected of the murder of at least one other person, so I doubt the Stadtholder is going to let him off with a slap on the wrist.";
			link.l1.go = "Abigile_return_3";
		break;
		
		case "Abigile_return_3":
			dialog.text = "Oh God! What a nightmare! I think I'm going to faint! Charles, is it true? No, please say it isn't!";
			link.l1 = "Sorry, miss, it gets worse. It has been revealed during the investigation of Rodenburg's actions that the pirate who sank your fluyt was acting under the orders of Lucas Rodenburg. He was waging a private war of his own against English shipping. I am so sorry, Abigail. All the men you've faced here in the Caribbean have been liars, thieves, and murderers.";
			link.l1.go = "Abigile_return_4";
		break;
		
		case "Abigile_return_4":
			dialog.text = "Oh... I am ruined. Charles... please... take me back home to Willemstad. I need my papa...";
			link.l1 = "Of course, dear miss. Unfortunately, there is nothing for you here in Bridgetown. Go, pack your things, say goodbye to John, and we will set sail immediately.";
			link.l1.go = "Abigile_return_5";
		break;
		
		case "Abigile_return_5":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-57");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload4", false);//откроем комнату Аби
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.questTemp.HWIC.Self = "AbiReturnHomeGo";
			pchar.quest.AbiReturn_Home.win_condition.l1 = "location";
			pchar.quest.AbiReturn_Home.win_condition.l1.location = "Villemstad_town";
			pchar.quest.AbiReturn_Home.function = "AbiGoInVillemstad";
			AddMapQuestMarkCity("Villemstad", true);
		break;
		
		case "Abigile_return_6":
			dialog.text = "No, Charlie, I need to thank you. If it weren't for you and John, I don't even know what would have happened to me. You are the only honest men I have met in the archipelago.";
			link.l1 = "Hm... you are making me blush, Abigail. I was glad to help you. And I am very sorry for all this mess.";
			link.l1.go = "Abigile_return_7";
		break;
		
		case "Abigile_return_7":
			dialog.text = "You know, Charlie, I have been thinking a lot during our voyage to Curacao. Everything is clear now - Richard Fleetwood, Mynheer Rodenburg - it all seems like a horrible nightmare that has finally ended. I am with my father again and we can return to a normal life\nIt won't be easy though - we don't have any money. But we will get through it, everything is going to be fine. The Blessed Mother will take care of us, she never forgets her children, even my stubborn old father who denies Her Son.";
			link.l1 = "Miss Abigail, I'm going to help you.";
			link.l1.go = "Abigile_return_8";
		break;
		
		case "Abigile_return_8":
			dialog.text = "Help us? But how, Charlie?";
			link.l1 = "Richard told me the story of your shipwreck and your rescue. Also, I know that your father managed to hide his belongings on an uncharted island. I'm going to find it and bring back your money.";
			link.l1.go = "Abigile_return_9";
		break;
		
		case "Abigile_return_9":
			dialog.text = "Oh Charlie... Neither my father nor I can tell you where that ill-fated island is... We are not sailors. On top of that, I was terrified for my life during the attack; I don't remember a thing besides blood and the smell of death.";
			link.l1 = "Abigail, try to remember. Please, any details could help me, even the smallest ones. Did anything happen before the attack? What does this island look like?";
			link.l1.go = "Abigile_return_10";
		break;
		
		case "Abigile_return_10":
			dialog.text = "Island... It looks like an island? A bay, jungles. Nothing really stood out to me. Oh, I remember! Perhaps this will help you. Not long before the pirate attack, we met a fluyt and hailed its captain. He was invited aboard our ship and had dinner with our captain. We were there too. Perhaps he knows about this island.";
			link.l1 = "That is something! What were the names of the fluyt and her captain?";
			link.l1.go = "Abigile_return_11";
		break;
		
		case "Abigile_return_11":
			dialog.text = "I don't remember, Charlie. I truly don't...";
			link.l1 = "Try to remember, Abi!";
			link.l1.go = "Abigile_return_12";
			pchar.questTemp.HWIC.Self = "SolomonHistory";
		break;
		
		case "Abigile_return_12":
			DialogExit();
			sld = characterFromId("Solomon");
			sld.greeting = "solomon_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Abigile_return_13":
			dialog.text = "We will be waiting for you. Help me, Charlie the Knippel. You're our only hope... I will pray for you! Godspeed!";
			link.l1 = "I am on my way. Farewell, Abi. Farewell, Solomon.";
			link.l1.go = "Abigile_return_14";
		break;
		
		case "Abigile_return_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "Villemstad_houseSp2_bedroom", "goto", "goto1", "ReturnAbiNormal", -1);
			pchar.questTemp.HWIC.Self = "SeekFleut";
			AddQuestRecord("Holl_Gambit", "3-58");
			AddLandQuestMark(characterFromId("Villemstad_PortMan"), "questmarkmain");
		break;
		
		case "Abigile_NoMoney":
			dialog.text = "Oh, dear... what a pity. We were hoping, but... thank you anyway, Charlie, for even trying to help us when no one else would. It seems this is the fate that God has set out for me.";
			link.l1 = "Farewell, Abigail. I hope you will be all right.";
			link.l1.go = "exit";
			npchar.dialog.currentnode = "Abigile_Poor";
		break;
		
		case "Abigile_GiveMoney":
			dialog.text = "Is it... is it true? Have you really brought our lost money back to us? Oh, Charlie!";
			link.l1 = "Yes, it's true. I have it. Here, take it. It's all yours.";
			link.l1.go = "Abigile_GiveMoney_1";
		break;
		
		case "Abigile_GiveMoney_1":
			AddMoneyToCharacter(pchar, -200000);
			pchar.quest.MakeAbiPoor.over = "yes"; //снять прерывание
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			dialog.text = "How can I ever thank you?! How?!";
			link.l1 = "I don't need any thanks, Abi. It's the least I could do for you. Now you can start a new life without any Rodenburgs, Fleetwoods, or any other strange men trying to take advantage of you. I'm sure your father can find a way to make this money grow... seems like an inherited trait.";
			link.l1.go = "Abigile_GiveMoney_2";
		break;
		
		case "Abigile_GiveMoney_2":
			dialog.text = "Charlie, don't be so cheeky! You have done so much for me, for me and for my poor father. Why, I've grown accustomed to your presence in my life. I have been praying tirelessly for you every day, and I'll keep praying for you and your crew to the Blessed Mother every day to come! You are our guardian angel. The Lord himself has sent you to our family, believe it or not\nBefore you go, I want you to know that the doors of our house will always be open for you at any time. And... please, let me kiss you, my dear Charlie...";
			link.l1 = "Well... yes, sure, Abi... if you insist.";
			link.l1.go = "Abigile_GiveMoney_3";
		break;
		
		case "Abigile_GiveMoney_3":
			DialogExit();
			npchar.greeting = "abigile_1";
			npchar.dialog.currentnode = "Abigile_AllRight";
			
			StartQuestMovie(true, false, true);
			LAi_SetActorType(pchar);
			LAi_Fade("AbiKiss", "");
		break;
		
		case "Abigile_Poor":
			dialog.text = "God bless you, Charles. Nothing has changed for us... I beg for scraps outside the church.";
			link.l1 = "Stay strong, miss. God be with you.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Abigile_Poor";
		break;
		
		case "Abigile_AllRight":
			dialog.text = "Charles, it's you! I'm so glad to see you! Please, sit down! I'll brew some coffee!";
			link.l1 = "I am glad to see you too, Abi. And I am glad that you are doing well.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Abigile_AllRight";
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Woman_FackYou":
			dialog.text = "Ah, so that's it?! I welcomed you as my guest and you decided to rob me?! Guards!!!";
			link.l1 = "Shut your mouth, foolish girl.";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}

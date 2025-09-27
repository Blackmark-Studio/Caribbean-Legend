// диалог индейцев в поселениях
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "We have nothing to talk about!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		// ==> индейцы в поселении
		case "IndianMan":
			NextDiag.TempNode = "IndianMan";
			dialog.text = NPCStringReactionRepeat(""+GetSexPhrase("Paleface","White squaw")+" wants to talk?","You again, "+GetSexPhrase("Paleface","White squaw")+".",""+GetSexPhrase("Paleface likes to talk. He looks like a squaw.","White squaw likes to talk.")+"","Spirits brought my pale face "+GetSexPhrase("brother","sister")+" to me.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Yes.","Yeah, me again.","Very poetic.","I am also happy to see you.",npchar,Dialog.CurrentNode);
			link.l1.go = "IndPearlMan_1";
		break;
		
		case "IndPearlMan_1":
			dialog.text = "Say, why have you come, pale face?";
			link.l1 = "Oh, nothing in particular, just wanted to hear what you had to say...";
			link.l1.go = "exit";
		break;
		
		case "IndianWoman":
			NextDiag.TempNode = "IndianWoman";
			dialog.text = NPCStringReactionRepeat("White man wants to talk?","You again, pale face?","Paleface likes to talk.","Spirits brought my pale-faced brother to me.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Yes.","Yeah, me again.","Very poetic.","I am glad to see you too.",npchar,Dialog.CurrentNode);
			link.l1.go = "IndianWoman_1";
		break;
		
		case "IndianWoman_1":
			dialog.text = LinkRandPhrase(""+npchar.name+" listen to you, son of the sea.","What do you want from "+npchar.name+", paleface?","My ears are open to your words, stranger.");
			if (CheckIndianGift() && !CheckAttribute(npchar, "quest.gift"))
			{
				link.l1 = LinkRandPhrase("I have something for you. Want to take a look?","Want to take a look at something really interesting? You'll surely like it...","I have something that will please you, child of the jungle. Want to take a look?");
				link.l1.go = "gift";
			}
			link.l9 = "Oh, nothing in particular, just wanted to hear what you had to say...";
			link.l9.go = "exit";
		break;
		
		case "gift":
			iTemp = 2;
			dialog.text = RandPhraseSimple(""+npchar.name+" wants to look. Show it.",""+npchar.name+" is interested. Show me.");
			if (CheckCharacterItem(pchar, "mineral6"))
			{
				link.l1 = "Give me a mirror.";
				link.l1.go = "gift_1";
			}
			for (i=50; i>=47; i--)
			{
				if (CheckCharacterItem(pchar, "jewelry"+i))
				{
					sTemp = "l"+iTemp;
					link.(sTemp) = "Give"+XI_ConvertString("jewelry"+i)+".";
					link.(sTemp).go = "gift_"+i;
					iTemp++;				
				}
			}
		break;
		
		case "gift_1":
			RemoveItems(pchar, "mineral6", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Oh! Now "+npchar.name+" can look at herself not only in the river water! Thank you, kind stranger!";
			link.l1 = "Sure, now you can admire your face as much as you like...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_47":
			RemoveItems(pchar, "jewelry47", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Oh! So beautiful! This bracelet is for "+npchar.name+"? Thank you, kind stranger!";
			link.l1 = "Put it on your swarthy hand, beauty, you'll look stunning...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_48":
			RemoveItems(pchar, "jewelry48", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Oh! What a beautiful ring! It's for "+npchar.name+", yes? Thank you, kind stranger!";
			link.l1 = "Put it on your finger, and all your friends will be jealous...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_49":
			RemoveItems(pchar, "jewelry49", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Oh! Those wonderful green beads are for "+npchar.name+"? So beautiful! Thank you, kind stranger!";
			link.l1 = "Adorn your neck with them, daughter of the selva. Everyone will admire you...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_50":
			RemoveItems(pchar, "jewelry50", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Oh, what a beautiful green ring! Is this a gift for "+npchar.name+"? Thank you, kind stranger!";
			link.l1 = "It will look great on your hand, pretty one...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_exit":
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Merida.Women")) // Addon 2016-1 Jason Пиратская линейка
			{
				dialog.text = "Wanted to ask "+npchar.name+" Anything, son of the sea?";
				link.l1 = "You are right, pretty one. My fearless warriors and I are going to the selva, to the Spanish settlement among the mountains, and we are looking for a guide. I will be generous to the man himself and also to his wife. I have many riches: beautiful guns, magic glasses, mirrors, necklaces, bracelets, and rings. Perhaps your husband can be the guide we are looking for?";
				link.l1.go = "hayamee";
			}
			else
			{
				DialogExit();
			}
			ChangeIndianRelation(1.00);
			npchar.quest.gift = true;
		break;
		
		// Addon 2016-1 Jason Пиратская линейка
		// Кумвана, вождь деревни араваков
		case "cumvana":
			dialog.text = "Greetings, son of the sea. I am Kumwana, chief of the Turtle clan of the Locono people. What business brings you to my village?";
			if (GetCharacterFreeItem(pchar, "pistol5") > 0 || CheckCharacterItem(pchar, "compass1") || GetCharacterFreeItem(pchar, "spyglass1") > 0 || GetCharacterFreeItem(pchar, "spyglass2") > 0 || GetCharacterFreeItem(pchar, "spyglass3") > 0)
			{
				link.l1 = "I brought you a gift, chief. Take a look, you'll like it.";
				link.l1.go = "cumvana_2";
			}
			else 
			{
				link.l1 = "Chief, I've come to ask for your assistance. I want to reach a Spanish settlement called Merida. It's located among the mountains in your selva, but the problem is I don't know how to get there.";
				link.l1.go = "cumvana_no";
			}
			DelLandQuestMark(npchar);
		break;
		
		case "cumvana_no":
			dialog.text = "That is very good for you, son of the sea, not knowing the way there. It leads through a forest, the land of the fearless Capong tribe. True jaguars, they are, oh-ey! Me never go to that Spanish place. My people - peaceful people, we do not go to the land of Capong. Kumwana cannot give you advice. The road is too dangerous.";
			link.l1 = "But the Spanish found a way there! And I am not afraid of those Capons...";
			link.l1.go = "cumvana_no_1";
		break;
		
		case "cumvana_no_1":
			dialog.text = "But you should. They are cruel people. They killed many of my people in the woods. Kumwana said it all.";
			link.l1 = "Well, shit...";
			link.l1.go = "cumvana_no_2";
		break;
		
		case "cumvana_no_2":
			DialogExit();
			AddQuestRecord("Roger_5", "5");
			npchar.dialog.currentnode = "cumvana_1";
		break;
		
		case "cumvana_1":
			dialog.text = "Oh-ey! You again, son of the sea. What do you want to say to Kumwana?";
			if (GetCharacterFreeItem(pchar, "pistol5") > 0 || CheckCharacterItem(pchar, "compass1") || GetCharacterFreeItem(pchar, "spyglass1") > 0 || GetCharacterFreeItem(pchar, "spyglass2") > 0 || GetCharacterFreeItem(pchar, "spyglass3") > 0)
			{
				link.l1 = "I brought you a gift, chief. Take a look, you're going to like it.";
				link.l1.go = "cumvana_2";
			}
			else 
			{
				link.l1 = "The hope of finding Merida is still with me...";
				link.l1.go = "cumvana_1_1";
			}
		break;
		
		case "cumvana_1_1":
			DialogExit();
			npchar.dialog.currentnode = "cumvana_1";
		break;
		
		case "cumvana_2":
			dialog.text = "Locono are always glad to see good friends.";
			if (GetCharacterFreeItem(pchar, "pistol5") > 0)
			{
				link.l1 = "Gift a handgun."; // 5
				link.l1.go = "cumvana_2_1";
			}
			if (CheckCharacterItem(pchar, "compass1")) // 3
			{
				link.l2 = "Give a compass as a gift.";
				link.l2.go = "cumvana_2_2";
			}
			if (GetCharacterFreeItem(pchar, "spyglass1") > 0)
			{
				link.l3 = "Give a cheap spyglass as a gift.";
				link.l3.go = "cumvana_2_3";
			}
			if (GetCharacterFreeItem(pchar, "spyglass2") > 0)
			{
				link.l4 = "Give a common spyglass as a gift."; // 2
				link.l4.go = "cumvana_2_4";
			}
			if (GetCharacterFreeItem(pchar, "spyglass3") > 0)
			{
				link.l5 = "Give a decent spyglass."; // 4
				link.l5.go = "cumvana_2_5";
			}
		break;
		
		case "cumvana_2_1":
			Log_Info("You have given a pistol");
			//Log_Info("You have received amulets");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "pistol5", 1);
			GiveItem2Character(pchar, "obereg_9");
			GiveItem2Character(pchar, "indian_7");
			GiveItem2Character(pchar, "obereg_3");
			dialog.text = "Oh-ey! What a fine paleface weapon! Kumwana accepts your gift! You too, son of the sea, accept a gift from Kumwana and the Locono people.";
			link.l1 = "Thank you, chief!..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_2":
			Log_Info("You have given a compass");
			//Log_Info("You have received amulets");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "compass1", 1);
			GiveItem2Character(pchar, "indian_10");
			GiveItem2Character(pchar, "indian_6");
			GiveItem2Character(pchar, "obereg_1");
			dialog.text = "Oh-ey! Magic amulet of the pale-faces! Kumwana accepts your gift! You too, son of the sea, accept a gift from Kumwana and the Locono people.";
			link.l1 = "Thank you, chief!..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_3":
			Log_Info("You have given a cheap spy glass");
			//Log_Info("You have received amulets");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "spyglass1", 1);
			GiveItem2Character(pchar, "obereg_2");
			GiveItem2Character(pchar, "indian_5");
			GiveItem2Character(pchar, "obereg_1");
			dialog.text = "Oh-ey! Magic tube of the pale-faces! Kumwana accepts your gift! You too, son of the sea, accept a gift from Kumwana and the Locono people.";
			link.l1 = "Thank you, chief!..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_4":
			Log_Info("You have given a common spy glass");
			//Log_Info("You have received amulets");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "spyglass2", 1);
			GiveItem2Character(pchar, "obereg_6");
			GiveItem2Character(pchar, "indian_6");
			GiveItem2Character(pchar, "obereg_1");
			dialog.text = "Oh-ey! Magic tube of the pale-faces! Kumwana accepts your gift! You too, son of the sea, accept a gift from Kumwana and the Locono people.";
			link.l1 = "Thank you, chief!..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_5":
			Log_Info("You have given a decent spy glass");
			//Log_Info("You have received amulets");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "spyglass3", 1);
			GiveItem2Character(pchar, "obereg_9");
			GiveItem2Character(pchar, "indian_7");
			GiveItem2Character(pchar, "obereg_5");
			dialog.text = "Oh-ey! Magic tube of palefaces! Kumwana accepts your gift! You too, son of the sea, accept a gift from Kumwana and the Locono people.";
			link.l1 = "Thank you, chief!..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_3":
			dialog.text = "What brings you to our village, son of the sea?";
			link.l1 = "Chief, I've come to ask for your assistance. I want to reach a Spanish settlement called Merida; it's located among the mountains in your selva. The problem is, I don't know how to get there. Perhaps you could provide me with a brave warrior who could show us the way?";
			link.l1.go = "cumvana_4";
		break;
		
		case "cumvana_4":
			dialog.text = "Oh-ey! Dangerous road, dangerous. The way there leads through a forest, land of the fearless Capong tribe. True jaguars, they are, oh-ey! Me never go that Spanish place. My people - peaceful people, we not go to land of Capong.";
			link.l1 = "I really must get to Merida. Kumwana, please ask your men, perhaps someone will agree to join my unit? My warriors are experienced, well-armed, and fear nothing, not even the Devil. We will protect the guide and reward him generously when it's over.";
			link.l1.go = "cumvana_5";
		break;
		
		case "cumvana_5":
			dialog.text = "Very well, son of the sea. I will gather a circle of warriors and tell them of your wishes. See me tomorrow after dawn.";
			link.l1 = "Thank you, chief!";
			link.l1.go = "cumvana_6";
		break;
		
		case "cumvana_6":
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_SetStayType(pchar);
			npchar.dialog.currentnode = "cumvana_7";
			//AddQuestRecord("Roger_5", "6");
			AddCharacterExpToSkill(pchar, "Leadership", 150);
			SetLaunchFrameFormParam("The next day...", "Mtraxx_MeridaVozhdDialog", 0, 4.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 1, 0, 0);
			RecalculateJumpTable();
		break;
		
		case "cumvana_7":
			dialog.text = "Oh-ey! You again, son of the sea. What do you want to say to Kumwana?";
			link.l1 = "Nothing yet, chief.";
			link.l1.go = "cumvana_7x";
			if(CheckAttribute(pchar,"questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "merida_hayamee")
			{
				link.l2 = " Listen, Kumwana. My people and I really need to cross the river and reach that damned little town. Let me explain just how crucial this is for us.";
				link.l2.go = "cumvana_hard";
			}
		break;
		
		case "cumvana_hard":
			dialog.text = "My hunters have already informed you that...";
			link.l1 = "There is no need to repeat yourself, Kumwana. But look outside – and don’t overestimate your abilities. My brave men who came here for Spanish stones are scattered throughout your village. And their patience is wearing thin. And what will happen when it finally runs out, it’s better for you not to know – believe me.";
			link.l1.go = "cumvana_medium_1";
			link.l2 = "Shut your mouth and listen, red-skinned ape. My people can be far more fearsome than these damned Kapongs. Do not be deceived by our kindness now. I give you a simple choice: either you find a guide within twenty-four hours, or we will tie you all up and send you through the jungle ahead of our squad. If you lead us in the wrong direction, you yourself will perish in the swamps or go bound to fight the Kapongs. Got it?";
			link.l2.go = "cumvana_hard_1";
			link.l3 = "Kumwana, I need this guide. We've come a long way, and I really don't want to tell my men that it was all in vain.";
			link.l3.go = "cumvana_good_1";
			pchar.questTemp.Mtraxx_MeridaZapugivanieIndeets = true;
		break;
		
		case "cumvana_good_1":
			dialog.text = "Kumwana already said, none of the Lokono want to go with the paleface.";
			link.l1 = "And you can't do anything about it? Ask someone personally. Give an order, after all. Are you the chief or not?";
			link.l1.go = "cumvana_good_2";
		break;
		
		case "cumvana_good_2":
			dialog.text = "The chief does not force the Indian. The chief rules and wants peace for his people. The Indians know - the Kapong will see that the Lokono bring the palefaces. Their heads are to be taken by Kanaima. They come to take revenge on the Lokono. Kapong - to kill. Capture the Lokono, make slaves.";
			link.l1 = "And who took your heads? What spirit or demon makes the Indians such cowardly maggots? Well, perhaps I really will have to abandon the campaign against Merida. But remember something, chief. Whenever I am asked what I know about the Lokono, I will invariably answer - that they are a tribe of worthless cowards. Led by a ruler as cowardly and short-sighted as they are, whose face is twisted in a grimace of horror at the mere memory of the Kapongs. You will not gain glory among the Indians, nor respect among us, the palefaces.";
			link.l1.go = "cumvana_good_3";
		break;
		
		case "cumvana_good_3":
			dialog.text = "Paleface does not know the customs of the Indians...";
			link.l1 = "I know enough to know whom the Indians call a coward and whom they call a brave warrior. Farewell, Kumwana. And remember my words. You are a cowardly and short-sighted ruler.";
			link.l1.go = "cumvana_good_4";
		break;
		
		case "cumvana_good_4":
			DialogExit();
			ChangeIndianRelation(5.00);
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Merida.Women")) DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Women");
			pchar.questTemp.Mtraxx = "fail";
			
			pchar.quest.Mtraxx_MeridaHayameeGoodDialog.win_condition.l1 = "location";
			pchar.quest.Mtraxx_MeridaHayameeGoodDialog.win_condition.l1.location = "Locono_village";
			pchar.quest.Mtraxx_MeridaHayameeGoodDialog.function = "Mtraxx_MeridaHayameeGoodDialog";
		break;
		
		case "cumvana_medium_1":
			dialog.text = "Why threaten me like this? We think you're a good person...";
			link.l1 = "I'm good, as long as you cooperate, got it? You've got one day. And trust me, my people will do whatever I order. We're stronger. And if you doubt it... I've seen your wife. And your daughters. I think you've got the message now.";
			link.l1.go = "cumvana_hard_2";
			AddCharacterExpToSkill(pchar, "Leadership", 300);
		break;
		
		case "cumvana_hard_1":
			dialog.text = "Why threaten me like this? We think you're a good person...";
			link.l1 = "I'm good, as long as you cooperate, got it? You've got one day. And trust me, my people will do whatever I order. We're stronger. And if you doubt it... I've seen your wife. And your daughters. I think you've got the message now.";
			link.l1.go = "cumvana_hard_2";
		break;
		
		case "cumvana_hard_2":
			dialog.text = "Kumwana understands, pale face. In the village, there's a hunter named Tagofa. Perhaps he can guide you to the settlement...";
			link.l1 = "I'll return in twenty-four hours. Charlie Prince has nothing more to add, savage.";
			link.l1.go = "cumvana_hard_3";
		break;
		
		case "cumvana_hard_3":
			DialogExit();
			ref Hayam = characterFromId("Hayamee");
			ChangeCharacterAddressGroup(Hayam, "none", "", "");
			Hayam.lifeday = 0;
			pchar.questTemp.Mtraxx = "merida_hayamee_hard";
			npchar.dialog.currentnode = "cumvana_7";
			SetFunctionTimerCondition("Mtraxx_MeridaHayameeHardTagofaWait", 0, 0, 1, false);
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Merida.Women")) DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Women");
			ChangeCharacterComplexReputation(pchar, "nobility", -80);
			ChangeOfficersLoyality("bad", 5);
			ChangeIndianRelation(-50.0);
			//log_Info("The attitude of the Indians has decreased");
			AddQuestRecord("Roger_5", "8a");
			pchar.GenQuest.CannotWait = true; //запретить отдыхать
			
			pchar.quest.Mtraxx_MeridaHayameeHardLepriconDialog.win_condition.l1 = "location";
			pchar.quest.Mtraxx_MeridaHayameeHardLepriconDialog.win_condition.l1.location = "Locono_village";
			pchar.quest.Mtraxx_MeridaHayameeHardLepriconDialog.function = "Mtraxx_MeridaHayameeHardLepriconDialog";
		break;
		
		case "cumvana_7x":
			DialogExit();
			npchar.dialog.currentnode = "cumvana_7";
		break;
		
		case "cumvana_8":
			dialog.text = "Son of the sea, it's you. Kumwana spoke with the warriors of the Locono.";
			link.l1 = "And? Do you have a volunteer?";
			link.l1.go = "cumvana_9";
		break;
		
		case "cumvana_9":
			dialog.text = "We have a few hunters around who have been there. But they fear Capongs, the jaguars are on the warpath. They won't go, they say Capong will kill your unit. They do not fear palefaces.";
			link.l1 = "My warriors are far superior to any of them! Part of my unit has spent a lifetime in the jungle! We are not mere amateurs!";
			link.l1.go = "cumvana_10";
		break;
		
		case "cumvana_10":
			dialog.text = "I am sorry, son of the sea. My hunters are afraid, Capongs are very, very dangerous.";
			link.l1 = "Fine, then perhaps they can explain how to get there? In detail.";
			link.l1.go = "cumvana_11";
		break;
		
		case "cumvana_11":
			dialog.text = "To get there you should sail along the river and then disembark at a specific spot. If you choose the wrong place, you'll end up in the swamp and die. Our selva is full of danger. You won't find the place on your own, son of the sea.";
			link.l1 = RandSwear()+"And what should I do then? How can I persuade your hunters?";
			link.l1.go = "cumvana_12";
		break;
		
		case "cumvana_12":
			dialog.text = "Kumwana, say no more, son of the sea.";
			link.l1 = "Fine...";
			link.l1.go = "cumvana_13";
		break;
		
		case "cumvana_13":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetPlayerType(pchar);
			npchar.dialog.currentnode = "cumvana_7";
			AddQuestRecord("Roger_5", "7");
			pchar.questTemp.Mtraxx = "merida_advice";
			LAi_SetHuberType(npchar);
			AddLandQuestMark(characterFromId("Lepricon"), "questmarkmain");
		break;
		
		// Хайами
		case "hayamee":
			if (npchar.id == "Hayamee")
			{
				dialog.text = "My husband Tagofa is the best hunter of the tribe. Oh-ey! "+npchar.name+" is proud of her husband. "+npchar.name+" often goes with Tagofa in Selva. Goes far away. Tagofa knows where the Spanish settlement is.";
				if (IsCharacterPerkOn(pchar, "Trustworthy") && stf(pchar.questTemp.Indian.relation) >= 40.0)
				{
					link.l1 = "Does Tagofa know the way to the Spanish city the pale-faces call Merida?";
					link.l1.go = "hayamee_1";
				}
				else
				{
					link.l1 = "Well, well... Does Tagofa know how to get to the Spanish city?";
					link.l1.go = "hayamee_bad_1";
				}
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = RandPhraseSimple(RandPhraseSimple("My husband does not go to the selva, son of the sea. He catches fish. Good fisherman, oh-ey! ","My husband is a good hunter, oh-ey, but he does not go deep into the jungle."),RandPhraseSimple("A jaguar wounded my husband while hunting. Now he sits in the village making arrows, oh-ey!","Six moons ago, three Capongs attacked my husband. Now he does not go hunting far from the village. Never! Oh-ey!"));
				link.l1 = LinkRandPhrase("Pity...","Too bad...","What a pity..."));
				link.l1.go = "exit";
			}
		break;
		
		case "hayamee_bad_1":
			dialog.text = "Tagofa grew up in this jungle. He knows every tree and every stone around!";
			link.l1 = "I will give you and Tagofa many gifts if he takes us there. Jewellery, weapons, anything. Anything you want. Within reason, of course, he-he. How can I speak to your husband?";
			link.l1.go = "hayamee_bad_2";
		break;
		
		case "hayamee_bad_2":
			dialog.text = "Tagofa will not go with the paleface. Tagofa will stay in the village. Go hunting. Do not fight with the Kapong.";
			link.l1 = "He won't have to fight the Kapong. As soon as he sees them, he can hide. Only my people will fight.";
			link.l1.go = "hayamee_bad_3";
		break;
		
		case "hayamee_bad_3":
			dialog.text = "No, yalanaui. The paleface never keeps his word. The paleface speaks - and the word immediately flies away into the void. The Kapong will kill Tagofa and then come to our village, kill the Lokono.";
			link.l1 = "Do you think these Kapongs are all you have to worry about? You are very wrong...";
			link.l1.go = "hayamee_bad_4";
			if (stf(pchar.questTemp.Indian.relation) < 40.0) notification("The Indians don't respect you "+stf(pchar.questTemp.Indian.relation)+"/40", "None");
			if (!IsCharacterPerkOn(pchar, "Trustworthy")) notification("Perk Check Failed", "Trustworthy");
		break;
		
		case "hayamee_bad_4":
			dialog.text = "Yahahu to enter into the paleface! Hayami will no longer speak to yalanaui.";
			link.l1 = "Well, well...";
			link.l1.go = "hayamee_bad_5";
		break;
		
		case "hayamee_bad_5":
			DialogExit();
			pchar.questTemp.Mtraxx = "merida_hayamee";
			DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Women");
			LAi_CharacterDisableDialog(npchar);
		break;
		case "hayamee_1":
			dialog.text = "Tagofa went hunting a day ago. Promised to come back tomorrow when the sun sleeps. Come tomorrow, son of the sea, I will be with Tagofa in that hut; as you walk into the village, walk to the right. I will ask him if he will go or not go with you.";
			link.l1 = "Tell Tagofa that I will gift him the prettiest handgun. And you, I will gift with a lot of jewels.";
link.l1.go = "hayamee_1_1";
		break;
		
		case "hayamee_1_1":
			dialog.text = "Lokono do not trust the Yalanaui. Yalanaui deceive the Indian, make the Indian a slave. But Lokono have heard your name, paleface. My trust is yours. Come tomorrow after sunset, son of the sea. I will be with Tagofa in that hut. I will ask him whether he will go with you or not.";
			link.l1 = "Tell Tagofa that I will give him my finest pistol. And for you, I have many jewels.";
			link.l1.go = "hayamee_2";
			notification("The Indians respect you "+stf(pchar.questTemp.Indian.relation)+"/40", "None");
			notification("Trustworthy", "Trustworthy");
		break;
		
		case "hayamee_2":
			dialog.text = "Oh-ey!";
			link.l1 = "...";
			link.l1.go = "hayamee_3";
		break;
		
		case "hayamee_3":
			DialogExit();
			AddQuestRecord("Roger_5", "9");
			DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Women");
			LAi_CharacterDisableDialog(npchar);
			pchar.quest.mtraxx_merida_wait1.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.hour  = 22.0;
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtraxx_merida_wait1.function = "Mtraxx_MeridaHayameeTimer";
		break;
		
		case "hayamee_4":
			pchar.quest.Mtraxx_MeridaPotionLate.over = "yes";
			dialog.text = ""+npchar.name+" is glad to see a son of the sea. Tagofa has come back. But he has drunk too much kasheeri and is sleeping. Do not wake him, Tagofa is resting. I will talk.";
			link.l1 = "Very well, "+npchar.name+". Will your husband guide us to Merida?";
			link.l1.go = "hayamee_5";
		break;
		
		case "hayamee_5":
			dialog.text = "Tagofa agreed to guide your warriors through the selva to the Spanish village. But there are terms...";
			link.l1 = "Which ones?";
			link.l1.go = "hayamee_6";
		break;
		
		case "hayamee_6":
			dialog.text = "You protect Tagofa from Capong warriors. Tagofa does not fight Spaniards or Capong. If he faces danger, he will run away and no one will find him, he is the best Locono hunter.";
			link.l1 = "I see. You worry about your man, that is understandable. I promise you we will deal with all those Capongs ourselves.";
			link.l1.go = "hayamee_7";
		break;
		
		case "hayamee_7":
			dialog.text = "Oh-ey! Tagofa wants gifts from the son of the sea: one small to shoot many stones and one big to shoot one stone, the pretty ones. Also, he wants bullets for each gun: as many as fingers on both hands, three times.";
			link.l1 = "Whoa! Your man knows a thing or two about guns, huh? Very well. What else?";
			link.l1.go = "hayamee_8";
		break;
		
		case "hayamee_8":
			dialog.text = "And Tagofa wants a beautiful magic eye from the pale-faces.";
			link.l1 = "A spyglass? Fine. Anything else?";
			link.l1.go = "hayamee_9";
		break;
		
		case "hayamee_9":
			dialog.text = "No more for Tagofa. "+npchar.name+" wants pretty things. A gold ring with a big red stone, and beads made of many, many green stones. "+npchar.name+"I saw it on White Mary in Maracaibo.";
			link.l1 = "A golden ring with ruby and jade beads?";
			link.l1.go = "hayamee_10";
		break;
		
		case "hayamee_10":
			dialog.text = "Not jade. It's shiny and white men value it.";
			link.l1 = "Emerald? Emerald beads?";
			link.l1.go = "hayamee_11";
		break;
		
		case "hayamee_11":
			dialog.text = "Oh-ey!";
			link.l1 = "Heh, "+npchar.name+" knows something about jewels! Very well, you'll get it.";
			link.l1.go = "hayamee_12";
		break;
		
		case "hayamee_12":
			dialog.text = "Bring everything to "+npchar.name+" together, son of the sea. Then Tagofa will guide you and your warriors. Do not waste time, in half a moon Tagofa and I will go to the neighbouring village. For a great day. Now go, "+npchar.name+" wants to sleep.";
			link.l1 = "I won't keep you waiting too long. See you.";
			link.l1.go = "hayamee_13";
		break;
		
		case "hayamee_13":
			DialogExit();
			AddQuestRecord("Roger_5", "10");
			LAi_CharacterDisableDialog(npchar);
			SetFunctionTimerCondition("Mtraxx_MeridaHayameeLate", 0, 0, 15, false); // таймер
			// Тагофу в сидячее положение
			pchar.quest.mtraxx_merida_wait2.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.hour  = 9.0;
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtraxx_merida_wait2.function = "Mtraxx_MeridaTagofaHide";
		break;
		
		case "hayamee_14":
			bOk = GetCharacterFreeItem(pchar, "spyglass1") > 0 || GetCharacterFreeItem(pchar, "spyglass2") > 0 || GetCharacterFreeItem(pchar, "spyglass3") > 0;
			dialog.text = "You brought what "+npchar.name+" and Tagofa asked?";
			if (bOk && GetCharacterFreeItem(pchar, "pistol3") > 0 && GetCharacterFreeItem(pchar, "pistol5") > 0 && GetCharacterItem(pchar, "bullet") >= 30 && GetCharacterItem(pchar, "grapeshot") >= 30 && GetCharacterItem(pchar, "gunpowder") >= 60 && CheckCharacterItem(pchar, "jewelry41") && CheckCharacterItem(pchar, "jewelry42"))
			{
				link.l1 = "Yes. Everything is as per your list.";
				link.l1.go = "hayamee_15";
			}
			else
			{
				link.l1 = "No, I am still working on it.";
				link.l1.go = "hayamee_14x";
			}
		break;
		
		case "hayamee_14x":
			DialogExit();
			npchar.dialog.currentnode = "hayamee_14";
		break;
		
		case "hayamee_15":
			pchar.quest.Mtraxx_MeridaHayameeLate.over = "yes";
			Mtraxx_MeridaRemoveGifts();
			dialog.text = ""+npchar.name+" is happy, son of the sea. I now call you husband. He goes with you. But remember what you promised to "+npchar.name+"!";
			link.l1 = "Yes, yes, I remember everything. I will keep him safe, don't worry.";
			link.l1.go = "hayamee_16";
		break;
		
		case "hayamee_16":
			DialogExit();
			pchar.questTemp.Mtraxx = "merida_hayamee_peace";
			chrDisableReloadToLocation = true;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 7.0);
			DoQuestFunctionDelay("Mtraxx_MeridaTagofaEnter", 20.0);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
			
		case "CitizenNotBlade":
			dialog.text = "Put away your weapon, paleface, or we'll make you do it!";
			link.l1 = LinkRandPhrase("Fine.","Fine.","Don't worry, I'm putting it away...");
			link.l1.go = "exit";
		break;  

	}
}

void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "What do you want?";
			link.l1 = "Nothing at this time.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		//Найти помощника в магазин
		case "Storehelper":
			DelLandQuestMark(npchar);
			dialog.text = "Is there anything you need, monsieur?";
			link.l1 = "You are Gralam Lavoie, correct?";
			link.l1.go = "Storehelper_1";
		break;
		
		case "Storehelper_1":
			dialog.text = "Who is asking? Don't bother me while I'm drinking rum, sir. I'm not in the mood for conversation.";
			link.l1 = "I won't take much of your time. I've been sent here by a merchant from Saint-Pierre. You were his former employee. He's searching for you and...";
			link.l1.go = "Storehelper_2";
		break;
		
		case "Storehelper_2":
			dialog.text = "Ha, he's searching for me!? That's rich of that fucking skinflint! Did he really think that I would spend my whole life working for such paltry wages? He is the greediest pennypincher in the Caribbean! I slaved for him for five years and he never paid me a penny more than he could get away with! Bah, not even enough to buy a drink!\nHe can count his own wares  now, I quit. No one in Saint-Pierre will work for that cheapskate, that's for sure. He has only one concern - earn more for himself and pay his people less.";
			link.l1 = "I take it you're not going back to work for him?";
			link.l1.go = "Storehelper_3";
		break;
		
		case "Storehelper_3":
			dialog.text = "No, God strike me dead if I did! I'll just wait here in Le Francois for some ship to arrive and I'll sign on as purser if they'll take me. And if that doesn't work out then I'll slum it as a common sailor. I can't even stand to set my eyes on that money grubber. If I'm going to be poor I may as well be a free man...";
			link.l1 = "I understand, that's all I needed to know. Good luck, Gralam!";
			link.l1.go = "Storehelper_12";
		break;
		
		case "Storehelper_4":
			DelLandQuestMark(npchar);
			dialog.text = "Sir, step aside. You're in my way!";
			link.l1 = "Just one question, monsieur. Are you Gralam Lavoie?";
			link.l1.go = "Storehelper_5";
		break;
		
		case "Storehelper_5":
			dialog.text = "Ha! Yeah, that's me. What do you want?";
			link.l1 = "You're being searched by a merchant from St. Pierre. You used to work for him, didn't you?";
			link.l1.go = "Storehelper_6";
		break;
		
		case "Storehelper_6":
			dialog.text = "Ha-ha! What a joke! And what does his royal majesty need from me? Has he decided to pay me my missing salary for my last two weeks of work? Or is he having troubles counting his barrels and fooling his customers at the same time, eh? Ha-ha-ha!";
			link.l1 = "He asked me to look for you and to clarify why you aren't coming to his store to work any more.";
			link.l1.go = "Storehelper_7";
		break;
		
		case "Storehelper_7":
			dialog.text = "Why? Because he is a fucking miser and a terrible employer! I am a part of the Brethren of the Coast now, a free man and a slave no longer! Look around you, I am really enjoying myself!\nSoon I will set sail and count pesos and doubloons taken from the Spanish instead of crates of bananas! And about that skinflint - I doubt that he will find anyone to replace me. No one in Saint-Pierre is stupid enough to work for him, we've spread news of his reputation to all the apprentices on the island, ha-ha!";
			link.l1 = "I understand. That's all I needed to know. Good luck, Gralam!";
			link.l1.go = "Storehelper_12";
		break;
		
		case "Storehelper_8":
			DelLandQuestMark(npchar);
			dialog.text = "How can I help you?";
			link.l1 = "Good afternoon. Gralam Lavoie, I presume?";
			link.l1.go = "Storehelper_9";
		break;
		
		case "Storehelper_9":
			dialog.text = "Yes. What do you want, monsieur?";
			link.l1 = "You're being searched for by a merchant from Saint-Pierre. You used to work for him, didn't you?";
			link.l1.go = "Storehelper_10";
		break;
		
		case "Storehelper_10":
			dialog.text = "Well, let him keep on searching. I don't owe him anything. He still owes me two weeks wage, but I'm not even going to bother getting my money from him. I hope he chokes on his own coppers.";
			link.l1 = "Hm. So you've left him for good, I take it?";
			link.l1.go = "Storehelper_11";
		break;
		
		case "Storehelper_11":
			dialog.text = "You got everything right, sirrah. My ex-employer is a rare specimen of miser, truly Biblical in scale. I'm a Brother of the Coast now and my talents are well esteemed by my new mates. I get twice as much, plus bonuses\nI doubt that our dear friend will find anyone to replace me. His greed is well-known to the people of Saint-Pierre, no one there is stupid enough to work for him.";
			link.l1 = "I got it. That's all I needed to know. Good luck, Gralam!";
			link.l1.go = "Storehelper_12";
		break;
		
		case "Storehelper_12":
			DialogExit();
			npchar.lifeday = 0;
			AddQuestRecord("SharlieA", "2");
			pchar.questTemp.Sharlie.Storehelper = "return";
			LAi_CharacterDisableDialog(npchar);
			pchar.quest.StorehelperOver.over = "yes"; //снять таймер
			// Rebbebion, новые марки до места назначения
			QuestPointerToLoc("lefransua_town", "reload", "gate_back");
			QuestPointerToLoc("lefransua_exittown", "reload", "reload2_back");
			QuestPointerToLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerToLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerToLoc("fortfrance_town", "reload", "reload6_back");
			AddLandQuestMark(characterFromId("FortFrance_trader"), "questmarkmain");
			QuestPointerDelLoc("fortfrance_town", "reload", "gate_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload3_back");
			QuestPointerDelLoc("lefransua_exittown", "reload", "reload1_back");
		break;
		
		case "Newstorehelper_1":
			dialog.text = "Hello, monsieur. I don't mean to be too forward, but I believe that my candidacy will be quite a fit for the position you are offering.";
			link.l1 = "Good afternoon. And why do you suppose that?";
			link.l1.go = "Newstorehelper_1_1";
		break;
		
		case "Newstorehelper_2":
			dialog.text = "Greetings, sir! Allow me to tell you a little bit about myself.";
			link.l1 = "I'm all ears.";
			link.l1.go = "Newstorehelper_2_1";
		break;
		
		case "Newstorehelper_3":
			dialog.text = "Good health to you, dear sir. Are you offering a merchant vacancy?";
			link.l1 = "Yes, I am. What can you tell me about yourself?";
			link.l1.go = "Newstorehelper_3_1";
		break;
		
		case "Newstorehelper_1_1":
			dialog.text = "I served as a quartermaster under the command of Captain Francis Dubois himself. He was quite pleased with my skills, but I was injured in battle and had to take leave to be treated. I am fine now, completely sound of body, but the thought of the rolling waves makes me sick. No, my only desire now is to stay on solid earth\n(whispering) And if you choose me, I will pay five hundred pesos and twenty five golden doubloons extra.";
			link.l1 = "I see. I'll think about it.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Newstorehelper_1_2";
		break;
		
		case "Newstorehelper_2_1":
			dialog.text = "I used to be a peddler, but had to flee some debtors and took to the sea as a purser on a trade ship. Fate has brought me to this village. I didn't like the sailor's life much anyway, and I'd be glad to accept your offer\n(whispering) And if you choose me, I will give you not only five hundred pesos, but also this heavy packet of amber.";
			link.l1 = "I see. I'll think about it.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Newstorehelper_2_2";
		break;
		
		case "Newstorehelper_3_1":
			dialog.text = "I was a clerk in one of the port warehouses of Glasgow. I came to the Caribbean in search of wealth and managed to earn enough money to live through my old age with dignity. But I got tired of sea voyages and I'd like to live a calm life on the shore\n(whispering) And if you choose me, I will give you five hundred pesos plus an additional twenty-five hundred pesos as extra.";
			link.l1 = "I see. I'll think about it.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Newstorehelper_3_2";
		break;
		
		case "Newstorehelper_1_2":
			dialog.text = "Monsieur, make the right choice. And don't forget about the doubloons...";
			link.l1 = "I have decided in your favor. Get yourself together. We're going to Saint-Pierre.";
			link.l1.go = "Newstorehelper_1_3";
			link.l2 = "I still haven't decided yet...";
			link.l2.go = "exit";
			NextDiag.TempNode = "Newstorehelper_1_2";
		break;
		
		case "Newstorehelper_2_2":
			dialog.text = "I hope you pick me, monsieur. And amber is also quite a valuable, useful thing...";
			link.l1 = "I have decided in your favor. Get yourself together. We're going to Saint-Pierre.";
			link.l1.go = "Newstorehelper_2_3";
			link.l2 = "I still haven't decided yet...";
			link.l2.go = "exit";
			NextDiag.TempNode = "Newstorehelper_2_2";
		break;
		
		case "Newstorehelper_3_2":
			dialog.text = "The merchant will not be disappointed by my work. And don't forget about your bonus.";
			link.l1 = "I have decided in your favor. Get yourself together. We're going to Saint-Pierre.";
			link.l1.go = "Newstorehelper_3_3";
			link.l2 = "I still haven't decided yet...";
			link.l2.go = "exit";
			NextDiag.TempNode = "Newstorehelper_3_2";
		break;
		
		case "Newstorehelper_1_3":
			dialog.text = "Just let me get my things together! I'll be waiting for you at the entrance of the tavern.";
			link.l1 = "...";
			link.l1.go = "Newstorehelper_exit";
			pchar.questTemp.Sharlie.Storehelper.Quality = 0;
		break;
		
		case "Newstorehelper_2_3":
			dialog.text = "I'll be right there in a moment, monsieur! I'll be waiting for you at the entrance of the tavern.";
			link.l1 = "...";
			link.l1.go = "Newstorehelper_exit";
			pchar.questTemp.Sharlie.Storehelper.Quality = 1;
		break;
		
		case "Newstorehelper_3_3":
			dialog.text = "I'll get my old valise and I'll be waiting for you at the entrance to the tavern, sir!";
			link.l1 = "...";
			link.l1.go = "Newstorehelper_exit";
			pchar.questTemp.Sharlie.Storehelper.Quality = 2;
		break;
		
		case "Newstorehelper_exit":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			pchar.questTemp.Sharlie.Storehelper.id = npchar.id;
			DeleteAttribute(npchar, "LifeDay")
			chrDisableReloadToLocation = true;
			for (i=1; i<=3; i++)
			{
				sld = characterFromId("Newstorehelper_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 10.0);
			}
			pchar.quest.storehelper2.win_condition.l1 = "location";
			pchar.quest.storehelper2.win_condition.l1.location = "LeFransua_town";
			pchar.quest.storehelper2.function = "NewstorehelperAdd";
			AddQuestRecord("SharlieA", "4");
			pchar.questTemp.Sharlie.Storehelper = "choise";
			pchar.quest.storehelper.over = "yes"; //снять прерывание
			pchar.quest.Sharlie_JungleBandos.win_condition.l1 = "location";
			pchar.quest.Sharlie_JungleBandos.win_condition.l1.location = "Martinique_Jungle_01";
			pchar.quest.Sharlie_JungleBandos.function = "SharlieJungleBandos";
			
			QuestPointerToLoc("lefransua_town", "reload", "gate_back");
			QuestPointerToLoc("lefransua_exittown", "reload", "reload2_back");
			QuestPointerToLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerToLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerToLoc("fortfrance_town", "reload", "reload6_back");
			AddLandQuestMark(characterFromId("FortFrance_trader"), "questmarkmain");
		break;
		
		case "Newstorehelper_regard":
			dialog.text = "Well, I take it this is where I work since now? Thank you, monsieur, for choosing me. Here are your five hundred pesos and the bonus on top as promised.";
			link.l1 = "My gratitude... Let me introduce you to your employer.";
			link.l1.go = "Newstorehelper_regard_1";
		break;
		
		case "Newstorehelper_regard_1":
			DialogExit();
			npchar.lifeday = 0;
			switch (sti(pchar.questTemp.Sharlie.Storehelper.Quality))
			{
				case 0:
					AddMoneyToCharacter(pchar, 500);
					TakeNItems(pchar, "gold_dublon", 25);
				break;
				
				case 1:
					AddMoneyToCharacter(pchar, 500);
					TakeNItems(pchar, "jewelry8", 10);
					TakeNItems(pchar, "jewelry7", 1);
				break;
				
				case 2:
					AddMoneyToCharacter(pchar, 3000);
				break;
			}
		break;
		
		//контрабанда рома
		case "Rum_Cap_Over":
			dialog.text = "Monsieur, I must ask you to leave my ship immediately. We are raising anchor and casting off!";
			link.l1 = "Alright...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rum_Cap_Over";
			chrDisableReloadToLocation = false;
			npchar.DontDeskTalk = true;
			LAi_LocationFightDisable(&Locations[FindLocation("Deck_Near_Ship")], false);
		break;
		
		case "Rum_Cap":
			pchar.quest.Sharlie_rum2.over = "yes"; //снять таймер
			chrDisableReloadToLocation = false; // patch-4
			dialog.text = "Well? Who are you, mate?";
			//link.l1.edit = 1;			
			link.l1 = ""+pchar.questTemp.Sharlie.Rum.Pass+"!";
			link.l1.go = "Rum_Cap_1";
		break;
		
		case "Rum_Cap_1":
			dialog.text = "Have a shot of rum, sailor! Ha-ha! Welcome on board my lugger. You've come for the product?";
			link.l1 = "Yes. What else would I be here for?";
			link.l1.go = "Rum_Cap_2";
			/* if(GetStrSmallRegister(pchar.questTemp.Sharlie.Rum.Pass) == GetStrSmallRegister(dialogEditStrings[1]))
			{
				dialog.text = "Have a shot of rum, sailor! Ha-ha! Welcome on board my lugger. You've come for the product?";
				link.l1 = "Yes. What else would I be here for?";
				link.l1.go = "Rum_Cap_2";
			}
			else
			{
				dialog.text = "My, my, what a green son of a whore! Boys, this one looks like a raw recruit! Let's pitch him overboard!";
				link.l1 = "Hup!";
				link.l1.go = "Rum_Cap_getout";
			} */
		break;
		
		case "Rum_Cap_getout":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("Deck_Near_Ship")], false);
			setCharacterShipLocation(pchar, "Shore38"));
			setWDMPointXZ("Shore38");
			DoQuestReloadToLocation("Shore38", "goto", "goto1", "Rum_RemoveBarkas");
		break;
		
		case "Rum_Cap_2":
			dialog.text = "Lads! Load the boxes onto the launch!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Rum_CarrierEnter");
		break;
		
		case "Rum_Cap_3":
			dialog.text = "All the crates of rum are on your launch. Port Le Francois is located due south from here. Make haste, it's time for me to pull in anchor too!";
			link.l1 = "Let's not waste time, gentlemen! Good luck!";
			link.l1.go = "Rum_Cap_4";
		break;
		
		case "Rum_Cap_4":
			dialog.text = "Same to you, matey...";
			link.l1 = "...";
			link.l1.go = "Rum_Cap_5";
		break;
		
		case "Rum_Cap_5":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation("Deck_Near_Ship")], false);
			npchar.DontDeskTalk = true;
			NextDiag.CurrentNode = "Rum_Cap_Over";
			pchar.quest.Sharlie_rum4.win_condition.l1 = "Ship_location";
			pchar.quest.Sharlie_rum4.win_condition.l1.location = "LeFransua_town";
			pchar.quest.Sharlie_rum4.function = "Rum_RemoveRum";
			AddQuestRecord("SharlieB", "4");
			i = FindIsland("Martinique");
			Islands[i].EffectRadius = 3000;
			
			DoQuestFunctionDelay("MessageRum1", 1.0);
			//NewGameTip("Transport the rum to Le Francois. Keep sailing around the island.");
			pchar.questTemp.Rum.Tip2.Reload = "l4";
			
			Weather.Wind.Speed = 16.0;
			pchar.wind.speed = Weather.Wind.Speed;
			fWeatherSpeed = stf(Weather.Wind.Speed);//халява первого выхода
			
			Weather.Wind.Angle = PId2;
			pchar.wind.angle = Weather.Wind.Angle;
			fWeatherAngle = stf(Weather.Wind.Angle);//халява первого выхода
			
			pchar.quest.MessageRum2.win_condition.l1 = "ExitFromLocation";
			pchar.quest.MessageRum2.win_condition.l1.location = pchar.location;
			pchar.quest.MessageRum2.function = "MessageRum2";
		break;
		
		case "Rum_Carrier":
			dialog.text = "We've been waiting for you, monsieur. How did everything go? Do you have the crates?";
			link.l1 = "Everything went spectacular. The rum boxes are on the launch.";
			link.l1.go = "Rum_Carrier_1";
		break;
		
		case "Rum_Carrier_1":
			dialog.text = "Great. We'll take care of it from here. You take off to St. Pierre to the tavern for the payment. Be attentive and cautious in the night jungles.";
			link.l1 = "All the best, gentlemen.";
			link.l1.go = "Rum_Carrier_2";
		break;
		
		case "Rum_Carrier_2":
			DialogExit();
			for (i=1; i<=3; i++)
			{
				
				sld = characterFromId("Rum_Carrier2_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 10.0);
			}
			pchar.questTemp.Sharlie.Rum = "regard";
			i = FindLocation("Fortfrance_town");
			setCharacterShipLocation(pchar, GetCityFrom_Sea(locations[i].fastreload));
		    setWDMPointXZ(GetCityFrom_Sea(locations[i].fastreload));
			SetCurrentTime(23, 0);
			Sharlie_removeLocks("");
			// Rebbebion, новые марки до места назначения
			QuestPointerToLoc("lefransua_town", "reload", "gate_back");
			QuestPointerToLoc("lefransua_exittown", "reload", "reload2_back");
			QuestPointerToLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerToLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerToLoc("fortfrance_town", "reload", "reload4_back");
			if(CheckAttribute(pchar, "questTemp.Sharlie.Gigolo")) QuestPointerToLocTime("fortfrance_town", "reload", "reload9_back", 23.0, 24.0);
			AddLandQuestMark(characterFromId("FortFrance_tavernkeeper"), "questmarkmain");
		break;
		
		//доставить девочку из борделя
		case "GigoloMan":
			DelLandQuestMark(npchar);
			dialog.text = "Good afternoon, monsieur! I say, you don't look like the raggedy scoundrels usually hanging around our colony. Judging by your clothes, you must've come a long way... Arrived from Europe, have you?";
			link.l1 = "Exactly, monsieur. "+GetFullName(pchar)+", at your service. What do you need?";
			link.l1.go = "GigoloMan_1";
		break;
		
		case "GigoloMan_1":
			dialog.text = "Allow me to introduce myself - "+GetFullName(npchar)+". I have arrived to this dreadful place from France a few years ago. But that is neither here nor there. I have a very delicate matter for you\nPlease understand that if I wasn't sure that you were a gentleman, I would never ask you for such a favour.";
			link.l1 = "Please, state your request, monsieur. If it is within my capabilities, then of course I will try to help.";
			link.l1.go = "GigoloMan_2";
		break;
		
		case "GigoloMan_2":
			dialog.text = "I am glad to hear that, monsieur de Maure. Now, how to put this delicately...There is a brothel in this town. A new girl appeared there recently; young, pale, blonde, stunningly beautiful! Now, I've been watching her for weeks and... got a very strong desire to spend some time with her in private\nBut my estate and status make it...inconvenient to visit such a place. Imagine the gossip!\nThat is why I am appealing to you. Plainly put, you are a newcomer to our island, people don't know you and they don't care about what you do... yet. You could do me a great favour, monsieur.";
			link.l1 = "I think I understand what you're getting at.";
			link.l1.go = "GigoloMan_3";
		break;
		
		case "GigoloMan_3":
			dialog.text = "I appreciate your discretion, monsieur. I can't go to the girl, so the girl must come to me. At my house. I ask you to go to the brothel and arrange a deal with the madame so she would allow you to arrange a 'house call' of the blonde girl for one night\nAurora won't refuse, she is well known to provide such delivery services, although it always costs a bit more. After that you shall bring the girl to my house. For payment, I will give you six thousand pesos. Aurora usually takes three thousand or three and five hundred for one night with the girl in house. You may keep the extra as a compensation for your troubles.";
			link.l1 = "Doesn't sound too complicated. I can do that.";
			link.l1.go = "GigoloMan_4";
			link.l2 = "Monsieur, I take my reputation as a gentleman just as seriously as you do. Please forgive me, but I can't fulfill your request. I must refuse. I'd should probably go to the tavern and check if the innkeeper has any job for me.";
			link.l2.go = "GigoloMan_exit";
		break;
		
		case "GigoloMan_exit":
			DialogExit();
			LocatorReloadEnterDisable("Fortfrance_town", "reload9_back", false);// бордель open
			LocatorReloadEnterDisable("Fortfrance_town", "reload9", false);// бордель
			LocatorReloadEnterDisable("Fortfrance_town", "reload4_back", false);// таверна
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			chrDisableReloadToLocation = false;
			QuestPointerToLoc("fortfrance_town", "reload", "reload4_back");
			SetCurrentTime(17, 30);
		break;
		
		case "GigoloMan_4":
			dialog.text = "I am damn glad to hear it. Now listen, the girl's name is Lucille. I ask you to deliver her to my place when it's dark, no earlier than eleven p.m., in order to avoid unwanted attention from any gawkers. Knock on the door, and I will open.\nMy house is located to the left of the governor's residence, facing away from it - a two-story mansion with a red roof. You can easily find it, and there's a shop nearby, too. Actually, I am heading to my house now; feel free to follow me to see what it looks like and where it is exactly, so you won't get lost at night.\n Regarding the matter at hand - here, take six thousand pesos. I expect you by the agreed-upon time!";
			link.l1 = "We've got a deal. Your blonde Lucille will be at your doorstep tonight.";
			link.l1.go = "GigoloMan_5";
		break;
		
		case "GigoloMan_5":
			DialogExit();
			AddMoneyToCharacter(pchar, 6000);
			AddQuestRecord("SharlieC", "1");
			AddQuestUserData("SharlieC", "sName", GetFullName(npchar));
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "houseSp1", "none", "", "", "", -1);
			LocatorReloadEnterDisable("Fortfrance_town", "houseSp1", true);
			npchar.lifeday = 0;
			pchar.questTemp.Sharlie.Gigolo = "start";
			pchar.questTemp.Sharlie.Gigolo.Rand1 = rand(1);
			pchar.questTemp.Sharlie.Gigolo.Rand2 = rand(1);
			LocatorReloadEnterDisable("Fortfrance_town", "reload9_back", false);// бордель open
			LocatorReloadEnterDisable("Fortfrance_town", "reload91", false);// бордель
			AddLandQuestMark(characterFromId("Fortfrance_hostess"), "questmarkmain");
			QuestPointerToLoc("fortfrance_town", "reload", "reload9_back");
			QuestPointerToLoc("fortfrance_brothel", "reload", "reload3");
			chrDisableReloadToLocation = false;
		break;
		
		case "GigoloGirl":
			if (npchar.quest.meeting == "0")
			{
				DelLandQuestMark(npchar);
				QuestPointerDelLoc("fortfrance_town", "reload", "reload9_back");
				dialog.text = "Good day, monsieur. Why, are you the man that hired me tonight? My my, I must say, I'm one lucky girl to score such a handsome and well-groomed gentleman, nothing like the brutes that come off the docks stinking of tar and sweat...";
				link.l1 = "My apologies but not tonight, Lucille. I am here on behalf of my good friend, who for a multitude of very complicated reasons is not able to leave his house, so I will be bringing you to him. Now, don't be upset, he's a gentle man and is quite fond of you. I think you will be happy at the end of it.";
				link.l1.go = "GigoloGirl_1";
				// belamour legendary edition -->
				link.l2 = "Uhm... You are quite right, dear. Shall we?";
				link.l2.go = "GigoloGirl_1a";
				// <-- legendary edition
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Monsieur, I hope you understand that I can't just promanade around with you at night. You need to take me to your friend's house quickly or I will go straight back to Madame and you're going to waste your money.";
				link.l1 = "Alright, I understand. Follow me!";
				link.l1.go = "GigoloGirl_2";
			}
		break;
		// belamour legendary edition -->
		case "GigoloGirl_1a":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			chrDisableReloadToLocation = true; //закрыть локацию
			DoQuestReloadToLocation(pchar.location+"_room", "goto", "goto2", "GigoloGirl_Sex");
			ChangeCharacterAddressGroup(npchar, pchar.location+"_room", "goto", "goto1");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Rum"))
			{
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1 = "Hour";
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.start.hour = 6.00;
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.finish.hour = 22.00;
				pchar.quest.Sharlie_CreatShipyardMarker.function = "Sharlie_CreatShipyardMarker";
			}
		break;
		
		case "GigoloGirl_1":
			AddCharacterExpToSkill(pchar, "Fortune", 40);
		// <-- legendary edition
			dialog.text = "That's too bad... I liked you right away, monsieur. I would've loved to spend the night with you...perhaps next time. Shall we go?";
			link.l1 = "Yes. Follow me!";
			link.l1.go = "GigoloGirl_2";
		break;
		
		case "GigoloGirl_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.Sharlie_Gigolo.win_condition.l1 = "locator";
			pchar.quest.Sharlie_Gigolo.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.Sharlie_Gigolo.win_condition.l1.locator_group = "reload";
			pchar.quest.Sharlie_Gigolo.win_condition.l1.locator = "houseSp1";
			pchar.quest.Sharlie_Gigolo.function = "Sharlie_GiveGigoloGirl";
			pchar.quest.Sharlie_Gigolo1.win_condition.l1 = "Timer";
			pchar.quest.Sharlie_Gigolo1.win_condition.l1.date.hour  = sti(GetTime() + 2);
			pchar.quest.Sharlie_Gigolo1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.Sharlie_Gigolo1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.Sharlie_Gigolo1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.Sharlie_Gigolo1.function = "Sharlie_GigoloGirlOver";
			QuestPointerToLoc("fortfrance_town", "reload", "houseSp1");
		break;
		
		case "GigoloGirl_3":
			dialog.text = "What a grand house. Is this the place?";
			link.l1 = "Yes. Come in. Don't be afraid, my friend is a good man.";
			link.l1.go = "GigoloGirl_4";
		break;
		
		case "GigoloGirl_4":
			dialog.text = "You underestimate me, I am not afraid, monsieur. I know how to handle myself. Now, maybe some time later you can pay Madame for a night with me? I promise it'll be the best night of your life!";
			link.l1 = "Anything's possible, Lucille. Maybe we'll meet each other again. Farewell!";
			link.l1.go = "GigoloGirl_5";
		break;
		
		case "GigoloGirl_5":
			pchar.quest.Sharlie_Gigolo1.over = "yes";
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "houseSp1", "none", "", "", "GigoloGirl_Remove", 5.0);
			QuestPointerDelLoc("fortfrance_town", "reload", "houseSp1");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Rum"))
			{
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1 = "Hour";
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.start.hour = 6.00;
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.finish.hour = 22.00;
				pchar.quest.Sharlie_CreatShipyardMarker.function = "Sharlie_CreatShipyardMarker";
			}
		break;
		
		//пираты с пленным испанцем
		case "CaptivePirate":
			pchar.quest.Captive_CreatePiratesOver.over = "yes";//снять таймер
			pchar.quest.Captive_CreatePiratesOver2.over = "yes";//снять таймер
			// Rebbebion, новые марки до места назначения
			QuestPointerDelLoc("fortfrance_town", "reload", "gate_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload2_back");
			QuestPointerDelLoc("martinique_jungle_03", "reload", "reload2_back");
			dialog.text = "What is this!? Who are you? What do you want here? Come on, get the hell out of here!";
			link.l1 = "You're not very polite, sirrah.";
			link.l1.go = "CaptivePirate_1";
		break;
		
		case "CaptivePirate_1":
			dialog.text = "Listen up boy, I wasn't raised to be polite, just like I didn't learn to read and write, but spliting your skull with a cutlass is as easy to me as a whore falling backwards. And I swear on my deadlights that if you don't walk out of here this minute, you'll be carried out. You got that?";
			link.l1 = "No, you listen to me you knave. Your scheme is out in the open. I need that man alive, so throw down your arms and run. There's a squad of French soldiers in the jungle right behind me. If you run fast enough, then maybe you'll manage to save your pathetic lives.";
			link.l1.go = "CaptivePirate_3";
			link.l2 = "All right, all right, calm down. I'm leaving.";
			link.l2.go = "CaptivePirate_2";
		break;
		
		case "CaptivePirate_2":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			DialogExit();
			n = makeint(MOD_SKILL_ENEMY_RATE/2);
			if (n <= 1) n = 2;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("CaptivePirate_"+i);
				LAi_CharacterDisableDialog(sld);
				LAi_SetImmortal(sld, true);
				sld.lifeday = 0;
			}
			sld = characterFromId("CaptiveSpain");
			LAi_SetImmortal(sld, true);
			sld.lifeday = 0;
			pchar.quest.Sharlie_captive1.over = "yes";
			pchar.quest.Sharlie_captive2.over = "yes";//снять прерывание
			AddQuestRecord("SharlieD", "5");
			CloseQuestHeader("SharlieD");
			DeleteAttribute(pchar, "questTemp.Sharlie.Captive");
			pchar.questTemp.Sharlie = "bankskipermoney";
		break;
		
		case "CaptivePirate_3":
			dialog.text = "Whaa-at? You're bluffing, mate! Take him down boys, to arms!";
			link.l1 = "On your own head be it then, en garde!";
			link.l1.go = "CaptivePirate_4";
		break;
		
		case "CaptivePirate_4":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			int n = makeint(MOD_SKILL_ENEMY_RATE/2);
			if (n <= 1) n = 2;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("CaptivePirate_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Captive_PiratesDead");
			AddDialogExitQuest("MainHeroFightModeOn");	
			sld = characterFromId("CaptiveSpain");
			LAi_SetCitizenType(sld);
			DoQuestFunctionDelay("Ngt_CaptiveEng", 0.5);
		break;
		
		//пленный испанец
		case "CaptiveSpain":
			dialog.text = "Gracias a Dios! Ah, you are Francés? Mierda, you fended off those brigands in style. But don't think that I'll just roll over and surrender, I'll show you how a Spainard fights! Santiago!";
			link.l1 = "No wait, please!";
			link.l1.go = "CaptiveSpain_1";
		break;
		
		case "CaptiveSpain_1":
			dialog.text = "I would sooner die than be taken by the French. I took a cutlass from one of the dead bodies while you were fighting...now I'll make you dance to a Spanish quadrille!";
			link.l1 = "You Spaniards are as stubborn as mules!";
			link.l1.go = "CaptiveSpain_2";
		break;
		
		case "CaptiveSpain_2":
			DialogExit();
			LAi_SetPlayerType(pchar);
			NextDiag.currentnode = "CaptiveSpain_3";
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_SetCheckMinHP(npchar, 10.0, true, "CaptiveSpain_capture");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "CaptiveSpain_3":
			dialog.text = "Maldito... You won. I give up, damn Frenchman. I'm at your mercy.";
			link.l1 = "Put up your blade and let me speak, you obstinate Castilian! I don't want you to die, and I'm not sending you to jail either!";
			link.l1.go = "CaptiveSpain_4";
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
		break;
		
		case "CaptiveSpain_4":
			dialog.text = "Then what are you doing? Why did you kill the pirates? And where are your soldiers?";
			link.l1 = "There are no soldiers. I tried to trick the scoundrels, but as you can see around us, it didn't work. I am here by myself, according to your old friend's request. His name is "+pchar.questTemp.Sharlie.Captive.Name+", he's a banker in St. Pierre.";
			link.l1.go = "CaptiveSpain_5";
		break;
		
		case "CaptiveSpain_5":
			dialog.text = ""+pchar.questTemp.Sharlie.Captive.Name+"? I don't know anyone by that name...";
			link.l1 = "Nor did I know a thing about you or your captivity. I became aware of your transfer to an English ship from him. My task is to deliver you to him and I swore I would fulfill that! Now then, come with me if you want to live.";
			link.l1.go = "CaptiveSpain_6";
		break;
		
		case "CaptiveSpain_6":
			dialog.text = "I don't have a choice anyway... This banker of yours can't be any worse than the English and their atrocious cooking...";
			link.l1 = "You're finally making a wise decision. That's enough talking for now, we're heading for St. Pierre. Keep close to me and don't stray. If you run, I'll catch you and beat you to within an inch of your life again.";
			link.l1.go = "CaptiveSpain_7";
		break;
		
		case "CaptiveSpain_7":
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "GenQuest.Notsearchbody"); // 170712
			DialogExit();
			AddQuestRecord("SharlieD", "6");
			LAi_group_Register("TempFriends");
			LAi_group_SetRelation("TempFriends", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "TempFriends");
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			SetNationRelation2MainCharacter(FRANCE, RELATION_ENEMY);
			pchar.quest.Sharlie_captive3.win_condition.l1 = "locator";
			pchar.quest.Sharlie_captive3.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.Sharlie_captive3.win_condition.l1.locator_group = "reload";
			pchar.quest.Sharlie_captive3.win_condition.l1.locator = "reload8_back";
			pchar.quest.Sharlie_captive3.win_condition.l2 = "Night";
			pchar.quest.Sharlie_captive3.win_condition.l3 = "Alarm";
			pchar.quest.Sharlie_captive3.win_condition.l3.value = 0;
			pchar.quest.Sharlie_captive3.win_condition.l3.operation = "=";
			pchar.quest.Sharlie_captive3.function = "CaptiveSpain_reload";//вход ночью
			pchar.questTemp.Sharlie = "bankskipercaptive";
			SetFunctionLocationCondition("CaptiveSpain_removeGuard", "fortfrance_town", 0);
			SetFunctionLocationCondition("CaptiveSpain_saveTip", "fortfrance_exittown", 0);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_town")], false);
			// Rebbebion, новые марки до места назначения. belamour поправил - были не в ту сторону
			QuestPointerToLoc("shore39", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_03", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerToLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerToLoc("fortfrance_town", "reload", "reload8_back");
			AddLandQuestMark(characterFromId("FortFrance_Usurer"), "questmarkmain");
		break;
		
		//горожанин с пропавшей дочерью
		case "Prosper":
			DelLandQuestMark(npchar);
			pchar.quest.Sharlie_RescueDaughter.over = "yes"; //снять прерывание
			dialog.text = "What do you need, monsieur? I've no time for conversation, so be brief.";
			link.l1 = "You are Prosper Trubal, aren't you?";
			link.l1.go = "Prosper_1";
		break;
		
		case "Prosper_1":
			dialog.text = "Yes, that's me. But you have the advantage of me. Please inform me of who you are and what the hell you want.";
			link.l1 = "My name is "+GetFullName(pchar)+". I've been sent to you by "+GetFullName(characterFromId("Fortfrance_portman"))+", the harbor master. He said that you needed urgent help...";
			link.l1.go = "Prosper_2";
		break;
		
		case "Prosper_2":
			dialog.text = "My God yes! That rascal of a commandant didn't even hear my complaint! He's either too lazy or cowardly to help. Have you really come here to help me? If it is so, I won't leave you unrewarded!";
			link.l1 = "Yes Prosper. Tell me what happened and what I have to do to help. I've heard that your daughter disappeared...";
			link.l1.go = "Prosper_3";
		break;
		
		case "Prosper_3":
			dialog.text = "Yes, my dear daughter Celene has been missing for two days. She went on a walk to the fort not far from here. But she did not return, so I went to the fort myself and soldiers told me that she had never been there!\nBut then on my return I was attacked by two savage Indians! They leapt upon me with clubs and tried to beat me\nBut I am no kitten, so I  punched one in the face, bought me enough time to draw my pistol and shoot. I missed but scared them away. I managed to reach the city gates and told the guards about the attack. They ran to the jungle, but the savages were already long gone\nI am sure that they are responsible for Celene's disappearance. Besides, on top of that, two more people have disappeared for the last week - Cesar Blanchet and Gilbert Courcy! One was heading to the bay and another to Le Francois. They've never returned.";
			link.l1 = "So the Indians have been attacking townsfolk right at the city gates? That's unbelievably bold...";
			link.l1.go = "Prosper_4";
		break;
		
		case "Prosper_4":
			dialog.text = "In the meantime I went out to the jungle myself to look for her and found a cave north of the city. I found the bastards are squatting in there. I saw several Indians at the entrance, but some of them must be inside too\nI heard a girl screaming... It was my Celene, I am sure of that, it was her voice! It took all of my restraint not to run in  right then and there - the odds were not in my favor and they would have butchered me. I am no use to her dead.";
			link.l1 = "But why on Earth are they attacking and taking townspeople as prisoners?";
			link.l1.go = "Prosper_5";
		break;
		
		case "Prosper_5":
			dialog.text = "I don't know... Maybe to sell them to pirates or slavers? Maybe they'll just eat them alive, they are savages after all.";
			link.l1 = "Dear God in Heaven, are they cannibals? I thought those were just stories to scare children in Europe...";
			link.l1.go = "Prosper_6";
		break;
		
		case "Prosper_6":
			dialog.text = "Stories? Well, some men like you thought the same until the Caribs had them cooked on a fire and eaten... So, I immediately addressed the commandant and requested a punitive raid to save my Celene. He refused! He said that when girls are missing, they probably ran off with a boy, not Indians. He suggested I search for her in the local haylofts\nAnd as for the two others missing... he said that one of them was under suspicion of smuggling, and the other is probably drinking to death in Le Francois' tavern. To sum up, I have achieved nothing and decided to act on my own.";
			link.l1 = "What are you intending on doing?";
			link.l1.go = "Prosper_7";
		break;
		
		case "Prosper_7":
			dialog.text = "I will go there and kill every last one of those red bastards. I only hope that Celene still lives. As you can see, I bought a musket - and I know how to shoot it. Paid a lot of coin for it but I don't give a damn\nMy mission will be much easier if you will accompany me. Together we can finish the savages without much trouble if you can watch my back while I reload. Will you go with me to save my daughter?";
			link.l1 = "Of course! It's a matter of honour! I can't just allow a girl to die by the knife of some savage.";
			link.l1.go = "Prosper_8";
			if (FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE) == "") {
				link.l1.go = "Prosper_noweapon";
			}
			link.l2 = "Hm. You know, I think commandant's words make sense. Maybe we should still follow his advice first?";
			link.l2.go = "Prosper_exit";
		break;
		
		case "Prosper_noweapon":
			dialog.text = "Monsieur, where is your blade?";
			link.l1 = "I seem to have misplaced it.";
			link.l1.go = "Prosper_noweapon_1";
		break;
		
		case "Prosper_noweapon_1":
			dialog.text = "That will simply not do. I will wait for you until evening, I advise you to grovel at the feet of our governor and beg for his assistance.";
			link.l1 = "Grovel at his feet, eh? Well, as you wish...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Prosper_getweapon";
			SetFunctionTimerConditionParam("RescueDaughter_Over", 0, 0, 0, 22, false);
		break;
		
		case "Prosper_getweapon":
			dialog.text = "Well, monsieur? Did you get yourself a weapon?";
			if (FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE) == "") {
				link.l1 = "Not yet, please wait a bit longer...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Prosper_getweapon";
			} else {
				link.l1 = "Got it. I'm ready to help you!";
				link.l1.go = "Prosper_8";
				DeleteQuestCondition("RescueDaughter_Over");
			}
		break;

		case "Prosper_exit":
			dialog.text = "My God, are you fleeing? No! Get the hell out of here! Coward!";
			link.l1 = "Hey-hey, easy there, you simpleton! I better go out and see any nobles on the streets of Saint-Pierre need help.";
			link.l1.go = "Prosper_exit_1";
			pchar.questTemp.Sharlie.GigoloMan.SamPodbezhit = true;
		break;
		
		case "Prosper_exit_1":
			DialogExit();
			npchar.lifeday = 0;
			//AddTimeToCurrent(2,0);
			SetCurrentTime(17,30);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "gate_back", "none", "", "", "", 10.0);
			CloseQuestHeader("SharlieF");
			chrDisableReloadToLocation = true;
			
			//Подбегает дворянин с квестом "девочка по вызову"
			sld = GetCharacter(NPC_GenerateCharacter("GigoloMan", "Guide_2", "man", "man", 25, FRANCE, 5, true, "soldier"));
			SetFantomParamFromRank(sld, 25, true);
			sld.Dialog.Filename = "Quest\Sharlie\StartMiniQuests.c";
			sld.dialog.currentnode = "GigoloMan";
			sld.greeting = "noble_male";
			AddLandQuestMark(sld, "questmarkmain");
			LAi_SetLoginTime(sld, 6.0, 21.0);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			ChangeCharacterAddressGroup(sld, "Fortfrance_town", "goto", "goto1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Prosper_8":
			dialog.text = "I'm glad there at least one courageous man in this town. Here, take these three vials. These are health-giving herbs, I bought them from our herbalist. It can be a substantial help to you in battle.";
			link.l1 = "What about you?";
			link.l1.go = "Prosper_9";
		break;
		
		case "Prosper_9":
			TakeNItems(pchar, "potion1", 3);
			PlaySound("interface\important_item.wav");
			dialog.text = "Don't worry, I've got more. Are you ready?";
			link.l1 = "Yes, let's not waste any time. Onward!";
			link.l1.go = "Prosper_10";
		break;
		
		case "Prosper_10":
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_SetImmortal(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "fortfrance_exittown", "reload", "reload3", "OpenTheDoors", 10.0);
			PChar.quest.RescueDaughter_ProsperGateOutReload.win_condition.l1 = "location";
			PChar.quest.RescueDaughter_ProsperGateOutReload.win_condition.l1.location = "FortFrance_ExitTown";
			PChar.quest.RescueDaughter_ProsperGateOutReload.win_condition = "RescueDaughter_ProsperGateOutReload";
			AddQuestRecord("SharlieF", "3");
			pchar.quest.Sharlie_RescueDaughter1.win_condition.l1 = "location";
			pchar.quest.Sharlie_RescueDaughter1.win_condition.l1.location = "Martinique_jungle_04";
			pchar.quest.Sharlie_RescueDaughter1.function = "RescueDaughter_NearCave";
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1 = "Timer";
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.date.hour  = sti(GetTime()+2);
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.Sharlie_RescueDaughter2.function = "RescueDaughter_CaveOver";
			NextDiag.CurrentNode = "Prosper_11";
			pchar.questTemp.Sharlie.RescueDaughter = "true";
			LocatorReloadEnterDisable("Fortfrance_exittown", "reload2_back", true);//форт
			LocatorReloadEnterDisable("Martinique_Jungle_01", "reload1_back", true);//джунгли
			LocatorReloadEnterDisable("Martinique_Jungle_04", "reload1_back", true);//джунгли
		break;
		
		case "Prosper_11":
			dialog.text = "We're almost in position, "+pchar.name+". Beyond this turn is the entrance into the cave. Come close and I'll tell you our plan.";
			link.l1 = "I'm all ears, Prosper.";
			link.l1.go = "Prosper_12";
		break;
		
		case "Prosper_12":
			dialog.text = "I need to get a steady aim with this heavy firelock, but if you can buy me time I won't miss. If I have to engage in hand-to-hand combat, forget about any fire support, I'll only be able to fend people off with my barrel as a club. This fight is going to depend on your skill at fencing.";
			link.l1 = "What are you trying to say?";
			link.l1.go = "Prosper_13";
		break;
		
		case "Prosper_13":
			dialog.text = "All you need is to distract their attention in order to let me shoot them all. I can't move and shoot, so I will stick to one location. There are three bastards close to the cave's entrance. You should rush them as fast as you can with your blade in hand\nHit one of them and make them chase you. Lure them away from me. If all three will focus on you, I can shoot them down like birds as you parry and dodge. But if those savages swoop down upon me, we are doomed. Are you ready?";
			link.l1 = "This won't be the first time I've handled a sword, these savages are no threat.";
			link.l1.go = "Prosper_14";
			// belamour legendary edition -->
			link.l2 = "Ha! Don't worry about me. It's like hunting in Le Mans! Just don't shoot me in the back by mistake!";
			link.l2.go = "Prosper_14a";
		break;
		
		case "Prosper_14a":
			AddCharacterExpToSkill(pchar, "FencingL", 10);
			AddCharacterExpToSkill(pchar, "FencingS", 10);
			AddCharacterExpToSkill(pchar, "FencingH", 10);
			AddCharacterExpToSkill(pchar, "Pistol", 10);
			dialog.text = "Go first, I'm behind you. Remember: you must not let them get close to me!";
			link.l1 = "I remember, let's go. Forward!";
			link.l1.go = "Prosper_15";
		break;
		
		case "Prosper_14":
			AddCharacterExpToSkill(pchar, "Leadership", 40);
			// <-- legendary edition
			dialog.text = "Then prepare for action. Go first, I'll be behind you. Remember: you can't let them get within a close distance to me!";
			link.l1 = "I remember. I'll do everything I can. Onward!";
			link.l1.go = "Prosper_15";
		break;
		
		case "Prosper_15":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LocatorReloadEnterDisable("Martinique_jungle_04", "reload2_back", false);
			NextDiag.CurrentNode = "Prosper_16";
			NewGameTip("A challenging fight awaits ahead. (F6) for quick save.");
		break;
		
		case "Prosper_16":
			dialog.text = "Well done, "+pchar.name+"! These pagan savages will murder no longer. Now for the main event - the cave. I believe that there are three or four of them inside, but I can't know for sure. Now listen\nI've been there ten years ago. There is a narrow tunnel inside the cave. It leads to a small grotto, divided by a wall with a hole in the middle of it. Let's repeat our plan from before. I stand still close to the entrance and you rush in\nProvoke them, don't try to fight all of them at once, just prevent them from attacking me. Take position at the tunnel I mentioned, it is narrow, so only one or two of them will be able to fight you at the same time\nI will shoot at them over your shoulder. Ready?";
			link.l1 = "Onward! Let's finish off this nest of savages!";
			link.l1.go = "Prosper_17";
		break;
		
		case "Prosper_17":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LocatorReloadEnterDisable("Martinique_CaveEntrance", "reload1_back", false);
			AddComplexSelfExpToScill(20, 20, 20, 20);
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1 = "location";
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.location = "Martinique_Grot";
			pchar.quest.Sharlie_RescueDaughter2.function = "RescueDaughter_CreateIndiansGrot";
			NextDiag.CurrentNode = "Prosper_18";
		break;
		
		case "Prosper_18":
			dialog.text = "My daughter is alive! Thank God! We've got here in time, "+pchar.name+". I'm indebted to you, sir. You're a brave man and a good fighter!";
			link.l1 = "I'm glad that there is a happy ending, Prosper. That was quite some bloody work taking out all those Indians.";
			link.l1.go = "Prosper_19";
		break;
		
		case "Prosper_19":
			DialogExit();
			sld = characterFromId("RD_Selina");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
			AddComplexSelfExpToScill(30, 30, 30, 30);
		break;
		
		case "Prosper_20":
			dialog.text = "My deepest thanks once again, "+pchar.name+"! Now let's make our way back to town. The life of my daughter is priceless, immeasurable by any amount of money, but I want to thank you by giving you what's left of my savings. As soon as we get to Saint-Pierre, I will gladly give them to you. And don't even think of refusing!";
			link.l1 = "I won't refuse, Prosper. Although money was not my object in helping you.";
			link.l1.go = "Prosper_21";
		break;
		
		case "Prosper_21":
			dialog.text = "You are a true Christian knight, "+pchar.name+"! Now let's not meddle around here. Let's make our way back home posthaste!";
			link.l1 = "...";
			link.l1.go = "Prosper_22";
		break;
		
		case "Prosper_22":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetImmortal(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			sld = characterFromId("RD_Selina");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			sld = characterFromId("RD_Jilberte");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			pchar.quest.Tutorial_Amulet.over = "yes";
			SetLaunchFrameFormParam("Back to the town...", "Reload_To_Location", 0, 3.0);
			SetLaunchFrameReloadLocationParam("FortFrance_town", "reload", "gate_back", "");
			LaunchFrameForm();
		break;
		
		case "Prosper_23":
			SelectPresentAmulet();
			dialog.text = "Here we are, Charles. I thank you once again for your help and tie this modest sum of pesos and gold doubloons to my words. I suggest you don't waste doubloons and hold onto them for special occasions. I know, this is not much money for such a service you have granted me, but it's from the bottom of my heart. Also take this amulet, "+pchar.questTemp.SMQ.Text+"";
			link.l1 = "Thank you! Farewell Prosper, I wish happiness to you and to your dear daughter!";
			link.l1.go = "Prosper_24";
		break;
		
		case "Prosper_24":
			LocatorReloadEnterDisable("Fortfrance_exittown", "reload2_back", false);//форт
			LocatorReloadEnterDisable("Martinique_Jungle_01", "reload1_back", false);//джунгли
			LocatorReloadEnterDisable("Martinique_Jungle_04", "reload1_back", false);//джунгли
			AddMoneyToCharacter(pchar, 5000);
			TakeNItems(pchar, "gold_dublon", 15);
			TakeNItems(pchar, pchar.questTemp.SMQ.Amulet, 1);
			Log_Info("You've received 15 doubloons");
			Log_Info("You've received an amulet");
			PlaySound("interface\important_item.wav");
			dialog.text = "Ah, a husband like you would do her well. All she does is get chased around town by a bunch of skinny-legged, chinless fops. Such a damned pity that every last one of them off and disappeared somewhere... good riddance to them. Good luck, Charles!";
			link.l1 = "...";
			link.l1.go = "Prosper_25";
		break;
		
		case "Prosper_25":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload10_back", "none", "", "", "", 10.0);
			sld = characterFromId("RD_Selina");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload10_back", "none", "", "", "", 10.0);
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterComplexReputation(pchar,"authority", 2);
			AddCharacterExpToSkill(pchar, "Leadership", 120);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 70);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 70);//скрытность
			AddQuestRecord("SharlieF", "7");
			CloseQuestHeader("SharlieF");
			DeleteAttribute(pchar, "questTemp.SMQ");
			pchar.questTemp.Prosper_fmql = "true"; // Addon-2016 Jason, французские миниквесты (ФМК)
			pchar.questTemp.ZsI_Cannibals = true;	//Sinistra Требуется для квеста "Знакомство с индейцами"
			pchar.quest.Sharlie_JungleNative.win_condition.l1 = "location";
			pchar.quest.Sharlie_JungleNative.win_condition.l1.location = "Martinique_jungle_01";
			pchar.quest.Sharlie_JungleNative.function = "SharlieJungleNative";
			SetCurrentTime(17,30);
			//AddTimeToCurrent(2,0);
			//QuestPointerToLoc("fortfrance_town", "reload", "reload4_back");
			sld = characterFromId("RD_Jilberte");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Selina":
			dialog.text = "Ah! God help me! (crying) You...you can't even imagine the horror that's going on here! These... these Indians have dragged us here to kill us and eat us! Cesar Blanchet was here...The savages took him... They performed some awful devilish ritual and then... Lord, I can't even speak of it! I was supposed to be next! They were going to slaughter me... tomorrow!";
			link.l1 = "Calm down, Celine. It's all over. Those bastards have got what they deserved and they won't hurt anyone anymore.";
			link.l1.go = "Selina_1";
		break;
		
		case "Selina_1":
			dialog.text = "Gilbert Coursie is here too. Over there... he uh...he still hasn't recovered yet. Speak with him... Then let's hurry up and get out of here!";
			link.l1 = "There, there. It's all right, girl. Enough crying. Everything's fine. You've got a wonderful father. He wouldn't let anybody harm you... Go outside, I'll help...uh... Gilbert out of here and I'll catch up with you later.";
			link.l1.go = "Selina_2";
		break;
		
		case "Selina_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "Martinique_CaveEntrance", "officers", "reload1_2", "", 5.0);
			sld = characterFromId("RD_Prosper");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "Martinique_CaveEntrance", "officers", "reload1_1", "", 5.0);
			AddQuestRecord("SharlieF", "5");
			sld = characterFromId("RD_Jilberte");
			LAi_SetStayType(sld);
		break;
		
		case "Selina_3":
			dialog.text = "God and the Blessed Mother have heard my prayers! Have you come to save us?";
			link.l1 = "You... Your name is Celine, isn't it?";
			link.l1.go = "Selina_4";
		break;
		
		case "Selina_4":
			dialog.text = "Yes... (crying) You...you can't even imagine the horror that's going on here! These... these Indians have dragged us here to kill us and eat us! Cesar Blanchet was here...They took him... They performed some devilish ritual and then... Lord, I can't even speak of it! I'm supposed to be next! They were going to slaughter me... tomorrow!";
			link.l1 = "Calm down, little girl... I'm sorry but I bring you bad news. I came here with your father. He was killed just outside by those redskinned savages as we fought to get to you. He gave his life to save you.";
			link.l1.go = "Selina_5";
		break;
		
		case "Selina_5":
			dialog.text = "What?! My father... Oh God! I... I...(sobbing)";
			link.l1 = "My condolences, Celine. There is another here with you, am I right?";
			link.l1.go = "Selina_6";
		break;
		
		case "Selina_6":
			dialog.text = "(through tears) Yes... Gilbert Coursie. He's in there... He still hasn't recovered yet. Go speak to him... Then let's hurry out of here!";
			link.l1 = "Yes, of course. We can't waste one minute standing around here.";
			link.l1.go = "Selina_7";
		break;
		
		case "Selina_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "Martinique_CaveEntrance", "officers", "reload1_2", "", 5.0);
			AddQuestRecord("SharlieF", "6");
			sld = characterFromId("RD_Jilberte");
			LAi_SetStayType(sld);
			AddComplexSelfExpToScill(20, 20, 20, 20);
		break;
		
		case "Selina_8":
			dialog.text = "My father... My poor, dear father! Ah, monsieur, I haven't even thanked you for saving me...";
			link.l1 = "Selina I'm just glad that you and Gilbert came out of that cave alive. Your father's heroic death was not in vain.";
			link.l1.go = "Selina_9";
		break;
		
		case "Selina_9":
			dialog.text = "(crying) Please, monsieur, take us with you to town. We have to send for the soldiers to come and get my father's body, so that he will have a proper Christian burial...";
			link.l1 = "Of course, Celine. Follow me!";
			link.l1.go = "Selina_10";
		break;
		
		case "Selina_10":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			sld = characterFromId("RD_Jilberte");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
		break;
		
		case "Selina_11":
			dialog.text = "Thank you, monsieur, for accompanying my poor father... Thank you for saving me from certain death. I... I... Here, take this bag of doubloons. I found it at home in my father's chest. Please, don't even dare think of refusing!";
			link.l1 = "Thank you, Celine. I'm glad we managed to save you. And my sincere condolences about the loss of your father.";
			link.l1.go = "Selina_12";
		break;
		
		case "Selina_12":
			TakeNItems(pchar, "gold_dublon", 15);
			PlaySound("interface\important_item.wav");
			dialog.text = "You are a noble man, monsieur. I will never forget you. Farewell!";
			link.l1 = "Farewell, Celine.";
			link.l1.go = "Selina_13";
		break;
		
		case "Selina_13":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload10_back", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterComplexReputation(pchar,"authority", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
			AddQuestRecord("SharlieF", "8");
			CloseQuestHeader("SharlieF");
			pchar.questTemp.ZsI_Cannibals = true;	//Sinistra Требуется для квеста "Знакомство с индейцами"
			
			sld = characterFromId("RD_Jilberte");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Jilberte":
			PlaySound("Voice\English\other\robinzons-08.wav");
			dialog.text = "Oh Lord, is it really all behind us? I can't even believe it... You've saved both me and Celine. If it weren't for you, the same fate that befell the luckless Cesar would've called upon her tomorrow and the same would be prepared for me in a few days.";
			link.l1 = "These Indians, are they really cannibals?!";
			link.l1.go = "Jilberte_1";
		break;
		
		case "Jilberte_1":
			dialog.text = "You doubt it? If you have a strong stomach, have a look into the ashes of their cooking fire. You'll find poor old Cesar there. Now he's just some gnawed bones...";
			link.l1 = "Blessed Sacrement... No, I'll pass. I've only recently arrived here from Europe and I couldn't even imagine that such vile diabolical things still take place on Earth.";
			link.l1.go = "Jilberte_2";
		break;
		
		case "Jilberte_2":
			dialog.text = "A lot of strange things happen in the Caribbean, things that you heard whispers of in the Old World... Indian medicine men, magic, shamans, and secret rituals. Stay here longer and you will witness all sorts of devilry. But forgive me, I haven't thanked you for saving me - I am still in shock\nYou saved my life and I am going to express my gratitude not only in words, but also in gold. Escort Celine and me to the city. There I will be able to thank you as you deserve, monsieur.";
			link.l1 = "All right. Step outside. I'm going to have a look around here first.";
			link.l1.go = "Jilberte_3";
		break;
		
		case "Jilberte_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "Martinique_CaveEntrance", "officers", "reload1_3", "OpenTheDoors", 10.0);
			pchar.quest.Sharlie_RescueDaughter5.win_condition.l1 = "location";
			pchar.quest.Sharlie_RescueDaughter5.win_condition.l1.location = "Martinique_CaveEntrance";
			pchar.quest.Sharlie_RescueDaughter5.function = "RescueDaughter_GoHome";
		break;
		
		case "Jilberte_4":
			dialog.text = "Let me express to you my profound gratitude once more for saving me, monsieur! As promised, I add to my verbal gratitude material gratitude in the form of silver pesos and gold doubloons.";
			link.l1 = "I am glad that everything turned out for the best, Gilbert.";
			link.l1.go = "Jilberte_5";
		break;
		
		case "Jilberte_5":
			AddMoneyToCharacter(pchar, 3000);
			TakeNItems(pchar, "gold_dublon", 20);
			Log_Info("You've received 20 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "You can't even imagine how happy I am about this! Thank you once again and allow me to take my leave, monsieur.";
			link.l1 = "Good luck, Gilbert! By the way, would you happen to know if anyone else in Saint-Pierre needs help?";
			link.l1.go = "Jilberte_6a";
		break;
		
		case "Jilberte_6a":
			dialog.text = "I don't know, but... You can ask the citizens out on the streets, Monsieur. Ordinary townspeople, and even the well-off ones are unlikely to offer anything worthy, but the rich nobles... they might have some job for you.";
			link.l1 = "Understood, Gilbert, thanks. See you!";
			link.l1.go = "Jilberte_6";
		break;
		
		case "Jilberte_6":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "questTemp.Sharlie.RescueDaughter");
			
			//Подбегает дворянин с квестом "девочка по вызову"
			sld = GetCharacter(NPC_GenerateCharacter("GigoloMan", "Guide_2", "man", "man", 25, FRANCE, 5, true, "soldier"));
			SetFantomParamFromRank(sld, 25, true);
			sld.Dialog.Filename = "Quest\Sharlie\StartMiniQuests.c";
			sld.dialog.currentnode = "GigoloMan";
			sld.greeting = "noble_male";
			AddLandQuestMark(sld, "questmarkmain");
			LAi_SetLoginTime(sld, 6.0, 21.0);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			ChangeCharacterAddressGroup(sld, "Fortfrance_town", "goto", "goto1");
			sld.talker = 9;
			LAi_SetCitizenType(sld);
		break;
		
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar, "Listen you, I am a law abiding citizen of this city. I must ask you not to walk around with your blade exposed like a robber.", "Sir please, the law is clear that men may not go about with weapons drawn within the city walls.");
			link.l1 = LinkRandPhrase("Alright.", "Very well.", "As you wish...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			if (npchar.id == "GigoloMan") NextDiag.TempNode = "GigoloMan";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}

void SelectPresentAmulet()
{
	switch (pchar.HeroParam.HeroType)
	{        
		case "HeroType_1":
			pchar.questTemp.SMQ.Amulet = "indian_7";
			pchar.questTemp.SMQ.Text = "it adds endurance and gives a second wind.";
		break;
		
		case "HeroType_2":
			pchar.questTemp.SMQ.Amulet = "amulet_7";
			pchar.questTemp.SMQ.Text = "it heightens resilience to battle wounds.";
		break;
		
		case "HeroType_3":
			pchar.questTemp.SMQ.Amulet = "indian_4";
			pchar.questTemp.SMQ.Text = "it raises the attack strength of your weapons.";
		break;
		
		case "HeroType_4":
			pchar.questTemp.SMQ.Amulet = "indian_1";
			pchar.questTemp.SMQ.Text = "it makes fire weaponry much more lethal.";
		break;
	}
}

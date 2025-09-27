void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag, arRld, arDis;
	int i, Qty;
	ref rColony;
	
	int iTest;
	
	bool  ok; // лесник . спецпеременная.

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	iTest = FindColony(NPChar.City);
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_GoOut":
			makearef(arRld, Locations[reload_cur_location_index].reload);
    		Qty = GetAttributesNum(arRld);
			for (i=0; i<Qty; i++)
    		{
    			arDis = GetAttributeN(arRld, i);
    			if (arDis.go == npchar.location)
    			{
					arDis.disable = true; //закрываем вход в дом
					break;
    			}
    		}
			DoQuestFunctionDelay("HouseEnc_TimerGoUot", 10.0);
			pchar.questTemp.HouseEncTimer = pchar.location;
			pchar.questTemp.HouseEncTimer.Id = npchar.id;
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "exit_close":
			makearef(arRld, Locations[reload_cur_location_index].reload);
    		Qty = GetAttributesNum(arRld);
			for (i=0; i<Qty; i++)
    		{
    			arDis = GetAttributeN(arRld, i);
    			if (arDis.go == npchar.location)
    			{
					arDis.disable = true; //закрываем вход в дом
					break;
    			}
    		}
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//--------------------------------- мужик ---------------------------------
		case "HouseMan":
			NextDiag.TempNode = "HouseMan";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase("An alarm has been raised in the town. Apparently, it's time for me to take up arms as well...","Aren't the city guards chasing after you, by any chance? ","You will find no shelter here, but you may well find several inches of cold steel between your ribs!"),LinkRandPhrase("What do you need?"+GetSexPhrase("scoundrel","rascal")+"?! The city guards have already caught your scent, you won't get far, "+GetSexPhrase("filthy pirate","you pirate wench")+"!","Filthy murderer! Guards!!!","I don't fear you, "+GetSexPhrase("creep","wench")+"! Soon you will be hanged in our fort, you won't get far..."));
				link.l1 = PCharRepPhrase(RandPhraseSimple("I see you're tired of living...","So it seems, there is no peaceful life for the citizens of "+XI_ConvertString("Colony"+npchar.city+"Gen")+"!"),RandPhraseSimple("Go to hell!","Heh, these will be the last few seconds of your life..."));
				link.l1.go = PCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			if (isBadReputation(pchar, 40))
			{
				if (CheckAttribute(pchar, "questTemp.HouseEncTimer"))
				{
					dialog.text = "I have warned you. Now you can decide for yourself if you want to get into trouble.";
					link.l1 = "Heh!";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "What do you want in my house, scoundrel?! You have ten seconds to get out of here!";
					link.l1 = LinkRandPhrase("Heh, looks like they know me here too!","My fame has just preceded me...","Hmm, I see.");
					link.l1.go = "exit_GoOut";
				}
			}
			else
			{
				if (IsDay())
				{
					dialog.text = NPCStringReactionRepeat("I am glad to welcome you to my home. Do you have business with me?","What can I do for you?","Hmm... What can I do for you?","I am sorry, but if you have no business with me, please do not disturb me...","block",1,npchar,Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("No, just looking around, meeting new people...","No, nothing in particular...","Nothing...","Fine, as you say.",npchar,Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("HouseMan_1", "exit_setOwner", "exit_setOwner", "exit_setOwner", npchar, Dialog.CurrentNode);
				}
				else
				{
					dialog.text = NPCStringReactionRepeat("I am sorry, but the night is not the best time for visiting, and therefore I must ask you to leave my house at once!","I have already told you, it's late. Please, leave.","I don't want to appear rude, but I insist that you leave my house at once!","Goddamn it, what's going on?! Guards! Thieves!","block",1,npchar,Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("Alright, I see...","Yeah, just a moment...","Alright, just don't get so excited.","What thieves?! Shut up!",npchar,Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("exit_close", "exit_setOwner", "exit_setOwner", "fight", npchar, Dialog.CurrentNode);
				}
			}
		break;

		case "HouseMan_1":
			dialog.text = "Oh, allow me to introduce myself - "+GetFullName(npchar)+". We're very happy to have you as our guest. In this town, the laws of hospitality are honoured.";
			link.l1 = GetFullName(pchar)+", if you please...";
			link.l1.go = "exit_setOwner";
		break;
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("You're "+GetSexPhrase("a thief, I see! Guards, seize him","a thief, I see! Guards, seize her")+"!!!","I can't believe it! I turned away for a second - and you're rifling through my belongings! Stop, thief!!!","Guards! Robbery! Stop the thief!!!");
			link.l1 = "Aaaah, devil!!!";
			link.l1.go = "fight";
		break;
		// --------------------------------- баба ---------------------------------
		case "HouseWoman":
			NextDiag.TempNode = "HouseWoman";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase("I am warning you, my husband will return soon! You'd better leave my house now!","I don't think you'll manage to escape! And be aware that my husband will be home soon!","My husband will be home soon! You must leave at once!"),LinkRandPhrase("A pity that my husband is not at home... Get out! Now!!!","Filthy murderer, get out of my house at once! Guards!",""+GetSexPhrase("What a scoundrel","What filth")+"... Soon my husband will return, and he will see what colour your blood is!"));
				link.l1 = PCharRepPhrase(RandPhraseSimple("Oh, your husband... oooooh... I am trembling...","Heh... You know, lass, your husband is just one man... you wouldn't want him dead at your feet, would you?"),RandPhraseSimple("Shut up, wench, before I gut you...","I will stay here for as long as I want. And you’d better keep your mouth shut if you know what's good for you..."));
				link.l1.go = "exit_setOwner";
				break;
			}
			if (isBadReputation(pchar, 40))
			{
				if (CheckAttribute(pchar, "questTemp.HouseEncTimer"))
				{
					dialog.text = "I have warned you. Get out or you will regret it!";
					link.l1 = "What a foolish wench...";
					link.l1.go = "exit";
				}
				else
				{					
					dialog.text = "What are you doing in my house, "+GetSexPhrase("scoundrel","rascal")+"?! If you are not gone in ten seconds, I am calling the guards!";
					link.l1 = "What a stupid wench...";
					link.l1.go = "exit_GoOut";
				}
			}
			else
			{
				if (IsDay())
				{
					dialog.text = NPCStringReactionRepeat("I am glad to see you in our house. My name is "+GetFullName(npchar)+". What can I do for you?","You still here?","Hm, excuse me, but don't you think it's time for you to leave?","I would kindly ask you not to abuse our hospitality.","block",1,npchar,Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat(GetFullName(pchar)+" at your service. I came here for no particular reason, just to make your acquaintance.","Still here.","Well, I don't know...","Fine.",npchar,Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("HouseWoman_1", "exit_setOwner", "exit_setOwner", "exit_setOwner", npchar, Dialog.CurrentNode);
				}
				else
				{
					dialog.text = NPCStringReactionRepeat("Oh my, why are you breaking into my house at such a time! You really scared me... Please, come visit us tomorrow!","Please, leave our house!"+GetSexPhrase("","I am a married woman!")+"","I am asking you to leave our home for the last time!","But what is going on here?!","block",1,npchar,Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("Don't be afraid, I won't hurt you.","Alright, just don't get so agitated.","I am leaving.","What's up?",npchar,Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("exit_close", "exit_setOwner", "exit_setOwner", "HouseWoman_2", npchar, Dialog.CurrentNode);
				}
			}
		break;

		case "HouseWoman_1":
			dialog.text = "We are always happy to have guests. Just don't stay here too long,"+GetSexPhrase(", since I am a married woman..."," since I have a lot to do...")+"";
			link.l1 = "Oh, yes, sure...";
			link.l1.go = "exit_setOwner";
		break;
		case "Woman_FackYou":
			dialog.text = "So that's how it is? I welcomed you as my guest, and you're rummaging through our chests?! Guards!";
			link.l1 = "Shut up, you bitch!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		case "HouseWoman_2":
			dialog.text = "I asked you to leave our house politely, but you simply would not listen! Enough! Help! Guards!";
			link.l1 = "Shut up, you foolish woman! Are you mad?!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break; 
		//--------------------------------- завсклад ---------------------------------		
		case "SkladMan":
			NextDiag.TempNode = "SkladMan1";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("An alarm has been raised in the town. Apparently, it's time for me to take up arms as well...","Aren't the city guards chasing after you, by any chance? ","You will find no shelter here, but you may well find several inches of cold steel between your ribs!"),LinkRandPhrase("What do you need?"+GetSexPhrase("scoundrel","rascal")+"?! The city guards have already caught your scent, you won't get far, "+GetSexPhrase("filthy pirate","wench")+"!","Filthy murderer! Guards!!!","I don't fear you, "+GetSexPhrase("creep","wench")+"! Soon you'll be hanged in our fort, you won't get far..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("I see you're tired of living...","So it seems, there is no peaceful life for the citizens of "+XI_ConvertString("Colony"+npchar.city+"Gen")+"!"),RandPhraseSimple("Go to hell!","Heh, these will be the last few seconds of your life..."));
				link.l1.go = NPCharRepPhrase("exit_setOwner", "fight");
				break;
			}
				dialog.text = NPCStringReactionRepeat("Welcome! My name is "+GetFullName(npchar)+". Here, I'm in charge, so don't even think about taking anything with you...","Behave yourself and keep in mind that I'm keeping an eye on you.","As long as you don't peek into the chests, you may stay here. I am bored alone, anyway...",RandPhraseSimple("Oh my, I am so bored!","Goddammit, what should I do? Being here is so boring!"),"block",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Alright, don't worry.","Sure!","I see...","Yeah, that sounds like a problem.",npchar,Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "exit", npchar, Dialog.CurrentNode);				
		break;
		
		case "SkladMan1":
			NextDiag.TempNode = "SkladMan1";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("An alarm has been raised in the town. Apparently, it's time for me to take up arms as well...","Aren't the city guards chasing after you, by any chance? ","You will find no shelter here, but you may well find several inches of cold steel between your ribs!"),LinkRandPhrase("What do you need?"+GetSexPhrase("scoundrel","rascal")+"?! The city guards have already caught your scent, you won't get far, "+GetSexPhrase("filthy pirate","wench")+"!",""+GetSexPhrase("Filthy","Filthy")+" Murderer! Guards!!!","I don't fear you, "+GetSexPhrase("creep","wench")+"! Soon you'll be hanged in our fort, you won't get far..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("I see you're tired of living...","So it seems, there is no peaceful life for the citizens of "+XI_ConvertString("Colony"+npchar.city+"Gen")+"!"),RandPhraseSimple("Go to hell!","Heh, these will be the last few seconds of your life..."));
				link.l1.go = NPCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			dialog.text = NPCStringReactionRepeat("Here, I am in charge, so don't even think about taking anything with you...","Behave yourself and keep in mind that I'm keeping an eye on you.","As long as you don't peek into the chests, you may stay here. I am bored alone, anyway...",RandPhraseSimple("Oh my, I am so bored!","Goddammit, what should I do? Being here is so boring!"),"block",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Alright, don't worry.","Sure!","I see...","Yeah, that sounds like a problem.",npchar,Dialog.CurrentNode);	
			link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "exit", npchar, Dialog.CurrentNode);				
			//открывание двери верфи по квесту промышленного шпионажа
			if (CheckAttribute(pchar, "questTemp.different.ShipyardsMap") && pchar.questTemp.different.ShipyardsMap == "toTarget" && npchar.city == pchar.questTemp.different.ShipyardsMap.city && locations[reload_cur_location_index].type == "shipyard")
			{
				link.l2 = "Listen, mate, I want to speak to you openly.";
				link.l2.go = "ShipyardsMap_1";
				pchar.questTemp.different.ShipyardsMap = "toResult";					
			}
			// ugeen --> склад товаров для ГГ				
			if(CheckAttribute(NPChar,"Storage"))
			{
				if(!CheckAttribute(NPChar, "Storage.Speak"))
				{
					dialog.text = "I have a tempting offer for you. Perhaps you might be interested in it.";
					link.l7 = "Really? Alright, I'm listening.";
					link.l7.go = "storage_rent";
				}
				else
				{
					if(CheckAttribute(NPChar,"Storage.Activate"))
					{
						link.l7 = "Take me to the warehouse. I want to see what condition it's in.";
						link.l7.go = "storage_0";
						link.l8 = "I have decided to vacate the warehouse. I don't need it anymore.";
						link.l8.go = "storage_04";
					}
					else
					{
						if(!CheckAttribute(NPChar,"Storage.NoActivate"))
						{
							link.l7 = "You mentioned a warehouse. Is it still vacant?";
							link.l7.go = "storage_01";
						}						
					}
				}		
			// <-- ugeen
			}		
		break;
		
		//--------------------------------- Аренда склада ---------------------------------
		case "storage_rent":
			NPChar.Storage.Speak = true;
			dialog.text = "We have an area suitable as a warehouse. Would you like to rent it for a reasonable price? Just think, you'd have your own warehouse to store valuable cargo...";
			link.l1 = "A warehouse, you say? Yes, tempting, indeed... Is it large enough? And how much will you charge for the rent?";
			link.l1.go = "storage_rent1";
		break;
		
		case "storage_rent1":
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar); 
			dialog.text = "It's quite spacious, even for a port warehouse. It can hold, let's see... 50,000 centners of cargo. For "+FindRussianMoneyString(sti(NPChar.MoneyForStorage))+"  per month I can provide safekeeping for your goods. "+"This includes guarding it with my men, protecting it from waterlogging, and fighting the rats. What say you? Oh, and confidentiality too, that goes without saying.";
			link.l1 = "Will do. May I take a look at it?";	
			link.l1.go = "storage_rent2";
			link.l2 = "That's too much. And I bet it's flooded and infested with rats.";
			link.l2.go = "storage_rent3";		
		break;
		
		case "storage_rent2":
			dialog.text = "Sure, sure. But... I'll need a month's payment in advance. ";
			if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
			{
				link.l1 = "You are... quite the merchant, I must say. Here's your money ... I'll rent this shed.";
				link.l1.go = "storage_11";
			}
			else
			{	
				link.l1 = "You are... quite mercantile, I must say. Alright, I'll fetch the money.";
				link.l1.go = "exit";
			}	
		break;
		
		case "storage_rent3":
			dialog.text = "As you wish. If you change your mind, just let me know. And keep in mind that such a nice warehouse is unlikely to stay vacant for long...";
			link.l1 = "No problem. I'll let you know if I need it.";
			link.l1.go = "exit";
		break;
		
		case "storage_0":
			NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar, "Storage.Date") * sti(NPChar.Storage.MoneyForStorage); 
			if(sti(NPChar.MoneyForStorage) > 0) 
			{
				dialog.text = "And as for the rent, you still owe me  "+FindRussianMoneyString(sti(NPChar.MoneyForStorage))+".";
				if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
				{
					link.l1 = "Alright, I'll pay the rent now.";
					link.l1.go = "storage_3";
				}
				else
				{
					link.l1 = "I'll come back later.";
					link.l1.go = "exit";
				}
			}		
			else
			{ // лесник . если забыл с собой корабль то никак.
				ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		        if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
				{	
				dialog.text = "Go ahead.";
				link.l1 = "Thanks.";
				link.l1.go = "storage_2";
				}
				else
				{
                dialog.text = RandPhraseSimple("Captain, where is your ship? How do you plan to move the cargo?","I don't see your ship docked in the port. How exactly are you going to load her?");
                link.l1 = RandPhraseSimple("Oh... I completely forgot about that!","Dammit, that's right!");
			    link.l1.go = "exit";
				break;
                }			
			}
			link.l2 = "No, I've changed my mind.";
			link.l2.go = "exit"; 						
		break;
		
		case "storage_01":
			dialog.text = "No, "+GetSexPhrase("mister","ma'am")+", still vacant and waiting for you. I knew you wouldn't turn down my offer in the end.";
			link.l1 = "Very good. I'll rent it.";
			link.l1.go = "storage_1";
			link.l2 = "No, it just came to mind...";
			link.l2.go = "exit";
		break;
		
		case "storage_1":
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar); 
			dialog.text = "As you should remember, I need a month's payment up front.";
			if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
			{
				link.l1 = "Of course, I remember. Here you go.";
				link.l1.go = "storage_11";
			}
			else
			{
				link.l1 = "Dammit. Alright, I'll fetch the money.";
				link.l1.go = "exit";
			}
		break;
		
		case "storage_11":
			AddMoneyToCharacter(pchar, -makeint(NPChar.MoneyForStorage)); 
			NPChar.Storage.MoneyForStorage = NPChar.MoneyForStorage;
			NPChar.Storage.Activate = true;
			Achievment_Set("ach_67"); // ugeen 2016
			SaveCurrentNpcQuestDateParam(NPChar, "Storage.Date");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;
				
		case "storage_2":			
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;
		
		case "storage_3":			
			AddMoneyToCharacter(pchar, -sti(NPChar.MoneyForStorage)); 
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar);
			NPChar.Storage.MoneyForStorage = NPChar.MoneyForStorage;
			SaveCurrentNpcQuestDateParam(NPChar, "Storage.Date");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;		

		case "storage_04":
			dialog.text = "Leaving already? What a pity, it's really an excellent place on great terms. I assure you that you won't get a deal like this anywhere else in the Caribbean.";
			link.l1 = "I said, I am vacating it. Or do you propose I pay for storing air? You may look for another tenant.";
			link.l1.go = "storage_4";
			link.l2 = "Nowhere in the Caribbean, you say? Alright, I'll keep it for a while, then. But the rent, I must say, is a bit too high.";
			link.l2.go = "exit";
		break;
		
		case "storage_4":
			NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar,"Storage.Date") * sti(NPChar.Storage.MoneyForStorage); 
			if(sti(NPChar.MoneyForStorage) > 0) 			
			{
				dialog.text = "And as for the rent, you still owe me "+FindRussianMoneyString(sti(NPChar.MoneyForStorage))+".";
				if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))			
				{
					link.l1 = "Fine.";
					link.l1.go = "storage_5";
				}
			}
			else
			{ // лесник . если нет корабля то и товар не забрать
				ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		        if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
				{	
				dialog.text = "Collect your goods, and I will close the warehouse.";
				link.l1 = "Fine.";
				link.l1.go = "storage_6";
				}
				else
				{
                dialog.text = RandPhraseSimple("Captain, where is your ship? How do you plan to move the cargo?","I don't see your ship docked in the port. How exactly are you going to load her?");
                link.l1 = RandPhraseSimple("Oh... I completely forgot about that!","Dammit, that's right!");
			    link.l1.go = "exit";
				break;
                }				
			}
		break;
		
		case "storage_5":
			SetStorageGoodsToShip(&stores[sti(rColony.StoreNum)]);
			AddMoneyToCharacter(pchar, -sti(NPChar.MoneyForStorage)); 
			NPChar.Storage.NoActivate = true;
			DeleteAttribute(NPChar,"Storage.Activate");
			DialogExit();
		break;
		
		case "storage_6":
			SetStorageGoodsToShip(&stores[sti(rColony.StoreNum)]);
			DeleteAttribute(NPChar,"Storage.Activate");
			NPChar.Storage.NoActivate = true;
			DialogExit();
		break;		

		//--------------------------------- Аренда склада ---------------------------------
		
		case "ShipyardsMap_1":
			dialog.text = "Heh! Alright, let's talk.";
			link.l1 = "I need to get to the shipyard at night, when there's no one around.";
			link.l1.go = "ShipyardsMap_2";
		break;
		case "ShipyardsMap_2":
			if (sti(pchar.questTemp.different.ShipyardsMap.skladFight))
			{
				dialog.text = "Look at you! Hey, guards, we have a thief here!!!";
				link.l1 = "What thief? I just wanted to talk!";
				link.l1.go = "fight";
				AddCharacterExpToSkill(pchar, "FencingL", 5);
				AddCharacterExpToSkill(pchar, "FencingS", 5);
				AddCharacterExpToSkill(pchar, "FencingH", 5);
				ChangeCharacterComplexReputation(pchar,"nobility", -1);
			}
			else
			{
				dialog.text = "Shiver me timbers! Look at you, "+GetSexPhrase("mate","lass")+". To come to the shipyard storehouse with such a request!";
				link.l1 = "I need to get to the shipyard itself. I couldn't care less about your storehouse.";
				link.l1.go = "ShipyardsMap_3";
				AddCharacterExpToSkill(pchar, "Fortune", 10);
			}
		break;
		case "ShipyardsMap_3":
			dialog.text = "But why do you need it?";
			link.l1 = "There is a need. And I am willing to pay for it...";
			link.l1.go = "ShipyardsMap_4";
		break;
		case "ShipyardsMap_4":
			dialog.text = "Hmm, that's better... Alright! Slip me "+FindRussianMoneyString(sti(pchar.questTemp.different.ShipyardsMap.sklad)*1000)+", and I'll leave the door to the shipyard open the following day.";
			link.l1 = "That's too expensive. I'll have to do without it, then...";
			link.l1.go = "exit";
			if (sti(pchar.money) >= (sti(pchar.questTemp.different.ShipyardsMap.sklad)*1000))
			{
				link.l2 = "Alright, I agree. Take your money and do as we agreed.";
				link.l2.go = "ShipyardsMap_5";
			}
		break;
		case "ShipyardsMap_5":
			dialog.text = "Don't worry, it will be done.";
			link.l1 = "I hope so...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.ShipyardsMap.sklad)*1000);
			AddQuestRecord("ShipyardsMap", "5");
			AddQuestUserData("ShipyardsMap", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			//снимаем close_for_night
			string  sName;
			int location_index = FindLocation(npchar.city + "_town");
    		makearef(arRld, Locations[location_index].reload);
    		Qty = GetAttributesNum(arRld);
    		for (int a=0; a<Qty; a++)
    		{
    			arDis = GetAttributeN(arRld, a);
				sName = arDis.go;
    			if (findsubstr(sName, "_shipyard" , 0) != -1)
    			{
					DeleteAttribute(arDis, "close_for_night");
					break;
    			}
    		}
			LocatorReloadEnterDisable(npchar.city + "_shipyard", "reload2", true);
			//ставим таймер на возврат close_for_night
			SetTimerFunction("ShipyardsMap_returnCFN", 0, 0, 2);
		break;

	}
}

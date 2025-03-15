// boal 08/04/06 общий диалог верфи
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;
	string s2;
	
	int iShipClass = GetCharacterShipClass(PChar); // Если корабля нет, вернет 7 (лодка)
	int iRank = sti(PChar.rank);
	int iSumm, iType;
	
	ref rRealShip;
	ref shTo;
	aref refShip;
	string attr;
	float fTmp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Shipyard\" + NPChar.City + "_Shipyard.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06
    bool ok;
    int iTest = FindColony(NPChar.City); // город магазина
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	int Material, WorkPrice;
	int amount;
	int	iCannonDiff;
	
	// генератор парусов по кейсу -->
	string attrLoc   = Dialog.CurrentNode;
	int i;
  	if (findsubstr(attrLoc, "SailsColorIdx_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.SailsColorIdx = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "SailsColorDone";
 	}
 	if (findsubstr(attrLoc, "SailsTypeChooseIDX_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.SailsTypeChooseIDX = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "SailsTypeChoose2";
 	}
 	// генератор парусов по кейсу <--
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "ship_tunning_not_now":  // аналог выхода, со старых времен, много переделывать.
            LockControl("DlgDown3", false);
			LockControl("DlgUp3", false);
			DialogExit();
			NextDiag.CurrentNode = "First time";  // выход для тюнинга, нужно тут из-за LoadSegment
		break;
		
		case "ship_tunning_not_now_1":  
			LockControl("DlgDown3", false);
			LockControl("DlgUp3", false);
			DialogExit();
			NextDiag.CurrentNode = "First time";  
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "First time":
            if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase("The alarm has been raised in the town, and everyone is looking for you. If I were you, I wouldn't stay here.", "All the city guards are scouring the town looking for you. I am not a fool and will not talk to you!", "Run, "+ GetSexPhrase("mate","lass") +", before the soldiers turn you into a sieve..."), 
					LinkRandPhrase("What do you need, "+ GetSexPhrase("scoundrel","stinker") +"?! The city guards already have your scent, you won't get far, filthy pirate!", "Murderer, leave my house at once! Guards!", "I am not afraid of you, "+ GetSexPhrase("scoundrel","rat") +"! Soon you will be hanged in our fort, you won't get far..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Heh, an alarm is not a problem for me...", "They will never get me."), 
					RandPhraseSimple("Shut your mouth, " + GetWorkTypeOfMan(npchar, "") + ", or I'll tear out your tongue!", "Heh, " + GetWorkTypeOfMan(npchar, "") + ", and there too - to catch pirates! That's what I tell you, mate: be quiet and you will not die!"));
				link.l1.go = "fight";
				break;
			}
			
//Jason ---------------------------------------Бремя гасконца------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock") && pchar.location == "Fortfrance_shipyard")
			{
				if (CheckAttribute(pchar, "questTemp.Sharlie.Rum") || CheckAttribute(pchar, "questTemp.Sharlie.Gigolo") || CheckAttribute(pchar, "questTemp.Sharlie.RescueDaughter"))
				{
					dialog.text = "Do you want anything, Monsieur?";
					Link.l1 = "I came to take a look at your ships... But right now I'm a bit busy - I still have a unfinished affair. I'll come in some time later, once I am through with it.";
					Link.l1.go = "exit";
					break;
				}
				if (pchar.questTemp.Sharlie == "ship" || pchar.questTemp.Sharlie == "ship_fast") // Addon 2016-1 Jason пиратская линейка 1
				{
					dialog.text = "Do you want anything, Monsieur?";
					Link.l1 = "Listen, I'd like to purchase a ship from you.";
					Link.l1.go = "Sharlie";
					break;
				}
				dialog.text = "Do you want anything else, Monsieur?";
				Link.l1 = "No, I guess not.";
				Link.l1.go = "exit";
				NextDiag.TempNode = "First time";
				NPChar.quest.meeting = "1";
				break;
			}
	//<-- Бремя гасконца
			// Addon-2016 Jason, французские миниквесты (ФМК) ФМК-Мартиника
			if (CheckAttribute(pchar, "questTemp.FMQM.Oil") && pchar.location == "Fortfrance_shipyard")
			{
				if (pchar.questTemp.FMQM == "remove_oil")
				{
					dialog.text = "This is it, Captain. Job's done. Now the pleasant part - the sound of coins. Give me a second...";
					link.l1 = "...";
					link.l1.go = "FMQM_oil_1";
					break;
				}
				if (pchar.questTemp.FMQM == "remove_oil1")
				{
					dialog.text = "Officer, wait! Please! This must be some kind of mistake. Monsieur, the Captain has nothing to do with this, he only docked here to see his ship repaired. He was just about to leave. And what barrels? What are you talking about?";
					link.l1 = "";
					link.l1.go = "FMQM_oil_2";
					break;
				}
				if (pchar.questTemp.FMQM == "remove_oil2")
				{
					dialog.text = "Officer, I say again: the Captain has come here to pay for ship repairs. These barrels are my property and they are only for production purposes. I am a master ship builder and this resin is for the vessels I build.";
					link.l1 = "";
					link.l1.go = "FMQM_oil_3";
					break;
				}
				if (pchar.questTemp.FMQM == "remove_oil3")
				{
					dialog.text = "Oh, Monsieur Captain! You have no idea how bad it was for me. Two days in dungeons accompanied by rats, mice and miserable characters! I had to use every connection I had to bail myself out of there. Ah, the fresh air!";
					link.l1 = "You have my sympathies, master. What about our resin? And my coins?";
					link.l1.go = "FMQM_oil_4";
					DelLandQuestMark(npchar);
					break;
				}
			}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_13" && pchar.location == "PortRoyal_shipyard")
			{
				dialog.text = "Oh, it's you again! I recognize you, young man! It was you who recently asked about... increasing your ship's speed using silk sailcloth, right?";
				link.l1 = "Your memory does you credit, master."; 
				link.l1.go = "mtraxx_x";
				break;
			}
			
			if(NPChar.quest.meeting == "0") // первая встреча
			{
				dialog.Text = GetNatPhrase(npchar, LinkRandPhrase("Ha! A real old salt came to my humble workshop! Are you new to the local waters, Captain?","Welcome, Sir! If you are not a alien to the sea and have a ship - you've come just to the right place!","Hello, Sir! You're in luck - this is the best ship workshop in all of the British New World."), LinkRandPhrase("Monsieur, I assume you're a dashing Captain, aren't you? If you are, you were right by visiting my modest shipyard!","First time here, Monsieur Captain? Come in and meet this old shipwright.","Let's have the pleasure of knowing each other, Monsieur! A ship needs to be caressed, just like a woman - and we, Frenchmen, are experts in that! Trust me, you won't regret coming here!"), LinkRandPhrase("I've never seen you here before, Senor. Nice meeting you!","I greet a valiant conqueror of the seas! You're a sailor, aren't you? And I am the local shipwright, we should get to know each other.","Hello, Caballero! I am happy to welcome you to my workshop!"),LinkRandPhrase("Good afternoon, Mynheer. I haven't met you before, have I? Do you have business with me?","Hello, Mynheer Captain. Don't be surprised, I've met quite a few Captains, so I realized that you're a Captain too, at first sight.","Come in, Mynheer. I am the local shipwright. Pleasure to meet you."));
				Link.l1 = LinkRandPhrase("I am glad to meet you, too. My name is "+GetFullName(pchar)+", and I am new to these places. So, I decided to drop in.","Just couldn't have passed by - you know, that smell of freshly planed planks... I am "+GetFullName(pchar)+", Captain of ship '"+pchar.ship.name+"'.","Allow me to introduce myself - "+GetFullName(pchar)+", Captain of ship '"+pchar.ship.name+"', pleased to meet you. So, you are building and repairing ships here, aren't you?");
				Link.l1.go = "meeting";
				NPChar.quest.meeting = "1";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_shipyard")
				{
					dialog.text = "Greetings, Captain MacArthur.";
					link.l1 = "You can just call me Helen, Mister "+npchar.lastname+". "+TimeGreeting()+".";
					Link.l1.go = "Helen_meeting";
				}
			}
			else
			{
				dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("Oh! The terror of the local water, Captain "+GetFullName(pchar)+"! What can I do for you?","Let's get straight down to business, "+GetAddress_Form(NPChar)+", I don't have time to chat. Do you require a repair or you just want to replace your tub?","Oh, isn't that "+GetFullName(pchar)+"! What's up, "+GetAddress_Form(NPChar)+"? Something bad happened to your tub?"),LinkRandPhrase("What do you need there, Captain? Not a single minute of peace - always all these rascals, what a cursed day...","Hello, "+GetAddress_Form(NPChar)+". I must say that your visit scared away all my customers. I hope your order will cover my damages?","On a business with me, "+GetAddress_Form(NPChar)+"? Well, get on with it, and be quick about it."),LinkRandPhrase("What brings you to me, Mister "+GetFullName(pchar)+"? I can understand that your ship might have a hard time, considering your lifestyle...","I am happy to greet a noble... oh, excuse me, "+GetAddress_Form(NPChar)+", I took you for someone else. What did you want?","I don't really like your type, Captain, but I will not drive you out, anyway. What did you want?")),LinkRandPhrase(LinkRandPhrase("I am very glad to see you, Mister "+GetFullName(pchar)+"! So, how is she running? Do you need a repair or careening?","Welcome, "+GetAddress_Form(NPChar)+"! Captain "+GetFullName(pchar)+" is always a welcome guest in my workshop!","Oh, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! You have paid me a visit again! I hope your beauty is fine, isn't she?"),LinkRandPhrase(""+GetAddress_Form(NPChar)+", I am so happy to see you again! How's your beautiful ship? Do you need help?","Oh, "+GetAddress_Form(NPChar)+", greetings! How are you doing? Maybe the masts are creaking or you need the bilge cleared? My guys will do their best for you!","Good afternoon, Captain "+GetFullName(pchar)+". I am glad that you have dropped in again, and I am always ready to help you."),LinkRandPhrase("I am happy to have you here, Captain! You are a very nice customer, "+GetAddress_Form(NPChar)+", and I wish that you stay as such.","Oh, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! I am really happy to have you here! What can I do for you?","Captain, again you have visited "+XI_ConvertString("Colony"+npchar.City+"Acc")+"! Believe me, we will be glad to help you.")));
				Link.l1 = pcharrepphrase(RandPhraseSimple(RandPhraseSimple("Get your instruments, master, and stay silent, alright? I am not in the mood.","Stop chattering, mate! I need your help, and not your twaddle."),RandPhraseSimple("I am paying - and you are working. Silently. Is that clear?","Hey, mate, drive them all away - it's me, your preferred customer!")),RandPhraseSimple(RandPhraseSimple("I am happy to see you, too, master. Alas, I don't have much time, so let's get down to business.","And I am happy to see you too, mate. Wanna help your preferred customer?"),RandPhraseSimple("Good afternoon, mate. Let's get down to business right away. Promise, next time we'll sit over a bottle for sure.","I am glad to see you, master. Always a pleasure seeing you, but right now I need your help.")));
				Link.l1.go = "Shipyard";
				if (GetNationRelation2MainCharacter(sti(NPChar.nation)) != RELATION_ENEMY) 
				{
					link.l11 = "I need cannons for my ship.";
					link.l11.go = "Cannons";					
				}	
				
				if(NPChar.city == "PortRoyal" || NPChar.city == "Havana" || NPChar.city == "Villemstad" || NPChar.city == "Charles" || NPChar.city == "PortoBello")
				{
					link.l22 = "Can you offer me something special, something that cannot be found at any other shipyard?";
					link.l22.go = "ship_tunning";
				}
				
				link.l15 = "Don't you have a job requiring help of a stranger?";
			    link.l15.go = "Tasks";
				// Jason Исла Мона 
				if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "tools" && !CheckAttribute(npchar, "quest.IslaMonaTools"))
				{
					link.l20 = "I want to buy a set of European quality construction, forging and measuring tools. Can you help me?";
					link.l20.go = "IslaMona";
				}
				if (CheckAttribute(npchar, "quest.IslaMonaMoney"))
				{
					link.l20 = "I brought doubloons for a set of building tools.";
					link.l20.go = "IslaMona_7";
				}
				//Jason --> генератор Призонер
				if (CheckAttribute(pchar, "GenQuest.Findship.Shipyarder") && NPChar.location == pchar.GenQuest.Findship.Shipyarder.City + "_shipyard")
				{
					ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
					if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
					{
						for(i = 1; i < COMPANION_MAX; i++)
						{
							int iTemp = GetCompanionIndex(PChar, i);
							if(iTemp > 0)
							{
								sld = GetCharacter(iTemp);
								if(GetRemovable(sld) && sti(RealShips[sti(sld.ship.type)].basetype) == sti(pchar.GenQuest.Findship.Shipyarder.ShipType))
								{
									pchar.GenQuest.Findship.Shipyarder.CompanionIndex = sld.Index;
									pchar.GenQuest.Findship.Shipyarder.OK = 1;
									pchar.GenQuest.Findship.Shipyarder.ShipName = sld.Ship.Name;
									pchar.GenQuest.Findship.Shipyarder.Money = makeint(GetShipSellPrice(sld, CharacterFromID(NPChar.city + "_shipyarder"))*1.5);
								}
							}
						}
					}
					if (sti(pchar.GenQuest.Findship.Shipyarder.OK) == 1)
					{
						link.l16 = "I delivered to you "+pchar.GenQuest.Findship.Shipyarder.ShipBaseName+", as you asked.";
						link.l16.go = "Findship_check";
					}// <-- генератор Призонер
				}
				//Jason --> генератор Неудачливый вор
				if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && CheckCharacterItem(pchar, "Tool") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_shipyard")
				{
					link.l17 = "I managed to seek out the thief and obtain "+pchar.GenQuest.Device.Shipyarder.Type+".";
					link.l17.go = "Device_complete";
				}
				// <-- генератор Неудачливый вор
				if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && RealShips[sti(Pchar.Ship.Type)].BaseType != SHIP_CURSED_FDM) // mitrokosta фикс ломаных диалогов
				{
					link.l12 = "I want to change the look of my sails.";
					link.l12.go = "SailsGerald";
				}
				Link.l2 = "I just wanted to talk.";
				Link.l2.go = "quests"; //(перессылка в файл города)
				// -->
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l3 = "I would like to talk to you about financial matters.";
					link.l3.go = "LoanForAll";
				}
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && CheckAttribute(pchar, "GenQuest.Intelligence.SpyId") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
				{
					link.l7 = RandPhraseSimple("I am here on request of one man. His name is Governor " + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".", 
						GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + " sent me to you. I am supposed to pick up something...");
					link.l7.go = "IntelligenceForAll";
				}
				//Jason, генер почтового курьера 2 уровня
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
				{
					if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
					{
						link.l14 = "I brought the drawing of the ship from "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
						link.l14.go = "Postcureer_LevelUp_ForAll";
					}
				} // patch-6
				if(CheckAttribute(pchar,"GenQuest.EncGirl"))
				{
					if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "shipyard_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
					{
						link.l7 = "Hello, I came by your son's invitation."; 
						link.l7.go = "EncGirl_4";
						pchar.quest.EncGirl_GetLoverFather.over = "yes";
					}	
					if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
					{
						if(pchar.GenQuest.EncGirl.Father == "shipyard_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
						{
							link.l8 = "This is about your daughter...";
							link.l8.go = "EncGirl_1";
						}
					}
				}								
				Link.l9 = "I need to go.";
				Link.l9.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "Meeting":
				dialog.Text = "I am very glad to meet a new customer. My shipyard is at your service.";
				Link.l1 = "Excellent, " + GetFullName(NPChar) + ". Let's take a look at what you can offer me.";
				Link.l1.go = "Shipyard";
				if (GetNationRelation2MainCharacter(sti(NPChar.nation)) != RELATION_ENEMY) 
				{
					link.l13 = "I need cannons for my ship.";
					link.l13.go = "Cannons";
				}									
				link.l15 = "Don't you have a job requiring help of a stranger?";
			    link.l15.go = "Tasks";
				
				if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && RealShips[sti(Pchar.Ship.Type)].BaseType != SHIP_CURSED_FDM) // mitrokosta фикс ломаных диалогов
				{
					link.l12 = "I want to change the look of my sails.";
					link.l12.go = "SailsGerald";
				}
				Link.l2 = "I just wanted to talk.";		
				link.l2.go = "quests";
				// -->
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l3 = "I would like to talk to you about financial matters.";
					link.l3.go = "LoanForAll";//(перессылка в файл города)
				}
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
				{
					link.l7 = RandPhraseSimple("I am here on request of one man. His name is Governor " + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".", 
						GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + " sent me to you. I am supposed to pick up something...");
					link.l7.go = "IntelligenceForAll";
				}
				//Jason, генер почтового курьера 2 уровня
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
				{
					if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
					{
						link.l14 = "I delivered the drawing of the ship from the town of "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
						link.l14.go = "Postcureer_LevelUp_ForAll";
					}
				}

				if(CheckAttribute(pchar,"GenQuest.EncGirl"))
				{
					if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "shipyard_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
					{
						link.l8 = "Hello, I came by your son's invitation."; 
						link.l8.go = "EncGirl_4";
						pchar.quest.EncGirl_GetLoverFather.over = "yes";
					}	
					if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
					{
						if(pchar.GenQuest.EncGirl.Father == "shipyard_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
						{
							link.l9 = "This is about your daughter...";
							link.l9.go = "EncGirl_1";
						}
					}
				}
				if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakShipyard"))
				{
					if(CheckAttribute(pchar, "questTemp.different.GiveShipLetters") && (pchar.questTemp.different.GiveShipLetters.city == npchar.city))
					{
						link.l10 = "What can you tell me about the owner of these documents?";
						link.l10.go = "ShipLetters_6";// генератор  "Найденные документы"
					}		
				}	
				Link.l11 = "I must leave, Thank you.";
				Link.l11.go = "exit";
				NextDiag.TempNode = "First time";
		break;
		
		case "Helen_Meeting":
				dialog.Text = "Of course, Captain MacArthur, as you wish. What do you need today?";
				Link.l1 = "Excellent, " + GetFullName(NPChar) + ". Let's take a look at what you can offer me.";
				Link.l1.go = "Shipyard";
				if (GetNationRelation2MainCharacter(sti(NPChar.nation)) != RELATION_ENEMY) 
				{
					link.l13 = "I need cannons for my ship.";
					link.l13.go = "Cannons";
				}									
				link.l15 = "Don't you have a job requiring help of a stranger?";
			    link.l15.go = "Tasks";
				
				if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && RealShips[sti(Pchar.Ship.Type)].BaseType != SHIP_CURSED_FDM) // mitrokosta фикс ломаных диалогов
				{
					link.l12 = "I want to change the look of my sails.";
					link.l12.go = "SailsGerald";
				}
				Link.l2 = "I just wanted to talk.";		
				link.l2.go = "quests";
				// -->
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l3 = "I would like to talk to you about financial matters.";
					link.l3.go = "LoanForAll";//(перессылка в файл города)
				}
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
				{
					link.l7 = RandPhraseSimple("I am here on request of one man. His name is Governor " + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".", 
						GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + " sent me to you. I am supposed to pick up something...");
					link.l7.go = "IntelligenceForAll";
				}
				//Jason, генер почтового курьера 2 уровня
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
				{
					if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
					{
						link.l14 = "I delivered the drawing of the ship from the town of "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
						link.l14.go = "Postcureer_LevelUp_ForAll";
					}
				}

				if(CheckAttribute(pchar,"GenQuest.EncGirl"))
				{
					if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "shipyard_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
					{
						link.l8 = "Hello, I came by your son's invitation."; 
						link.l8.go = "EncGirl_4";
						pchar.quest.EncGirl_GetLoverFather.over = "yes";
					}	
					if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
					{
						if(pchar.GenQuest.EncGirl.Father == "shipyard_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
						{
							link.l9 = "This is about your daughter...";
							link.l9.go = "EncGirl_1";
						}
					}
				}
				if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakShipyard"))
				{
					if(CheckAttribute(pchar, "questTemp.different.GiveShipLetters") && (pchar.questTemp.different.GiveShipLetters.city == npchar.city))
					{
						link.l10 = "What can you tell me about the owner of these documents?";
						link.l10.go = "ShipLetters_6";// генератор  "Найденные документы"
					}		
				}	
				Link.l11 = "I must leave, Thank you.";
				Link.l11.go = "exit";
				NextDiag.TempNode = "First time";
		break;

		case "ship_tunning":
			dialog.text = "Our shipyard is known for improving ships. Are you interested, Captain?";
			Link.l1 = LinkRandPhrase("Excellent! Perhaps you can take a look at my ship and tell me how it can be improved?",
			          "That's very interesting, master! And what can you do for my ship?",
					  "Hmm... You know, I got used to my ship, but if you offer me something really interesting, I can think about it. What do you say?");
			Link.l1.go = "ship_tunning_start";
		break;
				
		case "ship_tunning_start" :		
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if (sti(Pchar.Ship.Type) == SHIP_NOTUSED || ok)
			{				
				if (sti(RealShips[sti(pchar.Ship.Type)].Class) >= 6)
				{
					dialog.Text = "Errr... I am not dealing with boats. An old tub will still be an old tub, no matter how much effort you put into it.";
					Link.l1 = "I see...";
					Link.l1.go = "ship_tunning_not_now_1";
					break;
				}
				// belamour legendary edition -->
				if(!TuningAvailable())
				{
					dialog.Text = "So-so... let's see what we have here... Yeah - " + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) + ". Your ship already has the maximum number of improved characteristics, I'm afraid that further work on it makes no sense and can only do harm.";
					Link.l1 = "I see...";
					Link.l1.go = "ship_tunning_not_now_1";
					break;
				}
				// <-- legendary edition							
				if(GetHullPercent(pchar) < 100 || GetSailPercent(pchar) < 100)
				{
					dialog.Text = "Before improving a ship she must be fully repaired. This, too, can be done here at my shipyard.";
					Link.l1 = "Understood...";
					Link.l1.go = "ship_tunning_not_now_1";
					break;
				}
				
				s2 = "Alright, let's see what we've got here... Aha " + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) + ".";
				// belamour legendary edition -->
				if(NPChar.city == "PortRoyal")
				{
					s2 = s2 + " Our shipyard is famous for improving the ship's performance we can increase either the maximum speed or the angle to the wind.";
				}
				if(NPChar.city == "Havana" || NPChar.city == "PortoBello")
				{
					s2 = s2 + " At our shipyard we can increase the maximum number of cannons or the ship's carrying capacity.";
				}
				if(NPChar.city == "Villemstad")
				{
					s2 = s2 + " My guys can reinforce the hull of your ship or increase the maximum number of sailors in your crew.";
				}
				if(NPChar.city == "Charles")
				{
					s2 = s2 + " At this shipyard you can improve the maneurability or decrease the minimum number of sailors in the crew.";
				}	
				
				dialog.Text = s2;
				
				if(NPChar.city == "PortRoyal")
				{
					// belamour legendary edition -->
					ok = (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.SpeedRate")) && 
						 (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.WindAgainst"));
					if(ok)
					{
						Link.l1 = "Increase speed.";
						Link.l1.go = "ship_tunning_SpeedRate";
						Link.l2 = "Increase angle to the wind.";
						Link.l2.go = "ship_tunning_WindAgainst";
						Link.l3 = "Hold on! I've changed my mind.";
						Link.l3.go = "ship_tunning_not_now_1";
						break;
					}	
					else
					{
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.SpeedRate"))
						{
							Link.l1 = "Increase speed.";
							Link.l1.go = "ship_tunning_SpeedRate";
							Link.l2 = "Hold on! I've changed my mind.";
							Link.l2.go = "ship_tunning_not_now_1";
							break;
						}
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.WindAgainst"))
						{
							Link.l1 = "Increase angle to the wind.";
							Link.l1.go = "ship_tunning_WindAgainst";
							Link.l2 = "Hold on! I've changed my mind.";
							Link.l2.go = "ship_tunning_not_now_1";	
							break;
						}
						Link.l1 = LinkRandPhrase("Oh! My vessel is already improved in this way. Well, thank you for your time!",
						                         "Thank you, master, but I already have an improvement, and it's exactly what you've mentioned to me. Good luck with other ships and their Captains!",
												 "Heh! I take it that my ship had already been refitted before by a previous owner - it must have been at this very shipyard, Well, I guess I must thank him for his foresight, and you and your guys for their excellent work!");
						Link.l1.go = "ship_tunning_not_now_1";					
					}
						// <-- legendary edition
				}
				if(NPChar.city == "Havana" || NPChar.city == "PortoBello")
				{
					ok = (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.Cannon")) && 
						 (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.Capacity"));
					if(ok)
					{	
						if(GetPossibilityCannonsUpgrade(pchar, true) > 0)
						{	
							Link.l1 = "Increase the maximum number of cannons.";
							Link.l1.go = "ship_c_quantity";
						}	
							Link.l2 = "Increase the deadweight.";
							Link.l2.go = "ship_tunning_Capacity";
						Link.l3 = "Hold on! I changed my mind.";
						Link.l3.go = "ship_tunning_not_now_1";
						break;
					}
					else
					{
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.Cannon"))
						{
							if(GetPossibilityCannonsUpgrade(pchar, true) > 0)
							{	
								Link.l1 = "Increase the maximum number of cannons.";
								Link.l1.go = "ship_c_quantity";
								Link.l2 = "Hold on! I changed my mind.";
								Link.l2.go = "ship_tunning_not_now_1";	
								break;
							}	
						}
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.Capacity"))
						{
							Link.l1 = "Increase the deadweight.";
							Link.l1.go = "ship_tunning_Capacity";
							Link.l2 = "Hold on! I changed my mind.";
							Link.l2.go = "ship_tunning_not_now_1";	
							break;
						}
						Link.l1 = LinkRandPhrase("Oh! My vessel is already improved in this way. Well, thank you for your time!",
												 "Thank you, master, but I already have an improvement, and it's exactly what you've mentioned to me. Good luck with other ships and their Captains!",
												 "Heh! I take it that my ship had already been refitted before by a previous owner - it must have been at this very shipyard, Well, I guess I must thank him for his foresight, and you and your guys for their excellent work!");
						Link.l1.go = "ship_tunning_not_now_1";	
					// <-- legendary edition
					}						
				}
				if(NPChar.city == "Villemstad")
				{
					ok = (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.HP")) && 
						 (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.MaxCrew"));
					if(ok)
					{
						Link.l1 = "Increase the durability of the hull.";
						Link.l1.go = "ship_tunning_HP";
						Link.l2 = "Increase crew space.";
						Link.l2.go = "ship_tunning_MaxCrew";
						Link.l3 = "Hold on! I changed my mind.";
						Link.l3.go = "ship_tunning_not_now_1";
						break;
					}	
					else
					{
						// belamour legendary edition -->
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.HP"))
						{
							Link.l1 = "Increase the durability of the hull.";
							Link.l1.go = "ship_tunning_HP";
							Link.l2 = "Hold on! I changed my mind.";
							Link.l2.go = "ship_tunning_not_now_1";
							break;
						}
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.MaxCrew"))
						{
							Link.l1 = "Increase crew space.";
							Link.l1.go = "ship_tunning_MaxCrew";
							Link.l2 = "Hold on! I changed my mind.";
							Link.l2.go = "ship_tunning_not_now_1";
							break;	
						}
						Link.l1 = LinkRandPhrase("Oh! My vessel is already improved in this way. Well, thank you for your time!",
						                         "Thank you, master, but I already have an improvement, and it's exactly what you've mentioned to me. Good luck with other ships and their Captains!",
												 "Heh! I take it that my ship had already been refitted before by a previous owner - it must have been at this very shipyard, Well, I guess I must thank him for his foresight, and you and your guys for their excellent work!");
						Link.l1.go = "ship_tunning_not_now_1";	
						// <-- legendary edition
					}
				}
				if(NPChar.city == "Charles")
				{
					ok = (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.TurnRate")) && 
						 (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.MinCrew"));
					if(ok)
					{		
						Link.l1 = "Increase maneurability.";
						Link.l1.go = "ship_tunning_TurnRate";
						if(sti(RealShips[sti(pchar.Ship.Type)].Class) < 5)
						{
							Link.l2 = "Decrease the minimal crew size.";
							Link.l2.go = "ship_tunning_MinCrew";
						}	
						Link.l3 = "Hold on! I changed my mind.";
						Link.l3.go = "ship_tunning_not_now_1";
						break;
					}
					else
					{
						// belamour legendary edition -->
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.TurnRate"))
						{
							Link.l1 = "Increase maneurability.";
							Link.l1.go = "ship_tunning_TurnRate";
							Link.l2 = "Hold on! I changed my mind.";
							Link.l2.go = "ship_tunning_not_now_1";
							break;
						}
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.MinCrew"))
						{
							if(sti(RealShips[sti(pchar.Ship.Type)].Class) < 5)
							{
								Link.l1 = "Decrease the minimal crew size.";
								Link.l1.go = "ship_tunning_MinCrew";
								Link.l2 = "Hold on! I changed my mind.";
								Link.l2.go = "ship_tunning_not_now_1";
								break;
							}	
						}
						// <-- legendary edition				
					}
					Link.l1 = LinkRandPhrase("Oh! My vessel is already improved in this way. Well, thank you for your time!",
						                         "Thank you, master, but I already have an improvement, and it's exactly what you've mentioned to me. Good luck with other ships and their Captains!",
												 "Heh! I take it that my ship had already been refitted before by a previous owner - it must have been at this very shipyard, Well, I guess I must thank him for his foresight, and you and your guys for their excellent work!");
					Link.l1.go = "ship_tunning_not_now_1";	
				}								
			}
			else
			{
				dialog.Text = "Where's the ship? Are you pulling my leg or what?";
			    Link.l1 = "Oh, my bad, indeed... I am sorry.";
			    Link.l1.go = "ship_tunning_not_now_1";
			}			
		break;
		
		////////////////////////////////////////// Capacity ////////////////////////////////////////////////////
		case "ship_tunning_Capacity":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar, 2 );			
			s2 = "Well, let's see what we can do. At the moment the deadweight of your vessel is " + sti(RealShips[sti(pchar.Ship.Type)].Capacity);			
			s2 = s2 + ". For lighter bulkheads I will require: ironwood - " + Material + ".";
			s2 = s2 + " As payment for my work I will take: " + WorkPrice + " chests of doubloons - to cover my expenses. That should be all. Oh, and cash up front.";			
            dialog.Text = s2;
			Link.l1 = "Agreed. I accept your terms. I will bring you whatever you need.";
			Link.l1.go = "ship_tunning_Capacity_start";
			Link.l2 = "No. That doesn't suit me.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_tunning_Capacity_start":
		    amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та еще морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Chests of doubloons were taken from the cabin: " + iSumm+ " pcs.");
				}
				// <-- legendary edtion
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;			    
				NextDiag.TempNode = "ship_tunning_Capacity_again";
                dialog.text = "Excellent. I'll be waiting for the material.";
			    link.l1 = LinkRandPhrase("I assure you that you will not have to wait for long. I can resolve such issues, alright?",
										 "Consider that you already have them and hold the dock for me. I'll be as swift as the wind.",
										 "Of course. I'll just have to visit a couple of persons who have the stuff you requested, ha-ha!");
			    link.l1.go = "Exit";			    
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "For his work to increase the tonnage of " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'"+
				" shipwright requires: ironwood - " + NPChar.Tuning.Matherial + ". A deposit was paid in front in the amount of " + NPChar.Tuning.Money + " chests of doubloons.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "I don't see the deposit...";
				link.l1 = "I'll drop in later.";
				link.l1.go = "Exit";								
			}
		break;
				
		case "ship_tunning_Capacity_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_Capacity_again";
				dialog.Text = "Time goes by, and the ship is waiting. Have you brought everything that I requested?";
			    Link.l1 = "Yes, I managed to find something.";
			    Link.l1.go = "ship_tunning_Capacity_again_2";
			    Link.l2 = "No, I am still on it.";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
			    dialog.Text = "Mis"+ GetSexPhrase("ter","s") +", have you changed your ship since we've made our arrangement? You shouldn't have.";
			    Link.l1 = "Alas, it's all the circumstances! Pity that the deposit was lost...";
			    Link.l1.go = "Exit";
				DeleteAttribute(pchar,"achievment.Tuning");
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_Capacity_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_SANDAL);		
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "Excellent, now I have all I need. I'll start working, then.";
			    link.l1 = "I am waiting.";
			    link.l1.go = "ship_tunning_Capacity_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_Capacity_again";
				dialog.Text = "I still require: ironwood - " + sti(NPChar.Tuning.Matherial) + ".";
				link.l1 = "Fine.";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "I need to bring: ironwood - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;
		
		case "ship_tunning_Capacity_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
			if(!CheckAttribute(shTo, "Bonus_Capacity"))
			{
				shTo.Capacity        = sti(shTo.Capacity) + makeint(sti(shTo.Capacity)/5);
			}
			else
			{
				shTo.Capacity        = makeint((sti(shTo.Capacity) - sti(shTo.Bonus_Capacity)) * 1.2 + sti(shTo.Bonus_Capacity));
			}			
	        shTo.Tuning.Capacity = true;

	        // finish <--
            NextDiag.TempNode = "First time";
			dialog.Text = "...That seems to be all... You can load your hold fully now, I guarantee the quality of my work.";
			Link.l1 = "Thanks! I'll test it.";
			Link.l1.go = "Exit";
			if(!CheckAttribute(pchar, "achievment.Tuning.stage2") && CheckAttribute(shTo,"Tuning.Cannon") && CheckAttribute(shTo,"Tuning.Capacity")) 
			
			{
				pchar.achievment.Tuning.stage2 = true;
			}	
			TuningAvailable();
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
		break;
		
		////////////////////////////////////////// SpeedRate ////////////////////////////////////////////////////
		case "ship_tunning_SpeedRate":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar,  1 );			
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar,  2 );
			s2 = "Let's see what we can do, then. At the moment the speed of your ship is " + stf(RealShips[sti(Pchar.Ship.Type)].SpeedRate);	
			s2 = s2 + " knots. In order to replace the sails I will require: sail silk - "+ Material + ".";
			s2 = s2 + " As payment for my work I will take: " + WorkPrice + " chests of doubloons - to cover my expenses. That should be all. Oh, and cash up front.";						
            dialog.Text = s2;
			Link.l1 = "Agreed. I accept your terms. I will bring you whatever you need.";
			Link.l1.go = "ship_tunning_SpeedRate_start";
			Link.l2 = "No. That doesn't suit me.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
			
		case "ship_tunning_SpeedRate_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та еще морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Chests of doubloons were taken from the cabin: " + iSumm+ " pcs.");
				}
				// <-- legendary edtion	
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 			    
			    NPChar.Tuning.ShipType   	= Pchar.Ship.Type;
			    NPChar.Tuning.ShipName   	= RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_SpeedRate_again";
                dialog.text = "Excellent. I'll be waiting for the material.";
				link.l1 = LinkRandPhrase("I assure you that you will not have to wait for long. I can resolve such issues, alright?",
										 "Consider that you already have them and hold the dock for me. I'll be as swift as the wind.",
										 "Of course. I'll just have to visit a couple of persons who have the stuff you requested, ha-ha!");
			    link.l1.go = "Exit";
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "For his work to increase the speed at " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +
				" shipwright requires: ship silk - " + NPChar.Tuning.Matherial + ". As the deposit was paid for " + NPChar.Tuning.Money + " chests of doubloons.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "I don't see the deposit...";
				link.l1 = "I'll drop in later.";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_SpeedRate_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_SpeedRate_again";
				dialog.Text = "Time goes by, and the ship is waiting. Have you brought everything that I requested?";
			    Link.l1 = "Yes, I managed to find something.";
			    Link.l1.go = "ship_tunning_SpeedRate_again_2";
			    Link.l2 = "No, I am still on it.";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = "Mis"+ GetSexPhrase("ter","s") +", have you changed your ship since we've made our arrangement? You shouldn't have.";
			    Link.l1 = "Alas, it's all the circumstances! Pity that the deposit was lost...";
			    Link.l1.go = "Exit";			    
				DeleteAttribute(pchar,"achievment.Tuning");	
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_SpeedRate_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_SHIPSILK);		    
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "Excellent, now I have all I need. I'll start working, then.";
			    link.l1 = "I am waiting.";
			    link.l1.go = "ship_tunning_SpeedRate_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_SpeedRate_again";
				dialog.Text = "I still require: ship silk - "+ sti(NPChar.Tuning.Matherial) + ".";
				link.l1 = "Fine.";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText",  "I need to bring: ship silk - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;
		
		case "ship_tunning_SpeedRate_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
			if(!CheckAttribute(shTo, "Bonus_SpeedRate"))
			{
					shTo.SpeedRate        = (stf(shTo.SpeedRate) + stf(shTo.SpeedRate)/5.0);
			}
			else
			{
					shTo.SpeedRate        = (stf(shTo.SpeedRate) - stf(shTo.Bonus_SpeedRate)) * 1.2 + stf(shTo.Bonus_SpeedRate);
			}		
	        shTo.Tuning.SpeedRate = true;
			
			if(!CheckAttribute(pchar, "achievment.Tuning.stage1") && CheckAttribute(shTo, "Bonus_SpeedRate") &&  CheckAttribute(shTo,"Tuning.WindAgainst")) 
			{
				pchar.achievment.Tuning.stage1 = true;
			}	
            TuningAvailable();
            NextDiag.TempNode = "First time";
			dialog.Text = "... Everything is ready, Captain. Catch the wind in full sail. Check it out if you'd like to!";
			Link.l1 = "Thanks! I'll test it.";
			Link.l1.go = "Exit";			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
		break;
		
		////////////////////////////////////////// TurnRate ////////////////////////////////////////////////////
		case "ship_tunning_TurnRate":
			Material  = GetMaterialQtyUpgrade(pchar, NPChar, 1 );			
			WorkPrice = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			s2 = "Let's see what we can do, then. At the moment the maneurability of your ship is " + stf(RealShips[sti(Pchar.Ship.Type)].TurnRate);			
			s2 = s2 + " In order to add new sails to shake it up I shall require: ropes - "+ Material + ".";
			s2 = s2 + " As payment for my work I will take: " + WorkPrice + " chests of doubloons - to cover my expenses. That should be all. Oh, and cash up front.";										
            dialog.Text = s2;
			Link.l1 = "Agreed. I accept your terms. I will bring you whatever you need.";
			Link.l1.go = "ship_tunning_TurnRate_start";
			Link.l2 = "No. That doesn't suit me.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_tunning_TurnRate_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та еще морока
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Chests of doubloons were taken from the cabin: " + iSumm+ " pcs.");
				}
				// <-- legendary edtion	
			    NPChar.Tuning.Money  		= amount;
				NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_TurnRate_again";
                dialog.text = "Excellent. I'll be waiting for the material.";
				link.l1 = LinkRandPhrase("I assure you that you will not have to wait for long. I can resolve such issues, alright?",
										 "Consider that you already have them and hold the dock for me. I'll be as swift as the wind.",
										 "Of course. I'll just have to visit a couple of persons who have the stuff you requested, ha-ha!");			    
			    link.l1.go = "Exit";			    
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "For his work to increase agility by " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +
				" shipwright requires: ropes - " + NPChar.Tuning.Matherial + ". A deposit was paid in front in the amount of  " + NPChar.Tuning.Money + " chests of doubloons.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "I don't see the deposit...";
				link.l1 = "I'll drop in later.";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_TurnRate_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_TurnRate_again";
				dialog.Text = "Time goes by, and the ship is waiting. Have you brought everything that I requested?";
			    Link.l1 = "Yes, I managed to deliver something.";
			    Link.l1.go = "ship_tunning_TurnRate_again_2";
			    Link.l2 = "No, I am still on it.";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = "Mis"+ GetSexPhrase("ter","s") +", have you changed your ship since we've made our arrangement? You shouldn't have.";
			    Link.l1 = "Alas, it's all the circumstances! Pity that the deposit was lost...";
			    Link.l1.go = "Exit";			    
				DeleteAttribute(pchar,"achievment.Tuning");	
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_TurnRate_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_ROPES);		
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "Excellent, now I have all I need. I'll start working, then.";
			    link.l1 = "I'm waiting.";
			    link.l1.go = "ship_tunning_TurnRate_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_TurnRate_again";
				dialog.Text = "I still require: ropes - "+ sti(NPChar.Tuning.Matherial) + ".";
				link.l1 = "Fine.";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "I need to bring: ropes - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;
		
		case "ship_tunning_TurnRate_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
			if(!CheckAttribute(shTo, "Bonus_TurnRate"))
			{
				shTo.TurnRate        = (stf(shTo.TurnRate) + stf(shTo.TurnRate)/5.0);
			}
			else
			{
				shTo.TurnRate        = (stf(shTo.TurnRate) - stf(shTo.Bonus_TurnRate)) * 1.2 + stf(shTo.Bonus_TurnRate);
			}	

	        shTo.Tuning.TurnRate = true;
			if(!CheckAttribute(pchar, "achievment.Tuning.stage4") && CheckAttribute(shTo,"Tuning.TurnRate") && CheckAttribute(shTo,"Tuning.MinCrew")) 
			{
				pchar.achievment.Tuning.stage4 = true;
			}	
            TuningAvailable();
			dialog.Text = "... Everything should be ready now... Check the steering wheel now, Captain!";
			Link.l1 = "Thanks! I'll test it.";
			Link.l1.go = "Exit";
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
		break;
		
		////////////////////////////////////////// MaxCrew ////////////////////////////////////////////////////
		case "ship_tunning_MaxCrew":
			Material  = GetMaterialQtyUpgrade(pchar, NPChar, 1 );
			WorkPrice = GetMaterialQtyUpgrade(pchar, NPChar, 2 );				
			s2 = "Let's see what we can do, then. At the moment the maximum number of sailors in your crew, including overloading, is " + sti(RealShips[sti(Pchar.Ship.Type)].MaxCrew) + " men.";			
			s2 = s2 + " I will require: ironwood - "+ Material + ".";
			s2 = s2 + " As payment for my work I will take: " + WorkPrice + " chests of doubloons - to cover my expenses. That should be all. Oh, and cash up front.";									
            dialog.Text = s2;
			Link.l1 = "Agreed. I accept your terms. I will bring you whatever you need.";
			Link.l1.go = "ship_tunning_MaxCrew_start";
			Link.l2 = "No. That doesn't suit me.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_tunning_MaxCrew_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та еще морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Chests of doubloons were taken from the cabin: " + iSumm+ " pcs.");
				}
				// <-- legendary edtion		
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_MaxCrew_again";
                dialog.text = "Excellent. I'll be waiting for the material.";
				link.l1 = LinkRandPhrase("I assure you that you will not have to wait for long. I can resolve such issues, alright?",
										 "Consider that you already have them and hold the dock for me. I'll be as swift as the wind.",
										 "Of course. I'll just have to visit a couple of persons who have the stuff you requested, ha-ha!");
			    link.l1.go = "Exit";			    
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "For their efforts to increase the crew of " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +
				" shipwright requires: ironwood - " + NPChar.Tuning.Matherial + ". A deposit was paid in front in the amount of " + NPChar.Tuning.Money + " chests of doubloons.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "I don't see the deposit...";
				link.l1 = "I'll drop in later.";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_MaxCrew_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName  && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_MaxCrew_again";
				dialog.Text = "Time goes by, and the ship is waiting. Have you brought everything that I requested?";
			    Link.l1 = "Yes, I managed to find something.";
			    Link.l1.go = "ship_tunning_MaxCrew_again_2";
			    Link.l2 = "No, I am still on it.";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = "Mis"+ GetSexPhrase("ter","s") +", have you changed your ship since we've made our arrangement? You shouldn't have.";
			    Link.l1 = "Alas, it's all the circumstances! Pity that the deposit was lost...";				
			    Link.l1.go = "Exit";
				DeleteAttribute(pchar,"achievment.Tuning");
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_MaxCrew_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_SANDAL);		    
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "Excellent, now I have all I need. I'll start working, then.";
			    link.l1 = "I am waiting.";
			    link.l1.go = "ship_tunning_MaxCrew_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_MaxCrew_again";
				dialog.Text = "I still require: ironwood - "+ sti(NPChar.Tuning.Matherial) + ".";
				link.l1 = "Fine.";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "I need to bring: ironwood - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;
		
		case "ship_tunning_MaxCrew_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    
	        shTo.MaxCrew        = sti(shTo.MaxCrew) + makeint(sti(shTo.MaxCrew)/5);
	        shTo.Tuning.MaxCrew = true;
			if(!CheckAttribute(pchar, "achievment.Tuning.stage3") && CheckAttribute(shTo,"Tuning.MaxCrew") && CheckAttribute(shTo,"Tuning.HP")) 
			
			{
				pchar.achievment.Tuning.stage3 = true;
			}	
            TuningAvailable();
            NextDiag.TempNode = "First time";
			dialog.Text = "... It is done, Captain. You can now hire more sailors, there shall be enough room for everyone.";
			Link.l1 = "Thanks! I'll test it.";
			Link.l1.go = "Exit";
			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
		break;

		
		////////////////////////////////////////// MinCrew ////////////////////////////////////////////////////
		case "ship_tunning_MinCrew":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );			
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar, 2 );				
			s2 = "Let's see what we can do, then. At the moment the minimum number of required sailors in your crew is " + sti(RealShips[sti(Pchar.Ship.Type)].MinCrew) + " men.";			
			s2 = s2 + " To improve the controllability of the ship and to reduce the required number of sailors in the crew I will require: ropes - "+ Material + ".";
			s2 = s2 + " As payment for my work I will take: " + WorkPrice + " chests of doubloons - to cover my expenses. That should be all. Oh, and cash up front.";									
            dialog.Text = s2;
			Link.l1 = "Agreed. I accept your terms. I will bring you whatever you need.";
			Link.l1.go = "ship_tunning_MinCrew_start";
			Link.l2 = "No. That doesn't suit me.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_tunning_MinCrew_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та еще морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Chests of doubloons were taken from the cabin: " + iSumm+ " pcs.");
				}
				// <-- legendary edtion		
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_MinCrew_again";
                dialog.text = "Excellent. I'll be waiting for the material.";
				link.l1 = LinkRandPhrase("I assure you that you will not have to wait for long. I can resolve such issues, alright?",
										 "Consider that you already have them and hold the dock for me. I'll be as swift as the wind.",
										 "Of course. I'll just have to visit a couple of persons who have the stuff you requested, ha-ha!");
			    link.l1.go = "Exit";			    
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "For his work to reduce the minimum required number of crew on " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +			
				" shipwright requires: ropes - " + NPChar.Tuning.Matherial + ". A deposit was paid in front in the amount of " + NPChar.Tuning.Money + " chests of doubloons.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "I don't see the deposit...";
				link.l1 = "I'll drop in later.";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_MinCrew_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName  && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_MinCrew_again";
				dialog.Text = "Time goes by, and the ship is waiting. Have you brought everything that I requested?";
			    Link.l1 = "Yes, I managed to find something.";
			    Link.l1.go = "ship_tunning_MinCrew_again_2";
			    Link.l2 = "No, I am still on it.";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = "Mis"+ GetSexPhrase("ter","s") +", have you changed your ship since we've made our arrangement? You shouldn't have.";
			    Link.l1 = "Alas, it's all the circumstances! Pity that the deposit was lost...";
			    Link.l1.go = "Exit";			    
				DeleteAttribute(pchar,"achievment.Tuning");	
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_MinCrew_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_ROPES);		    
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "Excellent, now I have all I need. I'll start working, then.";
			    link.l1 = "I am waiting.";
			    link.l1.go = "ship_tunning_MinCrew_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_MinCrew_again";
				dialog.Text = "I still require: ropes - "+ sti(NPChar.Tuning.Matherial) + ".";
				link.l1 = "Fine.";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "I need to bring: ropes - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;
		
		case "ship_tunning_MinCrew_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
	        shTo.MinCrew        = sti(shTo.MinCrew) - makeint(sti(shTo.MinCrew)/5);
			if(sti(shTo.MinCrew) < 1) shTo.MinCrew = 1;
	        shTo.Tuning.MinCrew = true;
			
			if(!CheckAttribute(pchar, "achievment.Tuning.stage4")  && CheckAttribute(shTo,"Tuning.TurnRate") && CheckAttribute(shTo,"Tuning.MinCrew")) 
			{
				pchar.achievment.Tuning.stage4 = true;
			}	
            TuningAvailable();
            NextDiag.TempNode = "First time";
			dialog.Text = "... Ready, Captain! Now fewer sailors can manage the ship with the same overall result.";
			Link.l1 = "Thanks! I'll test it.";
			Link.l1.go = "Exit";
			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
		break;
		
		////////////////////////////////////////// HP ////////////////////////////////////////////////////
		case "ship_tunning_HP":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar, 2 );			
			s2 = "Let's see what we can do, then. At the moment the ship's hull is " + sti(RealShips[sti(Pchar.Ship.Type)].HP);			
			s2 = s2 + ". To reinforce the hull, I will require: resin - "+ Material + ".";
			s2 = s2 + " As payment for my work I will take: " + WorkPrice + " chests of doubloons - to cover my expenses. That should be all. Oh, and cash up front.";									
            dialog.Text = s2;
			Link.l1 = "Agreed. I accept your terms. I will bring you whatever you need.";
			Link.l1.go = "ship_tunning_HP_start";
			Link.l2 = "No. That doesn't suit me.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_tunning_HP_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та еще морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Chests of doubloons were taken from the cabin: " + iSumm+ " pcs.");
				}
				// <-- legendary edtion		
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_HP_again";
                dialog.text = "Excellent. I'll be waiting for the material.";
				link.l1 = LinkRandPhrase("I assure you that you will not have to wait for long. I can resolve such issues, alright?",
										 "Consider that you already have them and hold the dock for me. I'll be as swift as the wind.",
										 "Of course. I'll just have to visit a couple of persons who have the stuff you requested, ha-ha!");
			    link.l1.go = "Exit";
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "For his efforts to increase the strength of the hull " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +			
				" shipwright requires: resin - " + NPChar.Tuning.Matherial + ". A deposit was paid in front in the amount of " + NPChar.Tuning.Money + " chests of doubloons.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "I don't see the deposit...";
				link.l1 = "I'll drop in later.";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_HP_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_HP_again";
				dialog.Text = "Time goes by, and the ship is waiting. Have you brought everything that I requested?";
			    Link.l1 = "Yes, I managed to find something.";
			    Link.l1.go = "ship_tunning_HP_again_2";
			    Link.l2 = "No, I am still on it.";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = "Mis"+ GetSexPhrase("ter","s") +", have you changed your ship since we've made our arrangement? You shouldn't have.";
			    Link.l1 = "Alas, it's all the circumstances! Pity that the deposit was lost...";
			    Link.l1.go = "Exit";			    
				DeleteAttribute(pchar,"achievment.Tuning");	
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_HP_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_OIL);		
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "Excellent, now I have all I need. I'll start working, then.";
			    link.l1 = "I am waiting.";
			    link.l1.go = "ship_tunning_HP_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_HP_again";
				dialog.Text = "I still require: resin - "+ sti(NPChar.Tuning.Matherial) + ".";
				link.l1 = "Fine.";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "I need to bring: resin - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;
		
		case "ship_tunning_HP_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
			if(!CheckAttribute(shTo, "Bonus_HP"))
			{
				shTo.HP        = sti(shTo.HP) + makeint(sti(shTo.HP)/5);
			}
			else
			{
				shTo.HP        = makeint((sti(shTo.HP) - sti(shTo.Bonus_HP)) * 1.2 + sti(shTo.Bonus_HP));
			}	
	        shTo.Tuning.HP = true;
			shTo.BaseHP = sti(shTo.HP);

			if(!CheckAttribute(pchar, "achievment.Tuning.stage3") && CheckAttribute(shTo,"Tuning.MaxCrew") && CheckAttribute(shTo,"Tuning.HP")) 
			{
				pchar.achievment.Tuning.stage3 = true;
			}	
			TuningAvailable();
            NextDiag.TempNode = "First time";
			
			dialog.Text = "... That should do it... I guarantee that from now on your enemies will have a much harder time tearing your ship's hull to pieces!";
			Link.l1 = "Heh, I'll take your word for it! Thank you, master.";
			Link.l1.go = "Exit";
			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
		break;
		
		////////////////////////////////////////// WindAgainst ////////////////////////////////////////////////////
		case "ship_tunning_WindAgainst":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			fTmp = 180.0 - (stf(RealShips[sti(Pchar.Ship.Type)].WindAgainstSpeed) * 90.0);
			s2 = "Let's see what we can do, then. At the moment the point of sail by the wind is " + makeint(fTmp) + " degrees.";
			// belamour legendary edition если спускать курс по ветру, то это даунгрейд
			s2 = s2 + " To accelerate the ship upwind, I will require: ship silk - "+ Material + ",";
			s2 = s2 + " As payment for my work I will take: " + WorkPrice + " chests of doubloons - to cover my expenses. That should be all. Oh, and cash up front.";									
            dialog.Text = s2;
			Link.l1 = "Agreed. I accept your terms. I will bring you whatever you need.";
			Link.l1.go = "ship_tunning_WindAgainst_start";
			Link.l2 = "No. That doesn't suit me.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;

		case "ship_tunning_WindAgainst_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та еще морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Chests of doubloons were taken from the cabin: " + iSumm+ " pcs.");
				}
				// <-- legendary edtion		
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial    	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_WindAgainst_again";
                dialog.text = "Excellent. I'll be waiting for the material.";
				link.l1 = LinkRandPhrase("I assure you that you will not have to wait for long. I can resolve such issues, alright?",
										 "Consider that you already have them and hold the dock for me. I'll be as swift as the wind.",
										 "Of course. I'll just have to visit a couple of persons who have the stuff you requested, ha-ha!");
			    link.l1.go = "Exit";

			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "For his work on changing the wind angle of " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +			
				" shipwright requires: ship silk - " + NPChar.Tuning.Matherial + ". A deposit was paid in front in the amount of " + NPChar.Tuning.Money + " chests of doubloons.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "I don't see the deposit...";
				link.l1 = "I'll drop in later.";
				link.l1.go = "Exit";
			}
		break;

		case "ship_tunning_WindAgainst_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName  && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_WindAgainst_again";
			    dialog.Text = "Time goes by, and the ship is waiting. Have you brought everything that I requested?";
			    Link.l1 = "Yes, I managed to deliver something.";
			    Link.l1.go = "ship_tunning_WindAgainst_again_2";
			    Link.l2 = "No, I am still on it.";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = "Mis"+ GetSexPhrase("ter","s") +", have you changed your ship since we've made our arrangement? You shouldn't have.";
			    Link.l1 = "Alas, it's all the circumstances! Pity that the deposit was lost...";
			    Link.l1.go = "Exit";
				DeleteAttribute(pchar,"achievment.Tuning");
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;

		case "ship_tunning_WindAgainst_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_SHIPSILK);
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "Excellent, now I have all I need. I'll start working, then.";
			    link.l1 = "I am waiting.";
			    link.l1.go = "ship_tunning_WindAgainst_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_WindAgainst_again";
                dialog.Text = "I still require: ship silk - "+ sti(NPChar.Tuning.Matherial) + ".";
				link.l1 = "Fine.";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "I need to bring: ship silk - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;

		case "ship_tunning_WindAgainst_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим			
			// belamour legendary edtion чем больше WindAgainstSpeed, тем круче к ветру
	        shTo.WindAgainstSpeed   = stf(shTo.WindAgainstSpeed) + 0.20 * stf(shTo.WindAgainstSpeed);	
			if (stf(shTo.WindAgainstSpeed) > 1.985) shTo.WindAgainstSpeed = 1.985;
	        shTo.Tuning.WindAgainst = true;

			if(!CheckAttribute(pchar, "achievment.Tuning.stage1") && CheckAttribute(shTo, "Bonus_SpeedRate") &&  CheckAttribute(shTo,"Tuning.WindAgainst")) 
			{
				pchar.achievment.Tuning.stage1 = true;
			}	
            TuningAvailable();
            NextDiag.TempNode = "First time";
			dialog.Text = "... Ready, Captain!.. Your ship will sail upwind much quicker now.";
			Link.l1 = "Thanks! I'll test it.";
			Link.l1.go = "Exit";

			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
		break;
						
		////////////////////////////////////////// только количество орудий  ////////////////////////////////////////////////////	
		case "ship_c_quantity":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );			
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar, 2 );			
			s2 = "Let's see what can be done there. Right now, the number of cannons on your ship is " + sti(RealShips[sti(Pchar.Ship.Type)].CannonsQuantity) + ", and the maximum possible number is - " + sti(RealShips[sti(Pchar.Ship.Type)].CannonsQuantityMax) + ".";			
			s2 = s2 + " I can tell you right away that it's not going to be cheap. I will require: resin - "+ Material + ",";
			s2 = s2 + " As payment for my work I will take: " + WorkPrice + " chests of doubloons - to cover my expenses. That should be all. Oh, and cash up front.";						
			dialog.Text = s2;		
			Link.l1 = "Agreed. I accept your terms. I will bring you whatever you need.";
			Link.l1.go = "ship_c_quantity_start";		
			Link.l2 = "No. That doesn't suit me.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_c_quantity_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та еще морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Chests of doubloons were taken from the cabin: " + iSumm+ " pcs.");
				}
				// <-- legendary edtion		
			    NPChar.Tuning.Money  		= amount;
				NPChar.Tuning.Cannon 		= true;				
				NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 				
				NPChar.Tuning.ShipType      = Pchar.Ship.Type;
				NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;											    
				NextDiag.TempNode = "ship_c_quantity_again";
				dialog.text = "Excellent. I'll be waiting for the material.";
				link.l1 = LinkRandPhrase("I assure you that you will not have to wait for long. I can resolve such issues, alright?",
										 "Consider that you already have them and hold the dock for me. I'll be as swift as the wind.",
										 "Of course. I'll just have to visit a couple of persons who have the stuff you requested, ha-ha!");
				link.l1.go = "Exit";			    
				ReOpenQuestHeader("ShipTuning");
				AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "For his work to increase the number of cannons on the " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +						
				" shipwright requires: resin - " + NPChar.Tuning.Matherial + ". A deposit was paid in front in the amount of " + NPChar.Tuning.Money + " chests of doubloons.");				
			}		
			else
			{ 
				NextDiag.TempNode = "ship_tunning_not_now_1";
				dialog.text = "I don't see the deposit...";
				link.l1 = "I'll drop in later.";
				link.l1.go = "Exit";
			}
		break;		
		
		case "ship_c_quantity_again":	
			if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName && TuningAvailable())
			{
				NextDiag.TempNode = "ship_c_quantity_again";
				dialog.Text = "Time goes by, and the ship is waiting. Have you brought everything that I requested?";
				Link.l1 = "Yes, I managed to find something.";
				Link.l1.go = "ship_c_quantity_again_2";
				Link.l2 = "No, I am still on it.";
				Link.l2.go = "Exit";
			}		
			else
			{
				DeleteAttribute(NPChar, "Tuning");
				NextDiag.TempNode = "First time";
				dialog.Text = "Mis"+ GetSexPhrase("ter","s") +", have you changed your ship since we've made our arrangement? You shouldn't have.";
			    Link.l1 = "Alas, it's all the circumstances! Pity that the deposit was lost...";
				Link.l1.go = "Exit";
				DeleteAttribute(pchar,"achievment.Tuning");
				AddQuestRecord("ShipTuning", "Lose");
				CloseQuestHeader("ShipTuning");
			}		
		break;
		
		case "ship_c_quantity_again_2":		
			checkMatherial(Pchar, NPChar, GOOD_OIL);
			if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
				NextDiag.TempNode = "First time";
				dialog.text = "Excellent, now I have all I need. I'll start working, then.";
				link.l1 = "I am waiting.";
				link.l1.go = "ship_c_quantity_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_c_quantity_again";
				dialog.Text = "I still require: resin - "+ sti(NPChar.Tuning.Matherial) + ".";
				link.l1 = "Fine.";
				link.l1.go = "Exit";
				AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "I need to bring: resin - "+ sti(NPChar.Tuning.Matherial) + ".");
			}		
		break;
		
		case "ship_c_quantity_complite":
			AddTimeToCurrent(6, 30);
			shTo = &RealShips[sti(Pchar.Ship.Type)];
			DeleteAttribute(NPChar, "Tuning");		
			makearef(refShip, pchar.Ship);
			
			iCannonDiff = sti(refShip.CannonDiff);
			iCannonDiff -= 1;
								
			for (i = 0; i < sti(shTo.cannonr); i++)
			{
				attr = "c" + i;										
					
				if(i < (sti(shTo.cannonr) - iCannonDiff) )	
				{
					if( stf(refShip.Cannons.Borts.cannonr.damages.(attr)) > 1.0 )
					{
						refShip.Cannons.Borts.cannonr.damages.(attr) = 1.0; 
					}	
				}					
			}	
			for (i = 0; i < sti(shTo.cannonl); i++)
			{
				attr = "c" + i;
				if(i < (sti(shTo.cannonl) - iCannonDiff) )	
				{
					if( stf(refShip.Cannons.Borts.cannonl.damages.(attr)) > 1.0 )
					{
						refShip.Cannons.Borts.cannonl.damages.(attr) = 1.0; 
					}	
				}										
			}	
			
			if(CheckAttribute(shTo,"CannonsQuantityMax")) 	shTo.Cannons = sti(shTo.CannonsQuantityMax) - iCannonDiff * 2;
			else										    shTo.Cannons = sti(shTo.CannonsQuantity) - iCannonDiff * 2;
			
			shTo.CannonsQuantity = sti(shTo.Cannons);
		
			refShip.Cannons = sti(shTo.Cannons);
			refShip.CannonDiff = iCannonDiff;			

			shTo.Tuning.Cannon = true;
			
			if(!CheckAttribute(pchar, "achievment.Tuning.stage2") && CheckAttribute(shTo,"Tuning.Cannon") && CheckAttribute(shTo,"Tuning.Capacity")) 
			{
				pchar.achievment.Tuning.stage2 = true;
			}	
			TuningAvailable();
			NextDiag.TempNode = "First time";
			dialog.Text = "... That's it, Captain. You can use additional cannons - that is, if you have them, he-he.";
			Link.l1 = "Thanks!";
			Link.l1.go = "Exit";
			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
		break;
		
		case "Tasks":
			//--> Jason генератор Поиск корабля
			if (drand(4) == 2 && !CheckAttribute(pchar, "GenQuest.Findship.Shipyarder") && sti(pchar.rank) < 19)
			{
				if (!CheckAttribute(npchar, "Findship") || GetNpcQuestPastDayParam(npchar, "Findship") >= 60) 
				{
					SelectFindship_ShipType(); //выбор типа корабля
					pchar.GenQuest.Findship.Shipyarder.ShipBaseName =  GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Findship.Shipyarder.ShipType), "Name") + "Acc")); // new
					pchar.GenQuest.Findship.Shipyarder.City = npchar.city; //город квестодателя
					dialog.text = "I have an issue that needs to be resolved. I have an order for a ship - "+pchar.GenQuest.Findship.Shipyarder.ShipBaseName+". However, in my yard there's no such ship now and within two months I also have no possibility to get one.\nIf you can give me such a ship - I will be very grateful, and will pay you the sum of one and a half times greater than its selling price.";
					link.l1 = "An interesting offer. I agree!";
					link.l1.go = "Findship";
					link.l2 = "This is not interested to me.";
					link.l2.go = "Findship_exit";
					SaveCurrentNpcQuestDateParam(npchar, "Findship");
					break;
				}
				
			}//<-- генератор Поиск корабля
			//Jason --> генератор Неудачливый вор
			if (drand(6) == 1 && !CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && sti(pchar.rank) < 10 && npchar.city != "Charles")
			{
				if (!CheckAttribute(npchar, "Device")) 
				{
					switch (crand(4))
					{
						case 0:  
							pchar.GenQuest.Device.Shipyarder.Type = "inside gage";
							pchar.GenQuest.Device.Shipyarder.Describe = "two hammered strips, connected with a joint unriveted on both ends";
						break; 
						case 1:  
							pchar.GenQuest.Device.Shipyarder.Type = "Swedish broad axe";
							pchar.GenQuest.Device.Shipyarder.Describe = "an axe on a long straight handle with a thin semicircular blade";
						break; 
						case 2:  
							pchar.GenQuest.Device.Shipyarder.Type = "groover";
							pchar.GenQuest.Device.Shipyarder.Describe = "a small axe, looking like a farmer's mattock";
						break; 
						case 3:  
							pchar.GenQuest.Device.Shipyarder.Type = "stockpile level";
							pchar.GenQuest.Device.Shipyarder.Describe = "two wooden bars of equal length, linked by the same third one, which has in the middle a rotating liquid-filled plate with an air bubble";
						break;
						case 4:  
							pchar.GenQuest.Device.Shipyarder.Type = "barsik";
							pchar.GenQuest.Device.Shipyarder.Describe = "an ordinary flail, but the chain is rod-shaped and only moves in one direction";
						break; 
					}
					dialog.text = "You're just in time. Perhaps, you'd be able to help me. Someone stole from me a very valuable instrument just yesterday - "+pchar.GenQuest.Device.Shipyarder.Type+". I don't have the possibility to make another one and can't afford the time or cost to order it from Europe. And without it I can not normally build ships, you know?\nAnd the most annoying part - this thing isn't needed by anyone except shipbuilders, and I am the only shipbuilder in the colony. This thief will not sell it to anyone and just throw it away. Maybe you'll try to track down the thief, ask around in the town, but I simply have no time to be away from the shipyard - I urgently need to complete special orders.";
					link.l1 = "Alright, I'll give it a try. Tell me, how did that... device of yours look like?";
					link.l1.go = "Device";
					link.l2 = "This is of no interest to me.";
					link.l2.go = "Device_exit";
					SaveCurrentNpcQuestDateParam(npchar, "Device");
					break;
				}//<-- генератор Неудачливый вор
			}
			dialog.text = "I don't have anything of that kind.";
			link.l1 = "As you say.";
			link.l1.go = "exit";
		break;
		
		case "Findship_exit":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Findship.Shipyarder");
		break;
		
		case "Device_exit":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
		break;
		
		//--> Jason генератор Поиск корабля
		case "Findship":
			pchar.GenQuest.Findship.Shipyarder = "begin";
			pchar.GenQuest.Findship.Shipyarder.Name = GetFullName(npchar);
			pchar.GenQuest.Findship.Shipyarder.City = npchar.city;
			ReOpenQuestHeader("Findship");
			AddQuestRecord("Findship", "1");
			AddQuestUserData("Findship", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Findship.Shipyarder.City+"Gen"));
			AddQuestUserData("Findship", "sName", pchar.GenQuest.Findship.Shipyarder.Name);
			AddQuestUserData("Findship", "sShip", pchar.GenQuest.Findship.Shipyarder.ShipBaseName);
			SetFunctionTimerCondition("Findship_Over", 0, 0, 60, false);
			DialogExit();
		break;
		
		case "Findship_check":
			dialog.text = "Excellent! I am very glad that you managed so quickly. Where is that ship?";
			link.l1 = "At the moment the vessel is at the roadstead; her name is '"+pchar.GenQuest.Findship.Shipyarder.ShipName+"'.";
				link.l1.go = "Findship_complete";
				break;
		
		case "Findship_complete":
			pchar.quest.Findship_Over.over = "yes";//снять прерывание
			sld = GetCharacter(sti(pchar.GenQuest.Findship.Shipyarder.CompanionIndex));
			RemoveCharacterCompanion(PChar, sld);
			AddPassenger(PChar, sld, false);
			dialog.text = "Here is your money - "+FindRussianMoneyString(sti(pchar.GenQuest.Findship.Shipyarder.Money))+". Thank you for the job. Don't forget to come see me again. Goodbye!";
			link.l1 = "Goodbye, " + npchar.name + ".";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Findship.Shipyarder.Money));
			AddQuestRecord("Findship", "3");
			AddQuestUserData("Findship", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Findship.Shipyarder.Money)));
			CloseQuestHeader("Findship");
			DeleteAttribute(pchar, "GenQuest.Findship.Shipyarder");
		break;
		//<-- генератор Поиск корабля
		
		//Jason --> генератор Неудачливый вор
		case "Device":
			pchar.GenQuest.Device.Shipyarder.Chance1 = rand(6);
			pchar.GenQuest.Device.Shipyarder.Chance2 = rand(3);
			pchar.GenQuest.Device.Shipyarder.Chance3 = rand(2);
			pchar.GenQuest.Device.Shipyarder.Chance4 = rand(4);
			pchar.GenQuest.Device.Shipyarder.Money = 12000+rand(8000);
			//генерируем тип корабля для бонуса сейчас, чтобы не сливали
			if (sti(pchar.rank) < 2) iType = SHIP_SCHOONER; 
			if (sti(pchar.rank) >= 2 && sti(pchar.rank) < 5) iType = SHIP_BRIGANTINE; 
			if (sti(pchar.rank) >= 5 && sti(pchar.rank) < 7) iType = SHIP_BRIG; 
			if (sti(pchar.rank) >= 7) iType = SHIP_CORVETTE + rand(makeint(SHIP_GALEON_H - SHIP_CORVETTE)); 
			pchar.GenQuest.Device.Shipyarder.Bonus = iType;
			dialog.text = "Of course, I'll try to explain it in simple words. It looks like "+pchar.GenQuest.Device.Shipyarder.Describe+". It's one of its kind, so you will recognize it very easily. If you bring that instrument to me, I will pay you handsomely.";
			link.l1 = "Got it. I shall begin my search immediately!";
			link.l1.go = "exit";
			pchar.GenQuest.Device.Shipyarder = "begin";
			pchar.GenQuest.Device.Shipyarder.Name = GetFullName(npchar);
			pchar.GenQuest.Device.Shipyarder.City = npchar.city;
			pchar.GenQuest.Device.Shipyarder.Nation = npchar.Nation;
			ReOpenQuestHeader("Device");
			AddQuestRecord("Device", "1");
			AddQuestUserData("Device", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Device.Shipyarder.City+"Voc"));
			AddQuestUserData("Device", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Device", "sName", pchar.GenQuest.Device.Shipyarder.Type);
			AddQuestUserData("Device", "sDesc", pchar.GenQuest.Device.Shipyarder.Describe);
			SetFunctionTimerCondition("Device_Over", 0, 0, 30, false);
		break;
		
		case "Device_complete":
			pchar.quest.Device_Over.over = "yes";//снять прерывание
			dialog.text = "You've done it! You have no idea how grateful I am! I've already lost every hope to see my instrument again.";
			link.l1 = "Here you go.";
			link.l1.go = "Device_complete_1";
		break;
		
		case "Device_complete_1":
			RemoveItems(PChar, "Tool", 1);
			dialog.text = "For your efforts I will pay you "+FindRussianMoneyString(sti(pchar.GenQuest.Device.Shipyarder.Money))+". I hope that would be a deserving reward.";
			link.l1 = "Thanks!";
			link.l1.go = "Device_complete_2";
		break;
		
		case "Device_complete_2":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Device.Shipyarder.Money));
			ChangeCharacterComplexReputation(pchar,"nobility", 5); 
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			AddQuestRecord("Device", "10");
			AddQuestUserData("Device", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Device.Shipyarder.Money)));
			CloseQuestHeader("Device");
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance4) == 3)
			{
				dialog.text = "Besides, I'd like to make you an offer, as an additional gratitude.";
				link.l1 = "That's interesting. Well, go ahead - I like pleasant surprises.";
				link.l1.go = "Device_complete_3";
			}
			else
			{
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
			}
		break;
		
		case "Device_complete_3":
			iType = sti(pchar.GenQuest.Device.Shipyarder.Bonus);
			dialog.text = "I've just launched a new ship - "+ GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(iType, "Name") + "Acc")) +". There are already several customers for this ship, but I'll give you a priority. If you like this ship, and not frightened by the price - you can buy it.";
			link.l1 = "Heh! Sure, let's take a look!";
			link.l1.go = "Device_complete_4";
			link.l2 = "Thank you, but my current ship suits me just fine, and I am not looking to replace it.";
			link.l2.go = "Device_complete_5";
		break;
		
		case "Device_complete_4":
			iType = sti(pchar.GenQuest.Device.Shipyarder.Bonus);
			FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_TARTANE, NPChar), "ship1");
			FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_LUGGER, NPChar), "ship2");
			FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_LUGGER, NPChar), "ship3");
			FillShipParamShipyard(NPChar, GenerateStoreShipExt(iType, NPChar), "ship10");
			DialogExit();
			LaunchShipyard(npchar);
			DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
			SaveCurrentNpcQuestDateParam(npchar, "shipyardDate"); // лесник , митрокоста		   
		break;
		
		case "Device_complete_5":
			dialog.text = "Well, as you wish. Thank you once again - and good luck!";
			link.l1 = "Good luck to you, too!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
		break;
		// <-- генератор Неудачливый вор
		
		case "ShipLetters_6":
			pchar.questTemp.different.GiveShipLetters.speakShipyard = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Let me take a look... No, there wasn't anyone like him. I guess you should see the harbor master regarding that matter.";
				link.l1 = "Of course...";
				link.l1.go = "exit";
			}
			else
			{
				sTemp = "Let me take a look, Captain! A-ha! Those are the ship documents of a good friend of mine, my favorite customer! I am sure he will be extremely happy because of your find and will reward you deservedly.";
				sTemp = sTemp + "I guess I can offer you " + sti(pchar.questTemp.different.GiveShipLetters.price2) + " pesos on his behalf";
				dialog.text = sTemp;
				link.l1	= "No, I don't think so...";
				link.l1.go = "exit";
				link.l2 = "Thank you, " + GetFullName(NPChar) + "! Please convey my respects to your friend.";
				link.l2.go = "ShipLetters_7";				
			}	
		break;

		case "ShipLetters_7":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2)); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "4");		
			AddQuestUserData("GiveShipLetters", "sSex", GetSexPhrase("",""));		
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters"); 		
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "EncGirl_1":
			dialog.text = "I listen to you carefully.";
			link.l1 = "I brought your fugitive.";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "Oh, Captain, thank you so much! How is she? Is she hurt? Why did she run away? Why?\nDoesn't she understand? The groom is a wealthy and important man! Youth is naive and foolish... cruel even. Remember that!";
			link.l1 = "Well, you are her father and the final decision is yours, but I would not hurry with the wedding...";
			link.l1.go = "EncGirl_3";
		break;
		
		case "EncGirl_3":
			dialog.text = "What do you know? Do you have your own children? No? When you've got one, come to see me and we will talk.\nI promised a reward to anyone who'd take her back to the family.";
			link.l1 = "Thanks. You should keep an eye on her. I have a hunch that she won't stop at that.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;		
		
		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "Oh, so you are that Captain who's brought my prodigal son a young bride?";
				link.l1 = "Yes, it was me.";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "Oh, there "+ GetSexPhrase("he is, our benefactor","she is, our benefactress") +". Expecting a reward, I take it?";
				link.l1 = "Well, I'm fine without a reward, your good word would do just fine.";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "I am very grateful to you that you haven't abandoned my child in dire straits and helped him to find a way out of a delicate situation. Allow me to thank you and, please, accept this modest sum and a gift from me personally.";
			link.l1 = "Thanks. Helping out this young couple was my pleasure.";
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = "Thanks? What thanks?! It's been a half a year since that blockhead has been hanging around without a job - and look at him, he's got enough time for love affairs! When I was his age, I was already running my own business! Pff! A Governor has a marriageable daughter - and that dunce has brought a slut without kith or kin to my house and dared to ask for my blessing!";
			link.l1 = "Hmm... Apparently, you don't believe in sincere feelings?";
			link.l1.go = "EncGirl_6_1";		
		break;
		
		case "EncGirl_5_1":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.EncGirl.sum));
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item);
			AddQuestRecord("JungleGirl", "18");
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "EncGirl_6_1":
			dialog.text = "What feelings? What kind of feelings are you talking about? Feelings... how can one be so light-minded at your age?! Shame on you to indulge the young in their caprices and act as a procurer! You not only have taken a girl from her home, but you also ruined my greenhorn's life. There will be no thanks to you. Farewell.";
			link.l1 = "Alright, and all the same to you...";
			link.l1.go = "EncGirl_6_2";
		break;
		
		case "EncGirl_6_2":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddQuestRecord("JungleGirl", "19");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("",""));
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();		
		break;
		
		case "shipyard":
			if(CheckAttribute(npchar, "TrialDelQuestMark"))
			{
				DeleteAttribute(npchar, "TrialDelQuestMark");
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("PortRoyal");
			}
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		    if (sti(Pchar.Ship.Type) == SHIP_NOTUSED || ok)
			{
			    NextDiag.CurrentNode = NextDiag.TempNode;
				DialogExit();
				LaunchShipyard(npchar);
			}
			else
			{
			    dialog.text = NPCharRepPhrase(npchar, pcharrepphrase("Are you kidding me? Where is your ship? I don't see her in the port!",
				                                                     "I swear to devil, you will not trick me! Your ship is not in the port!"),
													  pcharrepphrase("I don't see your ship in the port, Captain " +GetFullName(pchar)+ ". I do hope she is not the 'Flying Dutchman'?",
													                 "Captain, it's much easier to load the cargo from the pier. Bring your ship to the port and come back."));
				link.l1 = NPCharRepPhrase(npchar, pcharrepphrase("" +RandSwear()+"What a trouble! Alright, old slyboots, see you soon!",
				                                                 "I did not want to deceive you, " +GetFullName(npchar)+ ", a ship on the other side of the island."),
												  pcharrepphrase("No. My ship is called the 'Black Pearl'! What happened to your face? It's pale... Haha! Joke!",
												                 "Thanks for the advice, I'll be sure to do it."));
			    link.l1.go = "exit";
			}
		break;
		
		case "Cannons":
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
			    NextDiag.CurrentNode = NextDiag.TempNode;
				DialogExit();
    			LaunchCannons(sti(rColony.StoreNum));
			}
			else
			{
			    dialog.text = NPCharRepPhrase(npchar, pcharrepphrase("Are you kidding me? Where is your ship? I don't see her in the port!",
				                                                     "I swear to devil, you will not trick me! Your ship is not in the port!"),
													  pcharrepphrase("I don't see your ship in the port, Captain " +GetFullName(pchar)+ ". I do hope she is not the 'Flying Dutchman'?",
													                 "Captain, it's much easier to load the cargo from the pier. Bring your ship to the port and come back."));
				link.l1 = NPCharRepPhrase(npchar, pcharrepphrase("" +RandSwear()+"What a trouble! Alright, old slyboots, see you soon!",
				                                                 "I did not want to deceive you, " +GetFullName(npchar)+ ", a ship on the other side of the island."),
												  pcharrepphrase("No. My ship is called the 'Black Pearl'! What happened to your face? It's pale... Haha! Joke!",
												                 "Thanks for the advice, I'll be sure to do it."));
			    link.l1.go = "exit";
			}
		break;
		
		case "SailsGerald":
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
			    dialog.text = "Changing the color of the sails costs " +
				              FindRussianMoneyString(GetSailsTuningPrice(Pchar, npchar, SAILSCOLOR_PRICE_RATE))+
							  ", changing the coat of arms costs " +
							  FindRussianMoneyString(GetSailsTuningPrice(Pchar, npchar, SAILSGERALD_PRICE_RATE)) +
							  ", replacing the sails - depends on your ship.";
							  
			    link.l1 = "Choose a new color.";
			    link.l1.go = "SailsColorChoose";
			    link.l2 = "Depict a new coat of arms.";
			    link.l2.go = "SailsGeraldChoose";
				link.l3 = "Install unique sails."; 
				link.l3.go = "SailsTypeChoose";
			    Link.l9 = "I've changed my mind.";
				Link.l9.go = "exit";
			}
			else
			{
			    dialog.text = NPCharRepPhrase(npchar, pcharrepphrase("Are you kidding me? Where is your ship? I don't see her in the port!","I swear to devil, you will not trick me! Your ship is not in the port!"),pcharrepphrase("I don't see your ship in the port, Captain " +GetFullName(pchar)+ ". I do hope she is not the 'Flying Dutchman'?","Captain, it's much easier to load the cargo from the pier. Bring your ship to the port and come back."));
				link.l1 = NPCharRepPhrase(npchar, pcharrepphrase("" +RandSwear()+"What a trouble! Alright, old slyboots, see you soon!","I did not want to deceive you, " +GetFullName(npchar)+ ", a ship on the other side of the island."), pcharrepphrase("No. My ship is called the 'Black Pearl'! What happened to your face? It's pale... Haha! Joke!","Thanks for the advice, I'll be sure to do it."));
			    link.l1.go = "exit";
			}
		break;
		
		case "SailsTypeChoose":
			dialog.text = "What sails do you want to install? At the moment you have " + GetSailsType(sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails))+".";
            Link.l6 = "I want to install "+GetSailsType(6) + ".";
			Link.l6.go = "SailsTypeChooseIDX_6";
			Link.l7 = "I want to install "+GetSailsType(7)  + ".";
			Link.l7.go = "SailsTypeChooseIDX_7";
			Link.l8 = "I want to install "+GetSailsType(8)  + ".";
			Link.l8.go = "SailsTypeChooseIDX_8";
			Link.l9 = "I want to install "+GetSailsType(9)  + ".";
			Link.l9.go = "SailsTypeChooseIDX_9";
			Link.l10 = "I want to install "+GetSailsType(10)  + ".";
			Link.l10.go = "SailsTypeChooseIDX_10";
			Link.l11 = "I want to install "+GetSailsType(11)  + ".";
			Link.l11.go = "SailsTypeChooseIDX_11";
			attrLoc = "l" + sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails);
			DeleteAttribute(Link, attrLoc);
		    Link.l99 = "I've changed my mind.";
			Link.l99.go = "exit";
		break;
		
		case "SailsTypeChoose2":
            NPChar.SailsTypeMoney = GetSailsTypePrice(sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails),
			                                          sti(NPChar.SailsTypeChooseIDX),
													  stf(NPChar.ShipCostRate),
													  sti(RealShips[sti(Pchar.Ship.Type)].Price));
													  
			dialog.text = "At the moment you have "+GetSailsType(sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails))+", you have selected "+ GetSailsType(sti(NPChar.SailsTypeChooseIDX))+". The cost of the replacement is "+ FindRussianMoneyString(sti(NPChar.SailsTypeMoney)) +". Proceed?";

			if (sti(NPChar.SailsTypeMoney) <= sti(Pchar.Money))
			{
	            Link.l1 = "Yes.";
				Link.l1.go = "SailsTypeChooseDone";
			}
		    Link.l99 = "No.";
			Link.l99.go = "exit";
		break;
		
		case "SailsTypeChooseDone":
			AddMoneyToCharacter(Pchar, -sti(NPChar.SailsTypeMoney));
			dialog.text = "Excellent! Everything will be just fine.";
		    Link.l9 = "Thanks.";
			Link.l9.go = "exit";

			RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails = sti(NPChar.SailsTypeChooseIDX);
			WaitDate("",0,0,0, 1, 30);
		break;
		
		case "SailsColorChoose":
			if (GetSailsTuningPrice(Pchar, npchar, SAILSCOLOR_PRICE_RATE) <= sti(Pchar.Money))
			{
				dialog.text = "What color shall we choose? The price is " + FindRussianMoneyString(GetSailsTuningPrice(Pchar, npchar, SAILSCOLOR_PRICE_RATE)) + ".";
				for (i = 0; i < SAILS_COLOR_QUANTITY; i++)
				{
					if (CheckSailsColor(Pchar, i))
					{
						attrLoc = "l" + i;
						Link.(attrLoc) = XI_ConvertString(SailsColors[i].name);
						Link.(attrLoc).go = "SailsColorIdx_" + i;
					}
				}
			    Link.l99 = "I've changed my mind.";
				Link.l99.go = "exit";
			}
			else
			{
				dialog.text = "Come when you have the money.";
			    Link.l9 = "Fine.";
				Link.l9.go = "exit";	
			}
		break;
		
		case "SailsColorDone":
			AddMoneyToCharacter(Pchar, -GetSailsTuningPrice(Pchar, npchar, SAILSCOLOR_PRICE_RATE));
			dialog.text = "Agreed. We'll paint the sails in "+ GetStrSmallRegister(XI_ConvertString(SailsColors[sti(NPChar.SailsColorIdx)].name)) +" color.";
		    Link.l9 = "Thanks.";
			Link.l9.go = "exit";
			
			SetSailsColor(Pchar, sti(NPChar.SailsColorIdx));
			WaitDate("",0,0,0, 1, 30);
		break;
		
		case "SailsGeraldChoose":
			if(GetSailsTuningPrice(Pchar, npchar, SAILSGERALD_PRICE_RATE) <= sti(Pchar.Money))
			{
				if(CheckSailsGerald(Pchar) && CanSetSailsGerald(PChar)) // Warship fix 04.06.09
				{
					NextDiag.CurrentNode = NextDiag.TempNode;
					DialogExit();
					LaunchSailsGeraldScreen(npchar);
				}
				else
				{
				    dialog.text = "Unfortunately, your ship cannot bear a coat of arms.";
				    Link.l9 = "Pity.";
					Link.l9.go = "exit";
				}
			}
			else
			{
				dialog.text = "Come back when you have the money.";
			    Link.l9 = "Fine.";
				Link.l9.go = "exit";	
			}
		break;

//--> -------------------------------------------Бремя гасконца---------------------------------------------------
		case "Sharlie":
			dialog.text = "I'm sorry to disappoint you, Monsieur, but right now I don't have any ships for sale.";
			link.l1 = "That's really strange, 'cause I was told you had a brand new lugger at your shipyard.";
			link.l1.go = "Sharlie_1";
		break;
		
		case "Sharlie_1":
			if (GetQuestPastDayParam("questTemp.Sharlie_ship") > 3)
			{
				dialog.text = "You know it's probably about the lugger, for which bail of three thousand pesos by Michel de Monper? So this ship is already sold, because according to the contract, the total amount was to be paid no later than one week after the descent of the ship to the water.\nAll periods are over, and I did not recieve the money so the lugger was sold. So sorry, Sir.";
				link.l1 = "Yeah, that was quite unlucky, indeed... But are you sure you don't have other ships for sale?";
				link.l1.go = "Sharlie_6";
			}
			else
			{
			dialog.text = "Hmm. Yes, indeed. But...";
			link.l1 = "And there's already a deposit on it - five thousand peso. Michel de Monper, who deposited the money, granted me all rights to this ship.";
			link.l1.go = "Sharlie_2";
			}
		break;
		
		case "Sharlie_2":
			int iDay = 3-sti(GetQuestPastDayParam("questTemp.Sharlie_ship"));
			sTemp = "You only have "+FindRussianDaysString(iDay)+"";
			if (iDay == 0) sTemp = "Today is the last day";
			dialog.text = "Well, if such a thing, then to continue our conversation, Sir. As you rightly pointed out, I've got the deposit of five thousand pesos for the ship. But the full value of the ship I think is fifteen thousand pesos, along with ammunition. So pay me ten thousand and the ship is yours.\nAccording to the contract, you have to pay the money no later than one week after the descent of the ship to the water. "+sTemp+", and then I am free to sell this ship to another customer. And, mind you, there already is one, so you'd better hurry.";
			if (sti(Pchar.money) >= 10000)
			{
				link.l1 = "There will be no need to hurry. I have the required sum on me right now. Here you go.";
				link.l1.go = "Sharlie_4";
			}
			link.l2 = "Fine, fine. You'll have your money, Monsieur. I will not keep you waiting for long.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Sharlie_3";
		break;
		
		case "Sharlie_3":
			if (CheckAttribute(pchar, "questTemp.Sharlie.Rum") || CheckAttribute(pchar, "questTemp.Sharlie.Gigolo") || CheckAttribute(pchar, "questTemp.Sharlie.RescueDaughter"))
			{
				dialog.text = "Can I help you, Monsieur?";
				Link.l1 = "I just dropped in to take a look at the ships you have available... But right now I am a bit busy - I have an unfinished affair to deal with. I'll return as soon as I am through with it.";
				Link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.Sharlie == "ship" || pchar.questTemp.Sharlie == "ship_fast") // Addon 2016-1 Jason пиратская линейка 1
			{	
				if (GetQuestPastDayParam("questTemp.Sharlie_ship") > 3)
				{
					dialog.text = "Monsieur, I had warned you that you had only three days at your disposal. They have run out, and you still brought me no money, so our deal expired, and I sold the ship to another customer. No offense.";
					link.l1 = "Yeah, that was quite unlucky, indeed... But are you sure you don't have other ships for sale?";
					link.l1.go = "Sharlie_6";
				}
				else
				{
					dialog.text = "Have you brought me ten thousand, Monsieur?";
					if (sti(Pchar.money) >= 10000)
					{
						link.l1 = "Sure I have. Here you go.";
						link.l1.go = "Sharlie_4";
					}
					link.l2 = "No, I'm still working on it.";
					link.l2.go = "exit";
					NextDiag.TempNode = "Sharlie_3";
				}
			}
		break;
		
		case "Sharlie_4":
			AddMoneyToCharacter(pchar, -10000);
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("fortfrance_town", "reload", "reload5_back");
			dialog.text = "Then allow me to congratulate you on this successful purchase. The ship is yours. I hope she will serve you well.";
			link.l1 = "Thanks!";
			link.l1.go = "Sharlie_5";
		break;
		
		case "Sharlie_5":
			NextDiag.CurrentNode = "First time";
			DialogExit();
			pchar.questTemp.Sharlie.Ship = "lugger";
			pchar.questTemp.Sharlie = "crew";
			//стартовый люггер
			pchar.Ship.Type = GenerateShipHand(pchar, SHIP_LUGGER, 6, 800, 40, 610, 16000, 15.2, 58.8, 1.42);
			SetBaseShipData(pchar);
			ResetShipCannonsDamages(pchar);
			SetShipCannonsDamagesNull(pchar);
			NullCharacterGoods(pchar);
			SetCrewQuantityOverMax(PChar, 0);
			/* UpgradeShipParameter(pchar, "SpeedRate");
			UpgradeShipParameter(pchar, "TurnRate");
			UpgradeShipParameter(pchar, "WindAgainstSpeed");
			UpgradeShipParameter(pchar, "HP");
			UpgradeShipParameter(pchar, "MaxCrew");
			UpgradeShipParameter(pchar, "Capacity");
			//UpgradeShipParameter(pchar, "Cannons");
			pchar.ship.HP = 732; */
			//UpgradeShipFull(pchar);
			UpgradeShipParameter(pchar, "Capacity");
			RealShips[sti(pchar.Ship.Type)].ship.upgrades.hull  = "q"; // belamour особый скин
			AddLandQuestMark(characterFromId("FortFrance_tavernkeeper"), "questmarkmain");
			AddCharacterGoods(pchar, GOOD_BALLS, 100);
			AddCharacterGoods(pchar, GOOD_GRAPES, 100);
			AddCharacterGoods(pchar, GOOD_KNIPPELS, 100);
			AddCharacterGoods(pchar, GOOD_BOMBS, 100);
			AddCharacterGoods(pchar, GOOD_POWDER, 220);
			pchar.Ship.name = "Adeline";
			pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS6;
			AddQuestRecord("Sharlie", "6");
			bDisableFastReload = false;//открыть переход
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			if (GetCharacterIndex("GigoloMan") != -1)
			{
				sld = characterFromId("GigoloMan");
				sld.lifeday = 0;
			}
			pchar.GenQuest.StoreGoods.StoreIdx = Fortfrance_STORE;
			pchar.GenQuest.StoreGoods.Starting = true; // заполняем магазин
			bNoEatNoRats  = true; // отменяем еду и крыс
			GiveItem2Character(pchar, "map_normal");
		break;
		
		case "Sharlie_6":
			if (sti(Pchar.money) >= 15000)
				{
					dialog.text = "Hmm... Well, I have one, actually, but I am not sure it would suit you.";
					link.l1 = "Well, I can't afford being too picky now. Show me what you've got!";
					link.l1.go = "Sharlie_7";
				}
				else
				{
					dialog.text = "Listen, Monsieur, first make a pile and then ask about ships, alright? No one here will give you anything for free. Did I make myself clear?";
					link.l1 = "Perfectly clear, although there was no need to be rude. Fine, I'll come back once I have the money.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Sharlie_shipwait";
				}
		break;
		
		case "Sharlie_7":
			dialog.text = "Then look. I've recently purchased at a reasonable price one sloop. This was a former pirate vessel, her former owners are already safely hanged for numerous of crimes. The ship frankly, is not as good as a lugger and also has heavy damage, but still can get out into the sea.\nI have no time to repair her now - all my men are busy building a brig that was ordered, so you can buy her from me in the same condition in which it is. Considering this I'll sell her cheaper than usual, while also including the contents of the cargo hold - fifteen thousand pesos.";
			link.l1 = "Deal. She's seaworthy, and it's all that matters. Guadeloupe is within spitting distance - I'll have it fixed there if you don't have such an opportunity.";
			link.l1.go = "Sharlie_8";
		break;
		
		case "Sharlie_8":
			AddMoneyToCharacter(pchar, -15000);
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("fortfrance_town", "reload", "reload5_back");
			dialog.text = "Then allow me to congratulate you on this successful purchase. The ship is yours. I hope she will serve you well.";
			link.l1 = "Thanks!";
			link.l1.go = "Sharlie_9";
		break;
		
		case "Sharlie_9":
			NextDiag.CurrentNode = "First time";
			DialogExit();
			pchar.questTemp.Sharlie.Ship = "sloop";
			pchar.questTemp.Sharlie = "crew";
			//стартовый шлюп
			pchar.Ship.Type = GenerateShipHand(SHIP_SLOOP, 6, 700, 50, 790, 20000, 13.1, 50.1, 1.25);
			SetBaseShipData(pchar);
			ResetShipCannonsDamages(pchar);
			SetShipCannonsDamagesNull(pchar);
			NullCharacterGoods(pchar);
			SetCrewQuantityOverMax(PChar, 0);
			UpgradeShipParameter(pchar, "SpeedRate");
			UpgradeShipParameter(pchar, "TurnRate");
			UpgradeShipParameter(pchar, "WindAgainstSpeed");
			UpgradeShipParameter(pchar, "HP");
			UpgradeShipParameter(pchar, "MaxCrew");
			UpgradeShipParameter(pchar, "Capacity");
			AddCharacterGoods(pchar, GOOD_BALLS, 51);
			AddCharacterGoods(pchar, GOOD_GRAPES, 39);
			AddCharacterGoods(pchar, GOOD_KNIPPELS, 54);
			AddCharacterGoods(pchar, GOOD_BOMBS, 36);
			AddCharacterGoods(pchar, GOOD_POWDER, 231);
			pchar.Ship.name = "Black Hound";
			pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS3;
			AddQuestRecord("Sharlie", "6");
			bDisableFastReload = false;//открыть переход
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			if (GetCharacterIndex("GigoloMan") != -1)
			{
				sld = characterFromId("GigoloMan");
				sld.lifeday = 0;
			}
			pchar.GenQuest.StoreGoods.StoreIdx = Fortfrance_STORE;
			pchar.GenQuest.StoreGoods.Starting = true; // заполняем магазин
			bNoEatNoRats  = true; // отменяем еду и крыс
			GiveItem2Character(pchar, "map_normal");
		break;
		
		case "Sharlie_shipwait":
			dialog.text = "So, Monsieur, have you come back with the money?";
			if (sti(Pchar.money) >= 15000)
			{
				link.l1 = "Yeah, I think I have enough to afford a shabby ship.";
				link.l1.go = "Sharlie_7";
			}
			else
			{
				link.l1 = "I don't have enough yet. Just dropped in to take a look around...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Sharlie_shipwait";
			}
		break;
//<-- -----------------------------------------Бремя гасконца-----------------------------------------------------
		// Addon-2016 Jason, французские миниквесты (ФМК) ФМК-Мартиника
		case "FMQM_oil_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto5", "FMQM_Looking", -1);
			pchar.questTemp.FMQM = "remove_oil1";
		break;
		
		case "FMQM_oil_2":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("FMQM_officer");
			sld.Dialog.currentnode = "officer_3";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
			pchar.questTemp.FMQM = "remove_oil2";
		break;
		
		case "FMQM_oil_3":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("FMQM_officer");
			sld.Dialog.currentnode = "officer_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
			pchar.questTemp.FMQM = "remove_oil3";
		break;
		
		case "FMQM_oil_4":
			dialog.text = "Alas, my friend, but we both had suffered here. They have confiscated the resin, plus I wasted a huge amount of money for my bail. And how the hell did they learn about our operation? Must be one of my workers... I will deal with this, Lord have mercy on the guilty party!";
			link.l1 = "Meaning all my efforts were a waste...";
			link.l1.go = "FMQM_oil_5";
		break;
		
		case "FMQM_oil_5":
			dialog.text = "I am very sorry, Captain. Nothing we can do here, fate is a bitch sometimes.";
			link.l1 = "I see. Fine, I will take my leave then. Farewell!";
			link.l1.go = "FMQM_oil_6";
		break;
		
		case "FMQM_oil_6":
			DialogExit();
			AddQuestRecord("FMQ_Martinique", "12");
			pchar.questTemp.FMQM = "officer";
			pchar.quest.FMQM_advice.win_condition.l1 = "location";
			pchar.quest.FMQM_advice.win_condition.l1.location = "FortFrance_town";
			pchar.quest.FMQM_advice.function = "FMQM_GuideAdvice";
			DeleteAttribute(pchar, "questTemp.FMQM.Oil");
		break;
		
		// Addon 2016-1 Jason пиратская линейка
		case "mtraxx_x":
            dialog.text = "I'd like to return to that conversation. I am willing to give a decent discount... a very sizable discount for any labor on your ship... if you provide me with some extra silk...";
			link.l1 = "Master, let us get straight to the point. I promise I am no spy and neither am I one of Colonel D'Oyley's men. Moreover, I work with Marcus Tyrex, the name you should be familiar with. So, let's lay the cards on the table. I know you need a steady supply of silk sailcloth, and Marcus Tyrex is willing to bring it to you. Also steadily. However, only in the case to when we agree on the price. Shall we get straight to that then, master?";
			link.l1.go = "mtraxx_x_1";
		break;
		
		case "mtraxx_x_1":
            dialog.text = "Alright. I seem to have no choice in the matter - either you work for D'Oyley and will send me to prison, or I will go broke if I don't urgently find a sizable shipment of silk. I am willing to pay 25 doubloons per piece, but only for large shipments, no less than 100 rolls.";
			link.l1 = "Then we have a deal. I am sure Tyrex is able to provide you with shipments of 100 rolls every month.";
			link.l1.go = "mtraxx_x_2";
		break;
		
		case "mtraxx_x_2":
            dialog.text = "That would be most excellent! I could purchase the first batch straight away.";
			link.l1 = "Can't do it right now, but it won't take long. A vessel with the cargo you need is at Capsterville at the moment, I am heading there immediately and I will send her to you. Where shall we do the unloading?";
			link.l1.go = "mtraxx_x_3";
		break;
		
		case "mtraxx_x_3":
            dialog.text = "Let's arrange it like this. Between 10th and 15th of every month, nightly, my people will be awaiting for your visitors at the bay... no, wait, better at Cape Negril. It sure will be a long haul, but there are much fewer patrols... The password will be: 'A merchant of Lyons'.";
			link.l1 = "Deal, master. I am heading to Capsterville right away.";
			link.l1.go = "mtraxx_x_4";
		break;
		
		case "mtraxx_x_4":
            dialog.text = "I hope your ship will arrive fast, I am in dire need of new silk.";
			link.l1 = "Don't worry, everything will be alright. Godspeed!";
			link.l1.go = "mtraxx_x_5";
		break;
		
		case "mtraxx_x_5":
			DialogExit();
            AddQuestRecord("Roger_2", "21");
			pchar.questTemp.Mtraxx = "silk_10"; // покупатель найден
			sld = characterFromId("Jeffry");
			sld.DeckDialogNode = "Jeffry_9";
		break;
		// Jason Исла Мона
		case "IslaMona":
			if (CheckAttribute(pchar, "questTemp.IslaMona.Shipyarder") && pchar.questTemp.IslaMona.Shipyarder == npchar.id)
			{
				if (sti(NPChar.nation) != PIRATE && ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", 0) > 10)
				{
					dialog.text = "No, "+pchar.name+". I have nothing against you, but solve your problems with my country first. Selling such a valuable inventory to an enemy of the Crown could be misunderstood.";
					link.l1 = "Yeah, and when you're smuggling smuggled goods of unclear origin into ships, you're best friends? Wait for me to solve this misunderstanding.";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Let's say. Why? Are you building something?";
					link.l1 = "No, I'm doing a very special charter. For a plantation manager.";
					link.l1.go = "IslaMona_1";
				}
			}
			else
			{
				npchar.quest.IslaMonaTools = "true";
				dialog.text = "I can't help you.";
				link.l1 = "It's a shame!";
				link.l1.go = "exit";
			}
		break;
		
		case "IslaMona_1":
            dialog.text = "I see. I hope this manager has provided enough for you, as I would charge a lot for a set like this. You're very fortunate to have had a recent import from the metropolis.";
			link.l1 = "How much?";
			link.l1.go = "IslaMona_2";
		break;
		
		case "IslaMona_2":
			pchar.questTemp.IslaMona.Shipyarder.Money = 1000;
            dialog.text = "One thousand gold doubloons.";
			link.l1 = "You're overheating, I see. I'm fine. I'll take it.";
			link.l1.go = "IslaMona_7";
			link.l2 = "It's too much. I doubt there'll be another buyer for the whole set like me. Some of it will sell out, some of it will be stolen by the local vagrants. How about a discount?";
			link.l2.go = "IslaMona_3";
		break;
		
		case "IslaMona_3":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) < 60)
			{
				notification("Skill Check Failed (60)", SKILL_COMMERCE);
				dialog.text = "I guarantee it'll turn up. No change in price. How about it? I won't wait long.";
				link.l1 = "Fine, alright, alright. I'll take it.";
				link.l1.go = "IslaMona_7";
				AddCharacterExpToSkill(pchar, "Commerce", 200);
			}
			else
			{
				notification("Skill Check Passed", SKILL_COMMERCE);
				pchar.questTemp.IslaMona.Shipyarder.Money = 900;
				dialog.text = "All right, we'll take a hundred. Nine hundred. I won't go any lower. Don't ask me to.";
				link.l1 = "And I won't. I agree.";
				link.l1.go = "IslaMona_7";
				link.l2 = "Why don't you give me some more? As a wholesaler. And then I'll order repairs and paints from you, and the most juiciest figurehead.";
				link.l2.go = "IslaMona_4";
				AddCharacterExpToSkill(pchar, "Fortune", 100);
			}
		break;
		
		case "IslaMona_4":
            if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) < 85)
			{
				notification("Skill Check Failed (85)", SKILL_COMMERCE);
				dialog.text = "I don't care if you order a live wench. Nine hundred.";
				link.l1 = "Fine, alright, alright. I'll take it.";
				link.l1.go = "IslaMona_7";
				AddCharacterExpToSkill(pchar, "Commerce", 400);
			}
			else
			{
				notification("Skill Check Passed", SKILL_COMMERCE);
				pchar.questTemp.IslaMona.Shipyarder.Money = 800;
				dialog.text = "Are you sure? You won't forget? All right, let's cut another hundred. But that's it!";
				link.l1 = "I won't forget. It's a deal!";
				link.l1.go = "IslaMona_7";
				link.l2 = "Well, how can I put this...";
				link.l2.go = "IslaMona_5";
				AddCharacterExpToSkill(pchar, "Fortune", 200);
			}
		break;
		
		case "IslaMona_5":
            dialog.text = "Unthinkable! "+pchar.name+", they forgot to remove the piece of buckshot from your skull? Greedy as a scorpion! We've all heard about your recent escapades! You've already earned your pile of gold, so don't stop others from earning theirs. One more word and I won't sell for less than a thousand.";
			link.l1 = "All right, all right! Take it easy. I agree.";
			link.l1.go = "IslaMona_7";
			link.l2 = "But, "+npchar.name+", I've got little kids! I've got to think of them too! You don't get paid enough for honest freight, you know that!";
			link.l2.go = "IslaMona_6";
		break;
		
		case "IslaMona_6":
            if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) < 100)
			{
				notification("Skill Check Failed (100)", SKILL_COMMERCE);
				pchar.questTemp.IslaMona.Shipyarder.Money = 1000;
				dialog.text = "Children of brothel girls don't count, "+pchar.name+". I'm sick of you. A thousand doubloons on the barrel, or we say goodbye.";
				link.l1 = "What do you mean, they're not? Uh-huh. I agree, you're a crook.";
				link.l1.go = "IslaMona_7";
				AddCharacterExpToSkill(pchar, "Commerce", 800);
			}
			else
			{
				notification("Skill Check Passed", SKILL_COMMERCE);
				pchar.questTemp.IslaMona.Shipyarder.Money = 700;
				dialog.text = "I didn't know you had kids. And that things were so bad. Fine, don't complain. Seven hundred. It's almost a loss.";
				link.l1 = "I won't forget. It's a deal!";
				link.l1.go = "IslaMona_7";
				AddCharacterExpToSkill(pchar, "Fortune", 400);
				Achievment_SetStat(106, 1);
			}
		break;
		
		case "IslaMona_7":
            dialog.text = "So, you owe me "+sti(pchar.questTemp.IslaMona.Shipyarder.Money)+" doubloons.";
			if (GetCharacterItem(pchar, "gold_dublon") >= sti(pchar.questTemp.IslaMona.Shipyarder.Money))
			{
				link.l1 = "Here, I'm giving you the last of it, I've got nothing left.";
				link.l1.go = "IslaMona_8";
			}
			else
			{
				if (GetCharacterItem(pchar, "gold_dublon") < 1)
				{
					link.l1 = "Wait, I'm going to the loan shark to get into debt.";
					link.l1.go = "IslaMona_money_exit";
				}
				else
				{
					link.l1 = "All I have on me "+FindRussianDublonString(GetCharacterItem(pchar, "gold_dublon"))+". Take this, and I'll go to the loan sharks.";
					link.l1.go = "IslaMona_money";
				}
			}
		break;
		
		case "IslaMona_money":
			pchar.questTemp.IslaMona.Shipyarder.Money = sti(pchar.questTemp.IslaMona.Shipyarder.Money)-GetCharacterItem(pchar, "gold_dublon");
			Log_Info("You gave "+FindRussianDublonString(GetCharacterItem(pchar, "gold_dublon"))+"");
			RemoveItems(pchar, "gold_dublon", GetCharacterItem(pchar, "gold_dublon"));
			PlaySound("interface\important_item.wav");
            dialog.text = "Don't feel sorry for me, you've got a cabin locker full of gold. You'll owe me "+FindRussianDublonString(sti(pchar.questTemp.IslaMona.Shipyarder.Money))+".";
			link.l1 = "";
			link.l1.go = "IslaMona_money_exit";
		break;
		
		case "IslaMona_money_exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			npchar.quest.IslaMonaMoney = "true";
			pchar.questTemp.IslaMona = "dublon";
		break;
		
		case "IslaMona_8":
			Log_Info("You gave "+FindRussianDublonString(sti(pchar.questTemp.IslaMona.Shipyarder.Money))+"");
			RemoveItems(pchar, "gold_dublon", sti(pchar.questTemp.IslaMona.Shipyarder.Money));
			PlaySound("interface\important_item.wav");
            dialog.text = "That's great. The full amount is in place. The tools will be delivered to your ship. These are some heavy crates.";
			link.l1 = "Thank you, "+npchar.name+"!";
			link.l1.go = "IslaMona_9";
		break;
		
		case "IslaMona_9":
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			GiveItem2Character(pchar, "islamona_toolbox");
			DeleteAttribute(pchar, "questTemp.IslaMona.Shipyarder");
			DeleteAttribute(npchar, "quest.IslaMonaMoney");
			AddQuestRecord("IslaMona", "2");
			pchar.questTemp.IslaMona = "get_tools";
		break;
	}
}

string findShipyardCity(ref NPChar)
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES); 
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (sti(colonies[n].nation) != PIRATE && colonies[n].id != "Panama" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //не на свой остров
		{
			if (GetCharacterIndex(colonies[n].id + "_shipyarder") != -1)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[rand(howStore-1)];
	return colonies[nation].id;
}

// проверка какой уже цвет есть
bool CheckSailsColor(ref chr, int col)
{
	int    st = GetCharacterShipType(chr);
	ref    shref;
	
	if (st != SHIP_NOTUSED)
	{
		shref = GetRealShip(st); 
		st = -1;
		if (!CheckAttribute(shref, "ShipSails.SailsColor"))  st = 0; // нету - это белый
		if (CheckAttribute(shref, "SailsColorIdx"))  st = sti(shref.SailsColorIdx);
		if (st == col) return false;
	}
	return true;		
}

bool CheckSailsGerald(ref chr)
{
    int    st = GetCharacterShipType(chr);
	ref    shref;
	if (st != SHIP_NOTUSED)
	{
		shref = GetRealShip(st);
		if (CheckAttribute(shref, "GeraldSails"))  return true;
	}
	return false;
}

string GetSailsType(int _type)
{
	string sSail;
	
	switch (_type)
	{
	    case 1 : sSail = ""+XI_ConvertString("sails_1")+""; break;
	    case 2 : sSail = ""+XI_ConvertString("sails_2")+""; break;
	    case 3 : sSail = ""+XI_ConvertString("sails_3")+""; break;
		case 4 : sSail = ""+XI_ConvertString("sails_4")+""; break;
		case 5 : sSail = ""+XI_ConvertString("sails_5")+""; break;
		case 6 : sSail = ""+XI_ConvertString("sails_6")+""; break;
		case 7 : sSail = ""+XI_ConvertString("sails_7")+""; break;
		case 8 : sSail = ""+XI_ConvertString("sails_8")+""; break;
		case 9 : sSail = ""+XI_ConvertString("sails_9")+""; break;
		case 10 : sSail = ""+XI_ConvertString("sails_10")+""; break;
		case 11 : sSail = ""+XI_ConvertString("sails_11")+""; break;
	}
	return sSail;
}

int GetSailsTypePrice(int _asis, int _tobe, float _shipCostRate, int _price)
{
	int ret;
	ret = _tobe - _asis;
	
	if (ret < 0) ret = 0;
	
	return makeint((ret*_price*0.05 + _price*0.05)*_shipCostRate / 10) * 10;
}

void SelectFindship_ShipType()
{
	int iRank;
	if (sti(pchar.rank) == 1) iRank = 0;
	if (sti(pchar.rank) > 1 && sti(pchar.rank) <= 2) iRank = 1;
	if (sti(pchar.rank) > 2 && sti(pchar.rank) <= 4) iRank = 2;
	if (sti(pchar.rank) > 4 && sti(pchar.rank) <= 7) iRank = 3;
	if (sti(pchar.rank) > 7 && sti(pchar.rank) <= 10) iRank = 4;
	if (sti(pchar.rank) > 10 && sti(pchar.rank) <= 18) iRank = 5;
	
	int iClassFlag = FLAG_SHIP_CLASS_5;
	int iTypesFlag = FLAG_SHIP_TYPE_MERCHANT;
	switch (iRank)
	{
		case 0:  
			iClassFlag = FLAG_SHIP_CLASS_5;
		break; 		
		case 1:  
			iClassFlag = FLAG_SHIP_CLASS_4;
		break;
		case 2:  
			iClassFlag = FLAG_SHIP_CLASS_4;
		break;
		case 3: 
			iClassFlag = FLAG_SHIP_CLASS_3;
		break;
		case 4:  
			iClassFlag = FLAG_SHIP_CLASS_3;
			iTypesFlag = or(FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_TYPE_WAR);
		break;
		case 5: 
			iClassFlag = FLAG_SHIP_CLASS_2;
			iTypesFlag = or(FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_TYPE_WAR);
		break;
	}
	
	pchar.GenQuest.Findship.Shipyarder.ShipType = GetRandomShipType(iClassFlag, iTypesFlag, FLAG_SHIP_NATION_ANY);
}

// проверка количества материалов для корабельного тюнинга
void checkMatherial(ref Pchar, ref NPChar, int good)
{
    int amount;

    amount = GetSquadronGoods(Pchar, good) - sti(NPChar.Tuning.Matherial);
    if (amount < 0)
    {
       amount = amount + sti(NPChar.Tuning.Matherial);
    }
    else
    {
        amount = sti(NPChar.Tuning.Matherial);
    }
    RemoveCharacterGoods(Pchar, good, amount);
    NPChar.Tuning.Matherial = sti(NPChar.Tuning.Matherial) - amount;
}

/*
  _chr 		- ГГ
  NPChar 	- верфист
  MaterialNum -  номер материала для апгрейда 
	 1 - товар	 
	 2 - цена в дублонах(сундуки)
  Функция возвращает кол-во материала необходимого для данного типа апгрейда	  
*/

int GetMaterialQtyUpgrade( ref _chr, ref _nchar, int MaterialNum )
{
	if ( sti(_chr.Ship.Type) == SHIP_NOTUSED) return 0;
	
	float fQuestShip 	= 1.0;
	float LEcoeff       = 1.0; // legendary edition
		
	int   	shipClass     		= sti(RealShips[sti(_chr.Ship.Type)].Class);	
	int   	shipMinCrew   		= sti(RealShips[sti(_chr.Ship.Type)].MinCrew);	
	int 	shipPrice			= sti(RealShips[sti(_chr.Ship.Type)].Price);	
		
    if(shipClass == 4) LEcoeff = 0.38;
    if(shipClass > 4) LEcoeff = 0.25;
	if(CheckAttribute(&RealShips[sti(_chr.Ship.Type)], "QuestShip")) 	fQuestShip = 1.3;	

	if(MaterialNum == 1) 
	{
	int Material 	= makeint((40 * (7 - shipClass) + 25 * MOD_SKILL_ENEMY_RATE + drand(shipMinCrew)) * fQuestShip * LEcoeff);
	if(Material < 1) 		Material 	= 1;
		return Material;
	}
	if(MaterialNum == 2)
	{
		int WorkPrice 	= 1;
		switch (shipClass)
		{
			case 1: 
				WorkPrice = 10;
			break;
			case 2: 
				WorkPrice = 7;
			break;
			case 3: 
				WorkPrice = 5;
			break;
			case 4: 
				WorkPrice = 3;
			break;
			case 5: 
				WorkPrice = 1;
			break;
		}
		return WorkPrice;
	}
	
	return 0;
}
// belamour legendary edition тюнинг - проверка на сделанное
bool TuningAvailable()
{
	int num = 0;
    ref shTo = &RealShips[sti(Pchar.Ship.Type)];

	if(CheckAttribute(shTo, "Tuning.SpeedRate"))    num++;
	if(CheckAttribute(shTo, "Tuning.WindAgainst"))  num++;
	if(CheckAttribute(shTo, "Tuning.Cannon"))       num++;
	if(CheckAttribute(shTo, "Tuning.Capacity"))     num++;
	if(CheckAttribute(shTo, "Tuning.HP"))           num++;
	if(CheckAttribute(shTo, "Tuning.MaxCrew"))      num++;
	if(CheckAttribute(shTo, "Tuning.TurnRate"))     num++;
	if(CheckAttribute(shTo, "Tuning.MinCrew"))      num++;
	
	if(sti(shTo.Class) > 4 && num == 7 && !CheckAttribute(shTo, "Tuning.MinCrew"))
	{
		if(!CheckAttribute(shTo, "Tuning.All"))
        {
			if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_HIMERA) Achievment_Set("ach_CL_115");
			if(startHeroType == 4 && sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_SCHOONER_W)
			{
				if(pchar.ship.name == "Rainbow") Achievment_Set("ach_CL_126");
			}
            shTo.Tuning.All = true;
            Log_Info("Ship " + pchar.ship.name + "  gains 5% speed increase on the Global Map!");
        }
        return false;
	}
	
	if(num < 8) return true;
	else
    {
        if(!CheckAttribute(shTo, "Tuning.All"))
        {
			if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_HIMERA) Achievment_Set("ach_CL_115");
			if(startHeroType == 4 && sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_SCHOONER_W)
			{
				if(pchar.ship.name == "Rainbow") Achievment_Set("ach_CL_126");
			}
            shTo.Tuning.All = true;
            Log_Info("Ship " + pchar.ship.name + "  gains 5% speed increase on the Global Map!");
        }
        return false;
    }
}
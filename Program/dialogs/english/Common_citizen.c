// boal 25/04/04 общий диалог горожан
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
    ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06
    int iTest, iTemp;
    iTest = FindColony(NPChar.City); // город
    ref rColony;
    string sTemp, sCity;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	String attrLoc = Dialog.CurrentNode;
	
	if(HasSubStr(attrLoc, "RumourAboutOwners_"))
	{
		NPChar.RumourOwnerType = FindStringAfterChar(attrLoc, "_");
		Dialog.CurrentNode = "RumourAboutOwners_TakeRumour";
	}
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "fight":
            LAi_group_Attack(NPChar, Pchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
            /*if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
				dialog.text = RandPhraseSimple("A spy? Guards!","Alarm! There's an intruder!");
				link.l1 = "Shut up. I'm leaving.";
				link.l1.go = "fight";
				break;
			}*/
			
			if (sti(NPChar.nation) == PIRATE)
			{
				if (sti(rColony.HeroOwn) == true) // наш горожанин
				{
				    dialog.text = RandPhraseSimple("They say that you are the one who rules this town, "+GetSexPhrase("sir","miss")+".","What a pleasant meeting, the city head has approached me with a question.");
					link.l1 = RandPhraseSimple("I've changed my mind.","I'm simply exploring this town. Goodbye.");
					link.l1.go = "exit";
					link.l2 = RandPhraseSimple("I have a question for you.","I need information.");
					link.l2.go = "quests";//(перессылка в файл города)
					if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
		            {
		                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
		                {
							link.l3 = RandPhraseSimple("I want to discuss business.","Regarding finances...");
							link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
						}
					}
					break;
				}
				else
				{ // пираты, не наши
				    dialog.text = RandPhraseSimple("What do you want? Move along.","Don't stand in the way, get lost!");
					link.l1 = RandPhraseSimple("Hey, stop barking, will you?","Simmer down, or you might regret it!");
					link.l1.go = "exit";
					link.l2 = RandPhraseSimple("I have a question for you.","A moment of your attention, please. I have a question.");
					link.l2.go = "quests";//(перессылка в файл города)
					if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
		            {
		                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
		                {
							link.l3 = RandPhraseSimple("I want to discuss business.","Regarding finances...");
							link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
						}
					}
					break;
				}
			}
            if(NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = "1";

                // homo 05/08/06
				dialog.Text = NPCharRepPhrase(npchar,LinkRandPhrase("My name is ","My name is ","You may call me ")+GetFullName(npchar)+LinkRandPhrase(". What do you need?",". I haven't "+NPCharSexPhrase(NPChar,"seen you here before","seen you there before")+", who are you?",". Who are you, and what do you want from me?"),LinkRandPhrase("Greetings, "+GetAddress_Form(NPChar)+". My name is "+GetFullName(npchar)+". What's yours?","Hello, "+GetAddress_Form(NPChar)+"! I am "+GetFullName(npchar)+". May I have your name?","Yes, "+GetAddress_Form(NPChar)+". What do you want? By the way, my name is "+GetFullName(npchar)+". And who are you?"));

				Link.l1 = pcharrepphrase(LinkRandPhrase("By thunder! ","Hell's bells! ","Bad cess to you! ")+"Yes, I am the Captain "+GetFullName(Pchar)+LinkRandPhrase(", you really haven't heard of me"+NPCharSexPhrase(NPChar,", rascal?","?")," and "+GetSexPhrase("the most notorious pirate","the most notorious lady pirate")+" in these waters! "," and may I burn in Hell if that's not true!"),LinkRandPhrase("I am the Captain"+GetFullName(Pchar)+".","My name is "+GetFullName(Pchar)+".","You may call me Captain "+GetFullName(Pchar)));

                //LinkRandPhrase("I am Captain" + GetFullName(Pchar) + ".", "My name is " + GetFullName(Pchar) + ".", "You may call me Captain " + GetFullName(Pchar));
				Link.l1.go = "Meeting";
			}
			else
			{
				if(rand(5) == 1 && NPChar.sex == "woman" && !CheckAttribute(NPChar, "CitizenFindItem.NoQuest") && !CheckAttribute(PChar, "GenQuest.CitizenFindItem.StartQuest") && CheckAttribute(NPChar, "City"))
				{
					dialog.Text = "Captain, could you please help me out?";
					link.l1 = LinkRandPhrase("Sorry, no. I have little time to spare.","Sorry, I can't. Too busy.","No, I can't. I have urgent matters that require my attention.");
					link.l1.go = "CitizenFindItem_NoQuest";
					link.l2 = LinkRandPhrase("Sure, I can. What's the problem?","Yes, I'll help you. Tell me more about this business of yours.","Tell me more about your business...");
					link.l2.go = "CitizenFindItem_1";
					NextDiag.TempNode = "First time";
					break;
				}
				
				if(CheckAttribute(PChar, "GenQuest.CitizenFindItem.CitizenID") && PChar.GenQuest.CitizenFindItem.CitizenID == NPChar.ID && CheckCharacterItem(PChar, "DOjeronRing"))
				{
					dialog.Text = "Yes, Captain, I am listening.";
					link.l1 = NPChar.name+", I found your wedding ring.";
					link.l1.go = "CitizenFindItem_Complete_1";
					break;
				}
			
				link.l1 = PCharRepPhrase("I want to learn more about this town.","Tell me about this town.");
				link.l1.go = "new question";
 				link.l2 = RandPhraseSimple("I have a question for you.","I need information.");
				if (CheckCharacterItem(pchar, "CaptainBook"))				
				{
					if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
					{
						link.l2.go = "ShipLetters_7";// генератор  "Найденные документы"
					}
					else
					{
						link.l2.go = "quests";
					}	
				}
				else
				{
					link.l2.go = "quests";//(перессылка в файл города)
				}	
				if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
	            {
	                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
	                {
						link.l3 = RandPhraseSimple("I want to discuss business.","Regarding finances...");
						link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
					}
				}
				// --> квестовый генератор мэра, поиск шпиёна на улице. eddy
				if (CheckAttribute(pchar, "GenQuest.SeekSpy.City") && pchar.location == (npchar.city + "_town"))
	            {
					link.l4 = NPCharSexPhrase(npchar,LinkRandPhrase("Hold on! Tell me who you are—right now! I am seeking an enemy spy at the request of the governor of "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+"!","Halt! I act in the interest of the town "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+" by order of the governor. I'm searching the city for a hostile agent.","Stop, friend! The local governor "+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname+" wants to find a spy in town."),LinkRandPhrase("Hold on, lady! Tell me who you are – right now! I am seeking out an enemy spy at the request of the governor of "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+"!","Woman, I must detain you! I act in the interest of the town "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+" by order of the governor. I'm searching the city for a hostile agent","Stand still, beauty! The local governor "+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname+" wants to find a spy in town..."));
					link.l4.go = "SitySpy";
				}
				// <-- квестовый генератор мэра, поиск шпиёна на улице
				
				//Jason --> генератор Неудачливый вор
				if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
				{
					link.l16 = "Maybe you can give me some advice. I want to purchase "+pchar.GenQuest.Device.Shipyarder.Type+", and I've been told it was being sold in your town. Well, someone was selling it on the streets. Do you know anything about that?";
					link.l16.go = "Device_Citizen";
				}
				// <-- генератор Неудачливый вор
				
				// Квестовый генератор священника. Квест №2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	            {
					link.l5 = LinkRandPhrase("Are you aware","Did you know","Did you hear")+" that a local church was raided recently?");
					link.l5.go = "Citiz_GenQuest_Church_2_1";
				}
				// <-- Квестовый генератор священника. Квест №2.
				
                dialog.Text = NPCharRepPhrase(npchar,PCharRepPhrase(LinkRandPhrase("Oh, it's you, "+GetFullName(Pchar)+" "+GetSexPhrase(", old scoundrel","- hotshot lady")+"","Good to see you again, "+GetSexPhrase("old chap","beauty")+" "+Pchar.name,"Oh, it's good old "+GetSexPhrase("Captain","lady")+" "+GetFullName(Pchar))+LinkRandPhrase(". I thought you were dead!",". And surely, "+GetSexPhrase("Drunk as usual.","already under the weather.")+"",". And, as I see, still at liberty!")+LinkRandPhrase(" So, speak your mind – what do you need?"," What do you need this time?"," Are you pestering me over nothing again?"),LinkRandPhrase(TimeGreeting()+", Captain ","Hello, "+GetAddress_Form(NPChar)+" ","I greet you, Captain ")+GetFullName(Pchar)+LinkRandPhrase(". What could "+GetSexPhrase("such a gallant gentleman","such a dashing lady")+", like? Is there anything you might need from me?",". What brings you here?",". What do you want to know this time?")),PCharRepPhrase(LinkRandPhrase("Hello, Captain ","Hello. Oh, it's you "+GetAddress_Form(NPChar)+" ","Oh, Captain ")+GetFullName(Pchar)+LinkRandPhrase(", I thought"+NPCharSexPhrase(NPChar," "," ")+"we would never meet again,",", can't say I'm glad"+NPCharSexPhrase(NPChar," "," ")+"to see you, but",", I see, you're still alive. Regrettable. So,")+LinkRandPhrase(" what do you need?"," what have you come for?"," what can I "+NPCharSexPhrase(NPChar,"help you with?","help you with?")),LinkRandPhrase(TimeGreeting()+", Captain "+GetFullName(Pchar)+". What can I help you with?","Oh, if it isn't"+GetSexPhrase("","")+" Captain "+GetFullName(Pchar)+"! What would you like to know this time?","Hello, "+GetAddress_Form(NPChar)+" "+Pchar.lastname+". Did you want something?")));                         
	   			link.l6 = PCharRepPhrase(RandPhraseSimple("No, you're hearing things. I'll be going now.","No, nothing – I was just heading"+GetSexPhrase("","")+" to the tavern."),RandPhraseSimple("No, nothing. Best of luck to you!","Just looking around. Goodbye."));
				link.l6.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "ShipLetters_7":
			dialog.text = "What questions?";
			link.l1 = "Does the name on these papers ring a bell?";
			link.l1.go = "ShipLetters_8";
		break;
		
		case "ShipLetters_8":
			dialog.text = LinkRandPhrase("I don't care for unfamiliar papers. Besides, I can't read. Go see the usurer, that devil surely knows how to read and write.","I have no clue what you're talking about. Ask around among the townsfolk, Captain "+GetFullName(Pchar)+".","I really have no idea how to help you, Captain "+GetFullName(Pchar)+". Try asking the usurer – perhaps he might know.");
			link.l1 = "I will gladly follow your advice!";
			link.l1.go = "exit";
		break;
		
		case "Meeting":
		    dialog.Text = NPCharRepPhrase(npchar,LinkRandPhrase("But aren't you lying, Captain "+GetFullName(Pchar)+"?","And so what, "+PChar.name+"?","I will remember you, "+GetFullName(Pchar)+".")+"And now, what is it that you need?",LinkRandPhrase("A pleasure to meet you, Captain "+PChar.name,"Glad"+NPCharSexPhrase(NPChar," "," ")+" to meet you, "+GetAddress_Form(NPChar)+" "+PChar.lastname,"Nice to meet you, Captain "+PChar.name)+". But I take it you came here for more than just learning my name?");

            link.l1 = PCharRepPhrase("I wanted to"+GetSexPhrase("","")+" to know something about this hole you call a town!","I wanted to"+GetSexPhrase("","")+" to know something about this town.");
			link.l1.go = "new question";
            Link.l2 = RandPhraseSimple("I have a question for you.","I need information.");
			if (CheckCharacterItem(pchar, "CaptainBook"))				
			{
				if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
				{
					link.l2.go = "ShipLetters_7";// генератор  "Найденные документы"
				}
				else
				{
					Link.l2.go = "quests";
				}	
			}
			else
			{
					link.l2.go = "quests";//(перессылка в файл города)
			}			
			if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
            {
                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
                {
					link.l3 = RandPhraseSimple("I want to discuss business.","Regarding finances...");
					link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
				}
			}
			
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l16 = "Maybe you can give me some advice. I want to purchase "+pchar.GenQuest.Device.Shipyarder.Type+", and I've been told that it was being sold in your town. Well, someone was selling it on the streets. Do you know anything about that?";
				link.l16.go = "Device_Citizen";
			}
			// <-- генератор Неудачливый вор
			
			// --> квестовый генератор мэра, поиск шпиёна на улице. eddy
			if (CheckAttribute(pchar, "GenQuest.SeekSpy.City") && pchar.location == (npchar.city + "_town"))
	        {
				link.l4 = NPCharSexPhrase(npchar,LinkRandPhrase("Hold on! Tell me who you are - right now! I am seeking an enemy spy at the request of the governor of "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+"!","Halt! I act in the interest of"+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+" by order of the governor. I'm searching the city for a hostile agent.","Stop, friend! The local governor "+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname+" wants to find a spy in town."),LinkRandPhrase("Hold on, lady! Tell me who you are – right now! I am seeking an enemy spy at the request of the governor of "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+"!","Woman, I must detain you! I act in the interest of the city "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+" by order of the governor. I'm searching the city for a hostile agent.","Stand, beautiful woman! The local governor "+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname+" wants to seek out a spy in town..."));
				link.l4.go = "SitySpy";
			}
			// <-- квестовый генератор мэра, поиск шпиёна на улице
			// Квестовый генератор священника. Квест №2. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	        {
				link.l5 = LinkRandPhrase("Are you aware","Did you hear","Did you hear")+" that a local church was raided recently?");
				link.l5.go = "Citiz_GenQuest_Church_2_1";
			}
			// <-- Квестовый генератор священника. Квест №2.
			
			Link.l6 = PCharRepPhrase(RandPhraseSimple("No, you're imagining things. I'll be going now.","No, nothing - I was just heading to the tavern."),RandPhraseSimple("No, nothing. Best of luck to you!","Just looking around. Goodbye."));
			Link.l6.go = "exit";
		break;
		
		case "new question":
            dialog.text = NPCharRepPhrase(npchar,PCharRepPhrase(LinkRandPhrase("Oh yes, I am almost as glad"+NPCharSexPhrase(NPChar," "," ")+" to see you as a cup of booze. Ask whatever you like.","You like talking, Captain? Well, me too... Especially over a cup of rum.","Yes, "+PChar.name+"?"),LinkRandPhrase("What do you need?","I see, Captain "+PChar.name+". You are"+GetSexPhrase("","")+" quite a talker. ","You've worn me out"+GetSexPhrase("","")+" with your questions, Captain. You'd better help me with the rum.")),PCharRepPhrase(LinkRandPhrase("What do you want to know "+GetAddress_Form(NPChar)+"?","I'm listening to you, Captain.","I have to go, so please be quick about it, Captain."),LinkRandPhrase("Always glad"+NPCharSexPhrase(NPChar," "," ")+"  to have good company, "+GetAddress_Form(NPChar)+" "+PChar.lastname+". Speak your mind.","Yes, "+GetAddress_Form(NPChar)+"?","You like chatting, Captain? Well, me too...")));

            // homo 25/06/06
			link.l1 = LinkRandPhrase("What gossip is popular in the local tavern?","What's going on in these lands?","What's new ashore here?");
			link.l1.go = "rumours_citizen";
			link.l2 = LinkRandPhrase("Can you direct me there?","I can't find the way to a certain place...","Could you show the way...?");
			link.l2.go = "town";  //(перессылка в файл города)
			if(Rand(1)==0)
			{
				link.l3 = LinkRandPhrase("I want to know what people are saying about a certain person.","Don't you know what people are saying about a certain person?","I'd like to learn something about the locals.");
				if(rand(1) == 0 || PChar.location == "LaVega_Town" || PChar.location == "PuertoPrincipe_town"
				|| PChar.location == "Pirates_town" || PChar.location == "Panama_town" || !CheckAttribute(NPChar, "City"))
				{
					link.l3.go = "info"; //(перессылка в файл города)
				}
				else
				{
					link.l3.go = "RumourAboutOwners"; // Warship. Сделал по-другому - у жителя каждого города будет свой диалог.
				}
			}
			else
			{
				link.l3 = "Please tell me more about your colony.";
				link.l3.go = "colony";
			}
            link.l4 = RandPhraseSimple("I've got important business!","I have business with you.");
			link.l4.go = "quests";  //(перессылка в файл города)
			link.l5 = PCharRepPhrase(RandPhraseSimple("No, you're imagining things. I'll be going now.","No, nothing - I was just heading to the tavern."),RandPhraseSimple("No, nothing. Best of luck to you!","Just looking around. Goodbye."));
			link.l5.go = "exit";
		break;
		
		case "RumourAboutOwners":
			Dialog.Text = "Who would you like to know about?";
			if(GetCharacterIndex(NPChar.city + "_Mayor") != -1)
			{
				link.l1 = "About the governor.";
				link.l1.go = "RumourAboutOwners_Mayor";
			}
			if(GetCharacterIndex(NPChar.city + "_TavernKeeper") != -1)
			{
				link.l2 = "About the owner of the local tavern.";
				link.l2.go = "RumourAboutOwners_TavernKeeper";
			}
			if(GetCharacterIndex(NPChar.city + "_ShipYarder") != -1)
			{
				link.l3 = "About the harbour master.";
				link.l3.go = "RumourAboutOwners_ShipYarder";
			}
			if(GetCharacterIndex(NPChar.city + "_Trader") != -1)
			{
				link.l4 = "About the owner of the local shop.";
				link.l4.go = "RumourAboutOwners_Trader";
			}
			link.l9 = "Never mind, forget it.";
			link.l9.go = "exit";
			break;
			
		case "RumourAboutOwners_TakeRumour":
			sTemp = sRumourAboutOwners_CityRumour(NPChar.City, NPChar.RumourOwnerType);
			Dialog.Text = sTemp;
			link.l1 = "Thanks.";
			link.l1.go = "exit";
			// Здесь можно делать проверка по квестам, какой слух выпал
			DeleteAttribute(PChar, "QuestTemp.RumoursAboutOwners");
			break;
		
		case "colony":
			dialog.text = LinkRandPhrase("Honestly, I don't know much about it, but I can still tell you a thing or two.","And what interests you in our colony?","Sure. What would you like to know?");
            switch(Rand(1))
			{
				case 0:
					link.l1 = "What kind of town is this?";
					link.l1.go = "colony_town";
				break;

				case 1:
					link.l1 = "What do you know about the fort defending the town?";
					link.l1.go = "fort";
				break;
            }
			link.l2 = "Let's change the subject.";
			link.l2.go = "new question";
		break;
	  // to_do
		case "colony_town":
            dialog.text = "Are you kidding? Or joking? Look at the top right corner of your screen.";
			link.l1 = "Yeah, my bad.";
		    link.l1.go = "exit";
		break;
		
		case "fort":
            dialog.text = "I don't know anything about it.";
			link.l1 = "Pity.";
		    link.l1.go = "exit";
		break;
		
		//Jason --> генератор Неудачливый вор
		case "Device_Citizen":
           dialog.text = "Hmm, "+pchar.GenQuest.Device.Shipyarder.Type+"? Never heard of it before... What is it, actually? I've never heard of such a thing in all my time"+NPCharSexPhrase(npchar,"","")+".";
			link.l1 = "Well, it's a shipwright's tool, "+pchar.GenQuest.Device.Shipyarder.Describe+". Has anyone been selling such a thing in town? Perhaps. Did you notice anyone carrying such a thing?";
			link.l1.go = "Device_Citizen_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_Citizen_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) > 3 && sti(pchar.GenQuest.Device.Shipyarder.Chance1) < 6 && npchar.sex != "woman")
			{
				dialog.text = "Hmm... Yes, I believe I've seen someone with something like that. He was walking around there with it several hours ago. An interesting device, certainly.";
				link.l1 = "And what did he look like, and where did he go? I need that instrument badly.";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "No, I haven't seen anything like that.";
				link.l1 = "I see. Well, time to ask around!";
				link.l1.go = "exit";
			}
		break;
		
		//============================ Генератор мэра. Квест по розыску шпиона на улице ============================
		case "SitySpy":
			dialog.text = NPCStringReactionRepeat(NPCharSexPhrase(npchar,"And what does that have to do with me? I'm a local!","Well, why do you trouble me with this? I live in this city and know nothing of such things!"),NPCharSexPhrase(npchar,"What do you want from me again? Haven't I already told you that I'm not the spy?!","Didn't I already tell you that I'm a local?!"),NPCharSexPhrase(npchar,"My dear, it's you again! Leave me be – I am a local!","Why are you bothering me with your stupid questions again?"),NPCharSexPhrase(npchar,"Again! Now this is an outrage!","Listen, just leave me be, all right? Please!"),"block",0,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Who can confirm your statement?","Oh, I am sorry - I've already asked you...","I am sorry, there are so many people...","All right, all right...",npchar,Dialog.CurrentNode);
		    link.l1.go = DialogGoNodeRepeat("SitySpy_1", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
			// ==> выбираем подтверждателя
			int num = FindNearCharacters(npchar, 20.0, -1.0, -1.0, 1.0, false, true);
			if(num > 0)
			{
				for(i = 0; i < num; i++)
				{
					iTemp = chrFindNearCharacters[i].index;
					if (CheckAttribute(&characters[iTemp], "CityType"))
					{
						if(characters[iTemp].CityType == "soldier" || characters[iTemp].CityType == "citizen")
						{
							break;
						}
					}
				}
				pchar.GenQuest.SeekSpy.Idx = chrFindNearCharacters[i].index; //индекс выбранного
				pchar.GenQuest.SeekSpy.Type = characters[sti(pchar.GenQuest.SeekSpy.Idx)].chr_ai.type; //тип кто помог
				pchar.GenQuest.SeekSpy.BaseIdx = npchar.index; //индекс
			}
		break;
		case "SitySpy_1":
			if (sti(pchar.GenQuest.SeekSpy.Idx) == -1 || sti(pchar.GenQuest.SeekSpy.Idx) == 1) //на всякий случай
			{
				dialog.text = "Anyone can! Listen, why do you keep pestering me?! If you have a problem, go see the governor and sort it all out!",link.l1 ="Hmm... It's probably best not to bother him over such a trivial matter. I believe you.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Anyone in this town! "+NPCharSexPhrase(npchar,GetFullName(&characters[sti(pchar.GenQuest.SeekSpy.Idx)])+" can do it, for instance, now that "+NPCharSexPhrase(&characters[sti(pchar.GenQuest.SeekSpy.Idx)],"he","she")+" is standing right there.","Oh, Lord, well, for instance, "+NPCharSexPhrase(&characters[sti(pchar.GenQuest.SeekSpy.Idx)],GetAddress_FormToNPC(NPChar)+" "+characters[sti(pchar.GenQuest.SeekSpy.Idx)].lastname,GetFullName(&characters[sti(pchar.GenQuest.SeekSpy.Idx)]))+" I can do it.");				
			link.l1 = "Alright, let's see, then.";
		    link.l1.go = "SitySpy_2";
			sld = &characters[sti(pchar.GenQuest.SeekSpy.Idx)];
			sld.dialog.currentnode = "SeekSpy_Checking";
			pchar.GenQuest.SeekSpy.time = 4.0; //время на подбежать
			if (sld.chr_ai.type == "merchant") pchar.GenQuest.SeekSpy.time = 0.0; //мерчант базарит сразу
            LAi_SetActorTypeNoGroup(sld);
		break;
		case "SitySpy_2":
			sld = &characters[sti(pchar.GenQuest.SeekSpy.Idx)];
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorTurnToCharacter(npchar, sld);
			LAi_ActorDialog(sld, pchar, "", stf(pchar.GenQuest.SeekSpy.time), 0); 
			DialogExit();
		break;
		//=================== ноды квеста мэра. поиск шпиона на улице, опрос свидетеля ==================
		case "SeekSpy_Checking":
			dialog.text = "Yes, "+NPCharSexPhrase(&characters[sti(pchar.GenQuest.SeekSpy.BaseIdx)]," is indeed a local.","she is indeed a local.");
			link.l1 = RandPhraseSimple("I see"+GetSexPhrase("","")+". Thank you for your help.","All clear. Thank you for the help.");
			link.l1.go = "SeekSpy_Checking_1";
		break;
		case "SeekSpy_Checking_1":
			switch (pchar.GenQuest.SeekSpy.Type)
			{
				case "guardian": LAi_SetGuardianTypeNoGroup(npchar); break;
				case "patrol":   LAi_SetPatrolTypeNoGroup(npchar);   break;
				case "citizen":  LAi_SetCitizenTypeNoGroup(npchar);  break;
				case "merchant": LAi_SetMerchantTypeNoGroup(npchar); break;
			}
			LAi_SetCitizenTypeNoGroup(&characters[sti(pchar.GenQuest.SeekSpy.BaseIdx)]);
			NextDiag.CurrentNode = "First Time";
			DialogExit();
		break;
		
		// Мини квест на поиск обручального кольца -->
		case "CitizenFindItem_1":
			dialog.text = "You see, yesterday I was out of town, taking a stroll, and I lost my wedding ring... "+GetSexPhrase("Captain, could you please look for it?","Lady, please, help me find it!")+"";
			link.l1 = "Of course "+GetSexPhrase("I can! For such a fair girl as you, I can do anything!","I'll help you. The Church teaches us to help those in need.")+"";
			link.l1.go = "CitizenFindItem_2";
			link.l2 = LinkRandPhrase("No, I can't. I'm sorry. I have too much to do.","I am sorry, I can't. I just remembered."+GetSexPhrase("","")+", that I still have unfinished business...","I have very little time, so I can't help you with anything...");
			link.l2.go = "CitizenFindItem_NoQuest";
			break;
			
		case "CitizenFindItem_2":
			dialog.text = ""+GetSexPhrase("Captain","Lady")+", that's wonderful! Please find this ring for me, my husband arrives in just "+sti(NPChar.LifeDay)+" days, and I would not want him to see me without my wedding ring.";
			link.l1 = RandPhraseSimple("Where did you lose it, you say?","So where exactly did you lose it?");
			link.l1.go = "CitizenFindItem_3";
		break;
			
		case "CitizenFindItem_3":
			dialog.text = "Right past the city gates...";
			link.l1 = "Well, then I am off to search for it...";
			link.l1.go = "CitizenFindItem_4";
		break;
			
		case "CitizenFindItem_4":
			dialog.text = "Yes, please do. And hurry up – remember that you only have "+sti(NPChar.LifeDay)+" days.";
			link.l1 = "I remember.";
			link.l1.go = "exit";
			PChar.GenQuest.CitizenFindItem.StartQuest = true;
			PChar.GenQuest.CitizenFindItem.City = NPChar.City;
			PChar.GenQuest.CitizenFindItem.CitizenID = NPChar.ID;
				
			sCity = NPChar.City + "_ExitTown";
				
			//sTemp = "randitem" + (rand(1)+1); // Т.е. может получиться, что его вовсе найти не удастся. И это гуд.
			sTemp = "randitem1";
			Log_TestInfo("The ring shall be in the locator - " + sTemp);
			PChar.GenQuest.CitizenFindItem.ItemLocator = sTemp;
			ChangeItemDescribe("DOjeronRing", "itmdescr_WeddingRing");			
			items[FindItem("DOjeronRing")].Name = "itmname_WeddingRing";
			items[FindItem("DOjeronRing")].City = XI_ConvertString("Colony" + NPChar.City + "Gen");
			SetFunctionTimerCondition("CitizenFindItemMiniQuest_Timer", 0, 0, sti(NPChar.LifeDay), false);
			PChar.GenQuestRandItem.(sCity).(sTemp) = "DOjeronRing";
			SetGameModeCondition("CitizenFindItemMiniQuest_CheckItem");			
		break;
			
		case "CitizenFindItem_NoQuest":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			NPChar.CitizenFindItem.NoQuest = true; // Эта девушка квест больше не даст
		break;
			
		case "CitizenFindItem_Complete_1":
			dialog.text = ""+GetSexPhrase("Captain","young lady")+"! I am so happy! How can I ever thank you?";
			link.l1 = "Oh, no thanks needed - I did it quite unselfishly.";
			link.l1.go = "CitizenFindItem_Complete_2";
			link.l2 = "A couple of hundred pesos would certainly not hurt...";
			link.l2.go = "CitizenFindItem_Complete_3";
			RemoveItems(PChar, "DOjeronRing", 1);
			DeleteAttribute(PChar, "GenQuest.CitizenFindItem");
			NPChar.CitizenFindItem.NoQuest = true;
			PChar.Quest.CitizenFindItemMiniQuest_Timer.over = "yes";
			BackItemDescribe("DOjeronRing");
			items[FindItem("DOjeronRing")].Name = "itmname_DOjeronRing";
			DeleteAttribute(&items[FindItem("DOjeronRing")], "City");
		break;
			
		case "CitizenFindItem_Complete_2":
			dialog.text = "Oh, "+GetSexPhrase("Captain, you are such a noble person","lady, you're so noble")+"! I shall surely pray for you at the church! Farewell...";
			link.l1 = "Farewell, "+NPChar.name+".";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(PChar,"nobility" ,1);
			AddCharacterExpToSkill(PChar, "Leadership", 10);
			AddCharacterExpToSkill(PChar, "Fortune", 10);
		break;
			
		case "CitizenFindItem_Complete_3":
			iTemp = (rand(3)+1)*50;
			dialog.text = "Oh, but of course. Here -"+FindRussianMoneyString(iTemp)+". That's all I have. Please take this money... And farewell.";
			link.l1 = "Goodbye, "+GetFullName(NPChar)+".";
			link.l1.go = "exit";
			AddMoneyToCharacter(PChar, iTemp);
		break;
		// <-- Мини квест на поиск обручального кольца
		
		//=================== ноды квеста священника. поиск грабителей (квест №2)==================
		case "Citiz_GenQuest_Church_2_1":
			if(rand(3) != 1)
			{
				dialog.text = LinkRandPhrase("No, I don't know anything about it.","I don't know anything about this.","I don't know anything.");
					link.l1 = LinkRandPhrase("Alright, thanks.","I see, thank you.","Fine, please excuse me.");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("I don't know anything about it, but you can ask the patrons at the tavern - they're sure to tell you a thing or two.","I can't tell you anything. Ask around at the tavern.","I don't know anything in particular, but I've heard there was some gossip at the tavern.");
				link.l1 = "Well, it's something at least.";
				link.l1.go = "exit";
			}
			
			NPChar.GenQuest.ChurchQuest_2.AskedPeople = true;
		break;		
		
		//замечение по обнажённому оружию
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Listen - as a citizen of this town, I must ask you to refrain from walking around with an unsheathed blade.","Listen - as a citizen of this town, I must ask you to refrain from walking around with an unsheathed blade.");
				link.l1 = LinkRandPhrase("Fine.","Fine.","As you say...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Hold your horses "+GetSexPhrase("mate","lass")+" when running around with a weapon in hand. That makes me nervous...","I don't like it when "+GetSexPhrase("men","anyone")+" walk around with weapons at the ready. It scares me...");
				link.l1 = RandPhraseSimple("Got it.","I'll put it away.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

	}
}

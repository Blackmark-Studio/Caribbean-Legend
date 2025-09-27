// общий диалог ростовщиков
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, chr, sld;
	aref Link, NextDiag;
	string NPC_Area, sTemp, sTitle, sDepositType1, sDepositType2;
	int LoanSum, LoanInterest, LoanPeriod, LoanResult, iPastMonths, DepositSum, DepositInterest, DepositResult, iNum, iTemp, iTotalDublonQty;
	int iRes, iPer, iDep;
	float fPer;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	string iDay, iMonth, s1;
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;

	NPC_Area = Npchar.City;
	sDepositType1 = NPC_Area + "_Type1";
	sDepositType2 = NPC_Area + "_Type2";
 
	if(!CheckAttribute(npchar, "quest.item_date"))
	{
		npchar.quest.item_date = "";
	} 
 
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Usurer\" + NPChar.City + "_Usurer.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06

	if (!CheckAttribute(npchar, "quest.trade_date"))
    {
        npchar.quest.trade_date = "";
    }
    if (!CheckAttribute(npchar, "quest.FindCitizenNoShip"))
    {
        npchar.quest.FindCitizenNoShip = 0;
    }

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "First time":
			if (LAi_group_GetPlayerAlarm() > 0)
			{
				//--> работорговец
				if(pchar.questTemp.Slavetrader == "After_enterSoldiers" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
				{
					dialog.text = " It's over. Now leave this place, "+pchar.name+". I'll clean up all this mess.";
					link.l1 = "Alright, I'll set sail!";
					link.l1.go = "exit";
					break;
				}
				//<-- работорговец
			
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("The town is on alert and they are searching for you everywhere! If I were you I would not stay here for long.","All the guards are looking for you. I'm not an idiot and I won't risk talking to you!","Run, "+GetSexPhrase("pal","girl")+", before the soldiers turn you into a sieve..."),LinkRandPhrase("What do you want, vile creature?! The town guards are aware of your position and you won't get away, "+GetSexPhrase("filthy pirate","you pirate whore")+"!","Dirty murderer, get away from my place! Guards!","I don't fear you, vile creature! Soon you'll be hanged at our fort, you won't get away..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Heh, that's no problem for me...","They'll never catch me."),RandPhraseSimple("Shut your mouth, "+GetWorkTypeOfMan(npchar,"")+", or I will cut out your bloody tongue!","Heh, "+GetWorkTypeOfMan(npchar,"")+", want to catch a pirate too? Listen, lad, sit here quietly and you'll live..."));
				link.l1.go = "fight";
				break;
			}
		//Jason ---------------------------------------Бремя гасконца------------------------------------
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock") && pchar.location == "Fortfrance_bank")
			{
				dialog.text = "Need something, monsieur?";
				Link.l1 = "I need some information... I want to ask you about something.";
				Link.l1.go = "quests";
				Link.l2 = "How about a small loan?";
				Link.l2.go = "sharlie_credit";
				Link.l3 = "No, I've changed my mind.";
				Link.l3.go = "exit";
				if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
				{
					link.l4 = "Take a look at these earrings, monsieur. I found them in the pocket of a bandit in the jungle. This is clearly the work of a fine jeweller which, I'm sure, is not from this wilderness. What do you say?";
					link.l4.go = "Sharlie_junglejew";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskiper")
				{
					link.l1 = "I know that you have a debtor by the name of Folke Deluc. Tell me, how bad is his... delinquency?";
					link.l1.go = "Sharlie";
				}	
				if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskipermoney")
				{
					link.l1 = "I'm here about Folke Deluc's debt.";
					link.l1.go = "Sharlie_repeat";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskipercaptive")
				{
					link.l1 = "I've completed your assignment, monsieur. Here is your... Spanish friend.";
					link.l1.go = "Sharlie_14";
				}
				break;
			}			
		//<-- Бремя гасконца
			
			//--> работорговец
			if (pchar.questTemp.Slavetrader == "canTakeQuest" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "Well, at last a worthy captain has visited my place. I am so tired of idiots who think that I simply plant their doubloons and guineas and harvest them every month to pay their interest.\nThey watch every penny, having no idea how the poor usurer must resort to various tricks to avoid dying of starvation himself, while at the same time providing them with the means to buy a goose for Christmas.";
				Link.l1 = "I suppose your clients won't be glad to hear such words from the man who holds their savings.";
				Link.l1.go = "GiveTaskSlave";
				npchar.quest.slave = "current";//чтобы камнем не долбил
				break;
			}	
			
			if (pchar.questTemp.Slavetrader == "TakeShoreCap_end" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "...";
				Link.l1 = "Listen, old hamster, you really have to do your best now to explain everything to me! There were no slaves in that ship's cargo, only a company of soldiers! It was a really tough mission to deal with them! I am very angry, so you'd better explain yourself!";
				Link.l1.go = "Slaveshore_5";
				break;
			}	
			if (pchar.questTemp.Slavetrader == "Win_HavanaFort" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "Ah, here you are at last! The whole archipelago is gossiping about your bold attack. Glad to see you!";
				Link.l1 = "I would prefer obscurity to that kind of fame... It's too dangerous.";
				Link.l1.go = "Win_Havana_Fort";
				break;
			}	
			if (pchar.questTemp.Slavetrader == "Havana_seekslaves" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "Have you brought my five thousand slaves?";
				if (GetSquadronGoods(Pchar, GOOD_SLAVES) >= 5000)
				{
					Link.l1 = "I have. They are in my cargo hold.";
					Link.l1.go = "Havana_Fort_yesA";
				}
				else
				{
					Link.l1 = "No, I am still working on this.";
					Link.l1.go = "exit";
				}
				break;
			}	
			
			if (pchar.questTemp.Slavetrader == "End_quest_bad" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "Hm... You're still alive? Strange. But it won't last long. Soldiers! Help! I've got a bandit here!";
				link.l1 = "Such a bastard!";
				link.l1.go = "exit";
				LAi_group_Attack(NPChar, Pchar);
				break;
			}
			
			if(pchar.questTemp.Slavetrader == "wait_6" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_6") > 6 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "Good day. My name is "+GetFullName(npchar)+". How can I be of service?";
				link.l1 = "Oh! What are you doing here, sir?";
				link.l1.go = "Usurer_Escape";
				break;
			}
			//<-- работорговец
			// ФМК-Гваделупа
			if(CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "killers" && npchar.location == "BasTer_bank")
			{
				dialog.Text = "...";
				link.l1 = "Hey there, you bastard. Did you have a brilliant idea? Hired thugs to kill me? Wanted to shut me up? Speak, now!";
				link.l1.go = "FMQG_x";
				break;
			}
			// Леди Бет -->
			if (pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_Bank" && !CheckAttribute(pchar, "questTemp.LadyBeth_Usurer")) // Блеквуд в городе
			{
				dialog.Text = "Oh, Captain! Please, look at what I have today. Some items I acquired from Blackwood's men. They need money for a new expedition, and for us – profit, right?";
				link.l1 = "Does Blackwood know his men are selling their findings?";
				link.l1.go = "LadyBeth_Usurer_1";
				break;
			}
			// Леди Бет <--
			if(NPChar.quest.meeting == "0")
			{
				dialog.Text = LinkRandPhrase(LinkRandPhrase("Good day to you, "+GetAddress_Form(NPChar)+". How can I help you? Do I know you?","Come in, captain. My name is "+GetFullName(npchar)+" and I'm the local banker.","Nice to meet you, "+GetAddress_Form(NPChar)+"! I am a local banker, and if you've got a money problem, then I can help you."),LinkRandPhrase("Have we met before, captain? I am "+GetFullName(npchar)+", and I'm a local banker.","Come in, Captain. My name is "+GetFullName(npchar)+" and I'm the local banker.","Greetings, "+GetAddress_Form(NPChar)+". I am "+GetFullName(npchar)+", the local banker."),LinkRandPhrase("Nice to meet you, "+GetAddress_Form(NPChar)+", I am "+GetFullName(npchar)+" just a modest banker in this wonderful town.","It is your call, captain! Want to borrow some coin from me or lend money at interest?","Sir Captain! I'm so glad you've visited my modest office!"));
				link.l1 = RandPhraseSimple(LinkRandPhrase("My pleasure! I was just walking around town and decided to visit you.","My pleasure, I am "+GetFullName(pchar)+", nice to meet you.",""+GetFullName(pchar)+" , captain of the ship called "+pchar.ship.name+" , glad to meet you. This is a bank, right?"),RandPhraseSimple("Nice to meet you. I am "+GetFullName(pchar)+". A captain of a ship named "+pchar.ship.name+". I just wanted to get to know you.","Aha, so you have a bank here, right? Glad to meet you, I am "+GetFullName(pchar)+", a captain of my own vessel."));
				link.l1.go = "next";
				NPChar.quest.meeting = "1";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_bank")
				{
					dialog.text = "Lady MacArthur, welcome, do come in.";
					link.l1 = "And to you, "+npchar.lastname;
					link.l1.go = "Helen_next";
				}
			}
			else
			{
				dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("It's you! What do you want, "+GetAddress_Form(NPChar)+"?","What brings you here, captain? I'm sorry, but your reputation doesn't make you a particularly desirable client.","Aha, another client! At first I thought you were a robber... ha-ha, I'm just joking."),LinkRandPhrase("Oh! What do you want? This is a bank, not a tavern.","Good day to you, captain. I must inform you that I'm quite selective in choosing my clients.","What do you want, "+GetFullName(pchar)+"? I hope that you remember that your renown won't let you raise a large loan?"),LinkRandPhrase("I hope you want to invest money, "+GetAddress_Form(NPChar)+"? It won't be easy to secure a loan for you.","Captain "+GetFullName(pchar)+" What do you want from a humble banker? I'm sorry, but I won't be able to arrange a loan for you. Only I can lend money to you with interest.","Come in, "+GetAddress_Form(NPChar)+". I am sorry to inform you that you are not the most welcome client, but I don't usually turn people away immediately.")),LinkRandPhrase(LinkRandPhrase("Hello, sir "+GetFullName(pchar)+"! I am always ready to help you with business matters.","Hello, sir "+GetAddress_Form(NPChar)+". I am always ready to take out a loan or accept any investment.","Dear "+GetFullName(pchar)+"! Glad to see you! What do you want?"),LinkRandPhrase("Captain "+GetFullName(pchar)+"! I am always at your service. Would you like to take out a loan or invest money at interest?","Greetings to you, captain! You are always a welcome client here. You have an excellent business reputation!","Good day, "+GetFullName(pchar)+". I am glad that you've visited me again. I hope you've come for a profitable business agreement?"),LinkRandPhrase("Good day to you, captain! What do you want? Looking to take out a loan or make an investment?","Captain "+GetFullName(pchar)+"! Do you want to lend money on profitable terms? I am always glad to see such a respectable client.","Glad to see you again, captain! I am always ready to help you, whether it's raising a loan or making an investment.")));
				link.l1 = pcharrepphrase(RandPhraseSimple(LinkRandPhrase("No kidding, banker, I've got a business to run here.","Too much talking, pal. Let's get straight to business.","Have you heard that money has no smell? So hold your nose and let's get down to business."),LinkRandPhrase("And this is how you greet your clients? Lucky for you, I am in a good mood today.","Ha! Aren't you glad to see me, huh? And am I not a golden doubloon to make a positive impression on you. Anyway, let's do business, usurer.","Eh, I'd like to teach you some respect, but I have no time for this. Let's talk about money instead.")),RandPhraseSimple(LinkRandPhrase("Glad to see my old friend!","It is always a pleasure to come here, my friend. Let's get straight to business.","I am very glad as well. Let's talk business, friend."),LinkRandPhrase("Really glad to meet you. What's new on the financial seas?","Glad you still remember me. I'm in a hurry, so let's get straight to business.","Hello, old friend! Glad to see you again!")));
				link.l1.go = "next";
			}
			break;
			
			case "next":
			dialog.text = NPCStringReactionRepeat("How can I help you?","What do you want this time?","Hm... what are your concerns?","Eh, "+GetAddress_Form(npchar)+", you can't even imagine how annoying clients can be...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("No thanks, I'm just walking around and talking.","Me again. Just wanted to talk to you.","Yes, it's me again. Nothing serious, I just wanted to talk to you.","Yes, being a banker is not that easy sometimes. Just wanted to talk...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			link.l2 = "I want to discuss our financial matters.";
			link.l2.go = "LoanUsurer";//(на кредитный генератор)
			link.l3 = "I am interested in jewels and unusual idols or gemstones.";
			if (!isMultiObjectKnown("gold_dublon"))
			{
				link.l3.go = "items_0";
			}
			else
			{
				link.l3.go = "items_1";
			}	
			link.l4 = "I need some information. Well, I have something to ask you.";
			link.l4.go = "quests";//(перессылка в файл города)
//Jason, генер почтового курьера 2 уровня
			if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
			{
				if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					link.l12 = "I brought you the business papers from "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
					link.l12.go = "Postcureer_LevelUp_ForAll";
				}
			}
			//квесты мэра, проникновение во враждебный город
  			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
			{
				link.l7 = RandPhraseSimple("I am here on the orders of one man. He is a governor "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".",GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+" sent me here. I need to get something from you.");
				link.l7.go = "IntelligenceForAll";
			}
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "usurer_keeper")
			{
				link.l9 = "Good day, I was invited by your son."; 
				link.l9.go = "EncGirl_4";
				pchar.quest.EncGirl_GetLoverFather.over = "yes";
			}	
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer"))
			{
				link.l10 = "I am interested to know who the owner of the document is.";
				link.l10.go = "ShipLetters_Usurer1";			
			}
			
			//--> семейная реликвия // лесник переписал с нпчара на чара 
			if (CheckAttribute(pchar, "GenQuest.Noblelombard") && npchar.city == pchar.GenQuest.Noblelombard.City && !CheckAttribute(pchar, "quest.noblelombard"))// вот тут 
			{
				link.l11 = "I want to talk about your client's debt. His name is "+pchar.GenQuest.Noblelombard.Name+". He pawned his family relic. I represent his interests here, and I have the right to discuss its return with you.";
				link.l11.go = "Noblelombard";			
			}
			if (CheckAttribute(pchar, "GenQuest.Noblelombard.Giveregard") && npchar.city == pchar.GenQuest.Noblelombard.City)
			{
				link.l11 = "We had a meeting three months ago and talked about a man's relic. His name was "+pchar.GenQuest.Noblelombard.Name+". Remember that? He had to open a deposit in my name. The sum is  "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Regard))+"...";
				link.l11.go = "Noblelombard_5";			
			}
			//<-- семейная реликвия
			
			//-->работорговец
			if (pchar.questTemp.Slavetrader == "Seek_slaves" && pchar.questTemp.Slavetrader.UsurerId == npchar.id) 
			{
				link.l8 = "It is about your ... slave assignment.";
				link.l8.go = "Checkslaves";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goaway" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Good day, "+NPChar.name+", let's talk about your assignment.";
				link.l8.go = "Takeslaves_4_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goaway_pinas" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Good day, "+NPChar.name+", let's talk about your assignment.";
				link.l8.go = "Pinas_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "died" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Good day, "+NPChar.name+", let's talk about your assignment.";
				link.l8.go = "Takeslaves_4_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait") > 20 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "I came, as we agreed. Got a job for me?";
				link.l8.go = "Takeslaves_3";
				break;
			}
			if(pchar.questTemp.Slavetrader == "waitship" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "I came as I promised. How about a job?";
				link.l8.go = "Takeslaves_3";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_1" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_1") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Good day, "+npchar.name+". How are you doing? Got a new assignment for me?";
				link.l8.go = "EscapeSlave";
				break;
			}
			if(pchar.questTemp.Slavetrader == "escapeslave_win" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Your mission is done. I was able to find those runaways. It wasn't that easy, though.";
				link.l8.go = "Escape_slaves_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_2" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_2") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Good day, "+npchar.name+". I came for a new profitable assignment.";
				link.l8.go = "Slaveshore";
				break;
			}			
			
			if(pchar.questTemp.Slavetrader == "goodbye" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Bad news,"+npchar.name+". I failed to take the brigantine.";
				link.l8.go = "Brig_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goodbye_1" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Look,  "+npchar.name+". I chased the brigantine down, but found no papers. Are you sure they were there?";
				link.l8.go = "Letter_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "winbrig" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Good news,"+npchar.name+". I managed to hunt down that brigantine and recover the papers. Here they are.";
				link.l8.go = "Brig_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_3" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_3") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Good day, "+npchar.name+". Have you prepared a new assignment for me?";
				link.l8.go = "SlaveGalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wingalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", I managed to intercept that so-called 'galleon'.";
				link.l8.go = "Wingalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "lostgalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", I am so sorry, but I couldn't board this galleon.";
				link.l8.go = "Lostgalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_4" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_4") > 4 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Good day, "+npchar.name+". I came for my money.";
				link.l8.go = "FindRat";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wincorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", your mission is complete. That bastard Gontier is dead, and so is his crew.";
				link.l8.go = "Wincorvette";
				break;
			}
			if(pchar.questTemp.Slavetrader == "lostcorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", I am sorry, but I have failed to catch Francois Gontier, although I was following him to Tortuga. He managed to escape from me on his corvette.";
				link.l8.go = "lostcorvette";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_5" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_5") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Good day,"+npchar.name+". Tell me about this new mission you've prepared for me.";
				link.l8.go = "Havana_fort";
				break;
			}
			//<--работорговец
			NextDiag.TempNode = "First time";
		break;
		
		case "Helen_next":
			dialog.text = NPCStringReactionRepeat("I wouldn't say you're in need of money or looking to increase your wealth. What brings you to my office?","What do you want this time?","Hm... what are your concerns?","Eh, "+GetAddress_Form(npchar)+", you can't even imagine how annoying clients can be...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("No thanks, I'm just walking around and talking.","Me again. Just wanted to talk to you.","Yes, it's me again. Nothing serious, I just wanted to talk to you.","Yes, being a banker is not that easy sometimes. Just wanted to talk...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			link.l2 = "I want to discuss our financial matters.";
			link.l2.go = "LoanUsurer";//(на кредитный генератор)
			link.l3 = "I am interested in jewels, unusual idols, or gems.";
			if (!isMultiObjectKnown("gold_dublon"))
			{
				link.l3.go = "items_0";
			}
			else
			{
				link.l3.go = "items_1";
			}	
			link.l4 = "I need some information. Well, I have something to ask you.";
			link.l4.go = "quests";//(перессылка в файл города)
//Jason, генер почтового курьера 2 уровня
			if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
			{
				if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					link.l12 = "I brought you the business papers from "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
					link.l12.go = "Postcureer_LevelUp_ForAll";
				}
			}
			//квесты мэра, проникновение во враждебный город
  			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
			{
				link.l7 = RandPhraseSimple("I am here on the orders of one man. He is a governor "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".",GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+" sent me here. I have to get something from you.");
				link.l7.go = "IntelligenceForAll";
			}
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "usurer_keeper")
			{
				link.l9 = "Good day, I was invited by your son."; 
				link.l9.go = "EncGirl_4";
				pchar.quest.EncGirl_GetLoverFather.over = "yes";
			}	
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer"))
			{
				link.l10 = "I am interested to know who the document's owner is.";
				link.l10.go = "ShipLetters_Usurer1";			
			}
			
			//--> семейная реликвия // лесник переписал с нпчара на чара 
			if (CheckAttribute(pchar, "GenQuest.Noblelombard") && npchar.city == pchar.GenQuest.Noblelombard.City && !CheckAttribute(pchar, "quest.noblelombard"))// вот тут 
			{
				link.l11 = "I want to talk about your client's debt. His name is "+pchar.GenQuest.Noblelombard.Name+". He pawned his family relic. I represent his interests here, and I have the right to discuss its return with you.";
				link.l11.go = "Noblelombard";			
			}
			if (CheckAttribute(pchar, "GenQuest.Noblelombard.Giveregard") && npchar.city == pchar.GenQuest.Noblelombard.City)
			{
				link.l11 = "We had a meeting three months ago and spoke about a man's relic. His name was "+pchar.GenQuest.Noblelombard.Name+". Remember that? He had to open a deposit in my name. The sum is  "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Regard))+"...";
				link.l11.go = "Noblelombard_5";			
			}
			//<-- семейная реликвия
			
			//-->работорговец
			if (pchar.questTemp.Slavetrader == "Seek_slaves" && pchar.questTemp.Slavetrader.UsurerId == npchar.id) 
			{
				link.l8 = "It is about your ... slave assignment.";
				link.l8.go = "Checkslaves";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goaway" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Good day, "+NPChar.name+", let's talk about your assignment.";
				link.l8.go = "Takeslaves_4_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goaway_pinas" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Good day, "+NPChar.name+", let's talk about your assignment.";
				link.l8.go = "Pinas_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "died" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Good day, "+NPChar.name+", let's talk about your assignment.";
				link.l8.go = "Takeslaves_4_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait") > 20 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "I came, as we agreed. Got a job for me?";
				link.l8.go = "Takeslaves_3";
				break;
			}
			if(pchar.questTemp.Slavetrader == "waitship" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "I came as I promised. How about a job?";
				link.l8.go = "Takeslaves_3";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_1" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_1") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Good day, "+npchar.name+". How are you doing? Got a new assignment for me?";
				link.l8.go = "EscapeSlave";
				break;
			}
			if(pchar.questTemp.Slavetrader == "escapeslave_win" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Your mission is done. I was able to find those runaways. It wasn't that easy, though.";
				link.l8.go = "Escape_slaves_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_2" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_2") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Good day, "+npchar.name+". I came for a new profitable assignment.";
				link.l8.go = "Slaveshore";
				break;
			}			
			
			if(pchar.questTemp.Slavetrader == "goodbye" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Bad news,"+npchar.name+". I failed to get the brigantine.";
				link.l8.go = "Brig_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goodbye_1" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Look,  "+npchar.name+". I have chased down the brigantine, but I found no papers. Are you sure they were there?";
				link.l8.go = "Letter_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "winbrig" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Good news,"+npchar.name+". I managed to hunt down that brigantine and retrieve the papers. Here they are.";
				link.l8.go = "Brig_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_3" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_3") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Good day, "+npchar.name+". Have you prepared a new assignment for me?";
				link.l8.go = "SlaveGalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wingalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", I managed to intercept that so-called 'galleon'.";
				link.l8.go = "Wingalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "lostgalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", I am so sorry, but I couldn't board this galleon.";
				link.l8.go = "Lostgalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_4" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_4") > 4 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Good day, "+npchar.name+". I came for my money.";
				link.l8.go = "FindRat";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wincorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", your mission is complete. That bastard Gontier is dead, and so is his crew.";
				link.l8.go = "Wincorvette";
				break;
			}
			if(pchar.questTemp.Slavetrader == "lostcorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", I am sorry, but I have failed to catch Francois Gontier, although I followed him to Tortuga. He managed to escape from me on his corvette.";
				link.l8.go = "lostcorvette";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_5" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_5") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Good day,"+npchar.name+". Tell me about this new mission you've prepared for me.";
				link.l8.go = "Havana_fort";
				break;
			}
			//<--работорговец
			NextDiag.TempNode = "First time";
		break;

		case "items_0":
			dialog.text = "Want to buy some golden doubloons or chests for them? Trust me, it's a very valuable investment.";
			link.l1 = "Yes, that's very interesting.";
			link.l1.go = "items";
			AddQuestRecordInfo("Recipe", "Gold_dublon");
			SetAlchemyRecipeKnown("gold_dublon");
			SetAlchemyRecipeKnown("Chest");
			npchar.quest.meeting = "1"; 			
		break;
		
		case "items_1":
			dialog.text = "Do you want to trade in pesos or doubloons?";
			link.l1 = "For pesos.";
			link.l1.go = "items";
			link.l2 = "For doubloons.";
			link.l2.go = "items_dub";
		break;
		
		case "items":
			if (npchar.quest.item_date != lastspeak_date)
			{
				GiveItemToTrader(npchar);
				npchar.quest.item_date = lastspeak_date;
			}
			if(CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu")) AddItems(npchar, "gold_dublon", 100);
			if(CheckAttribute(pchar, "questTemp.Del_Rostovshik_repeat")) AddItems(npchar, "gold_dublon", 100);
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
			LaunchItemsTrade(NPChar, 0);
		break;
		
		case "items_dub":
			if (npchar.quest.item_date != lastspeak_date)
			{
				GiveItemToTrader(npchar);
				npchar.quest.item_date = lastspeak_date;
			}
			if(CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu")) AddItems(npchar, "gold_dublon", 100);
			if(CheckAttribute(pchar, "questTemp.Del_Rostovshik_repeat")) AddItems(npchar, "gold_dublon", 100);
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
			LaunchItemsTrade(NPChar, 1);
		break;
		
		//<<<<----------генератор -"Shipping documents". ------		
		case "ShipLetters_Usurer1":
			pchar.questTemp.different.GiveShipLetters.speakUsurer = true;
			dialog.text = "It will take a lot of my time to read these papers and my time costs a lot.";
			link.l1 = "Perhaps, "+sti(pchar.questTemp.different.GiveShipLetters.price1)+" pesos will compensate you for your time?";
			link.l1.go = "ShipLetters_Usurer2";
			link.l2 = "As you wish. Farewell!";
			link.l2.go = "exit";
		break;
		
		case "ShipLetters_Usurer2":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.GiveShipLetters.price1));
			pchar.questTemp.different.GiveShipLetters.speakUsurer_1 = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Let me have a look! No, I've never seen this name before. Show it to our harbour master.";
				link.l1 = "I am sorry, but we had a deal! You promised to tell me about this captain!";
				link.l1.go = "ShipLetters_Usurer2_1";
			}
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
			{
				s1 = "Well... I know the owner of this ship. He is not a very rich man, but he has some wealth.";
				dialog.text = s1+" They say he's a successful smuggler. Is that what you wanted to hear?";
				link.l1 = "It seems so...";
				link.l1.go = "ShipLetters_Usurer2_2";
			}
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
			{
				s1 = "Well... I am not sure that I can congratulate you for your found.";
				dialog.text = s1+"These documents are signed for our colonial patrol ship, and its captain is known for his strong principles.";
				link.l1 = "A patrol? Under the commandant's orders?";
				link.l1.go = "ShipLetters_Usurer2_3";
			}
		break;
		
		case "ShipLetters_Usurer2_1":
			dialog.text = "I promised you I would take a look at those papers and nothing more. You can go.";
			link.l1 = "Thanks... I suppose.";
			link.l1.go = "exit";
		break;
		
		case "ShipLetters_Usurer2_2":
			dialog.text = "It's your call. Our commandant has been showing quite an 'interest' in this one person, for a long time. Got any ideas already? And here we have bills of lading with no marks on them...";
			link.l1 = "I see. My thanks!";
			link.l1.go = "exit";		
		break;
		
		case "ShipLetters_Usurer2_3":
			s1 = "Exactly. Our smugglers are bearing a grudge against this captain by the way.";
			dialog.text = s1+"And as I mentioned before, the paper's owner is a man of principle and doesn't really like local crimes.";
			link.l1 = "I see. My gratitude!";
			link.l1.go = "exit";		
		break;

		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "Ah, I take it you are the captain who brought my prodigal son and his young bride?";
				link.l1 = "Yes, it was I who helped them to escape.";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "Ah, here you are, my benefactor. Waiting for a reward, I suppose?";
				link.l1 = "Your thanks would be enough, at least...";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "I am truly grateful for helping my child and not leaving him in that troublesome situation. Please, allow me to thank you as best I can. Accept this modest sum and a small gift from me.";
			link.l1 = "My thanks. It was my pleasure to help this young couple.";
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = "Thanks? For what? This blockhead was unemployed for half the year and he's already found time to get himself a girl! I was running my own business at his age. There's a marriageable governor's daughter, and he brings this whore here—Lord, forgive me for saying it! And now he's looking for my blessing!";
			link.l1 = "I take it that you don't believe in feelings?";
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
			dialog.text = "Feelings? What kind of feelings? You are a grown man and you talk about feelings too? Shame on you for pandering to the young. You took the girl from her parents and ruined my son's life. You won't get any thanks from me. Farewell.";
			link.l1 = "Goodbye then...";
			link.l1.go = "EncGirl_6_2";
		break;
		
		case "EncGirl_6_2":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddQuestRecord("JungleGirl", "19");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("saw","saw"));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("",""));
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();		
		break;
		
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////		Кредитный генератор Loan
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "LoanUsurer":
			if (npchar.id == "Panama_Usurer")
			{
				if (sti(pchar.reputation.nobility) > 70 && ChangeCharacterNationReputation(pchar, SPAIN, 0) >= 80 && !CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold"))
				{
					dialog.text = "Let's discuss it. I'm listening.";
				}
				else
				{
					dialog.text = "Uh, uh. I'm afraid I must refuse you. "+GetAddress_Form(NPChar)+". I'm sorry, but my bank does not provide services to the enemies of Spain.";
					link.l1 = "Money has no nationality, señor banker.";
					if (CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold"))
					{
						if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)) && makeint(Pchar.Quest.Deposits.(sDepositType1)) == true)
						{
							dialog.text = "Mm-hmm, "+GetAddress_Form(NPChar)+". I must inform you that your deposit is no longer valid.";
							Link.l1 = "On what grounds?!";
							Link.l1.go = "Panama_Deposit_SgorelVklad";
							DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
							break;						
						}
						else
						{
							link.l1.go = "Panama_Deposit_Cartahena";
							break;
						}
					}
					if (sti(pchar.reputation.nobility) < 71 || ChangeCharacterNationReputation(pchar, SPAIN, 0) < 80)
					{
						link.l1.go = "Panama_Deposit_NoReputation";
						break;
					}
				}
			}
			dialog.text = "Let's discuss it. I'm listening.";
			//кредиты
            if(CheckAttribute(Pchar, "Quest.Loans." + (NPC_Area)) && makeint(Pchar.Quest.Loans.(NPC_Area)) == true)
			{
				iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Loans.(NPC_Area).StartYear),makeint(Pchar.Quest.Loans.(NPC_Area).StartMonth),makeint(Pchar.Quest.Loans.(NPC_Area).StartDay), makefloat(Pchar.Quest.Loans.(NPC_Area).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
				Pchar.Quest.Loans.(NPC_Area).Result = makeint(Pchar.Quest.Loans.(NPC_Area).Sum) + ((makeint(Pchar.Quest.Loans.(NPC_Area).Sum)/100)*makefloat(Pchar.Quest.Loans.(NPC_Area).Interest))*(iPastMonths+1);// boal 23.01.2004
				if(makeint(PChar.money) >= makeint(Pchar.Quest.Loans.(NPC_Area).Result))
				{
					Link.l5 = "I owe you "+FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).Result))+LinkRandPhrase(", I am ready to return your money",". I want to repay the debt.",".  At last, it's time to settle up.");
					Link.l5.go = "loan_return";	
					sTemp = "credit";
				}					
			}
			else
			{
				Link.l6 = LinkRandPhrase("I'd like to borrow some coins.","I really need to get some pesos.","How about a small loan?");
				Link.l6.go = "loan";					
				if(makeint(Pchar.money) >= 100)
				{
					Link.l7 = LinkRandPhrase("I would like to deposit my money to earn interest.","Would you agree to keep a few sacks of my silver?","May I leave you some silver for a rainy day?"); // patch
					Link.l7.go = "deposit";				
				}			
				if(CheckUseDublons(NPChar))
				{
					Link.l8 = "I want to deposit some doubloons for interest.";
					Link.l8.go = "deposit_dub";				
				}
			}
			
			if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)) && makeint(Pchar.Quest.Deposits.(sDepositType1)) == true)
			{
				iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Deposits.(sDepositType1).StartYear),makeint(Pchar.Quest.Deposits.(sDepositType1).StartMonth),makeint(Pchar.Quest.Deposits.(sDepositType1).StartDay), makefloat(Pchar.Quest.Deposits.(sDepositType1).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
				if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)+ ".Rem"))
				{
					Pchar.Quest.Deposits.(sDepositType1).Result = makeint(Pchar.Quest.Deposits.(sDepositType1).Sum) + ((makeint(Pchar.Quest.Deposits.(sDepositType1).Sum)/100)*makefloat(Pchar.Quest.Deposits.(sDepositType1).Interest))*iPastMonths+sti(Pchar.Quest.Deposits.(sDepositType1).Rem);
				}
				else
				{
					Pchar.Quest.Deposits.(sDepositType1).Result = makeint(Pchar.Quest.Deposits.(sDepositType1).Sum) + ((makeint(Pchar.Quest.Deposits.(sDepositType1).Sum)/100)*makefloat(Pchar.Quest.Deposits.(sDepositType1).Interest))*iPastMonths;
				}
				Link.l9 = LinkRandPhrase("I'm here to get my investment back, in pesos.","It's time to get back the silver you owe me.","I need my investment back in pesos, with all the interest.");
				Link.l9.go = "Deposit_return";									
			}
			
			if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType2)) && makeint(Pchar.Quest.Deposits.(sDepositType2)) == true)
			{
				iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Deposits.(sDepositType2).StartYear),makeint(Pchar.Quest.Deposits.(sDepositType2).StartMonth),makeint(Pchar.Quest.Deposits.(sDepositType2).StartDay), makefloat(Pchar.Quest.Deposits.(sDepositType2).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
				if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType2)+ ".Rem"))
				{
					Pchar.Quest.Deposits.(sDepositType2).Result = makeint(Pchar.Quest.Deposits.(sDepositType2).Sum) + ((makeint(Pchar.Quest.Deposits.(sDepositType2).Sum)/100)*makeint(Pchar.Quest.Deposits.(sDepositType2).Interest))*iPastMonths+sti(Pchar.Quest.Deposits.(sDepositType2).Rem);
				}
				else
				{
					Pchar.Quest.Deposits.(sDepositType2).Result = makeint(Pchar.Quest.Deposits.(sDepositType2).Sum) + ((makeint(Pchar.Quest.Deposits.(sDepositType2).Sum)/100)*makeint(Pchar.Quest.Deposits.(sDepositType2).Interest))*iPastMonths;
				}
				Link.l10 = LinkRandPhrase("I want to reclaim my investment in doubloons.","It's time to get back the gold you owe me.","I need my investment in doubloons back, with all the interest.");
				Link.l10.go = "Deposit_return_dub";									
			}
/*			
			
*/			
			//выход
			if (sTemp == "credit")
			{
				link.l11 = "I remember my debt, yet I am not ready to pay it...";
				link.l11.go = "Loan_Remind";
			}
			else
			{
				link.l11 = "My mistake, I have no financial matters with you. Farewell.";
				link.l11.go = "exit";
			}
		break;
		
		//============== кредиты ===============
		case "loan":
            if (sti(NPChar.nation) == PIRATE)
            {
                dialog.text = "No, I can't help you. I can only accept investments in this troublesome place. You can invest silver pesos or golden doubloons.";				
                if(makeint(Pchar.money) >= 100)
				{
	                Link.l1 = "I want to invest pesos, so let's talk about the amount.";
	                Link.l1.go = "deposit";
				}				
				if(CheckUseDublons(NPChar))
				{
					Link.l2 = "I want to invest doubloons. Let's clarify the amount.";
					Link.l2.go = "deposit_dub";
				}
                Link.l3 = "Not interested.";
				link.l3.go = "exit";
                break;
            }
			// проверка на проф пригодность -->
            if (isBadReputation(pchar, 42))
            {
                dialog.text = RandSwear()+"Your name is "+GetFullName(pchar)+", right? You have "+RandPhraseSimple("a bad reputation ","a bad reputation ")+" and I don't want to do business with you.";
				link.l1 = RandPhraseSimple("Can't a man make a mistake?",RandSwear()+"Whatever!");
				link.l1.go = "exit";
                break;
            }
            // проверка на проф пригодность <--
			Dialog.snd = "voice\USDI\USDI016";
			dialog.text = "Oh, you are always welcome. What sum do you need?";
			Link.l1 = "A small one.";
			Link.l1.go = "Small";
			Link.l2 = "Moderate.";
			Link.l2.go = "Medium";
			Link.l3 = "As big as possible.";
			Link.l3.go = "Large";
		break;

		case "small":
			Pchar.Quest.Loans.(NPC_Area).Sum = 500*makeint(Pchar.rank)+125*GetSummonSkillFromName(pchar,SKILL_COMMERCE);
			Dialog.snd = "voice\USDI\USDI017";
			dialog.text = "Excellent! It's always much easier to deal with small sums – less risk for both sides. I can offer you "+FindRussianMoneyString(sti(Pchar.Quest.loans.(NPC_Area).sum))+"...";
			Link.l1 = "Deal. And what about your share?";
			Link.l1.go = "Interest";
			Link.l2 = "It won't work for me. Let's change it.";
			Link.l2.go = "Loan";
			Link.l3 = "I suppose it's better not to get into debt because of me. Farewell.";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "Medium":
			Pchar.Quest.Loans.(NPC_Area).Sum = 1500*makeint(Pchar.rank)+325*GetSummonSkillFromName(pchar,SKILL_COMMERCE);
			Dialog.snd = "voice\USDI\USDI018";
			dialog.text = "No problem. I hope that "+FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).sum))+" will help you solve your problems. This is quite a substantial sum.";
			Link.l1 = "Deal. And what about your share?";
			Link.l1.go = "Interest";
			Link.l2 = "It won't work for me. Let's change it.";
			Link.l2.go = "Loan";
			Link.l3 = "I suppose it's better for me to stay away from debts. Farewell.";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "Large":
			Pchar.Quest.Loans.(NPC_Area).Sum = 4000*makeint(Pchar.rank)+600*GetSummonSkillFromName(pchar,SKILL_COMMERCE);
			Dialog.snd = "voice\USDI\USDI019";
			dialog.text = "Well... it's risky. Fine, I am ready to grant you a loan for "+FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).sum))+". I hope you understand, captain, this is a truly substantial sum. I ask you to take it seriously.";
			Link.l1 = "Deal. And what about your share?";
			Link.l1.go = "Interest";
			Link.l2 = "It won't work for me. Let's change it.";
			Link.l2.go = "Loan";
			Link.l3 = "I suppose it's better for me to stay away from debts. Farewell.";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "Interest":
			Pchar.Quest.Loans.(NPC_Area).Interest = 4.0 + (makeint((((6.0 - 4.0) * (GetSummonSkillFromName(pchar, "Commerce") + GetSummonSkillFromName(pchar, "Leadership")) / 200) ) / 0.5 + 0.5)) * 0.5;
			//Pchar.Quest.Loans.(NPC_Area).Interest = 16 - makeint(Pchar.skill.commerce);
			// Rebbebion, добавил фикс отображения знака процента
			Dialog.snd = "voice\USDI\USDI020";
			dialog.text = fts(stf(Pchar.Quest.Loans.(NPC_Area).Interest), 1)+"%% per month. I can't offer you better terms based on what I know about you."; 
			Link.l1 = "Works for me. Let's talk about time.";
			Link.l1.go = "Period";
			Link.l3 = "I suppose it's better for me to stay away from debts. Farewell.";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "Period":
			Pchar.Quest.Loans.(NPC_Area).Period = makeint(makeint(Pchar.reputation.nobility)/20) + 1;			
			Dialog.snd = "voice\USDI\USDI021";
			dialog.text = "Taking into account what I know about you, "+Pchar.name+", I'll wait for the return of this loan for "+FindRussianMonthString(sti(Pchar.Quest.Loans.(NPC_Area).Period))+". After that, I will take certain measures. I hope you understand that."; 
			Link.l1 = "I gladly accept your terms... and your coins.";
			Link.l1.go = "LoanGranted";
			Link.l3 = "Excuse me, but that won't work for me. Farewell.";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "LoanGranted":
			Dialog.snd = "voice\USDI\USDI022";
			dialog.text = "I am sincerely glad. But let me warn you. I have been doing this for a long time, and I know how to recover my investments. So if you ever have any foolish ideas, I suggest you leave them be\nNo offence, just a warning.";
			Link.l1 = "Hm... Well. Farewell.";
			Link.l1.go = "LoanGranted_exit";
		break;

		case "Loan_Remind":
			Dialog.snd = "voice\USDI\USDI023";
			dialog.text = "It's your choice, captain. My interest is growing and you don't have that much time.";
			Link.l1 = "Don't worry about it. See you.";
			Link.l1.go = "exit";
		break;

		case "loan_return":
			addMoneyToCharacter(Pchar, -(makeint(Pchar.Quest.Loans.(NPC_Area).Result)));
			// boal 27.01.2004 -->
            if (npchar.quest.trade_date != lastspeak_date) // дыра с прокачкой была
            {
    			AddCharacterExpToSkill(Pchar, "Commerce", makeint(Pchar.Quest.Loans.(NPC_Area).Result) / 350);
    			AddCharacterExpToSkill(Pchar, "Leadership", makeint(Pchar.Quest.Loans.(NPC_Area).Result) / 700);
			}
			// boal 27.01.2004 <--
			DeleteAttribute(PChar, "quest.Loans_" + NPC_Area); // bug fix
			DeleteAttribute(PChar, "quest.Loans." + NPC_Area);
			Dialog.snd1 = "voice\USDI\USDI024";
			Dialog.snd2 = "voice\USDI\USDI025";
			Dialog.snd3 = "voice\USDI\USDI026";
			dialog.text = LinkRandPhrase("Wonderful! Come to me when you need coins. I will be at your service at any time.","My gratitude. It is always a pleasure to deal with a man who is able to repay his debts on time. Things happen sometimes, and I can understand it, you know... but I prefer problems to be solved.","Oh, I was right to trust you, "+GetAddress_Form(NPChar)+"! I hope this won't be the last time you use my services. Perhaps we can strike even better deals for you, now that I know you're an honest man.");
			Link.l1 = LinkRandPhrase("I want to borrow some money.","I really need to get some pesos.","How about a small loan?");
			Link.l1.go = "loan";			
			if(makeint(PChar.money) >= 100)
			{
				Link.l2 = LinkRandPhrase("I'd like to invest my money.","Will you keep some pirate booty?","May I leave you some silver for a rainy day?");
				Link.l2.go = "deposit";				
			}		
			if(CheckUseDublons(NPChar))	
			{
				Link.l3 = "I want to invest some doubloons for interest";
				Link.l3.go = "deposit_dub";				
			}
			Link.l4 = "Farewell, "+NPchar.name+".";
			Link.l4.go = "ExitDelLoan1";
		break;

		case "deposit":
			dialog.text = LinkRandPhrase("I see a wise man! What sum would you like to invest?","Fine. Trust me, this sum will wait for you here in safety and with all its interest.","I see that you know what's truly important in this life. How much would you like to invest?");
			link.l1.edit = 3;
			link.l1 = "";	
			Link.l1.go = "result";
		break;
		
		case "result":
			Pchar.QuestTemp.Deposits.(sDepositType1).Interest = GetDepositRate();
			Pchar.QuestTemp.Deposits.(sDepositType1).Sum = dialogEditStrings[3];
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp <= 0)
			{
				dialog.text = "Joking, huh?";
				link.l1 = "My mistake.";
				link.l1.go = "exit";
				break;
			}
			if (iTemp > sti(pchar.money))
			{
				dialog.text = "Hm, unfortunately you don't have that much money. Let's be serious...";
				link.l1 = "Fine.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Alright. I can offer you... let's say..."+fts(stf(Pchar.QuestTemp.Deposits.(sDepositType1).Interest), 1)+" %. Per month, of course.";
			Link.l1 = "It works for me.";
			Link.l1.go = "Deposit_placed";
			Link.l2 = "I'd better change the amount.";
			Link.l2.go = "Deposit";
			Link.l3 = "Looks like this was a bad idea... Farewell.";
			Link.l3.go = "Exit";
		break;

		case "Deposit_placed":
			Dialog.snd = "voice\USDI\USDI033";
			if ( !CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)+".Result"))
			{
			    Pchar.Quest.Deposits.(sDepositType1).Result = 0;//fix
			}
			// boal limit
			if ( (sti(Pchar.Quest.Deposits.(sDepositType1).Result) + sti(Pchar.QuestTemp.Deposits.(sDepositType1).Sum)) > sti(NPChar.UsurerDeposit)*1000)
			{
			    dialog.text = "Pardon me, captain, but this sum is too large for my colonial bank. I won't be able to pay you your interest. And the lack of a reliable guard... I hope you understand. Anyway, the maximum sum I can accept from you is "+FindRussianMoneyString(MakeMoneyShow(sti(NPChar.UsurerDeposit)*1000,MONEY_SIGN,MONEY_DELIVER))+".";
				Link.l1 = "Too bad, I have to find another banker then.";
				Link.l1.go = "Exit";
			}
			else
			{
				dialog.text = "You can be confident now that even the fiercest storm wouldn't leave you without a coin.";
				Link.l1 = "Alright. See you.";
				Link.l1.go = "Deposit_Exit";
			}
		break;
		
		case "Deposit_return":
			Dialog.snd = "voice\USDI\USDI034";
			dialog.text = "Considering the promised interest and the time that has passed, I owe you "+FindRussianMoneyString(sti(Pchar.Quest.Deposits.(sDepositType1).Result))+"... Are you sure you want to take the money?";
			Link.l1 = "Absolutely. Give it to me.";			
			Link.l1.go = "Deposit_return_1";		
			Link.l2 = "I want to take part of my money.";			
			Link.l2.go = "Deposit_return_part";
			Link.l3 = "You are right. I'll let it stay with you for a while. Have a good day.";			
			Link.l3.go = "Exit";		
		break;		
		
		case "Deposit_exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)+ ".Rem"))
			{
				DeleteAttribute(Pchar,"Quest.Deposits." + (sDepositType1)+ ".Rem");
			}
			Pchar.Quest.Deposits.(sDepositType1).Interest = stf(Pchar.QuestTemp.Deposits.(sDepositType1).Interest);
			Pchar.Quest.Deposits.(sDepositType1).Sum      = sti(Pchar.QuestTemp.Deposits.(sDepositType1).Sum);
			Pchar.Quest.Deposits.(sDepositType1).city 	  = NPC_Area;	

			AddMoneyToCharacter(Pchar, -(makeint(Pchar.Quest.Deposits.(sDepositType1).Sum)));
			// общий долг
			Pchar.Quest.Deposits.(sDepositType1).Sum = sti(Pchar.Quest.Deposits.(sDepositType1).Result) + sti(Pchar.Quest.Deposits.(sDepositType1).Sum);
			Pchar.Quest.Deposits.(sDepositType1) = true;
			Pchar.Quest.Deposits.(sDepositType1).StartDay 	= getDataDay();
			Pchar.Quest.Deposits.(sDepositType1).StartMonth = getDataMonth();
			Pchar.Quest.Deposits.(sDepositType1).StartYear 	= getDataYear();
			Pchar.Quest.Deposits.(sDepositType1).StartTime 	= getTime();
			DialogExit();
		break;
		
		//--> Jason забор денег по частям
		case "Deposit_return_part":
			dialog.text = "And how much?";
			link.l1.edit = 4;
			link.l1 = "";	
			Link.l1.go = "result_part";
		break;

		case "result_part":
			iTemp = sti(dialogEditStrings[4]);
			if (iTemp <= 0)
			{
				dialog.text = "That was such a stupid joke, sir!";			
				link.l1 = "Damn! I'm so sorry... Let's change the sum.";	
				Link.l1.go = "Deposit_return_part";
				break;
			}
			if (iTemp > sti(Pchar.Quest.Deposits.(sDepositType1).Result))
			{
				dialog.text = "You don't have that much money in your account.";			
				link.l1 = "Damn! My mistake. Let's change the amount.";	
				Link.l1.go = "Deposit_return_part";
				break;
			}
			if (iTemp == sti(Pchar.Quest.Deposits.(sDepositType1).Result))
			{
				dialog.text = "All of it? Fine, as you say. Here is your money.";			
				link.l1 = "Thank you!";	
				Link.l1.go = "Deposit_return_all";
				break;
			}
			dialog.text = "Fine. Take it. Here is your money.";			
			link.l1 = "Thanks!";	
			Link.l1.go = "result_part_1";
		break;
		
		case "result_part_1":
			DialogExit();
			iTemp = sti(dialogEditStrings[4]);
			addMoneyToCharacter(Pchar, iTemp);
			iRes = sti(Pchar.Quest.Deposits.(sDepositType1).Result)-iTemp; //остаток на счете
			fPer = stf(Pchar.Quest.Deposits.(sDepositType1).Interest);
			iDep = sti(Pchar.Quest.Deposits.(sDepositType1).Sum); //стартовая сумма
			if (iRes <= sti(Pchar.Quest.Deposits.(sDepositType1).Sum)) // стало меньше начальной суммы
			{
				DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
				Pchar.Quest.Deposits.(sDepositType1).Interest = fPer;
				Pchar.Quest.Deposits.(sDepositType1).Sum = iRes;
				Pchar.Quest.Deposits.(sDepositType1).Result = 0;
			}
			else // если остаток больше начальной суммы - проценты продолжаем считать с неё, а не с остатка, ибо нефиг, дельту приплюсуем к набежавшим процентам - банкир Jason :) 
			{
				DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
				Pchar.Quest.Deposits.(sDepositType1).Interest = fPer;
				Pchar.Quest.Deposits.(sDepositType1).Sum = iDep;
				Pchar.Quest.Deposits.(sDepositType1).Rem = iRes-iDep;
			}
			Pchar.Quest.Deposits.(sDepositType1).city 	  	= NPC_Area;	
			Pchar.Quest.Deposits.(sDepositType1) 			= true;
			Pchar.Quest.Deposits.(sDepositType1).StartDay 	= getDataDay();
			Pchar.Quest.Deposits.(sDepositType1).StartMonth = getDataMonth();
			Pchar.Quest.Deposits.(sDepositType1).StartYear 	= getDataYear();
			Pchar.Quest.Deposits.(sDepositType1).StartTime 	= getTime();
		break;
		
		case "Deposit_return_all":
			DialogExit();
			iTemp = sti(dialogEditStrings[4]);
			addMoneyToCharacter(Pchar, iTemp);
			DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
		break;
		//<-- забор денег по частям		
		
		case "Deposit_return_1":
			addMoneyToCharacter(Pchar, makeint(Pchar.Quest.Deposits.(sDepositType1).Result));
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = "Oh... It's so hard to lose it. I've really grown used to this money. Come again anyway.";			
			Link.l1 = "I will if I need to. Farewell.";			
			Link.l1.go = "Exit";
			DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
		break;
		
		//  ugeen -> вклады в дублонах	
		case "deposit_dub":
			dialog.text = LinkRandPhrase("I see a wise man! What sum would you like to invest?","Fine. Trust me, this sum will wait for you here in safety and with all your interest.","I see that you know what's really important in this life. How much would you like to invest?");
			link.l1.edit = 3;
			link.l1 = "";	
			Link.l1.go = "result_dub";
		break;
		
		case "result_dub":		
			iTotalDublonQty = GetCharacterItem(pchar,"gold_dublon") + CheckItemMyCabin("gold_dublon");		
			Pchar.QuestTemp.Deposits.(sDepositType2).Interest = 1;
			Pchar.QuestTemp.Deposits.(sDepositType2).Sum = dialogEditStrings[3];
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp <= 0)
			{
				dialog.text = "Joking, huh?";
				link.l1 = "Hm, my mistake...";
				link.l1.go = "exit";
				break;
			}						
			if (iTemp > iTotalDublonQty)
			{
				dialog.text = "Hm, unfortunately you don't have that much money. Let's be serious...";
				link.l1 = "Hm... good.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Alright. I can offer you... let's say..."+Pchar.QuestTemp.Deposits.(sDepositType2).Interest+" %. Per month, of course.";
			Link.l1 = "Works for me.";
			Link.l1.go = "Deposit_placed_dub";
			Link.l2 = "I'd better change the amount.";
			Link.l2.go = "Deposit_dub";
			Link.l3 = "I suppose it's better to keep my gold. Farewell.";
			Link.l3.go = "Exit";
		break;
		
		case "Deposit_placed_dub":
			Dialog.snd = "voice\USDI\USDI033";
			if ( !CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType2)+".Result"))
			{
			    Pchar.Quest.Deposits.(sDepositType2).Result = 0;//fix
			}
			// boal limit
			if ( (sti(Pchar.Quest.Deposits.(sDepositType2).Result) + sti(Pchar.QuestTemp.Deposits.(sDepositType2).Sum)) > sti(NPChar.UsurerDeposit)*10)
			{
			    dialog.text = "Pardon me, captain, but this sum is too large for my colonial bank. I won't be able to pay you your interest. And the lack of a reliable guard... I hope you understand. Anyway, the maximum sum I can accept from you is "+FindRussianDublonString(MakeMoneyShow(sti(NPChar.UsurerDeposit)*10,MONEY_SIGN,MONEY_DELIVER))+".";
				Link.l1 = "Too bad, I'll have to find another banker then.";
				Link.l1.go = "Exit";
			}
			else
			{
				dialog.text = "You can be confident now that even the strongest storm wouldn't leave you without a coin.";
				Link.l1 = "Nice. Farewell.";
				Link.l1.go = "Deposit_Exit_dub";
			}
		break;
		
		case "Deposit_return_dub":
			Dialog.snd = "voice\USDI\USDI034";
			dialog.text = "Considering the promised interest and the time that has passed, I owe you "+FindRussianDublonString(sti(Pchar.Quest.Deposits.(sDepositType2).Result))+"... Are you sure you want to take the money?";
			Link.l1 = "Absolutely. Give it to me.";			
			Link.l1.go = "Deposit_return_dub_1";		
			Link.l2 = "I want to take part of my money.";			
			Link.l2.go = "Deposit_return_dub_part";
			Link.l3 = "You are right. I'll let it stay with you for a while. Have a good day.";			
			Link.l3.go = "Exit";		
		break;	

		case "Deposit_exit_dub":
			NextDiag.CurrentNode = NextDiag.TempNode;		
			if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType2)+ ".Rem"))
			{
				DeleteAttribute(Pchar,"Quest.Deposits." + (sDepositType2)+ ".Rem");
			}	
			Pchar.Quest.Deposits.(sDepositType2).Interest = sti(Pchar.QuestTemp.Deposits.(sDepositType2).Interest);
			Pchar.Quest.Deposits.(sDepositType2).Sum      = sti(Pchar.QuestTemp.Deposits.(sDepositType2).Sum);
			Pchar.Quest.Deposits.(sDepositType2).city 	  = NPC_Area;	
			
			iTemp = GetCharacterItem(pchar,"gold_dublon");
			if(iTemp > sti(Pchar.Quest.Deposits.(sDepositType2).Sum))
			{
				TakeNItems(pchar,"gold_dublon", -sti(Pchar.Quest.Deposits.(sDepositType2).Sum));
			}
			else
			{
				TakeNItems(pchar,"gold_dublon", -iTemp));
				iTemp = sti(Pchar.Quest.Deposits.(sDepositType2).Sum) - iTemp;
				GetItemMyCabin("gold_dublon", iTemp);
			}
						
			// общий долг
			Pchar.Quest.Deposits.(sDepositType2).Sum = sti(Pchar.Quest.Deposits.(sDepositType2).Result) + sti(Pchar.Quest.Deposits.(sDepositType2).Sum);
			Pchar.Quest.Deposits.(sDepositType2) = true;
			Pchar.Quest.Deposits.(sDepositType2).StartDay 	= getDataDay();
			Pchar.Quest.Deposits.(sDepositType2).StartMonth = getDataMonth();
			Pchar.Quest.Deposits.(sDepositType2).StartYear 	= getDataYear();
			Pchar.Quest.Deposits.(sDepositType2).StartTime 	= getTime();
			DialogExit();
		break;	
		
		//-->забор дублонов по частям
		case "Deposit_return_dub_part":
			dialog.text = "And how much?";
			link.l1.edit = 4;
			link.l1 = "";	
			Link.l1.go = "result_dub_part";
		break;
		
		case "result_dub_part":
			iTemp = sti(dialogEditStrings[4]);
			if (iTemp <= 0)
			{
				dialog.text = "Such a foolish joke, sir!";			
				link.l1 = "Damn! I'm so sorry... Let's change the sum...";	
				Link.l1.go = "Deposit_return_dub_part";
				break;
			}			
			if (iTemp > sti(Pchar.Quest.Deposits.(sDepositType2).Result))
			{
				dialog.text = "You don't have that much gold in your account, sir.";			
				link.l1 = "Damn! My mistake. Let's change the amount...";	
				Link.l1.go = "Deposit_return_dub_part";
				break;
			}			
			if (iTemp == sti(Pchar.Quest.Deposits.(sDepositType2).Result))
			{
				dialog.text = "All of it? Fine, as you say. Here is your money.";			
				link.l1 = "Thanks!";	
				Link.l1.go = "Deposit_return_dub_all";
				break;
			}
			dialog.text = "Fine. Take it. Here is your money.";			
			link.l1 = "Thank you!";	
			Link.l1.go = "result_dub_part_1";
		break;
		
		case "result_dub_part_1":
			DialogExit();
			iTemp = sti(dialogEditStrings[4]);
			TakeNItems(pchar,"gold_dublon", iTemp);
			iRes = sti(Pchar.Quest.Deposits.(sDepositType2).Result)-iTemp; //остаток на счете
			iPer = sti(Pchar.Quest.Deposits.(sDepositType2).Interest);
			iDep = sti(Pchar.Quest.Deposits.(sDepositType2).Sum); //стартовая сумма
			if (iRes <= sti(Pchar.Quest.Deposits.(sDepositType2).Sum)) // стало меньше начальной суммы
			{
				DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType2));
				Pchar.Quest.Deposits.(sDepositType2).Interest = iPer;
				Pchar.Quest.Deposits.(sDepositType2).Sum = iRes;
				Pchar.Quest.Deposits.(sDepositType2).Result = 0;
			}
			else // если остаток больше начальной суммы - проценты продолжаем считать с неё, а не с остатка, ибо нефиг, дельту приплюсуем к набежавшим процентам - банкир Jason :) 
			{
				DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType2));
				Pchar.Quest.Deposits.(sDepositType2).Interest = iPer;
				Pchar.Quest.Deposits.(sDepositType2).Sum = iDep;
				Pchar.Quest.Deposits.(sDepositType2).Rem = iRes-iDep;
			}
			Pchar.Quest.Deposits.(sDepositType2).city 	  	= NPC_Area;	
			Pchar.Quest.Deposits.(sDepositType2) 			= true;
			Pchar.Quest.Deposits.(sDepositType2).StartDay 	= getDataDay();
			Pchar.Quest.Deposits.(sDepositType2).StartMonth = getDataMonth();
			Pchar.Quest.Deposits.(sDepositType2).StartYear 	= getDataYear();
			Pchar.Quest.Deposits.(sDepositType2).StartTime 	= getTime();
		break;
		
		case "Deposit_return_dub_all":
			DialogExit();
			iTemp = sti(dialogEditStrings[4]);
			TakeNItems(pchar,"gold_dublon", iTemp);
			DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType2));
		break;
		//<-- забор денег по частям		
		
		case "Deposit_return_dub_1":
			TakeNItems(pchar,"gold_dublon", sti(Pchar.Quest.Deposits.(sDepositType2).Result));
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = "Oh... It's so hard to lose it. I've really grown used to this money. Come again anyway.";			
			Link.l1 = "I will if I need to. Farewell.";			
			Link.l1.go = "Exit";
			DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType2));
		break;
		//  ugeen <- вклады в дублонах	
		
		case "DeadMotherfucker":
			Dialog.TempNode = "DeadMotherFucker_1";
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = "You are still alive? Want to return my money, perhaps? Damn you! I've lost so much money that you could never repay me! And I won't find peace until I see your lifeless body!";
            Link.l1 = "I just want to settle things in a peaceful way.";
			Link.l1.go = "LoanRestore_1";
			Link.l2 = LinkRandPhrase("Very well, let's see then! Know that you are not safe from death either!","A threat?! Let's see then what you're going to do...","Money isn't the most important thing in our lives. Don't grieve too much over it, and don't kill people. Come on, I dare you.");
			Link.l2.go = "ExitDelLoan2";
		break;

		case "DeadMotherFucker_1":			
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = "Get out! I wish I would never see you again.";			
			Link.l1 = "...";			
			Link.l1.go = "ExitDelLoan2";
            Dialog.TempNode = "DeadMotherFucker_1";
		break;
		// boal обратимость факапства -->
		case "LoanRestore_1":
            iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Loans.(NPC_Area).StartYear),makeint(Pchar.Quest.Loans.(NPC_Area).StartMonth),makeint(Pchar.Quest.Loans.(NPC_Area).StartDay), makefloat(Pchar.Quest.Loans.(NPC_Area).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
			Pchar.Quest.Loans.(NPC_Area).Result = makeint(Pchar.Quest.Loans.(NPC_Area).Sum) + ((makeint(Pchar.Quest.Loans.(NPC_Area).Sum)/100)*makefloat(Pchar.Quest.Loans.(NPC_Area).Interest))*(iPastMonths+1);
			dialog.text = "Oh really? And what are your concerns?";
			Link.l1 = "For today, I owe you "+FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).Result))+". And I offer this money to you.";
			Link.l1.go = "DeadMotherFucker_1";
            if (sti(Pchar.Money) >= 2*sti(Pchar.Quest.Loans.(NPC_Area).Result))
            {
    			Link.l2 = "I offer you my debt to re-establish good relations with you. It is "+FindRussianMoneyString(2*sti(Pchar.Quest.Loans.(NPC_Area).Result))+".";
    			Link.l2.go = "LoanRestore_2";
			}
		break;
		
		case "LoanRestore_2":
			dialog.text = "Now we're talking! I can do business with you after all.";
			Link.l1 = "Thanks. I won't let you down again.";
			Link.l1.go = "ExitDelLoan2";
			NextDiag.TempNode = "First time";			
			addMoneyToCharacter(Pchar, -2*sti(Pchar.Quest.Loans.(NPC_Area).Result));
			DeleteAttribute(PChar, "quest.Loans_" + NPC_Area);
			DeleteAttribute(PChar, "quest.Loans." + NPC_Area);
			ChangeCharacterHunterScore(PChar, NationShortName(sti(NPChar.nation)) + "hunter", -30);
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
		break;

		case "ExitDelLoan1":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DeleteAttribute(Pchar, "quest.Loans." + (NPC_Area));
		break;

		case "ExitDelLoan2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DeleteAttribute(Pchar, "quest.Loans." + (NPC_Area));
			DeleteAttribute(Pchar, "quest.Deposits." + (NPC_Area));
		break;
		
        case "LoanGranted_exit":
			NextDiag.CurrentNode = NextDiag.TempNode;

			AddMoneyToCharacter(Pchar, makeint(Pchar.Quest.Loans.(NPC_Area).Sum));
			Pchar.Quest.Loans.(NPC_Area) = true;
			Pchar.Quest.Loans.(NPC_Area).StartDay = getDataDay();
			Pchar.Quest.Loans.(NPC_Area).StartMonth = getDataMonth();
			Pchar.Quest.Loans.(NPC_Area).StartYear = getDataYear();
			Pchar.Quest.Loans.(NPC_Area).StartTime = getTime();

			sTemp = "Loans_" + NPC_Area;			
			SetTimerCondition(sTemp, 0, makeint(Pchar.Quest.Loans.(NPC_Area).Period), 0, false);
			pchar.quest.(sTemp).CityId = NPC_Area;
			pchar.quest.(sTemp).win_condition = "LoansForAll";
			
			DialogExit();
			npchar.quest.trade_date = lastspeak_date; // дыра с прокачкой была
		break;
        
		//работорговец
		int iSlaveMoney;
		int amount;
		case "GiveTaskSlave":
			pchar.questTemp.Slavetrader.iSlaveQuantity = 100;
			pchar.questTemp.Slavetrader.iSlaveMoney = sti(pchar.questTemp.Slavetrader.iSlaveQuantity) * 250;
			dialog.Text = "Ah, come on! We are serious people, you and I, we are better than those idiots who are ready to die for a single doubloon, yet never even try to make two doubloons out of it\nI am looking for a man to offer a serious business to. A man brave and active, honest and punctual, but not burdened with... eh... too much scrupulousness concerning moral dilemmas. And I hope that you are the man I am looking for.";
			Link.l1 = "It will depend on what kind of 'deal' you are going to offer me.";
			Link.l1.go = "GiveTaskSlave_1";
		break;
			
		case "GiveTaskSlave_1":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity(npchar.city);
			dialog.Text = "Very well, listen then. Slavery is the most profitable business in the Caribbean nowadays. I am not a planter, but I have trustworthy clients\nSo, I need the following number of slaves - "+pchar.questTemp.Slavetrader.iSlaveQuantity+" heads. I am ready to pay you 250 pesos for each. Trust me, that's a fair price. In total you will earn "+FindRussianMoneyString(sti(pchar.questTemp.Slavetrader.iSlaveMoney))+".";
			Link.l1 = "No, I am not a slave trader. Find yourself another assistant who doesn't ignore his conscience.";
			Link.l1.go = "exit_slaves";
			Link.l2 = "A tempting offer. I'd like to do that. How soon do you need the slaves?";
			Link.l2.go = "GiveTaskSlave_2";
		break;
			
		case "exit_slaves":
			dialog.Text = "Meh, it seems that nobody is eager to move his butt and take the gold beneath his feet. I am very disappointed. Farewell, and don't even think about spreading gossip about our talk. My arm has a long reach...";
			Link.l1 = "Your reach is 'dirty'... just like your tongue. Farewell.";
			Link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "End_quest";
			DeleteAttribute(npchar, "quest.slave");
		break;
			
		case "GiveTaskSlave_2":
			dialog.Text = "I won't limit your time, but try to accomplish your mission as soon as possible. The demand for 'black ivory' is huge. If you do your job well, I'll be giving you this kind of work from time to time in the future.";
			Link.l1 = "Sounds good. Well, wait for the good news.";
			Link.l1.go = "exit";						
			pchar.questTemp.Slavetrader = "Seek_slaves"; // это ввод имени квеста и состояния квеста
			AddQuestRecord("Slavetrader", "1");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("Slavetrader", "sQty", makeint(pchar.questTemp.Slavetrader.iSlaveQuantity));
			AddQuestUserData("Slavetrader", "sSum", makeint(pchar.questTemp.Slavetrader.iSlaveMoney));
			LAi_LocationDisableOfficersGen(&Locations[FindLocation(pchar.location)], true); // блокируем вход офицеров 2015
		break;
			
		case "Checkslaves":
			amount = GetSquadronGoods(Pchar, GOOD_SLAVES) - sti(pchar.questTemp.Slavetrader.iSlaveQuantity);
			dialog.Text = "Have you succeeded in obtaining that shipment of 'black ivory'?";
            if (amount < 0)
			{
				Link.l1 = "Not yet. Just checking if our agreement is still valid.";
            	Link.l1.go = "exit";
			}
			else
			{
				Link.l1 = "I have. They are all in my cargo.";
            	Link.l1.go = "Takeslaves";
			}
		break;
		
		case "Takeslaves":
			amount = sti(pchar.questTemp.Slavetrader.iSlaveQuantity);
			dialog.Text = "Splendid. My men will take them... Don't worry about customs or the commandant of the fort. I am running a huge operation here, so don't expect any trouble and no one will accuse you of smuggling.";
			Link.l1 = "It seems that you've got a strong position here... So how about my payment?";
            Link.l1.go = "Takeslaves_1";
			RemoveCharacterGoods(Pchar, GOOD_SLAVES, amount);
		break;
		
		case "Takeslaves_1":
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.Slavetrader.iSlaveMoney));
			dialog.Text = "Here it is. I don't speak idly. Stay with me, captain, and soon you'll have so much gold you'll need a galleon to carry it!";
			Link.l1 = "That would be great, ha-ha... What's next?";
            Link.l1.go = "Takeslaves_2";
		break;
		
		case "Takeslaves_2":
			dialog.Text = "Next? Come back here in three weeks. I'm working on a deal right now, and it should be ready by then.";
			Link.l1 = "Very well, deal. Farewell.";
            Link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "2");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			pchar.questTemp.Slavetrader = "wait";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait");//запомнить дату
		break;
		
		case "Takeslaves_3":
			if (4-sti(RealShips[sti(pchar.ship.type)].Class) < 0)//проверка класса корабля
			{
				dialog.Text = "I've got a job, but your ship is too weak. I don't want you to fail the mission, nor do I wish to send you to your own death. There's still time, so get yourself a bigger ship, like a barkentine, brigantine, brig, or flute at least. Don't waste time!";
				Link.l1 = "I see, I'll handle it. See you.";
            	Link.l1.go = "Takeslaves_3_smallship";
			}
			else
			{
				dialog.Text = "At last! I was waiting for you. Now let's get straight to the point. As you know, there are always competitors in any business... and I have my own. These grasping and unscrupulous bastards are always eager to steal a client from me! Actually, I want to eliminate one of them and make a good coin at the same time.";
				Link.l1 = "I am all ears.";
            	Link.l1.go = "Takeslaves_4";
			}
		break;
		
		case "Takeslaves_3_smallship":
			pchar.questTemp.Slavetrader = "waitship";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Takeslaves_4":
			Slavetrader_GetRandomShore();//выбор бухты
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.questTemp.Slavetrader.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			dialog.text = "Most excellent. Now listen. This rogue called "+GetName(NAMETYPE_ORIG,pchar.questTemp.Slavetrader.UnknownPirateName,NAME_NOM)+", has brought slaves from Africa and dropped anchor at "+XI_ConvertString(pchar.questTemp.Slavetrader.Island.Shore+"Gen")+", it's on an island called "+XI_ConvertString(pchar.questTemp.Slavetrader.Island)+". He is waiting for smugglers there. His galleon is called '"+pchar.questTemp.Slavetrader.ShipName+". Their deal must be broken at any cost!";
			link.l1 = "And what about the slaves? It would be such a waste to sink them!";
			link.l1.go = "Takeslaves_5";
		break;
		
		case "Takeslaves_5":
			dialog.Text = "Why would you do that? There's no need for that. "+GetName(NAMETYPE_ORIG,pchar.questTemp.Slavetrader.UnknownPirateName,NAME_NOM)+" has a bad reputation and no one will be upset about his disappearance. Board his galleon, kill the man and make sure he stays dead, bring me the cargo and I will sell it. According to my sources, there are about one and a half thousand slaves.";
			Link.l1 = "Shiver me timbers. That's quite a number. What about my payment?";
            Link.l1.go = "Takeslaves_6";
			Link.l2 = "No, sir, these intrigues are not for me. Why should I spoil my relations with smugglers?";
            Link.l2.go = "exit_slaves_1";
		break;
		
		case "exit_slaves_1":
			dialog.Text = "Well... It looks like I was mistaken about you... Farewell, and forget about our talk. And don't spread gossip about what you've heard here. I own this town. And if you are planning to board the '"+pchar.questTemp.Slavetrader.ShipName+" for yourself... I will make sure you end up on the gallows. Consider it.";
			Link.l1 = "Don't worry, I won't report you to the authorities and I don't need your galleon. Farewell.";
            Link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "8");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase(" agreed"," agreed"));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";//конец квеста
		break;
		
		case "Takeslaves_6":
			dialog.Text = "Considering that I've given you the location of the cargo and you don't need to sail in search of 'a prize', the payment is a bit lower – 200 pesos per head. And still, that is a great sum – three hundred thousand pesos in case of success and the ship.";
			Link.l1 = "Deal. How much time do I have?";
            Link.l1.go = "Takeslaves_7";
			Link.l2 = "Ho-ho! You say that as if those slaves would swim to my ship themselves, hoping to get into my cargo as soon as possible! Do you really expect my people to risk their necks for such a paltry sum? Increase my reward or I'm out of this business.";
            Link.l2.go = "exit_slaves_1";
		break;
		
		case "Takeslaves_7":
			dialog.text = "You've got two weeks. Don't be late, or he'll transfer his cargo and it will all be over.";
			link.l1 = "I'll have to hurry, then. Expect me with good news.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "3");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
			AddQuestUserData("Slavetrader", "sShoreName", XI_ConvertString(pchar.questTemp.Slavetrader.Island.Shore + "Dat")); // belamour gen
			AddQuestUserData("Slavetrader", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.questTemp.Slavetrader.Island) + "Voc")); // belamour gen
			pchar.quest.Slavetrader_ShipsAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_ShipsAttack.win_condition.l1.location = pchar.questTemp.Slavetrader.Island;
            pchar.quest.Slavetrader_ShipsAttack.function = "Slavetrader_CreateSlaveShips";//создание кораблей
			SetFunctionTimerCondition("Slavetrader_SlaveShipsOver", 0, 0, 15, false);	//таймер
			pchar.questTemp.Slavetrader = "wait1";	//это заглушка
		break;
		
		case "Takeslaves_4_lose":
			dialog.text = "Well, "+GetFullName(pchar)+", what about our mission? Your gloomy face tells me that you've failed it.";
			link.l1 = "Damn, you are right... I... well, you know... I was late. It seemed he had already left the place, because I found no one there. Had to sail by the wind the whole way, damn it... ";
			link.l1.go = "Takeslaves_5_lose";
		break;
		
		case "Takeslaves_4_win":
			dialog.text = "Well, "+GetFullName(pchar)+", what's your catch today? They told me that "+GetName(NAMETYPE_ORIG,pchar.questTemp.Slavetrader.UnknownPirateName,NAME_NOM)+" feeds the fish! Ha-ha-ha!";
			link.l1 = "Yes, I was just in time! "+GetName(NAMETYPE_ORIG,pchar.questTemp.Slavetrader.UnknownPirateName,NAME_NOM)+" was transferring slaves to the smuggler's ship. Had to board them both and send them to Davy Jones himself, so you have fewer competitors now.";
			link.l1.go = "Takeslaves_5_win";
		break;
		
		case "Takeslaves_5_lose":
			dialog.text = "Yes, I suppose I was wrong about you. Were you late? Or just too frightened to fight? Whatever. It means nothing now. Get lost. I am done with you. Forget everything you saw or heard here.";
			link.l1 = "Farewell then.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "5_5");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
		
		case "Takeslaves_5_win":
			pchar.questTemp.Slavetrader.Nation = npchar.nation;
			amount = 1600 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*200;
			if (amount < 0)
			{
				dialog.text = "I was right about you - "+GetSexPhrase(" you are a dashing thug"," you are a fierce maiden")+"! I need men like you. You have succeeded in your mission in the most excellent way - you have brought more than one and a half thousand slaves! Unfortunately, I can pay you only for one thousand six hundred slaves. I don't have enough coin to pay you for the rest, so you will have to sell them yourself. Your reward is 320,000 pesos.";
				link.l1 = "Thank you. It was a pleasure doing business with you, "+npchar.name+"!";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, 320000);
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, 1600);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", 1600);
				AddQuestUserData("Slavetrader", "sMoney", 320000);
				break;
			}
			if (amount >= 0 && amount < 200)
			{
				dialog.text = "I was right about you - "+GetSexPhrase(" you are a dashing thug"," you are a fierce maiden")+"! I need men like you. You have succeeded in your mission in the most excellent way - you have brought me "+sTemp+" slaves. Your reward is "+FindRussianMoneyString(iSlaveMoney)+".";
				link.l1 = "Thank you. It was a pleasure doing business with you, "+npchar.name+"!";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 200 && amount < 600)
			{
				dialog.text = "At least you've survived the most difficult situation with honour intact. Though the prize is less than I expected, I am still satisfied. You have brought "+sTemp+" slaves. Your reward is "+FindRussianMoneyString(iSlaveMoney)+"";
				link.l1 = "Thank you. It was a pleasure doing business with you, "+npchar.name+"!";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 600 && amount < 1100)
			{
				dialog.text = "I see... I can understand that, but I was expecting far more. You've brought only "+sTemp+" slaves. At least you've destroyed my competitors and that's worth something. Your reward is  "+FindRussianMoneyString(iSlaveMoney)+".";
				link.l1 = "My thanks. I appreciate your understanding. "+npchar.name+"!";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 1100 && amount < 1600)
			{
				dialog.text = "Sounds great, but... hmm. Looks like I was mistaken about you. What have you brought? "+sTemp+" slaves? And what about the rest? And don't tell me that you have sunk them. I'm sure you've sold them to smugglers, or even worse – to that bastard Lavoisier. Get the hell out, I don't want to have any business with you anymore!";
				link.l1 = "As you wish, goodbye.";
				link.l1.go = "node_hanter_1";
				break;
			}
			dialog.text = "Sounds great, but... where are our slaves? Where is our cargo? And don't tell me that you have sunk it. You must have sold it to the smugglers or, worse, to that bastard Lavoisier. Get lost, I am done with you.";
			link.l1 = "As you wish, goodbye.";
			link.l1.go = "node_hanter_1";
		break;
		
		case "node_hanter_1":
			dialog.text = "This isn't over. No one dares to fool me! And you will pay for your attempt - I'll make sure you have problems. Now get out of here!";
			link.l1 = "To hell with you and your slave trading! I should cut you down where you stand, but I am a better man than you will ever be.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "9");
			CloseQuestHeader("Slavetrader");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 30);
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Takeslaves_6_win":
			dialog.text = "It looks like we are working well together, "+pchar.name+". I am very glad. See me in a month and perhaps I'll find a job just for you. I have a few ideas already.";
			link.l1 = "Sure, I'll see you in a month. Working with you is very profitable.";
			link.l1.go = "Takeslaves_7_win";
		break;
			
		case "Takeslaves_7_win":
			dialog.text = "It will make you a fortune... One last question, "+pchar.name+", have you found anything unusual in the galleon's cabin?";
			link.l1 = "Nothing special, really... Did I miss anything?";
			link.l1.go = "Nostatue";
			if (CheckCharacterItem(pchar, "talisman8"))
			{
				link.l2 = "You mean this old buckle, some 'scorpion' amulet?";
				link.l2.go = "Yestatue";
			}
		break;
			
		case "Nostatue":
			dialog.text = "Maybe you did, and maybe you didn't ... It doesn't matter now. See you in a month. Farewell!";
			link.l1 = "See you, "+npchar.name+".";
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "Yestatue":
			dialog.text = "Exactly! This is a Medici fibula... have you ever heard of them? That means it really was in the bastard's cabin... May I take a look?";
			link.l1 = "Sure, take it.";
			link.l1.go = "Yestatue_1";
			RemoveItems(PChar, "talisman8", 1);
		break;
			
		case "Yestatue_1":
			Log_Info("You gave a talisman");
			PlaySound("interface\important_item.wav");
			dialog.text = "Well, well... It really is. Listen, "+pchar.name+", sell it to me. I am ready to pay one hundred thousand pesos.";
			link.l1 = "One hundred thousand? Hm... I agree. There you go!";
			link.l1.go = "Buystatue";
			link.l2 = "No, I won't sell it. The true value of this fibula can't be measured in silver or gold. I know how such things work.";
			link.l2.go = "Nobuystatue";
		break;
			
		case "Buystatue":
			dialog.text = "Perfect! I am glad that we have a deal. Take your money. Looking forward to seeing you in a month.";
			link.l1 = "Farewell, "+npchar.name+".";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 100000);
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "Nobuystatue":
			dialog.text = "You see, I desperately need this fibula! I completely agree with you, it can't be valued in money; any foolish merchant wouldn't even pay you five thousand for it. But it seems you truly understand its worth, since you refuse to sell it for such a sum.\n May I offer you a trade, if you don't want money? I have something you might find interesting. Here, take a look. Remarkable light armour! See for yourself! I offer it to you in exchange for the fibula.\nIt is not unique, by the way. You sailors can always find more for yourselves, but I cannot. Do you agree now?";
			link.l1 = "Heh... I suppose so. Give me the armour and take this fibula.";
			link.l1.go = "Nobuystatue_yes";
			link.l2 = "No, this fibula is worth far more to me than this armour. I shall keep it for myself.";
			link.l2.go = "Nobuystatue_no";
		break;
			
		case "Nobuystatue_yes":
			dialog.text = "Splendid! Glad we have a deal. This is your armour now. Take it. See you in a month. Farewell.";
			link.l1 = "See you, "+npchar.name+".";
			link.l1.go = "exit";
			TakeNItems(pchar, "cirass7", 1);
			Log_Info("You have received a Brigandine");
			PlaySound("interface\important_item.wav");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "Nobuystatue_no":
			dialog.text = "Too bad... Really bad. Well, take it. I won't judge you. See you in a month. Farewell.";
			link.l1 = "Farewell.";
			link.l1.go = "exit";
			TakeNItems(pchar, "talisman8", 1);
			Log_Info("You have received a talisman");
			PlaySound("interface\important_item.wav");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "EscapeSlave":
			dialog.text = "You are just in time, "+pchar.name+". I have a mission for you, if you are ready to begin.";
			link.l1 = "Sure, I am ready.";
			link.l1.go = "EscapeSlave_1";
		break;
			
		case "EscapeSlave_1":
			dialog.text = "Excellent! Now, straight to the point. Have you heard the latest news?";
			link.l1 = "Hm, what do you mean? There is a lot of news coming in every day.";
			link.l1.go = "EscapeSlave_2";
		break;
			
		case "EscapeSlave_2":
			dialog.text = "This one is all about our business. There was the greatest runaway of slaves in the New World's history! More than a thousand souls have escaped and in the meantime they have destroyed and burned a few of Holland's outposts.";
			link.l1 = "Intriguing. Go on.";
			link.l1.go = "EscapeSlave_3";
		break;
			
		case "EscapeSlave_3":
			dialog.text = "But they didn't just run away, somehow they managed to leave the island! No trace left. Mathias Beck is outraged. But that's not the point... The point is, I ask you to sail to Curacao, find out what happened there, track down the refugees and capture them\nAnd, of course, save them from the hands of Dutch justice, which would show them no mercy. I will pay 300 pesos per head - I have heard they make very good slaves.";
			link.l1 = "Got it. I'm heading to Curacao. Await me with good news.";
			link.l1.go = "EscapeSlave_yes";
			link.l2 = "You know, I won't take the mission. I won't deprive the people of their freedom. They have risked their lives to gain it. They have earned it.";
			link.l2.go = "EscapeSlave_no";
		break;
			
		case "EscapeSlave_no":
			dialog.text = "What a pity... I didn't expect that from you... and at the most inappropriate time. I suppose it's clear to you that our partnership is over. Farewell.";
			link.l1 = "Have a nice day.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "8");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "EscapeSlave_yes":
			Slavetrader_GetEscapeShore();
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(HOLLAND);
			pchar.questTemp.Slavetrader = "EscapeSlave_Villemstad";
			AddQuestRecord("Slavetrader", "22_1");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			DialogExit();
		break;
			
		case "Escape_slaves_win":
			int iSlaveMoneyH;
			string sNum;
			amount = 1100 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*300;
			sNum = GetSquadronGoods(Pchar, GOOD_SLAVES) - 1100;
			iSlaveMoneyH = makeint(sNum)*100;
			if (amount < 0)
			{
				dialog.text = "Ha! You've not only succeeded in your hard mission, but you've brought more slaves than I requested - "+sTemp+" slaves. But "+sNum+" slaves didn't escape from Curacao. I'll pay you 100 pesos per head. I suppose that will work for you. Your reward is 330,000 pesos and "+FindRussianMoneyString(iSlaveMoneyH)+" for an excess, ha-ha.";
				link.l1 = "Ha! You definitely can't be cheated. I agree, whatever you say. "+npchar.name+"!";
				link.l1.go = "Escape_slaves_win_1";
				AddMoneyToCharacter(pchar, 330000);
				AddMoneyToCharacter(pchar, makeint(iSlaveMoneyH));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "22_5");
				AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoneyH));
				break;
			}
			if (amount < 101 && amount >= 0)
			{
				dialog.text = "You have completed that difficult mission in the most excellent way and brought me "+sTemp+" slaves. Your reward is "+FindRussianMoneyString(iSlaveMoney)+".";
				link.l1 = "My thanks. A pleasure doing business with you, "+npchar.name+"!";
				link.l1.go = "Escape_slaves_win_1";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "22_6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 100 && amount < 600)
			{
				dialog.text = "You have succeeded in that difficult mission. The prize is not as rich as I expected, but I am satisfied nonetheless. So you've brought it here "+sTemp+" slaves. Your reward is "+FindRussianMoneyString(iSlaveMoney)+".";
				link.l1 = "Thanks. It was a pleasure doing business with you, "+npchar.name+"!";
				link.l1.go = "Escape_slaves_win_1";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "22_6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 600 && amount < 1100)
			{
				dialog.text = "You've found them? Hm... what have you brought me?"+sTemp+" Slaves? Where is the rest of the cargo? And don't even try to tell me that you have sunk it. You must have sold it to smugglers, or even worse - to that bastard Lavoisier from Isla-Tesoro. Get away from here, I have no wish to work with you anymore.";
				link.l1 = "Farewell.";
				link.l1.go = "node_hanter_1";
				break;
			}
			dialog.text = "Found them? What about the slaves? Where is our cargo? And don't even try to tell me that you have sunk it. You must have sold it to smugglers or, even worse, to that bastard Lavoisier from Isla-Tesoro. Get away from here, I have no wish to work with you anymore.";
			link.l1 = "Farewell.";
			link.l1.go = "node_hanter_1";
		break;
		
		case "Escape_slaves_win_1":
			dialog.text = "I truly appreciate you, "+pchar.name+". Really. Come back here in a month and I will prepare a new business, profitable for both of us.";
			link.l1 = "I am also satisfied with our partnership, "+npchar.name+". See you in a month.";
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_2");
			pchar.questTemp.Slavetrader = "wait_2";
		break;
			
		case "Slaveshore":
			dialog.text = "You are just in time, "+pchar.name+". I am looking for a brave and unscrupulous sailor, ha-ha. Are you ready to handle my job?";
			link.l1 = "I am all ears.";
			link.l1.go = "Slaveshore_1";
		break;
			
		case "Slaveshore_1":
			pchar.questTemp.Slavetrader.Island = Islands[GetCharacterCurrentIsland(pchar)].id;
			pchar.questTemp.Slavetrader.Island.Shore = GetIslandRandomShoreId(pchar.questTemp.Slavetrader.Island);
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.questTemp.Slavetrader.Nation = NPChar.nation;
			dialog.text = "It is quite simple this time. Today, a pinnace "+pchar.questTemp.Slavetrader.ShipName+"' under the flag of "+NationNameGenitive(sti(npchar.nation))+" has dropped anchor at "+XI_ConvertString(pchar.questTemp.Slavetrader.Island.Shore+"Gen")+" bay. It was loaded with a large batch of 'ebony' with the help of the local smugglers. Two thousand heads, no less\nNo soldiers in the crew and the captain is a trader. Overall, no threat at all. Board the ship and bring me the cargo. 200 pesos per head as usual.";
			link.l1 = "Hm... This is not the same as the last job. You're suggesting I attack a ship of your own nation!";
			link.l1.go = "Slaveshore_2";
		break;
			
		case "Slaveshore_2":
			dialog.text = "I don't get it, "+pchar.name+"Does the ship's flag matter? Do you really care about that?";
			link.l1 = "Do I? No, I don't give a damn, gold doesn't have a nationality. It was just a bit unexpected...";
			link.l1.go = "Slaveshore_3_yes";
			link.l2 = "I do care. I don't want to have "+NationNameAblative(sti(npchar.nation))+" among my enemies.";
			link.l2.go = "Slaveshore_3_no";
		break;
			
		case "Slaveshore_3_no":
			dialog.text = "Are you serious? You must be joking, you can't trust anyone these days... In that case, go away. And forget everything you saw or heard here!";
			link.l1 = "See you,"+npchar.name+".";
			link.l1.go = "node_hanter_1";
		break;
			
		case "Slaveshore_3_yes":
			dialog.text = "Why are you surprised? Because I don't care about the nationality of coins? I assure you, indeed, I don't. To be honest, patriotism is bad for a professional banker, unless he is eager to go broke one day\nBut enough philosophy. Let's cut to the chase - the ship will stay here until midnight, so you don't have much time left. Are you ready to proceed?";
			link.l1 = "Yes, "+npchar.name+", I am on my way.";
			link.l1.go = "Slaveshore_4";
		break;
			
		case "Slaveshore_4":
			dialog.text = "Splendid. I have no doubt that you will succeed in our mission. Good luck."+pchar.name+".";
			link.l1 = "Thank you! Farewell.";
			link.l1.go = "exit";
            AddQuestRecord("Slavetrader", "10");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sShip", pchar.questTemp.Slavetrader.ShipName);
			pchar.quest.Slavetrader_ShoreAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_ShoreAttack.win_condition.l1.location = pchar.questTemp.Slavetrader.Island;//отправляем в локацию
            pchar.quest.Slavetrader_ShoreAttack.function = "Slavetrader_CreateShoreShips";//создание кораблей
			SetFunctionTimerCondition("Slavetrader_ShoreShipsOver", 0, 0, 1, false);	//таймер
			pchar.questTemp.Slavetrader = "wait1";	//заглушка
		break;
			
		case "Pinas_lose":
		dialog.text = "Well, "+GetFullName(pchar)+", what about your mission? Your gloomy face tells me you've failed it.";
			link.l1 = "You are damn right... I... Well... I was too late. I was in the tavern, and when I shipped out, there was nobody at sea.";
			link.l1.go = "Takeslaves_5_lose";
		break;
			
		case "Slaveshore_5":
			dialog.text = ""+pchar.name+", please calm down. It's not my fault! Damn, I received the report too late... There was treachery! One of my trusted men sold me out!";
			link.l1 = "Fine, I see that you are speaking the truth. You are lucky that the captain of the pinnace told me that our 'business' was uncovered. I'd have already killed you if he hadn't blabbed. But you, you bloody sack of money, kept telling me all this time that you 'own this town'!";
			link.l1.go = "Slaveshore_6";
		break;
			
		case "Slaveshore_6":
			dialog.text = "The ambush was not organized by the local authorities, otherwise I would have known... "+pchar.name+", this is not the right time for quarrels. Both of us are in danger; one of my former contractors has set us up\nI managed to find out that all the gathered evidence—a package of papers—is being transported to our governor-general. If he gets them, we are finished! You, by the way, will suffer the most.";
			link.l1 = "Now I see what that bastard captain meant!";
			link.l1.go = "Slaveshore_7";
		break;
			
		case "Slaveshore_7": //выбор острова, куда бригантина пойдёт
			switch (sti(NPChar.nation))
            {
                case HOLLAND :
					pchar.questTemp.Slavetraderbrig.Island = "Curacao";
                break;
                case FRANCE :
					pchar.questTemp.Slavetraderbrig.Island = "Nevis";
                break;
                case SPAIN :
					pchar.questTemp.Slavetraderbrig.Island = "Cuba2";  
                break;
                case ENGLAND :
					pchar.questTemp.Slavetraderbrig.Island = "Jamaica";     
                break;
			}
			pchar.questTemp.Slavetraderbrig.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));//имя бригантины
			pchar.questTemp.Slavetrader.Nation = NPChar.nation;
			dialog.text = "Listen carefully. We still have a chance. The package was sent on the brigantine '"+pchar.questTemp.Slavetraderbrig.ShipName+". That is the only thing I am certain about. Papers are being delivered to the governor-general at his residence on "+XI_ConvertString(pchar.questTemp.Slavetraderbrig.Island)+". You've got to intercept it, board it and find that incriminating evidence.";
			link.l1 = "Don't have much choice here. Pray for me, for yourself, and hope that I'll be able to catch it. We'll talk again about all of this when I'm back. Don't think that I'll just let it go.";
			link.l1.go = "Slaveshore_8";
			AddQuestRecord("Slavetrader", "14");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetraderbrig.ShipName);
			AddQuestUserData("Slavetrader", "sIsland", XI_ConvertString(GetIslandByArealName(pchar.questTemp.Slavetraderbrig.Island)));
			pchar.quest.Slavetrader_BrigAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_BrigAttack.win_condition.l1.location = pchar.questTemp.Slavetraderbrig.Island;//отправляем в локацию
            pchar.quest.Slavetrader_BrigAttack.function = "Slavetrader_CreateBrig";//создание бригантины
			SetFunctionTimerCondition("Slavetrader_BrigOver", 0, 0, 15, false);	//таймер
			pchar.questTemp.Slavetrader = "wait1";	//это нода ожидания, пустая
		break;
		
		case "Slaveshore_8":
			dialog.text = "Getting this package is your main priority! I won't feel safe until you deliver it to me... Damn..."+pchar.name+", looks like we've got a problem here...";
			link.l1 = "What is it?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Slavetrader_enterSoldiers");
			break;
			
		case "Brig_lose":
			dialog.text = "Damn... I was counting on you. "+pchar.name+". Fine then. But we won't be doing any more business. If I am not able to bribe the investigator, I'll have to run away. And I don't recommend you stay here – soldiers may come at any time. Farewell.";
			link.l1 = "Farewell, "+npchar.name+".";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Letter_lose":
			dialog.text = "They were there. Well, we can't do any business together, it's not safe anymore. Farewell.";
			link.l1 = "Farewell, "+npchar.name+".";
			link.l1.go = "exit";
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Brig_win":
			dialog.text = "Excellent! I had no doubt in you, "+pchar.name+". Please give me those papers, I am too nervous.";
			link.l1 = "Take them.";
			link.l1.go = "Brig_win_1";
		break;
			
		case "Brig_win_1":
			RemoveItems(PChar, "letter_1", 1);
			dialog.text = "Good... Now I am safe. The governor-general won't know a thing, and I've already sorted out all the problems with the local authorities, but it was costly, I tell you.";
			link.l1 = "Sounds great, but don't you think you ought to compensate me for my troubles because of your thoughtless actions?";
			link.l1.go = "Brig_win_2";
		break;
			
		case "Brig_win_2":
			dialog.text = "Sure, "+pchar.name+". Even more, I owe you a great deal. And I truly hope to continue our business. But I ask you to understand me – I've spent a fortune – the governor's and commandant's loyalty does not come cheap. And I had to deal with that murder of the entire patrol in my bank...";
			link.l1 = "You mean you won't compensate my costs?!";
			link.l1.go = "Brig_win_3";
		break;
			
		case "Brig_win_3":
			dialog.text = "Don't be so harsh, "+pchar.name+". I really am having trouble with money right now, so I offer you a different kind of payment.";
			link.l1 = "I am listening to you then.";
			link.l1.go = "Brig_win_4";
		break;
			
		case "Brig_win_4":
			dialog.text = "My companion and I were caught in a storm near the southern shores of the Main a year ago. Our ships were thrown onto the rocks of the Boca de la Serpienta coast; although they soon sank, we managed to drag our cargo ashore. Chests filled with precious stones and jewellery. The bay seemed quite cosy, so we hid the treasures without any trouble\nBut we were attacked by the Indians the next morning as soon as the storm had ended. That's how most of the survivors died, including my companion. A few sailors and I managed to escape on a longboat\nWe reached Cumana safely, yet I didn't dare return for the treasures. I am sure the local savages are still guarding their shore, along with my chests. But you can deal with that band of redskins\nThe jewellery you'll find there is more than enough to cover all your expenses, including an expedition to the southern Main.";
			link.l1 = "Hm... fine. Then I'm heading to Cumana";
			link.l1.go = "Brig_win_5";
		break;
			
		case "Brig_win_5":
			dialog.text = "You can be confident, "+pchar.name+", that all I've said is the truth. I expect to see you in a month. I already have another deal in mind, and how I might help my struggling business. Farewell.";
			link.l1 = "See you, "+npchar.name+".";
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_3");
			pchar.questTemp.Slavetrader = "wait_3";
			Pchar.quest.Slavetrader_Bonanza.win_condition.l1 = "location";
            Pchar.quest.Slavetrader_Bonanza.win_condition.l1.location = "Shore18";
            Pchar.quest.Slavetrader_Bonanza.function = "Slavetrader_Bonanza";
		break;
			
		case "SlaveGalleon":
			dialog.text = "And here you are, "+pchar.name+". Nice, you are just in time as always. I'd like to give you more information about the Caribbean slave market before I give you your next mission. Do you know what the word 'repartimiento' means?";
			link.l1 = "Hm, no, "+npchar.name+", I don't. But I suppose it's about taking something away from someone. Am I right?";
			link.l1.go = "SlaveGalleon_1";
		break;
			
		case "SlaveGalleon_end":
			dialog.text = "You surprise me. What did you expect from me? Go away!";
			link.l1 = "An illegal business is too much for my conscience. Especially the slave trade.";
			link.l1.go = "node_hanter_1";
		break;
			
		case "SlaveGalleon_1":
			dialog.text = "You've almost got it,"+pchar.name+". Taking away someone's freedom. Repartimiento is a cunning and legal way to enslave the local Indians. So to speak. Spanish authorities use it against the native people of the mainland. Are you interested in knowing more?";
			link.l1 = "Why not?";
			link.l1.go = "SlaveGalleon_2";
		break;
			
		case "SlaveGalleon_2":
			dialog.text = "Representatives of the Spanish crown visit Indian settlements. Using cynical deception and direct threats, they force the Indians to buy all kinds of rubbish, like rotten meat and old razors, at outrageous prices. On credit\nSome time later, let's say a year, the representatives return and demand payment. If the Indians can't pay, which is what usually happens, the Spanish take some of their able-bodied men, supposedly for a time and to 'teach them how to cultivate the land'\nAs you understand, they never return to their settlements. That's how our trusting redskins end up on sugar plantations and in redwood factories.";
			link.l1 = "Damn... really... What do the Indians do about that? Do they resist when the Spanish enslave them? Or do they just not understand what's happening?";
			link.l1.go = "SlaveGalleon_3";
		break;
			
		case "SlaveGalleon_3":
			dialog.text = "I suppose they always see it coming, but only a few dare to openly oppose, especially when the Spanish present a paper with the chieftain's fingerprint. Of course, such tactics are usually used against peaceful tribes like the Arawaks or Miskitos. Such a trick won't work with the warlike Itza or Akawoys\nWell, let's talk about your mission.";
			link.l1 = "I can already smell a lot of coins! I'm listening, "+npchar.name+".";
			link.l1.go = "SlaveGalleon_4";
		break;
			
		case "SlaveGalleon_4":
			Slavetrader_GetHispanShore();
			sTemp = pchar.questTemp.SlavetraderAreal.add; 
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(SPAIN);
			dialog.text = "Soon, a heavy galleon will set sail from Caracas. It's named "+pchar.questTemp.Slavetrader.ShipName+". It contains a huge number of slaves - about 3,000 men - Indians from the Orinoco, captured according to the repartimientos policy. The galleon is sailing to Santiago; the sugar plantations of Cuba need many workers. You must capture the galleon with her cargo. I would take at least two ships with me if I were you; they say the galleon is the finest of its kind. Pay rates remain the same - 200 pesos per head. ";
			link.l1 = "Heh! Sounds good. I agree.";
			link.l1.go = "SlaveGalleon_5";
			link.l2 = "You know I don't like that repartimiento of yours. It's too cynical. I'm not going to do this.";
			link.l2.go = "SlaveGalleon_end";
		break;
			
		case "SlaveGalleon_5":
			sTemp = pchar.questTemp.SlavetraderAreal.add; 
			dialog.text = "I wish you luck then. Know that the captain of this galleon is a very skilled and experienced sailor of war. It won't be an easy fight, so prepare yourself. Don't waste time, it will take fifteen or twenty days for him to reach "+sTemp+" Santiago. Try not to miss it, though this galleon is really hard to miss\nYes! Almost forgot! There are plenty of Indian trinkets on the ship, the natives often pay their debts with their cult items and crafts. Bring me anything special you might find, and I will pay you handsomely for every valuable item you bring.";
			link.l1 = "I understand.";
			link.l1.go = "exit";
			SlavetraderGalleonInWorld();
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("Slavetrader_SlaveGalleonOver", 0, 0, 20, false);
			pchar.questTemp.Slavetrader = "wait1";
			AddQuestRecord("Slavetrader", "18");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
			AddQuestUserData("Slavetrader", "sAreal", sTemp);
		break;
			
		case "Lostgalleon":
			dialog.text = "Well, "+pchar.name+", it was my very last hope... That's why I offered this job to you. No one but you could do it... and now I see that you are not capable either. Let's say our goodbyes then. After the last failure and all those rumours, all my clients are gone. And I am almost bankrupt, perhaps I will have to leave this town. I don't blame you - this job was too tough. Eh... Farewell,"+pchar.name+".";
			link.l1 = "I am so sorry, "+npchar.name+", that went too far. I am truly sorry. Perhaps it will all settle down. Goodbye.";
			link.l1.go = "exit";
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Wingalleon":
			pchar.questTemp.Slavetrader.Nation = npchar.nation;
			amount = 3000 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*200;
			if(amount < 1) 
			{
				dialog.text = "Phew, I feel better now... I was right to trust you... Where did this irony come from? What's wrong?";
				link.l1 = "Dear sir, it wasn't a galleon... or a very big galleon... Damn! It was a Line Ship! And you didn't even warn me! But I managed to board her. I have "+sTemp+" slaves and I'm ready to transfer them to you. According to our deal, you owe me - "+FindRussianMoneyString(iSlaveMoney)+". It would be great to receive some compensation for your misinformation.";
				link.l1.go = "Wingalleon_1";
			}
			else
			{
			dialog.text = "Did you find the galleon? What about the slaves? There are supposed to be three thousand of them, no less! Damn it, everyone is a rat and a traitor! I didn't expect it from you... you were my last hope\nVery well... I swear, I will spend every coin I have left to destroy you, to kill you! The whole fleet of "+NationNameGenitive(sti(npchar.nation))+" will be hunting you! Get out of here!";
				link.l1 = "Well...";
				link.l1.go = "Wingalleon_goaway";
			}
		break;
			
		case "Wingalleon_goaway":
			AddQuestRecord("Slavetrader", "9");
			CloseQuestHeader("Slavetrader");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 70);
			pchar.questTemp.Slavetrader = "End_quest";
			DialogExit();
		break;
			
		case "Wingalleon_1":
			dialog.text = "You don't say! I swear, I had no idea. A heavy galleon was supposed to sail, not a bloody ship of the line! It seems they changed their plans at the last moment... But still, you have succeeded!\nI completely agree with you about the money and compensation for your expenses, but the thing is, I don't possess such a sum right now. You know about my recent troubles... But don't be angry, "+pchar.name+", for God's sake. You give me the cargo and I'll sell it, my client is already waiting\nI will have the whole sum in five days, so you will get what you deserve. You may rely on me. Here, take all the cash I have right now.";
			link.l1 = "Hm... I expected to receive the money now. I wish you knew what kind of fight I had to go through! Ah, whatever... I'll sympathise with you. But keep in mind that if you try to cheat me, I'll find you even in Europe!";
			link.l1.go = "Wingalleon_yes";
			link.l2 = "You know, "+npchar.name+", screw you! It wasn't a deal. You can't even imagine what kind of fight I had to handle. I'll take all the slaves for myself and sell them without your agency.";
			link.l2.go = "Wingalleon_no";
		break;
			
		case "Wingalleon_no":
			dialog.text = "So, now you're talking! Looks like unsuspecting "+npchar.name+" was only a cow to milk, a simple delay is enough for you to betray me and start an operation on your own. It seems you have forgotten that I was the one who gave you the job and tipped you off about the booty\nVery well... I swear, I will spend every coin I have left to destroy you, to kill you! The whole fleet of "+NationNameGenitive(sti(npchar.nation))+" I will be hunting you! Get out of my sight!";
			link.l1 = "Don't you dare try to scare me with an empty money chest. I'll sink all your fleets and feed them to the crabs.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "9");
			CloseQuestHeader("Slavetrader");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 70);
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Wingalleon_yes":
			dialog.text = "Thank you for your understanding, "+pchar.name+". I promise that everything will be fine, no need for your threats\nTake this as an advance. Fifteen chests. Five of them will serve as compensation for moral damages. Come see me in five days to get the rest.\nDon't forget to bring any Indian items you found on the ship... if you found any at all, of course. I have nothing to pay you for them anyway.";
			link.l1 = "In five days,"+npchar.name+". In five days...";
			link.l1.go = "Wingalleon_yes_1";
		break;
			
		case "Wingalleon_yes_1":
			TakeNItems(pchar, "chest", 15);
			Log_Info("You've received credit chests");
			PlaySound("interface\important_item.wav");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_4");
			pchar.questTemp.Slavetrader = "wait_4";
			AddQuestRecord("Slavetrader", "20");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			pchar.questTemp.Slavetrader.iSlaveMoney = makeint(sTemp)*200-120000;
			RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
			DialogExit();
		break;
	
		case "FindRat":
			dialog.text = "As I promised, "+pchar.name+", I am ready to pay you. The slaves are sold, the customer is happy, and so are we. After deducting the advance, your reward is"+FindRussianMoneyString(sti(pchar.questTemp.Slavetrader.iSlaveMoney))+". Please, take your money.";
			link.l1 = "Splendid, "+npchar.name+". It's good to deal with a man who keeps his word...";
			link.l1.go = "FindRat_1";
		break;
			
		case "FindRat_1":
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.Slavetrader.iSlaveMoney));
			dialog.text = "You can always trust my word, "+pchar.name+". I have never given you any reason to doubt me. Partners must be honest with each other, that's the key to business\nLet's talk about Indian artifacts now. Show me what you have, don't make a collector like myself wait.";
			link.l1 = "Hm... Take a look.";
			link.l1.go = "FindRat_2";
		break;
			
		case "FindRat_2":
			if (CheckCharacterItem(pchar, "talisman16"))
			{
				dialog.text = "Yes! Excellent! A golden ritual knife! It's a rare thing. I've always wanted something like that in my collection. I'll offer you 30,000 for it, or an amulet of 'Ehecatl' in exchange. I've got two of them anyway.";
				link.l1 = "I'd take money.";
				link.l1.go = "BG_money";
				link.l2 = "I'd take an amulet of 'Ehecatl' in exchange.";
				link.l2.go = "BG_change";
				link.l3 = "I'd better keep this knife with me.";
				link.l3.go = "BG_no";
			}
			else
			{
				dialog.text = "Let's see... Unfortunately, you have nothing interesting for me.";
				link.l1 = "Whatever you say.";
				link.l1.go = "BG_PF";
			}
		break;
			
		case "BG_money":
			dialog.text = "Splendid. Take your 30,000 and this Indian knife is mine now.";
			link.l1 = "Good. And is that all you're interested in...";
			link.l1.go = "BG_PF";
			AddMoneyToCharacter(pchar, 30000);
			Log_Info("You've given a golden knife");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "talisman16", 1);
		break;
			
		case "BG_change":
			dialog.text = "Splendid! Here is your amulet, and this Indian knife is mine now.";
			link.l1 = "Good. And is that all you're interested in...";
			link.l1.go = "BG_PF";
			Log_Info("You've given a golden knife");
			Log_Info("You've received an amulet of 'Ehecatl'");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "talisman16", 1);
			TakeNItems(pchar, "obereg_9", 1);
		break;
			
		case "BG_no":
			dialog.text = "Whatever. But it's such a pity, anyway...";
			link.l1 = "Good. And is that all you are interested in...";
			link.l1.go = "BG_PF";
		break;
			
		case "BG_PF":
			dialog.text = "Wait! Let me take another look...";
			link.l1 = "Sure. Come take a look and choose what you want.";
			link.l1.go = "PF_check";
		break;
			
		case "PF_check":
			if (CheckCharacterItem(pchar, "mineral31"))
			{
				dialog.text = "This! And I didn't even notice it at first. I'm interested in this bone with a copper ring. Such an intriguing thing, I tell you... I can pay you 20,000 pesos or give you a 'Cimaruta' amulet in exchange.";
				link.l1 = "I'd take money.";
				link.l1.go = "PF_money";
				link.l2 = "I'd take a 'Cimaruta' amulet in exchange.";
				link.l2.go = "PF_change";
				link.l3 = "I'd keep this artifact with me.";
			link.l3.go = "PF_no";
			}
			else
			{
				dialog.text = "No... you have nothing else of interest here.";
				link.l1 = "Whatever!";
				link.l1.go = "FindRat_3";
			}
		break;
			
		case "PF_money":
			dialog.text = "Excellent! Here are your 20,000 pesos and this bone is mine now.";
			link.l1 = "Nice. I feel good about our deal.";
			link.l1.go = "FindRat_3";
			AddMoneyToCharacter(pchar, 20000);
			Log_Info("You've given a magic bone");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "mineral31", 1);
		break;
			
		case "PF_change":
			dialog.text = "Splendid! Here is your amulet, and this bone is mine now.";
			link.l1 = "Nice. I feel good about our deal.";
			link.l1.go = "FindRat_3";
			Log_Info("You've given a magic bone");
			Log_Info("I've received an amulet of 'Cimaruta'");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "mineral31", 1);
			TakeNItems(pchar, "amulet_11", 1);
		break;
			
		case "PF_no":
			dialog.text = "Whatever. But it's such a pity, anyway...";
			link.l1 = "I need that bone for myself, I'm so sorry.";
			link.l1.go = "FindRat_3";
		break;
			
		case "FindRat_3":
			dialog.text = "Well... by boarding the galleon—oh, I am sorry, the Line Ship—you have saved me. I truly appreciate our partnership, "+pchar.name+". You are my best agent.";
			link.l1 = "I am flattered. You are rather overestimating my accomplishments...";
			link.l1.go = "FindRat_4";
		break;
			
		case "FindRat_4":
			dialog.text = "I am completely serious. And I am going to ask you to undertake another mission because of your extraordinary skills and because I trust you.";
			link.l1 = "Heh! Surprising! I am listening. Where is the other galleon with slaves?";
			link.l1.go = "FindRat_5";
		break;
			
		case "FindRat_5":
			dialog.text = "The matter is not about slaves this time. Surprised? I'll pay you well for the mission... Very well.";
			link.l1 = "Get straight to business.";
			link.l1.go = "FindRat_6";
		break;
			
		case "FindRat_6":
			dialog.text = "This business is connected to the recent events you were also a part of... So, as you may know, I am involved in a rather illegal business - slave trading. You may also know that I hire privateers like you for all sorts of assignments\nOne of my men betrayed me not long ago for reasons unknown. He gathered evidence and made a report to the authorities. You had the pleasure of seeing the consequences with your own eyes. A ship with soldiers arrived here... you know the rest\nIt took quite an effort for me to settle the situation. As you likely understand, I cannot let this treachery go unanswered. Besides, I cannot live and work peacefully knowing that the rat is still alive. I have sent bounty hunters, but there is no result yet\nI ask you to deal with this matter personally. All the more so, his actions affected you too.";
			link.l1 = "Hm... that bastard ought to be hanged from the yardarm! Tell me more about him, and of course, my payment for the job.";
			link.l1.go = "FindRat_7";
		break;
			
		case "FindRat_7":
			dialog.text = "Don't worry about that. I will pay handsomely for his elimination, and I'm not just talking about money. I won't spare the finest items from my collections. Let's talk about the man. His name is Francois Gontier\nHe is aware of my hunt, so he sold his frigate to cover his tracks. My colleagues told me that he was seen in Panama. I believe you should begin your search there.";
			link.l1 = "Well, I am on my way then.";
			link.l1.go = "FindRat_8";
		break;
			
		case "FindRat_8":
			dialog.text = "I wish you luck then. Know that this Gontier is a very experienced sailor and he has a crew of reckless cutthroats. He has nothing to lose, so he'll be fighting in a very desperate way.";
			link.l1 = "I am not afraid of people like him, but I'll consider what you've said. Farewell, and rest assured, I will get him even in hell.";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(SPAIN);
			AddQuestRecord("Slavetrader", "21");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			pchar.questTemp.Slavetrader = "FindRatPanama";
		break;
			
		case "Wincorvette":
			dialog.text = "Splendid! Now he can write his reports to the jellyfish. No one dares to cross me. My thanks to you, "+pchar.name+", you are an indispensable man.";
			link.l1 = "Thank you, "+npchar.name+", for such a positive assessment of my actions. What about my payment?";
			link.l1.go = "Wincorvette_1";
		break;
			
		case "Wincorvette_1":
			dialog.text = "Sure. I'd pay a fair price for such a difficult job. First, I present you with this excellent spyglass.";
			link.l1 = "Shiver me timbers, what a gift!";
			link.l1.go = "Wincorvette_2";
		break;
			
		case "Wincorvette_2":
			dialog.text = "Besides, here are 100,000 pesos as your primary payment and 50,000 as compensation for your own expenses.";
			link.l1 = "Thanks, "+npchar.name+". I say again, it's a real pleasure to deal with you.";
			link.l1.go = "Wincorvette_3";
			Log_Info("You've received an excellent spyglass");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "spyglass4", 1);
		break;
			
		case "Wincorvette_3":
			dialog.text = "I will be waiting for you in a month, just as always. It's a very big deal on the row, and you'll need a well-equipped squadron. I ask you to understand that and prepare yourself well. If my plan works, we will be rich.";
			link.l1 = "Good,"+npchar.name+". I'll come back when I'm ready.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 150000);
			AddQuestRecord("Slavetrader", "21_13");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_5");
			pchar.questTemp.Slavetrader = "wait_5";
		break;
			
		case "Lostcorvette":
			dialog.text = "Pity, what a shame... Well, don't feel upset, you are not the first man that scum has fooled. I will nail him one day anyway\nAs for you, come and see me in a month. This will be big, so gather a well-equipped and armed squadron. Please, take it seriously and do your best to prepare. If my plan works, we will be rich.";
			link.l1 = "Good, "+npchar.name+". I'll come back when I'm ready.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_14");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_5");
			pchar.questTemp.Slavetrader = "wait_5";
		break;
		
		case "Havana_fort":
			dialog.text = "You are just in time, "+pchar.name+"! I was about to start worrying, I was going to send a man to find you\nLet's get started! Your mission is truly big and risky now, but the reward is adequate. You will receive more than a million pesos once the job is done.";
			link.l1 = "Now we are talking! I'm listening, "+npchar.name+".";
			link.l1.go = "Havana_fort_1";
		break;
		
		case "Havana_fort_1":
			dialog.text = "The enslaved Indians were being moved in small groups to Havana from all over the Main, and a few galleons also arrived from Africa and were unloaded. By now, there are almost five thousand slaves behind the high walls of Havana's fort.";
			link.l1 = "I've got a feeling that the deal is about storming Havana.";
			link.l1.go = "Havana_fort_2";
		break;
		
		case "Havana_fort_2":
			dialog.text = "You've got the right feeling, "+pchar.name+". That is exactly what I want to ask you to do. You and only you. I doubt that any of my other agents are capable of doing this\nI believe that you are in?";
			link.l1 = "To be honest, "+npchar.name+", I am a bit dumbfounded now. I had no idea your operation was so... large-scale. Sure, I am in. "+RandSwear()+"";
			link.l1.go = "Havana_fort_3";
			link.l2 = "You know what, "+npchar.name+", this is going too far. I've had enough of your surprises. Next time, your greed will have me declaring war on Spain and I'll have to fight them all by myself. If you really need those slaves, then storm Havana on your own.";
			link.l2.go = "Havana_fort_not";
		break;
		
		case "Havana_fort_not":
			dialog.text = "Didn't expect that from you... Damn, what am I supposed to tell my customer? Fine. It's your call and I have to find a new partner. Farewell, "+pchar.name+". And I will not use your services in the future. Remember that you have dropped the deal that could have made your descendants rich for seven generations.";
			link.l1 = "You can't take all the money in the world, and you've bitten off more than you can chew. Farewell, "+npchar.name+".";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "8");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
		
		case "Havana_fort_3":
			dialog.text = "I knew that you'd agree. Now, hear the details. The fort of Havana has always been a hard target, but it is even harder now.\nTwo ships of the line are guarding the shores of Cuba, and you must deal with them first before you storm the fort...";
			link.l1 = "I see. It won't be the first time I've fought Line Ships, ha-ha. How much time do I have?";
			link.l1.go = "Havana_fort_4";
		break;
		
		case "Havana_fort_4":
			dialog.text = "Not much. Three weeks at most, and after that the slaves will be moved to the Spanish outposts of Cuba. You have to hurry. ";
			link.l1 = "Let's not waste our time then. I am on my way!";
			link.l1.go = "Havana_fort_5";
		break;
		
		case "Havana_fort_5":
			dialog.text = "One moment!"+pchar.name+", you and I have never had any misunderstandings or disagreements. Nevertheless, I want you to know what is going on here. I count on you, and the client counts on me\nWe have invested a great deal of effort and money in this operation. Every single slave, all five thousand, must be delivered to me\nOtherwise, we will be forced to take very drastic measures against you. No offence, this is only a warning. ";
			link.l1 = "Don't worry, "+npchar.name+", I understand what business is, which is why you should also remember to pay me once I deliver them. Farewell.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "24");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			pchar.quest.Slavetrader_HavanaAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_HavanaAttack.win_condition.l1.location = "Cuba2";//отправляем в локацию
            pchar.quest.Slavetrader_HavanaAttack.function = "Slavetrader_CreateLineShips";//создание линейных кораблей
			SetFunctionTimerCondition("Slavetrader_HavanaOver", 0, 0, 20, false);	//таймер
			characters[GetCharacterIndex("Havana_Mayor")].dialog.captureNode = "Slavetrader_HavanaAttack"; //капитулянтская нода мэра
			pchar.questTemp.Slavetrader = "wait1";
		break;
		
		case "Win_Havana_Fort":
			pchar.quest.Slavetrader_FiveTSlavesOver.over = "yes";
			amount = 5000 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			if (amount < 1)
			{
				dialog.text = "Well... And what about the prize for your victory?";
				link.l1 = "I have "+sTemp+" slaves.";
				link.l1.go = "Havana_Fort_yes";
				break;
			}
			if (amount < 4500 && amount >= 1)
			{
				dialog.text = "Well, well. Did you forget what I said? You were supposed to bring me no less than five thousand slaves, and you've got "+sTemp+". Why is that?";
				link.l1 = "Hmm... Some of them didn't survive the journey from Havana... food and medicine were running low.";
				link.l1.go = "Havana_Fort_no";
				break;
			}
			dialog.text = "Well, well... Are you trying to cheat me? Did you forget what I said? Where are my slaves, I ask you! Where are they?!";
			link.l1 = "Hm... Well, you see...";
			link.l1.go = "Havana_Fort_no";
		break;
		
		case "Havana_Fort_no":
			dialog.text = "Fine. I don't need your explanations. We had a deal, and I will give you one week to get no less than five thousand slaves. You will have a lot of problems otherwise.";
			link.l1 = "Fine, fine, just relax, I'll get them for you.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "29");
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("Slavetrader_HavanaSeekOver", 0, 0, 14, false);
			} 
			else SetFunctionTimerCondition("Slavetrader_HavanaSeekOver", 0, 0, 7, false);
			pchar.questTemp.Slavetrader = "Havana_seekslaves";
		break;
		
		case "Havana_Fort_yes":
			dialog.text = "Splendid! You have accomplished my task just as always. I am very pleased with you.";
			link.l1 = "So am I... But I would be even more pleased when I receive my money for the cargo.";
			link.l1.go = "Havana_Fort_yes_1";
		break;
		
		case "Havana_Fort_yesA":
		dialog.text = "I am very glad for that. You were late, but you accomplished my task in the most excellent way.";
			link.l1 = "And now I want to get paid for the cargo.";
			link.l1.go = "Havana_Fort_yes_1";
			pchar.quest.Slavetrader_HavanaSeekOver.over = "yes";
		break;
		
		case "Havana_Fort_yes_1":
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*200;
			dialog.text = "Sure. I am going to sell the slaves to my client, he'll pay and you'll get your coins. Just like last time. Let's see, you've brought here "+sTemp+" slaves. The sum is "+FindRussianMoneyString(iSlaveMoney)+". Come here for the payment in a week.";
			link.l1 = "Fine, "+npchar.name+", we have a deal. I'll be here in a week. But be very careful...";
			link.l1.go = "Havana_Fort_yes_2";
			RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
		break;
		
		case "Havana_Fort_yes_2":
			dialog.text = ""+pchar.name+", please, don't. We are partners and there is no room for cheating or distrust between us. I promised you plenty of coins and you've received them. I promised you interesting tasks and you've had those too. I have always compensated your expenses, even in the darkest days for my business. Have I ever failed to keep my word?";
			link.l1 = "Hmm... No... I just want to get paid, that's all.";
			link.l1.go = "Havana_Fort_yes_3";
		break;
		
		case "Havana_Fort_yes_3":
			dialog.text = "See now..."+pchar.name+", you are my best agent and I am counting on doing business with you again in the future. ";
			link.l1 = "Fine, "+npchar.name+". But you must understand me as well - a million pesos is a huge sum.";
			link.l1.go = "Havana_Fort_yes_4";
		break;
		
		case "Havana_Fort_yes_4":
			dialog.text = "I understand you very well, but I have to sell the slaves first, and only then will I receive the money.";
			link.l1 = "Fine. I think we understand each other.";
			link.l1.go = "Havana_Fort_yes_5";
		break;
		
		case "Havana_Fort_yes_5":
			dialog.text = "Splendid. See you in a week. Now I must prepare and leave to trade with my client.";
			link.l1 = "I won't bother you then. See you in a week, "+npchar.name+".";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader.Name = npchar.name;
			AddQuestRecord("Slavetrader", "32");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_6");
			SetFunctionTimerCondition("Slavetrader_UsurerEscape", 0, 0, 8, false);
			pchar.questTemp.Slavetrader = "wait_6";
			pchar.questTemp.Slavetrader.Cityname = npchar.city +"_town";
			LocatorReloadEnterDisable(npchar.city +"_town", "reload8_back", true);//чтобы не ходил неделю сюда вообще
		break;

		case "Usurer_Escape":
			dialog.text = "What am I doing here? Well... it's my bank. I bought it two days ago. You are my first client and I can offer you very tempting credit terms...";
			link.l1 = "To hell with the credits! Where is "+pchar.questTemp.Slavetrader.Name+"?";
			link.l1.go = "Usurer_Escape_1";
		break;

		case "Usurer_Escape_1":
			dialog.text = "Calm down, please! He ran away a long time ago.";
			link.l1 = "How?";
			link.l1.go = "Usurer_Escape_2";
		break;
		
		case "Usurer_Escape_2":
			dialog.text = "Don't you know? He disappeared a week ago. Turns out he took all his clients' investments. They say even the governor suffered. This house was left behind and I bought it from the colony.";
			link.l1 = "Disappeared? How?";
			link.l1.go = "Usurer_Escape_3";
		break;
		
		case "Usurer_Escape_3":
			dialog.text = "I've heard that he has run away from our colony... I take it that he owes you too. A lot?";
			link.l1 = "More than a million! But I'll get this rat anyway! Where has he gone? The name of his ship?";
			link.l1.go = "Usurer_Escape_4";
		break;
		
		case "Usurer_Escape_4":
			dialog.text = "Nobody knows. Seriously. He just disappeared. The ship named 'Mauritius' or 'Maurdius' sailed away that day; perhaps he used it to escape.";
			link.l1 = "Fuck! And I trusted that bastard! He smelled like a traitor from the very first day! And I was foolish enough to believe we were true partners! But I'll make him regret it one day... Fine,"+npchar.name+", I apologize for my behavior... If you are a good man, I will deal with you in the future, be sure of it, but for now, farewell.";
			link.l1.go = "Usurer_Escape_5";
		break;
		
		case "Usurer_Escape_5":
			string sColony;
			sColony = npchar.city;
			SetNull2Deposit(sColony);
			dialog.text = "It is all right. I understand. If you need some money or want to invest, I am always at your service.";
			link.l1 = "Thanks. But I'd better keep my money to myself. See you.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "33");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "wait1";
			pchar.questTemp.SanBoxTarget.Slavetrader = true;
			ChangeCharacterComplexReputation(pchar, "fame", 25);
			LAi_LocationDisableOfficersGen(&Locations[FindLocation(pchar.location)], false); // разблокируем вход офицеров 2015
		break;
	//<--работорговец	

	//--> семейная реликвия
		case "Noblelombard":
			dialog.text = "Oh really? It seems he doesn't want to talk to me himself.... Fine, let's discuss the matter with you. "+pchar.GenQuest.Noblelombard.Name+" owes me "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Summ))+": "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Money))+" and also my interest - "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Percent))+" for three months. If I don't see the money in the next day, then I will sell his relic, and I don't care about its value to him. Business is business.";
			if(sti(pchar.money) >= sti(pchar.GenQuest.Noblelombard.Summ))
			{
				link.l1 = "Splendid! In that case, I am going to pay you the whole sum with all of the interest immediately - "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Summ))+". He will take his relic himself. Here is your money.";
				link.l1.go = "Noblelombard_1";
			}
			if(sti(pchar.money) >= sti(pchar.GenQuest.Noblelombard.Percent)*2)
			{
				link.l2 = "My client will have the money in three months. Let's make a deal, I'll pay you the interest for the past three months and for the next three months."+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Percent)*2)+". And the debt itself will be paid to you later.";
				link.l2.go = "Noblelombard_2";
			}
			if(sti(pchar.money) >= sti(pchar.GenQuest.Noblelombard.Percent))
			{
				link.l3 = "My client will have the money in three months. How about I pay you the interest for the last three months and you wait until my client has enough money?";
				link.l3.go = "Noblelombard_3";
			}
			link.l4 = "This rarity costs a fortune! It looks like my client will have to pay for it himself.";
			link.l4.go = "Noblelombard_4";
			pchar.quest.noblelombard = "true";//лесник с нпчара на пчара
		break;
		
		case "Noblelombard_1":
			dialog.text = "Excellent! It all turned out well, I got my money and "+pchar.GenQuest.Noblelombard.Name+" will get his relic back.";
			link.l1 = "Pleasure doing business with you, "+npchar.name+"! Farewell for now.";
			link.l1.go = "exit";
			pchar.GenQuest.Noblelombard.Regard = sti(pchar.GenQuest.Noblelombard.Summ)*2;
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Noblelombard.Summ));
			pchar.GenQuest.Noblelombard = "full";
			AddCharacterExpToSkill(pchar, "Leadership", 150);
	
		break;
		
		case "Noblelombard_2":
			if(sti(pchar.GenQuest.Noblelombard.Chance) < 7)
			{
				dialog.text = "Hm... Fine. This works for me. But if "+pchar.GenQuest.Noblelombard.Name+" doesn't find the money in three months, then I won't grant another extension. Make sure he knows that.";
				link.l1 = "I will! I am glad that we have made a deal. Farewell now.";
				link.l1.go = "exit";
				pchar.GenQuest.Noblelombard.Regard = sti(pchar.GenQuest.Noblelombard.Percent)*4;
				AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Noblelombard.Percent)*2);
				pchar.GenQuest.Noblelombard = "maxpercent";
				AddCharacterExpToSkill(pchar, "Leadership", 50);
				AddCharacterExpToSkill(pchar, "Fortune", 70);
			
			}
			else
			{
				dialog.text = "No. It won't work. I need the entire sum before sunset. Make sure your 'client' knows that. I have nothing more to tell you.";
				link.l1 = "Hm... fine. Too bad you don't want to compromise.";
				link.l1.go = "Noblelombard_4";
				AddCharacterExpToSkill(pchar, "Fortune", 30);
			
			}
		break;
		
		case "Noblelombard_3":
			if(sti(pchar.GenQuest.Noblelombard.Chance) < 3)
			{
				dialog.text = "Hm... Fine. I accept it only out of respect for your client. But if "+pchar.GenQuest.Noblelombard.Name+" doesn't find the money in three months, then I won't grant another extension. Make sure he knows that.";
				link.l1 = "I will! I'm glad we made a deal. Farewell now.";
				link.l1.go = "exit";
				pchar.GenQuest.Noblelombard.Regard = sti(pchar.GenQuest.Noblelombard.Percent)*2;
				AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Noblelombard.Percent));
				pchar.GenQuest.Noblelombard = "minpercent";
				AddCharacterExpToSkill(pchar, "Leadership", 50);
				AddCharacterExpToSkill(pchar, "Fortune", 150);
			}
			else
			{
				dialog.text = "No. It won't work. I need the whole sum before sunset. Make sure your 'client' knows that. I have nothing more to tell you.";
				link.l1 = "Hm... fine. Too bad you don't want to compromise.";
				link.l1.go = "Noblelombard_4";
				AddCharacterExpToSkill(pchar, "Fortune", 60);
	
			}
		break;
		
		case "Noblelombard_4":
			DialogExit();
			pchar.GenQuest.Noblelombard = "fail";
		break;
		
		case "Noblelombard_5":
			if(sti(pchar.GenQuest.Noblelombard.Chance) == 9)
			{
				dialog.text = "You don't say! "+pchar.GenQuest.Noblelombard.Name+" hasn't opened a deposit in your name. He is not even in our colony - sailed away to Europe. I tell you, I've never seen such a dishonest man. He tried to cheat me but failed - I have a few tricks of my own...";
				link.l1 = "Bastard! He gave me his word....";
				link.l1.go = "Noblelombard_6";
			}
			else
			{	// Addon-2016 Jason уменьшаем раздачу дублонов
				dialog.text = "Correct. "+pchar.GenQuest.Noblelombard.Name+" has made a deposit in your name. Please, take it...";
				link.l1 = "Splendid! Farewell, "+npchar.name+".";
				link.l1.go = "Noblelombard_9";
			}
		break;
		
		case "Noblelombard_6":
			dialog.text = "There is no such thing for people like "+pchar.GenQuest.Noblelombard.Name+" because they have neither honour nor conscience. I take it he has cheated on you?";
			link.l1 = "He has, I suppose. Whatever, "+npchar.name+", I am not going to stay here for long either, and Europe is small... Maybe we will meet one day. Farewell!";
			link.l1.go = "Noblelombard_7";
		break;
		
		case "Noblelombard_7":
			DialogExit();
			AddQuestRecord("Noblelombard", "6");
			AddQuestUserData("Noblelombard", "sName", pchar.GenQuest.Noblelombard.Name);
			CloseQuestHeader("Noblelombard");
			DeleteAttribute(Pchar, "GenQuest.Noblelombard");
			DeleteAttribute(Pchar, "quest.noblelombard"); // лесник с нпчара на пчара
		break;
		
		case "Noblelombard_9":
			DialogExit();
			iTemp = sti(pchar.GenQuest.Noblelombard.Regard); // Addon-2016 Jason уменьшаем раздачу дублонов
			AddMoneyToCharacter(pchar, iTemp);
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Noblelombard", "7");
			AddQuestUserData("Noblelombard", "sName", pchar.GenQuest.Noblelombard.Name);
			CloseQuestHeader("Noblelombard");
			DeleteAttribute(Pchar, "GenQuest.Noblelombard");
			DeleteAttribute(Pchar, "quest.noblelombard");// с нпчара на пчара  лесник
		break;
//<-- семейная реликвия

		// Бремя гасконца
		case "sharlie_credit":
			dialog.text = "Monsieur, I don't know you. I lend money only to local citizens or to captains. Pardon me...";
			link.l1 = "I see. That's a pity though.";
			link.l1.go = "exit";
		break;
		// Бремя гасконца
		
		// Addon-2016 Jason, французские миниквесты (ФМК)
		// ФМК-Гваделупа
		case "FMQG_x":
			DelLandQuestMark(npchar);
			dialog.text = "Wh-what... What do you mean?";
			link.l1 = "You are a fucking rat! Now listen to me very carefully: I am not that stupid. Pinette wrote two copies of the letter. I gave you one of them, the second is in the possession of my trusted agent. If anything happens to me - my man will deliver it straight into the hands of the governor...";
			link.l1.go = "FMQG_x1";
		break;
		
		case "FMQG_x1":
			dialog.text = "";
			link.l1 = "So I suggest you pray for my good health in church at every morning sermon instead of sending assassins after my life. One last warning! Make a move against me and you are fucked. Got it? Good. Take a deep breath and keep counting your doubloons.";
			link.l1.go = "FMQG_x2";
		break;
		
		case "FMQG_x2":
			DialogExit();
			pchar.questTemp.FMQG = "end";
			FMQ_Count();
			AddQuestRecord("FMQ_Guadeloupe", "27");
			CloseQuestHeader("FMQ_Guadeloupe");
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			AddCharacterExpToSkill(pchar, "Sneak", 400);
			AddCharacterExpToSkill(pchar, "Sailing", 200);
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		break;
		
		// Другое
		case "NeHochuRazgovarivat":
			dialog.text = "I don't want to talk to you.";
			link.l1 = "...";
			link.l1.go = "exit";
		break;
		
		// Леди Бет -->
		case "LadyBeth_Usurer_1":
			dialog.text = "Of course! Many just want to get their money and leave. Especially considering the recent rumours...";
			link.l1 = "What rumors?";
			link.l1.go = "LadyBeth_Usurer_2";
		break;
		
		case "LadyBeth_Usurer_2":
			dialog.text = "They say conditions among the crew are getting worse. Monsieur Blackwood has even started to tolerate regular losses - something that never happened before. But that's not my business. I just sell goods. So what are you interested in?";
			link.l1 = "Let's get down to business.";
			link.l1.go = "next";
			npchar.quest.item_date = "LadyBeth";
			pchar.questTemp.LadyBeth_Usurer = true;
		break;
		// Леди Бет <--
	}	
}

// ugeen проверка, можем ли мы использовать дублоны в качестве вклада
bool CheckUseDublons(ref NPChar)
{
	int iTest 	= FindColony(NPChar.City); // город банка
	if(iTest == -1) return false;
	
	ref rColony = GetColonyByIndex(iTest);
	 	 
	bool bOk1 = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea); 
	bool bOk2 = (GetCharacterItem(pchar,"gold_dublon") > 10) || (CheckItemMyCabin("gold_dublon") > 10);
	
	if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && bOk1 && bOk2) return true;

	return false;
}

void SlavetraderGalleonInWorld()
{
	//создаем галеон с рабами
	ref sld;
	string sName;
	sName = pchar.questTemp.Slavetrader.ShipName;
	sld = GetCharacter(NPC_GenerateCharacter("GaleonCap", "", "man", "man", 45, SPAIN, 20, true, "quest"));
	FantomMakeCoolSailor(sld, SHIP_LINESHIP, sName, CANNON_TYPE_CANNON_LBS42, 100, 100, 100);
	FantomMakeCoolFighter(sld, 45, 100, 100, "blade_21", "pistol5", "bullet", 100);
	sld.Ship.Mode = "war";	
	SetCaptanModelByEncType(sld, "war");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;
	sld.DontRansackCaptain = true;
	sld.WatchFort = true;
	sld.AlwaysEnemy = true;


	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "MusketsShoot");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	SetCharacterGoods(sld, GOOD_SLAVES, 3000 + rand(200));//положить в трюм рабов
	sld.ship.Crew.Morale = 100;
	ChangeCrewExp(sld, "Sailors", 100);
	ChangeCrewExp(sld, "Cannoners", 100);
	ChangeCrewExp(sld, "Soldiers", 100);
	//в морскую группу кэпа
	string sGroup = "SlaveGalleon";
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation)); 
	pchar.quest.SlaveHalleon_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.SlaveHalleon_AfterBattle.win_condition.l1.group = "SlaveGalleon";
	pchar.quest.SlaveHalleon_AfterBattle.function = "Slavetrader_SlaveHalleon_AfterBattle";
	sld.city = pchar.questTemp.Slavetrader.Island; //определим колонию, из бухты которой выйдет
	sld.cityShore = pchar.questTemp.Slavetrader.Island.Shore;
	sld.quest.targetCity = "Santiago"; //определим колонию, в бухту которой он придёт
	sld.quest.targetShore = GetIslandRandomShoreId(GetArealByCityName(sld.quest.targetCity));
	//Log_TestInfo("Captain of the galleon sailed away from " + sld.city + "and heading to " + sld.quest.targetShore);
	//==> на карту
	sld.mapEnc.type = "trade";
	//выбор типа кораблика на карте
	sld.mapEnc.worldMapShip = "quest_ship";
	sld.mapEnc.Name = "Galleon '" + sName + " '";
	int daysQty = 20; //дней доехать даем с запасом
	Map_CreateTrader(sld.cityShore, sld.quest.targetShore, sld.id, daysQty);//вот он, сам запуск энкаунтера
}

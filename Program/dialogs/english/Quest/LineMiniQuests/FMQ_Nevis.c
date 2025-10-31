// Addon-2016 Jason, французские миниквесты (ФМК) Сент-Кристофер
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "An obvious bug. Tell the devs about it.";
			link.l1 = "Oh, I will.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "seafox":
			DelMapQuestMarkCity("Charles");
			LAi_SetImmortal(npchar, false);
			DelLandQuestMark(npchar);
			LAi_RemoveLoginTime(npchar);
			PlaySound("Voice\English\LE\SeaFox\SeaFox_01.wav");
			dialog.text = TimeGreeting()+", captain. (salutes) Allow me to introduce myself - Lieutenant "+GetFullName(npchar)+", Antigua Maritime Regiment of Foot, garrisoned in St. John's. I have a favour to ask.";
			link.l1 = "Greetings, Lieutenant Gretton. My name is "+GetFullName(pchar)+". What sort of favour?";
			link.l1.go = "seafox_1";
		break;
		
		case "seafox_1":
			dialog.text = "Let me briefly explain the situation. Four of my men and I were sailing from St. Johns to Sint Maarten when a storm hit our ship. The foul weather didn't last long, but it was enough for our old tub to spring a leak. We had to change course and stop here for repairs. That is taking up time we do not have\nWe are in a hurry to get to Sint Maarten, specifically Grand Case Beach. Help me out, captain, and I will make it well worth your while. Two days' voyage for generous pay!";
			link.l1 = "Generous pay it should be indeed, lieutenant, if you want me to clandestinely insert English marines on a Dutch island.";
			link.l1.go = "seafox_2";
		break;
		
		case "seafox_2":
			dialog.text = ""+UpperFirst(GetAddress_Form(PChar))+", this shouldn't concern you. You're in no danger. Just drop us off at the bay, and that's it. So, do we have a deal?";
			link.l1 = "Fine, I'm in. It's not that far from here. Let's hear about that pay.";
			link.l1.go = "seafox_3";
			link.l2 = "I am sorry, but I have urgent business in a different direction and I'd rather not upset the Dutch.";
			link.l2.go = "seafox_exit";
		break;
		
		case "seafox_exit":
			dialog.text = "As you say, captain. I'll keep looking then. Farewell and Godspeed!";
			link.l1 = "Farewell, lieutenant.";
			link.l1.go = "seafox_exit_1";
		break;
		
		case "seafox_exit_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			npchar.lifeday = 0;
		break;
		
		case "seafox_3":
			GiveItem2Character(pchar, "purse2"); 
			Log_Info("You have received a purse of doubloons");
			dialog.text = "Ten thousand pieces of eight. Here's an advance.";
			link.l1 = "Good. Get your men aboard, let's not waste any time.";
			link.l1.go = "seafox_4";
		break;
		
		case "seafox_4":
			dialog.text = "Aye aye, captain!";
			link.l1 = "...";
			link.l1.go = "seafox_5";
		break;
		
		case "seafox_5":
			DialogExit();
			AddQuestRecord("FMQ_Nevis", "1");
			pchar.questTemp.FMQN = "begin";
			
			chrDisableReloadToLocation = false;
			sld = CharacterFromID("FMQN_seafox_1");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload4_back", "", "", "", "", 10.0); // англичане на борт
			sld.location = "None";
			AddPassenger(pchar, sld, false);//добавить пассажира
			SetCharacterRemovable(sld, false);
			pchar.quest.FMQN_sailing.win_condition.l1 = "location";
			pchar.quest.FMQN_sailing.win_condition.l1.location = "Shore40";
			pchar.quest.FMQN_sailing.win_condition.l2 = "Ship_location";
			pchar.quest.FMQN_sailing.win_condition.l2.location = "Shore40";
			pchar.quest.FMQN_sailing.function = "FMQN_ArriveMaarten";
			if(bImCasual)
			{
				NewGameTip(StringFromKey("FMQ_69"));
			}
			else SetFunctionTimerCondition("FMQN_SailingLate", 0, 0, 10, false);
			for(i = 0; i < MAX_LOCATIONS; i++)
			{	
				sld = &Locations[i];
				if (CheckAttribute(sld, "islandId") && sld.islandId == "SentMartin")
				{
					sld.DisableEncounters = true;	
				}
			}
			sld = &Locations[FindLocation("Shore40")];
			sld.QuestlockWeather = "23 Hour";
			AddMapQuestMarkShore("Shore40", true);
		break;
		
		case "seafox_6":
			PlaySound("Voice\English\LE\SeaFox\SeaFox_02.wav");
			dialog.text = "Thank you for the smooth voyage, captain! I am very sorry for this, but I can't pay you at this very moment... There was supposed to be one of our luggers in this area, but she's not here. As you can clearly see. I have to ask for your help one more time. Could you wait around this bay for two or three days? We have to go and take a look around. Once we return, take us to Antigua. Colonel Fox will reward you generously.";
			link.l1 = "Hmm... This isn't exactly what we agreed on...";
			link.l1.go = "seafox_7";
		break;
		
		case "seafox_7":
			dialog.text = "Please don't be frustrated, captain. I know how you must feel, but alas: I have no money at all. I can promise you that you will receive compensation for both voyages and for waiting for us here, as well as the thanks of Colonel Fox himself!";
			link.l1 = "I can't exactly leave you out to dry... Very well, Lieutenant Gretton. I will wait for three days, but no longer.";
			link.l1.go = "seafox_8";
		break;
		
		case "seafox_8":
			dialog.text = "Thank you, "+GetAddress_Form(NPChar)+"! We're heading inland. I swear we'll be back in 72 hours, not a minute longer.";
			link.l1 = "Godspeed, lieutenant. Don't get caught.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_EnglishmanGo");
		break;
		
		case "seafox_9":
			DelLandQuestMark(npchar);
			PlaySound("Voice\English\LE\SeaFox\SeaFox_02.wav");
			dialog.text = "What a chance meeting! I thought you'd be waiting for us at Grand Case Beach, Captain "+pchar.lastname+"!";
			link.l1 = "Hello, Lieutenant, the surprise is mutual. I didn't expect to see you dressed like a Dutch soldier.";
			link.l1.go = "seafox_10";
		break;
		
		case "seafox_10":
			dialog.text = "It's our disguise... Why are you out here, "+GetAddress_Form(NPChar)+"?";
			link.l1 = "That's a dangerous disguise, mate. Spies are liable to be summarily executed without trial. And speaking of execution, if you want to avoid yours, you'd better listen.";
			link.l1.go = "seafox_11";
		break;
		
		case "seafox_11":
			dialog.text = "You have my full attention.";
			link.l1 = "I sailed to Philipsburg and spoke with the locals after you disembarked. The Dutch are onto you. They know about your mission to rescue those captured high-ranking English officers.";
			link.l1.go = "seafox_12";
		break;
		
		case "seafox_12":
			dialog.text = "Damn and blast it! How the hell did they find out about this?";
			link.l1 = "One of the captured English officers. In return for his freedom, he told the Dutch everything he knew about the rescue operation. All of Philipsburg is ready for you and your men to try and enter the city. To make matters worse, a Dutch corvette is patrolling the sea around Sint Maarten. It is a trap, lieutenant.";
			link.l1.go = "seafox_13";
		break;
		
		case "seafox_13":
			dialog.text = RandSwear()+"That dishonourable villain! I'll find out who that traitor is and denounce him before Parliament!";
			link.l1 = "That will have to wait, Mr. Gretton. Get back to Grand Case Beach tonight and return to my ship before they catch you.";
			link.l1.go = "seafox_14";
		break;
		
		case "seafox_14":
			dialog.text = "And abandon English gentlemen inside a Dutch prison? I'd sooner die, sir. I will not fail Colonel Fox.";
			link.l1 = "Hm, do you think the Dutch will let you choose between the gallows or a firing squad after they capture you?";
			link.l1.go = "seafox_15";
		break;
		
		case "seafox_15":
			dialog.text = "Don't think they'll just let you sail out of here either, Captain de Maure. We're both in this up to our necks.";
			link.l1 = "Damn, you're probably right. That corvette will come crashing down on us the moment we weigh anchor...";
			link.l1.go = "seafox_16";
		break;
		
		case "seafox_16":
			dialog.text = "The Dutch may know we're coming, but they don't know *how* we're coming. We've already taken care of the disguise – take a look at this uniform. Lovely, isn't it? If our plan hadn't been betrayed, we would have just gone to the local prison, taken them by surprise, and killed everyone inside. But they're certainly lying in ambush there. So we improvise. Captain, go to Philipsburg's church and find a preacher there named Filippe Jacobsen. He should be there from six till ten o'clock in the morning. Filippe is one of our men on the inside. Tell him this password: 'How long ago did the captive sailors confess?'. After that, tell him about the situation and demand his assistance in Colonel Fox's name. Then you deliver his answer to me. Simple, and no risk to you.";
			link.l1 = "Sounds pretty damn risky asking about confession in a Dutch Calvinist church, lieutenant. The pastor would try to hang me for being a papist. Alright, tell me about these uniforms... did you take this off a Dutch patrol?";
			link.l1.go = "seafox_17";
		break;
		
		case "seafox_17":
			dialog.text = "Yes, sir.";
			link.l1 = "And where are they now?";
			link.l1.go = "seafox_18";
		break;
		
		case "seafox_18":
			dialog.text = "Held hostage in the bushes not far from this cave.";
			link.l1 = "Understood. Keep them safe, I am heading into town. Wait for me here and stay low – the Dutch are scouring the jungle as well as the seas looking for you.";
			link.l1.go = "seafox_19";
		break;
		
		case "seafox_19":
			dialog.text = "We'll be as quiet as church mice, captain. Please hurry!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_ToChurch");
		break;
		
		case "seafox_20":
			PlaySound("Voice\English\soldier_common_4.wav");
			DelLandQuestMark(npchar);
			dialog.text = "You're back? Captain, what are you doing here? Go to town, you're drawing attention to our hideout!";
			link.l1 = "I am back from town. What kind of games are you English playing?";
			link.l1.go = "seafox_21";
		break;
		
		case "seafox_21":
			dialog.text = "I beg your pardon?";
			link.l1 = "I went to the church. Big building, nice and austere, just the way those Dutch iconoclasts like it. Guess what, lieutenant? There is no preacher named Filippe Jacobsen.";
			link.l1.go = "seafox_22";
		break;
		
		case "seafox_22":
			dialog.text = "That's impossible, he visits the place every morning-";
			link.l1 = "Shut up and listen to me! If your Jacobsen even exists at all, he doesn't go to church! They've never seen him! Not in the morning, not in the evening! God fucking damn it! Why did I even agree to this fucking job?! Led by a stupid whoreson greenhorn idiot, wet behind the ears lieutenant-";
			link.l1.go = "seafox_23";
		break;
		
		case "seafox_23":
			dialog.text = "Sir, I demand satisfaction for that insult. Once we are out of here, we shall duel according to the customs of-";
			link.l1 = ""+RandSwear()+"";
			link.l1.go = "seafox_24";
		break;
		
		case "seafox_24":
			PlaySound("Ambient\Jail\chain.wav");
			PlaySound("Ambient\Land\door_001.wav");
			dialog.text = "Shut the hell up, all of you!!! ... I just heard something.";
			link.l1 = "";
			link.l1.go = "seafox_25";
		break;
		
		case "seafox_25":
			if (pchar.sex == "man") {PlaySound("VOICE\English\LE\SeaFox\SeaFox_04.wav");}
			dialog.text = "Zounds, someone's outside! You! You brought the Dutch back here, you scoundrel!";
			link.l1 = ""+RandSwear()+"!!!";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_HollandBattleFight");
		break;
		
		case "seafox_26":
			DelLandQuestMark(npchar);
			pchar.quest.FMQN_fail1.over = "yes";
			PlaySound("Voice\English\LE\SeaFox\SeaFox_02.wav");
			dialog.text = "Glad to see you, sir. What news?";
			link.l1 = "I met your man. This evening he will deliver some 'flavoured' wine to the prison garrison. He got a potion from a gypsy, not lethal, but they'll sleep like the dead. You need to get in there tonight and get your captured gentlemen out. By the way, this wine delivery cost me twenty-five doubloons. Be sure to mention that in the report.";
			link.l1.go = "seafox_27";
		break;
		
		case "seafox_27":
			dialog.text = "Don't worry about the money. Captain, I'd like you to join us in this operation and show us the way to the prison. You've been to Philipsburg before, so you know the city better than we do. No need to go inside the prison with us, we'll handle the breakout ourselves. Just get us to the door.";
			link.l1 = "Damn my eyes, Mr. Gretton, this job keeps getting better and better. The pay had better be increasing commensurately.";
			link.l1.go = "seafox_28";
		break;
		
		case "seafox_28":
			dialog.text = "It most certainly is, captain. You won't regret helping us. Is your vessel at Grand Case Beach?";
			if (pchar.location.from_sea == "Shore40")
			{
				link.l1 = "Aye.";
				link.l1.go = "seafox_29";
			}
			else
			{
				link.l1 = "No.";
				link.l1.go = "seafox_29x";
			}
		break;
		
		case "seafox_29":
			dialog.text = "Good. Then get ready and meet us at the town gates by eleven o'clock in the evening.";
			link.l1 = "See you there.";
			link.l1.go = "seafox_30";
		break;
		
		case "seafox_29x":
			dialog.text = "Be sure to move her there, because we have to get our men out through the jungle. Sailing from the port or Simpson Bay is impossible because of the fort. Get everything ready and meet us at the town gates by eleven o'clock in the evening.";
			link.l1 = "See you there.";
			link.l1.go = "seafox_30";
		break;
		
		case "seafox_30":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddDialogExitQuestFunction("FMQN_EnglandPrepare");
		break;
		
		case "seafox_31":
			PlaySound("Voice\English\Gr_hovernor01.wav");
			dialog.text = "Ready, captain?";
			link.l1 = "Yes.";
			link.l1.go = "seafox_32";
		break;
		
		case "seafox_32":
			dialog.text = "Let's get moving then.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_EnglandReload");
		break;
		
		case "seafox_33":
			dialog.text = "Hush... Captain! It's done, let's get the hell out of here!..";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_EnglandRunToJungle");
		break;
		
		case "seafox_34":
			dialog.text = "I don't know how we pulled it off, but we did it! None of this would have been possible without your help, sir. Now for the relatively easy part - we need to get off Sint Maarten alive and in one piece. Let's get to Grand Case Beach!";
			link.l1 = "Let's move!";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_EnglandRunToShore");
		break;
		
		case "seafox_35":
			PlaySound("Voice\English\LE\SeaFox\SeaFox_05.wav");
			dialog.text = "Captain "+pchar.lastname+"... "+GetAddress_Form(NPChar)+", thank you for your assistance! I beg you, please don't leave port immediately, but stay here for one more day while I report to Colonel Fox. Pay him a visit tomorrow; his office is in the governor's palace.";
			link.l1 = "Very well, Lieutenant Gretton. Please make it worth my while. It's going to take a long time to repair my reputation with the Dutch because of your escapade.";
			link.l1.go = "seafox_36";
		break;
		
		case "seafox_35x":
			PlaySound("Voice\English\LE\SeaFox\SeaFox_05.wav");
			dialog.text = "Thank you for your assistance, captain! You "+GetSexPhrase("acted like a true hero","are a very brave young lady")+", "+GetAddress_Form(NPChar)+"! It's a tragedy that Lieutenant Gretton didn't make it. He died as a true gentleman and a son of England. I'd like to ask to stay here for one more day while I report to Colonel Fox. Pay him a visit tomorrow, his office is in the governor's palace.";
			link.l1 = "Very well. Please make it worth my while. It's going to take a long time to repair my reputation with the Dutch because of your escapade.";
			link.l1.go = "seafox_36";
		break;
		
		case "seafox_36":
			dialog.text = "Don't worry, "+GetAddress_Form(NPChar)+". I will give you the highest credit possible in my report. (salutes) It was a pleasure, "+GetAddress_Form(NPChar)+"!";
			link.l1 = "...";
			link.l1.go = "seafox_37";
		break;
		
		case "seafox_37":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", -1);
			pchar.quest.FMQN_eng_reward.win_condition.l1 = "Timer";
			pchar.quest.FMQN_eng_reward.win_condition.l1.date.hour  = 6.0;
			pchar.quest.FMQN_eng_reward.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQN_eng_reward.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQN_eng_reward.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQN_eng_reward.function = "FMQN_EnglandReward";
			AddQuestRecord("FMQ_Nevis", "28");
		break;
		
		case "soldier":
			PlaySound("Voice\English\soldier_common_2.wav");
			dialog.text = "Captain "+GetFullName(pchar)+"?";
			link.l1 = "Hm... Yes, what can I do for you?";
			link.l1.go = "soldier_1";
		break;
		
		case "soldier_1":
			dialog.text = "The port office has informed us of your ship's recent arrival. His Excellency Mynheer Martin Thomas, the governor of Philipsburg, wishes to see you.";
			link.l1 = "Whatever for? Am I under arrest?";
			link.l1.go = "soldier_2";
		break;
		
		case "soldier_2":
			AddLandQuestMark(characterFromId("Marigo_Mayor"), "questmarkmain");
			dialog.text = "Oh no, no, "+GetAddress_Form(NPChar)+" captain, you are not under arrest. The governor has ordered that every newly arrived captain be invited to his palace for coffee and introductions. Follow me!";
			link.l1 = "Sounds like an offer I can't refuse. Lead the way.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_ReloadToGovernor");
		break;
		
		case "hol_officer":
			PlaySound("Voice\English\hol_gov_complete.wav");
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+", show us where you saw those English soldiers.";
			link.l1 = "They're hiding in a cave in the jungle, like common bandits.";
			link.l1.go = "hol_officer_1";
		break;
		
		case "hol_officer_1":
			dialog.text = "Lead on, we are following you!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_HollandBattleMarch");
		break;
		
		case "hol_officer_2":
			PlaySound("Voice\English\hol_gov_quest.wav");
			dialog.text = "Wait, captain! You mentioned that you met the spies over there - near the cave's entrance?";
			link.l1 = "Yes. I briefly saw them go inside after they talked to me.";
			link.l1.go = "hol_officer_3";
		break;
		
		case "hol_officer_3":
			dialog.text = "Most likely they are still in there. If we charge in all at once, they will retreat into the cave. It'll be a nightmare ferreting them out from there... Let's play this smart. Captain, you go there alone and distract them. My men and I will move to that dry well around the corner. It leads right inside the cave. The bastards won't see us coming from behind\nYou go inside and if the spies are still there, talk to them, ask them stupid questions, and keep them busy. Once you have their absolute attention - swear as filthily as you can. You are a sailor, so that should come naturally to you. That'll be our signal. Two of my men will guard the main entrance to prevent their escape that way. We'll get them.";
			link.l1 = "Your plan sounds awfully dangerous to my health. The way I see it, they'll just try to kill me first.";
			link.l1.go = "hol_officer_4";
		break;
		
		case "hol_officer_4":
			dialog.text = "Don't worry, captain. Your goal is to shout as loud as you can as soon as you see the enemy raiding party. If they attack you - then run and keep shouting. My men are well trained, so don't worry, they will take down these spies before you're hurt.";
			link.l1 = "They'd better. I'm heading in there.";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_HollandBattlePosition");
		break;
		
		case "hol_officer_5":
			PlaySound("Voice\English\hol_gov_common.wav");
			dialog.text = "Tough bastards they were... Nicely done, captain, the English dogs are finished. The saboteurs have been eliminated, the commandant and the governor will be pleased.";
			link.l1 = "You took your sweet time, mynheer...";
			link.l1.go = "hol_officer_6";
		break;
		
		case "hol_officer_6":
			dialog.text = "Blame the rope, it had a bucket on the end that made an absolute racket. We had to be careful.";
			link.l1 = "Yeah...the rope. Whatever. One of your missing patrols is tied up over there in the bushes. They should still be alive.";
			link.l1.go = "hol_officer_7";
		break;
		
		case "hol_officer_7":
			dialog.text = "I'll see to them. You should go to town and get some rest. Pay a visit to our governor tomorrow, he'll have my report with a glowing commendation of you in it by then.";
			link.l1 = "I'll do that. Godspeed, mynheer.";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_HollandBattleRest");
		break;
		
		case "monk":
			DelLandQuestMark(npchar);
			DelLandQuestMarkToPhantom();
			if (GetCharacterIndex("marigojailoff") != -1)
			{
				DelLandQuestMark(characterFromId("marigojailoff"));
			}
			pchar.questTemp.FMQN = "way_eng_2";
			dialog.text = "What can I do for you, my son?";
			link.l1 = "Hello pastor, just out of curiosity, how long ago did the captive sailors confess?";
			link.l1.go = "monk_1";
		break;
		
		case "monk_1":
			dialog.text = "Yesterday evening, my son... (whispering) I assume you know the plan has been betrayed?";
			link.l1 = "I wouldn't be standing here otherwise. Lieutenant Casper Gratton and his men are out in the jungle at the moment. They're all dressed as Dutch soldiers, but we need extra assistance since the prison guards are waiting for them.";
			link.l1.go = "monk_2";
		break;
		
		case "monk_2":
			dialog.text = "(loudly) I prayed every day to save his Anglican soul from damnation! (whispering) I have a plan, but I need two dozen gold doubloons to get everything I need.";
			link.l1 = "Expensive plan. What's the money for?";
			link.l1.go = "monk_3";
		break;
		
		case "monk_3":
			dialog.text = "Being a prison guard is dull work. To keep up morale, the officer in charge orders wine every evening to go with their dinner. The wine is brought from a warehouse I have access to. There is a gypsy woman in town who owes me a favour; she will make us a sleeping potion. All I need is to buy a few bottles of good wine, add the potion, and swap the bottles in the warehouse. That's why I need the gold.";
			if (PCharDublonsTotal() >= 24)
			{
				link.l1 = "I have the doubloons. Take them.";
				link.l1.go = "monk_4";
			}
			else
			{
				link.l1 = "Let me head back to my ship and fetch some for you.";
				link.l1.go = "monk_wait";
			}
		break;
		
		case "monk_wait":
			DialogExit();
			npchar.dialog.currentnode = "monk_repeat";
		break;
		
		case "monk_repeat":
			dialog.text = "Ah, my son, do you have the 'donation' we discussed?";
			if (PCharDublonsTotal() >= 24)
			{
				link.l1 = "Yes, here.";
				link.l1.go = "monk_4";
			}
			else
			{
				link.l1 = "I will get it soon enough...";
				link.l1.go = "monk_wait";
			}
		break;
		
		case "monk_4":
			RemoveDublonsFromPCharTotal(24);
			dialog.text = "Splendid. Come see me at the same time tomorrow - I will tell you the results.";
			link.l1 = "Very well...";
			link.l1.go = "monk_5";
		break;
		
		case "monk_5":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("FMQ_Nevis", "18");
			pchar.quest.FMQN_monk.win_condition.l1 = "Timer";
			pchar.quest.FMQN_monk.win_condition.l1.date.hour  = 6.0;
			pchar.quest.FMQN_monk.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQN_monk.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQN_monk.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQN_monk.function = "FMQN_EnglandMonkPlan";
			pchar.quest.FMQN_fail.win_condition.l1 = "Timer";
			pchar.quest.FMQN_fail.win_condition.l1.date.hour  = 11.0;
			pchar.quest.FMQN_fail.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQN_fail.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQN_fail.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQN_fail.function = "FMQN_EnglandFail";
			pchar.questTemp.FMQN = "way_eng_3";
		break;
		
		case "monk_6":
			DelLandQuestMark(npchar);
			pchar.quest.FMQN_fail.over = "yes";
			dialog.text = "Greetings, my son.";
			link.l1 = "Same to you, pastor. Any news?";
			link.l1.go = "monk_6x";
		break;
		
		case "monk_6x":
			dialog.text = "Yes. It's done. The wine has been 'flavoured' and the guards will get a special treat tonight. They have dinner at nine o'clock in the evening, they'll all be sleeping by midnight. This is your only window to do the job, no second chances. Be careful, you can't completely rely on your Dutch disguise.";
			link.l1 = "Got it. Let's not waste any time. Farewell.";
			link.l1.go = "monk_7";
		break;
		
		case "monk_7":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("FMQ_Nevis", "20");
			sld = CharacterFromID("FMQN_seafox_1");
			sld.dialog.currentnode = "seafox_26";
			LAi_CharacterEnableDialog(sld);
			sld.talker = 9;
			AddLandQuestMark(sld, "questmarkmain");
			pchar.quest.FMQN_fail1.win_condition.l1 = "Timer";
			pchar.quest.FMQN_fail1.win_condition.l1.date.hour  = 20.0;
			pchar.quest.FMQN_fail1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.FMQN_fail1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.FMQN_fail1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.FMQN_fail1.function = "FMQN_EnglandFail";
			pchar.questTemp.FMQN = "way_eng_4";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

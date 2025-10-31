// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What do you want? Ask away.","I am listening, what's your question?"),"This is the second time you have tried to ask...","This is the third time you've tried to ask...","When is this going to end?! I am a busy man, working on colony matters, and you are still bothering me!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I changed my mind...","Not now. Wrong place and time."),"True... But later, not now...","I'll ask... But a bit later...","I am sorry, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);			  
			link.l1.go = "exit";
			//Jason, Португалец
			if (CheckAttribute(PChar, "questTemp.Portugal") && pchar.questTemp.Portugal == "ToGovernor")
			{
				link.l1 = "Your Grace, I have absolutely excellent and urgent news for you! I have captured Bartolomeo the Portuguese, the bastard is under guard and awaiting a fair trial! And I am hoping for some modest gratitude from the Company...";
				link.l1.go = "Portugal";
			}
			//Португалец
			
			// Addon-2016 Jason ФМК-Сент-Кристофер
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "governor")
			{
				link.l1 = "You insisted on seeing me, Mynheer Governor...";
				link.l1.go = "FMQN";
			}
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "hol_battle_complete")
			{
				link.l1 = "I am here regarding the matter of the English spies, Mynheer governor...";
				link.l1.go = "FMQN_7";
			}
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple("You have taken everything already. What else do you want?","Is there anything left that you haven't grabbed?");
            link.l1 = RandPhraseSimple("Just looking around...","Just checking, I might forget to take something...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		
		//Jason, Португалец
		case "Portugal":
			dialog.text = "Bartolomeo... Bart the Portuguese is in my town?! Alive?!!";
			link.l1 = "He is, your Grace, and he is under reliable guard. I will hand him over to you after I receive the reward for Bart's head, as promised by the Company. Golden doubloons would be fine too...";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "Bill, doubloons? Are you crazy?! What were you thinking, bringing this beast to my town?! If he is here, then his frigate is not far from the island, and its crew could be in the town itself, right now!";
			link.l1 = "I have killed those who were with him, I don't know about the others, but it doesn't really matter I suppose because Bartolomeo is...";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			dialog.text = "It does! Don't you really understand what you have done?! The 'Albatross' is near the island and you have captured the pirate whose brutality frightens even his own bloodthirsty crew! Get away from here! Get away from the island! And take this monster with you!";
			link.l1 = "But listen, what about the promised reward and...";
			link.l1.go = "Portugal_3";
		break;
		
		case "Portugal_3":
			dialog.text = "I don't want to watch my city burn because of your greed and the Company's vengefulness! There are only fresh recruits in my fort, and half of them will run away as soon as they learn who and why is attacking their ravelins! And then the slaughter will begin... I am not going to risk it, do you hear me?! Get lost and deliver him to Curacao yourself if the Company wants his head that badly!\nDo it immediately, before it's too late! And you may do whatever you want with him, even throw him off your ship's deck, just don't do it in my city!\nHans! Hans, where are you, you lazy idiot! Fetch me a valerian potion or something, and someone, for God's sake, please throw this adventurer out of my residence!";
			link.l1 = "But your Grace...";
			link.l1.go = "Portugal_4";
		break;
		
		case "Portugal_4":
			DialogExit();
			DoQuestReloadToLocation("Marigo_town", "reload", "reload3_back", "PortugalOutResidence");
		break;
		
		// Addon-2016 Jason ФМК-Сент-Кристофер
		case "FMQN":
			DelLandQuestMark(npchar);
			dialog.text = "Very well! Tell me, captain, did you encounter any English military or trade vessels on your approach to our island?";
			link.l1 = "No, Mynheer. I saw neither military nor trade vessels under the English flag within your waters.";
			link.l1.go = "FMQN_1";
		break;
		
		case "FMQN_1":
			dialog.text = "I see. How long do you expect to stay here?";
			link.l1 = "Three days or so...";
			link.l1.go = "FMQN_2";
		break;
		
		case "FMQN_2":
			dialog.text = "In that case, I have an offer for you. According to our intelligence, there is a risk of English spies here. I will give ten thousand pesos as a reward for any information regarding suspicious vessels or people on the island, in the town, its vicinity, on the shores, etc. The reward will be significantly increased if you assist the authorities in detaining or eliminating an enemy.\nEvery civilian captain is welcome to take part in the investigation and to patrol the local shores and jungle in search of spies.\nIt's possible that you'll encounter our military corvette, the Zeepard; don't be alarmed, it is on patrol. You are free to approach its captain if you find any Brits.";
			link.l1 = "Alas, your Excellency, but I am here with only peaceful trading intentions. I will have to leave this island as soon as I resupply and finish my business here.";
			link.l1.go = "FMQN_3";
			link.l2 = "A tempting offer! I think I'll take part and raid the waters and shores of your island. I might even stay here for a while.";
			link.l2.go = "FMQN_5";
		break;
		
		case "FMQN_3":
			dialog.text = "It's just information, captain. No pressure. You know whom to address if you see anything suspicious.";
			link.l1 = "Very well, Mynheer, I understand. Farewell!";
			link.l1.go = "FMQN_4";
		break;
		
		case "FMQN_4":
			DialogExit();
			pchar.questTemp.FMQN = "way_eng_1";
			AddQuestRecord("FMQ_Nevis", "8");
			chrDisableReloadToLocation = false;
			FMQN_SetSoldiersInCave();
		break;
		
		case "FMQN_5":
			dialog.text = "Splendid, captain! Since you are that serious, make sure to talk to our commandant as well. He is responsible for catching spies and he could give you additional information.";
			link.l1 = "Fine, Mynheer. I'll go see him.";
			link.l1.go = "FMQN_6";
		break;
		
		case "FMQN_6":
			DialogExit();
			pchar.questTemp.FMQN = "way_div";
			AddQuestRecord("FMQ_Nevis", "9");
			chrDisableReloadToLocation = false;
			AddLandQuestMarkToPhantom("marigo_prison", "marigoJailOff");
		break;
		
		case "FMQN_7":
			DelLandQuestMark(npchar);
			dialog.text = "We've been waiting for you, Mynheer "+GetFullName(pchar)+". Allow me to express our gratitude for your actions in eliminating the dangerous English raiding party. Please accept these ten thousand pesos. In addition: 200 ship's silk will be loaded into your hold, and a very special reward — a three-year license from the Dutch West India Trading Company. This is an extremely valuable document; I trust you know that?";
			link.l1 = "Of course! A three-year license - this is big for sure.";
			link.l1.go = "FMQN_8";
		break;
		
		case "FMQN_8":
			dialog.text = "Please, take your reward. Besides, you can count on the gratitude of all Dutch citizens and authorities. You are a sensation in Philipsburg, and we'd be glad to see you again.";
			link.l1 = "Hearing such warm words is more valuable than the license. Thank you, it was a pleasure. And now, I should be on my way. Goodbye!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_HollandBattleComplete");
		break;
		
		// Jason НСО
		case "tomas":
			dialog.text = "We surrender! In the name of all that is holy, I beg you, do not loot or pillage Philipsburg and its citizens! I am ready to hear your demands!";
			link.l1 = "Do not worry about the citizens, Mynheer. Subjects of the French Crown should not be afraid of French soldiers.";
			link.l1.go = "tomas_1";
		break;
		
		case "tomas_1":
			dialog.text = "The French Crown?";
			link.l1 = "Exactly. This island belongs to France, and you are only tenants here. Impudent tenants, who believed this island could be their property. From today onwards, Dutch authority in Saint Maarten has come to an end. Is that clear?";
			link.l1.go = "tomas_2";
		break;
		
		case "tomas_2":
			dialog.text = "But... But what will happen to us, to the Dutch soldiers who surrendered to you, and to the wounded? And what...";
			link.l1 = "That will depend only on you, Mynheer Thomas. If you do me a favour, then I will allow all those who surrendered to take their wounded and depart from here on a ship or ships that we will find in the docks, to Curaçao, to Mynheer Stuyvesant.";
			link.l1.go = "tomas_2_1";
		break;
		
		case "tomas_2_1":
			dialog.text = "";
			link.l1 = "Otherwise, you will be kept in the holds of my ships and the casemates of Saint Kitts. Also, some important Dutch officials will have to be hanged, just to make sure that Stuyvesant loses his interest in conquering our colonies...";
			link.l1.go = "tomas_3";
		break;
		
		case "tomas_3":
			dialog.text = "(stuttering) Wha... What... about wh...at k-kind of  f-fa... vour?";
			link.l1 = "In the depths of the island lies a bone of contention - a salt mine. I know that there are not only miners and slaves, but also Dutch soldiers, armed to the teeth. They must be from the Company Guard, mustn't they, Mynheer? I will offer them the chance to surrender, or I will use force if they refuse. I need a guide who can show me the way to the mine. Find me such a guide.";
			link.l1.go = "tomas_4";
		break;
		
		case "tomas_4":
			dialog.text = "S-Salt... m-mine?";
			link.l1 = "Exactly. Don't be afraid, Mynheer Thomas, if the guards of the mine are wise enough to give up their arms, I will give them an opportunity to leave the island. I don't need unnecessary bloodshed. Don't worry, your conscience will be clear: even if you don't tell me where the mine is, the island of Saint Maarten is small enough that I can find the mine without your help; I just don't want to waste my time rambling through thickets and marshes. So this deal is more profitable to you than it is to me.";
			link.l1.go = "tomas_5";
		break;
		
		case "tomas_5":
			dialog.text = "F-fi...ne, I will tell you how to get to the mine, b-but you must g-gi...ve me your word that all... all of us will leave this island!";
			link.l1 = "I give you my word as an officer and a nobleman.";
			link.l1.go = "tomas_6";
		break;
		
		case "tomas_6":
			dialog.text = "In Grand Case bay... at its far edge, near the water, there are... there are stones. There... there, behind them, along the shoreline, there is a passage by the water, there... it is shallow there, waist-deep or less. You need to go around the rock and you will reach a big beach, where... where you can't dock your ship because of the reefs around it. From this beach there is a path leading directly... to... to the mine.";
			link.l1 = "Excellent. I'm setting off. And you, Mynheer, will remain here under the diligent watch of my soldiers until I return.";
			link.l1.go = "tomas_7";
		break;
		
		case "tomas_7":
			DialogExit();
			SetReturn_Gover_Dialog_Exit(NPChar);
			LAi_SetActorType(npchar);
			pchar.quest.Patria_BastionGate.win_condition.l1 = "location";
			pchar.quest.Patria_BastionGate.win_condition.l1.location = "Shore40";
			pchar.quest.Patria_BastionGate.function = "Patria_BastionShore";
			AfterTownBattle();
			AddQuestRecord("Patria", "50_1");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

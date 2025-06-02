void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
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
			dialog.text = "What do you want?";
			link.l1 = "Nothing.";
			link.l1.go = "exit";
		break;

		case "Naemnik":
			dialog.text = "You're good"+GetSexPhrase("","ess")+"... damn good"+GetSexPhrase("","ess")+". But before you finish the job, hear me out. I'm sure what I have to say will interest you.";
			link.l1 = "I suppose you can speak your last words before dying. But don’t get your hopes up. You're not leaving this cave.";
			link.l1.go = "Naemnik_2";
		break;

		case "Naemnik_2":
			dialog.text = "Port chief, huh? He sent you for my head?";
			link.l1 = "You're sharp as ever.";
			link.l1.go = "Naemnik_3";
		break;

		case "Naemnik_3":
			dialog.text = "He sent you to kill me, didn’t he? Not to find, not to capture — to kill.";
			link.l1 = "That's right. So what?";
			link.l1.go = "Naemnik_4";
		break;

		case "Naemnik_4":
			dialog.text = "Ha... you're a real "+GetSexPhrase("blockhead","little fool")+". Did you ever stop to think why it was so important to him that I die rather than rot in a cell? No? You’ve no idea who you’re trying to save. That portside spider has spun a web of lies over this whole place, and you, "+GetSexPhrase("boy","darling")+", are stuck deep in it.\nYou think he’s an honest official? Ha! The only time he dreams of honesty is when he sleeps. He sells intel to pirates and Dutchmen. Betrays those who trust him. A vermin like him belongs in the ground!";
			link.l1 = "And who doesn’t trample some dirt with their boots. You don’t look like a monk yourself.";
			link.l1.go = "Naemnik_5";
		break;

		case "Naemnik_5":
			dialog.text = "I’m no monk, and I don’t pretend to be. My blade never lies. One look, and a man knows death’s come for him. I don’t smile at my prey or shake its hand knowing it’s already doomed. No. My intent is clear. That bureaucrat?\nHe betrays everyone who trusts him, all while pretending to help. He’s worse than any bastard I’ve ever put in a grave.";
			link.l1 = "Suppose you’re telling the truth. Who hired you?";
			link.l1.go = "Naemnik_6";
		break;

		case "Naemnik_6":
			dialog.text = "I won’t give you a name – I don’t even know it. But he’s someone wronged by that scum. A man who seeks justice... or revenge. Call it what you will. Five hundred doubloons for the head of that rotten official! Help me, and we’ll split the money.";
			link.l1 = "Enough of your talk! You’d say anything to save your sorry hide. I let you speak, now it’s time to die.";
			link.l1.go = "Naemnik_7";
			link.l2 = "Fine tale. But I won't believe you just like that. Got anything beyond your word? Evidence, witnesses? Or is this just another ploy to cheat death?";
			link.l2.go = "Naemnik_8";
		break;
		
		case "Naemnik_7":
			DialogExit();
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("GS_Naemnik");
			LAi_SetImmortal(sld, false);
			LAi_SetCurHPMax(sld);
			LAi_GetCharacterMaxEnergy(sld);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheckFunction("EnemyFight", "GS_UbivaemNaemnika");
		break;
		
		case "Naemnik_8":
			dialog.text = "These parchments were discovered in a privateer's quarters, a sea-dog my patron vanquished in combat. The villain received his intelligence from none other than the Port Chief himself. Herein are meticulously recorded ship routes, their times of departure, and the nature of their cargo. These same vessels were later plundered, their crews slaughtered or vanished upon the endless blue\nMark this well - the quill-strokes in these notes match precisely those in the official manifests. This evidence shall unmask the traitor. My patron desires these documents be found upon his corpse. A magistrate's bench would not suffice\nThis blackguard commands too much sway, with countless corrupt allies in his pocket. Were he brought before the court, he would slither free from justice's grasp. Such vermin deserve no place among God's breathing creatures. Only death with lasting infamy befits such treachery.";
			link.l1 = "Treacherous dog! Men entrust him with their very fortunes, while he barters their lives to cutthroats and brigands! Count me your ally in this. Such a creature deserves no place beneath God's heaven.";
			link.l1.go = "Naemnik_9";
			GiveItem2Character(PChar, "GS_letters");
			AddQuestRecordInfo("GS_Letters", "1");
		break;

		case "Naemnik_9":
			dialog.text = "I procured a key to his dwelling - through the carpenter who mended furnishings in that lordly mansion. All proceeded as planned until I discovered he shares his quarters. When I entered to dispense justice, his lady wife was present\nHer unexpected company gave me pause. No bounty was offered for her blood, and the crown's men would hunt with far greater zeal for one who slays a woman of standing. Thus I altered my design and lay in wait for him near the customs house instead.";
			link.l1 = "Hellfire and damnation! The whole town stands vigilant now - we cannot strike openly as we might have done before. What course remains to us?";
			link.l1.go = "Naemnik_10";
		break;

		case "Naemnik_10":
			dialog.text = "I've kept watch over the town, biding my time until the commotion subsided. After my attempt, that cowardly rat hurried to hide away his wife. With my own eyes I saw her board a vessel and leave the harbor\nNow he remains alone - the perfect time to finish what we started. Under cover of darkness, you can slip into his lair and end this business. Then leave these damning papers where they cannot be missed, so all may know the foul corruption that festered within his heart\nBut for me, the town gates are barred. You, however... you can succeed where I cannot. No guard searches for your face; you'll pass their watch with ease. His house is near the city prison. Five hundred doubloons! Half this bounty will be yours when the traitor lies dead.";
			link.l1 = "So be it. By my own hand shall this villain be dispatched to meet his maker. These documents shall remain within his dwelling - that all might learn the truth of his perfidy. Await my return. I shall come back once justice has been served.";
			link.l1.go = "Naemnik_11";
		break;
		
		case "Naemnik_11":
			DialogExit();
			chrDisableReloadToLocation = false;
			locations[FindLocation("Beliz_Cave")].DisableEncounters = false;
			AddQuestRecord("GS", "5");
			AddQuestUserData("GS", "sSex", GetSexPhrase("","а"));
			
			sld = CharacterFromID("GS_Naemnik");
			LAi_SetWarriorType(sld);
			LAi_SetCurHPMax(sld);
			LAi_GetCharacterMaxEnergy(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
			NextDiag.CurrentNode = "Naemnik_12";
			
			sld = &Locations[FindLocation("Beliz_town")];
			sld.reload.l11.open_for_night = 1;
			sld = &Locations[FindLocation("Beliz_houseS5_room2")];
			sld.locators_radius.item.button01 = 1.0;
			
			pchar.quest.GS_SoldatyDoma.win_condition.l1 = "Hour";
			pchar.quest.GS_SoldatyDoma.win_condition.l1.start.hour = 0.00;
			pchar.quest.GS_SoldatyDoma.win_condition.l1.finish.hour = 5.00;
			PChar.quest.GS_SoldatyDoma.win_condition.l2 = "location";
			PChar.quest.GS_SoldatyDoma.win_condition.l2.location = "Beliz_houseS5";
			PChar.quest.GS_SoldatyDoma.function = "GS_SoldatyDoma";
		break;
		
		case "Naemnik_12":
			dialog.text = "Why are you standing there frozen, as if your feet were stuck in quicklime?";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Naemnik_12";
		break;

		case "Portman_1":
			dialog.text = "You? What the hell? How did you get in here?";
			link.l1 = "How I got here doesn't matter at all. And I think that deep down you understand why I've come.";
			link.l1.go = "Portman_2";
			DelLandQuestMark(npchar);
		break;

		case "Portman_2":
			dialog.text = "No, I don't understand! If you're here for the reward, then come to the administration tomorrow, I'll give you everything.";
			link.l1 = "Stop pretending to be innocent! I know everything. You sold tips about your clients' ships to pirates. Such a vile person doesn't deserve to hold such positions. Moreover, you don't deserve to live among honest people. Sir, your place is among your own kind - in hell.";
			link.l1.go = "Portman_3";
		break;

		case "Portman_3":
			dialog.text = "Oh, no-no-no! No! You've got it all wrong! Th-they forced me... They came to me and threatened to deal with my family if I didn't help them... you don't understand...";
			link.l1 = "I've had enough of your pathetic excuses! I have your notes in my hands, where you demand your percentage for tips! Your hypocrisy is disgusting, and I no longer intend to tolerate it. Draw your weapon and defend yourself, if you have the courage for it!";
			link.l1.go = "Portman_4";
		break;
		
		case "Portman_4":
			DialogExit();
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Beliz_portman_clone");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheckFunction("EnemyFight", "GS_PortmanDead");
		break;
		
		case "Naemnik_21":
			dialog.text = "So then, what tidings? Is our business concluded?";
			link.l1 = "Did you harbor doubts of me? The wretch strained mightily to wring some pitiful excuse from his lips, but all for nothing. I placed the damning papers where they cannot be missed, just as we agreed.";
			link.l1.go = "Naemnik_22";
		break;

		case "Naemnik_22":
			dialog.text = "Such craven worms as he forever believe they can purchase clemency from Justice's blade with base falsehoods and coin.";
			link.l1 = "Well, his thoughts trouble him no longer. Hand over my payment and I shall take my leave.";
			link.l1.go = "Naemnik_23";
		break;

		case "Naemnik_23":
			dialog.text = "Here are your doubloons, rightly earned. Fine work, I grant you that. Yet mark me well - had my hand held sterner steel when first we crossed blades, our fortunes might have turned quite differently... to your lasting regret. Within those cramped chambers, a proper weapon cannot swing true, so I carried nothing but this wretched toothpick, thinking to dispatch you with swift economy\nHad I foreseen how matters would unfold, I'd have armed myself with a blade more befitting a man of my mettle.";
			link.l1 = "Ha! Our departed friend claimed thee armed like Roland himself before the gorge at Roncesvalles! What a paladin you proved to be.";
			link.l1.go = "Naemnik_24";
			AddItems(pchar, "gold_dublon", 250);
		break;

		case "Naemnik_24":
			dialog.text = "Heh. Fear casts mighty shadows, does it not? You've seen with your own eyes the paltry eating-iron with which I nearly pierced your beating heart.";
			link.l1 = "Are you suggesting that with weightier steel in hand, you might have proven a worthy adversary to me?";
			link.l1.go = "Naemnik_25";
		break;

		case "Naemnik_25":
			dialog.text = "In the mastery of middle-weighted blades, none surpass my skill - this I swear upon my life's blood. Do you doubt? Very well then. I shall impart certain cunning maneuvers that have preserved me through countless perils. Listen closely - these are not mere boastful prattle, but wisdom that may one day save you from an early grave. Such arcane knowledge is seldom shared with any but the most worthy pupils.";
			link.l1 = "...";
			link.l1.go = "Naemnik_26";
		break;
		
		case "Naemnik_26":
			DialogExit();
			SetLaunchFrameFormParam("An hour passes...", "Run_Function", 0, 4.0);
			SetLaunchFrameRunFunctionParam("GS_Spravedlivost_2", 0.0);
			LaunchFrameForm();
		break;

		case "Naemnik_27":
			dialog.text = "...";
			link.l1 = "I see you are indeed a master of your craft. I thank you for your tutelage. But if our business is concluded, I must be on my way.";
			link.l1.go = "Naemnik_28";
			AddComplexSelfExpToScill(0, 500, 0, 0);
		break;

		case "Naemnik_28":
			dialog.text = "Fare well, "+GetSexPhrase("Cap'n","fair lady")+". Let's hope we cross blades no more. It would grieve me to send you to your maker. Ha-ha.";
			link.l1 = "You wouldn't stand a whisper of a chance, even if I were three sheets to the wind and balanced upon a single leg! Farewell, sellsword.";
			link.l1.go = "Naemnik_29";
		break;
		
		case "Naemnik_29":
			DialogExit();
			chrDisableReloadToLocation = false;
			locations[FindLocation("Beliz_Cave")].DisableEncounters = false;
			LAi_SetPlayerType(pchar);
			
			LAi_SetWarriorType(npchar);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PEACE);
			
			AddQuestRecord("GS", "7");
			CloseQuestHeader("GS");
			
			AddSimpleRumourCity("Word has it the Port Chief was found dead in his own home. Documents were discovered on his body proving his involvement in the disappearance of ships. Just imagine—what a disgrace for our town...", "Beliz", 30, 1, "");
			AddSimpleRumourCity("Have you heard the news? Someone snuck into the Port Chief’s house, killed the guards, and took him out. They found notes on the body with routes of missing ships—written in his own hand! A servant of the Crown, yet a traitor in truth! Got what he deserved! And where was the Governor all these years?", "Beliz", 30, 1, "");
			AddSimpleRumourCity("The Port Master is dead! Killed right in his own home! The guards were slaughtered, and among his possessions were notes mapping routes of vanished ships. No doubt about it—he was behind the disappearances! Justice has finally caught up with the scoundrel.", "Beliz", 30, 1, "");
			break;
	}
}
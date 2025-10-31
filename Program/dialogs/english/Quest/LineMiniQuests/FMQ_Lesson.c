// Addon-2016 Jason, французские миниквесты (ФМК) Последний урок
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
		
		case "greguar":
			PlaySound("Voice\English\LE\Greguar\Greguar_04.wav");
			pchar.quest.FMQL_delete_guide.over = "yes";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Fortfrance");
			if (CheckAttribute(pchar, "questTemp.HWIC") || pchar.Ship.Type == SHIP_NOTUSED)
			{
				dialog.text = "Oh, "+GetFullName(pchar)+"! You look different, my friend, and you are successful! They're starting to talk about you, you know? You learn fast, monsieur, I feel really proud of you. I wish you more fortune and luck in the future! A pleasure to meet you again!";
				link.l1 = "Monseigneur Gregoire Valinnie, what a meeting! I owe you a great deal for my humble achievements. Pleasure to meet you too! Good luck!";
				link.l1.go = "greguar_exit_1";
			}
			else
			{
				dialog.text = "Oh, "+GetFullName(pchar)+"! You look different, my friend, and you are successful! They're starting to talk about you, you know? You learn fast, monsieur, I must say you have made me proud.";
				link.l1 = "Monsieur Gregoire Valinnie, what a meeting! I owe you a great deal for my humble achievements. Pleasure to meet you! Let me guess, you have a business proposal for me?";
				link.l1.go = "greguar_1";
			}
		break;
		
		case "greguar_1":
			dialog.text = "Aye! That I do. I'll be brief, time is money. So, a Dutch crown squadron sailing from Brazil to Curaçao with a cargo of goods of strategic value was ambushed by the English between Trinidad and the mainland. One fluyt of the Company managed to flee and moor at the Boca de la Serpienta Coast. They saved part of the cargo, but not for long – they were attacked by a local Indian tribe\nAccording to my information, they wiped out every Dutchman on that coast and took the cargo to their village. The Indians also seized the Dutch firearms but suffered heavy casualties. This is our chance! The Brits and the Dutch are still fighting in that region and are too busy to care about the lost fluyt. For now... You have a ship and a crew. We can sail there, land, and finish off the Indians. The cargo is extremely valuable and there is a great deal of it there\nI have already sent a small expedition to do the scouting – that was all I could afford, money problems, remember? I have a trustworthy buyer, you can count on my sword and my mercenaries. Fifty-fifty split, we have a week to get there. So, my friend, are you in?";
			link.l1 = "Forgive me, monsieur, but I'll pass. I am just off a tough voyage, we don't have enough time for repairs and recruitment. Even in this God-forsaken place, a man can't have everything.";
			link.l1.go = "greguar_exit";
			link.l2 = "It sounds like a dangerous business, with the promise of decent profit and adventure. Of course I am in! Let us not waste any time!";
			link.l2.go = "greguar_2";
		break;
		
		case "greguar_exit":
			dialog.text = "Pity. It's your call then. Godspeed, monsieur, I will head there anyway. A man must try, huh?";
			link.l1 = "Godspeed, Monsieur Valinnie!";
			link.l1.go = "greguar_exit_1";
		break;
		
		case "greguar_exit_1":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload5_back", "none", "", "", "", 20.0);
		break;
		
		case "greguar_2":
			dialog.text = "Right choice, my friend! You could use some extra money, right? How's your brother, by the way?";
			link.l1 = "I can always use extra money. Michel? My brother is in good health and he's bored. I envy him sometimes... Time to set sail!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQL_Begin");
		break;
		
		case "greguar_3":
			PlaySound("Voice\English\QuestMan02.wav");
			dialog.text = "Easy as pie! These were the rookies who survived the skirmish with the Dutch. We should head deeper into the mainland, my expedition must be there!";
			link.l1 = "It seemed too easy... but it's too early to celebrate, monsieur Valinnie. Take a look over there...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQL_SecondCoastBattle");
		break;
		
		case "greguar_4":
			PlaySound("Voice\English\LE\Greguar\Greguar_05.wav");
			dialog.text = "Damn those redskins! They almost had us! Now I'm certain there are only women and children left in the village. Move out!";
			link.l1 = "I am not so sure you mentioned muskets, I didn't see them... Ah, whatever. Let's move!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQL_GoToJungle");
		break;
		
		case "greguar_5":
			PlaySound("Voice\English\LE\Greguar\Greguar_06.wav");
			dialog.text = "Meaning? The Dutch and we must have killed them all!";
			link.l1 = "";
			link.l1.go = "greguar_6";
		break;
		
		case "greguar_6":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Prosper_fmql")) sld = CharacterFromID("FMQL_Prosper");
			else sld = CharacterFromID("FMQL_mercen");
			sld.dialog.currentnode = "prosper_3";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "greguar_7":
			dialog.text = "To flee? Are you mad? We're almost there! Are you scared of a bunch of painted savages?";
			link.l1 = "";
			link.l1.go = "greguar_8";
		break;
		
		case "greguar_8":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Prosper_fmql")) sld = CharacterFromID("FMQL_Prosper");
			else sld = CharacterFromID("FMQL_mercen");
			sld.dialog.currentnode = "prosper_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "greguar_9":
			dialog.text = "The lowest of the low, captain. I am going back to Europe. I am disappointed! In you, in these cowards, and in this bloody region!";
			link.l1 = "...";
			link.l1.go = "greguar_10";
		break;
		
		case "greguar_10":
			DialogExit();
			DoQuestReloadToLocation("shore18", "goto", "goto8", "FMQL_JungleExit");
		break;
		
		case "greguar_11":
			dialog.text = "Phew! We did it!";
			link.l1 = "But at what cost! Look! Almost everyone in our squad is dead. We should retreat, Gregoire, there's no guarantee there aren't more warriors waiting for us. Plus, we simply lack the numbers to carry the loot.";
			link.l1.go = "greguar_12";
		break;
		
		case "greguar_12":
			dialog.text = "Damn it! It's sad, but you're right, "+pchar.name+": even if the savages are all dead, we won't be able to carry away the cargo before the Dutch or the English land here. We must leave now! To hell with this damned coast!";
			link.l1 = "...";
			link.l1.go = "greguar_10";
		break;
		
		case "greguar_13":
			dialog.text = "Phew! We did it! Nicely done, "+pchar.name+"! Now let's move on to the den of savages for our prize! Nothing can stop us now!";
			link.l1 = "We should hurry while the Brits and the Dutch are still busy with each other. Let's go!";
			link.l1.go = "greguar_14";
		break;
		
		case "greguar_14":
			DialogExit();
			DoQuestCheckDelay("FMQL_RunToGrabbing", 1.0);
		break;
		
		case "greguar_15":
			dialog.text = "We did well, "+pchar.name+". Now all we need to do is sell the cargo without arousing any suspicion. I have a reliable buyer, he will be waiting for us at Lamentin Bay at midnight. Don't bring any officers and avoid the place before the meeting, the client is a very nervous fellow.";
			link.l1 = "Business is business. The cargo must be sold and it must be done safely, otherwise my debt to Poincy will grow even higher. Fine, I will be there by midnight.";
			link.l1.go = "greguar_16";
		break;
		
		case "greguar_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "OpenTheDoors", 10.0);
			pchar.quest.FMQL_goods_timer.win_condition.l1 = "Timer";
			pchar.quest.FMQL_goods_timer.win_condition.l1.date.hour  = 0.0;
			pchar.quest.FMQL_goods_timer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQL_goods_timer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQL_goods_timer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQL_goods_timer.function = "FMQL_MeetingOnLamanten";
			AddQuestRecord("FMQ_Lesson", "7");
			LAi_LocationDisableOfficersGen("Shore38", true); // may-16
			LAi_LocationFightDisable(&Locations[FindLocation("Shore38")], true);
			locations[FindLocation("Shore38")].DisableEncounters = true;
			Pchar.GenQuest.Hunter2Pause = true;
		break;
		
		case "greguar_17":
			PlaySound("Voice\English\Master_01.wav");
			pchar.quest.FMQL_goods_over.over = "yes";// лесник снято прерывание на встречу.
			dialog.text = "It is done. The cargo is unloaded, the client is here. Let's do the talking.";
			link.l1 = "...";
			link.l1.go = "greguar_18";
		break;
		
		case "greguar_18":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("FMQL_contra_"+i);
				if (i == 2) 
				{
					LAi_CharacterEnableDialog(sld);
					AddLandQuestMark(sld, "questmarkmain");
				}
			}
		break;
		
		case "greguar_19":
			dialog.text = "Surprise, you bastards!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQL_LookOnGuards");
		break;
		
		case "greguar_20":
			PlaySound("Voice\English\OliverTrast01.wav");
			dialog.text = "Ah, Johnny, what a guy! Great! Do you have anything to say, "+pchar.name+"?";
			link.l1 = "No. Actually, yes! What the hell?!";
			link.l1.go = "greguar_21";
		break;
		
		case "greguar_21":
			dialog.text = "Don't tease the dead man, monsieur. Where are your manners?.. The money is here, the cargo is being taken care of by me and my friends. I didn't send them to the coast, it would have been a waste. Especially sending Johnny there. See that redskin fellow with a culverin in his hands? You know, Johnny never really liked his own tribe.";
			link.l1 = "I see... What now? Are you going to kill me as well?";
			link.l1.go = "greguar_22";
		break;
		
		case "greguar_22":
			dialog.text = "Well, I should. But I am sentimental. Leave and take a quarter of the cash. The cargo and the rest of the money will stay here with me. Don't try to play the hero, this is not the jungles of the mainland. You stand no chance.";
			link.l1 = "And where are your nobility and manners, Gregoire? I didn't expect this from you. I am leaving, but I won't forget this.";
			link.l1.go = "greguar_23";
			link.l2 = "I am not playing the hero, I never have. I will simply kill you all! First these ladies, then the ape with the grenade launcher, and then you!";
			link.l2.go = "greguar_25";
		break;
		
		case "greguar_23":
			dialog.text = "There are neither nobles nor thugs on this beach, monsieur. There are only five men, a big gun, and a victim. This happens here all the time, but you've made the only right choice. Well done. Do you know that instead of you, there could be two others in your shoes, standing right here, right now? They are almost just like you. But you are here and they are not, and I think they will perish because of it.";
			link.l1 = "I don't follow...";
			link.l1.go = "greguar_24";
		break;
		
		case "greguar_24":
			dialog.text = "One day you will. They didn't receive their final lesson. You did. You are welcome. Farewell, monsieur. Welcome to the Caribbean!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQL_PeaceFinal");
		break;
		
		case "greguar_25":
			dialog.text = "Ahh... You are not the brightest student I've had. Very well... to each his own!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQL_BattleOnBeach");
		break;
		
		case "mercen":
			PlaySound("Voice\English\pirat_guard_4.wav");
			dialog.text = "Perfect timing! We barely escaped from the horde of Caribs, they were heading in your direction and, by the look of you, you've already met them. Their village is nearby, but our problems are only just beginning.";
			link.l1 = "";
			link.l1.go = "prosper_2";
		break;
		
		case "prosper":
			dialog.text = ""+GetFullName(pchar)+"! You are here! And why am I not surprised! Perfect timing, my friend. We barely escaped from the horde of Caribs, they were heading in your direction and, by the look of you, you've already met them.";
			link.l1 = "Prosper! And I am surprised! Making holes in the Indians again? Hope Selina's well?";
			link.l1.go = "prosper_1";
		break;
		
		case "prosper_1":
			dialog.text = "It was foolish of me to join this expedition. I wonder if my daughter will ever see me again. Selina? Well, she is sitting at home and dreaming of you! The youngsters of Martinique have lost all hope by now... You know, I don't regret buying this musket anymore. A solid firearm. Reliable. Also, it's an extra reason to take part in another suicide mission, although it's now a bit less suicidal since you've shown up. Their village is nearby, but our problems are only just beginning.";
			link.l1 = "";
			link.l1.go = "prosper_2";
		break;
		
		case "prosper_2":
			DialogExit();
			sld = CharacterFromID("Guide_y");
			sld.dialog.currentnode = "greguar_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "prosper_3":
			dialog.text = "Not all of them. Our scout was shot but still managed to reach their lair. The chief himself is coming here with his guards. And they have Dutch muskets. They have the advantage in numbers and they are furious as hell. The chief is the best warrior of their tribe, his men are devils in the flesh. We must decide quickly, here and now. Either we give them a fight or we flee. I, for one, prefer the latter, to be honest...";
			link.l1 = "";
			link.l1.go = "prosper_4";
		break;
		
		case "prosper_4":
			DialogExit();
			sld = CharacterFromID("Guide_y");
			sld.dialog.currentnode = "greguar_7";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "prosper_5":
			dialog.text = "You haven't seen them, my good man! These 'savages' have muskets and they are surprisingly good with them. Someone has been giving them lessons, that's no doubt! So don't call me a coward again!";
			link.l1 = "Let's calm down and decide what to do. There is still time.";
			link.l1.go = "prosper_6";
		break;
		
		case "prosper_6":
			int n = 0;
			for (i=1; i<=5; i++)
			{
				if (GetCharacterIndex("FMQL_sailor_"+i) != -1) n++;
			}
			dialog.text = "I am listening, "+pchar.name+".";
			if (n > 2 && GetSummonSkillFromName(pchar, SKILL_SNEAK) > 30)
			{
				Notification_Skill(true, 31, SKILL_SNEAK);
				link.l1 = "We will give them a fight, boys! There are goods and money right behind this hill! We are here for them and we are not leaving. No way some bunch of redskins, even with muskets, can stop us! Let's bury the bastards and finish the job! We have enough men, there is a chance to ambush them. Four men will greet them with fire from the flanks and the rest of us will take positions here. Cut their numbers and finish them off!";
				link.l1.go = "prosper_8";
			}
			else
			{
				if (GetCharacterSkill(pchar, SKILL_SNEAK) < 31) Notification_Skill(false, 31, SKILL_SNEAK);
				if (n < 3) notification("Not enough people", "X");
				if (n > 0)
				{
					link.l1 = "We'll give them a fight, boys! There's goods and money just beyond this hill! We're here for them and we're not leaving. No way some bunch of redskins, even with muskets, can stop us! Let's bury the bastards and finish the job!";
					link.l1.go = "prosper_7";
				}
				else
				{
					link.l1 = "Chances are against us in every possible way. Don't forget about the Dutch right behind us.";
					link.l1.go = "prosper_9";
				}
			}
		break;
		
		case "prosper_9":
			DialogExit();
			sld = CharacterFromID("Guide_y");
			sld.dialog.currentnode = "greguar_9";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "prosper_7":
			DialogExit();
			pchar.questTemp.FMQL = "battle";
			AddDialogExitQuestFunction("FMQL_PrepareAttack");
		break;
		
		case "prosper_8":
			DialogExit();
			pchar.questTemp.FMQL = "sneak";
			AddDialogExitQuestFunction("FMQL_PrepareSneakAttack");
		break;
		
		case "prosper_9x":
			dialog.text = "We are alive and we are home! I swear, I've had enough adventures... for the next few months, ha-ha! I should go to my daughter, please come visit us, "+pchar.name+". And please, be careful.";
			link.l1 = "No promises, Prosper. Godspeed!";
			link.l1.go = "prosper_10";
		break;
		
		case "prosper_10":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 10.0);
		break;
		
		case "prosper_11":
			pchar.quest.FMQL_prosper_dead.over = "yes";
			LAi_RemoveCheckMinHP(npchar);
			PlaySound("Voice\English\pirat_guard_4.wav");
			dialog.text = "I warned you, captain, to be careful! I had suspicions about this bastard.";
			link.l1 = "Prosper! Thank you! But how?";
			link.l1.go = "prosper_12";
		break;
		
		case "prosper_12":
			sTemp = "";
			if (CheckAttribute(pchar, "questTemp.FMQL.PirateDead")) sTemp = "Poor lad, even though he was a pirate.";
			dialog.text = "Johnny got too talkative. The redskin fellow on the sand. He came to a brothel and tried to pick up a girl. They refused to serve him, Johnny got furious, started shouting that he would soon be rich, once he and his pals killed some captain in the jungle. I saw what was coming and ran to your officer, who had also managed to gain some notoriety in the town. "+sTemp+" I owe you a great deal, "+pchar.name+", so there is no need to thank me too much.";
			link.l1 = "And still, thank you very much, Prosper! It was tough here... too tough. Want to join my crew? I need an officer like you. It's hard to find loyal men these days, especially sharpshooters.";
			link.l1.go = "prosper_13";
		break;
		
		case "prosper_13":
			dialog.text = "No, my friend. I have obligations to my daughter. She made me swear to leave my adventures behind. That was my last one. Damn, what a pity, but I love my daughter more than anything in the world. Farewell, "+pchar.name+". And... Selina talks about you all the time. Perhaps you could pay us a visit someday?";
			link.l1 = "Who knows, maybe I will... Farewell, Prosper! I wish your daughter finds a good husband... (to oneself) Lesson learned, monsieur Gregoire, lesson learned... to each his own, he said... I will remember this.";
			link.l1.go = "prosper_14";
		break;
		
		case "prosper_14":
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 15.0);
			chrDisableReloadToLocation = false;
			InterfaceStates.Buttons.Save.enable = true; // разрешим сохраняться
			AddQuestRecord("FMQ_Lesson", "15");
			CloseQuestHeader("FMQ_Lesson");
			pchar.questTemp.FMQL = "end";
		break;
		
		case "contra":
			DelLandQuestMark(npchar);
			dialog.text = "Who the hell are you?";
			link.l1 = "We have the cargo. Interested?";
			link.l1.go = "contra_1";
		break;
		
		case "contra_1":
			dialog.text = "Ha. Very interested. My client's especially. What's the take?";
			link.l1 = ""+FindRussianQtyString(sti(pchar.questTemp.FMQL.Sanl))+" of ironwood, "+FindRussianQtyString(sti(pchar.questTemp.FMQL.Silk))+" of ship silk, "+FindRussianQtyString(sti(pchar.questTemp.FMQL.Rope))+" of rope and "+FindRussianQtyString(sti(pchar.questTemp.FMQL.Oil))+" of resin.";
			link.l1.go = "contra_2";
		break;
		
		case "contra_2":// Addon 2016-1 Jason пиратская линейка
			iTotalTemp = 2200*sti(pchar.questTemp.FMQL.Sanl)+1600*sti(pchar.questTemp.FMQL.Silk)+1000*sti(pchar.questTemp.FMQL.Rope)+900*sti(pchar.questTemp.FMQL.Oil);
			dialog.text = "Very well. 2200 pesos for every piece of ironwood, 900 pesos for resin, 1600 pesos for ship silk, and 1000 pesos for ropes. What do we have here... Well, well. "+iTotalTemp+" pesos. Deal?";
			link.l1 = "Deal!";
			link.l1.go = "contra_3";
		break;
		
		case "contra_3":
			LAi_Fade("", "");
			FMQL_CreateGuidesWarriors();
			dialog.text = "Splendid! Bring more. The Dutch never cease to be generous to the redskins... And who are these guests? What the hell?!";
			link.l1 = "";
			link.l1.go = "contra_4";
		break;
		
		case "contra_4":
			DialogExit();
			sld = CharacterFromID("Guide_y");
			sld.dialog.currentnode = "greguar_19";
			AddMoneyToCharacter(sld, iTotalTemp);
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "FMQL_beach":
			pchar.quest.FMQL_pirate_dead.over = "yes";
			LAi_RemoveCheckMinHP(npchar);
			dialog.text = "Yeah, captain. I drank too much before sailing for a reason.";
			link.l1 = "You? How?!";
			link.l1.go = "FMQL_beach_1";
		break;
		
		case "FMQL_beach_1":
			dialog.text = "I am sorry, captain. I had to drink a cup or two after that mess with the Indians. There was a girl, I took a room for a hundred pesos and she... she...";
			link.l1 = "What? Robbed you?";
			link.l1.go = "FMQL_beach_2";
		break;
		
		case "FMQL_beach_2":
			sld = CharacterFromID("FMQL_Prosper");
			dialog.text = "No! She fell in love! Damn it, I should have run away from there! But then your friend shows up, yelling at me about this scum, your former companion, who wants to screw you and kill you.";
			if (LAi_GetCharacterHP(sld) > 0)
			{
				link.l1 = "Well done, Prosper...";
				link.l1.go = "FMQL_beach_3";
			}
			else
			{
				link.l1 = "Prosper... I am so sorry. I will take care of your daughter. Lesson learnt, monsieur Gregoire... What did you say? To each his own? I should remember this.";
				link.l1.go = "FMQL_beach_3";
			}
		break;
		
		case "FMQL_beach_3":
			dialog.text = "Shall we go, captain?";
			link.l1 = "Yeah. Thank you for your service. Stay away from the cup and we will save you from that beauty. Let's go.";
			if (CheckAttribute(pchar, "questTemp.FMQL.ProsperDead")) link.l1.go = "FMQL_beach_5";
			else link.l1.go = "FMQL_beach_4";
		break;
		
		case "FMQL_beach_4": // Проспер жив
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload_sea", "none", "", "", "FMQL_PirateNormal", 10.0);
			sld = CharacterFromID("FMQL_Prosper");
			sld.Dialog.currentnode = "prosper_11";
			sld.MusketerDistance = 20;
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0); 
		break;
		
		case "FMQL_beach_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "FMQL_PirateNormal", 10.0);
			if (sti(pchar.money) >= 20000) DoQuestFunctionDelay("FMQL_MoneyForSelina", 0.5);
			else
			{
				pchar.quest.FMQL_money_20k.win_condition.l1 = "Money";
				pchar.quest.FMQL_money_20k.win_condition.l1.value = 20000;
				pchar.quest.FMQL_money_20k.win_condition.l1.operation = ">=";
				pchar.quest.FMQL_money_20k.function = "FMQL_MoneyForSelina";
			}
			chrDisableReloadToLocation = false;
			InterfaceStates.Buttons.Save.enable = true; // разрешим сохраняться
			AddQuestRecord("FMQ_Lesson", "10");
			CloseQuestHeader("FMQ_Lesson");
			pchar.questTemp.FMQL = "end";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

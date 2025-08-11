// Ришард Шамбон - контрабандист
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	float locx, locy, locz;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "Get lost, friend. I've got nothing to say to blokes who attack people for no reason!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			// --> кольцо
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "find" && CheckAttribute(npchar, "quest.answer_2") && GetNpcQuestPastDayParam(npchar, "quest_date") >= 3 && !CheckAttribute(npchar, "quest.ring"))
			{
				dialog.text = "Oh! Here you are. I was just about to come looking for you. I need you, friend.";
				link.l1 = "You are oddly friendly today, Richard. Well, spit it out. What do you want?";
				link.l1.go = "ring";
				break;
			}
			// <-- кольцо
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "What do you want? To be honest, I'm not in a good mood today - actually, I can't remember the last time I was.";
				link.l1 = "Is it really that bad, friend?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Oh, "+GetFullName(pchar)+"! "+TimeGreeting()+"! What do you want?";
				link.l1 = LinkRandPhrase("Hey Richard, heard any news lately?", "Has anything new happened on the island?", "Will you tell me the last gossip?");
				link.l1.go = "rumours_LSC";
				link.l2 = "I want to ask you a few questions about the island.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Just wanted to see if your mood's improved. 'Bye!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Bad? No, it's not bad, but not good, either. So... what do you want?";
			link.l1 = "Just to say hellp. I am a newcomer here, so I'm just walking around the island and getting to know people.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Really? Fine, then. I'm Richard Shambon. A long time ago I traded valuable goods - some of which were illegal - but for the last nine years I've been scavenging ship's wrecks, searching for scraps, and exchanging them for food and gold.";
			link.l1 = "And I am "+GetFullName(pchar)+", a captain...";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "You mean former captain, ha-ha!";
			link.l1 = "Well, actually, my ship is in Blueweld now; I sailed here on a barque.";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Really? Impossible! And where is your barque now?";
			link.l1 = "At the bottom...";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "Oh... I thought... Whatever, friend. I'm going for some rum...";
			link.l1 = "Good luck with that. It was nice talking with you. 'Til next time.";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Hey Richard, heard any news lately?", "Has anything new happened on the island?", "Will you tell me the latest gossip?");
			link.l2.go = "rumours_LSC";
			link.l3 = "I want to ask you a few questions about the island.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
		// Кольцо
		case "ring":
			dialog.text = "Was I not before? Come on, everybody has bad days! Anyway, word is around the island that you're an excellent fighter. Tell me, is that true?";
			link.l1 = "I don't know what people have been saying, but I do know how to handle a sword.";
			link.l1.go = "ring_1";
			npchar.quest.ring = "true";
		break;
		
		case "ring_1":
			dialog.text = "Good. Listen, "+pchar.name+", remember me telling you about the outer ring, and about the valuable stuff you can find there?";
			link.l1 = "Richard, everyone's been telling me about it. Seems like scavenging that ring is the only pastime on this island - aside from political intrigue.";
			link.l1.go = "ring_2";
		break;
		
		case "ring_2":
			dialog.text = "Truer words were never spoken, ha-ha! I'll come to the point. (lowering his voice) I found an untouched ship on the outer ring. She's in good condition, which is rare.\nThe ship is large: a pinnace. She was driven here not long ago - two months or so. No one else has noticed her yet, so we have a chance to make some good money by looting her.";
			link.l1 = "You want me to go with you?";
			link.l1.go = "ring_3";
		break;
		
		case "ring_3":
			dialog.text = "Exactly! The pinnace's bow is stoved in, and those damned crabs managed to get inside and build a whole nest in the hold. Sneaking in without them noticing isn't an option and I have no idea how to climb onto the main deck from the waterline.\nI'm not a good fighter - haven't even touched a blade in years - so I'd never be able to kill those beasts on my own. That's why I came to you.";
			link.l1 = "So you propose I kill all crabs inside that ship for you...";
			link.l1.go = "ring_4";
		break;
		
		case "ring_4":
			dialog.text = "Yes. Here's my offer: I show you the way to the ship, you eliminate the crabs, and we split whatever loot we find there.";
			link.l1 = "No, friend, I'm not interested. It's not worth the effort to fight a horde of crabs inside a half-sunk ship for a doubtful reward. Find yourself a more reckless helper.";
			link.l1.go = "ring_exit";
			link.l2 = "Interesting... I have been thinking of exploring the outer ring for a long time. Deal! Show me the wreck and I'll kill the crabs.";
			link.l2.go = "ring_5";
		break;
		
		case "ring_exit":
			dialog.text = "Too bad... You're making a mistake; untouched wrecks are a rarity on the outer ring. Oh well, it's your choice. Goodbye...";
			link.l1 = "'Bye, Richard...";
			link.l1.go = "exit";
		break;
		
		case "ring_5":
			dialog.text = "I'm glad I was right about you, friend. I have a feeling we'll find a lot of interesting things inside her...";
			link.l1 = "We'll see. Do you know how many crabs are in there?";
			link.l1.go = "ring_6";
		break;
		
		case "ring_6":
			dialog.text = "I think about four of five... Well, that I saw.";
			link.l1 = "All right... when do we go?";
			link.l1.go = "ring_7";
		break;
		
		case "ring_7":
			dialog.text = "How about tomorrow? We need time to prepare. Get some antidotes from Brother Julian - crab jaws are poisonous. Better safe than sorry. Let's meet tomorrow at eight o'clock in the morning on the canted deck. Know where that is?";
			link.l1 = "No, where?";
			link.l1.go = "ring_8";
		break;
		
		case "ring_8":
			dialog.text = "There's an old wreck behind the San Augustine. Her bow is underwater and her rear is raised high; that's why she's called the 'canted deck.' You can only get aboard her by swimming.\nGet into the water on either side of the rop bridge, then swim around either the bow or stern of the San Augustine and climb onto the canted deck. We'll swim to our untouched wreck from there.";
			link.l1 = "Fine. See you tomorrow!";
			link.l1.go = "ring_9";
		break;
		
		case "ring_repeat":
			dialog.text = "Eight o'clock, the canted oblique deck.";
			link.l1 = "Yes, yes, I'll remember...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ring_repeat";
		break;
		
		case "ring_9":
			DialogExit();
			NextDiag.CurrentNode = "ring_repeat";
			pchar.quest.LSC_Ring_Start.win_condition.l1 = "Timer";
			pchar.quest.LSC_Ring_Start.win_condition.l1.date.hour  = 7.0;
			pchar.quest.LSC_Ring_Start.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.LSC_Ring_Start.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.LSC_Ring_Start.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.LSC_Ring_Start.function = "LSC_RingStart"; // готовы
			pchar.quest.LSC_Ring_Over.win_condition.l1 = "Timer";
			pchar.quest.LSC_Ring_Over.win_condition.l1.date.hour  = 10.0;
			pchar.quest.LSC_Ring_Over.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.LSC_Ring_Over.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.LSC_Ring_Over.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.LSC_Ring_Over.function = "LSC_RingOver"; // опоздание
			AddQuestRecord("LSC_Ring", "1");
		break;
		
		case "ring_10":
			dialog.text = "Ah, there you are, friend. Ready to make some crab salad?";
			link.l1 = "Sure!";
			link.l1.go = "ring_11";
		break;
		
		case "ring_11":
			dialog.text = "All right. Now, turn your head to the outer ring and look. See there two shipwrecks sticking up out of the water?";
			link.l1 = "Hm... Yes, I see them.";
			link.l1.go = "ring_12";
		break;
		
		case "ring_12":
			dialog.text = "Look between them to the outer ring. See the galleon with her bow pointed at us?";
			link.l1 = "...";
			link.l1.go = "ring_look";
		break;
		
		case "ring_look":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload_ring");
			DoQuestCheckDelay("LSC_RingTalkLook", 6.0);
		break;
		
		case "ring_13":
			dialog.text = "";
			link.l1 = "Yes, I... I think, I see it!";
			link.l1.go = "ring_13a";
		break;
		
		case "ring_13a":
			dialog.text = "She's our target; our pinnace is hiding behind her. Swim straight and don't turn. I will show you the way from there, and how to get back to the island when we're done.\nThe entrance to the cargo hold is the hole in the pinnace's bow. I won't enter her until you kill all the crabs.";
			link.l1 = "I remember our deal. You show me the way and I'll take care of the crabs. Shall we?";
			link.l1.go = "ring_14";
		break;
		
		case "ring_14":
			dialog.text = "We shall. I'll follow you.";
			link.l1 = "...";
			link.l1.go = "ring_swim";
		break;
		
		case "ring_swim":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetImmortal(npchar, true);
			pchar.quest.LSC_Ring_enter.win_condition.l1 = "locator";
			pchar.quest.LSC_Ring_enter.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_Ring_enter.win_condition.l1.locator_group = "reload";
			pchar.quest.LSC_Ring_enter.win_condition.l1.locator = "reload_ring";
			pchar.quest.LSC_Ring_enter.function = "LSC_RingEnter";
			LSC_RingSetItems(); // раскладка итемзов
			AddQuestRecord("LSC_Ring", "3");
		break;
		
		case "ring_15":
			dialog.text = "Heh, well done! Seems like you got all of them!";
			link.l1 = "I distinctly remember someone telling me there were only 'four or five'...";
			link.l1.go = "ring_16";
		break;
		
		case "ring_16":
			dialog.text = "Look, friend, I didn't do a roll call, I just peeked through the hole. I wouldn't intentionally lie!";
			link.l1 = "Whatever. Shall we search the cargo hold...?";
			link.l1.go = "ring_17";
		break;
		
		case "ring_17":
			dialog.text = "Of course! That's why we're here.";
			link.l1 = "All right, let's not waste any time...";
			link.l1.go = "ring_18";
		break;
		
		case "ring_18":
			DialogExit();
			NextDiag.CurrentNode = "ring_wait";
			LAi_SetWarriorType(npchar);
			LAi_warrior_DialogEnable(npchar, true);
			LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
			DoQuestCheckDelay("LSC_RingDialog", 60.0); // 1 минуту на пошариться
			npchar.quest.diagnode = "ring_19";
			AddQuestRecord("LSC_Ring", "4");
		break;
		
		case "ring_wait":
			dialog.text = "Wait a bit, friend, I haven't checked all places I wanted to yet. Look more carefully, perhaps you'll find more valuables.";
			link.l1 = "Fine...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ring_wait";
		break;
		
		case "ring_19":
			dialog.text = "Nothing special. It's a pity that there aren't any high-value goods here; just casks of corned beef and boxes of copra. I did find a case of expensive wine, though. What do you have?";
			link.l1 = "Not much: a few things of value but the rest is corned beef and copra, as you said.";
			link.l1.go = "ring_20";
		break;
		
		case "ring_20":
			dialog.text = "Not enough... Let's go upstairs and check the upper decks and cabins.";
			link.l1 = "Let's go.";
			link.l1.go = "ring_21";
		break;
		
		case "ring_21":
			DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("ExternalRingInside", "reload1", true);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.LSC_Ring_deck.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LSC_Ring_deck.win_condition.l1.location = pchar.location;
			pchar.quest.LSC_Ring_deck.win_condition = "LSC_RingEnterDeck";
			for (i=1; i<=3; i++)
			{
				sld = ItemsFromID("purse"+i);
				sld.shown = true;
				sld.startLocation = "ExternalRingDeck";
				sld.startLocator = "item"+i;
			}
		break;
		
		case "ring_22":
			dialog.text = "Damn it! Just look at that! Damn crab filth are everywhere! How'd they get up here?!";
			link.l1 = "Calm yourself! Stay here, don't move, and keep quiet. I'll deal with them...";
			link.l1.go = "ring_23";
		break;
		
		case "ring_23":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocator(npchar, "reload", "reload1", "", -1);
		break;
		
		case "ring_24":
			dialog.text = "Huh! So the tales of your skill with a blade were true! If I was here alone, I'd have jumped overboard by now.";
			link.l1 = "And how did you manage to be a smuggler in past, huh, if you lose your nerve this easily?";
			link.l1.go = "ring_25";
		break;
		
		case "ring_25":
			dialog.text = "First of all, I was younger, stronger, and more reckless. Second, I'm no soldier - we smugglers always try to avoid bloodshed. Third, my skills lay in handling sails and tillers, not blades and pistols. And fourth, years of living here have made me soft!\nSo don't be angry with me. Let's check the upper deck. It looks like the ship was in a serious fight. Look at this damage...";
			link.l1 = "You're right. The ship definitely took heavy fire. Let's keep looking.";
			link.l1.go = "ring_26";
		break;
		
		case "ring_26":
			dialog.text = "And we need to find entrances to the officers' cabins.";
			link.l1 = "Then let's not waste time. Call me if you see a crab!";
			link.l1.go = "ring_27";
		break;
		
		case "ring_27":
			DialogExit();
			NextDiag.CurrentNode = "ring_wait";
			LAi_SetWarriorType(npchar);
			LAi_warrior_DialogEnable(npchar, true);
			LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
			DoQuestCheckDelay("LSC_RingDialog", 80.0); // 1.3 минуты на пошариться
			npchar.quest.diagnode = "ring_28";
			AddQuestRecord("LSC_Ring", "5");
		break;
		
		case "ring_28":
			dialog.text = "Nothing, again! A few bits of jewellery and that's all. But that's alright, there usually aren't any valuable goodies on the decks. The very best must be in the cabins. There's an entrance to the captain's quarters over there. Let's check it out.";
			link.l1 = "Be careful, who knows what's waiting for us inside. Perhaps I'd better enter first?";
			link.l1.go = "ring_29";
		break;
		
		case "ring_29":
			dialog.text = "Let's go, "+pchar.name+". I won't hide behind your back any more.";
			link.l1 = "Go on then...";
			link.l1.go = "ring_30";
		break;
		
		case "ring_30":
			DialogExit();
			chrDisableReloadToLocation = true;
			LocatorReloadEnterDisable("ExternalRingDeck", "reload2", false);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "ExternalRingCabin1", "reload", "reload1", "OpenTheDoors", -1);
			pchar.quest.LSC_Ring_cabin.win_condition.l1 = "location";
			pchar.quest.LSC_Ring_cabin.win_condition.l1.location = "ExternalRingCabin1";
			pchar.quest.LSC_Ring_cabin.win_condition = "LSC_RingEnterCabin";
			sld = ItemsFromID("RingCapBook"); // кладем журнал 'Санта-Люсии'
			sld.shown = true;
			sld.startLocation = "ExternalRingCabin1";
			sld.startLocator = "item1";
		break;
		
		case "ring_31":
			dialog.text = "It looks like we got lucky: neither crabs nor other filth in here. But fuck, I'm starting to get angry; I only found a couple dozen doubloons and a few sundries!";
			link.l1 = "Calm down. Remember: valuables are always stored in the captain's cabin. Let's see what we've got!";
			link.l1.go = "ring_32";
		break;
		
		case "ring_32":
			DialogExit();
			NextDiag.CurrentNode = "ring_wait";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto2", "LSC_RingSetToBarman", -1);
			DoQuestCheckDelay("LSC_RingDialog", 30.0); // 30 сек на пошариться
			npchar.quest.diagnode = "ring_33";
		break;
		
		case "ring_33":
			dialog.text = "Ha-ha! Just as I thought! I know the habits of merchants; they like to create secret stashes around the ship and hide their treasures there! The captain of this pinnace was a cunning rogue, but I won't be so easily cheated! Look what I found!";
			link.l1 = "Show me!";
			link.l1.go = "ring_34";
		break;
		
		case "ring_34":
			dialog.text = "Forty thousand pesos, two chests filled with doubloons, a packet of emerald and a bunch of jewels! The owner was quite rich. At least it'll repay our effort, though I was counting on finding more stuff. Lets split the loot.";
			link.l1 = "Excellent, Richard. At least we won't come away empty-handed!";
			link.l1.go = "ring_35";
		break;
		
		case "ring_35":
			TakeNItems(pchar, "jewelry4", 25);
			TakeNItems(pchar, "chest", 1);
			TakeNItems(pchar, "icollection", 1);
			AddMoneyToCharacter(pchar, 20000);
			Log_Info("You have received a chest with doubloons");
			Log_Info("You have received 25 emeralds");
			Log_Info("You have received  a collection of jewels");
			PlaySound("interface\important_item.wav");
			dialog.text = "Well, let's keep what each of us have found on the decks for ourselves. Are you all right with that? Have you found anything good in the chests and cabinets?";
			link.l1 = "A few Indian artifacts, amulets, papers and so on.";
			link.l1.go = "ring_36";
		break;
		
		case "ring_36":
			dialog.text = "Keep them for yourself. You did the riskiest job after all.";
			if (CheckAttribute(pchar, "questTemp.LSC.Ring.ReadCapBook")) // прочел журнал
			{
				link.l1 = "Fine. And here's something a treasure hunter like yourself might think useful: I found the captain's log lying on that desk. The story it tells is very sad, but it might help our search. There's a box hidden somewhere in the cargo hold filled with gold! Here, read!";
				link.l1.go = "ring_41";
			}
			else
			{
				if (CheckCharacterItem(pchar, "RingCapBook")) // взял журнал
				{
					link.l1 = "Fine. But I have found one more thing: the captain's log.";
					link.l1.go = "ring_38";
				}
				else
				{
					link.l1 = "I won't dispute that, ha-ha! So, time to return?";
					link.l1.go = "ring_37";
				}
			}
		break;
		
		case "ring_37":
			dialog.text = "Yes. Don't tell anyone about the ship; it'll be our secret. Sure, we don't need copra, but all that food will be useful; we won't have to buy from the Admiral anymore.";
			link.l1 = "Fine, I agree. I hope others don't find this ship anytime soon. Let's go!";
			link.l1.go = "ring_cabin_exit";
		break;
		
		case "ring_38":
			dialog.text = "Did you read it?";
			link.l1 = "Not yet...";
			link.l1.go = "ring_39";
		break;
		
		case "ring_39":
			dialog.text = "So let's read it! We might learn something important from it. And it'll be interesting to know how the ship ended up here. Read it!";
			link.l1 = "Hm. Fine, I'll read it now...";
			link.l1.go = "ring_40";
		break;
		
		case "ring_40":
			DialogExit();
			NextDiag.CurrentNode = "book_wait";
			LAi_SetWarriorType(npchar);
			LAi_warrior_DialogEnable(npchar, true);
			LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
		break;
		
		case "book_wait":
			dialog.text = "Did you read it? What's in there?";
			if (CheckAttribute(pchar, "questTemp.LSC.Ring.ReadCapBook")) // прочел журнал
			{
				link.l1 = "I did. Listen, the story is very sad, but it reveals there's a hidden box filled with gold in the cargo hold! Read it, maybe you can figure out where it is.";
				link.l1.go = "ring_41";
			}
			else
			{
				link.l1 = "Wait a second. I'll read it and tell you...";
				link.l1.go = "exit";
				NextDiag.TempNode = "book_wait";
			}
		break;
		
		case "ring_41":
			dialog.text = "Really? "+pchar.name+", I am... well, I don't read that good. Tell me what's written there, huh?";
			link.l1 = "In brief: this pinnace was crossing the Caribbean Sea from south to north, following the coast of New Spain. Along the way, the captain fell in love with and married an Indian princess of a Lower Orinoco tribe. She told him her people conducted sacrifices...";
			link.l1.go = "ring_42";
		break;
		
		case "ring_42":
			dialog.text = "";
			link.l1 = "Their sacrifices were gold nuggets! So of course, our captain stole the gold with the help of his first mate and quartermaster. They put it in a box in the cargo hold and covered it with copra...";
			link.l1.go = "ring_43";
		break;
		
		case "ring_43":
			dialog.text = "";
			link.l1 = "But it seems that the robbery of that sacred Indian place was punished: the ship was becalmed, her water ran low, fever broke out, and pirates attacked. The sailors blamed the Indian girl - the captain's wife - and demanded he throw her overboard. Of course the captain refused and a mutiny ensued...";
			link.l1.go = "ring_44";
		break;
		
		case "ring_44":
			dialog.text = "";
			link.l1 = "The captain lost the fight. According to his final entries, he barricaded himself and his Indian wife in his cabin and shot anyone who tried to break through the door. He mentions a storm was bearing down on them - that's likely what brought the ship to Justice Island. In the end, his wife was shot, and I've no doubt the mutineers eventually killed him, too.";
			link.l1.go = "ring_45";
		break;
		
		case "ring_45":
			dialog.text = "Hmm, yes, yes, a sad story... but the gold... is there really a box of gold nuggets in the cargo hold? Which one?! Let's find it! I'll turn the entire orlop over if I have to!";
			link.l1 = "All right, all right, yes, we'll look for it - slow down, Richard!";
			link.l1.go = "ring_seek_gold";
		break;
		
		case "ring_cabin_exit":
			DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("ExternalRingInside", "reload1", false); // открываем выход
			LocatorReloadEnterDisable("LostShipsCity_town", "reload_ring", false); // открываем вход // patch-2
			DoQuestReloadToLocation("ExternalRingDeck", "reload", "reload2", "LSC_RingFinalStage");
			sld = ItemsFromID("RingCapBook");
			sld.shown = false; // убираем журнал
			AddQuestRecord("LSC_Ring", "6");
		break;
		
		case "ring_seek_gold":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			// ставим прерывание на локатор
			pchar.quest.LSC_Ring_gold.win_condition.l1 = "locator";
			pchar.quest.LSC_Ring_gold.win_condition.l1.location = "ExternalRingInside";
			pchar.quest.LSC_Ring_gold.win_condition.l1.locator_group = "quest";
			pchar.quest.LSC_Ring_gold.win_condition.l1.locator = "gold";
			pchar.quest.LSC_Ring_gold.win_condition = "LSC_RingFindGold";
			// подменяем состав бокса
			pchar.GenQuestBox.ExternalRingInside = true;
			pchar.GenQuestBox.ExternalRingInside.box1.items.jewelry5 = 2522;
			AddQuestRecord("LSC_Ring", "7");
		break;
		
		case "ring_46":
			dialog.text = "Ha-ha! We found it! Just look at all that glitter! A whole box! There can't be less than five thousand nuggets in here! I've never seen so much gold!!";
			link.l1 = "Congratulations, partner. Seems all our efforts paid off! What should we do with all that gold?";
			link.l1.go = "ring_47";
		break;
		
		case "ring_47":
			dialog.text = "What do you mean? We we'll split it in half!";
			link.l1 = "I mean where will you keep it? Will you leave it here?";
			link.l1.go = "ring_48";
		break;
		
		case "ring_48":
			dialog.text = "Ha! No, I'll hide the gold in my own private stashes where no one will ever find them. Hiding is the one thing I know well how to do! Let's put half the gold into this barrel - that'll be my share. I'll take it away before sunset.\nYou do whatever you want with you share, but you'd do well to move it into your own stashes, too. Don't blame me if you find your gold missing; I'm an honest man, in my way, and I won't touch your cut. But very soon, others may find this ship, and they won't hesitate to grab whatever they find.";
			link.l1 = "Thanks. I'll figure what to do with my gold. Meanwhile, let's put your share in that barrel...";
			link.l1.go = "ring_49";
		break;
		
		case "ring_49":
			DialogExit();
			SetLaunchFrameFormParam("Two hours later..."+ NewStr() +"The gold was shared!", "", 0, 5);//табличка
			WaitDate("", 0, 0, 0, 2, 10);
			LaunchFrameForm();
			RecalculateJumpTable();
			sld = characterFromId("LSC_Rishard");
			sld.quest.diagnode = "ring_50";
			DoQuestCheckDelay("LSC_RingDialog", 5.0);
		break;
		
		case "ring_50":
			dialog.text = "Done... Thank you, "+pchar.name+", for coming with me. I couldn't have done this without you. Now, I should consider building a tartane... sail away from here...\nAh, I'll worry about that later. For now, it'll be a full-time job moving this gold into my stashes. Farewell, friend, I hope you use your cut wisely!";
			link.l1 = "'Bye, Richard. It's been a glorious day. Be well!";
			link.l1.go = "ring_51";
		break;
		
		case "ring_51":
			DialogExit();
			LocatorReloadEnterDisable("ExternalRingInside", "reload1", false); // открываем выход
			LocatorReloadEnterDisable("LostShipsCity_town", "reload_ring", false); // открываем вход
			DoQuestCheckDelay("LSC_RingFinalStage", 0.5);
			DeleteAttribute(pchar, "questTemp.LSC.Ring.ReadCapBook");
			AddQuestRecord("LSC_Ring", "8");
		break;
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Questions? Oh, fine, if you must...";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "How did you get here?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Do you want to leave the island?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Have you ever considered joining one of the clans? The Narwhals, for example?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Is it true that you can find a lot of interesting stuff on the outer ring?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "No questions. Pardon...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "For ten years me and my comrades sailed back and forth to this island from Cuba on a tartane to trade with the locals. We kept the location of the island a secret, and exchanged fresh meat, fruits, and vegetables for goods and gold from the holds of the wrecks. Good times!\nProvisioning has always been a problem for the Justice Islanders, so they paid us well for juicy meat with spices, which costs a fortune back in Europe! Every single voyage, I made enough money to buy every whore in Tortuga.\nBut everything has an end. The storms in this region grew stronger and more frequent, so sailing to the island became much more dangerous. Some of my crew left the business, but me and a dozen brave lads stayed the course.\nFinally, a storm threw us on a reef two miles from the island. I still don't get how I managed to swim through the churning sea. Now I'm one of those I traded with in the past.";
			link.l1 = "Interesting story...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Ha! I'll get out of here someday, damn it, but not as a pauper! What would I do on Cuba? I have no friends left and my pockets are empty.\nAll I need is to find one ship on the outer ring with a hold full of precious cargo, or a pile of doubloons. Then I'll build a new tartane, sail through the storms, and go back to civilization.";
			link.l1 = "I see...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
			SaveCurrentNpcQuestDateParam(npchar, "quest_date");
		break;
		
		case "ansewer_3":
			dialog.text = "Why should I? To stand guard roasting in the sun every third day, keeping people off the San Gabriel? Besides, they don't like to hire non-islanders - they're natives, after all... The Negros are the same. So no, I'd rather be on my own.";
			link.l1 = "I see...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Sure! That's how the locals survive. Do you know when they like to throw parties? When a new ship founders on the ring.\nThere are still a lot of untouched wrecks filled with gold and goods out there, but exploring the outer ring is dangerous. The place is a mess, and you don't want to go venturing alone. If you get snarled on some rigging, or slip and fall, you're done. A lot of people have died that way.";
			link.l1 = "Hm... I'll be careful then.";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Hey, take your hands off my stash, thief!", "Can't trust anyone on this island! En garde, thief!", "Leave my sea chest alone, you bastard!");
			link.l1 = "Fuck off!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Robbing an innocent woman?! You won't get away with this!";
			link.l1 = "Foolish girl!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Put your weapon away. You're making me nervous.", "Unless you plan to use that blade, you should put it away.", "Put that weapon away, you're scaring people - me included!");
			link.l1 = LinkRandPhrase("Fine.", "All right.", "Sorry...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "Unless you plan to use that blade, you should put it away.", "Put your weapon away. You're making me nervous.");
				link.l1 = LinkRandPhrase("Fine.", "All right.", "As you say...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "Put your weapon away. You're making me nervous.", "Put that weapon away, you're scaring people - me included!");
				link.l1 = RandPhraseSimple("Got it.", "I am taking it away.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

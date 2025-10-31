// Addon-2016 Jason, французские миниквесты (ФМК) Тортуга
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
		
		case "girl":
			DelMapQuestMarkCity("Tortuga");
			LAi_SetImmortal(npchar, false);
			DelLandQuestMark(npchar);
			LAi_RemoveLoginTime(npchar);
			FMQT_FillChest();
			PlaySound("Voice\English\Girls_1.wav");
			dialog.text = "Oh, hello monsieur! Welcome to Tortuga! Such noble captains as yourself are rare guests here...";
			link.l1 = "Greetings, mademoiselle. Thank you for the warm welcome. But how so? I thought that such an important port was always a place of interest for gentlemen of fortune far more noble than myself.";
			link.l1.go = "girl_1";
		break;
		
		case "girl_1":
			dialog.text = "Ah, monsieur... You are clearly a newcomer, am I right? You'll see for yourself. You have no idea how hard it is to find worthy men for a dance at the governor's palace. Perhaps you might accompany me...?";
			link.l1 = "How can I be of service to such a beautiful woman?";
			link.l1.go = "girl_2";
		break;
		
		case "girl_2":
			dialog.text = "My oh my, such gallantry! (giggle) Perhaps you could pay us a visit at six o'clock tonight? Our governor's wife regularly hosts informal parties in the palace servants' quarters. It is a rare chance for us to have intriguing company at such events. Will you pay us a visit? Please come, we'd be ever so delighted.";
			link.l1 = "I'd be honoured, mademoiselle. I will pay you a visit tonight.";
			link.l1.go = "girl_3";
			link.l2 = "Forgive me, mademoiselle, but I have urgent business to attend to. Another time, perhaps?";
			link.l2.go = "girl_exit";
		break;
		
		case "girl_exit":
			dialog.text = "Pity. I'll have to find someone else to keep me and my girlfriends... company. Farewell.";
			link.l1 = "Farewell.";
			link.l1.go = "girl_exit_1";
		break;
		
		case "girl_exit_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 40.0);
			npchar.lifeday = 0;
			FMQT_ClearChest();
		break;
		
		case "girl_3":
			dialog.text = "Thank you! I promise you, this will be a night you'll never forget, monsieur! Au revoir!";
			link.l1 = "See you...";
			link.l1.go = "girl_4";
		break;
		
		case "girl_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 40.0);
			npchar.lifeday = 0;
			pchar.questTemp.FMQT = "begin_serveroom";
			FMQT_Begin();
			AddQuestRecord("FMQ_Tortuga", "1");
		break;
		
		case "girl_5":
			DelMapQuestMarkCity("Tortuga");
			LAi_SetImmortal(npchar, false);
			DelLandQuestMark(npchar);
			LAi_RemoveLoginTime(npchar);
			FMQT_FillChest();
			PlaySound("Voice\English\Girls_1.wav");
			dialog.text = "Hey there, sailor! Which lucky wind blew you here today? We rarely see such fine men in Tortuga.";
			link.l1 = "Hello to you too, mademoiselle, you are apt to make me blush with your compliments. I am a captain of my own ship and a busy man, but I'm sure that this island can offer enough for a wild rover such as me to stay entertained.";
			link.l1.go = "girl_6";
		break;
		
		case "girl_6":
			dialog.text = "(giggle) Oh yes sir, I'm sure we can help with that! Tortuga always has something to offer. As do I... Why, I'm liable to do almost *anything* after I hear a good sea story. I do love them so! One captain once told me a tall tale about how he managed to escape being marooned on a desert island by making a raft out of sea turtles. What a gallant! Could you?";
			link.l1 = "Could I what?";
			link.l1.go = "girl_7";
		break;
		
		case "girl_7":
			dialog.text = "(giggle) Could you make a raft out of sea turtles?";
			link.l1 = "I'll do you one better. Once, as a runaway apprentice, I captured the fastest ship in the English Navy using only a hatchet. I can also hold my breath for ten minutes. Want to see?";
			link.l1.go = "girl_8";
		break;
		
		case "girl_8":
			dialog.text = "Maybe later. I work as a servant in our governor's palace. Come there by six o'clock tonight and find me and my friend in the bower. You can tell us all about your adventures then...";
			link.l1 = "Sounds like a show-and-tell invitation that I can't refuse. See you at six tonight.";
			link.l1.go = "girl_9";
			link.l2 = "Sneaking into the governor's palace? Sounds a bit rich for my blood. I'll pass, dear. Find me in the tavern if you want the company of a real man. Yo ho ho!";
			link.l2.go = "girl_exit_2";
		break;
		
		case "girl_exit_2":
			dialog.text = "Ph-f. Whatever, I'll find a better and bigger man than you then. Your codpiece looks too small after all. Good riddance.";
			link.l1 = "Even a battleship would look small sailing through your Windward Passage.";
			link.l1.go = "girl_exit_1";
		break;
		
		case "girl_9":
			dialog.text = "Looking forward to it!";
			link.l1 = "...";
			link.l1.go = "girl_10";
		break;
		
		case "girl_10":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 40.0);
			npchar.lifeday = 0;
			pchar.questTemp.FMQT = "begin_bedroom";
			FMQT_Begin();
			AddQuestRecord("FMQ_Tortuga", "2");
		break;
		
		case "wife":
			DelLandQuestMark(npchar);
			PlaySound("Voice\English\LE\Marselina\Marselina_Levasser_01.wav");
			dialog.text = "Ah, there you are! Captain "+GetFullName(pchar)+"! I am so glad to meet you, it's been a while since I've been graced by a caller of such nobility and stature!";
			link.l1 = "It is a great honour and pleasure for me to be here in your company, madame. But what about the rest of the guests? Am I too early?";
			link.l1.go = "wife_1";
		break;
		
		case "wife_1":
			dialog.text = "Oh, they're indisposed and cannot come. But never mind them, let's drink wine and talk... Ah, if only you knew how bored and lonely I feel here! Tortuga is a sordid den filled with scum, villains, and pirates! Pirates! And at last, a worthy gentleman in my house! I wish my husband did more business with men of your class and talents! But no, nothing but pirates, pirates everywhere! Have you heard about that new fashion becoming popular in Paris at His Majesty's Royal Court? What is your opinion of it?";
			link.l1 = "I am sorry, my opinion about what exactly? Pirates? Or fashion?";
			link.l1.go = "wife_2";
		break;
		
		case "wife_2":
			dialog.text = "Oh sir, you understand me so well! I can't even believe this. My husband gives me pennies while he makes MILLIONS off his pirates, imagine that! Pirates! I have to order dresses delivered here to this filthy hole, but by the time they arrive they're already six months out of date! How can a woman of my status wear such rags? Oh, I so want to see and wear the fashions of Paris! Do you think I'd look lovely in those?";
			link.l1 = "Madame, you look quite lovely. You don't need fashions from Paris for that, it's already obvious to every man on this beautiful island.";
			link.l1.go = "wife_3";
		break;
		
		case "wife_3":
			dialog.text = "You are too kind to me... Captain, I must confess, I am in great trouble. But you will help a poor woman, won't you?";
			link.l1 = "Certainly, madame. Anything you wish.";
			link.l1.go = "wife_4";
		break;
		
		case "wife_4":
			dialog.text = "Careful there, monsieur captain, or I shall lose my head! (coquettish giggle) My husband hasn't given me a single centime lately. That brute brings common harlots back to our home and pays me no mind at all!\nI know where he keeps some of his ill-gotten treasure, it's in a chest in his office. This is my money by the right of a wife and a woman. Help me get what he owes me and you'll be rewarded... With gold and... other delightful things.";
			link.l1 = "That is an intriguing offer. Very well, madam, I will help you. Where is this chest and how do I open it?";
			link.l1.go = "wife_5";
			link.l2 = "Very well, madame, I will get you the chest's contents. We will get the money and have a very pleasant 'conversation' together afterwards. What man could decline such an offer? Where is this chest and how do I open it?";
			link.l2.go = "wife_6";
			link.l3 = "Madame, you are trying to seduce me. I am sorry, but my honour demands that I decline your offer. You have my sympathies, you deserve better, but you'll have to find yourself another actor for your play.";
			link.l3.go = "wife_exit";
		break;
		
		case "wife_exit":
			dialog.text = "Pity. We have nothing more to talk about then, monsieur. Leave, and remember: if you breathe a word about this to my husband, you'll regret it!";
			link.l1 = "Farewell.";
			link.l1.go = "wife_exit_1";
		break;
		
		case "wife_exit_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "questTemp.FMQT.Common");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			pchar.questTemp.FMQT = "huber";
			pchar.quest.FMQT_late1.win_condition.l1 = "Timer";
			pchar.quest.FMQT_late1.win_condition.l1.date.hour  = 18.0;
			pchar.quest.FMQT_late1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQT_late1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQT_late1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQT_late1.function = "FMQT_HuberTime";
			AddQuestRecord("FMQ_Tortuga", "4");
		break;
		
		case "wife_5":
			pchar.questTemp.FMQT.Honour = "true"; // вар 1
			dialog.text = "I didn't expect this from you... The chest... Leave it for later, first we must find the duplicate key that was stolen by a filthy pirate. He's off carousing right now in a local den, drinking like a pig. Make haste and bring the duplicate key back to me. I will be waiting for you.";
			link.l1 = "No time to waste then!";
			link.l1.go = "wife_7";
		break;
		
		case "wife_6":
			pchar.questTemp.FMQT.Bed = "true"; // вар 2 
			dialog.text = "You won't regret this, captain. First, we must find a duplicate key that was stolen by a filthy pirate. He is off carousing right now in a local den, drinking like a pig. Make haste and bring the duplicate key back to me. I will be waiting for you.";
			link.l1 = "No time to waste then!";
			link.l1.go = "wife_7";
		break;
		
		case "wife_7":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "FMQT_PirateInTavern", 10.0);
			pchar.quest.FMQT_late2.win_condition.l1 = "Timer";
			pchar.quest.FMQT_late2.win_condition.l1.date.hour  = 0.0;
			pchar.quest.FMQT_late2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQT_late2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQT_late2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQT_late2.function = "FMQT_TavernTime";
			AddQuestRecord("FMQ_Tortuga", "6");
		break;
		
		case "wife_8":
			DelLandQuestMark(npchar);
			PlaySound("Voice\English\LE\Marselina\Marselina_Levasser_01.wav");
			dialog.text = "Captain "+GetFullName(pchar)+"! My, my! What a man in my private chambers! Are you surprised? You are the only guest here tonight. (giggle)";
			link.l1 = "I am surprised, madam. But I don't mind at all. Is this about business or pleasure?";
			link.l1.go = "wife_9";
		break;
		
		case "wife_9":
			dialog.text = "What a direct approach! I like men like you. I have a business proposal for you, captain. I will find a way to compensate your efforts if you succeed.";
			link.l1 = "Go on.";
			link.l1.go = "wife_10";
		break;
		
		case "wife_10":
			dialog.text = "Ah... My husband has a chest full of money and jewellery. I hate him, and I want a larger allowance for my troubles.";
			link.l1 = "Madame, you look lovely. You don't need more jewels or fashions from Paris for this, it's already obvious to every man on Hispaniola.";
			link.l1.go = "wife_11";
		break;
		
		case "wife_11":
			dialog.text = "You are too kind to me... Captain, I must confess, I am in great trouble. Will you help a woman in distress?";
			link.l1 = "Of course, madame. Honour demands it. Anything you wish.";
			link.l1.go = "wife_12";
		break;
		
		case "wife_12":
			dialog.text = "Careful there, monsieur captain, or I shall lose my head! (coquettish giggle) My husband hasn't given me a single centime lately. That brute brings common harlots back to our home and pays me no mind at all!\nI know where he keeps some of his ill-gotten treasure, it's in a chest in his office. This is my money by the right of a wife and a woman. Help me get what he owes me and you'll be rewarded... With gold and... other delightful things.";
			link.l1 = "Fine. I will do it. Where is this chest, and how do I open it?";
			link.l1.go = "wife_13";
			link.l2 = "Ha! No questions there, I can do that for a woman like you. You won't regret it, my dear. We'll get the money and have a very pleasant time together. Where is this chest, and how do I open it?";
			link.l2.go = "wife_14";
			link.l3 = "Not I, madam. I'm no gentleman to both cuckold and rob a man in one night. Not in this manner, anyway. Find yourself another performer for this play.";
			link.l3.go = "wife_exit_2";
		break;
		
		case "wife_13":
			pchar.questTemp.FMQT.Honour = "true"; // вар 1
			dialog.text = "Oh... I like you more and more... First, we must recover a duplicate key that was stolen by a filthy pirate. He's off carousing in a local den, drinking like a pig. Make haste and bring the duplicate to me. I will be waiting.";
			link.l1 = "No time to waste then!";
			link.l1.go = "wife_7";
		break;
		
		case "wife_14":
			pchar.questTemp.FMQT.Bed = "true"; // вар 2 
			dialog.text = "Keep your cool, monsieur, there will be plenty of time for that later. (giggle) First, we must recover a duplicate key that was stolen by a filthy pirate. He is off carousing in a local den, drinking like a pig. Make haste and bring the duplicate to me. I will be waiting for you. Are you sure you can manage that?";
			link.l1 = "Don't doubt me, I am already on my way.";
			link.l1.go = "wife_7";
		break;
		
		case "wife_exit_2":
			dialog.text = "Prudish bastard! Get out of my sight! And don't even think about telling my husband about this or you'll regret it!";
			link.l1 = "Bye, sweetheart.";
			link.l1.go = "wife_exit_1";
		break;
		
		case "wife_15":
			DelLandQuestMark(npchar);
			pchar.quest.FMQT_late3.over = "yes";
			dialog.text = "Captain! Did you get the key?";
			link.l1 = "Yes, I have it. Where is the chest?";
			link.l1.go = "wife_16";
		break;
		
		case "wife_16":
			dialog.text = "Oh! Is my vile husband actually going to get what he deserves? You are an incredible man, captain! You have a great future ahead of you, do you know that? Forget the chest. I'll do it myself. Come see me tomorrow to get your reward. You won't regret it, captain...";
			link.l1 = "Fine. Have it your way. Looking forward to seeing you tomorrow.";
			link.l1.go = "wife_17";
			link.l2 = "No, I am a busy man and I don't want to waste time waiting. Why wait? Tell me what has to be done and I will do it. I can't let such a beautiful woman spoil her pretty little hands messing about with a lock and key.";
			link.l2.go = "wife_18";
		break;
		
		case "wife_17":
			RemoveItems(pchar, "kaleuche_key", 1);
			ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key");
			dialog.text = "Come see me by six o'clock, my brave sir knight...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQT_Deceive");
		break;
		
		case "wife_18":
			dialog.text = "Are you sure? It might be dangerous for you. Why do you want to put your life at risk, captain?";
			link.l1 = "Fine. Have it your way. Looking forward to seeing you tomorrow.";
			link.l1.go = "wife_17";
			link.l2 = "I've already made my decision. What exactly should I do?";
			link.l2.go = "wife_19";
		break;
		
		case "wife_19":
			dialog.text = "A lionheart!... Go to my husband's office, you'll find the chest there. Use the duplicate key. No one is up there at this time of night, so take your time. There are... diamonds inside that chest. A great number of them. Take them all and return to me. I will be waiting. Don't betray my trust... please.";
			link.l1 = "I'll be back soon.";
			link.l1.go = "wife_20";
		break;
		
		case "wife_20":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("FMQ_Tortuga", "11");
			sld = &Locations[FindLocation("Tortuga_townhallRoom")];
			sld.private2.key = "kaleuche_key"; // допуск к сундуку
			pchar.questTemp.FMQT = "chest";
		break;
		
		case "wife_21":
			DelLandQuestMark(npchar);
			pchar.quest.FMQT_GemsTimeOver.over = "yes";
			PlaySound("Voice\English\LE\Marselina\Marselina_Levasser_02.wav");
			dialog.text = "Oh, captain! I... You... Is it done? Oh, and who is this?! A-ah!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQT_MercenAttackRoom");
		break;
		
		case "wife_22":
			dialog.text = "Oh my! Captain, you've saved me! You... you are my hero! It was my husband's thug, he wanted to kill you! I begged him not to! Are you hurt? Did you bring the diamonds?";
			link.l1 = "Ha. Really? Your husband is a jealous man... Whatever. To hell with him, I've got the guts.";
			link.l1.go = "wife_23";
		break;
		
		case "wife_21x":
			DelLandQuestMark(npchar);
			pchar.quest.FMQT_GemsTimeOver.over = "yes";
			PlaySound("Voice\English\LE\Marselina\Marselina_Levasser_02.wav");
			dialog.text = "Oh captain! I... You... Is it done?";
			link.l1 = "There was a minor complication, but it's settled now. Why are you pale, madame? Are you all right? I have the jewels, that should cheer you up, am I right?";
			link.l1.go = "wife_23";
		break;
		
		case "wife_23":
			dialog.text = "Thank God! I am avenged! My knight! How many diamonds were there?";
			if (GetCharacterItem(pchar, "jewelry2") >= 100)
			{
				link.l1 = "Your knight has returned from his adventure with a sack full of loot. He will leave half of it to his lady so she can buy the very best fashions from Paris. I have kept my promise to you.";
				if (CheckAttribute(pchar, "questTemp.FMQT.Honour")) link.l1.go = "wife_25";
				else link.l1.go = "wife_26";
			}
			else
			{
				link.l1 = "Oh, there were plenty of diamonds, but you'll get nothing. You hired an assassin to kill me, you putain! Do you really believe I would share with you after all this? Open your mouth about it and your husband will learn of your plan to rob and cuckold him. So keep it shut.";
				link.l1.go = "wife_24";
			}
		break;
		
		case "wife_24":
			PlaySound("Voice\English\LE\Marselina\Marselina_Levasser_03.wav");
			dialog.text = "Scoundrel! Bastard! You won't get away with this!";
			link.l1 = "Aye, I've heard that one before.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQT_FinalNoJewelry");
		break;
		
		case "wife_25":
			RemoveItems(pchar, "jewelry2", 100);
			Log_Info("You have given diamonds");
			PlaySound("interface\important_item.wav");
			dialog.text = "You are not like... the rest of them. You get what you want. You have a bright future ahead of you. I know you are a busy man, but... will you stay with me for a while? No one will disturb us, I promise.";
			link.l1 = "I always have time for a beautiful woman like yourself. Shall I open a bottle of your husband's wine?";
			link.l1.go = "wife_sex";
		break;
		
		case "wife_sex":
			DialogExit();
			LAi_SetActorType(npchar);
			pchar.questTemp.HorseQty = sti(pchar.questTemp.HorseQty) + 1;
			DoQuestCheckDelay("PlaySex_1", 1.0);
			
			// Rebbebion, для "Путеводной звезды"
			pchar.questTemp.FMQT.GiveDiamonds = true;
			pchar.questTemp.FMQT.Marceline = "Fuck"; 
		break;
		
		case "wife_26":
			RemoveItems(pchar, "jewelry2", 100);
			Log_Info("You have given diamonds");
			PlaySound("interface\important_item.wav");
			dialog.text = "I think I can live without them. There are plenty of ways to spend money here. So many handsome and worthy men on Tortuga... Thank you for everything, captain. Just so you know, please keep quiet about this affair or my husband will see you hanged from a gibbet. He is not a good man. Farewell.";
			link.l1 = "Just like that? That was an instructive experience. Farewell, madam, I suggest you keep quiet about this too, I am not a good man either. But you already know that, right?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQT_FinalNoSex");
			
			// Rebbebion, для "Путеводной звезды"
			pchar.questTemp.FMQT.GiveDiamonds = true;
			pchar.questTemp.FMQT.Marceline = "NoFuck"; 
		break;
		
		case "wife_27":
			PlaySound("Voice\English\Girls_2.wav");
			dialog.text = "Who are you and what are you doing here?";
			link.l1 = "What are you playing at? We had a deal...";
			link.l1.go = "wife_28";
		break;
		
		case "wife_28":
			dialog.text = "What deal, monsieur? I am a married woman, I don't do business with other men! Leave my chambers now or I shall call my husband and his guards!";
			link.l1 = "Just like that, huh? Very well, I believe I'll enlighten your good husband in that case!";
			link.l1.go = "wife_29";
		break;
		
		case "wife_29":
			dialog.text = "Leave now, you insolent fellow, or my men will throw you into the oubliette of Fort La Roche! I don't care about your threats! Get out!";
			link.l1 = "...";
			link.l1.go = "wife_30";
		break;
		
		case "wife_30":
			DialogExit();
			DoQuestReloadToLocation("Tortuga_town", "reload", "reload3", "FMQT_FinalFail");
			pchar.questTemp.FMQT.Marceline = "Deception"; // Rebbebion, для "Путеводной звезды"
		break;
		
		case "pirate":
			DelLandQuestMark(npchar);
			PlaySound("Voice\English\tavern\Pyanici-03.wav");
			pchar.quest.FMQT_late2.over = "yes";
			FreeSitLocator("Tortuga_tavern", "sit_base2");
			dialog.text = "Who are you? Ah, whatever. Don't trust women, pal. It's like the Bible says... even the dullest of strumpets can drag you to the depths of Hell with their manipulations. Take a seat, mate, have a drink!";
			link.l1 = "With pleasure!";
			link.l1.go = "pirate_1x";
		break;
		
		case "pirate_1x":
			DialogExit();
			LAi_Fade("", "");
			ChangeCharacterAddressGroup(pchar, "Tortuga_tavern", "sit", "sit_base2");
			LAi_SetSitType(pchar);
			npchar.Dialog.currentnode = "pirate_1";
			LAi_SetActorType(npchar);
			LAi_ActorSetSitMode(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 2.0);
		break;
		
		case "pirate_1":
			PlaySound("Voice\English\tavern\Pyanici-05.wav");
			dialog.text = "What are you staring at? Pour it up!!";
			link.l1 = "Here's to you!.. Hey friend, I'm not going to waste time here. I need that duplicate key you have, you know what I'm talking about. Give it to me and we'll part ways: you'll keep drinking and I'll keep helping damsels in distress.";
			link.l1.go = "pirate_2";
		break;
		
		case "pirate_2":
			dialog.text = "Aww, mate! Didn't you listen to anything I just said! You must look smarter than you really are... working for that whore. Do you know who her husband is? Just recently, Governor Levasseur sent his loyal negro Kampacho to go 'talk to' a local and highly respected merchant. The black beat the poor bastard to death in his own shop! This merchant had shown some sort of minor disrespect to the governor's wife during a ball or something. And this same bitch seduced me with her looks and his doubloons\nThe duplicate key exists. I used to be a decent safecracker back in France, so it was child's play. If it wasn't for the daughter of Lyons's commandant... I'd never have gone pirate. Bah! Fuck it!";
			link.l1 = "This is all very sad, but let's talk business. Where is the key?";
			link.l1.go = "pirate_3";
		break;
		
		case "pirate_3":
			dialog.text = "Are you listening? I'm out of the game, mate! I was smart enough to see what was coming! I'm leaving this place for good as soon as my ship is ready to set sail. You want the key, pay for it. Don't be greedy now, I think you won't need any money for much longer.";
			link.l1 = "You know, you are right. I don't want to be a woman's plaything. Thank you for the advice, and stay safe at sea!";
			link.l1.go = "pirate_4";
			link.l2 = "Pay for it? To you? You are a pathetic thief and a coward. You should have stayed in that shithole, Lyons. Who knows, maybe the local commandant would have taken pity on you and let a degenerate thief be his son-in-law. I am not going to take pity on you, that's for sure. You can give me the key the easy way or the hard way, the choice is yours.";
			link.l2.go = "pirate_5";
			link.l3 = "(sigh) How much?";
			link.l3.go = "pirate_6";
		break;
		
		case "pirate_4":
			dialog.text = "Clever lad, that's the right decision, mate. Good luck. Hope you find a true and loving woman one day. Preferably a redhead or a blonde, am I right?";
			link.l1 = "Farewell, mate...";
			link.l1.go = "pirate_exit";
		break;
		
		case "pirate_exit":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_Fade("", "");
			ChangeCharacterAddressGroup(pchar, "Tortuga_tavern", "tables", "stay8");
			LAi_SetPlayerType(pchar);
			pchar.questTemp.FMQT = "huber";
			pchar.quest.FMQT_late1.win_condition.l1 = "Timer";
			pchar.quest.FMQT_late1.win_condition.l1.date.hour  = 18.0;
			pchar.quest.FMQT_late1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQT_late1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQT_late1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQT_late1.function = "FMQT_HuberTime";
			AddQuestRecord("FMQ_Tortuga", "9");
		break;
		
		case "pirate_5":
			dialog.text = "You insult me! Draw steel, you bastard!";
			link.l1 = "Let's see how well you can crack safes without arms!";
			link.l1.go = "pirate_duel";
		break;
		
		case "pirate_duel":
			DialogExit();
			LAi_SetSitType(npchar);
			// ключ квестовый от Калеуче - вернуть назад
			GiveItem2Character(npchar, "kaleuche_key");
			ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key_FMQT");
			i = makeint(MOD_SKILL_ENEMY_RATE/4);
			pchar.questTemp.FMQT = "duel";
			PChar.questTemp.duel.enemy = NPChar.id;
			if (MOD_SKILL_ENEMY_RATE > 2) PChar.questTemp.duel.enemyQty = i;
			AddDialogExitQuestFunction("Duel_Prepare_Fight");
		break;
		
		case "pirate_6":
			dialog.text = "You are a man of business, I'll give you that. You might actually make it. Fifty doubloons. On the table.";
			link.l1 = "Fifty gold pieces? For a piece of tin? Keelhaul me. Put the key on the table. Now.";
			link.l1.go = "pirate_7";
			if (PCharDublonsTotal() >= 50)
			{
				link.l2 = "Quite the price... Fine. Take them.";
				link.l2.go = "pirate_8";
			}
			else
			{
				link.l2 = "Quite the price... Fine. I will bring them soon. Stay here.";
				link.l2.go = "pirate_wait";
			}
		break;
		
		case "pirate_wait":
			DialogExit();
			AddLandQuestMark(npchar, "questmarkmain");
			LAi_SetSitType(npchar);
			npchar.Dialog.currentnode = "pirate_dublon";
			LAi_Fade("", "");
			ChangeCharacterAddressGroup(pchar, "Tortuga_tavern", "tables", "stay8");
			LAi_SetPlayerType(pchar);
		break;
		
		case "pirate_dublon":
			NextDiag.TempNode = "pirate_dublon"; // mitrokosta правка явного бага
			dialog.text = "Did you bring fifty doubloons?";
			link.l1 = "You know, I think you can live without them. The key. On the table.";
			link.l1.go = "pirate_7";
			if (PCharDublonsTotal() >= 50)
			{
				link.l2 = "Yeah. Take them.";
				link.l2.go = "pirate_8";
			}
			else
			{
				link.l2 = "I'm still getting them.";
				link.l2.go = "exit";
			}
		break;
		
		case "pirate_7":
			dialog.text = "Shall we dance?";
			link.l1 = "I'll lead.";
			link.l1.go = "pirate_duel";
		break;
		
		case "pirate_8":
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(50);
			Log_Info("You have given 50 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Good. Use your brains and you might get out of this with some pieces of eight and your head. Take the key and hear my advice. Free of charge. Levasseur's woman is dumb as a fish, yet she believes herself to be cunning. Don't trust her. Keep your cock in your pants and watch your pockets. She is not much of an opponent, just be careful and avoid bringing her husband into this. One last thing - there is a chest in her bower where she keeps her trinkets, easy to pick. She will put her cut there. You heard me. Be safe at sea, brother. Remember, brethren before wenches.";
			link.l1 = "Godspeed, mate...";
			link.l1.go = "pirate_9";
		break;
		
		case "pirate_9":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_Fade("", "");
			ChangeCharacterAddressGroup(pchar, "Tortuga_tavern", "tables", "stay8");
			LAi_SetPlayerType(pchar);
			pchar.questTemp.FMQT = "key";
			pchar.questTemp.FMQT.Caution = "true";
			FMQT_KeyNextDay();
			pchar.quest.FMQT_late3.win_condition.l1 = "Timer";
			pchar.quest.FMQT_late3.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.FMQT_late3.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQT_late3.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQT_late3.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQT_late3.function = "FMQT_KeyTime";
			AddQuestRecord("FMQ_Tortuga", "10");
			// ключ квестовый от Калеуче - вернуть назад
			GiveItem2Character(pchar, "kaleuche_key");
			ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key_FMQT");
		break;
		
		case "mercen":
			PlaySound("Voice\English\EvilPirates10.wav");
			dialog.text = "Damn it! I didn't expect... to hell with that woman! My master told me to avoid her kind. But a job is a job. I will get you after all.";
			link.l1 = "Well well, mate... Looks like she wanted to cheat both of us, can't say I'm surprised. Why should we keep fighting? Want a job? I have one. You have skill, I need men like you in my crew. Meal, bunk, regular wage, rum, and a fair share of any plunder. I'll give you my affidavit on it. What do you say?";
			//if(CheckCharacterPerk(pchar, "IronWill") || CheckCharacterPerk(pchar, "HT2") || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 34 || GetSummonSkillFromName(pchar, SKILL_FORTUNE) > 20) link.l1.go = "mercen_1";
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 34) link.l1.go = "mercen_1";
			else link.l1.go = "mercen_4";
		break;
		
		case "mercen_1":
			//if(CheckCharacterPerk(pchar, "IronWill")) notification("Iron Will", "IronWill");
			//if(CheckCharacterPerk(pchar, "HT2")) notification("Mimicry", "Mimicry");
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 34) notification("Skill Check Passed", SKILL_LEADERSHIP);
			//if(GetSummonSkillFromName(pchar, SKILL_FORTUNE) > 20) notification("Skill Check Passed", SKILL_FORTUNE);
			dialog.text = "You've got a silver tongue and your fame precedes you, cap'n, I'll give you that. Aye, I'm in. What's your ship's name?";
			link.l1 = "'"+pchar.ship.name+"'. Talk to the bosun, he'll find you a bunk. Welcome aboard!";
			link.l1.go = "mercen_2";
		break;
		
		case "mercen_2":
			dialog.text = "Ha! I'm moving up in the world. Give that bitch a kick for me.";
			link.l1 = "...";
			link.l1.go = "mercen_3";
		break;
		
		case "mercen_3":
			DialogExit();
			LAi_group_Delete("EnemyFight");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "FMQT_MercenHire", 10.0);
			AddQuestRecord("FMQ_Tortuga", "17");
		break;
		
		case "mercen_4":
			//if(!CheckCharacterPerk(pchar, "IronWill")) notification("Perk check failed", "IronWill");
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 35) notification("Skill Check Failed (35)", SKILL_LEADERSHIP);
			//if(GetSummonSkillFromName(pchar, SKILL_FORTUNE) < 21) notification("Skill Check Failed (21)", SKILL_FORTUNE);
			dialog.text = "You talk sweet. But not sweet enough if you want real professionals to join your ranks. Keep that in mind for the future. If you have one.";
			link.l1 = "Give it a try. Be swift, I have an engagement with a lady.";
			link.l1.go = "mercen_5";
			link.l2 = "No second chances today. I am a busy man, so let's not spoil the carpet. You are not being paid enough to die for some small-time putain. If they even paid you at all.";
			link.l2.go = "mercen_6";
		break;
		
		case "mercen_5":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FMQT_MercenDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "mercen_6":
			dialog.text = "You are right. No one has paid me... yet. I'll fix this right now. Do whatever you want...";
			link.l1 = "...";
			link.l1.go = "mercen_7";
		break;
		
		case "mercen_7":
			DialogExit();
			LAi_SetCurHPMax(npchar); 
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_group_Delete("EnemyFight");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
			AddQuestRecord("FMQ_Tortuga", "18");
			pchar.questTemp.FMQT.Roomfight = "true";
			FMQT_WifeFinalTalk();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

// Соломон Шнеур - старый еврей
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
//--------------------------------------за Голландию------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
			{
				if (pchar.questTemp.HWIC.Holl == "AbbyFather")
				{
					dialog.text = "What do you want from this old Jew, young man?";
					link.l1 = "Solomon, I need you to think carefully and remember the lost island where you were shipwrecked. You hid a stash there. I've spoken with your daughter. My boss, Lucas Rodenburg, has given me carte blanche to act in the best interests of your family. As I see it, the most important thing for you right now is recovering your family's capital, and you won't get a whiff of that gold without my help.";
					link.l1.go = "SolomonBonanza";
					DelLandQuestMark(npchar);
					break;
				}
				if (pchar.questTemp.HWIC.Holl == "AbbyFindScull" && makeint(Pchar.money) >= 200000)
				{
					dialog.text = "Oh, my young man, is that you? Can't you tell me anything good? Are you Christians here to torment this poor old Jew with questions again?";
					if (CheckCharacterItem(pchar, "SkullAztec"))
					{
						link.l1 = "I have found the island, though it was quite difficult. I have also found your chest with the money and this skull. I take it this is the skull of your grandfather-patriarch, whatever it was you were talking about.";
						link.l1.go = "SolomonBonanza_2";
					}
					link.l2 = "I have found the island, although it was no easy matter. I have also found your chest with the money. But there were no skulls in that chest.";
					link.l2.go = "SolomonBonanza_3";
					link.l3 = "No, I have no questions at this time.";
					link.l3.go = "exit";
					break;
				}
				if (pchar.questTemp.HWIC.Holl == "GiveLucasMoney" && GetQuestPastDayParam("questTemp.HWIC.Holl.LucasMoney") > 7)
				{
					dialog.text = "Oh, my young man, is that you? Can you tell me any good news? Or are you going to torment this poor old Jew with questions again?";
					link.l1 = "I have found the island, though it was quite difficult. I have also found your chest of money. Here you are.";
					link.l1.go = "SolomonBonanza_5";
					break;
				}
				dialog.text = "Hello, young man. What do you want from this poor old Jew?";
				link.l1 = "Good afternoon. No, nothing, I've just come to say hello.";
				link.l1.go = "exit";
				break;
			}
//----------------------------------------за Англию-----------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
			{
				if (pchar.questTemp.HWIC.Eng == "toAbigile")
				{
					dialog.text = "Good afternoon, young man. I see you've come for a purpose... What do you want? Am I getting something out of this, or did I miss something?";
					link.l1 = "Good afternoon, Solomon. I would like to speak with Abigail.";
					link.l1.go = "Solomon_treasure";
					DelLandQuestMark(npchar);
					break;
				}
				dialog.text = "Hello, young man. What do you want from this poor old Jew?";
				link.l1 = "Good afternoon, Solomon. Nothing, I've just come to say hello.";
				link.l1.go = "exit";
				break;
			}
//-----------------------------------------против всех-------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				if (pchar.questTemp.HWIC.Self == "toVillemstad")
				{
					dialog.text = "Good afternoon, young man. I see you've come here for a reason... What do you want? Am I getting something out of this, or have I missed something?";
					link.l1 = "I need to talk to Abigail. I've got a letter for her.";
					link.l1.go = "Abigile_kidnap";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileNextDayOver")
				{
					dialog.text = "Hello, young man. What do you want? Another letter for my daughter?";
					link.l1 = "No. Where is Abigail?";
					link.l1.go = "Abigile_GoOver";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SolomonHistory")
				{
					dialog.text = "Oy... Are you talking about my money, young man?";
					link.l1 = "Yes, mynheer. About the money you hid on some island. Is it true that you and Abigail can't remember its location?";
					link.l1.go = "Solomon_history";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SolomonHistoryAfter")
				{
					dialog.text = "Alright. I remember the fluyt and its captain. I even saw him once before in Amsterdam. The fluyt's name was 'Leiden' and the captain's name was Toff Keller.";
					link.l1 = "That's a start! I've got a lead now.";
					link.l1.go = "Solomon_history_3";
					pchar.questTemp.HWIC.Self = "SolomonHistoryEnd";
					break;
				}
				dialog.text = "Oy vey, what do you want from this poor old Jew this time?";
				link.l1 = "Good afternoon. No, nothing, I've just come to say hello.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Oy vey, what do you want from this poor old Jew this time?";
			link.l1 = "Good afternoon. No, nothing, I've just come to say hello.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

//-----------------------------------------------За Голландию-----------------------------------
		case "SolomonBonanza":
			PlaySound("Voice\English\hambit\Solomon Shneur-03.wav");
			dialog.text = "And what do you want from me? Do I look like a man who knows anything? How could I know that on such a God-forsaken day there would be a plot of land with goods and gold free for the taking out there? Imagine how all the gentiles out there walking the streets want to outwit a Jew like me and take my money!\nThere is an island. Not a single man there, except Abi and me. Not a single one. No one at all. There was a grotto in the middle of it. I put my chest there to save it from that pirate goyim Amalek! A chest filled with gold, not a tchotchke among them. I schlepped it all the way from the Old Country! Everything I had earned through the sweat of my brow is there. Plus, my grandfather's skull... Trust me, that thing saved us, yes-yes\nOh-ho-ho, it is an ancient talisman loaded with Talmudic magic! God save us from Amalek! Oy vey, it is difficult to start over in this age of the gentiles! I wish you knew, young man! Oh, I wish you knew!";
			link.l1 = "What on earth are you babbling about, you lunatic? Who cares. I'll deal with it myself. Bye!";
			link.l1.go = "SolomonBonanza_1";
		break;
		
		case "SolomonBonanza_1":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "AbbySeekIsland";
			pchar.quest.Joakim_meeteng.win_condition.l1 = "location";
			pchar.quest.Joakim_meeteng.win_condition.l1.location = "Villemstad_town";
			pchar.quest.Joakim_meeteng.function = "Create_Joakim";
		break;
		
		case "SolomonBonanza_2"://отдаем всё
			dialog.text = "Oy, there is a God and you are a true mensch! You have brought back not only my gold, but you have also redeemed the Shneur name! What a shande you have prevented! Mynheer Rodenburg can be rightfully proud to have captains like you under his command. I will give the skull to mynheer Rodenburg, he promised to pay a significant sum for it. I would like to thank you personally, you are a fine shabbos goy - please, accept this amulet as a small token of this Jew's thanks.";
			link.l1 = "Uh, thank you, I suppose.";
			link.l1.go = "SolomonBonanza_4";
			RemoveItems(PChar, "SkullAztec", 1);
			AddMoneyToCharacter(pchar, -200000);
			GiveItem2Character(pchar, "amulet_7"); 
			AddDialogExitQuestFunction("DeleteJoakimFromRoom");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			SetFunctionTimerCondition("Caleuche_StartTotal", 0, 0, 180, false); // таймер на Калеуче
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("Joakim"));
			pchar.questTemp.Caleuche.SolomonSkul = true;
		break;
		
		case "SolomonBonanza_3":
			dialog.text = "Oy, there is a God and you are a true mensch! You have brought back not only my gold, but you have also redeemed the Shneur name! What a shande you have prevented! As for the skull - oh well, never mind, he was a meshuggeneh schmuck anyway! Mynheer Rodenburg can be rightfully proud to have captains like you under his command. I would like to thank you personally, you are a fine shabbos goy - please, accept this amulet as a memento.";
			link.l1 = "Uh, thank you, I suppose.";
			link.l1.go = "SolomonBonanza_4";
			AddMoneyToCharacter(pchar, -200000);
			GiveItem2Character(pchar, "obereg_10");
			pchar.questTemp.HWIC.Holl.ScullnotReturn = "true";//признак для Лукаса
			ChangeCharacterComplexReputation(pchar, "nobility", -8);
			DelLandQuestMark(npchar);
		break;
		
		case "SolomonBonanza_4":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "AbbyLeavesMarried";//теперь можно говорить с Аби
			AddQuestRecord("Holl_Gambit", "1-32");
			AddLandQuestMark(characterFromId("Abigile"), "questmarkmain");
		break;
		
		case "SolomonBonanza_5":
			dialog.text = "What? What are you saying, young man? Is this true? Let me have a look... ";
			link.l1 = "Here is your money. It belongs to you and Abigail. But alas, I haven't found your grandfather's skull.";
			link.l1.go = "SolomonBonanza_6";
		break;
		
		case "SolomonBonanza_6":
			AddMoneyToCharacter(pchar, -200000);
			GiveItem2Character(pchar, "amulet_7"); 
			dialog.text = "Oh money, money, money, wonderful money... Hmm, this doesn't look like my money, though... Doesn't smell like my lovely lucre. But then again - money is all the same, young man, isn't it? I won't kvetch about it. 'Don't look a gift goy in the mouth,' as we like to say! Thank you so much for returning my savings. I would like to thank you too, please, accept this amulet. Now go and tell Abi the good news. I need to count this.";
			link.l1 = "Many happy returns, Solomon.";
			link.l1.go = "SolomonBonanza_4";
			pchar.questTemp.HWIC.Holl.LucasMoney = "true";//признак для Лукаса
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

//-------------------------------------------за Англию------------------------------------------------
		
		case "Solomon_treasure":
			dialog.text = "Oy vey, watch yourself! Mynheer Rodenburg is a step away from being my goy son-in-law. All the soldiers from the garrison will be here in a second should I cry for help!";
			link.l1 = "Who the hell are you?";
			link.l1.go = "Solomon_treasure_1";
		break;
		
		case "Solomon_treasure_1":
			dialog.text = "Listen to me, captain. I am her father, Solomon. Do the right thing, bring me my lost coins and the jade skull of her great-grandfather. This old Jew may not be as cunning as you, but even he knows you want something from his daughter.\nMaybe you were sent by someone, by some captain who knows me. I will tell Abi everything, don't worry. She is not at home now, she is praying for the souls of gentile sinners like you.";
			link.l1 = "That barely made any sense... Damn, you're a real piece of work. Goodbye, you old miser.";
			link.l1.go = "Solomon_treasure_2";
		break;
		
		case "Solomon_treasure_2":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "2-17");
			pchar.questTemp.HWIC.Eng = "AbigileInChurch";
			sld = characterFromId("Abigile");
			sld.greeting = "abigile_3";
			ChangeCharacterAddressGroup(sld, "Villemstad_church", "goto", "goto1");//Аби в церковь
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
//----------------------------------------------против всех---------------------------------------------	
		
		case "Abigile_kidnap":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Villemstad");
			dialog.text = "A letter? You don't say! Listen here, goy, Mynheer Rodenburg is a step away from being my son-in-law. You can haul your tuchis out of here because I like him!";
			link.l1 = "Listen, I don't give a damn who your son-in-law is. I am obliged to give this letter to Abigail. Do you know where I can find her? And who the devil are you?";
			link.l1.go = "Abigile_kidnap_1";
		break;
		
		case "Abigile_kidnap_1":
			dialog.text = "Who am I? I am her father, Solomon... And I don't like you, goy.";
			link.l1 = "I'd be more worried if you said you did like me. Now, are you going to keep patronizing me or will you get Abigail? I say again, I am a messenger! I have a letter for your daughter!";
			link.l1.go = "Abigile_kidnap_2";
		break;
		
		case "Abigile_kidnap_2":
			dialog.text = "Give this letter to me. I will deliver it to my daughter.";
			link.l1 = "I'll shave your locks and tweak your nose before I hand you this letter. I have orders to deliver this message to her personally. I wasn't told a word about her father and I couldn't care less. Where can I find Abigail?";
			link.l1.go = "Abigile_kidnap_3";
		break;
		
		case "Abigile_kidnap_3":
			dialog.text = "As soon as I scream, young boy, every soldier in town will be here at once. Don't be so stubborn, you can see that I hold all the cards.";
			link.l1 = "Jesus, Mary, and Joseph! Really? And then what? You expect them to clap me in irons for delivering a letter? Don't be ridiculous!";
			link.l1.go = "Abigile_kidnap_4";
		break;
		
		case "Abigile_kidnap_4":
			DialogExit();
			sld = characterFromId("Abigile");
			ChangeCharacterAddressGroup(sld, "Villemstad_houseSP2", "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Abigile_GoOver":
			dialog.text = "Are you meshuggeneh? You've excited my poor girl half to death with your letter... She decided to go after that schmuck English captain! She sailed away on the first available ship! Oy vey, my poor daughter! What shall this old Jew do now? My life is ruined! It's a shande! Leave me to my misery, or stay and gloat, I care not! Ohhh my poor Abigail! You've brought your father's grey head down to Sheol in despair!";
			link.l1 = "Well, how about that! Guess she couldn't wait a moment longer. Bye, Solomon!";
			link.l1.go = "Abigile_GoOver_1";
		break;
		
		case "Abigile_GoOver_1":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-69");
			CloseQuestHeader("Holl_Gambit");
			pchar.questTemp.HWIC.Self = "end";
			pchar.questTemp.HWIC.Detector = "self_fail";
		break;
		
		case "Solomon_history":
			PlaySound("Voice\English\hambit\Solomon Shneur-03.wav");
			dialog.text = "What does it look like? It's just an island with no one but me and Abigail. That's where I hid my chest, to prevent that pirate goy Amalek from taking it. Everything I honestly earned through the sweat of my brow is in that chest...";
			link.l1 = "Tell me, Solomon, could you perhaps recall the name of the fluyt your daughter mentioned? And what was her captain's name?";
			link.l1.go = "Solomon_history_1";
		break;
		
		case "Solomon_history_1":
			dialog.text = "Hmm... Well, I do not know. This poor old Jew's head is scrambled like a pan of gefilte fish! And why are you asking, young man?";
			link.l1 = "I just want to help your daughter, Solomon. I cannot promise anything, but I'd like to try. My former boss treated her poorly, and after that I feel obliged to help her settle down somehow.";
			link.l1.go = "Solomon_history_2";
		break;
		
		case "Solomon_history_2":
			dialog.text = "Oy vey, well if that's the case...";
			link.l1 = "";
			link.l1.go = "Solomon_history_3";
			pchar.questTemp.HWIC.Self = "SolomonHistoryNext";
		break;
		
		case "Solomon_history_3":
			DialogExit();
			sld = characterFromId("Abigile");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Solomon_thanks":
			dialog.text = "Young man! Wait!";
			link.l1 = "Yes?";
			link.l1.go = "Solomon_thanks_1";
		break;
		
		case "Solomon_thanks_1":
			dialog.text = "Young man! I would like to thank you for everything you've done for me and my daughter. You saved us. I am sorry for giving you a hard welcome the first time we met and for doubting your sincere desire to help. Please, forgive this old Jew. You are truly a blessed man among the gentiles. Now tell me, didn't you find anything else besides my money in the grotto?";
			link.l1 = "No, Solomon. There was nothing but money. I had to fight van Berg's cutthroats - it was he who sank your ship months ago. It might be that they had already stolen something... What else was supposed to be there?";
			link.l1.go = "Solomon_thanks_2";
		break;
		
		case "Solomon_thanks_2":
			dialog.text = "Oh, nothing important... Just one ancient family relic... Well, never mind! Forget about it, he was a fool anyway! And... Just one more thing, young man... ";
			link.l1 = "Go on.";
			link.l1.go = "Solomon_thanks_3";
		break;
		
		case "Solomon_thanks_3":
			dialog.text = "You... well, I have found out something about you. Our governor holds you in high esteem, and you are a notable captain. I'll tell you a secret... my daughter likes you a lot. She told me that herself. Maybe... you will think about this? Abigail is a very good girl, I assure you, better than any of the shiksa strumpets you may have met in your travels.";
			link.l1 = "Oy vey... It's not that simple, Solomon. Your daughter is a rare jewel indeed. You take good care of her.";
			link.l1.go = "Solomon_thanks_4";
		break;
		
		case "Solomon_thanks_4":
			dialog.text = "Think it over, young man. Think again and come back! We'd love to see you again!";
			link.l1 = "Sure...bye, Solomon.";
			link.l1.go = "Solomon_thanks_5";
		break;
		
		case "Solomon_thanks_5":
			DialogExit();
			LocatorReloadEnterDisable("Villemstad_houseSp2", "reload1", false);
			AddQuestRecord("Holl_Gambit", "3-65");
			NextDiag.CurrentNode = "First time";
		break;
		
		case "Solomon_poor":
			dialog.text = "Oyyy... Sometimes it's impossible to start a new life, young man. To live in poverty - what could be worse for an old fool like me?";
			link.l1 = "I am sorry, Solomon. Stand firm and seek Christ.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Solomon_poor";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("You are a "+GetSexPhrase("Thief, mister! Guards, seize him","Thief, girl! Guards, seize her")+"!!!","Just look at that! The moment I was lost in contemplation, you decided to check my chest! Get the thief!!!","Guards! Robbery! Catch the thief!!!");
			link.l1 = "Damn it!";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}

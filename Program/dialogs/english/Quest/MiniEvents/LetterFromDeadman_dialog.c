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
		
		case "Sailor_1":
			dialog.text = "What do you want, "+GetSexPhrase("mate","lass")+"? If you're offering me some rum, I won't say no. I've walked so many circles around this godforsaken town, my legs are about to tie themselves in knots. What's your name, then?";
			link.l1 = "Captain "+GetFullName(pchar)+". You're not from the 'Eagle', are you?";
			link.l1.go = "Sailor_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Sailor_2":
			if (pchar.sex == "man")
			{
				dialog.text = "And I - "+GetFullName(npchar)+". And yes, I'm from the 'Eagle'. Do you like our ship, captain?";
			}
			else
			{
				dialog.text = "Captain? Well, well... Ahem... I'm Antonio Velenta. And yes, I'm from the 'Eagle'. Did our ship catch your eye, Captain?";
			}
			link.l1 = "A ship is a ship. You’d better hurry aboard instead of wandering around town—your captain is already spitting thunder. He means to leave port before the tide goes out, and something tells me, lad, he won’t be waiting for you.";
			link.l1.go = "Sailor_3";
		break;
		
		case "Sailor_3":
			dialog.text = "Blast it all... I know, I know... But I've still got some unfinished business in this city. Fancy earning a couple of doubloons, eh, Cap'n?";
			link.l1 = "Doubloons are never unwelcome. But earning them is one thing, getting into trouble is another. What's the job? Out with it.";
			link.l1.go = "Sailor_4";
		break;
		
		case "Sailor_4":
			dialog.text = "You see, while I was unloading the hold, I stumbled upon a letter. It didn’t look like it was hidden on purpose, just lying there among some old barrels. Our fluyt has seen more than one boarding, so there’s no telling where it came from.";
			link.l1 = "So you found the letter, but what of it?";
			link.l1.go = "Sailor_5";
		break;
		
		case "Sailor_5":
			dialog.text = "It's addressed to a certain Marisa Caldera from Porto Bello. Sealed with wax... I can feel it in my gut – this isn't some trivial matter. Maybe it's from a captain, maybe from a merchant... but definitely not from an ordinary sailor like me! Only, I won't have time to find the addressee – our captain really doesn't take jokes lightly.  Don't you want to buy it off me? I'll let it go for a thousand pesos. You're a captain, it won't be hard for you to track down this señorita. And who knows, she might reward you with gold, or something else... you catch my drift?";
			if (sti(pchar.Money) >= 1000)
			{
				link.l1 = "Well then, maybe I'll find your Marisa.  Either way, I've got nothing to lose. Except for a thousand pesos. Hand over the letter.";
				link.l1.go = "Sailor_6";
			}
			else
			{
				Notification_Money(false, 1000, "peso");
			}
			link.l2 = "Sorry, mate, but you'll have to find someone else. I've got more important things to do than delivering letters.";
			link.l2.go = "Sailor_end";
		break;
		
		case "Sailor_end":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Sailor_end");
		break;
		
		case "Sailor_6":
			dialog.text = "Here you go. Well, take care, "+GetSexPhrase("mate","lass")+", I should go – I wouldn't want my belongings to sail away with the 'Eagle'.";
			link.l1 = "...";
			link.l1.go = "Sailor_accept";
			GiveItem2Character(PChar, "LFD_letter");
			AddMoneyToCharacter(pchar, -1000);
		break;
		
		case "Sailor_accept":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Sailor_accept");
			AddQuestRecord("LFD", "2");
		break;
		
		case "Dolores_1":
			dialog.text = "Who are you? What do you want?";
			link.l1 = "My name is Captain "+GetFullName(pchar)+". I'm looking for Marisa Caldera.";
			link.l1.go = "Dolores_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Dolores_2":
			sld = CharacterFromID("PortoBello_priest");
			dialog.text = "I don't know any Marisa. You've got the wrong door. Leave now before I call the guards – they'll throw you out in no time.";
			link.l1 = "Father "+sld.name+" told me that you are her friend. I have a letter addressed to her. Judging by its appearance, it is very late. I want to deliver it in person.";
			link.l1.go = "Dolores_3";
		break;
		
		case "Dolores_3":
			dialog.text = "Ah, Father... He is too kind to everyone, but he rarely misjudges people. You can leave the letter with me. I'll make sure it gets into her hands.";
			link.l1 = "Forgive me, señorita, but I would prefer to deliver it in person. She may have questions about how I came by it and why it took so long to arrive.";
			link.l1.go = "Dolores_4";
		break;
		
		case "Dolores_4":
			dialog.text = "And you expect me to simply believe in your good intentions? I've seen plenty of scoundrels with a virtuous face. Leave the letter or be on your way.";
			link.l1 = "I give you my word as a captain that I will do no harm to you or to Marisa. Moreover, you may invite the guard or anyone else skilled with a weapon to our meeting. I have no other purpose but to deliver this letter to Marisa personally.";
			link.l1.go = "Dolores_5";
		break;
		
		case "Dolores_5":
			dialog.text = "Alright. Come by tomorrow after eleven o'clock at night. I can't promise she'll agree to meet, but I'll pass on everything you've said.";
			link.l1 = "I'll be there. See you soon.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Dolores_1");
		break;
		
		case "Marisa_1":
			dialog.text = "Hello, "+GetAddress_Form(NPChar)+" "+pchar.lastname+". You were looking for me, and here I am. Dolores said you have a letter for me?";
			link.l1 = "Good day, Mrs. Caldera. That's right, here you are. Alas, it seems it took quite a long time to reach you.";
			link.l1.go = "Marisa_2";
			DelLandQuestMark(npchar);
			TakeItemFromCharacter(pchar, "LFD_letter");
			notification("Given: Letter for Marisa Caldera", "None");
		break;
		
		case "Marisa_2":
			dialog.text = "Dolores... This is his handwriting... Ramiro's handwriting!";
			link.l1 = "...";
			link.l1.go = "Marisa_2_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
			sld = CharacterFromID("LFD_Dolores");
			LAi_CharacterEnableDialog(sld);
		break;
		case "Marisa_2_1":
			StartInstantDialog("LFD_Dolores", "Marisa_3", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_3":
			dialog.text = "But how is that possible? It's been two years!";
			link.l1 = "...";
			link.l1.go = "Marisa_3_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_3_1":
			StartInstantDialog("LFD_Marisa", "Marisa_4", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_4":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+" Captain... How did you come by it? Where did you find it? I must know everything! Please, tell me everything you know.";
			link.l1 = "This letter came to me from a sailor. He found it in a dark corner of his ship’s hold and wanted to deliver it to you himself, but was forced to return to his vessel in haste. So he asked me to find you, and here I am. That’s all I know...";
			link.l1.go = "Marisa_5";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Marisa_5":
			dialog.text = "Thank you, "+GetAddress_Form(NPChar)+"! Thank you so much! Please, don't go. I want to talk to you some more, but first... I need to read this letter.";
			link.l1 = "Of course, Lady Caldera. I will be here.";
			link.l1.go = "Marisa_6";
		break;
		
		case "Marisa_6":
			DialogExit();
			SetLaunchFrameFormParam("Twenty minutes passed, Marisa read the letter...", "Run_Function", 0, 4.0);
			SetLaunchFrameRunFunctionParam("LFD_Dolores_3", 0.0);
			LaunchFrameForm();
		break;
		
		case "Marisa_11":
			dialog.text = "Dolores... He wrote this letter before his last voyage. He wanted to tell me that he had a chance to buy a large shipment of ebony from a merchant in Belize, but he didn't have enough money. That's when he took out this loan... Two hundred doubloons... Because of which I can find no peace now.";
			link.l1 = "...";
			link.l1.go = "Marisa_11_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_11_1":
			StartInstantDialog("LFD_Dolores", "Marisa_12", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_12":
			dialog.text = "That explains everything... But, alas, it won’t lighten your burden. Stay strong, Marisa. Darkness is not eternal, and this debt won’t haunt you forever.";
			link.l1 = "...";
			link.l1.go = "Marisa_12_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_12_1":
			StartInstantDialog("LFD_Marisa", "Marisa_13", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_13":
			dialog.text = "No, Dolores, there won't be! Ramiro wrote that he has a stash... at our spot. If it's still untouched, maybe I can pay off the debt and finally escape this nightmare.";
			link.l1 = "...";
			link.l1.go = "Marisa_13_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_13_1":
			StartInstantDialog("LFD_Dolores", "Marisa_14", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_14":
			dialog.text = "The Lord has shown you mercy! He has heard our prayers...";
			link.l1 = "...";
			link.l1.go = "Marisa_14_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_14_1":
			StartInstantDialog("LFD_Marisa", "Marisa_15", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_15":
			dialog.text = "Captain, once again, thank you for bringing me this letter. It means the world to me... But I must ask you for one more favour. You see, my husband Ramiro was everything to me, and I never sought protection from any other man. Now that he is gone, I have no one left to turn to, no family of my own\nI must reach his hiding place – it's outside the city. But I'm too afraid to go alone, my late husband's creditors are after me. You acted honourably in finding me to deliver the letter... Please, help me once more.";
			link.l1 = "Of course, Marisa, I'll escort you. When would you like to set off?";
			link.l1.go = "Marisa_16";
			link.l2 = "I'm sorry, señora, but my stay in your city has already lasted too long. Country walks are not part of my plans.";
			link.l2.go = "Marisa_end_1";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Marisa_end_1":
			dialog.text = "I understand... You've already done more for me than I could have hoped for. Thank you, Captain, and farewell.";
			link.l1 = "Goodbye.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_end");
		break;
		
		case "Marisa_16":
			dialog.text = "Thank you, Captain. Come tomorrow at dawn, by seven o'clock. I will be ready.";
			link.l1 = "Then until we meet again, señora.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_1");
		break;
		
		case "Marisa_21":
			if (GetHour() >= 7 && GetHour() <= 19)
			{
				if (pchar.sex == "man")
				{
					dialog.text = "Caballero, there you are... You are truly a man of honour! Let us set off. Our path leads through the jungle to the grotto not far from Mosquitos Bay.";
				}
				else
				{
					dialog.text = "Captain, there you are... I knew you would come. You know, this is the first time I've ever met a woman who commands her own ship. And I can already see that you are every bit the equal of any man—both in honour and in nobility!";
				}
				link.l1 = "Excellent, señora. Then let's not waste any time. Stay close and don't stray for a moment.";
				link.l1.go = "Marisa_go_cove";
				if (startHeroType == 4) // если ГГ Элен
				{
					link.l1 = "Thank you, Marisa. My father was a captain and a man of honour – and from childhood he instilled in me those same ideals.";
					link.l1.go = "Marisa_22";
				}
			}
			else
			{
				dialog.text = "Come at dawn, by seven o'clock. I'll be ready.";
				link.l1 = "See you then, señora.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Marisa_21";
			}
		break;
		
		case "Marisa_22":
			dialog.text = "Was he? Did he meet the same fate as my Ramiro?";
			link.l1 = "He would surely have preferred to meet his end with a sword in hand or in the midst of a storm. But fate had other plans – he was finished off by an illness he never spoke of to anyone.";
			link.l1.go = "Marisa_23";
		break;
		
		case "Marisa_23":
			dialog.text = "I'm sorry for your loss, "+pchar.name+" The Lord takes the best among us... And though we may not always understand why, it is His will. All we can do is pray for the repose of their immortal souls.";
			link.l1 = "...";
			link.l1.go = "Marisa_24";
		break;
		
		case "Marisa_24":
			dialog.text = "Let's be on our way. Our path leads through the jungle to the grotto not far from Mosquitos Bay.";
			link.l1 = "Of course. Stay close and don't wander off for a moment.";
			link.l1.go = "Marisa_go_cove";
		break;
		
		case "Marisa_go_cove":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Marisa_2");
		break;
		
		case "Marisa_31":
			dialog.text = "Here we are... Ramiro and I once sheltered from the rain here, back when we were young, before he became my husband. It was then he told me he would win my heart, no matter what it took.";
			link.l1 = "I'm sorry you had to come here alone, without your husband, señora. Places like this hold many memories. Let's have a look around – perhaps, besides memories, we'll find what Ramiro kept for the hardest times.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_4");
		break;
		
		case "Marisa_32":
			dialog.text = ""+GetSexPhrase("Señor "+pchar.lastname+"",""+pchar.name+"")+"... Did you find anything? Is it what Ramiro left behind? I don't even know what scares me more – that it's empty, or that it won't be enough to cover the debt...";
			if (PCharDublonsTotal() >= 400 && GetCharacterItem(pchar, "jewelry2") >= 10 && GetCharacterItem(pchar, "jewelry3") >= 10 && CheckCharacterItem(PChar, "mushket1"))
			{
				link.l1 = "(shows) Here, this is everything that was in the chest. I hope it's enough to change your fate for the better.";
				link.l1.go = "Marisa_33";
				DelLandQuestMark(npchar);
			}
			else
			{
				link.l1 = "I'm still looking through the chest.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Marisa_32";
			}
		break;
		
		case "Marisa_33":
			dialog.text = "Ah, Captain! Of course! That should be enough! But I can't let your help go unrewarded. Take a hundred doubloons. If it weren't for you, I would never have learned about this stash and would still be hiding from the men sent by Ramiro's creditor...";
			link.l1 = "You are very generous, señora, thank you. In our line of work, gold is never wasted.";
			link.l1.go = "Marisa_34";
			link.l2 = "No, señora. You need this money far more than I do. What matters is that now you can leave your troubles behind and live in peace. That’s more than enough for me.";
			link.l2.go = "Marisa_35";
			RemoveDublonsFromPCharTotal(400);
			RemoveItems(pchar, "jewelry2", 10);
			RemoveItems(pchar, "jewelry3", 10);
			TakeItemFromCharacter(pchar, "mushket1");
			TakeItemFromCharacter(pchar, "obereg_7");
			TakeItemFromCharacter(pchar, "amulet_11");
			notification("Given: Amulet 'Cimaruta'", "None");
			notification("Given: Amulet 'Fisherman'", "None");
			notification("Given: Matchlock Musket", "None");
			notification("Given: Diamond (10)", "None");
			notification("Given: Ruby (10)", "None");
		break;
		
		case "Marisa_34":
			dialog.text = "Well then, "+GetSexPhrase("señor",""+pchar.name+"")+", we should get moving. If I was spotted in town, someone might be following us. Best not linger here.";
			link.l1 = "You're right, Marisa. Let's go.";
			link.l1.go = "Marisa_naemnik";
			TakeNItems(pchar, "gold_dublon", 100);
		break;
		
		case "Marisa_35":
			dialog.text = "Captain, please... my husband kept this weapon to protect our family, and I am certain—in your hands, it will serve a just cause. Ramiro would be glad to know it has gone to the person who saved me when all hope was lost.";
			link.l1 = "Alright, Marisa, thank you. You are a kind and honourable woman, and I truly regret that fate has been so cruel to you.";
			link.l1.go = "Marisa_36";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "Marisa_36":
			dialog.text = "Sometimes the Lord sends us hard days, or even years, to test our faith, but He never abandons those who walk the righteous path. He has sent you to help me, and now, I hope, my greatest trouble will soon be behind me.\nBut for now, it's time for us to go back. We've stayed here long enough, and it could be dangerous, since they're still looking for me.";
			link.l1 = "Of course, señora, let's go.";
			link.l1.go = "Marisa_naemnik";
			GiveItem2Character(pchar, "mushket1");
			GiveItem2Character(pchar, "obereg_7");
			GiveItem2Character(pchar, "amulet_11");
		break;
		
		case "Marisa_naemnik":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Marisa_6");
		break;
		
		case "Naemnik_1":
			dialog.text = "Ha! So here’s our missing one! Did you really think you could hide here, in this hole like a mouse, and I wouldn’t find you? I’ve turned the whole town upside down more than once, and here you are all along"+GetSexPhrase(", and on top of that, you went on a date with some pup. Where’s my money, you little whore? You’d better hand it over right now, or this cave will be your grave.",".")+"";
			link.l1 = "...";
			link.l1.go = "Naemnik_1_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Naemnik"));
			CharacterTurnByChr(CharacterFromID("LFD_Naemnik"), CharacterFromID("LFD_Marisa"));
		break;
		case "Naemnik_1_1":
			StartInstantDialog("LFD_Marisa", "Naemnik_2", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Naemnik_2":
			dialog.text = "You...";
			link.l1 = "...";
			link.l1.go = "Naemnik_2_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Naemnik"));
			CharacterTurnByChr(CharacterFromID("LFD_Naemnik"), CharacterFromID("LFD_Marisa"));
		break;
		case "Naemnik_2_1":
			StartInstantDialog("LFD_Naemnik", "Naemnik_3", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Naemnik_3":
			dialog.text = "...";
			link.l1 = "So you're the one making a living by shaking down women for debts? Judging by your chosen trade, brains were never your strong suit. It's a wonder you managed to find your way here on your own, instead of just following someone smarter... like your own boot, for example.";
			link.l1.go = "Naemnik_4";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Naemnik_4":
			if (pchar.sex == "man")
			{
				dialog.text = "Shut your mouth, hero. Your time will come, but first I’ll deal with her. She owes five hundred and twenty-five doubloons – that’s her debt with interest. Either she pays in full, or she stays here forever – to feed the worms. But since you’re so righteous, you can pay for her, and I’ll be gone.";
				if (PCharDublonsTotal() >= 525)
				{
					link.l1 = "You think you can just walk in, insult a lady, ignore me, and walk out of here in one piece, with the doubloons no less? Seems you’re not particularly bright. But I won’t start a brawl in front of a woman. So here’s my offer: you apologise to Madam Caldera, take your doubloons, and get the hell out of here. Or I’ll have to teach you some proper manners after all.";
					link.l1.go = "Naemnik_5";
					Notification_Money(true, 525, "dublon");
				}
				else
				{
					Notification_Money(false, 525, "dublon");
				}
			}
			else
			{
				dialog.text = "Shut your mouth and wait your turn. I'll deal with you later, once I'm finished with this wretch. She owes five hundred and twenty-five doubloons – that's her debt with interest. Since you're so righteous, you can pay for her, and I'll be gone.";
				if (PCharDublonsTotal() >= 525)
				{
					link.l1 = "Well, I'm willing to forgive your rough manners and even your rudeness towards me. But if you want to get your doubloons and leave here in one piece, you'll have to apologise to Lady Caldera. Otherwise, we'll see who handles a weapon better. And believe me, I don't carry mine just for show.";
					link.l1.go = "Naemnik_5";
					Notification_Money(true, 525, "dublon");
				}
				else
				{
					Notification_Money(false, 525, "dublon");
				}
			}
			link.l2 = "Clearly, you’re not burdened with much wit if you thought I’d wait my turn. And even less so if you believed I’d turn a blind eye to all the trouble you and your kind have brought upon Lady Caldera.";
			link.l2.go = "Naemnik_bitva";
		break;
		
		case "Naemnik_5":
			dialog.text = "Well then, have it your way. If we can get the money without unnecessary risk, I see no reason to stick my neck out. Hand over the doubloons – and be off.";
			link.l1 = "First, apologise to the lady.";
			link.l1.go = "Naemnik_6";
		break;
		
		case "Naemnik_6":
			dialog.text = "Forgive me, señora. The devil got the better of me.";
			link.l1 = "...";
			link.l1.go = "Naemnik_7";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Naemnik"));
			CharacterTurnByChr(CharacterFromID("LFD_Naemnik"), CharacterFromID("LFD_Marisa"));
		break;
		
		case "Naemnik_7":
			dialog.text = "Happy"+GetSexPhrase("","")+"? Hand over the gold and I'll be on my way. I've got plenty to do, no time to stand around exchanging pleasantries with you.";
			link.l1 = "Take your doubloons and get out of here.";
			link.l1.go = "Naemnik_7_1";
			CharacterTurnByChr(npchar, pchar);
			RemoveDublonsFromPCharTotal(525);
		break;
		
		case "Naemnik_7_1":
			StartInstantDialog("LFD_Marisa", "Marisa_37", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			ChangeCharacterNationReputation(pchar, SPAIN, 10);
		break;
		
		case "Marisa_37":
			dialog.text = "Captain, truly, I don't understand... What does this mean?";
			link.l1 = "That means you owe nothing now. You are free.";
			link.l1.go = "Marisa_38";
			CharacterTurnByChr(npchar, pchar);
			
			sld = CharacterFromID("LFD_Naemnik");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", 5);
			sld.lifeday = 0;
		break;
		
		case "Marisa_38":
			dialog.text = "But... I don't have the full amount to pay you back right now. If you could wait a little...";
			link.l1 = "You don't understand, Marisa. You don't owe me anything. You don't owe anyone anything anymore. And the money you found will be very useful to you. Go back to your old life – the church is waiting for you.";
			link.l1.go = "Marisa_39";
		break;
		
		case "Marisa_39":
			dialog.text = "I... I just can't believe it. Things like this don't happen, "+GetSexPhrase("caballero","senorita")+"! You paid a fortune for me... just like that? And now it's all over? No debt, no pursuit? Tell me, is it true?";
			link.l1 = "It's true, señora. It's all over. You don't owe anyone anything anymore.";
			link.l1.go = "Marisa_40";
		break;
		
		case "Marisa_40":
			dialog.text = "Oh, Captain, you are so noble! I feel as though you were sent by God! But I can't even imagine how to thank you. You've... completely changed my life, and I... what could I possibly do for you?";
			link.l1 = "You don't need to do anything, Marisa. Just live. Without fear, without the chains of the past. Go back to your old life and find happiness in it – that will be the best way to thank me. Come, I'll walk you to the town.";
			link.l1.go = "Naemnik_mir";
		break;
		
		case "Naemnik_bitva":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Naemnik_bitva");
		break;
		
		case "Naemnik_mir":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Naemnik_mir");
		break;
		
		case "Marisa_41":
			dialog.text = "What have you done, Captain, you've killed him!";
			link.l1 = "That's right, señora. I had to protect you and your honour...";
			link.l1.go = "Marisa_42";
		break;
		
		case "Marisa_42":
			dialog.text = "Oh, Captain, the taking of a life, even one such as his, is a terrible and heavy sin! You will have to pray day and night to wash even a little of it from your immortal soul. God is my witness, I could have simply given him all I had and he would have left... But now... now his blood is on your hands, and only the heavens will decide whether you are to be forgiven!";
			link.l1 = "Perhaps it was the will of the Lord. But let’s not dwell on that. Let’s get out of this cave instead.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Naemnik_bitva_3");
		break;
		
		case "Marisa_51":
			dialog.text = "Captain, allow me to thank you once again! I shall pray for your health and well-being, "+pchar.name+". Please, come to our church – may the Lord grant you forgiveness for all your sins and His blessing.";
			link.l1 = "Maybe I'll drop by sometime. And keep in mind, Marisa, if I don't see your happy face there, I'll be very disappointed.";
			link.l1.go = "Marisa_52";
		break;
		
		case "Marisa_52":
			dialog.text = "Ah, "+GetAddress_Form(NPChar)+"... You are so kind to me. I will be truly glad to see you again in our town. But for now, forgive me, I can't wait to put my life in order and share the good news with Dolores.";
			link.l1 = "Of course, Marisa. Goodbye. Take care of yourself.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_In_Church");
		break;
		
		case "Marisa_54":
			dialog.text = "Captain, allow me once again to express my endless gratitude! You have done the impossible for me! For your kindness and nobility, I want to tell you how I managed to avoid the mercenaries for these past two years. Perhaps this knowledge may one day be of use to you as well.";
			link.l1 = "Thank you, señora. In matters like these, knowledge is worth as much as gold. I’m listening.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Finish_In_Town_NaemnikAlive_2");
		break;
		
		case "Marisa_55":
			dialog.text = "That's how I spent these two years. In a world where strength means so much, knowing how to stay in the shadows opens up opportunities others can only dream of.";
			link.l1 = "Thank you for sharing your story, Marisa. You’ve been through a lot, and your experience is truly invaluable.";
			link.l1.go = "Marisa_56";
			AddCharacterExpToSkill(pchar, "Sneak", 500);
		break;
		
		case "Marisa_56":
			dialog.text = "I will be truly glad to see you in our town again. Please, come to our church—may the Lord grant you forgiveness for all your sins and His blessing.";
			link.l1 = "Maybe I'll drop by sometime. And keep in mind, Marisa, if I don't see your happy face there, I'll be very disappointed.";
			link.l1.go = "Marisa_57";
		break;
		
		case "Marisa_57":
			dialog.text = "Ah, Captain... You are so kind to me. But now, forgive me, I can't wait to put my life in order and share the good news with Dolores.";
			link.l1 = "Of course, Marisa. Goodbye. Take care of yourself.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_In_Church");
			
			//слухи
			AddSimpleRumourCity(""+GetSexPhrase("Did you hear? Captain "+GetFullName(pchar)+" paid off Calder's widow’s debt from his own pocket! Not many would part with that kind of money for a stranger. Seems Spain still has true caballeros left!","It warms the heart to see that Spain is home not only to worthy caballeros, but also to women whose honor and courage rival any man’s.")+"", "PortoBello", 7, 1, "");
			AddSimpleRumourCity("They say a certain captain paid his own money to free Calder’s widow from her late husband’s debts! Not everyone would act so nobly. A true person of honor, don’t you think?", "PortoBello", 7, 1, "");
		break;
		
		case "Marisa_61":
			if (CheckAttribute(pchar, "questTemp.LFD_NaemnikDead"))
			{
				switch (rand(1))
				{
					case 0:
						dialog.text = "Captain, it's such a pleasure to see you again! I was hoping you would stop by. Perhaps today you have time to stay a while and pray?";
						link.l1 = "Glad"+GetSexPhrase("","")+" meeting, Marisa. But I'm afraid I can't afford to linger right now. I remember my duty to the Lord, but prayer will have to wait.";
						link.l1.go = "Marisa_62";
					break;

					case 1:
						dialog.text = "Captain, you again! Always a pleasure. It seems the Lord won't let you forget the way to the church... Perhaps you'll find a moment for prayer after all?";
						link.l1 = "Marisa, it's good to see you. But I can't stay – my business cannot wait. I believe the Lord knows my thoughts even without prayer.";
						link.l1.go = "Marisa_63";
					break;
				}
			}
			else
			{
				switch (rand(1))
				{
					case 0:
						dialog.text = "Captain, what a joy it is to see you again! Every day I thank the Lord for your kindness. The world became brighter when you helped me.";
						link.l1 = "Glad"+GetSexPhrase("","")+"   Good to see you in good health, Marisa. I hope life hasn't brought you any more unpleasant surprises. You look much happier.";
						link.l1.go = "Marisa_64";
					break;

					case 1:
						dialog.text = "Captain, I’m so glad to see you! Every time you come to our church, I feel at peace. You bring with you the light of good deeds.";
						link.l1 = "And I'm glad"+GetSexPhrase("","")+" Good to see you, Marisa. Have you grown used to a quiet life, or do you still look back sometimes?";
						link.l1.go = "Marisa_65";
					break;
				}
			}
			SetTimerFunction("LFD_Marisa_HelloAgain", 0, 0, 1);
		break;
		
		case "Marisa_62":	
			dialog.text = ""+pchar.name+", if everyone kept putting off prayer, the world would have long since fallen into darkness. Set aside your worries for a while – repentance gives you the strength to carry on.";
			link.l1 = "I understand, Marisa, but I truly can't right now. I believe the Lord will hear me even without words.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_62_1";
		break;
		
		case "Marisa_62_1":	
			dialog.text = ""+pchar.name+", have you changed your mind? Sins do not simply vanish on their own, and the longer you wait, the heavier they become.";
			link.l1 = "Alas, I must be off. But next time, I promise I will pray.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_62_1";
		break;
		
		case "Marisa_63":	
			dialog.text = "But faith is not just about knowing, but about acting! You can't keep putting off the path to redemption forever. Don't you want to feel the relief of casting off the weight of sin?";
			link.l1 = "Perhaps, but not now. May the Lord hear me, even if the prayer must wait.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_63_1";
		break;
		
		case "Marisa_63_1":	
			dialog.text = "Captain, don't you think that putting off repentance is a sin in itself? One day it might be too late.";
			link.l1 = "Perhaps, but I'm afraid I have no time today. Faith is with me, and the Lord sees my repentance even without prayer.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_63_1";
		break;
		
		case "Marisa_64":	
			dialog.text = "Yes, thanks to you I can breathe freely again. May the Lord watch over you and your journey. Perhaps you would pray with me?";
			link.l1 = "I believe your prayers are strong enough as they are. What matters most is that you are now surrounded only by kindness.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_64_1";
		break;
		
		case "Marisa_64_1":	
			dialog.text = ""+pchar.name+", have you changed your mind after all? Shall we pray to our Creator?";
			link.l1 = "Unfortunately, Marisa, I have to go now, I have things to do.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_64_1";
		break;
		
		case "Marisa_65":	
			dialog.text = "I try to look only ahead. Now I have a future, and it's all thanks to you. Perhaps we should thank the Lord for this together?";
			link.l1 = "I think you'll do better than I would. The main thing is that your prayers bring you peace.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_65_1";
		break;
		
		case "Marisa_65_1":	
			dialog.text = ""+pchar.name+", perhaps I can persuade you to say at least one prayer?";
			link.l1 = "Forgive me, Marisa, but alas, I have no time right now. Pray for me as well.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_65_1";
		break;
		
		case "Marisa_Ne_Ta_Peshera":	
			dialog.text = "Captain, this isn't the place. The cave we need is by the Mosquitos Bay.";
			link.l1 = "...";
			link.l1.go = "Marisa_Ne_Ta_Peshera_1";
		break;
		
		case "Marisa_Ne_Ta_Peshera_1":	
			DialogExit();
			NextDiag.TempNode = "Marisa_31";
			DeleteQuestCondition("LFD_Ne_Ta_Peshera");
			
			sld = CharacterFromID("LFD_Marisa");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
		break;
		
	}
}
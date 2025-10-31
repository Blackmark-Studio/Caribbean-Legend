void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	bool bOk1, bOk2;
	
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
		
		case "OZ_Kuznets_1":
			//PlaySound("VOICE\Russian\Master_05.wav");
			dialog.text = "What did you want, "+GetAddress_Form(NPChar)+"? Sorry, but I’m not taking new orders. I just have... too much work...";
			link.l1 = "Is that so? I heard you recently lost something very valuable in a card game, is that true?";
			link.l1.go = "OZ_Kuznets_2";
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Kuznets_2":
			dialog.text = "Well, if you came to gloat, get in line – there are enough people who want to without you. But not one of them offered me help. My fate is hanging by a thread, and it depends entirely on Javier Castillo, while people only want to mock my misfortune.";
			link.l1 = "I’m not the kind who laughs at others’ misfortunes. Tell me how it happened. Maybe I can help you.";
			link.l1.go = "OZ_Kuznets_3";
			link.l2 = "Help? And why should anyone give it to you? I certainly won’t. You’re the smith of your own happiness... and of your misfortune as well. So stop pretending to be a victim – just accept the consequences of your actions, they are more than natural.";
			link.l2.go = "OZ_Kuznets_NoAgree";
		break;
		
		case "OZ_Kuznets_NoAgree":
			DialogExit();
			AddDialogExitQuestFunction("OZ_Kuznets_NoAgree");
		break;
		
		case "OZ_Kuznets_3":
			dialog.text = "That evening wasn’t supposed to be fatal. I just went into the tavern for a mug of rum after Admiral Eugenio de la Torre himself had placed a large order with me. But, quite tipsy, I sat down at a table to play cards. That’s when Javier set his sights on me\nAt first, luck was on my side – I even won a decent sum, but as soon as I started to believe in my luck, the situation changed drastically. Javier kept pouring rum into my mug, and I kept losing: first I spent all my cash, then the money set aside for materials, and then all my savings\nWhen I realized how much I had already lost, it was too late to back out. I was obsessed with one thought – to win it back at any cost. And then I wagered my book. That scoundrel Javier valued it at only five thousand pesos\nOf course, it’s worth much more, but I was so blinded by excitement that I agreed. And then... I think you already know the rest. I lost. You know, this has never happened to me before. I think that bastard drugged me with something.";
			link.l1 = "And how, may I ask, am I supposed to help you? You yourself sat at the table, you yourself wagered your property, and you yourself lost it all. Now you just don’t want to accept the consequences? And what’s so valuable about this book that you’re grieving over it?";
			link.l1.go = "OZ_Kuznets_4";
		break;
		
		case "OZ_Kuznets_4":
			dialog.text = "This book is the most valuable thing I had. It contains secrets passed down for centuries from master to apprentice. It is the heart of my forge, the soul of my craft. I’ve already come to terms with the loss, "+GetAddress_Form(NPChar)+", but how can I come to terms with losing the book? I offered Javier a ransom for it – five thousand pesos\nI was ready to go into debt just to get it back. But do you know what he said? He said he wanted a hundred thousand for it! A hundred, "+GetAddress_Form(NPChar)+"! I don’t have that kind of money. And he refuses to lower the price or take it in installments. I begged him... but he just laughed at me. I see you are "+GetSexPhrase("a brave man, a sailor... maybe even a captain. And your weapon isn’t hanging there just for show","not an ordinary woman, and surely able to find an approach to any man")+"\nI beg you, talk to Javier. Perhaps he will listen to you and agree to a delay in the payment of the debt. Without this book... my life has no meaning. In return, I will always be able to sell you quality materials at a good price when I get back on my feet, and maybe even craft something special for you, captain.";
			link.l1 = "Well, talking is no trouble. We’ll see what comes of it. But first allow me to introduce myself: my name is "+GetFullName(pchar)+", captain of my own ship.";
			link.l1.go = "OZ_Kuznets_5";
		break;
		
		case "OZ_Kuznets_5":
			dialog.text = ""+GetSexPhrase("And I am Sebastian Cordoba...","A woman – captain of her own ship? I’ve heard of such, but I’ve never met one in person or had a conversation.")+" Pleased to meet you, captain "+pchar.lastname+". And thank you. These days it’s easier to find those who mock others’ misfortunes than those who are willing to help. You know, if my book does return to me, I swear: I will never play games of chance again.";
			link.l1 = "There’s nothing to thank me for yet. First I’ll take care of my own business, and then, if I have time left, I’ll talk to Javier.";
			link.l1.go = "OZ_Kuznets_6";
		break;
		
		case "OZ_Kuznets_6":
			dialog.text = "I’m afraid you may be too late. Javier turned out to be much quicker than I thought\nHe has already found a buyer for the book – Etienne Renoir, a French master gunsmith. If the admiral finds out that through my fault such a treasure ended up in the hands of the French... I’ll lose my head. Prison would be an easy punishment.";
			link.l1 = "Hmm... All right. I’ll deal with your problem immediately.";
			link.l1.go = "exit";
			NextDiag.TempNode = "OZ_Kuznets_repeat";
			AddDialogExitQuestFunction("OZ_Kuznets_Agree");
		break;
		
		case "OZ_Kuznets_repeat":
			dialog.text = "Captain "+ pchar.lastname +"! Have you spoken with Javier? Any news?";
			link.l1 = "Not yet, but I’m heading to the tavern right now.";
			link.l1.go = "exit";
			NextDiag.TempNode = "OZ_Kuznets_repeat";
			if (CheckCharacterItem(PChar, "OZ_book"))
			{
				link.l1 = "I’ve spoken"+GetSexPhrase("","")+". And quite successfully. Javier has hastily departed this world, but before that he managed to return your book. Here you go.";
				link.l1.go = "OZ_Kuznets_11";
				DelLandQuestMark(npchar);
			}
		break;
		
		case "OZ_Kuznets_11":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+", you can’t even imagine what this means to me! Thanks to you, I’ll be able to fulfill all the orders, even the work for the admiral himself! I don’t have any money, unfortunately, but I still prepared a reward for you\nHere, take this cuirass – I made it for a certain don, but I’m sure he can wait a little. And I also have some materials that will come in handy if you decide to create something yourself.";
			link.l1 = "Thank you, "+npchar.name+", you are very generous!";
			link.l1.go = "OZ_Kuznets_12";
			TakeItemFromCharacter(pchar, "OZ_book");
		break;
		
		case "OZ_Kuznets_12":
			dialog.text = "And also, drop by if you need materials. My supplies come once a month, so there will always be something useful for you – and at a good price. I keep my promises.";
			link.l1 = "I definitely will! Well, "+npchar.name+", stay well. I’ll be going, I have things to do.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Kuznets_Nagrada");
			GiveItem2Character(PChar, "cirass3");
			AddItems(PChar, "jewelry13", 10);
			AddItems(PChar, "jewelry12", 5);
			AddItems(PChar, "jewelry10", 5);
			AddItems(PChar, "jewelry11", 2);
			AddQuestRecordInfo("Useful_Acquaintances", "7");
		break;
		
		case "OZ_Kuznets_Fail":
			dialog.text = "Captain "+ pchar.lastname +"! Have you spoken with Javier? Any news?";
			link.l1 = "You see... the book was in my hands. But... circumstances turned out so that it was sold.";
			link.l1.go = "OZ_Kuznets_Fail_2";
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Kuznets_Fail_2":
			dialog.text = "What?! You... you sold it?! My book?!";
			link.l1 = "The book you lost in a card game. It was sold to that Frenchman to whom Javier had promised it.";
			link.l1.go = "OZ_Kuznets_Fail_3";
		break;
		
		case "OZ_Kuznets_Fail_3":
			dialog.text = "But... now I’m finished. The book is with the French, the admiral’s order won’t be fulfilled... my life is ruined... I... I’m doomed!";
			link.l1 = "You’ve cornered yourself. I think this will serve you as a good lesson. Farewell.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Kuznets_Fail");
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
		break;
		
		case "OZ_Shuler_1":
			PlaySound("Voice\English\tavern\Igroki v Tavernah-01.wav"); 
			dialog.text = "Hey, "+GetSexPhrase("sailor","cutie")+", want to try your luck at cards? Have a seat, the stakes here are gentle... at least for beginners.";
			link.l1 = "I have a feeling you’re exactly the one I’m looking for. This is exactly how you lured Sebastian in before fleecing him to the bone, isn’t it? I’m here to get his book back.";
			link.l1.go = "OZ_Shuler_2";
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Shuler_2":
			dialog.text = "Well, great. Give me a hundred thousand – and you can take it. I’ve got no use for that book, I can’t even tell tongs from a hammer.";
			link.l1 = "I’ll give you five thousand – that’s the price you yourself set when you beat the blacksmith.";
			link.l1.go = "OZ_Shuler_3";
		break;
		
		case "OZ_Shuler_3":
			dialog.text = "Ha! Do you take me for a fool? I know perfectly well the real value of that book. A hundred thousand, and not a coin less. Or it goes to the French – they’ve got no problem with money.";
			link.l1 = "You think the authorities will turn a blind eye to you selling Spanish blueprints to the French? The admiral will be furious when he finds out.";
			link.l1.go = "OZ_Shuler_4";
		break;
		
		case "OZ_Shuler_4":
			dialog.text = "Oh, come on. The authorities don’t care about some book, they’ve got enough problems as it is. And the admiral? Yeah, he hates the French with all his heart, but I’m not sticking around to wait for him – with that kind of money I’ll be a welcome guest in any colony in the New World.";
			link.l1 = "Then let’s make a deal. You’ll get your money, but not right away. The blacksmith will pay the debt in installments, and the book goes back to him today under the pledge of my captain’s honor. Nothing changes for you – he’ll still pay, and you won’t lose a single peso.";
			link.l1.go = "OZ_Shuler_5";
		break;
		
		case "OZ_Shuler_5":
			dialog.text = "Looks like you’re not hearing me. I made it perfectly clear – I need the money right now. Not in a week, not in a month, or whenever the blacksmith scrapes it together, but right now. I’m planning to get off this miserable island as quickly as possible. So either the full amount is in my hands right now, or the book goes to the French, and you can pawn your captain’s honor to the admiral’s executioner.";
			if (sti(pchar.Money) >= 100000 && GetSummonSkillFromName(pchar, SKILL_SNEAK) >= 30)
			{
				link.l1 = "How about this: let’s play. My hundred thousand against the book. If you win, you’ll leave the island a rich man. If you lose – I take the book. Or do you only play with people who’ve never seen a deck before?";
				link.l1.go = "OZ_Shuler_6";
			}
			else
			{
				link.l1 = "...";
				link.l1.go = "OZ_Shuler_6_No_Money";
				AddDialogExitQuestFunction("OZ_GameCards_Fail");
			}
		break;
		
		case "OZ_Shuler_6_No_Money":
			DialogExit();
			Notification_Money(false, 100000, "peso");
			LAi_CharacterDisableDialog(npchar);
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) >= 30)
			{
			Notification_Skill(true, 30, SKILL_SNEAK);
			}
			else
			{
			Notification_Skill(false, 30, SKILL_SNEAK);
			}
		break;
		
		case "OZ_Shuler_6":
			dialog.text = "Ha! I don’t need to become rich – I’m already rich! Why would I risk something that’s going to bring me a pile of money?";
			link.l1 = "Well, well, Javier Castillo himself afraid to play? And here I thought"+GetSexPhrase(""," you")+", you were a seasoned player, not just a crook making money off drunk simpletons.";
			link.l1.go = "OZ_Shuler_7";
			Notification_Money(true, 100000, "peso");
			Notification_Skill(true, 30, SKILL_SNEAK);
		break;
		
		case "OZ_Shuler_7":
			dialog.text = "I’m not afraid, I just don’t see the point of sitting at the table when I already have everything I need.";
			link.l1 = "Oh, come on, I can see you shaking at the thought of playing against someone who’s not holding cards for the first time. Let me guess, you’re in such a hurry to get out of here because you’re ashamed? Everyone’s already figured out that you can’t beat anyone stronger than a drunk simpleton?";
			link.l1.go = "OZ_Shuler_8";
		break;
		
		case "OZ_Shuler_8":
			dialog.text = "How dare you?! I’ve beaten people who wouldn’t even sit at the same table with you! We’ve had pots big enough to buy a ship and one such arrogant captain for each player! Let’s play. Five thousand per card, a hundred thousand each, whoever runs out of money loses. Let’s see who beats who.";
			link.l1 = "Less talk, more action. Deal.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_GameCards");
		break;
		
		case "OZ_Shuler_Win_1":
			dialog.text = "Devil! That can’t be...";
			link.l1 = "What, not so much fun when someone else is winning?";
			link.l1.go = "OZ_Shuler_Win_2";
		break;
		
		case "OZ_Shuler_Win_2":
			dialog.text = "You’re a cheat! You think I didn’t see anything? No way I’ll let you swindle me! I’d sooner cut you to pieces.";
			link.l1 = "A cheat? Ha-ha! Looks like you just don’t know how to lose, friend. But if you’re in such a hurry to meet your end – I’ll help you with that. To arms!";
			link.l1.go = "exit";
			pchar.questTemp.OZ_Draka = true;
			AddDialogExitQuestFunction("OZ_GameCards_Duel");
		break;
		
		case "OZ_Shuler_Lose_1":
			dialog.text = "Ha! Well, "+GetSexPhrase("buddy","cutie")+", how does it feel to be fleeced"+GetSexPhrase("","") +"? They say arrogance is the second happiness, but not in your case.";
			link.l1 = "Don’t flatter yourself. You just got lucky.";
			link.l1.go = "OZ_Shuler_Lose_2";
		break;
		
		case "OZ_Shuler_Lose_2":
			dialog.text = "Losers always say that. Well, you played"+GetSexPhrase("","") +" – you lost"+GetSexPhrase("","") +", don’t take it personally. If you ever find another hundred thousand, you can try your luck again... But I doubt the result will change...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_GameCards_Lose");
			AddLandQuestMark(characterFromId("PortSpein_Tavern"), "questmarkmain");
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Felip_1":
			dialog.text = "Hello, "+GetAddress_Form(NPChar)+". To what do I owe your visit?";
			link.l1 = "Greetings. I am Captain "+GetFullName(pchar)+", and I want to talk to you about Javier Castillo.";
			link.l1.go = "OZ_Felip_2";
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Felip_2":
			dialog.text = "Hmm... If that rogue owes you money too, I’m afraid you’ll have to get in a long line. Javier has never been in a hurry to repay loans. But if he does get some money, he’ll pay me first – I’ve already made sure he has no other choice.";
			link.l1 = "Fortunately, I am not his creditor. How much does he owe you? And what measures have you taken exactly?";
			link.l1.go = "OZ_Felip_3";
		break;
		
		case "OZ_Felip_3":
			dialog.text = "The total amount of his debt is one hundred and fifty thousand pesos. He’s only paid ten thousand, apparently deciding that was enough. But I quickly made it clear to him that he was mistaken. My men got another twenty thousand out of him. The rest he must return within a week, and the deadline is almost here. Fortunately, I’ve heard he’ll soon be getting a good sum from selling some book.";
			link.l1 = "Do you really think he’s going to repay you? I don’t think you should seriously count on it. Javier doesn’t even hide that as soon as he gets the money, he’ll run away from here.";
			link.l1.go = "OZ_Felip_4";
		break;
		
		case "OZ_Felip_4":
			dialog.text = "I’m aware of that, Captain. Rest assured, I’ve already made sure he can’t escape without paying me.";
			link.l1 = "I see you’ve got the situation under control. However, as practice shows, a little extra precaution never hurts. You see, I’m something of a specialist"+GetSexPhrase("","ess")+" in debt collection. If you allow me to act on your behalf, I can get your money back.";
			link.l1.go = "OZ_Felip_5";
		break;
		
		case "OZ_Felip_5":
			dialog.text = "Alas, Captain, collecting this debt is already costing me too much, and I can’t afford to pay for your services as well...";
			link.l1 = ""+UpperFirst(GetAddress_Form(NPChar))+", you don’t need to worry about that. I have my own interest in this matter, so I’ll help you free of charge.";
			link.l1.go = "OZ_Felip_6";
		break;
		
		case "OZ_Felip_6":
			dialog.text = "May I ask, what exactly is your interest?";
			link.l1 = "Let’s just say, some of his tricks at the card table are something I can’t leave unpunished.";
			link.l1.go = "OZ_Felip_7";
		break;
		
		case "OZ_Felip_7":
			dialog.text = "Well, if it’s not going to cost me anything, I see no reason to refuse. The only thing, Captain – I ask you not to go too far. If that scoundrel goes to meet his maker before he repays the debt, it will be of no use to me.";
			link.l1 = "Don’t worry, Felipe, I’ll act carefully.";
			link.l1.go = "exit";
			NextDiag.TempNode = "OZ_Felip_again";
			AddDialogExitQuestFunction("OZ_Felip_2");
			pchar.questTemp.OZ_Dolg = true;
		break;
		
		case "OZ_Felip_again":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+"! Could it be that you’ve handled it so quickly?";
			link.l1 = "Unfortunately, not yet. But I’m working on it.";
			link.l1.go = "exit";
			NextDiag.TempNode = "OZ_Felip_again";
		break;
		
		case "OZ_Shuler_11":
			if (CheckAttribute(npchar, "quest.OZ_Shuler_Lose"))
			{
				dialog.text = "Ah, "+GetSexPhrase("captain","cutie")+" upstart! You again? What, want to lose a couple more thousand?";
			}
			else
			{
				dialog.text = "You again? I told you clearly: money on the table – or get lost.";
			}
			link.l1 = "Change your tone, Javier. And get your purse out – I’m not here for nothing. You haven’t forgotten about your debt to Felipe Alarcon, have you? I’m representing his interests now. So choose: either you pay the debt right now, or I’ll have to look for the money in your pockets after you’ve gone to meet your maker.";
			link.l1.go = "OZ_Shuler_12";
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Shuler_12":
			dialog.text = "Damn you! I’ve got a deal going on, can’t you see? Come back in a couple of hours – then we’ll talk.";
			link.l1 = "Looks like you didn’t hear me. I made it perfectly clear: I need the money right now. Not in a week, not in a month, or whenever you scrape it together, but right now. One hundred and twenty thousand pesos, not a coin less. I’m willing to take the book as five thousand.";
			link.l1.go = "OZ_Shuler_13";
		break;
		
		case "OZ_Shuler_13":
			dialog.text = ""+GetSexPhrase("You filthy bastard","You wretch")+"! If you think you can deal with me so easily – that’s the biggest mistake of your worthless life.";
			link.l1 = "We’ll see.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Shuler_Bitva");
		break;
		
		case "OZ_Frantsuz_1":
			//PlaySound("VOICE\Russian\tra_quest_1.wav");
			if (CheckAttribute(pchar, "questTemp.OZ_Draka"))
			{
				dialog.text = "What a sight... I must admit, "+GetAddress_Form(NPChar)+", you’ve given me great pleasure. You wield a blade superbly. Allow me to introduce myself – "+GetFullName(npchar)+". And this unfortunate fellow, if I’m not mistaken, is Javier Castillo?";
				link.l1 = "Exactly, that’s him. And I am Captain "+GetFullName(pchar)+".";
				link.l1.go = "OZ_Frantsuz_1_1";
			}
			else
			{
				dialog.text = "What a sight... I must admit, "+GetAddress_Form(NPChar)+", you’ve given me great pleasure. You wield a blade superbly. Funny how circumstances sometimes turn out – the book I traveled so far for has changed owners in the most unexpected way. But I do hope I won’t be leaving here empty-handed.";
				link.l1 = "Hmm... And how much do you value this book at?";
				link.l1.go = "OZ_Frantsuz_2";
			}
		break;
		
		case "OZ_Frantsuz_1_1":
			dialog.text = "You see, Captain, I have traveled quite a distance for one particular book... And it seems it is now in your hands. I sincerely hope we can come to an agreement – I would hate to leave this place empty-handed.";
			link.l1 = "Hmm... And how much do you value this book at?";
			link.l1.go = "OZ_Frantsuz_2";
		break;
		
		case "OZ_Frantsuz_2":
			dialog.text = "Oh, "+GetAddress_Form(NPChar)+", I know the price of truly rare things. Eighty thousand pesos. A more than generous sum, and believe me, you are unlikely to receive such an offer again.";
			link.l1 = "Well, the book is indeed valuable, and I admit I asked"+GetSexPhrase("","") +" purely out of curiosity. I do not intend to trade on a man’s fate. I’m afraid, monsieur, there will be no deal – this book must return to its rightful owner.";
			link.l1.go = "OZ_Frantsuz_3";
			link.l2 = "A laughable sum. This book contains the secrets of the finest masters of the blacksmith’s craft. One hundred and fifty thousand pesos – either you agree, or it goes back to its owner. No bargaining.";
			link.l2.go = "OZ_Frantsuz_4";
		break;
		
		case "OZ_Frantsuz_3":
			dialog.text = "Please, don’t be so quick to refuse. I have traveled a long way for it. I am prepared to offer you one hundred thousand, purely as a sign of respect for the skill with which you dealt with that man.";
			link.l1 = "I’ve said all I need to say. Now, if you’ll excuse me, I must go.";
			link.l1.go = "OZ_Frantsuz_4_1";
		break;
		
		case "OZ_Frantsuz_4_1":
			DialogExit();
			AddDialogExitQuestFunction("OZ_Frantsuz_1");
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, SPAIN, 10);
		break;
		
		case "OZ_Frantsuz_4":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+", I appreciate your confidence, but one hundred and fifty thousand – that’s not a price, that’s absurd. Let’s not turn this deal into a farce. One hundred thousand pesos is a reasonable amount, agree to it – no one will give more for this book.";
			link.l1 = "It seems we haven’t found common ground. Well, I see no reason to continue this conversation. Farewell, monsieur.";
			link.l1.go = "OZ_Frantsuz_5";
		break;
		
		case "OZ_Frantsuz_5":
			dialog.text = "Wait! All right, you’ve won. One hundred and fifty thousand. Do we have a deal?";
			link.l1 = "Glad you made the right choice. The book is yours. I think with it you’ll become the finest master in the Caribbean.";
			link.l1.go = "OZ_Frantsuz_6";
			TakeItemFromCharacter(pchar, "OZ_book");
			AddMoneyToCharacter(pchar, 150000);
			ChangeCharacterNationReputation(pchar, FRANCE, 10);
			ChangeCharacterNationReputation(pchar, SPAIN, -10);
			ChangeCharacterReputation(pchar, -5);
		break;
		
		case "OZ_Frantsuz_6":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+", even without this book I was second to none. But I must admit, it’s pleasant to acquire such a rare trophy. And now, please excuse me – I can’t wait to see if it truly lives up to the glowing words I’ve heard about it.";
			link.l1 = "Well then, I won’t keep you. Farewell.";
			link.l1.go = "OZ_Frantsuz_7";
		break;
		
		case "OZ_Frantsuz_7":
			DialogExit();
			AddDialogExitQuestFunction("OZ_Frantsuz_2");
		break;
		
		case "OZ_Bandit_1":
			if (pchar.sex == "man")
			{
				dialog.text = "Well, well, what’s this trash? Thought you’d clean out our chest and run off? Big mistake, buddy. Now we’ll stuff you into that chest ourselves and nail the lid shut!";
			}
			else
			{
				dialog.text = "Well, well... And who do we have here? Lost your way, darling? Thought you’d clean out the chest and quietly sneak away? Big mistake, sweetheart. Now we’ll search you properly – and see what you’ve got in your pockets... and elsewhere.";
			}
			link.l1 = "Too many words for pathetic worms like you. Draw your steel, let’s see what you’re really worth.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Grot_4");
		break;
		
		case "OZ_Felip_11":
			dialog.text = "Captain! I’ve already been informed that Javier went to meet his maker thanks to you. And I asked you not to kill him too soon! I hope you’re here to return my money?";
			if (sti(pchar.Money) >= 100000)
			{
				link.l1 = "Exactly. I managed to find his stash, which held one hundred thousand pesos. That’s all the money he had.";
				link.l1.go = "OZ_Felip_12";
			}
			link.l2 = "Yes, I had to kill him. But he attacked me first, and I had to defend myself. His pockets were empty – not a single coin. Unfortunately, I wasn’t able to recover the debt.";
			link.l2.go = "OZ_Felip_14";
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.OZ_Dolg");
		break;
		
		case "OZ_Felip_12":
			dialog.text = "One hundred thousand... Of course, that’s not the full amount, but knowing Javier, I doubt anyone could squeeze more out of him. Well then, thank you, Captain. It seems I hired the wrong people. You truly are a master of your trade.";
			link.l1 = "It wasn’t difficult. On that note, I’m afraid I must take my leave"+GetSexPhrase("","")+". Business awaits.";
			link.l1.go = "OZ_Felip_13";
			AddMoneyToCharacter(pchar, -100000);
		break;
		
		case "OZ_Felip_13":
			dialog.text = "Farewell, Captain.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Felip_good");
		break;
		
		case "OZ_Felip_14":
			dialog.text = "You "+GetSexPhrase("scoundrel","wretch")+"! Lying to my face while looking me in the eye?! You won’t get away with this!";
			link.l1 = "Argh...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Felip_bad");
		break;
		
		case "OZ_Kuznets_Tovar":
			//PlaySound("VOICE\Russian\Master_02.wav");
			dialog.text = "Hello, "+pchar.name+"! Would you like to purchase materials or goods?";
			link.l1 = ""+TimeGreeting()+". Let’s see what you have.";
			link.l1.go = "OZ_Kuznets_Tovar_2";
			link.l2 = "And hello to you, "+npchar.name+"! Thank you for the offer, but I just wanted"+GetSexPhrase("","") +" to say hello.";
			link.l2.go = "exit";
			NextDiag.TempNode = "OZ_Kuznets_Tovar_repeat";
			SetFunctionTimerCondition("OZ_Kuznets_Reset", 0, 0, 1, false);
			if (!CheckAttribute(npchar, "quest.OZ_Kuznets_tovar")) 
			{
				SetFunctionTimerCondition("OZ_Kuznets_Reset_2", 0, 0, 30, false);
				npchar.quest.OZ_Kuznets_tovar = true;
			}
		break;
		
		case "OZ_Kuznets_Tovar_repeat":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+", have you decided to purchase something after all?";
			link.l1 = "Exactly. Show me what you have today.";
			link.l1.go = "OZ_Kuznets_Tovar_2";
			link.l2 = "Sorry, I’m leaving already.";
			link.l2.go = "exit";
			NextDiag.TempNode = "OZ_Kuznets_Tovar_repeat";
		break;
		
		case "OZ_Kuznets_Tovar_2":
			DialogExit();
			LaunchItemsTrade(NPChar, 0);
			NextDiag.CurrentNode = "OZ_Kuznets_Tovar_repeat";
		break;
		
	}
}
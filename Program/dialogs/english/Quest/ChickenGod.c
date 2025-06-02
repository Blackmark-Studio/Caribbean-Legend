int questShips[50];
int questShipsNum = 0;

extern void InitGunExt(string id,			
				string sAttr,       
				string sBullet,     
				string sGunPowder,  
				float  DmgMin_NC,   
				float  DmgMax_NC,   
				float  DmgMin_C,    
				float  DmgMax_C,    
				float  EnergyP_NC,  
				float  EnergyP_C,   
				bool   Stun_NC,     
				bool   Stun_C,      
				bool   MultiDamage, 
				int    MisFire,     
				bool   SelfDamage,  
				bool   Explosion,   
				float  Accuracy,    
				int    ChargeSpeed, 
				bool   isDefault );

void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp, attr, companion;
	ref chref;
	int iTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	string node = Dialog.CurrentNode;
	if(HasSubStr(node, "joruba_p3_ship_")) {
		iTemp = findsubstr(node, "joruba_p3_ship_", 0);
	 	companion = strcut(node, iTemp + strlen("joruba_p3_ship_"), strlen(node) - 1);
 	    Dialog.CurrentNode = "joruba_p3";
	}
	
	if(HasSubStr(node, "joruba_p4_off_")) {
		iTemp = findsubstr(node, "joruba_p4_off_", 0);
	 	pchar.questTemp.ChickenGod.Sacrifice = strcut(node, iTemp + strlen("joruba_p4_off_"), strlen(node) - 1);
 	    Dialog.CurrentNode = "joruba_p4_off";
	}

	if(HasSubStr(node, "joruba_o6_off_")) {
		iTemp = findsubstr(node, "joruba_o6_off_", 0);
	 	pchar.questTemp.ChickenGod.Sacrifice = strcut(node, iTemp + strlen("joruba_o6_off_"), strlen(node) - 1);
 	    Dialog.CurrentNode = "joruba_o6_off";
	}

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "First time":
			dialog.text = "You're not supposed to see this.";
			link.l1 = "Time to file a bug report.";
			link.l1.go = "exit";
		break;
		
        case "native":
			dialog.text = "Uh-oh! Ta'kahi, young man. I don't mean to be rude, but how did you get in here? I strongly advised Madame to close the establishment for the duration of my stay.";
			link.l1 = "Uh-oh indeed. How did they let you in? Why hasn't this brothel already been burned down by angry God-fearing people?";
			link.l1.go = "native_1";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Panama");
		break;
		
        case "native_1":
			dialog.text = "Golden doubloons open all paths and make white people happier. Wouldn't you know?";
			if (HasSubStr(pchar.model, "Sharle")) {
				dialog.text = dialog.text + " I can sense the almost weathered smell of Versailles, where you were let in with such a squeak.";
			}
			link.l1 = "Don't talk to me like that, red face. It's true that I'm new here, though I don't know how you got wind of it. I could shoot you right where you stand and get any girl for the night to make up for the inconvenience.";
			link.l1.go = "native_var1";
			link.l2 = "I don't know who told you that nonsense, but you talk rather smoothly, I'll give you that. It's the first time I've seen such an educated native.";
			if (HasSubStr(pchar.model, "Sharle")) {
				link.l2 = link.l2 + " Versailles, my ass!";
			}
			link.l2.go = "native_var2";
		break;
		
        case "native_var1":
			dialog.text = "No, Captain, you don't know anything. I'm perfectly safe here... for now. However, since we've gotten so familiar so quickly, let's try again. Drink?";
			link.l1 = "I can do that, you definitely have piqued my interest.";
			link.l1.go = "native_play";
		break;
		
        case "native_var2":
			dialog.text = "Bravo! I see we're already on a first-name basis and exchanging barbs. Now I suggest we drink to peace and talk business.";
			link.l1 = "I can do that, you definitely have piqued my interest.";
			link.l1.go = "native_play";
		break;
		
        case "native_play":
			dialog.text = "Considering the purpose of the location, your comment, Captain, quite worries me! I've been stuck here for almost a month now. Tried everything I can think of, and I'm ready to climb the wall out of boredom and pointlessness.";
			link.l1 = "Leave then. Visit a church for a change... which they won't let you in.";
			link.l1.go = "native_play_1";
		break;
		
        case "native_play_1":
			dialog.text = "It's not that simple as I'm obligated to spend another twenty-four hours in this brothel, according to my... contract.";
			link.l1 = "Sounds awful of course, but you'll get no sympathy from me. An exclusive brothel rental for a month is a dream come true!";
			link.l1.go = "native_play_2";
		break;
		
        case "native_play_2":
			dialog.text = "Fear your desires, Captain. I don't know how you got here, because I was supposed to spend this month alone. Alone with squaw and wine, but I could only do wine by the third day or so. And today was the day when I got sick of it as well.";
			link.l1 = "And what do you want me to do? Share a load of girls and wine with you?";
			link.l1.go = "native_play_3";
		break;
		
        case "native_play_3":
			dialog.text = "Maybe, but I suggest we gamble first! A thousand silver per card! My name is Agueybana by the way.";
			link.l1 = "Mine is " + GetFullName(pchar) + ". Sure, let's play.";
			link.l1.go = "native_accept";
			link.l2 = "Mine is " + GetFullName(pchar) + ". A thousand pesos? Not bad. I'll give it some thought, but no promises.";
			link.l2.go = "native_decline";
		break;
		
        case "native_play_again":
			dialog.text = "Changed your mind, captain? Shall we?";
			link.l1 = "Sure, why the hell not.";
			link.l1.go = "native_accept";
			link.l2 = "Not yet.";
			link.l2.go = "native_decline";
		break;
		
        case "native_decline":
			DialogExit();
			
			NextDiag.CurrentNode = "native_play_again";
		break;
		
        case "native_accept":
			DialogExit();
			
			AddDialogExitQuestFunction("ChickenGod_Game1");
		break;
		
        case "native_cards_loss":
			dialog.text = "Thanks for the game, captain. I thought it would make me feel better, but it didn't. Please leave me alone - I'll manage for another day on my own somehow. Damn that bastard!";
			link.l1 = "That's it? Admittedly, my disappointment is greater than the bitterness of losing a whole lot of money.";
			link.l1.go = "native_cards_loss_1";
		break;
		
        case "native_cards_loss_1":
			dialog.text = "You weren't even supposed to be here, captain. But if you yearn to find out what it was all about... look for an ancient temple on the continent. And bring lots of tuunich kaane'. Here, take one.";
			link.l1 = "An adder stone? A stone with a hole definitely fits the location. Thanks, Agueybana";
			link.l1.go = "native_cards_loss_2";
		break;
		
        case "native_cards_loss_2":
			dialog.text = "Farewell, captain.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_Game1LossGoAway");
		break;
		
        case "native_cards_win":
			dialog.text = "Uh-oh! Thank you, captain! Shame about the money, but at least I got a taste of life again!";
			link.l1 = "Yeah, that's the first time I've ever seen anyone get that excited about a route like this. Where'd you get all that money, by the way?";
			link.l1.go = "native_cards_win_1";
		break;
		
        case "native_cards_win_1":
			dialog.text = "A rude question you would never ask of your equal, captain! But the night is still young, and I have a good deal of coin left. How about a rematch?";
			link.l1 = "Why the hell not? Let's do another one!";
			link.l1.go = "native_cards_win_2";
		break;
		
        case "native_cards_win_2":
			dialog.text = "I suggest this time we play dice and raise the stakes a bit. I also have a story to tell you, so please rent a room upstairs for both of us. Too many ears here! I'd appreciate it if you go to Madame and pay for the room. My credit, unfortunately, does not apply to you.";
			link.l1 = "Rent a room? For two? Here? Fuck you, Agueybana! I am out of here!";
			link.l1.go = "native_cards_rematch_decline";
			link.l2 = "Oh, what the hell. This story will end either as a good anecdote or a very expensive bloodbath. My sword stays with me, so no funny business, ha-ha! Wait here, I will sort this out.";
			link.l2.go = "native_cards_rematch_accept";
		break;
		
        case "native_cards_rematch_decline":
			DialogExit();
			
			AddDialogExitQuestFunction("ChickenGod_Game1WinNoRematch");
		break;
		
        case "native_cards_rematch_accept":
			DialogExit();
			
			AddDialogExitQuestFunction("ChickenGod_Game1WinRematch");
		break;
		
        case "native_dice":
			dialog.text = "So?";
			link.l1 = "I sincerely hope you called me here for booze and gamble only.";
			link.l1.go = "native_dice_1";
		break;
		
        case "native_dice_1":
			dialog.text = "Don't worry, captain, I'm not interested in such nonsense! Although, if you'd shown up here on the first day... ha ha! Shall we begin?";
			link.l1 = "Fortes fortuna adiuvat!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_Game2");
		break;
		
        case "native_dice_win":
			dialog.text = "Uh-oh! That feels good! Congratulations on your victory, Captain.";
			link.l1 = "Don't overdo it. Time for you to enlighten me as to what the hell is going on here?";
			link.l1.go = "native_dice_story";
			link.l2 = "You're weird, Agueybana. Now, if I don't leave this place at once, my reputation as a nobleman and a man will be irreparably damaged. Give me my silver and let's part our ways.";
			link.l2.go = "native_dice_win_not_story";
		break;
		
        case "native_dice_loss":
			dialog.text = "What a shame, I was hoping to end the day on a different note...";
			link.l1 = "This is the first time I've ever seen a man so upset about winning this plebeian game. Can you at least enlighten me now as to what the hell is going on here?!";
			link.l1.go = "native_dice_story";
			link.l2 = "Fuck you, Agueybana! I had enough of this!";
			link.l2.go = "native_dice_loss_not_story";
		break;
		
        case "native_dice_story":
			dialog.text = "As much as I can, captain. I am not sure that I am allowed to, but still, you've brightened my last few days... In this brothel, I mean.";
			link.l1 = "And what was this about?";
			link.l1.go = "native_dice_story_1";
		break;
		
        case "native_dice_story_1":
			dialog.text = "Never mind... Listen here, white man! I am the great chief of the Taino people, Agueybana. Sometimes I dream that I was born a hundred years earlier and drove the Spanish invaders off my islands! But instead I sold three thousand of my tribesmen to the mines for ten doubloons a head.";
			link.l1 = "A worthy biography. I am having a sudden urge to shoot you, Agueybana, and leave you to rot in this sour wine-scented dump.";
			link.l1.go = "native_dice_story_2";
		break;
		
        case "native_dice_story_2":
			dialog.text = "Whatever, captain. All I ever wanted was to be like you.";
			link.l1 = "Like me?";
			link.l1.go = "native_dice_story_3";
		break;
		
        case "native_dice_story_3":
			dialog.text = "I've seen your ships - marvels of human genius - and I've wanted one for myself. I have seen your women in tight corsets, and dreamed of taking one off my own. I have watched even the lousiest of your commandants wield power beyond the dreams of any of our leaders. Heard stories about Europe and the huge stone houses where people live instead of surviving. And I've had it all! Moreover, I've even been to Europe and all that in the past year!";
			link.l1 = "You've had too much wine, chief. The only tickets to Europe for you would be chains, to the delight of the Vatican and the street performers. What you're talking about is simply impossible in the world we live in.";
			link.l1.go = "native_dice_story_4";
		break;
		
        case "native_dice_story_4":
			dialog.text = "That is the world we live in, captain. It has already been explained to me that our world is wrong, imaginary, and anything is possible.";
			link.l1 = "And who was the smartass who told you that? Apparently they don't just let you into brothels, but asylums too!";
			link.l1.go = "native_dice_story_5";
		break;
		
        case "native_dice_story_5":
			dialog.text = "Now we're getting to the point of my story. You know how things work here, don't you? The Spanish and English pay for our prisoners of war with guns, tools and gunpowder. I paid for my tribesmen in your money. Why do you think that is?";
			link.l1 = "I feel like you're about to enlighten me.";
			link.l1.go = "native_dice_story_6";
		break;
		
        case "native_dice_story_6":
			dialog.text = "Only the gods can fulfill our deepest and most shameful desires. If you can't live the life you want, then ask them to interfere with fate. Only them can fulfill our deepest and most shameful desires. This is the way. But here's the trouble: almost all of our gods are already dead, and even if they weren't they were never interested in gold anyway. Luckily nature abhors a vacuum, and a new god has appeared in one of the old pyramids. He doesn't care who you are: local or European, villain or hero - just pay and you'll get what you asked! All the tribes know that, and some of your people too. I've paid the price in gold and lived like one of you. It'll be a year tomorrow.";
			link.l1 = "What god? To Europe and back in a year? And the high point of your trip was some lousy brothel in the Caribbean? Oh, what the hell. Sounds like a drunkard's tale, and I'll buy it as such. Let's have a drink and get on with your story.";
			link.l1.go = "native_dice_story_7";
		break;
		
        case "native_dice_story_7":
			dialog.text = "Everything I've told you is the truth. There's nothing more to tell.";
			link.l1 = "You haven't lived in our world long enough, Agueybana. Every booze-inspired fable, especially one told drunkenly in a brothel, must end with a moral. We should definitely philosophize before finishing our salon properly.";
			link.l1.go = "native_dice_story_8";
		break;
		
        case "native_dice_story_8":
			dialog.text = "How do they usually end?";
			link.l1 = "You don't know? Depends on the participant's gender of course! Fistfight the men, take women to bed. Sometimes fashion dictates the other way around though. So what's the moral of your fable? Money doesn't buy happiness? Boring!";
			link.l1.go = "native_dice_story_9";
		break;
		
        case "native_dice_story_9":
			dialog.text = "That's not the moral of my fable, as you put it. But since you started it, I feel the need to say that I am not in agreement with your point. On the contrary, I believe that money buys happiness and makes people better.";
			link.l1 = "Nonsense! You seem to be contradicting yourself now. You amassed a significant fortune through the trade of your own people. Do you recall the total amount you profited from? Nearly thirty thousand gold coins? Take a moment to reflect, but it's clear to me that money didn't buy you happiness. It did buy you this nice suite though.";
			link.l1.go = "native_dice_story_10";
		break;
		
        case "native_dice_story_10":
			dialog.text = "Fine, I will adjust my initial point: money makes life and people better.";
			link.l1 = "That's better, but what makes you think it makes people better? So you're a paragon of virtue now? And what about those who don't have much money? Are we going to label them as bad people?";
			link.l1.go = "native_dice_story_11";
		break;
		
        case "native_dice_story_11":
			dialog.text = "You know, captain, I truly appreciate this conversation. Let me adjust again: money makes life and people better but only those who already possess a spark of virtue.";
			link.l1 = "Hear, hear! So, no spark for you, eh?";
			link.l1.go = "native_dice_story_12";
		break;
		
        case "native_dice_story_12":
			dialog.text = "No. I was the chief of my people and, unlike money, power definitely corrupts men. You know what, captain? I look at you know and I realize that you will face the same dilemma some day.";
			link.l1 = "Has your god also given you the gift of providence? So you should go to Santiago, I've heard they're particularly interested in all kinds of mediums and fortune tellers.";
			link.l1.go = "native_dice_story_13";
		break;
		
        case "native_dice_story_13":
			dialog.text = "Let's finish our... ahem, salon without fistfighting and bedding please. I failed to make up a moral for my story, so I'd like to propose a toast instead.";
			link.l1 = "You're completely lost, chief. But in one thing, you're right. Let’s just have a drink!";
			link.l1.go = "native_dice_story_14";
		break;
		
        case "native_dice_story_14":
			dialog.text = "Here's to what we want always matches what we need. Thank you, Captain, that's a fitting end to... our evening. If you wish to test the truth of my fable one day, go to the continent and find an ancient temple there. Bring with you hundred and thirteen tuunich kaane'. I have ninety-nine left - take them and farewell!";
			link.l1 = "A pile of stones with holes? Fits the location alright. Thank you for the evening, Agueybana. See you again?";
			link.l1.go = "native_dice_story_15";
		break;
		
        case "native_dice_story_15":
			dialog.text = "No, you won't. Bye, captain.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_BuyAmulets");
		break;
		
        case "native_dice_win_not_story":
			dialog.text = "I understand, captain. For better or worse, I'll give you a tip on the treasure. Afterall you've brightened my last days... In this brothel, I mean. Search for an ancient temple in the great land and bring a pile of tuunich kaane' to. Here, take one.";
			link.l1 = "An adder stone? How charming and a stone with a hole definitely fits the location. I had enough of your treatment!";
			link.l1.go = "native_dice_not_story";
		break;
		
        case "native_dice_loss_not_story":
			dialog.text = "I get that you are upset, captain. For better or worse, I'll give you a tip on the treasure. Afterall you've brightened my last days... In this brothel, I mean. Search for an ancient temple in the great land and bring a pile of tuunich kaane' to. Here, take one.";
			link.l1 = "An adder stone? How charming and a stone with a hole definitely fits the location. I had enough of your treatment!";
			link.l1.go = "native_dice_not_story";
		break;
		
        case "native_dice_not_story":
			dialog.text = "Bye, captain.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_NotBuyAmulets");
		break;
		
		case "joruba":
			dialog.text = "Another one? Oh fucks sake, I'm so sick of all of you!";
			link.l1 = "A-a-ah! Be gone!";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "joruba_1";
			AddDialogExitQuestFunction("ChickenGod_ShootJoruba");
		break;
		
		case "joruba_1":
			dialog.text = "Eh? Yes, right. Bow to me, mortal! Behold the power of my pyramid!";
			link.l1 = "(scream desperately)";
			link.l1.go = "joruba_2";
			link.l2 = "(kill the monster)";
			link.l2.go = "joruba_3";
		break;
		
		case "joruba_2":
			dialog.text = "That's right. Welcome to my humble factoria, captain.";
			link.l1 = "W-what are you?";
			link.l1.go = "joruba_4";
		break;
		
		case "joruba_3":
			DialogExit();
			
			NextDiag.CurrentNode = "joruba_3_next";
			AddDialogExitQuestFunction("ChickenGod_ShootJoruba");
		break;
		
		case "joruba_3_next":
			dialog.text = "I commend you for your persistence. What's your next move, captain? How do you feel about doing some trade?";
			link.l1 = "W-what are you?";
			link.l1.go = "joruba_4";
		break;
		
		case "joruba_4":
			dialog.text = "It doesn't matter what I am, it's the function I perform that matters. At this point of time, I'm conducting trade deals with the inhabitants of this rathole for mutual benefit.";
			link.l1 = "The rathole? You mean this temple?";
			link.l1.go = "joruba_6";
			
			AddDialogExitQuestFunction("ChickenGod_JorubaToNormal");
		break;
		
		case "joruba_6":
			dialog.text = "Your first and your final warning, captain! However this pyramid is indeed kind of cramped, obviously I've outgrown it.";
			link.l1 = "You said something about trading. What kind of trade are you talking about?";
			if (CheckAttribute(pchar, "questTemp.ChickenGod.SawJoruba")) {
				link.l1.go = "joruba_7A";
			} else {
				link.l1.go = "joruba_7";
			}
		break;
		
		case "joruba_7":
			dialog.text = "I give what people need most.";
			link.l1 = "You grant wishes? Like a genie from a fairy tale? Dear Lord, what's going on here?!";
			link.l1.go = "joruba_7_1";
		break;
		
		case "joruba_7_1":
			dialog.text = "Don't be absurd! I only help people to get what they came to this world for in the most quick and pleasant manner.";
			link.l1 = "Are you a shaman or something?";
			link.l1.go = "joruba_8";
		break;
		
		case "joruba_7A":
			dialog.text = "Well, you did meet Agueybana, that should give you some ideas.";
			link.l1 = "That poor, lost and drunken Indian was your handiwork?";
			link.l1.go = "joruba_7A_1";
		break;
		
		case "joruba_7A_1":
			dialog.text = "It wasn't me who sold his tribe for a couple of thousand pounds of gold, it wasn't me who poured barrels of liquor down his throat, and I certainly did not force him to pick every disease, known and unknown, from hundreds of whores. He asked me to turn him into a white aristocrat, so I did. As his destiny commanded me.";
			link.l1 = "You grant wishes? Like a genie from a fairy tale? Dear Lord, what's going on here?!";
			link.l1.go = "joruba_7A_2";
		break;
		
		case "joruba_7A_2":
			dialog.text = "Don't be absurd! I only help people to get what they came to this world for in the most quick and pleasant manner. Agueybana was supposed to save his people from the yoke of the European invaders, but instead he drooled over the commandant's daughter's corset too much and decided to pawn his own\nFrom then on, the only meaning left in his life was to realize the depth of his mistake and start over soon. A year in Europe, cirrhosis and time you two spent in a brothel must have helped. But I'll admit, he had a great vacation, ha ha!";
			link.l1 = "Cirrho what? Are you a shaman or something?";
			link.l1.go = "joruba_8";
		break;
		
		case "joruba_8":
			dialog.text = "Or something. You'll like my offer though. And, for a change, I'll be genuinely happy to help.";
			link.l1 = "Right. How much?";
			link.l1.go = "joruba_9A";
			link.l2 = "Why? Am I special?";
			link.l2.go = "joruba_9B";
		break;
		
		case "joruba_9A":
			dialog.text = "Not too bad, captain. Either you're smart or you're dumb as a donkey, but your odds just went up a little. The price won't be an issue.";
			link.l1 = "Do you need to kill someone? I don't do that.";
			link.l1.go = "joruba_10";
		break;
		
		case "joruba_9B":
			dialog.text = "Because your purpose in this life is to make holes in a good friend of mine, ha ha!";
			link.l1 = "Do you need to kill someone? I don't do that.";
			link.l1.go = "joruba_10";
		break;
		
		case "joruba_10":
			dialog.text = "First, you do. Second, we will conduct four major transactions, and four more smaller ones. Each will make you much stronger and increase your chances in this cruel and strange world. If you complete every deal, I guarantee that one day you'll be able to go out and fight gods on equal terms, not to mention ordinary mortals.";
			link.l1 = "Sounds like fun. Tell me about it.";
			link.l1.go = "joruba_11";
		break;
		
		case "joruba_11":
			dialog.text = "Smart choice! Usually my speeches lead to people being carried off to Blueweld with a suspected heart attack, but you're holding up pretty well. Here's the task list: little errands of a bartering nature that I expect you to do. No deadlines, hehe.";
			link.l1 = "Curious. I'll read the list later. Anything else?";
			link.l1.go = "joruba_12";
		break;
		
		case "joruba_12":
			dialog.text = "Yep, the first major transaction. Two thousand doubloons is the price.";
			link.l1 = "Maybe I'll bite... But that's a lot of money! Why do you need that much? Can I pay in pesos?";
			link.l1.go = "joruba_13";
			link.l2 = "Are you crazy? I can buy a frigate with that money!";
			link.l2.go = "joruba_insult";
		break;
		
		case "joruba_13":
			dialog.text = "The pyramid is in need of repair - the masonry sometimes falls on the heads of customers and that's bad for business. My men patch it up every day, but our organization needs an urgent injection of money from the outside to fix the situation for good. As for pesos - I don't fancy them much, since their exchange rate is rather volatile.";
			link.l1 = "You are being just unfair to honest pesos... Wait a minute, you're not alone here?";
			link.l1.go = "joruba_14";
		break;
		
		case "joruba_14":
			dialog.text = "Nope, I'm the facade of a serious organization. So, you in?";
			link.l1 = "I'll think about it, but first, I'd like to know what I'm getting for such a hefty sum.";
			link.l1.go = "joruba_15";
		break;
		
		case "joruba_15":
			dialog.text = "Why ruin the surprise? Besides, just treat that money as a tax. Your most valuable acquisition will be unlocking next deals. Rewards will be godly. Unique too mind you, as you won't find them anywhere else!";
			link.l1 = "Fine. What's your name again?";
			link.l1.go = "joruba_16";
		break;
		
		case "joruba_16":
			dialog.text = "Aruba the Magnificent. One last thing, " + pchar.name + ", entry to the pyramid is allowed only once a day. Don't delay other clients and don't bother me for nothing.";
			link.l1 = "I don't see the queue lining up... Farewell, your majesty.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "joruba_wait";
			AddDialogExitQuestFunction("ChickenGod_GiveFirstTask");
		break;
		
		case "joruba_wait":
			dialog.text = "Ahoy, captain. What do you have for me?";
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p1") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p1.Completed") && PCharDublonsTotal() >= 2000) {
				link.p1 = "Here are your doubloons. It's hard enough to carry that damned metal around... but it is even harder to part with it!";
				link.p1.go = "joruba_p1";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p2") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p2.Completed") && GetCharacterItem(pchar, "cannabis7") >= 15) {
				link.p2 = "I kept my end of the bargain. Here's your herb, Aruba.";
				link.p2.go = "joruba_p2";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p3") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p3.Completed") && ChickenGod_FindQuestShips()) {
				for (i = 0; i < questShipsNum; i++) {
					sTemp = "p3_" + (i + 1);
				
					chref = GetCharacter(questShips[i]);
					sld = GetRealShip(sti(chref.ship.type));
					link.(sTemp) = "Aruba, ahoy! " + GetStrSmallRegister(XI_ConvertString(sld.BaseName)) + " '" + chref.Ship.Name + "' is all yours!";
					link.(sTemp).go = "joruba_p3_ship_" + questShips[i];
					if (FindCompanionShips(SHIP_PINK) && sti(pchar.questTemp.ChickenGod.Tasks.Schyot) <= 1 && startHeroType != 4)
					{
						link.(sTemp) = "Aruba, ahoy! Pink '" + chref.Ship.Name + "' is all yours!";
						link.(sTemp).go = "joruba_p3_PinkOtkaz";
					}
					/*if (FindCompanionShips(SHIP_GALEON_SM))
					{
						link.(sTemp) = "Aruba, ahoy! Galeon '" + chref.Ship.Name + "' is all yours!";
						link.(sTemp).go = "joruba_p3_HolyMercy";
					}*/
				}
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p4") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p4.Completed")) {
				link.p3 = "I'm willing to make a sacrifice.";
				link.p3.go = "joruba_p4";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o2.Lady") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o2.Completed")) {
				link.o2 = "I am bringing you a bride and troubles with the Spanish authorities, sir. The lady is taking a stroll outside, well protected by my men. I will not give her to you until you convince me of the nobility of your intentions.";
				link.o2.go = "joruba_o2";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o3") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o3.Completed") && GetCharacterFreeItem(pchar, "cirass4") >= 1) {
				link.o3 = "Here's your armor, Aruba. Make sure my reward will make up for it.";
				link.o3.go = "joruba_o3";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o4") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o4.Completed") && GetPrisonerQty() >= 30) {
				link.o4 = "I have the prisoners you asked for.";
				link.o4.go = "joruba_o4";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o5") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o5.Completed") && GetCharacterItem(pchar, "talisman11") >= 113) {
				link.p2 = "I brought you your junk. Here, a hundred and thirteen stones, just like you asked for.";
				link.p2.go = "joruba_o5";
			}
			
			bOk = (PCharDublonsTotal() >= 25000) || (ChickenGod_HaveOfficers());
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6.Completed") && bOk) {
				link.p3 = "I'm willing to make a sacrifice.";
				link.p3.go = "joruba_o6";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p4.Completed")) {
				link.respec = "(Respec character's stats)";
				link.respec.go = "joruba_respec";
			}
			
			link.exit = "I am just passing by.";
			link.exit.go = "joruba_wait_1";
			
			NextDiag.TempNode = "joruba_wait";
		break;
		
		case "joruba_wait_1":
			dialog.text = "Next time then.";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "joruba_p1":
			dialog.text = "Not bad, I will put that gold to good use. Here, a little trinket previously owned by a very virtuous Taino chief. Helps to carry piles of gold. Certainly helped him, heh-heh...";
			link.l1 = "Thank you and hope I won't regret it. What's the next deal?";
			link.l1.go = "joruba_p1_1";
			link.l2 = "Wait a minute. I gave you a pile of gold and got a lump of clay in return? Well, I need a refund!";
			link.l2.go = "joruba_insult";
			
			RemoveDublonsFromPCharTotal(2000);
			pchar.questTemp.ChickenGod.Gold = 2000;
			
			pchar.questTemp.ChickenGod.Tasks.p1.Completed = true;
			GiveItem2Character(pchar, "talisman13");
			//Log_info("You received Taino Figurine");
			PlaySound("interface\important_item.wav");
		break;
		
		case "joruba_p1_1":
			dialog.text = "Eh? Aye, the next deal. This gold should suffice for now, so it's time to consider more spiritual commodities. Got to find myself a cure.";
			link.l1 = "Why, are you ill?";
			link.l1.go = "joruba_p1_2";
		break;
		
		case "joruba_p1_2":
			dialog.text = "My soul is. See, priests avoid my humble pyramide since that incident with the Inquisition, so we have to rely on more traditional methods. I need, well, my factoria needs fifteen magarosa plants to stay operational.";
			if (!ChickenGod_TalkedToAmelia()) {
				link.l1 = "Is that a herb?";
			} else {
				link.l1 = "I know what it is, heh-heh.";
			}
			link.l1.go = "joruba_p1_3";
		break;
		
		case "joruba_p1_3":
			dialog.text = "I'll be honest - it's a rare herb of great value. Think carefully if you are really going to spend years gathering it all over the archipelago?";
			link.l1 = "No promises, but I wish you good health and hope that my reward for the herb will be well worth it.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_GiveSecondTask");
		break;
		
		case "joruba_p2":
			dialog.text = "All right, I am officially calling it my day off! A bargain such as this is worth a real treasure. Behold!\nThis machete was once this close to crushing that imbecile Kanek's head! Therefore, it's very dear to me and I humbly ask you to take good care of it. It's old, but crafted extremely well, they don't make steel like this anymore.";
			link.l1 = "Kanek? Who's that?";
			link.l1.go = "joruba_p2_1";
			
			TakeNItems(pchar, "cannabis7", -15);
			pchar.questTemp.ChickenGod.Tasks.p2.Completed = true;
			if (pchar.rank >= 21)
			{
				sld = ItemsFromID("machete2");
                sld.Attack = 80.0;
			}
			else
			{
				sld = ItemsFromID("machete2");
                sld.Attack = 60.0;
			}
			GiveItem2Character(pchar, "machete2");
			//Log_info("You received Machete Conquistador");
			PlaySound("interface\important_item.wav");
			SetAlchemyRecipeKnown("bullet_double");
			SetAlchemyRecipeKnown("grapeshot_double");
			ChickenGod_InitAmmo();
		break;
		
		case "joruba_p2_1":
			dialog.text = "Oh, you two will meet. Now, I hope you're not one of those pompous assholes who disdain manual labor? If so, you're a shit out of luck, because the second part of the reward are the schematics of double-charged ammo.";
			if (pchar.HeroParam.HeroType == "HeroType_4") {
				link.l1 = "Oh, I love those. But what's unique about them? A double powder charge is not news, therefore I conclude that you obviously haven't left your pyramid since the times of that museum machete.";
			} else {
				link.l1 = "That's it? Hey...";
			}
			link.l1.go = "joruba_p2_2";
		break;
		
		case "joruba_p2_2":
			dialog.text = "Don't be a smartass and listen! Any idiot can put two piles of gunpowder in a barrel and risk getting blind, face burns or a broken nose. I offer you a little magic trick: check the quality of the powder carefully, grind it to the right consistency, put in a bullet or buckshot, and spice it up with a chopped doubloon. The bang will tear even a cuirass to shreds!";
			link.l1 = "Shooting money, eh? So much like you.";
			link.l1.go = "joruba_p2_3";
		break;
		
		case "joruba_p2_3":
			dialog.text = "You are insufferable! Fine, grab a hand mortar, and a dozen grenades for it too. If you are so damn smart, you will acquire the grenades schematics on your own in no time!";
			link.l1 = "Many thanks, my lord. What's next?";
			link.l1.go = "joruba_p2_4";
			
			//Log_info("You received Hand mortar");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "mortairgun");
			TakeNItems(pchar, "grenade", 10);
		break;
		
		case "joruba_p2_4":
			dialog.text = "You are not going to love it. I need a ship... no, I need the ship. You know, with a story behind her.";
			link.l1 = "Why? You're not even a captain.";
			link.l1.go = "joruba_p2_5";
		break;
		
		case "joruba_p2_5":
			dialog.text = "None of your business! Better focus on your reward, because I can demand to clean this pyramid from top to bottom for this, and you'd still owe me!";
			link.l1 = "You're definitely not a captain, otherwise you'd know that a ship needs a pier or a bay to dock in. How the hell do you expect me to get a ship into your pyramid?!";
			link.l1.go = "joruba_p2_6";
		break;
		
		case "joruba_p2_6":
			dialog.text = "Have you noticed a giant lake behind my pyramid by any chance? That's right. Just dock with the right ship in the squadron nearby and my men will do the rest. Now get out of here, you're holding up the line.";
			link.l1 = "But of course. Bye!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_GiveThirdTask");
		break;
		
		case "joruba_p3":
			sld = GetCharacter(sti(companion));
			pchar.questTemp.ChickenGod.Tasks.p3.ship = sld.ship.type;
			RemoveCharacterCompanion(pchar, sld);
			AddPassenger(pchar, sld, false);
						
			npchar.ship.type = pchar.questTemp.ChickenGod.Tasks.p3.ship;
			SetCharacterShipLocation(npchar, "Temple");
						
			sld = GetRealShip(sti(pchar.questTemp.ChickenGod.Tasks.p3.ship));
					
			dialog.text = "Nice! Got it!";
			link.l1 = "Drop your smartass act and give me my reward!";
			link.l1.go = "joruba_p3_1";
			switch (sti(sld.BaseType)) {
				case SHIP_MAYFANG:
					dialog.text = "What about the other two? Couldn't save them for yourself? Heh-heh.";
				break;
				
				case SHIP_MIRAGE:
					dialog.text = "What about the other two? Couldn't save them for yourself? Heh-heh.";
				break;
				
				case SHIP_VALCIRIA:
					dialog.text = "What about the other two? Couldn't save them for yourself? Heh-heh.";
				break;
				
				case SHIP_FRIGATE_L:
					dialog.text = "Shit, I am impressed you didn't want to keep her for yourself. Now that's what I call a ship with a story! Damn it, William... I really wished you would return home and found a great bank like you always dreamed.";
				break;
				
				case SHIP_CORVETTE_QUEST:
					sTemp = "privateer";
					if (isMainCharacterPatented()) {
						sTemp = GetStrSmallRegister(GetAddress_FormTitle(sti(Items[sti(pchar.EquipedPatentId)].Nation), sti(Items[sti(pchar.EquipedPatentId)].TitulCur)));
					}
					
					dialog.text = "Will you look at this! You are a disgrace of your commission, " + sTemp + "!";
				break;
				
				case SHIP_POLACRE_QUEST:
					dialog.text = "Charlie Prince decided to get rid of incriminating evidence in my old pyramid? I approve!";
				break;
				
				case SHIP_ECLIATON:
					dialog.text = "Good luck explaining to your superiors the loss of the flagship, Admiral. Oh, pardon me, general-governor.";
				break;
				
				case SHIP_CURSED_FDM:
					dialog.text = "Are you a superstitious fool or just a fool? She is worth a fortune! I'm not sure it's a fair trade, but whatever.";
				break;
				
				case SHIP_FDM:
					dialog.text = "Are you a superstitious fool or just a fool? She is worth a fortune! I'm not sure it's a fair trade, but whatever.";
				break;
				
				case SHIP_RENOVATED_FDM:
					dialog.text = "Are you a superstitious fool or just a fool? She is worth a fortune! I'm not sure it's a fair trade, but whatever.";
				break;
				
				case SHIP_ELCASADOR:
					dialog.text = "Good call! I love the Castilians, you know. Maybe I will return her to them when I am done.";
				break;
				
				case SHIP_HIMERA:
					dialog.text = "Truly, you lack a heart, Captain. This ship stinks of treachery. I'll take her.";
				break;
				
				case SHIP_PINK:
					if (startHeroType == 4)
					{
						dialog.text = "Aye, this ship may have a history... but wasn't it too easy to obtain? Ah, fine. Your case is special, my dear, so I'll take it. Brings back some memories of my youth at least.";
						Achievment_Set("ach_CL_127");
					}
					else 
					{
						dialog.text = "Aye, this ship may have a history... but wasn't it too easy to obtain? Oh, what the hell. Alright, Cap, I'll let this one slide, since you did a great job with those tasks from my list. I'll take it. Brings back some memories of my youth at least.";
					}
				break;
				
				case SHIP_GALEON_SM:
					dialog.text = "And have you seen the priest? Well, you'll meet him. And you'd better stock up on double-shot pistol loads. If that doesn't help - try a wooden stake.";
				break;
				
				case SHIP_LADYBETH:
					dialog.text = "And have you seen the priest? Well, you'll meet him. And you'd better stock up on double-shot pistol loads. If that doesn't help - try a wooden stake.";
				break;
			}
		break;
		
		/*case "joruba_p3_HolyMercy":
			dialog.text = "And have you seen the priest?";
			link.l1 = "What priest?";
			link.l1.go = "joruba_p3_HolyMercy_2";
		break;
		
		case "joruba_p3_HolyMercy_2":
			dialog.text = "Well, you'll meet him. And you'd better stock up on double-shot pistol loads. If that doesn't help - try a wooden stake.";
			link.l1 = "...";
			link.l1.go = "joruba_p3_1";
		break;*/
		
		case "joruba_p3_PinkOtkaz":
			dialog.text = "Aye, this ship may have a history... but wasn't it too easy to obtain? No way! You still have a ton of unfinished work from the list. Once you've done that, we'll discuss this sacrifice again.";
			link.l1 = "...";
			link.l1.go = "exit";
		break;
		
		case "joruba_p3_1":
			dialog.text = "I bless thee, " + GetFullName(pchar) + ". May the sea be favorable to you. Now, let's discuss the next transaction...";
			link.l1 = "Wait, what? Even yokel idiots don't fall for such nonsense in our age of ration! I didn't put a centime in your charity box, I gave you a full-fledged warship!";
			link.l1.go = "joruba_insult";
			link.l2 = "Hold on a second. What exactly does your blessing mean to me?";
			link.l2.go = "joruba_p3_2";
			
			pchar.questTemp.ChickenGod.Tasks.p3.Completed = true;
		break;
		
		case "joruba_p3_2":
			dialog.text = "Any ship you master will from now be blessed with a stronger hull, while your enemies will suffer the opposite. Also, time at the sea will run slower for you. And if that's not enough for you to bring this whole shithole to its knees, you'd better go to your daddy and demand a refund!";
			link.l1 = "If it doesn't work, I swear I'll come back here tonight and burn your pyramid down! Tell me about the next deal!";
			link.l1.go = "joruba_p3_3";
			notification("+10% hull defence", "None");
			notification("+10% damage to enemy ships hull", "None");
			notification("+5% speed on the Global Map", "None");
			PlaySound("Interface\new_level.wav");
		break;
		
		case "joruba_p3_3":
			dialog.text = "Developing a taste for it, eh captain? Unfortunately for you, so am I. Why do you think I chose this pyramid for my office?";
			link.l1 = "Probably because witch purge is still a thing?";
			link.l1.go = "joruba_p3_4";
		break;
		
		case "joruba_p3_4":
			dialog.text = "Heh-heh, no, not quite. I conduct my business here because the best deals require blood. This pyramid requires blood. I require blood. That's the way it's been, that's the way it's going to be.";
			link.l1 = "Don't even think about it, you monster. I will not deliver victims for you to kill!";
			link.l1.go = "joruba_p3_5";
		break;
		
		case "joruba_p3_5":
			dialog.text = "And how many have you killed, eh? Wait, I'll even tell you the exact number: you personally killed " + (Statistic_AddValue(pchar, "Solder_s", 0) + Statistic_AddValue(pchar, "Citizen_s", 0) + Statistic_AddValue(pchar, "Warrior_s", 0) + Statistic_AddValue(pchar, "Solder_g", 0) + Statistic_AddValue(pchar, "Citizen_g", 0) + Statistic_AddValue(pchar, "Warrior_g", 0)) + " people! You put a mountain of corpses on the altar of your ambition and lust for wealth! ";
			if (HasSubStr(pchar.model, "Sharle")) {
				dialog.text = dialog.text + "Your brother's debt has already killed more people than an average European war! ";
			}
			dialog.text = dialog.text + "Don't even start moralizing here with me, especially since I'm not going to judge you. The success of some will always be paid for by the tragedies of others, and the gods, oh, gods, they will be watching and collecting their share!";
			link.l1 = "I can't give you an answer right now... I need to get out of here.";
			link.l1.go = "joruba_p3_6";
		break;
		
		case "joruba_p3_6":
			dialog.text = "An urgent need to clear your head? All right, but first, listen to me. I will give you power and complete control over your body and mind, if you bring me a man of great worth. Not an extra, not a faceless gray mouse from the streets or a rat from the stinking bilges. Bring me a man who follows you and plays an important role in your tragicomedy.";
			link.l1 = "One of my officers? You can't go any lower, Aruba! If word of this gets out...";
			link.l1.go = "joruba_p3_7";
		break;
		
		case "joruba_p3_7":
			dialog.text = "I'll take care of secrecy as I always do. And before you start whining again, I will let you know that there is another way.";
			link.l1 = "What's that supposed to mean? So I don't have to drag my own people to the altar?";
			link.l1.go = "joruba_p3_8";
		break;
		
		case "joruba_p3_8":
			dialog.text = "Nope, but you won't like the alternative. If you don't want to pay with blood, you can pay with gold. Three thousand doubloons and a clean conscience. Money can do that and more - I love it!";
			link.l1 = "Bye, Aruba. I don't want to talk to you anymore.";
			link.l1.go = "joruba_p3_9";
		break;
		
		case "joruba_p3_9":
			dialog.text = "You know where to find me.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_GiveFourthTask");
		break;
		
		case "joruba_p4":
			dialog.text = "Let's do this quick before the Spanish Inquisition shows up. Sangre u oro?";
			if (PCharDublonsTotal() >= 3000)
			{
				link.l1 = "Gold it is. Here's your three thousand although I can't imagine how you can possibly spend such an enormous amount in this wilderness.";
				link.l1.go = "joruba_p4_1";
			}
			if (ChickenGod_HaveOfficers()) 
			{
				link.l2 = "Blood.";
				link.l2.go = "joruba_p4_other";
			}
			link.l3 = "Nevermind.";
			link.l3.go = "exit";
		break;
		
		case "joruba_p4_1":
			dialog.text = "...";
			link.l1 = "Are you done? Let's talk about my award.";
			link.l1.go = "joruba_p4_reward_1";
			RemoveDublonsFromPCharTotal(3000);
			pchar.questTemp.ChickenGod.Gold = sti(pchar.questTemp.ChickenGod.Gold) + 3000;
		break;
		
		case "joruba_p4_other":
			dialog.text = "So be it. Say the name.";
			
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Duran");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Baker");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Folke");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Avendel");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Tonzag");
			if (!CheckAttribute(pchar, "questTemp.PZ_LongwayNelzyaOtdatArube")) ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Longway");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Knippel");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Tichingitu");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Irons");
		break;
		
		case "joruba_p4_off":
			if (pchar.questTemp.ChickenGod.Sacrifice == "Duran" && !CheckAttribute(pchar, "questTemp.SKD_DuranDruzhba"))
			{
				dialog.text = "Claude Durand is not an officer, but a ruthless mercenary, so choose another victim.";
				link.l1 = "";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.ChickenGod.Sacrifice == "Duran" && CheckAttribute(pchar, "questTemp.SKD_DuranDruzhba") && CheckAttribute(pchar, "questTemp.SKD_DevushkaUbita"))
			{
				Achievment_Set("ach_CL_116");
			}
			
			dialog.text = "I accept your tribute. You don't have to watch.";
			link.l1 = "No, I don't. I will be back for my reward in an hour.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "joruba_p4_reward";
			ChangeCharacterComplexReputation(pchar, "nobility", -50);
			
			AddDialogExitQuestFunction("ChickenGod_KillOfficer");
		break;
		
		case "joruba_o6_money":
			dialog.text = "Great choice. I hate cleaning the altar of all that blood, so gold is preferable. Here, take this potion - a compliment from a good friend of mine.";
			link.l1 = "The taste is not bad at all...";
			link.l1.go = "exit";
			
			PlaySound("Ambient\Tavern\glotok_001.wav");
			RemoveDublonsFromPCharTotal(25000);
			pchar.questTemp.ChickenGod.Gold = sti(pchar.questTemp.ChickenGod.Gold) + 25000;
			
			if (sti(pchar.questTemp.ChickenGod.Gold) >= 30000) {
				Achievment_Set("ach_CL_87");
			}
			
			notification("+3 P.I.R.A.T.E.S. point", "None");
			PlaySound("Interface\new_level.wav");
			pchar.skill.FreeSPECIAL = 3;
			pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices = sti(pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices) + 5;
			if (sti(pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices) >= 5) {
				pchar.questTemp.ChickenGod.Tasks.o6.Completed = true;
			}
			
			AddDialogExitQuestFunction("ChickenGod_Respec");
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_p4_reward":
			dialog.text = "";
			link.l1 = "Are you done? Let's talk about my award.";
			link.l1.go = "joruba_p4_reward_1";
		break;
		
		case "joruba_p4_reward_1":
			dialog.text = "Talk to me anytime you want to change your destiny.";
			link.l1 = "But what exactly does it mean for me?";
			link.l1.go = "joruba_p4_reward_2";
		break;
		
		case "joruba_p4_reward_2":
			dialog.text = "Power over yourself! Try it sometimes and you'll love it. In the meantime, let me tell you about the next transaction. The most important one.";
			link.l1 = "I'm not sure it's worth it anymore!";
			link.l1.go = "joruba_p4_reward_3";
			link.l2 = "Come on, spill it already.";
			link.l2.go = "joruba_p4_reward_3";
		break;
		
		case "joruba_p4_reward_3":
			dialog.text = "You have the opportunity to not just change your destiny, but to stand next to the geniuses and gods of our time. Aye, you can change your body and mind as much as you want now, but you will never jump above your head, because an ordinary person can't be good at everything. What I'm suggesting is that you break those boundaries.";
			link.l1 = "What's it gonna cost me? More blood? Gold?";
			link.l1.go = "joruba_p4_reward_4";
		break;
		
		case "joruba_p4_reward_4":
			dialog.text = "Aye. Either you bring me twenty five thousand doubloons or one of your companions.Once we are done there will be no more transactions.";
			link.l1 = "I'll give it a thought.";
			link.l1.go = "joruba_p4_reward_5";
		break;
		
		case "joruba_p4_reward_5":
			dialog.text = "You know where to find me. And don't hesitate to visit me anytime you would like to change your destiny.";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "joruba_wait";
			
			pchar.questTemp.ChickenGod.Tasks.p4.Completed = true;
			AddDialogExitQuestFunction("ChickenGod_GiveFifthTask");
		break;
		
		case "joruba_respec":
			dialog.text = "As you wish.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ChickenGod_Respec");
		break;
		
		case "joruba_o2":
			dialog.text = "First of all, that's my wife, not a bride. Secondly, you have a problem with the Castilians, not me. And finally, I've already taken her and dismissed your men. And as for honorable intentions... Look at me, am I not a model of a decent gentleman? Tlazolteotl, bless him that he too may one day know a real woman. Or a man.";
			link.l1 = "Screw you, Aruba!";
			link.l1.go = "exit";
			
			notification("+ 10 HP, + 10 Energy!", "None");
			PlaySound("Interface\new_level.wav");
			ChickenGod_ModifyStats(10.0);
			pchar.questTemp.ChickenGod.Tasks.o2.Completed = true;
			pchar.questTemp.ChickenGod.Tasks.Schyot = sti(pchar.questTemp.ChickenGod.Tasks.Schyot) + 1;
			
			sld = CharacterFromID(pchar.questTemp.ChickenGod.Tasks.o2.Lady);
			RemovePassenger(pchar, sld);
			ChangeCharacterAddressGroup(sld, "Temple", "goto", "goto1");
			LAi_SetCitizenTypeNoGroup(sld);
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_o3":
			dialog.text = "Not bad, thank you. Frankly, I don't really need it, but maybe I'll wear it in some salon or whatever. In the name of Ishtar I bless you. Now go and sin.";
			link.l1 = "What a strange feeling...";
			link.l1.go = "exit";
			
			notification("+ 15 HP, + 15 Energy!", "None");
			PlaySound("Interface\new_level.wav");
			ChickenGod_ModifyStats(15.0);
			pchar.questTemp.ChickenGod.Tasks.o3.Completed = true;
			pchar.questTemp.ChickenGod.Tasks.Schyot = sti(pchar.questTemp.ChickenGod.Tasks.Schyot) + 1;
			
			TakeItemFromCharacter(pchar, "cirass4");
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_o4":
			dialog.text = "I'll take them. What? I need deadmen in my crew like you do, except that unlike you I can't go around taverns recruiting. Now, Bast, bless the hero for his future endeavors.";
			link.l1 = "What a strange feeling...";
			link.l1.go = "exit";
			
			notification("+ 15 HP, + 15 Energy!", "None");
			PlaySound("Interface\new_level.wav");
			ChickenGod_ModifyStats(15.0);
			pchar.questTemp.ChickenGod.Tasks.o4.Completed = true;
			pchar.questTemp.ChickenGod.Tasks.Schyot = sti(pchar.questTemp.ChickenGod.Tasks.Schyot) + 1;
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
			
			AddDialogExitQuestFunction("ChickenGod_RemovePrisoners");
		break;
		
		case "joruba_o5":
			dialog.text = "Yeah, we'll have to scatter them back, cause people lose them all the time, and we need customers. Freya, protect this great rock collector.";
			link.l1 = "What a strange feeling...";
			link.l1.go = "exit";
			
			TakeNItems(pchar, "talisman11", -113);
			
			notification("+ 15 HP, + 15 Energy!", "None");
			PlaySound("Interface\new_level.wav");
			ChickenGod_ModifyStats(15.0);
			pchar.questTemp.ChickenGod.Tasks.o5.Completed = true;
			pchar.questTemp.ChickenGod.Tasks.Schyot = sti(pchar.questTemp.ChickenGod.Tasks.Schyot) + 1;
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_o6":
			dialog.text = "Let's do this quick before the Spanish Inquisition shows up. Sangre u oro?";
			
			if (PCharDublonsTotal() >= 25000)
			{
				link.money = "Here's your gold, you greedy bastard.";
				link.money.go = "joruba_o6_money";
			}
			
			if (ChickenGod_HaveOfficers())
			{
				link.blood = "Blood.";
				link.blood.go = "joruba_o6_blood";
			}
			link.l3 = "Nevermind.";
			link.l3.go = "exit";
		break;
		
		case "joruba_o6_blood":
			dialog.text = "Say the name.";
			
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Duran");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Baker");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Folke");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Avendel");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Tonzag");
			if (!CheckAttribute(pchar, "questTemp.PZ_LongwayNelzyaOtdatArube")) ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Longway");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Knippel");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Tichingitu");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Irons");
			
			if (!CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6.gf")) {
				ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Helena");
				ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Mary");
			}
		break;
		
		case "joruba_o6_off":
			if (pchar.questTemp.ChickenGod.Sacrifice == "Mary" || pchar.questTemp.ChickenGod.Sacrifice == "Helena") {
				pchar.questTemp.ChickenGod.Tasks.o6.gf = true;
				sTemp = "future wife";
				sld = CharacterFromID(pchar.questTemp.ChickenGod.Sacrifice);
				if (sld.lastname == pchar.lastname) {
					sTemp = "current wife";
				}
				
				dialog.text = "That's quite tempting, but I'll make an exception just this once - I won't accept your sacrifice. I won't disclose this to your " + sTemp + ", even though I probably should. Remember that you are nothing without her. Now, get lost and don't bother me today.";
				link.l1 = "";
				link.l1.go = "exit";
				
				AddDialogExitQuestFunction("ChickenGod_KickedFromTemple");
				break;
			}
			if (pchar.questTemp.ChickenGod.Sacrifice == "Duran" && !CheckAttribute(pchar, "questTemp.SKD_DuranDruzhba"))
			{
				dialog.text = "Claude Durand is not an officer, but a ruthless mercenary, so choose another victim.";
				link.l1 = "";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.ChickenGod.Sacrifice == "Duran" && CheckAttribute(pchar, "questTemp.SKD_DuranDruzhba") && CheckAttribute(pchar, "questTemp.SKD_DevushkaUbita"))
			{
				Achievment_Set("ach_CL_116");
			}
			
			dialog.text = "So be it. Here, take this potion - a compliment from a good friend of mine.";
			link.l1 = "The taste is not bad at all...";
			link.l1.go = "joruba_o6_reward";
			
			PlaySound("Ambient\Tavern\glotok_001.wav");
			
			ChangeCharacterComplexReputation(pchar, "nobility", -50);
			notification("+3 P.I.R.A.T.E.S. points", "None");
			PlaySound("Interface\new_level.wav");
			pchar.skill.FreeSPECIAL = 3;
			pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices = sti(pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices) + 5;
			if (sti(pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices) >= 5) {
				pchar.questTemp.ChickenGod.Tasks.o6.Completed = true;
			}
			
			AddDialogExitQuestFunction("ChickenGod_KillOfficer");
			AddDialogExitQuestFunction("ChickenGod_Respec");
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_o6_reward":
			dialog.text = "Until next time, captain.";
			link.l1 = "";
			link.l1.go = "exit";
			
			pchar.questTemp.ChickenGod.OnExitKick = true;
		break;
		
		case "joruba_final":
			dialog.text = "Ahoy-hoy! Finally, it's all over!";
			link.l1 = "Huh?";
			link.l1.go = "joruba_final_1";
		break;
		
		case "joruba_final_1":
			dialog.text = "We're finished here, Captain. The deals are sealed, everyone's satisfied, and there's no room for refunds. Our office is shutting down and relocating.";
			link.l1 = "Wait a moment, Aruba. I've given you plenty of gold, paid with blood, brought women and prisoners to this devilish lair. I can manage supernatural events that apparently occur in the Caribbean. But our 'transactions' with you defy all logic. Please explain.";
			link.l1.go = "joruba_final_2";
		break;
		
		case "joruba_final_2":
			dialog.text = "You know what? I'll tell you.\nI'm fed up with this world, and I want out. Every day, it's the same old routine: an ancient pyramid with a crumbling ceiling, those loathsome identical palm trees, and a never-ending stream of captains, each with their own ingenious ideas. Yes, I provide people with what they desire; it's my calling, and I take pride in it. But by the gods, how I detest all of you!";
			link.l1 = "Is someone keeping you here? The exit is right there, genius!";
			link.l1.go = "joruba_final_3";
		break;
		
		case "joruba_final_3":
			dialog.text = "You're absolutely right, nobody's holding me here. Not anymore. And it's all thanks to you, my friend.";
			link.l1 = "That's a sudden change of heart. I was expecting a story, but all I've heard so far is the meaningless rants of a vile lil' god in a dusty pyramid.";
			link.l1.go = "joruba_final_4";
		break;
		
		case "joruba_final_4":
			dialog.text = "Well, everyone needs to vent from time to time, don't they? I'm really glad you came here because, thanks to you, I can finally depart from this world. Gold, crew, equipment, and a ship, my friend. Remember? Sound familiar? That's all I required, and you provided it all.";
			link.l1 = "You're welcome. However, that still doesn't clarify your peculiar way of speaking and almost divine powers. If you're so all-powerful, you could have conjured your own ship, crew, and gold a long time ago!";
			link.l1.go = "joruba_final_5";
		break;
		
		case "joruba_final_5":
			dialog.text = "Which I did, as you can see. Everyone has their own methods.";
			link.l1 = "But how in the world? Who are you, exactly?";
			link.l1.go = "joruba_final_6";
		break;
		
		case "joruba_final_6":
			dialog.text = "Well... that's what I do, simply. See you in the new world, " + GetPersonaName() + ". Really new next time I hope. Thank you and goodbye.";
			link.l1 = "No, I don't want to see you ever again.";
			link.l1.go = "exit";
			link.l2 = "Then see you around, Aruba... this was interesting.";
			link.l2.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_FinalGood");
		break;
		
		case "joruba_insult":
			dialog.text = "Looks like all deals are off. Time to go, captain.";
			link.l1 = "Time for you to f...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_Insult");
		break;
		
		case "ChickenGod_TheInquisition_1":
			dialog.text = "In the name of the Spanish Inquisition, name yourself!";
			link.l1 = "Captain "+GetFullName(pchar)+". And it's true what they say, nobody expects the Spanish Inquisition...";
			link.l1.go = "ChickenGod_TheInquisition_2";
		break;
		
		case "ChickenGod_TheInquisition_2":
			dialog.text = "... This joke is always to the point, even though it led quite a few innocent Christians to the stake.";
			link.l1 = "...";
			link.l1.go = "ChickenGod_TheInquisition_3";
		break;
		
		case "ChickenGod_TheInquisition_3":
			dialog.text = "Just kidding, Captain. You were joking, and I was joking. My name is Padre Emilio Bocanegra, and these soldiers of Christ are my armed guards.";
			link.l1 = "What can I do for you, padre?";
			link.l1.go = "ChickenGod_TheInquisition_4";
		break;
		
		case "ChickenGod_TheInquisition_4":
			dialog.text = "Do you know a certain senor Aruba?";
			link.l1 = "Yes, he lived in this old pyramid until recently.";
			link.l1.go = "ChickenGod_TheInquisition_5";
		break;
		
		case "ChickenGod_TheInquisition_5":
			dialog.text = "What do you mean he lived there? Is it possible to live there? And why 'until recently'?";
			link.l1 = "This senor just left us on a ship a few minutes ago.";
			link.l1.go = "ChickenGod_TheInquisition_6";
		break;
		
		case "ChickenGod_TheInquisition_6":
			dialog.text = "How do you know that? The nearest bay is days away!";
			link.l1 = "This lake must be bigger than it looks. I have no other explanation for you, padre.";
			link.l1.go = "ChickenGod_TheInquisition_7";
		break;
		
		case "ChickenGod_TheInquisition_7":
			dialog.text = "Strange things are happening in the lands of the Viceroyalty.";
			link.l1 = "These are English lands, padre.";
			link.l1.go = "ChickenGod_TheInquisition_8";
		break;
		
		case "ChickenGod_TheInquisition_8":
			dialog.text = "Let the heretics continue to think so. We will surely get ours back. Forgive me, my son, for asking so many questions: Santiago has instructed me to conduct an official inquiry into this pyramid... and its former occupant.";
			link.l1 = "What exactly happened, padre?";
			link.l1.go = "ChickenGod_TheInquisition_9";
		break;
		
		case "ChickenGod_TheInquisition_9":
			dialog.text = "Since the case will probably be closed, I can entertain you with a little story.\nRumors of this place have been circulating all over the Main for some time. We had received reliable reports that a number of individuals who had left a significant mark on the history of the region had made regular visits here in the past\nHowever, Santiago began to pay real attention to these rumors after the Panama incident.\nA certain Indian had made a great splash in that glorious city and even gave several sermons of a rather philosophical nature. Unfortunately, the inhabitants of Panama made rather superficial conclusions and convinced themselves that this pyramid contains untold treasures and fulfills any wishes\nHeresy of the purest kind, of course... so we had to open proceedings against some Panamanian residents and this Indian, Aguebana.";
			link.l1 = "Why didn't the Panamanian authorities crack down on this?";
			link.l1.go = "ChickenGod_TheInquisition_10";
		break;
		
		case "ChickenGod_TheInquisition_10":
			dialog.text = "КAs they always do in these cases, they claimed they were bewitched. This legal loophole could have been closed if we had questioned Aguebana, but he died suddenly.";
			link.l1 = "How did he die?";
			link.l1.go = "ChickenGod_TheInquisition_11";
		break;
		
		case "ChickenGod_TheInquisition_11":
			dialog.text = "Drunkenness killed him. However, his death did not solve our problems, because the heresy had taken root all over the archipelago, and hundreds of people went on a kind of pilgrimage to this ancient temple.";
			link.l1 = "I've never seen crowds of people here before... So what, you were going to invade Aruba and put him on trial?";
			link.l1.go = "ChickenGod_TheInquisition_12";
		break;
		
		case "ChickenGod_TheInquisition_12":
			dialog.text = "Of course not, my son. The judgment of the Inquisition is harsh but fair. There must be a good reason for a trial. No, I was only going to collect senor Aruba's testimony and deliver it to Santiago.";
			link.l1 = "Well, that's unfortunate for you.";
			link.l1.go = "ChickenGod_TheInquisition_13";
		break;
		
		case "ChickenGod_TheInquisition_13":
			dialog.text = "You never know, my son. It's God's will.";
			link.l1 = "Goodbye, padre.";
			link.l1.go = "ChickenGod_TheInquisition_14";
		break;
		
		case "ChickenGod_TheInquisition_14":
			DialogExit();
			
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Temple", "reload2", false);
			LAi_SetActorType(npchar);
			//LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "ChickenGod_TheInquisitionLeave", -1);
			PChar.quest.ChickenGod_TheInquisitionLeave.win_condition.l1 = "ExitFromLocation";
			PChar.quest.ChickenGod_TheInquisitionLeave.win_condition.l1.location = PChar.location;
			PChar.quest.ChickenGod_TheInquisitionLeave.win_condition = "ChickenGod_TheInquisitionLeave";
		break;
		
	}
} 

void ChickenGod_InitAmmo() {
	if(LoadSegment("items\initItems.c")) {
		InitGunExt(		 "pistol1", "t3", 	 "bullet_double",               "", 100.0, 300.0,  60.0, 260.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 40, 20, 0);
		InitGunExt( 	 "pistol2", "t2", "grapeshot_double",               "",  60.0, 160.0,  20.0, 100.0,  0.0,  0.0, 0, 1, 1, 0, 1, 1, 40, 20, 0);
		InitGunExt(		 "pistol3", "t2", "grapeshot_double",               "",  80.0, 180.0,  30.0, 110.0,  0.0,  0.0, 0, 1, 1, 2, 1, 1, 40, 20, 0);
		InitGunExt(		 "pistol4", "t3",    "bullet_double",               "",  70.0, 270.0,  30.0, 230.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 35, 30, 0);
		InitGunExt(		 "pistol5", "t3", 	 "bullet_double",               "", 130.0, 330.0,  90.0, 290.0,  0.0,  0.0, 1, 0, 0, 2, 0, 0, 70, 30, 0);
		InitGunExt(		 "pistol6", "t3",    "bullet_double",               "", 100.0, 300.0,  60.0, 260.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 50, 20, 0);
		InitGunExt(		 "pistol8", "t4", "grapeshot_double",               "",  50.0, 100.0,  30.0,  60.0,  5.0,  5.0, 1, 1, 1, 0, 1, 1, 20, 20, 0);
		InitGunExt(		 "pistol9", "t3", 	 "bullet_double",               "", 100.0, 320.0,  80.0, 280.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 40, 30, 0);
		InitGunExt(		 "pistol10", "t3",   "bullet_double",               "", 140.0, 280.0, 100.0, 240.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 45, 30, 0);
		InitGunExt(		 "pistol11", "t3",   "bullet_double",               "",  10.0, 700.0,  10.0, 620.0, 40.0, 30.0, 1, 1, 0, 0, 0, 0, 45,100, 0);
		InitGunExt(		 "pistol12", "t3",   "bullet_double",               "",  80.0, 290.0,  60.0, 240.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 45, 20, 0);
		InitGunExt(		 "pistol13", "t3",   "bullet_double",               "", 130.0, 300.0,  90.0, 260.0, 15.0,  0.0, 1, 1, 0, 0, 0, 0, 60, 30, 0);
		InitGunExt(		 "howdah",  "t3", "grapeshot_double",	            "",  50.0, 140.0,  30.0,  70.0,  5.0,  5.0, 1, 1, 1, 0, 0, 1, 50, 30, 0);
		InitGunExt(		 "pistol14", "t3",   "bullet_double",               "", 130.0, 330.0,  90.0, 290.0,  0.0,  0.0, 1, 0, 0, 4, 0, 0, 70, 34, 0); // Дуэльный двухзарядный пистоль cle 1.3
		
		UnloadSegment("items\initItems.c");
	}
	
	CGInitGrapeGunExt(	"pistol2",	"t2",		3,		50,		4.25,	5.0,	3);		// трёхствольный дробовик, двойной заряд
	CGInitGrapeGunExt(	"pistol3",	"t2",		4,		40,		6.0,	5.0,	4);		// тромбон, двойной заряд
	CGInitGrapeGunExt(	"pistol8",	"t4",		4,		110,	5.0,	3.0,	2);		// бландербуз, двойной заряд
	CGInitGrapeGunExt(	"howdah",	"t3",		3,		85,		3.0,	5.5,	2);		// гауда, двойной заряд
	CGInitGrapeGunExt(	"mushket3",	"t2",		3,		60,		6.0,	3.0,	3);		// аркебуза, картечь
	CGInitGrapeGunExt(	"mushket6",	"t3",		3,		90,		4.0,	3.5,	2);		// башенный мушкетон, картечь
}

void CGInitGrapeGunExt(string id, string sAttr, int basedmg, int shards, float width, float height, int dispersion)
{
	ref gun = ItemsFromID(id);
	gun.type.(sAttr).basedmg = basedmg;
	gun.type.(sAttr).shards = shards;
	string sArea = "grapes_area_"+dispersion;
	gun.type.(sAttr).area = XI_ConvertString(sArea);
	gun.type.(sAttr).width = width;
	gun.type.(sAttr).height = height;
}

bool ChickenGod_FindQuestShips() {
	questShipsNum = 0;
	
	for(int i = 1; i < COMPANION_MAX; i++) {
		int index = GetCompanionIndex(pchar, i);
		if (index < 0) {
			continue;
		}
		
		sld = GetCharacter(index);
		int shipIndex = sti(sld.ship.type);
		if (shipIndex == SHIP_NOTUSED) {
			continue;
		}
		
		ref realShip = GetRealShip(shipIndex);
		if (!CheckAttribute(realShip, "QuestShip")) {
			continue;
		}
		
		if (!GetRemovable(sld) || !GetShipRemovable(sld)) {
			continue;
		}
		
		if (CheckAttribute(pchar, "questTemp.HWIC.TakeQuestShip")) {
			if (sti(realShip.BaseType) == SHIP_MAYFANG || sti(realShip.BaseType) == SHIP_MIRAGE || sti(realShip.BaseType) == SHIP_VALCIRIA) {
				continue;
			}
		}
		
		questShips[questShipsNum] = sti(sld.index);
		questShipsNum++;
	}
	
	return (questShipsNum > 0);
}

void ChickenGod_AddOfficerLink(aref link, string prefix, string id) {
	if (GetCharacterIndex(id) < 0) {
		return;
	}
	
	if (!CheckPassengerInCharacter(pchar, id)) {
		return;
	}
	
	if (id == "Mary" && !CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) {
		return;
	}
	
	if (id == "Helena" && !CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) {
		return;
	}
	
	sld = CharacterFromID(id);
	
	if (!GetRemovable(sld)) {
		return;
	}
	
	link.(id) = GetFullName(sld) + ".";
	link.(id).go = prefix + id;
}

bool ChickenGod_TalkedToAmelia() {
	if (GetCharacterIndex("Amelia") < 0) {
		return false;
	}
	
	sld = CharacterFromID("Amelia");
	if (sld.dialog.currentnode == "amelia") {
		return false;
	}
	
	return true;
}

bool ChickenGod_HaveOfficers() {
	object fakelink;
	
	ChickenGod_AddOfficerLink(&fakelink, "", "Duran");
	ChickenGod_AddOfficerLink(&fakelink, "", "Baker");
	ChickenGod_AddOfficerLink(&fakelink, "", "Folke");
	ChickenGod_AddOfficerLink(&fakelink, "", "Avendel");
	ChickenGod_AddOfficerLink(&fakelink, "", "Tonzag");
	if (!CheckAttribute(pchar, "questTemp.PZ_LongwayNelzyaOtdatArube")) ChickenGod_AddOfficerLink(&fakelink, "", "Longway");
	ChickenGod_AddOfficerLink(&fakelink, "", "Knippel");
	ChickenGod_AddOfficerLink(&fakelink, "", "Tichingitu");
	ChickenGod_AddOfficerLink(&fakelink, "", "Irons");
	
	if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6.gf")) {
		ChickenGod_AddOfficerLink(&fakelink, "", "Helena");
		ChickenGod_AddOfficerLink(&fakelink, "", "Mary");
	}
	
	return (GetAttributesNum(&fakelink) > 0);
}

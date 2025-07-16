//Jason общий диалог цыганок
// ugeen <-- добавил продажу мышьяка из под полы
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	int poison_price;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Ah hello, darling. What do you want?";
			link.l1 = "Nothing I suppose.";
			link.l1.go = "exit";
			link.l2 = RandPhraseSimple("I have got a question for you.", "I need information.");
			link.l2.go = "quests";//(перессылка в файл города)
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = LinkRandPhrase("Darling, would you be kindly to share some gold? I'll tell you your future.","Hey, sailor, don't hurry like that! Do you want to know the future?","Give me some tobacco and a few silver coins, brave young man. And I will take a look at your future. (wink) Want to hear some secret gypsy magic?");
				link.l1 = "Sorry, but I have to go.";
				link.l1.go = "exit";
				// --> мангароса
				if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "gipsy" && !CheckAttribute(npchar, "quest.mangarosa"))
				{
					link.l5 = "Listen tinker lady, I know that your people are experts in potions and poisons. I was told that you could be interested in this plant. Take a look. What do you think?";
					link.l5.go = "mangarosa";
				}
				if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "gipsy_trade" && !CheckAttribute(npchar, "quest.mangarosa"))
				{
					link.l5 = "Hey, dark-eyes, I've got something for you... This is mangarosa. Want to buy some??";
					link.l5.go = "mangarosa_trade1";
				}
				// <-- мангароса
				link.l2 = "Can you tell fortunes for me?";
				link.l2.go = "guess";
				link.l3 = RandPhraseSimple("I have got a question for you.", "I need information.");
				link.l3.go = "quests";//(перессылка в файл города)
				npchar.quest.meeting = "1";
			}
			// --> Тёмные воды исцеления
			if (CheckAttribute(pchar, "questTemp.DWH_Start") && !CheckAttribute(pchar, "questTemp.DWH_gipsy") && npchar.city == "SentJons")
			{
				link.l6 = "I'm looking for a gypsy woman who tends to the sick. Would that be thee?";
				link.l6.go = "dwh_ne_ta";
			}
			// <-- Тёмные воды исцеления

			if (!CheckAttribute(npchar, "quest.poison_price") && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && rand(2) == 0)
			{
				link.l4 = "Hey, dark-eyes, do you have any poisons for rats? They're being a damn nuisance on my ship.";
				link.l4.go = "get_poison_1";
			}
			NextDiag.TempNode = "First time";
		break;

//-------------------------------------------------гадание-------------------------------------------------
		case "guess":
			dialog.text = "Of course, handsome. Give me some coins and show me your right hand. I'll tell you about your future and help you avoid disaster. I never cheat! Money back guarantee!";
			link.l1 = "I feel like this is the part where your compatriot picks my pocket...I changed my mind. I am not in the mood.";
			link.l1.go = "exit";
			link.l2 = "How much money do you want?";
			link.l2.go = "guess_1";
		break;
		
		case "guess_1":
			dialog.text = "Ah dear, as much as your coinpurse allows and your heart desires. The more pieces of eight, the further into the future I can see!";
			link.l1 = "100 pesos";
			link.l1.go = "guess_rate_1";
			link.l2 = "500 pesos";
			link.l2.go = "guess_rate_2";
			link.l3 = "1000 pesos";
			link.l3.go = "guess_rate_3";
			link.l4 = "5000 pesos";
			link.l4.go = "guess_rate_4";
		break;
		
		sTemp = GuessText();
		case "guess_rate_1"://никаких плюшек
			if (sti(pchar.money) >= 100)
			{
				AddMoneyToCharacter(pchar, -100);
				dialog.text = "Ah, thanks you for your charity, my handsome young falcon! Now listen:  "+sTemp+"";
				link.l1 = LinkRandPhrase("Heh! That's very interesting. I'll consider that...","Really? I'll consider that...","Oh, really? Are you serious? I'll remember that...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "The ugliest and the unavoidable misfortune is waiting for you. Curse the mocker! Let dark clouds to gather upon you and let punishment find you!";
				link.l1 = "Ha-ha! Did you really think I would give you money, you gypsy witch? Get out of my way! I hope the Inquistiion takes you!";
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_rate_2"://немного в везение или скрытность
			if (sti(pchar.money) >= 500)
			{
				AddMoneyToCharacter(pchar, -500);
				dialog.text = "Ah, thank you, my handsome  young falcon! Now listen:"+sTemp+"";
				link.l1 = LinkRandPhrase("Heh! That's very interesting. I'll consider that...","Really? I'll consider that...","Oh, really? Are you serious? Well, I'll remember that...","Hey, I feel better already!");
				link.l1.go = "exit";
				if (hrand(1) == 0) AddCharacterExpToSkill(pchar, "Fortune", 30+rand(10));//везение
				else AddCharacterExpToSkill(pchar, "Sneak", 30+rand(10));//скрытность
			}
			else
			{
				dialog.text = "The ugliest and the unavoidable misfortune is waiting for you. Curse the mocker! Let dark clouds to gather upon you and let punishment find you!";
				link.l1 = "Ha-ha! Did you really think I would give you money, you gypsy witch? Get out of my way! I hope the Inquistiion takes you!";
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_rate_3"://здоровье + везение или скрытность, харизма
			if (sti(pchar.money) >= 1000)
			{
				AddMoneyToCharacter(pchar, -1000);
				dialog.text = "Ah, thanks for your silver, my handsome young falcon! Now listen:"+sTemp+"";
				link.l1 = LinkRandPhrase("Heh! That's very interesting. I'll consider that...","Really? I'll consider that...","Oh, really? Are you serious? Well, I'll remember that...");
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 1);
				AddCharacterExpToSkill(pchar, "Leadership", 20);
				if (hrand(1) == 0) AddCharacterExpToSkill(pchar, "Fortune", 50+rand(20));//везение
				else AddCharacterExpToSkill(pchar, "Sneak", 50+rand(20));//скрытность
			}
			else
			{
				dialog.text = "The ugliest and the unavoidable misfortune is waiting for you. Curse the mocker! Let dark clouds to gather upon you and let punishment find you!";
				link.l1 = "Ha-ha! Did you really think I would give you money, you gypsy witch? Get out of my way! I hope the Inquistiion takes you!";
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_rate_4"://умения в оружие, везение+скрытность, здоровье, харизма
			if (sti(pchar.money) >= 5000)
			{
				AddMoneyToCharacter(pchar, -5000);
				dialog.text = "Oh la la! Thank you for your generosity, my handsome young falcon! Now listen:"+sTemp+"";
				link.l1 = LinkRandPhrase("Heh! That's very interesting. I'll consider that...","Really? I'll consider that...","Oh, really? Are you serious? Well, I'll remember that...");
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 2);
				AddCharacterExpToSkill(pchar, "Leadership", 40);
				AddCharacterExpToSkill(pchar, "Fortune", 50+rand(100));//везение
				AddCharacterExpToSkill(pchar, "Sneak", 50+rand(50));//скрытность
				AddComplexSelfExpToScill(20, 20, 20, 20);
			}
			else
			{
				dialog.text = "The ugliest and the unavoidable misfortune is waiting for you. Curse the mocker! Let dark clouds to gather upon you and let punishment find you!";
				link.l1 = "Ha-ha! Did you really think I would give you money, you gypsy witch? Get out of my way! I hope the Inquistiion takes you!";
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_exit":
			DialogExit();
			AddCharacterHealth(pchar, -10);
			LAi_CharacterDisableDialog(npchar);
		break;
//<-- гадание

// --> продажа мышьяка
		case "get_poison_1" :
			npchar.quest.poison_price = (hrand(3) + 1) * 10;
			if(hrand(10) == 3 || IsCharacterPerkOn(pchar, "Trustworthy"))
			{				
				dialog.text = LinkRandPhrase("Oh, I am not sure, handsome! There was a fellow not long ago asking for help in killing rats and then someone poisoned the soldiers in the fort. It got pretty hot for my people on the island while the guards interrogated us for two weeks until they found the murderer. He was an enemy spy.",
				                             "And how can I be sure of your purpose? Maybe you just want to poison a nobleman who you are too cowardly to fight in an honorable duel??",
											 "I've been told that someone had poisoned some tradesman in the tavern and had stole all of his belongings. The man suffered for a long time before expiring. The foam came out from his mouth and he turned purple like an aubergine.. Are you responsible for that, my love?");
				link.l1 = "You gypsy wenches certainly like to share your opinions! Don't worry lass, I am not going to poison people. That's a womanish way to kill, not my style. For men I have my sword, but I can't handle those accursed rats.";
				link.l1.go = "get_poison_2";
				if (IsCharacterPerkOn(pchar, "Trustworthy")) notification("Trustworthy", "Trustworthy");
			}
			else
			{
				dialog.text = "You're trying to entrap me! No sir, I don't have any poison. I've got plants and potions, but no poisons.";
				link.l1 = "Whatever then. Don't put the evil eye on me.";
				link.l1.go = "exit";
				notification("Perk Check Failed", "Trustworthy");
			}	
		break;
		
		case "get_poison_2" :
			dialog.text = "Oh handsome such a gallant man! (whispering) Pay me "+sti(npchar.quest.poison_price)+" doubloons.";
			if (PCharDublonsTotal() >= sti(npchar.quest.poison_price))
			{				
				link.l1 = "Pricy... This stuff better work.";
				link.l1.go = "get_poison_4";
			}
			else
			{
				link.l1 = "No way! I bought the same back home for five pistoles! I could catch every rat myself for that much money!";
				link.l1.go = "get_poison_3";
			}
		break;
		
		case "get_poison_3" :
			dialog.text = "Catch them yourself then and don't bother me. I will call the guard next time.";
			link.l1 = "No need for the guards witch, I am leaving.";
			link.l1.go = "exit";
		break;
		
		case "get_poison_4" :
			PlaySound("interface\important_item.wav");
			RemoveDublonsFromPCharTotal(sti(npchar.quest.poison_price));
			TakeNItems(pchar, "rat_poison", 1);
			DialogExit();
		break;
// <-- продажа мышьяка

	// --> Мангароса
		case "mangarosa":
			dialog.text = LinkRandPhrase("Show me the plant, dear... Hm... I suppose that I can buy it from you. Three hundred pieces of eight, agree?","Show me to it, handsome... Heh... Well, I can pay two hundred and a half for it.","Let's see... Oh! An interesting example! Two hundred pesos! Deal?")"";
			link.l1 = LinkRandPhrase("Oh Lord... dark-eyes, I am not some country bumpkin. I know this plant. It is mangarosa...","Oh, really?! This is a perfect specimen of mangarosa. Don't try to cheat me, gyppo.","Aha, and you suppose that I will give you this mangarosa for such a paltry sum.");
			link.l1.go = "mangarosa_1";
		break;
		
		case "mangarosa_1":
			dialog.text = "Fine, fine, handsome. I see that you know something about this plant. Fifty doubloons. Give it to me.";
			link.l1 = "Hold on now! I want to know how it can be used and what for. Can you tell me about that? All of your people are willing to pay a lot of gold for this little shrub!";
			link.l1.go = "mangarosa_2";
		break;
		
		case "mangarosa_2":
			// тут работает харизма
			if (sti(pchar.questTemp.Mangarosa.g_count) == 5 || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 10+hrand(25)+hrand(30, "1"))
			{
				dialog.text = "Hm... I suppose that it's not too bad if I tell you a bit about it. You won't be able to do anything with this plant without special skills.";
				link.l1 = "I am listening.";
				link.l1.go = "mangarosa_3";
			}
			else
			{
				dialog.text = LinkRandPhrase("My people might pay a lot of gold but they would never expose their secrets.","Gold is gold and secrets are secrets, young man... ","Aye, we are willing to pay but not to tell.")+"So are you going to sell me your mangarosa? Fifty doubloons is our going rate for it, no one will pay you more.";
				link.l1 = "Oh, fine... It works for me anyway. Fifty doubloons. Take it";
				link.l1.go = "mangarosa_trade";
				link.l2 = "Understand me, I don't want to sell it. I want to know why do you need it. Share your knowledge with me and I will give it to you for free.";
				link.l2.go = "mangarosa_exit";
			}
		break;
		
		case "mangarosa_trade":
			RemoveItems(pchar, "cannabis7", 1);
			TakeNItems(pchar, "gold_dublon", 50);
			PlaySound("interface\important_item.wav");
			dialog.text = "Take your coins, young falcon. And one more thing, bring us more of these plants. But we can buy them only by one plant because we don't carry big sums with us. The guards don't trust our kind and like pestering us...";
			link.l1 = "Fine. If I find more, I'll bring it.";
			link.l1.go = "mangarosa_trade_exit";
		break;
		
		case "mangarosa_trade_exit":
			DialogExit();
			npchar.quest.mangarosa = "true";
			DeleteAttribute(pchar, "questTemp.Mangarosa.g_count");
			pchar.questTemp.Mangarosa = "gipsy_trade";
			AddQuestRecord("Mangarosa", "3");
		break;
		
		case "mangarosa_exit":
			dialog.text = LinkRandPhrase("No way! If you don't want to sell it - don't do so then. I won't tell you a thing.","I won't expose our secrets to a gorger outsider! (spits) Don't want to sell it? To hell with you.","Friend, that is not for your ears. Don't want to sell it for fifty doubloons? Go and sell it to the trade girl for two hundred pesos.");
			link.l1 = LinkRandPhrase("Too bad for you then! Another one of your people will tell me about it anyway. And she will get this plant as a present. See you!","Why so stubborn? If you won't tell me then the other does. And she will get this mangarosa as a present. Farewell.","Your breath stinks of garlic. I will get what I want eventually. Another of your race will be more talkative and will get the plant for free. See you.");
			link.l1.go = "exit";
			npchar.quest.mangarosa = "true";
			pchar.questTemp.Mangarosa.g_count = sti(pchar.questTemp.Mangarosa.g_count)+1;
		break;
		
		case "mangarosa_trade1":
			dialog.text = "And why do you ask, falcon?! Sure! Give it to me.";
			link.l1 = "Give me fifty doubloons.";
			link.l1.go = "mangarosa_trade1_1";
			link.l2 = "Oups! It seems that I've lost it or forgotten on my ship. Such a pity. Bye...";
			link.l2.go = "exit";
			npchar.quest.mangarosa = "true";
		break;
		
		case "mangarosa_trade1_1":
			RemoveItems(pchar, "cannabis7", 1);
			TakeNItems(pchar, "gold_dublon", 50);
			PlaySound("interface\important_item.wav");
			dialog.text = "Don't worry, I won't cheat you. Take your coins.";
			link.l1 = "Take your mangarosa. I will bring more if I find.";
			link.l1.go = "exit";
		break;
		
		case "mangarosa_3":
			dialog.text = "We grind the buds in this special way, then dry it, pick out the seeds and stems, then mix it with tobacco, tamp our pipes and smoke the mix. And we get an... unforgettable effect. Like intoxication with alcohol, but with no headache after. One plant is enough for two dozens pipefuls.";
			link.l1 = "I see now! Can you teach me this secret technique? I can pay you well...";
			link.l1.go = "mangarosa_4";
		break;
		
		case "mangarosa_4":
			dialog.text = "Young falcon, trust me, you don't need this. Don't get involved, the plant will ruin you. It dulls the brain and makes you fat. Don't even ask me. But... I see a brave man in front of me, with a sword, a man of the sea...even a captain perhaps?";
			link.l1 = "You are right.";
			link.l1.go = "mangarosa_5";
		break;
		
		case "mangarosa_5":
			dialog.text = "Listen here then. Mangarosa can be utilized for much nobler things and you may find it useful. One healer of ours knows all the secrets of it. She is the one you need\nGive me the plant and I will tell you her name and where to find her. Convincing her to share her secrets with you will be your problem though.";
			link.l1 = "Fine. Take the plant and tell me how to find your gypsy magician.";
			link.l1.go = "mangarosa_6";
		break;
		
		case "mangarosa_6":
			RemoveItems(pchar, "cannabis7", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Her name is Amelia. She lives alone in a small house among the dunes not far from the sea, somewhere on the south-west coast of the Spanish Main as the wise folks say.";
			link.l1 = "Oh for God's sake, can you please be more specific?";
			link.l1.go = "mangarosa_7";
		break;
		
		case "mangarosa_7":
			dialog.text = "You are a sailor, brave falcon, and I am not. Look for her where I said. Her home is really close to the seacoast. It is nearby a bay right on the south-west of the Spanish Main - sailors must know it.";
			link.l1 = "Alright, I'll try to find it...";
			link.l1.go = "mangarosa_8";
		break;
		
		case "mangarosa_8":
			dialog.text = "Take a Mangarosa to her or she won't even talk to you. And don't forget about bringing doubloons either, don't even think that she will teach you for free!";
			link.l1 = "Such avarice. I'll consider that. Thanks for your story!";
			link.l1.go = "mangarosa_9";
		break;
		
		case "mangarosa_9":
			DialogExit();
			npchar.quest.mangarosa = "true";
			DeleteAttribute(pchar, "questTemp.Mangarosa.g_count");
			pchar.questTemp.Mangarosa = "amelia";
			pchar.questTemp.Mangarosa.Tell = "true"; // калеуче
			AddQuestRecord("Mangarosa", "4");
			// создаем и ставим Амелию
			sld = GetCharacter(NPC_GenerateCharacter("Amelia", "gipsy_3", "woman", "towngirl", 10, PIRATE, -1, true, "citizen"));
			SetFantomParamFromRank(sld, 10, true);
			sld.name = "Amelia";
			sld.lastname = "";
			sld.dialog.FileName = "Quest\Mangarosa.c";
			sld.dialog.currentnode = "amelia";
			//sld.greeting = "";
			LAi_SetOwnerType(sld);
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "Amelia_house", "barmen", "stay");
		break;
		
		// --> Тёмные воды исцеления
		case "dwh_ne_ta":
			sld = CharacterFromID("DWH_gypsy");
			dialog.text = "No, " + GetSexPhrase("dear", "beauty") + ", I'm not the one you need, it's " + sld.name + ". She's here in the city right now. I saw her recently.";
			link.l1 = "Thank you.";
			link.l1.go = "exit";
		break;
		// <-- Тёмные воды исцеления
		
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar, "Listen to me brave falcon, I may be a gypsy but even we decry open violence. Please sheathe your sword.", "Listen to me brave falcon, as a citizen of this town I'm asking you to sheathe your blade.");
			link.l1 = LinkRandPhrase("Fine.", "As you wish.", "As you say...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

string GuessText()
{
	string sText;
	switch (hrand(19))
	{
		case 0: sText = "you will have luck, brave young falcon, tomorrow you'll be lucky with cards!" break;
		case 1: sText = "the fortune will be kind with you in your mercantile business, captain!" break;
		case 2: sText = "there is a misfortune awaiting you in the open sea, it's waiting just for you, wait for three days!" break;
		case 3: sText = "I see that you need to seek help from your closest ones, you won't make it alone in your next fight!" break;
		case 4: sText = "go and light a candle in a church, you have been cursed by your enemy. You won't make it without God's help!" break;
		case 5: sText = "you are going to lose a lot soon, my falcon, but don't despair and hope for yourself, seek help from you friends..." break;
		case 6: sText = "a heavy loss is waiting for you in the sea, but I see, that you, captain, will be able to ride it out even if you don't get what you want." break;
		case 7: sText = "you have entered the aim of misfortune, captain! Visit a brothel and have some rest." break;
		case 8: sText = "you will get what you want, captain, but don't expect anything good from it. All what you've wanted so passionately, captain, will bring only bad things so you'd better change your plans away." break;
		case 9: sText = "I see that there is a sign on that face of yours, the sign of ultimate luck. You will get more than you're expecting to get, young man!" break;
		case 10: sText = "you need to evaluate your wish once again and decide. Do you really need it? Your fate is giving you a chance to rethink." break;
		case 11: sText = "it's rare luck, not everyday we've getting a chance to rethink. Take a rest for a few days, bright-eyed, think about things. Don't hurry to your death!" break;
		case 12: sText = "though all of your efforts won't give you the expected result, don't despair, young falcon, great luck is waiting for you in the most unexpected day, don't lose it!" break;
		case 13: sText = "your problem won't be solved in a positive way but you are a stubborn one and you'll get what you want but, perhaps, not from the place you've expected." break;
		case 14: sText = "you'd better forget about the business you are up to. You will never be lucky in this and if you'll be continuing in it than, perhaps, your closest people will be hurt or killed." break;
		case 15: sText = "there is an event which is waiting for you, captain, and it will completely change your life. Your recent concerns will lose all of their meaning to you after that." break;
		case 16: sText = "there is danger on your way to your dream, captain, and you must be really lucky if you will be able to get what you want without heavy losses. It's better to turn away and forget your unachievable dream. Or perhaps, this fate could be tricked if you lose in cards or dice right now..." break;
		case 17: sText = "I see a strong power in you like a rock and a light as bright as the north star which leads people. Good news is waiting for you!" break;
		case 18: sText = "a bad sign is rising on your way, fear the evil eye and keep loyal men close to you." break;
		case 19: sText = "a lucky event is rising on your way right behind your own back. Look for the good which is coming right to your hands and don't chase the unachievable." break;
	}
	return sText;
}

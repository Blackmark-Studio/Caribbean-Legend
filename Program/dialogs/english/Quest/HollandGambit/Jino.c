// Джино Гвинейли - алхимик
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			// --> Страж истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "jino1")
			{
				dialog.text = "Oh! Good day, sir. How did you get here?";
				link.l1 = "Good day, Gino. Let's get to know each other. I am Captain "+GetFullName(pchar)+" and I am here with John's permission. Let me make this clear - I need your help, but I can also help you.";
				link.l1.go = "guardoftruth_0";
				npchar.quest.meeting = "1";
				DelLandQuestMark(npchar);
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Oh! Good day, sir. How did you get here? And where is John?";
				link.l1 = "Well, well... So that's who was always hiding behind this closed door! Interesting... About John... He's gone. And this house is mine now. But don't worry. Let's get to know each other. Who are you, and what are you doing here?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
				DelLandQuestMark(npchar);
			}
			else
			{
				// --> Страж истины
				if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "threeitems")
				{
					dialog.text = "Hello, "+pchar.name+". Your face tells me you've found something important. Have you gathered all the components of the Guardian of Truth?";
					link.l1 = "Exactly! I have all three items with me: the dagger, the map, and the compass!";
					link.l1.go = "guardoftruth_34";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "jino")
				{
					dialog.text = "Hello, "+pchar.name+". What happened? You have a strange look on your face...";
					link.l1 = "I have something to discuss with you, Gino. It's important.";
					link.l1.go = "guardoftruth";
					break;
				}
				// Ксочитэм
				if (CheckAttribute(pchar, "questTemp.Ksochitam") && pchar.questTemp.Ksochitam == "begin")
				{
					dialog.text = TimeGreeting()+", "+pchar.name+". Yes, I remember, two days have passed and you want to know about the Guardian of Truth, am I right?";
					link.l1 = "Yes, you are! Were you able to dig up anything?";
					link.l1.go = "ksochitam";
					break;
				}
				//--> Португалец
				if (CheckAttribute(pchar, "questTemp.Portugal.Nomoney"))
				{
					dialog.text = "Have you brought 5,000 pesos, "+pchar.name+"?";
					if (sti(pchar.money) >= 5000)
					{
						link.l1 = "Sure. Here, take the money and buy all you need.";
						link.l1.go = "Portugal_3";
						SetFunctionTimerCondition("Portugal_TreatmentOver", 0, 0, 1, false);
						DeleteAttribute(pchar, "questTemp.Portugal.Nomoney");
						pchar.quest.Portugal_Ill1.over = "yes";
						pchar.quest.Portugal_Ill.win_condition.l1 = "Timer";
						pchar.quest.Portugal_Ill.win_condition.l1.date.hour  = sti(GetTime());
						pchar.quest.Portugal_Ill.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 7);
						pchar.quest.Portugal_Ill.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 7);
						pchar.quest.Portugal_Ill.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 7);
						pchar.quest.Portugal_Ill.function = "Portugal_ToAntiguaOver";
					}
					else
					{
						link.l1 = "Unfortunately, I don't have the money on me at the moment.";
						link.l1.go = "Portugal_nomoney";
					}
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal.Die"))
				{
					dialog.text = "Alas, "+pchar.name+", I am very sorry - the patient is dead. He suddenly got worse and passed away very quickly.";
					link.l1 = "Too bad... May God have mercy on his soul!";
					link.l1.go = "exit";
					DeleteAttribute(pchar, "questTemp.Portugal.Die");
					pchar.quest.Remove_Avendel.win_condition.l1 = "Location_Type";
					pchar.quest.Remove_Avendel.win_condition.l1.location_type = "town";
					pchar.quest.Remove_Avendel.function = "RemoveAvendelnDoc";
					AddQuestRecord("Portugal", "6");
					CloseQuestHeader("Portugal");
					pchar.questTemp.Portugal = "end";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "ToAntigua")
				{
					dialog.text = "Hello, "+pchar.name+". Has something happened? You look very worried...";
					link.l1 = "Gino, I have an unusual request for you! There is a man with a high fever on my ship. He is delirious and unconscious... can you help him?";
					link.l1.go = "Portugal";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "Portugal_wait")
				{
					dialog.text = ""+pchar.name+", I am waiting for the patient. Hurry up, the sooner you bring him here, the better his chances are that I will be able to save him.";
					link.l1 = "Yes, yes, he will be brought here at once.";
					link.l1.go = "exit";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "TreatmentStart")
				{
					dialog.text = "You have brought him just in time, "+pchar.name+". He is in critical condition, yet there is still a chance.\nCaptain, I am running out of ingredients and we don't have time to gather them in the jungle. I must buy them all from the local herbalists for 5,000 pesos. Can you provide the sum?";
					if (sti(pchar.money) >= 5000)
					{
					link.l1 = "Sure. Here, take the money and buy all you need.";
					link.l1.go = "Portugal_3";
					SetFunctionTimerCondition("Portugal_TreatmentOver", 0, 0, 1, false);
					}
					else
					{
						link.l1 = "Unfortunately,  I don't have the money right now.";
						link.l1.go = "Portugal_nomoney";
						pchar.quest.Portugal_Ill.over = "yes";
						pchar.quest.Portugal_Ill1.win_condition.l1 = "Timer";
						pchar.quest.Portugal_Ill1.win_condition.l1.date.hour  = sti(GetTime());
						pchar.quest.Portugal_Ill1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
						pchar.quest.Portugal_Ill1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
						pchar.quest.Portugal_Ill1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
						pchar.quest.Portugal_Ill1.function = "Portugal_ToAntiguaOver";//не принесёт через 1 день - Португальцу капут
					}
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "TreatmentCurrent")
				{
					dialog.text = "I have nothing to say now, "+pchar.name+". I am fighting for the patient's life. There is still some hope. Come and see me later, I suppose I will be able to tell you something more specific soon.";
					link.l1 = "Fine, Gino, I will be back later.";
					link.l1.go = "exit";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "TreatmentFinish")
				{
					pchar.quest.Portugal_Ill.over = "yes";
					dialog.text = "I have news,"+pchar.name+". I won't say your man is alright, but he lives. The illness is receding and there is progress to be seen. To be honest, I didn't expect my potions would help him so much.";
					link.l1 = "That's great news, Gino, but tell me, when will I be able to take him? We have a long way to sail and the clock is ticking.";
					link.l1.go = "Portugal_4";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "TreatmentComplete")
				{
					dialog.text = "Good day, Captain. Glad to see you.";
					link.l1 = "How is our patient, Gino?";
					if (GetQuestPastDayParam("questTemp.Portugal_threedays") > 2) link.l1.go = "Portugal_9";
					else link.l1.go = "Portugal_threedays";
					break;
				}
				// <--Португалец
				dialog.text = "Good day, Captain. How are you doing? Need my help?";
				if (!CheckAttribute(npchar, "quest.rome"))
				{
					link.l1 = "Yes. Gino, I take it that you are an erudite man, and perhaps you might even know Latin...";
					link.l1.go = "rome";
				}
				if (CheckCharacterItem(pchar, "chemistry"))
				{
					link.l2 = "I have something different. A small present for you. Here, take a look at this book.";
					link.l2.go = "chemistry";
				}
				if (CheckAttribute(npchar, "quest.colt") && CheckCharacterItem(pchar, "pistol7"))
				{
					link.l2 = "Yes, Gino. I want to show you this pistol. Have you ever seen anything like it?";
					link.l2.go = "colt";
				}
				if (CheckAttribute(npchar, "quest.sample") && CheckCharacterItem(pchar, "pistol7") && CheckCharacterItem(pchar, "GunCap_colt") && CheckCharacterItem(pchar, "shotgun_cartridge"))
				{
					link.l2 = "I have brought you a sample of the charge for my pistol.";
					link.l2.go = "colt_1";
				}
				if (CheckAttribute(npchar, "quest.cartridge"))
				{
					link.l2 = "What about the charges for the pistol? Got any clues yet?";
					link.l2.go = "cartridge";
				}
				// Addon 2016-1 Jason Пиратская линейка
				if (CheckAttribute(pchar, "questTemp.Mtraxx.Gord"))
				{
					link.l3 = "Gino, I've found the word 'gord'—which is unfamiliar to me—in a captain's log. Do you know what it means?";
					link.l3.go = "mtraxx";
				}
				link.l9 = "Good day, Gino. I am doing well, no help is needed. Just wanted to check in on you and talk a bit.";
				link.l9.go = "exit";	
			}
			NextDiag.TempNode = "First time";
		break;

		case "meeting":
			pchar.questTemp.HWIC.Jino = "true"; // Addon 2016-1 Jason Пиратская линейка
			dialog.text = "My name is Gino. Gino Gvineili. I am a scientist. My job is to make powders, mixtures, and other medicines for Mister Murdock. But since he is gone...";
			link.l1 = "Well, I am "+GetFullName(pchar)+". A captain of my own ship. So, you're an alchemist then?";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Not only am I an alchemist, but also a physician. I possess considerable knowledge of medicine. I know much about healing herbs, and I am able to brew mixtures and potions from them. But chemistry is my true calling; I do a great deal of experimenting, and some of my inventions might be of use to people like you.\nI know Latin, French, English, and Italian. My help will be indispensable if you are planning to run a drugstore as Mister Murdock did...";
			link.l1 = "Oho! It's not every day you meet such an erudite man. The pharmacy business is fine, to be sure, but I am a sailor... hm, that sounds strange even to me... Anyway, I am sure we will become friends, Gino. You can continue living here and doing your science things...";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "";
			link.l1 = "And if I ever need help from an alchemist, a healer, or a scientist - I'll know whom to ask... Tell me, why do you always stay indoors? Don't you ever go outside?";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "I do go outside when I need to buy ingredients or herbs for my experiments. I like living alone, that is my way. I have dedicated my life to science and find no interest in ordinary life. Books, writings, test tubes, retorts...\nMister Murdock gave me such an opportunity in exchange for helping him make drugs.";
			link.l1 = "Now you will have even more time, Gino. But you'll have to give up some of your experiment time if I need your help, deal?";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "Of course, Captain. I shall call you Captain, "+GetAddress_Form(NPChar)+", if you don't mind? I will leave all my research in case you need my practical skills or theoretical knowledge.";
			link.l1 = "Splendid. I am glad that we have understood each other so quickly. Don't worry about your expenses, either I or my purser will leave you reasonable sums from time to time.";
			link.l1.go = "meeting_5";
		break;
		
		case "meeting_5":
			dialog.text = "Thank you, Captain. I don't need much... Captain, I have an idea... why don't you learn some alchemy skills? They might be really useful to you.";
			link.l1 = "Hm. As my brother once told me - don't be squeamish about learning to do things with your own hands. So sure, why not. What can you show me?";
			link.l1.go = "meeting_6";
		break;
		
		case "meeting_6":
			dialog.text = "Well, certainly, you won't be able to turn iron into gold, that's impossible... yet, but you can learn how to mix ingredients according to instructions to create potions or other useful items. Here, take this bag. It contains everything a beginner alchemist will need: test tubes, flasks, retorts, stills, spatulas, glass tubes, a burner, and so on...";
			link.l1 = "Fascinating!";
			link.l1.go = "meeting_7";
		break;
		
		case "meeting_7":
			Log_Info("You have received an alchemist's kit");
			GiveItem2Character(pchar, "alchemy_tool");
			PlaySound("interface\important_item.wav");
			dialog.text = "You must know a recipe in order to make a potion or an item. Recipes can be bought from merchants or found anywhere. Once you have studied a recipe, you should collect every ingredient needed and do exactly what is written there.\n Use your alchemy tools, find or buy a mortar and pestle, look for a crucible—alas, I don't possess an extra one to give you. Herbs, spirits, potions, minerals, rubbish—everything will do, provided you have the right recipe and tools.";
			link.l1 = "I see. I'll try to mix something in my spare time. Thanks, Gino! Can you give me a simple recipe? Something to start with? ";
			link.l1.go = "meeting_8";
		break;
		
		case "meeting_8":
			dialog.text = "I don't have any simple ones... but here, take this antidote recipe. I suppose you are capable of handling this task. Take it.";
			link.l1 = "Thank you! I will learn it. Goodbye now, Gino! Watch over my house, I fear I won't visit this place very often, so you are welcome to use not only your room, but also the rest of the building.";
			link.l1.go = "meeting_9";
		break;
		
		case "meeting_9":
			DialogExit();
			GiveItem2Character(pchar, "recipe_potion4"); // belamour legendary edition
			Log_Info("You have received an antidote recipe");
			PlaySound("interface\notebook.wav");
			Log_Info("You need to have the Alchemy skill in order to craft potions, amulets and items!");
			NextDiag.CurrentNode = "First time";
		break;
		
		case "rome":
			dialog.text = "Yes, Captain, I know the language of the ancient Romans. Every scholar, especially a healer or an alchemist, must know Latin. Do you need my knowledge of Latin?";
			link.l1 = "Yes. Gino, don't take me for a fool but... well, how can I explain...";
			link.l1.go = "rome_1";
		break;
		
		case "rome_1":
			dialog.text = "Speak plainly, Captain. Don't be shy.";
			link.l1 = "Fine. Can you make a list of scholarly Latin aphorisms for me? You see, there is... a man who likes to boast of his 'erudition', and sometimes he uses those Latin phrases to show me my ignorance compared to him. Something like... 'si vis pacem, para bellum'...";
			link.l1.go = "rome_2";
		break;
		
		case "rome_2":
			dialog.text = "'Si vis pacem, para bellum', you mean?";
			link.l1 = "Yes, yes. I want to learn them to beat my arrogant br... my friend.";
			link.l1.go = "rome_3";
		break;
		
		case "rome_3":
			AddQuestRecordInfo("Rome", "1");
			dialog.text = "There is nothing strange or shameful in your request, Captain. Knowing the aphorisms of the ancients who went down in history makes you an educated man. Here, take this text. It is what you have asked for.";
			link.l1 = "Thanks, Gino! I appreciate it! I'll read it in my spare time...";
			link.l1.go = "exit";
			npchar.quest.rome = true;
			NextDiag.TempNode = "First time";
		break;
		
		case "chemistry":
			RemoveItems(pchar, "chemistry", 1);
			Log_Info("You have given Lavoisier's chemistry textbook");
			dialog.text = "Show me... (reading) Impossible! A 'small present', you say? This book is priceless! Where did you get it?! This is... a real treasure!";
			link.l1 = "I am glad that you like it.";
			link.l1.go = "chemistry_1";
		break;
		
		case "chemistry_1":
			dialog.text = "(Reading) Incredible! I've never even heard of that... and this? I don't understand a thing here... but I will, damn it! Oh, soon work will be boiling in my lab! "+pchar.name+", you don't even realise WHAT you have given me...";
			link.l1 = "Why wouldn't I? I do. A scientific book for a scientist...";
			link.l1.go = "chemistry_2";
		break;
		
		case "chemistry_2":
			dialog.text = "But who is the author of this miracle? Antoine-Laurent de Lavoisier, France... Never heard of him. But wait! How is that possible! The year of printing is 1789? But how...";
			link.l1 = "I don't know why that year is written on there either. Well, maybe I do. But I advise you not to think too much about it. The book is useful and that is all that matters.";
			link.l1.go = "chemistry_3";
		break;
		
		case "chemistry_3":
			dialog.text = "It is more promising than I could have hoped, and that year must be a printing mistake of some sort... Whatever. Thank you very much, Captain!";
			link.l1 = "You are welcome, Gino. It is all yours.";
			link.l1.go = "exit";
			if (CheckCharacterItem(pchar, "pistol7"))
			{
				link.l1 = "That is not all, Gino. I want to show you this pistol. Have you ever seen anything like this?";
				link.l1.go = "colt";
			}
			npchar.quest.colt = true;
		break;
		
		case "colt":
			dialog.text = "I am no gunsmith, but I will take a look... No, I have never seen anything like it. Why do you ask?";
			link.l1 = "This pistol is powerful and destructive, but it requires special charges to use. Nothing else will work. And I have no idea how to make more rounds for it. So I came here for your advice.";
			link.l1.go = "colt_1";
		break;
		
		case "colt_1":
			dialog.text = "Have you got at least one round to show me as an example? If you don't, then I'm afraid I won't be able to help.";
			if (CheckCharacterItem(pchar, "GunCap_colt") && CheckCharacterItem(pchar, "shotgun_cartridge"))
			{
				link.l1 = "I do. The charge consists of two parts: the round itself with a bullet, and this thing which ignites the powder.";
				link.l1.go = "colt_2";
			}
			else
			{
				link.l1 = "Such a failure! What a shame! Fine, perhaps I will find more and bring them to you.";
				link.l1.go = "exit";
				npchar.quest.sample = true;
			}
			DeleteAttribute(npchar, "quest.colt");
		break;
		
		case "colt_2":
			RemoveItems(pchar, "pistol7", 1);
			RemoveItems(pchar, "GunCap_colt", 1);
			RemoveItems(pchar, "shotgun_cartridge", 1);
			Log_Info("You have given a revolver's cartridge");
			Log_Info("You have given a capsule");
			PlaySound("interface\important_item.wav");
			dialog.text = "Interesting! That looks simple, there's powder inside, a bullet goes in from above, but it looks a bit strange. And this 'thing'... hm. Powder won't explode without it, right? Curious... Look, Captain, leave all of this to me: the pistol and the charges. Come and see me in a month, I need time to figure it out.";
			link.l1 = "Great! Try to figure out how it works, I really want to fire this pistol.";
			link.l1.go = "colt_3";
		break;
		
		case "colt_3":
			dialog.text = "The main problem is to find out what this substance, which makes the powder explode, is made of. This book will come in handy. I will try to get to the bottom of this.";
			link.l1 = "Fine. Farewell, Gino!";
			link.l1.go = "colt_4";
		break;
		
		case "colt_4":
			DialogExit();
			DeleteAttribute(npchar, "quest.sample");
			SetFunctionTimerCondition("Colt_Timer", 0, 0, 30, false); // таймер
		break;
		
		case "cartridge":
			dialog.text = "Yes, I figured out what the charges for the pistol are made of. I have to give credit to the book you presented me with. It wouldn't have worked without it. But I have to warn you, Captain, it won't be easy to create rounds and capsules for this weapon.";
			link.l1 = "Capsules?";
			link.l1.go = "cartridge_1";
		break;
		
		case "cartridge_1":
			dialog.text = "The capsule is that 'thing' that, as you said, ignites the powder. But let's start from the top. Are you ready?";
			link.l1 = "Yes! I am listening to you very carefully.";
			link.l1.go = "cartridge_2";
		break;
		
		case "cartridge_2":
			AddQuestRecordInfo("Recipe", "shotgun_bullet");
			SetAlchemyRecipeKnown("shotgun_bullet");
			dialog.text = "So, first, you need to craft a special bullet. Ordinary bullets won't work. It must have a special conical shape. You will have to find a mold for such bullets, the bullet mold as I call it. Take ordinary lead bullets, melt them in a crucible, and pour the molten lead into the bullet mold. Let the cast cool and then take the finished bullet out of it.";
			link.l1 = "And where can I find such a bullet mould?";
			link.l1.go = "cartridge_3";
		break;
		
		case "cartridge_3":
			dialog.text = "I don't know, Captain. I'm an alchemist, not a blacksmith. Take this bullet as an example, perhaps you'll figure out what to do.";
			link.l1 = "Fine. Go on...";
			link.l1.go = "cartridge_4";
		break;
		
		case "cartridge_4":
			AddQuestRecordInfo("Recipe", "shotgun_cartridge");
			SetAlchemyRecipeKnown("shotgun_cartridge");
			dialog.text = "Then you have to make a container for the powder. You insert the bullet there. I have written clear instructions for you. Read them carefully and give it a try.";
			link.l1 = "Good...";
			link.l1.go = "cartridge_5";
		break;
		
		case "cartridge_5":
			AddQuestRecordInfo("Recipe", "GunCap_colt");
			SetAlchemyRecipeKnown("GunCap_colt");
			dialog.text = "Now we have to get the capsules. You will need a very thin copper sheet - craft it yourself from a copper nugget. Carve circles in it the same size as the rounds. Then put fulminating silver inside them using wax.";
			link.l1 = "Fulminating silver? What is that?";
			link.l1.go = "cartridge_6";
		break;
		
		case "cartridge_6":
			dialog.text = "I didn't know about it myself, I learnt the secret from your book. It is a white powder that can be made from silver, spirit and nitric acid. It explodes easily from rubbing or shaking, which is why it serves well for firing the gunpowder in your pistol's rounds. An unpleasant thing, it has exploded twice during my tests until I came up with the recipe.";
			link.l1 = "I was lucky to have this book with me!";
			link.l1.go = "cartridge_7";
		break;
		
		case "cartridge_7":
			dialog.text = "Be very careful, this stuff is explosive as hell! I could make some myself, but storing fulminating silver is too dangerous; it's vital that you put it in the capsules right after it's made. I can't craft copper capsules, I'm no blacksmith, as I've told you before.";
			link.l1 = "Fine. Give me the recipe, I'll learn it myself.";
			link.l1.go = "cartridge_8";
		break;
		
		case "cartridge_8":
			AddQuestRecordInfo("Recipe", "OxyHydSilver");
			SetAlchemyRecipeKnown("OxyHydSilver");
			dialog.text = "You are welcome. Follow the recipe precisely and be careful with the order of the process, or you'll be sent sky high with your flasks.";
			link.l1 = "I will be careful.";
			link.l1.go = "cartridge_9";
		break;
		
		case "cartridge_9":
			dialog.text = "Also, take these two flasks. This one contains nitric acid, and this one contains spirit. You will be able to make enough fulminating silver to fill about 20 capsules.";
			link.l1 = "Thank you, Gino!";
			link.l1.go = "cartridge_10";
		break;
		
		case "cartridge_10":
			GiveItem2Character(pchar, "Mineral29");
			GiveItem2Character(pchar, "Mineral28");
			Log_Info("You have received a flask of nitric acid");
			Log_Info("You have received a flask of spirit");
			PlaySound("interface\important_item.wav");
			dialog.text = "Also take your pistol and the sample charge. Good luck, Captain, with your charge crafting. I hope you stay alive and in one piece.";
			link.l1 = "I will do what I can to protect myself. And, Gino, have I told you that you are a genius?";
			link.l1.go = "cartridge_11";
		break;
		
		case "cartridge_11":
			TakeNItems(pchar, "pistol7", 1);
			TakeNItems(pchar, "shotgun_cartridge", 3);
			TakeNItems(pchar, "GunCap_colt", 1);
			dialog.text = "You are making me blush, Captain, I am serious...";
			link.l1 = "Fine. Goodbye, Gino! You are my best alchemist!";
			link.l1.go = "cartridge_12";
		break;
		
		case "cartridge_12":
			DialogExit();
			DeleteAttribute(npchar, "quest.cartridge");
		break;
		
		// Addon 2016-1 Jason Пиратская линейка
		case "mtraxx":
            dialog.text = "Gord, gord... Could you tell me more about the captain? Where is he from?";
			link.l1 = "No idea. Although he was born somewhere in the North, they sometimes called him a Viking.";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
            dialog.text = "A Viking! Yes, yes, I remember, I've read about this in a history book. A gord is a fortified settlement of a free jarl.";
			link.l1 = "A free jarl? Who would that be?";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = "It's a prince of the Northmen. Free jarls with their war bands used to raid and plunder Europe centuries ago on their ships, drakkars. You could call them pirates, I suppose. Gords were their bases and homes, places where they could rest, farm, and feast.";
			link.l1 = "I see. This gord must be his pirate lair then... Thanks, Gino!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekReadLogbookFourth");
		break;
		
	// ----------------------------------------- Португалец ----------------------------------------------------
		case "Portugal":
			dialog.text = "Fever and delusions, you say? That is intriguing. Bring him here immediately! I will see what I can do. But I can't promise you anything if his condition is too severe... Is he your officer?";
			link.l1 = "No, thank God, he is not. Gino, listen, don't ask who he is, just do what you can, it's really important to me!";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "All right, bring him into the house to your room. I will prepare some mixtures... perhaps this root will...";
			link.l1 = "I am going to bring him here immediately!";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			DialogExit();
			PChar.quest.Portugal_DoctorPodhodit.win_condition.l1 = "location";
			PChar.quest.Portugal_DoctorPodhodit.win_condition.l1.location = "SentJons_HouseF3";
			PChar.quest.Portugal_DoctorPodhodit.function = "Portugal_DoctorPodhodit";
		break;
		
		case "Portugal_nomoney":
			dialog.text = "Then try to find it as soon as possible, I won't be able to heal him without medicine and it might be too late if you don't hurry.";
			link.l1 = "Fine, I will find the money.";
			link.l1.go = "exit";
			pchar.questTemp.Portugal.Nomoney = "true";
		break;
		
		case "Portugal_3":
			AddMoneyToCharacter(pchar, -5000);
			dialog.text = "Splendid, Captain. Now I will prepare some mixtures, and I recommend you leave my patient. Come back here tomorrow.";
			link.l1 = "Fine, Gino. I trust your mixtures and your genius.";
			link.l1.go = "exit";
			pchar.questTemp.Portugal = "TreatmentCurrent";
			//pchar.GenQuest.CannotWait = true;//запрет ожидания
		break;
		
		case "Portugal_4":
			dialog.text = "Well, I think he will be fine in two weeks. I can't promise that he'll be able to dance, but at least he'll be able to stand on his own feet, that's for sure.";
			link.l1 = "Damn it, I don't have two weeks! I need... to set sail as soon as possible!";
			link.l1.go = "Portugal_5";
		break;
		
		case "Portugal_5":
			dialog.text = "Captain, I am not a mage, but I can assure you that the man is too weak for now. I am not sure he will survive even a few days on the ship; you can't move him!";
			link.l1 = "Fine, fine, but two weeks—no, even one week is too much!";
			link.l1.go = "Portugal_6";
		break;
		
		case "Portugal_6":
			dialog.text = "Three days... yes, I suppose in three days you may try to sail, but he will need care and medicine and you will have to make stops.";
			link.l1 = "I have a doctor, he will take care of him. I will be back in three days and we will take him, it is the most I can afford. We have to move, even with stops... yes, and one more thing - Gino, you are a genius!";
			link.l1.go = "Portugal_7";
		break;
		
		case "Portugal_7":
			dialog.text = "Thank you, Captain. Come back for your friend in three days, but don't disturb him until then. He needs complete rest.";
			link.l1 = "Fine, I got it. I'll take him in three days.";
			link.l1.go = "Portugal_8";
		break;
		
		case "Portugal_8":
			DialogExit();
			SaveCurrentQuestDateParam("questTemp.Portugal_threedays");
			pchar.quest.Portugal_Ill2.win_condition.l1 = "Timer";
			pchar.quest.Portugal_Ill2.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Portugal_Ill2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 5);
			pchar.quest.Portugal_Ill2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 5);
			pchar.quest.Portugal_Ill2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 5);
			pchar.quest.Portugal_Ill2.function = "Portugal_ToAntiguaOver";//чтобы не тянул
			pchar.questTemp.Portugal = "TreatmentComplete";
			pchar.quest.Avendel_room.win_condition.l1 = "location";
			pchar.quest.Avendel_room.win_condition.l1.location = "SentJons_HouseF3";
			pchar.quest.Avendel_room.function = "AvendelSpeach";
		break;
		
		case "Portugal_threedays":
			dialog.text = "He is doing well, but progress is slow. He can't be taken yet.";
			link.l1 = "Yes - yes, Gino, I remember. Three days...";
			link.l1.go = "exit";
		break;
		
		case "Portugal_9":
			pchar.quest.Portugal_Ill2.over = "yes";
			dialog.text = "No deterioration, but he hasn't really improved either. He is still unconscious, he doesn't understand where he is or why he is here, though it doesn't seem to trouble him much. He still has a fever, so I am not sure that taking him aboard now is a good idea.";
			link.l1 = "I can't wait any longer, we've been here for too long already. Pack your mixtures that will help him on the voyage and we're leaving. I hope this bastard is strong enough to survive long enough to face his death sentence...";
			link.l1.go = "Portugal_10";
		break;
		
		case "Portugal_10":
			dialog.text = "Wait, Captain! Have I been treating the condemned? What the hell? A huge amount of work was done here, do you have any idea how difficult it is to make dry powder...";
			link.l1 = "Gino, you didn't need to know that. Don't worry too much, he is a pirate and one of the most notorious of his kind. I have to take him to Curacao for a meeting with the Company's authorities as soon as possible. Period.";
			link.l1.go = "Portugal_11";
		break;
		
		case "Portugal_11":
			dialog.text = "Fine, you know better. Pirate then... Curaçao. Whatever, but listen to me, he will be sleeping most of the time, but the ship's rolling and the stifling heat can set back the whole process. I recommend making a stop after a few days of sailing and letting your... prisoner rest on land. Otherwise, there's a risk you'll be hanging a corpse in Curaçao... ";
			link.l1 = "Fine, I'll do that. Martinique will do fine, it is almost halfway to Curaçao. I hope that the wind will be fair. I am going to take him now and we will leave. Thank you again, Gino.";
			link.l1.go = "Portugal_12";
		break;
		
		case "Portugal_12":
			dialog.text = "You are welcome, Captain. Remember that you have four days—well, five, but no more. And one last thing... you know, I usually heal people not because I want them to be hanged after my treatment. A doctor is responsible for his patients, no matter who they are. And I am feeling really bad...";
			link.l1 = "I am sorry for dragging you into all of this, but we had no chance without you. We have to set sail now or the Portuguese lads will manage to assemble at our doors to meet their boss.";
			link.l1.go = "Portugal_13";
		break;
		
		case "Portugal_13":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "SentJons_HouseF3_Room", "goto", "goto2", "Portugal_JinoNorm", -1);//Джино в свою комнату
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			pchar.quest.Portugal_Ill3.win_condition.l1 = "Timer";
			pchar.quest.Portugal_Ill3.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Portugal_Ill3.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 5);
			pchar.quest.Portugal_Ill3.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 5);
			pchar.quest.Portugal_Ill3.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 5);
			pchar.quest.Portugal_Ill3.function = "Portugal_ToAntiguaOver";//5 дней до Мартиники
			pchar.questTemp.Portugal = "ToMartinique";
			pchar.quest.Avendel_room1.win_condition.l1 = "location";
			pchar.quest.Avendel_room1.win_condition.l1.location = "SentJons_HouseF3";
			pchar.quest.Avendel_room1.function = "AvendelSpeach";
			pchar.quest.Portugal_street.win_condition.l1 = "location";
			pchar.quest.Portugal_street.win_condition.l1.location = "SentJons_town";
			pchar.quest.Portugal_street.function = "PortugalOnStreet";
		break;
		// <-- Португалец
		case "guardoftruth_0":
			dialog.text = "Intriguing... And how exactly can you help me? I don't need any help, nor did I ask for it...";
			link.l1 = "But you will need it. Listen to me first, and then decide.";
			link.l1.go = "guardoftruth";
		break;
		
		case "guardoftruth":
			dialog.text = "I am all ears.";
			link.l1 = "I have been to Santiago recently... visiting Father Vincento. He was looking for his missing secretary named... Jesus, why have you gone so pale, Gino?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "You... have you seen the inquisitor? Is he...";
			link.l1 = "Don't worry, Gino. There's no chance I'll hand you over to him, even though that was his order: to find you and bring you to him. I need to acquire some information regarding an Indian of the Itza people. Tell me about Tayasal, its treasures, and the 'evil' surrounding it.";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "I see that you are well informed. Did Father Vincento tell you this?";
			link.l1 = "I got some information from him and some from other people. But I'd like to hear your side. You were once his secretary, so you must have kept a record of the interrogation, am I right?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "You can't imagine what he was doing to that poor Indian!.. It makes my flesh crawl every time I recall that interrogation in my mind.";
			link.l1 = "Still, let's talk about it. Who was that Indian? How did he end up in Father Vincento's hands?";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "He was among the Indians of the Itza people who travelled from Tayasal in search of the Kukulcan Mask - an artifact of the ancient Maya god Kukulcan. Those Indians encountered a band of white adventurers led by Archibald Calhoun - a treasure hunter from Scotland. Only one Indian survived; his name was Ksatl Cha. He had three interesting items on him, I will tell you about them later.\Calhoun tried to force the prisoner to tell him about treasures, but he kept silent. So the Scot delivered him to Santiago, to Father Vincento, in exchange for permission to visit Spanish cities for a year. He knew that the inquisitor was very interested in all kinds of local mysteries and legends. Vincento made the Indian talk. He started talking a lot, he told us everything he knew, and the information we got out of him shocked the inquisitor himself.";
			link.l1 = "You don't say? And what could make His Grace tremble?";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "I will tell you everything in order. There is an ancient Maya city called Tayasal in the depths of the Yucatan jungles. It is inhabited by the descendants of the Maya - the Itza people. They try to live their lives according to the rules and traditions of their ancestors. Surely, they don't like the state of the modern world - I mean the dominance of the white man.\nThey dream about the good old times. And here comes the most interesting part. A group of white adventurers accidentally got close to Tayasal and kidnapped the daughter of the supreme chief of the Itza people. It happened almost a quarter of a century ago.\nThis was the last straw and Kanek, the chief, was enraged. He decided to conduct the most dangerous and secret ritual of the Maya - summoning an Indian god in order to erase all descendants of the white conquerors...";
			link.l1 = "Hm... That must be the demon Father Vincento was talking about. But how is this Indian god supposed to deal with the white colonists? Should he appear as a dragon and burn them all?";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "Oh, "+pchar.name+", leave these fire monster tales to the old grannies! Actually, you aren't that wrong, but our case is more difficult and serious. Even the Flood won't be able to stop Europe from expanding into the New World. Ten more will come to replace one dead. Kanek needed to destroy the very possibility of European colonisation itself.";
			link.l1 = "Well, it has already happened.";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "You are thinking in the right direction, Captain... The purpose of Kanek's rite was not only to summon the higher being, but also to create a spatio-temporal rift.";
			link.l1 = "What?";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = "The ancient Maya possessed remarkable knowledge, Captain. Kanek found a description of a rite that allows one to control time.";
			link.l1 = "Whoa! Incredible!";
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			dialog.text = "Listen. The ultimate goal of the ritual is to alter the past to make the arrival of the white man in the New World impossible. In order to do such a thing, they are going to send someone into the past, someone who holds authority, power, and the ability to change people's fates. But most importantly, such a person must possess modern knowledge.\nThink about it, "+pchar.name+", what would have happened to Columbus if his caravels had been met by an Indian fleet of frigates and galleons armed with modern cannons? And what if the hackbuts of the white soldiers had not been opposed by bows and spears, but by mortars and muskets?";
			link.l1 = "I suppose that the Americas would not have been discovered at all....";
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			dialog.text = "Exactly! And perhaps some Indian 'Columbus' would have discovered Europe...";
			link.l1 = "Interesting, and who is Kanek going to send to the past? One of his naked warriors? I doubt he will be able to teach his ancestors...";
			link.l1.go = "guardoftruth_11";
		break;
		
		case "guardoftruth_11":
			dialog.text = "Don't laugh, Captain. Kanek didn't spend years in Maya temples just reading their writings. An Indian god must be sent to the past in human form...";
			link.l1 = "Gino, what nonsense are you talking about? Are you....";
			link.l1.go = "guardoftruth_12";
		break;
		
		case "guardoftruth_12":
			dialog.text = "Even the Son of our Lord, Jesus Christ, came to our earth in human form and was born of a human woman, the Holy Virgin Mary...";
			link.l1 = "Jesus, Gino... are you serious?";
			link.l1.go = "guardoftruth_13";
		break;
		
		case "guardoftruth_13":
			dialog.text = "Sure I am. Ksatl Cha was very persuasive...";
			link.l1 = "But which god did Kanek choose for such a 'noble' mission?";
			link.l1.go = "guardoftruth_14";
		break;
		
		case "guardoftruth_14":
			dialog.text = "The rite was meant to summon only one High Being. The feathered serpent, Quetzalcoatl, Kukulcan...";
			if (CheckAttribute(pchar, "questTemp.Dolly")) link.l1 = "Kukulcan?! I have already had the imprudence to encounter his 'spirit', which dwells in statues. Now I see... go on!";
			else link.l1 = "Hm. Interesting. I have already heard that name from Father Vincento... go on!";
			link.l1.go = "guardoftruth_15";
		break;
		
		case "guardoftruth_15":
			dialog.text = "Kanek decided to summon Kukulcan, since the Itza already possessed an ancient artifact of this god - the Mask of Kukulcan. Whoever holds the mask is able to pass through the portal, and only he will be accepted by the ancient Maya as a living god.\nThe priest performed the ritual, summoning Kukulcan to incarnate in the body of a mortal. He also created a time rift that drew several random people from the future into our era.\nThe purpose of this extraction was to endow Kukulcan's incarnation not only with the knowledge of our time, but also of the future. But something went wrong, and all those people arrived elsewhere, not in Tayasal. I have never met any of them.\nSeveral portals were created throughout the archipelago; they were meant to transport bearers of future knowledge and Itza agents across the region and to Tayasal. But these portals failed in their purpose—no one has been brought to Tayasal in the last 25 years...";
			if (CheckAttribute(pchar, "questTemp.Dolly"))
			{
				link.l1 = "Sure... Because these portals only transfer captured people to each other. Incredible!";
				link.l1.go = "guardoftruth_15a";
			}
			else
			{
				link.l1 = "Interesting...";
				link.l1.go = "guardoftruth_16";
			}
		break;
		
		case "guardoftruth_15a":
			dialog.text = "Have you seen those portals? Tell me!";
			link.l1 = "Maybe later, Gino... I'm more interested in your story at the moment. Go on!";
			link.l1.go = "guardoftruth_16";
		break;
		
		case "guardoftruth_16":
			dialog.text = "Father Vincento is aware of everything I have told you. This made him worry, of course. If Kukulcan, incarnated in human form, gets to the portal along with the Mask and all the knowledge he has gathered... End of times. Apocalypse.\nIf the past alters - the future does the same. Our reality will change, it will disappear, dissolve. You and I may never be born. Or we shall be different. Once Kukulcan reaches the past - we shall cease to exist.";
			link.l1 = "And who is Kukulcan's incarnation?";
			link.l1.go = "guardoftruth_17";
		break;
		
		case "guardoftruth_17":
			dialog.text = "Who knows. He might be anyone who was born a quarter of a century ago, when the ritual was conducted. In you, for example... just kidding. But we still have a chance. First, Kukulcan's incarnation is just a mortal person; he can drown, be stabbed, be shot, or die of fever. And in such a case, no apocalypse will ever happen.\nSecond, it is impossible to reach the past without the mask. Kanek stashed it very well—maybe too well, it seems. It might be that even the incarnated Kukulcan will fail to find it.";
			link.l1 = "Tell me more.";
			link.l1.go = "guardoftruth_18";
		break;
		
		case "guardoftruth_18":
			dialog.text = "Some time after the ritual, a group of Spanish conquistadors almost reached Tayasal and nearly made it to the treasury. The Itza managed to kill all of them except one—a strong giant, seven feet tall.   Kanek was worried that the Mask could be stolen by any stranger, so he decided to protect the relic. He devised his own ritual, using the ancient Maya's knowledge. He took three items which he believed held the power of the white man: a dagger, which once belonged to Cortez himself, and a compass. He also used that dagger to carve out a piece of skin from the back of the captured Spanish giant as the third item. The man himself was sacrificed on the altar of Kukulcan. Three items were used in the ritual.   And from this ritual, a new island was born, in the open sea, not far from Yucatan. No one knows its location, but the Mask is stashed there. In order to find it, one must use the dagger, the compass, and the piece of skin. Besides, all items from the treasury are cursed; not a single one of them can leave the archipelago.   An attempt to do so will cause a storm which will drive the ship right onto the rocks of the island where the Mask is hidden. It is called Ksocheatem. Smart, isn't it?";
			link.l1 = "Maybe too smart. No arguing on that. But how in the world was Ksatl Cha so well informed? I doubt that Kanek was sharing such knowledge with common warriors...";
			link.l1.go = "guardoftruth_19";
		break;
		
		case "guardoftruth_19":
			dialog.text = "Thing is, the current chief of the Itza, Urakan, son of Kanek, had told this warrior everything. He sent Ksatl Cha with a group of warriors to find the secret island and the Mask of Kukulcan. He had given him the Guardian of Truth to do that; it is the name of the three items together - the dagger, the compass, and the map made of human skin.";
			link.l1 = "The map? And why did Urakan need the Mask? Did he decide to alter the past himself?";
			link.l1.go = "guardoftruth_20";
		break;
		
		case "guardoftruth_20":
			dialog.text = "The skin bears the contours of the archipelago, so they call it the map. Urakan wanted the Mask for a very simple reason – he does not wish to destroy the existing reality or sacrifice his life and the lives of his people for the glory of the ancients.\nThat is why he was determined to destroy the Mask at all costs. But Ksatl Cha was captured by Calhoun and... well, you know the rest of the story. He never reached Ksocheatem.";
			link.l1 = "So it is possible to prevent the end of times by finding and destroying the Mask? And where is that... Guardian of Truth now?";
			link.l1.go = "guardoftruth_21";
		break;
		
		case "guardoftruth_21":
			dialog.text = "The dagger 'Chief's Claw' and the compass 'Arrow of the Way' were left to Calhoun, and the skin map 'Of Two Appearances' is still somewhere in the Inquisition. Calhoun used it as a gag to silence the prisoner. He had no idea what these items were for.";
			link.l1 = "What did you just say? 'Chief's Claw'? Damn it, this dagger is on me right now! Fadey gave it to me as repayment for his debt to my brother! Take a look!";
			link.l1.go = "guardoftruth_22";
		break;
		
		case "guardoftruth_22":
			dialog.text = "Incredible... It really is. I remember it.";
			link.l1 = "Gino, tell me, what exactly does Father Vincento know of your story?";
			link.l1.go = "guardoftruth_23";
		break;
		
		case "guardoftruth_23":
			dialog.text = "Everything, except information concerning the Guardian of Truth and how to make it reveal the location of the secret island where the Mask of Kukulcan is hidden. Ksatl Cha told me about that when we were alone, right before I gave him a poison mixture to end his suffering. He died with a smile on his face.\nSurely, I couldn't stay in Santiago after what I did. I had serious suspicions that I had become an important and dangerous witness for the inquisitor. Father Vincento always gets what he wants, no matter the cost. Ksatl Cha told him about the treasury in Tayasal.";
			link.l1 = "These treasures were already found by an adventurer named Miguel Dichoso. Have you heard of him?";
			link.l1.go = "guardoftruth_24";
		break;
		
		case "guardoftruth_24":
			dialog.text = "No. And where is he now, with his treasures?";
			link.l1 = "I want to know myself. That is why I came to you, I am looking for that Indian gold. Dichoso has taken the treasures to Europe and disappeared with them.";
			link.l1.go = "guardoftruth_25";
		break;
		
		case "guardoftruth_25":
			dialog.text = "I will tell you where the treasures and Dichoso himself are.";
			link.l1 = "Gino, you surprise me. How would you know that?!";
			link.l1.go = "guardoftruth_26";
		break;
		
		case "guardoftruth_26":
			dialog.text = "You can figure this out yourself from my story, Captain. The treasures of Tayasal were cursed - not a single item can be taken away from the archipelago. Any ship...";
			link.l1 = "... will be caught by the storm and thrown onto the island where the Mask of Kukulcan is hidden! I was blind, but now I see. It seems that I know enough to find Ksocheatem, the treasures, and the Mask itself!";
			link.l1.go = "guardoftruth_27";
		break;
		
		case "guardoftruth_27":
			dialog.text = "Want to save the world, Captain?";
			link.l1 = "I want to find my prodigal brother... Gino, how can I make the Guardian of Truth reveal the location of the island? You said you know how!";
			link.l1.go = "guardoftruth_28";
		break;
		
		case "guardoftruth_28":
			dialog.text = "I know the method, but I don't know the details. I won't be able to help you until I have all the components of the Guardian.";
			link.l1 = "Hm. We already have the dagger. Only the compass and the map remain. Calhoun has the compass, and Father Vincento has the map...";
			link.l1.go = "guardoftruth_29";
		break;
		
		case "guardoftruth_29":
			dialog.text = "Are you going to return to the inquisitor? But how are you going to report...";
			link.l1 = "I have to convince Father Vincento that you are dead, Gino. Only then will he stop his search. Let's say that you had a sudden stroke when you saw me. You should give me an item that I can use as proof of your death.";
			link.l1.go = "guardoftruth_30";
		break;
		
		case "guardoftruth_30":
			dialog.text = "Vincento won't believe the heart attack story, but he will believe you if you tell him that I committed suicide by drinking some poison that smells of almonds. Give him my almanac, he knows I never part with it.";
			link.l1 = "Fine. Because I need that connection with the inquisitor. He probably knows a lot about our business.";
			link.l1.go = "guardoftruth_31";
		break;
		
		case "guardoftruth_31":
			dialog.text = "Be careful with Father Vincento. He is as dangerous as a tiger and he plays his own game. He won't share either treasures or fame with you.";
			link.l1 = "I understand that. Fine, Gino, give me your almanac and try to remember what the Indian told you about the Guardian of Truth, because I want to piece it together. I need to find Ksocheatem; I am sure that I will find not only the mask and the treasures there, but also my dear brother.";
			link.l1.go = "guardoftruth_32";
		break;
		
		case "guardoftruth_32":
			dialog.text = "Take it. Good luck, Captain!";
			link.l1 = "I am not saying farewell, Gino...";
			link.l1.go = "guardoftruth_33";
		break;
		
		case "guardoftruth_33":
			DialogExit();
			Log_Info("You have received an almanac");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "Almanac");
			ChangeItemDescribe("Almanac", "itmdescr_jinobook");
			pchar.questTemp.Guardoftruth = "twoitems";
			AddQuestRecord("Guardoftruth", "37");
		break;
		
		case "guardoftruth_34":
			dialog.text = "Was it hard, Captain?";
			link.l1 = "Let's not talk about it... Too many people died to get these items. Far too many. It seems I'm not the only one eager to find the mysterious Ksocheatem. ";
			link.l1.go = "guardoftruth_35";
		break;
		
		case "guardoftruth_35":
			dialog.text = "I can imagine... By the way, how is Father Vincento? Do you communicate with him regularly?";
			link.l1 = "So far I do, but I think there is no need to do that anymore. I have all the components of the Guardian of Truth, which means that I hold the key to the location of Ksocheatem. For some reason, I am not eager to report my success to His Grace.";
			link.l1.go = "guardoftruth_36";
		break;
		
		case "guardoftruth_36":
			dialog.text = "Be careful, "+pchar.name+". Father Vincento has hundreds of eyes and hands. Very long hands...";
			link.l1 = "I have been through a lot in the last few months, and at this point I am certainly not afraid, neither of Father Vincento nor of his eyes and hands. Whatever. It is time for us to find Ksocheatem using the components of the Guardian. Do you know how to perform that? ";
			link.l1.go = "guardoftruth_37";
		break;
		
		case "guardoftruth_37":
			dialog.text = "Not really. Ksatl Cha was quite vague. I think that the Indian didn't really know how to make the Guardian work. Leave the components to me and I will try to figure it out. Come and see me in two days and perhaps I will have this riddle solved.";
			link.l1 = "Fine, Gino. I'm counting on you. Here, take them.";
			link.l1.go = "guardoftruth_38";
		break;
		
		case "guardoftruth_38":
			dialog.text = "You can be sure that they will stay safe and in one piece with me.";
			link.l1 = "I don't doubt that. Well, I won't bother you for now, Gino. Good luck with your research!";
			link.l1.go = "guardoftruth_39";
		break;
		
		case "guardoftruth_39":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			RemoveItems(pchar, "knife_01", 1);
			RemoveItems(pchar, "skinmap", 1);
			RemoveItems(pchar, "arrowway", 1);
			pchar.questTemp.Guardoftruth = "end";
			SetFunctionTimerCondition("Ksochitam_StartSearchIsland", 0, 0, 2, false);
			CloseQuestHeader("Guardoftruth");
			AddQuestRecord("Ksochitam", "1");
		break;
		
		case "ksochitam":
			dialog.text = "Partly. I mean, I've got something, but I don't know how to make it all work for real. Let's try to solve this puzzle together.";
			link.l1 = "Let's try! Give me your ideas.";
			link.l1.go = "ksochitam_1";
		break;
		
		case "ksochitam_1":
			dialog.text = "Ksatl Cha said something like this: 'The Chief's Claw will make the map reveal itself. The Arrow of the Way will show the direction of the appearances.'";
			link.l1 = "And what have you managed to do?";
			link.l1.go = "ksochitam_2";
		break;
		
		case "ksochitam_2":
			dialog.text = "I've figured out how to make the map 'reveal' itself. Have you taken a look at the map of Two Appearances?";
			link.l1 = "Hm. And was there anything unusual? Some obscure contours of the archipelago...";
			link.l1.go = "ksochitam_3";
		break;
		
		case "ksochitam_3":
			GiveItem2Character(pchar, "skinmap");
			dialog.text = "Take it and have another look. Be attentive.";
			link.l1 = "Well, let's do that if you insist.";
			link.l1.go = "ksochitam_4";
		break;
		
		case "ksochitam_4":
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_wait";
			pchar.questTemp.Ksochitam = "skinmap_1";
			chrDisableReloadToLocation = true;//закрыть локацию
		break;
		
		case "ksochitam_wait":
			dialog.text = "You haven't looked at the map, "+pchar.name+"...";
			link.l1 = "Yes, yes, I will do it now...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_wait";
		break;
		
		case "ksochitam_5":
			dialog.text = "";
			link.l1 = "I have. I didn't see anything new. Just some obscured shapes of islands and the mainland. What am I supposed to see there?";
			link.l1.go = "ksochitam_6";
		break;
		
		case "ksochitam_6":
			dialog.text = "Wait a second. Now you have to make this map reveal itself. Take the dagger and gently touch the map with its edge. Don't press, we need to avoid any damage. Take the dagger. And watch it carefully!";
			link.l1 = "Interesting! Let's see...";
			link.l1.go = "ksochitam_7";
		break;
		
		case "ksochitam_7":
			DialogExit();
			GiveItem2Character(pchar, "knife_01");
			NextDiag.CurrentNode = "ksochitam_wait";
			pchar.questTemp.Ksochitam = "skinmap_2";
			sld = ItemsFromID("skinmap");
			sld.mark = 2;
		break;
		
		case "ksochitam_8":
			dialog.text = "Well, do you see any differences now?";
			link.l1 = "Yes. When you touch the map with the dagger, two skull marks appear, and they are always in the same places...";
			link.l1.go = "ksochitam_9";
		break;
		
		case "ksochitam_9":
			dialog.text = "At the same two places, "+pchar.name+"! That is why it was called the Map of Two Appearances!";
			link.l1 = "And what does it mean?";
			link.l1.go = "ksochitam_10";
		break;
		
		case "ksochitam_10":
			dialog.text = "A lot, I think... But more puzzles are coming next. I take it that these skulls are the apparitions Ksatl Cha was talking about. So the compass must show the right direction to Ksocheatem from them. Have you seen the compass, "+pchar.name+"?";
			link.l1 = "Yes. It looks like an ordinary naval compass, but it behaves strangely; its needle twitches in different directions or starts spinning wildly.";
			link.l1.go = "ksochitam_11";
		break;
		
		case "ksochitam_11":
			dialog.text = "I thought that planting the compass on the skulls would stop its arrow and show some clear direction on the map. To do that, I placed it on one skull and then on the other, while touching the map with the dagger.";
			link.l1 = "And?";
			link.l1.go = "ksochitam_12";
		break;
		 
		case "ksochitam_12":
			dialog.text = "Fruitlessly. The compass didn't change its behaviour. The arrow is still spinning wildly. It seems that I am doing something wrong. Or perhaps I misunderstood Ksatl Cha's words.";
			link.l1 = "So the dagger and the map work, but the compass doesn't?";
			link.l1.go = "ksochitam_13";
		break;
		
		case "ksochitam_13":
			dialog.text = "The Arrow of the Way must be operational for sure, we just don't know how to make it work yet. "+pchar.name+",  you know the archipelago's geography better than I do... Tell me, what places are revealed by the map of two faces?";
			link.l1 = "Just a second! (taking a look)... Well, well... The land on the left is the western Main. The one on the right looks like the island of Dominica. Something like that.";
			link.l1.go = "ksochitam_14";
		break;
		
		case "ksochitam_14":
			dialog.text = "And tell me: Is there... anything noteworthy in those places?";
			link.l1 = "What do you mean?";
			link.l1.go = "ksochitam_15";
		break;
		
		case "ksochitam_15":
			dialog.text = "I am not sure myself... Well, something special?";
			link.l1 = "Gino, don't speak in riddles. Explain it simply.";
			link.l1.go = "ksochitam_16";
		break;
		
		case "ksochitam_16":
			dialog.text = "I can only suppose that these skulls show us some real places. The Arrow of the Way doesn't work while planted on the map's images. Perhaps it will work near the real geographical features revealed by the map?";
			link.l1 = "Gino, you are a genius! Western Main, Dominica? The skulls are too large to show the exact locations.";
			link.l1.go = "ksochitam_17";
		break;
		
		case "ksochitam_17":
			chrDisableReloadToLocation = false;//открыть локацию
			dialog.text = ""+pchar.name+", let's do the following: Bring me a paper map of the archipelago, combine it with the map of Two Appearances, and mark the appearances with crosses. Perhaps this will lead you to some suppositions?";
			if (CheckCharacterItem(pchar, "map_bad"))
			{
				link.l1 = "I have this old map of the archipelago.";
				link.l1.go = "ksochitam_17_1";
			}
			if (CheckCharacterItem(pchar, "map_normal"))
			{
				link.l2 = "I have this fine map of the archipelago.";
				link.l2.go = "ksochitam_17_2";
			}
			if (CheckCharacterItem(pchar, "Map_Best"))
			{
				link.l3 = "I have this excellent map of the archipelago.";
				link.l3.go = "ksochitam_17_3";
			}
			link.l4 = "Deal. I will bring you the map and we will continue...";
			link.l4.go = "ksochitam_17_4";
		break;
		
		case "ksochitam_17_1":
			dialog.text = "Oh, come on, "+pchar.name+"! This parchment from the time of Columbus is hardly any better than the skin map. I am sure there must be something better than this rubbish in the world. Bring me another map, a more recent one!";
			link.l1 = "Fine...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_map_wait";
		break;
		
		case "ksochitam_17_2":
			dialog.text = "Splendid! Now mark the locations of the appearances on it. It will make it easier to form suppositions.";
			link.l1 = "Just a second, Gino!";
			link.l1.go = "ksochitam_18";
		break;
		
		case "ksochitam_17_3":
			dialog.text = "No way we're ruining such a wonderful map with our markings. You'll need it yourself, "+pchar.name+". Bring me another map, one a bit more modest!";
			link.l1 = "Fine...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_map_wait";
		break;
		
		case "ksochitam_17_4":
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_map_wait";
		break;
		
		case "ksochitam_map_wait":
			dialog.text = "Have you brought me a map of the archipelago, "+pchar.name+"?";
			if (CheckCharacterItem(pchar, "map_bad"))
			{
				link.l1 = "I have this old map of the archipelago.";
				link.l1.go = "ksochitam_17_1";
			}
			if (CheckCharacterItem(pchar, "map_normal"))
			{
				link.l2 = "I have this fine map of the archipelago.";
				link.l2.go = "ksochitam_17_2";
			}
			if (CheckCharacterItem(pchar, "Map_Best"))
			{
				link.l3 = "I have this excellent map of the archipelago.";
				link.l3.go = "ksochitam_17_3";
			}
			link.l4 = "Not yet, but I have already ordered it. Soon I will have it and we will continue...";
			link.l4.go = "ksochitam_17_4";
		break;
		
		case "ksochitam_18":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_19";
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto1", "Ksochitam_SitTable", -1);
		break;
		
		case "ksochitam_19":
			dialog.text = "";
			link.l1 = "Done... I have made the markings, but the information is still not precise. The first location is somewhere northwest of Blueweld. The second is at the centre of Dominica island.";
			link.l1.go = "ksochitam_20";
		break;
		
		case "ksochitam_20":
			dialog.text = "Any ideas?";
			link.l1 = "No. But I think we should bring the Arrow of the Way there and observe its behaviour. Of course, it's like searching for a needle in a haystack, but we don't have any better ideas anyway.";
			link.l1.go = "ksochitam_21";
		break;
		
		case "ksochitam_21":
			dialog.text = "I agree with you, "+pchar.name+". Will you let me sail with you?";
			link.l1 = "Are you interested in testing your suppositions? It would be an honour to have you on my ship's decks, Gino. Pack your things!";
			link.l1.go = "ksochitam_22";
		break;
		
		case "ksochitam_22":
			dialog.text = "It won't take long. I'll be ready in a few hours. Here, take the Arrow of the Way.";
			link.l1 = "Welcome aboard!";
			link.l1.go = "ksochitam_23";
		break;
		
		case "ksochitam_23":
			LAi_SetOwnerType(npchar);
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_24";
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_SetPlayerType(pchar);
			GiveItem2Character(pchar, "arrowway");
			pchar.questTemp.Ksochitam = "seekway";
			sld = ItemsFromID("skinmap");
			sld.mark = 1;
			pchar.quest.Ksochitam_room.win_condition.l1 = "ExitFromLocation";
			pchar.quest.Ksochitam_room.win_condition.l1.location = pchar.location;
			pchar.quest.Ksochitam_room.function = "Ksochitam_JinoPassenger";
			AddQuestRecord("Ksochitam", "2");
		break;
		
		case "ksochitam_24":
			dialog.text = "Yes, yes, "+pchar.name+", I am preparing myself. I will be ready soon.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_24";
		break;
		
		case "ksochitam_25":
			dialog.text = "So what, "+pchar.name+", are we having any luck with our search?";
			link.l1 = "We were right. This is it. The Indian idol is one of its forms.";
			link.l1.go = "ksochitam_26";
		break;
		
		case "ksochitam_26":
			dialog.text = "Oh! It must be one of those idols that were supposed to teleport people to Tayasal! I was telling you about them, remember? So, where is the Arrow of the Way pointing?";
			link.l1 = "It is pointing northwest. I have marked the direction on the map. Though the drawn line crosses almost the entire Caribbean Sea. We have to find another appearance on Dominica to find Ksocheatem.";
			link.l1.go = "ksochitam_27";
		break;
		
		case "ksochitam_27":
			dialog.text = "I am sure that we will find another idol there... do you agree with my hypothesis, "+pchar.name+"?";
			link.l1 = "I do, Gino. Now let's not waste time and start searching.";
			link.l1.go = "ksochitam_28";
		break;
		
		case "ksochitam_28":
			DialogExit();
			locations[FindLocation(pchar.location)].DisableEncounters = false; //энкаутеры открыть
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "OpenTheDoors", 20.0);
		break;
		
		case "ksochitam_29":
			dialog.text = "So what, "+pchar.name+", have you found anything of interest?";
			link.l1 = "We were right. This is it. The Indian idol is one of its forms.";
			link.l1.go = "ksochitam_30";
		break;
		
		case "ksochitam_30":
			dialog.text = "Oh! It must be one of those idols that were supposed to teleport people to Tayasal! I was telling you about them, remember? So, where is the Arrow of the Way pointing?";
			link.l1 = "Northwest. I have marked the direction on the map. Though the drawn line crosses almost the whole Caribbean Sea. We have to find another landing on the Main to find Ksocheatem.";
			link.l1.go = "ksochitam_27";
		break;
		
		case "ksochitam_31":
			dialog.text = "So what, "+pchar.name+", have you found the second idol?";
			link.l1 = "Yes. I have drawn the direction shown by the Arrow of the Way. Now we know the location of Ksocheatem; it's not the exact spot, but we know where to search! I will search the whole area where the lines cross, and I will find that damn island!";
			link.l1.go = "ksochitam_32";
		break;
		
		case "ksochitam_32":
			dialog.text = "I am glad to hear such enthusiasm in your voice. But we must prepare well for the upcoming expedition; it is unknown what we will face there. I doubt we will receive a warm welcome...";
			link.l1 = "Are you worried about something specific or are you just expressing concerns?";
			link.l1.go = "ksochitam_33";
		break;
		
		case "ksochitam_33":
			dialog.text = "Think about it, "+pchar.name+".. Ksocheatem was created by Mayan magic performed by Kanek. It is not a natural formation and it possesses evil and destructive powers. It is unknown what awaits us there; I doubt we will find sunshine, peaceful seas, whores, or a calm wind there.";
			link.l1 = "Fine, Gino. I will consider your words and prepare myself for the expedition. I'll get my ship ready and take care of potions and ammo...";
			link.l1.go = "ksochitam_34";
		break;
		
		case "ksochitam_34":
			dialog.text = "A very wise decision. Well, shall we get back to the ship?";
			link.l1 = "Sure! Let's go!";
			link.l1.go = "ksochitam_28";
		break;
		
		case "ksochitam_35":
			dialog.text = "We have arrived, "+pchar.name+"! Uh, the wind is howling!";
			link.l1 = "Yes, Gino, you were right, there is no sunshine to greet us... I don't see any whores either. Actually, it's unclear what awaits us here at all.";
			link.l1.go = "ksochitam_36";
		break;
		
		case "ksochitam_36":
			dialog.text = "Well, you have chosen such a bad place to land, Captain! Just rocks and cliffs everywhere! And how are you going to get to the interior of the island from here?";
			link.l1 = "I didn't see any other suitable bay to land on this island because of this damn storm! Whatever, this is better than nothing. I'll manage to find my way among these rocks, I've had worse. Don't panic, friend!";
			link.l1.go = "ksochitam_37";
		break;
		
		case "ksochitam_37":
			dialog.text = "I don't like this island, "+pchar.name+"! It is creepy. And this storm must be attached to the island. This place is doomed, that's for sure!";
			link.l1 = "I don't really like this place either, Gino! But this island does exist, which means that the story of Kukulcan is true. We will all be in danger if he manages to get to Tayasal with the Mask...";
			link.l1.go = "ksochitam_38";
		break;
		
		case "ksochitam_38":
			dialog.text = "Try to find the Mask, Captain! It's more important than all the treasures in the world! It must be around here somewhere! Once we have it, we'll destroy Kukulcan's plans and won't let him alter the past!";
			link.l1 = "And what does this mask look like, do you know?";
			link.l1.go = "ksochitam_39";
		break;
		
		case "ksochitam_39":
			dialog.text = "No clue! But I think you'll recognize it, it's an ancient Indian artifact, it's hard to mistake it for anything else!";
			link.l1 = "I see. I'll keep my eyes open! Fine, Gino, get back to the ship! You don't have to wander around the island, your head is too valuable to risk!";
			link.l1.go = "ksochitam_40";
		break;
		
		case "ksochitam_40":
			dialog.text = "I won't lie, Captain, I'm a poor fighter and I don't feel comfortable in this place. Care for some advice? Every component of the Guardian is connected to the magic of this island. Ksatl Cha mentioned that the dagger has power over the local inhabitants, though I don't know what he meant.   I'll stay aboard. Find me there if you need my help.";
			link.l1 = "Good. And now wish me luck, Gino!";
			link.l1.go = "ksochitam_41";
		break;
		
		case "ksochitam_41":
			dialog.text = "Good luck, "+pchar.name+"! May God bless and keep you!";
			link.l1 = "...";
			link.l1.go = "ksochitam_42";
		break;
		
		case "ksochitam_42":
			DialogExit();
			NextDiag.CurrentNode = "adversary";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "My_Campus", "quest", "quest1", "Ksochitam_JinoStay", 10.0);
			AddQuestRecord("Ksochitam", "6");
		break;
		
		case "adversary":
			dialog.text = "How are you doing, "+pchar.name+" ? Need some advice? ";
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L1"))
			{
				link.l1 = "This bloody island is crawling with the undead, and those damn skeletons are surprisingly tough. I have no idea how to fight them.";
				link.l1.go = "adversary_1";
			}
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L2"))
			{
				link.l1 = "If you go left at the fork you will eventually reach the cavern. But where should I go next? I fear that the cavern is a dead end...";
				link.l1.go = "adversary_2";
			}
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L3"))
			{
				link.l1 = "I have found my way into the wet cavern, you can dive into its underwater part. But I don't see any exit from there...";
				link.l1.go = "adversary_3";
			}
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L4"))
			{
				link.l1 = "If you go left at the fork, you'll reach the cavern. But where should I go next? I fear the cavern is a dead end...";
				link.l1.go = "adversary_4";
			}
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L5"))
			{
				link.l1 = "There is a spot in the large cavern where you can dive into the flooded section. But it seems there is no way out from there...";
				link.l1.go = "adversary_5";
			}
			link.l10 = "Everything is alright so far, Gino, I am fine.";
			link.l10.go = "exit";
			NextDiag.TempNode = "adversary";
		break;
		
		case "adversary_1":
			dialog.text = "Ksatl Cha mentioned the Chief's Claw. Try to use it against the skeletons; the Indian said that this dagger holds power over the inhabitants of Ksocheatem.";
			link.l1 = "I will definitely try!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L1");
		break;
		
		case "adversary_2":
			dialog.text = "And what does this cave look like?";
			link.l1 = "Well, there is a small cave in the rock, it's damp, and water sways at the bottom just like the surf...";
			link.l1.go = "adversary_2_1";
		break;
		
		case "adversary_2_1":
			dialog.text = "If the water sways, then the cavern must have some connection with the sea and it can't be a dead end. Search for a passage, it must be there.";
			link.l1 = "On my way...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L2");
		break;
		
		case "adversary_3":
			dialog.text = "If there is a way to the flooded cavern from the main one, and if the water sways like surf in the main cavern, then the flooded cave has a second passage. Search more thoroughly, but be careful or you will drown.";
			link.l1 = "I am going to dive...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L3");
		break;
		
		case "adversary_4":
			dialog.text = "And what does this cave look like?";
			link.l1 = "Well, it's quite large with a few caverns, it's damp, and there's a small hole with still water...";
			link.l1.go = "adversary_4_1";
		break;
		
		case "adversary_4_1":
			dialog.text = "If the water is still, then the cave doesn't have a connection to the sea and it might be a dead end.";
			link.l1 = "I thought the same. I have been searching there for a long time and there is only one entrance, which is also an exit...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L4");
		break;
		
		case "adversary_5":
			dialog.text = "If the water is still in the cavern, then perhaps you are right. Search a bit more, but don't be sad if you don't find anything. It is likely that it is a dead end.";
			link.l1 = "I see...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L5");
		break;
		
		case "adversary_6":
			dialog.text = ""+pchar.name+", Spanish ships are onto us! This is not the best time to talk!";
			link.l1 = "Yes, sure...";
			link.l1.go = "exit";
			NextDiag.TempNode = "adversary_6";
		break;
		
		case "ksochitam_43":
			dialog.text = "Your happy eyes tell me that you have found what you were looking for.";
			link.l1 = "Yes. The treasures of Miguel Dichoso and the Mask of Kukulcan. Now his incarnation will never be able to change the future!";
			link.l1.go = "ksochitam_44";
		break;
		
		case "ksochitam_44":
			dialog.text = "Incredible! You are a hero, "+pchar.name+"...";
			link.l1 = "Gino, are you sure this is enough to stop Kukulcan?";
			link.l1.go = "ksochitam_45";
		break;
		
		case "ksochitam_45":
			dialog.text = "According to Ksatl Cha - yes. And he was quoting Urakan. His father, Kanek, was the one who started all this mess. Any doubts?";
			link.l1 = "I was met at the bay by a guest from the past – Alonso de Maldonado. He was in Tayasal when Kanek performed the ritual to create the Guardian of Truth. He was dragged into the spatio-temporal rift, yet survived... Until today.";
			link.l1.go = "ksochitam_46";
		break;
		
		case "ksochitam_46":
			dialog.text = "";
			link.l1 = "He said that I have to shut down the portal itself to protect our world for good. In order to do that, I have to destroy the Mask on some altar in Tayasal.";
			link.l1.go = "ksochitam_47";
		break;
		
		case "ksochitam_47":
			dialog.text = "And you are going to Tayasal? This is madness! "+pchar.name+", you have got the mask and the incarnation of Kukulcan won't be able to do anything! And Kanek himself is confident of that! That is why Urakan has sent Ksatl Cha to find Ksocheatem - to get the Mask and destroy it.";
			link.l1 = "And what if this Urakan was planning to destroy the mask in Tayasal?";
			link.l1.go = "ksochitam_48";
		break;
		
		case "ksochitam_48":
			dialog.text = ""+pchar.name+", only one man has managed to escape Tayasal alive so far, and that was Miguel Dichoso. Also Maldonado, but he was an exception. Even if the incarnation of Kukulcan goes back to the past, he will be killed by the ancient Maya!";
			link.l1 = "What if they don't kill him but recognise him?";
			link.l1.go = "ksochitam_49";
		break;
		
		case "ksochitam_49":
			dialog.text = "So, are you planning an expedition to Tayasal?";
			link.l1 = "I don't know, Gino. I really don't...";
			link.l1.go = "ksochitam_50";
		break;
		
		case "ksochitam_50":
			dialog.text = "Then think about it, why would you do that? You have heard my opinion. It is up to you now..."+pchar.name+", will you take me to St. John's?";
			link.l1 = "Sure, Gino. Let's set sail as soon as possible. I've had enough of this dreadful island.";
			link.l1.go = "ksochitam_51";
		break;
		
		case "ksochitam_51":
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_52";
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			AddQuestRecord("Ksochitam", "16");
			pchar.quest.Ksochitam_gohome.win_condition.l1 = "location";
			pchar.quest.Ksochitam_gohome.win_condition.l1.location = "sentjons_town";
			pchar.quest.Ksochitam_gohome.function = "Ksochitam_ArriveHome";
			pchar.questTemp.Ksochitam = "gohome";
		break;
		
		case "ksochitam_52":
			dialog.text = "Will we be home soon, "+pchar.name+"? I really miss my flasks and tubes...";
			link.l1 = "Yes, yes, Gino, soon we will be at Antigua.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_52";
		break;
		
		case "ksochitam_53":
			dialog.text = "I am glad that we are finally back! I can't imagine how you sailors spend so much time on your ships...";
			link.l1 = "It is a matter of habit, Gino.";
			link.l1.go = "ksochitam_54";
		break;
		
		case "ksochitam_54":
			dialog.text = "I will lie on my bed, standing on solid ground, with great pleasure... I hope, "+pchar.name+", that you have spared yourself the thought of visiting Tayasal?";
			link.l1 = "I don't know yet, Gino. To be honest, I'm still not sure.";
			link.l1.go = "ksochitam_55";
		break;
		
		case "ksochitam_55":
			dialog.text = "Destroy the mask of Kukulcan and live without worries, Captain. If you wish, we can dissolve the mask in the strongest acid I have. I won't hold a grudge over such a matter.";
			link.l1 = "You know, I'll wait a while. We'll always have time to destroy it.";
			link.l1.go = "ksochitam_56";
		break;
		
		case "ksochitam_56":
			dialog.text = "It's your call. If you decide to spare this world from this artifact, come to me. My gratitude for a wonderful voyage, Captain!";
			link.l1 = "Any time, Gino. See you around!";
			link.l1.go = "exit";
			NextDiag.TempNode = "first time";
			AddDialogExitQuestFunction("Ksochitam_TripComplete");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("You are a "+GetSexPhrase("Thief, mister! Guards, seize him","Thief, girl! Guards, seize her ")+"!!!","Just look at that! The moment I was lost in contemplation, you decided to check my chest! Thief! Catch the thief!!!","Guards! Robbery! Catch the thief!!!");
			link.l1 = "Damn it!";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}

int iFadeyPseudoGlobal;

// Фадей Московит
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int rate;
	string sTemp;
    bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			//--> LoyaltyPack
			if (GetDLCenabled(DLC_APPID_1))
			{
				if (CheckAttributeEqualTo(pchar, "questTemp.LoyaltyPack.Fadey", "ready"))
				{
					link.l32 = "Fadey, do you know a man named Alonso?";
					link.l32.go = "LoyaltyPack_Fadey_1";
				}
				if (CheckAttributeEqualTo(pchar, "questTemp.LoyaltyPack.Fadey", "money") && PCharDublonsTotal() >= 1000)
				{
					link.l32 = "Fadey, I'm ready to buy your mirror breastplate.";
					link.l32.go = "LoyaltyPack_Fadey_1000";
				}
			}
			//<-- LoyaltyPack
			if (CheckAttribute(pchar, "questTemp.Sharlie"))
			{
				if (pchar.questTemp.Sharlie == "fadey")
				{
					dialog.text = "What can I do for you, Monsieur? I don't speak to people I'm not acquainted with. If you've stopped by for a chat or to ask what time of the month the Spanish Silver Train arrives in Maracaibo in 1640, then I must disappoint you. I don't waste my time on idle talk.";
					link.l1 = "Good afternoon, Monsieur Fadey. You may not be acquainted with me yet, but you do know my brother. Allow me to introduce myself - Charles de Maure, brother of Michel de Monper.";
					link.l1.go = "Sharlie";
					break;
				}
				if (pchar.questTemp.Sharlie == "takeknife" && !CheckAttribute(pchar, "questTemp.Persian"))
				{
					dialog.text = "Aha, you again, Charles! Kak dela? What is it this time?";
					link.l1 = "You said that you've been robbed... Have you found the culprits?";
					link.l1.go = "Sharlie_8";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "fadey")
				{
					dialog.text = "So Charles, have you gone to speak to that savage?";
					link.l1 = "I have... That's why I've come back to you.";
					link.l1.go = "Tichingitu";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "dublon")
				{
					dialog.text = "Ah, it's you again, my dear friend! Well, have you brought the ransom of doubloons for the Indian?";
					if (CheckAttribute(npchar, "questTemp.Sharlie.Tichingitu_Skidka"))
					{
						if (PCharDublonsTotal() >= 35) // belamour legendary edition
						{
							link.l1 = "Yes. Here are your 35 doubloons.";
							link.l1.go = "Tichingitu_7";
						}
						else
						{
							link.l1 = "No, I haven't collected enough yet.";
							link.l1.go = "exit";
						}
					}
					else
					{
						if (PCharDublonsTotal() >= 40) // belamour legendary edition
						{
							link.l1 = "Yes. Here are your 40 doubloons.";
							link.l1.go = "Tichingitu_7";
						}
						else
						{
							link.l1 = "No, I haven't gathered enough yet.";
							link.l1.go = "exit";
						}
					}
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "begin")
				{
					dialog.text = "Ha, well, it's Monsieur de Maure himself! I said come in, don't stand there! What brings you to my dom?";
					link.l1 = TimeGreeting()+", Fadey, my brother told me to come to you. He said you'd help me find some work.";
					link.l1.go = "trial";
					// опоздал
					if (CheckAttribute(pchar, "questTemp.Trial.late")) {
						link.l1.go = "trial_late";
					}
					break;
				}
				if (pchar.questTemp.Sharlie == "trial" && !CheckAttribute(npchar, "quest.vodka"))
				{
					dialog.text = "Ha, it's you! What brings you here, Monsieur de Maure?";
					link.l1 = TimeGreeting()+", Fadey. My brother insisted that I shouldn't speak to you about this, but I couldn't keep myself away... ";
					link.l1.go = "vodka";
					break;
				}
				// belamour legendary edition пиратская линейка -->
				if(CheckAttribute(pchar, "questTemp.Mtraxx.GiveMeSlaves") && pchar.questTemp.Mtraxx.GiveMeSlaves == "Baster")
				{
					dialog.text = "Ah, old friend! Come in, come in, "+pchar.name+"! How are you?";
					link.l1 = TimeGreeting()+", Fadey. Good to see you. Actually, I have important business to discuss. Black gold.";
					link.l1.go = "Slaves";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Mtraxx.GiveMeSlaves") && pchar.questTemp.Mtraxx.GiveMeSlaves == "FindGold")
				{
					dialog.text = "Ah, it's you again, my dear friend! Have you got the loot? Did you find enough doubloons?";
					if(PCharDublonsTotal() >= 150)
					{
						link.l1 = "Yes, Monsieur Fadey! Here is your gold.";
						link.l1.go = "Slaves_2";
					}
					else
					{
						link.l1 = "No, just passing by. I'm still looking for the right amount.";
						link.l1.go = "exit";
					}
					
					link.l2 = "Fadey, I've just come up with an idea. I no longer need the slaves. You must excuse me, I'll see you later!";
					link.l2.go = "Slaves_3";
					break;
				}
				if(CheckAttribute(pchar,"questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "Baster")
				{
					dialog.text = "Ah, my old friend! Come in, come in, "+pchar.name+"! How are you?";
					if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves"))
					{
						if(pchar.questTemp.Mtraxx.GiveMeSlaves == "Deal" || pchar.questTemp.Mtraxx.GiveMeSlaves == "WithoutSlaves")
						{
							link.l1 = TimeGreeting()+", I need your help again.";
						}
					}
					else
					{
						link.l1 = TimeGreeting()+", Fadey. Good to see you. I have business with you.";
					}
					link.l1.go = "pistols";
					break;
				}
				if(CheckAttribute(pchar,"questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "FindMoney")
				{
					dialog.text = "Ah, it's you again, my dear friend! Well, did you find the money?";
					if(PCharDublonsTotal() >= 75)
					{
						link.l1 = "I have, Monsieur Fadey! Here are your 75 doubloons.";
						link.l1.go = "pistols_4D";
					}
					if(sti(Pchar.money) >= 40000)
					{
						link.l2 = "I have, Monsieur Fadey! Here are your 40,000 pesos.";
						link.l2.go = "pistols_4P";
					}
					if(PCharDublonsTotal() < 75 || sti(Pchar.money) < 40000) 
					{
						link.l3 = "No, just visiting. I'm still looking for the right sum.";
						link.l3.go = "exit";
					}
					link.l4 = "Excuse me, Fadey, but I can't afford it. I'll try to manage on my own. See you!";
					link.l4.go = "pistols_x";
					break;
				}
				if(CheckAttribute(pchar,"questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "Today")
				{
					dialog.text = "Come in, come in, "+pchar.name+"! I can see in your eyes that you want to hear about my success.";
					link.l1 = "Exactly, Fadey. I trust that you've brought what I want.";
					link.l1.go = "pistols_5";
					break;
				}
				if(CheckAttribute(pchar,"questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "FindMoney")
				{
					dialog.text = "Ah, it's you again, my dear friend! So, did you find the money?";
					if(PCharDublonsTotal() >= 75)
					{
						link.l1 = "Take 75 doubloons. I'll ask the sailors to carry this crate to my ship. Oh, what would I do without you, Fadey?! You have no idea how much you've helped me!";
						link.l1.go = "pistols_5D";
					}
					if(sti(Pchar.money) >= 40000)
					{
						link.l2 = "Take 40,000 pesos. I'll ask the sailors to carry this crate to my ship. Oh, what would I do without you, Fadey?! You have no idea how much you've helped me!";
						link.l2.go = "pistols_5P";
					}
					if(PCharDublonsTotal() < 75 || sti(Pchar.money) < 40000) // возможность найти без отказа
					{
						link.l3 = "No, just passing by. I'm still trying to gather enough.";
						link.l3.go = "exit";
					}
					link.l4 = "Excuse me, Fadey, I'm completely broke. Keep the deposit; I hope it will be enough to cover your expenses for this deal, and I'll try to manage on my own. See you!";
					link.l4.go = "pistols_x";
					break;
				}
				// <-- legendary edition
				//--> Дикая Роза
				if (CheckAttribute(pchar, "questTemp.WildRose_Etap5_Fadey"))
				{
					dialog.text = "Ah, here you are, good man! When I learned your ship had dropped anchor in our harbor, I hoped you might pay me a visit.";
					link.l1 = "Hello, "+npchar.name+". I won't bore you with a long tale. My companion Mary and I are searching for her father, who vanished without a trace twenty years ago...";
					link.l1.go = "WildRose_Fadey_4";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.WildRose_Etap5_Fadey_2")) 
				{
					link.l31 = "As for Mary's father...";
					link.l31.go = "WildRose_Fadey_return";
				}
				if (CheckAttribute(pchar, "questTemp.WildRose_Etap5_Fadey_3"))
				{
					dialog.text = "Well, look who it is, "+pchar.name+"!";
					link.l1 = "You positively glow, "+npchar.name+". So, tell me—did you manage to find anything out?";
					link.l1.go = "WildRose_Fadey_16";
					break;
				}
				//<-- Дикая Роза
				if (CheckAttribute(pchar, "questTemp.Guardoftruth.Baster_church") && pchar.questTemp.Guardoftruth.Baster_church == "seek")
				{
					dialog.text = "Ah, Marked One—I mean "+pchar.name+"! Come on, tell me what you've got for me!";
					link.l1 = TimeGreeting()+", Fadey. Pleased to see you. I've come to speak to you about business.";
					link.l1.go = "guardoftruth";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Guardoftruth.Baster_church") && pchar.questTemp.Guardoftruth.Baster_church == "find" && !CheckAttribute(npchar, "quest.utensil"))
				{
					dialog.text = TimeGreeting()+", "+pchar.name+". I bet you're eager to hear the outcome of my soul-searching conversation with the priest.";
					link.l1 = "Of course I am! How did it go?";
					link.l1.go = "guardoftruth_9";
					break;
				}
				if (CheckAttribute(npchar, "quest.utensil") && PCharDublonsTotal() >= 250)
				{
					dialog.text = "Ah, forgive me, I am so distracted by the clinking in your pockets!";
					link.l1 = "Such avarice, Fadey! Here is your gold.";
					link.l1.go = "guardoftruth_11";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Guardoftruth.Archy") && pchar.questTemp.Guardoftruth.Archy == "guadeloupe")
				{
					dialog.text = "Aha, my old friend! Come in, come in, "+pchar.name+"! So, have you got anything new?";
					link.l1 = "Hello, Fadey. I am once again asking for your support.";
					link.l1.go = "guardoftruth_14";
					break;
				}
				dialog.text = "What are you, a statue? If you've got something to say, spill the beans. If not, take a hike. "+pchar.name+"!";
				if (CheckAttribute(pchar, "questTemp.Persian") && pchar.questTemp.Persian == "start" && CheckNCountPersian() > 0)
				{// персидские клинки
					link.l2 = "Take a look, Fadey. I suppose this is a Persian shamshir, possibly one of those stolen from your collection?";
					link.l2.go = "persian";
				}
				if (CheckAttribute(pchar, "questTemp.Persian") && pchar.questTemp.Persian == "one" && CheckNCountPersian() > 0)
				{
					link.l2 = "I have good news for you. I have another Persian shamshir for you here.";
					link.l2.go = "persian_6";
				}
				if (CheckAttribute(pchar, "questTemp.Persian") && pchar.questTemp.Persian == "two" && CheckNCountPersian() > 0)
				{
					link.l2 = "I have a third Persian shamshir. Just as you asked, I brought it back as soon as I could.";
					link.l2.go = "persian_9";
				}
				if (CheckAttribute(pchar, "questTemp.Persian") && pchar.questTemp.Persian == "cirass")
				{
					link.l2 = "I'm here about the light armour we discussed.";
					link.l2.go = "persian_13";
				}
				if(CheckAttribute(npchar, "quest.ropes") && GetDataDay() == 20) // торговля канатами
				{
					link.l3 = "Fadey, I would like to buy some of your famous rope.";
					link.l3.go = "ropes";
				}
				link.l1 = "Fadey, I need your help.";
				link.l1.go = "help";
 				link.l9 = "No, nothing at the moment.";
				link.l9.go = "exit";
			}
			else
			{
				dialog.text = "What can I do for you, Monsieur? I don't speak to people I'm not acquainted with.";
				link.l1 = "Oh, I just stopped by to see who lives here.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "Sharlie":
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("baster_town", "reload", "houseSp1");
			dialog.text = "Ah, so you are good old Michel's baby brother! That changes things! Come in, come in, Monsieur, have a seat. Would you care to raise a glass of vodka to our meeting? I still have a few bottles left, and it would be a pleasure to share one with a good friend's brother, da!";
			link.l1 = "Forgive me, Monsieur Fadey, but drinking is not on the cards tonight. I would prefer to get straight to business.";
			link.l1.go = "Sharlie_1";
		break;
		
		case "Sharlie_1":
			dialog.text = "Chto vy govorite! This local rum is weak pisswater compared to Russian vodka! You don't know what you're missing, may the Sea take me if I'm lying! Fine, to business then. I'm all ears, Charles.";
			link.l1 = "Monsieur, I suspect that what I'm about to tell you will be quite unpleasant, but alas, I am compelled by duty to tell you! Michel has told me that you owe him a considerable sum from gambling with him. He has also instructed that you hand the money over to me, because my brother is... unable to come see you personally at the moment.";
			link.l1.go = "Sharlie_2";
		break;
		
		case "Sharlie_2":
			dialog.text = "Oh, young man! Of course, I remember everything and I admit that I owe your brother. A gambling debt is sacred, honouring that duty is the only thing that saves us from deadly anarchy and dangerous bandits! But I beg you, please understand my situation! An unpleasant story happened to me recently - I was robbed in the most brazen way!\nDamned thieves took everything they could, everything I had earned in years of labour, my money, and my priceless collection! I simply can't clear a debt right now, nyet\nBut, Monsieur de Maure, I don't give up my obligations! I only ask you to meet me halfway. Since I don't have any coin in my possession now anyway, I offer this excellent rare dagger. Take a look!\nThis is a real masterpiece of steel, the pride of my stolen collection. Besides, it was enchanted by Indian shamans and has strong hidden powers! Indians called it the Chief's Claw\nI would have never agreed to give it away because I paid a great sum for the dagger, much more than my debt, but considering the circumstances and my relation to your big brother, I am ready to give it to you. Take it, it's a very good deal!";
			link.l1 = "I'd much rather have the money than a knife...";
			link.l1.go = "Sharlie_3";
		break;
		
		case "Sharlie_3":
			dialog.text = "But I don't have the money and I do have this rare enchanted artifact! Do you really think, drug moy, that I would offer you this magnificent magical dagger instead of some worthless silver coins under different circumstances? You can find pesos anywhere, even lying in the street! You have to admit, I'm in a bit of a bind here. My heart bleeds at the very thought of parting with this incredible piece of craftsmanship, but a gambling debt is a debt of honour, so I'm willing to give it only to you, although it is very dear to me, because you are a true man of honour and a true friend.";
			link.l1 = "Alright, since you swear you don't have any money, I'll take this magic dagger of yours. Hopefully I can sell it for a good price...";
			link.l1.go = "Sharlie_4";
		break;
		
		case "Sharlie_4":
			dialog.text = "'Sell it'!? Get out of here, stal- I mean Charles! Nyet, I can scarcely believe my ears! I'm giving away my most prized possession, which I could get at least ten times more for back in Europe, and you stand there impertinently saying that you'll just go off and pawn it!? Why, this dagger, young man, saved a man's life! Let me tell you-";
			link.l1 = "And what is this hidden power you mentioned?";
			link.l1.go = "Sharlie_5";
		break;
		
		case "Sharlie_5":
			dialog.text = "Oh, ho ho! Now Charles, I am a good Christian, you know, not some Indian shaman. I have no way of knowing all the hidden properties of this blade. But they exist, oh yes! Hold this dagger in your hand and you will feel the power within for yourself! Take it, take it! How about that! Do you feel anything?";
			link.l1 = "Hm... I feel nothing. Although it fits comfortably in my hand.";
			link.l1.go = "Sharlie_6";
		break;
		
		case "Sharlie_6":
			dialog.text = "Ah ha! There you go! But that's merely the least of its qualities. If you wield this dagger in battle, I'm sure it will display its might in many dramatic ways! Well then, are you taking it?";
			link.l1 = "Well, do I have a choice? I'll take it, since you don't have the coin...";
			link.l1.go = "Sharlie_7";
		break;
		
		case "Sharlie_7":
			GiveItem2Character(pchar, "knife_01");
			PlaySound("interface\important_item.wav");
			//Log_Info("You've received the Chief's Claw'");
			sld = ItemsFromID("knife_01");
			sld.Weight = 1.5;
			sld.price = 0;
			AddLandQuestMark(characterFromId("Mishelle"), "questmarkmain");
			AddMapQuestMarkCity("FortFrance", false);
			dialog.text = "Thank you, Charles. You won't regret it, oh you most certainly won't! Here you go. And be sure to say hello to Michel for me! Tell him to drop by sometime, as soon as he gets the chance.";
			link.l1 = "Oh, I'll tell him...";
			link.l1.go = "exit";
			link.l2 = "You said that you had been robbed... Have you found the culprits?";
			link.l2.go = "Sharlie_8";
			pchar.questTemp.Sharlie = "takeknife";
			AddQuestRecord("Sharlie", "18-1");
			sld = characterFromId("Mishelle");	
			sld.greeting = "mishelle_2";
			
			// Sinistra - Старт квеста "Деньги на деревьях"
			PChar.quest.MOT_BarbieSpawn.win_condition.l1 = "location";
			PChar.quest.MOT_BarbieSpawn.win_condition.l1.location = "BasTer_town";
			PChar.quest.MOT_BarbieSpawn.win_condition = "MOT_BarbieSpawn";
			//убрать запрет боёвок на Мартинике
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_town")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_townhall")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_prison")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_fort")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_ammo")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("LeFransua_town")], false);
			LocatorReloadEnterDisable("FortFrance_townhall", "reload2", false);
			LocatorReloadEnterDisable("FortFrance_townhall", "reload3", false);
			sld = &Locations[FindLocation("FortFrance_prison")];
			sld.locators_radius.item.detector1 = 0.5;
		break;
		
		case "Sharlie_8":
			dialog.text = "The problem is, I haven't. Those ruffians cleared out the whole house, ran off with all the silver, gold, my savings from years of back-breaking labour. Now, that usually doesn't bother me; after all, a real gentleman, even if he loses everything he owns, must show no emotion! Money must be so far beneath a gentleman that it is hardly worth troubling about. But the worst part is, they swooped up my magnificent collection of Persian shamshirs! There isn't a collection like it in all of the New or Old World combined. Truly remarkable Persian cavalry swords...";
			link.l1 = "Persian swords, you say? That does sound rather interesting. So, you're a collector, then?";
			link.l1.go = "Sharlie_9";
		break;
		
		case "Sharlie_9":
			dialog.text = "Well, I like to collect rare things... Listen, Charles, maybe you could help me in this matter...";
			link.l1 = "Help? But how? Do you mean by catching the thieves?";
			link.l1.go = "Sharlie_10";
		break;
		
		case "Sharlie_10":
			dialog.text = "No. I'm not particularly interested in the thieves. I would like my Persian cavalry swords back. If you find them, I will definitely make it worth your while, I promise.";
			link.l1 = "Hm. But where should I even look for them? Around the Caribbean? Or perhaps all over the world?";
			link.l1.go = "Sharlie_11";
		break;
		
		case "Sharlie_11":
			dialog.text = "Well, perhaps you'll catch sight of them on the islands at some street merchants; those scoundrels can't even comprehend the value of those cavalry swords, and they'll surely sell them for scraps. So if you see the Persian swords anywhere, bring them to me. Will you be able to recognise them?";
			link.l1 = "I think I will. Alright, I'll keep my eyes peeled, and if I see any unusual blades matching the description, I'll definitely bring them to you.";
			link.l1.go = "Sharlie_12";
			link.l2 = "You know, I'm not an expert in fine weaponry. I'm afraid I won't be able to help you. So it would be dishonest of me to give you false hope.";
			link.l2.go = "Sharlie_13";
		break;
		
		case "Sharlie_12":
			dialog.text = "Horosho! I hope you get lucky and find those artefacts, and I will make it worth your while. Good hunting, stalker— I mean captain! Da, Charles, can you imagine, I had another robbery attempt recently!\nA thief tried to break into my home just a few days ago\nThat was just too much for me! He didn't escape from me this time though, I managed to catch him, gave him a good beating, and handed him over to the guards at the prison in town. I hope they hang him soon!";
			link.l1 = "Do you think he's one of the thieves who swiped your shamshirs?";
			link.l1.go = "Sharlie_14";
			pchar.questTemp.Persian = "start";
			// --> скимитар 021012
			pchar.questTemp.Persian.skimitar = "true";
			pchar.quest.Persian.win_condition.l1 = "item";
			pchar.quest.Persian.win_condition.l1.item = "blade_23";
			pchar.quest.Persian.function = "Persian_FindSkimitar";
		break;
		
		case "Sharlie_13":
			dialog.text = "Pity, but there's no use crying for the moon. Yes, Charles, can you imagine, I had another robbery attempt recently!\nA thief tried to break into my home just a few days ago\nThat was simply too much for me! He didn't get away from me though: I managed to catch him, gave him a good beating, and sent him to the local prison. You can't be happy at the expense of another's misery. I hope they hang him soon!";
			link.l1 = "Do you think he's one of the thieves who swiped your shamshirs?";
			link.l1.go = "Sharlie_14";
			pchar.questTemp.Persian = "end";
		break;
		
		case "Sharlie_14":
			dialog.text = "No, I don't think so. He was after money. Caught him in my room, rifling through my chests\nAn Indian from some deep jungle on the Spanish Main. He looks ridiculous, quite different from the local ones around here. All covered in war paint and dressed in a colourful costume... You should visit the dungeon and see that jester for yourself if you like, while he still lives.";
			link.l1 = "Hm... Maybe I'll drop by and see him.";
			link.l1.go = "Sharlie_15";
		break;
		
		case "Sharlie_15":
			dialog.text = "Go ahead, have a peek at the freak show... Horosho, Charles, this was a nice chat. Godspeed on your trip back to Martinique, poputniy veter!";
			link.l1 = "All the best, Fadey.";
			link.l1.go = "exit";
			SetQuestHeader("Tichingitu");
			AddQuestRecord("Tichingitu", "1");
			pchar.questTemp.Sharlie.Tichingitu = "true";
			AddDialogExitQuestFunction("Tichingitu_SetTichingituJail");
			SetFunctionTimerCondition("Tichingitu_FreeTichingituOver", 0, 0, 10, false);
			pchar.questTemp.Sharlie = "takeknife";
		break;
		
		case "Tichingitu":
			DelLandQuestMark(npchar);
			dialog.text = "How interesting! I'm listening.";
			link.l1 = "Fadey, I've spoken with that Indian. And I came to you to ask for help to get him out. The poor bastard just wanted something to eat...";
			link.l1.go = "Tichingitu_1";
		break;
		
		case "Tichingitu_1":
			dialog.text = "Hahaha, and you believed that tale? Young men these days are so gullible...";
			link.l1 = "Fadey, I may be younger than you, but even I can tell when I'm being told the truth and when I'm being lied to. Besides, do you really think hanging is an appropriate punishment for that kind of crime? It seems excessive. Back home you'd just get a few lashes or a branding for a repeat offender.";
			link.l1.go = "Tichingitu_2";
		break;
		
		case "Tichingitu_2":
			dialog.text = "Excessive!? He broke into my house! That savage should never have come here! What would you do if you were in my situation? I'm sure you'd turn his innards into outards and make him into worm food, eh?!";
			link.l1 = "No I wouldn't, Fadey. You're still angry about your stolen shamshir collection. If that hadn't happened, you'd be more inclined to give this silly redskin a good thrashing and a boot up the arse, am I wrong?";
			link.l1.go = "Tichingitu_3";
		break;
		
		case "Tichingitu_3":
			dialog.text = "Ahhhh, Charles... You're just like your brother... Horosho. We'll settle this like honest businessmen. Since you want this Indian so badly, compensate me for the moral distress and property damage he has caused and I will in turn tell the commandant that I do not wish to press charges. How does that sound?";
			link.l1 = "How much?";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_4":
			dialog.text = "Ha, you're already starting to learn the ways of the Caribbean, Charles. One hundred and fifty gold doubloons, not a kopek less.";
			link.l1 = "Fadey, God have mercy...";
			link.l1.go = "Tichingitu_5";
		break;
		
		case "Tichingitu_5":
			dialog.text = "Horosho, horosho, 40 gold doubloons. But that's the final price. And doubloons, not pesos. Our moneylender will surely have some.";
			if(PCharDublonsTotal() >= 40) // belamour legendary edition
			{
				link.l1 = "I have the required amount right now. Here, take your 40 doubloons.";
				link.l1.go = "Tichingitu_7";
			}
			if(CheckCharacterPerk(pchar, "Trustworthy"))
			{
				Notification_Perk(true, "Trustworthy");
				link.l2 = "(Trustworthy) Fadey, listen... I understand your frustration, but I'm the only one willing to compensate you with real money for this inconvenience.";
				link.l2.go = "Tichingitu_7_TW";
			}
			else Notification_Perk(false, "Trustworthy");
			link.l3 = "All right, I'll go and get what you need.";
			link.l3.go = "Tichingitu_6";
		break;
		
		case "Tichingitu_7_TW":
			dialog.text = "Oh, you'll go far, my friend. You've persuaded me! 35 gold — not a coin less!";
			link.l1 = "";
			link.l1.go = "Tichingitu_6";
			npchar.questTemp.Sharlie.Tichingitu_Skidka = true;
		break;
		
		case "Tichingitu_6":
			dialog.text = "And hurry, Charles! You have only ten days until he's executed.";
			link.l1 = "I'll keep that in mind. Goodbye!";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie.Tichingitu = "dublon";
		break;
		
		case "Tichingitu_7":
			if(CheckAttribute(npchar,"questTemp.Sharlie.Tichingitu_Skidka"))
			{
				RemoveDublonsFromPCharTotal(35);
				DeleteAttribute(npchar,"questTemp.Sharlie.Tichingitu_Skidka");
			}
			else RemoveDublonsFromPCharTotal(40); // belamour legendary edition
			PlaySound("interface\important_item.wav");
			dialog.text = "Very good. I'll write up a note right now and put my seal on it, hold on a second... here you go. Give this to the commandant and you can take your Indian with you. Not sure why exactly you worry about him so much, but that's your problem. What are you going to do, put him on display at a masquerade? Haha, what a thought!";
			link.l1 = "God sees all, Fadey. Saving a man's life is a noble deed.";
			link.l1.go = "Tichingitu_8";
		break;
		
		case "Tichingitu_8":
			GiveItem2Character(pchar, "letter_1");
			ChangeItemDescribe("letter_1", "itmdescr_letter_1_Fadey");
			PlaySound("interface\important_item.wav");
			dialog.text = "I agree with your first statement, but your second is debatable, Charles. What if you save a killer or a rapist from the justice awaiting him at the end of a rope?  Bah, whatever, not my problem anymore. God be with you. Get to the commandant before your red-skinned friend goes pale from a noose around his neck...";
			link.l1 = "I'm on my way. See you later, Fadey.";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie.Tichingitu = "pay";
			SetFunctionLocationCondition("Tichingitu_AddQuestMark", "baster_prison", false);
			QuestPointerToLoc("BasTer_town", "reload", "reload_jail");
			QuestPointerDelLoc("baster_town", "reload", "houseSp1");
		break;
		
		case "vodka":
			dialog.text = "You look grim, my friend! I take it you're about to bring me some bad news?";
			link.l1 = "That's the long and short of it, aye. I'll be straight with you, Fadey: Michel said that you tricked me with this 'Chief's claw' piece of rubbish. He said this is no artefact, and I could buy it from any street merchant for a couple of hundred pesos. I asked around among the street vendors dealing in metalware. They gave me exactly that price.";
			link.l1.go = "vodka_1";
			npchar.quest.vodka = "true";
		break;
		
		case "vodka_1":
			dialog.text = "Oh, Monsieur de Maure... I am wounded! I'm surprised by your brother. These half-witted hucksters on the street can say whatever they like, but him! Tell me, Charles, if someone brought you an old two-handed knight's sword from the days of Charlemagne and offered to sell it to you, what would you give for it?";
			link.l1 = "A two-hander? Are you fucking kidding me right now, Fadey? What use would I have for some rusty old executioner's blade? This is the seventeenth century of our Lord Jesus Christ! I wouldn't give a single peso for it!";
			link.l1.go = "vodka_2";
		break;
		
		case "vodka_2":
			dialog.text = "Ah, now see your shortsightedness, my friend! You'll never get anywhere with that attitude. And if you brought such an artefact to me, I would pay three hundred doubloons for it. Ask why? Because it is an antique, a historical treasure, hard to find in this day and age! You don't understand, yet you judge!  With God and His Blessed Mother as my witness, the Chief's Claw is a masterwork dagger—my sources tell me that Cortés himself owned it. THE Hernán Cortés! The legendary conquistador who sacked Tenochtitlan and captured the emperor of the Aztecs! And you scoff and say that it is common rubbish! Besides, I have already told you that it's not just any dagger—it is an enchanted dagger! Are you still so green that you have not seen all the wonders of the Caribbean? Spells and magic, rituals and curses? Charles, this is the New World, the homeland of the Mayans and Aztecs, whose knowledge of such diabolical arts reached heights inconceivable to us Christians! This dagger has hidden powers. Alas, no one yet knows what kind of powers. You have a unique, incredible chance to find out for yourself what it is capable of, and yet you still claim that it is a 'piece of shit' and your dear poor old friend Fadey tried to cheat you! If only I had enough money to cover my debt to your brother, I'd immediately exchange it back from you for your despicable coin... This is a very valuable item and its worth is measured in more than just money, da!";
			link.l1 = "Alright, alright, calm down Fadey. I believe you. Your arguments are quite convincing and the fiery ardour that you demonstrate is either a testament to your sincerity or your unparalleled chicanery.";
			link.l1.go = "vodka_3";
		break;
		
		case "vodka_3":
			dialog.text = "Spasiba! You've done well, Charles, not taking offence and coming directly to me for an explanation. I trust that now the issue is settled?";
			link.l1 = "Yes, Monsieur Fadey. Completely. Now, please, allow me to take my leave...";
			link.l1.go = "vodka_4";
		break;
		
		case "vodka_4":
			PlaySound("Voice\English\sharlie\Fadey Moskovit-04.wav");
			dialog.text = "Stop, Charles! I'll be honest, I like your style. Maybe you and I could become best friends one day. And why not take the first step towards that friendship right now? I have been chilling two bottles of excellent Russian vodka in icy spring water downstairs in the cellar. What do you say, shall we open a bottle to your brother's health?";
			link.l1 = "Hm. I'm sorry, Monsieur Fadey, but it's already time for me to set sail. I'm in a bit of a hurry.";
			link.l1.go = "vodka_no";
			link.l2 = "You offered last time and I refused... It would be impolite to refuse twice. Fine, Fadey. I'm in!";
			link.l2.go = "vodka_5";
		break;
		
		case "vodka_no":
			dialog.text = "That's too bad. Compared to vodka, rum is just water, cheap wishy-washy stuff. But since you're in a hurry, I shan't keep you any longer. Good hunting, Charles!";
			link.l1 = "Same to you, Monsieur Fadey...";
			link.l1.go = "exit";
		break;
		
		case "vodka_5":
			dialog.text = "That's what I like to hear! Splendid! Have a seat and take a load off your feet! Please, Monsieur, make yourself at home while I fetch the vodka. Oh, how I've missed these afternoon gatherings with friends! Ah, the vodka is nice and cold, you're bound to enjoy it, nazdoroviya! Let me lay out some pickles and smoked ham.";
			link.l1 = "...";
			link.l1.go = "vodka_6";
		break;
		
		case "vodka_6":
			DialogExit();
			sld = ItemsFromID("potionrum");
			sld.shown = true;
			sld.startLocation = "BasTer_houseSp1";
			sld.startLocator = "bottle";
			sld = ItemsFromID("lcheer");
			sld.shown = true;
			sld.startLocation = "BasTer_houseSp1";
			sld.startLocator = "sit2";
			DoQuestReloadToLocation("BasTer_houseSp1", "sit", "sit2", "Sharlie_DrinkWithFadey");
			NextDiag.CurrentNode = "vodka_7";
		break;
		
		case "vodka_7":
			dialog.text = "";
			link.l1 = "Whoa... So, tell m-me, Fadey, h-how does t-that work out? Hic! We've drunk... t-two b-bottles of v-vodka... by the way! - you look s-stone c-cold sob-er and I'm... drunk as a skunk. How's t-that, huh?";
			link.l1.go = "vodka_8";
		break;
		
		case "vodka_8":
			dialog.text = "Charles, my friend, relax. What's a skunk got to do with all this? We've just downed some excellent vodka. Get some sleep and you'll be bright-eyed and bushy-tailed when you wake up. Even your head will clear up with no hangover. You'll see.";
			link.l1 = "Y-yeah, vodka... it's... it's absolutely magnificent, this vodka. I've never drunk anything like it.";
			link.l1.go = "vodka_9";
		break;
		
		case "vodka_9":
			dialog.text = "Ha! You've got that right! That kind of vodka was made according to secret recipes and shipped from my motherland Russia, and even there not everybody knows how to make it properly. I buy only the best! Like this stuff here that you and I have had the chance to nip.";
			link.l1 = "B-but tell me, Fadey: h-how c-can you drink s-so much and not get drunk? H-how do you do that, huh? Sh-share the secret with me. M-maybe it'll c-come in handy later... Hic!";
			link.l1.go = "vodka_10";
		break;
		
		case "vodka_10":
			dialog.text = "Ha! Well, you can't compare yourself to me, young Charles! Just look at you, skinny as a whip. On top of that, you're not used to serious drinking, eh! But because we are true friends, I'll share a few secrets with you about how to drink and keep yourself from pissing yourself.";
			link.l1 = "P-please d-do...hic!";
			link.l1.go = "vodka_11";
		break;
		
		case "vodka_11":
			dialog.text = "Well, if you want to drink and not get instantly blasted, you must follow a few key rules. Most importantly, never drink on an empty stomach. Eat something hearty before the drinking session starts\nSecond, don't forget to eat something after every glass. Meat or fish is best, something nice and salty. Third, don't rinse your mouth with the vodka, swallow it at once\nAlso, having a small - no more than half a pint - shot before the main course will prepare your body for receiving serious doses of alcohol. Don't overdo this appetizer, otherwise the effect will be quite the opposite and you'll wreck yourself before setting sail\nFinally, disciplined training is key; drinking moderate amounts of rum or other types of alcohol on a regular basis will make you more resistant to them.";
			link.l1 = "Hm-mm... S-so that's how you do it! I'll d-definitely...hic!.. remember all your in-structions, Fadey. Th-thank you. And n-now I think it'd b-be a g-good idea for me to g-get some shuteye, 'cause I'm not feeling too good right now.";
			link.l1.go = "vodka_12";
		break;
		
		case "vodka_12":
			dialog.text = "Get some rest, Charles. We've had a pleasant evening, you and I! Good hunting to you!";
			link.l1 = "D-d-do svidaniya, Fadey! I'm off to - hic! - the Wish Granter!";
			link.l1.go = "vodka_13";
		break;
		
		case "vodka_13":
			DialogExit();
			sld = ItemsFromID("potionrum");
			sld.shown = false;
			sld = ItemsFromID("lcheer");
			sld.shown = false;
			pchar.questTemp.CanDrink = true; // Шарль теперь знает секреты выпивки, это ему потом пригодится
			LAi_SetSitType(npchar);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			NextDiag.CurrentNode = "First time";
		break;
		
		case "trial":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("BasTer");
			pchar.quest.Sharlie_TrialOver.over = "yes"; //снять таймер
			dialog.text = "What, did he actually say that I would help you?";
			link.l1 = "Well, pretty much. Will you lend a hand to the brother of your longtime friend? It's not like I'm asking for a handout like a beggar. I'm asking you to give me an opportunity to make some money.";
			link.l1.go = "trial_1";
		break;
		
		case "trial_late":
			dialog.text = "Oh Charles! You are late. If you had come earlier, I would have found the right thing for you, but now - forgive me. Do not worry, walk around the cities, chat with people. There is a lot of work to do in the Caribbean";
			link.l1 = "I see, that is regrettable. Goodbye!";
			link.l1.go = "trial_late_1";
		break;
		
		case "trial_late_1":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Trial");
		break;

		case "trial_1":
			dialog.text = "Hm. Nyet, I won't turn you down, of course. If you want to feed a man, don't give him a fish, but a fishing pole. Isn't that right, Monsieur de Maure? So you need a job... Easy enough. I'll have a chat with a man I know and I'll recommend you to him. And everything else will depend on how well you do the job.";
			link.l1 = "Wonderful. Who do I need to speak to?";
			link.l1.go = "trial_2";
		break;
		
		case "trial_2":
			dialog.text = "Come by the store tomorrow. A man by the name of Gerard LeCroix will be waiting for you there. He'll give you some work. He'll be in this colony only until tomorrow evening. See him soon and do the job properly. Don't put me in an awkward position.";
			link.l1 = "Deal. Thank you, Fadey!";
			link.l1.go = "trial_3";
		break;
		
		case "trial_3":
			DialogExit();
			SetFunctionTimerCondition("Trial_StartLine", 0, 0, 1, false); // таймер
			pchar.questTemp.Trial = "start";
			AddQuestRecord("Trial", "1");
		break;
		// belamour legendary edition пиратская линейка -->
		case "Slaves":
			DelMapQuestMarkCity("baster");
			DelLandQuestMark(npchar);
			dialog.text = "Ah, how can I help you, my friend?";
			link.l1 = "Fadey, listen, I really need to buy fifty slaves from smugglers. The trouble is, I'm unknown to them and I need you to make an introduction for me. Without you, they won't even listen to me, and this is a matter of life and death for a very important person.";
			link.l1.go = "Slaves_1";
		break;
		
		case "Slaves_1":
			dialog.text = "Oh ho! Expanding your business, I see! How profitable! I will help you, dear friend. But as you know, I don't work for free. It will take 150 gold doubloons to convince the seller of your good intentions to buy the negroes and, of course, a little extra for my diligent efforts...";
			if(PCharDublonsTotal() >= 150)
			{
				link.l1 = "I expected nothing less, Monsieur Fadey! Here is your gold.";
				link.l1.go = "Slaves_2";
			}
			else
			{
				link.l1 = "I'm going to the usurer immediately! Hold on, Monsieur Fadey, I'll be right back!";
				link.l1.go = "exit";
				pchar.questTemp.Mtraxx.GiveMeSlaves = "FindGold"; 
			}
			
			link.l2 = "Fadey, it seems I've come up with something and I no longer need the negroes. I'm sorry. See you!";
			link.l2.go = "Slaves_3";
		break;
		
		case "Slaves_2":
			RemoveDublonsFromPCharTotal(150);
			pchar.questTemp.Mtraxx.GiveMeSlaves = "kapster";
			locations[FindLocation("Shore29")].DisableEncounters = true; //энкаутеры закрыть
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l1 = "Hour";
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l1.start.hour = 22.00;
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l1.finish.hour = 23.00;
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l2 = "Timer";
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l2.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l2.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l2.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l3 = "location";
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l3.location = "Shore29";
			pchar.quest.Mtraxx_GiveMeSlavesKapster.function = "MtraxxGiveMeSlavesKapsterInShore"; // прибыли
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1 = "Timer";
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1.date.hour  = 23.0; // не пришли, значит гудбай
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.function = "MtraxxGiveMeSlavesKapsterInShoreLate"; // опоздание
			AddQuestRecord("Roger_3", "23");
			dialog.text = "Excellent, friend. But if you are trying to deceive me about your need for this purchase and your intentions are worthless, you will make me very angry. You don't want that. Tomorrow at ten o'clock, at sunset, on Capster Beach, I will arrange a meeting for you. Do not let me down.";
			link.l1 = "You have nothing to worry about, I'll be back for the goods.";
			link.l1.go = "exit";
		break;
		
		case "Slaves_3":
			DialogExit();
			AddQuestRecord("Roger_3", "22");
			pchar.questTemp.Mtraxx.GiveMeSlaves = "WithoutSlaves";
		break;
		
		case "pistols":
			DelMapQuestMarkCity("baster");
			DelLandQuestMark(npchar);
			dialog.text = "Hello, hello! Tell me, good fellow, what brings you to my modest house?";
			link.l1 = "I need weapons. The local merchants are not able to find the amount that I need, but I think you can help me.";
			link.l1.go = "pistols_1";
		break;
		
		case "pistols_1":
			dialog.text = "First of all, tell me, dear friend, exactly what you need. Then I'll tell you if I can help you.";
			link.l1 = "I need 30 soldiers' pistols, two matchlock muskets, 70 cartridges for them and 90 healing potions.";
			link.l1.go = "pistols_2";
		break;
		
		case "pistols_2":
			if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves"))
			{
				if(pchar.questTemp.Mtraxx.GiveMeSlaves == "Deal" || pchar.questTemp.Mtraxx.GiveMeSlaves == "WithoutSlaves")
				{
					dialog.text = pchar.name+", you are scaring me. First fifty negroes, then weapons. Are you trying to start a slave revolt, my friend?";
					link.l1 = "Very perceptive, Fadey. As I said earlier, all this is necessary for the salvation of one important person. Don't worry, they will be pulled out of the clutches of the Spanish, so your reputation here will not suffer.";
					link.l1.go = "pistols_3";
					break;
				}
			}
			dialog.text = "That is good to hear. I can help.";
			link.l1 = "I am glad to hear it. How much?";
			link.l1.go = "pistols_4";
		break;
		
		case "pistols_3":
			dialog.text = "I am glad you explained yourself. And if this really has something to do with the Spanish, then I will help you. But if it turns out that you have fooled me, I will be very angry.";
			link.l1 = "Have some faith in me, Fadey. How much?";
			link.l1.go = "pistols_4";
		break;
		
		case "pistols_4":
			dialog.text = "Alright, so ... pistols and a couple of muskets, with powder and shot for each... Therefore ... I cannot promise that I'll get absolutely everything you asked for, but I will do everything in my power. In the meantime, I need a deposit of 40,000 pesos, or 75 doubloons if you prefer.";
			if(PCharDublonsTotal() >= 75)
			{
				link.l1 = "Take the doubloons, Fadey. I happen to be carrying some with me right now.";
				link.l1.go = "pistols_4D";
			}
			if(sti(Pchar.money) >= 40000)
			{
				link.l2 = "All my doubloons are gone, take pesos, Fadey.";
				link.l2.go = "pistols_4P";
			}
			if(PCharDublonsTotal() < 75 || sti(Pchar.money) < 40000) // возможность найти без отказа
			{
				link.l3 = "I need to speak to my banker. I'll be right back!";
				link.l3.go = "exit";
				pchar.questTemp.Mtraxx.MagicBox = "FindMoney";
			}
			link.l4 = "Excuse me, Fadey, but I can't afford it. I'll try to manage on my own. See you!";
			link.l4.go = "pistols_x";
		break;
		
		case "pistols_4D":
			SetFunctionTimerCondition("Mtraxx_MagicBoxready", 0, 0, 1, false);
			RemoveDublonsFromPCharTotal(75);
			pchar.questTemp.Mtraxx.MagicBox = "Tomorow";
            dialog.text = "Come tomorrow, "+pchar.name+", and I'll have the materials you need.";
			link.l1 = "Then I won't get in the way. See you tomorrow!";
			link.l1.go = "exit";
		break;
		
		case "pistols_4P":
			AddMoneyToCharacter(pchar, -40000);
			SetFunctionTimerCondition("Mtraxx_MagicBoxready", 0, 0, 1, false);
            pchar.questTemp.Mtraxx.MagicBox = "Tomorow";
            dialog.text = "Come tomorrow, "+pchar.name+", and I'll have the materials you need.";
			link.l1 = "Then I won't get in the way. See you tomorrow!";
			link.l1.go = "exit";
		break;
		
		case "pistols_X":
			DialogExit();
			DeleteAttribute(pchar,"questTemp.Mtraxx.MagicBox");
			if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves")) DeleteAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves");
		break;
		
		case "pistols_5":
			dialog.text = "Well, my boy, I was lucky to find everything you asked for under such time constraints. You should be grateful! Now, the final payment. Give me exactly as much more as was given as a deposit, and take your weapons.";
			if(PCharDublonsTotal() >= 75)
			{
				link.l1 = "Take 75 doubloons. I'll have my men bring the arms to my ship. What would I do without you, Fadey? You have no idea how much you've helped me!";
				link.l1.go = "pistols_5D";
			}
			if(sti(Pchar.money) >= 40000)
			{
				link.l2 = "Take 40,000 pesos. I will have my men bring the arms to my ship. What would I do without you, Fadey? You have no idea how much you've helped me!";
				link.l2.go = "pistols_5P";
			}
			if(PCharDublonsTotal() < 75 || sti(Pchar.money) < 40000) // возможность найти без отказа
			{
				link.l3 = "Well, damn, how could I forget the money? I'll be back soon.";
				link.l3.go = "exit";
				pchar.questTemp.Mtraxx.MagicBox = "FindMoney";
			}
			link.l4 = "Excuse me, Fadey, I'm broke. Keep the deposit; I hope it will be enough to cover your expenses for this deal, and I'll try to manage on my own. See you!";
			link.l4.go = "pistols_x";
		break;
		
		case "pistols_5D":
			Log_Info("Fadey's weapons are loaded on the ship");
			RemoveDublonsFromPCharTotal(75);
			pchar.questTemp.Mtraxx.MagicBox = "Full";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves")) DeleteAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves");
            dialog.text = "Helping those in need is an honour. Helping those who pay is a pleasure. Next time you are in Basse-Terre, be sure to visit me to say hello.";
			link.l1 = "That's absurd – to be in Basse-Terre and not see my friend Fadey! Until next time!";
			link.l1.go = "exit";
		break;
		
		case "pistols_5P":
			Log_Info("Fadey's weapons are loaded on the ship");
			AddMoneyToCharacter(pchar, -40000);
			pchar.questTemp.Mtraxx.MagicBox = "Full";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves")) DeleteAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves");
            dialog.text = "Helping those in need is an honour. Helping those who pay is a pleasure. Next time you are in Basse-Terre, be sure to visit me to say hello.";
			link.l1 = "That's absurd – to be in Basse-Terre and not see my friend Fadey! Until next time!";
			link.l1.go = "exit";
		break;
		// <-- legendary edition
		
		//--> Дикая Роза
		case "WildRose_Fadey_4":
			dialog.text = "What a scheme you've set in motion, "+pchar.name+"! The intent, no doubt, is noble, yet is it feasible? Twenty years can do anything to a man...";
			link.l1 = "You're right, Fadey. But we've spent much time and effort, come a long way — and we're almost at the goal. We've learned nearly everything about him: his name, his service in His Majesty's Royal Navy, the name of the ship he served on... and some other details of his biography. The trace ends at the wreck that occurred off Cape Catoche in June 1638.";
			link.l1.go = "WildRose_Fadey_5";
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.WildRose_Etap5_Fadey");
		break;

		case "WildRose_Fadey_5":
			dialog.text = "Catoche? Oh-ho, good man, I wouldn't be driven to those parts with a stick — there wander hordes of cursed savages. If he ended up there and did not perish in the sea, then, plain as God's day, the damned natives made a meal of him...";
			link.l1 = "We have evidence that this man survived the wreck and afterwards managed to reach Cuba. Perhaps he met his end there, but from what we've heard — he was crafty enough to avoid the inquisitors' clutches. Unlikely he stayed on Cuba — more likely he settled in one of the Archipelago's settlements...";
			link.l1.go = "WildRose_Fadey_6";
		break;

		case "WildRose_Fadey_6":
			dialog.text = "Many wonders occur in this world, my friend, and anything may be. But I still do not see why you have told me all this.";
			link.l1 = ""+npchar.name+", you have more connections than some governors. I'm sure you have able men at hand who can perform simple tasks...";
			link.l1.go = "WildRose_Fadey_7_1";
			link.l2 = ""+npchar.name+", you are a respected and influential man. You move in high circles and have connections. I am sure your business interests reach far beyond Guadeloupe. Since you cannot do all this alone, you surely use trusted agents and clever men capable of carrying out not-too-complex assignments...";
			link.l2.go = "WildRose_Fadey_7_2";
		break;

		case "WildRose_Fadey_7_1":
			dialog.text = "You are a clever and perceptive man, "+pchar.name+". Indeed, you've been told that before. I do have capable and knowing men, you speak truth. But tell me plainly — what do you want them to do.";
			link.l1 = "I'd ask you to send them to several colonies of the Archipelago to try to learn something about the man we seek. Perhaps someone heard of him, or even knew him personally. I'll cover the expenses in full, of course. "+npchar.name+", this is very important to Mary, and we have nowhere else to turn.";
			link.l1.go = "WildRose_Fadey_8";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Fadey_7_2":
			dialog.text = "You are a clever and perceptive man, "+pchar.name+". Indeed, you've been told that before. I do have capable and knowing men, you speak truth. But tell me plainly — what do you want them to do.";
			link.l1 = "I'd ask you to send them to several colonies of the Archipelago to try to learn something about the man we seek. Perhaps someone heard of him, or even knew him personally. I'll cover the expenses in full, of course. "+npchar.name+", this is very important to Mary, and we have nowhere else to turn.";
			link.l1.go = "WildRose_Fadey_8";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Fadey_8":
			dialog.text = "Can I refuse such a good friend as you, "+pchar.name+"? Especially since you are ready to spend on this godly matter. So tell me the name of the man you wish to find.";
			link.l1 = "As for the name, I'm not certain, but I think he might have been called Rupert Casper or Joshua Northwood.";
			link.l1.go = "WildRose_Fadey_9";
		break;

		case "WildRose_Fadey_9":
			dialog.text = "Very well, we'll find the fellow if he went by the names you say...";
			link.l1 = "Excellent, "+npchar.name+". Shall we discuss payment for your services?";
			link.l1.go = "WildRose_Fadey_10";
		break;

		case "WildRose_Fadey_10":
			dialog.text = "An unpleasant business, but, alas, necessary.";
			link.l1 = "Then let's begin. He would hardly risk going among the Spaniards or Dutch. The man left trouble in Antigua, so no point searching there, nor probably on Barbados. He might have settled on the Western Main, on Jamaica after the Spaniards were driven out, in French colonies, and perhaps even in pirate settlements.";
			link.l1.go = "WildRose_Fadey_11";
		break;
		
				case "WildRose_Fadey_11":
			dialog.text = "I'll say plainly, dear friend: in all the time I've lived in Basse-Terre, I never heard of a gentleman by either of those names. So there's no need to search here. On Martinique and Saint Christopher I know English gentlemen, and he is not among them either.";
			link.l1 = "Then the search area is considerably narrowed.";
			link.l1.go = "WildRose_Fadey_12";
		break;

		case "WildRose_Fadey_12":
			dialog.text = "We must check Tortuga, certainly — and I'll have the same fellow visit La Vega, Puerto Principe and Port-au-Prince. I'll dispatch my capable men to Belize and Blueveld, and also to Jamaica and Isla Tesoro.";
			link.l1 = "And how much will all this cost me?";
			link.l1.go = "WildRose_Fadey_13";
		break;

		case "WildRose_Fadey_13":
			dialog.text = "These are knowledgeable, industrious men, and thus for each of them you'll pay one hundred and fifty doubloons. The emissary I send to Tortuga and Hispaniola with Cuba should be rewarded extra — fifty gold coins on top. After all, four settlements are not one.";
			link.l1 = "So that makes 800 doubloons... Shall we proceed to settlement of accounts?";
			link.l1.go = "WildRose_Fadey_14";
		break;

		case "WildRose_Fadey_14":
			dialog.text = "Right, why waste time? Do you have the required sum on you, good man?";
			if (PCharDublonsTotal() >= 800)
			{
				link.l1 = "Of course. Here, take it.";
				link.l1.go = "WildRose_Fadey_14_pay";
			}
			else
			{
				link.l1 = "Hmm... I do not have the full sum with me.";
				link.l1.go = "WildRose_Fadey_14_nopay";
			}
		break;

		case "WildRose_Fadey_14_pay":
			RemoveDublonsFromPCharTotal(800);
			dialog.text = "Splendid, my dear friend! I will dispatch written orders to my agents at once, and they will set to work. They'll need to find ships bound that way, which will take some time. The journey itself depends on the wind's strength, and that is in our Lord's hands. But I understand my men should return within a month.";
			link.l1 = "So we'll meet in a month, "+npchar.name+". Thank you again. You've been a great help. Until then!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap5_Fadey_1");
			DeleteAttribute(pchar, "questTemp.WildRose_Etap5_Fadey_2");
		break;

		case "WildRose_Fadey_14_nopay":
			dialog.text = "I understand, "+pchar.name+", the sum is sizable. I'll await you at my place once you've procured it.";
			link.l1 = "I'll return soon.";
			link.l1.go = "exit";
			pchar.questTemp.WildRose_Etap5_Fadey_2 = true;
		break;

		case "WildRose_Fadey_return":
			dialog.text = "I remember your matter, dear friend. I suppose you've gathered the eight hundred doubloons?";
			if (PCharDublonsTotal() >= 800)
			{
				link.l21 = "Here you are, Monsieur Fadey! Here's your gold. Everything as agreed.";
				link.l21.go = "WildRose_Fadey_14_pay";
			}
			link.l31 = "I'm still gathering the required sum, but don't worry — I won't delay long.";
			link.l31.go = "exit";
		break;

		case "WildRose_Fadey_16":
			dialog.text = "It succeeded, my friend — oh, how it succeeded! All my men returned with nothing but one thing. Jerome Sauvernier, whom I sent to Belize, did not return — but he sent word. With good news for you.";
			link.l1 = "He sent you a letter? May we read it?";
			link.l1.go = "WildRose_Fadey_17";
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.WildRose_Etap5_Fadey_3");
		break;

		case "WildRose_Fadey_17":
			dialog.text = "Of course, "+pchar.name+". I kept it specially for you, knowing you'd want to read it. Please, my friend.";
			link.l1 = "Thank you, we'll read it now.";
			link.l1.go = "WildRose_Fadey_18";
			AddQuestRecordInfo("WildRose_Records_6", "1");
		break;

		case "WildRose_Fadey_18":
			dialog.text = "I haven't seen such a smile on your face for a long time, good man!";
			link.l1 = "No wonder, "+npchar.name+"! We've waited so long! But you know, we believed in success! I don't know how to thank you for being such a crucial part of it.";
			link.l1.go = "WildRose_Fadey_19";
		break;

		case "WildRose_Fadey_19":
			dialog.text = "Oh, stop that, brave fellow! You are my friend, and friends must help one another. Come back to me soon — I'm sure Monsieur Jerome will recover quickly and board the first ship...";
			link.l1 = "I think we'll hasten matters. We'll go to Belize ourselves and speak with your agent. Thanks again, "+npchar.name+". You can't imagine what you've done for us! Until we meet!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap5_Fadey_5");
		break;
		//<-- Дикая Роза
		
		//--> LoyaltyPack
		case "LoyaltyPack_Fadey_1":
			dialog.text = "My dear friend Alonso Pimentel who serves on your vessel? Ha! But of course. Every time your ship makes port, that good fellow always stops by for a drink. Few friends remain to me, "+pchar.name+". I treasure each one.";
			link.l1 = "Alonso told me amazing stories about your war adventures. He even gave me your bandolier.";
			link.l1.go = "LoyaltyPack_Fadey_2";
			DelLandQuestMark(npchar);
		break;

		case "LoyaltyPack_Fadey_2":
			dialog.text = "I hope and trust that he kept the most remarkable ones to himself. But since Alonso has shared our friendship with you, I have a curiosity for you as well. Behold!";
			link.l1 = "Is that... armor?";
			link.l1.go = "LoyaltyPack_Fadey_3";
		break;

		case "LoyaltyPack_Fadey_3":
			dialog.text = "Ah, my friend. This is all that remains of my mirror armor that I wore during that accursed war. And later, near Smolensk, I had occasion to\n"+
			" Be that as it may, even in this condition it looks magnificent and protects even better. And it doesn't fit me at all anymore!";
			link.l1 = "Looks exotic... even for these parts. A magnificent gift, Fadey. Thank you.";
			link.l1.go = "LoyaltyPack_Fadey_4";
		break;
		
		case "LoyaltyPack_Fadey_4":
			dialog.text = "For you, my friend, merely one thousand doubloons.";
			if (PCharDublonsTotal() >= 600)
			{
				if (GetSummonSkillFromName(pchar, SKILL_Commerce) >= 60)
				{
					link.l1 = "Allow me to correct you, dear Fadey. A thousand doubloons would be for a full suit of armor. But for just the breastplate?";
					link.l1.go = "LoyaltyPack_Fadey_5";
					Notification_Skill(true, 60, SKILL_COMMERCE);
				}
				else if (PCharDublonsTotal() >= 1000)
				{
					link.l1 = "No wonder you and Alonso get along. Here's your gold.";
					link.l1.go = "LoyaltyPack_Fadey_1000";
					Notification_Skill(false, 60, SKILL_COMMERCE);
				}
			}
			link.l2 = "Ha! You almost had me there, Fadey! Perhaps another time.";
			link.l2.go = "LoyaltyPack_Fadey_MoneyLater";
		break;
		
		case "LoyaltyPack_Fadey_MoneyLater":
			dialog.text = "Of course, no rush. My mirror armor will always be waiting for you.";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LoyaltyPack.Fadey = "money";
		break;
		
		case "LoyaltyPack_Fadey_5":
			dialog.text = "Oh, you're a sharp one! Very well then, I'll part with it for six hundred gold pieces.";
			link.l1 = "No wonder you and Alonso get along. Here's your gold.";
			link.l1.go = "LoyaltyPack_Fadey_600";
		break;
		
		case "LoyaltyPack_Fadey_1000":
			dialog.text = "A good bargain. I thank you and entrust my mirror armor to worthy hands. And take care of Alonso, captain.";
			link.l1 = "Who's taking care of whom here...";
			link.l1.go = "LoyaltyPack_Fadey_end";
			RemoveDublonsFromPCharTotal(1000);
			GiveItem2Character(PChar, "cirass11");
		break;
		
		case "LoyaltyPack_Fadey_600":
			dialog.text = "A good bargain. I thank you and entrust my mirror armor to worthy hands. And take care of Alonso, captain.";
			link.l1 = "Who's taking care of whom here...";
			link.l1.go = "LoyaltyPack_Fadey_end";
			RemoveDublonsFromPCharTotal(600);
			GiveItem2Character(PChar, "cirass11");
		break;
		
		case "LoyaltyPack_Fadey_end":
			DialogExit();
			AddDialogExitQuestFunction("LoyaltyPack_Fadey_DlgExit");
		break;
		//<-- LoyaltyPack

		case "guardoftruth":
			dialog.text = "Well, who'd doubt that you'd come on business, my friend! Sadly, there's no vodka to offer you at the moment, I drank it all. Tell me, what kind of trouble are you in now.";
			link.l1 = "A local parish was offered a golden pectoral cross with lazurite by a certain privateer for the forgiveness of his sins. It's a unique and valuable item. The problem is that this cross was stolen from another parish. Not only that, but a priest was murdered during the robbery.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "O spotless Theotokos! You don't say!";
			link.l1 = "Aye. I am representing the robbed parishioners and attempting to return the cross to its rightful owners.";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "A noble deed, and very pious. Trying to curry favour with the Almighty?";
			link.l1 = "But the local padre refuses to return it to me, despite all I've told him. I don't get it. How can one calmly place a stolen cross, stained with the blood of an innocent man, in the House of God? That's blasphemy!";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Well now, technically every consecrated chalice bears the blood of the Innocent Christ... but I digress. I take it you want me to assist you?";
			link.l1 = "I do! You're quite an influence in Basse-Terre. You're well respected, so perhaps the priest will heed your admonitions.";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = ""+pchar.name+", have you told our priest the exact story of this stolen cross?";
			link.l1 = "Of course! I have appealed to his religious sentiments, to Christian solidarity, to his damned conscience for God's sake, but he closed his ears.";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "Hm... Have you tried any other methods to persuade him?";
			link.l1 = "You mean bribing him? I'm not bribing a priest. If he were a banker, or a merchant, or even a governor, I would try to solve the issue that way, but not a priest!";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "My dear naive friend, if the priest's ears truly are closed to proclamations of conscience, then surely his hands will be open to gold... Or perhaps the other way around. I'll help you; I think that keeping such a tainted treasure here is bound to cause greater trouble down the road. However, it will require certain expenses."link.l1 ="Why am I not surprised? How much is it this time?";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "Come by tomorrow, "+pchar.name+", I cannot yet name the price. But you shall have that stolen cross, rest assured.";
			link.l1 = "Very well, Fadey, I won't bother you any further then. See you tomorrow!";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			DialogExit();
			pchar.questTemp.Guardoftruth.Baster_church = "wait";
			SetFunctionTimerCondition("GuardOT_FadeyTimer", 0, 0, 1, false);
			AddQuestRecord("Guardoftruth", "29");
		break;
		
		case "guardoftruth_9":
			dialog.text = "Just as promised, I've got the cross. As for the details... oh, forget them... all nonsense forgiven by the shed blood of our Precious Saviour";
			link.l1 = "How much do I owe you?";
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			dialog.text = "Two hundred and fifty doubloons. To cover my expenses, and of course, I'd appreciate a little extra for my righteous aid...";
			if(PCharDublonsTotal() >= 250) // belamour legendary edition
			{
				link.l1 = "Aye aye, Monsieur Fadey. Here is your gold.";
				link.l1.go = "guardoftruth_11";
			}
			else
			{
				link.l1 = "I must fetch the gold from my cabin. I'll be right back.";
				link.l1.go = "exit";
				npchar.quest.utensil = "true";
			}
		break;
		
		case "guardoftruth_11":
			DeleteAttribute(npchar, "quest.utensil");
			dialog.text = "Alright. Here is the stolen cross.";
			link.l1 = "Thank you, Fadey. You can't even imagine how much you've done for me!";
			link.l1.go = "guardoftruth_12";
		break;
		
		case "guardoftruth_12":
			RemoveDublonsFromPCharTotal(250); // belamour legendary edition
			GiveItem2Character(pchar, "jewelry34");
			//Log_Info("You've received a golden cross with lazurite");
			PlaySound("interface\important_item.wav");
			dialog.text = "I am always glad to help a kind – and more importantly – generous friend. Drop by more often. Perhaps we'll have some vodka when it arrives from the motherland.";
			link.l1 = "Gladly!";
			link.l1.go = "guardoftruth_13";
		break;
		
		case "guardoftruth_13":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Guardoftruth.Baster_church");
			AddQuestRecord("Guardoftruth", "30");
		break;
		
		case "guardoftruth_14":
			dialog.text = "Well, well, the sea has not claimed you yet! Fill me in. What misfortunes have brought you to my door this time?";
			link.l1 = "I don't know whether to call them misfortunes or not, but nevertheless I'm here. Fadey, the first day we met you gave me a rare dagger, the Chief's Claw. Now I know that it previously belonged to a man named Archibald Calhoun. Please, tell me what you know about this man.";
			link.l1.go = "guardoftruth_15";
		break;
		
		case "guardoftruth_15":
			dialog.text = "Nothing can be kept from you, "+pchar.name+". You see through everything, just like your brother. Yes, I won this dagger in a game of dice from Calhoun. Who is he? I myself have not a clue. We met by chance at the tavern, we got to talking, had a few drinks, and he started telling me about some sins from his past that were weighing him down...";
			link.l1 = "What are you, his confessor? What sins?";
			link.l1.go = "guardoftruth_16";
		break;
		
		case "guardoftruth_16":
			dialog.text = "Archibald was haunted by the memory of a man who was tortured to death by the Inquisition because of him, along with other innocent souls he had killed. He kept calling himself Judas, saying that God was punishing him for his sins and that the Inquisition was hunting him. He mentioned that the Spanish inquisitor Vincento himself wanted him dead and had sent mercenaries to chase him across the Caribbean. Then alcohol got the better of him and we gambled for this old dagger.";
			link.l1 = "Is that all? You never saw him again?";
			link.l1.go = "guardoftruth_17";
		break;
		
		case "guardoftruth_17":
			dialog.text = "Of course not, he's dead now. A band of wretched pirates sent his fluyt to Davy Jones' Locker and the whole crew to Mictlantecuhtli. Truth be told, rumours were that they were attacked by professionals dressed as pirates... agents of the Inquisition. Father Vincento always gets his man, they say.";
			link.l1 = "Archibald Calhoun is alive. I saw him not long ago, along with a certain William Paterson. He serves as his first mate.";
			link.l1.go = "guardoftruth_18";
		break;
		
		case "guardoftruth_18":
			dialog.text = "Oh ho, what a surprise! Archibald can at least catch his breath under Captain Paterson's wing. He's in good company. The Spanish fear Paterson like the plague. They won't dare to plot against Archibald while he's under Paterson's protection.";
			link.l1 = "Do you know Paterson?";
			link.l1.go = "guardoftruth_19";
		break;
		
		case "guardoftruth_19":
			dialog.text = "Who doesn't know William Paterson!? He's a newcomer to the Caribbean, just like you. And just like you, he has already built a towering reputation. Mr. Paterson is Colonel Fox's closest friend and is well in with Lord Windsor himself, the Governor-General of all English colonies in the Caribbean. He often visits the governor's palace in Port Royal, on Jamaica.";
			link.l1 = "Got it. Thanks for the information, Fadey!";
			link.l1.go = "guardoftruth_20";
		break;
		
		case "guardoftruth_20":
			dialog.text = "Oh, don't mention it, friend. Come visit me sometime! Good hunting!";
			link.l1 = "Definitely!";
			link.l1.go = "guardoftruth_21";
		break;
		
		case "guardoftruth_21":
			DialogExit();
			pchar.questTemp.Guardoftruth.Archy = "portroyal";
			AddQuestRecord("Guardoftruth", "62");
			// эскадру Патерсона - в Порт-Рояль
			Group_SetAddress("Willy_group", "Jamaica", "quest_ships", "quest_ship_1");
			pchar.quest.GuardOT_jamaica.win_condition.l1 = "location";
			pchar.quest.GuardOT_jamaica.win_condition.l1.location = "Jamaica";
			pchar.quest.GuardOT_jamaica.function = "GuardOT_PortRoyalArrive";
		break;
		
		// персидские клинки
		case "persian":
			dialog.text = "Let's have a look, "+pchar.name+"... Yes! It's one of them! That's my boy, you've made my day! Where did you find it?";
			link.l1 = "It doesn't matter. The important thing is that it has found its way back to you.";
			link.l1.go = "persian_1";
		break;
		
		case "persian_1":
			dialog.text = "I'll pay well for your thorough investigation. Three hundred golden doubloons should be sufficient reward for your troubles...";
			link.l1 = "Are you paying me with some of the doubloons you squeezed out of me before? Although, of course, I won't refuse them. Here is your shamshir.";
			link.l1.go = "persian_2";
		break;
		
		case "persian_2":
			sTemp = CheckNIdentifyPersian();
			RemoveItems(pchar, sTemp, 1);
			PlaySound("interface\important_item.wav");
			pchar.questTemp.Persian = "one";
			dialog.text = "Spasiba, my friend! Thank you for the sword and for your sardonic words. You're wiser than your years, "+pchar.name+", but the human bonds of friendship surpass the value of gold. Speaking of gold, - I will pay you in full. Here, take your doubloons.";
			link.l1 = "Thanks.";
			link.l1.go = "persian_3";
		break;
		
		case "persian_3":
			TakeNItems(pchar, "gold_dublon", 300);
			//Log_Info("You've received 300 doubloons");
			PlaySound("interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, FRANCE, 2);
			dialog.text = "And speaking of the bonds of friendship, yours and mine in particular, "+pchar.name+". I have something that will be of great interest to you.";
			link.l1 = "Let me guess, more vodka?";
			link.l1.go = "persian_4";
		break;
		
		case "persian_4":
			dialog.text = "Ha! Vodka is good, but it is not the only thing my country is known for. There is a special material which only Russia produces. I get this material delivered from my contacts back home here to trade. Every captain wants it, because it improves any ship. I am talking about hemp ropes\nRopes immune to moisture and sea salt alike. They say it is the best material for rigging\nEvery month, I get a certain amount delivered to me from Reval. Normally, my storehouse has a few hundred coils around the middle of each month. So, "+pchar.name+", I am offering to sell you a batch of fifty coils. Ten doubloons a coil\nI have only two terms: first, I will keep your ropes until the 20th of every month; second, you can buy only the whole batch. Fifty coils for five hundred doubloons. Confidentially speaking, "+pchar.name+", they say that there are certain places where you can resell those ropes for a much greater price, but what do I know!\I am completely satisfied with the current state of my operation and don't need to find resellers myself. If you find a good merchant, you can turn a fine profit.";
			link.l1 = "Got it. That's a great offer, Fadey! I think I'll take advantage of the opportunity you've presented to me. So, on the twentieth day of each month, five hundred doubloons for fifty pieces?";
			link.l1.go = "persian_5";
		break;
		
		case "persian_5":
			AddQuestRecordInfo("Unique_Goods", "2");
			dialog.text = "Yes. Go collect your purchase. But wait, wait, dear fellow! Besides this shamshir, which you returned to me out of true benevolence, there were two others. I beg you, please, if you find them, bring them back to me and I will pay you more than a fair price for their return.";
			link.l1 = "Definitely, Fadey. If I find them, I'll bring them back.";
			link.l1.go = "exit";
			if (CheckNCountPersian() > 0)
			{
				link.l2 = "Good news for you. I've got another Persian shamshir.";
				link.l2.go = "persian_6";
			}
			npchar.quest.ropes = "true";
		break;
		
		case "persian_6":
			dialog.text = "Oh, my good friend! You have just wiped away my tears! Let me take a look... Ah! This is it, my precious shamshir! Here, just as I promised you, three hundred doubloons as a reward for it.";
			link.l1 = "Spasibo!";
			link.l1.go = "persian_7";
		break;
		
		case "persian_7":
			TakeNItems(pchar, "gold_dublon", 300);
			//Log_Info("You've received 300 doubloons");
			sTemp = CheckNIdentifyPersian();
			RemoveItems(pchar, sTemp, 1);
			PlaySound("interface\important_item.wav");
			pchar.questTemp.Persian = "two";
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, FRANCE, 2);
			dialog.text = "Please accept my gratitude and a modest but very useful gift. I don't need it, but you or your ship's joiner will find it quite helpful\nHere, look at this fine ring! It's yours now. But it is not just any common ring, it is an enchanted ring. It helps with carpentry and ship repair. Many craftsmen would like to have it, but I have been keeping it for a special occasion. Take it, my friend, I hope it will ease your burden!";
			link.l1 = "You certainly carry a lot of interesting artefacts. Thanks, Fadey!";
			link.l1.go = "persian_8";
		break;
		
		case "persian_8":
			GiveItem2Character(pchar, "talisman7");
			//Log_Info("You've received the Scarab amulet");
			PlaySound("interface\important_item.wav");
			dialog.text = "There's only one shamshir left from my lost collection to be found. I'm counting on you, "+pchar.name+", and on your luck. If you find it, do not hesitate to hurry back to me.";
			link.l1 = "Definitely! See you soon...";
			link.l1.go = "exit";
			if (CheckNCountPersian() > 0)
			{
				link.l2 = "Why should I hurry? The sword is with me.";
				link.l2.go = "persian_9";
			}
		break;
		
		case "persian_9":
			dialog.text = "Oh, thank God I asked you for help, "+pchar.name+". You're a miracle man, my friend! Show it to me... Ohooo! It's, it's her. My darling! Krasavitsa! Gramercy, fine fellow, I bow to you! Here, here's your money. Four hundred doubloons and not a kopek less! I won't be stingy.";
			link.l1 = "Thank you, Fadey. It's a pleasure to help.";
			link.l1.go = "persian_10";
		break;
		
		case "persian_10":
			TakeNItems(pchar, "gold_dublon", 400);
			//Log_Info("You've received 400 doubloons");
			sTemp = CheckNIdentifyPersian();
			RemoveItems(pchar, sTemp, 1);
			PlaySound("interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Leadership", 500);
			AddCharacterExpToSkill(pchar, "Fortune", 250);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, FRANCE, 3);
			Achievment_Set("ach_65");
			dialog.text = "My collection of shamshirs is all together again! No one will dare steal it from me again, I will make sure of that! I have a very special reward for you, good man. In two weeks, a merchant will bring me a set of excellent fencing armour from Europe. Commissioned by a nobleman, it is quite a unique piece of armour\nSo, if you wish, you can buy it for only seven hundred golden doubloons. I will tell the nobleman that it was lost in transit.";
			link.l1 = "What's so good about this armour?";
			link.l1.go = "persian_11";
		break;
		
		case "persian_11":
			dialog.text = "It's very comfortable and durable, yet it still performs as well as the iron cuirass. Plus, it looks great! You should come back in a couple of weeks and have a look at it. But don't take longer than a month or I'll sell it to the original customer.";
			link.l1 = "Deal. I'll drop by your house in two weeks.";
			link.l1.go = "persian_12";
		break;
		
		case "persian_12":
			DialogExit();
			pchar.questTemp.Persian = "time";
			SetFunctionTimerCondition("Persian_CirassLamport", 0, 0, 14, false); // таймер
		break;
		
		case "persian_13":
			dialog.text = "Yes, it's been delivered already and it's waiting for you. Did you bring the money?";
			if(PCharDublonsTotal() >= 700) // belamour legendary edition
			{
				link.l1 = "Yes. Here are seven hundred doubloons.";
				link.l1.go = "persian_14";
			}
			else
			{
				link.l1 = "Damn it. I left the money on the ship. I'll bring it in a moment!";
				link.l1.go = "exit";
			}
		break;
		
		case "persian_14":
			RemoveDublonsFromPCharTotal(700); // belamour legendary edition
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "cirass8"); 
			//Log_Info("You've received wicker armour");
			AddCharacterExpToSkill(pchar, "Sneak", 300);
			dialog.text = "Yes, my good man! Here, take it. This wicker armour will serve you well, I assure you. There's nothing else like it, not in all the Caribbean!";
			link.l1 = "Yes, I can see that. Thank you! Can't wait to try it on...";
			link.l1.go = "persian_15";
		break;
		
		case "persian_15":
			dialog.text = "Why do you need to wait? Go ahead. Let's see how it fits.";
			link.l1 = "Will do. See you later, Monsieur Fadey!";
			link.l1.go = "persian_16";
		break;
		
		case "persian_16":
			DialogExit();
			pchar.questTemp.Persian = "end";
			pchar.quest.Persian_CirassLamportOver.over = "yes"; //снять прерывание
		break;
		
		// торговля канатами
		case "ropes":
			if (CheckAttribute(pchar, "questTemp.UpgradeRopes"))
			{
				dialog.text = "Come in, my dear friend. The merchandise is ready for you to purchase. 2,125 doubloons for two hundred and fifty pieces.";
				if (PCharDublonsTotal() >= 2125)
				{
					link.l1 = "Everything's as we agreed. Take the money.";
					link.l1.go = "ropes_1";
				}
				else
				{
					link.l1 = "Just let me fetch the coins from my cabin.";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Come in, my dear friend. The merchandise is ready for you to purchase. Five hundred doubloons for fifty pieces.";
				if (PCharDublonsTotal() >= 500)
				{
					link.l1 = "Everything's as we agreed. Take the money.";
					link.l1.go = "ropes_1";
				}
				else
				{
					link.l1 = "Just let me fetch the coins from my cabin.";
					link.l1.go = "exit";
				}
			}
			if(sti(pchar.questTemp.FadeyRopes) >= 1 && !CheckAttribute(pchar, "questTemp.FadeyRopesBlock")) // увеличить объём поставок канатами
			{
				link.l4 = "Fadey, could we increase the volume of our deals? I'm ready to buy five times as many goods from you! I think this would benefit us both. What do you say?";
				link.l4.go = "UpgradeRopes";
			}
			if(sti(pchar.questTemp.FadeyRopes) >= 1 && CheckAttribute(pchar, "questTemp.FadeyRopesPotom") && PCharDublonsTotal() >= 3000) // увеличить объём поставок канатами, если в первый раз не принесли
			{
				link.l4 = "Fadey, I've brought the money! Three thousand gold doubloons, as agreed.";
				link.l4.go = "UpgradeRopes_Agreed";
			}
		break;
		
		case "ropes_1":
			if (CheckAttribute(pchar, "questTemp.UpgradeRopes")) RemoveDublonsFromPCharTotal(2125);
			else RemoveDublonsFromPCharTotal(500); // belamour legendary edition
			PlaySound("interface\important_item.wav");
			dialog.text = "Pleasure doing business with you, "+pchar.name+". I'll order my men to bring the ropes onto your ship.";
			link.l1 = "Thank you!";
			link.l1.go = "ropes_2";
		break;
		
		case "ropes_2":
			dialog.text = "If you still need more ropes, come back in a month.";
			link.l1 = "Very well, Fadey. See you later!";
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.UpgradeRopes")) AddCharacterGoods(pchar, GOOD_ROPES, 250);
			else AddCharacterGoods(pchar, GOOD_ROPES, 50);
			DeleteAttribute(npchar, "quest.ropes");
			SetFunctionTimerCondition("Ropes_FadeyAttrReturn", 0, 0, 1, false); // таймер
			AddCharacterExpToSkill(pchar, "Commerce", 200);
			pchar.questTemp.FadeyRopes = sti(pchar.questTemp.FadeyRopes) + 1; // счётчик покупок
		break;
		
		// уменьшение НЗГ
		case "help":
			if (!CheckAttribute(npchar, "quest.relation_info"))
			{
				dialog.text = "What can I do for you, my dear friend?";
				link.l1 = "You are an influential man, Fadey. A friend of the governor, and, as rumours say, you've got connections at court. Would you be able to petition the authorities in case I get in trouble with the law?";
				link.l1.go = "relation_info";
				break;
			}
			dialog.text = "How can I help you, my friend?";
			if (ChangeCharacterNationReputation(pchar, ENGLAND, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l1 = "I have a problem with the English authorities.";
				link.l1.go = "relation";
				pchar.GenQuest.FadeyNation = ENGLAND;
			}
			if (ChangeCharacterNationReputation(pchar, FRANCE, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l2 = "I've run into trouble with the French authorities.";
				link.l2.go = "relation";
				pchar.GenQuest.FadeyNation = FRANCE;
			}
			if (ChangeContrabandRelation(pchar, 0) <= 5)
            {
                Link.l5 = "I have a serious problem with the smugglers.";
				Link.l5.go = "contraband";
            }
			link.l9 = "Sorry, I think I can handle it myself.";
			link.l9.go = "exit";
		break;
		
		case "relation_info":
			dialog.text = "Oh ho ho, my good man, who told you that? Everybody lies. But since you are Michel's brother and a good friend of mine, I can try to fix things for you. I can petition for you only to the English and French authorities, although my connections have their limits. I don't do business with the Spanish or the Dutch\nI also warn you that my influence is only enough to save you from minor trespasses. I can persuade them to reconsider their attitude towards you in case of slight misconduct or to ease some mild anger. But go off starting a war and expect me to pull your chestnuts out of the fire!\nOn top of that, I can only soothe one nation at a time: France or England. I can't tear myself in half to do two jobs at once. Of course, coin will also be required in order to make bribes. Don't hesitate to come to me for help if you find my terms acceptable.";
			link.l1 = "Thanks, Fadey. I'll keep that in mind.";
			link.l1.go = "exit";
			npchar.quest.relation_info = "true";
		break;
		
		case "relation":
			rate = wdmGetNationThreat(sti(pchar.GenQuest.FadeyNation));
			iFadeyPseudoGlobal = DiplomatDublonPayment(rate, "Fadey", false);
			sTemp = FindRussianDublonString(iFadeyPseudoGlobal);
			if (rate < 2)
			{
				dialog.text = "Of course. I have certainly heard of your adventures - or misadventures. I can take care of your little problem; nothing that the right amount of gold greasing the right palms can't fix. " + sTemp + " and I'll pull you out of the cookpot.";
				if (PCharDublonsTotal() >= iFadeyPseudoGlobal) // belamour legendary edition
				{
					link.l1 = "Great! Here's the gold.";
					link.l1.go = "agree";
				}
				link.l2 = "Then it's just the right time for me to go and get the coins.";
				link.l2.go = "exit";
			}
			else
			{
				if (rate < 4)
				{
					dialog.text = "Of course. I have certainly heard of your adventures - or misadventures. I can take care of your little problem; there's nothing that the right amount of gold greasing the right palms can't fix. " + sTemp + " and I'll pull you out of the cookpot.";
					if (PCharDublonsTotal() >= iFadeyPseudoGlobal) // belamour legendary edition
					{
						link.l1 = "Great! Here's the gold.";
						link.l1.go = "agree";
					}
					link.l2 = "Then it's just the right time for me to go and get the coins.";
					link.l2.go = "exit";
				}
				else
				{
					dialog.text = "Yes, you're in quite the pickle! I can't completely sort out this situation. I can, however, soften the blow of the thunderbolt that is about to descend upon your sinful head. And later, at any moment, we can present a bribe again if you have the money and the desire. " + sTemp + " and I can start to smooth out your troubles.";
					if (PCharDublonsTotal() >= iFadeyPseudoGlobal) // belamour legendary edition
					{
						link.l1 = "I'm tired of the pirate hunters chasing me. Here's the gold.";
						link.l1.go = "agree";
					}
					link.l2 = "Then it's just the right time for me to go and get the coins.";
					link.l2.go = "exit";
				}
			}
		break;
		
		case "agree":
			RemoveDublonsFromPCharTotal(iFadeyPseudoGlobal); // belamour legendary edition
			PlaySound("interface\important_item.wav");
			dialog.text = "Fine, give me about ten to fifteen days. Meanwhile, I'll make arrangements and take care of this and that. It'll all be done in about two weeks. ";
			link.l1 = "Thank you, Fadey! I'll be waiting...";
			link.l1.go = "agree_1";
		break;
		
		case "agree_1":
			DialogExit();
            bOk = HasShipTrait(pchar, "trait23");
            rate = 10 + hrand(5);
            rate = GetIntByCondition(bOk, rate, rate / 2);
			SetFunctionTimerCondition("ChangeNationRelationFromFadeyComplete", 0, 0, rate, false);
			pchar.GenQuest.FadeyNation.Rate = GetDiplomatRate(bOk, sti(pchar.GenQuest.FadeyNation));
			npchar.quest.relation = "true";
		break;
		
		case "contraband":
			iFadeyPseudoGlobal = DiplomatDublonPayment(rate, "Fadey", true);
			sTemp = FindRussianDublonString(iFadeyPseudoGlobal);
			dialog.Text = "Why did you go and anger them, my good man? The smugglers are not the worst folk in this part of the world, and they can turn you a good profit. Fine, I will help you, I know how to butter them up... That'll be " + sTemp + ", no haggling.";
			if (PCharDublonsTotal() >= iFadeyPseudoGlobal) // belamour legendary edition
			{
				Link.l1 = "Very well, Fadey, I agree. Take your gold.";
				Link.l1.go = "Contraband_Agreed";
			}
			Link.l2 = "I don't have that much gold on me right now. I'll come back later!";
			Link.l2.go = "exit";
		break;
		
		case "Contraband_Agreed":
			dialog.Text = "Good, I will patch up the quarrel, don't you worry. They'll do business with you again, just like old times.";
			Link.l1 = "Thank you!";
			Link.l1.go = "exit";
			ChangeContrabandRelation(pchar, GetIntByCondition(HasShipTrait(pchar, "trait23"), 25, 40));
			RemoveDublonsFromPCharTotal(iFadeyPseudoGlobal); // belamour legendary edition
			PlaySound("interface\important_item.wav");
		break;
		
		case "UpgradeRopes":
			dialog.text = "Ho-ho, I see your business is thriving and appetites are growing! You're right, our goods are fine and prices aren't too steep. Mind you though, investments are needed! Such a business requires a serious approach to make everything perfect.";
			link.l1 = "Would I come to you with such an offer without having a couple of hundred doubloons in reserve?";
			link.l1.go = "UpgradeRopes_1";
		break;
		
		case "UpgradeRopes_1":
			dialog.text = "I know you've got coins in your chest, and not just a couple, surely fifty would fit! But our business isn't ordinary - it's not just about moving goods, but finding a way... shall we say, discreet. For such scale, you'll need to invest heavily, not just pay, to make it profitable! And to ensure your money doesn't vanish into thin air. If you're ready to part with three thousand gold doubloons, then take my word that everything will be done right by you, as a good friend, and we won't slight you on the price.";
			if (PCharDublonsTotal() >= 3000)
			{
				Link.l1 = "Three thousand doubloons! Well, I must admit, such a generous offer is rarely heard of, even by the most prosperous merchants, even in the most fantastic tales! Few are willing to invest so generously in such an enterprise. But I, fortunately, am among their number. Here's your money, Monsieur Fadey.";
				Link.l1.go = "UpgradeRopes_Agreed";
			}
			Link.l2 = "Three thousand gold doubloons! I'm not prepared for such a sum, Fadey. Unfortunately. I'll come back later.";
			Link.l2.go = "UpgradeRopes_Potom";
			link.l3 = "Three thousand, you say? Well... To tell the truth, such a sum commands respect for your ambition. But I must admit - this isn't for me.";
			link.l3.go = "UpgradeRopes_2";
		break;
		
		case "UpgradeRopes_2":
			dialog.text = "What a turn! You come with an offer, then immediately back out! I admit, I'm disappointed, but I won't let it ruin our friendship. Let's keep things as before: our previous agreement stands - fifty coils at ten doubloons each, every month, on the 20th.";
			link.l1 = "Good that you understand me, Fadey. I would love to change my mind, but such expenses are beyond me. Alas, my means are limited in this matter.";
			link.l1.go = "UpgradeRopes_3";
		break;
		
		case "UpgradeRopes_3":
			dialog.text = "Well, if that's your decision, there's nothing more to discuss. This won't affect our friendship. Do visit, "+GetSexPhrase("good sir","fair lady")+".";
			link.l1 = "Farewell.";
			link.l1.go = "exit";
			pchar.questTemp.FadeyRopesBlock = true;
		break;
		
		case "UpgradeRopes_Potom":
			DialogExit();
			pchar.questTemp.FadeyRopesBlock = true;
			pchar.questTemp.FadeyRopesPotom = true;
		break;
		
		case "UpgradeRopes_Agreed":
			dialog.text = "Now that's sensible! You're not one for empty talk, but you know how to act. For business people like you, there's always a discount to be found! Fifteen percent off all future shipments! Here's our deal: 250 coils of hemp rope I'll keep ready for you each month. You can collect them, as before, on the 20th, paying 2125 doubloons for everything, no remainder.";
			link.l1 = "Perfect, Fadey! You're remarkably easy to do business with. I'm sure success awaits us. Until next time!";
			link.l1.go = "exit";
			RemoveDublonsFromPCharTotal(3000);
			AddQuestRecordInfo("Unique_Goods", "2_1");
			pchar.questTemp.UpgradeRopes = true;
			pchar.questTemp.FadeyRopesBlock = true;
			DeleteAttribute(pchar, "questTemp.FadeyRopesPotom");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
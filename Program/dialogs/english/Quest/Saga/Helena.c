// Элен МакАртур - сомнительная любовь и офицер
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	string 	sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "What is it?";
			link.l1 = "No, it's nothing.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "After_boarding":
			dialog.text = "Thanks for you help, captain!";
			link.l1 = "My God... You are even more beautiful than I imagined!";
			link.l1.go = "After_boarding_1";
		break;
		
		case "After_boarding_1":
			dialog.text = "To hell with my beauty! Do you know how much grief it has caused me? I'd cut my own nose off if it wouldn't destroy my reputation. That bastard wouldn't let me leave the corvette alive, kept saying that I 'knew too much.' Then yesterday he told me that he was tired of waiting and was going to take me against my will\nYou couldn't have arrived at a better time! But where are my manners, my name is Helen McArthur. My papa used to call me Rumba because I kept accidentally breaking the fine china that he had 'acquired', so that's what my crew call me now.";
			link.l1 = "My name is "+GetFullName(pchar)+" and I'm here to rescue you. I've been scouring the Caribbean for several days looking for you for the sake of Ms. Gladys.";
			link.l1.go = "After_boarding_2";
		break;
		
		case "After_boarding_2":
			dialog.text = "Ms. Gladys!? How is she?";
			link.l1 = "Worried sick about you. But you'll see her soon, we are sailing to Blueweld. You can tell me everything that's happened to you on the way there.";
			link.l1.go = "After_boarding_3";
		break;
		
		case "After_boarding_3":
			dialog.text = "To be honest, "+pchar.name+", I'd like to have some food and a nap right now. I am exhausted after all those days I spent on that monster's ship...";
			link.l1 = "Of course Ms. McArthur. I will order the steward to serve you a meal and prepare a bed for you in your own private quarters.";
			link.l1.go = "After_boarding_4";
		break;
		
		case "After_boarding_4":
			DialogExit();
			LAi_SetActorType(npchar);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			npchar.greeting = "helena_2";
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			pchar.questTemp.Saga = "returntoblueveld";
			Island_SetReloadEnableGlobal("Antigua", true);//на остров можно
			bQuestDisableMapEnter = false;//открыть карту
			AddQuestRecord("Saga", "11");
			pchar.quest.Saga_returnBlueveld.win_condition.l1 = "location";
			pchar.quest.Saga_returnBlueveld.win_condition.l1.location = "Santacatalina_town";
			pchar.quest.Saga_returnBlueveld.function = "Saga_returnBlueveld";
			SetFunctionTimerCondition("Helena_ReturnOver", 0, 0, 45, false);
			sld = characterFromId("gladis");
			sld.greeting = "gladis_3";
		break;
		
		case "Return_blueveld":
			pchar.quest.Helena_ReturnOver.over = "yes";
			dialog.text = "Captain de Maure, I thank you again from the bottom of my heart for your timely rescue. You must visit me and my mother. Our house is not far from here, on your left coming from the pier. And know this "+pchar.name+", I will never forgive you if you sail off without saying goodbye!";
			link.l1 = "The pleasure was all mine, Ms. McArthur. I will be sure to call upon you!";
			link.l1.go = "Return_blueveld_1";
		break;
		
		case "Return_blueveld_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "houseSp3", "SantaCatalina_houseSp3_bedroom", "goto", "goto1", "OpenTheDoors", -1);
			AddQuestRecord("Saga", "13");
			LocatorReloadEnterDisable("SantaCatalina_houseS1", "reload2", false); // открыть кабинет Свенсона
			pchar.questTemp.Saga = "svenson";//идем к Свенсону
			sld = characterFromId("JS_girl");
			sld.dialog.currentnode = "js_girl";
			npchar.dialog.currentnode = "Helena_wait";
			sld = characterFromId("Gladis");
			sld.dialog.currentnode = "Gladis_regard";
			LocatorReloadEnterDisable("SantaCatalina_houseSp3", "reload2", true);//закрыть спальню Элен
			// закрыть город до беседы с Глэдис
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", true);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", true);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", true);
		break;
		
		case "Helena_wait":
			dialog.text = "Ah, there you are, Captain de Maure! I am so glad that you're here, I have lots of questions for you.";
			link.l1 = "I'm sorry Ms. McArthur, but we must delay our conversation a bit. I need to get some more information before I can provide satisfactory answers. Right now I'm asking you to not show yourself on the street. I hope that your waiting will not last long. Trust me and wait.";
			
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.CanDrink")) {
				link.l1.go = "drinking_refuse";
				link.l2 = "You said it yourself that you wouldn't forgive me if I didn't drop by.";
				link.l2.go = "drinking_accept";
				
				DeleteQuestCondition("HelenDrinking_NoVisit");
				DeleteAttribute(pchar, "questTemp.HelenDrinking.CanDrink");
			} else {
				link.l1.go = "exit";
				NextDiag.TempNode = "Helena_wait";
			}
		break;
		
		case "Helena_hire":
			dialog.text = "Ah, there you are, my captain! Your eyes tell me that you've got news for me!";
			link.l1 = "Captain Svenson told me that you want to sail with me. I appreciate your wish, plus Ms. Gladys mentioned that you have missed the sea. Welcome aboard, Ms. Helen McArthur!";
			link.l1.go = "Helena_hire_1";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_friend"))
			{
				link.l2 = "Captain Svenson told me that you want to sail with me. I appreciate your wish, plus Ms. Gladys mentioned that you have missed the sea. Welcome to my crew, Ms. Helen Sharp!";
				link.l2.go = "Helena_hire_2";
				pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 2;
			}
		break;
		
		case "Helena_hire_1":
			DeleteAttribute(pchar, "questTemp.Saga.Helena_friend");
			dialog.text = "Aye aye, captain! I hate to have to say this sir, but I can stand up for myself and I won't tolerate men taking liberties. I'm not responsible for any severed hands or gouged eyes.";
			link.l1 = "Don't worry, I have unshakable discipline on my ship. I must ask you something though...";
			link.l1.go = "Helena_hire_1_1";
		break;
		
		case "Helena_hire_1_1":
			dialog.text = "...Yes?";
			link.l1 = "Jan Svenson and I have found out that you are the rightful heir to Isla Tesoro. Yes, it's true, don't shake your head! I have half of the map which proves your rights. It won't be easy, but Jan and I will do our best to help you become the rightful owner.";
			link.l1.go = "Helena_hire_1_2";
		break;
		
		case "Helena_hire_1_2":
			dialog.text = ""+pchar.name+", are you serious? It's not kind to tease a poor girl like that! How can I have the right to ownership of an entire island?!";
			link.l1 = "I am absolutely serious, Ms. McArthur. And I am going to help you get your birthright. Let's sail now!";
			link.l1.go = "Helena_hire_6";
		break;
		
		case "Helena_hire_2":
			dialog.text = "W-what did you say? Helen Sharp? Why Sharp?";
			link.l1 = "Helen, you are the daughter of Beatrice Sharp and the only heir of the Sharp dynasty. This is half of the map which had been kept by Ms. Gladys for all these years. It's proof of your rights to Isla Tesoro. It won't be easy, but me and Jan Svenson will do our best to help you inherit your grandfather's island.";
			link.l1.go = "Helena_hire_3";
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 3;
			notification("Helen approves", "Helena");
			npchar.lastname = "Sharp";
		break;
		
		case "Helena_hire_3":
			dialog.text = "Oh... My poor mother! I wish I could find her grave one day and pray for her soul there. But... wait! Impossible!";
			link.l1 = "What is it, Ms. Sharp?";
			link.l1.go = "Helena_hire_4";
		break;
		
		case "Helena_hire_4":
			dialog.text = "The gypsy woman's prophecy has just come true... I finally understand it now.";
			link.l1 = "Eh? What prophecy?";
			link.l1.go = "Helena_hire_5";
		break;
		
		case "Helena_hire_5":
			dialog.text = ""+pchar.name+", you might call me naive, but I will tell you anyway. When I was a young girl a gypsy woman told me: 'Your fate will lie in the hands of the man who won't take the widow's coin, who returns the dead man's gold and who names the mother'\nI thought that it was all nonsense back then, but somehow you've managed to fulfil every part of the prophecy, there is no way you'd know about that!";
			link.l1 = "Your fate, you say... Well, perhaps you are right. I won't disappoint you. We will look for your mother's grave together. And for now... Ms. Helen Sharp! Get yourself ready for departure and don't be late!";
			link.l1.go = "Helena_hire_6";
		break;
		
		case "Helena_hire_6":
			dialog.text = "Aye-aye, captain!";
			link.l1 = "...";
			link.l1.go = "Helena_hire_add";
		break;
		
		case "Helena_hire_add":
			LAi_SetImmortal(npchar, false);
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Saga_HireHelena", -1);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", false);//открыть выходы из города
			pchar.questTemp.Saga = "svenson_wait";
			AddQuestRecord("Saga", "24");
			AddQuestUserData("Saga", "sTimer", AddDaysToDateString(367));
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("Saga_BaronsQuestsGo", 0, 0, 2, false);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			
			if (pchar.questTemp.HelenDrinking.Result != "no_visit") {
				AddQuestRecord("HelenDrinking", "3");
				
				SetFunctionLocationCondition("HelenDrinking_IslaTesoroAmbush", "Pirates_town", false);
				sld = &locations[FindLocation("Pirates_town")];
				sld.locators_radius.quest.detector1 = 4.0;
			}
		break;
		
		//-->  консультации по морским сражениям в искушении барбазона
		case "sea_bomb":
			dialog.text = "Captain "+pchar.name+"! I have got an idea...";
			link.l1 = ""+npchar.name+"? It's not safe here and I told you to stay on the ship...";
			link.l1.go = "sea_bomb_1";
		break;
		
		case "sea_bomb_1":
			dialog.text = "Charles, there is so much gunpowder stuffed in this old tub that if it blows up, the whole island will fly straight to St. Peter's front door! Makes no difference if you tell me to hide or not, so listen to me!";
			link.l1 = "Fine, talk fast!";
			link.l1.go = "sea_bomb_2";
		break;
		
		case "sea_bomb_2":
			dialog.text = "The corvette and the frigate. They don't recognize Knive's ship as hostile. We can use their complacency against them. Let's take a few barrels of gunpowder, set a fuse and will sail to the ships\nThey let us close, we'll light the fuse, drop the barrel to one of them and sail away as fast as we can. And then we'll watch a spectacular explosion... What do you say?";
			link.l1 = "An improvised fire ship...very cunning! Your plan is crazy enough that it just might work... if we can get close enough without being recognized.";
			link.l1.go = "sea_bomb_3";
		break;
		
		case "sea_bomb_3":
			dialog.text = "What do we have to lose "+pchar.name+"? It won't be easy to fight two ships at once but we'll get a chance to even the odds...";
			link.l1 = "Fine. Let's get on with this! Lads! Take three barrels of gunpowder! We are going to get the hell out of here! I love your imagination, "+npchar.name+"... I would have never come to this idea myself.";
			link.l1.go = "sea_bomb_4";
		break;
		
		case "sea_bomb_4":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetOfficerType(npchar);
			npchar.dialog.currentnode = "Helena_officer";
			pchar.questTemp.Saga.BarbTemptation.Bomb = "true";
			pchar.questTemp.Saga.BarbTemptation.adviser = "Helena";
		break;
		
		case "fugas":
			dialog.text = "Aye captain, what is the matter?";
			link.l1 = "Jackman's ship is at Sabo-Matila Cove, the heavy frigate 'Centurion'. This ship was once property of the Hawkes, so there must be important items and documents in Jackman's cabin...we must board it.";
			link.l1.go = "fugas_1";
		break;
		
		case "fugas_1":
			dialog.text = "Easier said than done. How are you going to do that on our polacre? They outman and outgun us.";
			link.l1 = "You are right. Jackman has at least twice more men than we have and all of them are experienced fencers. It would be madness to attack them without a preliminary bombardment. But protracted fighting is not the best option either. So I've been thinking about what to do.";
			link.l1.go = "fugas_2";
		break;
		
		case "fugas_2":
			dialog.text = ""+pchar.name+", they haven't recognized us as an enemy yet, just like those idiots back at Turks... We can try our trick again...";
			link.l1 = "Helen, I have just told you that we have to board and search the frigate, blowing it to kingdom come is not an option.";
			link.l1.go = "fugas_3";
		break;
		
		case "fugas_3":
			dialog.text = "Wait a minute, "+pchar.name+", we won't sink her. Let's put a twist on it.  Listen, we are going to take a few empty rum barrels and fill them with gunpowder, grapeshot, and short fuses. Then we will sail closer to their frigate and throw the improvised explosives onto their deck.";
			link.l1 = "Ha! Your feminine ingenuity continues to amaze me! Instead of a fire ship, you suggest a fougasse? You think that it could work?";
			link.l1.go = "fugas_4";
		break;
		
		case "fugas_4":
			dialog.text = "And why not? Their freeboard is higher than ours but two or three men aided by a pulley could hoist and throw a fully loaded barrel easily. We'll call out - 'Here's some free rum from Knive! And the barrels will explode before they can even react";
			link.l1 = "The exploding grapeshot will turn his best men on deck into mince... Damn, it sounds tempting.";
			link.l1.go = "fugas_5";
		break;
		
		case "fugas_5":
			dialog.text = "Let's throw five barrels at once from the quarterdeck to the poop. "+pchar.name+", we have the element of surprise. They won't suspect a thing yet! And then we will immediately sail away from them before they have a chance to board us.";
			link.l1 = "Well, let's try. They must not identify us before we get those explosive barrels on their deck... It won't be easy to close. Jackman is not as great a fool as Ghoul was.";
			link.l1.go = "fugas_6";
		break;
		
		case "fugas_6":
			dialog.text = "Let's risk it, "+pchar.name+"! Like I said before, what do we have to lose?";
			link.l1 = "Good point... Stand to boys! Prepare the fougasses and get ready to fight!";
			link.l1.go = "fugas_7";
		break;
		
		case "fugas_7":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			pchar.questTemp.Saga.BarbTemptation.Fugas = "true";
			AddQuestRecord("BarbTemptation", "21");
			DeleteAttribute(npchar, "quest.fugas");
		break;
		//<--  консультации по морским сражениям
		
	// --> разговор по итогам Саги
		case "result":
			//if (!CheckAttribute(pchar, "questTemp.Saga.Helena_friend")) // не друзья
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 11) {
				Achievment_Set("ach_CL_83");
			}
			
			if (sti(pchar.questTemp.Saga.HelenRelation) < 6)
			{
				dialog.text = "Well, my dear captain... It is time for us to say goodbye to each other. My service is over and it's time to get used to being the Pirate Queen of Isla Tesoro. I hope that I will be a worthy successor to my uncle. Thank you for your help.";
				link.l1 = "Aye, it's a pity to part with you, but such are the whims of fate. You have much more important resposibilities now than serving on my ship.";
				link.l1.go = "result_1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.HelenDrinking.Mary")) {
					dialog.text = "I'd love to be able to stay on your ship. Close to you... But it's impossible. Be happy, Charles. And she better be worthy of you!";
					link.l1 = "I'm sorry, Helen.";
					link.l1.go = "result_mary";
				} else {
					dialog.text = "It's so strange, "+pchar.name+"! I have just become an owner of a whole island but I don't feel myself a Queen of Isla Tesoro... I suppose that a new head of the Brethren will manage the colony better than I would. I have a lot to learn.";
					link.l1 = "Don't worry about it Helen, you are a woman who can take care of herself - just like you told me when you first came aboard.";
					link.l1.go = "result_9";
				}
			}
			
			DeleteQuestCondition("HelenDrinking_AtSHDN");
			DeleteQuestCondition("HelenDrinking_InBlueweldAfterCave");
		break;
		
		case "result_mary":
			dialog.text = "Well, we'll still be friends, won't we?";
			link.l1 = "Of course... Helen, we will meet again on Isla Tesoro. Should I take you to your island?";
			link.l1.go = "result_12";
		break;
		
		case "result_1":
			dialog.text = "You are right... Look, I saved my share of plunder while sailing on your ship. Take it and don't even try to reject my offer - I don't want to be in your debt.";
			link.l1 = "Hey now, just wait a moment...";
			link.l1.go = "result_2";
		break;
		
		case "result_2":
			dialog.text = "I know what you are going to say. Sure, you help was much more significant than this meager chest of treasure. But this is all I have got in my possesion right now and I must repay you. Take it, if you don't take it yourself I will leave it in your cabin.";
			link.l1 = "Are you going to sail on your own now? Perhaps I could take you to Isla Tesoro?";
			link.l1.go = "result_3";
		break;
		
		case "result_3":
			GiveItem2Character(pchar, "chest");
			Log_Info("You have received a chest with doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "No need for that, "+pchar.name+". I will get to the island myself. I've got my sword and pistol on me, it will suffice for a while... I am sure that the Queen of Isla Tesoro doesn't need to worry about income once I get there.";
			link.l1 = "Aye aye, your majesty. I wish you luck in your new life.";
			if (!CheckAttribute(pchar, "questTemp.Saga.Beltrop_die")) link.l1.go = "result_4";
			else link.l1.go = "result_7";
		break;
		
		case "result_4":
			dialog.text = "Enough of that, even in jest. I'm still Helen to you. But that is not all I wanted to say. I have found my father again, though it was a bit strange. He has paid with his good name of an English nobleman for my inheritance and that bothers me. The English Commonwealth hunts him and I don't want you, "+pchar.name+", to participate in it.";
			link.l1 = "Come to your senses, Helen! He is a bandit and a pirate!";
			link.l1.go = "result_5";
		break;
		
		case "result_5":
			dialog.text = "Pirate? And who the fuck are you to say something like that? He is my father and that's what matters to me! And I, the daughter of a bandit and a pirate, don't give a fuck what the English justice thinks of him. If you try to harm my father in any way, I will forget everything good you have done to me, know that. Consider this a warning.";
			link.l1 = "Is that so? Actually girl, you'd better be more polite. I didn't notice any complaints from you about my piratical attitude while I was saving your pretty skin from the hands of that rapist Donovan, or when we were sharing the profits of our captures!";
			link.l1.go = "result_6";
		break;
		
		case "result_6":
			dialog.text = "I.....I am sorry. I take it back, forgive me. I lost my head... But still, I'd like to stay your friend which would be impossible if you start chasing my father.";
			link.l1 = "Understood. But don't ever dare to threaten me, woman. You should know by now from sailing on my ship, that I don't fear anyone and anything. I especially will not tolerate disrespect from a woman - Pirate Queen or not. I may be a gentleman, but even my patience has its limits. Now that is settled, farewell. I wish you luck.";
			link.l1.go = "result_8";
		break;
		
		case "result_7":
			dialog.text = "Thank you.... Perhaps we will meet again, "+pchar.name+"...";
			link.l1 = "And why not? I will visit Isla Tesoro more than once in future. See you there... Goodbye, Helen.";
			link.l1.go = "result_8";
		break;
		
		case "result_8": // Элен уходит, но её не затираем
			DialogExit();
			RemovePassenger(pchar, npchar);
			//chrDisableReloadToLocation = true;//закрыть локацию  // уже не надо.
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "goto", "goto24", "", "", "", "", 7);//OpenTheDoors лесник . чтобы бежала и исчезла а не стояла.
			AddQuestRecord("Testament", "11");
			CloseQuestHeader("Testament");
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false); // лесник . пирс. 
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false); // ворота.
			InterfaceStates.Buttons.Save.enable = true;//можно сохраняться		
			if (CheckAttribute(pchar, "questTemp.LSC.MaryWait")) {
				pchar.questTemp.LSC.Mary = "return";
			}
		break;
		
		case "result_9": // вот тут - ключевой момент, если игрок нашёл Мэри - выбирай, какая девушка милее
			dialog.text = "I am sure. "+pchar.name+", I'd like to stay on your ship if you let me. To stay with you...";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive")
			{
				link.l1 = "(choose Mary) You don't understand, Helen. Your whole future is ahead of you and there is nothing for you to worry about. All I have is war, political intrigues and total uncertainty ahead of me. You have to arrange a life of your own, there is no room for such a wild rover like me in it.";
				link.l1.go = "result_10";
				link.l2 = "(choose Helen) It's more than I could hope for, Helen. Of course I don't want to lose you, but it would be better for you to go to Isla Tesoro. Who knows where my fate will lead me to yet. Right now, I have a war, political intrigues, and uncertainty ahead of me.";
				link.l2.go = "result_15";
			}
			else
			{
				link.l1 = "It's more than I could hope for, Helen. Of course I don't want to lose you, but it would be better for you to go to Isla Tesoro. Who knows where my fate will lead me to yet. Right now, I have a war, political intrigues, and uncertainty ahead of me.";
				link.l1.go = "result_15";
			}
		break;
		
		case "result_10":
			dialog.text = ""+pchar.name+"! Don't lie to me. You just don't want to... Tell me, who is she? It's that redheaded strumpet from the City of Abandoned Ships am I right?";
			link.l1 = "Helen! I'm trying to tell you what I think is best for you! How do you not understand that?!";
			link.l1.go = "result_11";
		break;
		
		case "result_11":
			dialog.text = "Oh sure, of course you are... And how was she able to charm you, huh? What does she have that *I* don't?! Is she really that good? Eh, "+pchar.name+"... Well, it's your decision, I have nothing left but to go to my island. I can't stand between you two\nThank you for everything you've done for me, Charles. You are the best man I've ever met. I hope that we can stay friends?";
			link.l1 = "Of course... Helen, I will see you again on Isla Tesoro. Do you want me to take you there?";
			link.l1.go = "result_12";
		break;
		
		case "result_12":
			dialog.text = "No need. I will buy a new ship. I have collected enough money to buy and to equip a schooner while serving under your command. I will sail on a new 'Rainbow' again.";
			link.l1 = "I am glad, Helen, that you were so... thrifty. But sailing on a schooner doesn't suit the Pirate Queen of Isla Tesoro. Soon, you should get a frigate for yourself.";
			link.l1.go = "result_13";
		break;
		
		case "result_13":
			dialog.text = "Perhaps, "+pchar.name+". Fine. I will go to the shipyard but first... give me a kiss goodbye... Please...?";
			link.l1 = "Helen...";
			link.l1.go = "result_14";
		break;
		
		case "result_14": // прощальный поцелуй
			DialogExit();
			SetMusic("music_romantic");
			SetLaunchFrameFormParam("", "", 0, 12);
			SetLaunchFrameFormPic("loading\inside\kiss.tga");
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 0, 20); //крутим время
			RecalculateJumpTable();
			DoQuestCheckDelay("Saga_HelenaBye", 0.5);
			pchar.questTemp.LSC.Mary = "return"; // к Мэри
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false); // лесник . пирс. 
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false); // ворота.
			InterfaceStates.Buttons.Save.enable = true;//можно сохраняться
		break;
		
		case "result_15":
			dialog.text = "My fate is your fate ever since we met. Don't you understand that? "+pchar.name+"? I will follow you to the ends of the world!";
			link.l1 = "And what of your father? Laurence Beltrope? He is my enemy...";
			link.l1.go = "result_16";
		break;
		
		case "result_16":
			dialog.text = "My father is Sean McArthur. I loved him and mourned his death. He was my only father. And that pirate... I don't even want to talk about him.";
			link.l1 = "Helen... My dear Helen!";
			link.l1.go = "result_17";
		break;
		
		case "result_17":
			dialog.text = ""+pchar.name+", I have always wanted to tell you are the greatest man I have ever met! You have done so much for me that I will never be able to repay you. I want to stay with you. Forever. I will marry you if you want... I love you.";
			link.l1 = "We will be together. I promise!"; // а куда же ты теперь денешься :)
			if (!CheckAttribute(pchar, "questTemp.Saga.Helena_friend")) {
				link.l1.go = "result_17A";
			} else {
				link.l1.go = "result_18";
			}
		break;
		
		case "result_17A":
			dialog.text = "Promise you'll do something for me right now? And please don't laugh!";
			link.l1 = "I promise, my dear!";
			link.l1.go = "result_17A_1";
		break;
		
		case "result_17A_1":
			dialog.text = "Call me by my real name. Please!";
			link.l1 = "I love you, Helen Sharp.";
			link.l1.go = "result_18";
		break;
		
		case "result_18":
			dialog.text = ""+pchar.name+", dear... Embrace me! I have been waiting for this moment for too long!";
			link.l1 = "Helen, my dear...";
			link.l1.go = "result_19";
		break;
		
		case "result_19": // романтик-сцена
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			StartQuestMovie(true, true, true);
			PlayStereoOGG("music_romantic");
			InterfaceStates.Buttons.Save.enable = false;//запретить сохраняться
			locCameraRotateAroundHero(0.0, 2.0, 0.0, 0.01, 0.0, 2.0, 0.0, 580);
			Pchar.FuncCameraFly = "";
			DoQuestCheckDelay("Saga_HelenaRomantic", 20.0);
			pchar.GenQuest.MusicContinue = true;
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			DeleteAttribute(pchar, "questTemp.LSC.MaryWait");
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false); // лесник . пирс. 
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false); // ворота.																					   
			
			pchar.quest.HelenUpgradeShip.win_condition.l1 = "Timer";
			pchar.quest.HelenUpgradeShip.win_condition.l1.date.day = GetAddingDataDay(0, 0, 180);
			pchar.quest.HelenUpgradeShip.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 180);
			pchar.quest.HelenUpgradeShip.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 180);
			pchar.quest.HelenUpgradeShip.win_condition.l2 = "location";
			pchar.quest.HelenUpgradeShip.win_condition.l2.location = "PortRoyal_town";
			pchar.quest.HelenUpgradeShip.function = "HelenUpgradeShip";
			
			// Квест Лонгвея "Путеводная звезда", начало 5 этапа
			if (GetCharacterIndex("Longway") != -1 && CheckPassengerInCharacter(pchar, "Longway") && CheckAttribute(pchar, "questTemp.PZ_Etap5_Start") && !CheckAttribute(pchar, "questTemp.PZ_ProvalFinal"))
			{
				PChar.quest.PZ_Etap5_Start.win_condition.l1 = "location";
				PChar.quest.PZ_Etap5_Start.win_condition.l1.location = "Pirates_town";
				PChar.quest.PZ_Etap5_Start.win_condition = "PZ_Etap5_Start";
				AddMapQuestMarkCity("Pirates", false);
			}
		break;
		
		case "happy":
			dialog.text = ""+pchar.name+"! That was... incredible! I don't want to go anywhere else... Let's stay here until morning. The world can wait!";
			link.l1 = "We'll let it wait, Helen!";
			link.l1.go = "happy_1";
		break;
		
		case "happy_1":
			DialogExit();
			LSC_MaryLoveWaitTime();
			SetLaunchFrameFormParam("Next morning...", "", 0, 4);
			LaunchFrameForm();
			DoQuestCheckDelay("Saga_HelenaRomantic_5", 4.0);
			pchar.questTemp.Saga.Helena_officer = "true"; // показатель, что Элен - наша навсегда
			
			pchar.GenQuest.BrothelCount = 0;
			
			pchar.quest.Helen_GiveSex.win_condition.l1 = "Timer";
			pchar.quest.Helen_GiveSex.win_condition.l1.date.day = GetAddingDataDay(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l1.date.month = GetAddingDataMonth(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l1.date.year  = GetAddingDataYear(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l2 = "Location_Type";
			pchar.quest.Helen_GiveSex.win_condition.l2.location_type = "town";
			pchar.quest.Helen_GiveSex.function = "Helen_GiveSex";
			
			// Запуск квеста Дороже золота
			SetFunctionTimerCondition("GoldenGirl_Start", 0, 0, 1, false);
		break;
		
	// -------------------------------------------- провалы саги ------------------------------------
		case "failcenturion":
			dialog.text = "Captain! Jackman is dead... Is my family finally safe?";
			link.l1 = "Yes, Helen, you are all safe. But 'Centurion' was sunk and so were all the documents which could help us find your mother's grave and prove your rights to claim Isla Tesoro... Eh... Now I will have to storm Tortuga on my own...";
			link.l1.go = "failcenturion_1";
		break;
		
		case "failcenturion_1":
			dialog.text = ""+pchar.name+", don't worry so much. There is nothing we can do about it. Don't worry about me either, I will live fine without that island. Thank you for all you've done for me!";
			link.l1 = "It sounds like you are going to... leave me, right?";
			link.l1.go = "failcenturion_2";
		break;
		
		case "failcenturion_2":
			dialog.text = "Yes, my captain. I was able to collect enough money to buy and to equip a schooner. I will sail on my 'Rainbow' again. We will meet again in Blueweld... I am going back home.";
			link.l1 = "Well... good luck, Helen!";
			link.l1.go = "failcenturion_3";
		break;
		
		case "failcenturion_3":
			DialogExit();
			RemovePassenger(pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 5.0);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary") && GetCharacterIndex("Mary") != -1 && !CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) // patch-6
			{
				pchar.questTemp.LSC.Mary = "return"; // к Мэри
			}
		break;
		
		case "late_l1":
			dialog.text = "Well, my captain... It seems that we have failed. Farewell. I am going back home. I have earned enough money under your command to buy a new schooner for myself. We will meet again at sea!";
			link.l1 = "Good luck, Helen. I am sorry for everything. Farewell.";
			link.l1.go = "failcenturion_3";
		break;
		
		case "late_l2":
			dialog.text = "Captain! Jackman is dead... So it seems that my family is safe, isn't it?";
			link.l1 = "Yes, Helen, it is safe. But I am not happy, I lost too much time and Isla Tesoro is now an English colony. You were left without your inheritance, so I'll have to storm Tortuga myself...";
			link.l1.go = "failcenturion_1";
		break;
		
		case "late_l3":
			dialog.text = ""+pchar.name+", what did the lawyer tell you?";
			link.l1 = "I have lost too much time and Isla Tesoro is now an English colony. You were left without your inheritance, so I'll have to storm Tortuga myself... Alas, we've lost.";
			link.l1.go = "failcenturion_1";
		break;
	// <-- провалы Саги
		
		// секс - Элен соглашается не всегда (голова болит, а что вы хотели? :)) и сама не требует секса
		case "cabin_sex":
			if (CheckAttribute(npchar, "quest.refusesex")) {
				dialog.text = "No, darling, it won't work.";
				link.l1 = "Well, why not?!";
				link.l1.go = "refuse";
				break;
			}
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
			if (drand(4) == 0)// вероятность отказа 20%
			{
				dialog.text = RandPhraseSimple(""+pchar.name+", I am not feeling well today. Don't feel bad, please, it's not your fault. Let's not do it today...",""+pchar.name+", dear, I have been so tired for the last few days. To be honest, I only want to sleep. Forgive me. Let's do it another time.");
				link.l1 = RandPhraseSimple("Fine...","That's alright. As you wish...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = RandPhraseSimple(""+pchar.name+", the mood is just right, let's go!",""+pchar.name+", sure, no questions asked! Let's go!");
				link.l1 = RandPhraseSimple("That's my girl...","You are so lovely, Helen...");
				link.l1.go = "exit";
				pchar.quest.sex_partner = Npchar.id;
				AddDialogExitQuest("cabin_sex_go");
			}
		break;
		
		case "sex_after":
			dialog.text = LinkRandPhrase(RandPhraseSimple("It was wonderful, "+pchar.name+"!..","You were great as always, dear..."), RandPhraseSimple("It was great, Charles!","Had a wonderful time, dear!"), RandPhraseSimple("Never boring with you, my captain!","You were wonderful, darling!"));
			link.l1 = RandPhraseSimple("I love you...","It is always good to be with you, Helen...");
			link.l1.go = "exit";
			NextDiag.TempNode = "Helena_officer";
			chrDisableReloadToLocation = false;//открыть локаци.
		break;
		
		case "room_sex":
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "tavern")
			{
				dialog.text = ""+pchar.name+", you know I am always glad to... But it's not the right time now - we have to catch that scoundrel Thibaut before he escapes.";
				link.l1 = "You are right as always, Helen...";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(npchar, "quest.refusesex")) {
				dialog.text = "No, darling, it won't work.";
				link.l1 = "Well, why not?!";
				link.l1.go = "refuse";
				break;
			}
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
			if (drand(4) == 0) // вероятность отказа 20%
			{
				dialog.text = RandPhraseSimple(""+pchar.name+", I am not feeling well today. Don't feel hurt, please. Let's not do it today...",""+pchar.name+", dear, I have been so tired for the last few days. To be honest, I only want to sleep. Forgive me. Let's do it another time.");
				link.l1 = RandPhraseSimple("Fine...","That's alright. As you wish...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = RandPhraseSimple(""+pchar.name+", I love you! Let's go!",""+pchar.name+", aye aye captain! Let's go!");
				link.l1 = RandPhraseSimple("You are my good girl...","You are gorgeous, Helen...");
				link.l1.go = "room_sex_go";
			}
		break;
		
		case "room_sex_go":
			DialogExit();
			pchar.quest.sex_partner = Npchar.id;
			chrDisableReloadToLocation = true;
			//npchar.quest.daily_sex_room = true; // для первого раза в таверне чтобы счетчик запустить . лесник
			//npchar.quest.daily_sex_cabin = true;
			if (sti(pchar.money) >= 10) AddMoneyToCharacter(pchar, -10);
			sld = CharacterFromID("Helena");
			ChangeCharacterAddressGroup(sld, loadedLocation.fastreload + "_tavern_upstairs", "quest", "quest3");
			DoFunctionReloadToLocation(loadedLocation.fastreload + "_tavern_upstairs", "quest", "quest4", "GiveKissInRoom");
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Helena_officer":
			ref rLoc = &Locations[FindLocation(pchar.location)];
			dialog.text = LinkRandPhrase("Yes, "+pchar.name+"?","Yes, my captain?","I am listening, "+pchar.name+"...");
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.CutlassTraining")) {
				DeleteAttribute(pchar, "questTemp.HelenDrinking.CutlassTraining");
				dialog.text = "Watch this, my captain!";
				link.l1 = "Wow, what a grip! I see you didn't waste any time, Helen.";
				link.l1.go = "cutlass_training";
				NextDiag.TempNode = "Helena_officer";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && sti(pchar.GenQuest.BrothelCount) > 0 && !CheckAttribute(npchar, "quest.refusesex")) {
				dialog.text = "Darling, about your visits to prostitutes.";
				npchar.quest.refusesex = true;
				link.l1 = "What? Helen, you've got it all wrong! I just...";
				link.l1.go = "brothel_found";
				NextDiag.TempNode = "Helena_officer";
				SetFunctionTimerCondition("Helena_ClearRefuseSex", 0, 0, 180, false);
				DeleteQuestCondition("Helen_GiveSex");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Helen, I am going to visit the lost Indian city of Tayasal. I won't lie to you: this trip is very dangerous and even more - it includes teleportation through the idol. Will you... follow me?";
				Link.l4.go = "tieyasal";
			}
       ////////////////////////казначей///////////////////////////////////////////////////////////
           		// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Helen, give me a full ship report.";
			    Link.l11.go = "QMASTER_1";
			        
			    // Warship. Автозакупка товара
				Link.l12 = "I want you to purchase certain goods every time we are docked.";
				Link.l12.go = "QMASTER_2";
			}
			
            /////////////////////////////////////казначей////////////////////////////////////////////////////////////     			
			if (CheckAttribute(NPChar, "IsCompanionClone"))//////////////////компаньон//////////////////////////////////////////////
			{
				//dialog.text = "Я прибыл по вашему распоряжению, капитан.";
				Link.l2 = "Helen, I need to give you several orders.";
				Link.l2.go = "Companion_Tasks";
				
				sld = GetCharacter(sti(npchar.RealCompanionIdx));
				if (CheckAttribute(pchar, "questTemp.HelenDrinking.Rainbow") && sld.ship.type == pchar.questTemp.HelenDrinking.Rainbow && CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) {
					DeleteAttribute(link, "");
					dialog.text = "Do you think it's funny?";
					link.l1 = "Nice vessel, isn't it? Got it for you, Helen! Just think, what kind of a guy in the Caribbean gives his lady a real ship, huh?";
					link.l1.go = "rainbow";
					
					NextDiag.TempNode = "Helena_officer";
					break;
				}
				
				NextDiag.TempNode = "Helena_officer";// не забыть менять в зависисомости от оффа
				break;
			}																															
			if (CheckAttribute(npchar, "quest.fugas"))
			{
				Link.l3 = "Helen, I need your advice.";
				Link.l3.go = "fugas";
			}
			Link.l1 = "Helen, I have an order for you...";
            Link.l1.go = "stay_follow";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && pchar.location == Get_My_Cabin() && GetNpcQuestPastDayWOInit(npchar, "sex_date") >= 1) // mitrokosta - очередные исправления интима
			{
				Link.l2 = RandPhraseSimple("Helen, let's stay in the cabin together alone... for a few hours? What do you think?","Darling, let's spend next the few hours tete-a-tete? Do you like this idea?");
				Link.l2.go = "cabin_sex";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && rLoc.type == "tavern" && sti(pchar.money) >= 10 && GetNpcQuestPastDayWOInit(npchar, "sex_date") >= 1) // mitrokosta - очередные исправления интима
			{
				Link.l2 = RandPhraseSimple("Helen, why don't we rent a room and stay there in private... for the next few hours? How do you feel about that?","Darling, let's spend next few hours tete-a-tete? We'll rent a room... what do you think?");
				Link.l2.go = "room_sex";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && rLoc.type == "town" && sti(pchar.money) >= 1000 && GetNpcQuestPastDayWOInit(npchar, "special_sex_date") >= 30 && !CheckAttribute(npchar, "quest.refusesex"))
			{
				Link.l2 = "Helen, dear, may I invite you to spend some quality time at the tavern?";
				Link.l2.go = "special_sex";
			}
			if (CheckAttribute(pchar, "questTemp.MysteryPortRoyal_Helena")) {
				link.l4 = "Helen, it looks like I found the last will of your admirer – Francis. He left you his inheritance.";
				link.l4.go = "MysteryPortRoyal_Helena_1";
			}
			if (CheckCharacterItem(pchar, "pirate_cutlass") && !CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) {
				link.l4 = "I think this cutlass is now yours. Blaise is your so-called uncle...";
				link.l4.go = "give_cutlass";
			}
			link.l9 = "Nothing right now, Helen.";
			NPChar.id = "Helena"; // лесник . Идентификация Элен на всяк. случай . если потеряет сознание.
			link.l9.go = "exit";
			NextDiag.TempNode = "Helena_officer";
		break;
		
		/////////////////////////// ответы для казнаячея - Элен ..(элен казначей - ужас!))///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Charles, dear, are you sick or something? What, you expect me to go down below, sweep the hold and start counting rats?";
			Link.l1 = "Right, sorry darling, my bad...";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "And I want my very own ship of the line, with a hundred guns flying at 20 knots. I've been a captain like you all my life. Go get yourself a bloody purser and bother him with it.";
			link.l1 = "Aye, you're right, Helen. Sorry about that.";
			link.l1.go = "exit";
		break;
		//Указания для компаньона 19.02.08 -->/////////////////////////////////////////////////////////////////////////////////////////
		case "Companion_Tasks":
			dialog.Text = "I am all ears.";
			Link.l1 = "About our boarding policy...";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "About the ship you command...";
			Link.l2.go = "Companion_TaskChange";
			Link.l8 = "Nothing so far.";
			Link.l8.go = "exit";
			 
		break;
		
		case "Companion_TaskBoarding":
			dialog.Text = "What is your wish, my captain?";
			Link.l1 = "I don't want you to board anything. Keep yourself and your men safe.";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "I want you to board enemy ships at the first opportunity.";
			Link.l2.go = "Companion_TaskBoardingYes";
		break;
		
		case "Companion_TaskChange":
			dialog.Text = "Yes, my captain?";
			Link.l1 = "I'd appreciate it if you abstained from swapping ships after boarding. She's too valuable for me.";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "If you happen to board anyone, take a good look at the prize vessel. If she's any good, feel free to take her for yourself.";
			Link.l2.go = "Companion_TaskChangeYes";
		break;
		
		case "Companion_TaskBoardingNo":
			dialog.Text = "Fine, I'll think about it.";
			Link.l1 = "She'll think about it... Right, like I can give her orders anyway.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
		break;
		
		case "Companion_TaskBoardingYes":
			dialog.Text = "Fine, I'll think about it.";
			Link.l1 = "She'll think about it... Right, like I can give her orders anyway.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
		break;
		
		case "Companion_TaskChangeNo":
			dialog.Text = "Fine, I'll think about it.";
			Link.l1 = "She'll think about it... Right, like I can give her orders anyway.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;
		
		case "Companion_TaskChangeYes":
			dialog.Text = "Fine, I'll think about it.";
			Link.l1 = "She'll think about it... Right, like I can give her orders anyway.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;
	//	<========//////////////////////////////////////																																			  
		
		case "stay_follow":
            dialog.Text = "Orders?";
            Link.l1 = "Stand here!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Follow me and keep up!";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Change the type of ammo for your firearms.";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Choose the type of ammo:";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");;
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;		
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "At once, captain!";
            Link.l1 = "...";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "At once, captain!";
            Link.l1 = "...";
            Link.l1.go = "Exit";
        break;
		//<-- ----------------------------------- офицерский блок ----------------------------------------
		
		// --> суп из черепахи
		case "terrapin_grot":
			dialog.text = "There you are! I finally found you... That was something, my captain! I have never seen such a roof run and a jump from such a breathtaking height! My heart was ready to explode! One day you will kill me with these tricks of yours, dear... Oh, you're not alone... Who is this girl?";
			link.l1 = "This is Catherine Fox, the daughter of Colonel Fox, the commander of the famed English Maritime Regiment of Foot, the 'Sea Foxes'. We are taking her to Antigua.";
			link.l1.go = "terrapin_grot_1";
		break;
		
		case "terrapin_grot_1":
			dialog.text = "Is that so...Welcome aboard Ms. Fox! .No no, don't hold Captain de Maure's arm, you can walk just fine on your own! And now let's get to the longboat - we need to get out of here."; 
			link.l1 = "Ha! Thank you Helen! What would I do without you? Catherine, follow us!";
			link.l1.go = "terrapin_grot_2";
		break;
		
		case "terrapin_grot_2":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			Terrapin_GotoShip();
		break;
		// <-- суп из черепахи
		
		// --> калеуче
		case "on_coast":
			dialog.text = "Finally you woke up, dear! How do you feel? You scared me half to death...";
			link.l1 = "Helen, what happened? My head is splitting...";
			link.l1.go = "on_coast_1";
		break;
		
		case "on_coast_1":
			dialog.text = "When we entered the captain's cabin, you were lying on the floor still. My heart almost stopped beating! The boys picked you up and dragged you back to our ship - just in time, since the dead men lying on the deck began to rise again.\nWhat a horror! It's almost enough to make me find God! They were totally impervious to our blades and bullets! We quickly cut the ropes and tried to sail away, but a volley from their ship severely damaged our ship and we lost control. Then they hoisted sails and were gone in the blink of an eye.\nOur ship ran aground, so we had to flee to this shore before the storm could destroy her. Many good people died today, but the ship survived in the end... if only I didn't command to abandon it...";
			link.l1 = "Not your fault, Helen. It was the right call. What would I do without you?";
			link.l1.go = "on_coast_2";
		break;
		
		case "on_coast_2":
			dialog.text = "I dragged you into the boat and then got you ashore. You looked dead, only your heart was beating very faintly. Look! My hands are still shaking";
			link.l1 = "Thank you, love. I am indebted to you. How long have I been lying here?";
			link.l1.go = "on_coast_3";
		break;
		
		case "on_coast_3":
			dialog.text = "For an entire day. I washed and bound your wounds, gave you medicine and poured some rum into you. Now you must get well!";
			link.l1 = "I won't die this time, darling. Although I don't feel well...blurgh....";
			link.l1.go = "on_coast_4";
		break;
		
		case "on_coast_4":
			dialog.text = "Tell me....Was it the real 'Flying Dutchman', Charles? Why did they attack us? And why didn't they shoot at us upon approach, but tied to sink us immidiately after they boarded?";
			link.l1 = "Their captain needed that amulet, about which I had talked to Tuttuathapak, an Indian shaman. Why they needed it I don't know...but as soon as their leader got the amulet, they disposed of us...God Almighty, what a wretched nightmare! A ship manned by the living dead! Impossible to believe...";
			link.l1.go = "on_coast_5";
		break;
		
		case "on_coast_5":
			dialog.text = "Aye, now it was our turn to encounter the 'Flying Dutchman'. Gah! It makes my skin crawl! Next port we stop at, I'm going to church, lighting a candle, and praying to our Lord Jesus Christ for our miraculous deliverance. Hell, I'm feeling so grateful that I'll even pray to some papish saints...";
			link.l1 = "I'll be there right with you Helen, I haven't been to a proper confession in a while... But first we have to go back to that village. I need to tell Tuttuathapak everything. That accursed ship attacked us because of the amulet! I hope that red-skinned devil has some ideas why the hell those living dead might have needed it.";
			link.l1.go = "on_coast_6";
		break;
		
		case "on_coast_6":
			dialog.text = "Alright. But we must be careful - your wounds have barely healed.";
			link.l1 = "But you will help me heal faster, won't you? I love you Helen...";
			link.l1.go = "on_coast_7";
		break;
		
		case "on_coast_7":
			chrDisableReloadToLocation = false;//открыть локацию
			dialog.text = "I love you too, my darling...";
			link.l1 = "...";
			link.l1.go = "on_coast_8";
		break;
		
		case "on_coast_8":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			AddQuestRecord("Caleuche", "5");
		break;
		// <-- калеуче
		
		// на Тайясаль
		case "tieyasal":
			dialog.text = ""+pchar.name+", I have told you once that we share fates now. Your fate is my fate. When are we going?";
			link.l1 = "I am very glad to hear that. I will tell you a bit later when we go there. We need to prepare ourselves.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "I am ready, my captain! I will follow you the ends of the Earth!";
			link.l1 = "Thank you, my love...";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "20");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		// на Исла Тесоро
		case "islatesoro":
			dialog.text = "Oh, "+pchar.name+"! Glad to see you! What are you doing here on Isla Tesoro?";
			link.l1 = "Same as always - business. Just wanted to stop by and see you too. How is everything, Helen?";
			link.l1.go = "islatesoro_1";
		break;
		
		case "islatesoro_1":
			DialogExit();
			NextDiag.CurrentNode = "islatesoro";
		break;
		
		// Jason Дороже золота
		case "GoldenGirl":
			dialog.text = "What's the matter with our dearest governor, Captain? Whose arse are we kicking this time? Spaniards, pirates, or someone worse?";
			link.l1 = "It's worse, Helen, much worse. The governor is intending to pay a visit to an expensive courtesan and I am supposed to accompany him as a curiosity. He promised his mistress to bring along a genuine privateer, adventurer, and all-around sea dog. So I'm in for boring talk, overpriced wine, and dull nobles.";
			link.l1.go = "GoldenGirl_1";
			link.l2 = "Quite the opposite, an invitation to a pleasant social event, run by a gentlewoman. His Excellency took me by surprise by asking me to accompany him, but to be honest, I am glad to get my mind off work for a change.";
			link.l2.go = "GoldenGirl_5";
		break;
		
		case "GoldenGirl_1":
			dialog.text = "Aye...so the fearsome Captain Charles de Maure will dress up and dance like a pet monkey for their amusement? How sweet! I have a better idea. Let's make sail and get the hell out of here. If you are in the mood for a long deserved vacation, let's sail to Isla Tesoro. We are always welcome there. Sunbathing, white sand, old friends, rum punch, getting our minds off things - you name it.";
			link.l1 = "Look, all this sounds fantastic, and I'd love to... but later. I promised to governor, this thing is important for the old man and...";
			link.l1.go = "GoldenGirl_2";
		break;
		
		case "GoldenGirl_2":
			dialog.text = "And what? You think your noble blood means a damn to them? I may not be of French blood, but I know all about their 'high society' and for them, Charles de Maure is not a captain that men follow and trust with their lives. He's not an gentleman like them. Real gentlemen don't go to sea and fight in a fog of gunpowder smoke. Charles de Maure is just a curious addition to their meal. Like a pet leopard or a house negro playing dress-up! A fancy toy! Since when do you submit to such treatment?!";
			link.l1 = "Helen, please calm yourself. I am sure I can handle a few uncomfortable glances for the governor's satisfaction and our future prosperity. It's good to have powerful friends. After all, this will be easier than leading a boarding party! And these 'good-for-nothings' are not always like that. Even high society has worthy people... at least it is supposed to.";
			link.l1.go = "GoldenGirl_3";
		break;
		
		case "GoldenGirl_3":
			dialog.text = "Whatever. (flicks her hair) But be ye warned - no way I am squeezing myself into a fancy dress. If you make me go, I'm wearing my breeches. I don't give a damn if all the gentlewomen in the Caribbean faint in disapproval.";
			link.l1 = "I wasn't going to make you. No point for both of us to suffer. I will get through this party and then we will sail to Isla Tesoro. As a treat, I've been saving a crate of excellent Spanish madeira in the cargo hold...";
			link.l1.go = "GoldenGirl_4";
		break;
		
		case "GoldenGirl_4":
			dialog.text = "Oh ho ho, Charles! Are you saying that I am no good for such esteemed company? That a girl in breeches would ruin your night? How interesting. Fine then, but don't forget to dress yourself like a fop. Monkeys in fancy dresses can touch even a courtesan's heart. Happy performance!";
			link.l1 = "Helen, wait! Goddammit...women!";
			link.l1.go = "GoldenGirl_8";
		break;
		
		case "GoldenGirl_5":
			dialog.text = "Yeah, we earned some rest alright. But damn me if I am squeezing myself in a fancy dress for this. How far gossips about your woman dressed like a man and a sailor will travel do you think?";
			link.l1 = "Ah...I don't think that's a great idea. How should I put this...this isn't an event that men are bringing their wives or respectable ladies to...";
			link.l1.go = "GoldenGirl_6";
		break;
		
		case "GoldenGirl_6":
			dialog.text = "Ha! Whores and depravity! Just wonderful - so you're going to an orgy! So why didn't you just fucking say so? You're lucky that I am not some jealous bint and won't shoot you right where you stand. At least not right now.";
			link.l1 = "Helen please, all I'm doing is accompanying our governor, he asked me to and he was very persistent about it. There will be no fucking courtesans\nWait, that came out wrong...I mean there will be fucking of courtesans... oh Goddamnit! I am just paying my respects!";
			link.l1.go = "GoldenGirl_7";
		break;
		
		case "GoldenGirl_7":
			dialog.text = "I suggest you dress yourself fashionably to 'pay your respects,' Captain de Maure. It's high society and all. It's a pure scandal showing up there without a collar and cuffs. Even for an orgy. Have fun.";
			link.l1 = "Helen, wait! Goddammit...women!";
			link.l1.go = "GoldenGirl_9";
		break;
		
		case "GoldenGirl_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlExit", 15.0);
			pchar.questTemp.GoldenGirl.Angry1 = "true";
		break;
		
		case "GoldenGirl_9":
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlExit", 15.0);
			pchar.questTemp.GoldenGirl.Angry2 = "true";
		break;
		
		case "GoldenGirl_10":
			dialog.text = "Cuffs and a collar, Captain. And perhaps lace. I heard it's back in fashion again. But what do I know!";
			link.l1 = "Oh Helen, come on!";
			link.l1.go = "GoldenGirl_11";
		break;
		
		case "GoldenGirl_11":
			DialogExit();
			NextDiag.CurrentNode = "GoldenGirl_10";
		break;
		
		case "GoldenGirl_12":
			dialog.text = "Look at this! My dear captain, back home from his orgy!";
			link.l1 = "...";
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angry1")) link.l1.go = "GoldenGirl_13";
			else link.l1.go = "GoldenGirl_18";
		break;
		
		case "GoldenGirl_13":
			dialog.text = "Do the local gentry still approve of their new monkey? Why, they say that its performance last night was legendary! Gambling over ships and whores, challenging high born princelings to duels? Would you kindly explain what the hell is going on with you?";
			link.l1 = "Helen, let me explain! It's not that simple. Damn it, I'm sorry, but I never thought I'd have to stay the night at Madame Botot's place. I only slept there, yes alone I swear! And yes, I won a frigate in a card game. Imagine that?";
			link.l1.go = "GoldenGirl_14";
		break;
		
		case "GoldenGirl_14":
			dialog.text = "Well then! You are either a great liar, a saint, or a fool. We will discuss the whores and ships you won later - now tell me everything about the duel and why everyone is gossiping that you had challenged a crown prince?";
			link.l1 = "Not a crown prince, only a count's bastard. He's the son of a very influential nobleman, Count de Levi Vantadur. Look, I didn't start it! He challenged me in the first place, and now I must win the duel without hurting him too much to avoid his father's wrath.";
			link.l1.go = "GoldenGirl_15";
		break;
		
		case "GoldenGirl_15":
			dialog.text = "Oh, 'only a count's son' huh? Are you serious right now Charles?! And how are we supposed to do this? What if he cheats? He'll kill you!";
			link.l1 = "This is why Excellency has provided me with noble seconds. I will take only them with me - if things go belly up, at least I can prove that all went according to the duel codex and the law. I am asking you to watch over the frigate while I am gone.";
			link.l1.go = "GoldenGirl_16";
		break;
		
		case "GoldenGirl_16":
			dialog.text = "Let's make sure that I got this straight... You were gone for a whole day and a night and won a whore and a frigate in a card game. And now, you are about to fight a noble whoreson who you are not allowed to kill, while *I* just sit here and wait? How am I supposed to feel about all this?!";
			link.l1 = "Helen, listen, you have every right to be mad at me and I am very sorry, but it is just...";
			link.l1.go = "GoldenGirl_17";
		break;
		
		case "GoldenGirl_17":
			dialog.text = "You know what, I've had enough of this. Just go and do your thing! I'll just dust your cabin and do your dirty laundry! Don't even think you're in the clear. We will talk about this when this is over. I'll take care of your new frigate, great Captain de Maure, don't you worry. Oh, and Captain de Maure, try not to die... for I'm planning on killing you myself afterwards. Now excuse me, I'm going to lock myself in my quarters and drink a bottle of that nice madeira I found in your cabin.";
			link.l1 = "Helen, just let me explain! Fuck... Here we go again!";
			link.l1.go = "GoldenGirl_23";
		break;
		
		case "GoldenGirl_18":
			dialog.text = "I've heard the latest Parisian fashion demands that gentlemen win ships and courtesans in card games rather than buying them! Moreover, if one want to make a good impression of himself, he has to challenge their previous owners to a duel. What the fuck have you gotten yourself into this time?!";
			link.l1 = "Helen, it's not that simple. Damn it, I am sorry, but I never thought I'd have stay the night at Madame Botot's place! Last night turned into an exhausting and brutal battle of wits. And yes, I won a damn frigate in cards. Imagine that?";
			link.l1.go = "GoldenGirl_19";
		break;
		
		case "GoldenGirl_19":
			dialog.text = "Lovely. Meaning that you won a courtesan too? And the frigate you won what did you stake against it? Not our ship, you couldn't have...";
			link.l1 = "I had to. Look it doesn't matter now, in the end I won. My opponent challenged me to a duel and accused me of cheating. He is a bastard of an extremely influential nobleman, Count de Levi Vantadur. Which means that I will have to do my best not to kill him or hurt him too badly.";
			link.l1.go = "GoldenGirl_20";
		break;
		
		case "GoldenGirl_20":
			dialog.text = "Will he do the same? Have you lost your mind, Charles? To risk your ship, to risk your life, because of some other woman?! Is she really worth it? Do I mean nothing to you?!";
			link.l1 = "Helen, there is no reason to be jealous, I swear. It just happened. I had to do it and the governor provided me with noble officers as my seconds in order to make sure everything happens by the rules. I can't take you nor any of our men with me. Please take care of the frigate while I am gone.";
			link.l1.go = "GoldenGirl_21";
		break;
		
		case "GoldenGirl_21":
			dialog.text = "Just great! First, you go to an orgy with strange women and show back up the next morning and I even didn't clip you for that. Now, you tell me that nearly lost our ship in a card game but won a courtesan! And now you about to fight for her 'honor' against some highborn whoreson who you are not even allowed to kill! How am I supposed to feel about all this? Tell me.";
			link.l1 = "Helen, listen, you have every right to be mad at me, but let me just explain...";
			link.l1.go = "GoldenGirl_22";
		break;
		
		case "GoldenGirl_22":
			dialog.text = "You know what, I had enough of this. Go off and fight your damn duel. I'll take care of your new frigate, great Captain de Maure, don't you worry. Now excuse me, I'm going to lock myself in my quarters and drink a bottle of that nice madeira I found in your cabin. But if something happens to you, I swear to God that I will rain hellfire upon this town and I will bury this brothel and your beloved Excellency's palace!";
			link.l1 = "Helen, it'll be alright, trust me... Wait, where are you going?! Fuck! Here we go again...";
			link.l1.go = "GoldenGirl_23";
		break;
		
		case "GoldenGirl_23":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlToFregat", 15.0);
		break;
		
		case "GoldenGirl_24":
			dialog.text = "Charles, you have some explaining to do. Would you kindly tell me what the hell happened? I didn't set a proper watch and the boys were drinking...some scoundrels assaulted our ship and tied us up while we were sleeping. Then the filthy scum started asking me how far you would go to rescue me. In the end, they locked me in the hold. I lost count of the days I've been waiting!";
			link.l1 = "That bastard wanted to repay me for the shame I brought on him. I was afraid he'd do something to you! Thank God you are alright!";
			link.l1.go = "GoldenGirl_25";
		break;
		
		case "GoldenGirl_25":
			dialog.text = "I take it you had to do something to get me back? Something bad, right?";
			link.l1 = "All that matters is you are back with me. I failed you, Helen. I am so sorry! I hope you can find it in your heart to forgive me!";
			link.l1.go = "GoldenGirl_26";
		break;
		
		case "GoldenGirl_26":
			dialog.text = "Already did. I've had a lot of time to think about what I said...I am sorry too, Charles. If only I didn't take your dealings with that marquis too personally. I would have set a proper watch that night, I would have been on guard. Ah! I'm just a useless woman!";
			link.l1 = "Stop saying that, the past is the past. I love you and I will never leave you again. I promise!";
			link.l1.go = "GoldenGirl_27";
		break;
		
		case "GoldenGirl_27":
			dialog.text = "I guess, I'd better not know what exactly you did, right? Fine, we are together again and that's the main thing.";
			link.l1 = "I have no secrets from you. I will tell you...";
			link.l1.go = "GoldenGirl_28";
		break;
		
		case "GoldenGirl_28":
			DialogExit();
			SetLaunchFrameFormParam("Some time has passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			npchar.dialog.currentnode = "GoldenGirl_28_1";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "GoldenGirl_28_1":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "What a mess... I know you had no choice, but how to explain this to Di Lu Parkes and his friends? I mean, you're a criminal now!";
				link.l1 = "I chose to pay that price, but I really had no choice. Don't you worry, I'll find a way to fix it and to restore our good name. If not, then we will always be welcome at Isla Tesoro! I can manage if you are with me.";
			}
			else
			{
				dialog.text = "What a story Charles... I believe you had no choice in the matter, but what comes next? Will that Englishman make things right or is it war? You sure you don't want to come to Basse-Terre to witness them chaining that bastard?";
				link.l1 = "You know Helen, two weeks ago I would never miss it. But today I say to hell with him! I don't even care anymore about his just punishment. We are together again, that is all that matters!";
			}
			link.l1.go = "GoldenGirl_29";
		break;
		
		case "GoldenGirl_29":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "You know that I will always be with you. Ha! It's not like it the first time you and I ended up neck deep in the bilges. We'll make it again.";
				link.l1 = "True. Let's set sail, dear! The horizon awaits us!";
			}
			else
			{
				dialog.text = "I like your thinking, Charles! No more nobles: French, British, Spaniards - whatever. I think we've earned a vacation!";
				link.l1 = "Agreed. Just you and me! No more governors and highborn bastards!";
			}
			link.l1.go = "GoldenGirl_30";
		break;
		
		case "GoldenGirl_30":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "Aye, aye, Captain!";
				link.l1 = "";
			}
			else
			{
				dialog.text = "Sounds lovely! I will go to tell the boys it's time to weigh anchor! And Charles...";
				link.l1 = "I know Helen, I know. I will join you in a moment.";
			}
			link.l1.go = "GoldenGirl_31";
		break;
		
		case "GoldenGirl_31":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "GoldenGirl_GirlGoOnBoard", 10.0);
		break;
		
		case "GoldenGirl_32":
			dialog.text = "Charles, you've made it! The Portuguese told me everything! What a story!";
			link.l1 = "Thank god, you're alive, Helen! You have no idea how glad I am too see you again!";
			link.l1.go = "GoldenGirl_33";
		break;
		
		case "GoldenGirl_33":
			dialog.text = "Speaking of which. You promised to tell me something, remember? Something big and complicated. This is your chance, Captain. What the hell happened?!";
			link.l1 = "I love you, Helen. The rest is irrelevant.";
			link.l1.go = "GoldenGirl_34";
		break;
		
		case "GoldenGirl_34":
			dialog.text = "Aye, that was helpful, but... Damn, me too, Charles. I love you too. My God, I've missed you so much!";
			link.l1 = "Me too. Come with me, I won't leave you tonight even if the sky starts falling on this miserable town. I will never leave you again. Ever.";
			link.l1.go = "GoldenGirl_35";
		break;
		
		case "GoldenGirl_35":
			dialog.text = "I guess, I'd better not know what exactly you did, right? Aye, we are together again and that's the main thing.";
			link.l1 = "I have no secrets from you. I will tell you...";
			link.l1.go = "GoldenGirl_36";
		break;
		
		case "GoldenGirl_36":
			DialogExit();
			SetLaunchFrameFormParam("Some time has passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			npchar.dialog.currentnode = "GoldenGirl_36_1";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "GoldenGirl_36_1":
			dialog.text = "Unbelievable! Did you just say that France and England are at the brink of war with each other because of me?";
			link.l1 = "No, Helen. It's because I made a very bad mistake in judgement. But I had to bring you back and fix everything.";
			link.l1.go = "GoldenGirl_37";
		break;
		
		case "GoldenGirl_37":
			dialog.text = "That is all very touching and romantic, I am even ready to forget about how it all had started in the first place. Almost ready. But seriously, they arrested you because the Portuguese gave a wrong name of the damned brigantine?";
			link.l1 = "Quite the contrary, he gave me the right one! I wish I knew how he managed to pull this off and why. By the way, where is the man himself?!";
			link.l1.go = "GoldenGirl_38";
		break;
		
		case "GoldenGirl_38":
			dialog.text = "He's gone. Right after he brought me here. I didn't want to use the 'hospitality' from the courtesan you won, so I had Bartholomew rent a room for me. He paid for it and disappeared without saying a word. Actually wait, no, he did leave a letter for you though!";
			link.l1 = "A letter? From Bartholomew the Portuguese? This is new. I don't like where this is going...";
			link.l1.go = "GoldenGirl_39";
		break;
		
		case "GoldenGirl_39":
			dialog.text = "Right, I will leave you to read it here while I go and say hello to the boys. They must be worried. I never thought I would ever miss those gloomy hangdog faces! In the meantime try not to get yourself into another disaster!";
			link.l1 = "Damn it... I still can't believe I've brought you back!";
			link.l1.go = "GoldenGirl_40";
		break;
		
		case "GoldenGirl_40":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_SPGirlReturn", 10.0);
		break;
		
		// Jason Долго и счастливо
		case "LongHappy":
			RemoveItems(pchar, "potionwine", 2);
			dialog.text = "White sand, clear green water, you, me, and good wine - Charles, this is so romantic! We should often have a walk like this together, alright!";
			link.l1 = "Glad you like it. I think we should make more time for this now.";
			link.l1.go = "LongHappy_1";
		break;
		
		case "LongHappy_1":
			dialog.text = "Charles, what are you up to and why are you on your knees? This is so sudden...";
			link.l1 = "Helen, I love you. And I want to live with you every day that is alloted to me from above. Therefore, here and now, in face of this sea and sky, I ask you - Helen Beatrice Sharp -  to give me the honor to stand with me before man and God until death do us part. I, Charles de Maure, Chevalier de Monper, ask you - will you marry me?";
			link.l1.go = "LongHappy_2";
		break;
		
		case "LongHappy_2":
			if (pchar.location == "Shore_ship1")
			{
				dialog.text = "You know, I never liked these formalities, but I'm with you till the end of the world. And as for your question, the answer is... oh, sorry, I spilled!";
				link.l1 = "Nevermind, this is just wine and I never loved this shirt...";
				link.l1.go = "LongHappy_3";
			}
			else
			{
				dialog.text = "Charles, of course yes! Yes, yes, and yes again!!! But I do hope you're not planning on retiring us to some dusty family castle to grow turnips until the end of our days?";
				link.l1 = "Well, we do have a family castle, but it's not dusty and we won't stay there. Our life is freedom and the horizon at our fingertips!";
				link.l1.go = "LongHappy_4";
			}
		break;
		
		case "LongHappy_3":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			DoQuestCheckDelay("Helena_LoveSex", 1.0);
			npchar.dialog.currentnode = "LongHappy_5";
			LAi_SetStayType(npchar);
		break;
		
		case "LongHappy_4":
			dialog.text = "Then a toast to you, my captain, my husband, and to our wedding!";
			link.l1 = "To you, my love! And to our future together, there's so much in store for us!";
			link.l1.go = "LongHappy_6";
		break;
		
		case "LongHappy_5":
			dialog.text = "Then a toast to you, my captain, my husband, and to my wedding!";
			link.l1 = "To you, my love! And to our future together, there's so much in store for us!";
			link.l1.go = "LongHappy_6";
		break;
		
		case "LongHappy_6":
			DialogExit();
			chrDisableReloadToLocation = false;
			npchar.dialog.currentnode = "Helena_officer";
			LongHappy_MarryToSenPierre();
		break;
		
		case "LongHappy_7":
			dialog.text = "So, Abbot Benoit has returned and is ready to marry us. But just so you know, I won't wear a dress even for such an occasion! Do you think me wearing breeches will cause a stir?";
			link.l1 = "Helen, I love you in any outfit, and they'll get over it. First I wanted to consult with you about the guests and the ceremony.";
			link.l1.go = "LongHappy_8";
		break;
		
		case "LongHappy_8":
			dialog.text = "Aye, there's one problem - most of our best friends with whom we would gladly share this day won't be allowed to enter the city, let alone the church. Therefore - let's get married here with all the important people, as expected, and then we'll sail to Isla Tessoro and have a proper celebratation with our real friends, what do you think?";
			link.l1 = "Sounds good to me! I'll talk to Abbot Benoit, but we need to send out invitations and more...";
			link.l1.go = "LongHappy_9";
		break;
		
		case "LongHappy_9":
			dialog.text = "Calm down, captain. Your darling future wife will pick up part of the burden! I will arrange everything on Isla Tesoro and write to our friends, just tell me: how big of a wedding do you want?";
			link.l1 = "Just you, me and our closest friends. After all the official foppery here in Martinique we will want some sincere intimacy.";
			link.l1.go = "LongHappy_10";
			link.l2 = "Everyone must remember this day! Call everybody! No one will be left out!";
			link.l2.go = "LongHappy_11";
		break;
		
		case "LongHappy_10":
			pchar.questTemp.LongHappy.SmallMarry = "true";
			dialog.text = "Cozy and friendly - you read my mind! We will have to visit Sharptown and I will prepare everything. I think fifty barrels of rum and two dozen barrels of wine will be enough. Also, for food and entertainment we will need three hundred thousand pieces of eight.";
			link.l1 = "Remind me - why don't you manage the ship finances again? I'll get it all. Just a quick visit to the abbot and then we set sail for Sharptown.";
			link.l1.go = "LongHappy_12";
		break;
		
		case "LongHappy_11":
			pchar.questTemp.LongHappy.BigMarry = "true";
			dialog.text = "So, you want to have a party like real sea wolves? Alright! We will have to visit Sharptown and I will prepare everything. We'll have to seriously stock up - I think a hundred barrels of rum and fifty barrels of wine will be enough. And other expenses will take at least five hundred thousand pieces of eight.";
			link.l1 = "Are you inviting the entirity of the Brethren of the Coast? Oh hell, let's do it! I will get the supplies. Just a quick visit to the abbot and we set sail for Sharptown.";
			link.l1.go = "LongHappy_12";
		break;
		
		case "LongHappy_12":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "10");
			AddQuestUserData("LongHappy", "sName", "Helen");
			LongHappy_MarryGoToBenua();
		break;
		
		case "LongHappy_13":
			dialog.text = "Charles, I'll take care of the loading then I'll hand out the invitations to the baron and come to terms with the barkeep. Shouldn't take too long.";
			link.l1 = "Don't worry my dear, I'll occupy myself with gainful employment... Or just have a nap on the sand. I didn't think that it would be easier to storm Tortuga than to plan my own wedding, for God's sake.";
			link.l1.go = "LongHappy_14";
		break;
		
		case "LongHappy_14":
			DialogExit();
			SetLaunchFrameFormParam("Several hours have passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 4, 0);
			LongHappy_IslaTesoroRemoveGoods();
			npchar.dialog.currentnode = "LongHappy_15";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "LongHappy_15":
			dialog.text = "Did you get some rest, Charles? Have some good news and bad news. Bad news is that the locals had so much fun last week that they accidentally burned the damn 'Old Woodpecker' tavern down! Here's the good news, the baron promised that it would be rebuilt bigger and better than it was by the time we get back. I've made arrangements, so we can set sail.";
			link.l1 = "I hope our wedding won't leave a similar pile of ashes in town when we leave. That's a damn shame, I quite liked the 'Old Woodpecker'- cozy, intimate, with just a faint whiff of vomit and oakum! Oh well darling, you're right - we should get going.";
			link.l1.go = "LongHappy_16";
		break;
		
		case "LongHappy_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "12");
			pchar.questTemp.LongHappy = "marry_wait";
			pchar.questTemp.LongHappy.DrinkReady = "true";
		break;
		
		case "LongHappy_17":
			dialog.text = "Jan is already in town with Gladys, can you imagine? I didn't think that they would ever attend my wedding! Oh Sweet Jesus! Even when we were in that horrible Indian temple city, I was not as scared as I am now!";
			link.l1 = "All is well, darling, all is well. I'm worried too - nerves are normal. Since the guests have already come, I should go to Father Benoit and find out when the service will begin.";
			link.l1.go = "LongHappy_18";
		break;
		
		case "LongHappy_18":
			dialog.text = "It's going to be a damn long and difficult day... I'm going to see Jan and Gladys.";
			link.l1 = "I'm glad they were able to come. Old Man Svensson loves you like his own daughter, and Mrs. McArthur even more. It's good that they're here today. Go and don't worry - everything will be fine.";
			link.l1.go = "LongHappy_19";
		break;
		
		case "LongHappy_19":
			DialogExit();
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0);
			AddQuestRecord("LongHappy", "14");
			AddQuestUserData("LongHappy", "sName", "Helen");
		break;
		
		case "LongHappy_20":
			dialog.text = "Yes.";
			link.l1 = "";
			link.l1.go = "LongHappy_21";
		break;
		
		case "LongHappy_21":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_27";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_22":
			dialog.text = "Yes.";
			link.l1 = "";
			link.l1.go = "LongHappy_23";
		break;
		
		case "LongHappy_23":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_29";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_24":
			dialog.text = "Yes.";
			link.l1 = "";
			link.l1.go = "LongHappy_25";
		break;
		
		case "LongHappy_25":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_31";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_26":
			dialog.text = "";
			link.l1 = "I, Charles Henry de Maure, chevalier de Monper, take you, Helen Beatrice Sharp, to be my wife, to have and to hold, from this day forward, for better and for worse, for richer and for poorer, in sickness and in health, until death do us apart. According to God's Holy Law, in the presence of God, I make this vow.";
			link.l1.go = "LongHappy_27";
		break;
		
		case "LongHappy_27":
			dialog.text = "I, Helen Beatrice Sharp, take you, Charles Henry de Maure, to be my husband, to have and to hold, from this day forward, for better and for worse, for richer and for poorer, in sickness and in health, until death do us apart. According to God's Holy Law, in the presence of God, I make this vow.";
			link.l1 = "";
			link.l1.go = "LongHappy_28";
		break;
		
		case "LongHappy_28":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_33";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_29":
			dialog.text = "Amen.";
			link.l1 = "";
			link.l1.go = "LongHappy_30";
		break;
		
		case "LongHappy_30":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_35";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_31":
			dialog.text = "Helen Beatrice de Maure, Madame de Monper - oh I like the sound of it, my dearest husband!";
			link.l1 = "Haven't heard anything better, my wife!";
			link.l1.go = "LongHappy_32";
		break;
		
		case "LongHappy_32":
			dialog.text = "You know - I thought, that this would not change anything, and probably it didn't - I loved you before and wanted to live with you the rest of the days, but this day, this holy service... I am truly happy, Charles! Happy as never before, and look at Gladys and Jan - they are shining! There are so many happy faces around! By the way - it's time for you to walk around the guests and accept their congratulations. Come back when you finish, don't forget - we are awaited in Sharptown.";
			link.l1 = "I'll do it right away, sweetheart. One kiss before I go!";
			link.l1.go = "LongHappy_33";
		break;
		
		case "LongHappy_33":
			DialogExit();
			LongHappy_MarryKiss();
		break;
		
		case "LongHappy_34":
			dialog.text = "Hello husband, have you already talked to the guests?";
			link.l1 = "Not yet, be patient, wife, I'll back soon.";
			link.l1.go = "LongHappy_34_1";
			link.l2 = "Yes, I've never listened to so many congratulations at once. And you know what - I think most of them spoke sincerely!";
			link.l2.go = "LongHappy_35";
		break;
		
		case "LongHappy_34_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_34";
		break;
		
		case "LongHappy_35":
			dialog.text = "Yes, these noblemen are surprisingly sincere - to admit, I expected more falsehood and hypocrisy. Or I'm just so happy that I don't notice anything. But after all, our friends are waiting for us in Sharptown! When do we sail?";
			link.l1 = "Right now. We'll fly on eagles' wings straight to a friendly feast. I hope my wife, you don't mind spending this night in our cabin?";
			link.l1.go = "LongHappy_36";
		break;
		
		case "LongHappy_36":
			dialog.text = "Oh yes, my husband, you are so romantic! And don't twitch like that, now I have the right to kiss you in public... Aye, we can go now!";
			link.l1 = "Navigator, set course for Sharptown and don't disturb us for any reason! I don't care if a ghost fleet is bearing down on us!";
			link.l1.go = "LongHappy_37";
		break;
		
		case "LongHappy_37":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_38";
			LongHappy_MarryComplete();
		break;
		
		case "LongHappy_38":
			dialog.text = "Oh my dear husband, I'm so happy! Today is a wonderful day...";
			link.l1 = "";
			link.l1.go = "LongHappy_38_1";
		break;
		
		case "LongHappy_38_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_38";
		break;
		
		case "LongHappy_39":
			dialog.text = "Come on Charles. This liar will be dead before he hits the ground!";
			link.l1 = "";
			link.l1.go = "LongHappy_40";
		break;
		
		case "LongHappy_40":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angerran") && CharacterIsAlive("Angerran")) // fix 02-04-20
			{
				sld = characterFromId("Angerran");
				sld.dialog.currentnode = "Shivo_6";
			}
			else 
			{
				sld = characterFromId("LH_Dussak");
				sld.dialog.currentnode = "Dussak_5";
			}
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "LongHappy_41":
			dialog.text = "I'm fine, Charles, it's alright. How is Nathan?";
			link.l1 = "So much blood... Dannie, is he breathing? I see him breathing!";
			link.l1.go = "LongHappy_42";
		break;
		
		case "LongHappy_42":
			DialogExit();
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_9";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "LongHappy_43":
			dialog.text = "Faster, dear, do not waste time!";
			link.l1 = "";
			link.l1.go = "LongHappy_43_1";
		break;
		
		case "LongHappy_43_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_43";
		break;
		
		case "LongHappy_44":
			dialog.text = "Charles, are you alright? Such a bloodbath! Sorry, we were stuck upstairs, there were a dozen of these bastards so I had to deal with them first!";
			link.l1 = "It's fine, I handled it. I'm glad I was able to finish that story with Jacques... finally. He got what he deserved.";
			link.l1.go = "LongHappy_45";
		break;
		
		case "LongHappy_45":
			dialog.text = "Fine, my dear, let's finish here and get back. I can't stop thinking about Nathan, how is he? He shielded me from that bullet!";
			link.l1 = "You're right, sweetie, I worry too. Go on, I'm right behind you.";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner")) link.l1.go = "LongHappy_46";
			else link.l1.go = "LongHappy_48";
		break;
		
		case "LongHappy_46":
			dialog.text = "We found Marcus! He was in the cargo hold, bound and unconscious.";
			link.l1 = "He's alive?";
			link.l1.go = "LongHappy_47";
		break;
		
		case "LongHappy_47":
			dialog.text = "Don't worry, love, Baron Tyrex will live even longer than us. He's just woken up and is already buzzing, he keeps calling for rum, his saber, and the bridge - in that order.";
			link.l1 = "That's our old Marcus! Let hem rest a bit while we finish here and then go back to the shore.";
			link.l1.go = "LongHappy_48";
		break;
		
		case "LongHappy_48":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LongHappy_BarbExit", -1);
		break;
		
		case "LongHappy_49":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") && CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "I'm so sorry, darling... First our faithful friend Tichingitu, now Gino... Barbazon should have been killed a dozen times for all he'd done!";
				link.l1 = "Alas I did it just once. I feel bad too... But we won, and he won't hurt anyone ever again.";
				link.l1.go = "LongHappy_50";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
				{
					dialog.text = "I feel so awful about Gino, Charles! When I found out, I didn't believe it! How are you, love?";
					link.l1 = "I can't believe it either... what a way to go... I didn't imagine this day would turn out like this.";
				}
				else
				{
					dialog.text = "I wonder, will future historians write about the great battle of Privateer Bay? The day when barons of the Brethren of the Coast met in open battle - I bet the Spanish Costa Garda are wiping away tears of gratitude! But, we won again! Our friends are alive, and our enemies are dead - a glorious wedding gift!";
					link.l1 = "Yeah, such a celebration, but we made it, my angel. We made it.";
				}
				link.l1.go = "LongHappy_50";
			}
		break;
		
		case "LongHappy_50":
			dialog.text = "Come on, Dannie found us a house here on the outskirts of town, I don't want to return to the ship now until it's been cleaned up. We'll sit and drink to those who didn't make it.";
			link.l1 = "Yes, Helen, let's go.";
			link.l1.go = "LongHappy_51";
		break;
		
		case "LongHappy_51":
			DialogExit();
			LongHappy_LogBook();
			DoQuestCheckDelay("LongHappy_MarryFinalizing", 0.5);
		break;
		
		case "LongHappy_52":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "I feel so bad about Gino, Charles! When I found out, I didn't believe it! How are you?";
				link.l1 = "I can't believe it either...what a way to go... I didn't imagine this day would turn out like this.";
			}
			else
			{
				dialog.text = "Have you seen Hawk? Dannie let me out when Gino said 'the danger is over'. I'm glad that everything is alright. Our friends are alive, and our enemies are dead - a glorious wedding gift!";
				link.l1 = "Me too, darling. And we won. Barbazon is dead, the barons are gathering what's left of their crews. The fight is over.";
			}
			link.l1.go = "LongHappy_53";
		break;
		
		case "LongHappy_53":
			dialog.text = "Charles, I see you are barely standing, but I visited the tavern and you won't believe what I heard from the bartender.";
			link.l1 = "Aye, I heard it from Jan, he's been there too. It seems to me that our dear Indian has gone on a warpath. Let's take a walk to Sabo-Matila Cove, a few people saw him leaving in that direction.";
			link.l1.go = "LongHappy_54";
		break;
		
		case "LongHappy_54":
			DialogExit();
			LongHappy_LogBook();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.longhappy_shoregirl.win_condition.l1 = "location";
			pchar.quest.longhappy_shoregirl.win_condition.l1.location = "Shore_ship1";
			pchar.quest.longhappy_shoregirl.function = "LongHappy_SetShoreGirl";
		break;
		
		case "LongHappy_55":
			dialog.text = "God above! That's the spirit, Tichingitu! Phew, I'm laughing my ass off here! Why don't we Europeans adopt such a custom too?! Oh Charles, you're nearly asleep on your feet! Come on, Dannie found for us a house here on the outskirts - you need to have some rest.";
			link.l1 = "Lead on ... I think I've fallen asleep on that beach before.";
			link.l1.go = "LongHappy_56";
		break;
		
		case "LongHappy_56":
			DialogExit();
			DoQuestCheckDelay("LongHappy_MarryFinalizing", 0.5);
		break;
		
		case "tonzag_jailed":
			dialog.text = "... It's ok.";
			link.l1 = "Good to hear.";
			link.l1.go = "exit";
			link.l2 = "Really?";
			link.l2.go = "tonzag_jailed_1";
			locCameraFromToPos(-15.50, 2.28, -1.23, true, -27.00, -10.60, -22.70);
		break;
		
		case "tonzag_jailed_1":
			dialog.text = "Yes.";
			link.l1 = "Good to hear.";
			link.l1.go = "exit";
			link.l2 = "Come on, I can see something is bothering you!";
			link.l2.go = "tonzag_jailed_2";
		break;
		
		case "tonzag_jailed_2":
			dialog.text = "I'm totally fine, let it go!\nCharles, go to hell! I hate dungeons, I hate you, and I hate this damned island! Get me out of here immediately!\nSorry... I really don't like dungeons, don't touch me!";
			link.l1 = "Sorry. We all fear something.";
			link.l1.go = "exit";
		break;
		
		case "tonzag_aftershot":
			dialog.text = "AAAA! Let us out of here! Charles, do something!";
			link.l1 = "Pull yourself together!";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Helena_officer";
			AddDialogExitQuestFunction("Tonzag_TichingituAfterShot");
		break;
		
		case "tonzag_after_boarding":
			dialog.text = "My Captain, the enemy breached the hull on the second deck and landed a boarding party. Battles are raging throughout the ship, and most of the gun crews are knocked out! We need to rescue our crew and Hercule! Will you go, or should I?";
			link.l1 = "This time, I'll go myself, Helen! Take command of the ship and get us out of here!";
			link.l1.go = "tonzag_after_boarding_1";
			DelLandQuestMark(npchar);
		break;
		
		case "tonzag_after_boarding_1":
			dialog.text = "Aye aye, my Captain. I won't let you down, and you please be careful!";
			link.l1 = "I know, Helen. And you be careful too!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_GoToGunDeck");
		break;
		
		case "tonzag_after_victory":
			dialog.text = "Victory, my Captain! The landing party has been eliminated, the enemy chose to retreat and headed south. The ship's condition is acceptable. Alive crew: " + GetCrewQuantity(pchar) + " people. Report completed!";
			link.l1 = "Thank you, Helen, and what...";
			link.l1.go = "tonzag_after_victory_1";
		break;
		
		case "tonzag_after_victory_1":
			dialog.text = "Undress, victor, your prize is to do whatever you please with me!";
			link.l1 = "Uh...";
			link.l1.go = "tonzag_after_victory_2";
			link.l2 = "Let's go!";
			link.l2.go = "tonzag_after_victory_2";
		break;
		
		case "tonzag_after_victory_2":
			dialog.text = "Oh, hi, Hercule. Sorry, you're caught us at an inopportune moment! But damn, I'm glad to see you alive and covered in someone else's blood - a natural state for you, huh!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HelenBoardingDialog");
		break;
		
		case "tonzag_after_victory_3":
			dialog.text = "";
			link.l1 = "Well, Helen, you're something!";
			link.l1.go = "tonzag_after_victory_4";
		break;
		
		case "tonzag_after_victory_4":
			dialog.text = "I haven't even started yet, my Captain. Shall we celebrate?";
			link.l1 = "I need no convincing!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ShowFrame");
		break;
		
		case "tonzag_dead":
			dialog.text = "Don't look, don't look, don't look... This is some other world, my Captain! It can't be like this!";
			link.l1 = "I think this is our world now, darling. And you're right, let's not hang about...";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Helena_officer";
		break;
		
		// Jason Исла Мона
		case "IslaMona":
			dialog.text = "I'm afraid this pandemic is taking its toll on your girls, Rodrigo. Keep them busy with knitting or something!";
			link.l1 = "This conversation is clearly going nowhere. We agreed that we will go to church tomorrow. To pray... of course.";
			link.l1.go = "IslaMona_1";
		break;
		
		case "IslaMona_1":
			DialogExit();
			LAi_SetOfficerType(npchar);
			npchar.dialog.currentnode = "Helena_officer";
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_26";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_2":
			dialog.text = "I'm proud of you, my love!";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
		break;
		
		case "IslaMona_3":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			sld = characterFromId("Himenes_companion_1");
			sld.dialog.currentnode = "island_man_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_4":
			dialog.text = "Well, Charles...";
			link.l1 = "What's on your mind again, Helen?";
			link.l1.go = "IslaMona_5";
		break;
		
		case "IslaMona_5":
			dialog.text = "The fact that the most scandalous couple in the Caribbean owns two entire islands! My pirate haven of Isla Tesora and your promised land - how long do you think they can last when civilization finally comes to the West Indies?";
			link.l1 = "Long enough to last us our lifetime, darling. And after? We can't control what happens then. Others will tell our story. The most important thing is that you and I are here and now, together and happy.";
			link.l1.go = "IslaMona_6";
		break;
		
		case "IslaMona_6":
			dialog.text = "Speaking of happiness... I'm about to go upstairs now: I need to light the candles, make the bed, maybe write in my diary...";
			link.l1 = "I'll stay here a little longer, and then I'll be up to help you 'make the bed.'";
			link.l1.go = "IslaMona_7";
		break;
		
		case "IslaMona_7":
			dialog.text = "Don't take too long...";
			link.l1 = "";
			link.l1.go = "IslaMona_8";
		break;
		
		case "IslaMona_8":
			DialogExit();
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			DoQuestFunctionDelay("IslaMona_ChurchReloadToRoom", 0.5);
			ChangeCharacterAddressGroup(npchar, "IslaMona_TwoFloorRoom", "goto", "goto4");
			DoQuestCheckDelay("Helena_LoveSex", 2.5);
			NextDiag.CurrentNode = "sex_after";
			pchar.questTemp.IslaMona.Doorlock = "true";
		break;
		
		case "drinking_refuse":
			dialog.text = "Are you really that busy? Too bad, but I understand. I'll find something else to busy myself with.";
			link.l1 = "";
			link.l1.go = "exit";
			NextDiag.TempNode = "Helena_wait";
			
			pchar.questTemp.HelenDrinking.Result = "no_visit";
			CloseQuestHeader("HelenDrinking");
		break;
		
		case "drinking_accept":
			dialog.text = "It's nice that you remember. I wanted to tell you that I'm very grateful. Not every day someone saves you from... you know what. Let's go have a drink. My treat.";
			link.l1 = "Helen... What will Gladys say?";
			link.l1.go = "drinking_accept_1";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToHouse");
		break;
		
		case "drinking_accept_1":
			dialog.text = "Very funny, Charles. Come on, and don't annoy me.";
			link.l1 = "Is this a date?";
			link.l1.go = "drinking_accept_1_1";
			link.l2 = "Coming, no need to get cranky.";
			link.l2.go = "drinking_accept_1_2";
		break;
		
		case "drinking_accept_1_1":
			dialog.text = "Ha-ha! You wish! I'd need to get completely drunk!";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "drinking_accept_1_2":
			dialog.text = "That's better.";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "drinking_in_tavern":
			dialog.text = "";
			link.l1 = "... she had many virtues, but she couldn't hold her alcohol. That's how we met.";
			link.l1.go = "drinking_in_tavern_1";
			link.l2 = "... my father insisted on military service. I yielded and went to Paris with a letter of recommendation. But I never made it to the designated address and became an artist.";
			link.l2.go = "drinking_in_tavern_2";
		break;
				
		case "drinking_in_tavern_1":
			dialog.text = "Ah, now I understand what virtues you're talking about. What was her name?";
			link.l1 = "Lulu.";
			link.l1.go = "drinking_in_tavern_1_1";
		break;
		
		case "drinking_in_tavern_1_1":
			dialog.text = "Lulu... With these stories, you've completely ruined Paris for me. I thought it was a city of grand life, but it just sounds like some big fancy brothel.";
			link.l1 = "Do you condemn brothels?";
			link.l1.go = "drinking_in_tavern_1_2";
		break;
		
		case "drinking_in_tavern_1_2":
			dialog.text = "Yes, Captain, and I don't understand men who visit them.";
			link.l1 = "(stare into the mug)";
			link.l1.go = "drinking_in_tavern_1_4";
			link.l2 = "(have a terrible cough)";
			link.l2.go = "drinking_in_tavern_1_4";
			link.l3 = "Uh... to each his own... I guess?";
			link.l3.go = "drinking_in_tavern_1_4";
		break;
		
		case "drinking_in_tavern_1_4":
			dialog.text = "(laughs) Ha! You should have seen your face! Scared? Let's raise another one! To Paris!";
			link.l1 = "To Paris!";
			link.l1.go = "drinking_in_tavern_3";
		break;
		
		case "drinking_in_tavern_2":
			dialog.text = "(laughs) Y-you?! An artist? So, the beauty and pride of the English fleet, a rapist and just a son of a bitch Donovan, died at the hands of a Parisian artist? Ah, too bad you didn't wear your pristine jabot for the boarding and didn't beat that scum with a cane!";
			link.l1 = "Yeah, very unfortunate. The jabot just happened to be in the wash that day.";
			link.l1.go = "drinking_in_tavern_2_1";
		break;
		
		case "drinking_in_tavern_2_1":
			dialog.text = "(laughs) Well, thanks, Charles. I don't know how the rest of tonight will go, but the evening has already been great. I might even allow you to paint my portrait. But, mind you, not in the same style you painted your Parisian girls!";
			link.l1 = "Ha! That is if I agree to paint you.";
			link.l1.go = "drinking_in_tavern_3";
		break;
		
		case "drinking_in_tavern_3":
			dialog.text = "Excuse me, my Captain, listening about your adventures and the life of noble... courtesans of both sexes. Shark bite me, I'll never believe that you couldn't find something more worthwhile to do with your time! Don't even dare to tell me that all you did was smear canvases and squander daddy's money. You wouldn't have survived a day with us if that were true.";
			link.l1 = "I had... other pursuits.";
			link.l1.go = "drinking_in_tavern_" + pchar.HeroParam.HeroType;
		break;
		
		case "drinking_in_tavern_herotype_3":
			dialog.text = "";
			link.l1 = "I combined the life at court with the military service, but not... hehe, not quite the way my father wanted, of course. A couple of escapes through the window and one brawl - and I became friends with the guardsmen. And naturally I picked up a lot of things, toughened up my body. Older comrades taught me to take a hit, wear armor, handle a sword, and relax properly. The last part especially suited me, of course. You won't believe it, but not everyone can swing a sword from morning till noon and then drink from noon till the next morning.";
			link.l1.go = "drinking_in_tavern_4";
		break;
		
		case "drinking_in_tavern_herotype_1":
			dialog.text = "";
			link.l1 = "Think it was easy in the capital for a nobleman with a poor reputation and an empty purse, losing daddy's recommendation letter on the first day? I had to assert myself and not let anyone mock me. Lessons in fencing at home were not forgotten, and I responded to any sideways glance with a duel. Then I really got into it. Still, I didn't kill anyone, and I managed to leave Paris before running into an experienced fighter who would have finished me off.";
			link.l1.go = "drinking_in_tavern_4";
		break;
		
		case "drinking_in_tavern_herotype_4":
			dialog.text = "";
			link.l1 = "Spent a lot of time at cemeteries. Don't think anything bad - it was just a popular hobby in my social circle. For courage, we would go to a cemetery at night, put empty bottles on the fence, and shoot at them on a timer. Overnight, we would waste a hundred bullets and a crate of champagne. Now of course, I'm ashamed of such behavior, but then the winner took a solid jackpot and got some... favors from the female side of the court. Everything was used - I even dabbled a bit with gunpowder mixtures. But why none of us thought to learn how to make paper cartridges - I'll never know.";
			link.l1.go = "drinking_in_tavern_4";
		break;
		
		case "drinking_in_tavern_herotype_2":
			dialog.text = "";
			link.l1 = "Studied, and quite diligently - was even close to getting into the Sorbonne. Worked at an office until it got boring, and in general - did a bit of everything. The teacher, an old friend of my father, preferred the practice to theory, so I got to see Paris from all sides and talk to different people: from bandits to nobles. All of that ended up coming in handy here.";
			link.l1.go = "drinking_in_tavern_4";
		break;
		
		case "drinking_in_tavern_4":
			dialog.text = "And... that's it? So there's still something in you, my captain. Something you haven't seen in yourself yet. To you!";
			link.l1 = "Good toast!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_TavernChange");
		break;
		
		case "drinking_my_background":
			dialog.text = "";
			link.l1 = "Tell me your story, Helen. My adventures in the Capital pale in comparison to a girl under thirty commanding a schooner with a hundred men on board.";
			link.l1.go = "drinking_my_background_1";
		break;
		
		case "drinking_my_background_1":
			dialog.text = "Just under thirty, huh, Charles? For such a strong comment, you'll have to pay for the next round! All my guys are dead, and I don't command a schooner anymore. Frankly, I don't know if I will command one ever again.";
			link.l1 = "I'm sorry, Helen. Didn't mean to touch a nerve. But why do you think your captain career is over?";
			link.l1.go = "drinking_my_background_2";
		break;
		
		case "drinking_my_background_2":
			dialog.text = "Because my crew is dead, and a different one won't ever accept me. Eh! Fine, my captain, you've told me a lot about your life; now it's my turn! The truth is not at the bottom of this mug, so let's dispense with the mystery.";
			link.l1 = "";
			link.l1.go = "drinking_my_background_3";
		break;
		
		case "drinking_my_background_3":
			dialog.text = "My case, Charles, is unique. My father was one of the best sailors in these parts, highly regarded by the Forest Devil, his crew worshipped him, and he loved me more than the life itself.";
			link.l1 = "";
			link.l1.go = "drinking_my_background_4";
		break;
		
		case "drinking_my_background_4":
			dialog.text = "Take away even one of these things, and he would have either sent me to London to live in... civilization, or left me to wither here like my mother. Everything worked out great at first: I wanted freedom, real freedom, Charles, and a skillful command of a warship with a loyal crew gives you exactly that. And my father gave me all he could. I went out at sea with him at the age of twelve, spent the first six months chasing rats in the hold, and only then was allowed to work with the sailors.";
			link.l1 = "Sean MacArthur made you a ship rat? Sorry, Helen, but there's no coming back from that! How did the crew accept you?";
			link.l1.go = "drinking_my_background_5";
		break;
		
		case "drinking_my_background_5":
			dialog.text = "Well, perhaps I'm exaggerating a bit for the sake of a good story? My father's crew accepted me; he gathered fine people. But since then, I've been afraid... of holds and any small dark spaces in general. Ha! Svensson almost killed my father when he found out!";
			link.l1 = "He is important to you. He clearly played a role in your fate, no less than Sean.";
			link.l1.go = "drinking_my_background_6";
		break;
		
		case "drinking_my_background_6":
			dialog.text = "Yeah. All the barons directly told my father he was a fool, but it was the Forest Devil who gave him his approval and shook his hand after I beat the crew's record climbing the mast. That moment will stay with me forever: the triumphant shouts of the crew and, everywhere I looked, the clean sea horizon. And my father's approving look, I couldn't see it, but I felt it with all my heart.";
			link.l1 = "My triumph ended with me falling from the rigging on the first day on the way to Guadeloupe.";
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.TakeFolke")) {
				link.l1 = link.l1 + " My helmsman, Deluc, had a very telling look too."
			}
			link.l1.go = "drinking_my_background_7";
		break;
		
		case "drinking_my_background_7":
			dialog.text = "Ah-ha-ha! I can imagine! Don't worry, that was a long time ago; now you're a real sea wolf!";
			link.l1 = "";
			link.l1.go = "drinking_my_background_8";
		break;
		
		case "drinking_my_background_8":
			dialog.text = "To our triumphs!";
			link.l1 = "Hear hear!";
			link.l1.go = "drinking_my_background_12";
		break;
		
		case "drinking_my_background_12":
			dialog.text = "... And then I gradually rose through the ranks, served at the captain's table in councils with my father and officers. Learned a lot. From the age of fifteen, they started taking me on military campaigns, and I killed a man in my very first battle. It was a disgusting campaign; we shouldn't have set sail on a Monday... Really shouldn't have!";
			link.l1 = "At fifteen? You're scaring me, Helen.";
			link.l1.go = "drinking_my_background_13";
		break;
		
		case "drinking_my_background_12":
			dialog.text = "I didn't even understand what happened. The Dutch merchant had his vanguard - mercenaries of the Company. They decided to play it boldly and counterattacked our poop deck. And I, a fool, without any fear for my life, stuck my blond head out. I immediately got hit with the butt of a pistol. But a moment before that I managed to stick my rapier into some fool from the Company.";
			link.l1 = "Good Lord, what about Sean? How didn't he kick you ashore after that?";
			link.l1.go = "drinking_my_background_13";
		break;
		
		case "drinking_my_background_13":
			dialog.text = "My father didn't come out of that battle unscathed either, and the sight of my cracked dumb head certainly didn't help. He slowly started to decline, and probably no one noticed except me. And then he was gone. According to his will, I inherited the Rainbow with her crew and enough funds to keep the ship afloat for a year.";
			link.l1 = "And did the crew accept you as captain?";
			link.l1.go = "drinking_my_background_14";
		break;
		
		case "drinking_my_background_14":
			dialog.text = "We don't live in a fairy tale, my captain. Some met my father's will with hostility - things took an unpleasant turn\nIf at least one sailor had left the Rainbow, refusing to serve under my command, it would have been very bad for my image. But Svensson intervened and straightened everyone out. No one left the crew openly... back then. For seven years, I commanded my beauty, transported dubious goods for the Forest Devil, searched for treasures, lived... But now, that's all in the past.";
			link.l1 = "Not in the past. I believe you are destined to sail under your own flag again! Let's drink to that!";
			link.l1.go = "drinking_my_background_sea";
			link.l2 = "We may not recover the ship, but your rapier is still with you.";
			link.l2.go = "drinking_my_background_land";
		break;
		
		case "drinking_my_background_sea":
			dialog.text = "You know, when you say it like that, I believe it too. Let's drink!";
			link.l1 = "";
			link.l1.go = "drinking_my_background_15";
			
			AddCharacterSkill(npchar, SKILL_COMMERCE, 5);
			AddCharacterSkill(npchar, SKILL_ACCURACY, 5);
			AddCharacterSkill(npchar, SKILL_CANNONS, 5);
			AddCharacterSkill(npchar, SKILL_SAILING, 5);
			AddCharacterSkill(npchar, SKILL_REPAIR, 5);
			AddCharacterSkill(npchar, SKILL_GRAPPLING, 5);
			AddCharacterSkill(npchar, SKILL_DEFENCE, 5);
			notification("Naval Skills +", "Helena");
			
			pchar.questTemp.HelenDrinking.Background = "sea";
		break;
		
		case "drinking_my_background_land":
			dialog.text = "But will my rapier bring me happiness? The answer is probably somewhere at the bottom of this mug. Let's drink!";
			link.l1 = "";
			link.l1.go = "drinking_my_background_15";
			
			AddCharacterSkill(npchar, SKILL_F_LIGHT, 5);
			AddCharacterSkill(npchar, SKILL_FENCING, 5);
			AddCharacterSkill(npchar, SKILL_F_HEAVY, 5);
			AddCharacterSkill(npchar, SKILL_PISTOL, 5);
			AddCharacterSkill(npchar, SKILL_FORTUNE, 5);
			AddCharacterSkill(npchar, SKILL_LEADERSHIP, 5);
			AddCharacterSkill(npchar, SKILL_SNEAK, 5);
			notification("Personal Skills +", "Helena");
			
			pchar.questTemp.HelenDrinking.Background = "land";
		break;
		
		case "drinking_my_background_15":
			dialog.text = "I've been thinking about your life in Europe... Look, you're a city dandy, and I'm just a regular girl, but we've already made names for ourselves in the most dangerous corner of the world.";
			link.l1 = "Sounds like a toast! So, is there something that unites us?";
			link.l1.go = "drinking_my_background_16";
		break;
		
		case "drinking_my_background_16":
			dialog.text = "Well, I stand on my father's shoulders. I don't know about you, but perhaps your family has also had no less influence on you? Maybe you haven't realized it yet?";
			link.l1 = "I'll ask my dear brother once I pull him out of prison.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_TavernEmpty");
		break;
		
		case "drinking_game":
			dialog.text = "Well, that's it, my captain. We've exchanged stories, time to call it a night.";
			link.l1 = "Hmm, I was hoping for a different ending to the evening.";
			link.l1.go = "drinking_game_1";
		break;
		
		case "drinking_game_1":
			dialog.text = "The night is not over yet. I suggest a game: if you play your cards right, perhaps your prayers will be answered.";
			link.l1 = "We're going to play cards? I'm in!";
			link.l1.go = "drinking_game_2";
		break;
		
		case "drinking_game_2":
			dialog.text = "Easy there, sea wolf. I won't play strip poker with you.";
			link.l1 = "Yeah, you're right, Helen. We don't have privacy here.";
			link.l1.go = "drinking_game_3";
		break;
		
		case "drinking_game_3":
			dialog.text = "That's not the only thing we don't have, Charles... It's not a card game, but don't worry, I bet you're a master at it. 'I Never' - heard of it?";
			link.l1 = "Familiar. From the past life. And do you often play it?";
			link.l1.go = "drinking_game_4";
		break;
		
		case "drinking_game_4":
			dialog.text = "Always wanted to try, but had no one to play with.";
			link.l1 = "That's a pretty bold game for our first shared drink. Are you sure?";
			link.l1.go = "drinking_game_5";
			link.l2 = "By the way, where is everyone? Are we alone here?";
			link.l2.go = "drinking_game_6";
		break;
		
		case "drinking_game_5":
			dialog.text = "Yes, after recent events, I need to live a little. Do something foolish, you know?";
			link.l1 = "No, it always ends badly, Rumba.";
			link.l1.go = "drinking_game_refuse";
			link.l2 = "Let's start! Ladies first!";
			link.l2.go = "drinking_game_accept";
		break;
		
		case "drinking_game_6":
			dialog.text = "Sent them all home - no need to let outsiders overhear.";
			link.l1 = "No, it always ends badly, Rumba.";
			link.l1.go = "drinking_game_refuse";
			link.l2 = "Let's do this! Ladies first!";
			link.l2.go = "drinking_game_accept";
		break;
		
		case "drinking_game_refuse":
			dialog.text = "Too bad, but maybe you're right. Another drink then?";
			link.l1 = "Let's start! Ladies first!";
			link.l1.go = "drinking_game_refuse_1";
		break;
		
		case "drinking_game_refuse_1":
			dialog.text = "I've arranged it - the room upstairs is yours. It was occupied by some important French officer, but the Forest Devil's boys politely asked him to vacate the place. Go get some shot eye - I won't let you wonder the street, or worse yet, go out in the sea, in this condition.";
			link.l1 = "Yes, ma'am!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToTavernRoom");
		break;
		
		case "drinking_game_accept":
			dialog.text = "Ha! Hic! Means, you're starting!";
			link.l1 = "Careful, darling! Hmm. I've never chased rats in the hold!";
			link.l1.go = "drinking_game_accept_1";
		break;
		
		case "drinking_game_accept_1":
			dialog.text = "So that's how it is? Gotta be on guard with you! (Drinks)";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_2";
		break;
		
		case "drinking_game_accept_2":
			dialog.text = "Brr! Just the memory of that... Well, brace yourself, handsome: I've never fallen from the yards!";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_3";
		break;
		
		case "drinking_game_accept_3":
			dialog.text = "";
			link.l1 = "Nice one! Allow me, mademoiselle, to drink to you! (Drinks)";
			link.l1.go = "drinking_game_accept_4";
		break;
		
		case "drinking_game_accept_4":
			dialog.text = "";
			link.l1 = "I've never been superstitious.";
			link.l1.go = "drinking_game_accept_5";
			
			LAi_Fade("", "");
			pchar.GenQuest.CamShuttle = 1;
			SetCamShuttle(loadedLocation);
			SetPitch(0.95);
		break;
		
		case "drinking_game_accept_5":
			dialog.text = "And you call yourself a sailor! You know very well what kind of people we are. Never know what the voyage will bring, don't know when and where you'll see land, if at all. You have to seek answers beyond maps and navigation tools! To your health! (Drinks)";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_6";
		break;
		
		case "drinking_game_accept_6":
			dialog.text = "And the girls you painted in person... Did they like the result?";
			link.l1 = "They didn't always like the paintings, but, um... the result - always.";
			link.l1.go = "drinking_game_accept_7";
		break;
		
		case "drinking_game_accept_7":
			dialog.text = "Charles! If we had met back then, I would have shot you or taken you hostage for ransom. And by the way, I have never taken up brushes.";
			link.l1 = "Hey! Well, that's completely banal. Dear Helen, if I start listing things you've never taken up...";
			link.l1.go = "drinking_game_accept_8";
		break;
		
		case "drinking_game_accept_8":
			dialog.text = "Fine, alright, I'll play fair. Your move, my captain.";
			link.l1 = "(Sips) Hic!. Hmm...I never had my models hit me on the head with a pistol grip.";
			link.l1.go = "drinking_game_accept_9";
		break;
		
		case "drinking_game_accept_9":
			dialog.text = "(Sips) Ugh. We're playing this game wrong, dear. I thought we'd be drinking and getting to know each other, but instead we're exchanging barbs and... and... Hic. Damn!";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_10";
			
			LAi_Fade("", "");
			pchar.GenQuest.CamShuttle = 2;
			SetCamShuttle(loadedLocation);
			SetPitch(0.90);
		break;
		
		case "drinking_game_accept_10":
			dialog.text = "Let's make it more interesting! And preferably something not from what we were talking about an hour ago!";
			link.l1 = "I've never woken up in an unfamiliar place after a drinking spree.";
			link.l1.go = "drinking_game_accept_11";
		break;
		
		case "drinking_game_accept_10":
			dialog.text = "Ouch! Damn it, Charles! (Drinks)";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_11";
		break;
		
		case "drinking_game_accept_11":
			dialog.text = "I... Hic... can't believe it. I confess, guilty - the little Rumba used to hit the bottom. But I've never been in prison!";
			link.l1 = "How did you...?";
			link.l1.go = "drinking_game_accept_12";
		break;
		
		case "drinking_game_accept_12":
			dialog.text = "Hahaha! Drink, drink!";
			link.l1 = "I'll regret this. (Drinks)";
			
			if (IsCharacterEquippedArtefact(pchar, "totem_01")) {
				link.l1.go = "drinking_game_accept_13";
			} else {
				link.l1.go = "exit";
				AddDialogExitQuestFunction("HelenDrinking_LightsOut");
			}
		break;
		
		case "drinking_game_accept_13":
			dialog.text = "Come on, my dear. The last question and the last chance to outplay me!";
			link.l1 = "No... I... Let's get some fresh air.";
			link.l1.go = "drinking_game_enough";
			link.l2 = "I've often drunk, but never like this... I've never gotten s-so drunk with a girl. Swear on my w-word, d-drinking is truly a g-great sin...";
			link.l2.go = "drinking_game_accept_14";
			
			LAi_Fade("", "");
			pchar.GenQuest.CamShuttle = 3;
			SetCamShuttle(loadedLocation);
			SetPitch(0.85);
		break;
		
		case "drinking_game_enough":
			dialog.text = "Eh!";
			link.l1 = "";
			link.l1.go = "drinking_game_refuse_1";
		break;
		
		case "drinking_game_accept_14":
			dialog.text = "";
			link.l1 = "W-wait... You're not drinking?";
			link.l1.go = "drinking_game_accept_15";
		break;
		
		case "drinking_game_accept_15":
			dialog.text = "Ah-ha-ha! That's hilarious! You have a high aim, my captain. Let it be... hic!... known to you...";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_16";
		break;
		
		case "drinking_game_accept_16":
			dialog.text = "ЧThat I have the misfortune of living in an all-male crew, and I have to behave carefully. I am an honest girl.";
			link.l1 = "I'm h-happy for you, H-Helen.";
			link.l1.go = "drinking_game_accept_17";
		break;
		
		case "drinking_game_accept_17":
			dialog.text = "You'll be even happier, because I won! But, to be honest, I've never gotten so drunk with a guy either.";
			link.l1 = "(Silently takes a drink) T-to you. Congratulations... h-hic...";
			link.l1.go = "drinking_game_accept_18";
		break;
		
		case "drinking_game_accept_18":
			dialog.text = "Hey-hey-hey! Captain, where are you going? Offended, perhaps?";
			link.l1 = "I n-need... a break? Just going to find my s-sword...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_ExitTavern");
		break;
		
		case "drinking_at_svenson":
			dialog.text = "Cap, are you ready? There's no turning back, and if anything goes wrong, I'll make you marry me.";
			link.l1 = "Phew! Let me at least catch some fresh air! Are you sure about this, Helen?";
			link.l1.go = "drinking_at_svenson_1";
		break;
		
		case "drinking_at_svenson_1":
			dialog.text = "Yes, damn it, and don't stand there like a pole! I need to lose myself, even if it's just for one night!";
			link.l1 = "I'm afraid after this night, I'll be the one wanting to lose myself. Let's go before we wake up the whole town.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_EnterSvenson");
		break;
		
		case "drinking_give_key":
			dialog.text = "Cap, take the key and go upstairs. There should be a chest; you probably saw it when Svensson had it. Grab the barrel and head back immediately.";
			link.l1 = "Hold on, dear, why do I have to rob your boss?";
			link.l1.go = "drinking_give_key_1";
			
			GiveItem2Character(pchar, "key3");
			PlaySound("interface\important_item.wav");
		break;
		
		case "drinking_give_key_1":
			dialog.text = "Don't be silly. I've been here since childhood; if the owners return, I can handle it and cover for you. Come on, don't lower your sail now!";
			link.l1 = "Sharp as a knife, a true smuggler! Hang on, I'll be quick.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GotKey");
		break;
		
		case "drinking_got_whiskey":
			dialog.text = "Got it?";
			link.l1 = "You bet! Not the first chest I've emptied, and certainly not the last!";
			link.l1.go = "drinking_got_whiskey_1";
		break;
		
		case "drinking_got_whiskey_1":
			dialog.text = "I'm proud of you! Haha! First-rate Irish whiskey, 'Bushmills'! They won't serve us such a drink in the tavern.";
			link.l1 = "Sounds good, but won't Svensson notice it's missing?";
			link.l1.go = "drinking_got_whiskey_2";
		break;
		
		case "drinking_got_whiskey_2":
			dialog.text = "He'll definitely notice, but he doesn't drink it himself. He seems to have saved it as a gift for his pirate mate Dodson, and Dodson either disappeared or killed someone...";
			link.l1 = "That's terrible! Such a gift absolutely must not go to waste. Grab the barrel, and let's change the scenery!";
			link.l1.go = "drinking_got_whiskey_3";
		break;
		
		case "drinking_got_whiskey_3":
			dialog.text = "Well said, Cap. One more thing through - tell me, did you take anything else from the chest? Answer honestly.";
			if (HelenDrinking_RobbedSvenson()) {
				link.l1 = "Took something, a habit, you know.";
				link.l1.go = "drinking_got_whiskey_notbelieve";
			}
			
			link.l2 = "No. Not sure if I'm a pirate, but I'm definitely not a thief.";
			link.l2.go = "drinking_got_whiskey_believe";
			
			if (HelenDrinking_RobbedSvenson()) {
				link.l2.go = "drinking_got_whiskey_notbelieve";
				pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 2;
				notification("Helen disapproves", "Helena");
				pchar.questTemp.HelenDrinking.RobbedSvenson = true;
			}
		break;
		
		case "drinking_got_whiskey_believe":
			dialog.text = "Somehow I believe you... a fool that I am!";
			link.l1 = "";
			link.l1.go = "drinking_get_out";
		break;
		
		case "drinking_got_whiskey_notbelieve":
			dialog.text = "Go and make sure you didn't take anything for some reason.";
			link.l1 = "";
			link.l1.go = "exit";
			if (!HelenDrinking_RobbedSvenson()) {
				AddDialogExitQuestFunction("HelenDrinking_JoanEnter");
				TakeItemFromCharacter(pchar, "cask_whisky");
				sld = ItemsFromID("cask_whisky");
				sld.price = sld.pricebak;
				DeleteAttribute(sld, "pricebak");
			}
			
			NextDiag.TempNode = "drinking_got_whiskey_notbelieve";
		break;
		
		case "drinking_get_out":
			DialogExit();
			
			AddDialogExitQuestFunction("HelenDrinking_JoanEnter");
			TakeItemFromCharacter(pchar, "cask_whisky");
			sld = ItemsFromID("cask_whisky");
			sld.price = sld.pricebak;
			DeleteAttribute(sld, "pricebak");
		break;
		
		case "drinking_at_fort":
			dialog.text = "Hey, hey, darling! Focus! My face, kissed by the sea breeze, is right here!";
			link.l1 = "Phew, well, your costume is something! You must have saved a lot of money on sewing material. And I... hic! I've seen a lot! But this... But this is the best thing I've seen.";
			link.l1.go = "drinking_at_fort_1";
			locCameraFromToPos(-1.65, 44.45, 76.64, true, -5.93, 42.10, 70.13);
		break;
		
		case "drinking_at_fort_1":
			dialog.text = "Everyone says that, but for some reason, I believe you! Do you really like it?";
			link.l1 = "Well, of course, it very favorably accentuates your figure, although...";
			link.l1.go = "drinking_at_fort_2";
		break;
		
		case "drinking_at_fort_2":
			dialog.text = "Oh, now you've ruined everything!";
			link.l1 = "... although I have no doubt that among the regular folk, it inspires awe!";
			link.l1.go = "drinking_at_fort_3";
		break;
		
		case "drinking_at_fort_3":
			dialog.text = "I'm rather in awe of this weird widespread habbit among the common and not-so-common folk to wear dense European clothing in such heat. That makes our villages look even more comical... I like my outfit, Charles. In it, I feel beautiful, and that's important for a woman.";
			link.l1 = "You would remain just as beautiful without that outfit, Helen.";
			link.l1.go = "drinking_at_fort_4";
		break;
		
		case "drinking_at_fort_4":
			dialog.text = "Careful, my captain! Saying such sweet things may corrupt a poor girl!";
			link.l1 = "If she's not against it, then I'm not against it.";
			link.l1.go = "drinking_at_fort_5";
		break;
		
		case "drinking_at_fort_5":
			dialog.text = "Hee-hee! Better ask me about something else. I like it when you get inquisitive.";
			link.l1 = "Then let's squeeze in a question about your costume. I don't believe that sea dogs can take a captain seriously in such attire.";
			link.l1.go = "drinking_at_fort_6";
		break;
		
		case "drinking_at_fort_6":
			dialog.text = "And I don't believe that sea dogs, in general, can see a woman as a captain, so my outfit probably didn't add to my problems. Or maybe it didn't have time to add since it's a new thing. I sewed it myself!\nAh-ha-ha! I used to wear one of those... what are they called? Our military still wears them! B-r-r... Seeing one of those now makes me feel sick.";
			link.l1 = "Uniforms?";
			link.l1.go = "drinking_at_fort_7";
		break;
		
		case "drinking_at_fort_7":
			dialog.text = "Oh, exactly, a uniform! A red uniform! Like that guy's wearing.";
			link.l1 = "";
			link.l1.go = "exit";
			
			pchar.GenQuest.BlockDialogCamera = true;
			AddDialogExitQuestFunction("HelenDrinking_OfficerAtFort");
		break;
		
		case "drinking_at_fort_7_1":
			dialog.text = "Oh, I'm sorry, Major, let me treat you to some fine Irish whiskey as an... hic!... apology.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog2");
		break;
		
		case "drinking_at_fort_7_2":
			dialog.text = "Charles won't get in trouble, will he, Major? Tell me he won't, pretty please!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog4");
		break;
		
		case "drinking_at_fort_8":
			dialog.text = "I'm so glad! Let's drink!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToVillage");
		break;
		
		case "drinking_at_miskito":
			dialog.text = "Upf. Look what I've got!";
			link.l1 = "Helen... Are you planning to use that... to lift your spirits?!.. Don't even think about it! Datura can completely overcome a person, drain their strength, crush their will! Before you know it, you're a living corpse, and then very quickly, a dead one...";
			link.l1.go = "drinking_at_miskito_1";
		break;
		
		case "drinking_at_miskito_1":
			dialog.text = "Charles, but... right now...";
			link.l1 = "No buts. I'm sorry for being harsh, but this is no joke. I'm taking this away from you. Can't believe what you were thinking... Here, drink this and snap out of it.";
			link.l1.go = "drinking_at_miskito_2";
			
			GiveItem2Character(pchar, "cannabis7");
			PlaySound("interface\important_item.wav");
		break;
		
		case "drinking_at_miskito_2":
			dialog.text = "I'm sorry, Charles. You're absolutely right, I know. A momentary weakness. It won't happen again. Thanks for saving me from the devil's temptation...";
			link.l1 = "Let's forget about it... Now, tell me, how did you manage to earn respect in the town, maintain good relations with the garrison officers, and befriend the natives?";
			link.l1.go = "drinking_at_miskito_3";
		break;
		
		case "drinking_at_miskito_3":
			dialog.text = "They respect Svensson, and some of it spills over to me. Our little town survives solely on Jan's deals. He shares a portion of the profits from his cocoa plantations with the redcoats, and the Miskito owe him their entire livelihood.";
			link.l1 = "How did that happen?";
			link.l1.go = "drinking_at_miskito_4";
		break;
		
		case "drinking_at_miskito_4":
			dialog.text = "When the Castilians were in charge, they didn't bother the Indians much. But after they kicked out the noble Hidalgos, our folks decided to take control of the local forests. Jan resolved the matter quite decisively back then - even sent people to London! Of course, not out of the goodness of his heart: extracting cocoa in a forest where every bush hates you is a hopeless venture. But now, the Indians don't only help Jan smuggle from Porto Bello to Blueweld but also cut down their own forests for a pittance. Bravo, Forest Devil, bravo!";
			link.l1 = "It sounds like you don't entirely approve of his methods.";
			link.l1.go = "drinking_at_miskito_5";
		break;
		
		case "drinking_at_miskito_5":
			dialog.text = "I love and respect the Miskito people, but I also respect Jan's strategy. We don't live in a fairy tale, my captain.";
			link.l1 = "Hm... I see your relationship with Svensson is more complicated than it seems at first glance...";
			link.l1.go = "drinking_at_miskito_6";
		break;
		
		case "drinking_at_miskito_6":
			dialog.text = "Even more than you know. His wife has a good reason to be venomous towards me... Jan has been eyeing me since I was about fifteen. It was around the time I started walking the decks of the Rainbow as an equal, and apparently, something clicked in the Forest Devil's mind back then... But I've said too much, my captain. Let's not delve into this topic; gossiping about our patron is not very decent.";
			link.l1 = "Then let's change the subject. I meant to say that you clearly fit into this company, and they consider you one of their own.";
			link.l1.go = "drinking_at_miskito_7";
		break;
		
		case "drinking_at_miskito_7":
			dialog.text = "It just so happens that it's much easier for me to be in the company of Indians, gypsies, and other decent misfits. Mom's stews, beach bonfires, and the Rainbow's gangway - I've built myself a cozy little world, Captain. Too bad it all came crushing down just when I thought I had everything figured out.";
			link.l1 = "The barrel is almost empty... One last round?";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToShipyard");
		break;
		
		case "drinking_at_perlas":
			dialog.text = "It's so good... I'm glad you agreed to spend time with me, Captain. I really needed it. I believe you did too.";
			link.l1 = "Yes, it's been a minute since I've relaxed like this. It'll be something to remember!";
			link.l1.go = "drinking_at_perlas_1";
		break;
		
		case "drinking_at_perlas_1":
			dialog.text = "You probably think devil knows what about me right now. I'm a very closed-off person by nature, Charles. I just... damn, I just wanted to feel alive! Just wanted to talk to someone!";
			link.l1 = "What about Gladys? Jan?";
			link.l1.go = "drinking_at_perlas_2";
		break;
		
		case "drinking_at_perlas_2":
			dialog.text = "All mom does is crying, and Jan seems like a different person now. Maybe I'm imagining things, I don't know, but it's like he's ashamed of me now? Forgive me, I... (sniffles).\nThat's enough, old girl. Sorry, I got a little carried away.";
			link.l1 = "No need to apologize. I understand everything, or at least I think I do.";
			link.l1.go = "drinking_at_perlas_3";
		break;
		
		case "drinking_at_perlas_3":
			dialog.text = "I'm saying all this because we've only just met, and I'm not used to being so open even with those I've known for a long time. They call me Rumba, ostensibly for my character, but as you can see, it's a misnomer. Is the booze all gone?";
			link.l1 = "A while ago, and dawn is already breaking.";
			link.l1.go = "drinking_at_perlas_4";
		break;
		
		case "drinking_at_perlas_4":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_friend") && !CheckAttribute(pchar, "questTemp.HelenDrinking.RobbedSvenson")) {
				dialog.text = "I'm sorry, my captain, if you had other expectations for our evening. I... I can't. Not today.";
			} else {
				dialog.text = "Then thank you for the evening, Captain. Who knows, maybe we'll do it again.";
			}
			link.l1 = "Of course, Helen.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_PoormanTalk");
		break;
		
		case "ambush":
			dialog.text = "Thanks for bringing me here, Captain. Let's have a look around, shall we? Examine my inheritance.";
			link.l1 = "Haven't you been here before?";
			link.l1.go = "ambush_1";
		break;
		
		case "ambush_1":
			dialog.text = "No, it's quite a ways away; besides, I'm no pirate. This place has never been particularly fascinating, and after they killed Blaise... It's better not to linger here.";
			link.l1 = "We won't. I already regret bringing you here.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPrepareAmbush");
		break;
		
		case "after_ambush":
			switch (pchar.questTemp.HelenDrinking.IslaTesoroAmbush) {
				case "A":
					if (!CheckAttribute(pchar, "questTemp.HelenDrinking.IslaTesoroAmbush.TriedB") && !CheckAttribute(pchar, "questTemp.HelenDrinking.IslaTesoroAmbush.TriedC")) {
						dialog.text = "Did you have to, Captain? Why so quick to fight? Well, one should not just a winner, I guess. Come on, let's take a look at the residence; there's nothing else worth seeing here anyway.";
						pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 1;
						notification("Helen disapproves", "Helena");
					} else {
						dialog.text = "Kudos, my Captain, for trying to resolve the issue wisely before getting into a fight. Come on, let's take a look at the residence; there's nothing else worth seeing here anyway.";
					}
					
					link.l1 = "What about that huge ship pulled ashore?";
					link.l1.go = "after_ambush_1";
				break;
				
				case "B":
					dialog.text = "You skillfully fooled those fools, my Captain! I almost burst out laughing, honest! Come on, let's take a look at the residence; there's nothing else worth seeing here anyway.";
					pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
					notification("Helen approves", "Helena");
					
					link.l1 = "What about that huge ship pulled ashore?";
					link.l1.go = "after_ambush_1";
				break;
				
				case "C":
					dialog.text = "Hold on, let a girl catch her breath! Are you really the one Charlie Prince?";
					pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
					notification("Helen approves", "Helena");
					
					link.l1 = "There was such a period in my biography, yes. Are you impressed?";
					link.l1.go = "after_ambush_c";
				break;
			}
		break;
		
		case "after_ambush_1":
			dialog.text = "Yes, you're right. I'd love to explore it, but to be honest, Charles, I'm kind of afraid of it. Let's go.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroGoToResidence");
		break;
		
		case "after_ambush_c":
			dialog.text = "Oh my God, yes! Be sure to tell me everything later, alright? Because I've only heard stories... very indecent stories!";
			link.l1 = "I'll tell you everything... almost everything.";
			link.l1.go = "after_ambush_c_1";
		break;
		
		case "after_ambush_c_1":
			dialog.text = "I'll be waiting eagerly! Come on, let's take a look at the residence; there's nothing else worth seeing here anyway.";
			link.l1 = "What about that huge ship pulled ashore?";
			link.l1.go = "after_ambush_1";
		break;
		
		case "ambush_inresidence":
			dialog.text = "A cramped, cold hovel with absurd demands. I already feel like I'm in a trap!";
			link.l1 = "I see that so far you are not pleased with the potential property?";
			link.l1.go = "ambush_inresidence_1";
		break;
		
		case "ambush_inresidence_1":
			dialog.text = "No, Charles. Perhaps I am too fussy, but for now, it epitomizes everything I fear and hate. I hope I'll be able to rent it out... Although, I'm not sure where I'll to spend the money.";
			link.l1 = "Don't underestimate the value of rent. I don't have rent, and often I have to come up with ways to pay my crew. You'll buy yourself a new ship, 'Rainbow II' - sounds good, don't you think?!";
			link.l1.go = "ambush_inresidence_sea";
			link.l2 = "There are many ways to spend money on yourself. Start with a personalized sword and a bottle of excellent wine. Treat yourself, Helen, you deserve it.";
			link.l2.go = "ambush_inresidence_land";
		break;
		
		case "ambush_inresidence_sea":
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Background") && pchar.questTemp.HelenDrinking.Background == "sea") {
				dialog.text = "Thank you, my captain. I'm pleased to hear that. It's especially nice to hear it for the second time. You know me well.";
				pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 3;
				notification("Helen approves", "Helena");
			} else {
				dialog.text = "Thank you, my captain. I'm pleased to hear that.";
			}
			
			link.l1 = "";
			link.l1.go = "ambush_inresidence_2";
			
			sld = CharacterFromID("Helena");
			
			AddCharacterSkill(sld, SKILL_COMMERCE, 5);
			AddCharacterSkill(sld, SKILL_ACCURACY, 5);
			AddCharacterSkill(sld, SKILL_CANNONS, 5);
			AddCharacterSkill(sld, SKILL_SAILING, 5);
			AddCharacterSkill(sld, SKILL_REPAIR, 5);
			AddCharacterSkill(sld, SKILL_GRAPPLING, 5);
			AddCharacterSkill(sld, SKILL_DEFENCE, 5);
		break;
		
		case "ambush_inresidence_land":
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Background") && pchar.questTemp.HelenDrinking.Background == "land") {
				dialog.text = "Do you think I deserve it? I've never spent money on such trifles, but I guess there's a first time for everything. I see you won't stop trying to make me forget about the sea, huh, Captain? Maybe you're right...";
				pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 3;
				notification("Helen disapproves", "Helena");
			} else {
				dialog.text = "Do you think I deserve it? I've never spent money on such trifles, but I guess there's a first time for everything.";
			}
			link.l1 = "";
			link.l1.go = "ambush_inresidence_2";
			
			sld = CharacterFromID("Helena");
			
			AddCharacterSkill(sld, SKILL_F_LIGHT, 5);
			AddCharacterSkill(sld, SKILL_FENCING, 5);
			AddCharacterSkill(sld, SKILL_F_HEAVY, 5);
			AddCharacterSkill(sld, SKILL_PISTOL, 5);
			AddCharacterSkill(sld, SKILL_FORTUNE, 5);
			AddCharacterSkill(sld, SKILL_LEADERSHIP, 5);
			AddCharacterSkill(sld, SKILL_SNEAK, 5);
		break;
		
		case "ambush_inresidence_2":
			dialog.text = "In any case, the inspection is complete. There seem to be no valuables here - the riffraff has already managed to loot everything, and I'm sure the second floor is in the same condition.";
			link.l1 = "It's as if you've changed, Helen. When we were hanging out last time, you were... I don't know, more open?";
			link.l1.go = "ambush_inresidence_3";
		break;
		
		case "ambush_inresidence_3":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6) {
				dialog.text = "Nothing has changed, my captain, but a lot has fallen on a poor girl's shoulders, haha! I didn't mean to offend you. I just need to think a lot of things over right now. You know, such sharp turns in life don't happen every day. And we still have plenty of time together!";
				link.l1 = "Glad to hear that! Let's get out of here.";
			} else {
				dialog.text = "Much has changed, Captain. I'm afraid I have to be more mature now and look at life differently. It's not a fairy tale about a princess and inheritance; it's big politics, and I still have to realize my place in it. And my family's place too.";
				link.l1 = "I'm glad we clarified that. Let's get out of here.";
			}
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroBeforeExit");
		break;
		
		case "ambush_inresidence_wait":
			dialog.text = "Yes?";
			if (CheckCharacterItem(pchar, "pirate_cutlass")) {
				link.l1 = "Hey, not everything has been looted! Look, Helen! This saber seems to be legendary, given that even the local riffraff hesitated to pocket it.";
				link.l1.go = "ambush_inresidence_give_cutlass";
			}
			
			link.l2 = "No, nothing.";
			link.l2.go = "exit";
			
			NextDiag.TempNode = "ambush_inresidence_wait";
		break;
		
		case "ambush_inresidence_give_cutlass":
			dialog.text = "Wow, this is... the legendary cutlass of Blaise himself! Pirates respected him too much to take the saber from his home even after his death. They took the money and valuables, of course, but even the future gallows birds have remnants of honor...";
			link.l1 = "It looks like someone is clearly tidying up here. As if the owner will come back... This is not a home; it's a memorial!";
			link.l1.go = "ambush_inresidence_give_cutlass_1";
		break;
		
		case "ambush_inresidence_give_cutlass_1":
			dialog.text = "Thanks for the keen observation, Charles. You've completely ruined this place in my eyes, ha-ha!";
			link.l1 = "I think this cutlass is now yours. Blaise is your so-called uncle...";
			link.l1.go = "ambush_inresidence_give_cutlass_2";
		break;
		
		case "ambush_inresidence_give_cutlass_2":
			dialog.text = "You're adding even more horror to it, my captain. I... I can't. I'm afraid that if I accept it, my past life will come to a complete end.";
			link.l1 = "Then take it not as part of the inheritance but as a gift from a handsome man.";
			link.l1.go = "ambush_inresidence_give_cutlass_3";
		break;
		
		case "ambush_inresidence_give_cutlass_3":
			dialog.text = "Who'd that be? Just kidding! Thanks for dispelling my dark thoughts, my captain. I promise I'll train a lot to become worthy of this blade!";
			link.l1 = "You're worthy of the finest weapon, Helen. Let's go, we're done here.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GiveCutlass");
		break;
		
		case "give_cutlass":
			dialog.text = "Wow, this is... the legendary cutlass of Blaise himself! Pirates respected him too much to take the saber from his home even after his death. They took the money and valuables, of course, but even the future gallows birds have remnants of honor\nI... I can't. I'm afraid that if I accept it, my past life will come to a complete end.";
			link.l1 = "Then take it not as part of the inheritance but as a gift from a handsome man.";
			link.l1.go = "give_cutlass_1";
		break;
		
		case "give_cutlass_1":
			dialog.text = "Who'd that be? Just kidding! Thanks for dispelling my dark thoughts, my captain.";
			link.l1 = "You're worthy of the finest weapon, Helen. I'm glad you like it.";
			link.l1.go = "give_cutlass_2";
		break;
		
		case "give_cutlass_2":
			dialog.text = "I promise I'll train a lot to become worthy of this blade!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GiveCutlass");
		break;
		
		case "arrive":
			dialog.text = "My captain! Charlie!";
			link.l1 = "Charlie? That's new! Glad to see you, dear.";
			link.l1.go = "arrive_1";
		break;

		case "arrive_1":
			dialog.text = "I accidentally slipped up, ha! Glad to see you too...";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JungleDialog1");
		break;

		case "arrive_2":
			dialog.text = "So much for the sisterly solidarity! My captain, I... I was really worried and missed you so much!";
			link.l1 = "So what did you have to run home for?";
			link.l1.go = "arrive_3";
		break;

		case "arrive_3":
			dialog.text = "To... Oh, right! I have a little gift for you, here!";
			link.l1 = "Three amulets... Helen, why? Did you want to follow me?";
			link.l1.go = "arrive_4";
			
			GiveItem2Character(pchar, pchar.questTemp.Saga.BaronReturn.Indian);
			GiveItem2Character(pchar, pchar.questTemp.Saga.BaronReturn.Amulet);
			GiveItem2Character(pchar, pchar.questTemp.Saga.BaronReturn.Obereg);
		break;

		case "arrive_4":
			dialog.text = "Come here, you fool!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FirstKiss");
		break;

		case "after_kiss":
			dialog.text = "Just don't you dare spoil this moment - I've imagined it my whole life!";
			link.l1 = "I won't, Helen.";
			link.l1.go = "after_kiss_a";
			link.l2 = "You've been waiting your whole life to meet me? Flattered!";
			link.l2.go = "after_kiss_b";
			if (GetCharacterIndex("Mary") >= 0 && CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive") {
				link.l3 = "Helen, there's something... On Justice Island, I met a woman, and...";
				link.l3.go = "after_kiss_c";
			}
			locCameraFromToPos(-19.00, 1.56, 19.07, true, -11.19, -0.90, 17.49);
		break;
		
		case "after_kiss_a":
			dialog.text = "Damn right! You'll tell me everything, everything! I'll be waiting for you on the ship, my captain!";
			link.l1 = "Wait!...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterKiss1");
		break;
		
		case "after_kiss_b":
			dialog.text = "Fool! Wanna offend me? All right, I'm offended! Ha-ha! I'll go to the ship for now, before Danny makes more fun of me...";
			link.l1 = "Wait!...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterKiss1");
		break;
		
		case "after_kiss_c":
			dialog.text = "Fool! I asked you not to ruin the moment! Met... well, you met - I don't see a ring on your finger yet. But don't think you'll get away with it - I'll be waiting for a detailed story when you return to the ship.";
			link.l1 = "Wait!...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterKiss1");
		break;
		
		case "loot_good":
			dialog.text = "My captain, what's the news? I can tell by your pale face that the lawyer decided to throw more problems your way instead of helping.";
			link.l1 = "You're right, Helen. Loxley demanded an impressive advance, and the case itself will cost me a tidy sum. I'm going to go shake Jan - I've had enough! It's like the Brethren decided to pass all their expenses onto me!";
			link.l1.go = "loot_good_1";
		break;
		
		case "loot_good_1":
			dialog.text = "There's no malice in it, Charles. That's just how they are - won't lift a finger unless they have to. I'm sure Jan will help you, and I won't stand idly by either.";
			link.l1 = "I know, Helen. Tell me what you have in mind.";
			link.l1.go = "loot_good_2";
		break;
		
		case "loot_good_2":
			dialog.text = "I used to work for Jan - smuggling valuable timber all over Maine. But I'm a resourceful girl, and I've set aside something for myself during all those trips.";
			link.l1 = "And Jan didn't find out? Clever!";
			link.l1.go = "loot_good_3";
		break;
		
		case "loot_good_3":
			dialog.text = "I had a good treasurer. In short, I've collected a decent amount of money, and I've hidden it not far from here. Are you going to Jan now? Then let's visit San Juan del Norte. There's a cave nearby, and we'll just need some sailors to help us, so we don't have to carry everything ourselves.";
			link.l1 = "You've already figured it all out, haven't you? Thanks, Helen, we'll definitely visit if we have the time.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_CreateLoot");
		break;
		
		case "loot_bad":
			dialog.text = "My captain, what's the news? I can tell by your pale face that the lawyer decided to throw more problems your way instead of helping.";
			link.l1 = "You're right, Helen. Loxley demanded an impressive advance, and the case itself will cost me a tidy sum. I'm going to go shake Jan - I've had enough! It's like the Brethren decided to pass all their expenses onto me!";
			link.l1.go = "loot_bad_1";
		break;
		
		case "loot_bad_1":
			dialog.text = "Did you think you were in a fairy tale? Don't worry, we're all in the same boat here, and I'll help you out. After all, I'm entitled to an inheritance, aren't I?";
			link.l1 = "That's true... Tell me, what's on your mind!";
			link.l1.go = "loot_bad_2";
		break;
		
		case "loot_bad_2":
			dialog.text = "I have something stashed away in San Juan del Norte. There's a cave nearby - we'll just need to grab some sailors so we don't have to carry everything ourselves.";
			link.l1 = "You've already figured it all out, haven't you? Thanks, Helen, we'll definitely visit if we have the time.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_CreateLoot");
		break;
		
		case "shdn":
			dialog.text = "This is it, Charles! But you'll have to go alone - I hate caves!";
			link.l1 = "Like any enclosed spaces, I know, Helen. Wait for me here.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GoForLoot");
		break;
		
		case "shdn_ambush":
			dialog.text = "We have a problem! A squad of soldiers is coming this way, and they look menacing. Be careful, Charles, it's not just ordinary coast guards - there's a French officer among them! I beg you, just don't do anything foolish!";
			link.l1 = "When have I ever done anything foolish?!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_SpawnAmbushSoldiers");
		break;
		
		case "shdn_ambush_1":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6) {
				dialog.text = "Ha, the second option sounds more enticing, but I hope you're not too proud of yourself, Charles?";
			} else {
				dialog.text = "Can't say I'm surprised, Charles...";
			}
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog1");
		break;
		
		case "shdn_ambush_2":
			dialog.text = "Are you done? Now it's my turn to speak!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_HelenKillFrancois");
		break;
		
		case "shdn_ambush_3":
			dialog.text = "My name is Helen MacArthur! Captain, you know who I am and whom I work for! Inform your people, especially this fancy idiot lying on the ground, about today's results, which I will now announce!";
			link.l1 = "";
			link.l1.go = "exit";
			CharacterTurnToLoc(npchar, "quest", "richard");
			sld = CharacterFromID("HelenDrinking_Richard");
			CharacterTurnByChr(sld, npchar);
			
			AddDialogExitQuestFunction("HelenDrinking_AfterFrancoisDeath2");
		break;
		
		case "shdn_ambush_4":
			dialog.text = "Protest? I don't care if you write to Cromwell himself. First, Monsieur de Maure did not lose his honor today.";
			link.l1 = "";
			link.l1.go = "shdn_ambush_5";
			CharacterTurnToLoc(npchar, "quest", "richard");
		break;
		
		case "shdn_ambush_5":
			dialog.text = "Second, Colonel de Tavann got shot by a girl in a very spicy outfit for calling her a prostitute.";
			link.l1 = "";
			link.l1.go = "shdn_ambush_6";
		break;
		
		case "shdn_ambush_6":
			dialog.text = "Third, you immediately withdraw your soldiers and forget about what happened unless you want the Forest Devil to know about it.";
			link.l1 = "";
			link.l1.go = "shdn_ambush_7";
		break;
		
		case "shdn_ambush_7":
			locCameraSleep(false);
			dialog.text = "No questions, I see. Have a good day, Captain.";
			link.l1 = "Good Lord, Helen, you're on fire!";
			link.l1.go = "shdn_ambush_8";
		break;
		
		case "shdn_ambush_8":
			dialog.text = "Later, Charles. Let's get out of here before they recover from the shock. I'm shaking all over too. May we talk in Blueweld?";
			link.l1 = "Agreed.";
			link.l1.go = "exit";
			CharacterTurnByChr(npchar, pchar);
			
			AddDialogExitQuestFunction("HelenDrinking_AfterFrancoisDeath3");
		break;
		
		case "duel_victory":
			dialog.text = "Let's get out of here before they recover from the shock. We still need to retrieve the ironwood, remember? We can talk in Blueweld.";
			link.l1 = "Wow! Not even a congratulations? Fine, let's go.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_DuelVictory1");
		break;
		
		case "after_cave":
			dialog.text = "Finally, home...";
			link.l1 = "What do you think about what happened?";
			link.l1.go = "after_cave_1";
		break;
		
		case "after_cave_1":
			dialog.text = "I don't understand duels. A man's pastime, usually ending with two corpses, and on a lucky day, even more. And honor... I believe honor is built on the desire to avoid conflict until the very end, as it rarely proves worthy. Ha! Just listen to me - I'm spouting some nonsense!";
			link.l1 = "That's an interesting perspective, Helen. Though not everyone would agree with it.";
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Duel")) {
				link.l1.go = "after_cave_duel";
			} else {
				link.l1.go = "after_cave_notduel";
			}
		break;
		
		case "after_cave_duel":
			dialog.text = "A pity you played into their hands. The colonel was clearly obsessed, and the rest were just after spectacle and some gossip material. Well, I won't rub it in - you've had enough today as it is.";
			link.l1 = "Yes, after duels, there's always a sense of emptiness. Enough adventures for today. What do you want to do next?";
			if (sti(pchar.questTemp.Saga.HelenRelation) == 7 || sti(pchar.questTemp.Saga.HelenRelation) == 8) {
				link.l1.go = "after_cave_mild";
			} else {
				if (sti(pchar.questTemp.Saga.HelenRelation) < 7) {
					link.l1.go = "after_cave_cold";
				} else {
					link.l1.go = "after_cave_lewd";
				}
			}
		break;
		
		case "after_cave_notduel":
			dialog.text = "Ugh! I just wanted to say that I'm proud of us. You showed real courage today, my captain. Didn't succumb to the hysteria of the crew who just wanted to command you for once. Stood firm against the pretense of the red uniform and the obsession of the blue. The colonel was clearly seeking death but got nothing more than a wound in an inappropriate place, ha-ha!";
			link.l1 = "Thanks, Helen. You brilliantly steered us away from the blow, like a true naval officer. Are you proud of yourself?";
			link.l1.go = "after_cave_notduel_1";
		break;
		
		case "after_cave_notduel_1":
			dialog.text = "Yes, I needed that. It's just a shame that it was a blue uniform, and not a red one, but at least the person wearing it got what he deserved.";
			link.l1 = "That person is indeed inconsequential, I admit. Enough adventures for today. What do you want to do next?";
			if (sti(pchar.questTemp.Saga.HelenRelation) == 7 || sti(pchar.questTemp.Saga.HelenRelation) == 8) {
				link.l1.go = "after_cave_mild";
			} else {
				if (sti(pchar.questTemp.Saga.HelenRelation) < 7) {
					link.l1.go = "after_cave_cold";
				} else {
					link.l1.go = "after_cave_lewd";
				}
			}
		break;
		
		case "after_cave_mild":
			dialog.text = "I'm heading home, my captain. Missed my mo... Gladys. Too bad she's home right now, otherwise, I would have invited you over!";
			link.l1 = "Indeed, that's a shame!";
			link.l1.go = "after_cave_mild_1";
		break;
		
		case "after_cave_mild_1":
			dialog.text = "Don't be so upset. Soon, my dear. In the meantime...";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_SecondKiss");
		break;
		
		case "after_second_kiss":
			locCameraFromToPos(4.97, 3.71, 16.06, true, 5.09, 1.25, 11.67);
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Kiss")) {
				dialog.text = "M-m-m, this one is even better than our first. Remember? By the idol?";
				link.l1 = "That's not something one forgets, dear.";
				link.l1.go = "after_second_kiss_1";
			} else {
				dialog.text = "Just don't you dare ruin this moment - I've been imagining it my whole life!";
				link.l1 = "I won't, Helen.";
				link.l1.go = "after_second_kiss_a";
				link.l2 = "You've been waiting your whole life to meet me? Flattered!";
				link.l2.go = "after_second_kiss_b";
			}
		break;
		
		case "after_second_kiss_1":
			dialog.text = "Ohh! Get a hold of yourself, girl! Until we meet again, my captain.";
			link.l1 = "Until then, Helen.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveMild");
		break;
		
		case "after_second_kiss_a":
			dialog.text = "Damn right! We'll see each other soon, my captain.";
			link.l1 = "Until we meet again, Helen. Oh God, what a girl...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveMild");
		break;
		
		case "after_second_kiss_b":
			dialog.text = "Fool! Wanna offend me? All right, I'm offended! Ha-ha! We'll see each other soon, my captain.";
			link.l1 = "Until we meet again, Helen. Oh God, what a girl...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveMild");
		break;
		
		case "after_cave_cold":
			dialog.text = "I'm heading home, Cap. I suppose the money issue with the lawyer is now sorted out? We've got tough obstacles ahead of us, so let's try to stay away from trouble from now on. The trouble will find us itself.";
			link.l1 = "Wow, really?";
			link.l1.go = "after_cave_cold_1";
		break;
		
		case "after_cave_cold_1":
			dialog.text = "Sorry for being blunt, Cap. My fate is also being decided now, you know.";
			link.l1 = "I know, I'll try to handle it as dignifiedly as possible. See you on the ship, Helen.";
			link.l1.go = "after_cave_cold_2";
		break;
		
		case "after_cave_cold_2":
			dialog.text = "Aye aye, Cap!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveCold");
		break;
		
		case "after_cave_lewd":
			dialog.text = "What's next? I'll show you.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_SecondKiss");
		break;
		
		case "after_second_kiss1":
			locCameraFromToPos(4.97, 3.71, 16.06, true, 5.09, 1.25, 11.67);
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Kiss")) {
				dialog.text = "M-m-m, this one is even better than our first. Remember? By the idol?";
				link.l1 = "That's not something one forgets, dear.";
				link.l1.go = "after_second_kiss1_1";
			} else {
				dialog.text = "Just don't you dare ruin this moment - I've been imagining it my whole life!";
				link.l1 = "I won't, Helen.";
				link.l1.go = "after_second_kiss1_a";
				link.l2 = "You've been waiting your whole life to meet me? Flattered!";
				link.l2.go = "after_second_kiss1_b";
			}
		break;
		
		case "after_second_kiss1_1":
			dialog.text = "Damn right! Wow! Gladys is not home now. Wanna come in?";
			link.l1 = "Inviting me over? And what will we be doing?";
			link.l1.go = "after_cave_lewd_accept";
			if (GetCharacterIndex("Mary") >= 0 && CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive") {
				link.l2 = "No, Helen. Another woman is waiting for me on Justice Island. I cannot do that to her.";
				link.l2.go = "after_cave_lewd_refuse_mary";
			}
			link.l3 = "Another time, my dear. I really want it, but today almost did me in. We'll catch up and compensate for the missed time tenfold.";
			link.l3.go = "after_cave_lewd_refuse_head";
		break;
		
		case "after_second_kiss1_a":
			dialog.text = "Damn right! Wow! Gladys is not home now. Wanna come in?";
			if (GetCharacterIndex("Mary") >= 0 && CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive") {
				link.l1 = "No, Helen. Another woman is waiting for me on Justice Island. I cannot do that to her.";
				link.l1.go = "after_cave_lewd_refuse_mary";
			}
			link.l2 = "Another time, my dear. I really want it, but today almost did me in. We'll catch up and compensate for the missed time tenfold.";
			link.l2.go = "after_cave_lewd_refuse_head";
			link.l3 = "Inviting me over? And what will we be doing?";
			link.l3.go = "after_cave_lewd_accept";
		break;
		
		case "after_second_kiss1_b":
			dialog.text = "Fool! Wanna offend me? All right, I'm offended! Ha-ha! You're going to have to make amends, my captain. Wow! Gladys is not home now. Wanna come in?";
			if (GetCharacterIndex("Mary") >= 0 && CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive") {
				link.l1 = "No, Helen. Another woman is waiting for me on Justice Island. I cannot do that to her.";
				link.l1.go = "after_cave_lewd_refuse_mary";
			}
			link.l2 = "Another time, my dear. I really want it, but today almost did me in. We'll catch up and compensate for the missed time tenfold.";
			link.l2.go = "after_cave_lewd_refuse_head";
			link.l3 = "Inviting me over? And what will we be doing?";
			link.l3.go = "after_cave_lewd_accept";
		break;
		
		case "after_cave_lewd_refuse_mary":
			dialog.text = "Ah, so I'm not adept enough at in the art of seduction? And she is? Who is she?";
			link.l1 = "Her name is Mary Casper, and I love her.";
			link.l1.go = "after_cave_lewd_refuse_mary_1";
		break;
		
		case "after_cave_lewd_refuse_mary_1":
			dialog.text = "That redhead in the red uniform? In the red uniform... Well, if I needed a sign, here it is. It's not meant to be. And don't worry, Captain, it won't affect my service on your ship.";
			link.l1 = "I'm sorry, Helen.";
			link.l1.go = "exit";
			
			pchar.questTemp.HelenDrinking.Mary = true;
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveRefuseMary");
		break;
		
		case "after_cave_lewd_refuse_head":
			dialog.text = "Oh, my captain! It's dangerous to leave a woman in such a state! I'm holding you to your word, and now run... I need to be alone now and try to deal with my problem... on my own! See you on the ship!";
			link.l1 = "What a girl!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveRefuseMild");
		break;
		
		case "after_cave_lewd_accept":
			dialog.text = "Don't worry, my dear, I'll guide you on if get lost.";
			link.l1 = "Well then... lead on!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveAccept");
		break;
		
		case "after_cave_bedroom":
			dialog.text = "Don't say anything, I beg you.";
			link.l1 = "...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveSex1");
		break;
		
		case "after_cave_sex":
			dialog.text = "... of course, until today, my understanding of this subject was solely based on the vulgar conversations of the 'Rainbow' crew, if you can call them conversations, of course.";
			link.l1 = "And how was it? Did reality meet your expectations?";
			link.l1.go = "after_cave_sex_1";
		break;
		
		case "after_cave_sex_1":
			dialog.text = "I enjoyed it a lot, but it feels like I haven't fully experienced it. And how...";
			link.l1 = "Let me show you! Shall we continue?";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveSex2");
		break;
		
		case "after_cave_sex_again":
			dialog.text = "Oh, now I understand! It was simply marvelous, my captain!";
			link.l1 = "You surprised me, to say the least!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveGladysEnter");
		break;
		
		case "after_cave_gladys":
			dialog.text = "Ah-ha-ha! That's a good one, for sure! Now she'll either plug her ears with wax or run to the highest platform of the fort!";
			link.l1 = "That was unexpected but very funny, ah-ha-ha!";
			link.l1.go = "after_cave_gladys_1";
			locCameraFromToPos(-0.62, 1.93, -0.39, true, -2.46, -1.20, 1.01);	// Sinistra - постельная камера
		break;
		
		case "after_cave_gladys_1":
			dialog.text = "Ready, my captain?";
			link.l1 = "Already?! No, Helen, have mercy on me, please. Gladys' sudden appearance definitely didn't help the atmosphere.";
			link.l1.go = "after_cave_gladys_2";
		break;
		
		case "after_cave_gladys_2":
			dialog.text = "Well, what can you do... Although...";
			link.l1 = "No, no, lower your sails!";
			link.l1.go = "after_cave_gladys_3";
		break;
		
		case "after_cave_gladys_3":
			dialog.text = "Alright, then let's just stay together for a bit. Our future is so murky and scary, but for the first time in a long while, I'm not afraid of anything else. I know that some new fear creep in, but not today. Not today, my captain.";
			link.l1 = "Not today, my dear. Not today.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveFin");
		break;
		
		case "give_potions":
			dialog.text = "Permission to speak, Captain?";
			link.l1 = "Yes, Helen?";
			link.l1.go = "give_potions_1";
		break;
		
		case "give_potions_1":
			dialog.text = "I know this Snake Eye - he's a good man, but a bit weird. He regularly sends people on quests for who knows what. I see that you got that dubious honor as well.";
			if (!CheckAttribute(CharacterFromID("SnakeEye"), "quest.amulet")) {
				link.l1 = "That's right, I need to bring him three amulets, or else he won't be able to help me get to Hawk's place. But you know what's funny? I already had them with me! Maybe he knew that from the very beginning?";
				link.l1.go = "give_potions_already";
			} else {
				link.l1 = "That's right, I need to bring him three amulets, or else he won't be able to help me get to Hawk's place. I can't figure out where to find them now, and time is running out.";
				link.l1.go = "give_potions_3";
			}
		break;
		
		case "give_potions_already":
			dialog.text = "Oh, what a shame! I'm glad you didn't have to run around getting those amulets from lighthouse keepers, but I was hoping that for once I could be of use to you, hoped to prove myself.";
			link.l1 = "Nonsense, Helen. You don't need to prove anything to me.";
			link.l1.go = "give_potions_4";
		break;
		
		case "give_potions_3":
			dialog.text = "I'll help you! I admit, I was hoping that for once I could be of use to you, hoped to prove myself.";
			link.l1 = "Nonsense, Helen. You don't need to prove anything to me.";
			link.l1.go = "give_potions_4";
		break;
		
		case "give_potions_4":
			dialog.text = "Nevertheless, I want to help you. Here, take the key to my room... I mean, the chest in my room! There's not much, but for you it will come in handy. And... Charles, just try not to burst laughing right now!";
			link.l1 = "Ahem, I wasn't going to. I see you're into these things?";
			link.l1.go = "give_potions_5";
		break;
		
		case "give_potions_5":
			dialog.text = "I'm a sailor, my captain, just like you. In our business, we gotta do all we can to get the Lady Luck on our side.";
			link.l1 = "Thanks, Helen. I really appreciate it.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GivePotionsKey");
		break;
		
		case "upgrade":
			dialog.text = "Darling, I have a gift for you!";
			link.l1 = "I see, there it is - standing and smiling!";
			link.l1.go = "upgrade_1";
		break;
		
		case "upgrade_1":
			dialog.text = "Ah-ha, stop it! I once delivered a decent batch of silk to the local shipwright, so now he owes me a complete overhaul of the ship. I thought of giving him 'Rainbow' for this job, but that's was not meant to be. Your vessel, on the other hand, could really benefit from such care, don't you think?";
			link.l1 = "Indeed, a splendid gift, Helen - right up your alley!";
			link.l1.go = "upgrade_2";
		break;
		
		case "upgrade_2":
			dialog.text = "I'm glad you like it. Visit him anytime and tell him that I sent you. They'll do their best job.";
			link.l1 = "Definitely!";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Helena_officer";
			AddDialogExitQuestFunction("HelenUpgradeShip1");
		break;
		
		case "give_sex":
			dialog.text = "Permission to speak, my captain?";
			link.l1 = "Of course, my dear.";
			link.l1.go = "give_sex_1";
		break;
		
		case "give_sex_1":
			dialog.text = LinkRandPhrase("Your lady misses you and demands attention. May I request to arrange a room for her and devote some time to her", "Reporting: your presence is required in a bed at the local tavern. Just five minutes of your time, but the crew hopes you'll stay longer!", "Mutiny on the ship, my captain! I am tasked to hand you a black mark in a private setting. Proceed with me immediately!");
			link.l1 = "He-he, ahem! Your request is granted, Officer Sharp!";
			link.l1.go = "give_sex_1_yes";
			link.l2 = "Not today, dear. Too much is happening right now.";
			link.l2.go = "give_sex_1_no";
		break;
		
		case "give_sex_1_yes":
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
			DialogExit();
			AddDialogExitQuestFunction("Helen_GiveSexGoToTavern");
		break;
		
		case "give_sex_1_no":
			dialog.text = "Oh, and what would you have a poor girl to do, huh? Alright, my dear, another time then.";
			link.l1 = "";
			link.l1.go = "give_sex_2_no";
		break;
		
		case "give_sex_2_no":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			npchar.location = "None";
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetOfficerType(npchar);
			chrDisableReloadToLocation = false;
			
			pchar.quest.Helen_GiveSex.win_condition.l1 = "Timer";
			pchar.quest.Helen_GiveSex.win_condition.l1.date.day = GetAddingDataDay(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l1.date.month = GetAddingDataMonth(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l1.date.year  = GetAddingDataYear(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l2 = "Location_Type";
			pchar.quest.Helen_GiveSex.win_condition.l2.location_type = "town";
			pchar.quest.Helen_GiveSex.function = "Helen_GiveSex";
		break;
		
		case "special_sex":
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
			SaveCurrentNpcQuestDateParam(npchar, "special_sex_date");
			
			dialog.text = "Ha! You don't have to ask me twice! Of course, let's go!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Helen_GiveSexGoToTavern");
		break;
		
		case "rainbow":
			dialog.text = "I'll throw you overboard right now!";
			link.l1 = "Hey, hey, hey! Calm down, dear!";
			link.l1.go = "rainbow_1";
		break;
		
		case "rainbow_1":
			dialog.text = "Come here, you rogue!";
			link.l1 = "Just kidding, Helen! I didn't mean to offend you!";
			link.l1.go = "rainbow_2";
		break;
		
		case "rainbow_2":
			dialog.text = "Oh really? Suck a joker...";
			link.l1 = "You're the most beautiful, and I love you madly!";
			link.l1.go = "rainbow_3";
		break;
		
		case "rainbow_3":
			dialog.text = "Get lost, Charles.";
			link.l1 = "";
			link.l1.go = "exit";
			
			DeleteAttribute(pchar, "questTemp.HelenDrinking.Rainbow");
			Achievment_Set("ach_CL_84");
		break;
		
		case "joan":
			dialog.text = "You're the hussy yourself! Be glad Jan made an honest woman out of you, or you'd still be spreading your legs for every passerby!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JoanDialog2");
		break;
		
		case "joan_1":
			dialog.text = "Harlot! Let's go, Charles!";
			link.l1 = "";
			link.l1.go = "exit";
			
			ResetSound();
			SetMusic("helendrinking_shanty");
			pchar.questTemp.lockedMusic = true;
			AddDialogExitQuestFunction("HelenDrinking_GoToFort");
		break;
		
		case "cutlass_training":
			dialog.text = "The cutlass fits perfectly in my hand! I don't know how to explain it... I always struggled with other types of cold weapons, like rapiers and swords. But this cutlass is a different story! It feels amazing! Thank you, Charles!";
			link.l1 = "Destiny has a way of finding us. I'm happy for you, Helen!";
			link.l1.go = "exit";
			notification("Medium Weapons +", "Helena");
		break;
		
		case "brothel_found":
			dialog.text = "Save your stories for someone else, they won't work on me. Do I look like a naive, lovestruck fool? I mean, I AM in love with you madly, but calling me a fool would be a stretch\n Listen, darling, do as you wish, but keep in mind that you won't find a better woman than me. If you want to look for her in brothels, go ahead, but then I'll vanish from your life for good.";
			link.l1 = "Helen, I...";
			link.l1.go = "brothel_found_1";
		break;
		
		case "brothel_found_1":
			dialog.text = "I understand everything, Charles. You love only me, and these are just natural urges. You know what my natural urge is? Respect from my man. A woman may not be satisfied with just love, darling. Let's forget about this misunderstanding for now, but ponder my words a bit. Fine?";
			link.l1 = "Fine, Helen.";
			link.l1.go = "exit";
		break;
		
		case "refuse":
			dialog.text = "You know how it goes. Let a girl cool off first.";
			link.l1 = "Sigh...";
			link.l1.go = "exit";
		break;
		
		// Тайна Порт-Рояля
		case "MysteryPortRoyal_Helena_1":
			dialog.text = "Francis... I remember him. He always waited for my arrival in Port Royal and was a hopeless romantic. I enjoyed spending time with someone far removed from the sea – all those poems and serenades... It was something new. A glimpse of a world I never knew.\nFrancis was wealthy, intelligent, and handsome – quite the catch. Any local girl would have gone mad for his attention, but back then, I was more concerned about keeping the Rainbow afloat.";
			link.l1 = "It seems the sensitive soul of a poet couldn’t bear your rejection. In all his letters, he spoke only of you, recalling the places you met. I can give you everything he left behind if you want it.";
			link.l1.go = "MysteryPortRoyal_Helena_2";
		break;
		
		case "MysteryPortRoyal_Helena_2":
			dialog.text = "I didn’t know he was sick. This all feels so foolish now. As for his gift... I’ve had enough of wills and inheritances. Trust me, I have everything I need – and more. You’d best keep it.";
			link.l1 = "One way or another, his legacy will still serve you in the end – which means I’ve unwittingly carried out his final wish. Quite the story.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.MysteryPortRoyal_Helena");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}

bool HelenDrinking_RobbedSvenson() {
	sld = &locations[FindLocation("SantaCatalina_houseS1_residence")];
	if (!CheckAttribute(sld, "private1.items.chest")) { 
		return true;
	}
	
	if (sti(sld.private1.items.chest) < 2) {
		return true;
	}
	
	return false;
}

// Эркюль Тонзаг, он же Плешивый Гастон
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
			if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "MainBegin")
			{
				dialog.text = "Well, hello, " + pchar.name + ". Glad to see you alive.";
				link.l1 = "Gaston! Is that you?";
				link.l1.go = "SJ_talk";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "MeetTonzag")
			{
				dialog.text = "Greetings, " + pchar.name + ". I already know about your dealings - John told me everything. I don't even know what to say. I admire you!";
				link.l1 = "I am pleased to hear such praise from you, Hercule!";
				link.l1.go = "SJ_talk_11";
				break;
			}
			dialog.text = "Good afternoon. Do you have business for me?";
			link.l1 = "No. My mistake. I am sorry. Bye. .";
			link.l1.go = "exit";	
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "SJ_talk":
			dialog.text = "You knew me by that name. But my real name is Hercule. Hercule Tonzag.";
			link.l1 = "Holy Lord! I am also glad to see you... I didn't recognize you in the heat of the fight. You were just in time with your help.";
			link.l1.go = "SJ_talk_1";
		break;
		
		case "SJ_talk_1":
			dialog.text = "Right after your departure I got news that Fleetwood stepped up efforts to protect his house. I suggested there may be a trap behind this. I immediately set sail to Antigua on my ship 'Twilight' - and, as you see now, for a good reason.";
			link.l1 = "True. I barely managed to deal with the guards inside the house, but I was too exhausted to keep fighting on the street...";
			link.l1.go = "SJ_talk_2";
		break;
		
		case "SJ_talk_2":
			dialog.text = "After this fight Fleetwood had put a Dutch spy on the wanted list. They thought you were a Dutch spy. He is at inveterate feud with them. The worst part was that a soldier in the house survived and remembered your face. But, anyway, it is not a problem now. I have finished what you'd started. This soldier will not be able to recognize anyone anymore, and no one will recognize him...";
			link.l1 = "Did you kill him? I see...";
			link.l1.go = "SJ_talk_3";
		break;
		
		case "SJ_talk_3":
			dialog.text = "Yes. While you were lying unconscious in John's house, I injured Fleetwood, but the fucker managed to survive. I struck him blind - threw pepper in his eyes, and then hit him before he had a chance to draw his sword. But the scum wore a hauberk under his uniform - it saved his life. Smart. Now he is staying in bed at home with increased security. It is very unfortunate that he survived.";
			link.l1 = "So, your main task on Antigua was eliminating Fleetwood?";
			link.l1.go = "SJ_talk_4";
		break;
		
		case "SJ_talk_4":
			dialog.text = "Generally, yes. Now it seems impossible, though - the house is always locked up, there are half a dozen of hand-picked guardsmen on duty round the clock, and they allow only his confidant to see him - an old canoneer Charlie, nicknamed the Knippel.";
			link.l1 = "That's already something...";
			link.l1.go = "SJ_talk_5";
		break;
		
		case "SJ_talk_5":
			dialog.text = "Wait a bit... Are you going to interfere with this affair?";
			link.l1 = "Why not? Don't you need help? You saved me, and I want to help. Also, I am still in need of coin.";
			link.l1.go = "SJ_talk_6";
			// belamour legendary edition -->
			link.l2 = "Why not? You are serious people. And serious people pay generously. I'm just looking for a job.";
			link.l2.go = "SJ_talk_6a";
		break;
		
		case "SJ_talk_6a":
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "Sneak", 120);
			dialog.text = "Believe me, friend, you will not manage that. You are a fine fellow, a real talent, and the logbook, which you had fetched, helped me plan an attempt on Fleetwood's life, you did a good job at slicing the guards - but you will never be able to get to Fleetwood now. Even I haven't the slightest clue how to do it.";
			if (pchar.Ship.Type == SHIP_NOTUSED)
			{
				link.l1 = "I will think it over. I still have time. It's too bad that my ship was arrested, and I do not have a crew.";
				link.l1.go = "SJ_talk_7";
			}
			else
			{
				link.l1 = "I will think about that. I have time and a ship.";
				link.l1.go = "SJ_talk_8";
			}
		break;
		
		case "SJ_talk_6":
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			// <-- legendary edition
			dialog.text = "Believe me, friend, you will not manage that. You are a fine fellow, a real talent, and the logbook, which you had fetched, helped me plan an attempt on Fleetwood's life, you did a good job at slicing the guards - but you will never be able to get to Fleetwood now. Even I haven't the slightest clue how to do it.";
			if (pchar.Ship.Type == SHIP_NOTUSED)
			{
				link.l1 = "I will think it over. I still have time. It's too bad that my ship was arrested, and I do not have a crew.";
				link.l1.go = "SJ_talk_7";
			}
			else
			{
				link.l1 = "I will think about that. I have time and a ship.";
				link.l1.go = "SJ_talk_8";
			}
		break;
		
		case "SJ_talk_7":
			dialog.text = "Don't worry about that. When your old tub was placed under arrest, I took all your officers and some of the sailors on board of my 'Twilight'. They know that you are alive and agreed to stay in service. And in reward for the journal, I am relinquishing my ship 'Twilight' to you.";
			link.l1 = "Thank you! I will remember that!";
			link.l1.go = "SJ_talk_9";
			if(GetSummonSkillFromName(pchar, SKILL_SAILING) < 46)
			{
				pchar.Ship.Type = GenerateShipHand(pchar, SHIP_CAREERLUGGER, 12, 580, 30, 800, 20000, 16.5, 65.5, 1.6);
			}
			else
			{
				pchar.Ship.Type = GenerateShipHand(pchar, SHIP_SCHOONER, 16, 1900, 50, 1350, 25000, 13.5, 55.0, 1.10);
			}
			pchar.Ship.name = "Twilight";
			SetBaseShipData(pchar);
			if(GetSummonSkillFromName(pchar, SKILL_SAILING) < 46) pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS12;
			else pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS16;
			SetCrewQuantityFull(pchar);
			pchar.Ship.Crew.Morale = 80;
			pchar.Ship.Crew.Exp.Sailors = 90;
			pchar.Ship.Crew.Exp.Cannoners = 70;
			pchar.Ship.Crew.Exp.Soldiers = 70;
			SetCharacterGoods(pchar, GOOD_BALLS, 100);
			SetCharacterGoods(pchar, GOOD_GRAPES, 100);
			SetCharacterGoods(pchar, GOOD_KNIPPELS, 100);
			SetCharacterGoods(pchar, GOOD_BOMBS, 100);
			SetCharacterGoods(pchar, GOOD_FOOD, 100);
			SetCharacterGoods(pchar, GOOD_POWDER, 300);
			SetCharacterGoods(pchar, GOOD_WEAPON, 60);
			SetCharacterGoods(pchar, GOOD_MEDICAMENT, 60);
		break;
		
		case "SJ_talk_8":
			AddMoneyToCharacter(pchar, 15000);
			dialog.text = "Yes, I would like to pay you for the journal. 15000 pesos - I don't have more at the moment, unfortunately. We'll settle it up in one day. ";
			link.l1 = "No need. This is enough. If you hadn't arrived in time, I wouldn't have needed any money, anyway.";
			link.l1.go = "SJ_talk_9";
		break;
		
		case "SJ_talk_9":
			dialog.text = "Alright, " + pchar.name + ", I have to go. I am not going back to Bridgetown yet. If you ever need me - ask John. Good luck!";
			link.l1 = "Good luck, Hercule!";
			link.l1.go = "SJ_talk_10";
		break;
		
		case "SJ_talk_10":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10);
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-13");
			pchar.questTemp.HWIC.Self = "HuntFleetwood";
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
		break;
		
		case "SJ_talk_11":
			dialog.text = "I would like to present you this armour for eliminating Fleetwood. It will protect you in future battles. Let's go see John now. He wants to talk to you and offer you... one interesting affair.";
			link.l1 = "Thank you for the present. Alright, let's go...";
			link.l1.go = "SJ_talk_12";
		break;
		
		case "SJ_talk_12":
			DialogExit();
			GiveItem2Character(pchar, "cirass7");//дать вещь
			sld = characterFromId("Merdok");
			AddLandQuestMark(sld, "questmarkmain");
			LAi_SetOwnerType(sld);
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			AddQuestRecord("Holl_Gambit", "3-35");
		break;
		
		case "Tonzag_hired":
			dialog.text = "I also would like to talk to you, captain. I was going to teach you my craft, but now I see that it is me who should learn from you. Hire me as an officer on your ship - you will not regret this.";
			link.l1 = "With pleasure, Hercule! Welcome to the crew!";
			link.l1.go = "Tonzag_hired_1";
			link.l2 = "Hercule, I cannot imagine myself being your superior. Thank you for your offer, but I just cannot see you as my subordinate.";
			link.l2.go = "Tonzag_exit";
		break;
		
		case "Tonzag_hired_1"://Тонзага - в офицеры
			DialogExit();
			DeleteAttribute(npchar, "LifeDay");
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			npchar.OfficerWantToGo.DontGo = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			LAi_SetOfficerType(npchar);
			npchar.greeting = "tonzag_hire";
			NextDiag.CurrentNode = "tonzag_officer";
			npchar.quest.meeting = true;
			npchar.HoldEquip = true;
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
			LAi_SetImmortal(npchar, false);
			SetCharacterPerk(npchar, "ShipEscape");
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
		break;
		
		case "Tonzag_exit":
			dialog.text = "As you wish, " + pchar.name + ". See you. Perhaps we will meet again. It's been a pleasure working with you.";
			link.l1 = "Good luck, friend!";
			link.l1.go = "Tonzag_exit_1";
		break;
		
		case "Tonzag_exit_1":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			DialogExit();
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "tonzag_officer":
			dialog.text = "I am listening to you, captain. What do you have to say?";
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Hercule, I am going to the old Indian city of Tayasal and, which is even more unusual, my way lies through a teleportation statue. Will you join me?";
				Link.l4.go = "tieyasal";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Hercule, give me a full ship report.";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "I want you to purchase certain goods every time we are docked.";
				Link.l12.go = "QMASTER_2";
			}

			if (CheckAttribute(NPChar, "IsCompanionClone"))//////////////////компаньон//////////////////////////////////////////////
			{
				//dialog.text = "Я прибыл по вашему распоряжению, капитан.";
				Link.l2 = "I need to issue several orders to you.";
				Link.l2.go = "Companion_Tasks";
				NextDiag.TempNode = "tonzag_officer";// не забыть менять в зависисомости от оффа
				break;
			}
			Link.l1 = "Listen to my order!";
            Link.l1.go = "stay_follow";
			link.l2 = "Nothing at the moment. At ease!";
			link.l2.go = "exit";
			NextDiag.TempNode = "tonzag_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Captain, so sorry, but I don't deal with numbers and calculations. Ask van Merden - he's got a knack for such things, however, I doubt that he'd be interested in leaving his nest.";
			Link.l1 = "You are right, Hercule. Meh, got to find me a purser...";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "Captain, when I was an innkeeper on Barbados I only purchased rum and provisions. And by provisions, I mean proper foods, not some crackers and corned beef. Sorry, but it's not my department.";
			link.l1 = "Perhaps we should turn my ship into a tavern... Just joking, Hercule. Whatever, I'll do it myself.";
			link.l1.go = "exit";
		break;
		
		//Указания для компаньона 19.02.08 -->/////////////////////////////////////////////////////////////////////////////////////////
		case "Companion_Tasks":
			dialog.Text = "I am listening to you.";
			Link.l1 = "This is about boarding.";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "This is about your ship.";
			Link.l2.go = "Companion_TaskChange";
			Link.l8 = "Nothing so far.";
			Link.l8.go = "exit";
		break;

		case "Companion_TaskBoarding":
			dialog.Text = "So what is your wish.";
			Link.l1 = "Don't board enemy ships. Take care of yourself and the crew.";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "I want you to board enemy ships.";
			Link.l2.go = "Companion_TaskBoardingYes";
		break;

		case "Companion_TaskChange":
			dialog.Text = "So what is your wish.";
			Link.l1 = "I would like you not to swap your ship for another one after boarding. It's too valuable.";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "When you are boarding enemy ships, you can take them for yourself, if they happen to be decent.";
			Link.l2.go = "Companion_TaskChangeYes";
		break;

		case "Companion_TaskBoardingNo":
			dialog.Text = "Aye-aye.";
			Link.l1 = "At ease.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
		break;

		case "Companion_TaskBoardingYes":
			dialog.Text = "It will be done.";
			Link.l1 = "At ease.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
		break;

		case "Companion_TaskChangeNo":
			dialog.Text = "Aye-aye.";
			Link.l1 = "It will be done.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;

		case "Companion_TaskChangeYes":
			dialog.Text = "It will be done.";
			Link.l1 = "At ease.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;
	//	<========////////////////////////////////////////
		
		case "stay_follow":
            dialog.Text = "What are your orders? ?";
            Link.l1 = "Stay here!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Follow me and don't fall behind!";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Change the type of your ammo.";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Choice of ammunition type:";
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
            dialog.Text = "Aye!";
            Link.l1 = "At ease.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Aye!";
            Link.l1 = "At ease.";
            Link.l1.go = "Exit";
        break;
	//<-- ----------------------------------- офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal":
			dialog.text = "You are lucky son of a bitch, captain. I am glad I've joined you back when me, you and John were working together. May a shark swallow me, if I won't support you in this undertaking!";
			link.l1 = "Thank you, Hercule! I am glad that I was right about you.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "So, when are we departing?";
			link.l1 = "A bit later. Now we should get prepared for the journey.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "23");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "tonzag_jailed":
			dialog.text = "Pretty much nothing, Cap. If this had to do with our business, they would have already had us on the torture table.\nSince they didn't take us for interrogation right away, the matter is apparently not urgent.\nEither a setup or extortion.\nThey'll marinate us here for a couple of days without explaining anything. And then they'll come with an offer, one we'll accept.";
			link.l1 = "Personal experience?";
			link.l1.go = "tonzag_jailed_1";
			link.l2 = "Well is there any way to get them to come with such an offer right now?";
			link.l2.go = "tonzag_jailed_2";
			locCameraFromToPos(-14.82, 0.92, 2.74, true, -60.00, -5.60, -22.70);
		break;
		
		case "tonzag_jailed_1":
			dialog.text = "Of course. Gruoh once got paid by the relatives of a dead man to spare him from the farewell caresses of the Trinidad executioner.\nShe paid the commandant for the right to walk through the holding cells. Common practice - many pay the soldiers for the opportunity to torment the people who can't fight back without any witnesses.\nThe man died quietly and without suffering. Clean and decent work.";
			link.l1 = "Gruoh? Who's that?";
			link.l1.go = "tonzag_jailed_1_1";
		break;
		
		case "tonzag_jailed_1_1":
			dialog.text = "Sorry, Cap. Wrong place and wrong time.";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "tonzag_jailed_2":
			dialog.text = "We can try. Let's wait for the feeding time, and I'll exchange a few words with the sentry. You see, they still haven't learned to search properly. Eh...";
			link.l1 = "What's wrong?";
			link.l1.go = "tonzag_jailed_2_1";
		break;
		
		case "tonzag_jailed_2_1":
			dialog.text = "Strange feeling, Cap. I would even call it a premonition. Excuse me, let's talk later.";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "tonzag_killed_hunters":
			dialog.text = "Did I miss something, Captain?";
			link.l1 = "Oh, nothing special, just another day at sea. Look at, you old devil! You've made quite a mess here for me.";
			link.l1.go = "tonzag_killed_hunters_1";
		break;
		
		case "tonzag_killed_hunters_1":
			dialog.text = "Blood washes off with cold water, Captain. We need to talk.";
			link.l1 = "You think? It wouldn't hurt to survive this day for starters.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_Victory");
		break;
		
		case "tonzag_after_victory_helena":
			dialog.text = "I'm glad to see you too, Rumba. Captain, I won't bother you, we'll talk later.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HelenBoardingDialog1");
		break;
		
		case "tonzag_after_victory_mary":
			dialog.text = "Hey, Ginger. Captain, I won't disturb, we'll talk later.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_MaryBoardingDialog1");
		break;
		
		case "tonzag_after_victory_alonso":
			dialog.text = "Captain, I won't bother you, we'll talk later.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ShowFrame");
		break;
		
		case "tonzag_drink":
			dialog.text = "Ready to hear me out, Captain?";
			link.l1 = "It's high time we talked, Hercule. I've just realized that I know almost nothing about you.";
			link.l1.go = "tonzag_drink_1";
		break;
		
		case "tonzag_drink_1":
			dialog.text = "So it's time to get acquainted. Let's skip the early years, if only because there's nothing there to talk about - a victorious soldier, a defeated soldier, a deserter, a marauder... you know how it goes.";
			link.l1 = "I don't, actually, but so far this sounds quite ordinary.";
			link.l1.go = "tonzag_drink_2";
		break;
		
		case "tonzag_drink_2":
			dialog.text = "Career opportunities after such a military path were few for me - a bandit, a hanged man, or a guard worthy of the Dutch West India Company. I chose the latter, as you understand.";
			link.l1 = "Did you desert from there too?";
			link.l1.go = "tonzag_drink_3";
		break;
		
		case "tonzag_drink_3":
			dialog.text = "On the contrary, I made a career there. I received an offer to join the combat wing of the Company's intelligence department, where I met my future wife.";
			link.l1 = "Ok, so far the story is quite peaceful... especially if you don't think too much about the methods of the Dutch.";
			link.l1.go = "tonzag_drink_4";
		break;
		
		case "tonzag_drink_4":
			dialog.text = "You won't earn huge money being honest, and you can fight competition in various ways. Yes, we were operating with via special methods...";
			link.l1 = "I guess I know what you mean...";
			link.l1.go = "tonzag_drink_5";
		break;
		
		case "tonzag_drink_5":
			dialog.text = "Yes, it could be anything: from piracy to setting fire to warehouses with goods. In the end, the scheme was exposed, and we were disbanded... on paper, of course. That is how the League was born, known and controlled only by the chosen leaders of the Company's higher echelons. For a Caribbean outlaw who is worth something, there were only two options: piracy or the League. And the League usually paid better\nFor the most part, the League still worked for the Dutch, but it could also take on side orders...";
			link.l1 = "Things are starting to clear up...";
			link.l1.go = "tonzag_drink_6";
		break;
		
		case "tonzag_drink_6":
			dialog.text = "The League was behind that farce on Tortuga. And then that landing party...";
			link.l1 = "I figured as much. But why?";
			link.l1.go = "tonzag_drink_7";
		break;
		
		case "tonzag_drink_7":
			dialog.text = "Because nobody leaves the League alive, and you can't get away scot-free with the things we did there, Captain. I wanted to retire, so I tried anyway. As you can see, not very successfully.";
			link.l1 = "Are you saying that your former colleagues took huge financial expenses, threw away almost a hundred people, burned a brander, and risked their warship just to... kill you for desertion?";
			link.l1.go = "tonzag_drink_8";
		break;
		
		case "tonzag_drink_8":
			dialog.text = "I was more than a runt in the League, Captain. I know too much about it. I can't just be let go, and they need to make this clear, so that no one else thinks about leaving the business... They tried to get to me before... quite a long time ago... They killed my wife and disfigured me, even though it cost them dearly. There is no happy ending to this story, Captain. Just give an order, and I'll leave the ship and deal with them on my own, for the final time.";
			link.l1 = "Don't talk nonsense, Hercule... And what role did Lucas Rodenburg play in all this? He must have been involved in these matters! Your, or rather his, 'organization', the League...";
			link.l1.go = "tonzag_drink_9";
		break;
		
		case "tonzag_drink_9":
			dialog.text = "Different agencies, Captain. Admittedly, they often did obey the same person and worked closely. But Rodenburg's special agents delivered pinpoint effective strikes, while the League carried out mass operations. And now what has become of the League? The organization is no more, as you can see: I'm here with you, John Murdock left, Longway ran off, Van Berg is on the bottom of the sea, Rodenburg was executed... Still, I owed that late scoundrel. He noticed me in the League, and when I tried to leave it, he pulled me out of some serious trouble and made me his deputy. Of course, the others didn't like it, but no one dared disobey him... And then, under the known circumstances, he decided to get rid of Murdock and me, but you intervened and took me into your service\nAnd so I thought, 'Here's my second chance to break up with the past...' You outplayed Rodenburg, the League lost its patron, there was no more danger... But, of course, I was wrong... Old fool... But enough about that, Captain. Let's think about what to do next, if of course, you really don't plan to let me go at the first port.";
			link.l1 = "I don't. I suppose you have a plan?";
			link.l1.go = "tonzag_drink_10";
		break;
		
		case "tonzag_drink_10":
			dialog.text = "Nothing special, actually. We'll never wipe them all out, but we can inflict such big losses on them that it won't be worth it for them to keep coming after me...us.";
			link.l1 = "And how do we do that? Do they have a camp?";
			link.l1.go = "tonzag_drink_11";
		break;
		
		case "tonzag_drink_11":
			dialog.text = "A large fortress? Hardly. It would be too noticeable and dangerous for the League. And by losses, I don't mean human losses - they don't care about people, but they won't enjoy losing gold. The money from the Company is no longer coming to them, right? I doubt the League found a new patron, so they must be squeezing gold from somewhere else.";
			link.l1 = "And what place would that be?";
			link.l1.go = "tonzag_drink_12";
		break;
		
		case "tonzag_drink_12":
			dialog.text = "I don't know, Captain.";
			link.l1 = "Hercule, but you just said that you are being pursued precisely because you know too much!";
			link.l1.go = "tonzag_drink_13";
		break;
		
		case "tonzag_drink_13":
			dialog.text = "Let me think... Perhaps the League is currently operating against the Spaniards. They are the primary candidates for a good shake up. Speaking of which, Rodenburg was always on good terms with the Castilian fat cats. Sometimes he would direct the League boys towards them for various jobs and always prohibited causing them any harm, which by the way, the boys didn't like very much...";
			link.l1 = "Good terms, you say? And what about that one Hidalgo and his finger that you made me drag to your tavern?";
			link.l1.go = "tonzag_drink_14";
		break;
		
		case "tonzag_drink_14":
			dialog.text = "That was a special case, a side order. If you feel guilty, Captain, you can rest easy - that Don got what he deserved... But I'm talking about something else: after their employer disappeared, the League operatives could just give in to their desires and try to grab a solid piece of the Spanish pie. Thanks to working with the Spaniards under Rodenburg, they know where and what to take.";
			link.l1 = "Hm... you might be right. But as far as I know, no one really brakes into Spanish banks, operating against the Spaniards at sea - that's up to the lady luck... Maybe we should look for some Spanish enterprise? A factory?";
			link.l1.go = "tonzag_drink_15";
		break;
		
		case "tonzag_drink_15":
			dialog.text = "Reasonable assumption, Captain... Do we have any other leads?";
			link.l1 = "Hm... the ship that attacked us today went south...";
			link.l1.go = "tonzag_drink_16";
		break;
		
		case "tonzag_drink_16":
			dialog.text = "It's unlikely that its captain will bother us again, but he must warn the others that things did not go as planned, and perhaps, transport the personnel to another place. Anything else?";
			if (CheckAttribute(pchar, "questTemp.TonzagQuest.KnowMain")) {
				link.l1 = "Yes, I had a friendly chat with the Tortuga prison commandant... He mentioned something about the mainland.";
				link.l1.go = "tonzag_drink_know";
			} else {
				link.l1 = "No, nothing else.";
				link.l1.go = "tonzag_drink_notknow";
			}
		break;
		
		case "tonzag_drink_know":
			dialog.text = "Excellent, Captain! South, mainland, Spaniards - means we'll find them quickly. Are we setting sail? And thanks for listening to my story.";
			link.l1 = "Yeah, quite a heart-to-heart conversation you and I ended up having... Let's set sail!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ExitToSea");
		break;
		
		case "tonzag_drink_notknow":
			dialog.text = "Not much to go by. But for people like us that's enough. Shall we head south? Look for a Spanish commercial enterprise? And thanks for listening to my story.";
			link.l1 = "Yeah, quite a heart-to-heart conversation you and I ended up having... Let's set sail!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ExitToSea");
		break;
		
		case "tonzag_dead":
			dialog.text = "Look, Captain. That's how they operate.";
			link.l1 = "And you worked like that too?";
			link.l1.go = "tonzag_dead_1";
		break;
		
		case "tonzag_dead_1":
			dialog.text = "Let's go, see what's inside.";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "tonzag_officer";
			AddDialogExitQuestFunction("Tonzag_AfterDead");
		break;
		
		case "tonzag_afterminefight":
			dialog.text = "A sordid affair, Captain. We cleared out this den, but it's certainly not the last one...";
			link.l1 = "What about the mine, Hercule?! All those people outside?! They were also 'cleared out'! And what did that scoundrel mean?";
			link.l1.go = "tonzag_afterminefight_1";
		break;
		
		case "tonzag_afterminefight_1":
			dialog.text = "Let's discuss this later, Captain. Their commander survived; we need to interrogate him.";
			link.l1 = "And what if he knows nothing?";
			link.l1.go = "tonzag_afterminefight_2";
		break;
		
		case "tonzag_afterminefight_2":
			dialog.text = "He knows something. Think about it - they were waiting for us, carried out all the gold, and eliminated witnesses. That means they had a plan. I want to take a look around here, and later I'll bring the scoundrel to the ship myself. You should also keep an eye out; perhaps they were too hasty and missed something.";
			link.l1 = "Fine, but when we get back to the ship, there is a serious conversation to be had!";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "tonzag_officer";
			locations[FindLocation("LosTeques_town")].locators_radius.reload.gate_back = 1.0;
			DeleteAttribute(&locations[FindLocation("LosTeques_town")], "locators_radius.reload.reload1_back");
			AddDialogExitQuestFunction("Tonzag_PrepareJournal");
		break;
		
		case "tonzag_in_hold":
			dialog.text = "Good news, Captain.";
			link.l1 = "I see nothing good in our situation, Hercule. Let's go, we need to talk privately.";
			link.l1.go = "tonzag_in_hold_1";
		break;
		
		case "tonzag_in_hold_1":
			dialog.text = "So, it's like that, huh? Aye, Captain.";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "tonzag_officer";
			AddDialogExitQuestFunction("Tonzag_EnterAlonso");
		break;
		
		case "tonzag_drink_again":
			dialog.text = "I see that we're in for a serious conversation, Captain.";
			link.l1 = "Yes, and I'll be the one doing the talking. First off, don't you think there is a certain trend emerging here? Piles of corpses are following us wherever we go! First, you take a load of grapeshot to the gut, and the next day over a hundred people, good and not so good, die in... I can't even call it a naval battle! A settlement was wiped out just a few days ago, and today we have contributed to the growing pile by slaughtering a bunch of people in the mines.";
			link.l1.go = "tonzag_drink_again_1_1";
		break;
		
		case "tonzag_drink_again_1_1":
			dialog.text = "";
			link.l1 = "Naturally, I'm worried about prospect of the pile becoming a mountain tomorrow, but what really frightens me is that all this blood is being shed because of one person. And that person holds a significant position in my crew!";
			link.l1.go = "tonzag_drink_again_1";
		break;
		
		case "tonzag_drink_again_1":
			dialog.text = "";
			link.l1 = "Second, you lied to me, Hercule. No deserter is worth the effort your former colleagues are putting into eliminating you. What was our prisoner shouting in the mines? Traitor? Porto Bello? Gruoh? You've done something, Hercule, and this time I want the truth.";
			link.l1.go = "tonzag_drink_again_2";
		break;
		
		case "tonzag_drink_again_2":
			dialog.text = "Truth? The truth is, Captain, that I did desert, along with my wife Gruoh. Madame Tonzag didn't want to leave the League; she loved that life, but she loved me even more. We were supposed to take care of a Spanish hidalgo, but he made a better offer. It was our chance, and we both agreed to go into his service. Of course, the League thought we perished on a mission and sent a second group to Porto Bello to finish the job and seek revenge.";
			link.l1 = "And you killed them all?";
			link.l1.go = "tonzag_drink_again_3";
		break;
		
		case "tonzag_drink_again_3":
			dialog.text = "First, they killed Gruoh and disfigured me. The hidalgo didn't want anything to do with me anymore and threw me out. That's when Rodenburg found me...";
			link.l1 = "And how am I supposed to trust you now? You deserted the army, deserted the League, and killed your own partners! When the right moment comes, will you betray me as well?";
			link.l1.go = "tonzag_drink_again_4";
		break;
		
		case "tonzag_drink_again_4":
			dialog.text = "Yes, I deserted, I broke the contract, I killed a couple dozens of League members. But I've learned that lesson, Captain. And besides, a dead man can't betray anyone, and I've been dead for a long time, ever since Porto Bello. And maybe that's why it's so hard to kill me now.";
			link.l1 = "That's enough for today. I feel like you're still not telling me everything.";
			link.l1.go = "tonzag_drink_again_5";
		break;
		
		case "tonzag_drink_again_5":
			dialog.text = "I'll handle the prisoner myself, or do you wish to join in?";
			link.l1 = "Let's go. I'll interrogate him myself.";
			link.l1.go = "tonzag_drink_again_hold";
			link.l2 = "No, such matters are not for me. See you in my cabin in half hour!";
			link.l2.go = "tonzag_drink_again_cabin";
		break;
		
		case "tonzag_drink_again_hold":
			DialogExit();
			
			NextDiag.CurrentNode = "tonzag_officer";
			AddDialogExitQuestFunction("Tonzag_ReturnToHold");
		break;
		
		case "tonzag_drink_again_cabin":
			DialogExit();
			
			NextDiag.CurrentNode = "tonzag_officer";
			AddDialogExitQuestFunction("Tonzag_ReturnToCabin");
		break;
		
		case "tonzag_hold":
			dialog.text = "Who's in charge now? Arno?";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HoldDialog1");
		break;
		
		case "tonzag_hold_1":
			dialog.text = "That scum rose to power? It didn't take you long to degrade to an ordinary gang of bandits...";
			link.l1 = "Who's Austin?";
			link.l1.go = "tonzag_hold_2";
		break;
		
		case "tonzag_hold_2":
			dialog.text = "Austin's gang was famous for luring free Captains into the wilderness, cutting them up, and completely stripping their corpses of any money or trinkets. Good business, and there's no shortage of adventure seekers, so nobody minded. But they hit a snag with one Captain, and so he had to take his crew under the Company's wing. We kept him on a leash and let him loose only when we needed to solve problems in a quick and simple way.";
			link.l1 = "I doubt that I can negotiate a deal with such a person.";
			link.l1.go = "tonzag_hold_3";
		break;
		
		case "tonzag_hold_3":
			dialog.text = "That's for sure. If he and his people are running things now, soon the League will turn into just another gang.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HoldDialog3");
		break;
		
		case "tonzag_after_hold":
			dialog.text = "An interesting conversation we had.";
			link.l1 = "I'd like to know how much of it is true... What about the massacre in Porto Bello? If he wasn't lying, it means that the last time you and I spoke, you once again omitted a couple of important facts from your illustrious biography.";
			link.l1.go = "tonzag_after_hold_1";
		break;
		
		case "tonzag_after_hold_1":
			dialog.text = "It was hot in Porto Bello, Captain. I fought for my life, for the life of the employer, for the life of my wife. I didn't have time to count the killed and mourn every peasant who showed up on the street at the wrong time.";
			link.l1 = "In that order of priority?";
			link.l1.go = "tonzag_after_hold_2";
		break;
		
		case "tonzag_after_hold_2":
			dialog.text = "No, of course not. Hers first. Always.";
			link.l1 = "What do you think? Should we go to Caracas?";
			link.l1.go = "tonzag_after_hold_3";
		break;
		
		case "tonzag_after_hold_3":
			dialog.text = "I personally wouldn't, Captain. And I'd advise you against it as well. To the League, you are not an enemy anymore, and I am of no interest to them, at least for the time being while I am in your service. Also, I have this nasty feeling deep down\nIt'll be bad if we go there. Very bad. This story does not have a happy ending. But I'll be with you to the end, Captain.";
			link.l1 = "I'll consider it.";
			link.l1.go = "exit";
			
			if (CheckCharacterItem(pchar, "MerdokArchive")) {
				link.l1.go = "tonzag_after_hold_4";
			}
			
			AddDialogExitQuestFunction("Tonzag_GoToCaracas");
		break;
		
		case "tonzag_after_hold_4":
			dialog.text = "";
			link.l1 = "By the way, you were right - they didn't manage to clean up the mine well enough. Look.";
			link.l1.go = "tonzag_after_hold_5";
		break;
		
		case "tonzag_after_hold_5":
			dialog.text = "An officer's journal... encrypted, but it's an old cipher, I know it\nNothing interesting, it seems. It was the journal of our prisoner. It's clear now why he was so willing to talk. Look here - indications of a hidden treasure! The scoundrel clearly planned to retire and was ready to slip away at any moment!";
			link.l1 = "And where is this hidden place?";
			link.l1.go = "tonzag_after_hold_6";
		break;
		
		case "tonzag_after_hold_6":
			dialog.text = "You know that island, Captain. In its waters, you ended Van Berd.";
			link.l1 = "Alright, it's not too far, so let's check it out. As for Caracas, I haven't decided yet, but I think we have a month.";
			link.l1.go = "tonzag_after_hold_7";
		break;
		
		case "tonzag_after_hold_7":
			dialog.text = "As you wish, Captain. I'm with you to the end.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_CreateLoot");
		break;
		
		case "tonzag_after_drink":
			dialog.text = "It's done, Captain. Austin is currently in Caracas; I think we have a month.";
			link.l1 = "First things first. What did the prisoner say? Who is this Austin? And why should we go to Caracas?";
			link.l1.go = "tonzag_after_drink_1";
		break;
		
		case "tonzag_after_drink_1":
			dialog.text = "Austin's gang was famous for luring free Captains into the wilderness, cutting them up, and completely stripping their corpses of any money or trinkets. Good business, and there's no shortage of adventure seekers, so nobody minded. But they hit a snag with one Captain, and so he had to take his crew under the Company's wing. We kept him on a leash and let him loose only when we needed to solve problems in a quick and simple way.";
			link.l1 = "I doubt that I can negotiate a deal with such a person.";
			link.l1.go = "tonzag_after_drink_2";
		break;
		
		case "tonzag_after_drink_2":
			dialog.text = "That's for sure. If he and his people are in charge now, soon the League will turn into just another gang. But I wouldn't go to Caracas, Captain.";
			link.l1 = "Seriously? Are you afraid?";
			link.l1.go = "tonzag_after_drink_3";
		break;
		
		case "tonzag_after_drink_3":
			dialog.text = "It's not like that, Captain. Before dying from his wounds, the prisoner revealed that you are no longer an enemy to the League, and I'm of no interest to them, at least for the time being while I'm in your service. The League appears to have some new influential patron who has ordered to leave us alone\nAnd Caracas... I have this nasty feeling deep down...It'll be bad if we go there. Very bad. This story does not have a happy ending. But I'll be with you to the end, Captain.";
			link.l1 = "I'll think about it. Of course, I would like to resolve this story once and for all, but perhaps you are right. I doubt that after the events of the past week, they will dare to approach us again.";
			link.l1.go = "exit";
			
			if (CheckCharacterItem(pchar, "MerdokArchive")) {
				link.l1.go = "tonzag_after_drink_4";
			}
			
			AddDialogExitQuestFunction("Tonzag_GoToCaracas");
		break;
		
		case "tonzag_after_drink_4":
			dialog.text = "";
			link.l1 = "By the way, you were right - they didn't manage to clean up the mine well enough. Look.";
			link.l1.go = "tonzag_after_drink_5";
		break;
		
		case "tonzag_after_drink_5":
			dialog.text = "An officer's journal... encrypted, but it's an old cipher, I know it\nNothing interesting, it seems. It was the journal of our prisoner. Look here - indications of a hidden treasure! The scoundrel clearly planned to retire and was ready to slip away at any moment!";
			link.l1 = "And where is this hidden place?";
			link.l1.go = "tonzag_after_drink_6";
		break;
		
		case "tonzag_after_drink_6":
			dialog.text = "You know that island, Captain. In its waters, you ended Van Berd.";
			link.l1 = "Alright, it's not too far, so let's check it out. As for Caracas, I haven't decided yet, but I think we have a month.";
			link.l1.go = "tonzag_after_drink_7";
		break;
		
		case "tonzag_after_drink_7":
			dialog.text = "As you wish, Captain.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_CreateLoot");
		break;
		
		case "tonzag_church":
			dialog.text = "Hold on, Captain. I'm going there alone.";
			link.l1 = "And why is that? Feeling heroic now? It's too late; you've made this mess, but we have to clean it together.";
			link.l1.go = "tonzag_church_1";
		break;
		
		case "tonzag_church_1":
			dialog.text = "No need for you to pay for my mistakes, Captain. You were right - wherever I go, people die, and innocent blood flows. If we enter that church together, it will be another Porto Bello, and I don't want that.";
			link.l1 = "What really happened there?";
			link.l1.go = "tonzag_church_2";
		break;
		
		case "tonzag_church_2":
			dialog.text = "A massacre. I wanted to retire, Captain. I wanted to take the gold, my wife, and go home to Carcassonne. I knew the League would send more people to finish my job and took a generous advance from my new patron. Then all that was left was to set the city guard off against my former accomplices and the new employer. In all that commotion, I was to vanish with the money, and perhaps if time permitted, rob a few fat cats of Porto Bello.";
			link.l1 = "Good plan, although I would have done it differently. Too many things could go wrong.";
			link.l1.go = "tonzag_church_2a";
			link.l2 = "I'm no angel myself, but your approach makes even me shudder. I'm surprised you haven't betrayed me yet, as you did the League, the Hidalgo, and even your own wife.";
			link.l2.go = "tonzag_church_2a";
		break;
		
		case "tonzag_church_2a":
			dialog.text = "Everything that could go wrong, did go wrong. Shooting a three-pounder towards the governor's palace was a mistake. It barely scratched the governor himself, but his beautiful daughter, as I hear, had to have both her legs amputated below the knees to save her life. The response was horrific - a blood bath; great many people perished, Captain. Now you're looking at the last living witness to those events, and not long ago, you cut down another one yourself.";
			link.l1 = "Explain.";
			link.l1.go = "tonzag_church_3";
		break;
		
		case "tonzag_church_2b":
			dialog.text = "If Madame Tonzag were still alive, I would have betrayed you without hesitation, Captain. I am a living dead man, following you because I have no other place in this world. Now you're looking at the last living witness to those events, and not long ago, you cut down another one yourself.";
			link.l1 = "Explain.";
			link.l1.go = "tonzag_church_3";
		break;
		
		case "tonzag_church_3":
			dialog.text = "Forgive me, Captain, for not telling you everything on the way. When we first met, I thought you were just another scumbag like me. And you know the first thing I did? I sent you to clean up after me - to kill that Spanish Don I initially didn't want to kill and then decided to betray. That Hidalgo, Rodriguez...";
			link.l1 = "And what did you need his finger for?";
			link.l1.go = "tonzag_church_4";
		break;
		
		case "tonzag_church_4":
			dialog.text = "No tricks there. Just a test, Captain. We recruited dozens of young cutthroats like you every year. Only a few passed the basic honesty check, and even they died in the first operations. You weren't supposed to survive the operation with Fleetwood's logbook. I was planning to simply enter the house, finish off the survivors, and take the logbook.";
			link.l1 = "If my memory serves me right, the story took a slightly different turn.";
			link.l1.go = "tonzag_church_5";
		break;
		
		case "tonzag_church_5":
			dialog.text = "So it did, Captain. I don't know what prompted me to help you, but you fought the Foxes with such a zest for life that you even infected me with it, if only briefly. In the end, unknowingly, you saved me. You owe me nothing, Captain. And I won't let you in there. This is my business, my redemption.";
			link.l1 = "As you wish, Hercule. It hurts to lose such a fighter, but you lost yourself a long time ago, and you're not worth more spilled blood. You don't owe me anything either, and I hope you find redemption in that little church.";
			link.l1.go = "tonzag_church_bad";
			link.l2 = "Nice speech, Hercule. Go to hell! If you haven't noticed, your problems have become mine lately. You're my officer, and only I will decide whether you deserve forgiveness or not. So you'll have to stay with us a little longer and earn your redemption with valor as part of my crew!";
			link.l2.go = "tonzag_church_good";
		break;
		
		case "tonzag_church_bad":
			dialog.text = "Thank you for everything, Captain. Farewell!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ChurchBad");
		break;
		
		case "tonzag_church_good":
			dialog.text = "Aye aye, Captain!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ChurchGood");
		break;
		
		case "tonzag_afterchurchfight":
			dialog.text = "I've seen many scoundrels in my time, Captain, but for the first time, I felt a twist of horror inside me. What do you think: if a smaller monster kills a bigger monster, does that count towards redemption?";
			link.l1 = "Do they dilute rum with water? Tell me when you figure it out. Let's go, we're done here.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ResetTonzag");
		break;

	}
}
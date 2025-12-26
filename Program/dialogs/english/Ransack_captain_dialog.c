// BOAL диалог пленников - в трюме
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ref offref;
    int i, cn;
    int qty;
    string attrLoc, sTmp;
    
	switch(Dialog.CurrentNode)
	{
		// -----------------------------------Диалог первый - первая встреча
		case "First time":
		//--> Jason, Ложный след
		if (CheckAttribute(pchar, "questTemp.FalseTrace.Prisoner") && GetFullName(npchar) == pchar.questTemp.FalseTrace.CapName)
		{
			dialog.text = "What do you want, captain? To discuss my ransom? I want you to know that I care about the girl's fate...";
			link.l1 = "Are you talking about Katerine Rayner? I am already informed about it, "+pchar.questTemp.FalseTrace.CapName+". She asked me to speak with you.";
			link.l1.go = "FalseTrace_Prisoner";
			break;	
		}
		//<-- Ложный след
		
		// Addon-2016 Jason ФМК-Гваделупа
		if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG != "fail" && CheckAttribute(pchar, "questTemp.FMQG.Prisoner") && GetFullName(npchar) == pchar.questTemp.FMQG.Prisoner)
		{
			dialog.text = "";
			link.l1 = "See now, don Juan, treason is a foul thing...";
			link.l1.go = "FMQG";
			break;	
		}
			if (sti(NPChar.nation) == PIRATE)
			{
				dialog.text = RandSwear()+"I am your prisoner, "+GetAddress_Form(NPChar)+". But I want you to know that "+NationNameNominative(sti(NPChar.nation))+" never pays for their people. We are all on our own.";
				link.l1 = "Well... I see that I won't make any profit from you. At least I can ransom you as a criminal in any colony.";
				link.l1.go = "offender";
				if (FindFreeRandomOfficer() > 0)
				{
					link.l2 = "Look, you are a skilled fighter and I need people like you. Would you like to serve under my command?";
					link.l2.go = "free_to_officer";
				}	
			}
			else
			{
				dialog.text = RandSwear()+"I am your prisoner, "+GetAddress_Form(NPChar)+". "+NationNameNominative(sti(NPChar.nation))+" will pay a good price for my freedom.";
				if(NPChar.EncType == "trade" && FindFreeRandomOfficer() > 0 && CheckAttribute(NPChar, "Back.Ship.Mode") && NPChar.Back.Ship.Mode == "trade")
				{
					link.l1 = "Look, you are a skilled sailor and I need people like you. Would you like to serve under my command?";
					link.l1.go = "free_to_officer_trader";
				}
			}
			attrLoc = Sea_FindNearColony();
			if (attrLoc != "none") 
			{
                link.l3 = "We are not far from "+GetCityName(attrLoc)+". And I could let you go here.";
			    link.l3.go = "free_withoutFee";
			}
			else
			{
                link.l3 = "Go to the boatswain, tell him to give you a locker. You can disembark at the next harbour.";
			    link.l3.go = "free_withoutFee_2";
			}			
			link.l4 = "I suppose I shall make a fine slave of you - strong and dutiful.";
			link.l4.go = "Slave_1";
			link.l5 = "You ignored an order to lower your sails and resisted with force. You'll hang for it. The boatswain has already received my orders.";
			link.l5.go = "PunishmentAction";
			link.l99 = "I know.";
			link.l99.go = "exit";
			NextDiag.TempNode = "second time"; 
		break;
		
		case "second time":
			if(CheckAttribute(NPChar,"Hold_GenQuest") && !CheckAttribute(pchar,"GenQuest.Hold_GenQuest"))
			{
				switch(sti(NPChar.Hold_GenQuest.variant))
				{				
					case 0: // "tip-off"
						dialog.text = RandPhraseSimple("Captain, would you like to hear my proposal for a more profitable alternative to my ransom?","I understand that there is no room for barter here, but would you like to hear my proposal?");
						link.l1 = "I am listening.";	
						link.l1.go = "free_tip_off";
					break;
					
					case 1:
						dialog.text = "Captain, why won't you just release me? I have no value to you. If you sell me to slavers, you'll only get a few coins and a bad reputation.";
						link.l1 = "And if I simply release you, I won't get a thing...";
						link.l1.go = "free_by_hoard";
						attrLoc = Sea_FindNearColony();
						if (attrLoc != "none") 
						{
							link.l2 = "You have ignored an order to lower your sails and resisted with force. You will be hanged for it. The boatswain has already received my orders.";
							link.l2.go = "PunishmentAction";							
						}
						else
						{
							link.l2 = "You are really insistent, so I think I can give you what you want. You are a free man now. Leave my ship.";
							link.l2.go = "free_in_sea";
						}
						link.l3 = LinkRandPhrase("Don't test my patience. You are already lucky to be alive.","I have my own plans for you.","I suppose you may still be of use to me in the future.");
						link.l3.go = "exit";	
					break;
					
					case 2: // "ransom"
						dialog.text = "Captain, this uncertainty is killing me. May I know what you plan to do with me?";
						link.l1 = "Have you got anything to offer me?";
						link.l1.go = "free_buyout";
						link.l2 = RandPhraseSimple("I haven't got any ideas about you yet.",RandPhraseSimple("Plans? A cannonball around your neck? I'm joking, ha!","You are my prisoner and I have every right to do with you whatever I wish. Your own opinion has no value here."));
						link.l2.go = "exit";
					break;										
				}
				NextDiag.TempNode = "second time"; 
			}
			else
			{
				if (sti(NPChar.nation) == PIRATE)
				{
					dialog.text = "Captain, why won't you just let me go? You don't need me. Becoming a pirate was my only option, as I have no valuable skills or education. All I wanted was to earn some coin and then retire.";
					if (FindFreeRandomOfficer() > 0)
					{
						link.l2 = "Look, you are a skilled fighter and I need cutthroats like you. Would you like to be my officer?";
						link.l2.go = "free_to_officer";
					}				
					link.l3 = LinkRandPhrase("No mercy for you. There are plenty of thugs at sea. At least there will be one less sailing now."," Any problems, 'sea wolf'? Stay here and keep quiet.","Gallows await all of your kind. I will sell you to the authorities, and that will be a great lesson for any pirate.");	
					link.l3.go = "exit";
				}
				else
				{
					if(NPChar.EncType == "trade")
					{
						dialog.text = "Captain, I beg you... Release me. I have a family and children, and they won't make it without me.";
						if (FindFreeRandomOfficer() > 0 && CheckAttribute(NPChar, "Back.Ship.Mode") && NPChar.Back.Ship.Mode == "trade")
						{
							link.l2 = "Look, you are a skilled sailor and I need people like you. Would you like to serve under my command?";
							link.l2.go = "free_to_officer_trader";
						}
						link.l3 = LinkRandPhrase("I have my own plans for you.","I suppose that you may still be useful to me in the future.","You are my prisoner and I have every right to do with you whatever I want.");
						link.l3.go = "exit";
					}
					if(NPChar.EncType == "war")
					{
						dialog.text = RandPhraseSimple("Captain, I have lost the fight and I beg you for your mercy. ","Captain, I beg for your generosity. I understand that there is no reason for you to treat me as a prisoner of war, so I ask you to spare me. I give you my word that I will avoid meeting you at sea.");
						link.l2 = LinkRandPhrase("Don't test my patience. You are already lucky to be alive.",RandPhraseSimple("I have my own plans for you.","I suppose you may still be of use to me in the future."),RandPhraseSimple("You are my prisoner and I have every right to do with you whatever I wish. Your own opinion has no value here.","You are... well, you were a captain of a warship and you were aware of the risks. Don't try to present yourself as a saint here."));
						link.l2.go = "exit";	
						if (isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 1)
						{
							if(sti(Items[sti(pchar.EquipedPatentId)].Nation) == sti(NPChar.nation) && FindFreeRandomOfficer() > 0)
							{
								link.l3 = "Look, you are a skilled fighter and I need cutthroats like you. Would you like to be my officer?";
								link.l3.go = "free_to_officer";
							}
						}
					}
				}
				attrLoc = Sea_FindNearColony();
				if (attrLoc != "none") 
				{
					link.l4 = "We are not far from "+GetCityName(attrLoc)+". And I could let you go here.";
					link.l4.go = "free_withoutFee";
				}
				else
				{
					if(NPChar.EncType == "trade" || NPChar.EncType == "pirate")
					{
						link.l4 = "Go to the boatswain, tell him to give you a locker. You can disembark at the next harbour.";
						link.l4.go = "free_withoutFee_4";			
					}	
					else
					{
						link.l4 = "Damn you! Go to the boatswain, tell him to give you a locker. You can disembark at the next harbour. And remember, our next meeting will be the last.";
						link.l4.go = "free_withoutFee_4";
					}
				}				
				link.l5 = "You have ignored an order to lower your sails and resisted with force. You will be hanged for it. The boatswain has already received my orders.";
				link.l5.go = "PunishmentAction";
				NextDiag.TempNode = "second time"; 
			}	
		break;
		
		case "offender":
			dialog.text = "Criminal? Are you kidding me,"+GetAddress_Form(NPChar)+"!";
			link.l1 = "No kidding. You are a pirate.";
			link.l1.go = "exit";
		break;
		
		case "free_to_officer":
			if ((GetSummonSkillFromName(pchar, "Leadership") + 20) <= GetSummonSkillFromName(npchar, "Leadership"))
			{
				dialog.text = "Serving under your command? I'd rather feed the sharks!";
				link.l1 = "Watch your tongue or you will feed them.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "To be your officer, "+GetAddress_Form(NPChar)+"? I agree. I know my job and I have nothing to lose.";
				link.l1 = "Deal! Go and do your job.";
				link.l1.go = "free_to_officer_Hire";
				link.l2 = "Wait a moment, I've changed my mind.";
				link.l2.go = "exit";
			}
		break;

		case "free_to_officer_trader":
			if (GetSummonSkillFromName(pchar, "Leadership") <= GetSummonSkillFromName(npchar, "Leadership"))
			{
				dialog.text = LinkRandPhrase("It is a tempting offer... but I have to refuse it. On principle.","Sorry, but after what you did to my friends... It's impossible.","No, captain. After all this terror I can't do this job anymore. I made a vow that if the Blessed Virgin hears my prayers and grants me freedom I won't sail anymore.");
				link.l1 = "It is your choice. I won't insist.";	
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Why not? I'm a poor captain, lost my ship, and there's nothing left for me on shore. Except bills and debts...";
				link.l1 = "Deal! Go to the boatswain and get your allowances. I will give you a position on my ship a bit later.";	
				link.l1.go = "free_to_officer_Hire";
				link.l2 = "Wait a bit, I've changed my mind.";
				link.l2.go = "exit";
			}
		break;
		
		case "free_to_officer_Hire":
            NPChar.Dialog.Filename = "Enc_Officer_dialog.c";
            NPChar.greeting = "Gr_Officer";
            NPChar.loyality = 5 + rand(10);
		    if (sti(NPChar.reputation) > 41)
		    {
		        NPChar.alignment = "good";
		    }
		    else
		    {
		        NPChar.alignment = "bad";
		    }
            ReleasePrisoner(NPChar); // освободили пленника
            DeleteAttribute(NPChar, "LifeDay") // постоянный
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			// тут трем накопивщиеся сабли и корабли 290704 BOAL -->
			DeleteAttribute(Npchar, "Ship");
			Npchar.Ship.Type = SHIP_NOTUSED;
            DeleteAttribute(Npchar, "Fellows"); // его офицеры
            Npchar.Fellows.Passengers.id0 = Npchar.index; // свой пассажир

			Npchar.Fellows.Passengers.boatswain = "-1";
			Npchar.Fellows.Passengers.navigator = "-1";
			Npchar.Fellows.Passengers.doctor = "-1";
			Npchar.Fellows.Passengers.cannoner = "-1";
			Npchar.Fellows.Passengers.treasurer = "-1";
			Npchar.Fellows.Passengers.carpenter = "-1";
            
			if(CheckAttribute(NPChar,"Hold_GenQuest")) DeleteAttribute(NPChar, "Hold_GenQuest");
			
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			DialogExit();
        break;
				
		case "Slave_1":
			dialog.text = "But "+GetAddress_Form(NPChar)+", you can't do that! I have surrendered.";
            link.l1 = "Shut your mouth! ... Bind him.";
			link.l1.go = "Slave_2";
			link.l99 = "Alright. Stay here until I decide...";
			link.l99.go = "exit";
		break;
		
		case "Slave_2":
			OfficersReaction("bad");		
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
            if (rand(5) == 1)
            {
    			dialog.text = "No way! I'd sooner die than become a slave!";
                link.l1 = "Stop that! That's an order!... Boatswain! Clean the cargo...";
    			link.l1.go = "free_in_sea_4";
			}			
			else
			{
                if (rand(1) == 1)
                {
                    if (GetPrisonerQty() > 1)
                    {
                        dialog.text = "Butcher! Guys, join me, we've got nothing to lose!";
                        link.l1 = "Wrong choice, ladies. I deal with mutinies myself, and I do it very quickly...";
            			link.l1.go = "free_in_sea_battle_all";
                    }
					else
					{
						dialog.text = "No way! I'd rather die in a fight!";
						link.l1 = "As you wish...";
						link.l1.go = "free_in_sea_battle_1";
					}	
    			}
    			else
    			{
					dialog.text = "Oh, I agree. I've got no choice.";
                    link.l1 = "Splendid. It's better to be a living slave than a dead hero.";
        			link.l1.go = "Slave_3";				
    			}			
			}
		break;

		case "Slave_3":
            ReleasePrisoner(NPChar); //  пленника в рабы
        	LAi_SetActorType(NPChar);
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
        	ChangeCharacterComplexReputation(pchar,"nobility", -6);
        	DialogExit();
        	AddCharacterGoodsSimple(pchar, GOOD_SLAVES, 1);
        break;

		case "free_withoutFee":
			dialog.text = "Oh, "+GetAddress_Form(NPChar)+", are you truly that kind, releasing me without demanding a ransom?";
            link.l1 = "Yes, I am. You are free now,"+GetFullName(NPChar);
			link.l1.go = "free_withoutFee_2";
			link.l99 = "Hm... You have a point! I need more time to decide.";
			link.l99.go = "exit";
		break;

		case "free_withoutFee_2":
			dialog.text = "Thank you, "+GetFullName(PChar)+"! I will pray for you.";
            link.l1 = "Go now, and try to stay alive, otherwise my generosity will be in vain.";
			link.l1.go = "free_withoutFee_3";
			OfficersReaction("good");
		break;
		
		case "free_withoutFee_3":
            ReleasePrisoner(NPChar); // освободили пленника
        	LAi_SetActorType(NPChar);
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
        	ChangeCharacterComplexReputation(pchar,"nobility", 2);
        	DialogExit();
        break;	

		case "free_withoutFee_4":	
			switch(NPChar.EncType)
			{
				case "pirate":
					dialog.text = RandPhraseSimple("Thank you, captain. I will never forget your kindness. I'm going to leave this job and repair small boats in peaceful harbours. I can do that.","Thank you, captain! I swear, I will give up this ungrateful occupation and become a fisherman.");
					link.l1 = "If you are being honest then I wish you luck, and if not then pray you never meet me again...";	
				break;
				case "trade":
					dialog.text = "Don't even know how to thank you, captain. I had already lost hope. I'll tell everyone about your kindness. I give you my word, I'll light a candle for you! Just let me get to a church.";
					link.l1 = "Farewell. And next time, don't even think about resisting. Fire at me, and it will be a death sentence for you and your crew.";
				break;
				case "war":
					dialog.text = "My thanks, captain. I will pray for you.";
					link.l1 = "Good luck, and remember, if you decide to hunt me, it will be your end.";
				break;
			}
			link.l1.go = "free_withoutFee_3";
		break;
		
		case "free_in_sea_battle_1":
            ReleasePrisoner(NPChar); // освободили пленника        	
        	LAi_LocationFightDisable(&Locations[FindLocation("My_Deck")], false);
            LAi_SetFightMode(Pchar, true);
            LAi_SetWarriorType(NPChar);
            LAi_group_MoveCharacter(NPChar, LAI_GROUP_TmpEnemy);
            LAi_group_SetHearRadius(LAI_GROUP_TmpEnemy, 100.0);
            LAi_group_FightGroupsEx(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
            LAi_group_SetRelation(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_SetCheck(LAI_GROUP_TmpEnemy, "My_Deck_Battle_End");
            LAi_group_SetRelation(LAI_GROUP_TmpEnemy, "Prisoner", LAI_GROUP_NEITRAL);
        	DialogExit();
        break;		

		case "free_in_sea_battle_all":
			//ugeen --> привет Сиварду !!! после релиза пленников кол-во пассажиров уменьшается и цикл нихрена дальше не срабатывал
			for(int j = GetPassengersQuantity(pchar) - 1; j > -1; j--)
            {
                cn = GetPassenger(pchar, j);
                if(cn != -1)
                {
                    offref = GetCharacter(cn);
                    if (CheckAttribute(offref,"prisoned"))
                    {
        	            if(sti(offref.prisoned)==true && GetRemovable(offref)) // ставим только фантомов
        	            {
                        	ReleasePrisoner(offref); // освободили пленника
							LAi_SetWarriorType(offref);
							LAi_warrior_DialogEnable(offref, false);
                            LAi_group_MoveCharacter(offref, LAI_GROUP_TmpEnemy);
                        }
                    }
                }
            }
            LAi_LocationFightDisable(&Locations[FindLocation("My_Deck")], false);
            LAi_SetFightMode(Pchar, true);
			LAi_group_SetHearRadius(LAI_GROUP_TmpEnemy, 100.0);
            LAi_group_FightGroupsEx(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
            LAi_group_SetRelation(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_SetCheck(LAI_GROUP_TmpEnemy, "My_Deck_Battle_End");
        	DialogExit();
        break;
		
		case "free_in_sea_4":
        	ReleasePrisoner(NPChar); // освободили пленника
            NPChar.location = "";
	        LAi_KillCharacter(NPChar);
        	DialogExit();
        break;

		case "PunishmentAction":
			dialog.text = "But "+GetAddress_Form(NPChar)+", you can't do that! I've surrendered.";
			link.l1 = "Only after your men were gone. You betrayed them... Boatswain! Take him.";
			link.l1.go = "PunishmentAction1";
			link.l2 = "Well... I need time to think it over. Stay here.";
			link.l2.go = "exit";
        break;

		case "PunishmentAction1":
			OfficersReaction("bad");		
			ChangeCharacterComplexReputation(pchar,"nobility", -2);			
			AddCharacterExpToSkill(Pchar, "Leadership", -150);
			if (rand(1) == 1)
            {
                if (GetPrisonerQty() > 1)
                {
                    dialog.text = "Butcher! Guys, we've got nothing to lose!";
                    link.l1 = "Wrong choice, ladies. I deal with mutinies myself, and I do it very quickly...";
					link.l1.go = "free_in_sea_battle_all";
                }
				else
				{
					dialog.text = "No way! I'd rather die in a fight!";
					link.l1 = "As you wish...";
					link.l1.go = "free_in_sea_battle_1";
				}	
    		}
			else
    		{
				dialog.text = "At least give me some time to pray...";
                link.l1 = "Pray, if you wish.";
        		link.l1.go = "PunishmentAction2";				
    		}						
		break;
		
		case "PunishmentAction2":
        	ReleasePrisoner(NPChar); // освободили пленника
            NPChar.location = "";		
			NPChar.LifeDay = 0;
			LAi_CharacterDisableDialog(NPChar);
			DialogExit();
		break;
		
		case "free_tip_off":
			dialog.text = "I have some interesting information that could be useful to a man like you. But I need your guarantee that I will gain my freedom in exchange.";
			link.l1 = "How can I give you any guarantees if I don't even know your proposal? I doubt your information will be of any use to me.";
			link.l1.go = "free_tip_off_0";
			link.l2 = "I can only give you my word.";
			link.l2.go = "free_tip_off_1";
		break;
		
		case "free_tip_off_0":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);			
			DeleteAttribute(NPChar, "Hold_GenQuest");
			DialogExit();
		break;
		
		case "free_tip_off_1":
			switch(NPChar.EncType)
			{
				case "trade":
					sTmp = "He proposed me a freight but this guy was too greedy and I rejected the offer.";  
				break;
				case "war":
					sTmp = "I have escorted him a few times as a commander of a convoy.";
				break;
				case "pirate":
					sTmp = "I had an idea to rob him once but I have never had a single chance to do that.";
				break;
			}
			dialog.text = "Fine. That's enough for me. Now, straight to business, in "+XI_ConvertString("Colony"+NPChar.Hold_GenQuest.City+"Voc")+" is home to a wealthy merchant "+NPChar.Hold_GenQuest.Name+". "+"He made his fortune on his ship '"+NPChar.Hold_GenQuest.ShipName+" selling "+GetStrSmallRegister(XI_ConvertString(Goods[sti(NPChar.Hold_GenQuest.Goods)].Name+"Acc"))+" with route : "+XI_ConvertString("Colony"+NPChar.Hold_GenQuest.FromCity)+" - "+XI_ConvertString("Colony"+NPChar.Hold_GenQuest.ToCity)+". "+"When he has too much cargo he pays for an escort."+sTmp+" I am sure that this information is more valuable to you than the life of a single man.";
			link.l1 = "I doubt this information will be useful to me. I won't hunt peaceful traders.";	
			link.l1.go = "free_tip_off_0";
			link.l2 = "Not sure if this information will be of any use to me, but I have given you my word. The boatswain will place you with my crew and release you at the nearest harbour.";
			link.l2.go = "free_tip_off_2";			
		break;
		
		case "free_tip_off_2":
			dialog.text = "My thanks, captain! I had no doubt about your honesty!";
			link.l1 = RandPhraseSimple(RandPhraseSimple("I wish I could say the same about you","Sorry, but I can't say the same about you."),RandPhraseSimple("Go, and remember that next time I won't be so generous.","Go and stay out of my way. Next time I won't believe you so easily."));
			link.l1.go = "free_tip_off_3";
		break;
		
		case "free_tip_off_3":
			pchar.GenQuest.Hold_GenQuest.Goods 			= NPChar.Hold_GenQuest.Goods;			
			pchar.GenQuest.Hold_GenQuest.Nation 		= NPChar.Hold_GenQuest.Nation; 
			pchar.GenQuest.Hold_GenQuest.Name 			= NPChar.Hold_GenQuest.Name;
			pchar.GenQuest.Hold_GenQuest.ToCity 		= NPChar.Hold_GenQuest.ToCity;
			pchar.GenQuest.Hold_GenQuest.FromCity 		= NPChar.Hold_GenQuest.FromCity; 
			pchar.GenQuest.Hold_GenQuest.ShipName 		= NPChar.Hold_GenQuest.ShipName;				
			pchar.GenQuest.Hold_GenQuest.City 			= NPChar.Hold_GenQuest.City;
			pchar.GenQuest.Hold_GenQuest.CapName		= GetFullName(NPChar);
			pchar.GenQuest.Hold_GenQuest.Island			= GetArealByCityName(pchar.GenQuest.Hold_GenQuest.City); 
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern 	= true;
			
			ReOpenQuestHeader("HoldQuest");
			AddQuestRecord("HoldQuest", "1");
			AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.Hold_GenQuest.Goods)].Name + "Acc"))); 
			AddQuestUserData("HoldQuest", "sCityFrom", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.FromCity));
			AddQuestUserData("HoldQuest", "sCityTo", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.ToCity));
			AddQuestUserData("HoldQuest", "sShipName", pchar.GenQuest.Hold_GenQuest.ShipName);
			
			SetFunctionTimerCondition("Hold_GenQuest_SetMerchant_pre", 0, 0, 1+rand(2), false);
			SetFunctionTimerCondition("Hold_GenQuest_MerchantOver", 0, 0, 30, false);
			
            ReleasePrisoner(NPChar); // освободили пленника
        	LAi_SetActorType(NPChar);
			NPChar.LifeDay = 0;
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
        	DialogExit();			
		break;
	
		case "free_buyout":
			dialog.text = "And I have a proposal for you. In "+XI_ConvertString("Colony"+NPChar.Hold_GenQuest.City+"Voc")+" lives, my friend, "+NPChar.Hold_GenQuest.Name+" is his name. We once had a business together."+"Find him there. I am sure that he'll pay you a great sum. He owes me, and I'll deal with him myself.";
			link.l1 = "Your friend, huh? Let's see him.";	
			link.l1.go = "free_buyout1";
			link.l2 = "Why should I look for your friend if I can get a ransom in the very first harbour?";
			link.l2.go = "free_tip_off_0";
		break;
	
		case "free_buyout1":
			LAi_CharacterDisableDialog(NPChar);
			
			pchar.GenQuest.Hold_GenQuest.City 		= NPChar.Hold_GenQuest.City;			
			pchar.GenQuest.Hold_GenQuest.Nation 	= NPChar.Hold_GenQuest.Nation;
			pchar.GenQuest.Hold_GenQuest.Name 		= NPChar.Hold_GenQuest.Name;
			pchar.GenQuest.Hold_GenQuest.CapName	= GetFullName(NPChar);
			pchar.GenQuest.Hold_GenQuest.CapId		= NPChar.Id;
			pchar.GenQuest.Hold_GenQuest.TavernVariant = rand(1);
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern = false;
			
			ReOpenQuestHeader("HoldQuest");
			AddQuestRecord("HoldQuest", "6");
			AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.City + "Voc")); 
			AddQuestUserData("HoldQuest", "sNameChar", NPChar.Hold_GenQuest.Name);
			DialogExit();
		break;

		case "free_by_hoard":
			dialog.text = "Actually, I know a man who has a fine treasure, but he doesn't have the guts to use it.";
			link.l1 = "What do you mean?";
			link.l1.go = "free_by_hoard1";
			link.l2 = "Spare me your stories. You'd better worry about your soul.";
			link.l2.go = "free_tip_off_0";
		break;
		
		case "free_by_hoard1":
			dialog.text = "I'm telling you a story that leads to great treasure. I need your word in return that you'll let me go at the next harbour.";
			link.l1 = "I will decide when and what to do with you myself. Your 'stories' won't make a difference.";
			link.l1.go = "free_tip_off_0";
			link.l2 = "I am listening. You have my word.";
			link.l2.go = "free_by_hoard2";
		break;
		
		case "free_by_hoard2":
			dialog.text = "I trust such an honourable "+GetSexPhrase("man","woman")+". People like you always keep your word! It doesn't matter if the whole world is burning, you will keep your word! Am I right, captain?";
			link.l1 = "Tell me your story, or I'll let you go right now... overboard and headless.";
			link.l1.go = "free_by_hoard4";
		break;
		
		case "free_by_hoard4":
			dialog.text = "Ha-ha, nice joke... Now listen. There's a fellow in "+XI_ConvertString("Colony"+NPChar.Hold_GenQuest.City+"Voc")+" named "+NPChar.Hold_GenQuest.Name+", he was quite a reckless fellow in his youth. He had a lot of 'deals' in those days..."+"So once in the tavern he told me that he was a member of "+GetName(NAMETYPE_VIP,NPChar.Hold_GenQuest.PirateName,NAME_ACC)+" gang and he saw how those pirates were burying a treasure."+" He had five of his mates killed over that treasure... There were rumours that he got caught and hanged, but the truth is that he withdrew from business, and so he started a family. He remembered the location of the treasure, even drew a map. He offered me to accompany him in finding the treasure. A superstitious man, he believed the treasure was covered in blood, so he feared to go there alone. I admit, I didn't venture either for the same reason. "+"He was ready to sell the map, but why would I need it if I would never go there anyway...\nThat's my story... I think that a brave man like you will find it useful, and the map is quite cheap, by the way.";
			link.l1 = "And do you really expect me to buy that? Your story isn't real, so I'm breaking our deal.";
			link.l1.go = "free_tip_off_0";
			link.l2 = "Interesting story, though I don't really believe it. But you have my word, go and tell the boatswain to give you a locker. You are free.";
			link.l2.go = "free_by_hoard5";
		break;
		
		case "free_by_hoard5":
			dialog.text = "My thanks, captain! Now I see the price of a man's word "+GetSexPhrase("gentleman!","lady!");
			link.l1 = "Go and stay out of my way. Next time I won't let you off so easily.");
			link.l1.go = "free_by_hoard6";
		break;
		
		case "free_by_hoard6":
			pchar.GenQuest.Hold_GenQuest.City 		= NPChar.Hold_GenQuest.City;			
			pchar.GenQuest.Hold_GenQuest.Nation 	= NPChar.Hold_GenQuest.Nation;
			pchar.GenQuest.Hold_GenQuest.Name 		= NPChar.Hold_GenQuest.Name;
			pchar.GenQuest.Hold_GenQuest.PirateName	= NPChar.Hold_GenQuest.PirateName;
			pchar.GenQuest.Hold_GenQuest.CapName	= GetFullName(NPChar);
			pchar.GenQuest.Hold_GenQuest.TavernVariant = rand(1) + 2;
			pchar.GenQuest.Hold_GenQuest.Sum		= 10000 + rand(10000);
			pchar.GenQuest.Hold_GenQuest.Treasure	= rand(1);
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern = false;
			
			ReOpenQuestHeader("HoldQuest");
			AddQuestRecord("HoldQuest", "12");
			AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.City + "Voc")); 
			AddQuestUserData("HoldQuest", "sNameChar", pchar.GenQuest.Hold_GenQuest.Name);
			AddQuestUserData("HoldQuest", "sPirateName", GetName( NAMETYPE_VIP, pchar.GenQuest.Hold_GenQuest.PirateName, NAME_ACC));
			
            ReleasePrisoner(NPChar); // освободили пленника
        	LAi_SetActorType(NPChar);
			NPChar.LifeDay = 0;
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
        	DialogExit();					
		break;
		
		case "free_in_sea":
			dialog.text = "But, "+GetAddress_Form(NPChar)+", we are on the open sea! It's the same as if you executed me!";
			link.l1 = "That's what you wanted. Farewell. The boatswain will carry out my order.";
			link.l1.go = "PunishmentAction1";
			link.l2 = "Alright, I haven't decided yet.";
			link.l2.go = "exit";
		break;		
		
		//--> Jason, Ложный след
		case "FalseTrace_Prisoner":
			dialog.text = "Katerine! She really asked you to come here? Such a wonderful girl...";
			link.l1 = "Let's leave poetry aside, captain, and talk about more serious matters. I'm going to tell you about the current situation, and I expect an answer from you. Your answer will determine both your fate and Katerine's.";
			link.l1.go = "FalseTrace_Prisoner_1";
		break;
		
		case "FalseTrace_Prisoner_1":
			dialog.text = "I am listening, captain.";
			link.l1 = "I have boarded your fluyt because Adam Rayner, Katerin's husband, told me there was a lot of silver on your ship. This trick allowed him to take back a woman who once belonged to him, and who escaped from him to you.";
			link.l1.go = "FalseTrace_Prisoner_2";
		break;
		
		case "FalseTrace_Prisoner_2":
			dialog.text = "Adam? That bastard? It was all his plan! Now I see... Yes, I helped Katrine escape three months ago. Such a poor girl, you have no idea how he treated her...";
			link.l1 = "She was his wife and I couldn't care less about what happened, it's none of my business. I made a mistake boarding your fluyt but it's too late to talk about it. Adam has promised to pay me for my help.";
			link.l1.go = "FalseTrace_Prisoner_3";
		break;
		
		case "FalseTrace_Prisoner_3":
			dialog.text = "Adam made a promise? Ha-ha! And you trusted him? Captain, do you even know what kind of person he is? He...";
			link.l1 = "Katerine has already told me a lot about him and put a great effort into that. But his proposal makes sense, and though I have no reason to trust this bastard, maybe this time he is telling the truth. So let's get straight to the point...";
			link.l1.go = "FalseTrace_Prisoner_4";
		break;
		
		case "FalseTrace_Prisoner_4":
			dialog.text = "";
			link.l1 = "I was going to ransom you to the authorities and deliver Adam and Katerine to "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Acc")+", then get from Adam the information about Squint-Eyed Solly's gold and sail to it. But Katerine persuaded me to speak with you first; she said you might offer me something better and more reliable than Adam did, in exchange for your lives and freedom.";
			link.l1.go = "FalseTrace_Prisoner_5";
		break;
		
		case "FalseTrace_Prisoner_5":
			dialog.text = "";
			link.l1 = "That's why I am standing here and talking to you. I have finished. Now it is your turn. Think about my words and Katerine's words, and give me your thoughts. You don't have much time.";
			link.l1.go = "FalseTrace_Prisoner_6";
		break;
		
		case "FalseTrace_Prisoner_6":
			dialog.text = "Captain! Though I don't think you are a good man, you did listen to the pleas of a poor girl and you came here. It shows me that you can be honourable and feel pity. I don't need time, I am ready to give you my proposal.";
			link.l1 = "Really? Excellent! Well then, I am listening.";
			link.l1.go = "FalseTrace_Prisoner_7";
		break;
		
		case "FalseTrace_Prisoner_7":
			dialog.text = "You will arrest Adam Rayner and put him in chains. Then you will take me and Katherine to "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity)+". Don't land in the city, after all, it was you who sank my fluyt, drop all three of us at "+XI_ConvertString(pchar.questTemp.FalseTrace.TargetShore+"Gen")+"\nI would also ask you for a weapon. We will go to the city through the jungle, and I'll make sure that the scum pays not only for his crimes but for yours as well. He deserves it\nYou have my word that your name won't come up. In return, I will give you true information concerning a ship carrying the gold of an enemy state\nIt won't be a great challenge for you, but it does have teeth; you will gain a fine booty. Much better than my ransom and the so-called Squint-Eyed Solly's treasures. Do we have a deal?";
			link.l1 = "I don't like your plan. I think the local authorities will organize a hunt for me as soon as I leave the shores of "+XI_ConvertString(pchar.questTemp.FalseTrace.TargetShore+"Gen")+". No, captain, I'm not going to risk my neck. Our conversation is over.";
			link.l1.go = "FalseTrace_Prisoner_8";
			link.l2 = "Well, it looks like Katerine was right. I like your proposal. Adam Rayner will be arrested. I'll have it done right now. You will be released after we arrest Adam. See you, captain!";
			link.l2.go = "FalseTrace_Prisoner_9";
		break;
		
		case "FalseTrace_Prisoner_8":
			DialogExit();
			AddQuestRecord("FalseTrace", "9");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
			AddDialogExitQuestFunction("SetCheckForSolly");
			bQuestDisableMapEnter = false;
			LAi_CharacterDisableDialog(npchar);
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
		break;
		
		case "FalseTrace_Prisoner_9":
			DialogExit();
			AddQuestRecord("FalseTrace", "10");
			pchar.quest.FalseTraceSollyOver.over = "yes"; //снять таймер
			AddDialogExitQuestFunction("SetCheckForGoldShip");
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.FalseTrace.PrisonerID = npchar.id;
			Pchar.questTemp.FalseTrace.PrisonerIDX = GetCharacterIndex(npchar.id);
		break;
		//<-- Ложный след
		
		// Addon-2016 Jason ФМК-Гваделупа
		case "FMQG":
			dialog.text = "Are you here to preach or to do business?";
			link.l1 = "To do business. I need your partner in crime - Bertrand Pinette. I'm in deep trouble because of him. Where can I find him, huh?";
			link.l1.go = "FMQG_1";
		break;
		
		case "FMQG_1":
			dialog.text = "Why do you think I would tell you this?";
			link.l1 = "It's your neck on the line. I will take you to Basse-Terre, deliver you to the governor, and claim the reward for capturing a deserter who aided Carlos de Milyar's escape. It's your choice. Either you tell me where Pinette is, or we both head to Guadeloupe.";
			link.l1.go = "FMQG_2";
		break;
		
		case "FMQG_2":
			dialog.text = "So you know everything... Fine, I'll tell you everything I know about Bertrand Pinette, but you must set me free in return.";
			link.l1 = "Go on, tell me then. I will land you in Mosquito Bay, just as I did last time. But if you lie to me, I will return and set that plantation you were gifted by Don Carlos on fire. I will also inform Basse-Terre of your whereabouts, so I won't be the only one hunting you.";
			link.l1.go = "FMQG_3";
		break;
		
		case "FMQG_3":
			dialog.text = "First, land me there. That will make me feel safer, and I swear I'll tell you everything.";
			link.l1 = "Fine. It's not like you're going anywhere.";
			link.l1.go = "FMQG_4";
		break;
		
		case "FMQG_4":
			DialogExit();
			AddQuestRecord("FMQ_Guadeloupe", "16");
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.FMQG.PrisonerID = npchar.id;
			Pchar.questTemp.FMQG.PrisonerIDX = GetCharacterIndex(npchar.id);
			pchar.quest.FMQG_SailMoskitos.win_condition.l1 = "location";
			pchar.quest.FMQG_SailMoskitos.win_condition.l1.location = "Shore47";
			pchar.quest.FMQG_SailMoskitos.function = "FMQG_ArriveMoskitos";
			pchar.questTemp.FMQG = "to_moskitos";
			AddMapQuestMarkShore("Shore47", true);
			bDisableMapEnter = false; // Rebbebion, теперь можно
		break;
		
		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
	}
}

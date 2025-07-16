// Чарли Книппель - старый артиллерист
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i, iTemp, amount;
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
		//ветка на взятие 2 варианта прохождения - за Англию
		if(CheckAttribute(pchar, "questTemp.HWIC.CanTake") && !CheckAttribute(pchar, "questTemp.HWIC.CanTake.Eng") && !CheckAttribute(npchar, "quest.HWICTake") && !CheckAttribute(pchar, "questTemp.HWIC.Holl") && !CheckAttribute(pchar, "questTemp.HWIC.Self"))
		{
			dialog.text = "Ahoy matey, chain shot my arse! What brings you here?";
			link.l1 = "Chain shot your...what? Oh nevermind, just wanted to say hello.";
			link.l1.go = "exit";
			link.l2 = "Greetings, Mr. Knippel. Ha, I see why they call you Knippel. Anyway, there are rumors that you used to serve with the English Navy. I have a fine ship and skilled crew. I'd like to offer me and my ship to the service of the English Crown...er...Commonwealth. Can you give me some advice or recommend me to someone or, perhaps, to help me in that matter?";
			link.l2.go = "Knippel_check";
			break;
		}
		//за Голландию
		if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
		{
			if (pchar.questTemp.HWIC.Holl == "toKnippel")
			{
				dialog.text = "Ahoymatey, chain shot my arse! What brings you here?";
				link.l1 = "Greetings, Mr. Knippel. Ha, I see why they call you Knippel. There are rumors that you used to serve in the English Navy, that is why I want to ask you for help...";
				link.l1.go = "Dominica";
				DelLandQuestMark(npchar);
				break;
			}
			dialog.text = "Chain shot my arse! What do you want, matey?";
			link.l1 = "No, it's nothing. I'm leaving.";
			link.l1.go = "exit";
			break;
		}
		//за Англию
		if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
		{
			if (pchar.questTemp.HWIC.Eng == "TakeHollConvoy")
			{
				dialog.text = "Ahoy cap'n, I've heard some rumors about a silver convoy getting intercepted...";
				link.l1 = "You're well informed, Mr. Knippel.";
				link.l1.go = "HollConvoy_Check";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("SentJons");
				break;
			}
			if (pchar.questTemp.HWIC.Eng == "Wait")
			{
				dialog.text = "Questions, cap'n?";
				link.l1 = "No, it's nothing. I'm leaving.";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Eng == "Start_main")
			{
				dialog.text = "I am glad to see you, cap'n! My commander Richard Fleetwood was going to come here to get know you himself, but an accident happened yesterday evening... Someone tried to kill him right in the middle of the street, chain shot my arse!";
				link.l1 = "Impossible! What were the guards doing?";
				link.l1.go = "Fleetwood_house";
				DelLandQuestMark(npchar);
				break;
			}
			dialog.text = "Questions, cap'n?";
			link.l1 = "No, it's nothing. I'm leaving.";
			link.l1.go = "exit";
		break;
		}
			dialog.text = "Ahoy matey, chain shot my arse! What brought you here?";
			link.l1 = "Hello, just stopping by.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

//-------------------------------------------за Голландию--------------------------------------------------	
		case "Dominica":
			dialog.text = "Ahoy, is that so? And how can an old sailor grounded long ago help you matey?";
			link.l1 = "See... I am just a common captain and I do regular voyages between Martinique and Curacao. So I have been attacked twice by the ghost ship not far from Martinique... Here's the thing though, she is no Fata Morgana or Flying Dutchman. I was able to tear her sails with simple cannonballs!";
			link.l1.go = "Dominica_1";			
		break;
		
		case "Dominica_1":
			dialog.text = "Is that so? That is certainly unlike a ghost ship to lose canvas to solid shot, shiver me timbers...";
			link.l1 = "We survived only because my ship could outrun it sailing close hauled to the wind. Last time I had to toss all my cargo overboard to lighten my hull enough to escape... can you imagine the loss? It's heartbreaking!";
			link.l1.go = "Dominica_2";			
		break;
		
		case "Dominica_2":
			dialog.text = "Blow me down, cap'n...";
			link.l1 = "Mathias Beck, the governor of Curacao, just brushed my complaints aside. He said that the tales of the ghost ship are nonsense and my watchmen were drunk on grog. The governor of Martinique promised to send a patrol there, but his eyes told me that he can't be bothered to do a thing.  I can't return to Martinique while that bastard pirate 'ghost' is prowling around. My ship is small as is my crew, it is likely that we won't survive the third encounter we have with him...";
			link.l1.go = "Dominica_3";			
		break;
		
		case "Dominica_3":
			dialog.text = "Tis a crying shame, matey. But how can I help you?";
			link.l1 = "I heard from the sailors around here that there was one captain here in St. John's named Richard Fleetwood who has hunted this same ghost ship. I don't know him personally, that is why I tell this story to you, perhaps you could pass on to him the story of my misfortunes? I am sure that the filthy pirate is hiding somewhere near the wild shores of Dominica and raiding between Barbados and Martinique.";
			link.l1.go = "Dominica_4";			
		break;
		
		case "Dominica_4":
			dialog.text = "Between Barbados and Martinique? Ya har! A fat and rich trade lane. It sounds very much like something that bilgerat would do.";
			link.l1 = "I am not rich or fat, and I don't have money to bribe a naval captain for a military escort. But, if Sir Fleetwood is hunting for this bilgerat already, could you please tell him where he could find this 'Flying Dutchman'?";
			link.l1.go = "Dominica_5";			
		break;
		
		case "Dominica_5":
			dialog.text = "You have done a good thing by coming here, matey. I will tell your story to the right men, chain shot my liver! Soon, you will be able to trade with Martinique again.";
			link.l1 = "I hope that God will hear your words! Thank you for listening to me, Charlie. I do hope for the best. Farewell and and dodge the chain shot!";
			link.l1.go = "Dominica_6";			
		break;
		
		case "Dominica_6":
			DialogExit();	
			pchar.questTemp.HWIC.Holl = "toDominica";
			AddQuestRecord("Holl_Gambit", "1-17");
			pchar.quest.toDominica.win_condition.l1 = "location";
			pchar.quest.toDominica.win_condition.l1.location = "Dominica";
			pchar.quest.toDominica.function = "PrepareToFleetwoodAttack";
			DelMapQuestMarkShore("Shore1");
			DelMapQuestMarkShore("Shore2");
			AddMapQuestMarkIsland("Dominica", true);
		break;

//----------------------------------------------за Англию--------------------------------------------------	
		case "Knippel_check"://начинаем проверять нашего ГГ по всем статьям
			if(makeint(PChar.reputation.nobility) < 48)//низкая репа
			{
				// belamour legendary edition покажем критерии
				notification("Reputation Too Low! (Adventurer)", "None");
				PlaySound("Voice\English\hambit\Charlie Knippel-04.wav");
				dialog.text = "Merry Old England don't need services from rogues, chain shot my arse! Respectfully, you can fuck right off.";
				link.l1 = "Hey hey mate, watch your mouth or I'll sew it shut!";
				link.l1.go = "exit";
				break;
			}
			else
			{
				notification("Reputation Check Passed", "None");
			}
			if(GetSummonSkillFromName(pchar, SKILL_SAILING) < 30)//низкая навигация
			{
				dialog.text = "Cap'n, I'll be blunt. You couldn't sail your way out of a wet sack. Come back when you will have more skills in navigating, savvy?";
				// belamour legendary edition покажем критерии  -->
				notification("Skill Check Failed (30)", SKILL_SAILING);
				//<--
				dialog.text = "Cao'n, our fleet needs experienced captains, not lubbers. Come back when you've mastered the art of navigation.";							 
				link.l1 = "I see... Then I will see you later.";
				link.l1.go = "exit";
				break;
			}
			else
			{
				notification("Skill Check Passed", SKILL_SAILING);
			}
			dialog.text = "Ahoy, you are just in time, cap'n, chain shot my arse! Richard didn't know who he could rely upon for this risky business, he was even considering declining it... So the little birds of opportunity are singing sweetly in your ears today. If you perform up to our standards then I will recommend you to a certain very important man. Do you have enough buckshot in your codpiece to handle it?";
			link.l1 = "I'm loaded with grapeshot, Mr. Knippel.";
			link.l1.go = "Knippel_task";
		break;
		
		case "Knippel_task"://первое задание
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("Bridgetown_tavernkeeper"));
			DelLandQuestMark(characterFromId("Lucas"));
			DelMapQuestMarkCity("Bridgetown");
			DelMapQuestMarkCity("Villemstad");
			DelMapQuestMarkCity("SentJons");
			dialog.text = "Ar har! I see your cock is up, cap'n! Soon flashing fire will follow! Now listen closely. The Dutch West India Company's silver fleet left Willemstad on Curacao one or two days ago. It is sailing to Philipsburg. There are only a few ships in the fleet this time around. A single Galleon with the silver in her cargo hold along with two escorts. Intercept the silver fleet, capture the East Galleon with the silver cargo and bring her to Antigua. You can sink the escorts though, they're expendable. Chain shot their livers, yar!";
			link.l1 = "Their days are numbered.";
			link.l1.go = "Knippel_task_1";
			DelLandQuestMark(npchar);
		break;
		
		case "Knippel_task_1":
			dialog.text = "Some advice, cap'n. The trade lane from Curacao to Sint Maarten lies not far from the shores of St. Christopher. I would advise preparing an ambush there. Prepare you and your ship well for this engagement. Tangling with the West India Company is not a walk in the park with a pretty girl.";
			link.l1 = "I know what I'm getting into, but I appreciate your candor, Mr. Knippel. I'll be back with the Dutch silver.";
			link.l1.go = "Knippel_task_2";			
		break;
		
		case "Knippel_task_2":
			DialogExit();
			npchar.quest.HWICTake = "true";
			pchar.questTemp.HWIC.CanTake.Eng = "true";//признак, что английка уже бралась
			HWICSilverConvoyInWorld();
			AddQuestRecord("Holl_Gambit", "2-1");
			ReOpenQuestHeader("Holl_Gambit"); // данила ,чтобы вышел из архива. 																				   
			pchar.questTemp.HWIC.Eng = "begin";
			SetFunctionTimerCondition("HollConvoy_Over", 0, 0, 15, false);
		break;
		
		case "HollConvoy_Check"://начинаем проверять
			int iHal = 0;
			for(i = 0; i < COMPANION_MAX; i++)
			{
				iTemp = GetCompanionIndex(PChar, i);
				if(iTemp > 0)
				{
					sld = GetCharacter(iTemp);
					pchar.questTemp.HWIC.Eng.CompanionIndex = sld.Index;
					if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_GALEON_L) iHal++;
				}
			}//признак наличия ТГ в компаньонах
			if (iHal > 0)
			{
				amount = sti(pchar.questTemp.HWIC.Eng.SlvQty) - GetSquadronGoods(pchar, GOOD_SILVER);
				if (amount <= 0)
				{
					dialog.text = "No need to tell me what happened, cap'n. I was informed about everything while the customs agent was inspecting your ship... You've done quite well, cap'n. Most excellent! It didn't sound easy, chain shot my arse!";
					link.l1 = "It's nice to be appreciated.";
					link.l1.go = "HollConvoy_complete";
				}
				else
				{
					dialog.text = "No need to tell me what happened, matey. I was informed about everything while the customs agent was inspecting your ship... You failed to bring back the whole of the silver, chain shot my arse! I know exactly how much silver was on that East Indiaman to the very peso. This mission's purpose was not only to test your battle skills but to test your honesty. You have failed the latter. Get out of my house, swabbie!";
					link.l1 = "To hell with you then, simpleton!";
					link.l1.go = "HollConvoy_fail";
				}
			}
			else
			{
				dialog.text = "Avast, matey. I don't see the Dutch East Indianman in your squadron. I told you to bring her here as a prize. You sold her and tried to keep the money for yourself, eh?";
				link.l1 = "Wait, I was supposed to bring the ship? I thought you only wanted the silver.";
				link.l1.go = "HollConvoy_noShip";
			}
		break;
		
		case "HollConvoy_noShip":
			dialog.text = "No one plays Charlie Knippel for a fool, matey! I clearly remember what I told you and what I didn't. You have broken the terms of our deal and no honest Englishman will work with you, there is no place for scoundrels here. Get out of my house, swabbie!";
			link.l1 = "To hell with you then, simpleton!";
			link.l1.go = "HollConvoy_fail";
		break;
		
		case "HollConvoy_fail":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "2-3");
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.Eng");//зачищаем для возможности отката к голландскому варианту
			pchar.questTemp.HWIC.Fail2 = "true";
		break;
		
		case "HollConvoy_complete":
			dialog.text = "Visit me tomorrow and I will introduce you to my patron. He will offer you some more work worthy of your skills. Plus he will see to your...financial incentive. Cast off!";
			link.l1 = "Very well, Mr. Knippel. I will be here tomorrow.";
			link.l1.go = "exit";
			npchar.greeting = "knippel_2";
			AddDialogExitQuestFunction("HollConvoy_Remove");
			AddQuestRecord("Holl_Gambit", "2-4");
			SetTimerFunction("EnglandGambit_2_ZadanieStart", 0, 0, 1);
			pchar.questTemp.HWIC.Eng = "Wait";
			AddSimpleRumourCity("They say that you captured a Dutch ship filled with silver. Well done! You are a valiant sailor, captain! Godspeed!", "SentJons", 10, 3, "");
		break;
		
		case "Fleetwood_house":
			dialog.text = "I've been asking myself the same thing... Some bastard threw ground pepper in Cap'n Fleetwood's eyes and stabbed him in the chest before Richard even managed to grab his blade. The murderer was hoping to end the cap'n with one thrust, since he didn't have time for another, but he failed. Cap'n Fleetwood always wears a cuirass under his coat\nThe filthy scum, chain shot his liver, managed to flee and go to ground. It looks like he has friends in town. The only detail that the cap'n remembers is that the assassin only has one eye. It won't help us much though, there are plenty of Cyclops like him roaming the docks these days\nRichard has lost a lot of blood and the pepper irritated his eyes horribly so that he is almost blind now...";
			link.l1 = "Ground pepper? That's an expensive way to blind someone. Fleetwood must have really pissed someone off. I am sorry for your captain. Has the search for the attacker turned anything up?";
			link.l1.go = "Fleetwood_house_1";
		break;
		
		case "Fleetwood_house_1":
			dialog.text = "Cap'n Fleetwood's marines have searched the whole town and the local bays, but they didn't find a thing, chain shots their necks! If we failed to find him right after the attack there is no prayer of finding the bastard now. Cap'n Fleetwood has a lot of enemies... But, cap'n, my commander wants to see you anyway despite the accident. He rests now at his house now so let's go to him. Follow me!";
			link.l1 = "Lead on, Mr. Knippel.";
			link.l1.go = "Fleetwood_house_2";
		break;
		
		case "Fleetwood_house_2":
			chrDisableReloadToLocation = true;//закрыть локацию
			bDisableFastReload = true;//закроем быстрый переход
			LocatorReloadEnterDisable("SentJons_town", "reload1_back", true);
			LocatorReloadEnterDisable("SentJons_town", "reload2_back", true);
			LocatorReloadEnterDisable("SentJons_town", "gate_back", true);//чтобы не сбежал
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "SentJons_town", "reload", "houseH1", "OpenTheDoors", -1);
			pchar.quest.Knippel_Outside.win_condition.l1 = "location";
			pchar.quest.Knippel_Outside.win_condition.l1.location = "SentJons_town";
			pchar.quest.Knippel_Outside.function = "Knippel_GoTown";
			LocatorReloadEnterDisable("SentJons_town", "houseSP3", true);
			sld = characterFromId("Fleetwood");
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_houseSP3_room", "goto", "goto1");
			AddLandQuestMark(sld, "questmarkmain");
			pchar.GenQuestBox.SentJons_houseSP3_room = true;
			pchar.GenQuestBox.SentJons_houseSP3_room.box1.money = 110000;
		break;
		
		case "InFleetwoodHouse":
			dialog.text = "Cap'n Fleetwood is upstairs in his room. Go to him, he is waiting for you. I will stay here.";
			link.l1 = "Understood, Mr. Knippel. I am on my way.";
			link.l1.go = "exit";	
		break;
		
		case "Knippel_ToOfficer":
			dialog.text = "Listen cap... Cap'n Fleetwood is safe and in good hands now. I want to help you to take revenge on the bastard that attacked him. I offer you my services as a gunnery officer. I am not so good at fencing, too old for that, but I can knock the topgallants off a merchantman at a thousand paces.";
			link.l1 = "Now that I'd like to see. Welcome aboard, Mr. Knippel!";
			link.l1.go = "Knippel_ToOfficer_1";	
		break;
		
		case "Knippel_ToOfficer_1":
			LocatorReloadEnterDisable("SentJons_town", "reload1_back", false);
			LocatorReloadEnterDisable("SentJons_town", "reload2_back", false);
			LocatorReloadEnterDisable("SentJons_town", "gate_back", false);//откроем локаторы
			//Книппеля - в офицеры
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.HalfImmortal = true;//полубессмертен
			npchar.loyality = 20;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			SetFunctionTimerCondition("GotoBridgetownOver", 0, 0, 30, false);//на все дела - 1 месяц
			AddSimpleRumourCity("They say that Sir Richard Fleetwood himself is indebted in you. You are a very important man in our town, sir", "SentJons", 10, 3, "");
		break;
		
		case "hired":
			dialog.text = "Ahoy cap'n! Need something?";
			link.l1 = "No, nothing.";
			link.l1.go = "exit";
			NextDiag.TempNode = "hired";
		break;
		
		case "MC_GoAway":
			PlaySound("Voice\English\hambit\Charlie Knippel-07.wav");
			if (pchar.questTemp.HWIC.Eng == "MirageFail")
			{
				dialog.text = "You are a complete buffoon, matey, chain shot my arse! You failed to do an elementary task - to capture the 'Mirage' without losing the 'Valkyrie'\nOur crew won't serve under your command any longer. We are sure that Sir Fleetwood will approve our decision, he likes idiots as little as we do.";
				link.l1 = "Fuck you and your master!";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.HWIC.Eng == "GotoBridgetown" || pchar.questTemp.HWIC.Eng == "SeekVanBerg")
			{
				dialog.text = "You are a complete idiot, matey, chain shot my arse! We have wasted too much time solving your personal problems\nOur crew won't serve you any longer. We are sure that Sir Fleetwood will approve our decision, he likes idiots as little as we do.";
				link.l1 = "Fuck you and your master!";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.HWIC.Eng == "VanBergFailInWorld")
			{
				dialog.text = "You are a complete idiot, matey, chain shot my arse! You were told to play a lone merchant on the 'Valkyrie', and what did you do? You scared the pirate off with your flotilla!\nWe are sure that Sir Fleetwood will approve our decision, he likes idiots as little as we do.";
				link.l1 = "Fuck you and your master!";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.HWIC.Eng == "MirageTake")
			{
				dialog.text = "You are a complete idiot, matey, chain shot my arse! Did you decide to waste our time doing anything but capturing the 'Mirage' and sailing to Antigua?\nOur crew won't serve you any longer. We are sure that Sir Fleetwood will approve our decision, he likes idiots as little as we do.";
			link.l1 = "Fuck you and your master!";
			link.l1.go = "exit";
			}
			PChar.quest.Munity = "Deads";
			LAi_LocationFightDisable(&Locations[FindLocation("Ship_deck")], false);
			if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_VALCIRIA)//если сам на Валькирии
			{
				pchar.Ship.Type = GenerateShipExt(SHIP_TARTANE, true, pchar);
				pchar.Ship.name = "Boat";
				SetBaseShipData(pchar);
				SetCrewQuantityOverMax(PChar, 0);
			}
			else
			{
				for(i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if(iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_VALCIRIA)
						{
							pchar.questTemp.HWIC.Eng.CompanionIndex = sld.Index;
							sld = GetCharacter(sti(pchar.questTemp.HWIC.Eng.CompanionIndex));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			LAi_CharacterDisableDialog(npchar);
			LAi_SetImmortal(npchar, true);
			ChangeCharacterAddressGroup(npchar, "SentJons_houseH1", "goto", "goto1");//Книппеля домой
			pchar.questTemp.HWIC.Eng = "end";
			pchar.questTemp.HWIC.Detector = "eng_fail";
			CloseQuestHeader("Holl_Gambit");
		break;
		
		case "OnCuracao":
			pchar.quest.HWICEng_toBarbadosOver.over = "yes";//снять прерывание
			dialog.text = "Greetings, cap'n. Glad to see you!";
			link.l1 = "Greetings, Mr. Knippel. Do you have the money? Give it to me and let's go to Willemstad to fetch Abigail. Will you join me?";
			link.l1.go = "OnCuracao_1";	
		break;
		
		case "OnCuracao_1":
			dialog.text = "Cap'n, listen... There is no need to go anywhere now.";
			link.l1 = "What are talking about? This is nonsense!";
			link.l1.go = "OnCuracao_2";	
		break;
		
		case "OnCuracao_2":
			dialog.text = "I have a letter from Cap'n Fleetwood for you. And the money. But this money is not for Abigail's father, but for you. Two hundred thousand pesos. Read the letter and try to don't judge him too harshly...";
			link.l1 = "What the hell is going on these days?! Another unpleasant surprise? Give me the letter!";
			link.l1.go = "OnCuracao_3";	
		break;
		
		case "OnCuracao_3":
			DialogExit();
			NextDiag.CurrentNode = "OnCuracao_4";
			AddMoneyToCharacter(pchar, 200000);
			LAi_SetCitizenType(npchar);
			npchar.lifeday = 1;//еще денек пусть погуляет по пляжу
			pchar.quest.Holland_ShoreAttack.win_condition.l1 = "location";
			pchar.quest.Holland_ShoreAttack.win_condition.l1.location = "Curacao";
			pchar.quest.Holland_ShoreAttack.function = "CreateHollandShorePatrol";//патруль в прибрежных водах
			LocatorReloadEnterDisable("SentJons_town", "basement1_back", false);//открыть подземелье
			pchar.questTemp.HWIC.Eng = "MerdokMeeteng";
			AddQuestRecordInfo("LetterFromFleetwood", "1");
			AddQuestRecord("Holl_Gambit", "2-23");
			AddLandQuestMark(npchar, "questmarkmain");
		break;
		
		case "OnCuracao_4":
			dialog.text = "Did you read it, cap'n? I'll be frank. I am ashamed of Cap'n Fleetwood and of what he did, chain shot his... ah, fuck this. Rodenburg was enraged when he learnt about Abigail's romance with Richard. Foot patrols are scouring Curacao and there are Company military ships cruising the local waters. We need to get the hell out of here.\n Captain, do you need a gunner? I don't need luxury - just a normal sea ration on a regular basis. I am not so good at fencing, too old for that, but I can knock the topgallants off a merchantman at a thousand paces.";
			link.l1 = "Well damn, I'd like to see you pull that off Mr. Knippel. Welcome to the crew!";
			link.l1.go = "Knippel_hire";
			link.l2 = "I regret helping you English scoundrels in the first place. I don't know now how to get out of this mess. Walk your own road, I had enough of surprises.";
			link.l2.go = "Knippel_exit";
			DelLandQuestMark(npchar);
		break;
		
		case "Knippel_hire":
			DialogExit();
			DeleteAttribute(npchar, "LifeDay");
			npchar.quest.OfficerPrice = sti(pchar.rank)*200;
			npchar.OfficerWantToGo.DontGo = true;
			DeleteAttribute(npchar, "CompanionDisable");//теперь можем и в компаньоны
			DeleteAttribute(npchar, "HalfImmortal");
			npchar.loyality = MAX_LOYALITY;
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
			SetCharacterPerk(npchar, "ShipEscape");
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			LAi_SetImmortal(npchar, false);
			LAi_SetHP(npchar, 120, 120);
			LAi_SetOfficerType(npchar);
			npchar.greeting = "knippel_hire";
			NextDiag.CurrentNode = "Knippel_officer";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			
			//Sinistra - через 2 месяца стартует личный квест Чарли Книппеля "Длинные тени старых грехов"
			SetTimerCondition("DTSG_Start", 0, 0, 60, false);
		break;
		
		case "Knippel_exit":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "none", "", "", "", -1);
		break;
		
//------------------------------------------------против всех-----------------------------------------------
		case "Knippel_abordage":
			dialog.text = "Avast you bilgerat! Why have you attacked this peaceful Dutch ship? I don't have any valuable goods or gold, chain shot my arse!";
			link.l1 = "Dutch ship? Haha! Don't make me laugh, 'Dutchman'. I have attacked your brigantine in order to capture you, dear Charlie. Welcome to my cargo hold. We will have a talk about where to you were sailing and why...";
			link.l1.go = "Knippel_abordage_1";	
		break;
		
		case "Knippel_abordage_1":
			AddQuestRecord("Holl_Gambit", "3-20");
            pchar.quest.Knippel_DieHard.over = "yes";
		    DoQuestCheckDelay("LAi_ReloadBoarding", 1.0);
            DialogExit();
			LAi_SetPlayerType(pchar);
			pchar.questTemp.HWIC.Self = "KnippelPrisoner";
			npchar.lifeday = 0;
			SetFunctionTimerCondition("RemoveKnippelOver", 0, 0, 1, false);//таймер до конца суток, ибо нефиг
		break;
		
		case "Knippel_prisoner":
			DelLandQuestMark(npchar);
			PlaySound("Voice\English\hambit\Charlie Knippel-07.wav");
			dialog.text = "You are a devil, pirate... You'll burn in hell for all your sins! Scre...";
			link.l1 = "Relax, sermonist. You preach like a Puritan. You'd better see to the state of your soul first.";
			link.l1.go = "Knippel_prisoner_1";
		break;
		
		case "Knippel_prisoner_1":
			dialog.text = "What are you planning, scoundrel? What do you want from my commander and from the poor Dutch girl?";
			link.l1 = "It is not your business, Charlie. I don't need you anymore. Get up.";
			link.l1.go = "Knippel_prisoner_2";	
		break;
		
		case "Knippel_prisoner_2":
			dialog.text = "Do you want to kill me? Worthy of such a bastard like you. *spits* Fuck you!";
			link.l1 = "Get up, Charlie. Say your final prayers.";
			link.l1.go = "Knippel_prisoner_3";	
		break;
		
		case "Knippel_prisoner_3":
			DialogExit();
			LAi_SetActorType(pchar);
			sld = characterFromId("KnippelClone");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Ground_StandUp", "Kill_Knippel", 3.5);
			pchar.quest.RemoveKnippelOver.over = "yes";//снять таймер
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Knippel_officer":
			dialog.text = "Ahoy cap'n, chain shot my arse!";
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Mr. Knippel, I am going to the ancient lost Indian city of Tayasal. I will be clear, this is going to be a really dangerous trip and it is also an unusual one - we need to get there through this...magic idol. Will you join me?";
				Link.l4.go = "tieyasal";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Mr. Knippel, give me a full ship report.";
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
				NextDiag.TempNode = "Knippel_officer";// не забыть менять в зависисомости от оффа
				break;
			}
			Link.l1 = "Listen to my orders!";
            Link.l1.go = "stay_follow";
			link.l2 = "It's nothing. Dismissed!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Knippel_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Sink me... The guns are alright, we replace the ones that explode and keep our powder dry and safe. What kind of a report did you expect, Captain? I am an old cannoneer, not a purser. Chain shot my arse, I am the best cannoneer in the Caribbean though, mind you!";
			Link.l1 = "No arguing here, Mr. Knippel, you do know your trade. I will find a purser myself, don't you worry.";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "You want old Charlie to exchange his gun deck for the quarterdeck? Captain, I sink ships, not put up a fight for each peso. And I am positive they will rip me off in the very first colony we try this.";
			link.l1 = "But of course, Mr. Knippel. I should start looking for a proper purser.";
			link.l1.go = "exit";
		break;
		
		//Указания для компаньона 19.02.08 -->/////////////////////////////////////////////////////////////////////////////////////////
		case "Companion_Tasks":
			dialog.Text = "I am listening to you.";
			Link.l1 = "This is about boarding.";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "This is about your ship.";
			Link.l2.go = "Companion_TaskChange";
			if (bBettaTestMode) // Только при бета-тесте
			{
				Link.l3 = "I want you to leave my squadron for a while and seek fortune on your own.";
				Link.l3.go = "CompanionTravel";
			}
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
			Link.l1 = "I would like you not to swap your ship for another one after boarding. Your ship is too valuable.";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "When you are boarding enemy ships, you can take them for yourself, if they happen to be decent.";
			Link.l2.go = "Companion_TaskChangeYes";
			break;

		case "Companion_TaskBoardingNo":
			dialog.Text = "Aye aye!";
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
			dialog.Text = "Aye aye!";
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
			Dialog.Text = "Choosing the type of ammo:";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
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
            dialog.Text = "There is a change of disposition!";
            Link.l1 = "Dismissed.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "There is a change of disposition!";
            Link.l1 = "Dismissed.";
            Link.l1.go = "Exit";
        break;
	//<-- ----------------------------------- офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal":
			dialog.text = "I have become really attached to you during my service, "+pchar.name+", and I don't leave my cap'n in the lurch. I'd follow you through hell if need be. I am with you!";
			link.l1 = "Thank you, Mr. Knippel! I am glad that I was right about you.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "When will we start, chain shot my eyes?";
			link.l1 = "A bit later. We have to prepare ourselves for it.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "22");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("You are a "+ GetSexPhrase("thief, mister! Guards, take him","thief, girl! Guards, take her") +"!!!", "Just look at that! The moment my back was turned, you decided to check my chest! Take the thief!!!", "Guards! Robbery! Take the thief!!!");
			link.l1 = "Damn it!";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}

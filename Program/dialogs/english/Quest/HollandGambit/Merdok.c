// Джон Мердок, он же Йохан ван Мерден, соратник Роденбурга
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;
	int iTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
		if (!CheckAttribute(pchar, "questTemp.HWIC.Self") && LAi_grp_playeralarm > 0)
		{
			dialog.text = "Mister, you've picked a hell of a bad time for a chitchat. The entire garrison is out looking for you. You'd better shove off proper quick...";
			link.l1 = "Don't worry. I won't stay for long.";
			link.l1.go = "exit";
			break;
		}
		// продажа алхимического набора, если провалил гамбит
		if (CheckAttribute(pchar, "questTemp.HWIC.Detector") && !CheckAttribute(npchar, "quest.alchemy"))
		{
			bOk = (findsubstr(pchar.questTemp.HWIC.Detector, "_fail" , 0) != -1) || (pchar.questTemp.HWIC.Detector == "eng_win_half");
			if (bOk)
			{
				dialog.text = "Welcome, captain. Would you be interested in an intriguing offer? ";
				link.l1 = "All sorts of people around here seem to have such offers, and I'm a curious man. What is it? ";
				link.l1.go = "alchemy";
				break;
			}
		}
		// Страж Истины
		if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok1")
		{
			dialog.text = "Good day. Welcome to my apothecary. I have medicines to treat most diseases and infirmities. What can I offer you?";
			link.l1 = "Listen, John, there are rumours that someone is living at your place on the second floor...";
			link.l1.go = "guardoftruth";
			break;
		}
//-----------------------------------------за Голландию------------------------------------------------
		if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
		{
			if (pchar.location.from_sea == "SentJons_town" && pchar.questTemp.HWIC.Holl == "toAntigua")
			{
				dialog.text = "Good day. I am happy to see you in my apothecary. I have medicines to treat most diseases and ailments. What can I offer you?";
				link.l1 = "Hello Mr. Murdock. I am here on behalf of Lucas Rodenburg. He sent me to you to discuss a matter concerning Richard Fleetwood.";
				link.l1.go = "Knippel_exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "toAntigua")
			{
				dialog.text = "Good afternoon. What kind of problem do you have? I have both cough mixture and diarrhea powder!";
				link.l1 = "Hello, Mr. Murdock. I am here on behalf of Lucas Rodenburg. He sent me to you to discuss a matter regarding Richard Fleetwood.";
				link.l1.go = "Knippel";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "KillMerdok")
			{
				dialog.text = "Ahhh, here is Rodenburg's hired dog... Hercule, Longway - would you please come out here?\nKill this man!";
				link.l1 = "Wait, I have a prescription!";
				link.l1.go = "Merdok_fight";
				break;
			}
			dialog.text = "Good afternoon. I am happy to see you in my drugstore. I have medicines to treat most ailments and infirmities. What can I offer you?";
			link.l1 = "Nothing at the moment, thank you. I feel quite well.";
			link.l1.go = "exit";
			break;
		}
//----------------------------------------------за Англию---------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "MerdokMeeteng")
			{
			dialog.text = "Hello, uninvited guest. You do not cover your face with a mask and do not look like a robber. Therefore, I conclude that you need something else from a poor druggist. Perhaps something for diarrhoea?";
			link.l1 = "Hello to you too, Johan van Merden. I bring greetings from Hercule Tonzag. I see you know the name.";
			link.l1.go = "Merdok_talk";
			DelLandQuestMark(npchar);
			break;
			}
//--------------------------------------------против всех--------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				if (pchar.questTemp.HWIC.Self == "HuntFleetwood")
				{
					dialog.text = "Ah, so here you are. Well, have you met Hercule? ";
					link.l1 = "Yes. We've come to an agreement. John, I am going to help Hercule, and I have several questions for you regarding Richard Fleetwood.";
					link.l1.go = "About_Fleetwood";
					break;
				}
				if (GetQuestPastDayParam("questTemp.Wait_Fleetwood") > 6 && pchar.questTemp.HWIC.Self == "WaitFleetwood")
				{
					dialog.text = "Hello! I'm glad to see you, "+pchar.name+"!";
					link.l1 = "Hello, John. Did you find out anything about Fleetwood?";
					link.l1.go = "About_Fleetwood_9";
					pchar.quest.Wait_FleetwoodOver.over = "yes"; //снять таймер
					break;
				}
				if (pchar.questTemp.HWIC.Self == "HWICSelf_fail")
				{
					dialog.text = "You're late. The bird has flown the coop. Charlie Knippel visited Willemstad and brought a girl from there for Richard. Now they're sailing for England with a military squadron in a day or two. Fleetwood's gone, you'll never see him in this life.";
					link.l1 = "Damn it. I'd completely forgotten about Richard and lost track of time. See you.";
					link.l1.go = "About_Fleetwood_17";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileOnShip")
				{
					dialog.text = "Welcome back, "+pchar.name+"! Nothing for you right now. There is no news about Fleetwood, and Charlie Knippel has not returned from Curaçao yet...";
					link.l1 = "And he never will. Neither he nor his brigantine.";
					link.l1.go = "Abigile";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileInHouse")
				{
					dialog.text = "Ah, we have guests! Hello, Charlie! Good afternoon, Miss!";
					link.l1 = "Good afternoon, John! Let me introduce my female companion, Richard's fiancée, the charming Abigail Shneur.";
					link.l1.go = "Abigile_7_1";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileInRoom")
				{
					dialog.text = "Keep your voice down... What are you going to do next?";
					link.l1 = "Next? I'd rather get some sleep, but unfortunately there's no time for that. I'm going to drag Fleetwood out of whatever hole he's hiding in and finish Hercule's job.";
					link.l1.go = "Abigile_9";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "LetterToFleetwood")
				{
					dialog.text = "Are you done writing? Let me see... My God, Charlie, you're a proper madman! Don't you think you've made this a bit too detailed? I mean, the part about Miss Shneur's fingers, ears, and face? You've got a sick talent, that's for sure. Damn me, I'm about to lose my lunch!";
					link.l1 = "I am bluffing, John. I won't kill the girl. I could make her part with her finger... But nothing more. She has nine more, after all.";
					link.l1.go = "Abigile_15";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "FleetwoodAgree")
				{
					dialog.text = "Did it go well? I can see it in your eyes - you did it!";
					link.l1 = "Yes. Fleetwood accepted my terms. The trap's jaws are closing. Now we wait.";
					link.l1.go = "Abigile_23";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "FleetwoodDied")
				{
					dialog.text = "Ah, welcome back, my friend! What can you tell me?";
					link.l1 = "Fleetwood is dead. Everything went according to plan. He arrived at the island, where I had organized an ambush on the beach. He put up quite a fight, but it didn't avail him. Only one of us walked away from that beach.";
					link.l1.go = "Abigile_27";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "MeetTonzag")
				{
					dialog.text = "Alright "+pchar.name+", I have a serious offer for you. The matter I am going to talk about is very dangerous, but, considering the way you got rid of Fleetwood, I am sure you can handle it. You have a...rare knack for solving difficult problems.";
					link.l1 = "I'm flattered. Keep talking.";
					link.l1.go = "Lucas";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SeekAbiIsland")
				{
					DelLandQuestMark(npchar);
					DelMapQuestMarkCity("SentJons");
					dialog.text = "Welcome back, "+pchar.name+"! Any good news for me?";
					link.l1 = "John, from now on you can sleep without a knife under your pillow. Lucas is no longer a threat to you. He is under arrest and locked up, and he is about to be sent to Holland in the near future, where he will be tried for insurrection, attempted murder, and other misdeeds.";
					link.l1.go = "Lucas_10";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "VanbergDestroyed")
				{
					DelLandQuestMark(npchar);
					DelMapQuestMarkCity("SentJons");
					dialog.text = "Glad to see you, "+pchar.name+"! You're alive - and that's a good thing. Any news?";
					link.l1 = "Yes. Van Berg is gone for good. Just as you said, he tracked me down and attacked at the most inconvenient moment. Van Berg was a tough nut, but in the end I cracked him.";
					link.l1.go = "Final";
					break;
				}
			dialog.text = "Do you need anything else?";
			link.l1 = "No, John, nothing. I am leaving.";
			link.l1.go = "exit";
			break;
			}
			dialog.text = "Good afternoon. I am happy to see you in my drugstore. I have remedies for most ailments and infirmities. What can I offer you?";
			link.l1 = "Nothing at the moment, thank you. I feel quite well.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

//--------------------------------------------за Голландию-----------------------------------------------------
		case "Knippel_exit":
			dialog.text = "I have no idea what you are talking about, sir. Who is Lucas Rodenburg? I have no dealings with the Dutch. You must be mistaken.";
			link.l1 = "What? Mynheer Rodenburg sent me to you!";
			link.l1.go = "Knippel_exit_1";
		break;
		
		case "Knippel_exit_1":
			dialog.text = "Let me tell you once again - I don't know any man named Mynheer Rodenburg. As for the Dutch, I do not deal with them. There are only two things I can't stand in this world: people who are intolerant of other people's cultures, and the Dutch. So if you don't need any medicine, please, leave me to do my work.";
			link.l1 = "Curiouser and curiouser...";
			link.l1.go = "exit";
		break;

		case "Knippel":
			dialog.text = "Well, well... Are you from Mynheer Rodenburg? Alright. I'm listening.";
			link.l1 = "I need to arrange a meeting with Captain Fleetwood in a secluded place. I borrowed the 'Mirage' from Jacob van Berg, the Dutch privateer whom Mr. Fleetwood is so eager to capture. I would like to inform him that the 'Mirage' will be conveniently hove to off the coast of Dominica in the near future. ";
			link.l1.go = "Knippel_1";
		break;
		
		case "Knippel_1":
			dialog.text = "Did Jacob give you his ship? Hm, so now you need someone to tell Mr. Fleetwood that the 'Mirage' will soon be off the coast of Dominica, since you can't tell Richard about that yourself for particular reasons...";
			link.l1 = "Exactly. Mynheer Rodenburg recommended that I address this matter to you.";
			link.l1.go = "Knippel_2";
		break;
		
		case "Knippel_2":
			dialog.text = "In this case, Charlie Knippel is the man you need. A loyal friend of Fleetwood... and his spy. Talk to him and mention everything you want Richard to know. Be careful, Knippel may seem quite simple, but he is no fool.\nYou can find him in a small hut, not far from the seashore. He should be there.";
			link.l1 = "I see. Thank you, Mr. Murdock. Farewell!";
			link.l1.go = "Knippel_3";
		break;
		
		case "Knippel_3":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "toKnippel";
			AddQuestRecord("Holl_Gambit", "1-16");
			AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
		break;
		
		case "Merdok_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			sld = characterFromId("Tonzag");
			PlaySound("Voice\English\hambit\Ercule Tongzag-04.wav");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			//а вот и китаец нарисовался
			sld = characterFromId("Longway");
			LAi_SetWarriorType(sld);
			FantomMakeCoolFighter(sld, 18, 40, 40, "blade_08", "pistol1", "bullet", 70);
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.LongwayEnemy"))//враг
			{
				ChangeCharacterAddressGroup(sld, "SentJons_TownCave", "monsters", "monster8");
				LAi_group_MoveCharacter(sld, "EnemyFight");
				PlaySound("Voice\English\hambit\Longway-02.wav");
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.LongwayFriend"))//друг
			{
				LAi_warrior_DialogEnable(sld, true);
				sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
				sld.dialog.currentnode = "Longway_hire";
				ChangeCharacterAddressGroup(sld, "SentJons_TownCave", "monsters", "monster8");
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				PlaySound("Voice\English\hambit\Longway-02.wav");
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.LongwayNeutral")) sld.lifeday = 0;//нейтрал - просто нет
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "Merdok_AfterBattle");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
//-------------------------------------------------за Англию-----------------------------------------------------
		case "Merdok_talk":
			dialog.text = "Really? I thought that poor Gaston had been burning in hell for quite some time now.";
			link.l1 = "Could well be, but there's clearly nobody quite like Gaston. I found his head in an old Jew's hoard on the secret island. But he still managed to send greetings to you. He also mentioned that we have a common enemy: Mr. Rodenburg. Tonzag said that you might have papers important to Lucas which could lure him out of his hideyhole in Curacao.";
			link.l1.go = "Merdok_talk_1";			
		break;
		
		case "Merdok_talk_1":
			dialog.text = "He was right. It is my archive that gives Rodenburg sleepless nights. It appears that he is still hanging around only because of it. The thing is, he was promised a cushy job in the Committee of Directors at the Company back in the United Provinces. If the information in this archive, which contains a lot of interesting things about Lucas's past and present, becomes widely known, his career aspirations will be snuffed out. In that case, the best thing he could hope for is to be beheaded instead of hanged.";
			link.l1 = "Give me the archive, and I will take care of our enemy.";
			link.l1.go = "Merdok_talk_2";			
		break;
		
		case "Merdok_talk_2":
			dialog.text = "You must think me a fool. I am still alive only because I still have it with me. How do I know that you are not working for Lucas now?";
			link.l1 = "You will have to take my word for it - or die.";
			link.l1.go = "Merdok_talk_3";			
		break;
		
		case "Merdok_talk_3":
			PlaySound("Voice\English\hambit\John Mardock-07.wav");
			dialog.text = "Wrong answer, you'll die here and now! Longway, gongji!";
			link.l1 = "Oh ho, the Chinaman emerges from the shadows! No worries, I'll make chop suey out of both of you!";
			link.l1.go = "Merdok_fightEng";			
		break;
		
		case "Merdok_fightEng":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");	
			sld = characterFromId("Longway");
			FantomMakeCoolFighter(sld, 20, 50, 50, "blade_08", "pistol1", "bullet", 80);
			LAi_SetWarriorType(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_TownCave", "monsters", "monster8");
			PlaySound("Voice\English\hambit\Longway-02.wav");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "Merdok_AfterBattleEng");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
//----------------------------------------против всех-------------------------------------------------------
		case "MC_InHouse":
			PlaySound("Voice\English\hambit\John Mardock-02.wav");
			dialog.text = "Finally, you're back on your feet. I was afraid you weren't going to wake up.";
			link.l1 = "What...? Who are you? Where the hell am I? How did I get here?";
			link.l1.go = "MC_InHouse_1";	
		break;
		
		case "MC_InHouse_1":
			dialog.text = "Calm down, don't ask so many questions at once, it's not good for you to get too excited. My name is John Murdock, I am a pharmacist here in St. John's. You lost consciousness in a fight with Fleetwood's men. I must say they gave you quite a beating... It was Hercule who brought you here to my drugstore, and, well, I have treated your wounds with my potions and medicines.";
			link.l1 = "Hercule? Who? The man who came to help me on the street? ";
			link.l1.go = "MC_InHouse_2";			
		break;
		
		case "MC_InHouse_2":
			dialog.text = "Yes. That's him. By the way, he wants to speak with you. You need to meet him in town. Can you still walk? Good. Head out at night - use the secret tunnel that starts behind the door on the ground floor of my house. Don't go out until dark - Fleetwood's men are looking for you.";
			link.l1 = "Aye... Where is my ship?";
			link.l1.go = "MC_InHouse_3";			
		break;
		
		case "MC_InHouse_3":
			if (pchar.Ship.Type == SHIP_NOTUSED)
			{
				dialog.text = "Your ship was impounded and your crew scattered for fear of being killed by Fleetwood's men. I am sorry.";
				link.l1 = "Fuck...";
			}
			else
			{
				dialog.text = "She is in port, at her usual place.";
				link.l1 = "Phew...that's good to hear. I thought I'd lost her.";
			}
			link.l1.go = "MC_InHouse_4";			
		break;
		
		case "MC_InHouse_4":
			dialog.text = "You should meet Hercule. Go to the city at night through the secret tunnel. He will approach you. Now get some rest, and I must return to my work.";
			link.l1 = "Alright, John. And... thank you for your help and for healing me!";
			link.l1.go = "MC_InHouse_5";
		break;
		
		case "MC_InHouse_5":
			NextDiag.CurrentNode = "First time";
			DialogExit();
			npchar.greeting = "merdok_2";
			AddQuestRecord("Holl_Gambit", "3-12");
			pchar.questTemp.HWIC.Self = "MainBegin";//новый флаг квеста
			sld = characterFromId("Bridgetown_tavernkeeper");
			sld.model = "barmen_3";
			sld.greeting = "barmen_1";
			sld.name = "Harry";
			sld.lastname = "Fletcher";//перерисуем бармена Бриджтауна
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload1", true);//закрыть выход из аптеки через дверь
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload2", false);//открыть подземелье из дома
			LocatorReloadEnterDisable("SentJons_TownCave", "reload1_back", false);//открыть дом из подземелья
			pchar.quest.Tonzag_Meeting.win_condition.l1 = "location";
			pchar.quest.Tonzag_Meeting.win_condition.l1.location = "SentJons_town";
			pchar.quest.Tonzag_Meeting.win_condition.l2 = "Night";
			pchar.quest.Tonzag_Meeting.function = "TonzagMeeting";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "SentJons_HouseF3", "goto", "goto1", "MC_TakeCloves", -1);	
		break;
		
		case "About_Fleetwood":
			DelLandQuestMark(npchar);
			dialog.text = "Fleetwood? What do you want to know about him?";
			link.l1 = "Everything. Tell me everything you know. It seems to me that it's no secret to you why Hercule came to Antigua. I'm on his side.";
			link.l1.go = "About_Fleetwood_1";
		break;
		
		case "About_Fleetwood_1":
			dialog.text = "Very well. Captain Richard Fleetwood of the Royal— I mean Commonwealth Navy... damn, I keep forgetting that fanatic Cromwell is in charge and changed the name. Regardless, Fleetwood is a good fighter and a seasoned sailor. He commands a brig called 'Valkyrie'— an excellent ship, I might add, with a crew of elite sailors and marines. He wages a private war upon the United Provinces in general and with the Dutch West India Company in particular. He has pillaged countless Dutch merchant ships and driven the cost of insurance through the roof. The governor of Curacao has put a record-breaking bounty on his head.";
			link.l1 = "Hmm... Seems a bit unusual for an officer of the 'Commonwealth Navy' to turn pirate...";
			link.l1.go = "About_Fleetwood_2";
		break;
		
		case "About_Fleetwood_2":
			dialog.text = "Yes, indeed. He is walking a tightrope. The English do not officially recognize his actions and refuse to have anything to do with it, but they actually encourage him behind the scenes. I have reason to suppose that he is somehow connected with the English spy ring in the Caribbean, and those scoundrels are not to be trifled with";
			link.l1 = "A serious man... Is this all? Hercule told me about one of his assistants... another Charlie... what's his name... Canister? Cannonball?";
			link.l1.go = "About_Fleetwood_3";
		break;
		
		case "About_Fleetwood_3":
			dialog.text = "Knippel? Yes, there is such a fellow. Charlie Knippel used to be a master gunner in the English Navy, now retired. Now he lives a quiet life on the shore. He is Fleetwood's eyes and ears in St. John's, so be careful with him and don't even think of questioning him about Richard – you will end up in prison or worse.";
			link.l1 = "I see. Can you tell me anything else worth mentioning about Fleetwood?";
			link.l1.go = "About_Fleetwood_4";
		break;
		
		case "About_Fleetwood_4":
			dialog.text = "An idol for all women on Antigua from sixteen to sixty. Seems that's all there is to say about him. Well, I think you know what's happened to him now. He stays in bed and licks his wounds.";
			link.l1 = "He must have some weaknesses or vices...";
			link.l1.go = "About_Fleetwood_5";
		break;
		
		case "About_Fleetwood_5":
			dialog.text = "What do you mean?";
			link.l1 = "Well, maybe he likes to gamble or drinks heavily or can't resist the fairer sex - something along these lines. Is he married?";
			link.l1.go = "About_Fleetwood_6";
		break;
		
		case "About_Fleetwood_6":
			dialog.text = "No, a bachelor. As for the things you mentioned – he is not known for any of them.";
			link.l1 = "I see. But perhaps there is still something special about him? Even a person like him must have some weak points!";
			link.l1.go = "About_Fleetwood_7";
		break;
		
		case "About_Fleetwood_7":
			dialog.text = "I don't know. Listen, let's do it this way. Come see me in a week, and I will investigate Fleetwood's private life. Deal?";
			link.l1 = "Deal. Thank you, John! I'll be here in a week.";
			link.l1.go = "About_Fleetwood_8";
		break;
		
		case "About_Fleetwood_8":
			DialogExit();
			pchar.questTemp.HWIC.Self = "WaitFleetwood";
			SaveCurrentQuestDateParam("questTemp.Wait_Fleetwood");
			SetFunctionTimerCondition("Wait_FleetwoodQM", 0, 0, 7, false);
			SetFunctionTimerCondition("Wait_FleetwoodOver", 0, 0, 12, false);//чтобы не опаздывал
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload1", false);//открыть выход из аптеки
			AddQuestRecord("Holl_Gambit", "3-14");
		break;
		
		case "About_Fleetwood_9":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("SentJons");
			dialog.text = "Yes, but not much, unfortunately. And I am afraid it is not of much use, anyway.";
			link.l1 = "Spit it out! Every tiny detail is important if it has anything to do with Fleetwood.";
			link.l1.go = "About_Fleetwood_10";
		break;
		
		case "About_Fleetwood_10":
			dialog.text = "Not so long ago, Richard picked up two Jewish refugees from an unknown island – an old man and his daughter, bound for Willemstad. The ship they had been sailing on was sunk by pirates. Fleetwood secretly brought them to Curaçao, risking his own neck. Several months have passed since then. Now he has dispatched his faithful dog, Charlie Knippel, to Willemstad...";
			link.l1 = "Hmm... How is it connected?";
			link.l1.go = "About_Fleetwood_11";
		break;
		
		case "About_Fleetwood_11":
			dialog.text = "I managed to learn that Charlie received an order to bring some girl here from Willemstad, a Jewess named Abigail Shneur. Yes, the same girl from the island. It seems Richard has fallen in love with her, since he’s sending his best agent for her.\nThat’s all. I don’t know if it helps at all.";
			link.l1 = "Oh ho ho! Hahaha! It seems our confirmed bachelor has fallen for the Jewess's wily charms. This is excellent work, John, thank you! Now, when will our friend Knippel depart for Curacao?";
			link.l1.go = "About_Fleetwood_12";
		break;
		
		case "About_Fleetwood_12":
			dialog.text = "He departed yesterday.";
			link.l1 = "And on which ship?";
			link.l1.go = "About_Fleetwood_13";
		break;
		
		case "About_Fleetwood_13":
			dialog.text = "I knew you'd ask that. He's on a brigantine commissioned by the Commonwealth—oh, to hell with it, the 'Royal Navy'. Her name is 'Zeekalf'.";
			link.l1 = "'Zeekalf'? That's quite a Dutch name for an English ship...ohhh, I see.";
			link.l1.go = "About_Fleetwood_14";
		break;
		
		case "About_Fleetwood_14":
			dialog.text = "You are a quick thinker... Her former name was 'Royal Mary', but for this voyage she's been named 'Zeekalf'. And she is flying the Dutch flag.";
			link.l1 = "Your help has been invaluable, John. I am setting off now. I will be back soon, and I will need your room on the second floor, where you put me up while I recovered.";
			link.l1.go = "About_Fleetwood_15";
		break;
		
		case "About_Fleetwood_15":
			dialog.text = "What are you up to?";
			link.l1 = "I will tell you everything when I'm back. Wish me luck, John! Farewell.";
			link.l1.go = "About_Fleetwood_16";
		break;
		
		case "About_Fleetwood_16":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-16");
			pchar.questTemp.HWIC.Self = "HuntKnippel";
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("HuntKnippelOver", 0, 0, 10, false);
			pchar.quest.Hunt_Knippel.win_condition.l1 = "location";
			pchar.quest.Hunt_Knippel.win_condition.l1.location = "Curacao";
			pchar.quest.Hunt_Knippel.function = "CreateKnippelShip";
			LocatorReloadEnterDisable("SentJons_town", "houseH1", true);//закрыть хижину Чарли
			AddMapQuestMarkIsland("Curacao", true);
		break;
		
		case "About_Fleetwood_17":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-15");
			pchar.questTemp.HWIC.Self = "end";
			pchar.questTemp.HWIC.Detector = "self_fail";
			CloseQuestHeader("Holl_Gambit");
		break;
		
		case "Abigile":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("SentJons");
			dialog.text = "Really? Why are you so sure?";
			link.l1 = "Because Charlie is at the seabed feeding the fish. I boarded the 'Zeekalf' and sent Knippel to hell. Of course, I questioned him beforehand... He had a letter on him, which allowed me to pass as Knippel when I spoke to our Jewess Abigail, the sweetheart of our brave Richard.";
			link.l1.go = "Abigile_1";
		break;
		
		case "Abigile_1":
			dialog.text = "Hmm... That's clever. So, you're saying that...";
			link.l1 = "Yes. I've brought the Jewess to Antigua. She is on board my ship. Now I have an ace up my sleeve in my game with Fleetwood! He will do anything for her...";
			link.l1.go = "Abigile_2";
		break;
		
		case "Abigile_2":
			dialog.text = "Are you sure? It could be that everything is not as simple as you imply...";
			link.l1 = "Oh yes, I am absolutely sure. From the letter I have figured out that Abigail's father was against her marriage with Richard because of money. I know, typical Jewish father-in-law. So Fleetwood decided to pay her father a dowry - 200,000 pesos! Tell me now, how many girls in the world are worth that much money?";
			link.l1.go = "Abigile_3";
		break;
		
		case "Abigile_3":
			dialog.text = "Heh! Certainly not a Jewess! I've never met a Christian girl worth that in my life, that's for sure. "+pchar.name+", you are a cunning scoundrel. What will you do with her?";
			link.l1 = "I will bring the Jewess here and we will keep her in your room. I will tell her that Richard has gone to sea and has not returned yet, so she will be our guest for a week. She thinks that I am Charlie Knippel.";
			link.l1.go = "Abigile_4";
		break;
		
		case "Abigile_4":
			dialog.text = "That's interesting. So you decided to keep the girl in my house? Hmm...";
			link.l1 = "John, she is a Jew. A stateless wanderer brought from a Dutch colony. She is a nobody here in St. John's and no one knows her. Rest assured, we can do as we please and she will not dare to say a word. She doesn't have a penny or a friend to her name. And anyway, she will not be our guest for long. I will lure Fleetwood out with her as bait, and after that there will be no need for her anymore.";
			link.l1.go = "Abigile_5";
		break;
		
		case "Abigile_5":
			dialog.text = "You're starting to frighten me, Charles. You're not going to take advantage of this girl, are you? Or bring her to the same end as Knippel?";
			link.l1 = "No, of course not. 'Cunning scoundrel' I may be, but I am no enemy of beautiful girls - Jew or Christian. Or of ugly ones, for that matter. If she behaves herself, I will bring her to her father in Willemstad after this is all over. The old miser will probably fall at my knees and thank me for saving her from that perfidious Englishman.";
			link.l1.go = "Abigile_6";
			// belamour legendary edition -->
			link.l2 = "She has a part to play in this mummery. When the play is over I will have no use for her.";
			link.l2.go = "Abigile_6a";
		break;
		
		case "Abigile_6a":
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "Sneak", 60);
			dialog.text = "I see, so for now I have to look after her.";
			link.l1 = "I won't insist, mate. If you are totally against this, she can stay aboard my ship. But then I will have to clap her in irons for safety and keep her in the hold with the rats to protect her from my crew. It's a novelty for them to have a woman aboard, you know. It would be a shame to treat such a lovely girl like that.";
			link.l1.go = "Abigile_7";
		break;
		
		case "Abigile_6":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 60);
			// <-- legendary edition
			dialog.text = "I see, so for now I have to look after her.";
			link.l1 = "I won't insist, mate. If you are totally against this, she can stay aboard my ship. But then I will have to clap her in irons for safety and keep her in the hold with the rats to protect her from my crew. It's a novelty for them to have a woman aboard, you know. It would be a shame to treat such a lovely girl like that.";
			link.l1.go = "Abigile_7";
		break;
		
		case "Abigile_7":
			dialog.text = "I understand. Very well, bring her here. It is my duty to help you in your fight against Fleetwood. Bring her here and I will prepare her 'guest room'.";
			link.l1 = "Thank you, John. I knew I could count on you.";
			link.l1.go = "exit";
			pchar.questTemp.HWIC.Self = "AbigileInCabin";
			DoQuestCheckDelay("SetAbigileToCabin", 1.0); // fix 180812
			AddQuestRecord("Holl_Gambit", "3-24");
			//поставим табурет
			sld = ItemsFromID("lcheer");
			sld.shown = true;
			sld.startLocation = "SentJons_HouseF3";
			sld.startLocator = "goto2";
			AddLandQuestMark(characterFromId("Abigile"), "questmarkmain");
		break;
		
		case "Abigile_7_1":
			DelLandQuestMark(npchar);
			dialog.text = "Oh! My pleasure. I am happy to welcome such an important and... elegant woman. Miss, could you go up to the second floor, please? There is supper waiting for you and the bed is made. I am sure you will want to have a good night's sleep after such a long trip.";
			link.l1 = "Yes. Abigail must be tired after such a long voyage from Willemstad.";
			link.l1.go = "Abigile_8";
		break;
		
		case "Abigile_8":
			DialogExit();
			sld = characterFromId("Abigile");
			sld.dialog.currentnode = "Abigile_kidnapping_11";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Abigile_9":
			dialog.text = "Do you already have a plan?";
			link.l1 = "I do. We need to write a letter to Richard with a ransom demand for Abigail. Arrange a meeting somewhere on an uninhabited island - like Turks. And if he doesn't comply, then, how shall I put it, we'll send his Hebrew sweetheart to him in pieces.";
			link.l1.go = "Abigile_10";
		break;
		
		case "Abigile_10":
			dialog.text = "What's the need for such complications with an uninhabited island?";
			link.l1 = "Neutral ground. It's safer. I'm not going to bring Abigail anyway. I need Fleetwood. He will certainly prepare an ambush on Antigua, but on Turks he will have no such advantage.";
			link.l1.go = "Abigile_11";
		break;
		
		case "Abigile_11":
			dialog.text = "Fair enough. Who will deliver the letter? It is very dangerous.";
			link.l1 = "A stranger. Pick a drunkard from the tavern, one who looks reliable. They are willing to do whatever you ask for some rum money. If Richard kills him in a fit of rage, we'll send another. And we'll enclose one of Abi's fingers in the letter. That will make him much more compliant.";
			link.l1.go = "Abigile_12";
		break;
		
		case "Abigile_12":
			dialog.text = ""+pchar.name+"...";
			link.l1 = "Don't worry, John. I'm sure it won't come to that. You just need to find a courier and I'll compose the letter right away. Do you have any paper and ink?";
			link.l1.go = "Abigile_13";
		break;
		
		case "Abigile_13":
			dialog.text = "Yes, I do. And I happen to know a suitable drunkard as well. I recommend Jack Harrison. He spends every evening in the tavern, tanking up on rum. You'll find him easily enough.";
			link.l1 = "Good, fetch me pen and ink and I will compose the ransom note for Richard.";
			link.l1.go = "Abigile_14";
		break;
		
		case "Abigile_14":
			DialogExit();
			StartQuestMovie(true, false, true);
			locCameraFromToPos(0.07, 2.57, -2.46, true, -0.08, -0.38, 1.35);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto2", "MC_writeLetter", -1);
		break;
		
		case "Abigile_15":
			dialog.text = "When are you going to hand him the letter? Are you going to watch the delivery in progress?";
			link.l1 = "Sure. Richard is not a fool, but I doubt he will take any chances. At least, I hope so. I don't want to hurt the girl, but I will if I must. Well, it's time to find the drunkard you mentioned. Jack... what was his full name?";
			link.l1.go = "Abigile_20";
		break;
		
		case "Abigile_20":
			dialog.text = "His name is Jack Harrison. He usually visits the tavern in the evening. Be careful!";
			link.l1 = "Everything will be alright. Wait for me.";
			link.l1.go = "Abigile_22";
		break;
		
		case "Abigile_22":
			DialogExit();
			LAi_SetOwnerType(npchar);
			pchar.questTemp.HWIC.Self = "LetterToDrunkardGo";
			AddDialogExitQuestFunction("CreateDrunckardInTavern");
			AddQuestRecord("Holl_Gambit", "3-25");
		break;
		
		case "Abigile_23":
			DelLandQuestMark(npchar);
			dialog.text = "Well, I would not say so. Fleetwood is cunning and dangerous. On top of that, he is a master swordsman and a seasoned sailor. He will not be easy prey.";
			link.l1 = "I stopped taking the easy way out when I came to the Caribbean. Well, John, it's time for me to leave. By the way, you mentioned that our brave Fleetwood has a good ship, didn't you?";
			link.l1.go = "Abigile_24";
		break;
		
		case "Abigile_24":
			dialog.text = "He has the finest brig I have ever seen. And I have seen quite a few.";
			link.l1 = "That's good. I like fine ships. Time to weigh anchor!";
			link.l1.go = "Abigile_26";
		break;
		
		case "Abigile_26":
			DialogExit();
			pchar.questTemp.HWIC.Self = "FleetwoodToIsland";
			pchar.quest.Fleetwood_meetingShore.win_condition.l1 = "location";
			pchar.quest.Fleetwood_meetingShore.win_condition.l1.location = "Shore56";
			pchar.quest.Fleetwood_meetingShore.function = "InTerksShore";
			AddQuestRecord("Holl_Gambit", "3-28");
			AddMapQuestMarkShore("Shore57", false);
		break;
		
		case "Abigile_27":
			int iVal = 0;
			for(i = 0; i < COMPANION_MAX; i++)
			{
				iTemp = GetCompanionIndex(PChar, i);
				if(iTemp > 0)
				{
				sld = GetCharacter(iTemp);
				if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_VALCIRIA) iVal = 1;
				}
			}//установили признак наличия Валькирии в эскадре.
			if (iVal != 0)
			{
				dialog.text = "I am speechless! An excellent combination, a brilliant idea, and masterful execution! My congratulations, "+pchar.name+"! And you've also managed to capture his brig as a prize!";
				link.l1 = "Thank you! And where is Hercule? I would like to see him. When we last met, he told me I would be able to find him with your help.";
				link.l1.go = "Abigile_28";
			}
			else
			{
				dialog.text = "An excellent combination, a great idea, and a masterful implementation! My congratulations, "+pchar.name+"!";
				link.l1 = "Thank you! And where is Hercule? I would like to see him. When we last met, he told me I would be able to find him with your help.";
				link.l1.go = "Abigile_28";
			}
		break;
		
		case "Abigile_28":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("SentJons");
			dialog.text = "I am expecting him any moment now. He should come here through the secret tunnel. And you should explain yourself to Abigail. She's started worrying about Richard's absence.";
			link.l1 = "Alright, but shouldn't we send her home?";
			link.l1.go = "Abigile_29";
		break;
		
		case "Abigile_29":
			dialog.text = "Not yet... I need to talk to you first. But first, wait for Hercule's arrival. Go and comfort Abigail. Tell her a story, make something up. Then come to the basement. Alright?";
			link.l1 = "Aye aye, John.";
			link.l1.go = "Abigile_30";
		break;
		
		case "Abigile_30":
			DialogExit();
			npchar.greeting = "merdok_4";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "SentJons_TownCave", "item", "berglar1", "", -1);
			pchar.questTemp.HWIC.Self = "AbigileLie";
			sld = characterFromId("Abigile");
			LAi_SetCitizenType(sld);
			AddLandQuestMark(sld, "questmarkmain");
			AddQuestRecord("Holl_Gambit", "3-34");
		break;
		
		case "Lucas":
			DelLandQuestMark(npchar);
			dialog.text = "Well, the time has come to lay the cards down. As you have already figured out, I am not just a plain druggist. My real name is Johan van Merden, and until recently I've been an agent for the Dutch West India Company and the right hand of its vice president, Lucas Rodenburg.";
			link.l1 = "Really! That is interesting...";
			link.l1.go = "Lucas_1";
		break;
		
		case "Lucas_1":
			dialog.text = "It's different now. Lucas wants to leave the game and return to the Netherlands, so he needs to bury everything and everyone connected to his past\nI think I am still breathing only because of my archives, which contain all the information about Lucas's crimes... like the story of the 'ghost ship', which is just an ordinary pirate vessel under the command of the reckless and unprincipled scoundrel Jacob van Berg. Rodenburg hired the man to plunder and sink English trade ships\nVan Berg is also responsible for sinking the fluyt with Abigail and her father aboard. Abigail is an important figure in this game; Rodenburg also wanted her hand and heart, just like Fleetwood did, so I was quite surprised when you brought her here...";
			link.l1 = "Rodenburg... that's the son-in-law Abigail's eccentric father was talking about!";
			link.l1.go = "Lucas_2";
		break;
		
		case "Lucas_2":
			dialog.text = "Yes, that is why I want her to stay here for a while. She might be my last ace in the game against Rodenburg, though I would prefer not to use her any further; she is a good girl, I don't want her to suffer. I think that Lucas would choose my archive over her, if the choice were presented.\nSo, I propose that you become my ally in the game against Lucas... get rid of him, use any means necessary. The reward will be substantial.";
			link.l1 = "Hmm... I don't think it's going to be any more difficult than with Fleetwood. ";
			link.l1.go = "Lucas_3";
		break;
		
		case "Lucas_3":
			dialog.text = "No, you're wrong. In the end, Fleetwood was a lone wolf, acting on his own. Rodenburg is vice president of the Company. He is a very influential man; only the governor of Curacao has more power. Jacob van Berg is his agent, a very dangerous man. Lucas sits on his arse in Willemstad under the protection of the Company's guardsmen; they are as good as Fleetwood's men.\nThis is not going to be easy.";
			link.l1 = "The rules of the game are the same - to lure a tiger out of its den... I already have a plan. What else can you tell me about Lucas?";
			link.l1.go = "Lucas_4";
		break;
		
		case "Lucas_4":
			dialog.text = "Well, I have told you almost everything. He owns a swift ship called 'Meifeng' - Beautiful Wind. Her captain is a Chinaman named Longway - Rodenburg's sworn man. He, too, is an enemy you would not wish to face. There are no amateurs in Lucas' crew. ";
			link.l1 = "We already had a trump card right from the start - your archive. If he values his life more than the Jewess, then he will do anything to keep the information in the archive confidential... But... does the archive really exist, John? Are you bluffing?";
			link.l1.go = "Lucas_5";
		break;
		
		case "Lucas_5":
			dialog.text = "The archive does exist. And Lucas knows about it. Have you come up with anything yet?";
			link.l1 = "I have. John, if you really were the company's agent, you should know something.";
			link.l1.go = "Lucas_6";
		break;
		
		case "Lucas_6":
			dialog.text = "What exactly? Ask me.";
			link.l1 = "I need to intercept a ship belonging to the Company. Preferably an unescorted vessel — a courier or something similar. Can you tell me anything about this?";
			link.l1.go = "Lucas_7";
		break;
		
		case "Lucas_7":
			dialog.text = "Hm... I don't possess such information. Wait! I know for sure that the Company has a packet ship on the sea lanes between Philipsburg and Willemstad once a month. She delivers business papers. She's a brigantine named 'Hoop'.\nShe will leave Philipsburg today or tomorrow.";
			link.l1 = "Aye, that's it! All I need now is to head to the shores of Saint Christopher. The sea route to Curaçao goes right past.";
			link.l1.go = "Lucas_8";
		break;
		
		case "Lucas_8":
			dialog.text = "Good luck, "+pchar.name+". I won't ask you about the details of your plan. I will be waiting for your return!";
			link.l1 = "Everything will be fine, John. Take care of the Jewish woman and treat her well!";
			link.l1.go = "Lucas_9";
		break;
		
		case "Lucas_9":
			DialogExit();
			RemoveItems(PChar, "MC_Letter", 1);
			GiveItem2Character(pchar, "MC_Letter");
			ChangeItemDescribe("MC_Letter", "itmdescr_MC_Letter2");
			AddQuestRecordInfo("LetterToLucas", "1");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "SentJons_HouseF3", "goto", "goto1", "MC_TakeCloves", -1);
			pchar.questTemp.HWIC.Self = "LetterToLucas";
			sld = characterFromId("Tonzag");
			sld.dialog.currentnode = "Tonzag_hired";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			AddQuestRecord("Holl_Gambit", "3-36");
			//установим таймер на генерацию энкаунтера
			pchar.quest.HWIC_Cureer.win_condition.l1 = "Timer";
			pchar.quest.HWIC_Cureer.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.HWIC_Cureer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.HWIC_Cureer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.HWIC_Cureer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.HWIC_Cureer.function = "CreateHWICCureerOnMap";
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("HWICCureerOnMapOver", 0, 0, 16, false);//таймер
		break;
		
		case "Lucas_10":
			dialog.text = "Incredible! I cannot believe my ears! How did that happen?";
			link.l1 = "I captured the packet ship and sent a letter to Lucas on behalf of Fleetwood, in which I stated that I'd taken possession of a certain archive belonging to some druggist from St. John's, and that soon the evidence of his every misdeed would become known from here to Amsterdam and London. I expected him to start hunting me, but it turned out the other way.";
			link.l1.go = "Lucas_11";
		break;
		
		case "Lucas_11":
			dialog.text = "";
			link.l1 = "Lucas accused Matthias Beck of betrayal and dealings with the English, put him behind bars and took up residence in the governor's palace. He most likely eliminated the captain of the brigantine. Then he ordered his loyal Chinaman from the Meifeng to sink the ship with the Company's director, Peter Stuyvesant, aboard!";
			link.l1.go = "Lucas_12";
		break;
		
		case "Lucas_12":
			dialog.text = "Rodenburg is a ruthless man. But even I did not think he could go to such lengths...";
			link.l1 = "I captured the Meifeng and questioned Longway. He told me everything. I found Stuyvesant and warned him about Rodenburg's intentions, and we sailed to Willemstad together. Stuyvesant set Beck free and arrested Lucas. He is in prison now.";
			link.l1.go = "Lucas_13";
		break;
		
		case "Lucas_13":
			dialog.text = "Heh! You have real talent, my friend... You should make a career in the Company Navy or as a politician back in the United Provinces - you've every chance to become governor! And what did you do to Longway?";
			link.l1 = "I let him go. He surrendered honourably, so I didn't do him any harm.";
			link.l1.go = "Lucas_14";
		break;
		
		case "Lucas_14":
			dialog.text = "That's good. Longway is a good man, unlike his former boss. Well, "+pchar.name+", you've done a great job! I'll prepare your reward, but I will need some time... In the meantime...";
			link.l1 = "John, to tell the truth, there is a fly in the ointment. Longway and then Rodenburg both told me that Jacob van Berg is hunting me. How bad is that?";
			link.l1.go = "Lucas_15";
		break;
		
		case "Lucas_15":
			dialog.text = "Jacob van Berg? Charlie, this is serious. He is a merciless pirate, a skilful sailor and fighter who makes Fleetwood look like a pussycat. A professional hunter. He was the one destroying shipping on Rodenburg's orders.\nHe will find you, so you must prepare. I should take precautions myself.";
			link.l1 = "How can I find this van Berg?";
			link.l1.go = "Lucas_16";
		break;
		
		case "Lucas_16":
			dialog.text = "I don't know. Lucas and Longway were the only ones who knew where to find him. So just be careful and stay alert\nI am shutting the place down. Go through the secret tunnel if you want to see me. And take the Jewess away, it is too dangerous for her to stay here.";
			link.l1 = "Don't worry, John. Let him show up and I'll deal with him. Where is Abigail?";
			link.l1.go = "Lucas_17";
		break;
		
		case "Lucas_17":
			dialog.text = "She's gone to church. I am sorry for her. She's been very upset recently.";
			link.l1 = "Well... That is a pleasant surprise. Perhaps she realises that Christ is the Messiah her people have long awaited. Well, it is time to bring her back to her father.";
			link.l1.go = "Lucas_18";
		break;
		
		case "Lucas_18":
			dialog.text = "She wanted to see you. I am sure that she will ask you to take her back home.";
			link.l1 = "Abi, huh?";
			link.l1.go = "Lucas_19";
		break;
		
		case "Lucas_19":
			dialog.text = "Well , I have to admit that we've become friends. I don't regret that she has been living in my house, and thank God she will never know why she was brought here.";
			link.l1 = "Alright, John, I will go to the church to meet Abigail. Then I am heading to Willemstad.";
			link.l1.go = "Lucas_20";
		break;
		
		case "Lucas_20":
			DialogExit();
			sld = characterFromId("Abigile");
			AddLandQuestMark(sld, "questmarkmain");
			ChangeCharacterAddressGroup(sld, "SentJons_church", "goto", "goto1");//Аби - в церковь
			AddQuestRecord("Holl_Gambit", "3-56");
			pchar.questTemp.HWIC.Self = "AbiReturnHome";
			LocatorReloadEnterDisable("SentJons_town", "HouseF3", true);//закрыть аптеку
		break;
		
		case "Final":
			dialog.text = "You... cracked his nuts? Oh - a metaphor. Well, nuts or no nuts, you did it! Congratulations!";
			link.l1 = "I would not lie to you, heh. Now you can breathe freely, John.";
			link.l1.go = "Final_1";
		break;
		
		case "Final_1":
			dialog.text = "Finally! I think it's better to give up all these political games and intrigues. Now it's time to talk about your reward for the job.";
			link.l1 = "Well, I would certainly appreciate that.";
			link.l1.go = "Final_2";
		break;
		
		case "Final_2":
			dialog.text = "I am going to leave the Caribbean forever. As a way of thanking you for your help and for rescuing me from Rodenburg, I am granting you the deed of ownership of this house and my apothecary. They are all yours now. Take the keys.";
			link.l1 = "That is great! I am quite happy. You've got a very comfortable house and a cosy cellar...";
			link.l1.go = "Final_3";
		break;
		
		case "Final_3":
			GiveItem2Character(pchar, "Drugstore_keys");//ключ
			dialog.text = "And also, please accept this modest sum of 100,000 pesos and this musket. It once served me faithfully, and it will serve you well, too.";
			link.l1 = "I am not refusing such gifts!";
			link.l1.go = "Final_4";
			LocatorReloadEnterDisable("SentJons_town", "HouseF3", false);//открыть аптеку
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload3", false); // открыть комнату
			pchar.quest.Jino_Door.win_condition.l1 = "locator";
			pchar.quest.Jino_Door.win_condition.l1.location = "SentJons_HouseF3";
			pchar.quest.Jino_Door.win_condition.l1.locator_group = "reload";
			pchar.quest.Jino_Door.win_condition.l1.locator = "reload4";
			pchar.quest.Jino_Door.function = "OpenRoomDoor";//на локатор комнаты Джино
			Achievment_Set("ach_10");
		break;
		
		case "Final_4":
			AddMoneyToCharacter(pchar, 100000);
			GiveItem2Character(pchar, "mushket2");
			dialog.text = "In the room upstairs you will find a young natural philosopher. He is the best apothecary I know. It was he who made these mixtures, which helped you recover in a couple of days. Take care of his allowance and his knowledge will compensate all your costs with interest.";
			link.l1 = "My own personal bookworm? Very well, I will take care of him.";
			link.l1.go = "Final_5";
		break;
		
		case "Final_5":
			dialog.text = "I have to say goodbye now. I am going to the cellar to pack up my belongings. Tomorrow I won't be here - I am sailing away from Antigua. I am glad that I've met you, and I am grateful you were on my side and not with my enemies.";
			link.l1 = "I am also happy to meet you, John. Perhaps we'll meet again...";
			link.l1.go = "Final_6";
		break;
		
		case "Final_6":
			dialog.text = "Not in this life, my friend. I'm going to pack up. Goodbye, "+pchar.name+"!";
			link.l1 = "Goodbye, John! Good luck to you!";
			link.l1.go = "Final_7";
		break;
		
		case "Final_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", -1);
			npchar.lifeday = 0;
			pchar.questTemp.HWIC.Self = "final";
			AddQuestRecord("Holl_Gambit", "3-64");
			CloseQuestHeader("Holl_Gambit");
			pchar.questTemp.HWIC.Detector = "self_win";
			CheckPortugalHWIC();
		break;
		
		// Страж Истины
		case "guardoftruth":
			dialog.text = "Ah, good sir, don't listen to such foolish talk. There is nobody there. That's my laboratory, mixtures are being prepared, you know...";
			link.l1 = "All kidding aside, John. Does the name Gino Gvineili ring a bell?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Hmm...";
			link.l1 = "Aha! I can see it in your eyes - I'm right... That's where he lives and for whom he prepares his herbs!";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Sir, I am telling you once again - there's nobody here.";
			link.l1 = "Let's put the excuses aside, John. I will not harm your alchemist - but if Father Vincento of Santiago finds him, I cannot be sure. The Inquisitor is already planning to send his 'Domini Canes' to Antigua...";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "What do you want from him?";
			link.l1 = "Just to talk. He has some rather important information for me. I promise I will not turn him over to the Inquisition, nor will I harm him in any way.";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "Gino is a kind fellow. Don't believe anything Father Vincenzo has told you about him. And remember - I will stand up for my alchemist.";
			link.l1 = "I gave you my word. Isn't that enough for you?";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "Go upstairs, then. The door is open. And I hope you will stay true to your word.";
			link.l1 = "Rest assured, I will.";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			DialogExit();
			pchar.questTemp.Guardoftruth = "jino1";
			AddQuestRecord("Guardoftruth", "36");
			LocatorReloadEnterDisable(pchar.location, "reload4", false);
		break;
		
		// алхимический набор
		case "alchemy":
			dialog.text = "Captain, wouldn't you like to become familiar with the hermetic arts? This could prove quite useful to you.";
			link.l1 = "I am sorry, but my occupation is somewhat different. I am used to holding a sword hilt in my hand – not flasks or test tubes.";
			link.l1.go = "alchemy_exit";
			link.l2 = "'There are more things in heaven and earth than are dreamt of in your philosophy.' Of course, I would love to. What is needed?";
			link.l2.go = "alchemy_1";
			npchar.quest.alchemy = true;
		break;
		
		case "alchemy_exit":
			dialog.text = "As you wish. I just offered...";
			link.l1 = "...";
			link.l1.go = "exit";
		break;
		
		case "alchemy_1":
			dialog.text = "You should learn to mix herbs with your own hands. But you will not succeed without an alchemist's kit. Take a look at this bag. It contains everything a budding alchemist needs - test tubes, flasks, a still, spatulas, glass tubes, a burner, and plenty of similar things...";
			link.l1 = "Very interesting! And what can I make with it?";
			link.l1.go = "alchemy_2";
		break;
		
		case "alchemy_2":
			dialog.text = "Well, you won't be able to transmute lead into gold, but you will be able to mix ingredients according to various recipes and thus obtain potions and other useful things.";
			link.l1 = "Recipes?";
			link.l1.go = "alchemy_3";
		break;
		
		case "alchemy_3":
			dialog.text = "True. You must know a recipe in order to make a potion or an item. Recipes can be bought from merchants or found anywhere. Once you have studied a recipe, you should collect every ingredient needed and do exactly what is written there\n Use your alchemy tools, find or buy a mortar and pestle, look for a crucible; alas, I don't possess an extra one to give you. Herbs, spirits, potions, minerals, garbage – everything will do, provided you have the right recipe and tools.";
			link.l1 = "Very interesting. And how much do you want for this kit?";
			link.l1.go = "alchemy_4";
		break;
		
		case "alchemy_4":
			dialog.text = "Twenty thousand pesos. This is a very good kit and it will pay for itself very quickly.";
			link.l1 = "You're mocking me, aren't you? A handbag with glassware for the price of a lugger? No, I'll pass.";
			link.l1.go = "alchemy_exit";
			if (sti(pchar.money) >= 20000)
			{
				link.l2 = "I agree. I think it will be interesting to try making something with my own hands.";
				link.l2.go = "alchemy_5";
			}
		break;
		
		case "alchemy_5":
			AddMoneyToCharacter(pchar, -20000);
			Log_Info("You've got the alchemist's kit.");
			GiveItem2Character(pchar, "alchemy_tool");
			PlaySound("interface\important_item.wav");
			dialog.text = "You won't regret this purchase, I am absolutely sure. It is definitely more profitable to make potions yourself as you need them, rather than visiting herbalists' stalls to buy everything piece by piece. Besides, it will not always be possible to buy everything you need. ";
			link.l1 = "Let's learn. I think I can do it!";
			link.l1.go = "alchemy_6";
		break;
		
		case "alchemy_6":
			DialogExit();
			PlaySound("interface\notebook.wav");
			Log_Info("In order to make your own herbs and amulets you must have the Alchemy skill!");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("You are a "+GetSexPhrase("Thief, mister! Guards, seize him","Thief, girl! Guards, seize her")+"!!!","Just look at that! The moment I was lost in contemplation, you decided to check my chest! Thief! Catch the thief!!!","Guards! Robbery! Catch the thief!!!");
			link.l1 = "Damn it!";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}

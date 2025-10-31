// диалоги по квесту Цена чахотки
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	string sStr;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (pchar.questTemp.Consumption == "final")
			{
				dialog.text = "Captain! You went to sea, I heard! What happened? Did you find out anything? Please, tell me, spit it out!";
				if (CheckAttribute(pchar, "questTemp.Consumption.TakeMoney"))
				{//взял деньги
					link.l1 = "No, my beauty, this raid was carried out at the request of His Grace, the governor. I am very sorry, but Angelo died in the casemates of the fort - there is no doubt about that now. Stand firm! ";
					link.l1.go = "Waitress";
				}
				else
				{//убил Хуана
					if (CheckAttribute(pchar, "questTemp.Consumption.KillJuan"))
					{
						link.l1 = "You were right. Your brother was kidnapped. The Commandant had been selling prisoners like cattle to a slaver nicknamed Consumption. But I caught up with his ship, and now he is lying on the bottom, and your brother Angelo will come ashore soon. Unfortunately, I do not have as many longboats as needed for all passengers to be delivered ashore at once. ";
						link.l1.go = "Waitress_2";
					}
					else
					{//отпустил Хуана
						link.l1 = "You were right. Your brother was kidnapped. The Commandant had been selling prisoners like cattle to a slaver nicknamed Consumption. But I caught up with his ship; although I failed to kill that bastard, your brother Angelo will come ashore soon. Unfortunately, I do not have enough longboats to bring all the passengers ashore at once. ";
						link.l1.go = "Waitress_2";
					}
					sld = characterFromId("ConAndjelo");
					sld.lifeday = 0;
					RemovePassenger(Pchar, sld);
				}
			}
			else
			{
				dialog.text = "Did you manage to find out anything about Angelo's fate, captain?";
				link.l1 = "Not yet. But I think I will have news soon. You just need to wait. ";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		case "without_moneysss": // лесник  если Гг нажрался..сволочь:D:D:D
		    dialog.text = "Señor, you promised to find my brother... Why are you wasting time drinking here?";
			link.l1 = "Ohh... Yeah, right... hic... Relax, lass... Jesus is in control... 'slurp'... Jesus is in control. I'm already gone... hic...";
			link.l1.go = "exit";
		break;
		
		case "Servant":
			dialog.text = "Good afternoon, señor. What's your business here?";
			link.l1 = "I've brought a dispatch for señor commandant, but I should give it to him personally.";
			link.l1.go = "Servant_1";
		break;
		
		case "Servant_1":
			dialog.text = "Then you go and look for him in the fort.";
			link.l1 = "This dispatch is too important and not for soldiers' eyes or ears. Maybe I came too early, but I can wait for him here. Trust me, it is very important!";
			link.l1.go = "Servant_2";
		break;
		
		case "Servant_2":
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) < 40)
			{
				notification("Skill Check Failed (40)", SKILL_SNEAK);
				dialog.text = "Señor Commandant usually warns me about all important matters that require a change in routine... You know, actually, he did warn me about this particular case.";
				link.l1 = "And what did he say?";
				link.l1.go = "Servant_3";
			}
			else
			{
				notification("Skill Check Passed", SKILL_SNEAK);
				dialog.text = "Alright, I believe you. And I will believe you even more when señor commandant arrives to confirm your words. But until then, I will constantly keep an eye on you.";
				link.l1 = "You can watch me as much as you like...";
				link.l1.go = "Servant_4";
			}
		break;
		
		case "Servant_3":
			dialog.text = "He told me to call the garrison guards in such cases. But we'll probably manage by ourselves. Boys! Let's gut him!";
			link.l1 = "Fuck!";
			link.l1.go = "Servant_fight";
		break;
		
		case "Servant_4":
			DialogExit();
			NextDiag.CurrentNode = "Servant_repeat";
			LAi_SetOwnerType(npchar);
			chrDisableReloadToLocation = false;
		break;
		
		case "Servant_repeat":
			dialog.text = "What else do you want? Have you decided to give me the message?";
			link.l1 = "No, I will wait for the commandant...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Servant_repeat";
		break;
		
		case "Servant_fight":
			int iRank = sti(pchar.rank)+5;
			int iScl = 15 + 2*sti(pchar.rank);
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			chrDisableReloadToLocation = true;
			for (i=9; i<=11; i++)
			{	
				sld = GetCharacter(NPC_GenerateCharacter("Conservant_"+i, "citiz_"+i, "man", "man", iRank, SPAIN, -1, true, "quest"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_10", "pistol1", "bullet", iScl*2);
				DeleteAttribute(sld, "SaveItemsForDead");
				DeleteAttribute(sld, "DontClearDead");
				LAi_SetWarriorType(sld);
				ChangeCharacterAddressGroup(sld, "PortSpein_houseF2", "goto", "goto5");
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Consumption_AfterHouseFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		//попытка залезть в сундук
		case "Man_FackYou":
			dialog.text = "You are a thief! Or perhaps a spy? Guys, downstairs, quickly!";
			link.l1 = "Gah, devil!";
			link.l1.go = "Servant_fight";
		break;
		
		case "Sergio":
			dialog.text = "Excuse me, may I speak with you?";
			link.l1 = "To be honest, I'm in a hurry. What do you want?";
			link.l1.go = "Sergio_1";
		break;
		
		case "Sergio_1":
			dialog.text = "I overheard that you are asking around about a man named Juan and a disease in our prison...";
			link.l1 = "Indeed I did... could you explain yourself?";
			link.l1.go = "Sergio_2";
		break;
		
		case "Sergio_2":
			dialog.text = "Easy, easy! Calm down and don't touch your sword! We're on the same side here! I don't know why you would care about our problems, but this must be stopped! I cannot keep silent any longer!";
			link.l1 = "Keep silent? About what? What do you know about consumption?";
			link.l1.go = "Sergio_3";
		break;
		
		case "Sergio_3":
			dialog.text = "I know a lot, if not everything, and I will explain myself – but not here. Let's meet in the evening when the lights are out. I am a medical assistant, so I am allowed to leave the fort. We will meet beyond the town gates, and I will tell you everything. I beg you – stop asking questions before you attract their attention, if you haven't already... I have to go now. Remember, at night, beyond the town gates.";
			link.l1 = "Alright, I'll be there. Hey! Wait...";
			link.l1.go = "Sergio_4";
		break;
		
		case "Sergio_4":
			DialogExit();
			AddQuestRecord("Consumption", "8");
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "none", "", "", "OpenTheDoors", -1);
			pchar.quest.Consumption3.win_condition.l1 = "location";
			pchar.quest.Consumption3.win_condition.l1.location = "PortSpein_Exittown";
			pchar.quest.Consumption3.win_condition.l2 = "Hour";
			pchar.quest.Consumption3.win_condition.l2.start.hour = 0;
			pchar.quest.Consumption3.win_condition.l2.finish.hour = 3;
			pchar.quest.Consumption3.function = "Consumption_MeetSergio";
			pchar.quest.Consumption4.win_condition.l1 = "Timer";
			pchar.quest.Consumption4.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Consumption4.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Consumption4.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Consumption4.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Consumption4.function = "Consumption_FailSergio";
			locations[FindLocation("PortSpein_Exittown")].DisableEncounters = true; //энкаутеры закрыть
			LAi_LocationDisableOfficersGen("PortSpein_Exittown", true);//офицеров не пускать
		break;
		
		case "Sergio_5":
			dialog.text = "Thank God, you are here... I hope you weren't followed?";
			link.l1 = "Why? You are too suspicious, perhaps even more than señor commandant is, so you'd better get down to business... What do you know about Juan?";
			link.l1.go = "Sergio_6";
		break;
		
		case "Sergio_6":
			dialog.text = "My name is Sergio Saldo. I serve as a medical assistant at our fort and...";
			link.l1 = "";
			link.l1.go = "Sergio_6_1";
		break;
		
		case "Sergio_6_1":
			dialog.text = "";
			link.l1 = "Wait! Did you hear that?";
			link.l1.go = "Sergio_7";
			Play3DSound("lomanie_vetki", -33.25, 1.00, 3.73)
		break;
		
		case "Sergio_7":
			dialog.text = "What?! Where?";
			link.l1 = "Shit, we are not alone here... Who did you bring with you, scum?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Consumption_CreateBandits");
		break;
		
		case "Bandit":
			dialog.text = "They've spotted us! You take the doc, and I'll take the other one!";
			link.l1 = "...";
			link.l1.go = "Bandit_1";
		break;
		
		case "Bandit_1":
			DialogExit();
			sld = characterFromId("Sergio");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			for (i=1; i<=3; i++)
			{	
				sld = characterFromId("Conbandit_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Conbandit_AfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Sergio_8":
			dialog.text = "Put away your sword, it's over! You've seen for yourself now that they tried to kill me too!";
			link.l1 = "Well, it seems too sophisticated for foul play - so, you are not with them. Where were we? You are a prison doctor, aren't you?";
			link.l1.go = "Sergio_9";
		break;
		
		case "Sergio_9":
			dialog.text = "Yes. I serve as the prison doctor. I studied medicine when I was young, and there are not many educated people here. That's why I know better than anyone what's going on in the prison!";
			link.l1 = "What's going on then? What about the prisoners? Do you know anything about them suddenly disappearing?";
			link.l1.go = "Sergio_10";
		break;
		
		case "Sergio_10":
			dialog.text = "Our commandant sells them... sells them like cattle to a slaver named Juan. He chooses those who won't be missed - paupers, sailors from random ships. And then they suddenly 'die of consumption' - you can figure out the rest...";
			link.l1 = "That Juan is human, after all! What do you know about him?";
			link.l1.go = "Sergio_11";
		break;
		
		case "Sergio_11":
			dialog.text = "A bit. He used to do his dirty business in Morocco along with Berber pirates, he likes to tell stories about those times when he pays us a visit. That was the place where he got his nickname - Consumption. Don't want to think about its origins\nHe comes here every month and takes all prisoners aboard.";
			link.l1 = "'Consumption!' And they accused me of being cynical! So that's why... That señor commandant of yours is a real jerk!";
			link.l1.go = "Sergio_12";
		break;
		
		case "Sergio_12":
			dialog.text = "As I understand it, you need someone from among the missing prisoners, otherwise how would you know about this story, am I right? If so, you should hurry: tonight is the last night this month. I have already signed the papers stating the death of three more people, and Juan will weigh anchor tomorrow before noon, when he receives them!";
			link.l1 = "What have you signed? I don't quite follow you...";
			link.l1.go = "Sergio_13";
		break;
		
		case "Sergio_13":
			dialog.text = "I had to do it - as I had been doing for several months already! That is why I came here to stop this. Do you know how Doctor Pinero died? The one who had treated prisoners before me?";
			link.l1 = "I believe I was told he died of consumption, did he not? So, you are forced into it. That is logical – but why did no one contact the authorities regarding this matter?";
			link.l1.go = "Sergio_14";
		break;
		
		case "Sergio_14":
			dialog.text = "And who will believe this? I don't possess any proof, and those soldiers who are supposed to guard the prisoners are being generously paid, so they wouldn't care even if they were selling people to the Caribs as a meal\nNobody gives a damn about prisoners, and that is an ace in the commandant's hand. But you can stop this, at least for some time, by eliminating Juan!";
			link.l1 = "As far as I understand, those men ashore were his, weren't they? How can I find him?";
			link.l1.go = "Sergio_15";
		break;
		
		case "Sergio_15":
			dialog.text = "You have probably caught someone's attention with your questions... I told you to be more careful! But that is not important now. I know nothing about Juan's ship, but prisoners are always sent to Galera Point, which is in the northern part of the island. I suppose the slaver's ship should be nearby and you might catch up with him. His messengers mentioned today that he was going to sail away tomorrow at noon.";
			if (!CheckCharacterItem(pchar, "letter_consumption"))
			{
				link.l1 = "Thank you, Sergio, you are a true officer and a man of honour. I will weigh anchor right now, and I will find this filthy ship. You need to get back to the fort before they start looking for you.";
				link.l1.go = "Sergio_16";
			}
			else
			{
				link.l1 = "Well, that's all I need to know. I have to raise anchor right now if I don't want to search for that 'Consumption' across the entire New World. Meanwhile, you can study this.";
				link.l1.go = "Sergio_17";
			}
		break;
		
		case "Sergio_16":
			dialog.text = "Good luck, captain! Don't worry about me - the most important thing is to stop this, at least for a while. I wish you luck!";
			link.l1 = "My cannons are the best cure for sickness and wickedness. I swear that all prisoners will be ashore before dawn – and Juan's ship will rest on the seabed!";
			link.l1.go = "Sergio_19";
		break;
		
		case "Sergio_17":
			RemoveItems(PChar, "letter_consumption", 1);
			Log_Info("You have given the letter");
			PlaySound("interface\important_item.wav");
			dialog.text = "What is it? Here is the colonel's name and a monogram 'J'? Incredible! Where did you get this from?";
			link.l1 = "You'd better not know that, but I trust you'll use it in the best way possible.";
			link.l1.go = "Sergio_18";
		break;
		
		case "Sergio_18":
			dialog.text = "I will, I swear by all that is holy! The colonel will go to the gallows before the end of the month! I will personally take care of that!";
			link.l1 = "I am afraid that it will end with a disciplinary punishment, which, as I see it, will not be the first in his life. Maybe it's better to shoot that cur? It's a very effective remedy... I have to go now - I don't want to keep 'Consumption' waiting.";
			link.l1.go = "Sergio_19";
		break;
		
		case "Sergio_19":
			DialogExit();
			AddQuestRecord("Consumption", "11");
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1);
			pchar.quest.Consumption5.win_condition.l1 = "location";
			pchar.quest.Consumption5.win_condition.l1.location = "Trinidad";
			pchar.quest.Consumption5.function = "Consumption_CreateJuan";
			pchar.quest.Consumption6.win_condition.l1 = "HardHour";
			pchar.quest.Consumption6.win_condition.l1.hour = 13;
			pchar.quest.Consumption6.function = "Consumption_FailJuan";
			// Сержио теперь наш друг и будет торговать смолами
			SetFunctionTimerCondition("Oil_PrepareSergio", 0, 0, 20, false); // таймер
		break;
		
		// генератор торговли смолами
		case "Sergio_20":
			dialog.text = "Oh, what a lucky meeting! Señor "+GetFullName(pchar)+"! I am so glad to see you!";
			link.l1 = "Señor Sergio! I did not expect to meet you! How are you? How's the good old commandant?";
			link.l1.go = "Sergio_21";
		break;
		
		case "Sergio_21":
			dialog.text = "I am fine, and señor commandant has gone to Los-Teques mines - his filthy machinations with Juan Consumption have been revealed.";
			link.l1 = "Mines?! Upon my soul! I never thought that justice would be served in his case...";
			link.l1.go = "Sergio_22";
		break;
		
		case "Sergio_22":
			dialog.text = "Ah, if only it were, captain... He was just transferred and demoted. He serves at the garrison now, and he wasn't even stripped of his officer rank. Well, at least San Jose got rid of this scum.";
			link.l1 = "Well, so far so good. Though I expected more.";
			link.l1.go = "Sergio_23";
		break;
		
		case "Sergio_23":
			dialog.text = "Me too... But let's forget about the scum - he doesn't deserve to be talked about. Señor, as soon as I heard your ship was about to enter the port, I hurried to the pier with all haste. I have a deal for you.";
			link.l1 = "Really? I'm listening.";
			link.l1.go = "Sergio_24";
		break;
		
		case "Sergio_24":
			if (startHeroType == 1) sStr = "French";
			if (startHeroType == 2) sStr = "Spanish";
			if (startHeroType == 3) sStr = "English";
			if (startHeroType == 4) sStr = "English";
			dialog.text = "Captain, you seem to be a man who can be trusted. Another very significant thing is that you are "+sStr+" and you have your own ship. I suggest we conclude a trade agreement.";
			link.l1 = "Sounds promising! What kind of agreement?";
			link.l1.go = "Sergio_25";
		break;
		
		case "Sergio_25":
			dialog.text = "We'd better discuss this somewhere else – at the lighthouse, in the keeper's hut. He's an old friend of mine, and I trust him. Come to the lighthouse at San Jose today or tomorrow. I will be waiting for you there. I'm confident you'll find my proposal most interesting!";
			link.l1 = "Alright, señor Sergio. I'll see you there!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Oil_SergioRuntoMayak");
		break;
		
		case "Sergio_26":
			chrDisableReloadToLocation = true;//закрыть локацию
			pchar.quest.Oil_SetSergioToMayakOver.over = "yes"; //снять прерывание
			dialog.text = "Welcome again, señor. Let me explain this matter to you. ";
			link.l1 = "I am all ears. ";
			link.l1.go = "Sergio_27";
		break;
		
		case "Sergio_27":
			dialog.text = "As you may already know, I am not only a soldier, but also a doctor. Why? Because I am a well-educated man. My education kept me from wasting my time here on women and drink. Instead, I have organised several expeditions and managed to find a deposit of resin not far from here\nThis is a resource of strategic importance; this island is the only place where you can find the special resin used to build solid and lasting vessels\nA governor and a commandant ordered me to sell all the resin to the Spanish navy\nThe problem is, they pay me only half its market price and I can't sell it anywhere else. Therefore, I offer you the chance to buy it from me. It is a very important commodity and very hard to come by.";
			link.l1 = "What are the terms of our agreement? ";
			link.l1.go = "Sergio_28";
		break;
		
		case "Sergio_28":
			dialog.text = "According to my calculations, I can collect 60 barrels per month without arousing suspicion. Let's make a deal – on the fifth of each month, I'll visit this lighthouse to have a drink with my friend. Come and join us if you want to buy the resin. Ten golden doubloons per barrel.\nYou pay for the whole batch and take it all at once. No pressure, it's up to you. So, do we have a deal?";
			link.l1 = "Sounds like a damn good deal to me! Of course, it's a deal!";
			link.l1.go = "Sergio_29";
		break;
		
		case "Sergio_29":
			dialog.text = "Wonderful. Then on the fifth of each month I will drink a bottle of Canarian wine with my old friend, the keeper, and we will wait for you.";
			link.l1 = "Fine. Let's do it that way.";
			link.l1.go = "Sergio_30";
		break;
		
		case "Sergio_30":
			dialog.text = "I am glad that we have come to an agreement. See you, captain!";
			link.l1 = "Good luck in your resin business, señor!";
			link.l1.go = "Sergio_31";
		break;
		
		case "Sergio_31":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5);
			pchar.questTemp.OilTrade = "true";
			pchar.quest.Oil_fail.win_condition.l1 = "NPC_Death";
			pchar.quest.Oil_fail.win_condition.l1.character = "Sergio";
			pchar.quest.Oil_fail.function = "Oil_TradeFail";
			AddQuestRecordInfo("Unique_Goods", "4");
		break;
		
		case "oil_trade":
			dialog.text = "Hello, señor captain! You have come for a batch of resin, as I suppose.";
			link.l1 = "That's right, señor Sergio. Is everything ready?";
			link.l1.go = "oil_trade_1";
			link.l2 = "Señor Sergio, I am in no mood for trade. Maybe later.";
			link.l2.go = "oil_trade_exit";
		break;
		
		case "oil_trade_exit":
			DialogExit();
			NextDiag.CurrentNode = "oil_trade";
		break;
		
		case "oil_trade_1":
			if (CheckAttribute(pchar, "questTemp.UpgradeOil"))
			{
				dialog.text = "Yes. Do you have 2550 doubloons with you?";
				if (PCharDublonsTotal() >= 2550)
				{
					link.l1 = "Sure. Here you are.";
					link.l1.go = "oil_trade_2";
				}
				else
				{
					link.l1 = "Tough luck! I've left the money on my ship. I'll bring it here at once!";
					link.l1.go = "oil_trade_exit";
				}
			}
			else
			{
				dialog.text = "Yes. Do you have six hundred doubloons with you?";
				if (PCharDublonsTotal() >= 600)
				{
					link.l1 = "Sure. Here you are.";
					link.l1.go = "oil_trade_2";
				}
				else
				{
					link.l1 = "Tough luck! I left the money on my ship. I'll bring it here at once!";
					link.l1.go = "oil_trade_exit";
				}
			}
			if(sti(pchar.questTemp.SergioOil) >= 1 && !CheckAttribute(pchar, "questTemp.SergioOilBlock")) // увеличить объём поставок смолами
			{
				link.l4 = "Señor Sergio, I want to buy more resin. Could you provide batches, say, five times larger?";
				link.l4.go = "UpgradeOil";
			}
			if(sti(pchar.questTemp.SergioOil) >= 1 && CheckAttribute(pchar, "questTemp.SergioOilPotom") && PCharDublonsTotal() >= 3000) // увеличить объём поставок смолами, если в первый раз не принесли
			{
				link.l4 = "Here, as I promised, Señor Sergio, three thousand doubloons, as you requested. I'm confident that with your foresight and my investment, this venture will bring considerable profit to both of us.";
				link.l4.go = "UpgradeOil_Agreed";
			}
		break;
		
		case "oil_trade_2":
			chrDisableReloadToLocation = true;//закрыть локацию
			if (CheckAttribute(pchar, "questTemp.UpgradeOil")) RemoveDublonsFromPCharTotal(2550);
			else RemoveDublonsFromPCharTotal(600);
			PlaySound("interface\important_item.wav");
			dialog.text = "It is a pleasure to deal with you, captain. My people will help you load the barrels onto your ship.";
			link.l1 = "Thank you!";
			link.l1.go = "oil_trade_3";
		break;
		
		case "oil_trade_3":
			dialog.text = "The deal still stands. Should you need another batch, come back in a month.";
			link.l1 = "Alright, Sergio. See you.";
			link.l1.go = "oil_trade_4";
		break;
		
		case "oil_trade_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5);
			if (CheckAttribute(pchar, "questTemp.UpgradeOil")) AddCharacterGoods(pchar, GOOD_OIL, 300);
			else AddCharacterGoods(pchar, GOOD_OIL, 60);
			AddCharacterExpToSkill(pchar, "Commerce", 200);
			pchar.questTemp.SergioOil = sti(pchar.questTemp.SergioOil) + 1; // счётчик покупок
		break;
		
		case "UpgradeOil":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 80)
			{
				dialog.text = "Señor"+GetSexPhrase("","ita")+", your desire to purchase more resin certainly shows trust in our business. However, there's one complication\nWith increased volumes comes a greater risk of attracting the attention of the island authorities, and controlling such shipments requires people and security measures, which, I admit, aren't cheap. If you're willing to add three thousand doubloons to the price, as a one-time payment, I'll hire reliable people who can protect the cargo and prevent information leaks. Then our route will become safer, and I can supply you with three hundred barrels of resin monthly. To compensate for your investment, I'll offer you, as a wholesale buyer, a fifteen percent discount on all future shipments.";
				link.l1 = "Three thousand doubloons to secure the shipments? Señor Sergio, I won't hide it, this price seems incredible – as if you're proposing a conspiracy in the Escorial rather than just securing a cargo of pitch!";
				link.l1.go = "UpgradeOil_1";
				Notification_Skill(true, 60, SKILL_COMMERCE);
			}
			else
			{
				dialog.text = "Señor"+GetSexPhrase("","ita")+", I appreciate your interest, but such large deals require experience and caution. To be honest, your level in trading matters is not yet high enough to handle such a volume. I advise you to gain a bit more experience and return to me when you're ready for larger shipments. Then, perhaps, we can discuss the matter thoroughly.";
				link.l1 = "Very well. We'll return to this question later.";
				link.l1.go = "oil_trade_exit";
				notification("Skill Check Failed (80)", SKILL_COMMERCE);
			}
		break;
		
		case "UpgradeOil_1":
			dialog.text = "Señor"+GetSexPhrase("","ita")+", I understand your concern. But you know security is never cheap, especially with such rare goods. Besides, I'm not only guaranteeing no leaks, but offering a discount that will compensate your investment over time. Isn't that a reasonable compromise?";
			link.l1 = "I admit: in our business, reliability and secrecy are costly, and the discount makes our potential deal somewhat more appealing. But still, three thousand doubloons is an excessive sum. Perhaps you could reduce it somewhat?";
			link.l1.go = "UpgradeOil_2";
		break;
		
		case "UpgradeOil_2":
			dialog.text = "I regret, but half-measures are unacceptable in such matters. Either we ensure full protection, or we risk everything. The sum remains the same, and only this way can I guarantee reliability and confidentiality. You wouldn't want the entire royal fleet chasing first me, then you, would you?";
			if (PCharDublonsTotal() >= 3000)
			{
				link.l1 = "Very well, Señor Saldo, you've convinced me. Security and reliability are worth their price. Three thousand doubloons. Here you are.";
				link.l1.go = "UpgradeOil_Agreed";
			}
			link.l2 = "Señor Saldo, you've convinced me of the necessity of these measures. However, three thousand doubloons is a considerable sum, and I don't have it at the moment. I'll have to wait until I gather the required amount.";
			link.l2.go = "UpgradeOil_4";
			link.l3 = "For such money, one could bribe an entire fleet and all the soldiers on the continent, let alone hire guards for a modest cargo of pitch! I apologize, but I cannot agree to such an offer. Let's leave everything as it is, without excess or additional expenses.";
			link.l3.go = "UpgradeOil_3";
		break;
		
		case "UpgradeOil_Agreed":
			dialog.text = "Well then, señor, I see our trust is mutual. Rest assured: everything will be arranged properly. Now for the details: 300 barrels of resin, as usual, will be waiting for you here at the Trinidad lighthouse on the 5th of each month. You can purchase the entire batch for 2550 doubloons.";
			link.l1 = "Excellent, Señor Sergio. Don't let me down.";
			link.l1.go = "UpgradeOil_Agreed_1";
			RemoveDublonsFromPCharTotal(3000);
			AddQuestRecordInfo("Unique_Goods", "4_1");
			pchar.questTemp.UpgradeOil = true;
			pchar.questTemp.SergioOilBlock = true;
			DeleteAttribute(pchar, "questTemp.SergioOilPotom");
		break;
		
		case "UpgradeOil_Agreed_1":
			dialog.text = "Have no doubt, señor"+GetSexPhrase("","ita")+". Everything will be organised at the highest level, and our joint effort will bear fruit.";
			link.l1 = "See you.";
			link.l1.go = "oil_trade_exit";
		break;
		
		case "UpgradeOil_3":
			DialogExit();
			pchar.questTemp.SergioOilBlock = true;
			NextDiag.CurrentNode = "oil_trade";
		break;
		
		case "UpgradeOil_4":
			dialog.text = "Come back when you have the full sum. I'll be happy to make a new deal with you.";
			link.l1 = "Alright.";
			link.l1.go = "oil_trade_exit";
			pchar.questTemp.SergioOilBlock = true;
			pchar.questTemp.SergioOilPotom = true;
		break;
	// <-- генератор смол
		
		case "Juan_abordage":
			dialog.text = "Who the hell are you!?";
			link.l1 = "My name is "+GetFullName(pchar)+", as for you, Consumption, the devil is waiting for you – and he'll have your soul very soon!";
			link.l1.go = "Juan_abordage_1";
		break;
		
		case "Juan_abordage_1":
			if (CheckAttribute(pchar, "questTemp.Consumption.House"))
			{
				dialog.text = "This ship is about to blow – the fuse is already burning in the powder room – why should we both die? Let's put down our swords. You'll have enough time to get out, and I'll jump overboard – Galera Point is within spitting distance from here. If you want gold, take it! Five hundred doubloons, cash on the nail – and you forget about me, and I forget about you! Deal?";
				link.l1 = "Gold? I started all this not for money, Juan, but for killing the scum, and you are the greatest reward of all.";
				link.l1.go = "Juan_abordage_2";
				link.l2 = "Five hundred doubloons? You're mocking me, Consumption. I reckon you've stashed at least twice that here... Give me a thousand right now and you can go to hell, otherwise...";
				link.l2.go = "Juan_abordage_3";
			}
			else
			{
				dialog.text = "The ship is about to blow up, so I'll have good company. What do you think?";
				link.l1 = "You talk too much, Consumption, get to the point!";
				link.l1.go = "Juan_abordage_5";
			}
		break;
		
		case "Juan_abordage_2":
			dialog.text = "We could have reached an agreement... Eh, whatever!";
			link.l1 = "You took these poor people from their cells, and they could neither resist nor escape. You are a coward, Consumption, and you will die a coward now.";
			link.l1.go = "Juan_abordage_5";
		break;
		
		case "Juan_abordage_3":
			dialog.text = "You've got a good head for business, friend... Here - this is all I have. Not much for a life, though, is it?";
			link.l1 = "Your life isn't worth a bullet, so it seems this is the most profitable bargain of my life. Now get lost.";
			link.l1.go = "Juan_abordage_4";
			TakeNItems(pchar, "gold_dublon", 1000);
			Log_Info("You received 1000 doubloons");
			PlaySound("interface\important_item.wav");
			ChangeCharacterComplexReputation(pchar, "nobility", -10);
			OfficersReaction("bad");
			pchar.questTemp.Consumption.TakeMoney = "true"; //атрибут для диалога
		break;
		
		case "Juan_abordage_4":
			DialogExit();
			chrDisableReloadToLocation = true;
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			Lai_SetPlayerType(pchar);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetImmortal(sld, true);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "ConJuan_AfterFight_1", 10.0);
		break;
		
		case "Juan_abordage_5":
			dialog.text = "It is a pity that you will not have time to save everyone and kill me, will you? The fuse is burning, and time is running out...";
			link.l1 = "Damn it! I have to get these people out of here... Get lost, scum – you'll get what you deserve sooner or later!";
			link.l1.go = "Juan_abordage_4";
			link.l2 = "I will try anyway...";
			link.l2.go = "Juan_abordage_6";
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			OfficersReaction("good");
			sld = GetCharacter(NPC_GenerateCharacter("ConAndjelo", "citiz_9", "man", "man", 5, SPAIN, -1, true, "quest"));
			sld.name = "Angelo";
			sld.lastname = "";
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
		break;
		
		case "Juan_abordage_6":
			//LAi_SetCurHPMax(NPChar);
			//LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle("ConJuan_AfterFight_2"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Consumption.KillJuan = "true"; //атрибут для диалога
		break;
		
		case "Waitress":
			dialog.text = "Ah... I am speechless... What a nightmare!";
			link.l1 = "Alas, I couldn't do anything. I am sorry, lass. Farewell.";
			link.l1.go = "Waitress_1";
		break;
		
		case "Waitress_1":
			DialogExit();
			AddQuestRecord("Consumption", "16");
			AddQuestUserData("Consumption", "sSex", GetSexPhrase("",""));
			Consumption_Close();
		break;
		
		case "Waitress_2":
			dialog.text = "Unbelievable! You... did you really save him? I have no idea how to thank you.";
			if (CheckAttribute(npchar, "quest.Consumption.sex"))
			{
				link.l1 = "I can imagine that, beauty. But my part of the deal is done now - just one little thing remains.";
				link.l1.go = "Waitress_3";
			}
			link.l2 = "Duty called – and I acted. That's it.";
			link.l2.go = "Waitress_5";
			if (CheckAttribute(pchar, "questTemp.Consumption.KillJuan")) AddQuestRecord("Consumption", "18");
			else AddQuestRecord("Consumption", "17");
		break;
		
		case "Waitress_3":
			dialog.text = "I... oh God! You're right. For him, as I promised... Go upstairs to the room - we don't have much time.";
			link.l1 = "Let's hurry, then!";
			link.l1.go = "Waitress_4";
		break;
		
		case "Waitress_4"://благодарность натурой
			DialogExit();
			LocatorReloadEnterDisable("PortSpein_tavern", "reload1_back", true); //закрыть таверну
			LocatorReloadEnterDisable("PortSpein_tavern", "reload2_back", false); //открыть комнату
			bDisableFastReload = true;//закрыть переход
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2_back", "PortSpein_tavern_upstairs", "goto", "goto3", "ConsumptionSexWaitress", -1);
			pchar.questTemp.Consumption.Sex = "true";
		break;
		
		case "Waitress_sex":
			dialog.text = "Here I am, my brave caballero! And look what I have brought with me.";
			link.l1 = "Well, well, I am impressed, let's open up that cherry wine! Then we'll open up something else... It's your lucky day after all... Ha-ha!";
			link.l1.go = "Waitress_sex_1";
		break;
		
		case "Waitress_sex_1":
			DialogExit();
			DoQuestCheckDelay("PlaySex_1", 0.1);
		break;
		
		case "Waitress_5":
			if (CheckAttribute(pchar, "questTemp.Consumption.KillJuan"))
			{
				dialog.text = "You are a true knight! Caballero! Here - don't take it as an insult, but I want you to have this. I collected this money to ransom Angelo, but now it is no longer important! Please, do not refuse - take it!";
				link.l1 = "Well, I will remember your eyes, señorita - they are so much more beautiful when they shine with tears of happiness and not pain. I accept your gift. Goodbye, and good luck to you and Angelo.";
				link.l1.go = "Waitress_6";
				AddMoneyToCharacter(pchar, 5000);
			}
			else
			{
				dialog.text = "You are a true knight! Caballero! I will tell everyone! I will always remember you!";
				link.l1 = "Well, and I will remember your eyes, señorita - they are so much more beautiful when they shine with tears of happiness and not pain. May you always be happy. Farewell!";
				link.l1.go = "Waitress_6";
			}
		break;
		
		case "Waitress_6":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			Consumption_Close();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

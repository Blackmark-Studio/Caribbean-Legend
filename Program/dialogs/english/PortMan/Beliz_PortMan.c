// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	bool ok;
    int iTest;
    ref rColony;
    string sFrom_sea = "";
    switch (Dialog.CurrentNode)
	{
		case "quests":
			//регата
			if (CheckAttribute(pchar, "questTemp.Regata.Go") && !CheckAttribute(npchar, "quest.regatatalk"))
			{
				dialog.text = "What do you want? A-ha, you are the participant of the regatta! Am I right?";
				link.l1 = "Exactly, mister. I need to get registered here according to the rules.";
				link.l1.go = "Regata_check";
				break;
			}
			//регата
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What kind of questions?", "What do you want, " + GetAddress_Form(NPChar) + "?"), "You've already tried to ask me a question " + GetAddress_Form(NPChar) + "...", "You have been talking about some question for the third time today...",
                          "Look, if you have nothing to tell me about the port's matters then don't bother me with your questions.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I have changed my mind.", "I've got nothing to talk about."), "Nevermind.", "Indeed, the third time already...", "Sorry, but I'm not interested in the port's matters for now.", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Грани справедливости
			if (CheckAttribute(pchar, "questTemp.GS_Portman"))
			{
				link.l1 = "Word has it that someone made an attempt on your life, and you're trying to track down the culprit?";
				link.l1.go = "GS_Portman_1";
			}
			if (CheckAttribute(pchar, "questTemp.GS_NaemnikMertv"))
			{
				link.l1 = "The man who attempted your life has fallen, Mr. "+npchar.lastname+". Nothing threatens you anymore.";
				link.l1.go = "GS_Portman_6";
			}
			//<-- Грани справедливости
		break;

		//регата
		case "Regata_check":
		iTest = FindColony(npchar.city); 
		if (iTest != -1)
		{
			rColony = GetColonyByIndex(iTest);
			sFrom_sea = rColony.from_sea;
		}
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
		{
			bool bRegLugger = sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_LUGGER || sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_CAREERLUGGER;
			if (CheckAttribute(pchar, "questTemp.Regata.Breach") || GetCompanionQuantity(pchar) > 1 || !bRegLugger || pchar.Ship.Name != "Saint Catherine")
			{
			dialog.text = "Hm... You have broken the rules of the regatta and I have to disqualify you. I am sorry. You are not participating in the next voyage. I have already prepared a dispatch to Port-Royal.";
			link.l1 = "Oops... what a pity! But I can't do anything here, you were too vigilant. Farewell!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Regata");
			pchar.quest.Regata_PU.over = "yes"; // mitrokosta снимаем прерывание
			AddQuestRecord("Regata", "45");
			CloseQuestHeader("Regata");
			}
			else
			{
			pchar.questTemp.Regata.FirstTransitionTime = GetPastTime("hour", sti(pchar.questTemp.Regata.StartYear), sti(pchar.questTemp.Regata.StartMonth), sti(pchar.questTemp.Regata.StartDay), stf(pchar.questTemp.Regata.StartTime), GetDataYear(), GetDataMonth(), GetDataDay(), GetTime());//истратил ГГ в часах на 1 переход
			dialog.text = "Let's register: captain "+ GetFullName(pchar) +", ship is "+pchar.Ship.Name+"... the regatta's time in hours is "+sti(pchar.questTemp.Regata.FirstTransitionTime)+". Done, your result is registered, you can continue your way.";
			link.l1 = "Tell me my rank.";
			link.l1.go = "Regata_info";
			}
		}
		else
		{
			dialog.text = "You are here but I don't see your ship. Where is it?";
			link.l1 = "I am sorry, sir. I will transfer my ship to the port immediately.";
			link.l1.go = "exit";
		}
		break;
		
		case "Regata_info":
			int n=1;
			string sTemp, sName, sShip;
			for (int i=1; i <=5; i++)
			{
				if (i==1) sTemp = "a";
				if (i==2) sTemp = "b";
				if (i==3) sTemp = "c";
				if (i==4) sTemp = "d";
				if (i==5) sTemp = "e";
				if (pchar.questTemp.Regata.AdversaryFirstTransition.Time.(sTemp) < sti(pchar.questTemp.Regata.FirstTransitionTime))
				{
					n++;
					sName = pchar.questTemp.Regata.AdversaryName.(sTemp);//имя ближайшего противника
					sShip = pchar.questTemp.Regata.AdversaryShipName.(sTemp);//его корабль
				}
			}
			if (n==1)
			{
			dialog.text = "You are in the lead. Congratulations! Keep it up!";
			link.l1 = "Thanks!";
			link.l1.go = "exit";
			AddQuestRecord("Regata", "4");
			}
			else
			{
				if (n==6)
				{
				dialog.text = "You are the last. You should hurry up.";
				link.l1 = "I am on my way!";
				link.l1.go = "exit";
				AddQuestRecord("Regata", "9");
				}
				else
				{
					if (n==2)
					{
					dialog.text = "You are the second. The leader is "+sName+" on the ship "+sShip+". I suppose that you can still outrun him.";
					link.l1 = "Thanks! I'll be trying!";
					link.l1.go = "exit";
					AddQuestRecord("Regata", "5");
					}
					else
					{
					dialog.text = "You rank is "+n+". Your closest opponent is "+sName+" on the ship "+sShip+".";
					link.l1 = "Thanks!";
					link.l1.go = "exit";
					if (n==3) AddQuestRecord("Regata", "6");
					if (n==4) AddQuestRecord("Regata", "7");
					if (n==5) AddQuestRecord("Regata", "8");
					}
				}
			}
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			npchar.quest.regatatalk = "true";
			pchar.questTemp.Regata.Beliz = "true";//отметка Белиза
			pchar.quest.Regata_Check1.win_condition.l1 = "location";
			pchar.quest.Regata_Check1.win_condition.l1.location = "Cuba1";
			pchar.quest.Regata_Check1.function = "RegataCheck";//проверка 1
			pchar.quest.Regata_Check2.win_condition.l1 = "location";
			pchar.quest.Regata_Check2.win_condition.l1.location = "Cuba2";
			pchar.quest.Regata_Check2.function = "RegataCheck";//проверка 2
			pchar.quest.Regata_Check.win_condition.l1 = "location";
			pchar.quest.Regata_Check.win_condition.l1.location = "Hispaniola2";
			pchar.quest.Regata_Check.function = "RegataCheck";//проверка 3
			pchar.questTemp.Regata.AttackIsland = "Cuba1";
			pchar.questTemp.Regata.AttackNation = SPAIN;
			pchar.quest.Regata_Attack.win_condition.l1 = "location";
			pchar.quest.Regata_Attack.win_condition.l1.location = "Cuba1";
			pchar.quest.Regata_Attack.function = "RegataAttack_Lugger";//первая засада у Сантьяго
			pchar.quest.Regata_Hunter.win_condition.l1 = "location";
			pchar.quest.Regata_Hunter.win_condition.l1.location = "Cuba2";
			pchar.quest.Regata_Hunter.function = "RegataAttack_Hunter";//ДУ у Гаваны
			pchar.questTemp.Regata.Town = "Portpax";
			pchar.quest.Regata_PU.win_condition.l1 = "locator";
			pchar.quest.Regata_PU.win_condition.l1.location = "Portpax_town";
			pchar.quest.Regata_PU.win_condition.l1.locator_group = "reload";
			pchar.quest.Regata_PU.win_condition.l1.locator = "reload10_back";
			pchar.quest.Regata_PU.win_condition.l2 = "Night";
			pchar.quest.Regata_PU.function = "RegataPU_Open";//вход в ПУ ночью
		break;
		//регата
		
		//--> Грани справедливости
		case "GS_Portman_1":
			dialog.text = "The attempt on my life did happen, that much is true. As for the search... it's not quite that. I don't need a fugitive caught — I need his head. Only then will peace return to me.";
			Link.l1 = "Do you have any idea who attacked you and why?";
			Link.l1.go = "GS_Portman_2";
			DelLandQuestMark(npchar);
		break;
		
		case "GS_Portman_2":
			dialog.text = "I... I don't know who he is! I don't know where he came from or why he struck at me. But one thing is clear — he wanted me dead. And now... now I crave his death with just as much fury! Do you understand me?\nSo spare me your pointless questions. Your curiosity means nothing to me — only action can help now. Two hundred doubloons for his head, that's my price. Start the hunt, or stop wasting my time.";
			Link.l1 = "I understand that fear and anger cloud your mind, and I’ll even forgive your tone. But get a grip on yourself. I don't see a line of volunteers to solve your problems, so temper your fire. Two hundred doubloons is acceptable, but before I take the job, I need to know everything.";
			Link.l1.go = "GS_Portman_3";
			Link.l2 = "Your words are just idle prattle, and there are no leads. Searching for someone unknown in the jungle is like looking for a needle in a haystack. I won't waste my time on a pointless hunt. Good luck. You'll surely need it.";
			Link.l2.go = "GS_Portman_End";
		break;
		
		case "GS_Portman_End":
			DialogExit();
			CloseQuestHeader("GS");
			DeleteAttribute(pchar, "questTemp.GS_Portman");
		break;
		
		case "GS_Portman_3":
			dialog.text = "Argh... Forgive me, "+GetAddress_Form(NPChar)+", my nerves are frayed... What exactly do you want to know?";
			Link.l1 = "Did you notice any features that could help identify him? Was he alone, or backed by someone more powerful? The more you tell me, the sooner you'll be able to sleep peacefully.";
			Link.l1.go = "GS_Portman_4";
		break;
		
		case "GS_Portman_4":
			dialog.text = "What foe?! I have no enemies! Never have! I’ve done nothing to deserve death in the middle of the street in broad daylight\nThat villain... he’s just a bitter madman, the kind you find everywhere in these colonial towns\nAs for where to look... I think he’s hiding in the jungle. It's easy to disappear in those cursed woods, but I'm sure he'll head for the grottos or coves — easier to hide there\nAs for appearance, his face was covered with a scarf, a hat on his head, and he carried more weapons than His Majesty’s own guards. There was no time to notice anything else.";
			Link.l1 = "Well, it's not much, but it's enough to begin the search. I'm heading out at once. Keep that gold close — I’ll be back soon.";
			Link.l1.go = "GS_Portman_5";
		break;
		
		case "GS_Portman_5":
			DialogExit();
			AddQuestRecord("GS", "2");
			DeleteAttribute(pchar, "questTemp.GS_Portman");
			
			PChar.quest.GS_Peshera.win_condition.l1 = "location";
			PChar.quest.GS_Peshera.win_condition.l1.location = "Beliz_Cave";
			PChar.quest.GS_Peshera.function = "GS_Peshera";
			locations[FindLocation("Beliz_Cave")].DisableEncounters = true;
			
			PChar.quest.GS_Peshera_pusto.win_condition.l1 = "location";
			PChar.quest.GS_Peshera_pusto.win_condition.l1.location = "Beliz_Cave_2";
			PChar.quest.GS_Peshera_pusto.function = "GS_Peshera_pusto";
		break;
		
		case "GS_Portman_6":
			dialog.text = "Magnificent, "+GetFullName(pchar)+"! Utterly magnificent! You have proven your prowess unmatched. Here lies your reward – two hundred doubloons. Please, take it!";
			Link.l1 = "My thanks to you! But tell me, have you any reason to suspect that the killer was hired by one of your former clients?";
			Link.l1.go = "GS_Portman_7";
			AddItems(pchar, "gold_dublon", 200);
			DelLandQuestMark(npchar);
		break;
		
		case "GS_Portman_7":
			dialog.text = "Former clients?.. What nonsense!... I am an honest man, and my dealings have always been aboveboard! But since you've aided me, I shall share something. Not long ago, pirates came to me\nThey offered money for tips on merchant vessels. I refused, and they hurled threats and curses before storming out. I believe the assassin was their doing. They do not take 'no' kindly.";
			Link.l1 = "In that case, take care of yourself. Who knows how many more hired blades these 'pirates' may send? With that, I must take my leave — business calls.";
			Link.l1.go = "GS_Portman_8";
		break;
		
		case "GS_Portman_8":
			dialog.text = "Wait, Captain. I want to thank you once again. Beyond gold, you've earned my favor. As long as I'm Port Chief here, you may leave any of your ships moored here for any length of time at a fifty percent discount. How does that sound?";
			Link.l1 = "A most generous offer! Thank you once again!";
			Link.l1.go = "GS_Portman_9";
		break;
		
		case "GS_Portman_9":
			dialog.text = "And I thank you once more for your efforts. I'm certain that as long as you keep focused on what matters, your affairs will continue to prosper as they did today. Farewell, Captain.";
			Link.l1 = "Goodbye.";
			Link.l1.go = "GS_Portman_10";
		break;
		
		case "GS_Portman_10":
			DialogExit();
			AddQuestRecord("GS", "4");
			CloseQuestHeader("GS");
			DeleteAttribute(pchar, "questTemp.GS_NaemnikMertv");
			pchar.questTemp.GS_BelizSkidka = true;
		break;
		//<-- Грани справедливости
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

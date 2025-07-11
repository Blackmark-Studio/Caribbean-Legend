// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions do you have?", "How can I help you?"), "You tried to ask me that question not long ago...", "Yup, let me guess... Once again going around in circles?",
                          "Listen, I do the finances here, I don't answer questions...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind...", "I've got nothing to talk about at the moment."), "Umph, where has my memory gone...",
                      "You've guessed it, I'm sorry...", "I understand...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			/* //--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
			{
				link.l1 = "Take a look at these earrings, monsieur. I've found them in the pocket of a bandit in the jungle. This is clearly the work of a fine jeweler which, I'm sure, is not from this wilderness. What do you say?";
                link.l1.go = "Sharlie_junglejew";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskiper")
			{
				link.l1 = "I know that you have a debtor by the name of Folke Deluc. Tell me, how bad is his... delinquency?";
                link.l1.go = "Sharlie";
			}	
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskipermoney")
			{
				link.l1 = "I'm here about Folke Deluc's debt.";
                link.l1.go = "Sharlie_repeat";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskipercaptive")
			{
				link.l1 = "I've completed your assignment, monsieur. Here is your... Spanish friend.";
                link.l1.go = "Sharlie_14";
			}
			//<-- Бремя гасконца */
			
			//--> Миниквест "Делюк" (Делюк снова попал в тюрьму)
			if (CheckAttribute(pchar, "questTemp.Del_Rostovshik"))
			{
				link.l1 = "I'm here about...";
                link.l1.go = "Del_Deluck";
			}
			if (CheckAttribute(pchar, "questTemp.Del_Rostovshik_repeat"))
			{
				dialog.text = "Did you bring 100 doubloons?";
				if (PCharDublonsTotal() >= 100)
				{
					link.l1 = "Here's your money for my officer...";
					link.l1.go = "Del_Deluck_5";
				}
				link.l2 = "No, I'm still thinking.";
				link.l2.go = "exit";
			}
			//<-- Миниквест "Делюк"
		break;
		
		case "Sharlie":
			DelLandQuestMark(npchar);
			dialog.text = "And why do you care about it, may I ask?";
			link.l1 = "I need this man free, not behind bars. And as far as I've been informed, until this debt is returned to you, he will not be released, I'm interested in paying off this debt.";
			link.l1.go = "Sharlie_1";
		break;
		
		case "Sharlie_1":
			dialog.text = "Aha, that changes everything. I'm also interested in my money returning back to me... This Folke Deluc is a strange fellow. He borrowed a relatively small amount of money - five thousand pesos. He just didn't want to give it back and started hiding away. In the end, interest ran all the way up to the price of the original debt and he found himself behind bars.";
			link.l1 = "It follows that, his debt has currently accumulated at ten thousand?";
			link.l1.go = "Sharlie_2";
		break;
		
		case "Sharlie_2":
			dialog.text = "Ten thousand four hundred fifty pesos exactly, monsieur. So his freedom is priced at this amount. You're willing to pay it to me? I'm a little surprised...";
			if (sti(pchar.money) >= 10450)
			{
				link.l1 = "Don't be surprised. Here's the money.";
				link.l1.go = "Sharlie_3";
			}
			link.l2 = "Hm... A hefty sum indeed. Listen, monsieur, maybe you and I should try to make a deal? For instance, you have something that I would be able to take care of and you could evaluate my favor at these ten thousand five hundred...";
			if (CheckAttribute(pchar, "questTemp.Sharlie.FastStart")) link.l2.go = "Sharlie_5x";
			else link.l2.go = "Sharlie_5"; // Addon 2016-1 Jason пиратскаЯ линейка 1
		break;
		
		case "Sharlie_3":
			AddMoneyToCharacter(pchar, -10450);
			dialog.text = "Yes, it appears that you really need this sailor if you're willing to shell out such an amount of money for him. Anyway, it's none of my business, is it monsieur? Here is his a bill of debt, now you're entitled to his debt and have right to ask money from him. Well, and of course, petition for his release from prison.";
			link.l1 = "That's exactly what I wanted. Goodbye, "+npchar.name+"!";
			link.l1.go = "Sharlie_4";
		break;
		
		case "Sharlie_4":
			DialogExit();
			Log_Info("You have received a bill of debt");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "letter_open");
			ChangeItemDescribe("letter_open", "itmdescr_letter_open_usurer");
			pchar.questTemp.Sharlie = "freeskiper";
			AddLandQuestMark(characterFromId("FortFranceJailOff"), "questmarkmain");
		break;
		
		case "Sharlie_5x": // Addon 2016-1 Jason пиратскаЯ линейка 1
			dialog.text = "A favor? Alas, I don't need any favors from you. At least for now.";
			link.l1 = "Pity. I should bring the money for Folke then. Bye!";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "bankskipermoney";
		break;
		
		case "Sharlie_5":
			dialog.text = "Favor? Hm... You know, monsieur, I would've given a negative answer if you had come yesterday, but now... yes, I have something that needs to be taken care of, but I warn you that it's quite dangerous.";
			link.l1 = "Dangerous for what?";
			link.l1.go = "Sharlie_6";
		break;
		
		case "Sharlie_6":
			dialog.text = "For your precious life, of course. So think about it, before agreeing and decide whether you're willing to do something like that or not.";
			link.l1 = "Monsieur, danger isn't any stranger to me. I've already been in dangerous situations so many times. So, let's get to the details. As long as it doesn't involve taking out the entire fort's garrison single-handedly, maybe I'll be able to accomplish what you're so mysteriously alluding to.";
			link.l1.go = "Sharlie_7";
		break;
		
		case "Sharlie_7":
			dialog.text = "Fine. Listen then. Tonight, several pirates and a prisoner will leave pirate den of Le Francois and will walk to the Le Marin cove. The prisoner is a Spanish officer, and a great expert of fortification engineering. Brits intend to use him for their own purposes, so they will send a warship to pick the man up from the cove\nThe officer is my old friend and I don't want him to end up as an English captive. I can't ask local authorities to help me because we are at war with Spain. If I had more time, I would hire men capable of retaking the spaniard... sorry, of retaking my friend, but alas!\nYou are the only man I can trust this job. You must go to Le Marin cove and... persuade pirates to give the prisoner to you. I doubt that they will show much cooperation, so it's up to you.";
			link.l1 = "How many pirates will be in the convoy?";
			link.l1.go = "Sharlie_8";
		break;
		
		case "Sharlie_8":
			dialog.text = "I don't know. Maybe two people, maybe three or four. So, what would you say?";
			link.l1 = "I've already told you 'danger isn't any stranger to me' and I know from which side to hold onto a sword.";
			link.l1.go = "Sharlie_10";
			link.l2 = "Hm. You're right, it's dangerous. I won't attack a crew of pirates all alone.";
			link.l2.go = "Sharlie_9";
		break;
		
		case "Sharlie_9":
			dialog.text = "That's your decision. If you believe that you're not up to this job, then you'd better refuse right away. Then I'll be waiting for Deluc's debt money.";
			link.l1 = "All right. I'll bring the money for him. See you later!";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "bankskipermoney";
		break;
		
		case "Sharlie_10":
			dialog.text = "Very well. Glad to hear that. Then you should go to Le Marin cove, the pirates will be there from seven p.m. until four a.m. Don't miss them! And don't even think to use a ship! Such actions will scare them off, walk there through the jungle!\nBring the prisoner to me when you'll find him, I'll keep the door open. I recommend to wait until one a.m. before returning to the city because you need to avoid guards' attention. Be careful and good luck!";
			link.l1 = "Thank you! I'll definitely need some luck...";
			if (CheckAttribute(pchar,"equip."+GUN_ITEM_TYPE)) link.l1.go = "Sharlie_13";
			else link.l1.go = "Sharlie_11";
		break;
		
		case "Sharlie_11":
			dialog.text = "Wait a minute! I see you don't even have a gun. Take one of mine. I've also got several bullets for it. I think it'll come in handy.";
			link.l1 = "Yes, this will definitely come in handy. Thank you, monsieur.";
			link.l1.go = "Sharlie_12";
		break;
		
		case "Sharlie_12":
			Log_Info("You have received a combat pistol");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "pistol1");
			TakeNItems(pchar, "bullet", 20);
			TakeNItems(pchar, "gunpowder", 20);
			dialog.text = "And now go, may God help you!";
			link.l1 = "...";
			link.l1.go = "Sharlie_13";
		break;
		
		case "Sharlie_13":
			DialogExit();
			pchar.quest.Sharlie_captive_Tut.win_condition.l1 = "location";
			pchar.quest.Sharlie_captive_Tut.win_condition.l1.location = "Shore39";
			pchar.quest.Sharlie_captive_Tut.function = "Tutorial_Rest_Delay";
			pchar.quest.Sharlie_captive.win_condition.l1 = "HardHour";
			pchar.quest.Sharlie_captive.win_condition.l1.hour = 19.00;
			pchar.quest.Sharlie_captive.function = "Captive_Timer";
			SetFunctionTimerCondition("Captive_CreatePiratesOver", 0, 0, 1, false);
			AddQuestRecord("SharlieD", "1");
			pchar.questTemp.Sharlie = "bankskiperfight";
			pchar.questTemp.Sharlie.Captive = "true";
			pchar.questTemp.Sharlie.Captive.Name = GetFullName(npchar);
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			// Rebbebion, новые марки до места назначения
			QuestPointerToLoc("fortfrance_town", "reload", "gate_back");
			QuestPointerToLoc("fortfrance_exittown", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_01", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_02", "reload", "reload2_back");
			QuestPointerToLoc("martinique_jungle_03", "reload", "reload2_back");
		break;
		
		case "Sharlie_14":
			pchar.quest.Sharlie_captive1.over = "yes";
			pchar.quest.Sharlie_captive2.over = "yes";
			pchar.quest.Sharlie_captive3.over = "yes";
			// Rebbebion, новые марки до места назначения
			QuestPointerDelLoc("shore39", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_03", "reload", "reload2_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload2_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload1_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload1_back");
			QuestPointerDelLoc("fortfrance_town", "reload", "reload8_back");
			DelLandQuestMark(npchar);
			ref sld = characterFromId("CaptiveSpain");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", 5.0);
			sld.lifeday = 0;
			SetNationRelation2MainCharacter(FRANCE, RELATION_FRIEND);
			DeleteAttribute(pchar, "questTemp.Sharlie.Captive");
			dialog.text = "Wonderful! I'm very pleased that you were able to handle it successfully. I suppose I need not know the details of the operation, do I?  So, my dear Spanish guest may now feel himself safe in my home...";
			link.l1 = "What about Folke Deluc's debt?";
			link.l1.go = "Sharlie_15";
		break;
		
		case "Sharlie_15":
			dialog.text = "Of course, yes. Take his bill of debt, now you're entitled to his debt and have right to ask money from him. Well, and of course, petition for his releasing from prison. Have I done everything as promised?";
			link.l1 = "Yes, monsieur. Everything's in strict according to the agreement. Now allow me to take my leave.";
			link.l1.go = "Sharlie_4";
			AddQuestRecord("SharlieD", "7");
			CloseQuestHeader("SharlieD");
			DeleteAttribute(pchar, "questTemp.Sharlie.Captive");
		break;
		
		case "Sharlie_repeat":
			dialog.text = "So, are you ready to pay his debt?";
			if (sti(pchar.money) >= 10450)
			{
				link.l1 = "Yes. Here's the money.";
				link.l1.go = "Sharlie_3";
			}
			link.l2 = "Unfortunately, I still haven't gathered the required sum...";
			link.l2.go = "exit";
		break;
		
		case "Sharlie_junglejew":
			dialog.text = "Hm. It appears you're right, these are expensive earrings and they were made in the Old World for sure... What can I say? I'll give you for them thirty... no even thirty five gold doubloons. Take the money, you won't sell them for any more.";
			link.l1 = "Thirty five doubloons? That isn't a bad price. I agree. Here you go.";
			link.l1.go = "Sharlie_junglejew_1";
			link.l2 = "No. I think I'll leave these earrings to myself.";
			link.l2.go = "exit";
			npchar.quest.junglejew = "true";
		break;
		
		case "Sharlie_junglejew_1":
			DialogExit();
			PlaySound("interface\important_item.wav");
			Log_Info("You've given the earrings");
			RemoveItems(pchar, "jewelry25", 1);
			TakeNItems(pchar, "gold_dublon", 35);
			AddQuestRecord("SharlieE", "3");
			CloseQuestHeader("SharlieE");
			DeleteAttribute(pchar, "questTemp.Sharlie.Junglejew");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
			{
				DelLandQuestMark(characterFromId("FortFrance_Mayor"));
			}
		break;
		
		//--> Миниквест "Делюк"
		case "Del_Deluck":
			DeleteAttribute(pchar, "questTemp.Del_Rostovshik");
			dialog.text = "I know, I know, Captain. Your navigator seems to have amassed debts in nearly every French colony. Truth be told, I was aware of it for a long time. I checked with my colleagues, a standard procedure you see...";
			link.l1 = "And you didn't think it was important enough to inform me during our previous arrangement?";
			link.l1.go = "Del_Deluck_2";
		break;
		
		case "Del_Deluck_2":
			dialog.text = "Why? At the time, I was primarily concerned with Deluc's debt to me, which, incidentally, was the largest. Once you settled that, I promptly notified my colleagues... We have a vast fleet of professional couriers, so it didn't take long before I amassed a pile of Deluc's bills on my desk.";
			link.l1 = "I see... You bought them knowing that I have a vital interest in him and means to pay... This is extortion, Monsenior.";
			link.l1.go = "Del_Deluck_3";
		break;
		
		case "Del_Deluck_3":
			dialog.text = "It's just business, Captain! Deluc's total debt is one hundred doubloons, and interest is accruing... Are you willing to buy it out?";
			link.l1 = "I'm not prepared to answer yet but I'll consider it. Goodbye!";
			link.l1.go = "Del_Deluck_4";
		break;
		
		case "Del_Deluck_4":
			DialogExit();
			
			pchar.questTemp.Del_Rostovshik_repeat = true;
			sld = CharacterFromID("Tichingitu");
			if (sld.location == pchar.location && !LAi_IsDead(sld))
			{
				sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
				sld.dialog.currentnode = "Del_Deluck";
				LAi_SetActorType(sld);
				LAi_ActorDialogDelay(sld, pchar, "", 0.0);
			}
		break;
		
		case "Del_Deluck_5":
			dialog.text = "Excellent! You know what to do next - same as the last time. Here are the documents - present them to the prison commandant. It's been a pleasure doing business with you, Captain.";
			link.l1 = "There's little to enjoy about this situation. Goodbye.";
			link.l1.go = "exit";
			RemoveItems(pchar, "gold_dublon", 100);
			DeleteAttribute(pchar, "questTemp.Del_Rostovshik_repeat");
			Log_Info("You have received a bill of debt");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "letter_open");
			ChangeItemDescribe("letter_open", "itmdescr_letter_open_usurer");
			pchar.questTemp.Del_DeluckSvoboda = true;
			AddLandQuestMark(characterFromId("FortFranceJailOff"), "questmarkmain");
			DelLandQuestMark(npchar);
		break;
		//<-- Миниквест "Делюк"
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

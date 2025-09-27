// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What kind of questions?","What do you want, "+GetAddress_Form(NPChar)+"?"),"You've already tried to ask me a question "+GetAddress_Form(NPChar)+"...","You've brought up this question for the third time today...","Look, if you have nothing to tell me about the port's affairs then don't bother me with your questions.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I have changed my mind.","I've got nothing to talk about."),"Never mind.","Indeed, the third time already...","Sorry, but I'm not interested in the port's affairs for now.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			
			// belamour legengary edition на пару с Акулой -->
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet"))
			{
				if(pchar.questTemp.SharkGoldFleet == "toCarPortOffice" || pchar.questTemp.SharkGoldFleet == "start" || pchar.questTemp.SharkGoldFleet == "afterGvik" || pchar.questTemp.SharkGoldFleet == "buyincar")
				{
					link.l1 = "The fact is, I am about to sail to Porto Bello any day now with a load of goods I purchased from you in the colony. I thought, perhaps you have some freight or business I could handle along the way... For a fee, of course.";
					link.l1.go = "SharkGoldFleet";
				}
				if(pchar.questTemp.SharkGoldFleet == "LightVar")
				{
					if(!bImCasual) pchar.quest.SharkGoldFleetToCPO10.over = "yes";
					link.l1 = "Hello again. I delivered your letter to Porto Bello. There, I was asked to give you a reply.";
					link.l1.go = "SharkGoldFleet_09";
				}
				if(pchar.questTemp.SharkGoldFleet == "DifficultVar")
				{
					if(!bImCasual) pchar.quest.SharkGoldFleetToCPO10.over = "yes";
					link.l1 = "Hello. I have come to you from Porto Bello. Your colleague from the local port authority asked me to give you this letter.";
					link.l1.go = "SharkGoldFleet_13";
				}
			}
			//<-- на пару с Акулой
		break;
		
		// belamour на пару с Акулой -->
		case "SharkGoldFleet":
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet.Fail21"))
			{
				pchar.questTemp.SharkGoldFleet = "toCurierDie";
				AddQuestRecord("SharkGoldFleet", "5");
				SGF_CreateCurierInWorld("");
				dialog.text = "Thank you for your concern, but I have no such cases. There was actually one assignment, but you were literally a couple of days late: I sent a fast courier lugger for this purpose.";
				link.l1 = "Got it... Well, thanks for that.";
				link.l1.go = "exit";
			}
			else
			{
				if(!bImCasual) pchar.quest.SharkGoldFleet21.over = "yes"; 
				if(!bImCasual) pchar.quest.SharkGoldFleet30.over = "yes"; 
				if(GetCompanionQuantity(pchar) > 1)
				{
					pchar.questTemp.SharkGoldFleet = "toCurierWait";
					AddQuestRecord("SharkGoldFleet", "10");
					SetFunctionTimerCondition("SGF_CreateCurierInWorld", 0, 0, 1+rand(2), false);
					dialog.text = "I see you don't even have a single ship. You must be a wealthy merchant. Hmm ... But I know all the local merchants with squadrons by sight, yet I don't know you. So don't blame me, but I can't trust you with anything serious.";
					link.l1 = "Got it... Well, thanks for that.";
					link.l1.go = "exit";
				}
				else
				{
					if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_FRIGATE_L)
					{
						pchar.questTemp.SharkGoldFleet = "toCurierWait";
						AddQuestRecord("SharkGoldFleet", "11");
						SetFunctionTimerCondition("SGF_CreateCurierInWorld", 0, 0, 1+rand(2), false);
						dialog.text = "Hmm... I have a task. Only now your ship does not fit. I need a ship that is both fast and powerful, and yours does not fully meet these requirements. At least not at the same time. So please forgive me.";
						link.l1 = "Got it... Well, thanks for that.";
						link.l1.go = "exit";
					}
					else
					{
						if(!CheckAttribute(pchar,"questTemp.SharkGoldFleet.LicenceOk"))
						{
							pchar.questTemp.SharkGoldFleet = "toCurierWait";
							AddQuestRecord("SharkGoldFleet", "12");
							SetFunctionTimerCondition("SGF_CreateCurierInWorld", 0, 0, 1+rand(2), false);
							dialog.text = "I have something to do... And you have a good ship. It just doesn't look like a merchant vessel. And, as far as I can see, you don't have a long-term license from the Dutch West India Company. Don't take it the wrong way, but you don't strike me as a merchant. I can't take that risk.";
							link.l1 = "Got it... Well, thanks for that.";
							link.l1.go = "exit";
						}
						else
						{
							if(pchar.questTemp.SharkGoldFleet != "toCarPortOffice" || GetSquadronGoods(pchar, GOOD_COFFEE) < 300 || GetSquadronGoods(pchar, GOOD_CHOCOLATE) < 300)
							{
								pchar.questTemp.SharkGoldFleet = "toCurierWait";
								AddQuestRecord("SharkGoldFleet", "13");
								SetFunctionTimerCondition("SGF_CreateCurierInWorld", 0, 0, 1+rand(2), false);
								dialog.text = "I have something to do... And you have a good ship. Only now I don't understand what you are going to trade... You said that you were going to Porto Bello to sell the goods, but, as far as I know, you didn't buy them from us in the colony. Don't take it the wrong way, but you don't strike me as a merchant. I can't take that risk.";
								link.l1 = "Got it... Well, thanks for that.";
								link.l1.go = "exit";
							}
							else
							{
								dialog.text = "I have things to do. Of course, I don't know you... But, to tell the truth, I only remember merchants with squadrons to their names. The rest - no. And you have a long-term license, so it's clear you're an experienced merchant. Your ship, however, is interesting. Why would you trade on a frigate?";
								link.l1 = "Hah, this is no ordinary frigate. She can reach very high speeds even with a full hold. It's always easier to escape from pirates than to fight them, isn't it? Although my vessel has a smaller capacity than ordinary merchant ships, the risk is much lower.";
								link.l1.go = "SharkGoldFleet_01";
							}
						}
						
					}
					
				}
			}
		break;
		
		case "SharkGoldFleet_01":
			dialog.text = "Hmm, but you're right! The Spaniards know how to build ships, don't they? Yes, yes, I immediately saw that this fine vessel had left the stocks of our shipyards. And yes, I was actually told today that you bought a batch of coffee and cocoa from our merchant for resale in Porto Bello. Good deal, I tell you. People unfamiliar with trade do not know that these goods are cheap here, thanks to the plantations, and in Porto Bello they are in great demand, since from there they go to the metropolis.";
			link.l1 = "Well, that's what it's all about, señor. For a few pesos, I wouldn't take my boat that far.";
			link.l1.go = "SharkGoldFleet_02";
		break;
		
		case "SharkGoldFleet_02":
			dialog.text = "Well, to tell you the truth, I do have a job for you. And it's very good that you have such a fast ship, which can also defend itself in case of emergency.";
			link.l1 = "Wait, señor... Your case suggests that I have to fight...?";
			link.l1.go = "SharkGoldFleet_03";
		break;
		
		case "SharkGoldFleet_03":
			dialog.text = "No, no! In fact, my task is as simple as possible. I need you to deliver a letter to the Port Authority in Porto Bello. The letter is sealed and must not be opened. No one needs to talk about it either, the correspondence is... personal. Hand it over in person. The deadline is ten days. After that, it will be irrelevant.";
			link.l1 = "So simple? And how much will I get for it?";
			link.l1.go = "SharkGoldFleet_04";
		break;
		
		case "SharkGoldFleet_04":
			dialog.text = "Five thousand pesos. Consider it payment for not having to send a courier lugger to Porto Bello.";
			link.l1 = "And what were your questions about me and my ship?";
			link.l1.go = "SharkGoldFleet_05";
		break;
		
		case "SharkGoldFleet_05":
			dialog.text = "Never mind. It's just that the correspondence is important, and I must be sure it will reach the addressee. So, nothing special. Bureaucracy... For an ordinary person, these documents hold no interest.";
			link.l1 = "Well, I agree. Let's get your papers here. As soon as I arrive in Porto Bello, I will bring them to your colleague. I'll manage it in ten days, don't worry.";
			link.l1.go = "SharkGoldFleet_06";
		break;
		
		case "SharkGoldFleet_06":
			dialog.text = "One moment. I'm sorry, I completely forgot your name. Could you tell me, please? I need to write it down in the documents.";
			link.l1 = "My name is Andreas Garcia.";
			link.l1.go = "SharkGoldFleet_07";
		break;
		
		case "SharkGoldFleet_07":
			dialog.text = "Thank you. So... Great. Remember, it is you who must deliver this document, and directly into the hands of the addressee. Here you go. The award will be given to you by the head of the Port Authority in Porto Bello. Have a good trip!";
			link.l1 = "Thank you! Now, excuse me.";
			link.l1.go = "SharkGoldFleet_08";
		break;
		
		case "SharkGoldFleet_08":
			DialogExit();
			if(!bImCasual) SetFunctionTimerCondition("SharkGoldFleetToPB10", 0, 0, 10, false);
			else NewGameTip("Exploration mode: timer is disabled.");
			AddCharacterSkillDontClearExp(pchar, SKILL_LEADERSHIP, 1);
			AddCharacterSkillDontClearExp(pchar, SKILL_SNEAK, 1);
			TakeNItems(pchar, "letter_1", 1);
			ChangeItemDescribe("letter_1", "itmdescr_letter_SharkGoldFleet_1");
			AddQuestRecord("SharkGoldFleet", "14");
			pchar.questTemp.SharkGoldFleet = "toPBPortOffice";
		break;
		
		case "SharkGoldFleet_09":
			RemoveItems(PChar, "letter_2", 1);
			ChangeItemDescribe("letter_2", "itmdescr_letter_2");
			dialog.text = "Great! You helped me a lot. Did you have any difficulties?";
			link.l1 = "No, there were no difficulties. True, your colleague cursed you: he said that you are all misers here, because you are not sending a courier ship, but passing merchants, and even charging the recipient for payment. He threatened that he would write a complaint to Havana ...";
			link.l1.go = "SharkGoldFleet_10";
		break;
		
		case "SharkGoldFleet_10":
			dialog.text = "What?! Am I the curmudgeon?! What does he think of himself there? First, keep your five... no, six thousand pesos! I'm crying honestly!";
			link.l1 = "Thank you. It's good to see that your colleague was mistaken about you.";
			link.l1.go = "SharkGoldFleet_11";
		break;
		
		case "SharkGoldFleet_11":
			AddMoneyToCharacter(pchar, 6000);
			dialog.text = "And secondly, this scoundrel seems to have forgotten how, two months ago, he saddled me with all the expenses for maintaining a merchant ship that sailed from Caracas to Porto Bello, and from there to Havana! And we agreed that he would pay for the second part of the journey! He never repaid the debt, but promised he would settle everything last month! And I'm still the miser... Yes, I'll write a complaint against him to Havana myself!";
			link.l1 = "Well, you have the passions of the Madrid court, of course ...";
			link.l1.go = "SharkGoldFleet_12";
		break;
		
		case "SharkGoldFleet_12":
			AddQuestRecord("SharkGoldFleet", "20");
			AddQuestUserData("SharkGoldFleet", "date", pchar.questTemp.SharkGoldFleet.Date)
			pchar.questTemp.SharkGoldFleet = "LightVarToShark";
			SetFunctionLocationCondition("SharkGoldFleetToShark", "Curacao", false);
			dialog.text = "No, come to think of it ... What an impudent fellow! Fine, I'll deal with him again ... And now I'll ask you to excuse me: I have urgent business ahead of me. It was a pleasure doing business with you!";
			link.l1 = "And good luck to you!";
			link.l1.go = "exit";
		break;
		
		case "SharkGoldFleet_13":
			RemoveItems(PChar, "letter_2", 1);
			ChangeItemDescribe("letter_2", "itmdescr_letter_2");
			dialog.text = "Great! You helped me a lot. Although, I sent a courier lugger to them, and they sent their reply back with a passing ship. Yeah ... And after that, they still complain that we have misers sitting here.";
			link.l1 = "Well, maybe they saved the money for the courier ...";
			link.l1.go = "SharkGoldFleet_14";
		break;
		
		case "SharkGoldFleet_14":
			AddMoneyToCharacter(pchar, 5000);
			AddQuestRecord("SharkGoldFleet", "20");
			AddQuestUserData("SharkGoldFleet", "date", pchar.questTemp.SharkGoldFleet.Date)
			pchar.questTemp.SharkGoldFleet = "DifficultVarToShark";
			SetFunctionLocationCondition("SharkGoldFleetToShark", "Curacao", false);
			dialog.text = "Not 'maybe', but definitely, I tell you! Fine, it doesn't matter. Here, take your work. And now I have a lot of work, excuse me.";
			link.l1 = "Well, maybe they spared the money for the courier ...";
			link.l1.go = "exit";
		break;
		// <-- на пару с Акулой
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

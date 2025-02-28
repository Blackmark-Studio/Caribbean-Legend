// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Go ahead, what do you want?",
                          "We were just talking about that. You must have forgotten...", "This is the third time today you're talking about some question...",
                          "Listen, this is a store. People buy stuff here. Don't disturb me!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("You know, " + NPChar.name + ", maybe next time.", "Right, I've forgotten for some reason...",
                      "Yes, it really is the third time...", "Hm, I wont...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			
			//Jason --> ----------------------------------мини-квест Бесчестный конкурент------------------------------------
			if (CheckAttribute(pchar, "questTemp.Shadowtrader"))
			{
				if(pchar.questTemp.Shadowtrader == "begin" && GetNpcQuestPastDayParam(npchar, "Shadowtrader_date") < 5 && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "Thank you, captain, for fulfilling my request. Now, when "+pchar.questTemp.Shadowtrader.Guardername+" is here, I can at least feel a bit more relaxed.";
					link.l1 = "Hmm... I wouldn't want to appear obtrusive, but it seems to me that you are having troubles. Can you tell me what the deal is - perhaps, I could help you?"; 
					link.l1.go = "Shadowtrader_fort";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.Trouble") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "So? Have you handed over my letter?";
					link.l1 = "I have. The commandant replied by word of mouth that the evidence in your letter is insufficient for the city guard to take any measures."; 
					link.l1.go = "Shadowtrader_trouble";
					pchar.quest.ShadowtraderTimeFort_Over.over = "yes";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.End.Fort") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store" && CheckAttribute(pchar, "questTemp.Shadowtrader.EndFort"))
				{
					dialog.text = "I have already heard the news - tonight guards discovered an illegal trading post of smugglers and arrested them all. It was under command of one rare piece of scum, it's alright now, he won't be able to do bad things to anyone else for a while\nCommandant told me about your role in all of this, you have my gratitude! You have kept your word! Here, take the money - 15 000 pesos. You have saved me. Nothing is threatening my business now!";
					link.l1 = "You're welcome. It was easy."; 
					link.l1.go = "Shadowtrader_complete";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.End.Escape") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "So, any good news, " + pchar.name + "?";
					link.l1 = "I have located your rival. He will not be a pain in your butt again - I managed to convince him... to leave this island. His 'shop' was in a house near the city gates. It's up to you to decide what to do with the cargo that was abandoned. You can turn it in to the authorities or attempt to collect it for yourself."; 
					link.l1.go = "Shadowtrader_Escape_complete";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.End.Free") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "I have already heard the news - tonight the guards have discovered an outlet of smugglers underneath one of the houses. Two villains found dead. Great job, " + pchar.name + ", I admire you! Here, take the reward - 15 000 pesos. You just saved me! Now I'll trade for real!\nSatisfy my curiosity - their leader... also among the two dead?";
					link.l1 = "No. But he will never show his face in your town again. I believe he should be several dozen miles away from this island, while we're talking."; 
					link.l1.go = "Shadowtrader_complete";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.End.Kill") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "I have already heard the news - this night the guards have located a secret smuggler shop in one of the houses. Three villains were found dead. Excellent work, " + pchar.name + ", I admire you! Here, take the award - 15,000 pesos. You just saved me! Now I'll trade for real!\nSatisfy my curiosity - their leader... also among the two dead?";
					link.l1 = "Yes. You've got rid of your rival forever. He will never trouble you again."; 
					link.l1.go = "Shadowtrader_complete";
					break;
				}
			}
			//<-- мини-квест Бесчестный конкурент
		break;
		
		// --> мини-квест Бесчестный конкурент
		case "Shadowtrader_begin":
			pchar.questTemp.Shadowtrader = "true";
			pchar.questTemp.Shadowtrader_Block = true;
			pchar.questTemp.Shadowtrader.Guardername = GenerateRandomName_Generator(sti(npchar.nation), "man");
			dialog.text = "Could you please go to the tavern, find a man by the name of "+pchar.questTemp.Shadowtrader.Guardername+" and tell him to come here as soon as possible? I cannot leave the store, and this blockhead sits in the tavern, loading up with rum, and surely he will not even think to come here, despite being on duty.";
			link.l1 = "I'm always happy to help, mate - all the more so because I was going to visit the tavern anyway.";
			link.l1.go = "Shadowtrader_begin_1";
			link.l2 = "Are you mocking me? Do I look like your errand boy? The tavern is just a couple steps away from here - you can go there yourself.";
			link.l2.go = "exit";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("BasTer");
		break;
		
		case "Shadowtrader_begin_1":
			dialog.text = "Thank you! Please tell him to come here right now. Oh my, why does he have to be such a nuisance...";
			link.l1 = "Don't worry. I will send him your way.";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader.City = npchar.City;
			pchar.questTemp.Shadowtrader.nation = sti(npchar.nation);
			//создаем охранника
			sld = GetCharacter(NPC_GenerateCharacter("ShadowGuarder" , "officer_7", "man", "man", 10, sti(npchar.nation), 5, true, "quest"));
			FantomMakeCoolFighter(sld, 20, 50, 50, "topor_2", "pistol3", "bullet", 50);
			sld.name = pchar.questTemp.Shadowtrader.Guardername;
			sld.lastname = "";
			sld.dialog.FileName = "Quest\LineMiniQuests\ShadowTrader.c";
			sld.dialog.currentnode = "ShadowGuarder";
			sld.greeting = "pirat_common";
			LAi_SetSitType(sld);
			LAi_SetImmortal(sld, true);
			FreeSitLocator(pchar.questTemp.Shadowtrader.City + "_tavern", "sit_front1");
			ChangeCharacterAddressGroup(sld, pchar.questTemp.Shadowtrader.City + "_tavern", "sit", "sit_front1");
			SaveCurrentNpcQuestDateParam(npchar, "Shadowtrader_date");
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "Shadowtrader_fort":
			dialog.text = "Oh, captain, I would really like your help. Could you please deliver this letter to the commandant as soon as possible? I would pay you 300 coins for that trivial deal - as I have already said, I cannot leave my shop.";
			link.l1 = "No problem. Give me that letter.";
			link.l1.go = "Shadowtrader_fort_1";
			link.l2 = "No, my good man, I have no more time for that bullshit.";
			link.l2.go = "Shadowtrader_fort_end";
			DelLandQuestMark(npchar);
		break;
		
		case "Shadowtrader_fort_1":
			dialog.text = "Here you go. Please hand it to him today and deliver me his reply.";
			link.l1 = "Don't worry, I'll do it.";
			link.l1.go = "exit";
			GiveItem2Character(pchar, "letter_1");
			ChangeItemDescribe("letter_1", "itmdescr_letter_1"); // 240912
			pchar.questTemp.Shadowtrader.Tradername = GetFullName(npchar);
			SetFunctionTimerCondition("ShadowtraderTimeFort_Over", 0, 0, 1, false);
			pchar.questTemp.Shadowtrader = "current"
			pchar.questTemp.Shadowtrader.Fort = "true";
			AddQuestRecord("Shadowtrader", "1");
			AddQuestUserData("Shadowtrader", "sCity", XI_ConvertString("Colony"+pchar.questTemp.Shadowtrader.City+"Gen"));
			AddLandQuestMarkToPhantom("baster_prison", "basterJailOff");
		break;
		
		case "Shadowtrader_fort_end":
			dialog.text = "Well, apparently I'll have to ask someone else. Sorry to have bothered you, captain.";
			link.l1 = "No problem. Goodbye!";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader = "true";
			DeleteAttribute(pchar, "questTemp.Shadowtrader_Block");
		break;
		
		case "Shadowtrader_trouble":
			dialog.text = "That's what he said? What evidence does he need from me, then?! My corpse? Well, there soon will be one, if it keeps going like that!..";
			link.l1 = "Hey, hey, " + npchar.name + ", calm down, or you will suffer a stroke. Here, drink some water... Now tell me, what's the matter - perhaps I'd be able to help you?";
			link.l1.go = "Shadowtrader_trouble_1";
			DeleteAttribute(pchar, "questTemp.Shadowtrader.Trouble");
			DelLandQuestMark(npchar);
		break;
		
		case "Shadowtrader_trouble_1":
			dialog.text = "Oh, captain! Please take your 300 pesos - I had almost forgotten... Of course, I'll tell you, but I am not sure how you'd be able to help me. My business is nearly ruined - all because of those cursed smugglers and that unknown bastard who leads them.";
			link.l1 = "Smugglers?";
			link.l1.go = "Shadowtrader_trouble_2";
			AddMoneyToCharacter(pchar, 300);
		break;
		
		case "Shadowtrader_trouble_2":
			dialog.text = "That's it! Those rascals have obviously decided to kick me out of town! Until then everything had been as usual - they resold prohibited items, and when patrols caught them, they hid or paid them off. But recently they have opened somewhere in a backstreet shop and began selling the most popular goods at incredibly low prices!\nI can not afford that luxury - in fact I have to pay taxes - I progressively impoverished myself and seamen almost don't want my goods - all goods they buy from these rogues.";
			link.l1 = "But you should've appealed to the authorities! After all, it's their job - stopping such lawlessness.";
			link.l1.go = "Shadowtrader_trouble_3";
		break;
		
		case "Shadowtrader_trouble_3":
			dialog.text = "You saw the last appeal result yourself. The governor is too busy and the commandant did not believe that smugglers organized backstreet stores, or pretends he does not believe - and, I suppose, that's the case\nOf course, why would they do that? And I say: I'm sure some rascal rascal who wants to destroy and expel me out of town came up with it all, and then he will quietly tidy up my business to clean their dirty little hands.";
			link.l1 = "Hm... your opinion is not unfounded. It's in the nature of merchants - making a cat's paw out of someone... Oh, I am sorry, I didn't mean you, of course. ";
			link.l1.go = "Shadowtrader_trouble_4";
		break;
		
		case "Shadowtrader_trouble_4":
			dialog.text = "Oh, nothing... And recently some ragamuffin came to me and brazenly said that if I continued to make noise, they would burn my shop\nSo I hired a bodyguard. "+pchar.questTemp.Shadowtrader.Guardername+" does not come cheap, but he's a professional and under his protection I can feel a little calmer.";
			link.l1 = "I see... An unpleasant story, indeed. Apparently, you were right - there's nothing I can do for you. But still, I am certain that things will work themselves out - such shady establishments usually do not last for long. Well, best of luck!";
			link.l1.go = "Shadowtrader_end";
			link.l2 = "I see. Well, perhaps I'd still be able to help you out...";
			link.l2.go = "Shadowtrader_trouble_5";
		break;
		
		case "Shadowtrader_trouble_5":
			dialog.text = "You're offering me your help anyway? But what are you going to do?";
			link.l1 = "I will try to find that 'colleague' of yours and... persuade him to get off your back. You know, I have certain skills at persuading people.";
			link.l1.go = "Shadowtrader_trouble_6";
		break;
		
		case "Shadowtrader_trouble_6":
			dialog.text = "Are you serious? May the Lord bless your just cause! If you rid me of that filth, I will be in your debt.";
			link.l1 = "Alright, consider it a deal. I will start searching, then.";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader.seeksmugglers = "true";
			AddLandQuestMark(characterFromId("BasTer_Smuggler"), "questmarkmain");
			AddQuestRecord("Shadowtrader", "2");
			AddQuestUserData("Shadowtrader", "sCity", XI_ConvertString("Colony"+pchar.questTemp.Shadowtrader.City+"Gen"));
			AddQuestUserData("Shadowtrader", "sSex1", GetSexPhrase("ся","ась"));
		break;
		
		case "Shadowtrader_end":
			pchar.questTemp.Shadowtrader = "true";
			CloseQuestHeader("Shadowtrader");
			DeleteAttribute(pchar, "questTemp.Shadowtrader_Block");
			DialogExit();
		break;
		
		case "Shadowtrader_Escape_complete":
			dialog.text = "Is that true? I can now do business without any fear? Oh, thank you so much! Here's your reward - 15000 pesos. As for the goods in their house, I guess it's best to hand them over to the commandant. Thank you again!";
			link.l1 = "You're welcome. It wasn't too hard. I told you I was good at persuasion.";
			link.l1.go = "Shadowtrader_complete";
		break;
		
		case "Shadowtrader_complete":
			dialog.text = "Come visit me again, captain - I will always be happy to see you.";
			link.l1 = "Of course! And now allow me to take my leave - I have things to do! Goodbye and good luck in your trade, " + npchar.name + "!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Shadowtrader.End");
			AddMoneyToCharacter(pchar, 15000);
			pchar.questTemp.Shadowtrader = "complete";
			AddQuestRecord("Shadowtrader", "11");
			AddQuestUserData("Shadowtrader", "sSex", GetSexPhrase("","а"));
			CloseQuestHeader("Shadowtrader");
			DeleteAttribute(pchar, "questTemp.Shadowtrader_Block");
			DeleteAttribute(pchar, "questTemp.Shadowtrader.EndFort");
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("BasTer");
		break;
		//<-- мини-квест Бесчестный конкурент
	}
	UnloadSegment(NPChar.FileDialog2);
}

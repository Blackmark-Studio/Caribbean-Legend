// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions do you have?","How can I help you, "+GetAddress_Form(NPChar)+"?"),"You tried to ask me a question not long ago, "+GetAddress_Form(NPChar)+"...","Over the course of this whole day, this is the third time you've brought up some question...","More questions, I presume?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind...","I've got nothing to talk about at the moment."),"Umph, where has my memory gone...","Yes, it really is the third time...","No, what questions?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			/* //--> Jason, Бремя гасконца
			if (!CheckAttribute(npchar, "quest.Rum") && CheckAttribute(pchar, "questTemp.Sharlie.Lock") && pchar.questTemp.Sharlie == "ship" && makeint(environment.time) > 5.0 && makeint(environment.time) < 19.0)
			{
				link.l1 = "Monsieur, I'm looking for work. Do you have any jobs?";
                link.l1.go = "Sharlie_rum";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Rum") && pchar.questTemp.Sharlie.Rum == "regard")
			{
				link.l1 = "I've fulfilled your assignment. The longboat with the rum has been delivered to Le François Bay and handed over to your people.";
                link.l1.go = "Sharlie_rum_5";
			}	
			//<-- Бремя гасконца */
			
			//Jason, Португалец
			if (CheckAttribute(PChar, "questTemp.Portugal") && pchar.questTemp.Portugal == "ToMartinique" && !CheckAttribute(npchar, "quest.Portugal"))
			{
				link.l1 = "I need to rent one of your rooms for two or three days. I have a man on board who's wounded. He needs to get some rest and recover.";
				link.l1.go = "Portugal";
			}
			if (CheckAttribute(PChar, "questTemp.Portugal") && pchar.questTemp.Portugal == "MartiniqueGovernorEnd")
			{
				link.l1 = "Tell me, the friend I rented a room for—has he left? He promised to wait for me, but the room is empty.";
				link.l1.go = "Portugal_2";
			}
			//Португалец
			// Jason Долго и счастливо
			if (!CheckAttribute(npchar, "quest.LongHappy") && CheckAttribute(PChar, "questTemp.LongHappy.MarryRum") && LongHappy_CheckTavernGoods())
			{
				link.l1 = "I am going to arrange a party for my men. I suppose you already know about it?";
				link.l1.go = "LH_tavern_SP";
			}
			if (CheckAttribute(npchar, "quest.LongHappy.Nomoney") && LongHappy_CheckTavernGoods() && sti(Pchar.money) >= 100000+sti(pchar.questTemp.LongHappy.MarryMoney))
			{
				link.l1 = "I brought everything we need for our celebration.";
				link.l1.go = "LH_tavern_SP_3";
			}
		break;
		
		//--> Jason, Бремя гасконца
		case "Sharlie_rum":
			DelLandQuestMark(npchar);
			dialog.text = "A task? Hm... You look like you've got some brains, boy. I may have something for you\nThis job may sound easy, but it requires responsibility and intelligence. I can't trust these idiots to do business, they'd ruin it for sure...";
			link.l1 = "Listen, can you please just tell me what exactly you want to assign to me? I swear, I won't let you down, or at least I'll do my best.";
			link.l1.go = "Sharlie_rum_1";
		break;
		
		case "Sharlie_rum_1":
			switch(rand(4))
			{
				case 0:
					pchar.questTemp.Sharlie.Rum.Pass = "Old Thomas has grown tired of waiting for the beer";
				break;
				case 1:
					pchar.questTemp.Sharlie.Rum.Pass = "The boards and the oakum will be here in the morning";
				break;
				case 2:
					pchar.questTemp.Sharlie.Rum.Pass = "Don't wait for the south wind";
				break;
				case 3:
					pchar.questTemp.Sharlie.Rum.Pass = "The bay is ready for disembarkation";
				break;
				case 4:
					pchar.questTemp.Sharlie.Rum.Pass = "The camels are going north";
				break;
			}
			dialog.text = "Good. I need someone to deliver several crates of fine Jamaican rum to my tavern. Here's the thing, import tariffs cut into my margins and my best customers are thirsty, so we need to act smart to avoid the customs officials. The lugger 'Ghost' will arrive off Martinique tonight\nThey will drop anchor not far from Lamanten Bay. You must find this vessel and get aboard. I will provide you with a longboat and five sailors, they will follow your orders\nOnce you are aboard, a man will approach you. You'll have to tell him a password: '"+pchar.questTemp.Sharlie.Rum.Pass+"'\nThe answer will be 'Why not have a rum, sailor?'. You'll have only one try, so write it down and don't make a mistake or the deal is off. That's why I can't entrust it to those brainless fools who will sail with you. Repeat the password.";
			link.l1 = "'"+pchar.questTemp.Sharlie.Rum.Pass+"'.";
			link.l1.go = "Sharlie_rum_2";
		break;
		
		case "Sharlie_rum_2":
			dialog.text = "Great. Repeat it to yourself a few more times, or better yet, write it down somewhere. After you mention the password to the lugger's captain, the crates of rum will be loaded onto the longboat, which you will then need to sail to the bay of the pirate settlement Le Francois - you will be welcomed there.\nThat's the whole task. You can get from Le Francois Bay to Saint Pierre on foot - the longboat will remain in the bay. I will pay five thousand pieces of eight once it's done.";
			link.l1 = "Smuggling sounds both exciting and lucrative. I'll do as you told me. Where's the longboat?";
			link.l1.go = "Sharlie_rum_3";
			link.l2 = "So, you propose that I take up smuggling? Hm... You know, I can't risk my name. You'll have to excuse me, let's just pretend I didn't hear anything.";
			link.l2.go = "Sharlie_rum_exit";
		break;
		
		case "Sharlie_rum_exit":
			dialog.text = "As you wish, monsieur. I don't have any other work.";
			link.l1 = "I see. Then all the best, "+npchar.name+".";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Sharlie.Rum");
			SetCurrentTime(23, 0);
			Sharlie_removeLocks("");
		break;
		
		case "Sharlie_rum_3":
			dialog.text = "The longboat will be at the pier at seven in the evening. The crew on the longboat are skilled, so you should reach the lugger quickly. The whole task shouldn't take more than four hours - I'm sure you'll be back in Saint Pierre by eleven in the evening. Take this spyglass, it's a piece of garbage but it's better than nothing. Lamanten Beach is located on the northern part of the island, so when leaving the port, keep your course due north. Good luck!";
			link.l1 = "Alright, got it. See you soon, "+npchar.name+"!";
			link.l1.go = "Sharlie_rum_4";
		break;
		
		case "Sharlie_rum_4":
			DialogExit();
			AddQuestRecord("SharlieB", "1");
			AddQuestUserData("SharlieB", "sPassword", pchar.questTemp.Sharlie.Rum.Pass);
			GiveItem2Character(pchar, "spyglass1"); 
			Log_Info("You've received a spyglass");
			PlaySound("interface\important_item.wav");
			if(CheckAttribute(pchar, "questTemp.Sharlie.FastStart"))
			{
				GiveItem2Character(pchar, "map_martiniqua");
				Log_Info("You have received a map of Martinique");
				RefreshEquippedMaps(GetMainCharacter());
			}
			/* pchar.quest.Sharlie_rum.win_condition.l1 = "location";
			pchar.quest.Sharlie_rum.win_condition.l1.location = "Fortfrance_town"; */
			//pchar.quest.Sharlie_rum.win_condition.l1.locator_group = "rld";
			//pchar.quest.Sharlie_rum.win_condition.l1.locator = "loc0";
			pchar.quest.Sharlie_rum.win_condition.l1 = "HardHour";
			pchar.quest.Sharlie_rum.win_condition.l1.hour = 19.00;
			pchar.quest.Sharlie_rum.function = "Rum_CreateBarkas";
			SetFunctionTimerCondition("Rum_CreateBarkasOver", 0, 0, 1, false);
			pchar.questTemp.Sharlie.Rum = "true";
			npchar.quest.Rum = "true";
			NewGameTip("Open your inventory (F1) and equip the spyglass.");
			pchar.quest.NgtBarkas.win_condition.l1 = "location";
			pchar.quest.NgtBarkas.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.NgtBarkas.win_condition.l2 = "HardHour";
			pchar.quest.NgtBarkas.win_condition.l2.hour = 19.00;
			pchar.quest.NgtBarkas.function = "NgtBarkas";
			AddTimeToCurrent(1,30);
			QuestPointerDelLoc("fortfrance_town", "reload", "reload4_back");
			QuestPointerToLoc("fortfrance_town", "reload", "reload1_back");
		break;
		
		case "Sharlie_rum_5":
			dialog.text = "Wonderful! I knew I could rely on you. Was it hard?";
			link.l1 = "Well, that depends on how you define hard...";
			link.l1.go = "Sharlie_rum_6";
		break;
		
		case "Sharlie_rum_6":
			dialog.text = "Well, here's your reward: five thousand pesos. You can keep the spyglass. And also, another little present—please, take these three bottles of rum. After you try it, you'll understand why there's such a demand for it.";
			link.l1 = "Thank you! It was a pleasure working with you! See you later!";
			link.l1.go = "Sharlie_rum_7";
		break;
		
		case "Sharlie_rum_7":
			DialogExit();
			AddMoneyToCharacter(pchar, 5000);
			TakeNItems(pchar, "potionrum", 3);
			AddQuestRecord("SharlieB", "5");
			CloseQuestHeader("SharlieB");
			DeleteAttribute(pchar, "questTemp.Sharlie.Rum");
			// Rebbebion, новые марки до места назначения
			QuestPointerDelLoc("lefransua_town", "reload", "gate_back");
			QuestPointerDelLoc("lefransua_exittown", "reload", "reload2_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerDelLoc("fortfrance_town", "reload", "reload4_back");
			DelLandQuestMark(npchar);
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Gigolo"))
			{
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1 = "Hour";
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.start.hour = 6.00;
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.finish.hour = 22.00;
				pchar.quest.Sharlie_CreatShipyardMarker.function = "Sharlie_CreatShipyardMarker";
			}
		break;
		//<-- Бремя гасконца
		
		//Португалец
		case "Portugal":
			dialog.text = "No problem, I have a room. For 50 pesos, it's yours for three days.";
			if (sti(pchar.money) >= 50)
			{
				link.l1 = "Here you go.";
				link.l1.go = "Portugal_1";
			}
			else
			{
				link.l1 = "I'll go get the money from the treasurer and I'll be back.";
				link.l1.go = "exit";
			}
		break;
		
		case "Portugal_1":
			ref sld;
			DialogExit();
			AddMoneyToCharacter(pchar, -50);
			npchar.quest.Portugal = "true";
			LocatorReloadEnterDisable("Fortfrance_tavern", "reload2_back", false);
			pchar.quest.Portugal_Ill3.over = "yes";
			LocatorReloadEnterDisable("Fortfrance_town", "reload1_back", true);
			LocatorReloadEnterDisable("Fortfrance_town", "reload2_back", true);
			LocatorReloadEnterDisable("Fortfrance_town", "gate_back", true);//закрыть выходы из города
			sld = characterFromId("Portugal");
			ChangeCharacterAddressGroup(sld, "FortFrance_tavern_upstairs", "goto", "goto3");
			sld = characterFromId("PortugalDoctor");
			ChangeCharacterAddressGroup(sld, "FortFrance_tavern_upstairs", "goto", "goto1");
			pchar.quest.Portugal_tavernroom.win_condition.l1 = "location";
			pchar.quest.Portugal_tavernroom.win_condition.l1.location = "FortFrance_tavern_upstairs";
			pchar.quest.Portugal_tavernroom.function = "PortugalInTavernRoom";
		break;
		
		case "Portugal_2":
			dialog.text = "I wouldn't say that he got up and left the room by himself, monsieur. Some people came by here yesterday. One of them was a tall, lanky, one-eyed man – an obvious bandit by his appearance, and there was also a lisping man, looked like a Castilian. I was just surprised, but that lisper gave me a look... just like you’d give a louse before crushing it. And so they asked about your friend... and I told them. What else was I supposed to do?";
			link.l1 = "I know, "+npchar.name+", you're no hero, that's right. What else did you see? Where did they go?";
			link.l1.go = "Portugal_3";
		break;
		
		case "Portugal_3":
			dialog.text = "That's all... wait, no! Hold on, the one-eyed man said something about a wagon. I guess they took a wagon and dragged your friend clear over to the other side of the island. That's all, monsieur, I swear... I would call the guard, but that lisper told me I had a beautiful wife just before he left... See? If they find out I told you all of this, they'll...";
			if (pchar.money >= 1000)
			{
				link.l1 = "Don't be afraid, they won't hear anything from me except bullets. You've really helped me, thank you. Here, take 1000 pesos as a reward.";
				link.l1.go = "Portugal_4";
			}
			link.l2 = "It's not much, but thanks anyway. Next time, call the guard and don't be such a coward.";
			link.l2.go = "Portugal_5";
		break;
		
		case "Portugal_4":
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = "Thank you, monsieur. I can give you my word that your friend has almost recovered. He was at least walking by himself. And that one man, the quiet Dutchman, he came in from outside at that moment, saw all that mess and leapt back outside, just disappeared after.";
			link.l1 = "I'd say he's already departed on the first ship he could find. Thank you for the information, it's time for me to go.";
			link.l1.go = "Portugal_6";
		break;
		
		case "Portugal_5":
			dialog.text = "Not every man can be a hero with his sword unsheathed, captain.";
			link.l1 = "Well... that's the man's choice.";
			link.l1.go = "Portugal_6";
		break;
		
		case "Portugal_6":
			DialogExit();
			sld = characterFromId("Avendel");
			sld.dialog.currentnode = "Avendel_seapatrol_9";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		//Португалец
		
		// Jason Долго и счастливо
		case "LH_tavern_SP":
			npchar.quest.LongHappy = "true";
			dialog.text = "Yes, your assistant dropped by, but I told her and I will repeat to you - I am used to crowds of drunken sailors, but I know how your parties go. What remains will look like Antwerp after the Spanish tercios came calling. I'll be happy if the walls are still standing. So, if you want to make the masses brawl, I will need a non-refundable deposit beyond what you have already brought. In case of consequences, so to speak.";
			link.l1 = "You sly fox! I've been drinking with sea dogs for many years, I've been in all sorts of... establishments, and I know that with the money I brought, we could rebuild your tavern from the ground up! Taking advantage of the situation, are you? Fine, I have a wedding to attend, and I'm not in the mood to trouble myself with such trifles - how much do you want?";
			link.l1.go = "LH_tavern_SP_1";
		break;
		
		case "LH_tavern_SP_1":
			dialog.text = "Another 100,000 pieces of eight should be enough and don't worry - I'll do everything in the best possible way. Your boys will remember this party for a long time, mark my words!";
			if (sti(Pchar.money) >= 100000+sti(pchar.questTemp.LongHappy.MarryMoney))
			{
				link.l1 = "You really must make an effort - this is a special occasion, you understand. And yes, after the celebration, don't come to me with complaints, even if your tavern burns down.";
				link.l1.go = "LH_tavern_SP_4";
			}
			else
			{
				link.l1 = "It already feels like I'm organising a king's wedding! Wait, I'll be back soon.";
				link.l1.go = "LH_tavern_SP_2";
			}
		break;
		
		case "LH_tavern_SP_2":
			DialogExit();
			npchar.quest.LongHappy.Nomoney = "true";
		break;
		
		case "LH_tavern_SP_3":
			dialog.text = "Your boys will remember this party for a long time, mark my words!";
			link.l1 = "You have to really try - this is a special occasion, you understand. Don't come crying to me if my boys accidentally burn your tavern down.";
			link.l1.go = "LH_tavern_SP_4";
		break;
		
		case "LH_tavern_SP_4":
			DialogExit();
			RemoveCharacterGoods(pchar, GOOD_RUM, sti(pchar.questTemp.LongHappy.MarryRum));
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.LongHappy.MarryMoney));
			AddMoneyToCharacter(pchar, -100000);
			DeleteAttribute(npchar, "quest.LongHappy.Nomoney");
			pchar.questTemp.LongHappy.DrinkReady = "true";
			pchar.questTemp.LongHappy.MarrySP = "true";
			DeleteAttribute(pchar, "questTemp.LongHappy.MarryMoney");
			DeleteAttribute(pchar, "questTemp.LongHappy.MarryRum");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

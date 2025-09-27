// Хенрик Ведекер. Он же Механик.
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Good day, sir. I have never seen you before. Are you new here? Is this your first time visiting this platform?";
				link.l1 = TimeGreeting()+". My name is "+GetFullName(pchar)+". I'm new here, just looking around and getting to know people...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				if (pchar.questTemp.LSC == "platinum_wait")
				{
					dialog.text = "Listen, "+pchar.name+", if you keep distracting me, I will never finish the repairs.";
					link.l1 = "Yes, yes, I remember that. I am sorry for troubling you!";
					link.l1.go = "exit";
					break;
				}
				// возвращение блудного скафандра
				if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
				{
					dialog.text = "Ah! Just look at that! The drowned man is back from the other world! Now, tell me, how did you manage such a trick? They held a funeral for you and buried you in your absence, just in case you didn't know...";
					link.l1 = "Too bad, I'm not going to die just yet. The trick is simple – I only touched Kukulcan's idol at the bottom. It teleported me to Dominica, right into the Caribs' village...";
					link.l1.go = "return";
					break;
				}
				
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+"!";
				// квестовые ветки
				if(pchar.questTemp.LSC == "mechanic")
				{
					link.l4 = "Henrik, I have a business proposition for you. A very important one. Ole Christiansen has told me about you. He's also called the White Boy.";
					link.l4.go = "mechanic_1";
				}
				if(pchar.questTemp.LSC == "platinum" && GetCharacterItem(pchar, "jewelry10") >= 11)
				{
					link.l4 = "Henrik, I have brought you enough 'silver'. Exactly as you asked: one of yours, plus ten extra pieces. Here, take them.";
					link.l4.go = "mechanic_15";
				}
				if(pchar.questTemp.LSC == "underwater_check")
				{
					link.l4 = "Me again, Henrik. How is your suit? Were you able to repair it?";
					link.l4.go = "mechanic_20";
				}
				if(pchar.questTemp.LSC == "platinum_add_wait" && GetCharacterItem(pchar, "jewelry10") >= sti(pchar.questTemp.LSC.PtAddQty))
				{
					link.l4 = "I have enough metal, the one you asked for. Take it.";
					link.l4.go = "mechanic_23";
				}
				if(pchar.questTemp.LSC == "underwater_prepare")
				{
					link.l4 = "Good day, Henrik. So, is the suit ready for a dive?";
					link.l4.go = "immersion";
				}
				if(pchar.questTemp.LSC == "underwater_natan" && CheckAttribute(pchar, "questTemp.LSC.NatanTalk"))
				{
					link.l4 = "It is over, I have dealt with my problems and I am ready to dive. When shall we begin?";
					link.l4.go = "immersion_1";
				}
				if(CheckAttribute(pchar, "questTemp.LSC.UW_ready"))
				{
					link.l5 = "Hello, Henrik. So, is the suit ready for a dive?";
					link.l5.go = "immersion_next";
				}
				if(CheckAttribute(pchar, "questTemp.LSC.UW_end") && CheckCharacterItem(pchar, "underwater"))
				{
					link.l5 = "I want to return your suit.";
					link.l5.go = "immersion_next_2";
				}
				// квестовые ветки				
				link.l1 = LinkRandPhrase("Got anything interesting to say?","Has anything new happened on the island?","Will you tell me the latest gossip?");
				link.l1.go = "rumours_LSC";
				link.l3 = "I just wanted to know how you're doing.";
				link.l3.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "And I am Henrik Vedecker. Though most of the locals know me as the Mechanic, and that is actually a very accurate description.";
			if(pchar.questTemp.LSC == "mechanic")
			{
				link.l1 = "Are you Henrik Vedecker? Glad to meet you! I was looking for you.";
				link.l1.go = "mechanic";
			}
			else
			{
				link.l1 = "You must be the jack of all trades, right?";
				link.l1.go = "meeting_1";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting_1":
			dialog.text = "Oh, yes, the Narwhals truly appreciate my skills. My tools allow them to recover many valuables from the lost ships of the outer ring, so they can buy provisions from Admiral Dodson\nActually, science and exploration are my passion. Therefore, I apologize if I won't be able to spend enough time with you – my experiments take up almost all of it.";
			link.l1 = "I see. I won't bother you without reason, mister Vedecker, I assure you. I am very glad to meet you!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "mechanic":
			dialog.text = "Were you? And why?";
			link.l1 = "Ole Christiansen has told me about you. He's also known as the White Boy.";
			link.l1.go = "mechanic_1";
		break;
		
		case "mechanic_1":
			dialog.text = "Ah, that funny guy! Yes, yes, I know him. And what did he tell you?";
			link.l1 = "I am sorry if my next question sounds stupid, but... I will ask you anyway. Ole told me that you might teach me how to dive to the bottom, underwater. Please don't laugh at me if it's just his imagination.";
			link.l1.go = "mechanic_2";
		break;
		
		case "mechanic_2":
			dialog.text = "It's true. I've been at the bottom myself several times. Though I don't dive anymore, the shoal is crawling with giant crabs these days and, as you can see, I am not capable of fighting them. I am a scientist, I can't fight those things.\nBesides, there were also two other men, two Narwhals, who used to dive, but they eventually stopped doing so—looting the holds of the outer ring ships turned out to be safer than diving to a place infested by giant crabs.\nNow they rarely use my equipment, not a single dive in the last few months because of the suit's fracture...";
			link.l1 = "Do you really have a suit that lets you dive to the bottom? Did I mishear you?";
			link.l1.go = "mechanic_3";
		break;
		
		case "mechanic_3":
			dialog.text = "Your ears are in the right place, young man. I have invented and crafted the suit myself. It is made of thick, thoroughly soaked, completely watertight canvas, metal parts, and a steel helmet forged by me and Jurgen in his smithy\nI also reinforced the suit with a metal chest plate, knee pieces, chest pieces, and boots for better protection against crabs and extra weight\nSpecial tanks, filled with pressurised air, provide life-support and the ability to spend some time underwater. The suit is unique, and I am quite proud of it.";
			link.l1 = "That is splendid. But did you mention that the suit is damaged?";
			link.l1.go = "mechanic_4";
		break;
		
		case "mechanic_4":
			dialog.text = "Unfortunately, that's true. Several parts of the suit were connected by metal plates to provide flexibility and extra protection, but the seawater affected them badly. The plates became rusty after years of use and lost their waterproof qualities.\nIt's fortunate that I noticed the damage and prevented anyone from dying. Even the dry suit contained some salt and water, which had already done their harmful work.";
			link.l1 = "Well... But you can repair the suit! You can replace the old rusty parts with new ones... Right?";
			link.l1.go = "mechanic_5";
		break;
		
		case "mechanic_5":
			dialog.text = "For what purpose? To replace them again a year later? Do you know how difficult this work is? To assemble the suit with flexible joints and make it waterproof? It is at least a week’s work with no rest.";
			link.l1 = "And that is the reason why you are willing to throw your invention away?";
			link.l1.go = "mechanic_6";
		break;
		
		case "mechanic_6":
			dialog.text = "No, of course not. I have an idea. I need to make the joints from a metal that can't be destroyed by water or salt. And I know which metal can help...";
			link.l1 = "So what is the problem?";
			link.l1.go = "mechanic_7";
		break;
		
		case "mechanic_7":
			dialog.text = "The problem is that this metal is very rare. I have only one piece, which is certainly not enough. I need at least ten more pieces, or even fifteen.";
			link.l1 = "And what is this... metal you are talking about?";
			link.l1.go = "mechanic_8";
		break;
		
		case "mechanic_8":
			dialog.text = "Oh, this is a unique metal, truly underestimated by many. It has high durability, plasticity, and it is absolutely immune to exposure – neither water nor salt can damage it\nPerhaps you have already seen this metal before. It is white, looks like silver, which is why the Spanish called it 'silver'. Ha! It is a hundred times better than silver! Even better than gold! One day they will understand that, but the right time hasn't come yet.";
			link.l1 = "Listen, why can't you use other types of metal instead? Why don't you use gold to make those plates? I've never heard that gold can rust or go to ruin.";
			link.l1.go = "mechanic_9";
		break;
		
		case "mechanic_9":
			dialog.text = "You have a flexible and lively mind, young man. That's good to know. Unfortunately, your proposition won't work. The thought of gold was the first thing that crossed my mind. But gold is too soft to link different parts of the suit\nAlas, platinum is the only material that will do. I'll be crafting parts only from it, even if it takes years to collect enough. But I've seen pieces of the metal before on the Island - it is often mixed with silver due to its appearance.";
			link.l1 = "Hm. And if I help you find enough of this... 'silver', will you lend me the suit so that I can dive underwater?";
			link.l1.go = "mechanic_10";
		break;
		
		case "mechanic_10":
			dialog.text = "No need to ask! Of course I will. I already told you I wouldn't dive there because of the crabs, and nobody else wants to either.";
			link.l1 = "Then show me this piece of metal so I can understand what I need to find.";
			link.l1.go = "mechanic_11";
		break;
		
		case "mechanic_11":
			dialog.text = "So you are going to search for it? Excellent. Here, take this piece as an example. Look for it among the silver ore and nuggets. It won't be easy to find, but you'll manage. There are small dark spots on silver, but our metal is clear and much harder than silver. The easiest way to test it is by scratching a silver coin on it; if the coin gets damaged, then you've found it.";
			link.l1 = "Fine. I am going to search for it immediately. Got any suggestions where I should look for it?";
			link.l1.go = "mechanic_12";
		break;
		
		case "mechanic_12":
			GiveItem2Character(pchar, "jewelry10");
			PlaySound("interface\important_item.wav");
			Log_Info("You have received a platinum ingot");
			dialog.text = "Alas, I don't. If I knew where to find it, I'd do it myself. But I can give you some advice though. Search the Rivados ships. I don't visit them, so it's very likely that they might have it.";
			link.l1 = "I will consider it, Henrik. I hope that I'll be lucky.";
			link.l1.go = "mechanic_13";
		break;
		
		case "mechanic_13":
			dialog.text = "Collect ten more pieces. That's the minimum needed to repair the suit. Good luck!";
			link.l1 = "Thank you. Farewell, Mechanic!";
			link.l1.go = "mechanic_14";
		break;
		
		case "mechanic_14":
			DialogExit();
			pchar.questTemp.LSC = "platinum";
			AddQuestRecord("LSC", "7");
			if (GetSummonSkillFromName(pchar, SKILL_FORTUNE) >= 65 || rand(2) == 1) pchar.questTemp.LSC.PtAddQty = 0;
			else pchar.questTemp.LSC.PtAddQty = rand(4);
		break;
		
		case "mechanic_15":
			RemoveItems(pchar, "jewelry10", 11);
			dialog.text = "Well, well, show me... Excellent! Well done, young man! Was it difficult?";
			link.l1 = "Not really...";
			link.l1.go = "mechanic_16";
		break;
		
		case "mechanic_16":
			dialog.text = "Well, now I can start the repairs. I won't waste any time and I'll begin tomorrow. You're really eager to dive, aren't you?";
			link.l1 = "Indeed. I really want to explore underwater.";
			link.l1.go = "mechanic_17";
		break;
		
		case "mechanic_17":
			dialog.text = "That is very good, because I will have a favour to ask of you when we organise your dive. But we will talk about it later. Come and see me in five days, I hope I will have finished the repairs.";
			link.l1 = "Fine. I wish you luck!";
			link.l1.go = "mechanic_18";
		break;
		
		case "mechanic_18":
			dialog.text = "Luck is needed for certain, but the suit's repair will mostly require skill. Besides, I will need to spend a day near the furnace with Jurgen to make plate from the metal you've brought me.";
			link.l1 = "Then I won't bother you. See you in five days. Goodbye!";
			link.l1.go = "mechanic_19";
		break;
		
		case "mechanic_19":
			DialogExit();
			pchar.questTemp.LSC = "platinum_wait";
			AddQuestRecord("LSC", "8");
			SetFunctionTimerCondition("LSC_PrepareUnderwater_Check", 0, 0, 5, false); // таймер
			AddCharacterExpToSkill(pchar, "Fortune", 300);
		break;
		
		case "mechanic_20":
			if (sti(pchar.questTemp.LSC.PtAddQty) == 0)
			{
				dialog.text = "Yes. Jurgen and I did a hell of a job, and the amount of pieces you brought was enough to do it. The suit is repaired and ready. I only need to run a few tests, but I am sure it is fine. Come tomorrow at 10 a.m. — I will fill the tanks with air and you will be able to do what you want.";
				link.l1 = "Excellent! I look forward to it. See you tomorrow, Henrik!";
				link.l1.go = "mechanic_24";
				DeleteAttribute(pchar, "questTemp.LSC.PtAddQty");
				AddCharacterExpToSkill(pchar, "Fortune", 100);
			}
			else
			{
				dialog.text = "I have to disappoint you, "+pchar.name+". As I suspected, there is not enough metal. I need "+FindRussianQtyString(sti(pchar.questTemp.LSC.PtAddQty))+" more pieces to finish the repair. I have to ask you for help again.";
				link.l1 = "Well now, I didn't expect such a turn of events. Fine, I'll try to find the nuggets you lack.";
				link.l1.go = "mechanic_21";
			}
		break;
		
		case "mechanic_21":
			dialog.text = "I will wait for you. You can be sure that this amount will be enough. Just bring them and I will finish the work in a day.";
			link.l1 = "I hope so... See you!";
			link.l1.go = "mechanic_22";
		break;
		
		case "mechanic_22":
			DialogExit();
			pchar.questTemp.LSC = "platinum_add_wait";
			AddQuestRecord("LSC", "9");
			AddQuestUserData("LSC", "sQty", FindRussianQtyString(sti(pchar.questTemp.LSC.PtAddQty)));
		break;
		
		case "mechanic_23":
			RemoveItems(pchar, "jewelry10", sti(pchar.questTemp.LSC.PtAddQty));
			dialog.text = "Splendid! Now the suit will be restored. I only need to run several tests, but I am sure that it is fine. Come tomorrow at 10 a.m. – I will fill the tanks with air and you will be able to do what you want.";
			link.l1 = "Excellent! I look forward to it. See you tomorrow, Henrik!";
			link.l1.go = "mechanic_24";
		break;
		
		case "mechanic_24":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.LSC.PtAddQty"))
			{
				iTemp = 2;
				sTemp = "the day after tomorrow";
				DeleteAttribute(pchar, "pchar.questTemp.LSC.PtAddQty");
			}
			else
			{
				iTemp = 1;
				sTemp = "tomorrow";
			}
			if (!CheckAttribute(pchar, "questTemp.LSC.NatanTalk")) string sText = "But I have to find Nathaniel Hawk first before I dive."; //не было разговора с Натаном
			else sText = "";
			AddQuestRecord("LSC", "10");
			AddQuestUserData("LSC", "sText1", sTemp);
			AddQuestUserData("LSC", "sText2", sText);
			pchar.quest.LSC_prepunderwater.win_condition.l1 = "Timer";
			pchar.quest.LSC_prepunderwater.win_condition.l1.date.hour  = 10;
			pchar.quest.LSC_prepunderwater.win_condition.l1.date.day   = GetAddingDataDay(0, 0, iTemp);
			pchar.quest.LSC_prepunderwater.win_condition.l1.date.month = GetAddingDataMonth(0, 0, iTemp);
			pchar.quest.LSC_prepunderwater.win_condition.l1.date.year  = GetAddingDataYear(0, 0, iTemp);
			pchar.quest.LSC_prepunderwater.function = "LSC_PrepareUnderwater";
			pchar.questTemp.LSC = "wait";
		break;
		
		case "immersion":
			dialog.text = "Yes, the suit is ready and filled with air. You can dive.";
			if (!CheckAttribute(pchar, "questTemp.LSC.NatanTalk")) // не было разговора с Натаном
			{
				link.l1 = "Good. But I can't dive now, I need to solve a problem concerning my... friend, Nathan Hawk. I can't find him. Can the suit wait a bit?";
				link.l1.go = "natan";
			}
			else
			{
				link.l1 = "Splendid! When do we begin? Now?";
				link.l1.go = "immersion_1";
			}
		break;
		
		case "natan":
			dialog.text = "Sure. It can wait. Will you be searching for your friend for a whole year?";
			link.l1 = "Sure, I won't. Perhaps I'll find him even today. I'll visit you just after I finish my business with him.";
			link.l1.go = "natan_1";
		break;
		
		case "natan_1":
			dialog.text = "Yes, please. Come when you are ready to dive.";
			link.l1 = "Thanks!";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "underwater_natan";
		break;
		
		case "immersion_1":
			dialog.text = "Right now, if you want. But let me give you a little instruction first. You will start your dive from the 'Phoenix' platform; you can get there from the San Gabriel's stern. There is a hoist that will take you to the bottom and back. This is the only way to return\nSo you'd better remember the location of the hoist underwater and don't get lost. The suit's tanks have enough air for twenty minutes of diving. Watch your time or you'll suffocate\nDon't stray too far from the hoist or you won't be able to return in time, and God save you if you leave our shoal – you'll be flattened like a flatfish\nBe careful and watch out for crabs. If you get too close, they'll attack you. Don't take risks if you don't have to; you won't be able to kill a whole pack of them, and running away quickly is not an option down there.";
			link.l1 = "I'll handle the crabs. I've got the rest. Don't dive too deep, don't stray far from the hoist, and don't forget about the time. When can I dive?";
			link.l1.go = "immersion_2";
		break;
		
		case "immersion_2":
			dialog.text = "Whenever you want, but only from 7 a.m. until 9 p.m. You won't be able to see a thing in the dark.";
			link.l1 = "Got it.";
			link.l1.go = "immersion_4";
		break;
		
		case "immersion_4":
			dialog.text = "That's just it. Take the suit from the room by the platform. Take it off after a dive and bring it to me. I will fill it with air again. But don't try to dive more than once per day; even 20 minutes of diving and breathing compressed air is bad for your health.";
			link.l1 = "Well, I won't dive more than once a day then.";
			link.l1.go = "immersion_5";
		break;
		
		case "immersion_5":
			dialog.text = "I am glad you understand. Now go, and good luck!";
			link.l1 = "Thanks!";
			link.l1.go = "immersion_6";
		break;
		
		case "immersion_6":
			DialogExit();
			pchar.questTemp.LSC = "first_immersion"; // флаг на первое погружение
			pchar.questTemp.LSC.immersion = "true"; // погружение возможно
			pchar.quest.LSC_takeUnderwater.win_condition.l1 = "locator";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.location = "FenixPlatform";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.locator_group = "item";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.locator = "armor";
			pchar.quest.LSC_takeUnderwater.function = "LSC_takeUnderwater"; // выдача костюма
			pchar.quest.LSC_UnderwaterDolly.win_condition.l1 = "locator";
			pchar.quest.LSC_UnderwaterDolly.win_condition.l1.location = "Underwater";
			pchar.quest.LSC_UnderwaterDolly.win_condition.l1.locator_group = "quest";
			pchar.quest.LSC_UnderwaterDolly.win_condition.l1.locator = "dolly";
			pchar.quest.LSC_UnderwaterDolly.function = "LSC_FindUnderwaterDolly"; // нашли статую
			NextDiag.CurrentNode = "after_first_immersion"; // нода после первого погружения
			AddQuestRecord("LSC", "11");
			QuestPointerToLoc("UnderWater", "quest", "dolly");
		break;
		
		case "after_first_immersion":
			if (CheckAttribute(pchar, "questTemp.LSC.immersion"))
			{
				dialog.text = "So, why are you still here? The suit is waiting for you.";
				link.l1 = "Yes, yes. I am on my way.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "So, how did the first dive go?";
				if (CheckAttribute(pchar, "questTemp.LSC.FindDolly"))
				{
					link.l1 = "Most excellent, and I am satisfied with the results. I found a stone idol in the sunken galleon. I heard that Rivados had made some sacrificial offerings to it before. Tell me, Henrik, do you know anyone who could tell me more about it?";
					link.l1.go = "af_immersion_1";
				}
				else
				{
					link.l1 = "Fine. I did it! It was really interesting, though a bit thrilling.";
					link.l1.go = "af_immersion_2";
				}
			}
			NextDiag.TempNode = "after_first_immersion";
		break;
		
		case "af_immersion_1":
			dialog.text = "Are you interested in our history? Go to Antonio Betancourt. He was born here. He lives on the flute Pluto. If he doesn't know anything about it - no one does.";
			link.l1 = "Excellent! I will definitely pay him a visit.";
			link.l1.go = "af_immersion_2";
			pchar.questTemp.LSC.Betancur = "true";
			AddQuestRecord("LSC", "14");
		break;
		
		case "af_immersion_2":
			dialog.text = "Leave the suit here. Come back tomorrow or any other day, I will fill it with air.";
			if (CheckCharacterItem(pchar, "underwater"))
			{
				link.l1 = "Sure. Here is your suit. Thanks!";
				link.l1.go = "af_immersion_3";
			}
			else
			{
				link.l1 = "Certainly. I will bring it at once!";
				link.l1.go = "af_immersion_wait";
			}
		break;
		
		case "af_immersion_wait":
			dialog.text = "Well, have you brought me my equipment?";
			if (CheckCharacterItem(pchar, "underwater"))
			{
				link.l1 = "Sure. Here is your suit. Thanks!";
				link.l1.go = "af_immersion_3";
			}
			else
			{
				link.l1 = "I will do it at once!";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "af_immersion_wait";
		break;
		
		case "af_immersion_3":
			DialogExit();
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			RemoveItems(pchar, "underwater", 1);
			LocatorReloadEnterDisable("SanGabrielMechanic", "reload3", false);
			SetFunctionTimerCondition("LSC_ReadyUnderwater", 0, 0, 1, false);
			NextDiag.CurrentNode = "First time";
			// даем старт мини-квестам с крабикусами
			sld = characterFromId("Carpentero");
			if(!CheckAttribute(sld, "quest.crab")) sld.quest.crab = "begin";
			if (GetCharacterIndex("LSC_Jacklin") != -1)
			{
				sld = characterFromId("LSC_Jacklin");
				sld.quest.crab = "true";
			}
		break;
		
		// блок погружений, за искл. первого
		case "immersion_next":
			if (CheckAttribute(npchar, "quest.guarantee")) // требует залог
			{
				dialog.text = "Yes, of course. The suit has been tested and filled with air. Do you have the pledge with you? 500,000 pesos?";
				if (sti(pchar.money) >= 500000)
				{
					link.l1 = "Yes, of course. Here, take it.";
					link.l1.go = "immersion_next_pay";
				}
				else
				{
					link.l1 = "Oops! I forgot about it. I'll bring it at once...";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Yes, of course. The suit has been tested and filled with air. Check the 'Phoenix' platform as usual.";
				link.l1 = "Then I'll dive. Thanks!";
				link.l1.go = "immersion_next_1";
			}
		break;
		
		case "immersion_next_1":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.LSC.UW_ready"); 
			LocatorReloadEnterDisable("LostShipsCity_town", "reload72", false); //открываем вход в Феникс
			pchar.questTemp.LSC.immersion = "true"; // погружение возможно
			pchar.quest.LSC_takeUnderwater.win_condition.l1 = "locator";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.location = "FenixPlatform";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.locator_group = "item";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.locator = "armor";
			pchar.quest.LSC_takeUnderwater.function = "LSC_takeUnderwater"; // выдача костюма
		break;
		
		case "immersion_next_2":
			dialog.text = "Fine. Come back tomorrow or later. I am going to prepare the suit.";
			link.l1 = "Thank you, Mechanic!";
			link.l1.go = "immersion_next_3";
		break;
		
		case "immersion_next_3":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.LSC.UW_end"); 
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			RemoveItems(pchar, "underwater", 1);
			if (CheckAttribute(npchar, "quest.guarantee")) AddMoneyToCharacter(pchar, 500000); // возврат залога
			LocatorReloadEnterDisable("SanGabrielMechanic", "reload3", false);
			SetFunctionTimerCondition("LSC_ReadyUnderwater", 0, 0, 1, false);
		break;
		
		case "immersion_next_pay":
			AddMoneyToCharacter(pchar, -500000);
			dialog.text = "You will get your money back when you return the suit. Fair deal.";
			link.l1 = "Thank you, Mechanic! I'm going to dive now.";
			link.l1.go = "immersion_next_1";
		break;
		// блок погружений
		
	//--------------------------------------вернулся на Остров---------------------------------------------
		case "return":
			dialog.text = "Wait a second, please! What statue? A-ah, I get it now. You mean that idol in the sunken ship 'San-Geronimo', don't you? So those Rivados tales are true?";
			link.l1 = "Exactly! And there are no tales. I know of two more idols in the archipelago that teleport people who touch them from one to another, in a circle.";
			link.l1.go = "return_1";
		break;
		
		case "return_1":
			dialog.text = "I see, I see. I will have to trust you, though your words are anti-scientific nonsense. Teleports, statues... ha! And who could even think of it, how do such things even work?";
			link.l1 = "Just trust me and don't try to find any logic here. I'm not lying.";
			link.l1.go = "return_2";
		break;
		
		case "return_2":
			dialog.text = "Fine. But I hope you didn't lose the suit during that teleportation of yours?";
			if(CheckCharacterItem(pchar, "underwater"))
			{
				link.l1 = "Sure, I didn't. It saved me from the Caribs, so to speak. Here it is.";
				link.l1.go = "return_4";
			}
			else
			{
				link.l1 = "Sure, I didn't. It saved me from the Caribs, so to speak. But I don't have it with me now.";
				link.l1.go = "return_3";
			}
		break;
		
		case "return_3":
			dialog.text = "So bring it to me, damn it! We won't talk until you bring it back to me, understand?";
			link.l1 = "Calm down, Mechanic. I'll return it to you!";
			link.l1.go = "exit";
			NextDiag.TempNode = "return_underwater";
		break;
		
		case "return_underwater":
			if(CheckCharacterItem(pchar, "underwater"))
			{
				dialog.text = "Ah, you actually brought my suit! Thank you, I was starting to worry about it.";
				link.l1 = "There was no need to worry about it. I promised you I would return it.";
				link.l1.go = "return_4";
			}
			else
			{
				dialog.text = "Don't even come here until you have my suit.";
				link.l1 = "Fine, fine.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "return_underwater";
		break;
		
		case "return_4":
			DeleteAttribute(pchar, "questTemp.LSC.UW_end"); 
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			RemoveItems(pchar, "underwater", 1);
			SetFunctionTimerCondition("LSC_ReadyUnderwater", 0, 0, 1, false);
			dialog.text = "Very good. I had started to think about making a new one, but it would be a year's work at least... I am glad that you have shown fine judgement and returned my property in one piece. I will even give you a present.";
			link.l1 = "Are you serious?";
			link.l1.go = "return_5";
		break;
		
		case "return_5":
			dialog.text = "Sure, I am! You helped me repair the suit and didn't throw it away at the first opportunity. You've been taking care of it, and finally you've brought it back to me. Anyway, here is a fine toolbox. Learn how to use it. You'll be able to make a lot of useful things with its help.";
			link.l1 = "And what else could I expect from the Mechanic! Of course, the toolbox! Thank you, Henrik, I am touched... I didn't deserve such a gift.";
			link.l1.go = "return_6";
		break;
		
		case "return_6":
			GiveItem2Character(pchar, "mechanic_tool");
			Log_Info("You have received a toolbox");
			PlaySound("interface\important_item.wav");
			dialog.text = "I know better what you deserved and what you didn't. Take it! It will be useful to you. But I will give you the suit again only if you pledge 500,000 pesos because of your habit of teleporting via idols.";
			link.l1 = "Shiver me timbers! Well, I understand... precautionary measures...";
			link.l1.go = "return_7";
		break;
		
		case "return_7":
			dialog.text = "Sure. And what if you escape with it one day? Then the money will be my compensation.";
			link.l1 = "Fine, Henrick. I agree. To be honest, I thought you would never give it to me again.";
			link.l1.go = "return_8";
		break;
		
		case "return_8":
			dialog.text = "Not a chance. Pledge half a million and it's all yours.";
			link.l1 = "Deal! Can I take it as usual to dive then? From tomorrow?";
			link.l1.go = "return_9";
		break;
		
		case "return_9":
			dialog.text = "Exactly.";
			link.l1 = "Thanks! See you, Henrik!";
			link.l1.go = "return_10";
		break;
		
		case "return_10":
			DialogExit();
			AddQuestRecord("LSC", "26");
			npchar.quest.return_isl = "true";
			npchar.quest.guarantee = "true"; // залог за скафандр
			NextDiag.CurrentNode = "First time";
		break;
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("What are you doing there, huh? Thief!","Just look at that! As soon as I was lost in contemplation, you decided to check my chest!","Decided to check my chests? You won't get away with it!");
			link.l1 = "Damn it!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "What?! Decided to check my chests? You won't get away with it!";
			link.l1 = "Foolish girl!...";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Listen, you'd better put your weapon away. It makes me nervous.","You know, running around with a blade is not tolerated here. Put it away.","Listen, don't act like a medieval knight running around with a sword. Put it away, it doesn't suit you...");
			link.l1 = LinkRandPhrase("Fine.","Sure.","As you say...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Listen, I am a citizen of this city and I'd ask you to sheathe your blade.","Listen, I am a citizen of this city and I'd ask you to sheathe your blade");
				link.l1 = LinkRandPhrase("Fine.","Sure.","As you say...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Be careful, pal, running around with a weapon. I might get nervous...","I don't like it when people walk in front of me with their weapons drawn. It scares me...");
				link.l1 = RandPhraseSimple("Got it.","I am taking it away.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

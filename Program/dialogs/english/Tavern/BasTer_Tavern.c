// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions do you have?", "How can I help you, " + GetAddress_Form(NPChar) + "?"), "What is it, " + GetAddress_Form(NPChar) + "...", "This is the third time you're bothering me now...",
                          "More questions, I presume?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I changed my mind...", "I've got nothing to talk about at the moment."), "Umph, where has my memory gone...",
                      "Yes, it really is the third time...", "No, what questions?...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//Jason, суп из черепахи
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "baster" && !CheckAttribute(npchar, "quest.terrapin"))
			{
				link.l1 = "I'm looking for my old messmate Fernand Luc. I've got a couple of questions for him. I heard he really had a good time here a week ago...";
				link.l1.go = "terrapin";
			}
			//Sinistra Путеводная звезда
			if (CheckAttribute(pchar, "questTemp.PZ_BasTerTavern"))
			{
				link.l1 = "My friend and I agreed to meet here, but I don't see him anywhere. Do you know where he went? Is he still in town, or at least on the island? His name is Longway - he's Chinese.";
				link.l1.go = "PZ_BasTerTavern_1";
			}
			//--> Торговля по закону
			if (CheckAttribute(pchar, "questTemp.TPZ_Tavern_2"))
			{
				link.l1 = "Good news, "+npchar.name+". I have exactly what will save your situation. One hundred bottles of excellent wine and one hundred bottles of rum. With such a shipment your customers will once again bathe in rivers of booze. Are you ready to pay up?";
				link.l1.go = "TPZ_Tavern2_1";
			}
			if (CheckAttribute(pchar, "questTemp.TPZ_Tavern_3"))
			{
				link.l1 = "Well then, "+npchar.name+", are you ready to discuss the terms of the deal?";
				link.l1.go = "TPZ_Tavern2_11";
			}
			if (CheckAttribute(pchar, "questTemp.TPZ_Tavern_4"))
			{
				link.l1 = "So, "+npchar.name+". On my end, everything is settled and the goods are already on their way to the tavern. Shall we proceed with the payment?";
				link.l1.go = "TPZ_Tavern3_1";
			}
			//<-- Торговля по закону
		break;
		
		//суп из черепахи
		case "terrapin":
			dialog.text = "He might still be having a good time while he's in hell. Your mate's dead, so you're a tad late, captain. That man over there sitting at the farthest table paid for his funeral, although I get the feeling that he's the same man that caused it. He's got a hanging face, as they say. His name is Robert Martene. If you want, you can walk over and ask him yourself. ";
			link.l1 = "Thanks, mate. I'll go have a talk with monsieur Robert. We'll drink for the soul of poor old Luc that his soul may rest in peace...";
			link.l1.go = "terrapin_1";
			npchar.quest.terrapin = "true";
		break;
		
		case "terrapin_1":
			DialogExit();
			AddQuestRecord("Terrapin", "4");
			pchar.questTemp.Terrapin = "rober";
		break;
		
		// Sinistra - Квест "Длинные тени старых грехов" ==>
		case "DTSG_BasTerTavern_1":
			dialog.text = "What's there to discuss? He attacked you and your friend, you fought back, I see this almost every day. Good job. Now I just have to clean up the mess...";
			Link.l1 = "You'll clean it up, I'm sure you're used to it by now. What do you know about him?";
			Link.l1.go = "DTSG_BasTerTavern_2";
		break;
		
		case "DTSG_BasTerTavern_2":
			dialog.text = "Not much, really. He showed up a couple of days ago. Liked it here, even rented a house on the outskirts of town. Came by often, paid regularly. And, most importantly, he behaved himself well all this time, never saying a bad word to anyone. I'm still shocked he attacked you and your friend\nI thought he might settle down here for good.";
			Link.l1 = "In a way, he did. Well, that's not much, but thanks for that, my friend. See you around.";
			Link.l1.go = "DTSG_BasTerTavern_3";
		break;
		
		case "DTSG_BasTerTavern_3":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DTSG_BasTerTavern");
			LAi_LocationDisableOfficersGen("BasTer_tavern", false);
			SetQuestHeader("DTSG");
			AddQuestRecord("DTSG", "1");
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			Return_KnippelOfficer();
			
			PChar.quest.DTSG_BasTerDom.win_condition.l1 = "locator";
			PChar.quest.DTSG_BasTerDom.win_condition.l1.location = "BasTer_town";
			PChar.quest.DTSG_BasTerDom.win_condition.l1.locator_group = "reload";
			PChar.quest.DTSG_BasTerDom.win_condition.l1.locator = "HutFish1";
			PChar.quest.DTSG_BasTerDom.win_condition = "DTSG_BasTerDom";
			
			SetTimerCondition("DTSG_BasTerDom_Timer", 0, 0, 7, false);
			SetTimerCondition("DTSG_Etap2", 0, 0, 14, false);
		break;
		// <== Квест "Длинные тени старых грехов" - Sinistra
		
		// Sinistra - Квест "Путеводная звезда" ==>
		
		case "PZ_BasTerTavern_1":
			dialog.text = "That name doesn't mean anything to me, and generally, I don't let people like him into my establishment, nor do I take any interest in them.";
			Link.l1 = "Fair enough. Alright, see you later.";
			Link.l1.go = "PZ_BasTerTavern_2";
		break;
		
		case "PZ_BasTerTavern_2":
			DialogExit();
			bDisableLandEncounters = true;
			DeleteAttribute(pchar, "questTemp.PZ_BasTerTavern");
			DeleteAttribute(pchar, "questTemp.PZ_BasTerAlkash");
			pchar.questTemp.PZ_BasTerTavern2 = true;
			DeleteQuestCondition("PZ_BasTer_Opozdal");
			DelMapQuestMarkIsland("Guadeloupe");
			
			PChar.quest.PZ_BasTer_Strazha.win_condition.l1 = "location";
			PChar.quest.PZ_BasTer_Strazha.win_condition.l1.location = "BasTer_town";
			PChar.quest.PZ_BasTer_Strazha.win_condition = "PZ_BasTer_Strazha";
		break;
		
		// <== Квест "Путеводная звезда" - Sinistra
		
		//--> Торговля по закону
		case "TPZ_Tavern_1":
			dialog.text = "Oh, "+GetAddress_Form(NPChar)+", it’s even worse than that. My supplier from Antigua lost his distillery — pirates raided it, everything burned to the ground. Now he says we shouldn't expect any rum or wine for at least two months.";
			link.l1 = "Then find a new supplier. You’re not going to just sit around waiting for two months, are you?";
			link.l1.go = "TPZ_Tavern_2";
		break;
		
		case "TPZ_Tavern_2":
			dialog.text = "Finding a reliable supplier is not easy. I tried dealing with small traders, but they’re unreliable. Sometimes the goods arrive, sometimes not. With a large supplier, everything is like clockwork — stable deliveries and high quality.";
			link.l1 = "Well, if normal suppliers are a problem, maybe you should look for someone in the shadows? They rarely let you down, and the goods are always in stock.";
			link.l1.go = "TPZ_Tavern_3";
		break;
		
		case "TPZ_Tavern_3":
			dialog.text = "You understand, "+GetAddress_Form(NPChar)+", this tavern is under public scrutiny. I don’t want any trouble with the authorities. If someone with a solid reputation brought the goods, I’d not only buy a batch but gladly turn a blind eye to where it came from\nAfter all, when the situation is this dire, who cares about such trivialities? The main thing is to avoid suspicion. But in the long term, I’ll only deal with serious and honest merchants.";
			link.l1 = "I understand. Well, maybe I’ll stop by again later. Any problem can be solved with a smart approach.";
			link.l1.go = "TPZ_Tavern_4";
		break;
		
		case "TPZ_Tavern_4":
			DialogExit();
			AddQuestRecord("TPZ", "2");
			pchar.questTemp.TPZ_ContraInfo = true;
			AddLandQuestMark(characterFromId("BasTer_Smuggler"), "questmarkmain");
		break;
		
		case "TPZ_Tavern2_1":
			dialog.text = "Captain, this is incredible! How did you pull this off? No matter, really. Just tell me, what do you want in exchange for such a luxurious shipment of alcohol? And will everything be fine with the paperwork?";
			if (sti(pchar.reputation.nobility) >= 40)
			{
				link.l1 = "Paperwork? Of course it’s all perfectly in order. You’re not actually planning to check it, are you?";
				link.l1.go = "TPZ_Tavern2_2";
				notification("Honor check passed", "None");
			}
			else
			{
				link.l1 = "Paperwork?";
				link.l1.go = "TPZ_Tavern2_2_badrep";
				notification("Honor level too low! ("+XI_ConvertString(GetReputationName(40))+")", "None");
			}
			DeleteAttribute(pchar, "questTemp.TPZ_Tavern_2");
			DelLandQuestMark(npchar);
		break;
		
		case "TPZ_Tavern2_2_badrep":
			dialog.text = "Captain, please understand, it's vital for me to get this shipment of alcohol. But my freedom and reputation are just as valuable. The governor is ruthless with black-market dealers, even the smallest ones. If people spoke well of you, I could turn a blind eye to the lack of paperwork, but right now... you're attracting too much unwanted attention...";
			link.l1 = "Looks like it's time to do some good deeds. Wait for me, I'll be back soon.";
			link.l1.go = "exit";
			pchar.questTemp.TPZ_Tavern_3 = true;
		break;
		
		case "TPZ_Tavern2_2":
			dialog.text = "This time, I suppose I’ll take your word for it. So, how much do you want for the batch?";
			link.l1 = "I want thirty doubloons for every ten bottles of wine, and five doubloons for every ten bottles of rum. The full batch — one hundred bottles of each — will cost you three hundred and fifty doubloons.";
			link.l1.go = "TPZ_Tavern2_3";
		break;
		
		case "TPZ_Tavern2_3":
			dialog.text = "Hold on, Captain! That's daylight robbery! Yes, my situation is desperate, but I won’t run my business at a loss!";
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 50)
			{
				link.l1 = "Perhaps I can give you a discount. But that’s not all. I want to be your regular supplier. I guarantee smooth and timely deliveries. I’ll rent a warehouse in Basse-Terre, and you’ll receive your stock directly from there without delay. There will always be enough alcohol stored to prevent any shortages. With the discount, the price will be two hundred and forty doubloons. What do you say?";
				link.l1.go = "TPZ_Tavern2_4";
				notification("Check passed", SKILL_COMMERCE);
			}
			else
			{
				link.l1 = "Alright, I'm willing to lower the price to two hundred and forty doubloons per shipment — I'm aiming for a long-term partnership. In the future, I can meet all your needs and ensure reliable supply. What do you say?";
				link.l1.go = "TPZ_Tavern2_7";
				notification("Skill too low (50)", SKILL_COMMERCE);
			}
		break;
		
		case "TPZ_Tavern2_4":
			dialog.text = "That's still more than I used to pay. But I’ve learned my lesson — stability is worth the price. I agree to your terms, but know this: one slip-up, and I’ll find another supplier. I need to understand what I’m paying extra for. And one more thing — how do you plan to handle the authorities?";
			link.l1 = "I’ll take care of that right now. Once everything’s sorted out, I’ll come back with the goods.";
			link.l1.go = "TPZ_Tavern2_5";
		break;
		
		case "TPZ_Tavern2_5":
			dialog.text = "Please don’t delay. I can’t wait to see my customers' mugs filled again.";
			link.l1 = "Don’t worry, I won’t keep you waiting.";
			link.l1.go = "TPZ_Tavern2_6";
		break;
		
		case "TPZ_Tavern2_6":
			DialogExit();
			AddQuestRecord("TPZ", "5");
			DeleteAttribute(pchar, "questTemp.TPZ_Tavern_3");
			AddLandQuestMark(characterFromId("BasTer_Mayor"), "questmarkmain");
			pchar.questTemp.TPZ_guber_1 = true;
			pchar.questTemp.TPZ_Vino240 = true;
			
			AddCharacterExpToSkill(pchar, "Commerce", 200);
		break;
		
	    case "TPZ_Tavern2_7":
			dialog.text = "Still too expensive, Captain. This price is higher than what I used to pay my previous supplier. Even if I agree now, in a couple of months I’ll have to go back to him once production resumes. I don’t see a reason to overpay.";
			link.l1 = "I understand. Alright. My final offer — two hundred doubloons. If that's not acceptable, then there’s no point continuing this conversation.";
			link.l1.go = "TPZ_Tavern2_8";
		break;
		
		case "TPZ_Tavern2_8":
			dialog.text = "Alright, deal. Two hundred is acceptable. But tell me, how do you plan to deal with the island’s authorities? As I said before, the governor strictly monitors the island for smuggling. He won’t tolerate deals happening right under his nose.";
			link.l1 = "Ha-ha, well, I'd argue with that. But rest assured — I intend to handle all the bureaucratic hurdles swiftly.";
			link.l1.go = "TPZ_Tavern2_9";
		break;
		
		case "TPZ_Tavern2_9":
			dialog.text = "Please don’t delay. I can’t wait to see my customers’ mugs filled again.";
			link.l1 = "Don’t worry, I won’t keep you waiting.";
			link.l1.go = "TPZ_Tavern2_10";
		break;
		
		case "TPZ_Tavern2_10":
			DialogExit();
			AddQuestRecord("TPZ", "6");
			DeleteAttribute(pchar, "questTemp.TPZ_Tavern_3");
			AddLandQuestMark(characterFromId("BasTer_Mayor"), "questmarkmain");
			pchar.questTemp.TPZ_guber_1 = true;
			pchar.questTemp.TPZ_Vino200 = true;
		break;
		
		case "TPZ_Tavern2_11":
			if (sti(pchar.reputation.nobility) >= 40)
			{
				dialog.text = "Of course, Captain! So, how much do you want for your shipment?";
				link.l1 = "For every ten bottles of wine I want thirty doubloons, and five doubloons for every ten bottles of rum. The whole shipment — one hundred bottles of each — will cost you three hundred and fifty doubloons.";
				link.l1.go = "TPZ_Tavern2_3";
				notification("Honor check passed", "None");
			}
			else
			{
				dialog.text = "I'm sorry, Captain, but your reputation still leaves much to be desired.";
				link.l1 = "Damn...";
				link.l1.go = "exit";
				notification("Honor too low! ("+XI_ConvertString(GetReputationName(40))+")", "None");
			}
		break;
		
		case "TPZ_Tavern3_1":
			if (CheckAttribute(pchar, "questTemp.TPZ_Vino240"))
			{
				dialog.text = "Of course, Captain, of course! 240 doubloons, just as agreed. Here you go!";
				link.l1 = "Pleasure doing business with you! Now the tavern will once again overflow with rum and wine.";
				link.l1.go = "TPZ_Tavern3_2";
				AddItems(pchar, "gold_dublon", 240);
			}
			if (CheckAttribute(pchar, "questTemp.TPZ_Vino200"))
			{
				dialog.text = "Of course, Captain, of course! 200 doubloons, just as agreed. Here you go!";
				link.l1 = "Pleasure doing business with you! Now the tavern will once again overflow with rum and wine.";
				link.l1.go = "TPZ_Tavern3_2";
				AddItems(pchar, "gold_dublon", 200);
			}
			DelLandQuestMark(npchar);
		break;
		
		case "TPZ_Tavern3_2":
			dialog.text = "You’re my savior, Captain! I will expect similar shipments every two weeks. I hope you’ll strictly keep to your obligations. Another dry spell like that, and my tavern won’t survive...";
			link.l1 = "No need to worry, "+npchar.name+". My representative in the city is Christian Deluce. He’ll make sure your tavern never lacks wine or rum.";
			link.l1.go = "TPZ_Tavern3_3";
		break;
		
		case "TPZ_Tavern3_3":
			dialog.text = "Christian? I know him. A responsible man, though... well, never mind. Since you’ve cleared things with the authorities, I suppose I can trust him.";
			link.l1 = "Excellent. Now, if you’ll excuse me, I have one more matter to settle in this town.";
			link.l1.go = "TPZ_Tavern3_4";
		break;
		
		case "TPZ_Tavern3_4":
			dialog.text = "Do visit us more often!";
			link.l1 = "I certainly will.";
			link.l1.go = "TPZ_Tavern3_5";
		break;
		
		case "TPZ_Tavern3_5":
			DialogExit();
			AddQuestRecord("TPZ", "7");
			DeleteAttribute(pchar, "questTemp.TPZ_Tavern_4");
			
			sld = CharacterFromID("TPZ_Kristian");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.filename = "Quest\MiniEvents\TradingByLaw_dialog.c";
			sld.dialog.currentnode = "Kristian_31";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		//<-- Торговля по закону
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

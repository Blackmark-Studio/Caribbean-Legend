// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions do you have?", "How can I help you?"), "You tried to ask me a question a little while ago...", "I have never met people with such curiosity in my shipyard or anywhere else in this town.",
                          "What's with all the questions? My job is to build ships. Let's take care about that.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind...", "I've got nothing to talk about at the moment."), "Umph, where has my memory gone...",
                      "Hm, well...", "Go ahead...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// Addon 2016-1 Jason пиратскаЯ линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx"))
            {
				if (pchar.questTemp.Mtraxx == "silk_2" || pchar.questTemp.Mtraxx == "silk_3")
				{
					link.l1 = "I've heard this shipyard deals with improving the ship's sailing speed. It requires some silk sailcloth which is very rare. Would you like... to talk about this?";
					link.l1.go = "mtraxx";
				}
			}
			if (CheckAttribute(npchar, "quest.upgradeship")) {
				link.l2 = "I'm from Miss MacArthur, regarding...";
				link.l2.go = "helen_upgradeship";
			}
			
			if (CheckAttribute(npchar, "quest.upgradeship.money") && HelenCanUpgrade()) {
				link.l2 = "Begin the overhaul on the ship!";
				link.l2.go = "helen_upgradeship_money";
			}
		break;
		
		// Addon 2016-1 Jason пиратскаЯ линейка
		case "mtraxx":
            dialog.text = "Could you be more clear, young man? What exactly brought you here? If you want to improve your ship - let's get to the business right away.";
			link.l1 = "Not entirely. The type of services you perform require goods which are not freely available in the store. I would like to offer you the same type of those materials you might require.";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
            dialog.text = "Well-well... Hmm... Are you aware that only the authorities of this colony are allowed to deal with such strategic goods? You are free to provide your own silk for me to work on improving your ship, however, selling it is strictly forbidden. As is buying it from me - such activities will be fined rather heavily.";
			link.l1 = "Well, this isn't a store, nor is it a customs office...";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = "I acquire all of the silk sailcloth directly from my clients, or purchase limited quantities with a special permission of the governor. If you don't have any further questions then please, let me get back to my job.";
			link.l1 = "Hmm... Very well. Have a good day, master.";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            DialogExit();
			AddQuestRecord("Roger_2", "5");
			pchar.questTemp.Mtraxx = "silk_4";
		break;
		
		case "helen_upgradeship":
			dialog.text = "Oh, I know! Lucky you, Captain. Is it about a complete overhaul of the ship? We'll take care of everything; our shipyard is on par with those in Plymouth!";
			link.l1 = "I assume this won't be a free service?";
			link.l1.go = "helen_upgradeship_1";
		break;
		
		case "helen_upgradeship_1":
			dialog.text = "Of course, Captain, such services can't be free, even for Cromwell! However, I keep my word and will only take money - you won't have to smuggle contraband.";
			link.l1 = "Understandable. How much?";
			link.l1.go = "helen_upgradeship_2";
		break;
		
		case "helen_upgradeship_2":
			dialog.text = "It depends on the size of your flagship, Captain. A first-rank ship will cost you five thousand doubloons, and a fifth-rank - only a thousand.";
			link.l1 = "Alright, I'll come to you once I make a decision.";
			link.l1.go = "exit";
			
			npchar.quest.upgradeship.money = true;
		break;
		
		case "helen_upgradeship_money":
			dialog.text = "Excellent, now I have all I need. I'll start working, then.";
			link.l1 = "I am waiting.";
			link.l1.go = "helen_upgradeship_money_1";
			
			iTemp = GetCharacterShipType(pchar);
			sld = GetRealShip(iTemp);
			iTemp = (7 - sti(sld.class)) * 1000;
			RemoveDublonsFromPCharTotal(iTemp);
		break;
		
		case "helen_upgradeship_money_1":
			AddTimeToCurrent(6, 30);
			dialog.text = "... I guess that's it... Quality is guaranteed.";
			link.l1 = "Thanks! I'll check it out.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenUpgradeShip2");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

bool HelenCanUpgrade() {
	int shipIndex = GetCharacterShipType(pchar);
	if (shipIndex == SHIP_NOTUSED) {
		return false;
	}
	
	sld = GetRealShip(shipIndex);
	if (sti(sld.class) == 7) {
		return false;
	}
	
	int cost = (7 - sti(sld.class)) * 1000;
	return (PCharDublonsTotal() >= cost);
}

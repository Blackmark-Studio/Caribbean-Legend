// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What do you want? Ask away.", "I am listening to you, what's the question?"), "This is the second time you are trying to ask...", "This is the third time you are trying to ask...",
                          "When is this going to end?! I am a busy man, working on colony matters and you are still bothering me!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I changed my mind...", "Not now. Wrong place and time."), "True... But later, not now...",
                      "I'll ask... But a bit later...", "I am sorry, " + GetAddress_FormToNPC(NPChar) + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_2" && !CheckAttribute(npchar, "quest.patria") && !CheckAttribute(pchar, "questTemp.Patria.Visiter_Late"))
			{
				link.l1 = TimeGreeting()+" Monsieur. I am here as ordered by the Governor-General Chevalier de Poincy. My task is to deliver a baron by the name of Noel Forget to Tortuga, who arrived from the parent state with a task to inspect the colonies, his main purpose is establishing a French West-Indies trading Company. Let me introduce him to you... He will explain all the details himself.";
                link.l1.go = "patria_portpax";
			}
			// Rebbebion, квест "Путеводная звезда"
			if (CheckAttribute(pchar, "questTemp.PZ.PortPaxMayorTalk"))
			{
				link.l1 = "Your Lordship, you wanted to see me?";
				link.l1.go = "PZ1";
			}
			// Украденное воспоминание
			if (CheckAttribute(pchar, "questTemp.UV_DialogMayor"))
			{
				link.l1 = "Excellency, I come bearing information of a most sensitive nature that requires your attention.";
				link.l1.go = "UV_1";
			}
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple("You have taken everything already. What else do you want?", "Is there anything left that you didn't grab?");
            link.l1 = RandPhraseSimple("Just looking around...", "Just checking, I might forget to take something...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		
		// Jason НСО
		case "patria_portpax":
			dialog.text = "I am very glad to meet you, Captain Charles de Maure, and the Baron. I will do everything so that Monsieur Forget's stay in our colony is as comfortable as possible. And taking advantage of the fact that such a high-ranking Monsieur paid me a visit, I will petition you for one matter.";
			link.l1 = "Most interesting! Tell us about your matter, your Grace.";
			link.l1.go = "patria_portpax_1";
		break;
		
		case "patria_portpax_1":
			dialog.text = "In recent months, our colony hasn't been visited by any representative of the Governor-General, as if they completely forgot about us at Saint Kitts! And in the meantime, the Spaniards, craving to make the whole of Hispaniola purely Spanish and to whom the French settlers and buccaneers at the west of the island are a major annoyance, are preparing an attack! My patrol officers, our trading captains and even ordinary fishermen have reported that a powerful Spanish squadron is gathering in Santiago, and that it is preparing to attack Port-au-Prince!";
			link.l1 = "Is the evidence clear enough, your Majesty?";
			link.l1.go = "patria_portpax_2";
		break;
		
		case "patria_portpax_2":
			dialog.text = "I don't have accurate intel, but such plenty of information from completely random people can't be mere rumors. Our colony is very important for France, we have the best plantations here, which the Baron can personally see. To lose this colony or even expose it to the risk of being looted is unacceptable!";
			link.l1 = "I will take your evidence into account and inform Chevalier de Poincy. I'm sure that he will take immediate measures.";
			link.l1.go = "patria_portpax_3";
		break;
		
		case "patria_portpax_3":
			dialog.text = "Thank you, captain...";
			link.l1 = "";
			link.l1.go = "patria_portpax_4";
		break;
		
		case "patria_portpax_4":
			DialogExit();
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_9";
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", "governor1");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
			npchar.quest.patria = "true";
		break;
		
		case "PZ1":
			DeleteAttribute(pchar, "questTemp.PZ.PortPaxMayorTalk");
			dialog.text = "No, I did not summon you, monsieur. Did you want something?";
			link.l1 = "How could I? But your messenger met us; he said you had prepared one of the houses in the town for me...";
			link.l1.go = "PZ2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ2":
			dialog.text = "What house, what messenger, what is this insolence?!";
			link.l1 = "What do you mean, what messenger... His name is Henri Thibaut, and...";
			link.l1.go = "PZ3";
		break;
		
		case "PZ3":
			dialog.text = "WHAT? Do you even know who he is? Apparently not. But it doesn't matter. What's Levasseur's nephew doing in my town?";
			link.l1 = "Oh, my God...";
			link.l1.go = "PZ4";
		break;
		
		case "PZ4":
			dialog.text = "De Maure, can you hear me? Monsieur?";
			link.l1 = "...";
			link.l1.go = "PZ5";
		break;
		
		case "PZ5":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorRunToLocator(pchar, "reload", "reload1", "PZ_SharleBezhitObratno", -1);
			bDisableCharacterMenu = true;
			InterfaceStates.Buttons.Save.enable = false;
			SetMusic("music_teleport");
			pchar.questTemp.lockedMusic = true;
		break;
		
		//--> Украденное воспоминание
		case "UV_1":
			dialog.text = "A sensitive matter, you say? You have piqued my interest, Captain. Please, continue—you have my full attention.";
			link.l1 = "The matter concerns your niece, Julie. She enlisted my services to recover a necklace that had been stolen from her possession.";
			link.l1.go = "UV_2";
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			DelLandQuestMark(npchar);
		break;

		case "UV_2":
			dialog.text = "A necklace? Curious. I have no recollection of such an item among her possessions.";
			link.l1 = "Allow me to present the facts in sequence, Governor. I have successfully recovered the necklace in question. My investigation revealed that the thief was your niece's lady's maid, Giselle. From my observations of the merchant who purchased the stolen item, I strongly suspect this is neither her first nor her last such transgression.";
			link.l1.go = "UV_3";
		break;

		case "UV_3":
			dialog.text = "Most illuminating. Pray continue with your account.";
			link.l1 = "What caught my attention, Excellency, was that Julie chose not to seek your assistance in this matter. The necklace, it seems, was a gift from an individual with whom you have expressly forbidden her to associate. Believing that your restrictions arise from the wisest and most protective intentions, I felt obligated to bring this matter to your attention and return the necklace directly to you.";
			link.l1.go = "UV_4";
			TakeItemFromCharacter(pchar, "SM_necklace_Julie");
		break;

		case "UV_4":
			dialog.text = "Your judgment proves sound"+GetSexPhrase(", Captain","")+". I commend your discretion in bringing this directly to me rather than indulging my niece's youthful indiscretions.";
			link.l1 = "I act only with her welfare in mind, Governor. I have no doubt your guidance springs from the same wellspring of concern and wisdom.";
			link.l1.go = "UV_5";
		break;

		case "UV_5":
			dialog.text = "Indeed, Captain. As her uncle and guardian, her well-being is my paramount concern. Please accept these one hundred and fifty doubloons as a token of my appreciation for your discretion. I also present you with this navigational compass—may it guide you safely through your journeys across treacherous waters.";
			link.l1 = "I am honored by your generosity, Excellency, though such reward was unnecessary. Regrettably, I must now bid you farewell—the tide waits for no sailor, and my vessel requires my attention.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("UV_End");
			AddItems(pchar, "gold_dublon", 150);
			GiveItem2Character(PChar, "compass1");
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
		break;
		//<-- Украденное воспоминание
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

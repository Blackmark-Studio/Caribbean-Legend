// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What do you want? Ask away.", "I am listening to you, what's the question?"), "It is the second time you are trying to ask...", "It is the third time you are again trying to ask...",
                          "When is it going to end?! I am a busy man, working on the colony's matters and you are still trying to ask something!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I have changed my mind...", "Not now. Wrong place and time."), "True... But later, not now...",
                      "I'll ask... But a bit later...", "I am sorry, " + GetAddress_FormToNPC(NPChar) + "...", npchar, Dialog.CurrentNode);			  
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Baster_church") && !CheckAttribute(npchar, "quest.utensil"))
			{
				link.l1 = "I have a delicate matter to you. Not long ago one privateer has granted a golden cross with a lazurite on it to the parish of Basse-Terre. The problem is that the cross was stolen from the Santiago's parish and a clergyman was murdered during the theft...";
                link.l1.go = "guardoftruth";
			}
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_9_continue" && !CheckAttribute(npchar, "quest.frigate"))
			{
				link.l1 = "I arrived by the order of Governor General Philippe de Poincy to take command of your armed frigate.";
                link.l1.go = "patria";
			}
			if (CheckAttribute(npchar, "quest.frigate.wait") && GetCompanionQuantity(pchar) < 5)
			{
				link.l1 = "I'm ready to take the frigate into the squadron.";
                link.l1.go = "patria_2";
			}
			// Jason Дороже золота
			if (CheckAttribute(pchar, "questTemp.GoldenGirl") && pchar.questTemp.GoldenGirl == "baster")
			{
				link.l1 = "I've got a meeting here with one person...";
                link.l1.go = "baster_goldengirl";
			}
			//--> Торговля по закону
			if (CheckAttribute(pchar, "questTemp.TPZ_guber_1"))
			{
				link.l1 = "Monsieur, I intend to pursue commercial activity within the town. Specifically, I'm interested in the steady, large-scale trade of spirits.";
				link.l1.go = "TPZ_guber_1";
			}
			//<-- Торговля по закону

		break;
		//************************** Квестовые штрумы ************************
		case "Cupture_after":
            dialog.text = RandPhraseSimple("You have taken everything already. What else do you want?", "Is there anything left that you didn't grab?");
            link.l1 = RandPhraseSimple("Just looking around...", "Just checking, I might forget to take something...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		
		case "guardoftruth":
			dialog.text = "Hm. That's quite interesting. But why do you think that I care about the problems of the Spanish?";
			link.l1 = "It is not about the Spanish, Monsieur. Religion doesn't divide people by nationality. There is an item which is covered in the holy servant's blood in your parish and there was a desecration made to the Santiago's parish...";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "";
			link.l1 = "I ask you to show a justice and to order holy father to return the cross to it's owners.";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "And since when have you become such a true and earnest believer, ha, "+pchar.name+"? Spanish are not our friends and I see no reason to push on the holy father in this matter. The cross was a gift and that's fine. Our priest has no connection to that theft and murder, so...";
			link.l1 = "And you can't help me, right?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "To be honest, "+pchar.name+", I don't feel that I have to. I have no love to those Papist's fanatics.";
			link.l1 = "I see. Sorry for troubling you, Monsieur...";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			DialogExit();
			npchar.quest.utensil = "true";
			AddQuestRecord("Guardoftruth", "28");
		break;
		
		// Jason НСО
		case "patria":
			if (GetCompanionQuantity(pchar) > 4)
			{
				dialog.text = "The ship is ready, but you don't have a free spot for it in your squadron. Captain, reduce your squadron and return, then I will immediately give you the frigate.";
				link.l1 = "Fine.";
				link.l1.go = "patria_1";
			}
			else
			{
				dialog.text = "Yes, of course, the ship is ready to sail. Its captain is aware and will follow all of your orders.";
				link.l1 = "Then we're setting out. Goodbye, Your Grace.";
				link.l1.go = "patria_3";
			}
		break;
		
		case "patria_1":
			DialogExit();
			npchar.quest.frigate.wait = "true";
		break;
		
		case "patria_2":
			DeleteAttribute(npchar, "quest.frigate.wait");
			dialog.text = "Excellent. Prepare to greet your new ship. It's captain is aware and will follow all of your orders.";
			link.l1 = "Then we're setting out. Goodbye, Your Grace.";
			link.l1.go = "patria_3";
		break;
		
		case "patria_3":
			DialogExit();
			npchar.quest.frigate = "true";
			Patria_BastionFrigateGlp(); // присоединяем фрегат
		break;
		
		// Jason Дороже золота
		case "baster_goldengirl":
			dialog.text = "Ah, Monsieur Charles de Maure, perfect timing! My old friend is very eager to meet you and asked to let him know of your arrival. Please, come to my living room, I will let Angerran know immediately. How did you two get familiar by the way?";
			link.l1 = "Gambled together. He lost, we had a small fight. I suppose, Monsieur de Chievous would like to fix things between us.";
			link.l1.go = "baster_goldengirl_1";
		break;
		
		case "baster_goldengirl_1":
			dialog.text = "No doubt! I hope you will get things straight between the two of you. Angerran might be not the most pleasant person to deal with, but he is clever and honorable, just like you are. It is a rare breed.";
			link.l1 = "You flatter me, Excellency. I will wait for him in the living room if you don't mind.";
			link.l1.go = "baster_goldengirl_2";
		break;
		
		case "baster_goldengirl_2":
			dialog.text = "But of course, suit yourself, make yourself at home. Perhaps you will have to wait a little. I will order to bring some drinks.";
			link.l1 = "Thank you, Excellency, but I'll pass. I will just sit and wait for our mutual... friend.";
			link.l1.go = "baster_goldengirl_3";
		break;
		
		case "baster_goldengirl_3":
			DialogExit();
			pchar.questTemp.GoldenGirl = "baster1";
			DoQuestReloadToLocation("CommonResidence_3", "reload", "reload1", "GoldenGirl_AngerranInResidence");
		break;
		
		//--> Торговля по закону
		case "TPZ_guber_1":
			dialog.text = "Captain, you were wise to approach me. We are making every effort to combat illicit trade on this island, and I truly welcome upright captains who seek to establish business through legal channels.";
			link.l1 = "So, what are the terms and steps required to commence trade?";
			link.l1.go = "TPZ_guber_2";
			DelLandQuestMark(npchar);
		break;

		case "TPZ_guber_2":
			dialog.text = "It is rather straightforward. To trade in spirits, you must pay a monthly tax of one hundred doubloons to the treasury, maintain proper records, and submit regular activity reports. Once the funds are deposited, you may begin trading in earnest.";
			link.l1 = "Excellent. The terms are entirely reasonable. A local resident by the name of Christian Deluce shall act on my behalf. I trust that will not pose a problem?";
			link.l1.go = "TPZ_guber_3";
		break;

		case "TPZ_guber_3":
			dialog.text = "As you wish, Captain. But bear in mind – full responsibility for your protégé shall rest upon your shoulders. Should he transgress, you shall share in his consequences.";
			link.l1 = "Of course. Thank you for the clarification, Governor. We shall make the arrangements, and Christian will see to the tax payment.";
			link.l1.go = "TPZ_guber_4";
		break;

		case "TPZ_guber_4":
			dialog.text = "Splendid. I am pleased to see such a diligent approach. I wish you success in your enterprise.";
			link.l1 = "Much obliged. I trust our cooperation will benefit the city. Farewell.";
			link.l1.go = "TPZ_guber_5";
		break;

		case "TPZ_guber_5":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.TPZ_guber_1");
			AddQuestRecord("TPZ", "11");

			sld = CharacterFromID("TPZ_Kristian");
			sld.dialog.filename = "Quest\MiniEvents\TradingByLaw_dialog.c";
			sld.dialog.currentnode = "Kristian_21";
			ChangeCharacterAddressGroup(sld, "BasTer_houseF3", "barmen", "stay");
			LAi_SetStayType(sld);
			AddLandQuestMark(sld, "questmarkmain");
		break;
		//<-- Торговля по закону
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

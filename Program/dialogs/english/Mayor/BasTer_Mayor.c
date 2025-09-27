// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What do you want? Ask away.","I am listening to you, what is the question?"),"It is the second time you are trying to ask...","It is the third time you are trying to ask again...","When will this end?! I am a busy man, working on the colony's affairs, and you are still trying to ask something!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I have changed my mind...","Not now. Wrong place and time."),"True... But later, not now...","I'll ask... But a bit later...","I am sorry, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);			  
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Baster_church") && !CheckAttribute(npchar, "quest.utensil"))
			{
				link.l1 = "I have a delicate matter for you. Not long ago, a privateer donated a golden cross with a lazurite stone to the parish of Basse-Terre. The problem is that the cross was stolen from the parish of Santiago, and a clergyman was murdered during the theft...";
                link.l1.go = "guardoftruth";
			}
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_9_continue" && !CheckAttribute(npchar, "quest.frigate"))
			{
				link.l1 = "I have arrived by order of Governor General Philippe de Poincy to take command of your armed frigate.";
                link.l1.go = "patria";
			}
			if (CheckAttribute(npchar, "quest.frigate.wait") && GetCompanionQuantity(pchar) < COMPANION_MAX)
			{
				link.l1 = "I'm ready to take the frigate into the squadron.";
                link.l1.go = "patria_2";
			}
			// Jason Дороже золота
			if (CheckAttribute(pchar, "questTemp.GoldenGirl") && pchar.questTemp.GoldenGirl == "baster")
			{
				link.l1 = "I've got a meeting here with someone...";
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
            dialog.text = RandPhraseSimple("You have taken everything already. What else do you want?","Is there anything left that you haven't grabbed?");
            link.l1 = RandPhraseSimple("Just looking around...","Just checking, I might forget to take something...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		
		case "guardoftruth":
			dialog.text = "Hm. That's quite interesting. But why do you think I care about the problems of the Spanish?";
			link.l1 = "It is not about the Spanish, Monsieur. Religion doesn't divide people by nationality. There is an item covered in the holy servant's blood in your parish, and there was a desecration committed in Santiago's parish...";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "";
			link.l1 = "I ask you to show justice and to order the holy father to return the cross to its owners.";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "And since when did you become such a true and earnest believer, ha, "+pchar.name+"? The Spanish are not our friends and I see no reason to press the holy father on this matter. The cross was a gift and that's fine. Our priest has no connection to that theft and murder, so...";
			link.l1 = "And you can't help me, right?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "To be honest, "+pchar.name+", I don't feel that I have to. I have no love for those Papist fanatics.";
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
				dialog.text = "The ship is ready, but you don't have a free berth for it in your squadron. Captain, reduce your squadron and return, then I will immediately give you the frigate.";
				link.l1 = "Fine.";
				link.l1.go = "patria_1";
			}
			else
			{
				dialog.text = "Yes, of course, the ship is ready to sail. Her captain is aware and will follow all of your orders.";
				link.l1 = "Then we're setting off. Goodbye, Your Grace.";
				link.l1.go = "patria_3";
			}
		break;
		
		case "patria_1":
			DialogExit();
			npchar.quest.frigate.wait = "true";
		break;
		
		case "patria_2":
			DeleteAttribute(npchar, "quest.frigate.wait");
			dialog.text = "Excellent. Prepare to greet your new ship. Its captain is aware and will follow all of your orders.";
			link.l1 = "Then we're setting off. Goodbye, Your Grace.";
			link.l1.go = "patria_3";
		break;
		
		case "patria_3":
			DialogExit();
			npchar.quest.frigate = "true";
			Patria_BastionFrigateGlp(); // присоединяем фрегат
		break;
		
		// Jason Дороже золота
		case "baster_goldengirl":
			dialog.text = "Ah, Monsieur Charles de Maure, perfect timing! My old friend is very eager to meet you and asked me to let him know of your arrival. Please, come to my living room, I will let Angerran know immediately. By the way, how did you two become acquainted?";
			link.l1 = "Gambled together. He lost, we had a bit of a scuffle. I suppose Monsieur de Chievous would like to mend things between us.";
			link.l1.go = "baster_goldengirl_1";
		break;
		
		case "baster_goldengirl_1":
			dialog.text = "No doubt! I hope you will sort things out between the two of you. Angerran may not be the most pleasant person to deal with, but he is clever and honourable, just like you. It's a rare breed.";
			link.l1 = "You flatter me, Excellency. I will wait for him in the drawing room if you don't mind.";
			link.l1.go = "baster_goldengirl_2";
		break;
		
		case "baster_goldengirl_2":
			dialog.text = "But of course, suit yourself, make yourself at home. You may have to wait a little. I'll order some drinks to be brought.";
			link.l1 = "Thank you, Excellency, but I'll pass. I'll just sit and wait for our mutual... friend.";
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

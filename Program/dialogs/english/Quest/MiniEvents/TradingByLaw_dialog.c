void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "What do you want?";
			link.l1 = "Nothing.";
			link.l1.go = "exit";
		break;

		case "Kristian":
			dialog.text = "Welcome to my humble abode! I am Christian. Christian Deluce at your service. What brings you to my doorstep?";
			link.l1 = "The name's Captain "+GetFullName(pchar)+". I seek to acquire a sizable quantity of spirits. I trust my meaning is clear?";
			link.l1.go = "Kristian_2";
			DelLandQuestMark(npchar);
		break;

		case "Kristian_2":
			dialog.text = "What??? Who would spread such falsehoods? A grievous misunderstanding, I assure you! I deal not in spirits of any kind!";
			link.l1 = "Well, well... It appears I've found precisely whom I seek.";
			link.l1.go = "Kristian_3";
		break;

		case "Kristian_3":
			dialog.text = "Oh heavens, no-no-no! What accusations you make! Trading spirits? Me? I... I merely, er, that is to say... Very well, I do possess certain libations, but all perfectly lawful! I simply procure refreshments for private citizens, ah... for festivities and modest social assemblies!";
			link.l1 = "Why such trembling, good man? I come not as your jailer but as your benefactor. Your fortunes may rise, and my purse grow heavier by a few doubloons in the bargain.";
			link.l1.go = "Kristian_4";
		break;

		case "Kristian_4":
			dialog.text = "Me? N-nervous? Preposterous! What cause have I for nerves? I'm a man of spotless character - my dwelling stands in the very shadow of the governor's residence! I break no laws whatsoever, upon my honor!";
			link.l1 = "So you're not involved in spirits trade? A terrible shame indeed. I came bearing an opportunity for substantial profit. The kind of doubloons a modest clandestine merchant could scarcely imagine. But since you're not my man, I'll trouble you no further and be on my way. Unless...?";
			link.l1.go = "Kristian_5";
		break;
		
		case "Kristian_5":
			dialog.text = "Ah... hold a moment... "+GetAddress_Form(NPChar)+"... forgive me, my wits scatter like gulls in a storm, I've quite forgotten your distinguished name.";
			link.l1 = "Captain "+GetFullName(pchar)+".";
			link.l1.go = "Kristian_6";
		break;

		case "Kristian_6":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+" "+pchar.lastname+", truth be told, I... that is... I may know the whereabouts of the individual you seek. I could relay to this person... your generous proposition.";
			link.l1 = "Relay? Surely you jest. Do you truly believe affairs of this delicate nature should pass through unnecessary hands?";
			link.l1.go = "Kristian_7";
		break;

		case "Kristian_7":
			dialog.text = "You speak true. But... heaven help me... the die is cast... yes, I am indeed your man.";
			link.l1 = "Now we understand one another, Christian. The tavern faces a dire shortage of spirits, and I believe we both stand to gain handsomely from this predicament.";
			link.l1.go = "Kristian_8";
		break;

		case "Kristian_8":
			dialog.text = "Captain, I'm well acquainted with the innkeeper's woes. Folk have been beating a path to my door, and it frightens me to continue my modest trade - too many eyes watching now. I had hoped that perhaps you... well, a person of your standing might...";
			link.l1 = "Why not approach the innkeeper yourself with your wares?";
			link.l1.go = "Kristian_9";
		break;

		case "Kristian_9":
			dialog.text = "He... he'd sooner embrace a leper than do business with me. That pompous fool holds nothing but contempt for humble merchants of my station.";
			link.l1 = "Indeed, his reputation precedes him. He may scorn your offerings directly. But presented through me - that's quite another matter.";
			link.l1.go = "Kristian_10";
		break;

		case "Kristian_10":
			dialog.text = "You offer yourself as the go-between? I find that arrangement quite agreeable... We've recently acquired a shipment of remarkable size - never managed such quantity before! Would've kept my cellars stocked for half a year at least. But by the grace of God Almighty, we narrowly escaped discovery\nStill can't fathom how we slipped through the governor's net. Tempting fate twice in such a manner would be nothing short of self-destruction.";
			link.l1 = "Then perhaps 'tis time you stepped into the light. Not fully, mind you, but enough to conduct your affairs with less peril.";
			link.l1.go = "Kristian_11";
		break;

		case "Kristian_11":
			dialog.text = "S-step into the light? But... why, that demands powerful friends! And considerable coin! To what purpose? Surely you, a sea captain with your own vessel, don't intend to drop anchor permanently and become a mere tavern supplier?";
			link.l1 = "As for connections, my reach extends where yours cannot. Regarding finances... the investment should prove modest. And to your last concern - fear not. You'll operate as my agent in these matters. I shall be your shield, and you my steady source. Our arrangement will be lasting and mutually profitable. You gain reliable custom, I secure dependable merchandise. How does such a venture strike you?";
			link.l1.go = "Kristian_12";
		break;

		case "Kristian_12":
			dialog.text = "I was certain this was some elaborate snare. Yet in truth, your proposition sounds... most enticing indeed. Stability, dependability... Never did I imagine such fortune would smile upon me. "+GetSexPhrase("Monsieur","Mademoiselle")+", you have my wholehearted agreement! What quantity do you wish to purchase?";
			link.l1 = "Let us first establish your trade on proper footing, then we shall discuss particulars. What quantities of rum and wine presently grace your storeroom?";
			link.l1.go = "Kristian_13";
		break;

		case "Kristian_13":
			dialog.text = "At this very moment? Ah... Perhaps we should inspect my cellar, where I might provide a precise accounting of my inventory.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TPZ_GoToPogreb");	// спускаемся в погреб
		break;
		
		// погреб
		case "Kristian_15":
			dialog.text = "Let's see... What treasures lie below? Ah yes\nMy current stock consists of precisely one hundred bottles of fine rum and one hundred bottles of excellent wine.";
			link.l1 = "A fair beginning, I should say. Once we've settled your import difficulties, could you maintain such deliveries each month without fail?";
			link.l1.go = "Kristian_16";
		break;

		case "Kristian_16":
			dialog.text = "Most assuredly, Captain! Nay, I could manage thrice, no-no... four times this quantity! You'll suffer no delays - I shall maintain ample reserves at all times, ensuring any misfortune can be swiftly overcome without affecting your supply.";
			link.l1 = "Name your price for this cargo.";
			link.l1.go = "Kristian_17";
		break;

		case "Kristian_17":
			dialog.text = "I would consider fair payment to be: ten doubloons per ten bottles of wine and three doubloons for each ten bottles of rum. In sum, one hundred and thirty doubloons for the complete cargo.";
			link.l1 = "Very well. I shall parley with the innkeeper and return forthwith.";
			link.l1.go = "Kristian_18";
		break;
		
		case "Kristian_18":
			DialogExit();
			
			NextDiag.CurrentNode = "Kristian_18_1";
			pchar.questTemp.TPZ_Tavern_2 = true;
			AddLandQuestMark(characterFromId("BasTer_tavernkeeper"), "questmarkmain");
			AddQuestRecord("TPZ", "4");
		break;
		
		case "Kristian_18_1":
			dialog.text = "Captain, what tidings? How fared your discussion with the innkeeper?";
			link.l1 = "I've yet to speak with him. That's my next port of call.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Kristian_18_1";
		break;

		case "Kristian_21":
			dialog.text = "How did it go, Captain? Were you able to reach an agreement with the innkeeper?";
			if (CheckAttribute(pchar, "questTemp.TPZ_Vino240"))
			{
				link.l1 = "I've done most admirably, Christian. He'll buy this and all future shipments for two hundred and forty doubloons. For the first load, I'll pay you the one hundred and thirty you asked, and keep the rest as my reward. Future profits, however, shall be yours entirely.";
			}
			if (CheckAttribute(pchar, "questTemp.TPZ_Vino200"))
			{
				link.l1 = "I've done well, Christian. He'll purchase this and future shipments for two hundred doubloons. For the first, I'll pay you the one hundred and thirty you requested, and keep the difference as fair compensation. All future profits are yours alone.";
			}
			link.l1.go = "Kristian_22";
			DelLandQuestMark(npchar);
		break;

		case "Kristian_22":
			dialog.text = "That's astonishing news, Captain! I never dared dream of such a deal - thank you! But... perhaps you acted too quickly? The governor... I... that is...";
			link.l1 = "The governor is well aware. From now on, you'll pay a monthly fee of one hundred doubloons and submit proper trade reports.";
			link.l1.go = "Kristian_23";
		break;

		case "Kristian_23":
			dialog.text = "Unbelievable! How did you manage it, Captain? The governor is a stern man, and a fierce enemy of black marketeers...";
			link.l1 = "That's just it, Christian - he's against illicit trade, not honest dealings. He heard me out and laid out clear conditions for liquor commerce on the island. You'll be operating under my name now. For any misconduct, I bear the burden as much as you. So don't fail me, or I'll hunt you down even in the afterlife.";
			link.l1.go = "Kristian_24";
		break;

		case "Kristian_24":
			dialog.text = "I swear, Captain, you won't regret this!";
			link.l1 = "Now we must conclude matters with the innkeeper, and then we’ll settle the details of our arrangement.";
			link.l1.go = "Kristian_25";
		break;
		
		case "Kristian_25":
			dialog.text = "Of course, Captain. Are you ready to take the shipment right now? That will be one hundred and thirty doubloons.";
			if (PCharDublonsTotal() >= 130)
			{
				link.l1 = "Yes, here are your doubloons.";
				link.l1.go = "Kristian_26";
			}
			else
			{
				link.l1 = "At present, I lack the required funds. Remain here — I'll return with the payment.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Kristian_25_1";
			}
		break;

		case "Kristian_25_1":
			dialog.text = "Captain! You've returned to collect the goods? The price remains one hundred and thirty doubloons.";
			if (PCharDublonsTotal() >= 130)
			{
				link.l1 = "Indeed I have! Here's your payment.";
				link.l1.go = "Kristian_26";
			}
			else
			{
				link.l1 = "Regrettably, I still lack the funds. I shall call again later.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Kristian_25_1";
			}
		break;

		case "Kristian_26":
			dialog.text = "Much obliged! Take them! One hundred bottles of wine and one hundred bottles of rum, as promised.";
			link.l1 = "My crew shall see to the cargo. In the meantime, I must have a word with the innkeeper.";
			link.l1.go = "Kristian_27";
			RemoveDublonsFromPCharTotal(130);
		break;
		
		case "Kristian_27":
			DialogExit();
			
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.TPZ_Tavern_4 = true;
			AddLandQuestMark(characterFromId("BasTer_tavernkeeper"), "questmarkmain");
		break;
		
		case "Kristian_31":
			dialog.text = ""+pchar.name+"! You return so swiftly! Tell me, did our arrangement proceed favorably?";
			link.l1 = "All transpired most admirably, Christian. The tavern keeper shall require identical shipments twice monthly. Maintain a steady flow of spirits to his establishment, and you shall soon bid farewell to the very notion of want.";
			link.l1.go = "Kristian_32";
			DelLandQuestMark(npchar);
		break;

		case "Kristian_32":
			dialog.text = "Captain... you... 'tis as though Providence itself guided you to my threshold! A veritable miracle has unfolded before me - I scarce dare believe my fortune! By what deed have I merited such benevolence? Words fail to express my gratitude!";
			link.l1 = "I, however, can enlighten you, Christian. Each month, you shall reserve a select portion of your finest merchandise exclusively for my purchase, offering it to no other buyer. I shall acquire it at your stated rates - ten doubloons for each ten bottles of wine and three doubloons for each ten of rum.";
			link.l1.go = "Kristian_33";
		break;

		case "Kristian_33":
			dialog.text = "It would be my utmost pleasure, "+pchar.name+", to set aside merchandise for your exclusive procurement! Upon my honor, you shall never find me wanting! What quantity shall you require? Fifty bottles? A hundred perhaps? Name any sum you desire!";
			link.l1 = "Such quantities exceed my present requirements. Twenty bottles of each shall suffice admirably. Should my needs increase - you shall be promptly informed.";
			link.l1.go = "Kristian_34";
		break;

		case "Kristian_34":
			dialog.text = "Certainly, certainly! Then it is settled - twenty bottles of wine and twenty of rum for twenty-six doubloons. On the fifteenth day of each month, your merchandise shall await your collection. I shall welcome your esteemed presence whenever you choose to call, even if merely to exchange pleasantries!";
			link.l1 = "Splendid! One final matter requires emphasis, Christian. I have staked my reputation upon your integrity. Fail me not, lest you discover the consequence.";
			link.l1.go = "Kristian_35";
		break;

		case "Kristian_35":
			dialog.text = "I... what suggestion do you make, captain... surely you... no-no, I shall never disappoint! All shall be conducted with impeccable propriety, upon my very soul!";
			link.l1 = "Then until our paths cross once more!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TPZ_SpawnShip");
		break;
		
		case "Pirate_1":
			dialog.text = "You meddlesome "+GetSexPhrase("cur","strumpet")+"! Were you never taught that thrusting yourself into affairs not your own invites naught but misfortune?";
			link.l1 = "’Twas you who set upon my vessel unbidden, and now you dare accuse me of interference? Has madness seized your faculties entirely?";
			link.l1.go = "Pirate_2";
		break;

		case "Pirate_2":
			dialog.text = "Thunder blast my foremast! So you, "+GetSexPhrase("miserable whelp","worthless strumpet")+", haven't the faintest notion of the affairs you've entangled yourself in? Did you imagine the tavern's supplies simply vanished by chance?";
			link.l1 = "Do you claim responsibility for reducing that distillery to ashes?";
			link.l1.go = "Pirate_3";
		break;

		case "Pirate_3":
			dialog.text = "Ha-ha, at last the truth pierces your thick skull, may chain-shot rip through my innards! ’Twas indeed my doing! That supplier had his roots sunk too deep in the trade. But as you witness, I never fail to vanquish my rivals. And you shall share their fate, may grapeshot shred my sails to ribbons!";
			link.l1 = "Most amusing. Well then, let us discover the measure of your prowess, may Neptune's beasts feast upon your carcass! Ha-ha!";
			link.l1.go = "Pirate_4";
		break;
		
		case "Pirate_4":
			DialogExit();
			
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "CitizSeekCap_GivePrisoner");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Kristian_41":
			dialog.text = "Greetings, "+pchar.name+"! What favorable winds have carried you to my threshold?";
			if(CheckAttribute(pchar, "questTemp.TPZ_TradeVinoAndRom")) // торговля вином и ромом
			{
				if (GetDataDay() == 15)
				{
					link.l1 = "Good day, Christian. Have you my merchandise prepared?";
					link.l1.go = "Kristian_42";
				}
			}
			link.l2 = "Good day, Christian. I merely wished to ensure your affairs proceed favorably. I'll trouble you no further now.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Kristian_41";
		break;

		case "Kristian_42":
			if (CheckAttribute(pchar, "questTemp.TPZ_UpgradeVino"))
			{
				dialog.text = "Certainly, Captain! Could you entertain the slightest uncertainty regarding my diligence?";
				if (PCharDublonsTotal() >= 130)
				{
					link.l1 = "Not for a moment, Christian. Your payment, as agreed. I shall take my spirits now.";
					link.l1.go = "Kristian_43";
				}
				else
				{
					link.l2 = "Not in the slightest. Alas, I find my purse inconveniently light at present. I shall return when better provisioned.";
					link.l2.go = "exit";
					NextDiag.TempNode = "Kristian_41";
				}
			}
			else
			{
				dialog.text = "Certainly, Captain! Could you entertain the slightest uncertainty regarding my diligence?";
				if (PCharDublonsTotal() >= 26)
				{
					link.l1 = "Not for a moment, Christian. Here are your doubloons as agreed. I shall take possession of my spirits now.";
					link.l1.go = "Kristian_43";
				}
				else
				{
					link.l2 = "Not in the slightest. Alas, I find myself without proper payment at present. I shall return when my purse is appropriately weighted.";
					link.l2.go = "exit";
					NextDiag.TempNode = "Kristian_41";
				}
			}
			if(sti(pchar.questTemp.TPZ_KritstianVinoAndRom) >= 1 && !CheckAttribute(pchar, "questTemp.TPZ_KritstianVinoBlock")) // увеличить объём поставок вина и рома
			{
				link.l4 = "Christian, I wish to increase my standing order. A hundred bottles each of rum and wine per month, to be precise.";
				link.l4.go = "UpgradeVino";
			}
			if(sti(pchar.questTemp.TPZ_KritstianVinoAndRom) >= 1 && CheckAttribute(pchar, "questTemp.TPZ_KritstianVinoPotom") && sti(pchar.Money) >= 50000) // увеличить объём поставок вина и рома, если в первый раз не принесли
			{
				link.l4 = "Christian, I wish to reconsider expanding our arrangement.";
				link.l4.go = "UpgradeVino_Agreed";
			}
		break;
		
		case "Kristian_43":
			dialog.text = "Splendid. As ever, fresh stock shall await your pleasure on the fifteenth. I look forward to your next visit.";
			link.l1 = "You may count on my return. Until our paths cross again.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Kristian_41";
			
			if (CheckAttribute(pchar, "questTemp.TPZ_UpgradeVino"))
			{
				RemoveDublonsFromPCharTotal(130);
				AddItems(pchar, "potionrum", 100);
				AddItems(pchar, "potionwine", 100);
			}
			else
			{
				RemoveDublonsFromPCharTotal(26);
				AddItems(pchar, "potionrum", 20);
				AddItems(pchar, "potionwine", 20);
			}
			
			DeleteAttribute(pchar, "questTemp.TPZ_TradeVinoAndRom");
			SetFunctionTimerCondition("TPZ_KristianReturn", 0, 0, 1, false); // таймер
			AddCharacterExpToSkill(pchar, "Commerce", 100);
			pchar.questTemp.TPZ_KritstianVinoAndRom = sti(pchar.questTemp.TPZ_KritstianVinoAndRom) + 1; // счётчик покупок
		break;

		case "UpgradeVino":
			dialog.text = "Captain, while such an expansion would be most welcome for business, 'tis not without considerable expense! Greater quantities demand additional laborers, enlarged warehousing, chartering of more capacious vessels... Without proper investment, I could never ensure timely delivery of such substantial orders.";
			link.l1 = "And what sum might such arrangements require? What investment would guarantee smooth operation of this expanded enterprise?";
			link.l1.go = "UpgradeVino_2";
		break;

		case "UpgradeVino_2":
			dialog.text = "Fifty thousand pesos would suffice. Any further costs I shall bear from my own coffers.";
			link.l1 = "Fifty thousand? By my troth... that's no trifling sum. Can you truly not manage with more modest financing?";
			link.l1.go = "UpgradeVino_3";
		break;

		case "UpgradeVino_3":
			dialog.text = "With profound regret, Captain, I must insist this sum represents the absolute minimum. Should corners be cut, our venture might... shall we say, veer disastrously from its course. Such calamities would serve neither your interests nor mine, I daresay.";
			if (sti(pchar.Money) >= 50000)
			{
				link.l1 = "Here is your payment in full. See that you prove worthy of such trust, Christian.";
				link.l1.go = "UpgradeVino_5";
			}
			link.l2 = "On further reflection, Christian, this expansion may be somewhat premature. Let us revisit the matter when circumstances prove more favorable.";
			link.l2.go = "UpgradeVino_4";
		break;

		case "UpgradeVino_4":
			dialog.text = "As you wish, Captain. Should your considerations alter, I remain at your service.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Kristian_41";
			pchar.questTemp.TPZ_KritstianVinoBlock = true;
			pchar.questTemp.TPZ_KritstianVinoPotom = true;
		break;
		
		case "UpgradeVino_Agreed":
			dialog.text = "Captain, most splendid tidings! Have you brought the fifty thousand in silver to proceed forthwith?";
			if (sti(pchar.Money) >= 50000)
			{
				link.l1 = "Here is your payment in full. See that you prove worthy of such trust, Christian.";
				link.l1.go = "UpgradeVino_5";
			}
			link.l2 = "At present, my coffers lack the necessary funds. I shall return when my finances permit such investment.";
			link.l2.go = "UpgradeVino_4";
		break;

		case "UpgradeVino_5":
			dialog.text = "Upon my honor, "+pchar.name+", you shall never rue this decision! I shall commence preparations without delay. Beginning with your next collection, you may receive one hundred bottles of the finest rum and an equal measure of superb wine, all for the sum of one hundred and thirty doubloons per complete shipment.";
			link.l1 = "Most satisfactory. But remember – exercise the utmost discretion in all matters. Your conduct reflects directly upon my standing in these waters.";
			link.l1.go = "UpgradeVino_6";
			AddMoneyToCharacter(pchar, -50000);
		break;
		
		case "UpgradeVino_6":
			DialogExit();
			
			NextDiag.CurrentNode = "Kristian_41";
			pchar.questTemp.TPZ_UpgradeVino = true;
			pchar.questTemp.TPZ_KritstianVinoBlock = true;
			DeleteAttribute(pchar, "questTemp.TPZ_KritstianVinoPotom");
			AddQuestRecordInfo("Useful_Acquaintances", "4_1");
		break;
		
		
	}
}
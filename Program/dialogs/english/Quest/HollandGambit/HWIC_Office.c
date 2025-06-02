// НПС офиса ГВИК
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Want something?";
			link.l1 = "No.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// офицер
		case "HWIC_officer":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "Alarm! The enemy is here! To arms!";
				link.l1 = "Damn!";
				link.l1.go = "fight";
				break;
			}
			if (ChangeCharacterHunterScore(Pchar, "holhunter", 0) > 12)
			{
				dialog.text = "You there, halt! Your face is familiar...of course! You are wanted for your crimes! Lads, seize him!";
				link.l1 = "Damn!";
				link.l1.go = "fight";
				break;
			}
			chrDisableReloadToLocation = true;
			if (CheckAttribute(pchar, "questTemp.HWIC.CanTake") && !CheckAttribute(pchar, "questTemp.HWIC.CanTake.Holl") && !CheckAttribute(pchar, "questTemp.HWIC.Eng") && !CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				dialog.text = "Welcome to the Dutch West India Company. Speak quickly, time is money.";
				link.l1 = "I am here for trading matters. Licenses, navigation instruments and so on...";
				link.l1.go = "HWIC_officer_3";
				link.l2 = "I want to offer my services to the Company. In exchange for gold of course. Are you hiring?";
				link.l2.go = "HWIC_officer_1";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
			{
				dialog.text = "Welcome to the Dutch West India Company. Speak quickly, time is money.";
				link.l1 = "I am sorry, it seems, that I was mistaken. I am leaving.";
				link.l1.go = "HWIC_officer_exit";
				link.l2 = "I am here for trading matters. Licenses, navigation instruments and so on...";
				link.l2.go = "HWIC_officer_3";
				break;
			}
			dialog.text = "Speak quickly, time is money.";
			link.l1 = "I am here for trading matters. Licenses, navigation instruments and so on...";
			link.l1.go = "HWIC_officer_3";
			link.l2 = "I want to offer my services to the Company. In exchange for gold of course. Are you hiring?";
			link.l2.go = "HWIC_officer_2";
		break;
		
		case "HWIC_officer_1":
			dialog.text = "Then go upstairs to Mynheer Rodenburg's office.";
			link.l1 = "Thanks, I am on my way.";
			link.l1.go = "HWIC_officer_exit";
			// belamour legendary edition переехали по другому адресу
			LocatorReloadEnterDisable("GVIK", "reload2", false);//кабинет откроем
		break;
		
		case "HWIC_officer_2":
			dialog.text = "The Company is not hiring at the moment.";
			link.l1 = "That's too bad. Sorry for bothering you.";
			link.l1.go = "HWIC_officer_exit";
		break;
		
		case "HWIC_officer_3":
			dialog.text = "Talk to Mynheer Gerritz. His table is on your left as you come in. He does business with contracted captains.";
			link.l1 = "Thank you, officer...";
			link.l1.go = "HWIC_officer_exit";
		break;
		
		case "HWIC_officer_exit":
			DialogExit();
			// belamour legendary edition переехали
			LAi_ActorGoToLocation(npchar, "soldiers", "soldier3", "GVIK", "soldiers", "soldier3", "", 5);
			DoQuestCheckDelay("ReturnTalkerToOfficer", 5.0); // 140313
			NextDiag.TempNode = "HWIC_officer";
		break;
		
		// солдаты
		case "HWIC_soldier":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "Alarm! The enemy is here! To arms!";
				link.l1 = "Damn!";
				link.l1.go = "fight";
				break;
			}
			if (ChangeCharacterHunterScore(Pchar, "holhunter", 0) > 12)
			{
				dialog.text = "Aha! I think I know who you are... But of course! You are wanted for your crimes! Lads, take him!";
				link.l1 = "Damn!";
				link.l1.go = "fight";
				break;
			}
			dialog.text = "Speak with our officers or with Mynheer Gerritz. I have nothing to say to you. I am on duty.";
			link.l1 = "Your discipline is admirable.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "HWIC_soldier";
		break;
		
		// клерки
		case "HWIC_clerk":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "Alarm! The enemy is here! Soldiers!";
				link.l1 = "Damn!";
				link.l1.go = "fight";
				break;
			}
			dialog.text = "Talk with Mynheer Gerritz.";
			link.l1 = "Fine, I got it.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "HWIC_clerk";
		break;
		
		// главный клерк - минхер Герритц
		case "HWIC_headclerk":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "Alarm! Enemy is here! Soldiers, take him!";
				link.l1 = "Damn!";
				link.l1.go = "fight";
				break;
			}
			if (ChangeCharacterHunterScore(Pchar, "holhunter", 0) > 12)
			{
				dialog.text = "Hm. I think that there is something off about you... But of course! You are wanted for your numerous crimes against Holland! Soldiers, take him!";
				link.l1 = "Damn!";
				link.l1.go = "fight";
				break;
			}
			dialog.text = "Want something, mynheer?";
			if (!CheckCharacterItem(pchar, "HolTradeLicence"))
			{
				link.l1 = "I want to buy a Dutch West India Company trading license.";
				link.l1.go = "licence";	
			}
			if (!CheckAttribute(npchar, "quest.trade"))
			{
				link.l2 = "I heard that it is possible to buy navigation instruments and other useful items here. Is that so?";
				link.l2.go = "trade";	
			}
			else
			{
				link.l2 = "What are you selling today?";
				link.l2.go = "trade_1";	
			}
			if (CheckCharacterItem(pchar, "Cromvel_depeshe"))
			{
				link.l3 = "I have an interesting document for you, mynheer. Take a look at the first few lines. It concerns the survival of the Republic and the profits of the Company. The coordinates of a certain meeting are in there as well. I will sell them to you if you are interested. For a generous price of course.";
				link.l3.go = "depeshe";	
			}
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche.Garpiya") && pchar.questTemp.Caleuche.Garpiya == "gwik")
			{
				link.l4 = "A captain by the name of Reginald Jackson must be working for you. He sails on a xebec called 'Harpy'. Could you tell me how can I find him? I have important business with him.";
				link.l4.go = "caleuche";	
			}
			// Sinistra Путеводная звезда
			if (CheckAttribute(pchar, "questTemp.PZ_RazgovorGerrits"))
			{
				link.l4 = "I need to see Mynheer Rodenburg urgently. It's of utmost importance. Where is he?";
				link.l4.go = "PZ_RazgovorGerrits_1";
			}
			link.l9 = "No, it's nothing.";
			link.l9.go = "exit";			
			NextDiag.TempNode = "HWIC_headclerk";
		break;
		
		// торговые лицензии
		case "licence":
			if (!CheckAttribute(npchar, "quest.licence"))
			{
				dialog.text = "Well, you are free to buy it. But I must warn you that the Company values its reputation of strict neutrality, therefore it is forbidden to attack any trade ships of any nation while you are holding this license\nIf we find out that such act was committed - we will annul your license. Additionally, if you come into conflict with Dutch or Company for any reason, your license will be annuled as well. Are we clear?";
				link.l1 = "Clear as crystal. I will remember that.";
				link.l1.go = "licence_0";
				npchar.quest.licence = true;
			}
			else
			{
				dialog.text = "You are welcome to buy a license. So, how many days?";
				link.l1.edit = 6;
				link.l1 = "";	
				link.l1.go = "licence_1";
			}
		break;
		
		case "licence_0":
			dialog.text = "The license grants free passage to any port of any nation, it shows your peaceful intentions and explains your purpose - to trade. But it won't help you if you have any problems with the law. They will simply take it from you in that case. Remember, \nDon't forget to raise a friendly flag before you sail into any port. Patrols and forts' cannoneers prefer to shoot first and ask later\nThe minimum length for the license is twenty days and the maximum length is six months or 180 days\nRight, I almost forgot... According to our esteemed traditions, all deals involving licenses are paid in doubloons.  Now let us discuss terms. How long do you want the license to last?";
			link.l1.edit = 6;
			link.l1 = "";	
			link.l1.go = "licence_1";
			link.l2 = "I am sorry, but I have to think a bit more about it. See you later.";	
			link.l2.go = "exit";
		break;
		
		case "licence_1":
			float fQty = stf(dialogEditStrings[6]);
			npchar.quest.lcc_summ = makeint(sqrt(fQty)*10)*7;
			if (fQty < 1)
			{
				dialog.text = "Mynheer please, speak up clearly. I didn't hear you properly. So for how long?";
				link.l1 = "Let me think...";
				link.l1.go = "licence_r";
				break;
			}
			if (fQty > 0 && fQty < 20)
			{
				dialog.text = "The minimum term for the license is twenty days. So? Twenty days or longer?";
				link.l1 = "Let me think...";
				link.l1.go = "licence_r";
				break;
			}
			if (fQty > 180)
			{
				dialog.text = "The maximum term for the license is half a year. One hundred and eighty days or less?";
				link.l1 = "Let me think...";
				link.l1.go = "licence_r";
				break;
			}
			dialog.text = "For "+FindRussianDaysString(sti(fQty))+"? Very good. It will cost you "+FindRussianDublonString(sti(npchar.quest.lcc_summ))+". Are those terms acceptable?";
			if (PCharDublonsTotal() >= sti(npchar.quest.lcc_summ))
			{
				link.l1 = "Aye, I am.";
				link.l1.go = "licence_2";
			}
			link.l2 = "Unfortunately, I don't have that much money with me now. I will be back for the license later.";
			link.l2.go = "exit";
		break;
		
		case "licence_r":
			dialog.text = "";
			link.l1.edit = 6;
			link.l1 = "";	
			link.l1.go = "licence_1";
			link.l2 = "I am sorry, but I still need to think about it. I will see you later.";	
			link.l2.go = "exit";
		break;
		
		case "licence_2":
			int iQty = sti(dialogEditStrings[6]);
			RemoveDublonsFromPCharTotal(sti(npchar.quest.lcc_summ));
			GiveNationLicence(HOLLAND, iQty);
			// belamour legendary edition на пару с Акулой
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet") && pchar.questTemp.SharkGoldFleet == "start")
			{
				if(iQty < 180) 
				{
					Log_info("Quest: 'Together with the Shark' - your license is less than 180 days");
				}
				else 
				{
					pchar.questTemp.SharkGoldFleet.LicenceOk = true;
					AddQuestRecord("SharkGoldFleet", "2");
				}
				pchar.questTemp.SharkGoldFleet = "afterGvik";
			}
			dialog.text = "Wait a minute... Let me put a sign and a stamp here...sealed and done. Take your document.";
			link.l1 = "Thanks! Goodbye, mynheer.";
			link.l1.go = "exit";
		break;
		
		case "trade":
			dialog.text = "Indeed we do. You can buy navigation tools here such as compasses, astrolabes, chronometers, and sand glasses. But we don't always have a full stock ready to buy except sand glasses, perhaps. Our contractors and captains buy out the other tools really quickly. So if you failed to find what you need - see us again in a week when we restock\nWe also sell maps and spyglasses. Want to see what we have?";
			link.l1 = "Yes, please.";
			link.l1.go = "trade_1";
			npchar.quest.trade = "true";
		break;
		
		case "trade_1":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 7)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;
		
		// депеша Кромвеля
		case "depeshe":
			dialog.text = "Hm, show me...(reading) Well, well... Cromwell's appetite is growing. Kanker! Did those Puritan dogs not shed enough blood on their own island without bringing their filth here!? Where did you get this dispatch?";
			link.l1 = "I took it from an English courier. So would you like to buy it?";
			link.l1.go = "depeshe_1";
		break;
		
		case "depeshe_1":
			dialog.text = "Yes. Peter Stuyvesant will be really glad to read it, I am sure. And he will take effective measures to stop it... I can pay with gold doubloons or I can make you out a license for a half a year term. Which do you prefer?";
			link.l1 = "I choose gold.";
			link.l1.go = "depeshe_dublon";
			link.l2 = "I want the license.";
			link.l2.go = "depeshe_licence";
		break;
		
		case "depeshe_dublon":
			TakeNItems(pchar, "gold_dublon", 700);
			Log_Info("You have received 700 doubloons");
			dialog.text = "Very good. Here are your seven hundred doubloons. A handsome reward for a service will rendered.";
			link.l1 = "Here is your dispatch.";
			link.l1.go = "depeshe_exit";
		break;
		
		case "depeshe_licence":
			if (CheckCharacterItem(pchar, "HolTradeLicence")) TakeNationLicence(HOLLAND);
			GiveNationLicence(HOLLAND, 180);
			dialog.text = "Good. Here is your license for a half a year term.";
			link.l1 = "Thanks! And here is your dispatch.";
			link.l1.go = "depeshe_exit";
		break;
		
		case "depeshe_exit":
			RemoveItems(pchar, "Cromvel_depeshe", 1);
			pchar.quest.Terrapin_CromvelScuadron.over = "yes"; //снять прерывание
			ChangeCharacterNationReputation(pchar, HOLLAND, 15);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			dialog.text = "Bedankt. It is good that you have shown your consciousness and loyalty to the Republic. I will tell Matthias Beck and Peter Stuyvesant about your good deed.";
			link.l1 = "Good to know. Goodbye!";
			link.l1.go = "exit";
		break;
		
		// Sinistra Путеводная звезда
		case "PZ_RazgovorGerrits_1":
			dialog.text = "I'm afraid he's already left for the Old World with the Schneur family. I believe he mentioned it to you.";
			link.l1 = "That's right, he did. But I hoped he might have been delayed by some recent business on the Archipelago. Tell me, Gerritz, does anyone in the Company keep in touch with Mynheer Rodenburg? Perhaps via courier ships?";
			link.l1.go = "PZ_RazgovorGerrits_2";
		break;
		
		case "PZ_RazgovorGerrits_2":
			dialog.text = "Not at all - before he left, he asked us never to bother him - said he was starting a new better life.";
			link.l1 = "Let's hope our lives will be better too. Goodbye.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.PZ_RazgovorGerrits");
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "Let me check the manifest logs....Ikema, Immerzeel, Jacobs...Jackson, found him. Hmm, Kapitein Reginald Jackson is currently running regular shipping operations between Port Royal and Philipsburg. Look for him on that route. Now kapitein, I must warn you in advance - if you're plotting some mischief, you'd better not, because that Kapitein Jackson is under our protection. Do we understand each other, mynheer?";
			link.l1 = "I just have business with him. A common trade. I don't mean to hurt him in any way.";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "Excellent. Kapitein Jackson usually doesn't stay for long in Port Royal, or in Philipsburg. Time is money after all. After his ship is unloaded and loaded again, he usually sets sail at once. You'll have better luck meeting him along the sea lanes.";
			link.l1 = "Thank you!";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			DialogExit();
			pchar.questTemp.Caleuche.Garpiya = "capitan";
			pchar.questTemp.Garpiya = "to_portroyal";
			AddQuestRecord("Caleuche", "19");
			DoQuestFunctionDelay("Caleuche_CreateGarpiyaInWorld", 1.0);
		break;
		
		// новый босс ГВИК
		case "HWIC_Boss":
			if(CheckAttribute(pchar,"questTemp.HWIC.Detector") && (pchar.questTemp.HWIC.Detector == "holl_win"))
			{
				if (!CheckAttribute(npchar, "quest.silk_info"))
				{
					if (sti(pchar.reputation.nobility) > 60)
					{
						dialog.text = "Aha, Kapitein " + GetFullName(pchar) + "! It is good that you came here. I have a business proposal for you.";
						link.l1 = "Interesting! I am listening to you, mynheer.";
						link.l1.go = "silk_info";
						break;
					}
					else notification("Reputation Too Low! ("+XI_ConvertString(GetReputationName(61))+")", "None");
				}
			}
			dialog.text = "Good day, Kapitein " + GetFullName(pchar) + "! How can I be of service?";
			if(CheckAttribute(pchar,"questTemp.HWIC.Detector") && (pchar.questTemp.HWIC.Detector == "holl_win"))
			{
				if(CheckAttribute(npchar, "quest.silk")) // торговля шелком
				{
					if (GetDataDay() == 1 || GetDataDay() == 15)
					{
						link.l1 = "About that ship silk...";
						link.l1.go = "trade_silk";
					}
				}
			}
			link.l2 = "Good day. No, I don't need anything, just wanted to say hello.";
			link.l2.go = "exit";			
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "silk_info":
			dialog.text = "I have recently established trading connections with a merchant from Lyons about supplying the Caribbean with ship silk. Do you know about it? The very best sails in the world are made from this silk, so you must be interested.";
			link.l1 = "Strike me dead, aye that is music to my ears. What are your terms?";
			link.l1.go = "silk_info_1";
		break;
		
		case "silk_info_1":
			dialog.text = "Small but regular shipments. I can save thirty rolls for you every two weeks. The cost of one roll is twenty doubloons. Let's make it this way: I will save thirty rolls for you every first and fifteenth day of month. If you don't come for them then, I sell the rolls to another customer.";
			link.l1 = "No obligations then?";
			link.l1.go = "silk_info_2";
		break;
		
		case "silk_info_2":
			dialog.text = "Precisely, kapitein. Buy the silk if you want. You pay for the whole batch - six hundred doubloons. I hope that you will be a regular customer.";
			link.l1 = "Thanks for your proposal, mynheer. Deal.";
			link.l1.go = "exit";
			NextDiag.TempNode = "HWIC_Boss";
			npchar.quest.silk_info = "true";
			npchar.quest.silk = "true";
			AddQuestRecordInfo("Unique_Goods", "3");
		break;
		
		// торговля шелком
		case "trade_silk":
			if (CheckAttribute(pchar, "questTemp.UpgradeSilk"))
			{
				dialog.text = "Sure, kapitein. Your silk is waiting for you. Are you ready to pay for it?";
				if (PCharDublonsTotal() >= 2550)
				{
					link.l1 = "Sure! Here, take 2550 doubloons.";
					link.l1.go = "trade_silk_1";
				}
				else
				{
					link.l1 = "Damn me, I have forgotten the money on my ship. I will bring it in a second!";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Sure, kapitein. Your silk is waiting for you. Are you ready to pay for it?";
				if (PCharDublonsTotal() >= 600)
				{
					link.l1 = "Sure! Here, take six hundred doubloons.";
					link.l1.go = "trade_silk_1";
				}
				else
				{
					link.l1 = "Damn me, I have forgotten the money on my ship. I will bring it in a second!";
					link.l1.go = "exit";
				}
			}
			if(sti(pchar.questTemp.GVIKSilk) >= 1 && !CheckAttribute(pchar, "questTemp.GVIKSilkBlock")) // увеличить объём поставок шёлка
			{
				link.l4 = "Mijnheer "+npchar.name+", I would like to discuss the possibility of increasing silk supplies.";
				link.l4.go = "UpgradeSilk";
			}
			if(sti(pchar.questTemp.GVIKSilk) >= 1 && CheckAttribute(pchar, "questTemp.GVIKSilkPotom") && PCharDublonsTotal() >= 3000) // увеличить объём поставок шёлка, если в первый раз не принесли
			{
				link.l4 = "I've brought your doubloons, Mijnheer "+npchar.name+". Please accept them.";
				link.l4.go = "UpgradeSilk_Agreed";
			}
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "trade_silk_1":
			RemoveDublonsFromPCharTotal(600);
			Log_Info("You have given 600 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Pleasure doing business with you, kapitein. Your silk will be delivered to your ship via longboat.";
			link.l1 = "Thanks!";
			link.l1.go = "trade_silk_2";
		break;
		
		case "trade_silk_2":
			dialog.text = "I hope to see you soon. Come back again.";
			link.l1 = "Sure. See you!";
			link.l1.go = "exit";
			AddCharacterGoods(pchar, GOOD_SHIPSILK, 30);
			DeleteAttribute(npchar, "quest.silk");
			SetFunctionTimerCondition("Silk_TraderAttrReturn", 0, 0, 1, false); // таймер
			AddCharacterExpToSkill(pchar, "Commerce", 150);
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "UpgradeSilk": //
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 80)
			{
				dialog.text = "I appreciate your business approach and am willing to consider your request. Perhaps we could increase the volume, say, five times. However, organizing such supplies will require significant resources. We will need to expand storage space, strengthen security, and ensure reliable delivery routes. Since this benefits you as well, I suggest we share these expenses between us.";
				link.l1 = "All this sounds reasonable. What amount do you consider necessary to cover these expenses?";
				link.l1.go = "UpgradeSilk_1";
				notification("Skill Check Passed", SKILL_COMMERCE);
			}
			else
			{
				dialog.text = "I understand your interest in increasing supplies, however at this stage it is difficult for me to agree to such changes. I do not doubt your aspiration for development, but this kind of transaction requires much more experience in trade affairs and confidence in your own actions. I suggest you increase your knowledge in the art of negotiation, and then return to me with a more specific proposal. When you are ready, I will be happy to strengthen our cooperation.";
				link.l1 = "Hmm... Alright. I'll return to this conversation later.";
				link.l1.go = "exit";
				notification("Skill Check Failed (80)", SKILL_COMMERCE);
			}
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "UpgradeSilk_1":
			dialog.text = "Considering all the nuances, your share of expenses will be three thousand gold doubloons. These funds will allow us to organize the necessary measures without delay.";
			link.l1 = "Mijnheer "+npchar.name+", three thousand doubloons? Is this a joke? I came to you with an honest proposal, and you want me to pay such an exorbitant amount for organizing supplies?";
			link.l1.go = "UpgradeSilk_2";
		break;
		
		case "UpgradeSilk_2":
			dialog.text = "I ask you to understand me correctly. I am not trying to deceive you. This money is the amount that will allow us to ensure proper order in the organization of supplies. It's not just about expanding warehouses and security, but also about guaranteeing the delivery of goods without delays and losses, despite all the unpredictability of this business. These are standard expenses for such volumes. In the end, your investments will justify themselves, and you will receive the goods in proper condition and on time.";
			link.l1 = "Your explanations are somewhat reassuring, mijnheer. But still, this amount remains too high. I am ready to agree to your terms if you lower the price to at least two and a half thousand doubloons. I am confident that this will be sufficient for organizing supplies and observing all security measures.";
			link.l1.go = "UpgradeSilk_3";
		break;
		
		case "UpgradeSilk_3":
			dialog.text = "I understand, the amount is large, but as I already said, it is necessary for the proper execution of the work. I cannot reduce it, as this would jeopardize all our efforts. However, so that you don't feel deceived, I am ready to offer you a fifteen percent discount on all future supplies. This, I hope, will allow you to compensate for the expenses.";
			if (PCharDublonsTotal() >= 3000)
			{
				link.l1 = "Hmm, a fifteen percent discount is, of course, a step forward. Alright. I am ready to accept your offer, even though the price seems extremely high to me. I hope our cooperation will meet my expectations. Here is your money.";
				link.l1.go = "UpgradeSilk_Agreed";
			}
			link.l2 = "Mijnheer "+npchar.name+", your offer leaves me no choice. Let it be three thousand doubloons, although it's a considerable sum. However, I cannot pay everything at once now. I'll return as soon as I get the money.";
			link.l2.go = "UpgradeSilk_5";
			link.l3 = "A fifteen percent discount? Mijnheer "+npchar.name+", this is not what I expected. This amount is not just expenses, it's outright and blatant robbery! But I do not intend to break off business relations with you. We will return to the previous terms - 30 rolls of silk at 20 doubloons each.";
			link.l3.go = "UpgradeSilk_4";
		break;
		
		case "UpgradeSilk_Agreed":
			dialog.text = "I'm glad you agreed, "+pchar.name+". Now regarding the details: 150 rolls of silk at 17 doubloons each. Total - 2550 doubloons for the entire batch. You can pick up the goods as usual - on the 1st and 15th of each month. I think this deal will bring good profit for both sides.";
			link.l1 = "Отлично! Вот это - уже неплохой размах. Всего доброго, минхер. Скоро увидимся.";
			link.l1.go = "exit";
			NextDiag.TempNode = "HWIC_Boss";
			RemoveDublonsFromPCharTotal(3000);
			AddQuestRecordInfo("Unique_Goods", "3_1");
			pchar.questTemp.UpgradeSilk = true;
			pchar.questTemp.GVIKSilkBlock = true;
			DeleteAttribute(pchar, "questTemp.GVIKSilkPotom");
		break;
		
		case "UpgradeSilk_4":
			dialog.text = "This is just a business approach, not robbery, as it might have seemed to you. But, as you wish. Come as usual, on the 1st and 15th, for a batch of silk, I will be glad to make a new deal.";
			link.l1 = "Certainly, mijnheer. Farewell.";
			link.l1.go = "exit";
			pchar.questTemp.GVIKSilkBlock = true;
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "UpgradeSilk_5":
			dialog.text = "I'm glad you made the right decision. As soon as you bring the money, we will discuss all the details of the deal and proceed to its implementation.";
			link.l1 = "Goodbye, Mijnheer "+npchar.name+". See you as soon as I gather the required amount.";
			link.l1.go = "exit";
			pchar.questTemp.GVIKSilkBlock = true;
			pchar.questTemp.GVIKSilkPotom = true;
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "fight":
			DialogExit();
			sld = characterFromId("HWIC_officer");
			LAi_SetGuardianTypeNoGroup(sld);
			LAi_group_Attack(sld, Pchar);
			for (i=1; i<=6; i++)
			{	
				sld = characterFromId("HWIC_sold_"+i);
				LAi_group_Attack(sld, Pchar);
			}
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

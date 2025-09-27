// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Speak, I am listening.";
			link.l1 = "I was mistaken. Farewell.";
			link.l1.go = "Exit";
			// --> Тичингиту
			if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "true")
            {
                link.l1 = "There is an Indian under arrest. He was captured by Fadey the Muscovite. May I speak with him?";
                link.l1.go = "Tichingitu";
            }
			if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "commandante")
            {
                link.l1 = "Tell me, are you really going to hang this Indian? Isn't that too harsh a punishment for such a small crime?";
                link.l1.go = "Tichingitu_3";
            }
			if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "pay")
            {
                link.l1 = "It is me again, commandant. Fadey the Muscovite has written this petition to release the Indian. Here it is.";
                link.l1.go = "Tichingitu_6";
            }
			// <-- Тичингиту
			//Jason --> Бесчестный конкурент
			if (CheckAttribute(pchar, "questTemp.Shadowtrader.Fort") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_prison")
			{
				link.l1 = "I have come to you at the request of the local store owner, his name is "+pchar.questTemp.Shadowtrader.Tradername+". He asked me to give you this letter.";
				link.l1.go = "Shadowtrader_prison";
			}
			
			if (CheckAttribute(pchar, "questTemp.Shadowtrader.SeekTrader") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_prison")
			{
				link.l1 = "That's me again. I have substantial evidence that "+pchar.questTemp.Shadowtrader.Tradername+" is right.";
				link.l1.go = "Shadowtrader_prison2";
			}
			//Jason <-- Бесчестный конкурент
			//Sinistra --> Путеводная звезда
			if (CheckAttribute(pchar, "questTemp.PZ_BasTerTurma"))
            {
                link.l1 = "I'm looking for a man named Longway. I hear you're searching for him too, Monsieur Officer. Have you had any luck finding him, or perhaps any leads?";
                link.l1.go = "PZ_IshemLongway_1";
            }
			//Sinistra <-- Путеводная звезда
		break;
		
		// --> Тичингиту
		case "Tichingitu":
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("BasTer_town", "reload", "reload_jail");
			dialog.text = "A-ah, Fadey has told you his story? I have no reason to forbid you from taking a look at him, monsieur. You are not the first to come to see that redskin. Well, in ten days every citizen will be able to take a look at him when we hang him out to dry in the sun...";
			link.l1 = "So, can I enter the prison?";
			link.l1.go = "Tichingitu_1";
		break;
		
		case "Tichingitu_1":
			dialog.text = "As I've already told you, 'I have no reason to forbid you that.' Move along.";
			link.l1 = "Thanks!";
			link.l1.go = "Tichingitu_2";
		break;
		
		case "Tichingitu_2":
			DialogExit();
			pchar.questTemp.Sharlie.Tichingitu = "wait";
			pchar.questTemp.jailCanMove = true;
		break;
		
		case "Tichingitu_3":
			DelLandQuestMark(npchar);
			dialog.text = "You are new here, aren't you, monsieur? Fresh from Europe? You don't understand the situation in the colonies. This execution will serve as a lesson to those redskin bastards who dare to encroach on the property of French colonists. Besides, Fadey himself insists on it, and he is a very respected man here, as well as a close friend of our governor.";
			link.l1 = "Is there any way to lessen the punishment? I still think that it is too harsh...";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_4":
			dialog.text = "Oh, spare me the philosophy! Go to Fadey and ask about this Indian if you truly care about his fate. If Fadey writes a petition for his release, we will grant it.";
			link.l1 = "Understood, officer. I'll go to Fadey.";
			link.l1.go = "Tichingitu_5";
		break;
		
		case "Tichingitu_5":
			DialogExit();
			pchar.questTemp.Sharlie.Tichingitu = "fadey";
			AddLandQuestMark(characterFromId("fadey"), "questmarkmain");
			QuestPointerToLoc("BasTer_town", "reload", "houseSp1");
		break;
		
		case "Tichingitu_6":
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("BasTer_town", "reload", "reload_jail");
			RemoveItems(pchar, "letter_1", 1);
			dialog.text = "(reading) Hm... This Fadey is strange... He demanded a public execution, and now he's asking to release this Indian... Whatever, I suppose all the governor's friends are like him. Fine, you can go and take this redskin.";
			link.l1 = "My thanks, officer!";
			link.l1.go = "Tichingitu_7";
		break;
		
		case "Tichingitu_7":
			DialogExit();
			AddQuestRecord("Tichingitu", "3");
			pchar.questTemp.Sharlie.Tichingitu = "wait";
			pchar.questTemp.jailCanMove = true;
			sld = characterFromId("Tichingitu");
			sld.dialog.currentnode = "Tichingitu_6";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		// <-- Тичингиту
		
		//Jason --> мини-квест Бесчестный конкурент
		case "Shadowtrader_prison":
			dialog.text = "Again that "+pchar.questTemp.Shadowtrader.Tradername+" with his complaints! Alright, let's see what it is this time... (reads through)";
			link.l1 = "...";
			link.l1.go = "Shadowtrader_prison_1";
			RemoveItems(PChar, "letter_1", 1);
			DeleteAttribute(pchar, "questTemp.Shadowtrader.Fort");
			DelLandQuestMark(npchar);
		break;
		
		case "Shadowtrader_prison_1":
			dialog.text = "Once again, absurd guesswork and not a single piece of strong evidence! Alright. Tell him that this is simply not enough for me to alert the guards and order them to scour the town.";
			link.l1 = "You want me to tell him that?";
			link.l1.go = "Shadowtrader_prison_2";
		break;
		
		case "Shadowtrader_prison_2":
			dialog.text = "Exactly – and, preferably, word-for-word. He will understand what I mean. I will not waste paper to write a reply to this annoying one.";
			link.l1 = "I see. Farewell, then.";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader.Trouble = "true";
			NextDiag.TempNode = "First_officer";
			AddLandQuestMark(characterFromId("BasTer_trader"), "questmarkmain");
		break;
		
		case "Shadowtrader_prison2":
			dialog.text = "And what is this 'substantial' evidence that you claim to have gathered?";
			link.l1 = "I struck a deal with the smugglers regarding the purchase of goods through their unofficial store. Their agent will come tonight to the port authority office to take me to their so-called 'store'.";
			link.l1.go = "Shadowtrader_prison2_1";
			DeleteAttribute(pchar, "questTemp.Shadowtrader.SeekTrader");
			pchar.quest.ShadowtraderTimeSmugglers_Over.over = "yes";
			pchar.quest.Shadowtrader_SMG.over = "yes";//снять оба прерывания
			sld = characterFromID("ShadowAgent_1");
			sld.lifeday = 0;
			DelLandQuestMark(npchar);
		break;
		
		case "Shadowtrader_prison2_1":
			dialog.text = "Hmm... Well, excellent work, captain! Now we proceed further. We'll send our man to their meeting, locate their hideout, and arrest all of them. Thank you for your initiative!";
			link.l1 = "Always glad to help. I'm sure your operation will be successful.";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader.End.Fort = "true";
			AddQuestRecord("Shadowtrader", "7");
			AddQuestUserData("Shadowtrader", "sSex", GetSexPhrase("","а"));
			SetTimerFunction("ShadowTrader_questmark", 0, 0, 1);
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			NextDiag.TempNode = "First_officer";
		break;
		// <-- мини-квест Бесчестный конкурент
		
		// Sinistra - Квест "Путеводная звезда" ==>
		case "PZ_IshemLongway_1":
			DelLandQuestMark(npchar);
			dialog.text = "Who? Long... Way? I don't recall any Englishmen in our town recently.";
			link.l1 = "No, Longway is... Chinese.";
			link.l1.go = "PZ_IshemLongway_2";
			DeleteAttribute(pchar, "questTemp.PZ_BasTerTurma");
			DeleteQuestCondition("PZ_BasTerPeshera");
		break;
		
		case "PZ_IshemLongway_2":
			dialog.text = "Well, well. And why are you looking for this Longway of yours, monsieur?";
			link.l1 = "He's a friend of mine. I've already heard about what happened - it's a sad misunderstanding, I assure you.";
			link.l1.go = "PZ_IshemLongway_Zashita_1";
			if (pchar.location.from_sea != "BasTer_Town")
			{
				link.l2 = "I'm looking for him because he's a known criminal in the Archipelago.";
				link.l2.go = "PZ_IshemLongway_OhotnikOtryad_1";
			}
		break;
		
		case "PZ_IshemLongway_Zashita_1":
			dialog.text = "Ah, a misunderstanding. We weren't trying to straighten him out on the spot, if anything. We just wanted to talk to him... for starters. However, this aggressive yellow man of yours not only cut down several city guards but also slaughtered the units sent to chase him in the jungle.";
			link.l1 = "Do you plan to send another unit? I could go with your men, talk to him, calm him down, and prevent another disaster. Would it suffice if the killings stopped and Longway left the city for good?";
			link.l1.go = "PZ_IshemLongway_Zashita_2";
		break;
		
		case "PZ_IshemLongway_Zashita_2":
			dialog.text = "Under normal circumstances, I might agree with you. But you see, one of those killed was an officer - a promising young lieutenant, His Grace's favourite. The town is in mourning. There's no turning a blind eye or making up for it. You understand?";
			link.l1 = "I understand perfectly. I apologise for my friend's actions. I'll trouble you no further.";
			link.l1.go = "PZ_IshemLongway_Uiti_1";
			link.l2 = "You know, God only knows what's going on in the jungle. Anyone could have killed those men.";
			link.l2.go = "PZ_IshemLongway_Blef_1";
		break;
		
		case "PZ_IshemLongway_Blef_1":
			dialog.text = "And who do you think could have taken down an entire squad of patrolmen led by an officer?";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				notification("Trustworthy", "Trustworthy");
				link.l1 = "(Trustworthy) Bandits, who else? I'm ashamed to admit it, but I barely escaped from a huge gang recently.";
				link.l1.go = "PZ_IshemLongway_Blef_2";
			}
			else
			{
				notification("Perk check failed", "Trustworthy");
				link.l1 = "But how would I know? It could have been anyone—brigands, pirates, spies...";
				link.l1.go = "PZ_IshemLongway_Blef_netVD_1";
			}
		break;
		
		case "PZ_IshemLongway_Blef_2":
			dialog.text = "Heh, it's not surprising – considering your size, Captain. Yes, we've got such scoundrels on the island these days...";
			link.l1 = "Exactly! So, they could have massacred the patrol and the poor junior lieutenant.";
			link.l1.go = "PZ_IshemLongway_Blef_3";
		break;
		
		case "PZ_IshemLongway_Blef_3":
			dialog.text = "Unfortunately, that's entirely possible.";
			link.l1 = "Precisely. So once again, I ask you to let me join the next search party – Longway will listen to me, and that way we can avoid more deaths.";
			link.l1.go = "PZ_IshemLongway_Blef_4";
		break;
		
		case "PZ_IshemLongway_Blef_4":
			dialog.text = "All right. But there's still one 'but', sir.";
			link.l1 = "And what's that?";
			link.l1.go = "PZ_IshemLongway_Blef_5";
		break;
		
		case "PZ_IshemLongway_Blef_5":
			dialog.text = "Unlike what happened in the jungle, your friend's guilt in the city is clear and fully proven. It won't go unpunished. So, these deaths must be compensated for if you want him to leave the city alive.";
			link.l1 = "Fair enough. How much will it cost, Monsieur Officer?";
			link.l1.go = "PZ_IshemLongway_Blef_6";
		break;
		
		case "PZ_IshemLongway_Blef_6":
			dialog.text = "Three hundred doubloons. That money will go to the city, not to the market square wranglers.";
			if (PCharDublonsTotal() >= 300)
			{
				link.l1 = "Of course. Three hundred doubloons - here you go.";
				link.l1.go = "PZ_IshemLongway_Blef_7";
			}
			link.l2 = "I didn't bring my doubloons into town this time. But if you'll let me retrieve them...";
			link.l2.go = "PZ_IshemLongway_NetDublonov_1";
		break;
		
		case "PZ_IshemLongway_Blef_7":
			dialog.text = "Excellent. You've proven your responsibility. We're just finalizing the briefing for the next squad. I authorize you to join it.";
			link.l1 = "Thank you. Goodbye, Monsieur Officer.";
			link.l1.go = "PZ_IshemLongway_BeryomOtryad";
			RemoveDublonsFromPCharTotal(300);
			pchar.questTemp.PZ_DrugOtryad = true;
		break;
		
		case "PZ_IshemLongway_NetDublonov_1":
			dialog.text = "I wasn't born yesterday. I know you intend to run away - not for doubloons, but for your dear Chinaman.";
			link.l1 = "I give you my word I won't leave town with Longway.";
			link.l1.go = "PZ_IshemLongway_NetDublonov_2";
		break;
		
		case "PZ_IshemLongway_NetDublonov_2":
			dialog.text = "Words, words... I'm tired of your chatter, Captain. You're not going anywhere until we catch this damn yellow-skinned man ourselves.";
			link.l1 = "I will obey your order if you promise not to kill Longway on the spot, Mr. Officer.";
			link.l1.go = "PZ_IshemLongway_Arest_1";
			link.l2 = "But did I personally break the laws of the city today?";
			link.l2.go = "PZ_IshemLongway_Pobeg_1";
		break;
		
		case "PZ_IshemLongway_Blef_netVD_1":
			dialog.text = "Then you don't know. I'll stick to my current hunch – the Chinaman must be caught, regardless.";
			link.l1 = "Your current hunch? But you have no proof that Longway killed everyone in the jungle.";
			link.l1.go = "PZ_IshemLongway_Blef_netVD_2";
		break;
		
		case "PZ_IshemLongway_Blef_netVD_2":
			dialog.text = "And do you have proof of his innocence? No? Then stop making a saint out of your yellow-skinned man. Do you understand me?";
			link.l1 = "I understand perfectly. I apologise for my friend's actions. I'll trouble you no further.";
			link.l1.go = "PZ_IshemLongway_Uiti_1";
		break;
		
		case "PZ_IshemLongway_Uiti_1":
			dialog.text = "I'm afraid I can't let you leave just yet, Captain.";
			link.l1 = "What do you mean?";
			link.l1.go = "PZ_IshemLongway_Uiti_2";
		break;
		
		case "PZ_IshemLongway_Uiti_2":
			dialog.text = "What I mean is that since this Longway is your friend, there's no guarantee you won't run after him and try to escape with him. So, I'll have to hold you until we catch this yellow-skinned butcher ourselves.";
			link.l1 = "I will obey your order if you promise not to kill Longway on the spot, Mr. Officer.";
			link.l1.go = "PZ_IshemLongway_Arest_1";
			link.l2 = "But did I personally break the laws of the city today?";
			link.l2.go = "PZ_IshemLongway_Pobeg_1";
		break;
		
		case "PZ_IshemLongway_Arest_1":
			dialog.text = "I can't promise anything. Who knows what your friend has in mind, or whether he'll start another massacre when he sees us. In the meantime, please enjoy your luxurious accommodations, Captain.";
			link.l1 = "Hilarious...";
			link.l1.go = "PZ_IshemLongway_Arest_2";
		break;
		
		case "PZ_IshemLongway_Arest_2":
			DialogExit();
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(PChar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(PChar, MUSKET_ITEM_TYPE);
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			bDisableCharacterMenu = true;
			InterfaceStates.Buttons.Save.enable = false;
			bDisableFastReload = true;
			chrDisableReloadToLocation = true;
			DoQuestReloadToLocation("BasTer_prison", "goto", "goto9", "PZ_SharliePlennik_BadFinal");
		break;
		
		case "PZ_IshemLongway_Pobeg_1":
			dialog.text = "Understand, I have nothing against you personally. And you're right – you haven't committed any crime. But we need to ensure that your yellow-skinned friend doesn't escape justice.";
			link.l1 = "Then understand that I will not allow myself to be detained in such a sham manner.";
			link.l1.go = "PZ_IshemLongway_Pobeg_2";
		break;
		
		case "PZ_IshemLongway_Pobeg_2":
			if (pchar.location.from_sea == "BasTer_Town")
			{
				dialog.text = "In that case, we'll have to quiet you down, sir.";
			}
			else
			{
				dialog.text = "I've had enough of this! Sergeant, lead the squad to that damned cave and find the Chinese! I'll deal with this one personally...";
			}
			link.l1 = "The hell you will.";
			link.l1.go = "PZ_IshemLongway_Pobeg_3";
		break;
		
		case "PZ_IshemLongway_Pobeg_3":
			DialogExit();
			
			LAi_SetHuberType(NPChar);
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_MoveCharacter(NPChar, "FRANCE_CITIZENS");
			LAi_group_Attack(characterFromId("BasTer_Mayor"), Pchar);
			ChangeCharacterNationReputation(pchar, FRANCE, -50);
			if (pchar.location.from_sea == "BasTer_Town")
			{
				PChar.quest.PZ_KorablPort_BadFinal.win_condition.l1 = "MapEnter";
				PChar.quest.PZ_KorablPort_BadFinal.win_condition = "PZ_KorablPort_BadFinal";
				AddQuestRecord("PZ", "10");
				LocatorReloadEnterDisable("BasTer_town", "gate_back", true);
				Island_SetReloadEnableGlobal("Guadeloupe", false);
			}
			else
			{
				PChar.quest.PZ_KorablBuhta_BadFinal.win_condition.l1 = "EnterToSea";
				PChar.quest.PZ_KorablBuhta_BadFinal.win_condition = "PZ_KorablBuhta_BadFinal";
				AddQuestRecord("PZ", "5");
				
				// Микро-диалог с Лонгвэем у пещеры, если мы побежали к пещере ему помочь после ссоры с комендантом
				PChar.quest.PZ_IshemLongway_SorraKomendant.win_condition.l1 = "location";
				PChar.quest.PZ_IshemLongway_SorraKomendant.win_condition.l1.location = "Guadeloupe_CaveEntrance";
				PChar.quest.PZ_IshemLongway_SorraKomendant.win_condition = "PZ_IshemLongway_SorraKomendant";
				
				LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", true);
				LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", true);
				//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", true);
			}
		break;
		
		case "PZ_IshemLongway_OhotnikOtryad_1":
			dialog.text = "A bounty hunter, huh? Normally, I don't like dealing with your kind, but in this case, it's to my advantage that our interests align. Apparently, this yellow-skinned one is an infamous killer. He's murdered many of my men, both in town and in the jungle.";
			link.l1 = "I've been chasing him across the Archipelago for some time now.";
			link.l1.go = "PZ_IshemLongway_OhotnikOtryad_2";
		break;
		
		case "PZ_IshemLongway_OhotnikOtryad_2":
			dialog.text = "Damned rascal! Here's what we'll do: I'll gather another squad, and you'll go with them. This time, he's got nowhere to run, and with your help, we'll have a better chance of success. Don't expect a reward from me, though – you're a bounty hunter, so your payment will come from whoever hired you. You should be grateful I'm letting you cooperate with me at all.";
			link.l1 = "That's true enough. See you later, officer. If any of your men survive another encounter with our Chinese friend, I'll let you know how it went.";
			link.l1.go = "PZ_IshemLongway_BeryomOtryad";
			pchar.questTemp.PZ_OhotnikOtryad = true;
		break;
		
		case "PZ_IshemLongway_BeryomOtryad":
			DialogExit();
			
			LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", true);
			LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", true);
			//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", true);
			DoQuestReloadToLocation("Guadeloupe_jungle_02", "goto", "goto1", "PZ_IshemLongway_Otryad");
		break;
		
		case "PZ_BasTer_ComendantDialog_1":
			dialog.text = "You're right. You two are acquainted, I take it? Who are you to each other?";
			link.l1 = " He's a navigation officer on my ship, and...";
			link.l1.go = "PZ_BasTer_ComendantDialog_2";
			if (pchar.location.from_sea != "BasTer_Town")
			{
				link.l2 = "I'm looking for him because he's a known criminal in the Archipelago.";
				link.l2.go = "PZ_IshemLongway_OhotnikOtryad_1";
			}
		break;
		
		case "PZ_BasTer_ComendantDialog_2":
			dialog.text = "He's better with guns than with maps. Do you have any idea what your pet Chinaman has done?";
			link.l1 = "To be honest, no, because I just docked and started searching. I'm sure it was all a misunderstanding.";
			link.l1.go = "PZ_IshemLongway_Zashita_1";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_1":
			dialog.text = "Exactly. Who are you to him, if you want him so much? It doesn't matter – what's important is the purpose of your visit to the city.";
			link.l1 = "Nothing illegal, sir. But what did you mean by “it doesn't matter anymore”? Did he...";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_2";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_2":
			dialog.text = "Yes. He was buried behind one of the hills, some distance from the cemetery. The holy fathers didn't allow a proper Christian burial for a pagan.";
			link.l1 = "How did it happen, if it's not a secret?";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_3";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_3":
			dialog.text = "Very simply - he arrived in the city, snooping around endlessly. We tried to talk to him, to find out what he was doing here, but he killed some men and fled into the jungle. I sent several search parties after him, one after another, but he wiped them all out! We had to trap him in a cave, and the marksmen did the rest.";
			link.l1 = "And you don't know what he was looking for? You see, he'd never done anything like this before – he used to be a navigator on my ship. But then he stole from me and ran away.";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_4";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_4":
			dialog.text = "It just slipped my mind, aye. So, you suffered from his actions too? That'll teach you a lesson, Captain. You'll know better than to take on someone you can't trust. Never trust a yellow-skinned man - mark my words!";
			link.l1 = "Aye, I'll keep that in mind. Did you find anything about him?";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_5";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_5":
			dialog.text = "Oh, you want to recover the stolen goods? He had some silver in his pockets, so if he stole from you, he's already spent it all. And there were some other papers... from your ship's log? We couldn't make sense of them anyway - some kind of code, perhaps? Everything was covered in blood, so we couldn't make out the undamaged parts.";
			link.l1 = "Er, yes. Thank you. I've always worried about what would happen if my journals and diaries were picked up by someone else...";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_6";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_6":
			dialog.text = "And having to come up with a full-blown complex cipher because of that? Didn't you feel sorry for your time and effort? Here you go. And about the silver - don't be angry, but we returned it to the city. That Chinaman put a lot of my men in the ground that day.";
			link.l1 = "Then I dare not insist. Goodbye.";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_7";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_7":
			DialogExit();
			
			LAi_SetHuberType(npchar);
			AddQuestRecord("PZ", "9");
			CloseQuestHeader("PZ");
			bDisableLandEncounters = false;
		break;
		// <== Квест "Путеводная звезда" - Sinistra
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

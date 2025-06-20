// диалоги НПС по квесту 'В поисках Стража Истины'
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
		case "First time":
			dialog.text = "How can I help you?";
			link.l1 = "Sorry, it's nothing.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// пленный испанец
		case "spa_prisoner":
			PlaySound("Voice\English\Ransack_1.wav");
			dialog.text = "What do you want? Another interrogation? Vete al diablo!";
			link.l1 = "Senor, what's your name?";
			link.l1.go = "spa_prisoner_1";			
		break;
		
		case "spa_prisoner_1":
			dialog.text = "What the hell do you care about the name of the man you're going to hang or shoot? Bastardo! I was incautious enough to fall into your hands after all...";
			link.l1 = "Senor, identify yourself. I cannot talk to a man without knowing what his name is.";
			link.l1.go = "spa_prisoner_2";			
		break;
		
		case "spa_prisoner_2":
			dialog.text = "Don "+GetFullName(npchar)+". There, are you happy? Now who do I have the pleasure of speaking with?";
			link.l1 = "My name is "+GetFullName(pchar)+". Have you ever heard of me before?";
			link.l1.go = "spa_prisoner_3";			
		break;
		
		case "spa_prisoner_3":
			dialog.text = "No, carajo! Do I look like I know every roaming vagabond in the West Indies who...";
			link.l1 = "Enough. Let's do this without insults and behave like gentlemen. Your fate will depend on what you can tell me. If you tell me something interesting, I'll petition for your release into my custody. That will allow you to escape the musket ball or noose awaiting you right now.";
			link.l1.go = "spa_prisoner_4";			
		break;
		
		case "spa_prisoner_4":
			dialog.text = "Dios mio, that is an offer I can't refuse. What would you like to know, senor?";
			link.l1 = "Who organized such a large attack on St. Pierre and why?";
			link.l1.go = "spa_prisoner_5";			
		break;
		
		case "spa_prisoner_5":
			dialog.text = "Baron Ramon de Mendosa y Riba, the garrison commander of Providence Island. He dispatched a squadron to raid and pillage the town, seizing any valuables we might find.";
			link.l1 = "What was your immediate task in the attack? Specifically, what were your orders?";
			link.l1.go = "spa_prisoner_6";			
		break;
		
		case "spa_prisoner_6":
			dialog.text = "I am the commander of the marine battalion. Our orders were to seize the fort and secure its batteries from firing upon our landing boats as they approached the town. After that, my men took part in attacking St. Pierre itself.";
			link.l1 = "Were you informed of the valuables located in the city? Of the amount and quality?";
			link.l1.go = "spa_prisoner_7";			
		break;
		
		case "spa_prisoner_7":
			dialog.text = "We didn't have exact information as to the amount, but Baron de Mendosa y Riba told us that there is silver stored under the fort and the port warehouses have strategic raw materials vital to the war effort: ironwood and ship silk.";
			link.l1 = "Did you find those valuables?";
			link.l1.go = "spa_prisoner_8";			
		break;
		
		case "spa_prisoner_8":
			dialog.text = "No. We didn't find either one. The warehouses were filled with typical colonial merchandise and beneath the fort was gunpowder, weaponry, and lead. But we didn't have enough time to conduct a more thorough search... the French reinforcements came roaring in and we were forced to give battle.";
			link.l1 = "Didn't you find it strange that you didn't find the valuables?";
			link.l1.go = "spa_prisoner_9";			
		break;
		
		case "spa_prisoner_9":
			dialog.text = "Of course I did, but I don't usually question orders.";
			link.l1 = "Listen to what I'm about to tell you. Fort St. Pierre has never contained silver, and those warehouses have never stored ironwood and silk. Think well senor, before answering, because if your answer does not please me, I'll turn around and walk out of here leaving you to your fate... a sorrowful fate.";
			link.l1.go = "spa_prisoner_10";			
		break;
		
		case "spa_prisoner_10":
			dialog.text = "I'm listening.";
			link.l1 = "I don't believe that the only goal of your raid was simple robbery. St.Pierre is an unassuming and relatively poor colony to send a whole squadron here led by a first rate ship of the line. Surely you or your commander or someone else had additional orders or directions. What did they tell you? Think well before answering...";
			link.l1.go = "spa_prisoner_11";			
		break;
		
		case "spa_prisoner_11":
			dialog.text = "";
			link.l1 = "You're going to keep quiet? Alright. Think about it for a moment, I'll wait.";
			link.l1.go = "spa_prisoner_12";			
		break;
		
		case "spa_prisoner_12":
			dialog.text = "Senor, my life is going to depend on my reply?";
			link.l1 = "Correct.";
			link.l1.go = "spa_prisoner_13";			
		break;
		
		case "spa_prisoner_13":
			dialog.text = "I've got something... But you must swear to me that you'll get me out of here and ransom me back to Spain.";
			link.l1 = "If you tell me something worthy of my attention, I swear upon the Holy Cross you will be delivered onboard my vessel for ransom and you will escape execution.";
			link.l1.go = "spa_prisoner_14";			
		break;
		
		case "spa_prisoner_14":
			dialog.text = "Alright. Don Diego de Montoya instructed our battalion of marines that we must under all secrecy and importance find and take captive a man by the name Miguel Dichoso, who is located somewhere in St. Pierre under protection of the authorities.";
			link.l1 = "Keep going. Who is Diego de Montoya?";
			link.l1.go = "spa_prisoner_15";			
		break;
		
		case "spa_prisoner_15":
			dialog.text = "The officer in command of the squadron. He fled soon after your...dramatic arrival.";
			link.l1 = "Who is he, this Don Diego?";
			link.l1.go = "spa_prisoner_16";			
		break;
		
		case "spa_prisoner_16":
			dialog.text = "I only know that he's an authorized representative of Baron de Mendosa y Riba, his right hand man and agent for critical tasks.";
			link.l1 = "Interesting... And who is Miguel Dichoso, the man whom apparently this whole catastrophe was arranged to catch? Must be a bad hombre, eh?";
			link.l1.go = "spa_prisoner_17";			
		break;
		
		case "spa_prisoner_17":
			dialog.text = "Do you remember your oath, senor?";
			link.l1 = "Yes. And I affirm that if you continue telling your story that you'll be delivered as a key witness to my vessel and later...well, I'll find a way to get you to a Spanish settlement. But not before you tell me everything that you know.";
			link.l1.go = "spa_prisoner_18";			
		break;
		
		case "spa_prisoner_18":
			dialog.text = "Miguel Dichoso is the former brother-in-arms of the baron, however some say that Miguel betrayed him. Senor de Mendosa y Riba wants him alive, so we were given an order to not kill Dichoso under any circumstances.";
			link.l1 = "Is Dichoso a Spaniard as well?";
			link.l1.go = "spa_prisoner_19";			
		break;
		
		case "spa_prisoner_19":
			dialog.text = "Si. Don Diego de Montoya gave us an approximate description and ordered that any man looking like Dichoso had to be delivered directly to him. But given the short time that we had before your counterattack, we never had the time to search.";
			link.l1 = "Did you know Dichoso personally?";
			link.l1.go = "spa_prisoner_20";			
		break;
		
		case "spa_prisoner_20":
			dialog.text = "No, only by reputation. I've never seen the man before. There were some of my fellow officers that knew him personally. All of them are dead.";
			link.l1 = "How badly did Dichoso betray your Don Mendosa that he decided to send a whole squadron after him?";
			link.l1.go = "spa_prisoner_21";			
		break;
		
		case "spa_prisoner_21":
			dialog.text = "I will tell you. The baron only recently arrived to the Caribbean from Spain. His orders were to ensure the safety of the Spanish Treasure Fleet convoys but instead he looked inland...searching for Indian gold. His head was turned by rumors of hidden treasure. He decided that an ancient Maya city exists somewhere deep in Yucatan's jungles - Tayasal, the legendary city of gold\nThe baron sent several expeditions to find the city but all of those were vanquished utterly into the wild selva. No doubt that each and every one of them were slaughtered by the martial Itza people who live there\nEventually Inquisitor Vincento had enough of Don Mendosa's fantasies and the pointless death of good soldiers. The inquisitor informed Madrid about the situation. The viceroy forbade Don Mendosa to search for the mythic city and to focus on his duties. That's when Miguel Dichoso showed up\nHe convinced the baron to organize another expedition which surprisingly was a success. They found ruins of an ancient city and a pile of gold encrusted with jewels. But on their return they were attacked by the Mosquito tribe\nAll except Miguel perished, the Indian darts are dipped in some local poison, even a small scratch leads to certain, agonizing death in a few days. Dichoso returned to Providence with what treasure he could carry\nCarajo! The baron was unspeakably happy, he sent urgent letters to Madrid and to Father Vincento in Santiago, no doubt that he wanted to rub his success in the Reverend Father's face. Then a frigate was prepared to deliver the treasure to back to Spain. Dichoso volunteered to escort it.";
			link.l1 = "Let me guess. He didn't deliver the gold?";
			link.l1.go = "spa_prisoner_22";			
		break;
		
		case "spa_prisoner_22":
			dialog.text = "Correct, senor! The frigate vanished without a trace along with the entire cargo and crew, including Dichoso. The baron was livid. He once again was humiliated in front of the Escorial to the great satisfaction of Father Vincento. Now Don Mendosa is a man obsessed with regaining his wounded pride, his lost treasure, and Miguel Dichoso";
			link.l1 = "Isn't it possible that the frigate could've just got caught in a storm and foundered? Or captured by pirates?";
			link.l1.go = "spa_prisoner_23";			
		break;
		
		case "spa_prisoner_23":
			dialog.text = "The baron swore in the heat of the moment that he was sure that Dichoso betrayed him. I don't know the details. After several weeks Don Diego de Montoya arrived with new information, that Miguel Dichoso may be in St.Pierre.";
			link.l1 = "Hm. Interesting. Those Indian treasures again. Everything seems suspiciously tied to them... So, you didn't find Dichoso?";
			link.l1.go = "spa_prisoner_24";			
		break;
		
		case "spa_prisoner_24":
			dialog.text = "No. And I honestly would be surprised if he was ever even here. The baron is so obsessed with the thought of capturing Dichoso that he would believe even the most farfetched fantasies.";
			link.l1 = "Tell me, "+npchar.name+", how did Don Mendosa find out about this... uh... city of Tayasal? He didn't dream it, right? Were there some facts or anything else?";
			link.l1.go = "spa_prisoner_25";			
		break;
		
		case "spa_prisoner_25":
			dialog.text = "It was Father Vincento who first heard of the alleged existence of Tayasal and the city of gold. Where he found out about it I have no idea...";
			link.l1 = "That's an interesting development. Father Vincento came up with the theory of Tayasal's existence by himself, informed Spain by himself, and began throwing flies into the baron's ointment...";
			link.l1.go = "spa_prisoner_26";			
		break;
		
		case "spa_prisoner_26":
			dialog.text = "As a fellow Catholic you should know about how these reverend fathers of the Holy Tribunal work... He didn't inform Madrid for no reason. He has some kind of angle, but the baron's arrival apparently wasn't part of his plans. Anyway, I don't know anything more about that. I've never had the desire to deal with the Inquisition.";
			link.l1 = "Alright. You've given me a lot of interesting information, "+npchar.name+", and true to my oath I'm taking you out of here. I will return for you later, but for now... let me think for a little bit about what you've told me...";
			link.l1.go = "spa_prisoner_27";			
		break;
		
		case "spa_prisoner_27":
			DialogExit();
			pchar.questTemp.Guardoftruth = "think";
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto3", "GuardOT_MCthink", -1);
		break;
		
		case "spa_prisoner_28":
			PlaySound("Voice\English\Ransack_2.wav");
			dialog.text = "Senor? Will you follow through with your promise?";
			link.l1 = "I always keep my promises. Today's your lucky day, "+npchar.name+". You're coming with me to Santiago on Cuba. I'll tell you more about my plan when we arrive. But for now, welcome on board. You'll be accompanied to the port and delivered to my ship.";
			link.l1.go = "spa_prisoner_29";			
		break;
		
		case "spa_prisoner_29":
			dialog.text = "My gratitude, captain. I'm glad you're a gentleman of your word.";
			link.l1 = "You can express your gratitude later. You will be my guest, but under guard. Don't take it the wrong way, I still need you.";
			link.l1.go = "spa_prisoner_30";			
		break;
		
		case "spa_prisoner_30":
			dialog.text = "I understand, senor. I give you my word as a Spanish officer that I won't make any attempts to escape.";
			link.l1 = "God spares the cautious. See you on board.";
			link.l1.go = "spa_prisoner_31";			
		break;
		
		case "spa_prisoner_31":
			DialogExit();
			pchar.questTemp.Guardoftruth = "cuba";
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			chrDisableReloadToLocation = false;//открыть локацию
			pchar.quest.GuardOT_exitbase.win_condition.l1 = "ExitFromLocation";
			pchar.quest.GuardOT_exitbase.win_condition.l1.location = pchar.location;
			pchar.quest.GuardOT_exitbase.function = "GuardOT_ExitFrombase";
			AddQuestRecord("Guardoftruth", "4");
		break;
		
		case "spa_prisoner_32":
			PlaySound("Voice\English\Serve_senior.wav");
			dialog.text = "Captain, what are your aims here on Cuba? Are you here to drop me off? I don't even dare hope for that...";
			link.l1 = "That's exactly right, I am here to deliver back to your countrymen. Now, the reason for my arrival here is a little more complicated than just that. But that no longer concerns you. I'll let you go right now without any ransom, but on the condition that you will swear two things to me.";
			link.l1.go = "spa_prisoner_33";			
		break;
		
		case "spa_prisoner_33":
			dialog.text = "What are they?";
			link.l1 = "The first is that I'll give you a sealed letter. You will personally deliver that letter to the Inquisitor of Santiago, Father Vincento. If he asks whom the letter from and how you got it, tell him the truth...";
			link.l1.go = "spa_prisoner_34";			
		break;
		
		case "spa_prisoner_34":
			dialog.text = "";
			link.l1 = "The second is that you will not aid or assist any attempts to find me and attack my ship at least for one week. Agreed?";
			link.l1.go = "spa_prisoner_35";			
		break;
		
		case "spa_prisoner_35":
			dialog.text = "Is that all?";
			link.l1 = "Yes, that's all. Fulfil my conditions and you're free to go.";
			link.l1.go = "spa_prisoner_36";			
		break;
		
		case "spa_prisoner_36":
			dialog.text = "I swear to you, senor, that I'll deliver the letter to Father Vincento personally and that I will not undertake actions of any kind that may provoke the aggression of Santiago's garrison against you or your ship. Rest assured, I will keep my word. I am a Spaniard and I respect strong and noble adversaries.";
			link.l1 = "All right, Don "+GetFullName(npchar)+", I accept your oath and I am letting you go right now. Here, take this letter for the Inquisitor. You are now free.";
			link.l1.go = "spa_prisoner_37";			
		break;
		
		case "spa_prisoner_37":
			Log_Info("You've given the letter");
			PlaySound("interface\important_item.wav");
			dialog.text = "Farewell, senor. I hope we will never meet again on the battlefield. It would grieve me terribly.";
			link.l1 = "Farewell...";
			link.l1.go = "spa_prisoner_38";			
		break;
		
		case "spa_prisoner_38":
			DialogExit();
			RemovePassenger(pchar, npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			chrDisableReloadToLocation = false;//открыть локацию
			AddQuestRecord("Guardoftruth", "5");
			pchar.quest.GuardOT_mayak.win_condition.l1 = "Timer";
			pchar.quest.GuardOT_mayak.win_condition.l1.date.hour  = sti(GetTime()-(rand(4)));
			pchar.quest.GuardOT_mayak.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.GuardOT_mayak.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.GuardOT_mayak.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.GuardOT_mayak.win_condition.l2 = "location";
			pchar.quest.GuardOT_mayak.win_condition.l2.location = "mayak9";
			pchar.quest.GuardOT_mayak.function = "GuardOT_CreateVinsentoAgent";
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;
		
		case "spa_prisoner_39":
			dialog.text = "Dios mio, what a lucky meeting! Hello, monsieur "+GetFullName(pchar)+"! I see you have become a welcome guest in Santiago. Are you working for the Holy Inquisition?";
			link.l1 = "Greetings, senor "+npchar.name+". I thought we'd never see each other again, at least not under friendly circumstances! No, I've just stopped by to visit Father Vincento. And what about you? Serving in Santiago now?";
			link.l1.go = "spa_prisoner_40";
		break;
		
		case "spa_prisoner_40":
			dialog.text = "After you freed me from arrest, I was compelled to stay in Santiago, it is not safe for me to return to Providence... but as you can see, I've kept my word. No Spanish ships in hot pursuit of you...";
			link.l1 = "I am glad that we are both men of our word.";
			link.l1.go = "spa_prisoner_41";
		break;
		
		case "spa_prisoner_41":
			dialog.text = "Listen, captain, would you mind to raise a glass of rum, to our reunion, so to speak? I never thought that I would ever offer that to a Frenchman, but you, senor, are an exception.";
			link.l1 = "Of course! I wouldn't mind rinsing my mouth with some rum. Let's go to the tavern.";
			link.l1.go = "spa_prisoner_42";
		break;
		
		case "spa_prisoner_42":
			DialogExit();
			NextDiag.CurrentNode = "spa_prisoner_43"; 
			FreeSitLocator("Santiago_tavern", "sit_front4");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "Santiago_tavern", "sit", "sit_front4", "GuardOT_SpaOfficerInTavern", -1);
		break;
		
		case "spa_prisoner_43":
			LAi_SetSitType(Pchar);
			dialog.text = "Ah, salud!";
			link.l1 = "What are we drinking to, senor officer?";
			link.l1.go = "spa_prisoner_44";
		break;
		
		case "spa_prisoner_44":
			dialog.text = "Let us drink to something neutral, but that concerns us both. For example, gallant and successful service to one's nation! We've all got our own!";
			link.l1 = "And let's drink also to our monarchs coming to an agreement with each other and that the French and the Spanish cease fighting both at home and in the Caribbean.";
			link.l1.go = "spa_prisoner_45";
		break;
		
		case "spa_prisoner_45":
			dialog.text = "Well said, captain! To peace! I will show you how to drink in Spainish! Arriba, abajo, al centro y pa' dentro!";
			link.l1 = "To peace... (drinking)";
			link.l1.go = "spa_prisoner_46";
		break;
		
		case "spa_prisoner_46":
			dialog.text = "Aha! Cuban rum is truly the best in the Caribbean...";
			link.l1 = "I agree. Tell me, did they try to punish you for being captured in St. Pierre?";
			link.l1.go = "spa_prisoner_47";
		break;
		
		case "spa_prisoner_47":
			dialog.text = "Fortunately I only got a slap on the wrist. That disaster is all behind me now. They need officers out here in the colonies, after all.";
			link.l1 = "And your commander... what was his name... Diego, right? How did the fruitless raid pan out for him? Did he get demoted?";
			link.l1.go = "spa_prisoner_48";
		break;
		
		case "spa_prisoner_48":
			dialog.text = "Oh, no! Our dear Diego de Montoya is untouchable while he's got Don Ramon de Mendosa y Riba behind him. By the way, Don Diego was in Santiago just yesterday. He arrived from San Jose.";
			link.l1 = "You don't say? Intriguing! Good thing we didn't meet on the street. I'm afraid that affair might have ended in a duel, haha!";
			link.l1.go = "spa_prisoner_49";
		break;
		
		case "spa_prisoner_49":
			dialog.text = "Don Diego has no time for you now, captain. He has far too much at stake right now to risk his life on a duel. He's come up with some scheme along with Baron Mendosa in the West Main. He put together a squadron in Havana and is looking to sail back to Spain any day now.";
			link.l1 = "Are you on his crew too?";
			link.l1.go = "spa_prisoner_50";
		break;
		
		case "spa_prisoner_50":
			dialog.text = "No. Tomorrow I'm departing to garrison in San Juan, which is in Puerto Rico. I'm no longer welcome on Providence with Don Mendosa there.";
			link.l1 = "Well, then let's drink to your new posting and may there be nothing but happy times and beautiful girls awaiting you there.";
			link.l1.go = "spa_prisoner_51";
		break;
		
		case "spa_prisoner_51":
			dialog.text = "Muchos gracias, monsieur. All kinds of good wishes to you to as well. Ah, I think it's time for me to go. I'll finish this drink and then take my leave of you.";
			link.l1 = "Vaya con Dios, senor "+npchar.name+". Maybe we'll meet each other again in peace.";
			link.l1.go = "spa_prisoner_52";
		break;
		
		case "spa_prisoner_52":
			DialogExit();
			AddDialogExitQuest("GuardOT_SpaOfficerOutTavern");
		break;
		
		case "spa_prisoner_53":
			PlaySound("Voice\English\other\OZGi-01.wav");
			dialog.text = "Just as I told you, Don Diego: the fish took the bait; hook, line, and sinker... Oh, looks like we meet again, monsieur. Unfortunately, not under the peaceful auspices that we wished.";
			link.l1 = ""+npchar.name+"? Well! I didn't expect this. For some reason, I thought you were an honest, noble officer. It turns out I was wrong.";
			link.l1.go = "spa_prisoner_54";
		break;
		
		case "spa_prisoner_54":
			dialog.text = "What makes you wrong? I kept my word, I didn't swear to eternal friendship with you. Nothing's changed, monsieur. You are still an enemy to Spain and my personal enemy. This isn't Santiago, there's no Father Vincento here, and his little writ of safe passage isn't going to help you...";
			link.l1 = "Oh, it's like that? I happen to think that having a friendly conversation over some rum, all the while trying to lure me into a trap is quite treacherous, don't you think, senor "+npchar.name+"?";
			link.l1.go = "spa_prisoner_55";
		break;
		
		case "spa_prisoner_55":
			dialog.text = "You dare call me treacherous, you maricon?!";
			link.l1 = "...";
			link.l1.go = "spa_prisoner_56";
		break;
		
		case "spa_prisoner_56":
			DialogExit();
			sld = CharacterFromID("Diego");
			sld.dialog.currentnode = "shore";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		// посланец Винсенто
		case "vinsentoagent":
			PlaySound("Voice\English\other\OZGi-02.wav");
			dialog.text = "Hey, you! Yeah, yeah, you! "+GetFullName(pchar)+"?";
			link.l1 = "Aye, mate. It's me.";
			link.l1.go = "vinsentoagent_1";			
		break;
		
		case "vinsentoagent_1":
			dialog.text = "I've got a letter from an important person. You already know who it is.";
			link.l1 = "I know, give it here.";
			link.l1.go = "vinsentoagent_2";			
		break;
		
		case "vinsentoagent_2":
			GiveItem2Character(pchar, "specialletter");
			ChangeItemDescribe("specialletter", "itmdescr_specialletter_vinsento");
			sld = ItemsFromID("specialletter");
			sld.text = "Letter_Vincento";
			dialog.text = "There you go. How about a few coins for my trouble?";
			if (sti(Pchar.money) >= 2000)
			{
				link.l1 = "Take a little silver. You've earned it honestly.";
				link.l1.go = "vinsentoagent_2_1";	
				AddCharacterExpToSkill(pchar, "Leadership", 50);
			}
			else
			{
				link.l1 = "You trying to put one over on me, mate? You were already paid for the delivery.";
				link.l1.go = "vinsentoagent_2_2";
			}
		break;
		
		case "vinsentoagent_2_1":
			AddMoneyToCharacter(pchar, -2000);
			dialog.text = "Thanks, lad. A pleasure dealing with a generous gentleman.";
			link.l1 = "Alright, get lost, and don't speak a word about went down here.";
			link.l1.go = "vinsentoagent_3";			
		break;
		
		case "vinsentoagent_2_2":
			dialog.text = "The Havana wolf is your friend...";
			link.l1 = "Huh? You still here...";
			link.l1.go = "vinsentoagent_3";			
		break;
		
		case "vinsentoagent_3":
			DialogExit();
			npchar.lifeday = 0;
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			chrDisableReloadToLocation = false;//открыть локацию
		break;
		
		// боцман Гая Марше
		case "boatsvandega":
			dialog.text = "Welcome aboard the 'Admirable', captain "+GetFullName(pchar)+"!";
			link.l1 = TimeGreeting()+"! Surprising. Do you know me?";
			link.l1.go = "boatsvandega_1";			
		break;
		
		case "boatsvandega_1":
			dialog.text = "Who in the French colonies hasn't heard about the grand captain named "+GetFullName(pchar)+", the one that kicked the teeth out of a Spanish squadron led by a battleship attacking St. Pierre and killed the whole enemy raiding party! You're a national hero!";
			link.l1 = "Oh, come on. 'A hero'... I'm just a soldier fulfilling his duty to France.";
			link.l1.go = "boatsvandega_2";
		break;
		
		case "boatsvandega_2":
			dialog.text = "Don't think that a lot of soldiers could have done what you did, captain... Eh, I would like to treat you to some rum in the tavern, but alas: the captain has forbidden letting the men drink even a drop of rum and I don't want to set a bad example...";
			link.l1 = "Hm... So you're not a captain yourself?";
			link.l1.go = "boatsvandega_3";
		break;
		
		case "boatsvandega_3":
			dialog.text = "Do I look like a captain? Hoho! No, I'm just the boatswain. Name is Serge Degas. Our captain, Gaius Marchais, spends all day in the tavern, meanwhile we've been lying out waiting for some 'merchants' caravan. Cap owes an allowance to the sailors, and to us to, the whole crew is completely out of pocket.. ";
			link.l1 = "What's wrong? The Spanish vanilla caravan not showing up to get its feathers plucked?";
			link.l1.go = "boatsvandega_4";
		break;
		
		case "boatsvandega_4":
			dialog.text = "No way! Our captain made an end of piracy after he had captured this galleon. You see, he heard that a trade caravan sailing to Europe will make a stop at Guadeloupe soon and they will be buying vanilla. So he filled our holds with vanilla to the top in Bridgetown! Thought that he would be able to sell it three hundred pesos a crate, yeah, fat chance!\nThere is no vanilla caravan when we arrive, of course, and selling vanilla to the locals would be a loss. So here we are, waiting for the 'merchants', I am sure they will show up here one day or three years from now... the Captain sits in the tavern the whole day, being a royal nuisance and pestering everyone. He only returns to the ship to pass out. Now, finally, he is ready to sell for two hundred pesos just to break even\nAll our money was put into that cargo. One day, the crew is going to tie him and sell vanilla for cheap just to cover our debts... I swear I can see it coming any day now.";
			link.l1 = "Aye...what's eating your captain?";
			link.l1.go = "boatsvandega_5";
		break;
		
		case "boatsvandega_5":
			dialog.text = "Well, if a job is worth doing, it's worth doing well. He does neither. He's a terrible bargainer. It would've been a different matter if he shipped freight as well, but he wanted to feel himself like a real merchant. I hope he trips overboard one night...";
			link.l1 = "I understood you, Serge. Don't worry, I'm sure someday your... caravan will show up.";
			link.l1.go = "boatsvandega_6";
		break;
		
		case "boatsvandega_6":
			dialog.text = "Oh, I don't believe in miracles, captain. Maybe we'll meet again someday and sip some rum... what I wouldn't do for some rum right now...";
			link.l1 = "Good luck, mate.";
			link.l1.go = "boatsvandega_7";
		break;
		
		case "boatsvandega_7":
			DialogExit();
			NextDiag.currentnode = "boatsvandega_8";
			npchar.DeckDialogNode = "boatsvandega_8";
			// активируем каракку
			sld = characterFromId("GOT_Gevarra");
			sld.Dialog.Filename = "Quest\Sharlie\Guardoftruth.c";
			sld.DeckDialogNode = "gevarra";
			AddQuestRecord("Guardoftruth", "16");
		break;
		
		case "boatsvandega_8":
			dialog.text = "Eh, captain, I sure would like a sip of rum!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "boatsvandega_8";
		break;
		
		// Гай Марше
		case "marshe_tavern":
			PlaySound("Voice\English\tavern\Kontrabandisti-08.wav");
			dialog.text = NPCStringReactionRepeat("Ho! Don't you happen to be from the merchant ship? No? Oh, my apologies. Of course, not... My mistake.", "I'm not in the mood, monsieur, so find yourself somebody else to talk to.", "Ah, you again?!", "Ahem...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Don't worry about it, mate. It happens.", "Have some rum, captain. It'll ease your troubles a bit...", "Don't be nervous, mate. It's bad for your health.", "All right, all right. I'm leaving.", npchar, Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
			NextDiag.TempNode = "marshe_tavern";
		break;
		
		case "marshe_lay":
			PlaySound("Voice\English\citizen\convict-03.wav");
			dialog.text = "A argh... Mm... What the hell, what is this?..";
			link.l1 = "Quiet, mate... Don't make noise...";
			link.l1.go = "marshe_lay_1";
		break;
		
		case "marshe_lay_1":
			PlaySound("Voice\English\citizen\convict-02.wav");
			dialog.text = "Huh? What? Fuck!";
			link.l1 = "";
			link.l1.go = "marshe_lay_2";
		break;
		
		case "marshe_lay_2":
			DialogExit();
			LAi_SetgroundSitType(npchar);
			NextDiag.currentnode = "marshe_sitground";
		break;
		
		case "marshe_sitground":
			PlaySound("Voice\English\EvilPirates07.wav");
			dialog.text = "Aaah! Who are you? What do you want from me?";
			link.l1 = "If you don't shut up, I'll beat your teeth in, savvy? Where are the holy vessels you grabbed when you took this ship?";
			link.l1.go = "marshe_sitground_1";
		break;
		
		case "marshe_sitground_1":
			dialog.text = "What vessels? I don't know what you're talking about! This is my ship!";
			link.l1 = "Your ship? Until not that long ago she was called 'Santa Margarita' and sailed under the Spanish flag... I'm asking you, where are those holy vessels? A gold ostensory, a cross encrusted with lazurite, and a gold censer? What did you do with them? You didn't sell them, did you?";
			link.l1.go = "marshe_sitground_2";
		break;
		
		case "marshe_sitground_2":
			dialog.text = "Oh God, I don't believe my ears... you're Spanish? Oh, no... you're not Spanish! You're French! That's even worse! You've sold out to those vile Castilians! How much are they buying Frenchmen's souls for these days? I won't tell you anything, traitor! You won't get your hands on those trinkets!";
			link.l1 = "Not a word eh? That's just fine with me. This isn't the best place for interrogation anyway... We're gonna gag you to keep you from squealing and then we're going into my longboat... you'll talk eventually matey. I have no doubt of that.";
			link.l1.go = "marshe_sitground_3";
		break;
		
		case "marshe_sitground_3":
			dialog.text = "You Spanish turncoat! You better...";
			link.l1 = "Silence, scoundrel... Follow right behind me or I'll knock you down and drag you across the deck by your feet.";
			link.l1.go = "marshe_sitground_4";
		break;
		
		case "marshe_sitground_4":
			DialogExit();
			RemoveAllCharacterItems(npchar, true);
			ChangeCharacterAddressGroup(npchar, "Deck_Galeon_Ship", "goto", "stand");
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			pchar.quest.GuardOT_marchfromgaleon.win_condition.l1 = "locator";
			pchar.quest.GuardOT_marchfromgaleon.win_condition.l1.location = "Deck_Galeon_Ship";
			pchar.quest.GuardOT_marchfromgaleon.win_condition.l1.locator_group = "reload";
			pchar.quest.GuardOT_marchfromgaleon.win_condition.l1.locator = "reload2";
			pchar.quest.GuardOT_marchfromgaleon.function = "GuardOT_ExitGaleon";
		break;
		
		// капитан каракки - Карлос Геварра
		case "gevarra":
			dialog.text = "How can I help you, sir?";
			link.l1 = "How are things, captain? What brings you to Basse-Terre? As I understand, you're a Spaniard sailing under the Dutch flag?";
			link.l1.go = "gevarra_1";			
		break;
		
		case "gevarra_1":
			dialog.text = "What's the problem, sir? Yes, I'm Spanish. That's easy to guess by the name and type of my ship, but I am here quite legally. I have a license from the Dutch West India Company, so...";
			link.l1 = "Don't get into a fuss, senor! We are very actually very glad that you are Spanish... Tell me, are you here for import or export?";
			link.l1.go = "gevarra_2";			
		break;
		
		case "gevarra_2":
			dialog.text = "I brought merchandise from Havana and sold it at on the local market. Now, I am awaiting some profitable freight to avoid sailing home with an empty hold.";
			link.l1 = "Senor, I've got a business proposition for you! You could earn good money if you help me. Shall we discuss it? What's your name by the way?";
			link.l1.go = "gevarra_3";			
		break;
		
		case "gevarra_3":
			dialog.text = "Carlos. Captain Carlos Guevara. What's your offer?";
			link.l1 = "I need to purchase a batch of vanilla and send it to Cuba, to a man named "+pchar.questTemp.Guardoftruth.LMname+", the watchman of the Santiago lighthouse. However, I've got a serious problem. First of all, no store has the amount of vanilla that I need...";
			link.l1.go = "gevarra_4";			
		break;
		
		case "gevarra_4":
			dialog.text = "";
			link.l1 = "Secondly, I must immediately depart for St. Christopher and I don't know how long I'll be gone. I'm losing money by the day, understand? It's a Goddamn shame!";
			link.l1.go = "gevarra_5";			
		break;
		
		case "gevarra_5":
			dialog.text = "I understand. Que lastima, senor. You can't make all the money in the world, after all. So what do you want from me?";
			link.l1 = "Look over there. See that galleon? She's stuffed with vanilla that I need dearly. The trouble is the captain of the galleon has drummed up some nonsense in his head about a spice caravan arriving here soon that'll buy his cargo at a profit, at almost three hundred pesos a crate!";
			link.l1.go = "gevarra_6";			
		break;
		
		case "gevarra_6":
			dialog.text = "Yes, there are a lot of naive men around these days, a fool and his money are soon parted...";
			link.l1 = "Naive is one thing, but he is just flat out stupid! I offered buying his vanilla at two hundred ten pesos, he won't even fetch two hundred in a store here. And can you believe it, he told me to shove off! He said he'd only sell at two hundred fifty!";
			link.l1.go = "gevarra_7";			
		break;
		
		case "gevarra_7":
			dialog.text = "Haha! What an idiot!";
			link.l1 = "Yes! That's basically what I told him. Of course he got angry at me... but I really need that vanilla! Here is my proposal senor. I'm not a merchant, but I think you are a real master of the art of the deal. And you have a capacious hold...";
			link.l1.go = "gevarra_8";			
		break;
		
		case "gevarra_8":
			dialog.text = "";
			link.l1 = "Talk this damned fool into selling you the cargo. He's not going to sell it to me now after I insulted him to his face. I'm willing to pay two hundred ten pesos per box. If you knock the price down, leave the difference to yourself. And for that I'll charter your boat to deliver the vanilla to Santiago";
			link.l1.go = "gevarra_9";			
		break;
		
		case "gevarra_9":
			dialog.text = "How much are you willing to pay me for the shipment?";
			link.l1 = "How much do you want?";
			link.l1.go = "gevarra_10";			
		break;
		
		case "gevarra_10":
			dialog.text = "Santiago is pretty far away...thirty thousand pesos.";
			link.l1 = "That's too much, amigo. Meet me halfway here.";
			link.l1.go = "gevarra_11";			
		break;
		
		case "gevarra_11":
			dialog.text = "Alright, it's on my way anyway...Twenty five thousand and not a peso less.";
			link.l1 = "That's fine. The captain of the galleon's named Gaius Marchais. He spends all day sulking in the tavern. I hope you can manage to convince him to part with his spices.";
			link.l1.go = "gevarra_12";			
		break;
		
		case "gevarra_12":
			dialog.text = "I've done business with bigger imbeciles before. I'll tell him all the details about who's making the rumors about the caravan who was supposedly going to buy the merchandise at sky-high prices. Once I've convinced him that its all a figment of his imagination he'll sell, I'm sure of it.";
			link.l1 = "So, we've got a deal?";
			link.l1.go = "gevarra_13";			
		break;
		
		case "gevarra_13":
			iTemp = sti(pchar.questTemp.Guardoftruth.VanilleQty)*210+25000;
			dialog.text = "We've got a deal if you have the cash to pay for the vanilla and the shipping. As the charming Irish saying goes: 'Show me the money.'";
			if (sti(Pchar.money) >= iTemp)
			{
				link.l1 = "Here you go, take a look. It's all here.";
				link.l1.go = "gevarra_14";
			}
			else
			{
				link.l1 = "I have the silver on my ship. I'll go get it and be right back!";
				link.l1.go = "gevarra_14_no";
			}
		break;
		
		case "gevarra_14_no":
			DialogExit();
			NextDiag.currentnode = "gevarra_wait";
			npchar.DeckDialogNode = "gevarra_wait";
		break;
		
		case "gevarra_wait":
			iTemp = sti(pchar.questTemp.Guardoftruth.VanilleQty)*210+25000;
			dialog.text = "Have you brought the money?";
			if (sti(Pchar.money) >= iTemp)
			{
				link.l1 = "Here you go, take a look. It's all here.";
				link.l1.go = "gevarra_14";
			}
			else
			{
				link.l1 = "I'm getting it right now!";
				link.l1.go = "exit";
			}	
		break;
		
		case "gevarra_14":
			if (stf(environment.time) < 24.0)
			{
				sTemp = "tomorrow";
				iTemp = 1;
			}
			else
			{
				sTemp = "today";
				iTemp = 0;
			}
			if (stf(environment.time) > 21.0 && stf(environment.time) < 7.0)
			{
				dialog.text = "Estupendo! I do enjoy doing business with sensible partners. Come back "+sTemp+" by ten in the morning. I think by that point our mutual friend Gaius will have come to his senses.";
				link.l1 = "Great! See you later!";
				link.l1.go = "gevarra_15";
				pchar.quest.GuardOT_tradetimer.win_condition.l1 = "Timer";
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.hour  = 10.0;
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, iTemp);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, iTemp);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, iTemp);
				pchar.quest.GuardOT_tradetimer.function = "GuardOT_PrepareTrade";
			}
			else
			{
				dialog.text = "Estupendo! I do enjoy doing business with sensible partners. I'm off to the shore. Come back in three hours. I think by that point our mutual friend Gaius will have come to his senses..";
				link.l1 = "Great! See you later!";
				link.l1.go = "gevarra_15";
				pchar.quest.GuardOT_tradetimer.win_condition.l1 = "Timer";
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.hour  = sti(GetTime()+3);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
				pchar.quest.GuardOT_tradetimer.function = "GuardOT_PrepareTrade";
			}
		break;
		
		case "gevarra_15":
			iTemp = sti(pchar.questTemp.Guardoftruth.VanilleQty)*210+25000;
			DialogExit();
			NextDiag.currentnode = "gevarra_time";
			npchar.DeckDialogNode = "gevarra_time";
			AddMoneyToCharacter(pchar, -iTemp); // деньги сразу списываем
			bQuestDisableMapEnter = true;
			pchar.GenQuest.MapClosedNoBattle = true;
			AddQuestRecord("Guardoftruth", "17");
			AddCharacterExpToSkill(pchar, "Sneak", 50);
		break;
		
		case "gevarra_time":
			dialog.text = "Senor, I remember my role well. Don't worry, he may be a tough nut, but I'll crack him.";
			link.l1 = "Thank you.";
			link.l1.go = "exit";
			NextDiag.TempNode = "gevarra_time";
		break;
		
		case "gevarra_16":
			dialog.text = "It is done, senor. The poor man was overjoyed that I wanted to buy his vanilla. His hands were shaking with happiness while I counted out an advance - or maybe that was just from the rum. We will load the cargo at Capster Beach at midday tomorrow in order to avoid any unwanted attention from customs agents at the harbor\nI will sail immediately to Santiago as soon as I have the cargo on board. I contact your partner at the lighthouse and sign the vanilla over to him after delivery there. Any message you want me to pass on to him?";
			link.l1 = "Yes. Here's a letter. You say the deal will be at Capster Beach tomorrow at noon? Alright then, I'll lie at anchor just off the headland, inaccessible to the island in case something happens.";
			link.l1.go = "gevarra_17";
		break;
		
		case "gevarra_17":
			Log_Info("You handed the letter over");
			PlaySound("interface\important_item.wav");
			dialog.text = "You can trust me, senor. I'm an honest man. Besides, I have no desire to quarrel with you, and a merchant is nothing without his reputation. But if you'd like to watch and verify, it is no hardship for me.";
			link.l1 = "I am grateful, senor. I'll watch over the deal tomorrow and as soon as you cast off, I'll go about my business at St. Christopher.";
			link.l1.go = "gevarra_18";
		break;
		
		case "gevarra_18":
			DialogExit();
			NextDiag.currentnode = "gevarra_exit";
			npchar.DeckDialogNode = "gevarra_exit";
			bQuestDisableMapEnter = true;
			pchar.GenQuest.MapClosedNoBattle = true;
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			AddQuestRecord("Guardoftruth", "18");
			pchar.quest.GuardOT_gotoshore.win_condition.l1 = "ExitFromSea";
			pchar.quest.GuardOT_gotoshore.function = "GuardOT_TradeComplete";
		break;
		
		case "gevarra_exit":
			dialog.text = "Captain, I assure you: I won't let you down and I will fulfill the conditions of our deal in full.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "gevarra_exit";
		break;
		
		// матросы Марше
		case "marshe_sailor":
			dialog.text = LinkRandPhrase("Hiic! H-hurrah! Good ol' capt'n finally gave us our pay! Three c-cheers for the cap'n! Hic!","It comes in pints?! I'm getting one!","May our purses be fat and our wenches fatter! Hurrah!","And there they lay, all good dead men, hic! Like break o'day in a boozing ken. Yo ho ho and a bottle of rum!","Yo ho ho and a bottle of rum!");
			link.l1 = LinkRandPhrase("Aye, mate.","Don't you think you've had enough rum already?","Drink and the devil have done for the rest...");
			link.l1.go = "exit";
		break;
		
		case "galeonguard":
			PlaySound("Voice\English\EvilPirates01.wav");
			dialog.text = "Halt! Who goes there? Alarm! Repel boarders!";
			link.l1 = "...";
			link.l1.go = "galeonguard_1";
		break;
		
		case "galeonguard_1":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.CantRun");
			CheckAndSetOverloadMode(GetMainCharacter());
			DeleteAttribute(pchar, "questTemp.Guardoftruth.Attack");
			LAi_RemoveCheckMinHP(pchar);
			GuardOT_GaleonGuardFightAdd();
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("GuardOT_galeonguard_"+i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, "GaleonFight");
			}
			LAi_group_FightGroups("GaleonFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// англичане в бухте
		case "dominica_hunter":
			dialog.text = "Har har! You've come for Rollie the Cap's treasure too, eh? We've been looking and looking and looking and we just couldn't find it. I wish at least one of these imbeciles would guess to swim behind the waterfall onto the ledge!";
			link.l1 = "You're one of Colonel Fox's men, aren't you?";
			link.l1.go = "dominica_hunter_1";
		break;
		
		case "dominica_hunter_1":
			dialog.text = "I may have ties to the Sea Foxes. You don't need to know, there's no point. You don't need to know anything right now. You've found my treasure, which we now owe you a huge thanks for...";
			link.l1 = "I see. You're not a Sea Fox, more like a sea dog... or jackal. What suits you better?";
			link.l1.go = "dominica_hunter_2";
		break;
		
		case "dominica_hunter_2":
			dialog.text = "Looks like we've got a natural philosopher on our hands, boys. A real expert on the animal kingdom!";
			link.l1 = "Shall you inspect the sharpness of my saber, jackal?";
			link.l1.go = "dominica_hunter_3";
		break;
		
		case "dominica_hunter_3":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("GuardOT_DH_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_HuntersDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// Белинда Риберо
		case "belinda":
			dialog.text = TimeGreeting()+", senor. How can I help you?";
			link.l1 = "Hello. Are you Donna Belinda de Ribero?";
			link.l1.go = "belinda_1";
		break;
		
		case "belinda_1":
			dialog.text = "Yes, I am. With whom do I have the honor of speaking?";
			link.l1 = "Captain "+GetFullName(pchar)+", madam. Please don't be put off by my French surname, at the moment I'm fulfilling an assignment from the Right Reverend Inquisitor of Santiago, Father Vincento.";
			link.l1.go = "belinda_2";
		break;
		
		case "belinda_2":
			dialog.text = "Que interesante! I've heard that the Holy Tribunal and the Society of Jesus are filled with a great multitude of people, of all classes and nationalities, but I had never personally met a foreigner working for them before now. What can I do for you, senor?";
			link.l1 = "You possess an object that the Reverend Father is very interested in. A golden ostensory, a monstrance that you've acquired recently from the banker in Willemstad.";
			link.l1.go = "belinda_3";
		break;
		
		case "belinda_3":
			dialog.text = "You're very well-informed, senor. Well, knowing who you work for, this shouldn't surprise me. Yes, I bought the ostensory, it certainly should not have been left to sit in a merchant's shop next to stolen baubles and pawned goods like some petty trifle.";
			link.l1 = "Do you have the monstrance, madam?";
			link.l1.go = "belinda_4";
		break;
		
		case "belinda_4":
			dialog.text = "Yes. I intended to gift it to our parish church, but so much has come upon me here... I couldn't... oh, I'm sorry...";
			link.l1 = "Am you weeping, madam? Have my words brought sorrow to you? If so, please forgive me.";
			link.l1.go = "belinda_5";
		break;
		
		case "belinda_5":
			dialog.text = "Oh, please senor... Let's return to our conversation. As I understand, Father Vincento needs this ostensory? You would like me to give it to you?";
			link.l1 = "This precious vessel was intended for the cathedral in Santiago, but it was captured by a common pirate and sold to a usurer with several other holy objects. My task is to return that which was stolen back to where it belongs. Of course, I will fully compensate you for your expenses.";
			link.l1.go = "belinda_6";
		break;
		
		case "belinda_6":
			dialog.text = "Oh, you mustn't! Do you really think this money means that much to me? I bought this ostensory for Holy Mother Church and I won't hesitate to hand it over to its true owner, not even to mention a member of the Society of Jesus serving Father Vincento. But, another thing troubles me deeply. Could you please help a faithful daughter of the Church in her need?";
			link.l1 = "You are a noble woman, madam. What troubles bother you? How may I help you?";
			link.l1.go = "belinda_7";
		break;
		
		case "belinda_7":
			dialog.text = "Oh, but senor... I wouldn't dare to ask a Jesuit brother himself for help. You are always so very busy...";
			link.l1 = "You already did. What's the matter?";
			link.l1.go = "belinda_8";
		break;
		
		case "belinda_8":
			dialog.text = "Can you promise me, as a representative of the Holy Church that no one will ever find out what I'm asking you for?";
			link.l1 = "I give you my solemn oath, senora. It is the not the seal of the confessional, but I will not breathe a word about this to a soul.";
			link.l1.go = "belinda_9";
		break;
		
		case "belinda_9":
			dialog.text = "Very well. I trust you. My very dear friend Esteban Sosa has got in trouble. He was captured by bandits while traveling and they demand a ransom of one hundred thousand pesos. I don't possess that much money and only managed to collect about half of the sum from my allowance. I can't ask for anyone's help in such matter because they swore they would kill him if I did\nBesides I worry for my dear... friend and fear the worst. They may have him killed as soon as they get the money to make sure that he won't tell the guards about them. Perhaps you, a brave captain, a Christian, and a brother of the Society could persuade the bandits to accept the money I have and not to harm him...";
			link.l1 = "When and where will the exchange take place?";
			link.l1.go = "belinda_10";
		break;
		
		case "belinda_10":
			dialog.text = "Their ringleader is some man named Bartie the Knacker. He said he'd be waiting for Esteban's ransom every night from eleven p.m. to midnight at the cave entrance in the jungle...";
			link.l1 = "Those are unusually specific conditions...";
			link.l1.go = "belinda_11";
		break;
		
		case "belinda_11":
			dialog.text = "Apparently they wanted me to put the whole ransom together quickly and didn't want me to ask anyone for help... but I can't find such money, I'll never be able to!";
			link.l1 = "Don't cry, madam. I'll try to help you. A brother of the Society of Jesus would never leave a righteous Christian woman in peril.";
			link.l1.go = "belinda_12";
		break;
		
		case "belinda_12":
			dialog.text = "I must put my faith in you...But captain, Bartie the Knacker also said that if the ransom bearer doesn't come alone or if I go to the guards, he'll immediately kill poor Estaban!";
			link.l1 = "I'll keep that in mind.";
			link.l1.go = "belinda_13";
		break;
		
		case "belinda_13":
			dialog.text = "Here, take this. It's the fifty thousand pesos I was able to scrape together. Talk those brigandos into taking this at least. Tell them I don't have a single peso more! Bring Esteban back! Once you do I'll gladly give you the ostensory for Father Vincento.";
			link.l1 = "I'll do everything I can, madam. Let's hope for the best.";
			link.l1.go = "belinda_14";
		break;
		
		case "belinda_14":
			dialog.text = "May God help you, courageous captain! I will pray for you!";
			link.l1 = "...";
			link.l1.go = "belinda_15";
		break;
		
		case "belinda_15":
			AddMoneyToCharacter(pchar, 50000);
			DialogExit();
			NextDiag.CurrentNode = "belinda_16";
			AddQuestRecord("Guardoftruth", "31");
			bQuestDisableMapEnter = true;//закрыть карту
			locations[FindLocation("Cumana_CaveEntrance")].DisableEncounters = true; //энкаутеры закрыть
			LAi_LocationDisableOfficersGen("Cumana_CaveEntrance", true);
			LAi_LocationDisableOfficersGen("Cumana_Cave", true);
			pchar.quest.GuardOT_gotocave.win_condition.l1 = "location";
			pchar.quest.GuardOT_gotocave.win_condition.l1.location = "Cumana_CaveEntrance";
			pchar.quest.GuardOT_gotocave.win_condition.l2 = "HardHour";
			pchar.quest.GuardOT_gotocave.win_condition.l2.hour = 23.00;
			pchar.quest.GuardOT_gotocave.function = "GuardOT_InCaveEntrance";
		break;
		
		case "belinda_16":
			dialog.text = "Do you have any news, captain?";
			link.l1 = "Not yet. Just wait, senora. I won't let you down.";
			link.l1.go = "exit";
			NextDiag.TempNode = "belinda_16";
		break;
		
		case "belinda_17":
			dialog.text = "Do you have any news, captain?";
			link.l1 = "Yes, senora. It's not good news, I'm afraid.";
			link.l1.go = "belinda_18";
		break;
		
		case "belinda_18":
			dialog.text = "Tell me, don't keep me waiting! Did you meet with the bandits?";
			if (sti(Pchar.money) >= 50000)
			{
				link.l1 = "Here, take your fifty thousand back. I didn't need it. Take this ring too. I believe you'll find it familiar.";
				link.l1.go = "belinda_19_1";
			}
			link.l2 = "Here, take this ring. I believe you'll find it familiar.";
			link.l2.go = "belinda_19_2";
		break;
		
		case "belinda_19_1":
			RemoveItems(pchar, "jewelry29", 1);
			PlaySound("interface\important_item.wav");
			AddMoneyToCharacter(pchar, -50000);
			dialog.text = "It... yes, it's familiar. What happened to Esteban?";
			link.l1 = "I found the brigands at the cave, like you told me. 'Bartie the Knacker' and Esteban Sosa are the same man. He staged the kidnapping in order to extort you. He told me about your... relationship. He also said that he does not want to see you anymore. I took the ring that you gave him as proof.";
			link.l1.go = "belinda_20";
		break;
		
		case "belinda_19_2":
			dialog.text = "This... yes, yes I know it. What happened to Esteban?";
			link.l1 = "I found the brigands at the cave, like you told me. They attacked me, tied me up, and took your money. 'Bartie the Knacker' and Esteban Sosa are the same man. He staged the kidnapping to extort you. He told me about your... relationship. Esteban let me go and gave me this ring as proof. He said that you will never see him again.";
			link.l1.go = "belinda_20";
			npchar.quest.nomoney = true;
		break;
		
		case "belinda_20":
			if (CheckAttribute(npchar, "quest.nomoney")) sTemp = "";
			else sTemp = "I taught him a lesson, but I didn't kill him out of respect to you.";
			dialog.text = "Dios mio! I don't believe my ears! Why does all this happen to me, why?! What did I do for him to....";
			link.l1 = "Senora, I'm begging you, don't beat yourself up over this. That reprobate isn't worth a single tear of yours. "+sTemp+"";
			link.l1.go = "belinda_21";
		break;
		
		case "belinda_21":
			if (CheckAttribute(npchar, "quest.nomoney")) sTemp = "";
			else sTemp = "And besides that, here's a gift to keep up your courage.";
			dialog.text = "Oh... I'll try to calm down. Senor, I must thank you for your help. Here, take your ostensory. "+sTemp+" Vaya con Dios.";
			link.l1 = "Gracias, senora. Don't worry, no one will find out about what happened in the cave. We Jesuits always keep our word. Now if you please, I must go.";
			link.l1.go = "belinda_22";
		break;
		
		case "belinda_22":
			DialogExit();
			AddQuestRecord("Guardoftruth", "33");
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 3;
			GiveItem2Character(pchar, "jewelry33");
			Log_Info("You've received a gold ostensory");
			PlaySound("interface\important_item.wav");
			if (CheckAttribute(npchar, "quest.nomoney"))
			{
				ChangeCharacterComplexReputation(pchar, "nobility", -3);
				OfficersReaction("bad");
			}
			else
			{
				Log_Info("You've received an amulet");
				GiveItem2Character(pchar, "amulet_7");
				ChangeCharacterComplexReputation(pchar, "nobility", 5);
				OfficersReaction("good");
				ChangeCharacterNationReputation(pchar, SPAIN, 3);
				AddCharacterExpToSkill(pchar, "Leadership", 300);
			}
		break;
		
		// бандит Эстебана
		case "bandos_mush":
			PlaySound("Voice\English\other\OZGi-04.wav");
			dialog.text = "Stop right there, matey!";
			link.l1 = "I'm standing right here.";
			link.l1.go = "bandos_mush_1";
		break;
		
		case "bandos_mush_1":
			dialog.text = "Did you bring the money?";
			link.l1 = "What a silly question. No, I'm out here picking Manga Rosas... Why else do you think I would've come here?";
			link.l1.go = "bandos_mush_2";
		break;
		
		case "bandos_mush_2":
			dialog.text = "Oh ho ho! A comedian! Off you go into the cave, Bartie's been waiting for you.";
			link.l1 = "You are clearly an experienced guard...with that attitude you'd be fit to guard King Philip himself. I'll show myself in.";
			link.l1.go = "bandos_mush_3";
		break;
		
		case "bandos_mush_3":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("Cumana_CaveEntrance", "reload2_back", true);
			LAi_SetWarriorType(npchar);
			LAi_CharacterDisableDialog(npchar);
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			pchar.quest.GuardOT_incave.win_condition.l1 = "location";
			pchar.quest.GuardOT_incave.win_condition.l1.location = "Cumana_Cave";
			pchar.quest.GuardOT_incave.function = "GuardOT_InCumanaCave";
		break;
		
		// Эстебан-Барти
		case "barty":
			PlaySound("Voice\English\other\OZGi-03.wav");
			dialog.text = "You kept me waiting... Do you have the money with you?";
			link.l1 = "Are you Bartie the Knacker? You don't look like a common bandit to me.";
			link.l1.go = "barty_1";
		break;
		
		case "barty_1":
			dialog.text = "Why do you care what I look like? Do you have the goddamn money or not?";
			link.l1 = "Where's the hostage?";
			link.l1.go = "barty_2";
		break;
		
		case "barty_2":
			dialog.text = "You'll get your hostage. Come on, give me the coin. Don't make me angry, boy.";
			link.l1 = "Bartie, do I look like an fool? Until I see Esteban Sosa alive and kicking, you're not going to see a single peso. Where is he?";
			link.l1.go = "barty_3";
		break;
		
		case "barty_3":
			dialog.text = "Oh, you're diggin' your heels in, eh? All right, we're gonna teach you a good lesson... Lads, let's tear this shiteater a new hole!";
			link.l1 = "Bastard!";
			link.l1.go = "barty_4";
		break;
		
		case "barty_4":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			GuardOT_InCumanaCaveEnemyAdd();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("GOT_bandos_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_CumanaCaveBandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");
			// офицеров насильно
			LAi_LocationDisableOfficersGen("Cumana_Cave", false); //офицеров пускать
			DoQuestFunctionDelay("GuardOT_SetOfficerCumanaCave", 3.0);
		break;
		
		case "barty_5":
			PlaySound("Voice\English\other\Plennie-02.wav");
			dialog.text = "";
			link.l1 = "Is that enough dancing for you? Where's Esteban Sosa? Come on, tell me or I'll hold your head underwater until the bubbles stop!";
			link.l1.go = "barty_6";
		break;
		
		case "barty_6":
			dialog.text = "No... Don't hurt me, please! I am Esteban Sosa.";
			link.l1 = "What?";
			link.l1.go = "barty_7";
		break;
		
		case "barty_7":
			dialog.text = "Yeah, yeah. I'm no Bartie the Knacker. I'm just...";
			link.l1 = "You scoundrel! So you decided to suck a hundred thousand pesos out of Senora de Ribero by 'kidnapping' yourself?!";
			link.l1.go = "barty_8";
		break;
		
		case "barty_8":
			dialog.text = "You need to understand me, man to man. Belinda...She's really got me turned off with her obsessive love. She's all over me, night and day, man! Even her husband started getting suspicious about us and he's half blind!";
			link.l1 = "Well, how about that! So you're lovers?";
			link.l1.go = "barty_9";
		break;
		
		case "barty_9":
			dialog.text = "Not anymore. I just ran away from her.";
			link.l1 = "And you decided to take some coins for the road, eh? Well, what should I do with you now? Hide your body in the jungle like you tried to do to me?";
			link.l1.go = "barty_10";
		break;
		
		case "barty_10":
			dialog.text = "No! I didn't want any blood, I swear!";
			link.l1 = "Is that why you set your dogs on me?";
			link.l1.go = "barty_11";
		break;
		
		case "barty_11":
			dialog.text = "We were just going to turn out your pockets, that's it!";
			link.l1 = "And leave me naked in the selva? I should string you up and hang you from the highest yardarm of my ship, you knave! But I will not do that, purely out of respect to the good woman that had the misfortune of getting involved with you. You know what? I should take you to her and let her decide what to do with you.";
			link.l1.go = "barty_12";
		break;
		
		case "barty_12":
			dialog.text = "No, anything but that! I'm not going back to Cumana!";
			link.l1 = "You'd rather stay in this cave forever?";
			link.l1.go = "barty_13";
		break;
		
		case "barty_13":
			dialog.text = "Spare me, senor! Let me go and I'll sail away from here and never come back to Cumana again! I'm not going to wait for Belinda's husband to slice me apart me in a duel or send an assassin for me!";
			link.l1 = "Fine. For the sake of Senora de Ribero, I'm not going to bring you to her. But don't think for a second that this is all going to be swept under the rug. She is going to find out about the pathetic piece of shit that she decided to flirt with. What tokens do you have that she'd be able to recognize?";
			link.l1.go = "barty_14";
		break;
		
		case "barty_14":
			dialog.text = "Here. This turquoise ring here. She gave it to me herself.";
			link.l1 = "Perfect. Give it here and get out of my sight!";
			link.l1.go = "barty_15";
			// belamour legendary edition -->
			link.l2 = "Perfect. And you know, Sosa, I changed my mind - now I serve the Society of Jesus. As the Scriptures say, 'You must purge the evil person from among you.' And you are a wicked narcissist, a criminal, and a useless piece of shit. I think I'll drown you in this cave. Requiesce in pace.";
			link.l2.go = "barty_15a";
		break;
		
		case "barty_15a":
			DialogExit();
			GiveItem2Character(pchar, "jewelry29");
			Log_Info("You received a turquoise ring");
			PlaySound("interface\important_item.wav");
			LAi_SetActorType(pchar);
			// если не надет пистоль или мушкет, то выдадим строевой -->
			if(!CheckAttribute(pchar,"equip."+GUN_ITEM_TYPE))
			{
				GiveItem2Character(pchar, "pistol1");
				EquipCharacterbyItem(pchar, "pistol1");
			}
			LAi_ActorAnimation(pchar, "Shot", "RIP_Sosa", 1.0); 
		break;
			
		case "barty_15":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			// <-- legendary edition
			GiveItem2Character(pchar, "jewelry29");
			Log_Info("You received a turquoise ring");
			PlaySound("interface\important_item.wav");
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationDisableOfficersGen("Cumana_CaveEntrance", false);//офицеров пускать
			locations[FindLocation("Cumana_CaveEntrance")].DisableEncounters = false; //энкаутеры открыть
			locations[FindLocation("Cumana_Cave")].DisableEncounters = false; // patch
			LAi_LocationFightDisable(&Locations[FindLocation("Cumana_CaveEntrance")], false);//разрешить драться
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			LocatorReloadEnterDisable("Cumana_CaveEntrance", "reload2_back", false);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			sld = characterFromId("GOT_Belinda");
			sld.dialog.currentnode = "Belinda_17";
			AddQuestRecord("Guardoftruth", "32");
		break;
		
		// охотники
		case "spa_hunter":
			dialog.text = "You've got what we need, matey...";
			link.l1 = "Really? And what would that be?";
			link.l1.go = "spa_hunter_1";
		break;
		
		case "spa_hunter_1":
			dialog.text = "I didn't ask, rich boy. I've just been ordered to take your belongings, absolutely everything you have on you. Are we going to do this the easy way or the hard way? The choice is yours.";
			link.l1 = "Think you're a warrior, huh? You have no clue who you're dealing with. I eat scum like you for breakfast.";
			link.l1.go = "spa_hunter_2";
		break;
		
		case "spa_hunter_2":
			dialog.text = "You're a proper jester, aren't you froggy? Well then, let's see how your blood looks on the ground!";
			link.l1 = "It'll look the same as yours, idiot. Let me treat you to an anatomy lesson!";
			link.l1.go = "spa_hunter_3";
		break;
		
		case "spa_hunter_3":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for(i=1; i<=5; i++)
			{
				sld = characterFromID("GOT_santiagoband_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_SantiagoBandDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "cabin_hunter":
			dialog.text = "Haw haw, all right matey... Turn out your pockets on the double! If you're a good little boy and listen, you'll stay in one piece, savvy?";
			link.l1 = "Goddamn, you lot again? You came all the way out here too? Who the devil hired you?!";
			link.l1.go = "cabin_hunter_1";
		break;
		
		case "cabin_hunter_1":
			dialog.text = "None of your business. Now surrender and live or put up a fight and we'll just take your loot off your dead body. How's that for a deal?";
			link.l1 = "I have a counteroffer. How about I take your loot off your dead body?";
			link.l1.go = "cabin_hunter_2";
		break;
		
		case "cabin_hunter_2":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for(i=1; i<=2; i++)
			{
				sld = CharacterFromID("GOT_cabinband_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_CabinBandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// командир абордажников
		case "batabano_officer":
			dialog.text = "Awaiting orders, captain!";
			link.l1 = "Move through the jungle toward San Antonio Cape. Take the trail left and keep going straight. Keep your heads down and get ready for an ambush on the shore. Be ready. I'll be going there by sea and will meet you there. How long will it to take you to get there?";
			link.l1.go = "batabano_officer_1";
		break;
		
		case "batabano_officer_1":
			dialog.text = "We'll be there in six hours, captain!";
			link.l1 = "Good. Move!";
			link.l1.go = "batabano_officer_2";
		break;
		
		case "batabano_officer_2":
			DialogExit();
			LocatorReloadEnterDisable("Shore13", "boat", false);
			for(i=1; i<=10; i++)
			{
				sld = characterFromID("GuardOT_Oursoldier_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "OpenTheDoors", 20.0);
			}
			AddQuestRecord("Guardoftruth", "48");
			// на мыс
			pchar.quest.GuardOT_sanantonio.win_condition.l1 = "Ship_location";
			pchar.quest.GuardOT_sanantonio.win_condition.l1.location = "Shore15";
			pchar.quest.GuardOT_sanantonio.function = "GuardOT_SanantonioArrive";
			// на время, специально для дебилов, не читающих диалоги и СЖ
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1 = "Timer";
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1.date.hour  = sti(GetTime()+6);
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.GuardOT_sanantoniotimer.function = "GuardOT_SanAntonio_Timer";
		break;
		
		// наёмник Патерсона
		case "housemercen":
			dialog.text = "Tenacious bastard! He's still alive... I knew we should've used more gunpowder! Alright fine, I'll finish you off, you son of a bitch...";
			link.l1 = "...";
			link.l1.go = "housemercen_1";
		break;
		
		case "housemercen_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			bDisableCharacterMenu = false;//разлочим F2
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			if (MOD_SKILL_ENEMY_RATE < 5) LAi_group_SetCheck("EnemyFight", "GuardOT_HouseMercenDie");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

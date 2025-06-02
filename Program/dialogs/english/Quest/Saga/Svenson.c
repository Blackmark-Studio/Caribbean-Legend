// Ян Свенсон - пиратский барон Западного Мэйна
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp, sStr;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Svenson")) {
				if (pchar.questTemp.HelenDrinking.Result == "won") {
					dialog.text = "Ah, Charles. Thanks for coming by. Just wanted to thank you for spending time with Helen. The girl needed to heal her wounds, and I heard you also had a good time, ha-ha! Damn, I'm even jealous!";
					link.l1 = "You're not upset? About the barrel and... everything else?";
					link.l1.go = "after_drinking";
				} else {
					dialog.text = "Ah, Charles. Thanks for coming by. Just wanted to thank you for spending time with Helen. The girl needed to heal her wounds, and I heard you also had a good time, ha-ha! Good luck to you in Cartagena!";
					link.l1 = "Yeah, I'm also glad that everything went well yesterday. Until we meet again, Jan.";
					link.l1.go = "exit";
				}
				
				DeleteAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Svenson");
				break;
			}
		
			if(CheckAttribute(pchar, "questTemp.Saga"))
			{
				if (CheckAttribute(pchar, "questTemp.Saga_Late")) // отсекание при провале по времени
				{
					dialog.text = "Oh, my friend "+pchar.name+"! Pleasure seeing you! What can I do for you?";
					link.l1 = "Just stopping by to see how you're doing.";
					link.l1.go = "exit";
					if(CheckAttribute(npchar, "quest.trade_bakaut")) // торговля бакаутом
					{
						if (GetDataDay() == 14 || GetDataDay() == 28)
						{
							link.l2 = "Jan, I'd like to buy ironwood.";
							link.l2.go = "trade_bakaut";
						}
					}
					break;
				}
				if(pchar.questTemp.Saga == "svenson")
				{
					dialog.text = "How can I help you, Sir?";
					link.l1 = "I'd like to ask for your help, Forest Devil.";
					link.l1.go = "saga";
					break;
				}
				if(pchar.questTemp.Saga == "svenson1")
				{
					dialog.text = "Aha, my friend "+pchar.name+"! What's the news?";
					link.l1 = "I've managed to learn a lot of interesting things from Hangman.";
					link.l1.go = "saga_11";
					break;
				}
				if(pchar.questTemp.Saga == "svenson2")
				{
					dialog.text = "So, "+pchar.name+", did you speak to Gladys?";
					link.l1 = "Yes I did. Jan, have a look here... Can you tell me anything about this patch of parchment here?";
					link.l1.go = "saga_17";
					break;
				}
				if(pchar.questTemp.Saga == "helena1" || pchar.questTemp.Saga == "helena2" || pchar.questTemp.Saga == "svenson_wait")
				{
					dialog.text = "I've got nothing new to tell you yet, "+pchar.name+". But I'm working on a solution for our matter. Come back later.";
					link.l1 = "Alright, Jan. I'll see you later.";
					link.l1.go = "exit";
					break;
				}
				if(pchar.questTemp.Saga == "baronsquests") // старт трех квестов баронов
				{
					// первая проверка времени. Свенсон очень недоволен растяпством ГГ. Счищаем Элен, к Свенсону доступ закроем
					if (CheckAttribute(pchar, "questTemp.Saga.Late"))
					{
						dialog.text = ""+pchar.name+", you have utterly disappointed me. I expected you to be a serious man, but as it turns out you are just a silly boy. Where have you been all this time, huh? The English claimed Isla Tesoro while you were doing god knows what!\nAll my plans are ruined! To be honest, I have almost forgotten about your existence and I don't want to be remembered about it. Get lost!";
						link.l1 = "I can't believe it!";
						link.l1.go = "saga_l1";
					}
					else
					{
						dialog.text = "There you are, "+pchar.name+". I've chewed our plight over a little. I wouldn't necessarily call it a plan, but...";
						link.l1 = "I'm all ears, Jan.";
						link.l1.go = "saga_25";
					}
					break;
				}
				if(pchar.questTemp.Saga == "baronsquests_1") // идут три квеста баронов
				{
					dialog.text = "How are things coming along? Is there anything I can assist you with?";
					if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "after_marlow")
					{
						link.l3 = "I've spoken to the Black Pastor. Sadly, the outcome of our conversation has sent me right back to you for advice, I'm stumped.";
						link.l3.go = "shark_hunt_2";
					}
					if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "LSC" && !CheckAttribute(pchar, "questTemp.Saga.BaronReturn"))
					{
						link.l3 = "I found Dios and we had a pleasant chat. He told me many interesting things, but unfortunately we didn't get to the nitty-gritty.";
						link.l3.go = "shark_hunt_7";
					}
					if (CheckAttribute(pchar, "questTemp.Saga.BaronReturn") && pchar.questTemp.Saga.BaronReturn == "third_teleport")
					{
						link.l3 = "Oh, Jan. I've got so much to tell you that it would take all night for me to relay everything onto you, so I'll be brief.";
						link.l3.go = "return_LSC";
					}
					if (CheckAttribute(pchar, "questTemp.Saga.BaronReturn") && pchar.questTemp.Saga.BaronReturn == "shamane" && !CheckAttribute(npchar, "quest.shamane"))
					{
						link.l3 = "I picked up Nathaniel Hawk from Justice Island. He's on my ship right now.";
						link.l3.go = "nathaniel";
					}
					if (CheckAttribute(pchar, "questTemp.Saga.BaronReturn") && pchar.questTemp.Saga.BaronReturn == "treatment")
					{
						link.l3 = "I've dropped off Nathaniel Hawk at the Miskito village for treatment by a shaman named Snake Eye. He promised me to restore Nathan's health.";
						link.l3.go = "nathaniel_2";
					}
					link.l4 = "Not much to tell you at the moment. Just stopping by to see how you are.";
					link.l4.go = "exit";
					break;
				}
				if(pchar.questTemp.Saga == "fail_centurion") // провал - потоплен Центурион
				{
					dialog.text = "What's the news, "+pchar.name+"? How are things?";
					link.l1 = "Oh, couldn't be worse. I've done so much work... I tracked down Jackman, we threw away the scabbards, and I drowned him like the biggest imbecile along with everything that might've been inside his cabin. Now I've got nothing to help me take the stink off of Shark's name and put the heat on Barbazon. I'm afraid it's a lost cause, Jan.";
					link.l1.go = "saga_f_1";
					break;
				}
				if(pchar.questTemp.Saga == "calendar") // квесты баронов завершены
				{
					// вторая проверка времени. Отбираем Элен, со Свенсоном нейтральные отношения - ну не выщло и не вышло, хоть попытались. Данни и Натана - в Марун-Таун
					if (CheckAttribute(pchar, "questTemp.Saga.Late"))
					{
						dialog.text = "I heard about your heroic deeds! Dannie gave me the short version. By the way, we are friends now. And Nathan has completely changed! All his depression was blown away when he saw his 'Centurion'.\nBut I have bad news for you, "+pchar.name+". We've wasted so much time that the inheritance rights of Sharp's will are long gone and Isla Tesoro has become an English military base. There's nothing I can do anymore to help you with Levasseur."
						link.l1 = "I'm absolutely speechless... We've gone through so much troubles all for nothing. Is there really nothing we can do?";
						link.l1.go = "saga_l2";
					}
					else
					{
						dialog.text = "I've heard all about your heroics! Dannie gave me the briefing. We've made up, by the way. You can't even recognize Nathan. As soon as he saw his 'Centurion', he left behind his grumbling like a bad dream...";
						link.l1 = "Nathan's well again? I'm glad to hear it!";
						link.l1.go = "saga_26";
					}
					break;
				}
				if(pchar.questTemp.Saga == "mine") // рудник взят
				{
					dialog.text = "Here you are, "+pchar.name+"! Now I've got something to tell you.";
					link.l1 = "Hello, Jan. I'm overjoyed! What's the word? I hope, something positive?";
					link.l1.go = "saga_32";
					break;
				}
				if(pchar.questTemp.Saga == "mine_1") // рудник взят совместно
				{
					dialog.text = "Here you are, "+pchar.name+"! Got some rest? And, may I conclude, you are once again ready for great adventures?";
					link.l1 = "Hello, Jan. Yes, I'm ready.";
					link.l1.go = "saga_32a";
					break;
				}
				if(pchar.questTemp.Saga == "late_l3") // провал по времени у адвоката
				{
					dialog.text = "What's the news, "+pchar.name+"? How are things?";
					link.l1 = "Oh. Things are absolutely awful.  I've fought tooth and nail, but still ended up losing. As you remember, Sharp's will had a time limit on it. Well, that time has run out and Isla Tesoro is now an English military base. It's a lost cause, Jan.";
					link.l1.go = "saga_l3";
					break;
				}
				if(pchar.questTemp.Saga == "bakaut") // пришёл от адвоката за деньгами
				{
					dialog.text = "Greetings, "+pchar.name+"! Good news: the Council meeting has been held and the Brethren of the Coast has found a new head.";
					link.l1 = "Good afternoon, Jan. I'm happy for you.";
					link.l1.go = "saga_44";
					break;
				}
				if(pchar.questTemp.Saga == "sellbakaut" && GetSquadronGoods(pchar, GOOD_SANDAL) >= 1) // отдает бакаут
				{
					dialog.text = "Well, "+pchar.name+"? Did you catch up with Molligan?";
					link.l1 = "I did. He was the one who stole your ironwood.";
					link.l1.go = "saga_55";
					break;
				}
				if(CheckAttribute(npchar, "quest.bakaut") && GetNpcQuestPastDayParam(npchar, "bakaut_date") >= 1) // за деньгами за бакаут
				{
					dialog.text = "On time as always, "+pchar.name+". I sold the ironwood you brought me.";
					link.l1 = "Excellent. How much money did you earn?";
					link.l1.go = "saga_57";
					break;
				}
				if(CheckAttribute(npchar, "quest.bakaut_sum")) // сам продал бакаут
				{
					dialog.text = "Well, "+pchar.name+"? Did you catch up with Molligan?";
					link.l1 = "I did. He was the one who stole your ironwood. I happened to come upon his buyer as well. He was some Dutch military commander. I sold the product to him.";
					link.l1.go = "saga_59";
					link.l2 = "I did. I tried to force him to show me his cargo hold... we got into a skirmish and...there's no more Molligan now. But there's nothing you can see in the hold except for ebony and mahogany.";
					link.l2.go = "saga_59_1";
					break;
				}
				if(CheckAttribute(npchar, "quest.jessika")) // информация о Джессике
				{
					dialog.text = TimeGreeting()+", "+pchar.name+". What's new?";
					link.l1 = "Jan, I would like to talk to you on one matter. I've been digging into Helen mother's, Beatrice, past and happened to stumble upon someone you know quite well. As far as I've been told...";
					link.l1.go = "saga_62";
					break;
				}
				if(pchar.questTemp.Saga == "lastpages") 
				{
					dialog.text = TimeGreeting()+", "+pchar.name+". How are things coming along? Judging by your face, I can congratulate you? ";
					link.l1 = "Yes. I've finally managed to sort this mess out. Helen has received all the rights to Isla Tesoro. Never again will anyone encroach upon the shelter of the Brethren of the Coast!";
					link.l1.go = "saga_82";
					break;
				}
				if (pchar.questTemp.Saga == "end") sTemp = "Oh, my friend "+pchar.name+"! Pleased to see you! What brings you here?";
				else sTemp = "Anything else, "+pchar.name+"?";
				dialog.text = sTemp;
				link.l1 = "No, Jan. Nothing at the moment.";
				link.l1.go = "exit";
				if(CheckAttribute(npchar, "quest.trade_bakaut")) // торговля бакаутом
				{
					if (GetDataDay() == 14 || GetDataDay() == 28)
					{
						link.l2 = "Jan, I'd like to buy some of your ironwood.";
						link.l2.go = "trade_bakaut";
					}
				}
				NextDiag.TempNode = "First time";
			}
			else
			{
				// заглушка Элен
				if(startHeroType == 4)
				{
					dialog.text = "Helen, hello, my dear. What news do you have? Was there something you wanted?";
					link.l1 = "Hello, Jan! All the same, just stopped by to see you.";
					link.l1.go = "exit";
					NextDiag.TempNode = "First time";
					break;
				}
				dialog.text = "Can I help you with anything?";
				link.l1 = "No, I'm fine.";
				link.l1.go = "exit";
				NextDiag.TempNode = "First time";
			}
		break;
		
		case "saga":
			dialog.text = "I know you, god-damn it! You're the brave captain that saved Rumba and took the cannons of the English corvette head on! Such a joy to see you! Helen is like a daughter to me. From today onward, I am forever indebted to you. You can just call me Jan or Svenson if you like. What can I do for you?";
			link.l1 = "I need to eliminate Levasseur, the governor of Tortuga. I know that getting to him on his island won't be an easy task, so I came to you for advice.";
			link.l1.go = "saga_1";
		break;
		
		case "saga_1":
			dialog.text = "Gracious me, where were you a couple of years ago! I was planning to pull off the same escapade myself. He ruined the whole game for us with the French. But everything was different in those days. Blaze was alive, Shark had some authority, and Nathan was calling all the shots in Maroon Town... Now everything's changed and, God knows, not for the better. Do you know anything about us, about the Brethren?";
			link.l1 = "I've recently arrived here, so I know basically nothing. Besides the fact that you and Jackman are part of the Council.";
			link.l1.go = "saga_2";
		break;
		
		case "saga_2":
			dialog.text = "Oh, I can't stand that Jackman! When he got here was when all our troubles began. I'll contemplate your request. Right off the bat nothing comes to mind.";
			link.l1 = "I've got something interesting regarding Jackman.";
			link.l1.go = "saga_3";
		break;
		
		case "saga_3":
			dialog.text = "Hm. What's that?";
			link.l1 = "Jackman is searching for Gladys Chandler and her daughter. After talking to Higgins, I've started to think that he's looking for Rumba. It seems that Gladys isn't Helen's biological mother and her last name was Chandler before she married Sean McArthur.";
			link.l1.go = "saga_4";
		break;
		
		case "saga_4":
			dialog.text = "God-damn it! That's bad news. Jackman is stronger than ever now. On top of that, I've got a bad feeling he's not working alone. He's got quite an ominous shadow behind his back. If he really needs Helen, then the girl is in dire need of a protector. I'm afraid I'm a little too old to do that myself...";
			link.l1 = "That's not all. Jackman is also looking for someone named Henry the Hangman, former boatswain of the 'Neptune', from captain Butcher's crew.";
			link.l1.go = "saga_5";
		break;
		
		case "saga_5":
			dialog.text = "Caramba! My worst suspicions have come true! This Butcher and his 'Neptune' used to keep the whole archipelago frightened. There were no Brethren back then, everyone was on their own. That man did a lot of bad things, a person dear to me died because of him.\nI have never had the chance to meet him. The 'Neptune' was sunk by an English frigate, and Butcher was executed in St. John's. Good riddance! Though there were a lot of people who admired his luck and reckless bravery.\nJackman himself was his right hand and first mate on the 'Neptune'. Surprised? The ex-criminals have become heroes of the Nation, all thanks to Cromwell! Where did good old England go?\nWe must find Henry the Hangman before Jackman's men will. Perhaps, he holds the key to this mystery, if he's still alive.";
			link.l1 = "I bet you'd have an easier time finding a needle in a haystack. Have you got any leads at least?";
			link.l1.go = "saga_6";
		break;
		
		case "saga_6":
			dialog.text = "I knew Henry when he was a kid. The son of a whore from Cartagena, half Spanish, though he always kept it a secret. His mother was hot! Can't say she was pretty, but there were very few flamenco dancers like her. The whole brothel watched shows of naked Chica Gonzales and her castanets.\nPoor girl. Caught a bad disease and died like a candle. That was when I persuaded Henry to go to Providence where he quickly made a name for himself and joined the crew of Thomas Beltrope, a close friend of Nicolas Sharp. Those two were the last dogs of queen Elizabeth and always worked together. Good times!\nThomas sailed back to England when his partner died. He took his crew with him, but Henry stayed in the Caribbean. Sailed under different captains until Butcher showed up. By the way, he got his nickname because of a cutlass he always kept close by.";
			link.l1 = "And what does this information tell us?";
			link.l1.go = "saga_7";
		break;
		
		case "saga_7":
			dialog.text = "If Hangman has decided to hide from the pirates, the best place for him would be in a Spanish city. Especially at his home in Cartagena, where he has got friends and relatives. Henry was fairly religious. So, it's unlikely that he would be going to a different saint church. He has probably still got the same name that he has had since he was a kid, Enrique.";
			link.l1 = "Yeah... The pickens are slim, but at least it's better than nothing.";
			link.l1.go = "saga_8";
		break;
		
		case "saga_8":
			dialog.text = "Try to find him, Charles! Few know about Henry's Spanish roots, so we have a small advantage here. I'll think how to persuade Rumba to join your crew. The girl has balls, never served under anyone's command except her father's.\nBut she has neither ship nor crew, and she needs to make a living. Sure, I will continue helping Gladys, as I always did, but I won't be able to keep Helen in Blueweld for long. And you will find such an officer very useful. Sean taught her everything he knew and raised her like a boy.\nI'd feel better if she were under the command of such a captain like you.";
			link.l1 = "Rumba has proven herself quite worthy. I need more people like her in my crew. So, if you manage to talk her into it, I'll make her an officer. But first I want to understand who she really is and why Jackman needs her. I am afraid that, unlike Donovan, he is not interested in her charms. So I'll try to find Hangman, although I can't promise anything.";
			link.l1.go = "saga_9";
		break;
		
		case "saga_9":
			dialog.text = "Well, splendid. Take this license of the Dutch West India Company for three months. Write your name there, it very well might come in handy in your searches. In the meantime, I'll think about what you have said concerning Levasseur and Tortuga.";
			link.l1 = "Thanks a million! This paper is going to come in handy for me. In that case, I'm off to Cartagena then.";
			link.l1.go = "saga_10";
		break;
		
		case "saga_10":
			DialogExit();
			GiveNationLicence(HOLLAND, 90);
			AddQuestRecord("Saga", "14");
			pchar.questTemp.Saga = "cartahena";//идем в Картахену
			pchar.quest.Saga_Gonsales.win_condition.l1 = "location";
			pchar.quest.Saga_Gonsales.win_condition.l1.location = "Cartahena_town";
			pchar.quest.Saga_Gonsales.function = "Saga_CreateGonsalesB";
			LocatorReloadEnterDisable("SantaCatalina_houseSp3", "reload2", false);//открыть спальню Элен
			LocatorReloadEnterDisable("FortOrange_town", "reload6", true); // закрыть резиденцию Джекмана
			npchar.greeting = "svenson_3";
			
			AddQuestRecord("HelenDrinking", "1");
			pchar.questTemp.HelenDrinking.CanDrink = true;
			SetFunctionTimerConditionParam("HelenDrinking_NoVisit", 0, 0, 1, 24 - GetHour(), false);
			
			pchar.questTemp.Saga.HelenRelation = 0;
		break;
		
		case "saga_11":
			dialog.text = "Henry's dead?  Wait, did you kill him?";
			link.l1 = "Don't look at me with those wide eyes! I had nothing to do with it. He died by his own, of his rotting conscience and his fear of Jackman. The old pirate had problems with his heart and he didn't have very long to live. Here's what I managed to find out...";
			link.l1.go = "saga_12";
		break;
		
		case "saga_12":
			dialog.text = "Please, tell!";
			link.l1 = "Twenty years ago Henry was supposed to hand over a chest of gold on behalf of Captain Butcher to his biological daughter's foster mother. There's absolutely no doubt that this foster mother was Mrs. McArthur. At that time she bore the surname Chandler and lived in Belize. But circumstances held Hangman up in St. John's for a whole additional month and when he finally arrived at Belize, it was in ruins after being raided by the Spanish, and aunt Gladys and Sean had already hit the road under your wing.";
			link.l1.go = "saga_13";
		break;
		
		case "saga_13":
			dialog.text = "";
			link.l1 = "They passed off Helen as their biological daughter and raised her as their own. Henry lost track of them and laid low, being aware of Jackman's revenge and living the whole twenty years since then in fear. It turns out that Jackman is looking for his captain's daughter. But why, I don't know.";
			link.l1.go = "saga_14";
		break;
		
		case "saga_14":
			dialog.text = "Maybe he's carrying out someone's orders...";
			link.l1 = "Doubt it. Who could give him orders? Butcher is dead. His death is confirmed by official documents. Dozens, if not hundreds of people witnessed him dying.";
			link.l1.go = "saga_15";
		break;
		
		case "saga_15":
			dialog.text = "Maybe this is not about who Helen's father is. Maybe this is all about her biological mother. I can already guess who she was, but I'm afraid to acknowledge it. But Gladys! How could she keep this a secret for so many years without even revealing it to her husband! Sean McArthur surely would've told me about it. We've never had any secrets that we didn't tell each other.";
			link.l1 = "I'm going to have a heart-to-heart talk with Gladys. I think I've got the means to make her talk. Until next time, Jan!";
			link.l1.go = "saga_16";
		break;
		
		case "saga_16":
			DialogExit();
			pchar.questTemp.Saga = "gladis1";
			sld = characterFromId("Gladis");
			sld.dialog.currentnode = "Gladis_history";
			AddQuestRecord("Saga", "21");
		break;
		
		case "saga_17":
			dialog.text = "Where did you get that!?";
			link.l1 = "Gladys gave it to me. She said it was the 'inheritance of Helen's mother'. She doesn't know her name. Something tells me this is not some average piece of scrap paper.";
			link.l1.go = "saga_18";
		break;
		
		case "saga_18":
			dialog.text = "Remember when I told you that I had a hunch on who Helen's real mother was? Now I'm sure of it. Her name was Beatrice Sharp. She was the biological daughter of my teacher and friend Nicholas Sharp, the declared sister of the founder of our Brethren, Blaze Sharp, and part owner of Isla Tesoro. It's this map piece that Jackman is after.";
			link.l1 = "Well, how about that! But why would he need half of an island map?";
			link.l1.go = "saga_19";
		break;
		
		case "saga_19":
			dialog.text = "The island was discovered by Nicolas Sharp. He named it Isla Tesoro, mapped it and took its possession through the Providence Island Company where he had good connections.\nNicolas wrote in his testimony that the island can be inherited only by those who produce two parts of the map. He did it in order to avoid any discords. He gave the parts to Beatrice and his stepson Blaze before he tragically died by Spanish hand.";
			link.l1 = "Well, damn me! How odd.";
			link.l1.go = "saga_20";
		break;
		
		case "saga_20":
			dialog.text = "You are right. It wasn't the best idea. And a sly notary added that the island will belong to the English crown if no one produces both parts of the map within a year after the deaths of the heirs.\nNo one saw it coming back then. And now we are paying the price for our stupidity. Beatrice died twenty years ago. All these years have passed and we still haven't got any idea where her grave together with her part of the map are. Blaze Sharp was murdered not long ago. His part has also disappeared.\nIf no one produces the whole map of Isla Tesoro to the authorities within a year, then Sharptown will be claimed by England. They will send a governor with a garrison there and the Brethren will be finished.";
			link.l1 = "What do you suggest we do?";
			link.l1.go = "saga_21";
		break;
		
		case "saga_21":
			dialog.text = "We can't let this happen. I need you, Charles, I need you to prevent such a course of actions. And I will be able to help you with eliminating Levasseur only after we seize control over Isla Tesoro and elect Shark Dodson as the new leader of the Brethren. He is the most worthy of us. I offer you an alliance.\nAnd, by the way, I have spoken to Helen. She agreed to join your crew.";
			link.l1 = "You leave me no choice, Jan. I can't return back to France without restoring honor to my family. And in order to do that I need to take out Levasseur with or without your help. Unnecessary deaths are not what I want and I hope you can figure out how to take Tortuga without spilling too much blood. Although, I must admit that I'd like to make sense of the hazy past surrounding Sharps' inheritance myself.";
			link.l1.go = "saga_22";
		break;
		
		case "saga_22":
			dialog.text = "It's nice to hear sound thoughts! We'll figure out the right way to take Tortuga. That I promise you. So, let's go?";
			link.l1 = "Let's go! I'll drop in again a bit later. For now, think about where to start with tackling the issue.";
			link.l1.go = "saga_23";
		break;
		
		case "saga_23":
			dialog.text = "Drop in again in two or three days. By then I think my plan will have come to culmination. And don't forget taking Helen on your ship with you. The poor girl is just pining away without the sea. She'll be a loyal assistant and you won't have to think twice about relying on her.";
			link.l1 = "All right, Jan. I'll go get her right now.";
			link.l1.go = "saga_24";
		break;
		
		case "saga_24":
			DialogExit();
			pchar.questTemp.Saga = "helena1";
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", true);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", true);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", true);//закрыть выходы из города
			LocatorReloadEnterDisable("SantaCatalina_houseSp3", "reload2", true);//закрыть спальню Элен
			AddQuestRecord("Saga", "23");
		break;
		
		case "saga_25":
			dialog.text = "First, you need to find the Shark. He wanted to get rid of Levasseur himself and I assure you that he has some bright ideas. Of course we could also persuade Marcus to accept the leadership. He is the keeper of the Codex, after all. But I doubt that he would be of any help, he has intentionally limited any contact with Levasseur and Tortuga. A man of principals.\nI have no idea where Steven and his men hide, but his frigate 'Fortune' was seen at Puerto Principe. Perhaps Zachary Marlow, also known as the Black Pastor, can point us to where to look for the Shark. Second, we have to gain the support of the other barons to elect Dodson. And in order to do that, we need to collect their Indian shards - the votes. The new leader must have all five of them. That is what the Code tells us to do in the case that the previous leader has died.\nRidiculous! It is time to change the laws, but only the new leader can do that. We already have my vote. I believe that the Black Pastor doesn't give a damn about whose ass is planted in Sharptown. I hope that Jackman didn't talk to him first. We also have to persuade both Tyrex and Jacques Barbazon, who hate each other. But it is all irrelevant until we find out what has happened with the Shark. Third, one day we will have to kill Jackman and replace him with someone else. He won't negotiate with us.\nToo bad that Hawk is dead! People trusted him and we could use his word. We won't find a better baron for Maroon Town. It is possible that Jackman has something to do with Blaze's murder, so he is also the clue to finding the second part of the map. Jacob trusts no one and most likely keeps the part of the map in his cabin on the 'Centurion'.\nHawks family used to own the frigate, but Jackman claimed it just like Hawk's barony. If we find the second part of the map in Jackman's possession, it would be a great argument for Steven's election. Especially for Marcus Tyrex, the Code keeper, and his over scrupulousness in terms of honor. We will return back to Helen her rights over Isla Tesoro as soon as we acquire both parts of the map.\nWe must be careful though, Jackman won't stay idle and just watch you searching.";
			link.l1 = "Well... I'm about to pay the Black Pastor a visit. Tell me about him.";
			link.l1.go = "shark_hunt";
			pchar.questTemp.Saga = "baronsquests_1";
		break;
		
		case "shark_hunt":
			dialog.text = "Hell if I know what's on his mind. Sometimes he looks like a complete freak, but nevertheless, I believe this is just smart acting. Besides, his men are ready to fight the devil himself in honor of their beloved Pastor.\nThey have established some sort of protestant sect close to the Spanish inquisition on Cuba. So don't even start talking about theological matters there, they won't approve of them.";
			link.l1 = "I'll take that into account...";
			link.l1.go = "shark_hunt_0";
		break;
		
		case "shark_hunt_0":
			dialog.text = "And, "+pchar.name+": don't waste a minute of your time. I mean it. Remember the subscript in the will that says that if the heirs don't claim the island within the period of one year, then Isla Tesoro will go to the English crown, right? Well, time isn't on our side right now. When you and I saw each other last time, there were only around eleven months left until the time will be up.";
			link.l1 = "I remember, Jan.  You're right, time is money. I am on it!";
			link.l1.go = "shark_hunt_1";
		break;
		
		case "shark_hunt_1":
			DialogExit();
			AddQuestRecord("SharkHunt", "1");
			pchar.questTemp.Saga.SharkHunt = "begin";
			pchar.GenQuest.LigaAttack = "true"; // киллеры Лиги активированы
		break;
		
		case "shark_hunt_2":
			dialog.text = "Hm... What did Zachary tell you?";
			link.l1 = "Prior to his disappearance, Shark came to visit him and left his frigate with Zachary as collateral for a brig with some food, and then sailed off somewhere northwest to Cuba.";
			link.l1.go = "shark_hunt_3";
		break;
		
		case "shark_hunt_3":
			dialog.text = "That really is fishy. Go on.";
			link.l1 = "One month later Dodson did not return and the Pastor, according to the terms of the agreement, took the frigate for himself and sold it for a good price to some guy named Paterson. As far as our affairs go, Zachary mentioned that Shark might have taken off to some legendary Justice Island, supposedly located somewhere not far away to the Northwest of Cuba.";
			link.l1.go = "shark_hunt_4";
		break;
		
		case "shark_hunt_4":
			dialog.text = "I have heard about Justice Island. They say that there is an island where white and black live peaceful lives, together as equals. Bullshit spread by all sorts of dreamers. But there is a possibility that some sort of smuggler base exists to the North-West. Their barques used to be seen in the open sea on a regular basis ten years ago. They brought different kinds of goods to Cuba in exchange for food.";
			link.l1 = "Treasures for food? The Pastor has also told me about the beef-shipping buccaneers. It's pretty much a walking contradiction.";
			link.l1.go = "shark_hunt_5";
		break;
		
		case "shark_hunt_5":
			dialog.text = "These gossips must have a source, those smugglers' or buccaneers' barques were sailing to that region for some reason. I remember the Shark told me stories about his youth, he was some sort of a slave at some odd formation made of ship wrecks in the middle of the sea.\nPerhaps that is our place? No clue. Anyway, the Pastor has a point, something is out there, either a secret base or an island where Shark could have gone to. Listen, sail to Santo Domingo and find a scientist named Jose Dios.\nHe is a Spanish cartographer. I once saved him from dirty scum, I respect educated people. He will help you, just tell him my name. Go to Hispaniola, find Dios and talk to him.\nHe knows our region's geography perfectly and if he won't be able to help you - no one will.";
			link.l1 = "All right, Jan. Sounds like a plan. Off I go!";
			link.l1.go = "shark_hunt_6";
		break;
		
		case "shark_hunt_6":
			DialogExit();
			pchar.questTemp.Saga.SharkHunt = "dios";
			AddQuestRecord("SharkHunt", "3");
		break;
		
		case "shark_hunt_7":
			dialog.text = "That's too bad. I did hope Jose would lend us a hand.";
			link.l1 = "I was counting on that too, but alas. Well, let's not wallow in our pity. I'll spend some more time contemplating this matter. Yes, Jan, tell me, how did Hawk die?";
			link.l1.go = "baron_return";
		break;
		
		case "baron_return":
			dialog.text = "Nobody witnessed his death, just like no one has seen his body. He simply disappeared several months ago. Since then, it's been the same as with Shark, neither hide nor hair. But unlike Steven, Nathan didn't have a reason to hide out. It's for that reason that everyone figured that he had passed away in the selva. If it wasn't for that, then they wouldn't have agreed to elect Jackman in his place.";
			link.l1 = "What the hell was Hawk doing in the selva?";
			link.l1.go = "baron_return_1";
		break;
		
		case "baron_return_1":
			dialog.text = "It was my fault, I am an old fool! I had persuaded him into taking care of the newly arrived bandits. I have no idea who they are and who their boss is. Normally I wouldn't care, but they started kidnapping friendly Miskitos. Their war chief Kumvana threatened to declare the War Path and asked for my help. I had no option, but to interfere.\nHawk landed with a small unit on Mosquito Coast, became trapped by an excellently organized ambush and was then defeated. It looked like he and his men were expected to land there. Hawk's corpse wasn't found among the others in the jungles.";
			link.l1 = "You've got all kinds of shenanigans happening under your nose! Didn't any of Hawk's guys try to handle the bandits?";
			link.l1.go = "baron_return_2";
		break;
		
		case "baron_return_2":
			dialog.text = "Jackman beat everyone to the punch. He called himself out to solve the issue at the Brethren's council and made the decision. Miskitos stopped going missing, but the bandits stayed there, laying relatively low.\nJackman said that they weren't keeping anyone hostage of those who came to attack them and there was no reason for the Brethren to declare war on them. Hawk attacked them first, so according to our laws, the bandits were entitled to protect themselves. Everyone agreed. Everyone but...";
			link.l1 = "Everyone but who?";
			link.l1.go = "baron_return_3";
		break;
		
		case "baron_return_3":
			dialog.text = "Nathan had a wife. Her name is Danielle Hawk and she's a tough bitch! I doubt she ever got over losing her captain, not to mention the fact that she suspected something from the very beginning and tried to discourage Hawk. I remember they had a huge dispute about it, but that was nothing out of the ordinary for them.";
			link.l1 = "And where's Danielle now?";
			link.l1.go = "baron_return_4";
		break;
		
		case "baron_return_4":
			dialog.text = "Who knows! Jackman made sure she left Maroon Town. She doesn't pay me visits. We never liked each other, she has become even more bitchy over the years, and now she must really hate me, because she probably believes that I am the reason for her misfortunes.\nPerhaps she is looking for Hawk on her own but what can one woman do, even if she wears pants and a saber! By the way, she has mastered the saber. I don't recommend testing her if you meet her. Yes, and there is no point in talking to the bandits either. They have set up a very impressive camp there and are armed to the teeth.\nLooks like they are ex-military and know their business well. They don't allow anyone on their territory. They say that the Spanish used to mine gold there. But the gold was depleted and they abandoned the mine. I have no clue what those bastards are doing there.";
			link.l1 = "Well, since nobody has seen Hawk's corpse, the hope of finding him alive goes on. God knows, we could even return him back into baronage.";
			link.l1.go = "baron_return_5";
		break;
		
		case "baron_return_5":
			dialog.text = "Yeah, how about that. Here, take this letter. When you meet Steve Dodson, give it to him right away. The contents of this letter will guarantee your safety. Well, just in case.";
			link.l1 = "Thanks, Jan. I'll make sure to do that!";
			link.l1.go = "baron_return_6";
		break;
		
		case "baron_return_6":
			DialogExit();
			GiveItem2Character(pchar, "letter_svenson");
			AddQuestRecord("BaronReturn", "1");
			pchar.questTemp.Saga.BaronReturn = "begin";
			pchar.quest.Saga_DannyMeeting.win_condition.l1 = "location";
			pchar.quest.Saga_DannyMeeting.win_condition.l1.location = "SantaCatalina_town";
			pchar.quest.Saga_DannyMeeting.function = "Saga_DannyMeeting";
		break;
		
		case "return_LSC":
			dialog.text = "Well, why the long face. You tired? Maybe a glass of rum for you?";
			link.l1 = "I wouldn't mind...";
			link.l1.go = "return_LSC_1";
		break;
		
		case "return_LSC_1":
			LAi_AlcoholSetDrunk(pchar, 51, 5600);
			dialog.text = "Here, have a glass. Now speak.";
			link.l1 = "(drinking) Ah, that's much better... Well, Jan, you and the Black Pastor were both right. Justice Island does exist. I was there.";
			link.l1.go = "return_LSC_2";
		break;
		
		case "return_LSC_2":
			dialog.text = "I told you there was supposed to be a smuggling base over there!";
			link.l1 = "There's actually no base of any kind. And the rumors around the Caribbean didn't lie. Blacks and whites really are living together over there, surely not necessarily in peace, but more like cats and dogs. And the island itself consists of an innumerable multitude of shipwrecks.";
			link.l1.go = "return_LSC_3";
		break;
		
		case "return_LSC_3":
			dialog.text = "I can't believe it! Jose Dios will be very interested in hearing your story, I'm sure of it. Pay him a visit one day, by the way.";
			link.l1 = "I'll pay him a visit later. It's not the best time for that right now. I've got more pressing matters to take care of at the moment. I have found Nathaniel Hawk on the Island.";
			link.l1.go = "return_LSC_4";
		break;
		
		case "return_LSC_4":
			dialog.text = "You've found Nathan? That's remarkable! How is he?";
			link.l1 = "Well... He's sick, constantly drunk, and deeply depressed.";
			link.l1.go = "return_LSC_5";
		break;
		
		case "return_LSC_5":
			dialog.text = "God-damn it, that's disheartening. Where is he? On your ship?";
			link.l1 = "No, he's on his own ship. On the Island.";
			link.l1.go = "return_LSC_6";
		break;
		
		case "return_LSC_6":
			dialog.text = "What, you didn't bring him here? Why?";
			link.l1 = "Because there was nothing to take him on. I made my way to the Island without a ship.";
			link.l1.go = "return_LSC_7";
		break;
		
		case "return_LSC_7":
			dialog.text = "God-damn it, "+pchar.name+", you've barely drunk a glass of rum and you're talking gibberish as if you had drunk yourself into oblivion. What, did you swim across the Caribbean? Or did you strap some turtles to your feet?";
			link.l1 = "No, I didn't swim. Jan, I made it onto the Island directly out of the jungle of Main, just like Nathan did, through a magic Indian idol. I've already told this story to so many people and I'm tired of proving I haven't gone mad, so all I have to say is: just believe me, fine!?";
			link.l1.go = "return_LSC_8";
		break;
		
		case "return_LSC_8":
			dialog.text = "Indian idol?";
			link.l1 = "There are at least three idols in the Caribbean known as the Kukulcan statues: one near the Miskito village of West Main, one at the bottom of the shallow waters of Justice Island, and another one at the Carib village of Dominica. These idols, with the help of Indian magic, are capable of instantaneously transferring human beings through time and space.";
			link.l1.go = "return_LSC_9";
		break;
		
		case "return_LSC_9":
			dialog.text = "";
			link.l1 = "I passed through all three statues in a circle and got out right where I started my journey in the Miskito village. If you don't believe me, I can call over Danielle. She's seen everything with her own eyes!";
			link.l1.go = "return_LSC_10";
		break;
		
		case "return_LSC_10":
			dialog.text = "Danielle? Hawk's wife? She was with you?";
			link.l1 = "In part, yes. She found me herself in Blueweld and brought me to the Miskito village, to a shaman who sent me to the magic statue. Now she's serving as one of my officers, temporarily of course.";
			link.l1.go = "return_LSC_11";
		break;
		
		case "return_LSC_11":
			dialog.text = "I am absolutely flabbergasted, "+pchar.name+"! It's just like the English say. You were fed with a silver spoon. You're one lucky son of a bitch! Fine, I'll just believe you, although it's hard to. But the matter with Nathan stays the same, he needs to be helped out.";
			link.l1 = "That's what I'm going to do. I'm preparing an expedition to Justice Island. Now I have everything I need: the island's coordinates and sailing directions.";
			link.l1.go = "return_LSC_12";
		break;
		
		case "return_LSC_12":
			dialog.text = "Fantastic. Can I do anything to help you?";
			link.l1 = "No, thanks. But I left out one small detail. Besides Nathan, I also found Shark Dodson on the island.";
			link.l1.go = "return_LSC_13";
		break;
		
		case "return_LSC_13":
			dialog.text = "So, he has really gone there! Well, "+pchar.name+", you've done an excellent job. How's Dodson doing over there? You've spoken with him of course, haven't you?";
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie"))
			{
				link.l1 = "I not only talked with him. We've become friends too. It was him who gave me the sailing directions that I'll need to make it back to the Island. Steven has agreed to trade the cabin of his warship for Sharptown's residence.";
				link.l1.go = "return_LSC_14";
			}
			else
			{
				link.l1 = "We talked, yes, but in the end it turned out to be useless. Steven was killed while I was staying on the Island, when a conspiracy, organized by his boatswain, Chad Kapper, came into action.";
				link.l1.go = "return_LSC_17";
			}
		break;
		
		case "return_LSC_14":
			dialog.text = "Hah! And how did Shark manage to become captain of a warship?";
			link.l1 = "The ship has been in a never-ending 'calm' for over half a century. He's trapped with his people on the Island. This is why he hasn't shown himself in the Caribbean for such a long time. Anyway, I'll bring him here soon and he'll tell you about his adventures himself.";
			link.l1.go = "return_LSC_15";
		break;
		
		case "return_LSC_15":
			dialog.text = "I can't wait for that! Now things are starting to get better. We've just become more powerful, "+pchar.name+". When are you planning to depart back to the Island?";
			link.l1 = "Right now. I just came in here for a minute to tell you about the news, while Danielle is making preparations for the expedition. She's dying to see her Nathan. And you know what, Jan, she's not that much of a bitch.";
			link.l1.go = "return_LSC_16";
		break;
		
		case "return_LSC_16":
			dialog.text = "Yeah?  Well, maybe I wasn't quite right about her. Fine, "+pchar.name+", I'm not gonna hold you back any longer. Go and may luck be with you! I'll be looking forward to your return.";
			link.l1 = "See ya, Jan.";
			link.l1.go = "return_LSC_19";
		break;
		
		case "return_LSC_17":
			dialog.text = "Chad Kapper? Fuck, I knew that fellow. He killed Steven? That bastard...";
			link.l1 = "Kapper is dead. But we can't bring Steven back, so we have to think about a way to continue organizing our politics.";
			link.l1.go = "return_LSC_18";
		break;
		
		case "return_LSC_18":
			dialog.text = "Hah! That's too bad... What is there to think about? We'll just have to convince Tyrex to head the Brethren. Besides, after Blaze, Tyrex, as the keeper of the Code, is our most respectable figure. But first we need to bring back Hawk to at least get one ace in the hole. When are you departing to the Island?";
			link.l1 = "Right now. I just came in here for a minute to tell you about the news, while Danielle is making preparations for the expedition. She's dying to see her Nathan. And you know what, Jan, she's not that much of a bitch.";
			link.l1.go = "return_LSC_16";
		break;
		
		case "return_LSC_19":
			DialogExit();
			pchar.questTemp.Saga.BaronReturn = "return_LSC";
			// LSC ждёт своего героя!
			i = FindIsland("LostShipsCity");
			Islands[i].visible = true;
			Islands[i].reload_enable = true;
			pchar.quest.return_LSC.win_condition.l1 = "location";
			pchar.quest.return_LSC.win_condition.l1.location = "LostShipsCity";
			pchar.quest.return_LSC.function = "LSC_ReturnCheckShips"; // проверка типов кораблей
			pchar.quest.return_LSC_attack.win_condition.l1 = "location";
			pchar.quest.return_LSC_attack.win_condition.l1.location = "Beliz";
			pchar.quest.return_LSC_attack.function = "LSC_ReturnJackmanAttack"; // атака наймитов Джекмана
			pchar.quest.return_LSC_main.win_condition.l1 = "Ship_location";
			pchar.quest.return_LSC_main.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.return_LSC_main.function = "LSC_ReturnMain"; // основная функция возвращения
		break;
		
		case "nathaniel":
			dialog.text = "How is he? You said that he didn't feel well.";
			link.l1 = "Yes, that exactly right. I'm going to take him with me to get treated in the Miskito village by Snake Eye, the shaman.";
			link.l1.go = "nathaniel_1";
		break;
		
		case "nathaniel_1":
			dialog.text = "Then no time to waste! Hurry, "+pchar.name+"! As soon as you deliver Nathan to your shaman, come right back to me.";
			link.l1 = "All right, Jan. Sounds like a plan.";
			link.l1.go = "exit";
			npchar.quest.shamane = "true";
		break;
		
		case "nathaniel_2":
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) // Акула жив
			{
				if (CheckAttribute(npchar, "quest.shark")) //и на месте
				{
					dialog.text = "Very well. Steven has already stopped by to see me. Now we can finally continue discussing our plans.";
					link.l1 = "I'm all ears, Jan.";
					link.l1.go = "barbazon";
				}
				else
				{
					dialog.text = "That's nice of course, but why hasn't Dodson come by to see me yet? What, have you left him on the island?";
					link.l1 = "Hm... I was in a hurry bringing Nathan to Snake Eye...";
					link.l1.go = "nathaniel_wait";
				}
			}
			else
			{
				dialog.text = "Very well. My heart is crying about Shark. But that's life, so Tyrex will take his place. Well, now we can finally continue discussing our plans.";
				link.l1 = "I'm all ears, Jan.";
				link.l1.go = "barbazon";
			}
		break;
		
		case "nathaniel_wait":
			dialog.text = "... and you forgot to take Shark? I can't believe it, "+pchar.name+"! Deliver Steven to Blueweld now! Do you hear me? Go!";
			link.l1 = "Calm down, Jan. I'll take care of everything.";
			link.l1.go = "exit";
			NextDiag.TempNode = "nathaniel_wait_1";
		break;
		
		case "nathaniel_wait_1":
			if (CheckAttribute(npchar, "quest.shark"))
			{
				dialog.text = "Steven stopped by to see me. Now we can finally continue discussing our plans.";
				link.l1 = "I'm all ears, Jan.";
				link.l1.go = "barbazon";
			}
			else
			{
				dialog.text = "Oh, "+pchar.name+"... It seems to me that you have been drinking too much rum lately. You see, it never ends in a good way. First your hands start shaking, then you start losing your memory, and then you get a black spot...";
				link.l1 = "I understood, Jan. I'm off to get Steven right away!";
				link.l1.go = "exit";
				NextDiag.TempNode = "nathaniel_wait_1";
			}
		break;
		
		case "barbazon":
			dialog.text = "The Black Pastor has been very clear, he is only interested in that theological book. I've sent my men to search for it, perhaps someone will find it. Marcus Tyrex is not an issue, we'll have no problems persuading him. Jackman has left Maroon Town soon after you paid him a visit. He sailed somewhere on the 'Centurion', the Hawks' frigate.\nThere is only Barbazon left - he is also known as Jacques the Kindman. We must find a way to make him cooperate with us. I am not sure how to perform that so far. But one thing is obvious - you should visit him.";
			link.l1 = "Tell me about Barbazon."; // Addon 2016-1 Jason пиратская линейка патч 17/1
			link.l1.go = "barbazon_1";
		break;
		
		case "barbazon_1":
			dialog.text = "Secretive type. Pretending to be poor, yet he is possibly the richest man in the Caribbean. He controls all smuggling operations of the East. If it wasn't for Marcus standing against him, he would rule all smuggling traffic on the Windward Islands. Tyrex is like a bone in his throat.\nThey always quarrel in the council, but Barbazon hasn't got the balls to declare an open war. Perhaps he really once was a pirate of Dunkirk as he claims, but now he reminds me more of an usurer.";
			link.l1 = "How the hell did he get elected as a baron?";
			link.l1.go = "barbazon_2";
		break;
		
		case "barbazon_2":
			dialog.text = "Gold, my friend, rules everything and everywhere, whoever has the gold makes the rules. Besides, Barbazon is really good at coming up with all kinds of profitable and illegal operations. He doesn't take part in them himself, but he always takes a share. So he has constantly got a lot of brave thugs, who are mostly weak in the head, around him. They would all just die of hunger or end up on the scaffold without him.";
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end")
			{
				link.l1 = "He reminds me of Marcus... Jan, thing is... I have no idea how to approach Barbazon. There is a problem you are not aware of.";
				link.l1.go = "barbazon_5";
			}
			else
			{
				link.l1 = "How do I get to Barbazon?";
				link.l1.go = "barbazon_3";
			}
		break;
		
		case "barbazon_3":
			dialog.text = "Simply pretend to be one of those imbeciles that need a tip-off for a fat job. Don't even think of trying to trick him about his share. Beneficent Barbazon doesn't forgive.";
			link.l1 = "That goes without saying. I'm not getting involved with him for my own gain. Anyway, it's time to pay him a visit.";
			link.l1.go = "barbazon_4";
		break;
		
		case "barbazon_4":
			DialogExit();
			AddQuestRecord("BarbTemptation", "1");
			pchar.questTemp.Saga.BarbTemptation = "begin";
			pchar.questTemp.Saga.BaronReturn = "barbazon";
			NextDiag.CurrentNode = "First time";
			// тут вычищаем квестовый мусор от LSC
			if (CheckCharacterItem(pchar, "letter_chad")) RemoveItems(pchar, "letter_chad", 1);
			if (CheckCharacterItem(pchar, "letter_chad_1")) RemoveItems(pchar, "letter_chad_1", 1);
		break;
		
		// Addon 2016-1 Jason пиратская линейка патч 17/1
		case "barbazon_5":
			dialog.text = "Really? Shoot.";
			link.l1 = "Ever heard of Charlie Prince?"; 
			link.l1.go = "barbazon_6";
		break;
		
		case "barbazon_6":
			dialog.text = "Yeah I heard the rumors. This guy used to work for Marcus Tyrex not too long ago. Did quite a lot in very short time, made a name for himself by plundering Cartagena. So?";
			link.l1 = "This guy is me. I am Charlie Prince. I was. See now?"; 
			link.l1.go = "barbazon_7";
		break;
		
		case "barbazon_7":
			dialog.text = "Fuck me! You are Charlie Prince? What a twist! "+pchar.name+", I am impressed! Now I see where your grip originated from... But what has Barbazon got to do with this?";
			link.l1 = "How would it be for Prince to pay Barbazon a visit, Jan?.."; 
			link.l1.go = "barbazon_8";
		break;
		
		case "barbazon_8":
			dialog.text = "Hm... I get this. You had dealings with him before?";
			link.l1 = "Not exactly. One of his grunts by the name of Ignacio Marco tried to fuck me up by direct orders of Barbazon. It was part of their little war."; 
			link.l1.go = "barbazon_9";
		break;
		
		case "barbazon_9":
			dialog.text = "Did he see your face? Did you make introductions to him?";
			link.l1 = "No."; 
			link.l1.go = "barbazon_10";
		break;
		
		case "barbazon_10":
			dialog.text = "Don't see a problem here then. I also heard of the corsair Charlie Prince but I didn`t know he was you before you told me.";
			link.l1 = "You think Barbazon will not see through me?"; 
			link.l1.go = "barbazon_11";
		break;
		
		case "barbazon_11":
			dialog.text = "How could he if he has never seen your face? All he did was giving orders to get rid of one of Marcus' employees.";
			link.l1 = "Hm... You might be right on this."; 
			link.l1.go = "barbazon_12";
		break;
		
		case "barbazon_12":
			dialog.text = "No way we are pulling through this without Barbazon. Go see him but be careful. Run if he recognizes you, we will think of another way to approach him in that case.";
			link.l1 = "Fine. I should be going now. Been looking forward to meet the bastard."; 
			link.l1.go = "barbazon_13";
		break;
		
		case "barbazon_13":
			dialog.text = "Don't play stupid and don't try to fuck Jacques. He never forgives. Act like an idiot who is eager to make easy money.";
			link.l1 = "My favorite role it seems... Farewell, Jan!"; 
			link.l1.go = "barbazon_4";
		break;
		
		case "saga_26":
			dialog.text = "Yes. The Indian shaman gave it all he could, Hawk is as good as new. He's supposed to be in Maroon Town with Dannie already, so if you want, go ahead and say hello. They would be thrilled to see you.";
			link.l1 = "I'll definitely stop by to see how they are doing... Jan, I was able to find the second part of Sharp's map! It was in Jackman's cabin. Now we won't have a problem proving Helen's rights to Isla Tesoro.";
			link.l1.go = "saga_27";
		break;
		
		case "saga_27":
			dialog.text = "Great, show me that.\nWe were right, Jacob was the one who killed Blaze. Now the stain on Shark's name is to be removed for good. As far as proof goes, that's a more delicate issue. And it must be approached only after very thorough contemplation.";
			link.l1 = "Another thing, Jan. Take a look at this note. It was among Jackman's things too.";
			link.l1.go = "saga_28";
		break;
		
		case "saga_28":
			RemoveItems(pchar, "letter_parol", 1); // удалить записку
			dialog.text = "Well, let's have a look... Ha, so this is why the bandits listened to Jackman and ceased abducting Miskitos! It couldn't turn out any other way! That scumbag planned it all and was several steps ahead.";
			link.l1 = "Yeah, and I can see why Hawk's men were slaughtered too. But there are two things I don't understand: first, what are Jackman's accomplices doing in the mine and second, why are you reacting so calmly to the fact that this whole mess is taking place on your territory?";
			link.l1.go = "saga_29";
		break;
		
		case "saga_29":
			dialog.text = "I'm ashamed... You're right. Jackman has really got out of hand. And his henchmen have no business in my domain. Seems like the time has come to remind the Caribbean who they are dealing with.";
			link.l1 = "What have you got in mind, Jan?";
			link.l1.go = "saga_30";
		break;
		
		case "saga_30":
			dialog.text = "Reviving the past... I intend to organize a punitive expedition and eliminate every bandit at the mines. Now we have proof that they are Jackman's men and I am obliged to clear my territories of this scum.\n"+pchar.name+", you've done an excellent job. It's time for me to put my butt in gear. You get some rest for now. Go visit the Hawks. Come back in ten days!";
			link.l1 = "Fine, Jan.  Will do. I'll be back in exactly the time you said!";
			link.l1.go = "saga_31";
			link.l2 = "Ha! I want to take part in this crusade as well. Why is it that you've decided to put me on recreation time?";
			link.l2.go = "saga_31_1";
		break;
		
		case "saga_31_1":
			dialog.text = "Forgive me, old chap. I just thought it might finally be time for me to do some work and for you to have some rest. But if it is your desire, I'd be more than happy! Let's hit the storm together! And everything we find in the mine we'll split equally between our crews, as written in the Brethren's laws.";
			link.l1 = "Deal, Jan! When are we heading off?";
			link.l1.go = "saga_31_2";
		break;
		
		case "saga_31_2":
			dialog.text = "Come with your people to Mosquito Coast in three days. I will have gathered my squad by then and I'll be already, waiting for you. Don't be late!";
			link.l1 = "All right, Forest Devil. I'm just itching to goin into battle with you back to back! See you soon!";
			link.l1.go = "saga_31";
			npchar.quest.mine_tw = "true";
		break;
		
		case "saga_31": 
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto1");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			if (CheckAttribute(npchar, "quest.mine_tw"))
			{
				pchar.quest.Saga_MinePrepareAttack.win_condition.l1 = "location";
				pchar.quest.Saga_MinePrepareAttack.win_condition.l1.location = "Shore53";
				pchar.quest.Saga_MinePrepareAttack.win_condition.l2 = "Timer";
				pchar.quest.Saga_MinePrepareAttack.win_condition.l2.date.hour  = sti(GetTime());
				pchar.quest.Saga_MinePrepareAttack.win_condition.l2.date.day   = GetAddingDataDay(0, 0, 3);
				pchar.quest.Saga_MinePrepareAttack.win_condition.l2.date.month = GetAddingDataMonth(0, 0, 3);
				pchar.quest.Saga_MinePrepareAttack.win_condition.l2.date.year  = GetAddingDataYear(0, 0, 3);
				pchar.quest.Saga_MinePrepareAttack.function = "Saga_MineBanditsPrepareAttack";
				SetFunctionTimerCondition("Saga_MineBanditsAttackOver", 0, 0, 4, false); // таймер
			}
			else SetFunctionTimerCondition("Saga_MineBanditsDestroyed", 0, 0, 10, false); // таймер
			sld = characterFromId("Nathaniel");
			sld.model = "Hawk_2";
			Characters_RefreshModel(sld); // наверно не нужно
			sld.greeting = "nathaniel_2";
			sld.dialog.currentnode = "marun_town";
			ChangeCharacterAddressGroup(sld, "FortOrange_townhall", "sit", "sit1");
			LAi_SetHuberType(sld);
			LocatorReloadEnterDisable("FortOrange_town", "reload6", false); // открыть резиденцию Хоука
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "marun_town";
			sld.greeting = "danny_2";
			ChangeCharacterAddressGroup(sld, "FortOrange_townhall", "goto", "goto1");
			LAi_SetStayType(sld);
		break;
		
		case "saga_32a":
			dialog.text = "Excellent. I ferreted out something about the mysterious owner of the mine, Lawrence Beltrope.";
			link.l1 = "So, who is this bird?";
			link.l1.go = "saga_35";
		break;
		
		case "saga_32":
			dialog.text = "I beat it out Jackman's stooges in the mine. They ended up being tough nuts to crack, but my guys weren't born yesterday either. On top of that, we were able to put down their vigilance after telling them the password from the note you found. We penetrated the mine and we gave them a showy send-off.";
			link.l1 = "You took the mine? Outstanding!";
			link.l1.go = "saga_33";
		break;
		
		case "saga_33":
			dialog.text = "Let that be a lesson for anyone who thinks that the Forest Devil is rusty. I've really loafed around way too much in the past years and look what happened? Jackman was unfurling his evil scheme right under my nose!";
			link.l1 = "What did you see in that mine? Tell me about it!";
			link.l1.go = "saga_34";
		break;
		
		case "saga_34":
			dialog.text = "The mine was abandoned by the Spanish for real, however Lawrence Beltrope from Port Royal bought it for peanuts and secretly continued exploitation. Apparently, the Spanish ditched the shaft too early, since although we didn't find any gold there ourselves, we found several slaves who claimed there was gold to be found until very recently.";
			link.l1 = "Lawrence Beltrope? Never heard of him. Who is he?";
			link.l1.go = "saga_35";
		break;
		
		case "saga_35":
			dialog.text = "He's a local native, the son of Thomas Beltrope, long ago the sworn brother of Nicholas Sharp and the privateer of Providence Island Company. I knew Thomas very well myself. A year ago, Lawrence came to the Caribbean once again. It turns out that Jackman was working for him. Keep that in mind and your eyes peeled!";
			link.l1 = "So Jackman's mysterious 'boss', mentioned in that letter, is Lawrence Beltrope... Alright, I'll remember that name.";
			link.l1.go = "saga_36";
		break;
		
		case "saga_36":
			dialog.text = "One more thing. I recall something odd. Blaze once mentioned some abandoned Spanish gold mine and that he was going to invest its gold into Sharptown. But the map of the mine disappeared after his sister had run away with captain Butcher. Perhaps he was talking about our mine?\nWhatever, it was too long ago and doesn't change much... You and I should deal with the Council. Have you got all five shards?";
			link.l1 = "Yes. These four: Nathaniel, Tyrex, Marlow, and Barbazon. All of them have given their yes.";
			link.l1.go = "saga_37";
		break;
		
		case "saga_37":
			RemoveItems(pchar, "splinter_nh", 1);
			RemoveItems(pchar, "splinter_mt", 1);
			RemoveItems(pchar, "splinter_jb", 1);
			RemoveItems(pchar, "splinter_zm", 1);
			sTemp = "Shark";
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Tyrex";
			dialog.text = "Great. I'm sure there won't be any problems electing "+sTemp+" as head of the Brethren of the Coast. I'll immediately work on calling a Council meeting.";
			link.l1 = "So Jan, we can consider all problems under control for now? Nathaniel is in Maroon Town, Jackman is dead, and the Brethren now has a new head... Maybe it's time to go back to where we started, that is taking Tortuga?";
			link.l1.go = "saga_38";
		break;
		
		case "saga_38":
			dialog.text = "I remember, "+pchar.name+", but we need to bide our time a little. On top of that, the time to sort out Sharp's inheritance is running out and that issue, as you know, seriously needs to be handled.";
			link.l1 = "What's wrong with the inheritance? I've got both parts of the map. All we really have to do is to present them and that's it...";
			link.l1.go = "saga_39";
		break;
		
		case "saga_39":
			dialog.text = ""+pchar.name+", I assure you that they don't just simply give islands to people these days. Even to the lawful heirs with every paragraph of the testimony fulfilled. English authorities want this island badly, I am well aware of that.\nI don't think that colonel Doyle will idly watch us take away the island he already considers English property. Also, you and me should stay in the shadows.";
			link.l1 = "And what do you suggest?";
			link.l1.go = "saga_40";
		break;
		
		case "saga_40":
			dialog.text = "Make your way to Port Royal and find a man named Albert Loxley there. He's the best lawyer in the entire Caribbean. He's become considerably adept in shady matters of all kinds, so he'll take any kind of work if he's offered an exorbitant fee for it. He's got a king-size appetite, but he's worth it.";
			link.l1 = "You think Sharp's will could have some pitfalls in it?";
			link.l1.go = "saga_41";
		break;
		
		case "saga_41":
			dialog.text = "I don't just think so, I am sure of it. Have you ever had to conduct business with officials? Know, that if they want something from you, they will pull out your soul, point your nose on a misplaced comma, interpret everything in the way they need and leave you as naked as a blind kitten.\nThat is why layers were created. They fight the officials with their own weapons - the verbiage, the ink shed and the chicanery. Therefore, you should pay Loxley a visit and hire him to protect our interests while I deal with the elections.";
			link.l1 = "Alright. I'm off to Port Royal. How much time will it take for the Council to meet and hold an election?";
			link.l1.go = "saga_42";
		break;
		
		case "saga_42":
			dialog.text = "Ten days. So don't bother yourself looking for me in Blueweld any earlier.";
			link.l1 = "Got it. Well, Jan. In that case, see you in a while!";
			link.l1.go = "saga_43";
		break;
		
		case "saga_43":
			DialogExit();
			AddQuestRecord("Testament", "1");
			pchar.questTemp.Saga = "loxly"; // обновляем флаг
			LocatorReloadEnterDisable("SantaCatalina_houseS1", "reload2", true); // закрыть кабинет Свенсона
			SetFunctionTimerCondition("Saga_GoldForLoxly", 0, 0, 10, false); // таймер
		break;
		
		case "saga_44":
			sTemp = "Steven Dodson";
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus Tyrex";
			dialog.text = ""+sTemp+" sends his warmest greetings. He will always be glad to see you in his residence on Isla Tesoro. Go visit him, should the opportunity arise.";
			link.l1 = "To make sure "+sTemp+" won't leave his new residence, you and I, Jan, have a little bit of work ahead of us.";
			link.l1.go = "saga_45";
		break;
		
		case "saga_45":
			sTemp = "four hundred and fifty";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) sTemp = "one thousand";
			dialog.text = "I take it you've already visited Loxley...";
			link.l1 = "Yes I have. He's taking our case, but he demanded a heap of gold for his services. "+sTemp+" doubloons in advance. Advance! And we'll also have to pay him even more, depending on how well Helen's proof of rights will go. The sum will double or triple, as he said.";
			link.l1.go = "saga_46";
		break;
		
		case "saga_46":
			dialog.text = "Ha! Well, I didn't assume any less of an old shuffler like him. He smells prey from far away, just like a hyena. Of course, we're talking about a whole island here. It's ridiculous to think that Albert wouldn't ask for a couple hundreds. So, the total amount might be somewhere around one thousand and five hundred gold...";
			link.l1 = "Jan, that's a ton of money!";
			link.l1.go = "saga_47";
		break;
		
		case "saga_47":
			dialog.text = "I know what you're getting at. I agree you're not some dumb gorilla paying that all out of your own pocket. But unfortunately, at the moment I don't have that quantity of gold stashed away. I had planned for such expenses, however the intervention of one blackguard ruined everything.";
			link.l1 = "What are you talking about?";
			link.l1.go = "saga_48";
		break;
		
		case "saga_48":
			dialog.text = "Listen. Perhaps you already know that our settlement is only half legal. The English keep a garrison here and we provide them with mahogany for a good price. But there is a very heavy and durable type of wood - Lignum Vitae, which you should know as ironwood.\nIt's rare and hard to process even with hardened steel. They say that a long time ago the Maya-Itza used to make their dreadful clubs of it. You can't buy ironwood at the open market and smuggled it costs its weight in silver.\nDoyle's men occasionally come and buy the entire quantity, that we have processed, for cheap. But I always manage to save some for my own need.";
			link.l1 = "I've heard about this tree. They say that musket bullets sink into its oily wood like tar! It's stoutness is good enough to make gears for steel mechanisms out of it.";
			link.l1.go = "saga_49";
		break;
		
		case "saga_49":
			dialog.text = "They're fibbing a little about the gears, but the rest is spot on. So, predicting expenses, I prepared a large batch of ironwood, but some bastard cleared out my warehouse a couple days ago. It's someone of us, I know that. I've got a suspicion, but I can't say for sure.";
			link.l1 = "Rats are to be squashed! Who is it that you suspect?";
			link.l1.go = "saga_50";
		break;
		
		case "saga_50":
			dialog.text = "Paul Molligan. His east indian 'Oyster' sailed to Barbados yesterday. I didn't have the chance to check her holds. But he wouldn't bring the ironwood to Bridgetown anyway, lord Willoughby has serious customs officers there and ironwood is a raw material of strategic importance for the English navy.\nIf he really has my ironwood, then he will sell it before arriving at Bridgetown. If only you could intercept Molligan and inspect his holds!..";
			link.l1 = "You say that he took off to Bridgetown yesterday? Not all is yet lost. I'll try to catch up with him.";
			link.l1.go = "saga_51";
		break;
		
		case "saga_51":
			dialog.text = "You know what to do, if Molligan is the rat. But try to learn his client's name first. Then you can either deliver the cargo to the client yourself or return it to me.\nBring the 'Oyster' to Blueweld too, that's a fine ship, I'd like to take her for myself and re-equip her for my own needs. You are allowed to take whatever you want as a prize too... And in case Molligan is not the man to blame... no, I am confident that he is the rat who stole my ironwood.";
			link.l1 = "I'll make good use of my time!";
			link.l1.go = "saga_52";
		break;
		
		case "saga_52":
			dialog.text = "If you sell the ironwood yourself, put aside one thousand five hundred gold doubloons for Loxley and we'll split the rest in half. I can trust you on this, can't I?";
			link.l1 = "Of course. I am not a rat.";
			link.l1.go = "saga_53";
		break;
		
		case "saga_53":
			dialog.text = "I have no doubt. Good luck, "+pchar.name+"! I hope it smiles down on you this time.";
			link.l1 = "Thank you. See you later!";
			link.l1.go = "saga_54";
		break;
		
		case "saga_54":
			DialogExit();
			pchar.questTemp.Saga = "molligan"; // обновляем флаг
			AddQuestRecord("Testament", "3");
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			Saga_CreateMolliganInWorld(); // ставим корабль Моллигана на карту
		break;
		
		case "saga_55":
			npchar.quest.bakaut = GetSquadronGoods(pchar, GOOD_SANDAL);
			dialog.text = "I knew it. How much did he have in his holds?";
			link.l1 = "I have found "+FindRussianQtyString(sti(npchar.quest.bakaut))+" on the 'Oyster'.";
			link.l1.go = "saga_56";
		break;
		
		case "saga_56":
			iTemp = sti(npchar.quest.bakaut);
			if (iTemp > 100)
			{
				dialog.text = "Whoa! I've never had that much in my warehouse. Look who had got his own happy hands on a fortune. Thank you, "+pchar.name+", you never let me down. I'll sell the product right away, we've got a buyer already. I'll have the money for you tomorrow.";
				link.l1 = "All right. I won't distract you any further then. See you tomorrow.";
				link.l1.go = "saga_oust";
				break;
			}
			if (iTemp >= 90 && iTemp < 101)
			{
				dialog.text = "Yeah, I've had just about that much. Little rat! Thank you, "+pchar.name+", you never let me down. I'll sell the product right away, we've got a buyer already. I'll have the money for you tomorrow.";
				link.l1 = "All right. I won't distract you any further then. See you tomorrow.";
				link.l1.go = "saga_oust";
				break;
			}
			if (iTemp >= 70 && iTemp < 90)
			{
				dialog.text = "He has probably already managed to sell a part of the shipment to somebody, because there should have been more. But it's not a big deal, we got most of it back. Thank you, "+pchar.name+", I'll sell the product right away, we've got a buyer already. I'll have the money for you tomorrow.";
				link.l1 = "All right. I won't distract you any further then. See you tomorrow.";
				link.l1.go = "saga_oust";
				break;
			}
			if (iTemp >= 50 && iTemp < 70)
			{
				dialog.text = "God damn it, that bastard was able to sell off a decent share of the shipment already... Ah, that's too bad. Oh well. I'll sell what I have, I have a buyer already. I'll have the money tomorrow.";
				link.l1 = "All right. I won't distract you any further then. See you tomorrow.";
				link.l1.go = "saga_oust";
				break;
			}
			if (iTemp >= 20 && iTemp < 50)
			{
				dialog.text = "God damn it, that's deplorable! That bastard was able to sell off more than half of the shipment already... Ah, that's too bad. Oh well. I'll sell what I have, I've found a buyer already. I'll have the money tomorrow.";
				link.l1 = "All right. I won't distract you any further then. See you tomorrow.";
				link.l1.go = "saga_oust";
				break;
			}
			dialog.text = "Man, I'm just shit out of luck. He has sold almost everything... Here keep this ironwood for yourself, "+pchar.name+", do what you want with it. You're my only hope to make some money now.";
			link.l1 = "Got it. Fine, I'll look myself. This isn't my first rodeo... Bye, Jan.";
			link.l1.go = "saga_oust";
		break;
		
		case "saga_oust":
			if (CheckAttribute(npchar, "quest.bakaut"))
			{
				if (sti(npchar.quest.bakaut) < 20) DeleteAttribute(npchar, "quest.bakaut");
				else 
				{
					SaveCurrentNpcQuestDateParam(npchar, "bakaut_date");
					RemoveCharacterGoods(pchar, GOOD_SANDAL, sti(npchar.quest.bakaut));
				}
				pchar.questTemp.Saga = "removebakaut";
			}
			int iUst = 0;
			for(i = 0; i < COMPANION_MAX; i++)
			{
				iTemp = GetCompanionIndex(PChar, i);
				if(iTemp > 0)
				{
					sld = GetCharacter(iTemp);
					if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_EASTINDIAMAN && sld.ship.name == "Oyster") iUst = 1;
				}
			} // есть ли у нас Устрица
			dialog.text = "Wait! Did you capture the 'Oyster'?";
			if (iUst == 1)
			{
				link.l1 = "Yes. She is in the harbour right now. I anchored her for you, just like you asked.";
				link.l1.go = "saga_oust_yes";
			}
			else
			{	
				link.l1 = "No. The ship was so badly damaged during battle that I had to sink her.";
				link.l1.go = "saga_oust_no";
			}
		break;
		
		case "saga_oust_no":
			dialog.text = "What a pity. But it is what it is. See you later, "+pchar.name+"!";
			link.l1 = "Bye, Jan.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "saga_oust_yes":
			dialog.text = "Remarkable! I'll rig this beauty up the way she deserves. And later you can always borrow her for a while, just like we agreed. I think in about two months time she will be ready.";
			link.l1 = "All right. A ship like this could really come in handy sometimes... See you later, Jan!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Saga_RemoveOuster");
			npchar.quest.ouster = "true";
			SaveCurrentNpcQuestDateParam(npchar, "ouster_date"); // через 2 месяца
			NextDiag.TempNode = "First time";
		break;
		
		case "saga_57":
			int idlt;
			iTemp = sti(npchar.quest.bakaut)*30; // Ян за 1 шт бакаута даёт 30 дублонов
			if (iTemp > 1600)
			{
				idlt = makeint(iTemp-1500)/2; // доля Бонса :)
				dialog.text = "I received "+iTemp+" coins for it. One thousand five hundred is for the lawyer, plus your share of doubloons - "+idlt+". Here you go.";
				link.l1 = "Commendable! Now I can easily take off to Loxley.";
				link.l1.go = "saga_58";
				TakeNItems(pchar, "gold_dublon", 1500+idlt);
				break;
			}
			if (iTemp > 1450 && iTemp <= 1600)
			{
				dialog.text = "I received one thousand five hundred doubloons for it. It's just enough for the lawyer. Here you go.";
				link.l1 = "Fantastic. Now I can take off to Loxley.";
				link.l1.go = "saga_58";
				TakeNItems(pchar, "gold_dublon", 1500);
				break;
			}
			dialog.text = "I received "+iTemp+" doubloons for it. Here you go. You're going to have to dig up the rest by yourself.";
			link.l1 = "Well, if by myself then myself. Alright, I'm on my way to see Loxley.";
			link.l1.go = "saga_58";
			TakeNItems(pchar, "gold_dublon", iTemp);
		break;
		
		case "saga_58":
			DialogExit();
			PlaySound("interface\important_item.wav");
			DeleteAttribute(npchar, "quest.bakaut");
		break;
		
		case "saga_59":
			dialog.text = "How about that? That's interesting. And how much is the Dutch guy willing to pay for it?";
			link.l1 = "Forty doubloons a piece.";
			link.l1.go = "saga_60";
		break;
		
		case "saga_60":
			dialog.text = "Whoa! My buyers pay less...";
			link.l1 = "Overall, I've got two thousand gold for Loxley and "+sti(npchar.quest.bakaut_sum)*2+" doubloons on top of that.";
			link.l1.go = "saga_61";
		break;
		
		case "saga_61":
			dialog.text = "Full well. Then we'll split it down the middle.";
			if (CheckCharacterItem(pchar, "gold_dublon"))
			{
				npchar.quest.bakaut_pay = GetCharacterItem(pchar, "gold_dublon"); // дублоны в кармане
				link.l1 = "Here you go. I've got "+FindRussianQtyString(sti(npchar.quest.bakaut_pay))+".";
				link.l1.go = "bakaut_pay";
			}
			else
			{
				link.l1 = "I left the doubloons on the ship. I'll make a quick run over there and be right back.";
				link.l1.go = "exit";
				NextDiag.TempNode = "bakaut_pay_wait";
			}
		break;
		
		case "saga_61_1":
			dialog.text = "Jolly good. How much did you bring?";
			if (CheckCharacterItem(pchar, "gold_dublon"))
			{
				npchar.quest.bakaut_pay = GetCharacterItem(pchar, "gold_dublon"); // дублоны в кармане
				link.l1 = "Here you go. I've got "+FindRussianQtyString(sti(npchar.quest.bakaut_pay))+".";
				link.l1.go = "bakaut_pay";
			}
			else
			{
				link.l1 = "What's going on with my memory! It's time to stop messing around with this rum. Once again I left the doubloons in my chest. I'll make a quick run over there and bring them.";
				link.l1.go = "exit";
				NextDiag.TempNode = "bakaut_pay_wait";
			}
		break;
		
		case "bakaut_pay": // оплата
			if (sti(npchar.quest.bakaut_sum) < sti(npchar.quest.bakaut_pay)) // полная сумма
			{
				npchar.quest.bakaut_pay = sti(npchar.quest.bakaut_sum);
				iTemp = 0;
			}
			else iTemp = sti(npchar.quest.bakaut_sum)-sti(npchar.quest.bakaut_pay);
			npchar.quest.bakaut_sum = iTemp; // запоминаем остаток
			RemoveItems(pchar, "gold_dublon", sti(npchar.quest.bakaut_pay));
			Log_Info("You have given "+sti(npchar.quest.bakaut_pay)+" doubloons");
			PlaySound("interface\important_item.wav");
			if (iTemp == 0)
			{
				dialog.text = "Good work, "+pchar.name+"! I'm once again reminded that you're a good person to be involved with.";
				link.l1 = "I try, Jan...";
				link.l1.go = "bakaut_done";
			}
			else
			{
				dialog.text = "Great. Will you bring the remaining "+FindRussianQtyString(sti(npchar.quest.bakaut_sum))+" doubloons later?";
				link.l1 = "Yes. I just couldn't haul such a large heap of gold all in one go.";
				link.l1.go = "exit";
				NextDiag.TempNode = "bakaut_pay_wait";
			}
		break;
		
		case "bakaut_pay_wait":
			dialog.text = "So, "+pchar.name+", how are my doubloons doing?";
			link.l1 = "I'm willing to give you some more gold.";
			link.l1.go = "saga_61_1";
		break;
		
		case "bakaut_done": // рассчитались
			dialog.text = "I've got a proposition for you. Since you were able to find a lucrative buyer, then I could sell you some ironwood. I used to get paid thirty doubloons a piece. If you want, you can buy it from me for that price. I'd rather sell it to you than to somebody else.";
			link.l1 = "How much ironwood are you able to sell?";
			link.l1.go = "bakaut_done_1";
		break;
		
		case "bakaut_done_1":
			dialog.text = "I avoid saving up big batches. Molligan's was an exception. The authorities won't like the news of a local black market. So, here is the deal: I will save up 25 pieces of ironwood for you on every 14th and 24th of a month.\nIf you want to buy it, bring seven hundred and fifty doubloons and take the whole batch. If you won't show up during that day, then I will sell it to another customer. So, this way you will be able to have 50 pieces per month. Deal?";
			link.l1 = "You've got yourself a deal, Jan! Let's do that. Now, it's time for me to get going...";
			link.l1.go = "saga_oust";
			DeleteAttribute(npchar, "quest.bakaut_sum");
			npchar.quest.trade_bakaut = "true"; // генератор купли-продажи бакаута
			AddQuestRecordInfo("Unique_Goods", "1");
		break;
		
		case "saga_59_1": // укрысил у Яна - нет генератора на бакаут, потерял больше
			dialog.text = "Ah, so either it wasn't him or he has sold the ironwood already before... What a pity. Well, you're my only hope to get the money for the lawyer now.";
			link.l1 = "I'll be willing to take that responsibility. This isn't my first rodeo.";
			link.l1.go = "exit";
			// Ян расстроен и забыл про Устрицу - так что и Устрицы тоже не будет
			DeleteAttribute(npchar, "quest.bakaut_sum");
		break;
		
		case "saga_62":
			dialog.text = "Is that so? That's interesting. Go ahead, ask. Who do you want to talk about?";
			link.l1 = "About a girl. Her name was... Jessica Rose.";
			link.l1.go = "saga_63";
		break;
		
		case "saga_63":
			dialog.text = "Hm. Did the new head of our Brethren tell you about her?";
			link.l1 = "He did too. But I found out about her from Baker, the old St. John's executioner. The same man that put captain Butcher to death.";
			link.l1.go = "saga_64";
		break;
		
		case "saga_64":
			dialog.text = "Fine. Hm. Well, it's been over twenty years since I saw Jessica for the last time. What do you know about her?";
			link.l1 = "Well, I know how she ended up with captain Butcher and how they pirated together. I know he left her for Beatrice. Later, she avenged him for that with the help of some Joshua Leadbeater, also known as the Mask...";
			link.l1.go = "saga_65";
		break;
		
		case "saga_65":
			dialog.text = "";
			link.l1 = "I also know that you, Jan, forgive my frankness, were interested in Jessica. This is the reason why I came to you. Jessica is an important figure in my searches. It was her who murdered Beatrice Sharp, out of jealousy, as far as I understand.";
			link.l1.go = "saga_66";
		break;
		
		case "saga_66":
			dialog.text = "Well, you know a great deal. Yes, I really had been courting Jess, but it was no surprise, all pirates of Isla Tesoro were separated into two different groups back then: those who wanted to fuck Beatrice and those who wanted Jessica.\nI remember her well... She was beautiful, very beautiful!..";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("Video_Jess");
			NextDiag.TempNode = "saga_66a";
		break;
		
		case "saga_66a":
			dialog.text = "She was special... It's also quite probable that Jess killed Beatrice. After Butcher booted her ass from the 'Neptune', she likely didn't think about anything else, but satisfying her revenge on him and Beatrice. By the way, do you know how Butcher got rid of Jessica?";
			link.l1 = "No. Either he just let her off on Barbados or put her up for ransom.";
			link.l1.go = "saga_67";
		break;
		
		case "saga_67":
			dialog.text = "The second. He demeaned her beyond belief. He just locked her up in the cabin, brought her to Barbados, started negotiating with her father Oliver Rose and actually sold her for a heap of doubloons... after everything she had done for him.";
			link.l1 = "Hm. I thought Butcher protected her honor when pirates seized the 'Neptune' from Joshua Leadbeater...";
			link.l1.go = "saga_68";
		break;
		
		case "saga_68":
			dialog.text = "That's true as well. But she also paid him dearly as a reward. Jessica saved that scum's pathetic life on several occasions, lifting him off the bed of nails that he regularly fixed up for himself for his roistering and fierce temperament. It was actually only thanks to her that he attained the glory of a prosperous pirate.";
			link.l1 = "Yeah, yeah, his 'red talisman'. I heard about that. They say that as soon as Butcher kicked off Jess, his luck did the same to him...";
			link.l1.go = "saga_69";
		break;
		
		case "saga_69":
			dialog.text = "But of course. Without Jessica he had become just another common sea raider, even though a recklessly brave one. But Jessica wasn't there for him, she was the one who helped him plan all his risky operations and he could always count on her blade.\nSure, Beatrice wasn't a good girl either, but she couldn't match Jess, Bea's charms were completely different... She made the mistake of messing with Butcher.";
			link.l1 = "I heard that somewhere already...";
			link.l1.go = "saga_70";
		break;
		
		case "saga_70":
			dialog.text = "All pirates thought so, including Blaze Sharp, her brother. He couldn't stand Butcher... But let's get back to Jessica. I didn't even dare to think of her while she was on the 'Neptune', she would never leave her beloved captain. But when Butcher got rid of her in such a mean way...\nI arrived on Barbados and became friends with her. It wasn't easy for her, she loved the sea and dangerous adventures. That dull colony life was killing her. Besides, she had become a very infamous person in the Caribbean while serving on the 'Neptune' and Bridgetown's folk had reasons to consider her Butcher's partner in crime...";
			link.l1 = "But they couldn't prove shit...";
			link.l1.go = "saga_71";
		break;
		
		case "saga_71":
			dialog.text = "No. But no one wanted to have anything to do with her either. She was considered cursed, despite of her status in Bridgetown. I guess I was the only man who spent more than half an hour with Jessica there.\nI offered her to come with me to the West Main and start a new life there. The life she always wanted - the sea, ships, voyages, adventures. I had already set up a large operation in Blueweld by then and I was able to offer her hundred times more than that scum Butcher. But Jess was very injured. She hadn't forgiven Butcher for his betrayal and how he treated her afterwards. And I believe she still had feelings for him even then... Despite all my efforts, I could not make her forget the past, she was obsessed with thoughts of revenge.";
			link.l1 = "Yes, I don't envy her. Poor girl...";
			link.l1.go = "saga_72";
		break;
		
		case "saga_72":
			dialog.text = "I was feeling the same way about her. And later she started growing fond of ancient Indian cults and rituals. It happened after some Indian mage was captured and brought from the jungles' deeps of Yucatan to the local plantation. Jessica bought him and gave him a house at her plantation.\nShe was spending a great deal of time with the mage. She was saying that it was all because of her historical interest in magic Indian rituals. The Bridgetown people got worried, especially the local pastor. Actually, he was one of the few who was good to Jessica.\nThe priest often talked to her, persuading her to get rid of the mage, threatened her with dangers and the inquisition, but trying to scare Jessica was a pointless exercise. One night some strangers broke into the mage's house and murdered him.\nThe same night two men attacked Jessica in her own bedroom but it didn't turn out well for them - no one in Bridgetown knew how well Jess wielded her flame bladed sword. She literally cut them into slices.";
			link.l1 = "Yeah, sure... that reckless virago!";
			link.l1.go = "saga_73";
		break;
		
		case "saga_73":
			dialog.text = "After that, the whole town became fearful of her. And then the Mask came around. They found each other rather quickly.";
			link.l1 = "According to writings, the Mask is Joshua Leadbeater, the former captain of the 'Neptune'...";
			link.l1.go = "saga_74";
		break;
		
		case "saga_74":
			dialog.text = "I learned about that much later. A week after the Mask's arrival, Jess took her things, said goodbye to me and sailed away on a military frigate into unknown directions. She never returned... just like Beatrice never returned to Isla Tesoro.\nSoon after they hanged Butcher in St.John's, he was delivered there by the Mask himself. But he outlived Butcher only for a day.";
			link.l1 = "Yes... Our Steven Dodson showed class...";
			link.l1.go = "saga_75";
		break;
		
		case "saga_75":
			dialog.text = "Yes, that's what I was told. He avenged Beatrice... And that's how Jessica's story ends, she passed away somewhere on an uninhabited island in a skirmish with Butcher's pirates. Nobody knows where this place is. Butcher is dead and so are Jackman and Hangman.";
			link.l1 = "That's where you're wrong, Jan. Butcher is alive.";
			link.l1.go = "saga_76";
		break;
		
		case "saga_76":
			dialog.text = " What!? It can't be! He was hanged!";
			link.l1 = "Read Raymond Baker's testimony. It's better than any story.";
			link.l1.go = "saga_77";
		break;
		
		case "saga_77":
			PlaySound("interface\important_item.wav");
			dialog.text = "Show me that...(reading) Hm. Incredible! It turns out that his execution was staged!";
			link.l1 = "Slick, huh? That's not all, though. You know Butcher. You just don't know who he is now.";
			link.l1.go = "saga_78";
		break;
		
		case "saga_78":
			dialog.text = "Yeah? And who is he?";
			link.l1 = "Lawrence Beltrope from Port Royal. The owner of the mine, that very mysterious shadow standing behind Jackman. I discovered it through Baker and Baker found out from the Mask.";
			link.l1.go = "saga_79";
		break;
		
		case "saga_79":
			dialog.text = "Holy fuck! So it turns out that he's the one who orchestrated it all? Well, alright... We'll make our way to Butcher too. I'll ponderate on how to get down this bad penny. Although it won't be easy, he's under the sustainable protection of the English authorities.";
			link.l1 = "His time will come, Jan. Soon, he will meet his boatswain and quartermaster. Alright, thanks for the story. It's time for me to go.";
			link.l1.go = "saga_80";
		break;
		
		case "saga_80":
			dialog.text = "Where are you heading right now?";
			link.l1 = "To some island. I believe it's the same place where Jess and Beatrice passed away and where the Mask swooped on Butcher-Beltrope. I need proof that Helen belongs to the Sharp family and I hope to dig it up there.";
			link.l1.go = "saga_81";
		break;
		
		case "saga_81":
			dialog.text = "Alright. So, "+pchar.name+", lots of luck to you. Give me the details when you get back.";
			link.l1 = "Sure thing. See you later, Jan!";
			link.l1.go = "saga_81a";
		break;
		
		case "saga_81a":
			DialogExit();
			LAi_SetHuberType(npchar);
			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = "First time";
			DeleteAttribute(npchar, "quest.jessika");
			npchar.quest.jessika_peace = "true"; // атрибут на мирное разрешение после боя
		break;
		
		case "saga_82":
			dialog.text = "Great job, "+pchar.name+". You accomplished the impossible. All of us barons of the Brethren of the Coast are indebted to you.";
			link.l1 = "Yes, the road to victory was narrow. If only I knew beforehand than I would have to withstand so much...";
			link.l1.go = "saga_83";
		break;
		
		case "saga_83":
			dialog.text = "How is Helen? What is she planning on doing?";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				link.l1 = "She's staying on my ship with me. She's not just an ordinary officer anymore. Control over the island will be given to the leader of the Brethren, and all she will get is rent. Helen has decided that by herself.";
				link.l1.go = "saga_84";
			}
			else
			{
				link.l1 = "She set off to Isla Tesoro to take the barony into her own hands.";
				link.l1.go = "saga_85";
			}
		break;
		
		case "saga_84":
			dialog.text = "Well, "+pchar.name+"... Congratulations! Many men have dreamed to be in your shoes. I am glad that Helen has chosen a man who deserves her. There could never be a better candidate than you to be her life's companion.";
			link.l1 = "Thank you, Jan! Now I'd like to turn back to our conversation about Tortuga and Levasseur.";
			link.l1.go = "saga_86";
			if (CheckAttribute(pchar, "questTemp.PZ_DialogSvensonBlock"))
			{
				link.l1 = "Thank you, Jan!";
				link.l1.go = "saga_87";
			}
		break;
		
		case "saga_85":
			dialog.text = "Wonderful. She deserves this. I think the new head of the Brethren will help her handle her affairs. She's a talented and bright young girl that can catch on quickly and learn anything. Thank you, "+pchar.name+"! Helen is like a daughter to me and I'm overjoyed that such a marvelous future has just opened up for her.";
			link.l1 = "You're welcome, Jan... Anyway, I'd like to turn back to our conversation about Tortuga and Levasseur.";
			link.l1.go = "saga_86";
			if (CheckAttribute(pchar, "questTemp.PZ_DialogSvensonBlock"))
			{
				link.l1 = "You're welcome, Jan.";
				link.l1.go = "saga_87";
			}
		break;
		
		case "saga_86":
			sTemp = "Shark Dodson";
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus Tyrex";
			dialog.text = "While you were gone, "+sTemp+" and I have already discussed it and came to a common opinion regarding the disposal of Levasseur. Sail off to Isla Tesoro and speak with our new head, he'll give you the details of our plan and will render you all the assistance he can give you.";
			link.l1 = "I finally smell the savor of gunpowder! No time to lose, I'm moving out to Isla Tesoro!";
			link.l1.go = "saga_87";
		break;
		
		case "saga_87":
			dialog.text = ""+pchar.name+", wait a minute. I've got a couple of gifts for you for your help regarding Helen and the Brethren. The first one is the enchanted amulet of Saracen from the far East. Its charms fortify discipline on the ship, verified by me personally. Here you go.";
			link.l1 = "Thank you!";
			link.l1.go = "saga_88";
		break;
		
		case "saga_88":
			GiveItem2Character(pchar, "talisman4");
			Log_Info("You've received the 'Janissary' amulet.");
			PlaySound("interface\important_item.wav");
			dialog.text = "The second is just a souvenir of past adventures. I convinced the Council to throw this ridiculous holdover of using stone fragments into the wind. They're no longer needed. I'll give them to you. Maybe you will somehow find some use for them.";
			link.l1 = "A use for fragments? Hm. I don't know... but as a souvenir, I'm much obliged!";
			link.l1.go = "saga_89";
		break;
		
		case "saga_89":
			GiveItem2Character(pchar, "splinter_js"); 
			GiveItem2Character(pchar, "splinter_nh"); 
			GiveItem2Character(pchar, "splinter_mt"); 
			GiveItem2Character(pchar, "splinter_zm"); 
			GiveItem2Character(pchar, "splinter_jb"); 
			Log_Info("You've received five ornamental pattern fragments");
			dialog.text = "Well, don't forget about your friend, "+pchar.name+". Stop by my place when you anchor in Blueweld. We'll sit down and drink some rum. I'm always glad to see you.";
			link.l1 = "Definitely, Jan. We have something to remember now, don't we? Ha-ha! Anyway, I should go.";
			link.l1.go = "saga_90";
		break;
		
		case "saga_90":
			dialog.text = "Good luck, "+pchar.name+"!";
			link.l1 = "See you...";
			link.l1.go = "saga_91";
		break;
		
		case "saga_91":
			DialogExit();
			pchar.questTemp.Saga = "end";
			if (CheckAttribute(pchar, "questTemp.PZ_DialogSvensonBlock")) AddQuestRecord("Saga", "26_1");
			else 
			{
				AddQuestRecord("Saga", "26");
				pchar.questTemp.Terrapin = "islatesoro";
			}
			CloseQuestHeader("Saga");
			ChangeCharacterComplexReputation(pchar, "fame", 5);
		break;
		
	// --> провалы Саги
		case "saga_f_1":
			dialog.text = "Yep... It really looks like our plan has come crashing down. Now we won't be able to put who we wanted as head of the Brethren. Jackman is dead that's well and good. But alas, my plan isn't going to work out now. We'll have to elect the head of the Brethren the usual way and God knows what kind of a twist it's going to take...";
			link.l1 = "That's unfortunate. Very unfortunate. And it looks like Helen is gonna be left without her inheritance.";
			link.l1.go = "saga_f_2";
		break;
		
		case "saga_f_2":
			dialog.text = "Yes, "+pchar.name+". And I would like to help you take Tortuga, I really would, but now I don't even now how. There's probably nothing I can do to help. It looks like you'll have to rely on nothing but your own strengths and your ability to fight.";
			link.l1 = "It looks like there's no other option left... All right, Jan, I'll go think about what to do next. See you later...";
			link.l1.go = "saga_f_3";
		break;
		
		case "saga_f_3":
			dialog.text = "Stop on by, "+pchar.name+". I'm always glad to see you.";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.Saga = "end";
			CloseQuestHeader("Saga");
			CloseQuestHeader("Testament");
		break;
		
		case "saga_l1": // проход первый - отбираем Элен и закрываем вход к Свенсону
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LocatorReloadEnterDisable("SantaCatalina_houseS1", "reload2", true); // закрыть кабинет Свенсона
			pchar.questTemp.Saga = "end";
			CloseQuestHeader("Saga");
			// Элен - к разговору
			sld = characterFromId("Helena");
			sld.quest.talk = "late_l1";
			pchar.quest.Saga_Late_1.win_condition.l1 = "Location_Type";
			pchar.quest.Saga_Late_1.win_condition.l1.location_type = "town";
			pchar.quest.Saga_Late_1.function = "Saga_HelenaTalk";
			pchar.questTemp.Saga.Jackman = "true";
			Saga_ChangesIslatesoro(); // вызов перестановки на Исла-Тесоро
		break;
		
		case "saga_l2": // проход второй - отбираем Элен, Натана и Данни в Марун-Таун, чистим квестовый лут
			dialog.text = "But alas, it's too late to do anything now. Isla Tesoro is officially transferred into the authority of the English crown. There's a garrison located there now. This is a heavy blow to the Brethren, which, I'm afraid, we won't be able to recover from.";
			link.l1 = "How awful... Ah, I should've acted more quickly. Then, you see, everything would've turned out fine. Alright, Jan, I'll go think about what to do next. See you later...";
			link.l1.go = "saga_l2_1";
		break;
		
		case "saga_l2_1":
			dialog.text = "Stop on by, "+pchar.name+". I'm always glad to see you.";
			link.l1 = "...";
			link.l1.go = "saga_l2_2";
		break;
		
		case "saga_l2_2":
			DialogExit();
			pchar.questTemp.Saga = "end";
			CloseQuestHeader("Saga");
			RemoveItems(pchar, "splinter_nh", 1);
			RemoveItems(pchar, "splinter_mt", 1);
			RemoveItems(pchar, "splinter_jb", 1);
			RemoveItems(pchar, "splinter_zm", 1);
			RemoveItems(pchar, "letter_parol", 1);
			RemoveItems(pchar, "map_sharp_full", 1);
			sld = characterFromId("Nathaniel");
			sld.model = "Hawk_2";
			Characters_RefreshModel(sld); // наверно не нужно
			sld.greeting = "nathaniel_2";
			sld.dialog.currentnode = "marun_town";
			ChangeCharacterAddressGroup(sld, "FortOrange_townhall", "sit", "sit1");
			LAi_SetHuberType(sld);
			LocatorReloadEnterDisable("FortOrange_town", "reload6", false); // открыть резиденцию Хоука
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "marun_town";
			sld.greeting = "danny_2";
			ChangeCharacterAddressGroup(sld, "FortOrange_townhall", "goto", "goto1");
			LAi_SetStayType(sld);
			// Элен - к разговору
			sld = characterFromId("Helena");
			sld.quest.talk = "late_l2";
			pchar.quest.Saga_Late_2.win_condition.l1 = "Location_Type";
			pchar.quest.Saga_Late_2.win_condition.l1.location_type = "town";
			pchar.quest.Saga_Late_2.function = "Saga_HelenaTalk";
			Saga_ChangesIslatesoro(); // вызов перестановки на Исла-Тесоро
			pchar.questTemp.Saga_Late = true; // второй атрибут, отсекающий диалоги, на всякий пожарный
		break;
		
		case "saga_l3":
			dialog.text = "Yep... We really just suffered a harsh defeat. And the worst part of it is we were literally one step away from victory. Caramba! How could this have happened, huh, "+pchar.name+"? You tried so hard, you did so much and... such tough luck!";
			link.l1 = "I'm the imbecile who's responsible for this. I should've been faster. And thanks to me, Helen is going to lose her inheritance. And the Tortuga plan will never come to fruition.";
			link.l1.go = "saga_f_2";
			pchar.questTemp.Saga_Late = true; // второй атрибут, отсекающий диалоги, на всякий пожарный
		break;
	// <-- провалы Саги
		
	//-----------------------------------генератор торговли бакаутом--------------------------------------------
		case "trade_bakaut":
			if (CheckAttribute(pchar, "questTemp.UpgradeBakaut"))
			{
				dialog.text = "Alright, I don't mind. I've got 125 units in my warehouse. The price, as you remember, is 3150 per piece.";
				if (PCharDublonsTotal() >= 3150)
				{
					link.l1 = "Alright, deal. Here you go. Here's 3150 doubloons.";
					link.l1.go = "trade_bakaut_1";
				}
				else
				{
					link.l1 = "Ain't that rotten luck. I forgot my money on my ship. I'll be back with it in a second.";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Alright, I don't mind. I've got twenty five units in my warehouse. The price, as you remember, is thirty doubloons per piece.";
				if (PCharDublonsTotal() >= 750)
				{
					link.l1 = "Alright, deal. Here you go. Here's seven hundred fifty doubloons.";
					link.l1.go = "trade_bakaut_1";
				}
				else
				{
					link.l1 = "Ain't that rotten luck. I forgot my money on my ship. I'll be back with it in a second.";
					link.l1.go = "exit";
				}
			}
			if(sti(pchar.questTemp.SvensonBakaut) >= 1 && !CheckAttribute(pchar, "questTemp.SvensonBakautBlock")) // увеличить объём поставок бакаута
			{
				link.l4 = "Jan, would it be possible to increase the size of ironwood shipments?";
				link.l4.go = "UpgradeBakaut";
			}
			if(sti(pchar.questTemp.SvensonBakaut) >= 1 && CheckAttribute(pchar, "questTemp.SvensonBakautPotom") && PCharDublonsTotal() >= 3000) // увеличить объём поставок бакаута, если в первый раз не принесли
			{
				link.l4 = "Jan, I've gathered three thousand gold coins. Here, you can present this gift to our parasites. I suppose they'll have a happy day today.";
				link.l4.go = "UpgradeBakaut_Agreed";
			}
		break;
		
		case "trade_bakaut_1":
			RemoveDublonsFromPCharTotal(750);
			Log_Info("You have given 750 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Commendable. I'll order my people to carry the ironwood over onto your ship.";
			link.l1 = "Thank you!";
			link.l1.go = "trade_bakaut_2";
		break;
		
		case "trade_bakaut_2":
			dialog.text = "If you want to buy more, come back in two weeks. I will have put together another batch by then.";
			link.l1 = "Alright, Jan. See you next time!";
			link.l1.go = "exit";
			AddCharacterGoods(pchar, GOOD_SANDAL, 25);
			DeleteAttribute(npchar, "quest.trade_bakaut");
			SetFunctionTimerCondition("Bakaut_SvensonAttrReturn", 0, 0, 1, false); // таймер
			AddCharacterExpToSkill(pchar, "Commerce", 100);
		break;
		
		case "UpgradeBakaut": //
			if (startHeroType == 1) sStr = "old friend";
			if (startHeroType == 2) sStr = "old friend";
			if (startHeroType == 3) sStr = "old friend";
			if (startHeroType == 4) sStr = "Helen";
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 80)
			{
				dialog.text = "Glad you're taking a liking to the ironwood, " + sStr + ". Increasing shipments isn't a problem, but there's a catch, as you understand. With larger volumes comes a trail that might attract unwanted attention, especially from the English authorities. But if we add reliable hands, trustworthy ears, and people in the residence who'll help us stay in the shadows, everything can be arranged. Though it won't come cheap - three thousand doubloons to bypass the city treasury and England's needs. Then I can supply you with five times more. What do you say?";
				link.l1 = "Three thousand doubloons? Jan, that's daylight robbery! Couldn't we manage with lower expenses? Perhaps there's a way to settle the matter without such fabulous sums?";
				link.l1.go = "UpgradeBakaut_1";
				notification("Skill Check Passed", SKILL_COMMERCE);
			}
			else
			{
				dialog.text = "Good idea, but I must say, for such volumes in trade affairs you need a bit more experience and skill. Hurry, and there's more risk than benefit. Let's do this: gain a little more experience, and when you're ready for larger batches, come back. Then we'll discuss everything properly.";
				link.l1 = "Hmm... Alright. Let's return to this conversation later.";
				link.l1.go = "exit";
				notification("Skill Check Failed (80)", SKILL_COMMERCE);
			}
		break;
		
		case "UpgradeBakaut_1":
			dialog.text = "Alas, "+pchar.name+", such is the price of peace these days - the appetites of those gentlemen in wigs and uniforms grow each day. Nothing entices them more than doubloons clinking in their chests. I guarantee you a fifteen percent discount on all subsequent shipments, if that comforts you.";
			link.l1 = "Damn them! To ask for such sums! With such greed they should be buying kings' treasures, not bargaining for silence! Jan, maybe we should... show them who's the real power in the archipelago, eh?";
			link.l1.go = "UpgradeBakaut_2";
		break;
		
		case "UpgradeBakaut_2":
			if (startHeroType == 1) sStr = "my friend";
			if (startHeroType == 2) sStr = "my friend";
			if (startHeroType == 3) sStr = "my friend";
			if (startHeroType == 4) sStr = "Helen";
			dialog.text = "Ha! What spirit you have, " + sStr + "! But going against all of England is not in my interest right now, and I'm not as young as I used to be. Let's just pay these bloodsuckers, and let them sit quietly - we have our business to do. Gather the necessary sum, and our path will be clear, without unnecessary questions!";
			if (PCharDublonsTotal() >= 3000)
			{
				link.l1 = "Well, alright, Jan, you've convinced me. Let it be so, since there's no other way around it. Here's your three thousand doubloons. Just remember: I don't intend to feed these misers forever.";
				link.l1.go = "UpgradeBakaut_Agreed";
			}
			link.l2 = "Devil take them, Jan! Do you really think there's no other way out? Fine. I'll find these doubloons. But right now I don't have that kind of money.";
			link.l2.go = "UpgradeBakaut_4";
			link.l3 = "Damn it, Jan, do you really want me to feed these officials with their pampered ladies? They sit in their chairs, do nothing, and only demand money! No, I don't like this! I'm not going to fill their pockets with my sweat and blood! Let's go back to the previous terms. That's enough for me.";
			link.l3.go = "UpgradeBakaut_3";
		break;
		
		case "UpgradeBakaut_Agreed":
			dialog.text = "Now that's more like it! With your contribution our business will run smoothly, and these misers will get their due - and stop even looking in the direction of ironwood. I assure you, soon we'll recoup all investments a hundredfold.";
			link.l1 = "I hope so, Jan, I hope so.";
			link.l1.go = "UpgradeBakaut_Agreed_1";
			RemoveDublonsFromPCharTotal(3000);
			AddQuestRecordInfo("Unique_Goods", "1_1");
			pchar.questTemp.UpgradeBakaut = true;
			pchar.questTemp.SvensonBakautBlock = true;
			DeleteAttribute(pchar, "questTemp.SvensonBakautPotom");
		break;
		
		case "UpgradeBakaut_Agreed_1":
			dialog.text = "Business will go as it should, you need not worry. And now, as for our future deals: I will keep 125 logs of ironwood ready for you, as before, by the 14th and 28th of each month. You can take the entire batch for 3150 doubloons.";
			link.l1 = "I like these conversations much better! One hundred and twenty-five logs, then? Excellent, Jan. Well, see you soon, I'll be waiting for the shipment!";
			link.l1.go = "exit";
		break;
		
		case "UpgradeBakaut_3":
			if (startHeroType == 1) sStr = "old friend";
			if (startHeroType == 2) sStr = "old friend";
			if (startHeroType == 3) sStr = "old friend";
			if (startHeroType == 4) sStr = "Helen";
			dialog.text = "As you wish, " + sStr + ". And don't get so worked up. That's just how this world is arranged.";
			link.l1 = "Yes, Jan, I know how this world is arranged. But that doesn't mean I have to tolerate it. Alright, I must go.";
			link.l1.go = "exit";
			pchar.questTemp.SvensonBakautBlock = true;
		break;
		
		case "UpgradeBakaut_4":
			dialog.text = "I'll wait until you gather the money. I know you'll find a way. As soon as you're ready - I'll be waiting for you with the money, and we'll continue.";
			link.l1 = "Alright.";
			link.l1.go = "exit";
			pchar.questTemp.SvensonBakautBlock = true;
			pchar.questTemp.SvensonBakautPotom = true;
		break;
		// <-- генератор бакаута
		
	//----------------------------------- штурм рудника --------------------------------------------
		case "mine_attack":
			dialog.text = "Glad to see you, "+pchar.name+". My people are ready. Off to the selva?";
			link.l1 = "Yes, Jan. My squad is ready for battle.";
			link.l1.go = "mine_attack_1";
		break;
		
		case "mine_attack_1":
			dialog.text = "Let's move out then. The mine is in the great depth of the jungle right along this trail. Stay right at the fork. Onward!";
			link.l1 = "Onward!";
			link.l1.go = "mine_attack_2";
		break;
		
		case "mine_attack_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Svensons_off_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			for (i=1; i<=12; i++)
			{
				sld = characterFromId("Svensons_sold_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("shore53", "boat", true);
			LocatorReloadEnterDisable("mine_03", "reload3_back", true);
			LocatorReloadEnterDisable("mine_02", "reload3_back", true);
			pchar.quest.Saga_MineAttack_01.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_01.win_condition.l1.location = "Mine_02";
			pchar.quest.Saga_MineAttack_01.function = "Saga_PrepareMineAttackTail";
		break;
		
		case "mine_attack_3":
			dialog.text = "So, "+pchar.name+", it's time to discuss how we're going to go about this operation. I've already sent several Miskito Indians beforehand to survey the area and composed a plan of action based on their observations.";
			link.l1 = "Fill me in!";
			link.l1.go = "mine_attack_4";
		break;
		
		case "mine_attack_4":
			dialog.text = "The pit represents the mine beneath the mountains in the jungle. There is a camp close to an entrance of the mine. A few houses and a palisade. There is a pathway leading to the palisade. Look, it leads to a small, cleared space in the jungles not far from here. That is where the main entrance to the pit is located\nIt represents a high stone wall between two steep hills preventing anyone from sneaking inside. The gates are protected by a guard of six men. Not a big deal, but they also have put up two cannons there. That's the biggest problem.\nTwo volleys of grapeshot can take down half of our squad which would be a disaster, so a head-on attack isn't an option...";
			link.l1 = "Ha! But we've got a trump card, we know the password that will get us inside...";
			link.l1.go = "mine_attack_5";
		break;
		
		case "mine_attack_5":
			dialog.text = "That's correct. We'll use that to our advantage, but for now let me impart my entire plan to you up to the end.";
			link.l1 = "Sure, Jan. I'm all ears.";
			link.l1.go = "mine_attack_6";
		break;
		
		case "mine_attack_6":
			dialog.text = "There is another entrance to the pit - through that path in the jungle. It rounds the hills protecting the mine and leads to a small and narrow hollow which can be used to get inside. But the bandits have established a high fence and put guards there. The fence has small gates but they are barricaded from the other side.\nNow listen to what we are going to do. We will get rid of those who guard the second entrance to the mine. Part of our squad will stay there and find some log to use as a ram.\nWe will return to the main entrance and kill the cannon crews. The password we have will help us twice. Afterwards we'll attack the mine from two sides. I will lead the first assault unit and you will lead the second.";
			link.l1 = "Well, it's logical. We'll make them fight us on two fronts. Onward!";
			link.l1.go = "mine_attack_7";
		break;
		
		case "mine_attack_7":
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.quest.mine01 = "true";
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationDisableOfficersGen("mine_01", true);//офицеров не пускать
			pchar.quest.Saga_MineAttack_02.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_02.win_condition.l1.location = "Mine_04";
			pchar.quest.Saga_MineAttack_02.function = "Saga_PrepareMineAttackTail";
		break;
		
		case "mine_attack_8":
			dialog.text = "Right, here we are... This is the path to the bandit's fence. Now we need to decide on how to deal with them. If we send the whole squad there, it will be too suspicious and they will raise an alarm.\nWe should send a small group of three, not more, this group will be able to get close enough without causing suspicions and attack by surprise. I can't lead the group, my face is too well known around here.\nSo it's up to you, "+pchar.name+", because you are the only one I can trust to command without risking the whole operation. I will give you Gregory and a musketeer to assist...";
			link.l1 = "How many guards are at the picket fence?";
			link.l1.go = "mine_attack_9";
		break;
		
		case "mine_attack_9":
			dialog.text = "Four. Two musketeers and two soldiers.";
			link.l1 = "We'll take 'em...";
			link.l1.go = "mine_attack_10";
		break;
		
		case "mine_attack_10":
			dialog.text = "Knowing you, I don't even doubt that for a second. Walk up to them and tell them that Jackman sent you. Tell them the password. And then after they're all relaxed... act upon the circumstances.";
			link.l1 = "Alright. We'll keep them on their toes.";
			link.l1.go = "mine_attack_11";
		break;
		
		case "mine_attack_11":
			dialog.text = "Good luck, "+pchar.name+"!";
			link.l1 = "...";
			link.l1.go = "mine_attack_12";
		break;
		
		case "mine_attack_12":
			DialogExit();
			LAi_SetStayTypeNoGroup(npchar);
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Svensons_off_"+i);
				LAi_SetStayTypeNoGroup(sld);
				if (i == 2)
				{
					LAi_SetActorType(sld);
					LAi_ActorFollowEverywhere(sld, "", -1);
				}
			}
			for (i=1; i<=12; i++)
			{
				sld = characterFromId("Svensons_sold_"+i);
				LAi_SetStayTypeNoGroup(sld);
				if (i == 12)
				{
					LAi_SetActorType(sld);
					LAi_ActorFollowEverywhere(sld, "", -1);
				}
			}
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("Ourmine_sold_"+i);
				LAi_SetStayTypeNoGroup(sld);
				LAi_CharacterDisableDialog(sld);//запрет диалога
			}
			chrDisableReloadToLocation = false;//открыть локацию
			DeleteAttribute(npchar, "quest.mine01");
			npchar.quest.mine02 = "true";
			pchar.questTemp.Saga.MineAttack = "true";
			pchar.quest.Saga_MineAttack_03.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_03.win_condition.l1.location = "Mine_01";
			pchar.quest.Saga_MineAttack_03.function = "Saga_MineAttackTail";
		break;
		
		case "mine_attack_13":
			dialog.text = "Great job, "+pchar.name+"! You have come out on top, as always. Now, my boys will prepare to initiate a storm from this side of the mine and we'll clear off the main entrance.";
			link.l1 = "I take it, I'll be walking up to the guards again?";
			if (GetCharacterIndex("Svensons_off_2") != -1 && GetCharacterIndex("Svensons_sold_12") != -1) link.l1.go = "mine_attack_14";
			else link.l1.go = "mine_attack_14a";
		break;
		
		case "mine_attack_14a":
			dialog.text = "Yes, "+pchar.name+", once again. I'd love to go myself, but they would surely recognize me and the whole operation would go haywire. It will be more dangerous as there are more enemies, and don't forget the weapons.";
			link.l1 = "I'll take my officers with me.";
			link.l1.go = "mine_attack_14_1";
		break;
		
		case "mine_attack_14":
			dialog.text = "Yes, "+pchar.name+", once again. I'd love to go myself, but they would surely recognize me and the whole operation would go haywire. It will be more dangerous as there are more enemies, and don't forget the weapons. Who will you take with you to aid you? Your officers or Gregory and the musketeer like last time?";
			link.l1 = "I'll take my officers.";
			link.l1.go = "mine_attack_14_1";
			link.l2 = "I'll take Gregory and the musketeer.";
			link.l2.go = "mine_attack_14_2";
		break;
		
		case "mine_attack_14_1":
			dialog.text = "Alright. Your own people are your best backup. Now we'll make our way back towards the main entrance. Do you remember the way?";
			link.l1 = "Of course. Back the way we came, then stay left, and then take the trail around the hill.";
			link.l1.go = "mine_attack_15";
			pchar.questTemp.Saga.MineAttack = "officer";
		break;
		
		case "mine_attack_14_2":
			dialog.text = "Fine. You've managed to pull it off once, so doing it a second time should be a piece of cake. We're going to make our way back to the main entrance now. Do you remember the way?";
			link.l1 = "Of course. Back the way we came, then stay left, and take the trail around the hill.";
			link.l1.go = "mine_attack_15";
			pchar.questTemp.Saga.MineAttack = "soldiers";
		break;
		
		case "mine_attack_15":
			dialog.text = "No time to waste. Let's march!";
			link.l1 = "Onward!";
			link.l1.go = "mine_attack_16";
		break;
		
		case "mine_attack_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			for (i=1; i<=2; i++)
			{
				if (GetCharacterIndex("Svensons_off_"+i) != -1)
				{
					sld = characterFromId("Svensons_off_"+i);
					LAi_SetActorType(sld);
					LAi_ActorFollowEverywhere(sld, "", -1);
				}
			}
			for (i=1; i<=12; i++)
			{
				sld = characterFromId("Svensons_sold_"+i);
				LAi_SetActorType(sld);
				if (pchar.questTemp.Saga.MineAttack == "soldiers" && i == 12) LAi_ActorFollowEverywhere(sld, "", -1);
				else LAi_ActorRunToLocation(sld, "reload", "reload3_back", "mine_01", "goto", "goto"+i, "", 5);
			}
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("Ourmine_sold_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationDisableOfficersGen("mine_01", false);//офицеров пускать
			if (pchar.questTemp.Saga.MineAttack == "soldiers") LAi_LocationDisableOfficersGen("mine_exit", true);//офицеров не пускать
			LocatorReloadEnterDisable("mine_03", "reload3_back", false);
			LocatorReloadEnterDisable("mine_02", "reload3_back", false);
			DeleteAttribute(npchar, "quest.mine02");
			npchar.quest.mine03 = "true";
			pchar.quest.Saga_MineAttack_05.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_05.win_condition.l1.location = "Mine_02";
			pchar.quest.Saga_MineAttack_05.function = "Saga_PrepareMineAttackTail";
		break;
		
		case "mine_attack_17":
			dialog.text = "Right, "+pchar.name+", listen to these last instructions. These devils guarding the gates are tough, so it is not going to be easy for you. Your main objective is to kill the cannoneers standing near the gates because we won't be able to come help you if they are still breathing.\nOnce both of them are dead and there is no chance of a gun volley all of us will come and slay them in seconds. Did you get that, "+pchar.name+"? Don't play a hero, kill the cannoneers and leave the rest to us.";
			link.l1 = "Fine, Jan. I'll try to do everything like we planned. And if something goes wrong, I'll play by ear.";
			link.l1.go = "mine_attack_18";
		break;
		
		case "mine_attack_18":
			dialog.text = "Sounds good. May God be with you!";
			link.l1 = "Thanks...";
			link.l1.go = "mine_attack_19";
		break;
		
		case "mine_attack_19":
			DialogExit();
			LAi_SetStayTypeNoGroup(npchar);
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			for (i=1; i<=2; i++)
			{
				if (GetCharacterIndex("Svensons_off_"+i) != -1)
				{
					sld = characterFromId("Svensons_off_"+i);
					if (pchar.questTemp.Saga.MineAttack == "soldiers" && i == 2)
					{
						LAi_SetActorType(sld);
						LAi_ActorFollowEverywhere(sld, "", -1);
					}
					else LAi_SetStayTypeNoGroup(sld);
				}
			}
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("Ourmine_sold_"+i);
				LAi_SetStayTypeNoGroup(sld);
			}
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationDisableOfficersGen("mine_01", false);//офицеров пускать
			DeleteAttribute(npchar, "quest.mine03");
			pchar.quest.Saga_MineAttack_06.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_06.win_condition.l1.location = "Mine_exit";
			pchar.quest.Saga_MineAttack_06.function = "Saga_MineAttackTail";
		break;
		
		case "mine_attack_20":
			dialog.text = "Phew! We mowed down those sons of bitches... Feisty little ruffians they were. I can tell that these mercs used to serve in the regular troops. We did some noise here, I'm afraid we might've been heard. Not a minute to waste! "+pchar.name+", it is time for us to attack the mine.\nI will return to my group at the second entrance - they must have already found and prepared a log to ram the fence. You and your men will go through the central gates. Wait for us for half an hour, don't attack immediately...";
			link.l1 = "Jan, if they heard the firing at the mine, we don't have this half an hour. Those bandits could set up a defense line or likely come right to the central gates and attack my group with everything they have...";
			link.l1.go = "mine_attack_21";
		break;
		
		case "mine_attack_21":
			dialog.text = "Fuck! That's quite possible. What do you suggest we do?";
			link.l1 = "Hm... Ha! I have an idea! Cannons! Look around. There is not only grapeshot but bombs can be found too! Now these bandits are done! Why didn't I think of this earlier?!";
			link.l1.go = "mine_attack_22";
		break;
		
		case "mine_attack_22":
			dialog.text = "What do you think we should do?";
			link.l1 = "We'll take one cannon. With one we'll be able to move much quicker and more efficiently. We'll roll it inside, beyond the gates, to the mine and set it in position. If they engage an attack themselves, they'll get a big boom, and if they sit back, we'll just bombard their camp. Can you tell me where exactly the camp is located behind the gates?";
			link.l1.go = "mine_attack_23";
		break;
		
		case "mine_attack_23":
			dialog.text = "The camp is on low ground by a mountain. There's a trail right beyond the gates leading down and weaving around the hill. The camp is located right behind this hill.";
			link.l1 = "Splendid! We'll set up on top of the trail and fire a couple bombs over the hill into their nest! Oh, we'll have them dancing all around!";
			link.l1.go = "mine_attack_24";
		break;
		
		case "mine_attack_24":
			dialog.text = "God damn it, "+pchar.name+", well done! All speed ahead! I'll leave Randolf under your command, he's my best cannon gunner. Make him your gunner and he won't let you down. I am off to my unit right now.";
			link.l1 = "Alright. I will be bombarding their positions to hell for half an hour until you break the gates.";
			link.l1.go = "mine_attack_25";
		break;
		
		case "mine_attack_25":
			dialog.text = "I'll try to make it in time. Meet you in the camp!";
			link.l1 = "Deal... Squad! Listen to my command! Prepare to transfer the cannon to a new position! Take gunpowder, bombs, and grapeshot with you! To the mine through the gates. Forward march!";
			link.l1.go = "mine_attack_26";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2_back", "none", "", "", "", 5);
			if (GetCharacterIndex("Svensons_off_2") != -1)
			{
				sld = characterFromId("Svensons_off_2");
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload2_back", "none", "", "", "", 5);
			}
		break;
		
		case "mine_attack_26":
			DialogExit();
			int n = Findlocation("mine_exit");
			DeleteAttribute(&locations[n], "mine_bandits");
			LocatorReloadEnterDisable("mine_exit", "reload1_back", false);
			pchar.quest.Saga_MineAttack_07.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_07.win_condition.l1.location = "Mine";
			pchar.quest.Saga_MineAttack_07.function = "Saga_MineGunAttack";
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("mine_exit", "reload2_back", true);
			LAi_LocationDisableOfficersGen("mine_exit", false); // офицеров пускать
			n = Findlocation("mine");
			locations[n].models.always.Gun = "mortair";
			Locations[n].models.always.Gun.locator.group = "goto";
			Locations[n].models.always.Gun.locator.name = "fire"; // орудие - к бою!
			Locations[n].hidden_sound = true;
		break;
		
		case "mine_attack_27":
			dialog.text = "Phew, aren't we too late, "+pchar.name+"?";
			link.l1 = "Jan, holy shit! What took you so long? My squad just took a huge blow!";
			link.l1.go = "mine_attack_28";
		break;
		
		case "mine_attack_28":
			dialog.text = "That fucking wooden fence turned out to by really sturdy. We broke it by force... We heard your rumble bumble. Looks like you've cleaned out this place nicely! It's burning to the ground!";
			link.l1 = "Randolf's doings... I wish you could have seen how many bastards we had buried before we finally entered into hand to hand combat!";
			link.l1.go = "mine_attack_29";
		break;
		
		case "mine_attack_29":
			dialog.text = "Caramba! I take my hat off to you, "+pchar.name+". Well done! Well, about the losses... you have them any time you're at war.";
			link.l1 = "Now what we need to do is mop up the mine itself. It's possible that some survivors are hiding in there.";
			link.l1.go = "mine_attack_30";
		break;
		
		case "mine_attack_30":
			dialog.text = "Let's go just the two of us. Explore the situation there.";
			link.l1 = "Sounds like a plan!";
			link.l1.go = "mine_attack_31";
		break;
		
		case "mine_attack_31":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetCheckMinHP(npchar, 10, true, "");
			TakeNItems(npchar, "potion2", 8); 
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4", "Mine_mines", "reload", "reload1", "", -1);
			LAi_LocationDisableOfficersGen("Mine_mines", true);//офицеров не пускать
			pchar.quest.Saga_MineAttack_08.win_condition.l1 = "locator";
			pchar.quest.Saga_MineAttack_08.win_condition.l1.location = "mine";
			pchar.quest.Saga_MineAttack_08.win_condition.l1.locator_group = "reload";
			pchar.quest.Saga_MineAttack_08.win_condition.l1.locator = "reload4";
			pchar.quest.Saga_MineAttack_08.function = "Saga_MineAttackMines";
		break;
		
		case "mine_attack_32a":
			dialog.text = "We haven't searched the whole mine yet! I guarantee you that some more of those scallywags are hiding in here!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "mine_attack_32a";
		break;
		
		case "mine_attack_32":
			dialog.text = "I don't think there's another scumbag left...";
			link.l1 = "Jan, I thought we were just coming here to explore the situation...";
			link.l1.go = "mine_attack_33";
		break;
		
		case "mine_attack_33":
			dialog.text = "Ha-ha, well, I didn't tell you that this would be a special exploration, a bloody exploration... I haven't got a warm up like that for a while! Now everybody can be assured that there isn't one scumbag that escaped this mine!";
			link.l1 = "So what are we gonna do next, Jan?";
			link.l1.go = "mine_attack_34";
		break;
		
		case "mine_attack_34":
			dialog.text = "What do you mean what are we gonna do next? We're gonna search for gold and silver. I don't think Jackman was holding this kind of a bulwark here out of boredom. He placed a whole garrison here. Did you see the slaves in the mine? You should inquire where they're storing the extracts.";
			link.l1 = "All right. Then you go interrogate the slaves and I'll climb up and search all the houses in the camp, maybe I'll find something.";
			link.l1.go = "mine_attack_35";
		break;
		
		case "mine_attack_35":
			dialog.text = "Gotcha! Time to move it!";
			link.l1 = "...";
			link.l1.go = "mine_attack_36";
		break;
		
		case "mine_attack_36":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			LAi_SetImmortal(npchar, true);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("mine", "reload1", true);
			LocatorReloadEnterDisable("mine", "reload6", true);//закрыть выходы с рудника
			pchar.quest.Saga_Mine_letter.win_condition.l1 = "item";
			pchar.quest.Saga_Mine_letter.win_condition.l1.item = "letter_mine";
			pchar.quest.Saga_Mine_letter.function = "Saga_FindMineLetter";
			NextDiag.CurrentNode = "mine_attack_36a";
		break;
		
		case "mine_attack_36a":
			dialog.text = "Go, mate. And turn these pitiful hovels inside out!";
			link.l1 = "I'm on my way!";
			link.l1.go = "exit";
			NextDiag.TempNode = "mine_attack_36a";
		break;
		
		case "mine_attack_37":
			dialog.text = "Ha-ha! "+pchar.name+", it's great that you volunteered to come out with me to tear up this mine! It's another clear indicator for you being born under a lucky star.";
			link.l1 = "Have you found gold?";
			link.l1.go = "mine_attack_38";
		break;
		
		case "mine_attack_38":
			dialog.text = "Yes, damn it! Not gold but silver, a good pile of it. A day later and they would have moved it out of the camp. That's why there were so many thugs here - they were an escort group.\nThanks to you we made it in time, without you I would still gather people. Congratulations partner!";
			link.l1 = "Ha! I see... How much silver have we got?";
			link.l1.go = "mine_attack_39";
		break;
		
		case "mine_attack_39":
			dialog.text = "We've got about four thousand units. We'll split it in two parts - half for me, half for you, just like we agreed.";
			link.l1 = "Outstanding! We can get paid a whole heap of money for that stuff!";
			link.l1.go = "mine_attack_40";
		break;
		
		case "mine_attack_40":
			dialog.text = "That's for sure... Did you find anything valuable?";
			link.l1 = "Nope. There isn't even a single doubloon in these hovels. Although I found some papers. I read them and learned that the owner of this mine is some Lawrence Beltrope from Port Royal.";
			link.l1.go = "mine_attack_41";
		break;
		
		case "mine_attack_41":
			dialog.text = "Oh, really? Let me see those documents...";
			link.l1 = "Here you go.";
			link.l1.go = "mine_attack_42";
		break;
		
		case "mine_attack_42":
			RemoveItems(pchar, "letter_mine", 1);
			dialog.text = "(reading)... Fine... Beltrope? I know that surname from somewhere. Oh, yes! Thomas Beltrope! That's interesting... Alright, I'll check up on this when I get back to Blueweld. I'll keep these documents with me if you don't mind?";
			link.l1 = "Not at all. I don't need them for anything.";
			link.l1.go = "mine_attack_43";
		break;
		
		case "mine_attack_43":
			dialog.text = "Good. Now, the best part is left, I'm going to transport the silver to the ships. The Miskitos will help us with that. We'll put a wagon together... Meanwhile, you just go ahead and get some rest, "+pchar.name+". You've deserved it more than anybody!";
			link.l1 = "Thanks, Jan. We'll make a camp on that hill, the cindery smell is too much. Yeah, and we need to put out the fires on these hovels, who knows, maybe they will come in handy for us sometime in the future...";
			link.l1.go = "mine_attack_44";
		break;
		
		case "mine_attack_44":
			dialog.text = "Thinking of claiming the mine? Ha-ha! I have already been considering the idea, but plundering is one thing, taking it as property is another. Friend, it has already got an owner. We might get into troubles with the English authorities.\nBesides, the slaves I was talking to told me that all veins here were basically used up - big batches of silver had been moved away from here several times before. I am afraid, this mine is done for.";
			link.l1 = "Hm... We'll see. Maybe not everything is depleted. Fine, I really should take some rest. See you later, Jan";
			link.l1.go = "mine_attack_45";
		break;
		
		case "mine_attack_45":
			dialog.text = "Go ahead. And don't worry about a thing. We'll take care of everything else on our own.";
			link.l1 = "...";
			link.l1.go = "mine_attack_46";
		break;
		
		case "mine_attack_46":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "rld", "attack1", "Saga_MineWaitTime", -1);
			n = Findlocation("mine");
			DeleteAttribute(&locations[n], "hidden_sound");
			DeleteAttribute(&locations[n], "hidden_fire");
			n = Findlocation("mine_exit");
			DeleteAttribute(&locations[n], "models.always.Gun1");
		break;
		
		case "mine_attack_47":
			dialog.text = "Had a good rest, "+pchar.name+"?";
			link.l1 = "It wasn't bad... Although, honestly, I'd kill to find myself a tavern, get a drink, and get some sleep in a clean bed.";
			link.l1.go = "mine_attack_48";
		break;
		
		case "mine_attack_48":
			dialog.text = "The Indians have delivered the silver to the shore and are loading it onto your ship under my officers' supervision. You can head back already. Your wish for rum, a tavern, and a bed will soon come true. And I'd like you to stop by in five days in my house, we still have a lot of things to do.";
			link.l1 = "Alright, Jan. See you in Blueweld in five days! Good luck!";
			link.l1.go = "mine_attack_49";
		break;
		
		case "mine_attack_49":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4", "none", "", "", "", 15.0);
			LocatorReloadEnterDisable("shore53", "boat", false);
			LocatorReloadEnterDisable("mine", "reload1", false);
			LocatorReloadEnterDisable("mine", "reload6", false);
			LocatorReloadEnterDisable("mine_01", "reload3_back", false);
			LocatorReloadEnterDisable("mine_exit", "reload2_back", false); //открыть выходы с рудника
			LAi_LocationDisableOfficersGen("mine_mines", false); // офицеров пускать
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			SetFunctionTimerCondition("Saga_ReturnFromMine", 0, 0, 5, false); // таймер
			pchar.questTemp.Saga.Mines = "true"; // после Саги рудник будет разрабатываться
			ChangeCharacterComplexReputation(pchar, "fame", 2);
			DoQuestReloadToLocation("Shore53", "goto", "goto6", "");
		break;
		// <-- штурм рудника
		
		case "helensleep":
			dialog.text = "";
			link.l1 = "Jan, don't shout at me. Let's sort things out like reasonable people - remember, we have business to conduct!";
			link.l1.go = "helensleep_1";
		break;
		
		case "helensleep_1":
			dialog.text = "I'll set my dogs on you right now, you toad! Forget about Levasseur, and get lost!";
			link.l1 = "Jan! Listen to me...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenSleep_SvensonThrowOut");
		break;
		
		case "after_drinking":
			dialog.text = "What barrel? As for Helen, I'll be sure to give her a good whooping... Just kidding, Charles, just kidding! I know how it goes, and as for Joanna - this story will hopefully make her think a little - she's been especially cranky lately, you know...Well, such is life. Anyway, good luck to you in Cartagena!";
			link.l1 = "Until we meet again, Jan.";
			link.l1.go = "exit";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

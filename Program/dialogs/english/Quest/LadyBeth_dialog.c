void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag, arTmp;
	int i, n;
	string sTemp, sStr;
	
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
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "AlonsoNaPalube":
			if (CheckAttribute(pchar, "questTemp.LadyBeth_AlonsoNaPalube"))
			{
				pchar.questTemp.LadyBeth_AlonsoNaPalube2 = true;
				dialog.text = "Your decision, Captain? Maybe we shouldn't?";
				link.l1 = "Did you manage to gather more volunteers for the task?";
				link.l1.go = "AlonsoNaPalube_StrongGroup";
			}
			else
			{
				pchar.questTemp.LadyBeth_AlonsoNaPalube = true;
				dialog.text = "Captain, a word.";
				link.l1 = "Report, Alonso.";
				link.l1.go = "AlonsoNaPalube_2";
			}
			locCameraFromToPos(-10.33, 9.69, -22.16, true, -5.22, 7.19, -21.06);
		break;
		
		case "AlonsoNaPalube_2":
			dialog.text = "The crew is wondering what your plans for Cayman are. People are worried.";
			link.l1 = "I haven't decided yet. And why are the men worried, Alonso?";
			link.l1.go = "AlonsoNaPalube_3";
		break;
		
		case "AlonsoNaPalube_3":
			dialog.text = "This island is Captain Blackwood's domain. Sailors say he's digging it up like a man possessed, length and breadth. That he's ruined dozens of men in his excavations... And those who leave him... tell strange tales.";
			link.l1 = "What kind of tales?";
			link.l1.go = "AlonsoNaPalube_4";
		break;
		
		case "AlonsoNaPalube_4":
			dialog.text = "That Blackwood is no longer the man he once was. That he's obsessed with finding some conquistador treasure. That he's ready to sacrifice everything and everyone for it. We know how much you like getting into pretty stories, landing alone and falling into traps... Well, you won't get out of this one.";
			link.l1 = "Thanks for the report and the warning. If I do decide to make a landing, I'll be sure to take the vanguard and a detachment of our best fighters.";
			link.l1.go = "AlonsoNaPalube_5";
		break;
		
		case "AlonsoNaPalube_5":
			dialog.text = "That may be difficult, Captain. Boarding is one thing, but going ashore under the bullets of marines and the sabers of the riffraff that Blackwood has supposedly hired from every hole in the Lesser Antilles is quite another. And there are bad rumors about Cayman... No, you won't find many volunteers for such work.";
			link.l1 = "Then we'll have to make do with whoever we can. Your participation is mandatory, Alonso.";
			link.l1.go = "AlonsoNaPalube_LiteGroup";
			link.l2 = "In my opinion, I've already proven to everyone everything that could be proven. All good fighters and shooters will go. That's an order.";
			link.l2.go = "AlonsoNaPalube_StrongGroup";
			link.l3 = "Hmm... Well, I need to think it all through. Perhaps we'll return to this question later.";
			link.l3.go = "AlonsoNaPalube_Exit";
		break;
		
		case "AlonsoNaPalube_Exit":
			SetFunctionLocationCondition("LadyBeth_CaimanSea", "Caiman", false);
			EndQuestMovie();
			bQuestDisableMapEnter = false;
			chrDisableReloadToLocation = false;
			if(UnloadLocation(loadedLocation) == true)
			{
				pchar.Ship.Pos.x = 0;
				pchar.Ship.Pos.z = 0;
				pchar.Ship.Ang.y = 0;
				Land_MapLoad();
				pchar.location = "";
			}
		break;
		
		case "AlonsoNaPalube_LiteGroup":
			dialog.text = "Aye, Captain!";
			link.l1 = "What about Blackwood's ship? Won't it cause problems?";
			link.l1.go = "AlonsoNaPalube_Vpered";
			pchar.questTemp.LadyBeth_LiteGroup = true;
		break;
		
		case "AlonsoNaPalube_StrongGroup":
			if (GetSummonSkillFromName(pchar, SKILL_Leadership) >= 50 || sti(pchar.rank) >= 17)
			{
				dialog.text = "Aye, Captain!";
				link.l1 = "What about Blackwood's ship? Won't it cause problems?";
				link.l1.go = "AlonsoNaPalube_Vpered";
				pchar.questTemp.LadyBeth_StrongGroup = true;
				if (GetSummonSkillFromName(pchar, SKILL_Leadership) >= 50) notification("Skill Check Passed", SKILL_Leadership);
				if (sti(pchar.rank) >= 17) notification("Level check passed", "None");
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LadyBeth_AlonsoNaPalube2"))
				{
					dialog.text = "I'm afraid not yet, Captain.";
				}
				else
				{
					dialog.text = "You have nothing to prove to me or your officers, and we will go by orders to wherever you say, but the ordinary sailor thinks differently. I'm afraid there will be problems, Captain.";
				}
				link.l1 = "Then we'll have to make do with whoever we can. Your participation is mandatory, Alonso.";
				link.l1.go = "AlonsoNaPalube_LiteGroup";
				link.l2 = "Hmm... Well, I need to think it all through. Perhaps we'll return to this question later.";
				link.l2.go = "AlonsoNaPalube_Exit";
				if (GetSummonSkillFromName(pchar, SKILL_Leadership) < 50) notification("Skill Check Failed (50)", SKILL_Leadership);
				if (sti(pchar.rank) < 17) notification("Level 17 required", "None");
			}
		break;
		
		case "AlonsoNaPalube_Vpered":
			dialog.text = "A snow. They say a real beauty with a fierce temperament. I wouldn't worry about her. Most likely, the entire crew is slaving away on land while the ship is safely hidden in the folds of the coastline. When and if we win, we can take her as a prize from the shore.";
			link.l1 = "Gather the men. Today is a good day - fortune will be on our side.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_AlonsoNaPalube_Vpered");
		break;
		
		// Диалог в таверне с Блеквудом
		case "LadyBeth_DialogInCity": // главное меню
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Fourth"))
			{
				dialog.text = "Glad to see you, Captain. I believe we've discussed everything already..";
				link.l1 = "Indeed. Farewell.";
				link.l1.go = "exit";
				NextDiag.TempNode = "LadyBeth_DialogInCity_again";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Third"))
			{
				dialog.text = "...";
				link.l1 = ""+TimeGreeting()+", "+npchar.name+"";
				link.l1.go = "LadyBeth_DialogInCity_Third_2";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Second"))
			{
				dialog.text = "...";
				link.l1 = ""+TimeGreeting()+", Captain Blackwood.";
				link.l1.go = "LadyBeth_DialogInCity_Second_1";
				break;
			}
			if (startHeroType == 4)
			{
				dialog.text = "...";
				link.l1 = "Hello. Are you Captain Blackwood?";
				link.l1.go = "LadyBeth_DialogInCity_First_Helena_1";
			}
			else
			{
				dialog.text = "...";
				link.l1 = ""+TimeGreeting()+". Are you Captain Albert Blackwood, correct?";
				link.l1.go = "LadyBeth_DialogInCity_First_1";
			}
		break;
		
		case "LadyBeth_DialogInCity_again": // повтор
			dialog.text = "Glad to see you, Captain. I believe we've discussed everything already.";
			link.l1 = "Indeed. Farewell.";
			link.l1.go = "exit";
			NextDiag.TempNode = "LadyBeth_DialogInCity_again";
		break;
		
		case "LadyBeth_DialogInCity_First_1": // первый диалог
			dialog.text = "Yes, that's me. And you?";
			link.l1 = "Captain "+GetFullName(pchar)+". I command the ship '" + PChar.Ship.Name + "'.";
			link.l1.go = "LadyBeth_DialogInCity_First_2";
		break;
		
		case "LadyBeth_DialogInCity_First_2":
			dialog.text = "Captain... Have you been to Cayman?";
			link.l1 = "Just passed by.";
			link.l1.go = "LadyBeth_DialogInCity_First_3";
		break;
		
		case "LadyBeth_DialogInCity_First_3":
			dialog.text = "Have you heard anything about treasures there?";
			link.l1 = "No, nothing specific.";
			link.l1.go = "LadyBeth_DialogInCity_First_4";
		break;
		
		case "LadyBeth_DialogInCity_First_4":
			dialog.text = "Traces of Spaniards? Old weapons? Coins from the time of the conquistadors?";
			link.l1 = "Haven't found anything like that.";
			link.l1.go = "LadyBeth_DialogInCity_First_5";
		break;
		
		case "LadyBeth_DialogInCity_First_5":
			dialog.text = "Local legends? Stories about Cortez? Anything about burials?";
			link.l1 = "I'm sorry, Captain, but I don't have such information. And this is already starting to feel like an interrogation.";
			link.l1.go = "LadyBeth_DialogInCity_First_6";
		break;
		
		case "LadyBeth_DialogInCity_First_6":
			dialog.text = "I apologize... Bad habit of a former officer. It's just... this is extremely important to me.";
			link.l1 = "Why are you so interested in Cayman specifically?";
			link.l1.go = "LadyBeth_DialogInCity_First_7";
		break;
		
		case "LadyBeth_DialogInCity_First_7":
			dialog.text = "Not important. Once again, I apologize.";
			link.l1 = "I understand. Good luck in your searches.";
			link.l1.go = "LadyBeth_DialogInCity_First_8";
		break;
		
		case "LadyBeth_DialogInCity_First_8":
			if (GetHour() >= 23 || GetHour() < 6) sStr = "Good night";
			else sStr = "Wishing you a good day";
			dialog.text = "Come see me if you find anything worthwhile. I would enjoy conversing with another captain... with someone who understands the sea. " + sStr + ".";
			link.l1 = ""+Goodbye()+".";
			link.l1.go = "LadyBeth_DialogInCity_First_9";
		break;
		
		case "LadyBeth_DialogInCity_First_9":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Second = true;
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_1": // первый диалог с Элен
			dialog.text = "In the flesh. And you... Captain Helen MacArthur? Jan Svenson's protégé, right? I've heard about you.";
			link.l1 = "You are well-informed, Captain Blackwood. But I'm not surprised that an English officer knows about me.";
			link.l1.go = "LadyBeth_DialogInCity_First_Helena_2";
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_2":
			dialog.text = "Former officer. And all the red coats know about you and your... unique preferences from the Crown. Ironwood, as they say, doesn't smell. And the story of how your father Sean MacArthur took you to sea since childhood and made you a captain has become something of a legend in the fleet.";
			link.l1 = "And how does it feel to meet this legend?";
			link.l1.go = "LadyBeth_DialogInCity_First_Helena_3";
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_3":
			dialog.text = "I personally am impressed. Though many of my former colleagues, I must admit, find it quite irritating. But to become a captain takes something more than just noble birth or a royal patent, doesn't it?";
			link.l1 = "True. It takes knowledge, experience, and a constant readiness to prove your competence. Especially in my case.";
			link.l1.go = "LadyBeth_DialogInCity_First_Helena_4";
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_4":
			dialog.text = "Exactly! At sea, as in life, what matters are not titles, but results. Pleased to meet you, Captain MacArthur. I hope we'll meet again. Perhaps you'll drop by for a glass of wine when I return from my expedition?";
			link.l1 = "Perhaps. Good luck in your searches, Captain.";
			link.l1.go = "LadyBeth_DialogInCity_First_Helena_5_harizma";
			link.l2 = "Not interested. But good luck in your searches, Captain.";
			link.l2.go = "LadyBeth_DialogInCity_First_Helena_5_oruzhie";
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_5_harizma":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Second = true;
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_5_oruzhie":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Second = true;
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "LadyBeth_DialogInCity_Second_1": // второй диалог
			dialog.text = "Ah, Captain "+pchar.lastname+"! Glad to see you. Would you like to sit?";
			link.l1 = "With pleasure.";
			link.l1.go = "LadyBeth_DialogInCity_Second_2";
		break;
		
		case "LadyBeth_DialogInCity_Second_2":
			dialog.text = "Captain... tell me, what do real treasures mean to you?";
			link.l1 = "A real treasure is love. The right person by your side. There's nothing worse than being alone.";
			link.l1.go = "LadyBeth_DialogInCity_Second_3_love";
			link.l2 = "Money, of course. What else could be a treasure?";
			link.l2.go = "LadyBeth_DialogInCity_Second_3_sokrovisha";
			link.l3 = "Valuable and unique equipment. A good sword or pistol is worth more than gold.";
			link.l3.go = "LadyBeth_DialogInCity_Second_3_oruzhie";
			link.l4 = "Knowledge. The most valuable treasure is what's in your head.";
			link.l4.go = "LadyBeth_DialogInCity_Second_3_znania";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_love":
			if (startHeroType == 4)
			{
				dialog.text = "Love? Hmm... I didn't expect such an answer from a pirate's daughter. I... I was engaged. To Elizabeth. The daughter of a plantation owner from Barbados. But her father... he decided I didn't have enough money. What could I offer his daughter besides my love? You were lucky, Captain MacArthur. You had a father who valued your abilities more than your dowry.";
				link.l1 = "Perhaps it's not about luck, but about the fact that true love isn't measured in gold. My father understood that. What about your fiancée? Does she share her father's views?";
				link.l1.go = "LadyBeth_DialogInCity_Second_3_love_Helena_1";
			}
			else
			{
				dialog.text = "Love? Yes... Perhaps you're right. I... I was engaged. On Barbados. We loved each other, but... her father deemed me an unworthy match. Ha! Not wealthy enough. That's why I'm here - seeking treasures to prove them all wrong. Maybe it's in vain?";
				link.l1 = "Perhaps you should just talk to her? To hell with that plantation owner.";
				link.l1.go = "LadyBeth_DialogInCity_Second_3_love_2";
			}
			AddComplexLandExpToScill(100, 100, 0);
		break;
		
		case "LadyBeth_DialogInCity_Second_3_love_2":
			dialog.text = "Talk... Yes, perhaps. But what would I say? 'Sorry, I couldn't provide you with a decent life'? No. I must return a winner. Or not return at all.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_DialogInCity_Second_4";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_love_Helena_1":
			dialog.text = "Elizabeth? No... she loves me. But I... I couldn't let her live in poverty. She deserves better. And I must prove that I am worthy of her.";
			link.l1 = "Sometimes pride hinders happiness more than poverty, Captain.";
			link.l1.go = "LadyBeth_DialogInCity_Second_3_love_Helena_2";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_love_Helena_2":
			dialog.text = "I cannot return empty-handed. I just can't. I apologize, I have a lot of work. It was pleasant to chat with you, Captain MacArthur.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_DialogInCity_Second_5";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_sokrovisha":
			dialog.text = "What a banal answer. But it's hard to argue with. Indeed, when you grew up in the slums of Bristol, when you had to fight for scraps... you begin to understand the true value of money. It's not luxury. It's freedom. The ability to never return to that filth from which you climbed out with such difficulty.";
			link.l1 = "I agree. Money solves most problems. And if they don't solve them - it means there's simply not enough of it.";
			link.l1.go = "LadyBeth_DialogInCity_Second_3_sokrovisha_2";
			AddCharacterExpToSkill(pchar, "Commerce", 200);
		break;
		
		case "LadyBeth_DialogInCity_Second_3_sokrovisha_2":
			dialog.text = "Exactly! You understand. Money doesn't make you happy, but its absence makes you unhappy for sure. I know this all too well...";
			link.l1 = "...";
			link.l1.go = "LadyBeth_DialogInCity_Second_4";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_oruzhie":
			dialog.text = "Interesting. Practical. I have an arquebus... a real one, from the time of the conquistadors. A gift from a certain priest. Sometimes I think it's worth more than all the gold I've found. But... it won't solve my problems.";
			link.l1 = "Good weapons can solve many problems. And they will never betray you.";
			link.l1.go = "LadyBeth_DialogInCity_Second_3_oruzhie_2";
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "LadyBeth_DialogInCity_Second_3_oruzhie_2":
			dialog.text = "There's truth in that. But some battles cannot be won by force of arms.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_DialogInCity_Second_4";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_znania":
			dialog.text = "Knowledge... Yes, I understand. I've studied everything I could about the conquistadors, about treasures. I've compiled a whole manual on treasure hunting. Devised a system of regular drills and material incentives for the ship's rifle company. Any captain would be glad to get my manual. But all this knowledge... It's useless if it doesn't lead to results. To real results.";
			link.l1 = "But it's knowledge that helps achieve results. Without it, any search is just wandering in the dark.";
			link.l1.go = "LadyBeth_DialogInCity_Second_4";
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "LadyBeth_DialogInCity_Second_4":
			if (GetHour() >= 23 || GetHour() < 6) sStr = "Well, it's already late, and I have a lot of work to do";
			else sStr = "Well, I have a lot of work to do";
			dialog.text = "" + sStr + ". Thank you for the conversation, Captain. It was truly interesting.";
			link.l1 = "Thank you, too. "+Goodbye()+".";
			link.l1.go = "LadyBeth_DialogInCity_Second_5";
		break;
		
		case "LadyBeth_DialogInCity_Second_5":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Third = true;
		break;
		
		case "LadyBeth_DialogInCity_Third_2": // третий диалог
			dialog.text = "Ah, "+pchar.name+"! Glad to see you. I have excellent news - I've finally found a solution to my problems. Soon I'll set off on an expedition, and this time I'll return with a real treasure! By the way, a friendly piece of advice - stay away from Cayman. It's now my territory.";
			link.l1 = "Cayman doesn't belong to you, Albert. You don't have crown rights to it. That's piracy.";
			link.l1.go = "LadyBeth_DialogInCity_Third_3_harizma";
			link.l2 = "Are you threatening me, Blackwood?";
			link.l2.go = "LadyBeth_DialogInCity_Third_3_oruzhie";
		break;
		
		case "LadyBeth_DialogInCity_Third_3_harizma":
			dialog.text = "Crown rights? You should have lived in the slums of Bristol, "+pchar.name+", then you'd understand what these papers are worth. When you're hungry, the law is meaningless. However... you're right. Formally, I have no rights to the island. But I've found there what I've been seeking for years. And I won't let anyone take it away.";
			link.l1 = "I hope you understand that you're on a dangerous path.";
			link.l1.go = "LadyBeth_DialogInCity_Third_3_harizma_2";
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;
		
		case "LadyBeth_DialogInCity_Third_3_harizma_2":
			dialog.text = "I always understood that my road wouldn't be easy. Farewell, "+pchar.name+". Perhaps we'll meet again.";
			link.l1 = ""+Goodbye()+".";
			link.l1.go = "LadyBeth_DialogInCity_Third_4";
		break;
		
		case "LadyBeth_DialogInCity_Third_3_oruzhie":
			dialog.text = "Threatening? No, not at all. Just a friendly advice from one captain to another. Cayman is dangerous... especially for those who interfere in my affairs.";
			link.l1 = "I'll remember your 'advice'. Good luck on Cayman.";
			link.l1.go = "LadyBeth_DialogInCity_Third_3_oruzhie_2";
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "LadyBeth_DialogInCity_Third_3_oruzhie_2":
			dialog.text = "And good luck to you, Captain. I hope you won't need it. Farewell.";
			link.l1 = ""+Goodbye()+".";
			link.l1.go = "LadyBeth_DialogInCity_Third_4";
		break;
		
		case "LadyBeth_DialogInCity_Third_4":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Fourth = true;
		break;
		
		// Ловушка, абордаж в каюте
		case "LadyBeth_abordage":
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Second"))
			{
				dialog.text = "You?!! Think I'll surrender? Think I'll return to poverty? I'd rather die than starve in the slums again! No mercy, no reward, no victory! Under the bunk there's a powder keg... We'll all go to the bottom!";
				link.l1 = "...";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("LadyBeth_Lovushka");
			}
			else
			{
				dialog.text = "Who are you to attack me?! Think I'll surrender? No! I'd rather die than starve in the slums again! No mercy, no reward, no victory! Under the bunk there's a powder keg... We'll all go to the bottom!";
				link.l1 = "...";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("LadyBeth_Lovushka");
			}
		break;
		
		// Блеквуд разговаривает с ГГ перед битвой на Каймане
		case "LadyBeth_BlackWood_Boss":
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Second"))
			{
				dialog.text = "Captain! I warned you. Now you'll pay for your curiosity.";
			}
			else
			{
				dialog.text = "Who are you and how dare you invade my territory?! This island is mine!";
			}
			link.l1 = "We'll see, Blackwood. Today there will be one obsessed man less in this world.";
			link.l1.go = "LadyBeth_BlackWood_Boss_oruzhie_1";
			link.l2 = "Let's resolve this peacefully, Blackwood. I can leave.";
			link.l2.go = "LadyBeth_BlackWood_Boss_torgovlya_1";
			link.l3 = "Blackwood, you're a reasonable man! You're an officer! You have the royal flag flying over your camp, for God's sake! Can't we come to an agreement?";
			link.l3.go = "LadyBeth_BlackWood_Boss_harizma_1";
		break;
		
		case "LadyBeth_BlackWood_Boss_oruzhie_1":
			dialog.text = "Obsessed? Ha! I'm just a man who knows what he wants!";
			link.l1 = "...";
			link.l1.go = "LadyBeth_BlackWood_Boss_2";
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "LadyBeth_BlackWood_Boss_torgovlya_1":
			dialog.text = "Leave? After what you've seen? No, no, no! No one should know about what I've found here. No one!";
			link.l1 = "I give you my word that I won't tell anyone. I swear by a captain's honor.";
			link.l1.go = "LadyBeth_BlackWood_Boss_torgovlya_2";
			AddCharacterExpToSkill(pchar, "Commerce", 200);
		break;
		
		case "LadyBeth_BlackWood_Boss_torgovlya_2":
			dialog.text = "There is no honor in this world, Captain. There's only filth, poverty, and contempt. I regret it, but you must die here.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_BlackWood_Boss_2";
		break;
		
		case "LadyBeth_BlackWood_Boss_harizma_1":
			dialog.text = "I've thought. Thought a lot. And realized - this is my only chance. Either I find Cortez's gold, or... nothing. Understand? NOTHING! I won't return to my former life! Won't return to filth and poverty! Better to die here!";
			link.l1 = "...";
			link.l1.go = "LadyBeth_BlackWood_Boss_2";
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;
		
		case "LadyBeth_BlackWood_Boss_2":
			dialog.text = "To battle! Bullock, Fraser - fire grapeshot if they approach! Hopkins, charge!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_CaimanKino_11");
		break;
		
		// Диалоги с офицерами
		case "LadyBeth_Helena_1": // Элен
			dialog.text = "Are you all right?";
			link.l1 = "Yes, everything's fine. And you?";
			link.l1.go = "LadyBeth_Helena_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Helena_2":
			dialog.text = "Alive. But these land battles aren't for me. Give me a deck under my feet and I'll tear apart any ship, but here... strange place. To make a hundred sea wolves come ashore, swing picks, build fortifications... I couldn't do that.";
			link.l1 = "Blackwood knew how to inspire his crew.";
			link.l1.go = "LadyBeth_Helena_3";
		break;
		
		case "LadyBeth_Helena_3":
			dialog.text = "I heard about him back in Bluefield. Many English sailors spoke of him with respect. The best officer in the fleet, a brilliant career... and suddenly he threw it all away to hunt for treasures.";
			link.l1 = "What do you think of him?";
			link.l1.go = "LadyBeth_Helena_4";
		break;
		
		case "LadyBeth_Helena_4":
			dialog.text = "I think that Blackwood's example clearly shows the burden of responsibility that we... I mean you, bear before... your men. Please, don't become the same kind of captain he became.";
			link.l1 = " I'll try, Helen.";
			link.l1.go = "LadyBeth_Helena_5";
		break;
		
		case "LadyBeth_Helena_5":
			dialog.text = "Thank you, my Captain. I know you'll succeed.";
			link.l1 = "We will.";
			link.l1.go = "LadyBeth_Helena_6";
		break;
		
		case "LadyBeth_Helena_6":
			dialog.text = "We will.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_Helena_7";
		break;
		
		case "LadyBeth_Helena_7":
			DialogExit();
			Return_HelenaOfficer();
		break;
		
		case "LadyBeth_Mary_1": // Мэри
			dialog.text = "Charles... how dreadful it is here.";
			link.l1 = "Are you all right, Mary? You held up like a real soldier.";
			link.l1.go = "LadyBeth_Mary_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Mary_2":
			dialog.text = "No, I'm not all right, alright. Look at these people! They worked to exhaustion, lived in hunger, died of diseases... And for what? For gold that might not even exist.";
			link.l1 = "Blackwood believed it was here.";
			link.l1.go = "LadyBeth_Mary_3";
		break;
		
		case "LadyBeth_Mary_3":
			dialog.text = "This red coat... exactly like mine. An English officer... You know, I suddenly thought about my parents, alright. About my roots... about what I never knew. Maybe I'm also one of those?";
			link.l1 = "One of those?";
			link.l1.go = "LadyBeth_Mary_4";
		break;
		
		case "LadyBeth_Mary_4":
			dialog.text = "Those who seek something that might not even exist. And then lose themselves in the search. I... I'd like to talk about this later, alright. When we leave this terrible place.";
			link.l1 = "Of course, Mary.";
			link.l1.go = "LadyBeth_Mary_5";
		break;
		
		case "LadyBeth_Mary_5":
			dialog.text = "Let's bury him first, please? Even if he doesn't deserve it. For the sake of the man he once was.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_Mary_6";
		break;
		
		case "LadyBeth_Mary_6":
			DialogExit();
			Return_MaryOfficer();
		break;
		
		case "LadyBeth_Tichingitu_1": // Тичингиту
			dialog.text = "Captain, Tichingitu see bad place here. Very bad place.";
			link.l1 = "What do you mean?";
			link.l1.go = "LadyBeth_Tichingitu_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Tichingitu_2":
			dialog.text = "This island now be cursed. Land absorb too much blood and tears. Everyone who dig here, breathe this curse.";
			link.l1 = "You think Blackwood was possessed?";
			link.l1.go = "LadyBeth_Tichingitu_3";
		break;
		
		case "LadyBeth_Tichingitu_3":
			dialog.text = "Not just possessed. He be... how to say... empty vessel. Something enter him and push out his soul. Me see this before. When shaman of my tribe bring human sacrifice to spirits. That shaman have same look.";
			link.l1 = "But what could cause such an obsession?";
			link.l1.go = "LadyBeth_Tichingitu_4";
		break;
		
		case "LadyBeth_Tichingitu_4":
			dialog.text = "Man with emptiness inside easy to fill with other thoughts. Someone find his weakness and use it. Tichingitu almost feel sorry for this man.";
			link.l1 = "Almost?";
			link.l1.go = "LadyBeth_Tichingitu_5";
		break;
		
		case "LadyBeth_Tichingitu_5":
			dialog.text = "Yes, almost. Every warrior responsible for own choice. Even if demons whisper in his ear.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_Tichingitu_6";
		break;
		
		case "LadyBeth_Tichingitu_6":
			DialogExit();
			Return_TichingituOfficer();
		break;
		
		case "LadyBeth_Irons_1": // Томми
			dialog.text = "Damn it, Captain! Just look at this! Just like the good old days!";
			link.l1 = "You know well what war on land is like.";
			link.l1.go = "LadyBeth_Irons_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Irons_2":
			dialog.text = "Reminds me of the Battle of Naseby. Our wing of cavalry clashed with Rupert's cavalrymen. They fought with the same ferocity for their king.";
			link.l1 = "What do you think of Blackwood?";
			link.l1.go = "LadyBeth_Irons_3";
		break;
		
		case "LadyBeth_Irons_3":
			dialog.text = "This Blackwood was either a genius or a complete whackjob. I think both. You know what surprises me? His men. Many of them are former military. Not some street rats, but real thing. And they all followed him in this madness. Even Fox's marine infantry. Ha! Now there's someone who'll be delighted with today's carnage! He never forgave them for deserting.";
			link.l1 = "Maybe it's about the money?";
			link.l1.go = "LadyBeth_Irons_4";
		break;
		
		case "LadyBeth_Irons_4":
			dialog.text = "Nah, there's something else. This guy had power over them. Real power. And I also heard he was engaged to some rich girl from Barbados. Strange that he didn't marry her after getting all these treasures. Typical soldier - didn't know when to end the war.";
			link.l1 = "Thank you, Tommy. You're a real thinker.";
			link.l1.go = "LadyBeth_Irons_5";
		break;
		
		case "LadyBeth_Irons_5":
			dialog.text = "Huh?";
			link.l1 = "Nothing.";
			link.l1.go = "LadyBeth_Irons_6";
		break;
		
		case "LadyBeth_Irons_6":
			DialogExit();
			Return_IronsOfficer();
		break;
		
		case "LadyBeth_Knippel_1": // Книппель
			dialog.text = "How bitter it is to see this, Captain. What have we sunk to?!";
			link.l1 = "We?";
			link.l1.go = "LadyBeth_Knippel_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Knippel_2":
			dialog.text = "The English fleet! Just look: tiny dots of red coats lying in a pile of this dead scum!";
			link.l1 = "Some of that 'scum' are our people, Charlie. I understand your feelings, but...";
			link.l1.go = "LadyBeth_Knippel_3";
		break;
		
		case "LadyBeth_Knippel_3":
			dialog.text = "Fuck that, sir!";
			link.l1 = "I understand your feelings, but you'd better direct your anger and disappointment at Blackwood. He's the one who deserted from your beloved English fleet and led them here.";
			link.l1.go = "LadyBeth_Knippel_4";
			link.l2 = "Indeed. Let's go, the day isn't over yet.";
			link.l2.go = "LadyBeth_Knippel_6";
		break;
		
		case "LadyBeth_Knippel_4":
			dialog.text = "They were just following their commander!";
			link.l1 = "Like you followed Fleetwood?";
			link.l1.go = "LadyBeth_Knippel_5";
			link.l2 = "Indeed. Let's go, the day isn't over yet.";
			link.l2.go = "LadyBeth_Knippel_6";
		break;
		
		case "LadyBeth_Knippel_5":
			dialog.text = "Like I follow you!";
			link.l1 = "I hope I'll prove to be a better captain than Blackwood and Fleetwood. Let's go, the day isn't over yet.";
			link.l1.go = "LadyBeth_Knippel_6";
		break;
		
		case "LadyBeth_Knippel_6":
			dialog.text = "Aye, Captain. And when it ends - I'll drink until the next one ends.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_Knippel_7";
		break;
		
		case "LadyBeth_Knippel_7":
			DialogExit();
			Return_KnippelOfficer();
		break;
		
		case "LadyBeth_Alonso_1": // Алонсо
			dialog.text = "Madre de Dios, Captain! Are you all right?";
			link.l1 = "That remains to be seen. How many men did we lose?";
			link.l1.go = "LadyBeth_Alonso_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Alonso_2":
			
			dialog.text = "Killed? In this venture we lost "+sti(pchar.SailorDiedInBattleInfo)+" men. Don't want to seem intrusive, Captain, but... I warned you!";
			link.l1 = "I'll ignore that remark because today you proved yourself, Alonso. Where did you get so many talents?";
			link.l1.go = "LadyBeth_Alonso_3";
		break;
		
		case "LadyBeth_Alonso_3":
			dialog.text = "One day I'll tell you that story, Captain - if we live long enough, of course.";
			link.l1 = "Any more valuable advice?";
			link.l1.go = "LadyBeth_Alonso_4";
		break;
		
		case "LadyBeth_Alonso_4":
			dialog.text = "If there were treasures here - they'd have found them long ago. But we should still search the island and find survivors, then decide what to do with them. And we shouldn't forget about Blackwood's ship: I've heard only good things about that beauty of a snow. It would be a shame to miss such a prize, Captain. Of course, I'm merely conveying the crew's position on this matter.";
			link.l1 = "Of course. Let's go. The spoils await!";
			link.l1.go = "LadyBeth_Alonso_5";
		break;
		
		case "LadyBeth_Alonso_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
		break;
		
		// Диалог с матросом в гроте Каймана
		case "LadyBeth_MatrosyInGrot":
			dialog.text = "Don't shoot! We surrender!";
			link.l1 = "Who are you?";
			link.l1.go = "LadyBeth_MatrosyInGrot_2";
		break;
		
		case "LadyBeth_MatrosyInGrot_2":
			dialog.text = "We... we're from the 'Lady Beth'. Captain Blackwood's crew. Is he... is he alive?";
			link.l1 = "No. Your captain is dead.";
			link.l1.go = "LadyBeth_MatrosyInGrot_3";
		break;
		
		case "LadyBeth_MatrosyInGrot_3":
			dialog.text = "So it's all over... Thank God.";
			link.l1 = "You don't seem to be mourning your captain.";
			link.l1.go = "LadyBeth_MatrosyInGrot_4";
		break;
		
		case "LadyBeth_MatrosyInGrot_4":
			dialog.text = "You don't understand. Blackwood was a great man. The best captain I ever knew. But in recent months... he changed. Became obsessed, cruel. Made us work day and night, looking for something that might not even exist.";
			link.l1 = "I'm taking you into my crew. We need experienced sailors.";
			link.l1.go = "LadyBeth_MatrosyInGrot_PlusKomanda";
			link.l2 = "Woe to the vanquished, lads. Now your place is in my hold. If you're lucky - you'll live to see some plantation on Barbados.";
			link.l2.go = "LadyBeth_MatrosyInGrot_PlusRaby";
		break;
		
		case "LadyBeth_MatrosyInGrot_PlusKomanda":
			dialog.text = "Really? You're... you're not afraid that we... that there's something wrong with us after all this?";
			link.l1 = "Everyone deserves a second chance.";
			link.l1.go = "LadyBeth_MatrosyInGrot_PlusKomanda_1";
		break;
		
		case "LadyBeth_MatrosyInGrot_PlusKomanda_1":
			dialog.text = "Thank you, Captain. I swear, you won't regret it. We're good sailors. And... maybe now the nightmares will stop.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_Grot_MatrosySdautsya_2");
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			pchar.Ship.Crew.Quantity = sti(pchar.ship.Crew.Quantity) + 30;
		break;
		
		case "LadyBeth_MatrosyInGrot_PlusRaby":
			dialog.text = "Thank you, thank you! At least we'll be alive. Get us out of here, please. This island... it's as if it's cursed.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_Grot_MatrosySdautsya_2");
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			SetCharacterGoods(pchar, GOOD_SLAVES, GetCargoGoods(pchar, GOOD_SLAVES)+30);
		break;
		
		case "LadyBeth_MatrosyInGrot_exit":
			DialogExit();
			for (i=1; i<=8; i++)
			{
				sld = CharacterFromID("LadyBeth_MatrosyPryachutsya_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "OpenTheDoors", 5);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
		break;
		
		// Диалог с матросом на Леди Бет
		case "LadyBeth_EnemyMatros_1":
			dialog.text = "What the hell?! How dare you attack the 'Lady' and kill Jeremy? You won't get out of here alive, you scoundrels, the captain will return and...";
			link.l1 = "Your captain is dead. Jeremy fired first, and I'm taking your 'Lady' as a lawful prize paid for with blood.";
			link.l1.go = "LadyBeth_EnemyMatros_2";
		break;
		
		case "LadyBeth_EnemyMatros_2":
			dialog.text = "The captain... dead? You're lying, dog! You're not worth a button on his uniform!";
			link.l1 = "If that uniform meant anything, it was to the Blackwood who's long gone. It's your choice - fight for a dead man or save your lives.";
			link.l1.go = "LadyBeth_EnemyMatros_3";
		break;
		
		case "LadyBeth_EnemyMatros_3":
			if (CharacterIsHere("Helena"))
			{
				StartInstantDialog("Helena", "LadyBeth_EnemyMatros_Helena_1", "Quest\LadyBeth_dialog.c");
				break;
			}
			if (CharacterIsHere("Knippel"))
			{
				StartInstantDialog("Knippel", "LadyBeth_EnemyMatros_Knippel_1", "Quest\LadyBeth_dialog.c");
				break;
			}
			if (CharacterIsHere("Irons"))
			{
				StartInstantDialog("Irons", "LadyBeth_EnemyMatros_Irons_1", "Quest\LadyBeth_dialog.c");
				break;
			}
			dialog.text = "We won't give you the ship without a fight!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_ShipInShore_Bitva");
		break;
		
		case "LadyBeth_EnemyMatros_Helena_1":
			dialog.text = "Listen, guys. I know you're loyal to your captain. That's worthy of respect. But he's dead, and you're alive. And you must decide how to live on. We're offering you a chance to start anew.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_EnemyMatros_5";
			CharacterTurnByChr(npchar, CharacterFromID("LadyBeth_CrewOfShip_7"));
		break;
		
		case "LadyBeth_EnemyMatros_Knippel_1":
			dialog.text = "Captain, these men aren't enemies. They were just following orders. Many of them are former royal sailors, well-trained and disciplined. It would be wasteful not to use their skills. Lads, I've been in your place more than once in my long service in the fleet. And I made the right choice. Make it too.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_EnemyMatros_5";
		break;
		
		case "LadyBeth_EnemyMatros_Irons_1":
			dialog.text = "Well, sailor boys! The choice is simple - either you live, either as prisoners in the hold or joining our crew with good rations and regular pay, or... (draws finger across throat) I'd choose the first if I were you!";
			link.l1 = "...";
			link.l1.go = "LadyBeth_EnemyMatros_10";
			CharacterTurnByChr(npchar, CharacterFromID("LadyBeth_CrewOfShip_7"));
		break;
		
		case "LadyBeth_EnemyMatros_5":
			StartInstantDialog("LadyBeth_CrewOfShip_7", "LadyBeth_EnemyMatros_6", "Quest\LadyBeth_dialog.c");
		break;
		
		case "LadyBeth_EnemyMatros_6":
			dialog.text = "...";
			link.l1 = "You'll become part of my crew.";
			link.l1.go = "LadyBeth_EnemyMatros_7";
			link.l2 = "Woe to the vanquished, lads. Now your place is in my hold. If you're lucky - you'll live to see some plantation on Barbados.";
			link.l2.go = "LadyBeth_EnemyMatros_9";
		break;
		
		case "LadyBeth_EnemyMatros_7":
			dialog.text = "You're taking us into your crew? After all this?";
			link.l1 = "Good sailors are always valuable. And Captain Blackwood knew how to choose his men.";
			link.l1.go = "LadyBeth_EnemyMatros_8";
		break;
		
		case "LadyBeth_EnemyMatros_8":
			dialog.text = "Thank you, Captain. We won't let you down.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_ShipInShore_Vnutri_1");
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			pchar.Ship.Crew.Quantity = sti(pchar.ship.Crew.Quantity) + 12;
		break;
		
		case "LadyBeth_EnemyMatros_9":
			dialog.text = "Well... at least that's the only way this adventure could have ended. Forgive us, Captain Blackwood. We didn't protect you.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_ShipInShore_Vnutri_1");
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			SetCharacterGoods(pchar, GOOD_SLAVES, GetCargoGoods(pchar, GOOD_SLAVES)+12);
		break;
		
		case "LadyBeth_EnemyMatros_10":
			StartInstantDialog("LadyBeth_CrewOfShip_7", "LadyBeth_EnemyMatros_11", "Quest\LadyBeth_dialog.c");
		break;
		
		case "LadyBeth_EnemyMatros_11":
			dialog.text = "We won't give you the ship without a fight!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_ShipInShore_Bitva");
		break;
		
		// Диалог с Элизабет Бишоп
		case "LadyBeth_Elizabeth_1":
			dialog.text = "...";
			link.l1 = "Excuse me. Are you Elizabeth?";
			if (pchar.sex == "man") link.l1.go = "LadyBeth_Elizabeth_2";
			if (pchar.sex == "woman") link.l1.go = "LadyBeth_Elizabeth_Woman_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Elizabeth_2":
			dialog.text = "Yes, that's me. And who are you?";
			link.l1 = "Captain "+GetFullName(pchar)+". I... knew Albert Blackwood.";
			link.l1.go = "LadyBeth_Elizabeth_3";
		break;
		
		case "LadyBeth_Elizabeth_3":
			dialog.text = "My Albert? Oh my God... Is he... is he all right?";
			link.l1 = "Unfortunately, no. He died in battle. Fought to the last.";
			link.l1.go = "LadyBeth_Elizabeth_4";
		break;
		
		case "LadyBeth_Elizabeth_4":
			dialog.text = "I... I suspected so. So many years without a single word... You know, I waited for him. Waited a long time. Father said Albert just needed to wait for a promotion. The governor had already decided everything, it was a matter of a few months. But Albert... he took that conversation quite differently. Said he would return wealthy, worthy of my hand. And he left. Just... left.";
			link.l1 = "He thought of you until his last day.";
			link.l1.go = "LadyBeth_Elizabeth_5";
		break;
		
		case "LadyBeth_Elizabeth_5":
			dialog.text = "How foolish. I didn't need his treasures. I loved him, not his money. I was ready to run away with him... but he was so proud. I waited for a letter, any word... And then only this strange manual arrived. Such a cold, calculating document... not at all like the Albert I knew. That's when I realized I had lost him.";
			link.l1 = "Among his things, I found this.";
			link.l1.go = "LadyBeth_Elizabeth_6";
		break;
		
		case "LadyBeth_Elizabeth_6":
			dialog.text = "A map to my house? I was his main treasure? What irony. He searched for riches all over the Caribbean, and the only thing that mattered to him was always here... Wait. I have something for you. This is Albert's manual. He sent it to me a year ago. Said it would help him find treasures and return to me. Now it will be more useful to you.";
			link.l1 = "Thank you, Elizabeth. I'm sorry it all turned out this way.";
			link.l1.go = "LadyBeth_Elizabeth_7";
			GiveItem2Character(PChar, "talisman18");
		break;
		
		case "LadyBeth_Elizabeth_7":
			dialog.text = "And I got married, Captain. To Mr. Bishop. Father insisted. You don't know this man... and you wouldn't want to. Every day I think about how my life would have been if Albert had just... returned.";
			link.l1 = "Now I'll think about that too.";
			link.l1.go = "LadyBeth_Elizabeth_8";
		break;
		
		case "LadyBeth_Elizabeth_8":
			dialog.text = "Goodbye, Captain. And... take care of yourself. Don't chase ghosts.";
			link.l1 = ""+Goodbye()+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_Barbados_Elizabeth_2");
		break;
		
		case "LadyBeth_Elizabeth_Woman_2":
			dialog.text = "Yes, that's me.";
			link.l1 = " Captain Helen MacArthur. I... knew Albert Blackwood.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_3";
		break;
		
		case "LadyBeth_Elizabeth_Woman_3":
			dialog.text = "My Albert? Oh my God... He... And who are you?";
			link.l1 = "Captain Helen MacArthur, I just said. I command my own ship.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_4";
		break;
		
		case "LadyBeth_Elizabeth_Woman_4":
			dialog.text = "Captain? A woman captain? You... You were with Albert? In what sense... knew him?";
			link.l1 = "Only as a captain. I'm sorry, but Albert is dead. I witnessed his final battle.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_5";
		break;
		
		case "LadyBeth_Elizabeth_Woman_5":
			dialog.text = "I understand. Forgive my suspicions. It's just... Captain Blackwood always attracted women's attention. Even here, on Barbados. Especially here.";
			link.l1 = "You loved him.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_6";
		break;
		
		case "LadyBeth_Elizabeth_Woman_6":
			dialog.text = "With all my heart. Father said Albert only needed to wait for a promotion. It was a matter of a few months. But he understood father's words as a refusal due to poverty. Said he would return with treasures. And he left.";
			link.l1 = "Men and their pride!";
			link.l1.go = "LadyBeth_Elizabeth_Woman_7";
		break;
		
		case "LadyBeth_Elizabeth_Woman_7":
			dialog.text = "You're lucky, Captain MacArthur. You're free. You sail wherever you want. No plantation owners, no fathers deciding your fate. No husbands considering you their property.";
			link.l1 = "Freedom comes at a high price. And you have to defend it every day.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_8";
		break;
		
		case "LadyBeth_Elizabeth_Woman_8":
			dialog.text = "I may have something that will help you in this matter. Here, take it. This is his treasure hunting manual. Albert sent it to me about a year ago. Said it was the best thing he'd ever created. That it would help him get rich and return to me. But with each page, he less and less resembled the Albert I knew.";
			link.l1 = "Thank you. I'll keep it.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_9";
			GiveItem2Character(PChar, "talisman18");
		break;
		
		case "LadyBeth_Elizabeth_Woman_9":
			dialog.text = "Please, Captain... value your freedom. I married Colonel Bishop. A man even my father fears. If I were free, like you... Everything would be different.";
			link.l1 = "I know.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_10";
		break;
		
		case "LadyBeth_Elizabeth_Woman_10":
			dialog.text = "Farewell, Captain. And fair winds to you.";
			link.l1 = ""+Goodbye()+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_Barbados_Elizabeth_2");
		break;
		
		// диалог с Диего де Ланда
		case "LadyBeth_DiegoDeLanda_1":
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 1)
			{
				dialog.text = "Have you seen Lady Bishop? A sad story, isn't it?";
				link.l1 = "Who are you?";
				link.l1.go = "LadyBeth_DiegoDeLanda_First_1";
			}
			else
			{
				dialog.text = "Hello, Captain.";
				link.l1 = "Wait! We've met before! What are you doing in Barbados?";
				link.l1.go = "LadyBeth_DiegoDeLanda_Second_1";
			}
		break;
		
		case "LadyBeth_DiegoDeLanda_First_1":
			dialog.text = "\nI serve the parish of Saint Mary. Few Catholics in Barbados find solace in our church.";
			link.l1 = "Do you know Elizabeth?";
			link.l1.go = "LadyBeth_DiegoDeLanda_First_2";
		break;
		
		case "LadyBeth_DiegoDeLanda_First_2":
			dialog.text = "Oh, yes. Poor woman. Her husband... is not the kindest man. They say his plantations are the most productive on Barbados. And the cruelest. Do you know how many slaves die there each month? Recently he beat to death a real doctor from England - a man of great intellect and talent. But her fate is not much better, believe me.";
			link.l1 = "You seem well-informed.";
			link.l1.go = "LadyBeth_DiegoDeLanda_First_3";
		break;
		
		case "LadyBeth_DiegoDeLanda_First_3":
			dialog.text = "People come to me for confession, Captain. I hear what they're afraid to tell even to their loved ones. Their fears, their sins... their pain.";
			link.l1 = "Aren't you afraid of persecution? It's not easy for a Catholic priest in English territories.";
			link.l1.go = "LadyBeth_DiegoDeLanda_First_4";
		break;
		
		case "LadyBeth_DiegoDeLanda_First_4":
			dialog.text = "Tell me... did you specifically look for Blackwood? Curious. But why? It was dangerous and foolish. What is your fire, Captain? What drives you?";
			link.l1 = "That's none of your business.";
			link.l1.go = "LadyBeth_DiegoDeLanda_First_5";
		break;
		
		case "LadyBeth_DiegoDeLanda_First_5":
			dialog.text = "I can't understand. The others - I can. But you - not yet.";
			link.l1 = "Others?";
			link.l1.go = "LadyBeth_DiegoDeLanda_First_6";
		break;
		
		case "LadyBeth_DiegoDeLanda_First_6":
			dialog.text = "One, for example, strives for justice. Or there was another... obsessed with the dark waters of death. People so easily lose themselves in their desires. Isn't that true?";
			link.l1 = "You're a strange priest, Holy Father.";
			link.l1.go = "LadyBeth_DiegoDeLanda_First_7";
		break;
		
		case "LadyBeth_DiegoDeLanda_First_7":
			dialog.text = "...";
			link.l1 = "I think I'll go now.";
			link.l1.go = "LadyBeth_DiegoDeLanda_First_8";
		break;
		
		case "LadyBeth_DiegoDeLanda_First_8":
			dialog.text = "Of course. Your work is just beginning, Captain.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_Barbados_Diego_2");
		break;
		
		case "LadyBeth_DiegoDeLanda_Second_1":
			dialog.text = "I serve the parish of Saint Mary. Have you seen Lady Bishop? A sad fate. But, I fear, a deserved one.";
			link.l1 = "Last time you spoke in riddles. Will you do so again?";
			link.l1.go = "LadyBeth_DiegoDeLanda_Second_2";
		break;
		
		case "LadyBeth_DiegoDeLanda_Second_2":
			dialog.text = "\nThe real riddle stands before me now. You've collected many interesting... relics. Bible. Charter. Do you like collecting such things? Are you a collector?";
			link.l1 = "How do you know about the manual?";
			link.l1.go = "LadyBeth_DiegoDeLanda_Second_3";
		break;
		
		case "LadyBeth_DiegoDeLanda_Second_3":
			dialog.text = "A trophy hunter?";
			link.l1 = "I repeat my question: how do you know about the manual?";
			link.l1.go = "LadyBeth_DiegoDeLanda_Second_4";
		break;
		
		case "LadyBeth_DiegoDeLanda_Second_4":
			dialog.text = "A thrill-seeker?";
			link.l1 = "...";
			link.l1.go = "LadyBeth_DiegoDeLanda_Second_5";
		break;
		
		case "LadyBeth_DiegoDeLanda_Second_5":
			dialog.text = "\nAh. Of course. Certainly. Well, Captain, I won't keep you.";
			link.l1 = "Wait a moment, Holy Father. You still haven't answered my question.";
			link.l1.go = "LadyBeth_DiegoDeLanda_Second_6";
		break;
		
		case "LadyBeth_DiegoDeLanda_Second_6":
			dialog.text = "Oh, Captain. I can't. Sometimes answers hurt more than any ignorance. Go in peace. And take care of your collection... of trophies. They may be useful in the journey that awaits you.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_Barbados_Diego_2");
		break;
	}
} 
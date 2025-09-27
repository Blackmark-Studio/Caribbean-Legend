// Дональд Гринспи - лидер нарвалов
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "What? What do you want?";
				link.l1 = TimeGreeting()+". My name is "+GetFullName(pchar)+". I wanted to meet the leader of the clan.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! Want something?";
				link.l5 = "Just wanted to say hello. See you!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Now you know me. My name is Donald Greenspen, and don't make me or my men angry. And don't try to visit the 'San Gabriel' until you have a password. The shop is open to all; everyone needs to trade. Any questions?";
			link.l2 = "No, I got it. See you.";
			link.l2.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
	// ----------------------------------после разгрома Чада и Мэри на Каролине---------------------------
		case "shark":
			dialog.text = "What business do you have with me?";
			link.l1 = "A very unpleasant one, Donald. There was an attempt on Steven's life last night. Fighters from your clan were involved.";
			link.l1.go = "shark_1";
		break;
		
		case "shark_1":
			dialog.text = "I don't know about that. Why do you think they were my men?";
			link.l1 = "Because I was there. We are able to see the difference between your men, pirates, and Rivados. The group was led by Mary Casper and Chad Kapper. Do you need more evidence?";
			link.l1.go = "shark_2";
		break;
		
		case "shark_2":
			dialog.text = "I can only assure you that my men and I have nothing to do with it.";
			link.l1 = "You will have to assure the admiral of it, and it won't be easy. Dodson is very angry at all Narwhals after the attack. He is going to declare war on you – he will stop providing you with provisions and shoot your men whenever he gets the chance. And it's not just words.";
			link.l1.go = "shark_3";
		break;
		
		case "shark_3":
			dialog.text = "I hope the admiral knows what he's doing. Does he doubt that my men can shoot as well?";
			link.l1 = "I think he does. He is ready to turn the 'San Augustine' into a fortress and fight until you all starve. Besides, Dodson is going to talk with Rivados and offer them cooperation. You won't stand a chance against the admiral and Rivados together.";
			link.l1.go = "shark_4";
		break;
		
		case "shark_4":
			dialog.text = "Fuck! But we are not part of this attempt! Why must the whole clan pay for the actions of that stupid girl Mary and a bunch of scum from my crew?\nBesides, let's talk logic, by killing Marlow, Dodson himself provoked Mary and my soldiers. That's exactly what happens when you commit such meanness.";
			link.l1 = "You don't understand a thing. You've been fooled. Why are you so sure that Dodson killed Alan? In fact, he thinks you did it to take his position...";
			link.l1.go = "shark_5";
		break;
		
		case "shark_5":
			dialog.text = "I don't give a damn what he thinks. All the evidence is against him. Only he and his men had access to the prison. Alan was in his hands. Red Mary told me a lot. Before Alan was murdered, Dodson personally visited the prison, and he doesn't do it often.";
			link.l1 = "Have you seen him die?";
			link.l1.go = "shark_6";
		break;
		
		case "shark_6":
			dialog.text = "Rubbish! Of course I haven't.";
			link.l1 = "And Chimiset too. Yes, yes, Rivados' wizard who had been sitting next to Alan. He was also murdered there recently. I was in the prison a day before his death and spoke with him. Milrow was killed by Chad Kapper, the boatswain of the Shark.";
			link.l1.go = "shark_7";
		break;
		
		case "shark_7":
			dialog.text = "Is it true?";
			link.l1 = "Think about it: Chimiset didn't care about your relationship with the admiral. He had no reason to lie. The old wizard was afraid of Chad, he supposed he would be next. He was right, Chad murdered him as soon as he learned that the admiral was going to set him free.";
			link.l1.go = "shark_8";
		break;
		
		case "shark_8":
			dialog.text = "But why did Kapper want Alan's death?";
			link.l1 = "Damn, don't you really understand? I told you that Kapper was working with Red Mary. He wanted to take Shark's position and came up with a cunning plan to do so. Killing Alan Milrow and spreading rumours about Shark's involvement in his death made the Narwhal clan hostile towards the admiral...";
			link.l1.go = "shark_9";
		break;
		
		case "shark_9":
			dialog.text = "";
			link.l1 = "Silly girl Mary trusted him and sided with the real killer of her boyfriend. They persuaded a few Narwhals to join them; it must have been easy for Mary. Then they organised an attack on the admiral in Fazio's cabin, where he was forced to write an invitation to the admiral...";
			link.l1.go = "shark_10";
		break;
		
		case "shark_10":
			dialog.text = "";
			link.l1 = "I have a letter from Fazio that explains everything. Chimiset was killed by Chad as a dangerous witness. He was cooperating with the Narwhals, and Rivados would be very glad to hear that during their talk with Shark. We will easily prove to Black Eddie that Chad became one of your kind by showing this letter.";
			link.l1.go = "shark_11";
		break;
		
		case "shark_11":
			dialog.text = "Hm. You've got all the aces, so what are you doing here then? You want something from me, right?";
			link.l1 = "I do. Because I believe that it was all Chad's plan and you are not involved. Chad has cheated on Mary, she called her friends from your clan to help her, that's the whole story. At least, I haven't found any evidence against you or any other Narwhal...";
			link.l1.go = "shark_12";
		break;
		
		case "shark_12":
			dialog.text = "";
			link.l1 = "But it doesn't mean that there are no other plotters left. I want you to search for them. Then, perhaps, we will settle things without a slaughter.";
			link.l1.go = "shark_13";
		break;
		
		case "shark_13":
			dialog.text = "I have already told you that none of my men were involved. After Marlow's death, Mary essentially left the clan and locked herself in her cabin. Honestly, I have no idea how she managed to persuade others to take part in it, but it seems she succeeded. I swear that neither I nor anyone else from my clan is acting against the admiral. We have lost too many men recently, so we don't want to get involved in any messy business now. I am not afraid of the admiral's attack, even if he joins forces with the Rivados. The Narwhals are true warriors, and we will prove that in our last battle. But that would be pointless. We have already decided to keep the peace with the admiral. The Rivados are a different matter; we don't negotiate with Negros. I am ready to apologize to the admiral personally, to ask forgiveness for my suspicions caused by Milrow's death and for the attack on his life. I will swear on the Bible to prove my sincerity. Are you and Dodson fine with that?";
			link.l1 = "I am. Are you sure there are no tricks to be expected from your men?";
			link.l1.go = "shark_14";
		break;
		
		case "shark_14":
			dialog.text = "Absolutely. I will inform my clan about the real killer of Alan Milrow. My men's relationship with the admiral will change immediately, I assure you. Tell me, will a slaughter be necessary after that?";
			link.l1 = "No, it won't. I am here to prevent it. I trust you, Donald, and I will try to persuade Shark. I have a few arguments left... See you, Donald!";
			link.l1.go = "shark_15";
		break;
		
		case "shark_15":
			DialogExit();
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "narval"; // ноду Акуле
			AddQuestRecord("SharkHunt", "26");
			NextDiag.CurrentNode = "narval_wait";
		break;
		
		case "narval_wait":
			dialog.text = "Have you spoken to the admiral already? Any results?";
			link.l1 = "I am making progress. I will see you later...";
			link.l1.go = "exit";
			NextDiag.TempNode = "narval_wait";
		break;
		
		case "shark_16":
			dialog.text = "Have you spoken to the admiral already? Any results?";
			link.l1 = "Yes, I have. Your apology is accepted, and your clan's accusation is withdrawn. There is more: Shark invites you to meet him and discuss the terms of a future peace agreement between the Narwhals and the pirates.";
			link.l1.go = "shark_17";
		break;
		
		case "shark_17":
			dialog.text = "To be honest, I didn't expect... This is great news. Perhaps we will even be able to reconsider the prices for provisions for our clan and a new policy concerning Rivados.";
			link.l1 = "That concerns only you and the admiral.";
			link.l1.go = "shark_18";
		break;
		
		case "shark_18":
			dialog.text = "Yes, of course. You have done a great service to the Narwhal clan by preventing pointless bloodshed and perhaps even the total annihilation of my men. Take this tower musket as a token of my gratitude, you won't find another weapon of this kind\nBesides, you are allowed to visit our restricted areas just like any other clan member.";
			link.l1 = "Thanks! Farewell for now, I have a lot of things to do.";
			link.l1.go = "shark_19";
		break;
		
		case "shark_19":
			GiveItem2Character(pchar, "mushket6"); 
			Log_Info("You have received a tower mousqueton");
			PlaySound("interface\important_item.wav");
			dialog.text = "Good luck. See me if you have any questions.";
			link.l1 = "Got it. See you!";
			link.l1.go = "exit";
			CloseQuestHeader("SharkHunt");
			bDisableFastReload = false; // belamour legendary edition
			pchar.questTemp.LSC.nrv_friend = "true"; //флаг на проход по кораблям нарвалов
			NextDiag.TempNode = "grinspy_wait";
			for (i=1; i<=6; i++)
			{
				sld = CharacterFromID("NarvalSold_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("NarvalProt_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			AddSimpleRumourCityTip("They say that you are a friend of Donald, Greenspen, the leader of Narwhals. Well, Rivados hate you now...", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("They say that you are Narwhal now. Or do you serve under admiral's command? I don't get it...", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("I've heard that you have made peace between admiral and Narwhals. Hm, Rivados must be insane about that...", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("So Chad Kapper was a murderer of Alan Milrow! That is surprising!", "LostShipsCity", 5, 2, "LSC", "");
		break;
		
		case "grinspy_wait": // стал другом
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "Ho! "+GetFullName(pchar)+"! You are... no, it can't be! Are you alive?!";
				link.l1 = "Rumours of my death were a bit exaggerated, Donald. Ha-ha, glad to see you!";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			dialog.text = "A-ah, my friend "+GetFullName(pchar)+"! Need something?";
			link.l1 = "No, I don't. Just wanted to greet you.";
			link.l1.go = "exit";
			NextDiag.TempNode = "grinspy_wait";
		break;
		
		case "negotiations":
			dialog.text = "What business do you have with me?";
			link.l1 = "A very unpleasant one, Donald. There was an attempt on Steven's life. Fighters from your clan were involved.";
			link.l1.go = "negotiations_1";
		break;
		
		case "negotiations_1":
			dialog.text = "I don't know about that. Why do you think my men were involved?";
			link.l1 = "Because I personally killed a few of them along with Chad Kapper, the admiral's boatswain who is responsible for all of this mess. He wasn't able to do it on his own, so your men were helping him a lot. The admiral knows that and he is very, very angry.";
			link.l1.go = "negotiations_2";
		break;
		
		case "negotiations_2":
			dialog.text = "My men? Who exactly? Can you name them?";
			link.l1 = "They didn't introduce themselves. They were just shooting and fencing. Your people are reckless. They can even attack one of their own. Hell, with me or with the admiral, but to attempt to kill the girl?";
			link.l1.go = "negotiations_3";
		break;
		
		case "negotiations_3":
			dialog.text = "Hm. Who are you talking about?";
			if (pchar.questTemp.LSC.Mary == "alive")
			{
				link.l1 = "Who am I talking about? I am talking about the attack on Red Mary. Two Narwhals tried to kill her. I reached her cabin at a critical moment purely by accident. They would have killed her if I had come any later. I didn't ask their names, I'm sorry, I had no time to speak with them, but Mary said they were Narwhals.";
				link.l1.go = "negotiations_4";
			}
			else
			{
				link.l1 = "Who am I talking about? I am talking about the attack on Red Mary and those two Narwhals who killed her."link.l1.go ="negotiations_6";
			}
		break;
		
		case "negotiations_4":
			dialog.text = "What? Why didn't she tell me?! I would have acted at once!";
			link.l1 = "She was scared even to leave her cabin recently. She had an argument with you not long ago, so why should she run to you and ask for your help?";
			link.l1.go = "negotiations_5";
		break;
		
		case "negotiations_5":
			dialog.text = "I didn't argue with her! She demanded the impossible from me, we had a rough conversation and I sent her away. But it doesn't mean that I...";
			link.l1 = "Fine, whatever. After all, all problems are solved now. But there are bastards among your men, that is a fact.";
			link.l1.go = "negotiations_7";
		break;
		
		case "negotiations_6":
			dialog.text = "What? Was she killed by narwhals? Why?";
			link.l1 = "By the order of Chad Kapper, Donald. She knew too much and refused to help Chad. And now the poor girl is dead!";
			link.l1.go = "negotiations_7";
		break;
		
		case "negotiations_7":
			dialog.text = "I swear, I didn't know about it!";
			link.l1 = "Sure, you didn't... But let's talk about the admiral. Chad Kapper organised the attempt and your men helped him. They tried to poison Dodson and I barely prevented it.";
			link.l1.go = "negotiations_8";
		break;
		
		case "negotiations_8":
			dialog.text = "I didn't order anything like that. Dodson knows I don't support the late Alan's policy, and I think a lean compromise is better than a fat lawsuit.";
			link.l1 = "You will have to convince the admiral, and it won't be easy. Dodson is furious with all Narwhals after the attempt. He is going to declare war on you.";
			link.l1.go = "negotiations_9";
		break;
		
		case "negotiations_9":
			dialog.text = "I hope the admiral understands his actions. Does he doubt that my men can shoot back?";
			link.l1 = "He does. He thinks your clan is a bandit gang and must be destroyed before you start killing everyone. Besides, we have strong connections with Rivados. I can simply talk to Black Eddie and offer him an alliance. You won't stand against all of us.";
			link.l1.go = "negotiations_10";
		break;
		
		case "negotiations_10":
			if (pchar.questTemp.LSC.Mary == "alive") sTemp = "Call Red Mary if you don't believe me and ask her! She will confirm.";
			else sTemp = "I have a letter from Chad to Mary which proves everything.";
			dialog.text = "Fuck! Why does the whole clan have to pay for the actions of a few idiots? Don't think that I am scared. We are warriors, and we will prove that even in our last battle. But I want justice. Actually, the admiral is responsible for killing Alan Milrow in the prison.";
			link.l1 = "How can you be the leader, Donald... You know nothing about Mary or Alan. Chad Kapper killed him. "+sTemp+" He did that to turn the Narwhals against the admiral and draw some of them to his side.";
			link.l1.go = "negotiations_11";
		break;
		
		case "negotiations_11":
			dialog.text = "I see. Fine. Let's talk another way. You're here for a reason, right? What do you want?";
			link.l1 = "I don't want a bloody mess on the island. I don't want people to die. I don't like the idea of eliminating all Narwhals, though I assure you that Rivados and we are able to do that. I also think that the whole clan should not answer for the actions of a few bastards...";
			link.l1.go = "negotiations_12";
		break;
		
		case "negotiations_12":
			dialog.text = "";
			link.l1 = "But my vote won't be enough - you should officially assure the admiral that the attempt wasn't approved by you and your clan is not planning to kill Dodson.";
			link.l1.go = "negotiations_13";
		break;
		
		case "negotiations_13":
			dialog.text = "What can I do? I am ready to apologise for the attempt and for my suspicions about Marlow's death. I can assure him that the Narwhals are not planning anything against him, and I will swear on the Holy Bible. Will you and Dodson find that sufficient?";
			link.l1 = "I will. I am sure it will work for Dodson as well if you visit him personally. But first, I will tell him about your intentions and then visit you again with the results.";
			link.l1.go = "negotiations_14";
		break;
		
		case "negotiations_14":
			dialog.text = "Fine. I will wait.";
			link.l1 = "I'll be back soon...";
			link.l1.go = "negotiations_15";
		break;
		
		case "negotiations_15":
			DialogExit();
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "peace"; // ноду Акуле
			sld = characterFromId("Dexter");
			sld.dialog.currentnode = "First time"; 
			LAi_SetStayTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "SanAugustineResidence", "goto", "goto11");
			AddQuestRecord("SharkHunt", "56");
			NextDiag.CurrentNode = "narval_wait";
		break;
		
		case "negotiations_17":
			dialog.text = "Have you spoken to the admiral already? Any results?";
			link.l1 = "Yes, I have. If you pay him an official visit, then the problem is solved.";
			link.l1.go = "negotiations_18";
		break;
		
		case "negotiations_18":
			dialog.text = "To be honest, I didn't expect... This is great news.";
			link.l1 = "Yes, you know, I'm glad too.";
			link.l1.go = "negotiations_19";
		break;
		
		case "negotiations_19":
			dialog.text = "You have done a great service to the Narwhal clan by preventing a meaningless massacre and, perhaps, even the total extermination of my people. I grant you this tower musket - you won't find another weapon like it. You are also allowed to visit our ships without any limitations.";
			if (pchar.questTemp.LSC.Mary == "alive") 
			{
				link.l1 = "Thanks. A very valuable gift. Yes, Donald, one more thing: make peace with Red Mary. She is hot-tempered, but she is also sincere and honest. Arguing with you made her leave the clan, and it almost cost her her life.";
				link.l1.go = "negotiations_20";
			}
			else
			{
				link.l1 = "Thank you. This is a very valuable gift. And I am truly glad it ended so well.";
				link.l1.go = "negotiations_21";
			}
		break;
		
		case "negotiations_20":
			dialog.text = "Tell her that I ask her to forgive me for hurting her and for those two scum who dared to attack her. You both are... friends, am I right?";
			link.l1 = "You are right, Donald. I will tell her. And I am really glad that it all ended so well.";
			link.l1.go = "negotiations_21";
		break;
		
		case "negotiations_21":
			GiveItem2Character(pchar, "mushket6"); 
			Log_Info("You have received a tower musket");
			PlaySound("interface\important_item.wav");
			dialog.text = "Good luck. See me if you have any questions.";
			link.l1 = "Fine. Goodbye!";
			link.l1.go = "exit";
			CloseQuestHeader("SharkHunt");
			bDisableFastReload = false; // belamour legendary edition
			pchar.questTemp.LSC.nrv_friend = "true"; //флаг на проход по кораблям нарвалов
			NextDiag.TempNode = "grinspy_wait";
			sld = characterFromId("Mary");
			sld.quest.donald = "true";
			LocatorReloadEnterDisable("CeresSmithy", "reload3", false);
			LocatorReloadEnterDisable("CeresSmithy", "reload4", false); // открываем Церес изнутри
			for (i=1; i<=6; i++)
			{
				sld = CharacterFromID("NarvalSold_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("NarvalProt_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			// здесь почищу весь хлам, который накопился
			DeleteAttribute(pchar, "questTemp.LSC.Donald_enter"); // атрибут гардов
			DeleteAttribute(pchar, "questTemp.LSC.Florentina");
			DeleteAttribute(pchar, "questTemp.LSC.Dodson_poison");
			DeleteAttribute(pchar, "questTemp.LSC.Dodson_warning");
			DeleteAttribute(pchar, "questTemp.LSC.Whiskey_clear");
			DeleteAttribute(pchar, "questTemp.LSC.CapperDie_Aeva");
			AddSimpleRumourCityTip("They say that you are a friend of Donald, Greenspen, the leader of Narwhals. Well, Rivados hate you now...", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("They say that you are Narwhal now. Or do you serve under admiral's command? I don't get it...", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("I've heard that you have made peace between admiral and Narwhals. Hm, Rivados must be insane about that...", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("So Chad Kapper was a murderer of Alan Milrow! That is surprising!", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("Take care of Red Mary cause you are lucky to be with her - she is so reckless! She always gets in trouble...", "LostShipsCity", 20, 5, "LSC", "");
		break;
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("What are you doing there, eh? Thief!","Just look at that! As soon as I got lost in contemplation, you decided to check my chest!","Decided to check my chests? You won't get away with it!");
			link.l1 = "Shit!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "What?! Decided to check my chests? You won't get away with it!";
			link.l1 = "Foolish girl!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Listen, you'd better put your weapon away. It makes me nervous.","You know, running with a blade is not tolerated here. Take it away.","Listen, don't act like a medieval knight running around with a sword. Put it away, it doesn't suit you...");
			link.l1 = LinkRandPhrase("Fine.","Sure.","As you say...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Listen, I am a citizen of this city and I'd ask you to lower your blade.","Listen, I am a citizen of this city and I'd ask you to lower your blade.");
				link.l1 = LinkRandPhrase("Fine.","Sure.","As you say...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Be careful, pal, running around with a weapon. It makes me nervous...","I don't like it when men walk in front of me with their weapons drawn. It frightens me...");
				link.l1 = RandPhraseSimple("Got it.","I am taking it away.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

// Маркус Тиракс, барон Ла Веги
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc, sTemp;
	int i;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

// ------------------------------------------блок angry-----------------------------------------------
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
            switch (npchar.angry.kind) //сюда расписываем реакцию ангри. В npchar.angry.name пробелы удалены!!!
            {
                case "repeat":
                    if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
                    if (npchar.angry.name == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                break;
            }
        }
    }
// ------------------------------------------блок angry-----------------------------------------------

	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
			// Addon 2016-1 Jason пиратская линейка патч 17/1
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && !CheckAttribute(npchar, "quest.mtraxx_complete")) 
			{
				if (pchar.questTemp.Mtraxx == "full_complete_end" || pchar.questTemp.Mtraxx == "full_complete")
				{
					dialog.text = "Ah, Prince, you are finally here. At least one of you has bothered to show up! Work is waiting and all of you have disappeared! Where the hell is everyone?";
					link.l1 = "Not a clue... Marcus, I'm out. I've had enough. Dead men come to me in my dreams and Lucifer himself is breathing down my neck. Too much blood has been spilled recently.";
					link.l1.go = "mtraxx_113";
					break;
				}
			}
			// Jason НСО
			// если Сага завалена, то у Маркуса ноды в двух местах и оплата вперед
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && pchar.questTemp.Patria == "epizode_12_pirates")
			{
				dialog.text = "Got any 'jobs' for me?";
				link.l1 = "Greetings, Marcus. Yes, I have one 'affair'. Profitable and practical.";
				link.l1.go = "patria_x";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Condotier.NeedMoney") && pchar.questTemp.Patria == "epizode_12_pirates" && sti(pchar.money) >= 100000)
			{
				dialog.text = "Did you bring the money?";
				link.l1 = "I did.";
				link.l1.go = "patria_x8";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && pchar.questTemp.Patria == "epizode_12_talk")
			{
				dialog.text = "That's our customer! The job is done, your Baron is sitting in a well-guarded dungeon. Perhaps you'd like to take a look, he-he?!";
				link.l1 = "I will have plenty of time to do that, ha-ha. Is he being well-treated?";
				link.l1.go = "patria_10";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonFail"))
			{
				dialog.text = "Charles, what the hell?!";
				link.l1 = "Marcus, everything went wrong. I could neither come nor inform you...";
				link.l1.go = "patria_x33";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonAgain"))
			{
				dialog.text = "Here's our puppeteer!";
				link.l1 = "Ha-ha! The spectacle was perfect!";
				link.l1.go = "patria_x29";
				break;
			}
            dialog.text = NPCStringReactionRepeat(""+GetSexPhrase("Do you have anything to tell me? No? Then leave me alone!","Ha, "+pchar.name+"! Got any business with me? No? Then don't bother me.")+"","I thought I'd made myself clear... I told you to leave, but you keep annoying me!","Right, I am getting tired of this rudeness.","repeat",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("I am leaving already.","Sure, Marcus...","Sorry, Marcus...","Oops...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Are you insane? Wanted to play butcher, huh? All the pirates are angry with you, boy, you'd better leave this place...","It seems you've turned into a mad dog, boy. Wanted to stretch your hands a bit? No offence, but there's nothing for you here. Get lost!");
				link.l1 = RandPhraseSimple("Listen, I want to fix the situation.","Help me solve this problem, please...");
				link.l1.go = "pirate_town";
				break;
			}
			// Сага - завершаем искушение барбазона
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "terrax")
			{
				// Addon 2016-1 Jason пиратская линейка патч 17/1
				if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end")
				{
					link.l1 = "Marcus, will you ever stop being angry with me? I saved your friend Vincent, who raided Cartagena with us, and I saved your neck too! Or has Bernard not even told you?";
					link.l1.go = "Temptation_13";
				}
				else
				{
					link.l1 = "Why are you so rude, Marcus? Did Bernard not say anything about me?";
					link.l1.go = "Temptation";
				}
			}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "to_lavega")
			{
				link.l2 = "I'm looking for a job... Do you have anything profitable in mind?";
				link.l2.go = "Mtraxx";
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkTrade") && GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l2 = "I have some silk to sell.";
				link.l2.go = "Mtraxx_silktrade";
			}
			if (pchar.questTemp.Mtraxx == "silk_14")
			{
				link.l1 = "I've found you a buyer. He's a shipbuilder from Port Royal. He needs ship silk for his production and will be able to buy batches of one hundred rolls every month for 25 doubloons per roll. His men will collect the goods from the 10th to the 15th, at night, at Negril Cape. The password is 'A merchant of Lyons.' Bald Geffrey has already delivered the first batch to Jamaica.";
				link.l1.go = "mtraxx_13";
			}
			if (pchar.questTemp.Mtraxx == "silk_15")
			{
				link.l1 = "I've found you a buyer. He's a shipbuilder from Port Royal. He needs ship silk for his production and will be able to buy batches of one hundred rolls every month for 25 doubloons a roll. His men will receive the goods from the 10th to the 15th, at night, at Negril Cape. The password is 'A merchant of Lyons'. It took me more than two months to find such a buyer; Geffrey must have already sold the silk to smugglers. I am sorry, Marcus.";
				link.l1.go = "mtraxx_15";
			}
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

        case "I_know_you_good":
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Are you insane? Wanted to play the butcher? All the pirates are angry with you, boy, you'd better leave this place...","It seems you've turned into a mad dog, boy. Wanted to stretch your hands a bit? No offence, but there's no room for you here. Get lost!");
				link.l1 = RandPhraseSimple("Listen, I want to fix the situation...","Help me solve this problem, please...");
				link.l1.go = "pirate_town";
				break;
			}
			// Jason НСО
			if(!CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonFail"))
			{
				dialog.text = "Charles, what the hell?!";
				link.l1 = "Marcus, everything went wrong. I could neither come nor inform you...";
				link.l1.go = "patria_33";
				break;
			}
			if(!CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonAgain"))
			{
				dialog.text = "Glad to see you, friend!";
				link.l1 = "Glad to see you too. Thank you for the amazing spectacle!";
				link.l1.go = "patria_29";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax") && pchar.questTemp.Patria == "epizode_12_pirates")
			{
				dialog.text = "Glad to see you, boy! How can I help you?";
				link.l1 = "I have a proposal for you. Suits a pirate, you know!";
				link.l1.go = "patria";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax") && pchar.questTemp.Patria == "epizode_12_talk")
			{
				dialog.text = "That's our customer! The job is done, your Baron is sitting in a well-guarded dungeon. Perhaps you'd like to take a look, heh?!";
				link.l1 = "I will have plenty of time to do that, ha-ha. Is he being treated well?";
				link.l1.go = "patria_10";
				break;
			}
			// если Сага завалена, то у Маркуса ноды в двух местах и оплата вперед
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && pchar.questTemp.Patria == "epizode_12_pirates")
			{
				dialog.text = "Got any business for me?";
				link.l1 = "Greetings, Marcus. Yes, one affair. Profitable and piratical.";
				link.l1.go = "patria_x";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Condotier.NeedMoney") && pchar.questTemp.Patria == "epizode_12_pirates" && sti(pchar.money) >= 100000)
			{
				dialog.text = "Did you bring the money?";
				link.l1 = "I did.";
				link.l1.go = "patria_x8";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && pchar.questTemp.Patria == "epizode_12_talk")
			{
				dialog.text = "That's our customer! The job is done, your Baron is sitting in a well-guarded dungeon. Perhaps you'd like to take a look, he-he?!";
				link.l1 = "I will have plenty of time to do that, ha-ha. Is he being well treated?";
				link.l1.go = "patria_10";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonFail"))
			{
				dialog.text = "Charles, what the hell?!";
				link.l1 = "Marcus, everything went wrong. I could neither come nor inform you...";
				link.l1.go = "patria_x33";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonAgain"))
			{
				dialog.text = "Here's our puppeteer!";
				link.l1 = "Ha-ha! The spectacle was perfect!";
				link.l1.go = "patria_x29";
				break;
			}
			// Тени прошлого
			if(CheckAttribute(pchar, "questTemp.Saga.Shadows") && pchar.questTemp.Saga.Shadows == "islatesoro" && npchar.location == "Pirates_townhall")
			{
				dialog.text = "Glad to see you, boy! How can I help you?";
				link.l1 = "Marcus, I need to talk to you. I'm not sure you'll like it, but I need your help all the same.";
				link.l1.go = "shadows";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "islatesoro" && npchar.location == "Pirates_townhall")
			{
				dialog.text = "Ha, here you are, "+pchar.name+". I've been waiting for your arrival. The Forest Devil has confounded me with your problem about Tortuga...";
				link.l1 = "He told me you found a solution. Am I right?";
				link.l1.go = "terrapin";
				break;
			}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkTrade") && GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l2 = "I have silk to sell.";
				link.l2.go = "Mtraxx_silktrade";
			}
            dialog.text = NPCStringReactionRepeat(GetFullName(pchar)+", glad to see you! What do you need this time?","What do you want?","Again? Don't bother people if you have nothing to do!","You are a "+GetSexPhrase("good privateer","good girl")+", so you can live for now. But I don't want to talk to you anymore.","repeat",10,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Just wanted to see you.","Nothing.","Fine, Marcus, I'm sorry.","Damn it, I'm really sorry, Marcus!",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Robbery! That is unacceptable! Prepare to die, rat...","Hey, what are you doing there?! Thought you could rob me? You're finished...","Wait, what the hell?! Turns out you are a thief! End of the line, bastard...");
			link.l1 = LinkRandPhrase("Shit!","Caramba!","Ah, damn it!");
			link.l1.go = "PL_Q3_fight";
		break;
					
		// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple(""+GetSexPhrase("Go away","Get away")+" from here!","Get out of my home!");
			link.l1 = "Oops...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Don't distract me from my work with your worthless talk. Next time, it won't end so well for you...";
        			link.l1 = "Got it, Marcus.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryRepeat_2":
            dialog.text = RandPhraseSimple("I am tired of you.","I don't want to talk to you, so you better keep your distance from me.");
			link.l1 = RandPhraseSimple("Well...","Hm, fine then...");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "I hope you won't bother me with your empty talk anymore, or I'll have to kill you. I must say, I wouldn't be glad to do so.";
        			link.l1 = "You can be sure of that, Marcus, I won't...";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
		break;
		case "AngryExitAgainWithOut":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
            DoReloadCharacterToLocation("Lavega_town","reload","reload6");
		break;
		// <<<<<<<<<<<<============= блок нод angry =============================
		
//--> -----------------------------Сага - Искушение Барбазона завершающие этапы---------------------------
		case "Temptation":
			dialog.text = "Ha! The hero of Turks? Sorry for the rough greeting, boy. Bernard has already told me about your remarkable involvement and mentioned something about a trap for me. I'd like to hear the details...";
			link.l1 = "It was a trap indeed. They were hunting you, not Bernard. He was just the bait.";
			link.l1.go = "Temptation_1";
		break;
		
		case "Temptation_1":
			dialog.text = "";
			link.l1 = "The plan was simple. You were supposed to save your friend and be the first one to board the 'Separator'. And right at that moment, they would have fired at the ship and blown her to pieces. The brigantine was loaded with gunpowder like hell is with sulfur.";
			link.l1.go = "Temptation_2";
		break;
		
		case "Temptation_2":
			dialog.text = "Damn! Whose idea was that madness?! And how was I supposed to find out where they were hiding Bernard?!";
			link.l1 = "The authors of that plan were Jackman and his brother David. A messenger would have informed you that the 'Separator' was waiting for your help at the southern bay of Turks. They chose me as that messenger, and that was their mistake.";
			link.l1.go = "Temptation_3";
		break;
		
		case "Temptation_3":
			dialog.text = "I don't get it! What's your role in all of this?";
			link.l1 = "I've been watching that bastard Jackman for a long time. I work with Jan Svenson, if you don't know. The Forest Devil and I have decided to expose him. Jan is sure that he is the one to blame for Blaze's death, and Steven was accused for nothing.";
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end") link.l1.go = "Temptation_14";
			else link.l1.go = "Temptation_4"; //патч 17/1
		break;
		
		case "Temptation_4":
			dialog.text = "Heh! But a shark tooth with his initials was found on Blaze's body – S.D. – everyone knows this belongs to Steven...";
			link.l1 = "It was all a setup. Jackman played for high stakes. He got rid of Nathaniel Hawk and took his place in Maroon Town, then he murdered Sharp and framed Shark for the crime. I have enough proof of his misdeeds. I found it in Jacob's chest. That's where the second part of Sharp's map and Hawk's shard were.";
			link.l1.go = "Temptation_5";
		break;
		
		case "Temptation_5":
			dialog.text = "Damn! So Steven is innocent? And why did Jacob do all of this?";
			link.l1 = "He expected to become the head of the Brethren and anticipated something connected to Isla Tesoro. He couldn't gain your and Svenson's support, so he decided to get rid of you both. You were first on the list. Jan, as the most dangerous one, was second.";
			link.l1.go = "Temptation_6";
		break;
		
		case "Temptation_6":
			dialog.text = "Where is that bastard?! I'll tear him apart!";
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) // Акула жив
			{
				link.l1 = "Jackman and his brother are dead, as are the rest of his hunters. I have personally dealt with them. This bastard won't harm anyone anymore. Marcus, would you vote for Steven Dodson? This is my personal favour.";
				link.l1.go = "Temptation_7";
			}
			else
			{
				link.l1 = "Jackman and his brother are dead, as well as the rest of the hunters. I have personally dealt with them. This bastard won't harm anyone anymore. Unfortunately, Steven was killed...";
				link.l1.go = "Temptation_10";
			}
		break;
		
		case "Temptation_7":
			dialog.text = "Sure, I'll vote! I always considered Shark the most worthy of us after Blaze. And I almost believed in his guilt. We all have! Here, take my shard.";
			link.l1 = "Very well! Now you can breathe freely.";
			link.l1.go = "Temptation_8";
		break;
		
		case "Temptation_8":
			GiveItem2Character(pchar, "splinter_mt"); // дать осколок
			dialog.text = "True... As I understand it, you represent Shark's interests?";
			link.l1 = "Yes. Jan Svenson and I. Fine, Marcus, see you!";
			link.l1.go = "Temptation_9";
		break;
		
		case "Temptation_10":
			dialog.text = "Dead?! How? Jackman's work too?";
			link.l1 = "No. His own boatswain did it, Chad Kapper was his name. He already got what he deserved... Marcus, Svenson thinks that you are the worthiest to be the new leader of the Brethren. The rest of the barons will support this decision. Do you accept this?";
			link.l1.go = "Temptation_11";
		break;
		
		case "Temptation_11":
			dialog.text = "Heh! You don't need to ask me twice. It's a great honour to be the Head of the Brethren! Don't even think that I'll disagree.";
			link.l1 = "Great. I am glad that you have accepted this.";
			link.l1.go = "Temptation_12";
		break;
		
		case "Temptation_12":
			GiveItem2Character(pchar, "splinter_mt"); // дать осколок
			dialog.text = "Here, take my shard. Deliver it to Svenson. I take it he is in charge?";
			link.l1 = "Yes, he is. Fine, Marcus, see you!";
			link.l1.go = "Temptation_9";
		break;
		
		case "Temptation_9":
			dialog.text = "Yes, and I want to thank you for saving my friend Bernard. Here, take this purse full of gold.";
			link.l1 = "Thank you! Farewell!";
			link.l1.go = "Temptation_exit";
		break;
		
		case "Temptation_exit":
			DialogExit();
			TakeNItems(pchar, "gold_dublon", 300);
			Log_Info("You have received 300 doubloons");
			PlaySound("interface\important_item.wav");
			NextDiag.CurrentNode = "I_know_you_good";
			AddQuestRecord("BarbTemptation", "25");
			if (CheckCharacterItem(pchar, "splinter_mt") && CheckCharacterItem(pchar, "splinter_jb") && CheckCharacterItem(pchar, "splinter_zm")) Saga_GiveCalendar();
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		// Addon 2016-1 Jason пиратская линейка патч 17/1
		case "Temptation_13":
			dialog.text = "Yeah, he told me about the magnificent arrival of Charlie Prince at Turks... Saved my ass, you say? How? Bernard mentioned something about a trap...";
			link.l1 = "Yes, it was a trap. You were the target; Bernard was just the bait...";
			link.l1.go = "Temptation_1";
		break;
		
		case "Temptation_14":
			dialog.text = "Ha-ha-ha, working for the Forest Devil, eh Prince? So, do you earn better money with him than you did with me? Tell me honestly!";
			link.l1 = "Marcus, let's set aside the past for good. We have a common goal now, and it's more important than plundering caravans. Damn! It's the most important thing now! The future of the Brethren is at stake!";
			link.l1.go = "Temptation_15";
		break;
		
		case "Temptation_15":
			dialog.text = "Fine Prince, I get it! You are a free privateer after all, working for the Forest Devil was your choice, and you've made a good decision... Steven then... You said he was slandered, right?";
			link.l1 = "Absolutely right.";
			link.l1.go = "Temptation_4";
		break;
		
		// Тени прошлого
		case "shadows":
			dialog.text = "Sure, I'll do my best to help you! Go on.";
			link.l1 = "Take a look, Marcus... Here is a shark's tooth. What can you tell me about it?";
			link.l1.go = "shadows_1";
		break;
		
		case "shadows_1":
			RemoveItems(pchar, "shark_teeth", 1);
			dialog.text = "Ha! That's the tooth of a white shark killed by Steven Dodson, who was hoping to impress a girl. People have called him Shark ever since. Only a few could manage that underwater with just a simple sabre. But he was young and foolish, and Beatrice Sharp was the most beautiful girl in the Caribbean... So, how did you get it?";
			link.l1 = "It was given to me by the former hangman of Saint John's. This tooth was used to slay a man. His name was... Joshua Leadbeater.";
			link.l1.go = "shadows_2";
		break;
		
		case "shadows_2":
			dialog.text = "That is an old story. Steven killed that man. He was shocked by Beatrice's death and thought that Leadbeater was the only living person responsible for it. But later he found some papers on Joshua's corpse, studied them, and repented his deed.\nThe Mask wasn't to blame for Beatrice's death; he only needed Butcher. Butcher's jealous ex-girlfriend Jessica had set all this up.";
			link.l1 = "Have you read those papers?";
			link.l1.go = "shadows_3";
		break;
		
		case "shadows_3":
			dialog.text = "Why should I? Of course not. I wasn't interested in them. But I can tell you why the Mask was pursuing Butcher if you've got some spare time. Drunken Steven told me this story many times.";
			link.l1 = "I've got time. Trust me, my interest has a purpose. I could even write this story.";
			link.l1.go = "shadows_4";
		break;
		
		case "shadows_4":
			dialog.text = "I know that you never waste your time. Listen then. Joshua Leadbeater was an English naval captain, and the legendary 'Neptune' was under his command...";
			link.l1 = "...";
			link.l1.go = "shadows_5";
		break;
		
		case "shadows_5":
			DialogExit();
			SetLaunchFrameFormParam("One hour later", "Saga_FinalLedbitterStory", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 10); //крутим время
			RecalculateJumpTable();
		break;
		
		case "shadows_6":
			AddQuestRecordInfo("Mask", "1");
			dialog.text = "... but Leadbeater survived and was picked up by a passing ship. His wound disfigured him, and since then he has been wearing a mask. After some time, people started to call him the Mask. Revenge against the man who scarred him for life became his sole purpose.";
			link.l1 = "I see... I have written it all. I think I need to reread it and compare it with all the information I already have. A sad story indeed. Have you ever seen Jessica?";
			link.l1.go = "shadows_7";
		break;
		
		case "shadows_7":
			dialog.text = "Sure! She accompanied Butcher on all his voyages until he left her for Beatrice. Jess couldn't forgive him for that. People called her the Butcher's talisman, because he always had luck while she was there with him.\nBelieve it or not, but as soon as he got rid of her in Barbados, his business went bad, the booty became poor, and the 'Neptune' became a frequent guest at the shipyard of Isla Tesoro. But that can be explained by the fact that Butcher had been spending most of his time with Beatrice in the cabin rather than on the quarterdeck.\nBeatrice was not like Jessica; she wasn't addicted to adventure and war, although Nicholas taught her fencing and sailing. Yes, she was fond of sea romances, but she didn't have enough steel in her. Butcher's 'Neptune' wasn't the right place for her. In the end, it killed her.";
			link.l1 = "And what about Jessica?";
			link.l1.go = "shadows_8";
		break;
		
		case "shadows_8":
			dialog.text = "Oh, she was something, alright... Every sailor on the 'Neptune' obeyed her orders, and not just because she was the captain's girlfriend. Jess was a master of fencing and sailing; Butcher's efforts weren't wasted. She was tough and reckless, and she was so beautiful. A lot of men wanted to share a bed with her, but she wanted only Butcher. Bothering her was really risky; many felt the consequences on their own skin, quite literally, and for the most persistent, her fencing lessons turned out to be the last of their lives. Jess owned a very special sword, the only one of its kind in the Caribbean. I have no clue where she got it. A flame-bladed sword. The blade couldn't be grabbed by hand, and even the slightest touch left a terrible wound. Jess was an adventurer not by birth, but by vocation. By the way, if you want to know more about her, you can talk to an acquaintance of yours. He can tell you much more about her than I can.";
			link.l1 = "Really? And who is this man?";
			link.l1.go = "shadows_9";
		break;
		
		case "shadows_9":
			dialog.text = "Jan Svenson. The Forest Devil would never admit it, but he had plans for Jessica. That was the time when he had already taken Western Main for himself and his fame was something to envy, so the tigress suited him well.\nAfter Butcher got rid of Jess, Jan started to visit Barbados suspiciously often, making the garrison tremble with fear, he did. As you know, Jessica was the daughter of a Bridgetown planter.\nAll in all, his intentions were well known in private circles, yet no one dared to speak their mind about it. Jan may sit on his backside in Blueweld nowadays, but back then any wrong word addressed to him could end badly.\nIn the end, it didn't work out for them. Jess couldn't live with the pain caused by Butcher's betrayal, and she had her revenge a year later with the help of the Mask. This vengeance ended terribly for everyone: for Butcher, for Beatrice, for the Mask, and for herself. They all died.";
			link.l1 = "Nope. Butcher is still alive.";
			link.l1.go = "shadows_10";
		break;
		
		case "shadows_10":
			dialog.text = "What?! Did I hear you wrong?! He's alive?!";
			link.l1 = "Yes. Captain Butcher wasn't hanged. Well, he was, actually, but thanks to Jacob Jackman and Henry the Hangman, who scared the hangman, he survived. The hanging was just a performance. I've got proof.";
			link.l1.go = "shadows_11";
		break;
		
		case "shadows_11":
			dialog.text = "Incredible! And where is he now?";
			link.l1 = "He is known as Lawrence Beltrop and he lives in Port Royal. But it seems he hasn't changed and is still dangerous. Jackman, who has caused a lot of trouble within the Brethren, was following his orders.";
			link.l1.go = "shadows_12";
		break;
		
		case "shadows_12":
			dialog.text = "Damn! The quartermaster has found his captain after all! After so many years... Beltrop, you say... wait! Now I see why there was that strange interrogation protocol in Blaze's papers... It seems that Blaze discovered something interesting about Butcher-Beltrop...";
			link.l1 = "What are you talking about?";
			link.l1.go = "shadows_13";
		break;
		
		case "shadows_13":
			dialog.text = "When I took up this residence, I allowed myself some time to look through Blaze's papers. I found an interrogation protocol concerning someone named Samuel Brooks. There were many details about the adventures of Thomas Beltrope, a famous pirate and the closest friend of Nicolas Sharp. It seems he is Butcher's father.";
			link.l1 = "Interesting. Looks like Beltrop's and Sharp's children have carried on their fathers' job...";
			link.l1.go = "shadows_14";
		break;
		
		case "shadows_14":
			dialog.text = "It seems so... Tell me, friend, why are you so interested in the past of people who have been dead for a long time already? What's this all about?";
			link.l1 = "I need documents that prove Ellen McArthur is the daughter of Beatrice Sharp and the granddaughter of Nicolas Sharp, and that she has every right to bear this surname. I don't care if her surname might be Beltrop.";
			link.l1.go = "shadows_15";
		break;
		
		case "shadows_15":
			dialog.text = "I have found nothing about Ellen McArthur in Blaze's archives. It is strange that Beatrice didn't tell Blaze about his niece's birth. It's not like her.";
			link.l1 = "Listen, maybe there's something else in Sharp's papers about this story? I need every detail I can get!";
			link.l1.go = "shadows_16";
		break;
		
		case "shadows_16":
			dialog.text = "Hm... Maybe. According to Blaze's notes, he was trying to find the island where his sister died. There are copies of archive papers concerning Leadbeater's punitive expedition. Nothing interesting, except for a few latitude numbers.\nThis parallel crosses the Caribbean Sea in its northern part. But there is no sign of longitude. Obviously, Blaze's search failed; you can't even imagine how many small islands are at that latitude.";
			link.l1 = "And what's the latitude?";
			link.l1.go = "shadows_17";
		break;
		
		case "shadows_17":
			dialog.text = "Let's see... Here: 21° 32' North. I don't know how it can help you.";
			link.l1 = "It can. Thank you very much, Marcus, for your honest story. See you!";
			link.l1.go = "shadows_18";
		break;
		
		case "shadows_18":
			DialogExit();
			pchar.questTemp.Saga.Shadows = "jessika";
			AddQuestRecord("Shadows", "6");
			LAi_SetHuberType(npchar);
			NextDiag.CurrentNode = "I_know_you_good";
			sld = characterFromId("Svenson");
			sld.quest.jessika = "true";
			// рифы доступны для посещения
			i = FindIsland("RockIsland");
			Islands[i].visible = true;
			Islands[i].reload_enable = true;
			// для любителей самостоятельно добавлять локаторы
			LAi_LocationDisableOfficersGen("Shore67", true);//офицеров не пускать
			// и сразу прерывание
			pchar.quest.Saga_Jess_Island.win_condition.l1 = "location";
			pchar.quest.Saga_Jess_Island.win_condition.l1.location = "Shore67";
			pchar.quest.Saga_Jess_Island.function = "Saga_JessikaIsland"; 
			// активируем квест хронометра Алекса
			pchar.questTemp.AlexClock = "terrax"; // 280912
		break;		
		
		// суп из черепахи
		case "terrapin":
			dialog.text = "Well, I can do something for you. As you know, Tortuga's security is not only provided by Fort La Roche but also by a pirate squadron constantly guarding the shores of the island. The port of Tortuga is safe, these lads know their business and they have powerful ships. Levasseur has been luring these captains for a long time.\nThey are capable of fighting even against a line squadron and they will be serious opponents. So, being the keeper of the Code and also the leader of the Brethren of the Coast, I can make these watchdogs leave Tortuga's shores.";
			link.l1 = "And that's all?";
			link.l1.go = "terrapin_1";
		break;
		
		case "terrapin_1":
			dialog.text = "Isn't that enough? I can't help you any further anyway. You have to destroy the fort, but at least you don't need to fight those guard ships. Trust me, they're more dangerous than the fort, so my help will make things easier.";
			link.l1 = "Well, if I have to attack it anyway, the departure of the pirate squadron will really help. Thanks, Marcus! When can I attack Tortuga?";
			link.l1.go = "terrapin_2";
		break;
		
		case "terrapin_2":
			dialog.text = "Whenever you wish. The guard ships will depart on my signal.";
			link.l1 = "Fine. I have to go now to prepare myself.";
			link.l1.go = "terrapin_3";
		break;
		
		case "terrapin_3":
			DialogExit();
			// Левассера - к барьеру!
			sld = characterFromId("Tortuga_Mayor");
			LAi_LoginInCaptureTown(sld, true);
			pchar.questTemp.Sharlie.Hardcore_Tortuga = "true";
			pchar.questTemp.Terrapin = "hardcore";
			pchar.questTemp.Sharlie.DelTerGuard = "true"; // убираем пиратскую эскадру
		break;
		
		case "pirate_town":
            dialog.text = "Solve the problem? Do you have any idea what you've done? Anyway, bring me a million pesos and I will persuade the lads to forget your deed. If you don't like the idea, then you may go to hell.";
			if (sti(Pchar.money) >= 1000000)
			{
				link.l1 = "Fine, I am ready to pay.";
				link.l1.go = "pirate_town_pay";
			}
			link.l2 = "Farewell...";
			link.l2.go = "pirate_town_exit";
		break;
		
		case "pirate_town_exit":
			DialogExit();
            bDisableFastReload = true;//закрыть переход
			pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
			pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
			pchar.quest.pirate_in_town.function = "TownPirate_battle";
		break;
		
		case "pirate_town_pay":
            dialog.text = "Good! Consider yourself clean again. But I hope you won't do such disgusting things again.";
			link.l1 = "I won't. Far too expensive for me. Farewell...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000000);
			pchar.GenQuest.Piratekill = 0;
		break;
		
		// Addon 2016-1 Jason ------------------------- пиратская линейка --------------------------
		case "Mtraxx":
			if (pchar.Ship.Type == SHIP_NOTUSED)
			{
				dialog.text = "First get yourself a ship, then ask for a job. A landlubber has nothing to do here. Get lost!";
				link.l1 = "Hmm... I see.";
				link.l1.go = "exit";
				break;
			}
			if(ChangeCharacterHunterScore(Pchar, "spahunter", 0) > 10)
			{
				dialog.text = "Are you completely out of your mind? Half the Spanish world is after you. You'll do more harm than good. Sort out your problems, then apply. That's all I wanted to say! Get out of here!";
				link.l1 = "Hmm... I see.";
				link.l1.go = "exit";
				break;
			}
            dialog.text = "Looking for some action, huh? Ha-ha! Good... But I warn you, boy, you won't find any peace with me. If you're afraid of the smell of gunpowder or can't spill blood - the door's behind you. I can't stand cowards. And you won't last long with me if you're a snitch or a rat who fancies stealing a partner's share of the plunder. So, what do you say? Are you in?";
			link.l1 = "I am in, Marcus. I'm not afraid to fight and there's no dog that can accuse me of being either a coward or a rat.";
			link.l1.go = "Mtraxx_1";
			link.l2 = "Whoa, that's too much for me! Beg your pardon, Marcus, but I'd better take my leave...";
			link.l2.go = "Mtraxx_exit";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("LaVega");
		break;
		
		case "Mtraxx_exit":
            DialogExit();
			pchar.questTemp.Mtraxx = "fail";
		break;
		
		case "mtraxx_wait":
            dialog.text = "What, are you still here?";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkTrade") && GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l2 = "I have some silk to sell.";
				link.l2.go = "Mtraxx_silktrade";
				link.l1 = "I am leaving already.";
				link.l1.go = "exit";
				break;
			}
			link.l1 = "...";
			link.l1.go = "exit";
		break;
		
		case "Mtraxx_1":
            dialog.text = "Ha-ha, well, well, my brave little pirate, let's discuss business then. My source in Santo Domingo informed me about a Spanish captain who is so rich with blue amber that he is giving it away to whores. Have you heard about blue amber?";
			link.l1 = "I have. A rare and valuable stone.";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = "Precisely. Even here, bankers and jewellers pay good money for it, and in good old Europe you can get ten times more for it. Amber is not a rare stone in the Caribbean, but the blue variety is a rarity. And now we have some Castilian sly dog bragging that he has more blue amber than the bankers of Cuba and Hispaniola have yellow amber put together.";
			link.l1 = "Can the stories of some drunk Spaniard be trusted? Found three doubloons and is telling everyone that he has found El Dorado";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = "I wouldn't have, but he was actually giving blue amber to whores. There must be some truth in his boasting. Go to Santo Domingo and investigate. If you find the blue amber deposit, that will be even better. Do this and I can guarantee you a reward and respect in La Vega.";
			link.l1 = "What if your information is worthless?";
			link.l1.go = "mtraxx_4";
		break;
		
		case "mtraxx_4":
            dialog.text = "Then prove to me that the Castilian is a liar.";
			link.l1 = "Very well. Who is your source in Santo Domingo?";
			link.l1.go = "mtraxx_5";
		break;
		
		case "mtraxx_5":
			// belamour legendary edition даем флаг и лизензию ГВИК если отсутствует -->
			bOk = IsCharacterPerkOn(pchar,"FlagSpa") || IsCharacterPerkOn(pchar,"FlagHol");
			if(CheckCharacterItem(pchar, "HolTradeLicence") && GetDaysContinueNationLicence(HOLLAND) >= 60 && bOk) sTemp = ".";
			else 
			{
				if(bOk) 
				{
					if(!CheckCharacterItem(pchar, "HolTradeLicence") || GetDaysContinueNationLicence(HOLLAND) < 60) 
					{
						sTemp = ". Wait a minute, take a trading license for 60 days."; 
						GiveNationLicence(HOLLAND, 60);
					}
				}
				else // нет флага
				{
					if(!CheckCharacterItem(pchar, "HolTradeLicence")) 
					{
						sTemp = ". Wait a minute, take a 60-day trade license and a Spanish flag to land in Santo Domingo. From now on, I recommend getting your own, it will help to fool the simpleton in the trading pelvis. This one will be returned to me.";
						GiveNationLicence(HOLLAND, 60);
						SetCharacterPerk(pchar, "FlagSpa");
						log_info("You have received spanish flag");
						pchar.questTemp.GiveMeSpaFlag = true;
					}
					else // есть лицензия
					{	
						if(GetDaysContinueNationLicence(HOLLAND) < 60) 
						{
							sTemp = ". Wait, how are you going to trade without having the right flag?! Here you go, a 60-day trading license, longer than yours. As well as the Spanish flag for landing in Santo Domingo. From now on, I recommend getting your own, it will help to fool the simpleton in the trading pelvis. This one will be returned to me.";
							GiveNationLicence(HOLLAND, 60);
							SetCharacterPerk(pchar, "FlagSpa");
							log_info("You have received spanish flag");
							pchar.questTemp.GiveMeSpaFlag = true;
						}
						else 
						{
							sTemp = ". Wait, how are you going to trade without having the right flag?! Here, take the Spanish flag for the Santo Domingo landings. From now on, I recommend getting your own, it will help to fool the simpleton in the trading pelvis. This one will be returned to me.";
							SetCharacterPerk(pchar, "FlagSpa");
							log_info("You have received spanish flag");
							pchar.questTemp.GiveMeSpaFlag = true;
						}
					}
				}
			}
			// <-- legendary edition
            dialog.text = "You need a brothel girl named Gabriela Chapado. Say my name and the password - 'Amber Necklace'. She will give you the details. And do not waste time - the information is still fresh, but in a day or two it may become outdated"+sTemp;
			link.l1 = "Got it, Marcus. I'm heading to Santo Domingo.";
			link.l1.go = "mtraxx_6";
		break;
		
		case "mtraxx_6":
            DialogExit();
			pchar.questTemp.Mtraxx = "jewelry_1";
			pchar.questTemp.Mtraxx.AffairOfHonor = "true"; // конфликт с делом чести
			pchar.questTemp.ZA.Block = true;			// конфликт с квестом "Заносчивый аристократ"
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_1", "1");
			Mtraxx_JewelryBegin();
			AddMapQuestMarkCity("SantoDomingo", false);
		break;
		
		case "mtraxx_7":
			i = GetCharacterItem(pchar, "jewelry7");
            dialog.text = "I've already been informed of your arrival. Give me your report!";
			link.l1 = "I've dealt with that blue amber lover, although it wasn't easy. I managed to find his deposits and plunder them. I have brought you "+FindRussianQtyString(i)+" pieces of blue amber.";
			link.l1.go = "mtraxx_8";
			DelLandQuestMark(characterFromId("Terrax"));
			DelMapQuestMarkCity("LaVega");
		break;
		
		case "mtraxx_8":
			if (sti(pchar.questTemp.Mtraxx.JewQty) > GetCharacterItem(pchar, "jewelry7"))
			{
				PlaySound("interface\important_item.wav");
				Log_Info("You have given "+FindRussianQtyString(GetCharacterItem(pchar, "jewelry7"))+" pieces of blue amber");
				RemoveItems(pchar, "jewelry7", GetCharacterItem(pchar, "jewelry7"));
				dialog.text = "Well, well... Son, do you remember my warning about the dangers of being a rat? What did you say to me then? No dog can blame you for that? Do you think I am stupid, kid? I am perfectly aware that you have plundered "+FindRussianQtyString(sti(pchar.questTemp.Mtraxx.JewQty))+" pieces of blue amber on the Mosquito Coast. Now run, little rat, run, and pray we never meet again!";
				link.l1 = "Damn it!";
				link.l1.go = "AngryExitAgainWithOut";
				pchar.questTemp.Mtraxx = "fail";
				npchar.Dialog.currentnode = "First time";
				CloseQuestHeader("Roger_1");
				// belamour legendary edition забрать флаг обратно
				if(CheckAttribute(pchar, "questTemp.GiveMeSpaFlag")) 
				{
					DeleteAttribute(pchar, "questTemp.GiveMeSpaFlag")); 
					DeleteAttribute(pchar,"perks.list.FlagSpa"); 
					log_info("You have given spanish flag");
				}
			}
			else
			{
				PlaySound("interface\important_item.wav");
				Log_Info("You have given "+FindRussianQtyString(GetCharacterItem(pchar, "jewelry7"))+" pieces of blue amber");
				RemoveItems(pchar, "jewelry7", sti(pchar.questTemp.Mtraxx.JewQty));
				dialog.text = "Nicely done, boy! You have shown your best side: handled a difficult matter and brought everything you've plundered. Good work! I'm glad I wasn't wrong about you.";
				link.l1 = "What about my share, Marcus?";
				link.l1.go = "mtraxx_9";
			}
		break;
		
		case "mtraxx_9":
			i = sti(pchar.questTemp.Mtraxx.JewQty)/2;
			PlaySound("interface\important_item.wav");
			Log_Info("You have received "+FindRussianQtyString(i)+" pieces of blue amber");
			TakeNItems(pchar, "jewelry7", i);
			// belamour legendary edition забрать флаг обратно
			if(CheckAttribute(pchar, "questTemp.GiveMeSpaFlag")) 
			{
				DeleteAttribute(pchar, "questTemp.GiveMeSpaFlag")); 
				DeleteAttribute(pchar,"perks.list.FlagSpa"); 
				log_info("You have given spanish flag");
			}
            dialog.text = "Spoken like a true pirate, ha-ha-ha! Half the loot is yours. Take it.";
			link.l1 = "Thanks, Cap. Have anything else for me?";
			link.l1.go = "mtraxx_10";
			DeleteAttribute(pchar, "questTemp.Mtraxx.JewQty");
			CloseQuestHeader("Roger_1");
			Achievment_Set("ach_57");
		break;
		
		case "mtraxx_10":
            dialog.text = "I always have tasks for capable lads. There is a delicate matter I want you to deal with. There is a ship stationed in Capsterville, called the 'Snake', under the command of Geffrey Brooke, also known as Bald Geffrey. He works for me. An excellent fighter, knows everything about guns and blades, yet a complete idiot in every other aspect of life. But let's not be too hard on Baldy, no one is perfect, ha-ha! So. This tough guy attacked a Dutch convoy north of Saint Martin and captured a bark filled with sacks of wheat. Thing is, he managed to find hidden ship silk among the sacks. A really big cargo. This merchandise is extremely valuable and rare; the Dutch bring it from Europe solely for their military needs. This silk is used for special sails which increase a ship's speed and ability to sail by the wind. It is almost impossible to buy, selling it is not a problem but it is hard to find the right price. These goddamn traders always reduce the price! I am aware that there are people in the Caribbean who are ready to give a good price in doubloons to buy this silk, and your goal is to find such people. What? Any fool can plunder caravans, but trade is only for people with at least a sign of brains' existence in their skull. I am planning to sell ship silk on a monthly basis, so your goal is to find a regular buyer who will pay at least twenty golden doubloons for a roll. You have two months to do that, I cannot keep Bald Geffrey in Capsterville forever. That's all. Set sail to Capsterville and talk to Geffrey before he sells the cargo to smugglers for a penny. I've already told you that he is a bit 'simple'.";
			link.l1 = "Hm... Got it. Already on my way.";
			link.l1.go = "mtraxx_11";
		break;
		
		case "mtraxx_11":
            DialogExit();
			pchar.questTemp.Mtraxx = "silk_1";
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_2", "1");
			Mtraxx_SilkBegin();
		break;
		
		case "mtraxx_12":
            dialog.text = "Ha! Here's the brave captain "+GetFullName(pchar)+"! What about the buyer?";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkLate"))
			{
				link.l1 = "I've found you a buyer. He's a shipbuilder from Port Royal. He needs ship silk for his production and will be able to buy batches of one hundred rolls every month for 25 doubloons a roll. His men will collect the goods from the 10th to the 15th, at night, at Negril Cape. The password is 'A merchant of Lyons'. It took me more than two months to find such a buyer; Geffrey must have already sold the silk to smugglers. I'm sorry, Marcus.";
				link.l1.go = "mtraxx_15";
			}
			else
			{
				link.l1 = "I've found you a buyer. He's a shipbuilder from Port Royal. He needs ship silk for his production and will be able to buy batches of one hundred rolls every month for 25 doubloons a roll. His men will receive the goods from the 10th to the 15th, at night, at Negril Cape. The password is 'A merchant of Lyons'. Bald Geffrey has already delivered the first batch to Jamaica.";
				link.l1.go = "mtraxx_13";
			}
		break;
		
		case "mtraxx_13":
            dialog.text = "That's great, my friend! Nicely done. It is hard to find a man capable of using both his hands and his head. See me in 20 days to collect your reward. Bald Geffrey will have brought the money from the first transaction by then."; // правки прогона 3
			link.l1 = "Very well, Marcus. See you soon. I hope you'll have another job for me.";
			link.l1.go = "mtraxx_14";
		break;
		
		case "mtraxx_14":
            dialog.text = "I will. See you later.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkLate"))
			{
				SetFunctionTimerCondition("Mtraxx_SilkPay", 0, 0, 30, false);
				//SetFunctionTimerCondition("Mtraxx_SilkPayLate", 0, 0, 40, false);
				AddQuestRecord("Roger_2", "23");
			}
			else
			{
				SetFunctionTimerCondition("Mtraxx_SilkPay", 0, 0, 20, false); // правки прогона 3
				//SetFunctionTimerCondition("Mtraxx_SilkPayLate", 0, 0, 30, false);
				AddQuestRecord("Roger_2", "24");
			}
		break;
		
		case "mtraxx_15":
			pchar.quest.Mtraxx_SilkTimeLateAll.over = "yes";
            dialog.text = "Pity, but still a huge success. You did a good job! You won't receive your share from Geffrey's batch, but you still deserve a reward. See me in a month, I will have sold the first batch to your buyer by that time, then we will talk.";
			link.l1 = "Very well, Marcus. See you soon. I hope you'll have another job for me.";
			link.l1.go = "mtraxx_14";
		break;
		
		case "mtraxx_16":
			//pchar.quest.Mtraxx_SilkPayLate.over = "yes";
            dialog.text = "There you are, "+pchar.name+". Let's talk about your reward.";
			link.l1 = "I like conversations like this, ha-ha-ha! I'm all ears.";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkLate")) link.l1.go = "mtraxx_19";
			else link.l1.go = "mtraxx_17";
		break;
		
		case "mtraxx_17":
            dialog.text = "Bald Geffrey has sold your buyer the first batch of 105 rolls of ship silk. Since I was expecting to sell it for twenty doubloons a roll, I think it would be fair to give you the difference. That's my decision. Your share is 525 doubloons plus a bonus - a doubloon per roll. That makes 630 doubloons in total. Here, take them.";
			link.l1 = "Thank you, Marcus!";
			link.l1.go = "mtraxx_18";
		break;
		
		case "mtraxx_18":
			TakeNItems(pchar, "gold_dublon", 630);
			Log_Info("You have received 630 doubloons");
			PlaySound("interface\important_item.wav");
            dialog.text = "One more thing. You can make some extra profit from this.";
			link.l1 = "Interesting... Go on.";
			link.l1.go = "mtraxx_19";
		break;
		
		case "mtraxx_19":
            dialog.text = "Your buyer wants more than 100 rolls of silk to be delivered over the next two months. If you have any, then bring me 20 to 100 rolls for a price of 24 doubloons. The offer will stand for two months.";
			link.l1 = "Fine! I'll bring more if I have any.";
			link.l1.go = "mtraxx_20";
			pchar.questTemp.Mtraxx.SilkTrade = "true";
			SetFunctionTimerCondition("Mtraxx_SilkTradeOver", 0, 0, 60, false);
		break;
		
		// торговля шелком
		case "mtraxx_silktrade":
			iTotalTemp = GetSquadronGoods(pchar, GOOD_SHIPSILK);
            dialog.text = "How much do you have?";
			link.l1 = ""+FindRussianQtyString(iTotalTemp)+".";
			if (iTotalTemp > 100) link.l1.go = "mtraxx_silktrade_2";
			else link.l1.go = "mtraxx_silktrade_1";
		break;
		
		case "mtraxx_silktrade_1":
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, iTotalTemp);
			TakeNItems(pchar, "gold_dublon", iTotalTemp*24);
            dialog.text = "Very good. Take the gold - 24 doubloons for a roll, as we agreed.";
			link.l1 = "Gratitude!";
			link.l1.go = "mtraxx_silktrade_3";
		break;
		
		case "mtraxx_silktrade_2":
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, 100);
			TakeNItems(pchar, "gold_dublon", 2400);
            dialog.text = "I'll take a hundred rolls. Take the gold - 24 doubloons per roll, as we agreed.";
			link.l1 = "Gratitude!";
			link.l1.go = "mtraxx_silktrade_3";
		break;
		
		case "mtraxx_silktrade_3":
            DialogExit();
			npchar.dialog.currentnode = "First time";
			DeleteAttribute(pchar, "questTemp.Mtraxx.SilkTrade");
		break;
		
		case "mtraxx_20":
            dialog.text = "Let's talk about something more urgent, do you want to deal with something dangerous?";
			link.l1 = "Sure! My men and I are ready to set sail immediately.";
			link.l1.go = "mtraxx_24";
		break;
		
		case "mtraxx_22":
            dialog.text = "For fuck's sake, "+pchar.name+", where the hell have you been? Remember when I told you to come see me? I had a job for you and now it's wasted thanks to your excellent sense of timing. You've really upset me, boy. Get lost, I don't work with people I can't rely on.";
			link.l1 = "Well, shit...";
			link.l1.go = "mtraxx_23";
		break;
		
		case "mtraxx_23":
			DialogExit();
            npchar.dialog.currentnode = "First time";
			CloseQuestHeader("Roger_2");
			pchar.questTemp.Mtraxx = "fail";
		break;
		
		case "mtraxx_24":
			// belamour legendary edition даем флаг и лизензию ГВИК если отсутствует -->
			bOk = IsCharacterPerkOn(pchar,"FlagSpa") || IsCharacterPerkOn(pchar,"FlagHol");
			if(CheckCharacterItem(pchar, "HolTradeLicence") && GetDaysContinueNationLicence(HOLLAND) >= 40 && bOk) sTemp = ".";
			else 
			{
				if(bOk) 
				{
					if(!CheckCharacterItem(pchar, "HolTradeLicence") || GetDaysContinueNationLicence(HOLLAND) < 40) 
					{
						sTemp = ", as well as a trade license for 40 days."; 
						GiveNationLicence(HOLLAND, 40);
					}
				}
				else // нет флага
				{
					if(!CheckCharacterItem(pchar, "HolTradeLicence")) 
					{
						sTemp = ", as well as a trade license for 40 days. Besides, how are you going to fool the bungler in the fort?! You will let me down one day with such sloppiness... Here you go... You will return it back upon arrival. The new generation, pah...";
						GiveNationLicence(HOLLAND, 40);
						SetCharacterPerk(pchar, "FlagSpa");
						log_info("You have received spanish flag");
						pchar.questTemp.GiveMeSpaFlag = true;
					}
					else // есть лицензия
					{	
						if(GetDaysContinueNationLicence(HOLLAND) < 40) 
						{
							sTemp = ". Tell me, how are you going to fool the bungler in the fort?! Your paper won't help you without the right flag. I feel that you will let me down one day with such sloppiness... Here, a trading license for 40 days, more than yours. As well as the Spanish flag for landing in Maracaibo. You will return it upon arrival. The new generation, pah...";
							GiveNationLicence(HOLLAND, 40);
							SetCharacterPerk(pchar, "FlagSpa");
							log_info("You have received spanish flag");
							pchar.questTemp.GiveMeSpaFlag = true;
						}
						else 
						{
							sTemp = ". Tell me, how are you going to fool the bungler in the fort?! Your paper won't help you without the right flag. I feel that you will let me down one day with such sloppiness... Here you go... You will return it back upon arrival. The new generation, pah...";
							SetCharacterPerk(pchar, "FlagSpa");
							log_info("You have received spanish flag");
							pchar.questTemp.GiveMeSpaFlag = true;
						}
					}
				}
			}
			// <-- legendary edition
            dialog.text = "Then listen closely. Two months ago I had an appointment with a captain by the name of Jean Picard, also known as Jean the Handsome. He didn't show up to the meeting and since I was going to discuss serious matters with him, I did some investigation regarding his whereabouts. Turned out our good brave privateer and his brigantine had managed to engage in a fight with a Spanish heavy galleon under command of don Eduardo de Losad and he is a tough son of a bitch. As a result, Jean and what's left of his crew was taken to Maracaibo and sold to a local plantation. This is where he is, busy with honest labor, at the moment.\nYour tasks are: firstsly - investigate the details of his misfortunes, secondly - get him out from plantation alive and bring him here; I really need details of his story. I am assigning a captain of a barquentine called 'Moray' to assist you in this. Captain's name is Paul Chant also known as Pelly the Cutlass. Remember Geffrey? He is almost as dumb as him, but good at fighting too.\nHe will be waiting for you at cape Ragget Point, on Barbados. Find him and his 'Moray' and sail to Maracaibo. Cutlass will follow your orders without asking stupid questions. Actually, he won't be asking questions at all. Just do your job and come back here, I'll be waiting for you. Here is ten thousand pesos for future expenses"+sTemp+". Any questions?";
			link.l1 = "Nope. Everything's clear. Heading to Barbados.";
			link.l1.go = "mtraxx_25";
		break;
		
		case "mtraxx_25":
			AddMoneyToCharacter(pchar, 10000);
            dialog.text = "I wish you luck then. Be swift, don't keep Cutlass and poor Jean waiting.";
			link.l1 = "Sure, boss! On my way.";
			link.l1.go = "mtraxx_26";
		break;
		
		case "mtraxx_26":
            DialogExit();
			CloseQuestHeader("Roger_2");
			npchar.dialog.currentnode = "mtraxx_wait";
			// belamour legendary edition по пути могут заскочить к Московиту, если рабов нет
			pchar.questTemp.Mtraxx.GiveMeSlaves = "Baster";
			AddQuestRecord("Roger_3", "1");
			AddLandQuestMark(characterFromId("Fadey"), "questmarkmain");
			AddMapQuestMarkCity("baster", false);
			Mtraxx_PlantBegin();
		break;
		
		case "mtraxx_27":
			pchar.quest.Mtraxx_PlantGoHomeOver.over = "yes"; 
            dialog.text = "Welcome back, my brave corsair, ha-ha! Did you take down a Spanish squadron? Picard has already told me. Nicely done!";
			link.l1 = "Yeah, my boys gave them a good kicking when we were sailing away from Maracaibo.";
			link.l1.go = "mtraxx_28";
			if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup3"))
			{
				dialog.text = "Welcome back, my brave corsair, ha-ha! Picard has already told me. Well done!";
				link.l1 = "...";
				link.l1.go = "mtraxx_28";
			}
		break;
		
		case "mtraxx_28":
            dialog.text = "I can see it in your eyes that you're waiting for your reward. Fair enough. Jean will pay you, after all, it was his life we were trying to save there. Send him a bill, but later – the lad doesn't have a crew or a ship. He's a smart kid, just like you, so his current state won't last long.";
			link.l1 = "Hm... Well... I'll bide my time. Any work for me, Marcus? Nothing to do with saving or searching for anyone?";
			link.l1.go = "mtraxx_29";
		break;
		
		case "mtraxx_29":
            dialog.text = "Tired of being the brightest candle? I have to disappoint you there: I have enough brainless brutes like Cutlass, so I'll use your talents accordingly. I'll have a job for you in a month. For now, you should sail to Isla Tesoro and see Pasquale Lavoisier, he is a merchant of Sharptown.\nHe asked for a tough pirate to be sent to him as soon as possible for serious business – most likely just what you want: less thinking and more shooting. You have a week to present yourself to him, so don't waste time or you'll lose this mission. And be polite, don't try to deceive him, this man is respected among the Brethren. Now go, and see me in a month. Don't be late!";
			link.l1 = "Fine, Marcus. See you!";
			link.l1.go = "mtraxx_30";
		break;
		
		case "mtraxx_30":
            DialogExit();
			// belamour legendary edition забрать флаг обратно
			if(CheckAttribute(pchar, "questTemp.GiveMeSpaFlag")) 
			{
				DeleteAttribute(pchar, "questTemp.GiveMeSpaFlag")); 
				DeleteAttribute(pchar,"perks.list.FlagSpa"); 
				log_info("You have given spanish flag");
			}
			CloseQuestHeader("Roger_3");
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_4", "1");
			pchar.questTemp.Mtraxx = "pasq_start";
			Mtraxx_PasqualeBegin();
			SetFunctionTimerCondition("Mtraxx_PlantFithTaskTimer", 0, 0, 35, false);
			SaveCurrentNpcQuestDateParam(npchar, "task_date");
		break;
		
		case "mtraxx_31":
            dialog.text = "Whoa! A dead man has returned! We already buried you, boy! But it seems you're still alive";
			link.l1 = "As you can see, Marcus...";
			link.l1.go = "mtraxx_32";
		break;
		
		case "mtraxx_32":
            dialog.text = "Then why did it take you so long to get to Hispaniola from Maracaibo? You are out of my organization now, boy. I am truly glad to see you alive, but there are no more jobs for you here.";
			link.l1 = "Eh!.. What a pity...";
			link.l1.go = "mtraxx_33";
		break;
		
		case "mtraxx_33":
            DialogExit();
            npchar.dialog.currentnode = "First time";
			pchar.questTemp.Mtraxx = "fail";
		break;
		
		case "mtraxx_34x":
            DialogExit();
            npchar.dialog.currentnode = "mtraxx_34";
		break;
		
		case "mtraxx_34":
			/*if (GetNpcQuestPastDayParam(npchar, "task_date") >= 35 && !bImCasual) // опоздал
			{
				dialog.text = "Damn it "+pchar.name+", where have you been?! I told you to see me in a month! This is not the military, but some bloody discipline is expected! Get lost, I will not work with you anymore!";
				link.l1 = "As you wish...";
				link.l1.go = "mtraxx_33";
				break;
			}*/
			if (GetNpcQuestPastDayParam(npchar, "task_date") < 28) // рано пришёл
			{
				dialog.text = ""+pchar.name+", I told you 'see me in a month.' I have no time to spare for you right now.";
				link.l1 = "Fine...";
				link.l1.go = "mtraxx_34x";
				break;
			}
			if (pchar.questTemp.Mtraxx == "pasq_angry")
			{
				dialog.text = "An agent of Lavoisier told me that you screwed him over with his black wood. I warned you not to be a rat and to be fair to Pasquale. You have broken both of my rules. You are a smart kid, but this is unacceptable. Get the hell out of here and forget the road to this place.";
				link.l1 = "Shit...";
				link.l1.go = "AngryExitAgainWithOut";
				pchar.questTemp.Mtraxx = "fail";
				npchar.dialog.currentnode = "First time";
				CloseQuestHeader("Roger_4");
				break;
			}
			if (pchar.questTemp.Mtraxx == "pasq_fail")
			{
				dialog.text = "An agent of Lavoisier told me that you screwed him over with his black wood - didn't bring the whole batch. If it had been a brainless Cutlass or Bald, perhaps I would have believed they hadn't really captured the whole load, but someone as clever as you... Decided to fool Pasquale? I told you 'don't deceive him'! I have no more confidence in you, and I have no more business with you either. Get the hell out of here and forget the road to this place!";
				link.l1 = "Your Lavoisier is a rat himself!";
				link.l1.go = "AngryExitAgainWithOut";
				pchar.questTemp.Mtraxx = "fail";
				npchar.dialog.currentnode = "First time";
				CloseQuestHeader("Roger_4");
				break;
			}
			if (pchar.questTemp.Mtraxx == "pasq_late" || pchar.questTemp.Mtraxx == "pasq_sink" || pchar.questTemp.Mtraxx == "pasq_esc")
			{
				pchar.questTemp.Mtraxx.CharleePrince = "true"; // атрибут - ГГ известный пират // правки прогона 3
				dialog.text = "Ha! Charlie Prince, a brave captain! That's your new name in La Vega, in case you didn't know. So, did you enjoy playing the brute? No? Has Lady Luck turned her back on you this time? This is how my brainless agents like Cutlass live: today he parties in a brothel, squandering everything he earned, and in a week he's at my doorstep begging for a couple of thousand to pay his crew of fools, just like him. Whatever. Let's talk business?";
				link.l1 = "Sure!";
				link.l1.go = "mtraxx_36";
				break;
			}
            dialog.text = "Ha! Charlie Prince, a brave captain! Ha-ha! An agent of Lavoisier told me you did well. I am glad you managed to show some respect to our profiteer.";
			link.l1 = "It wouldn't hurt if he were a bit more generous...";
			link.l1.go = "mtraxx_35";
		break;
		
		case "mtraxx_35":
			pchar.questTemp.Mtraxx.Pasquale.Continue = "true"; // правки прогона 3
            dialog.text = "Remember what I said about brainless brutes and buyers of stolen goods? Right. Never take a job like this in the future. Leave it to Cutlass and people like him. Anyway. Let's talk business?";
			link.l1 = "Sure!";
			link.l1.go = "mtraxx_36";
		break;
		
		case "mtraxx_36":
            dialog.text = "Great! Jean Picard is coming here, he will tell you more. You and Jean will work together on this mission. Plus, it's his chance to repay his debt to you... There he is!";
			link.l1 = "...";
			link.l1.go = "mtraxx_37";
		break;
		
		case "mtraxx_37":
            DialogExit();
            npchar.dialog.currentnode = "mtraxx_38";
			chrDisableReloadToLocation = true;
			// преобразуем Пикара
			sld = characterFromId("Mrt_Rocur");
			sld.model = "Jan_Pikar";
		
			SetCharacterPerk(sld, "GunProfessional");
			RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(sld, GUN_ITEM_TYPE);
			GiveItem2Character(sld, "blade_17");
			EquipCharacterbyItem(sld, "blade_17");
			GiveItem2Character(sld, "pistol6");
			EquipCharacterbyItem(sld, "pistol6");
			TakeNItems(sld, "bullet", 40);
			TakeNItems(sld, "gunpowder", 40);
			LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "bullet");
			GiveItem2Character(sld, "cirass7");
			EquipCharacterbyItem(sld, "cirass7");
			sld.dialog.currentnode = "rocur_29";
			sld.greeting = "Rocur_03";
			Characters_RefreshModel(sld);
			LAi_SetCheckMinHP(sld, 10, true, "");
			TakeNItems(sld, "potion2", 7);
			TakeNItems(sld, "potion3", 7);
			TakeNItems(sld, "potion4", 7);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "mtraxx_38":
            dialog.text = "My man will join your raid. Name's Luka Bayard, mostly known as Luke Leprechaun. He and his men are buccaneers—hunters who have spent most of their lives in the forests of Hispaniola. So they are masters at trekking through the jungle; add your fighters to theirs and consider Merida yours. You'll take a third of the loot. The rest goes to Jean. Jean, you'll pay your debt to this brave captain from your share, then bring what's left to me. We'll settle things between us then. Questions? Splendid! Leprechaun will be waiting for you in our harbour. Good luck, corsairs, ha-ha!";
			link.l1 = "...";
			link.l1.go = "mtraxx_39";
		break;
		
		case "mtraxx_39":
            DialogExit();
			CloseQuestHeader("Roger_4");
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_5", "1");
			pchar.questTemp.Mtraxx = "merida_start";
			Mtraxx_MeridaBegin();
			LAi_SetHuberType(npchar);
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "Mtraxx_MeridaAddPicar", 5.0);
			pchar.GenQuest.HunterLongPause = true;
		break;
		
		case "mtraxx_40":
            dialog.text = "Welcome back, my brave cutthroat! Word of your raid has already reached us.";
			link.l1 = "Can't say I like hearing it. Such things are better left unknown...";
			link.l1.go = "mtraxx_41";
		break;
		
		case "mtraxx_41":
            dialog.text = "Trust me, they never are, my friend. Whatever. Has Picard paid off his debt to you?";
			link.l1 = "Yes.";
			link.l1.go = "mtraxx_42";
		break;
		
		case "mtraxx_42":
            dialog.text = "Very good. Did Luke Leprechaun make a good impression on you?";
			link.l1 = "He did.";
			link.l1.go = "mtraxx_43";
		break;
		
		case "mtraxx_43":
            dialog.text = "Perfect then. Everyone is happy, everyone is paid.";
			link.l1 = "Do you have a job for me, Marcus?";
			link.l1.go = "mtraxx_44";
			// belamour legendary edition отказ после событий Мериды
			link.l2 = "You know, Marcus, I've weighed everything and this job is not for me. I'm sorry, but I've already made up my mind.";
			link.l2.go = "mtraxx_44a";
		break;
		
		case "mtraxx_44":
            dialog.text = "No real job yet. Although I have a personal favour to ask. Interested?";
			link.l1 = "Sure, boss. What favour?";
			link.l1.go = "mtraxx_45";
		break;
		
		case "mtraxx_45":
            dialog.text = "There is a pinnace, 'Kittie', near the shores of La Vega. She has been there for days, waiting for an escort to Bridgetown. There is no way I am letting her sail there alone, for obvious reasons. Would you be kind enough to accompany her? I'll have a real job for you when you return. And, of course, money to pay you for this escort.";
			link.l1 = "Deal.";
			link.l1.go = "mtraxx_46";
		break;
		
		case "mtraxx_46":
            dialog.text = "Nice! Good sailing.";
			link.l1 = "Thanks!";
			link.l1.go = "mtraxx_47";
		break;
		
		case "mtraxx_47":
            DialogExit();
			sld = characterFromId("Mrt_Rocur");
			RemovePassenger(pchar, sld);
			sld = characterFromId("Lepricon");
			RemovePassenger(pchar, sld);
			LAi_SetWarriorType(sld);
			ChangeCharacterAddressGroup(sld, "none", "", "");
			CloseQuestHeader("Roger_5");
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_6", "1");
			pchar.questTemp.Mtraxx = "ignasio_start";
			sld = characterFromId("Mtr_KittyCap");
			DeleteAttribute(sld, "DontDeskTalk");
			LocatorReloadEnterDisable("LaVega_port", "boat", false);
		break;
		// belamour legendary edition -->
		case "mtraxx_44a":
            dialog.text = "What?! I pulled you off the street, filled your pockets with amber and gems! Is this how you repay me?";
			link.l1 = "Merida showed me that I'm not ruthless enough for this job. Not as ruthless as you and your men. Don't be cruel.";
			link.l1.go = "mtraxx_45a";
		break;
		
		case "mtraxx_45a":
            dialog.text = "Weakling! Well, get lost! Go haul some freight or, better yet, drink yourself to death like the rest of the losers!";
			link.l1 = "...";
			link.l1.go = "mtraxx_46a";
		break;
		
		case "mtraxx_46a":
            DialogExit();
			sld = characterFromId("Mrt_Rocur");
			RemovePassenger(pchar, sld);
			sld = characterFromId("Lepricon");
			RemovePassenger(pchar, sld);
			LAi_SetWarriorType(sld);
			ChangeCharacterAddressGroup(sld, "none", "", "");
			CloseQuestHeader("Roger_5");
			npchar.dialog.currentnode = "First time";
			Group_DelCharacter("Mtr_Kitty", "Mtr_KittyCap");
			sld = characterFromId("Mtr_KittyCap");
			sld.lifeday = 0;
			LocatorReloadEnterDisable("LaVega_port", "boat", false);
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			pchar.questTemp.Mtraxx = "fail";
			if(CheckAttribute(pchar, "GenQuest.HunterLongPause")) DeleteAttribute(pchar, "GenQuest.HunterLongPause");
			DoQuestReloadToLocation("LaVega_town", "reload", "reload6", ""); // выставим за дверь
		break;
		// <--- legendary edition
		case "mtraxx_48":
			AddMoneyToCharacter(pchar, 10000);
            dialog.text = "Ah, there you are... I've been waiting for you. Here are 10,000 for escorting 'Kittie'.";
			link.l1 = "Thanks... I have something to discuss with you, Marcus.";
			link.l1.go = "mtraxx_49";
		break;
		
		case "mtraxx_49":
            dialog.text = "Do you?! Ha-ha! Shoot!..";
			link.l1 = "Remember how Jean Picard was enslaved? First, he plundered a Dutch caravan with a British privateer, and then the same was done to him by a Spanish heavy galleon.";
			link.l1.go = "mtraxx_50";
		break;
		
		case "mtraxx_50":
            dialog.text = "Remember. And?";
			link.l1 = "I was approached in Bridgetown by Ignacio Marco. The same Portuguese privateer who serves England. He offered me to plunder a Dutch caravan near the shores of an uninhabited island between Curacao and Trinidad.";
			link.l1.go = "mtraxx_51";
		break;
		
		case "mtraxx_51":
            dialog.text = "Well, well... Did you agree?";
			link.l1 = "I did. First off, it was a good deal. Secondly, I recalled Picard's story and decided to investigate...";
			link.l1.go = "mtraxx_52";
		break;
		
		case "mtraxx_52":
            dialog.text = "I bet you did.";
			link.l1 = "Yeah. There was a caravan, we did the job nice and clean. Then we split the spoils of it on shore, but first I quietly sent a watchman with a spyglass up on a hill. And it paid off, since a Spanish squadron appeared shortly after, led by a heavy galleon.";
			link.l1.go = "mtraxx_53";
		break;
		
		case "mtraxx_53":
            dialog.text = "Your partner surely fled, so the Spanish chased you?";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.LosadaSink")) 
			{
				link.l1 = "Exactly. They didn't even pay attention to him. Too bad for them: we fought the Spanish so hard they'll never forget it. Those Castilians were good fighters, but we managed to take down the whole squadron.";
				link.l1.go = "mtraxx_53x";
			}
			else
			{
				link.l1 = "Exactly. They didn't even pay attention to him. Although I managed to escape, thanks to my watchman...";
				link.l1.go = "mtraxx_53y";
			}
		break;
		
		case "mtraxx_53x":
			DeleteAttribute(pchar, "questTemp.Mtraxx.LosadaSink");
            dialog.text = "Heh! Taking down a squadron of Eduardo de Losad! You are a Sea Devil, Prince! I bet the Spanish have already sent hunters after your arse.";
			link.l1 = "Bad for them... Nevertheless, we should deal with this scum, Ignacio. If you know what I mean.";
			link.l1.go = "mtraxx_54";
		break;
		
		case "mtraxx_53y":
            dialog.text = "Heh! I can only imagine the shitstorm that erupted when the Castilians realised you'd slipped away from them! Nicely done!";
			link.l1 = "Their problem, not mine. Nevertheless, we should deal with this scum, Ignacio. If you know what I mean.";
			link.l1.go = "mtraxx_54";
		break;
		
		case "mtraxx_54":
            dialog.text = "I'll take care of it. We should learn more about this Ignacio Marco. He might be working for someone. His 'interest' in my men is suspicious. What ship does he own?";
			link.l1 = "A polacre, the 'Torero'. A unique vessel, must be an original design.";
			link.l1.go = "mtraxx_55";
		break;
		
		case "mtraxx_55":
            dialog.text = "Good, easier to track her then... I got it. And for you, Prince, I have a job. Ready for it?";
			link.l1 = RandSwear()+"By all means, chief!";
			link.l1.go = "mtraxx_56";
		break;
		
		case "mtraxx_56":
            dialog.text = "Listen then. Some time ago we had a curious pirate in our region. Name's Wulfric Iogansen, also known as Red Wolf. A very colourful character. He came here from the north of Europe a couple of years ago. This Viking wasn't paying Levasseur his protection fee, didn't make friends and kept to himself. A very secretive type, no one had ever left his crew alive. There were rumours that he personally cut out the tongues of those in his crew whose tongues loosened in taverns about their raids... Unlike most of our kind, Wulfric never wasted money on whores or drink. Never sold his plunder for pennies. Never trusted bankers and never changed ships. He had a fine corvette, the 'Freyja', and a loyal crew he paid well for service and for silence. I believe he was planning to stash as much gold as possible and then return to Europe to live there like a king. It didn't work out for him, thanks to the Spanish hunters. This man had inflicted colossal damage and losses on Spain, so punitive expeditions hunted him down in the waters of Hispaniola, sank the 'Freyja', and killed the whole crew along with Wolf. Surrounded in shallow water by Spanish ships, Red Wolf met his death. Thing is, everyone in La Vega knew about Wolf's treasures and even found the sunken 'Freyja', but neither local nor Indian divers found any treasure. He wasn't a fool and must have had a huge stash somewhere in that location only he and his crew knew about, but we can't ask them for... obvious reasons. But now comes the interesting part: I have his undamaged ship's log, which was hidden in a locked chest on his ship. It has no obvious leads to the treasure, but you may try to find them between the lines. Read the log, find out where the Viking hid his treasures after two years of robbery in the Caribbean, and find them. If you succeed – two thirds are yours. Are you in?";
			link.l1 = "Hm... sounds like looking for a black cat in a dark room. Where's the log?";
			link.l1.go = "mtraxx_57";
		break;
		
		case "mtraxx_57":
            dialog.text = "Here, take it. Good luck!";
			link.l1 = "Thanks, I'm going to need it...";
			link.l1.go = "mtraxx_58";
		break;
		
		case "mtraxx_58":
            DialogExit();
			CloseQuestHeader("Roger_6");
			npchar.dialog.currentnode = "mtraxx_wait";
			GiveItem2Character(pchar, "wolfreeks_book");
			AddQuestRecord("Roger_7", "1");
			pchar.questTemp.Mtraxx = "wolfreek_start";
			pchar.questTemp.Mtraxx.Logbook.CanRead = "true";
			pchar.questTemp.Mtraxx.Logbook.Page1 = "true";
			bQuestDisableMapEnter = true;//закрыть карту
			pchar.GenQuest.MapClosedNoBattle = true;
		break;
		
		case "mtraxx_59":
            dialog.text = "Ah, there is our brave captain. What of Red Wolf's treasure?";
			link.l1 = "I'm working on it. I need your help with this.";
			link.l1.go = "mtraxx_60";
		break;
		
		case "mtraxx_60":
            dialog.text = "I am all ears.";
			link.l1 = "There is an unknown word written several times in Wulfric's log, 'Gord'. I must know its meaning to move ahead in my investigation.";
			link.l1.go = "mtraxx_61";
		break;
		
		case "mtraxx_61":
            dialog.text = "Hm... Gord, you say... Never heard of it before either. Very well, see me in a week: I will consult with some clever minds who serve as pursers on ships. At least they know how to count and read. They may give us some idea.";
			link.l1 = "Fine, Marcus. See you in a week then.";
			link.l1.go = "mtraxx_62";
		break;
		
		case "mtraxx_62":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			SetFunctionTimerCondition("Mtraxx_WolfreekTimer", 0, 0, 7, false);
		break;
		
		case "mtraxx_63":
            dialog.text = "I have an answer for you. Some smartass enlightened me. A gord is a fortified settlement of a free jarl.";
			link.l1 = "A free jarl? Who is that?";
			link.l1.go = "mtraxx_64";
		break;
		
		case "mtraxx_64":
            dialog.text = "Some sort of pirate admiral of Vikings. For example, I am a free jarl and La Vega is my gord. Seems like Red Wolf enjoyed his ancestors' history, ha-ha! Did this information help you?";
			link.l1 = "Don't know yet. I should compare the notes first. So Gord means settlement... Thank you, Marcus!";
			link.l1.go = "mtraxx_65";
		break;
		
		case "mtraxx_65":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			Mtraxx_WolfreekReadLogbookFourth();
		break;
		
		case "mtraxx_66":
            dialog.text = "So? Your smug face tells me you succeeded.";
			link.l1 = "Yeah. Red Wolf's treasure has been found! It wasn't easy though.";
			link.l1.go = "mtraxx_67";
		break;
		
		case "mtraxx_67":
            dialog.text = "How much did our Viking stash?";
			link.l1 = "750,000 pesos and 900 doubloons.";
			link.l1.go = "mtraxx_68";
		break;
		
		case "mtraxx_68":
            dialog.text = "Ho-ho! You did well, Prince. What about my cut?";
			if (sti(pchar.money) >= 250000 && PCharDublonsTotal() >= 300) // belamour legendary edition
			{
				link.l1 = "Here, take this. As agreed: 250,000 pesos and 300 doubloons.";
				link.l1.go = "mtraxx_69";
			}
			else
			{
				link.l1 = "All pesos and doubloons are in my cabin. Give me a moment to bring them here!";
				link.l1.go = "mtraxx_68_1";
			}
		break;
		
		case "mtraxx_68_1":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_68_2";
		break;
		
		case "mtraxx_68_2":
            dialog.text = "Did you bring my cut?";
			if (sti(pchar.money) >= 250000 && PCharDublonsTotal() >= 300) // belamour legendary edition
			{
				link.l1 = "Here, take this. As agreed: 250,000 pesos and 300 doubloons.";
				link.l1.go = "mtraxx_69";
			}
			else
			{
				link.l1 = "Yes-yes, I am on my way!";
				link.l1.go = "mtraxx_68_1";
			}
		break;
		
		case "mtraxx_69":
			AddMoneyToCharacter(pchar, -250000);
			RemoveDublonsFromPCharTotal(300); // belamour legendary edition
			PlaySound("interface\important_item.wav");
            dialog.text = "Very good. You did great again. Well done!";
			link.l1 = "Marcus, did you find out anything about Ignacio Marco?";
			link.l1.go = "mtraxx_70";
			// mitrokosta возможность отстройки исламоны
			pchar.questTemp.IslaMona = "start";
		break;
		
		case "mtraxx_70":
            dialog.text = "Yes, but I need to verify it first...";
			link.l1 = "What?";
			link.l1.go = "mtraxx_71";
		break;
		
		case "mtraxx_71":
            dialog.text = "I have a suspicion that Marco is connected to someone... And I need you to find out who. Sail to Martinique. Leave your ship in Saint Pierre and make your way to Le Francois through the jungle. I've been told our man has been seen there. Don't ask the pirates around, just watch and observe. Once you find him, follow and see where he goes or whom he meets. Do not attack him or his ship, for by doing so you'd ruin a plan I am preparing right now! I have warned you! Follow and watch him, then return to me once you've learned enough. I understand your hands are itching to strangle the bastard, but keep your mind calm. Now go. You have three weeks. Good luck.";
			link.l1 = "On my way, boss.";
			link.l1.go = "mtraxx_72";
		break;
		
		case "mtraxx_72":
            DialogExit();
			CloseQuestHeader("Roger_7");
			RemoveItems(pchar, "wolfreeks_book", 1);
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_8", "1");
			pchar.questTemp.Mtraxx = "corrida_start";
			pchar.quest.mtraxx_corrida_martinique.win_condition.l1 = "location";
			pchar.quest.mtraxx_corrida_martinique.win_condition.l1.location = "Martinique";
			pchar.quest.mtraxx_corrida_martinique.function = "Mtraxx_CorridaStart";
			pchar.quest.mtraxx_pasq_continue.win_condition.l1 = "location";
			pchar.quest.mtraxx_pasq_continue.win_condition.l1.location = "LaVega_exittown";
			pchar.quest.mtraxx_pasq_continue.function = "Mtraxx_PasqualeJan";
			bDisableFastReload = true;
			//SaveCurrentNpcQuestDateParam(npchar, "task_date");
		break;
			
		case "mtraxx_73":
			/*if (GetNpcQuestPastDayParam(npchar, "task_date") >= 22) // опоздал
			{
				dialog.text = "Damn it, Prince! You could have had your revenge and a hellish sum of money if you weren't so slow! I didn't expect this from you, but since you're a good kid, I forgive you. You'll have a chance to regain your reputation in my eyes in a month. I'm gathering everyone for a raid!\nCome to me in a month on a single but powerful ship. Luke, Cutlass, Geffrey, and Jean will take part in this too. Don't be late, not even for a day!";
				link.l1 = "I understand, Marcus. Won't happen again!";
				link.l1.go = "mtraxx_73x";
				break;
			}*/
			dialog.text = "Good timing! Report to me, now.";
			link.l1 = "I've tracked my obligor to Le Francois. His polacre was part of a squadron consisting of a corvette and a frigate. Marco himself paid a visit to Barbaszon; they had a meeting at his place for two hours, and other visitors were sent away by his guards. Then he left the house with two gloomy fellows: one was red-haired and bearded, wearing a reiter cuirass; the other had a moustache and wore heavy trench armour. They all went to the port and sailed away before I reached Saint Pierre.";
			link.l1.go = "mtraxx_74";
		break;
		
		/*case "mtraxx_73x":
            DialogExit();
            npchar.dialog.currentnode = "First time";
			pchar.questTemp.Mtraxx = "wait_month";
			AddQuestRecord("Roger_8", "5");
			SetFunctionTimerCondition("Mtraxx_CartahenaTavernPrepare", 0, 0, 1, false); // belamour legendary edition увеличим таймер 
			SetFunctionTimerCondition("Mtraxx_CartahenaPrepare", 0, 0, 1, false);
			SetFunctionTimerCondition("Mtraxx_CartahenaLate", 0, 0, 92, false);
		break;*/
		
		case "mtraxx_74":
            dialog.text = "That is fine. Now I see the whole picture. Those two bastards you saw work either for Barbazon or for Jackman. They are almost like my Bald and Cutlass, but they fight better. The red-haired one is called Prowler, he is captain of the 'Cuttlefish', a corvette, and the guy with the moustache is Ghoul, he sails the 'Merciless', a frigate. As for our friend Ignacio - he is working not only for the Brits and the Spanish don Losad, but also for Barbazon. This is why he tried to frame you and Picard.";
			link.l1 = "Why?";
			link.l1.go = "mtraxx_75";
		break;
		
		case "mtraxx_75":
            dialog.text = "Barbazon's order. You didn't know, but Jacques never misses a chance to piss in my porridge. He would never openly oppose me for obvious reasons, so he crosses me in secret. He knew that Picard and you are my men. Sending his mercenary after you was just his style, and he didn't send an idiot, as you've seen for yourself.";
			link.l1 = "I'll pay Barbazon a visit as soon as I take care of Marco...";
			link.l1.go = "mtraxx_76";
		break;
		
		case "mtraxx_76":
            dialog.text = "Get this shit out of your head! You have no chance against Barbazon in open conflict. He will easily fuck you up. We will repay him with his own trickery - by hitting his associates. Ready to do that? It's a messy business.";
			link.l1 = "Sounds like my kind of business!";
			link.l1.go = "mtraxx_77";
		break;
		
		case "mtraxx_77":
            dialog.text = "Ignacio Marco, Prowler, Goul, and another of Barbazon's men called Joker Jim have a plan to capture one of the Spanish ships from the Golden Fleet. The whole operation was devised by Barbazon himself, and I've managed to learn the details from my spies. One heavy galleon of the Golden Fleet lingered in Havana at the shipyard, while the rest of the squadron departed for Spain. The galleon was repaired and will soon be heading to Europe, along with two more ships. The squadron will sail from Cuba to the northeast, but I don't know the exact route.\nI've been informed that the Spanish ships intend to sail to Santo Domingo, then along the shores of Puerto Rico and straight into the ocean. Barbazon knows this as well. However, since Hispaniola can be rounded not only from the south but also from the north, changing the route and leaving for the ocean through Turks or Isla-Tesoro without entering Santo Domingo, Jacques decided to play it safe and sent the cunning fox Ignacio to Cuba.\nMarco's task is to obtain the sailing schedule of the Spanish galleon which is going to depart from Cuba and is supposed to catch up with the rest of the Fleet later. He has connections within the Spanish, so this task shouldn't be a problem for him. The rest of Barbazon's band is waiting for Marco at Saint Martin, which is an optimal place to start hunting this prize. Since Marco and the Dutch are not on good terms, he won't be able to enter Saint Martin's waters, so he'll have to send his mates a message from afar...";
			link.l1 = "I suppose I know what I'm meant to do here...";
			link.l1.go = "mtraxx_78";
		break;
		
		case "mtraxx_78":
            dialog.text = "It strikes me that you are quite clever, but I haven't finished yet. I disrupted this plan with help from Gabriela Chapada. You know her. Together, we informed the Spanish that the pirate ambush would be set not far from Puerto Rico. So the galleon won't be sailing through that area, but they have secretly sent a squadron of pirate hunters there instead. You have a number of tasks. The first will be to find and capture the 'Torero'. I suppose you know what to do with her captain.";
			link.l1 = "Naturally...";
			link.l1.go = "mtraxx_79";
		break;
		
		case "mtraxx_79":
            dialog.text = "Secondly, you will need to find out the real course of the Spanish golden galleon. Marco must have its schedule. Get it and send it to me.";
			link.l1 = "How?";
			link.l1.go = "mtraxx_80";
		break;
		
		case "mtraxx_80":
			GiveItem2Character(pchar, "Dove"); 
            dialog.text = "By air. Take a cage... This is Spyke, a carrier pigeon born and raised here in La Vega. He will always find his way back here, even from Trinidad. Once you obtain the schedule, write a note, attach it to his leg, and release him. Spyke will fly to me within a few hours. Take care of him, Prince!";
			link.l1 = "Of course, boss!";
			link.l1.go = "mtraxx_81";
		break;
		
		case "mtraxx_81":
            dialog.text = "Third, sail to Saint Martin on the 'Torero'. Only on her alone! Otherwise, they will get suspicious too soon. Send them a signal to sail to Puerto Rico, where the Spanish await. Their signal codes must be in Marco's papers. Or you can learn them from him personally.";
			link.l1 = "I see. A clever move to send Barbazon's men to the Spanish, ha-ha!";
			link.l1.go = "mtraxx_82";
		break;
		
		case "mtraxx_82":
            dialog.text = "Exactly! I will strike him from the shadows. Just as he did. And one last thing: once you send them a signal, immediately set sail to intercept the Spanish galleon and her escort. There will be no time to waste.";
			link.l1 = "On a polacre? Against a heavy galleon and two more ships, and certainly no schooners? They'll tear me apart!";
			link.l1.go = "mtraxx_83";
		break;
		
		case "mtraxx_83":
            dialog.text = "Stop crying like a little girl! Why do you think you'll send me Spyke? You won't be left without reinforcements. Just don't let the caravan escape, don't let them reach the ocean. Got it?";
			link.l1 = "Yes, boss.";
			link.l1.go = "mtraxx_84";
		break;
		
		case "mtraxx_84":
            dialog.text = "Your reward will be a hefty load of gold plus Marco's polacre. People say she is a damn good ship. Any questions? Do you understand your mission?";
			link.l1 = "I am not Cutlass, I know what to do. Where should I intercept the 'Torero'?";
			link.l1.go = "mtraxx_85";
		break;
		
		case "mtraxx_85":
            dialog.text = "While we are having this chat, the ship is swiftly sailing straight to Philipsburg from Cuba. Must be near Tortuga now, or a bit to the east of it. So raise anchor and sail to Saint Martin, intercept the 'Torero' not far from the island, just don't let Barbazon's men see the fight, otherwise my plan will be ruined.";
			link.l1 = "Right away!";
			// belamour legendary edition испанский флаг к выдаче -->
			if(IsCharacterPerkOn(pchar,"FlagSpa")) link.l1.go = "mtraxx_86";
			else link.l1.go = "mtraxx_85f";
		break;
		
		case "mtraxx_85f":
			SetCharacterPerk(pchar, "FlagSpa");
			log_info("You have received a spanish flag");
			pchar.questTemp.GiveMeSpaFlag = true;
            dialog.text = "What the hell? I'd smack you with a fireplace poker, Prince. I didn't think I'd have to explain such basic things. Hold on to the Spanish flag, or you'll ruin everything before it even begins. Give it back to me. Now get out of here!";
			link.l1 = "I'm already at sea, Boss";
			link.l1.go = "mtraxx_86";
		break;
		// <-- legendary edition
		case "mtraxx_86":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			AddQuestRecord("Roger_8", "6");
			pchar.questTemp.Mtraxx = "corrida_marko";
			/*pchar.quest.mtraxx_corrida_landtimer.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_corrida_landtimer.win_condition.l1.date.hour  = sti(GetTime()+1);
			pchar.quest.mtraxx_corrida_landtimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.mtraxx_corrida_landtimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.mtraxx_corrida_landtimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.mtraxx_corrida_landtimer.function = "Mtraxx_CorridaLandTimer";
			pchar.quest.mtraxx_corrida_checktime.win_condition.l1 = "location";
			pchar.quest.mtraxx_corrida_checktime.win_condition.l1.location = "Hispaniola1";
			pchar.quest.mtraxx_corrida_checktime.function = "Mtraxx_CorridaCheckTime";*/
			pchar.quest.mtraxx_corrida_torero.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_corrida_torero.win_condition.l1.date.hour  = sti(GetTime()+12);
			pchar.quest.mtraxx_corrida_torero.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtraxx_corrida_torero.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtraxx_corrida_torero.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtraxx_corrida_torero.function = "Mtraxx_CorridaToreroOnMap";
			SetFunctionTimerCondition("Mtraxx_CorridaTimeFindTorero", 0, 0, 7, false); // время на перехват Тореро, снимать при потоплении или захвате
		break;
		
		case "mtraxx_87":
            dialog.text = "So Prince, you screw everything up, huh?";
			link.l1 = "I did. This mission was a much bigger challenge than I thought. You can give me an angry speech and show me the door.";
			link.l1.go = "mtraxx_88";
		break;
		
		case "mtraxx_88": // belamour legendary edition увеличиваем срок
            dialog.text = "Come on, quit it. It happens. You're a good corsair and we all fail sometimes. Pity we didn't get that gold... but if we didn't get it in one place, we'll get it somewhere else, ha-ha! You'll have a chance to restore your reputation: come to me in three weeks, and preferably on a stronger ship, but only one - we'll be a whole squadron. I'm gathering everyone for a raid!\nCome to me in three weeks on a single but powerful ship. Luke, Cutlass, Geffrey and Jean will take part as well. Don't be late!";
			link.l1 = "I won't, boss!";
			link.l1.go = "mtraxx_89";
		break;
		
		case "mtraxx_89":
            DialogExit();
			// belamour legendary edition забрать флаг обратно
			if(CheckAttribute(pchar, "questTemp.GiveMeSpaFlag")) 
			{
				DeleteAttribute(pchar, "questTemp.GiveMeSpaFlag")); 
				DeleteAttribute(pchar,"perks.list.FlagSpa"); 
				log_info("You have given a spanish flag");
			}
			npchar.dialog.currentnode = "First time";
			pchar.questTemp.Mtraxx = "wait_month";
			AddQuestRecord("Roger_8", "22");
			SetFunctionTimerCondition("Mtraxx_CartahenaTavernPrepare", 0, 0, 1, false); // belamour legendary edition увеличим таймер 
			SetFunctionTimerCondition("Mtraxx_CartahenaPrepare", 0, 0, 1, false);
			//SetFunctionTimerCondition("Mtraxx_CartahenaLate", 0, 0, 92, false);
			if (CheckCharacterItem(pchar, "Dove")) RemoveItems(pchar, "Dove", 1);
		break;
		
		case "mtraxx_board":
            dialog.text = "Ho-ho, ahoy, kid! Didn't expect to see me here, did you? Ha-ha-ha! We've found the Spanish caravan after all...";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Gold")) // был абордаж
			{
				link.l1 = "Yes boss, we have, although it wasn't easy.";
				link.l1.go = "mtraxx_board_1";
			}
			else
			{
				link.l1 = "Yeah, but the Golden Galleon was sunk with all her gold.";
				link.l1.go = "mtraxx_board_7";
			}
		break;
		
		case "mtraxx_board_1":
			iTotalTemp = GetSquadronGoods(pchar, GOOD_GOLD);
            dialog.text = "How much gold did we get, Prince?";
			if (iTotalTemp < 1) link.l1 = "Eh... Nothing.";
			else link.l1 = "Heh... "+iTotalTemp+" in total!";
			link.l1.go = "mtraxx_board_2";
		break;
		
		case "mtraxx_board_2":
			if (iTotalTemp < 20)
			{
				dialog.text = "Damn it! The Spanish must have thrown it into the sea so we wouldn't get it. At least they paid for it. As did Barbazon's men, which is also a victory...";
				link.l1 = "Sorry about the gold... What now, Marcus? Are we going to La Vega?";
				link.l1.go = "mtraxx_board_4";
				AddQuestRecord("Roger_8", "18");
				break;
			}
			if (iTotalTemp >= 20 && iTotalTemp < 300)
			{
				dialog.text = "Pathetic. It doesn't even cover the cost of my trip here. The Spanish must have thrown it into the sea so we wouldn't get it. At least they paid for it. As did Barbazon's men, which is also a victory...";
				link.l1 = "Sorry about the gold... Let's split it anyway.";
				link.l1.go = "mtraxx_board_3";
				AddQuestRecord("Roger_8", "19");
				break;
			}
			if (iTotalTemp >= 300 && iTotalTemp < 700)
			{
				dialog.text = "This is a poor prize. Just enough to cover expenses. The Spanish must have thrown part of it into the sea so we wouldn't get it. At least they paid for it. As did Barbazon's men, which is also a victory...";
				link.l1 = "Sorry about the gold... Let's split it anyway.";
				link.l1.go = "mtraxx_board_3";
				AddQuestRecord("Roger_8", "19");
				AddCharacterExpToSkill(pchar, "Fortune", 100);
				break;
			}
			if (iTotalTemp >= 700 && iTotalTemp < 1000)
			{
				dialog.text = "Not bad, although I expected better. The Spanish must have thrown part of it into the sea so we wouldn't get it. At least they paid for it. As did Barbazon's men, which is also a victory...";
				link.l1 = "Let's split the prize!";
				link.l1.go = "mtraxx_board_3";
				AddQuestRecord("Roger_8", "20");
				AddCharacterExpToSkill(pchar, "Fortune", 200);
				break;
			}
			dialog.text = "Splendid! We got a fine prize, my friend! And Barbazon's men got what they deserved, ha-ha!";
			link.l1 = "Heh, that's a lot of gold! Let's split it!";
			link.l1.go = "mtraxx_board_3";
			AddQuestRecord("Roger_8", "21");
			AddCharacterExpToSkill(pchar, "Fortune", 300);
		break;
		
		case "mtraxx_board_3":
			RemoveCharacterGoods(pchar, GOOD_GOLD, makeint(iTotalTemp/2));
			WaitDate("", 0, 0, 0, 3, 10);
			LAi_Fade("", "");
            dialog.text = "... like we always do in the Brethren - a fair share for each. You can keep the 'Torero', she is your prize.";
			link.l1 = "What's next, Marcus? Are we going to La Vega?";
			link.l1.go = "mtraxx_board_4";
		break;
		
		case "mtraxx_board_4": // belamour legendary edition увеличиваем срок до 3х месяцев
            dialog.text = "I'll definitely be in La Vega, I'll be waiting for you there for three weeks. Come when you're ready. Preferably on a stronger ship, but only one - we will be a whole squadron. I'm getting all my people on the march. You will go under my command, Jean Handsome, Bald Geoffrey, Cleaver Pelly and Luke Leprechaun as well. Get ready. We are expecting a serious expedition and rather big booty. You will find out all the details later.";
			link.l1 = "Fine, boss! See you in La Vega in three weeks.";
			link.l1.go = "mtraxx_board_5";
		break;
		
		case "mtraxx_board_5":
            dialog.text = "Farewell, cutthroat! Ha-ha!";
			link.l1 = "...";
			link.l1.go = "mtraxx_board_6";
		break;
		
		case "mtraxx_board_6":
            DialogExit();
            npchar.dialog.currentnode = "mtraxx_board_6x";
			npchar.DeckDialogNode = "mtraxx_board_6x";
			npchar.DontDeskTalk = true;
			Ship_SetTaskRunAway(SECONDARY_TASK, sti(npchar.index), sti(pchar.index));
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			pchar.quest.mtraxx_corrida_complete.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_corrida_complete.function = "Mtraxx_CorridaComplete";
			RemoveItems(pchar, "wolfreeks_book", 1);
			// belamour legendary edition забрать флаг обратно
			if(CheckAttribute(pchar, "questTemp.GiveMeSpaFlag")) 
			{
				DeleteAttribute(pchar, "questTemp.GiveMeSpaFlag")); 
				DeleteAttribute(pchar,"perks.list.FlagSpa"); 
				log_info("You have given spanish flag");
			}
		break;
		
		case "mtraxx_board_6x":
            dialog.text = "Anything else?";
			link.l1 = "No, I don't think so. I'm already heading to my ship.";
			link.l1.go = "mtraxx_board_6y";
		break;
		
		case "mtraxx_board_6y":
            DialogExit();
			npchar.DeckDialogNode = "mtraxx_board_6x";
		break;
		
		case "mtraxx_board_7":
            dialog.text = "Heh! And whose fault is that, Prince? Was it yours?";
			link.l1 = "I am sorry, boss, but we were both good enough... You did an excellent job shooting too. Nice aim, by the way...";
			link.l1.go = "mtraxx_board_8";
		break;
		
		case "mtraxx_board_8":
            dialog.text = "Whatever. The fault is on both of us. We are not empty-handed though - Barbazon's men got what we had for them, a victory in itself...";
			link.l1 = "Sorry about the gold... What's next, Marcus? Are we going to La Vega?";
			link.l1.go = "mtraxx_board_4";
		break;
		
		case "mtraxx_90x":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_90";
		break;
		
		case "mtraxx_90":
			pchar.quest.Mtraxx_CartahenaLate.over = "yes";
			if (GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = "Prince, have you lost your mind? I told you to bring only one ship! Go get rid of the extra one and come back as soon as possible! Now!";
				link.l1 = "Alright, alright!";
				link.l1.go = "mtraxx_90x";
				break;
			}
			if (RealShips[sti(pchar.Ship.Type)].Type.Merchant) // торговые
			{
				dialog.text = "Prince, have you decided to be my second Cutlass? Why did you bring a trade vessel to me? I was counting on you! Go and bring me a proper warship! Now!";
				link.l1 = "Alright, alright!";
				link.l1.go = "mtraxx_90x";
				break;
			}
			if (sti(RealShips[sti(pchar.ship.type)].Class) > 3)
			{
				dialog.text = "Prince, you have surprised me. I told you to bring a warship! How are you going to help me on this tub? Come back here on a third or second rank ship, no less and no higher! Now! I am not going to wait for anyone.";
				link.l1 = "Alright, alright!";
				link.l1.go = "mtraxx_90x";
				break;
			}
			if (sti(RealShips[sti(pchar.ship.type)].Class) < 2)
			{
				dialog.text = "Prince, why don't you bring the Sovereign of the Seas here? When I told you to bring a warship, I didn't mean a bloody ship of the line! Come back here on a third or second rate vessel! Now! I am not going to wait for anyone.";
				link.l1 = "Alright, alright!";
				link.l1.go = "mtraxx_90x";
				break;
			}
            dialog.text = "Good timing, corsair! Glad to see you in one piece! Ready for a voyage?";
			link.l1 = "Sure thing, chief. Always ready.";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Barbazon")) link.l1.go = "mtraxx_91";
			else link.l1.go = "mtraxx_94";
		break;
		
		case "mtraxx_91":
            dialog.text = "By the way, do you want to know about Barbazon's squadron you sent to Puerto Rico?";
			link.l1 = "They have completely slipped my mind. Of course I want to know. Did they meet their doom?";
			link.l1.go = "mtraxx_92";
		break;
		
		case "mtraxx_92":
            dialog.text = "Hell yes, they did! The flagship – Joker Jim's frigate 'Owl' – burned to the waterline. Joker Jim himself has vanished without a trace. The Tramp and Ghoul were badly beaten, but they managed to escape: the Tramp to Tortuga, under the protection of La Rocha's cannons, and the Ghoul to Isla Tesoro. Pasquale told me that Ghoul also ran his ship aground on the reefs near Sharptown and barely got her off. Master Alexus has his work cut out for him now, hehe. All in all, the Spaniards disappointed me a little. I thought they'd kill everyone.";
			link.l1 = "Heh. Whatever, we still pissed in Barbazon's boots. Sent him a message.";
			link.l1.go = "mtraxx_93";
		break;
		
		case "mtraxx_93":
            dialog.text = "True. Let's talk business.";
			link.l1 = "I am all ears.";
			link.l1.go = "mtraxx_94";
		break;
		
		case "mtraxx_94":
            dialog.text = "My intelligence service, in the form of my good friend Bernard Vensan, has reported a huge pile of gold ingots stored by the Spanish in Cartagena. Under its fort, to be more specific. Normally, it would have been attributed to the Golden Fleet of Spain, but this time it is ours for the taking. We are heading to the Spanish Main to storm Cartagena.";
			link.l1 = "Argh! Did I hear that right? Are we going to plunder an entire colony, with a bloody fort?";
			link.l1.go = "mtraxx_95";
			// belamour legendary edition отказ от великого похода
			link.l2 = "I'm not going to Cartagena with you, Marcus. Burning down an entire city is not my story.";
			link.l2.go = "mtraxx_94a";
		break;
		
		case "mtraxx_95":
            dialog.text = "You heard right. That's exactly what we're going to do. My warship will deal with the fort, with your help of course. Bold Jeffrey will be carrying ground troops on his new East Indiaman, stolen from the Dutch. Pelly has finally got rid of his battered brigantine and acquired a decent corvette, not without my financial aid, of course. Paul Chant and you are responsible for taking out the patrol fleet; your crews will also take part in the assault, and you, Charles, such a fine fighter and captain, will help me destroy the fort. Jean Picard didn't show up, which is strange since his corvette has been seen in Port Royal. Well, if he isn't interested in Spanish gold, that's his problem, so to hell with him. Instead of him, my friend Bernard Vensan will join the raid. Plus, Leprechaun and his buccaneers will assist our troops. We will take the gold from the fort and ransom from the city. They won't forget it, ha-ha!  Now, go rest. And come join me and the other captains in the tavern this evening! We should drink to our cause! I'll order the bartender to drive out all the local drunks, so only the six of us and some charming girls will be in the tavern. You're drinking with your comrades tonight, and tomorrow morning you'll lead the squadron, you'll set the course. And try to bring us to Cartagena as soon as possible. All clear?";
			link.l1 = "Aye, aye, chief!";
			link.l1.go = "mtraxx_96";
		break;
		
		case "mtraxx_96":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			chrDisableReloadToLocation = true;
			CloseQuestHeader("Roger_8");
			pchar.questTemp.Mtraxx = "cartahena";
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, "LaVega_townhall", "goto", "goto3");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Mtraxx_CartahenaReloadInTavern", 10.0);
			pchar.worldmapencountersoff = "1"; // уберем враждебные энкаунтеры
		break;
		// belamour legendary edition -->
		case "mtraxx_94a":
            dialog.text = "You... you... Mad Prince! Are you setting me up?! You know what, to hell with you! You had a chance to join the Brotherhood, you had a chance to escape from the ranks of all this useless rabble. And you just cowardly missed your chance. Get out with your whining! Weakling! If I see you again - I'll set the dogs on you!";
			link.l1 = "...";
			link.l1.go = "mtraxx_95a";
		break;
		
		case "mtraxx_95a":
            DialogExit();
			QuestSetCurrentNode("Terrax", "First time");
			CloseQuestHeader("Roger_8");
			DeleteAttribute(pchar, "questTemp.Mtraxx.Corrida");
			DeleteAttribute(pchar, "questTemp.Mtraxx.InTavern");
			LocatorReloadEnterDisable("LaVega_town", "reload6", true); // закрыть на месяц
			SetFunctionTimerCondition("Mtraxx_CartahenaLateOpen", 0, 0, 30, false);
			Mtraxx_TerraxReset(8);
			DoQuestReloadToLocation("LaVega_town", "reload", "reload6", ""); // выставим за дверь
		break;
		// <-- legendary edition
		case "mtraxx_97":
            dialog.text = "Prince, at last! Look, lads - we've prepared a gift for him, and he’s off wandering who knows where! Sit down, we’re starting!\nSo, brave corsairs! The gold of Cartagena awaits us, ha-ha! And we shall claim it, I swear by thunder! But those who work hard must also rest well! That’s why tonight we shall enjoy ourselves in this fine establishment. Pour yourselves some rum, the more the better! Fill your mugs to the brim! To the winds of treasure, to the winds of fortune! We drink to the last drop!\nFor you, the finest brew from the cellars of our tavern, and the most beautiful ladies on the island, ha-ha-ha!\nAnd for you, Charles, from us — a splendid hat. Try it on, and don’t argue!\nCorsairs, sing our song! Our favourite!..";
			link.l1 = "";
			link.l1.go = "mtraxx_98";
		break;
		
		case "mtraxx_98":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			LAi_SetSitType(npchar);
			GiveItem2Character(PChar, "hat8");
			EquipCharacterByItem(PChar, "hat8");
			DoQuestCheckDelay("Mtraxx_CartahenaTavernSong", 1.0);
		break;
		
		case "mtraxx_99":
            dialog.text = "Time to show them who we are, corsairs. Leprechaun! Take your men and seize control of the city gates. We don't want them sending reinforcements to the fort! Hit them hard from behind when we charge through the fort's soldiers!";
			link.l1 = "";
			link.l1.go = "mtraxx_100";
		break;
		
		case "mtraxx_100":
            dialog.text = "Prince and Paul! You saw the military squadron with three ships, get rid of them. Stay away from the fort and don't board their vessels. We have neither the time nor the position to deal with prizes. Is everything clear?! Prince, I'm talking especially to you, I know about your addiction to heroics, you'll have an opportunity for that later!\nDon't come too close to the fort, get rid of these ships, and come back! We'll be waiting for you here. Is everything clear? Great, ha-ha-ha-ha! Charge!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CartahenaSquadronAttack");
		break;
		
		case "mtraxx_101":
            dialog.text = "So, the Spanish squadron is gone for good. Now it's time for the 'Red Dragon' to play her part. We'll turn the fort of Cartagena into a pile of rubble. Are you with me?";
			link.l1 = "Sure!";
			link.l1.go = "mtraxx_102";
		break;
		
		case "mtraxx_102":
            dialog.text = "The 'Red Dragon' is a very sturdy ship with powerful artillery, yours is no match for her. So be careful, don't play the hero and stay away from my guns!";
			link.l1 = "...";
			link.l1.go = "mtraxx_103";
		break;
		
		case "mtraxx_103":
            DialogExit();
			
			Weather.Wind.Speed = 16.0;
			pchar.wind.speed = Weather.Wind.Speed;
			fWeatherSpeed = stf(Weather.Wind.Speed);//халява первого выхода
	
			Weather.Wind.Angle = 0.0;
			pchar.wind.angle = Weather.Wind.Angle;
			fWeatherAngle = stf(Weather.Wind.Angle);//халява первого выхода
			
            npchar.dialog.currentnode = "mtraxx_board_6x";
			npchar.DeckDialogNode = "mtraxx_board_6x";
			npchar.DontDeskTalk = true;
			Group_FindOrCreateGroup("Terrax_SeaGroup2");
			Group_DelCharacter("Terrax_SeaGroup", "Jeffry");
			Group_DelCharacter("Terrax_SeaGroup", "Mtr_Vensan");
			Group_AddCharacter("Terrax_SeaGroup2", "Jeffry");
			Group_AddCharacter("Terrax_SeaGroup2", "Mtr_Vensan");
			Group_AddCharacter("Terrax_SeaGroup2", "Pelly");
			Group_SetGroupCommander("Terrax_SeaGroup2", "Jeffry");
			Group_SetTaskNone("Terrax_SeaGroup2");
			Group_LockTask("Terrax_SeaGroup2");
			sld = CharacterFromID("Cartahena Fort Commander");
			LAi_SetImmortal(sld, false);
			Ship_SetTaskAttack(SECONDARY_TASK, sti(npchar.index), sti(sld.index));
			AddQuestRecord("Roger_9", "5");
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			pchar.questTemp.Mtraxx.Cartahena.Fort = "true";
			SetFunctionExitFromLocationCondition("Mtrxtofort", pchar.location, false);
		break;
		
		case "mtraxx_104":
            dialog.text = RandSwear()+"Hell of a fight! This is it, my brave corsairs! Cartagena is ours! Resistance is down! Bold, Leprechaun! Come with me to the fort – Bernie must have already found the gold. Prince, take Cutlass and negotiate with the governor to pay us a ransom of 250,000 pesos! They have the money, so be persistent. I know you can.";
			link.l1 = "Heh! With pleasure, boss!";
			link.l1.go = "mtraxx_105";
		break;
		
		case "mtraxx_105":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "Cartahena_fort", "goto", "goto10", "", 5.0);
			sld = CharacterFromID("Jeffry");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "gate_back", "Cartahena_fort", "goto", "goto11", "", 5.0);
			sld = CharacterFromID("Lepricon");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "gate_back", "Cartahena_fort", "goto", "goto12", "", 5.0);
			sld = CharacterFromID("Pelly");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			AddQuestRecord("Roger_9", "6");
			// запрещаем драки в городе, резиденции, форте
			LAi_LocationFightDisable(&Locations[FindLocation("Cartahena_fort")], true);
			LAi_LocationFightDisable(&Locations[FindLocation("Cartahena_town")], true);
			LAi_LocationFightDisable(&Locations[FindLocation("Cartahena_townhall")], true);
			LAi_LocationDisableOfficersGen("Cartahena_townhall", true);
			pchar.quest.mtraxx_cartahena_townhall.win_condition.l1 = "locator";
			pchar.quest.mtraxx_cartahena_townhall.win_condition.l1.location = "Cartahena_town";
			pchar.quest.mtraxx_cartahena_townhall.win_condition.l1.locator_group = "reload";
			pchar.quest.mtraxx_cartahena_townhall.win_condition.l1.locator = "reload3_back";
			pchar.quest.mtraxx_cartahena_townhall.function = "Mtraxx_CartahenaToResidence";
		break;
		
		case "mtraxx_106":
            dialog.text = "How are you doing, Prince?";
			link.l1 = "Everything is splendid. I forced Cartagena's richest to pay 350,000 pesos.";
			link.l1.go = "mtraxx_107";
		break;
		
		case "mtraxx_107":
            if (sti(Pchar.money) < 350000)
			{
				dialog.text = "Ho-ho, that's my boy! But where is the money?";
				link.l1 = RandSwear()+"I will bring it in a moment!";
				link.l1.go = "mtraxx_107x";
			}
			else
			{
				dialog.text = "Ho-ho, that's my boy! You and the Cutlass can keep 50,000 each as a bonus for speed and resourcefulness. The rest will be split between all of us later.";
				link.l1 = "Here you go!";
				link.l1.go = "mtraxx_109";
			}
		break;
		
		case "mtraxx_107x":
           DialogExit();
		   npchar.dialog.currentnode = "mtraxx_108";
		break;
		
		case "mtraxx_108":
            if (sti(Pchar.money) < 350000)
			{
				dialog.text = "So? Stop messing about and bring the coins here!";
				link.l1 = "On my way!";
				link.l1.go = "mtraxx_107x";
			}
			else
			{
				dialog.text = "Great! You and the Cutlass can keep 50,000 each as a bonus for speed and resourcefulness. The rest will be split between all of us later.";
				link.l1 = "Here you go!";
				link.l1.go = "mtraxx_109";
			}
		break;
		
		case "mtraxx_109":
			AddMoneyToCharacter(pchar, -300000);
            dialog.text = "You must be concerned about our gold? It's been found - 5,000 units, and it's already being transported to our ships. The split has already been done, the men have agreed to it, and we hope that Cutlass and you will not object either.";
			link.l1 = "What is my share?";
			link.l1.go = "mtraxx_110";
		break;
		
		case "mtraxx_110":
            dialog.text = "Since the whole operation was planned by me, and the 'Red Dragon' took on the hardest task of dealing with the fort, my men and I will receive half the plunder. The other half will be shared among the captains of the other four ships according to the size of their crews. You have "+GetCrewQuantity(pchar)+" men at your disposal, your share is "+sti(pchar.questTemp.Mtraxx.Cartahena.Gold)+" units of gold and "+sti(pchar.questTemp.Mtraxx.Cartahena.Money)+" pesos.";
			link.l1 = "Well, since everyone is fine with this, then I am too!";
			link.l1.go = "mtraxx_111";
		break;
		
		case "mtraxx_111":
            dialog.text = "Splendid. Congratulations on this successful voyage, corsairs! Nothing left for us here, time to go home. All of us, myself included, receive a month's vacation. Not you, Prince, though; I have another task for you. You see, Janette, the Madame of Tortuga's brothel, had a complaint about you: she said that Charlie Prince doesn't give much attention or affection to her establishment. Therefore, I command you to sail to Tortuga, go to Janette's, and spend your bonuses there. You've earned it. Make the Madame and her girls happy. I don't want to see you before you've had your rest in Tortuga, ha-ha-ha!";
			link.l1 = "Got it, boss. This is the most pleasant assignment I've ever received. It'll be done!";
			link.l1.go = "mtraxx_112";
		break;
		
		case "mtraxx_112":
            dialog.text = "Farewell, gentlemen! Get to your ships and set sail! See you all in La Vega!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CartahenaFinal");
		break;
		
		// Addon 2016-1 Jason пиратская линейка патч 17/1
		case "mtraxx_113":
            dialog.text = "What?! Jean is now a bitch of the English, Bold and Cutlass have disappeared, Leprechaun and his men are nowhere to be found! And now you?!";
			link.l1 = "Marcus, I've made my decision. I made good coin, you made quite a fortune off me too. But I'm done. I am leaving.";
			link.l1.go = "mtraxx_114";
		break;
		
		case "mtraxx_114":
            dialog.text = "You, just like Picard, think you can make better earnings on your own? Yeah? Think you can manage without me? Ha-ha-ha! Get the hell out of here, Prince, I'm not keeping you. Soon, very soon, you'll see how wrong you were, and then you'll come back begging me to take your sorry ass back. And you know what? I won't! Ha-ha! Get out of my sight!";
			link.l1 = "...";
			link.l1.go = "mtraxx_115";
		break;
		
		case "mtraxx_115":
            DialogExit();
		    npchar.quest.mtraxx_complete = "true";
		break;
		
		// Jason НСО
		case "patria":
			dialog.text = "Ho-ho! You've come to the right place! Spit it out!";
			link.l1 = "There is a fellow who has no fear of pirates. He doesn't take them seriously. He needs to be taught a lesson in respect. Remember, don't kill him.";
			link.l1.go = "patria_1";
		break;
		
		case "patria_1":
			dialog.text = "Huh! It's no one other than the old man Charles! I bet you've got yourself into some affair again! Let's get to the details, who's the target this time and what should we teach him?";
			link.l1 = "A guest from Europe, an inspector from the French Ministry of Finance - Baron Noel Forget. He wants to establish a French Trading Company here, but a close friend of mine and I object to it. We tried to convince the Baron that trading here would be very risky because of the Dutch, the English, and especially the pirates after Levasseur was defeated, but he wouldn't listen. We need to strike fear into him, to make him feel it firsthand.";
			link.l1.go = "patria_2";
		break;
		
		case "patria_x":
			dialog.text = "Ho-ho! You've come to the right place! Spit it out!";
			link.l1 = "There is a fellow who has no fear of pirates. He doesn't take them seriously. He needs to be taught a lesson in respect. Remember, don't kill him.";
			link.l1.go = "patria_x1";
		break;
		
		case "patria_x1":
			dialog.text = "Huh! Why did you decide to hire pirates all of a sudden? Fine, I don't care as long as you pay me. Let's get to the details, who's the target this time and what should we teach him";
			link.l1 = "A guest from Europe, an inspector from the French Ministry of Finance - Baron Noel Forget. He wants to establish a French Trading Company here, but a close friend of mine and I object to it. We tried to convince the Baron that trading here would be very risky because of the Dutch, the English, and especially the pirates after Levasseur was defeated, but he wouldn't listen. We need to strike fear into him, to make him feel it on his own skin.";
			link.l1.go = "patria_2";
		break;
		
		case "patria_2":
			dialog.text = "Yes, yes... An actual baron! Should we assault his ship?";
			link.l1 = "Here's the plan: his vessel will depart for Capsterville from Port-au-Prince soon. You must intercept the Baron near Saint Kitts and take him hostage. It would be better if you didn't sink the ship or kill any men. The French are our friends, after all. Will you be able to handle that?";
			link.l1.go = "patria_3";
		break;
		
		case "patria_3":
			dialog.text = "Well, I can't promise anything. But I'll try. What ship is it?";
			link.l1 = "A brig called 'Favory'.";
			link.l1.go = "patria_4";
		break;
		
		case "patria_4":
			dialog.text = "A brig is no match for my 'Red Dragon'. We'll deal with them easily. If they surrender, I'll let everyone live.";
			link.l1 = "Perfect. Strike fear and offer them a chance to yield. Afterwards, send the Baron to the rat-infested hold. Try to find the filthiest place you can, but keep him there no longer than a day, or he could get sick and die. Then accommodate him in the cabin, find and lock him in some secluded place. Dress some of your men as captured French merchants and make them act the part. For three days straight, they should tell him all about how ruthless pirates chase them, rob them, demand ransoms, torture them... with all the required details.";
			link.l1.go = "patria_5";
		break;
		
		case "patria_5":
			dialog.text = "Ha-ha-ha! This must be the funniest job I've taken in a very long time! Well then, I will find such actors, lad. Have no doubt, after their stories your Baron will shit his pants! They will show him scars from cutlasses and heated ramrods...";
			link.l1 = "Perfect! Then you will force him to write a letter to de Poincy, asking for ransom. Thirty-five hundred thousand for such a big shot is not that much.";
			link.l1.go = "patria_6";
		break;
		
		case "patria_6":
			dialog.text = "Good. What shall we do next?";
			link.l1 = "And then you'll bring the Baron to Turks. There you will take the ransom, and you will give me the Baron. And additionally, you should tell him that all the French will answer for Tortuga and Levasseur, and not just once.";
			if (CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax")) link.l1.go = "patria_x7";
			else link.l1.go = "patria_7";
		break;
		
		case "patria_7":
			dialog.text = "Ha-ha-ha! That is one hell of a trick! We, personally, well, you know what we did to Levasseur, and now... ha-ha-ha!.. Fine, lad. It will be done! So you say that the ship will arrive soon?";
			link.l1 = "Soon. We need to be on the lookout.";
			link.l1.go = "patria_8";
		break;
		
		case "patria_x7":
			dialog.text = "Ha-ha-ha! That is one hell of a trick! How much should I charge you for this farce? Fine, a hundred thousand will seal the deal. Hand me the money.";
			if (sti(pchar.money) >= 100000) 
			{
				link.l1 = "Take it.";
				link.l1.go = "patria_x8";
			}
			else
			{
				link.l1 = "Alright, I'll bring it.";
				link.l1.go = "patria_xwait";
			}
		break;
		
		case "patria_xwait":
			DialogExit();
			pchar.questTemp.Patria.Condotier.NeedMoney = "true";
		break;
		
		case "patria_x8":
			AddMoneyToCharacter(pchar, -100000);
			dialog.text = "Perfect! Did you say the ship will arrive soon?";
			link.l1 = "Soon. We need to be on the lookout.";
			link.l1.go = "patria_8";
		break;
		
		case "patria_8":
			dialog.text = "Don't worry about it, I won't let you down. I'll handle this personally. When you hear a rumour that the Baron has been captured, come to me.";
			link.l1 = "Good. My thanks, Marcus.";
			link.l1.go = "patria_9";
		break;
		
		case "patria_9":
			DialogExit();
			AddQuestRecord("Patria", "71");
			pchar.questTemp.Patria = "epizode_12_wait";
			pchar.questTemp.Patria.Condotier.Success = "true";
			if (CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax")) LocatorReloadEnterDisable("Pirates_town", "reload3_back", true);
			else LocatorReloadEnterDisable("Lavega_town", "reload6", true);
		break;
		
		case "patria_10":
			dialog.text = "Of course, lad. As agreed. Frightening tales of ruthless pirates, slaughtering innocent French merchants, the sound of the whip, moans and screams. A brazier with coals and scorched handcuffs. Just as it should be.";
			link.l1 = "Whoa, whoa! Hold your horses! I need him alive";
			link.l1.go = "patria_11";
		break;
		
		case "patria_11":
			dialog.text = "Don't worry, he'll live. He wrote this letter with a shaky hand. Here it is.";
			link.l1 = "What is written there? He's begging Poincy to get him out of this?";
			link.l1.go = "patria_12";
		break;
		
		case "patria_12":
			dialog.text = "That's right, lad! He's begging, ha!";
			link.l1 = "Throw this letter away, or better yet - burn it. We'll meet on Turks in a week. It must look as if we need time to collect the ransom.";
			link.l1.go = "patria_13";
		break;
		
		case "patria_13":
			dialog.text = "Got it. In a week's time, northern gulf on Turks. Don't forget to take the money: this must look good. After all this, come to me, we'll discuss it.";
			link.l1 = "Of course, see you later, Marcus!";
			link.l1.go = "patria_14";
		break;
		
		case "patria_14":
			DialogExit();
			AddQuestRecord("Patria", "73");
			pchar.questTemp.Patria = "epizode_12_terks";
			SetFunctionTimerCondition("Patria_CondotierTerks", 0, 0, 7, false);
			SetFunctionTimerCondition("Patria_CondotierTerksOver", 0, 0, 14, false);
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
		break;
		
		case "patria_15":
			pchar.quest.Patria_CondotierTerksOver.over = "yes"; //снять таймер
			dialog.text = "Hey, frog-eater! Halt!";
			link.l1 = "I'm not moving.";
			link.l1.go = "patria_16";
		break;
		
		case "patria_16":
			dialog.text = "Here's your Baron. A bit worn, heh, but in one piece. Still recognizable? Ha-ha-ha!";
			link.l1 = "Yes... somewhat.";
			link.l1.go = "patria_17";
		break;
		
		case "patria_17":
			dialog.text = "Perfect. Now hand over the money or he's done! And don't try to trick us, we've got you in our sights!";
			if (sti(pchar.money) >= 350000)
			{
				link.l1 = "Here, take it.";
				link.l1.go = "patria_18";
			}
			else
			{
				link.l1 = "Damn! I left it on the ship...";
				link.l1.go = "patria_22";
			}
		break;
		
		case "patria_18":
			AddMoneyToCharacter(pchar, -350000);
			dialog.text = "Ha-ha-ha! You're a clever kid, frenchie. Take your 'eminence'. And tell Poincy he should prepare the money: you'll have to pay for what you did to Levasseur and Tortuga. And your merchants will pay us with their goods and ships. Ha-ha-ha! Don't forget to bring us more barons to the archipelago, they bring us plenty of profit! Ha-ha-ha!";
			link.l1 = "Please, go to my boat, Baron.";
			link.l1.go = "patria_19";
		break;
		
		case "patria_19":
			sld = CharacterFromID("Noel");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
			dialog.text = "And don't even think about chasing us, captain. You know who I am. I hold more frog-eaters captive, and if I don't return home on time, they will all be executed. Got it?";
			link.l1 = "The time will come, and we will deal with you, cursed blasphemers!";
			link.l1.go = "patria_20";
		break;
		
		case "patria_20":
			dialog.text = "Ha-ha-ha-ha! Of course you will!";
			link.l1 = "...";
			link.l1.go = "patria_21";
		break;
		
		case "patria_21":
			DialogExit();
			LAi_SetPlayerType(pchar);
			AddQuestRecord("Patria", "74");
			LAi_SetActorType(npchar);
			if (CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax"))
			{
				LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierDodsonNorm", 10.0);
				Island_SetReloadEnableGlobal("Bermudes", false); // закрыть остров до отвоза барона
			}
			else LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierTerraxNorm", 10.0);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 8.0);
			pchar.questTemp.Patria = "epizode_12_baronalive";
			pchar.questTemp.Patria.DodsonAgain = "true";
			sld = CharacterFromID("Noel");
			AddPassenger(pchar, sld, false);//добавить пассажира
			SetCharacterRemovable(sld, false);
			pchar.quest.Patria_Condotier_toPuancie.win_condition.l1 = "location";
			pchar.quest.Patria_Condotier_toPuancie.win_condition.l1.location = "Charles_town";
			pchar.quest.Patria_Condotier_toPuancie.function = "Patria_CondotierEnCapstervil";
			// Теркс в норму
			LAi_LocationFightDisable(&Locations[FindLocation("Shore56")], false);
			LAi_LocationDisableOfficersGen("Shore56", false);
		break;
		
		case "patria_22":
			dialog.text = "Are you kidding me?! Is this some kind of trick?!";
			link.l1 = "One moment, I'll bring it...";
			link.l1.go = "patria_23";
		break;
		
		case "patria_23":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Shot", "Patria_CondotierBaronDie", 1.0);
		break;
		
		case "patria_24":
			dialog.text = "";
			link.l1 = "Argh, Marcus, what has your dullard done!";
			if (CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax")) link.l1.go = "patria_25";
			else link.l1.go = "patria_x25";
		break;
		
		case "patria_25":
			dialog.text = "Charles, what were you doing? Where's the money? I didn't tell my boys that this wasn't real... and so this idiot decided that you wanted to trick us...";
			link.l1 = "It's a disaster! The Baron is dead... What will de Poincy do now?";
			link.l1.go = "patria_26";
		break;
		
		case "patria_x25":
			dialog.text = "Charles, what were you doing? Where's the money? I didn't tell my boys that this wasn't real... and so this idiot decided you were trying to trick them...";
			link.l1 = "It's a disaster! The Baron is dead... What will de Poincy do now?";
			link.l1.go = "patria_x26";
		break;
		
		case "patria_x26":
			dialog.text = "Well lad, that's your fault, I hope you understand that. Perhaps it's for the best, a dead man can't cause any harm.";
			link.l1 = "What a fool I am! I messed everything up. Fine, I'll go to Poincy... Forgive me for being such a fool, Marcus, see you.";
			link.l1.go = "patria_28";
		break;
		
		case "patria_26":
			dialog.text = "Well lad, it's your fault, I hope you understand that. Perhaps it's for the best.";
			link.l1 = "What a fool I am! I messed everything up. Fine, I'll go to Poincy... Forgive me for being such a fool, Marcus, see you.";
			link.l1.go = "patria_27";
		break;
		
		case "patria_27":
			dialog.text = "You need to rest, you're losing your touch. Come to me sometime, I'll get you some rum and fine maidens.";
			link.l1 = "Thank you, I'll pay you a visit when I can.";
			link.l1.go = "patria_28";
		break;
		
		case "patria_28":
			DialogExit();
			AddQuestRecord("Patria", "75");
			LAi_SetActorType(npchar);
			if (CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax")) LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierDodsonNorm", 10.0);
			else LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierTerraxNorm", 10.0);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 8.0);
			pchar.questTemp.Patria = "epizode_12_barondie";
			// Теркс в норму
			LAi_LocationFightDisable(&Locations[FindLocation("Shore56")], false);
			LAi_LocationDisableOfficersGen("Shore56", false);
		break;
		
		case "patria_29":
			dialog.text = "You're welcome, lad. For me, this was the most fun I've had this year! We laughed so much, me and my lads! So I'd like to thank you for this. Here's your money.";
			link.l1 = "You should keep a part of it for your performance.";
			link.l1.go = "patria_30";
		break;
		
		case "patria_x29":
			AddMoneyToCharacter(pchar, 350000);
			dialog.text = "Take your money, 'plotter'. Ha-ha! That was fun.";
			link.l1 = "Thank you for your help, Marcus. Good luck!";
			link.l1.go = "patria_32";
		break;
		
		case "patria_30":
			AddMoneyToCharacter(pchar, 350000);
			dialog.text = "Forget it. I did this for the sake of our friendship. The Brethren of the Coast owes you much more, yet you didn't ask for a single doubloon.";
			link.l1 = "Still, take at least fifty thousand for your services and compensation. Thank you, Marcus!";
			link.l1.go = "patria_31";
		break;
		
		case "patria_31":
			AddMoneyToCharacter(pchar, -50000);
			dialog.text = "You're welcome. Charles, pay me a visit whenever you have some time!";
			link.l1 = "With pleasure!";
			link.l1.go = "patria_32";
		break;
		
		case "patria_32":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Patria.DodsonAgain");
		break;
		
		case "patria_33":
			dialog.text = "You're a week late! I didn't tell my boys this wasn't real... They refused to wait any longer and decided to finish off your Baron!";
			link.l1 = "What a fool I am! I’ve messed everything up! What am I going to tell Poincy?";
			link.l1.go = "patria_34";
		break;
		
		case "patria_x33":
			dialog.text = "You're a week late! I didn't tell my boys this wasn't real... They refused to wait any longer and decided to finish off your Baron!";
			link.l1 = "What a fool I am! I've messed everything up! What am I going to tell Poincy?";
			link.l1.go = "patria_x34";
		break;
		
		case "patria_34":
			dialog.text = "Well, lad, it's your fault, I hope you understand that. Perhaps it will be all the better for you.";
			link.l1 = "Fine, I'll go to Poincy... Forgive me for being a fool, Marcus, see you...";
			link.l1.go = "patria_35";
		break;
		
		case "patria_x34":
			dialog.text = "You've gotten yourself into this mess, it's your own fault.";
			link.l1 = "See you later, I suppose...";
			link.l1.go = "patria_36";
		break;
		
		case "patria_35":
			dialog.text = "You need to rest, you're losing your touch. Come to me sometime, I'll get you some rum and fine maidens.";
			link.l1 = "Thank you, I'll pay you a visit when I can.";
			link.l1.go = "patria_36";
		break;
		
		case "patria_36":
			DialogExit();
			AddQuestRecord("Patria", "75");
			pchar.questTemp.Patria = "epizode_12_barondie";
			DeleteAttribute(pchar, "questTemp.Patria.DodsonFail");
		break;
		
		// Rebbebion, квест "Путеводная звезда"
		case "PZ_1":
			DelLandQuestMark(npchar);
			
			if (pchar.questTemp.Mtraxx == "full_complete")
			{
				dialog.text = "Been a while, Prince.";
				link.l1 = "I am not sure this name has brought me anything but bad luck, Marcus.";
				link.l1.go = "PZ_Prince1";
			}
			else
			{
				dialog.text = "De Maure! What brings you here?";
				link.l1 = "Ah, Marcus. I wanted to ask you something.";
				link.l1.go = "PZ_DeMaure1";
			}
		break;
		
		case "PZ_Prince1":
			dialog.text = "I see it's quite the opposite. What brings you here?";
			link.l1 = "Have you heard about the new brothel in Tortuga?";
			link.l1.go = "PZ_2";
		break;
		
		case "PZ_DeMaure1":
			dialog.text = "Then by all means, ask. You know that I don't like formalities, so cut to the chase.";
			link.l1 = "Have you heard about the new brothel in Tortuga?";
			link.l1.go = "PZ_2";
		break;
		
		case "PZ_2":
			dialog.text = "Are you drunk? What kind of question is that? Don't waste my time if that's what you really wanted to talk about.";
			link.l1 = "I guess you haven't heard? A new brothel recently opened there—a very expensive one, where only the most beautiful, healthy, and well-dressed girls work.";
			link.l1.go = "PZ_3";
		break;
		
		case "PZ_3":
			dialog.text = "Oh, that! Of course I've heard – who hasn't?";
			link.l1 = "Well, I only learned about it the other day.";
			link.l1.go = "PZ_4";
		break;
		
		case "PZ_4":
			dialog.text = "Ha-ha-ha-ha, you scoundrel, I'll be damned! But still, why are you discussing it with me? Why not try Hawks first? Heh heh. Although... have you already had some fun there?";
			if (CheckAttribute(pchar, "questTemp.PZ.EliteWhoreFucked"))
			{
				link.l1 = "I have. They only accept doubloons, by the way.";
				link.l1.go = "PZ_Fucked1";
			}
			else
			{
				link.l1 = "I visited the place, but I didn't partake in the services. However...";
				link.l1.go = "PZ_NoFucked1";
			}
		break;
		
		case "PZ_Fucked1":
			dialog.text = "So you've come to show off! Ha, what a rascal.";
			link.l1 = "Actually, no. I really wanted to ask you something, Marcus.";
			link.l1.go = "PZ_5";
		break;
		
		case "PZ_NoFucked1":
			dialog.text = "You didn't?! You're a fool, De Maure. If I were you...";
			link.l1 = "You'd have started a proper debauch, I know. But that's not exactly what I wanted to discuss with you.";
			link.l1.go = "PZ_5";
		break;
		
		case "PZ_5":
			dialog.text = "What is it? Come on, don't keep me in suspense.";
			link.l1 = "I'm looking for the owner of that place. I was told she wanted to meet you and offer you an investment opportunity in her trade. You can't mistake her - she's Chinese.";
			link.l1.go = "PZ_6";
		break;
		
		case "PZ_6":
			dialog.text = "Ho ho. No, I haven't had the pleasure of meeting any Chinese women lately. But I wouldn't mind meeting her and investing in her business. After all, you can't just stroll into Levasseur's territory, and as a subject of your king, he'd be forced to fire his coastal vessels at my 'Dragon' the moment he spotted her.";
			link.l1 = "Seems like she's considering Port-au-Prince first...";
			link.l1.go = "PZ_7";
		break;
		
		case "PZ_7":
			dialog.text = "You think so? That's a mistake. Even if de Mussac has more money than I do, which I doubt, he can't afford to allocate any of the city's budget to a brothel, no matter how much gold it brings in.";
			link.l1 = "Good point. She clearly hasn't thought this ambition of hers through.";
			link.l1.go = "PZ_8";
		break;
		
		case "PZ_8":
			dialog.text = "You know, I always wondered how other brothels stay afloat. It's not a woman's ability to think, and certainly not to rule - mark my words.";
			link.l1 = "Well, you're wrong about that. Thanks for your time, Marcus! If I meet her first, I'll let her know you'd be glad to see her.";
			link.l1.go = "Exit";
			
			AddQuestRecord("PZ", "32");
			
			pchar.quest.PZ_SetHeavyFrigate.win_condition.l1 = "location";
			pchar.quest.PZ_SetHeavyFrigate.win_condition.l1.location = "Hispaniola1";
			pchar.quest.PZ_SetHeavyFrigate.win_condition = "PZ_SetHeavyFrigate";
			DelMapQuestMarkCity("LaVega");
			AddMapQuestMarkCity("PortPax", false);
			LocatorReloadEnterDisable("LaVega_ExitTown", "reload1_back", true);
			LocatorReloadEnterDisable("PortPax_town", "gate_back", true);
		break;
	}
}
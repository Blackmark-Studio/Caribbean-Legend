// boal 25/04/04 общий диалог солдат
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;	

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	int DeceptionChance  = 0;
	int DeceptionPenalty  = 0;
	if(CheckAttribute(pchar,"StealtDeceptionPenalty")) DeceptionPenalty = sti(pchar.StealtDeceptionPenalty);
	
	DeceptionChance = sti(GetSummonSkillFromName(pchar, SKILL_SNEAK)*100/110);
	if(DeceptionChance - DeceptionPenalty > 50) DeceptionChance -= DeceptionPenalty;
	if (false) 
	{
		DeceptionChance = sti(GetSummonSkillFromName(pchar, SKILL_SNEAK)*100/310);
		if(DeceptionChance - DeceptionPenalty > 50) DeceptionChance -= DeceptionPenalty;
	}
	if(sti(pchar.reputation.fame) < 41 && CheckCharacterPerk(pchar, "Trustworthy"))
	{
		DeceptionChance = 100;
		if(DeceptionChance - DeceptionPenalty > 50) DeceptionChance -= DeceptionPenalty;
	}
	if(DeceptionChance > 90) DeceptionChance = 90;
	// belamour legendary edition в квестах не используется, да, и лишний раз игроков не нужно заставлять по кейсам бегать. Квесты пишите в коммоне
    /* // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Soldier\" + NPChar.City + "_Soldier.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <-- */
    int iTest, iTemp;
	string sTemp;
    iTest = FindColony(NPChar.City); // город
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			sTemp = npchar.location;
			if (findsubstr(sTemp, "_townhall" , 0) != -1) AddDialogExitQuest("MainHeroFightModeOff");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "First time":			
            NextDiag.TempNode = "First time";
			if (false)
			{
				// заглушка на пирата
				if (false)
				{
    				dialog.text = RandPhraseSimple("Pirates in the town?! I can't believe it... Seize "+GetSexPhrase("him","her")+"!!","That's a pirate! Seize "+GetSexPhrase("him","her")+"!!!");
					link.l1 = RandPhraseSimple("I am a pirate, so what?","Heh, you can try...");
					link.l1.go = "fight"; 
					break;
				}
				else
				{
					if (DeceptionChance > (10+rand(150)+rand(150)))
					{
						dialog.text = RandPhraseSimple("Who are you and what are you doing here?","Stop right there! Who are you, and by what right are you trying to enter the town?");
						link.l2 = "I dropped anchor near "+XI_ConvertString(GetIslandByCityName(npchar.city)+"Gen")+" under the flag of "+NationNameGenitive(sti(npchar.nation))+". What don't you understand? (Probability of deception "+DeceptionChance+"%%)";
						link.l1.go = "NotPegYou";
					}
					else
					{
						dialog.text = RandPhraseSimple("A spy! Surrender your weapon and follow me!","An enemy agent! Seize "+GetSexPhrase("him","her")+"!");
						link.l1 = RandPhraseSimple("Shut up, sissy!","Fuck you!");
						link.l1.go = "fight"; 
					}
				}
			}
			else
			{
				// eddy. проверяем, не казачок ли. -->
				if (false)
				{
					// грамота Винсенто
					if(CheckAttribute(pchar, "questTemp.Guardoftruth") && CheckCharacterItem(pchar, "VerifyPaper") && npchar.city == "santiago")
					{
						dialog.text = RandPhraseSimple("Who are you and what are you doing here?","Stop right there! Who are you, and by what right do you seek to enter the town?");
						link.l1 = "Look at this paper, soldier. I am here with permission from the Inquisitor, Father Vincenzo.";
						link.l1.go = "vincento"; 
						break;
					}
					if(CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && CheckCharacterItem(pchar, "VerifyPaper") && npchar.city == "portspein")
					{
						dialog.text = RandPhraseSimple("Who are you and what are you doing here?","Stop right there! Who are you, and by what right are you trying to enter the town?");
						link.l1 = "Look at this paper, soldier. I am here with permission from the Inquisitor, Father Vincento.";
						link.l1.go = "vincento"; 
						break;
					}
					if (PChar.location == "Maracaibo_Plantation")
					{
						dialog.text = LinkRandPhrase("Behave yourself and don't bother the slaves.","Come on, move along!","Ah, it's you. Go ahead, we've already been informed about you.");
						link.l1 = "...";
						link.l1.go = "exit";
						break;
					}
					dialog.text = RandPhraseSimple("Who are you and what are you doing here?","Stop right there! Who are you, and by what right are you trying to enter the town?");
					//==> по лицензии
					if (CheckNationLicence(HOLLAND))
					{
						link.l1 = "Officer, I have "+GetRusNameNationLicence(HOLLAND)+", so I am here on legal grounds. Here, please take a look...";
						link.l1.go = "LicenceOk";
						if (findsubstr(pchar.location.from_sea, "_town" , 0) != -1) //если причалил в городе
						{
							link.l2 = "Don't you see the flag of "+NationNameGenitive(sti(pchar.nation))+"on the mast of my ship?! (Probability of deception "+DeceptionChance+"%%)";
						}
						else //если причалил не в городе
						{
							link.l2 = "I dropped anchor near "+XI_ConvertString(GetIslandByCityName(npchar.city)+"Gen")+" under the flag of "+NationNameGenitive(sti(pchar.nation))+". What don't you understand? (Probability of deception "+DeceptionChance+"%%)";
						}
						if (DeceptionChance < (10+rand(50)+rand(50)))
						{
							link.l2.go = "PegYou";
						}
						else
						{
							link.l2.go = "NotPegYou";
						}
					}
					else
					{
						//==> по флагу
						// заглушка на пирата
						if (false)
						{
    						dialog.text = RandPhraseSimple("Pirates in the town?! I can't believe it... Seize him!","That's a pirate! Seize him!");
							link.l1 = RandPhraseSimple("Yes, I am a pirate - now what?","Heh, catch me if you can...");
							link.l1.go = "fight"; 
							break;
						}
						if (findsubstr(pchar.location.from_sea, "_town" , 0) != -1) //если причалил в городе
						{
							link.l1 = "Don't you see the flag of "+NationNameGenitive(sti(pchar.nation))+" on my ship?! (Probability of deception "+DeceptionChance+"%%)";
						}
						else //если причалил не в городе
						{
							link.l1 = "I dropped anchor near "+XI_ConvertString(GetIslandByCityName(npchar.city)+"Gen")+" under the flag "+NationNameGenitive(sti(pchar.nation))+". What don't you understand? (Probability of deception "+DeceptionChance+"%%)";
						}
						if (DeceptionChance < (10+rand(50)+rand(50)))
						{
							link.l1.go = "PegYou";
						}
						else
						{
							link.l1.go = "NotPegYou";
						}
					}
				}
				// <-- eddy. проверяем, не казачок ли.
				else
				{
					if (sti(NPChar.nation) == PIRATE)
					{
						if (sti(rColony.HeroOwn) == true) // наш горожанин
						{
			         		switch (rand(10))
							{
								case 0:
									dialog.text = "Oh, captain, we've had such a wonderful time with you at sea! So many ships we've sunk together under your command! And here...";
									link.l1 = "And here, my friend, you can feast your eyes on charming ladies you won't see at sea.";
									link.l1.go = "exit";
								break;

								case 1:
									dialog.text = "Captain, what have we done to deserve this?! We aren't land rats, are we?";
									link.l1 = "Quiet, sailor! Your post is very important and an honourable one, so quit your whining.";
									link.l1.go = "exit";
								break;

								case 2:
									dialog.text = "What's happening at sea, captain? Will we ever see it again?";
									link.l1 = "But of course, sailor! Once you are relieved of duty, you can head to the pier and enjoy the sea as much as you like.";
									link.l1.go = "exit";
								break;

								case 3:
									dialog.text = "I want to complain, captain: every one of us misses the sea. We're all completely fed up with this land duty!";
									link.l1 = "I am tired of this whining! You've got enough rum here too! Serve where the captain assigned you, or else someone will be hanged as an example to the others.";
									link.l1.go = "exit";
								break;

								case 4:
									dialog.text = "I'll tell you in confidence, captain, the new governor is a bribe-taker and embezzler. But that's really none of my business...";
									link.l1 = "Exactly, corsair. Your business is to stand at your post and keep order. And hanging the governor from the yardarm is my business. Good job!";
									link.l1.go = "exit";
								break;

								case 5:
									dialog.text = "Thank you for not forgetting about us, captain! We'd follow you through fire and water!";
									link.l1 = "I know your type, crooks! All you really care about is gold. There's a party at the tavern tonight, drinks are on me. Don't forget to show up.";
									link.l1.go = "exit";
								break;

								case 6:
									dialog.text = "Heh, captain! Just think about it, can a corsair really be a keeper of order?! It's been so long since we were last on real business!";
									link.l1 = "No time to relax, corsair! Enemy armadas are scouring the waters near our islands, and we must be ready for a bloodbath at any moment.";
									link.l1.go = "exit";
								break;

								case 7:
									dialog.text = "Captain, I heard that the Crown has sent another squadron our way?";
									link.l1 = "Of course, corsair. While we live, there will be no peace for us. And even in Hell, we will be fighting devils!";
									link.l1.go = "exit";
								break;

								case 8:
									dialog.text = "Yo-ho-ho! Damn, that was some really strong booze yesterday, captain! It's a pity you weren't there.";
									link.l1 = "Not a big deal, I'll make up for it. And I don't envy you, guys.";
									link.l1.go = "exit";
								break;

								case 9:
									dialog.text = "I'll tell you in confidence, captain, since you've always treated us well. We had a good time with a really lovely girl yesterday...";
									link.l1 = "Heh, corsair, a noose is exactly what you need!";
									link.l1.go = "exit";
								break;

								case 10:
									dialog.text = "Cap! Please, relieve me of this cursed duty! I simply can't play the part of a keeper of order anymore.";
									link.l1 = "Night watch on a ship is not easy either. Friend, duty is duty, wherever and whatever it may be.";
									link.l1.go = "exit";
								break;
							}
							// belamour legendary edition в квестах не используется, да, и лишний раз игроков не нужно заставлять по кейсам бегать. Квесты пишите в коммоне
							/* link.l2 = RandPhraseSimple("There’s something important!","I have business with you.");
							link.l2.go = "quests";//(перессылка в файл города) */
							break;
						}
						else
						{ // пираты, не наши
							if (sti(pchar.GenQuest.Piratekill) > 20)
							{
								dialog.text = RandPhraseSimple("Alert! An armed, deranged lunatic is here!","To arms, to arms! Some crazy bastard is here!");
								link.l1 = RandPhraseSimple("Huh? What?","Uh, why are you doing this?");
								link.l1.go = "pirate_fight";
							}
							else
							{
							    /* dialog.text = LinkRandPhrase(RandPhraseSimple("Do you have business with me, Captain?","I'm just here on business, if you need anything - ask, don't hesitate."),RandPhraseSimple("Captain, I'm very busy, so look for someone else to talk to.","Is something wrong, Captain? If you have no questions, may I be excused?"),"Make way, Captain, I'm in a hurry.");
							link.l1 = LinkRandPhrase("Sorry, mate, I "+GetSexPhrase("обознался","обозналась")+" ","Alright, get on with your business.","No, nothing.");
							link.l1.go = "exit";
							link.l2 = LinkRandPhrase(RandPhraseSimple("I have a couple of questions for you.","I have business with you."),RandPhraseSimple("I see you're in a hurry. Just one question and you'll be free.","Я "+GetSexPhrase("хотел","хотела")+" ask something."),"Your business can wait. I have something to ask you "+GetSexPhrase("хотел","хотела")+".");
							    link.l2.go = "quests";//(перессылка в файл города) */
								
								//Экку Korsar - что-то они больно вежливые для пиратов были...
								dialog.text = RandPhraseSimple("What do you want? Move along.","Stop blocking the road, back off.");
					            link.l1 = RandPhraseSimple("You know? Don't shout!","Reduce your ardour. I won't cool it down quickly!");
					            link.l1.go = "exit";
						    	/* link.l2 = LinkRandPhrase(RandPhraseSimple("I have a couple of questions for you.","I have business with you."),RandPhraseSimple("I see you're in a hurry. Just one question and you'll be free.","Я "+GetSexPhrase("хотел","хотела")+" ask something."),"Your business can wait. I have something to ask you "+GetSexPhrase("хотел","хотела")+".");
							link.l2.go = "quests";//(перессылка в файл города) */
							}
							break;
						}
					}
					else
					{ //если негодяй, имеющий НЗГ к дружественной или нейтральной нации
						if (ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -15)
						{
							dialog.text = RandPhraseSimple("Just look  "+GetSexPhrase("at that scoundrel! He dared to show his face","at that scoundrel! She dared to show her face")+" in "+XI_ConvertString("Colony"+npchar.city)+". Seize "+GetSexPhrase("him","her")+"!!!","Ha, I recognise you, "+GetSexPhrase("scoundrel","rascal")+"! Seize "+GetSexPhrase("him","her")+"!!!");
							link.l1 = RandPhraseSimple("Argh!..","Well, you've asked for it...");
							link.l1.go = "fight";
							break;						
						}
					}

					// --> девица в джунглях
					if(rand(2) == 1 && CheckAttribute(pchar,"GenQuest.EncGirl") && CheckAttribute(pchar,"GenQuest.EncGirl.MeetSoldiers"))
					{
						if(sti(pchar.GenQuest.EncGirl.MeetSoldiers) == 1)	
						{
							dialog.text = "Oh, look who's here! Lady "+pchar.GenQuest.EncGirl.name+" herself has honoured us with her presence! I wonder how you dared? We've been looking for you! Please proceed to the dungeon - your cell is ready and waiting for you. ";
							link.l1 = "What utter nonsense are you talking!? My crew and I "+GetSexPhrase("cavalier","companion")+" were taking a stroll in the jungle, picking flowers. Leave me alone! Where are the manners of these martinets?! As soon as they see an attractive girl, they start pestering her! "+GetSexPhrase("My dear, please tell those blockheads to get lost and leave an honest woman alone!","Darling, please tell those blockheads...")+"!";
							link.l1.go = "GirlEnc_1";
						}
						if(sti(pchar.GenQuest.EncGirl.MeetSoldiers) == 2)	
						{
							dialog.text = "Oh, there you are, beautiful! Your dad got the entire garrison out to find you and bring you back home.";
							link.l1 = "Get lost! I know where I am going and I do not need your help! Captain, tell them to take their hands off me.";
							link.l1.go = "GirlEnc_2";						
						}
						DeleteAttribute(pchar,"GenQuest.EncGirl.MeetSoldiers");
					}
					// <-- девица в джунглях

					// --> belamour ночной приключенец
					if(CheckAttribute(pchar,"GenQuest.NightAdventureSolNum") && npchar.index == pchar.GenQuest.NightAdventureSolNum)
					{
						dialog.text = "A soldier's life is scheduled - standing guard, patrolling ... What do you want, "+GetAddress_Form(NPChar)+"?";
						link.l1 = "Listen, was it you who got into a fight with that drunkard here recently? Well, apparently, yes, it was you...";
						link.l1.go = "NightAdventure_CitizenHomieSolder";
						break;
					}
					// <-- ночной приключенец
					
					//belamour legendary edition диалоги, если герой имеет звания и заслуги перед отечеством -->
					
					// Шарль де Мор генерал-губернатор французских колоний
					if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
					{
						switch(rand(2))
						{
							case 0: 
							dialog.text = "Your Excellency, Governor General! How may I serve?";
							link.l1 = "I don't need anything, thanks.";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "This is a great honour for me, Mr. Governor General! How can I help you?";
								link.l1 = "Carry out your service conscientiously - I require nothing more from you.";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "Good to see you, Your Excellency! What can a humble soldier do for the governor-general of our colonies?";
								link.l1 = "Personally, I don't need anything from you. Keep serving.";
								link.l1.go = "exit";
							break;
						}
						break;
					}
					// Вице-адмирал на службе нации узнается без мундира
					if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
					{
						switch(rand(2))
						{
							case 0: 
							dialog.text = "Vice Admiral, Your Excellency! Allow me to report: during my watch...";
							link.l1 = "Calm down, soldier, I don't need your report. Report to your officer.";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "Glad to see you, Vice Admiral! Can I help you with something?";
								link.l1 = "No, I was just checking how attentive you are. I'm glad you recognised me.";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "Vice Admiral, this is an honour for me! What can I do for you?";
								link.l1 = "Serve "+NationNameGenitive(sti(npchar.nation))+", soldier! It's the best thing you can do.";
								link.l1.go = "exit";
							break;
						}
						break;
					}
					// Офицер с патентом
					if(IsOfficerFullEquip() && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
					{
						switch(rand(2))
						{
							case 0: 
							dialog.text = "Greetings, captain! If you have any instructions for me, then I beg your pardon: although I am in the service of "+NationNameGenitive(sti(npchar.nation))+", I answer only to the commandant and the governor."; 
							link.l1 = "I have my officers and crew answer to my command. Do your duty, soldier.";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "Captain, may I serve aboard your ship? The same service for "+NationNameGenitive(sti(npchar.nation))+", but I prefer the sea."; 
								link.l1 = "You are needed where you have been assigned, so carry out your service with honour. Close your eyes for a second, and they will take it to the sea.";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "Oh, you're in luck: you're the captain of a ship in the service of "+NationNameGenitive(sti(npchar.nation))+"... And I'm stuck here all day."; 
								link.l1 = "Do you think I just arrived in the Caribbean and became a captain a week later? It's all years of hard work...";
								link.l1.go = "exit";
							break;
						}
						break;
					}
					// <-- legendary edition
					switch (rand(10))
					{
						case 0: ////////////////////////////////////////
							dialog.text = "Can't you see? I'm on duty. Stop bothering me.";
							link.l1 = "Alright, alright...";
							link.l1.go = "exit";
						break;

						case 1:
							dialog.text = "Are you going to tell me about some suspicious activity?";
							link.l1 = "No, none at all, and I am a captain, by the way. I see you're not listening anymore? Bye.";
							link.l1.go = "exit";
						break;

						case 2: ///////////////////////////////////////////
							dialog.text = "This is a military facility, so don't make too much noise here.";
							link.l1 = "Alright, I'll keep that in mind.";
							link.l1.go = "exit";
						break;

						case 3:
							dialog.text = "Such fair weather, and I'm stuck standing here. In town, at least there are girls, but what do we have here? Only rats about.";
							link.l1 = ""+GetSexPhrase("I sympathise, but there's nothing I can do to help - it's your duty after all.","Hey! What's wrong with me? Am I not a woman?")+"";
							link.l1.go = "exit";
						break;

						case 4: ///////////////////////////////////////////
							dialog.text = "If you enjoy talking, find someone else. I must keep order here, and I have no time for idle chatter.";
							link.l1 = "Oh, no, I am just checking if you're still alive. You were standing just like a statue.";
							link.l1.go = "exit";
						break;

						case 5: ////////////////////////////////////////////
							dialog.text = "You probably think that garrison duty is a cakewalk? Absolutely not! It's hard and important work. I remember once... ";
							link.l1 = "You will tell me that story some other time. I am in a bit of a hurry now.";
							link.l1.go = "exit";
						break;

						case 6: ////////////////////////////////////////////
							dialog.text = "Careful here, you're in a fort! Be as quiet as a mouse!";
							link.l1 = "As you say, soldier.";
							link.l1.go = "exit";
						break;

						case 7:
							dialog.text = "Hey! Do you have any water, by any chance? I'm dying of thirst.";
							link.l1 = "No, friend, be patient...";
							link.l1.go = "exit";
						break;

						case 8://///////////////////////////////////////////
							dialog.text = "How dull is garrison life, only rednecks like you around! Now, the town garrison surely has better times...";
							link.l1 = "And you call this 'being on duty'? At this rate, you'll surely let a spy slip past you!";
							link.l1.go = "exit";
						break;

						case 9://///////////////////////////////////////////
							dialog.text = ""+GetSexPhrase("You look like a strong fellow, don't you? Would you like to sign up for duty at the fort's garrison? We have spacious barracks, two meals a day, and free booze.","Oh, young lady, you have no idea how pleasant it is to meet such a lovely damsel in this back of beyond!")+"";
							link.l1 = ""+GetSexPhrase("That's certainly tempting, but I still must refuse. All that barrack drill is just not for me.","Thank you for the compliment, soldier.")+".";
							link.l1.go = "exit";
						break;

						case 10:
							dialog.text = "This goddamn heat... I'd gladly give up half my life to go back to Europe.";
							link.l1 = "Yes, I can see that your health is not suited to the local climate.";
							link.l1.go = "exit";
						break;

					}
					// belamour legendary edition в квестах не используется, да, и лишний раз игроков не нужно заставлять по кейсам бегать. Квесты пишите в коммоне
					/* link.l3 = "Wait a moment. I wanted to ask you something "+GetSexPhrase("хотел","хотела")+"...";
					link.l3.go = "quests";//(перессылка в файл города) */				
				}
			}
			//--> Дикая Роза
			if (CheckAttribute(pchar, "questTemp.WildRose_DialogeWithSoldierOnPier") && npchar.location.group == "soldiers" && npchar.city == "Bridgetown")
			{
				dialog.text = "Welcome to Bridgetown, "+GetAddress_Form(NPChar)+"...";
				link.l1 = "I thought my face was known not only in the French colonies... My name is "+GetFullName(pchar)+".";
				link.l1.go = "WildRose_Soldier_1";
				DeleteAttribute(pchar, "questTemp.WildRose_DialogeWithSoldierOnPier");
				DelLandQuestMark(npchar);
			}
			//<-- Дикая Роза
		break;
		
		//============================== ноды на разборки при распознавании =========================
		case "PegYou":
			dialog.text = RandPhraseSimple("It seems to me it's some trickery. Let's talk to the commandant, "+GetSexPhrase("mate","deary")+", and figure it all out...","Hmm... Something tells me you're not who you're pretending to be... Surrender your weapon "+GetAddress_Form(npchar)+", and follow me for further investigation!");
			link.l1 = RandPhraseSimple("Screw you!","When two Sundays come in one week...");
			link.l1.go = "fight";
			if (!CheckAttribute(pchar,"questTemp.stels.landSolder") || sti(pchar.questTemp.stels.landSolder) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 40);
				pchar.questTemp.stels.landSolder = GetDataDay();
			}
		break;
		
		case "NotPegYou":
			dialog.text = RandPhraseSimple("Oh, I see... Everything seems to be in order, you're free to go, "+GetAddress_Form(pchar)+".","I must have got a bit tired standing watch... Everything seems to be fine, "+GetAddress_Form(pchar)+", I am sorry.");
			link.l1 = "No problem!";
			link.l1.go = "exit";
			if (!CheckAttribute(pchar,"questTemp.stels.landSolder") || sti(pchar.questTemp.stels.landSolder) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 80);
				pchar.questTemp.stels.landSolder = GetDataDay();
			}
		break;
		
		case "vincento":
			dialog.text = RandPhraseSimple("Oh, I see... Everything seems to be in order, you're free to go. "+GetAddress_Form(pchar)+".","Let's see now... Well, everything seems to be in order, "+GetAddress_Form(pchar)+", I am sorry.");
			link.l1 = "That'll teach you!";
			link.l1.go = "exit";
		break;
		
		case "LicenceOk":
			iTemp = GetDaysContinueNationLicence(HOLLAND);
			if (ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -12)
			{
				dialog.text = "Just think of it! Such insolence! To come here under the guise of a merchant! Your pictures are posted in every barracks, you bastard! You won't get away with it this time! Seize him!";
				link.l1 = RandPhraseSimple("Arrgh!..","Well, you've asked for it...");
				link.l1.go = "fight";	
				break;
			}
			if (pchar.location != "LosTeques_town" && findsubstr(pchar.location.from_sea, "_town" , 0) == -1) //если причалил не в городе 300912
			{
				dialog.text = "You have come to trade here? May I ask how? Where is your ship? You know, it all looks very suspicious, and I am forced to detain you until we sort this out. Surrender your weapon and follow me!";
				link.l1 = RandPhraseSimple("Fuck you!","When two Sundays come in one week...");
				link.l1.go = "fight";	
				break;
			}
			if (iTemp == -1)
			{
				dialog.text = "Your license must be revoked as it has expired and is therefore invalid. Surrender your weapon and follow me for further investigation!";
				link.l1 = RandPhraseSimple("Screw you!","When two Sundays come in one week...");
				link.l1.go = "fight";	
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "Hmm... Everything seems to be in order. Still, I must note that your license expires today. I'll let you pass this time, but you will still need to obtain a new license.";
				link.l1 = "Thank you, I'll get a new one at my earliest convenience.";
				link.l1.go = "exit";			
			}
			if (iTemp > 0 && iTemp <= 10)
			{
				dialog.text = "Hmm... Everything looks alright. Still, I must note that your license will expire soon. It is valid only for "+FindRussianDaysString(iTemp)+". So keep that in mind, "+GetAddress_Form(npchar)+".";
				link.l1 = "Thank you, I'll get a new one at my earliest convenience.";
				link.l1.go = "exit";			
			}
			if (iTemp > 10)
			{
				dialog.text = LinkRandPhrase("Well, everything looks fine. Your license is valid for another "+FindRussianDaysString(iTemp)+". You may pass.","Everything is clear, "+GetAddress_Form(npchar)+". You are free to come and go from town, your license is valid for another "+FindRussianDaysString(iTemp)+". Sorry for bothering you.","Everything looks fine, "+GetAddress_Form(npchar)+", I am no longer keeping you here.");
				link.l1 = RandPhraseSimple("Excellent. Best regards.","Thank you, officer.");
				link.l1.go = "exit";
			}
		break;
		//============================== ноды маяка Порт Рояля =========================
		case "PortRoyal_Mayak":
			dialog.text = RandPhraseSimple("Hey, mate, don't break anything in the lighthouse.","This lighthouse is a very important part of the town. Be careful!");
			link.l1 = RandPhraseSimple("Alright, don't worry.","Alright, don't worry.");
			link.l1.go = "exit";
			NextDiag.TempNode = "PortRoyal_Mayak";
		break;
		case "PortRoyal_Gans":
			dialog.text = LinkRandPhrase("Don't walk too close to the cannons - this is a military facility!","Strangers are not allowed near the cannons!","If I catch you hanging around near the cannons, you're finished!");
			link.l1 = RandPhraseSimple("I got it.","Alright, I got it.");
			link.l1.go = "exit";
			NextDiag.TempNode = "PortRoyal_Gans";
		break;

		// --> генератор "A damsel in the jungle"
		case "GirlEnc_1":
			dialog.text = "And just who are you, captain? Aren't you, by any chance, an accomplice of the most notorious thief in this settlement?";
			link.l1 = "Whom did you just call a partner in crime?! Are you sunstruck or what?! Hey, take your paws off the girl!";
			link.l1.go = "GirlEnc_11";
			link.l2 = "Actually, I've "+GetSexPhrase("got to know her","got to know her")+" recently...";
			link.l2.go = "GirlEnc_12";
		break;

		case "GirlEnc_11":
			dialog.text = ""+GetSexPhrase("Sir","Miss")+", we have orders to detain her and take her to the dungeon. And if you think you can stop us, you are mistaken.";
			link.l1 = "Let's see, then...";
			link.l1.go = "GirlEnc_11End";
		break;

		case "GirlEnc_11End":
			DialogExit();
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			sld.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		case "GirlEnc_12":
			dialog.text = "Oh, really? In that case, I would advise you to check your pockets. That lady is a professional, you know";
			link.l1 = "Thank you, I will do that. How could I have made such a fool of myself...";
			link.l1.go = "GirlEnc_12End";		
		break;		
		
		case "GirlEnc_12End":
			pchar.money = sti(pchar.money) - makeint(sti(pchar.money)/20);
			NextDiag.CurrentNode = NextDiag.TempNode;
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorStay(sld);
			LAi_CharacterDisableDialog(sld);
			sld.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "GirlEnc_2":
			dialog.text = ""+GetSexPhrase("Sir","Miss")+", we have orders to find that lady and bring her to her father.";
			link.l1 = "Well, an order is an order - go ahead, then.";
			link.l1.go = "GirlEnc_2End";
			link.l2 = "Too late for that, because I am already talking to her father.";
			link.l2.go = "GirlEnc_21";
		break;
		
		case "GirlEnc_2End":
			NextDiag.CurrentNode = NextDiag.TempNode;
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorStay(sld);
			LAi_CharacterDisableDialog(sld);
			sld.lifeDay = 0;	
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("JungleGirl", "11");	
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));	
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();			
		break;
		
		case "GirlEnc_21":
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < rand(100))
			{
				dialog.text = "Captain, we have our orders, and if you think you can stop us, you are mistaken.";
				link.l1 = "Let's see, then...";
				link.l1.go = "GirlEnc_21End";
			}
			else
			{
				dialog.text = "Heh, "+GetSexPhrase("you're a lucky man","you're a lucky lass")+". Her father has promised a generous reward to whoever brings her back to him.";
				link.l1 = "Don't despair - you still have many rewards ahead of you.";
				link.l1.go = "exit";			 
			}
		break;
		
		case "GirlEnc_21End":
			DialogExit();
			AddQuestRecord("JungleGirl", "12");
			AddQuestUserData("JungleGirl","sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			CloseQuestHeader("JungleGirl");
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			sld.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");				
		break;
		// <-- генератор "A damsel in the jungle"
		// --> belamour ночной приключенец
		case "NightAdventure_CitizenHomieSolder":
			dialog.text = "Yes, with me. Let him sit behind bars and think about his behaviour. And if you came to threaten me on his behalf, then believe me: I can even reach the commandant of the fort.";
			link.l1 = "Yes, I did not come to threaten, but to ask you to withdraw your claims against him. You see, he is an old acquaintance of mine, he just got drunk, but you know, for a drunk, the sea is knee-deep ...";
			link.l1.go = "NightAdventure_CitizenHomieSolder_1";
		break;
		
		case "NightAdventure_CitizenHomieSolder_1":
			dialog.text = "That is, he gave me a black eye while I was on duty, and now he should be released? Why should that happen?";
			link.l1 = "How about five hundred pesos as an apology for his behaviour?";
			link.l1.go = "NightAdventure_CitizenHomieSolder_2";
		break;
		
		case "NightAdventure_CitizenHomieSolder_2":
			dialog.text = "Do you think so? He has insulted my honour, and you think this can be forgiven for five hundred pesos? Do you think my honour can be bought?";
			link.l1 = "...";
			link.l1.go = "NightAdventure_CitizenHomieSolder_3";
		break;
			
		case "NightAdventure_CitizenHomieSolder_3":
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomieSolderNM")
			{
				DeleteAttribute(pchar,"GenQuest.NightAdventureSolNum");
				pchar.quest.NightAdventure_SeaExit.over = "yes";
				pchar.quest.NightAdventure_JungleExit.over = "yes";
				SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
				dialog.text = "No, Captain, it's all fair. He deserved it. And I ask you not to distract me from my duties anymore.";
				link.l1 = "Well, you're right.";
				link.l1.go = "exit";
			}
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomieSolderGM")
			{
				dialog.text = "Thousand. And not a peso less.";
				link.l1 = "No, perhaps I'm not ready to pay so much for a single bruise.";
				link.l1.go = "NightAdventure_CitizenHomieSolder_3NM";
				if (sti(pchar.money) >= 1000)
				{
					link.l2 = "Oh... Fine, hold on. Here's a pen and some parchment right away. Write that you are withdrawing any claims against my friend.";
					link.l2.go = "NightAdventure_CitizenHomieSolder_3GM";
				}
			}
		break;
		
		case "NightAdventure_CitizenHomieSolder_3NM":
			DeleteAttribute(pchar,"GenQuest.NightAdventureSolNum");
			pchar.quest.NightAdventure_SeaExit.over = "yes";
			pchar.quest.NightAdventure_JungleExit.over = "yes";
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			dialog.text = "Then I ask you not to distract me from my duties any further.";
			link.l1 = "I won't.";
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_CitizenHomieSolder_3GM":
			DeleteAttribute(pchar,"GenQuest.NightAdventureSolNum");
			pchar.GenQuest.NightAdventureToPrisoner = true;
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = "Here you are.";
			link.l1 = "Good luck with the job.";
			link.l1.go = "exit";
		break;
		// <-- ночной приключенец
		
		//--> Дикая Роза
		case "WildRose_Soldier_1":
			if (GetHour() >= 6 && GetHour() <= 21)
			{
				dialog.text = "Ah, it’s you, captain... The sun’s made me drowsy... Cursed heat!";
			}
			else
			{
				dialog.text = "Can’t argue with that. Still, at night everyone looks the same, you know.";
			}
			link.l1 = "What’s the matter, soldier? Normally your lot doesn’t bother me with talk.";
			link.l1.go = "WildRose_Soldier_2";
		break;
		
		case "WildRose_Soldier_2":
			dialog.text = "Ahem, yes, "+GetAddress_Form(NPChar)+". But I have an order from Lord Willoughby: I must warn all newcomers to the island that a few days ago a bunch of slaves bolted from Bishop’s plantation. Damn overseers must’ve been fast asleep while they were breaking their chains. And today I should’ve been in the arms of my sweet Angelique...";
			link.l1 = "Let me guess: they sent garrison soldiers to hunt down the planter’s property?";
			link.l1.go = "WildRose_Soldier_3";
		break;
		
		case "WildRose_Soldier_3":
			dialog.text = "Of course... Bishop also sent a few bands of his mercenaries into the jungle, but even that wasn’t enough for him. He promised a fine reward to anyone who brings the slaves back. Alive. Usually it’s the blacks who bend their backs for him, but not long ago they delivered a batch of navy deserters – not much use in the stone quarry, but smart enough to slip off the plantation...";
			link.l1 = "So they were whites?";
			link.l1.go = "WildRose_Soldier_4";
		break;
		
		case "WildRose_Soldier_4":
			dialog.text = "White as they come, strike me down! The blacks would’ve just run, but these grabbed a few muskets and sabers off slain mercenaries – and already put them to use. Took down one of ours, and a couple of Bishop’s lackeys too – which drove the rest mad.\nThey almost gunned down our own men by mistake, thinking they were the fugitives. And a few civilians vanished without a trace in the jungle.";
			link.l1 = "The city gates are locked?";
			link.l1.go = "WildRose_Soldier_5";
		break;
		
		case "WildRose_Soldier_5":
			dialog.text = "No, of course not – the city isn’t under siege. You’re free to go wherever you wish. But if you decide to hunt the fugitives and get caught in crossfire, don’t come whining. And if you survive, don’t bother knocking at the residence to complain to His Lordship – after all, he’s shown enough goodwill to care not only for Bridgetown’s citizens but also its guests.";
			link.l1 = "How... gracious of him. God save Francis Willoughby!";
			link.l1.go = "WildRose_Soldier_6";
			link.l2 = "Ah, if only all governors cared so much for newcomers as Sir Willoughby!..";
			link.l2.go = "WildRose_Soldier_7";
		break;
		
		case "WildRose_Soldier_6":
			dialog.text = "Very funny. You may go, captain.";
			link.l1 = "Farewell then, soldier.";
			link.l1.go = "WildRose_Soldier_8";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "WildRose_Soldier_7":
			dialog.text = "Aye, we’d have a lot less work on our hands. I won’t keep you any longer, captain.";
			link.l1 = "Good luck, soldier.";
			link.l1.go = "WildRose_Soldier_8";
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 2);
		break;
		
		case "WildRose_Soldier_8":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves");
		break;
		//<-- Дикая Роза
		
		//замечение по обнажённому оружию
		case "SoldierNotBlade":
			// belamour legendary edition если у герой офицер нации -->
			if(IsOfficerFullEquip())
			{
			dialog.text = "Captain, I ask you to put away your weapons: it is forbidden to draw them in our city.";
			link.l1 = LinkRandPhrase("Alright, I'll put it away...","Already done.","As you say...");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Screw you!","I suppose I'll use it!","I'll put it away when the time is right.");
			link.l2.go = "fight";
			npchar.greeting = "soldier_common";
			NextDiag.TempNode = "First Time";
		break;
			}
			// <-- legendary edition
			dialog.text = LinkRandPhrase("Hey, what's the deal with all that weapon swinging?! Put it away this instant!","I order you to put away your weapon at once!","Hey, "+GetAddress_Form(NPChar)+", stop scaring people! Put away your weapon.");
			link.l1 = LinkRandPhrase("Alright, I'll put it away...","Already done.","As you say...");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Screw you!","I suppose I'll use it!","I'll put it away when the time is right.");
			link.l2.go = "fight";
			npchar.greeting = "soldier_common";
			NextDiag.TempNode = "First Time";
		break;

		case "pirate_fight":
			DialogExit();
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_group_Attack(NPChar, Pchar);
			DoQuestFunctionDelay("TownPirate_battle", 0.5);
		break;
	}
}

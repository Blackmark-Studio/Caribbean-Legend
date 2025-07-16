// Альберт Локсли - адвокат
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n;
    string sTemp, attrLoc;
	
    attrLoc = Dialog.CurrentNode;
	int iSumm = 0;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	if (findsubstr(attrLoc, "RelationTo_" , 0) != -1)
	{
		i = findsubstr(attrLoc, "_" , 0);
		npchar.quest.relation = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
		// проверка на уже договор
		attrLoc = "RelationAgent" + GetNationNameByType(sti(npchar.quest.relation));
		if (CheckAttribute(Pchar, "GenQuest." + attrLoc) && sti(Pchar.GenQuest.(attrLoc)) == true)
		{
			Dialog.CurrentNode = "RelationYet";
		}
		else
		{
			Dialog.CurrentNode = "RelationAny_Done";
			npchar.quest.relation.summ = CalculateRelationLoyerSum(sti(npchar.quest.relation));
		}
	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "My name is Albert Loxley and I am a lawyer. I present my client's interests in trials. My services are pricey, but they're worth it, I can assure you.";
				if(SandBoxMode)
				{					
					if (ChangeCharacterNationReputation(pchar, ENGLAND, 0) < 0)
					{
						link.l1 = "I am in trouble with the English authorities.";
						link.l1.go = "RelationTo_0";
					}
					
					if (ChangeCharacterNationReputation(pchar, FRANCE, 0) < 0)
					{
						link.l2 = "I am in trouble with the French authorities.";
						link.l2.go = "RelationTo_1";
					}
					if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0)
					{
						link.l3 = "I am in trouble with the Spanish authorities.";
						link.l3.go = "RelationTo_2";
					}

					if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0)
					{
						link.l4 = "I am in trouble with the Dutch authorities.";
						link.l4.go = "RelationTo_3";
					}
					if (ChangeContrabandRelation(pchar, 0) <= 5)
					{
						Link.l5 = "I quarreled with the smugglers.";
						Link.l5.go = "contraband";
					}
					Link.l7 = "Thanks but, fortunately, I don't need the services of a lawyer so far.";
					Link.l7.go = "exit";
					NextDiag.TempNode = "Loxly";
					npchar.quest.meeting = "1";
				}
				link.l1 = "Thanks but, fortunately, I don't need the services of a lawyer so far.";
				link.l1.go = "exit";
				npchar.quest.meeting = "1";
				if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "loxly")
				{
					link.l1 = "I need your services. I am an authorized delegate of one young lady named Helen McArthur, she is the granddaughter of the famous Nicolas Sharp. She is the only heir at law left after the death of her mother and uncle. She has all rights to Isla Tesoro according to her uncle's testament. How much would you ask for helping Helen become the rightful mistress of the island?";
					link.l1.go = "saga";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Saga"))
				{
					if (pchar.questTemp.Saga == "loxly") // первое обращение по саге
					{
						dialog.text = "Do you need my services, Sir? You will be satisfied, I can assure you.";
						link.l1 = "Yes, I need them. I am an authorized delegate of one young lady named Helen McArthur, she is the granddaughter of the famous Nicolas Sharp. She is the only heir at law left after the death of her mother and uncle. She has all rights to Isla Tesoro according to her uncle's testament. How much would you ask for helping Helen become the rightful mistress of the island?";
						link.l1.go = "saga";
						break;
					}
					if (pchar.questTemp.Saga == "bakaut")
					{
						dialog.text = "Sir, I am not familiar with the materials of your business yet. Please, come see me later as I've already told you.";
						link.l1 = "Fine.";
						link.l1.go = "exit";
						break;
					}
					if (pchar.questTemp.Saga == "molligan" || pchar.questTemp.Saga == "sellbakaut")
					{ // если не выполнил до конца квест по бакауту
						dialog.text = "Sir, unfortunately, I need more time to gather all the papers needed in the archives. I am not ready yet. Please, see me later.";
						link.l1 = "Fine.";
						link.l1.go = "exit";
						break;
					}
					if (pchar.questTemp.Saga == "removebakaut") // с бакаутом разобрались
					{
						// четвертая проверка времени
						if (CheckAttribute(pchar, "questTemp.Saga.Late"))
						{
							RemoveItems(pchar, "map_sharp_full", 1);
							dialog.text = "Mister, why have you been working so slowly?! It's all over for your principal. The period of validation of the testament has expired and Isla Tesoro now belongs to England. It will become a military base soon."
							link.l1 = "Wow! It seems that all my efforts were for nothing...";
							link.l1.go = "saga_l3";
						}
						else
						{
							dialog.text = "Ah, here you are, Sir. I have become familiar with the materials so it's time for an advance payment. Have you brought the doubloons with you?";
							if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) {n = 1000;}
							else {n = 450;}
							if (PCharDublonsTotal() >= n)
							{
								link.l1 = "Yes, I have. Here are your doubloons.";
								link.l1.go = "saga_5";
							}
							else
							{
								link.l1 = "Pardon me for my bad memory, I have left them in a chest on my ship. I will bring them at once.";
								link.l1.go = "exit";
							}
						}
						break;
					}
					if (pchar.questTemp.Saga == "shadow")
					{
						// пятая проверка времени
						if (CheckAttribute(pchar, "questTemp.Saga.Late"))
						{
							dialog.text = "Mister, why have you been working so slowly?! It's all over for your principal. The period of validation of the testament has expired and Isla Tesoro now belongs to England. It will become a military base soon."
							link.l1 = "Wow! It seems that all my efforts were for nothing...";
							link.l1.go = "saga_l3";
						}
						else
						{
							dialog.text = "Sir, were you able to find anything that can prove your principal's parentage?";
							if (!CheckCharacterItem(pchar, "Letter_beatriss"))
							{
								link.l1 = "Not yet. But I am working on it.";
								link.l1.go = "exit";
							}
							else
							{
								link.l1 = "Yes. I really have exhaustive proof.";
								link.l1.go = "saga_14";
							}
						}
						break;
					}
					if (pchar.questTemp.Saga == "court" && GetNpcQuestPastDayParam(npchar, "court_date") >= 1 && IsOfficer(characterFromId("Helena")))
					{
						 // запрет сохранения чтобы ленку не заграбастали себе умники всякие с ГК-  лесник
						InterfaceStates.Buttons.Save.enable = false;//запретить сохраняться																																			   
						dialog.text = "A-ah, here you are, Sir. Glad to see you. I must admit, I've been waiting for you for quite some time. Is this your principal?";
						link.l1 = "Yes. Let me introduce you to Helen McArthur.";
						link.l1.go = "saga_26";
						break;
					}
					dialog.text = "Do you need my services, Sir? You will be satisfied, I can assure you.";
					link.l1 = "Thank you, but I don't need them for now.";
					link.l1.go = "exit";
				}
				if (CheckAttribute(npchar, "quest.waitgold"))
				{
					dialog.text = "Good day, Sir. I take it that you have brought my fee?";
					if (PCharDublonsTotal() >= 450)
					{
						link.l1 = "Yes, I have. Here are your doubloons.";
						link.l1.go = "saga_36";
					}
					link.l2 = "You know, Mister Loxley, I thought... My point is that 900 doubloons is more than enough for your work.";
					link.l2.go = "saga_38";
					link.l3 = "I remember, Mister Loxley. I will bring it a bit later...";
					link.l3.go = "exit";
					break;
				}
				dialog.text = "Do you need my services, Sir? You will be satisfied, I can assure you.";
				link.l1 = "Thank you, but I don't need them for now.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "saga":
			// третья проверка времени. Отбираем Элен, чистим квестовый лут, даем флаг на Свенсона, вызываем перемены
			if (CheckAttribute(pchar, "questTemp.Saga.Late"))
			{
				RemoveItems(pchar, "map_sharp_full", 1);
				dialog.text = "Sir, you must have been at sea for too long. Isla Tesoro is now a military base of the English Navy! Yes, Sharp's testament exists but it has expired and Isla Tesoro has become property of the English crown. Alas!"
				link.l1 = "Wow! It seems that all my efforts were for nothing...";
				link.l1.go = "saga_l3";
			}
			else
			{
				dialog.text = "The lady claims to own the whole island? Hm... It seems that it won't be an easy matter. Isla Tesoro is almost an English colony already...";
				link.l1 = "Not yet. According to the testament, the man or woman who shows both parts of the map will become the owner of Isla Tesoro. We have both parts of Sharp's map which is the main proof of heritage.";
				link.l1.go = "saga_1";
			}
		break;
		
		case "saga_1":
			dialog.text = "Nicolas Sharp... Well, well. I need to visit an archive and get familiar with materials pertinent to Isla Tesoro. Do you have the map with you?";
			link.l1 = "I have, but I will give it to you only after we sign a contract. So, what about the price for your services?";
			link.l1.go = "saga_2";
		break;
		
		case "saga_2":
			sTemp = "";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) sTemp = " Your esteemed involvement won't go unnoticed either. Cartagena... There will be questions.";
			dialog.text = "As I said - it won't be easy. You need to prove the right of ownership to an entire island, not to some old tub or a shack. Besides, Nicolas Sharp was a pirate and helping pirates or their relatives is pricey."+sTemp;
			link.l1 = "Are you going to tell me an actual sum?";
			link.l1.go = "saga_3";
		break;
		
		case "saga_3":
			sTemp = "four hundred and fifty";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) sTemp = "one thousand";
			dialog.text = "Sir, the final sum will be formed during the trial. I still don't know how problematic it will be. But I am ready to estimate an advance - "+sTemp+" doubloons. This amount of gold will have to be paid again once or twice, depending on how well our business will go.\nBring me the money in a week, I need time to check the archives and to prepare myself. Then we will make an arrangement. Deal?";
			link.l1 = "They have recommended you as the best lawyer in the archipelago, so we have a deal. See you in a week!";
			link.l1.go = "saga_4";
		break;
		
		case "saga_4":
			DialogExit();
			pchar.questTemp.Saga = "bakaut"; // обновляем флаг
			AddQuestRecord("Testament", "2");
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) AddQuestUserData("Testament", "sMoney", "1000");
			else AddQuestUserData("Testament", "sMoney", "450");
			
			if (pchar.questTemp.HelenDrinking.Result != "no_visit") {
				bDisableFastReload = true;
				SetFunctionLocationCondition("HelenDrinking_PortRoyalDialog", "PortRoyal_town", false);
			}
		break;
		
		case "saga_5":
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold"))
			{
				RemoveDublonsFromPCharTotal(1000);
				//Log_Info("You have given 1450 doubloons");
			}
			else
			{
				RemoveDublonsFromPCharTotal(450);
				//Log_Info("You have given 450 doubloons");
			}
			PlaySound("interface\important_item.wav");
			dialog.text = "Very well. I am ready to take on your case and to represent your interests in court. Now let's cut to the chase. I did good in the archives and talked with important people. The case of Sharp's legacy is not going to be easy. It's good that you've acquired both pieces of the map. But this might not be enough.\nColonel Doyle has big plans for Isla Tesoro, since he failed to seize control over Tortuga. It has natural defences and could serve as a future military base in this area.";
			link.l1 = "But Helen has all rights to the island according to the law of England!";
			link.l1.go = "saga_6";
		break;
		
		case "saga_6":
			dialog.text = "You don't know perhaps that late Sharp made an addition to his will. An heir or heirs must have his surname. And as far as I remember, your girl has a different surname. You've said that it was McArthur, right?";
			link.l1 = "This is the surname of her stepfather, but Helen has all rights to carry Sharp as her surname, because she is a daughter of late Beatrice Sharp, the daughter of Nicolas.";
			link.l1.go = "saga_7";
		break;
		
		case "saga_7":
			dialog.text = "Splendid! But who can confirm that under oath? Were Helen's foster parents familiar with Beatrice Sharp?";
			link.l1 = "As far as I understand, then weren't. Mister McArthur considered her to be Gladys' daughter and Gladys was only familiar with the girl's father.";
			link.l1.go = "saga_8";
		break;
		
		case "saga_8":
			dialog.text = "That is a pity. See, I haven't found any mention in the archives that Beatrice Sharp ever had any offspring. There is a possibility that there is no official note about the child's birth at all. Anyone can call himself a grandkid of Sharp and claim the right to carry his surname.";
			link.l1 = "But only Helen has the complete map!";
			link.l1.go = "saga_9";
		break;
		
		case "saga_9":
			dialog.text = "This is her trump card and perhaps it would be enough if the local authorities didn't have their own plans for Isla Tesoro. A document with the handwriting of Beatrice and her signature under it is in the archives. We need to find some document written by her which would prove the fact of her daughter's birth, the daughter who was given to that Gladys... eh, what was her surname?";
			link.l1 = "Chandler. Gladys Chandler from Belize.";
			link.l1.go = "saga_10";
		break;
		
		case "saga_10":
			dialog.text = "Exactly. Do you have an opportunity to find anything like that?";
			link.l1 = "I doubt it. Too many years have passed. According to the legend, captain Butcher himself might be Helen's father. Perhaps, the ex-hangman of St. John's can tell us something about this. He was the last man who saw her father alive.";
			link.l1.go = "saga_11";
		break;
		
		case "saga_11":
			dialog.text = "Hm. He really was an entertaining man. As far as remember, his name was Raymond Baker. I was lucky to chat with him once. He is a smart and well educated man. Well, try to find something on Antigua and I am going to continue my searches in the archives, perhaps I'll find something useful.";
			link.l1 = "Fine. Works for me.";
			link.l1.go = "saga_12";
		break;
		
		case "saga_12":
			dialog.text = "Give me Sharp's map and hurry up, talk to Baker, perhaps you will be able to find some documents with his help. You might even find evidence of her birth.";
			link.l1 = "Eh, I wish I could. Fine, see you, Mister Loxley.";
			link.l1.go = "saga_13";
		break;
		
		case "saga_13":
			DialogExit();
			RemoveItems(pchar, "map_sharp_full", 1);
			pchar.questTemp.Saga = "shadow";
			pchar.questTemp.Saga.Shadows = "sentjons";
			AddQuestRecord("Shadows", "1");
		break;
		
		case "saga_14":
			dialog.text = "Is that so? Let's have a look at this evidence.";
			link.l1 = "This is a private letter written by Beatrice Sharp to her brother. It's written here that she gave birth to a daughter and that her father was in fact Lawrence Beltrope. The girl was sent to a young widow named Gladys Chandler. Lawrence Beltrope is also know as captain Butcher. Here, take the letter...";
			link.l1.go = "saga_15";
		break;
		
		case "saga_15":
			RemoveItems(pchar, "Letter_beatriss", 1);
			dialog.text = "";
			link.l1 = "Gladys is ready to confirm it under oath. She is also ready to confirm that the father had introduced himself as captain Butcher.";
			link.l1.go = "saga_16";
		break;
		
		case "saga_16":
			if (CheckAttribute(pchar, "questTemp.Saga.Beltrop_die")) // Белтроп убит
			{
				dialog.text = "Wait a minute! Captain Butcher, the evil pirate and killer of English subjects was hanged in the fort of St. John's twenty years ago. And Lawrence Beltrope, a close friend to Richard Doyle, tragically died not long ago. And most of all, Doyle wanted to make him the new governor of Sharptown!";
				link.l1 = "Ha! Sure, nobody knows that... I have a written testimony of Raymond Baker, the ex hangman of St. John's, that he was forced under threat of certain death to fake Butcher's execution! Here, take a look...";
				link.l1.go = "saga_17";
			}
			else
			{
				dialog.text = "Wait a minute! Captain Butcher, the evil pirate and killer of English subjects was hanged in the fort of St. John's twenty years ago. And Lawrence Beltrope is alive and lives in one of the best mansions of Port Royal. And most of all, Doyle wants to make him the new governor of Sharptown!";
				link.l1 = "Ha! Sure, nobody knows that... I have a written testimony of Raymond Baker, the ex hangman of St. John's, that he was forced under threat of certain death to fake Butcher's execution! Here, take a look...";
				link.l1.go = "saga_17";
			}
		break;
		
		case "saga_17":
			RemoveItems(pchar, "letter_baker", 1);
			dialog.text = "Hm. Well, well...";
			link.l1 = "Isn't that very adroitly? Captain Butcher managed to stay alive and went back to England. He changed his name back to Lawrence Beltrope and has returned here unnoticed.";
			if (CheckAttribute(pchar, "questTemp.Saga.Beltrop_die")) link.l1.go = "saga_18";
			else link.l1.go = "saga_22";
		break;
		
		case "saga_18":
			dialog.text = "But this... This changes everything! Publishing Beatrice's letter will show that all this time the military governor had been hiding the fugitive pirate Butcher, who should have been arrested on sight and who should have appeared in court for his past crimes!\nAnd Baker's testimony will completely destroy any reasons against that! This is great! With such an ace in the hand we will beat Doyle fair and square!";
			link.l1 = "I am glad. I rely on you in this trial. Also, tell me, how did Lawrence Beltrope die?";
			link.l1.go = "saga_19";
		break;
		
		case "saga_19":
			dialog.text = "This is a creepy story, Sir. He was found in his own bedroom with a twisted face. It is too hard to imagine what could have scared this fearless man so much. They say that he was covered in hoarfrost. His body was full of scary looking, lacerated wounds, but not a single drop of blood on the floor! Just imagine! Not a single drop!";
			link.l1 = "Yes, that seems straight out of a nightmare. It seems that he was murdered... But who could have done that?";
			link.l1.go = "saga_20";
		break;
		
		case "saga_20":
			dialog.text = "It is unknown. It is too tangled... The garrison physician said that his wounds were none lethal. Beltrope died of fear, pain or something else. Anyway, this is a mystic death.";
			link.l1 = "I see... And when will the trial begin?";
			link.l1.go = "saga_21";
		break;
		
		case "saga_21":
			dialog.text = "It all depends on you, Sir. I will submit all documents to the court as soon as you pay me the second part of my fee - 450 doubloons. Helen will gain her rights a week after that.";
			if (PCharDublonsTotal() >= 450)
			{
				link.l1 = "Very well. Here are your doubloons.";
				link.l1.go = "saga_24";
			}
			else
			{
				link.l1 = "Yes, sure. I will bring you the sum you need.";
				link.l1.go = "exit";
				NextDiag.TempNode = "saga_23";
			}
		break;
		
		case "saga_23":
			// шестая проверка времени
			if (CheckAttribute(pchar, "questTemp.Saga.Late"))
			{
				dialog.text = "Sir, you have staggered me! You have done so much, the island was almost in our hands but it is over now because of your delay with my fee! The testament expired and Isla Tesoro belongs to the English crown now. It will be a military base."
				link.l1 = "Wow! It seems that all my efforts were for nothing...";
				link.l1.go = "saga_l3";
			}
			else
			{
				dialog.text = "Have you brought the second part of my fee, Sir?";
				if (PCharDublonsTotal() >= 450)
				{
					link.l1 = "Yes, sure. Here are your doubloons.";
					link.l1.go = "saga_24";
				}
				else
				{
					link.l1 = "Pardon me for my bad memory, I have left them in a chest on my ship. I will bring them at once.";
					link.l1.go = "exit";
					NextDiag.TempNode = "saga_23";
				}
			}
		break;
		
		case "saga_22":
			dialog.text = "But this... this changes everything! Publishing Beatrice's letter will mean that Lawrence Beltrope must be arrested immediately and appear in court for his past crimes!\nAnd Baker's testimony will completely destroy any reasons against that! This is great! With such an ace in the hand we will beat Doyle fair and square!";
			link.l1 = "I am very glad. When will the trial begin?";
			link.l1.go = "saga_21";
		break;
		
		case "saga_24":
			RemoveDublonsFromPCharTotal(450);
			//Log_Info("You have given 450 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Excellent, Sir. Pleasure doing business with you. Now, here is the deal. Come back here tomorrow. Yes-yes, you have heard right - tomorrow! After all I am the best lawyer of the archipelago and I have connections.\nBring your principal, the trial won't happen without her. Don't be late and don't leave the city. And take the last part of the payment with you if you can, I am completely sure of our victory.";
			link.l1 = "Good. We will be at your office tomorrow, Mister Loxley.";
			link.l1.go = "saga_25";
		break;
		
		case "saga_25":
			DialogExit();
			SaveCurrentNpcQuestDateParam(npchar, "court_date");
			pchar.questTemp.Saga = "court"; // обновляем флаг
			AddQuestRecord("Testament", "10");
			NextDiag.CurrentNode = "First time";
			// закрываем выходы из города
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", true);
			//LocatorReloadEnterDisable("PortRoyal_town", "reload2_back", true);// лесник там нет этого пирса
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", true);
			//pchar.GenQuest.CannotWait = true;//запрет ожидания
			// снимаем общий таймер Саги!
			pchar.quest.Saga_TimeOver.over = "yes";
		break;
		
		case "saga_26":
			dialog.text = "MacArthur? No, it's Sharp! Well, follow me now!";
			link.l1 = "...";
			link.l1.go = "saga_27";
		break;
		
		case "saga_27":
			DialogExit();
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto10");
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			sld = characterFromId("Helena");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(npchar, "reload", "reload1", "Saga_CourtGo", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
			LAi_ActorFollow(sld, npchar, "", -1);
			NextDiag.CurrentNode = "saga_28";
			// открываем выходы из города
			//LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false); // лесник рано 
			//LocatorReloadEnterDisable("PortRoyal_town", "reload2_back", false);
			//LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false);
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
		break;
		
		case "saga_28":
			dialog.text = "Allow me to congratulate you, Sir, and your principal. She is the rightful ruler of Ilsa Tesoro now. It's worth drinking some champagne over this!";
			link.l1 = "Absolutely, Mister Loxley. Your speech was most excellent. I thought that colonel Doyle would suffer a heart attack when you told the court that Lawrence Beltrop is captain Butcher.";
			link.l1.go = "saga_29";
		break;
		
		case "saga_29":
			dialog.text = "Yes, mister Doyle will have to say goodbye to his dream of a military base on Isla Tesoro. And what can he do? Law is law and it is written for everyone, even for the respected colonel.";
			if (CheckAttribute(pchar, "questTemp.Saga.Beltrop_die"))
			{
				link.l1 = "Are all the papers fine and do they confirm Helen's right to the island?";
				link.l1.go = "saga_30";
			}
			else
			{
				link.l1 = "I have heard that the judge has ordered the arrest of Lawrence Beltrop. I take it that he is going to be hanged?";
				link.l1.go = "saga_34";
			}
		break;
		
		case "saga_30":
			dialog.text = "Sure, Sir. I have checked every comma on them. You can be sure that they are fine.";
			link.l1 = "Very well...";
			link.l1.go = "saga_31";
		break;
		
		case "saga_31":
			dialog.text = "Well, my job is done. The case was tricky but we have won it together. Now, Sir, you only have to pay me the last part of my fee. No pressure, I realize that you must be busy. But I believe that you will find time to bring me the last 450 doubloons within a week.\nBesides, a client like you may always count on substantial discounts. I can help you a lot, I have connections into every capital of the archipelago, even into the hostile ones, so any legal problem you encounter can be settled.";
			link.l1 = "Excellent. Now I know who to ask.";
			link.l1.go = "saga_32";
		break;
		
		case "saga_32":
			dialog.text = "I guarantee you a positive outcome even in the toughest situations.";
			link.l1 = "Nice. I have to go now, me and Helen have a lot to do.";
			link.l1.go = "saga_33";
		break;
		
		case "saga_33":
			dialog.text = "Goodbye, Sir.";
			link.l1 = "Goodbye, Mister Loxley.";
			link.l1.go = "saga_35";
		break;
		
		case "saga_34":
			dialog.text = "I suppose so, he is captain Butcher, a pirate and bandit. Though he is not in Port Royal now. He was fortunate enough to leave, moving deep into the island. But the hunt has begun and he will be caught for sure.";
			link.l1 = "I see... Are the papers in check?";
			link.l1.go = "saga_30";
		break;
		
		case "saga_35":
			DialogExit();
			SetFunctionTimerCondition("Saga_RemainGoldLoxly", 0, 0, 10, false); // таймер на оплату услуг
			DoQuestReloadToLocation("PortRoyal_town", "quest", "quest3", "Saga_HelenaIslaTesoro");
			npchar.quest.waitgold = "true";
			pchar.questTemp.Saga = "lastpages";
			NextDiag.CurrentNode = "First time";
		break;
		
		case "saga_36":
			RemoveDublonsFromPCharTotal(450);
			//Log_Info("You have given 450 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Splendid! It was a pleasure doing business with you, Sir! Now you can ask for my help in any matter and receive a discount. Troubles with the law, bounty for your head... You are welcome. I will always be glad to see you.";
			link.l1 = "It would be better if I stay out of trouble at all but... things happen. Thank you and goodbye, Mister Loxley.";
			link.l1.go = "saga_37";
		break;
		
		case "saga_37":
			DialogExit();
			pchar.quest.Saga_RemainGoldLoxly.over = "yes"; //снять таймер
			NextDiag.CurrentNode = "Loxly"; // услуги адвоката
		break;
		
		case "saga_38":
			dialog.text = "What do you mean, Mister? Are you going to breach the terms of our agreement?";
			link.l1 = "Exactly. I did most of the work. You can't even imagine what I had to do to get the evidence. And you have only taken those papers and went to court. Nine hundred doubloons is more than enough, I am certain of that.";
			link.l1.go = "saga_39";
		break;
		
		case "saga_39":
			dialog.text = "You speak like a pirate, Mister! Well, I won't go poor losing four hundred fifty doubloons but you won't go rich either. In fact, you've just lost much more! And you will lose something in the future perhaps... Leave my house immediately and don't ever show yourself here again!";
			link.l1 = "And I am going to do that. Farewell, Mister Loxley.";
			link.l1.go = "exit";
			NextDiag.TempNode = "saga_40";
			pchar.quest.Saga_RemainGoldLoxly.over = "yes"; //снять таймер
			LocatorReloadEnterDisable("PortRoyal_town", "houseSp4", true); // закроем вход к Локсли
			ChangeCharacterNationReputation(pchar, ENGLAND, -10);
		break;
		
		case "saga_40":
			dialog.text = "I don't want to talk with you. Get lost or I will call the guards!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "saga_40";
		break;
		
		// провалы Саги
		case "saga_l3":
			dialog.text = "Sir, we would have won your case if you had come to see me earlier. The testament has expired. I am sorry.";
			link.l1 = "Eh, I am even more sorry! Well, farewell, Mister Loxley.";
			link.l1.go = "saga_l3_1";
			// Элен - к разговору
			sld = characterFromId("Helena");
			sld.quest.talk = "late_l3";
		break;
		
		case "saga_l3_1":
			DialogExit();
			pchar.quest.Saga_Late_3.win_condition.l1 = "Location_Type";
			pchar.quest.Saga_Late_3.win_condition.l1.location_type = "town";
			pchar.quest.Saga_Late_3.function = "Saga_HelenaTalk";
			Saga_ChangesIslatesoro(); // вызов перестановки на Исла-Тесоро
			pchar.questTemp.Saga = "late_l3"; // для Свенсона
		break;
		
	//-------------------------------------- адвокатские услуги ------------------------------------------------
		case "Loxly":
			dialog.text = TimeGreeting()+", Sir. Glad to see you. Do you need my services?";
			link.l1 = "Yes. That is why I am here.";
			link.l1.go = "loxly_1";
			link.l2 = "No, fortunately I don't need them at the moment. Just wanted to greet you.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Loxly";
		break;
		
		case "loxly_1":
			dialog.text = "I am ready to listen to you. What kind of help do you need.";
			if (ChangeCharacterNationReputation(pchar, ENGLAND, 0) < 0)
			{
				link.l1 = "I am in trouble with the English authorities.";
				link.l1.go = "RelationTo_0";
			}
			
			if (ChangeCharacterNationReputation(pchar, FRANCE, 0) < 0)
			{
				link.l2 = "I am in trouble with the French authorities.";
				link.l2.go = "RelationTo_1";
			}
			if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0)
			{
				link.l3 = "I am in trouble with the Spanish authorities.";
				link.l3.go = "RelationTo_2";
			}

			if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0)
			{
				link.l4 = "I am in trouble with the Dutch authorities.";
				link.l4.go = "RelationTo_3";
			}
			if (ChangeContrabandRelation(pchar, 0) <= 5)
            {
                Link.l5 = "I quarreled with the smugglers.";
				Link.l5.go = "contraband";
            }
			Link.l7 = "I am sorry, I have changed my mind...";
			Link.l7.go = "exit";
			NextDiag.TempNode = "Loxly";
		break;
		
		case "RelationYet": // уже оплачено
			dialog.text = "I am already working on your matter. It will be alright, I can assure you.";
			Link.l1 = "Thank you. I'll be waiting.";
			Link.l1.go = "exit";
			NextDiag.TempNode = "Loxly";
		break;
		
		// --> снятие НЗГ
		case "RelationAny_Done":
			iSumm = sti(npchar.quest.relation.summ);
			int iRate = abs(ChangeCharacterNationReputation(pchar, sti(npchar.quest.relation), 0));
			if (iRate <= 10) sTemp = "Well, I wouldn't call that trouble. Just a little problem. I will settle the affair at once";
			if (iRate > 10 && iRate <= 30) sTemp = "Yes, your reputation is slightly spoiled but I don't see anything critical. I will settle the affair at once";
			if (iRate > 30 && iRate <= 60) sTemp = "Yes, you went down the wrong path with the authorities. It won't be easy but I am sure that I will be able to settle your disagreements without a hitch";
			if (iRate > 60 && iRate <= 90) sTemp = "And how did you do that, Sir? Your troubles are not just serious, they are really serious. The authorities are very eager to get you. I will have to put a lot of effort into settling your disagreements";
			if (iRate > 90) sTemp = "Well... The situation is catastrophic - you are claimed to be the most bitter enemy. It will be tough but I am the best lawyer in the Caribbean after all, so I will settle your disagreements";
			dialog.text = ""+sTemp+" with "+XI_ConvertString(Nations[sti(npchar.quest.relation)].Name+"Abl")+". It will cost you "+FindRussianMoneyString(iSumm)+".";
			if(sti(pchar.money) >= iSumm)
			{
				link.l1 = "Very well, Mister Loxley, I agree. Here is your money and try to settle things as soon as possible.";
				link.l1.go = "relation";
			}
			link.l2 = "I don't have the sum you are asking for right now. I will be back later!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Loxly";
		break;

		case "relation":
			dialog.text = "Pleasure doing business with you, Sir. You can breath freely again, your problem will go away within the next two weeks. Please avoid any confrontations with "+XI_ConvertString(Nations[sti(npchar.quest.relation)].Name+"Abl") +", while I am in the middle of negotiations.";
			link.l1 = "Fine, I will consider your warning. Thank you and farewell!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(npchar.quest.relation.summ));
			ChangeNationRelationFromRelationAgent(npchar);
			attrLoc = "RelationAgent" + GetNationNameByType(sti(npchar.quest.relation));
            Pchar.GenQuest.(attrLoc) = true;
			Pchar.GenQuest.(attrLoc).loyer = "true";
			NextDiag.TempNode = "Loxly";
		break;
		// <-- снятие НЗГ
		
		case "contraband":
			npchar.quest.contrasum = makeint(0.3*stf(Pchar.rank)/stf(Pchar.reputation.nobility)*60000);
			dialog.Text = "And why have you done that? Smugglers are good lads, they are honest in their way. We all need to live and eat... Fine, it is not a big deal and it will cost you only "+FindRussianMoneyString(sti(npchar.quest.contrasum))+".";
			if(sti(Pchar.money) >= sti(npchar.quest.contrasum))
			{
				Link.l1 = "Very well, Mister Loxley, I agree. Here is your money and try to settle things as soon as possible.";
				Link.l1.go = "Contraband_Agreed";
			}
			Link.l2 = "I don't have the sum you are asking for right now. I will be back later!";
			Link.l2.go = "exit";
		break;
		
		case "Contraband_Agreed":
			dialog.Text = "Excellent, I will settle your problem. They will want to do business with you again soon.";
			Link.l1 = "Thanks!";
			Link.l1.go = "exit";
			ChangeContrabandRelation(pchar, GetIntByCondition(HasShipTrait(pchar, "trait23"), 25, 40));
			AddMoneyToCharacter(pchar, -sti(npchar.quest.contrasum));
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

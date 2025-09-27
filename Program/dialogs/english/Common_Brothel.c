void ProcessDialogEvent()
{
	ref NPChar, sld, location;
	aref Link, NextDiag;
	string sTemp,sTemp1, str, str1;
	int	s1,s2,s3,s4,s5,p1, iColony, crewWhoreCost, charWhoreCost = 0;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
		
    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Brothel\" + NPChar.City + "_Brothel.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	crewWhoreCost = 50 + 7 * MOD_SKILL_ENEMY_RATE - hrand(40);
	charWhoreCost = 2460 + sti(pchar.rank) * 40;
	
	switch(Dialog.CurrentNode)
	{
		// ============= хозяйка борделя =============
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase(""+GetSexPhrase("What girls, dear?! Half the garrison is after you, and you come straight to the brothel!","Get lost, will you? Half the garrison is after you!")+"","Every town guard is looking for you. I'm not a fool to provide services to you at this moment ...","You have nothing to do here!"),LinkRandPhrase(""+GetSexPhrase("Just dare to touch my girls and I will skin you alive!","Get lost, you creep!")+"","Dirty"+GetSexPhrase("","")+" Murderer, leave my establishment, now! Guards!!!","I am not afraid of you, "+GetSexPhrase("scoundrel","rat")+"! Soon you will be hanged in our fort, you won't get far..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Heh, an alarm is never a problem for me...","They will never catch me."),RandPhraseSimple("Just shut up, you stupid crone.","Shut up if you don't want any trouble..."));
				link.l1.go = "exit";
				break;
			}
			//--> Мерзкий Божок
			if (CheckAttribute(pchar, "questTemp.ChickenGod.HostessDialog")) {
				dialog.text = "Oh, my God! How did you get in here? Dear captain, please leave – I beg you! Our establishment is currently closed!";
				link.l1 = "Good to see you, dear "+npchar.name+". I was on the guest list. However, in such establishments, even guests have to pay, so... Please don't make this too difficult for me, but I want to pay for a room.";
				link.l1.go = "chicken_god";
				
				DeleteAttribute(pchar, "questTemp.ChickenGod.HostessDialog");
				break;
			}
			//<-- Мерзкий Божок
			//--> туториал Мартиника
			if (CheckAttribute(pchar, "questTemp.Sharlie.Gigolo") && pchar.questTemp.Sharlie.Gigolo == "start" && npchar.location == "FortFrance_SecBrRoom")
			{
				DelLandQuestMark(npchar);
				link.l1 = "Listen, Aurora, I need a girl for the night. And I want to take her home with me. Can you arrange that?";
                link.l1.go = "Gigolo";
				break;
			}
			//<-- туториал Мартиника
			//Jason --> Заносчивый аристократ
			if (!CheckAttribute(pchar, "GenQuest.Badboy") && !CheckAttribute(npchar, "quest.Badboy") && !CheckAttribute(pchar, "questTemp.ZA.Block") && makeint(environment.time) > 15.0 && makeint(environment.time) < 21.0 && sti(pchar.questTemp.HorseQty) > 4)
			{
				dialog.text = "You're such a distinguished man. Moreover, my girls like you very much. I would like to ask you for a small favour for my establishment.";
				link.l5 = "I am flattered, that's for certain. What is it that you need my help with?";
				link.l5.go = "Badboy";
				link.l8 = "I am sorry, but I am busy at the moment.";
				link.l8.go = "exit";
				npchar.quest.Badboy = "true";
				break;
			}
			
			if (CheckAttribute(pchar, "GenQuest.Badboy.Complete") || CheckAttribute(pchar, "GenQuest.Badboy.Continue"))
			{
				if (npchar.City == pchar.GenQuest.Badboy.Brothel.City)
				{
					dialog.text = "Oh, you have returned! Have you arranged for that "+pchar.GenQuest.Badboy.Brothel.Name+" to leave my girls alone?";
					link.l5 = "Yes. He won't show his face here anymore.";
					link.l5.go = "Badboy_complete";
				break;
				}
			}
			// <-- Заносчивый аристократ
			
			//--> Jason Португалец
			if (CheckAttribute(pchar, "questTemp.HWIC.Detector") || SandBoxMode)
			{
				bool bOk = (pchar.questTemp.HWIC.Detector == "holl_win") || (pchar.questTemp.HWIC.Detector == "eng_win") || (pchar.questTemp.HWIC.Detector == "self_win") || SandBoxMode;
				if (!CheckAttribute(pchar, "questTemp.Portugal") && bOk && !CheckAttribute(npchar, "quest.Portugal") && npchar.location == "Marigo_SecBrRoom" && makeint(environment.time) > 6.0 && makeint(environment.time) < 22.0)
				{
					DelMapQuestMarkCity("marigo");
					DelLandQuestMark(npchar);
					dialog.text = "Captain, may I ask you a favor?";
					link.l5 = "For you, madam, anything you like! I am at your service!";
					link.l5.go = "Portugal";
					link.l8 = "I am sorry, but I am busy at the moment.";
					link.l8.go = "exit";
					npchar.quest.Portugal = "true";
					DelLandQuestMark(npchar);
					break;
				}
			}
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "HostressMoney" && npchar.location == "Marigo_SecBrRoom")
			{
				DelLandQuestMark(npchar);
				dialog.text = "Have you spoken with Hugo, mynheer Captain?";
				if (sti(pchar.money) >= 10000)
				{
					link.l1 = "Moreover, ma'am, here is your money. Everything went in the most favourable way...";
					link.l1.go = "Portugal_3";
				}
				else
				{
					link.l1 = "Yes, I conveyed your request to him.";
					link.l1.go = "Portugal_exit";
				}
				break;
			}
			//<--Португалец
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "brothel" && npchar.location == "Tortuga_SecBrRoom")
			{
				dialog.text = "Oh my, look at this! Charlie Prince, the famous corsair! In the flesh!";
				link.l1 = RandSwear()+"Hello, Janette. I am here on a mission for Marcus Tyrex.";
				link.l1.go = "mtraxx_R";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "brothel_repeat" && npchar.location == "Tortuga_SecBrRoom")
			{
				dialog.text = "Are you ready for an unforgettable restorative treatment, my brave corsair?";
				if (sti(pchar.money) >= 31000)
				{
					link.l1 = "I am! Charlie Prince doesn't waste words like he wastes money, ha-ha!";
					link.l1.go = "mtraxx_R2";
				}
				else
				{
					link.l1 = "Almost... I think I have lost my purse in your establishment... I will be back with money!";
					link.l1.go = "exit";
				}
				break;
			}
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = RandPhraseSimple(TimeGreeting()+". Welcome to my house of love. My name is "+npchar.name+", and I am the proprietor. "+GetSexPhrase("What can I do for you, "+GetAddress_Form(NPChar)+"?","Frankly, I'm a bit surprised to see you here, "+GetAddress_Form(NPChar)+", but I assure you that we provide services not only for men.")+"",TimeGreeting()+". I welcome you, "+GetSexPhrase("stranger","young lady")+", to my humble establishment. Allow me to introduce myself, I am "+NPChar.Name+" - keeper of this refuge for men hungry for a woman's touch. "+GetSexPhrase("What can I do for you?","Although we have a thing or two for the ladies, too...")+"");
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = RandPhraseSimple(TimeGreeting()+". How can I help you, "+GetAddress_Form(NPChar)+"?",TimeGreeting()+". What can I do for you, "+GetAddress_Form(NPChar)+"?");
			}
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Gigolo"))//не идёт квест девочки
			{
				if (!CheckAttribute(pchar, "GenQuest.BrothelLock"))// нет запрета от Мэри 280313
				{
					link.l2 = npchar.name+", I want to spend some quality time with one of your girls.";
					link.l2.go = "Hostess_1";
				}
			}
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock")) // не идёт старт Шарля
			{
				if (sti(pchar.ship.type) != SHIP_NOTUSED && GetCrewQuantity(pchar) > 0) // Rebbebion - а смысл, если нет как корабля, так и команды?
				{
					link.l3 = "It's been a while since I last treated my men. Can I make a bulk order of girls for my crew?";
					link.l3.go = "ForCrew";
				}
			}
			link.l4 = "I have a question.";
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakBrothelMadam"))
			{
				if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
				{
					link.l4.go = "ShipLetters_1";// генератор  "Найденные документы"
				}
				else
				{
					link.l4.go = "quests";
				}	
			}
			else
			{
				link.l4.go = "quests";//(перессылка в файл города)
			}	
			//-->> квест поиска кольца мэра
			if (pchar.questTemp.different == "TakeMayorsRing" && pchar.questTemp.different.TakeMayorsRing.city == npchar.city && GetNpcQuestPastDayWOInit(npchar, "TakeMayorsRing") > 7)
			{
				link.l5 = "Listen, "+npchar.name+", I am looking for the governor's ring. He stayed at your establishment and probably lost it here.";
				link.l5.go = "TakeMayorsRing_H1";
				SaveCurrentNpcQuestDateParam(npchar, "TakeMayorsRing");
			}
			//<<-- квест поиска кольца мэра

			// belamour ночной приключенец -->
			if(CheckAttribute(pchar, "GenQuest.NightAdventureVar") && pchar.GenQuest.NightAdventureVar == "NightAdventure_NobleWhoreMoney")
			{
				link.l8 = "Look, I would like to take the finest girl you have.";
				link.l8.go = "NA_Girl";
			}
			// <-- приключенец
			link.l9 = "Never mind, I am already leaving.";
			link.l9.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "ShipLetters_1":
				pchar.questTemp.different.GiveShipLetters.speakBrothelMadam = true;
				dialog.text = RandPhraseSimple("What do you want, handsome?","I am listening to you, Captain.");
				link.l1 = "Listen, "+npchar.name+", I found these papers in a private room of your institution ...";
				link.l1.go = "ShipLetters_2";				
		break;
		
		case "ShipLetters_2":
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Let me see! Hmm... some captain lost his documents, right? I think you should ask the harbour master about this.";
				link.l1 = "Perhaps, perhaps...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Let me take a look! Oh! Judging by the name, they belong to my esteemed customer and a worthy citizen of our town. I can hand these documents to him myself.";
				link.l1 = "Probably not...";
				link.l1.go = "exit";
				link.l2 = "Excellent! Always glad to help a good person and a worthy establishment.";
				link.l2.go = "ShipLetters_3";										
			}	
		break;
		
		case "ShipLetters_3":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "2");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters"); 
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "Hostess_1":
			if (!CheckAttribute(npchar, "quest.selected"))
			{
				if (CheckNPCQuestDate(npchar, "quest.date"))
				{
					dialog.text = ""+GetSexPhrase("We're always happy to serve a customer. Now tell me, handsome – have you already picked anyone, or do you not much care?","Well, my girls are certainly able to... help you. Have you already picked anyone, or do you not much care?")+"";
					Link.l1 = ""+GetSexPhrase("Heh, I just need a whore and I need her right now. I don't care which one, your girls all look good to me...","Anyone will be fine if she knows her duties, of course...")+"";
					Link.l1.go = "Hostess_NotChoice";	
					Link.l2 = "Yes, there is one, "+GetSexPhrase("who caught my fancy...","she would be the nicest...")+"";
					Link.l2.go = "Hostess_Choice";
				}
				else
				{
					dialog.text = "I have no free girls for you today, we already have too many customers. Come back tomorrow, and you won't regret it!";
					Link.l1 = "Pity, I'd just begun to enjoy it.";
					Link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Hmm. You've already paid for the girl. Please, don't distract me.";
				Link.l1 = "Alright, I'm coming.";
				Link.l1.go = "exit";	
			}
		break;

        case "Hostess_NotChoice":
			sld = GetFreeHorseRef(npchar.city);
			location = &locations[FindLocation(npchar.city + "_Brothel")];
			if (sld.id == "none" || GetNpcQuestPastDayParam(location, "Brothel_date") > 98)
			{
				dialog.text = "I don't have any free girls right now, you'll have to check back in a couple of days.";
				Link.l1 = "Fine, as you say.";
				Link.l1.go = "exit";	
			}
			else
			{
				// belamour legendary edition Орден Святого Людовика -->
				if(IsEquipTalisman9() && npchar.nation == FRANCE)
				{
					dialog.text = ""+GetSexPhrase("Well, stallion, that's excellent!","I have them all skilled, you can be sure.")+"I can offer a beautiful girl named "+GetFullName(sld)+", she's free now.\nOh, what's this you're hiding so modestly there?! Is that the highest award in France? Rumour has it that the bearers of this insignia are legendary not only on the battlefield... Well, you know what I mean, my filibuster... Besides, anyone would consider it an honour to touch your 'Order', so tonight you rest at the expense of my establishment. Refusals are not accepted, handsome.";
					Link.l1 = "Of course I agree, what questions could there be?!";
					Link.l1.go = "Hostess_NotChoice_agree";	
					npchar.quest.choiceIdx = sld.index;
					break;
				}
				// <-- legendary edition
				dialog.text = ""+GetSexPhrase("Well, excellent, my stallion!","They are all very skilled at what they do, have no doubt.")+" I can offer you a very lovely girl, her name is "+GetFullName(sld)+", and she is available at the moment. That pleasure will cost you "+FindRussianMoneyString(sti(sld.quest.price)+charWhoreCost)+". Agree?";
				Link.l1 = "No. I suppose not. It's too expensive...";
				Link.l1.go = "exit";
				if (sti(pchar.money) >= (sti(sld.quest.price) + charWhoreCost))
				{
					Link.l2 = "Of course, how could I refuse?!";
					Link.l2.go = "Hostess_NotChoice_agree";	
					npchar.quest.choiceIdx = sld.index;
				}
				else
				{
					Link.l1 = "Oh blast, I don't have that much money with me...";
					Link.l1.go = "exit";
				}
			}
		break;
		
        case "Hostess_NotChoice_agree":
			sld = &characters[sti(npchar.quest.choiceIdx)];
			if (sti(pchar.money) >= (sti(sld.quest.price) + charWhoreCost))
			{
				dialog.text = "Fine, "+GetSexPhrase("handsome","beautiful")+". "+sld.name+" will be waiting for you in a private room on the second floor.";
				Link.l1 = ""+GetSexPhrase("Fine, I'm coming, then","Fine, I'm coming, then")+"...";
				Link.l1.go = "exit";
				// belamour legendary edition деньги только без ордена или адмиральского мундира
				if(IsEquipTalisman9())
				{
					if(npchar.nation != FRANCE) AddMoneyToCharacter(pchar, -(sti(sld.quest.price) + charWhoreCost));
				}
				else
				{
					AddMoneyToCharacter(pchar, -(sti(sld.quest.price) + charWhoreCost));
				}
				sld.dialog.currentnode = "Horse_ReadyFack";			
				//--> таймер на возврат, чтобы не вечно ждали
				str = npchar.city;
				pchar.quest.(str).win_condition.l1            = "Timer";
				pchar.quest.(str).win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
				pchar.quest.(str).win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
				pchar.quest.(str).win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
				pchar.quest.(str).win_condition               = "Brothel_checkVisitTime";	
				pchar.quest.(str).HorseId = sld.id;
				pchar.quest.(str).locator = sld.location.locator;
				//<-- таймер на возврат, чтобы не вечно ждали
				ChangeCharacterAddressGroup(sld, npchar.city + "_Brothel_room", "goto", "goto"+(rand(2)+1));
				LocatorReloadEnterDisable(npchar.city + "_Brothel", "reload2_back", false); //открываем комнату
				npchar.quest.selected = true; //флаг взял девку у хозяйки
				SetNPCQuestDate(npchar, "quest.date"); //дату взятия запишем
				for(int n=0; n<MAX_CHARACTERS; n++)
				{
					makeref(sld, Characters[n]);
					if (sld.location == npchar.city+"_Brothel" && CheckAttribute(sld, "CityType") && sld.CityType == "horse")
					{
						sld.dialog.currentnode = "Horse_4";
					}
				}
				
				// генератор найденных бумаг
				
				// belamour legendary edition не давать квесты губернатору и адмиралу
				bool MCGovernon = CheckAttribute(pchar, "questTemp.Patria.GenGovernor");
				bool MCAdmiral = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4;
				
				if ((rand(4) == 1) && (pchar.questTemp.different == "free") && (!CheckCharacterItem(pchar, "CaptainBook")) && GetNpcQuestPastDayWOInit(npchar, "questShipLetters") > 10 && !MCGovernon && !MCAdmiral ) 
				{					
					pchar.questTemp.different = "GiveShipLetters";
					pchar.questTemp.different.GiveShipLetters = "toBrothel";
					pchar.questTemp.different.GiveShipLetters.Id = GetFullName(npchar);
					pchar.questTemp.different.GiveShipLetters.city = npchar.city;	
					pchar.questTemp.different.GiveShipLetters.variant = rand(2);
					p1 = rand(20 - MOD_SKILL_ENEMY_RATE) + 1; // даем хотя бы один день
					s1 = rand(80 - pchar.rank - p1) * 50 + rand(100);
					s2 = s1 * 2;
					s3 = s1 * rand(GetCharacterSPECIAL(pchar, "Luck")) + s1;
					s4 = s2 + s3;
					s5 = s4 * GetCharacterSPECIAL(pchar, "Charisma");
					pchar.questTemp.different.GiveShipLetters.price1 = s1;
					pchar.questTemp.different.GiveShipLetters.price2 = s2;
					pchar.questTemp.different.GiveShipLetters.price3 = s3;
					pchar.questTemp.different.GiveShipLetters.price4 = s4;
					pchar.questTemp.different.GiveShipLetters.price5 = s5;
										
					sld = ItemsFromID("CaptainBook");
					sld.CityName = XI_ConvertString("Colony" + npchar.city + "Gen");
					//ложим бумаги в итем								
					sTemp = "_Brothel_room";	
					sTemp1 = "_town";					
					sld.shown = true;
					sld.startLocation = pchar.questTemp.different.GiveShipLetters.city + sTemp;
					sld.startLocator = "item" + (rand(4)+1);
					sld.endLocation = pchar.questTemp.different.GiveShipLetters.city + sTemp1;
					pchar.questTemp.different.GiveShipLetters.item = true; //флаг -  бумаги валяются в итемах
					Log_QuestInfo("The papers are in location " + sld.startLocation + ", in locator " + sld.startLocator + " p1 : " + p1);
					
					pchar.quest.CheckShipLetters.win_condition.l1 = "location";
					pchar.quest.CheckShipLetters.win_condition.l1.location = sld.endLocation;
					pchar.quest.CheckShipLetters.function = "CheckShipLetters";
					
					SetTimerFunction("GiveShipLetters_null", 0, 0, p1); //освобождаем разрешалку на миниквесты 
					SaveCurrentNpcQuestDateParam(npchar, "questShipLetters");					
				}
				// генератор - "Повод для спешки"
				if((rand(5) == 2) && !CheckAttribute(pchar, "questTemp.ReasonToFast") && GetNpcQuestPastDayWOInit(npchar, "questReasonToFast") > 20 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && !MCGovernon && !MCAdmiral) // Addon-2016 Jason
				{
					iColony = FindColony(npchar.city);	
					if( sti(Colonies[iColony].HeroOwn) == false && npchar.city != "Panama" && npchar.city != "Charles")
					{
						pchar.questTemp.ReasonToFast = "Begin";
						pchar.questTemp.ReasonToFast.city = npchar.city;
						sTemp1 = "_town";					
						pchar.quest.CheckReasonToFast.win_condition.l1 = "location";
						pchar.quest.CheckReasonToFast.win_condition.l1.location = npchar.city + sTemp1;
						pchar.quest.CheckReasonToFast.function = "ReasonToFast_CheckHorse";
						SaveCurrentNpcQuestDateParam(npchar, "questReasonToFast");	
					}	
				}				
			}
			else
			{
				dialog.text = "Oh, you see, the problem is that "+sld.name+" is not a cheap girl, her price is "+FindRussianMoneyString(sti(sld.quest.price)+charWhoreCost)+". And I see that you just can't afford her at the moment. Come back when you're wealthy"+GetSexPhrase(", dear","")+"...";
				Link.l1 = "That's my luck...";
				Link.l1.go = "exit";
			}
		break;

        case "Hostess_Choice":
			dialog.text = "I am always happy when girls and customers develop warm feelings for each other... Tell me her name.";
			Link.l1.edit = 9;
			Link.l1 = "";
			Link.l1.go = "Hostess_Choice_1";	
		break;
		
        case "Hostess_Choice_1":
			sld = CheckHorsesName(npchar.city, 9);
			if (sld.id == "none")
			{
				dialog.text = "Hmm... you must be mistaken. I have no such girl in my establishment. Perhaps you got her name wrong.";
				Link.l1 = "Hmm... but I just spoke with her.";
				Link.l1.go = "Hostess_Choice_2";				
				Link.l2 = "Perhaps. It would be better to ask her name once again, just to be sure. I'll talk to you about this later.";
				Link.l2.go = "exit";	
			}
			else
			{
				dialog.text = GetFullName(sld)+", you're talking about her?";
				Link.l1 = "Yeah, about her.";
				Link.l1.go = "Hostess_NotChoice_agree";				
				Link.l2 = "No, it's not her.";
				Link.l2.go = "Hostess_Choice_2";
				npchar.quest.choiceIdx = sld.index;
			}
		break;
		
        case "Hostess_Choice_2":
			dialog.text = "Then perhaps you should tell me her name once again, and maybe I'll realise who you are talking about.";
			Link.l1.edit = 9;
			Link.l1 = "";
			Link.l1.go = "Hostess_Choice_1";
			Link.l2 = "Perhaps. It would be better to ask her name once again, just to be sure. I'll talk to you about this later.";
			Link.l2.go = "exit";	
		break;
		//==> команда
		case "ForCrew":
			dialog.text = "Hmm... Want to help your men 'let off some steam'? You see, this establishment of mine is a reputable one, and I have the best girls around. But I know several port wenches, and they'll be happy to please all your sailors. That will cost you "+FindRussianMoneyString(GetCrewQuantity(pchar)*crewWhoreCost)+".";			
			link.l1 = "Fine, I agree.";
			link.l1.go = "ForCrew_1";
			link.l2 = "Guess they can manage without it...";
			link.l2.go = "exit";
		break;
		
		case "ForCrew_1":
		    if (sti(Pchar.money) >= GetCrewQuantity(pchar)*crewWhoreCost && GetCrewQuantity(pchar)>0)
		    {
		        AddMoneyToCharacter(Pchar, -makeint(GetCrewQuantity(pchar)*crewWhoreCost));
	            AddCrewMorale(Pchar, 10);
				ChangeCharacterComplexReputation(pchar,"authority", 1);
	            LAi_Fade("", "");
                AddTimeToCurrent(5 + rand(1), rand(30));
			    DialogExit();
		    }
		    else
		    {
		        dialog.text = "It's not my business, but I think that first you should earn enough money to hire a crew, and only then worry about its spirit.";
			    link.l1 = "You're probably right...";
			    link.l1.go = "exit";
		    }
		break;
		
		case "Woman_FackYou":
			dialog.text = "Dear, just what are you doing?! And you looked like a decent captain... You won't 'fly' away this time, handsome. The guards will clip your wings...";
			link.l1 = "Shut up, old hag.";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		
		//поиски кольца губернатора
		case "TakeMayorsRing_H1":
			dialog.text = "I haven't found any ring.";
			link.l1 = "And your girls?";
			link.l1.go = "TakeMayorsRing_H2";
		break;
		
		case "TakeMayorsRing_H2":
			dialog.text = "They have not either. If a customer forgets or loses anything, my girls bring it to me. But no one has brought me the governor's ring.";
			link.l1 = "I see... But could it be that they decided to keep it for themselves?";
			link.l1.go = "TakeMayorsRing_H3";
		break;
		
		case "TakeMayorsRing_H3":
			dialog.text = "Unlikely. The girls are allowed to keep gifts from the customers, but that's all.";
			link.l1 = "I see. Well, thank you, "+npchar.name+".";
			link.l1.go = "exit";
		break;
		
		case "Hostess_inSexRoom":
			dialog.text = "Oh, there you are...";
			link.l1 = "Here I am, my lady!";
			link.l1.go = "exit";
			pchar.quest.SexWithHostess_null.over = "yes"; //нулим таймер на не пришёл
			NextDiag.TempNode = "First time";
			if (CheckAttribute(pchar, "questTemp.RomNaTroih_Pogovoril"))
			{
				sld = CharacterFromID(pchar.RomNaTroih_Shluha);
				dialog.text = ""+sld.name+"! My hero, I see you didn't waste your time downstairs!";
				link.l1 = "I hope you will forgive me this weakness, my queen?";
				link.l1.go = "RomNaTroih_2";
			}
			AddDialogExitQuestFunction("SexWithHostess_fack");
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			DeleteAttribute(pchar, "questTemp.RomNaTroih");
            if(IsEquipCharacterByArtefact(pchar, "totem_03")) 	
			{
				AddCharacterHealth(pchar, 10);
				AddCharacterMaxHealth(pchar, 1.0);
			}
			else AddCharacterHealth(pchar, 5);
		break;
		
		// ================================== рядовой состав =======================================
        case "Horse_talk":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("You'd better leave the establishment!","All the guards in town are looking for you! You'd best leave...","You've made a mess and now you show up here?! No, not this time..."),LinkRandPhrase("Get lost!","Filthy murderer, get out of here! Guards!","I am not afraid of you,"+GetSexPhrase("scoundrel","rat")+"! Soon you will be hanged in our fort, you won't get far..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Heh, an alarm is never a problem for me...","They will never catch me."),RandPhraseSimple("Heh, what a foolish wench you are...","Shut your mouth, whore, or I'll shut it with something else..."));
				link.l1.go = "exit";
				break;
			}
			dialog.text = NPCStringReactionRepeat("Hello, "+GetAddress_Form(NPChar)+""+GetSexPhrase("",", hee-hee...")+". You need to see the señora and fill out the order.","You again? Please speak with the keeper. She's in her office.","Look, "+GetAddress_Form(NPChar)+""+GetSexPhrase(", I do hope that you are as stubborn in other matters as you are in talking... Again","Once again")+" I ask you to see the proprietor of the establishment.","Oh, "+GetAddress_Form(NPChar)+""+GetSexPhrase(", aren't you a stubborn one!",", Hee-hee... You're a stubborn one, aren't you?")+" You need to see the señora and fill out the order.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Alright, "+GetSexPhrase("beauty, ","")+"I got it"+GetSexPhrase("","")+".","Yeah, right...",""+GetSexPhrase("Have no doubt, my pretty, I am as stubborn and strong as a bull!","Yeah, yeah...")+"",""+GetSexPhrase("Oh hell, I must have missed something... I'm sorry, dear.","Fine, alright.")+"",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			Link.l2 = "And where is she?";
			Link.l2.go = "Horse_1";
			Link.l3 = LinkRandPhrase(""+GetSexPhrase("Oh, beauty, I could drown in those eyes of yours...","You look beautiful, darling!")+"",""+GetSexPhrase("You know, I've never met such a beautiful woman before!","You know, I've never met such a lovely lady before!")+"",""+GetSexPhrase("Darling, you look beautiful.","Damn, I was so tired of all those yokels... And you're so charming!")+"");
			if (!CheckAttribute(npchar, "quest.choice"))
			{
				Link.l3.go = "Horse_2";
			}
			else
			{
				Link.l3.go = "HorseChoice_" + npchar.quest.choice;
			}
			//-->> квест поиска кольца мэра
			if (pchar.questTemp.different == "TakeMayorsRing" && pchar.questTemp.different.TakeMayorsRing.city == npchar.city && GetNpcQuestPastDayWOInit(npchar, "TakeMayorsRing") > 7)
			{
				link.l5 = LinkRandPhrase("Listen, "+GetSexPhrase("beauty","deary")+", have you by any chance found a wedding ring here? Someone seems to have lost it...","Darling, have you seen a wedding ring or anything like that around?","Listen, "+GetSexPhrase("my kitty","babe")+", haven't you seen a wedding ring around here?");
				link.l5.go = "TakeMayorsRing_S1";
				SaveCurrentNpcQuestDateParam(npchar, "TakeMayorsRing");
			}
			//<<-- квест поиска кольца мэра
			
			// Addon 2016-1 Jason пиратская линейка
			if (pchar.location == "santodomingo_brothel" && CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_1" && npchar.id == "HorseGen_"+reload_location_index+"_2")
			{
				link.l6 = "Hey there, sweetheart. Marcus Tyrex sent me, take a look at this amber necklace...";
				link.l6.go = "mtraxx";
			}
			NextDiag.TempNode = "Horse_talk";
		break;
		
        case "Horse_1":
			dialog.text = "She's in her office. You can get there from here through the door opposite the exit to the street, or from the street on the other side of the house. Her name is "+characters[GetCharacterIndex(npchar.city+"_Hostess")].name+".";
			Link.l1 = "I see. "+GetSexPhrase("sweetheart","darling")+", thank you.";
			Link.l1.go = "exit";			
		break;
		
        case "Horse_2":
			if (rand(1))
			{
				dialog.text = LinkRandPhrase("Oh my, it's so nice to hear such things! Hey, I'm free at the moment, so if you pick me, you won't regret it...","You really think so? You know, that's so sweet... Listen, I'm free at the moment, so you can pick me."+GetSexPhrase(" I promise you a sea of love and an ocean of caresses...","")+"",""+GetSexPhrase("Do you think so? Oh, I am truly flattered. You know, I rarely hear such compliments...","Oh, girl... if you only knew how fed up I am with rednecks...")+" Hey, listen, I'm free at the moment, so you can choose me to make you happy. I won't disappoint you, I promise...");
				if (CheckAttribute(pchar, "questTemp.RomNaTroih") && !CheckAttribute(pchar, "questTemp.RomNaTroih_Pogovoril"))
				{
					link.l1 = "My dear, that's exactly what I was going to do! How fortunate that your hostess has already arranged a private meeting with me upstairs. Care to join?";
					Link.l1.go = "RomNaTroih_1";
					pchar.questTemp.RomNaTroih_Pogovoril = true;
					break;
				}
				link.l1 = "Well, I'll pick you, then!";
				Link.l1.go = "Horse_3";		
				Link.l2 = ""+GetSexPhrase("No, that was just a compliment for a lovely lady","That was just a compliment")+".";
				Link.l2.go = "exit";
				npchar.quest.choice = 0; //был базар, но ГГ потом отказался
			}
			else
			{
				dialog.text = LinkRandPhrase(""+GetSexPhrase("You know what I say, sweetie? I don't need this cheap talk. Do business or leave!","That's all I needed! Compliments from women!")+"",""+GetSexPhrase("Are you one of those who think women love with their ears? Well, dear, that's just not true. If you want me, then pay the madame and spare me your empty words.","Lass, don't waste yourself on empty talk. If you mean business - then pay...")+"",""+GetSexPhrase("Oh, another lover of pleasure... You just pay and I am yours. It's all that simple, without all this gentle nonsense!","What's wrong with you, darling? If you want to indulge yourself in pleasures, then just pay and stop all that nonsense!")+"");
				link.l1 = "Oh, what a grip!";
				Link.l1.go = "exit";
				npchar.quest.choice = 2; //ГГ послали
			}
		break;
		
        case "Horse_3":
			dialog.text = characters[GetCharacterIndex(npchar.city+"_Hostess")].name+" completes all formalities in her office. Go see her"+GetSexPhrase(", my hero,","")+" and say my name - "+npchar.name+". I'll be waiting for you...";
			Link.l1 = "I see, darling, I'll be back soon...";
			Link.l1.go = "exit";
			npchar.quest.choice = 1; //она согласная
			SetNPCQuestDate(npchar, "quest.choice");
		break;
		
        case "Horse_4": 
			dialog.text = NPCStringReactionRepeat("You have already paid.","I told you to go upstairs.","Upstairs, young man.","Some people think so slowly...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Yeah, I know.","I remember.","Oh, don't repeat yourself, I remember.","Hmm, what do you mean?",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "Horse_4";
		break;
		
		//===>> реакция на попытки пофлиртовыть, если флирт уже был
        case "HorseChoice_0": 
			if (!CheckAttribute(npchar, "quest.sexHappend"))
			{
				dialog.text = NPCStringReactionRepeat("I just don't quite understand you."+GetSexPhrase(" First you pay compliments, and then you go back on your word. What a strange sort...","")+"","Compliments again?","The keeper is in her office. Got it?","We aren't supposed to insult our customers, but you're really asking for it"+GetSexPhrase("","")+"...","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("It just happened the way it did...","Alright, I'll do that.","Yeah, I got it.","Beg your pardon, my love.",npchar,Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Thanks for the compliment. If you want to take me, just go and see the madam. Business as usual.";
				Link.l1 = "I see.";
				Link.l1.go = "exit";
			}
		break;
		
        case "HorseChoice_1": 
			if (!CheckAttribute(npchar, "quest.sexHappend"))
			{
				if (!CheckNPCQuestDate(npchar, "quest.choice"))
				{
					dialog.text = NPCStringReactionRepeat(""+GetSexPhrase("Dear, we've already talked it all over. ","")+"Don't make me wait too long...",""+GetSexPhrase("Hmm... Listen, dear, I","I")+" I find your words very nice and all, but could you get down to business...","Perhaps you will discuss this with madame, won't you?","Hmm... I don't even know what to say...","block",1,npchar,Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("I would never do that, wait for me!","Certainly!","Of course, as you say!","I am already running to see your madam...",npchar,Dialog.CurrentNode);
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "I was waiting for you, but you didn't come to take me... I can't say I liked that...";
					Link.l1 = "You see, it just happened the way it did...";
					Link.l1.go = "exit";
					npchar.quest.choice = 0; //был базар, но ГГ потом отказался
				}
			}
			else
			{
				dialog.text = "Oh, it's you again, my "+GetSexPhrase("glorious corsair","pretty lass")+"! If you want me again, come see the madam, you won't be disappointed..."+GetSexPhrase(" By the way, I recognized you, dear, but we've been told we must treat all customers equally. There shouldn't be any favourites, sorry about that...","")+"";
				Link.l1 = "Don't worry, darling. Just wait for me a little longer, "+GetSexPhrase("cutie","cutie")+", and soon we'll meet in private again.";
				Link.l1.go = "exit";
				Link.l2 = "It's very sweet that you remember me, but I cannot spend this night with you, sorry.";
				Link.l2.go = "HorseChoice_1_Add";
			}
		break;
		
        case "HorseChoice_2": 
			if (!CheckAttribute(npchar, "quest.sexHappend"))
			{
				dialog.text = NPCStringReactionRepeat("So,"+GetSexPhrase(" dear friend,","")+" you'd better be engaged in business. It's more useful than doing nothing.",""+GetSexPhrase("Hmm, why are you ","Why are you")+" saying the same things over and over again?","Hey, isn't that enough?!","Hm, what a surprise, nothing new"+GetSexPhrase(", once again with all those foolish attempts at charm! If you want to have sex with me, go and see the madame, you featherbrain!","...")+"","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Yeah, I've heard"+GetSexPhrase("","")+" you...","Hmm, that's how it turns out...","Hmm, maybe that's enough, or maybe not...","Watch your tongue"+GetSexPhrase(", goat","")+"...",npchar,Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Oh, it's you again! "+GetSexPhrase("And once again, all those stupid compliments. Nothing ever changes in this world... If ","Just a reminder: if ")+"you want to"+GetSexPhrase("have a good time","have a good time")+" with me, pay the owner of the establishment. I couldn't care less about your words.";
				Link.l1 = "That's not a big surprise...";
				Link.l1.go = "exit";
			}
		break;
		
        case "HorseChoice_1_Add":
			dialog.text = "I can't say it made me happy... A pity.";
			Link.l1 = "I am sorry...";
			Link.l1.go = "exit";
			npchar.quest.choice = 0;
		break;
		
		//===>> секс
        case "Horse_ReadyFack":
			// Addon 2016-1 Jason пиратская линейка
			if (pchar.location == "SantoDomingo_Brothel_room" && CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_2" && npchar.name == "Gabriela")
			{
				dialog.text = "Ah, you've finally arrived! Excellent! We can speak freely, nobody's listening...";
				Link.l1 = "So, it was the Spaniard who gave you the blue amber?";
				Link.l1.go = "mtraxx_2";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("SantoDomingo");
				break;
			}
			if (!CheckAttribute(npchar, "quest.choice")) npchar.quest.choice = 0;
			switch(npchar.quest.choice)
			{
				case "0":
					dialog.text = RandPhraseSimple("I am very happy to see you. "+GetSexPhrase("So, what are we going to do next?","How about we enjoy ourselves?")+"","Don't be shy"+GetSexPhrase(", make yourself at home for at least two hours.",". I'll be able to entertain you, have no doubt.")+"");
					Link.l1 = RandPhraseSimple("I don't think it will be boring...",""+GetSexPhrase("Let's have a good time, baby!","Let's waste no time!")+"");
				break;
				case "1":
					dialog.text = "Oh, it's you again, my "+GetSexPhrase("Glorious corsair! I promised you something and I am ready to keep my word","Pretty lass! You will never forget the next two hours")+"...";
					Link.l1 = "Now that sounds tempting...";	
				break;
				case "2":
					dialog.text = "Oh, there you are at last. Let's waste no time!";
					Link.l1 = ""+GetSexPhrase("Let's not, coward...","Now show me what you can do...")+"";
				break;
			}
			if (pchar.sex == "woman")
			{
				Link.l1.go = "exit";
				NextDiag.TempNode = "Horse_AfterSex";
				AddDialogExitQuest("PlaySex_1");
				// кач от борделя
				if (CheckNPCQuestDate(pchar, "BrothelSex"))
				{
					if(IsEquipCharacterByArtefact(pchar, "totem_03")) 	AddCharacterHealth(pchar, 10);
					else 												AddCharacterHealth(pchar, 5);
					SetNPCQuestDate(pchar, "BrothelSex");
				}
				// изменение статусов
				ChangeCharacterComplexReputation(pchar,"nobility", -1);
				AddCharacterExpToSkill(pchar, "Leadership", 30);
				AddCharacterExpToSkill(pchar, "FencingS", -15);
				AddCharacterExpToSkill(pchar, "Pistol", -15);
			}
			else
			{
				pchar.horsekiss = npchar.id;
				Link.l1.go = "Horse_Kiss";
			}
			//--> кол-во посещений
			if (!CheckAttribute(npchar, "quest.sexHappend")) npchar.quest.sexHappend = 1;
			else npchar.quest.sexHappend = sti(npchar.quest.sexHappend) + 1;
			pchar.GenQuest.BrothelCount = sti(pchar.GenQuest.BrothelCount) + 1; // для Данек
			Achievment_SetStat(23, 1);
			//<-- кол-во посещений
			str = npchar.city;
			pchar.quest.(str).win_condition.l1 = "ExitFromLocation";
			pchar.quest.(str).win_condition.l1.location = pchar.location;
			pchar.quest.(str).win_condition = "Brothel_checkVisitTime";
			pchar.questTemp.HorseQty = sti(pchar.questTemp.HorseQty) + 1; //счетчик
		break;
		
		case "Horse_Kiss":
			DialogExit();
			
			StartQuestMovie(true, false, true);
			LAi_SetActorType(pchar);
			LAi_Fade("Horse_Kiss", "");
		break;

        case "Horse_AfterSex":
			if (CheckAttribute(pchar, "questTemp.ReasonToFast") && pchar.questTemp.ReasonToFast == "Begin")
			{
				dialog.text = "Captain, why are you so silent?";
				link.l1 = LinkRandPhrase("Well, that's me.","We'll talk next time.",RandPhraseSimple("I'm not paying you to talk.","But you, "+GetSexPhrase("beauty","deary")+", weren't so quiet all that time."));
				link.l1.go = "exit";
				link.l2 = ""+GetSexPhrase("You were simply amazing, I nearly lost my mind! It's a rare thing to find a woman who is both so beautiful and alluring","Oh, you certainly know how to please a woman... I am so excited.")+".";
				link.l2.go = "Horse_ReasonToFast_1";
			}
			else
			{
				switch(npchar.quest.choice)
				{
					case "0":
						dialog.text = LinkRandPhrase("Did you like it?","So, what do you think? Was everything alright?","So,"+GetSexPhrase(" corsair, is, everything"," everything")+" Fine?");
						Link.l1 = RandPhraseSimple(""+GetSexPhrase("Of course, everything is fine","You certainly know your duties")+".",""+GetSexPhrase("Everything's fine, darling","You know, I was quite pleased")+".");
						Link.l1.go = "exit";
					break;
					case "1":
						dialog.text = LinkRandPhrase("So, did I keep my promise?","So,"+GetSexPhrase(" did you like me",", did you like it")+"?","I hope, "+GetSexPhrase("you were pleased, because I am ve-e-e-ry pleased","You were pleased, because I did my best")+"...");
						Link.l1 = RandPhraseSimple("Yeah, I liked it a lot.",""+GetSexPhrase("We had a wonderful time, you looked stunning!","Everything was simply terrific!")+"");	
						Link.l1.go = "exit";
					break;
					
					case "2":
						dialog.text = RandPhraseSimple("Well, that's it, you have to go.","Your time is over,"+GetSexPhrase(" Captain,","")+".");
						Link.l1 = RandPhraseSimple("Yeah, see you...","Goodbye and thank you...");
						Link.l1.go = "exit";
					break;
				}
				NextDiag.TempNode = "Horse_AfterSex_2";
			}	
		break;
		
        case "Horse_AfterSex_2":
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && pchar.GenQuest.EncGirl == "Bag_BrothelRoom" && !CheckCharacterItem(pchar, "leather_bag"))
			{
				dialog.text = "So, how did you like it here?";
				link.l1 = "Tell me, beauty, haven't you seen a gripsack anywhere around?";
				link.l1.go = "EncGirl_GetBag";
			}
			else
			{
				dialog.text = LinkRandPhrase("Drop by again sometime...","Goodbye. We'll be waiting for you anytime...","We'll be glad to see you here again...");
				Link.l1 = "Alright...";
				Link.l1.go = "exit";
				NextDiag.TempNode = "Horse_AfterSex_2";
			}	
		break;
		
		case "EncGirl_GetBag":
			dialog.text = "Was it that brown chest with a handle?";
			link.l1 = "Yeah, something like that...";
			link.l1.go = "EncGirl_GetBag1";	
		break;
		
		case "EncGirl_GetBag1":
			dialog.text = "Because the owner of that chest hasn't shown up, madam has taken it to her boudoir.";
			link.l1 = "Thanks, darling. Goodbye.";
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "Bag_BrothelHostess";
			NextDiag.TempNode = "Horse_AfterSex_2";
		break;
		
		// --> генератор - "A reason to hurry"
		case "Horse_ReasonToFast_1":
			dialog.text = "Then drop by anytime, I'll always be glad to see you. You're so "+GetSexPhrase("gentle, not like the others","gentle, not like those roughnecks")+" no hello, no goodbye, and often even try to hurt...";
			link.l1 = "What do you mean by that?";
			link.l1.go = "Horse_ReasonToFast_2";
		break;
		
		case "Horse_ReasonToFast_2":
			pchar.questTemp.ReasonToFast.speakHorse = true;
			dialog.text = "There was a master sergeant just before you. Usually he doesn't pay us visits, but this time some devil brought him here. Moreover, he picked me... He was groaning over me for a few minutes, then called me low-skilled and rushed off to some cove. He left so quickly he nearly forgot his trousers down there, ha-ha-ha...";
			link.l1 = "Don't you know, "+GetSexPhrase("beauty","darling")+", who are men really? He told his wife he was going to the brothel for an 'inspection', then told his mistress he was rushing back to his wife, but the only thing he ever truly wanted was to patrol that cove. "+GetSexPhrase("Ha-ha-ah!..","Ha-ha-ha!")+"";
			link.l1.go = "Horse_ReasonToFast_3";
		break;
		
		case "Horse_ReasonToFast_3":
			NextDiag.TempNode = "Horse_AfterSex_2";			
			ReOpenQuestHeader("ReasonToFast");
			AddQuestRecord("ReasonToFast", "1");
			pchar.questTemp.ReasonToFast = "SpeakHorse";
			pchar.questTemp.ReasonToFast.GuardNation = npchar.nation;
			pchar.questTemp.ReasonToFast.cantSpeakOther = true;
			ReasonToFast_InitVariables();
			string TargetLocation = SelectQuestShoreLocation();
			if(TargetLocation != "")
			{ 
				Locations[FindLocation(TargetLocation)].DisableEncounters = true;
				LAi_LocationDisableOfficersGen(TargetLocation, true);
				pchar.quest.ReasonToFast_MeetPatrol.win_condition.l1 = "location";
				pchar.quest.ReasonToFast_MeetPatrol.win_condition.l1.location = TargetLocation;
				pchar.quest.ReasonToFast_MeetPatrol.function = "ReasonToFast_MeetPatrolShore";
				pchar.questTemp.ReasonToFast.PatrolLocation = TargetLocation;
			}	
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();		
		break;
		// <-- генератор "A reason to hurry"
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//поиски кольца мэра
		case "TakeMayorsRing_S1":
			if (CheckAttribute(pchar, "questTemp.different.TakeMayorsRing.item")) //если валяется в итемах
			{
				dialog.text = LinkRandPhrase("No, darling, sorry, but no. I would gladly help you, but I can't.","No, "+GetSexPhrase("handsome","young lady")+", I haven't seen any ring...","Sorry, but no. I haven't seen any ring.");
				link.l1 = "Pity... Well, thank you anyway.";
				link.l1.go = "exit";
			}
			else
			{
				if (npchar.id == "HorseGen_"+reload_location_index+"_1")
				{
					dialog.text = "Do you mean the governor's ring?";
					link.l1 = "Exactly, darling!";
					link.l1.go = "TakeMayorsRing_S2";
				}
				else
				{
					dialog.text = LinkRandPhrase("No, darling, sorry, but no. I would gladly help you – but I can't.","No, "+GetSexPhrase("handsome","young lady")+", I haven't seen any ring...","Sorry, but no. I haven't seen any ring.");
					link.l1 = "Pity... Well, thank you anyway.";
					link.l1.go = "exit";
				}
			}
		break;

		case "TakeMayorsRing_S2":
			dialog.text = "I am sorry, but the ring was given to me as a present, so I am not obliged to return it.";
			link.l1 = "A present?! And who gave it to you?";
			link.l1.go = "TakeMayorsRing_S3";
		break;
		
		case "TakeMayorsRing_S3":
			dialog.text = "The governor himself, of course!";
			link.l1 = "But he was... tipsy, to say the least. He can't remember a thing.";
			link.l1.go = "TakeMayorsRing_S4";
		break;
		
		case "TakeMayorsRing_S4":
			dialog.text = "And what does that have to do with me? If he was drunk, that's his problem, not mine!";
			link.l1 = "Do you really need to quarrel with him? It's a wedding ring, and you know it... Just give it back, such a small thing is not worth any trouble.";
			link.l1.go = "TakeMayorsRing_S5";
		break;
		
		case "TakeMayorsRing_S5":
			if (rand(1) && sti(pchar.money)>5000)
			{
				dialog.text = "Well, I'll give the ring back, but you will pay me five thousand pesos.";
				link.l1 = "Fine, take your money and give me the ring.";
				link.l1.go = "TakeMayorsRing_S6";
			}
			else
			{
				dialog.text = "Oh, well. Let him have it!";
				link.l1 = "That's for sure, darling!";
				link.l1.go = "exit";
				GiveItem2Character(pchar, "MayorsRing");
				pchar.questTemp.different.TakeMayorsRing = "HorseTakenRing";
				AddQuestRecord("SeekMayorsRing", "3");
				AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
				AddQuestUserData("SeekMayorsRing", "sName", GetFullName(npchar));
			}
		break;
		
		case "TakeMayorsRing_S6":
			dialog.text = "Here you go...";
			link.l1 = "Fine, then. Thanks for the help, darling.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -5000);
			GiveItem2Character(pchar, "MayorsRing");
			pchar.questTemp.different.TakeMayorsRing = "HorseTakenRingMoney";
			AddQuestRecord("SeekMayorsRing", "2");
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("SeekMayorsRing", "sName", GetFullName(npchar));
		break;
		
		//Jason --> Заносчивый аристократ
		case "Badboy":
			pchar.GenQuest.Badboy.Brothel.City = npchar.city; //город квестодателя
			//log_info(pchar.GenQuest.Badboy.Brothel.City); // patch-6
			pchar.GenQuest.Badboy.Brothel.nation = npchar.nation;
			pchar.GenQuest.Badboy.Brothel.Name = GenerateRandomName_Generator(sti(npchar.nation), "man");
			dialog.text = "You see, there is one troublesome customer we have - "+pchar.GenQuest.Badboy.Brothel.Name+". And he really annoys us every time he comes! First he gets drunk at the tavern, then he comes over here, picks up a girl and causes a violent uproar\nAnd the worst thing is that he is of noble descent! He's a distant relative of our governor, so we are forced to endure all his escapades. Maybe you could make that young brazen man... well... calm down a bit... so that he would stop visiting my establishment?";
			link.l1 = "Governor's relative, you say? Hmmm... I'd rather not get into a confrontation with the authorities. I'm really sorry.";
			link.l1.go = "exit";
			link.l2 = "I think I can arrange that. Tell me, where can I find that scapegrace?";
			link.l2.go = "Badboy_1";
		break;
		
		case "Badboy_1":
			dialog.text = "By this time, he is usually already at the tavern. He gets drunk there and then comes over to visit.";
			link.l1 = "I see. Well, I'll probably meet him there.";
			link.l1.go = "exit";
			//создаем дебошира
			int iRank, iType, b;
			string sBlade, sPistol;
			if (sti(pchar.rank) < 6) iType = 0;
			if (sti(pchar.rank) >= 6 && sti(pchar.rank) < 16) iType = 1;
			if (sti(pchar.rank) >= 16) iType = 2;
			switch (iType)
			{
				case 0:
					iRank = 6;
					sBlade = "blade_12";
					sPistol = "pistol1";
					b = 25;
				break;
				case 1:
					iRank = sti(pchar.rank)+10;
					sBlade = "blade_09";
					sPistol = "pistol1";
					b = 65;
				break;
				case 2:
					iRank = sti(pchar.rank)+5;
					sBlade = "blade_14";
					sPistol = "pistol1";
					b = 40;
				break;
			}
			sld = GetCharacter(NPC_GenerateCharacter("Badboy", "citiz_"+(7+rand(1)), "man", "man", iRank, HOLLAND, -1, true, "citizen"));
			FantomMakeCoolFighter(sld, iRank, b, b, sBlade, sPistol, "bullet", makeint(iRank*5));
			sld.name = pchar.GenQuest.Badboy.Brothel.Name;
			sld.lastname = "";
			sld.dialog.FileName = "Quest\Other_quests_NPC.c";
			sld.dialog.currentnode = "Badboy";
			sld.greeting = "noble_male"; // patch-6
			LAi_SetLoginTime(sld, 15, 22);
			LAi_SetSitType(sld);
			FreeSitLocator(pchar.GenQuest.Badboy.Brothel.City + "_tavern", "sit1");
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.Badboy.Brothel.City + "_tavern", "sit", "sit1");
			pchar.GenQuest.Badboy.Brothel.Type = iType; //запомним тип
			pchar.GenQuest.Badboy.Brothel = "true";
		break;
		
		case "Badboy_complete":
			dialog.text = "Oh, you're a real man, aren't you? I always knew I could count on you.";
			link.l1 = "I am always happy to help such a lovely lady and her... wards.";
			link.l1.go = "Badboy_complete_1";
		break;
		
		case "Badboy_complete_1":
			dialog.text = "You are not only brave, but also very gallant. I would like to thank you in a special way - in a way only a woman can thank a man. You will never forget this, I promise. Come upstairs, brave sailor...";
			link.l1 = "...";
			link.l1.go = "Badboy_complete_2";
		break;
		
		case "Badboy_complete_2":
			pchar.questTemp.different.HostessSex.city = pchar.GenQuest.Badboy.Brothel.City;
			AddDialogExitQuestFunction("SexWithHostess_goToRoom");
			SetTimerFunction("SexWithHostess_null", 0, 0, 1); 
			DialogExit();
			if (sti(pchar.GenQuest.Badboy.Brothel.Type) != 2)
			{
				DeleteAttribute(pchar, "GenQuest.Badboy");
			}
			else
			{
				pchar.quest.Badboy_Brothel.win_condition.l1 = "location";
				pchar.quest.Badboy_Brothel.win_condition.l1.location = pchar.GenQuest.Badboy.Brothel.City +"_town";
				pchar.quest.Badboy_Brothel.function = "Badboy_friends";
				DeleteAttribute(pchar, "GenQuest.Badboy.Continue"); // patch-6
			}
			SaveCurrentQuestDateParam("questTemp.Badboy");
			if (!CheckAttribute(pchar, "questTemp.RomNaTroih"))
			{
				pchar.questTemp.RomNaTroih = true;
			}
		break;
		// <-- Заносчивый аристократ
		
		//Португалец
		case "Portugal":
			dialog.text = "There is a man who owes me some money... I don't know how to say...";
			link.l1 = "No words! I'll find him and shake every last peso out of him, just for one look into your fathomless eyes! Just tell me his name!";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "No, no, you haven't understood me correctly, Captain! This man... don't do anything bad to him. Just remind him of his debts. His name is Hugo Avendell, and I suppose you'll find him wherever the cheapest booze is sold. For God's sake, don't use force on him!\nJust say... remind him that he promised to pay. I don't want to involve the guard, but I have friends among the officers, so tell him that I'm waiting, and with all due respect to him, I'll be forced to take action no later than tomorrow. Just remind him of his promise.";
			link.l1 = "Your word is my law, madam. I will gladly fulfil your request.";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			DialogExit();
			InitHugo("Hugo","Avendell");
		break;
		
		case "Portugal_exit":
			dialog.text = "Thank you, captain. I do hope that he will show due prudence.";
			link.l1 = "I am certain of that, madam. Now allow me to take my leave.";
			link.l1.go = "exit";
			sld = characterFromId("Avendel");
			sld.lifeday = 0;
			pchar.questTemp.Portugal = "end";
		break;
		
		case "Portugal_3":
			AddMoneyToCharacter(pchar, -10000);
			dialog.text = "Oh no! Don't tell me you've done something terrible to him... He had no money, and I knew it! We just grew up in the same small town, I would never have turned to the guards! I just wanted to scare him a bit... to shake him up before he drowned in the bottle!";
			link.l1 = "Hmm... Nevertheless, here's your money. And don't worry about Hugo, he's fine... At least he will be if he sobers up.";
			link.l1.go = "Portugal_4";
		break;
		
		case "Portugal_4":
			dialog.text = "Oh, Captain, you don't understand! He was one of... well, you know, they're called bounty hunters - mercenaries, they track down pirates and robbers and eliminate them. But he was not the most fortunate, to say the least\nNot so long ago, he finally splurged and lost his crew and ship, and since then he's been drowning at the bottom of his mug, day after day. Out of old friendship, I let him come here sometimes. He's so... so pitiful now. He used to be the most handsome man in our town on the coast of La Manche, and look at him now\nI know he promised you something, and you paid out of your own pocket! I'll give you this money, just don't do anything bad to him, I beg you, captain!";
			link.l1 = "Fine, alright, madam, I got it. Keep the money, it's yours. As for your friend, I promise that I will not hurt him. And now allow me to take my leave, I've got some business to attend to. Also, I was happy to help such a beautiful lady.";
			link.l1.go = "Portugal_5";
		break;
		
		case "Portugal_5":
			DialogExit();
			sld = characterFromId("Avendel");
			sld.dialog.currentnode = "Avendel_tavern_7";
			AddLandQuestMark(sld, "questmarkmain");
			pchar.questTemp.Portugal = "AvendelTavern";
		break;
		
		// Addon 2016-1 Jason пиратская линейка
		case "mtraxx":
            dialog.text = "Shush, keep your voice down... Go ask Madame Lolita to have a date with me. Then come upstairs, where we can talk freely. And not a word until then... Hey, sailor, go pay Madame before touching me! (giggles)";
			link.l1 = "On my way, sweetheart...";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
           DialogExit();
		   chrDisableReloadToLocation = false;
		   pchar.questTemp.Mtraxx = "jewelry_2";
		break;
		
		case "mtraxx_2":
			pchar.quest.Mtraxx_JewelrySDMOver.over = "yes"; //снять таймер
            dialog.text = "Nah, not me. I'll tell you the whole story, just don't interrupt me.";
			link.l1 = "I am all ears!";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = "Alright then. About a week ago, a military ship arrived in Santo Domingo. It was damaged, either in a storm or a fight, so the repairs began right away, and the crew moved to the fort. Its captain, however, spent all his free time right here. For two days straight he had been drinking and relaxing, accompanied by one of our girls. It was she who got the gemstone, and not just one. She bragged about it endlessly – Lolita lets us keep customers' presents.\nSilly girl didn't even know the true value of the gift, whereas I sized it up straight away. When she told me how the drunk captain boasted about a mountain filled with ambers, I promptly sent a letter to Tyrex...";
			link.l1 = "";
			link.l1.go = "mtraxx_4";
		break;
		
		case "mtraxx_4":
            dialog.text = "By the captain's next arrival I had everything arranged so that his favourite girl was busy with another client, and I got the 'job' myself. I tried to get the coordinates out of him, but alas, to no avail. He just kept boasting that he would become as rich as Crassus and return to the Old World\nNot a single word about the location. The only thing I learned was that his ship had been repaired and was about to sail to Havana, where he would try to arrange a mission in the right direction. He isn't the ship's owner, after all.";
			link.l1 = "So, he is in Havana now?";
			link.l1.go = "mtraxx_5";
		break;
		
		case "mtraxx_5":
            dialog.text = "Sailed off two days ago at dawn. You're the seaman here, you do the counting.";
			link.l1 = "Captain's name, his ship type and name, anything?";
			link.l1.go = "mtraxx_6";
		break;
		
		case "mtraxx_6":
            dialog.text = "What, do you take me for a fool? His name is Esberdo Cabanas, captain of the Cantavro. I think the sailors called it a schooner.";
			link.l1 = "And that's all you know?";
			link.l1.go = "mtraxx_7";
		break;
		
		case "mtraxx_7":
            dialog.text = "What more do you want? I'm sure you could catch up with him before Havana. Don't waste time though, I don't think he'll take a long rest before leaving Cuba for his stash, and then it's a lost cause. On second thought, you could stay for an hour or two, you did pay for it after all.";
			link.l1 = "Good point, darling. Two hours won't make much of a difference...";
			// belamour legendary edition -->
			link.l1.go = "mtraxx_7S";
			link.l2 = "Another time, dear. Consider giving yourself a lunch break. Go to church, or do something else.";
			link.l2.go = "mtraxx_7NS";
			sTotalTemp = npchar.id;
			AddMapQuestMarkCity("Havana", false);
			AddLandQuestMark(characterFromId("Havana_PortMan"), "questmarkmain");
		break;
		
		case "mtraxx_7S":
            DialogExit();
			pchar.GenQuest.BrothelCount = sti(pchar.GenQuest.BrothelCount) + 1; // для Данек
			Achievment_SetStat(23, 1);
			//<-- кол-во посещений
			str = npchar.city;
			pchar.quest.(str).win_condition.l1 = "ExitFromLocation";
			pchar.quest.(str).win_condition.l1.location = pchar.location;
			pchar.quest.(str).win_condition = "Brothel_checkVisitTime";
			pchar.questTemp.HorseQty = sti(pchar.questTemp.HorseQty) + 1; //счетчик
			AddDialogExitQuest("PlaySex_1");
			// кач от борделя
			if (CheckNPCQuestDate(pchar, "BrothelSex"))
			{
				if(IsEquipCharacterByArtefact(pchar, "totem_03")) 	
				{
					AddCharacterHealth(pchar, 10);
					AddCharacterMaxHealth(pchar, 1.0);
				}
				else AddCharacterHealth(pchar, 5);
				SetNPCQuestDate(pchar, "BrothelSex");
			}
			// изменение статусов
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "FencingS", -15);
			AddCharacterExpToSkill(pchar, "Pistol", -15);
		break;
		
		case "mtraxx_7NS":
            DialogExit();
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			AddQuestRecord("Roger_1", "3");
			pchar.questTemp.Mtraxx = "jewelry_3";
			SetFunctionTimerCondition("Mtraxx_JewelryHavanaOver", 0, 0, 7, false); // таймер
			ChangeCharacterAddressGroup(npchar, "none", "", "");
			pchar.quest.mtr_jewelry_havana.win_condition.l1 = "location";
			pchar.quest.mtr_jewelry_havana.win_condition.l1.location = "Cuba2";
			pchar.quest.mtr_jewelry_havana.function = "Mtraxx_HavanaInfo";
			DeleteAttribute(pchar, "questTemp.Mtraxx.AffairOfHonor");
			DeleteAttribute(pchar, "questTemp.ZA.Block");
		break;
		// <-- legendary edition
		case "mtraxx_R":
            dialog.text = "O-oh... What a pity. And I thought you were here on vacation. My girls miss brave corsairs so much. Very well then, speak, what's the task?..";
			link.l1 = "Marcus tasked me to throw a hell of a party in your establishment for two days, to drink all the wine and bed every girl. When shall we begin?";
			link.l1.go = "mtraxx_R1";
		break;
		
		case "mtraxx_R1":
            dialog.text = "Ah, Charlie Prince, your humour is as sharp as your sabre! You almost made me upset... Girls! We have a guest, a special guest! Bring wine and food!";
			if (sti(pchar.money) >= 31000)
			{
				link.l1 = "Call every pretty girl here! We're going to rest and have some fun! Yo-ho-ho!..";
				link.l1.go = "mtraxx_R2";
			}
			else
			{
				link.l1 = "Hold on a minute, Janette. I need to fetch the gold from my ship for you and your ladies. See you in a minute!";
				link.l1.go = "exit";
				pchar.questTemp.Mtraxx.Retribution = "brothel_repeat";
				chrDisableReloadToLocation = false;
			}
		break;
		
		case "mtraxx_R2":
			AddMoneyToCharacter(pchar, -30000);
            dialog.text = "I wish all our customers were as sweet, handsome, and generous as you are... We'll give you perfect relaxation. Girls!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionInBrothel");
		break;
		// belamour ночной приключенец
		case "NA_Girl":
            dialog.text = "Oh, so we have a connoisseur here, hee hee ... Well, well, I have just the girl. But she doesn't come cheap: "+makeint(pchar.GenQuest.NightAdventure_money)+" pesos."; 
			link.l1 = "Deal.";
			link.l1.go = "NA_Girl_1";
		break;
		
		case "NA_Girl_1":
			AddMoneyToCharacter(pchar, -makeint(pchar.GenQuest.NightAdventure_money));
            dialog.text = "That's great, dear. The Priestess of Love will be waiting for you upstairs. Trust me, you won't regret it."; 
			link.l1 = "I already don't.";
			link.l1.go = "NA_Girl_2";
		break;
		
		case "NA_Girl_2":
			DialogExit();
			pchar.GenQuest.NightAdventureVar = "NightAdventure_NobleWhore"; 
			sld = characterFromId(pchar.GenQuest.NightAdventureId);
			sld.dialog.currentnode = "NightAdventure_NobleWhore_7";
		break;
		// <-- приключенец
		
		case "chicken_god":
			dialog.text = "For you and m'lord Agüeybana? Of course you do. That will be ten thousand, captain.";
			if (sti(pchar.money) >= 10000) {
				link.l1 = "Wait, not like that!.. Damn it! Whatever, here is the pay.";
				link.l1.go = "chicken_god_pay";
			} else {
				link.l2 = "Can I get a loan?";
				link.l2.go = "chicken_god_notpay";
			}
		break;
		
		case "chicken_god_pay":
			dialog.text = "Enjoy your stay, captain. Please come back again when we are open. Our establishment provides all kinds of leisure for noble men and women.";
			link.l1 = "...";
			link.l1.go = "chicken_god_pay_1";
		break;
		
		case "chicken_god_pay_1":
			dialog.text = "";
			link.l1 = "Madam "+npchar.name+", can you at least explain what's going on here? Is the governor even aware that you've had a native in charge for a month? No settlement can survive a brothel being closed for a day, I can tell you that!";
			link.l1.go = "chicken_god_pay_2";
		break;
		
		case "chicken_god_pay_2":
			dialog.text = "The room is yours, captain. Now, if you'll excuse me.";
			link.l1 = "Charming. Goodbye, madam.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_PayForRoom");
		break;
		
		case "chicken_god_notpay":
			dialog.text = "Why, Lord, why? Get out of here! Go away, go away, I can't take it anymore! Bastard!";
			link.l1 = "That went well.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_NotPayForRoom");
		break;
		
		//-->> Sinistra Ром на троих
		case "RomNaTroih_1":
			dialog.text = "Mhm... I don't usually do this... but I'm willing to risk it for you. It's your lucky day, Captain!";
			link.l1 = "Let's go!";
			link.l1.go = "exit";
			pchar.RomNaTroih_Shluha = npchar.id;
		break;
		
		case "RomNaTroih_2":
			dialog.text = "I am angry with you, Captain... But I will show you mercy if you work hard enough for it.";
			link.l1 = "Oh, I will. Shall we open some wine?";
			link.l1.go = "exit";
			Achievment_Set("ach_CL_105");
		break;
		//<<-- Sinistra Ром на троих
	}
}

ref GetFreeHorseRef(string City)
{
	ref rCharacter;
    int storeArray[8];
	int howStore = 0;
	for(int n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter, Characters[n]);
		if (rCharacter.location == City+"_Brothel" && CheckAttribute(rCharacter, "CityType") && rCharacter.CityType == "horse" && rCharacter.horse == "HorseStay")
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return &NullCharacter;
	return &characters[storeArray[rand(howStore-1)]];
}

ref CheckHorsesName(string City, int num)
{
	ref rCharacter;
	string sTemp, sSeeked;
	sSeeked = GetStrSmallRegister(dialogEditStrings[num]);
	for(int n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter, Characters[n]);
		if (rCharacter.location == City+"_Brothel" && CheckAttribute(rCharacter, "CityType") && rCharacter.CityType == "horse")
		{
			sTemp = GetStrSmallRegister(rCharacter.lastname + " " + rCharacter.name);
			if (findsubstr(sSeeked, sTemp , 0) != -1)
				return rCharacter;			
			sTemp = GetStrSmallRegister(rCharacter.lastname);
			if (findsubstr(sSeeked, sTemp , 0) != -1)
				return rCharacter;
			sTemp = GetStrSmallRegister(rCharacter.name);
			if (findsubstr(sSeeked, sTemp , 0) != -1)
				return rCharacter;
		}
	}
	return &NullCharacter;
}

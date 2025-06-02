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
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase(""+GetSexPhrase("Quelles filles, cher?! La moitié de la garnison est après toi, et tu viens directement au bordel!","Dégage, tu veux? La moitié de la garnison est après toi!")+"","Chaque garde de ville vous cherche. Je ne suis pas un imbécile pour vous fournir des services en ce moment ...","Vous n'avez rien à faire ici !"),LinkRandPhrase(""+GetSexPhrase("Ose seulement toucher à mes filles et je te dépècerai vivant !","Dégage, espèce de crevure!")+"","Sale"+GetSexPhrase("","")+" assassin, quitte mon établissement, maintenant! Gardes!!!","Je n'ai pas peur de toi, "+GetSexPhrase("scélérat","rat")+"! Bientôt tu seras pendu dans notre fort, tu n'iras pas loin..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Heh, une alarme n'est jamais un problème pour moi...","Ils ne m'attraperont jamais."),RandPhraseSimple("Taisez-vous, vieille idiote.","Tais-toi si tu ne veux pas de problèmes..."));
				link.l1.go = "exit";
				break;
			}
			//--> прибыла инспекция на Святом Милосердии
			if (CheckAttribute(npchar, "quest.SantaMisericordia"))
			{
				dialog.text = "Oh, "+GetSexPhrase("jeune homme","doux enfant")+", nous sommes fermés aujourd'hui.";
				link.l1 = "Fermé?";
				link.l1.go = "SantaMisericordia_1";
				break;
			}
			//<-- прибыла инспекция на Святом Милосердии
			//--> Мерзкий Божок
			if (CheckAttribute(pchar, "questTemp.ChickenGod.HostessDialog")) {
				dialog.text = "Oh, mon Dieu! Comment êtes-vous entré ici? Cher capitaine, je vous prie de partir - je vous en supplie! Notre établissement est actuellement fermé!";
				link.l1 = "Heureux de te voir, cher "+npchar.name+". J'étais sur la liste des invités. Cependant, dans de telles établissements, même les invités doivent payer, alors... S'il te plaît ne rends pas cela trop difficile pour moi, mais je veux payer pour une chambre.";
				link.l1.go = "chicken_god";
				
				DeleteAttribute(pchar, "questTemp.ChickenGod.HostessDialog");
				break;
			}
			//<-- Мерзкий Божок
			//--> туториал Мартиника
			if (CheckAttribute(pchar, "questTemp.Sharlie.Gigolo") && pchar.questTemp.Sharlie.Gigolo == "start" && npchar.location == "FortFrance_SecBrRoom")
			{
				DelLandQuestMark(npchar);
				link.l1 = "Ecoute, Aurora, j'ai besoin d'une fille pour la nuit. Et je veux l'emmener chez moi. Peux-tu arranger ça ?";
                link.l1.go = "Gigolo";
				break;
			}
			//<-- туториал Мартиника
			//Jason --> Заносчивый аристократ
			if (!CheckAttribute(pchar, "GenQuest.Badboy") && !CheckAttribute(npchar, "quest.Badboy") && !CheckAttribute(pchar, "questTemp.ZA.Block") && makeint(environment.time) > 15.0 && makeint(environment.time) < 21.0 && sti(pchar.questTemp.HorseQty) > 4)
			{
				dialog.text = "Vous êtes un homme si respectable. De plus, mes filles vous aiment beaucoup. J'aimerais vous demander une petite faveur pour mon établissement.";
				link.l5 = "Je suis flatté, c'est certain. Avec quoi avez-vous besoin de mon aide?";
				link.l5.go = "Badboy";
				link.l8 = "Je suis désolé, mais je suis occupé pour le moment.";
				link.l8.go = "exit";
				npchar.quest.Badboy = "true";
				break;
			}
			
			if (CheckAttribute(pchar, "GenQuest.Badboy.Complete") || CheckAttribute(pchar, "GenQuest.Badboy.Continue"))
			{
				if (npchar.City == pchar.GenQuest.Badboy.Brothel.City)
				{
					dialog.text = "Oh, vous êtes revenu ! Avez-vous arrangé cela "+pchar.GenQuest.Badboy.Brothel.Name+" pour laisser mes filles tranquilles?";
					link.l5 = "Oui. Il ne montrera plus son visage ici.";
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
					dialog.text = "Capitaine, puis-je vous demander une faveur?";
					link.l5 = "Pour vous, madame, tout ce que vous voulez! Je suis à votre service!";
					link.l5.go = "Portugal";
					link.l8 = "Je suis désolé, mais je suis occupé pour le moment.";
					link.l8.go = "exit";
					npchar.quest.Portugal = "true";
					break;
				}
			}
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "HostressMoney" && npchar.location == "Marigo_SecBrRoom")
			{
				DelLandQuestMark(npchar);
				dialog.text = "Vous avez parlé avec Hugo, monsieur le Capitaine?";
				if (sti(pchar.money) >= 10000)
				{
					link.l1 = "De plus, madame, voici votre argent. Tout s'est passé de la manière la plus favorable...";
					link.l1.go = "Portugal_3";
				}
				else
				{
					link.l1 = "Oui, je lui ai transmis votre demande.";
					link.l1.go = "Portugal_exit";
				}
				break;
			}
			//<--Португалец
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "brothel" && npchar.location == "Tortuga_SecBrRoom")
			{
				dialog.text = "Oh la la, regarde ça ! Charlie Prince, un corsaire célèbre ! En chair et en os !";
				link.l1 = RandSwear()+"Bonjour, Janette. Je suis ici pour la mission de Marcus Tyrex.";
				link.l1.go = "mtraxx_R";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "brothel_repeat" && npchar.location == "Tortuga_SecBrRoom")
			{
				dialog.text = "Êtes-vous prêt pour un traitement réparateur inoubliable, mon brave corsaire?";
				if (sti(pchar.money) >= 31000)
				{
					link.l1 = "Je le suis! Charlie Prince ne gaspille pas les mots comme il gaspille l'argent, ha-ha!";
					link.l1.go = "mtraxx_R2";
				}
				else
				{
					link.l1 = "Presque... Je suppose que j'ai perdu une bourse dans votre établissement... Je reviendrai avec de l'argent!";
					link.l1.go = "exit";
				}
				break;
			}
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = RandPhraseSimple(TimeGreeting()+". Bienvenue dans ma maison d'amour. Mon nom est "+npchar.name+", et je suis le proprietaire. "+GetSexPhrase("Que puis-je faire pour vous, "+GetAddress_Form(NPChar)+"?","Franchement, je suis un peu surpris de te voir ici, "+GetAddress_Form(NPChar)+", mais je vous assure que nous rendons des services non seulement pour les hommes.")+"",TimeGreeting()+". Je vous souhaite la bienvenue, "+GetSexPhrase("étranger","jeune dame")+", à mon humble établissement. Permettez-moi de me présenter, je suis "+NPChar.Name+" - détenteur de cet asile pour les hommes affamés du toucher d'une femme. "+GetSexPhrase("Que puis-je faire pour vous ?","Bien que nous ayons une chose ou deux pour les dames aussi...")+"");
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = RandPhraseSimple(TimeGreeting()+". Comment puis-je vous aider, "+GetAddress_Form(NPChar)+"?",TimeGreeting()+". Que puis-je faire pour vous, "+GetAddress_Form(NPChar)+"?");
			}
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Gigolo"))//не идёт квест девочки
			{
				if (!CheckAttribute(pchar, "GenQuest.BrothelLock"))// нет запрета от Мэри 280313
				{
					link.l2 = npchar.name+", je veux passer du bon temps avec l'une de vos filles.";
					link.l2.go = "Hostess_1";
				}
			}
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock")) // не идёт старт Шарля
			{
				if (sti(pchar.ship.type) != SHIP_NOTUSED && GetCrewQuantity(pchar) > 0) // Rebbebion - а смысл, если нет как корабля, так и команды?
				{
					link.l3 = "Cela fait un moment depuis la dernière fois que j'ai gâté mes hommes. Puis-je passer une commande en gros de filles pour mes gars?";
					link.l3.go = "ForCrew";
				}
			}
			link.l4 = "J'ai une question.";
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
				link.l5 = "Écoute, "+npchar.name+", je cherche l'anneau du gouverneur. Il s'est reposé dans votre établissement et l'a probablement perdu ici.";
				link.l5.go = "TakeMayorsRing_H1";
				SaveCurrentNpcQuestDateParam(npchar, "TakeMayorsRing");
			}
			//<<-- квест поиска кольца мэра

			// belamour ночной приключенец -->
			if(CheckAttribute(pchar, "GenQuest.NightAdventureVar") && pchar.GenQuest.NightAdventureVar == "NightAdventure_NobleWhoreMoney")
			{
				link.l8 = "Regarde, j'aimerais prendre la meilleure fille que tu as.";
				link.l8.go = "NA_Girl";
			}
			// <-- приключенец
			link.l9 = "Peu importe, je pars déjà.";
			link.l9.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "ShipLetters_1":
				pchar.questTemp.different.GiveShipLetters.speakBrothelMadam = true;
				dialog.text = RandPhraseSimple("Que voulez-vous, beau gosse ?","Je vous écoute, Capitaine.");
				link.l1 = "Écoute, "+npchar.name+", J'ai trouvé ces papiers dans une pièce privée de votre établissement ...";
				link.l1.go = "ShipLetters_2";				
		break;
		
		case "ShipLetters_2":
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Laissez-moi voir ! Hmm ... un capitaine a perdu ses documents, n'est-ce pas ? Je pense que vous devriez demander au maître du port à ce sujet.";
				link.l1 = "Peut-être, peut-être...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Laissez-moi jeter un coup d'oeil ! Oh ! À en juger par le nom, ils appartiennent à mon estimé client et à un citoyen digne de notre ville. Je peux lui remettre ces documents moi-même.";
				link.l1 = "Probablement, non...";
				link.l1.go = "exit";
				link.l2 = "Excellent ! Toujours ravi d'aider une bonne personne et un établissement digne.";
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
					dialog.text = ""+GetSexPhrase("Nous sommes toujours heureux de servir un client. Alors dites-moi, beau gosse - avez-vous déjà choisi quelqu'un ou cela ne vous importe guère?","Eh bien, mes filles sont certainement capables de... vous aider. Avez-vous déjà choisi quelqu'un ou cela ne vous importe pas beaucoup?")+"";
					Link.l1 = ""+GetSexPhrase("Heh, j'ai juste besoin d'une pute et je la veux tout de suite. Je m'en fiche laquelle, toutes vos filles me plaisent...","N'importe qui ira bien si elle connait ses devoirs, bien sûr...")+"";
					Link.l1.go = "Hostess_NotChoice";	
					Link.l2 = "Oui, il y en a un, "+GetSexPhrase("qui a pris ma fantaisie...","elle serait la plus gentille...")+"";
					Link.l2.go = "Hostess_Choice";
				}
				else
				{
					dialog.text = "Je n'ai pas de filles libres pour toi aujourd'hui, nous avons déjà trop de clients. Viens demain, et tu ne le regretteras pas!";
					Link.l1 = "Dommage, je commençais juste à m'amuser.";
					Link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Hmm. Vous avez déjà payé pour la fille. Ne me dérangez pas, s'il vous plaît.";
				Link.l1 = "D'accord, je viens.";
				Link.l1.go = "exit";	
			}
		break;

        case "Hostess_NotChoice":
			sld = GetFreeHorseRef(npchar.city);
			location = &locations[FindLocation(npchar.city + "_Brothel")];
			if (sld.id == "none" || GetNpcQuestPastDayParam(location, "Brothel_date") > 98)
			{
				dialog.text = "Je n'ai pas de filles libres en ce moment, vous devrez revenir dans quelques jours.";
				Link.l1 = "D'accord, comme tu dis.";
				Link.l1.go = "exit";	
			}
			else
			{
				// belamour legendary edition Орден Святого Людовика -->
				if(IsEquipTalisman9() && npchar.nation == FRANCE)
				{
					dialog.text = ""+GetSexPhrase("Eh bien, etalon, c'est excellent!","Je les ai tous adroits, vous pouvez en être sûr.")+"Je peux offrir une belle fille nommée "+GetFullName(sld)+", elle est libre maintenant.\nOh, qu'est-ce que tu caches si modestement là ?! Est-ce la plus haute distinction en France ? On dit que les porteurs de cette insigne sont légendaires non seulement sur le champ de bataille... Eh bien, tu sais ce que je veux dire, mon flibustier... De plus, n'importe qui considérerait comme un honneur de toucher ton 'Ordre', donc aujourd'hui tu te reposes aux frais de mon établissement. Les refus ne sont pas acceptés, beau gosse.";
					Link.l1 = "Bien sûr que je suis d'accord, quelles questions peuvent y avoir?!";
					Link.l1.go = "Hostess_NotChoice_agree";	
					npchar.quest.choiceIdx = sld.index;
					break;
				}
				// <-- legendary edition
				dialog.text = ""+GetSexPhrase("Eh bien, excellent, mon étalon!","Ils sont tous très doués dans ce qu'ils font, n'en doutez pas.")+"Je peux vous proposer une fille très sympa, son nom est "+GetFullName(sld)+", et elle est libre en ce moment. Ce plaisir vous coûtera "+FindRussianMoneyString(sti(sld.quest.price)+charWhoreCost)+". D'accord?";
				Link.l1 = "Non. Je suppose que non. C'est trop cher...";
				Link.l1.go = "exit";
				if (sti(pchar.money) >= (sti(sld.quest.price) + charWhoreCost))
				{
					Link.l2 = "Bien sûr, comment pourrais-je refuser?!";
					Link.l2.go = "Hostess_NotChoice_agree";	
					npchar.quest.choiceIdx = sld.index;
				}
				else
				{
					Link.l1 = "Oh merde, je n'ai pas autant d'argent sur moi...";
					Link.l1.go = "exit";
				}
			}
		break;
		
        case "Hostess_NotChoice_agree":
			sld = &characters[sti(npchar.quest.choiceIdx)];
			if (sti(pchar.money) >= (sti(sld.quest.price) + charWhoreCost))
			{
				dialog.text = "D'accord, "+GetSexPhrase("beau","beau")+". "+sld.name+" vous attendra dans une salle privée au deuxième étage.";
				Link.l1 = ""+GetSexPhrase("D'accord, j'arrive, alors","D'accord, j'arrive, alors")+"Bonjour, monami.";
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
				dialog.text = "Oh, tu vois, le problème est que "+sld.name+" n'est pas une fille bon marché, son prix est "+FindRussianMoneyString(sti(sld.quest.price)+charWhoreCost)+". Et je vois que tu ne peux tout simplement pas te permettre de l'acheter pour le moment. Reviens quand tu seras riche"+GetSexPhrase(", cher","")+"Bonjour, monami.";
				Link.l1 = "C'est ma chance...";
				Link.l1.go = "exit";
			}
		break;

        case "Hostess_Choice":
			dialog.text = "Je suis toujours content quand les filles et les clients développent des sentiments chaleureux l'un pour l'autre... Dis-moi son nom.";
			Link.l1.edit = 9;
			Link.l1 = "";
			Link.l1.go = "Hostess_Choice_1";	
		break;
		
        case "Hostess_Choice_1":
			sld = CheckHorsesName(npchar.city, 9);
			if (sld.id == "none")
			{
				dialog.text = "Hmm... vous devez vous tromper. Je n'ai aucune fille de ce nom dans mon établissement. Peut-être que vous vous êtes trompé de nom.";
				Link.l1 = "Hmm... mais je viens de parler avec elle.";
				Link.l1.go = "Hostess_Choice_2";				
				Link.l2 = "Peut-être. Il serait préférable de lui demander son nom encore une fois, juste pour être sûr. Je discuterai de cela avec vous plus tard.";
				Link.l2.go = "exit";	
			}
			else
			{
				dialog.text = GetFullName(sld)+", vous parlez d'elle?";
				Link.l1 = "Ouais, a propos d'elle.";
				Link.l1.go = "Hostess_NotChoice_agree";				
				Link.l2 = "Non, ce n'est pas elle.";
				Link.l2.go = "Hostess_Choice_2";
				npchar.quest.choiceIdx = sld.index;
			}
		break;
		
        case "Hostess_Choice_2":
			dialog.text = "Alors peut-être, vous devriez me dire son nom une fois de plus, et peut-être je réaliserai, de qui vous parlez.";
			Link.l1.edit = 9;
			Link.l1 = "";
			Link.l1.go = "Hostess_Choice_1";
			Link.l2 = "Peut-être. Il serait préférable de lui demander à nouveau son nom, juste pour être sûr. Je parlerai de cela avec toi plus tard.";
			Link.l2.go = "exit";	
		break;
		//==> команда
		case "ForCrew":
			dialog.text = "Hmm... Vous voulez aider vos gars à 'se défouler un peu'? Vous voyez, mon établissement est un lieu respectable, et j'ai les meilleures filles du coin. Mais je connais plusieurs servantes de port, et elles seront heureuses de satisfaire tous vos marins. Cela vous coûtera "+FindRussianMoneyString(GetCrewQuantity(pchar)*crewWhoreCost)+".";			
			link.l1 = "D'accord, je suis d'accord.";
			link.l1.go = "ForCrew_1";
			link.l2 = "Je suppose qu'ils peuvent se débrouiller sans ça...";
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
		        dialog.text = "Ce n'est pas mes oignons, mais je pense qu'au début, tu devrais gagner assez d'argent pour engager un équipage, et seulement ensuite te préoccuper de son moral.";
			    link.l1 = "Tu as probablement raison...";
			    link.l1.go = "exit";
		    }
		break;
		
		case "Woman_FackYou":
			dialog.text = "Chéri, que faites-vous ?! Et vous aviez l'air d'un capitaine décent... Vous ne 'volerez' pas cette fois, beau gosse. Les gardes vous couperont les ailes...";
			link.l1 = "Tais-toi, vieille sorcière.";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		
		//поиски кольца губернатора
		case "TakeMayorsRing_H1":
			dialog.text = "Je n'ai trouvé aucune bague.";
			link.l1 = "Et vos filles?";
			link.l1.go = "TakeMayorsRing_H2";
		break;
		
		case "TakeMayorsRing_H2":
			dialog.text = "Ils ne l'ont pas non plus. Si un client oublie ou perd quelque chose, mes filles me l'apportent. Mais personne ne m'a apporté la bague du gouverneur.";
			link.l1 = "Je vois... Mais pourrait-il qu'ils aient décidé de le garder pour eux-mêmes ?";
			link.l1.go = "TakeMayorsRing_H3";
		break;
		
		case "TakeMayorsRing_H3":
			dialog.text = "Peu probable. Les filles sont autorisées à garder les cadeaux des clients, mais c'est tout.";
			link.l1 = "Je vois. Eh bien, merci, "+npchar.name+".";
			link.l1.go = "exit";
		break;
		
		case "Hostess_inSexRoom":
			dialog.text = "Oh, voici que tu es là...";
			link.l1 = "Me voici, ma dame!";
			link.l1.go = "exit";
			pchar.quest.SexWithHostess_null.over = "yes"; //нулим таймер на не пришёл
			NextDiag.TempNode = "First time";
			if (CheckAttribute(pchar, "questTemp.RomNaTroih_Pogovoril"))
			{
				sld = CharacterFromID(pchar.RomNaTroih_Shluha);
				dialog.text = ""+sld.name+"! Mon héros, je peux voir que tu n'as pas perdu ton temps en bas!";
				link.l1 = "J'espère que vous me pardonnerez cette faiblesse, ma reine?";
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
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("Tu ferais mieux de quitter l'établissement !","Tous les gardes de la ville vous cherchent ! Il serait préférable que vous partiez...","Tu as tout foutu en l'air et maintenant tu te pointes ici ?! Non, pas cette fois..."),LinkRandPhrase("Va-t'en !","Sale meurtrier, sors d'ici! Gardes!","Je n'ai pas peur de toi,"+GetSexPhrase("canaille","rat")+"! Bientôt tu seras pendu dans notre fort, tu ne t'échapperas pas loin..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Heh, une alarme n'est jamais un problème pour moi...","Ils ne m'attraperont jamais."),RandPhraseSimple("Heh, quelle sotte garce tu es...","Ferme ta gueule, pute, ou je la fermerai avec quelque chose d'autre..."));
				link.l1.go = "exit";
				break;
			}
			dialog.text = NPCStringReactionRepeat("Bonjour, "+GetAddress_Form(NPChar)+""+GetSexPhrase("",", hee-hee..")+". Vous devez voir la dame et remplir la commande.","Encore vous? Veuillez parler avec la gardienne. Elle est dans son bureau.","Regarde, "+GetAddress_Form(NPChar)+""+GetSexPhrase(", J'espère que tu es aussi têtu dans d'autres choses que tu l'es en parlant... Encore une fois","Encore une fois")+"Je vous demande de voir le propriétaire de l'établissement.","Oh, "+GetAddress_Form(NPChar)+""+GetSexPhrase(", n'es-tu pas un têtu !",", Hee-hee... Tu es un têtu, n'est-ce pas?")+" Vous devez voir la dame et remplir la commande.","bloc",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("D'accord, "+GetSexPhrase("beauté, ","")+"Je l'ai eu"+GetSexPhrase("","")+".","Ouais, bien sûr...",""+GetSexPhrase("N'aie aucun doute, ma jolie, je suis aussi têtu et fort qu'un taureau !","Ouais, ouais...")+"",""+GetSexPhrase("Oh diable, j'ai dû manquer quelque chose... Je suis désolé, cher.","D'accord, très bien.")+"",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			Link.l2 = "Et où est-elle ?";
			Link.l2.go = "Horse_1";
			Link.l3 = LinkRandPhrase(""+GetSexPhrase("Oh, beauté, je parie que je pourrais me noyer dans ces yeux à toi...","Tu es belle, chérie!")+"",""+GetSexPhrase("Vous savez, je n'ai jamais rencontré une femme aussi belle auparavant!","Tu sais, je n'ai jamais rencontré une poulette aussi sympa auparavant!")+"",""+GetSexPhrase("Chérie, tu es magnifique.","Zut, j'en avais tellement marre de tous ces ploucs... Et tu es si charmant!")+"");
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
				link.l5 = LinkRandPhrase("Écoutez, "+GetSexPhrase("beauté","chéri")+", n'avez-vous pas trouvé une alliance ici, par hasard ? Un homme semble l'avoir perdue...","Chérie, as-tu vu une bague de mariage ou quelque chose comme ça autour?","Écoute, "+GetSexPhrase("mon minou","poupee")+", n'avez-vous pas vu une bague de mariage par ici?");
				link.l5.go = "TakeMayorsRing_S1";
				SaveCurrentNpcQuestDateParam(npchar, "TakeMayorsRing");
			}
			//<<-- квест поиска кольца мэра
			
			// Addon 2016-1 Jason пиратская линейка
			if (pchar.location == "santodomingo_brothel" && CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_1" && npchar.id == "HorseGen_"+reload_location_index+"_2")
			{
				link.l6 = "Salut, mon coeur. Marcus Tyrex m'a envoyé, regarde ce collier d'ambre...";
				link.l6.go = "mtraxx";
			}
			NextDiag.TempNode = "Horse_talk";
		break;
		
        case "Horse_1":
			dialog.text = "Elle est dans son bureau. Vous pouvez y arriver d'ici par la porte opposée à la sortie sur la rue, ou depuis la rue de l'autre côté de la maison. Son nom est "+characters[GetCharacterIndex(npchar.city+"_Hostess")].name+".";
			Link.l1 = "Je vois, "+GetSexPhrase("chérie","chérie")+", merci.";
			Link.l1.go = "exit";			
		break;
		
        case "Horse_2":
			if (rand(1))
			{
				dialog.text = LinkRandPhrase("Oh là là, c'est tellement agréable d'entendre de telles choses! Hé, je suis libre pour le moment, donc si tu me choisis, tu ne le regretteras pas...","Tu penses vraiment ça ? Tu sais, c'est si mignon... Écoute, je suis libre pour le moment, donc tu peux me choisir."+GetSexPhrase("Je te promets la mer d'amour et un océan de caresse...","")+"",""+GetSexPhrase("Pensez-vous vraiment? Oh, je suis vraiment flatté. Vous savez, j'entends rarement des compliments comme ceux-ci...","Oh, fille... si seulement tu savais combien j'en ai marre des ploucs...")+" Hé, écoute, je suis libre en ce moment, alors tu peux me choisir pour te rendre heureux. Je ne te décevrai pas, je te le promets...");
				if (CheckAttribute(pchar, "questTemp.RomNaTroih") && !CheckAttribute(pchar, "questTemp.RomNaTroih_Pogovoril"))
				{
					link.l1 = "Ma chère, c'est exactement ce que j'allais faire ! Comme il est heureux que votre hôtesse ait déjà obtenu un rendez-vous privé avec moi à l'étage. Souhaitez-vous vous joindre à nous ?";
					Link.l1.go = "RomNaTroih_1";
					pchar.questTemp.RomNaTroih_Pogovoril = true;
					break;
				}
				link.l1 = "Eh bien, je te choisis, alors!";
				Link.l1.go = "Horse_3";		
				Link.l2 = ""+GetSexPhrase("Non, c'était juste un compliment à une jolie dame","C'était juste un compliment")+".";
				Link.l2.go = "exit";
				npchar.quest.choice = 0; //был базар, но ГГ потом отказался
			}
			else
			{
				dialog.text = LinkRandPhrase(""+GetSexPhrase("Tu sais ce que je dis, ma chérie? Je n'ai pas besoin de ce discours bon marché. Fais affaire ou pars!","C'est tout ce dont j'avais besoin! Des compliments de femmes!")+"",""+GetSexPhrase("Es-tu de ceux qui pensent que les femmes aiment avec leurs oreilles ? Eh bien, mon cher, ce n'est tout simplement pas vrai. Si tu me veux, alors paie à la madame et épargne-moi tes paroles vides.","Demoiselle, ne gaspillez pas votre temps avec des paroles vaines. Si vous êtes sérieuse - alors payez...")+"",""+GetSexPhrase("Oh, un autre amateur de sensualité... Tu paies juste et je suis à toi. C'est aussi simple, sans toutes ces bêtises douces!","Qu'est-ce qui te prend, chéri? Si tu veux te faire plaisir, alors paie juste et arrête toutes ces sottises!")+"");
				link.l1 = "Oh, quelle prise !";
				Link.l1.go = "exit";
				npchar.quest.choice = 2; //ГГ послали
			}
		break;
		
        case "Horse_3":
			dialog.text = characters[GetCharacterIndex(npchar.city+"_Hostess")].name+" termine toutes les formalités dans son cabinet. Allez la voir"+GetSexPhrase(", mon héros,","")+" et dis mon nom - "+npchar.name+". Je t'attendrai...";
			Link.l1 = "Je vois, chérie, je reviendrai bientôt...";
			Link.l1.go = "exit";
			npchar.quest.choice = 1; //она согласная
			SetNPCQuestDate(npchar, "quest.choice");
		break;
		
        case "Horse_4": 
			dialog.text = NPCStringReactionRepeat("Vous avez déjà payé.","Je t'ai dit 'monte à l'étage'.","En haut, jeune homme.","Certaines personnes réfléchissent si lentement...","bloc",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Ouais, je sais.","Je me souviens.","Oh, ne te répète pas, je me souviens.","Hmm, que voulez-vous dire ?.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "Horse_4";
		break;
		
		//===>> реакция на попытки пофлиртовыть, если флирт уже был
        case "HorseChoice_0": 
			if (!CheckAttribute(npchar, "quest.sexHappend"))
			{
				dialog.text = NPCStringReactionRepeat("Je ne vous comprends pas tout à fait."+GetSexPhrase(" D'abord tu fais des compliments, puis tu reviens sur tes mots. Quel type étrange...","")+"","Des compliments encore ?.","La gardienne est dans son bureau. Compris?","Nous ne sommes pas censés insulter nos clients, mais vous le demandez vraiment"+GetSexPhrase("","")+"...","bloc",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("C'est juste arrivé comme ça...","D'accord, je vais faire ça.","Ouais, je l'ai.","Pardon, mon amour.",npchar,Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Merci pour le compliment. Si tu veux m'emporter, va voir la patronne. Les affaires comme d'habitude.";
				Link.l1 = "Je vois.";
				Link.l1.go = "exit";
			}
		break;
		
        case "HorseChoice_1": 
			if (!CheckAttribute(npchar, "quest.sexHappend"))
			{
				if (!CheckNPCQuestDate(npchar, "quest.choice"))
				{
					dialog.text = NPCStringReactionRepeat(""+GetSexPhrase("Chéri, nous en avons déjà parlé en long et en large. ","")+"Ne me fais pas attendre trop longtemps...",""+GetSexPhrase("Hmm... Écoute, mon cher, je","Je")+" je trouve vos mots très agréables et tout, mais pourriez-vous en venir aux affaires...","Peut-être, discuterez-vous de cela avec madame, n'est-ce pas?","Hm... Je ne sais même pas quoi dire...","bloc",1,npchar,Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("Je ne ferais jamais cela, attends-moi!","Certainement!","Bien sûr, comme vous le dites !","Je suis déjà en train de courir pour voir votre madame...",npchar,Dialog.CurrentNode);
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Je t'attendais, mais tu n'es pas venu me chercher... Je ne peux pas dire que j'ai aimé ça...";
					Link.l1 = "Tu vois, cela s'est juste passé comme ça...";
					Link.l1.go = "exit";
					npchar.quest.choice = 0; //был базар, но ГГ потом отказался
				}
			}
			else
			{
				dialog.text = "Oh, c'est toi encore, mon "+GetSexPhrase("glorieux corsaire","jolie demoiselle")+"! Si tu veux me revoir, viens voir la madame, tu ne seras pas déçu..."+GetSexPhrase(" Au fait, je vous ai reconnu, cher, mais on nous dit que nous devons parler à tous les clients de la même manière, il ne devrait pas y avoir de favori, désolé pour ça...","")+"";
				Link.l1 = "Ne t'inquiète pas, ma chérie. Attends-moi juste un peu, "+GetSexPhrase("beauté","mignon")+", et bientôt nous nous rencontrerons à nouveau en privé.";
				Link.l1.go = "exit";
				Link.l2 = "C'est très joli que tu te souviennes de moi, mais je ne peux pas passer cette nuit avec toi, désolé.";
				Link.l2.go = "HorseChoice_1_Add";
			}
		break;
		
        case "HorseChoice_2": 
			if (!CheckAttribute(npchar, "quest.sexHappend"))
			{
				dialog.text = NPCStringReactionRepeat("Alors,"+GetSexPhrase("cher ami,","")+" tu ferais mieux de t'occuper des affaires. Ce sera plus utile que de ne rien faire.",""+GetSexPhrase("Hmm, pourquoi es-tu ","Pourquoi es-tu")+" dire les mêmes choses encore et encore?","Eh bien, n'est-ce pas assez?!","Hm, quelle surprise, rien de nouveau"+GetSexPhrase(", encore une fois toutes ces stupides tentatives de charme ! Si tu veux coucher avec moi, va voir la madame, espèce de cervelle d'oiseau !","Bonjour, monami.")+"","bloc",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Ouais, j'ai entendu"+GetSexPhrase("","")+" toi...","Hmm, c'est comme ça que ça se passe...","Hmm, peut-être que c'est assez, ou peut-être pas ...","Surveille ta langue"+GetSexPhrase(", chèvre","")+"...",npchar,Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Ohh, c'est toi encore! "+GetSexPhrase("Et une fois de plus tous ces stupides compliments. Rien ne change jamais dans ce monde... Si ","Juste pour rappeler: si ")+"tu veux"+GetSexPhrase("passe un bon moment","passe un bon moment")+" avec moi, paye le propriétaire de l'établissement. Je ne pourrais pas me soucier moins de tes paroles.";
				Link.l1 = "Ce n'est pas une grande surprise...";
				Link.l1.go = "exit";
			}
		break;
		
        case "HorseChoice_1_Add":
			dialog.text = "Je ne peux pas dire que cela m'a rendu heureux... Dommage.";
			Link.l1 = "Je suis désolé...";
			Link.l1.go = "exit";
			npchar.quest.choice = 0;
		break;
		
		//===>> секс
        case "Horse_ReadyFack":
			// Addon 2016-1 Jason пиратская линейка
			if (pchar.location == "SantoDomingo_Brothel_room" && CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_2" && npchar.name == "Gabriela")
			{
				dialog.text = "Ah, tu es enfin arrivé ! Super ! Nous pouvons parler librement, personne n'écoute...";
				Link.l1 = "Alors, c'était l'Espagnol qui t'a donné l'ambre bleu ?";
				Link.l1.go = "mtraxx_2";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("SantoDomingo");
				break;
			}
			if (!CheckAttribute(npchar, "quest.choice")) npchar.quest.choice = 0;
			switch(npchar.quest.choice)
			{
				case "0":
					dialog.text = RandPhraseSimple("Je suis très heureux de te voir. "+GetSexPhrase("Alors, qu'allons-nous faire ensuite ?","Que diriez-vous de nous amuser un peu ?")+"","Ne sois pas timide"+GetSexPhrase(", faites comme chez vous pendant au moins deux heures.",". Je pourrai vous divertir, n'en doutez pas.")+"");
					Link.l1 = RandPhraseSimple("Je ne pense pas que ce sera ennuyeux...",""+GetSexPhrase("Passons un bon moment, bébé !","Ne perdons pas de temps !")+"");
				break;
				case "1":
					dialog.text = "Oh, c'est toi encore, mon "+GetSexPhrase("glorieux corsaire! Je vous ai promis quelque chose et je suis prêt à tenir ma parole","jolie demoiselle! Vous n'oublierez jamais les deux prochaines heures")+"...";
					Link.l1 = "Maintenant, cela semble tentant...";	
				break;
				case "2":
					dialog.text = "Ohh, te voila enfin. Ne perdons pas de temps!";
					Link.l1 = ""+GetSexPhrase("Ne faisons pas ça, minou...","Montre-moi maintenant ce que tu peux faire...")+"";
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
				dialog.text = "Capitaine, pourquoi êtes-vous si silencieux ?";
				link.l1 = LinkRandPhrase("Eh bien, c'est moi.","Nous parlerons la prochaine fois.",RandPhraseSimple("Je ne te paye pas pour parler.","Mais toi, "+GetSexPhrase("beauté","mon cher")+", n'étaient pas aussi silencieux tout ce temps."));
				link.l1.go = "exit";
				link.l2 = ""+GetSexPhrase("Tu étais simplement magnifique, j'ai presque perdu la tête! C'est une occasion très rare, quand une femme est à la fois si belle et ardente","Ohh, tu sais certainement comment plaire à une femme... Je suis tellement excitée.")+".";
				link.l2.go = "Horse_ReasonToFast_1";
			}
			else
			{
				switch(npchar.quest.choice)
				{
					case "0":
						dialog.text = LinkRandPhrase("Ça vous a plu ?","Alors, que pouvez-vous dire? Est-ce que tout allait bien?","Alors,"+GetSexPhrase("corsaire, est, tout","tout")+" bien ?");
						Link.l1 = RandPhraseSimple(""+GetSexPhrase("Bien sûr, tout va bien","Vous connaissez certainement vos devoirs")+".",""+GetSexPhrase("Tout va bien, bébé","Vous savez, j'étais assez content")+".");
						Link.l1.go = "exit";
					break;
					case "1":
						dialog.text = LinkRandPhrase("Alors, ai-je tenu ma promesse ?","Alors,"+GetSexPhrase(" tu m'as aimé ",", avez-vous aimé cela")+"?","J'espère, "+GetSexPhrase("tu étais content, parce que je suis trè-è-ès content","vous étiez content, parce que j'ai fait de mon mieux")+"Bonjour, monami.");
						Link.l1 = RandPhraseSimple("Ouais, ça m'a beaucoup plu.",""+GetSexPhrase("Nous avons passé un bon moment, tu étais magnifique!","Tout était tout simplement terrifique!")+"");	
						Link.l1.go = "exit";
					break;
					
					case "2":
						dialog.text = RandPhraseSimple("Eh bien, c'est ça, tu dois partir.","Votre temps est révolu,"+GetSexPhrase(" Capitaine,","")+".");
						Link.l1 = RandPhraseSimple("Ouais, à la revoyure...","Au revoir et merci...");
						Link.l1.go = "exit";
					break;
				}
				NextDiag.TempNode = "Horse_AfterSex_2";
			}	
		break;
		
        case "Horse_AfterSex_2":
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && pchar.GenQuest.EncGirl == "Bag_BrothelRoom" && !CheckCharacterItem(pchar, "leather_bag"))
			{
				dialog.text = "Alors, comment avez-vous aimé ici?";
				link.l1 = "Dis-moi beauté, n'as-tu pas vu une sacoche quelque part autour?";
				link.l1.go = "EncGirl_GetBag";
			}
			else
			{
				dialog.text = LinkRandPhrase("Passez encore parfois...","Au revoir. Nous vous attendrons à tout moment...","Nous serons ravis de vous revoir ici...");
				Link.l1 = "D'accord...";
				Link.l1.go = "exit";
				NextDiag.TempNode = "Horse_AfterSex_2";
			}	
		break;
		
		case "EncGirl_GetBag":
			dialog.text = "C'était ce coffre marron avec une poignée ?";
			link.l1 = "Ouais, quelque chose comme ça...";
			link.l1.go = "EncGirl_GetBag1";	
		break;
		
		case "EncGirl_GetBag1":
			dialog.text = "Parce que le propriétaire de ce coffre n'est pas venu, madame l'a emmené dans son boudoir.";
			link.l1 = "Merci, chérie. Au revoir.";
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "Bag_BrothelHostess";
			NextDiag.TempNode = "Horse_AfterSex_2";
		break;
		
		// --> генератор - "A reason to hurry"
		case "Horse_ReasonToFast_1":
			dialog.text = "Alors passez à tout moment, je serai toujours ravi de vous voir. Vous êtes si "+GetSexPhrase("doux, pas comme ces autres","doux, pas comme ces ploucs")+" pas de bonjour, pas d'au revoir, et ils essayent souvent de faire du mal...";
			link.l1 = "Que voulez-vous dire par là?";
			link.l1.go = "Horse_ReasonToFast_2";
		break;
		
		case "Horse_ReasonToFast_2":
			pchar.questTemp.ReasonToFast.speakHorse = true;
			dialog.text = "Il y avait un sergent-chef juste avant toi. D'habitude, il ne nous rend pas visite, mais cette fois un diable l'a amené ici. De plus, il m'a choisi... Il gémissait pendant qu'il était sur moi pendant quelques minutes, puis m'a traité de peu qualifié et s'est précipité vers une anse. Il est parti si vite qu'il a presque laissé son pantalon là-bas, ha-ha-ha...";
			link.l1 = "Ne sais-tu pas, "+GetSexPhrase("beaute","chéri")+", qui sont vraiment les hommes ? Il avait dit à sa femme qu'il allait au bordel pour 'inspection', puis il a dit à sa maîtresse qu'il était pressé d'aller chez sa femme, mais la seule chose qu'il a toujours voulu, c'est aller patrouiller cette crique. "+GetSexPhrase("Ha-ha-ah !..","Ha-ha-ha!")+"";
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
				dialog.text = LinkRandPhrase("Non, chéri, désolé, mais non. Je t'aiderais volontiers, mais je ne peux pas.","Non, "+GetSexPhrase("beau","jeune dame")+", Je n'ai vu aucune bague...","Désolé, mais non. Je n'ai pas vu de bague.");
				link.l1 = "Dommage... Eh bien, merci quand même.";
				link.l1.go = "exit";
			}
			else
			{
				if (npchar.id == "HorseGen_"+reload_location_index+"_1")
				{
					dialog.text = "Voulez-vous dire l'anneau du gouverneur?";
					link.l1 = "Exactement, ma belle!";
					link.l1.go = "TakeMayorsRing_S2";
				}
				else
				{
					dialog.text = LinkRandPhrase("Non, chéri, désolé, mais non. Je t'aiderais volontiers - mais je ne peux pas.","Non, "+GetSexPhrase("beau gosse","jeune dame")+", je n'ai vu aucun anneau...","Désolé, mais non. Je n'ai pas vu de bague.");
					link.l1 = "Dommage... Eh bien, merci quand même.";
					link.l1.go = "exit";
				}
			}
		break;

		case "TakeMayorsRing_S2":
			dialog.text = "Je suis désolé, mais l'anneau m'a été donné en cadeau, donc je ne suis pas obligé de le rendre.";
			link.l1 = "Un cadeau?! Et qui te l'a donné?";
			link.l1.go = "TakeMayorsRing_S3";
		break;
		
		case "TakeMayorsRing_S3":
			dialog.text = "Le gouverneur lui-même, bien sûr !";
			link.l1 = "Mais il était... disons... un peu éméché. Il ne se souvient de rien.";
			link.l1.go = "TakeMayorsRing_S4";
		break;
		
		case "TakeMayorsRing_S4":
			dialog.text = "Et qu'est-ce que j'ai à voir avec ça? S'il était ivre, c'est son problème, pas le mien!";
			link.l1 = "Avez-vous vraiment besoin de vous quereller avec lui ? C'est une bague de mariage, et vous le savez... Rendez-la simplement, une si petite chose ne vaut aucun trouble.";
			link.l1.go = "TakeMayorsRing_S5";
		break;
		
		case "TakeMayorsRing_S5":
			if (rand(1) && sti(pchar.money)>5000)
			{
				dialog.text = "Eh bien, je rendrai la bague, mais tu me paieras cinq mille pesos.";
				link.l1 = "D'accord, prenez votre argent et donnez-moi l'anneau.";
				link.l1.go = "TakeMayorsRing_S6";
			}
			else
			{
				dialog.text = "Oh, eh bien. Laissez-le l'avoir!";
				link.l1 = "C'est sûr, ma chérie !";
				link.l1.go = "exit";
				GiveItem2Character(pchar, "MayorsRing");
				pchar.questTemp.different.TakeMayorsRing = "HorseTakenRing";
				AddQuestRecord("SeekMayorsRing", "3");
				AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
				AddQuestUserData("SeekMayorsRing", "sName", GetFullName(npchar));
			}
		break;
		
		case "TakeMayorsRing_S6":
			dialog.text = "Voila pour toi...";
			link.l1 = "D'accord, alors. Merci pour l'aide, cheri.";
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
			dialog.text = "Vous voyez, nous avons un client désagréable - "+pchar.GenQuest.Badboy.Brothel.Name+". Et il nous ennuie vraiment à chaque fois qu'il vient ! D'abord, il se saoule à la taverne, puis il vient ici, choisit une fille et fait un boucan violent\nEt le pire, c'est qu'il est de noble descendance ! Il est un parent éloigné de notre gouverneur, donc nous sommes forcés de subir toutes ses escapades. Peut-être pourriez-vous faire en sorte que ce jeune homme effronté... eh bien... se calme un peu... pour qu'il arrête de visiter mon établissement ?";
			link.l1 = "Un parent du gouverneur, dites-vous ? Hmmm... Je préférerais ne pas entrer en confrontation avec les autorités. Je suis vraiment désolé.";
			link.l1.go = "exit";
			link.l2 = "Je pense que je peux arranger ça. Dites-moi, où puis-je trouver ce vaurien?";
			link.l2.go = "Badboy_1";
		break;
		
		case "Badboy_1":
			dialog.text = "D'habitude, à cette heure-ci, il est déjà à la taverne. Il s'y enivre puis vient me rendre visite.";
			link.l1 = "Je vois. Eh bien, je le rencontrerai probablement là-bas.";
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
			dialog.text = "Oh, tu es un vrai homme, n'est-ce pas? J'ai toujours su que je pouvais compter sur toi..";
			link.l1 = "Je suis toujours heureux d'aider une si gentille dame et ses... pupilles.";
			link.l1.go = "Badboy_complete_1";
		break;
		
		case "Badboy_complete_1":
			dialog.text = "Vous n'êtes pas seulement courageux, mais aussi très galant. Je voudrais vous remercier d'une manière spéciale - d'une manière qu'une femme seule peut remercier un homme. Vous n'oublierez jamais cela, je le promets. Montez à l'étage, brave marin...";
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
			dialog.text = "Il y a un homme et il me doit de l'argent... Je ne sais pas comment le dire...";
			link.l1 = "Aucun mot ! Je le trouverai et le secouerai jusqu'au dernier peso juste pour un regard de tes yeux insondables ! Dis-moi simplement son nom !";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "Non, non, vous ne m'avez pas bien compris, Capitaine ! Cet homme... ne lui faites rien de mal. Rappellez-lui simplement ses dettes. Son nom est Hugo Avendell, et je suppose que vous le trouverez là où l'on vend de l'alcool très bon marché. Par pitié pour Dieu, ne lui faites pas de violence !\nDites-lui simplement... rappellez-lui qu'il avait promis de payer. Je ne veux pas contacter la garde, mais j'ai des amis officiers, alors dites-lui que j'attends, et avec tout le respect qui lui est dû, je serai contraint d'agir au plus tard demain. Rappellez-lui simplement sa promesse.";
			link.l1 = "Votre parole est ma loi, madame. Je remplirai volontiers votre demande.";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			DialogExit();
			//создаем Хьюго
			sld = GetCharacter(NPC_GenerateCharacter("Avendel", "Hugh", "man", "man", 10, HOLLAND, -1, true, "quest"));
			FantomMakeCoolFighter(sld, 20, 50, 50, "blade_04", "pistol1", "bullet", 50);
			sld.name = "Hugo";
			sld.lastname = "Avendell";
			sld.dialog.FileName = "Quest\Portugal_dialog.c";
			sld.dialog.currentnode = "Avendel_tavern";
			sld.greeting = "avendel_1";
			sld.rank = 12;
			LAi_SetHP(sld, 80, 80);
			SetSelfSkill(sld, 10, 12, 10, 10, 70);
			SetShipSkill(sld, 50, 75, 15, 15, 25, 55, 10, 15, 30);
			SetSPECIAL(sld, 3, 8, 3, 10, 10, 3, 6);
			SetCharacterPerk(sld, "BasicCommerce");
			SetCharacterPerk(sld, "AdvancedCommerce");
			SetCharacterPerk(sld, "BasicBattleState");
			SetCharacterPerk(sld, "AdvancedBattleState");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "Gunman");
			GiveItem2Character(sld, "blade_12");
			sld.equip.blade = "blade_12";
			GiveItem2Character(sld, "pistol1");
			EquipCharacterbyItem(sld, "pistol1");
			TakeNItems(sld, "bullet", 10);
			AddItems(sld, "gunpowder", 10);
			LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "bullet");
			LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
			LAi_SetImmortal(sld, true);
			LAi_SetSitType(sld);
			FreeSitLocator("Marigo_tavern", "sit_front1");
			ChangeCharacterAddressGroup(sld, "Marigo_tavern", "sit", "sit_front1");
			AddLandQuestMark(sld, "questmarkmain");
			SetFunctionTimerCondition("Portugal_BeginOver", 0, 0, 2, false);
			pchar.questTemp.Portugal = "begin";
		break;
		
		case "Portugal_exit":
			dialog.text = "Merci, capitaine. J'espère qu'il fera preuve de la prudence nécessaire.";
			link.l1 = "Je suis sûr de cela, madame. Permettez-moi maintenant de prendre congé.";
			link.l1.go = "exit";
			sld = characterFromId("Avendel");
			sld.lifeday = 0;
			pchar.questTemp.Portugal = "end";
		break;
		
		case "Portugal_3":
			AddMoneyToCharacter(pchar, -10000);
			dialog.text = "Oh non ! Ne me dites pas que vous lui avez fait quelque chose de terrible... Il n'avait pas d'argent, et je le savais ! Nous avons simplement grandi dans la même petite ville, je ne me serais jamais tourné vers les gardes ! Je voulais juste lui faire peur un peu... pour le secouer avant qu'il ne se noie dans la bouteille !";
			link.l1 = "Hmm... Néanmoins, voici ton argent. Et ne t'inquiète pas pour Hugo, il va bien... Du moins, il le sera s'il se remet à jeun.";
			link.l1.go = "Portugal_4";
		break;
		
		case "Portugal_4":
			dialog.text = "Oh, Capitaine, vous ne comprenez pas ! Il faisait partie de... eh bien, vous savez, ce qu'on appelle des chasseurs de primes - des mercenaires, ils traquent les pirates et les voleurs et les éliminent. Mais, il n'a pas été le plus chanceux, pour dire le moins\nIl n'y a pas si longtemps, il a finalement fait des folies et a perdu son équipage et son navire, depuis lors il flotte au fond de sa chope, jour après jour. Moi, pour le vieux souvenir, je lui permets de venir ici de temps en temps. Il est si... si pitoyable maintenant. Il était l'homme le plus beau de notre ville sur la côte de La Manche, et regardez-le maintenant\nJe sais qu'il vous a promis quelque chose, et que vous avez payé de votre poche ! Je vous donnerai cet argent, ne lui faites juste rien de mal, je vous en supplie, capitaine !";
			link.l1 = "D'accord, très bien, madame, j'ai compris. Gardez l'argent, il est à vous. Quant à votre ami, je promets que je ne lui ferai pas de mal. Et maintenant permettez-moi de prendre congé, j'ai des affaires à régler. De plus, j'étais heureux d'aider une si belle dame.";
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
            dialog.text = "Chut, garde ta voix basse... Va demander à Madame Lolita d'avoir un rendez-vous avec moi. Puis monte à l'étage, où nous pourrons parler librement. Et pas un mot jusqu'à ce moment... Hé, marin, va payer à Madame avant de me toucher ! (rie) ";
			link.l1 = "Sur mon chemin, ma chérie...";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
           DialogExit();
		   chrDisableReloadToLocation = false;
		   pchar.questTemp.Mtraxx = "jewelry_2";
		break;
		
		case "mtraxx_2":
			pchar.quest.Mtraxx_JewelrySDMOver.over = "yes"; //снять таймер
            dialog.text = "Non, pas moi. Je vais te raconter toute l'histoire, ne m'interromps simplement pas.";
			link.l1 = "Je suis tout ouïe!";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = "D'accord alors. Il y a environ une semaine, un navire militaire est arrivé à Santo Domingo. Il était endommagé, soit par une tempête, soit par un combat, alors les réparations ont commencé immédiatement et l'équipage a déménagé au fort. Son capitaine, cependant, a passé tout son temps libre ici. Pendant deux jours d'affilée, il a bu et se détendait en compagnie de l'une de nos filles. C'est elle qui a obtenu la pierre précieuse, et pas seulement une. Elle s'en vantait sans fin - Lolita nous laisse garder les cadeaux des clients. La pauvre fille ne connaissait même pas la vraie valeur du cadeau, alors que je l'ai évalué tout de suite. Quand elle m'a parlé du capitaine ivre qui se vantait d'une montagne remplie d'ambres, j'ai aussitôt envoyé une lettre à Tyrex...";
			link.l1 = "";
			link.l1.go = "mtraxx_4";
		break;
		
		case "mtraxx_4":
            dialog.text = "D'ici la prochaine arrivée du capitaine, j'ai tout arrangé pour que sa fille préférée soit occupée avec un autre client, et j'ai obtenu le 'travail' pour moi-même. J'ai essayé de lui soutirer les coordonnées, hélas, en vain. Il n'a cessé de se vanter de comment il deviendrait aussi riche que Crassus et retournerait dans le Vieux Monde. Pas un mot sur l'emplacement. La seule chose que j'ai découverte, c'est que son navire était réparé et qu'il allait naviguer vers La Havane, où il essaierait d'organiser une mission dans la bonne direction. Après tout, il n'est pas le propriétaire du navire.";
			link.l1 = "Alors, il est à La Havane maintenant?";
			link.l1.go = "mtraxx_5";
		break;
		
		case "mtraxx_5":
            dialog.text = "S'est éloigné il y a deux jours à l'aube. Tu es le marin ici, tu fais le comptage.";
			link.l1 = "Le nom du capitaine, le type de son bateau et son nom, quoi d'autre?";
			link.l1.go = "mtraxx_6";
		break;
		
		case "mtraxx_6":
            dialog.text = "Quoi, tu me prends pour un imbécile ? Son nom est Esberdo Cabanas, capitaine du Cantavro. Je pense que les marins l'appelaient une goélette.";
			link.l1 = "Et c'est tout ce que tu sais ?";
			link.l1.go = "mtraxx_7";
		break;
		
		case "mtraxx_7":
            dialog.text = "Que voulez-vous de plus? Je suis sûr que vous pourriez le rattraper avant La Havane. Ne perdez pas de temps cependant, je ne pense pas qu'il prendra un long repos avant de quitter Cuba vers sa cachette, et alors c'est une cause perdue. À la réflexion, vous pourriez rester une heure ou deux, après tout vous avez payé pour ça.";
			link.l1 = "Bon point, chérie. Deux heures ne feront pas beaucoup de différence...";
			// belamour legendary edition -->
			link.l1.go = "mtraxx_7S";
			link.l2 = "Une autre fois, cher. Pensez à vous offrir une pause déjeuner. Allez à l'église, ou quelque chose d'autre.";
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
            dialog.text = "O-oh... Quel dommage. Et je pensais que vous étiez ici en vacances. Mes filles manquent tellement aux courageux corsaires. Très bien alors, parle, quelle est la tâche ?..";
			link.l1 = "Marcus m'a chargé d'organiser une sacrée fête dans ton établissement pendant deux jours, de boire tout le vin et de coucher avec toutes les filles. Quand est-ce qu'on commence?";
			link.l1.go = "mtraxx_R1";
		break;
		
		case "mtraxx_R1":
            dialog.text = "Ah, Charlie Prince, ton humour est aussi tranchant que ton sabre! Tu m'as presque contrarié ... Filles! Nous avons un invité, un invité spécial! Apportez du vin et des repas!";
			if (sti(pchar.money) >= 31000)
			{
				link.l1 = "Appelez toutes les jolies filles ici! Nous allons nous reposer et nous amuser! Yo-ho-ho!..";
				link.l1.go = "mtraxx_R2";
			}
			else
			{
				link.l1 = "Attendez une minute, Janette. Je dois récupérer l'or de mon navire pour toi et tes dames. A tout à l'heure!";
				link.l1.go = "exit";
				pchar.questTemp.Mtraxx.Retribution = "brothel_repeat";
				chrDisableReloadToLocation = false;
			}
		break;
		
		case "mtraxx_R2":
			AddMoneyToCharacter(pchar, -30000);
            dialog.text = "Je voudrais que tous nos clients soient aussi doux, beaux et généreux que vous... Nous allons vous offrir une détente parfaite. Les filles!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionInBrothel");
		break;
		// belamour ночной приключенец
		case "NA_Girl":
            dialog.text = "Oh, donc nous avons un connaisseur ici, hi hi ... Eh bien, eh bien, j'ai une telle fille. Mais elle n'est pas bon marché : "+makeint(pchar.GenQuest.NightAdventure_money)+" pesos."; 
			link.l1 = "Marché conclu.";
			link.l1.go = "NA_Girl_1";
		break;
		
		case "NA_Girl_1":
			AddMoneyToCharacter(pchar, -makeint(pchar.GenQuest.NightAdventure_money));
            dialog.text = "C'est génial, cher. La Prêtresse de l'Amour vous attendra à l'étage. Croyez-moi, vous ne le regretterez pas."; 
			link.l1 = "Je ne le fais déjà pas.";
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
			dialog.text = "Pour vous et m'sieur Agueybana? Bien sûr que vous le faites. Ce sera dix mille, capitaine.";
			if (sti(pchar.money) >= 10000) {
				link.l1 = "Attends, pas comme ça !.. Zut ! Peu importe, voici ta paye.";
				link.l1.go = "chicken_god_pay";
			} else {
				link.l2 = "Puis-je obtenir un prêt?";
				link.l2.go = "chicken_god_notpay";
			}
		break;
		
		case "chicken_god_pay":
			dialog.text = "Profitez de votre séjour, capitaine. Veuillez revenir quand nous sommes ouverts. Notre établissement offre toutes sortes de loisirs pour les hommes et les femmes nobles.";
			link.l1 = "...";
			link.l1.go = "chicken_god_pay_1";
		break;
		
		case "chicken_god_pay_1":
			dialog.text = "";
			link.l1 = "Madame "+npchar.name+", pouvez-vous au moins expliquer ce qui se passe ici ? Le gouverneur est-il même au courant que vous avez eu un indigène aux commandes pendant un mois ? Aucune colonie ne peut survivre à la fermeture d'un bordel pendant une journée, je peux vous le dire !";
			link.l1.go = "chicken_god_pay_2";
		break;
		
		case "chicken_god_pay_2":
			dialog.text = "La chambre est à vous, capitaine. Maintenant, si vous voulez bien m'excuser.";
			link.l1 = "Charmant. Au revoir, madame.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_PayForRoom");
		break;
		
		case "chicken_god_notpay":
			dialog.text = "Pourquoi, Seigneur, pourquoi? Sortez d'ici! Allez-vous-en, allez-vous-en, je ne peux plus le supporter! Salaud!";
			link.l1 = "Cela s'est bien passé.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_NotPayForRoom");
		break;
		
		//-->> Sinistra Ром на троих
		case "RomNaTroih_1":
			dialog.text = "Mhm... Je ne fais pas habituellement cela... mais je suis prêt à prendre le risque pour toi. C'est ton jour de chance, Capitaine!";
			link.l1 = "Allons-y !";
			link.l1.go = "exit";
			pchar.RomNaTroih_Shluha = npchar.id;
		break;
		
		case "RomNaTroih_2":
			dialog.text = "Je suis en colère contre toi, Capitaine... Mais je te montrerai de la miséricorde si tu travailles assez dur pour cela.";
			link.l1 = "Oh, je le ferai. Ouvrons-nous du vin?";
			link.l1.go = "exit";
			Achievment_Set("ach_CL_105");
		break;
		//<<-- Sinistra Ром на троих
		
		//--> прибыла инспекция на Святом Милосердии
		case "SantaMisericordia_1":
			dialog.text = "Jusqu'à ce que ce maudit de Alamida parte. Maudit saint homme...";
			link.l1 = "Mais peut-être...";
			link.l1.go = "SantaMisericordia_2";
		break;
		
		case "SantaMisericordia_2":
			dialog.text = "Non peut-etre. Et s'il entre ici tout de suite? Tout le monde dehors.";
			link.l1 = "Bonjour, monami.";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
		break;
		//<-- прибыла инспекция на Святом Милосердии
		
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

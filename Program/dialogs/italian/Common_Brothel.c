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
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase(""+GetSexPhrase("Che ragazze, cara?! Metà della guarnigione ti sta cercando, e tu vieni direttamente al bordello!","Sparisci, vuoi? Metà della guarnigione ti sta cercando!")+"","Ogni guardia della città ti sta cercando. Non sono una sciocca da offrirti i miei servizi in questo momento ...","Non hai nulla da fare qui!"),LinkRandPhrase(""+GetSexPhrase("Osate solo toccare le mie ragazze e vi scuoterò vivo!","Vattene, sei un bruto!")+"","Sporco"+GetSexPhrase("","")+" assassino, lascia subito il mio locale! Guardie!!!","Non ho paura di te, "+GetSexPhrase("birbante","ratto")+"! Presto sarai impiccato nella nostra fortezza, non andrai lontano..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Eh, un allarme non è mai un problema per me...","Non mi prenderanno mai."),RandPhraseSimple("Basta parlare, vecchia stupida.","Taci se non vuoi problemi..."));
				link.l1.go = "exit";
				break;
			}
			//--> прибыла инспекция на Святом Милосердии
			if (CheckAttribute(npchar, "quest.SantaMisericordia"))
			{
				dialog.text = "Oh, "+GetSexPhrase("giovane uomo","dolce bambino")+", siamo chiusi oggi.";
				link.l1 = "Chiuso?";
				link.l1.go = "SantaMisericordia_1";
				break;
			}
			//<-- прибыла инспекция на Святом Милосердии
			//--> Мерзкий Божок
			if (CheckAttribute(pchar, "questTemp.ChickenGod.HostessDialog")) {
				dialog.text = "Oh, mio Dio! Come sei entrato qui? Caro capitano, per favore vai via - ti prego! La nostra casa è attualmente chiusa!";
				link.l1 = "Buono vederti, caro "+npchar.name+". Ero sulla lista degli ospiti. Tuttavia, in tali stabilimenti, anche gli ospiti devono pagare, quindi... Per favore, non rendere questo troppo difficile per me, ma voglio pagare per una stanza.";
				link.l1.go = "chicken_god";
				
				DeleteAttribute(pchar, "questTemp.ChickenGod.HostessDialog");
				break;
			}
			//<-- Мерзкий Божок
			//--> туториал Мартиника
			if (CheckAttribute(pchar, "questTemp.Sharlie.Gigolo") && pchar.questTemp.Sharlie.Gigolo == "start" && npchar.location == "FortFrance_SecBrRoom")
			{
				DelLandQuestMark(npchar);
				link.l1 = "Ascolta, Aurora, ho bisogno di una ragazza per la notte. E voglio portarla a casa con me. Puoi organizzare questo?";
                link.l1.go = "Gigolo";
				break;
			}
			//<-- туториал Мартиника
			//Jason --> Заносчивый аристократ
			if (!CheckAttribute(pchar, "GenQuest.Badboy") && !CheckAttribute(npchar, "quest.Badboy") && !CheckAttribute(pchar, "questTemp.ZA.block") && makeint(environment.time) > 15.0 && makeint(environment.time) < 21.0 && sti(pchar.questTemp.HorseQty) > 4)
			{
				dialog.text = "Sei un uomo così distinto. Inoltre, alle mie ragazze piaci molto. Vorrei chiederti un piccolo favore per il mio stabilimento.";
				link.l5 = "Sono lusingato, questo è certo. Con cosa hai bisogno del mio aiuto?";
				link.l5.go = "Badboy";
				link.l8 = "Mi dispiace, ma sono occupata al momento.";
				link.l8.go = "exit";
				npchar.quest.Badboy = "true";
				break;
			}
			
			if (CheckAttribute(pchar, "GenQuest.Badboy.Complete") || CheckAttribute(pchar, "GenQuest.Badboy.Continue"))
			{
				if (npchar.City == pchar.GenQuest.Badboy.Brothel.City)
				{
					dialog.text = "Oh, sei tornato! Hai sistemato per quello "+pchar.GenQuest.Badboy.Brothel.Name+" per lasciare in pace le mie ragazze?";
					link.l5 = "Sì. Non mostrerà più il suo volto qui.";
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
					dialog.text = "Capitano, posso chiederti un favore?";
					link.l5 = "Per te, signora, tutto quello che vuoi! Sono al tuo servizio!";
					link.l5.go = "Portugal";
					link.l8 = "Mi dispiace, ma sono occupato al momento.";
					link.l8.go = "exit";
					npchar.quest.Portugal = "true";
					break;
				}
			}
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "HostressMoney" && npchar.location == "Marigo_SecBrRoom")
			{
				DelLandQuestMark(npchar);
				dialog.text = "Hai parlato con Hugo, mio capitano?";
				if (sti(pchar.money) >= 10000)
				{
					link.l1 = "Inoltre, signora, ecco i vostri soldi. Tutto è andato nel modo più favorevole...";
					link.l1.go = "Portugal_3";
				}
				else
				{
					link.l1 = "Sì, gli ho trasmesso la tua richiesta.";
					link.l1.go = "Portugal_exit";
				}
				break;
			}
			//<--Португалец
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "brothel" && npchar.location == "Tortuga_SecBrRoom")
			{
				dialog.text = "Oh mamma, guarda questo! Charlie Prince, un famoso corsaro! In carne ed ossa!";
				link.l1 = RandSwear()+"Ciao, Janette. Sono qui per una missione per Marcus Tyrex.";
				link.l1.go = "mtraxx_R";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "brothel_repeat" && npchar.location == "Tortuga_SecBrRoom")
			{
				dialog.text = "Sei pronto per un trattamento rigenerante indimenticabile, mio coraggioso corsaro?";
				if (sti(pchar.money) >= 31000)
				{
					link.l1 = "Lo sono! Charlie Prince non spreca parole come spreca soldi, ah-ah!";
					link.l1.go = "mtraxx_R2";
				}
				else
				{
					link.l1 = "Quasi... Credo di aver perso una borsa nel vostro stabilimento... Tornerò con dei soldi!";
					link.l1.go = "exit";
				}
				break;
			}
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = RandPhraseSimple(TimeGreeting()+". Benvenuto nella mia casa dell'amore. Il mio nome è "+npchar.name+", e sono il proprietario. "+GetSexPhrase("Cosa posso fare per te, "+GetAddress_Form(NPChar)+"?","Sinceramente, sono un po' sorpreso di vederti qui, "+GetAddress_Form(NPChar)+", ma ti assicuro che offriamo servizi non solo per gli uomini.")+"",TimeGreeting()+". Ti do il benvenuto, "+GetSexPhrase("straniero","signorina")+", al mio umile stabilimento. Permettimi di presentarmi, io sono "+NPChar.Name+" - titolare di questo rifugio per uomini affamati di un tocco femminile. "+GetSexPhrase("Cosa posso fare per te?","Anche se abbiamo una cosa o due per le signore...")+"");
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = RandPhraseSimple(TimeGreeting()+". Come posso aiutarti, "+GetAddress_Form(NPChar)+"?",TimeGreeting()+". Cosa posso fare per te, "+GetAddress_Form(NPChar)+"?");
			}
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Gigolo"))//не идёт квест девочки
			{
				if (!CheckAttribute(pchar, "GenQuest.BrothelLock"))// нет запрета от Мэри 280313
				{
					link.l2 = npchar.name+", Voglio trascorrere un po' di tempo di qualità con una delle tue ragazze.";
					link.l2.go = "Hostess_1";
				}
			}
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock")) // не идёт старт Шарля
			{
				if (sti(pchar.ship.type) != SHIP_NOTUSED && GetCrewQuantity(pchar) > 0) // Rebbebion - а смысл, если нет как корабля, так и команды?
				{
					link.l3 = "È passato un po' di tempo dall'ultima volta che ho viziato i miei uomini. Posso fare un ordine all'ingrosso di ragazze per i miei ragazzi?";
					link.l3.go = "ForCrew";
				}
			}
			link.l4 = "Ho una domanda.";
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
				link.l5 = "Ascolta, "+npchar.name+", Sto cercando l'anello del governatore. Si è riposato nel vostro stabilimento e probabilmente l'ha perso qui.";
				link.l5.go = "TakeMayorsRing_H1";
				SaveCurrentNpcQuestDateParam(npchar, "TakeMayorsRing");
			}
			//<<-- квест поиска кольца мэра

			// belamour ночной приключенец -->
			if(CheckAttribute(pchar, "GenQuest.NightAdventureVar") && pchar.GenQuest.NightAdventureVar == "NightAdventure_NobleWhoreMoney")
			{
				link.l8 = "Guarda, vorrei prendere la migliore ragazza che hai.";
				link.l8.go = "NA_Girl";
			}
			// <-- приключенец
			link.l9 = "Non importa, sto già andando via.";
			link.l9.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "ShipLetters_1":
				pchar.questTemp.different.GiveShipLetters.speakBrothelMadam = true;
				dialog.text = RandPhraseSimple("Cosa desideri, bello?","Ti sto ascoltando, Capitano.");
				link.l1 = "Ascolta, "+npchar.name+", Ho trovato questi documenti in una stanza privata della vostra istituzione ...";
				link.l1.go = "ShipLetters_2";				
		break;
		
		case "ShipLetters_2":
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Lasciami vedere! Hmm... qualche capitano ha perso i suoi documenti, giusto? Penso che dovresti chiedere al maestro del porto a questo riguardo.";
				link.l1 = "Forse, forse...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Lasciami dare un'occhiata! Oh! A giudicare dal nome, appartengono al mio stimato cliente e un degno cittadino della nostra città. Posso consegnare io stesso questi documenti a lui.";
				link.l1 = "Probabilmente, no...";
				link.l1.go = "exit";
				link.l2 = "Eccellente! Sempre felice di aiutare una brava persona e un locale degno.";
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
					dialog.text = ""+GetSexPhrase("Siamo sempre felici di servire un cliente. Ora dimmi, bello - hai già scelto qualcuno o non ti importa molto?","Beh, le mie ragazze sono certamente in grado di... aiutarti. Hai già scelto qualcuna o non te ne importa molto?")+"";
					Link.l1 = ""+GetSexPhrase("Eh, ho solo bisogno di una prostituta e ne ho bisogno subito. Non mi importa quale, le tue ragazze mi sembrano tutte belle...","Va bene chiunque conosca i suoi doveri, ovviamente...")+"";
					Link.l1.go = "Hostess_NotChoice";	
					Link.l2 = "Sì, ce n'è una, "+GetSexPhrase("chi ha attirato la mia attenzione...","lei sarebbe la più carina...")+"";
					Link.l2.go = "Hostess_Choice";
				}
				else
				{
					dialog.text = "Non ho ragazze libere per te oggi, abbiamo già troppi clienti. Vieni domani, e non te ne pentirai!";
					Link.l1 = "Peccato, avevo appena iniziato a divertirmi.";
					Link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Mmm. Hai già pagato per la ragazza. Non distrarmi, per favore.";
				Link.l1 = "Bene, sto arrivando.";
				Link.l1.go = "exit";	
			}
		break;

        case "Hostess_NotChoice":
			sld = GetFreeHorseRef(npchar.city);
			location = &locations[FindLocation(npchar.city + "_Brothel")];
			if (sld.id == "none" || GetNpcQuestPastDayParam(location, "Brothel_date") > 98)
			{
				dialog.text = "Non ho ragazze disponibili al momento, dovrai tornare tra un paio di giorni.";
				Link.l1 = "Bene, come dici tu.";
				Link.l1.go = "exit";	
			}
			else
			{
				// belamour legendary edition Орден Святого Людовика -->
				if(IsEquipTalisman9() && npchar.nation == FRANCE)
				{
					dialog.text = ""+GetSexPhrase("Bene, stallone, è eccellente!","Le ho tutte abili, puoi esserne sicuro.")+"Posso offrire una bella ragazza chiamata "+GetFullName(sld)+", è libera adesso.\nOh, cosa nascondi così modestamente lì?! Questa è la più alta onorificenza in Francia? Si dice che i portatori di questo distintivo siano leggendari non solo sul campo di battaglia... Beh, capisci a cosa mi riferisco, mio filibustiere... Inoltre, chiunque considererebbe un onore toccare il tuo 'Ordine', quindi oggi riposi a spese della mia istituzione. Rifiuti non sono accettati, bello.";
					Link.l1 = "Certo che sono d'accordo, quali domande potrebbero esserci?!";
					Link.l1.go = "Hostess_NotChoice_agree";	
					npchar.quest.choiceIdx = sld.index;
					break;
				}
				// <-- legendary edition
				dialog.text = ""+GetSexPhrase("Bene, eccellente, mio stallone!","Sono tutte molto abili in quello che fanno, non avere dubbi.")+" Posso offrirti una ragazza molto carina, si chiama "+GetFullName(sld)+", e al momento è libera. Quel piacere ti costerà "+FindRussianMoneyString(sti(sld.quest.price)+charWhoreCost)+". D'accordo?";
				Link.l1 = "No. Immagino di no. È troppo costoso...";
				Link.l1.go = "exit";
				if (sti(pchar.money) >= (sti(sld.quest.price) + charWhoreCost))
				{
					Link.l2 = "Certo, come potrei rifiutare?!";
					Link.l2.go = "Hostess_NotChoice_agree";	
					npchar.quest.choiceIdx = sld.index;
				}
				else
				{
					Link.l1 = "Cavolo, non ho così tanti soldi con me...";
					Link.l1.go = "exit";
				}
			}
		break;
		
        case "Hostess_NotChoice_agree":
			sld = &characters[sti(npchar.quest.choiceIdx)];
			if (sti(pchar.money) >= (sti(sld.quest.price) + charWhoreCost))
			{
				dialog.text = "Bene, "+GetSexPhrase("affascinante","bella")+". "+sld.name+" ti aspetterà in una stanza privata al secondo piano.";
				Link.l1 = ""+GetSexPhrase("Bene, sto arrivando, allora","Bene, allora sto arrivando")+"...";
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
				dialog.text = "Oh, vedi, il problema è che "+sld.name+" non è una ragazza a buon mercato, il suo prezzo è "+FindRussianMoneyString(sti(sld.quest.price)+charWhoreCost)+". E vedo che al momento semplicemente non puoi permetterti di averla. Torna quando sarai ricco"+GetSexPhrase(", caro","")+"...";
				Link.l1 = "Questa è la mia fortuna...";
				Link.l1.go = "exit";
			}
		break;

        case "Hostess_Choice":
			dialog.text = "Sono sempre felice quando le ragazze e i clienti sviluppano sentimenti calorosi l'uno per l'altro... Dimmi il suo nome.";
			Link.l1.edit = 9;
			Link.l1 = "";
			Link.l1.go = "Hostess_Choice_1";	
		break;
		
        case "Hostess_Choice_1":
			sld = CheckHorsesName(npchar.city, 9);
			if (sld.id == "none")
			{
				dialog.text = "Mmm... devi esserti sbagliato. Non ho una tale ragazza nel mio stabilimento. Forse hai sbagliato il suo nome.";
				Link.l1 = "Mmm... ma ho appena parlato con lei.";
				Link.l1.go = "Hostess_Choice_2";				
				Link.l2 = "Forse. Sarebbe meglio chiederle nuovamente il suo nome, giusto per essere sicuri. Ne parlerò con te più tardi.";
				Link.l2.go = "exit";	
			}
			else
			{
				dialog.text = GetFullName(sld)+", stai parlando di lei?";
				Link.l1 = "Sì, riguardo a lei.";
				Link.l1.go = "Hostess_NotChoice_agree";				
				Link.l2 = "No, non è lei.";
				Link.l2.go = "Hostess_Choice_2";
				npchar.quest.choiceIdx = sld.index;
			}
		break;
		
        case "Hostess_Choice_2":
			dialog.text = "Allora forse, dovresti dirmi di nuovo il suo nome, e magari capirò, di chi stai parlando.";
			Link.l1.edit = 9;
			Link.l1 = "";
			Link.l1.go = "Hostess_Choice_1";
			Link.l2 = "Forse. Sarebbe meglio chiederle di nuovo il suo nome, giusto per essere sicuro. Ne parlerò con te più tardi.";
			Link.l2.go = "exit";	
		break;
		//==> команда
		case "ForCrew":
			dialog.text = "Mmm... Vuoi aiutare i tuoi ragazzi a 'sfogarsi un po''? Vedi, il mio stabilimento è uno rispettabile, e ho le ragazze migliori in giro. Ma conosco diverse ragazze del porto, e saranno felici di accontentare tutti i tuoi marinai. Ti costerà "+FindRussianMoneyString(GetCrewQuantity(pchar)*crewWhoreCost)+".";			
			link.l1 = "Bene, sono d'accordo.";
			link.l1.go = "ForCrew_1";
			link.l2 = "Immagino che possano farne a meno...";
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
		        dialog.text = "Non è affar mio, ma penso che prima dovresti guadagnare abbastanza denaro per assumere un equipaggio, e solo allora preoccuparti del suo spirito.";
			    link.l1 = "Hai probabilmente ragione...";
			    link.l1.go = "exit";
		    }
		break;
		
		case "Woman_FackYou":
			dialog.text = "Cara, ma cosa stai facendo?! E sembravi un capitano decente... Questa volta non 'volerai' via, bello. Le guardie ti taglieranno le ali...";
			link.l1 = "Taci, vecchia strega.";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		
		//поиски кольца губернатора
		case "TakeMayorsRing_H1":
			dialog.text = "Non ho trovato nessun anello.";
			link.l1 = "E le tue ragazze?";
			link.l1.go = "TakeMayorsRing_H2";
		break;
		
		case "TakeMayorsRing_H2":
			dialog.text = "Anche loro non lo hanno. Se un cliente dimentica o perde qualcosa, le mie ragazze me lo portano. Ma nessuno mi ha portato l'anello del governatore.";
			link.l1 = "Capisco... Ma potrebbe essere che hanno deciso di tenerlo per sé?";
			link.l1.go = "TakeMayorsRing_H3";
		break;
		
		case "TakeMayorsRing_H3":
			dialog.text = "Poco probabile. Alle ragazze è permesso tenere i regali dai clienti, ma è tutto.";
			link.l1 = "Capisco. Beh, grazie, "+npchar.name+".";
			link.l1.go = "exit";
		break;
		
		case "Hostess_inSexRoom":
			dialog.text = "Oh, eccoti qui...";
			link.l1 = "Eccomi qui, mia signora!";
			link.l1.go = "exit";
			pchar.quest.SexWithHostess_null.over = "yes"; //нулим таймер на не пришёл
			NextDiag.TempNode = "First time";
			if (CheckAttribute(pchar, "questTemp.RomNaTroih_Pogovoril"))
			{
				sld = CharacterFromID(pchar.RomNaTroih_Shluha);
				dialog.text = ""+sld.name+"! Il mio eroe, vedo che non hai sprecato il tuo tempo al piano di sotto!";
				link.l1 = "Spero che mi perdonerai questa debolezza, mia regina?";
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
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("È meglio che tu lasci l'istituzione!","Tutte le guardie in città ti stanno cercando! È meglio per te andartene...","Hai combinato un disastro e ora ti presenti qui?! No, non questa volta..."),LinkRandPhrase("Vattene!","Assassino sporco, vai via da qui! Guardie!","Non ho paura di te,"+GetSexPhrase("birbone","ratto")+"! Presto sarai impiccato nel nostro forte, non andrai lontano..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Eh, un allarme non è mai un problema per me...","Non mi prenderanno mai."),RandPhraseSimple("Ehi, che stupida femmina sei...","Chiudi quella bocca, puttana, o la chiuderò con qualcos'altro..."));
				link.l1.go = "exit";
				break;
			}
			dialog.text = NPCStringReactionRepeat("Ciao, "+GetAddress_Form(NPChar)+""+GetSexPhrase("",", hihi..")+". Devi vedere la madama e compilare l'ordine.","Di nuovo tu? Per favore, parla con la padrona. È nel suo ufficio.","Guarda, "+GetAddress_Form(NPChar)+""+GetSexPhrase(", Spero davvero che tu sia ostinato in altre cose come lo sei nel parlare... Di nuovo","Di nuovo")+"Ti chiedo di vedere il proprietario del locale.","Oh, "+GetAddress_Form(NPChar)+""+GetSexPhrase(", non sei proprio uno testardo!",", Hee-hee... Sei proprio un tipo ostinato, vero?")+"Devi vedere la madam e compilare l'ordine.","blocca",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Bene, "+GetSexPhrase("bellezza, ","")+"Ce l'ho fatta"+GetSexPhrase("","")+".","Già, certo...",""+GetSexPhrase("Non avere dubbi, bella mia, sono ostinato e forte come un toro!","Sì, sì...")+"",""+GetSexPhrase("Oh inferno, devo aver perso qualcosa... Mi dispiace, cara.","Bene, va bene.")+"",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			Link.l2 = "E dove è lei?";
			Link.l2.go = "Horse_1";
			Link.l3 = LinkRandPhrase(""+GetSexPhrase("Oh, bellezza, scommetto che potrei annegare in quegli occhi tuoi...","Sei bellissima, bambina!")+"",""+GetSexPhrase("Sai, non ho mai incontrato una donna così bella prima d'ora!","Sai, non ho mai incontrato una ragazza così simpatica prima d'ora!")+"",""+GetSexPhrase("Tesoro, sei bellissima.","Dannazione, ero così stanco di tutti quei rozzoni... E tu sei così affascinante!")+"");
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
				link.l5 = LinkRandPhrase("Ascolta, "+GetSexPhrase("bellezza","caro")+", non hai trovato per caso un anello di matrimonio qui? Sembra che un uomo l'abbia perso...","Tesoro, hai visto un anello nuziale o qualcosa del genere in giro?","Ascolta, "+GetSexPhrase("la mia micina","bambola")+", non hai visto un anello di matrimonio da queste parti?");
				link.l5.go = "TakeMayorsRing_S1";
				SaveCurrentNpcQuestDateParam(npchar, "TakeMayorsRing");
			}
			//<<-- квест поиска кольца мэра
			
			// Addon 2016-1 Jason пиратская линейка
			if (pchar.location == "santodomingo_brothel" && CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_1" && npchar.id == "HorseGen_"+reload_location_index+"_2")
			{
				link.l6 = "Ciao, dolcezza. Marcus Tyrex mi ha mandato, guarda questa collana d'ambra...";
				link.l6.go = "mtraxx";
			}
			NextDiag.TempNode = "Horse_talk";
		break;
		
        case "Horse_1":
			dialog.text = "Lei è nel suo ufficio. Puoi arrivarci da qui attraverso la porta di fronte all'uscita sulla strada, o dalla strada dall'altra parte della casa. Il suo nome è "+characters[GetCharacterIndex(npchar.city+"_Hostess")].name+".";
			Link.l1 = "Capisco, "+GetSexPhrase("tesoro","tesoro")+", grazie.";
			Link.l1.go = "exit";			
		break;
		
        case "Horse_2":
			if (rand(1))
			{
				dialog.text = LinkRandPhrase("Oh mio, è così bello sentire queste cose! Ehi, sono libera al momento, quindi se mi scegli, non te ne pentirai...","Davvero lo pensi? Sai, è così carino... Ascolta, al momento sono libera, quindi potresti scegliere me."+GetSexPhrase("Ti prometto un mare d'amore e un oceano di carezze...","")+"",""+GetSexPhrase("Pensi davvero? Oh, sono davvero lusingata. Sai, raramente sento tali complimenti...","Oh, ragazza... se solo sapessi quanto sono stufo dei redneck...")+"Ehi, ascolta, sono libera al momento, quindi puoi scegliermi per renderti felice. Non ti deluderò, te lo prometto...");
				if (CheckAttribute(pchar, "questTemp.RomNaTroih") && !CheckAttribute(pchar, "questTemp.RomNaTroih_Pogovoril"))
				{
					link.l1 = "Cara mia, è esattamente quello che stavo per fare! Com'è fortunato che la tua padrona di casa abbia già organizzato un incontro privato con me al piano di sopra. Vuoi unirti?";
					Link.l1.go = "RomNaTroih_1";
					pchar.questTemp.RomNaTroih_Pogovoril = true;
					break;
				}
				link.l1 = "Allora, ti scelgo, allora!";
				Link.l1.go = "Horse_3";		
				Link.l2 = ""+GetSexPhrase("No, era solo un complimento a una bella signora","Quello era solo un complimento")+".";
				Link.l2.go = "exit";
				npchar.quest.choice = 0; //был базар, но ГГ потом отказался
			}
			else
			{
				dialog.text = LinkRandPhrase(""+GetSexPhrase("Sai cosa dico, dolcezza? Non ho bisogno di queste chiacchiere da quattro soldi. Facciamo affari o vattene!","Ecco tutto ciò di cui avevo bisogno! Complimenti dalle donne!")+"",""+GetSexPhrase("Sei uno di quelli che pensa che le donne si innamorino con le orecchie? Beh, caro, non è affatto vero. Se mi vuoi, allora paga alla madama e risparmiami le tue parole vuote.","Ragazza, non sprecarti in chiacchiere vuote. Se sei seria - allora paga...")+"",""+GetSexPhrase("Oh, un altro amante della sensualità... Basta che paghi e sono tua. È tutto così semplice, senza tutte queste sciocchezze gentili!","Cosa c'è, cara? Se vuoi concederti dei piaceri, allora paga e smetti con tutte queste sciocchezze!")+"");
				link.l1 = "Oh, che presa!";
				Link.l1.go = "exit";
				npchar.quest.choice = 2; //ГГ послали
			}
		break;
		
        case "Horse_3":
			dialog.text = characters[GetCharacterIndex(npchar.city+"_Hostess")].name+" completa tutte le formalità nel suo ufficio. Vai a vederla"+GetSexPhrase(", mio eroe,","")+" e pronuncia il mio nome - "+npchar.name+". Ti aspetterò...";
			Link.l1 = "Capisco, cara, tornerò presto...";
			Link.l1.go = "exit";
			npchar.quest.choice = 1; //она согласная
			SetNPCQuestDate(npchar, "quest.choice");
		break;
		
        case "Horse_4": 
			dialog.text = NPCStringReactionRepeat("Hai già pagato.","Ti ho detto 'vai al piano di sopra'.","Su, giovane uomo.","Alcune persone pensano così lentamente...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sì, lo so.","Mi ricordo.","Oh, non ripeterti, mi ricordo.","Mmm, cosa intendi?.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "Horse_4";
		break;
		
		//===>> реакция на попытки пофлиртовыть, если флирт уже был
        case "HorseChoice_0": 
			if (!CheckAttribute(npchar, "quest.sexHappend"))
			{
				dialog.text = NPCStringReactionRepeat("Semplicemente non ti capisco molto bene."+GetSexPhrase("Prima fai i complimenti, poi torni sui tuoi passi. Che strano tipo...","")+"","Di nuovo complimenti?.","La padrona è nel suo ufficio. Capito?","Non dovremmo insultare i nostri clienti, ma stai davvero chiedendo troppo"+GetSexPhrase("","")+"...","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("È successo semplicemente così...","Bene, lo farò.","Sì, ho capito.","Chiedo scusa, amore mio.",npchar,Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Grazie per il complimento. Se vuoi prendermi, vai a vedere la madama. Affari come al solito.";
				Link.l1 = "Capisco.";
				Link.l1.go = "exit";
			}
		break;
		
        case "HorseChoice_1": 
			if (!CheckAttribute(npchar, "quest.sexHappend"))
			{
				if (!CheckNPCQuestDate(npchar, "quest.choice"))
				{
					dialog.text = NPCStringReactionRepeat(""+GetSexPhrase("Cara, abbiamo già discusso di tutto. ","")+"Non farmi aspettare troppo a lungo...",""+GetSexPhrase("Mmm... Ascolta, cara, io","Io")+" trovo le tue parole molto belle e tutto, ma potresti passare ai fatti...","Forse, ne parlerai con la madame, non è vero?","Mm... Non so nemmeno cosa dire...","block",1,npchar,Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("Non farei mai una cosa del genere, aspettami!","Certo!","Certo, come dici tu!","Sto già correndo per vedere la vostra madame...",npchar,Dialog.CurrentNode);
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Ti stavo aspettando, ma non sei venuto a prendermi... Non posso dire che mi sia piaciuto...";
					Link.l1 = "Vedi, è semplicemente successo come è successo...";
					Link.l1.go = "exit";
					npchar.quest.choice = 0; //был базар, но ГГ потом отказался
				}
			}
			else
			{
				dialog.text = "Oh, sei tu di nuovo, mio "+GetSexPhrase("glorioso corsaro","bella ragazza")+"! Se mi vuoi di nuovo, vieni a vedere la madama, non rimarrai deluso..."+GetSexPhrase("A proposito, ti ho riconosciuto, caro, ma ci dicono che dobbiamo parlare con tutti i clienti allo stesso modo, non dovrebbe esserci un preferito, mi dispiace per questo...","")+"";
				Link.l1 = "Non preoccuparti, tesoro. Aspettami solo un po', "+GetSexPhrase("bella","carina")+", e presto ci incontreremo di nuovo in privato.";
				Link.l1.go = "exit";
				Link.l2 = "È molto carino che tu ti ricordi di me, ma non posso passare questa notte con te, mi dispiace.";
				Link.l2.go = "HorseChoice_1_Add";
			}
		break;
		
        case "HorseChoice_2": 
			if (!CheckAttribute(npchar, "quest.sexHappend"))
			{
				dialog.text = NPCStringReactionRepeat("Allora,"+GetSexPhrase(" caro amico,","")+" sarebbe meglio se ti occupassi di affari. Sarà più utile che non fare nulla.",""+GetSexPhrase("Mmm, perché sei tu ","Perché sei qui")+" dicendo le stesse cose ancora e ancora?","Ehi, non ne hai abbastanza?!","Mh, che sorpresa, nulla di nuovo"+GetSexPhrase(", ancora una volta tutti questi stupidi tentativi di seduzione! Se vuoi fare sesso con me, vai a vedere la madame, tu sciocco!","...")+"","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Sì, ho sentito"+GetSexPhrase("","")+" tu...","Mmm, è così che va...","Mmm, forse è abbastanza, o forse no ...","Guarda la tua lingua"+GetSexPhrase(", capra","")+"...",npchar,Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Ohh, sei tu di nuovo! "+GetSexPhrase("E ancora una volta tutti quei stupidi complimenti. Niente cambia mai in questo mondo... Se ","Solo per ricordare: se ")+"vuoi"+GetSexPhrase("divertiti","divertiti")+" con me, paga il proprietario del locale. Non potrebbe importarmi di meno delle tue parole.";
				Link.l1 = "Non è una grande sorpresa...";
				Link.l1.go = "exit";
			}
		break;
		
        case "HorseChoice_1_Add":
			dialog.text = "Non posso dire che mi ha reso felice... Un peccato.";
			Link.l1 = "Mi dispiace...";
			Link.l1.go = "exit";
			npchar.quest.choice = 0;
		break;
		
		//===>> секс
        case "Horse_ReadyFack":
			// Addon 2016-1 Jason пиратская линейка
			if (pchar.location == "SantoDomingo_Brothel_room" && CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_2" && npchar.name == "Gabriela")
			{
				dialog.text = "Ah, finalmente sei arrivato! Fantastico! Possiamo parlare liberamente, nessuno ci sta ascoltando...";
				Link.l1 = "Allora, è stato lo spagnolo a darti l'ambra blu?";
				Link.l1.go = "mtraxx_2";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("SantoDomingo");
				break;
			}
			if (!CheckAttribute(npchar, "quest.choice")) npchar.quest.choice = 0;
			switch(npchar.quest.choice)
			{
				case "0":
					dialog.text = RandPhraseSimple("Sono molto felice di vederti. "+GetSexPhrase("Allora, cosa faremo dopo?","Che ne dici di divertirci un po'?")+"","Non essere timido"+GetSexPhrase(", fatti come a casa tua per almeno due ore.",". Sarò in grado di intrattenerti, non avere dubbi.")+"");
					Link.l1 = RandPhraseSimple("Non credo che sarà noioso...",""+GetSexPhrase("Passiamo un bel momento, tesoro!","Non perdiamo tempo!")+"");
				break;
				case "1":
					dialog.text = "Oh, sei tu di nuovo, mio "+GetSexPhrase("glorioso corsaro! Ti ho promesso qualcosa e sono pronta a mantenere la mia parola","bella ragazza! Non dimenticherai mai le prossime due ore")+"...";
					Link.l1 = "Ecco, questo suona allettante...";	
				break;
				case "2":
					dialog.text = "Ohh, eccoti qui, finalmente. Non perdiamo tempo!";
					Link.l1 = ""+GetSexPhrase("Non facciamolo, gattina...","Ora mostrami cosa sai fare...")+"";
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
				dialog.text = "Capitano, perché sei così silenzioso?";
				link.l1 = LinkRandPhrase("Ebbene, sono io.","Parleremo la prossima volta.",RandPhraseSimple("Non ti sto pagando per parlare.","Ma tu, "+GetSexPhrase("bellezza","tesoro")+", non eri così silenzioso tutto quel tempo."));
				link.l1.go = "exit";
				link.l2 = ""+GetSexPhrase("Sei stata semplicemente fantastica, ho quasi perso la testa! È un'occasione molto rara, quando una donna è sia così bella che calda","Ohh, di certo sai come far piacere a una donna... Sono così eccitata.")+".";
				link.l2.go = "Horse_ReasonToFast_1";
			}
			else
			{
				switch(npchar.quest.choice)
				{
					case "0":
						dialog.text = LinkRandPhrase("Ti è piaciuto?","Allora, cosa puoi dire? Andava tutto bene?","Allora,"+GetSexPhrase("corsaro, è, tutto"," tutto")+" bene?");
						Link.l1 = RandPhraseSimple(""+GetSexPhrase("Certo, tutto va bene","Sicuramente conosci i tuoi doveri")+".",""+GetSexPhrase("Tutto bene, cara","Sai, ero piuttosto contento")+".");
						Link.l1.go = "exit";
					break;
					case "1":
						dialog.text = LinkRandPhrase("Allora, ho mantenuto la mia promessa?","Allora,"+GetSexPhrase(" ti sono piaciuta",", ti è piaciuto")+"?","Spero, "+GetSexPhrase("eri contento, perché io sono mo-o-olto contenta","eri contento, perché ho fatto del mio meglio")+"...");
						Link.l1 = RandPhraseSimple("Sì, mi è piaciuto molto.",""+GetSexPhrase("Ci siamo divertiti molto, eri splendida!","Tutto era semplicemente fantastico!")+"");	
						Link.l1.go = "exit";
					break;
					
					case "2":
						dialog.text = RandPhraseSimple("Bene, è tutto, devi andare.","Il tuo tempo è finito,"+GetSexPhrase(" Capitano,","")+".");
						Link.l1 = RandPhraseSimple("Sì, ci vediamo...","Addio e grazie...");
						Link.l1.go = "exit";
					break;
				}
				NextDiag.TempNode = "Horse_AfterSex_2";
			}	
		break;
		
        case "Horse_AfterSex_2":
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && pchar.GenQuest.EncGirl == "Bag_BrothelRoom" && !CheckCharacterItem(pchar, "leather_bag"))
			{
				dialog.text = "Allora, come ti è piaciuto qui?";
				link.l1 = "Dimmi bella, non hai visto una sacca da viaggio da qualche parte?";
				link.l1.go = "EncGirl_GetBag";
			}
			else
			{
				dialog.text = LinkRandPhrase("Passa di nuovo qualche volta...","Addio. Ti aspetteremo sempre...","Saremo lieti di rivederti qui di nuovo...");
				Link.l1 = "Bene...";
				Link.l1.go = "exit";
				NextDiag.TempNode = "Horse_AfterSex_2";
			}	
		break;
		
		case "EncGirl_GetBag":
			dialog.text = "Era quella cassa marrone con una maniglia?";
			link.l1 = "Sì, qualcosa del genere...";
			link.l1.go = "EncGirl_GetBag1";	
		break;
		
		case "EncGirl_GetBag1":
			dialog.text = "Perché il proprietario di quel baule non si è presentato, la madame l'ha portato nel suo boudoir.";
			link.l1 = "Grazie, cara. Addio.";
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "Bag_BrothelHostess";
			NextDiag.TempNode = "Horse_AfterSex_2";
		break;
		
		// --> генератор - "A reason to hurry"
		case "Horse_ReasonToFast_1":
			dialog.text = "Allora vieni quando vuoi, sarò sempre felice di vederti. Sei così "+GetSexPhrase("dolce, non come quelle altre","dolce, non come quei villani")+" nessun saluto, nessun addio, e spesso cercano persino di fare del male...";
			link.l1 = "Cosa intendi con quello?";
			link.l1.go = "Horse_ReasonToFast_2";
		break;
		
		case "Horse_ReasonToFast_2":
			pchar.questTemp.ReasonToFast.speakHorse = true;
			dialog.text = "C'era un sergente maggiore proprio prima di te. Di solito non ci fa visita, ma questa volta qualche diavolo lo ha portato qui. Inoltre, mi ha scelta... Stava gemendo mentre era sopra di me per qualche minuto, poi mi ha chiamato poco abile e si è precipitato in qualche insenatura. Se n'è andato così in fretta che ha quasi lasciato i pantaloni lì, ah-ah-ah...";
			link.l1 = "Non lo sai, "+GetSexPhrase("bellezza","tesoro")+", chi sono veramente gli uomini? Aveva detto a sua moglie che sarebbe andato al bordello per un 'ispezione', poi aveva detto alla sua amante che aveva fretta di tornare dalla moglie, ma l'unica cosa che voleva sempre fare era andare a pattugliare quella insenatura. "+GetSexPhrase("Ah-ah-ah!..","A-ha-ha!")+"";
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
				dialog.text = LinkRandPhrase("No, cara, mi dispiace, ma no. Ti aiuterei volentieri, ma non posso.","No, "+GetSexPhrase("affascinante","signorina")+", Non ho visto nessun anello...","Mi dispiace, ma no. Non ho visto nessun anello.");
				link.l1 = "Peccato... Comunque, grazie.";
				link.l1.go = "exit";
			}
			else
			{
				if (npchar.id == "HorseGen_"+reload_location_index+"_1")
				{
					dialog.text = "Intendi l'anello del governatore?";
					link.l1 = "Esattamente, bella!";
					link.l1.go = "TakeMayorsRing_S2";
				}
				else
				{
					dialog.text = LinkRandPhrase("No, tesoro, mi dispiace, ma no. Ti aiuterei volentieri - ma non posso.","No, "+GetSexPhrase("affascinante","signorina")+", Non ho visto nessun anello...","Mi dispiace, ma no. Non ho visto nessun anello.");
					link.l1 = "Peccato... Beh, grazie comunque.";
					link.l1.go = "exit";
				}
			}
		break;

		case "TakeMayorsRing_S2":
			dialog.text = "Mi dispiace, ma l'anello mi è stato dato come regalo, quindi non sono obbligato a restituirlo.";
			link.l1 = "Un regalo?! E chi te l'ha dato?";
			link.l1.go = "TakeMayorsRing_S3";
		break;
		
		case "TakeMayorsRing_S3":
			dialog.text = "Il governatore stesso, naturalmente!";
			link.l1 = "Ma lui era... ubriaco, per dirlo in modo gentile. Non ricorda nulla.";
			link.l1.go = "TakeMayorsRing_S4";
		break;
		
		case "TakeMayorsRing_S4":
			dialog.text = "E cosa c'entra con me? Se era ubriaco, è un suo problema, non mio!";
			link.l1 = "Davvero devi litigare con lui? È un anello di matrimonio, e lo sai... Restituiscilo, una cosa così piccola non vale la pena di nessun guaio.";
			link.l1.go = "TakeMayorsRing_S5";
		break;
		
		case "TakeMayorsRing_S5":
			if (rand(1) && sti(pchar.money)>5000)
			{
				dialog.text = "Bene, restituirò l'anello, ma tu mi pagherai cinquemila pesos.";
				link.l1 = "Bene, prendi i tuoi soldi e dammi l'anello.";
				link.l1.go = "TakeMayorsRing_S6";
			}
			else
			{
				dialog.text = "Oh, beh. Lascia che lo abbia!";
				link.l1 = "Questo è certo, tesoro!";
				link.l1.go = "exit";
				GiveItem2Character(pchar, "MayorsRing");
				pchar.questTemp.different.TakeMayorsRing = "HorseTakenRing";
				AddQuestRecord("SeekMayorsRing", "3");
				AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
				AddQuestUserData("SeekMayorsRing", "sName", GetFullName(npchar));
			}
		break;
		
		case "TakeMayorsRing_S6":
			dialog.text = "Eccoti...";
			link.l1 = "Bene, allora. Grazie per l'aiuto, tesoro.";
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
			dialog.text = "Vedi, abbiamo un cliente molto sgradevole - "+pchar.GenQuest.Badboy.Brothel.Name+". E ci infastidisce davvero ogni volta che viene! Prima si ubriaca alla taverna, poi viene qui, sceglie una ragazza e fa un gran baccano\nE la cosa peggiore è che è di nobile discendenza! È un parente lontano del nostro governatore, quindi siamo costretti a sopportare tutte le sue bravate. Forse potresti fare in modo che quel giovane sfrontato... beh... si calmi un po'... in modo che smetta di visitare il mio locale?";
			link.l1 = "Parente del Governatore, dici? Hmmm... Preferirei non affrontare le autorità. Mi dispiace davvero.";
			link.l1.go = "exit";
			link.l2 = "Credo di poter organizzare questo. Dimmi, dove posso trovare quel mascalzone?";
			link.l2.go = "Badboy_1";
		break;
		
		case "Badboy_1":
			dialog.text = "Di solito a quest'ora è già alla taverna. Si ubriaca lì e poi viene a trovarci.";
			link.l1 = "Capisco. Beh, probabilmente lo incontrerò lì.";
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
			dialog.text = "Oh, sei un vero uomo, vero? Ho sempre saputo che potevo contare su di te..";
			link.l1 = "Sono sempre felice di aiutare una signora così gentile e le sue... pupille.";
			link.l1.go = "Badboy_complete_1";
		break;
		
		case "Badboy_complete_1":
			dialog.text = "Non sei solo coraggioso, ma anche molto galante. Vorrei ringraziarti in modo speciale - in un modo che solo una donna può ringraziare un uomo. Non lo dimenticherai mai, te lo prometto. Vieni su, coraggioso marinaio...";
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
			dialog.text = "C'è un uomo e mi deve dei soldi... Non so come dirlo...";
			link.l1 = "Senza parole! Lo troverò e lo scuoterò fino all'ultimo peso solo per uno sguardo dei tuoi occhi insondabili! Dimmi solo il suo nome!";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "No, no, non mi hai capito bene, Capitano! Quest'uomo... non fargli nulla di male. Ricordagli solo dei suoi debiti. Il suo nome è Hugo Avendell, e suppongo che lo troverai lì, dove vendono alcolici molto economici. Per l'amor di Dio, non usare la forza con lui!\nDìgli solo... ricordagli che ha promesso di pagare. Non voglio contattare la guardia, ma ho amici ufficiali, quindi digli che sto aspettando e, con tutto il dovuto rispetto per lui, sarò costretta a prendere provvedimenti non oltre domani. Ricordagli solo della sua promessa.";
			link.l1 = "La tua parola è legge per me, signora. Sarò lieto di esaudire la tua richiesta.";
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
			dialog.text = "Grazie, capitano. Spero davvero che dimostrerà la dovuta prudenza.";
			link.l1 = "Ne sono certo, signora. Ora permettimi di prendere congedo.";
			link.l1.go = "exit";
			sld = characterFromId("Avendel");
			sld.lifeday = 0;
			pchar.questTemp.Portugal = "end";
		break;
		
		case "Portugal_3":
			AddMoneyToCharacter(pchar, -10000);
			dialog.text = "Oh no! Non dirmi che gli hai fatto qualcosa di terribile... Non aveva soldi, e io lo sapevo! Siamo solo cresciuti nella stessa piccola città, non avrei mai chiamato le guardie! Volevo solo spaventarlo un po'... per scuoterlo prima che si annegasse nella bottiglia!";
			link.l1 = "Hmm... Comunque, ecco i tuoi soldi. E non preoccuparti per Hugo, sta bene... Almeno lo sarà se smetterà di bere.";
			link.l1.go = "Portugal_4";
		break;
		
		case "Portugal_4":
			dialog.text = "Oh, Capitano, non capisci! Era uno di... beh, sai, sono chiamati cacciatori di taglie - mercenari, danno la caccia ai pirati e ai ladri e li eliminano. Ma, non era il più fortunato, per dirla in modo gentile\nNon molto tempo fa, ha finalmente sperperato e ha perso il suo equipaggio e la nave, da allora è stato alla deriva nel fondo del suo boccale, giorno dopo giorno. Io, per vecchia memoria, gli permetto di venire qui qualche volta. È così... così pietoso ora. Era l'uomo più bello della nostra città sulla costa della Manica, e guardalo ora\nSo che ti ha promesso qualcosa, e tu hai pagato di tasca tua! Ti restituirò questi soldi, solo non fargli nulla di male, ti prego, capitano!";
			link.l1 = "Bene, va bene, signora, ho capito. Tieni i soldi, sono tuoi. Per quanto riguarda il tuo amico, prometto che non gli farò del male. E ora permettimi di andare, ho degli affari da sbrigare. Inoltre, sono stato felice di aiutare una signora così bella.";
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
            dialog.text = "Taci, abbassa la voce... Vai a chiedere a Madame Lolita un appuntamento per me. Poi vieni su, dove possiamo parlare liberamente. E nessuna parola fino ad allora... Ehi, marinaio, vai a pagare a Madame prima di toccarmi! (ride)";
			link.l1 = "In viaggio, tesoro...";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
           DialogExit();
		   chrDisableReloadToLocation = false;
		   pchar.questTemp.Mtraxx = "jewelry_2";
		break;
		
		case "mtraxx_2":
			pchar.quest.Mtraxx_JewelrySDMOver.over = "yes"; //снять таймер
            dialog.text = "No, non io. Ti racconterò tutta la storia, basta non interrompermi.";
			link.l1 = "Sono tutto orecchie!";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = "Bene allora. Circa una settimana fa, una nave militare è arrivata a Santo Domingo. Era danneggiata, sia da una tempesta che da una lotta, quindi le riparazioni sono iniziate immediatamente, e l'equipaggio si è trasferito al forte. Il suo capitano, però, ha passato tutto il suo tempo libero proprio qui. Per due giorni di seguito si è dedicato a bere e rilassarsi in compagnia di una delle nostre ragazze. Fu lei a ricevere la pietra preziosa, e non solo una. Ne parlava senza fine - Lolita ci permette di tenere i regali dei clienti\nLa sciocca ragazza non conosceva nemmeno il vero valore del dono, mentre io l'ho capito subito. Quando mi ha parlato di come il capitano ubriaco si vantava di una montagna piena di ambre, ho prontamente inviato una lettera a Tyrex...";
			link.l1 = "";
			link.l1.go = "mtraxx_4";
		break;
		
		case "mtraxx_4":
            dialog.text = "All'arrivo successivo del capitano ho organizzato tutto in modo che la sua ragazza preferita fosse occupata con un altro cliente, e ho ottenuto il 'lavoro' per me. Ho cercato di ottenere le coordinate da lui, ahimè, senza successo. Continuava solo a vantarsi di come sarebbe diventato ricco come Crasso e sarebbe tornato al Vecchio Mondo\nNon una parola sulla posizione. L'unica cosa che ho scoperto era che la sua nave era stata riparata e stava per salpare per L'Avana, dove avrebbe cercato di organizzare una missione nella giusta direzione. Dopotutto, non è il proprietario della nave.";
			link.l1 = "Allora, è a L'Avana ora?";
			link.l1.go = "mtraxx_5";
		break;
		
		case "mtraxx_5":
            dialog.text = "Ha salpato due giorni fa all'alba. Sei tu il marinaio qui, fai tu i conti.";
			link.l1 = "Nome del capitano, tipo e nome della sua nave, qualcosa?";
			link.l1.go = "mtraxx_6";
		break;
		
		case "mtraxx_6":
            dialog.text = "Cosa, mi prendi per un idiota? Il suo nome è Esberdo Cabanas, capitano della Cantavro. Credo che i marinai la chiamassero una goletta.";
			link.l1 = "E questo è tutto quello che sai?";
			link.l1.go = "mtraxx_7";
		break;
		
		case "mtraxx_7":
            dialog.text = "Cosa vuoi di più? Sono sicura che potresti raggiungerlo prima di arrivare all'Avana. Non perdere tempo però, non credo si riposerà a lungo prima di lasciare Cuba verso il suo nascondiglio, e poi è un caso perso. Pensandoci un attimo, potresti restare un'ora o due, dopotutto l'hai pagato.";
			link.l1 = "Buon punto, cara. Due ore non faranno molta differenza...";
			// belamour legendary edition -->
			link.l1.go = "mtraxx_7S";
			link.l2 = "Un'altra volta, cara. Considera di concederti una pausa pranzo. Vai in chiesa, o qualcosa del genere.";
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
			DeleteAttribute(pchar, "questTemp.ZA.block");
		break;
		// <-- legendary edition
		case "mtraxx_R":
            dialog.text = "O-oh... Che peccato. E pensavo che tu fossi qui in vacanza. Le mie ragazze sentono tanto la mancanza di coraggiosi corsari. Molto bene, allora, parla, qual è il compito?..";
			link.l1 = "Marcus mi ha incaricato di organizzare una festa diabolica nel tuo stabilimento per due giorni, di bere tutto il vino e di divertirmi con ogni ragazza. Quando iniziamo?";
			link.l1.go = "mtraxx_R1";
		break;
		
		case "mtraxx_R1":
            dialog.text = "Ah, Charlie Prince, il tuo umorismo è tagliente come la tua sciabola! Quasi mi hai fatto arrabbiare... Ragazze! Abbiamo un ospite, un ospite speciale! Portate vino e pasti!";
			if (sti(pchar.money) >= 31000)
			{
				link.l1 = "Chiamate tutte le belle ragazze qui! Stiamo per riposare e divertirci! Yo-ho-ho!..";
				link.l1.go = "mtraxx_R2";
			}
			else
			{
				link.l1 = "Aspetta un minuto, Janette. Devo prendere l'oro dalla mia nave per te e le tue signorine. Ci vediamo in un minuto!";
				link.l1.go = "exit";
				pchar.questTemp.Mtraxx.Retribution = "brothel_repeat";
				chrDisableReloadToLocation = false;
			}
		break;
		
		case "mtraxx_R2":
			AddMoneyToCharacter(pchar, -30000);
            dialog.text = "Vorrei che tutti i nostri clienti fossero dolci, belli e generosi come te... Ti offriremo un relax perfetto. Ragazze!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionInBrothel");
		break;
		// belamour ночной приключенец
		case "NA_Girl":
            dialog.text = "Oh, quindi abbiamo un intenditore qui, hee hee ... Beh, beh, ho una ragazza così. Ma non viene a buon mercato: "+makeint(pchar.GenQuest.NightAdventure_money)+" pesos."; 
			link.l1 = "Affare.";
			link.l1.go = "NA_Girl_1";
		break;
		
		case "NA_Girl_1":
			AddMoneyToCharacter(pchar, -makeint(pchar.GenQuest.NightAdventure_money));
            dialog.text = "È fantastico, caro. La Sacerdotessa dell'Amore ti aspetterà al piano di sopra. Credimi, non te ne pentirai."; 
			link.l1 = "Già non lo faccio.";
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
			dialog.text = "Per te e m'signore Agueybana? Certo che lo fai. Saranno diecimila, capitano.";
			if (sti(pchar.money) >= 10000) {
				link.l1 = "Aspetta, non così!.. Accidenti! Comunque, ecco il pagamento.";
				link.l1.go = "chicken_god_pay";
			} else {
				link.l2 = "Posso ottenere un prestito?";
				link.l2.go = "chicken_god_notpay";
			}
		break;
		
		case "chicken_god_pay":
			dialog.text = "Goditi il tuo soggiorno, capitano. Per favore, torna di nuovo quando siamo aperti. Il nostro istituto offre ogni tipo di svago per nobili uomini e donne.";
			link.l1 = "...";
			link.l1.go = "chicken_god_pay_1";
		break;
		
		case "chicken_god_pay_1":
			dialog.text = "";
			link.l1 = "Signora "+npchar.name+", puoi almeno spiegarmi cosa sta succedendo qui? Il governatore è anche a conoscenza che avete avuto un nativo al comando per un mese? Nessun insediamento può sopravvivere alla chiusura di un bordello per un giorno, posso dirtelo io!";
			link.l1.go = "chicken_god_pay_2";
		break;
		
		case "chicken_god_pay_2":
			dialog.text = "La stanza è tua, capitano. Ora, se mi scuserai.";
			link.l1 = "Incantatore. Addio, signora.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_PayForRoom");
		break;
		
		case "chicken_god_notpay":
			dialog.text = "Perché, Signore, perché? Vattene! Vai via, vai via, non ne posso più! Bastardo!";
			link.l1 = "È andata bene.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_NotPayForRoom");
		break;
		
		//-->> Sinistra Ром на троих
		case "RomNaTroih_1":
			dialog.text = "Mhm... Di solito non faccio questo... ma sono disposta a rischiare per te. È il tuo giorno fortunato, Capitano!";
			link.l1 = "Andiamo!";
			link.l1.go = "exit";
			pchar.RomNaTroih_Shluha = npchar.id;
		break;
		
		case "RomNaTroih_2":
			dialog.text = "Sono arrabbiata con te, Capitano... Ma ti mostrerò pietà se lavori abbastanza per essa.";
			link.l1 = "Oh, lo farò. Dobbiamo aprire il vino?";
			link.l1.go = "exit";
			Achievment_Set("ach_CL_105");
		break;
		//<<-- Sinistra Ром на троих
		
		//--> прибыла инспекция на Святом Милосердии
		case "SantaMisericordia_1":
			dialog.text = "Fino a quando quel maledetto de Alamida se ne va. Dannato uomo santo...";
			link.l1 = "Ma forse...";
			link.l1.go = "SantaMisericordia_2";
		break;
		
		case "SantaMisericordia_2":
			dialog.text = "Niente forse. E se lui entrasse qui proprio ora? Tutti fuori.";
			link.l1 = "...";
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

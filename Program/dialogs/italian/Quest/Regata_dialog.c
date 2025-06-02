void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n, iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	bool ok;
    int iTest;
    ref rColony;
    string sFrom_sea = "";
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		//вестовой
		case "Regata_Cureer":
			dialog.text = "Buon giorno. Siete voi il capitano "+GetFullName(pchar)+"?";
			link.l1 = "Sì, sono io. E qual è la faccenda?";
			link.l1.go = "Regata_Cureer_1";
		break;
		
		case "Regata_Cureer_1":
			dialog.text = "Ho una lettera per voi dal governatore della Giamaica, sir Edward Doily.";
			link.l1 = "Per mille balene! Non me l’aspettavo... E che diavolo vuole il governatore da me?";
			link.l1.go = "Regata_Cureer_2";
		break;
		
		case "Regata_Cureer_2":
			dialog.text = "Legga la lettera, signore. In breve, le offrono di partecipare alla regata, una corsa che attraversa tutto l’arcipelago. Le voci sulle sue doti marinare e sulla sua velocità in mare sono arrivate lontano.";
			link.l1 = "Incredibile! Beh io... ci rifletterò su.";
			link.l1.go = "Regata_Cureer_3";
			GiveItem2Character(pchar, "letter_open");
			ChangeItemDescribe("letter_open", "itmdescr_letter_open_Regata");
			AddQuestRecordInfo("RegataLetter", "1");
		break;
		
		case "Regata_Cureer_3":
			if (Pchar.BaseNation == SPAIN || Pchar.BaseNation == HOLLAND)
			{
				dialog.text = "Inoltre ti concedo libero accesso al porto di Port Royal. Ecco una licenza valida per 30 giorni. Ora la mia missione è compiuta. Addio, capitano.";
				link.l1 = "Grazie. La lettera di corsa è assai gradita. Addio!";
				link.l1.go = "Cureer_exit";
				GiveNationLicence(HOLLAND, 30);
			}
			else
			{
				dialog.text = "Bene. Ora la mia missione è compiuta. Addio, capitano.";
				link.l1 = "Addio!";
				link.l1.go = "Cureer_exit";
			}
		break;
		
		case "Cureer_exit":
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
			pchar.questTemp.Regata.ToPortRoyal = "true";
			SetQuestHeader("Regata");
			AddQuestRecord("Regata", "1");
		break;
		
		//распорядитель регаты
		case "Regata_Head":
			if (CheckAttribute(pchar, "questTemp.Regata.Begin"))
			{
				dialog.text = "Buon dì. Partecipi alla regata, vero?";
				link.l1 = "Esattamente, signore. Il mio nome è "+GetFullName(pchar)+". Ho ricevuto l’invito.";
				link.l1.go = "Regata_Head_1";
			}
			else
			{
				dialog.text = "Desiderate qualcosa, signore?";
				link.l1 = "No, non è nulla. Me ne sto già andando.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Regata_Head";
			}
		break;
		
		case "Regata_Head_1":
			iTest = FindColony("PortRoyal"); 
			if (iTest != -1)
			{
				rColony = GetColonyByIndex(iTest);
			}
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
			{
				dialog.text = "Sono lieto d’incontrarti, capitano "+GetFullName(pchar)+". Allora, cominciamo. Hai già appreso le basi dalla lettera, vero? Solo lugri, e lei dev’essere l’unica nave nella tua flottiglia per partecipare alla regata. Hai soddisfatto questi requisiti?";
				// belamour legendary edition допускаем курьерский люггер 
				ok = sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_LUGGER || sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_CAREERLUGGER;
				if((GetCompanionQuantity(pchar) > 1) || !ok)
				{
					link.l1 = "Non ancora. Lo farò ora e tornerò presto.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Regata_Head_repeat";
				}
				else
				{
					link.l1 = "Sì, ce l’ho.";
					link.l1.go = "Regata_Head_2";
				}
			}
			else
			{
				dialog.text = "Sei venuto a partecipare alla regata, ma dov'è la tua nave, capitano?";
				link.l1 = "Perdonate, signore. Farò attraccare la mia nave al porto senza indugio.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Regata_Head_repeat";
			}
		break;
		
		case "Regata_Head_repeat":
			if (CheckAttribute(pchar, "questTemp.Regata.Begin"))
			{
				iTest = FindColony("PortRoyal"); 
				if (iTest != -1)
				{
					rColony = GetColonyByIndex(iTest);
				}
				ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
				if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
				{
					ok = sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_LUGGER || sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_CAREERLUGGER;
					dialog.text = "Ah, sei di nuovo tu. Hai fatto tutto il necessario per soddisfare i requisiti della regata?";
					// belamour legendary edition допускаем курьерский люггер 
					if ((GetCompanionQuantity(pchar) > 1) || !ok)
					{
						link.l1 = "Non ancora. Lo farò subito e torno presto.";
						link.l1.go = "exit";
						NextDiag.TempNode = "Regata_Head_repeat";
					}
					else
					{
						link.l1 = "Sì, ce l’ho.";
						link.l1.go = "Regata_Head_2";
					}
				}
				else
				{
					dialog.text = "Capitano, non abbiamo nulla da discutere finché non vedrò la vostra nave all’ancora in rada. Mi avete capito, o devo ripetermi?";
					link.l1 = "Perdonate, signore. Farò attraccare la mia nave in porto all’istante.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Regata_Head_repeat";
				}
			}
			else
			{
				dialog.text = "Desiderate qualcosa, signore?";
				link.l1 = "No... non è niente. Me ne vado già.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Regata_Head";
			}
		break;
		
		case "Regata_Head_2":
			dialog.text = "Bene. Ora il prossimo punto. Qual è il nome della tua nave?";
			link.l1 = "'"+pchar.Ship.Name+"'. ";
			link.l1.go = "Regata_Head_3";
		break;
		
		case "Regata_Head_3":
			dialog.text = "Poiché la regata è organizzata dalle autorità inglesi e secondo le regole stabilite il nome della tua nave dovrà essere cambiato per la durata dell’evento. Non temere, la cosa riguarda tutti i partecipanti.";
			link.l1 = "Dicono che porti sventura cambiare il nome della tua nave.";
			link.l1.go = "Regata_Head_4";
		break;
		
		case "Regata_Head_4":
			dialog.text = "Potrai cambiare nome dopo la regata. Dunque, il tuo legno porterà il nome 'Santa Caterina'.";
			link.l1 = "Capisco, signore, cambierò il nome.";
			link.l1.go = "Regata_Head_5";
			pchar.Ship.Name = "Saint Catherine";
		break;
		
		case "Regata_Head_5":
			dialog.text = "Ora parliamo della regata in sé. Ascolta con attenzione. Ti darò anche un foglio con le regole.\nLa regata comincia e finisce a Port Royal. Ci sono cinque tappe che dovrai raggiungere.\nLa prima è da Port Royal a Belize, Costa Occidentale\nLa seconda da Belize a Port-au-Prince, Hispaniola\nLa terza da Port-au-Prince a St.John's, Antigua\nLa quarta da St.John's a Bridgetown, Barbados\nE infine da Bridgetown a Port Royal\nTutto chiaro?";
			link.l1 = "Chiarissimo, signore.";
			link.l1.go = "Regata_Head_6";
		break;
		
		case "Regata_Head_6":
			dialog.text = "Splendido. Devi presentarti all'ufficio portuale di ciascuna di queste città: Belize, Port-au-Prince, St.John's, Bridgetown. Sarai squalificato se salti una di queste città o alteri l’ordine giusto.\nGli uffici resteranno aperti ventiquattr’ore su ventiquattro durante tutta la regata. Bussa alla porta e ti faranno entrare.";
			link.l1 = "Capito.";
			link.l1.go = "Regata_Head_7";
		break;
		
		case "Regata_Head_7":
			dialog.text = "È vietato cambiare nave o aggiungerne altre alla tua squadra. Questo verrà controllato in ogni città, tienilo a mente.";
			link.l1 = "Ci penserò su. E chi di solito viene ritenuto vincitore, e possiamo parlare dei premi?";
			link.l1.go = "Regata_Head_8";
		break;
		
		case "Regata_Head_8":
			dialog.text = "C'è un solo vincitore in regata – il capitano la cui nave sarà la prima ad arrivare a Port-Royal. Il premio è di gran valore. Il vincitore si porterà a casa una grossa somma – 250.000 pesos. In più, riceverà anche una serie di doni preziosi.";
			link.l1 = "Allora, i perdenti non beccano un accidente?";
			link.l1.go = "Regata_Head_9";
		break;
		
		case "Regata_Head_9":
			dialog.text = "Esatto. Inoltre, un sacco di ricconi e poveracci delle colonie inglesi scommettono sul vincitore della regata. Puoi anche puntare... su te stesso. Di solito ogni capitano lo fa. Se vinci, guadagnerai ancor di più e non dimenticarti della motivazione. Di norma accetto io le scommesse\nVuoi puntare sulla tua vittoria?";
			link.l1 = "Ah! Certo che ci sto. Quanto posso puntare?";
			link.l1.go = "Regata_rate";
			link.l2 = "Ci penserò. Forse scommetterò.";
			link.l2.go = "Regata_Head_10";
		break;
		
		case "Regata_Head_10":
			if (CheckAttribute(pchar, "questTemp.Regata.Begin"))
			{
				dialog.text = "Pensa pure se vuoi. Hai ancora un po' di tempo prima che inizi la regata.";
				link.l1 = "Va bene. Quando si comincia?";
				link.l1.go = "Regata_Head_11";
				DeleteAttribute(pchar, "questTemp.Regata.Rate");
				pchar.questTemp.Regata.Ratenext = "true";
			}
			else
			{
				dialog.text = "Pensa pure, se vuoi. Hai ancora un po’ di tempo prima che inizi la regata.";
				link.l1 = "Va bene.";
				link.l1.go = "exit";
			}
		break;
		
		case "Regata_Head_11":
			CreateRegataAdversaries();
			dialog.text = "Tra tre giorni, a mezzodì. Presentati al molo, e non tardare. Avrai cinque rivali."+pchar.questTemp.Regata.AdversaryName.a+", della "+pchar.questTemp.Regata.AdversaryShipName.a+"\n"+pchar.questTemp.Regata.AdversaryName.b+", della "+pchar.questTemp.Regata.AdversaryShipName.b+"\n"+pchar.questTemp.Regata.AdversaryName.c+", della "+pchar.questTemp.Regata.AdversaryShipName.c+"\n"+pchar.questTemp.Regata.AdversaryName.d+", della "+pchar.questTemp.Regata.AdversaryShipName.d+"\n"+pchar.questTemp.Regata.AdversaryName.e+", della "+pchar.questTemp.Regata.AdversaryShipName.e+"\nTutti loro sono capitani navigati. Beh, pare sia tutto. Prendi comunque il foglio delle regole. Ci si vede alla partenza!";
			link.l1 = "Addio, signore.";
			if (Pchar.BaseNation == SPAIN || Pchar.BaseNation == HOLLAND) link.l1.go = "Regata_Head_13";
			else link.l1.go = "Regata_Head_12";
		break;
		
		case "Regata_Head_12":
			DialogExit();
			pchar.quest.RegataToPortRoyalTimeOver.over = "yes";//снять таймер
			SetFunctionTimerCondition("Regata_SetTime", 0, 0, 3, false);
			pchar.quest.Regata_Lost.win_condition.l1 = "Timer";
			pchar.quest.Regata_Lost.win_condition.l1.date.hour  = 13.0;
			pchar.quest.Regata_Lost.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 3);
			pchar.quest.Regata_Lost.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 3);
			pchar.quest.Regata_Lost.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 3);
			pchar.quest.Regata_Lost.function = "Regata_Lost";
			pchar.quest.Regata_Start.win_condition.l1 = "Timer";
			pchar.quest.Regata_Start.win_condition.l1.date.hour  = 12.0;
			pchar.quest.Regata_Start.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 3);
			pchar.quest.Regata_Start.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 3);
			pchar.quest.Regata_Start.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 3);
			pchar.quest.Regata_Start.win_condition.l2 = "locator";
			pchar.quest.Regata_Start.win_condition.l2.location = "Portroyal_town";
			pchar.quest.Regata_Start.win_condition.l2.locator_group = "reload";
			pchar.quest.Regata_Start.win_condition.l2.locator = "reload1_back";
			pchar.quest.Regata_Start.function = "Regata_Start";
			AddQuestRecordInfo("RegataRules", "1");
			NextDiag.CurrentNode = "Regata_Prepare";
			DeleteAttribute(pchar, "questTemp.Regata.Begin");
			pchar.questTemp.Regata.Prepare = "true";
			AddQuestRecord("Regata", "2");
		break;
		
		case "Regata_Head_13":
			dialog.text = "Aspetta! Ti darò la licenza di 30 giorni per visitare i porti inglesi e francesi. La regata non durerà più di un mese. Prendila, ti prego.";
			link.l1 = "Grazie!";
			link.l1.go = "Regata_Head_12";
			GiveNationLicence(HOLLAND, 30);
		break;
		
		case "Regata_rate":
			dialog.text = "Quanto vuoi scommettere?";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "Regata_rate_1";
			link.l2 = "Suppongo di aver ancora bisogno di un po' di tempo per riflettere.";
			link.l2.go = "Regata_Head_10";
		break;
		
		case "Regata_rate_1":
			int iQty = sti(dialogEditStrings[4]);
			pchar.questTemp.Regata.Rate = sti(iQty);
			if (iQty < 10000)
			{
				dialog.text = "Signore, questa non è una burla, né è divertente. Non muovo un dito per una somma così meschina.";
				link.l1 = "Perdona... Riconsideriamo la posta in gioco.";
				link.l1.go = "Regata_rate";
				break;
			}
			if (iQty > 100000)
			{
				dialog.text = "Signore, non posso accettare una posta simile secondo le regole della regata. Riducetela a una somma ragionevole.";
				link.l1 = "Peccato. Riconsideriamo la somma.";
				link.l1.go = "Regata_rate";
				break;
			}
			dialog.text = ""+iQty+"?   Una bella posta, questa.   Accetto la sfida.   I vostri dobloni, signore?";
			if (makeint(Pchar.money) >= sti(pchar.questTemp.Regata.Rate))
			{
				link.l1 = "Per favore, prendilo.";
				link.l1.go = "Regata_rate_2";
			}
			link.l2 = "Non ho abbastanza monete adesso. Tornerò da te più tardi e faremo la nostra puntata. E ci rifletterò ancora su, forse rivedrò la somma.";
			link.l2.go = "Regata_Head_10";
		break;
		
		case "Regata_rate_2":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Regata.Rate));
			pchar.questTemp.Regata.Advantage = sti(pchar.questTemp.Regata.Rate)*(1.5+frand(1.5)); // dlc
			dialog.text = "Splendido! Ora tutto ciò che ti resta da fare è arrivare primo e il premio sarà tuo. Il suo valore finale potrebbe cambiare, tutto dipende da quanti scommetteranno su di te alla fine.";
			if (!CheckAttribute(pchar, "questTemp.Regata.Ratenext"))
			{
				link.l1 = "Capisco. Quando ha inizio la regata?";
				link.l1.go = "Regata_Head_11";
			}
			else
			{
				link.l1 = "Capisco. Aspetterò l’inizio. A presto!";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.Regata.Ratenext");
				NextDiag.TempNode = "Regata_Prepare";
			}
		break;
		
		case "Regata_Prepare":
			dialog.text = "Ah, siete tornato di nuovo, capitano "+GetFullName(pchar)+"? Che vuoi, marinaio?";
			if (!CheckAttribute(pchar, "questTemp.Regata.Rate"))
			{
				link.l1 = "Voglio scommettere sulla mia vittoria.";
				link.l1.go = "Regata_rate";
			}
			link.l2 = "No, non è nulla. Volevo solo salutarti.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Regata_Prepare";
		break;
		
		//старт регаты
		case "Regata_CitMan":
			dialog.text = RandPhraseSimple(LinkRandPhrase("Capitano, sei alla tua prima traversata? Lascia che ti dia un consiglio: fa' attenzione. I tuoi rivali potrebbero prepararti delle sorprese davvero sgradite...","Capitano, ho scommesso tutto su di te. Non deludermi!","Capitano, la gente dei porti della regata potrebbe proporti di comprare qualcosa. Spesso può tornare davvero utile. Tienilo a mente."),LinkRandPhrase("Che tu possa avere venti favorevoli, capitano!","Capitano, sii prudente, gli spagnoli dannati danno spesso la caccia ai luggers che solcano le loro acque.","Ho sentito dire che certi loschi figuri spesso offrono i loro 'servigi' ai capitani delle regate. Sta a te decidere se accettare o meno le loro proposte."));
			link.l1 = "Sì, sì, certo... grazie, suppongo.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_CitMan";
		break;
		
		case "Regata_CitWom":
			dialog.text = LinkRandPhrase("Capitano, io e mio marito abbiamo scommesso diecimila sulla tua vittoria. Non ci deludere! Pregherò per te!","Capitano! Che la fortuna ti assista!","Uhm... siete un capitano davvero audace e coraggioso...");
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_CitWom";
		break;
		
		case "Regata_CitHorse":
			dialog.text = LinkRandPhrase("Ehi, marinaio! Saluta la bellezza! Ti aspetterò al tuo ritorno!","Ehi, vecchio lupo di mare! La signora ha detto che mi darà in premio gratis al vincitore della regata... Prova a vincere tu, che sei così affascinante!","Non dimenticarti di farci visita quando tornerai, bel capitano, ti daremo piaceri degni dei migliori bordelli dei Caraibi!");
			link.l1 = "Ebbene, ahah... Ci penserò su, grazie!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_CitHorse";
		break;
		
		case "Regata_Prepare_1":
			if (sti(environment.time) < 12.0)
			{
				dialog.text = "Capitano, la regata comincia a mezzogiorno. Ora potete riposarvi, stiamo allestendo la festa. Tornate verso il meriggio, anche i vostri rivali faranno lo stesso.";
				link.l1 = "Molto bene, signore! Resterò in attesa dell’inizio...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Eccoti qua, capitano.";
				link.l1 = "Io e la mia ciurma siamo pronti, signore! Attendo solo il segnale...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Regata_Prepare_1";
		break;
		
		case "Regata_Start":
			dialog.text = "Ebbene, signori, eccoci qua. Dichiaro aperta la regata. Conoscete le regole. Colui che tornerà qui per primo sarà celebrato come il vincitore. Signore e signori, auguriamo buona fortuna ai nostri coraggiosi capitani!\nSignori! Siete pronti? In posizione! Pronti! Via!";
			link.l1 = "...";
			link.l1.go = "Regata_Start_1";
		break;
		
		case "Regata_Start_1":
			DialogExit();
			PlaySound("people fight\mushketshot.wav");
			log_info("The regatta has started! Get aboard! Head to Belize!");
			for (i=1; i <=5; i++)
			{
				sld = characterFromId("Regata_Cap_F"+i);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
			}
			Island_SetReloadEnableGlobal("Jamaica", false);//на остров нельзя
			SetFunctionTimerCondition("ReturnJamaicaNorm", 0, 0, 1, false);//таймер на возврат нормы
			LocatorReloadEnterDisable("Portroyal_town", "reload1_back", false);//откроем выход в море
			DeleteAttribute(pchar, "questTemp.Regata.Prepare");
			pchar.questTemp.Regata.Go = "true";
			pchar.questTemp.Regata.Town = "Beliz";
			pchar.quest.Regata_PU.win_condition.l1 = "locator";
			pchar.quest.Regata_PU.win_condition.l1.location = "Beliz_town";
			pchar.quest.Regata_PU.win_condition.l1.locator_group = "reload";
			pchar.quest.Regata_PU.win_condition.l1.locator = "reload10_back";
			pchar.quest.Regata_PU.win_condition.l2 = "Night";
			pchar.quest.Regata_PU.function = "RegataPU_Open";//вход в ПУ ночью
			//ситуации
			pchar.quest.Regata_ShYarder.win_condition.l1 = "location";
			pchar.quest.Regata_ShYarder.win_condition.l1.location = "Beliz_town";
			pchar.quest.Regata_ShYarder.function = "RegataShipyarder";
			sld = characterFromId("Beliz_shipyarder");
			LAi_RemoveLoginTime(sld);
			AddQuestRecord("Regata", "3");
		break;
		//старт регаты
		
		//верфист с парусами
		case "Regata_Shipyarder":
			dialog.text = "Saluti, capitano! Mi dicono che prendi parte alla regata dei Caraibi.";
			link.l1 = "È vero. Le notizie volano tra queste isole più rapide d’un soffio di vento.";
			link.l1.go = "Regata_Shipyarder_1";
		break;
		
		case "Regata_Shipyarder_1":
			dialog.text = "Lo fanno, capitano. Ho una proposta per voi. Riguarda la vostra nave e la regata.";
			link.l1 = "Heh! Interessante. Ti sto ascoltando, signore.";
			link.l1.go = "Regata_Shipyarder_2";
		break;
		
		case "Regata_Shipyarder_2":
			dialog.text = "Ho un set di vele perfette per una lugger, tessute con il miglior cotone che si trovi. Queste vele daranno alla tua nave più sprint e ti faranno guadagnare tempo sui tuoi rivali.\nSono pronto a vendertele, se sei disposto a concludere l'affare.";
			link.l1 = "Quanto chiedi per queste vele?";
			link.l1.go = "Regata_Shipyarder_3";
		break;
		
		case "Regata_Shipyarder_3":
			dialog.text = "Solo 15 000 pesos. Devi ammettere che è un prezzo assai modesto per una... situazione del genere.";
			if (makeint(Pchar.money) >= 15000)
			{
				link.l1 = "Sono d'accordo. Sto acquistando queste nuove vele per il mio lugger. Ecco, prendi i miei soldi, signore. Potresti essere così gentile da portarle sulla mia nave mentre io mi occupo delle formalità?";
				link.l1.go = "Regata_Shipyarder_4";
			}
			link.l2 = "Non ho quei soldi. Quindi non potrò comprare le tue vele.";
			link.l2.go = "Regata_Shipyarder_exit";
		break;
		
		case "Regata_Shipyarder_4":
			AddMoneyToCharacter(pchar, -15000);
			dialog.text = "Sarà fatto, signore. I miei uomini aspettano solo un tuo cenno, e ti giuro che non te ne pentirai. E poi queste vele sono tinte di un bel blu. La tua dama saprà apprezzarle.";
			link.l1 = "D'accordo allora! Beh, io devo andare e tu pensa alle vele.";
			link.l1.go = "Shipyarder_exit";
			for (i=1; i <=5; i++)
			{
				if (i==1) sTemp = "a";
				if (i==2) sTemp = "b";
				if (i==3) sTemp = "c";
				if (i==4) sTemp = "d";
				if (i==5) sTemp = "e";
				pchar.questTemp.Regata.AdversarySecondTransition.Time.(sTemp) = sti(pchar.questTemp.Regata.AdversarySecondTransition.Time.(sTemp))+12;//выиграл 12 часов у всех
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversarySecondTransition.Time.(sTemp)));
			}
			RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails = 3;
			SetSailsColor(Pchar, 5);
			AddQuestRecord("Regata", "28");
		break;
		
		case "Regata_Shipyarder_exit":
			dialog.text = "Che peccato. Beh, è la tua scelta. Addio, capitano.";
			link.l1 = "Addio!";
			link.l1.go = "Shipyarder_exit";
			pchar.questTemp.Regata.AdversarySecondTransition.Time.d = sti(pchar.questTemp.Regata.AdversarySecondTransition.Time.d)-16;//четвертый соперник выиграл 16 часов
			log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversarySecondTransition.Time.e));
			AddQuestRecord("Regata", "29");
		break;
		
		case "Shipyarder_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload5_back", "Beliz_Shipyard", "sit", "sit1", "ReturnRegataSYNorm", 5);
		break;
		//верфист с парусами
		
		//контрики с пушками
		case "Regata_Contra":
			dialog.text = "Ciao, capitano "+GetFullName(pchar)+"   Dobbiamo parlarti... in realtà è solo una... proposta d'affari.";
			link.l1 = "Mm. Interessante... e come diavolo sai chi sono io?";
			link.l1.go = "Regata_Contra_1";
		break;
		
		case "Regata_Contra_1":
			dialog.text = "Che vi devo dire, mi han sempre detto che avevo un certo talento... Ah-ah, la Regata è nel pieno del suo furore e voi siete tra i protagonisti, Capitano rinomato!";
			link.l1 = "Capisco. Su, sputa il rospo.";
			link.l1.go = "Regata_Contra_2";
		break;
		
		case "Regata_Contra_2":
			if (sti(pchar.questTemp.Regata.Index != 1))
			{
				sTemp = pchar.questTemp.Regata.ContraIndex;
				dialog.text = "Sappiamo che c’è ancora un altro partecipante davanti a te - "+pchar.questTemp.Regata.AdversaryName.(sTemp)+" del "+pchar.questTemp.Regata.AdversaryShipName.(sTemp)+". È salpato dal porto poco tempo fa e presto starà navigando vicino al capo di Gonaives.";
			}
			else
			{
				dialog.text = "Sappiamo che c’è un altro partecipante proprio dietro di te - "+pchar.questTemp.Regata.AdversaryName.b+" del "+pchar.questTemp.Regata.AdversaryShipName.b+". Sarà qui tra qualche ora.";
			}
			link.l1 = "Hmm... sei ben informato, a quanto pare.";
			link.l1.go = "Regata_Contra_3";
		break;
		
		case "Regata_Contra_3":
			if (sti(pchar.questTemp.Regata.Index != 1)) sTemp = "letting you pass ahead of him and take his position";
			else sTemp = "therefore you will be taking a lead for a long time";
			dialog.text = "Assolutamente. Ora veniamo al sodo. Ti offriamo il nostro aiuto in cambio del tuo denaro. Abbiamo piazzato quattro cannoni della nostra nave sul promontorio dietro la baia di Gonaives. Qualsiasi nave da regata dovrà doppiare quel punto.\nI cannoni sono carichi con palle a catena. Se ci accordiamo, dirò ai nostri compari artiglieri di stracciare le vele del tuo rivale, così sarà costretto a perdere tempo a ripararle, "+sTemp+".";
			link.l1 = "Quanto vuoi per questo servigio?";
			link.l1.go = "Regata_Contra_4";
			link.l2 = "No. Non userò mai simili mezzucci per vincere. Vi siete sbagliati su di me. Addio, gentiluomini.";
			link.l2.go = "Regata_Contra_exit";
		break;
		
		case "Regata_Contra_exit":
			dialog.text = "Ebbene, capitano, sta a voi decidere. Addio.";
			link.l1 = "Grazie per l'informazione sul capo. Starò alla larga da lì.";
			link.l1.go = "Contra_exit";
			AddQuestRecord("Regata", "31");
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
		break;
		
		case "Regata_Contra_4":
			if (sti(pchar.questTemp.Regata.Index != 1)) iTemp = 50000;
			else iTemp = 30000;
			dialog.text = "Poco. Solo "+iTemp+" pesos. E uno dei tuoi rivali perderà quasi due giorni a causa di... un piccolo incidente, ah-ah!";
			if (makeint(Pchar.money) >= iTemp)
			{
				link.l1 = "Eh! Parli bene, amico mio! Pago io. Ma quali garanzie ho che farai davvero il tuo lavoro? E che non sparerai alla mia nave quando passerò il capo?";
				link.l1.go = "Regata_Contra_5";
			}
			link.l2 = "Non ho tutto quel denaro. Quindi non potrò servirimi dei tuoi servigi.";
			link.l2.go = "Regata_Contra_exit";
		break;
		
		case "Regata_Contra_5":
			dialog.text = "Capitano, per carità, siamo contrabbandieri, non dei pirati. Siamo tutti uomini d’onore... a modo nostro. Avrai già usato i nostri servigi, vero? Ti do la mia parola. Puoi fidarti.";
			link.l1 = "D’accordo, va bene, prendi i tuoi dobloni.";
			link.l1.go = "Regata_Contra_6";
		break;
		
		case "Regata_Contra_6":
			AddQuestRecord("Regata", "30");
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
			dialog.text = "Sarai ben contento di questo affare, capitano. E farò sapere subito ai miei ragazzi armati. Buona fortuna!";
			link.l1 = "Altrettanto a te...";
			link.l1.go = "Contra_exit";
			if (sti(pchar.questTemp.Regata.Index != 1))
			{
				AddMoneyToCharacter(pchar, -50000);
				sTemp = pchar.questTemp.Regata.ContraIndex;
				pchar.questTemp.Regata.AdversaryThirdTransition.Time.(sTemp) = sti(pchar.questTemp.Regata.AdversaryThirdTransition.Time.(sTemp))+48;//задержка на 48 часов
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversaryThirdTransition.Time.(sTemp)));
			}
			else
			{
				AddMoneyToCharacter(pchar, -30000);
				pchar.questTemp.Regata.AdversaryThirdTransition.Time.b = sti(pchar.questTemp.Regata.AdversaryThirdTransition.Time.b)+36;//задержка на 36 часов
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversaryThirdTransition.Time.b));
			}
		break;
		
		case "Contra_exit":
			DialogExit();
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("RegataContra_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "quest", "quest2", "none", "", "", "", 10.0);
			}
		break;
		//контрики с пушками
		
		//падре
		case "Regata_Padre":
			pchar.questTemp.Regata.BranderName = GenerateRandomNameToShip(ENGLAND);
			dialog.text = "Buongiorno a te, figliolo. Desidero salutarti e umilmente domandarti: vuoi forse contribuire al tesoro della parrocchia come devoto servitore d’Inghilterra e del nostro grande Signore?";
			link.l1 = "Padre, la carità si fa per voce dell’anima, non per costrizione. Comincio a pensare che tutti su quest’arcipelago abbiano deciso di spennare i capitani della regata...";
			link.l1.go = "Regata_Padre_exit";
			link.l2 = "Certo, padre santo. Quanto sarebbe sufficiente?";
			link.l2.go = "Regata_Padre_1";
		break;
		
		case "Regata_Padre_1":
			dialog.text = "Tanto quanto ti permetteranno il desiderio e le tue possibilità, figliolo. La nostra parrocchia sarà grata anche per il più piccolo obolo.";
			Link.l1.edit = 4;			
			link.l1 = "";
			link.l1.go = "Regata_Padre_2";
		break;
		
		case "Regata_Padre_2":
			iTemp = sti(dialogEditStrings[4]);
			if (iTemp <= 0 || sti(pchar.money) < iTemp)
			{
				dialog.text = "Questa è una cattiva disposizione d’animo, figliolo. Tutti portiamo dei peccati, non dimenticare la tua anima. Dovrai presentarti davanti al nostro Creatore… e forse molto presto.";
				link.l1 = "Non mi servono le tue prediche, reverendo. Addio.";
				link.l1.go = "Padre_exit";
				ChangeCharacterComplexReputation(pchar, "nobility", -3);
				AddQuestRecord("Regata", "35");
				break;
			}
			if (iTemp > 0 && iTemp <= 1000)//ничего не скажет
			{
				dialog.text = "La nostra parrocchia ed io vi ringraziamo per questo umile dono.";
				link.l1 = "Sei il benvenuto, padre santo.";
				link.l1.go = "Padre_exit";
				AddMoneyToCharacter(pchar, -iTemp);
				AddQuestRecord("Regata", "35");
			}
			if (iTemp > 1000 && iTemp <= 5000)//1 категория - намекнет
			{
				dialog.text = "La nostra parrocchia e io ti ringraziamo per questo dono. E voglio avvertirti, figliolo, che certi uomini peccaminosi tramano contro di te. Sta’ attento in mare!";
				link.l1 = "Padre, ogni giorno la gente trama alle mie spalle... Ma vi ringrazio per la vostra premura verso la mia sorte.";
				link.l1.go = "Padre_exit";
				AddMoneyToCharacter(pchar, -iTemp);
				AddQuestRecord("Regata", "34");
				AddQuestUserData("Regata", "sMoney", iTemp);
			}
			if (iTemp > 5000 && iTemp <= 10000)//2 категория - скажет
			{
				dialog.text = "Ti ringrazio a nome della nostra parrocchia per questo dono prezioso. In cambio, voglio metterti in guardia: gente davvero malvagia sta tramando contro di te. Ho sentito che questi luridi apostati hanno intenzione di mandare a fondo la tua nave proprio in questo porto.\nHanno già approntato un bastimento pieno di polvere da sparo per questa malefatta. Sta' in guardia, figliolo, queste anime perdute fanno sul serio con le loro nefande intenzioni... Che il Signore ti protegga!";
				link.l1 = "Grazie, padre santo. Starò all’erta.";
				link.l1.go = "Padre_exit";
				AddMoneyToCharacter(pchar, -iTemp);
				AddQuestRecord("Regata", "33");
				AddQuestUserData("Regata", "sMoney", iTemp);
			}
			if (iTemp > 10000)//3 категория - расскажет полностью
			{
				dialog.text = "Sei davvero generoso, figliolo. L’umiltà di un servo del Signore non mi consente d’accettare tutta la somma che desideri donare per il bene della nostra chiesa. Mi accontenterò di soli 10.000 pesos.\nIn cambio, voglio metterti in guardia: uomini malvagi tramano contro di te. Ho sentito dire che questi infami apostati intendono affondare la tua nave proprio qui, nel porto.\nHanno preparato una goletta piena di polvere da sparo, chiamata '"+pchar.questTemp.Regata.BranderName+"’, sta navigando sotto la bandiera inglese per avvicinarsi a te senza destare sospetti. Fa’ attenzione, figliolo, queste anime perdute son decise nei loro misfatti. Distruggili, ti concedo l’assoluzione per questo peccato. Che Dio ti benedica! Pregherò per te, figliolo.";
				link.l1 = "Grazie, padre santo. Se quei canaglie osano fare qualche porcheria, li spedisco dritti all’inferno!";
				link.l1.go = "Padre_exit";
				AddMoneyToCharacter(pchar, -10000);
				ChangeCharacterComplexReputation(pchar, "nobility", 2);
				AddQuestRecord("Regata", "32");
				AddQuestUserData("Regata", "sText", pchar.questTemp.Regata.BranderName);
			}
		break;
		
		case "Regata_Padre_exit":
			dialog.text = "Non t'adirare, figliolo. L'ira è peccato. Hai il diritto di rifiutare l'elemosina. Va' in pace, figliolo.";
			link.l1 = "Addio, sant’uomo.";
			link.l1.go = "Padre_exit";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddQuestRecord("Regata", "35");					  
		break;
		
		case "Padre_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload7_back", "SentJons_church", "barmen", "stay", "ReturnRegataPadreNorm", 5);
		break;
		
		case "Regata_Spyglass":
			dialog.text = "Buon dì a voi, capitano! Il mio nome è "+npchar.name+" e mi piacerebbe...";
			link.l1 = "...   per offrirmi qualcosa... Dico bene, signorina?";
			link.l1.go = "Regata_Spyglass_1";
		break;
		
		case "Regata_Spyglass_1":
			dialog.text = "Ma certo, capitano! E perché vi stupite così? Siete un bel marinaio e partecipate alla regata, sicuro che tutti siano pronti a vendervi qualche utile roba da bordo.";
			link.l1 = "D’accordo, bellezza, hai ragione. Che hai da offrirmi?";
			link.l1.go = "Regata_Spyglass_2";
		break;
		
		case "Regata_Spyglass_2":
			if(hrand(11) > 10)//отличная труба
			{
				pchar.questTemp.Regata.Spy = "spyglass4";
				sTemp = "an excellent spyglass";
				pchar.questTemp.Regata.SpyPrice = 20000;
				pchar.questTemp.Regata.SpyIndex = 12;//выигрыш - 12 часов
			}
			else
			{
				if(hrand(11) < 6)//обычная труба
				{
					pchar.questTemp.Regata.Spy = "spyglass2";
					sTemp = "an ordinary spyglass";
					pchar.questTemp.Regata.SpyPrice = 1800;
					pchar.questTemp.Regata.SpyIndex = 4;//выигрыш - 4 часа
				}
				else//хорошая труба - как пригодится
				{
					pchar.questTemp.Regata.Spy = "spyglass3";
					sTemp = "a good spyglass";
					pchar.questTemp.Regata.SpyPrice = 10000;
					pchar.questTemp.Regata.SpyIndex = 8;//выигрыш - 8 часов
				}
			}
			dialog.text = "Ecco, dai un'occhiata. L'ho ereditato da mio padre. Anche lui era un marinaio, proprio come te, e aveva un sacco di gingilli da navigazione. Io non ne ho bisogno, ma a te tornerà certamente utile. Chiedo solo "+FindRussianMoneyString(sti(pchar.questTemp.Regata.SpyPrice))+" per questo.";
			if (sti(pchar.money) >= sti(pchar.questTemp.Regata.SpyPrice))
			{
				link.l1 = "Ebbene, ebbene..."+sTemp+"! Interessante! Dico, te la compro io. Per quegli occhietti belli. Allora, vuoi "+FindRussianMoneyString(sti(pchar.questTemp.Regata.SpyPrice))+" per questo? Prego, prendi i tuoi dobloni.";
				link.l1.go = "Regata_Spyglass_3";
			}
			link.l2 = "Hm..."+sTemp+"   No, ragazza, mi spiace, ma non mi serve. Ho già un bel cannocchiale tutto mio. Quindi... ahimè!";
			link.l2.go = "Regata_Spyglass_exit";
		break;
		
		case "Regata_Spyglass_3":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Regata.SpyPrice));
			GiveItem2Character(pchar, pchar.questTemp.Regata.Spy);
			dialog.text = "Grazie, capitano. Spero che ti sia d’aiuto. Son lieto che tu l’abbia trovato utile. Buona fortuna nella regata!";
			link.l1 = "Grazie, "+npchar.name+"Addio, allora.";
			link.l1.go = "Spyglass_exit";
			for (i=1; i <=5; i++)
			{
				if (i==1) sTemp = "a";
				if (i==2) sTemp = "b";
				if (i==3) sTemp = "c";
				if (i==4) sTemp = "d";
				if (i==5) sTemp = "e";
				pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp) = sti(pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp))+sti(pchar.questTemp.Regata.SpyIndex);//купил трубу - выиграл время
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp)));
			}
		break;
		
		case "Regata_Spyglass_exit":
			dialog.text = "Che peccato, capitano. Speravo che vi sarebbe stato utile. Pazienza, tenterò di piazzarlo a qualcun altro. Addio!";
			link.l1 = "Addio, "+npchar.name+".";
			link.l1.go = "Spyglass_exit";
			pchar.questTemp.Regata.AdversaryFourthTransition.Time.c = sti(pchar.questTemp.Regata.AdversaryFourthTransition.Time.c)-sti(pchar.questTemp.Regata.SpyIndex);//третий соперник выиграл время
		break;
		
		case "Spyglass_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10);
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		case "Regata_SiegeOfficer":
			dialog.text = "Saluti, capitano. Non siete forse uno dei partecipanti alla regata? Ho ragione?";
			link.l1 = "Sì. E qual è l’accordo, ufficiale?";
			link.l1.go = "Regata_SiegeOfficer_1";
		break;
		
		case "Regata_SiegeOfficer_1":
			dialog.text = "Sarai già al corrente che la nostra colonia è sotto assedio spagnolo. Ecco perché il nostro governatore desidera parlarti. Potresti avere la cortesia di fargli visita? La faccenda è alquanto urgente.";
			link.l1 = "Hm... Va bene, andrò subito a vedere Sua Eccellenza, anche se non capisco proprio come io possa essere coinvolto nelle faccende militari.";
			link.l1.go = "Regata_SiegeOfficer_2";
		break;
		
		case "Regata_SiegeOfficer_2":
			dialog.text = "Sei coinvolto, capitano. Non perdiamo tempo e andiamo alla residenza. Seguimi.";
			link.l1.go = "Regata_SiegeOfficer_3";
		break;
		
		case "Regata_SiegeOfficer_3":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "Bridgetown_townhall", "goto", "governor1", "RegataSiegeHover", -1);
		break;
		
		case "Regata_SiegeOfficer_4":
			dialog.text = "Signore! Son pronto a imbarcare i civili sulla vostra nave. Salpiamo ora?";
			link.l1 = "Sì, certo. Salpiamo subito. Dì ai marinai di salire sulle scialuppe.";
			link.l1.go = "Regata_SiegeOfficer_5";
		break;
		
		case "Regata_SiegeOfficer_5":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "RegataSiegeOpen", -1);
			for (i=1; i <=9; i++)
			{
				sld = characterFromId("RegataBridgWom_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "quest", "quest1", "none", "", "", "", 30);
			}
		break;
		
		case "Regata_SiegeOfficer_6":
			dialog.text = "Ce l’abbiamo fatta... Pare che questo sloop fosse un ricognitore della squadra e quei bastardi castigliani stavano spiando in giro. Capitano, aiutatemi a portare le donne nelle grotte, c’è la possibilità che ci siano altri distaccamenti spagnoli.";
			link.l1 = "D'accordo. Andiamo!";
			link.l1.go = "Regata_SiegeOfficer_7";
		break;
		
		case "Regata_SiegeOfficer_7":
			DialogExit();
			sld = characterFromId("SiegeOfficer");
			LAi_ActorFollowEverywhere(sld, "", -1);
			pchar.quest.Regata_Siege3.win_condition.l1 = "location";
			pchar.quest.Regata_Siege3.win_condition.l1.location = "Barbados_cave";
			pchar.quest.Regata_Siege3.function = "RegataBarbadosCave";
		break;
		
		case "Regata_SiegeOfficer_8":
			dialog.text = "Ti sono debitore, capitano! Se non fosse stato per te e il tuo coraggio... Sei un vero eroe, hai portato a termine questa faccenda sfidando ogni pericolo e persino il tuo tornaconto. Ho pensato a come ricompensarti... e c’è un modo per darti un vantaggio nella regata.";
			link.l1 = "Interessante. Qual è questa via?";
			link.l1.go = "Regata_skiper";
		break;
		
		case "Regata_Hovernor":
			dialog.text = "Saluti, capitano "+GetFullName(pchar)+"È bene che tu sia arrivato. La nostra città ha bisogno del tuo aiuto.";
			link.l1 = "Signore, se parlate dello squadrone spagnolo che sta assaltando la vostra colonia proprio ora, ebbene, non ho la minima idea di come potrei aiutarvi. Io comando un lugger, non una nave di linea...";
			link.l1.go = "Regata_Hovernor_1";
		break;
		
		case "Regata_Hovernor_1":
			dialog.text = "Ascoltami, capitano, e capirai. Siamo nei guai seri. La città è sotto assedio spagnolo. Una battaglia decisiva col forte sta per cominciare. Inoltre, qualche centinaio di spagnoli è già sbarcato e ha bloccato ogni uscita dalla città, adesso possono attaccarci sia dal mare che da terra.\nLa guarnigione del forte si sta preparando a difendere la città dalla squadra navale ma non ci sono abbastanza soldati dentro l'abitato. Ogni uomo capace di brandire un'arma è stato mobilitato, ma cosa ne sarà degli altri?\nA Bridgetown ci sono centinaia di donne. Riesci a immaginare cosa ne sarà di loro se non riusciremo a difendere la nostra colonia? Credo che tu capisca.";
			link.l1 = "Signore, La capisco, ma di nuovo, come posso esserLe utile? Cosa cerca da me? Che affronti vascelli di linea o che arruoli la mia ciurma nella milizia cittadina?";
			link.l1.go = "Regata_Hovernor_2";
		break;
		
		case "Regata_Hovernor_2":
			switch (sti(Pchar.BaseNation))
			{
				case ENGLAND: sTemp = "You are English , help us to save English citizens and what is important - women!" break;
				case FRANCE: sTemp = "You are French, so you basically are our ally, help us to save English citizens and what is more important - women!" break;
				case SPAIN: sTemp = "I know that you are Spanish and these are your people in the sea, so I know that I am already asking for a lot, but these women are innocent and have nothing to do with this battle. So please I beg of you, help them!" break;
				case HOLLAND: sTemp = "I know that you are Dutch and our nations are at war, but you are participating in the English regatta under the English flag. Don't you think that it is right to fight for innocent and peaceful people, for women? Please captain, help them!" break;
			}
			dialog.text = "Nessuna delle due. Ti chiedo solo una cosa. Porta via da qui donne e bambini sulla tua nave. Non sono molti, forse un centinaio. Conducili a Capo Harrison insieme al tenente Mahony, lui si assicurerà che siano al sicuro nella grotta.\nSono certo che gli spagnoli non li cercheranno lì. Non ho più navi da mandare, tutto ciò che avevamo è stato affondato dalla squadriglia spagnola. Sei la mia ultima speranza. Puoi portarli tutti al capo in una sola traversata, anche se la tua nave sarà carica fino all’orlo. Le navi di linea non ti seguiranno.\nNon posso chiedere a nessun altro di farlo. "+sTemp+"";
			link.l1 = "Signore, mi rincresce, ma la mia nave è già strapiena e non reggerebbe così tanta gente nemmeno per due traversate. Basterebbe una palla di cannone vagante per mandare la mia nave e le vostre donne a fondo. Perdonatemi, ma non posso aiutarvi.";
			link.l1.go = "Regata_Hovernor_exit";
			link.l2 = "Molto bene, signore. Vi aiuterò. L’onore di un marinaio me lo impone.";
			link.l2.go = "Regata_Hovernor_3";
		break;
		
		case "Regata_Hovernor_3":
			dialog.text = "Sono lieto che tu abbia accettato. Sei un vero uomo d'arme. Il tenente Mahony condurrà donne e bambini sulla tua nave. Che il vento ti sia favorevole, Capitano!";
			link.l1 = "Grazie, signore. Non perdiamo tempo!";
			link.l1.go = "Regata_Hovernor_4";
		break;
		
		case "Regata_Hovernor_wait":
			dialog.text = "Sbrigati, capitano. Il tempo stringe.";
			link.l1 = "Sto già salpando!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_Hovernor_wait";
		break;
		
		case "Regata_Hovernor_exit":
			dialog.text = "Questo è incredibile. Non ci provi nemmeno? Beh, ne hai diritto. Non posso pretendere nulla da te. Se fossi stato un capitano qualunque, ti avrei requisito la nave per il bene di cento donne, ma partecipi alla regata, e quindi sei sotto la protezione del governatore generale delle colonie inglesi.\nSperavo che la tua coscienza avesse la meglio su di te, ma mi sbagliavo. Vai pure, e che Dio abbia pietà della tua anima!";
			link.l1 = "Addio, signore.";
			link.l1.go = "Hovernor_exit";
		break;
		
		case "Hovernor_exit":
			DialogExit();
			pchar.quest.Regata_TH.over = "yes"; // belamour снять прерывание
			pchar.questTemp.Regata.AdversaryFifthTransition.Time.e = sti(pchar.questTemp.Regata.AdversaryFifthTransition.Time.e)-36;//пятый противник выиграл 36 часов
			ChangeCharacterComplexReputation(pchar, "nobility", -8);
			ChangeCharacterNationReputation(pchar, ENGLAND, -5);
			//вертаем губера в норму
			npchar.Dialog.Filename = "Common_Mayor.c";
			npchar.dialog.currentnode = "First time";
			//удаляем лейтенанта
			sld = characterFromId("SiegeOfficer");
			sld.lifeday = 0;
			//открываем ворота и выход в море
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Bridgetown_town", "reload1_back", false);
			LocatorReloadEnterDisable("Bridgetown_town", "reload2_back", false);
			LocatorReloadEnterDisable("Bridgetown_town", "gate1_back", false);
			LocatorReloadEnterDisable("Bridgetown_town", "gate_back", false);
			LocatorReloadEnterDisable("Bridgetown_Exittown", "reload3", false);
			//остров в норму
			n = FindIsland("Barbados");	
			DeleteAttribute(Islands[n], "DontSetShipInPort");
			//осаду снимем через 5 дней
			SetFunctionTimerCondition("RegataSiegeDelete", 0, 0, 5, false);
			for (i=1; i <=9; i++)//девок счистим
			{
				sld = characterFromId("RegataBridgWom_"+i);
				sld.lifeday = 0; // patch-7
				LAi_CharacterDisableDialog(sld);
			}
			AddQuestRecord("Regata", "38");
			AddQuestUserData("Regata", "sName", GetFullName(npchar));
		break;
		
		case "Regata_Hovernor_4":
			DialogExit();
			pchar.quest.Regata_TH.over = "yes"; // belamour снять прерывание
			NextDiag.CurrentNode = "Regata_Hovernor_wait";
			sld = characterFromId("SiegeOfficer");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "Bridgetown_town", "goto", "goto4", "", 10);
			pchar.quest.Regata_evacuation.win_condition.l1 = "location";
			pchar.quest.Regata_evacuation.win_condition.l1.location = "Bridgetown_town";
			pchar.quest.Regata_evacuation.function = "RegataSiegeEvacuation";
			AddQuestRecord("Regata", "36");
			AddQuestUserData("Regata", "sName", GetFullName(npchar));
		break;
		
		case "Regata_BridgWom":
			dialog.text = "Gli spagnoli ci hanno fiutati! Dio, salvaci!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_BridgWom";
		break;
		
		case "Regata_BridgWom_1":
			dialog.text = "Il tenente Mahony è morto... dev’essere un incubo. Era un ufficiale coraggioso. Capitano, potreste portarci in una grotta? Portateci lì e ce la caveremo da soli.";
			link.l1 = "Certo. Seguimi!";
			link.l1.go = "Regata_BridgWom_2";
		break;
		
		case "Regata_BridgWom_2":
			DialogExit();
			for (i=1; i <=9; i++)
			{
				sld = characterFromId("RegataBridgWom_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			pchar.quest.Regata_Siege3.win_condition.l1 = "location";
			pchar.quest.Regata_Siege3.win_condition.l1.location = "Barbados_cave";
			pchar.quest.Regata_Siege3.function = "RegataBarbadosCave";
		break;
		
		case "Regata_BridgWom_3":
			dialog.text = "Eccoci qua... grazie, capitano! Ci hai appena salvato la pellaccia a tutti! Ho pensato a come ricompensarti... c’è un modo per aumentare le tue probabilità nella regata.";
			link.l1 = "Avanti.";
			link.l1.go = "Regata_skiper";
		break;
		
		case "Regata_skiper":
			pchar.questTemp.Regata.Name = GetFullName(npchar);
			dialog.text = "Stai puntando verso Port Royal? La rotta più breve passa per Curaçao. Torna a Bridgetown. Cerca un uomo di nome Woodrow Dougherty, un vecchio lupo di mare e navigatore esperto. Conosce a menadito le acque tra Barbados e Giamaica, potrebbe esserti di grande aiuto\nCosì risparmierai un sacco di tempo prezioso — e il tempo ti serve come il pane per vincere. Trova quest’uomo nella chiesa locale e digli che "+GetFullName(npchar)+" - ti ha mandato lui, non ti rifiuterà. Portalo a Port Royal, tanto doveva salpare proprio laggiù.";
			link.l1 = "Benissimo! Un bravo nocchiere mi tornerà utile. Addio.";
			link.l1.go = "Regata_skiper_1";
		break;
		
		case "Regata_skiper_1":
			dialog.text = "Addio, capitano! Buona fortuna!";
			link.l1 = "Forse ci rivedremo ancora...";
			link.l1.go = "Regata_skiper_2";
		break;
		
		case "Regata_skiper_2":
			DialogExit();
			AddQuestRecord("Regata", "37");
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			ChangeCharacterNationReputation(pchar, ENGLAND, 10);
			LAi_SetStayType(npchar);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0; // patch-8
			for (i=1; i <=9; i++)
			{
				sld = characterFromId("RegataBridgWom_"+i);
				LAi_SetStayType(sld);
				LAi_CharacterDisableDialog(sld);
				sld.lifeday = 0; // patch-8
			}
			//вертаем губера в норму
			sld = characterFromId("Bridgetown_Mayor");
			sld.Dialog.Filename = "Common_Mayor.c";
			sld.dialog.currentnode = "First time";
			//открываем ворота и выход в море
			LocatorReloadEnterDisable("Shore4", "boat", false);
			LocatorReloadEnterDisable("Bridgetown_town", "gate1_back", false);
			LocatorReloadEnterDisable("Bridgetown_town", "gate_back", false);
			LocatorReloadEnterDisable("Bridgetown_Exittown", "reload3", false);
			LocatorReloadEnterDisable("Barbados_cave", "reload1", false);
			bQuestDisableMapEnter = false;
			//осаду снимем через 5 дней
			SetFunctionTimerCondition("RegataSiegeDelete", 0, 0, 5, false);
			RegataSiegeSkiper();//поставим Вудро в церковь
		break;
		
		case "Regata_SiegeSkiper":
			dialog.text = "Buon dì. Cercavi qualcosa?";
			link.l1 = "Il tuo nome è Woodrow Dougherty, dico bene?";
			link.l1.go = "Regata_SiegeSkiper_1";
		break;
		
		case "Regata_SiegeSkiper_1":
			dialog.text = "Hai ragione. In che modo posso esserti d’aiuto?";
			link.l1 = "So che sei un navigatore esperto e conosci bene i mari tra Barbados e Curaçao. So anche che vuoi arrivare a Port Royal. Io partecipo alla regata e manca solo una tappa – Port Royal. Vorrei chiederti di unirti al mio equipaggio come nocchiero per quest’ultima traversata.";
			link.l1.go = "Regata_SiegeSkiper_2";
		break;
		
		case "Regata_SiegeSkiper_2":
			dialog.text = "Interessante... E perché mai pensi che dovrei unirmi alla tua ciurma?";
			link.l1 = "Ebbene, perché ho sentito parlare di te da "+pchar.questTemp.Regata.Name+" con tutte le garanzie che non potrai rifiutare. E per via del mio aiuto a Bridgetown in questo momento critico...";
			link.l1.go = "Regata_SiegeSkiper_3";
		break;
		
		case "Regata_SiegeSkiper_3"://а тут - как уж свезет
			if(hrand(2) != 2)
			{
				dialog.text = "Da "+pchar.questTemp.Regata.Name+"? Ora capisco, certo. Va bene, capitano, vi aiuterò a trovare la rotta più corta per Port Royal. Velete salpare subito?";
				link.l1 = "Sì.";
				link.l1.go = "Regata_SiegeSkiper_4";
			}
			else
			{
				dialog.text = ""+pchar.questTemp.Regata.Name+"  Capisco. Ma, capitano, non posso abbandonare la mia città in tempi tanto turbolenti. Devi capirmi come un soldato che ci ha prestato aiuto senza chiedere nulla in cambio.\nNon voglio che la gente sussurri alle mie spalle che il vecchio Woodrow è scappato alla vigilia dello scontro finale contro gli spagnoli. Resterò. Non serbare rancore, capitano.";
				link.l1 = "E questa è la tua ultima parola? Ma ho aiutato la tua colonia...";
				link.l1.go = "Regata_SiegeSkiper_6";
			}
		break;
		
		case "Regata_SiegeSkiper_4":
			dialog.text = "Non perdiamo altro tempo allora. Fammi solo radunare le mie cose e sarò ai tuoi ordini.";
			link.l1 = "I miei marinai ti aspetteranno al molo e ti porteranno alla 'Santa Caterina'. Ti ringrazio, Woodrow!";
			link.l1.go = "SiegeSkiper_hire";
		break;
		
		case "Regata_SiegeSkiper_6":
			dialog.text = "Capitano, la regata è un passatempo, ma l’assedio spagnolo alla mia casa è questione di vita o di morte. Non verrò con voi da nessuna parte. E ve lo ripeto, dovete capirmi — onore e dovere hanno ancora valore in questo mondo. Questa è la mia ultima parola e non ho intenzione di rimangiarmela.\nTuttavia, posso darvi un consiglio su come arrivarci in men che non si dica, seguendo la rotta più sicura: puntate a nord-ovest verso Dominica, poi mettete la prua su Martinica o Guadalupa, secondo il vento e la vostra scelta. Da lì, dritti a Port-Royal, oppure potete passare per Curaçao — che io vi sconsiglio, ma se siete in buoni rapporti coi dannati olandesi, allora fate pure.";
			link.l1 = "Ebbene, grazie... ma sono deluso. Addio, Woodrow.";
			link.l1.go = "SiegeSkiper_exit";
		break;
		
		case "SiegeSkiper_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
		break;
		
		case "SiegeSkiper_hire":
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 10.0);
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.loyality = 25;
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			//пересчитываем время пятого перехода
			for (i=1; i <=5; i++)
			{
				if (i==1) sTemp = "a";
				if (i==2) sTemp = "b";
				if (i==3) sTemp = "c";
				if (i==4) sTemp = "d";
				if (i==5) sTemp = "e";
				pchar.questTemp.Regata.AdversaryFifthTransition.Time.(sTemp) = sti(pchar.questTemp.Regata.AdversaryFifthTransition.Time.(sTemp))+18+(rand(18));//выигрыш до 1.5 суток
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp)));
			}
			SetFunctionTimerCondition("SiegeSkiperOver", 0, 0, 15, false);//чтобы не присвоил офицера
			DialogExit();
		break;
		
		case "Regata_Finish":
		iTest = FindColony("Portroyal"); 
		if (iTest != -1)
		{
			rColony = GetColonyByIndex(iTest);
			sFrom_sea = rColony.from_sea;
		}
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
		{
			//снимаем запреты
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			bool bRegLugger = sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_LUGGER || sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_CAREERLUGGER;
			if (CheckAttribute(pchar, "questTemp.Regata.Breach") || !CheckAttribute(pchar, "questTemp.Regata.Bridgetown") || GetCompanionQuantity(pchar) > 1 || !bRegLugger || pchar.Ship.Name != "Saint Catherine")
			{
				dialog.text = "Hai infranto le regole della regata proprio all’ultima tappa. Il tuo risultato è stato squalificato. Non ho altro da dirti, capitano.";
				link.l1 = "Eh... che diavolo! Beh, non c'è altro da fare allora, sei stato troppo sveglio. Addio!";
				link.l1.go = "exit";
				npchar.lifeday = 1;
				DeleteAttribute(pchar, "questTemp.Regata");
				AddQuestRecord("Regata", "45");
				CloseQuestHeader("Regata");
			}
			else
			{
				n=1;
				for (i=1; i <=5; i++)
				{
					if (i==1) sTemp = "a";
					if (i==2) sTemp = "b";
					if (i==3) sTemp = "c";
					if (i==4) sTemp = "d";
					if (i==5) sTemp = "e";
					if (pchar.questTemp.Regata.AdversaryFifthTransition.Time.(sTemp) < sti(pchar.questTemp.Regata.FifthTransitionTime)) n++;
					pchar.questTemp.Regata.Result = n;//место в регате
				}
				if (n==1)
				{
					dialog.text = "Capitano "+GetFullName(pchar)+", le mie congratulazioni! Ci hai messo "+sti(pchar.questTemp.Regata.FifthTransitionTime)+" ore per terminare la regata e hai lasciato tutti i tuoi avversari ben dietro. Questo sì che è un risultato straordinario!";
					link.l1 = "Grazie per le vostre gentili parole, signore!";
					link.l1.go = "First_result";
				}
				else
				{
					if (n==6)
					{
						dialog.text = "Capitano, ahimè, il tuo risultato è il peggiore, hai sprecato "+sti(pchar.questTemp.Regata.FifthTransitionTime)+" ore. Non rattristarti, avevi davvero dei cani di mare tosti contro di te.";
						link.l1 = "Non sono triste, signore. Sono lieto d’aver preso parte alla regata e messo alla prova le mie capacità.";
						link.l1.go = "Other_result";
						AddQuestRecord("Regata", "44");
						CloseQuestHeader("Regata");
					}
					else
					{
          				dialog.text = "Capitano, vi trovate in "+n+"º posto. Congratulazioni per il risultato ottenuto, hai dimostrato un tempo degno - "+sti(pchar.questTemp.Regata.FifthTransitionTime)+" ore. Congratulazioni nonostante la sconfitta!";
						link.l1 = "Va bene, signore. Son lieto d’aver dato prova di me stesso in questa dura tenzone.";
						link.l1.go = "Other_result";
						if (n==2) AddQuestRecord("Regata", "40");
						if (n==3) AddQuestRecord("Regata", "41");
						if (n==4) AddQuestRecord("Regata", "42");
						if (n==5) AddQuestRecord("Regata", "43");
						CloseQuestHeader("Regata");
					}
				}
			}
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex("SiegeSkiper");
			sld = &Characters[sti(Pchar.questTemp.FiringOfficerIDX)];
			CheckForReleaseOfficer(sti(Pchar.questTemp.FiringOfficerIDX));
			RemovePassenger(Pchar, sld);
			DeleteAttribute(sld, "Payment");
			DeleteAttribute(Pchar, "questTemp.FiringOfficerIDX");//удаляем из офицеров
			log_info("Woodrow Dougherty has landed");
			pchar.quest.SiegeSkiperOver.over = "yes"; //снять таймер
		}
		else
		{
			dialog.text = "Signore, permettete una domanda – dov’è la vostra nave? Non la vedo...";
			link.l1 = "Mi scusi, signore. La porterò subito al porto.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_Finish";
		}
		break;
		
		case "First_result":
			if (CheckAttribute(pchar, "questTemp.Regata.Rate")) sTemp = "Come and see me in my office. I will give you your prize for your stake.";
			else sTemp = "And if you had made a stake on your victory as I offered you to, you would have gotten an extra prize too.";
			dialog.text = "Fai visita al governatore generale domani e ti consegnerà i tuoi 250 000 pesos e doni preziosi. "+sTemp+" Non abbandonare la città, secondo le tradizioni i premi finiranno nel tesoro cittadino se il vincitore non li reclama entro una settimana.";
			link.l1 = "Capito, signore. Andrò a trovarlo domani!";
			link.l1.go = "First_result_1";
		break;
		
		case "First_result_1":
			DialogExit();
			//npchar.lifeday = 7;
			Achievment_Set("ach_09");
			npchar.dialog.currentnode = "Other_result_repeat";
			pchar.questTemp.Regata.Win = "true";
			pchar.quest.Regata_Final.win_condition.l1 = "Timer";
			pchar.quest.Regata_Final.win_condition.l1.date.hour  = 6.0;
			pchar.quest.Regata_Final.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Regata_Final.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Regata_Final.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Regata_Final.function = "RegataFinal";
			SetFunctionTimerCondition("RegataFinalOver", 0, 0, 8, false);//таймер не снимаем - через 8 дней подчистится все автоматически
			// слухи
			AddSimpleRumour("Ah, you are the legendary captain, the winner of the regatta! It's such a pleasure to see you in flesh!", ENGLAND, 60, 10);
			AddSimpleRumour("Ha, look at this, a master of wind and waves, the winner of the regatta! You have my respect...", ENGLAND, 60, 10);
			AddSimpleRumour("Oh, a great sailor, a king of the wind and the sea, the winner of regatta has visited our city! We are glad to see you, captain!", ENGLAND, 60, 10);
			AddSimpleRumour("Oh, yes I was lucky to chat with a living legend, the captain who is capable of crossing the archipelago in three days even facing a headwind! My respects, captain!", ENGLAND, 60, 10);
			AddSimpleRumour("Ah, so you are the legendary captain, the winner of the regatta! Pleasure to see you!", FRANCE, 60, 10);
			AddSimpleRumour("Ha, aren't you the master of wind and waves, the winner of the regatta! You have my respects...", FRANCE, 60, 10);
			AddSimpleRumour("Oh, a great sailor, a king of the wind and the sea, the winner of regatta has visited our city! We are glad to see you, captain!", FRANCE, 60, 10);
			AddSimpleRumour("Oh, yes I was lucky to chat with a living legend, the captain capable of crossing the archipelago in three days even facing a headwind! My respects, captain!", FRANCE, 60, 10);
			// экспа
			AddComplexSeaExpToScill(2000, 300, 300, 0, 500, 500, 0);
			AddCharacterExpToSkill(pchar, "Leadership", 2000);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 1000);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
			ChangeCharacterComplexReputation(pchar, "authority", 10);
			ChangeCharacterComplexReputation(pchar, "fame", 15);
			ChangeOfficersLoyality("good_all", 3);
			AddQuestRecord("Regata", "39");
			CloseQuestHeader("Regata");
		break;
		
		case "Other_result":
			dialog.text = "Mi fa piacere sentire una risposta onorevole. Buona fortuna, capitano!";
			link.l1 = "Addio, signore.";
			link.l1.go = "Other_result_1";
		break;
		
		case "Other_result_1":
			DialogExit();
			npchar.dialog.currentnode = "Other_result_repeat";
			SetFunctionTimerCondition("RegataFinalOver", 0, 0, 1, false);
			// экспа
			AddComplexSeaExpToScill(500, 100, 100, 0, 100, 100, 0);
			AddCharacterExpToSkill(pchar, "Leadership", 200);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		case "Other_result_repeat":
			dialog.text = "Desiderate altro, capitano?";
			link.l1 = "No... non è nulla.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Other_result_repeat";
		break;
		
		case "Give_advantage":
			dialog.text = "Ah, eccoti qua, signore "+GetFullName(pchar)+". Lieto di vederti. Sei qui per il tuo premio? Ti aspetta già, pronto.";
			link.l1 = "Fa piacere sentire questo! E quale sarebbe la taglia del mio premio extra?";
			link.l1.go = "Give_advantage_1";
		break;
		
		case "Give_advantage_1":
			dialog.text = "Considerando tutto in gioco, la tua ricompensa finale è "+FindRussianMoneyString(makeint(pchar.questTemp.Regata.Advantage))+". Prego, prendilo. Congratulazioni!";
			link.l1 = "Grazie!";
			link.l1.go = "Give_advantage_2";
		break;
		
		case "Give_advantage_2":
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.Regata.Advantage));
			dialog.text = "Certo, la tua fama tra i cittadini di Port Royal è cresciuta. Penso che tu stesso possa notarlo... ma ahimè, la memoria del popolo è corta. Goditi la gloria finché brilla ancora così intensamente!";
			link.l1 = "Parlate di cose assai piacevoli, signore... Vediamo dunque come sia tuffarsi nella gloria. Addio! È stato un vero piacere.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Other_result_repeat";
		break;
		
		case "Regata_CitMan_1":
			if (CheckAttribute(pchar, "questTemp.Regata"))
			{
				if (CheckAttribute(pchar, "questTemp.Regata.Result"))
				{
					if (sti(pchar.questTemp.Regata.Result) == 1)
					{
						dialog.text = "Congratulazioni per la vittoria, capitano! Un risultato eccellente!";
						link.l1 = "Grazie!";
						link.l1.go = "exit";
					}
					else
					{
						dialog.text = "Non rattristarti, capitano. Vincere la regata non è cosa da poco, già solo parteciparvi è un privilegio!";
						link.l1 = "Non preoccuparti per me. Son ben soddisfatto del mio bottino.";
						link.l1.go = "exit";
					}
				}
				else
				{
					dialog.text = "Felice di vederti, capitano! Dovresti presentarti parlando con sir Stevenson.";
					link.l1 = "Capisco. Sto andando da lui!";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Ah, capitano, come hai potuto fallire proprio all’ultimo, maledizione!";
				link.l1 = "Sì, che sciocchezza la mia...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Regata_CitMan_1";
		break;
		
		case "Regata_CitWom_1":
			if (CheckAttribute(pchar, "questTemp.Regata"))
			{
				if (CheckAttribute(pchar, "questTemp.Regata.Result"))
				{
					if (sti(pchar.questTemp.Regata.Result) == 1)
					{
						dialog.text = "Congratulazioni per la vittoria, capitano! Un risultato eccellente!";
						link.l1 = "Grazie, compare!";
						link.l1.go = "exit";
					}
					else
					{
						dialog.text = "Non rattristarti, capitano. Vincere la regata non è cosa da poco, già solo parteciparvi è un onore!";
						link.l1 = "Non preoccuparti per me. Sono soddisfatto del mio risultato.";
						link.l1.go = "exit";
					}
				}
				else
				{
					dialog.text = "Felice di vederti, capitano! Dovresti farti registrare parlando con sir Stevenson.";
					link.l1 = "Capisco. Mi metto subito in viaggio!";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Ah, capitano, come mai hai fatto fiasco proprio alla fine!";
				link.l1 = "Sì, che sciocchezza da parte mia...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Regata_CitWom_1";
		break;
		
		case "Regata_CitHorse_1":
			if (CheckAttribute(pchar, "questTemp.Regata"))
			{
				if (CheckAttribute(pchar, "questTemp.Regata.Result"))
				{
					if (sti(pchar.questTemp.Regata.Result) == 1)
					{
						dialog.text = "Congratulazioni per la tua vittoria, capitano! Un risultato eccellente!";
						link.l1 = "Grazie a te!";
						link.l1.go = "exit";
					}
					else
					{
						dialog.text = "Non rattristarti, capitano. Vincere alla regata non è cosa da poco, già solo metterci piede è un onore!";
						link.l1 = "Non preoccuparti per me. Son ben contento del mio bottino.";
						link.l1.go = "exit";
					}
				}
				else
				{
					dialog.text = "Felice di vederti, capitano! Dovresti farti registrare parlando con sir Stevenson.";
					link.l1 = "Capisco. Sono in rotta!";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Ah, capitano, come mai sei andato a fondo proprio all’ultimo, dannazione!";
				link.l1 = "Sì, che sciocco sono stato...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Regata_CitHorse_1";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

void CreateRegataAdversaries()
{
	string sTemp;
	for (int i=0; i<=4; i++)
	{
	if (i==0) sTemp = "a";
	if (i==1) sTemp = "b";
	if (i==2) sTemp = "c";
	if (i==3) sTemp = "d";
	if (i==4) sTemp = "e";
	pchar.questTemp.Regata.AdversaryName.(sTemp) = GenerateRandomName_Generator(i, "man");
	pchar.questTemp.Regata.AdversaryShipName.(sTemp) = GenerateRandomNameToShip(ENGLAND);
	pchar.questTemp.Regata.AdversarySpeed.(sTemp) = 0.4+frand(0.9);
	log_testinfo(FindRussianDaysString(stf(pchar.questTemp.Regata.AdversarySpeed.(sTemp))));
	}
}

// НПС офиса ГВИК
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Vuoi qualcosa?";
			link.l1 = "No.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// офицер
		case "HWIC_officer":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "Allarme! Il nemico è qui! Alle armi!";
				link.l1 = "Maledizione!";
				link.l1.go = "fight";
				break;
			}
			if (ChangeCharacterHunterScore(Pchar, "holhunter", 0) > 12)
			{
				dialog.text = "Ehi tu, fermo! La tua faccia non mi è nuova...ah già! Sei ricercato per i tuoi misfatti! Ragazzi, acchiappatelo!";
				link.l1 = "Maledizione!";
				link.l1.go = "fight";
				break;
			}
			chrDisableReloadToLocation = true;
			if (CheckAttribute(pchar, "questTemp.HWIC.CanTake") && !CheckAttribute(pchar, "questTemp.HWIC.CanTake.Holl") && !CheckAttribute(pchar, "questTemp.HWIC.Eng") && !CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				dialog.text = "Benvenuto alla Compagnia Olandese delle Indie Occidentali. Parla in fretta, il tempo è oro.";
				link.l1 = "Sono qui per affari di commercio. Licenze, strumenti di navigazione e simili...";
				link.l1.go = "HWIC_officer_3";
				link.l2 = "Desidero offrire i miei servigi alla Compagnia. In cambio dell’oro, s’intende. State ingaggiando qualcuno?";
				link.l2.go = "HWIC_officer_1";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
			{
				dialog.text = "Benvenuto alla Compagnia Olandese delle Indie Occidentali. Parla in fretta, il tempo è denaro.";
				link.l1 = "Perdonami, pare che mi sia sbagliato. Me ne vado.";
				link.l1.go = "HWIC_officer_exit";
				link.l2 = "Sono qui per affari di commercio. Licenze, strumenti di navigazione e via discorrendo...";
				link.l2.go = "HWIC_officer_3";
				break;
			}
			dialog.text = "Parla svelto, il tempo è denaro.";
			link.l1 = "Sono qui per affari di commercio. Licenze, strumenti di navigazione e simili...";
			link.l1.go = "HWIC_officer_3";
			link.l2 = "Desidero mettere le mie capacità al servizio della Compagnia. In cambio d’oro, s’intende. State cercando gente?";
			link.l2.go = "HWIC_officer_2";
		break;
		
		case "HWIC_officer_1":
			dialog.text = "Allora sali al piano di sopra, nell’ufficio del signor Rodenburg.";
			link.l1 = "Grazie, sono già in rotta.";
			link.l1.go = "HWIC_officer_exit";
			// belamour legendary edition переехали по другому адресу
			LocatorReloadEnterDisable("GVIK", "reload2", false);//кабинет откроем
		break;
		
		case "HWIC_officer_2":
			dialog.text = "La Compagnia al momento non assume nessuno.";
			link.l1 = "Che peccato. Scusate il disturbo.";
			link.l1.go = "HWIC_officer_exit";
		break;
		
		case "HWIC_officer_3":
			dialog.text = "Parla con Mynheer Gerritz. Il suo tavolo è alla tua sinistra appena entri. Fa affari con capitani sotto contratto.";
			link.l1 = "Grazie, ufficiale...";
			link.l1.go = "HWIC_officer_exit";
		break;
		
		case "HWIC_officer_exit":
			DialogExit();
			// belamour legendary edition переехали
			LAi_ActorGoToLocation(npchar, "soldiers", "soldier3", "GVIK", "soldiers", "soldier3", "", 5);
			DoQuestCheckDelay("ReturnTalkerToOfficer", 5.0); // 140313
			NextDiag.TempNode = "HWIC_officer";
		break;
		
		// солдаты
		case "HWIC_soldier":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "Allarme! Il nemico è qui! Alle armi!";
				link.l1 = "Maledizione!";
				link.l1.go = "fight";
				break;
			}
			if (ChangeCharacterHunterScore(Pchar, "holhunter", 0) > 12)
			{
				dialog.text = "Ahah! Credo d’aver capito chi sei... Ma certo! Sei ricercato per i tuoi misfatti! Ragazzi, prendetelo!";
				link.l1 = "Maledizione!";
				link.l1.go = "fight";
				break;
			}
			dialog.text = "Parla con i nostri ufficiali o con il signor Gerritz. Non ho nulla da dirti. Sono di guardia.";
			link.l1 = "La tua disciplina è degna d’ammirazione.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "HWIC_soldier";
		break;
		
		// клерки
		case "HWIC_clerk":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "Allarme! Il nemico è qui! Soldati!";
				link.l1 = "Maledizione!";
				link.l1.go = "fight";
				break;
			}
			dialog.text = "Parla con Mynheer Gerritz.";
			link.l1 = "D'accordo, ho capito.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "HWIC_clerk";
		break;
		
		// главный клерк - минхер Герритц
		case "HWIC_headclerk":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "Allarme! Il nemico è qui! Soldati, prendetelo!";
				link.l1 = "Maledizione!";
				link.l1.go = "fight";
				break;
			}
			if (ChangeCharacterHunterScore(Pchar, "holhunter", 0) > 12)
			{
				dialog.text = "Hm. Credo che ci sia qualcosa che non va in te... Ma certo! Sei ricercato per i tuoi innumerevoli crimini contro l’Olanda! Soldati, prendetelo!";
				link.l1 = "Maledizione!";
				link.l1.go = "fight";
				break;
			}
			dialog.text = "Desidera qualcosa, mynheer?";
			if (!CheckCharacterItem(pchar, "HolTradeLicence"))
			{
				link.l1 = "Desidero acquistare una licenza commerciale della Compagnia Olandese delle Indie Occidentali.";
				link.l1.go = "licence";	
			}
			if (!CheckAttribute(npchar, "quest.trade"))
			{
				link.l2 = "Ho sentito dire che qui si possono acquistare strumenti di navigazione e altre cose utili. È vero?";
				link.l2.go = "trade";	
			}
			else
			{
				link.l2 = "Cosa vendi oggi?";
				link.l2.go = "trade_1";	
			}
			if (CheckCharacterItem(pchar, "Cromvel_depeshe"))
			{
				link.l3 = "Ho tra le mani un documento interessante per voi, signor mio. Date un’occhiata alle prime righe: riguarda la sopravvivenza della Repubblica e i profitti della Compagnia. Troverete anche le coordinate di un certo incontro. Se vi interessa, sono disposto a cederle… naturalmente a un prezzo generoso.";
				link.l3.go = "depeshe";	
			}
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche.Garpiya") && pchar.questTemp.Caleuche.Garpiya == "gwik")
			{
				link.l4 = "Un capitano di nome Reginald Jackson deve lavorare per voi. Naviga su uno sciabecco chiamato 'Arpia'. Potreste dirmi dove posso trovarlo? Ho affari urgenti con lui.";
				link.l4.go = "caleuche";	
			}
			// Sinistra Путеводная звезда
			if (CheckAttribute(pchar, "questTemp.PZ_RazgovorGerrits"))
			{
				link.l4 = "Devo vedere subito il signor Rodenburg. È di massima importanza. Dov’è lui?";
				link.l4.go = "PZ_RazgovorGerrits_1";
			}
			link.l9 = "No, non è nulla.";
			link.l9.go = "exit";			
			NextDiag.TempNode = "HWIC_headclerk";
		break;
		
		// торговые лицензии
		case "licence":
			if (!CheckAttribute(npchar, "quest.licence"))
			{
				dialog.text = "Ebbene, sei libero di comprarla. Ma devo avvertirti: la Compagnia tiene molto alla sua fama d’assoluta neutralità, dunque è severamente vietato attaccare navi mercantili di qualsiasi nazione finché possiedi questa licenza.\nSe scopriremo che hai trasgredito – la licenza ti sarà immediatamente revocata. E bada: se per qualsivoglia ragione entri in conflitto con gli Olandesi o con la Compagnia stessa, la licenza svanirà all’istante. Ci siamo capiti?";
				link.l1 = "Chiaro come il sole. Me lo segno in testa.";
				link.l1.go = "licence_0";
				npchar.quest.licence = true;
			}
			else
			{
				dialog.text = "Se vuoi puoi comprare una licenza. Allora, per quanti giorni la vuoi?";
				link.l1.edit = 6;
				link.l1 = "";	
				link.l1.go = "licence_1";
			}
		break;
		
		case "licence_0":
			dialog.text = "La patente ti concede libero passaggio verso qualsiasi porto di qualsiasi nazione, mostra le tue intenzioni pacifiche e spiega il motivo della tua visita — il commercio. Ma non ti salverà se hai grane con la legge: in quel caso te la porteranno via senza tanti complimenti. Ricorda,\nNon scordarti di issare una bandiera amica prima di far rotta su un porto. Le pattuglie e i cannoni delle fortezze sparano prima e fanno domande poi.\nLa durata minima della patente è di venti giorni, la massima è di sei mesi, ovvero 180 giorni.\nAh, per poco dimenticavo... Secondo le nostre illustri consuetudini, ogni affare che riguarda le patenti si paga in dobloni.  Ora discutiamo i dettagli: per quanto tempo vuoi che la patente resti valida?";
			link.l1.edit = 6;
			link.l1 = "";	
			link.l1.go = "licence_1";
			link.l2 = "Mi dispiace, ma devo rifletterci ancora un po'. Ci vediamo più tardi.";	
			link.l2.go = "exit";
		break;
		
		case "licence_1":
			float fQty = stf(dialogEditStrings[6]);
			npchar.quest.lcc_summ = makeint(sqrt(fQty)*10)*7;
			if (fQty < 1)
			{
				dialog.text = "Mynheer, per cortesia, parlate più forte. Non ho ben inteso le vostre parole. Dunque, per quanto tempo?";
				link.l1 = "Lascia che ci pensi...";
				link.l1.go = "licence_r";
				break;
			}
			if (fQty > 0 && fQty < 20)
			{
				dialog.text = "Il termine minimo per la licenza è di venti giorni. Allora? Venti giorni o di più?";
				link.l1 = "Lascia che ci pensi...";
				link.l1.go = "licence_r";
				break;
			}
			if (fQty > 180)
			{
				dialog.text = "Il termine massimo per la licenza è di mezzo anno. Centottanta giorni o anche meno?";
				link.l1 = "Lascia che ci pensi...";
				link.l1.go = "licence_r";
				break;
			}
			dialog.text = "Per "+FindRussianDaysString(sti(fQty))+" ? Molto bene. Ti costerà "+FindRussianDublonString(sti(npchar.quest.lcc_summ))+"   Sono accettabili queste condizioni?";
			if (PCharDublonsTotal() >= sti(npchar.quest.lcc_summ))
			{
				link.l1 = "Sì, sono io.";
				link.l1.go = "licence_2";
			}
			link.l2 = "Purtroppo non ho con me una somma simile al momento. Tornerò più tardi per la licenza.";
			link.l2.go = "exit";
		break;
		
		case "licence_r":
			dialog.text = "";
			link.l1.edit = 6;
			link.l1 = "";	
			link.l1.go = "licence_1";
			link.l2 = "Mi dispiace, ma ho ancora bisogno di rifletterci su. Ci rivediamo più tardi.";	
			link.l2.go = "exit";
		break;
		
		case "licence_2":
			int iQty = sti(dialogEditStrings[6]);
			RemoveDublonsFromPCharTotal(sti(npchar.quest.lcc_summ));
			GiveNationLicence(HOLLAND, iQty);
			// belamour legendary edition на пару с Акулой
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet") && pchar.questTemp.SharkGoldFleet == "start")
			{
				if(iQty < 180) 
				{
					Log_info("Quest: 'Together with the Shark' - your license is less than 180 days");
				}
				else 
				{
					pchar.questTemp.SharkGoldFleet.LicenceOk = true;
					AddQuestRecord("SharkGoldFleet", "2");
				}
				pchar.questTemp.SharkGoldFleet = "afterGvik";
			}
			dialog.text = "Aspetta un momento... Lascia che ci metta un segno e il timbro qui... sigillato e fatto. Prendi il tuo documento.";
			link.l1 = "Grazie! Addio, signor mio.";
			link.l1.go = "exit";
		break;
		
		case "trade":
			dialog.text = "Proprio così. Qui puoi acquistare strumenti di navigazione come bussole, astrolabi, cronometri e clessidre. Ma, a parte le clessidre forse, non sempre abbiamo tutto disponibile: i nostri appaltatori e capitani fanno sparire il resto in un lampo. Dunque, se non trovi ciò che cerchi, torna tra una settimana quando rinnoviamo la merce. \nVendiamo anche mappe e cannocchiali. Vuoi dare un’occhiata a cosa abbiamo?";
			link.l1 = "Sì, per favore.";
			link.l1.go = "trade_1";
			npchar.quest.trade = "true";
		break;
		
		case "trade_1":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 7)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;
		
		// депеша Кромвеля
		case "depeshe":
			dialog.text = "Hm, fammi vedere...(legge) Eh già... l’appetito di Cromwell cresce. Maledetti! Non bastava ai quei cani puritani spargere sangue nella loro lurida isola che ora portano la loro feccia anche qui!? Dove hai trovato questa missiva?";
			link.l1 = "L'ho preso a un corriere inglese. Dunque, volete comprarlo?";
			link.l1.go = "depeshe_1";
		break;
		
		case "depeshe_1":
			dialog.text = "Sì. Sono certo che Peter Stuyvesant sarà ben lieto di leggerla, e prenderà provvedimenti efficaci per porre fine a questa storia... Posso pagarti in dobloni d’oro, oppure farti una patente valida per mezzo anno. Che preferisci?";
			link.l1 = "Scelgo l’oro.";
			link.l1.go = "depeshe_dublon";
			link.l2 = "Voglio la licenza.";
			link.l2.go = "depeshe_licence";
		break;
		
		case "depeshe_dublon":
			TakeNItems(pchar, "gold_dublon", 700);
			Log_Info("You have received 700 doubloons");
			dialog.text = "Molto bene. Ecco a te le tue settecento dobloni. Una ricompensa degna per un lavoro ben fatto.";
			link.l1 = "Ecco la tua dispaccia.";
			link.l1.go = "depeshe_exit";
		break;
		
		case "depeshe_licence":
			if (CheckCharacterItem(pchar, "HolTradeLicence")) TakeNationLicence(HOLLAND);
			GiveNationLicence(HOLLAND, 180);
			dialog.text = "Bene. Ecco la tua patente valida per sei mesi.";
			link.l1 = "Grazie! Ecco qui il tuo dispaccio.";
			link.l1.go = "depeshe_exit";
		break;
		
		case "depeshe_exit":
			RemoveItems(pchar, "Cromvel_depeshe", 1);
			pchar.quest.Terrapin_CromvelScuadron.over = "yes"; //снять прерывание
			ChangeCharacterNationReputation(pchar, HOLLAND, 15);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			dialog.text = "Grazie. È bene che tu abbia dimostrato il tuo senso del dovere e la tua lealtà verso la Repubblica. Riferirò a Matthias Beck e Peter Stuyvesant della tua buona azione.";
			link.l1 = "Bene a sapersi. Addio!";
			link.l1.go = "exit";
		break;
		
		// Sinistra Путеводная звезда
		case "PZ_RazgovorGerrits_1":
			dialog.text = "Temo che sia già partito per il Vecchio Mondo insieme alla famiglia Schneur. Credo che ve ne abbia accennato.";
			link.l1 = "Proprio così, lo fece. Ma speravo che fosse stato trattenuto da qualche faccenda recente nell’Arcipelago. Dimmi, Gerritz, qualcuno della Compagnia mantiene i contatti con il signor Rodenburg? Magari attraverso navi di corriere?";
			link.l1.go = "PZ_RazgovorGerrits_2";
		break;
		
		case "PZ_RazgovorGerrits_2":
			dialog.text = "Affatto - prima di partire ci pregò di non disturbarlo mai più, disse che iniziava una vita nuova e migliore.";
			link.l1 = "Speriamo che anche le nostre vite migliorino. Addio.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.PZ_RazgovorGerrits");
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "Lascia che dia un'occhiata ai registri del manifesto... Ikema, Immerzeel, Jacobs... Jackson, eccolo. Hmm, il Capitano Reginald Jackson attualmente si occupa di spedizioni regolari tra Port Royal e Philipsburg. Cercalo su quella rotta. Ora, capitano, ti avverto subito – se stai architettando qualche malefatta, ti conviene lasciar perdere, perché quel Capitano Jackson è sotto la nostra protezione. Ci siamo capiti, signor mio?";
			link.l1 = "Ho solo degli affari con lui. Una semplice faccenda di scambi. Non ho intenzione di fargli alcun male.";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "Eccellente. Il Kapitein Jackson non si ferma mai troppo a lungo né a Port Royal né a Philipsburg. Il tempo è denaro, dopotutto. Appena la sua nave viene scaricata e caricata di nuovo, salpa subito. Avrai più fortuna a incrociarlo lungo le rotte di mare.";
			link.l1 = "Grazie a voi!";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			DialogExit();
			pchar.questTemp.Caleuche.Garpiya = "capitan";
			pchar.questTemp.Garpiya = "to_portroyal";
			AddQuestRecord("Caleuche", "19");
			DoQuestFunctionDelay("Caleuche_CreateGarpiyaInWorld", 1.0);
		break;
		
		// новый босс ГВИК
		case "HWIC_Boss":
			if(CheckAttribute(pchar,"questTemp.HWIC.Detector") && (pchar.questTemp.HWIC.Detector == "holl_win"))
			{
				if (!CheckAttribute(npchar, "quest.silk_info"))
				{
					if (sti(pchar.reputation.nobility) > 60)
					{
						dialog.text = "Aha, Kapitein "+GetFullName(pchar)+"Ah! È bene che tu sia venuto qui. Ho una proposta d’affari da farti.";
						link.l1 = "Interessante! Vi ascolto, mynheer.";
						link.l1.go = "silk_info";
						break;
					}
					else notification("Reputation Too Low! ("+XI_ConvertString(GetReputationName(61))+")", "None");
				}
			}
			dialog.text = "Buongiorno, Kapitein "+GetFullName(pchar)+"! Come posso esserti utile?";
			if(CheckAttribute(pchar,"questTemp.HWIC.Detector") && (pchar.questTemp.HWIC.Detector == "holl_win"))
			{
				if(CheckAttribute(npchar, "quest.silk")) // торговля шелком
				{
					if (GetDataDay() == 1 || GetDataDay() == 15)
					{
						link.l1 = "A proposito di quella seta sulla nave...";
						link.l1.go = "trade_silk";
					}
				}
			}
			link.l2 = "Buon dì. No, non mi serve nulla, volevo solo salutare.";
			link.l2.go = "exit";			
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "silk_info":
			dialog.text = "Ho recentemente allacciato rapporti commerciali con un mercante di Lione per rifornire i Caraibi di seta navale. Ne hai sentito parlare? Le vele più pregiate al mondo si fabbricano con questa seta, perciò dev’esserci un certo interesse da parte tua.";
			link.l1 = "Diavolo, queste sì che sono parole che mi fanno fremere il cuore. Quali sono le tue condizioni?";
			link.l1.go = "silk_info_1";
		break;
		
		case "silk_info_1":
			dialog.text = "Piccoli ma regolari carichi. Posso metterti da parte trenta rotoli ogni due settimane. Il prezzo di un rotolo è venti dobloni. Facciamo così: ti riservo trenta rotoli ogni primo e quindicesimo giorno del mese. Se non vieni a prenderli allora, li vendo a un altro cliente.";
			link.l1 = "Nessun obbligo, dunque?";
			link.l1.go = "silk_info_2";
		break;
		
		case "silk_info_2":
			dialog.text = "Precisamente, kapitein. Compra la seta se ti va. Paghi tutto il lotto – seicento dobloni. Spero che diventerai un cliente abituale.";
			link.l1 = "Grazie per la proposta, signor mio. Affare fatto.";
			link.l1.go = "exit";
			NextDiag.TempNode = "HWIC_Boss";
			npchar.quest.silk_info = "true";
			npchar.quest.silk = "true";
			AddQuestRecordInfo("Unique_Goods", "3");
		break;
		
		// торговля шелком
		case "trade_silk":
			if (CheckAttribute(pchar, "questTemp.UpgradeSilk"))
			{
				dialog.text = "Certo, kapitein. La tua seta ti aspetta. Sei pronto a pagarla?";
				if (PCharDublonsTotal() >= 2550)
				{
					link.l1 = "Certo! Ecco qua, prendi 2550 dobloni.";
					link.l1.go = "trade_silk_1";
				}
				else
				{
					link.l1 = "Maledizione, ho lasciato il denaro sulla mia nave. Torno subito, un attimo e lo porto!";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Certo, kapitein. La tua seta ti aspetta. Sei pronto a pagare per questa merce?";
				if (PCharDublonsTotal() >= 600)
				{
					link.l1 = "Certo! Tieni, prendi seicento dobloni.";
					link.l1.go = "trade_silk_1";
				}
				else
				{
					link.l1 = "Maledizione a me, ho lasciato i soldi sulla mia nave. Li porto in un lampo!";
					link.l1.go = "exit";
				}
			}
			if(sti(pchar.questTemp.GVIKSilk) >= 1 && !CheckAttribute(pchar, "questTemp.GVIKSilkBlock")) // увеличить объём поставок шёлка
			{
				link.l4 = "Mijnheer "+npchar.name+", Vorrei discutere la possibilità di aumentare le forniture di seta.";
				link.l4.go = "UpgradeSilk";
			}
			if(sti(pchar.questTemp.GVIKSilk) >= 1 && CheckAttribute(pchar, "questTemp.GVIKSilkPotom") && PCharDublonsTotal() >= 3000) // увеличить объём поставок шёлка, если в первый раз не принесли
			{
				link.l4 = "Ho portato i tuoi dobloni, Mijnheer "+npchar.name+". Ti prego, accettali.";
				link.l4.go = "UpgradeSilk_Agreed";
			}
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "trade_silk_1":
			RemoveDublonsFromPCharTotal(600);
			Log_Info("You have given 600 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "È stato un piacere fare affari con voi, kapitein. La vostra seta sarà portata alla nave con la scialuppa.";
			link.l1 = "Grazie!";
			link.l1.go = "trade_silk_2";
		break;
		
		case "trade_silk_2":
			dialog.text = "Spero di rivederti presto. Torna a trovarmi.";
			link.l1 = "Certo. A presto!";
			link.l1.go = "exit";
			AddCharacterGoods(pchar, GOOD_SHIPSILK, 30);
			DeleteAttribute(npchar, "quest.silk");
			SetFunctionTimerCondition("Silk_TraderAttrReturn", 0, 0, 1, false); // таймер
			AddCharacterExpToSkill(pchar, "Commerce", 150);
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "UpgradeSilk": //
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 80)
			{
				dialog.text = "Apprezzo il tuo spirito d’affari e sono disposto a prendere in considerazione la tua richiesta. Forse potremmo aumentare le quantità, diciamo, di cinque volte. Tuttavia, mettere insieme simili forniture richiederà risorse notevoli. Dovremo ampliare i magazzini, rafforzare la sicurezza e assicurare rotte di consegna affidabili. Poiché ne trarrai vantaggio anche tu, propongo di dividere queste spese tra noi.";
				link.l1 = "Tutto ciò mi sembra sensato. Quale somma riterresti necessaria per coprire queste spese?";
				link.l1.go = "UpgradeSilk_1";
				notification("Skill Check Passed", SKILL_COMMERCE);
			}
			else
			{
				dialog.text = "Capisco il tuo interesse ad aumentare le forniture, tuttavia al momento mi è difficile acconsentire a simili cambiamenti. Non dubito della tua voglia di crescere, ma trattative di questo calibro richiedono ben altra esperienza nel commercio e sicurezza nelle proprie decisioni. Ti consiglio di affinare le tue doti di negoziazione e poi tornare da me con una proposta più concreta. Quando sarai pronto, sarò lieto di rafforzare la nostra collaborazione.";
				link.l1 = "Hmm... Va bene. Tornerò a questa conversazione più tardi.";
				link.l1.go = "exit";
				notification("Skill Check Failed (80)", SKILL_COMMERCE);
			}
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "UpgradeSilk_1":
			dialog.text = "Considerando tutte le sfumature, la tua parte delle spese sarà di tremila dobloni d’oro. Con questa somma potremo mettere in moto tutto il necessario senza perdere tempo.";
			link.l1 = "Monsieur "+npchar.name+", tremila dobloni? È uno scherzo? Sono venuto da voi con una proposta onesta, e pretendete che io paghi una somma così esorbitante solo per organizzare dei rifornimenti?";
			link.l1.go = "UpgradeSilk_2";
		break;
		
		case "UpgradeSilk_2":
			dialog.text = "Ti chiedo di capirmi bene. Non ho intenzione di imbrogliarti. Questa somma servirà a mantenere il giusto ordine nell'organizzazione dei rifornimenti. Non si tratta solo di ampliare i magazzini o rafforzare la sorveglianza, ma anche di garantire che la merce arrivi puntuale e senza danni, nonostante tutta l’incertezza di questo mestiere. Queste spese sono la regola per simili volumi. Alla fine, il tuo denaro tornerà indietro con gli interessi, e riceverai quanto ti spetta, in tempo e come si deve.";
			link.l1 = "Le vostre spiegazioni mi rassicurano, mijnheer. Tuttavia, la somma resta troppo elevata. Sono disposto ad accettare le vostre condizioni, purché riduciate il prezzo ad almeno duemilacinquecento dobloni. Son certo che basterà per provvedere ai rifornimenti e garantire la sicurezza.";
			link.l1.go = "UpgradeSilk_3";
		break;
		
		case "UpgradeSilk_3":
			dialog.text = "Capisco, la somma è grande, ma come ho già detto, è indispensabile per portare a termine l’impresa come si deve. Non posso ridurla, altrimenti andrebbe tutto a monte. Tuttavia, affinché non vi sentiate gabbato, sono disposto a concedervi uno sconto del quindici per cento su tutte le future forniture. Spero che ciò vi aiuti a recuperare le spese.";
			if (PCharDublonsTotal() >= 3000)
			{
				link.l1 = "Hmm, uno sconto del quindici percento è pur sempre un passo avanti. Va bene. Accetto la tua offerta, anche se il prezzo mi pare un’esagerazione. Spero che la nostra collaborazione sia all’altezza delle mie aspettative. Ecco il tuo denaro.";
				link.l1.go = "UpgradeSilk_Agreed";
			}
			link.l2 = "Signor "+npchar.name+", la tua offerta non mi lascia scelta. Sia pure tremila dobloni, anche se è una cifra non da poco. Tuttavia, non posso pagare tutto subito. Tornerò non appena avrò i soldi.";
			link.l2.go = "UpgradeSilk_5";
			link.l3 = "Uno sconto del quindici per cento? Mijnheer "+npchar.name+", questo non è affatto ciò che mi aspettavo. Questa cifra non è solo una spesa, è una rapina bella e buona! Ma non ho intenzione di troncare i nostri affari. Torneremo ai vecchi accordi: 30 rotoli di seta a 20 dobloni l’uno.";
			link.l3.go = "UpgradeSilk_4";
		break;
		
		case "UpgradeSilk_Agreed":
			dialog.text = "Sono lieto che tu abbia accettato, "+pchar.name+". Ora, quanto ai dettagli: 150 rotoli di seta a 17 dobloni l’uno. In totale – 2550 dobloni per tutto il carico. Puoi ritirare la merce come sempre – il primo e il quindicesimo giorno di ogni mese. Credo che quest’affare porterà buon guadagno ad entrambe le parti.";
			link.l1 = "Eccellente! Ora sì che si ragiona in grande. Addio, minheer. Ci rivedremo presto.";
			link.l1.go = "exit";
			NextDiag.TempNode = "HWIC_Boss";
			RemoveDublonsFromPCharTotal(3000);
			AddQuestRecordInfo("Unique_Goods", "3_1");
			pchar.questTemp.UpgradeSilk = true;
			pchar.questTemp.GVIKSilkBlock = true;
			DeleteAttribute(pchar, "questTemp.GVIKSilkPotom");
		break;
		
		case "UpgradeSilk_4":
			dialog.text = "Questa è solo una questione d’affari, non un atto di pirateria, come forse ti è parso. Ma come preferisci tu. Vieni come sempre, il primo e il quindici per una partita di seta, sarò lieto di fare nuovi affari.";
			link.l1 = "Certamente, signor mio. Addio.";
			link.l1.go = "exit";
			pchar.questTemp.GVIKSilkBlock = true;
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "UpgradeSilk_5":
			dialog.text = "Sono lieto che tu abbia preso la decisione giusta. Non appena porterai il denaro, discuteremo tutti i dettagli dell’accordo e passeremo alla sua esecuzione.";
			link.l1 = "Addio, Mijnheer "+npchar.name+". Ci vediamo non appena avrò raccolto la somma necessaria.";
			link.l1.go = "exit";
			pchar.questTemp.GVIKSilkBlock = true;
			pchar.questTemp.GVIKSilkPotom = true;
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "fight":
			DialogExit();
			sld = characterFromId("HWIC_officer");
			LAi_SetGuardianTypeNoGroup(sld);
			LAi_group_Attack(sld, Pchar);
			for (i=1; i<=6; i++)
			{	
				sld = characterFromId("HWIC_sold_"+i);
				LAi_group_Attack(sld, Pchar);
			}
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

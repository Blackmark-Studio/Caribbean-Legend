// BOAL новый диалог офицера и компаньона 21/06/06
void ProcessDialogEvent()
{
	ref NPChar, d;
	aref Link, Diag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(Diag, NPChar.Dialog);
	
	ref    	sld, rItm, rItem;
	string 	attr, attrLoc, sGun, sBullet, attrL, sAttr;
	int    	iTemp, iTax, iFortValue, i;
	aref 	rType;
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	if (findsubstr(sAttr, "SetMusketBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetMusketBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetMusketBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
        case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = RandPhraseSimple("Ehi, capitano, mezza guarnigione ti sta cercando in questo momento. Certamente non è il miglior momento per essere assunti nel tuo equipaggio!","E lottare per raggiungere la nave? No, capo, un'altra volta...");
				link.l1 = RandPhraseSimple("Come desideri...","In realtà, non avevo intenzione di assumerti."); 
				link.l1.go = "exit";
				break;
			}
			Diag.TempNode = "OnceAgain";
			dialog.text = "Hai bisogno di un ufficiale, capitano?";
			if (FindFreeRandomOfficer() > 0)
			{
    			Link.l1 = "Un ufficiale? E in cosa sei bravo?";
    			Link.l1.go = "Node_2";
			}
			Link.l2 = "No, ho un set completo.";
			Link.l2.go = "Exit";			
		break;
		
		case "CitizenNotBlade":
			dialog.text = "Capitano, cosa stai facendo? Metti via la tua arma, prima di causare un sacco di guai!";
			link.l1 = LinkRandPhrase("Bene.","Bene.","Non preoccuparti, lo sto mettendo via...");
			link.l1.go = "exit";
		break;
		
		case "hired":
			Diag.TempNode = "Hired";
			// только наняли -->
			if (IsCompanion(NPChar))
			{
				Dialog.text = "Oggi, finalmente salpiamo!";
				link.l2 = "Sì... Sono contento.";
				link.l2.go = "Exit";
				break;
			}
			if (Npchar.location.group == "sit" && !isShipInside(pchar.location))
			{
				dialog.text = "Terminerò solo il mio drink, capitano, e poi andrò alla nave. Non preoccuparti - sarò lì in tempo.";
				Link.l1 = "Bene. Se arrivi in ritardo, ti farò strofinare il ponte!";
				Link.l1.go = "Exit";
				break;
			}
			// только наняли <--
   			dialog.text = "Cosa desidera, capitano?";
			// диалог компаньона на корабле.
			if (CheckAttribute(NPChar, "IsCompanionClone"))
			{
				Link.l2 = "Ho bisogno di darti diversi ordini.";
				Link.l2.go = "Companion_Tasks";
				break;
			}
			
			// на Тайясаль
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l66 = ""+npchar.name+", Sto andando alla vecchia città indiana di Tayasal. Questo sarà un viaggio pericoloso e insolito - attraverso un idolo di teletrasporto. Mi accompagnerai?";
				if(npchar.id == "Folke")
				{
					Link.l66 = ""+npchar.name+", Ho una richiesta seria per te - un affare reale, suicida ma dannatamente redditizio. Ho bisogno di un uomo leale per una missione in un'antica città indiana. Sei con me?";
				}
				if(npchar.id == "Duran")
				{
					Link.l66 = "Claude, una volta ti lamentasti che i mercenari sono sottopagati.";
				}
				Link.l66.go = "tieyasal";
			}
			
			if (isOfficer(Npchar)) // проверка для кампуса, где слотовые офы
			{
				Link.l2 = "Ora ascolta il mio ordine!";
				Link.l2.go = "stay_follow";
			}

           		// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l8 = "Dammi un rapporto completo della nave, "+GetStrSmallRegister(XI_ConvertString("treasurer"))+".";
			    Link.l8.go = "QMASTER_1";
			        
			    // Warship. Автозакупка товара
			    if(!CheckAttribute(PChar, "TransferGoods.Enable"))
			    {
				    Link.l11 = "Voglio che tu acquisti merci mentre stiamo soggiornando nella colonia.";
				    Link.l11.go = "TransferGoodsEnable";
			    }
			    else
			    {
				    Link.l11 = "Sapete, non abbiamo più bisogno di acquistare merci nelle colonie.";
				    Link.l11.go = "TransferGoodsDisable";
			    }
			}
			
			if (pchar.location != "My_Campus") // patch-5
			{
			Link.l4 = "Ufficiale, i tuoi servizi non sono più necessari.";
			Link.l4.go = "AsYouWish";
			}
			
			
			// по тек локации определим можно ли тут приказать  -->
			if(IsEntity(&loadedLocation))
			{
				if(CheckAttribute(loadedLocation, "fastreload"))
				{
					iTemp = FindColony(loadedLocation.fastreload);
					if(iTemp != -1)
					{
						sld = GetColonyByIndex(iTemp);
						if(sti(sld.HeroOwn) == true && !CheckAttribute(sld, "OfficerIdx"))
						{
							NPChar.ColonyIdx = iTemp;
							Link.l7 = "Ti nomino vice di questa città!";
							Link.l7.go = "Gover_Hire";
						}
					}
				}
			}
			
			Link.l9 = "Niente. A vostro agio!";
			Link.l9.go = "Exit";
		break;
		
		// Тайясаль
		case "tieyasal":
			if(npchar.id == "Folke")
			{
				dialog.text = "Maledizione, Cap! Pensavo che mi avresti mandato via alla prima occasione che avresti avuto, ma mi hai sorpreso, come sempre. Naturalmente sto con te, e grazie per aver dato a questo idiota la vera vita di un lupo di mare!";
				Link.l1 = "Bene fatto, "+npchar.name+"!";
				Link.l1.go = "folke_tieyasal";
				break;
			}
			if(npchar.id == "Duran")
			{
				dialog.text = "Eh? Ho davvero detto quello?";
				Link.l1 = "Hai fatto. Ti ho ascoltato attentamente allora, e sono pronto a correggere l'ingiustizia.";
				Link.l1.go = "Duran_tieyasal";
				break;
			}
			dialog.text = LinkRandPhrase("Mi dispiace, capitano, ma non è per questo che ho firmato. Non pensare che io sia un codardo, ma non sono disposto ad affrontare una morte certa. Non sono ancora così stanco di vivere. Puoi licenziarmi se vuoi.","Capitano, chiedo il vostro perdono, ma - no. Mari, abbordaggi, città nemiche - questo va perfettamente bene, ma non voglio avere a che fare con quella stregoneria indiana. Se siete contrariati dalla mia risposta, potete rescindere il nostro contratto.","Volete l'impossibile, capitano, e ve ne rendete conto. Nessuno tornerà vivo, incluso voi, quindi passo. Se considerate il mio rifiuto una violazione dei termini del contratto, potete annullarlo.");
			link.l1 = LinkRandPhrase("Non ti biasimo, ufficiale. Lo capisco perfettamente.","Un peccato, ma posso capirti. Ecco perché te l'ho detto in anticipo.","Contavo su di te... Ma posso capire la tua posizione, ufficiale.");
			link.l1.go = "tieyasal_1";
		break;
		
		case "Duran_tieyasal":
			dialog.text = "Ehi! Allora aumenterai il mio stipendio?";
			Link.l1 = "Assolutamente no! Sto andando in una antica città indiana. Il lavoro è suicida, ma ci sarà dell'oro lì...";
			Link.l1.go = "Duran_tieyasal_2";
		break;
		
		case "Duran_tieyasal_2":
			dialog.text = "Non mi interessa l'oro. Sarebbe un onore aiutarti, Capitano, come una volta mi hai aiutato tu. Quando partiamo?";
			Link.l1 = "Bene detto, Claude! Sii in piena prontezza - non ci vorrà molto ora.";
			Link.l1.go = "Duran_tieyasal_3";
		break;
		
		case "Duran_tieyasal_3":
			DialogExit();
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "folke_tieyasal":
			Achievment_Set("ach_CL_108");
			DialogExit();
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "tieyasal_1":
			DialogExit();
			npchar.quest.Tieyasal = "true";
		break;
		
		case "TransferGoodsEnable":
			if(sti(PChar.Ship.Type) == SHIP_NOTUSED)
	        {
				dialog.text = "Capitano, quali merci? Dobbiamo prima trovare una nave!";
				Link.l1 = "Sì, hai ragione.";
				Link.l1.go = "Exit";
				Diag.TempNode = "Hired";
				break;
	        }
	        	
			PChar.TransferGoods.Enable = true;
		//	PChar.TransferGoods.TreasurerID = NPChar.id;
			Dialog.text = "Sarà fatto, "+GetSexPhrase("signore","signorina")+" capitano!";
			Link.l1 = "A vostro agio.";
			Link.l1.go = "TransferGoodsEnable_2";
        break;
        	
		case "TransferGoodsEnable_2":
			Diag.CurrentNode = "Hired";
			DialogExit();
			LaunchTransferGoodsScreen(); // Интерфейс автозакупки товаров
		break;
		
		case "TransferGoodsDisable":
			DeleteAttribute(PChar, "TransferGoods.Enable");
			Dialog.text = "Sarà fatto, "+GetSexPhrase("signore","signorina")+" capitano!";
			Link.l1 = "A vostro agio.";
			Link.l1.go = "exit";
			Diag.TempNode = "Hired";
		break;
        
		case "ShowParam_exit":
			Diag.CurrentNode = "OnceAgain";
			NPChar.quest.meeting = true;
			DialogExit();
			
			PChar.SystemInfo.OnlyShowCharacter = true;
            LaunchCharacter(NPChar);
		break;
		
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();			
		break;

		case "exit_hire":
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
			if(CheckAttribute(pchar,"systeminfo.tutorial.Fighter") && Npchar.quest.officertype == "fighter")
			{
				DeleteAttribute(pchar,"systeminfo.tutorial.Fighter");
				LaunchTutorial("Fighter", 1);
			}
		break;

		case "exit_fire":
			//navy -->
			if (CheckAttribute(NPChar, "PGGAi"))
			{
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();			
				break;
			}
			//navy <--
			Diag.TempNode = "Fired";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");

			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;

			DialogExit();			
		break;
		
		// boal 29.05.04 офицер хочет свалить -->
        case "WantToGo":
			if (npchar.id == "Duran" && !CheckAttribute(pchar, "questTemp.SKD_SobytieKlodDuran"))
			{
				SetTimerCondition("SKD_DuranTavern", 0, 0, 30, false);
				pchar.questTemp.SKD_SobytieKlodDuran = true;
			}
			chrDisableReloadToLocation = false;
			Diag.TempNode = "Hired";
			dialog.text = LinkRandPhrase(LinkRandPhrase("Capitano, sai, io... Beh, ti chiederei di liberarmi. È ora per me di sistemarmi, sposarmi e fare dei bambini. Non ho ancora una casa mia, quando sarò vecchio non ci sarà nessuno a portarmi un bicchiere d'acqua.","Capitano, per favore, lasciatemi dimettermi. Per tutti questi anni ho vagato in tutto il mondo, e non ho davvero visto nulla. Voglio solo vivere una nuova vita, gettare l'ancora e vedere il mondo da una prospettiva diversa.","Capitano, il servizio navale è certamente una cosa nobile, c'è buon profitto e avventura, ma è giunto il momento per me di pensare a me stesso. Sai, gettare l'ancora in un porto tranquillo, comprare una casa, avere figli. Per favore, lasciami andare."),LinkRandPhrase("Capitano, sai, mi dispiace davvero, ma sono stufo di tutti questi doveri, guardie e disciplina. Sai, voglio solo vivere una vita libera almeno per un po', ma capisco che non mi aspetterai, quindi... Potresti congedarmi?","Capitano, sai... C'è una piccola nave che posso permettermi, quindi... Credo sia probabilmente il momento per me di iniziare il mio proprio affare. Per favore, potresti lasciarmi andare?","Capitano, mi è stata appena offerta una posizione al porto. In realtà, desidero da tempo gettare l'ancora e stabilirmi in una vita matrimoniale. Per favore, permettimi di andare. Non posso davvero perdere un'opportunità del genere."),LinkRandPhrase("Capitano, sono veramente malato di mare. I dottori continuano a dirmi che è idiosincrasia. Per l'amor di Dio, lasciami andare, o a un certo punto salterò semplicemente fuori bordo.","Capitano, penso che sia il momento per me di stabilirmi e trovare un posto più tranquillo. Sai, ho paura. Paura dei proiettili vaganti, paura di morire durante un abbordaggio. Prego il Signore di tenermi in vita, e quando chiudo gli occhi, vedo tutte le anime innocenti che ho ucciso. Mi stanno implorando di risparmiarle... Per favore, mostra un po' di compassione, e lasciami andare.","Capitano, le mie vecchie ferite mi fanno male, e la recente contusione si fa sentire ogni giorno. Presto mi licenzierai, e chi mi assumerà dopo? Per favore, lasciami andare, mi rimetterò in sesto e troverò un posto più tranquillo."));
			Link.l1 = RandPhraseSimple(LinkRandPhrase("Se ne vanno tutti alla fine. Bene, sei libero di andare.","Posso capire il tuo ragionamento. Prima o poi tutte le cose arrivano alla fine. Bene, allora vai... e non portare rancore se ti ho mai offeso.","Di nuovo questo? Hai scelto appositamente il momento più inopportuno possibile per lasciarmi, vero? Comunque. Addio."),LinkRandPhrase("Difficile credere a quello che mi dici... Bene, prepara le tue cose e vai.","Tu? Non me lo aspettavo... Dopo tutto questo tempo a combattere spalla a spalla... Beh, non ti sto fermando. Dio ti accompagni.","Sembrate seri. Bene, vi auguro fortuna, sappiate che mi mancherete."));				
			Link.l1.go = "WantToGo_free";
			if (sti(Pchar.money) >= sti(NPChar.rank)*250)
			{
				Link.l2 = LinkRandPhrase("Capisco... Quindi è così, eh? E io contavo su di te... Beh, se hai già deciso allora lasciamoci. Prendi "+sti(NPChar.rank)*250+" pesos per il tuo leale servizio. E non aver rancore se ti ho mai offeso.","Ebbene, non porto rancore e non ricordo il male. Se è questa la tua decisione, allora vai. E prendi "+sti(NPChar.rank)*250+" pesos per un nuovo inizio, sarà sicuramente utile.","Capisco... Beh, prima o poi doveva succedere. Ti darò "+sti(NPChar.rank)*250+" pesos per sistemare la tua vita. E presta attenzione anche alla tua salute, il servizio navale è pieno di difficoltà..."); 
				Link.l2.go = "Im_kind_A2_1";
			}
			Link.l3 = LinkRandPhrase("Allora dici... Non ti rendi conto che andandotene ora mi stai semplicemente pugnalando alle spalle? Non posso permetterti di andare ora, non pensarci nemmeno.","Ecco una novità! Sai, dovrebbero avvisarmi di queste cose in anticipo! Quindi dimentica la tua vita privata per un po'. Quando arriverà il momento, ti suggerirò quando ritirarti.","Non si accettano dimissioni. Ho tutti sotto controllo. Non posso lasciare andare tutti solo per un loro desiderio personale. Servite, finché considero se meritate un permesso.");	
			Link.l3.go = "WantToGo_Stay";
		break;
		
		case "Im_kind_A2_1":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*250)));
			ChangeOfficersLoyality("good_all", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			dialog.text = "Grazie, capitano! Una generosità davvero inaspettata... Sai, ho ancora alcune delle tue cose, forse vorresti riaverle?";
			Link.l1 = "Forse... Trovare una buona lama non è così facile al giorno d'oggi.";
			Link.l1.go = "Get_out_А2_chang";
			Link.l2 = "Oh, non disturbarti. Conservali come ricordo del tuo servizio.";
			Link.l2.go = "WantToGo_free";
		break;
		
		case "WantToGo_Stay":
			dialog.text = RandPhraseSimple("Ma come, capitano? Anche gli schiavi vengono infine mandati a riva. E io non sono uno schiavo, quindi posso decidere il mio destino da solo!","Capitano, vi ho servito fedelmente tutto questo tempo. Non merito il diritto di decidere il mio destino da solo?");
			Link.l1 = LinkRandPhrase("Vedo che non posso mantenerti così com'è. Va bene, che ne dici di un po' di sostegno finanziario? Non fa mai male, puoi usare quei soldi per costruirti una casa accogliente in un porto tranquillo o prenderti cura della tua salute.","Va bene, mettiamola in questo modo. Quale somma potrebbe farvi riconsiderare la vostra decisione?","Hai ragione. Ma che ne dici di un'indennità monetaria una tantum, cambierebbe la tua opinione?");
			Link.l1.go = "WantToGo_Stay_2";
			Link.l2 = PCharRepPhrase(RandPhraseSimple("Oh, no, amico mio, qui ti sbagli... Mentre sprecavi il tuo tempo nelle taverne a rincorrere le gonne dopo i bicchieri, potevi decidere per te stesso, ma una volta salito a bordo della mia nave, hai affidato il tuo destino nelle mie mani.","Mmm. Ora, questa è una dichiarazione seria. Apparentemente, hai dimenticato come ti ho trovato, in una taverna puzzolente senza un soldo in tasca. Non puoi nemmeno vedere una singola moneta d'oro, perché la trasformerai immediatamente in rum. 'Decidi il mio destino...' Pfff! Che barzelletta!"),LinkRandPhrase("Mentre sei al mio servizio, sono io a prendere le decisioni. E ora, per favore, torna ai tuoi doveri, prima di avermi irritato troppo!","Mmm. Ora, questa è una dichiarazione seria. Ma non hai ancora lavorato abbastanza per ripagare tutto il denaro che ti è stato dato in anticipo. Quindi la tua demarche può essere considerata un tentativo di estorsione, giusto?","Oh, capisco... Cosa dicono di nuovo i regolamenti della nave? Ecco, paragrafo due: 'Chiunque tenti di partire senza permesso sarà abbandonato su una spiaggia deserta con un solo sacchetto di polvere, un fiasco d'acqua, una pistola e un solo proiettile.' Ora, ti piacerebbe questo?"));	
			Link.l2.go = "WantToGo_Stay_force";
		break;
		
	case "WantToGo_Stay_2":
		dialog.text = LinkRandPhrase("Ebbene, questa è un'altra storia. "+sti(NPChar.rank)*500+" pesos sul chiodo, e resterò con te.","Bene, forse per "+sti(NPChar.rank)*500+"Suppongo che potrei restare per qualche peso.","Bene, se lo metti in questo modo, per "+sti(NPChar.rank)*500+" posso continuare il mio servizio con pesos.");
		if (sti(Pchar.money) >= sti(NPChar.rank)*500)
		{
			Link.l1 = RandPhraseSimple("Bene, d'accordo.","Va bene. Anche se potresti chiedere di meno.","Vedo che hai un appetito notevole! Ma, ti ho fatto una promessa, non è vero? E rimarrò fedele alla mia parola.");	
			Link.l1.go = "WantToGo_Stay_ForMoney";
		}
		Link.l2 = LinkRandPhrase("È troppo. Potrei assumere due ufficiali per un prezzo del genere. Forse, è più facile semplicemente lasciarti andare.","Ebbene, hai certamente un alto concetto di te stesso. Va bene, ti lascio andare. Ma vedrai da solo, una volta che sarai libero, che la tua vita non sarà così senza nuvole come ti aspettavi.","Non sto per pagare un tale denaro. Puoi andare, ma non chiedere nemmeno di tornare, non perdono il tradimento.");				
		Link.l2.go = "WantToGo_free";
	break;
	
	case "WantToGo_Stay_force":
		Npchar.loyality = makeint(Npchar.loyality) - 2;
		dialog.text = "Bene, se lo metti in questo modo, resterò. Ma sappi che così facendo sto agendo contro la mia volontà.";
		Link.l1 = LinkRandPhrase("Molto bene. Torna ai tuoi doveri, e continueremo questa conversazione più tardi.","Torna alla nave. E la prossima volta rifletti bene prima di chiedere il pensionamento.","Certo. Il dovere è dovere, e non dovresti ancora lasciarti andare alle tue fantasie.");
		Link.l1.go = "exit";
	break;
	
	case "WantToGo_Stay_ForMoney":
		Diag.TempNode = "Hired";
		NPChar.greeting = "Gr_Officer";
		if(NPChar.id == "Duran") NPChar.greeting = "Duran_officer";
		ChangeCharacterComplexReputation(pchar,"authority", 0.2);
		AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
		Npchar.loyality = makeint(Npchar.loyality) + 1;    
		Diag.CurrentNode = Diag.TempNode;
		NPChar.quest.meeting = true;
		DialogExit();
		NPChar.location = "none";
		LAi_SetOfficerType(NPChar);
	break;
	
	case "WantToGo_free":
		//navy -->
		if (CheckAttribute(NPChar, "PGGAi"))
		{	
			pchar.questTemp.FiringOfficerIDX = NPChar.index;
			AddDialogExitQuestFunction("PGG_FireOfficer");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();	
			break;
		}
		//navy <--
		Diag.TempNode = "WantToGo_free_Yet";
		Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
		AddDialogExitQuestFunction("LandEnc_OfficerFired");
		Diag.CurrentNode = Diag.TempNode;
		NPChar.quest.meeting = true;
		DialogExit();
	break;
	
	case "WantToGo_free_Yet":
		Diag.TempNode = "WantToGo_free_Yet";
		dialog.text = LinkRandPhrase("Non ci posso credere! Grazie Capitano, è un peso tolto dalla mia mente.","Grazie, capitano, per non cercare di trattenermi. Sai, ho davvero voglia di provare altre cose nella vita.","Eh, ora dovrò abituarmi alla mia nuova libertà. Solo ora ho iniziato a rendersi conto di quanto fossi stufo di tutto quel servizio di flotta.");	
		Link.l1 = RandPhraseSimple("Bene, buona fortuna a te.","Sei libero ora. Il tuo servizio è finito.");
		Link.l1.go = "exit";
	break;
	// boal 29.05.04 офицер хочет свалить <--
		
	// пассажир возмущен игроком и сваливает -->
	case "WantToRemove":
		if (npchar.id == "Duran" && !CheckAttribute(pchar, "questTemp.SKD_SobytieKlodDuran"))
		{
			SetTimerCondition("SKD_DuranTavern", 0, 0, 30, false);
			pchar.questTemp.SKD_SobytieKlodDuran = true;
		}
        chrDisableReloadToLocation = false;
		if (Npchar.alignment == "good")
		{
			dialog.text = RandPhraseSimple(LinkRandPhrase("Capitano, non voglio agire contro la mia coscienza e partecipare alla brigantaggio.","Capitano, non desidero più partecipare alle vostre rivolte. Sono un ufficiale, non un macellaio.","Capitano, il tuo modo banditesco di fare affari rende impossibile la mia permanenza nel tuo equipaggio."),LinkRandPhrase("Capitano, devo ammettere che il mio impiego con lei è stato un errore deludente. Non sono disposto a sacrificare la mia reputazione per nessuna somma di denaro.","Capitano, hai radunato sulla tua nave tutti i tagliagole più malvagi del Nuovo Mondo. È disgustoso per un uomo onesto persino guardarli. Non voglio più continuare a servire con un equipaggio del genere.","Capitano, avete assunto un equipaggio pieno di furfanti, non c'è un solo uomo decente con cui chiacchierare. Disprezzo un tale servizio."))+" Addio.";
			Link.l1 = "Cosa?! È una nave militare, non una scuola di buone maniere! Allora puoi andare all'inferno!";
			Link.l1.go = "exit_fire_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l2 = "Sapevo che presto te ne saresti andato... questo servizio non fa per te. Ma non accusarmi di nulla. Ecco "+sti(NPChar.rank)*500+" pesos, li troverai utili mentre cerchi un lavoro a tuo piacimento.";
				Link.l2.go = "Im_kind_A2";
			}
			Link.l3 = LinkRandPhrase("Oh, quindi questa è la melodia che stai cantando ora. E che ne dici della tua quota da ogni singolo colpo, ti brucia le mani? O stai pensando di ritirarti in un monastero per pregare per il perdono dei tuoi peccati? Metti una buona parola anche per noi, allora! Ha-ha-ha-ha-ha!","Mmm. Ora, questa è una dichiarazione seria. E dove stava guardando la tua innocente coscienza, mentre stavamo derubando i mercanti insieme? Come pensi di lavarla pulita? O hai intenzione di farci cantare, così che finiamo a penzolare dalla forca in buona compagnia?","Oh, bravo! A quanto pare, hai dimenticato come ti ho trovato, in una taverna puzzolente senza un soldo in tasca. Per tua informazione, come ufficiale non vali un quattrino. Non vali nulla!");
			Link.l3.go = "WantToGo_stop";
		}
		else
		{
            dialog.text = RandPhraseSimple(LinkRandPhrase("Capitano, non mi piacciono davvero i vostri nobili giochi e non intendo abbandonare le mie abitudini per il bene della vostra serenità. Addio.","Capitano, non posso più restare al tuo servizio. Ho già sprecato troppo tempo. Essere un semplice corsaro mi avrebbe già fatto guadagnare una fortuna. Me ne vado.","Capitano, i tuoi uomini mi disgustano. Non c'è un solo uomo decente, solo pantaloni eleganti, nessuno con cui fare compagnia per bere. Me ne vado."),LinkRandPhrase("Capitano, sono un ufficiale veterano e la vostra nave sembra più una chiatta da carico. Non mi piace un tale servizio. Addio.","Capitano, tutto il tuo equipaggio è pieno di pappagalli, non c'è un solo uomo con cui bere o parlare. Non sopporto questo tipo di servizio. Addio.","Capitano, pensavo di servire sotto un vero corsaro, ma tutto quello che facciamo è solo carità! Non voglio continuare a sprecare il mio tempo. Me ne vado."));
			Link.l1 = RandPhraseSimple("Capisco. Considerando il tuo atteggiamento, sarebbe dovuto accadere prima o poi. Va bene, non ti tratterrò.","La tua affermazione non è stata inaspettata. Francamente, sono insoddisfatto del tuo atteggiamento da un bel po' di tempo.")+"Buona fortuna.";
			Link.l1.go = "exit_fire_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l2 = "Sapevo che presto te ne saresti andato... questo servizio non fa per te. Ma non accusarmi di nulla. Ecco "+sti(NPChar.rank)*500+" pesos, ti saranno utili mentre cerchi un nuovo lavoro.";
				Link.l2.go = "Im_kind_A2";
			}
			Link.l3 = RandPhraseSimple("Mmm. Ora, questa è una dichiarazione seria. Ma non hai ancora restituito tutti i soldi che ti sono stati pagati in anticipo. Quindi la tua dimostrazione può essere considerata un tentativo di estorsione, giusto?","Oh, capisco... Cosa dicono i regolamenti della nave? Ecco, paragrafo due: 'Chiunque tenti di lasciare senza permesso sarà abbandonato su una spiaggia deserta con un solo sacco di polvere, una fiaschetta d'acqua, una pistola e un solo proiettile.' Ora, come ti piacerebbe questo?");
			Link.l3.go = "WantToGo_stop";
		}
		break;
		
		case "WantToGo_stop":
			if (Npchar.alignment == "good")
			{
				dialog.text = LinkRandPhrase("Non osare nemmeno insultarmi! Lavoro per soldi, ma ho ancora il diritto di scegliere un lavoro a mio piacimento!","Sono un uomo libero! E ho il diritto di accettare un nuovo lavoro quando voglio!","Non sono uno schiavo che lavora per il cibo, quindi la mia coscienza è pulita! Ma non parteciperò più a nessuna rapina!");
				Link.l1 = "Beh, in realtà, ti sbagli... Mentre bevevi alla taverna, potevi scegliere qualsiasi lavoro ti piaceva... Ma non appena sei salito a bordo della mia nave, il tuo unico ritorno è diventato una palla di cannone che frantuma il tuo collo... E con la lingua strappata, così che non balbuzisci niente nell'altro mondo...";
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "WantToGo_stop_stay";
				}
				else
				{
					Link.l1.go = "WantToGo_stop_fight";	
				}
				Link.l2 = "Bene. Puoi andare... Ma Dio ti proibisca di incontrarmi in mare aperto. Ti giuro, te ne pentirai del momento in cui hai deciso di non restare al mio fianco.";
				Link.l2.go = "exit_fire_5";
			}
			else
			{
				dialog.text = LinkRandPhrase("Non cercare nemmeno di intimidirmi! Lavoro per soldi, ma ho ancora il diritto di scegliere un lavoro che mi piace!","Sono un uomo libero! E ho il diritto di trovare un nuovo lavoro quando voglio!","Non sono il tuo schiavo! E non continuerò a vivere una vita miserabile sulla tua vecchia tinozza!");
				Link.l1 = "Ebbene, in realtà, vi sbagliate... Mentre bevevate alla taverna, potevate scegliere qualsiasi lavoro vi piacesse... Ma non appena avete messo piede sulla mia nave, l'unico modo per tornare indietro è diventato un colpo di cannone che vi spezza il collo... E con la lingua strappata, così che non sbotterete nulla nel mondo successivo...";
				// belamour legendary edition можно запугать офицера -->
				//if (makeint(Pchar.Rank) > makeint(NPchar.Rank) || CheckCharacterPerk(pchar, "IronWill"))
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "WantToGo_stop_stay";
				}
				else
				{
					Link.l1.go = "WantToGo_stop_fight";	
				}
				Link.l2 = "Va bene. Puoi andare... Ma Dio ti proibisca di incontrarmi in mare aperto. Ti giuro, rimpiangerai il momento in cui hai deciso di non rimanere al mio fianco.";
				Link.l2.go = "exit_fire_5";
			}
		break;
		
		case "WantToGo_stop_stay":
			dialog.text = RandPhraseSimple("Se lo metti in questo modo, rimarrò, semplicemente non ho altra scelta. Ma tieni presente che non lo sto facendo di mia spontanea volontà...","Bene, se la metti in questo modo, resterò. Ma sappi che facendo così vado contro la mia volontà.");
			Link.l1 = RandPhraseSimple("Va bene... Servi fino a quando decido di lasciarti andare.","Bene così. Continua a servire... Deciderò io quando lasciarti andare.");
			Link.l1.go = "WantToGo_Munity"; //этот линк ведет к бегству
		break;
		
		case "WantToGo_stop_fight":
			dialog.text = NPCharRepPhrase(NPChar,"Non mi costringerai mai a ripensarci! Non hai diritti per tenermi come uno schiavo! Sto per andarmene, stai lontano o sei finito.","Pensi di poter spaventare un ufficiale veterano?! Più di una volta sono stato a un soffio dalla morte. E se la metti in questo modo, è molto meglio morire in una battaglia leale piuttosto che durante un sanguinoso saccheggio!");
			Link.l1 = NPCharRepPhrase(NPChar,"Ebbene... ognuno sceglie il proprio destino. Spero che tu abbia detto le tue preghiere prima di venire da me.","Se avessi saputo che sarebbe successo quando ti ho raccolto nella taverna, avrei preferito lasciarti pendere dalla forca. E ora non è troppo tardi per organizzarlo...");
			Link.l1.go = "WantToGo_stop_fight_1";
			Link.l2 = NPCharRepPhrase(NPChar,"Bene, puoi andartene se hai così tanto bisogno della tua libertà. Ma non ti darò alcuna raccomandazione.","Bene. Puoi andare... Ma Dio ti proibisca di incontrarmi in mare aperto. Giuro, te ne pentirai del momento in cui hai deciso di non restare al mio fianco.");
			Link.l2.go = "exit_fire_5";	
		break;
		
		case "WantToGo_stop_fight_1":
			ChangeOfficersLoyality("bad_all", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			dialog.text = NPCharRepPhrase(NPChar,"Smettetela di intimidirmi! Quale dei vostri poltroni oserà sfidarmi? Se fossi io il capitano, sarebbero già pieni di soldi! E dopo avervi impegnato in tutta questa carità, temete che il vostro equipaggio prenderà le mie parti?!","Lascia perdere i tuoi modi, non mi farai paura! Addio.");
			Link.l1 = NPCharRepPhrase(NPChar,"No, compagno, non vivrai abbastanza a lungo per arrivare alla forca. Un lusso del genere non è per te...","Non così veloce amico, non siamo ancora pari, mi devi ancora.");
			Link.l1.go = "Get_out_fight";
		break;	
		///////////////////////////////////////////////////////////////////////////////////
		case "WantToGo_Munity":	//zagolski. отыгрыш бегство офицера
			Diag.TempNode = "Hired";
			// belamour legendary edition в ближайшее время не подойдет от страха
			/* if(CheckCharacterPerk(pchar, "IronWill"))
			{
				Npchar.loyality = makeint(Npchar.loyality) + 3 + hrand(sti(GetSummonSkillFromNameToOld(pchar,SKILL_FORTUNE)+GetSummonSkillFromNameToOld(pchar,SKILL_LEADERSHIP)));
				log_info(GetFullName(Npchar)+" increased his loyalty");
				log_testinfo("Loyalty has become: " + Npchar.loyality + " of " + MAX_LOYALITY);
			}
			else
			{ */
				if (!CheckAttribute(pchar, "questTemp.MutinyOfficerIDX"))
				{
					pchar.questTemp.MutinyOfficerIDX = npchar.index;
					npchar.quest.Mutiny = true; // mitrokosta доп защита от багов
					SetFunctionTimerCondition("mOfficer_fc", 0, 0, 1, false);
				}
			//}
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.location = "none";
			LAi_SetOfficerType(NPChar);
			DialogExit();
		break;
		////////////////////////////////////////////////////////////////////
		// пассажир возмущен игроком и сваливает <--
		
		case "Node_2":
			dialog.text = NPCharRepPhrase(Npchar,RandSwear()+"Sono il migliore "+XI_ConvertString(Npchar.quest.officertype)+" in queste acque. "+Npchar.quest.officertype_2+"E sono pronto a fare un favore e servire sotto di te.","Bene, dicono che non sono male "+XI_ConvertString(Npchar.quest.officertype)+". "+Npchar.quest.officertype_2+"Potete prendermi sulla vostra nave, capitano, e vedere di persona.");
			Link.l1 = "E quanto vuoi?";
			Link.l1.go = "price";
			Link.l2 = "E che tipo di specialista sei?";
			Link.l2.go = "ShowParam_exit";
			Link.l3 = "Purtroppo, ho già un "+XI_ConvertString(Npchar.quest.officertype)+".";
			Link.l3.go = "Exit";
		break;

		case "OnceAgain":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = RandPhraseSimple("Ehi, capitano, metà della guarnigione ti sta cercando in questo momento. Sicuramente non è il momento migliore per essere assunti nel tuo equipaggio!","E combattere per raggiungere la nave? No, cap, un'altra volta...");
				link.l1 = RandPhraseSimple("Come desideri...","Effettivamente, non avevo intenzione di assumerti."); 
				link.l1.go = "exit";
				break;
			}
			Diag.TempNode = "OnceAgain";
			dialog.text = "Hai cambiato idea, capitano? Hai deciso che un nuovo "+XI_ConvertString(Npchar.quest.officertype)+" non farebbe male?";
			// boal -->
			if (FindFreeRandomOfficer() > 0)
			{
                Link.l1 = "Qualcosa del genere. Quanto vuoi?";
                Link.l1.go = "price";
			}
			Link.l2 = "E di cosa sei capace?";
			Link.l2.go = "ShowParam_exit";
			// boal <--
			Link.l3 = "Ho un set completo. Ci vediamo.";
			Link.l3.go = "exit";
		break;

		case "price":
			dialog.text = "Credo che possiamo concordare su "+Npchar.quest.OfficerPrice+" pesos.";
			if(Npchar.rank >= 15)
			{
				dialog.text = "Credo che possiamo concordare su "+(makeint(Npchar.quest.OfficerPrice)/ 100+30)+" dobloni.";
			}	
			Link.l1 = "Non è un po' troppo?";
			Link.l1.go = "trade";
			Link.l2 = "Sono d'accordo. Considerati parte dell'equipaggio.";
			Link.l2.go = "hire";
			Link.l3 = "Non vali questi soldi.";
			Link.l3.go = "exit";
		break;

		case "trade":
			if (GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE) >= Rand(12) && (sti(Npchar.quest.OfficerPrice) - GetCharacterSkillToOld(Pchar, "commerce")*100) >= sti(Npchar.quest.OfficerLowPrice))// bug fix
			{
				Npchar.quest.OfficerPrice = makeint(makeint(Npchar.quest.OfficerPrice) - GetCharacterSkillToOld(Pchar, "commerce")*100); // пусть будет коммерция перса голой
				dialog.text = "Bene... Penso che potrei essere d'accordo anche su "+Npchar.quest.OfficerPrice+" pesos. Che ne dici?";
				if(Npchar.rank >= 15)
				{
					dialog.text = "Suppongo che potrei essere d'accordo anche su "+(makeint(Npchar.quest.OfficerPrice)/ 100+30)+" dobloni. Cosa ne dici?";
				}
				Link.l1 = "Ecco, molto meglio. Sei dentro.";
				Link.l1.go = "hire";				
				Link.l2 = "Continuo a pensare che sia un po' troppo. Addio.";
				Link.l2.go = "exit";
			}
			else
			{
				dialog.text = "Mi dispiace, capitano, ma valgo esattamente quanto ho chiesto. Se è troppo per te, allora trova qualcun altro.";
				Link.l1 = "Bene, sono d'accordo. Ti prenderò con me.";
				Link.l1.go = "hire";				
				Link.l2 = "Ecco quello che sto per fare. Addio.";
				Link.l2.go = "exit";
			}
		break;

		case "hire":
			dialog.text = "Vedo che sei a corto di denaro, capitano! Mi dispiace, ma non lavoro a credito.";
			Link.l1 = "Oh, diavolo!";
			Link.l1.go = "Exit";
			if(Npchar.rank < 15 && makeint(Pchar.money) >= makeint(Npchar.quest.OfficerPrice))
			{
				AddMoneyToCharacter(Pchar, -(makeint(Npchar.quest.OfficerPrice)));
				Diag.TempNode = "OnboardSoon";
				dialog.text = "Grazie, capitano. Non te ne pentirai della tua scelta.";
				Link.l1 = "Spero proprio di sì.";
				Link.l1.go = "Exit_hire";								
			}
			if(Npchar.rank >= 15 && PCharDublonsTotal() >= makeint((makeint(Npchar.quest.OfficerPrice) / 100 + 30)))
			{
				RemoveDublonsFromPCharTotal(makeint((makeint(Npchar.quest.OfficerPrice) / 100 + 30)));
				Diag.TempNode = "OnboardSoon";
				dialog.text = "Grazie, capitano. Non rimpiangerai la tua scelta.";
				Link.l1 = "Spero proprio di sì.";
				Link.l1.go = "Exit_hire";								
			}
		break;

		case "OnboardSoon":			
			Diag.TempNode = "OnboardSoon";
			dialog.text = "Terminerò solo il mio drink, capitano, e poi andrò alla nave. Non preoccuparti, ci sarò in tempo.";
			Link.l1 = "Bene. Se arrivi in ritardo, ti farò strofinare il ponte!";
			Link.l1.go = "Exit";											
		break;
        
		case "QMASTER_1":
			if(sti(PChar.Ship.Type) == SHIP_NOTUSED)
			{
				dialog.text = "Capitano, ma non hai una nave!";
				Link.l1 = "Grazie per avermelo ricordato...";
				Link.l1.go = "Exit";
				Diag.TempNode = "Hired";
				break;
			}
			// Rebbebion, добавил фикс отображения знака процента
			dialog.text = "Massima attività dei ratti in viaggio "+FloatToString(50.0 /(2.0+GetSummonSkillFromNameToOld(PChar,SKILL_REPAIR)+GetSummonSkillFromNameToOld(PChar,SKILL_SNEAK)),1)+"%% della quantità totale del carico. Per "+GetCrewQuantity(PChar)+" marinai di cui avremo bisogno "+makeint((GetCrewQuantity(PChar)+6)/ 10)+" cibo al giorno. Questo senza contare gli schiavi in trasporto.";
			Link.l1 = "Grazie.";
			Link.l1.go = "Exit";
			Diag.TempNode = "Hired";
		break;
        
        // boal 05.09.03 offecer need to go to abordage -->
        case "stay_follow":
            dialog.text = "Quali sono i vostri ordini?";
            Link.l1 = "Stai qui!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Seguitemi e non rimanete indietro!";
            Link.l2.go = "Boal_Follow";
            // boal 05.09.03 offecer need to go to abordage <--
			if (npchar.id == "OffMushketer")
			{
				Link.l3 = "Voglio che tu mantenga una certa distanza dal bersaglio.";
				Link.l3.go = "TargetDistance";
			}
			
			if(CheckAttribute(NPChar, "equip.gun"))
			{
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l4 = "Dobbiamo cambiare il tipo di munizioni per la tua arma da fuoco.";
					Link.l4.go = "SetGunBullets";
				}	
			}
			if(CheckAttribute(NPChar, "equip.musket"))
			{
				if(CheckAttribute(NPChar, "chr_ai.musket.bulletNum") && sti(NPChar.chr_ai.musket.bulletNum) > 1)
				{
					Link.l5 = "Dobbiamo cambiare il tipo di munizioni per il tuo moschetto.";
					Link.l5.go = "SetMusketBullets";
				}
					Link.l6 = "Dobbiamo cambiare la tua arma principale per il combattimento.";
					Link.l6.go = "SetPriorityMode";
			}
		break;

		case "SetGunBullets":
			Dialog.Text = "Scegli il tipo di munizioni:";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			Diag.CurrentNode = Diag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;
		
		case "SetMusketBullets":
			Dialog.Text = "Scegli il tipo di munizioni:";
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.musket.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
				Link.(attrL).go = "SetMusketBullets1_" + i;
			}
		break;	

		case "SetMusketBullets2":
			i = sti(NPChar.SetMusketBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, MUSKET_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, MUSKET_ITEM_TYPE);
			Diag.CurrentNode = Diag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetMusketBullets");
			DialogExit();
		break;
		
		case "SetPriorityMode":
			Dialog.Text = "All'inizio della lotta userai:";
			Link.l1 = "Lama";
			Link.l1.go = "BladePriorityMode";
			Link.l2 = "Moschetto";
			Link.l2.go = "MusketPriorityMode";
		break;
		
		case "BladePriorityMode":
            SetPriorityMode(NPChar, 1);
			DialogExit();
		break;
		
		case "MusketPriorityMode":
			SetPriorityMode(NPChar, 2);
			DialogExit();
		break;
		
		case "TargetDistance":
			dialog.text = "Quale distanza esattamente, capitano? Indica in passi, ma non più di 20.";
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";			
		break;
		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = "Capitano, stai bene?";
				link.l1 = "Mi dispiace, la mia colpa...";
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "Resterò fermo senza muovermi. È quello che vuoi da me, capitano?";
				link.l1 = "Sì. È esattamente quello che si richiede di te.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = "Credo di avervi detto che non posso stare a più di 20 passi dal bersaglio.";
				link.l1 = "Bene, mantieni la distanza di 20 metri.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = "Compreso e preso in considerazione.";
			link.l1 = "Bene.";
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;

		case "AsYouWish":
			// проверка на море -->
			if (bSeaActive)
			{
				attr = Sea_FindNearColony();
				if (attr == "none")
				{
					dialog.text = "Capitano, anche se davvero non capisco il tuo ragionamento, potremmo parlarne a terra? O hai deciso di gettarmi semplicemente fuoribordo?";
					Link.l1 = "Mmm... No, non è quello che intendevo. Rimani qui finché non arriviamo al porto.";
					Link.l1.go = "Exit";	
					break;	
				}
			}
			// проверка на море <--
			if (makeint(PChar.reputation.nobility) >= 41 && makeint(NPChar.reputation) < 41) //герой против злодея
			{
				dialog.text = RandPhraseSimple(LinkRandPhrase("Ecco qualcosa di nuovo!","Perché, nel nome del Cielo?","Qual è il motivo?!"),RandPhraseSimple("Capitano, sei pazzo? Dire tali notizie senza preavviso!","Caspita! E cosa ho fatto per scontentarti?"));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("Ho deciso di mettere ordine nell'equipaggio. E non mi piacciono i tuoi rapporti con i tuoi colleghi","I tuoi vantaggi non erano così buoni come discusso durante l'assunzione. Dunque,","Canaglie e furfanti nella mia squadra non resteranno! Quindi,"),LinkRandPhrase("È venuto a mia conoscenza che stai rubando il rum, abituando segretamente il mio equipaggio a bere pesante e quindi abbassando il suo morale. Pertanto,","Ne ho abbastanza dei tuoi modi da bandito e non ho intenzione di tollerarli. Quindi,","Passi costantemente il tuo tempo nella cabina centrale per una partita a carte o dadi, distraendo gli altri ufficiali dall'esecuzione del dovere. Questo non può continuare all'infinito. Dunque,"))+"impacchetta le tue cose e lascia la nave.";
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "Get_out_A1_peace";
				}
				else
				{
					Link.l1.go = "Get_out_A1_strife";
				}
				break;	
			}
			if (makeint(PChar.reputation.nobility) >= 41 && makeint(NPChar.reputation) >= 41) // герой против героя
			{
				dialog.text = RandPhraseSimple(RandPhraseSimple("Posso sapere il motivo di una tale decisione?","Ovviamente, tale decisione è ben motivata?"),RandPhraseSimple("Spiega, capitano","Questo è davvero inaspettato. Ma mi piacerebbe ancora conoscere il motivo."));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("Sono completamente insoddisfatto del tuo atteggiamento verso i tuoi doveri.","Sfortunatamente, non sei stato un buon ufficiale e probabilmente non lo sarai mai...","Sei un buon ufficiale e il tuo servizio è stato leale, ma ora le nostre strade si sono divise. Non chiedermi perché."),LinkRandPhrase("Ti ho avvertito che la passione per il rum ti avrebbe distrutto. Come posso fidarmi di un uomo in battaglia che non è neanche in grado di infilare la sua spada nel fodero?","Sei un marinaio e un ufficiale terribile... Penso che passerai più tempo a terra che in mare.","Non sono soddisfatto delle tue qualifiche, ma ora ho finalmente trovato un degno sostituto."));
				Link.l1.go = "Get_out_A2";
				break;	
			}
			if (makeint(PChar.reputation.nobility) < 41 && makeint(NPChar.reputation) >= 41) // злодей против героя 
			{		
				dialog.text = RandPhraseSimple(RandPhraseSimple("Mmm... Posso sapere il motivo?","È una affermazione seria. Posso sapere in particolare di cosa sei insoddisfatto?"),RandPhraseSimple("Spiega te stesso, capitano.","Ovviamente, tale affermazione è ben motivata?"));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("Sono totalmente insoddisfatto della tua qualificazione, quindi","Sfortunatamente, non ti sei dimostrato un ufficiale decente. Quindi,","Ne ho abbastanza dei vostri modi nobili. Non li tollererò all'infinito, quindi"),LinkRandPhrase("È venuto alla mia conoscenza che stai incitando l'equipaggio alla disobbedienza. Non ci saranno disturbi sulla mia nave! E non ringraziarmi per non averti buttato via prima. Quindi","I vostri nobili principi vi fanno onore, ma sono contrari alla vita di brigante del libero corsaro. Quindi","Non mi piace il tuo rapporto con i tuoi doveri. Quindi"))+"impacchetta le tue cose e lascia la nave.";
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "Get_out_A3_peace";
				}
				else
				{
					Link.l1.go = "Get_out_A3_strife";
				}	
				break;
	
			}
			if (makeint(PChar.reputation.nobility) < 41 && makeint(NPChar.reputation) < 41) // злодей против злодея
			{	
				dialog.text = RandPhraseSimple(LinkRandPhrase("Capitano, davvero non me lo aspettavo! Forse mi spiegheresti cosa sta succedendo?","Capitano, cosa ti tormenta?!","Cosa intendi con questo, capitano?!"),RandPhraseSimple("Che diavolo, capitano?! Tutto sembrava andare bene ieri, e ora eccoci qui, cosa è successo?","Caspita! Forse, ti spiegheresti?"));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("Sei un totale fannullone e un idiota inutile, perfino un mozzo su una nave farebbe meglio. Ho sofferto a causa tua per troppo tempo. Quindi","Stavo pensando di licenziarti da un po', e ora ho finalmente trovato un degno sostituto. Quindi","È giunto alla mia conoscenza che stai rubando rum, abituando segretamente il mio equipaggio a bere pesantemente e così abbassando il suo morale. Pertanto"),LinkRandPhrase("Quando ti ho assunto, ti vantavi di essere il miglior ufficiale dell'intera flotta, ma si è scoperto che eri solo un fannullone, quindi","Ti ho avvertito che la tua abitudine a bere avrebbe finito male. Perché dovrei tenere un ubriacone inutile sulla mia nave? Quindi","Invece di servire, sei costantemente in giro da qualche parte o stai giocando a carte o dadi. Spero tu non pensassi che questo potesse continuare all'infinito? Quindi"))+"riunisci i tuoi averi e lascia la nave.";
				Link.l1.go = "Get_out_A4";
				break;
			}
		break;
	
		case "Get_out_A1_peace":
			dialog.text = RandPhraseSimple(LinkRandPhrase("Allora come stai parlando adesso! Va bene, come desideri. Ma stai certo: non tornerò da te, anche se sto morendo di fame!","Sinceramente, non mi piacciono molto nemmeno i vostri nobili giochi. Quindi addio...","Oh, vai all'inferno! Rimani con i tuoi leccapiedi. Un 'eroe', davvero!"),LinkRandPhrase("Effettivamente, non mi è mai piaciuto servirti... Hai una chiatta cargo lì, non una nave decente. Più probabilmente un istituto di perfezionamento...","Sai, sono stanco del tuo equipaggio, tutti quei pavoni, solo ragazzini, nemmeno un vero uomo...","Bene, capitano, come dici tu. Ma Dio sa, stavo facendo bene il mio lavoro..."));
			Link.l1 = "Fermati. Al momento non posso lasciare la nave senza un ufficiale. Ma più tardi torneremo a questa conversazione.";
			Link.l1.go = "exit_bad";
			Link.l2 = "Allora vai in pace.";
			Link.l2.go = "Exit_Fire_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "Non ti scaldare. Ho preparato per te una liquidazione - "+sti(NPChar.rank)*500+" pesos. Spero che questo rimuoverà tutte le domande.";
				Link.l3.go = "Get_out_А1_ForMoney";
			}
		break;

		case "Get_out_A1_strife":
			dialog.text = LinkRandPhrase("Scusatemi! Cosa intendi con 'lasciare la nave'?! Non ho esposto la mia testa alle palle di cannone solo per farmi buttare fuori quando ti pare e piace!","Ha! 'Lasciare la nave'! Pensi seriamente che ti permetterò di gettarmi via come un gattino?!","Piano, capitano, le persone serie non risolvono le questioni in questo modo. Non sarò trattato come un novellino.");
			Link.l1 = "Bene, puoi restare per ora - ma solo fino a quando non trovo un sostituto decente.";
			Link.l1.go = "exit_bad";
			Link.l2 = "Ripeto, il tuo servizio è finito. Puoi fare i bagagli.";
			Link.l2.go = "Get_out_A1_strife_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "Non ti agitare. Ho preparato "+sti(NPChar.rank)*500+" pesos per te. Spero che ciò rimuova tutte le domande.";
				Link.l3.go = "Get_out_А1_ForMoney";
			}
		break;

		case "Get_out_A1_strife_1":
			dialog.text = RandPhraseSimple("In realtà, non desidero ardentemente rimanere qui. Ma nemmeno me ne andrò senza un risarcimento!","Ora, certamente non resterò su quella vecchia tinozza di tua proprietà, ma prima mi compenserai!")+" "+sti(NPChar.rank)*1000+" pesos, e ci dimenticheremo l'uno dell'altro.";
			Link.l1 = "Mi sono un po' agitato... Per favore, accetta le mie scuse e torna ai tuoi doveri.";
			Link.l1.go = "exit_bad1";
			Link.l2 = "Di che soldi stai parlando se hai sempre ricevuto la tua parte equa? Questo mi sembra estorsione!";
			Link.l2.go = "Get_out_А1_strife_battle";
			if (sti(Pchar.money) >= sti(NPChar.rank)*1000)
			{
				Link.l3 = "Bene. Restituisci l'equipaggiamento, e poi avrai quello che hai chiesto.";
				Link.l3.go = "Get_out_А1_chang";
			}
		break;

		case "Get_out_А1_ForMoney":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			dialog.text = "Ecco una storia diversa. Addio!";
			Link.l1 = "Spero vivamente che i nostri percorsi non si incrocino mai più.";
			Link.l1.go = "Exit_Fire_1";
		break;

		case "Get_out_А1_strife_battle":
			dialog.text = LinkRandPhrase("Considera questo un risarcimento per danni morali. Non tollererò un tale trattamento, e chiunque osi trattarmi in questo modo se ne pentirà!","Questo non è un'estorsione, ma piuttosto un risarcimento per questa stupida perdita del mio tempo! E lo otterrò, a qualunque costo!","Ho sprecato troppo tempo al servizio di un fifone come te. Avrei potuto fare una fortuna saccheggiando navi mercantili. Quindi voglio solo compensare il mio profitto perduto.");
			if (sti(Pchar.money) >= sti(NPChar.rank)*1000)
			{
				Link.l1 = "Bene. Ecco i tuoi soldi... E ora sparisci!";
				Link.l1.go = "Get_out_А1_ForMoney_angry";
			}
			Link.l2 = "Sembra che tu stia dimenticando chi sei! Non permetterò a sciocchi come te di urlare contro di me!";
			Link.l2.go = "Get_out_А1_strife_death";
		break;

		case "Get_out_А1_strife_death":
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			OfficersReaction("good");
			dialog.text = "Vai avanti, capitano! Mostra te stesso!";
			Link.l1 = "Dio sa, non lo volevo!";
			Link.l1.go = "Get_out_fight";
		break;
	
		case "Get_out_А1_ForMoney_angry":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			OfficersReaction("bad");
			dialog.text = "Ecco una storia diversa. Addio!";
			Link.l1 = "Spero davvero che i nostri percorsi non si incrocino mai più.";
			Link.l1.go = "Exit_Fire_1";
		break;

		case "Get_out_A2":
			dialog.text = RandPhraseSimple(LinkRandPhrase("Ebbene, è deciso, allora. Addio, capitano, e non serbare rancore...","Un peccato, capitano. Ma Dio sa, ho provato. Addio.","Ebbene, capitano, sei certamente difficile da accontentare! Bene, buona fortuna a te."),LinkRandPhrase("Un peccato, capitano. Sai, mi piaceva lavorare per te.","Sì, le cose succedono... Ma non porto rancore. Addio.","Sei ingiusto con me, capitano. Tuttavia, rispetto la tua decisione. Addio."));
			Link.l1 = "Aspetta, ho cambiato idea. Torniamo a parlare di questo più tardi.";
			Link.l1.go = "exit_good";
			Link.l2 = "Non ti abbattere. Buona fortuna a te...";
			Link.l2.go = "exit_fire_2";
			Link.l3 = "Aspetta... ti ho fornito un bel equipaggiamento. Ridammi tutto, non ho intenzione di equipaggiare un'intera orda...";
			Link.l3.go = "Return_items_A2";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l4 = "Aspetta... Non voglio lasciarti andare a mani vuote. Ecco, prendi "+sti(NPChar.rank)*500+" pesos. Ti saranno utili mentre cerchi un nuovo lavoro.";
			}
			Link.l4.go = "Im_kind_A2";
		break;

		case "Return_items_A2":
			ChangeOfficersLoyality("bad_all", 1);
			dialog.text = "Oh, certo, riprenditi tutto...";
			Link.l1 = "So che mi capisci bene...";
			Link.l1.go = "Get_out_А2_chang";
		break;

		case "Im_kind_A2":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeOfficersLoyality("good_all", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			dialog.text = "Grazie, capitano! Una generosità davvero inaspettata... Sai, ho ancora alcune delle tue cose, forse vorresti riaverle?";
			Link.l1 = "Forse... Trovare una buona lama non è così facile oggigiorno...";
			Link.l1.go = "Get_out_А2_chang";
			Link.l2 = "Oh, non preoccuparti. Conservali come ricordo del tuo servizio.";
			Link.l2.go = "exit_fire_2";
		break;

		case "Get_out_A3_peace":
			dialog.text = RandPhraseSimple(LinkRandPhrase("Bene, come desideri. Ma stai certo: non tornerò da te, anche se sto morendo di fame!!","Capitano, il tuo modo banditesco di fare affari mi fa sentire male. Prima o poi, questo era destinato a succedere. E non c'è bisogno di inventare alcuna ragione.","Rimani con i tuoi tagliagole, allora. Un uomo decente non mostrerebbe nemmeno il suo volto nella sala degli ufficiali della tua nave. Che bordello hai qui, Dio me ne scampi!"),LinkRandPhrase("Sinceramente, non mi è piaciuto il mio servizio sotto di te. Hai assunto un equipaggio pieno di mascalzoni, non c'è un solo uomo decente con cui chiacchierare.","Sì, se continui con quell'atteggiamento verso il tuo equipaggio, presto sarai completamente solo e non ci sarà bisogno di inventare alcuna scusa.","La nostra inimicizia è reciproca, e questo mi consola. Addio."));
			Link.l1 = "Aspetta. Ora non è il momento migliore per il tuo pensionamento. Ma tutte le richieste rimangono valide.";
			Link.l1.go = "exit_bad";
			Link.l2 = "Vai, vai. Me la caverò benissimo senza le tue lezioni.";
			Link.l2.go = "exit_fire_3";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "Aspetta. Ti darò "+sti(NPChar.rank)*500+" pesos. Non voglio che tu muoia in un fosso, così mi sentirei colpevole.";
				Link.l3.go = "Get_out_А3_ForMoney";
			}
		break;

		case "Get_out_А3_ForMoney":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			ChangeOfficersLoyality("good_all", 1);
			dialog.text = LinkRandPhrase("Bene, grazie. Addio...","Grazie per la tua comprensione. Buona fortuna.","Ora abbiamo finito. Buona fortuna...");
			Link.l1 = "So che mi capisci bene.";
			Link.l1.go = "exit_fire_3";
		break;
	
		case "Get_out_A3_strife":
			dialog.text = LinkRandPhrase("Ma capitano, in quel caso rimango a secco. Sei davvero disposto a mandarmi dalla nave direttamente al sagrato?","Sei ingiusto con me, capitano. Ma non avrò rancore se riceverò un compenso decente.","E questa è la tua gratitudine per tutte le mie ferite di battaglia? Beh, immagino che non posso fare a meno di un compenso monetario.");
			Link.l1 = "Bene, ho cambiato idea. Puoi restare, ma torneremo a parlare di questo.";
			Link.l1.go = "exit_bad";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l2 = "Oh, non preoccuparti. Ecco - "+sti(NPChar.rank)*500+" pesos. Questo compenserà il tuo tempo sulla mia nave.";
				Link.l2.go = "Get_out_А3_ForMoney";
				Link.l3 = "Ti darò i soldi. Comunque, grazie a me sei ben equipaggiato, e penso sia appropriato restituire le cose a me.";
				Link.l3.go = "Return_items_A3";
			}
			Link.l4 = "Oh, davvero? E che ne dici della tua parte, che stavi ricevendo regolarmente?! Sapevo che tutto sarebbe finito in lamentele e preghiere per un premio extra.";
			Link.l4.go = "Get_out_A3_strife_1";
		break;

		case "Return_items_A3":
			dialog.text = "Sapevo che avresti detto questo, ma riavrà la tua attrezzatura solo una volta che ricevo "+sti(NPChar.rank)*1000+" pesos. Altrimenti puoi averlo solo sul mio cadavere!";
			Link.l1 = "Bene, prendi i tuoi soldi, allora.";
			Link.l1.go = "Get_out_А3_chang";
			Link.l2 = "Sei pazzo o cosa?! Esigere una somma così per quello che ti è stato dato gratuitamente?! Ora vedo che la tua avidità ha chiaramente vinto sulla tua finta bontà.";
			Link.l2.go = "Get_out_A3_strife_1";
		break;

		case "Get_out_A3_strife_1":
			dialog.text = "Non osare insultarmi! Potrei non essere il migliore nella Marina, ma sono comunque un ufficiale combattente. E sarò rispettato, anche da un rustico come te!";
			Link.l1 = "Se non l'hai ancora capito, lo ripeterò un'altra volta: smetti di mendicare, non otterrai nulla da me.";
			Link.l1.go = "Get_out_А3_strife_death";
		break;

		case "Get_out_А3_strife_death":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			OfficersReaction("bad");
			dialog.text = "Ebbene, otterrò comunque soddisfazione!";
			Link.l1 = "Oh, quindi è una sfida, vero? Come desideri allora...";
			Link.l1.go = "Get_out_fight";
		break;

		case "Get_out_A4":
			dialog.text = RandPhraseSimple(LinkRandPhrase("Questa è la mia fortuna! Metto cuore e anima nel servizio solo per essere cacciato senza nemmeno un beneficio di servizio!","Che sfortuna?! Vengo assunto e poi vengo cacciato quasi subito. Non ho idea a quale santo accendere una candela in questi giorni...","Caspita! Licenziato per la terza volta quest'anno, tutte di lunedì. Forse, non dovrei presentarmi alla presenza del capitano quando ho i postumi di una sbornia."),LinkRandPhrase("Bene, come desideri. Prega che non ci incontriamo mai più.","Come desideri. Tieni però a mente che non troverai mai un ufficiale migliore.","Bene, capitano, come dici tu. Ma Dio sa, ho svolto bene il mio lavoro..."));
			Link.l1 = "Fermo. Ora non è il momento migliore per il tuo pensionamento. Ma tutte le richieste sono valide.";
			Link.l1.go = "exit_good";
			Link.l2 = RandPhraseSimple("Vattene ora. E ringrazia Dio che oggi sono di buon umore.","Sparisci ora. Sei un buon ufficiale quanto la merda è buona per fare proiettili.");
			Link.l2.go = "exit_fire_4";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "Aspetta. Ti darò "+sti(NPChar.rank)*500+" pesos. Non voglio che tu muoia in un fosso, così mi sentirei colpevole.";
				Link.l3.go = "Get_out_А4_ForMoney";
			}
			Link.l4 = "Aspetta... Ti ho equipaggiato bene, restituiscimi le mie cose.";
			Link.l4.go = "Return_items_A4";
		break;

		case "Get_out_А4_ForMoney":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			ChangeOfficersLoyality("good_all", 1);
			dialog.text = LinkRandPhrase("Oh, grazie, capitano! Questo è davvero gentile da parte tua...","Grazie per la vostra comprensione. Buona fortuna.","Ora abbiamo finito. Buona fortuna...");
			Link.l1 = "Buona fortuna. Spero che non la sprechi tutta nella prima taverna.";
			Link.l1.go = "exit_fire_4";
		break;

		case "Return_items_A4":
			if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
			{
				dialog.text = LinkRandPhrase("E ora stai prendendo la mia attrezzatura! Oh, mio, al diavolo! Andrò a pescare, lo giuro...","Vedo che hai deciso di spogliarmi completamente. Oh, beh. Ora c'è solo una strada per me, verso il parvis...","Oh, grazie mille! Ora hai deciso di derubarmi. Oh, che crudele destino... Prendilo allora, prendilo! Cosa posso fare comunque...");
				Link.l1 = "Sparisci adesso. Sei un ufficiale bravo quanto la merda è buona per fare proiettili.";
				Link.l1.go = "Get_out_А4_chang_1";
			}
			else	
			{
				dialog.text = RandPhraseSimple("Come desiderate, capitano, ma prima per favore sarebbe così gentile da darmi "+sti(NPChar.rank)*1000+" pesos. Considera questo come un risarcimento per il danno morale.","Bene. Ma voglio ancora ricevere "+sti(NPChar.rank)*1000+" pesos come compensazione per il mio duro ed fedele servizio.");
				if (sti(Pchar.money) >= sti(NPChar.rank)*1000)
				{
					Link.l1 = "Che furfante! Va bene, ecco i tuoi soldi.";
					Link.l1.go = "Get_out_А4_chang";
				}
				Link.l2 = "Non sei pazzo?! Come osi chiedere così tanti soldi per quello che ti ho dato io stesso!";
				Link.l2.go = "Get_out_A4_strife";
				Link.l3 = "Ah-ha! Stavo scherzando! Come potrei cacciare un vecchio amico, con un cappello tutto bucherellato!";
				Link.l3.go = "exit_bad1";
			}
		break;

		case "Get_out_A4_strife":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			ChangeOfficersLoyality("bad_all", 1);
			dialog.text = "Ebbene, allora non otterrai nulla! Non farò un passo finché non sento il tintinnio dei miei soldi!";
			Link.l1 = RandPhraseSimple("Presto sentirai il tintinnio della mia spada!","Allora sarai portato via con i piedi avanti!");
			Link.l1.go = "Get_out_fight";
		break;

		case "Get_out_fight":
			CheckForReleaseOfficer(GetCharacterIndex(Npchar.id));
			RemovePassenger(Pchar, Npchar);
			LAi_CharacterDisableDialog(NPChar);
			LAi_SetWarriorType(Npchar);
			LAi_group_MoveCharacter(Npchar, "TmpEnemy");
			LAi_group_SetHearRadius("TmpEnemy", 100.0);
			LAi_group_FightGroupsEx("TmpEnemy", LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
			if (PChar.location == Get_My_Cabin() || findsubstr(PChar.location, "_tavern" , 0) != -1 || findsubstr(PChar.location, "_store" , 0) != -1)
            {
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				LAi_group_SetCheck("TmpEnemy", "CannotFightCurLocation");
				LAi_group_SetCheck("TmpEnemy", "MainHeroFightModeOff");
            }
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

	    case "Get_out_А1_chang": // интерфейс обмена
			Diag.TempNode = "Fired_1";
			LAi_CharacterDisableDialog(NPChar);
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;	
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_А2_chang": // интерфейс обмена
			Diag.TempNode = "Fired_2";
			LAi_CharacterDisableDialog(NPChar);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_А3_chang": // интерфейс обмена
			Diag.TempNode = "Fired_3";
			LAi_CharacterDisableDialog(NPChar);
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_А4_chang_1": // интерфейс обмена
			Diag.TempNode = "Fired_4";
			LAi_CharacterDisableDialog(NPChar);
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;	
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_А4_chang": // интерфейс обмена
			Diag.TempNode = "Fired_4";
			LAi_CharacterDisableDialog(NPChar);
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;	
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

	    case "exit_bad":
			Npchar.loyality = makeint(Npchar.loyality) - 3;
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_bad1":
			Npchar.loyality = makeint(Npchar.loyality) - 2;
			ChangeOfficersLoyality("bad_all", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			Diag.CurrentNode = Diag.TempNode;			
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_good":
			Npchar.loyality = makeint(Npchar.loyality) - 1;
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_fire_1":	//navy -->			
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();
				break;
			}	//navy <--		
			Diag.TempNode = "Fired_1";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "exit_fire_2":	//navy -->		
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");	
				DialogExit();
				break;
			}	//navy <--	
			Diag.TempNode = "Fired_2";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "exit_fire_3":	//navy -->		
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();
				break;
			}	//navy <--	
			Diag.TempNode = "Fired_3";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "exit_fire_4":	//navy -->		
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");	
				DialogExit();
				break;
			}	//navy <--		
			Diag.TempNode = "Fired_4";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "exit_fire_5":	//navy -->		
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();
				break;
			}	//navy <--	
			Diag.TempNode = "Fired_1";
			OfficersReaction("good");
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "Fired_1":
			Diag.TempNode = "Fired_1";      
			dialog.text = "Cosa adesso?! Abbiamo già parlato di tutto! Mai più metterò piede sulla tua nave.";
			Link.l1 = RandPhraseSimple("Andatevene ora. Non è una grande perdita, dopotutto.","Bene, vai, allora. Non ti tratterrò.");	
			Link.l1.go = "Exit";
		break;

		case "Fired_2":
			Diag.TempNode = "Fired_2"; 
			dialog.text = "Qualcos'altro, capitano? Pensavo avessimo già discusso tutto...";
			Link.l1 = "No, niente. Volevo solo dire addio...";	 
			Link.l1.go = "Exit";
		break;

		case "Fired_3":
			Diag.TempNode = "Fired_3"; 
			dialog.text = "Capitano, abbiamo discusso tutto ed espresso le nostre richieste. Non dirai mica che hai cambiato idea, vero?";
			Link.l1 = "Bene, allora vai. Non è una grande perdita, dopotutto.";	 
			Link.l1.go = "Exit";
		break;

		case "Fired_4":
			Diag.TempNode = "Fired_4"; 
			dialog.text = "Capitano, quali altre domande potrebbero esserci? Solo per dirtelo, sono molto offeso, e non ho alcuna voglia di tornare...";
			Link.l1 = "Bene, vai, allora. Non che avessi bisogno di te così tanto.";	 
			Link.l1.go = "Exit";
		break;
		
		// boal 05.09.03 offecer need to go to abordage -->
	    case "Boal_Stay":
            //SetCharacterTask_Stay(Characters[Npchar.index]); // it's a mistic but here doesn't work :(
            //Log_SetStringToLog(Npchar.id +" "+Npchar.index);
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
		    Diag.TempNode = "Hired";
		    dialog.text = "Si, si Capitano!";
		    Link.l1 = "A vostro agio.";
		    Link.l1.go = "Exit";
		    Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
	    break;
		
	    case "Boal_Follow":
		    SetCharacterTask_FollowCharacter(Npchar, PChar); // it works here!!!
		    Diag.TempNode = "Hired";
		    dialog.text = "Si, si Capitano!";
		    Link.l1 = "All'agio.";
		    Link.l1.go = "Exit";
	    break;
        // boal 05.09.03 offecer need to go to abordage <--

		//////////////////////////////    офицер-наместник -->
		case "Gover_Hire":
            dialog.Text = "Capitano! Sarebbe un onore!";
            Link.l1 = "Mantieni l'ordine e fai prosperare la città, e io verrò a navigare di tanto in tanto per riscuotere le tariffe.";
			Link.l1.go = "Exit_Gover_Hire";
            Link.l2 = "Ho cambiato idea.";
            Link.l2.go = "Exit";
            Diag.TempNode = "Hired";
        break;

        case "Exit_Gover_Hire":
            sld = GetColonyByIndex(sti(NPChar.ColonyIdx));
            attr = sld.id + "_townhall";

            // снимем пассажира -->
			CheckForReleaseOfficer(sti(NPChar.index));
			RemovePassenger(pchar, NPChar);
			// снимем пассажира <--
		    sld.OfficerIdx = sti(NPChar.index);
			ChangeCharacterAddressGroup(NPChar, attr, "sit", "sit1");
			LAi_SetHuberTypeNoGroup(NPChar);
            SaveCurrentNpcQuestDateParam(NPChar, "StartTaxDate");
            SaveCurrentNpcQuestDateParam(NPChar, "GoverTalkDate");
            LAi_LoginInCaptureTown(NPChar, true);
			//  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
            AddQuestRecordInfo("Gen_CityCapture", "t3_1");
			AddQuestUserData("Gen_CityCapture", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + sld.id));
			AddQuestUserData("Gen_CityCapture", "sName", GetFullName(NPChar));
			//  СЖ <--
			Diag.CurrentNode = "Gover_Main";
            DialogExit();
        break;

        case "Gover_Main":
            iTemp = GetNpcQuestPastDayParam(NPChar, "GoverTalkDate");
            if (iTemp > 0)
            {
				dialog.Text = "Quali sono i tuoi ordini? L'ultima volta che mi hai visitato "+FindRussianDaysString(iTemp)+" fa.";
			}
			else
			{
			    dialog.Text = "Quali sono i vostri ordini?";
			}

            Link.l1 = "Quanto denaro delle tasse hai "+NPCharSexPhrase(NPChar,"raccolto","raccolto")+" a questo punto?";
        	Link.l1.go = "Gover_Tax";
            Link.l8 = "Sei necessario sulla nave, ti sollevo dal dovere in città.";
            Link.l8.go = "Gover_Fire";
			Link.l9 = "Tutto il meglio.";
            Link.l9.go = "Exit";
            Diag.TempNode = "Gover_Main";
            SaveCurrentNpcQuestDateParam(NPChar, "GoverTalkDate");
        break;

        case "Gover_Tax":
            iTemp = GetNpcQuestPastDayParam(NPChar, "StartTaxDate");
            iTax  = makeint((GetCharacterSkillSimple(NPChar, SKILL_COMMERCE) + GetCharacterSkillSimple(NPChar, SKILL_LEADERSHIP)) / 2);
            sld = GetColonyByIndex(sti(NPChar.ColonyIdx));
			if (CheckAttribute(sld, "FortValue"))
			{
			    iFortValue = sti(sld.FortValue);
			}
			else
			{
			    iFortValue = 20;
			}
			NPChar.Gover_Tax_Sum = iFortValue*iTax*iTemp;
			dialog.Text = "Le mie abilità permettono di raccogliere "+FindRussianMoneyString(iFortValue*iTax)+" Al giorno. Oltre "+FindRussianDaysString(iTemp)+" Io "+NPCharSexPhrase(NPChar,"raccolto","raccolto")+" "+FindRussianMoneyString(sti(NPChar.Gover_Tax_Sum))+".";
			if (sti(NPChar.Gover_Tax_Sum) > 0)
			{
			    Link.l1 = "Voglio prendere tutti i soldi delle tasse raccolte.";
            	Link.l1.go = "Gover_Tax_Get";
			}
			Link.l2 = "Grazie per il servizio!";
            Link.l2.go = "Exit";
        break;

        case "Gover_Tax_Get":
            SaveCurrentNpcQuestDateParam(NPChar, "StartTaxDate");
            AddMoneyToCharacter(Pchar, sti(NPChar.Gover_Tax_Sum));

			Diag.CurrentNode = "Gover_Main";
            DialogExit();
        break;

        case "Gover_Fire":
            dialog.Text = "Ottimo! Non sono un lubrano di terra, lo sai.";
            Link.l8 = "Questo è buono.";
            Link.l8.go = "exit_hire";
            Diag.TempNode = "Hired";
            sld = GetColonyByIndex(sti(NPChar.ColonyIdx));
            DeleteAttribute(sld, "OfficerIdx");
            //  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
            AddQuestRecordInfo("Gen_CityCapture", "t3_2");
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + sld.id));
			AddQuestUserData("Gen_CityCapture", "sName", GetFullName(NPChar));
			//  СЖ <--
        break;
        //////////////////////////////    офицер-наместник <--

		//Указания для компаньона 19.02.08 -->
		case "Companion_Tasks":
			dialog.Text = "Ti sto ascoltando.";
			Link.l1 = "Questo riguarda l'abbordaggio.";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "Si tratta della tua nave.";
			Link.l2.go = "Companion_TaskChange";
			if(bBettaTestMode) // Только при бета-тесте
			{
			    Link.l3 = "Voglio che tu lasci il mio squadrone per un po' e cerchi fortuna da solo.";
			    Link.l3.go = "CompanionTravel";
			}
			Link.l8 = "Niente fino ad ora.";
			Link.l8.go = "exit";
		break;
		
		case "Companion_TaskBoarding":
			dialog.Text = "Allora qual è il tuo desiderio.";
			Link.l1 = "Non salire sulle navi nemiche. Prenditi cura di te stesso e dell'equipaggio.";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "Voglio che tu salpi sulle navi nemiche.";
			Link.l2.go = "Companion_TaskBoardingYes";
		break;
		
		case "Companion_TaskChange":
			dialog.Text = "Allora qual è il tuo desiderio.";
			Link.l1 = "Vorrei che non scambiassi la tua nave con un'altra dopo l'abbordaggio. È troppo preziosa.";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "Quando stai abbordando le navi nemiche, puoi prenderle per te stesso, se si rivelano decenti.";
			Link.l2.go = "Companion_TaskChangeYes";
		break;
		
		case "Companion_TaskBoardingNo":
			dialog.Text = "Sì-sì Capitano.";
			Link.l1 = "A vostro agio.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
		break;
		
		case "Companion_TaskBoardingYes":
			dialog.Text = "Sarà fatto, Capitano.";
			Link.l1 = "A vostro agio.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
		break;
		
		case "Companion_TaskChangeNo":
			dialog.Text = "Sì-sì Capitano.";
			Link.l1 = "A vostro agio.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;
		
		case "Companion_TaskChangeYes":
			dialog.Text = "Sarà fatto, Capitano.";
			Link.l1 = "A vostro agio.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;
		//<--
	
		// Самостоятельное плавание компаньона -->
		case "CompanionTravel":
			if(GetAttrValue(PChar, "CompanionTravel") == 3) // Если уже троих отпустил
			{
				dialog.Text = "Capitano, non lascerò la tua squadra, perché hai già licenziato tre navi.";
					Link.l1 = "Sì, forse, hai ragione.";
					Link.l1.go = "exit";
				break;
			}
		
			dialog.Text = "Nessun problema, cap. In quale città ci incontreremo?";
			for(iTemp=0; iTemp<MAX_COLONIES; iTemp++)
			{
				sld = &colonies[iTemp];
				attr = sld.ID;
				if(sld.nation == "none" || sld.nation == PIRATE || attr == "Panama" || attr == "FortOrange") continue;
				attrLoc = "l" + iTemp;
				Link.(attrLoc) = "In the " + XI_ConvertString("Colony" + attr + "Dat");
				Link.(attrLoc).go = "CompanionTravelToColony_" + attr;
			}
				Link.l99 = "Ho cambiato idea.";
				Link.l99.go = "exit";
		break;
			
		case "CompanionTravel_EnemyColony":
			dialog.Text = "Capitano, ma non posso aspettarti nella colonia, che è ostile a noi!";
				Link.l1 = "Sai, dimentica tutti questi viaggi...";
				Link.l1.go = "exit";
		break;
			
		case "CompanionTravel_NoCrew":
			dialog.Text = "Capitano, abbiamo quasi nessun marinaio nell'equipaggio! Di che viaggio stai parlando?!";
				Link.l1 = "È vero, ci mancano davvero dei marinai...";
				Link.l1.go = "exit";
		break;
			
		case "CompanionTravel_NoFood":
			dialog.Text = "Capitano, non ho abbastanza provviste a bordo per un viaggio così lungo.";
				Link.l1 = "Sì, hai ragione. Il viaggio può attendere...";
				Link.l1.go = "exit";
		break;
			
		case "CompanionTravel_NoHP":
			dialog.Text = "Capitano, ma la mia nave è in cattive condizioni. Sarebbe imprudente per me salpare da solo in tali circostanze!";
				Link.l1 = "Sì, hai ragione. La tua nave ha bisogno di riparazioni.";
				Link.l1.go = "exit";
		break;
		
		case "CompanionTravel_PrepareStart":
			dialog.Text = "Capisco. Fino a "+XI_ConvertString("Colony"+characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID+"Gen")+" andare "+sti(characters[sti(NPChar.realcompanionidx)].CompanionTravel.Days)+" giorni, cosa faccio al mio arrivo?";
				Link.l1 = "Stai alla larga dal porto della colonia per un mese.";
				Link.l1.go = "CompanionTravel_PrepareStart_2";
				Link.l2 = "Sai, mi è passato per la mente. Rimani con me...";
				Link.l2.go = "exit";
		break;
		
		case "CompanionTravel_PrepareStart_2":
			dialog.Text = "Capisco, capitano. Partirò subito.";
				Link.l1 = "Sì, per favore fallo.";
				Link.l1.go = "CompanionTravel_Start";
		break;
			
		case "CompanionTravel_Start":
			Diag.CurrentNode = "CompanionTravel_LastNode";
			NPChar.quest.meeting = true;
			CompanionTravel_SetTraveller(NPChar);
			DialogExit();
		break;
			
		case "CompanionTravel_LastNode":
			Dialog.text = RandPhraseSimple("Oggi, salperò di nuovo...","Non dimenticare il nostro incontro in "+XI_ConvertString("Colony"+characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID+"Dat")+".");
				link.l2 = "...";
				link.l2.go = "Exit";
				Diag.TempNode = "CompanionTravel_LastNode";
		break;
			
		case "CompanionTravel_ToSquadron":
			if(GetCompanionQuantity(PChar) < COMPANION_MAX)
			{
				dialog.text = "Mi piacerebbe anche a me. D'ora in poi, la mia nave è di nuovo sotto il tuo comando, cap.";
					Link.l1 = "Bene.";
					Link.l1.go = "exit";
					Diag.TempNode = "hired";
					CompanionTravel_DeleteSpecialShipAttributes(NPChar);
					Group_DeleteAtEnd(NPChar.CompanionTravel.GroupID); // Потрем группу
					SetCompanionIndex(PChar, -1, sti(NPChar.index));
					PChar.CompanionTravel = sti(PChar.CompanionTravel) - 1; // Этого компаньона взяли обратно в эскадру
					DeleteAttribute(NPChar, "CompanionTravel");
			}
			else
			{
				dialog.text = "Capitano, hai già cinque navi nella tua squadra - che cosa farai con la sesta? Beh, penso che preferirei aspettarti qui sulla mia nave. I tuoi nuovi compagni non mi sembrano affidabili. Le loro navi affonderanno presto, e tu tornerai a cercarmi.";
					Link.l1 = "Ehi, non sei mica intelligente? Dovresti essere un ammiraglio, non solo un capitano!";
					Link.l1.go = "exit";
					Diag.TempNode = "CompanionTravel_ToSquadron_2";
					NPChar.DeckDialogNode = "CompanionTravel_ToSquadron_2"; // ставим снова эту ноду
			}
		break;
			
		case "CompanionTravel_ToSquadron_2":
			dialog.text = "Oh, capitano, sei tornato, proprio come avevo detto. Quindi, c'è ora un posto vacante nel tuo squadrone?";
			if(GetCompanionQuantity(PChar) < COMPANION_MAX)
			{
				Link.l1 = "Sì, "+NPChar.name+", c'è uno. Benvenuto nella squadra.";
				Link.l1.go = "exit";
				Diag.TempNode = "hired";
				CompanionTravel_DeleteSpecialShipAttributes(NPChar);
				Group_DeleteAtEnd(NPChar.CompanionTravel.GroupID);
				SetCompanionIndex(PChar, -1, sti(NPChar.index));
				PChar.CompanionTravel = sti(PChar.CompanionTravel) - 1; // Этого компаньона взяли обратно в эскадру
				DeleteAttribute(NPChar, "CompanionTravel");
			}
			else
			{
				Link.l1 = "Non ancora, purtroppo.";
				Link.l1.go = "exit";
				Diag.TempNode = "CompanionTravel_ToSquadron_2";
				NPChar.DeckDialogNode = "CompanionTravel_ToSquadron_2";
			}
		break;
		// <-- Самостоятельное плавание компаньона
		
		case "tonzag_after_boarding":
			dialog.text = "Capitano, le cose sono pessime! Il nemico ci ha stretto in un pugno di ferro, temo non ci lasceranno andare finché non saremo morti! I nostri uomini sono in grave pericolo adesso, e la maggior parte delle equipaggi dei cannoni sono fuori gioco!";
			link.l1 = "Li aiuterò. Prendi il comando e portaci via da qui!";
			link.l1.go = "tonzag_after_boarding_1";
			DelLandQuestMark(npchar);
		break;
		
		case "tonzag_after_boarding_1":
			dialog.text = "Sì, signore!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_GoToGunDeck");
		break;
		
		case "tonzag_after_victory":
			dialog.text = "Vittoria, Capitano! Il gruppo di sbarco è stato distrutto, il nemico ha scelto di ritirarsi e si è diretto a sud. Lo stato della nave è accettabile. Equipaggio vivo: "+GetCrewQuantity(pchar)+" persone. Rapporto completato!";
			link.l1 = "Grazie! Rum per tutti e rafforzate la guardia fino a quando non raggiungiamo il porto!";
			link.l1.go = "tonzag_after_victory_1";
		break;
		
		case "tonzag_after_victory_1":
			dialog.text = "Urrà! Aye aye!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_AlonsoBoardingDialog");
		break;
	}
}

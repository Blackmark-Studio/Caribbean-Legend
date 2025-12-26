int iBenuaPseudoGlobal;

// аббат Бенуа
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int rate;
    bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.Sharlie.BenuaLoan.Late")) // Addon 2016-1 Jason пиратская линейка 1
			{
				dialog.text = "Che piacere vederti, figliolo. Sei venuto a saldare il tuo debito?";
				if (PCharDublonsTotal() >= 100 && sti(pchar.money) >= 50000)
				{
					link.l1 = "Sì, padre. Lo sono.";
					link.l1.go = "FastStart_7";
				}
				else
				{
					link.l1 = "Perdona il ritardo, ma non sono qui per questo. Ma ci arriverò presto, non temere.";
					link.l1.go = "exit";
				}
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "benua_final")
			{
				dialog.text = "C'è qualcosa che ti serve, figliolo?";
				link.l1 = "Sì, padre. Vorrei vedere mio fratello, Michel de Monper. Diceva...";
				link.l1.go = "escape";
				break;
			}
			dialog.text = "C'è qualcosa che desideri, figliolo?";
			//--> Эпилог
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Benua"))
			{
				dialog.text = "Salve, figlio mio. Sono felice che tu sia venuto. Volevo parlarti.";
				link.l1 = ""+TimeGreeting()+", padre. Vi ascolto.";
				link.l1.go = "SharlieEpilog_Benua_1";
				DelLandQuestMark(npchar);
				break;
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Benua_back"))
			{
				link.l99 = "Vorrei parlare di mio padre.";
				link.l99.go = "SharlieEpilog_Benua_3";
			}
			//<-- Эпилог
			if (CheckAttribute(pchar, "questTemp.Sharlie.FastStart") && !CheckAttribute(npchar, "quest.FastStart") && !CheckAttribute(npchar, "quest.meet")) // ещё не виделись
			{
				link.l1 = "Sì, padre. Ho bisogno del vostro aiuto. Il mio nome è "+GetFullName(pchar)+"Michel de Monper mi ha consigliato di parlare con te.";
				link.l1.go = "FastStart";
			}
			if (CheckAttribute(npchar, "quest.help") && !CheckAttribute(npchar, "quest.meet")) // ещё не виделись
			{
				link.l1 = "Sì, padre. Ho bisogno del vostro aiuto. Il mio nome è "+GetFullName(pchar)+" Mio fratello, Michel de Monper, mi ha consigliato di parlare con voi.";
				link.l1.go = "meet";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.FastStart") && !CheckAttribute(npchar, "quest.FastStart") && CheckAttribute(npchar, "quest.meet"))
			{
				link.l1 = "Sì, padre. Ho bisogno d'una nave per aiutare Michel, ma son giunto or ora nei Caraibi e la mia borsa è vuota. Mio fratello mi disse che potevi prestarmi qualche moneta...";
				link.l1.go = "FastStart_2";
			}
			if (CheckAttribute(npchar, "quest.help") && CheckAttribute(npchar, "quest.meet"))
			{
				link.l1 = "Sì, padre. Ho bisogno del vostro aiuto.";
				if (CheckAttribute(npchar, "quest.relation_info")) link.l1.go = "help";
				else link.l1.go = "help_start";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.BenuaLoan") && PCharDublonsTotal() >= 100 && sti(pchar.money) >= 50000)
			{
				link.l2 = "Sì, padre. Lo sono.";
				link.l2.go = "FastStart_7";
			}
			link.l9 = "No, niente, padre.";
			link.l9.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "Benua_meeting":
			DelLandQuestMark(npchar);
			if(CheckAttribute(pchar, "questTemp.Sharlie.Citcount"))
				DeleteAttribute(pchar, "questTemp.Sharlie.Citcount");
			DelLandQuestMark(characterFromId("FortFrance_Mayor"));
			dialog.text = "Cosa ti porta da me, figliolo?";
			link.l1 = "Salve, padre. Mi hanno consigliato di parlare con voi. Il mio nome è Charles de Maure. Sto cercando Michel de Monper. Da quel che so, dovrebbe trovarsi da qualche parte su Martinica. Io sono... suo fratello.";
			link.l1.go = "Benua_meeting_1";			
		break;
		
		case "Benua_meeting_1":
			dialog.text = "Fratello di Michel de Monper? De Maure? Che stramberia...";
			link.l1 = "Capisco i tuoi dubbi, padre. Abbiamo semplicemente cognomi diversi. Mio padre è Henri de Monper.";
			link.l1.go = "Benua_meeting_2";			
		break;
		
		case "Benua_meeting_2":
			dialog.text = "A-ah, ora capisco. Conoscevo personalmente Henri de Monper. Vieni, fatti vedere alla luce, giovanotto. Ma sì! Sei sputato lui. Gli stessi lineamenti, la stessa aria nobile! È un piacere accogliere il figlio di Henri de Monper nella nostra parrocchia. \nQuanto alla tua domanda, ti dico che Michel è un ufficiale di alto rango dell’Ordine di Malta, ma... si trova nei guai. Per fortuna, uno dei cavalieri dell’Ordine è qui in visita da me. Credo che potrebbe accettare di accompagnarti dal tuo sfortunato fratello, che il Signore abbia pietà della sua anima...";
			link.l1 = "Chi è quest’uomo, padre santo?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Sharlie_enterMaltie");
			NextDiag.TempNode = "First time";
			npchar.quest.meet = true;		
			if (GetCharacterIndex("SharlieKnown") != -1)
			{
				sld = characterFromId("SharlieKnown");
				sld.lifeday = 0;
			}			
		break;
		
		case "Benua_meeting_3":
			DialogExit();
			NextDiag.CurrentNode = "Benua_meeting_repeat";
			AddQuestRecord("Sharlie", "4");
			pchar.quest.Sharlie_Benua.win_condition.l1 = "Timer";
			pchar.quest.Sharlie_Benua.win_condition.l1.date.hour  = 6;
			pchar.quest.Sharlie_Benua.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Sharlie_Benua.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Sharlie_Benua.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Sharlie_Benua.function = "Sharlie_BenuaMaltie";
		break;
		
		case "Benua_meeting_repeat":
			dialog.text = "Figlio mio, torna domani mattina. Per ora, non ho altro da dirti.";
			link.l1 = "D'accordo.";
			link.l1.go = "exit";	
			NextDiag.TempNode = "Benua_meeting_repeat";
		break;
		
		/* case "Benua_maltie":
			dialog.text = "Ciao, figlio mio. Come promesso, la persona di cui ti parlavo ieri è già qui e ti aspetta. È pronto a condurti da tuo fratello, che, da quel che so, versa in gran miseria. Che il Signore abbia pietà della sua anima...";
			link.l1 = "Chi è quest’uomo, padre santo?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Sharlie_enterMaltie");
			NextDiag.TempNode = "First time";
			npchar.quest.meet = true;
		break; */
		
		case "escape":
			dialog.text = "Sì, Charles, ne sono al corrente. Ma temo di deluderti: Michel qui non c’è.";
			link.l1 = "Come sarebbe a dire che non è qui? Mi aveva detto che mi avrebbe aspettato nella tua chiesa! Padre, che diavolo è successo? Dov’è mio fratello?!";
			link.l1.go = "escape_1";
		break;
		
		case "escape_1":
			dialog.text = "Figliolo, tuo fratello era qui e ha lasciato il mio umile rifugio ieri notte tardi. Dove sia andato, non saprei dirti. Ma ha lasciato questa lettera per te.";
			link.l1 = "Non ci posso credere... dopo tutto quello che ho fatto per lui! Dammi quella lettera!";
			link.l1.go = "escape_2";
		break;
		
		case "escape_2":
			dialog.text = "Non ti infuriare così, Charles. Ecco la lettera. Leggila e poi... poi vorrei parlarti. Ma prima, leggi il messaggio di tuo fratello.";
			link.l1 = "Brucio dall'impazienza!";
			link.l1.go = "escape_3";
		break;
		
		case "escape_3":
			DialogExit();
			GiveItem2Character(pchar, "specialletter");
			ChangeItemDescribe("specialletter", "itmdescr_specialletter_mishelle");
			sld = ItemsFromID("specialletter");
			sld.text = "Letter_Mishelle";
			NextDiag.CurrentNode = "escape_4";
			LocatorReloadEnterDisable("FortFrance_town", "reload91", false); // лесник открыл входы
			LocatorReloadEnterDisable("FortFrance_town", "reload_jail", false);
		break;
		
		case "escape_4":
			if (CheckAttribute(pchar, "GenQuest.specialletter.read") && pchar.GenQuest.specialletter.read == "Letter_Mishelle")
			{
				dialog.text = "Vedo che hai letto la lettera. Ora vorrei dirti una cosa, Charles...";
				link.l1 = "Ma... com’è possibile? Che razza di fandonie sono queste? So che mio fratello è un tipo strambo, ma non è certo un pazzo!";
				link.l1.go = "escape_5";
			}
			else
			{
				dialog.text = "Figlio mio, leggi la lettera. Ne parleremo più tardi.";
				link.l1 = "Sì, padre...";
				link.l1.go = "exit";
				NextDiag.TempNode = "escape_4";
			}
		break;
		
		case "escape_5":
			dialog.text = "Anche a me le azioni di tuo fratello hanno lasciato di stucco, Charles. Mi capita ancora di restare perplesso. Un servitore fedele dell’Ordine e della Trinità... e ora si comporta come un rinnegato.";
			link.l1 = "Hai forse qualche idea sulle ragioni di un comportamento tanto bizzarro?";
			link.l1.go = "escape_6";
		break;
		
		case "escape_6":
			dialog.text = "Ahimè, non ne ho idea. Ma suppongo che abbia le sue ragioni, profonde e oscure. Cancellare tutto il proprio passato... dev’esserci un motivo davvero grave. Non riesco nemmeno a immaginare quale. Ma sento che si tratta di qualcosa di terribile... forse persino orrendo.";
			link.l1 = "Che sarà mai, padre?";
			link.l1.go = "escape_7";
		break;
		
		case "escape_7":
			dialog.text = "Figlio mio, un prete non vede con gli occhi, ma con il cuore. Non riesco a spiegartelo a parole, ma... tuo fratello si è messo su una strada impura, sporca. Mai avrei pensato che la mia bocca dirà questo. Eppure...";
			link.l1 = "Eh, non dubito che mio fratello abbia in mente qualche porcheria. Posso persino intuire cosa stia tramando, più o meno. Questo 'qualcosa' è giallo e fa un bel tintinnio.";
			link.l1.go = "escape_8";
		break;
		
		case "escape_8":
			dialog.text = "Non credo che sia la brama d’oro a muovere tuo fratello. Direi che va cercando qualcosa di ben più grande.";
			link.l1 = "Ho imparato molto da Michel e ho colto la sua filosofia, quindi credo di saper intuire cosa gli sta davvero a cuore e cosa no. Tuttavia terrò a mente le tue preziose parole, padre.";
			link.l1.go = "escape_9";
		break;
		
		case "escape_9":
			dialog.text = "Dio ti benedica, figliolo. Vai, vai ora. Che il Signore vegli su di te!";
			link.l1 = "Grazie, padre. Addio!";
			link.l1.go = "escape_10";
		break;
		
		case "escape_10":
			DialogExit();
			NextDiag.CurrentNode = "first time";
			AddDialogExitQuestFunction("Sharlie_Benua_BrotherEscape");
		break;
		
		// уменьшение награды за голову
		case "meet":
			dialog.text = "Fratello di Michel de Monper? De Maure? Che stramberia...";
			link.l1 = "Capisco i tuoi dubbi, padre. È solo che portiamo cognomi diversi. Mio padre è Henri de Monper.";
			link.l1.go = "meet_1";			
		break;
		
		case "meet_1":
			dialog.text = "A-ah, ora capisco. Conoscevo personalmente Henri de Monper. Vieni alla luce, giovanotto... Ma certo! Gli somigli proprio. Stesso portamento, stesso profilo nobile! Mi rallegra vedere un figlio di Henri de Monper nella nostra parrocchia.\nHo già sentito che Michel è stato visitato da un tale venuto dall’Europa, ma mai avrei pensato fosse suo fratello in carne ed ossa. Spero che tu possa dare una mano a Michel: sta passando un brutto quarto d’ora. Dimmi pure, in che modo posso esserti utile?";
			link.l1 = "Michel mi disse che, se mai mi fossi cacciato nei guai con le autorità, tu saresti stato in grado di aiutarmi.";
			link.l1.go = "help_info";	
			npchar.quest.meet = true;
		break;
		
		case "help_info":
			dialog.text = "Questo è ciò che ti ha detto Michel? Capisco. Ebbene, posso darti una mano in faccende simili. Ho una certa influenza presso la Santa Chiesa Romana e nelle colonie olandesi. Potrei dunque intercedere per te sia presso le autorità spagnole che olandesi. Certo, se le tue malefatte sono troppo gravi, potrò solo smussare un poco la pena.\nPer una piena riconciliazione serviranno più intercessioni. Inoltre, dovrai comunque ungermi il palmo con dobloni d’oro – beneficenza, spese di viaggio e tutto il resto. Ricorda anche che non posso intercedere se non per una nazione alla volta. Se queste condizioni ti stanno bene, non esitare a bussare alla mia porta e vedremo che si può fare.";
			link.l1 = "Grazie! Ne terrò conto.";
			link.l1.go = "exit";
			npchar.quest.relation_info = "true";
		break;
		
		case "help_start":
			dialog.text = "Cosa posso fare per te, figliolo? Parla, t’ascolto.";
			link.l1 = "Michel mi ha detto che saresti in grado di aiutarmi se mai dovessi avere guai con le autorità.";
			link.l1.go = "help_info";
		break;
		
		case "help":
			dialog.text = "In che modo posso esserti d'aiuto, figliolo?";
			//--> Эпилог
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Benua_DublonsLater"))
			{
				link.l1 = "Kehren wir zur Frage der Bezahlung für die Übermittlung der Anweisungen zurück.";
				link.l1.go = "SharlieEpilog_Benua_DublonsLater_2";
			}
			if (CheckAttribute(npchar, "SharlieEpilog_BenuaRazgovor_2"))
			{
				link.l1 = "Ich möchte eine Anweisung senden...";
				link.l1.go = "SharlieEpilog_Benua_Delivery";
			}
			//<-- Эпилог
			if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l1 = "Ho avuto dei guai con le autorità spagnole.";
				link.l1.go = "relation_spa";
			}
			if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l2 = "Ho avuto dei guai con le autorità olandesi.";
				link.l2.go = "relation_hol";
			}
			link.l9 = "Scusate, credo che stavolta me la caverò da solo.";
			link.l9.go = "exit";
		break;
		
		case "relation_spa": // patch-10
			pchar.GenQuest.BenuaNation = SPAIN;
			dialog.text = "Dunque, i nobili signori fremono all’idea di ficcarti nelle segrete dell’Avana...";
			link.l1 = "Proprio così, padre...";
			link.l1.go = "relation";
		break;
		
		case "relation_hol":
			pchar.GenQuest.BenuaNation = HOLLAND;
			dialog.text = "Dunque, i mercanti svegli son tutti impazienti di vederti marcire nelle segrete di Willemstad...";
			link.l1 = "Proprio così, padre...";
			link.l1.go = "relation";
		break;
		
		case "relation":
			rate = wdmGetNationThreat(sti(pchar.GenQuest.BenuaNation));
			iBenuaPseudoGlobal = DiplomatDublonPayment(rate, "Benua", false);
			sTemp = FindRussianDublonString(iBenuaPseudoGlobal);
			if (rate < 2)
			{
				dialog.text = "Sì, anche nella nostra chiesa sono giunte quelle voci. Posso darti una mano con il tuo impiccio, sai. È una faccenda risolvibile. Ma mi serviranno " + sTemp + " d'oro per appianare la tua situazione.";
				if (PCharDublonsTotal() >= iBenuaPseudoGlobal) // Sinistra legendary edition
				{
					link.l1 = "Magnifico! Ecco l’oro.";
					link.l1.go = "agree";
				}
				link.l2 = "Allora è proprio il momento giusto per andare a caccia di dobloni.";
				link.l2.go = "exit";
			}
			else
			{
				if (rate < 4)
				{
					dialog.text = "Sì, le voci delle tue 'prodezze' sono giunte anche alla nostra chiesa. Hai macchiato la tua reputazione, figliolo. Dovresti esser più accorto. Ma posso aiutarti. Mi servono " + sTemp + " d’oro per sistemare la tua brutta faccenda.";
					if (PCharDublonsTotal() >= iBenuaPseudoGlobal) // Sinistra legendary edition
					{
						link.l1 = "Magnifico! Ecco l’oro.";
						link.l1.go = "agree";
					}
					link.l2 = "Allora è proprio il momento giusto per andare a caccia di dobloni.";
					link.l2.go = "exit";
				}
				else
				{
					dialog.text = "Sì, figliolo. Sei disperato quanto tuo fratello... Dev'essere un vizio di famiglia, questo. Non posso raddrizzare del tutto la situazione, ma credo di poter alleviare un poco la tua miseria. E in seguito, se lo vorrai, potremo fare altre offerte. Ora mi servono " + sTemp + " d’oro e mi metterò subito all’opera per sbrigare la tua faccenda.";
					if (PCharDublonsTotal() >= iBenuaPseudoGlobal) // Sinistra legendary edition
					{
						link.l1 = "Magnifico! Ecco l’oro.";
						link.l1.go = "agree";
					}
					link.l2 = "Allora è proprio il momento giusto per andare a caccia di dobloni.";
					link.l2.go = "exit";
				}
			}
		break;
		
		case "agree":
			RemoveDublonsFromPCharTotal(iBenuaPseudoGlobal); // Sinistra legendary edition
			PlaySound("interface\important_item.wav");
			dialog.text = "Ora dovrai aspettare almeno due settimane. Credo che in questo tempo riuscirò a incontrare e parlare con le persone giuste.";
			link.l1 = "Grazie, padre! Attenderò con ansia...";
			link.l1.go = "agree_1";
		break;
		
		case "agree_1":
			DialogExit();
            bOk = HasShipTrait(pchar, "trait23");
            rate = 10 + hrand(5);
            rate = GetIntByCondition(bOk, rate, rate / 2);
			SetFunctionTimerCondition("ChangeNationRelationFromBenuaComplete", 0, 0, rate, false);
			pchar.GenQuest.BenuaNation.Rate = GetDiplomatRate(bOk, sti(pchar.GenQuest.BenuaNation));
			npchar.quest.relation = "true";
		break;
		
		// Addon 2016-1 Jason пиратская линейка 1
		case "FastStart":
			dialog.text = "De Maure? E sei fratello di Michel de Monper? Strano...";
			link.l1 = "Capisco i vostri dubbi, padre. Mio padre è Henri de Monper.";
			link.l1.go = "FastStart_1";			
		break;
		
		case "FastStart_1":
			dialog.text = "Ah-ah, capisco. Henri de Monper lo conoscevo di persona. Vieni, fatti vedere meglio alla luce, giovanotto. Giusto! Gli stessi occhi, lo stesso portamento nobile! Mi rallegra vedere il figlio di Henri de Monper nella mia chiesa. Spero che tu riesca ad aiutare tuo fratello. Gli è capitata una sfilza di sfortune, ultimamente.";
			link.l1 = "Sì, padre. Mi serve una nave per aiutare Michel, ma sono appena sbarcato nei Caraibi e il mio borsellino piange miseria. Michel mi disse che potevi prestarmi qualche scudo...";
			link.l1.go = "FastStart_2";	
			npchar.quest.meet = true;
		break;
		
		case "FastStart_2":
			DelLandQuestMark(npchar);
			dialog.text = "Te l’ha detto Michel?";
			link.l1 = "Padre, forse non sembro il più affidabile, ma è la verità. Più presto avrò una nave, più presto potrò tirar fuori mio fratello dalla galera.";
			link.l1.go = "FastStart_3";
		break;
		
		case "FastStart_3":
			dialog.text = "Capisco, figliolo. Sento che dici la verità. Ebbene, per il bene di Michel e di tuo padre, ti aiuterò. Ho messo via qualche risparmio, prendili pure. Suppongo che 50.000 pesos e 100 dobloni ti basteranno.";
			link.l1 = "Grazie, padre. Quali sono le condizioni?";
			link.l1.go = "FastStart_4";
		break;
		
		case "FastStart_4":
			AddMoneyToCharacter(pchar, 50000);
			TakeNItems(pchar, "gold_dublon", 100);
			dialog.text = "Nessuna fretta. Mezzo anno per restituire il debito basterà.";
			link.l1 = "Molto bene, padre santo. Grazie ancora!";
			link.l1.go = "FastStart_5";
		break;
		
		case "FastStart_5":
			dialog.text = "Va’ con la mia benedizione, figlio mio.";
			link.l1 = "...";
			link.l1.go = "FastStart_6";
		break;
		
		case "FastStart_6":
			DialogExit();
			NextDiag.CurrentNode = "first time";
			npchar.quest.FastStart = "true";
			pchar.questTemp.Sharlie.BenuaLoan = "true";
			SetFunctionTimerCondition("Sharlie_BenuaLoanTime", 0, 0, 180, false);
			AddQuestRecord("Sharlie", "5-2");
		break;
		
		case "FastStart_7":
			dialog.text = "Splendido, figliolo. Spero che quei soldi ti siano stati utili.";
			link.l1 = "Proprio così, grazie di cuore!";
			link.l1.go = "FastStart_8";
		break;
		
		case "FastStart_8":
			DialogExit();
			NextDiag.CurrentNode = "first time";
			AddMoneyToCharacter(pchar, -50000);
			RemoveDublonsFromPCharTotal(100);
			pchar.quest.Sharlie_BenuaLoanTime.over = "yes";
			DeleteAttribute(pchar, "questTemp.Sharlie.BenuaLoan");
			AddQuestRecord("Sharlie", "5-3");
		break;
		
		// Jason Долго и счастливо
		case "LH_abbat":
			dialog.text = "Charles, non posso credere ai miei occhi! Cosa ti porta da queste parti?!";
			link.l1 = "Beneditemi, Padre Santo, ché porto lieto annuncio: mi sposo, e desidererei vedervi quale sacerdote alle mie nozze.";
			link.l1.go = "LH_abbat_1";
		break;
		
		case "LH_abbat_1":
			dialog.text = "Figliolo, che splendida notizia! Hai dunque ricevuto quella lettera da tuo padre e, come sempre, hai deciso di fare di testa tua? Ne sono sinceramente lieto! Ma temo di non poterti aiutare... a meno che tu non voglia sposarti proprio in questa chiesa.";
			link.l1 = "Capisco che la vostra missione si trovi in un vicolo cieco, Padre Santo? Posso esservi utile in qualche modo? Poiché le nozze si terranno in una cappella spagnola, naturalmente, sarebbe un’avventura che mi piacerebbe intraprendere, ma sono deciso a celebrare il matrimonio in Martinica. Con la dovuta magnificenza, alla presenza di testimoni rispettabili e ospiti d’onore.";
			link.l1.go = "LH_abbat_2";
		break;
		
		case "LH_abbat_2":
			dialog.text = "Mi dispiace, figliolo, ma tutta la tua autorità non vale un soldo bucato contro la testardaggine dei più alti gerarchi della Chiesa Cattolica, specialmente nelle colonie spagnole. Non ci siamo messi d'accordo sulla spartizione dell’influenza delle missioni cattoliche tra i nostri paesi, e ora eccomi qui, ospite onorato e, allo stesso tempo, ostaggio d’onore. Gli spagnoli stanno aspettando un’offerta migliore da parte nostra. Ho inviato un messaggio in Europa, speriamo che la risposta arrivi entro due mesi e potremo riprendere le trattative. Se non dovesse arrivare in due mesi, arriverà di certo entro sei mesi.\nE sì, benché il Papa e Mazarino abbiano trovato un compromesso nelle ultime settimane, è ancora presto per parlare di veri rapporti cordiali. Onestamente, non sono sicuro che si giungerà mai a un accordo. Mi pare che Palotti mi tenga semplicemente come pedina nelle sue manovre di potere. Però devo ammettere, l’inquisitore serve un caffè eccellente!";
			link.l1 = "Non ho né sei mesi né due mesi! Devo soddisfare il desiderio di mio padre, altrimenti mi costringerà a sposarmi contro la mia volontà. E la sua salute non è più quella di un tempo, eppure vorrei pur sempre avere modo di presentargli la mia prescelta e futura signora di Monper.";
			link.l1.go = "LH_abbat_3";
		break;
		
		case "LH_abbat_3":
			dialog.text = "Temo che dovrai cercare un altro prete per le tue nozze, figliolo. Ahimè, rimarrò qui a lungo.";
			link.l1 = "Cosa diresti se ti separassi dal caffè dell'inquisitore?";
			link.l1.go = "LH_abbat_4";
		break;
		
		case "LH_abbat_4":
			dialog.text = "Sarei ben lieto di accettare il tuo aiuto. Ho il sospetto che non sia stato scelto per questa missione per pura combinazione. Nel peggiore dei casi, si dimenticheranno semplicemente di padre Benoit. E, sebbene il Signore mi abbia ordinato di sopportare, porto un peso nel mio cuore, nonostante tutte le sue... benedizioni. Ma ripeto – è poco probabile che padre Palotti dia retta alle tue suppliche.";
			link.l1 = "Allora mi risparmierò il fiato e non cercherò di convincerlo oltre. Appena finisce la messa sgattaioliamo fuori dalla chiesa e ci dirigiamo dritti sulla mia nave. Non esiti, Padre Santo – ci hanno visti insieme e mi riconosceranno, e sarà un diavolo di impresa tirarvi fuori dalla residenza del governatore.";
			link.l1.go = "LH_abbat_5";
		break;
		
		case "LH_abbat_5":
			dialog.text = "È rischioso, figliolo, davvero rischioso. Un drappello di guardie mi aspetta fuori per scortarmi alla villa, e la città pullula di soldati.";
			link.l1 = "Andremo con l’elemento sorpresa, Padre Benoit. Devi solo fidarti di me e andrà tutto a gonfie vele. Ho... una certa esperienza in queste faccende.";
			link.l1.go = "LH_abbat_6";
		break;
		
		case "LH_abbat_6":
			dialog.text = "Come desideri. Ma ti prego, fallo senza spargimenti di sangue inutili! Anche io ho avuto esperienze simili... Guidaci, figliolo. Ti seguo a ruota. Ma non impugnerò alcuna arma, quindi non chiedermelo nemmeno.";
			link.l1 = "Non ci ho nemmeno pensato, padre. Ce la faccio io. Seguimi, ma fa' attenzione, potrebbero spararci addosso.";
			link.l1.go = "LH_abbat_7";
		break;
		
		case "LH_abbat_7":
			DialogExit();
			LongHappy_SantiagoBenuaEscape();
		break;
		
		case "LH_abbat_8":
			LocatorReloadEnterDisable("FortFrance_town", "reload1_back", false);
			LocatorReloadEnterDisable("FortFrance_town", "reload2_back", false);
			LocatorReloadEnterDisable("FortFrance_town", "gate_back", false);
			dialog.text = "Figlio mio, non ho avuto modo di ringraziarti per la mia liberazione. Pare che il vescovo spagnolo e l’inquisitore Palotti volessero mettere i bastoni tra le ruote ai rapporti appena intessuti tra il nostro cardinale e la Santa Sede, dunque hai agito pienamente nell’interesse del nostro paese. Ancora una volta. Ma nessuno ti dirà 'grazie', tranne me.";
			link.l1 = "Cosa comune, Padre Santo. Felice d’aver potuto aiutare. Ma devo anche chiedervi una cosa, ve ne ricordate?";
			link.l1.go = "LH_abbat_9";
		break;
		
		case "LH_abbat_9":
			dialog.text = "Ma certo! Dunque, veniamo alle cose piacevoli – Charles, come vanno i preparativi per il tuo giorno più importante?";
			link.l1 = "Sta prendendo forma, pian piano. Ho visto campagne militari messe insieme più in fretta e con meno fatica, ma ne vale la pena!";
			link.l1.go = "LH_abbat_10";
		break;
		
		case "LH_abbat_10":
			dialog.text = "Certo, figlio mio! E, già che ci siamo, vorrei chiarire una cosa – come immagini tu la cerimonia nuziale?";
			link.l1 = "Vuoi dire, quanto sono pieno di me stesso?";
			link.l1.go = "LH_abbat_11";
		break;
		
		case "LH_abbat_11":
			dialog.text = "Ma certo! Devo preparare la chiesa, e magari vorrai invitare qualche pezzo grosso.";
			link.l1 = "Niente di speciale, Padre Santo. Coloro che ritengo nostri amici ci aspetteranno altrove. Qui ci saranno solo pochi funzionari, la mia gente e qualche curioso qualsiasi.";
			link.l1.go = "LH_abbat_12";
		break;
		
		case "LH_abbat_12":
			dialog.text = "Ebbene, credo che ce la caveremo con una piccola donazione.";
			link.l1 = "Non sembra poi così spaventoso. E quanto oro richiede una simile donazione?";
			link.l1.go = "LH_abbat_13";
		break;
		
		case "LH_abbat_13":
			dialog.text = "Per il coro, la messa solenne e le altre spese – centocinquanta, non di più. Più la solita offerta dagli sposi, in tutto – duecento dobloni.";
			if (PCharDublonsTotal() >= 200) // Sinistra legendary edition
			{
				link.l1 = "Ecco a voi, Santo Padre.";
				link.l1.go = "LH_abbat_15";
			}
			else
			{
				link.l1 = "Riguardo a quelle campagne militari... dovrò fare una passeggiata fino alla banca e poi tornare.";
				link.l1.go = "LH_abbat_14";
			}
		break;
		
		case "LH_abbat_14":
			DialogExit();
			npchar.dialog.currentnode = "LH_abbat_14_1";
		break;
		
		case "LH_abbat_14_1":
			dialog.text = "E la tua offerta, figliolo?";
			if (PCharDublonsTotal() >= 200) // Sinistra legendary edition
			{
				link.l1 = "Ecco a voi, Santo Padre.";
				link.l1.go = "LH_abbat_15";
			}
			else
			{
				link.l1 = "Sì, sì, lo porterò presto...";
				link.l1.go = "LH_abbat_14";
			}
		break;
		
		case "LH_abbat_15":
			RemoveDublonsFromPCharTotal(200); // Sinistra legendary edition
			dialog.text = "Resta ancora una questione da risolvere: chi accompagnerà la sposa all’altare e farà da testimone per lei?";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				pchar.questTemp.LongHappy.Pater1 = "Svenson";
				link.l1 = "Jan Svensson, di Blueweld. È inglese, ma uomo rispettato e affezionato a Helen come fosse sua figlia, e la madre adottiva è Gladys McArthur.";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor"))
				{
					pchar.questTemp.LongHappy.Pater1 = "Noel";
					link.l1 = "Barone Noel Forget, son certo che avrà l’onore di ricevermi.";
				}
				else
				{
					pchar.questTemp.LongHappy.Pater1 = "Puancie";
					link.l1 = "Cavaliere Philippe de Poincy, sono certo che mi concederà quest’onore.";
				}
			}
			link.l1.go = "LH_abbat_16";
		break;
		
		case "LH_abbat_16":
			dialog.text = "Ebbene, e chi renderà testimonianza per lo sposo? Rammenta, dev’esser un uomo di nobile lignaggio e d’onorevole reputazione.";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor"))
				{
					link.l1 = "Barone Noel Forget, son certo che mi concederà tale onore.";
					link.l1.go = "LH_abbat_17_1";
				}
				else
				{
					link.l1 = "Cavaliere Philippe de Poincy, son certo che mi farà quest’onore.";
					link.l1.go = "LH_abbat_17_2";
				}
				link.l2 = "Fadey - un mercante rispettabile di Guadalupa. Devo solo rifornirmi del suo liquore preferito.";
				link.l2.go = "LH_abbat_17_3";
			}
			else
			{
				link.l1 = "Fadey – un mercante rispettabile di Guadalupa. Mi basta riempire la stiva del suo liquore preferito.";
				link.l1.go = "LH_abbat_17_3";
			}
		break;
		
		case "LH_abbat_17_1":
			pchar.questTemp.LongHappy.Pater2 = "Noel";
			dialog.text = "Benissimo, manderò gli inviti, ma agli ospiti servirà un po' di tempo per arrivare fin qui. Credo che tutto sarà pronto tra un mese, e le persone indicate saranno già giunte in città.";
			link.l1 = "Bene! Allora ho il tempo di sbrigare un paio di faccende. A presto, Santo Padre, e augurami buona fortuna!";
			link.l1.go = "LH_abbat_18";
		break;
		
		case "LH_abbat_17_2":
			pchar.questTemp.LongHappy.Pater2 = "Puancie";
			dialog.text = "Perfetto, manderò gli inviti, ma gli ospiti avranno bisogno di tempo per arrivare. Credo che tutto sarà pronto fra un mese, e le persone indicate saranno giunte in città.";
			link.l1 = "Bene! Allora ho tempo per sbrigare un paio di faccende. A presto, Reverendo Padre, e augurami buona fortuna!";
			link.l1.go = "LH_abbat_18";
		break;
		
		case "LH_abbat_17_3":
			pchar.questTemp.LongHappy.Pater2 = "Fadey";
			dialog.text = "Benissimo, manderò subito gli inviti, ma agli ospiti servirà un po’ di tempo per arrivare. Penso che fra un mese tutto sarà pronto e le persone indicate saranno già giunte in città.";
			link.l1 = "Bene! Allora ho tempo per sbrigare un paio di faccende. A presto, Santo Padre, e augurami buona fortuna!";
			link.l1.go = "LH_abbat_18";
		break;
		
		case "LH_abbat_18":
			DialogExit();
			AddQuestRecord("LongHappy", "11");
			SetFunctionTimerCondition("LongHappy_SenPierreGuests", 0, 0, 31, false); // таймер
			if (!CheckAttribute(pchar, "questTemp.LongHappy.MarryRum"))
			{
			pchar.questTemp.LongHappy = "toIslaTesoro";
			LocatorReloadEnterDisable("Pirates_town", "reload4_back", true);//закрыть таверну Исла-Тесоро
			}
			npchar.dialog.currentnode = "First time";
		break;
		
		case "LH_abbat_19":
			dialog.text = "Dunque, è giunto il giorno, figliolo! Tutto è pronto – tra un paio d’ore potremo salpare. Hai una faccia da morto!";
			link.l1 = "Sono un po' in ansia, Reverendo Padre.";
			link.l1.go = "LH_abbat_20";
		break;
		
		case "LH_abbat_20":
			dialog.text = "Succede spesso. Questo è il giorno più importante della tua vita, e sono sinceramente lieto per te, come tutti gli altri qui presenti. Spero che almeno tu ricordi le preghiere fondamentali – non hai mai dato troppa attenzione alla chiesa, vero? Ad ogni modo, ti aiuterò comunque.\nE ancora una cosa – se ho capito bene, la sposa non intende rinunciare ai suoi principi e non la vedremo in abito? Beh, l’alta società avrà un’altra sorpresa da parte tua – ne hai sempre una pronta. Ora vai, figliolo, renditi presentabile e daremo inizio.";
			link.l1 = "Sì, Santo Padre. Procediamo.";
			link.l1.go = "LH_abbat_21";
		break;
		
		case "LH_abbat_21":
			DialogExit();
			chrDisableReloadToLocation = true;
			WaitDate("", 0, 0, 0, 2, 0);
			DoQuestReloadToLocation("FortFrance_church", "reload", "reload1", "LongHappy_MarryInit");
		break;
		
		case "LH_abbat_22":
			pchar.questTemp.LongHappy.Mistake = 0;
			dialog.text = "Pater noster, che sei nei cieli, sia santificato il tuo nome, ad...";
			link.l1 = "...adveniat regnum tuum";
			link.l1.go = "LH_abbat_23_1";
			link.l2 = "...requiem aeternam dona eis";
			link.l2.go = "LH_abbat_23_2";
		break;
		
		case "LH_abbat_23_1":
			dialog.text = "...fiat voluntas tua, sicut in caelo et in terra. Dacci oggi il nostro pane quotidiano, e rimetti a noi i nostri debiti se...";
			link.l1 = "...come anche noi rimettiamo ai nostri debitori";
			link.l1.go = "LH_abbat_24_1";
			link.l2 = "...come era in principio, ora e sempre, nei secoli dei secoli. Amen";
			link.l2.go = "LH_abbat_24_2";
		break;
		
		case "LH_abbat_23_2":
			pchar.questTemp.LongHappy.Mistake = sti(pchar.questTemp.LongHappy.Mistake)+1;
			dialog.text = "E-e... Mh...";
			link.l1 = "";
			link.l1.go = "LH_abbat_23_1";
		break;
		
		case "LH_abbat_24_2":
			pchar.questTemp.LongHappy.Mistake = sti(pchar.questTemp.LongHappy.Mistake)+1;
			dialog.text = "E-e... Mh...";
			link.l1 = "";
			link.l1.go = "LH_abbat_24_1";
		break;
		
		case "LH_abbat_24_1":
			dialog.text = "et ne nos inducas in tentationem; sed libera nos a malo. Amen.";
			link.l1 = "Amen.";
			link.l1.go = "LH_abbat_25";
		break;
		
		case "LH_abbat_25":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Amatissimi, siam qui radunati innanzi a Dio, e al cospetto di questa compagnia, per unire quest’uomo e questa donna in sacro Matrimonio. Cari "+sld.name+" e Charles, tu hai prestato ascolto alla parola di Dio, che ti ha rammentato il senso dell’amor umano e del sacro vincolo del matrimonio. Ora, a nome della Santa Chiesa, desidero mettere alla prova le tue intenzioni.\n"+sld.name+" e Charles, hai tu il desiderio sincero e volontario di unirti in matrimonio al cospetto del nostro Signore?";
			link.l1 = "Sì.";
			link.l1.go = "LH_abbat_26";
		break;
		
		case "LH_abbat_26":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_27":
			dialog.text = "Avete intenzione di restarvi fedeli nella salute e nella malattia, nella gioia e nella sventura, finché morte non vi separi?";
			link.l1 = "Sì.";
			link.l1.go = "LH_abbat_28";
		break;
		
		case "LH_abbat_28":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_22";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_29":
			dialog.text = "Hai intenzione di amare e accogliere i figli che il Signore vorrà donarti, e crescerli secondo la fede cristiana?";
			link.l1 = "Sì.";
			link.l1.go = "LH_abbat_30";
		break;
		
		case "LH_abbat_30":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_24";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_31":
			dialog.text = "Ebbene, voltatevi l’uno verso l’altro e fate un giuramento.";
			link.l1 = "";
			link.l1.go = "LH_abbat_32";
		break;
		
		case "LH_abbat_32":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_26";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_33":
			dialog.text = "Se qualcuno qui presente conosce una ragione per cui questa coppia non debba essere unita in sacro matrimonio, parli ora o taccia per sempre.\nIn tal caso, davanti al Signore e a tutta la compagnia radunata, vi dichiaro marito e moglie! In nomine Patris, et Filii, et Spiritus Sancti. Amen.";
			link.l1 = "Amen.";
			link.l1.go = "LH_abbat_34";
		break;
		
		case "LH_abbat_34":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_29";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_35":
			string sTemp;
			if (sti(pchar.questTemp.LongHappy.Mistake) > 1) sTemp = "(Whispering) Charles, my son, just move your lips, I beg you - don't try to make any sound...";
			else sTemp = "";
			dialog.text = "Novelli sposi, inginocchiatevi e pregate insieme. Oratio fidelium."+sTemp+"";
			link.l1 = "";
			link.l1.go = "LH_abbat_36";
		break;
		
		case "LH_abbat_36":
			DialogExit();
			SetLaunchFrameFormParam("Some time has passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.lastname = "de Maure";
			sld.SpecialRole = "wife";
			sld.dialog.currentnode = "LongHappy_31";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 4.0);
		break;
		
		case "LH_abbat_37":
			dialog.text = "Le mie congratulazioni, figliolo. Tuo padre può andarne fiero, e io lo sono altrettanto. Siate felici e sostenetevi l'un l'altro in questi tempi travagliati.";
			link.l1 = "Vi ringrazio, Santo Padre. È stata una funzione meravigliosa e sono lieto che sia stato proprio voi a celebrarla.";
			link.l1.go = "LH_abbat_38";
		break;
		
		//--> Дикая Роза
		case "WildRose_Abb_2":
			dialog.text = "Quindi siete venuti da me per un consiglio, figli miei? Bene, vi ascolto.";
			link.l1 = "Piuttosto per un aiuto, padre. L’aiuto di un uomo con contatti e conoscenze tra le più disparate persone...";
			link.l1.go = "WildRose_Abb_3";
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.WildRose_Etap3_Benua");
		break;

		case "WildRose_Abb_3":
			dialog.text = "Perdonami se ti interrompo, figlio mio, ma voglio ricordarti che sono solo un semplice abate, non un agente segreto.";
			link.l1 = "Ma un semplice abate può conoscere un agente segreto, giusto? Oppure suggerire come trovarne uno?";
			link.l1.go = "WildRose_Abb_4_fortune";
			link.l2 = "La questione che ci ha portati da voi riguarda davvero dei misteri dimenticati... E noi cerchiamo di riportarli alla luce.";
			link.l2.go = "WildRose_Abb_4_stealth";
		break;

		case "WildRose_Abb_4_fortune":
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			dialog.text = "Giovanotto, questa storia inizia a non piacermi. Vai dritto al punto, poi vedremo se posso aiutarti... e se voglio.";
			link.l1 = "Sì, padre. Cercherò di spiegare tutto brevemente...";
			link.l1.go = "WildRose_Abb_5";
		break;

		case "WildRose_Abb_4_stealth":
			AddCharacterExpToSkill(pchar, "Sneak", 100);
			dialog.text = ""+pchar.name+", non parlare per enigmi — confesso che mi stanca.";
			link.l1 = "Sì, padre. Cercherò di spiegare tutto brevemente...";
			link.l1.go = "WildRose_Abb_5";
		break;

		case "WildRose_Abb_5":
			dialog.text = "Continua, figlio mio.";
			link.l1 = "La mia compagna, Mary Kasper, sta cercando suo padre — o almeno qualche informazione su di lui. Abbiamo scoperto che era un ufficiale della marina inglese e che prestava servizio sul brigantino 'Wrangler', naufragato presso Capo Catoche nel 1638.";
			link.l1.go = "WildRose_Abb_6";
		break;

		case "WildRose_Abb_6":
			dialog.text = "E sperate che sia ancora vivo? Dopo tutti questi anni?";
			link.l1 = "Anche se non è sopravvissuto al naufragio, Mary vuole sapere da dove veniva suo padre, che uomo fosse, che vita ha vissuto... I documenti ufficiali sono poveri di dettagli — ma anche in essi può nascondersi qualcosa di prezioso, non è vero, padre?";
			link.l1.go = "WildRose_Abb_7";
		break;

		case "WildRose_Abb_7":
			dialog.text = "Hai certamente ragione, figlio mio. È una missione nobile e gradita a Dio. Ma ancora non comprendo esattamente cosa desideriate da me.";
			link.l1 = "Vivete da molto tempo nell’Arcipelago, padre. Forse conoscete qualcuno con accesso agli archivi coloniali contenenti informazioni sugli ufficiali della marina inglese?";
			link.l1.go = "WildRose_Abb_8_stealth";
			link.l2 = "Ci serve una persona con accesso agli archivi coloniali dove sono conservati i dati sugli ufficiali della marina inglese. Sicuramente conoscete qualcuno, padre.";
			link.l2.go = "WildRose_Abb_8_charisma";
		break;

		case "WildRose_Abb_8_stealth":
			AddCharacterExpToSkill(pchar, "Sneak", 100);
			dialog.text = "Capisci cosa stai chiedendo, figlio mio? Non si tratta solo del fatto che tali informazioni potrebbero essere segrete...";
			link.l1 = "E di cosa si tratta, allora, padre? Te lo dirò subito...";
			link.l1.go = "WildRose_Abb_9";
		break;

		case "WildRose_Abb_8_charisma":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			dialog.text = "Capisci cosa stai chiedendo, figlio mio? Non si tratta solo del fatto che tali informazioni potrebbero essere segrete...";
			link.l1 = "E di cosa si tratta, allora, padre? Te lo dirò subito...";
			link.l1.go = "WildRose_Abb_9";
		break;

		case "WildRose_Abb_9":
			dialog.text = "Il problema riguarda proprio quegli archivi coloniali. Vent’anni fa, la Giamaica era sotto controllo spagnolo, e Saint John e Bridgetown erano sotto minaccia costante di razzie. Difficile credere che vi fossero registrate navi della Marina Reale...";
			link.l1 = "State parlando dell’archivio dell’Ammiragliato a Londra, padre?";
			link.l1.go = "WildRose_Abb_10";
		break;

		case "WildRose_Abb_10":
			dialog.text = "È possibile. I documenti dovrebbero essere stati trasferiti all’Ammiragliato. Ottenere l’accesso non è facile.";
			link.l1 = "Ma è possibile, vero, padre?";
			link.l1.go = "WildRose_Abb_11";
		break;

		case "WildRose_Abb_11":
			dialog.text = "Nulla è impossibile, figlio mio. Ma richiederà sforzi... e denaro.";
			link.l1 = "Naturalmente, padre. Devo darvi i soldi, o incontrare qualcun altro?";
			link.l1.go = "WildRose_Abb_12";
		break;
		
		case "WildRose_Abb_12":
			dialog.text = "Mi incontrerò personalmente con qualcun altro, figlio mio. Da te mi servono... ottocento dobloni.";
			link.l1 = "Va bene, padre. Quanto tempo ci vorrà?";
			link.l1.go = "WildRose_Abb_13";
		break;

		case "WildRose_Abb_13":
			dialog.text = "Direi due mesi. E, tra l’altro, non mi hai ancora detto il nome della persona che cercate.";
			link.l1 = "Si chiama Joshua Kasper.";
			link.l1.go = "WildRose_Abb_14";
		break;

		case "WildRose_Abb_14":
			dialog.text = "Ricorderò. Se sei pronto a consegnare l’intera somma adesso — già domani manderò un messaggio.";
			if (PCharDublonsTotal() >= 800)
			{
				link.l1 = "Naturalmente, padre. Ecco qui. Ottocento dobloni d’oro.";
				link.l1.go = "WildRose_Abb_14_pay";
			}
			link.l2 = "No, padre, non ho con me quella somma. Ma tornerò presto e li porterò.";
			link.l2.go = "WildRose_Abb_14_nopay";
		break;

		case "WildRose_Abb_14_pay":
			RemoveDublonsFromPCharTotal(800);
			dialog.text = "Molto bene, "+pchar.name+". Tornate tra due mesi — sono certo che per allora avrò qualche risposta per voi.";
			link.l1 = "Grazie, padre. A presto!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			AddDialogExitQuestFunction("WildRose_Etap3_Paperwork_1");
			DeleteAttribute(pchar, "questTemp.WildRose_Etap3_Benua_2");
		break;

		case "WildRose_Abb_14_nopay":
			dialog.text = "Come desideri, figlio mio.";
			link.l1 = "Tornerò presto.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			pchar.questTemp.WildRose_Etap3_Benua_2 = true;
		break;
		
		case "WildRose_Abb_16":
			dialog.text = "Ha scoperto sia di Joshua Kasper che della sua nave — che, però, non era affatto il 'Wrangler'. Un brigantino con quel nome non ha mai fatto parte della Marina Reale.";
			link.l1 = "Hmm... Sono assolutamente certo che la nave su cui serviva Joshua Kasper si chiamava proprio così... E riguardo a Joshua stesso?";
			link.l1.go = "WildRose_Abb_17";
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.WildRose_Etap3_Benua_3");
		break;
		
				case "WildRose_Abb_17":
			dialog.text = "Quest’uomo era un eccellente ufficiale, con numerosi meriti e onorificenze — tutto documentato nel suo fascicolo personale. Pur non appartenendo alla vera fede, fu un capitano degno. Mademoiselle può essere orgogliosa delle sue origini.";
			link.l1 = "Una buona notizia, padre. Ma se permette, torniamo alla nave. Se non si chiamava 'Wrangler', allora come si chiamava?";
			link.l1.go = "WildRose_Abb_19";
			AddQuestRecordInfo("WildRose_Records_3", "1");
		break;

		case "WildRose_Abb_19":
			dialog.text = "'Cornwall'. Salpò da Plymouth nel gennaio del 1638 con l’ordine di consegnare la paga alle guarnigioni di Antigua e Providence.";
			link.l1 = "Incredibile...";
			link.l1.go = "WildRose_Abb_20";
			AddQuestRecordInfo("WildRose_Records_4", "1");
		break;

		case "WildRose_Abb_20":
			dialog.text = "Se sia arrivata alla destinazione finale non lo so. Ma attraccò a Saint John's. All’amministrazione portuale si conserva un rapporto del capitano Kasper datato 2 giugno di quell’anno.";
			link.l1 = "Sapevo che non siete così semplice come sembrate, padre! Quel documento, immagino, contiene informazioni importanti?";
			link.l1.go = "WildRose_Abb_21_charisma";
			link.l2 = "Vi siamo debitori, padre. Se avete menzionato quel documento, vuol dire che contiene qualcosa di rilevante?";
			link.l2.go = "WildRose_Abb_21_honor";
			AddQuestRecordInfo("WildRose_Records_5", "1");
		break;

		case "WildRose_Abb_21_charisma":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			dialog.text = "Solo il resoconto di uno scontro con il galeone spagnolo 'Toro' presso le Azzorre, dove un terzo dell’equipaggio perse la vita — leggi il rapporto, c’è tutto scritto lì.";
			link.l1 = "Un’altra domanda: se siete riuscito a consultare i registri del porto di Antigua, vi è mai capitato di vedere di nuovo il nome di Joshua Kasper?";
			link.l1.go = "WildRose_Abb_22";
		break;

		case "WildRose_Abb_21_honor":
			AddComplexSelfExpToScill(100, 100, 100, 100);
			dialog.text = "Solo il resoconto di uno scontro con il galeone spagnolo 'Toro' presso le Azzorre, dove un terzo dell’equipaggio perse la vita — leggi il rapporto, c’è tutto scritto lì.";
			link.l1 = "Un’altra domanda: se siete riuscito a consultare i registri del porto di Antigua, vi è mai capitato di vedere di nuovo il nome di Joshua Kasper?";
			link.l1.go = "WildRose_Abb_22";
		break;

		case "WildRose_Abb_22":
			dialog.text = "Mi chiedi molto, figlio mio. Se stai insinuando che possa essere sopravvissuto al naufragio e tornato in servizio — ne dubito fortemente.";
			link.l1 = "Le vie del Signore sono imperscrutabili, padre.";
			link.l1.go = "WildRose_Abb_23";
		break;

		case "WildRose_Abb_23":
			dialog.text = "In verità, figlio mio. Ma vedi, nel suo fascicolo è scritto che Joshua Kasper nacque nel 1586...";
			link.l1 = "Forse avete ragione, padre.";
			link.l1.go = "WildRose_Abb_24_fortune";
			link.l2 = "Sapete, padre, vivendo nei Caraibi ho visto cose così assurde da credere perfino all’impossibile.";
			link.l2.go = "WildRose_Abb_24_charisma";
		break;

		case "WildRose_Abb_24_fortune":
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			dialog.text = "Senza dubbio, un ufficiale del genere meritava di morire in battaglia. Ma se vogliamo essere filosofici, anche quella fu una battaglia, in un certo senso...";
			link.l1 = "Non sono molto ferrato in filosofia, padre. Ma grazie di tutto...";
			link.l1.go = "WildRose_Abb_25";
		break;

		case "WildRose_Abb_24_charisma":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			dialog.text = "Senza dubbio, un ufficiale del genere meritava di morire in battaglia. Ma se vogliamo essere filosofici, anche quella fu una battaglia, in un certo senso...";
			link.l1 = "Non sono molto ferrato in filosofia, padre. Ma grazie di tutto...";
			link.l1.go = "WildRose_Abb_25";
		break;

		case "WildRose_Abb_25":
			dialog.text = "È il Signore che vi guida in questo cammino, figli miei, ed è mio dovere assistervi come posso. Ma temo di non poter fare più nulla in questa faccenda...";
			link.l1 = "Capisco, padre. Allora permetteteci di congedarci.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			AddDialogExitQuestFunction("WildRose_Etap3_Paperwork_5");
		break;
		//<-- Дикая Роза
		
		//--> Эпилог
		case "SharlieEpilog_Benua_1":
			dialog.text = "Sono profondamente preoccupato per le condizioni di tuo padre. Non so se te ne abbia parlato nella sua lettera, ma nel messaggio che ha inviato a me ha confessato che le forze fisiche lo stanno abbandonando e che teme di non avere ancora molto tempo.";
			link.l1 = "Ha accennato al fatto che il male non lo lascia... Ma, a quanto pare, ha taciuto le sue paure.";
			link.l1.go = "SharlieEpilog_Benua_2";
			DeleteAttribute(pchar, "questTemp.SharlieEpilog_Benua");
		break;

		case "SharlieEpilog_Benua_2":
			dialog.text = "Non posso dirti altro: questo è tutto ciò che mi ha riferito. Ma una cosa è chiara: teme di presentarsi davanti al Signore senza averti rivisto ancora una volta.";
			link.l1 = "Ne parlava. A dire il vero, anch’io avevo pensato di fargli visita... Ma...";
			link.l1.go = "SharlieEpilog_Benua_3";
		break;

		case "SharlieEpilog_Benua_3":
			if (!CheckAttribute(npchar, "SharlieEpilog_BenuaRazgovor_1"))
			{
				dialog.text = "Figlio mio, solo il Signore sa quanto tempo è concesso a ciascuno di noi. Non rimandare l’incontro: talvolta un solo abbraccio può donare all’anima una pace che nemmeno mille preghiere sanno dare.";
				npchar.SharlieEpilog_BenuaRazgovor_1 = true;
			}
			else
			{
				dialog.text = ""+pchar.name+", spero che tu non voglia rimandare ancora la visita a tuo padre. Ricorda che il tempo gioca contro di te...";
			}
			link.l1 = "Avete ragione, abate. Inizierò immediatamente i preparativi per la partenza. Considerata la posizione che ricopro ora, potrebbe volerci parecchio tempo per sistemare ogni cosa...";
			link.l1.go = "SharlieEpilog_Benua_5";
			link.l2 = "Comprendo le vostre preoccupazioni, santo padre, e prometto di rifletterci. Ma in questo momento ho questioni molto importanti che non ammettono rinvii. Torneremo su questo argomento più tardi.";
			link.l2.go = "SharlieEpilog_Benua_4_exit";
		break;
		
		case "SharlieEpilog_Benua_4_exit":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_DlgExit_2");
		break;
		
		case "SharlieEpilog_Benua_5":
			dialog.text = "Se hai dei debiti, figlio mio, ti consiglierei di iniziare saldandoli. Gli usurai sono persone vendicative: possono arrecare gravi danni alla tua reputazione e, con essa, al buon nome dell’intera famiglia, persino nel Vecchio Mondo\n"+
			"Per il resto — in nome della mia amicizia con tuo padre e a gloria del Signore — ti offrirò tutto l’aiuto possibile. Potrai impartire per iscritto le disposizioni necessarie, e mi assicurerò che giungano ai destinatari in tempo. Dovrai solo coprire le spese dei corrieri. Ritengo che duecento dobloni saranno sufficienti per la consegna di tutte le missive.";
			if (PCharDublonsTotal() >= 200)
			{
				link.l1 = "Vi ringrazio, santo padre. Il vostro aiuto mi sarà di grande utilità. Ecco, prendete.";
				link.l1.go = "SharlieEpilog_Benua_6";
			}
			link.l2 = "Vi ringrazio per l’interessamento, santo padre. Purtroppo, al momento non dispongo della somma necessaria. Torneremo su questa questione più avanti.";
			link.l2.go = "SharlieEpilog_Benua_DublonsLater";
			SharlieEpilog_Benua_Dlg_1();
		break;
		
		case "SharlieEpilog_Benua_DublonsLater":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_DlgExit_3");
		break;
		
		case "SharlieEpilog_Benua_DublonsLater_2":
			dialog.text = "Certamente, "+pchar.name+". Suppongo che tu abbia portato i duecento dobloni?";
			if (PCharDublonsTotal() >= 200)
			{
				link.l1 = "Naturalmente. Ecco, prendete.";
				link.l1.go = "SharlieEpilog_Benua_6";
			}
			link.l2 = "Purtroppo non ho ancora la somma necessaria.";
			link.l2.go = "exit";
		break;
		
		case "SharlieEpilog_Benua_6":
			dialog.text = "Eccellente, figlio mio.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
			RemoveDublonsFromPCharTotal(200);
			DeleteAttribute(pchar, "questTemp.SharlieEpilog_Benua_DublonsLater");
		break;
		
		case "SharlieEpilog_Benua_Delivery":
			if (!CheckAttribute(npchar, "SharlieEpilog_BenuaRazgovor_2"))
			{
				dialog.text = "Allora, da dove preferisci iniziare?";
				npchar.SharlieEpilog_BenuaRazgovor_2 = true;
			}
			else
			{
				dialog.text = "Chi desideri informare, e su quale questione?";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Plantation") && !CheckAttribute(pchar, "questTemp.SharlieEpilog_IslaMona"))
			{
				link.l1 = "Un giorno ho scoperto un'isola che non compare sulle mappe. Vi abitavano già alcuni coloni, di cui mi sono preso cura. Ora che me ne vado, avranno bisogno di un nuovo 'governatore'.";
				link.l1.go = "SharlieEpilog_Benua_IslaMona";
			}
			if (CheckAttribute(pchar, "questTemp.LongHappy.Baron") && !CheckAttribute(pchar, "questTemp.SharlieEpilog_Baron"))
			{
				link.l2 = "Vorrei inviare una lettera a Marcus Tirax a La Vega. Non è una questione urgente, ma la lettera deve essere recapitata in tempo.";
				link.l2.go = "SharlieEpilog_Benua_Baron";
			}
			if (CheckCharacterItem(PChar, "patent_fra") && !CheckAttribute(pchar, "questTemp.SharlieEpilog_Patent"))
			{
				link.l3 = "Sono in possesso di una patente francese attiva: desidero informare la cancelleria di Capsterville della mia decisione.";
				link.l3.go = "SharlieEpilog_Benua_Patent";
			}
			if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_Money"))
			{
				link.l4 = "Santo padre, negli anni trascorsi in queste terre ho accumulato una discreta fortuna. Ma prima che diventi patrimonio della mia famiglia, vorrei purificarla. Lavare via il sangue con cui, forse, è stata ottenuta. Voglio lasciare queste terre non come un predone col bottino, ma come un uomo la cui coscienza e reputazione siano pulite agli occhi della società.";
				link.l4.go = "SharlieEpilog_Benua_Money";
			}
			if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_Svenson") && CheckAttribute(pchar, "questTemp.SharlieEpilog_IslaMona_France"))
			{
				link.l5 = "Vorrei informare Jan Svenson di Blueveld della mia partenza. Sarebbe scortese lasciare l’arcipelago senza avvisarlo.";
				link.l5.go = "SharlieEpilog_Benua_Svenson";
			}
			if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_Houk"))
			{
				link.l6 = "Desidero informare la famiglia Houk di Maroon Town del mio viaggio.";
				link.l6.go = "SharlieEpilog_Benua_Houk";
			}
			if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_Jino"))
			{
				link.l7 = "Vorrei notificare a Gino Guinelli di Saint John's la mia partenza per il Vecchio Mondo.";
				link.l7.go = "SharlieEpilog_Benua_Jino";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_gold_S") || CheckAttribute(pchar, "questTemp.SharlieEpilog_gold_M") || CheckAttribute(pchar, "questTemp.SharlieEpilog_gold_L"))
			{
				link.l85 = "È tutto, padre... Sembra che io sia pronto a partire.";
				link.l85.go = "SharlieEpilog_Benua_TimeToGoHome";
			}
			link.l99 = "Mi scusi, santo padre, ma ora devo andare.";
			link.l99.go = "SharlieEpilog_exit";
		break;
		
		case "SharlieEpilog_exit":
			DialogExit();
			LAi_SetStayType(npchar);
			NextDiag.CurrentNode = "First time";
		break;
		
		case "SharlieEpilog_Benua_Jino":
			dialog.text = "Certamente, figlio mio.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Jino_2";
			pchar.questTemp.SharlieEpilog_Jino = true;
		break;
		
		case "SharlieEpilog_Benua_Jino_2":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Jino_3";
			AddQuestRecord("SharlieEpilog", "8_1");
		break;
		
		case "SharlieEpilog_Benua_Jino_3":
			dialog.text = "...";
			link.l1 = "Fatto. Può essere spedita.";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;
		
		case "SharlieEpilog_Benua_Houk":
			dialog.text = "Certamente, figlio mio.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Houk_2";
			pchar.questTemp.SharlieEpilog_Houk = true;
		break;
		
		case "SharlieEpilog_Benua_Houk_2":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Houk_3";
			AddQuestRecord("SharlieEpilog", "8");
		break;
		
		case "SharlieEpilog_Benua_Houk_3":
			dialog.text = "...";
			link.l1 = "Fatto. Può essere spedita.";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;
		
		case "SharlieEpilog_Benua_Svenson":
			dialog.text = "Jan Svenson di Blueweld... Me ne ricorderò. Dammi la lettera: partirà oggi stesso.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Svenson_2";
			pchar.questTemp.SharlieEpilog_Svenson = true;
		break;
		
		case "SharlieEpilog_Benua_Svenson_2":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Svenson_3";
			AddQuestRecord("SharlieEpilog", "7");
		break;
		
		case "SharlieEpilog_Benua_Svenson_3":
			dialog.text = "...";
			link.l1 = "Trovare la casa di Jan non è difficile. Basta chiedere a qualunque abitante: difficilmente a Blueweld c’è qualcuno che non sappia chi sia e dove viva.";
			link.l1.go = "SharlieEpilog_Benua_Svenson_4";
		break;
		
		case "SharlieEpilog_Benua_Svenson_4":
			dialog.text = "Non preoccuparti, figlio mio: la nostra gente sa fare il proprio mestiere. La lettera giungerà al destinatario giusto e nei tempi stabiliti.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;
		
		case "SharlieEpilog_Benua_Money":
			dialog.text = "Vuoi che la Chiesa benedica l’oro ottenuto con mezzi criminali?";
			link.l1 = "Piuttosto, ottenuto al servizio della Francia e di Sua Maestà.";
			link.l1.go = "SharlieEpilog_Benua_Money_2";
		break;
		
		case "SharlieEpilog_Benua_Money_2":
			dialog.text = "Ti capisco, figlio mio. Potrei dirti che la Chiesa non purifica il denaro e non cancella il modo in cui è stato ottenuto. Ma a che servirebbe, se i poveri continuassero a soffrire la fame, i senzatetto a dormire per strada e i malati a morire senza aiuto? Sono disposto a concedere la mia benedizione, in cambio del fatto che una piccola parte di queste ricchezze non serva te, ma coloro che hanno bisogno di aiuto.";
			link.l1 = "Naturalmente, santo padre, sono pronto a donare quanto riterrete opportuno.";
			link.l1.go = "SharlieEpilog_Benua_Money_3";
		break;
		
		case "SharlieEpilog_Benua_Money_3":
			dialog.text = "Dunque, quale somma desideri portare con te?";
			link.l1 = "Dieci milioni di pesos.";
			link.l1.go = "SharlieEpilog_Benua_Money_4";
			if (sti(pchar.Money) >= 250000)
			{
				link.l2 = "Venticinque milioni di pesos.";
				link.l2.go = "SharlieEpilog_Benua_Money_5";
			}
			if (sti(pchar.Money) >= 500000)
			{
				link.l3 = "Cinquanta milioni di pesos.";
				link.l3.go = "SharlieEpilog_Benua_Money_6";
			}
		break;
		
		case "SharlieEpilog_Benua_Money_4":
			dialog.text = "In tal caso, una donazione di centomila pesos sarà sufficiente. Con questo denaro potremo offrire pasti ai bisognosi per molti mesi. Sei pronto a versare subito questa somma, figlio mio?";
			link.l1 = "Certamente. Ecco, prendete. Sono lieto di aiutare chi ne ha davvero bisogno e sono certo che, sotto la vostra guida, questo denaro sarà impiegato con saggezza e onore.";
			link.l1.go = "SharlieEpilog_Benua_Money_4_1";
			link.l2 = "Perdonatemi, ho bisogno di rifletterci ancora una volta.";
			link.l2.go = "SharlieEpilog_Benua_Delivery";
		break;
		
		case "SharlieEpilog_Benua_Money_5":
			dialog.text = "In tal caso, la tua donazione dovrà ammontare a duecentocinquantamila pesos. Questi fondi ci permetteranno di costruire un orfanotrofio che porterà il tuo nome e ne sosterrà le necessità, almeno inizialmente. Sei pronto a versare subito questa somma, figlio mio?";
			link.l1 = "Certamente. Ecco, prendete. Sono lieto di aiutare chi ne ha davvero bisogno e sono certo che, sotto la vostra guida, questo denaro sarà impiegato con saggezza e onore.";
			link.l1.go = "SharlieEpilog_Benua_Money_5_1";
			link.l2 = "Perdonatemi, ho bisogno di rifletterci ancora una volta.";
			link.l2.go = "SharlieEpilog_Benua_Delivery";
		break;
		
		case "SharlieEpilog_Benua_Money_6":
			dialog.text = "Ebbene, pare che tu non abbia perso tempo, "+pchar.name+". Credo che una donazione di cinquecentomila pesos sarà più che sufficiente. Grazie a un contributo simile potremo costruire un ospedale e dotarlo di tutto il necessario per molti anni. Sei pronto a versare subito questa somma, figlio mio?";
			link.l1 = "Certamente. Ecco, prendete. Sono lieto di aiutare chi ne ha davvero bisogno e sono certo che, sotto la vostra guida, questo denaro sarà impiegato con saggezza e onore.";
			link.l1.go = "SharlieEpilog_Benua_Money_6_1";
			link.l2 = "Perdonatemi, ho bisogno di rifletterci ancora una volta.";
			link.l2.go = "SharlieEpilog_Benua_Delivery";
		break;
		
		case "SharlieEpilog_Benua_Money_4_1":
			dialog.text = "Benissimo, figlio mio.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
			AddMoneyToCharacter(pchar, -100000);
			AddQuestRecord("SharlieEpilog", "6");
			AddQuestUserData("SharlieEpilog", "sSum", "10000000");
			AddQuestUserData("SharlieEpilog", "tSum", "100000");
			pchar.questTemp.SharlieEpilog_gold_S = true;
			pchar.questTemp.SharlieEpilog_Money = true;
		break;

		case "SharlieEpilog_Benua_Money_5_1":
			dialog.text = "Benissimo, figlio mio.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
			AddMoneyToCharacter(pchar, -250000);
			AddQuestRecord("SharlieEpilog", "6");
			AddQuestUserData("SharlieEpilog", "sSum", "25000000");
			AddQuestUserData("SharlieEpilog", "tSum", "250000");
			pchar.questTemp.SharlieEpilog_gold_M = true;
			pchar.questTemp.SharlieEpilog_Money = true;
		break;

		case "SharlieEpilog_Benua_Money_6_1":
			dialog.text = "Benissimo, figlio mio.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
			AddMoneyToCharacter(pchar, -500000);
			AddQuestRecord("SharlieEpilog", "6");
			AddQuestUserData("SharlieEpilog", "sSum", "50000000");
			AddQuestUserData("SharlieEpilog", "tSum", "500000");
			pchar.questTemp.SharlieEpilog_gold_L = true;
			pchar.questTemp.SharlieEpilog_Money = true;
			Achievment_Set("ach_CL_205");
		break;

		case "SharlieEpilog_Benua_Patent":
			dialog.text = "E quale sarà, figlio mio?";
			link.l1 = "Nonostante il lungo viaggio che mi attende, vorrei conservare il mio brevetto – così come la mia lealtà alla Francia e al Re.";
			link.l1.go = "SharlieEpilog_Benua_Patent_2";
			link.l2 = "Ho deciso di rinunciare al brevetto. Mi attende un lungo cammino e non so quando tornerò. Forse è meglio non portare con me un fardello di obblighi e regole che potrei non riuscire a rispettare.";
			link.l2.go = "SharlieEpilog_Benua_Patent_6";
			pchar.questTemp.SharlieEpilog_Patent = true;
		break;

		case "SharlieEpilog_Benua_Patent_2":
			dialog.text = "Sono lieto che tu abbia preso questa decisione, figlio mio. Alla nostra nazione servono oggi, più che mai, cavalieri forti e coraggiosi. Ma dimmi, "+pchar.name+", non hai mai pensato di sistemarti, trovare una casa, smettere di rischiare la vita ogni istante? Nessuno può mettere alla prova se stesso per sempre.";
			link.l1 = "Non sono certo di poter restare con le mani in mano, santo padre. Ma come dice la Scrittura: 'anche ai guerrieri del Signore è concesso il riposo, quando la loro opera è compiuta'. Per quanto io sia lontano dal mio compimento, spero di scegliere io stesso il giorno in cui riporre la spada per sempre.";
			link.l1.go = "SharlieEpilog_Benua_Patent_3";
		break;

		case "SharlieEpilog_Benua_Patent_3":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Patent_4";
			AddQuestRecord("SharlieEpilog", "5_2");
		break;

		case "SharlieEpilog_Benua_Patent_4":
			dialog.text = "Benissimo, figlio mio. Credo che Sua Maestà non resterà indifferente alla tua dedizione e al tuo sacrificio.";
			link.l1 = "Ora i miei pensieri sono rivolti ad altro... Spero che mio padre non insista perché io resti nella nostra tenuta. Non credo di essere pronto. Ma per fortuna, avrò tutto il tempo per rifletterci.";
			link.l1.go = "SharlieEpilog_Benua_Patent_5";
		break;

		case "SharlieEpilog_Benua_Patent_5":
			dialog.text = "...";
			link.l1 = "Ebbene, torniamo ora alle faccende terrene.";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_Patent_6":
			dialog.text = "È una decisione saggia. Tuttavia devo dire che la tua partenza indebolirà notevolmente la forza della Francia in queste acque.";
			link.l1 = "Sono certo che, sotto il comando di Sua Maestà, vi siano abbastanza capitani valorosi perché la grandezza della Francia non vacilli.";
			link.l1.go = "SharlieEpilog_Benua_Patent_7";
		break;

		case "SharlieEpilog_Benua_Patent_7":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Patent_8";
			AddQuestRecord("SharlieEpilog", "5_1");
		break;

		case "SharlieEpilog_Benua_Patent_8":
			dialog.text = "...";
			link.l1 = "Ecco fatto. Come se mi fossi tolto un peso dalle spalle. A dire il vero, avevo quasi dimenticato chi ero quando arrivai nei Caraibi... Quante cose ho vissuto.";
			link.l1.go = "SharlieEpilog_Benua_Patent_9";
		break;

		case "SharlieEpilog_Benua_Patent_9":
			dialog.text = "Forse l’hai già sentito dire, figlio mio: le vie del Signore sono imperscrutabili. Tutto ciò che ti era destinato, l’hai affrontato con onore. Ma credo che le tue prove non siano finite, e forse la tua gloria sia solo agli inizi.";
			link.l1 = "La gloria è un peso, santo padre. Non tutti quelli che la cercano sanno sopportarla... o fermarsi in tempo.";
			link.l1.go = "SharlieEpilog_Benua_Patent_10";
		break;

		case "SharlieEpilog_Benua_Patent_10":
			dialog.text = "...";
			link.l1 = "Ebbene, torniamo ora alle faccende terrene.";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;
		
		case "SharlieEpilog_Benua_Baron":
			dialog.text = "Figlio mio, hai affari con il capo dei pirati?";
			link.l1 = "Conoscete il Custode del Codice?";
			link.l1.go = "SharlieEpilog_Benua_Baron_2";
			pchar.questTemp.SharlieEpilog_Baron = true;
		break;

		case "SharlieEpilog_Benua_Baron_2":
			dialog.text = "Il Custode del Codice? No, non lo conosco. Ma conosco Marcus Tirax – un boia con tanto sangue innocente sulle mani che nemmeno cent'anni di preghiere basterebbero a ottenere il perdono del Signore. Eppure... hai davvero rapporti con lui?";
			link.l1 = "Ho dovuto guadagnarmi la sua fiducia... per liberare Michel dalla prigione. Comunque sia, ho riconosciuto il mio errore e non intendo più mantenere alcun contatto con lui. Con questa lettera spezzerò l’ultimo filo che ci lega.";
			link.l1.go = "SharlieEpilog_Benua_Baron_3";
			link.l2 = "Ormai non importa più. Sto lasciando l’arcipelago, e le nostre strade si separeranno da sole, santo padre.";
			link.l2.go = "SharlieEpilog_Benua_Baron_7";
		break;

		case "SharlieEpilog_Benua_Baron_3":
			dialog.text = "E quale sarebbe questo filo, figlio mio? Spero non sia macchiato del sangue degli innocenti.";
			link.l1 = "Formalmente ero il capo dell’insediamento pirata di Le François. Ma in realtà era un altro a governare. Oggi rinuncio al titolo di Barone dei Pirati – definitivamente e irrevocabilmente.";
			link.l1.go = "SharlieEpilog_Benua_Baron_4";
		break;

		case "SharlieEpilog_Benua_Baron_4":
			dialog.text = "Sono felice che tu abbia scelto la retta via, figlio mio, e pregherò per la salvezza della tua anima. Tutti possono cadere, ma il Signore perdona solo chi si pente sinceramente.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Baron_5";
		break;

		case "SharlieEpilog_Benua_Baron_5":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Baron_6";
			AddQuestRecord("SharlieEpilog", "4_1");
		break;

		case "SharlieEpilog_Benua_Baron_6":
			dialog.text = "Perfetto, "+pchar.name+". Dammi la lettera – farò in modo che arrivi al destinatario. E non dimenticare di pregare, figlio mio. Solo il pentimento e la preghiera possono purificare anche i peccati più gravi.";
			link.l1 = "Grazie, santo padre. Forse non tutto è perduto per me.";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_Baron_7":
			dialog.text = "Per quanto grande sia il peccato, figlio mio, le porte del perdono restano sempre aperte. Il pentimento, la preghiera e le buone azioni purificano l’anima come la pioggia lava la polvere dalla pietra.";
			link.l1 = "Ogni cosa a suo tempo, santo padre. Ora devo occuparmi di questioni terrene.";
			link.l1.go = "SharlieEpilog_Benua_Baron_8";
		break;

		case "SharlieEpilog_Benua_Baron_8":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Baron_9";
			AddQuestRecord("SharlieEpilog", "4_2");
		break;

		case "SharlieEpilog_Benua_Baron_9":
			dialog.text = "...";
			link.l1 = "Ecco.";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_IslaMona":
			dialog.text = "È lodevole, figlio mio, che tu voglia occuparti di quelle persone e non ti sia dimenticato di loro. A chi desideri affidare quest’isola?";
			link.l1 = "Penso che dovrebbe sventolarvi la bandiera francese. Prima o poi l’isola verrà scoperta e altri potrebbero cercare di appropriarsene. Non posso permetterlo.";
			link.l1.go = "SharlieEpilog_Benua_IslaMona_France";
			link.l2 = "Quest’isola e i suoi abitanti meritano di vivere liberi, non sotto il giogo della corona. Intendo inviare una lettera al mio amico Jan Svenson di Blueweld. Sono certo che accetterà di prendersi cura di quelle terre. Ma vi prego, santo padre, mantenete il segreto – per la sicurezza e il bene di quelle persone.";
			link.l2.go = "SharlieEpilog_Benua_IslaMona_Pirate";
			pchar.questTemp.SharlieEpilog_IslaMona = true;
		break;

		case "SharlieEpilog_Benua_IslaMona_France":
			dialog.text = "Hai preso una decisione saggia, "+pchar.name+". Sotto la protezione del Re, quest’isola troverà ordine e sicurezza.";
			link.l1 = "Spedirò una lettera all’ufficio di Capsterville e agli abitanti dell’isola. Indicherò le coordinate sulla busta.";
			link.l1.go = "SharlieEpilog_Benua_IslaMona_France_2";
		break;
		
		case "SharlieEpilog_Benua_IslaMona_France_2":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_IslaMona_France_3";
			pchar.questTemp.SharlieEpilog_IslaMona_France = true;
			AddQuestRecord("SharlieEpilog", "3_1");
		break;
		
		case "SharlieEpilog_Benua_IslaMona_France_3":
			dialog.text = "...";
			link.l1 = "Prendete. Spero che i vostri uomini riescano a trovare l'isola prima che vi arrivi la flotta di Sua Maestà.";
			link.l1.go = "SharlieEpilog_Benua_IslaMona_France_4";
		break;

		case "SharlieEpilog_Benua_IslaMona_France_4":
			dialog.text = "Non preoccuparti, figlio mio. Affiderò la consegna di queste lettere ai migliori corrieri.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_IslaMona_Pirate":
			dialog.text = "Non sta a me giudicare se il tuo cammino sia giusto, figlio mio. Prima o poi qualcuno scoprirà quell'isola, e una delle potenze vorrà reclamarla. È solo questione di tempo. Ma se questa è stata la tua decisione, allora forse è la volontà di Dio. Non preoccuparti: non metterò in pericolo quelle persone e pregherò per loro.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_IslaMona_Pirate_2";
		break;

		case "SharlieEpilog_Benua_IslaMona_Pirate_2":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_IslaMona_Pirate_3";
			pchar.questTemp.SharlieEpilog_IslaMona_Pirate = true;
			AddQuestRecord("SharlieEpilog", "3_2");
		break;

		case "SharlieEpilog_Benua_IslaMona_Pirate_3":
			dialog.text = "Jan Svenson di Blueweld, giusto?";
			link.l1 = "Proprio lui, santo padre. E la seconda lettera deve essere consegnata direttamente sull'isola. Le coordinate sono scritte sulla busta.";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_TimeToGoHome":
			dialog.text = "Benissimo, figlio mio. Se non sbaglio, sei arrivato qui a bordo della pinassa '"+GetShipName("Ulysse")+"'?";
			link.l1 = "Esatto. Ma perché lo chiedete?";
			link.l1.go = "SharlieEpilog_Benua_TimeToGoHome_2";
		break;

		case "SharlieEpilog_Benua_TimeToGoHome_2":
			dialog.text = "Perché quella nave è stata recentemente messa all'asta. E tu, Charles, hai l'opportunità di tornare a casa a bordo dello stesso vascello – ma questa volta come capitano.";
			link.l1 = "Hmm... Devo ammettere che l'offerta è allettante. Forse dovrei passare all'ufficio portuale. Vi ringrazio, santo padre.";
			link.l1.go = "SharlieEpilog_Benua_TimeToGoHome_3";
		break;
		
		case "SharlieEpilog_Benua_TimeToGoHome_3":
			DialogExit();
			NextDiag.CurrentNode = "First Time";
			AddDialogExitQuestFunction("SharlieEpilog_PU_Ulysse_1");
		break;
		//<-- Эпилог
		
		case "LH_abbat_38":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

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

// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Cosa vuoi? Chiedi pure.","Ti sto ascoltando, qual è la domanda?"),"È la seconda volta che provi a chiedere...","È la terza volta che stai cercando di chiedere ancora...","Quando finirà?! Sono un uomo impegnato, lavoro sulle questioni della colonia e tu stai ancora cercando di chiedere qualcosa!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea...","Non ora. Luogo e momento sbagliati."),"Vero... Ma più tardi, non ora...","Chiederò... Ma un po' più tardi...","Mi dispiace, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);			  
			link.l1.go = "exit";
			/* //--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew"))
			{
				link.l1 = "Signore, ho trovato un cadavere di bandito nella giungla. È stato ucciso dagli indiani. C'erano degli orecchini sul suo corpo, sembra che siano stati portati qui dall'Europa. Forse appartenevano a uno dei nobili della vostra città?";
                link.l1.go = "Sharlie_junglejew";
			}
			//<-- Бремя гасконца */
			//--> Sinistra, Травля крысы
			if (CheckAttribute(pchar, "questTemp.TK_Potopil"))
			{
				link.l1 = "Sua Eccellenza, l'azione è compiuta! Tuttavia, mi dispiace informarla che il criminale non ha sopravvissuto allo scontro, e quindi non affronterà l'esecuzione.";
                link.l1.go = "TK_Potopil";
			}
			if (CheckAttribute(pchar, "questTemp.TK_Plen"))
			{
				link.l1 = "Sua Eccellenza, il compito è completo! Il prigioniero attende il suo destino nella mia prigione.";
                link.l1.go = "TK_Plen";
			}
			//<-- Травля крысы
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_9_continue" && !CheckAttribute(npchar, "quest.frigate"))
			{
				link.l1 = "Sono arrivato per ordine del Governatore Generale Philippe de Poincy per prendere il comando della vostra fregata armata.";
                link.l1.go = "patria";
			}
			if (CheckAttribute(npchar, "quest.frigate.wait") && GetCompanionQuantity(pchar) < 5)
			{
				link.l1 = "Sono pronto a prendere la fregata nella mia squadra.";
                link.l1.go = "patria_2";
			}
			// Jason Дороже золота
			if (CheckAttribute(pchar, "questTemp.GoldenGirl") && pchar.questTemp.GoldenGirl == "message")
			{
				link.l1 = "Sono arrivato al vostro invito, Monsieur...";
                link.l1.go = "goldengirl";
			}
			if (CheckAttribute(pchar, "questTemp.GoldenGirl") && pchar.questTemp.GoldenGirl == "girl_prisoner")
			{
				link.l1 = "C'è stata una sfortuna, Monsieur";
                link.l1.go = "goldengirl_10";
			}
			// andre39966 ===> В плену великого улова.
			if (CheckAttribute(pchar, "questTemp.VPVL_Magor_Dialogue"))
			{
				link.l1 = "Sua Eccellenza, sono venuto in possesso di informazioni riguardanti il commercio illecito che presto avrà luogo su queste coste. Oso dire che questa questione potrebbe dimostrarsi degna della vostra attenzione.";
				link.l1.go = "VPVL_Magor_1";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.VPVL_GovernorDialogueAvailable"))
			{
				link.l1 = "Sua Eccellenza, vengo in cerca di notizie riguardo a quella nave da contrabbando di cui abbiamo discusso.";
				link.l1.go = "VPVL_Magor_4";
			}
			//  <=== В плену великого улова.  
		break;
		
		case "Sharlie_junglejew":
			dialog.text = "Vediamo cosa hai... Incredibile! È semplicemente incredibile, Charles! Questi sono gli orecchini di mia moglie. Glieli avevo regalati prima di lasciare l'Europa e venire nelle colonie. Sono scomparsi alcuni mesi fa in circostanze misteriose. Sapevo che erano stati rubati!\nCharles, sono molto contento che tu sia venuto direttamente da me, e non hai venduto la cosa che tengo così cara ai mercanti. Ti ripagherò per il tuo favore. Come ho sentito, stai per comprare una nave? Dal momento che hai deciso di partecipare alla navigazione, avrai senza dubbio bisogno di una mappa del nostro arcipelago. Eccola, prendila. Sono sicuro che ti sarà utile!";
			link.l1 = "Grazie, vostra Grazia!";
			link.l1.go = "Sharlie_junglejew_1";
		break;
		
		case "Sharlie_junglejew_1":
			DialogExit();
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "jewelry25", 1);
			GiveItem2Character(pchar, "map_normal");
			AddQuestRecord("SharlieE", "2");
			CloseQuestHeader("SharlieE");
			DeleteAttribute(pchar, "questTemp.Sharlie.Junglejew");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
			{
				DelLandQuestMark(npchar);
			}
		break;
		
		//--> Sinistra, Травля крысы
		case "TK_Potopil":
			dialog.text = "È sfortunato, Charles, ma dobbiamo fare i conti con la situazione attuale. Ecco la tua ricompensa: cinquemila pesos, dopo le tasse.";
			link.l1 = "Mi fa piacere servire St. Pierre e te personalmente. Anche se la battaglia è stata difficile, ho trovato un certo piacere in essa.";
			link.l1.go = "TK_Potopil_3";
			link.l2 = "È stata una battaglia impegnativa, vostra Eccellenza. La mia nave ha subito danni significativi. Sarebbe possibile compensarmi per le mie perdite?";
			link.l2.go = "TK_Potopil_4";
			DeleteAttribute(pchar, "questTemp.TK_Potopil");
			AddCharacterExpToSkill(pchar, "Accuracy", 20);
			AddCharacterExpToSkill(pchar, "Cannons", 20);
			AddCharacterExpToSkill(pchar, "Grappling", 20);
			AddCharacterExpToSkill(pchar, "Defence", 20);
			
			CloseQuestHeader("TravlyaKrys");
		break;
		
		case "TK_Potopil_3":
			dialog.text = "Bravo, Charles! Non ho dubbi che salirai molto nei nostri ranghi.";
			link.l1 = "Fino al nostro prossimo incontro, Vostra Eccellenza.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 5000);
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
		break;
		
		case "TK_Potopil_4":
			dialog.text = "Devo dire, sono un po' sorpreso dalla tua richiesta, Charles... Molto bene, considera altri due mila pesos da me personalmente come un gesto di buona volontà. Addio.";
			link.l1 = "Grazie, vostra Eccellenza.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 7000);
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterNationReputation(pchar, FRANCE, 2);
		break;
		
		case "TK_Plen":
			dialog.text = "Eccellente, Charles! Sarai lieto di sapere che il tuo successo aiuterà i tuoi amici maltesi in un'operazione delicata... Ecco la tua ricompensa: ottomila pesos, dopo le tasse.";
			link.l1 = "Sono lieto di servire St. Pierre, l'Ordine e te personalmente. Anche se la lotta è stata impegnativa, ho trovato una certa soddisfazione in essa.";
			link.l1.go = "TK_Plen_3";
			link.l2 = "È stata una dura battaglia, vostra Eccellenza. La mia nave ha subito danni considerevoli. Potrei richiedere un risarcimento per le mie perdite?";
			link.l2.go = "TK_Plen_4";
			AddCharacterExpToSkill(pchar, "Accuracy", 20);
			AddCharacterExpToSkill(pchar, "Cannons", 20);
			AddCharacterExpToSkill(pchar, "Grappling", 20);
			AddCharacterExpToSkill(pchar, "Defence", 20);
			CloseQuestHeader("TravlyaKrys");
			DeleteAttribute(pchar, "questTemp.TK_Plen");
			sld = CharacterFromID("TK_Heiter2");
			RemovePassenger(pchar, sld);
			sld.lifeday = 0;
		break;
		
		case "TK_Plen_3":
			dialog.text = "Bravo, Charles! Sono sicuro che andrai lontano.";
			link.l1 = "Fino al nostro prossimo incontro, vostra Eccellenza";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 8000);
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
		break;
		
		case "TK_Plen_4":
			dialog.text = "Suppongo che te lo sia meritato. Tieni altri duemila da me personalmente come gesto di buona volontà. Grazie, amico mio.";
			link.l1 = "Grazie, vostra Eccellenza.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 10000);
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterNationReputation(pchar, FRANCE, 2);
		break;
		//<-- Травля крысы
		
		// Jason НСО
		case "patria":
			if (GetCompanionQuantity(pchar) > 4)
			{
				dialog.text = "La nave è pronta, ma non hai un posto libero per essa nella tua squadriglia. Capitano, riduci la tua squadriglia e torna, allora ti darò immediatamente la fregata.";
				link.l1 = "Bene.";
				link.l1.go = "patria_1";
			}
			else
			{
				dialog.text = "Sì, certo, la nave è pronta a salpare. Il suo capitano è informato e seguirà tutti i tuoi ordini.";
				link.l1 = "Allora partiamo. Addio, Vostra Grazia.";
				link.l1.go = "patria_3";
			}
		break;
		
		case "patria_1":
			DialogExit();
			npchar.quest.frigate.wait = "true";
		break;
		
		case "patria_2":
			DeleteAttribute(npchar, "quest.frigate.wait");
			dialog.text = "Eccellente. Preparati a salutare la tua nuova nave. Il suo capitano è informato e seguirà tutti i tuoi ordini.";
			link.l1 = "Allora stiamo partendo. Addio, Vostra Grazia.";
			link.l1.go = "patria_3";
		break;
		
		case "patria_3":
			DialogExit();
			npchar.quest.frigate = "true";
			Patria_BastionFrigateMrt(); // присоединяем фрегат
		break;
		
		// Jason Дороже золота
		case "goldengirl":
			dialog.text = "Capitano Charles de Maure, finalmente! Ti aspettavo con ansia! Per favore, entra, unisciti a me.";
			link.l1 = "Buongiorno anche a Lei, Sua Eccellenza. C'è sempre un motivo dietro una tale cortesia da parte sua. Cosa c'è stavolta? Pirati, spagnoli, cannibali pellerossa?";
			link.l1.go = "goldengirl_1";
		break;
		
		case "goldengirl_1":
			dialog.text = "Non diventare tutto ironico, Capitano. Non è colpa mia se finiamo sempre nei guai, tu ed io. Ma per favore, non preoccuparti, questa volta non ci saranno sparatorie... probabilmente.";
			link.l1 = "Mi incuriosisci, continua. Come posso essere d'aiuto?";
			link.l1.go = "goldengirl_2";
		break;
		
		case "goldengirl_2":
			dialog.text = "Mai sentito parlare del raffinato stabilimento di Madame Botot? Durante l'assedio il nostro... bordello è andato in cenere. Un giorno una certa signora si è offerta di ricostruirlo.";
			link.l1 = "Un incendio in un bordello e senza di me? A proposito, quel giorno sono stato anche colpito dagli spagnoli.";
			link.l1.go = "goldengirl_3";
		break;
		
		case "goldengirl_3":
			dialog.text = "Dannazione, Charles cosa ti succede oggi? Il tuo sarcasmo è inopportuno! Anche se non è una questione di Stato, è comunque un affare importante, per me, personalmente! Ho bisogno del tuo aiuto! Per l'amor di Dio, riscuotiti e ascoltami!";
			link.l1 = "Perdonatemi, Vostra Eccellenza. Sento un grande sollievo, tutto qui. Ad essere onesto, mi sono stancato di tutte queste continue battaglie e lotte. Mi aspettavo che mi trascinaste in un altro cerchio di violenza. Per favore, continuate. Non ho mai sentito parlare di questa Madame Botot.";
			link.l1.go = "goldengirl_4";
		break;
		
		case "goldengirl_4":
			dialog.text = "Bene, quindi questa onorabile dama ha elevato l'establishment a un livello totalmente nuovo. È ora un luogo di alta e nobile società, non un buco di topo, come era solito essere. Un luogo di vizi distinti, vino costoso e gioco d'azzardo illimitato. Vedrai tutto con i tuoi occhi!";
			link.l1 = "Sua Eccellenza, non sono un puritano e la sua descrizione era molto colorita, ma perché me lo sta raccontando?";
			link.l1.go = "goldengirl_5";
		break;
		
		case "goldengirl_5":
			dialog.text = "Perché sei nella lista, perché altrimenti?! Vedi, mi sento in colpa per la Marchesa e ho promesso di presentarti a lei in una delle sue feste domani. Juliana non lo fa spesso quindi per favore sii gentile da unirti a noi. Niente lotte, sparatorie e inseguimenti questa volta, lo prometto. Tutto sarà cortese e dignitoso: vino, donne splendide, carte e altri nobili divertimenti.";
			link.l1 = "Carte e puttane. È passato un po' di tempo da quando, in una vita diversa. Tuttavia, non ti seguo ancora. Perché io?";
			link.l1.go = "goldengirl_6";
		break;
		
		case "goldengirl_6":
			dialog.text = "Sei sordo? Juliana Botot, lei... colleziona volti luminosi e famosi. Rendono le sue feste speciali e fresche. Ti sei fatto un bel nome, la Marchesa ha aspettato a lungo per averti come suo ospite. Il mio passo falso le ha dato l'opportunità e non la coglierò se rifiuta di ricevermi di nuovo. Questo è tutto quello che otterrò se non ti consegnerò a lei!";
			link.l1 = "Vostra Eccellenza, siete un attraente vedovo e governatore ... Perché vi preoccupate dell'opinione di qualche cortigiana? Sono loro che dovrebbero cercare il vostro favore, non il contrario.";
			link.l1.go = "goldengirl_7";
		break;
		
		case "goldengirl_7":
			dialog.text = "La marchesa Botot è sotto la protezione del conte Henry de Levi-Vantadur - che, per grazia di Sua Maestà, è il capo degli stati della Nuova Francia in Nord America. Credimi, Charles, qui nessuno vuole contraddirlo.";
			link.l1 = "Quasi mi avevi qui - pensavo che fosse solo questione di lussuria e amore. Ora vedo che era politica fin dall'inizio. Banale, ma prevedibile. Molto bene, ti aiuterò. Sarà dolce ritornare ai giorni della mia gioventù solo per una notte.";
			link.l1.go = "goldengirl_8";
		break;
		
		case "goldengirl_8":
			dialog.text = "Capitano, sei senza dubbio un uomo esperto, ma non cercare di fingere di essere un vecchio. Non si tratta solo di politica. Apprezzo la presenza di Juliana e sono grato per il tuo aiuto. È importante per me personalmente, veramente. Vieni da Marchesa Botot dopo il tramonto, domani. Ti prometto che la politica non rovinerà la notte.";
			link.l1 = "Vino, carte, donne. Proprio come nei vecchi tempi. Addio, Vostra Eccellenza!";
			link.l1.go = "goldengirl_9";
		break;
		
		case "goldengirl_9":
			DialogExit();
			bDisableFastReload = true;//закрыть переход
			pchar.quest.GoldenGirl_bronca.win_condition.l1 = "location";
			pchar.quest.GoldenGirl_bronca.win_condition.l1.location = "FortFrance_town";
			pchar.quest.GoldenGirl_bronca.function = "GoldenGirl_GirlAngry";
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("GoldenGirl_TimeOver", 0, 0, 2, false); // таймер до завтрашней полуночи
			SetFunctionTimerCondition("GoldenGirl_BrothelDoor", 0, 0, 1, false); // таймер на закрытие дверей борделя
			pchar.quest.GoldenGirl_eventstart.win_condition.l1 = "Timer";
			pchar.quest.GoldenGirl_eventstart.win_condition.l1.date.hour  = 21.00;
			pchar.quest.GoldenGirl_eventstart.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.GoldenGirl_eventstart.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.GoldenGirl_eventstart.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.GoldenGirl_eventstart.win_condition.l2 = "location";
			pchar.quest.GoldenGirl_eventstart.win_condition.l2.location = "FortFrance_SecBrRoom"; // возможно закрыть бордель и вход только через боковую комнату
			pchar.quest.GoldenGirl_eventstart.function = "GoldenGirl_Party"; // таймер на начало вечеринки
			pchar.questTemp.GoldenGirl = "brothel";
			AddQuestRecord("GoldenGirl", "2");
		break;
		
		case "goldengirl_10":
			dialog.text = "Charles, cosa è successo, sembri un inferno!";
			link.l1 = "Angerran, maledetto, Chievous, Eccellenza. Ha rubato la mia fregata la scorsa notte. Ha messo a morte il mio equipaggio di premio e ha preso il largo nella nebbia.";
			link.l1.go = "goldengirl_11";
		break;
		
		case "goldengirl_11":
			dialog.text = "È uno sviluppo spiacevole, lo capisco, ma credimi - tale risultato è abbastanza soddisfacente. Non sei in urgente bisogno di navi e uomini, mentre de Levi Vantadur pagherà una somma significativa per nascondere la verità dietro un certo duello recente. O ricorderà il nostro ruolo nel nasconderlo gratuitamente, il che vale anche molto. De Chievous ha agito in modo disonesto due volte, ma ora è lontano, mentre noi abbiamo ancora delle buone carte contro di lui.";
			link.l1 = "Tre volte, vostra Eccellenza. Angerran ha ammesso di aver barato durante la nostra partita a carte. Ma non intende risarcirmi con denaro, se è questo quello che intendi. Ha oltrepassato il limite. C'era una certa persona su quella nave stamattina... è molto cara per me! Non permetterò al bastardo di farle del male! Hai sentito, Jacques, non lo permetterò!";
			link.l1.go = "goldengirl_12";
		break;
		
		case "goldengirl_12":
			dialog.text = "Credo di sapere di chi stai parlando - ricordo di averti visto con una... ragazza, vestita come un uomo e armata fino ai denti come un pirata. Charles, non fare lo stupido! Sei stato fortunato, hai evitato grossi guai e ora cosa, stai cercando di cacciarti di nuovo nei guai? Lascia perdere. De Chievous è in fuga - grazie a Dio! E riguardo alla tua 'fidanzata in armi' - segui il consiglio di un amico - vai a vedere Julianna e dimentica tutto questo.";
			link.l1 = "Fuori questione, vostra Eccellenza. Alcune cose sono semplicemente al di là della vostra comprensione, capito? Ora ditemi tutto quello che sapete su quel bastardo. Dove potrebbe andare da Saint Pierre? E non cercate di dissuadermi di nuovo - Ho fatto i conti con la Compagnia Olandese, con i baroni dei pirati, con i governatori generali, persino con la Santa Inquisizione! Non sono un uomo facile da spaventare. La riavrò a qualunque costo!";
			link.l1.go = "goldengirl_13";
		break;
		
		case "goldengirl_13":
			dialog.text = "Charles, hai mai riflettuto sulla questione di chi nomina i governatori generali? Questo è un mondo assolutamente diverso! Lo hai appena sfiorato, è al di là della tua comprensione, sei come un bambino in un deposito di polvere da sparo. E mi stai chiedendo di passarti una candela accesa. Per quanto riguarda i governatori generali: de Poincy stesso non si scontra mai con il conte, né in questioni di denaro né in questioni di politica. Vice Re, il termine così popolare tra la gente comune, si adatterebbe perfettamente a Henri de Levi Vantadur.";
			link.l1 = "Eccomi qui, intenzionato a sbudellare il suo unico erede maschio, so cosa sto rischiando. Ora, dimmi: c'è qualcosa di utile che conosci che potrebbe aiutarmi?";
			link.l1.go = "goldengirl_14";
		break;
		
		case "goldengirl_14":
			dialog.text = "L'altro giorno, avrei considerato questo gesto verso la tua pistola come la fine della nostra amicizia, Charles. Ma capisco il tuo stato d'animo attuale. Ecco perché sono pronto a dimenticare tutto questo. Non so nulla di utile per te, la fregata è andata a Ovest all'alba. Dovresti fare una visita alla Marchesa... Aspetta, non così! Julianna sa molto sul tuo nemico ed era personalmente... conosciuta da suo padre per un po'. Chiedile. A differenza mia, lei non ti fermerà.";
			link.l1 = "Questo è il piano. Ci vediamo, Eccellenza. Grazie per il tuo tempo.";
			link.l1.go = "goldengirl_15";
		break;
		
		case "goldengirl_15":
			DialogExit();
			LocatorReloadEnterDisable("FortFrance_town", "reload9_back", false); 
			LocatorReloadEnterDisable("FortFrance_town", "reload91", false);
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_58";
			LAi_SetOwnerType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			pchar.questTemp.GoldenGirl = "find_girl";
		break;
		
		// В плену великого улова, andre39966
		case "VPVL_Magor_1":
			dialog.text = "Merci di contrabbando, dici? Hmm... molto intrigante. Prego, illuminami con i particolari della tua scoperta.";
			link.l1 = "Tre giorni fa, una nave carica di contrabbando doveva gettare l'ancora nella baia di Le Marin. La nave non ha fatto il suo appuntamento, ma ho buoni motivi per credere che arriverà presto al porto. Forse i tuoi uomini potrebbero organizzare un'accoglienza adeguata per questi briganti quando arrivano, Vostra Eccellenza.";
			link.l1.go = "VPVL_Magor_2";
			pchar.questTemp.VPVL_DontSpawnSmugglersShip = true; 
			DelLandQuestMark(npchar);
		break;

		case "VPVL_Magor_2":
			dialog.text = "Una nave senza nome che trasporta un carico senza nome... E presumi che dovrei mandare le forze di Sua Maestà su una tale intelligenza nebulosa?";
			link.l1 = "Sua Eccellenza, riconosco che i dettagli sono scarsi. Ma permettetemi di raccontare come queste informazioni sono entrate in mio possesso. (Cutscene)";
			link.l1.go = "VPVL_Magor_3";
		break;

		case "VPVL_Magor_3":
			dialog.text = "Molto bene, metteremo alla prova la tua intelligenza. Se una nave che trasporta contrabbando dovesse davvero ancorare al largo delle coste di Le Marin, sarai generosamente ricompensato per il tuo servizio alla Corona. Torna da me tra tre giorni. Entro allora, la nebbia dell'incertezza si sarà diradata.";
			link.l1 = "Eccellente. Allora ci vediamo tra tre giorni.";
			link.l1.go = "VPVL_Delete_Spawn_Ship";
			AddDialogExitQuest("VPVL_SetGovernorDialogueFlag");
			AddQuestRecord("VPVL", "6");
		break;

		case "VPVL_Magor_4":
			dialog.text = "Ah, Capitano! Un piacere riceverti di nuovo. Le tue informazioni si sono rivelate davvero preziose. I miei uomini hanno intercettato la nave esattamente dove avevi indicato. Ecco - centocinquanta dobloni spagnoli, appena coniati e pesanti nel borsellino. Prendili con la mia gratitudine.";
			link.l1 = "Le mie umili grazie, Vostra Eccellenza. È una buona fortuna che il mio briciolo di intelligenza abbia servito gli interessi della Corona. Se si dovesse presentare un'altra occasione, sappiate che il mio braccio spadaccino e il mio occhio acuto restano a vostra disposizione.";
			link.l1.go = "VPVL_Delete_Flag";
			AddItems(PChar, "gold_dublon", 150);
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
			DelLandQuestMark(npchar);
		break;

		case "VPVL_Delete_Flag":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.VPVL_GovernorDialogueAvailable");
			DeleteAttribute(pchar, "questTemp.VPVL_DontSpawnSmugglersShip");
		break;

		case "VPVL_Delete_Spawn_Ship":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.VPVL_Magor_Dialogue");
			AddDialogExitQuest("VPVL_KillCapitanOfSmuggler");
		break;
		// <=== В плену великого улова
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

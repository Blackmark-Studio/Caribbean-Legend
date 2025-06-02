// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Cosa vuoi? Chiedi pure.","Ti sto ascoltando, qual è la domanda?"),"Questa è la seconda volta che provi a chiedere...","Questa è la terza volta che provi a chiedere...","Quando finirà tutto questo?! Sono un uomo impegnato, lavoro su questioni della colonia e tu continui a disturbarmi!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea...","Non ora. Luogo e momento sbagliati."),"Vero... Ma più tardi, non ora...","Chiederò... Ma un po' più tardi...","Mi dispiace, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_2" && !CheckAttribute(npchar, "quest.patria") && !CheckAttribute(pchar, "questTemp.Patria.Visiter_Late"))
			{
				link.l1 = TimeGreeting()+"Signore. Sono qui su ordine del Governatore Generale Chevalier de Poincy. Il mio compito è consegnare un barone di nome Noel Forget a Tortuga, che è arrivato dalla metropoli con il compito di ispezionare le colonie, il suo scopo principale è la creazione di una Compagnia commerciale delle Indie Occidentali francesi. Permettetemi di presentarvelo... Spiegherà lui stesso tutti i dettagli.";
                link.l1.go = "patria_portpax";
			}
			// Rebbebion, квест "Путеводная звезда"
			if (CheckAttribute(pchar, "questTemp.PZ.PortPaxMayorTalk"))
			{
				link.l1 = "Sua Signoria, volevate vedermi?";
				link.l1.go = "PZ1";
			}
			// Украденное воспоминание
			if (CheckAttribute(pchar, "questTemp.UV_DialogMayor"))
			{
				link.l1 = "Eccellenza, porto informazioni di natura molto delicata che richiedono la vostra attenzione.";
				link.l1.go = "UV_1";
			}
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple("Hai già preso tutto. Cosa vuoi ancora?","C'è qualcosa che non hai preso?");
            link.l1 = RandPhraseSimple("Solo sto guardando intorno...","Solo un controllo, potrei dimenticare di prendere qualcosa...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		
		// Jason НСО
		case "patria_portpax":
			dialog.text = "Sono molto lieto di incontrarvi, Capitano Charles de Maure, e il Barone. Farò tutto il possibile affinché il soggiorno di Monsieur Forget nella nostra colonia sia il più confortevole possibile. E approfittando del fatto che un Monsieur di così alto rango mi ha fatto visita, vi proporrei una questione.";
			link.l1 = "Molto interessante! Raccontaci del tuo affare, Sua Grazia.";
			link.l1.go = "patria_portpax_1";
		break;
		
		case "patria_portpax_1":
			dialog.text = "Negli ultimi mesi, nessun rappresentante del Governatore Generale ha visitato la nostra colonia, come se a Saint Kitts si fossero completamente dimenticati di noi! E nel frattempo, gli spagnoli, desiderosi di rendere l'intera Hispaniola puramente spagnola e per i quali i coloni francesi e i bucanieri a ovest dell'isola sono un grosso fastidio, stanno preparando un attacco! I miei ufficiali di pattuglia, i nostri capitani mercantili e persino i pescatori comuni hanno riferito che una potente squadra spagnola si sta radunando a Santiago, e che si sta preparando ad attaccare Port-au-Prince!";
			link.l1 = "Le prove sono abbastanza chiare, Sua Maestà?";
			link.l1.go = "patria_portpax_2";
		break;
		
		case "patria_portpax_2":
			dialog.text = "Non ho informazioni precise, ma così tante notizie da persone completamente casuali non possono essere solo voci. La nostra colonia è molto importante per la Francia, abbiamo le migliori piantagioni qui, che il Barone può vedere personalmente. Perdere questa colonia o persino esporla al rischio di essere saccheggiata è inaccettabile!";
			link.l1 = "Prenderò in considerazione le tue prove e informerò il Cavaliere de Poincy. Sono sicuro che prenderà misure immediate.";
			link.l1.go = "patria_portpax_3";
		break;
		
		case "patria_portpax_3":
			dialog.text = "Grazie, capitano...";
			link.l1 = "";
			link.l1.go = "patria_portpax_4";
		break;
		
		case "patria_portpax_4":
			DialogExit();
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_9";
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", "governor1");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
			npchar.quest.patria = "true";
		break;
		
		case "PZ1":
			DeleteAttribute(pchar, "questTemp.PZ.PortPaxMayorTalk");
			dialog.text = "No, non ti ho convocato, signore. Desideravi qualcosa?";
			link.l1 = "How could I? But your messenger met us; he said you had prepared one of the houses in the town for me...";
			link.l1.go = "PZ2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ2":
			dialog.text = "Che casa, che messaggero, che è questa insolenza?!";
			link.l1 = "Cosa intendi, quale messaggero... Il suo nome è Henri Thibaut, e...";
			link.l1.go = "PZ3";
		break;
		
		case "PZ3":
			dialog.text = "COSA? Sai nemmeno chi sia lui? Apparentemente no. Ma non importa. Cosa sta facendo il nipote di Levasseur nella mia città?";
			link.l1 = "Oh, mio Dio...";
			link.l1.go = "PZ4";
		break;
		
		case "PZ4":
			dialog.text = "De Maure, mi senti? Signore?";
			link.l1 = "...";
			link.l1.go = "PZ5";
		break;
		
		case "PZ5":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorRunToLocator(pchar, "reload", "reload1", "PZ_SharleBezhitObratno", -1);
			bDisableCharacterMenu = true;
			InterfaceStates.Buttons.Save.enable = false;
			SetMusic("music_teleport");
			pchar.questTemp.lockedMusic = true;
		break;
		
		//--> Украденное воспоминание
		case "UV_1":
			dialog.text = "Una questione delicata, dite? Avete suscitato il mio interesse, Capitano. Per favore, continuate—avete tutta la mia attenzione.";
			link.l1 = "La questione riguarda tua nipote, Julie. Ha richiesto i miei servizi per recuperare una collana che le era stata rubata.";
			link.l1.go = "UV_2";
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			DelLandQuestMark(npchar);
		break;

		case "UV_2":
			dialog.text = "Una collana? Curioso. Non ricordo un tale oggetto tra i suoi averi.";
			link.l1 = "Mi permetta di presentare i fatti in ordine, Governatore. Ho recuperato con successo la collana in questione. La mia indagine ha rivelato che la ladra era la cameriera di vostra nipote, Giselle. Dalle mie osservazioni del mercante che ha acquistato l'oggetto rubato, sospetto fortemente che questa non sia né la sua prima né l'ultima trangressione.";
			link.l1.go = "UV_3";
		break;

		case "UV_3":
			dialog.text = "Molto illuminante. Continua pure con il tuo racconto.";
			link.l1 = "Quello che ha attirato la mia attenzione, Eccellenza, è che Julie ha scelto di non cercare il vostro aiuto in questa questione. La collana, pare, era un dono da un individuo con cui le avete espressamente vietato di associarsi. Credendo che le vostre restrizioni nascano dalle intenzioni più sagge e protettive, mi sono sentito obbligato a portare questa questione alla vostra attenzione e a restituire la collana direttamente a voi.";
			link.l1.go = "UV_4";
			TakeItemFromCharacter(pchar, "SM_necklace_Julie");
		break;

		case "UV_4":
			dialog.text = "La tua valutazione si dimostra solida"+GetSexPhrase(", Capitano","")+". Lodo la tua discrezione nel portare questo direttamente a me piuttosto che indulgere nelle indiscrezioni giovanili di mia nipote.";
			link.l1 = "Agisco solo pensando al suo bene, Governatore. Non ho dubbi che la vostra guida nasca dalla stessa fonte di preoccupazione e saggezza.";
			link.l1.go = "UV_5";
		break;

		case "UV_5":
			dialog.text = "Certo, Capitano. Come suo zio e tutore, il suo benessere è la mia principale preoccupazione. Si prega di accettare questi centocinquanta dobloni come segno del mio apprezzamento per la vostra discrezione. Vi presento anche questa bussola di navigazione, possa guidarvi in sicurezza nei vostri viaggi attraverso acque pericolose.";
			link.l1 = "Sono onorato dalla vostra generosità, Eccellenza, anche se tale ricompensa non era necessaria. Purtroppo, ora devo dirvi addio: la marea non aspetta nessun marinaio e la mia nave richiede la mia attenzione.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("UV_End");
			AddItems(pchar, "gold_dublon", 150);
			GiveItem2Character(PChar, "compass1");
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
		break;
		//<-- Украденное воспоминание
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

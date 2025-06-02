// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quali domande hai?","Come posso aiutarti, "+GetAddress_Form(NPChar)+"?"),"Hai cercato di farmi una domanda poco tempo fa, "+GetAddress_Form(NPChar)+"...","Per tutto il giorno, è la terza volta che parli di qualche domanda...","Altre domande, presumo?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea...","Non ho nulla di cui parlare al momento."),"Umph, dove se n'è andata la mia memoria...","Sì, è davvero la terza volta...","No, quali domande?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(PChar, "questTemp.Guardoftruth.Archy") && pchar.questTemp.Guardoftruth.Archy == "islatesorotavern")
			{
				link.l1 = "Ascolta, "+npchar.name+", hai sentito qualcosa su un uomo di nome Miguel Dichoso? Dicono che la sua nave sia stata avvistata nelle acque dell'Isla Tesoro...";
				link.l1.go = "guardoftruth";
			}
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				link.l1 = "Ascolta, "+npchar.name+", non hai visto recentemente Miguel Dichoso su Isla Tesoro?";
				link.l1.go = "tieyasal";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Sì, l'ho fatto. Quel don spagnolo ha venduto a Shark Dodson una nave straordinaria, una fregata, quando ancora risiedeva qui. Ah quella nave... Era incredibile...";
			link.l1 = "Lascia che indovini: aveva una struttura moderna e snella ed era in grado di raggiungere sedici nodi? E il suo nome era 'Santa Quitaria'?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Per quanto riguarda la struttura e la velocità, hai perfettamente ragione, ma aveva un nome diverso: 'San Martin'. Lo Squalo ha pagato un mucchio di oro a quel furfante per quella nave.";
			link.l1 = "Sei sicuro che fosse 'San Martin' e non 'Santa Quiteria'? Quando l'ha comprato? E perché hai chiamato Dichoso un furfante?";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Maledetti occhi, sono assolutamente sicuro che era 'San Martin', perché ho assistito personalmente ai lavoratori di Alexus mentre strappavano una targa con quella sciocchezza papista dalla poppa. Shark Dodson la chiamava 'Fortuna', un nome molto più adatto per una bellezza del genere. (sputa) L'ha comprata nell'inverno del '54, poco prima che Blaze venisse assassinato\nPerché ho chiamato Don Miguel un furfante? Perché ha rubato la maledetta nave dalla marina spagnola fuori da Providence! Dodson ha messo in scena uno spettacolo con fuoco e fumo per il forte di San Juan e la sua guarnigione, come mi ha sempre raccontato quando era ubriaco. Shark ha sacrificato due luggers danneggiati per far sembrare reale il combattimento con la fregata\nQuando è arrivata la notte, ha navigato segretamente il 'San Martin' verso Isla Tesoro. Shark ha ottenuto la nave e Dichoso ha ottenuto i soldi. Il furbo bastardo ha poi detto ai suoi superiori che la fregata era affondata durante il combattimento con la flotta pirata, il comandante del forte di San Juan lo ha confermato.";
			link.l1 = "Oh, come quei dons spagnoli riempiono le loro tasche! Che furbo! Dimmi, sei sicuro che è successo nell'inverno del 1654? Non potrebbe essere stata durante la primavera? E quella fregata non mostrava segni di usura e di strappi dalla tempesta?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Sono abbastanza sicuro che fosse inverno... Oh, chi lo sa. Forse era primavera. Non me lo ricordo con certezza. Probabilmente ero ubriaco. La fregata non era per niente usurata, era nuovissima.";
			link.l1 = "E dove si trova quella bellezza di una fregata ora?";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "Una storia oscura, è... Quando Blaze fu assassinato, tutti sospettavano di Shark perché la sua collana, un dente di squalo, fu trovata sul cadavere. Inoltre, alcune persone videro Shark nella residenza di Blaze quella notte\nShark fuggì da Isla Tesoro prima che gli dessero la marca nera. Ha fatto visita al Pastore Oscuro e ha scambiato la sua fregata per una brigantina. Nessuna idea di dove sia l'uomo ora. Zachary ha poi venduto la fregata a William Paterson.";
			link.l1 = "Chi è questo Paterson?";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "Cosa, non hai mai sentito parlare di Willie Paterson? È uno scozzese, appena arrivato nei Caraibi. Si considera capitano della flotta reale, il preferito del colonnello Fox! A proposito, ha appena iniziato a fare qualche affare con Jackman. La nave ammiraglia di Patterson è 'Fortuna' in persona.";
			link.l1 = "Capisco. Sai dove si trova Dichoso ora?";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "Non ne ho idea. Dopo quel trucco con la 'Fortuna' non l'ho più visto su Isla Tesoro e non ho sentito nulla su di lui.";
			link.l1 = "Va bene, "+npchar.name+", grazie per le informazioni dettagliate! Sei un eccellente locandiere! Vorrei ci fossero più persone come te... Addio!";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "Buona fortuna, "+pchar.name+"!";
			link.l1 = "...";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			DialogExit();
			AddQuestRecord("Guardoftruth", "60_1");
			pchar.questTemp.Guardoftruth.Archy = "guadeloupe";
			// маленькая развлекуха
			pchar.quest.GuardOT_cabinattack.win_condition.l1 = "EnterToSea";
			pchar.quest.GuardOT_cabinattack.function = "GuardOT_PrepareCreateBandosInCabin";
		break;
		
		case "tieyasal":
			dialog.text = "Sembra che tu e lui vi stiate rincorrendo, amico. Sì, Dichoso era qui, proprio dove stai tu. E proprio come lui, si informava su di te l'ultima volta che eri a Sharptown.";
			link.l1 = "Cavolo! Questa è la notizia... E dove si trova Miguel adesso?";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Non ne ho idea. È partito per il mare dove... ha detto qualcosa su Blueweld. Probabilmente è andato lì solo per cercarti.";
			link.l1 = "Sei per caso quella che l'ha mandato a Blueweld?";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = "No. Tutto quello che gli ho detto è che non ti avevo visto da molto tempo.";
			link.l1 = "Capisco. Va bene, allora. Grazie, amico!";
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			DialogExit();
			AddQuestRecord("Tieyasal", "3");
			npchar.quest.tieyasal = "true";
			pchar.quest.Tieyasal_ITAttack.win_condition.l1 = "location";
			pchar.quest.Tieyasal_ITAttack.win_condition.l1.location = "Bermudes";
			pchar.quest.Tieyasal_ITAttack.function = "Tieyasal_CreateITShips";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

int iClockSP4PseudoGlobal = SOUND_INVALID_ID;

void ProcessDialogEvent()
{
	ref NPChar, sld, realShip;
	aref Link, NextDiag, arTmp;
	int i, n, NextMonth, idx;
	string sTemp, sStr, Month, NationName, shipType;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	if (HasSubStr(Dialog.CurrentNode, "chosenIdx/"))
	{
		Dialog.tmpIdx = FindStringAfterChar(Dialog.CurrentNode, "/");
		Dialog.CurrentNode = FindStringBeforeChar(Dialog.CurrentNode, "/");
	}

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Что вам надо?";
			link.l1 = "Ничего.";
			link.l1.go = "exit";
		break;
		
		// Диалог с Йоханом
		case "ClockTower_Johan_1":
			dialog.text = "Fermatevi, "+GetTitle(NPChar, true)+". Oltre non si passa.";
			link.l1 = "Perché?";
			link.l1.go = "ClockTower_Johan_2";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Johan_2":
			dialog.text = "Vedete quella torre? Ufficio della Compagnia Olandese delle Indie Occidentali. Dipartimento di registrazione navale e archivio. Ingresso solo su appuntamento.";
			link.l1 = "E come si ottiene un appuntamento?";
			link.l1.go = "ClockTower_Johan_3";
		break;

		case "ClockTower_Johan_3":
			dialog.text = "Chi deve sapere, sa. Il mynheer direttore non lavora con chiunque.";
			link.l1 = "'Mynheer direttore'? Chi sarebbe?";
			link.l1.go = "ClockTower_Johan_4";
		break;

		case "ClockTower_Johan_4":
			dialog.text = "L'amministratore van Doorn. Forse non è esattamente un direttore, ma tutti lo chiamano così. Lavora qui da dieci anni — ha messo ordine in tutto. Ora tutte le navi dei Caraibi passano dal suo ufficio.";
			link.l1 = "Tutte le navi? Anche quelle da guerra?";
			link.l1.go = "ClockTower_Johan_5";
		break;

		case "ClockTower_Johan_5":
			dialog.text = "Solo le navi migliori e i capitani più ricchi. Essere un cliente del nostro ufficio è un grande onore!";
			link.l1 = "Che tipo di servizi offrite?";
			link.l1.go = "ClockTower_Johan_6";
		break;

		case "ClockTower_Johan_6":
			dialog.text = "Non mi è dato sapere i dettagli — io sorveglio soltanto l'ingresso. Però ho sentito che la gente esce soddisfatta.";
			link.l1 = "Impressionante.";
			link.l1.go = "ClockTower_Johan_7";
		break;

		case "ClockTower_Johan_7":
			dialog.text = "Vi dirò un'altra cosa. Vedete quell'orologio? Una meraviglia europea — non ne troverete uno simile in questo angolo sperduto. Il mynheer direttore se ne occupa personalmente.";
			link.l1 = "Forse potremmo trovare un accordo?";
			link.l1.go = "ClockTower_Johan_8_1";
			link.l2 = "Non c'è davvero niente che posso fare per entrare?";
			link.l2.go = "ClockTower_Johan_8_2";
		break;

		case "ClockTower_Johan_8_1":
			dialog.text = "Non accetto tangenti!";
			link.l1 = "Mi scusi. Lei è un bravo uomo. Come si chiama?";
			link.l1.go = "ClockTower_Johan_9";
		break;

		case "ClockTower_Johan_9":
			dialog.text = ""+npchar.name+"... Sentite... Capisco che non siete di qui. Ma qui c'è ordine. Il mynheer direttore dice sempre: mostra debolezza una volta, e la nostra torre crolla. Volete entrare? Aiutate la città — e vi noteranno.";
			link.l1 = "Ho capito. Arrivederci, soldato.";
			link.l1.go = "ClockTower_Johan_11";
		break;

		case "ClockTower_Johan_8_2":
			dialog.text = "Beh, non saprei. Il mynheer direttore premi gli amici di Willemstad. Aiutate la città — e vi noteranno. Capisco che non siete di qui. Ma qui c'è ordine. Il mynheer direttore dice sempre: mostra debolezza una volta, e la nostra torre crolla.";
			link.l1 = "Ho capito. E lei come si chiama?";
			link.l1.go = "ClockTower_Johan_10";
		break;

		case "ClockTower_Johan_10":
			dialog.text = ""+npchar.name+", "+GetTitle(NPChar, true)+".";
			link.l1 = "Io sono "+GetTitle(NPChar, false)+" "+GetFullName(pchar)+". Arrivederci, soldato.";
			link.l1.go = "ClockTower_Johan_11";
		break;
		
		case "ClockTower_Johan_11":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_Quest_1");
		break;
		
		case "ClockTower_Johan_repeat":
			if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) >= 51)
			{
				dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+"!";
				link.l1 = "È successo qualcosa?";
				link.l1.go = "ClockTower_Johan_22";
				Notification_ReputationNation(true, 51, HOLLAND);
			}
			else 
			{
				dialog.text = ""+Greeting(true)+", "+GetTitle(NPChar, true)+". Posso aiutarla in qualcosa?";
				link.l1 = "No, "+npchar.name+". Continua.";
				link.l1.go = "exit";
				NextDiag.TempNode = "ClockTower_Johan_repeat";
				Notification_ReputationNation(false, 51, HOLLAND);
			}
		break;
		
		case "ClockTower_Johan_21":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+"!";
			link.l1 = "È successo qualcosa?";
			link.l1.go = "ClockTower_Johan_22";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Johan_22":
			dialog.text = "Congratulazioni. Avete un appuntamento fissato.";
			link.l1 = "Un appuntamento? Con chi?";
			link.l1.go = "ClockTower_Johan_23";
		break;

		case "ClockTower_Johan_23":
			dialog.text = "Con il vice del mynheer direttore. Ha saputo del vostro aiuto alla città e mi ha ordinato di invitarvi.";
			link.l1 = "E il direttore in persona?";
			link.l1.go = "ClockTower_Johan_24";
		break;

		case "ClockTower_Johan_24":
			dialog.text = "Ehm... Non sono autorizzato a dirvi nulla al riguardo. Buona fortuna là dentro, mynheer capitano.";
			link.l1 = "Grazie.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_InvitationToTheTower");
		break;
		
		// Диалог с Маартеном Виссером, заместителем директора
		case "ClockTower_Visser_1":
			dialog.text = "Benvenuto al dipartimento di registrazione navale della COIOC. "+UpperFirst(GetTitle(NPChar, false))+"?..";
			link.l1 = ""+GetFullName(pchar)+".";
			link.l1.go = "ClockTower_Visser_2";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Visser_2":
			dialog.text = ""+GetFullName(NPChar)+", vicedirettore.\n"+
						 "Ho sentito che siete stati di grande aiuto a Willemstad. Forse il nostro ufficio può essere utile anche a voi.";
			link.l1 = "È per questo che sono qui.";
			link.l1.go = "ClockTower_Visser_3_1";
			link.l2 = "Sono felice di aver potuto essere utile alla capitale di Curaçao.";
			link.l2.go = "ClockTower_Visser_3_2";
		break;

		case "ClockTower_Visser_3_1":
			dialog.text = "Qualsiasi capitano — francese, spagnolo, olandese — può commissionarci un'ispezione navale. Controlliamo l'attrezzatura, i cannoni, il sartiame. Troviamo i punti deboli, diamo raccomandazioni.";
			link.l1 = "";
			link.l1.go = "ClockTower_Visser_4";
		break;

		case "ClockTower_Visser_3_2":
			dialog.text = "Qualsiasi capitano — francese, spagnolo, olandese — può commissionarci un'ispezione navale. Controlliamo l'attrezzatura, i cannoni, il sartiame. Troviamo i punti deboli, diamo raccomandazioni.";
			link.l1 = "";
			link.l1.go = "ClockTower_Visser_4";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;

		case "ClockTower_Visser_4":
			dialog.text = "E se un'ispezione non basta, possiamo anche procurare nuovi documenti di bordo. In altre parole, il lavoro del nostro ufficio migliorerà la vostra nave — senza sprecare mogano e seta preziosi.";
			link.l1 = "Come è possibile?";
			link.l1.go = "ClockTower_Visser_4_1";
		break;

		case "ClockTower_Visser_4_1":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+"? Non avete idea di quanto sia potente il luogo in cui siete entrato, e quanto può fare un semplice tratto di penna.";
			link.l1 = "Per dobloni, immagino?";
			link.l1.go = "ClockTower_Visser_5";
		break;

		case "ClockTower_Visser_5":
			dialog.text = "Naturalmente. I nostri servizi non sono economici e dipendono dalle dimensioni della vostra nave. Ma si ripagano sempre. Un capitano che è passato da noi raramente fallisce\n"+
						 "Tuttavia, non prendiamo solo il vostro oro — vi diamo anche la possibilità di guadagnarlo. I pirati si sono moltiplicati a tal punto che persino nelle Piccole Antille i capitani devono allestire squadre per scacciare questi parassiti. Portate prove dell'eliminazione — e riceverete il pagamento negli stessi dobloni.";
			link.l1 = "Che tipo di prove?";
			link.l1.go = "ClockTower_Visser_6";
		break;

		case "ClockTower_Visser_6":
			dialog.text = "I giornali di bordo. Persino quella feccia è costretta a tenere una qualche documentazione — altrimenti non si può comandare nemmeno un lugger come si deve. Oltre a essere prova assoluta di malefatte, i giornali trovano sempre posto nei nostri archivi. Utili nelle controversie assicurative\n"+
						 "Se siete interessati ai nostri servizi, si è liberato un posto nella nostra lista clienti — uno dei capitani ha recentemente concluso la sua collaborazione. Completate il lavoro — e il posto sarà vostro.";
			link.l1 = "Perché tante complicazioni? I miei dobloni non bastano?";
			link.l1.go = "ClockTower_Visser_7";
		break;

		case "ClockTower_Visser_7":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+", Operiamo sulla qualità, non sulla quantità. Ogni cliente del nostro ufficio riceve il miglior servizio e l'attenzione personale del mynheer direttore in persona. E quest'ultimo, credetemi, costa somme considerevoli persino per la nostra compagnia tutt'altro che povera. Dato che ci sono solo trenta giorni in un mese, possiamo permetterci solo trenta clienti.";
			link.l1 = "Cosa bisogna fare?";
			link.l1.go = "ClockTower_Visser_8";
		break;

		case "ClockTower_Visser_8":
			dialog.text = "Portate cinque giornali di bordo pirata — questo proverà la vostra efficacia. La ricompensa dipende da quanto fossero pericolosi i loro proprietari.";
			link.l1 = "Molto bene. Lo farò.";
			link.l1.go = "ClockTower_Visser_9_1";
			link.l2 = "Devo pensarci.";
			link.l2.go = "ClockTower_Visser_9_2";
			link.l3 = "E dov'è il direttore in persona?";
			link.l3.go = "ClockTower_Visser_9_3";
		break;

		case "ClockTower_Visser_9_1":
			dialog.text = "Eccellente. Attendo i risultati e spero in una collaborazione.";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "ClockTower_Visser_13_exit";
		break;

		case "ClockTower_Visser_9_2":
			dialog.text = "Come desiderate. L'offerta rimane valida. Ma il vostro posto potrebbe essere occupato più velocemente di quanto pensiate.";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "ClockTower_Visser_13_exit";
		break;

		case "ClockTower_Visser_9_3":
			dialog.text = "In mare. Il mynheer van Doorn combina la gestione dell'ufficio con il comando dell'ammiraglia.";
			link.l1 = "Come ci riesce?";
			link.l1.go = "ClockTower_Visser_10";
		break;

		case "ClockTower_Visser_10":
			dialog.text = "Lavora diciotto ore al giorno. Dorme qui, nell'ufficio al piano di sopra. Dice che dormire è una perdita di tempo. Quattro ore gli bastano.";
			link.l1 = "E il frastuono di quegli enormi meccanismi dell'orologio? Come si può dormire qui?";
			link.l1.go = "ClockTower_Visser_11";
		break;

		case "ClockTower_Visser_11":
			dialog.text = "Potrete chiederglielo voi stesso e magari imparare qualcosa. È sempre felice di parlare con i clienti. Ci capiamo?";
			link.l1 = "Perfettamente.";
			link.l1.go = "ClockTower_Visser_12";
			link.l2 = "Non del tutto...";
			link.l2.go = "ClockTower_Visser_12";
		break;

		case "ClockTower_Visser_12":
			dialog.text = "Buona giornata, "+GetTitle(NPChar, false)+".";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "ClockTower_Visser_13_exit";
		break;

		case "ClockTower_Visser_13_exit":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_Quest_2");
		break;
		
		// Йохан спрашивает про журналы
		case "ClockTower_Johan_31":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+"! Ha i registri con sé?";
			link.l1 = "Vedo che sei ben informato, Johan.";
			link.l1.go = "ClockTower_Johan_32";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Johan_32":
			if (!CheckAttribute(npchar, "questTemp.ClockTower_Johan_journal"))
			{
				dialog.text = "Ah! Questo non è il molo né le porte della città, e io non sono una semplice guardia di turno, ma un dipendente della compagnia.";
				npchar.questTemp.ClockTower_Johan_journal = true;
			}
			else
			{
				dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+"! Ha i registri con sé?";
			}
			if (ClockTower_JournalsQty() >= 5 || bBettaTestMode)
			{
				link.l1 = "Ho portato i registri. Mi fai passare?";
				link.l1.go = "ClockTower_Johan_33";
			}
			link.l2 = "Un'altra volta.";
			link.l2.go = "ClockTower_Johan_34";
		break;

		case "ClockTower_Johan_33":
			dialog.text = "Contento che sia andato tutto bene! Vada pure, la stanno aspettando.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_InvitationToTheTower_2");
		break;

		case "ClockTower_Johan_34":
			dialog.text = "Buona giornata, mynheer capitano.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ClockTower_Johan_32";
		break;
		
		case "ClockTower_Visser_21":
			dialog.text = "Capitano! Siete tornato. Avete portato i giornali?";
			if (ClockTower_JournalsQty() >= 5 || bBettaTestMode)
			{
				link.l1 = "Sì. Tutti e cinque.";
				link.l1.go = "ClockTower_Visser_22";
				DelLandQuestMark(npchar);
			}
			else
			{
				link.l1 = "Un'altra volta.";
				link.l1.go = "exit";
				NextDiag.TempNode = "ClockTower_Visser_21";
			}
		break;

		case "ClockTower_Visser_22":
			dialog.text = "Eccellente. Fateli vedere.\n"+
						"Sì, tutto in ordine. Sono vere navi pirata. Ottimo lavoro. Vi spettano #количество_дублонов dobloni.\n"+
						"Vi prego, prendeteli. E firmate qui, per favore.";
			link.l1 = "Quindi sono nella lista?";
			link.l1.go = "ClockTower_Visser_23";
			//RemoveItemsFromPCharTotal("ClockTower_PirateJournal", 5);        
		break;

		case "ClockTower_Visser_23":
			dialog.text = "Quasi. Prima dobbiamo compilare i documenti. Ci vorranno alcuni minuti.\n"+
						"Nome completo?";
			link.l1 = ""+GetFullName(pchar)+".";
			link.l1.go = "ClockTower_Visser_24";
		break;

		case "ClockTower_Visser_24":
			dialog.text = "Nazionalità?";
			link.l1 = ""+NationNameNominative(sti(pchar.baseNation))+".";
			link.l1.go = "ClockTower_Visser_25";
		break;

		case "ClockTower_Visser_25":
			dialog.text = "Nome della vostra nave?";
			link.l1 = ""+PChar.Ship.Name+".";
			link.l1.go = "ClockTower_Visser_26";
		break;

		case "ClockTower_Visser_26":
			shipType = XI_ConvertString(GetShipTypeName(pchar));
			dialog.text = "Tipo di nave?";
			link.l1 = ""+shipType+".";
			link.l1.go = "ClockTower_Visser_27";
		break;

		case "ClockTower_Visser_27":
			dialog.text = "Numero di cannoni?";
			link.l1 = ""+GetCannonQuantity(pchar)+".";
			link.l1.go = "ClockTower_Visser_28";
		break;

		case "ClockTower_Visser_28":
			dialog.text = "Dimensione dell'equipaggio?";
			link.l1 = ""+GetMaxCrewQuantity(pchar)+".";
			link.l1.go = "ClockTower_Visser_29";
		break;

		case "ClockTower_Visser_29":
			dialog.text = "Bene. Ora firmate qui. Qui. E anche qui.";
			link.l1 = "È tutto?";
			link.l1.go = "ClockTower_Visser_30";
		break;

		case "ClockTower_Visser_30":
			dialog.text = "Quasi. Resta solo di inserirvi nel registro. Naturalmente, il mynheer direttore deve conoscervi personalmente prima... Ma è una formalità — sono autorizzato ad accettare nuovi clienti.\n"+
					"...Ma mi sto distraendo. Permettetemi di rifamiliarvi ancora una volta con la nostra lista di servizi.\n"+
					"Assicurazione. Costosa, ma nessuna squadra navale toccherà le navi assicurate dalla compagnia. Potrete tenere quante navi volete nelle amministrazioni portuali senza timore di perderle durante l'assedio di una colonia.\n"+
					"Ispezione navale — aumenta leggermente tutte le caratteristiche senza spendere beni strategici. Controlleremo tutto: attrezzature, stiva, alloggi dell'equipaggio. Daremo raccomandazioni. Il prezzo dipende dalle dimensioni della nave.\n"+
					"Registrazione nei nostri archivi. Incrementa la sicurezza della nave nella regione dei Caraibi, in modo che i cacciatori di taglie, i pirati e i militari penseranno due volte prima di attaccarvi.\n"+
					"Ispezione e registrazione possono essere effettuate solo una volta per una nave specifica. Quindi se avete già investito, datevi cura della vostra nave. Non immaginate quanto infastidisce i miei superiori quando i capitani trattano le proprie navi negligentemente e le cambiano come fossero guanti!\n"+
					"Ma mi sto distraendo di nuovo. Ora, riguardo ai servizi ripetibili...\n"+
					"Cambio di documenti. Sapete che le navi possono avere diverse specializzazioni. Ma non sospettate nemmeno che ciò dipenda principalmente da come è documentata la nave. Se non vi piace che la vostra nave da guerra sia documentata per l'assedio dei forti, sapete a chi rivolgervi.\n"+
					"Be', per quanto riguarda le ricompense per la consegna dei giornali di bordo pirata che avete già sentito... Più pericoloso è il pirata, più pagheremo per il suo giornale.";
			link.l1 = "Impressionante. Devo dire, mynheer Visser, che il vostro ufficio è davvero...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_AmsterdamInTheHarbor");
		break;

		case "ClockTower_Visser_31":
			dialog.text = "'"+GetShipName("Amsterdam")+"' nel porto! Il mynheer direttore è tornato!";
			link.l1 = "";
			link.l1.go = "ClockTower_Visser_31_add";
			CharacterTurnByChr(CharacterFromID("ClockTower_Johan_Clone"), CharacterFromID("ClockTower_Visser"));
			ClockTower_AmsterdamInTheHarbor_2();
		break;

		case "ClockTower_Visser_31_add":
			StartInstantDialogNoType("ClockTower_Visser", "ClockTower_Visser_32", "Quest\ShipsPack\ClockTower_dialog.c");
		break;

		case "ClockTower_Visser_32":
			dialog.text = "Cosa?! Già?! Ma doveva tornare solo fra tre giorni!";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_32_add";
		break;

		case "ClockTower_Visser_32_add":
			StartInstantDialog("ClockTower_Johan_clone", "ClockTower_Visser_33", "Quest\ShipsPack\ClockTower_dialog.c");
		break;

		case "ClockTower_Visser_33":
			dialog.text = "Il mynheer direttore è già sbarcato! Viene direttamente qui!";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_33_add";
			CharacterTurnByChr(CharacterFromID("ClockTower_Johan_Clone"), CharacterFromID("ClockTower_Visser"));
		break;

		case "ClockTower_Visser_33_add":
			StartInstantDialogNoType("ClockTower_Visser", "ClockTower_Visser_34", "Quest\ShipsPack\ClockTower_dialog.c");
		break;

		case "ClockTower_Visser_34":
			dialog.text = "Dio mio... Se vi vede...";
			link.l1 = "Qual è il problema? Avete appena detto che siete autorizzato ad accettare nuovi clienti.";
			link.l1.go = "ClockTower_Visser_35";
		break;

		case "ClockTower_Visser_35":
			dialog.text = "Lo sono! Ma non gli piace quando... Non importa. Capitano, aspettate fuori. Vicino all'ingresso. Il mynheer direttore vorrà parlare con voi.";
			link.l1 = "Con me?";
			link.l1.go = "ClockTower_Visser_36";
		break;

		case "ClockTower_Visser_36":
			dialog.text = "Esamina personalmente ogni nuovo cliente. Sempre. Andate, in fretta!";
			link.l1 = "Non renderò indietro i dobloni per i giornali!";
			link.l1.go = "ClockTower_Visser_36_1";
			link.l2 = "Peccato, sarei rimasto ad ascoltare.";
			link.l2.go = "ClockTower_Visser_36_2";
		break;
		
		case "ClockTower_Visser_36_1":
			DialogExit();
			AddCharacterExpToSkill(pchar, "Commerce", 100);
			AddDialogExitQuestFunction("ClockTower_AmsterdamInTheHarbor_Kino_1");
		break;
		
		case "ClockTower_Visser_36_2":
			DialogExit();
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddDialogExitQuestFunction("ClockTower_AmsterdamInTheHarbor_Kino_1");
		break;
		
		// диалог с Йоханом, после того как мы вышли из башни
		case "ClockTower_Johan_41":
			dialog.text = "...";
			link.l1 = "Cos'è stato, Johan?";
			link.l1.go = "ClockTower_Johan_42";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Johan_42":
			dialog.text = "Il mynheer direttore è tornato.";
			link.l1 = "E cosa c'è di così terribile?";
			link.l1.go = "ClockTower_Johan_43";
		break;

		case "ClockTower_Johan_43":
			dialog.text = "Niente di terribile! È solo che... Al mynheer direttore non piacciono le sorprese. Tutto deve andare secondo i piani. E qui c'è un nuovo cliente che non ha ancora controllato.";
			link.l1 = "Maarten ha detto che aveva l'autorità per iscrivermi al registro.";
			link.l1.go = "ClockTower_Johan_44";
		break;

		case "ClockTower_Johan_44":
			dialog.text = "No, non è questo il punto. Il mynheer direttore semplicemente... beh, vuole controllare tutto da solo. Ogni minimo dettaglio. Dice che altrimenti tutto crollerà. Vedrete, ora comincerà di nuovo a preoccuparsi del suo orologio.";
			link.l1 = "Cosa?";
			link.l1.go = "ClockTower_Johan_45";
		break;

		case "ClockTower_Johan_45":
			dialog.text = "Mynheer van Doorn, quando si irrita, ferma l'orologio e inizia a smanettarci. A volte la città rimane senza ora per mezza giornata. E succede...";
			link.l1 = "...";
			link.l1.go = "ClockTower_Johan_45_1";
		break;

		case "ClockTower_Johan_45_1":
			dialog.text = "Oh... Sentite? È cominciato.";
			link.l1 = "Il capo è tornato. Tutto come al solito.";
			link.l1.go = "ClockTower_Johan_46_1";
			link.l2 = "Eccome se lo sento. Stanno facendo il culo a Maarten.";
			link.l2.go = "ClockTower_Johan_46_2";
			iClockSP4PseudoGlobal = ClockTower_PlaySound_rh2("Location/SP4_quest2");
		break;

		case "ClockTower_Johan_46_1":
			dialog.text = "Purtroppo, ormai è diventato normale.";
			link.l1 = "...";
			link.l1.go = "ClockTower_Johan_47";

			if (iClockSP4PseudoGlobal != SOUND_INVALID_ID)
				SendMessage(Sound, "lll", MSG_SOUND_EVENT_STOP, iClockSP4PseudoGlobal, 0);
			ClockTower_PlaySound_rh2("Location/SP4_quest3");
		break;

		case "ClockTower_Johan_46_2":
			dialog.text = "Non dovreste dirlo. Non è giusto, se volete la mia opinione.";
			link.l1 = "...";
			link.l1.go = "ClockTower_Johan_47";	
			ChangeCharacterComplexReputation(pchar, "nobility", -2);

			if (iClockSP4PseudoGlobal != SOUND_INVALID_ID)
				SendMessage(Sound, "lll", MSG_SOUND_EVENT_STOP, iClockSP4PseudoGlobal, 0);
			ClockTower_PlaySound_rh2("Location/SP4_quest3");
		break;

		case "ClockTower_Johan_47":
			dialog.text = "Sembra essersi calmato. Vi inviteranno a entrare tra poco.";
			link.l1 = "Avrò problemi?";
			link.l1.go = "ClockTower_Johan_48";
		break;

		case "ClockTower_Johan_48":
			dialog.text = "Non preoccupatevi. Non avete fatto niente di male.";
			link.l1 = "Che sollievo.";
			link.l1.go = "ClockTower_Johan_49";
		break;

		case "ClockTower_Johan_49":
			dialog.text = "Ma dai! Il mynheer direttore a volte può essere eccessivamente severo... Ma è generoso e cortese... Oh, ve l'avevo detto!";
			link.l1 = "...";
			link.l1.go = "ClockTower_Johan_50";
		break;

		case "ClockTower_Johan_50":
			dialog.text = "Oh, ve l'avevo detto!";
			link.l1 = "...";
			link.l1.go = "exit";
			ClockTower_VisserComingTowardsUs();
		break;

		case "ClockTower_Visser_37":
			dialog.text = "Il mynheer direttore vi aspetta dentro.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_VisserComingTowardsUs_2");
			DelLandQuestMark(npchar);
		break;
		
		// Первое знакомство с ван Дорном
		case "ClockTower_VanDoorn_1":
			NationName = GetSexPhrase(""+NationNameMan(sti(pchar.baseNation))+"",""+NationNameWoman(sti(pchar.baseNation))+"");
			shipType = LowerFirst(XI_ConvertString(GetShipTypeName(pchar)));
			dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+" "+GetFullName(pchar)+", "+NationName+". La vostra nave — '"+PChar.Ship.Name+"', "+shipType+". "+GetCannonQuantity(pchar)+" cannoni e "+GetMaxCrewQuantity(pchar)+" membri d'equipaggio.";
			link.l1 = "Tutto corretto.";
			link.l1.go = "ClockTower_VanDoorn_2";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_VanDoorn_2":
			shipType = XI_ConvertString(GetShipTypeName(npchar));
			dialog.text = "È ingiusto che io sappia tutto di voi mentre voi non sapete nulla di me tranne i pettegolezzi di Johan. Hendrik van Doorn. Direttore del dipartimento di registrazione della Compagnia Olandese delle Indie Occidentali nei Caraibi. Comandante della fregata Amsterdam. "+shipType+". "+GetCannonQuantity(npchar)+" cannoni e "+GetMaxCrewQuantity(npchar)+" membri d'equipaggio.";
			link.l1 = "Piacere di conoscervi.";
			link.l1.go = "ClockTower_VanDoorn_3";
		break;

		case "ClockTower_VanDoorn_3":
			dialog.text = "Avete ottenuto cinque giornali di bordo pirata. Il mio vice vi ha tenuto in grande considerazione, vi ha iscritto al registro clienti e vi ha familiarizzato con i servizi del mio ufficio.\n"+
						"Ma la decisione finale sull'ammissione è sempre mia. Personalmente. Dopo un colloquio. Maarten poteva proporre un candidato — niente di più.";
			link.l1 = "Allora, cominciamo.";
			link.l1.go = "ClockTower_VanDoorn_4";
		break;

		case "ClockTower_VanDoorn_4":
			if (!CheckAttribute(npchar, "ClockTower_option"))
			{
				dialog.text = "Ho bisogno di capitani che combattono efficacemente i pirati pur essendo abbastanza di successo commercialmente da potersi permettere i nostri servizi. Soddisfate questi criteri?";
			}
			else dialog.text = "";
			if (!CheckAttribute(npchar, "ClockTower_option_1") && CheckAttribute(pchar, "questTemp.DiegoDeLanda_Memento"))
			{
				link.l1 = "Ho distrutto Mortimer Grimm. Capitano del brigantino Memento.";
				link.l1.go = "ClockTower_VanDoorn_option_1";
			}
			if (!CheckAttribute(npchar, "ClockTower_option_2") && CheckAttribute(pchar, "questTemp.DiegoDeLanda_LadyBeth"))
			{
				link.l2 = "Credo che la vostra compagnia abbia apprezzato molto la mia vittoria su Albert Blackwood. Il brigantino goletta Lady Beth era un avversario formidabile.";
				link.l2.go = "ClockTower_VanDoorn_option_2";
			}
			if (!CheckAttribute(npchar, "ClockTower_option_3") && CheckAttribute(pchar, "questTemp.DiegoDeLanda_SantaMisericordia"))
			{
				link.l3 = "Fernando de Alamida non era un pirata, ma...";
				link.l3.go = "ClockTower_VanDoorn_option_3";
			}
			if (!CheckAttribute(npchar, "ClockTower_option_4") && CheckAttribute(pchar, "questTemp.KhaelRoa"))
			{
				link.l4 = "Ho sconfitto il terrore di tutti coloro che navigano. Dovete saperlo.";
				link.l4.go = "ClockTower_VanDoorn_option_4";
			}
			if (!CheckAttribute(npchar, "ClockTower_option_5") && GetCharacterShipClass(PChar) <= 3)
			{
				link.l5 = "Avete appena iscritto la mia nave al registro. Pensate che un capitano incompetente potrebbe mantenerla?";
				link.l5.go = "ClockTower_VanDoorn_option_5";
			}
			if (!CheckAttribute(npchar, "ClockTower_option_6") && sti(pchar.Money) >= 1000000)
			{
				link.l6 = "Me la cavo benissimo, e i soldi crescono sugli alberi nei Caraibi.";
				link.l6.go = "ClockTower_VanDoorn_option_6";
			}
			link.l7 = "Mynheer Visser ha già verificato la mia competenza. La valutazione del vostro stesso vice non è sufficiente?";
			link.l7.go = "ClockTower_VanDoorn_5";
			npchar.ClockTower_option = true;
		break;

		case "ClockTower_VanDoorn_option_1":
			dialog.text = "Grimm? La nostra organizzazione non ha mai avuto lamentele su Grimm, anzi tutto il contrario. Ma colui che ha preso il suo posto... So chi era e con quale scopo arrivò originariamente nei Caraibi. Tali malefatte non hanno prescrizione, e sono lieto che abbiate punito il criminale e vero nemico del mio paese.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_1 = true;
		break;

		case "ClockTower_VanDoorn_option_2":
			dialog.text = "Se ricordo bene il rapporto sull'incidente alle Cayman, non avete avuto modo di verificarlo. A mio parere, la situazione non è del tutto chiara, ma la vostra vittoria è stata indubbiamente competente.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_2 = true;
		break;

		case "ClockTower_VanDoorn_option_3":
			dialog.text = "Ma avrebbe potuto diventare qualcosa di ben peggio, sì davvero. Un nemico degno, anche se non ha perso contro di voi ma contro i suoi ingrati superiori. Sono olandese, quindi so di cosa parlo quando si tratta di guerra con la Castiglia.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_3 = true;
		break;

		case "ClockTower_VanDoorn_option_4":
			dialog.text = "'"+GetShipName("Flying Heart")+"'. Mi sorprende ancora che la gente onesta non si disperda alla vista di quella mostruosità che entra in porto. Molte cose di questa storia mi sorprendono, capitano. Ma un giorno troverà il suo posto nei nostri libri e perderà tutto il suo fascino. Quanto a voi... vi siete immortalato.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_4 = true;
		break;

		case "ClockTower_VanDoorn_option_5":
			dialog.text = "Vi sorprendereste. Ma nel vostro caso, non ci sono dubbi, è vero.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_5 = true;
		break;

		case "ClockTower_VanDoorn_option_6":
			dialog.text = "E quindi non valgono nulla. A meno che non siano dobloni, ovviamente.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_6 = true;
		break;

		case "ClockTower_VanDoorn_5":
			dialog.text = "\nSiete approvato per i servizi dell'ufficio. Benvenuto nel registro clienti della stimata Compagnia Olandese delle Indie Occidentali.";
			link.l1 = "Grazie.";
			link.l1.go = "ClockTower_VanDoorn_6";
		break;

		case "ClockTower_VanDoorn_6":
			dialog.text = "È una collaborazione reciprocamente vantaggiosa. Ottenete l'accesso ai migliori servizi dei Caraibi. Noi otteniamo un partner affidabile.";
			link.l1 = "Bene.";
			link.l1.go = "ClockTower_VanDoorn_7";
		break;

		case "ClockTower_VanDoorn_7":
			dialog.text = "Aspettate! Sentite?";
			link.l1 = "Non sento nulla.";
			link.l1.go = "ClockTower_VanDoorn_8";
			// sound stops
			i = FindSoundEventId("Location/clocks_mechanism_inside");
			SetSoundEventPauseState(i, true);
			DelEventHandler("NextHour", "Villemstad_BigClock_Above");
		break;

		case "ClockTower_VanDoorn_8":
			dialog.text = "Proprio questo è il punto! È bastato partire per una settimana...";
			link.l1 = "Qualcosa non va?";
			link.l1.go = "ClockTower_VanDoorn_9";
		break;

		case "ClockTower_VanDoorn_9":
			dialog.text = "Con l'orologio. Devo controllare il meccanismo. Mi scuso. Questo... è importante.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_10";
		break;

		case "ClockTower_VanDoorn_10":
			if (!CheckAttribute(npchar, "ClockTower_question"))
			{
				dialog.text = "Sembra tutto a posto ora. Ancora le mie scuse. Avete domande?";
				LAi_Fade("", "");
				// sound returns
				i = FindSoundEventId("Location/clocks_mechanism_inside");
				SetSoundEventPauseState(i, false);
				SetEventHandler("NextHour", "Villemstad_BigClock_Above", 0);
			}
			else dialog.text = "Altre domande?";
			if (!CheckAttribute(npchar, "ClockTower_question_1"))
			{
				link.l1 = "Il vostro vice ha spiegato i servizi dell'ufficio in dettaglio. Come è possibile tutto questo?";
				link.l1.go = "ClockTower_VanDoorn_question_1";
			}
			if (!CheckAttribute(npchar, "ClockTower_question_2"))
			{
				link.l2 = "Come unite due posizioni? Capitano e direttore?";
				link.l2.go = "ClockTower_VanDoorn_question_2";
			}
			if (!CheckAttribute(npchar, "ClockTower_question_3"))
			{
				link.l3 = "Come lavorate in tali condizioni? Il frastuono dei meccanismi dell'orologio, l'oscurità e le finestre coperte da pesanti tende.";
				link.l3.go = "ClockTower_VanDoorn_question_3";
			}
			link.l4 = "No, grazie per il vostro tempo. E per quanto riguarda i servizi dell'ufficio?";
			link.l4.go = "ClockTower_VanDoorn_11";
			npchar.ClockTower_question = true;
		break;

		case "ClockTower_VanDoorn_question_1":
			dialog.text = "Non c'è stregoneria qui, "+GetTitle(NPChar, false)+". Penna e inchiostro governano il mondo. La Chiesa registra nascita, battesimo, matrimonio e morte di una persona. Cambia anche solo una riga — e il suo destino cambia. Una nave è leggermente più complessa, ma anche nel suo caso un tratto di penna cambia molto. Non lo nasconderò, sono orgoglioso di ciò che ho raggiunto. Eppure so ancora che potrebbe essere meglio. E se registrassimo nei libri contabili non solo navi e persone, ma un mondo intero?";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_10";
			npchar.ClockTower_question_1 = true;
		break;

		case "ClockTower_VanDoorn_question_2":
			dialog.text = "Perché qualcuno deve farlo. Il precedente capitano dell'Amsterdam morì in battaglia contro un gruppo di Antigua. La compagnia non trovò un degno sostituto. Mi sono offerto io. Ho seguito l'addestramento. Superato gli esami. Ottenuto la patente\n"+
			"Sì, sono un pessimo capitano. Molto peggiore di voi — questo è certo. Ma un buon dirigente può comandare qualsiasi cosa, non solo una nave. È difficile imparare a comandare tre persone. Ma una volta imparato, puoi comandarne tremila. Un ufficio, una nave, una città o persino una vasta compagnia — non c'è limite, finché trovi persone di talento e ti fidi che ti rappresentino... Quest'ultimo è il più difficile. Una vera maledizione.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_10";
			npchar.ClockTower_question_2 = true;
		break;

		case "ClockTower_VanDoorn_question_3":
			dialog.text = "E c'è a malapena aria da respirare. "+UpperFirst(GetTitle(NPChar, false))+", una persona plasma il proprio ambiente. Qui niente e nessuno mi distrae, tutto è a portata di mano e soggetto solo a me e al tempo. Se potessi, comunicherei con il mondo esterno esclusivamente tramite carta. Purtroppo, è impossibile. E non prendetevela personalmente, "+GetTitle(NPChar, false)+". Meglio essere soli, ma non in solitudine. Se capite cosa intendo.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_10";
			npchar.ClockTower_question_3 = true;
		break;

		case "ClockTower_VanDoorn_11":
			// pchar.quest.ClockTower.date = rand(27)+1;
			if (pchar.quest.ClockTower.date <= GetDataDay())
			{
				NextMonth = GetDataMonth() + 1;
				if (NextMonth == 13) NextMonth = 1;
			}
			else NextMonth = GetDataMonth();
			Month = XI_ConvertString("MonthGen_" + NextMonth);
			dialog.text = "Riceviamo solo su appuntamento. Siete in programma per... "+pchar.quest.ClockTower.date+" "+month+". Se non venite nel giorno stabilito, non importa. Contattate Johan, e vi comunicherà il prossimo appuntamento disponibile.";
			link.l1 = "Perché tante complicazioni?";
			link.l1.go = "ClockTower_VanDoorn_12";
		break;

		case "ClockTower_VanDoorn_12":
			if (pchar.quest.ClockTower.date <= GetDataDay())
			{
				NextMonth = GetDataMonth() + 1;
				if (NextMonth == 13) NextMonth = 1;
			}
			else NextMonth = GetDataMonth();
			Month = XI_ConvertString("MonthGen_" + NextMonth);
			dialog.text = "Il nostro lavoro è costoso perché compiamo veri miracoli e portiamo grande beneficio ai nostri clienti. I conflitti di interesse sono impossibili, e pertanto dedichiamo un'intera giornata lavorativa alle esigenze di una persona specifica. Il vostro prossimo giorno disponibile: "+pchar.quest.ClockTower.date+" "+month+"\n"+
			"Se vedete Visser... Maarten ha agito correttamente nel proporre la vostra candidatura. Diteglielo. È un buon vice. Che non ne dubiti.";
			link.l1 = "Bene.";
			link.l1.go = "ClockTower_VanDoorn_13";
		break;

		case "ClockTower_VanDoorn_13":
			dialog.text = "Buona giornata, "+GetTitle(NPChar, false)+".";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_VanDoornInCabinet_3");
		break;
		
		case "ClockTower_Visser_41":
			dialog.text = "Come è andata?";
			link.l1 = "È stata una lunga giornata, ma van Doorn ha confermato la tua decisione.";
			link.l1.go = "ClockTower_Visser_42";
		break;

		case "ClockTower_Visser_42":
			dialog.text = "Grazie a Dio. Quindi ho fatto tutto bene.";
			link.l1 = "Mi ha chiesto di dirti che sei un buon vice.";
			link.l1.go = "ClockTower_Visser_43";
		break;

		case "ClockTower_Visser_43":
			dialog.text = "Davvero? Lui... l'ha detto?";
			link.l1 = "Sì. L'ha detto davvero.";
			link.l1.go = "ClockTower_Visser_44";
		break;

		case "ClockTower_Visser_44":
			dialog.text = "Maledizione. Non avrebbe dovuto dirlo. Ora mi sentirò un bastardo ingrato. Oppure aveva previsto tutto questo e ha calcolato ogni cosa?";
			link.l1 = "Mynheer vice, sei improvvisamente smesso di essere te stesso.";
			link.l1.go = "ClockTower_Visser_45";
		break;

		case "ClockTower_Visser_45":
			dialog.text = "Capitano, sono un uomo d'affari, e lo sei anche tu, quindi non perdiamo tempo.\n"+
						 "Il mynheer direttore non lavora più per noi da molto tempo.";
			link.l1 = "Come, scusa?!";
			link.l1.go = "ClockTower_Visser_46";
		break;

		case "ClockTower_Visser_46":
			dialog.text = "È venuto qui con un contratto e un solo obiettivo: organizzare il lavoro del dipartimento di registrazione navale. Ci è riuscito brillantemente, ha formato il suo successore, mi ha promosso... e basta.";
			link.l1 = "Come, basta?";
			link.l1.go = "ClockTower_Visser_47";
		break;

		case "ClockTower_Visser_47":
			dialog.text = "Il suo contratto è scaduto da tempo. Non sappiamo esattamente quando, ma siamo assolutamente certi che quest'uomo non ha più il diritto di mantenere la sua carica.";
			link.l1 = "Capisco. I pezzi grossi nell'ala centrale di questo edificio si innervosiscono.";
			link.l1.go = "ClockTower_Visser_48_1";
			link.l2 = "Capisco. Sei stanco di aspettare che ti liberi la poltrona.";
			link.l2.go = "ClockTower_Visser_48_2";
		break;

		case "ClockTower_Visser_48_1":
			dialog.text = "Esattamente! E non possono farci niente!";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_49";
		break;

		case "ClockTower_Visser_48_2":
			dialog.text = "Non mentirò. Sono davvero stanco. Dannazione, van Doorn mi ha promosso proprio perché lo sostituissi alla scadenza del contratto!";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_49";
		break;

		case "ClockTower_Visser_49":
			dialog.text = "Eppure non cercherei mai di scalzarlo da quella maledetta poltrona solo perché mi sento ingannato! Dio sa che sono grato e ammiro quest'uomo!";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_50";
		break;

		case "ClockTower_Visser_50":
			dialog.text = "No, mynheer. Van Doorn vuole sbarazzarsi dei nostri superiori comuni. Precisamente quelli che stanno dietro il muro della torre — nell'ala centrale di questo edificio! Ma nemmeno loro riescono a controllarlo!";
			link.l1 = "Cos'ha di difficile? Van Doorn non è certo più importante di Stuyvesant.";
			link.l1.go = "ClockTower_Visser_51";
		break;

		case "ClockTower_Visser_51":
			dialog.text = "Questa non è una nave né una corte reale, capitano. La nostra compagnia è un tipo di organizzazione completamente nuovo. Non si può semplicemente puntare il dito e licenziare una persona così preziosa.\n"+
						 "Primo, nessuno sa dove si trovi l'originale del contratto di van Doorn. Ergo, non ci sono motivi per il licenziamento. Cercheremmo di farlo, e lui invierebbe un esercito di avvocati, e finiremmo per dovergli dei soldi.\n"+
						 "Secondo, la direzione ha commesso un errore quando ha dato a van Doorn il brevetto per l'Amsterdam. Potrebbe essere un capitano mediocre, ma ha messo insieme un equipaggio che è il migliore dell'intera regione. Date un ordine, e i soldati scelti della Compagnia occuperanno questo edificio senza battere ciglio.\n"+
						 "Terzo, sua moglie lo adora. Non importa che non lo abbia visto per anni. La figlia stessa di De Witt è capace di molto per il suo amato marito. E il Consiglio dei Diciassette è costretto ad accettarlo.\n"+
						 "In altre parole, il direttorato pagherà molto generosamente il tuo aiuto. E conserverà i tuoi privilegi presso l'ufficio di registrazione navale.";
			link.l1 = "Impressionante. Sei davvero un uomo d'affari, Maarten. Mi stai vendendo un tradimento con lo stesso professionismo con cui fino a poco fa vendevi i servizi del tuo ufficio.";
			link.l1.go = "ClockTower_Visser_57";
		break;

		case "ClockTower_Visser_57":
			dialog.text = "Non è difficile quando van Doorn stesso ti ha insegnato l'arte della negoziazione e credi sinceramente in quello che dici.";
			link.l1 = "Quindi, cosa vuoi da me?";
			link.l1.go = "ClockTower_Visser_58";
		break;

		case "ClockTower_Visser_58":
			dialog.text = "Qualcosa che solo un estraneo può fare. Entra nell'ufficio di notte e trova il contratto originale di van Doorn. Mi assicurerò che le porte siano aperte.";
			link.l1 = "Perché non lo fai tu stesso? E cosa mi impedisce di andare subito a raccontarlo tutto al tuo superiore?";
			link.l1.go = "ClockTower_Visser_59";
		break;

		case "ClockTower_Visser_59":
			dialog.text = "Perché van Doorn ha l'abitudine di ricevere chiunque di notte, eccetto i dipendenti della compagnia. Nessuno si stupirà di vederti uscire da questa torre a un'ora insolita.";
			link.l1 = "";
			link.l1.go = "ClockTower_Visser_60";
		break;

		case "ClockTower_Visser_60":
			if (pchar.quest.ClockTower.date <= GetDataDay())
			{
				NextMonth = GetDataMonth() + 1;
				if (NextMonth == 13) NextMonth = 1;
			}
			else NextMonth = GetDataMonth();
			Month = XI_ConvertString("MonthGen_" + NextMonth);
			dialog.text = "Per quanto riguarda la tua minaccia... Non arriverai dal direttore ora, hai un appuntamento per un altro giorno. "+pchar.quest.ClockTower.date+" "+month+", giusto? A quel punto l'urgenza della notizia sarà un po' diminuita. E poi, il direttore non premi mai gli informatori. E protegge sempre i suoi dipendenti.";
			link.l1 = "Comodo per te.";
			link.l1.go = "ClockTower_Visser_61";
		break;

		case "ClockTower_Visser_61":
			dialog.text = "Non è un tradimento, capitano. Vogliamo semplicemente rispettare il contratto e proteggere la compagnia. E Willemstad, che hai tanto aiutato, tra l'altro.";
			link.l1 = "Tornerò su questa conversazione. Ma non prometto nulla.";
			link.l1.go = "ClockTower_Visser_62";
		break;

		case "ClockTower_Visser_62":
			dialog.text = "Non ti chiedo di più, capitano. Prima di tutto, sei nostro cliente. Comunque vada, sono molto orgoglioso di essere stato io a trovarti e iscriverti nel registro dell'ufficio.";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_63";
		break;

		case "ClockTower_Visser_63":
			dialog.text = "Puoi sempre trovarmi nell'ala centrale. Buona giornata.";
			link.l1 = "Ci vediamo.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_Quest_3");
		break;
		
		case "ClockTower_Visser_64":
			dialog.text = "Salve, "+GetTitle(NPChar, false)+". Ci sono novità?";
			link.l1 = "Niente ancora.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ClockTower_Visser_64";
		break;
		
		case "ClockTower_Johan_51":
			if (GetHour() >= 6 && GetHour() < 24)
			{
				if (pchar.quest.ClockTower.date <= GetDataDay())
				{
					NextMonth = GetDataMonth() + 1;
					if (NextMonth == 13) NextMonth = 1;
				}
				else NextMonth = GetDataMonth();
				Month = XI_ConvertString("MonthGen_" + NextMonth);
				if (pchar.quest.ClockTower.date == GetDataDay() && CheckAttribute(pchar, "questTemp.ClockTower_NoToday"))
				{
					if (!CheckAttribute(npchar, "ClockTower_repeat"))
					{
						dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+", oggi è il suo giorno. Prego, vada pure.";
						npchar.ClockTower_repeat = true;
						SetFunctionTimerCondition("ClockTower_GuardianNewDay", 0, 0, 1, false);
						
						ClockTower_RightDay();
					}
					else
					{
						dialog.text = "Buona giornata, "+GetTitle(NPChar, false)+"!";
					}
				}
				else
				{
					if (!CheckAttribute(npchar, "ClockTower_repeat"))
					{
						dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+", la aspettano un altro giorno. Saremo lieti di vederla: "+pchar.quest.ClockTower.date+" "+month+".";
						npchar.ClockTower_repeat = true;
						SetFunctionTimerCondition("ClockTower_GuardianNewDay", 0, 0, 1, false);
					}
					else
					{
						dialog.text = "Buona giornata, "+GetTitle(NPChar, false)+"!";
					}
				}
				link.l1 = "Grazie, Johan.";
				link.l1.go = "exit";
				NextDiag.TempNode = "ClockTower_Johan_51";
			}
			else
			{
				if (!CheckAttribute(npchar, "ClockTower_repeatnight"))
				{	// первая ночная встреча с Йоханом
					dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+", arrivi piuttosto tardi. L'ufficio è chiuso.";
					link.l1 = "Ciao, "+npchar.name+". Ho sentito dire che lavora anche di notte.";
					link.l1.go = "ClockTower_Johan_52";
					npchar.ClockTower_repeatnight = true;
					SetFunctionTimerCondition("ClockTower_GuardianNewDay", 0, 0, 1, false);
				}
				else
				{
					dialog.text = ""+TimeGreeting()+", "+GetTitle(NPChar, false)+"!";
					link.l1 = "";
					link.l1.go = "ClockTower_Johan_53";
				}
			}
		break;
		
		case "ClockTower_Johan_52":
			dialog.text = "È vero. Viene gente di ogni tipo. Persino i preti a volte passano, eh-eh. Ma tutti devono passare prima da me. E non ho ricevuto istruzioni riguardo a te.";
			link.l1 = "Aspetta, fai la guardia qui ventiquattr'ore su ventiquattro? Come è possibile?";
			link.l1.go = "ClockTower_Johan_53";
		break;

		case "ClockTower_Johan_53":
			if (!CheckAttribute(npchar, "ClockTower_repeatnight_2"))
			{
				dialog.text = "Sì. Il mynheer direttore l'ha appena ordinato. Come ci riesca, non lo so, ma ho comunque abbastanza tempo sia per riposare che per il servizio. E mi hanno aumentato la paga — non posso lamentarmi!";
				npchar.ClockTower_repeatnight_2 = true;
			}
			else
			{
				dialog.text = "Qualcos'altro?";
			}
			if (!CheckAttribute(pchar, "questTemp.ClockTower_NightFree"))
			{
				link.l1 = "Dovresti lasciarmi passare. Lavoro per l'alta dirigenza della compagnia.";
				link.l1.go = "ClockTower_Johan_54";
				link.l2 = "(Ucciderlo)";
				link.l2.go = "ClockTower_Johan_KillHim";
			}
			link.l3 = "Continua così, soldato.";
			link.l3.go = "ClockTower_Johan_NightExit";
		break;

		case "ClockTower_Johan_KillHim":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_KillToJohan");
		break;

		case "ClockTower_Johan_NightExit":
			DialogExit();
			NextDiag.CurrentNode = "ClockTower_Johan_51";
		break;

		case "ClockTower_Johan_54":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 80)
			{
				dialog.text = "Eh. Cosa vuole da me, mynheer capitano? Sono solo un semplice soldato, non so niente.";
				link.l1 = "Sai tutto, Johan. Non essere così modesto. I signori negli uffici importanti forse non ti rendono conto, ma hai sicuramente sentito parlare del gatto nero tra loro.";
				link.l1.go = "ClockTower_Johan_55";
				Notification_Skill(true, 80, SKILL_LEADERSHIP);
			}
			else
			{
				dialog.text = "Sono un uomo semplice, ma non scavalcherò il mio superiore diretto. Mi scusi, mynheer capitano.";
				link.l1 = "Torneremo su questa conversazione.";
				link.l1.go = "ClockTower_Johan_NightExit";
				Notification_Skill(false, 80, SKILL_LEADERSHIP);
			}
		break;

		case "ClockTower_Johan_55":
			Achievment_Set("ach_CL_197");
			dialog.text = "È vero, mynheer capitano. Il mynheer direttore è rimasto troppo a lungo. Si sta preparando una tempesta.";
			link.l1 = "Cosa hai sentito?";
			link.l1.go = "ClockTower_Johan_56";
		break;

		case "ClockTower_Johan_56":
			dialog.text = "Tutti temono che, se non oggi, domani prenderà il potere. È un uomo troppo grande per la nostra provincia dimenticata. Sta soffocando tutti con le sue ispezioni, fa passare ogni firma attraverso di lui.\nGlielo dico sinceramente, e l'ha visto lei stesso: ogni volta che l'Amsterdam entra in porto, si alza subito una brutta tensione.";
			link.l1 = "Posso risolvere questo, ma per farlo devi lasciarmi passare.";
			link.l1.go = "ClockTower_Johan_57";
		break;

		case "ClockTower_Johan_57":
			dialog.text = "Vada pure, mynheer capitano. Solo la prego, non mi rovini: se il mynheer direttore lo scopre, ci rimetto la testa, e ho una famiglia da sfamare.";
			link.l1 = "Farò del mio meglio.";
			link.l1.go = "ClockTower_Johan_58_hint";
		break;

		case "ClockTower_Johan_58_hint":
			ClockTower_AddBook();
			dialog.text = "Lei è un brav'uomo, mynheer capitano. Forse posso aiutarla: so che in uno dei libri il mynheer direttore tiene una chiave. A cosa serva, non lo so, ma forse le tornerà utile.";
			link.l1 = "Grazie, Johan.";
			link.l1.go = "ClockTower_Johan_NightSuccess";
		break;
		
		case "ClockTower_Johan_NightSuccess":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_NightFree");
			NextDiag.CurrentNode = "ClockTower_Johan_51";
			// if (sti(pchar.reputation.nobility) < 71) Notification_Reputation(false, 71, "low");
		break;
		
		case "ClockTower_Peter_50":
			dialog.text = "Alt. Si trova sulla proprietà della Compagnia Olandese delle Indie Occidentali. Dipartimento di registrazione navale e archivio. Ingresso solo su appuntamento.";
			link.l1 = "Sono il "+GetTitle(NPChar, false)+" "+pchar.name+".";
			link.l1.go = "ClockTower_Peter_51";
			DelLandQuestMark(npchar);
		break;
		
		case "ClockTower_Peter_51":
			if (pchar.quest.ClockTower.date <= GetDataDay())
			{
				NextMonth = GetDataMonth() + 1;
				if (NextMonth == 13) NextMonth = 1;
			}
			else NextMonth = GetDataMonth();
			Month = XI_ConvertString("MonthGen_" + NextMonth);
			if (pchar.quest.ClockTower.date == GetDataDay() && CheckAttribute(pchar, "questTemp.ClockTower_NoToday"))
			{
				if (!CheckAttribute(npchar, "ClockTower_repeat"))
				{
					dialog.text = "Ha un appuntamento? Vada pure.";
					npchar.ClockTower_repeat = true;
					SetFunctionTimerCondition("ClockTower_GuardianNewDay", 0, 0, 1, false);
					
					ClockTower_RightDay();
				}
				else
				{
					dialog.text = "...";
				}
			}
			else
			{
				if (!CheckAttribute(npchar, "ClockTower_repeat"))
				{
					dialog.text = "Il suo appuntamento è fissato per un altro giorno: "+pchar.quest.ClockTower.date+" "+month+".";
					npchar.ClockTower_repeat = true;
					SetFunctionTimerCondition("ClockTower_GuardianNewDay", 0, 0, 1, false);
				}
				else
				{
					dialog.text = "...";
				}
			}
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ClockTower_Peter_51";
		break;
		
		case "ClockTower_Visser_71":
			dialog.text = "Salve, "+GetTitle(NPChar, false)+". Ci sono novità?";
			link.l1 = "Sì. Ecco il contratto.";
			link.l1.go = "ClockTower_Visser_72";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Visser_72":
			dialog.text = "Incredibile... È scaduto sette anni fa!";
			link.l1 = "Quindi è questo ciò che serviva?";
			link.l1.go = "ClockTower_Visser_73";
		break;

		case "ClockTower_Visser_73":
			dialog.text = "Esattamente! Con questo documento la compagnia può richiamarlo legalmente. Niente scappatoie. Niente scuse. Il tempo è scaduto, punto.";
			link.l1 = "E adesso?";
			link.l1.go = "ClockTower_Visser_74";
		break;

		case "ClockTower_Visser_74":
			dialog.text = "Manderò il contratto ad Amsterdam. Il Consiglio dei Diciassette prenderà una decisione. A Doorn verrà ordinato di tornare. Non potrà rifiutare.";
			link.l1 = "E se rifiutasse?";
			link.l1.go = "ClockTower_Visser_75";
		break;

		case "ClockTower_Visser_75":
			dialog.text = "Non può. Benché sua moglie sia la figlia di un azionista, il Gran Pensionario, nemmeno suo padre andrà contro il Consiglio. E Catharina stessa... Aspetta da dieci anni. Se scopre che può tornare ma rifiuta — la ucciderà.";
			link.l1 = "Crudele.";
			link.l1.go = "ClockTower_Visser_76";
		break;

		case "ClockTower_Visser_76":
			dialog.text = "Sì. Ma è l'unico modo. Grazie, capitano. Hai fatto un lavoro importante.";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_77";
		break;

		case "ClockTower_Visser_77":
			if (CharacterIsAlive("ClockTower_Johan"))
			{
				dialog.text = "La tua ricompensa: cinquecento dobloni. E ti do la mia parola: tra due o tre mesi, quando prenderò la poltrona del direttore, avrai accesso illimitato ai servizi dell'ufficio. Senza code. Senza appuntamenti. In qualsiasi momento.";
				AddItems(pchar, "gold_dublon", 500);
			}
			else
			{
				dialog.text = "E hai ucciso Johan. Già ho tradito un uomo che ammiro e a cui devo tutto. Ora anche questo.\n"+
							 "Forse sulla tua nave le persone sono come legna da ardere, ma la compagnia tiene ai suoi dipendenti. E mi disgusta essere complice di un omicidio.\n"+
							 "I tuoi dobloni andranno alla famiglia di Johan, ma adempirò alla seconda parte dell'accordo.\n"+
							 "Ti do la mia parola: tra due o tre mesi, quando prenderò la poltrona del direttore, avrai accesso illimitato ai servizi dell'ufficio.";
			}
			link.l1 = "Conto sulla tua parola. Buona giornata.";
			link.l1.go = "ClockTower_Visser_78";
		break;

		case "ClockTower_Visser_78":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_WaitFewMonths");
		break;

		case "ClockTower_Visser_79":
			dialog.text = "Salve, "+GetTitle(NPChar, false)+". Ancora nessuna novità. Non preoccuparti, ricordo il nostro accordo.";
			link.l1 = "Speriamo.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ClockTower_Visser_79";
		break;

		case "ClockTower_Visser_81":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+"! Entra, entra. Contento di vederti.";
			link.l1 = "Congratulazioni per la nomina.";
			link.l1.go = "ClockTower_Visser_82";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Visser_82":
			dialog.text = "Grazie. Il Consiglio dei Diciassette ha preso la decisione più velocemente di quanto mi aspettassi. Il contratto si è rivelato prova sufficiente. Mynheer van Doorn è stato rimosso dalla gestione dell'ufficio.";
			link.l1 = "E come l'ha presa?";
			link.l1.go = "ClockTower_Visser_83";
		break;

		case "ClockTower_Visser_83":
			dialog.text = "Sa perdere. Ha semplicemente raccolto i suoi effetti personali dall'ufficio e se n'è andato. Anche se, ha davvero perso?\n"+
						 "Gli hanno lasciato il comando dell'Amsterdam. Su questo punto, la compagnia ha certamente commesso un errore. Non avrebbero dovuto dargli quella nave allora.\n"+
						 "L'abbiamo sottovalutato. Speriamo che alla fine le cose non peggiorino.";
			link.l1 = "Come potrebbe andare peggio?";
			link.l1.go = "ClockTower_Visser_84";
		break;

		case "ClockTower_Visser_84":
			dialog.text = "Mynheer van Doorn sa chi ha preso il contratto dal suo ufficio.";
			link.l1 = "Come?!";
			link.l1.go = "ClockTower_Visser_85";
		break;

		case "ClockTower_Visser_85":
			dialog.text = "Non guardarmi così! Non gli ho detto niente. L'ha capito tutto da solo.";
			link.l1 = "E adesso?";
			link.l1.go = "ClockTower_Visser_86";
		break;

		case "ClockTower_Visser_86":
			dialog.text = "Ora ti considera un nemico. Ma finché non rappresenti una minaccia per la Repubblica delle Sette Province Unite, non ti toccherà.\n"+
						 "Van Doorn ha sempre saputo separare il personale dal professionale. La domanda è: tu ci riesci?";
			link.l1 = "E se non ci riesco?";
			link.l1.go = "ClockTower_Visser_87";
		break;

		case "ClockTower_Visser_87":
			dialog.text = "Allora ti troverà. E farà il suo lavoro. Non dargli un motivo.";
			link.l1 = "Ci proverò.";
			link.l1.go = "ClockTower_Visser_88";
		break;

		case "ClockTower_Visser_88":
			dialog.text = "Buona giornata, "+GetTitle(NPChar, false)+". Sentiti libero di usare i servizi del nostro... mio ufficio in qualsiasi momento.";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_VillemstadStreet");
		break;
		
		case "ClockTower_Johan_61":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+", la aspettano. Mynheer Visser ha ordinato di far entrare liberamente tutti i clienti. Dice che le vecchie regole erano troppo rigide.";
			link.l1 = "Grazie, Johan.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_FreeAccess_2");
			DelLandQuestMark(npchar);
		break;
		
		case "ClockTower_Peter_61":
			dialog.text = "Vada pure durante qualsiasi orario d'ufficio. Gli appuntamenti sono stati aboliti.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_FreeAccess_2");
			DelLandQuestMark(npchar);
		break;
		
		case "ClockTower_Helena_1":
			dialog.text = "Hai un minuto?";
			link.l1 = "Per te, sempre.";
			link.l1.go = "ClockTower_Helena_2";
		break;

		case "ClockTower_Helena_2":
			dialog.text = "Ah, magari, mio capitano. Hai altre passioni nella vita. Proprio adesso, ad esempio, la tua bella testa è occupata da qualcuno che non sono io, giusto?";
			link.l1 = "...";
			link.l1.go = "ClockTower_Helena_3";
		break;

		case "ClockTower_Helena_3":
			dialog.text = "Ecco, appunto. Conosco bene il mio uomo. E l'ardore di un marinaio — quello lo conosco ancora meglio. Quindi dimmelo chiaramente, tesoro...\n"+
						 "Quanto ci costerà catturare l'ammiraglia della stimata Compagnia Commerciale Olandese delle Indie Occidentali?";
			link.l1 = "Perché van Doorn venga a prenderci di persona, dovrò diventare nemico di Willemstad.";
			link.l1.go = "ClockTower_Helena_4";
		break;

		case "ClockTower_Helena_4":
			dialog.text = "Oh, mio capitano... Quindi sarà così. Non è la prima volta, vero?";
			link.l1 = "Come se non lo approvasse.";
			link.l1.go = "ClockTower_Helena_5";
		break;

		case "ClockTower_Helena_5":
			dialog.text = "Mi sono innamorata di te per quello che sei. E sarò sempre dalla tua parte. Ricorda solo il peso della responsabilità che noi... cioè, che tu porti verso la tua gente.";
			link.l1 = "Comunque, per questo c'è il nostro Alonso. Lui te lo ricorderà.";
			link.l1.go = "ClockTower_Helena_6";
		break;

		case "ClockTower_Helena_6":
			dialog.text = "Non appena salperemo, mio capitano.";
			link.l1 = "Allora non perdiamo tempo, tesoro.";
			link.l1.go = "ClockTower_Girl_End";
		break;
		
		case "ClockTower_Mary_1":
			dialog.text = "Charles? Voglio chiederti una cosa.";
			link.l1 = "Certo, Mary. Cos'è successo?";
			link.l1.go = "ClockTower_Mary_2";
		break;

		case "ClockTower_Mary_2":
			dialog.text = "Io... sono preoccupata per te, sai. Conosco quello sguardo. Stai pensando a qualcosa di brutto.";
			link.l1 = "Sciocchezze. Non ricordo nemmeno a cosa stavo pensando. Come fai a saperlo?";
			link.l1.go = "ClockTower_Mary_3";
		break;

		case "ClockTower_Mary_3":
			dialog.text = "Lo so e basta! Ho visto quell'Amsterdam, sai. Una bella nave. Molto bella. Ma...\n"+
						 "Hai già deciso tutto... Come prima, vero?";
			link.l1 = "Van Doorn verrà a prenderci di persona, ma per questo dovrò diventare nemico di Willemstad.";
			link.l1.go = "ClockTower_Mary_4";
		break;

		case "ClockTower_Mary_4":
			dialog.text = "Ne vale la pena, Charles?";
			link.l1 = "Non lo so, Mary.";
			link.l1.go = "ClockTower_Mary_5";
		break;

		case "ClockTower_Mary_5":
			dialog.text = "Voglio che tu sia felice, sai. Ma comunque chiederò ad Alonso di convincerti a lasciar perdere, va bene!";
			link.l1 = "È da lui. Andiamo, tesoro.";
			link.l1.go = "ClockTower_Girl_End";
		break;
		
		case "ClockTower_Girl_End":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_Girl_DlgExit");
		break;
		
		case "ClockTower_Alonso_1":
			dialog.text = "Cap, dobbiamo parlare.";
			link.l1 = "Ti ascolto.";
			link.l1.go = "ClockTower_Alonso_2";
			link.l2 = "Non ora, Alonso.";
			link.l2.go = "ClockTower_Alonso_2";
		break;

		case "ClockTower_Alonso_2":
			dialog.text = "Insomma, cap, ma devi ascoltarmi. È, ehm, come dire...\n"+
						 "Un caso urgente — ecco!\n"+
						 "In sostanza, un piccolo volatile mi ha sussurrato che lei personalmente ha buttato fuori uno dei direttori della compagnia dal suo comodo posto, e quello ora covando rancore ci dà la caccia sul suo bellissimo vascello.";
			link.l1 = "È un'esagerazione palese.";
			link.l1.go = "ClockTower_Alonso_3";
		break;

		case "ClockTower_Alonso_3":
			dialog.text = "Sa come la gente ama fare circolare le voci, cap. Lasci che un pettegolezzo fermenti per una settimana — e sentirà che van Doorn è stato sedotto dalla figlia di un piantatore, che l'Amsterdam ha un equipaggio di morti viventi, e nella stiva ci sono i tesori di Cortés in persona.\n"+
						 "Ma ciò che mi interessa di più è la situazione reale. Insomma, cap, ci sarà uno scontro o no?";
			link.l1 = "...";
			if (CheckPassengerInCharacter(pchar, "Irons"))
			{
				link.l1.go = "ClockTower_Alonso_4_1";
			}
			else
			{
				link.l1.go = "ClockTower_Alonso_4_5";
			}
		break;

		case "ClockTower_Alonso_4_1":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_TommyInCabin");
		break;

		case "ClockTower_Alonso_4_2":
			dialog.text = "Che, tra l'altro, sarebbe dannatamente divertente, non discuto! L'ammiraglia olandese! Ah! Immagino le facce di quei mangiatori di formaggio quando noi...";
			link.l1 = "...";
			link.l1.go = "ClockTower_Alonso_4_3";
		break;

		case "ClockTower_Alonso_4_3":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_TommyInCabin_2");
		break;

		case "ClockTower_Alonso_4_4":
			dialog.text = "Tomasso, chiudi quella bocca.";
			link.l1 = "...";
			link.l1.go = "ClockTower_Alonso_4_5";
		break;

		case "ClockTower_Alonso_4_5":
			dialog.text = "...";
			link.l1 = "Se ci sarà uno scontro, non sarà presto. Van Doorn non cercherà vendetta, non è quel tipo di uomo. Prima dovremo irritare seriamente gli olandesi.";
			link.l1.go = "ClockTower_Alonso_4_6";
			CharacterTurnByChr(npchar, pchar);
		break;

		case "ClockTower_Alonso_4_6":
			dialog.text = "Grazie, cap, questo rassicurerà l'equipaggio.";
			link.l1 = "E te?";
			link.l1.go = "ClockTower_Alonso_5";
		break;

		case "ClockTower_Alonso_5":
			dialog.text = "La mia preoccupazione è proteggere l'equipaggio. Da se stessi e... da lei, se ci riesco. Lei farà comunque quello che ha pianificato.";
			if (CheckPassengerInCharacter(pchar, "Irons"))
			{
				link.l1 = "...";
				link.l1.go = "ClockTower_Alonso_5_add";
			}
			else
			{
				link.l1 = "Continua così, Alonso.";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("ClockTower_CuracaoInCabin_4_DlgExit");
			}
		break;

		case "ClockTower_Alonso_5_add":
			StartInstantDialogTurnToNPC("Irons", "ClockTower_Alonso_6", "Quest\ShipsPack\ClockTower_dialog.c", "ClockTower_Alonso");
		break;

		case "ClockTower_Alonso_6":
			dialog.text = "Testardo come un mulo spagnolo!";
			link.l1 = "...";
			link.l1.go = "ClockTower_Alonso_6_add";
		break;

		case "ClockTower_Alonso_6_add":
			StartInstantDialogTurnToNPC("ClockTower_Alonso", "ClockTower_Alonso_7", "Quest\ShipsPack\ClockTower_dialog.c", "Irons");
		break;

		case "ClockTower_Alonso_7":
			dialog.text = "Signore, perché proprio a me.";
			link.l1 = "...";
			link.l1.go = "ClockTower_Alonso_7_add";
		break;

		case "ClockTower_Alonso_7_add":
			StartInstantDialogTurnToNPC("Irons", "ClockTower_Alonso_8", "Quest\ShipsPack\ClockTower_dialog.c", "ClockTower_Alonso");
		break;

		case "ClockTower_Alonso_8":
			dialog.text = "Complichi tutto! Il cap vuole una bella nave — gli daremo una bella nave! Siamo un equipaggio!";
			link.l1 = "Continua così, Alonso. Tomasso, fuori.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_CuracaoInCabin_4_DlgExit");
		break;
		
		// Абордаж Амстердама, перед боем с Ван Дормом
		case "ClockTower_VanDoorn_21":
			NationName = GetSexPhrase(""+NationNameMan(sti(pchar.baseNation))+"",""+NationNameWoman(sti(pchar.baseNation))+"");
			shipType = LowerFirst(XI_ConvertString(GetShipTypeName(pchar)));
			dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+" "+GetFullName(pchar)+", "+NationName+". La vostra nave — '"+PChar.Ship.Name+"', "+shipType+". "+GetCannonQuantity(pchar)+" cannoni e "+GetMaxCrewQuantity(pchar)+" membri d'equipaggio.";
			link.l1 = "Lei è preciso come sempre, mynheer direttore.";
			link.l1.go = "ClockTower_VanDoorn_22";
		break;

		case "ClockTower_VanDoorn_22":
			dialog.text = "Quel titolo non mi appartiene più — grazie ai suoi sforzi. Ma non pensi nemmeno che l'abbia attaccata per meschina vendetta. Stavo facendo il mio lavoro.\n"+
						 "E ovviamente ho fallito. Né avrei potuto riuscire: le dissi una volta che lei è un capitano molto migliore di me.";
			link.l1 = "Lei si è preso questo peso da solo! Il suo contratto è scaduto sette anni fa. Cosa le impediva di tornare semplicemente a casa?";
			link.l1.go = "ClockTower_VanDoorn_23";
		break;

		case "ClockTower_VanDoorn_23":
			dialog.text = "Cosa le impedisce di fare lo stesso? Lei conosce la risposta, capitano. Ha un sogno. Non ha un'altra vita. E se molla il controllo — tutto crolla.\n"+
						 "Avrei potuto portare ordine in questa regione. Fermare il ciclo infinito di violenza. Se non avessi allentato il controllo. Se avessi schiacciato la mia paura e fatto ciò che dovevo fare da tempo.\n"+
						 "Ma basta con il patetismo. Sono un combattente pessimo quanto un capitano, ma so scegliere i miei uomini. Lei stesso si è reso il mio ultimo compito, capitano. Oggi nel registro dell'ufficio ci saranno due capitani in meno!";
			if (CheckCharacterItem(PChar, "CatharinaLetter"))
			{
				link.l1 = "Stava dicendo qualcosa sulla paura. Quindi legga questa lettera.";
				link.l1.go = "ClockTower_VanDoorn_24";
			}
			link.l2 = "Solo uno. Alla battaglia!"; // бой
			link.l2.go = "ClockTower_cabinFight";
		break;

		case "ClockTower_VanDoorn_24":
			dialog.text = "Da Catharina?! Come osa mescolare il personale con il lavoro?!";
			link.l1 = "Come vede, la lettera è ancora sigillata. Sto aspettando.";
			link.l1.go = "ClockTower_VanDoorn_25";
			TakeItemFromCharacter(pchar, "CatharinaLetter");
			pchar.questTemp.ClockTower_GaveCatharinaLetter = true;
		break;

		case "ClockTower_VanDoorn_25":
			dialog.text = "...non può più aspettare... andrà con un altro... se non torno?!";
			link.l1 = "Ha già perso l'ufficio. Il suo equipaggio sta morendo proprio ora. È pronto a perdere anche la sua famiglia?";
			link.l1.go = "ClockTower_VanDoorn_26";
		break;

		case "ClockTower_VanDoorn_26":
			dialog.text = "Non così. Capitano, accetta la mia resa?";
			link.l1 = "Sì. Se ne vada dalla mia nave.";
			link.l1.go = "ClockTower_VanDoorn_27";
			link.l2 = "No. Quella era l'ultima cortesia per il condannato. Alla battaglia!";
			link.l2.go = "ClockTower_cabinFight";
		break;

		case "ClockTower_VanDoorn_27":
			dialog.text = "Allora congratulazioni per la sua vittoria, capitano "+GetFullName(pchar)+". Oggi nel registro ci sarà solo un capitano in meno. Addio.";
			link.l1 = "...";
			link.l1.go = "ClockTower_cabinPeace";
			GiveItem2Character(PChar, "pistol15");
			RemoveCharacterEquip(npchar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(npchar, GUN_ITEM_TYPE);
			TakeItemFromCharacter(npchar, "pistol15");
		break;
		
		// Финальный диалог с Маартеном
		case "ClockTower_Visser_101":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+" "+GetFullName(pchar)+". Non mi aspettavo che osasse venire qui.";
			link.l1 = "Perché no? Sono ancora suo cliente, e ho bisogno dei servizi dell'ufficio.";
			link.l1.go = "ClockTower_Visser_102";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Visser_102":
			dialog.text = "Servizi? SERVIZI?! Dopo quello che ha fatto? Lei è un nemico della stimata Compagnia Olandese delle Indie Occidentali! Un altro capitano prenderà il suo posto di cliente!";
			link.l1 = "Improbabile. Guardate cosa ho trovato fra i documenti di van Doorn.";
			link.l1.go = "ClockTower_Visser_103";
		break;

		case "ClockTower_Visser_103":
			dialog.text = "...";
			link.l1 = "Il suo predecessore riteneva indecoroso usare questo documento — anche quando la sua poltrona ha cominciato a traballare.";
			link.l1.go = "ClockTower_Visser_104";
			TakeItemFromCharacter(pchar, "Visser_Key");
		break;

		case "ClockTower_Visser_104":
			dialog.text = "...";
			link.l1 = "Ha avuto fortuna ad avere un tale superiore. Per simili manovre l'avrebbe aspettato un processo — nella migliore delle ipotesi.";
			link.l1.go = "ClockTower_Visser_105";
		break;

		case "ClockTower_Visser_105":
			dialog.text = "...";
			link.l1 = "Lei è un uomo d'affari. Sa dove voglio arrivare.";
			link.l1.go = "ClockTower_Visser_106";
		break;

		case "ClockTower_Visser_106":
			dialog.text = "Lei... Il suo posto nel registro è ripristinato.";
			link.l1 = "Ah, Maarten. Voleva prendere il posto del direttore, anche se lui le ha dato tutto. L'ha salvata dal processo e non ha nemmeno ritenuto necessario informarla.";
			link.l1.go = "ClockTower_Visser_107";
		break;

		case "ClockTower_Visser_107":
			dialog.text = "...";
			link.l1 = "Questo peccatuccio non le permetterà mai di salire più in alto e la lascerà vivere nella paura costante.";
			link.l1.go = "ClockTower_Visser_108";
		break;

		case "ClockTower_Visser_108":
			dialog.text = "...";
			link.l1 = "Ora tocca a lei essere incatenato a questo posto. Ma certamente non avrà un vice come quello che aveva van Doorn.";
			link.l1.go = "ClockTower_Visser_109";
		break;

		case "ClockTower_Visser_109":
			dialog.text = "Basta. Vuole finirmi completamente?!";
			link.l1 = "Non proprio. Voglio che registri la mia nuova nave nel registro. Non voglio malintesi.";
			link.l1.go = "ClockTower_Visser_110";
		break;

		case "ClockTower_Visser_110":
			dialog.text = "La sua nave è l'Amsterdam. Ammiraglia della COIOC. Non si può semplicemente... ri-registrare.";
			link.l1 = "Perché no? La carta sopporta tutto. Non è così che funziona il suo sistema?";
			link.l1.go = "ClockTower_Visser_111";
		break;

		case "ClockTower_Visser_111":
			dialog.text = "Buon Dio, ma tutto ha dei limiti!";
			link.l1 = "Credo nel potere di questo luogo. Anche lei dovrebbe.";
			link.l1.go = "ClockTower_Visser_112";
		break;

		case "ClockTower_Visser_112":
			dialog.text = "...";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_113";
		break;

		case "ClockTower_Visser_113":
			dialog.text = "Nome completo?";
			link.l1 = ""+GetFullName(pchar)+".";
			link.l1.go = "ClockTower_Visser_114";
		break;

		case "ClockTower_Visser_114":
			dialog.text = "Nazionalità?";
			link.l1 = ""+NationNameNominative(sti(pchar.baseNation))+".";
			link.l1.go = "ClockTower_Visser_115";
		break;

		case "ClockTower_Visser_115":
			dialog.text = "Nome della sua nave?";
			link.l1 = ""+PChar.Ship.Name+".";
			link.l1.go = "ClockTower_Visser_116";
		break;

		case "ClockTower_Visser_116":
			shipType = XI_ConvertString(GetShipTypeName(pchar));
			dialog.text = "Tipo di nave?";
			link.l1 = ""+shipType+".";
			link.l1.go = "ClockTower_Visser_117";
		break;

		case "ClockTower_Visser_117":
			dialog.text = "Numero di cannoni?";
			link.l1 = ""+GetCannonQuantity(pchar)+".";
			link.l1.go = "ClockTower_Visser_118";
		break;

		case "ClockTower_Visser_118":
			dialog.text = "Dimensione dell'equipaggio?";
			link.l1 = ""+GetMaxCrewQuantity(pchar)+".";
			link.l1.go = "ClockTower_Visser_119";
		break;

		case "ClockTower_Visser_119":
			dialog.text = "Bene. Ora firmi qui. E qui. E qui anche.";
			link.l1 = "È tutto?";
			link.l1.go = "ClockTower_Visser_120";
		break;

		case "ClockTower_Visser_120":
			dialog.text = "È tutto.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_Visser_pausa_1");
		break;

		case "ClockTower_Visser_121":
			dialog.text = "...";
			link.l1 = "Ha dimenticato di dire qualcosa.";
			link.l1.go = "ClockTower_Visser_122";
		break;

		case "ClockTower_Visser_122":
			dialog.text = "\nBenvenuto nel registro clienti della stimata Compagnia Olandese delle Indie Occidentali.";
			link.l1 = "Arrivederci, mynheer direttore.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_FINAL");
		break;
		

		//------------------Услуги конторы------------------//
		case "ClockTower_OfficeServices":
			if (npchar.id == "ClockTower_VanDoorn")
			{
				dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+" "+pchar.name+". Come posso aiutarla oggi io e il mio ufficio?";
			}
			if (npchar.id == "ClockTower_Visser")
			{
				if (CharacterIsAlive("ClockTower_VanDoorn"))
				{
					dialog.text = "Contento di vederla, "+GetTitle(NPChar, false)+"! Sempre al suo servizio. Cosa la interessa oggi?";
				}
				else
				{
					dialog.text = "Allora? Cosa la interessa oggi?";
				}
			}
			link.l1 = "Condurrà un audit della mia nave? Voglio migliorare le sue caratteristiche.";
			link.l1.go = "ClockTower_OfficeServices_audit"; // Аудит
			link.l2 = "Non sono soddisfatto della specializzazione della mia nave. Può produrre nuovi documenti?";
			link.l2.go = "ClockTower_OfficeServices_changeTrait"; // Смена документов
			link.l3 = "Registrerà la mia nave nel registro della compagnia? Affinché i pirati e i cacciatori di taglie ci pensino due volte.";
			link.l3.go = "ClockTower_OfficeServices_buffSpec"; // Занесение в реестр
			if (!CheckAttribute(pchar, "questTemp.ShipInsurance"))
			{
				link.l4 = "Vorrei assicurare le mie navi nei depositi portuali. Correnti e future.";
				link.l4.go = "ClockTower_OfficeServices_Insurance"; // Страховка (пропадает после оплаты)
			}
			if(!CheckAttributeEqualTo(npchar, "last_logbook_date", LastSpeakDate()) && ClockTower_JournalsQty() > 0)
			{
				link.l5 = "Accetta i registri di bordo dei capitani pirati?";
				link.l5.go = "ClockTower_OfficeServices_logbook"; // Награда за пиратов (раз в сутки)
			}
			link.l6 = "Forse non oggi. Buona giornata.";
			link.l6.go = "ClockTower_OfficeServices_exit"; // Отказ
		break;

		// Аудит
		case "ClockTower_OfficeServices_audit":
			if (!IsShipInPort(npchar.city))
			{
				ClockTower_NoShipInPort(link);
				break;
			}
			n = 0;
			dialog.text = "Il costo dipende dalle dimensioni della nave. Di quale nave si tratta?";
			for (i = 0; i < COMPANION_MAX; i++)
			{
				idx = GetCompanionIndex(pchar, i);
				if (idx < 0) continue;

				sld = GetCharacter(idx);
				realShip = GetRealShip(GetCharacterShipType(sld));
				if (CheckAttribute(realShip, "tuning.Audit")) continue;
				if (!IsFellowOurCrew(sld)) continue;

				n++;
				sTemp = "l"+n;
				link.(sTemp) = XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName) + " '" + sld.Ship.Name + "'.";
				link.(sTemp).go = Dialog.currentNode + "_chosenIdx/" + idx;
			}

			if (n == 0)
			{
				dialog.text = "Purtroppo, l'audit è un servizio unico per ogni singola nave. Altro?";
				link.l1 = "Allora un'altra volta.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_audit_chosenIdx":
			sld = GetCharacter(sti(Dialog.tmpIdx));
			sTemp = "";
			if (CanUpgradeShip(sld, &sTemp, "Audit"))
			{
				n = GetAuditShipCost(sld);
				dialog.text = "Vediamo... Questo costerà " + n + " dobloni.";
				if (PCharDublonsTotal() > n)
				{
					link.l1 = "Proceda.";
					link.l1.go = "ClockTower_OfficeServices_audit_upgradeShip";
				}
				link.l2 = "Anche se... facciamolo un'altra volta.";
				link.l2.go = "ClockTower_OfficeServices_exit";
			}
			else if (sTemp == "Kaleuche")
			{
				dialog.text = "Mi vedo costretto a rifiutare. Secondo il registro, la vostra nave è finita in pasto al diavolo del mare molti anni fa, e un simile fantasma del passato non può essere cancellato con un colpo di penna. Prima di poter collaborare, dovrete restaurarla. Si dice che a Isla Tesoro ci sia un maestro disposto a occuparsi di un lavoro del genere.";
				link.l1 = "Chiaro, grazie.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
			else if (sTemp == "alreadyUpgraded")
			{
				dialog.text = "$La nave è già stata migliorata.";
				link.l1 = "Chiaro, grazie.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_audit_upgradeShip":
			Achievment_Set("ach_CL_199");
			sld = GetCharacter(sti(Dialog.tmpIdx));
			RemoveDublonsFromPCharTotal(GetAuditShipCost(sld));
			UpgradeShipAudit(sld);
			dialog.text = "Fatto.";
			link.l1 = "Grazie.";
			link.l1.go = "ClockTower_OfficeServices_exit";
		break;

		// Улучшение специализации
		case "ClockTower_OfficeServices_buffSpec":
			if (!IsShipInPort(npchar.city))
			{
				ClockTower_NoShipInPort(link);
				break;
			}
			n = 0;
			dialog.text = "Il costo dipende dalle dimensioni della nave. Di quale nave si tratta?";
			for (i = 0; i < COMPANION_MAX; i++)
			{
				idx = GetCompanionIndex(pchar, i);
				if (idx < 0) continue;

				sld = GetCharacter(idx);
				realShip = GetRealShip(GetCharacterShipType(sld));
				if (CheckAttribute(realShip, "tuning.SpecialityUpgrade")) continue;
				if (!IsFellowOurCrew(sld)) continue;

				n++;
				sTemp = "l"+n;
				link.(sTemp) = XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName) + " '" + sld.Ship.Name + "'.";
				link.(sTemp).go = Dialog.currentNode + "_chosenIdx/" + idx;
			}

			if (n == 0)
			{
				dialog.text = "Purtroppo, la registrazione è un servizio unico per ogni singola nave. Altro?";
				link.l1 = "Allora un'altra volta.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_buffSpec_chosenIdx":
			sld = GetCharacter(sti(Dialog.tmpIdx));
			sTemp = "";
			if (CanUpgradeShip(sld, &sTemp, "SpecialityUpgrade"))
			{
				n = GetSpecialityUpgradeShipCost(sld);
				dialog.text = "Vediamo... Questo costerà " + n + " dobloni.";
				if (PCharDublonsTotal() > n)
				{
					link.l1 = "Proceda.";
					link.l1.go = "ClockTower_OfficeServices_buffSpec_upgradeShip";
				}
				link.l2 = "Anche se... facciamolo un'altra volta.";
				link.l2.go = "ClockTower_OfficeServices_exit";
			}
			else if (sTemp == "Kaleuche")
			{
				dialog.text = "Mi vedo costretto a rifiutare. Secondo il registro, la vostra nave è finita in pasto al diavolo del mare molti anni fa, e un simile fantasma del passato non può essere cancellato con un colpo di penna. Prima di poter collaborare, dovrete restaurarla. Si dice che a Isla Tesoro ci sia un maestro disposto a occuparsi di un lavoro del genere.";
				link.l1 = "Chiaro, grazie.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
			else if (sTemp == "alreadyUpgraded")
			{
				dialog.text = "$La nave è già stata migliorata.";
				link.l1 = "Chiaro, grazie.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_buffSpec_upgradeShip":
			Achievment_Set("ach_CL_199");
			sld = GetCharacter(sti(Dialog.tmpIdx));
			RemoveDublonsFromPCharTotal(GetSpecialityUpgradeShipCost(sld));
			UpgradeShipSpeciality(sld);
			dialog.text = "Fatto.";
			link.l1 = "Grazie.";
			link.l1.go = "ClockTower_OfficeServices_exit";
		break;

		// Смена трейта корабля
		case "ClockTower_OfficeServices_changeTrait":
			if (!IsShipInPort(npchar.city))
			{
				ClockTower_NoShipInPort(link);
				break;
			}
			n = 0;
			dialog.text = "Il costo dipende dalle dimensioni della nave. Di quale nave si tratta?";
			for (i = 0; i < COMPANION_MAX; i++)
			{
				idx = GetCompanionIndex(pchar, i);
				if (idx < 0) continue;

				sld = GetCharacter(idx);
				realShip = GetRealShip(GetCharacterShipType(sld));
				sTemp = "";
				ShipTraitCanBeChanged(sld, &sTemp);
				if (sTemp == "EmptyShip" || sTemp == "QuestCompanion") continue;

				n++;
				sTemp = "l"+n;
				link.(sTemp) = XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName) + " '" + sld.Ship.Name + "'.";
				link.(sTemp).go = Dialog.currentNode + "_chosenIdx/" + idx;
			}

			if (n == 0)
			{
				dialog.text = "Uhmm. Non vedo nessuna delle sue navi nel porto.";
				link.l1 = "Allora un'altra volta.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_changeTrait_chosenIdx":
			sld = GetCharacter(sti(Dialog.tmpIdx));
			sTemp = "";

			if (ShipTraitCanBeChanged(sld, &sTemp))
			{
				n = GetChangeShipTraitCost(sld);
				dialog.text = "Vediamo... Questo costerà " + n + " dobloni.";
				if (PCharDublonsTotal() > n)
				{
					link.l1 = "Proceda.";
					link.l1.go = "ClockTower_OfficeServices_changeTrait_upgradeShip";
				}
				link.l2 = "Anche se... facciamolo un'altra volta.";
				link.l2.go = "ClockTower_OfficeServices_exit";
			}
			else if (sTemp == "QuestSP")
			{
				dialog.text = "Mi spiace, ma ciò non è possibile. La sua nave è unica, avvolta da leggende. Un semplice colpo di penna non può cambiare nulla.";
				link.l1 = "Chiaro, grazie.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
			else
			{
				dialog.text = "Di quale specializzazione parlate? La sua nave è universale, senza caratteristiche particolari.";
				link.l1 = "Piace sapere, grazie.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_changeTrait_upgradeShip":
			sld = GetCharacter(sti(Dialog.tmpIdx));
			NextDiag.CurrentNode = "ClockTower_OfficeServices";
			DialogExit();
			LaunchChangeShipTraitScreen(sld);
		break;

		// Страховка
		case "ClockTower_OfficeServices_Insurance":
			n = GetInsuranceCost();
			dialog.text = "Vediamo... Questo costerà " + n + " dobloni.";
			if (PCharDublonsTotal() > n)
			{
				link.l1 = "Proceda.";
				link.l1.go = "ClockTower_OfficeServices_Insurance_done";
			}
			link.l2 = "Anche se... facciamolo un'altra volta.";
			link.l2.go = "ClockTower_OfficeServices_exit";
		break;

		case "ClockTower_OfficeServices_Insurance_done":
			pchar.questTemp.ShipInsurance = true;
			RemoveDublonsFromPCharTotal(GetInsuranceCost());
			dialog.text = "Fatto.";
			link.l1 = "Grazie.";
			link.l1.go = "ClockTower_OfficeServices_exit";
			Achievment_Set("ach_CL_199");
		break;

		// Награда за пиратов
		case "ClockTower_OfficeServices_logbook":
			dialog.text = "Assolutamente corretto. La ricompensa dipende dal numero di registri e dal pericolo relativo dei loro proprietari.\n" +
						  "Quanti registri avete portato?";
			link.l1 = "" + ClockTower_JournalsQty();
			link.l1.go = "ClockTower_OfficeServices_logbook_1";
		break;

		case "ClockTower_OfficeServices_logbook_1":
			dialog.text = "La compagnia vi ringrazia per il vostro lavoro. Vi spettano " + JournalsCost() + " dobloni. Riceveteli e firmate qui.";
			link.l1 = "Grazie.";
			link.l1.go = "ClockTower_OfficeServices_exit";
			npchar.last_logbook_date = LastSpeakDate();
			Achievment_Set("ach_CL_199");
		break;

		case "ClockTower_OfficeServices_exit":
			DialogExit();
			NextDiag.CurrentNode = "ClockTower_OfficeServices";
		break;

		case "ClockTower_cabinFight":
			QuestAboardCabinDialogExitWithBattle("");
			DialogExit();
			ClockTower_CabinFight2();
		break;
		
		case "ClockTower_cabinPeace":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_cabinPeace");
		break;
	}
}

void ClockTower_NoShipInPort(ref link)
{
	dialog.text = "Non vedo la sua nave in Porto.";
	link.l1 = "Allora un'altra volta.";
	link.l1.go = "ClockTower_OfficeServices_exit";
}

int ClockTower_PlaySound_rh2(string name)
{
    float x = stf(loadedLocation.locators.reload.houseO2.x);
    float y = stf(loadedLocation.locators.reload.houseO2.y);
    float z = stf(loadedLocation.locators.reload.houseO2.z);
    return SendMessage(Sound, "lslfff", MSG_SOUND_EVENT_PLAY, name, 0, x, y, z);
}

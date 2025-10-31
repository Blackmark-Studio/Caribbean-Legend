void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Cosa vuoi?";
			link.l1 = "Niente.";
			link.l1.go = "exit";
		break;
		
		case "Sailor_1":
			dialog.text = "Cosa vuoi, "+GetSexPhrase("amico","ragazza")+"? Se mi offri del rum, non dico di no. Ho fatto così tanti giri in questa maledetta città che le gambe stanno per annodarsi da sole. E tu come ti chiami?";
			link.l1 = "Capitano "+GetFullName(pchar)+". Non vieni dalla 'Aquila', vero?";
			link.l1.go = "Sailor_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Sailor_2":
			if (pchar.sex == "man")
			{
				dialog.text = "E io - "+GetFullName(npchar)+". E sì, vengo dall’‘Aquila’. Ti piace la nostra nave, capitano?";
			}
			else
			{
				dialog.text = "Capitano? Bene, bene... Ehm... Sono Antonio Velenta. E sì, vengo dall'‘Aquila’. La nostra nave ha attirato la sua attenzione, Capitano?";
			}
			link.l1 = "Una nave è una nave. Faresti meglio a salire a bordo invece di girare per la città—il tuo capitano sta già sputando fulmini. Vuole salpare prima che la marea si ritiri, e qualcosa mi dice, ragazzo, che non ti aspetterà.";
			link.l1.go = "Sailor_3";
		break;
		
		case "Sailor_3":
			dialog.text = "Maledizione... Lo so, lo so... Ma ho ancora qualche faccenda in sospeso in questa città. Ti andrebbe di guadagnare un paio di dobloni, eh, Capitano?";
			link.l1 = "I dobloni non fanno mai schifo. Ma guadagnarli è una cosa, cacciarsi nei guai è un'altra. Di che si tratta? Sputa il rospo.";
			link.l1.go = "Sailor_4";
		break;
		
		case "Sailor_4":
			dialog.text = "Vedi, mentre scaricavo la stiva, mi sono imbattuto in una lettera. Non sembrava che fosse stata nascosta di proposito, era semplicemente lì, tra alcune vecchie botti. Il nostro fluyt ne ha viste di tutti i colori, quindi è impossibile sapere da dove sia arrivata.";
			link.l1 = "Quindi hai trovato la lettera, ma che importa?";
			link.l1.go = "Sailor_5";
		break;
		
		case "Sailor_5":
			dialog.text = "È indirizzata a una certa Marisa Caldera di Porto Bello. Sigillata con la cera... Lo sento nelle ossa – non è una faccenda da poco. Forse viene da un capitano, forse da un mercante... ma di certo non da un semplice marinaio come me! Solo che non avrò tempo di trovare la destinataria – il nostro capitano non scherza affatto.  Non vuoi comprarmela? Te la lascio per mille pesos. Sei un capitano, non ti sarà difficile rintracciare questa señorita. E chissà, magari ti ricompenserà con dell’oro, o con qualcos’altro... hai capito cosa intendo?";
			if (sti(pchar.Money) >= 1000)
			{
				link.l1 = "E allora, forse troverò io la tua Marisa. In ogni caso, non ho nulla da perdere. Tranne mille pesos. Dammi la lettera.";
				link.l1.go = "Sailor_6";
			}
			else
			{
				notification("Non abbastanza denaro (1000)", "Money");
			}
			link.l2 = "Mi dispiace, amico, ma dovrai trovare qualcun altro. Ho cose più importanti da fare che consegnare lettere.";
			link.l2.go = "Sailor_end";
		break;
		
		case "Sailor_end":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Sailor_end");
		break;
		
		case "Sailor_6":
			dialog.text = "Ecco qua. Beh, stammi bene, "+GetSexPhrase("amico","ragazza")+", dovrei andare – non vorrei che le mie cose salpassero via con la 'Eagle'.";
			link.l1 = "...";
			link.l1.go = "Sailor_accept";
			GiveItem2Character(PChar, "LFD_letter");
			AddMoneyToCharacter(pchar, -1000);
		break;
		
		case "Sailor_accept":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Sailor_accept");
			AddQuestRecord("LFD", "2");
		break;
		
		case "Dolores_1":
			dialog.text = "Chi sei?   Che cosa vuoi?";
			link.l1 = "Il mio nome è Capitano "+GetFullName(pchar)+". Sto cercando Marisa Caldera.";
			link.l1.go = "Dolores_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Dolores_2":
			sld = CharacterFromID("PortoBello_priest");
			dialog.text = "Non conosco nessuna Marisa. Hai sbagliato porta. Vai via subito prima che chiami le guardie – ti butteranno fuori in un attimo.";
			link.l1 = "Padre "+sld.name+" mi ha detto che sei sua amica. Ho una lettera indirizzata a lei. A giudicare dal suo aspetto, è molto in ritardo. Vorrei consegnarla di persona.";
			link.l1.go = "Dolores_3";
		break;
		
		case "Dolores_3":
			dialog.text = "Ah, padre... È troppo gentile con tutti, ma raramente si sbaglia sulle persone. Puoi lasciare la lettera a me. Mi assicurerò che arrivi nelle sue mani.";
			link.l1 = "Perdonami, señorita, ma preferirei consegnarlo di persona. Potrebbe avere domande su come l'ho ottenuto e perché ci è voluto così tanto tempo per arrivare.";
			link.l1.go = "Dolores_4";
		break;
		
		case "Dolores_4":
			dialog.text = "E ti aspetti che creda semplicemente alle tue buone intenzioni? Ho visto fin troppi furfanti con la faccia da galantuomo. Lascia la lettera o vattene.";
			link.l1 = "Ti do la mia parola da capitano che non farò del male né a te né a Marisa. Inoltre, puoi invitare la guardia o chiunque altro sia abile con le armi al nostro incontro. Il mio unico scopo è consegnare questa lettera a Marisa di persona.";
			link.l1.go = "Dolores_5";
		break;
		
		case "Dolores_5":
			dialog.text = "D'accordo. Passa domani dopo le undici di sera. Non posso promettere che accetterà di incontrarti, ma le riferirò tutto quello che hai detto.";
			link.l1 = "Ci sarò. A presto.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Dolores_1");
		break;
		
		case "Marisa_1":
			dialog.text = "Ciao, "+GetAddress_Form(NPChar)+" "+pchar.lastname+". Mi stavi cercando, ed eccomi qui. Dolores ha detto che hai una lettera per me?";
			link.l1 = "Buongiorno, signora Caldera. Esatto, eccola qui. Purtroppo, sembra che ci sia voluto parecchio tempo per arrivare fino a lei.";
			link.l1.go = "Marisa_2";
			DelLandQuestMark(npchar);
			TakeItemFromCharacter(pchar, "LFD_letter");
			notification("Consegnato: Lettera per Marisa Caldera", "None");
		break;
		
		case "Marisa_2":
			dialog.text = "Dolores... Questa è la sua calligrafia... La calligrafia di Ramiro!";
			link.l1 = "...";
			link.l1.go = "Marisa_2_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
			sld = CharacterFromID("LFD_Dolores");
			LAi_CharacterEnableDialog(sld);
		break;
		case "Marisa_2_1":
			StartInstantDialog("LFD_Dolores", "Marisa_3", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_3":
			dialog.text = "Ma com'è possibile? Sono passati due anni!";
			link.l1 = "...";
			link.l1.go = "Marisa_3_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_3_1":
			StartInstantDialog("LFD_Marisa", "Marisa_4", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_4":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+" Capitano... Come sei entrato in possesso di questo? Dove l'hai trovato? Devo sapere tutto! Ti prego, dimmi tutto quello che sai.";
			link.l1 = "Questa lettera mi è stata consegnata da un marinaio. L’ha trovata in un angolo buio della stiva della sua nave e voleva portartela di persona, ma è stato costretto a tornare in fretta a bordo. Così mi ha chiesto di cercarti, ed eccomi qui. Questo è tutto ciò che so...";
			link.l1.go = "Marisa_5";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Marisa_5":
			dialog.text = "Grazie, "+GetAddress_Form(NPChar)+"! Grazie mille! Ti prego, non andare. Voglio parlare ancora un po' con te, ma prima... devo leggere questa lettera.";
			link.l1 = "Certo, Lady Caldera. Sarò qui.";
			link.l1.go = "Marisa_6";
		break;
		
		case "Marisa_6":
			DialogExit();
			SetLaunchFrameFormParam("Sono passati venti minuti, Marisa ha letto la lettera...", "Run_Function", 0, 4.0);
			SetLaunchFrameRunFunctionParam("LFD_Dolores_3", 0.0);
			LaunchFrameForm();
		break;
		
		case "Marisa_11":
			dialog.text = "Dolores... Ha scritto questa lettera prima della sua ultima traversata. Voleva dirmi che aveva l'opportunità di acquistare un grosso carico di ebano da un mercante a Belize, ma non aveva abbastanza denaro. È allora che ha chiesto questo prestito... Duecento dobloni... Ed è per questo che ora non riesco a trovare pace.";
			link.l1 = "...";
			link.l1.go = "Marisa_11_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_11_1":
			StartInstantDialog("LFD_Dolores", "Marisa_12", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_12":
			dialog.text = "Questo spiega tutto... Ma, ahimè, non alleggerirà il tuo fardello. Sii forte, Marisa. L’oscurità non è eterna, e questo debito non ti perseguiterà per sempre.";
			link.l1 = "...";
			link.l1.go = "Marisa_12_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_12_1":
			StartInstantDialog("LFD_Marisa", "Marisa_13", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_13":
			dialog.text = "No, Dolores, non ce ne sarà! Ramiro ha scritto che ha una scorta... nel nostro posto. Se è ancora intatta, forse potrò saldare il debito e finalmente fuggire da questo incubo.";
			link.l1 = "...";
			link.l1.go = "Marisa_13_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_13_1":
			StartInstantDialog("LFD_Dolores", "Marisa_14", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_14":
			dialog.text = "Il Signore ti ha mostrato misericordia! Ha ascoltato le nostre preghiere...";
			link.l1 = "...";
			link.l1.go = "Marisa_14_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_14_1":
			StartInstantDialog("LFD_Marisa", "Marisa_15", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_15":
			dialog.text = "Capitano, ancora una volta, grazie per avermi portato questa lettera. Significa tutto per me... Ma devo chiederti ancora un favore. Vedi, mio marito Ramiro era tutto per me, e non ho mai cercato protezione da nessun altro uomo. Ora che lui non c'è più, non ho più nessuno a cui rivolgermi, non ho una famiglia tutta mia\nDevo raggiungere il suo nascondiglio – è fuori città. Ma ho troppa paura di andarci da sola, i creditori di mio marito mi stanno cercando. Sei stato onorevole nel trovarmi per consegnare la lettera... Ti prego, aiutami ancora una volta.";
			link.l1 = "Certo, Marisa, ti accompagno io. Quando vuoi partire?";
			link.l1.go = "Marisa_16";
			link.l2 = "Mi dispiace, señora, ma la mia permanenza nella vostra città si è già protratta troppo a lungo. Le passeggiate in campagna non rientrano nei miei piani.";
			link.l2.go = "Marisa_end_1";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Marisa_end_1":
			dialog.text = "Capisco... Hai già fatto più di quanto potessi sperare. Grazie, Capitano, e addio.";
			link.l1 = "Addio.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_end");
		break;
		
		case "Marisa_16":
			dialog.text = "Grazie, Capitano. Vieni domani all'alba, entro le sette. Sarò pronto.";
			link.l1 = "Allora, fino al nostro prossimo incontro, señora.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_1");
		break;
		
		case "Marisa_21":
			if (GetHour() >= 7 && GetHour() <= 19)
			{
				if (pchar.sex == "man")
				{
					dialog.text = "Caballero, eccoti... Sei davvero un uomo d'onore! Partiamo. Il nostro cammino passa attraverso la giungla fino alla grotta, non lontano dalla Baia dei Mosquitos.";
				}
				else
				{
					dialog.text = "Capitano, eccoti qui... Sapevo che saresti venuta. Sai, è la prima volta che incontro una donna che comanda la propria nave. E posso già vedere che sei all'altezza di qualsiasi uomo—sia per onore che per nobiltà!";
				}
				link.l1 = "Eccellente, señora. Allora non perdiamo tempo. Stia vicino e non si allontani nemmeno per un attimo.";
				link.l1.go = "Marisa_go_cove";
				if (startHeroType == 4) // если ГГ Элен
				{
					link.l1 = "Grazie, Marisa. Mio padre era un capitano e un uomo d'onore – e fin da bambina mi ha trasmesso quegli stessi ideali.";
					link.l1.go = "Marisa_22";
				}
			}
			else
			{
				dialog.text = "Vieni all'alba, per le sette. Sarò pronto.";
				link.l1 = "Ci vediamo allora, señora.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Marisa_21";
			}
		break;
		
		case "Marisa_22":
			dialog.text = "Ah sì? Ha fatto la stessa fine del mio Ramiro?";
			link.l1 = "Di certo avrebbe preferito trovare la fine con la spada in pugno o nel mezzo di una tempesta. Ma il destino aveva altri piani – fu stroncato da una malattia di cui non parlò mai a nessuno.";
			link.l1.go = "Marisa_23";
		break;
		
		case "Marisa_23":
			dialog.text = "Mi dispiace per la tua perdita, "+pchar.name+" Il Signore prende i migliori tra noi... E anche se non sempre capiamo il perché, è la Sua volontà. Tutto ciò che possiamo fare è pregare per il riposo delle loro anime immortali.";
			link.l1 = "...";
			link.l1.go = "Marisa_24";
		break;
		
		case "Marisa_24":
			dialog.text = "Andiamo. La nostra strada passa attraverso la giungla fino alla grotta non lontano dalla Baia delle Zanzare.";
			link.l1 = "Certo. Resta vicino e non allontanarti nemmeno per un attimo.";
			link.l1.go = "Marisa_go_cove";
		break;
		
		case "Marisa_go_cove":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Marisa_2");
		break;
		
		case "Marisa_31":
			dialog.text = "Eccoci qui... Una volta io e Ramiro ci siamo riparati dalla pioggia proprio qui, quando eravamo giovani, prima che diventasse mio marito. Fu allora che mi disse che avrebbe conquistato il mio cuore, a qualunque costo.";
			link.l1 = "Mi dispiace che sia dovuta venire qui da sola, senza suo marito, señora. Luoghi come questo custodiscono molti ricordi. Diamoci un'occhiata intorno – forse, oltre ai ricordi, troveremo ciò che Ramiro aveva messo da parte per i momenti più difficili.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_4");
		break;
		
		case "Marisa_32":
			dialog.text = ""+GetSexPhrase("Signore "+pchar.lastname+"",""+pchar.name+"")+"... Hai trovato qualcosa? È quello che ha lasciato Ramiro? Non so nemmeno cosa mi spaventi di più – che sia vuoto, o che non basti a coprire il debito...";
			if (PCharDublonsTotal() >= 400 && GetCharacterItem(pchar, "jewelry2") >= 10 && GetCharacterItem(pchar, "jewelry3") >= 10 && CheckCharacterItem(PChar, "mushket1"))
			{
				link.l1 = "(mostra) Ecco, questo è tutto quello che c'era nel forziere. Spero che sia abbastanza per cambiare il tuo destino in meglio.";
				link.l1.go = "Marisa_33";
				DelLandQuestMark(npchar);
			}
			else
			{
				link.l1 = "Sto ancora rovistando nel forziere.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Marisa_32";
			}
		break;
		
		case "Marisa_33":
			dialog.text = "Ah, Capitano! Certo! Questo dovrebbe bastare! Ma non posso lasciare che il tuo aiuto resti senza ricompensa. Prendi cento dobloni. Se non fosse stato per te, non avrei mai saputo di questo nascondiglio e starei ancora nascondendomi dagli uomini mandati dal creditore di Ramiro...";
			link.l1 = "Sei molto generosa, señora, grazie. Nel nostro mestiere, l’oro non va mai sprecato.";
			link.l1.go = "Marisa_34";
			link.l2 = "No, señora. Questo denaro serve a lei molto più che a me. L’importante è che ora può lasciarsi alle spalle i suoi problemi e vivere in pace. Per me questo è più che sufficiente.";
			link.l2.go = "Marisa_35";
			RemoveDublonsFromPCharTotal(400);
			RemoveItems(pchar, "jewelry2", 10);
			RemoveItems(pchar, "jewelry3", 10);
			TakeItemFromCharacter(pchar, "mushket1");
			TakeItemFromCharacter(pchar, "obereg_7");
			TakeItemFromCharacter(pchar, "amulet_11");
			notification("Consegnato: Amuleto 'Cimaruta'", "None");
			notification("Consegnato: Amuleto 'Pescatore'", "None");
			notification("Consegnato: Moschetto Matchlock", "None");
			notification("Consegnato: Diamante (10)", "None");
			notification("Consegnato: Rubino (10)", "None");
		break;
		
		case "Marisa_34":
			dialog.text = "E allora, "+GetSexPhrase("signore",""+pchar.name+"")+", dobbiamo muoverci. Se mi hanno visto in città, qualcuno potrebbe seguirci. Meglio non indugiare qui.";
			link.l1 = "Hai ragione, Marisa. Andiamo.";
			link.l1.go = "Marisa_naemnik";
			TakeNItems(pchar, "gold_dublon", 100);
		break;
		
		case "Marisa_35":
			dialog.text = "Capitano, per favore... mio marito teneva quest'arma per proteggere la nostra famiglia, e sono certa che—nelle tue mani—servirà una giusta causa. Ramiro sarebbe felice di sapere che è finita alla persona che mi ha salvato quando ogni speranza era perduta.";
			link.l1 = "D'accordo, Marisa, grazie. Sei una donna gentile e onorevole, e mi dispiace davvero che il destino sia stato così crudele con te.";
			link.l1.go = "Marisa_36";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "Marisa_36":
			dialog.text = "A volte il Signore ci manda giorni difficili, o persino anni, per mettere alla prova la nostra fede, ma non abbandona mai chi segue la retta via. Ti ha mandato qui per aiutarmi e ora, spero, il mio più grande problema sarà presto alle mie spalle.\nMa per ora, è il momento di tornare indietro. Siamo rimasti qui abbastanza a lungo, e potrebbe essere pericoloso, visto che mi stanno ancora cercando.";
			link.l1 = "Certo, señora, andiamo.";
			link.l1.go = "Marisa_naemnik";
			GiveItem2Character(pchar, "mushket1");
			GiveItem2Character(pchar, "obereg_7");
			GiveItem2Character(pchar, "amulet_11");
		break;
		
		case "Marisa_naemnik":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Marisa_6");
		break;
		
		case "Naemnik_1":
			dialog.text = "Ah! Ecco il nostro scomparso! Davvero pensavi di poterti nascondere qui, in questo buco come un topo, e che io non ti avrei trovato? Ho rivoltato la città più di una volta, e invece eri qui per tutto questo tempo"+GetSexPhrase(", e oltre a tutto questo, sei pure uscita con qualche ragazzino. Dov’è il mio denaro, piccola puttana? Faresti meglio a consegnarmelo subito, o questa caverna sarà la tua tomba.",".")+"";
			link.l1 = "...";
			link.l1.go = "Naemnik_1_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Naemnik"));
			CharacterTurnByChr(CharacterFromID("LFD_Naemnik"), CharacterFromID("LFD_Marisa"));
		break;
		case "Naemnik_1_1":
			StartInstantDialog("LFD_Marisa", "Naemnik_2", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Naemnik_2":
			dialog.text = "Tu...";
			link.l1 = "...";
			link.l1.go = "Naemnik_2_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Naemnik"));
			CharacterTurnByChr(CharacterFromID("LFD_Naemnik"), CharacterFromID("LFD_Marisa"));
		break;
		case "Naemnik_2_1":
			StartInstantDialog("LFD_Naemnik", "Naemnik_3", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Naemnik_3":
			dialog.text = "...";
			link.l1 = "Quindi sei tu quello che si guadagna da vivere estorcendo denaro alle donne? A giudicare dal mestiere che hai scelto, l'intelligenza non è mai stata il tuo punto forte. Mi sorprende che tu sia riuscito ad arrivare fin qui da solo, invece di limitarti a seguire qualcuno più sveglio... come il tuo stesso stivale, per esempio.";
			link.l1.go = "Naemnik_4";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Naemnik_4":
			if (pchar.sex == "man")
			{
				dialog.text = "Chiudi quella bocca, eroe. Il tuo turno arriverà, ma prima me la vedo con lei. Deve cinquecentoventicinque dobloni – è il suo debito con gli interessi. O paga tutto subito, o resta qui per sempre – a dar da mangiare ai vermi. Ma visto che sei così giusto, puoi pagare tu per lei, e io sparisco.";
				if (PCharDublonsTotal() >= 525)
				{
					link.l1 = "Pensi davvero di poter entrare qui, insultare una signora, ignorarmi e andartene via tutto intero, con i dobloni per giunta? Non sembri particolarmente sveglio. Ma non inizierò una rissa davanti a una donna. Quindi ecco la mia proposta: chiedi scusa a Madam Caldera, prendi i tuoi dobloni e sparisci da qui. Oppure dovrò insegnarti io come ci si comporta, dopotutto.";
					link.l1.go = "Naemnik_5";
					Notification_Money(true, 525, "dublon");
				}
				else
				{
					Notification_Money(false, 525, "dublon");
				}
			}
			else
			{
				dialog.text = "Chiudi quella bocca e aspetta il tuo turno. Mi occuperò di te dopo, quando avrò finito con questa miserabile. Deve cinquecentoventicinque dobloni – è il suo debito con gli interessi. Se ti senti così giusto, paga tu per lei, e io me ne andrò.";
				if (PCharDublonsTotal() >= 525)
				{
					link.l1 = "Bene, sono disposto a perdonare i tuoi modi bruschi e persino la tua maleducazione nei miei confronti. Ma se vuoi prendere i tuoi dobloni e andartene di qui sano e salvo, dovrai chiedere scusa a Lady Caldera. Altrimenti vedremo chi sa maneggiare meglio un'arma. E credimi, non porto la mia solo per bellezza.";
					link.l1.go = "Naemnik_5";
					Notification_Money(true, 525, "dublon");
				}
				else
				{
					Notification_Money(false, 525, "dublon");
				}
			}
			link.l2 = "Chiaramente, non sei affatto gravato dall’ingegno se pensavi che avrei aspettato il mio turno. E ancor meno se credevi che avrei chiuso un occhio su tutti i guai che tu e i tuoi simili avete causato a Lady Caldera.";
			link.l2.go = "Naemnik_bitva";
		break;
		
		case "Naemnik_5":
			dialog.text = "E va bene, fai come vuoi. Se possiamo ottenere il denaro senza rischi inutili, non vedo perché dovrei rischiare la pelle. Consegnami i dobloni – e vattene.";
			link.l1 = "Prima, chiedi scusa alla signora.";
			link.l1.go = "Naemnik_6";
		break;
		
		case "Naemnik_6":
			dialog.text = "Perdonatemi, señora. Il diavolo ha avuto la meglio su di me.";
			link.l1 = "...";
			link.l1.go = "Naemnik_7";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Naemnik"));
			CharacterTurnByChr(CharacterFromID("LFD_Naemnik"), CharacterFromID("LFD_Marisa"));
		break;
		
		case "Naemnik_7":
			dialog.text = "Felice"+GetSexPhrase("","")+"? Consegnami l'oro e me ne andrò. Ho già fin troppe cose da fare, non ho tempo da perdere in chiacchiere con te.";
			link.l1 = "Prendi i tuoi dobloni e vattene di qui.";
			link.l1.go = "Naemnik_7_1";
			CharacterTurnByChr(npchar, pchar);
			RemoveDublonsFromPCharTotal(525);
		break;
		
		case "Naemnik_7_1":
			StartInstantDialog("LFD_Marisa", "Marisa_37", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			ChangeCharacterNationReputation(pchar, SPAIN, 10);
		break;
		
		case "Marisa_37":
			dialog.text = "Capitano, davvero, non capisco... Cosa significa tutto questo?";
			link.l1 = "Questo significa che ora non devi più nulla. Sei libero.";
			link.l1.go = "Marisa_38";
			CharacterTurnByChr(npchar, pchar);
			
			sld = CharacterFromID("LFD_Naemnik");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", 5);
			sld.lifeday = 0;
		break;
		
		case "Marisa_38":
			dialog.text = "Ma... non ho tutta la somma per restituirtela adesso. Se potessi aspettare un po'...";
			link.l1 = "Non capisci, Marisa. Non mi devi nulla. Non devi più niente a nessuno. E i soldi che hai trovato ti saranno molto utili. Torna alla tua vecchia vita – la chiesa ti aspetta.";
			link.l1.go = "Marisa_39";
		break;
		
		case "Marisa_39":
			dialog.text = "Io... io proprio non ci credo. Cose del genere non succedono, "+GetSexPhrase("caballero","signorina")+"! Hai pagato una fortuna per me... così, senza motivo? E ora è tutto finito? Niente debiti, nessuno che mi rincorre? Dimmi, è vero?";
			link.l1 = "È vero, señora. È tutto finito. Non devi più niente a nessuno.";
			link.l1.go = "Marisa_40";
		break;
		
		case "Marisa_40":
			dialog.text = "Oh, Capitano, sei così nobile! Sento come se fossi stato mandato da Dio! Ma non riesco nemmeno a immaginare come potrei ringraziarti. Tu hai... completamente cambiato la mia vita, e io... cosa potrei mai fare per te?";
			link.l1 = "Non devi fare nulla, Marisa. Vivi soltanto. Senza paura, senza le catene del passato. Torna alla tua vecchia vita e trova la felicità lì – sarà il modo migliore per ringraziarmi. Vieni, ti accompagno in città.";
			link.l1.go = "Naemnik_mir";
		break;
		
		case "Naemnik_bitva":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Naemnik_bitva");
		break;
		
		case "Naemnik_mir":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Naemnik_mir");
		break;
		
		case "Marisa_41":
			dialog.text = "Che cosa hai fatto, Capitano, l'hai ucciso!";
			link.l1 = "Esatto, señora. Dovevo proteggere te e il tuo onore...";
			link.l1.go = "Marisa_42";
		break;
		
		case "Marisa_42":
			dialog.text = "Oh, Capitano, togliere una vita, anche una come la sua, è un peccato terribile e gravoso! Dovrai pregare giorno e notte per lavarne almeno una parte dalla tua anima immortale. Dio mi è testimone, avrei potuto semplicemente dargli tutto ciò che avevo e se ne sarebbe andato... Ma ora... ora il suo sangue è sulle tue mani, e solo il cielo deciderà se sarai perdonato!";
			link.l1 = "Forse era la volontà del Signore. Ma non soffermiamoci su questo. Usciamo piuttosto da questa grotta.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Naemnik_bitva_3");
		break;
		
		case "Marisa_51":
			dialog.text = "Capitano, permettimi di ringraziarti ancora una volta! Pregherò per la tua salute e il tuo benessere, "+pchar.name+". Per favore, vieni nella nostra chiesa – che il Signore ti conceda il perdono per tutti i tuoi peccati e la Sua benedizione.";
			link.l1 = "Forse passerò a trovarti qualche volta. E ricorda, Marisa, se non vedrò il tuo bel sorriso lì, sarò molto deluso.";
			link.l1.go = "Marisa_52";
		break;
		
		case "Marisa_52":
			dialog.text = "Ah, "+GetAddress_Form(NPChar)+"... Sei così gentile con me. Sarò davvero felice di rivederti nella nostra città. Ma per ora, perdonami, non vedo l'ora di rimettere in ordine la mia vita e condividere la bella notizia con Dolores.";
			link.l1 = "Certo, Marisa. Addio. Abbi cura di te.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_In_Church");
		break;
		
		case "Marisa_54":
			dialog.text = "Capitano, permettimi ancora una volta di esprimerti la mia infinita gratitudine! Hai fatto per me l’impossibile! Per la tua gentilezza e nobiltà, voglio raccontarti come sono riuscito a sfuggire ai mercenari in questi ultimi due anni. Forse un giorno questa conoscenza potrà tornare utile anche a te.";
			link.l1 = "Grazie, señora. In questioni come queste, la conoscenza vale quanto l’oro. Ti ascolto.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Finish_In_Town_NaemnikAlive_2");
		break;
		
		case "Marisa_55":
			dialog.text = "Ecco come ho passato questi due anni. In un mondo dove la forza conta così tanto, saper restare nell’ombra apre porte che gli altri possono solo sognare.";
			link.l1 = "Grazie per aver condiviso la tua storia, Marisa. Hai passato davvero tanto, e la tua esperienza è davvero preziosa.";
			link.l1.go = "Marisa_56";
			AddCharacterExpToSkill(pchar, "Sneak", 500);
		break;
		
		case "Marisa_56":
			dialog.text = "Sarò davvero felice di rivederti nella nostra città. Ti prego, vieni nella nostra chiesa—che il Signore ti conceda il perdono per tutti i tuoi peccati e la Sua benedizione.";
			link.l1 = "Forse passerò di tanto in tanto. E ricorda, Marisa, se non vedrò il tuo bel sorriso lì, sarò molto deluso.";
			link.l1.go = "Marisa_57";
		break;
		
		case "Marisa_57":
			dialog.text = "Ah, Capitano... Sei così gentile con me. Ma ora, perdonami, non vedo l'ora di rimettere in ordine la mia vita e condividere la bella notizia con Dolores.";
			link.l1 = "Certo, Marisa. Addio. Abbi cura di te.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_In_Church");
			
			//слухи
			AddSimpleRumourCity(""+GetSexPhrase("Avete sentito? Il capitano "+GetFullName(pchar)+" ha pagato di tasca propria i debiti della vedova Calder! Non molti rinuncerebbero a una tale somma per aiutare uno sconosciuto. In Spagna esistono ancora veri caballeros!", "È bello vedere che in Spagna ci sono non solo caballeros d'onore, ma anche donne il cui coraggio e onore non sono inferiori a quelli degli uomini.")+"", "PortoBello", 7, 1, "");
			AddSimpleRumourCity("Si dice che un capitano abbia donato il proprio denaro per liberare la vedova Calder dai debiti lasciati dal marito defunto! Non tutti farebbero un gesto così nobile. Un vero uomo d'onore, non è vero?", "PortoBello", 7, 1, "");
		break;
		
		case "Marisa_61":
			if (CheckAttribute(pchar, "questTemp.LFD_NaemnikDead"))
			{
				switch (rand(1))
				{
					case 0:
						dialog.text = "Capitano, che piacere rivederti! Speravo proprio che passassi di qui. Forse oggi hai tempo di fermarti un po' e pregare?";
						link.l1 = "Contento"+GetSexPhrase("","")+" incontro, Marisa. Ma temo di non potermi trattenere adesso. Ricordo il mio dovere verso il Signore, ma la preghiera dovrà aspettare.";
						link.l1.go = "Marisa_62";
					break;

					case 1:
						dialog.text = "Capitano, di nuovo lei! Sempre un piacere. Pare che il Signore non voglia farle dimenticare la strada per la chiesa... Forse troverà un momento per pregare, dopotutto?";
						link.l1 = "Marisa, è un piacere vederti. Ma non posso fermarmi – i miei affari non possono aspettare. Credo che il Signore conosca i miei pensieri anche senza preghiera.";
						link.l1.go = "Marisa_63";
					break;
				}
			}
			else
			{
				switch (rand(1))
				{
					case 0:
						dialog.text = "Capitano, che gioia rivederla! Ogni giorno ringrazio il Signore per la sua gentilezza. Il mondo è diventato più luminoso quando mi ha aiutato.";
						link.l1 = "Contento"+GetSexPhrase("","")+"   Sono felice di vederti in buona salute, Marisa. Spero che la vita non ti abbia riservato altre brutte sorprese. Sembri molto più serena.";
						link.l1.go = "Marisa_64";
					break;

					case 1:
						dialog.text = "Capitano, sono così felice di vederti! Ogni volta che vieni nella nostra chiesa, sento una grande pace. Porti con te la luce delle buone azioni.";
						link.l1 = "E sono contento"+GetSexPhrase("","")+"   Felice di vederti, Marisa. Ti sei abituata a una vita tranquilla, o ogni tanto ti capita ancora di guardare indietro?";
						link.l1.go = "Marisa_65";
					break;
				}
			}
			SetTimerFunction("LFD_Marisa_HelloAgain", 0, 0, 1);
		break;
		
		case "Marisa_62":	
			dialog.text = ""+pchar.name+",   se tutti continuassero a rimandare la preghiera, il mondo sarebbe già precipitato nell’oscurità da tempo.   Metti da parte le tue preoccupazioni per un po’ – il pentimento ti dà la forza di andare avanti.";
			link.l1 = "Capisco, Marisa, ma davvero non posso adesso. Credo che il Signore mi ascolterà anche senza parole.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_62_1";
		break;
		
		case "Marisa_62_1":	
			dialog.text = ""+pchar.name+", hai cambiato idea? I peccati non svaniscono da soli, e più aspetti, più diventano pesanti.";
			link.l1 = "Ahimè, devo andare. Ma la prossima volta, prometto che pregherò.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_62_1";
		break;
		
		case "Marisa_63":	
			dialog.text = "Ma la fede non è solo sapere, è agire! Non puoi continuare a rimandare il cammino verso la redenzione all’infinito. Non vuoi sentire il sollievo di liberarti dal peso del peccato?";
			link.l1 = "Forse, ma non ora. Che il Signore mi ascolti, anche se la preghiera dovrà attendere.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_63_1";
		break;
		
		case "Marisa_63_1":	
			dialog.text = "Capitano, non credi che rimandare il pentimento sia già di per sé un peccato? Un giorno potrebbe essere troppo tardi.";
			link.l1 = "Forse, ma temo di non avere tempo oggi. La fede è con me, e il Signore vede il mio pentimento anche senza preghiera.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_63_1";
		break;
		
		case "Marisa_64":	
			dialog.text = "Sì, grazie a te posso finalmente respirare di nuovo. Che il Signore vegli su di te e sul tuo viaggio. Forse vorresti pregare con me?";
			link.l1 = "Credo che le tue preghiere siano già abbastanza forti così. Ciò che conta di più è che ora sei circondata solo dalla gentilezza.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_64_1";
		break;
		
		case "Marisa_64_1":	
			dialog.text = ""+pchar.name+", hai cambiato idea dopotutto? Preghiamo il nostro Creatore?";
			link.l1 = "Purtroppo, Marisa, devo andare adesso, ho delle cose da fare.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_64_1";
		break;
		
		case "Marisa_65":	
			dialog.text = "Cerco di guardare solo avanti. Ora ho un futuro, e tutto questo è grazie a te. Forse dovremmo ringraziare insieme il Signore per questo?";
			link.l1 = "Penso che te la caverai meglio di me. L'importante è che le tue preghiere ti diano pace.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_65_1";
		break;
		
		case "Marisa_65_1":	
			dialog.text = ""+pchar.name+", forse posso convincerti a recitare almeno una preghiera?";
			link.l1 = "Perdonami, Marisa, ma purtroppo adesso non ho tempo. Prega anche per me.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_65_1";
		break;
		
		case "Marisa_Ne_Ta_Peshera":	
			dialog.text = "Capitano, questo non è il posto. La grotta che ci serve è vicino alla Baia dei Mosquitos.";
			link.l1 = "...";
			link.l1.go = "Marisa_Ne_Ta_Peshera_1";
		break;
		
		case "Marisa_Ne_Ta_Peshera_1":	
			DialogExit();
			NextDiag.TempNode = "Marisa_31";
			DeleteQuestCondition("LFD_Ne_Ta_Peshera");
			
			sld = CharacterFromID("LFD_Marisa");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
		break;
		
	}
}
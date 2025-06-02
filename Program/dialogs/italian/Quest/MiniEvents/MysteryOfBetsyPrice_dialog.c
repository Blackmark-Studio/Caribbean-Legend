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
			dialog.text = "Cosa vuoi, forestiero?";
			link.l1 = "Niente.";
			link.l1.go = "exit";
		break;

		case "Poorman_1":
			if (pchar.sex == "woman")
			{
				dialog.text = "Ehi, bellezza, che ne dici di un ornamento squisito per la collezione della tua dama? Un vero tesoro! Tu avrai sguardi ammirati, io qualche moneta per il pane e un sorso di rum.";
			}
			else
			{
				dialog.text = "Ehi, Capitano, che ne dici di un dono squisito per la tua dama? Un vero tesoro! Tu guadagni la sua gratitudine ardente, io mi prendo qualche moneta per il pane e un goccio di rum.";
			}
			link.l1 = "Così che fra un’ora arrivino i soldati a prendermi e mi sbattano in galera per furto? E tu dove l’hai trovato, vagabondo?";
			link.l1.go = "Poorman_2_fortune";
			link.l2 = "Un dono squisito? E dove mai un pezzente come te, senza tetto né patria, potrebbe procurarselo?";
			link.l2.go = "Poorman_2_leadership";
			if (npchar.quest.meeting == "0") npchar.quest.meeting = "1";
		break;

		case "Poorman_2_fortune":
			dialog.text = ""+GetSexPhrase("Capo, io","Io")+" ho trovato questo bel pendente con un cammeo, per mille balene! Che mi porti giù il diavolo se mento! Era lì, abbandonato, nessuno lo voleva. Non potevo lasciare un simile tesoro nella polvere, vero?";
			link.l1 = "D'accordo. Fammi vedere cosa hai lì.";
			link.l1.go = "Poorman_3";
			link.l2 = "Chi mai crederebbe alle parole di un gentiluomo così rispettabile come voi? Cercate qualcun altro più credulone.";
			link.l2.go = "Poorman_exit";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

		case "Poorman_2_leadership":
			dialog.text = ""+GetSexPhrase("Capo, io","Io")+" ho trovato questo pendente magnifico con un cammeo, parola d’onore! Che mi prenda la maledizione se sto mentendo! Era lì, abbandonato, nessuno lo voleva. Non potevo lasciare una simile meraviglia fra la polvere, vero?";
			link.l1 = "D'accordo. Fammi vedere cosa hai lì.";
			link.l1.go = "Poorman_3";
			link.l2 = "Chi mai crederebbe alle parole d’un gentiluomo così rispettabile come voi? Cercate qualcun altro più allocco.";
			link.l2.go = "Poorman_exit";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Poorman_exit":
			DialogExit();
			AddDialogExitQuestFunction("TBP_PismoVDome");
		break;
		
		case "Poorman_3":
			dialog.text = "Guarda... è proprio un bel pezzo! L'ho trovato in un'aiuola, vicino alla casa con la lanterna, vicino alla taverna. Ma lì non ci vive anima viva da un bel po', quindi non c'è nessuno a cui restituirlo.";
			link.l1 = "Curioso gingillo, eh. E quanto ne vuoi, per questa robetta?";
			link.l1.go = "Poorman_4";
		break;

		case "Poorman_4":
			dialog.text = "Solo cento pesos"+GetSexPhrase(", Capitano","")+"... solo pochi spiccioli per uno come te! E per me – una settimana intera senza dovermi scervellare dove trovare un tozzo di pane. Guarda solo che meraviglia!";
			if (sti(pchar.Money) >= 100)
			{
				link.l1 = "Va bene, ecco i tuoi cento pesos.";
				link.l1.go = "Poorman_5";
			}
			link.l2 = "Penso che passerò. Vai a tentare fortuna con qualcun altro.";
			link.l2.go = "Poorman_exit";
		break;

		case "Poorman_5":
			dialog.text = "Grazie, "+GetAddress_Form(NPChar)+"! Ora la fortuna ti sorriderà di sicuro! Sei una brava persona, si vede subito.";
			link.l1 = "...";
			link.l1.go = "Poorman_exit";
			GiveItem2Character(PChar, "jewelry24");
			pchar.questTemp.TBP_BuyKulon = true;
			pchar.questTemp.TBP_BuyKulonOtdatBetsy = true;
		break;
		
		case "Pirate_1":
			if (pchar.sex == "woman")
			{
				dialog.text = "O-o-oh, chi ci viene a trovare? Pare che tu non abbia sbagliato porta, tesoruccio... avanti, avanti! Spogliati pure, mettiti comodo come a casa tua.";
				link.l1 = "Ehi, ehi... Chi abbiamo qui? Non siete forse gli stessi furfanti che hanno lasciato quel 'dolce' messaggio minaccioso per Betsy?";
			}
			else
			{
				dialog.text = "E che razza di calamaro sei tu?! Hai sbagliato porta, testa di capra? Fuori dai piedi prima che ti sventri!";
				link.l1 = "Ebbene, ebbene... Chi abbiamo qui? Non siete forse voi gli stessi sciocchi che avete lasciato quel bel messaggio minaccioso per Betsy?";
			}
			link.l1.go = "Pirate_2";
		break;

		case "Pirate_2":
			if (pchar.sex == "woman")
			{
				dialog.text = "Betsy? Al diavolo quella Betsy! Quello che mi intriga davvero è che ci fai qui, bellezza... Ormai che sei arrivata – niente fretta di andar via, troveremo il modo di tenerti occupata...";
			}
			else
			{
				dialog.text = "Che diavolo, Betsy? Non sfidare la sorte, sciocco. Finché puoi ancora andartene con le tue gambe – vattene. Altrimenti dovremo raccoglierti a pezzi e portarti via in un secchio!";
			}
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_HouseBetsi_2");
		break;

		case "BetsiPrice_1":
			dialog.text = " Aiuto! Aiuto, vi supplico! ";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_HouseBetsi_3");
			locCameraFromToPos(1.40, 1.62, 1.14, false, 2.58, -0.30, -1.64);
		break;
		
		case "Pirate_3":
			dialog.text = "...";
			link.l1 = "Eccola lì. Sei nei guai fino al collo, amico mio, e se non vuoi che questa sia la tua ultima sciocchezza, ti consiglio di lasciarla andare. Subito.";
			link.l1.go = "Pirate_4";
		break;

		case "Pirate_4":
			dialog.text = "Ah! L’hai sentito, Reggie? "+GetSexPhrase("È","Lei è")+" persino minacciandoci. "+GetSexPhrase("Che lumacone presuntuoso","Che feccia sfrontata")+". Ehi, facciamo vedere "+GetSexPhrase("questo moccioso, vediamo di che colore ha le budella","questo moccioso imparerà cos’è il vero tormento")+".";
			link.l1 = "Sarà la tua rovina.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_HouseBetsi_4");
		break;

		case "Pirate_5":
			if (!CharacterIsAlive("TBP_Bandit_1"))
			{
				dialog.text = "...";
				link.l1 = "Ora lascia andare la ragazza. O finirai sdraiato accanto al tuo compare.";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("TBP_HouseBetsi_6");
			}
			else
			{
				dialog.text = "...";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Pirate_5";
			}
		break;

		case "BetsiPrice_2":
			dialog.text = "Maledetti cani! Credevate che me ne sarei stato zitto?!";
			link.l1 = "...";
			link.l1.go = "BetsiPrice_2_1";
			sld = CharacterFromID("TBP_Bandit_2");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("TBP_BetsiPrice"));
			CharacterTurnByChr(npchar, sld);
		break;

		case "BetsiPrice_2_1":
			dialog.text = "E tu... Non sembri dei loro. Chi sei, di grazia?";
			link.l1 = "Capitano "+GetFullName(pchar)+", al vostro servizio.";
			link.l1.go = "BetsiPrice_2_2";
			CharacterTurnByChr(npchar, pchar);
		break;

		case "BetsiPrice_2_2":
			dialog.text = "Dunque, ti devo la vita?";
			link.l1 = "Così pare. Ma adesso c’è qualcosa di più importante – chi diavolo sono questi e in che guaio ti sei cacciato, eh?";
			link.l1.go = "BetsiPrice_3";
		break;
		
		case "BetsiPrice_3":
			dialog.text = "Questi uomini... Li ha mandati un pezzo grosso inglese. Un tempo eravamo assai vicini... e ora, come vedi, mi vuole sotto terra.";
			link.l1 = "Credo di cominciare a capire la tua storia. Eri la sua amante, ma ad un certo punto hai pensato di sfruttare la cosa a tuo favore. Hai voluto spaventarlo... magari minacciare di raccontare tutto alla sua famiglia?";
			link.l1.go = "BetsiPrice_4";
		break;

		case "BetsiPrice_4":
			dialog.text = "Sei incredibilmente vicino"+GetSexPhrase("   alla verità, bel capitano","   alla verità, bellezza")+"... e allo stesso tempo molto lontano da ciò. Se fosse stato così, sarei già morta ormai. Sì, ero la sua amante, ma non mi è mai passato per la testa di creare drammi familiari.\nEra tutto molto più contorto: un giorno scoprii che si era trovato un nuovo giocattolo e aveva deciso di sbarazzarsi di me, lasciandomi con un pugno di mosche. Gettarmi via come un oggetto inutile. Ebbene, non sono abituata ad andarmene a mani vuote.\nCosì presi ciò che contava davvero – dei documenti in grado di rovinarlo – e me la diedi a gambe nel Nuovo Mondo. Poi proposi uno scambio: i suoi segreti in cambio della mia pelle salva e di una lauta ricompensa.\nEcco perché sono ancora in vita: hanno bisogno di quei documenti. E io non avevo alcuna fretta di svelare dove li avevo nascosti.";
			link.l1 = "Ebbene, non sei solo bella, ma anche maledettamente furba. Hai giocato d'azzardo, ma diciamoci la verità – ormai questa partita ti è sfuggita di mano. Forse è il momento di pensare a un'altra via, finché hai ancora tempo per tirarti fuori? Se ti hanno scovata qui, difficilmente potrai nasconderti altrove. Prima o poi la tua fortuna finirà, stattene certa.";
			link.l1.go = "BetsiPrice_5";
		break;

		case "BetsiPrice_5":
			dialog.text = "Cosa proponi? Che gli consegni i documenti e resti a mani vuote? Dopo tutto quello che ho passato?";
			link.l1 = "Ti rendi conto che per loro sei solo una scocciatura da far fuori. Non si fermeranno finché non avranno ciò che vogliono. Ma tu hai ancora una scelta. Dai i documenti a quello stolto laggiù. Lascialo portarli al suo padrone e convincilo che hai rinunciato alle tue intenzioni e desideri solo che tutto finisca qui.";
			link.l1.go = "BetsiPrice_6";
		break;

		case "BetsiPrice_6":
			dialog.text = "Se questa è la mia unica occasione... Va bene, sono pronta a rischiare. Ho sempre tenuto i documenti con me. Li ho cuciti nel mio corsetto, così non me ne separo nemmeno per un attimo. Aspetta, solo un istante...";
			link.l1 = "...";
			link.l1.go = "BetsiPrice_7";
		break;

		case "BetsiPrice_7":
			dialog.text = "Ecco, prendi. Questi sono tutti i documenti che avevo. Vorrai dire due parole d’addio a quella creatura? Hai la lingua sciolta, vero?";
			link.l1 = "Penso che abbia già imparato la lezione principale. Ora dobbiamo solo spiegargli chiaramente cosa deve fare.";
			link.l1.go = "exit";
			notification(StringFromKey("Neutral_15"), "BoxMinus");
			PlaySound("interface\\important_item.wav");
			AddDialogExitQuestFunction("TBP_HouseBetsi_11");
		break;
		
		case "Pirate_6":
			dialog.text = "...";
			link.l1 = "Alzati. E ascoltami bene, bastardo. Ecco i documenti per cui sei stato mandato. Portali al tuo padrone e digli questo: se continuerà a mandare tagliagole dietro Betsy, faranno la stessa fine dei tuoi compagni. Digli che lei se ne va dalla sua vita per sempre – e non ha più alcun motivo per inseguirla. Che prenda questo gesto come il suo passo volontario verso la pace. Spero che abbia abbastanza senno da chiudere la faccenda qui. Hai capito tutto, o devo ficcartelo in testa a forza?";
			link.l1.go = "Pirate_7";
			notification(StringFromKey("Neutral_16"), "BoxMinus");
			PlaySound("interface\\important_item.wav");
		break;

		case "Pirate_7":
			dialog.text = "Ho capito tutto, "+GetAddress_Form(NPChar)+"...";
			link.l1 = "Allora sparisci da qui. E non ti venga in mente di restare nei paraggi – se ti rivedo da queste parti, la prossima volta non sarai così fortunato.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_HouseBetsi_12");
		break;

		case "BetsiPrice_8":
			dialog.text = "Ebbene, "+GetSexPhrase("mio eroe","la mia furia")+", pare persino che mi sia scordato di ringraziarti... Tutta colpa dell'agitazione. Non capita ogni giorno di finire prigioniero, e poi riavere la libertà grazie a un tale coraggioso "+GetSexPhrase("salvatore","salvatrice")+" Dimmi, è una tua abitudine salvare dame in pericolo, o sono solo incredibilmente fortunata?";
			link.l1 = "Che posso dire, Betsy, ho un debole per le entrate teatrali e "+GetSexPhrase("belle signore","ogni sorta d’avventure")+".";
			link.l1.go = "BetsiPrice_9";
		break;

		case "BetsiPrice_9":
			dialog.text = "Mi chiamo Miranda. Miranda Bell. Ho preso il nome Betsy quando sono dovuta sparire – nuova vita, nuovo nome, capisci. Sono fuggita dall’Europa così in fretta che sono riuscita a prendere solo qualche moneta e un paio di gioielli. Il resto sarà finito a quei cani maledetti che mi davano la caccia. Ora, invece di ricevimenti sontuosi e abiti pregiati, mi ritrovo in una lurida catapecchia in periferia a sgobbare in una taverna. Mai avrei pensato di servire rum invece di sorseggiare vino in buona compagnia...";
			link.l1 = "Nonostante tutto questo, sembri padroneggiare il destino stesso. Forse è proprio lì che risiede il tuo vero talento.";
			link.l1.go = "BetsiPrice_10";
		break;

		case "BetsiPrice_10":
			dialog.text = ""+GetSexPhrase("Lusingatore. Ma, sai, ti calza a pennello","Mi lusinghi")+"... Dopo tutto questo, mi sento un po’ agitato. E se mi stessero già aspettando dietro l’angolo? Accompagnami a casa, sii il mio "+GetSexPhrase("salvatore","salvatrice")+" ancora per un altro po'.";
			link.l1 = "Non sono tipo da lasciare le cose a metà. Dunque, madama, sono al vostro servizio. Andiamo.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_ProvodimDoDoma");
		break;

		case "BetsiPrice_11":
			dialog.text = "Eccoci qua. Dimmi, quale vento ti ha portato in quella casa, eh?";
			link.l1 = "Non ero lì per caso. L’oste pareva davvero turbato dalla tua sparizione e m’ha chiesto di scoprire che fine avessi fatto. Eh, potevo forse tirarmi indietro? Lasciar una dama nei guai non si confà a un capitano degno di questo nome.";
			link.l1.go = "BetsiPrice_12";
			if (CheckAttribute(pchar, "questTemp.TBP_BuyKulonOtdatBetsy") && pchar.questTemp.TBP_BuyKulonOtdatBetsy == true)
            {
			link.l2 = "Non ci sono finito per caso. È stato questo ciondolo a portarmici. Prendilo.​ Il taverniere sembrava davvero turbato per la tua sparizione e mi ha chiesto di scoprire cosa fosse successo. Beh, potevo forse rifiutare? Abbandonare una dama in pericolo è roba da capitani senza onore.";
			link.l2.go = "BetsiPrice_12_otdal_kulon";
			}
		break;
		
		case "BetsiPrice_12":
			dialog.text = "Ah, che nobile gesto, Capitano "+pchar.name+"! Anche se, sono certa che l’oste era più preoccupato per il suo bottino che per la mia pelle. Purtroppo oggi non posso invitarti – devo rimettermi in sesto. Il tempo passato in cantina non mi ha certo resa più graziosa. Ma se non ci rivediamo… giuro che non te la perdonerò. Quindi torna domani in taverna, avrò un… dono per te.";
			link.l1 = "Ebbene, ora ho un altro buon motivo per tornare qui. A presto, M... Betsy.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_ProvodimDoDoma_3");
		break;
		
		case "BetsiPrice_12_otdal_kulon":
			dialog.text = "Ah, che nobile gesto, Capitano "+pchar.name+"! Anche se, sono certa che l’oste era più preoccupato per i suoi guadagni che per la mia sorte. Purtroppo oggi non posso invitarti dentro – devo riprendermi. Il tempo passato in cantina non mi ha certo reso più bella. Ma se non ci rivedremo – non te lo perdonerò mai. Quindi passa domani in taverna, avrò un… dono per te.";
			link.l1 = "Ebbene, adesso ho un'altra buona ragione per far tappa da queste parti. Ci vediamo, M... Betsy.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_ProvodimDoDoma_3");
			TakeItemFromCharacter(pchar, "jewelry24");
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
		break;

		case "TBP_Helena_1":
			dialog.text = "Ebbene, ebbene... Che tenero addio. E chi sarebbe questa donzella tutta scompigliata? Pare abbia passato una settimana in cantina, eppure ciò non ti ha impedito di divorarla con lo sguardo, vero, "+pchar.name+"?";
			link.l1 = "Non è come pensavi. La ragazza si è trovata nei guai, e io le ho dato una mano per uscirne. Tutto qui.";
			link.l1.go = "TBP_Helena_2";
		break;

		case "TBP_Helena_2":
			dialog.text = "E tu, ovviamente, hai pensato di farti cavaliere dal cuore impavido per lei?";
			link.l1 = "Sai, non posso starmene con le mani in mano quando qualcuno è in pericolo.";
			link.l1.go = "TBP_Helena_3";
		break;

		case "TBP_Helena_3":
			dialog.text = "Va bene. Ma la prossima volta, "+pchar.name+", sii più attento... e non darmi motivo d’essere gelosa.";
			link.l1 = "Certo, tesoro. Andiamo via di qui, abbiamo ancora tanto da fare.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_ProvodimDoDoma_5");
		break;

		case "TBP_Mary_1":
			dialog.text = "Eh, eh... Che tenero addio. Quanta premura, quante promesse sussurrate... E la chiami pure per nome con tutto quell'affetto, eh? Forse dovrei sparire anch’io per qualche giorno, così magari mi cercheresti con la stessa smania?";
			link.l1 = "Mary, lo sai che sei il mio talismano, e lei... non è che una fanciulla finita nei guai.";
			link.l1.go = "TBP_Mary_2";
		break;

		case "TBP_Mary_2":
			dialog.text = "Ah, certo! Solo una povera anima che ha bisogno d’un cavaliere! E quello sguardo che le hai lanciato – era solo per cortesia, eh? Quasi la spogliavi con gli occhi, furfante!";
			link.l1 = "Mary, stai esagerando! Guarda come ti fisso, eh? Vedi la differenza? O devo rinfrescarti la memoria... da vicino?";
			link.l1.go = "TBP_Mary_3";
		break;

		case "TBP_Mary_3":
			dialog.text = "D'accordo, "+pchar.name+", te la sei cavata stavolta, va bene. Ma se mi capita di vedere ancora una scena simile...";
			link.l1 = "Allora dovrò ricordarti ancora una volta chi occupa il primo e unico posto nel mio cuore. Su, tesoro, abbiamo ancora un mare di faccende da sbrigare.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_ProvodimDoDoma_5");
		break;
		
		case "BetsiPrice_sex_1":
			dialog.text = "Mmm... Non immagini nemmeno quali pensieri mi girano per la testa quando ti ho così vicino... E quanto bramo dar loro vita.";
			link.l1 = "Allora smetti di rimuginare... e mostrameli uno per uno.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_Betsi_sex_3");
		break;

		case "BetsiPrice_sex_2":
			dialog.text = "Ah, "+GetSexPhrase("mio caro Capitano","mia cara "+pchar.name)+", sono ancora tutto preso da questa dolce follia.";
			link.l1 = "Forse questa follia merita d’esser ricordata... o magari rivissuta un giorno.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_Betsi_sex_7");
		break;
		
		
		
		
		
		
		
	}
}
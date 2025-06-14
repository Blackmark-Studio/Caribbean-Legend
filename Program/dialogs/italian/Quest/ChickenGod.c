int questShips[50];
int questShipsNum = 0;

extern void InitGunExt(string id,			
				string sAttr,       
				string sBullet,     
				string sGunPowder,  
				float  DmgMin_NC,   
				float  DmgMax_NC,   
				float  DmgMin_C,    
				float  DmgMax_C,    
				float  EnergyP_NC,  
				float  EnergyP_C,   
				bool   Stun_NC,     
				bool   Stun_C,      
				bool   MultiDamage, 
				int    MisFire,     
				bool   SelfDamage,  
				bool   Explosion,   
				float  Accuracy,    
				int    ChargeSpeed, 
				bool   isDefault );

void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp, attr, companion;
	ref chref;
	int iTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	string node = Dialog.CurrentNode;
	if(HasSubStr(node, "joruba_p3_ship_")) {
		iTemp = findsubstr(node, "joruba_p3_ship_", 0);
	 	companion = strcut(node, iTemp + strlen("joruba_p3_ship_"), strlen(node) - 1);
 	    Dialog.CurrentNode = "joruba_p3";
	}
	
	if(HasSubStr(node, "joruba_p4_off_")) {
		iTemp = findsubstr(node, "joruba_p4_off_", 0);
	 	pchar.questTemp.ChickenGod.Sacrifice = strcut(node, iTemp + strlen("joruba_p4_off_"), strlen(node) - 1);
 	    Dialog.CurrentNode = "joruba_p4_off";
	}

	if(HasSubStr(node, "joruba_o6_off_")) {
		iTemp = findsubstr(node, "joruba_o6_off_", 0);
	 	pchar.questTemp.ChickenGod.Sacrifice = strcut(node, iTemp + strlen("joruba_o6_off_"), strlen(node) - 1);
 	    Dialog.CurrentNode = "joruba_o6_off";
	}

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "First time":
			dialog.text = "Non dovresti vedere questa roba.";
			link.l1 = "È ora di segnalare un dannato problema.";
			link.l1.go = "exit";
		break;
		
        case "native":
			dialog.text = "Uh-oh! Ta'kahi, giovanotto. Non voglio essere scortese, ma come sei entrato qui? Ho caldamente consigliato alla padrona di chiudere la locanda finché resto ospite.";
			link.l1 = "Eh già, proprio così. Come ti hanno fatto entrare qui? Com’è che questa bettola non è stata ancora data alle fiamme dalla brava gente timorata di Dio?";
			link.l1.go = "native_1";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Panama");
		break;
		
        case "native_1":
			dialog.text = "I dobloni d’oro aprono tutte le strade e fanno sorridere i visi pallidi. Non te lo immaginavi, eh?";
			if (HasSubStr(pchar.model, "Sharle")) {
				dialog.text = dialog.text+"   Sento ancora l’odore stantio di Versailles su di te, dov’hanno lasciato entrare la tua carcassa con uno squittio.";
			}
			link.l1 = "Non parlarmi in quel tono, faccia da gambero. È vero che sono nuovo da queste parti, anche se non so come tu l'abbia scoperto. Potrei farti saltare le cervella qui e ora e consolarmi stanotte con qualsiasi donzella che mi vada a genio, tanto per rifarmi del fastidio.";
			link.l1.go = "native_var1";
			link.l2 = "Non so chi ti abbia messo in testa quelle fandonie, ma parli con una lingua assai sciolta, te lo concedo. È la prima volta che vedo un selvaggio così istruito.";
			if (HasSubStr(pchar.model, "Sharle")) {
				link.l2 = link.l2+" Versailles, un accidente!";
			}
			link.l2.go = "native_var2";
		break;
		
        case "native_var1":
			dialog.text = "No, Capitano, non sai nulla. Qui sono al sicuro... per ora. Però, visto che ci siamo già fatti confidenza, riproviamo. Un sorso?";
			link.l1 = "Posso farlo, mi hai davvero stuzzicato la curiosità.";
			link.l1.go = "native_play";
		break;
		
        case "native_var2":
			dialog.text = "Bravo! Vedo che siamo già passati ai nomi di battesimo e alle frecciatine. Ora propongo di bere alla pace e parlare d’affari.";
			link.l1 = "Posso farlo, mi hai davvero stuzzicato la curiosità.";
			link.l1.go = "native_play";
		break;
		
        case "native_play":
			dialog.text = "Considerando la natura di questo posto, la tua osservazione, Capitano, mi mette una certa inquietudine! Sono bloccato qui da quasi un mese ormai. Ho provato ogni dannato trucco, e ormai sono pronto a scalare le mura dalla noia e dal senso d’inutilità.";
			link.l1 = "Allora vattene. Fatti un giro in chiesa per una volta... anche se non ti faranno entrare.";
			link.l1.go = "native_play_1";
		break;
		
        case "native_play_1":
			dialog.text = "Non è così semplice, poiché sono costretto a passare altre ventiquattro ore in questo bordello, secondo il mio... contratto.";
			link.l1 = "Sembra orribile, certo, ma non aspettarti compassione da me. Affittare un bordello tutto per sé per un mese è roba da sogno!";
			link.l1.go = "native_play_2";
		break;
		
        case "native_play_2":
			dialog.text = "Temi i tuoi desideri, Capitano. Non so come tu sia arrivato qui, perché avrei dovuto passare questo mese da solo. Solo con una squaw e del vino, ma dopo tre giorni mi è rimasto solo il vino. E oggi pure quello mi ha stufato.";
			link.l1 = "E che vorresti che faccia? Che divida con te una ciurma di donzelle e fiaschi di vino?";
			link.l1.go = "native_play_3";
		break;
		
        case "native_play_3":
			dialog.text = "Forse sì, ma prima propongo una partita a carte! Mille pezzi d’argento a carta! Ah, il mio nome è Agueybana, per inciso.";
			link.l1 = "La mia è "+GetFullName(pchar)+" Certo, giochiamo.";
			link.l1.go = "native_accept";
			link.l2 = "La mia è "+GetFullName(pchar)+" Mille pesos? Niente male. Ci penserò su, ma non prometto nulla.";
			link.l2.go = "native_decline";
		break;
		
        case "native_play_again":
			dialog.text = "Hai cambiato idea, capitano? Si va?";
			link.l1 = "Certo, per tutti i diavoli, perché no.";
			link.l1.go = "native_accept";
			link.l2 = "Non ancora.";
			link.l2.go = "native_decline";
		break;
		
        case "native_decline":
			DialogExit();
			
			NextDiag.CurrentNode = "native_play_again";
		break;
		
        case "native_accept":
			DialogExit();
			
			AddDialogExitQuestFunction("ChickenGod_Game1");
		break;
		
        case "native_cards_loss":
			dialog.text = "Grazie per la partita, capitano. Pensavo mi avrebbe tirato su, ma niente. Ora lasciami in pace – vedrò di cavarmela ancora un giorno da solo, in qualche modo. Maledetto quel bastardo!";
			link.l1 = "Tutto qui? Devo ammettere che la mia delusione è più grande dell’amarezza di aver perso un sacco di dobloni.";
			link.l1.go = "native_cards_loss_1";
		break;
		
        case "native_cards_loss_1":
			dialog.text = "Non dovevi nemmeno trovarti qui, capitano. Ma se davvero brami sapere di che diavolo si trattava... cerca un antico tempio sul continente. E porta con te un bel po’ di tuunich kaane’. Tieni, prendi questo.";
			link.l1 = "Una pietra di serpente? Una pietra bucata ci sta proprio a pennello qui. Grazie, Agueybana.";
			link.l1.go = "native_cards_loss_2";
		break;
		
        case "native_cards_loss_2":
			dialog.text = "Addio, capitano.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_Game1LossGoAway");
		break;
		
        case "native_cards_win":
			dialog.text = "Ahia! Grazie, capitano! Peccato per il denaro, ma almeno ho assaporato di nuovo la vita!";
			link.l1 = "Già, è la prima volta che vedo qualcuno entusiasmarsi tanto per una rotta del genere. Da dove diamine hai tirato fuori tutti quei soldi, a proposito?";
			link.l1.go = "native_cards_win_1";
		break;
		
        case "native_cards_win_1":
			dialog.text = "Domanda scortese che non faresti mai a un tuo pari, capitano! Ma la notte è ancora giovane, e ho ancora un bel po’ di monete. Che ne dici di una rivincita?";
			link.l1 = "Perché diamine no? Facciamone un'altra!";
			link.l1.go = "native_cards_win_2";
		break;
		
        case "native_cards_win_2":
			dialog.text = "Ti propongo stavolta di giocare ai dadi e alzare un po' la posta. Ho anche una storia da raccontarti, quindi affitta una stanza al piano di sopra per noi due. Qui ci sono troppi orecchi in ascolto! Faresti cosa gradita andando dalla Madame a pagare la stanza. Purtroppo il mio credito non vale per te.";
			link.l1 = "Affittare una stanza? Per due? Qui? Va’ al diavolo, Agueybana! Io me ne vado da qui!";
			link.l1.go = "native_cards_rematch_decline";
			link.l2 = "Oh, al diavolo tutto questo. Questa storia finirà o come una buona storiella da taverna, o come un bagno di sangue molto costoso. La mia spada resta con me, quindi niente scherzi, ah-ah! Aspetta qui, ci penso io.";
			link.l2.go = "native_cards_rematch_accept";
		break;
		
        case "native_cards_rematch_decline":
			DialogExit();
			
			AddDialogExitQuestFunction("ChickenGod_Game1WinNoRematch");
		break;
		
        case "native_cards_rematch_accept":
			DialogExit();
			
			AddDialogExitQuestFunction("ChickenGod_Game1WinRematch");
		break;
		
        case "native_dice":
			dialog.text = "Allora?";
			link.l1 = "Spero davvero che tu mi abbia chiamato solo per bere e giocare d’azzardo.";
			link.l1.go = "native_dice_1";
		break;
		
        case "native_dice_1":
			dialog.text = "Non temere, capitano, non m'interessa questa ciarlataneria! Anche se, se fossi arrivato qui il primo giorno... ah ah! Iniziamo?";
			link.l1 = "La fortuna aiuta gli audaci!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_Game2");
		break;
		
        case "native_dice_win":
			dialog.text = "Uh-oh! Questo sì che è piacevole! Complimenti per la vittoria, Capitano.";
			link.l1 = "Non esagerare. Ora tocca a te spiegarmi, diavolo, che cosa sta succedendo qui?";
			link.l1.go = "native_dice_story";
			link.l2 = "Sei strano, Agueybana. Ora, se non me ne vado subito da qui, la mia reputazione di gentiluomo e d’uomo andrà a farsi friggere. Dammi il mio argento e ognuno per la sua rotta.";
			link.l2.go = "native_dice_win_not_story";
		break;
		
        case "native_dice_loss":
			dialog.text = "Che peccato, speravo di concludere la giornata in tutt’altra maniera...";
			link.l1 = "È la prima volta che vedo un uomo così sconvolto per aver vinto questo gioco da straccioni. Ora vuoi finalmente dirmi, per tutti i diavoli, che diamine sta succedendo qui?!";
			link.l1.go = "native_dice_story";
			link.l2 = "Vaffanculo, Agueybana! Ne ho fin sopra i capelli di tutto questo!";
			link.l2.go = "native_dice_loss_not_story";
		break;
		
        case "native_dice_story":
			dialog.text = "Quanto posso, capitano. Non sono sicura di poterlo fare, ma insomma, mi hai rallegrato questi ultimi giorni... In questo bordello, voglio dire.";
			link.l1 = "E di che si trattava, dunque?";
			link.l1.go = "native_dice_story_1";
		break;
		
        case "native_dice_story_1":
			dialog.text = "Non importa... Ascolta bene, uomo bianco! Io sono il grande capo della gente Taino, Agueybana. A volte sogno di essere nato cent’anni prima e di aver cacciato gli invasori spagnoli dalle mie isole! Invece ho venduto tremila dei miei alla miniera per dieci dobloni a testa.";
			link.l1 = "Una degna biografia. Mi viene un improvviso desiderio di spararti, Agueybana, e lasciarti marcire in questa lurida tana che puzza di vino andato a male.";
			link.l1.go = "native_dice_story_2";
		break;
		
        case "native_dice_story_2":
			dialog.text = "Comunque sia, capitano. Tutto ciò che ho sempre voluto era essere come voi.";
			link.l1 = "Come me?";
			link.l1.go = "native_dice_story_3";
		break;
		
        case "native_dice_story_3":
			dialog.text = "Ho visto le vostre navi – meraviglie dell’ingegno umano – e ne ho bramato una tutta per me. Ho ammirato le vostre donne nei loro corsetti stretti, sognando di strapparne uno con le mie mani. Ho visto anche i vostri peggiori comandanti esercitare un potere che i nostri capi non oserebbero neppure immaginare. Ho sentito racconti d’Europa e delle sue immani case di pietra dove la gente vive, non sopravvive. Ebbene, tutto questo l’ho avuto! Anzi, sono stato persino in Europa, e tutto questo solo nell’ultimo anno!";
			link.l1 = "Hai tracannato troppo vino, capo. L'unico biglietto per l'Europa che ti aspetta sono le catene, per la gioia del Papa e dei saltimbanchi di strada. Quello che dici è pura fantasia nel mondo in cui navighiamo.";
			link.l1.go = "native_dice_story_4";
		break;
		
        case "native_dice_story_4":
			dialog.text = "Questo è il mondo in cui viviamo, capitano. Mi hanno già spiegato che il nostro mondo è sbagliato, immaginario, e che tutto è possibile.";
			link.l1 = "E chi è stato quel furbo che te l’ha detto? A quanto pare ti fanno entrare non solo nei bordelli, ma pure nei manicomî!";
			link.l1.go = "native_dice_story_5";
		break;
		
        case "native_dice_story_5":
			dialog.text = "Ora arriviamo al nocciolo della mia storia. Sai bene come vanno le cose da queste parti, vero? Spagnoli e Inglesi si scambiano i prigionieri di guerra per fucili, attrezzi e polvere da sparo. Io ho riscattato la mia gente con i tuoi dobloni. E secondo te, perché mai?";
			link.l1 = "Ho come l’impressione che stai per illuminarmi.";
			link.l1.go = "native_dice_story_6";
		break;
		
        case "native_dice_story_6":
			dialog.text = "Solo gli dèi possono esaudire i nostri desideri più profondi e vergognosi. Se non riesci a vivere la vita che vuoi, allora chiedi loro di cambiare il tuo destino. Solo loro possono soddisfare le nostre brame più segrete. Così si fa. Ma ecco il guaio: quasi tutti i nostri dèi sono già morti, e anche da vivi non si sarebbero mai interessati all’oro. Fortuna che la natura odia il vuoto, e un nuovo dio s’è fatto avanti in una delle vecchie piramidi. A lui non importa chi tu sia: locale o europeo, canaglia o gentiluomo – paghi e ottieni ciò che chiedi! Lo sanno tutte le tribù, e persino alcuni dei tuoi. Io ho pagato il mio prezzo in oro e ho vissuto come uno di voi. Domani sarà passato un anno.";
			link.l1 = "Quale dio? In Europa e ritorno in un anno? E il momento clou del viaggio sarebbe stato una bettola da quattro soldi nei Caraibi? Bah, al diavolo tutto ciò. Sembra proprio una storia da ubriacone, e la prenderò come tale. Beviamoci su e continua il tuo racconto.";
			link.l1.go = "native_dice_story_7";
		break;
		
        case "native_dice_story_7":
			dialog.text = "Tutto ciò che ti ho raccontato è la verità. Non ho altro da aggiungere.";
			link.l1 = "Non hai ancora vissuto abbastanza nel nostro mondo, Agueybana. Ogni favola nata dall’alcool, soprattutto se raccontata ubriachi in un bordello, deve avere una morale alla fine. Dobbiamo decisamente filosofeggiare prima di chiudere come si deve il nostro salone.";
			link.l1.go = "native_dice_story_8";
		break;
		
        case "native_dice_story_8":
			dialog.text = "Come finiscono di solito queste storie?";
			link.l1 = "Non lo sai? Dipende dal sesso del partecipante, ovviamente! Con gli uomini ci si prende a pugni, con le donne si va a letto. Ma a volte la moda vuole il contrario, sai com’è. E qual è la morale della tua favola? Il denaro non porta la felicità? Che noia!";
			link.l1.go = "native_dice_story_9";
		break;
		
        case "native_dice_story_9":
			dialog.text = "Non è questa la morale della mia favola, come tu dici. Ma visto che hai tirato fuori l’argomento, sento il bisogno di dire che non concordo con te. Al contrario, credo che il denaro compri la felicità e renda la gente migliore.";
			link.l1 = "Bagianate! Adesso ti contraddici da solo, mi pare. Hai messo insieme un bel gruzzolo trafficando coi tuoi stessi fratelli. Ti ricordi quanto hai guadagnato, eh? Quasi trentamila dobloni d’oro? Fatti due conti, ma per me è chiaro che tutto quel denaro non t’ha portato felicità. Però, ti sei comprato questa bella stanza, questo sì.";
			link.l1.go = "native_dice_story_10";
		break;
		
        case "native_dice_story_10":
			dialog.text = "D’accordo, correggo il tiro: il denaro rende la vita e la gente migliori.";
			link.l1 = "Va meglio così, ma chi ti dice che renda la gente migliore? Ora saresti un modello di virtù, tu? E quelli che non hanno una moneta bucata? Li marchiamo come mascalzoni, forse?";
			link.l1.go = "native_dice_story_11";
		break;
		
        case "native_dice_story_11":
			dialog.text = "Sai, capitano, apprezzo davvero questa chiacchierata. Lascia che aggiusti il tiro: il denaro rende la vita e le persone migliori, ma solo chi già porta in sé una scintilla di virtù.";
			link.l1 = "Ascolta, ascolta! Dunque, niente fuoco per te, eh?";
			link.l1.go = "native_dice_story_12";
		break;
		
        case "native_dice_story_12":
			dialog.text = "No. Ero il capo della mia gente e, a differenza dell’oro, il potere corrompe davvero gli uomini. Sai una cosa, capitano? Ti guardo ora e capisco che un giorno anche tu dovrai affrontare questo stesso dilemma.";
			link.l1 = "Anche il tuo dio t’ha dato il dono della provvidenza? Allora dovresti salpare per Santiago, dicono che laggiù hanno un debole per ogni sorta di medium e indovino.";
			link.l1.go = "native_dice_story_13";
		break;
		
        case "native_dice_story_13":
			dialog.text = "Finiamo il nostro... ehm, salotto senza scazzottate né baldorie, ve ne prego. Non sono riuscito a trovare una morale per la mia storia, quindi vi propongo un brindisi al suo posto.";
			link.l1 = "Sei proprio spaesato, capitano. Ma su una cosa c’hai ragione. Beviamoci sopra, va’!";
			link.l1.go = "native_dice_story_14";
		break;
		
        case "native_dice_story_14":
			dialog.text = "Che i nostri desideri vadano sempre d’accordo coi nostri bisogni. Grazie, Capitano, questo è un degno finale per... la nostra serata. Se mai vorrai mettere alla prova la verità della mia storia, vai sul continente e trova là un antico tempio. Portati con te centotredici tuunich kaane’. Me ne restano novantanove – prendili, e addio!";
			link.l1 = "Un mucchio di pietre bucherellate? Si adatta bene al posto. Ti ringrazio per la serata, Agueybana. Ci rivedremo?";
			link.l1.go = "native_dice_story_15";
		break;
		
        case "native_dice_story_15":
			dialog.text = "No, non lo farai. Addio, capitano.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_BuyAmulets");
		break;
		
        case "native_dice_win_not_story":
			dialog.text = "Capisco, capitano. Nel bene o nel male, ti darò una dritta sul tesoro. Dopotutto hai reso più lieti i miei ultimi giorni... In questo bordello, voglio dire. Cerca un tempio antico sulla terraferma e porta un mucchio di tuunich kaane'. Tieni, prendi questo.";
			link.l1 = "Una pietra del serpente? Che delizia, e una pietra bucata si addice proprio a questo posto. Ne ho abbastanza del tuo comportamento!";
			link.l1.go = "native_dice_not_story";
		break;
		
        case "native_dice_loss_not_story":
			dialog.text = "Capisco che tu sia contrariato, capitano. Nel bene o nel male, ti do una dritta sul tesoro. In fondo hai rischiarato i miei ultimi giorni... In questo bordello, intendo. Cerca un antico tempio sulla grande terra e porta un mucchio di tuunich kaane'. Tieni, prendine uno.";
			link.l1 = "Una pietra del serpente? Che trovata deliziosa, e una pietra bucata calza a pennello con questo posto. Ne ho abbastanza dei tuoi modi!";
			link.l1.go = "native_dice_not_story";
		break;
		
        case "native_dice_not_story":
			dialog.text = "Addio, capitano.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_NotBuyAmulets");
		break;
		
		case "joruba":
			dialog.text = "Un altro ancora? Maledizione, ne ho fin sopra i capelli di tutti voi!";
			link.l1 = "A-a-ah! Vattene via!";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "joruba_1";
			AddDialogExitQuestFunction("ChickenGod_ShootJoruba");
		break;
		
		case "joruba_1":
			dialog.text = "Eh? Sì, giusto. Inchìnati davanti a me, mortale! Ammira il potere della mia piramide!";
			link.l1 = "(urlo disperato)";
			link.l1.go = "joruba_2";
			link.l2 = "(uccidi il mostro)";
			link.l2.go = "joruba_3";
		break;
		
		case "joruba_2":
			dialog.text = "Già così. Benvenuto nella mia umile factorìa, capitano.";
			link.l1 = "C-cosa sei, tu?";
			link.l1.go = "joruba_4";
		break;
		
		case "joruba_3":
			DialogExit();
			
			NextDiag.CurrentNode = "joruba_3_next";
			AddDialogExitQuestFunction("ChickenGod_ShootJoruba");
		break;
		
		case "joruba_3_next":
			dialog.text = "Ti lodo per la tua ostinazione. Qual è la tua prossima mossa, capitano? Che ne dici di fare un po’ di commercio?";
			link.l1 = "C-cosa sei tu?";
			link.l1.go = "joruba_4";
		break;
		
		case "joruba_4":
			dialog.text = "Non importa chi io sia, conta soltanto il ruolo che svolgo. Al momento, sto concludendo affari con gli abitanti di questa topaia per vantaggio reciproco.";
			link.l1 = "La topaia? Intendi questo tempio?";
			link.l1.go = "joruba_6";
			
			AddDialogExitQuestFunction("ChickenGod_JorubaToNormal");
		break;
		
		case "joruba_6":
			dialog.text = "La tua prima e ultima avvertenza, capitano! Comunque, questa piramide è davvero un po' stretta, ormai ci sto troppo stretto anch'io.";
			link.l1 = "Hai parlato di mercanteggiare. Che affari hai in mente, precisamente?";
			if (CheckAttribute(pchar, "questTemp.ChickenGod.SawJoruba")) {
				link.l1.go = "joruba_7A";
			} else {
				link.l1.go = "joruba_7";
			}
		break;
		
		case "joruba_7":
			dialog.text = "Do ciò di cui la gente ha più bisogno.";
			link.l1 = "Esaudisci i desideri? Come un genio delle fiabe? Santo cielo, che diavolo sta succedendo qui?!";
			link.l1.go = "joruba_7_1";
		break;
		
		case "joruba_7_1":
			dialog.text = "Non dire sciocchezze! Io aiuto soltanto la gente a ottenere ciò per cui è venuta in questo mondo, nel modo più rapido e piacevole possibile.";
			link.l1 = "Sei forse uno stregone o roba simile?";
			link.l1.go = "joruba_8";
		break;
		
		case "joruba_7A":
			dialog.text = "Ebbene, hai incontrato Agueybana, dovresti averne ricavato qualche idea.";
			link.l1 = "Quel povero indio smarrito e ubriaco era opera tua?";
			link.l1.go = "joruba_7A_1";
		break;
		
		case "joruba_7A_1":
			dialog.text = "Non sono stato io a vendere la sua tribù per qualche migliaio di libbre d’oro, non sono stato io a fargli tracannare barili di rum, e di certo non l’ho costretto a prendersi ogni malanno, noto e ignoto, da centinaia di sgualdrine. Fu lui a chiedermi di farne un nobile bianco, ed io obbedii. Così volle il suo destino.";
			link.l1 = "Esaudisci desideri? Come un genio delle fiabe? Santo cielo, che diavolo succede qui?!";
			link.l1.go = "joruba_7A_2";
		break;
		
		case "joruba_7A_2":
			dialog.text = "Non dire sciocchezze! Io aiuto solo la gente a ottenere ciò per cui sono venuti al mondo, nel modo più rapido e piacevole. Agueybana avrebbe dovuto salvare la sua gente dal giogo degli invasori europei, ma invece s'è fatto incantare dal corsetto della figlia del comandante e ha finito per impegnare il suo stesso destino.\nDa quel momento, l'unico scopo rimastogli era comprendere l'abisso del suo errore e ricominciare da capo. Un anno in Europa, la cirrosi e il tempo che voi due avete passato in un bordello avranno fatto la loro parte. Ma lo ammetto, si è fatto una gran bella vacanza, ah ah!";
			link.l1 = "Cirrho che? Sei forse uno stregone o roba simile?";
			link.l1.go = "joruba_8";
		break;
		
		case "joruba_8":
			dialog.text = "O qualcosa del genere. Ma la mia proposta ti piacerà, vedrai. E, per una volta, sarò davvero lieto di aiutarti.";
			link.l1 = "Giusto. Quanto vuoi?";
			link.l1.go = "joruba_9A";
			link.l2 = "Perché? Ho forse il marchio della provvidenza?";
			link.l2.go = "joruba_9B";
		break;
		
		case "joruba_9A":
			dialog.text = "Niente male, capitano. O siete furbo oppure siete tonto come un asino, ma la vostra sorte s'è appena fatta più favorevole. Il prezzo non sarà un problema.";
			link.l1 = "Hai bisogno di far fuori qualcuno? Non è il mio mestiere, quello.";
			link.l1.go = "joruba_10";
		break;
		
		case "joruba_9B":
			dialog.text = "Perché il tuo scopo in questa vita è riempire di buchi un buon compare mio, ah ah!";
			link.l1 = "Hai bisogno di far fuori qualcuno? Non è il mio mestiere, amico.";
			link.l1.go = "joruba_10";
		break;
		
		case "joruba_10":
			dialog.text = "Primo, sì che lo fai. Secondo, concluderemo quattro affari grossi e altri quattro minori. Ognuno ti renderà più forte e aumenterà le tue possibilità in questo mondo crudele e bizzarro. Se porterai a termine ogni patto, ti giuro che un giorno potrai sfidare gli dèi stessi ad armi pari, per non parlare della feccia mortale.";
			link.l1 = "Sembra divertente. Raccontami tutto.";
			link.l1.go = "joruba_11";
		break;
		
		case "joruba_11":
			dialog.text = "Scelta saggia! Di solito i miei discorsi fanno venir voglia alla gente di farsi portare a Blueweld con il cuore in gola, ma tu reggi bene il colpo. Ecco la lista dei compiti: lavoretti di scambio che mi aspetto tu svolga. Nessuna scadenza, eh eh.";
			link.l1 = "Curioso. Darò un'occhiata alla lista più tardi. Altro da segnalare?";
			link.l1.go = "joruba_12";
		break;
		
		case "joruba_12":
			dialog.text = "Sì, la prima grossa faccenda. Duemila dobloni è il prezzo.";
			link.l1 = "Forse ci sto... Ma è una somma da capogiro! A cosa ti serve tutta quella grana? Posso pagare in pesos?";
			link.l1.go = "joruba_13";
			link.l2 = "Sei impazzito? Con quella somma mi compro una fregata!";
			link.l2.go = "joruba_insult";
		break;
		
		case "joruba_13":
			dialog.text = "La piramide ha bisogno di riparazioni – la muratura ogni tanto cade sulla testa dei clienti, e ciò non fa bene agli affari. I miei uomini rattoppano ogni giorno, ma la nostra organizzazione necessita urgentemente di un’iniezione di denaro fresco per sistemare la faccenda una volta per tutte. Quanto ai pesos – non mi piacciono troppo, visto che il loro valore cambia come il vento.";
			link.l1 = "Sei proprio ingiusto verso i poveri pesos onesti... Un momento, non sei solo qui?";
			link.l1.go = "joruba_14";
		break;
		
		case "joruba_14":
			dialog.text = "No, sono la facciata d’una compagnia rispettabile. Allora, ci stai?";
			link.l1 = "Ci penserò, ma prima voglio sapere cosa ricevo in cambio di una somma così salata.";
			link.l1.go = "joruba_15";
		break;
		
		case "joruba_15":
			dialog.text = "Perché rovinarti la sorpresa? Considera quei soldi come una tassa, dài. Il vero tesoro sarà poter accedere agli affari futuri. Le ricompense saranno divine, te lo giuro! E uniche, bada bene: certe cose qui nei Caraibi non le troverai da nessun’altra parte!";
			link.l1 = "D'accordo. Come ti chiami, di nuovo?";
			link.l1.go = "joruba_16";
		break;
		
		case "joruba_16":
			dialog.text = "Aruba la Magnifica. Un’ultima cosa, "+pchar.name+", l'ingresso alla piramide è consentito solo una volta al giorno. Non far aspettare gli altri clienti e non scocciarmi senza motivo.";
			link.l1 = "Non vedo la folla in fila... Addio, vostra maestà.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "joruba_wait";
			AddDialogExitQuestFunction("ChickenGod_GiveFirstTask");
		break;
		
		case "joruba_wait":
			dialog.text = "Ahoy, capitano. Che novità mi porti?";
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p1") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p1.Completed") && PCharDublonsTotal() >= 2000) {
				link.p1 = "Here are your doubloons. It's hard enough to carry that damned metal around... but it is even harder to part with it!";
				link.p1.go = "joruba_p1";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p2") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p2.Completed") && GetCharacterItem(pchar, "cannabis7") >= 15) {
				link.p2 = "I kept my end of the bargain. Here's your herb, Aruba.";
				link.p2.go = "joruba_p2";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p3") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p3.Completed") && ChickenGod_FindQuestShips()) {
				for (i = 0; i < questShipsNum; i++) {
					sTemp = "p3_" + (i + 1);
				
					chref = GetCharacter(questShips[i]);
					sld = GetRealShip(sti(chref.ship.type));
					link.(sTemp) = "Aruba, ahoy! " + GetStrSmallRegister(XI_ConvertString(sld.BaseName)) + " '" + chref.Ship.Name + "' is all yours!";
					link.(sTemp).go = "joruba_p3_ship_" + questShips[i];
					if (FindCompanionShips(SHIP_PINK) && sti(pchar.questTemp.ChickenGod.Tasks.Schyot) <= 1 && startHeroType != 4)
					{
						link.(sTemp) = "Aruba, ahoy! Pink '" + chref.Ship.Name + "' is all yours!";
						link.(sTemp).go = "joruba_p3_PinkOtkaz";
					}
					/*if (FindCompanionShips(SHIP_GALEON_SM))
					{
						link.(sTemp) = "Aruba, ahoy! Galeon '" + chref.Ship.Name + "' is all yours!";
						link.(sTemp).go = "joruba_p3_HolyMercy";
					}*/
				}
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p4") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p4.Completed")) {
				link.p3 = "I'm willing to make a sacrifice.";
				link.p3.go = "joruba_p4";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o2.Lady") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o2.Completed")) {
				link.o2 = "I am bringing you a bride and troubles with the Spanish authorities, sir. The lady is taking a stroll outside, well protected by my men. I will not give her to you until you convince me of the nobility of your intentions.";
				link.o2.go = "joruba_o2";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o3") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o3.Completed") && GetCharacterFreeItem(pchar, "cirass4") >= 1) {
				link.o3 = "Here's your armor, Aruba. Make sure my reward will make up for it.";
				link.o3.go = "joruba_o3";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o4") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o4.Completed") && GetPrisonerQty() >= 30) {
				link.o4 = "I have the prisoners you asked for.";
				link.o4.go = "joruba_o4";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o5") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o5.Completed") && GetCharacterItem(pchar, "talisman11") >= 113) {
				link.p2 = "I brought you your junk. Here, a hundred and thirteen stones, just like you asked for.";
				link.p2.go = "joruba_o5";
			}
			
			bOk = (PCharDublonsTotal() >= 25000) || (ChickenGod_HaveOfficers());
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6.Completed") && bOk) {
				link.p3 = "I'm willing to make a sacrifice.";
				link.p3.go = "joruba_o6";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p4.Completed")) {
				link.respec = "(Respec character's stats)";
				link.respec.go = "joruba_respec";
			}
			
			link.exit = "I am just passing by.";
			link.exit.go = "joruba_wait_1";
			
			NextDiag.TempNode = "joruba_wait";
		break;
		
		case "joruba_wait_1":
			dialog.text = "Allora, sarà per la prossima volta.";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "joruba_p1":
			dialog.text = "Niente male, farò buon uso di quest’oro. Tieni, un piccolo amuleto che apparteneva a un capo Taino molto virtuoso. Aiuta a portare carichi d’oro. Di certo a lui ha portato fortuna, eh-eh...";
			link.l1 = "Grazie, spero di non pentirmene. Qual è il prossimo affare?";
			link.l1.go = "joruba_p1_1";
			link.l2 = "Aspetta un attimo. Ti ho dato un mucchio d’oro e in cambio ho ricevuto solo una zolla d’argilla? Voglio indietro i miei soldi!";
			link.l2.go = "joruba_insult";
			
			RemoveDublonsFromPCharTotal(2000);
			pchar.questTemp.ChickenGod.Gold = 2000;
			
			pchar.questTemp.ChickenGod.Tasks.p1.Completed = true;
			GiveItem2Character(pchar, "talisman13");
			//Log_info("You received Taino Figurine");
			PlaySound("interface\important_item.wav");
		break;
		
		case "joruba_p1_1":
			dialog.text = "Eh? Sì, il prossimo affare. Questo oro basterà per ora, dunque è tempo di pensare a merci più... spirituali. Devo cercar una cura per me stesso.";
			link.l1 = "Perché, ti senti male?";
			link.l1.go = "joruba_p1_2";
		break;
		
		case "joruba_p1_2":
			dialog.text = "La mia anima sì. Vedi, i preti tengono lontano la mia umile piramide da quell’incidente con l’Inquisizione, quindi dobbiamo arrangiarci coi metodi più antichi. Mi serve, anzi, la mia factorìa ha bisogno di quindici piante di magarosa per restare a galla.";
			if (!ChickenGod_TalkedToAmelia()) {
				link.l1 = "È forse un'erba, questa?";
			} else {
				link.l1 = "So cosa intendi, eh-eh.";
			}
			link.l1.go = "joruba_p1_3";
		break;
		
		case "joruba_p1_3":
			dialog.text = "Sarò franco: si tratta d'un'erba rara e di gran pregio. Pensaci bene se vuoi davvero passare anni a raccoglierla in tutto l'arcipelago!";
			link.l1 = "Nessuna promessa, ma ti auguro buona salute e spero che la mia ricompensa per quell’erba ne valga davvero la pena.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_GiveSecondTask");
		break;
		
		case "joruba_p2":
			dialog.text = "Benissimo, oggi lo dichiaro giorno di riposo ufficiale! Un affare simile è degno d’un vero tesoro. Guarda qua!\nQuesta machete una volta stava per spaccare la testa di quell’imbecille di Kanek! Perciò, mi è molto cara e ti chiedo umilmente di averne buona cura. È vecchia, ma forgiata a regola d’arte, non si trova più acciaio così al giorno d’oggi.";
			link.l1 = "Kanek? Chi diavolo sarebbe costui?";
			link.l1.go = "joruba_p2_1";
			
			TakeNItems(pchar, "cannabis7", -15);
			pchar.questTemp.ChickenGod.Tasks.p2.Completed = true;
			if (pchar.rank >= 21)
			{
				sld = ItemsFromID("machete2");
                sld.Attack = 80.0;
			}
			else
			{
				sld = ItemsFromID("machete2");
                sld.Attack = 60.0;
			}
			GiveItem2Character(pchar, "machete2");
			//Log_info("You received Machete Conquistador");
			PlaySound("interface\important_item.wav");
			SetAlchemyRecipeKnown("bullet_double");
			SetAlchemyRecipeKnown("grapeshot_double");
			ChickenGod_InitAmmo();
		break;
		
		case "joruba_p2_1":
			dialog.text = "Oh, voi due vi incontrerete. Ora, spero che tu non sia uno di quegli sbruffoni che schifano il lavoro duro? Se sì, sei proprio nella merda, perché la seconda parte del premio sono i progetti per le munizioni a doppia carica.";
			if (pchar.HeroParam.HeroType == "HeroType_4") {
				link.l1 = "Oh, le adoro. Ma che ci sarebbe di speciale? Una doppia carica di polvere non è certo una novità, ergo deduco che non hai messo piede fuori dalla tua piramide dai tempi di quel machete da museo.";
			} else {
				link.l1 = "Tutto qui? Ehi...";
			}
			link.l1.go = "joruba_p2_2";
		break;
		
		case "joruba_p2_2":
			dialog.text = "Non fare il furbo e ascolta! Qualunque testa di legno può ficcare due manciate di polvere da sparo in una botte e rischiare di rimaner cieco, bruciarsi la faccia o rompersi il grugno. Io invece ti propongo un trucchetto da stregone: controlla bene la qualità della polvere, macinala fino alla grana giusta, mettici una palla o del piombo, e condisci tutto con un doblone tritato. Lo scoppio farà a brandelli pure una corazza!";
			link.l1 = "Sparare per denaro, eh? Proprio da te.";
			link.l1.go = "joruba_p2_3";
		break;
		
		case "joruba_p2_3":
			dialog.text = "Sei insopportabile! Va bene, prendi un mortaio a mano e una dozzina di granate per quello, già che ci sei. Se sei così dannatamente sveglio, ti procurerai da solo gli schemi delle granate in men che non si dica!";
			link.l1 = "Grazie infinite, mio signore. Qual è il prossimo passo?";
			link.l1.go = "joruba_p2_4";
			
			//Log_info("You received Hand mortar");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "mortairgun");
			TakeNItems(pchar, "grenade", 10);
		break;
		
		case "joruba_p2_4":
			dialog.text = "Non ti piacerà, te lo dico. Mi serve una nave... anzi, mi serve quella nave. Sai, quella col passato burrascoso alle spalle.";
			link.l1 = "Perché? Non sei nemmeno un capitano.";
			link.l1.go = "joruba_p2_5";
		break;
		
		case "joruba_p2_5":
			dialog.text = "Non sono affari tuoi! Meglio che ti concentri sulla tua ricompensa, perché potrei farti lucidare questa piramide da cima a fondo, e mi dovresti ancora qualcosa!";
			link.l1 = "Di certo non sei un capitano, altrimenti sapresti che una nave ha bisogno d’un molo o d’una baia per attraccare. Dannazione, come diavolo pensi che possa far entrare una nave nella tua piramide?!";
			link.l1.go = "joruba_p2_6";
		break;
		
		case "joruba_p2_6":
			dialog.text = "Hai forse notato un lago immenso dietro la mia piramide, per caso? Proprio così. Basta che attracchi con la nave giusta della flottiglia qui vicino e i miei uomini s’occuperanno del resto. Ora levati dai piedi, che fai perder tempo alla fila.";
			link.l1 = "Ma certo. Addio!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_GiveThirdTask");
		break;
		
		case "joruba_p3":
			sld = GetCharacter(sti(companion));
			pchar.questTemp.ChickenGod.Tasks.p3.ship = sld.ship.type;
			RemoveCharacterCompanion(pchar, sld);
			AddPassenger(pchar, sld, false);
						
			npchar.ship.type = pchar.questTemp.ChickenGod.Tasks.p3.ship;
			SetCharacterShipLocation(npchar, "Temple");
						
			sld = GetRealShip(sti(pchar.questTemp.ChickenGod.Tasks.p3.ship));
					
			dialog.text = "Bene! Preso!";
			link.l1 = "Pianta la tua aria da furbo e dammi la mia ricompensa!";
			link.l1.go = "joruba_p3_1";
			switch (sti(sld.BaseType)) {
				case SHIP_MAYFANG:
					dialog.text = "E degli altri due che mi dici? Non sei riuscito a tenerteli per te, eh? Heh-heh.";
				break;
				
				case SHIP_MIRAGE:
					dialog.text = "E gli altri due? Non li potevi tenere per te, eh? Eh-eh.";
				break;
				
				case SHIP_VALCIRIA:
					dialog.text = "E gli altri due? Non te li sei tenuti per te, eh? Eh-eh.";
				break;
				
				case SHIP_FRIGATE_L:
					dialog.text = "Maledizione, sono stupito che tu non abbia voluto tenerla per te. Questa sì che è una nave con una storia! Dannazione, William... Avrei davvero voluto che tornassi a casa e fondassi una gran banca come hai sempre sognato.";
				break;
				
				case SHIP_CORVETTE_QUEST:
					sTemp = "privateer";
					if (isMainCharacterPatented()) {
						sTemp = GetStrSmallRegister(GetAddress_FormTitle(sti(Items[sti(pchar.EquipedPatentId)].Nation), sti(Items[sti(pchar.EquipedPatentId)].TitulCur)));
					}
					
					dialog.text = "Ma guarda un po’! Sei una vera vergogna per la tua patente, "+sTemp+"!";
				break;
				
				case SHIP_POLACRE_QUEST:
					dialog.text = "Charlie Prince ha deciso di sbarazzarsi delle prove compromettenti nella mia vecchia piramide? Lo approvo!";
				break;
				
				case SHIP_ECLIATON:
					dialog.text = "Buona fortuna a spiegare ai tuoi superiori la perdita della nave ammiraglia, Ammiraglio. Oh, perdonami, generale-governatore.";
				break;
				
				case SHIP_CURSED_FDM:
					dialog.text = "Sei uno stolto superstizioso o solo un povero idiota? Lei vale una fortuna! Non so se sia uno scambio equo, ma che diavolo.";
				break;
				
				case SHIP_FDM:
					dialog.text = "Sei uno sciocco superstizioso o solo un povero fesso? Lei vale una fortuna! Non so se sia uno scambio equo, ma tant’è.";
				break;
				
				case SHIP_RENOVATED_FDM:
					dialog.text = "Sei uno sciocco superstizioso o solo uno sciocco? Vale una fortuna, quella lì! Non sono poi tanto sicuro che sia uno scambio equo, ma tant’è.";
				break;
				
				case SHIP_ELCASADOR:
					dialog.text = "Ben pensato! Adoro i castigliani, lo sai. Forse gliela restituirò quando avrò finito.";
				break;
				
				case SHIP_HIMERA:
					dialog.text = "In verità, non hai cuore, Capitano. Questa nave puzza di tradimento. Me la prendo io.";
				break;
				
				case SHIP_PINK:
					if (startHeroType == 4)
					{
						dialog.text = "Ay, questa nave avrà pure una storia... ma non è stato forse troppo facile metterci le mani sopra? Bah, va bene. Il tuo caso è particolare, mio caro, quindi l'accetto. Almeno mi ricorda i vecchi tempi della mia gioventù.";
						Achievment_Set("ach_CL_127");
					}
					else 
					{
						dialog.text = "Aye, questa nave avrà pure una storia... ma non è stata forse troppo facile da prendere? Bah, al diavolo. Va bene, Capitano, te la passo stavolta, visto che hai fatto un lavoro da dio con quei lavoretti che ti avevo dato. La prendo. Mi fa tornare alla mente certi ricordi della mia gioventù, almeno.";
					}
				break;
				
				case SHIP_GALEON_SM:
					dialog.text = "E hai già visto il prete? Beh, lo incontrerai. E ti conviene far scorta di cariche doppie per la pistola. Se nemmeno quello basta - prova con un paletto di legno.";
				break;
				
				case SHIP_LADYBETH:
					dialog.text = "E hai incontrato il prete? Beh, lo incontrerai. E ti conviene fare scorta di cariche doppie per la pistola. Se non basta – prova con un paletto di legno.";
				break;
			}
		break;
		
		/*case "joruba_p3_HolyMercy":
			dialog.text = "E hai visto il prete?";
			link.l1 = "Che prete?";
			link.l1.go = "joruba_p3_HolyMercy_2";
		break;
		
		case "joruba_p3_HolyMercy_2":
			dialog.text = "Ebbene, lo incontrerai. E ti conviene far scorta di cariche doppie per la pistola. Se non basta... prova con un palo di legno.";
			link.l1 = "...";
			link.l1.go = "joruba_p3_1";
		break;*/
		
		case "joruba_p3_PinkOtkaz":
			dialog.text = "Ay, questa nave avrà pure una storia... ma non ti sembra che sia finita nelle tue mani fin troppo facilmente? Neanche per sogno! Hai ancora un mare di faccende lasciate a metà. Quando le avrai sbrigate tutte, torneremo a parlare di questo sacrificio.";
			link.l1 = "...";
			link.l1.go = "exit";
		break;
		
		case "joruba_p3_1":
			dialog.text = "Ti benedico, "+GetFullName(pchar)+". Che il mare ti sia propizio. Ora, parliamo del prossimo affare...";
			link.l1 = "Aspetta, cosa? Nemmeno il più scemo dei bifolchi si berrebbe una fandonia simile in questi tempi di buon senso! Non ti ho lasciato nemmeno uno scudo per l’elemosina, ti ho consegnato una nave da guerra in tutto e per tutto!";
			link.l1.go = "joruba_insult";
			link.l2 = "Aspetta un attimo. Che diavolo significa per me la tua benedizione?";
			link.l2.go = "joruba_p3_2";
			
			pchar.questTemp.ChickenGod.Tasks.p3.Completed = true;
		break;
		
		case "joruba_p3_2":
			dialog.text = "Ogni nave che comanderai d’ora in poi avrà lo scafo più robusto, mentre i tuoi nemici si ritroveranno col legno marcio. E in più, il tempo sul mare scorrerà più lento per te. E se questo non ti basta per piegare questo dannato buco all’inferno, allora torna da tuo padre e chiedi indietro i tuoi soldi!";
			link.l1 = "Se non funziona, giuro che stanotte torno qui e ti do fuoco alla piramide! Dimmi qual è il prossimo affare!";
			link.l1.go = "joruba_p3_3";
			notification("+10% hull defence", "None");
			notification("+10% damage to enemy ships hull", "None");
			notification("+5% speed on the Global Map", "None");
			PlaySound("Interface\new_level.wav");
		break;
		
		case "joruba_p3_3":
			dialog.text = "Ti stai prendendo gusto, eh capitano? Peccato per te, anche io. E secondo te perché ho scelto proprio questa piramide come mio ufficio?";
			link.l1 = "Forse perché la caccia alle streghe non è ancora finita?";
			link.l1.go = "joruba_p3_4";
		break;
		
		case "joruba_p3_4":
			dialog.text = "Heh-heh, no, non proprio. Faccio i miei affari qui perché i migliori accordi richiedono sangue. Questa piramide vuole sangue. Io voglio sangue. Così è sempre stato, così sempre sarà.";
			link.l1 = "Non ci provare nemmeno, mostro. Non ti porterò nessuna povera anima da scannare!";
			link.l1.go = "joruba_p3_5";
		break;
		
		case "joruba_p3_5":
			dialog.text = "E quante anime hai mandato all’altro mondo, eh? Aspetta, te lo dico io il numero preciso: ne hai ammazzati personalmente "+(Statistic_AddValue(pchar,"Saldati_s",0)+Statistic_AddValue(pchar,"Cittadini",0)+Statistic_AddValue(pchar,"Guerrieri_s",0)+Statistic_AddValue(pchar,"Solder_g",0)+Statistic_AddValue(pchar,"Citizen_g",0)+Statistic_AddValue(pchar,"Warrior_g",0))+" gente! Avete sacrificato una montagna di cadaveri sull'altare della vostra ambizione e sete d'oro! ";
			if (HasSubStr(pchar.model, "Sharle")) {
				dialog.text = dialog.text+"Il debito di tuo fratello ha già mandato al creatore più anime di quante ne stermini una guerra europea media! ";
			}
			dialog.text = dialog.text+"Non ti azzardare a farmi la predica, soprattutto perché non sono io a giudicarti. Il trionfo di qualcuno si paga sempre con la sventura d'altri, e gli dèi, ah, gli dèi, staranno a guardare e raccoglieranno il loro tributo!";
			link.l1 = "Non posso darti una risposta adesso... Devo levarmi dai piedi.";
			link.l1.go = "joruba_p3_6";
		break;
		
		case "joruba_p3_6":
			dialog.text = "Una voglia impellente di schiarirti le idee? Va bene, ma prima ascoltami. Ti donerò potere e pieno dominio del tuo corpo e della tua mente, se mi porterai un uomo di grande valore. Non un poveraccio qualunque, né una topa grigia senza volto delle strade o un ratto delle stive fetide. Portami un uomo che ti segue e gioca un ruolo importante nella tua tragicommedia.";
			link.l1 = "Uno dei miei ufficiali? Sei proprio caduto in basso, Aruba! Se questa voce si sparge...";
			link.l1.go = "joruba_p3_7";
		break;
		
		case "joruba_p3_7":
			dialog.text = "Mi occuperò della segretezza come sempre. E prima che tu ricominci a frignare, sappi che c’è un’altra via.";
			link.l1 = "Cosa vorresti dire? Che non devo portare i miei uomini all'altare con la forza?";
			link.l1.go = "joruba_p3_8";
		break;
		
		case "joruba_p3_8":
			dialog.text = "No, ma l'alternativa non ti piacerà. Se non vuoi pagare col sangue, puoi pagare con l'oro. Tremila dobloni e la coscienza pulita. I soldi fanno miracoli, li adoro!";
			link.l1 = "Addio, Aruba. Non voglio più scambiare parola con te.";
			link.l1.go = "joruba_p3_9";
		break;
		
		case "joruba_p3_9":
			dialog.text = "Sai dove trovarmi.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_GiveFourthTask");
		break;
		
		case "joruba_p4":
			dialog.text = "Facciamola in fretta, prima che l’Inquisizione spagnola ci metta le mani addosso. Sangue o oro?";
			if (PCharDublonsTotal() >= 3000)
			{
				link.l1 = "Oro sia. Ecco i tuoi tremila, anche se non riesco proprio a capire come tu possa sperperare una somma tanto grossa in questa landa selvaggia.";
				link.l1.go = "joruba_p4_1";
			}
			if (ChickenGod_HaveOfficers()) 
			{
				link.l2 = "Sangue.";
				link.l2.go = "joruba_p4_other";
			}
			link.l3 = "Lascia stare.";
			link.l3.go = "exit";
		break;
		
		case "joruba_p4_1":
			dialog.text = "...";
			link.l1 = "Hai finito? Parliamo della mia ricompensa.";
			link.l1.go = "joruba_p4_reward_1";
			RemoveDublonsFromPCharTotal(3000);
			pchar.questTemp.ChickenGod.Gold = sti(pchar.questTemp.ChickenGod.Gold) + 3000;
		break;
		
		case "joruba_p4_other":
			dialog.text = "Così sia. Pronuncia il nome.";
			
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Duran");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Baker");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Folke");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Avendel");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Tonzag");
			if (!CheckAttribute(pchar, "questTemp.PZ_LongwayNelzyaOtdatArube")) ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Longway");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Knippel");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Tichingitu");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Irons");
		break;
		
		case "joruba_p4_off":
			if (pchar.questTemp.ChickenGod.Sacrifice == "Duran" && !CheckAttribute(pchar, "questTemp.SKD_DuranDruzhba"))
			{
				dialog.text = "Claude Durand non è un ufficiale, ma un mercenario spietato, quindi scegli un'altra vittima.";
				link.l1 = "";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.ChickenGod.Sacrifice == "Duran" && CheckAttribute(pchar, "questTemp.SKD_DuranDruzhba") && CheckAttribute(pchar, "questTemp.SKD_DevushkaUbita"))
			{
				Achievment_Set("ach_CL_116");
			}
			
			dialog.text = "Accetto il tuo tributo. Non c’è bisogno che tu guardi.";
			link.l1 = "No, non ce l'ho. Tornerò per la mia ricompensa tra un'ora.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "joruba_p4_reward";
			ChangeCharacterComplexReputation(pchar, "nobility", -50);
			
			AddDialogExitQuestFunction("ChickenGod_KillOfficer");
		break;
		
		case "joruba_o6_money":
			dialog.text = "Ottima scelta. Odio dover ripulire l'altare da tutto quel sangue, quindi l'oro è senz'altro meglio. Prendi questa pozione – omaggio da un buon compare mio.";
			link.l1 = "Il sapore non è affatto male...";
			link.l1.go = "exit";
			
			PlaySound("Ambient\Tavern\glotok_001.wav");
			RemoveDublonsFromPCharTotal(25000);
			pchar.questTemp.ChickenGod.Gold = sti(pchar.questTemp.ChickenGod.Gold) + 25000;
			
			if (sti(pchar.questTemp.ChickenGod.Gold) >= 30000) {
				Achievment_Set("ach_CL_87");
			}
			
			notification("+3 P.I.R.A.T.E.S. point", "None");
			PlaySound("Interface\new_level.wav");
			pchar.skill.FreeSPECIAL = 3;
			pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices = sti(pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices) + 5;
			if (sti(pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices) >= 5) {
				pchar.questTemp.ChickenGod.Tasks.o6.Completed = true;
			}
			
			AddDialogExitQuestFunction("ChickenGod_Respec");
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_p4_reward":
			dialog.text = "";
			link.l1 = "Hai finito? Parliamo della mia ricompensa.";
			link.l1.go = "joruba_p4_reward_1";
		break;
		
		case "joruba_p4_reward_1":
			dialog.text = "Parlami ogni volta che desideri cambiare il tuo destino.";
			link.l1 = "Ma che diavolo significa per me, tutto questo?";
			link.l1.go = "joruba_p4_reward_2";
		break;
		
		case "joruba_p4_reward_2":
			dialog.text = "Dominio su te stesso! Prova, ogni tanto, ti piacerà. Nel frattempo, lascia che ti parli della prossima faccenda. La più importante.";
			link.l1 = "Non sono più sicuro che ne valga la pena!";
			link.l1.go = "joruba_p4_reward_3";
			link.l2 = "Dài, sputa il rospo.";
			link.l2.go = "joruba_p4_reward_3";
		break;
		
		case "joruba_p4_reward_3":
			dialog.text = "Hai l’opportunità non solo di cambiare il tuo destino, ma di stare fianco a fianco coi geni e gli dèi dei nostri tempi. Eh già, ora puoi mutar corpo e mente quanto vuoi, ma non salterai mai più in alto della tua testa, ché un uomo comune non potrà mai eccellere in ogni cosa. Quel che ti propongo, è di infrangere quei limiti.";
			link.l1 = "Che prezzo dovrò pagare? Ancora sangue? Oro?";
			link.l1.go = "joruba_p4_reward_4";
		break;
		
		case "joruba_p4_reward_4":
			dialog.text = "Aye. O mi porti venticinquemila dobloni o uno dei tuoi compagni. Una volta concluso, non ci saranno più affari tra di noi.";
			link.l1 = "Ci penserò su.";
			link.l1.go = "joruba_p4_reward_5";
		break;
		
		case "joruba_p4_reward_5":
			dialog.text = "Sai dove trovarmi. E non esitare a venirmi a trovare ogni volta che vorrai cambiare il tuo destino.";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "joruba_wait";
			
			pchar.questTemp.ChickenGod.Tasks.p4.Completed = true;
			AddDialogExitQuestFunction("ChickenGod_GiveFifthTask");
		break;
		
		case "joruba_respec":
			dialog.text = "Come desideri.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ChickenGod_Respec");
		break;
		
		case "joruba_o2":
			dialog.text = "Prima di tutto, è mia moglie, non una sposa novella. Secondo, il tuo guaio è coi castellani, non con me. E infine, l'ho già portata via e congedato la tua ciurma. Quanto alle intenzioni onorevoli... Guardami bene, non sono io forse un esempio di gentiluomo decoroso? Tlazolteotl, benedicilo affinché possa anch’egli un giorno conoscere una vera donna. O magari un uomo.";
			link.l1 = "Al diavolo te e Aruba!";
			link.l1.go = "exit";
			
			notification("+ 10 HP, + 10 Energy!", "None");
			PlaySound("Interface\new_level.wav");
			ChickenGod_ModifyStats(10.0);
			pchar.questTemp.ChickenGod.Tasks.o2.Completed = true;
			pchar.questTemp.ChickenGod.Tasks.Schyot = sti(pchar.questTemp.ChickenGod.Tasks.Schyot) + 1;
			
			sld = CharacterFromID(pchar.questTemp.ChickenGod.Tasks.o2.Lady);
			RemovePassenger(pchar, sld);
			ChangeCharacterAddressGroup(sld, "Temple", "goto", "goto1");
			LAi_SetCitizenTypeNoGroup(sld);
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_o3":
			dialog.text = "Niente male, grazie. Francamente, non mi serve granché, ma magari lo sfoggerò in qualche salotto o simili. In nome di Ishtar ti benedico. Ora vai e pecca.";
			link.l1 = "Che strana sensazione...";
			link.l1.go = "exit";
			
			notification("+ 15 HP, + 15 Energy!", "None");
			PlaySound("Interface\new_level.wav");
			ChickenGod_ModifyStats(15.0);
			pchar.questTemp.ChickenGod.Tasks.o3.Completed = true;
			pchar.questTemp.ChickenGod.Tasks.Schyot = sti(pchar.questTemp.ChickenGod.Tasks.Schyot) + 1;
			
			TakeItemFromCharacter(pchar, "cirass4");
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_o4":
			dialog.text = "Li prendo io. Che c'è? Anche a me servono cani morti nella ciurma, proprio come a te, ma a differenza tua non posso andare in giro per taverne a reclutare. Ora, Bast, benedica l’eroe nelle sue prossime imprese.";
			link.l1 = "Che strana sensazione...";
			link.l1.go = "exit";
			
			notification("+ 15 HP, + 15 Energy!", "None");
			PlaySound("Interface\new_level.wav");
			ChickenGod_ModifyStats(15.0);
			pchar.questTemp.ChickenGod.Tasks.o4.Completed = true;
			pchar.questTemp.ChickenGod.Tasks.Schyot = sti(pchar.questTemp.ChickenGod.Tasks.Schyot) + 1;
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
			
			AddDialogExitQuestFunction("ChickenGod_RemovePrisoners");
		break;
		
		case "joruba_o5":
			dialog.text = "Sì, dovremo spargerli di nuovo, ché la gente li perde sempre e ci servono clienti. Freya, proteggi questo gran raccoglitore di pietre.";
			link.l1 = "Che strana sensazione...";
			link.l1.go = "exit";
			
			TakeNItems(pchar, "talisman11", -113);
			
			notification("+ 15 HP, + 15 Energy!", "None");
			PlaySound("Interface\new_level.wav");
			ChickenGod_ModifyStats(15.0);
			pchar.questTemp.ChickenGod.Tasks.o5.Completed = true;
			pchar.questTemp.ChickenGod.Tasks.Schyot = sti(pchar.questTemp.ChickenGod.Tasks.Schyot) + 1;
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_o6":
			dialog.text = "Facciamola corta prima che arrivi l’Inquisizione Spagnola. Sangue o oro?";
			
			if (PCharDublonsTotal() >= 25000)
			{
				link.money = "Here's your gold, you greedy bastard.";
				link.money.go = "joruba_o6_money";
			}
			
			if (ChickenGod_HaveOfficers())
			{
				link.blood = "Blood.";
				link.blood.go = "joruba_o6_blood";
			}
			link.l3 = "Lascia stare.";
			link.l3.go = "exit";
		break;
		
		case "joruba_o6_blood":
			dialog.text = "Dimmi il nome.";
			
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Duran");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Baker");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Folke");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Avendel");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Tonzag");
			if (!CheckAttribute(pchar, "questTemp.PZ_LongwayNelzyaOtdatArube")) ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Longway");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Knippel");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Tichingitu");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Irons");
			
			if (!CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6.gf")) {
				ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Helena");
				ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Mary");
			}
		break;
		
		case "joruba_o6_off":
			if (pchar.questTemp.ChickenGod.Sacrifice == "Mary" || pchar.questTemp.ChickenGod.Sacrifice == "Helena") {
				pchar.questTemp.ChickenGod.Tasks.o6.gf = true;
				sTemp = "future wife";
				sld = CharacterFromID(pchar.questTemp.ChickenGod.Sacrifice);
				if (sld.lastname == pchar.lastname) {
					sTemp = "current wife";
				}
				
				dialog.text = "È molto allettante, ma farò un'eccezione solo questa volta – non accetterò il tuo sacrificio. Non lo rivelerò al tuo "+sTemp+", anche se probabilmente dovrei. Ricorda che senza di lei non sei nessuno. Ora sparisci e non scocciarmi oggi.";
				link.l1 = "";
				link.l1.go = "exit";
				
				AddDialogExitQuestFunction("ChickenGod_KickedFromTemple");
				break;
			}
			if (pchar.questTemp.ChickenGod.Sacrifice == "Duran" && !CheckAttribute(pchar, "questTemp.SKD_DuranDruzhba"))
			{
				dialog.text = "Claude Durand non è un ufficiale, ma un mercenario spietato, quindi scegli un'altra vittima.";
				link.l1 = "";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.ChickenGod.Sacrifice == "Duran" && CheckAttribute(pchar, "questTemp.SKD_DuranDruzhba") && CheckAttribute(pchar, "questTemp.SKD_DevushkaUbita"))
			{
				Achievment_Set("ach_CL_116");
			}
			
			dialog.text = "Sia così. Tieni, prendi questa pozione – un regalo da un buon compare mio.";
			link.l1 = "Il sapore non è affatto male...";
			link.l1.go = "joruba_o6_reward";
			
			PlaySound("Ambient\Tavern\glotok_001.wav");
			
			ChangeCharacterComplexReputation(pchar, "nobility", -50);
			notification("+3 P.I.R.A.T.E.S. points", "None");
			PlaySound("Interface\new_level.wav");
			pchar.skill.FreeSPECIAL = 3;
			pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices = sti(pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices) + 5;
			if (sti(pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices) >= 5) {
				pchar.questTemp.ChickenGod.Tasks.o6.Completed = true;
			}
			
			AddDialogExitQuestFunction("ChickenGod_KillOfficer");
			AddDialogExitQuestFunction("ChickenGod_Respec");
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_o6_reward":
			dialog.text = "Alla prossima, capitano.";
			link.l1 = "";
			link.l1.go = "exit";
			
			pchar.questTemp.ChickenGod.OnExitKick = true;
		break;
		
		case "joruba_final":
			dialog.text = "Ahoy-hoy! Finalmente, è tutto finito!";
			link.l1 = "Eh?";
			link.l1.go = "joruba_final_1";
		break;
		
		case "joruba_final_1":
			dialog.text = "Abbiamo concluso qui, Capitano. Gli accordi sono fatti, tutti sono contenti, e non si accettano ripensamenti. Il nostro ufficio chiude baracca e si sposta altrove.";
			link.l1 = "Aspetta un attimo, Aruba. Ti ho già dato abbastanza oro, sudato col sangue, portato donne e prigionieri in questo maledetto covo. Me la cavo pure con eventi soprannaturali che, a quanto pare, accadono qui nei Caraibi. Ma le nostre 'transazioni' con te sfidano ogni logica. Dammi qualche spiegazione, per l’amor del cielo.";
			link.l1.go = "joruba_final_2";
		break;
		
		case "joruba_final_2":
			dialog.text = "You know what? I'll tell you.\nI'm fed up with this world, and I want out. Every day, it's the same old routine: an ancient pyramid with a crumbling ceiling, those loathsome identical palm trees, and a never-ending stream of captains, each with their own ingenious ideas. Yes, I provide people with what they desire; it's my calling, and I take pride in it. But by the gods, how I detest all of you!";
			link.l1 = "Qualcuno ti tiene qui prigioniero? L’uscita è proprio lì, cervellone!";
			link.l1.go = "joruba_final_3";
		break;
		
		case "joruba_final_3":
			dialog.text = "Hai proprio ragione, nessuno mi tiene più qui. Non ormai. E tutto questo grazie a te, mio compare.";
			link.l1 = "Che improvviso cambiamento d’animo. Mi aspettavo una storia, ma finora non ho sentito altro che le farneticazioni senza senso di un miserabile dioletto in una piramide impolverata.";
			link.l1.go = "joruba_final_4";
		break;
		
		case "joruba_final_4":
			dialog.text = "Ebbene, ognuno deve sfogarsi di tanto in tanto, non è vero? Sono davvero lieto che tu sia venuto qui, perché grazie a te posso finalmente lasciare questo mondo. Oro, ciurma, attrezzatura e una nave, amico mio. Ricordi? Ti suona familiare? Era tutto ciò che mi serviva, e tu me l'hai dato tutto.";
			link.l1 = "Di nulla, compare. Ma ciò non spiega il tuo strano modo di ciarlare, né quei poteri che paiono d'un dio. Se sei così dannatamente potente, perché non ti sei già creato una nave, un equipaggio e una cassa d'oro dal nulla?";
			link.l1.go = "joruba_final_5";
		break;
		
		case "joruba_final_5":
			dialog.text = "Così feci, come puoi vedere. Ognuno ha i suoi mezzi.";
			link.l1 = "Ma per mille balene! Chi sei tu, di grazia?";
			link.l1.go = "joruba_final_6";
		break;
		
		case "joruba_final_6":
			dialog.text = "Ebbene... è questo che faccio, semplicemente. Ci si vede nel nuovo mondo, "+GetPersonaName()+". Spero che la prossima volta sia qualcosa di davvero nuovo. Grazie e addio.";
			link.l1 = "No, non voglio mai più vederti.";
			link.l1.go = "exit";
			link.l2 = "Allora ci si rivede, Aruba... è stata una faccenda interessante.";
			link.l2.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_FinalGood");
		break;
		
		case "joruba_insult":
			dialog.text = "Sembra che tutti gli accordi siano andati in fumo. È ora di levar l'àncora, capitano.";
			link.l1 = "Tempo che tu vada a f...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_Insult");
		break;
		
		case "ChickenGod_TheInquisition_1":
			dialog.text = "In nome della Santa Inquisizione spagnola, dichiara chi sei!";
			link.l1 = "Capitano "+GetFullName(pchar)+"... E dicon proprio il vero, nessuno si aspetta mai l’Inquisizione Spagnola...";
			link.l1.go = "ChickenGod_TheInquisition_2";
		break;
		
		case "ChickenGod_TheInquisition_2":
			dialog.text = "... Questa burla colpisce sempre nel segno, anche se ha portato più d’un povero cristiano dritto al rogo.";
			link.l1 = "...";
			link.l1.go = "ChickenGod_TheInquisition_3";
		break;
		
		case "ChickenGod_TheInquisition_3":
			dialog.text = "Scherzavo, Capitano. Tu facevi il buffone, io pure. Mi chiamo Padre Emilio Bocanegra, e questi soldati di Cristo sono le mie guardie armate.";
			link.l1 = "Che posso fare per voi, padre?";
			link.l1.go = "ChickenGod_TheInquisition_4";
		break;
		
		case "ChickenGod_TheInquisition_4":
			dialog.text = "Conosci forse un certo señor Aruba?";
			link.l1 = "Sì, abitava in questa vecchia piramide fino a poco tempo fa.";
			link.l1.go = "ChickenGod_TheInquisition_5";
		break;
		
		case "ChickenGod_TheInquisition_5":
			dialog.text = "Cosa vuoi dire che viveva lì? Si può davvero vivere in quel posto? E perché 'fino a poco tempo fa'?";
			link.l1 = "Questo señor ci ha appena lasciati su una nave pochi minuti fa.";
			link.l1.go = "ChickenGod_TheInquisition_6";
		break;
		
		case "ChickenGod_TheInquisition_6":
			dialog.text = "Come lo sai? La baia più vicina dista giorni di navigazione!";
			link.l1 = "Questo lago dev’essere più vasto di quanto sembri. Non so darti altra spiegazione, padre.";
			link.l1.go = "ChickenGod_TheInquisition_7";
		break;
		
		case "ChickenGod_TheInquisition_7":
			dialog.text = "Cose strane stanno accadendo nelle terre del Vicereame.";
			link.l1 = "Queste sono terre inglesi, padre.";
			link.l1.go = "ChickenGod_TheInquisition_8";
		break;
		
		case "ChickenGod_TheInquisition_8":
			dialog.text = "Lascia che gli eretici continuino a pensarla così. Stai certo che riavremo ciò che ci appartiene. Perdonami, figliolo, se ti tempesto di domande: Santiago mi ha ordinato di condurre un'indagine ufficiale su questa piramide... e sul suo precedente occupante.";
			link.l1 = "Che diavolo è successo, padre?";
			link.l1.go = "ChickenGod_TheInquisition_9";
		break;
		
		case "ChickenGod_TheInquisition_9":
			dialog.text = "Visto che il caso sarà probabilmente archiviato, posso intrattenerti con una storiella.\nLe voci su questo luogo circolano per tutto il Main già da un po’ di tempo. Avevamo ricevuto notizie affidabili che diversi individui che hanno lasciato un segno nella storia della regione si recavano spesso qui in passato.\nTuttavia, Santiago ha cominciato a prendere sul serio queste chiacchiere solo dopo l’incidente di Panama.\nUn certo indio aveva fatto un gran scalpore in quella città gloriosa, persino tenendo qualche sermone dal tono piuttosto filosofico. Sfortunatamente, gli abitanti di Panama hanno tratto conclusioni assai superficiali e si sono convinti che questa piramide contenga ricchezze inimmaginabili e realizzi ogni desiderio.\nEresia della più pura specie, ovviamente... così abbiamo dovuto avviare un procedimento contro alcuni residenti panamensi e contro quell’indio, Aguebana.";
			link.l1 = "Perché le autorità di Panama non hanno messo fine a questa faccenda?";
			link.l1.go = "ChickenGod_TheInquisition_10";
		break;
		
		case "ChickenGod_TheInquisition_10":
			dialog.text = "Come sempre accade in questi casi, hanno giurato d’essere stati stregati. Questo cavillo legale si sarebbe potuto chiudere se avessimo interrogato Aguebana, ma quello è morto all’improvviso.";
			link.l1 = "Come ha tirato le cuoia?";
			link.l1.go = "ChickenGod_TheInquisition_11";
		break;
		
		case "ChickenGod_TheInquisition_11":
			dialog.text = "L'ebbrezza l'ha portato alla tomba. Tuttavia, la sua morte non ha risolto i nostri guai, ché l'eresia aveva già messo radici in tutto l’arcipelago, e centinaia d’anime s’erano messe in pellegrinaggio verso quell’antico tempio.";
			link.l1 = "Non ho mai visto tanta gente qui prima d’ora... Allora, volevi invadere Aruba e processarlo davanti a tutti?";
			link.l1.go = "ChickenGod_TheInquisition_12";
		break;
		
		case "ChickenGod_TheInquisition_12":
			dialog.text = "Ma certo che no, figliolo. Il giudizio dell’Inquisizione è severo ma giusto. Deve esserci un valido motivo per un processo. No, intendevo solo raccogliere la testimonianza del signor Aruba e portarla a Santiago.";
			link.l1 = "Eh, che sfortuna per te.";
			link.l1.go = "ChickenGod_TheInquisition_13";
		break;
		
		case "ChickenGod_TheInquisition_13":
			dialog.text = "Non si può mai sapere, figliolo. È la volontà di Dio.";
			link.l1 = "Addio, padre.";
			link.l1.go = "ChickenGod_TheInquisition_14";
		break;
		
		case "ChickenGod_TheInquisition_14":
			DialogExit();
			
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Temple", "reload2", false);
			LAi_SetActorType(npchar);
			//LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "ChickenGod_TheInquisitionLeave", -1);
			PChar.quest.ChickenGod_TheInquisitionLeave.win_condition.l1 = "ExitFromLocation";
			PChar.quest.ChickenGod_TheInquisitionLeave.win_condition.l1.location = PChar.location;
			PChar.quest.ChickenGod_TheInquisitionLeave.win_condition = "ChickenGod_TheInquisitionLeave";
		break;
		
	}
} 

void ChickenGod_InitAmmo() {
	if(LoadSegment("items\initItems.c")) {
		InitGunExt(		 "pistol1", "t3", 	 "bullet_double",               "", 100.0, 300.0,  60.0, 260.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 40, 20, 0);
		InitGunExt( 	 "pistol2", "t2", "grapeshot_double",               "",  60.0, 160.0,  20.0, 100.0,  0.0,  0.0, 0, 1, 1, 0, 1, 1, 40, 20, 0);
		InitGunExt(		 "pistol3", "t2", "grapeshot_double",               "",  80.0, 180.0,  30.0, 110.0,  0.0,  0.0, 0, 1, 1, 2, 1, 1, 40, 20, 0);
		InitGunExt(		 "pistol4", "t3",    "bullet_double",               "",  70.0, 270.0,  30.0, 230.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 35, 30, 0);
		InitGunExt(		 "pistol5", "t3", 	 "bullet_double",               "", 130.0, 330.0,  90.0, 290.0,  0.0,  0.0, 1, 0, 0, 2, 0, 0, 70, 30, 0);
		InitGunExt(		 "pistol6", "t3",    "bullet_double",               "", 100.0, 300.0,  60.0, 260.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 50, 20, 0);
		InitGunExt(		 "pistol8", "t4", "grapeshot_double",               "",  50.0, 100.0,  30.0,  60.0,  5.0,  5.0, 1, 1, 1, 0, 1, 1, 20, 20, 0);
		InitGunExt(		 "pistol9", "t3", 	 "bullet_double",               "", 100.0, 320.0,  80.0, 280.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 40, 30, 0);
		InitGunExt(		 "pistol10", "t3",   "bullet_double",               "", 140.0, 280.0, 100.0, 240.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 45, 30, 0);
		InitGunExt(		 "pistol11", "t3",   "bullet_double",               "",  10.0, 700.0,  10.0, 620.0, 40.0, 30.0, 1, 1, 0, 0, 0, 0, 45,100, 0);
		InitGunExt(		 "pistol12", "t3",   "bullet_double",               "",  80.0, 290.0,  60.0, 240.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 45, 20, 0);
		InitGunExt(		 "pistol13", "t3",   "bullet_double",               "", 130.0, 300.0,  90.0, 260.0, 15.0,  0.0, 1, 1, 0, 0, 0, 0, 60, 30, 0);
		InitGunExt(		 "howdah",  "t3", "grapeshot_double",	            "",  50.0, 140.0,  30.0,  70.0,  5.0,  5.0, 1, 1, 1, 0, 0, 1, 50, 30, 0);
		InitGunExt(		 "pistol14", "t3",   "bullet_double",               "", 130.0, 330.0,  90.0, 290.0,  0.0,  0.0, 1, 0, 0, 4, 0, 0, 70, 34, 0); // Дуэльный двухзарядный пистоль cle 1.3
		
		UnloadSegment("items\initItems.c");
	}
	
	CGInitGrapeGunExt(	"pistol2",	"t2",		3,		50,		4.25,	5.0,	3);		// трёхствольный дробовик, двойной заряд
	CGInitGrapeGunExt(	"pistol3",	"t2",		4,		40,		6.0,	5.0,	4);		// тромбон, двойной заряд
	CGInitGrapeGunExt(	"pistol8",	"t4",		4,		110,	5.0,	3.0,	2);		// бландербуз, двойной заряд
	CGInitGrapeGunExt(	"howdah",	"t3",		3,		85,		3.0,	5.5,	2);		// гауда, двойной заряд
	CGInitGrapeGunExt(	"mushket3",	"t2",		3,		60,		6.0,	3.0,	3);		// аркебуза, картечь
	CGInitGrapeGunExt(	"mushket6",	"t3",		3,		90,		4.0,	3.5,	2);		// башенный мушкетон, картечь
}

void CGInitGrapeGunExt(string id, string sAttr, int basedmg, int shards, float width, float height, int dispersion)
{
	ref gun = ItemsFromID(id);
	gun.type.(sAttr).basedmg = basedmg;
	gun.type.(sAttr).shards = shards;
	string sArea = "grapes_area_"+dispersion;
	gun.type.(sAttr).area = XI_ConvertString(sArea);
	gun.type.(sAttr).width = width;
	gun.type.(sAttr).height = height;
}

bool ChickenGod_FindQuestShips() {
	questShipsNum = 0;
	
	for(int i = 1; i < COMPANION_MAX; i++) {
		int index = GetCompanionIndex(pchar, i);
		if (index < 0) {
			continue;
		}
		
		sld = GetCharacter(index);
		int shipIndex = sti(sld.ship.type);
		if (shipIndex == SHIP_NOTUSED) {
			continue;
		}
		
		ref realShip = GetRealShip(shipIndex);
		if (!CheckAttribute(realShip, "QuestShip")) {
			continue;
		}
		
		if (!GetRemovable(sld) || !GetShipRemovable(sld)) {
			continue;
		}
		
		if (CheckAttribute(pchar, "questTemp.HWIC.TakeQuestShip")) {
			if (sti(realShip.BaseType) == SHIP_MAYFANG || sti(realShip.BaseType) == SHIP_MIRAGE || sti(realShip.BaseType) == SHIP_VALCIRIA) {
				continue;
			}
		}
		
		questShips[questShipsNum] = sti(sld.index);
		questShipsNum++;
	}
	
	return (questShipsNum > 0);
}

void ChickenGod_AddOfficerLink(aref link, string prefix, string id) {
	if (GetCharacterIndex(id) < 0) {
		return;
	}
	
	if (!CheckPassengerInCharacter(pchar, id)) {
		return;
	}
	
	if (id == "Mary" && !CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) {
		return;
	}
	
	if (id == "Helena" && !CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) {
		return;
	}
	
	sld = CharacterFromID(id);
	
	if (!GetRemovable(sld)) {
		return;
	}
	
	link.(id) = GetFullName(sld) + ".";
	link.(id).go = prefix + id;
}

bool ChickenGod_TalkedToAmelia() {
	if (GetCharacterIndex("Amelia") < 0) {
		return false;
	}
	
	sld = CharacterFromID("Amelia");
	if (sld.dialog.currentnode == "amelia") {
		return false;
	}
	
	return true;
}

bool ChickenGod_HaveOfficers() {
	object fakelink;
	
	ChickenGod_AddOfficerLink(&fakelink, "", "Duran");
	ChickenGod_AddOfficerLink(&fakelink, "", "Baker");
	ChickenGod_AddOfficerLink(&fakelink, "", "Folke");
	ChickenGod_AddOfficerLink(&fakelink, "", "Avendel");
	ChickenGod_AddOfficerLink(&fakelink, "", "Tonzag");
	if (!CheckAttribute(pchar, "questTemp.PZ_LongwayNelzyaOtdatArube")) ChickenGod_AddOfficerLink(&fakelink, "", "Longway");
	ChickenGod_AddOfficerLink(&fakelink, "", "Knippel");
	ChickenGod_AddOfficerLink(&fakelink, "", "Tichingitu");
	ChickenGod_AddOfficerLink(&fakelink, "", "Irons");
	
	if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6.gf")) {
		ChickenGod_AddOfficerLink(&fakelink, "", "Helena");
		ChickenGod_AddOfficerLink(&fakelink, "", "Mary");
	}
	
	return (GetAttributesNum(&fakelink) > 0);
}

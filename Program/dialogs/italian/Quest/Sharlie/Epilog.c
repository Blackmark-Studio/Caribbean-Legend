void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk;
	int i, n, iTemp, addGold, NextMonth;
	string attrL, sStr, Month;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	attrL = Dialog.CurrentNode;
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Volevate qualcosa?";
			link.l1 = "No, niente.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// диалоги в ПУ
		case "SharlieEpilog_Pikar_1":
			dialog.text = "Che sorpresa! Proprio tu "+GetTitle(NPChar,true)+" "+pchar.lastname+" in persona!";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarAlive"))
			{
				link.l1 = ""+npchar.name+"! Non pensavo proprio di vederti qui... Anzi, non credevo nemmeno che fossi ancora vivo!";
				link.l1.go = "SharlieEpilog_Pikar_2";
			}
			else
			{
				link.l1 = "Non ci posso credere... Bello? Ma... come?";
				link.l1.go = "SharlieEpilog_PikarResurrected_1";
			}
			PlaySound("Voice\" + LanguageGetLanguage() + "\LE\Rocur\Rocur_03.wav");
		break;
		
		case "SharlieEpilog_Pikar_2":
			if (IsStateTitle())
			  {
				dialog.text = "Ah ah! Beh, hai fatto male a dubitare. Come vedi, sono più vivo che mai. Ecco, ho deciso di comprarmi una nave tutta ‘pulita’. E tu... racconta: come sei arrivato a такой vita, eh, amico?";
			  }
			  else 
			  {
				dialog.text = "Ah ah! Beh, ti sbagli di grosso. Come vedi, sono più vivo che mai. Ecco, ho deciso di comprarmi una nave tutta 'pulita'. E tu... racconta: cosa ti porta da queste parti, eh, amico?";
			  }
			link.l1 = "Non qui. Andiamo in taverna, gli affari possono aspettare.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_WithPikarToTavern");
		break;
		
		case "SharlieEpilog_PikarResurrected_1":
			dialog.text = "Shh... Non gridare così. Il bellimbusto è ormai passato, come credo anche il Principe. Non è vero?";
			link.l1 = "Ma l'ho visto con i miei occhi...";
			link.l1.go = "SharlieEpilog_PikarResurrected_2";
		break;

		case "SharlieEpilog_PikarResurrected_2":
			dialog.text = "Come mi hanno fatto fuori? Magari fosse così, amico. Puoi crederci.";
			link.l1 = "Andiamo in taverna. Mi racconterai tutto.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_WithPikarToTavern");
		break;
		
		case "SharlieEpilog_Captain_1":
			dialog.text = "...";
			link.l1 = "Quindi, siete il nuovo proprietario del pinasco '"+GetShipName("Ulysse")+"'?";
			link.l1.go = "SharlieEpilog_Captain_2";
			PlaySound("Voice\" + LanguageGetLanguage() + "\z_arest_02.wav");
		break;
		
		case "SharlieEpilog_Captain_2":
			dialog.text = "Io. "+GetFullName(npchar)+", visto che siete così curioso. E voi chi siete?";
			link.l1 = ""+UpperFirst(GetTitle(NPChar,false))+" "+pchar.lastname+", e vorrei riscattare questa nave da voi.";
			link.l1.go = "SharlieEpilog_Captain_3";
		break;
		
		case "SharlieEpilog_Captain_3":
			dialog.text = "Ma certo, ma certo, ne ho sentito parlare. E pensare che credevo di essermi già liberato di tutti quelli che volevano mettere le mani su questa barca. Dovrò deludervi, "+GetTitle(NPChar,true)+" - '"+GetShipName("Ulysse")+"' ora è mio, e molto presto partirò con lui per Bordeaux. Non sono entrato nel commercio per rovinare subito il mio primo affare. Porta sfortuna, sapete.";
			link.l1 = "Bordeaux, dite? Interessante... Forse ho una proposta vantaggiosa per voi. Che ne dite di discuterne davanti a una tazza di rum?";
			link.l1.go = "SharlieEpilog_Captain_4";
		break;
		
		case "SharlieEpilog_Captain_4":
			dialog.text = "Non è nel mio stile rifiutare né il rum, né le offerte vantaggiose. Andiamo.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_WithPikarToTavern");
		break;
		
		// диалоги в таверне
		case "SharlieEpilog_Pikar_5":
			if (IsStateTitle())
			  {
				dialog.text = "E allora, a te, "+GetTitle(npchar,false)+" "+pchar.lastname+". Lo sapevo che uno come te non sarebbe rimasto a lungo a fare il galoppino per Tirax.   Ma che saresti diventato una persona così importante... sai davvero sorprendere, dannazione.";
				link.l1 = "Ahah. Sentilo chi parla. Quindi hai deciso di diventare un mercante?";
			  }
			  else 
			  {
				dialog.text = "Un brindisi all’incontro! Sentivo con la nuca che ci saremmo rivisti.";
				link.l1 = "Ah-ah. A lei! Allora, hai deciso di darti al commercio?";
			  }
			
			link.l1.go = "SharlieEpilog_Pikar_6";
		break;

		case "SharlieEpilog_Pikar_6":
			dialog.text = "Non si può mica rischiare la testa per un paio di dobloni tutta la vita. Ho unto chi serviva, tappato la bocca a chi non serviva – ed ecco: non sono più un ladro e pirata, ma un rispettabile negoziante.";
			link.l1 = "Questa sì che è una sorpresa. Ora nemmeno so come offrirti то, che volevo proporre al nuovo capitano di pinassa '"+GetShipName("Ulysse")+"'.";
			link.l1.go = "SharlieEpilog_Pikar_7";
		break;

		case "SharlieEpilog_Pikar_7":
			dialog.text = "Ma dai, racconta tutto com’è. Ci conosciamo da una vita.";
			link.l1 = "Vedi... sono arrivato qui, ai Caraibi, proprio sulla pinassa che hai riscattato tu. Quando ho saputo che l’avevano messa all’asta, volevo contrattare per riaverla – e tornare a casa, in Francia, su quella nave.";
			link.l1.go = "SharlieEpilog_Pikar_8";
		break;

		case "SharlieEpilog_Pikar_8":
			dialog.text = "Ah-ah-ah-ah! Aspetta... ah-ah-ah-ah-ah!..";
			link.l1 = "E allora, che c'è da ridere?";
			link.l1.go = "SharlieEpilog_Pikar_9";
		break;

		case "SharlieEpilog_Pikar_9":
			dialog.text = "E appena ho vinto l’asta, subito si è avvicinato a me un damerino – giovane, ben curato: “Portami, caro mio, insieme ai miei averi a Bordeaux, ti pagherò con moneta sonante.” E che moneta – un intero dannato sacco di monete.";
			link.l1 = "Davvero? Ah-ah. Davvero divertente. E allora? Hai accettato?";
			link.l1.go = "SharlieEpilog_Pikar_10";
		break;

		case "SharlieEpilog_Pikar_10":
			dialog.text = ""+pchar.name+", beh, non sono mica uno sciocco da rinunciare a una montagna d’oro per una semplice traversata dell’Atlantico. Certo, dovrò sgranocchiare biscotti secchi e masticare carne salata per un paio di mesi. Ma sai, mi è già capitato di rischiare la pelle per molto meno. Quindi, ovviamente, ci sto.";
			link.l1 = "In tal caso, sono pronto a offrirti lo stesso. Portami a Bordeaux e riceverai la stessa montagna di monete.";
			link.l1.go = "SharlieEpilog_Pikar_11";
		break;

		case "SharlieEpilog_Pikar_11":
			dialog.text = "Sei pronto a diventare un passeggero? Sai bene quali sono le nostre regole: a bordo c’è un solo capitano. E sulla mia nave, quel capitano sono io.";
			link.l1 = "Perché no? Mi prenderò una pausa, rifletterò sulla vita. Forse dovrei davvero fermarmi, mettere radici. Ora mi sembra quasi impossibile, ma forse c’è del senso. Perfino tu hai deciso di stare lontano dalle battaglie.";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l1.go = "SharlieEpilog_Pikar_12_wife";
			}
			else
			{
				link.l1.go = "SharlieEpilog_Pikar_12";
			}
		break;
		
		case "SharlieEpilog_Pikar_12_wife":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarAlive"))
			{
				dialog.text = "Ah, se avessi anch’io una moglie bella come la tua, forse avrei lasciato il mare, mi sarei sistemato in qualche angolo sperduto: avrei costruito una casa e magari commerciato un po’ di vino. Per fortuna, non mi manca di che vivere – da quando mi hai tirato fuori dalle grinfie degli spagnoli, non ho perso tempo.";
			}
			else
			{
				dialog.text = "Ah, se avessi anch’io una moglie bella come la tua, forse avrei lasciato il mare, mi sarei sistemato in qualche angolo sperduto: avrei costruito una casa e magari avrei venduto un po’ di vino. D’altronde, con l’eredità che la vedova del piantatore si è ritrovata, si può vivere senza pensieri.";
			}
			link.l1 = "Moglie! Diavolo, "+npchar.name+", non ne ho ancora parlato con lei.";
			link.l1.go = "SharlieEpilog_Pikar_13_wife";
		break;
		
		case "SharlieEpilog_Pikar_13_wife":
			dialog.text = "Hai ancora tutto il tempo del mondo per questo. Io devo sistemare come si deve la mia carretta. Quando finirai con i tuoi affari, trascina il tuo culo qui. Facciamo una bella festa prima della partenza.";
			link.l1 = "Così mi piace! Non preoccuparti, non dovrai aspettare a lungo.";
			link.l1.go = "SharlieEpilog_Pikar_14_wife";
		break;
		
		case "SharlieEpilog_Pikar_14_wife":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarAlive")) {AddQuestRecord("SharlieEpilog", "11_1");}
			else {AddQuestRecord("SharlieEpilog", "11_5");}
			AddDialogExitQuestFunction("SharlieEpilog_OutTavern");
		break;
		
		case "SharlieEpilog_Pikar_12":
			dialog.text = "Ah, se avessi una moglie, forse anch’io lascerei il mare e mi sistemerei in qualche angolo sperduto: costruirei una casa e venderei un po’ di vino. Ma per ora... il mare è la mia casa.";
			link.l1 = "Con il vino delle mie piantagioni, ah-ah! A Bordeaux, "+npchar.name+", certe ragazze sono proprio uno spettacolo! Magari anche tu там potresti trovare qualcuna — in amore se la cavano niente male. Sai che ti dico? Nei prossimi mesi, tutto quello che vedremo saranno le facce dei tuoi marinai. Prima di salpare, dovremmo proprio organizzare una bella festa in un bordello locale.";
			link.l1.go = "SharlieEpilog_Pikar_13";
		break;
		
		case "SharlieEpilog_Pikar_13":
			dialog.text = "E voi, monsieur, sapete cosa offrire. Quando avrete sistemato tutte le vostre faccende, portate qui il vostro sedere. E poi magari finiremo anche in un bordello, statene certo.";
			link.l1 = "E allora, non perderò altro tempo. Al lavoro!";
			link.l1.go = "SharlieEpilog_Pikar_14";
		break;
		
		case "SharlieEpilog_Pikar_14":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarAlive")) {AddQuestRecord("SharlieEpilog", "11_2");}
			else {AddQuestRecord("SharlieEpilog", "11_6");}
			AddDialogExitQuestFunction("SharlieEpilog_OutTavern");
		break;
		
		case "SharlieEpilog_PikarResurrected_3":
			dialog.text = "Per la libertà!";
			link.l1 = "E anche per te, Jean! Per la tua resurrezione! Ancora non ci credo. Come?";
			link.l1.go = "SharlieEpilog_PikarResurrected_4";
		break;

		case "SharlieEpilog_PikarResurrected_4":
			dialog.text = "Mi hanno trascinato fuori dal campo di battaglia – mezzo morto, coperto di sangue dalla testa ai piedi. Mi hanno buttato in una baracca e lasciato lì a crepare come una bestia. Tra gli schiavi c’era un tipo in gamba – Moko. È stato lui a salvarmi la pelle: mi ha stretto la ferita con un pezzo della mia camicia, mi ha dato da bere.";
			link.l1 = "Vuoi dire che gli spagnoli ti hanno lasciato in vita dopo tutto questo?";
			link.l1.go = "SharlieEpilog_PikarResurrected_5";
		break;

		case "SharlieEpilog_PikarResurrected_5":
			dialog.text = "Come vedi. Solo che non è stata bontà d’animo. Volevano vendetta: interrogatori crudeli, torture. Mi hanno bruciato, picchiato, tagliato. Minacciavano di cavarmi gli occhi – tutto per il grande amore che provavano per me. Ma poi qualcuno ha sparso la voce che i pirati stavano preparando una vendetta per me e già affilavano i coltelli. Al padrone della piantagione è venuto un tic all’occhio. Non ha aspettato la visita dei nostri fratelli e si è precipitato nelle sue proprietà a Campeche. Ha portato con sé me, Moko e gli altri, per non lasciare testimoni. Agli altri hanno detto che ero morto – e su questo hanno messo una croce.";
			link.l1 = "E quindi? Come hai fatto a uscire di prigione? E come diamine sei finito qui?";
			link.l1.go = "SharlieEpilog_PikarResurrected_6";
		break;

		case "SharlieEpilog_PikarResurrected_6":
			dialog.text = "La fortuna, amico mio. Fortuna cieca e sporca. Mi portarono in una piantagione, e le torture continuarono. Quel bastardo decise che avrebbe assaporato ogni secondo della mia sofferenza, ma giorno dopo giorno si indeboliva... finché non crepò di febbre. Dopo di che, a nessuno importava più di me. Mi buttarono nei campi come una bestia, senza dimenticare di frustarmi generosamente.";
			link.l1 = "Non capisco ancora come tu sia riuscito a scappare da lì?";
			link.l1.go = "SharlieEpilog_PikarResurrected_7";
		break;

		case "SharlieEpilog_PikarResurrected_7":
			dialog.text = "Hai sentito parlare di Christopher Myngs?";
			link.l1 = "Alonso ha menzionato qualcosa... Il raid a Campeche! Hanno davvero messo in fuga gli spagnoli quella volta. Quindi sono stati loro a liberarti?";
			link.l1.go = "SharlieEpilog_PikarResurrected_8";
		break;

		case "SharlieEpilog_PikarResurrected_8":
			dialog.text = "Non proprio. Ci siamo liberati da soli. Mentre le guardie respingevano il gruppo degli anglo-buccanieri, io e Moko abbiamo trovato una via d’uscita dal tetto della baracca e abbiamo scatenato una rivolta. Abbiamo preso l’arsenale e il tesoro della moglie del defunto bastardo piantatore.";
			link.l1 = "Il tesoro?! Questa sì che è una sorpresa.";
			link.l1.go = "SharlieEpilog_PikarResurrected_9";
		break;

		case "SharlieEpilog_PikarResurrected_9":
			dialog.text = "Non ci siamo persi in troppe riflessioni: abbiamo preso le armi e le nostre cose e ci siamo inoltrati nella selva. Per due giorni ci siamo fatti strada nella giungla, finché non ci siamo imbattuti in un villaggio degli indigeni Can Pech. Il loro sciamano obbediva agli spagnoli solo per facciata, ma di certo non li amava. Moko riuscì subito a trovare un linguaggio comune con lui: ci accolsero in cambio di metà del nostro arsenale e del nostro aiuto nella guerra contro chiunque fosse necessario. Così ho vissuto lì per un anno e mezzo.";
			link.l1 = "Tu, Jean, non sei più quello di una volta. D'ora in poi sei il Fortunato.";
			link.l1.go = "SharlieEpilog_PikarResurrected_10";
		break;

		case "SharlieEpilog_PikarResurrected_10":
			dialog.text = "Ahah. Non mi oppongo. Poi, nel nostro battibile, è capitato un predicatore francese. Abbiamo subito capito: era la nostra occasione per uscire da lì senza catene. Abbiamo corrotto la sua scorta – e poco dopo già navigavamo verso Tortuga.\nE poi, come avrai sicuramente intuito, ho deciso di smettere di giocare a rincorrere la morte. Ho lasciato il vecchio mestiere... e, cogliendo l’occasione, ho comprato un’"+GetShipName("Ulysse")+"'.\n"+"E tu? Come hai fatto a finire così? Sapevo che un tipo in gamba come te non sarebbe rimasto a lungo a fare il galoppino di Tirax. Ma che tu sia diventato una persona così importante... sai davvero sorprendere, accidenti.";
			link.l1 = "Ahah. Sentilo chi parla. Quindi hai deciso di diventare un mercante?";
			link.l1.go = "SharlieEpilog_Pikar_6";
		break;
		
		case "SharlieEpilog_Captain_5":
			dialog.text = "Per chi è in mare!";
			link.l1 = "E alla signora Fortuna!";
			link.l1.go = "SharlieEpilog_Captain_6";
		break;

		case "SharlieEpilog_Captain_6":
			dialog.text = "Bene, veniamo al dunque. Cosa volevate propormi?";
			link.l1 = "State andando a Bordeaux... Vedete, anch’io sono diretto lì.";
			link.l1.go = "SharlieEpilog_Captain_7";
		break;

		case "SharlieEpilog_Captain_7":
			dialog.text = "Volete che vi porti a bordo? Per quanto ne so, dovreste avere una vostra nave. Magari anche un’intera flottiglia. Eppure avete deciso di salire su una nave altrui. Ho capito bene?";
			link.l1 = "Proprio così. Gli ultimi avvenimenti mi hanno fatto riflettere: forse è arrivato il momento di gettare l’ancora, di mettere radici... Credo che il ruolo di semplice passeggera sulla tua nave mi aiuterà a capire se riuscirò ad accettare un nuovo ritmo di vita.";
			link.l1.go = "SharlieEpilog_Captain_8";
		break;

		case "SharlieEpilog_Captain_8":
			dialog.text = "Hmm... Quindi vi siete un po' stancati di rischiare il collo per niente? Capisco bene. Anch’io, in effetti... Ma lasciamo stare. Un posto sulla nave per voi si trova, anche per tutta la vostra compagnia. Il viaggio è già stato pagato da un giovane damerino francese – e lui stesso paga anche per la velocità, quindi non caricherò le stive. Quanto al pagamento...";
			link.l1 = "Non preoccupatevi, capitano. Non sono meno generoso del vostro datore di lavoro e sono pronto a pagare la stessa somma.";
			link.l1.go = "SharlieEpilog_Captain_9";
		break;

		case "SharlieEpilog_Captain_9":
			dialog.text = "Eccellente! Allora, d'accordo?";
			link.l1 = "Affare fatto! Questo merita un brindisi!";
			link.l1.go = "SharlieEpilog_Captain_10";
		break;

		case "SharlieEpilog_Captain_10":
			dialog.text = "Sì, questo rum è proprio buono... Mi serviranno due settimane per rimettere in sesto la nave e fare tutte le provviste necessarie. Dopo di che, potremo salpare.";
			link.l1 = "Allora ci vediamo qui tra due settimane. Beh, a presto, capitano.";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l1.go = "SharlieEpilog_Captain_11_wife";
			}
			else
			{
				link.l1.go = "SharlieEpilog_Captain_11";
			}
		break;
		
		case "SharlieEpilog_Captain_11_wife":
			DialogExit();
			AddQuestRecord("SharlieEpilog", "11_3");
			AddQuestUserData("SharlieEpilog", "sName", GetFullName(npchar));
			AddDialogExitQuestFunction("SharlieEpilog_OutTavern");
		break;
		
		case "SharlieEpilog_Captain_11":
			DialogExit();
			AddQuestRecord("SharlieEpilog", "11_4");
			AddQuestUserData("SharlieEpilog", "sName", GetFullName(npchar));
			AddDialogExitQuestFunction("SharlieEpilog_OutTavern");
		break;
		
		case "SharlieEpilog_Pikar_WaitInTavern":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "Allora, amico, hai sistemato le tue faccende? Facciamo vedere a questo pollaio come ci si diverte davvero?";
				link.l1 = "Non è ancora il momento, "+npchar.name+", ho ancora alcune faccende da sbrigare.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Capitano, siete già pronto a salire a bordo?";
				link.l1 = "Purtroppo, collega, ho ancora delle faccende da sbrigare.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "SharlieEpilog_Pikar_WaitInTavern";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_FarewellOfficers") && CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				// только если знаком с Пикаром и поговорил с женой
				link.l2 = "Ehi, oste! Da bere per tutti, offro io! E non roba qualunque, ma il meglio che hai!";
				link.l2.go = "SharlieEpilog_Pikar_WaitInTavern_2";
			}
		break;
		
		case "SharlieEpilog_Pikar_WaitInTavern_2":
			dialog.text = "...";
			link.l1 = "Per noi, amico mio. Per il vento salato, per il mare senza fine e per l’orizzonte – sempre invitante, sempre irraggiungibile...";
			link.l1.go = "SharlieEpilog_FrameInSea";
			DelLandQuestMark(npchar);
		break;
		
		case "SharlieEpilog_FrameInSea":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_FrameInSea");
		break;
		
		case "SharlieEpilog_Mary_1":
			dialog.text = "...";
			link.l1 = ""+npchar.name+", cara, vorrei parlarti di mio padre.";
			link.l1.go = "SharlieEpilog_Mary_2";
			DelLandQuestMark(npchar);
		break;

		case "SharlieEpilog_Mary_2":
			dialog.text = "Cosa è successo, caro? Spero che stia bene, giusto?";
			link.l1 = "Beh, non così bene come si vorrebbe. Ci sono motivi di credere che non gli resti molto tempo, e lo preoccupa molto l’idea di non vedermi prima di partire per il suo ultimo viaggio.";
			link.l1.go = "SharlieEpilog_Mary_3";
		break;

		case "SharlieEpilog_Mary_3":
			dialog.text = ""+pchar.name+"...";
			link.l1 = "Lo so, mia cara, lo so... Ma questa è la vita. Vorrei che vi conosceste. Così vedrà che moglie straordinaria ho e ci darà la sua benedizione.";
			link.l1.go = "SharlieEpilog_Mary_4";
		break;

		case "SharlieEpilog_Mary_4":
			dialog.text = "E se non gli piaccio, giusto? Non sono mica di sangue nobile...";
			link.l1 = "Che sciocchezze, "+npchar.name+", ma come potrebbe non piacergli? Sei un vero incanto! Se hai conquistato il mio cuore, conquisterai anche il suo.";
			link.l1.go = "SharlieEpilog_Mary_5";
		break;

		case "SharlieEpilog_Mary_5":
			dialog.text = "Lo pensi davvero, caro? Allora dobbiamo andare da lui il prima possibile.";
			link.l1 = "È proprio quello che intendo fare. Ho già trovato una nave per noi. Salpiamo tra due settimane.";
			link.l1.go = "SharlieEpilog_Mary_6";
		break;

		case "SharlieEpilog_Mary_6":
			dialog.text = "La nave? Non salperemo sulla nostra?";
			link.l1 = "No, cara. Partiremo sulla pinassa '"+GetShipName("Ulysse")+"'.  È su di lui che sono arrivato ai Caraibi – ed è su di lui che li lascerò.";
			link.l1.go = "SharlieEpilog_Mary_7";
		break;

		case "SharlieEpilog_Mary_7":
			dialog.text = "E tu non sarai più capitano?";
			link.l1 = "Prima o poi avrei comunque dovuto rinunciare a questo ruolo. Spero che sia solo per un po'. Ma, in ogni caso, non mi farà male capire cosa mi aspetta in futuro.";
			link.l1.go = "SharlieEpilog_Mary_8";
		break;

		case "SharlieEpilog_Mary_8":
			dialog.text = "E i nostri ufficiali? Non potremo certo portarli tutti con noi. E dubito che vorranno aspettarti qui.";
			link.l1 = "Ehm... Sì, hai ragione. Dovrò parlare con ognuno di loro e, molto probabilmente, dire addio per sempre. Anche se non sarà facile, considerando tutto quello che abbiamo passato insieme.";
			link.l1.go = "SharlieEpilog_Mary_9";
		break;
			
		case "SharlieEpilog_Mary_9":
			dialog.text = "Forse dovremmo organizzare una piccola festa d’addio in taverna?";
			link.l1 = "Ci ho pensato anch'io, cara. Sai... forse hai ragione. In effetti è davvero una buona idea.";
			link.l1.go = "exit";
			link.l2 = "Non credo sia una buona idea. Meglio evitare addii plateali... Così, forse, sarà meglio per tutti. Al massimo, potremmo invitare solo gli amici più fidati...";
			link.l2.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_FarewellOfficers");
		break;
		
		case "SharlieEpilog_Helena_1":
			dialog.text = "...";
			link.l1 = "Tesoro, vorrei parlarti di mio padre.";
			link.l1.go = "SharlieEpilog_Helena_2";
			DelLandQuestMark(npchar);
		break;

		case "SharlieEpilog_Helena_2":
			dialog.text = "Certo, "+pchar.name+". Spero che stia bene?";
			link.l1 = "Non proprio. È malato da tempo e, temo, la malattia avrà presto la meglio... Mio padre affronta tutto questo con grande coraggio. L’unica cosa che davvero lo preoccupa è che potrebbe non rivedermi più. Voglio andare a trovarlo... e presentarti a lui. Vorrei avere la sua benedizione per il nostro matrimonio.";
			link.l1.go = "SharlieEpilog_Helena_3";
		break;

		case "SharlieEpilog_Helena_3":
			dialog.text = "Sarò felice di conoscerlo, amore mio. Quando salpiamo?";
			link.l1 = "Tra due settimane. Ma non è tutto. Non partiremo sulla nostra nave. Nel Vecchio Mondo ci porterà una pinassa '"+GetShipName("Ulysse")+" - quello stesso che un tempo mi ha portato qui.";
			link.l1.go = "SharlieEpilog_Helena_4";
		break;

		case "SharlieEpilog_Helena_4":
			dialog.text = ""+pchar.name+", ma cambiare nave prima di un lungo viaggio porta sfortuna.";
			link.l1 = "Non cambieremo nave, cara. Saremo passeggeri.";
			link.l1.go = "SharlieEpilog_Helena_5";
		break;

		case "SharlieEpilog_Helena_5":
			dialog.text = "Ma... amore, non capisco...";
			link.l1 = "Così deve essere, "+npchar.name+".   Prima o poi dovrò lasciare il comando della nave. E voglio sapere in anticipo quali sentimenti mi aspettano.";
			link.l1.go = "SharlieEpilog_Helena_6";
		break;

		case "SharlieEpilog_Helena_6":
			dialog.text = "Se è questa la tua decisione... Ma che ne sarà dei nostri ufficiali? Non potremo certo portarli tutti con noi. E dubito che vorranno aspettarti qui.";
			link.l1 = "Ehm... Sì, hai ragione. Dovrò parlare con ognuno di loro e, molto probabilmente, dirgli addio per sempre. Anche se non sarà facile, considerando tutto quello che abbiamo passato insieme.";
			link.l1.go = "SharlieEpilog_Helena_7";
		break;
			
		case "SharlieEpilog_Helena_7":
			dialog.text = "Forse dovremmo organizzare una piccola festa d’addio in taverna?";
			link.l1 = "Ci ho pensato anch'io, cara. Sai... forse è proprio quello che faremo. In effetti, è davvero una buona idea.";
			link.l1.go = "exit";
			link.l2 = "Non credo sia una buona idea. Meglio evitare addii plateali... Così, forse, sarà meglio per tutti. Al massimo, invitiamo solo gli amici più fidati...";
			link.l2.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_FarewellOfficers");
		break;
		
		// Диалог с Алонсо в таверне Сен-Пьера
		case "SharlieEpilog_AlonsoInTavern":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
			{
				dialog.text = "Capo... Ho già parlato con l’oste – ha preparato il miglior vino che ha. Quando cominciamo?";
				link.l1 = "Proprio adesso! Ehi, oste! Da bere per tutti, offro io!";
				link.l1.go = "SharlieEpilog_AlonsoInTavern_1";
			}
			else
			{
				dialog.text = "Capitano, mi avevate promesso di raccontarmi come avete saputo dell’‘Ulisse’.";
				link.l1 = "Mi ricordo, mi ricordo. Ehi, oste! Il miglior rum per questo tavolo.";
				link.l1.go = "SharlieEpilog_AlonsoInTavern_3";
			}
			link.l2 = "Presto, "+npchar.name+". Ho ancora delle questioni urgenti da sbrigare.";
			link.l2.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_AlonsoInTavern";
		break;
		
		case "SharlieEpilog_AlonsoInTavern_1":
			dialog.text = "...";
			link.l1 = "Allora, amico, chiama gli altri – facciamo vedere a Saint-Pierre come si divertono i veri lupi di mare!";
			link.l1.go = "SharlieEpilog_AlonsoInTavern_2";
			DelLandQuestMark(npchar);
		break;
		
		case "SharlieEpilog_AlonsoInTavern_2":
			dialog.text = "Ah-ah! Capitano, non ci crederete – li ho già chiamati!";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_FrameInSea";
		break;
		
		case "SharlieEpilog_AlonsoInTavern_3":
			dialog.text = "...";
			link.l1 = "Per noi, "+npchar.name+"   Alla signora Fortuna e al vento che gonfia le nostre vele!";
			link.l1.go = "SharlieEpilog_FrameInSea";
			DelLandQuestMark(npchar);
		break;
		
		// На пинасе Улисс
		case "SharlieEpilog_Alonso_1":
			dialog.text = "Che scompiglio che abbiamo combinato, capitano. Ah-ah. Sembra che solo le scarse scorte di rum dell’oste abbiano salvato la taverna dalla rovina totale.";
			link.l1 = "Non me lo ricordare, "+npchar.name+", solo ora mi sento un po' meglio.";
			link.l1.go = "SharlieEpilog_Alonso_2";
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "tutorial_4", "", -1);
			CharacterTurnByLoc(pchar, "quest", "quest6");
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "tutorial_5", "", -1);
			CharacterTurnByLoc(npchar, "quest", "quest7");
		break;
		
		case "SharlieEpilog_Alonso_2":
			dialog.text = "Come desidera, signore "+pchar.lastname+". Ah-ah. Però abbiamo salutato la Martinica in grande stile. Lì si ricorderanno a lungo della vostra partenza.";
			link.l1 = "Mi sa che abbiamo un po’ esagerato quando abbiamo messo l’oste sulla scialuppa e l’abbiamo mandato a Le François a prendere da bere.";
			link.l1.go = "SharlieEpilog_Alonso_2_1";
		break;
		
		case "SharlieEpilog_Alonso_2_1":
			if (GetAttributeInt(pchar, "questTemp.SharlieEpilog_Friends") >= 2)
				{
					dialog.text = "Ah ah ah. Non preoccupatevi per lui. In questi giorni ha messo insieme così tanto oro che potrebbe comprarsi una piantagione, e magari anche un titolo nobiliare in più.";
				}
			else
				{
					dialog.text = "Ah ah ah. Non preoccupatevi per lui. In questi giorni ha guadagnato così tanto oro che potrebbe comprarsi una piantagione, e magari anche un titolo nobiliare. Peccato solo che non abbiate parlato con nessuno degli ufficiali. Ci mancheranno.";
				}
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Alonso_3";
		break;
		
		case "SharlieEpilog_Alonso_3":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
				{
					sld = CharacterFromID("Helena");
					locCameraFromToPos(-8.97, 6.39, -12.78, true, -8.54, 4.94, -13.90);
				}
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
				{
					sld = CharacterFromID("Mary");
					locCameraFromToPos(-3.62, 4.03, 2.30, true, -4.98, 2.62, 3.26);
					// locCameraFromToPos(-4.13, 4.23, 2.55, true, -5.71, 2.54, 3.58);
				}
				dialog.text = "Sembra, "+sld.name+" è ancora arrabbiata con voi perché siete spariti per tutta la notte.";
			}
			else
			{
				dialog.text = "Ma con quel mercante… lì, capitano, davvero avete un po’ esagerato.";
			}
			link.l1 = "Diavolo, proprio noi con Jean dovevamo ficcarci in quel negozio locale…";
			link.l1.go = "SharlieEpilog_Alonso_4";
		break;
		
		case "SharlieEpilog_Alonso_4":
			dialog.text = "E come hanno fatto a non beccarvi? Sarebbe stato proprio divertente - "+GetTitle(PChar,true)+"   sorpreso mentre cercava di rubare alcune bottiglie di vino.";
			link.l1 = "Ti fa ridere, "+npchar.name+", e io non ricordo nemmeno la metà di tutto questo. L’ultima volta che mi sono ubriacato così... beh... praticamente mai.";
			link.l1.go = "SharlieEpilog_Alonso_5";
			locCameraFromToPos(-8.74, 6.30, 7.38, true, -14.34, 4.16, 6.56);
		break;
		
		case "SharlieEpilog_Alonso_5":
			dialog.text = "Allora, alla prima, capitano. Ahah. Mi è piaciuto. Lo rifarei volentieri. Quando dici che torniamo?";
			link.l1 = "Vai a controllare le nostre cose, piuttosto. Abbiamo preso tutto? Io scenderò dopo – l’aria della stiva ora non mi farebbe certo bene.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_UlysseInSea_8");
		break;
		
		// диалог с Алонсо у горы золота
		case "SharlieEpilog_Alonso_11": // этап 1
			dialog.text = "...";
			link.l1 = "Guarda solo questo... che scossa ha preso la nave.";
			link.l1.go = "SharlieEpilog_Alonso_12";
			SharlieEpilog_GoldInTheDeck_1_1();
		break;
		
		case "SharlieEpilog_Alonso_12":
			dialog.text = "Qui c'è un vero mare di oro, capo!";
			link.l1 = "Vedo, "+npchar.name+".   Bisogna nascondere tutto questo in fretta nei forzieri, prima che la ciurma lo veda.   Non hanno bisogno di таких tentazioni.";
			link.l1.go = "SharlieEpilog_Alonso_13";
		break;
		
		case "SharlieEpilog_Alonso_13":
			dialog.text = "No, non resisto...";
			link.l1 = "Cosa?";
			link.l1.go = "exit";
			locCameraFromToPos(-1.28, 7.70, -10.26, true, 0.74, 5.42, -9.49);
			AddDialogExitQuestFunction("SharlieEpilog_GoldInTheDeck_2");
		break;
			
		case "SharlieEpilog_Alonso_21": // этап 2
			dialog.text = "...";
			link.l1 = "Ehi, che ti prende?";
			link.l1.go = "SharlieEpilog_Alonso_22";
			// SharlieEpilog_GoldInTheDeck_6();
		break;
		
		case "SharlieEpilog_Alonso_22":
			dialog.text = "...";
			link.l1 = "Su, alzati. Hai trovato proprio il momento...";
			link.l1.go = "SharlieEpilog_Alonso_23";
		break;
		
		case "SharlieEpilog_Alonso_23":
			dialog.text = "Unitevi a noi, capitano.";
			link.l1 = "Alzati, basta fare lo stupido.";
			link.l1.go = "SharlieEpilog_Alonso_24";
		break;
		
		case "SharlieEpilog_Alonso_24":
			dialog.text = "Ma rilassatevi. Dovete sentirlo davvero.";
			link.l1 = "D'accordo, al diavolo. Dai, fatti più in là.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_GoldInTheDeck_7");
		break;
		
		case "SharlieEpilog_Alonso_31": // этап 3
			dialog.text = "Ho sempre sognato di fare così...";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Alonso_32";
			SharlieEpilog_GoldInTheDeck_10();
		break;
		
		case "SharlieEpilog_Alonso_32":
			dialog.text = "Una sensazione magnifica, vero, capitano?";
			link.l1 = "Ah ah ah. Ecco come ho visitato i Caraibi – solo per scoprire come sta mio fratello. Mio padre di certo non si aspettava un colpo di scena simile. Ah ah!";
			link.l1.go = "SharlieEpilog_Alonso_33";
		break;
		
		case "SharlieEpilog_Alonso_33":
			dialog.text = "Signore "+GetTitle(NPChar,false)+" "+pchar.lastname+"... Ah-ah! Vi ricordate come siete arrivato sull’arcipelago?";
			link.l1 = "Altroché se ricordo. Ahah. Quasi non ci credo che una volta ero vanitoso come quel tipo che ora passeggia sul ponte. Quante ne sono successe in queste maledette Caraibi… Intrighi, non-morti, il fratellino Kukulkan…";
			link.l1.go = "SharlieEpilog_Alonso_34";
		break;
		
		case "SharlieEpilog_Alonso_34":
			dialog.text = "Sei dannatamente fortunato, capitano. Mettere insieme una fortuna così — e restare vivo… non è da tutti.";
			link.l1 = "Già. Va bene, basta oziare. Non si sa mai – qualcuno potrebbe davvero accorgersene.";
			link.l1.go = "exit";
			locCameraSleep(true);
			AddDialogExitQuestFunction("SharlieEpilog_GoldInTheDeck_11");
		break;
		
		// диалоги в катсцене с брашпилем
		case "SharlieEpilog_windlass_1":
			dialog.text = "...";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				link.l1 = "Ascolta, amico, non mi piace il fermo del verricello su questa nave. È troppo poco affidabile. Qualcuno potrebbe staccarlo per sbaglio.";
			}
			else
			{
				link.l1 = "Ascoltate, capitano, non mi piace il fermo del verricello su questa nave. È davvero poco affidabile. Basterebbe un attimo di distrazione perché qualcuno lo faccia saltare.";
			}
			link.l1.go = "SharlieEpilog_windlass_2";
			locCameraFromToPos(-7.57, 9.68, -21.21, true, -9.79, 7.76, -20.01);
		break;
		
		case "SharlieEpilog_windlass_2":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "Ma dai, "+pchar.name+",   su una nave tutti sanno che…";
			}
			else
			{
				dialog.text = "Ma dai, capitano. A chi mai verrebbe in mente...";
			}
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_windlass_3");
		break;
		
		case "SharlieEpilog_windlass_3": // диалог Пикара и дворянина
			dialog.text = "Ehi, tu, idiota... Che diavolo stai facendo? Non ti hanno mai insegnato a non ficcare quei tuoi piedi storti dove non dovresti?";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_windlass_4";
			locCameraFromToPos(-10.28, 9.94, -22.90, true, -9.29, 7.86, -21.36);
			NPCsLookEachOther("SharlieEpilog_Pikar", "SharlieEpilog_Bernard_Clone");
			CharacterTurnByChr(pchar, CharacterFromID("SharlieEpilog_Bernard_Clone"));
		break;
		
		case "SharlieEpilog_windlass_4":
			dialog.text = "...";
			link.l1 = "Piano, non dimenticarti con chi parli! Sono un nobile, e non permetterò che…";
			link.l1.go = "SharlieEpilog_windlass_5";
		break;
		
		case "SharlieEpilog_windlass_5":
			dialog.text = "Sulla mia nave tu non sei nessuno. I miei marinai qui hanno più diritti di te. Quindi o te ne stai zitto senza dare fastidio a nessuno, oppure ti butto io stesso fuori bordo.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_windlass_6";
		break;
		
		case "SharlieEpilog_windlass_6": // диалог Пикара и Шарля
			dialog.text = "...";
			link.l1 = "Ah ah ah. È come se mi fossi visto dall'esterno.";
			link.l1.go = "SharlieEpilog_windlass_7";
			SharlieEpilog_windlass_9_1();
		break;
		
		case "SharlieEpilog_windlass_7":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "Di cosa parli?";
				link.l1 = "Sì, non importa, "+npchar.name+". Non essere così severo con il nostro passeggero. Per lui è ancora tutto nuovo. In fondo, anche noi non siamo diventati lupi di mare in un giorno solo.";
			}
			else
			{
				dialog.text = "Di cosa state parlando?";
				link.l1 = "Non fateci caso, "+npchar.name+".   E non giudicate troppo severamente il vostro passeggero.   Per lui è tutto nuovo.   In fondo, anche noi non siamo diventati lupi di mare dall’oggi al domani.";
			}
			link.l1.go = "SharlieEpilog_windlass_8";
		break;
		
		case "SharlieEpilog_windlass_8":
			dialog.text = "Con il suo talento, finirà impigliato nel verricello prima di diventare un vero marinaio. Bisogna proprio riuscirci...";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				link.l1 = "Chissà, chissà. Sono arrivato sull’arcipelago proprio così: spensierato, curioso e un po’ arrogante, come un ragazzino.";
			}
			else
			{
				link.l1 = "Chi lo sa. Quando sono arrivato sull’arcipelago, ero anch’io un giovane spensierato, curioso e presuntuoso.";
			}
			link.l1.go = "SharlieEpilog_windlass_9";
		break;
		
		case "SharlieEpilog_windlass_9":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "Ma dai, che paragone.\n"+"Aspetta\n"+"Quindi ti rivedi in lui? Ah ah ah. Allora prenditelo tu sotto la tua ala. Io non ho nessuna intenzione di fare da balia a quel tipo.";
				link.l1 = "Mi occuperò di lui. Finché non gli toglierai la pelle. Ma per l’ancora che paghi fino all’ultimo.";
			}
			else
			{
				dialog.text = "Quindi vi siete riconosciuto in lui? Ahah. Beh, capitano, allora prendetelo sotto la vostra protezione. Io non ho intenzione di fare da balia.";
				link.l1 = "Lo terrò d'occhio. Finché non gli avrete tolto anche l'ultima camicia. Ma per l'ancora – che paghi come si deve.";
			}
			link.l1.go = "SharlieEpilog_windlass_10";
		break;
		
		case "SharlieEpilog_windlass_10":
			dialog.text = "Scegliere l’ancora. Aspettiamo il vento. Mantenere la rotta.";
			link.l1 = "...";
			link.l1.go = "exit";
			SharlieEpilog_windlass_10();
			AddDialogExitQuestFunction("SharlieEpilog_AlonsoTrollingHighSailor_1");
		break;
		
		// диалоги Старшего матроса и Алонсо		
		case "SharlieEpilog_AlonsoTrollingHighSailor_2": // Алонсо
			dialog.text = "";
			link.l1 = "Salpiamo l’ancora. Prendiamo il vento. Rotta a nord-est.";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_3";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_2();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_3": // Старший матрос
			dialog.text = "";
			link.l1 = "Alzate l’ancora! Abbassate il fiocco – prendiamo il vento. Al lavoro...";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_4";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_1();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_4": // Алонсо
			dialog.text = "";
			link.l1 = "Cosa stai facendo?";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_5";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_2();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_5": // Старший матрос
			dialog.text = "";
			link.l1 = "Cosa stai facendo?";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_6";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_1();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_6": // Алонсо
			dialog.text = "";
			link.l1 = "No, cosa stai facendo?";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_7";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_2();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_7": // Старший матрос
			dialog.text = "";
			link.l1 = "Argh...   Che stai facendo? Il nostromo ripete gli ordini del capitano.";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_8";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_1();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_8": // Алонсо
			dialog.text = "";
			link.l1 = "Ecco perché il nostromo li ripete.";
			link.l1.go = "exit";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_2();
			AddDialogExitQuestFunction("SharlieEpilog_AlonsoTrollingHighSailor_2");
		break;
		
		// Шарль ругает Алонсо
		case "SharlieEpilog_AlonsoTrollingHighSailor_9":
			dialog.text = "...";
			link.l1 = "Lascia perdere, Alonso. Siamo solo passeggeri qui. Hai dimenticato?";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_10";
			locCameraFromToPos(-8.00, 4.49, -1.91, true, -9.97, 2.64, -1.90);
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_10":
			dialog.text = "Ehm... Scusa, capitano. Non ho resistito\nMa ne è valsa la pena. Era come tornare indietro nel tempo.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_AlonsoTrollingHighSailor_5");
		break;
		
		// Диалог Шарля с Пикаром о всяком (можно попасть в Поместье де Монпе)
		case "SharlieEpilog_PikarOnUliss":
			dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+pchar.lastname+"... Cosa desiderate?";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_A"))
				{
					link.l1 = "Allora, amico, come ti senti?";
					link.l1.go = "SharlieEpilog_PikarOnUliss_A_1";
				}
				if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_B"))
				{
					if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarAlive"))
					{
						link.l2 = "Ammettilo, "+npchar.name+",   hai deciso di diventare un mercante già quando hai scelto di separarti da Tirax, vero?";
						link.l2.go = "SharlieEpilog_PikarOnUliss_B_1";
					}
					else
					{
						link.l2 = "Ammettilo, "+npchar.name+",   non è vero che avevi già deciso di diventare mercante laggiù, alla piantagione?";
						link.l2.go = "SharlieEpilog_PikarOnUliss_B_1";
					}
				}
				if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_C"))
				{
					link.l3 = "Ricordo chiaramente che un messo ha cercato di parlarmi. Ma, per quanto mi sforzi, non riesco proprio a ricordare il motivo. Tu ne sai qualcosa?";
					link.l3.go = "SharlieEpilog_PikarOnUliss_C_1";
				}
			}
			else
			{
				if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_E"))
				{
					link.l1 = "Siete già stato a Bordeaux, capitano?";
					link.l1.go = "SharlieEpilog_PikarOnUliss_E_1";
				}
				if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_F"))
				{
					link.l2 = "Capitano, a dire il vero non ricordo nemmeno bene come abbiamo lasciato la Martinica. Dovevo ricevere una lettera importante da una persona, ma a quanto pare non mi è mai arrivata. Nessuno si è rivolto a voi per questo?";
					link.l2.go = "SharlieEpilog_PikarOnUliss_F_1";
				}
			}
			link.l4 = "Sembra che sia arrivata una leggera brezza. È ora di spiegare le vele. (Salpare)";
			link.l4.go = "SharlieEpilog_PikarOnUliss_D_1";
			link.l5 = "Niente per ora. Vado.";
			link.l5.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_PikarOnUliss";
		break;
		
		case "SharlieEpilog_PikarOnUliss_A_1":
			dialog.text = "Ah ah... Mai stato meglio! Mi sento pieno di forze e in ottima salute.";
			link.l1 = "Davvero? Eppure sembri uno che è appena stato masticato da uno squalo.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_A_2";
			pchar.questTemp.SharlieEpilog_PikarOnUliss_A = true;
		break;

		case "SharlieEpilog_PikarOnUliss_A_2":
			dialog.text = "Chi parla! Anche tu sembri proprio un cane bastonato.";
			link.l1 = "E mi sento proprio così. Ahah. Diavolo, non ricordo nemmeno come e quando siamo salpati.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_A_3";
		break;

		case "SharlieEpilog_PikarOnUliss_A_3":
			dialog.text = "Eh, che festa memorabile. Solo che è costata un occhio della testa. I miei idioti hanno quasi incendiato il bordello – ho dovuto sborsare un sacco di monete per mettere a tacere lo scandalo. Ora quei babbei mi saranno debitori a vita.\nE tu come ti senti nei panni del passeggero? Non hai ancora cominciato a ululare dalla noia?";
			link.l1 = "Ho la sensazione di non avere più il controllo del mio destino. Ma allo stesso tempo provo uno strano sollievo. Come se avessi tolto dalle spalle una cassa piena di palle di cannone.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_A_4";
		break;

		case "SharlieEpilog_PikarOnUliss_A_4":
			dialog.text = "Ahah. Va bene, se la nostalgia ti assale – sono pronto a prenderti come mio ufficiale.";
			link.l1 = "Molto generoso da parte tua, ma devo rifiutare. In tutti i Caraibi non si troverebbe abbastanza rum per sostenere le nostre baldorie.";
			link.l1.go = "SharlieEpilog_PikarOnUliss";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_1":
			if (IsStateTitle()) 
			{
				dialog.text = "Non proprio, amico mio. Ogni tanto mi veniva in mente questa idea, ma non le davo mai troppo peso. È tornata a trovarmi una seconda volta, quando mi è arrivata voce che tutta la banda dei fedeli cani di Tirax era sparita nel nulla. Tutti quanti – Mannaia, il Pelato, e persino quella vecchia carogna puzzolente di Leprechaun.\nE quando ho sentito dei tuoi successi, ho deciso che era davvero ora di smettere. Non si può rischiare la testa per qualche moneta per sempre.\nDi oro ne ho abbastanza per non dovermi mai più inchinare davanti a nessun bastardo impomatato. Ma separarmi dal mare... a quello non ero pronto. Così ho deciso di cambiare mestiere.";
			} 
			else 
			{
				dialog.text = "Non proprio, amico mio. Ogni tanto mi veniva in mente questa idea, ma non le davo mai troppo peso. Ma poi è tornata a farmi visita quando ho sentito dire che tutta la banda dei fedeli cani di Tirax era sparita nel nulla. Tutti quanti – Mannaia, il Pelato, e persino quella vecchia carogna puzzolente di Leprechaun.\nE quando i proiettili nemici hanno rischiato di farmi saltare il cervello due volte in una sola battaglia, ho deciso che ne avevo abbastanza. Non si può rischiare la testa per delle monete per sempre.\nD’oro ne ho abbastanza per non dovermi mai più umiliare davanti a nessun bastardo incipriato. Ma lasciare il mare... a quello non ero pronto. Così ho deciso di cambiare mestiere.";
			}
			link.l1 = "Tesak, Pelato, Leprechaun... Sai dove sono spariti?";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_2";
			pchar.questTemp.SharlieEpilog_PikarOnUliss_B = true;
		break;

		case "SharlieEpilog_PikarOnUliss_B_2":
			dialog.text = "No, non lo so. E a dire il vero – non me ne importa niente di dove siano finite quelle bestie. Anche se fossero sparite all’inferno.";
			link.l1 = "Più o meno lì li ho mandati.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_3";
		break;

		case "SharlieEpilog_PikarOnUliss_B_3":
			dialog.text = "Quindi sei stato tu a sterminare tutta la loro compagnia? Incredibile! E Marcus te l’ha perdonata?";
			link.l1 = "Lui non lo sa.   E, molto probabilmente, non lo saprà mai.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_4";
		break;

		case "SharlieEpilog_PikarOnUliss_B_4":
			dialog.text = "Allora, accidenti, ho fatto proprio bene ad andarmene da loro, ah-ah. Tu, magari, non avresti risparmiato nemmeno la mia testa\nSolo una cosa non capisco – che diavolo te ne importava tutto questo?";
			link.l1 = "Avevi ragione: per un misero pezzo d’oro questi bastardi sono pronti a tutto, tradire, uccidere chiunque. Ci hanno attirato in uno dei sotterranei, nel Sud del Main, raccontandoci una favola su tesori inestimabili. Era una trappola ben congegnata, e quei dannati idioti ci sono cascati senza pensarci. Invece di dividere il bottino in parti uguali, hanno deciso che era meglio non condividere affatto: più semplice farla finita con me e prendersi tutto.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_5";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_5":
			dialog.text = "E non ci sono riusciti per niente, ah-ah! Aspetta un attimo, ma chi ha organizzato questa trappola?";
			if (CharacterIsAlive("Tonzag") && CheckPassengerInCharacter(pchar, "Tonzag"))
			{
				link.l1 = "Un certo Zorro, un vendicatore popolare spagnolo – per vendicare Cartagena. Chiunque fosse sopravvissuto a quel massacro sarebbe dovuto restare per sempre nei sotterranei: tutte le uscite erano state chiuse. Ma a quel bastardo non è andata bene – il mio ufficiale l’ha ingannato.";
			}
			else
			{
				link.l1 = "Un certo Zorro, il vendicatore popolare spagnolo – per vendicarsi di Cartagena. Chiunque fosse sopravvissuto a quell’inferno di carneficina sarebbe dovuto restare per sempre nelle segrete: tutte le uscite erano sbarrate. Io sono riuscito a scappare. Ma a un prezzo altissimo.";
			}
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_6";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_6":
			dialog.text = "Almeno sei rimasto vivo. E, immagino, ti sei preso tutto l’oro per cui hai quasi rischiato la pelle?";
			link.l1 = "Non c’era nessun oro lì. Era solo piombo dorato...";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_7";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_7":
			dialog.text = "...";
			link.l1 = "Dopo tutto questo, ho deciso di lasciare Tirax. Sei il primo a cui lo racconto. A parte i miei ufficiali.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_8";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_8":
			dialog.text = "Non mi piace dire 'te l'avevo detto', ma... te l'avevo detto.";
			link.l1 = "Fermarmi al momento giusto non è il mio punto forte. Quindi dovrai darmi qualche lezione.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_9";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_9":
			dialog.text = "Mi conosci ormai – per un paio di boccali di buon rum ti racconterei anche del mio nascondiglio d’oro, eh-eh.";
			link.l1 = "E invece da me non aspettarti tanta generosità, ah-ah-ah. Ti bastino le tue provviste.";
			link.l1.go = "SharlieEpilog_PikarOnUliss";
		break;
		
		case "SharlieEpilog_PikarOnUliss_C_1":
			dialog.text = "Lo so. Ha cercato di rifilarti delle lettere – da un certo Ben, o forse Benedetto. Ma tu hai ringhiato che non conosci nessun Ben e hai minacciato di buttarlo fuori dalla taverna se continuava a rovinarci la serata.";
			link.l1 = "Diavolo... Sembra che queste fossero lettere dell'abate Benoît. Lettere importanti.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_C_2";
			pchar.questTemp.SharlieEpilog_PikarOnUliss_C = true;
		break;

		case "SharlieEpilog_PikarOnUliss_C_2":
			dialog.text = "Allora, meno male che li ho presi io. Eh-eh.  Ho sentito subito che quel ragazzino aveva scelto il destinatario giusto. Tieni.";
			link.l1 = "Mi hai davvero tirato fuori dai guai, "+npchar.name+", grazie.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_C_3";
		break;

		case "SharlieEpilog_PikarOnUliss_C_3":
			dialog.text = "Un semplice 'grazie' non basta, amico. Mi devi da bere – e non una qualsiasi, ma la migliore che si trova a Bordeaux.";
			link.l1 = "Avrai da bere, accattone. Il nostro rum, certo, non è come quello dei Caraibi, ma il vino... Un vino così non l’hai mai assaggiato.";
			link.l1.go = "SharlieEpilog_PikarOnUliss";
		break;
		
		case "SharlieEpilog_PikarOnUliss_E_1":
			dialog.text = "Non mi è mai capitato...";
			link.l1 = "Vi invidio. Vorrei poter rivedere Bordeaux come la prima volta. Probabilmente preferite il rum, ma vi consiglio comunque di visitare la fiera del vino vicino al municipio. Qui nei Caraibi, i veri intenditori sono pronti a spendere una fortuna per il nostro clairet.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_E_2";
			pchar.questTemp.SharlieEpilog_PikarOnUliss_E = true;
		break;

		case "SharlieEpilog_PikarOnUliss_E_2":
			dialog.text = "Grazie per il consiglio. Posso farle una domanda?";
			link.l1 = "Certo.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_E_3";
		break;

		case "SharlieEpilog_PikarOnUliss_E_3":
			dialog.text = "Che effetto fa essere passeggera dopo tanti anni al timone? Ti sei già abituata al nuovo ruolo?";
			link.l1 = "Hmm... Ho la sensazione di non avere più il controllo del mio destino. Ma allo stesso tempo provo uno strano sollievo. Come se mi fossi tolto un peso enorme dalle spalle. Penso che sia presto per trarre conclusioni.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_E_4";
		break;

		case "SharlieEpilog_PikarOnUliss_E_4":
			dialog.text = "Visto il dannato bonaccia in cui siamo finiti così opportunamente, avrete tempo quanto ne volete.";
			link.l1 = "In buona compagnia anche la bonaccia non pesa. E con la compagnia, capitano, devo ammettere che mi è andata bene.";
			link.l1.go = "SharlieEpilog_PikarOnUliss";
		break;
		
		case "SharlieEpilog_PikarOnUliss_F_1":
			dialog.text = "Si è fatto vivo. Un messo da parte di un certo abate. Continuo a dimenticare di darvi queste lettere. Eccole, prendete.";
			link.l1 = "Eccellente. Mi avete davvero aiutato, capitano. Vi ringrazio.";
			link.l1.go = "SharlieEpilog_PikarOnUliss";
			pchar.questTemp.SharlieEpilog_PikarOnUliss_F = true;
		break;
		
		case "SharlieEpilog_PikarOnUliss_D_1":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_A")){dialog.text = "Hai ragione.";}
			else {dialog.text = "Avete ragione.";}
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_PikarOnUliss_D_2";
		break;
		
		case "SharlieEpilog_PikarOnUliss_D_2":
			dialog.text = "Vento a dritta! Tutte le vele alzate, dalla trinchetta alla randa! Avanti tutta!";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_InEstateDeMonpe";
			locCameraFromToPos(-9.34, 8.28, -16.03, true, -9.33, 7.32, -20.48);
			CharacterTurnToLoc(CharacterFromID("SharlieEpilog_Pikar"), "quest", "quest10");
		break;
		
		case "SharlieEpilog_InEstateDeMonpe":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_InEstateDeMonpe");
		break;
		
		//Матрос 1 на верхней палубе
		case "SharlieEpilog_Sailor_1":
			dialog.text = "Una lama eccellente, "+GetTitle(NPChar,true)+". Posso dare un'occhiata?";
			link.l1 = "Forse, magari un'altra volta.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Sailor_1";
			PlaySound("Voice\" + LanguageGetLanguage() + "\officer05.wav");
		break;
		
		//Матрос 2 на верхней палубе
		case "SharlieEpilog_Sailor_2":
			dialog.text = "Quando arrivano finalmente queste clessidre? Sto per ingoiare la lingua.";
			link.l1 = "Pazienza, marinaio.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Sailor_2";
			PlaySound("Voice\" + LanguageGetLanguage() + "\other\Matrosi na Korablyah-07.wav");
		break;
		
		//Матрос 3 на орудийной палубе
		case "SharlieEpilog_Sailor_3":
			dialog.text = "Avete visto che topo è passato? Giuro, non ne ho mai visti di così grossi in vita mia!";
			link.l1 = "Mah...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Sailor_3";
			PlaySound("Voice\" + LanguageGetLanguage() + "\other\Matrosi na Korablyah-04.wav");
		break;
		
		//Матрос 4 на орудийной палубе
		case "SharlieEpilog_Sailor_4":
			dialog.text = "Cosa dovrei fare adesso, monsieur? Ho bevuto così tanto che non ricordo nemmeno come sono finito su questa nave. Non sono certo un marinaio... E a casa mi aspettano mia moglie e due bambini.";
			link.l1 = "Dovevi bere di meno. Ma ormai è tardi – dovrai diventare un marinaio.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Sailor_4";
			PlaySound("Voice\" + LanguageGetLanguage() + "\Ransack_2.wav");
		break;
		
		//Старший матрос
		case "SharlieEpilog_HighSailor_1":
			dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+pchar.lastname+". È un onore per noi avervi a bordo della nostra nave.";
			link.l1 = "Siete davvero cortese, monsieur nostromo. La cortesia non è la qualità più diffusa tra i vecchi lupi di mare. Ma non mettiamo in imbarazzo l’equipaggio – non siamo certo a corte di Sua Maestà. Rivolgiti a me semplicemente: capitano.";
			link.l1.go = "SharlieEpilog_HighSailor_2";
			PlaySound("Voice\" + LanguageGetLanguage() + "\YoungMan03.wav");
		break;

		case "SharlieEpilog_HighSailor_2":
			dialog.text = "Beh, sono diventato marinaio solo di recente. Prima lavoravo come scrivano per monsieur Levasseur. Ma quando lui è stato... ehm... fatto fuori, è arrivato un nuovo governatore. Nei circoli ristretti si è subito saputo che il signor de René de Boisdufle de Lettre era un vero mascalzone. A quel punto ho capito che non avrei più trovato un lavoro normale. La gente avrebbe pensato che sapevo tutto — e che sono stato zitto.";
			link.l1 = "E non era così?";
			link.l1.go = "SharlieEpilog_HighSailor_3";
		break;

		case "SharlieEpilog_HighSailor_3":
			dialog.text = "Ovviamente no. Non ho mai avuto l’abitudine di ficcare il naso negli affari altrui. Inoltre, Levasseur puniva severamente la curiosità.";
			link.l1 = "Questo lo credo volentieri.";
			link.l1.go = "SharlieEpilog_HighSailor_4";
		break;

		case "SharlieEpilog_HighSailor_4":
			dialog.text = "Così, quando l’avete fatto fuori, mi sono arruolato come marinaio sulla prima nave pirata che ho trovato. E, stranamente, mi sono ambientato e cambiato piuttosto in fretta. Sono persino riuscito a guadagnarmi il rispetto dei più temuti tagliagole. Ma quello che facevano loro… Non era per me. Così sono finito qui.";
			link.l1 = "Quindi sapevi del mio coinvolgimento nel destino di Levasseur?";
			link.l1.go = "SharlieEpilog_HighSailor_5";
		break;

		case "SharlieEpilog_HighSailor_5":
			dialog.text = "Certo, capitano. E sono felice che abbiate liberato il mondo da quel mostro. E, allo stesso tempo, mi avete tirato fuori dalla mia stanzetta soffocante. Mi avete fatto guardare alla mia vita con occhi nuovi.";
			link.l1 = "È sorprendente quanto sia piccolo questo mondo...";
			link.l1.go = "SharlieEpilog_HighSailor_6";
		break;

		case "SharlieEpilog_HighSailor_6":
			dialog.text = "Per quanto possa sembrare un paradosso, il mondo è tanto piccolo quanto è grande.";
			link.l1 = "Divertente. Non ci avevo mai pensato.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_HighSailor_7";
		break;
		
		case "SharlieEpilog_HighSailor_7":
			dialog.text = "Capitano "+pchar.lastname+"... Che serata meravigliosa, non è vero?";
			link.l1 = "Forse sì. Solo una leggera brezza da nord-ovest potrebbe renderlo ancora migliore.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_HighSailor_7";
			PlaySound("Voice\" + LanguageGetLanguage() + "\YoungMan03.wav");
		break;
		
		//Диалог с боцманом Моко
		case "SharlieEpilog_Moko_1":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "Capitano "+pchar.lastname+"...";
				link.l1 = "In realtà... Anzi, non importa. Ti ricordo! Tu sei Moko. Sei stato tu a scolarti un intero barile di rum tutto d'un fiato?";
				link.l1.go = "SharlieEpilog_Moko_2";
			}
			else
			{
				dialog.text = "Cosa volete... monsieur?";
				link.l1 = "Non capita tutti i giorni di incontrare un gigante come te. Come ti chiami?";
				link.l1.go = "SharlieEpilog_Moko_4";
			}
			PlaySound("Voice\" + LanguageGetLanguage() + "\citizen\Kapitani Korabley-07.wav");
		break;

		case "SharlieEpilog_Moko_2":
			dialog.text = "Io... E mi sono svegliato solo due giorni dopo.";
			link.l1 = "Un altro al tuo posto non sarebbe sopravvissuto nemmeno un paio d’ore. Se combatti come bevi – Jean è stato davvero fortunato ad avere un nostromo come te.";
			link.l1.go = "SharlieEpilog_Moko_3";
		break;

		case "SharlieEpilog_Moko_3":
			dialog.text = "Anche io sono stato fortunato con il capitano. Grazie a lui ho ritrovato la libertà. E grazie a voi. Sarei marcito nelle piantagioni, se non aveste aiutato Jean.";
			link.l1 = "È stata un'avventura interessante. E sono felice che sia finita meglio di quanto avrebbe potuto.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Moko_repeat";
		break;
		
		case "SharlieEpilog_Moko_4":
			dialog.text = ""+npchar.name+". Sono il nostromo su questa nave.";
			link.l1 = "Ahah, vorrei proprio vedere chi avrebbe il coraggio di contraddirti. Da quanto tempo servi sotto il capitano?";
			link.l1.go = "SharlieEpilog_Moko_5";
		break;

		case "SharlieEpilog_Moko_5":
			dialog.text = "Alcuni anni. Gli devo molto. Se non fosse stato per lui, sarei marcito in...";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Moko_6";
		break;

		case "SharlieEpilog_Moko_6":
			dialog.text = "...";
			link.l1 = "Volevi dire – nella piantagione?";
			link.l1.go = "SharlieEpilog_Moko_7";
		break;

		case "SharlieEpilog_Moko_7":
			dialog.text = "...";
			link.l1 = "Dai, "+npchar.name+", certo, hai tutto il diritto di non raccontarmi nulla, ma, se non l’hai ancora notato, non sono uno di quei damerini impomatati con la parrucca. Il capitano ti ha riscattato?";
			link.l1.go = "SharlieEpilog_Moko_8";
		break;

		case "SharlieEpilog_Moko_8":
			dialog.text = "Siamo scappati insieme. Dalla piantagione di Maracaibo. Senza Jean non ce l’avremmo mai fatta. Da allora sono nella sua ciurma. Prima come marinaio, ora sono il nostromo.";
			link.l1 = "Il capitano è stato in schiavitù? Non l’avrei mai detto. D’altronde, anch’io ho qualche scheletro nell’armadio. Sono contento che siate riusciti a sfuggire al tallone spagnolo, "+npchar.name+".   E allora, com’è essere un marinaio?";
			link.l1.go = "SharlieEpilog_Moko_9";
		break;

		case "SharlieEpilog_Moko_9":
			dialog.text = "Come se prima non avessi mai vissuto. Il mare è ormai la mia casa.";
			link.l1 = "Qui ti capisco, amico mio. Come nessun altro.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Moko_repeat";
		break;
		
		case "SharlieEpilog_Moko_repeat":
			dialog.text = "Capitano "+pchar.lastname+"... In cosa posso aiutare?";
			link.l1 = "Ti ringrazio, "+npchar.name+", per ora non ho bisogno di niente.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Moko_repeat";
		break;
		
		//Диалог с дворянином Бернардом
		case "SharlieEpilog_Bernard_1":
			dialog.text = ""+UpperFirst(GetTitle(NPChar,true))+"! Quanto sono felice di vedere almeno un volto ragionevole su questa nave. Questi... marinai... sono dei barbari.";
			link.l1 = "Al vostro posto eviterei certi toni su una nave che non è la vostra. Non so come siete arrivato ai Caraibi, ma qui, sappiate, valgono altre regole. Dovreste mostrare rispetto all’equipaggio.";
			link.l1.go = "SharlieEpilog_Bernard_2";
			PlaySound("Voice\" + LanguageGetLanguage() + "\citizen\Dvoryane-06.wav");
		break;

		case "SharlieEpilog_Bernard_2":
			dialog.text = "Rispetto? Per loro? Ma sono dei selvaggi! Io sono un nobile, "+GetTitle(NPChar,true)+", sono abituato all’ordine, al servizio, alla… civiltà! Che provino solo a contraddirmi – mio padre li…";
			link.l1 = "Tuo padre verrà a sapere che sei morto di febbre durante il viaggio. E difficilmente potrà dimostrare il contrario.";
			link.l1.go = "SharlieEpilog_Bernard_3";
		break;

		case "SharlieEpilog_Bernard_3":
			dialog.text = "Maledetto sia quel colonnello Fox! È tutta colpa sua! Per sua figlia ho attraversato l’oceano, rinunciato al comfort, sopportato quegli sguardi storti, quel cibo orribile, quel... dondolio! E ora devo pure viaggiare su una nave che non è nemmeno mia!";
			link.l1 = "Colonnello Fox…";
			link.l1.go = "SharlieEpilog_Bernard_4";
		break;

		case "SharlieEpilog_Bernard_4":
			dialog.text = "Lo conoscete, "+GetTitle(NPChar,true)+"?";
			link.l1 = "Ehm... Ho sentito parlare di lui.";
			link.l1.go = "SharlieEpilog_Bernard_5";
		break;

		case "SharlieEpilog_Bernard_5":
			dialog.text = "Beh, allora non vi siete persi molto. Quest’uomo è l’incarnazione della cieca ostinazione militare e dei pregiudizi.";
			link.l1 = "È un militare...";
			link.l1.go = "SharlieEpilog_Bernard_6";
		break;

		case "SharlieEpilog_Bernard_6":
			dialog.text = "Esatto! E questo dice tutto. Quando sono venuto a chiedere un incontro con sua figlia, sapete cosa ha fatto? Sapete? Mi ha cacciato fuori! Senza dire una parola!";
			link.l1 = "Ma voi, a quanto pare, non vi siete tirato indietro?";
			link.l1.go = "SharlieEpilog_Bernard_7";
		break;

		case "SharlieEpilog_Bernard_7":
			dialog.text = "Certo! Ho cercato di ottenere un'udienza per una settimana intera! Mi sono umiliato! Ho persino... offerto una mazzetta alle guardie! Alla fine, sono riuscito a intrufolarmi da lui, senza invito. Volevo solo parlare!";
			link.l1 = "Non credo che ne sia stato felice.";
			link.l1.go = "SharlieEpilog_Bernard_8";
		break;

		case "SharlieEpilog_Bernard_8":
			dialog.text = "Felice? Oh, ha fatto una vera scenata! Mi hanno cacciata via, proibito avvicinarmi alla residenza, confiscato la nave di mio padre, e poi hanno addirittura vietato a tutti i capitani inglesi di prendermi a bordo! Ho dovuto cercare una nave francese a Martinica... È stato un incubo.";
			link.l1 = "Sembra che l’abbiate fatto davvero arrabbiare.";
			link.l1.go = "SharlieEpilog_Bernard_9";
		break;

		case "SharlieEpilog_Bernard_9":
			dialog.text = "È sempre stato contro di me. La sua frase preferita era: 'Figlia di un ufficiale, moglie di un ufficiale'. Voi, "+GetTitle(NPChar,true)+", lui ha ritenuto una scelta molto più adatta.";
			link.l1 = "Forse, questa volta aveva anche altri motivi...";
			link.l1.go = "SharlieEpilog_Bernard_10";
		break;

		case "SharlieEpilog_Bernard_10":
			dialog.text = "...";
			link.l1 = "Quindi siete venuto qui per vedere la vostra amata.";
			link.l1.go = "SharlieEpilog_Bernard_11";
		break;

		case "SharlieEpilog_Bernard_11":
			dialog.text = "Sì. Non ho ricevuto da lei neanche una riga da quando ha lasciato l’Europa. Sono sicuro che suo padre intercetta semplicemente le lettere. Non può avermi dimenticato! Certo, era riservata con me… persino fredda… Ma non credo che mi abbia cancellato dalla sua vita.";
			link.l1 = "Le sono vicino, monsieur. Le ferite dell’anima guariscono molto più lentamente di quelle del corpo. Un momento… Perché lei, un inglese, va a Bordeaux?";
			link.l1.go = "SharlieEpilog_Bernard_12";
		break;

		case "SharlieEpilog_Bernard_12":
			dialog.text = "Non ho intenzione di tornare a casa coperto di vergogna. Dovrò fermarmi dallo zio a Bordeaux finché tutto non si sarà calmato. In fondo, la sua tenuta è molto più spaziosa ed elegante della nostra. E anche la servitù è meglio istruita.";
			link.l1 = "Ebbene, forse non è la peggiore delle soluzioni. Magari troverete anche un'altra donna degna del vostro cuore. Bordeaux è davvero ricca di giovani bellezze, potete credermi.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Bernard_repeat";
		break;
		
		case "SharlieEpilog_Bernard_repeat":
			dialog.text = "Quando finalmente arriveremo, "+GetTitle(NPChar,true)+"? Sto soffrendo terribilmente circondata da tutti questi... gentiluomini. Ho assolutamente bisogno di fare subito un bagno.";
			link.l1 = "Temo che per i prossimi due mesi non vi resterà che sognarla.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Bernard_repeat";
			PlaySound("Voice\" + LanguageGetLanguage() + "\citizen\Dvoryane-06.wav");
		break;
		
		//Диалог с Книппелем на корабле Улисс
		case "SharlieEpilog_Knippel_1":
			dialog.text = "Maledetta bonaccia, che il grappolo lo porti via.";
			link.l1 = "Non brontolare, "+npchar.name+", prima o poi il vento si alzerà.";
			link.l1.go = "SharlieEpilog_Knippel_2";
		break;

		case "SharlieEpilog_Knippel_2":
			dialog.text = "E cosa dovrei fare fino ad allora, signore? Non posso nemmeno controllare i cannoni... Siamo pur sempre su una nave che non è la nostra.";
			link.l1 = "Cerca di rilassarti un po'. Non si può lavorare sempre.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Knippel_repeat";
		break;
		
		case "SharlieEpilog_Knippel_repeat":
			dialog.text = "Maledetta bonaccia...";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Knippel_repeat";
		break;
		
		//Диалог с Лонгвэем на корабле Улисс
		case "SharlieEpilog_Longway_1":
			dialog.text = "Bel vascello, signor capitano. Anche voi la pensate così?";
			link.l1 = "Anche meglio di Meifeng?";
			link.l1.go = "SharlieEpilog_Longway_2";
		break;

		case "SharlieEpilog_Longway_2":
			dialog.text = "Per "+npchar.name+" non c'è nave migliore della Meifeng. Nessuna nave può stringere il vento come lei. ";
			link.l1 = "Tranquilla, "+npchar.name+", ma stavo scherzando. Certo, Meifeng non ha rivali. Però anche Ulisse è una buona nave. Solida.";
			link.l1.go = "SharlieEpilog_Longway_3";
		break;

		case "SharlieEpilog_Longway_3":
			dialog.text = ""+npchar.name+" voler prendere il timone. Sentire come la nave segue la mano...";
			link.l1 = "Purtroppo, amico mio, questa nave non è nostra. Meglio che tu proponga a quel gigante laggiù di allenarsi un po' nella scherma. Vi farà bene a entrambi.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Longway_repeat";
		break;
		
		case "SharlieEpilog_Longway_repeat":
			dialog.text = "A che velocità potremo andare, se il vento sarà favorevole?";
			link.l1 = "Questo non posso dirtelo con certezza, "+npchar.name+". Meglio chiedere al loro nostromo.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Longway_repeat";
		break;
		
		//Диалог с Тонзагом на корабле Улисс
		case "SharlieEpilog_Tonzag_1":
			dialog.text = "Hai visto che gigante fa da nostromo qui? Dicono che può spaccare una noce di cocco con una mano sola.";
			link.l1 = "Ah-ah. Ma vedo che tu un po' lo temi, vero?";
			link.l1.go = "SharlieEpilog_Tonzag_2";
		break;

		case "SharlieEpilog_Tonzag_2":
			dialog.text = "Perché mai? La taglia non è tutto. Ho già avuto a che fare con tipi ben peggiori.";
			link.l1 = "Forse allora gli proporrai una sfida a pugni? Uno contro uno, ad armi pari.";
			link.l1.go = "SharlieEpilog_Tonzag_3";
		break;

		case "SharlieEpilog_Tonzag_3":
			dialog.text = "Argh...";
			link.l1 = "Sei diventato pallido, eh. Ahah. Beh, se non vuoi — pazienza. Meglio risparmiare le tue ossa, che poi tanto giovani non sono più.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Tonzag_repeat";
		break;
		
		case "SharlieEpilog_Tonzag_repeat":
			dialog.text = "In queste acque il pesce abbonda, basterebbe raccoglierlo a secchiate, ma questi sfaticati nemmeno la rete si sono degnati di gettare.";
			link.l1 = "Parla con il loro nostromo. Penso che apprezzerà la tua osservazione, eh eh.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Tonzag_repeat";
		break;
		
		//Диалог с Тичингиту, охраняющим золото
		case "SharlieEpilog_Tichingitu_21":
			dialog.text = "L'oro è al sicuro, capitano "+pchar.name+". Ho incaricato Tichingitu di sorvegliarlo con attenzione.";
			link.l1 = "Grazie, amico. Alonso presto ti darà il cambio.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Tichingitu_21";
		break;
		
		//Диалог с Книппелем, охраняющим золото
		case "SharlieEpilog_Knippel_21":
			dialog.text = "Per mille cannoni, signore, su questa carretta ci sono più topi di quanti ne abbia mai visto in tutta la mia vita.";
			link.l1 = "La nave è rimasta a lungo in porto, senza la dovuta attenzione. Il nuovo equipaggio presto se ne sbarazzerà.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Knippel_21";
		break;
		
		//Диалог с Лонгвэем, охраняющим золото
		case "SharlieEpilog_Longway_21":
			dialog.text = "Longway sente il rumore della catena. Il capitano ha gettato l’ancora?";
			link.l1 = "È stato il nostro passeggero a far saltare la sicura. Il vento per ora è molto debole, ma spero che non durerà a lungo.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Longway_21";
		break;
		
		//Диалог с Тонзагом, охраняющим золото
		case "SharlieEpilog_Tonzag_21":
			dialog.text = "Sì, accidenti... Adesso non mi dispiacerebbe affatto una tazza di rum forte.";
			link.l1 = "Presto sarà ora di cena, abbi pazienza. Alonso ti darà il cambio.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Tonzag_21";
		break;
		
		//Диалог с Мэри перед походом в каюту
		case "SharlieEpilog_Mary_11":
			dialog.text = "...";
			link.l1 = ""+npchar.name+", amore mio, come ti senti?";
			link.l1.go = "SharlieEpilog_Mary_12";
			DelLandQuestMark(npchar);
		break;

		case "SharlieEpilog_Mary_12":
			dialog.text = "...";
			link.l1 = "Dai, cara, ti sei davvero offesa con me solo perché sono andato in negozio a prendere del vino?";
			link.l1.go = "SharlieEpilog_Mary_13";
		break;

		case "SharlieEpilog_Mary_13":
			dialog.text = "Al negozio a prendere del vino? Potevi almeno avvisare! Come faccio a sapere che non eri in un bordello – con qualcuna… o magari con tutte insieme?!";
			link.l1 = "Tesoro, secondo te rischierei così tanto? Ho la moglie più bella, intelligente e terribilmente gelosa di tutto l’arcipelago. Davvero pensi che potrei sprecarmi con qualche squallida ragazza da taverna?";
			link.l1.go = "SharlieEpilog_Mary_14";
		break;

		case "SharlieEpilog_Mary_14":
			dialog.text = "Potevi almeno dirmelo, giusto! Io ero lì e…";
			link.l1 = "Prometto, la prossima volta non mi limiterò ad avvisarti – ti porterò con me. Ma adesso… mi è venuta una certa curiosità: chissà se nella cabina del capitano è tutto a posto con i mobili. Soprattutto con il letto. Andiamo a controllare?";
			link.l1.go = "SharlieEpilog_Mary_15";
		break;

		case "SharlieEpilog_Mary_15":
			dialog.text = ""+pchar.name+"... E se qualcuno dovesse entrare?\nMh… adesso lo desidero ancora di più.";
			link.l1 = "Allora non perdiamo neanche un secondo.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_1");
		break;
		
		//Диалог с Элен перед походом в каюту
		case "SharlieEpilog_Helena_11":
			dialog.text = "...";
			link.l1 = ""+npchar.name+", amore, come ti senti?";
			link.l1.go = "SharlieEpilog_Helena_12";
			DelLandQuestMark(npchar);
		break;

		case "SharlieEpilog_Helena_12":
			dialog.text = "...";
			link.l1 = "Dai, cara, ti sei davvero offesa con me solo perché sono andato al negozio a prendere del vino?";
			link.l1.go = "SharlieEpilog_Helena_13";
		break;

		case "SharlieEpilog_Helena_13":
			dialog.text = "Potevi anche portarmi con te. O pensi che me la sarei cavata peggio delle tue complici?";
			link.l1 = "Penso che le avresti oscurate senza alcuna fatica. Ma allora io non penserei affatto al vino.";
			link.l1.go = "SharlieEpilog_Helena_14";
		break;

		case "SharlieEpilog_Helena_14":
			dialog.text = "E di cosa, allora?";
			link.l1 = "Di isolarmi con te proprio lì... E questo pensiero non mi dà pace proprio adesso.";
			link.l1.go = "SharlieEpilog_Helena_15";
		break;

		case "SharlieEpilog_Helena_15":
			dialog.text = "Davvero? E dove pensi di nasconderti dagli sguardi curiosi?";
			link.l1 = "Nella cabina del capitano. Direi che dovremmo testare la resistenza del suo letto.";
			link.l1.go = "SharlieEpilog_Helena_16";
		break;

		case "SharlieEpilog_Helena_16":
			dialog.text = "Ah ah. E se il capitano ci sorprendesse?\nAnche solo pensarci mi fa battere il cuore più forte.";
			link.l1 = "Allora non perdiamo tempo!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_1");
		break;
		
		//Диалог с Мэри в каюте
		case "SharlieEpilog_Mary_21":
			dialog.text = "È stato meraviglioso, mio capitano...\nHo una notizia per te.";
			link.l1 = "Novità? Sono tutto orecchi.";
			link.l1.go = "SharlieEpilog_Mary_22";
			SharlieEpilog_LoveInCabin_CameraDialog();
		break;

		case "SharlieEpilog_Mary_22":
			dialog.text = ""+pchar.name+"... Avremo un bambino. Sono incinta, giusto.";
			link.l1 = "Amore mio... È vero?";
			link.l1.go = "SharlieEpilog_Mary_23";
		break;

		case "SharlieEpilog_Mary_23":
			dialog.text = "Diventerai padre, "+pchar.name+"!";
			link.l1 = ""+npchar.name+"... È incredibile!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_6");
		break;
		
		case "SharlieEpilog_Mary_31":
			dialog.text = "Sei felice, amore mio?";
			link.l1 = "Felice? Stai scherzando? Diamine, sono l’uomo più felice del mondo! Ma… perché non me l’hai detto prima?";
			link.l1.go = "SharlieEpilog_Mary_32";
		break;

		case "SharlieEpilog_Mary_32":
			dialog.text = "Per impedire la partenza? Ho davvero voglia di conoscere tuo padre, "+pchar.name+".";
			link.l1 = ""+npchar.name+"... Ti amo!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_9");
		break;
		
		//Диалог с Элен в каюте
		case "SharlieEpilog_Helena_21":
			dialog.text = "Sei stato, come sempre, all’altezza, caro. Ho una notizia per te.";
			link.l1 = "Novità? Sono tutto orecchi.";
			link.l1.go = "SharlieEpilog_Helena_22";
			SharlieEpilog_LoveInCabin_CameraDialog();
		break;

		case "SharlieEpilog_Helena_22":
			dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+GetFullName(pchar)+", chevalier de Monpe - diventerai padre.";
			link.l1 = "È... è vero?";
			link.l1.go = "SharlieEpilog_Helena_23";
		break;

		case "SharlieEpilog_Helena_23":
			dialog.text = "È vero tanto quanto il fatto che mi chiamo "+npchar.name+".   Non più tardi di sei mesi avremo un bambino – un piccolo monsieur de Mor... o forse una mademoiselle.";
			link.l1 = "Hélène... È incredibile!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_6");
		break;
		
		case "SharlieEpilog_Helena_31":
			dialog.text = "...";
			link.l1 = "Ecco perché non hai voluto bere con noi per la partenza! Ma… perché non me l’hai detto prima?";
			link.l1.go = "SharlieEpilog_Helena_32";
		break;

		case "SharlieEpilog_Helena_32":
			dialog.text = "Avevo paura che avresti deciso di non rischiare e saresti rimasto sull’arcipelago. Volevo che tu esaudissi la richiesta di tuo padre. E poi… ci tengo davvero a conoscerlo di persona.";
			link.l1 = ""+npchar.name+"… Ti amo!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_9");
		break;
		
		// Диалог с Пикаром
		case "SharlieEpilog_PikarInCabin_1":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "Allora… E cosa stiamo facendo qui? Piccoli guasconi?";
				link.l1 = "Ah ah ah! Avrò un figlio, "+npchar.name+"!   Diventerò padre!";
				link.l1.go = "SharlieEpilog_PikarInCabin_1_1";
			}
			else
			{
				dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+pchar.lastname+". Non le sembra che usare la cabina del capitano senza il suo permesso sia un po’ troppo, anche per una persona del suo rango?";
				link.l1 = "Mi scusi, capitano. Ma ho un buon motivo! Diventerò padre!";
				link.l1.go = "SharlieEpilog_PikarInCabin_12";
			}
			SharlieEpilog_PikarInCabin_camera_2();
		break;
		
		case "SharlieEpilog_PikarInCabin_1_1":
			locCameraSleep(true);
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				StartInstantDialogTurnToNPC("Helena", "SharlieEpilog_PikarInCabin_2", "Quest\Sharlie\Epilog.c", "Blaze");
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				StartInstantDialogTurnToNPC("Mary", "SharlieEpilog_PikarInCabin_2", "Quest\Sharlie\Epilog.c", "Blaze");
			}
		break;

		case "SharlieEpilog_PikarInCabin_2":
			dialog.text = "O una figlia!";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_PikarInCabin_2_1";
		break;
		
		case "SharlieEpilog_PikarInCabin_2_1":
			StartInstantDialogTurnToNPC("SharlieEpilog_Pikar", "SharlieEpilog_PikarInCabin_3", "Quest\Sharlie\Epilog.c", "Blaze");
		break;

		case "SharlieEpilog_PikarInCabin_3":
			dialog.text = "E tu me l’hai nascosto, mascalzone? E io che ti consideravo un amico!";
			link.l1 = "L’ho appena scoperto anch’io! Riesci a crederci? Io! Diventerò! Padre!";
			link.l1.go = "SharlieEpilog_PikarInCabin_4";
		break;

		case "SharlieEpilog_PikarInCabin_4":
			dialog.text = "Ah ah ah! Ma sei davvero felice, amico mio! Non ti ho mai visto così\nBeh, voi due chiacchierate ancora un po', io intanto preparo i cannoni per la salva di festa. Fammi sapere quando sei pronto a dare l'ordine.";
			link.l1 = "...";
			link.l1.go = "exit";
			locCameraSleep(false);
			SharlieEpilog_PikarInCabin_camera_1();
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_13");
		break;

		case "SharlieEpilog_PikarInCabin_12":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				sld = CharacterFromID("Helena");
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				sld = CharacterFromID("Mary");
			}
			dialog.text = "Ah... Credetemi, avevo già intuito perché siete venuti qui.";
			link.l1 = "Ma no! "+sld.name+" sono incinta! Avrò un figlio!";
			link.l1.go = "SharlieEpilog_PikarInCabin_12_1";
		break;
		
		case "SharlieEpilog_PikarInCabin_12_1":
			locCameraSleep(true);
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				StartInstantDialogTurnToNPC("Helena", "SharlieEpilog_PikarInCabin_13", "Quest\Sharlie\Epilog.c", "Blaze");
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				StartInstantDialogTurnToNPC("Mary", "SharlieEpilog_PikarInCabin_13", "Quest\Sharlie\Epilog.c", "Blaze");
			}
		break;

		case "SharlieEpilog_PikarInCabin_13":
			dialog.text = "O una figlia!";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_PikarInCabin_13_1";
		break;
		
		case "SharlieEpilog_PikarInCabin_13_1":
			StartInstantDialogTurnToNPC("SharlieEpilog_Pikar", "SharlieEpilog_PikarInCabin_14", "Quest\Sharlie\Epilog.c", "Blaze");
		break;

		case "SharlieEpilog_PikarInCabin_14":
			dialog.text = "Ehm... Beh, vi faccio le mie più sincere congratulazioni!\nDarò ordine di sparare una salva festiva da tutti i cannoni. Avvisatemi quando sarete pronti a dare il comando.\nNel frattempo... la cabina è a vostra disposizione.";
			link.l1 = "...";
			link.l1.go = "exit";
			locCameraSleep(false);
			SharlieEpilog_PikarInCabin_camera_1();
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_13");
		break;
		
		// Диалог с Пикаром после интима с женой
		case "SharlieEpilog_PikarZalp_1":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "Ehm-ehm... Allora, papà... vedo che hai già deciso di mettere al mondo un altro erede, eh?";
				link.l1 = "Ah-ah! Se fosse per me, ne farei una dozzina in un colpo solo! Allora, amico, spariamo con tutti i cannoni?";
				link.l1.go = "SharlieEpilog_PikarZalp_2";
				link.l2 = "Temo, amico mio, che non funzioni così. Ma ci abbiamo provato.";
				link.l2.go = "exit";
			}
			else
			{
				dialog.text = ""+UpperFirst(GetTitle(NPChar,true))+"...";
				link.l1 = "Allora, capitano, facciamo fuoco con tutti i cannoni?";
				link.l1.go = "SharlieEpilog_PikarZalp_3";
				link.l2 = "Non adesso.";
				link.l2.go = "exit";
			}
			NextDiag.TempNode = "SharlieEpilog_PikarZalp_1";
		break;
		
		case "SharlieEpilog_PikarZalp_2":
			dialog.text = "L'equipaggio non aspetta altro! Date l'ordine, "+GetTitle(NPChar,true)+".";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_PikarZalp_final";
			DelLandQuestMark(npchar);
		break;
		
		case "SharlieEpilog_PikarZalp_3":
			dialog.text = "La ciurma è pronta. Date l’ordine.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_PikarZalp_final";
			DelLandQuestMark(npchar);
		break;
		
		case "SharlieEpilog_PikarZalp_final":
			dialog.text = "...";
			link.l1 = "Cannonieri! Fuoco da tutti i cannoni! Fuoco!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_ZalpInSea");
			locCameraFromToPos(-9.34, 8.28, -16.03, true, -9.33, 7.32, -20.48);
			CharacterTurnToLoc(pchar, "quest", "quest10");
			CharacterTurnToLoc(npchar, "quest", "quest10");
		break;
		
		// Диалог с отцом в поместье де Монпе
		case "SharlieEpilog_HenriDeMonper_1":
			NextMonth = GetDataMonth() + 2;
			if (NextMonth == 13) NextMonth = 1;
			else if (NextMonth == 14) NextMonth = 2;
			Month = XI_ConvertString("MonthVoc_" + NextMonth);
			dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+pchar.lastname+"... Quanto sono felice di vederti, figlio mio!";
			if (GetDataMonth() >= 4 && GetDataMonth() <= 10)
			{
				link.l1 = "Padre... Non riesco a credere di essere di nuovo a casa... Avevo quasi dimenticato com’è fatto la neve. Sembra che qui non sia cambiato proprio nulla...";
			}
			else
			{
				link.l1 = "Padre... Non posso credere di essere di nuovo a casa... Sembra che persino la neve abbia deciso di cadere per questa occasione. In "+month+". Qui non è cambiato proprio nulla...";
			}
			link.l1.go = "SharlieEpilog_HenriDeMonper_2";
			locCameraFromToPos(-8.76, 7.86, 0.75, true, -7.41, 6.11, 0.18);
			Achievment_Set("ach_CL_202");
		break;
		
		case "SharlieEpilog_HenriDeMonper_2":
			dialog.text = "E invece di te non si può dire lo stesso! Il tuo portamento, il modo in cui cammini, le cicatrici\n"+"No, davanti a me non c'è più quel ragazzino viziato che ho salutato quando partiva per terre lontane.";
			link.l1 = "Si cresce in fretta ai Caraibi, padre. Ma di questo avremo ancora tempo per parlare. Piuttosto, ditemi, come state? Spero che la malattia sia regredita, visto che siete qui davanti a me in tutto il vostro splendore.";
			link.l1.go = "SharlieEpilog_HenriDeMonper_3";
		break;
		
		case "SharlieEpilog_HenriDeMonper_3":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				dialog.text = "Ahimè, "+pchar.name+", lei si è solo aggrappata ancora più forte alla mia gola. Ma potevo forse incontrare il mio amato figlio in un abito qualunque? Per me è un giorno grandioso, "+pchar.name+"\n"+"Mi sa che dovresti presentarmi a qualcuno.";
				link.l1 = "...";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("SharlieEpilog_InEstateDeMonpe_10");
			}
			else
			{
				dialog.text = "Ahimè, "+pchar.name+",   la sua presa con gli anni si fa solo più forte.   Ma potevo forse incontrare il mio amato figlio in un abito qualunque?   Per me questo è un giorno grandioso, "+pchar.name+"\n"+"Vedo che non sei arrivato da solo\n"+"Devi essere affamato dopo il viaggio? Suzanne ha preparato il fegato d’oca secondo la tua ricetta preferita!\n"+"Accomodati a tavola – così ci presenterai lungo la strada!";
				link.l1 = "Devo ammettere, ho sentito questo profumo già avvicinandomi alla tenuta!";
				link.l1.go = "SharlieEpilog_HenriDeMonper_8"; // заходят в поместье
			}
		break;
		
		case "SharlieEpilog_HenriDeMonper_4":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = CharacterFromID("Helena");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld = CharacterFromID("Mary");
			dialog.text = "...";
			link.l1 = "Padre, permettetemi di presentarvi mia moglie - "+sld.name+" "+pchar.lastname+". "+sld.name+", questo è mio padre - lo chevalier "+GetCharacterName("Henri")+" "+GetCharacterName("de Monper")+".";
			link.l1.go = "SharlieEpilog_HenriDeMonper_5";
			SharlieEpilog_InEstateDeMonpe_11_1();
		break;
		
		case "SharlieEpilog_HenriDeMonper_5":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				sld = CharacterFromID("Helena");
				dialog.text = ""+pchar.name+", sono incantato! La tua prescelta non assomiglia affatto a una viziata dama di società, come quelle a cui siamo abituati qui. Oso supporre che sappia manovrare una nave con la stessa sicurezza con cui ha conquistato il cuore di mio figlio.";
				link.l1 = "...";
				link.l1.go = "SharlieEpilog_HenriDeMonper_Helena_1";
				CharacterTurnByChr(npchar, sld);
			}
			else
			{
				sld = CharacterFromID("Mary");
				dialog.text = "Per me è una grande gioia fare la vostra conoscenza, madame. Vi assicuro che mio figlio ha un gusto eccellente!";
				link.l1 = "...";
				link.l1.go = "SharlieEpilog_HenriDeMonper_Mary_1";
				CharacterTurnByChr(npchar, sld);
			}
		break;
		
		case "SharlieEpilog_HenriDeMonper_Helena_1":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_HenriDeMonper_Helena_1");
		break;
		
		case "SharlieEpilog_HenriDeMonper_Helena_2":
			dialog.text = "Sono lusingata, chevalier! Avete ragione, so davvero tenere il timone anche nella tempesta più feroce. Tuttavia, per quanto riguarda il cuore di vostro figlio – non c’è bisogno di governarlo. Siamo uniti nei nostri intenti e desideri.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_HenriDeMonper_Helena_2_1";
			SharlieEpilog_InEstateDeMonpe_11_2();
		break;
		
		case "SharlieEpilog_HenriDeMonper_Helena_2_1":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_HenriDeMonper_Helena_2_1");
		break;
		
		case "SharlieEpilog_HenriDeMonper_Helena_3":
			dialog.text = "L'abate Benoît vi ha descritto come una donna saggia e coraggiosa – e sembra che non abbia esagerato. Sono felice che "+pchar.name+" ho trovato in te non solo una moglie, ma anche una compagna che mi è pari nello spirito\n"+"Devi essere affamato dopo il viaggio? Suzanne ha preparato il fegato d’oca secondo la tua ricetta preferita!\n"+"Ebbene, vi invito tutti a tavola! E spero che, strada facendo, avremo modo di conoscerci meglio.";
			link.l1 = "Devo ammettere, ho sentito questo profumo già avvicinandomi alla tenuta!";
			link.l1.go = "SharlieEpilog_HenriDeMonper_6";
			SharlieEpilog_InEstateDeMonpe_11_1();
		break;
		
		case "SharlieEpilog_HenriDeMonper_Mary_1":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_HenriDeMonper_Mary_1");
		break;
		
		case "SharlieEpilog_HenriDeMonper_Mary_2":
			dialog.text = "È un piacere conoscervi, chevalier! "+pchar.name+" mi ha parlato molto di voi, e vi immaginavo proprio così, giusto!";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_HenriDeMonper_Mary_2_1";
			CharacterTurnByChr(pchar, npchar);
			SharlieEpilog_InEstateDeMonpe_11_2();
		break;
		
		case "SharlieEpilog_HenriDeMonper_Mary_2_1":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_HenriDeMonper_Mary_2_1");
		break;
		
		case "SharlieEpilog_HenriDeMonper_Mary_3":
			sld = CharacterFromID("Mary");
			dialog.text = ""+pchar.name+", sono incantato! La tua prescelta non somiglia affatto alle dame ingioiellate dell’alta società – ed è proprio questa la sua vera virtù\n"+"Mi sembra che tu abbia scelto una splendida rosa invece di delicate e capricciose gigli.";
			link.l1 = "La rosa selvatica, padre… "+sld.name+"  - un vero tesoro. Sono certo che sarete d'accordo con me, quando la conoscerete meglio.";
			link.l1.go = "SharlieEpilog_HenriDeMonper_Mary_4";
			SharlieEpilog_InEstateDeMonpe_11_1();
		break;
		
		case "SharlieEpilog_HenriDeMonper_Mary_4":
			if (GetAttributeInt(pchar, "questTemp.SharlieEpilog_Friends") >= 2) sStr = "ты познакомишь меня с остальными";
			else sStr = "ты представишь меня нашему гостю";
			dialog.text = "Allora non rimandiamo oltre questo momento! Dovete essere affamati dopo il viaggio, vero? Suzanne ha preparato il fegato d’oca secondo la tua ricetta preferita!\n"+"Vi prego, tutti a tavola! E spero che, strada facendo, "+sStr+"";
			link.l1 = "Devo ammettere, ho sentito questo profumo già avvicinandomi alla tenuta!";
			link.l1.go = "SharlieEpilog_HenriDeMonper_6";
			CharacterTurnByChr(CharacterFromID("HenriDeMonper"), pchar);
		break;
		
		case "SharlieEpilog_HenriDeMonper_6":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_InEstateDeMonpe_14");
		break;
		
		case "SharlieEpilog_HenriDeMonper_7":
			dialog.text = "...";
			link.l1 = "Tesoro, devi assolutamente assaggiarlo – niente può competere con il fegato d’oca preparato secondo la nostra ricetta di famiglia! L’abbiamo ereditata dal nonno – e a lui l’avevano portata in dono da un paese del Mediterraneo.";
			link.l1.go = "SharlieEpilog_HenriDeMonper_8"; // заходят в поместье
			SharlieEpilog_InEstateDeMonpe_11_1();
		break;
		
		case "SharlieEpilog_HenriDeMonper_8":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_InEstateDeMonpe_15");
		break;
		
		// диалог на ужине в поместье де Монпе
		case "SharlieEpilog_InKitchenDeMonpe":
			dialog.text = "";
			link.l1 = "Non vorrei iniziare il banchetto con tristezza, ma come famiglia dobbiamo ricordare chi ci ha lasciato prima di noi. Vi chiedo di alzare i calici per Michel. Che il Signore conceda pace alla sua anima.";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_2";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_2":
			dialog.text = "";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_3";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_3":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				if (GetAttributeInt(pchar, "questTemp.SharlieEpilog_Friends") >= 2) sStr = "добрых друзей";
				else sStr = "соратника";
				dialog.text = "";
				link.l1 = "Ho così tante domande da farti, "+pchar.name+"... Ma prima lascia che ascolti tua moglie e "+sStr+". Vi prego, raccontate come avete conosciuto Charles.";
			}
			else
			{
				if (GetAttributeInt(pchar, "questTemp.SharlieEpilog_Friends") >= 2) sStr = "твоих добрых друзей";
				else sStr = "твоего друга";
				dialog.text = "";
				link.l1 = "Devo chiederti così tante cose, "+pchar.name+"... Ma prima permettimi di ascoltare "+sStr+". Vi prego, raccontateci come avete conosciuto Charles.";
			}
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_4";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		// if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
		
		case "SharlieEpilog_InKitchenDeMonpe_4":
			dialog.text = "";
			link.l1 = "Non vedo l'ora di ascoltarlo, proprio come voi!";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_5";
			}
			else if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_6";
			}
			else if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7";
			}
			else
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_8";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_5":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				link.l1 = "Ero in pericolo di morte... "+pchar.name+",   da vero gentiluomo, non ha permesso che accadesse nulla di male! Mi ha difesa e ha sistemato quei furfanti, giusto?";
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l1 = ""+pchar.name+" mi hai strappata dalle mani di un inglese spregevole che aveva osato... rapirmi. Se fossi arrivato anche solo un'ora più tardi, non ci saremmo mai conosciuti.";
			}
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_5_1";
			SharlieEpilog_InKitchenDeMonpe_camera_Wife();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_5_1":
			dialog.text = "";
			link.l1 = "Non avevo dubbi che si sarebbe comportato come si addice a un vero gentiluomo. L’onore non è solo una parola per la nostra famiglia. Sono fiero di te, figlio mio.";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_6";
			}
			else if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7";
			}
			else
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_8";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_6":
			sld = CharacterFromID("Tichingitu");
			dialog.text = "";
			link.l1 = ""+sld.name+" entrare nella casa dei visi pallidi per trovare del cibo. Il viso pallido sorprendere "+sld.name+" - e mandarlo in prigione. Capitano "+pchar.name+" venire, salvare "+sld.name+" dalla prigione. Da allora "+sld.name+" servire il capitano "+pchar.name+" e rimanere fedele fino all’ultimo respiro.";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_6_1";
			SharlieEpilog_InKitchenDeMonpe_camera_Tichingitu();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_6_1":
			sld = CharacterFromID("Tichingitu");
			dialog.text = "";
			link.l1 = "È confortante sapere che mio figlio non è solo un nobile gentiluomo, ma anche una persona dal cuore generoso. Sono felice che accanto a lui ci siano amici leali come voi, "+sld.name+".";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7";
			}
			else
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_8";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_7":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel"))
			{
				link.l1 = "Un giorno il Capitano è venuto a casa mia in cerca di lavoro. Gli ho affidato un incarico, e lui l’ha svolto come si deve. È piaciuto al capo, che ha iniziato a coinvolgerlo sempre di più nei suoi affari, mentre a me ha ordinato di andare sulla sua nave – per tenerlo d’occhio… E poi questo… signore, silenzioso come un’ombra, ha mollato gli ormeggi, accidenti a lui, ed è sparito dall’arcipelago senza dire una parola al Capitano. L’ha lasciato solo a sbrogliare il pasticcio che lui stesso aveva combinato. Ho offerto al Capitano il mio aiuto e, anche se Richard si è comportato da vero bastardo, accidenti a lui, il Capitano non mi ha mandato via.";
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7_2";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway"))
			{
				link.l1 = "Longwei e il signor capitano lavoravano per la stessa persona. Ma quella persona ha tradito Longwei. Allora Longwei ha deciso: non servirà più quell’uomo. Il signor capitano mi ha preso sulla sua nave come ufficiale, e ha fatto moltissimo per Longwei.";
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7_2";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1 = "Ci siamo incontrati per la prima volta nella taverna di Bridgetown: "+pchar.name+" lui cercava un affare, io - un esecutore affidabile. Quell'incontro fu solo l'inizio: da lì gli eventi intrecciarono i nostri destini. Sono diventato il suo ufficiale, e ora, senza esitazione, posso chiamarlo amico - una persona per cui sarei pronto a rischiare la vita.";
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7_2";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Gambitnik();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_7_2":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel"))
			{
				link.l1 = "Riuscire a vedere la persona oltre le circostanze è una dote rara. Questo, direi, dimostra che mio figlio non è privo di buon senso.";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway"))
			{
				link.l1 = "Sono felice che mio figlio non sia un militare senz’anima, ma un vero comandante, capace di prendersi cura dei suoi compagni.";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1 = "Non si sentono tutti i giorni parole come queste. Direi che questa è la prova migliore che mio figlio non è solo un abile marinaio, ma anche un buon amico.";
			}
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_8";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_8":
			dialog.text = "";
			link.l1 = "Ci siamo conosciuti a Bordeaux. Il capitano è salito a bordo della nostra nave come passeggero e lo abbiamo portato a Martinica. Da allora – e fino alla partenza per qui – sono rimasto la voce del suo equipaggio e ho osservato come "+GetFullName(pchar)+" passo dopo passo è diventato ciò che è ora.";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_8_1";
			SharlieEpilog_InKitchenDeMonpe_camera_Alonso();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_8_1":
			dialog.text = "";
			link.l1 = "Quindi conoscete Charles ancora come quel ragazzo insopportabile che, su mia insistenza, lasciò la casa di famiglia? Suppongo, monsieur, che avremo di che parlare.";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_9";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_9":
			dialog.text = "";
			link.l1 = "Mio caro "+pchar.name+", hai percorso una lunga e gloriosa strada... Sei partito per la selvaggia savana in cerca solo di una pelle di coniglio, ma hai affrontato un leone e sei tornato trionfante, portando la sua pelle sulle spalle. Ora, come mai prima d’ora, sono tranquillo per il destino della nostra tenuta e di tutte le nostre terre.";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_10";
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_10":
			dialog.text = "";
			link.l1 = "Non vedo l’ora di affidarti al più presto le redini di tutti gli affari della nostra famiglia. Ci sarà molto da fare, ma credo che il Signore stesso vegli su di te con la Sua benedizione, e che tu possa non solo custodire l’eredità che ti è stata affidata, ma anche accrescere l’onore e la prosperità della famiglia de Monpe.";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_11";
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_11": //выбор Шарля
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l1 = "Per me è un grande onore essere vostro figlio e vostro erede. Sarà per me una gioia prendermi cura della nostra famiglia. Sono certo che mia moglie sarà per me un sostegno fedele. Prometto di fare tutto il possibile per rendere ancora più illustre il nostro casato... E il primo contributo alla sua prosperità sarà la nascita di un figlio!";
				link.l1.go = "SharlieEpilog_ChooseEstate_HaveWife_1";
			}
			else
			{
				link.l1 = "Per me è un grande onore essere vostro figlio ed erede. Sarà per me una gioia prendermi cura della nostra famiglia e prometto di fare tutto il possibile per rendere il nostro nome ancora più illustre.";
				link.l1.go = "SharlieEpilog_ChooseEstate_Single_1";
			}
			link.l2 = "Padre, gli anni nel Nuovo Mondo mi hanno cambiato. Temo di non riuscire più a riconciliarmi con il ritmo tranquillo della vita qui, in Europa.";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l2.go = "SharlieEpilog_ChooseCaribbean_HaveWife_1";
			}
			else
			{
				link.l2.go = "SharlieEpilog_ChooseCaribbean_Single_1";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		// --> Выбрал остаться в поместье с женой
		case "SharlieEpilog_ChooseEstate_HaveWife_1":
			dialog.text = "";
			link.l1 = ""+pchar.name+", davvero...";
			link.l1.go = "SharlieEpilog_HaveWife_12";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
			pchar.questTemp.SharlieEpilog_ChooseEstate = true;
		break;
		
		case "SharlieEpilog_HaveWife_12":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = CharacterFromID("Helena");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld = CharacterFromID("Mary");
			dialog.text = "";
			link.l1 = "Sì, padre. "+sld.name+" incinta.";
			link.l1.go = "SharlieEpilog_HaveWife_13";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_HaveWife_13":
			dialog.text = "";
			link.l1 = "Queste sono davvero notizie straordinarie, mio caro figlio! Il Signore ha ascoltato le mie preghiere! Che tutti qui presenti siano testimoni: in onore del neonato darò il più grande ballo che la nostra tenuta abbia mai visto! Alziamo i calici – al nostro erede!";
			link.l1.go = "SharlieEpilog_HaveWife_14";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_HaveWife_14":
			dialog.text = "";
			link.l1 = "O magari un’erede!";
			link.l1.go = "SharlieEpilog_HaveWife_15";
			SharlieEpilog_InKitchenDeMonpe_camera_Wife();
		break;
		
		case "SharlieEpilog_HaveWife_15":
			dialog.text = "";
			link.l1 = "Per un nuovo capitolo nella storia della nostra famiglia!";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
			{
				link.l1.go = "SharlieEpilog_HaveWife_16";
			}
			else if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_HaveWife_17";
			}
			else
			{
				link.l1.go = "SharlieEpilog_HaveWife_18";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_HaveWife_16":
			dialog.text = "";
			link.l1 = "Per il futuro guerriero o la brava figlia!";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_HaveWife_17";
			}
			else
			{
				link.l1.go = "SharlieEpilog_HaveWife_18";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Tichingitu();
		break;
		
		case "SharlieEpilog_HaveWife_17":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel"))
			{
				link.l1 = "Alla salute robusta del neonato!";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway"))
			{
				link.l1 = "Per il caso che vi ha fatto incontrare!";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1 = "Per il luminoso futuro della vostra famiglia!";
			}
			link.l1.go = "SharlieEpilog_HaveWife_18";
			SharlieEpilog_InKitchenDeMonpe_camera_Gambitnik();
		break;
		
		case "SharlieEpilog_HaveWife_18":
			dialog.text = "";
			link.l1 = "Per il futuro Alonso de Mor o la piccola Alonsita de Mor!";
			link.l1.go = "SharlieEpilog_HaveWife_19";
			SharlieEpilog_InKitchenDeMonpe_camera_Alonso();
		break;
		
		case "SharlieEpilog_HaveWife_19":
			dialog.text = "";
			link.l1 = "Ah-ah-ah!";
			link.l1.go = "SharlieEpilog_HaveWife_20";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_HaveWife_20":
			dialog.text = "";
			link.l1 = "Ah-ah!";
			link.l1.go = "SharlieEpilog_HaveWife_21";
			SharlieEpilog_InKitchenDeMonpe_camera_Wife();
		break;
		
		case "SharlieEpilog_HaveWife_21":
			dialog.text = "";
			link.l1 = "Ah ah ah!";
			link.l1.go = "SharlieEpilog_toast";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_toast":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_toast");
		break;
		// <-- Выбрал остаться в поместье с женой
		
		// --> Выбрал остаться в поместье будучи холостяком
		case "SharlieEpilog_ChooseEstate_Single_1":
			dialog.text = "";
			link.l1 = "Per me è un grande onore essere vostro figlio ed erede. Sarà per me una gioia prendermi cura della nostra famiglia e vi prometto che farò tutto il possibile per rendere il nostro nome ancora più glorioso.";
			link.l1.go = "SharlieEpilog_ChooseEstate_Single_2";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
			pchar.questTemp.SharlieEpilog_ChooseEstate = true;
		break;
		
		case "SharlieEpilog_ChooseEstate_Single_2":
			dialog.text = "";
			link.l1 = "Dimmi, "+pchar.name+", hai riflettuto sulla mia proposta di unirti in matrimonio con Yvonne?";
			link.l1.go = "SharlieEpilog_Single_13";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_Single_13":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_ChooseCaribbean"))
			{
				link.l1 = "Lo ammetto, padre… Yvonne non mi è mai stata davvero cara. Ma nel Nuovo Mondo non mancano ragazze splendide. Vi prometto: quando ne incontrerò una degna, non esiterò.";
			}
			else
			{
				link.l1 = "Lo ammetto, padre… Yvonne non mi è mai stata davvero cara. Ma in Francia non mancano ragazze meravigliose. Vi prometto: quando ne incontrerò una degna, non esiterò.";
			}
			link.l1.go = "SharlieEpilog_Single_14";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_Single_14":
			dialog.text = "";
			link.l1 = "Mi piace il tuo spirito, mio caro figlio. Alziamo i calici – a te, alle tue imprese e a un degno ritorno a casa!";
			link.l1.go = "SharlieEpilog_Single_15";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_Single_15":
			dialog.text = "";
			link.l1 = "Agli amici leali, senza i quali nel Nuovo Mondo non si sopravvive!";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
			{
				link.l1.go = "SharlieEpilog_Single_16";
			}
			else if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_Single_17";
			}
			else
			{
				link.l1.go = "SharlieEpilog_Single_18";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_Single_16":
			dialog.text = "";
			link.l1 = "Per il grande cuore del capitano Charles!";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_Single_17";
			}
			else
			{
				link.l1.go = "SharlieEpilog_Single_18";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Tichingitu();
		break;
		
		case "SharlieEpilog_Single_17":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel"))
			{
				link.l1 = "Alla ferrea volontà del capitano!";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway"))
			{
				link.l1 = "Alla saggezza del signor capitano!";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1 = "Per la dedizione alla causa!";
			}
			link.l1.go = "SharlieEpilog_Single_18";
			SharlieEpilog_InKitchenDeMonpe_camera_Gambitnik();
		break;
		
		case "SharlieEpilog_Single_18":
			dialog.text = "";
			link.l1 = "Per la capacità di cavarsela sempre!";
			link.l1.go = "SharlieEpilog_toast";
			SharlieEpilog_InKitchenDeMonpe_camera_Alonso();
		break;
		// <-- Выбрал остаться в поместье будучи холостяком
		
		// Шарль губернатор разговаривает с зелёным капитаном
		case "SharlieEpilog_GreenCaptain":
			dialog.text = "";
			link.l1 = "Ho sentito che avete chiesto con grande insistenza un’udienza. Allora, cosa vi serve dal governatore della Martinica?";
			link.l1.go = "SharlieEpilog_GreenCaptain_1";
			locCameraFromToPos(-1.80, 3.84, -9.08, true, -2.38, 2.21, -7.33);
			PlaySound("Voice\" + LanguageGetLanguage() + "\officer_common_2.wav");
		break;
		
		case "SharlieEpilog_GreenCaptain_1":
			dialog.text = "Voglio parlare del lavoro a beneficio della corona di Francia.";
			link.l1 = "Sì, ho un incarico per voi che richiederà la massima prontezza e anche una certa abilità nel combattimento navale. Siete pronti a dimostrare di che pasta siete fatti?";
			link.l1.go = "SharlieEpilog_GreenCaptain_2";
		break;

		case "SharlieEpilog_GreenCaptain_2":
			dialog.text = "Vostra Eccellenza, potreste spiegare più in dettaglio l'essenza dell'incarico che ci attende?";
			link.l1 = "Certo. Dovete trovare il corriere spagnolo chiamato 'Santa Esperanza', abbordarlo e portarmi i documenti che troverete nella cabina del capitano. La nave che vi ho indicato passerà vicino a Trinidad tra circa dodici giorni.";
			link.l1.go = "SharlieEpilog_GreenCaptain_3";
		break;

		case "SharlieEpilog_GreenCaptain_3":
			dialog.text = "Va bene, mi occuperò di questo incarico. E quali documenti devo cercare?";
			link.l1 = "La corrispondenza postale. Lì, tra le altre cose, ci saranno dei documenti molto importanti per me. Ma non serve che rovistiate tra le carte, consegnatemi semplicemente tutto il pacco così com’è. Per questo servizio vi pagherò quindicimila pesos... Dunque, vi aspetto nella mia residenza con il risultato del vostro lavoro.";
			link.l1.go = "SharlieEpilog_GreenCaptain_4";
		break;

		case "SharlieEpilog_GreenCaptain_4":
			dialog.text = "Suppongo di non farvi attendere troppo a lungo, Vostra Altezza.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_GuberOnMartinique_5");
		break;
		
		//Шарль разговаривает с комендантом форта
		case "SharlieEpilog_KomendantFort":
			dialog.text = "Vostra Eccellenza... Permettete che riferisca?";
			link.l1 = "Fate rapporto, "+GetAddress_Form(NPChar)+" "+npchar.lastname+".";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) link.l1.go = "SharlieEpilog_KomendantFort_1";
			else link.l1.go = "SharlieEpilog_KomendantFort_2";
			PlaySound("Voice\" + LanguageGetLanguage() + "\military02.wav");
		break;
		
		case "SharlieEpilog_KomendantFort_1":
			dialog.text = "Ehm-ehm...";
			link.l1 = "Parlate pure. Non ho segreti davanti a mia moglie.";
			link.l1.go = "SharlieEpilog_KomendantFort_2";
		break;
		
		case "SharlieEpilog_KomendantFort_2":
			dialog.text = "La ricognizione riferisce: da Willemstad è salpata una squadra navale. In testa c’è la nave di linea di secondo rango ‘Gouden Leeuw’, un vero mostro dei mari. La potenza complessiva della squadra supera i duecentocinquanta cannoni e conta più di millecinquecento soldati. Il loro obiettivo è Saint-Pierre.";
			link.l1 = "Hm... Quindi praticamente non abbiamo tempo per prepararci.";
			link.l1.go = "SharlieEpilog_KomendantFort_3";
		break;

		case "SharlieEpilog_KomendantFort_3":
			dialog.text = "Come intendiamo procedere, signor governatore?";
			link.l1 = "Abbiamo alcune navi alla fonda, pronte a colpire il nemico alle spalle...";
			link.l1.go = "SharlieEpilog_KomendantFort_4";
		break;

		case "SharlieEpilog_KomendantFort_4":
			dialog.text = "Avete intenzione di colpirli da due lati?";
			link.l1 = "Esatto. Il forte attirerà il fuoco su di sé. E quando calerà la notte, la squadra al mio comando attaccherà dal mare. Distrarremo la loro attenzione, e allora dal porto partiranno i brulotti, carichi di pece e assi. Della loro flotta non resterà nemmeno una scheggia.";
			link.l1.go = "SharlieEpilog_KomendantFort_5";
		break;

		case "SharlieEpilog_KomendantFort_5":
			dialog.text = "Un piano eccellente, Vostra Altezza! Permettete che dia l’ordine di iniziare i preparativi?";
			link.l1 = "Iniziate. E che il Signore sia con noi.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_GuberOnMartinique_11");
		break;
		
		// Стражник вызывает Алонсо
		case "SharlieEpilog_Guard":
			dialog.text = "";
			link.l1 = "Guardie, chiamate Alonso.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_AlonsoArrive");
		break;
		
		//Шарль разговаривает с Алонсо после коменданта
		case "SharlieEpilog_Alonso35":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")))
			{
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = CharacterFromID("Helena");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld = CharacterFromID("Mary");
				dialog.text = "Signor Governatore...";
				link.l1 = ""+npchar.name+", una squadra olandese arriverà qui da un giorno all'altro e inizierà l'assedio. Ascolta l'ordine: prendi Philippe e "+sld.name+", e conducili subito dall’abate. Che raduni tutte le donne, i bambini e gli anziani e si occupi della loro sicurezza.";
				link.l1.go = "SharlieEpilog_Alonso36_Wife";
				break;
			}
			dialog.text = "Signor Governatore...";
			link.l1 = ""+npchar.name+", una squadra olandese arriverà qui da un giorno all'altro e assedierà la città. Di' all'abate di radunare tutte le donne, i bambini e gli anziani, e di occuparsi della loro sicurezza. Quanto a te, ho intenzione di affidarti il comando di una nave incendiaria. I dettagli dopo. Prima di tutto dobbiamo proteggere i civili.";
			link.l1.go = "SharlieEpilog_Alonso37";
		break;

		case "SharlieEpilog_Alonso36_Wife":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = CharacterFromID("Helena");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld = CharacterFromID("Mary");
			dialog.text = "Non credo che "+sld.name+" accetterà di unirsi alle altre donne. Si sta consumando dalla noia.";
			link.l1 = "Hmm... Allora dille di prepararsi alla battaglia. Anche tu non resterai con le mani in mano: comanderai il brulotto. I dettagli dopo. Ora — prenditi cura di mio figlio.";
			link.l1.go = "SharlieEpilog_Alonso37";
		break;
		
		case "SharlieEpilog_Alonso37":
			dialog.text = "Sarà un onore! Permettete che mi metta all’opera?";
			link.l1 = "Ti do il permesso. Agisci. Ogni secondo conta per noi.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_GuberOnMartinique_13");
		break;
		// --> Выбрал отправиться назад на Карибы с женой
		case "SharlieEpilog_ChooseCaribbean_HaveWife_1":
			dialog.text = "";
			link.l1 = "Ebbene... Devo ammettere che mi aspettavo questa risposta – eppure speravo in qualcosa di diverso. Ma rispetto la tua scelta e non cercherò di convincerti oltre.";
			link.l1.go = "SharlieEpilog_ChooseCaribbean_HaveWife_2";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
			pchar.questTemp.SharlieEpilog_ChooseCaribbean = true;
		break;
		
		case "SharlieEpilog_ChooseCaribbean_HaveWife_2":
			dialog.text = "";
			link.l1 = "Capisco di avervi deluso. Ma ho una notizia per voi che, spero, farà dimenticare tutto ciò che è stato detto prima.";
			link.l1.go = "SharlieEpilog_ChooseCaribbean_HaveWife_3";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_ChooseCaribbean_HaveWife_3":
			dialog.text = "";
			link.l1 = "Sono tutto orecchi.";
			link.l1.go = "SharlieEpilog_ChooseCaribbean_HaveWife_4";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_ChooseCaribbean_HaveWife_4":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = CharacterFromID("Helena");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld = CharacterFromID("Mary");
			dialog.text = "";
			link.l1 = "Ho intenzione di fermarmi qui almeno per un anno. "+sld.name+" nella sua condizione il rollio è controindicato.";
			link.l1.go = "SharlieEpilog_ChooseCaribbean_HaveWife_5";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_ChooseCaribbean_HaveWife_5":
			dialog.text = "";
			link.l1 = ""+pchar.name+", davvero...";
			link.l1.go = "SharlieEpilog_HaveWife_12";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		// <-- Выбрал отправиться назад на Карибы с женой
		
		// --> Выбрал отправиться назад на Карибы один
		case "SharlieEpilog_ChooseCaribbean_Single_1":
			dialog.text = "";
			link.l1 = "Ebbene... Devo ammettere, mi aspettavo che avresti detto così – eppure speravo in una risposta diversa. Ma rispetto la tua scelta e non cercherò di convincerti. Però, dimmi, "+pchar.name+", hai riflettuto sulla mia proposta di unirti in matrimonio con Yvonne?";
			link.l1.go = "SharlieEpilog_Single_13";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
			pchar.questTemp.SharlieEpilog_ChooseCaribbean = true;
		break;
		// <-- Выбрал отправиться назад на Карибы один
		
		//Диалог Шарль и Мишеля на Рифе Скелета
		case "SharlieEpilog_Mishelle_1":
			dialog.text = "Non sei riuscito a fermarti, vero?";
			link.l1 = "Tu?! È un sogno?";
			link.l1.go = "SharlieEpilog_Mishelle_2";
			SharlieEpilog_OnReefs_6();
			PlaySound("Voice\" + LanguageGetLanguage() + "\sharlie\mishelle-04.wav");
		break;

		case "SharlieEpilog_Mishelle_2":
			dialog.text = "La sete di guadagno facile, il potere, l’illusione dell’invulnerabilità… Cos’è che ti ha rovinato, fratello? Cosa ha ottenebrato la tua mente, come ottenebra le menti di tutti i visi pallidi?";
			link.l1 = "Vattene! Sei solo un fantasma! Non esisti qui!";
			link.l1.go = "SharlieEpilog_Mishelle_3";
		break;

		case "SharlieEpilog_Mishelle_3":
			dialog.text = "Non hai ancora capito? Spectra sunt memoria peccatorum. Sei tu il fantasma... La leggenda dei Caraibi parla di un uomo divorato dall’avidità e da una vanità cieca. Quanti ne hai uccisi per l’oro, "+pchar.name+"?";
			link.l1 = "Ebbene, caro fratello, non mi dispiace ucciderti una seconda volta! Te la sei cercata tu!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_OnReefs_9");
		break;
		
		
		
		
		
	}
}
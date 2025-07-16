// Арчибальд Колхаун
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Vi serve qualcosa, messere?";
			link.l1 = "No, niente.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "portroyal":
			dialog.text = "Ah, Monsieur de Maure!  Benvenuto a Port Royal!  Mi riconoscete ancora?";
			link.l1 = "Hmm... Siete voi il signor Calhoun, vero? Henry Calhoun?";
			link.l1.go = "portroyal_1";
		break;
		
		case "portroyal_1":
			dialog.text = "Quasi... Archibald Calhoun.";
			link.l1 = "Oh, perdonatemi, Monsieur. Sì, ora vi ricordo. Ci siamo incontrati a Capo Catoche, nella baia. Il vostro capitano era con voi, William Patterson. Ho riconosciuto la sua squadra.";
			link.l1.go = "portroyal_2";
		break;
		
		case "portroyal_2":
			dialog.text = "Assolutamente giusto! Vi prego di scusare il mio capitano. È sempre scontroso con chi non conosce. Avete fatto un ottimo lavoro, prendendo d'assalto il forte di Diego de Montoya, proprio mentre noi stavamo per mostrare gli artigli...";
			link.l1 = "Per amor della giustizia, aggiungo, se non fosse stato per le astuzie del vostro capitano, dubito che sarei riuscito ad avventurarmi tra i bottini sotto la grandine dei cannoni spagnoli. Il vostro comandante ha trovato ciò che cercava?";
			link.l1.go = "portroyal_3";
		break;
		
		case "portroyal_3":
			dialog.text = "Sì. S’è infilato ben bene nei sotterranei sotto il forte e ha scovato una specie d’archivio. Era felice come un pascià, non ti dico. A proposito, se posso permettermi, cosa ti ha punto per assaltare quel dannato forte nella giungla?";
			link.l1 = "Dopo aver subito la mia sconfitta a Saint-Pierre, don Diego ha cominciato a tramare, finché non ha osato lanciarsi in un attacco aperto contro Cuba. Poi ha interrotto la battaglia e s’è dato alla macchia verso la terraferma. Beh, ho deciso di farla finita con quel cane codardo una volta per tutte, così non infangherà mai più il nome dei Francesi.";
			link.l1.go = "portroyal_4";
		break;
		
		case "portroyal_4":
			dialog.text = "Eh già, ho sentito un bel po' di storie leggendarie sulle gesta dell’eroico Capitano Charles de Maure. Ora le ho viste coi miei stessi occhi...";
			link.l1 = "Già, ho sentito anch’io qualche storia sul valore di William Paterson. Sei fortunato ad avere un capitano del genere.";
			link.l1.go = "portroyal_5";
		break;
		
		case "portroyal_5":
			dialog.text = "Che fortuna la mia, davvero. Anche se ormai è diventato un uomo così importante, tutto salotti, udienze, balli, parate e festini privati... Non lo si tira fuori dal palazzo del governatore nemmeno se scoppia l’inferno ogni volta che mettiamo piede a Port Royal. In verità, pure adesso è rintanato lì.\nCapitano Charles de Maure, vorresti fare un piacere a uno scozzese ubriacone? Unisciti alla mia ciurma e facciamo due chiacchiere! Non ne posso più di vedere sempre le stesse facce, e tu mi sembri uno di compagnia. Vieni da me, rilassiamoci e svuotiamo una botte di ottimo whiskey. L'offerta è mia!";
			link.l1 = "Hm... Allettante, ma...";
			link.l1.go = "portroyal_6";
		break;
		
		case "portroyal_6":
			dialog.text = "Oh, su via, Capitano, anche voi dovete riposarvi ogni tanto. A proposito, ho preso degli stuzzichini squisiti, freschi freschi dal negozio del mercante locale. Ho affittato una stanza proprio sopra il negozio. Quando vi viene fame o sete, vi basta scendere le scale e tutto è pronto, ahah! Comodo, vero? Allora, andiamo!";
			link.l1 = "Mi hai proprio convinto!";
			link.l1.go = "portroyal_7";
		break;
		
		case "portroyal_7":
			dialog.text = "Perfetto. Seguimi!";
			link.l1 = "...";
			link.l1.go = "portroyal_8";
		break;
		
		case "portroyal_8":
			DialogExit();
			NextDiag.CurrentNode = "portroyal_9";
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload6_back", "PortRoyal_store", "goto", "goto2", "GuardOT_ArchyIntoStore", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
		break;
		
		case "portroyal_9":
			LAi_SetSitType(Pchar);
			dialog.text = "Vedi com’è piacevole qua dentro? Bello fresco... E guarda qui, barili di whisky! Alla salute, Capitano!";
			link.l1 = "Ebbene, beviamo al nostro fortunato incontro e a questa piacevole conoscenza!";
			link.l1.go = "portroyal_10";
		break;
		
		case "portroyal_10":
			dialog.text = "Incantato!... Ah! Siete giunto di fresco nei Caraibi, vero, Monsieur de Maure?";
			link.l1 = "Relativamente di recente... o forse no. In verità, non saprei come dirlo. Mi sembra d’aver vissuto qui metà della mia vita.";
			link.l1.go = "portroyal_11";
		break;
		
		case "portroyal_11":
			dialog.text = "Oh, come ti capisco... Eppure anch’io ormai sono qui da un bel pezzo. Quando sono finito su quell’isola maledetta, da cui William mi tirò fuori... Ah, mi sembrava d’averci lasciato almeno metà della mia vita laggiù.";
			link.l1 = "Interessante! Quale isola era quella?";
			link.l1.go = "portroyal_12";
		break;
		
		case "portroyal_12":
			dialog.text = "Willy è un vecchio compare mio, ci conoscevamo da quando ancora respiravo l’aria fresca di Scozia... Bei tempi, quelli. Fui tanto sciocco da mettermi a litigare coi maledetti papisti e col Sant’Uffizio stesso, che poi mi mise una taglia sulla testa. All’epoca facevo il mercante, avevo persino una mia flûte.\nEh, quel maledetto giorno la mia nave fu assaltata dagli spagnoli, mascherati da filibustieri. Combattemmo come diavoli, ma riuscirono a serrarci in trappola come topi! Eppure, il vecchio Colhaun non perse la bussola e si gettò fuori bordo con una botte d’acqua e qualche tavola.\nMi approfittai del buio e sgattaiolai via dalla nave, senza farmi scorgere dai soldati. Le speranze di cavarsela erano misere, ma restare a bordo voleva dire non averne affatto. Dopo due giorni, m’approdai sulla spiaggia di qualche isoletta deserta.\nAvevo già bazzicato i Caraibi per un po’, eppure mai avevo sentito parlare di quel posto! Piccola, senza anima viva... e ci rimasi per due anni, che mi parvero un’eternità. Ancora non so come feci a non perdere il senno.";
			link.l1 = "Hai passato due anni su un'isola deserta?";
			link.l1.go = "portroyal_13";
		break;
		
		case "portroyal_13":
			dialog.text = "Eccome, maledetto posto! Per fortuna c’era acqua dolce. Mi sono mantenuto con granchi, cirripedi, pesci e uccelli. Ecco perché l’ho chiamata Isola dei Granchi. Non avevo armi, così ho imparato a maneggiare fiocina, lancia e freccia come un selvaggio! Ohoo! Beviamo, capitano! Non mi tiro certo indietro davanti a un sorso...";
			link.l1 = "Eh... Non ti invidio, davvero.";
			link.l1.go = "portroyal_14";
		break;
		
		case "portroyal_14":
			dialog.text = "Ecco qua! Proprio così dissi quando misi piede su quella distesa di sabbia: 'Vecchio Archy, la tua sorte non è invidiabile, ma non è neppure disperata!' E sai cosa mi ha tenuto in vita, Capitano?";
			link.l1 = "Una nave che passa vicino all'isola?";
			link.l1.go = "portroyal_15";
		break;
		
		case "portroyal_15":
			dialog.text = "No! Fu il lavoro a salvarmi! Il lavoro, la fede e la voglia di campare! Ho esplorato tutta l’isola, ogni suo anfratto, e sono stato ricompensato con uno scrigno pieno di attrezzi da carpentiere, calamai e altre piccole cianfrusaglie. Sai che mi sono detto, in quel momento? Versa ancora, Capitano, versa!\nMi sono detto: Archie, devi lavorare per non perdere la brocca, e Dio ti ha dato tutto per cominciare. E guarda qua! Ho iniziato a costruire una casa vicino a una baia, e sai che ti dico? Mi ha salvato dai cattivi pensieri e mi ha dato uno scopo per restare vivo!";
			link.l1 = "Mi siete d’ispirazione viva, signor Calhoun. Non ogni uomo riuscirebbe a combinare alcunché in una situazione simile, se pure muover dito...";
			link.l1.go = "portroyal_16";
		break;
		
		case "portroyal_16":
			dialog.text = "Eh già, il vecchio Calhaun non è nato in Scozia per caso! Proprio così! Siamo figli delle montagne – forti, coraggiosi e duri, ben più degli smidollati delle paludi. Versa ancora un goccio... Già, di che blateravo? Ah, sì! Ho sgobbato e mi sono costruito una casa degna. E ho pure iniziato un diario per annotare ogni sventura quotidiana. Il diario l'ho portato con me quando Willy mi ha tirato fuori dai guai.\nOra lo tengo qui su questo tavolo e lo rileggo ogni volta che ci fermiamo a Port Royal, bello sdraiato in un letto caldo e morbido.\nCi ho scritto tutto, ogni cosa accaduta prima e dopo il mio arrivo. È una delle ragioni per cui non ho ancora perso il senno.";
			link.l1 = "Allora è stato il signor Paterson a pescarti dall’isola? Ma come diavolo ha fatto a trovarla? Avevi detto...";
			link.l1.go = "portroyal_17";
		break;
		
		case "portroyal_17":
			dialog.text = "Sì, sì, l'isola non si trova su nessuna mappa. Ma Willy, lui è il vecchio Willy! Può fare ogni maledetta cosa! E lui ha trovato quell'isola maledetta e mi ha salvato, e per questo gli sarò grato finché campo. Eh già...";
			link.l1 = "Ti piace servire il signor Paterson? Vorresti riprovarci contando solo sulle tue forze?";
			link.l1.go = "portroyal_18";
		break;
		
		case "portroyal_18":
			dialog.text = "Ho finito con questa storia dell’essere indipendente. Willy è giovane, fortunato, e siamo amici da una vita. Che altro mi serve? No, starò con Willy fino alla fine dei miei giorni, o perlomeno finché non mi caccia di nuovo quando mi ubriaco, ahah! A proposito di sbronzarsi, versa da bere!";
			link.l1 = "Akh... (bevo) Dimmi, signor Calhoun. Ho sentito dire che eri, ehm, un cacciatore di tesori. È vero, o sono solo chiacchiere da taverna?";
			link.l1.go = "portroyal_19";
		break;
		
		case "portroyal_19":
			dialog.text = "Chi te l'ha detto? Beh, ormai non ha senso negarlo. Un tempo lo ero, sì. Ma non è finita bene, quella maledetta caccia al tesoro mi ha portato dritto dai gesuiti e su quell’isola. Quei santi padri hanno torturato un poveraccio a morte per mia causa, e io stesso... Ma lasciamo stare il passato, che resti sepolto.\nHo già pagato abbastanza per i miei peccati, e spero di non ripeterli mai più. No, Willy non lo permetterà, ne sono certo!";
			link.l1 = "Ascolta, Archibald. Hai mai sentito parlare d’un tale chiamato Miguel Dichoso?";
			link.l1.go = "portroyal_20";
		break;
		
		case "portroyal_20":
			dialog.text = "Non ho mai sentito quel nome prima d’ora. Chi sarebbe costui?";
			link.l1 = "Oh, nessuno di importante... solo un uomo a cui piace andare a caccia d’avventure e tesori. Ma visto che non ne hai sentito parlare, lasciamo stare.";
			link.l1.go = "portroyal_21";
		break;
		
		case "portroyal_21":
			dialog.text = "Sì, lasciam perdere! Parliamo invece della vecchia Europa! Ricordo vent’anni fa in Scozia...";
			link.l1 = "...";
			link.l1.go = "portroyal_22";
		break;
		
		case "portroyal_22":
			DialogExit();
			AddDialogExitQuest("GuardOT_MCOutFromArchyRoom");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

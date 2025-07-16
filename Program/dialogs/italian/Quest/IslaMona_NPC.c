void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
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
			dialog.text = "Che ti serve?";
			link.l1 = "Niente.";
			link.l1.go = "exit";
		break;
		
		// Родриго Хименес
		case "Himenes_exit":
			dialog.text = "Altro, Capitano?";
			link.l1 = "Niente per ora...";
			link.l1.go = "Himenes_exit_1";
		break;
		
		case "Himenes_exit_1":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_exit";
		break;
		
		case "Himenes":
			dialog.text = "Ah-ah-ah! Señor Gesù Cristo! Gloria a Santiago il Protettore! Gloria alla Vergine Maria! Siamo salvi! Ah-ah-ah!";
			link.l1 = "Spagnoli! Alle armi!";
			link.l1.go = "Himenes_1_1";
			link.l2 = "Salve. Ho sentito che avete dei guai? Chi siete, buon uomo?";
			link.l2.go = "Himenes_2";
		break;
		
		case "Himenes_1_1":
			AddComplexSelfExpToScill(100, 100, 100, 100);
			dialog.text = "Ah-ah-ah-ah-ah-ah-ah-ah!";
			link.l1 = "Bene-bene, calmati. È solo un'abitudine.";
			link.l1.go = "Himenes_2";
		break;
		
		case "Himenes_2":
			dialog.text = "Ah-ah! Señor, mi chiamo Rodrigo Jimenez. Sono un perito e, per volere del destino, el jefe di questa sventurata gente.";
			link.l1.go = "Himenes_3";
		break;
		
		case "Himenes_3":
			dialog.text = "Noi... siamo stati sbarcati qui. Ma, señor, non siamo dei furfanti! Ah-ah-ah-ah!";
			link.l1 = "Che c’è da ridere?";
			link.l1.go = "Himenes_4";
		break;
		
		case "Himenes_4":
			dialog.text = "Ah... Mi scusi, señor! È tutto a causa del mio malanno, da bambino rido quando sono molto nervoso. Ah.";
			link.l1 = "E tu sei stato scelto come capo?.. Bene. La gente non sbarca su isole deserte senza motivo, señor. Vuoi spiegarti? Ti concedo solo un’opportunità.";
			link.l1.go = "Himenes_5";
		break;
		
		case "Himenes_5":
			string nationManName[4];
			nationManName[0] = "English";
			nationManName[1] = "French";
			nationManName[2] = "If you are seeing this, it's a bug";
			nationManName[3] = "Spaniard";
			dialog.text = "Perdonate, messere, temo di non aver colto il vostro nome. Siete inglese?";
			link.l1 = nationManName[sti(pchar.BaseNation)]+" . È davvero così importante? Lasciamo stare il mio nome per ora.";
			link.l1.go = "Himenes_6";
		break;
		
		case "Himenes_6":
			dialog.text = "In verità, essendo stati riconosciuti come eretici dalla Chiesa Cattolica spagnola, dobbiamo presentarci al tribunale giusto della Santa Inquisizione. Ecco perché la tua nazionalità è per noi di vitale importanza. Un capitano spagnolo sarebbe costretto a consegnarci alle autorità locali. Una cosa simile non la sopravviveremmo un'altra volta! Ah-ah!";
			if (sti(pchar.BaseNation) == SPAIN) dialog.text = "Ah-ah-ah-ah-ah-ah! Questa è la nostra sorte, tanto ormai non abbiamo più nulla da perdere."+dialog.text;
			link.l1 = "Ebbene, per tua fortuna, le faccende dell’Inquisizione non mi riguardano. E allora? Siete dei pagani, voi?";
			link.l1.go = "Himenes_7";
		break;
		
		case "Himenes_7":
			dialog.text = "No, te lo giuro! La nostra comunità si dedicava all’artigianato e al commercio nella gloriosa città di Cadice da cinquant’anni. Tutto filava liscio, avevamo persino comprato una nave e ottenuto una licenza per commerciare con le colonie del nostro Impero. Ora capisco che allora abbiamo varcato un certo limite e non eravamo affatto pronti ai nuovi rivali... e ai loro sporchi metodi.";
			link.l1 = "Non hai fatto affari con qualcuno in Europa e per questo tutta la compagnia s’è ritrovata bloccata su un’isola deserta nei Caraibi? E io che pensavo d’avere dei guai...";
			link.l1.go = "Himenes_8";
		break;
		
		case "Himenes_8":
			dialog.text = "Purtroppo è proprio così. La nostra comunità fu fondata da ebrei convertiti alla nuova fede, che ottennero il permesso di tornare in patria, in Spagna. Questa vecchia storia è bastata per dar adito ad accuse e agli occhi vigili delle autorità.";
			link.l1 = "E così sei scappato...";
			link.l1.go = "Himenes_9";
		break;
		
		case "Himenes_9":
			dialog.text = "Sì! Ah-ah-ah! Sulla nostra nave! Stavamo andando a Curaçao per costruirci una nuova casa e un nuovo mestiere. Ma abbiamo sottovalutato la tenacia dell’Inquisizione, e ci è costato caro. Il loro messaggero ci ha intercettati poco lontano da qui e ha ordinato al capitano di riportarci a casa...";
			link.l1 = "Maledizione!";
			link.l1.go = "Himenes_10";
		break;
		
		case "Himenes_10":
			dialog.text = "E c’è dell’altro! Ah! Il nostro capitano non voleva scocciarsi a riportarci oltre l’Atlantico né a liberarci a suo rischio nel primo porto. Così, con una decisione da vero Salomone, ci ha dato da mangiare, ci ha sbarcati qui, e tanti saluti.";
			link.l1 = "Una storia tragica davvero, non c'è che dire. Riassumiamo: non puoi tornare a casa, le colonie amiche ti denunceranno, e i porti stranieri non ti accoglieranno - qui la guerra non finisce mai. Quali sono i tuoi piani?";
			link.l1.go = "Himenes_11";
		break;
		
		case "Himenes_11":
			dialog.text = "Mi avete dipinto un quadro così cupo, signore, che resto senza parole. Pare quasi che non ci sia terra migliore per noi di quest’isola.";
			link.l1 = "Non direi, c’è un’isola migliore.";
			link.l1.go = "Himenes_12";
		break;
		
		case "Himenes_12":
			dialog.text = "Davvero? È spagnolo?";
			link.l1 = "È mio. Per volontà del destino, ho ereditato un vecchio rifugio di pirati su un’isola disabitata. Ora è la mia base, e voglio ampliarla, esplorare l’isola e, se possibile, costruirci una manifattura...";
			link.l1.go = "Himenes_13";
		break;
		
		case "Himenes_13":
			dialog.text = "Sei forse un filibustiere?";
			link.l1 = "Sì.";
			link.l1.go = "Himenes_14_1";
			link.l2 = "No.";
			link.l2.go = "Himenes_14_2";
		break;
		
		case "Himenes_14_1":
			dialog.text = "Nuovo Mondo! Eh già, eccoci qua. A casa dicono che i pirati siano veri demoni, manco fossero uomini. Mangiano i bambini, violentano le donne e spellano i buoni cattolici vivi. È vero tutto ciò?";
			link.l1 = " Dipende dal giorno della settimana. Ne parleremo un'altra volta. Sto cercando gente. Persone laboriose e capaci, pronte a vivere lontano dalla civiltà per diversi anni. Ti interesserebbe una faccenda simile? ";
			link.l1.go = "Himenes_15";
		break;
		
		case "Himenes_14_2":
			dialog.text = "Peccato, visto che son già un fuorilegge, mi piacerebbe veder almeno un pirata.";
			link.l1 = "Forse avrai di nuovo un’occasione simile. Ne parleremo un’altra volta. Sto cercando gente laboriosa e capace, disposta a vivere lontano dalla civiltà per qualche anno. Ti interesserebbe una proposta del genere?";
			link.l1.go = "Himenes_15";
		break;
		
		case "Himenes_15":
			dialog.text = "Non abbiamo altra via d’uscita. Ma in verità non è poi una pessima scelta. Accetteremo, se ci permetterai di vivere e lavorare in pace. E prometti di rimandarci un giorno a casa! Dacci la tua parola, signore, e dicci il tuo nome...";
			link.l1 = "Io, Capitano "+GetFullName(pchar)+", ti do la mia parola. ?";
			link.l1.go = "Himenes_16";
		break;
		
		case "Himenes_16":
			dialog.text = "Ah-ah! Siamo salvi! Così sia! Siamo diverse famiglie, circa trenta anime. Tutti istruiti, abili nei mestieri e nel commercio.";
			link.l1 = "Il destino ha parlato... Sali pure a bordo!";
			link.l1.go = "Himenes_17";
		break;
		
		case "Himenes_17":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "goto", "goto1", "none", "", "", "", 10.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			IslaMona_TerksHimenesOnBoard();
		break;
		
		case "Himenes_18":
			dialog.text = "Piacere di conoscerti, Senor Rodgar. Pare che dovremo convivere e lavorare assieme per un bel pezzo... Santo cielo, come fai a sopportare questo caldo infernale?";
			link.l1 = "";
			link.l1.go = "Himenes_19";
		break;
		
		case "Himenes_19":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_14";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Himenes_20":
			dialog.text = "Se non ti dispiace, intervengo io: Capitano, concedici un giorno per ambientarci e dare un'occhiata veloce alle scorte e alla terra. Son certo che il signor Rodgar avrà mille idee su come sfruttare questo pezzo di terra. Credo proprio che faremo una bella squadra.";
			link.l1 = "Non hai davvero scelta, Hymenese. Ah-ah.!";
			link.l1.go = "Himenes_21";
		break;
		
		case "Himenes_21":
			dialog.text = "Ah-ah-ah-ah-ah-ah!";
			link.l1 = "";
			link.l1.go = "Himenes_22";
		break;
		
		case "Himenes_22":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_16";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Himenes_23":
			dialog.text = "Sì, Capitano?";
			link.l1 = "Hymenese, qualche buona novella per me?";
			link.l1.go = "Himenes_24";
		break;
		
		case "Himenes_24":
			dialog.text = "Capitano, questo è un incubo. La tua casa non è male, certo. Ma per il resto... È impossibile vivere in queste catapecchie, circondati da giungla, e don Rodgar nemmeno sa cosa succede dall’altra parte dell’isola!! Incredibile! Ah-ah!";
			link.l1 = "Sei in ansia o stai davvero ridendo di tutto questo proprio adesso?";
			link.l1.go = "Himenes_25";
		break;
		
		case "Himenes_25":
			dialog.text = "Ma certo che è buffo! Che diavolo hanno fatto in tutti questi anni? Prima di tutto, bisogna finire di tirare su due case e sistemare queste catapecchie almeno a un livello decente. Se la gente deve lavorare per davvero, deve pure viverci come si deve. Poi farò esplorare l’isola per bene ai pirati: magari qui non ci sono soltanto sassi e sabbia. Quando tutto sarà sistemato, saprò dirti per filo e per segno che fare di questa terra.";
			link.l1 = "Sembra magnifico! Che cosa volete da me?";
			link.l1.go = "Himenes_26";
		break;
		
		case "Himenes_26":
			AddQuestRecordInfo("IslaMonaData", "1");
			dialog.text = "Materiali per case, mobilio e rifugi provvisori. Ho fatto tutti i conti. Ecco, prendi questa lista.";
			link.l1 = "Notevole...";
			link.l1.go = "Himenes_27";
		break;
		
		case "Himenes_27":
			dialog.text = "Davvero? Signore, abbiamo costruito cattedrali! Ora sì che è qualcosa di grandioso...";
			link.l1 = "Sono propenso a crederti! Basta che non ti venga in mente di tirar su una cattedrale qui. Dovrò scarrozzare montagne di roba ogni volta?";
			link.l1.go = "Himenes_28";
		break;
		
		case "Himenes_28":
			dialog.text = "No, questi materiali ci basteranno per un po’, ma dovremo comunque procurarci altra roba più avanti. Se vuoi evitarti seccature in futuro, porta il doppio delle provviste.";
			link.l1 = "Va bene, mi hai convinto. Vedrò cosa posso fare. C'è una scadenza?";
			link.l1.go = "Himenes_29";
		break;
		
		case "Himenes_29":
			dialog.text = "No, signore. Ma vi prego cortesemente di non indugiare - questi sono lavori che vanno fatti per far avanzare le cose. E la gente ha bisogno anche di un tetto sulla testa. Caricate i materiali nel magazzino e non scordate di avvisarmi quando tutto sarà pronto. Ah, quasi dimenticavo! Parlate con il signor Rodgar per esplorare l'isola.";
			link.l1 = "D'accordo!";
			link.l1.go = "Himenes_30";
		break;
		
		case "Himenes_30":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_exit";
			pchar.questTemp.IslaMona = "stalk";
			AddQuestRecord("IslaMona", "6");
		break;
		
		case "Himenes_31":
			dialog.text = "Aye, Capitano?";
			if (IslaMona_CheckBuild()) // привез товары на стройку
			{
				link.l1 = "Ciao, Hymenez. Controlla il magazzino.";
				link.l1.go = "Himenes_32_1";
			}
			else // не привез товары на стройку
			{
				link.l1 = "Ciao, Hymenez. I miei uomini hanno perlustrato l’intera isola. Che ne dici?";
				if (CheckAttribute(pchar, "questTemp.IslaMona.Food")) link.l1.go = "Himenes_32_2"; // привез еду и лекарства
				else link.l1.go = "Himenes_32_3";
			}
		break;
		
		case "Himenes_32_1":
			IslaMona_RemoveBuild(); // сразу удаляем товары со склада
			dialog.text = "Hai svolto questo compito con gran maestria! Se mai metti piede a Cadice, vieni a lavorare per me come magazziniere!";
			link.l1 = "Vado subito! Dimmi, compare, che farai adesso?";
			if (CheckAttribute(pchar, "questTemp.IslaMona.Food")) link.l1.go = "Himenes_34_1"; // привез еду и лекарства
			else link.l1.go = "Himenes_34_2";
		break;
		
		case "Himenes_32_2":
			dialog.text = "Señor Capitano, prima pensiamo a sistemazione e provviste. Faremo piani in seguito. Attendo la merce del vostro elenco al magazzino.";
			link.l1 = "D'accordo, ho capito. Prima dobbiamo costruire delle case e sistemare questo posto. La merce arriverà presto.";
			link.l1.go = "Himenes_33";
		break;
		
		case "Himenes_32_3":
			dialog.text = "Capitano, prima pensiamo a sistemarci e alle provviste. I piani li faremo dopo. Sto aspettando la merce della tua lista al magazzino. E il tuo compare pirata aspetta anch’egli viveri e medicamenti.";
			link.l1 = "D'accordo, ho capito. Prima dobbiamo costruire delle case e mettere un po' d'ordine in questo posto. La merce arriverà presto. Anche per il mio compare pirata.";
			link.l1.go = "Himenes_33";
		break;
		
		case "Himenes_33":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_31";
		break;
		
		case "Himenes_34_1":
			dialog.text = "Dacci sei mesi, Capitano, e non riconoscerai più questo posto.";
			link.l1 = "Stai dicendo che tra sei mesi non ci saranno né te, né l’insediamento, né le provviste qui? Ci si vede, allora!";
			link.l1.go = "Himenes_37"; // все выполнил
		break;
		
		case "Himenes_34_2":
			dialog.text = "Cominceremo a lavorare non appena avrai sistemato la faccenda con questo furfante. Ti ha chiesto viveri e medicamenti, e sono d’accordo con lui – la richiesta è ben ragionevole.";
			link.l1 = "Riferirò le tue parole a lui.";
			link.l1.go = "Himenes_35";
			AddQuestRecord("IslaMona", "11");
		break;
		
		case "Himenes_35":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_36";
		break;
		
		case "Himenes_36":
			dialog.text = "E allora, Capitano? Hai fatto tutto quello che il tuo filibustiere ti ha chiesto?";
			if (CheckAttribute(pchar, "questTemp.IslaMona.Food"))
			{
				link.l1 = "Ho risolto tutte le faccende con Rodgar. La ricognizione dell’isola è iniziata, viveri e medicine sono in magazzino. Ora tocca a te.";
				link.l1.go = "Himenes_34_1";
			}
			else
			{
				link.l1 = "Non temere, troveremo una soluzione. Lascialo a me.";
				link.l1.go = "Himenes_35";
			}
		break;
		
		case "Himenes_37":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_exit";
			DeleteAttribute(pchar, "questTemp.IslaMona.Food");
			pchar.questTemp.IslaMona = "build";
			AddQuestRecord("IslaMona", "12");
			SetFunctionTimerCondition("IslaMona_BuildDone", 0, 0, 180, false);
		break;
		
		case "Himenes_38":
			dialog.text = "Señor Capitano! Che ne dite? Ah-ah-ah?";
			link.l1 = "È assai più gradevole. Riporta, Himenes!";
			link.l1.go = "Himenes_39";
		break;
		
		case "Himenes_39":
			dialog.text = "Ora puoi davvero vivere qui! Abbiamo ripulito e ricostruito tutte le case, tranne la tua, ovviamente. Non è proprio lussuoso, ma non è peggio che nel nostro Belize.";
			link.l1 = "Belize appartiene da tempo all’Inghilterra, Himenes.";
			link.l1.go = "Himenes_40";
		break;
		
		case "Himenes_40":
			dialog.text = "Non sono sicuro che le case lo sappiano, Capitano, ahah!";
			link.l1 = "Ora hai un tetto sopra la testa, e l’insediamento sembra abitato da cristiani. E adesso, che si fa?";
			link.l1.go = "Himenes_41";
		break;
		
		case "Himenes_41":
			dialog.text = "Guarda un po’ in giro, parla con il signor Janssen, e ritorna da me. Discuteremo quel che hai scoperto sull’isola e i nostri piani, aye.";
			link.l1 = "Da quando hai cominciato a chiamare Rodgar così? Non stavate sempre a beccarvi?";
			link.l1.go = "Himenes_42";
		break;
		
		case "Himenes_42":
			dialog.text = "E li abbiamo ancora. Ma dobbiamo pur trovare un modo per costruire dei rapporti, in qualche maniera.";
			link.l1 = "Grazie, Rodrigo. Tornerò presto.";
			link.l1.go = "Himenes_43";
		break;
		
		case "Himenes_43":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload6", "none", "", "", "", 10.0); // возможно будет иной локатор в новой локации
			pchar.questTemp.IslaMona = "village";
		break;
		
		case "Himenes_44":
			dialog.text = "Capitano. Señor Janssen.";
			link.l1 = "Avanti, raccontami cosa hai scoperto durante la ricognizione dell’isola.";
			link.l1.go = "Himenes_45";
		break;
		
		case "Himenes_45":
			dialog.text = "Sì, Capitano. Alcuni posti li ho ispezionati di persona col nostro cercatore. Beh, che dirle... Isla Mona è un'isoletta misera, piccina e piuttosto noiosa. C'è pochissimo spazio per costruire, il terreno è arduo, scosceso, e di terra buona non ce n'è quasi per niente. Tre spiagge, una grotta allagata, rovi fitti, due pappagalli, un branco di capre, e noi...";
			link.l1 = "Sei serio? Vuoi dirmi che la cosa più preziosa su quest’isola è una mandria di capre?";
			link.l1.go = "Himenes_46";
		break;
		
		case "Himenes_46":
			dialog.text = "Ah-ah-ah-ah! Lo chiederei, signor! Ah-ah! Non mi hai lasciato finire!";
			link.l1 = "";
			link.l1.go = "Himenes_47";
		break;
		
		case "Himenes_47":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_38";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_48":
			dialog.text = "";
			link.l1 = "Va bene, d'accordo, dai, rilassati e continua pure. Lo sai, ho speso un bel po' di dobloni in questo posto.";
			link.l1.go = "Himenes_49";
		break;
		
		case "Himenes_49":
			dialog.text = "E non invano! Nella grotta c’è acqua dolce in abbondanza, terra sufficiente per piantare alberi da frutto, e le capre si possono allevare. Con un po’ di pesca e l’aiuto dei tuoi compagni, la questione del cibo si sistemerà in men che non si dica.";
			link.l1 = "Quindi, non dovrai più portare cibo qui? Non male. Speravo che questo posto potesse sopravvivere senza le mie continue attenzioni. Andiamo avanti.";
			link.l1.go = "Himenes_50";
		break;
		
		case "Himenes_50":
			dialog.text = "Hai ragione su tutto, señor. Ma non è finita qui! Prima di tutto, il señor Rodgar ha avuto la folle idea di costruire una taverna. Non so che vantaggi ne avrai, ma quel furfante sta tramando qualcosa.";
			link.l1 = "Vuole solo sbronzarsi, ecco cosa!";
			link.l1.go = "Himenes_51";
		break;
		
		case "Himenes_51":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_40";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_52":
			dialog.text = "In secondo luogo, la Baia del Governatore s’è rivelata assai più profonda di quanto pensassimo. Possiamo costruirci un molo vero e proprio.";
			link.l1 = "Non capisco bene come questo mi tornerà utile, ma già questa è una buona notizia. Non è tutto, spero?";
			link.l1.go = "Himenes_53";
		break;
		
		case "Himenes_53":
			dialog.text = "Abbiamo trovato un boschetto di alberi di bacote. Un luogo perfetto per una fabbrica.";
			link.l1 = "Mi rallegri, Rodrigo! Eh già, ottime novelle!";
			link.l1.go = "Himenes_54";
		break;
		
		case "Himenes_54":
			dialog.text = "Questo è tutto per ora, señor. Forse ci verranno altre idee in futuro. Sai, le idee migliori arrivano mentre si lavora! Cosa vuoi chiedere?";
			link.l1 = "Parlami del bacote. Sembra interessante.";
			link.l1.go = "Himenes_55";
		break;
		
		case "Himenes_55":
			dialog.text = "A mio avviso, una piccola manifattura potrà estrarre questo prezioso legname per diversi anni. Le riserve sono modeste, ma la risorsa è strategica. Possiamo ripulire un’area nel centro dell’isola e costruirvi una casa con magazzino. È un inizio. Oltre ai materiali da costruzione, ci serviranno anche una quindicina di paia di manette e moschetti.";
			link.l1 = "E perché mai ci servono le manette? E poi, perché proprio quindici?";
			link.l1.go = "Himenes_56";
		break;
		
		case "Himenes_56":
			dialog.text = "È fatica dura, señor. Direi persino che è lavoro da schiavi.";
			link.l1 = "Capisco. Eh-eh...";
			link.l1.go = "Himenes_57_1";
			link.l2 = "Sei impazzito? Non diventerò mai un padrone di schiavi!";
			link.l2.go = "Himenes_57_2";
		break;
		
		case "Himenes_57_1":
			dialog.text = "";
			link.l1 = "E perché ci serve un moschetto? E perché solo uno?";
			link.l1.go = "Himenes_59";
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
		break;
		
		case "Himenes_57_2":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_42";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
		break;
		
		case "Himenes_58":
			dialog.text = "Sono d'accordo col pirata, signor mio. Non vi comprendo, capitano. Tutta l'economia di queste terre si regge sul lavoro degli schiavi, e così resterà per molti anni ancora. In cosa saremmo diversi noi?";
			link.l1 = "Prenderò una decisione. Intanto, dimmi perché ti serve un moschetto? E perché proprio uno solo?";
			link.l1.go = "Himenes_59";
		break;
		
		case "Himenes_59":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_44";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_60":
			dialog.text = "Certo, la fabbrica avrà bisogno di manutenzione. Una volta costruita, quest’isola avrà un’economia e tu sarai il suo principale compagno di scambi. Gli schiavi li nutriremo noi, ma sicurezza e produzione saranno tutte a tue spese. I coloni vorranno cento dobloni e cinque fiaschi di vino per ogni partita. Per la sicurezza, tratta direttamente con Don Janssen.";
			link.l1 = "";
			link.l1.go = "Himenes_61";
		break;
		
		case "Himenes_61":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_46";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_62":
			dialog.text = "quaranta misure ogni mese. E l’oro è per il futuro. Un giorno ci porterai via da qui, ricordi la tua promessa? Ogni fatica va ricompensata, e con i tuoi dobloni pagheremo cacciatori e artigiani per il loro lavoro nel villaggio. Così avremo il commercio, e con esso – la civiltà!";
			link.l1 = "Questo è lo spirito! Bene! Per ora, tutto suona abbastanza convincente...";
			link.l1.go = "Himenes_63";
		break;
		
		case "Himenes_63":
			dialog.text = "Cos'altro ti incuriosisce, dunque?";
			link.l1 = "E allora, qual è la storia di questa taverna? Perché non costruire un teatro?";
			link.l1.go = "Himenes_64";
		break;
		
		case "Himenes_64":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_48";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_65":
			dialog.text = "Capitano, l’ho avvertito che l’idea della casa non vi sarebbe piaciuta. Ma non c’è altro verso. Avete la dimora più grande di... ehm, tutta la città; trasformeremo il pianterreno in una sala, monteremo tavoli e cucina. Le provviste e il rum li terremo nelle grotte sotto la casa. Ci sono mani pronte a cucinare e musici da ingaggiare. Il piano di sopra resterà vostro, non lo toccheremo. Tutto ciò che avete al piano terra lo sposteremo noi al piano di sopra.";
			link.l1 = "D'accordo. Ma che cosa ci darà davvero la taverna?";
			link.l1.go = "Himenes_66";
		break;
		
		case "Himenes_66":
			dialog.text = "Avremo un po' di vita culturale, e tu potrai tenere in serbo circa trecento anime proprio nel cuore dei Caraibi.";
			link.l1 = "Interessante... Ci rifletterò su.";
			link.l1.go = "Himenes_67";
		break;
		
		case "Himenes_67":
			dialog.text = "Cos'altro ti incuriosisce?";
			link.l1 = "E allora, che mi dici del molo?";
			link.l1.go = "Himenes_68";
		break;
		
		case "Himenes_68":
			dialog.text = "È semplice. Sgombreremo la Baia del Governatore dagli scogli, installeremo dei fanali di segnalazione e costruiremo un molo. Il signor Janssen sostiene che potrai riparare tre navi nella baia, oppure una nave di prima classe. E sarà ben più gradevole tornare qui, senza dover trascinare ogni volta la scialuppa sulla spiaggia.";
			link.l1 = "Sarebbe cosa gradita.";
			link.l1.go = "Himenes_69";
		break;
		
		case "Himenes_69":
			dialog.text = "Cosa desideri sapere?";
			link.l1 = "Questo è tutto per ora. Tornerò quando avrò deciso cosa costruire.";
			link.l1.go = "Himenes_70";
		break;
		
		case "Himenes_70":
			dialog.text = "Signor Capitano, prenda questo documento. Mi sono permesso di annotare tutti i dettagli così da non doverli ripetere una dozzina di volte. Studiatelo, portate i materiali e date l’ordine.";
			link.l1 = "Ti ringrazio, Rodrigo.";
			link.l1.go = "Himenes_71";
		break;
		
		case "Himenes_71":
			DialogExit();
			IslaMona_HouseDialogFin();
		break;
		
		case "Himenes_72": // нода Хименеса строителя и управляющего факторией
			if (CheckAttribute(pchar, "questTemp.IslaMona.RecordPart")) // после защиты Исла Моны - нужно еще 10 рабов
			{
				dialog.text = "Señor Capitano, ci servono 10 schiavi per lavorare nella fabbrica – te l’avevo già detto, non te ne sei scordato, vero?";
				if (GetSquadronGoods(pchar, GOOD_SLAVES) >= 10)
				{
					link.l1 = "Già consegnato. Scaricateli e avviate la produzione.";
					link.l1.go = "Himenes_plantation_12";
				}
				else
				{
					link.l1 = "La mia memoria non mi tradisce. Li porterò presto.";
					link.l1.go = "Himenes_plantation_14";
				}
				break;
			}
			dialog.text = "Allora, Señor Capitano, che ne dite?";
			if (!CheckAttribute(pchar, "questTemp.IslaMona.Harbour"))
			{
				link.l1 = "Voglio una baia limpida e un molo sicuro. Sarà la base della mia flotta.";
				link.l1.go = "Himenes_harbour";
			}
			if (!CheckAttribute(pchar, "questTemp.IslaMona.Tavern"))
			{
				link.l2 = "Vai pure e costruisci la taverna. Tutti ne saranno grati, e io potrò tenere qui una scorta.";
				link.l2.go = "Himenes_tavern";
			}
			if (!CheckAttribute(pchar, "questTemp.IslaMona.Plantation"))
			{
				link.l3 = "Inizia a costruire la piantagione. È ora di recuperare l’investimento.";
				link.l3.go = "Himenes_plantation";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Plantation.Slave") && IslaMona_CheckSlave())
			{
				link.l4 = "Rodrigo, gli specialisti più preziosi e l'attrezzatura sono stati consegnati alla fabbrica. Puoi metterti al lavoro.";
				link.l4.go = "Himenes_plantation_7";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Factory.Part") && sti(pchar.questTemp.IslaMona.Factory.Part) > 0)
			{
				link.l4 = "Rodrigo, sono venuto a prendere il mio legno di ferro.";
				link.l4.go = "Himenes_bacaut";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Harbour") && pchar.questTemp.IslaMona.Harbour == "done" && CheckAttribute(pchar, "questTemp.IslaMona.Tavern") && pchar.questTemp.IslaMona.Tavern == "done" && CheckAttribute(pchar, "questTemp.IslaMona.Factory") && !CheckAttribute(pchar, "questTemp.IslaMona.Church"))
			{
				link.l5 = "Rodrigo, abbiamo terminato la nostra grande costruzione?";
				link.l5.go = "Himenes_church";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Church") && pchar.questTemp.IslaMona.Church == "start" && IslaMona_CheckChurch())
			{
				link.l5 = "Rodrigo, costruiamo la tua chiesa.";
				link.l5.go = "Himenes_church_10";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Church") && pchar.questTemp.IslaMona.Church == "Wait_candles" && IslaMona_CheckCandles())
			{
				link.l5 = "Rodrigo, ti ho portato gli oggetti sacri della tua chiesa.";
				link.l5.go = "Himenes_church_10_3";
			}
			link.l10 = "Niente per ora...";
			link.l10.go = "Himenes_73";
		break;
		
		case "Himenes_harbour":
			if (IslaMona_CheckHarbour())
			{
				dialog.text = "I materiali sono a disposizione, tutto è pronto. La costruzione richiederà 4 mesi.";
				link.l1 = "Non hai fretta, vero! Ebbene, buona fortuna, Rodrigo.";
				link.l1.go = "Himenes_harbour_1";
			}
			else
			{
				dialog.text = "Temo che non ci siano abbastanza materiali nel magazzino. Per favore, ricontrolla la lista.";
				link.l1 = "Ci penserò io.";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_tavern":
			if (IslaMona_CheckTavern())
			{
				dialog.text = "I materiali sono a disposizione, tutto è pronto. La costruzione richiederà tre mesi.";
				link.l1 = "Non hai mica fretta, vero! Ebbene, buona fortuna, Rodrigo.";
				link.l1.go = "Himenes_tavern_1";
			}
			else
			{
				dialog.text = "Temo che nel magazzino non ci siano abbastanza materiali. Per favore, controlla di nuovo l'inventario.";
				link.l1 = "Me ne occuperò io.";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_plantation":
			if (IslaMona_CheckPlantation())
			{
				dialog.text = "I materiali ci sono, tutto è pronto. La costruzione richiederà sei mesi.";
				link.l1 = "Non hai fretta, vero! Che la fortuna ti assista, Rodrigo.";
				link.l1.go = "Himenes_plantation_1";
			}
			else
			{
				dialog.text = "Temo che non ci siano abbastanza materiali nel magazzino. Per favore, controlla di nuovo la lista.";
				link.l1 = "Me ne occuperò io.";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_73":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
		break;
		
		case "Himenes_harbour_1":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_RemoveHarbour();
			pchar.questTemp.IslaMona.Harbour = "true";
			SetFunctionTimerCondition("IslaMona_BuildHarbour", 0, 0, 120, false);
		break;
		
		case "Himenes_harbour_2":
			dialog.text = "Benvenuto, Capitano. Come ti garba questo nuovo porto?";
			if (stf(environment.time) > 22.0 || stf(environment.time) < 5.0)
			{
				link.l1 = "È buio pesto, Rodrigo! Abbiamo quasi sfasciato il tuo tanto decantato molo! Almeno hai avuto la decenza d'accendere qualche luce, bravo!";
				link.l1.go = "Himenes_harbour_3";
			}
			else
			{
				link.l1 = "Niente male, Rodrigo! Pare una cosa da poco, ma è un piacere passeggiare su queste assi fino alla riva. E la baia è diventata più facile da navigare. Dunque, ora suppongo di poter ospitare più navi in questa piccola baia?";
				link.l1.go = "Himenes_harbour_4";
			}
		break;
		
		case "Himenes_harbour_3":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_51";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_harbour_4":
			sld = characterFromId("Islamona_carpenter");
			sld.portman.info = "true"; // если вдруг до сих пор не говорил об условиях стоянки
			pchar.questTemp.IslaMona.Harbour = "done"; // флаг - пристань построена и сдана
			dialog.text = "Sì, Capitano. Devo ammettere che c’è un certo orgoglio in tutto ciò. Dimmi pure come vuoi proseguire con il nostro grande progetto di costruzione.";
			if (CheckAttribute(pchar, "questTemp.IslaMona.Plantation") && pchar.questTemp.IslaMona.Plantation == "complete") // если пересеклось со сдачей фактории
			{
				link.l1 = "A proposito di costruzione. La mia manifattura dovrebbe ormai essere pronta. Giusto, Rodrigo?";
				link.l1.go = "Himenes_plantation_2";
			}
			else
			{
				link.l1 = "...";
				link.l1.go = "Himenes_harbour_5";
			}
		break;
		
		case "Himenes_harbour_5":
			DialogExit();
			IslaMona_HarbourClear();
		break;
		
		case "Himenes_tavern_1":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_RemoveTavern();
			pchar.questTemp.IslaMona.Tavern = "true";
			SetFunctionTimerCondition("IslaMona_BuildTavern", 0, 0, 90, false);
		break;
		
		case "Himenes_tavern_2":
			dialog.text = "H-hic! Capo! Qui si festeggia!";
			link.l1 = "Rodgar. Rodrigo. Oh, maledizione!";
			link.l1.go = "Himenes_tavern_3";
		break;
		
		case "Himenes_tavern_3":
			dialog.text = "Che c’è, c-c-capitano? Non ti va a genio il colore di queste mura?";
			link.l1 = "Solo ora mi rendo conto che voi due avete lo stesso nome! Ah-ah-ah! Uno spagnolo e un filibustiere, con lo stesso nome, che aprono una taverna su un’isola deserta e bevono insieme come se gli dèi indiani dovessero divorare tutti e far finire il mondo all’alba! Ah-ah! Io sto con voi!";
			link.l1.go = "Himenes_tavern_4";
		break;
		
		case "Himenes_tavern_4":
			dialog.text = "Ah-ah-ah! Proprio così! Bottino preso!";
			link.l1 = "Colpo grosso!";
			link.l1.go = "Himenes_tavern_5";
		break;
		
		case "Himenes_tavern_5":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_ReloadTavern();
		break;
		
		case "Himenes_plantation_1":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_RemovePlantation();
			pchar.questTemp.IslaMona.Plantation = "true";
			SetFunctionTimerCondition("IslaMona_BuildPlantation", 0, 0, 180, false);
		break;
		
		case "Himenes_plantation_2":
			dialog.text = "Tutto è pronto. Andiamo? Lascia che ti mostri la tua fabbrica.";
			link.l1 = "Fai strada.";
			link.l1.go = "Himenes_plantation_3";
		break;
		
		case "Himenes_plantation_3":
			DialogExit();
			pchar.questTemp.IslaMona.Plantation.Harbour = "true"; // наложилась сдача пристани и фактории
			IslaMona_PlantationGo();
		break;
		
		case "Himenes_plantation_4":
			dialog.text = "Capitano, quasi tutto è pronto per avviare le operazioni. Alloggi per i lavoratori, magazzino per le materie prime, area di lavorazione – una fabbrica degna di questo nome è sorta. Abbiamo già segnato gli alberi più promettenti nella giungla per l’abbattimento. Porta quindici lavoratori e l’equipaggiamento pattuito – 15 catene e moschetti – e daremo inizio ai lavori.";
			link.l1 = "Noi? Intendi gli schiavi?";
			link.l1.go = "Himenes_plantation_5";
		break;
		
		case "Himenes_plantation_5":
			dialog.text = "Ah! Schiavi... Gli schiavi taglieranno, i coloni lavoreranno, e i pirati faranno la guardia. Ci sarà da sgobbare per tutti – ti sei imbarcato in un’impresa tosta, Capitano.";
			link.l1 = "Quasi come la terra promessa, eh. Aspetta la merce, ora tocca a me andare a caccia.";
			link.l1.go = "Himenes_plantation_6";
		break;
		
		case "Himenes_plantation_6":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			pchar.questTemp.IslaMona.Plantation.Slave = "true"; // привезти рабов, кандалы и мушкет для запуска фактории
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "IslaMona_factoria_residence", "sit", "sit1", "IslaMona_PlantationHouse", -1);
			sld = characterFromId("Islamona_carpenter");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5);
			pchar.questTemp.IslaMona.Plantation = "done"; // флаг - фактория построена и сдана
		break;
		
		case "Himenes_plantation_7":
			dialog.text = "Un triste destino... Non lasceranno mai questo posto.";
			link.l1 = "Rodgar... voglio dire, Rodrigo! Primo, potrebbero andarsene. E secondo, se avessi incontrato qualcun altro a Terks, la tua sorte non sarebbe stata migliore.";
			link.l1.go = "Himenes_plantation_8";
		break;
		
		case "Himenes_plantation_8":
			dialog.text = "Lo so bene, Capitano. E non me lo scordo. Permettetemi di spiegarvi come funziona questa fabbrica. A partire dal mese prossimo, il quindicesimo giorno, consegneremo quaranta tronchi di bacout lavorato. Naturalmente, non occorre che veniate ogni mese per ogni consegna: tutte le partite verranno tenute qui in deposito, ad attendervi nella fabbrica.";
			link.l1 = "Dunque, posso prendere più carichi in una volta sola?";
			link.l1.go = "Himenes_plantation_9";
		break;
		
		case "Himenes_plantation_9":
			dialog.text = "Entro certi limiti, ovviamente – non sparire per troppo tempo. La gente non lavora anni senza paga, senza sapere se il loro unico cliente è ancora in vita o già marcisce tra i pescecani. Direi che consegneremo sei carichi prima di sospendere l’attività.";
			link.l1 = "Devo prendere tutta la mercanzia in una volta sola? E il prezzo, ricordami un po'?";
			link.l1.go = "Himenes_plantation_10";
		break;
		
		case "Himenes_plantation_10":
			dialog.text = "Sì, tutto in una volta. Il prezzo di un tronco di bacout standard è dieci dobloni. Inoltre, per ogni partita, dovrai consegnare cinque bottiglie di buon rum e altrettante di vino. Rodgar giura che prezzi così non li trovi in nessun altro angolo del mondo.";
			link.l1 = "Ma certo, sono d’accordo! Grazie, Rodrigo. Mettiamoci all’opera!";
			link.l1.go = "Himenes_plantation_11";
		break;
		
		case "Himenes_plantation_11":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			DeleteAttribute(pchar, "questTemp.IslaMona.Plantation.Slave");
			AddQuestRecordInfo("Unique_Goods", "5");
			IslaMona_RemoveSlave();
		break;
		
		case "Himenes_plantation_12":
			dialog.text = "Eccellente! Ora torniamo subito al lavoro!";
			link.l1 = "Bene.";
			link.l1.go = "Himenes_plantation_13";
		break;
		
		case "Himenes_plantation_13":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_FactoryReActivar(); // запустить факторию
		break;
		
		case "Himenes_plantation_14":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
		break;
		
		case "Himenes_bacaut":
			dialog.text = "Certo, capitano, prenda pure. Abbiamo i seguenti carichi pronti per la prossima data: "+sti(pchar.questTemp.IslaMona.Factory.Part)+", questo è "+sti(pchar.questTemp.IslaMona.Factory.Goods)+" tronchi. Quindi, ci devi "+sti(pchar.questTemp.IslaMona.Factory.Dublon)+" dobloni, "+sti(pchar.questTemp.IslaMona.Factory.Bottle)+" bottiglie di rum, e "+sti(pchar.questTemp.IslaMona.Factory.Bottle)+" bottiglie di vino, le hai tutte quante?";
			if (PCharDublonsTotal() >= sti(pchar.questTemp.IslaMona.Factory.Dublon) && PCharItemsTotal("potionrum") >= sti(pchar.questTemp.IslaMona.Factory.Bottle) && PCharItemsTotal("potionwine") >= sti(pchar.questTemp.IslaMona.Factory.Bottle))
			{
				link.l1 = "Ma certo. Ecco il tuo compenso.";
				link.l1.go = "Himenes_bacaut_1";
			}
			else
			{
				link.l1 = "Pare che non abbia tutto. Lo porto subito.";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_bacaut_1":
			if (IslaMona_CheckBacautSpace())
			{
				dialog.text = "Eccellente. Trasporteremo il bacout dalla fabbrica al tuo magazzino, da dove potrai ritirarlo quando ti pare.";
				link.l1 = "Ottimo. Prepara la prossima partita.";
				link.l1.go = "Himenes_bacaut_2";
			}
			else
			{
				dialog.text = "Frena un po', capitano! Il tuo magazzino è pieno zeppo – non possiamo caricare tutto il bacout raccolto. Libera un po' di spazio nel magazzino, poi torna da me.";
				link.l1 = "D'accordo, ci penso io.";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_bacaut_2":
			dialog.text = "Ma certo, capitano!";
			link.l1 = "...";
			link.l1.go = "Himenes_73";
			IslaMona_FactoryTrade();
		break;
		
		case "Himenes_church":
			dialog.text = "Ah! Capitano, temo che costruire altro sarebbe solo una follia inutile e uno spreco di dobloni. A meno che...";
			link.l1 = "A meno di cosa?";
			link.l1.go = "Himenes_church_1";
		break;
		
		case "Himenes_church_1":
			dialog.text = "Capitano, mi imbarazza chiedere una cosa simile... Hai già speso un bel gruzzolo in questo posto!";
			link.l1 = "Un bordello?";
			link.l1.go = "Himenes_church_2_1";
			link.l2 = "Una chiesa?";
			link.l2.go = "Himenes_church_2_2";
		break;
		
		case "Himenes_church_2_1":
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			dialog.text = "Lo giuro su San Santiago, non sarebbe affatto male! Ma già la prima notte, le nostre donne lo darebbero alle fiamme. E noi insieme. No, capitano, parlo d'una chiesa. Sì, abbiamo alloggio decente e paga, il mare e i passatempi, famiglie e amici. Ma manca ancora qualcosa, capisce?";
			link.l1 = "Me lo posso ben immaginare.";
			link.l1.go = "Himenes_church_3";
		break;
		
		case "Himenes_church_2_2":
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			AddCharacterExpToSkill(pchar, "Defence", 500);
			dialog.text = "Mi leggi dentro, capitano. Sì, abbiamo una buona sistemazione e paga, il mare e un po’ di svago, famiglie e amici. Eppure, qualcosa manca, capisci?";
			link.l1 = "Posso immaginare.";
			link.l1.go = "Himenes_church_3";
		break;
		
		case "Himenes_church_3":
			dialog.text = "Esatto. Non possiamo innalzare la Casa di Dio senza il tuo aiuto. Un luogo simile dev’essere speciale, quasi ultraterreno. E dunque, ci vorrà un bel gruzzolo. Serviranno candele, lingotti d’oro, ambra, e ovviamente materiali da costruzione – ma niente robaccia da due soldi. Non ti porterà alcun guadagno, quindi non oso chiedere.";
			link.l1 = "Dunque, hai bisogno di portare qui un prete?";
			link.l1.go = "Himenes_church_4";
		break;
		
		case "Himenes_church_4":
			dialog.text = "No.";
			link.l1 = "Avete già un prete tra voi?";
			link.l1.go = "Himenes_church_5";
		break;
		
		case "Himenes_church_5":
			dialog.text = "No, capitano. E credo che tu abbia già capito tutto.";
			link.l1 = "Dunque, avevano motivo i santi padri dell’Inquisizione di perseguitarvi? Siete forse degli eretici?";
			link.l1.go = "Himenes_church_6";
		break;
		
		case "Himenes_church_6":
			dialog.text = "Secondo le leggi canoniche, siamo i peggiori degli eretici. Non crediamo che per parlare con Dio serva per forza un intermediario terreno.";
			link.l1 = "Di questo mondo?";
			link.l1.go = "Himenes_church_7";
		break;
		
		case "Himenes_church_7":
			dialog.text = "Capitano, noi non siamo satanisti, né la nostra comunità è una setta. Siamo cristiani, come voi, ma guardiamo alle cose con una mente molto aperta. Troppo aperta, secondo certi uomini assai dotti e rispettabili. Se mai troverete nel vostro cuore un po' di apertura e comprensione, allora vi dirò di più. Ma per ora, prendete questa lista. Non si sa mai.";
			link.l1 = "Dovevi dirmelo prima, Rodrigo. Non voglio tornare un bel giorno e trovare un sabba di streghe o la nascita d’una nuova fede sulle mie terre! Mentre aspetti – prenderò una decisione.";
			link.l1.go = "Himenes_church_8_1";
			link.l2 = "Lista impressionante. Comincio a capire perché i santi padri hanno bisogno di tanto oro! Rifletterò sulla tua offerta, Rodrigo, e prenderò una decisione.";
			link.l2.go = "Himenes_church_8_2";
		break;
		
		case "Himenes_church_8_1":
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
			dialog.text = "";
			link.l1 = "Se la risposta è favorevole, porterò tutte le merci della tua lista al magazzino e ti stenderò i tesori sul tavolo.";
			link.l1.go = "Himenes_church_9";
		break;
		
		case "Himenes_church_8_2":
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			dialog.text = "";
			link.l1 = "Se va tutto liscio, porterò tutta la mercanzia della tua lista nel magazzino, e ti spargerò i tesori sul tavolo.";
			link.l1.go = "Himenes_church_9";
		break;
		
		case "Himenes_church_9":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			pchar.questTemp.IslaMona.Church = "start";
			AddQuestRecord("IslaMona", "14");
			AddQuestRecordInfo("IslaMonaData", "3");
		break;
		
		case "Himenes_church_10":
			dialog.text = "A nome di tutta la nostra comunità, vi ringrazio, capitano. Non ve ne pentirete, lo giuro!";
			link.l1 = "Me ne pentirò solo se tirerai su una baracca da quattro soldi.";
			link.l1.go = "Himenes_church_10_1";
		break;
		
		case "Himenes_church_10_1":
			dialog.text = "Capitano, tutti i materiali da costruzione sono pronti! Inizieremo i lavori appena porterai i beni di lusso richiesti. Serviranno per gioielli e strumenti rituali. Ancora una volta, grazie di cuore, Capitano! Muchas gracias!";
			link.l1 = "Di nulla, compare!";
			link.l1.go = "Himenes_church_10_2";
		break;
		
		case "Himenes_church_10_2":
			DialogExit();
			IslaMona_RemoveChurch();
			npchar.dialog.currentnode = "Himenes_72";
			pchar.questTemp.IslaMona.Church = "Wait_candles";
			pchar.questTemp.IslamonaChurch.GoldNugget = 50;
			pchar.questTemp.IslamonaChurch.Candle = 100;
			pchar.questTemp.IslamonaChurch.Amber = 30;
			pchar.questTemp.IslamonaChurch.BlueAmber = 1;
		break;
		
		case "Himenes_church_10_3":
			IslaMona_RemoveCandles();
			string sAdd = "";
			if(CheckAttribute(pchar, "questTemp.IslamonaChurch.Candle"))
			{
				sAdd += " "+sti(pchar.questTemp.IslamonaChurch.Candle)+ " candles,"
			}
			if(CheckAttribute(pchar, "questTemp.IslamonaChurch.Amber"))
			{
				sAdd += " "+sti(pchar.questTemp.IslamonaChurch.Amber)+ " amber,"
			}
			if(CheckAttribute(pchar, "questTemp.IslamonaChurch.GoldNugget"))
			{
				sAdd += " "+ sti(pchar.questTemp.IslamonaChurch.GoldNugget) + " ingots,"
			}
			if(CheckAttribute(pchar, "questTemp.IslamonaChurch.BlueAmber"))
			{
				sAdd += " and one blue amber"
			}
			if(sAdd == "")
			{
				dialog.text = "Mille grazie, capitano! Tutto è pronto, iniziamo i lavori. Torna tra un paio di mesi per la prima messa. Ah, e un'altra cosa, l'uva è matura! Faremo vino fatto in casa, ci sarà una gran festa e banchetteremo in tuo onore!";
				link.l1 = "Penso che tutti noi meritiamo una bella festa. Tornerò tra due mesi.";
				link.l1.go = "Himenes_church_12";
			}
			else
			{
				dialog.text = "Capitano, ce ne sono ancora "+sAdd+" rimasto.";
				link.l1 = "Certo, solo dammi ancora un po' di tempo, per favore. A dire il vero, se non fosse per queste candele, penserei che tu stia per seppellire un tesoro.";
				link.l1.go = "Himenes_church_11";
			}
		break;
		
		case "Himenes_church_11":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
		break;
		
		case "Himenes_church_12":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			pchar.questTemp.IslaMona.Church = "build";
			AddQuestRecord("IslaMona", "15");
			//IslaMona_RemoveChurch();
			SetFunctionTimerCondition("IslaMona_ChurchComplete", 0, 0, 60, false);
		break;
		
		case "Himenes_church_13":
			dialog.text = "Ah-ah-ah-ah-ah-ah-ah-ah-ah-ah-ah!";
			link.l1 = "E io che pensavo ti fossi sbarazzato di quella stupida abitudine.";
			link.l1.go = "Himenes_church_14";
		break;
		
		case "Himenes_church_14":
			sld = characterFromId("Islamona_carpenter");
			i = sti(sld.crew.qty);
			if (i >= 50) sTemp = "that we won't have to sit here for weeks waiting for events to unfold.";
			else sTemp = "that not everyone will have to participate in the battle.";
			dialog.text = "Ah-ah-ah-ah-ah... ah. Lo pensavo anch’io, capitano! Rodgar ha ragione, il fatto che tu sia qui già significa, "+sTemp+"";
			link.l1 = "So già cos’è successo. Ci sono state vittime?";
			if (GetCharacterIndex("Mirabella") != -1) link.l1.go = "Himenes_church_15";
			else link.l1.go = "Himenes_church_16";
		break;
		
		case "Himenes_church_15":
			DialogExit();
			sld = characterFromId("Mirabella"); 
			sld.dialog.currentnode = "mirabelle_44";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_church_16":
			dialog.text = "Non crucciarti troppo, Rodgar. Non è colpa tua, i fucilieri sono piombati su di noi in un lampo. Tanto non saremmo riusciti a trattenerli dietro le nostre linee, e non c’era tempo per passarli tutti a fil di spada.";
			link.l1 = "E che ne dici degli Spagnoli?";
			link.l1.go = "Himenes_church_17";
		break;
		
		case "Himenes_church_17":
			sld = characterFromId("Islamona_carpenter");
			i = sti(sld.crew.qty);
			if (CheckAttribute(pchar, "questTemp.IslaMona.Defend.Force")) // решил проблему самостоятельно
			{
				dialog.text = "Solo tre di loro sono arrivati da noi, e solo uno è sopravvissuto. Il capitano in persona! Sembra proprio un vero lupo di mare, di quelli tosti e navigati. Ma per ora non ci può aiutare – dovrà restarsene a letto almeno un paio di giorni ancora. Ah, capitano, abbiamo sentito degli spari e a giudicare dal tuo aspetto, pure tu ne hai avuto la tua parte.";
				link.l1 = "Potresti dirlo. Quei maledetti scrocconi non si aspettavano di essere colti alla sprovvista e sono stati ributtati a mollo.";
				link.l1.go = "Himenes_church_20";
			}
			else
			{
				dialog.text = "Solo tre di loro sono arrivati fino a noi, e soltanto uno è sopravvissuto. Il capitano in persona! A quanto pare, un vero lupo di mare, uno di quelli tosti della marina. Ma per ora non ci può dare una mano – dovrà restarsene a letto ancora per almeno un paio di giorni.";
				if (i >= 50) 
				{
					link.l1 = "L'ultima volta ho lasciato qui un bel po' della mia ciurma di guardia, quindi dovreste essere molti più dei fucilieri. Perché non li avete rispediti tutti dritti in mare, in una volta sola?";
					link.l1.go = "Himenes_church_17_1";
				}
				else 
				{
					link.l1 = "Bene, risolviamo questa faccenda. Ecco il piano: li attirerò fuori per uno scontro aperto, e lo faccio subito. Non c’è ragione di perdere tempo. Preparate pallettoni e moschetti, i filibustieri alle porte, gli altri restino alle case – e che nessuno si muova.";
					link.l1.go = "Himenes_church_18";
				}
			}
		break;
		
		case "Himenes_church_17_1":
			dialog.text = "Capo, quelli son tutti soldati navigati, con un comandante vero e proprio. E noi? Nemmeno abbiamo armi degne di questo nome. Sì, certo, col numero potremmo travolgerli, ma ci lasceremmo almeno il doppio degli uomini, e ognuno qui vale oro e ci serve come il pane.";
			link.l1 = "Bene, risolviamo questa faccenda. Il piano è questo: li attirerò fuori per un assalto aperto, e lo faccio ora. Non ha senso perdere tempo. Preparate pallettoni e moschetti, i pirati alle porte, gli altri restano in casa – e che nessuno si muova.";
			link.l1.go = "Himenes_church_18";
		break;
		
		case "Himenes_church_18":
			dialog.text = "Capitano, siamo pronti a combattere!";
			link.l1 = "Lo so, Rodrigo. Ma non m’hai lasciato finire: se anche solo un nemico riesce a sfondare i cancelli, dovete tutti piombargli addosso da ogni lato. E in battaglia, le tue probabilità di beccarti una palla o una scheggia si fanno più piccole. Altre domande?";
			link.l1.go = "Himenes_church_19";
		break;
		
		case "Himenes_church_19":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_68";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_church_20":
			dialog.text = "Ben fatto! Certo, è una sfortuna che un destino così crudele sia toccato ai tuoi compatrioti. Ma ti sono grato che ancora una volta tu abbia scelto di stare dalla nostra parte.";
			link.l1 = "Non è stato facile, Rodrigo. La gente normale lo chiamerà tradimento, e avranno ragione.";
			link.l1.go = "Himenes_church_20_1";
			link.l2 = "Questa è la mia terra, Rodrigo. Va difesa sempre, da chiunque osi minacciarla.";
			link.l2.go = "Himenes_church_20_2";
		break;
		
		case "Himenes_church_20a":
			dialog.text = "Sì, il vecchio Rodrigo non si sarebbe mai aspettato, quando lasciò Cadice, che simili avventure lo attendessero nel Nuovo Mondo.";
			link.l1 = "Non dirmelo. A volte ho ancora proprio gli stessi pensieri.";
			link.l1.go = "Himenes_church_20b";
		break;
		
		case "Himenes_church_20b":
			dialog.text = "È spiacevole, certo, che una sorte tanto nefasta sia toccata ai tuoi compatrioti. Ma ti sono grato che anche stavolta tu abbia scelto di stare dalla nostra parte.";
			link.l1 = "Non fu facile, Rodrigo. La gente comune lo chiamerebbe tradimento, e avrebbero ragione.";
			link.l1.go = "Himenes_church_20_1";
			link.l2 = "Questa è la mia terra, Rodrigo. Va difesa sempre, non importa da chi.";
			link.l2.go = "Himenes_church_20_2";
		break;
		
		case "Himenes_church_20_1":
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			dialog.text = "Capisco, capitano. Permettetemi allora di darvi un rapido resoconto su com’è andata nella nostra colonia durante la vostra assenza.";
			link.l1 = "Davvero? Aspetta un attimo... Capitano?";
			link.l1.go = "Himenes_church_21";
		break;
		
		case "Himenes_church_20_2":
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			dialog.text = "Comprendo, capitano. Permettetemi dunque di darvi un rapido resoconto della situazione nel nostro insediamento durante la vostra assenza.";
			link.l1 = "Davvero? Aspetta un po'... Capitano?";
			link.l1.go = "Himenes_church_21";
		break;
		
		case "Himenes_church_21":
			dialog.text = "Non volevo offendere. È solo che Rodgar pronuncia quella parola in modo così succulento che ho voluto provarci anch’io. Davvero... da vero pirata.";
			link.l1 = "Nessun problema, solo che mi hai sorpreso. Allora, che diavolo è successo qui?";
			link.l1.go = "Himenes_church_22";
		break;
		
		case "Himenes_church_22":
			dialog.text = "Prima di tutto, abbiamo costruito la chiesa. Ci vorrà un attimo, entra. C’è qualcosa che devi vedere. Hai compiuto una grande impresa, capitano. Forse non te ne rendi conto, ma poter parlare con Dio è cosa assai, assai preziosa per noi. Da oggi, Isla Mona sarà la nostra dimora.";
			link.l1 = "Casa dolce casa? Ehi, ci darò senz’altro un’occhiata. Non vorrei aver trascinato tutte quelle candele per niente!";
			link.l1.go = "Himenes_church_23";
		break;
		
		case "Himenes_church_23":
			dialog.text = "Non per niente! In secondo luogo, la fabbrica è andata in rovina – abbiamo perso tutta la manovalanza. Dovrai procurarti una nuova partita di schiavi. Fortunatamente, dopo aver rivalutato l’efficienza del lavoro, abbiamo concluso che dieci schiavi saranno più che sufficienti. Quindi, meno grane per te.";
			link.l1 = "D'accordo. C'è altro?";
			link.l1.go = "Himenes_church_24";
		break;
		
		case "Himenes_church_24":
			dialog.text = "Tutto è pronto per la festa. Beh, quasi: dobbiamo sistemare qui, seppellire i corpi di quei poveri disgraziati... Dunque, vieni in chiesa domani e daremo inizio.";
			link.l1 = "In chiesa? Strano posto per iniziare la baldoria. Hai forse intenzione di chiedere la mano, Rodrigo?";
			link.l1.go = "Himenes_church_25";
		break;
		
		case "Himenes_church_25":
			dialog.text = "Ah-ah! No, capitano, benché alcune delle nostre ragazze non ci sputerebbero sopra. A noi non dà fastidio se lo fai tu.";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1 && IsOfficer(characterFromId("Mary")))
			{
				link.l1 = "";
				link.l1.go = "Himenes_church_25_1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1 && IsOfficer(characterFromId("Helena")))
				{
					link.l1 = "";
					link.l1.go = "Himenes_church_25_2";
				}
				else
				{
					link.l1 = "D’accordo, domani verremo in chiesa. A pregare, s’intende.";
					if (CheckAttribute(pchar, "questTemp.IslaMona.Defend.Common") || CheckAttribute(pchar, "questTemp.IslaMona.Defend.Force")) link.l1.go = "Himenes_church_28";
					else link.l1.go = "Himenes_church_26";
				}
			}
		break;
		
		case "Himenes_church_25_1":
			DialogExit();
			sld = characterFromId("Mary");
			sld.dialog.currentnode = "IslaMona";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_church_25_2":
			DialogExit();
			sld = characterFromId("Helena");
			sld.dialog.currentnode = "IslaMona";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_church_26":
			dialog.text = "E ancora una cosa, capitano. Prima dei festeggiamenti, vai a sistemare la faccenda del prigioniero. Bisogna prendere una decisione, e capisco che sarà spiacevole in ogni caso.";
			link.l1 = "D'accordo. Ci vado subito.";
			link.l1.go = "Himenes_church_27";
		break;
		
		case "Himenes_church_27":
			DialogExit();
			DoQuestReloadToLocation("IslaMona_factoria", "reload", "reload1", "IslaMona_DefFraPrisoner"); /// ОПРЕДЕЛИТЬ ЛОКАТОР
		break;
		
		case "Himenes_church_28":
			DialogExit();
			WaitDate("", 0, 0, 0, 3, 5); //крутим время
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			IslaMona_DefBattleLightClear();
			DoQuestReloadToLocation("IslaMona_town", "quest", "detector1", "");
		break;
		
		case "Himenes_church_29":
			dialog.text = "Siamo tutti qui! Señor, non sappiamo cosa voleste davvero da questo posto all’inizio, né come lo vedete ora. Per noi era un rifugio forzato, adesso è diventato una vera casa. Qui vivono i vostri marinai, pirati e eretici spagnoli in fuga. Altrove ci saremmo già sgozzati a vicenda, ma qui siam compagni, lavoriamo e ci godiamo la vita. Isla Mona non è la meta finale sulla mappa di nessuno di noi, eppure forse qui passeremo gli anni più felici e ricchi delle nostre vite. Questo è merito vostro: la vostra terra, la vostra gente. Muchas gracias, "+pchar.name+"!";
			link.l1 = "";
			link.l1.go = "Himenes_church_30";
			locCameraFromToPos(-4.11, 1.55, 1.09, true, -4.55, -0.20, 3.08);
		break;
		
		case "Himenes_church_30":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_86";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.0);
		break;
		
		case "Himenes_church_31":
			dialog.text = "D'accordo, d'accordo. Capitano, abbiamo raccolto dei doni per voi – una moltitudine di cose utili e gradevoli. Alcune le abbiamo portate con noi, altre le abbiamo fabbricate con le nostre mani. Accettate questo dono con cuore sincero, e il resto ve lo offriremo col nostro duro lavoro.";
			link.l1 = "Grazie... Non me l’aspettavo. Così pochi momenti luminosi e gesti d’umanità in questa mia odissea... Significa molto per me, credimi.";
			link.l1.go = "Himenes_church_32";
			locCameraFromToPos(-4.11, 1.55, 1.09, true, -4.55, -0.20, 3.08);
		break;
		
		case "Himenes_church_32":
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "GunEchin", 10);
			TakeNItems(pchar, "slave_01", 10);
			TakeNItems(pchar, "grenade", 10);
			TakeNItems(pchar, "obereg_7", 1);
			TakeNItems(pchar, "purse3", 1);
			TakeNItems(pchar, "jewelry47", 1);
			TakeNItems(pchar, "jewelry52", 1);
			TakeNItems(pchar, "berserker_potion", 1);
			TakeNItems(pchar, "potion5", 10);
			TakeNItems(pchar, "cannabis7", 1);
			dialog.text = "E ora - al lavoro!";
			link.l1 = "No, ora si va - in taverna! Rodrigo, andiamo!";
			link.l1.go = "Himenes_church_33_1";
			link.l2 = "Sì, godiamoci ancora un po’ questo momento magnifico.";
			link.l2.go = "Himenes_church_33_2";
		break;
		
		case "Himenes_church_33_1":
			DialogExit();
			DoQuestReloadToLocation("IslaMona_Town", "sit", "sit_base2", "IslaMona_ChurchToTavern"); /// ОПРЕДЕЛИТЬ ЛОКАТОР
		break;
		
		case "Himenes_church_33_2":
			DialogExit();
			LAi_SetActorType(pchar);
			ChangeShowIntarface();
			ResetSound();
			SetMusic("music_terrain");
			InterfaceStates.Buttons.Save.enable = false;
			bDisableCharacterMenu = true;
			pchar.GenQuest.FrameLockEsc = true;
			locCameraRotateAroundHero(0.0, 1.5, 0.0, 0.005, 0.0, 1.5, 0.0, 10000);
			Pchar.FuncCameraFly = "";
			DoQuestCheckDelay("IslaMona_ChurchTavernExit", 45.0);
		break;
		
		case "Himenes_74":
			dialog.text = "Ah-ah! Hic!";
			link.l1 = "A proposito, vedo che hai quasi smesso di ridere come un matto senza motivo. Sarà l’aria fresca dei Caraibi?";
			link.l1.go = "Himenes_75";
		break;
		
		case "Himenes_75":
			dialog.text = "Direi piuttosto la pessima influenza di Rodgar. A forza di guardarlo, ho imparato a mandar tutto al diavolo.";
			link.l1 = "";
			link.l1.go = "Himenes_76";
		break;
		
		case "Himenes_76":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_90";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_77":
			dialog.text = "Conosco molti gentiluomini rispettabili da quelle parti.";
			link.l1 = "";
			link.l1.go = "Himenes_78";
		break;
		
		case "Himenes_78":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_93";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_79":
			dialog.text = "No, preferisco continuare a tracannare rum e fissarti di brutto.";
			link.l1 = "";
			link.l1.go = "Himenes_80";
		break;
		
		case "Himenes_80":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_96";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_81":
			dialog.text = "Capitano! Hic!";
			link.l1 = "Salute anche a te, Rodrigo. Sembra che la notte sia stata movimentata, eh?";
			link.l1.go = "Himenes_82";
		break;
		
		case "Himenes_82":
			dialog.text = "Meglio... non chiedere. Un mese... senza bere. Oh. Ho delle novità! Il capitano... ha ritrovato la ragione.";
			link.l1 = "L’unico spagnolo scampato?";
			link.l1.go = "Himenes_83";
		break;
		
		case "Himenes_83":
			dialog.text = "Hic! Ahi! Sì, l’hanno ficcato nella factoria, in una casa sorvegliata.";
			link.l1 = "D'accordo. Andrò da lui. Fa' attenzione a non esagerare.";
			link.l1.go = "Himenes_84";
		break;
		
		case "Himenes_84":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10); /// ОН ИДЕТ НА ВЫХОД, ПОСТАВИТЬ ПРАВИЛЬНЫЙ ЛОКАТОР
			IslaMona_ChurchSetHispanos();
		break;
		
		case "Himenes_85":
			dialog.text = "Mi sono fatto una nuotata e ora sto come nuovo! Vivremo e lavoreremo. Cercherò di mandare avanti la factoría finché potrò. E poi, farò qualche riparazione, qualche lavoretto qua e là. Magari, chissà, decideremo pure di metter su famiglia.";
			link.l1 = "Felice per tutti voi! È stata un’avventura nervosa, dispendiosa... e meravigliosa, e sono lieto che sia finita bene per noi. Buona fortuna a tutti, e a chi prende il largo, che gli Dei del mare siano ancor più propizi!";
			link.l1.go = "Himenes_86";
		break;
		
		case "Himenes_86":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "IslaMona_Final", -1);
			sld = characterFromId("Islamona_carpenter");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
		break;
		
		// солдат в бухте
		case "Capral":
			dialog.text = "Altolà! Caporale "+GetFullName(npchar)+". Siete sbarcati in una zona di battaglia! Dichiarate subito chi siete e spiegate cosa vi porta qui!";
			if (CheckCharacterItem(pchar, "patent_fra"))
			{
				link.l1 = "Caporale, a riposo! "+GetFullName(pchar)+", capitano della Marina Francese. Vi ordino di scortarmi dal vostro superiore. Eseguite l’ordine!";
				link.l1.go = "Capral_1";
			}
			else
			{
				link.l1 = ""+GetFullName(pchar)+", capitano della nave chiamata '"+pchar.ship.name+"'. Sono sbarcato su quest’isola per puro caso – per riparazioni e per rifornire la cambusa d’acqua fresca.";
				link.l1.go = "Capral_3";
			}
		break;
		
		case "Capral_1":
			if(IsUniformEquip())
			{
				dialog.text = "Sissignore, Capitano! Seguitemi, vi prego. Ma fate attenzione! Quest’isola pullula di mascalzoni.";
				link.l1 = "";
			}
			else
			{
				dialog.text = "Chiedo venia, Capitano. Non indossate la divisa, dunque sono tenuto a controllare il vostro brevetto d’ufficiale.";
				link.l1 = "Visto. Soddisfatto? Ora sbrigati a eseguire l’ordine, caporale!";
			}
			link.l1.go = "Capral_2";
		break;
		
		case "Capral_2":
			DialogExit();
			AddQuestRecord("IslaMona", "16");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "IslaMona_DefReloadFactory", 20.0);
		break;
		
		case "Capral_3":
			dialog.text = "Dovrete venire con me, Capitano. Il nostro superiore desidera parlarvi. Da questo momento, la vostra nave è temporaneamente requisita al servizio della Marina Francese. Avvisate subito la guardia di bordo e seguitemi.";
			link.l1 = "Requisire la nave Charle Prince? Non ci penso nemmeno, maledizione!";
			link.l1.go = "Capral_5";
			link.l2 = "Sembra che non abbia scelta. Farò come dici tu.";
			link.l2.go = "Capral_4";
		break;
		
		case "Capral_4":
			DialogExit();
			AddQuestRecord("IslaMona", "18");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "IslaMona_DefReloadFactory", 5.0);
		break;
		
		case "Capral_5":
			DialogExit();
			DoQuestFunctionDelay("IslaMona_DefKillCapral", 1.0);
		break;
		
		case "Capral_6":
			if (CheckCharacterItem(pchar, "patent_fra"))
			{
				dialog.text = "Mastro Capitano, il sentiero verso l'accampamento nemico è alla nostra destra. Vi scorterò.";
				link.l1 = "Fermati, caporale. Preferisco andare da solo.";
			}
			else
			{
				dialog.text = "Capitano, il sentiero verso l'accampamento nemico è sulla nostra destra. Non ti smarrirai.";
				link.l1 = "Ti ringrazio per la premura.";
			}
			link.l1.go = "Capral_7";
		break;
		
		case "Capral_7":
			DialogExit();
			chrDisableReloadToLocation = false;
			IslaMona_DefGotoMarch();
			pchar.quest.islamona_def_killslaves.win_condition.l1 = "location";
			pchar.quest.islamona_def_killslaves.win_condition.l1.location = "IslaMona_town";
			pchar.quest.islamona_def_killslaves.function = "IslaMona_DefKillSlaves";
		break;
		
		case "FraOfficer":
			if (CheckCharacterItem(pchar, "patent_fra"))
			{
				dialog.text = "Capitano "+GetFullName(pchar)+"! Grazie al cielo! Permettete che mi presenti – Tenente "+GetFullName(npchar)+"Un grande ammiratore vostro! Non so che ci fate su questa miserabile zolla di terra, ma arrivate proprio al momento giusto!\nDevo dire, Capitano, che siete diventato assai popolare tra i nostri ufficiali. Sebbene molti siano infastiditi dal vostro... ‘peculiare’ modo di servire, tutti concordano che la vostra patente rende la nostra flotta più gagliarda. Al momento siamo in un vero stallo, quindi l’aiuto di uno come voi è una manna che non si può misurare!";
				link.l1 = "Cosa posso fare? E che diavolo succede qui?";
				link.l1.go = "FraOfficer_1";
			}
			else
			{
				dialog.text = "Capitano "+GetFullName(pchar)+". Il tuo nome è stato menzionato più volte nei rapporti della flotta. E sempre in termini piuttosto loschi. Tuttavia, adesso hai l'opportunità di interrompere questa tendenza poco onorevole e servire la madrepatria.";
				link.l1 = "Cosa posso fare? E che diavolo succede qui?";
				link.l1.go = "FraOfficer_8";
			}
		break;
		
		case "FraOfficer_1":
			dialog.text = "Eravamo sulla 'Guerriero', una missione di routine – dare la caccia a quei dannati razziatori spagnoli troppo audaci. In genere è tutto semplice: la spia ti passa la zona e i dati sul bersaglio, e tu li becchi prima che vedano la tua vela sull’orizzonte. Nulla di degno di nota, e invece è finita in modo disastroso: furono gli spagnoli a trovarci per primi e ci assalirono, e dire che pure loro erano su una corvetta. Se avessimo avuto qualcosa di più tosto, non saremmo andati a fondo con la nave... ma almeno siamo riusciti a far saltare il loro scafo in mille pezzi. Solo la mia ciurma si è salvata. Anche tra i castigliani qualcuno sopravvisse. Ma non per molto, ahah!";
			if (CheckAttribute(pchar, "questTemp.IslamonaSpaOfficer"))
			{
				link.l1 = "La fregata 'Warrior'? Il capitano Shocke è morto?";
				link.l1.go = "FraOfficer_1_1";
			}
			else
			{
				link.l1 = "";
				link.l1.go = "FraOfficer_2";
			}
		break;
		
		case "FraOfficer_1_1":
			dialog.text = "Non mi stupisce che tu abbia chiesto di lui, Capitano. Ho sentito della tua partecipazione all’intercettazione dell’‘Alcantara’. Un’impresa degna, già allora gettavi le basi per la tua patente! Il comandante Shocke non è morto, tutt’altro! È stato promosso, e su sua richiesta, mandato a servire nel Mediterraneo. Non ci resta che invidiarlo, visto come stiamo messi ora. Ma, tornando a noi e alla nostra situazione...";
			link.l1 = "";
			link.l1.go = "FraOfficer_2";
		break;
		
		case "FraOfficer_2":
			dialog.text = "Abbiamo trovato un insediamento sull’isola – una vera e propria tana affollata di furfanti, ascolta bene: pirati e spagnoli insieme! Incredibile, eh? Di solito quei bastardi si squartano e si impiccano a vicenda, ma qui – guarda un po’ – proprio nel cuore dell’arcipelago, lavorano come una famiglia per tagliare il legname dei bucanieri. Hai visto il molo che si sono costruiti? Non arrivano ospiti di questa razza su scialuppe, te lo dico io. Il nostro compito è cristallino: col tuo aiuto prendiamo l’insediamento, ci portiamo via il legname e i prigionieri, e tu conduci tutti a Capsterburg. Intanto le autorità si scervelleranno tra loro... E finché si scervellano, noi facciamo sparire quel legname e festeggiamo come si deve con gli altri ufficiali del mio squadrone!";
			link.l1 = "Che cosa ti ha impedito finora di prendere il controllo dell’insediamento da solo?";
			link.l1.go = "FraOfficer_3";
		break;
		
		case "FraOfficer_3":
			sld = characterFromId("Islamona_carpenter");
			i = sti(sld.crew.qty);
			if (i >= 50) sTemp = "There are probably many more bandits than us - we saw tents on the shore. And besides tents, they also have a wall, gates, cannon!";
			else sTemp = "There are probably not so many bandits, otherwise they would have kicked us out of here already, but they still have a wall, gates, cannon and plenty of time!";
			dialog.text = "Che cosa ci ha fermati?! Abbiamo solo dodici fucilieri e sette marinai. Tutti sfiniti e a pezzi. Siamo riusciti a salvare solo cinque moschetti, e al massimo una cartuccia ciascuno!"+sTemp+"";
			link.l1 = "Ma hai già una rotta in testa?";
			link.l1.go = "FraOfficer_4";
		break;
		
		case "FraOfficer_4":
			dialog.text = "Ascolta, non abbiamo perso tempo. Prima di tutto, ci siamo impossessati di questa fabbrica, così abbiamo messo le mani su un po’ di provviste e acqua, e soprattutto – un magazzino pieno di legno da bucanieri e più di una dozzina di schiavi! Tanto non avremmo potuto sorvegliarli comunque, quindi li abbiamo subito mandati all’attacco dei loro vecchi padroni sotto la copertura dei nostri moschetti. Così abbiamo scoperto che quei furfanti avevano delle armi nascoste.";
			link.l1 = "Ho capito bene che ora vuoi mandare me e i miei uomini a occuparci di quest’arma al posto degli schiavi?";
			link.l1.go = "FraOfficer_5";
		break;
		
		case "FraOfficer_5":
			dialog.text = "No, ma puoi presentarti ai banditi per trattare. Il tuo arrivo vuol dire che il loro covo è ormai scoperto, e adesso i soldati del re hanno nave e rinforzi. Dunque, mentre quelli staranno a orecchiare e a misurare la loro sventura, tu avvicinati più che puoi al cannone, lancia una bomba a mano sotto, e non farti ammazzare finché i nostri e i tuoi non saranno lì. Se non ti senti all’altezza, prova a mandare uno dei tuoi uomini al posto tuo.";
			link.l1 = "Prima lasciami andare da loro senz'armi e proporre la resa. Scruterò il loro animo, capirò che vento tira e seminerò dubbi nei loro cuori. Se non si arrendono, tornerò, ma stavolta con la bomba.";
			if (CheckCharacterItem(pchar, "patent_fra")) link.l1.go = "FraOfficer_6";
			else link.l1.go = "FraOfficer_6_1";
		break;
		
		case "FraOfficer_6":
			GiveItem2Character(pchar, "grenade");
			//Log_Info("Вы получили гранату");
			PlaySound("interface\important_item.wav");
			dialog.text = "... e a quel punto, saranno già abituati a te, così sarà più facile mandare tutto a monte! Astuto! Beh, non mi aspettavo niente di meno da te, Capitano. Procedi quando ti senti pronto. Ma aspetta, prendi questo... Potrebbe tornarti utile.";
			link.l1 = "";
			link.l1.go = "FraOfficer_7";
		break;
		
		case "FraOfficer_6_1":
			dialog.text = "... e a quel punto, si saranno già abituati a te, quindi sarà più facile portare a termine il sabotaggio. Questo è il nostro piano. Avanti, allora!";
			link.l1 = "";
			link.l1.go = "FraOfficer_7";
		break;
		
		case "FraOfficer_7":
			DialogExit();
			AddQuestRecord("IslaMona", "19");
			chrDisableReloadToLocation = false;
			pchar.quest.islamona_def_goout.win_condition.l1 = "location";
			pchar.quest.islamona_def_goout.win_condition.l1.location = "IslaMona_Jungle_01";
			pchar.quest.islamona_def_goout.function = "IslaMona_DefCapralTalk";
		break;
		
		case "FraOfficer_8":
			dialog.text = "In questa zona c’è stata una lunga battaglia coi maledetti spagnoli. Entrambe le navi sono affondate, e i superstiti sono finiti qui. Perlopiù francesi, ma anche alcuni dei nostri nemici sono riusciti a scamparla. E non serve che tu sappia altro, mi spiace, Capitano. Informazioni segrete, capisci.";
			link.l1 = "Inteso.";
			link.l1.go = "FraOfficer_9";
		break;
		
		case "FraOfficer_9":
			dialog.text = "Abbiamo trovato un insediamento sull’isola — una vera e propria tana di filibustieri, popolata da — senti qua — pirati e spagnoli insieme. Da non credere! Di solito questi cani si sventrano a vicenda, invece qui — guarda un po’: nel cuore stesso dell’arcipelago, lavorano gomito a gomito come fratelli per tagliare il legno dei bucanieri. Hai visto il molo che si sono costruiti? Non è certo un posto dove la gente arriva con la scialuppa. Il compito nostro è limpido come l’acqua: con il tuo aiuto prendiamo il villaggio, ci pigliamo il legname e i prigionieri, e tu porti tutti a Capsterburg. Intanto le autorità si scervelleranno da sole su come sistemare le cose... E mentre rimuginano, potrei anche lasciarti prendere un po’ di legname pregiato per i tuoi bisogni.";
			link.l1 = "Che cosa ti ha impedito di prendere il villaggio da solo fino ad ora?";
			link.l1.go = "FraOfficer_3";
		break;
		
		case "FraOfficer_10":
			dialog.text = "Eccoti qui! Novità in vista?";
			link.l1 = "È questa una guardia d’onore?";
			link.l1.go = "FraOfficer_11";
		break;
		
		case "FraOfficer_11":
			dialog.text = "Ovviamente, a breve si prenderà una decisione su come muoverci. Non vorrei dover cercare la mia ciurma per tutta l’isola solo per dare nuovi ordini.";
			if (CheckCharacterItem(pchar, "patent_fra"))
			{
				link.l1 = "Eccellente iniziativa! Riceverai i tuoi ordini. Ho fatto una ricognizione: il nemico è debole e il cannone è a secco di polvere. Ti ordino di attaccare subito il covo dei banditi, tenente. Basta cincischiare. Un altro giorno in flotta, nulla di nuovo. In marcia!";
				link.l1.go = "FraOfficer_12";
			}
			else
			{
				link.l1 = "A parer mio, li potevi prendere subito dopo la ricognizione degli 'schiavi', con la forza. La loro difesa fa ridere i polli, solo un paio di veri combattenti. Niente menate: potevamo già star bevendo vino di bottino seduti su una montagna di legno di ferro.";
				link.l1.go = "FraOfficer_14";
			}
		break;
		
		case "FraOfficer_12":
			dialog.text = "Affermativo, Capitano!";
			link.l1 = "...";
			link.l1.go = "FraOfficer_13";
		break;
		
		case "FraOfficer_13":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -25);
			AddQuestRecord("IslaMona", "22");
			IslaMona_DefAttackLight();
		break;
		
		case "FraOfficer_14":
			dialog.text = "E questi sarebbero i risultati della tua ricognizione? Capisco che forse è strano pretendere troppo da un civile, ma ho bisogno di fatti! Fatti, Capitano, non delle tue chiacchiere!";
			link.l1 = "Mi offendi, Tenente. Rapporto!";
			link.l1.go = "FraOfficer_15";
		break;
		
		case "FraOfficer_15":
			dialog.text = "";
			link.l1 = "Al momento, con te c'è un capitano superstite di una nave spagnola che hai affondato. Un comandante esperto che presto si rimetterà in sesto. Se cincischiamo, si riprenderà e organizzerà una difesa da manuale militare, e allora saranno dolori. Dobbiamo sbrigarci – te lo ripeto, adesso sono fiacchi e senza morale.";
			link.l1.go = "FraOfficer_15_1";
			link.l2 = "I rinforzi stanno arrivando presto – per prendersi il legname del bucaniere. Non credo sia una finta: hai visto coi tuoi occhi i moli e la catasta di merci pronte nel magazzino della fabbrica. Bisogna sbrigarci – te lo ripeto, sono deboli e senza spirito. Se perdi tempo, ti toccherà aspettare l’arrivo di una nave pirata.";
			link.l2.go = "FraOfficer_15_2";
			link.l3 = "Quasi la metà degli abitanti di questa tana sono donne. Non hai nemmeno combattuto contro la milizia: durante tutto questo tempo contro di te si sono alzati al massimo una dozzina di uomini. Sono deboli e senza più coraggio.";
			link.l3.go = "FraOfficer_15_3";
			link.l4 = "The cannon is out of ammunition. I've seen enough guns in my lifetime and can tell when a crew is ready to fire and when it's not. Without their artillery, they're nothing but poor warriors; they are weak and demoralized.";
			link.l4.go = "FraOfficer_15_4";
			link.l5 = "Pensa ai trofei e alla gloria, Tenente! Una vittoria in solitaria contro un corsaro spagnolo, la conquista di un covo di banditi e una fonte unica di legno da filibustiere – tutto ciò grida che devi comandare la tua nave! Te lo ripeto, sono deboli e senza morale, è l’ora di schiacciarli!";
			link.l5.go = "FraOfficer_15_5";
		break;
		
		case "FraOfficer_15_1":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 80)
			{
				notification("Skill Check Passed", SKILL_LEADERSHIP);
				dialog.text = "Grazie, Capitano. Queste sono notizie preziose, e avevi ragione, non c’è motivo di indugiare qui. I miei uomini sono tutti presenti, siamo forti, addestrati e pronti. Fra mezz’ora sarà tutto finito. Capitano, preparatevi a ricevere uomini, prigionieri e carico sulla vostra nave. Non ci fermeremo qui a lungo.";
				link.l1 = "Tutto è pronto, Tenente. Stavamo solo aspettando voi. Ci si rivede presto!";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				notification("Skill Check Failed (80)", SKILL_LEADERSHIP);
				dialog.text = "Grazie, Capitano. Queste sono notizie preziose. In tal caso, dirigiti al molo e raduna la tua squadra d’abbordaggio. Assalteremo il covo dei furfanti insieme, senza indugio. I migliori dei miei e dei tuoi uomini guideranno l’avanguardia – saranno loro a sfondare i cancelli. Il resto ne parleremo dopo aver passato in rassegna le truppe. Non deludere me né la tua patria, "+GetFullName(pchar)+".";
				link.l1 = "...Così sia. A presto, Tenente.";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_15_2":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 60 && sti(pchar.reputation.nobility) > 41)
			{
				notification("Reputation Check Passed", "None");
				notification("Skill Check Passed", SKILL_LEADERSHIP);
				dialog.text = "Grazie, Capitano. Questa è un’informazione preziosa, e avevi ragione, non c’è motivo di indugiare qui. I miei uomini sono tutti presenti, siamo forti, addestrati e pronti. Tutto sarà finito in mezz’ora. Capitano, preparatevi a ricevere gente, prigionieri e carico a bordo della vostra nave. Non ci fermeremo qui a lungo.";
				link.l1 = "Tutto è pronto, Tenente. Stavamo solo aspettando voi. Ci vediamo più tardi!";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				notification("Reputation Too Low! ("+XI_ConvertString(GetReputationName(42))+")", "None");
				notification("Skill Check Failed (60)", SKILL_LEADERSHIP);
				dialog.text = "Grazie, Capitano. Questa è un’informazione preziosa. Allora vai subito al molo e raduna la tua ciurma d’abbordaggio. Assalteremo il covo dei furfanti insieme, senza indugio. I migliori tra i miei e i tuoi uomini guideranno l’avanguardia – saranno loro a conquistare i cancelli. Il resto lo decideremo dopo aver passato in rassegna le nostre forze. Non deludere me né la tua patria, "+GetFullName(pchar)+".";
				link.l1 = "...Così sia. Ci vediamo più tardi, Tenente.";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_15_3":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 70 && sti(pchar.reputation.nobility) > 41)
			{
				notification("Reputation Check Passed", "None");
				notification("Skill Check Passed", SKILL_LEADERSHIP);
				dialog.text = "Grazie, Capitano. Questa è un'informazione preziosa, e avevate ragione, non c'è motivo di indugiare qui. I miei uomini sono tutti presenti, siamo forti, addestrati e pronti. Tutto finirà entro mezz'ora. Capitano, preparatevi ad accogliere gente, prigionieri e carico sulla vostra nave. Non ci tratterremo qui a lungo.";
				link.l1 = "Tutto è pronto, Tenente. Stavamo solo aspettando voi. A presto!";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				notification("Reputation Too Low! ("+XI_ConvertString(GetReputationName(42))+")", "None");
				notification("Skill Check Failed (70)", SKILL_LEADERSHIP);
				dialog.text = "Grazie, Capitano. Queste sono notizie preziose. Allora, vai subito al molo e prepara la tua squadra d’abbordaggio. Assalteremo insieme il covo dei furfanti, senza perdere tempo. I migliori dei miei e dei tuoi uomini guideranno l’avanguardia — loro prenderanno i cancelli. Il resto lo discuteremo dopo aver passato in rassegna le nostre forze insieme. Non deludere né me, né la tua patria, "+GetFullName(pchar)+".";
				link.l1 = "...Così sia. A presto, Tenente.";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_15_4":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 60 && sti(pchar.reputation.nobility) > 41)
			{
				notification("Reputation Check Passed", "None");
				notification("Skill Check Passed", SKILL_LEADERSHIP);
				dialog.text = "Grazie, Capitano. Questa è un'informazione preziosa, e avevate ragione, non c'è ragione di indugiare qui. I miei uomini sono tutti presenti, siamo forti, addestrati, pronti. Tra mezz'ora tutto sarà finito. Capitano, preparatevi ad accogliere gente, prigionieri e carico sulla vostra nave. Non ci tratterremo a lungo in questo posto.";
				link.l1 = "Tutto è pronto, Tenente. Stavamo solo aspettando voi. Ci si rivede presto!";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				notification("Reputation Too Low! ("+XI_ConvertString(GetReputationName(42))+")", "None");
				notification("Skill Check Failed (60)", SKILL_LEADERSHIP);
				dialog.text = "Grazie, Capitano. Sono notizie preziose. Allora, vai subito al molo e raduna la tua squadra d’abbordaggio. Faremo irruzione nel covo dei furfanti insieme, senza indugi. I migliori tra i miei uomini e i tuoi guideranno l’avanguardia: a loro toccherà prendere i cancelli. Il resto lo decideremo dopo aver passato in rassegna le nostre forze assieme. Non tradire la mia fiducia né quella della tua patria, "+GetFullName(pchar)+".";
				link.l1 = "...Così sia. Ci si rivede, tenente.";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_15_5":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 90)
			{
				notification("Skill Check Passed", SKILL_LEADERSHIP);
				dialog.text = "Grazie, Capitano. Queste sono notizie preziose, e avevi ragione: non c’è motivo di indugiare qui. I miei uomini sono tutti presenti, siamo forti, addestrati e pronti. In mezz’ora sarà tutto finito. Capitano, preparatevi ad accogliere gente, prigionieri e carico sulla vostra nave. Non ci fermeremo qui a lungo.";
				link.l1 = "Tutto è pronto, Tenente. Stavamo solo aspettando voi. A più tardi!";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				notification("Skill Check Failed (90)", SKILL_LEADERSHIP);
				dialog.text = "Grazie, Capitano. Questa è un'informazione preziosa. Allora vai subito al molo e raduna la tua ciurma d'abbordaggio. Assalteremo insieme il covo dei furfanti, senza indugio. I migliori tra i miei e i tuoi uomini guideranno l'avanguardia: saranno loro a prendere i cancelli. Il resto lo discuteremo dopo aver passato in rassegna le nostre forze insieme. Non deludere me, né la tua patria, "+GetFullName(pchar)+".";
				link.l1 = "...Sia come vuoi. A rivederci, Tenente.";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_16": // французы атакуют сами
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -10);
			ChangeCharacterComplexReputation(pchar, "authority", 5);
			AddQuestRecord("IslaMona", "24");
			IslaMona_DefAttackLight();
		break;
		
		case "FraOfficer_17": // совместная атака
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -7);
			AddQuestRecord("IslaMona", "23");
			IslaMona_DefAttackCommon();
		break;
		
		case "FraOfficer_18":
			if (CheckCharacterItem(pchar, "patent_fra")) dialog.text = "E io, stolto, ti ammiravo! A-agh! L'orgoglio di Francia, Capitano "+GetFullName(pchar)+"!! Non sei degno della tua patente!!!";
			else dialog.text = ""+GetFullName(pchar)+", feccia, traditore e maledetto bucaniere! Dovevo immaginare che questa lurida tana fosse il tuo puzzolente covo! La Francia non dimentica né perdona canaglie come te!";
			link.l1 = "";
			link.l1.go = "FraOfficer_19";
		break;
		
		case "FraOfficer_19":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_75";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "FraOfficer_20":
			dialog.text = "Sei pronto, Capitano? La tua ciurma sembra all’altezza!";
			link.l1 = "Grazie, Tenente. Iniziamo dunque?";
			link.l1.go = "FraOfficer_21";
		break;
		
		case "FraOfficer_21":
			dialog.text = "Sì, procediamo senza indugio!";
			link.l1 = "...";
			link.l1.go = "FraOfficer_22";
		break;
		
		case "FraOfficer_22":
			DialogExit();
			IslaMona_DefAttackCommonRun();
		break;
		
		// обиженный пират
		case "Pirate":
			dialog.text = "Ah! "+GetFullName(pchar)+"! Che incontro, per mille balene. Acchiappatelo! Questo furfante possiede tutto qui! Quest’isola è roba sua!";
			link.l1 = "Che giornata, questa...";
			link.l1.go = "Pirate_1";
		break;
		
		case "Pirate_1":
			DialogExit();
			IslaMona_DefCheckJungleFight();
		break;
		
		// Алонсо
		case "Alonso":
			dialog.text = "Capitano, quali sono gli ordini? Hanno issato il segnale per stare pronti e mandare la squadra d'abbordaggio.";
			link.l1 = "L'ordine resta. Ragazzi, seguitemi, dobbiamo ripulire la nostra casa da questi ospiti indesiderati. Il bottino è mio, tutto il resto è vostro!";
			link.l1.go = "Alonso_1";
		break;
		
		case "Alonso_1":
			dialog.text = "Urrà!";
			link.l1 = "All’arrembaggio!";
			link.l1.go = "Alonso_2";
		break;
		
		case "Alonso_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_CharacterDisableDialog(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			for (i=1; i<=5; i++) 
			{
				sld = characterFromId("IM_our_soldier_"+i);
				LAi_SetActorType(sld);
				LAi_CharacterDisableDialog(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Defend.Common"))
			{
				pchar.quest.islamona_attack_common1.win_condition.l1 = "location";
				pchar.quest.islamona_attack_common1.win_condition.l1.location = "IslaMona_Jungle_01";
				pchar.quest.islamona_attack_common1.function = "IslaMona_DefAttackCommonPrepare";
			}
			else
			{
				LocatorReloadEnterDisable("IslaMona_Jungle_01", "reload3_back", true);
				LocatorReloadEnterDisable("IslaMona_Jungle_01", "reload1_back", true);
				pchar.quest.islamona_attack_force.win_condition.l1 = "location";
				pchar.quest.islamona_attack_force.win_condition.l1.location = "IslaMona_factoria";
				pchar.quest.islamona_attack_force.function = "IslaMona_DefAttackForce";
			}
		break;
		
		// испанский офицер
		case "SpaOfficer":
			dialog.text = "Salute, señor. Siete voi il padrone di queste terre? Permettetemi di presentarmi: Gran Francisco de Alba, già capitano della corvetta 'Perro Marino'.";
			link.l1 = "Sì, questa è la mia terra. Io sono "+GetFullName(pchar)+", capitano della nave '"+pchar.ship.name+"‘. Grandioso? Non abbiamo mai avuto ospiti così illustri qui prima d’ora.";
			link.l1.go = "SpaOfficer_1";
		break;
		
		case "SpaOfficer_1":
			dialog.text = "Oh, Monsieur "+GetFullName(pchar)+"! Il tuo nome è sulla bocca di tutti. Vedi, ultimamente il tuo nome spunta così spesso nei rapporti della Casa de Contratación che quasi mi aspettavo ordini di sistemarti per le brutte.";
			link.l1 = "Vuoi trattare con me?";
			link.l1.go = "SpaOfficer_2";
		break;
		
		case "SpaOfficer_2":
			dialog.text = "Penso che sia inutile fingere. Il mio compito è cercare e distruggere i nemici della Spagna e di Re Filippo su tutti i mari del mondo.";
			link.l1 = "Per fortuna tali ordini non sono ancora arrivati. Si vede subito che siete un ufficiale di marina di gran stoffa.";
			link.l1.go = "SpaOfficer_3";
		break;
		
		case "SpaOfficer_3":
			dialog.text = "Il fatto che ora sia un prigioniero mezzo morto su un’isoletta brulicante di pirati e di miei compatrioti in fuga non fa che confermare la tua conclusione, ah-ah! Era una faccenda maledettamente rischiosa, ma gli ordini sono ordini. Ci siamo quasi riusciti! Mi dispiace terribilmente per i miei uomini – li conoscevo tutti per nome, abbiamo servito insieme per tanti anni. Ma la mia patria dovrà ancora versare sangue dei suoi figli, per mantenere il suo rango imperiale. La nostra famiglia lo sa meglio di chiunque altro.";
			if (CheckAttribute(pchar, "questTemp.IslamonaSpaOfficer"))
			{
				link.l1 = "";
				link.l1.go = "SpaOfficer_4";
			}
			else
			{
				link.l1 = "Torniamo a questioni più urgenti, per ora. Che devo fare con te, Grand?";
				link.l1.go = "SpaOfficer_5";
			}
		break;
		
		case "SpaOfficer_4":
			dialog.text = "A proposito, Monsieur de Mor, la 'Guerriera' – quella piccola nave ti era ben nota, vero? La tua impresa sfrontata a Porto Bello non è passata inosservata. Roba audace, quasi da suicida. Avevi un disperato bisogno di dobloni, vero? Ah!";
			link.l1 = "Sai molte cose su di me, Grand. Ma ora passiamo al tuo destino.";
			link.l1.go = "SpaOfficer_5";
		break;
		
		case "SpaOfficer_5":
			dialog.text = "Che c’è da riflettere? Come in ogni buona storia, hai tre scelte: ammazzarmi, lasciarmi qui o darmi la libertà. Se mi lasci andare, ti do la parola della famiglia de Alba che mai racconterò a nessuno di questo posto né del tuo coinvolgimento nelle mie sventure. Inoltre, ti sarò debitore, e finché il debito non sarà saldato, mai mi schiererò contro di te.";
			link.l1 = "Non posso rischiare, vecchio mio.";
			link.l1.go = "SpaOfficer_6";
			link.l2 = "Trascorrerai un po' di tempo qui. Vivrai e lavorerai alla pari coi tuoi compatrioti.";
			link.l2.go = "SpaOfficer_7";
			link.l3 = "Benvenuto a bordo della mia nave, Grand. Ti sbarcherò al faro di Santiago quando sarà il momento. Spero che manterrai la tua parola.";
			link.l3.go = "SpaOfficer_8";
		break;
		
		case "SpaOfficer_6":
			dialog.text = "Capisco, señor. Beh, in ogni caso, sono già morto in quella battaglia insieme ai miei uomini. È una degna fine.";
			link.l1 = "";
			link.l1.go = "SpaOfficer_6_1";
		break;
		
		case "SpaOfficer_6_1":
			DialogExit();
			DoQuestFunctionDelay("IslaMona_KillSpanish", 1.0);
		break;
		
		case "SpaOfficer_7":
			dialog.text = "Lo ammetto, non mi piace fare le cose a metà. Ma non c'è disonore nell'essere prigioniero, quindi accetto il tuo dono di vita e vivrò in pace con questa gente gentile e, a quanto pare, assai felice. Tuttavia, se mai dovessi lasciare questo posto, non ti sarò debitore di nulla.";
			link.l1 = "";
			link.l1.go = "SpaOfficer_7_1";
		break;
		
		case "SpaOfficer_7_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			AddQuestRecord("IslaMona", "27");
			IslaMona_FinalPrepare();
		break;
		
		case "SpaOfficer_8":
			dialog.text = "Ti do la mia parola e quella della famiglia de Alba! Ci vediamo sulla nave!";
			link.l1 = "";
			link.l1.go = "SpaOfficer_8_1";
		break;
		
		case "SpaOfficer_8_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddQuestRecord("IslaMona", "28");
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			ChangeCharacterComplexReputation(pchar, "nobility", 6);
			pchar.quest.islamona_final_mayak.win_condition.l1 = "location";
			pchar.quest.islamona_final_mayak.win_condition.l1.location = "Mayak9";
			pchar.quest.islamona_final_mayak.function = "IslaMona_FinalMayakSpanish";
			pchar.questTemp.IslaMona.Mayak = "true";
			IslaMona_FinalPrepare();
		break;
		
		case "SpaOfficer_9":
			dialog.text = "Capitano "+GetFullName(pchar)+"! You saved my life and brought me back to my own. I understand how difficult it was to take such a risk - I would never have dared to do such a thing. I owe you, senor. I give you my word that I will never tell anyone about the circumstances of that ill-fated battle. When you return to the Old World, be sure to find me; you will always be welcome at our family estate in Madrid. For now, take this...";
			link.l1 = "Un pezzo di mappa?";
			link.l1.go = "SpaOfficer_10";
		break;
		
		case "SpaOfficer_10":
			AddMapPart();
			dialog.text = "Questo era tutto ciò che avevo di prezioso con me. Non dubito che troverai facilmente l’altro pezzo. Addio! E che la fortuna ti assista, amico mio.";
			link.l1 = "Addio, Grand. Tien fede alla tua parola e che la fortuna ti assista!";
			link.l1.go = "SpaOfficer_11";
		break;
		
		case "SpaOfficer_11":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
			pchar.questTemp.IslaMona.Mayak = "done";
			ChangeCharacterNationReputation(pchar, SPAIN, 20);
			AddQuestRecord("IslaMona", "29");
			CloseQuestHeader("IslaMona");
		break;
		
		// Диалоги обитателей Исламоны
		// мужское население
		case "island_man":
			dialog.text = LinkRandPhrase("Salute! Come va, Capitano? Le cose ci vanno a gonfie vele.","Lavorar per la comunità è la gioia più grande!","La vostra isola è magnifica, Capitano, e faremo di tutto per la sua prosperità.");
			link.l1 = LinkRandPhrase("Fa piacere sentirlo.","Felice di sapere che va tutto bene.","Ammiro il tuo entusiasmo, amico mio.");
			link.l1.go = "island_man_1";
			if(CheckAttribute(pchar,"questTemp.IslaMona.TownStage"))
			{
				switch(sti(pchar.questTemp.IslaMona.TownStage))
				{
					case 0:
						dialog.text = RandPhraseSimple(RandPhraseSimple("Non prendertela come un'irriverenza, señor, ma vivere qui è impossibile.","Qualunque cosa è meglio che marcire nelle celle dell’Inquisizione..."),RandPhraseSimple("Grazie per averci salvato, Capitano.","Questi... pirati sarebbero tuoi compari?"));
						link.l1 = "...";
						link.l1.go = "island_man_1";
					break;
					
					case 1:
						dialog.text = RandPhraseSimple(RandPhraseSimple("Non si sta male qui! Solo che è un po’ noioso.","Capitano, che piacere vederti. Passa a trovarmi ogni tanto!"),RandPhraseSimple("Qualcuno ha trovato dei teschi sulla spiaggia e li ha portati all’adunata del mattino.   Succede spesso così da queste parti?","Ti svelerò un segreto, señor Himenes gode chiaramente dell’aria fresca e della sicurezza di questo posto."));
						link.l1 = "...";
						link.l1.go = "island_man_1";
					break;
					
					case 2:
						dialog.text = RandPhraseSimple(RandPhraseSimple("Non è male qui! Solo un tantino noioso.","Capitano, lieto di rivederti. Passa a trovarci quando vuoi!"),RandPhraseSimple("Qualcuno ha trovato dei teschi sulla spiaggia e li ha portati all'adunanza del mattino. Succede sempre così da queste parti?","Ti svelerò un segreto, señor Himenes gode chiaramente dell’aria fresca e della sicurezza di questo posto."));
						link.l1 = "...";
						link.l1.go = "island_man_1";
					break;
					
					case 3:
						dialog.text = RandPhraseSimple(RandPhraseSimple("Dio vi benedica, Capitano!","Una volta alla settimana, facciamo spettacoli sulla spiaggia e nella taverna. Vieni a trovarci quando vuoi."),RandPhraseSimple("I tuoi marinai ci portano ogni sorta di cianfrusaglia in cambio di un po' di cibo fresco. Ti ringrazio per averli spinti a farlo.","È sorprendente che questo posto non sia stato ancora scoperto. Spero che resti così."));
						link.l1 = "...";
						link.l1.go = "island_man_1";
					break;
				}
			}
		break;
		
		case "island_man_1":
			DialogExit();
			npchar.dialog.currentnode = "island_man";
		break;
		
		case "island_man_2":
			dialog.text = "Grazie, signor. Grazie a voi abbiamo visto il vero Nuovo Mondo. Che Dio vi benedica!";
			link.l1 = "";
			link.l1.go = "island_man_3";
			locCameraFromToPos(1.64, 1.58, -5.11, false, 2.66, 0.20, -5.74);
		break;
		
		case "island_man_3":
			DialogExit();
			npchar.dialog.currentnode = "island_man";
			sld = characterFromId("Himenes_companion_12");
			sld.dialog.currentnode = "island_woman_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.0);
		break;
		
		// женское население
		case "island_woman":
			dialog.text = LinkRandPhrase("La sicurezza e la pace – ecco cosa mi piace di questo posto!","Un paradiso meraviglioso! Beh, quasi...","Siam lieti d’aver trovato nuova dimora qui, dopo tante tribolazioni.");
			link.l1 = LinkRandPhrase("Sono lieto per te e per la tua comunità.","Sì, anche a me piace quest’isoletta.","Mi fa piacere sapere che sei soddisfatto.");
			link.l1.go = "island_woman_1";
			if(CheckAttribute(pchar,"questTemp.IslaMona.TownStage"))
			{
				switch(sti(pchar.questTemp.IslaMona.TownStage))
				{
					case 0:
						dialog.text = LinkRandPhrase("Oh... Salve.","Signore, chi sono quei... brutti ceffi armati?","Grazie per averci salvato, Capitano.");
						link.l1 = "...";
						link.l1.go = "island_woman_1";
					break;
					
					case 1:
						dialog.text = LinkRandPhrase("I nostri uomini hanno fatto un lavoro splendido – le case sono eccellenti. Ma anche noi ci siamo fatti il mazzo!","Signor Capitano, non temete: le donne della nostra piccola ciurma non si spaventano davanti a fatiche o disagi passeggeri.","Che aria qui! E che mare! Ti senti più vicino a Dio!");
						link.l1 = "...";
						link.l1.go = "island_woman_1";
					break;
					
					case 2:
						dialog.text = LinkRandPhrase("I nostri uomini hanno fatto un lavoro eccellente – le case sono magnifiche. Ma pure noi ci siamo spaccati la schiena!","Signor Capitano, non temete: le donne del nostro piccolo clan non hanno paura né delle difficoltà né dei disagi passeggeri.","Che aria qua! E il mare! Ti senti più vicino a Dio!");
						link.l1 = "...";
						link.l1.go = "island_woman_1";
					break;
					
					case 3:
						dialog.text = LinkRandPhrase("Fa’ ritorno più spesso, Señor Capitano. Son sempre lieta di rivederti.","Don Rodgar è un vero maestro di storie. Potresti ascoltarlo per l’eternità, senza mai stufarti!","Hehe. Dicono che qualcuno del nostro gruppo aspetta già un pargoletto. La vita non si ferma nemmeno a Isla Mona!");
						link.l1 = "...";
						link.l1.go = "island_woman_1";
					break;
				}
			}
		break;
		
		case "island_woman_1":
			DialogExit();
			npchar.dialog.currentnode = "island_woman";
		break;
		
		case "island_woman_2":
			dialog.text = "Voi... Muchas gracias, señor! Passate più spesso da queste parti...";
			link.l1 = "";
			link.l1.go = "island_woman_3";
			locCameraFromToPos(-1.86, 1.18, 4.51, true, -1.49, 0.20, 6.13);
		break;
		
		case "island_woman_3":
			DialogExit();
			npchar.dialog.currentnode = "island_woman";
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_31";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.0);
		break;
		
		// пираты Родгара
		case "fort_pirate":
			if(npchar.location == "islamona_factoria")
			{
				dialog.text = dialog.text = RandPhraseSimple(RandPhraseSimple("Tutto a posto, Capitano!","Gli schiavi sono sotto controllo, non temere."),RandPhraseSimple("Non devi preoccuparti, l’ammutinamento è fuori discussione.","Grazie per il rum! Ci mettiamo subito all’opera!"));
			}
			else
			{
				dialog.text = dialog.text = RandPhraseSimple(RandPhraseSimple("Spagnoli? Non ce l’aspettavamo da voi.","Ora dobbiamo camminare fino alla spiaggia solo per dormire in santa pace!"),RandPhraseSimple("Perché hai deciso di buttarti in tutto questo, eh, Capitano?","Il capo si fidò di te allora – e non sbagliò. Ci fideremo di nuovo di te."));
			}
			link.l1 = "...";
			link.l1.go = "fort_pirate_1";
		break;
		
		case "fort_pirate_1":
			DialogExit();
			npchar.dialog.currentnode = "fort_pirate";
		break;
		
		// посетители таверны
		case "citizen_tavern":
			dialog.text = LinkRandPhrase("Dopo una faticaccia del diavolo, non è peccato buttarsi giù un paio di bicchieri...","I'm almost done and heading home; the wife must be waiting...","Ah, it's nice to relax in our tavern after work! We're all grateful to you, captain!");
			link.l1 = LinkRandPhrase("Goditi il tuo bicchiere, compadre, ah-ah!","Rilassati, compare, ma non esagerare, o la moglie ti strapazzerà, ahah!","Calmati, compare, la vita non è fatta solo di lavoro!");
			link.l1.go = "citizen_tavern_1";
		break;
		
		case "citizen_tavern_1":
			DialogExit();
			npchar.dialog.currentnode = "citizen_tavern";
		break;
		
		case "sailor_tavern":
			if (GetCharacterIndex("Mirabella") != -1) sTemp = "Who's that pretty mulatto woman living here?";
				else sTemp = "Captain, nice place you got here!";
			dialog.text = RandPhraseSimple(RandPhraseSimple("Capitano, bel posto che avete qui!","Immagina se all'improvviso ci ritrovassimo senza rum. Scommetto che tu te ne procureresti dell'altro, vero?"),RandPhraseSimple("Da tempo sognavo una vacanza così. Però mi piacerebbe un bordello... solo un pensieraccio selvaggio, Capitano.",sTemp));
			link.l1 = "...";
			link.l1.go = "sailor_tavern_1";
		break;
		
		case "sailor_tavern_1":
			DialogExit();
			npchar.dialog.currentnode = "sailor_tavern";
		break;
		
		case "sailor_town":
			dialog.text = RandPhraseSimple(RandPhraseSimple("Grazie per la vacanza, Capitano.","Bel posto che hai messo su qui – hai proprio il dono di tenere tutto in riga, Capitano."),RandPhraseSimple("Cibo fresco, rum a fiumi, terra solida sotto i piedi. È un sogno.","Vorrei restare qui ancora un po'."));
			link.l1 = "...";
			link.l1.go = "sailor_town_1";
		break;
		
		case "sailor_town_1":
			DialogExit();
			npchar.dialog.currentnode = "sailor_town";
		break;
		
		// рабы
		case "slave":
			dialog.text = RandPhraseSimple(RandPhraseSimple("Sono così stanco - riesco a malapena a reggermi in piedi.","Non ho più forza per vivere così!"),RandPhraseSimple("Questo lavoro è troppo duro per me.","I sorveglianti non hanno lasciato nemmeno una cellula viva sulla mia pelle!"));				
			link.l1 = "";
			link.l1.go = "slave_1";
		break;
		
		case "slave_1":
			DialogExit();
			npchar.dialog.currentnode = "slave";
		break;
		
		// энкауниеры в домах
		case "HouseMan":
			dialog.text = LinkRandPhrase("Posso esserle d'aiuto in qualcosa, capitano?","Entra, assaggia la paella del posto. Ma, per l'amor di Dio, non chiedere mai di cosa sia fatta!","Benvenuto, capitano. Come ti sembra questo posto?");
			link.l1 = "...";
			link.l1.go = "HouseMan_1";
		break;
		
		case "HouseMan_1":
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			npchar.dialog.currentnode = "HouseMan";
		break;
		
		case "HouseWoman":
			dialog.text = LinkRandPhrase("Signor, benvenuto!","Salve, capitano. Vi fermerete?","Sei venuto per me? Ti prego, entra pure, non badare al disordine, señor.");
			link.l1 = "...";
			link.l1.go = "HouseWoman_1";
		break;
		case "HouseWoman_1":
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			npchar.dialog.currentnode = "HouseWoman";
		break;
	}
}
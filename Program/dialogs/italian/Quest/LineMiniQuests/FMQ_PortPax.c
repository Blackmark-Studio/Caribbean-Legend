// Addon-2016 Jason, французские миниквесты (ФМК) Порт-о-Пренс
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Ecco qua un bug bello evidente. Avvisa quei cani degli sviluppatori.";
			link.l1 = "Oh, lo farò.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "officer":
			PlaySound("Voice\English\z_arest_02.wav");
			dialog.text = "Che diavolo sta succedendo qui, signori? Ho sentito delle urla e del trambusto.";
			link.l1 = "Salve ufficiale, ho sentito una donna urlare e...";
			link.l1.go = "officer_1";
		break;
		
		case "officer_1":
			DialogExit();
			sld = CharacterFromID("FMQP_noble");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "officer_2":
			dialog.text = "";
			link.l1 = ""+GetFullName(pchar)+". Capitano "+GetFullName(pchar)+".";
			link.l1.go = "officer_3";
		break;
		
		case "officer_3":
			dialog.text = "Sei libero di andare per ora, capitano. Vedo bene cosa è successo qui, ti convocheremo se avremo domande.";
			link.l1 = "Molto bene...";
			link.l1.go = "officer_4";
		break;
		
		case "officer_4":
			DialogExit();
			sld = CharacterFromID("FMQP_noble");
			sld.Dialog.currentnode = "noble_3";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "officer_5":
			PlaySound("Voice\English\z_arest_02.wav");
			dialog.text = "Che diavolo sta succedendo qui, signori? Ho sentito delle botte.";
			link.l1 = "Grazie, ufficiale, ho sentito una donna urlare aiuto e ho visto questo gentiluomo assalito da due mascalzoni. Ho provato a salvare il poveretto, ma ahimè, sono arrivato troppo tardi. Quei bastardi l'hanno ammazzato!";
			link.l1.go = "officer_6";
		break;
		
		case "officer_6":
			dialog.text = "Maledizione ai miei occhi... È uno spagnolo! Che diavolo ci fa qui? Mh. E tu chi saresti, signore?";
			link.l1 = ""+GetFullName(pchar)+". Capitano "+GetFullName(pchar)+".";
			link.l1.go = "officer_7";
		break;
		
		case "officer_7":
			dialog.text = "Capitano, per ora sei libero di andare. Le tue parole combaciano con quelle del testimone. Ti chiameremo se sarà necessario.";
			link.l1 = "Molto bene...";
			link.l1.go = "officer_8";
		break;
		
		case "officer_8":
			DialogExit();
			DoQuestReloadToLocation("Portpax_town", "reload", "reload4", "");
		break;
		
		case "noble":
			dialog.text = "Permettetemi di spiegare ogni cosa, señor! Il mio nome è Don Domingo Ortiz Albalate di Santo Domingo. Son giunto a Port-au-Prince su invito di una giovane señorita e mi son fermato in questa taverna in attesa dell’ora fissata. Mentre stavo per i fatti miei, sono stato assalito da questi due maledetti furfanti. A quest’ora starei banchettando con gli angeli, se non fosse stato per questo buon Samaritano che è capitato qua.";
			link.l1 = "Don Domingo Ortiz Albalate? Sei spagnolo?";
			link.l1.go = "noble_1";
		break;
		
		case "noble_1":
			dialog.text = "Spagnolo quanto il re Felipe in persona, ah! E vorrei pure sottolineare che i miei documenti sono in buen orden. Sono nobile di Spagna, non qualche sporco filibustiere!";
			link.l1 = "Don Domingo, le nostre più sentite scuse per questo spiacevole incidente! Ci segua pure alla guarnigione per qualche domanda e una bottiglia di vino. Al resto pensiamo noi. Quanto a voi...";
			link.l1.go = "noble_2";
		break;
		
		case "noble_2":
			DialogExit();
			sld = CharacterFromID("FMQP_off");
			sld.Dialog.currentnode = "officer_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "noble_3":
			PlaySound("Voice\English\LE\Domingo\Domingo_01.wav");
			dialog.text = "Señor Capitano! Señor Capitano! Giuro su Santiago e sulla Santa Vergine che siete un uomo nobile, e un vero figlio di Castiglia premia sempre la nobiltà! Vorrei vedervi ricompensato più tardi, quando avrò finito i miei affari qui. Vi prego, onoratemi con una visita nella mia umile dimora a Santo Domingo! È vicino alle porte della città. Vi preparerò un banchetto, mio buon cavaliere Carlos! Ricordate il mio nome, sono Don Domingo Ortiz Albalate!";
			link.l1 = "...";
			link.l1.go = "noble_4";
		break;
		
		case "noble_4":
			DialogExit();
			AddMapQuestMarkCity("santodomingo", true);
			DoQuestReloadToLocation("Portpax_town", "reload", "reload4", "FMQP_AfterFightInTown");
		break;
		
		case "noble_5":
			dialog.text = "Capitano "+GetFullName(pchar)+"?! Oh Madre de Dios! Che disastro! È una carneficina! Cosa è successo qui, buen amigo? Chi sono questi uomini?";
			link.l1 = "Felice di vederti, Don Domingo. Questi sono... sono venuto qui a farti visita. Vedi quel tizio laggiù? Quello è Ugo, il tuo servitore e lui...";
			link.l1.go = "noble_6";
		break;
		
		case "noble_6":
			dialog.text = "Ugo?! Oh, no, ti hanno fregato, capitano!";
			link.l1 = "Capisco, mi capita spesso. Tre furfanti hanno fatto irruzione in casa tua, hanno ammazzato il tuo fedele Ugo – ho già trovato il suo cadavere di sopra – e poi ti hanno teso un'imboscata. Il mio arrivo non era previsto dai loro loschi piani. Non sono sopravvissuti al nostro incontro.";
			link.l1.go = "noble_7";
		break;
		
		case "noble_7":
			dialog.text = "Santa Maria, ora pro nobis! Maneggi la spada come un vero maestro di Toledo! È un bene che tu sia dalla mia parte! Oh, povero Ugo mio! Mi ha cresciuto fin da bambina e ora... assassinato da quelle maledette canaglie!";
			link.l1 = "Don Domingo, pare che tu non sia ancora fuori pericolo. Il tuo uomo Ugo sapeva qualcosa, leggi questa nota. L’ho trovata su un tavolo.";
			link.l1.go = "noble_8";
		break;
		
		case "noble_8":
			ChangeItemDescribe("letter_parol", "itmdescr_letter_parol");
			RemoveItems(pchar, "letter_parol", 1);
			dialog.text = "Dammelo... (leggendo) Non può essere... oh, no! È incredibile! Zio Luis... Ma...";
			link.l1 = "Hai qualche indizio su chi sia stato il bastardo?";
			link.l1.go = "noble_9";
		break;
		
		case "noble_9":
			dialog.text = "Solo sospetti... terribili sospetti, amigo mio! Come potrebbe il fratello di mia madre aver fatto una simile infamia?";
			link.l1 = "Ti dispiacerebbe mettermi al corrente? Perdona la franchezza, Don Domingo, ma per quel che ho visto io, i parenti sanno essere i peggiori nemici di un uomo...";
			link.l1.go = "noble_10";
		break;
		
		case "noble_10":
			dialog.text = "Sì, hai ragione, Carlos! Ti racconterò tutto! Mi hai già salvato due volte e pare che tu sia l’unico di cui possa fidarmi adesso! Ma andiamocene da questo lurido posto, mi viene la nausea. Devo avvisare l’alcalde di questo casino, si occuperanno loro del povero Ugo. Che ne dici di un bicchiere di vino nella taberna locale, così ci rimettiamo i nervi in sesto?";
			link.l1 = "I tuoi nervi ne hanno bisogno più dei miei, avanti senor!";
			link.l1.go = "noble_11";
		break;
		
		case "noble_11":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoQuestReloadToLocation("Santodomingo_tavern", "sit", "sit_base2", "FMQP_InSantoDomingoTavern");
		break;
		
		case "noble_12":
			LAi_SetSitType(pchar);
			dialog.text = "Dunque, amico mio, permettimi di narrarti una... versione ridotta della mia storia di famiglia. Mia madre, Dona Isabella Ortiz, sposò mio padre, il Marchese Ricardo Albalate, e prese il suo cognome come vuole la consuetudine. Suo fratello, Luis Ortiz, era comandante di guarnigione nelle colonie, ma dopo il matrimonio di mia madre, fu nominato da mio padre come amministratore di una piantagione di zucchero non lontano da Portobello\nEra una piantagione enorme e ricchissima, davvero molto redditizia. Dopo la tragica morte dei miei genitori in mare qualche anno fa, io, loro unico figlio, ho ereditato tutto, compresa la piantagione. Mio zio ha mantenuto il suo incarico e io mi accontentavo dell'affitto che mi corrispondeva. Era sempre puntuale nei pagamenti.";
			link.l1 = "Quindi pensi che tuo zio...";
			link.l1.go = "noble_13";
		break;
		
		case "noble_13":
			dialog.text = "Sì. Al momento non è altro che un affittuario. La piantagione è mia, non sua. Ma! Se dovesse capitarmi qualcosa – la proprietà passerà a lui.";
			link.l1 = "Sai, Domingo, ho conosciuto uomini che avrebbero sgozzato tutti i loro parenti a sangue freddo per una ricompensa ben meno succulenta di quella.";
			link.l1.go = "noble_14";
		break;
		
		case "noble_14":
			dialog.text = "Chiaramente devi sceglierti meglio le compagnie, Carlos. Il mio caro Ugo ha menzionato i documenti di mio zio nella sua ultima lettera... È un indizio bello chiaro. Oh, non voglio crederci! Ma... mia cugina, Margarita Ortiz, che vive in Spagna, si è promessa poco tempo fa. Potrebbe essere questa la causa, mio buon capitano?";
			link.l1 = "Il tuo caro zio potrebbe all’improvviso aver bisogno di qualche moneta...";
			link.l1.go = "noble_15";
		break;
		
		case "noble_15":
			dialog.text = "Denaro?! Ma certo... ma non dimenticare il titolo di marchese! Così mia cugina sarebbe davvero all’altezza del suo futuro marito! Per mille balene! Che idiota sono stato!";
			link.l1 = "Quel titolo nobiliare vale più d’una piantagione di zucchero.";
			link.l1.go = "noble_16";
		break;
		
		case "noble_16":
			dialog.text = "Aspetta, amico mio! Mi è appena tornato in mente che questo non è stato il primo attentato alla mia vita! Qualche settimana fa, ho avuto uno scontro con un mendicante per strada! Quel canaglia ubriaco mi ha insultato in modo che non potevo lasciar correre. Si è rivelato un maledetto spadaccino, ha sguainato la lama e persino è riuscito a ferirmi con una rapier prima che lo mandassi all'altro mondo.";
			link.l1 = "E come diavolo sei finito in una taverna a Port-au-Prince? Hai menzionato una giovane signorina?";
			link.l1.go = "noble_17";
		break;
		
		case "noble_17":
			dialog.text = "(arrossendo) Signore... Sì capitano, c’era una giovane e graziosa señorita sulla scena... ora capisco che era solo l’esca della trappola. Maledetti, maledetti ovunque, non ci si può fidare di nessuno! Povero Ugo... ormai è morto.";
			link.l1 = "Dovresti farci qualcosa, Domingo. Che ne dici di filartela in Spagna?";
			link.l1.go = "noble_18";
		break;
		
		case "noble_18":
			dialog.text = "In Spagna? E lasciare la mia piantagione a quel furfante? Capitano, io sono il Marchese Domingo Ortiz Albalate!";
			link.l1 = "Ma...";
			link.l1.go = "noble_19";
		break;
		
		case "noble_19":
			dialog.text = "Amico mio Carlos, posso chiederti un favore? Ora che Ugo è morto, non ho più nessuno di cui fidarmi accanto a me. Mi hai già salvato due volte! Due! Ti devo moltissimo, sarò in debito con te per sempre, eppure oso chiederti ancora un aiuto. Ti giuro sulla Santa Madre Benedetta che saprò ricompensarti degnamente!";
			link.l1 = "Molto bene, sei un brav'uomo per essere uno spagnolo. Cosa posso fare per te, Domingo?";
			link.l1.go = "noble_20";
		break;
		
		case "noble_20":
			dialog.text = "Andiamo alla mia piantagione a Portobello! So che mio zio è a Cartagena in questo momento. Ugo ha parlato di alcune carte, quindi diamo un'occhiata ai libri e ai documenti di Don Luis Ortiz! Magari troviamo qualcosa che ci aiuti a smascherare la sua lurida cospirazione. Portobello è parecchio distante, ma ti pagherò generosamente per il viaggio!";
			link.l1 = "Sarebbe una follia rifiutarti adesso, Don Domingo. Ormai sono invischiato fino al collo e non posso tirarmi indietro.";
			link.l1.go = "noble_21";
		break;
		
		case "noble_21":
			AddMoneyToCharacter(pchar, 20000);
			dialog.text = "Grazie a Dio, sapevo che mi avresti dato una mano, amico mio! Tieni, prendi questi ventimila pesos per il viaggio fino a Portobello. Quando si salpa? Dobbiamo sbrigarci prima che mio zio torni da Cartagena!";
			link.l1 = "Non perdiamo tempo, allora.";
			if (CheckCharacterItem(pchar, "HolTradeLicence") && GetDaysContinueNationLicence(HOLLAND) >= 20) link.l1.go = "noble_22";
			else link.l1.go = "noble_22x";
		break;
		
		case "noble_22x":
			GiveNationLicence(HOLLAND, 20);
			dialog.text = "Ecco una licenza della Compagnia Olandese delle Indie Occidentali. Ha una scadenza di venti giorni, mettiamo qui il tuo nome. Fatto. Questo dovrebbe aiutarci a evitare grane con la Costa Guardia.";
			link.l1 = "Eccellente!";
			link.l1.go = "noble_22";
		break;
		
		case "noble_22":
			dialog.text = "Posso finalmente salire a bordo della tua nave, amico mio?";
			link.l1 = "Considerati un ospite d’onore. Non appena soffierà il vento giusto, salperemo.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_OnBoard");
			AddMapQuestMarkCity("portobello", true);
		break;
		
		case "noble_23":
			dialog.text = "Allora, Capitano Carlos, eccoci qua. Ora dobbiamo trovare la casa di mio zio e vedere cosa c’è dentro.";
			link.l1 = "Don Domingo, dobbiamo aspettarci grane con la guardia?";
			link.l1.go = "noble_24";
		break;
		
		case "noble_24":
			dialog.text = "No. Sebbene... mh. C’è una possibilità che Luis li abbia messi contro di me. In ogni caso, la prudenza è sempre la parte migliore del valore. Cerchiamo la casa che ci serve.";
			link.l1 = "Non lo sai già? È la tua piantagione.";
			link.l1.go = "noble_25";
		break;
		
		case "noble_25":
			dialog.text = "Mm... A dirla tutta, l’ultima volta che sono stato qui avevo appena otto anni. Ma giuro che rimedierò presto a questa mancanza!";
			link.l1 = "Capisco. Allora cominciamo a cercare. La casa di tuo zio dev’essere la più grande qui.";
			link.l1.go = "noble_26";
		break;
		
		case "noble_26":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			AddQuestRecord("FMQ_Portpax", "7");
		break;
		
		case "noble_27":
			dialog.text = "Cosa abbiamo qui, amico mio?";
			link.l1 = "Dai un'occhiata, Don Domingo. Sembrano registri contabili. Potrebbe essere interessante.";
			link.l1.go = "noble_28";
		break;
		
		case "noble_28":
			ChangeItemDescribe("Almanac", "itmdescr_Almanac");
			RemoveItems(pchar, "Almanac", 1);
			dialog.text = "(leggendo) Mh... Già. Guarda qua... Per mille balene! Centomila pesos! E poi altri centocinquantamila! E qui... (sfogliando le pagine) Zio Luis!";
			link.l1 = "Qualcosa che valga la pena d’essere raccontato?";
			link.l1.go = "noble_29";
		break;
		
		case "noble_29":
			dialog.text = "Qualcosa di interessante! Il mio caro zio aveva un reddito cinque volte superiore a quello che mi raccontava! Ladro! Farabutto!";
			link.l1 = "Non posso dire che mi sorprenda. Non si può dare piena fiducia a nessuno senza controllare di tanto in tanto come vanno davvero le cose. È solo buon senso.";
			link.l1.go = "noble_30";
		break;
		
		case "noble_30":
			dialog.text = "Buonsenso per la gente comune, forse. Ma la mia educazione m’ha reso cieco a simili inganni da parte di gentiluomini che credevo onorati! Hai sempre ragione, Carlos! Mio zio stesso mi deruba! Maledizione! È colpa mia, ma rimetterò tutto a posto. Questa piantagione è mia e da oggi mio zio è stato sollevato dall’incarico! Non è più nessuno! Lo farò strisciare sotto la chiglia!";
			link.l1 = "Don Domingo... Non pensi che tuo zio potrebbe non essere d'accordo con una simile decisione?";
			link.l1.go = "noble_31";
		break;
		
		case "noble_31":
			dialog.text = "Non me ne frega un accidente se è d'accordo o no! Io sono il marchese Domingo Ortiz Albalate e Luis Ortiz non è altro che un affittuario, e pure ex affittuario! E lui...";
			link.l1 = "Calmati, señor. Sei una faccia nuova qui e io sono un francese che naviga con patente olandese, con... un passato piuttosto torbido coi cani da caccia spagnoli. Quanto a tuo zio, questo porto è roba sua. Pensa alle guardie e al governatore locale. Davvero credi che staranno dalla tua parte?";
			link.l1.go = "noble_32";
		break;
		
		case "noble_32":
			dialog.text = "Colpisci nel segno con una spada... Forse... No. I soldati spagnoli non oserebbero mai alzare una mano contro un nobiluomo! Mio zio può sfidarmi, se ne ha il coraggio!";
			link.l1 = "Tuttavia, ti consiglio una strada diversa. Che ne dici di rivolgerti al tribunale?";
			link.l1.go = "noble_33";
		break;
		
		case "noble_33":
			dialog.text = "Ah! Hai ragione, Carlos. Andiamo a parlare con le autorità giuste. Mio zio ha fatto una sciocchezza annotando dettagli precisi nei suoi appunti sulle sue faccende con i contrabbandieri. Ha comprato schiavi da loro a prezzi da miseria. Questi registri ci saranno molto utili, dubito che quel bastardo possa nuocermi in alcun modo mentre marcisce nelle segrete. Andiamo, amico mio! Verso Portobello!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_PrepareUncle");
		break;
		
		case "noble_34":
			PlaySound("Voice\English\LE\Domingo\Domingo_04.wav");
			dialog.text = "Questa è una lurida, sfacciata menzogna! Come osa infangare il buon nome dei miei genitori con quella lingua da miserabile! Maledetto sia, gliela farò pagare! Spada alla mano, furfante!";
			link.l1 = "";
			link.l1.go = "noble_35";
		break;
		
		case "noble_35":
			DialogExit();
			sld = CharacterFromID("FMQP_Uncle");
			sld.Dialog.currentnode = "uncle_3";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "noble_36":
			PlaySound("Voice\English\LE\Domingo\Domingo_05.wav");
			dialog.text = "Zio Luis ora si trova dove merita la sua anima – all’inferno... Carlos, sei stato mandato da me dal mio angelo custode! Sono felice che tu non abbia dato fiducia alle parole di quel furfante. A dire il vero, temevo che mi avresti lasciato qui da solo a vedermela con questa canaglia.\nSì señor, non sono un santo, ma questa... questa lurida menzogna su di me che avrei assoldato pirati per far fuori i miei stessi genitori! Accusarmi di questo... questo! Bah! Una fine ben meritata.";
			link.l1 = "Contento che ce l’abbiamo fatta, Don Domingo. E adesso? Spero che non ci siamo messi contro la legge di Spagna.";
			link.l1.go = "noble_37";
		break;
		
		case "noble_37":
			dialog.text = "Con la legge? Ah-ah! No Carlos, mostrerò questo bel libro dei conti pieno di tutte le operazioni di contrabbando di mio zio. E non scordarti dei tanti attentati alla mia vita, abbiamo una folla di testimoni dopo l’ultimo tentativo appena ora. Non preoccuparti, mi buen amigo. Questa è la mia città, è tempo di mostrare a tutti chi comanda!";
			link.l1 = "Proceda con cautela, signor mio. Che pensino meglio di lei di quanto abbiano mai pensato del suo defunto zio.";
			link.l1.go = "noble_38";
		break;
		
		case "noble_38":
			dialog.text = "Ecco il piano, capitano. Ma non avrò pietà per chiunque osi mettersi di traverso. Permettimi di esprimere la mia sincera gratitudine a te, Carlos! Ora vai pure in taverna, riposati, bevi un paio di bicchieri. Mi farebbe piacere accompagnarti, ma avevi ragione. È tempo che io faccia il furbo e prenda in mano la piantagione. Passa a trovarmi qui domani, capitano!";
			link.l1 = "Molto bene, Don Domingo. Ci vediamo domani.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_PlantatonPause");
		break;
		
		case "noble_39":
			DelLandQuestMark(npchar);
			PlaySound("VOICE\English\LE\Domingo\Domingo_05.wav");
			dialog.text = "Ah, eccoti qui, mio buon amico!";
			link.l1 = "Come va, don Domingo? E la tua piantagione, come tira?";
			link.l1.go = "noble_40";
		break;
		
		case "noble_40":
			dialog.text = "La piantagione va a gonfie vele, peccato che lo stesso non si possa dire per i dobloni – pare che il mio caro zio abbia trasferito tutto il denaro alla banca di Cartagena. Mi ci vorranno schiere di avvocati per rimettere le mani sul mio oro. Ma va bene così, ci penserò io. Non crucciarti, capitano, manterrò la mia parola e ti ricompenserò per la tua nobiltà, onestà e amicizia!";
			link.l1 = "Mai mi è passato per la testa di chiedere una ricompensa mentre combattevo al vostro fianco, señor...";
			link.l1.go = "noble_41";
		break;
		
		case "noble_41":
			dialog.text = "So che è così, capitano, e ciò dice molto sul vostro carattere! Ogni buona azione merita una ricompensa. Dunque, sebbene ora non abbia monete con me, ordinerò che la vostra nave sia caricata con le merci della mia piantagione. Intendo dire caffè, una bella partita. Potrete venderlo con gran profitto, ne sono certo.";
			link.l1 = "Oh! Questo è piacevole...";
			link.l1.go = "noble_42";
		break;
		
		case "noble_42":
			dialog.text = "Inoltre, possiedo alcuni oggetti di poco conto per me, ma di gran valore per un marinaio come te. Un bel cannocchiale e tre amuleti. Accetta pure, ormai sono tuoi.";
			link.l1 = "Grazie di cuore!";
			link.l1.go = "noble_43";
		break;
		
		case "noble_43":
			Log_Info("You have received a good spyglass");
			Log_Info("You have received three amulets");
			PlaySound("interface\important_item.wav");
			dialog.text = "Infine, ti dono la mia spada come segno della mia infinita gratitudine. Mi ha servito fedelmente, ora possa servir te ancor meglio. Guardala e ricorda il tuo buon amico spagnolo – marchese Domingo Albalate!";
			link.l1 = "Grazie di cuore, signore! Non me l’aspettavo proprio...";
			link.l1.go = "noble_44";
		break;
		
		case "noble_44":
			Log_Info("You have received the Smallsword");
			PlaySound("interface\important_item.wav");
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			dialog.text = "E ora, ahimè, devo dire addio. Devo andare a Portobello a far visita al governatore e poi a Cartagena... Insomma, la mia vita spensierata è finita, è tempo di vivere come un uomo fatto e finito.";
			link.l1 = "Ebbene, ora sei molto più sveglio...";
			link.l1.go = "noble_45";
		break;
		
		case "noble_45":
			dialog.text = "È vero. È stato un piacere, compare! Vienimi a trovare quando vuoi. Che il vento ti sia favorevole!";
			link.l1 = "Anche a te nel tuo affare di piantagioni, don Domingo!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_ReceiveReward");
		break;
		
		case "noble_46":
			PlaySound("Voice\English\YoungMan02.wav");
			dialog.text = "Eh, siamo in ritardo, señor! Che peccato, il mio caro vecchio zio ha già fatto una bella pulizia tra le sue carte. Pare che qualcuno gli abbia parlato di Santo Domingo e lui ha preso delle precauzioni... Ma non intendo lasciarla passare! Devo vedere il governatore di Portobello per avviare un procedimento legale contro mio zio. Ne ho abbastanza che gestisca le mie ricchezze.";
			link.l1 = "Buona scelta.";
			link.l1.go = "noble_47";
		break;
		
		case "noble_47":
			dialog.text = "Voglio ringraziarti, capitano! È stato un vero piacere! Ti dono la mia spada come segno della mia gratitudine. Mi ha servito fedelmente, ora che serva ancor meglio te. Guardala e ricorda il tuo buon amico spagnolo – il marchese Domingo Albalate!";
			link.l1 = "Grazie mille, signor! Non me l’aspettavo...";
			link.l1.go = "noble_48";
		break;
		
		case "noble_48":
			Log_Info("You have received the Smallsword");
			PlaySound("interface\important_item.wav");
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			GiveItem2Character(pchar, GetGeneratedItem("blade_16")); // belamour legendary edition используем GetGeneratedItem иначе пачка одинаковых клинков из первой части массива
			dialog.text = "E ora, ahimè, devo dare l’addio. Devo andare a Portobello. La mia vita spensierata è finita, è tempo di vivere da uomo fatto. Che il vento ti sia favorevole, in mare!";
			link.l1 = "Buona fortuna con vostro zio, don Domingo! Son certo che la spunterete!";
			link.l1.go = "noble_49";
		break;
		
		case "noble_49":
			DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("PortoBello_Plantation", "reload2_back", false);
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 40.0);
			pchar.questTemp.FMQP = "fail";
			AddQuestRecord("FMQ_Portpax", "13");
			CloseQuestHeader("FMQ_Portpax");
			sld = &Locations[FindLocation("PortoBello_Plantation")];
			sld.soldiers = true;
		break;
		
		case "uncle":
			PlaySound("Voice\English\OliverTrast02.wav");
			dialog.text = "Sembra che sia arrivato giusto in tempo. Mio nipote spensierato e il suo angelo custode, Capitano "+GetFullName(pchar)+"  Non fare quella faccia, francese, so benissimo chi sei.";
			link.l1 = "Luis Ortiz?";
			link.l1.go = "uncle_1";
		break;
		
		case "uncle_1":
			dialog.text = "Hai ragione, capitano, ma tutto il resto lo hai frainteso. Non dovresti ficcare il naso negli affari di famiglia altrui. E non hai nemmeno idea di chi stai difendendo. Mio nipote dissoluto, Domingo, è un fannullone buono a nulla, il primo ad entrare in ogni taverna e bordello, sempre pronto a saltare o almeno provarci con ogni fanciulla all’orizzonte. Gli pago l’affitto ogni mese e lui lo sperpera in pochi giorni, sempre a chiedere ancora e ancora. Sempre la stessa storia. Il suo comportamento indegno ha fatto impazzire sua madre e mia sorella.\nHo sentito voci che questo furfante abbia persino assoldato e guidato alcuni corsari inglesi contro una certa nave del Marchese Ricardo Albalate, che affondarono insieme a quell’uomo degno e alla mia cara sorella. Domingo desiderava così tanto i soldi di famiglia che avrebbe ucciso per averli... Purtroppo non sono riuscito a trovare abbastanza prove per mandare questo mascalzone alla forca.";
			link.l1 = "";
			link.l1.go = "uncle_2";
		break;
		
		case "uncle_2":
			DialogExit();
			sld = CharacterFromID("FMQP_noble");
			sld.Dialog.currentnode = "noble_34";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "uncle_3":
			dialog.text = "Tipico. Urla, spade che sbattono e boccali che tintinnano, tutto un gran baccano per nulla. Quanto ti ha pagato, capitano, per la tua protezione?";
			link.l1 = "Per quel che ho capito, visto che non sei riuscito a scovare prove contro tuo nipote, hai cominciato a mandargli addosso sicari. Sembra che una semplice causa legale sarebbe bastata.";
			link.l1.go = "uncle_4";
		break;
		
		case "uncle_4":
			dialog.text = "Tu menti. Questo Domingo qui s’è fatto una schiera infinita di nemici. Ovunque va lascia dietro di sé amanti ingannate e mariti cornuti. Mi chiedo come abbia fatto a campare così a lungo! Chiedigli tu: quante nozze ha rovinato? Quanti fidanzati offesi ha ferito o mandato al creatore?";
			link.l1 = "Il suo servitore Ugo...";
			link.l1.go = "uncle_5";
		break;
		
		case "uncle_5":
			dialog.text = "Ah, Ugo! Il più gran furfante di tutti! Ugo adorava quel suo padrone scapestrato. Tutte le malefatte del padrone gli parevano bazzecole da bambini. Ricorda, francese, gli affari di famiglia restano in famiglia. Chi ficca il naso dove non deve rischia di bruciarsi le dita.";
			link.l1 = "Adesso mi minacci, eh.";
			link.l1.go = "uncle_6";
		break;
		
		case "uncle_6":
			int icpy = GetOfficersQuantity(pchar);
			iTotalTemp = 10000+10000*icpy;
			dialog.text = "Non è una minaccia, capitano, è una promessa. Ascolta ragazzo, ne hai viste di onde, ma siccome ti prendo per uno sventurato illuso e non un nemico, ascolta la mia offerta semplice e magnanima: vattene. Non voglio spargere sangue qui. Dei nostri affari di famiglia non hai da impicciarti. Sono persino disposto a ripagarti per i guai che ti ha causato quel mio nipote idiota - "+FindRussianMoneyString(iTotalTemp)+" pezzi da otto. Prendili e levati dai piedi intero. Rifiuta la mia offerta e ti rimanderemo alla tua nave a fettine sottili.";
			link.l1 = "La famiglia prima di tutto, dico sempre io. Non sono affari miei allora, dai i soldi e 'che il diavolo ti accompagni'.";
			link.l1.go = "uncle_7";
			link.l2 = "La tua storia puzza più del letame della tua piantagione. Don Domingo sarà pure un mascalzone, ma tu, señor, sei il diavolo in persona!";
			link.l2.go = "uncle_8";
		break;
		
		case "uncle_7":
			AddMoneyToCharacter(pchar, iTotalTemp);
			dialog.text = "Sapevo che eri un uomo di buon senso. Prendi i tuoi dobloni e addio, capitano. E la prossima volta, evita di frugare nei panni sporchi degli altri – non ti porterà mai riconoscenza.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_UncleExit");
		break;
		
		case "uncle_8":
			dialog.text = "Un diavolo? Allora sarà un piacere mandarti dritto all’inferno!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQP_UncleFight");
		break;
		
		case "ugo":
			pchar.quest.FMQP_SantoDomingoOver.over = "yes";
			PlaySound("Voice\English\Serve_senior.wav");
			dialog.text = TimeGreeting()+" signor. Come posso esservi utile?";
			link.l1 = "Salve. Perdona l’intrusione, ma questa è la dimora del Signor Domingo Albalate?";
			link.l1.go = "ugo_1";
		break;
		
		case "ugo_1":
			dialog.text = "Sì, questa è la dimora degli Albalate. È modesta ma accogliente. Il mio nome è Ugo, servo il giovane padrone. Sei qui per lui?";
			link.l1 = "Sì, señor. Don Domingo mi ha invitato da lui non molto tempo fa. È stato molto convincente. Posso incontrarlo?";
			link.l1.go = "ugo_2";
		break;
		
		case "ugo_2":
			dialog.text = "Ahimè, mio buon caballero, Don Domingo non è in casa al momento. A dire il vero, piacerebbe anche a me sapere dove sia finito quel monellaccio... ehm, perdonate, quel giovane señor. Posso chiedere che affari avete con lui?";
			link.l1 = "Beh... ho aiutato don Domingo per caso. È stato assalito da due mascalzoni in una taverna di Port-au-Prince. Ho dato una mano al vostro padrone a difendersi da quei... come li ha chiamati... maledetta canaglia. Don Domingo mi invitò qui dopo che avesse finito le sue indagini. Pensavo che ormai fosse tutto sistemato e così mi aspettavo di trovarlo a casa.";
			link.l1.go = "ugo_3";
		break;
		
		case "ugo_3":
			dialog.text = "Madre de Dios! Che storie spaventose racconti qui! Devo vedere subito il comandante – devo avvertirlo del pericolo che corre Don Domingo in questo momento! Signore, dovete andare e io devo sbrigarmi!";
			link.l1 = "Calmati, Ugo. Il tuo giovane padrone sta bene. Ha detto che i suoi documenti sono in regola, dovevano già lasciarlo andare, ed è per questo che sono qui. Credo che lo vedremo presto.";
			link.l1.go = "ugo_4";
		break;
		
		case "ugo_4":
			dialog.text = "Oh! Come avete potuto? Il mio giovane padrone, quel ragazzo ingenuo - e ora nelle grinfie di quei mangiarane francesi?! Senza contare quei ladroni che minacciano la sua vita? No, devo vedere il comandante! Signore, vi prego, andate!";
			link.l1 = "Va bene, va bene, non fare il prepotente. Me ne vado.";
			link.l1.go = "ugo_exit";
			link.l2 = "Señor, perché tanta agitazione? Ti ho già detto che al tuo padrone non corre alcun pericolo. Lasciami restare qui ad aspettare l’arrivo del signor Domingo, sono esausto dal lungo viaggio e apprezzerei la tua ospitalità. Vorrei dell’acqua fresca e un bel bagno caldo per sciacquare il vento salmastro dalla gola. Poi puoi andare alla guarnigione locale e fare tutto ciò che ti pare.";
			link.l2.go = "ugo_5";
		break;
		
		case "ugo_exit":
			DialogExit();
			LocatorReloadEnterDisable("Santodomingo_town", "houseSp4", true);
			DoQuestReloadToLocation("SantoDomingo_town", "reload", "houseSp4", "FMQP_SDMFail");
		break;
		
		case "ugo_5":
			dialog.text = "Señor, lasci questa casa subito!";
			link.l1 = "Ugo, dubito assai che a un servitore sia concesso parlare così a un gentiluomo. E dubito pure che Don Domingo approverebbe un simile trattamento verso chi gli ha salvato la pellaccia!";
			link.l1.go = "ugo_6";
		break;
		
		case "ugo_6":
			dialog.text = "Davvero? (chiamando al piano di sopra) Ragazzi, scendete giù, abbiamo un guaio!";
			link.l1 = "Che diavolo?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_SantoDomingoFight");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

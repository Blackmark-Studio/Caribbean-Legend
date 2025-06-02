// диалоги НПС по квесту 'В поисках Стража Истины'
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
		case "First time":
			dialog.text = "In che modo posso esserti utile?";
			link.l1 = "Scusa, non è nulla.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// пленный испанец
		case "spa_prisoner":
			PlaySound("Voice\English\Ransack_1.wav");
			dialog.text = "Cosa vuoi? Un altro interrogatorio? Vaffanmare!";
			link.l1 = "Señor, qual è il vostro nome?";
			link.l1.go = "spa_prisoner_1";			
		break;
		
		case "spa_prisoner_1":
			dialog.text = "Che diavolo t'importa del nome dell'uomo che stai per impiccare o fucilare? Bastardo! Sono stato tanto sciocco da cadere nelle tue grinfie, dopotutto...";
			link.l1 = "Signore, presentatevi. Non posso ciarlare con un uomo senza sapere come si chiama.";
			link.l1.go = "spa_prisoner_2";			
		break;
		
		case "spa_prisoner_2":
			dialog.text = "Don "+GetFullName(npchar)+". Ecco, contento adesso? E con chi ho l'onore di conversare?";
			link.l1 = "Il mio nome è "+GetFullName(pchar)+" . Hai mai sentito parlare di me prima d’ora?";
			link.l1.go = "spa_prisoner_3";			
		break;
		
		case "spa_prisoner_3":
			dialog.text = "No, maledizione! Ti sembro forse uno che conosce ogni vagabondo randagio delle Indie Occidentali che...";
			link.l1 = "Basta. Facciamola finita con le offese e comportiamoci da gentiluomini. Il tuo destino dipenderà da ciò che saprai dirmi. Se mi racconti qualcosa di interessante, farò richiesta per la tua liberazione sotto la mia custodia. Così potrai evitare la palla di moschetto o la forca che ti aspettano in questo momento.";
			link.l1.go = "spa_prisoner_4";			
		break;
		
		case "spa_prisoner_4":
			dialog.text = "Dio mio, questa è un'offerta a cui non posso dire di no. Che cosa vuoi sapere, señor?";
			link.l1 = "Chi ha orchestrato un attacco così massiccio a St. Pierre, e per quale diavolo di motivo?";
			link.l1.go = "spa_prisoner_5";			
		break;
		
		case "spa_prisoner_5":
			dialog.text = "Barone Ramon de Mendosa y Riba, il comandante della guarnigione dell’Isola di Providence. Ha mandato uno squadrone a saccheggiare la città e a portar via ogni ben di Dio che ci capitasse sotto mano.";
			link.l1 = "Qual era il tuo compito immediato durante l’assalto? Dillo chiaro: quali ordini ti дали?";
			link.l1.go = "spa_prisoner_6";			
		break;
		
		case "spa_prisoner_6":
			dialog.text = "Sono il comandante del battaglione di marina. Avevamo l’ordine di prendere il forte e di mettere fuori uso le sue batterie, così che non potessero sparare sulle nostre scialuppe mentre ci avvicinavamo alla città. Poi i miei uomini hanno partecipato all’assalto di Saint-Pierre stesso.";
			link.l1 = "Fosti messo al corrente dei tesori nascosti in città? Della loro quantità e valore?";
			link.l1.go = "spa_prisoner_7";			
		break;
		
		case "spa_prisoner_7":
			dialog.text = "Non avevamo notizie precise sulla quantità, ma il Barone de Mendosa y Riba ci ha riferito che sotto il forte è nascosto dell’argento e nei magazzini del porto si trovano materiali strategici indispensabili per la guerra: legno di ferro e seta navale.";
			link.l1 = "Hai trovato quei preziosi?";
			link.l1.go = "spa_prisoner_8";			
		break;
		
		case "spa_prisoner_8":
			dialog.text = "No. Non abbiamo trovato né l’uno né l’altro. I magazzini erano colmi della solita mercanzia coloniale e sotto il forte c’erano polvere da sparo, armi e piombo. Ma non abbiamo avuto tempo per una ricerca più accurata... i rinforzi francesi sono piombati addosso e siamo stati costretti a batterci.";
			link.l1 = "Non ti sei chiesto come mai non hai trovato la roba di valore?";
			link.l1.go = "spa_prisoner_9";			
		break;
		
		case "spa_prisoner_9":
			dialog.text = "Certo che l'ho fatto, ma di solito non metto in discussione gli ordini.";
			link.l1 = "Ascolta bene ciò che sto per dirti. Forte St. Pierre non ha mai visto argento, e quei magazzini non hanno mai contenuto né legno di ferro né seta. Rifletti bene, señor, prima di rispondere, perché se la tua risposta non m’andrà a genio, mi volterò e lascerò che il destino ti travolga… un destino assai amaro.";
			link.l1.go = "spa_prisoner_10";			
		break;
		
		case "spa_prisoner_10":
			dialog.text = "Ascolto.";
			link.l1 = "Non credo proprio che l’unico scopo della vostra incursione fosse una semplice rapina. St.Pierre è una colonia modesta e piuttosto povera — non vale того, чтобы сюда слали целую эскадру во главе с линейным кораблём первого ранга. Scommetto che tu, il tuo comandante o qualcun altro avevate ordini o istruzioni aggiuntive. Cosa ti hanno detto davvero? Pensaci bene prima di rispondere...";
			link.l1.go = "spa_prisoner_11";			
		break;
		
		case "spa_prisoner_11":
			dialog.text = "";
			link.l1 = "Vuoi startene zitto? Va bene. Pensaci su un attimo, io aspetto.";
			link.l1.go = "spa_prisoner_12";			
		break;
		
		case "spa_prisoner_12":
			dialog.text = "Señor, la mia vita dipenderà dalla mia risposta?";
			link.l1 = "Esatto.";
			link.l1.go = "spa_prisoner_13";			
		break;
		
		case "spa_prisoner_13":
			dialog.text = "Ho qualcosa... Ma devi giurarmi che mi tirerai fuori di qui e mi riscatterai per farmi tornare in Spagna.";
			link.l1 = "Se mi dici qualcosa che meriti la mia attenzione, giuro sulla Santa Croce che ti porterò vivo sulla mia nave per il riscatto, e ti risparmierò dall’impiccagione.";
			link.l1.go = "spa_prisoner_14";			
		break;
		
		case "spa_prisoner_14":
			dialog.text = "D'accordo. Don Diego de Montoya ha ordinato al nostro battaglione di marines che, con la massima segretezza e urgenza, dobbiamo trovare e catturare un uomo di nome Miguel Dichoso, che si trova da qualche parte a St. Pierre sotto la protezione delle autorità.";
			link.l1 = "Continua pure. Chi diavolo è Diego de Montoya?";
			link.l1.go = "spa_prisoner_15";			
		break;
		
		case "spa_prisoner_15":
			dialog.text = "L’ufficiale al comando dello squadrone. È scappato subito dopo il tuo… teatrale arrivo.";
			link.l1 = "Chi è costui, questo Don Diego?";
			link.l1.go = "spa_prisoner_16";			
		break;
		
		case "spa_prisoner_16":
			dialog.text = "So solo che è il rappresentante ufficiale del Barone de Mendosa y Riba, la sua mano destra e il braccio per le faccende più delicate.";
			link.l1 = "Interessante... E chi sarebbe Miguel Dichoso, l’uomo per cui, a quanto pare, tutta questa catastrofe è stata orchestrata? Dev’essere un bel mascalzone, eh?";
			link.l1.go = "spa_prisoner_17";			
		break;
		
		case "spa_prisoner_17":
			dialog.text = "Ricordi il tuo giuramento, signore?";
			link.l1 = "Sì. E ti assicuro che se continui a raccontare la tua storia, finirai come testimone chiave sulla mia nave e poi... beh, troverò il modo di scaricarti in qualche colonia spagnola. Ma prima mi dirai tutto quello che sai.";
			link.l1.go = "spa_prisoner_18";			
		break;
		
		case "spa_prisoner_18":
			dialog.text = "Miguel Dichoso era un tempo compagno d'armi del barone, ma si mormora che abbia tradito. Il signor de Mendosa y Riba lo vuole vivo, dunque ci è stato ordinato di non toccare un capello a Dichoso, costi quel che costi.";
			link.l1 = "Anche Dichoso è uno spagnolo?";
			link.l1.go = "spa_prisoner_19";			
		break;
		
		case "spa_prisoner_19":
			dialog.text = "Sì. Don Diego de Montoya ci ha dato una descrizione approssimativa e ha ordinato che ogni uomo somigliante a Dichoso fosse consegnato subito a lui. Ma, data la breve finestra prima della vostra controffensiva, non abbiamo avuto il tempo di cercare.";
			link.l1 = "Conoscevi personalmente Dichoso?";
			link.l1.go = "spa_prisoner_20";			
		break;
		
		case "spa_prisoner_20":
			dialog.text = "No, solo di fama. Non ho mai visto quell’uomo prima d’ora. Alcuni dei miei colleghi ufficiali lo conoscevano di persona. Tutti loro sono morti.";
			link.l1 = "Che razza di tradimento ha commesso Dichoso contro il vostro Don Mendosa, se quello ha mandato un’intera squadra alle sue calcagna?";
			link.l1.go = "spa_prisoner_21";			
		break;
		
		case "spa_prisoner_21":
			dialog.text = "Te lo racconterò. Il barone è giunto nei Caraibi solo di recente dalla Spagna. Doveva proteggere i convogli della Flotta del Tesoro, invece si è lasciato sedurre dalle leggende d’oro indiano e ha puntato verso l’entroterra... bramando ricchezze nascoste. Si convinse che in fondo alle giungle dello Yucatan si cela una città Maya antichissima – Tayasal, la mitica città dell’oro.\nIl barone spedì diverse spedizioni a cercarla, ma ognuna fu divorata dalla selva selvaggia. Scommetto il mio cappello che tutti quanti sono stati fatti a pezzi dai bellicosi Itza che abitano laggiù.\nAlla fine l’Inquisitore Vincento perse la pazienza con le fantasie di Don Mendosa e lo spreco di uomini. Avvisò Madrid della faccenda. Il viceré proibì al barone di inseguire la città leggendaria e gli ordinò di tornare ai suoi doveri. Fu allora che spuntò Miguel Dichoso.\nConvince il barone a tentare ancora. E, contro ogni aspettativa, stavolta va a segno. Trovano le rovine d’una città antica, e una montagna di oro tempestato di gemme. Ma sulla via del ritorno li assale la tribù dei Mosquito.\nTutti, tranne Miguel, periscono. I dardi indigeni son bagnati in un veleno locale: basta un graffietto, e in pochi giorni ti prende una morte lenta e atroce. Dichoso torna a Providence con quanto oro riesce a portarsi dietro.\nCarajo! Il barone era fuori di sé dalla gioia, manda dispacci urgenti a Madrid e a Padre Vincento a Santiago, certo voleva sbandierare la sua vittoria al reverendo. Presto un vascello fu allestito per riportare il tesoro in Spagna. Dichoso si offrì come scorta.";
			link.l1 = "Fammi indovinare. Non ha consegnato l’oro, vero?";
			link.l1.go = "spa_prisoner_22";			
		break;
		
		case "spa_prisoner_22":
			dialog.text = "Esatto, señor! La fregata è sparita senza lasciare traccia, assieme a tutto il carico e all’equipaggio, compreso Dichoso. Il barone era furibondo. Ancora una volta fu umiliato all’Escorial, con grande gioia di padre Vincento. Ora don Mendosa è un uomo accecato dal desiderio di riprendersi l’orgoglio ferito, il tesoro perduto e Miguel Dichoso.";
			link.l1 = "Non potrebbe essere che la fregata sia solo incappata in una tempesta e sia affondata? O magari finita nelle grinfie dei filibustieri?";
			link.l1.go = "spa_prisoner_23";			
		break;
		
		case "spa_prisoner_23":
			dialog.text = "Il barone, preso dalla furia, giurò che era certo che Dichoso l'avesse tradito. I dettagli non li conosco. Dopo qualche settimana, don Diego de Montoya arrivò con nuove notizie: Miguel Dichoso potrebbe trovarsi a Saint-Pierre.";
			link.l1 = "Hm. Interessante. Quei tesori indiani di nuovo. Tutto sembra sospettosamente collegato a loro... Dunque, non hai trovato Dichoso?";
			link.l1.go = "spa_prisoner_24";			
		break;
		
		case "spa_prisoner_24":
			dialog.text = "No. E a dirla tutta, sarei sorpreso se fosse mai passato di qui. Il barone è talmente ossessionato dall’idea di mettere le mani su Dichoso che si berrebbe anche le fandonie più assurde.";
			link.l1 = "Dimmi, "+npchar.name+", come ha fatto Don Mendosa a scoprire questa... ehm... città di Tayasal? Non l’ha mica sognata, vero? C’erano delle prove o qualcos’altro?";
			link.l1.go = "spa_prisoner_25";			
		break;
		
		case "spa_prisoner_25":
			dialog.text = "Fu padre Vincento il primo a sentire parlare della presunta esistenza di Tayasal e della città d’oro. Dove abbia raccolto tali voci, non ne ho la minima idea...";
			link.l1 = "Che storia intrigante. Padre Vincento s’è inventato di sana pianta la leggenda di Tayasal, ha avvisato la Spagna di sua iniziativa, e ora va seminando zizzania tra i progetti del barone...";
			link.l1.go = "spa_prisoner_26";			
		break;
		
		case "spa_prisoner_26":
			dialog.text = "In quanto buon cattolico dovresti sapere bene come lavorano questi reverendi padri del Santo Tribunale... Non ha avvisato Madrid senza un secondo fine. Sta tramando qualcosa, ma pare che l’arrivo del barone non rientrasse nei suoi piani. Comunque, non ne so altro. Non ho mai avuto la brama di farmi impicciare dall’Inquisizione.";
			link.l1 = "D'accordo. Mi hai raccontato cose davvero interessanti, "+npchar.name+", e fedele al mio giuramento ti porto via di qui. Tornerò a prenderti più tardi, ma per ora... lasciami riflettere un poco su ciò che mi hai appena raccontato...";
			link.l1.go = "spa_prisoner_27";			
		break;
		
		case "spa_prisoner_27":
			DialogExit();
			pchar.questTemp.Guardoftruth = "think";
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto3", "GuardOT_MCthink", -1);
		break;
		
		case "spa_prisoner_28":
			PlaySound("Voice\English\Ransack_2.wav");
			dialog.text = "Señor? Manterrete la vostra parola?";
			link.l1 = "Le promesse le mantengo sempre. Oggi la sorte ti sorride, "+npchar.name+". Vieni con me a Santiago, a Cuba. Ti spiegherò meglio il mio piano quando arriveremo. Ma per ora, benvenuto a bordo. Ti scorteranno al porto e ti condurranno sulla mia nave.";
			link.l1.go = "spa_prisoner_29";			
		break;
		
		case "spa_prisoner_29":
			dialog.text = "La mia gratitudine, capitano. Lieto di vedere che siete un gentiluomo di parola.";
			link.l1 = "Potrai ringraziarmi più tardi. Ora sarai mio ospite, ma sotto sorveglianza. Non prenderla a male, mi servi ancora.";
			link.l1.go = "spa_prisoner_30";			
		break;
		
		case "spa_prisoner_30":
			dialog.text = "Capisco, señor. Vi do la mia parola d’onore, come ufficiale spagnolo, che non tenterò la fuga.";
			link.l1 = "Il buon Dio protegge chi sta in guardia. Ci si vede a bordo.";
			link.l1.go = "spa_prisoner_31";			
		break;
		
		case "spa_prisoner_31":
			DialogExit();
			pchar.questTemp.Guardoftruth = "cuba";
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			chrDisableReloadToLocation = false;//открыть локацию
			pchar.quest.GuardOT_exitbase.win_condition.l1 = "ExitFromLocation";
			pchar.quest.GuardOT_exitbase.win_condition.l1.location = pchar.location;
			pchar.quest.GuardOT_exitbase.function = "GuardOT_ExitFrombase";
			AddQuestRecord("Guardoftruth", "4");
		break;
		
		case "spa_prisoner_32":
			PlaySound("Voice\English\Serve_senior.wav");
			dialog.text = "Capitano, quali sono i vostri scopi qui a Cuba? Siete forse venuto per sbarcarmi? Non oso nemmeno sperarlo...";
			link.l1 = "Proprio così, sono qui per riportarti tra i tuoi compatrioti. Tuttavia, la ragione del mio arrivo in queste terre è ben più intricata di così. Ma ormai non riguarda più te. Ti lascerò andare subito, senza riscatto, ma solo se mi giurerai due cose.";
			link.l1.go = "spa_prisoner_33";			
		break;
		
		case "spa_prisoner_33":
			dialog.text = "Che diavolo sono?";
			link.l1 = "La prima cosa è che ti consegnerò una lettera sigillata. La porterai di persona all’Inquisitore di Santiago, Padre Vincento. Se ti chiederà chi te l’ha affidata e come l’hai ottenuta, raccontagli la verità...";
			link.l1.go = "spa_prisoner_34";			
		break;
		
		case "spa_prisoner_34":
			dialog.text = "";
			link.l1 = "La seconda è che non presterai alcun aiuto né favorirai tentativi di trovarmi e assalire la mia nave, almeno per una settimana. D’accordo?";
			link.l1.go = "spa_prisoner_35";			
		break;
		
		case "spa_prisoner_35":
			dialog.text = "È tutto qui?";
			link.l1 = "Sì, tutto qui. Soddisfa le mie condizioni e sarai libero di andartene.";
			link.l1.go = "spa_prisoner_36";			
		break;
		
		case "spa_prisoner_36":
			dialog.text = "Te lo giuro, señor, consegnerò la lettera a Padre Vincento di persona e non farò nulla che possa provocare l’ira della guarnigione di Santiago contro di te o la tua nave. Puoi stare tranquillo, manterrò la mia parola. Sono uno spagnolo e rispetto gli avversari valorosi e nobili.";
			link.l1 = "D'accordo, Don "+GetFullName(npchar)+", Accetto il tuo giuramento e ti lascio libero proprio ora. Prendi questa lettera per l’Inquisitore. Sei un uomo libero, adesso.";
			link.l1.go = "spa_prisoner_37";			
		break;
		
		case "spa_prisoner_37":
			Log_Info("You've given the letter");
			PlaySound("interface\important_item.wav");
			dialog.text = "Addio, signore. Spero che mai più ci incroceremo su un campo di battaglia. Mi affliggerebbe assai.";
			link.l1 = "Addio...";
			link.l1.go = "spa_prisoner_38";			
		break;
		
		case "spa_prisoner_38":
			DialogExit();
			RemovePassenger(pchar, npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			chrDisableReloadToLocation = false;//открыть локацию
			AddQuestRecord("Guardoftruth", "5");
			pchar.quest.GuardOT_mayak.win_condition.l1 = "Timer";
			pchar.quest.GuardOT_mayak.win_condition.l1.date.hour  = sti(GetTime()-(rand(4)));
			pchar.quest.GuardOT_mayak.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.GuardOT_mayak.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.GuardOT_mayak.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.GuardOT_mayak.win_condition.l2 = "location";
			pchar.quest.GuardOT_mayak.win_condition.l2.location = "mayak9";
			pchar.quest.GuardOT_mayak.function = "GuardOT_CreateVinsentoAgent";
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;
		
		case "spa_prisoner_39":
			dialog.text = "Dio mio, che incontro fortunato! Salute, monsieur "+GetFullName(pchar)+"! Vedo che sei diventato un ospite gradito a Santiago. Lavori forse per la Santa Inquisizione?";
			link.l1 = "Salute, señor "+npchar.name+". Pensavo che non ci saremmo mai più rivisti, almeno non in circostanze amichevoli! No, sono solo passato a far visita a padre Vincento. E tu invece? Ora servi a Santiago?";
			link.l1.go = "spa_prisoner_40";
		break;
		
		case "spa_prisoner_40":
			dialog.text = "Dopo che mi hai tirato fuori dalle grinfie dei sbirri, sono stato costretto a restare a Santiago, tornare a Providence sarebbe stato un suicidio... ma come vedi, ho mantenuto la parola. Nessuna nave spagnola alle calcagna...";
			link.l1 = "Sono lieto che siamo entrambi uomini di parola.";
			link.l1.go = "spa_prisoner_41";
		break;
		
		case "spa_prisoner_41":
			dialog.text = "Ascolta, capitano, che ne dici di alzare un bicchiere di rum per festeggiare il nostro incontro, per così dire? Mai avrei pensato di proporlo a un francese, ma voi, señor, fate eccezione.";
			link.l1 = "Ma certo! Non mi dispiacerebbe sciacquarmi la bocca con un po' di rum. Andiamo in taverna.";
			link.l1.go = "spa_prisoner_42";
		break;
		
		case "spa_prisoner_42":
			DialogExit();
			NextDiag.CurrentNode = "spa_prisoner_43"; 
			FreeSitLocator("Santiago_tavern", "sit_front4");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "Santiago_tavern", "sit", "sit_front4", "GuardOT_SpaOfficerInTavern", -1);
		break;
		
		case "spa_prisoner_43":
			LAi_SetSitType(Pchar);
			dialog.text = "Ah, salute!";
			link.l1 = "A che brindiamo, signor ufficiale?";
			link.l1.go = "spa_prisoner_44";
		break;
		
		case "spa_prisoner_44":
			dialog.text = "Beviamo a qualcosa di neutro, ma che riguarda entrambi. Per esempio, al valoroso e fruttuoso servizio per la propria patria! Ognuno ha la sua, dopotutto!";
			link.l1 = "E beviamo anche ai nostri sovrani che finalmente trovino un accordo, e che francesi e spagnoli smettano di azzuffarsi sia in patria che nei Caraibi.";
			link.l1.go = "spa_prisoner_45";
		break;
		
		case "spa_prisoner_45":
			dialog.text = "Ben detto, capitano! Alla pace! Ora vi mostro come si beve in Spagna! Arriba, abajo, al centro e giù per la gola!";
			link.l1 = "Alla pace... (bevendo)";
			link.l1.go = "spa_prisoner_46";
		break;
		
		case "spa_prisoner_46":
			dialog.text = "Ahah! Il rum cubano è davvero il migliore di tutti i Caraibi...";
			link.l1 = "Sono d'accordo. Dimmi, hanno cercato di punirti per essere stato catturato a Saint-Pierre?";
			link.l1.go = "spa_prisoner_47";
		break;
		
		case "spa_prisoner_47":
			dialog.text = "Per fortuna me la sono cavata con una pacca sulle mani. Quella disgrazia ormai è acqua passata. Qui nelle colonie hanno sempre bisogno di ufficiali, dopotutto.";
			link.l1 = "E il tuo comandante... come si chiamava... Diego, vero? Com'è andata a finire quella scorribanda a mani vuote? Gli hanno tolto i gradi?";
			link.l1.go = "spa_prisoner_48";
		break;
		
		case "spa_prisoner_48":
			dialog.text = "Oh, no! Il nostro caro Diego de Montoya è intoccabile finché ha Don Ramon de Mendosa y Riba alle sue spalle. A proposito, Don Diego era a Santiago proprio ieri. È arrivato da San Jose.";
			link.l1 = "Ma davvero? Che storia interessante! Meno male che non ci siamo incrociati per strada, temo che quella faccenda sarebbe finita a fil di spada, ahah!";
			link.l1.go = "spa_prisoner_49";
		break;
		
		case "spa_prisoner_49":
			dialog.text = "Don Diego non ha tempo per te adesso, capitano. Ha troppo da perdere in questo momento per rischiare la pelle in duello. Sta tramando qualcosa insieme al Barone Mendosa nella Main Occidentale. Ha radunato una squadra a L'Avana e conta di salpare per la Spagna da un giorno all'altro.";
			link.l1 = "Anche tu fai parte della sua ciurma?";
			link.l1.go = "spa_prisoner_50";
		break;
		
		case "spa_prisoner_50":
			dialog.text = "No. Domani partirò per la guarnigione di San Juan, a Puerto Rico. Ormai su Providence, con Don Mendosa presente, non sono più il benvenuto.";
			link.l1 = "E allora, beviamo al tuo nuovo incarico: che ti aspettino solo giorni lieti e belle fanciulle!";
			link.l1.go = "spa_prisoner_51";
		break;
		
		case "spa_prisoner_51":
			dialog.text = "Molte grazie, monsieur. Che vi giungano mille auguri d’ogni sorta. Ah, credo sia l’ora di andarmene. Finirò quest’ultimo bicchiere e poi vi lascerò.";
			link.l1 = "Vaya con Dio, señor "+npchar.name+"Forse ci rivedremo un giorno, in tempi più tranquilli.";
			link.l1.go = "spa_prisoner_52";
		break;
		
		case "spa_prisoner_52":
			DialogExit();
			AddDialogExitQuest("GuardOT_SpaOfficerOutTavern");
		break;
		
		case "spa_prisoner_53":
			PlaySound("Voice\English\other\OZGi-01.wav");
			dialog.text = "Just as I told you, Don Diego: the fish took the bait; hook, line, and sinker... Oh, looks like we meet again, monsieur. Unfortunately, not under the peaceful auspices that we wished.";
			link.l1 = ""+npchar.name+"Eh! Non me l’aspettavo proprio. Chissà perché ti facevo un ufficiale onesto, nobile. Mi sbagliavo di grosso, a quanto pare.";
			link.l1.go = "spa_prisoner_54";
		break;
		
		case "spa_prisoner_54":
			dialog.text = "Che cosa ti fa pensare che io sia in torto? Ho mantenuto la mia parola, non ti ho giurato eterna amicizia. Nulla è cambiato, monsieur. Rimani un nemico della Spagna e mio nemico personale. Qui non siamo a Santiago, non c’è padre Vincento e il suo bel lasciapassare non ti servirà a nulla...";
			link.l1 = "Ah, così stanno le cose? Io invece trovo che invitarmi a bere del rum e chiacchierare amichevolmente, mentre cerchi di attirarmi in una trappola, sia una bella carognata, non credi, señor?"+npchar.name+"?";
			link.l1.go = "spa_prisoner_55";
		break;
		
		case "spa_prisoner_55":
			dialog.text = "Tu osi chiamarmi traditore, maledetto maricon?!";
			link.l1 = "...";
			link.l1.go = "spa_prisoner_56";
		break;
		
		case "spa_prisoner_56":
			DialogExit();
			sld = CharacterFromID("Diego");
			sld.dialog.currentnode = "shore";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		// посланец Винсенто
		case "vinsentoagent":
			PlaySound("Voice\English\other\OZGi-02.wav");
			dialog.text = "Ehi, tu! Sì, sì, proprio tu! "+GetFullName(pchar)+"?";
			link.l1 = "Aye, compare. Son proprio io.";
			link.l1.go = "vinsentoagent_1";			
		break;
		
		case "vinsentoagent_1":
			dialog.text = "Ho ricevuto una lettera da una persona importante. Sai già di chi si tratta.";
			link.l1 = "Lo so, dammelo qua.";
			link.l1.go = "vinsentoagent_2";			
		break;
		
		case "vinsentoagent_2":
			GiveItem2Character(pchar, "specialletter");
			ChangeItemDescribe("specialletter", "itmdescr_specialletter_vinsento");
			sld = ItemsFromID("specialletter");
			sld.text = "Letter_Vincento";
			dialog.text = "Ecco qua. Che ne dici di qualche moneta per il mio disturbo?";
			if (sti(Pchar.money) >= 2000)
			{
				link.l1 = "Prendi un po' d'argento. Te lo sei guadagnato onestamente.";
				link.l1.go = "vinsentoagent_2_1";	
				AddCharacterExpToSkill(pchar, "Leadership", 50);
			}
			else
			{
				link.l1 = "Stai cercando di gabbarmi, compare? Hai già preso il tuo oro per la consegna.";
				link.l1.go = "vinsentoagent_2_2";
			}
		break;
		
		case "vinsentoagent_2_1":
			AddMoneyToCharacter(pchar, -2000);
			dialog.text = "Grazie, ragazzo. È un piacere trattare con un gentiluomo così generoso.";
			link.l1 = "Va' via subito, e non fiatare su quel che è successo qui.";
			link.l1.go = "vinsentoagent_3";			
		break;
		
		case "vinsentoagent_2_2":
			dialog.text = "Il lupo dell'Avana è tuo compare...";
			link.l1 = "Eh? Sei ancora qui...";
			link.l1.go = "vinsentoagent_3";			
		break;
		
		case "vinsentoagent_3":
			DialogExit();
			npchar.lifeday = 0;
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			chrDisableReloadToLocation = false;//открыть локацию
		break;
		
		// боцман Гая Марше
		case "boatsvandega":
			dialog.text = "Benvenuto a bordo dell’‘Ammirabile’, capitano "+GetFullName(pchar)+"!";
			link.l1 = TimeGreeting()+"! Sorprendente. Mi conosci, forse?";
			link.l1.go = "boatsvandega_1";			
		break;
		
		case "boatsvandega_1":
			dialog.text = "Chi nelle colonie francesi non ha sentito parlare del gran capitano chiamato "+GetFullName(pchar)+", quello che ha fatto saltare i denti a uno squadrone spagnolo guidato da una nave da guerra che assaltava St. Pierre e ha mandato all'altro mondo tutta la ciurma nemica! Sei un eroe nazionale!";
			link.l1 = "Oh, andiamo. 'Un eroe'... Sono solo un soldato che compie il suo dovere verso la Francia.";
			link.l1.go = "boatsvandega_2";
		break;
		
		case "boatsvandega_2":
			dialog.text = "Non credo che molti soldati avrebbero saputo fare quel che hai fatto tu, capitano... Eh, ti offrirei volentieri un po' di rum alla taverna, ma ahimè: il capitano ha proibito ai suoi uomini anche solo un goccio di rum, e non voglio dare il cattivo esempio...";
			link.l1 = "Hm... Quindi non sei tu il capitano?";
			link.l1.go = "boatsvandega_3";
		break;
		
		case "boatsvandega_3":
			dialog.text = "Sembro forse un capitano? Ahah! No, sono solo il nostromo. Mi chiamo Serge Degas. Il nostro capitano, Gaius Marchais, si scola la giornata in taverna, mentre noi qui marcimmo ad aspettare какую-то ‘carovana’ di mercanti. Il capitano deve ancora pagarci la paga, a noi e a tutto l’equipaggio, ormai siamo rimasti a secco fino all’ultima moneta...";
			link.l1 = "Che succede? La carovana spagnola della vaniglia non si fa vedere per farsi spennare?";
			link.l1.go = "boatsvandega_4";
		break;
		
		case "boatsvandega_4":
			dialog.text = "Neanche per sogno! Il nostro capitano ha smesso con la pirateria dopo aver messo le mani su questo galeone. Vedi, aveva sentito che una carovana mercantile diretta in Europa si sarebbe fermata presto a Guadalupa, e avrebbero comprato vaniglia. Così ha riempito le stive fino all’orlo a Bridgetown! Sperava di venderla a trecento pesos la cassa, sì, bella speranza!\nArriviamo e della carovana, ovviamente, neanche l’ombra. Vendere la vaniglia alla gente del posto? Una perdita secca. Così eccoci qua, ad aspettare questi ‘mercanti’; sono certo che arriveranno, magari tra un giorno... o tra tre anni. Il Capitano intanto si scolaccia la taverna tutto il giorno, fastidio reale che non è altro, scoccia tutti quanti. Torna a bordo solo per svenire. Ora, finalmente, è disposto a venderla a duecento pesos solo per non rimetterci.\nAbbiamo investito tutto il denaro in quel carico. Un giorno di questi l’equipaggio lo legherà e svenderà la vaniglia pur di coprire i debiti... Giuro, lo sento che ci siamo quasi.";
			link.l1 = "Aye...che rode il tuo capitano?";
			link.l1.go = "boatsvandega_5";
		break;
		
		case "boatsvandega_5":
			dialog.text = "Ebbene, se un lavoro merita d’esser fatto, va fatto come si deve. Lui non fa né одно, né altro. Come mercante, fa pena a contrattare. Sarebbe stata un’altra storia, se almeno trasportasse merci come si deve, ma voleva sentirsi un vero negoziante, lui. Spero che una notte inciampi e cada fuoribordo...";
			link.l1 = "Ti ho capito, Serge. Non ti crucciare, sono certo che un giorno la tua... carovana salterà fuori.";
			link.l1.go = "boatsvandega_6";
		break;
		
		case "boatsvandega_6":
			dialog.text = "Oh, non credo nei miracoli, capitano. Forse ci rincontreremo un giorno per sorseggiare un po' di rum... darei qualsiasi cosa per un goccio di rum adesso...";
			link.l1 = "Buona fortuna, compare.";
			link.l1.go = "boatsvandega_7";
		break;
		
		case "boatsvandega_7":
			DialogExit();
			NextDiag.currentnode = "boatsvandega_8";
			npchar.DeckDialogNode = "boatsvandega_8";
			// активируем каракку
			sld = characterFromId("GOT_Gevarra");
			sld.Dialog.Filename = "Quest\Sharlie\Guardoftruth.c";
			sld.DeckDialogNode = "gevarra";
			AddQuestRecord("Guardoftruth", "16");
		break;
		
		case "boatsvandega_8":
			dialog.text = "Ehi, capitano, mi farei volentieri un sorso di rum!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "boatsvandega_8";
		break;
		
		// Гай Марше
		case "marshe_tavern":
			PlaySound("Voice\English\tavern\Kontrabandisti-08.wav");
			dialog.text = NPCStringReactionRepeat("Oh! Non sarai tu della nave mercantile, vero? No? Ah, perdona la mia svista. Certo che no... Che sciocco sono stato.","Non sono dell’umore, monsieur, quindi vai a chiacchierare con qualcun altro.","Ah, ancora tu?!","Ehm...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Non te ne crucciare, compare. Succede a tutti.","Bevi un po' di rum, capitano. Ti alleggerirà le pene, almeno un poco...","Non agitarti, compare. Ti fa male alla salute.","Va bene, va bene. Me ne vado.",npchar,Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
			NextDiag.TempNode = "marshe_tavern";
		break;
		
		case "marshe_lay":
			PlaySound("Voice\English\citizen\convict-03.wav");
			dialog.text = "A argh... Mm... Maledizione, che diavolo è questo?.. ";
			link.l1 = "Zitto, compare... Non fare rumore...";
			link.l1.go = "marshe_lay_1";
		break;
		
		case "marshe_lay_1":
			PlaySound("Voice\English\citizen\convict-02.wav");
			dialog.text = "Eh? Che? Maledizione!";
			link.l1 = "";
			link.l1.go = "marshe_lay_2";
		break;
		
		case "marshe_lay_2":
			DialogExit();
			LAi_SetgroundSitType(npchar);
			NextDiag.currentnode = "marshe_sitground";
		break;
		
		case "marshe_sitground":
			PlaySound("Voice\English\EvilPirates07.wav");
			dialog.text = "Aaah! Chi sei tu? Che diavolo vuoi da me?";
			link.l1 = "Se non chiudi quella bocca, ti faccio saltare i denti, capito? Dove sono i sacri calici che hai arraffato quando hai preso questa nave?";
			link.l1.go = "marshe_sitground_1";
		break;
		
		case "marshe_sitground_1":
			dialog.text = "Quali navi? Non ho la minima idea di cosa tu stia blaterando! Questa è la mia nave!";
			link.l1 = "La tua nave? Fino a poco tempo fa si chiamava 'Santa Margarita' e batteva bandiera spagnola... Dimmi, dove sono quei sacri oggetti? Un ostensorio d’oro, una croce tempestata di lapislazzuli, e un turibolo d’oro? Che ne hai fatto? Non starai mica dicendo che li hai venduti, vero?";
			link.l1.go = "marshe_sitground_2";
		break;
		
		case "marshe_sitground_2":
			dialog.text = "Oh Dio, non credo alle mie orecchie... sei spagnolo? Oh, no... non sei spagnolo! Sei francese! Peggio ancora! Ti sei venduto a quei luridi castigliani! Quanto pagano adesso per l’anima di un francese? Non ti dirò un accidente, traditore! Quelle cianfrusaglie non le avrai mai!";
			link.l1 = "Nessuna parola, eh? Va benissimo così. Questo non è certo il posto migliore per un interrogatorio... Ti metteremo il bavaglio, così non strillerai, poi ti porteremo sulla mia scialuppa... prima o poi parlerai, compare. Su questo non ho il minimo dubbio.";
			link.l1.go = "marshe_sitground_3";
		break;
		
		case "marshe_sitground_3":
			dialog.text = "Traditore spagnolo! Faresti meglio a...";
			link.l1 = "Silenzio, canaglia... Seguimi da vicino o ti stendo e ti trascino per i piedi su tutto il ponte.";
			link.l1.go = "marshe_sitground_4";
		break;
		
		case "marshe_sitground_4":
			DialogExit();
			RemoveAllCharacterItems(npchar, true);
			ChangeCharacterAddressGroup(npchar, "Deck_Galeon_Ship", "goto", "stand");
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			pchar.quest.GuardOT_marchfromgaleon.win_condition.l1 = "locator";
			pchar.quest.GuardOT_marchfromgaleon.win_condition.l1.location = "Deck_Galeon_Ship";
			pchar.quest.GuardOT_marchfromgaleon.win_condition.l1.locator_group = "reload";
			pchar.quest.GuardOT_marchfromgaleon.win_condition.l1.locator = "reload2";
			pchar.quest.GuardOT_marchfromgaleon.function = "GuardOT_ExitGaleon";
		break;
		
		// капитан каракки - Карлос Геварра
		case "gevarra":
			dialog.text = "In che modo posso esservi utile, messere?";
			link.l1 = "Come vanno le cose, capitano? Cosa vi porta a Basse-Terre? Se non erro, siete spagnolo che naviga sotto bandiera olandese, vero?";
			link.l1.go = "gevarra_1";			
		break;
		
		case "gevarra_1":
			dialog.text = "Qual è il problema, signore? Sì, sono spagnolo. Si capisce dal nome e dal tipo della mia nave, ma mi trovo qui del tutto legalmente. Ho una patente dalla Compagnia Olandese delle Indie Occidentali, dunque...";
			link.l1 = "Non ti agitare, señor! In verità siamo ben lieti che tu sia spagnolo... Dimmi, sei qui per caricare o scaricare la stiva?";
			link.l1.go = "gevarra_2";			
		break;
		
		case "gevarra_2":
			dialog.text = "Ho portato mercanzia da L’Avana e l’ho smerciata qui al mercato locale. Ora aspetto un carico redditizio, ché tornare a casa con la stiva vuota non для gente моего звания.";
			link.l1 = "Señor, ho una proposta d’affari per voi! Potreste guadagnare una bella somma se mi date una mano. Ne parliamo? Ah, come vi chiamate, di grazia?";
			link.l1.go = "gevarra_3";			
		break;
		
		case "gevarra_3":
			dialog.text = "Carlos. Capitano Carlos Guevara. Qual è la tua offerta?";
			link.l1 = "Devo acquistare una partita di vaniglia e spedirla a Cuba, a un uomo chiamato "+pchar.questTemp.Guardoftruth.LMname+", il guardiano del faro di Santiago. Tuttavia, ho un bel grattacapo. Prima di tutto, nessuna bottega ha la quantità di vaniglia che mi serve...";
			link.l1.go = "gevarra_4";			
		break;
		
		case "gevarra_4":
			dialog.text = "";
			link.l1 = "In secondo luogo, devo partire subito per Saint Christophe e non so quanto tempo resterò via. Sto perdendo soldi ogni santo giorno, capisci? È una dannata vergogna!";
			link.l1.go = "gevarra_5";			
		break;
		
		case "gevarra_5":
			dialog.text = "Capisco. Che peccato, señor. Non si può guadagnare tutto l’oro del mondo, dopotutto. Allora, cosa vuoi da me?";
			link.l1 = "Guarda laggiù. Vedi quel galeone? È carico di vaniglia che mi serve come l’aria. Il guaio è che il capitano si è messo in testa una favola su una carovana di spezie che dovrebbe arrivare presto e comprare il suo carico a un guadagno, quasi trecento pesos per cassa!";
			link.l1.go = "gevarra_6";			
		break;
		
		case "gevarra_6":
			dialog.text = "Sì, di sprovveduti in giro ce n’è fin troppi al giorno d’oggi, e il denaro non resta mai a lungo in tasca a uno sciocco…";
			link.l1 = "Ingenuo è una cosa, ma questo è proprio uno scimunito! Gli ho offerto duecentodieci pesos per la sua vaniglia, qui non ne prenderebbe nemmeno duecento in bottega. E tu ci credi? Mi ha mandato al diavolo! Dice che la vende solo a duecentocinquanta!";
			link.l1.go = "gevarra_7";			
		break;
		
		case "gevarra_7":
			dialog.text = "Ahah! Che babbeo!";
			link.l1 = "Sì! Questo è praticamente ciò che gli ho detto. Ovviamente s'è infuriato con me... ma ho davvero bisogno di quella vaniglia! Ecco la mia proposta, señor. Io non sono un mercante, ma credo che voi siate un vero maestro nell’arte dell’accordo. E avete una stiva capientissima...";
			link.l1.go = "gevarra_8";			
		break;
		
		case "gevarra_8":
			dialog.text = "";
			link.l1 = "Convincilo tu, quel babbeo, a venderti il carico. Dopo che l’ho coperto d’insulti, a me non lo mollerà mai. Sono disposto a pagare duecentodieci pesos a cassa. Se riesci a spuntare un prezzo più basso, tieniti la differenza. E in cambio ti noleggio la barca per portare la vaniglia fino a Santiago.";
			link.l1.go = "gevarra_9";			
		break;
		
		case "gevarra_9":
			dialog.text = "Quanto sei disposto a sganciare per questa spedizione?";
			link.l1 = "Quanto vuoi?";
			link.l1.go = "gevarra_10";			
		break;
		
		case "gevarra_10":
			dialog.text = "Santiago è piuttosto lontana... trentamila pesos.";
			link.l1 = "È troppo, compare. Facciamo a metà, suvvia.";
			link.l1.go = "gevarra_11";			
		break;
		
		case "gevarra_11":
			dialog.text = "D'accordo, tanto mi ci trovo... Venticinquemila e non un peso di meno.";
			link.l1 = "Va bene. Il capitano del galeone si chiama Gaius Marchais. Passa le sue giornate a rimuginare nella taverna. Spero che tu riesca a convincerlo a separarsi dalle sue spezie.";
			link.l1.go = "gevarra_12";			
		break;
		
		case "gevarra_12":
			dialog.text = "Ho già fatto affari con idioti ben peggiori. Gli racconterò ogni dettaglio su chi sta mettendo in giro voci su quella carovana che, dicono, avrebbe dovuto comprare la merce a prezzi da rapina. Una volta convinto che son solo fandonie della sua testa, venderà, ne sono certo.";
			link.l1 = "Allora, abbiamo un patto?";
			link.l1.go = "gevarra_13";			
		break;
		
		case "gevarra_13":
			iTemp = sti(pchar.questTemp.Guardoftruth.VanilleQty)*210+25000;
			dialog.text = "Abbiamo un accordo se hai il denaro per la vaniglia e il trasporto. Come dicono gli allegri irlandesi: 'Fammi vedere i dobloni.'";
			if (sti(Pchar.money) >= iTemp)
			{
				link.l1 = "Ecco qua, dai un'occhiata. È tutto qui.";
				link.l1.go = "gevarra_14";
			}
			else
			{
				link.l1 = "Ho l’argento sulla mia nave. Vado a prenderlo e torno subito!";
				link.l1.go = "gevarra_14_no";
			}
		break;
		
		case "gevarra_14_no":
			DialogExit();
			NextDiag.currentnode = "gevarra_wait";
			npchar.DeckDialogNode = "gevarra_wait";
		break;
		
		case "gevarra_wait":
			iTemp = sti(pchar.questTemp.Guardoftruth.VanilleQty)*210+25000;
			dialog.text = "Hai portato il denaro?";
			if (sti(Pchar.money) >= iTemp)
			{
				link.l1 = "Ecco qua, dai un'occhiata. C'è tutto.";
				link.l1.go = "gevarra_14";
			}
			else
			{
				link.l1 = "La prendo subito!";
				link.l1.go = "exit";
			}	
		break;
		
		case "gevarra_14":
			if (stf(environment.time) < 24.0)
			{
				sTemp = "tomorrow";
				iTemp = 1;
			}
			else
			{
				sTemp = "today";
				iTemp = 0;
			}
			if (stf(environment.time) > 21.0 && stf(environment.time) < 7.0)
			{
				dialog.text = "Splendido! Mi piace trattare con partner di buon senso. Torna pure "+sTemp+" per le dieci del mattino. Credo che a quell’ora il nostro comune amico Gaius avrà già riacceso la testa.";
				link.l1 = "Fantastico! Ci vediamo dopo!";
				link.l1.go = "gevarra_15";
				pchar.quest.GuardOT_tradetimer.win_condition.l1 = "Timer";
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.hour  = 10.0;
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, iTemp);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, iTemp);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, iTemp);
				pchar.quest.GuardOT_tradetimer.function = "GuardOT_PrepareTrade";
			}
			else
			{
				dialog.text = "Magnifico! Mi piace trattare con soci di buon senso. Vado alla riva. Torna tra tre ore. Credo che a quel punto il nostro comune amico Gaius avrà ritrovato la ragione...";
				link.l1 = "Magnifico! Ci vediamo dopo!";
				link.l1.go = "gevarra_15";
				pchar.quest.GuardOT_tradetimer.win_condition.l1 = "Timer";
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.hour  = sti(GetTime()+3);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
				pchar.quest.GuardOT_tradetimer.function = "GuardOT_PrepareTrade";
			}
		break;
		
		case "gevarra_15":
			iTemp = sti(pchar.questTemp.Guardoftruth.VanilleQty)*210+25000;
			DialogExit();
			NextDiag.currentnode = "gevarra_time";
			npchar.DeckDialogNode = "gevarra_time";
			AddMoneyToCharacter(pchar, -iTemp); // деньги сразу списываем
			bQuestDisableMapEnter = true;
			pchar.GenQuest.MapClosedNoBattle = true;
			AddQuestRecord("Guardoftruth", "17");
			AddCharacterExpToSkill(pchar, "Sneak", 50);
		break;
		
		case "gevarra_time":
			dialog.text = "Señor, ricordo bene la mia parte. Non temete, magari sarà un osso duro, ma lo farò cantare io.";
			link.l1 = "Grazie.";
			link.l1.go = "exit";
			NextDiag.TempNode = "gevarra_time";
		break;
		
		case "gevarra_16":
			dialog.text = "È fatto, signor. Quel poveraccio era al settimo cielo che volessi comprare la sua vaniglia. Gli tremavano le mani dalla felicità mentre gli contavo l’anticipo – o forse era solo il rhum a fargli ballare le dita. Caricheremo la merce domani a mezzodì sulla spiaggia di Capster, così da non attirare gli occhi indiscreti dei gabellieri al porto. Salperò senza indugio verso Santiago appena la vaniglia sarà stivata. Contatterò il vostro compare al faro e gli consegnerò la robaccia, come d’accordo. Volete che gli lasci qualche parola da parte vostra?";
			link.l1 = "Sì. Ecco la lettera. Dici che lo scambio sarà domani a mezzogiorno a Capster Beach? Va bene, allora getto l’ancora appena al largo della punta, fuori mano dall’isola, nel caso succeda qualche malanno.";
			link.l1.go = "gevarra_17";
		break;
		
		case "gevarra_17":
			Log_Info("You handed the letter over");
			PlaySound("interface\important_item.wav");
			dialog.text = "Puoi fidarti di me, señor. Son uomo d’onore, parola di mercante. E poi, non ho alcuna voglia di litigare con voi, ché la reputazione è tutto per chi traffica nei mari. Ma se volete assistere e controllare di persona, per me non è certo un peso.";
			link.l1 = "Vi sono grato, señor. Domani terrò d’occhio l’accordo e, appena mollate gli ormeggi, mi sbrigherò a sbrigare i miei affari a San Cristoforo.";
			link.l1.go = "gevarra_18";
		break;
		
		case "gevarra_18":
			DialogExit();
			NextDiag.currentnode = "gevarra_exit";
			npchar.DeckDialogNode = "gevarra_exit";
			bQuestDisableMapEnter = true;
			pchar.GenQuest.MapClosedNoBattle = true;
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			AddQuestRecord("Guardoftruth", "18");
			pchar.quest.GuardOT_gotoshore.win_condition.l1 = "ExitFromSea";
			pchar.quest.GuardOT_gotoshore.function = "GuardOT_TradeComplete";
		break;
		
		case "gevarra_exit":
			dialog.text = "Capitano, vi do la mia parola: non vi deluderò e rispetterò ogni patto preso tra noi.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "gevarra_exit";
		break;
		
		// матросы Марше
		case "marshe_sailor":
			dialog.text = LinkRandPhrase("Hic! Evviva! Il vecchio capitano ci ha finalmente dato la paga! Tre urrà per il capitano! Hic!","In pinta?! Allora me ne prendo una anch’io!","Che le nostre borse siano gonfie e le nostre donne ancor di più! Evviva!","E là giacevano, tutti buoni uomini morti, hic! Come l’alba in una taverna di ubriaconi. Yo ho ho e una bottiglia di rum!","Yo ho ho e una bottiglia di rum!");
			link.l1 = LinkRandPhrase("Già, compare.","Non credi d’aver già tracannato abbastanza rum, eh?","Bevi e il diavolo ha fatto piazza pulita degli altri...");
			link.l1.go = "exit";
		break;
		
		case "galeonguard":
			PlaySound("Voice\English\EvilPirates01.wav");
			dialog.text = "Altolà! Chi va là? Allarme! Respingi gli abbordi!";
			link.l1 = "...";
			link.l1.go = "galeonguard_1";
		break;
		
		case "galeonguard_1":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.CantRun");
			CheckAndSetOverloadMode(GetMainCharacter());
			DeleteAttribute(pchar, "questTemp.Guardoftruth.Attack");
			LAi_RemoveCheckMinHP(pchar);
			GuardOT_GaleonGuardFightAdd();
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("GuardOT_galeonguard_"+i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, "GaleonFight");
			}
			LAi_group_FightGroups("GaleonFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// англичане в бухте
		case "dominica_hunter":
			dialog.text = "Argh argh! Sei qui pure tu a cercare il tesoro del Capitano Rollie, eh? Abbiam cercato e cercato e ancora cercato, ma niente da fare. Magari almeno uno di questi scalcagnati si decidesse a tuffarsi dietro la cascata fino alla sporgenza!";
			link.l1 = "Sei uno degli uomini del colonnello Fox, vero?";
			link.l1.go = "dominica_hunter_1";
		break;
		
		case "dominica_hunter_1":
			dialog.text = "Potrei avere qualche legame coi Gatti di Mare. Non t’impicciare, non serve a nulla saperlo. Non è il momento di ficcare il носe ovunque. Hai trovato il mio tesoro, per questo ti dobbiamo una gran bella riconoscenza...";
			link.l1 = "Capisco. Non sei una Volpe del Mare, piuttosto un cane... o una iena dei mari. Cosa ti calza meglio?";
			link.l1.go = "dominica_hunter_2";
		break;
		
		case "dominica_hunter_2":
			dialog.text = "Sembra che abbiamo tra le mani un vero filosofo della natura, ragazzi. Un autentico esperto del regno animale!";
			link.l1 = "Vuoi assaggiare il filo della mia sciabola, sciacallo?";
			link.l1.go = "dominica_hunter_3";
		break;
		
		case "dominica_hunter_3":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("GuardOT_DH_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_HuntersDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// Белинда Риберо
		case "belinda":
			dialog.text = TimeGreeting()+", señor. Come posso servirla?";
			link.l1 = "Salve. Siete Donna Belinda de Ribero?";
			link.l1.go = "belinda_1";
		break;
		
		case "belinda_1":
			dialog.text = "Sì, sono io. Con chi ho il piacere di parlare?";
			link.l1 = "Capitano "+GetFullName(pchar)+", madama. Non lasciatevi ingannare dal mio cognome francese, al momento sto svolgendo un incarico per il Reverendo Inquisitore di Santiago, Padre Vincento.";
			link.l1.go = "belinda_2";
		break;
		
		case "belinda_2":
			dialog.text = "Che curioso! Ho sentito dire che il Santo Tribunale e la Compagnia di Gesù pullulano d’una gran folla, di ogni ceto e nazione, ma mai prima d’ora avevo fatto la conoscenza diretta d’uno straniero al loro servizio. Cosa posso fare per voi, señor?";
			link.l1 = "Possiedi un oggetto che interessa molto al Reverendo Padre. Un ostensorio d’oro, una pisside che hai recentemente ottenuto dal banchiere di Willemstad.";
			link.l1.go = "belinda_3";
		break;
		
		case "belinda_3":
			dialog.text = "Sei davvero ben informato, señor. Beh, sapendo per chi lavori, non dovrei stupirmi. Sì, ho comprato l’ostensorio, di certo non era cosa da lasciar marcire in una bottega tra cianfrusaglie rubate e robaccia impegnata come fosse un ninnolo qualunque.";
			link.l1 = "Avete la pisside, madama?";
			link.l1.go = "belinda_4";
		break;
		
		case "belinda_4":
			dialog.text = "Sì. Avevo intenzione di donarlo alla nostra chiesa parrocchiale, ma qui m'è capitato tanto addosso... Non ci sono riuscito... Oh, perdonatemi...";
			link.l1 = "State forse piangendo, madama? Le mie parole vi hanno rattristata? Se così fosse, vi chiedo perdono.";
			link.l1.go = "belinda_5";
		break;
		
		case "belinda_5":
			dialog.text = "Oh, vi prego signor... Torniamo al nostro discorso. Se ho capito bene, padre Vincento ha bisogno di quest’ostensorio? Vorreste che ve lo consegnassi?";
			link.l1 = "Questo prezioso reliquiario era destinato alla cattedrale di Santiago, ma è stato catturato da un volgare pirata e svenduto a un usuraio insieme ad altri oggetti sacri. Il mio compito è restituire ciò che è stato rubato al suo giusto posto. Naturalmente, sarò pronto a rimborsare interamente le vostre spese.";
			link.l1.go = "belinda_6";
		break;
		
		case "belinda_6":
			dialog.text = "Oh, non dovete! Davvero pensate che questi soldi abbiano tanto valore per me? Ho acquistato quest’ostensorio per la Santa Madre Chiesa e non esiterò a restituirlo al suo vero padrone, tanto meno a un membro della Compagnia di Gesù al servizio di Padre Vincento. Ma c’è un’altra questione che mi affligge profondamente. Potreste aiutare una devota figlia della Chiesa nel suo bisogno?";
			link.l1 = "Siete una dama di nobile lignaggio, madama. Quali affanni vi tormentano? In che modo posso prestarvi aiuto?";
			link.l1.go = "belinda_7";
		break;
		
		case "belinda_7":
			dialog.text = "Oh, ma signore... Non oserei mai disturbare un fratello gesuita in persona per chiedere aiuto. Siete sempre così occupati...";
			link.l1 = "L’hai già fatto. Che c’è che non va?";
			link.l1.go = "belinda_8";
		break;
		
		case "belinda_8":
			dialog.text = "Puoi giurarmi, in quanto uomo della Santa Chiesa, che nessuno mai verrà a sapere ciò che sto per chiederti?";
			link.l1 = "Vi do la mia parola d’onore, señora. Non sarà il sigillo della confessione, ma non svelerò questa faccenda anima viva.";
			link.l1.go = "belinda_9";
		break;
		
		case "belinda_9":
			dialog.text = "Molto bene. Mi fido di te. Il mio carissimo amico Esteban Sosa si è cacciato nei guai. È stato catturato da mascalzoni lungo la strada e ora chiedono un riscatto di centomila pesos. Non dispongo di tanto oro, e sono riuscito a raccogliere solo metà della somma con la mia rendita. Non posso chiedere aiuto a nessuno, ché mi hanno giurato che lo ammazzerebbero al minimo sospetto.\nInoltre, temo per il mio... amico, e ho il cuore pesante. Potrebbero farlo fuori subito dopo aver intascato il denaro, per non rischiare che parli con le guardie. Forse tu, che sei capitano coraggioso, buon cristiano e fratello della Compagnia, potresti convincere i banditi ad accettare quello che ho raccolto e a lasciarlo vivo...";
			link.l1 = "Quando e dove avverrà lo scambio?";
			link.l1.go = "belinda_10";
		break;
		
		case "belinda_10":
			dialog.text = "Il loro capobanda è un certo Bartie lo Scuoiatore. Ha detto che aspetterà il riscatto di Esteban ogni notte, dall’undicesima campana fino a mezzanotte, all’ingresso della grotta nella giungla...";
			link.l1 = "Queste sono condizioni insolitamente precise...";
			link.l1.go = "belinda_11";
		break;
		
		case "belinda_11":
			dialog.text = "A quanto pare volevano che raccogliessi tutto il riscatto in fretta e senza chiedere aiuto a nessuno... ma una tale somma non la troverò mai, è impossibile!";
			link.l1 = "Non piangete, madama. Farò del mio meglio per aiutarvi. Un fratello della Compagnia di Gesù mai lascerebbe una pia cristiana in balìa del pericolo.";
			link.l1.go = "belinda_12";
		break;
		
		case "belinda_12":
			dialog.text = "Devo riporre la mia fiducia in te... Ma capitano, Bartie lo Scuoiatore ha anche detto che se il portatore del riscatto non verrà da solo, o se mi rivolgerò alle guardie, farà fuori il povero Estaban all’istante!";
			link.l1 = "Terrò a mente questa cosa.";
			link.l1.go = "belinda_13";
		break;
		
		case "belinda_13":
			dialog.text = "Ecco, prendi questo. Sono i cinquantamila pesos che sono riuscito a racimolare. Cerca di convincere quei briganti ad accettare almeno questa somma. Dì loro che non ho neanche un peso in più! Riporta indietro Esteban! Appena lo farai, ti darò volentieri l’ostensorio per padre Vincento.";
			link.l1 = "Farò tutto il possibile, madame. Speriamo che il vento ci sia favorevole.";
			link.l1.go = "belinda_14";
		break;
		
		case "belinda_14":
			dialog.text = "Che Dio ti assista, capitano valoroso! Pregherò per te!";
			link.l1 = "...";
			link.l1.go = "belinda_15";
		break;
		
		case "belinda_15":
			AddMoneyToCharacter(pchar, 50000);
			DialogExit();
			NextDiag.CurrentNode = "belinda_16";
			AddQuestRecord("Guardoftruth", "31");
			bQuestDisableMapEnter = true;//закрыть карту
			locations[FindLocation("Cumana_CaveEntrance")].DisableEncounters = true; //энкаутеры закрыть
			LAi_LocationDisableOfficersGen("Cumana_CaveEntrance", true);
			LAi_LocationDisableOfficersGen("Cumana_Cave", true);
			pchar.quest.GuardOT_gotocave.win_condition.l1 = "location";
			pchar.quest.GuardOT_gotocave.win_condition.l1.location = "Cumana_CaveEntrance";
			pchar.quest.GuardOT_gotocave.win_condition.l2 = "HardHour";
			pchar.quest.GuardOT_gotocave.win_condition.l2.hour = 23.00;
			pchar.quest.GuardOT_gotocave.function = "GuardOT_InCaveEntrance";
		break;
		
		case "belinda_16":
			dialog.text = "Hai qualche novità, capitano?";
			link.l1 = "Non ancora. Abbi pazienza, signora. Non ti deluderò.";
			link.l1.go = "exit";
			NextDiag.TempNode = "belinda_16";
		break;
		
		case "belinda_17":
			dialog.text = "Hai qualche novità, capitano?";
			link.l1 = "Sì, signora. Temo che non sia una buona notizia.";
			link.l1.go = "belinda_18";
		break;
		
		case "belinda_18":
			dialog.text = "Dimmi, non farmi aspettare! Hai incontrato quei mascalzoni?";
			if (sti(Pchar.money) >= 50000)
			{
				link.l1 = "Ecco, riprenditi i tuoi cinquantamila. Non mi sono serviti. Prendi anche quest’anello. Scommetto che ti parrà famigliare.";
				link.l1.go = "belinda_19_1";
			}
			link.l2 = "Ecco, prendi questo anello. Credo che ti sarà familiare.";
			link.l2.go = "belinda_19_2";
		break;
		
		case "belinda_19_1":
			RemoveItems(pchar, "jewelry29", 1);
			PlaySound("interface\important_item.wav");
			AddMoneyToCharacter(pchar, -50000);
			dialog.text = "Sì... mi suona familiare. Che ne è stato di Esteban?";
			link.l1 = "Ho trovato i briganti nella grotta, proprio come mi hai detto. 'Bartie il Macellaio' ed Esteban Sosa sono la stessa canaglia. Ha inscenato il rapimento solo per spillarti denaro. Mi ha parlato anche della vostra... relazione. Ha aggiunto pure che non vuole più vederti. Ho preso l’anello che gli avevi dato come prova.";
			link.l1.go = "belinda_20";
		break;
		
		case "belinda_19_2":
			dialog.text = "Questo... sì, sì, lo so. Che ne è stato di Esteban?";
			link.l1 = "Ho trovato i briganti nella grotta, proprio come mi avevi detto. Mi hanno assalito, legato e portato via i tuoi soldi. 'Bartie il Macellaio' ed Esteban Sosa sono la stessa persona. Ha inscenato il rapimento per spillarti denaro. Mi ha raccontato della vostra... relazione. Esteban mi ha lasciato andare e mi ha dato quest’anello come prova. Ha detto che non lo rivedrai mai più.";
			link.l1.go = "belinda_20";
			npchar.quest.nomoney = true;
		break;
		
		case "belinda_20":
			if (CheckAttribute(npchar, "quest.nomoney")) sTemp = "";
			else sTemp = "I taught him a lesson, but I didn't kill him out of respect to you.";
			dialog.text = "Dio mio! Non credo alle mie orecchie! Perché mi succede tutta questa dannata roba, perché?! Che diavolo ho fatto perché lui...";
			link.l1 = "Signora, vi supplico, non tormentatevi per questa faccenda. Quel mascalzone non vale nemmeno una vostra lacrima."+sTemp+"";
			link.l1.go = "belinda_21";
		break;
		
		case "belinda_21":
			if (CheckAttribute(npchar, "quest.nomoney")) sTemp = "";
			else sTemp = "And besides that, here's a gift to keep up your courage.";
			dialog.text = "Oh... Cercherò di calmarmi. Signore, devo ringraziarvi per l'aiuto. Ecco, prendete il vostro ostensorio. "+sTemp+" Va’ con Dio.";
			link.l1 = "Gracias, señora. Non tema, nessuno verrà mai a sapere quel che è accaduto nella grotta. Noi gesuiti manteniamo sempre la parola data. Ora, se permette, devo proprio andarmene.";
			link.l1.go = "belinda_22";
		break;
		
		case "belinda_22":
			DialogExit();
			AddQuestRecord("Guardoftruth", "33");
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 3;
			GiveItem2Character(pchar, "jewelry33");
			Log_Info("You've received a gold ostensory");
			PlaySound("interface\important_item.wav");
			if (CheckAttribute(npchar, "quest.nomoney"))
			{
				ChangeCharacterComplexReputation(pchar, "nobility", -3);
				OfficersReaction("bad");
			}
			else
			{
				Log_Info("You've received an amulet");
				GiveItem2Character(pchar, "amulet_7");
				ChangeCharacterComplexReputation(pchar, "nobility", 5);
				OfficersReaction("good");
				ChangeCharacterNationReputation(pchar, SPAIN, 3);
				AddCharacterExpToSkill(pchar, "Leadership", 300);
			}
		break;
		
		// бандит Эстебана
		case "bandos_mush":
			PlaySound("Voice\English\other\OZGi-04.wav");
			dialog.text = "Fermati subito, compare!";
			link.l1 = "Sono proprio qui, davanti a te.";
			link.l1.go = "bandos_mush_1";
		break;
		
		case "bandos_mush_1":
			dialog.text = "Hai portato il denaro?";
			link.l1 = "Che domanda sciocca. No, sono qui a raccogliere Manga Rosa... Perché mai altro dovrei esser venuto fin qua?";
			link.l1.go = "bandos_mush_2";
		break;
		
		case "bandos_mush_2":
			dialog.text = "Oh ho ho! Un buffone! Avanti, nella grotta con te, Bartie ti aspetta da tempo.";
			link.l1 = "Si vede che sei una guardia di lungo corso... con quell’aria potresti far la guardia persino a Re Filippo in persona. Mi presento da solo, grazie.";
			link.l1.go = "bandos_mush_3";
		break;
		
		case "bandos_mush_3":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("Cumana_CaveEntrance", "reload2_back", true);
			LAi_SetWarriorType(npchar);
			LAi_CharacterDisableDialog(npchar);
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			pchar.quest.GuardOT_incave.win_condition.l1 = "location";
			pchar.quest.GuardOT_incave.win_condition.l1.location = "Cumana_Cave";
			pchar.quest.GuardOT_incave.function = "GuardOT_InCumanaCave";
		break;
		
		// Эстебан-Барти
		case "barty":
			PlaySound("Voice\English\other\OZGi-03.wav");
			dialog.text = "Mi hai fatto aspettare... Hai portato i soldi con te?";
			link.l1 = "Sei tu Bartie lo Scorticato? Non hai proprio l’aria d’un ladruncolo da strapazzo.";
			link.l1.go = "barty_1";
		break;
		
		case "barty_1":
			dialog.text = "Perché ti interessa come sono fatto? Hai i dannati soldi o no?";
			link.l1 = "Dov'è l’ostaggio?";
			link.l1.go = "barty_2";
		break;
		
		case "barty_2":
			dialog.text = "Avrai il tuo ostaggio. Dai, passa la moneta. Non farmi incazzare, ragazzo.";
			link.l1 = "Bartie, ti sembro forse uno sprovveduto? Finché non vedrò Esteban Sosa vivo e vegeto coi miei occhi, non vedrai manco uno spicciolo. Dov'è finito?";
			link.l1.go = "barty_3";
		break;
		
		case "barty_3":
			dialog.text = "Oh, ti ostini, eh? Va bene, ti insegneremo una bella lezione... Ragazzi, spacchiamo il culo a questo mangiamerda!";
			link.l1 = "Maledetto bastardo!";
			link.l1.go = "barty_4";
		break;
		
		case "barty_4":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			GuardOT_InCumanaCaveEnemyAdd();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("GOT_bandos_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_CumanaCaveBandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");
			// офицеров насильно
			LAi_LocationDisableOfficersGen("Cumana_Cave", false); //офицеров пускать
			DoQuestFunctionDelay("GuardOT_SetOfficerCumanaCave", 3.0);
		break;
		
		case "barty_5":
			PlaySound("Voice\English\other\Plennie-02.wav");
			dialog.text = "";
			link.l1 = "Ti sei divertito abbastanza a ballare? Dov’è Esteban Sosa? Su, parla o ti tengo la testa sotto l’acqua finché non smetti di fare bolle!";
			link.l1.go = "barty_6";
		break;
		
		case "barty_6":
			dialog.text = "No... Non farmi del male, te ne prego! Sono Esteban Sosa.";
			link.l1 = "Come?";
			link.l1.go = "barty_7";
		break;
		
		case "barty_7":
			dialog.text = "Sì, sì. Non sono mica Bartie lo Scannatore. Io sono solo...";
			link.l1 = "Mascalzone! Hai davvero deciso di spillare centomila pesos alla Señora de Ribero fingendo il tuo stesso rapimento?!";
			link.l1.go = "barty_8";
		break;
		
		case "barty_8":
			dialog.text = "Devi capirmi, da uomo a uomo. Belinda... Non ne posso più di quell’amore appiccicoso che ha per me. Mi sta addosso a ogni ora, notte e giorno, amico! Perfino suo marito ha iniziato a insospettirsi, e quello ci vede a malapena!";
			link.l1 = "E allora guarda un po’! Siete amanti, voi due?";
			link.l1.go = "barty_9";
		break;
		
		case "barty_9":
			dialog.text = "Non più. Sono semplicemente scappato da lei.";
			link.l1 = "E hai pensato bene di arraffare qualche moneta per la strada, eh? E adesso che dovrei farci con te? Nasconderti il cadavere nella giungla, proprio come volevi fare con me?";
			link.l1.go = "barty_10";
		break;
		
		case "barty_10":
			dialog.text = "No! Non volevo spargere sangue, lo giuro!";
			link.l1 = "È per questo che mi hai sguinzagliato i tuoi mastini addosso?";
			link.l1.go = "barty_11";
		break;
		
		case "barty_11":
			dialog.text = "Volevamo solo svuotarti le tasche, tutto qui!";
			link.l1 = "E lasciarmi nudo nella selva? Dovrei impiccarti all’albero maestro più alto della mia nave, furfante! Ma non lo farò, solo per rispetto verso la povera donna che ha avuto la sventura d’intrecciare la sua sorte con la tua. Sai che ti dico? Dovrei portarti da lei e lasciare che sia lei a decidere che fare di te.";
			link.l1.go = "barty_12";
		break;
		
		case "barty_12":
			dialog.text = "No, qualsiasi cosa ma non questo! Non tornerò a Cumana!";
			link.l1 = "Preferiresti restare in questa caverna per l’eternità?";
			link.l1.go = "barty_13";
		break;
		
		case "barty_13":
			dialog.text = "Abbi pietà, signore! Lasciami andare e prometto che salperò lontano da qui, non metterò mai più piede a Cumana! Non resterò ad aspettare che il marito di Belinda mi faccia a fette in duello o mi mandi dietro un sicario!";
			link.l1 = "D’accordo. In nome della Señora de Ribero non ti porto da lei, ma non credere nemmeno per un attimo che questa tua porcheria passi inosservata. Verrà a sapere che razza di miserabile ha scelto per i suoi giochetti. Hai con te qualcosa che possa riconoscere?";
			link.l1.go = "barty_14";
		break;
		
		case "barty_14":
			dialog.text = "Ecco. Questo anello di turchese qui. Me l’ha dato lei stessa.";
			link.l1 = "Perfetto. Dammi qua e sparisci dalla mia vista!";
			link.l1.go = "barty_15";
			// belamour legendary edition -->
			link.l2 = "Perfetto. E sai che c’è, Sosa? Ho cambiato idea – ora servo la Compagnia di Gesù. Come dice la Scrittura, 'Devi scacciare il malvagio di mezzo a voi.' E tu sei un dannato narcisista, un criminale, e una nullità da gettare agli squali. Credo che ti annegherò in questa grotta. Requiescat in pace.";
			link.l2.go = "barty_15a";
		break;
		
		case "barty_15a":
			DialogExit();
			GiveItem2Character(pchar, "jewelry29");
			Log_Info("You received a turquoise ring");
			PlaySound("interface\important_item.wav");
			LAi_SetActorType(pchar);
			// если не надет пистоль или мушкет, то выдадим строевой -->
			if(!CheckAttribute(pchar,"equip."+GUN_ITEM_TYPE) || !CheckAttribute(pchar,"equip."+MUSKET_ITEM_TYPE))
			{
				GiveItem2Character(pchar, "pistol1");
				EquipCharacterbyItem(pchar, "pistol1");
			}
			LAi_ActorAnimation(pchar, "Shot", "RIP_Sosa", 1.0); 
		break;
			
		case "barty_15":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			// <-- legendary edition
			GiveItem2Character(pchar, "jewelry29");
			Log_Info("You received a turquoise ring");
			PlaySound("interface\important_item.wav");
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationDisableOfficersGen("Cumana_CaveEntrance", false);//офицеров пускать
			locations[FindLocation("Cumana_CaveEntrance")].DisableEncounters = false; //энкаутеры открыть
			locations[FindLocation("Cumana_Cave")].DisableEncounters = false; // patch
			LAi_LocationFightDisable(&Locations[FindLocation("Cumana_CaveEntrance")], false);//разрешить драться
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			LocatorReloadEnterDisable("Cumana_CaveEntrance", "reload2_back", false);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			sld = characterFromId("GOT_Belinda");
			sld.dialog.currentnode = "Belinda_17";
			AddQuestRecord("Guardoftruth", "32");
		break;
		
		// охотники
		case "spa_hunter":
			dialog.text = "Hai proprio quello che ci serve, compare...";
			link.l1 = "Davvero?   E di che si tratterebbe?";
			link.l1.go = "spa_hunter_1";
		break;
		
		case "spa_hunter_1":
			dialog.text = "Non t'ho chiesto niente, damerino. Ho solo ricevuto l’ordine di prendere tutto ciò che hai addosso, fino all’ultimo scudo. Vuoi farlo alla buona o preferisci che ti spacchi la zucca? Decidi tu.";
			link.l1 = "Pensi di essere un guerriero, eh? Non hai la minima idea con chi hai a che fare. Feccia come te la mastico a colazione.";
			link.l1.go = "spa_hunter_2";
		break;
		
		case "spa_hunter_2":
			dialog.text = "Sei proprio un buffone, vero, ranocchio? Vediamo un po’ come sta il tuo sangue sparso per terra!";
			link.l1 = "Sarà uguale alla tua, idiota. Lascia che ti insegni un po’ d’anatomia!";
			link.l1.go = "spa_hunter_3";
		break;
		
		case "spa_hunter_3":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for(i=1; i<=5; i++)
			{
				sld = characterFromID("GOT_santiagoband_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_SantiagoBandDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "cabin_hunter":
			dialog.text = "Ah ah, avanti furfantello... Svòta le tasche, e sbrigati! Se fai il bravo e non fiati, magari te ne vai via intero, ciurma?";
			link.l1 = "Maledizione, ancora voi? Siete venuti fin quaggiù anche voi? Chi diavolo vi ha ingaggiato?!";
			link.l1.go = "cabin_hunter_1";
		break;
		
		case "cabin_hunter_1":
			dialog.text = "Non sono affari tuoi. Ora arrenditi e vivi oppure fatti sotto e ci prenderemo il bottino dal tuo cadavere. Ti va questo accordo, eh?";
			link.l1 = "Ho una controproposta. Che ne dici se ti levo il bottino dal cadavere, bastardo?";
			link.l1.go = "cabin_hunter_2";
		break;
		
		case "cabin_hunter_2":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for(i=1; i<=2; i++)
			{
				sld = CharacterFromID("GOT_cabinband_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_CabinBandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// командир абордажников
		case "batabano_officer":
			dialog.text = "In attesa di ordini, capitano!";
			link.l1 = "Attraversate la giungla verso Capo San Antonio. Prendete il sentiero a sinistra e andate sempre dritto. State bassi e preparatevi all’agguato sulla riva. Restate all’erta. Io ci arriverò via mare e ci incontreremo lì. Quanto ci metterete ad arrivare?";
			link.l1.go = "batabano_officer_1";
		break;
		
		case "batabano_officer_1":
			dialog.text = "Saremo lì fra sei ore, capitano!";
			link.l1 = "Bene. Avanti, muoviti!";
			link.l1.go = "batabano_officer_2";
		break;
		
		case "batabano_officer_2":
			DialogExit();
			LocatorReloadEnterDisable("Shore13", "boat", false);
			for(i=1; i<=10; i++)
			{
				sld = characterFromID("GuardOT_Oursoldier_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "OpenTheDoors", 20.0);
			}
			AddQuestRecord("Guardoftruth", "48");
			// на мыс
			pchar.quest.GuardOT_sanantonio.win_condition.l1 = "Ship_location";
			pchar.quest.GuardOT_sanantonio.win_condition.l1.location = "Shore15";
			pchar.quest.GuardOT_sanantonio.function = "GuardOT_SanantonioArrive";
			// на время, специально для дебилов, не читающих диалоги и СЖ
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1 = "Timer";
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1.date.hour  = sti(GetTime()+6);
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.GuardOT_sanantoniotimer.function = "GuardOT_SanAntonio_Timer";
		break;
		
		// наёмник Патерсона
		case "housemercen":
			dialog.text = "Testardo maledetto! È ancora vivo... Sapevo che dovevamo usare più polvere da sparo! Va bene, allora, ti finirò io, figlio di puttana...";
			link.l1 = "...";
			link.l1.go = "housemercen_1";
		break;
		
		case "housemercen_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			bDisableCharacterMenu = false;//разлочим F2
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			if (MOD_SKILL_ENEMY_RATE < 5) LAi_group_SetCheck("EnemyFight", "GuardOT_HouseMercenDie");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

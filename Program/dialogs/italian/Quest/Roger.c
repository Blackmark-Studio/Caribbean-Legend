// диалоги персонажей по пиратской линейке // Addon 2016-1 Jason пиратская линейка
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp, attrL;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	attrL = Dialog.CurrentNode;
	
	if(HasSubStr(attrL, "ShipStockManBack_"))
 	{
        i = findsubstr(attrL, "_" , 0);
	 	NPChar.ShipToStoreIdx = strcut(attrL, i+1, strlen(attrL)-1); // индех в конце
 	    Dialog.CurrentNode = "ShipStockManBack";
 	}

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "First time":
			dialog.text = "Cosa vuoi?";
			link.l1 = "Dovrei andare...";
			link.l1.go = "exit";
		break;
		
		// Лопе Монторо
		case "Mtr_officer":
			if (pchar.questTemp.Mtraxx != "fail" && pchar.questTemp.Mtraxx == "jewelry_5")
			{
				pchar.quest.Mtraxx_JewelryHavanaOver.over = "yes"; //снять таймер
				dialog.text = "Per l'amor di Dio, chi diavolo sei tu?";
				link.l1 = "Buon giorno, don Lope. Anche se non ci siamo ancora conosciuti, ora sarebbe un ottimo momento. Soprattutto ora che sono così desideroso di aiutarti a uscire da questa situazione difficile...";
				link.l1.go = "Mtr_officer_1";
			}
			else
			{
				dialog.text = "Cosa vuoi?";
				link.l1 = "Dovrei andare...";
				link.l1.go = "exit";
			}
		break;
		
		case "Mtr_officer_1":
            dialog.text = "Aiuto? A me? Che svolta di eventi! Potrebbe illuminarmi, signore, da dove proviene una tale generosità?";
			link.l1 = "Certo. Sto cercando il tuo ex capitano, Esberdo Cabanas, e non ho molto tempo... preferibilmente, mi piacerebbe incontrarlo in quel posto che tiene segreto. Ancora meglio se arrivassi là prima di lui.";
			link.l1.go = "Mtr_officer_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Mtr_officer_2":
            dialog.text = "Ah-ah! Ho detto a questo patetico idiota di tenere la bocca chiusa! L'ambra blu, ho ragione?";
			link.l1 = "Stai pensando nella giusta direzione, mio buon signore.";
			link.l1.go = "Mtr_officer_3";
		break;
		
		case "Mtr_officer_3":
            dialog.text = "Allora facciamo presto. Mi piacerebbe raccontarti ogni singolo dettaglio se trovi un modo per tirarmi fuori da qui. Sai come sono finito in questo buco?";
			link.l1 = "Nel complesso, sì, lo faccio.";
			link.l1.go = "Mtr_officer_4";
		break;
		
		case "Mtr_officer_4":
            dialog.text = "Ero ubriaco fradicio quando è successo. Dannato quel maledetto barista! Non ricordo un bel niente. Mi hanno raccontato tutto solo quando mi sono svegliato nella stiva della 'Cantavro'. Sarebbe tutto alle nostre spalle se solo fossimo andati via, sia il comandante che l'alcalde erano disposti a fare finta di niente. Ma quel maledetto don Esberdo mi ha semplicemente messo in prigione. Pensi che l'abbia fatto 'per fare la cosa giusta'? Ma va', quel furfante voleva solo tenersi la mia parte di ambre\nEro io che avevo detto che ci potrebbero essere più ambre sott'acqua di quante ne abbiamo trovate sulla spiaggia. Ero io, che avevo trovato un modo per prenderle. Dovevo ricevere una grossa parte, ma... ah, quel figlio di cagna! Ugh, ma basta con questo. Né l'alcalde, né il comandante, né il don de Toledo sono contenti che io venga lasciato qui a marcire. Se non fosse stato per quel contadino e la sua moglie vacca, che hanno fatto sobbalzare i colombai... comunque, non si opporranno a te che mi aiuti\nParla con il governatore, fai finta di essere un mio vecchio amico dall'Europa - lo confermerò io stesso. Come ti chiami, a proposito?";
			link.l1 = ""+GetFullName(pchar)+".";
			link.l1.go = "Mtr_officer_5";
		break;
		
		case "Mtr_officer_5":
            dialog.text = ""+GetFullName(pchar)+", meraviglioso. Vai a trovare don Diego de Toledo e chiedigli un consiglio. Ricorda, hai solo tre giorni, inseguire il 'Cantavro' dopo sarebbe inutile. Liberami e ti darò tutto ciò di cui hai bisogno per affrontare quel bastardo, Cabanas.";
			link.l1 = "Andrò a vedere il governatore immediatamente, don Lope. Farò del mio meglio per risolvere questa situazione per il bene di entrambi.";
			link.l1.go = "Mtr_officer_6";
		break;
		
		case "Mtr_officer_6":
            DialogExit();
			pchar.questTemp.Mtraxx = "jewelry_6";
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("Roger_1", "8");
			SetFunctionTimerCondition("Mtraxx_TimeclearPrison", 0, 0, 4, false); // таймер
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			AddLandQuestMark(characterFromId("Havana_Mayor"), "questmarkmain");
		break;
		
		case "Mtr_officer_7":
			pchar.quest.Mtraxx_TimeclearPrison.over = "yes"; //снять таймер
            dialog.text = "Allora, l'usuraio e la sua gallina chioccia hanno avuto la loro vendetta, e finalmente ho finito con questo buco. Hai la mia gratitudine signore, hai fatto la tua parte. Ora permettimi di fare la mia.";
			link.l1 = "Sono tutto orecchie!";
			link.l1.go = "Mtr_officer_8";
			DelLandQuestMark(npchar);
		break;
		
		case "Mtr_officer_8":
            dialog.text = "Bene. Durante la nostra precedente pattuglia, siamo stati colpiti da una tempesta che ci ha fatto abbandonare il nostro corso. Siamo approdati sulla spiaggia della Costa Occidentale, non lontano dalla Costa dei Mosquitos, per cercare un po' d'acqua fresca. Lì abbiamo trovato un buon deposito di ambra blu. Ho fatto un po' di prospezione e ho trovato un mucchio sotto l'acqua. Avevamo bisogno di attrezzature migliori per raccoglierla, ecco perché abbiamo deciso di ritornarci più tardi\nEsberdo aveva comprato cinque barche lunghe a L'Avana per far immergere gli indigeni e raccogliere l'ambra. Conosci il resto della storia - quella feccia si è sbarazzata di me e se ne è andata. Trovalo alla Costa dei Mosquitos a nord del Blueweld, e fai in fretta - secondo i miei calcoli, hai solo circa sette giorni per arrivarci. Spero che tu prenda quel bastardo nel bel mezzo della raccolta, gli porti via tutta la sua ambra e gli conficchi un coltello nella pancia più volte. Ma stai attento, il mio ex capitano è un abile combattente e un marinaio. Buona fortuna, signore.";
			link.l1 = "Anche a te, Lope. Addio!";
			link.l1.go = "Mtr_officer_9";
		break;
		
		case "Mtr_officer_9":
            DialogExit();
			pchar.questTemp.Mtraxx = "jewelry_10";
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Roger_1", "12");
			SetFunctionTimerCondition("Mtraxx_TimeclearGulf", 0, 0, 7, false); // таймер
			pchar.quest.mtr_jewelry_gulf.win_condition.l1 = "location";
			pchar.quest.mtr_jewelry_gulf.win_condition.l1.location = "Santacatalina";
			pchar.quest.mtr_jewelry_gulf.function = "Mtraxx_JewelryGulf";
			DeleteAttribute(pchar, "GenQuest.PrisonQuestLock");
			DelMapQuestMarkCity("Havana");
			AddMapQuestMarkShore("Shore53", true);
		break;
		
		// Росарио Гусман
		case "Mtr_rosario":
            dialog.text = "Vuole chiedere qualcosa, signore?";
			link.l1 = "Riguardo a don Montoro. Siamo vecchi conoscenti e mi ha davvero turbato quando ho saputo delle sue sfortune. Don Diego de Toledo mi ha mandato da te, ha detto che hai già cercato di liberare il nostro amico comune...";
			link.l1.go = "Mtr_rosario_1";
		break;
		
		case "Mtr_rosario_1":
            dialog.text = "Ehm... signore, questo è un po'... inaspettato, ma sono lieto di incontrare un amico di Lope! È stato sfortunato per un bel po' di tempo già e ora questo...";
			link.l1 = "Cosa possiamo fare per lui? Non è modo per un nobile hidalgo di marcire tra la feccia della società!";
			link.l1.go = "Mtr_rosario_2";
		break;
		
		case "Mtr_rosario_2":
            dialog.text = "Un uomo d'affari! È sia facile che difficile aiutare il povero Lope. Ho avuto una conversazione con il profittatore con cui il povero Lope ha avuto la sfortuna di litigare. Ha accettato di incontrarci a metà strada per cinquecento dobloni. Una somma notevole per le sue 'sofferenze' e quelle di sua moglie. Ahimè, sono riuscito a raccogliere solo metà della somma richiesta - duecentocinquanta dobloni.";
			link.l1 = "Allora, se ti porto altri duecentocinquanta dobloni, don Lope sarà liberato?";
			link.l1.go = "Mtr_rosario_3";
		break;
		
		case "Mtr_rosario_3":
            dialog.text = "Sì. Quel bastardo avido mi ha promesso di diffondere la voce che Lope lo ha risarcito di tutti i danni. Chiederà anche al governatore di perdonarlo.";
			if (PCharDublonsTotal() >= 250) // belamour legendary edition
			{
				link.l1 = "Ho la somma richiesta con me proprio ora. Ecco, lascia che questo avido borghese si soffochi con essa.";
				link.l1.go = "Mtr_rosario_4";
			}
			link.l2 = "Farò del mio meglio per ottenere denaro il più presto possibile.";
			link.l2.go = "Mtr_rosario_5";
		break;
		
		case "Mtr_rosario_4":
			RemoveDublonsFromPCharTotal(250); // belamour legendary edition
			PlaySound("interface\important_item.wav");
            dialog.text = "Non posso credere ai miei propri orecchi! Signore, devi essere stato inviato dal Signore!";
			link.l1 = "Quando lasceranno libero il nostro uomo?";
			link.l1.go = "Mtr_rosario_8";
			DelLandQuestMark(npchar);
		break;
		
		case "Mtr_rosario_5":
            dialog.text = "Contento di sentirlo, signore. Sei un vero amico di Lope e un vero nobile.";
			link.l1 = "Arrivederci!";
			link.l1.go = "Mtr_rosario_6";
		break;
		
		case "Mtr_rosario_6":
            DialogExit();
			AddQuestRecord("Roger_1", "10");
			npchar.dialog.currentnode = "Mtr_rosario_7";
		break;
		
		case "Mtr_rosario_7":
            dialog.text = "Hai portato i soldi?";
			if (PCharDublonsTotal() >= 250) // belamour legendary edition
			{
				link.l1 = "Ho con me la somma richiesta proprio ora. Ecco, lascia che questo avido borghese si strozzi con essa.";
				link.l1.go = "Mtr_rosario_4";
			}
			link.l2 = "Sono ancora su di esso.";
			link.l2.go = "Mtr_rosario_7_1";
		break;
		
		case "Mtr_rosario_7_1":
            DialogExit();
			npchar.dialog.currentnode = "Mtr_rosario_7";
		break;
		
		case "Mtr_rosario_8":
            dialog.text = "Porterò i soldi al furfante stasera. Credo che avranno un ordine di rilascio del nostro amico entro mezzogiorno. E spero che ci riuniremo per festeggiare più tardi?";
			link.l1 = "Certo, don Rosario. Dovrei andare ora. Ci vediamo!";
			link.l1.go = "Mtr_rosario_9";
		break;
		
		case "Mtr_rosario_9":
            DialogExit();
			AddQuestRecord("Roger_1", "11");
			npchar.lifeday = 1;
			SaveCurrentNpcQuestDateParam(NPChar, "LifeTimeCreate");
			npchar.dialog.currentnode = "Mtr_rosario_10";
			pchar.quest.mtr_prisoner.win_condition.l1 = "Timer";
			pchar.quest.mtr_prisoner.win_condition.l1.date.hour  = 12;
			pchar.quest.mtr_prisoner.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtr_prisoner.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtr_prisoner.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtr_prisoner.function = "Mtraxx_PrisonerFree";
		break;
		
		case "Mtr_rosario_10":
            dialog.text = "Presto il nostro amico sarà libero!";
			link.l1 = "...";
			link.l1.go = "exit";
			npchar.dialog.currentnode = "Mtr_rosario_10";
		break;
		
		// Лысый Джеффри
		case "Jeffry":
			pchar.quest.Mtraxx_SilkCPVOver.over = "yes"; //снять прерывание
            dialog.text = "Ehi, cosa diavolo stai facendo sulla mia nave? Non credo di averti inviato un invito, eh?";
			link.l1 = "Calmati, Geffrey. Sono della Tyrex riguardo al business della seta navale.";
			link.l1.go = "Jeffry_1";
		break;
		
		case "Jeffry_1":
            dialog.text = "A-ah, beh, allora parliamo. Cosa sta progettando? Ho già parlato con i contrabbandieri, secondo me offrono un bel prezzo per la merce...";
			link.l1 = "E quanto, se posso chiedere?";
			link.l1.go = "Jeffry_2";
		break;
		
		case "Jeffry_2":
            dialog.text = "1300 pesos per un rotolo. Credo sia un buon prezzo.";
			link.l1 = "Sì, e Tyrex vuole venti pezzi d'oro per un rotolo. Non una moneta di meno. E intendo dobloni. Mi ha dato un lavoro per trovare un compratore adeguato per quel prezzo.";
			link.l1.go = "Jeffry_3";
		break;
		
		case "Jeffry_3":
            dialog.text = "Ah-ah-ah, ragazzo, non sei fortunato! Marcus ha davvero un appetito! Beh, vai a trovare un tale compratore, sarebbe glorioso vederti provare.";
			link.l1 = "Sì, tutto questo è molto dannatamente divertente ed esilarante. Sembro felice? Non lo sono. Quindi ti suggerisco di smettere di ridere e di aiutarmi.";
			link.l1.go = "Jeffry_4";
		break;
		
		case "Jeffry_4":
            dialog.text = "Bene, bene, amico... Gesù, non sei molto amante delle battute, eh? Ma capisco, non sei da biasimare per le fantasie di Tyrex, tutti avremo la nostra parte di questa, fidati di me. E come posso aiutarti? Non puoi venderlo nei negozi, nemmeno le dogane sono un'opzione, rimangono solo i contrabbandieri. Chi altro ne ha bisogno? Hai qualche idea?";
			link.l1 = "Ci penso da quando eravamo a Hispaniola... Comunque. Ho solo due mesi per trovare un compratore regolare. Devo fare qualcosa a riguardo. I tuoi ordini sono di approdare nella baia più vicina e fare delle riparazioni.";
			link.l1.go = "Jeffry_5";
		break;
		
		case "Jeffry_5":
            dialog.text = "Due mesi?! Che diavolo? Ah, al diavolo. Il 'Serpente' ha bisogno di riparazioni e pulizia o non sarà in grado di inseguire nemmeno una barca. Ehi, puttane francesi! L'equipaggio del Calvo Geffrey si ferma a Capsterville per due mesi! Ah-ah-ah!... Beh, buona fortuna a te, amico, in quelle tue inutili ricerche. Se trovi un idiota disposto a pagare il prezzo di Marcus per questa maledetta seta - sai dove trovarmi.";
			link.l1 = "Aspetta! Dammi un rotolo di questa seta. Devo mostrare la merce ai potenziali acquirenti.";
			link.l1.go = "Jeffry_6";
		break;
		
		case "Jeffry_6":
            dialog.text = "Certo, nessun problema. Puoi portarlo con te su una barca lunga... Ehi ragazzi! Gettate un balla di seta sulla barca del capitano!";
			link.l1 = "Bene. Beh, ci vedremo quando troverò l'acquirente!";
			link.l1.go = "Jeffry_7";
		break;
		
		case "Jeffry_7":
            DialogExit();
			AddQuestRecord("Roger_2", "3");
			npchar.DeckDialogNode = "Jeffry_8";
			npchar.dialog.currentnode = "Jeffry_8";
			pchar.questTemp.Mtraxx = "silk_2";
			AddCharacterGoods(pchar, GOOD_SHIPSILK, 1);
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("Mtraxx_SilkTimeOver", 0, 0, 61, false); // таймер
		break;
		
		case "Jeffry_8":
            dialog.text = "Qualcos'altro, amico?";
			link.l1 = "Nulla al momento...";
			link.l1.go = "Jeffry_8_1";
		break;
		
		case "Jeffry_8_1":
            DialogExit();
			npchar.DeckDialogNode = "Jeffry_8";
			npchar.dialog.currentnode = "Jeffry_8";
		break;
		
		case "Jeffry_9":
			pchar.quest.Mtraxx_SilkTimeOver.over = "yes";
            dialog.text = "Come stai, amico?";
			link.l1 = "Sto andando alla grande. Ho trovato un compratore. Venticinque dobloni per rotolo. Credo che a Tyrex piacerà.";
			link.l1.go = "Jeffry_10";
		break;
		
		case "Jeffry_10":
            dialog.text = "Ma non è possibile! Sei il figlio diavolosamente ingegnoso del diavolo! Come hai fatto, eh?";
			link.l1 = "È una lunga storia, Geffrey. Ora ascolta. Dovresti arrivare a Capo Negril in Giamaica tra il 10 e il 15. Ti aspetteranno lì di notte. La parola d'ordine è 'Un mercante di Lione'. Capito? Ripeti.";
			link.l1.go = "Jeffry_11";
		break;
		
		case "Jeffry_11":
            dialog.text = "Un mercante di Lione. Capito. Dovrei dire al mio cassiere di scriverlo, è l'unico uomo qui che sappia scrivere. Ah-ah!";
			link.l1 = "Hai cento rotoli nella stiva?";
			link.l1.go = "Jeffry_12";
		break;
		
		case "Jeffry_12":
            dialog.text = "Ne ho ancora di più.";
			link.l1 = "Splendido. È ora per te di mettere le vele allora. Non deludermi!";
			link.l1.go = "Jeffry_13";
		break;
		
		case "Jeffry_13":
            dialog.text = "Rilassati, amico, tutto sarà fatto come si deve.";
			link.l1 = "Buon vento, Geffrey. Forse, ci incontreremo di nuovo.";
			link.l1.go = "Jeffry_14";
		break;
		
		case "Jeffry_14":
            DialogExit();
            AddQuestRecord("Roger_2", "22");
			pchar.questTemp.Mtraxx = "silk_14"; // к Тираксу
			sld = characterFromId("Terrax");
			sld.dialog.currentnode = "mtraxx_12";
			pchar.quest.mtraxx_hide_jeffry.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_hide_jeffry.function = "Mtraxx_SilkHideJeffry";
		break;
		
		case "Jeffry_15":
            dialog.text = "Ah-ah-ah! L'astuto Charlie Principe, in carne ed ossa! Bello vederti di nuovo, amico!";
			link.l1 = "Geffrey Calvo! Hai detto Charlie Prince? Ah!";
			link.l1.go = "Jeffry_15x";
		break;
		
		case "Jeffry_15x":
            dialog.text = "Mai sentito il tuo secondo nome prima? Così ti chiamano ora a La Vega.";
			link.l1 = "Capisco da dove viene Charlie, ma perché Principe?";
			link.l1.go = "Jeffry_15y";
		break;
		
		case "Jeffry_15y":
            dialog.text = "Ebbene, sei l'unico figlio di puttana nobile a La Vega! Ha-ha-ha! Come stai? Sei stato al negozio di Pasquale? Hai comprato rifornimenti dal vecchio bastardo?";
			link.l1 = "Mai più!";
			link.l1.go = "Jeffry_16";
		break;
		
		case "Jeffry_16":
            dialog.text = "K-ha! Perché, non ti piaceva? Ti ha venduto la carne salata al prezzo del rum?";
			link.l1 = "Peggio! Ho avuto da lui un'indicazione su un convoglio olandese carico di ebano. Non è stato facile trovarlo, salire a bordo del mercante e poi proteggere quel maledetto legno da alcune decine di ratti! E indovina un po', il bastardo mi ha pagato 150 pesos per pezzo. Per un pezzo di maledetto ebano, Geffrey!";
			link.l1.go = "Jeffry_17";
		break;
		
		case "Jeffry_17":
            dialog.text = "Succede sempre, amico, ti assicuro. Lavoisier ha già fregato una dozzina di bravi ragazzi come te. Ti ha addirittura pagato qualcosa, il che è raro per lui. Non prendiamo i suoi 'indizi' nemmeno se stiamo morendo di fame.";
			link.l1 = "Grazie amico mio, almeno ora so che non sono stato il primo e l'unico idiota! Ma questa volta quel bastardo si è rovinato da solo. Mi assicurerò che si penta del giorno in cui mi ha visto.";
			link.l1.go = "Jeffry_18";
		break;
		
		case "Jeffry_18":
            dialog.text = "Ehi-ehi-ehi! Aspetta Principe, calmati un po'. Il mercante qui è intoccabile. Osa saccheggiarlo - Marcus sarà lì per il tuo culo. Dimmi, è stato Tyrex a mandarti da Lavoisier?";
			link.l1 = "Mm. Sì... Perché?";
			link.l1.go = "Jeffry_19";
		break;
		
		case "Jeffry_19":
            dialog.text = "Ascolta... (abbassando la voce) Dicono che il quattro occhi condivide con Marcus. Mi capisci ora? Questo è il motivo per cui nessun pirata oserebbe mai attaccare le navi di Lavoisier, altrimenti sarebbero finiti.";
			link.l1 = "Preso nota. Grazie per l'avvertimento Geffrey. Addio e che Dio ti accompagni!";
			link.l1.go = "Jeffry_20";
		break;
		
		case "Jeffry_20":
            dialog.text = "Anche a te, amico.";
			link.l1 = "...";
			link.l1.go = "Jeffry_21";
		break;
		
		case "Jeffry_21":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 15.0);
			AddQuestRecord("Roger_4", "10");
			CloseQuestHeader("Roger_4");
			QuestSetCurrentNode("Terrax", "mtraxx_34"); // релиз-правка
			bDisableFastReload = false;
			pchar.questTemp.Mtraxx.CharleePrince = "true"; // атрибут - ГГ известный пират
			pchar.questTemp.CharleePrince = true; // атрибут для найма команды 
		break;
		
		case "Jeffry_22":
            dialog.text = "Ah-ah-ah Principe! Mi chiedevo chi avesse creato i fuochi d'artificio! Ho portato una squadra di moschettieri nel caso fossero gli spagnoli.";
			link.l1 = "Geffrey? Sei anche tu qui? Ma come? Hai comprato anche tu la mappa del tesoro?";
			link.l1.go = "Jeffry_23";
			QuestPointerDelLoc("Judgement_dungeon_05", "reload", "reload1");
			QuestPointerDelLoc("Judgement_dungeon_04", "reload", "reload1");
		break;
		
		case "Jeffry_23":
            dialog.text = "Amico, non sprecare i miei soldi per cose del genere. Mi hanno consegnato il diario di qualche viaggiatore che scriveva di un passaggio sicuro per queste segrete.";
			link.l1 = "Chi te l'ha portato?";
			link.l1.go = "Jeffry_24";
		break;
		
		case "Jeffry_24":
            dialog.text = "Un drogato. Aveva bisogno solo di cento pesos per un drink.";
			link.l1 = "È successo a Tortuga?";
			link.l1.go = "Jeffry_25";
		break;
		
		case "Jeffry_25":
            dialog.text = "Macché. Era Barbados? Principe, perché ti preoccupi tanto? Più siamo, più velocemente porteremo via i tesori!";
			link.l1 = "Non mi piace questo. Non credo in coincidenze come questa. Potrebbe essere il padre di Camilla che ha scritto questo diario?";
			link.l1.go = "Jeffry_26";
		break;
		
		case "Jeffry_26":
            dialog.text = "Chi è Camilla?";
			link.l1 = "La sgualdrina che mi ha venduto una mappa di questo posto per duecento pesos!";
			link.l1.go = "Jeffry_27";
		break;
		
		case "Jeffry_27":
            dialog.text = "Eh... Principe, pensi troppo. Andiamo a caccia di tesori. Dai!";
			link.l1 = "Non c'è bisogno. Li ho già trovati... Sono laggiù nel dungeon, dietro le sbarre di ferro. Dovremo romperli. Ascolta Geffrey, c'è un'altra cosa! Anche Pelly il Coltello era qui!";
			link.l1.go = "Jeffry_28";
		break;
		
		case "Jeffry_28":
            dialog.text = "Coltello? Beh, allora è il nostro giorno fortunato! Ma dov'è ora?";
			link.l1 = "Sotto... morto. L'ho incontrato vicino al tesoro. È impazzito, ha iniziato a urlare di avidità. Poi lui e i suoi compagni mi hanno attaccato.";
			link.l1.go = "Jeffry_29";
		break;
		
		case "Jeffry_29":
            dialog.text = "Hm... Pelly ha sempre avuto sfortuna con i soldi. Deve essere impazzito vedendo quel mucchio d'oro.";
			link.l1 = "Potrebbe essere così... ma Geffrey, non capisci! Siamo arrivati qui tutti e tre! E abbiamo tutti la stessa pista! Pensi che sia stato per caso? Qualcuno chiaramente vuole tutti noi in un unico posto, e questo posto sembra proprio una tomba.";
			link.l1.go = "Jeffry_30";
		break;
		
		case "Jeffry_30":
            dialog.text = "Hai visto l'oro però?";
			link.l1 = "L'ho visto con i miei stessi occhi. Diverse gigantesche casse piene di monete e lingotti.";
			link.l1.go = "Jeffry_31";
		break;
		
		case "Jeffry_31":
            dialog.text = "Allora perché ti preoccupi Principe? Guida la strada, diamo un'occhiata a queste tue sbarre. Poi condivideremo l'oro.";
			link.l1 = "Eh, potresti avere ragione, chissà... Andiamo.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionWithJeffry");
		break;
		
		case "Jeffry_32":
            PlaySound("Voice\English\LE\Jeffry\Jeffry_gold.wav");
			dialog.text = "Che spettacolo! È un mucchio di oro! Ora capisco perché Cutlass è impazzito. Siamo molto fortunati Principe! Secondo te, quanto oro troveremo qui?";
			link.l1 = "Molto. Lo sapremo di sicuro quando ci occuperemo di queste sbarre.";
			link.l1.go = "Jeffry_33";
		break;
		
		case "Jeffry_33":
            dialog.text = "Sì, la grata è molto robusta, non la romperemo né a mani nude né con le spade. Hai ragione, compagno - dobbiamo trovare degli attrezzi o un sacco di polvere da sparo. Ehi guarda! Cos'è quello!?";
			link.l1 = "...";
			link.l1.go = "Jeffry_34";
		break;
		
		case "Jeffry_34":
            DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Mtraxx_RetributionJeffryMushketer", 0.1);
		break;
		
		case "Jeffry_35":
            PlaySound("Voice\English\LE\Jeffry\Jeffry_mozila.wav");
			dialog.text = RandSwear()+"Che cazzo di fighetta!";
			link.l1 = "Sei un cazzo di serpente!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionJeffryFight");
		break;
		
		// Билли Сипатый
		case "Billy":
			pchar.quest.Mtraxx_BillySeaTimeOver.over = "yes"; //снять таймер
			PlaySound("VOICE\English\LE\Billy\Billy_01.wav");
            dialog.text = "Squalo mi inghiotta se è successo sulla 'Fly Fish' quest'anno... ragazzi abbiamo un ospite qui! Cos'è andato così male nella tua vita, amico, che hai deciso di far visita alla mia vecchia tinozza?";
			link.l1 = "Saluti! Tu sei quello a cui chiamano Husky Billy, non è vero?";
			link.l1.go = "Billy_1";
		break;
		
		case "Billy_1":
            dialog.text = "Non riesci a capire dalla mia voce, capitano? Tanto tempo fa faceva cagare addosso ai mercanti britannici e spagnoli. Che tempi gloriosi erano quelli!... Ora il vecchio Billy aspetta la fine della sua vita vicino alle coste della sua isola preferita sulla sua preziosa barca lunga...";
			link.l1 = "Ho un affare per te, Billy. Mi è stato detto che sai tutto su ciò che sta succedendo qui intorno alla Giamaica. È così?";
			link.l1.go = "Billy_2";
		break;
		
		case "Billy_2":
            dialog.text = "Se te l'hanno detto, allora deve essere così, non pensi? Non tirare il granchio per le palle, parla. Che affari hai per me?";
			link.l1 = "Molto bene. C'è un costruttore di navi a Port Royal. Offre ai suoi clienti servizi speciali, e ha bisogno di seta per navi per la sua produzione e i suddetti servizi. Poiché il commercio di questa merce è illegale qui, ha trovato un venditore illegale. Voglio sapere chi e come, lo sta rifornendo di seta per navi.";
			link.l1.go = "Billy_3";
		break;
		
		case "Billy_3":
            dialog.text = "Oho-ho, guarda qui! Lavorando per il colonnello D'Oyley, figliolo?";
			link.l1 = "Eccoci di nuovo! No, lavoro con Marcus Tyrex. Vuole una parte nel mercato della seta navale e questo costruttore di navi ha una paura sacra di trattare con persone 'sconosciute'...";
			link.l1.go = "Billy_4";
		break;
		
		case "Billy_4":
            dialog.text = "Oh, stai lavorando per il Custode del Codice! Queste sono ottime notizie... se non stai mentendo, ovviamente. Non me ne frega niente dei costruttori di navi, ne arresti uno - ne arriva un altro. Ma mi importa della mia vecchia ragazza. La 'Pesce Volante' è in cattive condizioni. Mi capisci?\nPortami un'altra barca lunga, una nuova, e un rotolo di seta per navi, lo stesso tipo di cui stai parlando - Billy ne farà una vela decente con cui potrà fregare le pattuglie, ah-ah-ah! In cambio Billy ti dirà tutto sul costruttore di navi e la sua fonte di seta. Fidati di me figliolo so tutto quello che vuoi sapere, devo solo assicurarmi che tu sia un pirata onesto e non qualche leccapiedi in divisa rossa!";
			link.l1 = "Una nuova barca lunga? Che ne dici se ti do abbastanza soldi per comprarla da solo? Aggiungerò anche un extra.";
			link.l1.go = "Billy_5";
		break;
		
		case "Billy_5":
            dialog.text = "Eh-eh, capitano, il vecchio Billy non è ben accetto in città. Mi ricordano troppo bene a Port Royal e non mi piace l'idea di essere impiccato tra i miei vecchi amici su quella roccia. Quindi, figliolo, aspetto che tu mi porti una nuova barca lunga. Ti aspetterò per tre giorni a Capo Negril. E non dimenticare la seta!";
			link.l1 = "Molto bene, Billy. Avrai la tua lunga barca e un rotolo di seta navale. Tornerò presto.";
			link.l1.go = "Billy_6";
		break;
		
		case "Billy_6":
            dialog.text = "Molto bene, Billy ti aspetterà sulla riva, capitano. A presto!";
			link.l1 = "...";
			link.l1.go = "Billy_7";
		break;
		
		case "Billy_7":
            DialogExit();
			AddQuestRecord("Roger_2", "8");
			npchar.dialog.currentnode = "Billy_8";
			pchar.questTemp.Mtraxx = "silk_7";
			SetFunctionTimerCondition("Mtraxx_BillyTimeOver", 0, 0, 3, false); // таймер
			pchar.quest.mtr_billy_coast.win_condition.l1 = "ExitFromLocation";
			pchar.quest.mtr_billy_coast.win_condition.l1.location = pchar.location;
			pchar.quest.mtr_billy_coast.function = "Mtraxx_BillyOnCoast";
			locations[FindLocation("shore35")].DisableEncounters = true; //энкаутеры закрыть
			npchar.DontDeskTalk = true;
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
		break;
		
		case "Billy_8":
			PlaySound("VOICE\English\LE\Billy\Billy_02.wav");
            dialog.text = "Cosa? Hai già portato una lunga barca per me?";
			link.l1 = "Sei un ragazzo buffone, eh, Billy?";
			link.l1.go = "exit";
		break;
		
		case "Billy_9":
            dialog.text = "Allora, capitano, che ne pensi della mia nuova lunga barca?";
			if(Companion_CheckShipType(SHIP_TARTANE) && GetSquadronGoods(pchar, GOOD_SHIPSILK) > 0)
			{
				link.l1 = "È fatto, Husky. Lei è stata consegnata insieme a un rotolo di seta navale nella sua stiva. Sei libero di affondare la tua vecchia tinozza.";
				link.l1.go = "Billy_11";
			}
			else
			{
				PlaySound("VOICE\English\LE\Billy\Billy_02.wav");
				link.l1 = "Sono ancora su di esso. Aspetta.";
				link.l1.go = "Billy_10";
			}
		break;
		
		case "Billy_10":
			DialogExit();
			npchar.dialog.currentnode = "Billy_9";
		break;
		
		case "Billy_11":
			PlaySound("VOICE\English\LE\Billy\Billy_03.wav");
			pchar.quest.Mtraxx_BillyTimeOver.over = "yes"; //снять прерывание
            dialog.text = "Cazzo, mi ha preso alla sprovvista! Questa è la notizia migliore degli ultimi cinque anni della vita del vecchio Billy! Eh, un buon motivo per stappare questa bottiglia...";
			link.l1 = "Passo. Allora, riguardo al fornitore di seta?";
			link.l1.go = "Billy_12";
		break;
		
		case "Billy_12":
            dialog.text = "Peccato, potremmo bere alla mia nuova 'Pesca Volante'! Comunque... Ascolta qui, figliolo\nUna brigantina sotto la bandiera inglese arriva a Portland Cove a metà di ogni mese, tra il 10 e il 15. Non bevo rum fino a che non sono morto se è davvero inglese! Il suo nome è 'Utrecht' e arriva dal sud-ovest, dove si trova Curacao. È chiaramente una nave olandese, capitano, si può vedere\nSempre lo stesso gruppo di persone li incontra sulla riva, guidati dal capomastro di quel furbastro costruttore di navi. È un ricevitore di seta navale che gli olandesi scaricano lì. Sono sicuro che è la seta navale, dato che solo gli olandesi la impacchettano in quel modo.";
			link.l1 = "Ogni mese hai detto?";
			link.l1.go = "Billy_13";
		break;
		
		case "Billy_13":
            dialog.text = "Certo ragazzo mio, non hanno saltato un solo mese nell'ultimo anno. Se vuoi fare quattro chiacchiere con questa cupa compagnia barbuta ti suggerisco di aspettarli a Portland Cove dal 10 al 15 di ogni mese di notte. Lo giuro sulle nuove vele di seta fresca della mia lunga barca!";
			link.l1 = "Eh! Sembra che i miei soldi siano stati spesi per una buona ragione. Buon viaggio, Billy, assicurati di tenere il tuo vecchio culo al sicuro dalle pattuglie, altrimenti mi farai davvero arrabbiare.";
			link.l1.go = "Billy_14";
		break;
		
		case "Billy_14":
            dialog.text = "Eh, il vecchio Billy sta per creare un bel divertimento intorno alle coste della Giamaica! Buon vento, capitano! Buona caccia!";
			link.l1 = "Lo stesso a te, Billy!";
			link.l1.go = "Billy_15";
		break;
		
		case "Billy_15":
            DialogExit();
			npchar.lifeday = 0;
			pchar.questTemp.Mtraxx = "silk_8";
			chrDisableReloadToLocation = true;//закрыть локацию
			locations[FindLocation("shore35")].DisableEncounters = false; //энкаутеры открыть
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "OpenTheDoors", 20.0);
			AddDialogExitQuestFunction("Mtraxx_BillyTakeShip");
			AddQuestRecord("Roger_2", "9");
			//
			if (GetDataDay() >= 1 && GetDataDay() <= 9)
			{
				DoQuestFunctionDelay("Mtraxx_SilkCreateSmuggler", 1.0);
			}
			
			if (GetDataDay() >= 10 && GetDataDay() <= 15)
			{
				int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+2;
				if (iRank > 45) iRank = 45;
				Group_FindOrCreateGroup("Mtr_Utreht");
				sld = GetCharacter(NPC_GenerateCharacter("Cap_Utreht", "mercen_19", "man", "man", iRank, ENGLAND, -1, true, "quest"));
				FantomMakeCoolSailor(sld, SHIP_BRIGANTINE, "Utrecht", CANNON_TYPE_CULVERINE_LBS18, 50, 50, 50);
				FantomMakeCoolFighter(sld, iRank, 50, 50, "blade_13", "pistol5", "bullet", 100);
				sld.name = "Joachim";
				sld.lastname = "Gusen";
				sld.DontRansackCaptain = true;
				sld.AnalizeShips = true;
				sld.Coastal_Captain = true; // правки прогона 3
				DeleteAttribute(sld, "SaveItemsForDead");
				sld.Ship.Mode = "pirate";
				SetSailsColor(sld, 2);
				sld.ship.Crew.Morale = 40+MOD_SKILL_ENEMY_RATE*4;
				sld.Ship.Crew.Exp.Sailors = 60+MOD_SKILL_ENEMY_RATE*4;
				sld.Ship.Crew.Exp.Cannoners = 40+MOD_SKILL_ENEMY_RATE*4;
				sld.Ship.Crew.Exp.Soldiers = 40+MOD_SKILL_ENEMY_RATE*4;
				if (MOD_SKILL_ENEMY_RATE > 4) SetCharacterPerk(sld, "MusketsShoot");
				SetCharacterGoods(sld, GOOD_SHIPSILK, 80);

				Group_AddCharacter("Mtr_Utreht", "Cap_Utreht");
				Group_SetGroupCommander("Mtr_Utreht", "Cap_Utreht");
				Group_SetTaskAttackInMap("Mtr_Utreht", PLAYER_GROUP);
				Group_SetAddress("Mtr_Utreht", "Jamaica", "Quest_Ships", "Quest_Ship_4");
				Group_SetTaskRunaway("Mtr_Utreht", PLAYER_GROUP);
				Group_LockTask("Mtr_Utreht");
				
				pchar.quest.mtr_silksmuggler_AfterBattle.win_condition.l1 = "Group_Death";
				pchar.quest.mtr_silksmuggler_AfterBattle.win_condition.l1.group = "Mtr_Utreht";
				pchar.quest.mtr_silksmuggler_AfterBattle.function = "Mtraxx_SilkSmugglerAfterBattle";
				
				SetTimerFunction("Mtraxx_SilkSmugglerFail", 0, 0, 2);
			}
			
			if (GetDataDay() >= 16 && GetDataDay() <= 20)
			{
				SetTimerFunction("Mtraxx_SilkCreateSmuggler", 0, 0, 15);
			}
			if (GetDataDay() >= 21 && GetDataDay() <= 26)
			{
				SetTimerFunction("Mtraxx_SilkCreateSmuggler", 0, 0, 10);
			}
			if (GetDataDay() >= 27 && GetDataDay() <= 31)
			{
				SetTimerFunction("Mtraxx_SilkCreateSmuggler", 0, 0, 5);
			}
		break;
		
		// мастеровой с верфи Порт-Ройаля
		case "Mtr_acceptor_fight":
            LAi_group_Delete("EnemyFight");
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation("shore36")], false);
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("Mtr_acceptor_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Mtraxx_SilkWrongTalk");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Mtr_acceptor":
            dialog.text = "Ehi, marinaio, sei appena arrivato in Giamaica, eh?";
			link.l1 = "Hm. Corretto. Qual è il problema?";
			link.l1.go = "Mtr_acceptor_1";
		break;
		
		case "Mtr_acceptor_1":
            dialog.text = "Hai visto succedere qualcosa in mare da queste parti?";
			link.l1 = "Sì, l'ho fatto. Una brigantina è entrata in combattimento con una corvetta della pattuglia inglese. Gli inglesi li hanno colpiti duramente, gli olandesi hanno liberato il loro carico nel tentativo di fuggire.";
			link.l1.go = "Mtr_acceptor_2";
		break;
		
		case "Mtr_acceptor_2":
            dialog.text = "Perché sei così sicuro che fosse olandese? Nessun olandese in sano giudizio penserebbe nemmeno di avvicinarsi così tanto a Port Royal...";
			link.l1 = "Aveva colori inglesi ma il nome ... L''Utrecht'. Non molto britannico, eh? Erano olandesi ti dico, forse anche contrabbandieri. La pattuglia sicuramente se li aspettava.";
			link.l1.go = "Mtr_acceptor_3";
		break;
		
		case "Mtr_acceptor_3":
            dialog.text = "Cazzo!";
			link.l1 = "Sembra che non sei esattamente felice di questo...";
			link.l1.go = "Mtr_acceptor_4_1";
			link.l2 = "Stavi aspettando questa brigantina qui?";
			link.l2.go = "Mtr_acceptor_7";
		break;
		
		case "Mtr_acceptor_4_1":
            dialog.text = "Perché dovrei esserlo?";
			link.l1 = "Avanti. So chi sei. Sei il caposquadra del cantiere navale di Port Royal e stai aspettando che una brigantina consegni un carico molto speciale.";
			link.l1.go = "Mtr_acceptor_wrong";
			link.l2 = "Lo hai scritto sul tuo viso, proprio lì!";
			link.l2.go = "Mtr_acceptor_4_2";
		break;
		
		case "Mtr_acceptor_wrong":
            dialog.text = "Argh! Ragazzi, questa è una pattuglia travestita! Sbarazzatevene e cavatevi di qui all'inferno!";
			link.l1 = "Merda! Aspetta, stai sc...";
			link.l1.go = "Mtr_acceptor_fight";
		break;
		
		case "Mtr_acceptor_4_2":
            dialog.text = "Sei maleducato, 'lupo di mare'? Guarda la tua bocca o...";
			link.l1 = "Su, sembri ovviamente contrariato. Stavi davvero aspettando l'arrivo di questi olandesi?";
			link.l1.go = "Mtr_acceptor_4_3";
			link.l2 = "O cosa? Mi insegnerai una lezione di vita?";
			link.l2.go = "Mtr_acceptor_6";
		break;
		
		case "Mtr_acceptor_4_3":
            dialog.text = "E se lo fossi? Perché ti importa?";
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l1 = "Non lo faccio, davvero. Sei tu quello che aspetta qui, non io. Hai un'eternità davanti.";
				link.l1.go = "Mtr_acceptor_4_4";
			}
			link.l2 = "Oh, ho ogni motivo per preoccuparmi. So cosa c'era nella stiva della brigantina. Seta da nave. Sei qui per questo, vero?";
			link.l2.go = "Mtr_acceptor_wrong";
		break;
		
		case "Mtr_acceptor_4_4":
            dialog.text = "Mh... Eternità?";
			link.l1 = "Richiede un'eternità per tornare dal fondo del mare. La tua brigantina è stata affondata da una corvetta di pattuglia, amico. Proprio così. Anche se, la guerra porta sia premi che perdite. Farò un bel guadagno su quel olandese affondato.";
			link.l1.go = "Mtr_acceptor_4_5";
		break;
		
		case "Mtr_acceptor_4_5":
            dialog.text = "E come esattamente, mi chiedo?";
			link.l1 = "Venderò ciò che hanno gettato fuori bordo mentre cercavano di fuggire. Quasi tutto è perduto ma la preziosa seta navale galleggiava come... un tappo. Ne ho recuperato la maggior parte, quindi domani mi dirigerò verso la città per trovare un acquirente. Non si sa mai dove si guadagnerà e dove si perderà.";
			link.l1.go = "Mtr_acceptor_4_6";
		break;
		
		case "Mtr_acceptor_4_6":
            dialog.text = "Aspetta!";
			link.l1 = "Caramba! E ora che cosa?";
			link.l1.go = "Mtr_acceptor_4_7";
		break;
		
		case "Mtr_acceptor_4_7":
            dialog.text = "Quanta seta sei riuscito a raccogliere?";
			link.l1 = "E perché ti importa? Questa è la mia seta! O sei il cane del governatore? Tu sei de...";
			link.l1.go = "Mtr_acceptor_4_8";
		break;
		
		case "Mtr_acceptor_4_8":
            dialog.text = "Mantieni la tua spada nel fodero, marinaio. Non sono un cane e non sono uno spione. Lavoriamo nel cantiere navale locale... Questa seta era per noi e per quanto ho capito, ora l'hai tu. Ti comprerò tutto, abbiamo bisogno di questa seta, amico.";
			link.l1 = "Davvero? Interessante... Quanto?";
			link.l1.go = "Mtr_acceptor_4_9";
		break;
		
		case "Mtr_acceptor_4_9":
			i = GetSquadronGoods(pchar, GOOD_SHIPSILK);
            dialog.text = "Duemila e mezzo per un rotolo. È un buon prezzo, non troverai di meglio.";
			link.l1 = "Sembra che io sia fortunato! Ho "+FindRussianQtyString(i)+". Mostrami i soldi e ordinerò di consegnarli a terra subito.";
			if (i > 80) link.l1.go = "Mtr_acceptor_4_11";
			else link.l1.go = "Mtr_acceptor_4_10";
		break;
		
		case "Mtr_acceptor_4_10":
            dialog.text = "Affare fatto!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CargoSilk");
			AddCharacterExpToSkill(pchar, "Fortune", 300);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
		break;
		
		case "Mtr_acceptor_4_11":
            dialog.text = "Hm... Joachim doveva consegnare solo ottanta rotoli - impossibile che tu ne abbia salvati così tanti... il che significa che stai cercando di giocare sporco qui o... sei una spia! Ragazzi, uccidetelo e cavatevi di qui!";
			link.l1 = "Cazzo!";
			link.l1.go = "Mtr_acceptor_fight";
		break;
		
		case "Mtr_acceptor_5":
            dialog.text = "";
			link.l1 = "Un affare splendido, amico! Perché così cupo? Preoccupato per gli olandesi sul fondo del mare? Cose che succedono, non preoccuparti!";
			link.l1.go = "Mtr_acceptor_5_1";
		break;
		
		case "Mtr_acceptor_5_1":
            dialog.text = "Sì, certo... Erano il nostro fornitore abituale. Da dove dovremmo prendere la seta ora? Siamo sempre a corto di essa e l'intero commercio è sotto il controllo diretto del colonnello D'Oyley. Bah, dannazione...";
			link.l1 = "Mh... Ascolta, amico, suppongo che posso aiutarti con questo.";
			link.l1.go = "Mtr_acceptor_5_2";
		break;
		
		case "Mtr_acceptor_5_2":
            dialog.text = "Davvero? E come pensi di aiutarci? Ci consegnerai un lotto di cento rotoli ogni mese?";
			link.l1 = "Io? Hmm, probabilmente no, ma Marcus Tyrex sì. Hai sentito parlare di lui?";
			link.l1.go = "Mtr_acceptor_5_3";
		break;
		
		case "Mtr_acceptor_5_3":
            dialog.text = "K-ha! Quindi, sei un pirata?";
			link.l1 = "No, faccio affari con loro solo in occasioni speciali. So per certo che Marcus riceve periodicamente lotti di seta navale e la vende a chiunque possa permettersela. E non sto parlando di 2500 pesos per un rotolo qui, direi che se puoi pagargli 25 dobloni d'oro per ogni rotolo, ti sommergerà di questi, puoi contarci.";
			link.l1.go = "Mtr_acceptor_5_4";
		break;
		
		case "Mtr_acceptor_5_4":
            dialog.text = "Queste sono notizie interessanti... Dici Marcus Tyrex? Solo in dobloni?..";
			link.l1 = "Allora amico, importa davvero a te da chi ottieni la tua seta? E i soldi sono soldi, puoi sempre scambiare i pesos per i dobloni in una banca. Allora, dovrei sussurrare una parola o due su di te nelle orecchie del custode del codice? Sto andando a La Vega comunque.";
			link.l1.go = "Mtr_acceptor_5_5";
		break;
		
		case "Mtr_acceptor_5_5":
            dialog.text = "Molto bene. Facciamo un accordo. Questi sono i nostri termini: un lotto di cento rotoli ogni mese tra il 10 e il 15. Staremo qui ad aspettare... aspetta, cambiamo il punto di incontro, questo posto è compromesso ora. Staremo aspettando a Capo Negril, vicino alla città di Maroon, dovrebbe essere più sicuro là. La password - 'Un mercante di Lione'.";
			link.l1 = "Affare fatto, amico. Che diavolo di viaggio è stato! Tyrex mi pagherà un doblone o due per un acquirente del genere! Ha-ha! Bene, dovrei andare. Aspetta la nave di Tyrex il mese prossimo. Buona fortuna a te e alla tua famiglia!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CargoSilkWin");
		break;
		
		case "Mtr_acceptor_6":
            dialog.text = "Non avrai bisogno di altre lezioni di vita dopo che ti avremo insegnato a essere educato.";
			link.l1 = "Facendo il duro, falegname? Bene, continua ad aspettare quella tua brigantina, anche se ci vorrà un po'.";
			link.l1.go = "Mtr_acceptor_6_1";
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l2 = "Ehi, insegnante, ho anche qualche lezione per te!";
				link.l2.go = "Mtr_acceptor_6_2";
			}
		break;
		
		case "Mtr_acceptor_6_1":
            dialog.text = "Carpentiere? Dannazione, come lo sai? K-ha! Cazzo, ragazzi, questa è una pattuglia sotto mentite spoglie! Uccidetelo e cavatevi il diavolo da qui!";
			link.l1 = "Merda!";
			link.l1.go = "Mtr_acceptor_fight";
		break;
		
		case "Mtr_acceptor_6_2":
            dialog.text = "Lasciaci in pace, squama di pesce, non abbiamo tempo. Sparisci!";
			link.l1 = "Sei occupato ad aspettare una certa nave olandese? Buona fortuna con quello. Hai un'eternità davanti.";
			link.l1.go = "Mtr_acceptor_4_4";
		break;
		
		case "Mtr_acceptor_7":
            dialog.text = "Di che diavolo stai parlando?";
			link.l1 = "Capisco. Ma, nel caso tu lo sia, dimenticalo. Non arriverà grazie a una corvetta di pattuglia. Ho visto attraverso un cannocchiale la fine di una lotta. È successo così velocemente e non lontano da qui";
			link.l1.go = "Mtr_acceptor_7_1";
		break;
		
		case "Mtr_acceptor_7_1":
            dialog.text = "Di nuovo, non stiamo aspettando nulla o nessuno e...";
			link.l1 = "Guarda, a me non importa davvero un cazzo. Non appartengo alla pattuglia della città e non mi importa delle tue faccende, non sono un angelo neanche io. Se stai contrabbandando - è affar tuo. Tutto quello che volevo fare era avvertirti. Buona fortuna, amico.";
			link.l1.go = "Mtr_acceptor_7_2";
		break;
		
		case "Mtr_acceptor_7_2":
            dialog.text = "Aspetta... Sei sicuro che l''Utrecht' sia affondato?";
			link.l1 = "Certo. Ha cercato di fuggire, ha gettato via tutto quello che aveva nelle sue stive, non hanno nemmeno risparmiato la preziosa seta da nave, ma tali misure drastiche non potevano aiutare contro il vantaggio di velocità di una corvetta.";
			link.l1.go = "Mtr_acceptor_7_3";
		break;
		
		case "Mtr_acceptor_7_3":
            dialog.text = "Che peccato... e cosa dovremmo fare senza la seta? Accidenti!";
			link.l1 = "Hai bisogno di seta per la nave?";
			link.l1.go = "Mtr_acceptor_7_4";
		break;
		
		case "Mtr_acceptor_7_4":
            dialog.text = "Perché lo chiedi, lo stai vendendo?";
			link.l1 = "Non lo sono, ma conosco un uomo che lo è. Sta cercando un acquirente generoso e regolare. Pensi di poter farcela?";
			link.l1.go = "Mtr_acceptor_7_5";
		break;
		
		case "Mtr_acceptor_7_5":
            dialog.text = "E chi è quell'uomo?";
			link.l1 = "Marcus Tyrex, il barone di La Vega, meglio conosciuto come il Custode del Codice. Riceve lotti di seta da nave su base costante, quindi ha sempre qualcosa da vendere. Suppongo che considererà di venderlo anche a te se il tuo prezzo è abbastanza alto.";
			link.l1.go = "Mtr_acceptor_7_6";
		break;
		
		case "Mtr_acceptor_7_6":
            dialog.text = "Allora sei un pirata?";
			link.l1 = "Perché ti importa? Posso organizzare un accordo tra te e Tyrex se hai le palle per farlo. Se non le hai - allora addio.";
			link.l1.go = "Mtr_acceptor_7_7";
		break;
		
		case "Mtr_acceptor_7_7":
            dialog.text = "Bene-bene, non arrabbiarti. Certo, lo faccio. Voglio fare un accordo con Tyrex. Ma cosa ci guadagni tu?";
			link.l1 = "Se offrite un buon prezzo per il carico, probabilmente otterrò da Marcus una somma decente per il mio aiuto. Quindi, cosa sarà?";
			link.l1.go = "Mtr_acceptor_7_8";
		break;
		
		case "Mtr_acceptor_7_8":
            dialog.text = "Venticinque dobloni per un rotolo. Questo è il miglior prezzo che puoi ottenere, fidati di me su questo.";
			link.l1 = "Venticinque monete d'oro? Hm. Non male. Credo che Tyrex mi sarà molto debitore per un compratore del genere. Trattato molto bene, lo farò sapere a lui. Tuttavia, se mi hai mentito sul prezzo, allora sarai tu a rispondere.";
			link.l1.go = "Mtr_acceptor_7_9";
		break;
		
		case "Mtr_acceptor_7_9":
            dialog.text = "Non preoccuparti, siamo gente onesta. Queste sono le nostre condizioni: un lotto di cento rotoli ogni mese tra il 10 e il 15. Ti aspetteremo qui... aspetta, cambiamo il punto di incontro, questo posto è compromesso ora. Ti aspetteremo a Capo Negril, vicino alla città di Maroon, dovrebbe essere più sicuro lì. La password - 'Un mercante di Lione'.";
			link.l1 = "Capito. Aspetta il primo lotto il mese prossimo.";
			link.l1.go = "Mtr_acceptor_7_10";
		break;
		
		case "Mtr_acceptor_7_10":
            dialog.text = "Fai sapere a Tyrex che può portare più carico questa volta, siamo rimasti senza seta per questo mese.";
			link.l1 = "Lo farò. Buon vento, amico.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CargoSilkWin");
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
		break;
		
		// Тесак Пелли
		case "Pelly":
            dialog.text = "Ahoy! Cosa ti ha portato a bordo della mia nave, amico?";
			link.l1 = "Ehi, Sciabola. Marcus Tyrex mi ha mandato. Ci aspetta una marcia verso Maracaibo.";
			link.l1.go = "Pelly_1";
		break;
		
		case "Pelly_1":
            dialog.text = "A-ah, finalmente. Quindi devi essere il mio nuovo capo per questo viaggio. Bene. Come si chiama il mio nuovo ammiraglio?";
			link.l1 = "Capitano "+GetFullName(pchar)+".";
			link.l1.go = "Pelly_2";
		break;
		
		case "Pelly_2":
            dialog.text = "Ordini, Ammiraglio "+GetFullName(pchar)+"?";
			link.l1 = "Navigheremo separati fino al Lago di Maracaibo. Dovresti arrivarci di notte e sbarcare segretamente nella Baia di Guajira. Aspettami lì e nel frattempo allestisci un piccolo campo. Per quanto mi riguarda, sbarcherò nel porto spagnolo.";
			link.l1.go = "Pelly_3";
		break;
		
		case "Pelly_3":
            dialog.text = "Sissignore, Ammiraglio!";
			link.l1 = "Quanto tempo ci metterai per arrivare lì?";
			link.l1.go = "Pelly_4";
		break;
		
		case "Pelly_4":
            dialog.text = "Hmmm... Dovrebbe essere circa una settimana. Un giorno in meno, un giorno in più, tutto dipende dal vento.";
			link.l1 = "Bene. Non perdiamo tempo allora. Ci vediamo a Guajira Bay, amico.";
			link.l1.go = "Pelly_5";
		break;
		
		case "Pelly_5":
            dialog.text = "Si si, ammiraglio!";
			link.l1 = "...";
			link.l1.go = "Pelly_6";
		break;
		
		case "Pelly_6":
            DialogExit();
			AddQuestRecord("Roger_3", "3");
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true;
			Mtraxx_PlantContinue();
		break;
		
		case "Pelly_7":
            dialog.text = "Ordini, ammiraglio?";
			link.l1 = "Niente al momento. Sono occupato con la nostra operazione.";
			link.l1.go = "Pelly_wait";
			if (pchar.questTemp.Mtraxx == "plant_3")
			{
				link.l1 = "Prepara un baule capiente sulla riva. Ci raccoglieremo armi per i nostri fratelli imprigionati.";
				link.l1.go = "Pelly_7_1";
			}
			if (pchar.questTemp.Mtraxx == "plant_6" && CheckAttribute(pchar, "questTemp.mtraxx_PlantInfoTovar"))
			{
				dialog.text = "Allora, qual è il problema con il Bello? Le mie mani prudono per versare un po' di sangue Don!";
				link.l1 = "È più complicato di quanto pensavamo. Ha detto che le guardie della piantagione sono troppo allerta. L'unico modo per infiltrare armi è nasconderle nelle merci. Dovremmo urgentemente procurarci una spedizione di caffè, copra o vaniglia - il coltivatore locale tratta solo in questi e nient'altro.";
				link.l1.go = "Pelly_70";
				DelLandQuestMark(npchar);
			}
			if (pchar.questTemp.Mtraxx == "plant_8" && pchar.location.from_sea == "Shore37")
			{
				link.l1 = "Lascia il campo e raduna una squadra tempestiva. È ora di marciare, attacchiamo sotto il manto dell'oscurità.";
				link.l1.go = "Pelly_11";
				DelLandQuestMark(npchar);
			}
		break;
		
		case "Pelly_wait":
             DialogExit();
			 npchar.dialog.currentnode = "Pelly_7";
		break;
		
		case "Pelly_7_1":
            dialog.text = "Ascolta, ammiraglio, ho riflettuto...";
			link.l1 = "Cosa succede, Terrax ti paga per pensare invece di sfoderare quella tua sciabola, eh, Cutlass?";
			link.l1.go = "Pelly_35";
		break;
		
		case "Pelly_8":
            dialog.text = "Ehi! Una rivolta nella piantagione, vero, ammiraglio? Fiamme! Dovremmo trarre un po' d'oro da tutto questo!..";
			link.l1 = "Ho bisogno di un baule sulla riva, Sciabola.";
			link.l1.go = "Pelly_9";
		break;
		
		case "Pelly_9":
            dialog.text = "Subito, ammiraglio!";
			link.l1 = "...";
			link.l1.go = "Pelly_10";
		break;
		
		case "Pelly_10":
            DialogExit();
			npchar.dialog.currentnode = "Pelly_7";
			pchar.questTemp.Mtraxx = "plant_4";
			pchar.questTemp.Mtraxx.Chest = "true";
			// подгружаем сундук в локу и меняем локаторы
			int n = Findlocation("Shore37");
			Locations[n].models.always.locators = "shore03_q_locators";
			locations[n].models.always.chest = "chest_quest";
			Locations[n].models.always.chest.locator.group = "box";
			Locations[n].models.always.chest.locator.name = "private1";
			Locations[n].models.always.chest.tech = "DLightModel";
			DoQuestReloadToLocation("Shore37", "goto", "goto5", "Mtraxx_PlantChestReady");
		break;
		
		case "Pelly_11":
            dialog.text = "Subito, Ammiraglio!..";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantPrepareMarch");
		break;
		
		case "Pelly_12":
            dialog.text = "Gli uomini sono pronti e preparati, Ammiraglio!";
			link.l1 = "Avanti!";
			link.l1.go = "Pelly_13";
		break;
		
		case "Pelly_13":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			chrDisableReloadToLocation = false;
		break;
		
		case "Pelly_14":
            dialog.text = "Ammiraglio, sembra che l'amico di Tyrex che dovevamo salvare sia... in qualche modo morto.";
			link.l1 = "Sì, ma non si poteva fare nulla lì. Hai visto le guardie, siamo stati fortunati a rimanere vivi.";
			link.l1.go = "Pelly_15";
		break;
		
		case "Pelly_15":
            dialog.text = "Ammiraglio, Marcus sarà furioso con te. Non andare da lui ora. Io me ne sto andando. Dovresti fare lo stesso.";
			link.l1 = "Sì...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantFailFinal");
		break;
		
		case "Pelly_16":
            dialog.text = "Cattive notizie Ammiraglio. C'è una squadra spagnola che ci viene addosso da est. Non abbiamo tempo per fuggire.";
			link.l1 = "Quanti sono?";
			link.l1.go = "Pelly_17";
		break;
		
		case "Pelly_17":
            dialog.text = "Tre navi. Un sacco di cannoni. Siamo fottuti."; // лесникПОСЛЕДНЕЕ
			link.l1 = "Vedremo.";// Жан, ты отправляйся на борт к Тесаку. Тесак, поднимешь испанский флаг и на всех парусах прочь отсюда - глядишь, за торговца сойдёшь. А я пойду прямо на испанцев - отвлеку их от вас. Увидимся в Ла Веге у Тиракса.";
			link.l1.go = "Pelly_181";
		break;
		case "Pelly_181":
	    	DialogExit();
		   sld = characterFromId("Mrt_Rocur");
		   sld.Dialog.currentnode = "Pelly_182";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		case "Pelly_182":
		   dialog.text = ""; 
		   link.l1 = "Jean vai alla nave di Cutlass.";
		   link.l1.go = "Pelly_183"; 
		break;
		case "Pelly_183":
		     DialogExit();
			sld = characterFromId("Pelly");
			sld.Dialog.currentnode = "Pelly_18";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		case "Pelly_18":
            dialog.text = "";//"Но...";
			link.l1 = "Cutlass, dovresti issare la bandiera spagnola e cavartela da qui. Io li distrarrò da te. Ci vediamo tutti a La Vega.";//"Отставить! Тесак, за Жана Пикара отвечаешь головой перед Тираксом. Все на борт!";
			link.l1.go = "Pelly_19";
		break;
		
		case "Pelly_19":
            dialog.text = "Ma...";
			link.l1 = "Niente ma! Cutlass è il tuo culo sulla linea se Picard non arriva al posto di Tyrex. Tutti a bordo!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantSeaEscape");
		break;
		
		case "Pelly_20":
            dialog.text = "Ordini Ammiraglio?";
			link.l1 = "Preparatevi a combattere. Attaccate su mio comando!";
			link.l1.go = "Pelly_21";
		break;
		
		case "Pelly_21":
            dialog.text = "Si, si Ammiraglio... su tuo comando!";
			link.l1 = "...";
			link.l1.go = "Pelly_22";
		break;
		
		case "Pelly_22":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;
		break;
		
		case "Pelly_23":
            dialog.text = "Oho! Ciao Principe. Cosa ti ha portato a Tortuga?";
			link.l1 = "Di nuovo un compito di Marcus. Ascolta Cutlass, perché il bastardo che vive in questa casa non mi lascia entrare?";
			link.l1.go = "Pelly_24";
		break;
		
		case "Pelly_24":
            dialog.text = "Gaspard Denti d'Oro? Lui lavora solo con compagni di fiducia. Gli altri avrebbero bisogno di una raccomandazione per lavorare con lui. Vuoi vendere qualche gingillo lucente? Potrei farti da garante se vuoi...";
			link.l1 = "Allora è un usuraio? Qual è il suo interesse?";
			link.l1.go = "Pelly_25";
		break;
		
		case "Pelly_25":
            dialog.text = "Fratello, ti manca qualcosa. Gaspard non è un usuraio, dovresti andare da "+GetFullName(characterFromId("Usuraio_di_Tortuga"))+"se ne hai bisogno. Goldenteeth compra pietre preziose e gioielli di ogni tipo. A proposito, paga bene e non fa mai domande stupide. Ogni capitano pirata è suo cliente.";
			link.l1 = "Capisco... Mi è stato detto che alcuni di loro affidano addirittura i loro soldi a lui...";
			link.l1.go = "Pelly_26";
		break;
		
		case "Pelly_26":
            dialog.text = "Ha-ha! È stato un bugiardo a dirtelo, vai e sputa nei suoi occhi senza vergogna. Gaspard lavora solo con gioielli, l'ha sempre fatto. Perché avrebbe bisogno di problemi con i soldi degli altri?";
			link.l1 = "Capisco. Grazie Cutlass, ci vediamo in mare!";
			link.l1.go = "Pelly_27";
			link.l2 = "Mmm, davvero. Quindi, acquista cianfrusaglie? Interessante... Dici che puoi parlare bene di me?";
			link.l2.go = "Pelly_27z";
		break;
		
		case "Pelly_27":
            dialog.text = "Ci vediamo, Principe.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekReadLogbookThird");
		break;
		
		case "Pelly_27z":
            dialog.text = "Certo! Ora sei uno di noi, hehe! Aspetta qui un momento.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekPellyTalkGems");
		break;
		
		case "Pelly_28z":
            dialog.text = "Tutto è sistemato! Ora Goldentooth sa che Charlie Prince potrebbe venire da lui per vendere cianfrusaglie. Ricorda solo che il suo prezzo, sebbene buono, è comunque inferiore a quello che pagano quegli avari usurai. Ma lui compra tutto a tonnellate! E senza domande inutili, come ho già detto.";
			link.l1 = "Ecco il mio bel ragazzo! Ben fatto Paolo! Ora ho un posto dove scaricare tutto il bottino!";
			link.l1.go = "Pelly_29z";
		break;
		
		case "Pelly_29z":
            dialog.text = "No, Jean Picard è il 'Bello', io sono il 'Scimitarra', haha! Addio, Principe!";
			link.l1 = "Grazie, Sciabola, buona fortuna in mare!";
			link.l1.go = "Pelly_27";
		break;
		
		case "Pelly_28":
			PlaySound("VOICE\English\LE\Pelly\Pelly_03.wav");
            dialog.text = "Ho preso tre uccellini per te, Principe. Li ho trovati nascosti negli armadi e sotto un letto. Belle cose, eh? Ah-ah-ah!";
			link.l1 = "Dico che lo sono davvero. E sono anche ben curati. Don Testardo deve tenerci molto a loro.";
			link.l1.go = "Pelly_29";
		break;
		
		case "Pelly_29":
            DialogExit();
			sld = CharacterFromID("Mtr_CartahenaMayorClone");
			sld.dialog.currentnode = "CartahenaMayor_8";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Pelly_30":
			PlaySound("VOICE\English\LE\Pelly\Pelly_04.wav");
            dialog.text = "Alle hagel! Cosa diavolo stai facendo qui Principe?";
			link.l1 = "Scimitarra?.. Stavo seguendo le voci e il rumore, ma mai avrei pensato che saresti tu. Come diavolo sei finito qui?";
			link.l1.go = "Pelly_31";
			QuestPointerDelLoc("Judgement_dungeon_01", "reload", "reload2_back");
			QuestPointerDelLoc("Judgement_dungeon_02", "reload", "reload2");
			QuestPointerDelLoc("Judgement_dungeon_03", "reload", "reload2");
			QuestPointerDelLoc("Judgement_dungeon_04", "reload", "reload2");
			QuestPointerDelLoc("Judgement_dungeon_05", "quest", "pelly");
		break;
		
		case "Pelly_31":
            dialog.text = "No, perché sei qui! Sei sempre nei paraggi! Tyrex deve averti mandato per questo tesoro, vero? Caramba, sono in ritardo, di nuovo...";
			link.l1 = "Tyrex? No... Ho comprato una mappa da una sgualdrina. Probabilmente ne ha venduto una copia anche a te, eh? A Tortuga? Che furba troia. Non ha mentito però - guarda questa montagna d'oro! Tornerò con più persone per portare via tutto questo...";
			link.l1.go = "Pelly_32";
		break;
		
		case "Pelly_32":
            dialog.text = "Certo che è un mucchio d'oro! Ma non è tuo o di Tyrex! L'ho trovato io per primo! È mio! Non importa come ne sono venuto a conoscenza! Non sono affari tuoi!";
			link.l1 = "Calmati Cutlass, perché sei così arrabbiato? Guarda questo mucchio - ci devono essere un milione. Forse anche di più! Abbastanza per entrambi!";
			link.l1.go = "Pelly_33";
		break;
		
		case "Pelly_33":
            dialog.text = "Ottieni sempre una fetta migliore di una torta, Principe! Ma non questa volta! Il tesoro è mio! L'ho trovato per primo!";
			link.l1 = "Maledizione, Paul, cosa ti prende? Non possiamo fare un accordo qui? Anche la metà di quest'oro è una fortuna. Non hai mai avuto una somma così grande nelle tue mani prima. Inoltre potrei trovare una pista redditizia un giorno e dirtelo.";
			link.l1.go = "Pelly_34";
		break;
		
		case "Pelly_34":
            dialog.text = "Vuoi fregarmi, Principe? Neanche per sogno! Non ti darò un solo soldo, neanche una singola ghinea! Sei in ritardo!\nAh-ah, capisco cosa stai cercando di fare! Non avrai questo oro!!!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionPellyFight");
		break;
		
		case "Pelly_35": //
            dialog.text = "Divertente. Davvero. Sei un comico, ammiraglio. Ma è vero - a Marcus non piacciono quelli che cercano di fregarlo, come te. Ma apprezza gli uomini intelligenti.";
			link.l1 = "Bene, bene. Allora, cosa ti preoccupa?";
			link.l1.go = "Pelly_36";
		break;
		
		case "Pelly_36":
            dialog.text = "Qualcosa che tu e Handsome chiaramente non avete considerato. State pianificando una rivolta nella piantagione. Ottima idea - se l'obiettivo era saccheggiare o creare caos. Ma...";
			link.l1 = "Ma cosa? Sei contrario alla rivolta? Ti spaventa?";
			link.l1.go = "Pelly_37";
		break;
		
		case "Pelly_37":
            dialog.text = "Io? Ah! Mai. Ma pensa a cosa succede se Handsome incontra la sua fine durante il massacro. Cosa diremo a Marcus? Ti dico cosa - non importerà quello che diremo. Avrà la nostra pelle comunque.";
			link.l1 = "Mmm. Quindi qual è il tuo brillante piano? Dobbiamo tirarlo fuori in qualche modo.";
			link.l1.go = "Pelly_38";
		break;
		
		case "Pelly_38":
            dialog.text = "Lo facciamo. Ecco perché... perché non comprarlo? Ufficialmente, voglio dire. Un pugno di oro può comprare chiunque da questi bastardi, anche le loro stesse madri. Cosa dire del povero Jean?";
			link.l1 = "Ha! Cutlass, stai seriamente suggerendo che entri in una piantagione e chieda di comprare Picard? Dovrei anche dire loro per chi lavoro, giusto per divertimento? Hai perso la testa?";
			link.l1.go = "Pelly_39";
		break;
		
		case "Pelly_39":
            dialog.text = "Non c'è bisogno di dire quello. Anzi, tutto il contrario - fai finta di essere un mercante. Certo, non hai la pancia per il ruolo, ma non sembri nemmeno un pirata. Nessuna offesa, Ammiraglio, ma è la verità. Entrate solo in quella piantagione, agite con sicurezza e chiedete di Jean. Il proprietario potrebbe sospettare chi sei, ma non lo mostrerà. Come ho detto - una manciata di monete d'oro sigilla le bocche.";
			link.l1 = "E quanto ci costerebbe questa... mano d'oro? L'intera montagna?";
			link.l1.go = "Pelly_40";
		break;
		
		case "Pelly_40":
            dialog.text = "Magari. Ma è meglio separarsi dall'oro che dalla testa. Non sono stato inattivo mentre tu eri a terra - mi sono cambiato in qualcosa di meno pirata e ho chiesto in giro sulla piantagione e sul suo umile proprietario.";
			link.l1 = "E cosa hai trovato, Sciabola?";
			link.l1.go = "Pelly_41";
		break;
		
		case "Pelly_41":
            dialog.text = "Prezzi di mercato, per così dire. Non è la prima volta che un prigioniero di valore finisce tra le sue mani. Di solito, finiscono sulla forca o peggio - nelle segrete dell'Inquisizione.";
			link.l1 = "E a quanto le vende?";
			link.l1.go = "Pelly_42";
		break;
		
		case "Pelly_42":
            dialog.text = "Per qualcuno importante? Cinquecento monete. In dobloni, ovviamente.";
			link.l1 = "CINQUECENTO?!";
			link.l1.go = "Pelly_43";
		break;
		
		case "Pelly_43":
            dialog.text = "Piantatori, cosa vi aspettavate?";
			link.l1 = "Per quel prezzo, potrei equipaggiare un piccolo esercito! Perché diavolo sto accumulando un arsenale sulla mia nave per una rivolta? Questo sarà sufficiente per una piccola guerra.";
			link.l1.go = "Pelly_44";
		break;
		
		case "Pelly_44":
            dialog.text = "Le armi ti saranno utili per il tuo equipaggio in seguito, in ogni caso. Allora, cosa dici?";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				if (PCharDublonsTotal() >= 500)
				{
					link.l1 = "(Affidabile) Dirò solo che sarà divertente se la ricompensa di Terrax è inferiore a quello che spendiamo qui. Ma hai ragione - le nostre vite valgono di più. Ho i dobloni.";
					link.l1.go = "Pelly_45";
				}
				link.l2 = "Non ho quel tipo di montagna d'oro al momento.";
				link.l2.go = "Pelly_44_1";
				notification("Trustworthy", "Trustworthy");
			}
			else notification("Perk Check Failed", "Trustworthy");
			link.l3 = "Sai cosa, Cutlass? Lascia stare. Siamo pirati o cosa? E Jean? O il suo bel viso è il suo unico pregio? Prepara un baule - ci atterremo al piano originale.";
			link.l3.go = "Pelly_62";
		break;
		
		case "Pelly_44_1":
            dialog.text = "Sarei sorpreso se lo facessi - è una somma enorme. Bene, quando sei pronto, o se escogiti qualcosa di meglio, vieni a cercarmi.";
			link.l1 = "Certo. Aspetta qui.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Pelly_44_2";
		break;
		
		case "Pelly_44_2":
			dialog.text = "Ebbene, ammiraglio, hai racimolato abbastanza oro per salvare Picard?";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "Sì, finalmente l'ho fatto. Speriamo che funzioni.";
				link.l1.go = "Pelly_45";
			}
			link.l2 = "Sto ancora lavorando su di esso, Cutlass.";
			link.l2.go = "exit";
			link.l3 = "Non darò i miei sudati soldi a quei piantatori avidi! Prepariamo il baule - ci comporteremo come Gentiluomini di Fortuna. Questa è la mia decisione.";
			link.l3.go = "Pelly_9";
			NextDiag.TempNode = "Pelly_44_2";
		break;
		
		case "Pelly_45":
            dialog.text = "Whoa. Sei nuovo nel nostro equipaggio e già stai spargendo quel tipo di soldi!";
			link.l1 = "I soldi non sono tutto. Ma crogiolarsi nella gloria di Terrax? Non ha prezzo.";
			link.l1.go = "Pelly_46";
			pchar.questTemp.mtraxx_PlantVykup = true;
		break;
		
		case "Pelly_46":
            dialog.text = "Non posso discutere su questo. Ma come hai detto, non si tratta solo di soldi - c'è qualcos'altro di importante, ammiraglio.";
			link.l1 = "Sono curioso ora. Cosa?";
			link.l1.go = "Pelly_47";
		break;
		
		case "Pelly_47":
            dialog.text = "Ti ho detto che ho esaminato tutto sulla piantagione. Incluso quali merci sono richieste qui e circolano sul mercato. Se vuoi farti passare per un commerciante legittimo, sarebbe meglio che tu facessi scorta di quelle invece di sbattere semplicemente un mucchio d'oro sulla scrivania del piantatore.";
			link.l1 = "Ha senso. Di che tipo di merci stiamo parlando?";
			link.l1.go = "Pelly_48";
		break;
		
		case "Pelly_48":
            dialog.text = "Ebbene, a parte le merci viventi, eh-eh, il proprietario della piantagione locale compra, scambia e rivende caffè, copra e vaniglia. Quindi...";
			link.l1 = "Devo rifornirmi rapidamente da qualche parte. O attaccare una carovana e sperare che trasporti ciò di cui ho bisogno.";
			link.l1.go = "Pelly_49";
		break;
		
		case "Pelly_49":
            dialog.text = "Non solo una carovana qualsiasi. Mi dispiace separarmi da essa, ma ho riservato un'opportunità per me stesso. Una carovana che trasporta esattamente ciò di cui hai bisogno arriverà presto. Ma c'è un avvertimento...";
			link.l1 = "Oh, cosa adesso?";
			link.l1.go = "Pelly_50";
		break;
		
		case "Pelly_50":
            dialog.text = "È sotto la bandiera francese.";
			link.l1 = "Cosa?!";
			link.l1.go = "Pelly_51";
		break;
		
		case "Pelly_51":
            dialog.text = "Capisco la tua frustrazione, ah-ah. La decisione è tua... Ammiraglio. Vuoi i dettagli?";
			link.l1 = "Maledizione... Va bene, sputalo fuori. Non abbiamo molto tempo - se tu o io non li mordiamo, qualcun altro lo farà.";
			link.l1.go = "Pelly_52";
			link.l2 = "Non tocco i francesi a meno che non abbia altra scelta. Fine della discussione.";
			link.l2.go = "Pelly_51_1";
		break;
		
		case "Pelly_51_1":
            dialog.text = "Allora faresti meglio a iniziare a raccogliere tutti quei beni da solo e velocemente prima che Pretty Boy venga venduto a qualcuno. Non posso rimanere qui in eterno neanche io.";
			link.l1 = "Me lo aspettavo.";
			link.l1.go = "Pelly_51_2";
		break;
		
		case "Pelly_51_2": // добываем товары сами
            DialogExit();
			
			LAi_SetActorType(npchar);
			AddQuestRecord("Roger_3", "28");
			SetTimerCondition("Mtraxx_PlantCaravanGuadeloupe", 0, 0, 14, false);
			SetTimerCondition("Mtraxx_PlantCaravanGuadeloupe_time", 0, 0, 45, false);
			//DoQuestCheckDelay("Mtraxx_PlantCaravanGuadeloupe", 1.0);
		break;
		
		case "Pelly_52":
            dialog.text = "Ecco cosa mi piace sentire! Sapevo che ne eri capace... Ammiraglio. Ecco il piano: un mio contatto affidabile ha riportato di recente che tra circa due settimane, una carovana francese trasportante caffè e spezie apparirà nelle acque di Guadalupa. È grande e ben armata, quindi preparati in modo approfondito.";
			link.l1 = "Qual altra scelta ho.";
			link.l1.go = "Pelly_53";
		break;
		
		case "Pelly_53": // наводка на караван с нужными товарами
            DialogExit();
			
			LAi_SetActorType(npchar);
			AddQuestRecord("Roger_3", "28");
			//if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup")) AddQuestUserData("Roger_3", "sText", "Who would've thought that among the captains of Terrax, there'd be someone with at least the spark of a negotiator or a true entrepreneurial streak? That person turned out to be my temporary companion, Paul "Cutlass." Understanding the consequences of Marcus's wrath if we fail his assignment, Cutlass suggested... officially buying Picard from the plantation owner. While I scouted the situation and spoke with Jean, Cutlass didn't waste time either. He discovered that the plantation owner frequently sells valuable captives, with the average price for such transactions being around 500 doubloons - a small fortune. But Paul is right - it's better to do this than risk Picard being killed by a stray bullet or blade. Now all that's left is to load up on the plantation's usual trade goods - be it coffee, copra, or vanilla - in large quantities.");
			SetTimerCondition("Mtraxx_PlantCaravanGuadeloupe", 0, 0, 14, false);
			SetTimerCondition("Mtraxx_PlantCaravanGuadeloupe_time", 0, 0, 45, false);
			//DoQuestCheckDelay("Mtraxx_PlantCaravanGuadeloupe", 1.0);
		break;
		
		case "Pelly_54": // провал выкупа Красавчика
            dialog.text = "Sembrate giù di morale, Ammiraglio. Dove è Splendido? È tutto andato a monte?";
			link.l1 = "Certo. Ho guadagnato un bel pò di soldi, ma quel testardo di mulo si è rifiutato di vendermi Picard - anche per un mucchio di dobloni!";
			link.l1.go = "Pelly_55";
		break;
		
		case "Pelly_55":
            dialog.text = "Che sciocco! E adesso?";
			link.l1 = "Ho già concordato con il coltivatore di scaricare la merce. Dovremo tornare al piano originale - è adesso o mai più!";
			link.l1.go = "Pelly_56";
		break;
		
		case "Pelly_56":
            dialog.text = "Ma non abbiamo nemmeno preparato nulla per Handsome e gli altri!";
			link.l1 = "Non c'è tempo! Salite sulle navi - nasconderemo armi e medicine dai nostri depositi nei sacchi di merci. E non dimenticate di issare la bandiera spagnola!";
			link.l1.go = "Pelly_57";
		break;
		
		case "Pelly_57":
            dialog.text = "Sembra un piano.";
			link.l1 = "Comunque non abbiamo tempo per altro. Muoviti! Lo scarico avviene presto.";
			link.l1.go = "Pelly_58";
		break;
		
		case "Pelly_58":
            DialogExit();
			DoQuestFunctionDelay("Mtraxx_PlantWaitDay", 1.0);
		break;
		
		case "Pelly_59":
            dialog.text = "Guarda chi si vede! Bello! E a giudicare dal tuo viso intatto e dal tuo passo sicuro, deduco che tutto è andato liscio?";
			link.l1 = "Dire che è andato liscio è un eufemismo - non solo ho evitato una lotta e ho ricomprato Jean, ma ho anche guadagnato un po' di soldi. Il tuo piano ha funzionato perfettamente, Paul. Tutto tranquillo all'orizzonte?";
			link.l1.go = "Pelly_60";
		break;
		
		case "Pelly_60":
            dialog.text = "Silenzioso come può essere. Tornando da Marcus?";
			link.l1 = "Giusto.";
			link.l1.go = "Pelly_61";
		break;
		
		case "Pelly_61":
            DialogExit();
			DeleteAttribute(pchar,"questTemp.Mtraxx.MagicBox");
			chrDisableReloadToLocation = true;
			LocatorReloadEnterDisable("shore37", "boat", false);
			bQuestDisableMapEnter = false;
			AddQuestRecord("Roger_3", "29");
			pchar.questTemp.Mtraxx = "plant_success";
			QuestSetCurrentNode("Terrax", "mtraxx_27");
			//SetFunctionTimerCondition("Mtraxx_PlantGoHomeOver", 0, 0, 40, false);
			SetFunctionTimerCondition("Mtraxx_PlantOpenMaracaibo", 0, 0, 5, false);
			
			sld = characterFromId("Mtr_plantation_boss");
			sld.lifeday = 0;
			
			sld = &Locations[FindLocation("shore37")];
			sld.DisableEncounters = false;
			sld = ItemsFromID("fire");
			sld.shown = false;
			DeleteAttribute(sld, "fire");
			for (i=1; i<=4; i++)
			{
				if (GetCharacterIndex("Pelly_sailor_"+i) != -1)
				{
					sld = characterFromId("Pelly_sailor_"+i);
					sld.lifeday = 0;
					LAi_SetActorType(sld);
					LAi_ActorRunToLocation(sld, "reload", "sea", "none", "", "", "", 5);
				}
			}
			sld = characterFromId("Pelly");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "sea", "none", "", "", "OpenTheDoors", 5);
			sld = characterFromId("mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "sea", "none", "", "", "", 5);
		break;
		
		case "Pelly_62":
            dialog.text = "Mah, come desideri, Ammiraglio. Ma se succede qualcosa a Handsome, mi assicurerò che Terrax sappia che hai ignorato il mio consiglio. Hai tutto pronto per la fuga?";
			link.l1 = "Lasciami ricontrollare e contare cosa ho nel baule.";
			link.l1.go = "Pelly_63";
		break;
		
		case "Pelly_63":
            dialog.text = "Sii certo di questo. Posso aiutare per una modesta tariffa e per coprire i miei sforzi, eheh.";
			link.l1 = "Com'è così?";
			link.l1.go = "Pelly_64";
		break;
		
		case "Pelly_64":
            dialog.text = "Ho un contatto, un trafficante d'armi a Maracaibo. Mi travestirò, entrerò di nascosto, lo pagherò e organizzerò il contrabbando delle armi qui. Ma ti costerà - dubloni d'oro, per l'esattezza.";
			link.l1 = "E perché non mi hai presentato prima a questo tizio? Quanto mi costerà?";
			link.l1.go = "Pelly_65";
		break;
		
		case "Pelly_65":
            dialog.text = "Dovrei presentarti anche tutti i miei informatori? Va bene. Considerando le spese, i rischi e la mia quota... costerà circa quanto il riscatto per il Bello.";
			link.l1 = "Scimitarra, temi Dio...";
			link.l1.go = "Pelly_66";
		break;
		
		case "Pelly_66":
            dialog.text = "Non temo né Dio né te, Ammiraglio. Ma l'ira di Marcus se non riusciamo a salvare Jean? Questa è un'altra storia. Allora, come sarà? Hai bisogno di aiuto con il baule?";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "Bene, vai avanti - è già stato sprecato abbastanza tempo. Ecco, questa dovrebbe essere la giusta quantità.";
				link.l1.go = "Pelly_68";
			}
			link.l2 = "È un sacco di soldi, Paul. Devo pensarci su.";
			link.l2.go = "Pelly_67";
			link.l3 = "È decisamente troppo costoso per un piccolo lotto di armi che posso comprare all'ingrosso molto più economico! No grazie, me ne occuperò io stesso.";
			link.l3.go = "Pelly_67_1";
		break;
		
		case "Pelly_67":
            dialog.text = "Ebbene, pensa pure. Ma ricorda - mentre stai pensando, il numero di lividi sul volto e sul corpo di Handsome aumenta di ora in ora, eh-eh-eh.";
			link.l1 = "Ti porterò i dobloni...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Pelly_67_2";
		break;
		
		case "Pelly_67_1":
            dialog.text = "Non si tratta della dimensione della spedizione, ma del tempismo e dei rischi. Ma fai come credi.";
			link.l1 = "Fidati di me, lo so. Prepara solo il baule - me ne occuperò io da qui.";
			link.l1.go = "Pelly_10";
		break;
		
		case "Pelly_67_2":
            dialog.text = "Pronto, Ammiraglio? Hai bisogno di aiuto con le armi, o sei ancora a corto d'oro?";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "Alla fine ne ho abbastanza! Prendilo e risolvi questa faccenda - mi sta dando sui nervi.";
				link.l1.go = "Pelly_68";
			}
			link.l2 = "Guarda come parli, Spada. Sono pronto, ma ho bisogno di più tempo per racimolare i soldi.";
			link.l2.go = "Pelly_67";
			link.l3 = "È decisamente troppo costoso per un piccolo lotto di armi che posso comprare all'ingrosso molto più economico! No grazie, me ne occuperò io stesso.";
			link.l3.go = "Pelly_67_1";
		break;
		
		case "Pelly_68":
            dialog.text = "Oh, che mucchio di dobloni è questo! Ma non preoccuparti - ogni moneta andrà a favore del piano. Altrimenti, Marcus mi scaverebbe dalla tomba più tardi, heh-heh. Ora, vai da Bello, Ammiraglio, e digli che tutto è pronto.";
			link.l1 = "Sono io qui a dare gli ordini. Ora, muoviti.";
			link.l1.go = "Pelly_69";
			RemoveDublonsFromPCharTotal(500);
		break;
		
		case "Pelly_69":
            DialogExit();
			sld = characterFromId("Pelly");
			sld.dialog.currentnode = "Pelly_7";
			pchar.questTemp.Mtraxx = "plant_5";
			AddQuestRecord("Roger_3", "30");
			sld = characterFromId("Mrt_Rocur");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "rocur_wait";
			sld.greeting = "Rocur_02";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "Pelly_70":
            dialog.text = "Sì, è un problema. Qual è il tuo piano, ammiraglio?\nHo esaminato tutto riguardo la piantagione. Incluso quali merci sono richieste qui e circolano sul mercato. Se vuoi farti passare per un commerciante legittimo, sarebbe meglio che ti approvvigionassi di quelle invece di buttare semplicemente un mucchio d'oro sulla scrivania del piantatore.";
			link.l1 = "Ha senso. Di che tipo di merci stiamo parlando?";
			link.l1.go = "Pelly_48";
			DeleteAttribute(pchar, "questTemp.mtraxx_PlantInfoTovar");
		break;
		
		// Жан Пикар
		case "rocur":
            dialog.text = "Cosa vuoi da me?";
			link.l1 = "Amico mio, sto cercando Jean Picard. C'è qualche possibilità che tu porti lo stesso nome?";
			link.l1.go = "rocur_1";
		break;
		
		case "rocur_1":
            dialog.text = "C'è una possibilità. Tuttavia, non ricordo il tuo volto.";
			link.l1 = "Non essere troppo brusco, Jean. Sono stato mandato qui da Marcus Tyrex. I miei ordini sono di farti uscire da qui.";
			link.l1.go = "rocur_2";
		break;
		
		case "rocur_2":
            dialog.text = "Marcus? Tsh-sh... Silenzio. Mi dispiace, amico, non lo sapevo. Ma non dovremmo parlare qui, ci sono maledetti guardie dappertutto e stanno sempre ascoltando... Vedo che sei un ospite gradito tra gli spagnoli, trova me in una delle capanne di notte e parleremo. Ti starò aspettando, fratello.";
			link.l1 = "...";
			link.l1.go = "rocur_3";
		break;
		
		case "rocur_3":
            DialogExit();
			AddQuestRecord("Roger_3", "6");
			LAi_CharacterDisableDialog(npchar);
			Mtraxx_PlantMakeMaxRocurClone();
		break;
		
		case "rocur_4":
            dialog.text = "Ebbene, qui è sicuro... Come ti chiami, fratello?";
			link.l1 = "Capitano "+GetFullName(pchar)+". Ora dimmi, come sei finito in questa merda. Tyrex vuole sapere tutto.";
			link.l1.go = "rocur_5";
		break;
		
		case "rocur_5":
            dialog.text = "Sono stato avvicinato da uno sconosciuto in una taverna di Willemstad... Mi ha chiesto di essere il suo compagno per saccheggiare un convoglio olandese. Avevo una brigantina, lui aveva un polacre, molto unico anche. Così abbiamo inseguito un convoglio non lontano da Caracas e lo abbiamo saccheggiato... Era notte, stavamo dividendo il bottino quando un'imponente galea spagnola è apparsa nel buio\nIl mio compagno è fuggito e così ho fatto io. Ma non c'era modo per la mia brigantina danneggiata di sfuggire a una galea e altre due navi. Ci hanno abbordato e venduto tutti i sopravvissuti a questo posto come bestiame.";
			link.l1 = "Capisco. Pensi che sia stato un incidente? Sto parlando della galea.";
			link.l1.go = "rocur_6";
		break;
		
		case "rocur_6":
            dialog.text = "Cavolo, se lo sapessi. Potrebbero aver sentito una sparatoria, non era lontano dalla Piazza Principale.";
			link.l1 = "Mmm. È possibile. Hai incontrato il tuo ex compagno prima? Chi è?";
			link.l1.go = "rocur_7";
		break;
		
		case "rocur_7":
            dialog.text = "Mai incontrato prima. Ha detto che il suo nome era Ignacio Marco, un corsaro d'Inghilterra. Mi ha dato l'impressione di essere un uomo serio, ecco perché ho accettato di partecipare a questa impresa. È sicuramente un marinaio esperto e un capitano, ha un equipaggio audace dietro di lui e la sua polacca è una bellezza, non tutti i giorni si può vedere una nave come quella.";
			link.l1 = "Ignacio Marco? Un corsaro inglese? È spagnolo?";
			link.l1.go = "rocur_8";
		break;
		
		case "rocur_8":
            dialog.text = "È un portoghese, non uno spagnolo. Qual è il problema con una lettera di marca britannica? Abbiamo un sacco di spagnoli tra noi, lo sai.";
			link.l1 = "Capisco. Bene, parliamo della tua fuga da qui. Hai qualche idea?";
			link.l1.go = "rocur_9";
		break;
		
		case "rocur_9":
            dialog.text = "Quali sono i tuoi numeri?";
			link.l1 = "La mia nave, una barquentina e gli uomini di Pelly il Coltello. La mia nave è ormeggiata nel porto di Maracaibo. Il Coltello ha sbarcato nella baia di Guajira e ha montato un campo là.";
			link.l1.go = "rocur_10";
		break;
		
		case "rocur_10":
            dialog.text = "Mmm...";
			link.l1 = "Cosa, ti aspettavi che Tyrex mandasse una nave di linea qui?";
			link.l1.go = "rocur_11";
		break;
		
		case "rocur_11":
            dialog.text = "Non mi aspettavo nulla. In realtà, sono sorpreso che Marcus non si sia dimenticato di me.";
			link.l1 = "Non l'ha fatto, ovviamente. Quindi, hai qualche idea?";
			link.l1.go = "rocur_12";
		break;
		
		case "rocur_12":
            dialog.text = "Nessuna possibilità di fuga da qui - questa piantagione è troppo ben sorvegliata e ci sono giungle selvagge intorno. Non ha senso nemmeno assaltarla, non hai abbastanza uomini, in più c'è un forte nelle vicinanze.";
			link.l1 = "Forse, tu e i tuoi ragazzi potreste aiutarci dall'interno? Colpiscili duramente alle spalle.";
			link.l1.go = "rocur_13";
		break;
		
		case "rocur_13":
            dialog.text = "Con cosa? Mani nude e machete arrugginiti?";
			link.l1 = "E se avessi delle armi?";
			link.l1.go = "rocur_14";
		break;
		
		case "rocur_14":
            dialog.text = "Ebbene, in tal caso avremmo fatto loro vedere i diavoli. C'è un problema però, controllano tutto quello che porti dentro, non c'è modo di contrabbandare armi. Quindi suggerisco di dimenticare tutto questo.";
			link.l1 = "Eppure, al momento è la nostra migliore opzione. Penserò a come fornirti a te e ai tuoi uomini delle armi... Dimmi, quanti di voi sono in grado di combattere?";
			link.l1.go = "rocur_15";
		break;
		
		case "rocur_15":
            dialog.text = "Trenta teste, direi.";
			link.l1 = "Trenta sciabole allora ... Credo che anche le pistole farebbero la differenza.";
			link.l1.go = "rocur_16";
		break;
		
		case "rocur_16":
            dialog.text = "Capitano, parli sul serio di questo?";
			link.l1 = "Sono io. Sono arrivato qui di proposito, scherzare non fa parte del piano. Di cosa altro potresti aver bisogno?";
			link.l1.go = "rocur_17";
		break;
		
		case "rocur_17":
            dialog.text = "Molto bene... Diamo un'occhiata almeno. Abbiamo bisogno di semplice acciaio freddo - i miei ragazzi non sono addestrati a lavorare con raffinati stocchi e simili. Lo stesso può essere detto delle pistole, le più economiche andranno benissimo. Se ci procuri un paio di moschetti, ci aiuteresti molto, ho un paio di ragazzi bravi con i moschetti. Pallottole, polvere da sparo. Le pozioni curative sono le più gradite.";
			link.l1 = "Capito. Spade e asce possono essere prese dall'arsenale della nave. Il resto è più difficile da ottenere. Ti farò sapere quando avrò tutto.";
			link.l1.go = "rocur_18";
		break;
		
		case "rocur_18":
            dialog.text = "Per favore, sbrigati, fratello. Non abbiamo mezzo anno qui, questo maledetto lavoro da manovali ci sta uccidendo uno ad uno. Se hai bisogno di me - vieni a trovarmi di notte.";
			link.l1 = "Capito, amico. Aspetta, cercherò di non farti aspettare. E stai attento, non dargli un motivo per liquidarti, ancora.";
			link.l1.go = "rocur_19";
		break;
		
		case "rocur_19":
            DialogExit();
			AddQuestRecord("Roger_3", "7");
			npchar.dialog.currentnode = "rocur_wait";
			pchar.questTemp.Mtraxx = "plant_3";
			pchar.questTemp.Mtraxx.MagicBox = "Baster";
			AddLandQuestMark(characterFromId("Fadey"), "questmarkmain");
			AddMapQuestMarkCity("baster", false);
			pchar.quest.Mtraxx_PlantPrepareTimeOver.over = "yes"; //снять таймер
			SetFunctionTimerCondition("Mtraxx_SeekWeaponOver", 0, 0, 30, false); // таймер
		break;
		
		case "rocur_wait":
            dialog.text = "Qualche novità, amico? Hai raccolto le armi?";
			if (pchar.questTemp.Mtraxx == "plant_5")
			{
				link.l1 = "Sì. Un baule con munizioni si trova nella Baia di Guajira. Tutto quello che rimane è trovare un modo per farlo entrare di nascosto nella piantagione.";
				link.l1.go = "rocur_20";
			}
			else
			{
				link.l1 = "Sono su di esso. Aspetta.";
				link.l1.go = "rocur_wait_1";
			}
		break;
		
		case "rocur_wait_1":
            DialogExit();
			npchar.dialog.currentnode = "rocur_wait";
		break;
		
		case "rocur_20":
            dialog.text = "Molto bene, capitano. Ho già pensato a come eseguire ciò.";
			link.l1 = "Contento di sentirlo. Cosa ti preoccupa?";
			link.l1.go = "rocur_21";
			DelLandQuestMark(npchar);
		break;
		
		case "rocur_21":
            dialog.text = "Producono zucchero e coltivano fagioli di cacao in questa piantagione. A volte il suo capo vende la merce da solo, è più redditizio così. Fagli un'offerta. Pagalo non con soldi ma con merci. Qualcosa che puoi mettere nelle scatole come copra, vaniglia o caffè. Metti un po' di impegno nel contrattare ma non esagerare\nNascondi le armi in una o due scatole e metti dei segni su di loro. Organizza uno scambio alla sera in modo che dovranno lasciare le scatole fuori per una notte\nDi notte troveremo le tue scatole segnate, ci armeremo e daremo l'inferno agli spagnoli. Con il tuo aiuto, ovviamente.";
			link.l1 = "Bel pensiero, fratello! Molto bene, mi piace questo piano. Teniamoci a questo.";
			link.l1.go = "rocur_22";
		break;
		
		case "rocur_22":
            dialog.text = "Un'ultima cosa - offri solo un tipo di merci per lo scambio. Più tipi di merci - più caselle controllate dalle guardie.";
			link.l1 = "Sono d'accordo. Sceglierò solo un tipo allora. Caffè, vaniglia e copra, hai detto?";
			link.l1.go = "rocur_23";
		break;
		
		case "rocur_23":
            dialog.text = "Sì. Questo sembrerà un buon affare al capo della piantagione.";
			link.l1 = "Capito. Ti farò sapere quando l'affare è concluso.";
			link.l1.go = "rocur_24";
		break;
		
		case "rocur_24":
            DialogExit();
			AddQuestRecord("Roger_3", "9");
			npchar.dialog.currentnode = "rocur_wait_2";
			pchar.questTemp.Mtraxx = "plant_6";
			pchar.questTemp.mtraxx_PlantInfoTovar = true;
			AddLandQuestMark(characterFromId("Pelly"), "questmarkmain");
		break;
		
		case "rocur_wait_2":
            dialog.text = "Vai amico mio, il tempo è oro e noi non ne abbiamo...";
			link.l1 = "";
			link.l1.go = "rocur_wait_3";
		break;
		
		case "rocur_wait_3":
            DialogExit();
			npchar.dialog.currentnode = "rocur_wait_2";
		break;
		
		case "rocur_25":
            dialog.text = "...";
			link.l1 = "(sottovoce) L'accordo è fatto. Le casse saranno consegnate alla piantagione domani sera. Le casse di cui hai bisogno sono contrassegnate con una lettera 'W'. Le altre hanno il resto dell'alfabeto su di loro. Prepara i tuoi uomini. Attaccheremo prima dell'alba, intorno alle tre.";
			link.l1.go = "rocur_25x";
			DelLandQuestMark(npchar);
		break;
		
		case "rocur_25x":
            dialog.text = "Inizieremo al tuo segnale...";
			link.l1 = "";
			link.l1.go = "rocur_26";
		break;
		
		case "rocur_26":
            DialogExit();
			LAi_CharacterDisableDialog(npchar);
			DoQuestFunctionDelay("Mtraxx_PlantWaitDay", 3.0);
		break;
		
		case "rocur_27":
            dialog.text = "Finalmente! Sto per vedere di nuovo il mare! Ho già dimenticato il suo aspetto e il suo odore. Ben fatto capitano! Ti devo.";
			link.l1 = "Non preoccuparti, lo risolveremo dopo... Ora imbarchiamoci e andiamo via da qui!";
			link.l1.go = "rocur_28";
		break;
		
		case "rocur_28":
            DialogExit();
			sld = characterFromId("Pelly");
			sld.Dialog.currentnode = "Pelly_16";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "rocur_29":
            dialog.text = "Saluti "+pchar.name+". Felice di rivederti, anche felice di averti come mio compagno in questa avventura. Questo lavoro sarà duro ma sono sicuro che ce la faremo.";
			link.l1 = "È bello rivederti Picard. Sono tutto orecchie, raccontami questa tua avventura.";
			link.l1.go = "rocur_30";
		break;
		
		case "rocur_30":
            dialog.text = "Ho già detto a Marcus, ora te lo dirò. Quando ero uno schiavo nella piantagione a Maracaibo ho imparato qualcosa dagli spagnoli. Sono piuttosto loquaci quando sono ubriachi... Ascolta, a sud-est della baia di Maracaibo c'è un piccolo villaggio. È nascosto tra due montagne nel profondo della giungla. Ha un nome diavolo: Santiago-de-Los-Caballeros-de-Merida. Chiamiamolo Merida\nNon sembra molto interessante ancora, vero? Si è scoperto che le montagne che circondano il villaggio sono ricche di gemme. Smeraldi, opali e leggendari opali di fuoco\nPer quanto ne capisco, i coloni di Merida non hanno parlato al governatore generale di queste gemme. Tuttavia presto lo saprà, ecco perché dovremmo visitare Merida prima dell'arrivo degli ufficiali coloniali spagnoli.";
			link.l1 = "Vuoi saccheggiare l'insediamento?";
			link.l1.go = "rocur_31";
		break;
		
		case "rocur_31":
            dialog.text = "Esattamente. È perso tra giungle e montagne con una piccola guarnigione - una preda facile per un'unità di corsari. Inoltre, sono molto lontani dal mare, non si aspettano che qualcuno li attacchi tranne i selvaggi con lance e archi.";
			link.l1 = "Quanto sei sicuro che l'insediamento abbia pietre preziose?";
			link.l1.go = "rocur_32";
		break;
		
		case "rocur_32":
            dialog.text = "Se le nostre avventure si rivelano una falsa traccia, io stesso servirò sulla tua nave come ufficiale o marinaio, pulirò i ponti e combatterò in innumerevoli abbordaggi fino a quando il mio debito con te e Marcus sarà cancellato.";
			link.l1 = "Capisco... Molto bene, sai come arrivare a Merida?";
			link.l1.go = "rocur_33";
		break;
		
		case "rocur_33":
            dialog.text = "Certo, non conosco il percorso esatto attraverso le giungle, ma assumeremo una guida dalla gente indiana. Dovremmo sbarcare a sud del lago Maracaibo, trovare un villaggio indiano e trovare chi sa come arrivarci.";
			link.l1 = "...";
			link.l1.go = "rocur_34";
		break;
		
		case "rocur_34":
            DialogExit();
			sld = characterFromId("Terrax");
			sld.Dialog.currentnode = "mtraxx_38";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rocur_35":
            dialog.text = "Capitano, mi dispiace molto per il mio linguaggio, ma perché diavolo non siamo ancora a Merida? Eh? Hai sputato sulla nostra causa comune! Leprechaun ed io ce ne andiamo senza di te. Spiegherò tutto a Tyrex e tu dovresti andare. Ecco, prendi 50 000 pesos per il tuo aiuto a Maracaibo, li ho presi in prestito da amici. Addio, dannata vergogna, pensavo meglio di te.";
			link.l1 = "Mmm... Mi dispiace.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_MeridaTimeOverFail");
		break;
		
		case "rocur_36":
            dialog.text = "Eccoci qui. Le giungle davanti a noi. Prima, dovremmo trovare un villaggio indiano e chiedere informazioni per una guida.";
			link.l1 = "Facciamolo. Luke, hai qualcosa da dire... o magari un consiglio?";
			link.l1.go = "rocur_37";
		break;
		
		case "rocur_37":
            DialogExit();
			sld = characterFromId("Lepricon");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rocur_38":
            dialog.text = "La guarnigione di Merida è finita. Non mi aspetto resistenza seria all'interno del villaggio. Andiamo!";
			link.l1 = "All'attacco!!!";
			link.l1.go = "rocur_39";
		break;
		
		case "rocur_39":
            DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Merida_ExitTown", "reload1_back", true);
			pchar.quest.mtraxx_merida_town.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_town.win_condition.l1.location = "Merida_Town";
			pchar.quest.mtraxx_merida_town.function = "Mtraxx_MeridaTown";
			Mtraxx_MeridaCheckOurWarriors();
			AddQuestRecord("Roger_5", "16");
		break;
		
		case "rocur_40":
            dialog.text = "È fatto! Non ci sono più eroi. Ora dovremmo parlare con il governatore di questa 'città'. Spero sia del tipo persuadibile.";
			link.l1 = "Sono d'accordo, 'persuadiamolo'!.. Jean! Seguimi!";
			link.l1.go = "rocur_41";
		break;
		
		case "rocur_41":
            DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Merida_Town", "gate_back", true);
			pchar.quest.mtraxx_merida_townhall.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_townhall.win_condition.l1.location = "Merida_townhall";
			pchar.quest.mtraxx_merida_townhall.function = "Mtraxx_MeridaTownhall";
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			sld = characterFromId("Lepricon");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			AddQuestRecord("Roger_5", "17");
		break;
		
	case "rocur_42": //злой вариант
            DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Merida_Town", "reload3", true); 
			pchar.questTemp.Mtraxx = "merida_success";
			pchar.quest.mtraxx_merida_exit.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_exit.win_condition.l1.location = "Merida_Town";
			pchar.quest.mtraxx_merida_exit.function = "Mtraxx_MeridaExit";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			
			sld = characterFromId("Merida_Head");
			LAi_SetActorType(sld);
			
			pchar.questTemp.Mtraxx_MeridaZloVariant = true;
			
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "reload", "reload1", "Mtraxx_MeridaExitResidensia", -1);
		break;
		
		case "rocur_43": //мирный вариант
            DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Merida_Town", "reload3", true); 
			pchar.questTemp.Mtraxx = "merida_success";
			pchar.quest.mtraxx_merida_exit.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_exit.win_condition.l1.location = "Merida_Town";
			pchar.quest.mtraxx_merida_exit.function = "Mtraxx_MeridaExit";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			
			sld = characterFromId("Merida_Head");
			LAi_SetActorType(sld);
			
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto2", "Mtraxx_MeridaGiveJewelry", -1);
			
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "reload", "reload1", "Mtraxx_MeridaExitResidensia", -1);
		break;
		
		case "rocur_44":
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaKamushki"))
			{
            	dialog.text = "Bene fatto, "+pchar.name+"! È ora di dividere le quote. Ho già i numeri. C'erano quasi 2000 gemme nel baule: 1560 smeraldi, 1032 opali e 363 opali di fuoco. La tua parte è un terzo: 350 smeraldi, 244 opali e 63 opali di fuoco. Ecco, prendili.";
            }
            else
           	{
           	dialog.text = "Bene fatto, "+pchar.name+"! È ora di dividere le quote. Ho già i numeri. C'erano quasi 2000 gemme nel baule: 1050 smeraldi, 732 opali e 189 opali di fuoco. La tua quota è un terzo: 350 smeraldi, 244 opali e 63 opali di fuoco. Ecco, prendili.";
           	}
			link.l1 = "Bene!";
			link.l1.go = "rocur_45";
		break;
		
		case "rocur_45":
			PlaySound("interface\important_item.wav");
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaKamushki"))
			{
				TakeNItems(pchar, "jewelry4", 520);
				TakeNItems(pchar, "jewelry16", 334);
				TakeNItems(pchar, "jewelry14", 121);
			}
			else
			{
				TakeNItems(pchar, "jewelry4", 350);
				TakeNItems(pchar, "jewelry16", 244);
				TakeNItems(pchar, "jewelry14", 63);
			}
            dialog.text = "Ora parliamo del mio debito con te per il mio salvataggio. Capisco che hai avuto spese serie. Quale compensazione considereresti giusta? Sto pagando dalla mia quota di gemme.";
			link.l1 = "Un terzo della tua quota sarà sufficiente. Anche tu hai bisogno di soldi - per comprare e rifornire una nave, per pagare il tuo equipaggio...";
			link.l1.go = "rocur_46";
		break;
		
		case "rocur_46":
			PlaySound("interface\important_item.wav");
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaKamushki"))
			{
				TakeNItems(pchar, "jewelry4", 173);
				TakeNItems(pchar, "jewelry16", 111);
				TakeNItems(pchar, "jewelry14", 40);
			}
			else
			{
				TakeNItems(pchar, "jewelry4", 116);
				TakeNItems(pchar, "jewelry16", 81);
				TakeNItems(pchar, "jewelry14", 21);
			}
            dialog.text = "Grazie amico! Pensavo che non avresti chiesto meno della metà. Ho proprio bisogno di soldi adesso. Ecco, prendi i gioielli.";
			link.l1 = "Che razia Jean! Andiamo verso Hispaniola, da Tyrex.";
			link.l1.go = "rocur_47";
		break;
		
		case "rocur_47":
            DialogExit();
			chrDisableReloadToLocation = false;
			pchar.questTemp.Mtraxx = "merida_gohome";
			AddQuestRecord("Roger_5", "18");
			sld = characterFromId("Mrt_Rocur");
			LAi_SetWarriorType(sld);
			LAi_CharacterDisableDialog(sld); // релиз-правка
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			sld = characterFromId("Lepricon");
			LAi_SetWarriorType(sld);
			LAi_CharacterDisableDialog(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			sld = characterFromId("Terrax");
			sld.dialog.currentnode = "mtraxx_40";
			pchar.quest.mtraxx_merida_lavega.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_lavega.win_condition.l1.location = "Hispaniola1";
			pchar.quest.mtraxx_merida_lavega.function = "Mtraxx_IgnasioKitty";
			// таймер на доплыть домой 40 дней
			SetFunctionTimerCondition("Mtraxx_MeridaReturnLate", 0, 0, 40, false);
			DeleteAttribute(pchar, "GenQuest.HunterLongPause");
		break;
		
		case "rocur_48":
            dialog.text = "Oh, che incontro! Piacere di vederti, "+pchar.name+". Come stai?";
			link.l1 = "Abbastanza bene. Ho trovato i tesori del Lupo Rosso poco fa. Ora mi sto dirigendo a Martinica per incontrare un nostro amico comune. Vuoi vedere Tyrex?";
			link.l1.go = "rocur_49";
		break;
		
		case "rocur_49":
            dialog.text = "Sì. Voglio parlare con lui riguardo a Pasquale Lavoisier. Marcus mi ha mandato da quel mezzo bandito-mezzo mercante. Ho fatto quello che mi ha chiesto e lui ha pagato con della merda sostenendo che fosse un pagamento maledettamente buono. Avrei ucciso quel bastardo proprio dove stava, ma Marcus ha chiesto di trattarlo con rispetto... quindi è lui a dover affrontare questo guaio.";
			link.l1 = "Mi dispiace ma Marcus non farà nulla. Quattro-occhi fa affari con lui.";
			link.l1.go = "rocur_50";
		break;
		
		case "rocur_50":
            dialog.text = "Cosa diamine?";
			link.l1 = "Sì, ma non ti ho parlato di questo, capito? Anche Lavoisier mi ha fregato non molto tempo fa. Tyrex mi ha chiesto di aiutarlo, proprio come ha chiesto a te. Mi hanno avvertito a Isla Tesoro che incrociare i quattro occhi è come incrociare Marcus. Quindi ti suggerisco di dimenticare tutto questo. Non sei né il primo né l'ultimo in questo.";
			link.l1.go = "rocur_51";
		break;
		
		case "rocur_51":
            dialog.text = "Capisco. Quindi anche tu sei stato fregato da quei due, eh?";
			link.l1 = "Beh, sì. Pensavo di creare qualche problema anche al quattro occhi prima di conoscerlo meglio. Non ne vale la pena.";
			link.l1.go = "rocur_52";
		break;
		
		case "rocur_52":
            dialog.text = "Cercheresti di ripagare il bastardo se sapessi che nessuno lo scoprirà mai?";
			link.l1 = "Ah! Certo che lo farei! Anche se non so come. Attacca i flauti di Lavoisier e un giorno luminoso i tuoi marinai si ubriacheranno e spiffereranno tutto. Non sai come funziona?";
			link.l1.go = "rocur_53";
		break;
		
		case "rocur_53":
            dialog.text = "Stai andando a Martinica adesso? Quando arriverai di nuovo a La Vega?";
			link.l1 = "Marcus mi ha dato tre settimane.";
			link.l1.go = "rocur_54";
		break;
		
		case "rocur_54":
            dialog.text = "Cerca di farlo in due. Ci penserò... Trovami nella baia di Gonaives tra 14 giorni. Vai direttamente là, e non entrare a La Vega.";
			link.l1 = "Vedo che stai tramando qualcosa, ah-ah. Va bene. Proverò.";
			link.l1.go = "rocur_55";
		break;
		
		case "rocur_55":
            dialog.text = "Sarebbe meglio che tu lo faccia. Ci vediamo!";
			link.l1 = "...";
			link.l1.go = "rocur_56";
		break;
		
		case "rocur_56":
            DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3", "none", "", "", "", 10.0);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			ReOpenQuestHeader("Roger_4");
			AddQuestRecord("Roger_4", "11");
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1.date.hour  = 1.0;
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 14);
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 14);
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 14);
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l2 = "location";
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l2.location = "Shore34";
			pchar.quest.mtraxx_pasq_gonaiv.function = "Mtraxx_PasqualeJanGonaiv";
			SetFunctionTimerCondition("Mtraxx_PasqualeJanTimer", 0, 0, 10, false); // правки прогона 3
			SetFunctionTimerCondition("Mtraxx_PasqualeJanTimeOver", 0, 0, 15, false);
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			pchar.questTemp.Mtraxx.Pasquale.Grabbing = "true";
		break;
		
		case "rocur_57":
			if (pchar.location.from_sea != "Shore34")
			{
				dialog.text = RandSwear()+"Dove è la tua nave? Sei arrivato qui da La Vega? Merda! Ti ho chiesto di venire qui inosservato e in segreto. Il mio piano è rovinato ora. Accidenti!..";
				link.l1 = "Mh...";
				link.l1.go = "rocur_58";
			}
			if (GetOfficersQuantity(pchar) > 0)
			{
				dialog.text = "Eccoti qua , "+pchar.name+". È bene che tu sia qui. Manda i tuoi compagni indietro alla nave. È una conversazione privata.";
				link.l1 = "Molto bene.";
				link.l1.go = "rocur_59";
			}
			else
			{
				dialog.text = "Eccoti qui , "+pchar.name+". È bene che tu sia qui. Ho un affare per te. Pronto ad ascoltarlo?";
				link.l1 = "Certo!";
				link.l1.go = "rocur_61";
			}
		break;
		
		case "rocur_58":
            DialogExit();
			Group_DelCharacter("RocurSeaGroup", "Mrt_Rocur");
			Group_DeleteGroup("RocurSeaGroup");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "OpenTheDoors", 10.0);
			AddQuestRecord("Roger_4", "14");
			CloseQuestHeader("Roger_4");
		break;
		
		case "rocur_59":
            DialogExit();
			LAi_SetStayType(npchar);
			npchar.dialog.currentnode = "rocur_60";
		break;
		
		case "rocur_60":
            if (GetOfficersQuantity(pchar) > 0)
			{
				dialog.text = "Te l'ho già detto - manda via i tuoi ufficiali!";
				link.l1 = "Sì-sì, ho capito.";
				link.l1.go = "rocur_59";
			}
			else
			{
				dialog.text = "Bene. Ora possiamo parlare liberamente. Ho un affare per te. Pronto ad ascoltare?";
				link.l1 = "Certo!";
				link.l1.go = "rocur_61";
			}
		break;
		
		case "rocur_61":
            dialog.text = "Conosci bene La Vega?";
			link.l1 = "Beh... Credo di sì. Perché chiedi?";
			link.l1.go = "rocur_62";
			npchar.greeting = "";
		break;
		
		case "rocur_62":
            dialog.text = "Hai mai notato il magazzino sulla destra del negozio locale? L'unico grande edificio tra le baracche.";
			link.l1 = "Quella sempre chiusa? Sì, l'ho vista. Che c'è con quella?";
			link.l1.go = "rocur_63";
		break;
		
		case "rocur_63":
            dialog.text = "Hai notato bene - è sempre chiusa. Mentre eri in missione a Martinica, il nostro comune amico Lavoisier è stato qui per tre giorni come ospite di Marcus Tyrex. Hanno trascorso il loro tempo in questa casa a bere rum e divertirsi.";
			link.l1 = "Mh...";
			link.l1.go = "rocur_64";
		break;
		
		case "rocur_64":
            dialog.text = "Allora gli uomini di Lavoisier hanno trascinato alcune scatole e pacchi nella casa. Poi se n'è andato. Per quanto riguarda Marcus, rimane in quel luogo ogni giorno per diverse ore.";
			link.l1 = "Hai dei suggerimenti?";
			link.l1.go = "rocur_65";
		break;
		
		case "rocur_65":
            dialog.text = "Quali suggerimenti? Sono sicuro che questa casa debba essere una base di Lavoisier a La Vega. Non ho visto molto dalla finestra ma ci sono merci stocate lì. Penso che il quattro occhi abbia i mezzi per ripagare ciò che ci deve.";
			link.l1 = "Bene-bene... Vuoi entrare? E la porta chiusa? È pesante e robusta, non c'è modo di entrarci in silenzio.";
			link.l1.go = "rocur_66";
		break;
		
		case "rocur_66":
            dialog.text = ""+pchar.name+", pensi che io sia un idiota? Ho già risolto tutto. Ho realizzato la chiave utilizzando una maschera di cera della serratura. Mi è costato un bel po' di soldi, ma è un mio problema.";
			link.l1 = "Eh! Perché aspettarmi allora?";
			link.l1.go = "rocur_67";
		break;
		
		case "rocur_67":
            dialog.text = "Sarà più sicuro in questo modo, oltre al fatto che sei l'unico di cui mi posso fidare. Una testa è buona, due teste sono meglio, e quattro occhi sono meglio di due.";
			link.l1 = "Ebbene sì, attraversare Lavoisier richiederà tanti occhi quanti ne ha lui, ah-ah-ah! Ma che ne sarà di Tyrex? E se entra in casa mentre stiamo controllando le cose di Pasquale?";
			link.l1.go = "rocur_68";
		break;
		
		case "rocur_68":
            dialog.text = "Non lo farà. È sempre di ritorno a casa sua entro la mezzanotte. Pronto a partire per La Vega la prossima notte? Non capiranno mai chi li ha fottuti: tu sei ancora a Martinica e io ho lasciato La Vega una settimana fa.";
			link.l1 = "Mi piacerebbe fregare quel quattro occhi enculé. Ma dimmi Jean, come si suppone che trasportiamo barili e casse dalla casa?";
			link.l1.go = "rocur_69";
		break;
		
		case "rocur_69":
            dialog.text = "Sono sicuro che troveremo lì oggetti più preziosi di casse e barili con merci, che saranno molto più leggeri. Allora, sei dentro?";
			link.l1 = "Certo che lo sono!";
			link.l1.go = "rocur_70";
		break;
		
		case "rocur_70":
            dialog.text = "Bene, sono contento di non essermi sbagliato su di te. Riposiamoci ora, partiremo per La Vega a mezzanotte.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNight");
		break;
		
		case "rocur_71":
            dialog.text = "È ora di andare. Dovremmo derubare questo bastardo e uscire di lì prima dell'alba.";
			link.l1 = "Avanti!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNightMarch");
			SetLocationCapturedState("LaVega_town", true);
			LAi_LoginInCaptureTown(npchar, true);
		break;
		
		case "rocur_72":
            dialog.text = "Zitto... Ora muoviti, silenziosamente, verso la casa di Pasquale. Seguimi.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNightToHouse");
		break;
		
		case "rocur_73":
            dialog.text = "Guarda questo - c'è roba ovunque. Cominciamo. Controlla un baule vicino alla porta, poi sali al piano di sopra e occupati di una stanza. Io resterò qui: conosco i trucchi per nascondere oggetti di valore tra la roba. Tieni gli occhi e le orecchie aperte e stai lontano dalle finestre.";
			link.l1 = "Bene...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNightInHouse");
		break;
		
		case "rocur_74":
            dialog.text = ""+pchar.name+", cosa hai? Qualcosa di interessante?";
			link.l1 = "Vieni e guarda. Questo è qualcosa.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeJanSeeGirl");
		break;
		
		case "rocur_75":
            dialog.text = "Accidenti! Ora capisco perché Tyrex viene qui ogni giorno. Non è solo il magazzino del quattro occhi, ma anche un bordello.";
			link.l1 = "Sembra che sia una schiava qui.";
			link.l1.go = "rocur_76";
		break;
		
		case "rocur_76":
            dialog.text = "Certo. Guardala - è chiaramente una puttana del porto... Sfortuna per noi. Dobbiamo ucciderla.";
			link.l1 = "Davvero?";
			link.l1.go = "rocur_77";
		break;
		
		case "rocur_77":
            dialog.text = "Ha visto i nostri volti e ha sentito il tuo nome. Dirà tutto a Tyrex.";
			link.l1 = "Mh...";
			link.l1.go = "rocur_78";
		break;
		
		case "rocur_78":
            dialog.text = "È la tua scelta. La sua vita potrebbe costarti la tua.";
			link.l1 = "";
			link.l1.go = "rocur_79";
		break;
		
		case "rocur_79":
            DialogExit();
			sld = characterFromId("Mirabella");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rocur_80":
            dialog.text = "Non pensare nemmeno di fidarti di questa sgualdrina. Domani Tyrex saprà tutto. Vuoi ricevere una marca nera?";
			link.l1 = "No, non lo faccio. E non voglio uccidere la sgualdrina - ho un uso per lei. Verrà con me.";
			link.l1.go = "rocur_81";
		break;
		
		case "rocur_81":
            dialog.text = "Non essere idiota! Scapperà appena ne avrà l'occasione. Guarda la sua fronte, vedi il marchio? È una ladra.";
			link.l1 = "Hm. Probabilmente hai ragione, Jean. Bene, finiscila e andiamo via da qui.";
			link.l1.go = "rocur_82";
			link.l2 = "Non ho intenzione di tenerla sulla mia nave. Ho un posto per lei da cui non scapperà mai, e non ci sono orecchie per sentire le sue grida. Là continuerà a fare il suo mestiere... Una puttana personale, senza alcun costo, he-he!";
			link.l2.go = "rocur_84";
		break;
		
		case "rocur_82":
            DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto6", "", 5);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto7", "Mtraxx_PasqualeJanKillGirl", 5);
		break;
		
		case "rocur_83":
			ChangeCharacterComplexReputation(pchar, "nobility", -10);
            dialog.text = "Ecco, non c'è modo che lei dirà qualcosa a Marcus ora...";
			link.l1 = "Povera ragazza... ah beh come si suol dire, la signora fortuna è una stronza...";
			link.l1.go = "rocur_86";
		break;
		
		case "rocur_84":
            DialogExit();
			sld = characterFromId("Mirabella");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rocur_85":
            dialog.text = "Sei un uomo gentile, "+pchar.name+". Perché vuoi preoccuparti di lei? Ah, vabbè, è la tua scelta. Assicurati che stia zitta mentre stiamo partendo.";
			link.l1 = "Se non sarà - è morta.";
			link.l1.go = "rocur_86";
		break;
		
		case "rocur_86":
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Pasquale.Grabbing.Chest")) sTemp = "A bit. A chest full of doubloons, a handful of rubies, a map of Hispaniola and some rum.";
			else sTemp = "Nothing of value.";
            dialog.text = "Cosa hai trovato?";
			link.l1 = sTemp;
			link.l1.go = "rocur_87";
		break;
		
		case "rocur_87":
			Log_Info("You have received two treasure collections.");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "icollection", 2);
            dialog.text = "Più fortuna dalla mia parte. Prendi la tua parte. Non sarei mai riuscito a portare tutto con me a riva. Il quattro occhi ci ha pagato per intero.";
			link.l1 = "Splendido! Ben fatto, Jean!";
			link.l1.go = "rocur_88";
		break;
		
		case "rocur_88":
            dialog.text = "Ora vai!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNightOutHouse");
		break;
		
		case "rocur_89":
			PlaySound("VOICE\English\LE\Rocur\Rocur_04.wav");
            dialog.text = "Bene. È fatto. Bello e tranquillo. Ora, torniamo alle navi.";
			link.l1 = "Ah, buona idea.";
			link.l1.go = "rocur_89_1";
			//AddDialogExitQuestFunction("Mtraxx_PasqualeNightGulf");
		break;
		
		case "rocur_89_1":
			DialogExit();
			DoFunctionReloadToLocation("shore34", "goto", "goto13", "Mtraxx_PasqualeFinal");
		break;
		
		case "rocur_90":
			PlaySound("VOICE\English\LE\Rocur\Rocur_05.wav");
            dialog.text = "Bene, "+pchar.name+". È tempo che ci separiamo. Non sono sicuro che ci incontreremo mai di nuovo, ma sappi che è stato un piacere conoscerti, amico.";
			link.l1 = "Ah, dai, ci vedremo spesso a La Vega.";
			link.l1.go = "rocur_91";
			SetLocationCapturedState("LaVega_town", false);
			LAi_LoginInCaptureTown(npchar, false);
		break;
		
		case "rocur_91":
            dialog.text = "No. Ho finito con Tyrex. Questo pasticcio con Lavoisier è stata la goccia che ha fatto traboccare il vaso.";
			link.l1 = "Hmm... Capisco, dimenticatelo. Abbiamo ottenuto ciò che era nostro di diritto. Tyrex fornisce piste redditizie, vero? L'ultima volta ho guadagnato più di mezzo milione dal tesoro del Lupo Rosso.";
			link.l1.go = "rocur_92";
		break;
		
		case "rocur_92":
            dialog.text = "Dimmi allora, hai fatto molta fatica per trovarlo?";
			link.l1 = "Bene... Non è stato facile. Ho pensato molto, viaggiato e combattuto. Penso ne sia valsa la pena.";
			link.l1.go = "rocur_93";
		break;
		
		case "rocur_93":
            dialog.text = "Quanto hai pagato a Tyrex?";
			link.l1 = "Un terzo.";
			link.l1.go = "rocur_94";
		break;
		
		case "rocur_94":
            dialog.text = "Qual è stato il suo ruolo in questa faccenda? Cosa ha fatto esattamente Marcus?";
			link.l1 = "Mh... Mi ha dato il registro del Lupo Rosso...";
			link.l1.go = "rocur_95";
		break;
		
		case "rocur_95":
            dialog.text = "E questo è tutto? Giusto?";
			link.l1 = "Beh... Non avrei mai saputo del capitano Wulfric altrimenti...";
			link.l1.go = "rocur_96";
		break;
		
		case "rocur_96":
            dialog.text = ""+pchar.name+", non vedi che Tyrex fa fare agli altri il lavoro sporco? Pensi che ti avrebbe dato il compito di trovare quel tesoro se avesse potuto farlo da solo? Diavolo no! Scommetto che ha provato a farlo prima lui e quando ha fatto un casino, ti ha chiamato per fare il lavoro. E mentre tu pensavi, passando settimane in mare, combattendo e rischiando la tua stessa vita, quel bastardo insieme al suo disgustoso amico quattro occhi si scopavano la puttana a La Vega. E per questo ha anche ottenuto un quarto di milione di pesos. Proprio così\nPensi che abbia mandato il suo cane Leprechaun ad aiutarci nella nostra incursione a Merida? No, voleva assicurarsi che i suoi interessi fossero al sicuro. Tutto ciò che Marcus può fare da solo, lo fa, sia da solo sia con l'aiuto dei Cutlasses, dei Balds, dei Leprechauns e degli altri stupidi idioti che lavorano per lui per pochi spiccioli. Persone come te e io riceviamo informazioni che Marcus è troppo stupido per eseguire da solo\nRicordi tutti i compiti che hai fatto per lui? Conta quanto ha guadagnato su di te. Ne ho abbastanza di tutto questo. Ora ho i soldi, una grande corvetta, e un equipaggio leale... d'ora in poi sono un freelancer. Mi sto dirigendo verso la Giamaica, forse lì riceverò una lettera di corsa.";
			link.l1 = "Non credo che tu abbia proprio ragione su Tyrex... Ma ti auguro fortuna Jean! Spero che tu abbia successo in Jamaica.";
			link.l1.go = "rocur_97";
		break;
		
		case "rocur_97":
            dialog.text = "Lo farò. Buona fortuna anche a te e pensa a quello che ho detto. Essere la pedina di Marcus non è il miglior ruolo per te, so che sei capace di molto di più. Bene... addio fratello! Dio ti accompagni!";
			link.l1 = "Buona caccia, Jean!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeAddComplete");
		break;
		
		case "rocur_98":
            dialog.text = ""+pchar.name+", dimmi, come abbiamo trascorso così tanto tempo nelle giungle? Ora il mio piano è rovinato. Eh... Addio, amico...";
			link.l1 = "Eh...";
			link.l1.go = "rocur_99";
		break;
		
		case "rocur_99":
            DialogExit();
		    LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 10.0);
			sld.lifeday = 0;
			Group_DeleteGroup("RocurSeaGroup");
			AddQuestRecord("Roger_4", "18");
			CloseQuestHeader("Roger_4");
		break;
		
		case "rocur_100":
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaZloVariant"))
			{
				dialog.text = "È ora di andare, ragazzi. Dannazione, Principe, mi hai sorpreso. Hai bruciato un'intera città, ma hai rifiutato di sporcarti le mani quando contava.";
				link.l1 = "Non ho ordinato di bruciare la città!";
				link.l1.go = "rocur_101";
			}
			else
			{
				dialog.text = "È ora di partire, ragazzi. Lucas, te lo sei perso. Il Principe ha gestito tutto brillantemente - e ha fatto un bel guadagno!";
				link.l1 = "E la città, Bello?! Ho dato la mia parola!";
				link.l1.go = "rocur_102";
			}
			sld = CharacterFromID("Lepricon");
			CharacterTurnToLoc(sld, "reload", "reload3");
		break;
		
		case "rocur_101":
            dialog.text = "Almeno non hai cercato di salvarlo. Altrimenti, i nostri uomini ti avrebbero sventrato per primi. È stata una dura giornata per loro. Meritavano di sfogarsi. Ti ci abituerai. Hai tutte le carte in regola per farlo.";
			link.l1 = "Grazie per il consiglio, ma non ricordo di averlo chiesto. Andiamo.";
			link.l1.go = "rocur_103";
		break;
		
		case "rocur_102":
            dialog.text = " Pensavo stessi scherzando. Beh ... sei stato troppo precipitoso. La città è finita. È sempre così quando la Fraternità della Costa si mette al lavoro. Ti ci abituerai.";
			link.l1 = "Non sono sicuro di farlo. Va bene, andiamo.";
			link.l1.go = "rocur_103";
		break;
		
		case "rocur_103":
            DialogExit();
			LAi_SetPlayerType(pchar);
			DeleteAttribute(pchar, "questTemp.lockedMusic");
			EndQuestMovie();
			locCameraTarget(PChar);
			locCameraFollow();
			sld = characterFromId("Tagofa");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			Mtraxx_MeridaCheckOurWarriors();
			AddQuestRecord("Roger_5", "12");
		break;
		
		case "rocur_104":
            dialog.text = "Compagno... cos'era quello appena ora?";
			link.l1 = "Cosa, non hai capito? Ti ho comprato. Una volta hai detto che avevo accesso agli spagnoli, quindi ne ho fatto uso.";
			link.l1.go = "rocur_105";
		break;
		
		case "rocur_105":
            dialog.text = "Ho capito - non sono un idiota. Ma non stavamo lavorando su un piano diverso?";
			link.l1 = "Ebbene, Cutlass ed io abbiamo pensato che non sarebbe stato giusto se fossi finito morto durante una rivolta o un inseguimento, quindi abbiamo deciso di comprarti direttamente.";
			link.l1.go = "rocur_106";
		break;
		
		case "rocur_106":
            dialog.text = "Ehi, non insultarmi. Dopotutto, sono uno dei capitani di Terrax. So come impugnare una lama.";
			link.l1 = "Non dubito di ciò, ma sei davvero turbato per essere libero?";
			link.l1.go = "rocur_107";
		break;
		
		case "rocur_107":
            dialog.text = "No, no - sono grato. È solo che... non era un po' troppo spendere tutto quel oro? Mi sento malato solo a pensarci. Il piantatore, invece, sembrava lucido come un vassoio d'argento lucidato.";
			link.l1 = "Sì, 'L'affare del secolo', infatti. Punge un po', certo. Ma il tempo è più prezioso dell'oro, Jean. Cercando pistole e medicine per tutti voi...";
			link.l1.go = "rocur_108";
		break;
		
		case "rocur_108":
            dialog.text = "Sono grato, ma amico, sei un pazzo - - senza offesa. Ti ho detto che i miei ragazzi non sono grandi con le spade. Ma chiunque può premere un grilletto. Avresti potuto portare qualsiasi pistola e medicina dalla stiva, come con i pugnali e le asce - non sono schizzinosi.";
			link.l1 = "Mmm, onestamente, non ci avevo pensato... Comunque, andiamo - Cutlass probabilmente si sta impazientendo.";
			link.l1.go = "rocur_109";
		break;
		
		case "rocur_109":
			DialogExit();
			DoFunctionReloadToLocation("Shore37", "goto", "goto6", "Mtraxx_PlantPlantVykup_3");
		break;
		
		// Люк Лепрекон
		case "lepricon":
            dialog.text = "Saluti, capitano "+GetFullName(pchar)+". Luke il Leprecauno è al tuo servizio! Mi hanno detto che stiamo andando nelle giungle del Sud Principale.";
			link.l1 = "Esatto. Imbarcatevi sulle lunghe barche, partiamo subito.";
			link.l1.go = "lepricon_1";
		break;
		
		case "lepricon_1":
            dialog.text = "Lascia che un vecchio bucaniere ti dia qualche consiglio, capitano. Poiché ci stiamo dirigendo verso la selva - incontreremo sicuramente gli indiani. Porta con te dei regali per loro. I guerrieri indiani adorano le belle pistole, specialmente quelle da duello. A loro piacciono anche le bussole e i cannocchiali. Li trattano come oggetti magici\nLe loro donne preferiscono gioielli economici e gingilli come specchi e conchiglie. Se ci imbattiamo in una lotta con loro usa tromboni e archibugi: il mitraglio in generale è molto efficace contro i nemici che non indossano armature. Per quanto riguarda l'insediamento stesso, suggerisco armi che possono utilizzare cartucce di carta.";
			link.l1 = "Molto bene, Luke. Le tue parole sono note. Benvenuto a bordo.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_MeridaSail");
		break;
		
		case "lepricon_2":
            dialog.text = "Vedi il capo non appena arriviamo al villaggio. E porta dei doni, altrimenti è inutile. Chiedi se tra la sua gente c'è qualcuno che conosce passaggi segreti nelle giungle avanti, e chiedi per quelli che non hanno paura di viaggiare. Vengo con te, rivolgiti a me in caso incontri difficoltà.";
			link.l1 = "Andiamo! Jean, Luke - seguitemi!";
			link.l1.go = "exit";
			npchar.greeting = "Lepricon_02";
			AddDialogExitQuestFunction("Mtraxx_MeridaSeekVillage");
		break;
		
		case "lepricon_3":
            dialog.text = "Hai delle domande, capitano?";
			link.l1 = "Niente per ora, Luke.";
			link.l1.go = "lepricon_3x";
			if (pchar.questTemp.Mtraxx == "merida_advice")
			{
				link.l1 = "Sì! Ho parlato con il loro capo, gli ho fatto un dono e poi ha convocato i suoi pellirosse per una riunione. Ci sono alcuni tra loro che sanno come arrivare a Merida ma nessuno è disposto ad andare - temono un'altra tribù chiamata Capongs. Questi spaventano a morte i locali. Il bastardo pellirossa sostiene che non abbiamo possibilità di trovare il percorso da soli e che non c'è una guida per noi da assumere. Quindi, cosa dobbiamo fare ora, eh?!";
				link.l1.go = "lepricon_4";
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Merida.Potion") && GetCharacterItem(pchar, "potion3") >= 12)
			{
				link.l2 = "Ho degli antidoti con me.";
				if (GetCharacterItem(pchar, "potion3") > 42) link.l2.go = "lepricon_7";
				else link.l2.go = "lepricon_6";
			}
		break;
		
		case "lepricon_3x":
           DialogExit();
		   npchar.dialog.currentnode = "lepricon_3";
		break;
		
		case "lepricon_4":
            dialog.text = "Hmm, capisco... Capitano, dovresti sapere che la codardia è spesso vinta dall'avidità. Prometti una ricompensa così generosa che un uomo accetterà il lavoro... Sai cosa? Prova un'opzione più astuta - le loro donne. Falle un dono e chiedi dei loro uomini e probabilmente troverai la guida di cui abbiamo bisogno. Prometti a lei cumuli di perline e specchi in cambio dell'aiuto di suo marito. Sii generoso e prometti molto, convincila.";
			link.l1 = "Eh! Beh, il minimo che posso fare è provare, anche se non sono sicuro che funzionerà...";
			link.l1.go = "lepricon_5_1";
			DelLandQuestMark(npchar);
		break;
		
		case "lepricon_5_1":
            dialog.text = "Beh, c'è un'altra opzione... Ma non è esattamente una buona, se capisci cosa intendo.";
			link.l1 = "Un'altra opzione? Dimmelo! Non sono troppo entusiasta di andare dalle donne indiane e supplicarle di convincere i loro mariti a unirsi a noi.";
			link.l1.go = "lepricon_5_2";
		break;
		
		case "lepricon_5_2":
            dialog.text = "Questa opzione è vecchia quanto il tempo. Mostra loro che dovrebbero temerti più di quanto dovrebbero temere i Kapongs. Sai... Potresti dire al capo cosa potrebbero fare i tuoi pirati a tutte le donne del villaggio, specialmente a sua moglie e alle sue figlie. Potresti persino lanciare alcune minacce di torturan\Comunque, sono sicuro che troverai qualcosa per far temere questi indiani. Personalmente, non sono un fan di questa strada, e ci sono ragioni per questo.";
			link.l1 = "Motivi? Quali? Nel mio libro, sembra una soluzione piuttosto efficace e semplice.";
			link.l1.go = "lepricon_5_3";
		break;
		
		case "lepricon_5_3":
            dialog.text = "Per cominciare, non saremo esattamente il fiore all'occhiello della città dopo quello. Potremmo finire per cadere in una trappola o in qualche altra brutta situazione. E in secondo luogo, beh... non mi sembra giusto. È una cosa eliminare avversari armati, ma è un'altra cosa minacciare le donne. Suggerirei di trovare un modo per gestire gli Indiani in modo più... diplomatico.";
			link.l1 = "Capito, ci penserò su. Forse proverò a corteggiare qualche signora con delle perle... O forse inventerò nuovi modi immaginativi per torturare le figlie del capo, haha!";
			link.l1.go = "lepricon_5";
		break;
		
		case "lepricon_5":
            dialog.text = "Un'altra cosa capitano, secondo il capo, potremmo affrontare una tribù ostile di indiani nella giungla, è molto probabile che siano solo un piccolo gruppo di cannibali ma è meglio prevenire che curare. Se è una tribù bellicosa avveleneranno le loro armi, quindi assicurati di fornire ai tuoi uomini degli antidoti\nIo e i miei uomini abbiamo sempre molte pozioni con noi. Per quanto riguarda i tuoi pirati... Portami solo gli antidoti e farò in modo che siano distribuiti tra i tuoi uomini. Ho bisogno di almeno una dozzina di pozioni per questo. Assicurati di portarne anche per te e i tuoi ufficiali.";
			link.l1 = "Bene. Porterò gli antidoti.";
			link.l1.go = "lepricon_5x";
		break;
		
		case "lepricon_5x":
           DialogExit();
		   npchar.dialog.currentnode = "lepricon_3";
		   pchar.questTemp.Mtraxx = "merida_advice2";
		   pchar.questTemp.Mtraxx.Merida.Women = "true";
		   pchar.questTemp.Mtraxx.Merida.Potion = "true";
		   AddQuestRecord("Roger_5", "8");
		   sld = characterFromId("Hayamee");
		   LAi_CharacterEnableDialog(sld);
		   AddLandQuestMark(sld, "questmarkmain");
		  // LocatorReloadEnterDisable("Shore_ship3", "boat", false); 
		   bQuestDisableMapEnter = false;
		   DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");// выпустим в море
		   SetFunctionTimerCondition("Mtraxx_MeridaPotionLate", 0, 0, 10, false); // таймер, чтобы не ходил долго
		break;
		
		case "lepricon_6":
			i = GetCharacterItem(pchar, "potion3");
			RemoveItems(pchar, "potion3", i);
			pchar.questTemp.Mtraxx.Merida.Antidote = i;
            dialog.text = "Molto bene. Dammi. Farò il resto.";
			link.l1 = "Lì...";
			link.l1.go = "lepricon_8";
		break;
		
		case "lepricon_7":
			RemoveItems(pchar, "potion3", 42);
			pchar.questTemp.Mtraxx.Merida.Antidote = 42;
            dialog.text = "Quarantadue pozioni saranno sufficienti. Il resto dovresti tenertelo per te.";
			link.l1 = "Bene...";
			link.l1.go = "lepricon_8";
		break;
		
		case "lepricon_8":
            DialogExit();
		    npchar.dialog.currentnode = "lepricon_3";
			DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Potion");
		break;
		
		case "lepricon_9":
            dialog.text = "Capitano, i tuoi indiani - Hayami e Tagofa hanno aspettato troppo a lungo che tu consegnassi i doni che avevi promesso loro e sono andati in un altro villaggio per ballare e bere kasheeri. Ho la sensazione che il tuo modo di fare affari non ci porterà nulla di buono. Mi dispiace, ma sei fuori da questo. Picard guiderà la spedizione.";
			link.l1 = "Allora, vaffanculo a tutti voi!";
			link.l1.go = "exit";
			AddQuestRecord("Roger_5", "19");
			AddDialogExitQuestFunction("Mtraxx_MeridaHayameeFail");
		break;
		
		case "lepricon_10":
            dialog.text = "Capitano, che diavolo? Abbiamo perso troppo tempo per nulla! Ho l'impressione che il tuo modo di fare affari non ci porterà nulla di buono. Mi dispiace, ma sei fuori da questo. Picard guiderà la spedizione.";
			link.l1 = "Che vi fottano tutti!";
			link.l1.go = "exit";
			AddQuestRecord("Roger_5", "20");
			AddDialogExitQuestFunction("Mtraxx_MeridaHayameeFail");
		break;
		
		case "lepricon_11":
            dialog.text = "Capitano, che diavolo? Avevi dieci giorni per trovare pelle e assi. C'è la città di Maracaibo non lontano da qui! Ho la sensazione che il tuo modo di fare affari non ci porterà nulla di buono. Mi dispiace, ma sei fuori da questo. Picard guiderà la spedizione.";
			link.l1 = "Che vi fottano tutti!";
			link.l1.go = "exit";
			AddQuestRecord("Roger_5", "20");
			AddDialogExitQuestFunction("Mtraxx_MeridaHayameeFail");
		break;
		
		case "lepricon_12":
            dialog.text = "Capitano, mi dispiace, ma avrei dovuto essere a La Vega molto tempo fa, come te in realtà. Devi aver dimenticato dell'esistenza mia e di Marcus. Comunque, me ne vado. Continua a fare quello che stai facendo e spiegherò tutto a Marcus. Addio, è un peccato, pensavo meglio di te.";
			link.l1 = "Hmph...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_MeridaReturnFail");
		break;
		
		case "lepricon_13":
			PlaySound("VOICE\English\LE\Leprikon\Lepricon_03.wav");
            dialog.text = "Allora, per quanto ho capito, voi ragazzi avete avuto una lotta. Non siete riusciti a dividere il bottino, vero Charlie Prince?";
			link.l1 = "Folletto? Sei qui... Non è una grande sorpresa però. Sì, quei bastardi avidi hanno sputato sul Codice e hanno cercato di uccidermi.";
			link.l1.go = "lepricon_14";
			QuestPointerDelLoc("Judgement_dungeon_05", "reload", "reload1");
			QuestPointerDelLoc("Judgement_dungeon_04", "reload", "reload1");
			QuestPointerDelLoc("Judgement_dungeon_03", "reload", "reload1");
			QuestPointerDelLoc("Judgement_dungeon_02", "reload", "reload1");
			QuestPointerDelLoc("Judgement_dungeon_01", "quest", "lepricon");
		break;
		
		case "lepricon_14":
            dialog.text = "Sì, ti hanno dato una bella mazzata, Principe. Sembri come merda bagnata\nCosa hai detto del Codice? Lasciami illuminarti: ho lavorato con Marcus che dovrebbe essere il Custode di questo Codice, ho visto uomini sputare su di esso così tante volte che non oserei contare. Alcuni di questi uomini hanno pagato un prezzo terribile. Alcuni di loro no\nPuoi fare tutto ciò che vuoi, se il premio lo coprirà. Soprattutto se nessuno sta guardando.";
			link.l1 = "Allora... sei qui anche tu per il tesoro?";
			link.l1.go = "lepricon_15";
		break;
		
		case "lepricon_15":
            dialog.text = "Una domanda così stupida. Cos'altro dovrei fare qui, così lontano dalla mia patria Hispaniola? Sebbene dopo tutto sono più intelligente di voi tutti: conoscendo la vostra corrotta natura di pirata. Ho semplicemente aspettato, lasciando che voi topi vi strappiate a vicenda lasciando solo un nemico vivo, ma ferito e stanco.";
			link.l1 = "Nemico? È così che segui il Codice del tuo patrono?! Uccide persone per questo!";
			link.l1.go = "lepricon_16";
		break;
		
		case "lepricon_16":
            dialog.text = "Non sono soggetto al Codice Principe, non sono un pirata. Non possiedo nemmeno una nave - ho dovuto affittare una tinozza per arrivare qui. Non sono altro che un bucaniere in miniatura. Sono un cacciatore, caccio i bufali e preparo il bucan. Dannati Spagnoli che affermano che noi, i bucanieri francesi, roviniamo la loro vita, mi hanno fatto cercare supporto e protezione da Marcus. Lo aiuto nei suoi affari per questo a volte\nAnche se non sono un pirata, io e i miei uomini combattiamo bene, ci avete visto in azione.";
			link.l1 = "Eravamo in raid e combattimenti insieme, Leprechaun. Ci coprivamo le spalle a vicenda, rischiando le nostre vite per salvarne un'altra. È tutto questo solo niente per te?";
			link.l1.go = "lepricon_17";
		break;
		
		case "lepricon_17":
			PlaySound("VOICE\English\LE\Leprikon\Lepricon_04.wav");
            dialog.text = "Sarò onesto con te, Principe: non mi sei mai piaciuto. Sei un arrivista. Un giovanotto insolente, un amante di bevande e donne perdute, che ha fatto qualche lavoro redditizio per Tyrex e si è considerato un grande pirata. \nInoltre, sei un macellaio per natura. Pensi che Cartagena ti abbia dato più peso all'interno dei Fratelli? Ho-ho, oh diavolo no, solo tra i mostri come te.";
			link.l1 = "Oh, questo è esilarante! Ah-ah-ah detto da un vero angelo in persona! Vecchio bastardo!";
			link.l1.go = "lepricon_18";
		break;
		
		case "lepricon_18":
            dialog.text = "Credo che abbiamo chiarito tutto ormai. È tempo di porre fine a questa commedia. I diavoli ti stanno aspettando all'inferno da troppo tempo.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionLepriconFight");
		break;
		
		case "lepricon_19":
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaZapugivanieIndeets"))
			{
				dialog.text = "Ti piace, eh?";
				link.l1 = "Indietro!";
				link.l1.go = "lepricon_20";
			}
			else
			{
				dialog.text = "Ebbene, cosa ne pensi?";
				link.l1 = "Non è divertente, Leprechaun. Che diavolo?! Non ho ordinato un massacro! Non pensi che sia troppo?! Terrax non sarà contento!";
				link.l1.go = "lepricon_24";
			}
		break;
		
		case "lepricon_20":
            dialog.text = "Perché quell'aria di colpevolezza, allora? Non ti diverti? Lascia che ti dica - le cose peggioreranno solo. Pensi che il massacro di oggi sia successo solo perché è quel tipo di giorno? Ah, certo. Questa è la routine. Picard non ha nemmeno battuto ciglio. Per loro, è solo un altro giorno a fare ciò che amano.";
			link.l1 = "E tu? Solo di passaggio?";
			link.l1.go = "lepricon_21";
		break;
		
		case "lepricon_21":
            dialog.text = "Non sono un pirata. E preferirei non aver fatto parte degli eventi di oggi. E... se sei così turbato dalla vista dei corpi delle donne sul terreno annerito di Merida, perché hai agito come hai fatto con gli indiani, Principe?";
			link.l1 = "Cosa avrei dovuto fare? Lasciare tutto e strisciare da Marcus con delle scuse?";
			link.l1.go = "lepricon_22";
		break;
		
		case "lepricon_22":
            dialog.text = "Pensavo solo che l'avessi completamente accettato, che avessi iniziato a pensare e agire come i capitani di Tirax. Ma no, ah! Sei troppo morbido per questo tipo di lavoro. Saresti meglio a dare la tua quota a Marcus e andartene con la coda tra le gambe. Questo non è il tuo mestiere.";
			link.l1 = "Non tocca a te decidere per me, Leprecauno. E certamente non hai il diritto di insultarmi. Non rinuncerò alla mia parte a nessuno. La dividerò equamente con Terrax.";
			link.l1.go = "lepricon_23";
		break;
		
		case "lepricon_23":
            dialog.text = "Certo. Ma sarebbe meglio andarcene prima che tu svenisca.";
			link.l1 = "Non è divertente, dannazione.";
			link.l1.go = "lepricon_30";
		break;
		
		case "lepricon_24":
            dialog.text = "Allora non lo conosci bene. Comunque, dato che gli eventi di oggi non ti portano gioia, ascolta quello che ho da offrirti.";
			link.l1 = "Cosa potresti possibilmente offrire dopo tutto questo?!";
			link.l1.go = "lepricon_25";
		break;
		
		case "lepricon_25":
            dialog.text = "Sarebbe meglio che ti sforzassi di ascoltare, ragazzo.";
			link.l1 = "Mmm, non mi piace il tuo tono, Lucas, ma va bene, vai avanti.";
			link.l1.go = "lepricon_26";
		break;
		
		case "lepricon_26":
            dialog.text = "Posso permettermelo - ho vissuto più di te, Principe. Quindi ho un occhio acuto, non solo per sparare. Vuoi sapere cosa ho notato?";
			link.l1 = "Dillo semplicemente!";
			link.l1.go = "lepricon_27";
		break;
		
		case "lepricon_27":
            dialog.text = "Sei fuori posto. Sì, sei bravo. Stai facendo progressi. Ma solo perché sei un capitano forte, non perché questa è veramente la tua vocazione. Non so come ti sei rivolto a Terrax, o perché, ma credimi, questo non fa per te.";
			link.l1 = "Ho... un obiettivo. Non posso dirti quale sia.";
			link.l1.go = "lepricon_28";
		break;
		
		case "lepricon_28":
            dialog.text = "E sei arrivato più vicino a questo?";
			link.l1 = "Non ancora.";
			link.l1.go = "lepricon_29";
		break;
		
		case "lepricon_29":
            dialog.text = "Ebbene, se nemmeno oggi ti ha avvicinato, non c'è più nulla da guadagnare qui. Sei un bravo ragazzo, Principe. Hai trattato gli indiani come esseri umani. È ironico che tu sia finito qui con noi. Il mio consiglio: dai la tua parte a Terrax per evitare problemi, e tieniti alla larga da tutto questo - salva la tua anima mentre puoi.";
			link.l1 = "Ci penserò su.";
			link.l1.go = "lepricon_30";
		break;
		
		case "lepricon_30":
			DialogExit();
			locCameraFromToPos(21.35, 1.54, 0.05, true, 25.55, 0.46, -0.91);
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaZloVariant"))
			{
				PlaySound("People Fight\PistolShot.wav");
				DoQuestFunctionDelay("Mtraxx_MeridaGorit_5", 2.0);
			}
			else
			{
				DoQuestFunctionDelay("Mtraxx_MeridaGorit_5", 0.5);
			}
		break;
		
		// Тагофа - проводник к Мериде
		case "tagofa":
            dialog.text = "Tagofa ti saluta, figlio del mare. Vuoi che ti mostri la strada per l'insediamento spagnolo tra le montagne?";
			link.l1 = "Corretto. Vedo che sei bravo con la nostra lingua a differenza del resto del tuo popolo.";
			link.l1.go = "tagofa_1";
		break;
		
		case "tagofa_1":
            dialog.text = "Tagofa spesso aveva a che fare con yalanaui... Gran parte del nostro cammino lo percorreremo su un fiume. Avrai bisogno di barche lunghe. Ne hai?";
			link.l1 = "Davvero? Potremmo prenderli in prestito per un po'...";
			link.l1.go = "tagofa_2";
		break;
		
		case "tagofa_2":
            dialog.text = "Il nostro villaggio è piccolo, abbiamo pochissime barche lunghe e tutte sono utili solo per la pesca. Ora, abbiamo bisogno di buone barche lunghe, quelle che resistono a un lungo viaggio, come quelle sulle tue navi.";
			link.l1 = "Hmm... Avremo bisogno di sei barche lunghe allora. La nave non ne ha così tante.";
			link.l1.go = "tagofa_3";
		break;
		
		case "tagofa_3":
            dialog.text = "Costruiscili allora. Voi, gente bianca, potete riparare le vostre enormi navi a terra, sicuramente potete costruire alcune lunghe barche.";
			link.l1 = "Eh, sembra che tu abbia ragione, Tagofa. Portaci al fiume, spero non sia lontano da qui?";
			link.l1.go = "tagofa_4";
		break;
		
		case "tagofa_4":
            dialog.text = "Non lo è. Seguimi.";
			link.l1 = "...";
			link.l1.go = "tagofa_5";
		break;
		
		case "tagofa_5":
           DialogExit();
		   chrDisableReloadToLocation = true;
		   npchar.dialog.currentnode = "tagofa_6";
		   LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Mtraxx_MeridaGotoRiver", 5.0);
		break;
		
		case "tagofa_6":
            dialog.text = "Ecco il fiume di cui ti parlavo. Inizieremo il nostro viaggio da qui. Costruisci le barche e poi cominceremo.";
			link.l1 = "Capito, Tagofa. Ti dirò quando è fatto.";
			link.l1.go = "tagofa_7";
		break;
		
		case "tagofa_7":
            DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.dialog.currentnode = "tagofa_8";
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.questTemp.Mtraxx = "merida_boats";
			pchar.questTemp.Mtraxx.Boats = "true";
			chrDisableReloadToLocation = false;
			DoQuestCheckDelay("TalkSelf_Quest", 2.0);
			// Лепрекона - гулять
			sld = characterFromId("Lepricon");
			sld.dialog.currentnode = "lepricon_3";
			LAi_SetWarriorType(sld);
			LAi_warrior_DialogEnable(sld, true);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			SetFunctionTimerCondition("Mtraxx_MeridaBoatLate", 0, 0, 10, false); // таймер, чтобы не ходил долго
		break;
		
		case "tagofa_8":
            dialog.text = "Le barche sono pronte, capo bianco?";
			link.l1 = "Sì. I miei uomini stanno per salpare.";
			link.l1.go = "tagofa_9";
		break;
		
		case "tagofa_9":
            dialog.text = "Molto bene. Salga sul primo insieme a me. Tagofa mostrerà la strada.";
			link.l1 = "";
			link.l1.go = "tagofa_10";
		break;
		
		case "tagofa_10":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "none", "", "", "Mtraxx_MeridaRiverTrip", -1);
			chrDisableReloadToLocation = true;
		break;
		
		case "tagofa_11":
            dialog.text = "La parte del fiume è finita. Non siamo lontani dall'insediamento spagnolo da qui. C'è il sentiero, attenetevi ad esso e non ci perderemo. Siamo riusciti a girare intorno a una foresta piena di cacciatori Capong, ma anche qui è la loro terra. Dobbiamo stare attenti.";
			link.l1 = "Non preoccuparti. Li spazzeremo via non appena ci mostreranno le loro brutte facce dipinte.";
			link.l1.go = "tagofa_12";
		break;
		
		case "tagofa_12":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.quest.mtraxx_merida_warning.win_condition.l1 = "locator";
			pchar.quest.mtraxx_merida_warning.win_condition.l1.location = "Serpentine2";
			pchar.quest.mtraxx_merida_warning.win_condition.l1.locator_group = "quest";
			pchar.quest.mtraxx_merida_warning.win_condition.l1.locator = "detector1";
			pchar.quest.mtraxx_merida_warning.function = "Mtraxx_MeridaWarning";
			chrDisableReloadToLocation = false;
		break;
		
		case "tagofa_13":
			StartQuestMovie(true, false, true);
            dialog.text = "";
			link.l1 = "Ehi! Tagofa! Guarda! Cos'è quella... al centro del sentiero? Qualche roba indiana.";
			link.l1.go = "tagofa_14";
			locCameraFromToPos(7.63, 9.07, 11.73, true, 2.97, 9.02, 7.70);
			CharacterTurnToLoc(pchar, "quest", "quest1");
		break;
		
		case "tagofa_14":
            DialogExit();
			LAi_SetActorType(pchar);
			LAi_FadeLong("Mtraxx_MeridaWarningCutscene", "");
			locCameraSleep(true);
		break;
		
		case "tagofa_15":
            dialog.text = "È un segno dei Capongs. Un avvertimento. Ti dice di fermarti e non andare oltre. I Capongs ci hanno già individuato.";
			link.l1 = "E se andiamo oltre? Ci attaccheranno?";
			link.l1.go = "tagofa_16";
		break;
		
		case "tagofa_16":
            dialog.text = "Sì, capo bianco. Devi sembrare minaccioso a loro visto che non ci hanno ancora attaccato. Eppure hanno messo un segno per te.";
			link.l1 = "Fanculo al segnale. Stiamo andando avanti... Ascoltate tutti! Alle armi! Preparatevi! Siate all'erta! Se questi selvaggi ci mostrano le loro brutte facce, li uccideremo tutti!";
			link.l1.go = "tagofa_17";
		break;
		
		case "tagofa_17":
            DialogExit();
			EndQuestMovie();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.quest.mtraxx_merida_capong.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_capong.win_condition.l1.location = "Merida_jungle_01";
			pchar.quest.mtraxx_merida_capong.function = "Mtraxx_MeridaPrepareCapongAttack";
		break;
		
		case "tagofa_18":
            dialog.text = "Il capo bianco e i suoi uomini hanno schiacciato i capongas, Tagofa è impressionato. La città spagnola è vicina. C'è una valle dove vedrai una cascata. Tagofa non andrà dagli spagnoli. Ti aspetterò vicino alla cascata.";
			link.l1 = "Molto bene. Avanti!";
			link.l1.go = "tagofa_19";
		break;
		
		case "tagofa_19":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			chrDisableReloadToLocation = false;
			pchar.quest.mtraxx_merida_exittown.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_exittown.win_condition.l1.location = "Merida_ExitTown";
			pchar.quest.mtraxx_merida_exittown.function = "Mtraxx_MeridaExitTown";
			Mtraxx_MeridaCheckOurWarriors();
			AddQuestRecord("Roger_5", "15");
		break;
		
		case "tagofa_20":
            dialog.text = "Siamo tornati, capo bianco. Tagofa ha fatto quello che ha promesso.";
			link.l1 = "Grazie, Tagofa. Hai fatto bene.";
			link.l1.go = "tagofa_21";
		break;
		
		case "tagofa_21":
            dialog.text = "Tagofa dovrebbe andare. Hayami mi sta aspettando molto. Addio figlio del mare.";
			link.l1 = "Buona fortuna figlio della selva. Saluta tua moglie per me. E grazie per averci aiutato.";
			link.l1.go = "tagofa_22";
		break;
		
		case "tagofa_22":
            DialogExit();
			chrDisableReloadToLocation = false;
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.quest.mtraxx_merida_final.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_final.win_condition.l1.location = "Shore_ship3";
			pchar.quest.mtraxx_merida_final.function = "Mtraxx_MeridaFinal";
			ChangeIndianRelation(7.0);
		break;
		
		// дозорный у Мериды
		case "merida_guard":
            dialog.text = "Ehi! Chi sei e cosa vuoi?";
			link.l1 = "Dobbiamo arrivare a Merida e fare una chiacchierata con il tuo governatore o chiunque tu abbia al suo posto...";
			link.l1.go = "merida_guard_1";
		break;
		
		case "merida_guard_1":
            dialog.text = "Non permettiamo a estranei di entrare a Merida. Vattene!";
			link.l1 = "Amico, abbiamo remato duramente per due giorni e poi combattuto orde di indiani per non andarcene così. Ripeto, voglio parlare con il capo del vostro villaggio! Abbiamo una... proposta di affari per lui, sì! E se siamo tutti d'accordo, il vostro villaggio rimarrà intatto.";
			link.l1.go = "merida_guard_2";
		break;
		
		case "merida_guard_2":
            dialog.text = "Stai minacciando ladro?";
			link.l1 = "Come hai capito questo? Ah sì infatti, sto facendo minacce. O otteniamo ciò per cui siamo qui in pace o con la forza, e tu hai l'onore di decidere il destino del tuo villaggio.";
			link.l1.go = "merida_guard_3";
		break;
		
		case "merida_guard_3":
            dialog.text = "Non entrerai mai a Merida, maledetto pirata! Allarme! Nemico alle porte!";
			link.l1 = "Un tale signore irragionevole...";
			link.l1.go = "merida_guard_4";
		break;
		
		case "merida_guard_4":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "none", "", "", "", 10.0);
			DoQuestFunctionDelay("Mtraxx_MeridaHouseGuards", 5.0);
		break;
		
		// мэр Мериды
		case "merida_head":
            dialog.text = "Maledetti ladri! Cosa volete da noi?! Questo è un piccolo, modesto insediamento. Non abbiamo né oro né argento! Come avete fatto a scoprire di noi?";
			link.l1 = "Oh, non fingere di essere innocente e ignaro, Sua Eccellenza. Il mondo intero è già pieno di voci sulle tue opali.";
			link.l1.go = "merida_head_1";
		break;
		
		case "merida_head_1":
            dialog.text = "E hai causato questo massacro senza dio per... voci?! Non hai risparmiato nessuno! Bestie... Sappiate questo: i depositi sono lontani da qui. Non c'è nulla da guadagnare qui. Andatevene.";
			link.l1 = "Hai iniziato tu questo massacro senza Dio. I civili hanno combattuto al fianco dei tuoi soldati. Non crederò mai che un tale eroismo insensato sia possibile solo per proteggere qualche muro spoglio.";
			link.l1.go = "merida_head_2";
		break;
		
		case "merida_head_2":
            dialog.text = "Sai quanto sforzo è stato impiegato per costruire queste mura? Non abbiamo assunto costruttori esterni - le abbiamo costruite noi stessi, mattone su mattone. Ogni singolo residente. Anche io, con queste stesse mani.";
			link.l1 = "Una storia così toccante... E i mobili? Li avete fatti anche voi? Che bella sedia intagliata. E il tavolo. E gli armadi. È quercia tinta? O ebano? Un po' troppo lussuoso per un 'insediamento modesto', non credi?";
			link.l1.go = "merida_head_3";
		break;
		
		case "merida_head_3":
            dialog.text = "La bramosia ha offuscato la tua mente, ladro.";
			link.l1 = "Non c'è bisogno di complicare le cose, Signor Governatore. O te ne pentirai.";
			link.l1.go = "merida_head_4";
		break;
		
		case "merida_head_4":
            dialog.text = "Mi stai per torturare, maledetto pirata? Peccato per te - io credo in Dio Onnipotente. E ascenderò come un martire se esageri.";
			link.l1 = "Uh-m...";
			link.l1.go = "merida_head_5";
		break;

		case "merida_head_5":
			StartInstantDialog("Mrt_Rocur", "merida_head_6", "Quest\Roger.c");
		break;
		
		case "merida_head_6":
            dialog.text = "Amico mio, non parlerà in questo modo. Lascia che me ne occupi io.";
			link.l1 = "Oh?";
			link.l1.go = "merida_head_7";
		break;
		
		case "merida_head_7":
            dialog.text = "Ricordo tutto quello che quei presuntuosi spagnoli mi hanno fatto in quella piantagione maledetta. Sarei felice di mostrartelo, Principe. E ti racconterò anche qualche storia. Non ti annoierai.";
			link.l1 = "E se ti lasci trasportare?";
			link.l1.go = "merida_head_8";
		break;
		
	case "merida_head_8":
            dialog.text = "Non parlerà gentilmente. Conosco il suo tipo.";
			if (IsCharacterPerkOn(pchar, "Trustworthy") && sti(pchar.reputation.nobility) >= 50 && GetSummonSkillFromName(pchar, SKILL_Leadership) >= 50)
			{
				link.l1 = "(Affidabile) (Onore) (Leadership) Basta sangue per oggi, Jean. Me ne occuperò io stesso.";
				link.l1.go = "merida_head_dobro_1";
				notification("Trustworthy", "Trustworthy");
				notification("Reputation Check Passed", "None");
				notification("Skill Check Passed", SKILL_Leadership);
			}
			else
			{
				if (!IsCharacterPerkOn(pchar, "Trustworthy")) notification("Perk Check Failed", "Trustworthy");
				if (sti(pchar.reputation.nobility) < 50) notification("Reputation Too Low! ("+XI_ConvertString(GetReputationName(50))+")", "None");
				if (GetCharacterSkill(pchar, SKILL_LEADERSHIP) < 50) notification("Skill Check Failed (50)", SKILL_LEADERSHIP);
			}
			link.l2 = "Fallo. Non mi sto coinvolgendo. E non sto neanche guardando.";
			link.l2.go = "merida_head_zlo_1";
		break;
		
		case "merida_head_zlo_1":
            dialog.text = "Se non fossi in debito con te, avrei un paio di parole scelte per te... Dannazione. Vai avanti. Ora è il momento del vero lavoro.";
			link.l1 = "Non sforzarti troppo.";
			link.l1.go = "rocur_42";
		break;
		
		case "merida_head_dobro_1":
            dialog.text = "Come desideri, amico mio. Sarà divertente guardare.";
			link.l1 = "Non sorridere troppo presto.";
			link.l1.go = "merida_head_dobro_2";
		break;
		
		case "merida_head_dobro_2":
			StartInstantDialog("Merida_Head", "merida_head_dobro_3", "Quest\Roger.c");
		break;
		
		case "merida_head_dobro_3":
            dialog.text = "Dici che te la caverai da solo, senza spargimento di sangue, maledetto ladro? Non c'è nulla che tu possa dire per far apparire pietre dal nulla!";
			link.l1 = "meglio che compaiano, Governatore. Altrimenti, raseremo al suolo la città e uccideremo tutti tranne te. Non mi piace questa soluzione, ma sono disposto a compromettere il mio onore per la mia causa. Il tuo dovere, invece, è proteggere i civili, i soldati sopravvissuti e i lavoratori di Merida. O preferiresti 'ascedere come un martire' a costo della loro sofferenza? Non mi sembra molto divino.";
			link.l1.go = "merida_head_dobro_4";
		break;
		
		case "merida_head_dobro_4":
            dialog.text = "Maledizione a te...\nLì... nel baule. Risparmia solo la gente del paese!";
			if (GetSummonSkillFromName(pchar, SKILL_Sneak) >= 50)
			{
				link.l1 = "(Furtivo) C'è tutto nel baule?";
				link.l1.go = "merida_head_dobro_vnimatelnost_1";
				notification("Skill Check Passed", SKILL_Sneak);
			}
			else
			{
				link.l1 = "Mantengo la mia parola. Addio, Governatore.";
				link.l1.go = "merida_head_dobro_5";
				notification("Skill Check Failed (50)", SKILL_SNEAK);
			}
		break;
		
		case "merida_head_dobro_vnimatelnost_1":
            dialog.text = "Maledetto all'inferno!\nIl baule ha anche un falso fondo. Prendi tutto!!";
			link.l1 = "...";
			link.l1.go = "merida_head_dobro_vnimatelnost_2";
			pchar.questTemp.Mtraxx_MeridaKamushki = true;
		break;
		
		case "merida_head_dobro_vnimatelnost_2":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto2", "Mtraxx_MeridaOpenChest", -1);
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
		break;
		
		case "merida_head_dobro_vnimatelnost_3":
            dialog.text = "Liscio, Principe. Mi dispiace per averti sottovalutato.";
			link.l1 = "Soddisfatto?";
			link.l1.go = "merida_head_dobro_7";
		break;
		
		case "merida_head_dobro_5":
			StartInstantDialog("Mrt_Rocur", "merida_head_dobro_6", "Quest\Roger.c");
		break;
		
		case "merida_head_dobro_6":
            dialog.text = "Liscio, Principe.";
			link.l1 = "Soddisfatto?";
			link.l1.go = "merida_head_dobro_7";
		break;
		
		case "merida_head_dobro_7":
            dialog.text = "More than. But... you'll see for yourself. You go ahead; I'll dig around a little more.";
			link.l1 = "...";
			link.l1.go = "rocur_43";
		break;
		
		/*case "merida_head_99999":
            DialogExit();
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto2", "Mtraxx_MeridaGiveJewelry", -1);
		break;*/
		
		case "merida_head_sleep":
            dialog.text = "Hai promesso di lasciare la città una volta ottenute le gemme... Ora le hai e i tuoi ladri hanno incendiato le nostre case! Sei un bugiardo e un malvagio pirata! Spero che le fiamme dell'inferno saranno così ardenti per te!!!";
			link.l1 = "";
			link.l1.go = "exit";
			locCameraFromToPos(19.18, 1.28, -0.28, true, 24.88, 1.62, -1.19);
			AddDialogExitQuest("Mtraxx_RetributionSleep2");
		break;
		
		// капитан пинаса Китти
		case "kittycap":
            dialog.text = TimeGreeting()+", gentile signore. Qual è il tuo scopo qui?";
			link.l1 = "Sono da Tyrex. Mi è stato detto di scortare la vostra nave a Bridgetown. Siete pronti?";
			link.l1.go = "kittycap_1";
		break;
		
		case "kittycap_1":
            dialog.text = "Beh, finalmente! Sì, il mio equipaggio è pronto a salpare immediatamente!";
			link.l1 = "Splendido. Prepara le vele capitano. Mettiamoci in viaggio!";
			link.l1.go = "kittycap_2";
		break;
		
		case "kittycap_2":
		    DialogExit();
            LAi_CharacterDisableDialog(npchar);
			Group_DelCharacter("Mtr_Kitty", "Mtr_KittyCap");
			SetCharacterRemovable(npchar, false);
			npchar.CompanionEnemyEnable = false; //всегда друзья
			LAi_SetImmortal(npchar, false);
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.loyality = MAX_LOYALITY;
		    pchar.quest.mtraxx_ignasio_sail.win_condition.l1 = "location";
			pchar.quest.mtraxx_ignasio_sail.win_condition.l1.location = "Bridgetown_town";
			pchar.quest.mtraxx_ignasio_sail.function = "Mtraxx_IgnasioArrive";
			SetFunctionTimerCondition("Mtraxx_IgnasioTimeOver", 0, 0, 30, false);
			pchar.quest.mtraxx_ignasio_sinkkitty.win_condition.l1 = "NPC_Death";
			pchar.quest.mtraxx_ignasio_sinkkitty.win_condition.l1.character = "Mtr_KittyCap";
			pchar.quest.mtraxx_ignasio_sinkkitty.function = "Mtraxx_IgnasioKittySink";
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		break;
		
		case "kittycap_3":
            dialog.text = "Grazie per avermi aiutato, capitano! Con te al mio fianco ero al sicuro come se fossi dietro le mura del forte.";
			link.l1 = "Eh, non menzionarlo amico! Tutto è su Marcus. Buona fortuna a te compagno!";
			link.l1.go = "kittycap_4";
		break;
		
		case "kittycap_4":
            DialogExit();
			npchar.lifeday = 0;
			RemoveCharacterCompanion(pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 30.0);
			Mtraxx_IgnasioCreateMarko();
			AddCharacterExpToSkill(pchar, "Sailing", 200);
		break;
		
		// Игнасио Марко
		case "ignasio":
            PlaySound("Voice\English\LE\Ignasio_Marko\Ignasio_01.wav");
			dialog.text = "Saluti al coraggioso capitano! Lascia che mi presenti - un corsaro d'Inghilterra, Ignacio Marco del Torero.";
			link.l1 = TimeGreeting()+", amico. Capitano "+GetFullName(pchar)+" al vostro servizio. Come posso aiutarvi?";
			link.l1.go = "ignasio_1";
		break;
		
		case "ignasio_1":
            PlaySound("Voice\English\LE\Ignasio_Marko\Ignasio_02.wav");
			dialog.text = "Oh, ti conosco! Monseniour "+GetFullName(pchar)+"! Voci sulle tue risorse e sui tuoi protettori mi sono giunte da tutto l'Arcipelago. Credo che la mia offerta sarà molto interessante per te.";
			link.l1 = "Quale offerta?";
			link.l1.go = "ignasio_2";
		break;
		
		case "ignasio_2":
            dialog.text = "Andiamo in una taverna per bere qualcosa. Ti dirò tutto. Non è una conversazione da strada.";
			link.l1 = "Molto bene... Andiamo!";
			link.l1.go = "ignasio_3";
		break;
		
		case "ignasio_3":
            DialogExit();
			FreeSitLocator("Bridgetown_tavern", "sit_front2");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "Bridgetown_tavern", "sit", "sit_front2", "Mtraxx_IgnasioInTavern", -1);
		break;
		
		case "ignasio_4":
			LAi_SetSitType(pchar);
            dialog.text = "Un giro, capitano?";
			link.l1 = "Certo!";
			link.l1.go = "ignasio_5";
		break;
		
		case "ignasio_5":
			LAi_Fade("", "");
            dialog.text = "Ehi, qui in realtà non mescolano il rum con l'acqua...";
			link.l1 = "E non trattare i clienti con pesce marcio, sì-sì. Allora, qual è il problema?";
			link.l1.go = "ignasio_6";
		break;
		
		case "ignasio_6":
            dialog.text = "Mi piace la tua franchezza, signore. Dimmi, sei a conoscenza della guerra commerciale tra gli inglesi e gli olandesi?";
			link.l1 = "Sono. Ho avuto il piacere di prenderne parte.";
			link.l1.go = "ignasio_7";
		break;
		
		case "ignasio_7":
            PlaySound("Voice\English\LE\Ignasio_Marko\Ignasio_02.wav");
			dialog.text = "Non c'è bisogno di spiegare allora. Essendo un corsaro inglese, sto combattendo questa guerra dalla loro parte. Tu sei per lo più un freelancer. Il che ti rende indifferente su quale lato combattere...";
			link.l1 = "Quasi. Non tradisco la Francia, mi dispiace.";
			link.l1.go = "ignasio_8";
		break;
		
		case "ignasio_8":
            dialog.text = "Certo, capitano! Allora, dritto al punto: c'è una piccola isola abitata tra Curacao e Trinidad, non è sulle mappe... Da poco tempo, direi molto recentemente, gli olandesi hanno iniziato a usarla come fermata temporanea per rifornirsi e riparare. Sembra che credano che solo loro siano a conoscenza di questa isola. Sbagliato. He-he\nUn paio di giorni fa una carovana d'argento è stata colpita da una... tempesta, e ora gli olandesi stanno riparando le loro navi su quest'isola. La nave ammiraglia ha perso il suo albero maestro, quindi ci vorrà del tempo per ripararlo. Gli olandesi sono impegnati con le riparazioni, e gli equipaggi sono per lo più dispersi sull'isola...";
			link.l1 = "E poi, all'improvviso, ci presentiamo per salvare la situazione?";
			link.l1.go = "ignasio_9";
		break;
		
		case "ignasio_9":
            dialog.text = "Esattamente, capitano. Non posso farlo da solo, ma con te - è una storia completamente diversa. Sarai disposto a rischiare? Ho una grande nave, l'equipaggio è ottimo e ho una buona quantità di esperienza. Le tue abilità... sono lodevoli.";
			link.l1 = "Quanto tempo abbiamo?";
			link.l1.go = "ignasio_10";
		break;
		
		case "ignasio_10":
            dialog.text = "Molto, se non lo stiamo sprecando e ci mettiamo subito in viaggio.";
			link.l1 = "Allora riforniamoci di munizioni e armi, capitano Ignacio Marco, e mettiamo le vele. Quali sono le coordinate esatte dell'isola?";
			link.l1.go = "ignasio_11";
		break;
		
		case "ignasio_11":
            dialog.text = "12'40 Nord, 64'11 Ovest. Capito?";
			if (CheckAttribute(pchar, "questTemp.HWIC.Isladecoche")) link.l1 = "Ah! Déjà vu... Capito.";
			else link.l1 = "Capito.";
			link.l1.go = "ignasio_12";
		break;
		
		case "ignasio_12":
            dialog.text = "In rotta verso il 'Torero'. Ti aspetterò, capitano!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioAddMarko");
		break;
		
		case "ignasio_13":
            PlaySound("Voice\English\LE\Ignasio_Marko\Ignasio_03.wav");
			dialog.text = "Inferno di una lotta, vero, capitano? Ora la parte piacevole: dividiamo le nostre quote. Metà va a me e ai miei uomini.";
			link.l1 = "Molto bene, facciamolo...";
			link.l1.go = "ignasio_14";
		break;
		
		case "ignasio_14":
			LAi_Fade("", "");
			WaitDate("", 0, 0, 0, 3, 10); 
			pchar.questTemp.Mtraxx.Silver = GetSquadronGoods(pchar, GOOD_SILVER)-sti(pchar.questTemp.Mtraxx.Silver);
			pchar.questTemp.Mtraxx.Mahogany = GetSquadronGoods(pchar, GOOD_MAHOGANY)-sti(pchar.questTemp.Mtraxx.Mahogany);
			if (sti(pchar.questTemp.Mtraxx.Silver) < 100)
			{
				dialog.text = "Capitano, che succede? Dov'è il nostro argento? Hai affondato il nostro premio?";
				if (sti(pchar.questTemp.Mtraxx.Mahogany) < 200) 
				{
					link.l1 = "Mh...";
					link.l1.go = "ignasio_15_1";
				}
				else
				{
					link.l1 = "L'argento è stato sprecato in qualche modo, anche se abbiamo ottenuto un po' di sequoia. Dividiamolo.";
					link.l1.go = "ignasio_15_11";
				}
				break;
			}
			if (sti(pchar.questTemp.Mtraxx.Silver) < 300 && sti(pchar.questTemp.Mtraxx.Silver) > 100)
			{
				dialog.text = "Mh.. Questo è scarso. Pensavo che ce ne fosse di più.";
				link.l1 = "Abbiamo quello che abbiamo.";
				link.l1.go = "ignasio_15_2";
				break;
			}
			if (sti(pchar.questTemp.Mtraxx.Silver) < 700 && sti(pchar.questTemp.Mtraxx.Silver) > 300)
			{
				dialog.text = "Non male, non male. Anche se, pensavo ce ne fossero di più.";
				link.l1 = "Abbiamo quello che abbiamo.";
				link.l1.go = "ignasio_15_3";
				break;
			}
            dialog.text = "Ben fatto, Monseniour. Questo è un bel bottino...";
			link.l1 = "Non posso non essere d'accordo con te su questo, capitano.";
			link.l1.go = "ignasio_15_4";
		break;
		
		case "ignasio_15_1":
			dialog.text = "Sembra che tu abbia un grosso problema con la testa. Stiamo partendo! Ragazzi!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_15_11":
			RemoveCharacterGoods(pchar, GOOD_MAHOGANY, makeint(sti(pchar.questTemp.Mtraxx.Mahogany)/2));
			dialog.text = "Almeno otteniamo qualcosa da questo... Ragazzi! Andiamo!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_15_2":
			RemoveCharacterGoods(pchar, GOOD_SILVER, makeint(sti(pchar.questTemp.Mtraxx.Silver)/2));
			RemoveCharacterGoods(pchar, GOOD_MAHOGANY, makeint(sti(pchar.questTemp.Mtraxx.Mahogany)/2));
            dialog.text = "È qualcosa. Prendiamo strade separate.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_15_3":
            RemoveCharacterGoods(pchar, GOOD_SILVER, makeint(sti(pchar.questTemp.Mtraxx.Silver)/2));
			RemoveCharacterGoods(pchar, GOOD_MAHOGANY, makeint(sti(pchar.questTemp.Mtraxx.Mahogany)/2));
            dialog.text = "È qualcosa. Separiamo le nostre strade. È un successo dopo tutto, eh!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_15_4":
			RemoveCharacterGoods(pchar, GOOD_SILVER, makeint(sti(pchar.questTemp.Mtraxx.Silver)/2));
			RemoveCharacterGoods(pchar, GOOD_MAHOGANY, makeint(sti(pchar.questTemp.Mtraxx.Mahogany)/2));
            dialog.text = "Abbiamo avuto un incontro molto proficuo. Forse, non è l'ultima volta che facciamo affari insieme, capitano!";
			link.l1 = "Chiamami se trovi altri mercanti grassi, he-he!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_boarding":
			PlaySound("Voice\English\LE\Ignasio_Marko\Ignasio_04.wav");
            dialog.text = "Presumo che non sia un caso, capitano?";
			link.l1 = "Non saresti intelligente se non lo vedessi. Mi devi per l'organizzazione. Sai di cosa sto parlando. Inoltre, mi devi per aver organizzato il mio amico Jean Picard. È stato venduto a una piantagione dopo il tuo piano... Hai perso Ignacio. Sto per impiccarti, ma puoi alleviare la tua punizione...";
			link.l1.go = "ignasio_boarding_1";
		break;
		
		case "ignasio_boarding_1":
            dialog.text = "Mi chiedo addirittura - cosa potrei fare per farti provare pietà di me?";
			link.l1 = "Mi serve informazione. Ti metterò nella mia stiva dove parleremo del tuo programma a L'Avana...";
			link.l1.go = "ignasio_boarding_2";
		break;
		
		case "ignasio_boarding_2":
            dialog.text = RandSwear()+" Non me lo aspettavo! Nemmeno ci pensare. Barbazon scoprirà il mio tradimento in men che non si dica. È meglio per te non sapere cosa fa a chi lo tradisce. L'ho visto.";
			link.l1 = "Allora essere impiccato è un'opzione migliore?";
			link.l1.go = "ignasio_boarding_3";
		break;
		
		case "ignasio_boarding_3":
            dialog.text = "Preferirei morire in combattimento!";
			link.l1 = "...";
			link.l1.go = "ignasio_boarding_4";
		break;
		
		case "ignasio_boarding_4":
            DialogExit();
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "spy_sailor":
            dialog.text = "Capitano! Capitano! Affrettati! La squadra militare spagnola ci sta inseguendo!";
			link.l1 = RandSwear()+"Me lo aspettavo... La stessa storia è capitata a Picard. Hai visto quanti erano là fuori?";
			link.l1.go = "spy_sailor_1";
		break;
		
		case "spy_sailor_1":
            dialog.text = "Sì, capitano. Tre navi. La loro nave ammiraglia è un galeone, il più grande che abbia mai visto e si muove velocemente, le altre due sono una corvetta e una xebec.";
			link.l1 = "Tutti a bordo. Potremmo ancora essere in grado di fuggire.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioOurEscape");
		break;
		
		// индей-кариб в гроте Порто-Белло
		case "grot_canib":
            dialog.text = "Ehi! Dannato yalanaui, è entrato nella nostra foresta! Uccidilo! Ehi!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekGrotFight");
		break;
		
		// бандит у пещеры Панамы
		case "cave_bandit":
            dialog.text = "Ehi! Che diavolo stai facendo qui? Ah-ah, rubando le cose altrui? Beh, sei nei guai!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekCaveFight");
		break;
		
		case "carpenter":
            dialog.text = "Ehi! Tutti fermi lì! O vi porterò tutti via con una raffica di mitraglia! "+RandSwear()+"";
			link.l1 = "Non ci stiamo muovendo da nessuna parte ora. Ma ascolta amico - non c'è modo che tu ci uccida tutti con un solo colpo. Alcuni di noi ti taglieranno a pezzi mentre stai ricaricando. Sarebbe meglio parlare proprio ora.";
			link.l1.go = "carpenter_1";
			locCameraFromToPos(-71.57, 14.57, -130.20, true, -63.78, 11.36, -125.50);
		break;
		
		case "carpenter_1":
            dialog.text = "Sei tu il capo qui? Rispondimi!";
			link.l1 = "Sono il capitano "+GetFullName(pchar)+". E tu devi essere il secondo in comando del Lupo Rosso mentre lui è lontano da qui, ho ragione?";
			link.l1.go = "carpenter_2";
		break;
		
		case "carpenter_2":
            dialog.text = "Cosa stai facendo qui capitano "+GetFullName(pchar)+"Non invitiamo ospiti in questo posto!";
			link.l1 = "Qual è il tuo nome? Voglio sapere con chi sto parlando.";
			link.l1.go = "carpenter_3";
		break;
		
		case "carpenter_3":
            dialog.text = "Mi chiamo Rodgar Janssen.";
			link.l1 = "Vedo che siete proprio al buio, ragazzi. Non avete più un capitano. E la vostra corvetta è sparita pure. La 'Freyja' è stata maledettamente bombardata dagli spagnoli non lontano da Hispaniola. Il suo equipaggio è stato massacrato fino all'ultimo...";
			link.l1.go = "carpenter_4";
		break;
		
		case "carpenter_4":
            dialog.text = RandSwear()+" Wulfric... Aahhh-ghhhhh!!! ... Ma come posso sapere che stai dicendo la verità?";
			link.l1 = "Ho il diario del tuo ex capitano! Abbiamo recuperato alcuni oggetti dal relitto di Freyja. Grazie al diario sono riuscito a trovare quest'isola e questo... tuo gordes.";
			link.l1.go = "carpenter_5";
		break;
		
		case "carpenter_5":
            dialog.text = "Ehi! Mi devi ancora una risposta: perché sei qui in questa terra sconosciuta?";
			link.l1 = "Non mentirò, amico. Dicono che il Lupo Rosso possedesse una fortuna considerevole. Sono qui per trovarla visto che nessun tesoro è stato trovato sulla sua nave. Credo che dovrebbe appartenere alla gente comune, tanto a Wulfric non serve più.";
			link.l1.go = "carpenter_6";
		break;
		
		case "carpenter_6":
            dialog.text = "Ah! Amico, sto per deluderti: né io né nessun altro dell'equipaggio ha mai visto i tesori del Lupo. Era troppo rischioso chiederglielo.";
			link.l1 = "Allora probabilmente dovrei cercarli nel tuo villaggio. Toglierai la tua pistola o dovrò iniziare a stormire il villaggio? Non hai speranze Rodgar. Porterò pistole e più uomini se ne avrò bisogno.";
			link.l1.go = "carpenter_7";
		break;
		
		case "carpenter_7":
            dialog.text = "Prima di morire, porteremo un bel po' di voi bastardi all'inferno! Forse anche tu!";
			link.l1 = "Sei sicuro? Non hai un capitano, né una nave e nessuno verrà a salvarti. Anche se me ne vado, presto morirete tutti di fame!";
			link.l1.go = "carpenter_8";
		break;
		
		case "carpenter_8":
            dialog.text = "Mhmm... hai qualche suggerimento?";
			link.l1 = "Sì, lo faccio. Fai un passo indietro dal cannone e tieni sotto controllo i tuoi uomini. Giuro che non farò del male a te o ai tuoi uomini. Se vuoi, puoi unirti al mio equipaggio o ti porteremo in qualche civiltà.";
			link.l1.go = "carpenter_9";
		break;
		
		case "carpenter_9":
            dialog.text = "Giuralo davanti ai tuoi uomini, forte e chiaro!";
			link.l1 = "Lo giuro! Hai la mia parola: tu e i tuoi uomini non subirete alcun danno.";
			link.l1.go = "carpenter_10";
		break;
		
		case "carpenter_10":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_11";
			LAi_SetActorType(npchar);
			LAi_ActorDialog(npchar, pchar, "", -1, 0);
			for (i=1; i<=2; i++) // 
			{
				sld = CharacterFromID("Islamona_fort_pirate_"+i);
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
		break;
		
		case "carpenter_11":
            dialog.text = "Spero che manterrai la tua parola, capitano.";
			link.l1 = "Lo faccio sempre. Quanti di voi sono rimasti?";
			link.l1.go = "carpenter_12";
		break;
		
		case "carpenter_12":
            dialog.text = "Vedi tutti noi. Tre. Gli altri sono morti nelle giungle attaccandoti. Gli ho detto di non farlo, ma non hanno ascoltato...";
			link.l1 = "Capisco...";
			link.l1.go = "carpenter_13";
		break;
		
		case "carpenter_13":
            dialog.text = "La cibo stava finendo. Abbiamo iniziato a cacciare i pappagalli. La 'Freyja' era assente da troppo tempo. Avevamo i nostri sospetti e si sono avverati.";
			link.l1 = "Grazie a Dio per aver deciso di andare a caccia del tesoro. Dove pensi che li abbia nascosti?";
			link.l1.go = "carpenter_14";
		break;
		
		case "carpenter_14":
            dialog.text = "Te l'ho già detto: nessuno li ha mai visti. Wulfric era attento con la sua parte, non l'ha mai sprecata. Era giusto con noi, ma chiunque abbia cercato di trovare il suo tesoro è scomparso. Sei libero di cercare nel villaggio se lo desideri.";
			link.l1 = "Questo è il mio piano. Dove si trova la casa del Lupo Rosso?";
			link.l1.go = "carpenter_15";
		break;
		
		case "carpenter_15":
            dialog.text = "L'unico edificio a due piani che abbiamo qui.";
			link.l1 = "Bene. A proposito, qual è la tua occupazione?";
			link.l1.go = "carpenter_16";
		break;
		
		case "carpenter_16":
			worldMap.labels.islamona.icon = 5;
			worldMap.labels.islamona.text = CheckingTranslate(LanguageOpenFile("LocLables.txt"),"Islamona");
            dialog.text = "Sono un falegname e questi due sono i miei assistenti. Prima riparavamo e sistemavamo la 'Freyja'. Potremmo essere utili nel tuo equipaggio.";
			link.l1 = "Capisco. Molto bene, sei dentro, parleremo dei dettagli dopo. Prendi questa pistola all'entrata. E Rodgar, non lasciare il villaggio mentre sto cercando il nascondiglio.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekInFort");
		break;
		
		case "carpenter_17":
            dialog.text = "Ordini, capitano?";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.WolfreekGord"))
			{
				link.l1 = "Sì. I tesori del tuo capitano sono stati trovati. Li ha nascosti bene ma io l'ho superato in astuzia!";
				link.l1.go = "carpenter_18";
				break;
			}
			// Jason Исла Мона -->
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "start")
			{
				link.l1 = "Rodgar, cosa ne pensi, c'è qualcos'altro che possiamo fare con questa base?";
				link.l1.go = "IslaMona";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "get_tools")
			{
				link.l1 = "Rodgar, ho portato gli attrezzi. Dovrebbero essere già stati consegnati a te.";
				link.l1.go = "IslaMona_8";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "himenes")
			{
				link.l1 = "Benvenuto! Questo è Rodrigo Jimenez, il capo di una piccola ma molto laboriosa comunità di Cadiz. Il signor Jimenez ha gentilmente accettato di stabilirsi temporaneamente nella nostra terra e di aiutarci con la costruzione.";
				link.l1.go = "IslaMona_12";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "nextday")
			{
				link.l1 = "Rodgar, come stai? Hai qualche buon consiglio per me?";
				link.l1.go = "IslaMona_18";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "stalk")
			{
				link.l1 = "Rodgar, ho bisogno di un favore.";
				link.l1.go = "IslaMona_20";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "dublon_wait" && GetCharacterItem(pchar, "gold_dublon") >=600)
			{
				link.l1 = "Ti ho portato i dobloni, solo non sprecarli tutti subito in alcol.";
				link.l1.go = "IslaMona_24";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "storage" && !CheckAttribute(pchar, "questTemp.IslaMona.Food") && IslaMona_CheckFood())
			{
				link.l1 = "Rodgar, controlla il magazzino. Ho portato i medicinali e le provviste.";
				link.l1.go = "IslaMona_30";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "village")
			{
				link.l1 = "Ciao, Rodgar, come vanno le cose nel nuovo insediamento?";
				link.l1.go = "IslaMona_32";
				break;
			}
			if (!CheckAttribute(npchar, "quest.stalk")) // ремонт кораблей
			{
				link.l2 = "Rodgar, la mia nave ha bisogno di riparazioni. Tu e i tuoi ragazzi siete pronti?";
				link.l2.go = "repair";
			}
			link.l3 = "Rodgar, vorrei lasciare una delle mie navi qui.";
			if (CheckAttribute(npchar, "portman.info")) link.l3.go = "shipstock";
			else link.l3.go = "shipstock_info";
			if (CheckAttribute(npchar, "portman") && sti(npchar.portman > 0))
			{
				link.l4 = "Rodgar, vorrei riprendere una delle mie navi.";
				link.l4.go = "shipstockreturn";
			}
			if (!CheckAttribute(npchar, "storadge"))
			{
				link.l5 = "Guarda, c'è qualche edificio vuoto che potrei usare come magazzino?";
				link.l5.go = "storadge";
			}
			if (CheckAttribute(npchar, "storadge"))
			{
				link.l5 = "Rodgar, voglio vedere un magazzino.";
				link.l5.go = "storadge_3";
			}
			if (CheckAttribute(npchar, "crew"))
			{
				link.l6 = "Rodgar, voglio lasciare una parte della squadra sull'isola.";
				link.l6.go = "crew";
			}
			if (CheckAttribute(npchar, "crew") && sti(npchar.crew.qty) > 0)
			{
				link.l7 = "Rodgar, voglio portare i miei marinai con me di nuovo al mare.";
				link.l7.go = "crew_3";
			}// <-- Исла Мона
			link.l99 = "Nulla ancora...";
			link.l99.go = "carpenter_exit";
		break;
		
		case "Crew":
			DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			LaunchHireCrew();
		break;
		
		case "carpenter_exit":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
		break;
		
		case "carpenter_18":
            dialog.text = "Congratulazioni cap. Cosa facciamo dopo? Stiamo partendo?";
			link.l1 = "Sei qui da molto tempo?";
			link.l1.go = "carpenter_19";
		break;
		
		case "carpenter_19":
            dialog.text = "Da troppo tempo. È passato un anno da quando Wulfric mi ha messo al comando qui.";
			link.l1 = "Ho deciso che questa base segreta è troppo buona per essere sprecata. Il villaggio è mio ora. Posso lasciare te e i tuoi uomini qui se vuoi. Rum, provviste, medicine - tutto vostro.";
			link.l1.go = "carpenter_20";
		break;
		
		case "carpenter_20":
            dialog.text = "Sarebbe fantastico capitano. Mi sono abituato alla vita su questa spiaggia, su quest'isola.";
			link.l1 = "Splendido. A proposito, qual è il nome dell'isola?";
			link.l1.go = "carpenter_21";
		break;
		
		case "carpenter_21":
            dialog.text = "Isla Mona.";
			link.l1 = "Isla Mona... Forse un giorno costruiremo più case e strutture qui... Ma più tardi. Per ora manterrai lo stesso ruolo qui ma sotto un nuovo capitano.";
			link.l1.go = "carpenter_22";
		break;
		
		case "carpenter_22":
            dialog.text = "Affare. Basta che tu stia attento, capitano, e non dimenticare di fornirci provviste.";
			link.l1 = "Certo Rodgar. Buona fortuna, dovrei navigare verso La Vega.";
			link.l1.go = "carpenter_exit";
			npchar.portman = 0;
			AddDialogExitQuestFunction("Mtraxx_WolfreekComplete");
		break;
		//------------------------------------------------------------ Исла Мона ------------------------------------
		case "IslaMona":
			sTemp = "";
			if (GetCharacterIndex("Mirabella") != -1) sTemp = ", not accounting for your woman";
            dialog.text = "È difficile a dirsi, Cap. Il defunto Wulfric non ha mai lasciato più di due dozzine di persone qui. Al momento, siamo solo in tre,"+sTemp+". Non c'è molto che possiamo fare.";
			link.l1 = "Vuoi dire che se qui vivessero più persone, potresti trasformare questo posto in un vero e proprio insediamento?";
			link.l1.go = "IslaMona_1";
		break;
		
		case "IslaMona_1":
            dialog.text = "L'isola è piccola, quindi non puoi costruire una colonia su di essa, ma un insediamento è del tutto possibile! Puoi pescare, cacciare uccelli e capre, raccogliere frutti. Possiamo sostenerci, ma non ci arricchiremo con esso.\nMa c'è una cosa che non capisco del tutto, Cap. Perché ne hai bisogno?";
			link.l1 = "Questa è la mia casa e la mia terra, il mio popolo. Che cosa divento se non me ne prendo cura?";
			link.l1.go = "IslaMona_2_1";
			link.l2 = "Voglio investire soldi in un'attività che valga la pena.";
			link.l2.go = "IslaMona_2_2";
			link.l3 = "Questa piccola isola è proprio nel cuore di questa regione. Sarebbe saggio trasformarla in una base militare a pieno titolo e segreta.";
			link.l3.go = "IslaMona_2_3";
			link.l4 = "Mi preoccupo per te, Rodgar, tutti voi siete completamente fuori di testa a questo punto.";
			link.l4.go = "IslaMona_2_4";
		break;
		
		case "IslaMona_2_1":
            dialog.text = "Sei uno strano. Beh, non importa. Almeno ci sarà qualcosa da fare...";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
			AddCharacterExpToSkill(pchar, "Defence", 2000);//защита
		break;
		
		case "IslaMona_2_2":
            dialog.text = "Sei uno strano. Beh, non importa. Almeno ci sarà qualcosa da fare...";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
			AddCharacterExpToSkill(pchar, "Commerce", 1500);//торговля
		break;
		
		case "IslaMona_2_3":
            dialog.text = "Sei uno strano. Beh, non importa. Almeno ci sarà qualcosa da fare...";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
			AddComplexSelfExpToScill(250, 250, 250, 250);//оружие
		break;
		
		case "IslaMona_2_4":
            dialog.text = "Sei uno strano. Beh, non importa. Almeno ci sarà qualcosa da fare...";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
			AddCharacterExpToSkill(pchar, "Leadership", 1000);//авторитет
		break;
		
		case "IslaMona_3":
            dialog.text = "Prima di tutto, dovrai trovare individui molto speciali. Coloro che potrebbero essere persuasi a trasferirsi in questa selvaggia per viverci e lavorarci per anni, in completa isolamento dal mondo esterno. Questo è il tipo di persone speciali che dovrai cercare. Sperabilmente, non solo uno. Dopotutto, non puoi ordinare al tuo equipaggio di vivere qui, almeno non ancora. I coloni non vorrebbero lasciare le loro case stabilite e lavori stabili. E noi non abbiamo bisogno di vagabondi e altri inadatti qui da noi. \nInoltre, il problema della segretezza che circonda questa isola sarà sempre presente. Se lo dici a qualcuno, ci sarà immediatamente la minaccia di cacciatori che cercano di indagare.";
			link.l1 = "Capisco, hai dei suggerimenti?";
			link.l1.go = "IslaMona_4";
		break;
		
		case "IslaMona_4":
            dialog.text = "No, Capitano. Sono stato qui per troppo tempo e ho completamente perso contatto con la vita civilizzata.";
			link.l1 = "Ottimo, è di aiuto!";
			link.l1.go = "IslaMona_5";
		break;
		
		case "IslaMona_5":
            dialog.text = "Lavoro con il legno, non con le persone. E ne sono molto contento, ah-ah! A proposito, oltre alle persone, dovrai portare anche un set di attrezzi da forgia e da costruzione di alta qualità qui. Si producono solo nella vecchia Europa, quindi ti costeranno un bel po'. Chiedi ai proprietari dei cantieri navali, quelli più grandi.";
			link.l1 = "Tutto è chiaro. Riassumiamo: se voglio trasformare questa base in qualcosa di più grande, devo riportare qui più coloni e attrezzi?";
			link.l1.go = "IslaMona_6";
		break;
		
		case "IslaMona_6":
            dialog.text = "È corretto!";
			link.l1 = "Vedrò cosa posso fare.";
			link.l1.go = "IslaMona_7";
		break;
		
		case "IslaMona_7":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			AddQuestRecord("IslaMona", "1");
			pchar.questTemp.IslaMona = "tools";
			IslaMona_SelectShipyard();
		break;
		
		case "IslaMona_8":
            dialog.text = "Già, Capitano! Un set di prim'ordine, siamo pronti a costruire una colonia! È stato costoso?";
			link.l1 = "Mi è costato una fortuna, spero davvero ne sia valsa la pena!";
			link.l1.go = "IslaMona_9_1";
			link.l2 = "Un paio di anni fa, avrei detto che era molto costoso. Ma adesso... non lo so nemmeno.";
			link.l2.go = "IslaMona_9_2";
		break;
		
		case "IslaMona_9_1":
			AddCharacterExpToSkill(pchar, "Commerce", 600);
            dialog.text = "Non potevi accontentarti di quello che già avevi, vero? In ogni caso, preparati a vedere le tue spese aumentare sempre di più. Hai risolto il problema con i coloni?";
			link.l1 = "No, Rodgar. Non ho ancora capito dove trovarli. Dopotutto, non ho i diritti sovrani per stabilire insediamenti in queste acque.";
			link.l1.go = "IslaMona_10";
		break;
		
		case "IslaMona_9_2":
			AddCharacterExpToSkill(pchar, "Leadership", 300);
            dialog.text = "Non potevi accontentarti di quello che avevi già, vero? In ogni caso, preparati a vedere le tue spese aumentare. Hai risolto il problema con i coloni?";
			link.l1 = "No, Rodgar. Non ho ancora capito dove trovarli. Dopo tutto, non ho i diritti sovrani per stabilire insediamenti in queste acque.";
			link.l1.go = "IslaMona_10";
		break;
		
		case "IslaMona_10":
            dialog.text = "In queste acque, Capitano, regna il caos ogni giorno. Ascolta ciò che la gente dice, potresti scorgere un'opportunità nascosta. Io mi occuperò degli strumenti per ora.";
			link.l1 = "Bene, starò all'erta per quel tipo di informazioni.";
			link.l1.go = "IslaMona_11";
		break;
		
		case "IslaMona_11":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			AddQuestRecord("IslaMona", "3");
			RemoveItems(pchar, "islamona_toolbox", 1);
			pchar.questTemp.IslaMona = "rumours";
			AddRumor("They say some criminals have been cast out to one of the uninhabited islands! It seems they're such fierce monsters that even the executioner and the holy fathers wouldn't want to deal with them! But why do they always bring such people to us?!", 1, "all", "none", 0, (2022 - STARTGAME_YEAR) * 365, "IslaMona_TerksRumour", "none");
		break;
		
		case "IslaMona_12":
            dialog.text = "Spagnoli? Devi scherzare, capitano. Pensavo che avresti portato degli oziosi da Le Francois, non questi...";
			link.l1 = "";
			link.l1.go = "IslaMona_13";
		break;
		
		case "IslaMona_13":
            DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_18";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "IslaMona_14":
            dialog.text = "Sei dall'Europa? Hehe, non è difficile capirlo. Non preoccuparti, ti ci abituerai.";
			link.l1 = "Jimenez, rimarrai a casa mia per un po'. C'è una cantina là, tanto spazio. Rodgar, ho portato gli attrezzi, e anche i coloni. Cosa c'è dopo?";
			link.l1.go = "IslaMona_15";
		break;
		
		case "IslaMona_15":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_20";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "IslaMona_16":
            dialog.text = "Ci vediamo domani, Capitano. Parleremo tra un giorno, una volta che questi... coloni si sistemano con i loro tesori..";
			link.l1 = "Bene, continueremo domani.";
			link.l1.go = "IslaMona_17";
		break;
		
		case "IslaMona_17":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			LAi_SetWarriorType(npchar);
			IslaMona_HimenesWait();
		break;
		
		case "IslaMona_18":
            dialog.text = "Capitano, parla con lo spagnolo. È già completamente impegnato nel suo lavoro.";
			link.l1 = "Capito, lo farò.";
			link.l1.go = "IslaMona_19";
			link.l2 = "C'è qualcosa che non va?";
			link.l2.go = "IslaMona_18_1";
		break;
		
		case "IslaMona_18_1":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
            dialog.text = "Capitano, sono rimasto con i ragazzi qui per alcuni anni. Ora, l'attività frenetica degli spagnoli mi sta sulle nervature.";
			link.l1 = "Niente conflitti! E vi proibisco, a te e ai tuoi uomini, di guardare anche solo in direzione delle loro donne! Almeno, per ora... Se le cose si fanno accese, prendi una scialuppa e vai... a pescare per un paio di giorni.";
			link.l1.go = "IslaMona_18_2";
		break;
		
		case "IslaMona_18_2":
            dialog.text = "Sì, sì, signore!";
			link.l1 = "Perfetto. Bene, andrò a vedere cosa sta combinando.";
			link.l1.go = "IslaMona_19";
		break;
		
		case "IslaMona_19":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			IslaMona_SetHimenesNextDay();
		break;
		
		case "IslaMona_20":
            dialog.text = "Lo so già, Capitano. Lo spagnolo vuole che esploriamo l'isola? Saltare sulle rocce con una mappa come un branco di idioti?";
			link.l1 = "È corretto, Rodgar.";
			link.l1.go = "IslaMona_21";
		break;
		
		case "IslaMona_21":
            dialog.text = "Seicento dobloni e lo farò.";
			link.l1 = "Sei impazzito? Sei stato morso da un ragno locale o da un serpente velenoso? Cosa farai con un baule pieno d'oro su un'isola disabitata? Lo seppellirai?";
			link.l1.go = "IslaMona_22";
		break;
		
		case "IslaMona_22":
            dialog.text = "Su, Capitano. Un giorno lasceremo questo posto, e chi avrà bisogno di noi nel grande mondo senza monete? Certo, abbiamo una piccola scorta nascosta, ma non è quasi abbastanza. Wulfric non ha mai saldato i suoi debiti con me e i ragazzi per le sue ultime imprese.\nÈ una cosa oziare sulla spiaggia per mesi e servire la tua flotta una volta ogni sei mesi. Ma lavorare duramente sulla terraferma ogni giorno, come un maledetto bucaniere - questa è tutta un'altra storia! Questo è un lavoro, e i lavori pagano. Tu paghi il tuo equipaggio, vero, Capitano?";
			link.l1 = "Sembra ragionevole. Ti procurerò i 600 dobloni. Spero tu non ti aspetti il pagamento in anticipo, vero?";
			link.l1.go = "IslaMona_23";
			link.l2 = "Ho un'altra proposta. Tu lavori sulla terra, non gratti le balene dalle navi in mare. Al momento, abbiamo un disperato bisogno di quel tipo di lavoro.";
			link.l2.go = "IslaMona_25";
		break;
		
		case "IslaMona_23":
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			AddCharacterExpToSkill(pchar, "Leadership", 500);
			AddQuestRecord("IslaMona", "7");
            dialog.text = "Capitano, sono pronto a iniziare subito, ma i miei uomini lavoreranno molto più duramente quando vedranno i dobloni nelle loro mani. Prometto che non lasceremo un singolo pezzo di terra inesplorata su quest'isola.";
			if (PCharDublonsTotal() >= 600)
			{
				link.l1 = "Bene. Ecco il tuo oro. Semplicemente non sprecarlo subito per bere.";
				link.l1.go = "IslaMona_24";
			}
			else
			{
				link.l1 = "Bene, ti porterò i tuoi dobloni.";
				link.l1.go = "IslaMona_24_1";
			}
		break;
		
		case "IslaMona_24_1":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			pchar.questTemp.IslaMona = "dublon_wait";
		break;
		
		case "IslaMona_24":
			RemoveDublonsFromPCharTotal(600);
			Log_Info("You gave away 600 doubloons");
			PlaySound("interface\important_item.wav");
            dialog.text = "Ha-ha! Hai ragione, Capitano! Oh, e quasi me ne ero dimenticato. Ora ci sono molte persone che vivono qui, e hanno bisogno di qualcosa da mangiare. Hai visto quelle signore? Non sono abituate alla sopravvivenza e a nutrirsi della terra. Non saranno d'aiuto.";
			link.l1 = "Solo non dirmi che dovrò trovare altri bucanieri per aiutarti.";
			link.l1.go = "IslaMona_26";
		break;
		
		case "IslaMona_25":
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			ChangeCharacterComplexReputation(pchar, "authority", 5);
			pchar.questTemp.IslaMona.Nodublon = "true"; // дублоны не заплатил
			AddQuestRecord("IslaMona", "8");
            dialog.text = "Sì-sì, Capitano! Siamo pronti a lavorare sulla terra! Ah, e un'altra cosa, quasi l'ho dimenticata. Ora qui vivono parecchie persone, e hanno bisogno di qualcosa da mangiare. Hai visto quelle signore? Non sono abituate alla sopravvivenza e a nutrirsi della terra. Non saranno d'aiuto.";
			link.l1 = "Solo non dirmi che dovrò cercare anche dei bucanieri per aiutarti.";
			link.l1.go = "IslaMona_26";
		break;
		
		case "IslaMona_26":
            dialog.text = "No, perché dovremmo? Addestreremo e prepareremo i più capaci tra loro per il sostentamento. Ma fino a quel meraviglioso momento, dovrai fornirci del cibo. Un paio di migliaia di set di provviste navali saranno sufficienti. E un quintale di medicine per il futuro. Scarica tutto questo dalle navi nel nostro magazzino sull'isola.";
			link.l1 = "Certo. Quanto tempo ti serve per la missione di ricognizione?";
			link.l1.go = "IslaMona_27";
		break;
		
		case "IslaMona_27":
            dialog.text = "Concluderemo in due o tre giorni, abbiamo già trovato alcune cose interessanti.";
			link.l1 = "Ottimo!";
			link.l1.go = "IslaMona_28";
		break;
		
		case "IslaMona_28":
            dialog.text = "Non appena finiamo, vai direttamente da quel spagnolo che ride. Il pazzo deve trarre conclusioni dal nostro lavoro.";
			link.l1 = "Vedo che siete quasi amici già. Lo visiterò tra tre giorni allora. Beh, al lavoro. Buona fortuna a tutti noi!";
			link.l1.go = "IslaMona_29";
		break;
		
		case "IslaMona_29":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			npchar.quest.stalk = "true";
			AddQuestRecord("IslaMona", "9");
			pchar.questTemp.IslaMona = "storage";
			SetFunctionTimerCondition("IslaMona_StalkFin", 0, 0, 3, false);
		break;
		
		case "IslaMona_30":
            dialog.text = "Wow! Grazie, Capitano. Ora abbiamo tempo per preparare le signore a questa vita folle nella selvaggina.";
			link.l1 = "Sii solo attento a non farne dei pirati! Grazie, Rodgar";
			link.l1.go = "IslaMona_31";
		break;
		
		case "IslaMona_31":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			pchar.questTemp.IslaMona.Food = "true";
			AddQuestRecord("IslaMona", "10");
			IslaMona_RemoveFood();
		break;
		
		case "IslaMona_32":
            dialog.text = "Capitano! Devo dire, ho iniziato a sentirmi piuttosto a disagio a vivere qui.";
			link.l1 = "Perché è così, Rodgar? Ti manca il fascino della povertà e della rovina?";
			link.l1.go = "IslaMona_33";
		break;
		
		case "IslaMona_33":
            dialog.text = "Potresti dire così. Ora la civiltà sta raggiungendo anche qui. E persone come me non hanno posto in essa.";
			link.l1 = "Compra un jabot e un bastone. Ti integrerai perfettamente.";
			link.l1.go = "IslaMona_34";
		break;
		
		case "IslaMona_34":
            dialog.text = "Piuttosto, andiamo a vedere il tuo spagnolo e discutiamo i risultati del ricognizione. Ho un'altra idea pazza...";
			link.l1 = "Ho appena parlato con lui! Va bene, andiamo, Rodgar.";
			link.l1.go = "IslaMona_37";
			link.l2 = "Ti piace lavorare con lui?";
			link.l2.go = "IslaMona_35";
		break;
		
		case "IslaMona_35":
            dialog.text = "Persone altamente istruite e laboriose! E Jimenez è veramente un maestro. Ai vecchi tempi, si poteva ottenere una buona quantità d'oro per persone così. E le loro ragazze sono belle, anche...";
			link.l1 = "Non ne voglio sentire parlare, Rodgar! Andiamo a parlare con quel nostro padrone";
			link.l1.go = "IslaMona_36_1";
			link.l2 = "Se non riescono a gestire il lavoro, li venderemo. Ma teniamo le ragazze, ah-ah! Andiamo a vedere il padrone.. ";
			link.l2.go = "IslaMona_36_2";
		break;
		
		case "IslaMona_36_1":
			ChangeCharacterComplexReputation(pchar, "nobility", 6);
            dialog.text = "Sul serio, Capitano? Stavo solo scherzando, andiamo...";
			link.l1 = "";
			link.l1.go = "IslaMona_37";
		break;
		
		case "IslaMona_36_2":
			ChangeCharacterComplexReputation(pchar, "nobility", -6);
            dialog.text = "Sapevo che mi avresti sostenuto, Capitano! Andiamo...";
			link.l1 = "";
			link.l1.go = "IslaMona_37";
		break;
		
		case "IslaMona_37":
            DialogExit();
			DoQuestReloadToLocation("IslaMona_TwoFloorHouse", "goto", "goto5", "IslaMona_HouseDialog");
		break;
		
		case "IslaMona_38":
            dialog.text = "Non sta ridendo, cap...";
			link.l1 = "";
			link.l1.go = "IslaMona_39";
		break;
		
		case "IslaMona_39":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_48";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_40":
            dialog.text = "Anche quello, cap. Ne parleremo più tardi...";
			link.l1 = "";
			link.l1.go = "IslaMona_41";
		break;
		
		case "IslaMona_41":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_52";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_42":
            dialog.text = "Il signore ha ragione, Capitano. Nessuno di noi si spezzerà la schiena nella giungla. L'affare può essere sporco, ma non farai di questo posto altro che un nido di pirati in nessun altro modo.";
			link.l1 = "";
			link.l1.go = "IslaMona_43";
		break;
		
		case "IslaMona_43":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_58";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_44":
            dialog.text = "Captain, when you build the factory, the slaves will need protection. My guys will take care of that. One of them even shoots like Thor with lightning. Nothing motivates work like a hunting scope. We already have one gun; now we need a second. Any musket will do.";
			link.l1 = "";
			link.l1.go = "IslaMona_45";
		break;
		
		case "IslaMona_45":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_60";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_46":
            dialog.text = "E i miei ragazzi avranno bisogno della stessa quantità di oro e un'altra dozzina di bottiglie di buon rum.";
			link.l1 = "Quanta legna potrai fornire in ogni lotto? E perché hai bisogno d'oro?";
			link.l1.go = "IslaMona_47";
		break;
		
		case "IslaMona_47":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_62";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_48":
            dialog.text = "Ebbene, prima di tutto, la vita senza svago è priva di significato, e presto anche i pii, hehe, cattolici inizieranno a scalare le pareti. E in secondo luogo, se c'è una taverna sull'isola, potrai lasciare parte dell'equipaggio qui in attesa. Vedi, convincere la gente a vivere come selvaggi gratuitamente in capanne sulla spiaggia per un intero anno è piuttosto difficile. Ma se c'è un insediamento con una taverna, cibo caldo, musica e intrattenimento nelle vicinanze... Cos'altro ha bisogno un marinaio durante una licenza a terra?";
			link.l1 = "Puttane?";
			link.l1.go = "IslaMona_49";
			link.l2 = "Bevande?";
			link.l2.go = "IslaMona_49";
		break;
		
		case "IslaMona_49":
            dialog.text = "Hai ragione, ma risolviamo i problemi uno alla volta. Prima, ricostruiremo la tua casa...";
			link.l1 = "...";
			link.l1.go = "IslaMona_50";
		break;
		
		case "IslaMona_50":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_65";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_51":
            dialog.text = "Non ci ha nemmeno pensato, cap.";
			link.l1 = "Grazie, Rodgar. Capisco che ora riuscirò a servire più navi in questa piccola baia, giusto?";
			link.l1.go = "IslaMona_52";
		break;
		
		case "IslaMona_52":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_harbour_4";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_53":
            dialog.text = "Saluti, Capitano! Sei venuto a discutere del lavoro?";
			link.l1 = "No, per niente. Mi mancava solo la tua fisionomia settentrionale.";
			link.l1.go = "IslaMona_54";
		break;
		
		case "IslaMona_54":
            dialog.text = "Andiamo a fare una passeggiata? Ti mostrerò la tua fabbrica.";
			link.l1 = "Guida la strada.";
			link.l1.go = "IslaMona_55";
		break;
		
		case "IslaMona_55":
            DialogExit();
			IslaMona_PlantationGo();
		break;
		
		case "IslaMona_56":
            dialog.text = "H-hic! Cap, stiamo festeggiando!";
			link.l1 = "Rodgar! Rodrigo! Accidenti!";
			link.l1.go = "IslaMona_57";
		break;
		
		case "IslaMona_57":
            dialog.text = "Cosa c'è che non va, c-c-capitano? Non ti piace il colore delle pareti?";
			link.l1 = "Proprio ora mi sono reso conto che voi due condividete lo stesso nome! Ah-ah-ah! Uno spagnolo e un pirata, con lo stesso nome, hanno costruito una taverna su un'isola deserta e bevono insieme come se gli dei indiani divoreranno tutti e finiranno il mondo all'alba! Ah-ah! Sono con voi!";
			link.l1.go = "IslaMona_58";
		break;
		
		case "IslaMona_58":
            dialog.text = "Ah-ah-ah! È vero! Salute!";
			link.l1 = "Salute!";
			link.l1.go = "IslaMona_59";
		break;
		
		case "IslaMona_59":
            DialogExit();
			npchar.dialog.currentnode = "IslaMona_60";
			IslaMona_ReloadTavern();
		break;
		
		case "IslaMona_60":
            dialog.text = "Vuoi bere, cap?";
			link.l1 = "Stai diventando un oste, Rodgar?";
			link.l1.go = "IslaMona_61";
		break;
		
		case "IslaMona_61":
            dialog.text = "Temporaneamente! Agli spagnoli piace particolarmente avere un pirata che si occupa del bar - questa è la vera esotica e avventura per loro. Ma nel complesso, è bello qui. Se decidi di lasciare una parte del tuo equipaggio in riserva in questo insediamento, fammelo sapere - lo organizzerò.";
			link.l1 = "Dove vivranno però?";
			link.l1.go = "IslaMona_62";
		break;
		
		case "IslaMona_62":
            dialog.text = "Semplice - costruiremo delle capanne sulla spiaggia. In questo modo, correranno dalla taverna alla riva. Solo un promemoria, quest'isola non può ospitare più di trecento persone, quindi tienilo a mente per il futuro. A volte ti chiederemo di portare rum e vino, quindi sarebbe fantastico se tu, Capitano, potessi stoccare le merci nel magazzino in anticipo.";
			link.l1 = "Ricorderò questo. Allora, compagno. Intrattieni gli Spagnoli e prenditi una pausa. Solo per favore, non bere fino a quando l'intero villaggio brucia - Non potrei sopportare la vista di questo!";
			link.l1.go = "IslaMona_63";
		break;
		
		case "IslaMona_63":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			//LocatorReloadEnterDisable("IslaMona_TwoFloorHouse", "reload1", false);
			//LocatorReloadEnterDisable("IslaMona_TwoFloorHouse", "reload3", false);
			npchar.crew = "true"; // можно оставлять матросов
			npchar.crew.qty = 0;
			pchar.questTemp.IslaMona.Tavern = "done"; // флаг - таверна построена и сдана
			// belamour обнулим матросов-->
			ref rTown = GetColonyByIndex(FindColony(loadedLocation.fastreload));
			rTown.Ship.crew.quantity = 0;
			rTown.Ship.crew.morale = 0;
			rTown.Ship.Crew.Exp.Sailors   = 0;
			rTown.Ship.Crew.Exp.Cannoners = 0;
			rTown.Ship.Crew.Exp.Soldiers  = 0;
			ChangeCrewExp(rTown, "Sailors", 0);  // приведение к 1-100
			ChangeCrewExp(rTown, "Cannoners", 0);
			ChangeCrewExp(rTown, "Soldiers", 0);
			
		break;
		
		case "IslaMona_64":
            dialog.text = "Capitano! Sono dannatamente felice di vederti! Grazie a Freyja, sei arrivato proprio in tempo!";
			link.l1 = "Ehi, ci siamo messi in un altro bel pasticcio. Hola, Rodrigo!";
			link.l1.go = "IslaMona_65";
		break;
		
		case "IslaMona_65":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_13";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_66":
            dialog.text = "Nessuna vittima. I sopravvissuti spagnoli ci hanno raggiunto per primi, hanno riferito che c'è la possibilità di incontrare altri ospiti, e siamo riusciti a portare quasi tutte le provviste e le attrezzature dalla zona all'insediamento. La situazione con gli schiavi non è andata molto bene, ovviamente.";
			link.l1 = "";
			link.l1.go = "IslaMona_67";
		break;
		
		case "IslaMona_67":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_16";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_68":
            dialog.text = "E se ci trascinano in un assalto aperto?";
			link.l1 = "Allora lavoriamo senza pistole. Come in una parata, marceremo insieme verso le porte e poi li colpiremo da dietro. Tu tieni le porte e fornisci supporto. Questo è tutto, buona fortuna a noi!";
			link.l1.go = "IslaMona_69";
		break;
		
		case "IslaMona_69":
            DialogExit();
			AddQuestRecord("IslaMona", "21");
			pchar.quest.islamona_def_jungle1.win_condition.l1 = "locator";
			pchar.quest.islamona_def_jungle1.win_condition.l1.location = "IslaMona_jungle_01";
			pchar.quest.islamona_def_jungle1.win_condition.l1.locator_group = "encdetector";
			pchar.quest.islamona_def_jungle1.win_condition.l1.locator = "enc04";
			pchar.quest.islamona_def_jungle1.function = "IslaMona_DefSoldiersInJungle"; // встреча с французами
			LAi_LocationFightDisable(&Locations[FindLocation("IslaMona_jungle_01")], true);//запретить драться
		break;
		
		case "IslaMona_70":
            dialog.text = "Urrà, Capitano!";
			link.l1 = "D'accordo! È stato così divertente, mi sentivo come se dovessi sdraiarmi anch'io. Ragazzi, cosa avete caricato lì dentro?";
			link.l1.go = "IslaMona_71";
		break;
		
		case "IslaMona_71":
            dialog.text = "Doppio carico, Capitano. Così che un solo colpo li scoraggi dal combattere ancora!";
			link.l1 = "Non ti preoccupava che il cannone potesse esplodere da un trattamento così delicato?";
			link.l1.go = "IslaMona_72";
		break;
		
		case "IslaMona_72":
            dialog.text = "Ho un talismano speciale lasciato da Wulfric. Un ricordo della nostra natia Danimarca. Andiamo tutti alla taverna, capitano? Siamo tutti stanchi dopo oggi.";
			link.l1 = "Sì, sarebbe fantastico. Giochiamo a carte - scommettiamo sul tuo miracoloso talismano.";
			link.l1.go = "IslaMona_73";
		break;
		
		case "IslaMona_73":
            dialog.text = "Ha-ha, dopo una tale divina performance oggi, Capitano, potrei persino considerare quell'opzione!";
			link.l1 = "";
			link.l1.go = "IslaMona_74";
		break;
		
		case "IslaMona_74":
            DialogExit();
			sld = characterFromId("IM_fraofficer");
			sld.dialog.currentnode = "FraOfficer_18";
			LAi_CharacterEnableDialog(sld);
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_75":
            dialog.text = "Capitano, hai sentito quello? Ho ancora un ronzio nelle orecchie. Di chi è quella voce lamentosa?";
			link.l1 = "Quello, Rodgar, è un problema attuale. Portalo alla fabbrica, mettilo a catena e aspetta ulteriori istruzioni.";
			link.l1.go = "IslaMona_76";
		break;
		
		case "IslaMona_76":
            dialog.text = "Si, si, capitano!";
			link.l1 = "";
			link.l1.go = "IslaMona_77";
		break;
		
		case "IslaMona_77":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);
			sld = characterFromId("IM_fraofficer");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			for (i=1; i<=5; i++) 
			{
				sld = characterFromId("IM_soldier_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			}
			for(i=4; i<=7; i++)
			{
				sld = characterFromId("IM_fra_sailor_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			}
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_20";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "IslaMona_78":
            dialog.text = "Capitano, sei venuto a risolvere la questione con il prigioniero? Sono stanco di stare qui a fare la guardia.";
			link.l1 = "Dovremo ucciderlo. Il rischio è troppo grande, quindi non abbiamo scelta. Altrimenti, sarebbe meglio se non mostrassi il mio volto nelle colonie francesi.";
			link.l1.go = "IslaMona_79";
			link.l2 = "Non posso lasciarlo andare, altrimenti sarebbe meglio non mostrare il mio volto nelle colonie francesi. Mettetelo in catene e fatelo lavorare in fabbrica. È meglio che ucciderlo.";
			link.l2.go = "IslaMona_80";
		break;
		
		case "IslaMona_79":
            dialog.text = "Capito! Facciamolo in fretta. Vai avanti, Capitano. Ci vediamo domani.";
			link.l1 = "";
			link.l1.go = "IslaMona_81";
		break;
		
		case "IslaMona_80":
            dialog.text = "Caspita. Sei proprio un genio del male. Non vorrei essere il tuo nemico. Beh, allora, dovremo fare un po' di lavoro esplicativo con lui prima. Vai avanti, Capitano. Ci vediamo domani.";
			link.l1 = "";
			link.l1.go = "IslaMona_81";
			pchar.questTemp.IslaMona.Fraprisoner = "true";
		break;
		
		case "IslaMona_81":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "IslaMona_DefFraPrisonerFin", 10.0); /// идёт внутрь фактории - УСТАНОВИТЬ ЛОКАТОР
		break;
		
		case "IslaMona_82":
            dialog.text = "Che massacro! Peccato che non potevamo sparare dal cannone, ma si sono precipitati direttamente nella tua imboscata - è stato bello guardare!";
			link.l1 = "Sì, abbiamo versato molto sangue su questa terra. Ma a quanto pare, non c'è altro modo per costruire una casa in questo mondo.";
			link.l1.go = "IslaMona_83";
		break;
		
		case "IslaMona_83":
            dialog.text = "Non pensarci troppo, Capitano. È stato il destino stesso a portarli a Isla Mona. E lascia che ti dica, il destino può essere davvero una maledetta!";
			link.l1 = "Destino, o l'isola?";
			link.l1.go = "IslaMona_84";
		break;
		
		case "IslaMona_84":
            dialog.text = "Entrambi hanno svolto il loro ruolo.";
			link.l1 = "Haha! E entrambi sono bellissimi! Va bene, coraggioso vichingo. Raccogli i trofei e rimuovi questi corpi. Seppelliscili con dignità. Sono pur sempre dei nostri...";
			link.l1.go = "IslaMona_85";
		break;
		
		case "IslaMona_85":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_20a";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "IslaMona_86":
            dialog.text = "Sì, Capitano. È vero! Rodrigo lo ha detto così splendidamente che mi ha portato una lacrima all'occhio. È chiaro perché i santi padri vogliono mettere il suo culo su un palo!";
			link.l1 = "";
			link.l1.go = "IslaMona_87";
			locCameraFromToPos(1.36, 1.32, 0.31, true, 3.44, 0.20, -0.50);
		break;
		
		case "IslaMona_87":
            DialogExit();
			if (GetCharacterIndex("Mirabella") != -1)
			{
				sld = characterFromId("Mirabella");
				sld.dialog.currentnode = "mirabelle_46";
				LAi_SetActorType(sld);
				LAi_ActorDialogDelay(sld, pchar, "", 0.0);
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					sld = characterFromId("Mary");
					sld.dialog.currentnode = "IslaMona_2";
					LAi_SetActorType(sld);
					LAi_ActorDialogDelay(sld, pchar, "", 0.0);
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
					{
						sld = characterFromId("Helena");
						sld.dialog.currentnode = "IslaMona_2";
						LAi_SetActorType(sld);
						LAi_ActorDialogDelay(sld, pchar, "", 0.0);
					}
					else
					{
						sld = characterFromId("Himenes_companion_1");
						sld.dialog.currentnode = "island_man_2";
						LAi_SetActorType(sld);
						LAi_ActorDialogDelay(sld, pchar, "", 0.0);
					}
				}
			}
		break;
		
		case "IslaMona_88":
            dialog.text = "Rodrigo, e mi sono imbattuto proprio nel nostro prelato nel boudoir... E lascia che ti dica, è il miglior stabilimento di Santiago!";
			link.l1 = "Il posto migliore se ti piacciono anche i prelati.";
			link.l1.go = "IslaMona_89";
		break
		
		case "IslaMona_89":
            DialogExit();
			sld = characterFromId("Himenes");
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_90":
            dialog.text = "Sì, ho trasformato quel mascalzone e eretico Rodrigo in un vero pirata, davvero.";
			link.l1 = "A proposito, illuminami, Rodgar. Perché ci sono così pochi pirati spagnoli?";
			link.l1.go = "IslaMona_91";
		break;
		
		case "IslaMona_91":
            dialog.text = "Perché così pochi? Ah, intendi i capitani dei pirati? Beh, ce ne sono molti, operano semplicemente sotto la Casa de Contratación a Siviglia. È come l'intelligence militare, ma per qualche motivo la chiamano casa di commercio...";
			link.l1 = "";
			link.l1.go = "IslaMona_92";
		break;
		
		case "IslaMona_92":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_77";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_93":
            dialog.text = "Sì, perché non inviar loro un messaggio e invitarli. Beh, tutti hanno dei brevetti, e sono anche idealisti. Di solito non derubano i loro simili, solo se il raid non ha avuto successo, ah-ah! Si fermano solo a Puerto Principe e scontrano costantemente con il Pastor.\nDi recente, uno si è distinto... Diego de Montoya. Proprio quando l'ultima volta sono andato in campagna con Wulfric, ho sentito parlare molto delle sue avventure. Tu, capitano, hai qualcosa in comune con lui. E allo stesso tempo, sei molto diverso... Comunque, di cosa sto parlando? Facciamo un altro giro e giochiamo a carte.";
			link.l1 = "Non hai soldi. Non stai scommettendo sui dobloni, vero?";
			link.l1.go = "IslaMona_94";
		break;
		
		case "IslaMona_94":
            dialog.text = "Scommettiamo un peso a testa. Giochiamo fino a venti? Hymenes, sei dentro?";
			link.l1 = "";
			link.l1.go = "IslaMona_95";
		break;
		
		case "IslaMona_95":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_79";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_96":
            dialog.text = "Giochiamo, cap?";
			if (sti(pchar.money) >= 20)
			{
				link.l1 = "Inizia!";
				link.l1.go = "IslaMona_97";
			}
			link.l2 = "Anche io passerò, Rodgar. Pesos o meno, la gente perde navi così. Con le isole. Tu divertiti qui, e io cercherò ancora un po'.";
			link.l2.go = "IslaMona_98";
		break;
		
		case "IslaMona_97": // игра в карты
            DialogExit();
			pchar.questTemp.GoldenGirl.Game.IslaMona = "true"; // атрибут квестовой игры
			npchar.money = 20;
			pchar.questTemp.IslaMona.Money = sti(pchar.money);
			pchar.money = 20;
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 1; // ставка
			LaunchCardsGame();
		break;
		
		case "IslaMona_98": // выход из-за стола
            DialogExit();
			IslaMona_ChurchTavernStandUp();
		break;
		
		case "IslaMona_99":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win"))
			{
				dialog.text = "Passa! Bene, bene, non giocherò più con te! Sono sicuro che hai barato, Capitano! E lasciare che un baro se ne vada così non sarebbe giusto!";
				link.l1 = "Ti sto ascoltando, Rodgar.";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Fail"))
				{
					dialog.text = "Ho vinto, cap. Ma non posso lasciarti andare a mani vuote così, haha!";
					link.l1 = "Bene, birbante. Sarà una lezione per me...";
				}
				else
				{
					dialog.text = "Ho vinto, cap. Ma non posso lasciarti andare a mani vuote così, haha!";
					link.l1 = "Bene, te mezzafinocchia. Sarà una lezione per me...";
				}
			}
			link.l1.go = "IslaMona_100";
		break;
		
		case "IslaMona_100":
            dialog.text = "Ah, dai! Hai dato a me e al mio equipaggio la possibilità di una vera vita lontano da spazi angusti, acqua stagnante e il rischio di prendere un frammento in... il cranio. Ecco. Questo amuleto è stato portato da Wulfric dalla lontana Danimarca e poi passato a me così che... eh, non avrei dovuto sprofondare troppo nel suo seminterrato. Non ne ho più bisogno, ma tu - oh, lo troverai molto utile.";
			link.l1 = "Grazie, Rodgar. Infatti, un oggetto utile. E anche bello...";
			link.l1.go = "IslaMona_101_1";
			link.l2 = "Tienilo, Rodgar. Senza di te, questo posto non esisterebbe. Che sia un promemoria della tua patria.";
			link.l2.go = "IslaMona_101_2";
		break;
		
		case "IslaMona_101_1":
			GiveItem2Character(pchar, "talisman3");
			Log_Info("You received 'Thor's Hammer'");
			PlaySound("interface\important_item.wav");
            dialog.text = "Sono contento che ti sia piaciuto, Capitano. Un altro round?";
			link.l1 = "Voi ragazzi rilassatevi qui, e io darò un'occhiata in giro un po' di più.";
			link.l1.go = "IslaMona_102";
		break;
		
		case "IslaMona_101_2":
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			AddCharacterExpToSkill(pchar, "Fortune", 2000);
            dialog.text = "Come desideri! Allora ne darò uno alla signora fortuna, haha! Un altro giro?";
			link.l1 = "Voi ragazzi rilassatevi qui, e io darò un'occhiata in giro un po' di più.";
			link.l1.go = "IslaMona_102";
		break;
		
		case "IslaMona_102":
            DialogExit();
			DeleteAttribute(pchar, "questTemp.GoldenGirl.Game");
			DeleteAttribute(pchar, "GenQuest.Cards");
			pchar.money = sti(pchar.money)+sti(pchar.questTemp.IslaMona.Money);
			DeleteAttribute(pchar, "questTemp.IslaMona.Money");
			IslaMona_ChurchTavernStandUp();
		break;
		
		case "IslaMona_103":
            dialog.text = "Ebbene, Capitano. Hai risolto le questioni con lo spagnolo, abbiamo fatto la nostra celebrazione e il mal di testa è un po' diminuito. La vita è buona!";
			link.l1 = "Cosa stai combinando, Rodgar?";
			link.l1.go = "IslaMona_104";
		break;
		
		case "IslaMona_104":
			sTemp = "";
            if (CheckAttribute(pchar, "questTemp.IslaMona.MiraRodgar")) sTemp = "I'll get along with the woman. ";
			dialog.text = "Andrò a cacciare come al solito, tenendo d'occhio la mia... la nostra taverna, prendendo a calci gli schiavi alla fabbrica. Una pensione perfetta.";
			link.l1 = "Hai solo cinque anni più di me, Rodgar. E tu, Rodrigo? Come va?";
			link.l1.go = "IslaMona_105";
		break;
		
		case "IslaMona_105":
            DialogExit();
			sld = characterFromId("Himenes");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		// <-- Исла Мона
		
		case "repair":
			if (CheckSelfRepairConditions())
			{
				dialog.text = "Certo, capitano! Ci serve solo legname e tela per le vele. Vai al tuo punto di sbarco e ordina all'equipaggio di preparare i materiali.";
				link.l1 = "Sulla mia strada. Fallo in fretta.";
				link.l1.go = "repair_1";
			}
			else
			{
				dialog.text = "Certo, capitano, ma come la vedo io, la tua nave non ha bisogno di riparazioni ora.";
				link.l1 = "Ho solo chiesto...";
				link.l1.go = "carpenter_exit";
			}
		break;
		
		case "repair_1":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			chrDisableReloadToLocation = true;
			DoQuestReloadToLocation(Pchar.location.from_sea, "reload", "sea", "Mtraxx_WolfreekRepairShore");
		break;
		
		case "shipstock_info":
			npchar.portman.info = "true";
            dialog.text = "È possibile, capitano. Tuttavia, ci sono alcune limitazioni: ci sono solo due posti su quest'isola adatti a questo. Inoltre non puoi lasciare qui nessuno tranne un singolo ufficiale per ogni nave. Semplicemente non abbiamo abbastanza risorse per mantenere equipaggi qui. Ancora. Infine, non c'è spazio per le navi di primo rango.";
			link.l1 = "Capito. Sono pronto a lasciare una nave qui.";
			link.l1.go = "shipstock";
			link.l2 = "Molto bene, la preparerò.";
			link.l2.go = "carpenter_exit";
		break;
		
		case "shipstock":
			if(CheckAttribute(pchar,"questTemp.IslaMona.Harbour") && pchar.questTemp.IslaMona.Harbour == "done")
			{
				if(sti(npchar.portman) == 3)
				{
					dialog.text = "Capitano, ci sono già tre delle vostre navi ancorate al molo. Non c'è più spazio disponibile.";
					link.l1 = "Hai ragione, ho dimenticato.";
					link.l1.go = "carpenter_exit";
					break;
				}
				else
				{
					if(CheckAttribute(npchar,"FstClassInHarbour") && sti(npchar.portman) > 0)
					{
						dialog.text = "Capitano, c'è già una nave di primo rango ancorata al molo. Non c'è più spazio disponibile.";
						link.l1 = "Hai ragione, ho dimenticato.";
						link.l1.go = "carpenter_exit";
						break;
					}
				}
			}
			else
			{
				if (sti(npchar.portman) == 2)
				{
					dialog.text = "Capitano, due delle tue navi sono già ancorate al molo. Non c'è più spazio disponibile.";
					link.l1 = "Hai ragione, ho dimenticato.";
					link.l1.go = "carpenter_exit";
					break;
				}
			}
			if (GetCompanionQuantity(pchar) < 2)
			{
				dialog.text = "Capitano, hai solo una nave.";
				link.l1 = "Mh... Dovrei bere di meno...";
				link.l1.go = "carpenter_exit";
				break;
			}
            dialog.text = "Quale nave vuoi lasciare qui?";
			for(i=1; i<COMPANION_MAX; i++)
			{
				int cn = GetCompanionIndex(PChar, i);
				if( cn > 0 )
				{
					ref chref = GetCharacter(cn);
					if (!GetRemovable(chref)) continue;

					attrL = "l"+i;
					Link.(attrL) = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
					Link.(attrL).go = "ShipStockMan_" + i;
				}
			}
			Link.l9 = "Aspetta, ho cambiato idea.";
			Link.l9.go = "carpenter_exit";
		break;
		
		case "ShipStockMan_1":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 1);
			dialog.text = "Vediamo...";
			Link.l1 = "Molto bene.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Aspetta, ho cambiato idea.";
			Link.l2.go = "carpenter_exit";
		break;

		case "ShipStockMan_2":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 2);
			dialog.text = "Vediamo...";
			Link.l1 = "Molto bene.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Aspetta, ho cambiato idea.";
			Link.l2.go = "carpenter_exit";
		break;

		case "ShipStockMan_3":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 3);
			dialog.text = "Vediamo...";
			Link.l1 = "Molto bene.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Aspetta, ho cambiato idea.";
			Link.l2.go = "carpenter_exit";
		break;
		
		case "ShipStockMan_4":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 4);
			dialog.text = "Vediamo...";
			Link.l1 = "Molto bene.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Aspetta, ho cambiato idea.";
			Link.l2.go = "carpenter_exit";
		break;
		
		case "ShipStock_2":
            chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			if(CheckAttribute(pchar,"questTemp.IslaMona.Harbour") && pchar.questTemp.IslaMona.Harbour == "done")
			{
				if(sti(RealShips[sti(chref.Ship.Type)].Class) < 2 && sti(npchar.portman) > 0)
				{
					dialog.text = "Capitano, ho già detto che il nostro ancoraggio può ospitare solo una nave di primo rango. È troppo grande per lo spazio disponibile.";
					Link.l1 = "Hai ragione, ho dimenticato.";
					Link.l1.go = "carpenter_exit";
					break;
				}
			}
			else
			{
				if (sti(RealShips[sti(chref.Ship.Type)].Class) < 2)
				{
					dialog.text = "Capitano, le navi di primo rango sono troppo grandi per le nostre coste. Te l'ho già detto.";
					Link.l1 = "Hai ragione, ho dimenticato.";
					Link.l1.go = "carpenter_exit";
					break;
				}
			}
			if (sti(chref.Ship.Crew.Quantity) > 0)
			{
				dialog.text = "Capitano, porta tutto il suo equipaggio sulla tua nave ammiraglia tranne un ufficiale.";
				Link.l1 = "Ah, giusto! Lo farò!";
				Link.l1.go = "carpenter_exit";
				break;
			}
			dialog.Text = "Allora, dobbiamo rimanere qui"+XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName+"Acc")+" nominato '"+chref.Ship.Name+"'. Giusto?";
			Link.l1 = "Giusto.";
			Link.l1.go = "ShipStock_3";
			Link.l2 = "Aspetta, ho cambiato idea.";
			Link.l2.go = "carpenter_exit";
		break;
		
		case "ShipStock_3":
            chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
            chref.ShipInStockMan = NPChar.id;
			chref.ShipInStockMan.MoneyForShip = 0;
            chref.ShipInStockMan.AltDate = GetQuestBookDataDigit();
            SaveCurrentNpcQuestDateParam(chref, "ShipInStockMan.Date");
            RemoveCharacterCompanion(pchar, chref);
            chref.location = "";
            chref.location.group = "";
            chref.location.locator = "";
			if(sti(RealShips[sti(chref.Ship.Type)].Class) < 2)
			{
				npchar.FstClassInHarbour = 1;
			}
            npchar.portman = sti(npchar.portman)+1;
            pchar.ShipInStock = sti(pchar.ShipInStock)+1;
			dialog.text = "Molto bene, ci assicureremo che sia consegnata a un porto sicuro.";
			Link.l1 = "Eccellente!";
			Link.l1.go = "carpenter_exit";
		break;
		
		case "shipstockreturn":
            if (GetCompanionQuantity(pchar) < COMPANION_MAX)
			{
				dialog.text = "Quale nave prenderai, capitano?";
				cn = 1;
				for (i=1; i<MAX_CHARACTERS; i++)
				{
					makeref(chref, Characters[i]);
					if (CheckAttribute(chref, "ShipInStockMan"))
					{
						if (chref.ShipInStockMan == NPChar.id)
						{
							attrL = "l"+cn;
							Link.(attrL)    = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
							Link.(attrL).go = "ShipStockManBack_" + i;
							cn++;
						}
					}
				}
				link.l9 = "Aspetta, ho cambiato idea.";
				link.l9.go = "carpenter_exit";
			}
			else
			{
				dialog.text = "Capitano, non hai spazio nel tuo squadrone per un'altra nave.";
				link.l1 = "Mh. Sembra che tu abbia ragione.";
				link.l1.go = "carpenter_exit";
			}
		break;
		
		 case "ShipStockManBack":
            chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			dialog.Text = "La stai portando con te?";
			link.l1 = "Sì.";
			link.l1.go = "ShipStockManBack2";
			link.l2 = "Aspetta, ho cambiato idea.";
			link.l2.go = "carpenter_exit";
		break;
		
		case "ShipStockManBack2":
			DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			if(CheckAttribute(npchar,"FstClassInHarbour")) DeleteAttribute(npchar,"FstClassInHarbour");
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			DeleteAttribute(chref, "ShipInStockMan");
			SetCompanionIndex(pchar, -1, sti(NPChar.ShipToStoreIdx));
			npchar.portman = sti(npchar.portman)-1;
            pchar.ShipInStock = sti(pchar.ShipInStock)-1;
		break;
		
		case "storadge":
            dialog.text = "Qui? No. Ma Wulfric ha costruito un grande fienile non lontano da qui. Un edificio solido, ben coperto con foglie di palma e tela cerata. Ha un lucchetto e una stanza per un carico abbastanza grande da riempire una dozzina di navi mercantili\nÈ vuoto ora, ma ho una chiave se vuoi esaminarlo. Andiamo?";
			link.l1 = "Certo! A proposito: che ne è dei ratti su quest'isola? Rovineranno la mia merce nel granaio?";
			link.l1.go = "storadge_1";
		break;
		
		case "storadge_1":
            dialog.text = "Anche il Lupo ha provveduto a questo: ha portato qui dall'entroterra due gatte. Si è dimenticato dei maschi però, quindi queste pazze pelose in calore fanno dei rumori terribili ogni volta che arriva la loro stagione. Ma cacciano i topi e i ratti abbastanza bene. Non preoccuparti, capitano. I tuoi beni saranno al sicuro da parassiti e venti.";
			link.l1 = "Ottimo! Ne farò buon uso. Tieni la tua chiave per te e mostrami questo magazzino.";
			link.l1.go = "storadge_2";
		break;
		
		case "storadge_2":
			DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			npchar.city = "islamona";
			npchar.Storage.Activate = true;
			SaveCurrentNpcQuestDateParam(npchar, "Storage.Date");
			npchar.MoneyForStorage = 0;
			npchar.storadge = true;
			LaunchStorage(29);
		break;
		
		case "storadge_3":
            dialog.text = "Seguimi, capitano.";
			link.l1 = "...";
			link.l1.go = "storadge_4";
		break;
		
		case "storadge_4":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			LaunchStorage(29);
		break;
		
		// Мирабель
		case "mirabelle":
			PlaySound("Voice\English\Girl_Q.wav");
            dialog.text = "Ah...";
			link.l1 = "Beh ora... Una ragazza... Cosa ci fai qui?";
			link.l1.go = "mirabelle_1";
		break;
		
		case "mirabelle_1":
			PlaySound("Voice\English\Girl_Q.wav");
            dialog.text = "Oh...";
			link.l1 = "...";
			link.l1.go = "mirabelle_2";
		break;
		
		case "mirabelle_2":
            DialogExit();
			npchar.dialog.currentnode = "mirabelle_3";
			sld = characterFromId("Mrt_Rocur");
			sld.dialog.currentnode = "rocur_74";
			ChangeCharacterAddressGroup(sld, "LaVega_TwoFloorHouse", "goto", "goto8");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
		break;
		
		case "mirabelle_3":
			PlaySound("Voice\English\LE\Mirabel\Mirabel_01.wav");
            dialog.text = "Signore! Signore "+pchar.name+" non mi uccidere per favore! Ti prego! Non dirò nulla a Tyrex! Odio quella bestia! Ti prego, per favore!";
			link.l1 = "...";
			link.l1.go = "mirabelle_4";
		break;
		
		case "mirabelle_4":
			DialogExit();
            npchar.dialog.currentnode = "mirabelle_5";
			npchar.greeting = "mirabella_goodgirl";
			sld = characterFromId("Mrt_Rocur");
			sld.dialog.currentnode = "rocur_80";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "mirabelle_5":
            dialog.text = "";
			link.l1 = "Ehi ragazza! Hai sentito? Verrai con me o questo bastardo tosto ti ucciderà.";
			link.l1.go = "mirabelle_6";
		break;
		
		case "mirabelle_6":
            dialog.text = "Andrò con te, signore, ovunque tu mi stia portando!";
			link.l1 = "Bene allora. Tieni chiusa la bocca, o ti ucciderò se cominci a urlare o a chiamare Tyrex. Come ti chiami?";
			link.l1.go = "mirabelle_7";
		break;
		
		case "mirabelle_7":
            dialog.text = "Mirabelle...";
			link.l1 = "Comportati bene Mirabelle e tutto finirà bene per te. Stai vicino a me e non fare rumore.";
			link.l1.go = "mirabelle_8";
		break;
		
		case "mirabelle_8":
            dialog.text = "Giuro che non lo farò, signore.";
			link.l1 = "...";
			link.l1.go = "mirabelle_9";
		break;
		
		case "mirabelle_9":
            DialogExit();
            npchar.dialog.currentnode = "mirabelle_10";
			LAi_SetImmortal(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			sld = characterFromId("Mrt_Rocur");
			sld.dialog.currentnode = "rocur_85";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
			pchar.questTemp.Mtraxx.Mirabella = "true";
		break;
		
		case "mirabelle_10":
            dialog.text = "Signore?";
			link.l1 = "Hai fatto bene ragazza, mi piaci per questo. Ora stiamo andando alla mia nave dove sarai messa in una piccola cabina per un po' di tempo. Mi dispiace ma non voglio che tu corra da Tyrex e gli dica qualcosa.";
			link.l1.go = "mirabelle_11";
		break;
		
		case "mirabelle_11":
            dialog.text = "Assolutamente no, signore! Non andrei mai da Tyrex, questo bastardo! Lo detesto! Lo odio!!!";
			link.l1 = "Caspita! Cosa ti ha fatto?";
			link.l1.go = "mirabelle_12";
		break;
		
		case "mirabelle_12":
            dialog.text = "Molto... Lo odio, lo odio!";
			link.l1 = "Capisco. Una volta arrivati vivrai in una casa piuttosto lussuosa. Da solo. Mantienimi di buon umore e nessuno ti farà mai del male. Ora vai su una barca lunga... Mirabelle.";
			link.l1.go = "mirabelle_13";
		break;
		
		case "mirabelle_13":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "OpenTheDoors", 20.0);
			pchar.quest.mtraxx_pasq_mirabella.win_condition.l1 = "location";
			pchar.quest.mtraxx_pasq_mirabella.win_condition.l1.location = "Shore75";
			pchar.quest.mtraxx_pasq_mirabella.function = "Mtraxx_PasqualeMirabella";
			pchar.quest.mtraxx_pasq_mirabella1.win_condition.l1 = "location";
			pchar.quest.mtraxx_pasq_mirabella1.win_condition.l1.location = "Shore77";
			pchar.quest.mtraxx_pasq_mirabella1.function = "Mtraxx_PasqualeMirabella";
			AddPassenger(pchar, npchar, false);//добавить пассажира
			SetCharacterRemovable(npchar, false);
			SetFunctionTimerCondition("Mtraxx_MirabellaSailOver", 0, 0, 30, false); // месяц на доплыть до Исла Моны
		break;
		
		case "mirabelle_14":
            dialog.text = "Siamo arrivati, signore?";
			link.l1 = "Sì, tesoro. Questo è il mio villaggio e la mia casa. Sono il proprietario del luogo. Sono però un ospite raro qui - c'è troppo lavoro da fare là fuori. Assicurati di tenere pulita la mia casa mentre ci vivi dentro o ti darò a Rodgar e ai suoi falegnami. Sentiti libero di girare per l'isola, è molto bella, ma comunque non c'è scampo da essa.";
			link.l1.go = "mirabelle_15";
			// belamour legendary edition -->
			link.l2 = "Ecco dove siamo. Questa è casa mia. Tutto su quest'isola mi appartiene. Non vengo qui spesso - vivo sulla nave dopotutto, ma comunque qualcuno deve badare alla casa. Rodgar ha gentilmente accettato di affidarti questo ruolo onorario. Puoi girare quanto vuoi, anche nella giungla o sulle spiagge, ma assicurati di avere qualcuno come compagno, ci sono ancora animali selvatici in giro. Comunque, non puoi partire da qui senza una nave.";
			link.l2.go = "mirabelle_15a";
		break;
		
		case "mirabelle_15a":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
            dialog.text = "Non ho dove correre, signore "+pchar.name+". Non ho nessuno, e nessuno ha bisogno di me. A meno che non mi vendi a un bordello...";
			link.l1 = "Al focolare c'è un portello che conduce al sotterraneo, non andarci, potresti cadere nella grotta e romperti le ossa, o non riusciresti a tornare indietro e potresti morire di fame. E poi sarebbe un peccato che ti ho salvato invano.";
			link.l1.go = "mirabelle_16";
		break;
		
		case "mirabelle_15":
			ChangeCharacterComplexReputation(pchar,"nobility", -10);
			// <-- legendary edition
            dialog.text = "Non ho dove andare, signore "+pchar.name+". Non ho famiglia e non sono utile. Potrei finire di nuovo in un bordello.";
			link.l1 = "C'è un portello che conduce alla grotta, stanne lontano. È buio e pericoloso laggiù.";
			link.l1.go = "mirabelle_16";
		break;
		
		case "mirabelle_16":
            dialog.text = "Resterò lontano, signore.";
			link.l1 = "C'è anche una camera da letto al piano di sopra. Seguimi.";
			link.l1.go = "mirabelle_17";
		break;
		
		case "mirabelle_17":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			pchar.quest.mtraxx_islamona_mirabella1.win_condition.l1 = "location";
			pchar.quest.mtraxx_islamona_mirabella1.win_condition.l1.location = "IslaMona_TwoFloorRoom";
			pchar.quest.mtraxx_islamona_mirabella1.function = "Mtraxx_PasqualeMirabellaRoom";
		break;
		
		case "mirabelle_18":
            dialog.text = "";
			link.l1 = "Ecco. Ti ho mostrato tutta la casa. Non è peggio del posto di Tyrex in cui vivevi prima. Spero ti piaccia.";
			link.l1.go = "mirabelle_19";
		break;
		
		case "mirabelle_19":
            dialog.text = "Sì, signore. Avete una grande casa. Prometto di prendermene cura bene in vostra assenza.";
			link.l1 = "Sono contento che tu sia così disponibile nei miei confronti. Spero che tu stia dicendo la verità. Sii onesta con me o te ne pentirai. Sii una brava ragazza e non mi rendere triste e io sarò buono con te. Charlie Prince onora la sua parola!";
			link.l1.go = "mirabelle_20";
			// belamour legendary edition -->
			link.l2 = "Ti credo, cara. Penso che sarai più al sicuro qui piuttosto che essere legata in catene in quella oscura stanza dove Tyrex ti teneva.";
			link.l2.go = "mirabelle_20a";
		break;
		
		case "mirabelle_20a":
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
            dialog.text = "Grazie signore "+pchar.name+". Grazie per non aver lasciato che il tuo... companero mi uccidesse. Sei così gentile con me...";
			link.l1 = "Eh, e sei divertente,... E il tuo viso è anche bello, anche con un marchio sulla fronte. Spero che tutto il resto sia a posto... Bene, ora mostra al tuo capitano cosa sai fare. Rilassiamoci per un paio d'ore dopo il rollio del mare.";
			link.l1.go = "mirabelle_21";
			link.l2 = "Molto bene. Questo è tutto, ho - molto lavoro da fare. E tu sistemati, incontra Rodgar e i ragazzi. Quando torno, chiacchiereremo ancora un po'.";
			link.l2.go = "mirabelle_21a";
		break;
		
		case "mirabelle_20":
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			// <-- legendary edition
            dialog.text = "Grazie signore "+pchar.name+". Grazie per non aver permesso al tuo... compagno di uccidermi. Sei molto gentile.";
			link.l1 = "Ehi, sei un piccolo tesoro divertente... Un bel viso nonostante il segno. Spero che anche il resto sia a posto.. Ora mostra al tuo capitano cosa sai fare.";
			link.l1.go = "mirabelle_21";
			// belamour legendary edition -->
			link.l2 = "Molto bene. Ecco, ho - molto lavoro da fare. E tu sistemati, incontra Rodgar e i ragazzi. Quando torno, chiacchiereremo ancora.";
			link.l2.go = "mirabelle_21a";
		break;
		
		case "mirabelle_21a":
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			AddCharacterExpToSkill(pchar, "Fortune", 400);
			pchar.questTemp.Mtraxx.MirabellaFirstTimeSex = true;
            DialogExit();
			npchar.InOurHouse = true;
		    npchar.dialog.currentnode = "mirabelle_26";
		    chrDisableReloadToLocation = false;
			pchar.quest.mtraxx_mirabella_setlife.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_mirabella_setlife.function = "Mtraxx_MirabellaSetLife";
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		break;
		
		case "mirabelle_21":
			DialogExit();
			
			pchar.questTemp.Mtraxx.MirabellaFirstTimeKiss = true;
			sld = characterFromId("Mirabella");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			StartQuestMovie(true, false, true);
			LAi_SetActorType(pchar);
			LAi_Fade("IslaMona_MirabelleKiss", "");
		break;
		
		case "mirabelle_22":
			PlaySound("Voice\English\LE\Mirabel\Mirabel_07.wav");
            dialog.text = "Signore "+pchar.name+"sei così dolce... Sei un vero gentiluomo. Devi essere arrivato dall'Europa da poco.";
			link.l1 = "Lusingami pure, piccola bugiarda, ci sto cascando. Ehi, sei brava, Mirabelle! Tyrex ha un buon gusto, ah-ah...";
			link.l1.go = "mirabelle_23";
			locCameraFromToPos(0.55, 1.64, -1.09, true, 0.63, -0.30, -3.12);
		break;
		
		case "mirabelle_23":
            dialog.text = "Non lo sono. Sei un gentiluomo. Ma stai fingendo di essere rude per qualche motivo. Mhmm... Mi è piaciuto molto. Sarò in attesa di rivederti...";
			link.l1 = "Ah sì, un gentiluomo... un gentiluomo di fortuna, ah-ah! Molto bene cara, sistemati qui per ora.";
			link.l1.go = "mirabelle_24";
		break;
		
		case "mirabelle_24":
            dialog.text = "Addio, signore.";
			link.l1 = "...";
			// belamour legendary edition -->
			if(CheckAttribute(pchar,"questTemp.Mtraxx.MirabellaFirstTimeSex"))
			{
				link.l1.go = "mirabelle_28";
				DeleteAttribute(pchar,"questTemp.Mtraxx.MirabellaFirstTimeSex");
			}
			else link.l1.go = "mirabelle_25";
			// <-- legendary edition
		break;
		
		case "mirabelle_25":
            DialogExit();
			npchar.InOurHouse = true;
		    npchar.dialog.currentnode = "mirabelle_26";
			LAi_SetStayType(npchar);
		    chrDisableReloadToLocation = false;
			pchar.quest.mtraxx_mirabella_setlife.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_mirabella_setlife.function = "Mtraxx_MirabellaSetLife";
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		break;
		
		case "mirabelle_26":
            dialog.text = TimeGreeting()+", signore "+pchar.name+"! Sono molto contento di vederti. Come stai?";
			link.l1 = RandSwear()+""+RandPhraseSimple("Brivido i miei Bottoni, brivido la mia Anima!","Oh, meglio vivere e morire, sotto l'audace bandiera nera che sventolo!")+"Charlie Prince va bene, tesoro.";
			link.l1.go = "mirabelle_26x";
			if (!CheckAttribute(pchar, "questTemp.Mirabelleblock")) {
				if (!CheckAttribute(npchar, "sex_date") || GetNpcQuestPastDayParam(npchar, "sex_date") >= 1)
				{
					link.l2 = "Cara, che ne dici di rendere un capitano un po' più felice?";
					link.l2.go = "mirabelle_sex";
				}
			}
		break;
		
		case "mirabelle_26x":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_26";
		break;
		
		case "mirabelle_sex":
            dialog.text = "Qualsiasi cosa per te, signore!";
			link.l1 = RandPhraseSimple("Preparate gli arpioni!","All'arrembaggio!");
			link.l1.go = "mirabelle_sex_1";
		break;
		
		case "mirabelle_sex_1":
            DialogExit();
			
			StartQuestMovie(true, false, true);
			LAi_SetActorType(pchar);
			LAi_Fade("", "");
			
			LAi_SetActorType(npchar);
			// belamour legendary edition -->
			if(CheckAttribute(pchar,"questTemp.Mtraxx.MirabellaFirstTimeSex")) npchar.dialog.currentnode = "mirabelle_22";
		    else npchar.dialog.currentnode = "mirabelle_27";
			// <-- legendary edition
			if (pchar.location == "IslaMona_TwoFloorRoom") DoQuestCheckDelay("IslaMona_MirabelleKiss", 0.5);
			else DoQuestReloadToLocation("IslaMona_TwoFloorRoom", "goto", "goto2", "IslaMona_MirabelleKiss");
		break;
		
		case "mirabelle_27":
            dialog.text = "Mhm... Signore, sei un mago! Spero ti sia piaciuto anche a te? Ho fatto del mio meglio.";
			link.l1 = "Hai fatto benissimo, tesoro.";
			link.l1.go = "mirabelle_28";
			locCameraFromToPos(0.55, 1.64, -1.09, true, 0.63, -0.30, -3.12);
		break;
		
		case "mirabelle_28":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_26";
			LAi_SetStayType(npchar);
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
		break;
		
		case "mirabelle_sleep":
            dialog.text = "Non è vero, non è vero! Signor "+pchar.name+" è buono e gentile! Sta solo fingendo di essere un pirata malvagio! Tu sei, signore "+pchar.name+"?";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep6_1");
		break;
		
		case "mirabelle_29":
            dialog.text = TimeGreeting()+", signore "+pchar.name+"! Sono molto felice di vederti. Come stai? Perché sei così triste?";
			link.l1 = "Ciao, Mirabelle. Perché pensi che io sia triste?";
			link.l1.go = "mirabelle_30";
		break;
		
		case "mirabelle_30":
            dialog.text = "Ebbene, posso vedere. Non sei il solito tu. Vuoi che ti tiri su di morale? Dai! Ho raccolto dei frutti davvero dolci dalla giungla e il pesce che Rodgar e i suoi ragazzi hanno pescato ieri è arrostito e ancora caldo.";
			link.l1 = "Aspetta. Voglio parlare con te.";
			link.l1.go = "mirabelle_31";
		break;
		
		case "mirabelle_31":
            dialog.text = "Certo, signore, come vuoi. Sono tutto orecchie";
			link.l1 = "Dimmi come sei finito nelle mani di Tyrex e perché c'è un segno di un ladro sulla tua fronte. Non avere paura, non ti farò mai del male. Ho solo bisogno di sentire la tua storia.";
			link.l1.go = "mirabelle_32";
		break;
		
		case "mirabelle_32":
            dialog.text = "Ah, signore! La mia storia è breve e noiosa. Sono nato a Puerto Rico, mio padre era un gentiluomo bianco, mia madre - un'indiana. Non ho mai visto mio padre. Quando ero bambino ero un servo e quando sono cresciuto ho avuto la follia di rubare i gioielli del mio padrone. Non ne ho mai avuto uno mio e ne volevo uno così tanto, solo per provarlo per un giorno. Ovviamente, hanno scoperto tutto\nC'è stato un processo, sono stato frustato, marchiato e messo in prigione a San Juan. Non sono rimasto lì a lungo: uno degli ufficiali ha fatto un affare con un capo e sono stato venduto a un bordello di Philipsburg per una manciata di dobloni d'oro\nHo passato lì un anno o giù di lì. Un giorno sfortunato ci hanno fatto visita Tyrex e il suo amico sfigato con gli occhiali.";
			link.l1 = "Pasquale Lavoisier...";
			link.l1.go = "mirabelle_33";
		break;
		
		case "mirabelle_33":
            dialog.text = "Sì-sì, il suo nome era signor Pasquale Lavoisier. Non ho la minima idea di cosa abbiano visto in me, ma poco dopo la loro visita, Tyrex mi ha comprato da Madame Johanna e mi ha messo in una casa chiusa a chiave piena di casse e merci. È stato il periodo peggiore della mia vita, ancora peggio dei giorni passati nella prigione di San Juan. Tyrex mi visitava ogni giorno a meno che non fosse in mare e allora potevo respirare liberamente, ma ogni volta che veniva il signor Lavoisier io... io.... È stato il peggio di tutti. Signor "+pchar.name+", per favore, posso non parlare di questo?\nNon so quanto tempo sono stata lì. E poi sei arrivato tu e mi hai portato via da quella terribile casa. Sono stata molto fortunata che tu fossi così gentile.";
			link.l1 = "Gentile? Mirabelle, ma ho fatto esattamente la stessa cosa a te: ti ho portato su un'isola e ti ho rinchiuso dentro una casa.";
			link.l1.go = "mirabelle_34";
		break;
		
		case "mirabelle_34":
            dialog.text = "No, signore, non è vero. Sono chiuso qui dentro? Faccio una passeggiata intorno all'isola ogni giorno. È un posto meraviglioso e pacifico. Devo fare un sacco di lavori domestici? Per niente, e mi ci sono abituato comunque. E tu non sei come Tyrex, non come il suo amico mercante. Sono sempre felice di vederti, sei così giovane e bello. E anche un gentiluomo...";
			link.l1 = "Mirabelle, vuoi che ti porti in qualche città? Ti darò abbastanza soldi. Dove? Scegli qualunque colonia.";
			link.l1.go = "mirabelle_35";
		break;
		
		case "mirabelle_35":
            dialog.text = "Signore, vuoi cacciarmi via? Per favore, non farlo, te lo prego!";
			link.l1 = "Bene... Pensavo che tu volessi tornare alla vita normale...";
			link.l1.go = "mirabelle_36";
		break;
		
		case "mirabelle_36":
            dialog.text = "Ah, signore "+pchar.name+", e cosa c'è per me? Come potrei mai sposarmi essendo una mezzosangue marchiata? Sarò di nuovo venduta a un bordello. Per favore, non mandarmi via. Mi piace questo posto, non mi sono mai sentita così pacifica e sicura da nessuna parte come qui. Rodgar e i suoi ragazzi sono bravi ragazzi, siamo amici e non mi hanno mai fatto del male, ognuno di loro rischierebbe la vita per me. Mi piace passare il tempo con loro, è divertente! A volte facciamo un fuoco sulla spiaggia e ballo la samba. Per favore, signore, farò qualsiasi cosa per te, basta che mi lasci stare!";
			link.l1 = "Bene, Mirabelle, resta qui visto che ti piace così tanto questo posto. Sappi solo che non sei una prigioniera qui, puoi sempre chiedermi di portarti via da qui.";
			link.l1.go = "mirabelle_37";
		break;
		
		case "mirabelle_37":
            dialog.text = "Mio caro e buon signore, grazie! Grazie! Grazie! Non ti chiederò mai nulla del genere - voglio rimanere prigioniero di questa isola... e tuo prigioniero, tee-hee... Sei così gentile ma triste oggi! Non canti e non bestemmi come fai di solito.";
			link.l1 = "Potrei cantare ma niente più bestemmie, Mirabelle. E... mi dispiace se sono mai stato scortese con te.";
			link.l1.go = "mirabelle_38";
		break;
		
		case "mirabelle_38":
            dialog.text = "Sarai severo e rigido proprio come un signore inglese?.. Ah... signore, vuoi che io balli e canti stasera? Solo per te. Ora vieni con me! Non c'è miglior rimedio per la tristezza dell'amore. Mi sei mancato tanto.";
			link.l1 = "Ah! Buon punto, cara mia... Andiamo.";
			link.l1.go = "mirabelle_39";
		break;
		
		case "mirabelle_39":
            DialogExit();
			LAi_SetActorType(npchar);
		    npchar.dialog.currentnode = "mirabelle_40";
			if (pchar.location == "IslaMona_TwoFloorRoom") DoQuestCheckDelay("IslaMona_MirabelleKiss", 0.5);
			else DoQuestReloadToLocation("IslaMona_TwoFloorRoom", "goto", "goto2", "IslaMona_MirabelleKiss");
		break;
		
		case "mirabelle_40":
			PlaySound("Voice\English\LE\Mirabel\Mirabel_07.wav");
            dialog.text = "Ah, signore "+pchar.name+", sei stato così gentile oggi, mhm... Sei contento di me, mio caro capitano?";
			link.l1 = "Tutto era delizioso, Mirabelle.";
			link.l1.go = "mirabelle_41";
			locCameraFromToPos(0.55, 1.64, -1.09, true, 0.63, -0.30, -3.12);
		break;
		
		case "mirabelle_41":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_42";
			LAi_SetStayType(npchar);
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
		break;
		
		case "mirabelle_42":
			bool bMary = GetCharacterIndex("Mary") != -1 && CheckAttribute(pchar, "questTemp.LSC.Mary_officer");
			bool bHelena = GetCharacterIndex("Helena") != -1 && CheckAttribute(pchar, "questTemp.Saga.Helena_officer");
            dialog.text = TimeGreeting()+", signore "+pchar.name+"! Sono così felice di vederti! Come stai?";
			link.l1 = ""+LinkRandPhrase("Anche io sono felice di vederti, mia ragazza.","Ciao, Mirabelle. Sei sempre la stessa - gioiosa e bella, che vista piacevole.","Ciao, bella. Sei splendida!")+"Sto proprio bene. Spero che tu stia bene anche tu.";
			link.l1.go = "mirabelle_42x";
			if (!bMary && !bHelena && !CheckAttribute(npchar,"quest.rodgar")) // прогона 3
			{
				if (!CheckAttribute(npchar, "sex_date") || GetNpcQuestPastDayParam(npchar, "sex_date") >= 1)
				{
					link.l2 = "Mirabelle, ho già iniziato a sentire la tua mancanza e quella del tuo donnola. Bacerai il tuo lupo di mare?";
					link.l2.go = "mirabelle_43";
				}
			}
		break;
		
		case "mirabelle_42x":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_42";
		break;
		
		case "mirabelle_43":
            dialog.text = "Ah, dolce mio capitano, anche tu mi sei mancato! Dai, sono al limite!";
			link.l1 = "...";
			link.l1.go = "mirabelle_39";
		break;
		
		// Jason Исла Мона
		case "mirabelle_44":
			dialog.text = "Signor Capitano! Capitano "+pchar.name+"! Sono così felice! Ci salverai!";
			link.l1 = "Sono felice di vederti anche tu, Mirabelle. Allora, quali sono le perdite?";
			link.l1.go = "mirabelle_45";
		break;
		
		case "mirabelle_45":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_42";
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_66";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "mirabelle_46":
			dialog.text = "Capitano, Capitano, grazie! Sei il migliore, il più gentile! Non solo mi hai salvato dai mostri, ma mi hai anche dato una nuova vita! A tutti noi!";
			link.l1 = "";
			link.l1.go = "mirabelle_47";
			locCameraFromToPos(1.25, 1.28, 0.71, false, 2.28, -0.20, 1.91);
		break;
		
		case "mirabelle_47":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_42";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				sld = characterFromId("Mary");
				sld.dialog.currentnode = "IslaMona_2";
				LAi_SetActorType(sld);
				LAi_ActorDialogDelay(sld, pchar, "", 0.0);
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					sld = characterFromId("Helena");
					sld.dialog.currentnode = "IslaMona_2";
					LAi_SetActorType(sld);
					LAi_ActorDialogDelay(sld, pchar, "", 0.0);
				}
				else
				{
					sld = characterFromId("Himenes_companion_1");
					sld.dialog.currentnode = "island_man_2";
					LAi_SetActorType(sld);
					LAi_ActorDialogDelay(sld, pchar, "", 0.0);
				}
			}
		break;
		
		case "mirabelle_48":
			dialog.text = "Signor Capitano!";
			link.l1 = "Ciao anche a te, bellezza. Non ti annoi, vero?";
			link.l1.go = "mirabelle_49";
		break;
		
		case "mirabelle_49":
			dialog.text = "Ah, Capitano! Da quando mi hai salvato da quella terribile casa, la mia vita ha acquisito colore e gioia.";
			link.l1 = "Sei felice?";
			link.l1.go = "mirabelle_50";
		break;
		
		case "mirabelle_50":
			dialog.text = "Certo! E mi piacerebbe condividere questa felicità con te... Ti aspetterò nella tua stanza, al piano di sopra.";
			link.l1 = "Che donna...";
			link.l1.go = "mirabelle_51";
		break;
		
		case "mirabelle_51":
			DialogExit();
			LAi_SetActorType(npchar);
		    npchar.dialog.currentnode = "mirabelle_40";
			DoQuestFunctionDelay("IslaMona_ChurchReloadToRoom", 0.5);
			pchar.questTemp.IslaMona.Mirabelle = "true";
		break;
		
		case "mirabelle_52":
			dialog.text = "Signor Capitano!";
			link.l1 = "Ciao anche a te, bellezza. Non ti stai annoiando, vero?";
			link.l1.go = "mirabelle_53";
		break;
		
		case "mirabelle_53":
			dialog.text = "Ah, Capitano! Da quando mi hai salvato da quella casa spaventosa, la mia vita ha guadagnato colore e gioia.";
			link.l1 = "Sei felice?";
			link.l1.go = "mirabelle_54";
		break;
		
		case "mirabelle_54":
			dialog.text = "Molto! Eccetto...";
			link.l1 = "Capisco, vuoi chiedermi qualcosa?";
			link.l1.go = "mirabelle_55";
		break;
		
		case "mirabelle_55":
			dialog.text = "Sì, Capitano! Vorrei... condividere la mia felicità con un certo uomo...";
			link.l1 = "Gli dispiacerà?";
			link.l1.go = "mirabelle_56";
		break;
		
		case "mirabelle_56":
			dialog.text = "No, no, Capitano. Saremmo felici insieme, ne sono sicuro. Solo... mi permetteresti?";
			link.l1 = "Tu più di chiunque altro meriti questo. Ma non unirò in matrimonio voi due, nemmeno chiedetelo!";
			link.l1.go = "mirabelle_57";
		break;
		
		case "mirabelle_57":
			dialog.text = "Ha-ha! Il mio gentiluomo! Grazie, Signor Capitano. Non so cosa dicono di te nel grande mondo, ma ho sempre visto in te la persona più gentile e luminosa.";
			link.l1 = "Buona fortuna a te, Mirabelle.";
			link.l1.go = "mirabelle_58";
		break;
		
		case "mirabelle_58":
			DialogExit();
			npchar.quest.rodgar = true;
		    npchar.dialog.currentnode = "mirabelle_42";
		break;
		
		// губернатор Картахены
		case "CartahenaMayor":
            dialog.text = "Maledetti ladrones! Comunque, il nostro corriere è già in viaggio verso Porto Bello. Presto arriverà la nostra squadra e...";
			link.l1 = TimeGreeting()+", vostra Altezza. È un piacere vedervi in una così bella dimora. Spero che la manterrete dopo la nostra partenza. Se fossi in voi, non contarei sulla squadra, inoltre non resteremo qui per più di tre giorni. Scommetto che capite che i nobili don di Porto Bello non arriveranno qui a aiutarvi così presto. Quindi, passiamo direttamente agli affari, non è vero?";
			link.l1.go = "CartahenaMayor_1";
		break;
		
		case "CartahenaMayor_1":
            dialog.text = "Parliamo già di affari? Guarda alla finestra! Guarda cosa stanno facendo i tuoi tagliagole nelle strade e nelle case!";
			link.l1 = "Oh, vostra Altezza, questo non è niente rispetto a quello che faranno se non siete abbastanza cooperativi. Spero che capiate chi sono questi uomini...";
			link.l1.go = "CartahenaMayor_2";
		break;
		
		case "CartahenaMayor_2":
            dialog.text = "So cosa è capace di fare l'infame pirata Charlie Prince! So chi è il suo capo! Col tempo, daremo fuoco al tuo covo di banditi su Hispaniola! Quanto costa?";
			link.l1 = "Non perdere parole, mio caro governatore. Faresti meglio a procurarmi 250 000 pesos.";
			link.l1.go = "CartahenaMayor_3";
		break;
		
		case "CartahenaMayor_3":
            dialog.text = "Cosa?! La tua insolenza non ha limiti! Questo è un furto!";
			link.l1 = "È un furto, ovviamente. Che altro potrebbe essere? Raduna i tuoi élite, i tuoi mercanti e commercianti, raccogli l'oro in un grande baule perché altrimenti... renderò la vita molto peggio per te e il tuo popolo.";
			link.l1.go = "CartahenaMayor_4";
		break;
		
		case "CartahenaMayor_4":
            dialog.text = "Maledetto pirata! Bastardo! Eretico! Vaffanculo!";
			link.l1 = "A causa della tua lingua sporca, aumento il riscatto fino a 300.000.";
			link.l1.go = "CartahenaMayor_5";
		break;
		
		case "CartahenaMayor_5":
            dialog.text = "BRUCIA NELL'INFERNO, FIGLIO DI PUTTANA!!!";
			link.l1 = "350 000. Vuoi continuare?";
			link.l1.go = "CartahenaMayor_6";
		break;
		
		case "CartahenaMayor_6":
            dialog.text = "Non c'è così tanto denaro in città!";
			link.l1 = "Menti. Non può essere. Siamo in grado di raccogliere almeno un milione qui, ma temo che non abbiamo abbastanza tempo per farlo. Pertanto sarò gentile e generoso. Conosci la somma. Vai a prenderla.";
			link.l1.go = "CartahenaMayor_7";
		break;
		
		case "CartahenaMayor_7":
            dialog.text = "Ti sto dicendo di nuovo, Charlie Prince: non esistono tali soldi a Cartagena!";
			link.l1 = "Oh... come puoi essere così noioso. Sciabola! Cerca intorno e porta qui tutti quelli che trovi. Cerca bene! E noi resteremo qui per ora, vostra grazia...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CartahenaInResidence");
		break;
		
		case "CartahenaMayor_8":
            dialog.text = "";
			link.l1 = "Ehi, signor 'Testardo'! Non hai cambiato idea riguardo alla raccolta di denaro nella buona città di Cartagena?... Cosa è successo, perché sei così serio all'improvviso?! Stai bene? Dovrei portarti un po' d'acqua?";
			link.l1.go = "CartahenaMayor_9";
		break;
		
		case "CartahenaMayor_9":
            dialog.text = "";
			link.l1 = "Per quanto capisco, queste due signore sono tua moglie e tua figlia, ho ragione? La terza ragazza sembra una serva, sembra che non te ne freghi niente di lei quindi non le faremo del male, ma queste due bellezze potrebbero attirare l'attenzione del mio fratello d'armi, il signor Cutlass. Sembra che gli piacciano, signore. E allora? Hai intenzione di gestire il riscatto?";
			link.l1.go = "CartahenaMayor_10";
		break;
		
		case "CartahenaMayor_10":
            dialog.text = "Io... Avrò bisogno di tempo.";
			link.l1 = "Aha! Ora stai parlando! Quindi chi è il bastardo qui? Non ti importava un cazzo dei miei uomini che terrorizzavano i tuoi cittadini, ma le tue due donne sono un altro paio di maniche, vero? Hai osato contrattare con me, stronzo? Ti mostrerò cosa significa contrariare Charlie Prince!";
			link.l1.go = "CartahenaMayor_10x";
		break;
		
		case "CartahenaMayor_10x":
            dialog.text = "";
			link.l1 = "Vai e raccogli il cazzo di riscatto. 350 000 e non un peso di meno. Hai un giorno. Noi resteremo qui a bere un po' di vino e a socializzare con queste dolci donne... Sii veloce, amico, o io e il mio amico qui, il signor Cutlass, potremmo innamorarci delle tue bellezze e poi dovrai pagare anche il loro riscatto. Avanti! Marciare!";
			link.l1.go = "CartahenaMayor_11";
		break;
		
		case "CartahenaMayor_11":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Mtraxx_CartahenaResidenceWait", 5.0);
		break;
		
		case "CartahenaMayor_12":
			AddMoneyToCharacter(pchar, 350000);
            dialog.text = "Prendi il tuo denaro insanguinato, Charlie Prince!";
			link.l1 = "Hai raccolto il riscatto? Splendido! Ma sei in ritardo di un'ora, mio caro governatore. Quest'ora extra mi ha dato a me e alla Cutlass la comprensione che le nostre vite sarebbero troppo noiose senza queste bellezze che sono state così gentili e loquaci con noi...";
			link.l1.go = "CartahenaMayor_13";
		break;
		
		case "CartahenaMayor_13":
            dialog.text = "Tu... tu!";
			link.l1 = "Ah, sei troppo nervoso a causa del tuo lavoro, amico mio. Stavo scherzando... Sciabola! Andiamo, stiamo partendo!";
			link.l1.go = "CartahenaMayor_14";
		break;
		
		case "CartahenaMayor_14":
            DialogExit();
			AddQuestRecord("Roger_9", "7");
			AddDialogExitQuestFunction("Mtraxx_CartahenaToFort");
		break;
		
		// Камилла
		case "camilla":
			PlaySound("Voice\English\hambit\Girls_3.wav");
            dialog.text = "Oh, quindi questo è Il Principe Charlie, il famoso pirata, il terrore del Sud Principale spagnolo!";
			link.l1 = RandSwear()+"Eh, non avevo idea di essere così popolare a Tortuga. Come ti chiami, dolce ragazza?";
			link.l1.go = "camilla_1";
		break;
		
		case "camilla_1":
            dialog.text = "Il mio nome è Camilla.";
			link.l1 = "Camilla... Conoscevo una ragazza con lo stesso nome in Francia. È stato così tanto tempo fa!";
			link.l1.go = "camilla_2";
		break;
		
		case "camilla_2":
			PlaySound("ambient\tavern\orijka_003.wav");
            dialog.text = "";
			link.l1 = "(vomitando) ... cazzo... Mi dispiace, principessa, ma il Principe è un po' ubriaco stasera. Quindi... ehm.. perché sei venuta da me?";
			link.l1.go = "camilla_3";
		break;
		
		case "camilla_3":
            dialog.text = "Per varie ragioni. O forse senza alcuna ragione.";
			link.l1 = "Dio, è troppo complicato. Sembri essere un mistero, ragazza.";
			link.l1.go = "camilla_4";
		break;
		
		case "camilla_4":
            dialog.text = "Ogni ragazza deve avere un mistero.";
			link.l1 = "Sembra che tu voglia che io risolva questo mistero. No? Sono un maestro nel risolvere i misteri delle ragazze, te lo giuro! Dovremmo andare in una taverna e bere un po' di vino? Ti farò avere la migliore delle leccornie!";
			link.l1.go = "camilla_5";
		break;
		
		case "camilla_5":
            dialog.text = "Mmm... Mi piacciono i tipi tosti. Ma non berrò vino al piano di sotto vicino a degli ubriaconi. Prendici una stanza, là berremo e parleremo.";
			link.l1 = RandSwear()+"Sei in forma! Seguimi!";
			link.l1.go = "camilla_6";
		break;
		
		case "camilla_6":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.mtraxx_retribution_tavern.win_condition.l1 = "locator";
			pchar.quest.mtraxx_retribution_tavern.win_condition.l1.location = "Tortuga_town";
			pchar.quest.mtraxx_retribution_tavern.win_condition.l1.locator_group = "reload";
			pchar.quest.mtraxx_retribution_tavern.win_condition.l1.locator = "reload4_back";
			pchar.quest.mtraxx_retribution_tavern.function = "Mtraxx_RetributionToTavern";
		break;
		
		case "camilla_7":
			PlaySound("Voice\English\hambit\Gr_officiant_1.wav");
            dialog.text = "Andiamo... Versalo, non far aspettare la signora!";
			link.l1 = "Certo, tesoro mio!";
			link.l1.go = "camilla_8";
		break;
		
		case "camilla_8":
			LAi_Fade("", "");
			PlaySound("ambient\tavern\krujki_005.wav");
			PlaySound("ambient\tavern\naliv_003.wav");
			PlaySound("ambient\tavern\glotok_001.wav");
			WaitDate("", 0, 0, 0, 1, 5);
            dialog.text = "Mmm... Solo a pensarci, sono qui tutto solo con Charlie Prince, a bere un ottimo vino...";
			link.l1 = "Ti godrai questo viaggio con me, oh te lo prometto! Charlie Prince è gentile e cortese con le signore che si sottomettono a lui. Ti sottometterai, principessa?";
			link.l1.go = "camilla_9";
		break;
		
		case "camilla_9":
            dialog.text = "Hi-hi... Certo, tesoro! Le tue promesse suonano così allettanti, lo sai...";
			link.l1 = "Ebbene, non perdiamo tempo allora, bellezza?";
			link.l1.go = "camilla_10";
		break;
		
		case "camilla_10":
            dialog.text = "Oh! Amo! Veri uomini!..";
			link.l1 = "...";
			link.l1.go = "camilla_11";
		break;
		
		case "camilla_11":
            DialogExit();
			pchar.GenQuest.FrameLockEsc = true;
			bDisableCharacterMenu = true;
			ResetSound();
			WaitDate("", 0, 0, 0, 2, 30);
			SetLaunchFrameFormParam("", "", 0, 5.1);
			SetLaunchFrameFormPic("loading\inside\censored1.tga");
			PlayStereoSound("sex\sex2.wav");
			LaunchFrameForm();
			if(IsEquipCharacterByArtefact(pchar, "totem_03")) 	
			{
				AddCharacterHealth(pchar, 6);
				AddCharacterMaxHealth(pchar, 1.0);
			}
			else AddCharacterHealth(pchar, 3);
			LAi_SetCurHPMax(pchar);
			DoQuestCheckDelay("Mtraxx_RetributionRoomSex", 5.1);
		break;
		
		case "camilla_12":
            dialog.text = "Mmm...";
			link.l1 = "Ti è piaciuto, mia principessa?";
			link.l1.go = "camilla_13";
		break;
		
		case "camilla_13":
            dialog.text = "Certo! Spero che anche tu mi abbia preso in simpatia.";
			link.l1 = "Eh! Anche la mia testa è ora cristallina!";
			link.l1.go = "camilla_14";
		break;
		
		case "camilla_14":
            dialog.text = "Principe, ho una richiesta per te. Mi aiuterai?";
			link.l1 = "Prenderò una stella dal cielo per te, ah-ah! Vai avanti.";
			link.l1.go = "camilla_15";
		break;
		
		case "camilla_15":
            dialog.text = "Devo arrivare a La Vega, per vedere Tyrex. Ho paura di lui, ma voi fate affari insieme. Per favore portami da lui.";
			link.l1 = "Guarda questo! E perché una dolce e fragile ragazza vorrebbe vedere il Custode del Codice?";
			link.l1.go = "camilla_16";
		break;
		
		case "camilla_16":
            dialog.text = "Questa dolce e fragile ragazza vorrebbe fare qualche soldo. Mio padre e i miei fratelli non mi hanno lasciato molte monete. Tyrex può risolvere questo.";
			link.l1 = "Oh davvero? E come? Vuoi un indizio per un galeone spagnolo? Ah-ah!";
			link.l1.go = "camilla_17";
		break;
		
		case "camilla_17":
            dialog.text = "Saccheggiare carovane e città è un affare da uomini tosti, proprio come te, tesoro. Ho un altro affare per Marcus. Lui compra e vende informazioni, giusto? Ho qualcosa... Non c'è modo che io possa usarlo da solo, ma lui potrebbe. Sarò abbastanza felice solo di ottenere un piccolo interesse da esso.";
			link.l1 = "Interessante! Raccontami di più.";
			link.l1.go = "camilla_18";
		break;
		
		case "camilla_18":
            dialog.text = "Mh... Non lo so...";
			link.l1 = "Oh, suvvia. Considerami come la mano destra di Tyrex, ho scavato molto per lui fino ad ora, fidati di me. Se le tue informazioni valgono la pena - le comprerò io stesso.";
			link.l1.go = "camilla_19";
		break;
		
		case "camilla_19":
            dialog.text = "Bene. Ti dirò di più, ma nessun dettaglio finché non ricevo i soldi. Affare, tesoro?";
			link.l1 = "Certo, bella. Charlie Prince non frega i suoi partner... capisci cosa intendo, ah-ah-ah! Vai avanti, sono tutto orecchie.";
			link.l1.go = "camilla_20";
		break;
		
		case "camilla_20":
            dialog.text = "... Mio padre era il capitano di uno schooner mercantile. Un giorno, in qualche modo venne a sapere di un vecchio insediamento minerario spagnolo situato nel profondo delle giungle del Maine. Vent'anni fa fu distrutto da un terremoto. I minatori lo abbandonarono e i passaggi segreti furono dimenticati. Tranne uno. Mio padre lo trovò\nPrese i miei fratelli e una guida là e trovarono il posto pieno di oro estratto e fuso anni prima. Un sacco di oro. Almeno un milione di pesos. Padre tornò alla nave per poter ottenere uomini per trasportare l'oro ma fu scioccato nello scoprire che era sparita. Sembra che il suo primo ufficiale avesse iniziato una rivolta e lo avessero lasciato con i miei fratelli sulle spiagge deserte\nCostruirono una barca lunga e navigarono lungo la costa alla disperata ricerca di un luogo abitato, ma... (singhiozza) una tempesta li colpì e i miei (singhiozza) fratelli morirono. Padre sopravvisse ma non visse a lungo dopo essere tornato a casa - la morte dei miei fratelli lo stava uccidendo giorno dopo giorno. Prima di morire, fece una mappa e me la diede\nMi disse che quando mi fossi sposata, mio marito avrebbe dovuto andare là, prendere l'oro e avremmo vissuto come re. Certo che lo faremo, ma non lascerò mai il mio uomo entrare in quelle maledette giungle. Non di nuovo! Un milione di pesos, disse mio padre, ma semplicemente non è il mio campo. Un premio del genere, solo i migliori e più duri degli uomini possono ottenerlo - uomini come Marcus Tyrex. Ecco perché sto andando a incontrarlo.";
			link.l1 = "Quanto vuoi per la mappa?";
			link.l1.go = "camilla_21";
		break;
		
		case "camilla_21":
            dialog.text = "Duecento dobloni d'oro. È niente rispetto al premio. Tyrex accetterà, ne sono sicuro. È ricco quanto Crasso.";
			link.l1 = "Eh! E se tutto questo è solo un inganno?";
			link.l1.go = "camilla_22";
		break;
		
		case "camilla_22":
            dialog.text = "Sembrò suicida? Cercare di attraversare Tyrex? Tesoro, meglio vivere in povertà che non vivere affatto. Quindi mi porterai lì? Per favore...";
			link.l1 = "Dove si trova la mappa? Me la mostrerai?";
			link.l1.go = "camilla_23";
		break;
		
		case "camilla_23":
            dialog.text = "Il mio prete lo tiene al sicuro. Te lo mostrerò per 200 dobloni.";
			link.l1 = "Molto bene! Lo compro. Gli stranieri nelle taverne a volte chiedono molto di più per la spazzatura.";
			link.l1.go = "camilla_24";
		break;
		
		case "camilla_24":
            dialog.text = "Lo sei? È vero, tesoro? Sono così felice di non andare a La Vega! Per essere onesta, temo Marcus. Ho paura anche di te, a proposito... ma un po' meno.";
			link.l1 = "Una dolce piccola ragazza non ha bisogno di temermi. Dove dovrei portare i soldi?";
			link.l1.go = "camilla_25";
		break;
		
		case "camilla_25":
            dialog.text = "Facciamo un accordo: trovatemi nella nostra chiesa ogni giorno dalle dieci del mattino all'una del pomeriggio. Mi sentirò molto più al sicuro sotto la protezione di questo luogo sacro. Concluderemo il nostro accordo lì.";
			link.l1 = "Mi temi ancora? Ah-ah! Non farlo, Camilla, non ti tradirò. Charlie Prince non farebbe una cosa così vile per duecento dobloni, inoltre voglio aiutarti.";
			link.l1.go = "camilla_26";
		break;
		
		case "camilla_26":
            dialog.text = "Meraviglioso. Allora ti aspetterò, bello... Grazie per l'incredibile tempo trascorso insieme stasera! Sono così felice che ci siamo incontrati!";
			link.l1 = "A presto, bella.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionOutRoom");
		break;
		
		case "camilla_27":
			PlaySound("Voice\English\hambit\Girls_3.wav");
            dialog.text = "Allora? Hai portato i soldi, dolcezza?";
			if (PCharDublonsTotal() >= 200) // belamour legendary edition
			{
				link.l1 = "Sì. Prendi il tuo oro e ora dammi la mappa.";
				link.l1.go = "camilla_28";
			}
			else
			{
				link.l1 = "Sono proprio dietro di esso.";
				link.l1.go = "camilla_27x";
			}
		break;
		
		case "camilla_27x":
            DialogExit();
			npchar.dialog.currentnode = "camilla_27";
		break;
		
		case "camilla_28":
			RemoveDublonsFromPCharTotal(200); // belamour legendary edition
			GiveItem2Character(pchar, "mapEnrico"); 
            dialog.text = "Grazie, tesoro... Tieni, prendilo. Giuro sulla memoria di mio padre - questa mappa non è un falso, ti condurrà direttamente dove dovresti andare...";
			link.l1 = "Bene, dolcezza. Che ne dici di festeggiare il nostro accordo proprio come l'ultima volta?";
			link.l1.go = "camilla_29";
		break;
		
		case "camilla_29":
            dialog.text = "Vorrei, Principe, ma mi sto preparando per una confessione davanti al mio prete, quindi sono obbligato a stare lontano da qualsiasi tentazione in questo momento. Facciamolo la prossima volta.";
			link.l1 = "Eh, mi stai prendendo in giro, ragazza. Bene! Non c'è tempo da perdere: stiamo per levare l'ancora. Giuro che raddoppierò il tuo interesse se la mappa di tuo padre mi porterà davvero all'oro.";
			link.l1.go = "camilla_30";
		break;
		
		case "camilla_30":
            dialog.text = "Sei così generoso, tesoro. Buon viaggio!";
			link.l1 = "Yo-ho-ho!";
			link.l1.go = "camilla_31";
		break;
		
		case "camilla_31":
            DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("Roger_10", "2");
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			pchar.quest.mtraxx_retribution_carataska.win_condition.l1 = "location";
			pchar.quest.mtraxx_retribution_carataska.win_condition.l1.location = "shore10";
			pchar.quest.mtraxx_retribution_carataska.function = "Mtraxx_RetributionCarataska";
			pchar.questTemp.Mtraxx.Retribution = "carataska";
		break;
		
		case "camilla_sleep":
            dialog.text = "I tuoi bastardi hanno ucciso mio padre e i miei fratelli. Il tuo attacco a Cartagena ha portato dolore in ogni famiglia lì. Spero che tu abbia paura ora, tanta paura quanto noi, cittadini di Cartagena, quando i tuoi bruti si divertivano per le strade e nelle case. Brucerai all'inferno, Charlie Prince.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep4");
		break;
		
		// дон Энрико - народный мститель
		case "enrico":
			PlaySound("Voice\English\LE\Zorro\Don_Enriko_01.wav");
            dialog.text = "Ci sono così poche cose in questo mondo che mi danno gioia quanto guardare i topi nella scatola che si lacerano a vicenda!\nSopravvive solo il topo più forte e più disgustoso. Poi tutto quello che devi fare è strizzarlo...";
			link.l1 = "Argh! Chi sei?!";
			link.l1.go = "enrico_1";
		break;
		
		case "enrico_1":
			PlaySound("Voice\English\LE\Zorro\Don_Enriko_02.wav");
            dialog.text = "Sono don Enrico. La feccia inglese mi chiama Volpe, gli olandesi mi chiamano Vos, i francesi mi chiamano Renaud. Ma preferisco il mio soprannome di casa spagnola - Zorro. Punisco il male che tortura e terrorizza la gente comune, la parte meno protetta del popolo\nQuesto processo oggi giudicherà quattro pirati di Marcus Tyrex: Jeffry il Coraggioso, Pelly la Sciabola, Luke il Leprechaun e Charlie Principe - questi banditi sono responsabili per un massacro a Merida e Cartagena. L'ultimo bastardo chiamato Jean il Bello non si è presentato qui, deve essere il più astuto del tuo gruppo.";
			link.l1 = "Cosa?!";
			link.l1.go = "enrico_2";
		break;
		
		case "enrico_2":
            dialog.text = "Sei un pezzo di merda, Charlie Prince, ma non sei un idiota. Ho capito già, penso. È una trappola per voi tutti preparata da me con l'aiuto di false mappe, documenti, parole e promesse di oro e argento. Vi ho attirato tutti in queste segrete dove vi siete distrutti a vicenda guidati dai vostri disgustosi difetti: invidia, avidità, meschinità e mancanza di scrupoli. È stata davvero una giusta nemesi!";
			link.l1 = "Camilla... Avrei dovuto capire che c'era qualcosa di strano in quella ragazza!";
			link.l1.go = "enrico_3";
		break;
		
		case "enrico_3":
            dialog.text = "Una ragazza di nome Camilla viveva una vita tranquilla a Cartagena con suo padre e i suoi fratelli, stava per sposarsi quando tu e i tuoi diavoli avete attaccato la città. I tuoi pirati hanno ucciso tutti coloro che le erano vicini, così ha giurato di fare tutto il possibile per vendicarli. È stato un ruolo difficile da interpretare per lei. Ha persino dovuto dormire con un bastardo responsabile della morte della sua famiglia. Temo di immaginare cosa provasse durante l'atto\nLa povera ragazza ha passato giorni in chiesa a pregare per il perdono. Ha donato i dobloni insanguinati che le hai dato alle vittime che hanno sofferto di più dal tuo attacco. Ora è in un monastero, povera anima. Hai distrutto la sua vita, feccia! Pensa a questo! Pensa a quante Camillas, Isabelas, Rositas hai violentato e reso vedove! Quanti Juans, Carloses, Pedros avete bastardi ucciso e torturato!\nRicorda Merida! Ricorda come hai promesso al capo della città di non incendiarla e poi hai bruciato tutto al suolo!";
			link.l1 = "Non ho mai voluto farlo! Quando ho lasciato la residenza, il fuoco era già ovunque. Non ho ordinato questo...";
			link.l1.go = "enrico_4";
		break;
		
		case "enrico_4":
            dialog.text = "Sei responsabile per le azioni dei tuoi pirati. Uomini morti pendono dal tuo collo e presto ti trascineranno all'inferno!";
			link.l1 = "Allora vieni! Eh? Combatti con me! Questo è quello che vuoi, vero?! Facciamolo allora!";
			link.l1.go = "enrico_5";
		break;
		
		case "enrico_5":
            PlaySound("Voice\English\LE\Zorro\Don_Enriko_03.wav");
            if (CharacterIsAlive("Tonzag") && CheckPassengerInCharacter(pchar, "Tonzag"))
			{
				dialog.text = "No, Charlie Prince. Non cercare di afferrare la tua arma, è inutile... Potrei ucciderti facilmente, ma una morte rapida non è abbastanza per un bastardo come te. Resterai in questa segreta per sempre. La porta che hai usato per entrare qui è bloccata da una pietra fuori, la porta dietro di me sarà bloccata anche, oltre ci sono anche robuste sbarre a proteggerla. Questo è tutto, non c'è via d'uscita tranne queste due porte\nChe diavolo... Ho bloccato tutte le porte!";
				link.l1 = "Cosa sta succedendo...";
				link.l1.go = "exit";
				AddDialogExitQuest("Mtraxx_RetributionEnricoAndTonzag");
			}
			else
			{
				dialog.text = "No, Charlie Prince. Non cercare di prendere la tua arma, è inutile... Potrei ucciderti facilmente, tuttavia una morte rapida non è abbastanza per un bastardo come te. Resterai in questa prigione per sempre. La porta da cui sei entrato è bloccata da una pietra all'esterno, la porta dietro di me sarà bloccata anche lei, inoltre ci sono anche robuste sbarre a proteggerla. Questo è tutto, non c'è via d'uscita tranne queste due porte\nC'è acqua sotto, quindi avrai abbastanza tempo per pensare alle tue azioni. Qui da solo, nel buio, forse, ti pentirai di quello che hai fatto prima di morire di fame o impazzire\nUna cosa dell'ultimo minuto - il tesoro sottostante è un falso. I lingotti d'oro non sono altro che piombo colorato. I dobloni sono veri però, ma ce ne sono solo pochi, abbastanza da coprire le rocce all'interno dei cofani. Una fine degna per i pirati, eh? Vi siete uccisi a vicenda per un tesoro falso, Principe. Addio ora. Prega per la tua anima peccatrice, Charlie Prince, se ti ricordi ancora come...";
		// belamour legendary edition -->
				link.l1 = "Ho appena ucciso l'intera avanguardia di Marcus Tyrex! Pensi che queste sbarre arrugginite mi fermeranno?! Le romperò con la tua stessa testa!";
				link.l1.go = "enrico_5a";
				link.l2 = "Forse me lo meritavo. Ma non mi arrenderò, mi senti?! Troverò un modo, lo faccio sempre!";
				link.l2.go = "enrico_5b";
			}
		break;
		
		case "enrico_5a":
			AddCharacterHealth(pchar, 5);
			AddCharacterExpToSkill(pchar, "FencingL", 400);
			AddCharacterExpToSkill(pchar, "FencingS", 400);
			AddCharacterExpToSkill(pchar, "FencingH", 400);
			AddCharacterExpToSkill(pchar, "Pistol", 400);
            DialogExit();
			AddDialogExitQuestFunction("Mtraxx_RetributionEnricoGo");
		break;
		
		case "enrico_5b":
			AddCharacterExpToSkill(pchar, "Leadership", 1200);
			ChangeCharacterComplexReputation(pchar, "nobility", 15);
            DialogExit();
			AddDialogExitQuestFunction("Mtraxx_RetributionEnricoGo");
		break;
		// <-- legendary edition
		
		case "enrico_Tonzag_1":
			dialog.text = "Hai ragione, la porta è affidabile, anche se vecchia. Grazie per non aver abbassato il cancello, mi avrebbe ritardato. Ma non per molto.";
			link.l1 = "Hercule Tonzag, Gaston Calvo! Avrei dovuto sospettare che qualcuno come te si schierasse con il Principe e tutta la sua cricca. Fortunato io a incontrarti qui, anche.";
			link.l1.go = "enrico_Tonzag_2";
			sld = CharacterFromID("Zorro");
			CharacterTurnToLoc(sld, "quest", "door");
		break;
		
		case "enrico_Tonzag_2":
			dialog.text = "Fortunato, dici? Beh, se hai fretta di morire... Anche se pensavo che non lo fossi, visto che lo hai lasciato morire di fame invece di affrontarlo.";
			link.l1 = "Mi accusi di codardia? Quanto sei sciocco. Come ho detto al Principe, la morte è una punizione troppo facile per lui. Non è all'altezza di me.";
			link.l1.go = "enrico_Tonzag_3";
		break;
		
		case "enrico_Tonzag_3":
			dialog.text = "E tu non sei alla mia altezza, Don.";
			link.l1 = "Dieci anni fa? Certamente. Ora? Difficilmente. Inoltre...";
			link.l1.go = "enrico_Tonzag_4";
		break;
		
		case "enrico_Tonzag_4":
			dialog.text = "Inoltre cosa? Cos'è questa pausa drammatica? Anche se, considerando la tua maschera carnevalesca... Non è un po' presto per darmi per spacciato?";
			link.l1 = "Hai rotto la porta, ma la sola forza bruta non basterà con me. Come sono i tuoi riflessi? La tua vista? Con un solo occhio. Io ne ho ancora entrambi.";
			link.l1.go = "enrico_Tonzag_5";
		break;
		
		case "enrico_Tonzag_5":
			dialog.text = "Ebbene, per ora, comunque. Heh-heh.";
			link.l1 = "Per Porto Bello, meriti un tormento peggiore del Principe!";
			link.l1.go = "enrico_Tonzag_6";
		break;
		
		case "enrico_Tonzag_6":
			dialog.text = "Oh, quindi hai sentito quello che ho fatto? Immagino che continueranno a farne pettegolezzi tra i tuoi per un po'. Allora sai quello che ho passato.";
			link.l1 = "Sei vecchio, Tonzag, e questa volta la tua arroganza sarà la tua rovina. E sì, non ne ho solo sentito parlare - Cartagena, Merida sono opera tua. Proprio come Porto Bello.";
			link.l1.go = "enrico_Tonzag_7";
		break;
		
		case "enrico_Tonzag_7":
			dialog.text = "L'avrei preso come un complimento, ma no, non è stato un mio lavoro. Anche se da lontano potrebbe sembrare simile. Troppo dilettantesco. D'altra parte, anche a Porto Bello, ci sono stati... incidenti.";
			link.l1 = "Incidenti?! Quel giorno, una persona è morta... E considerando che hai iniziato quel massacro, ti incolpo ancora, anche se non hai ucciso tutti personalmente. Ti incolpo per ogni 'incidente'.";
			link.l1.go = "enrico_Tonzag_8";
		break;
		
		case "enrico_Tonzag_8":
			dialog.text = "Una persona, dici... Quel giorno sono morti in molti. Sii specifico.";
			link.l1 = "Veramente, non hai cuore se puoi dire questo! Ma risponderò: quello che non avresti dovuto uccidere. Mio padre, Don de la Vega. Se fosse vivo, non avrei preso questa strada, e voi tutti sareste ancora vivi.";
			link.l1.go = "enrico_Tonzag_9";
		break;
		
		case "enrico_Tonzag_9":
			dialog.text = "Chiudi il becco, cucciolo. Mia cara moglie... è morta là.";
			link.l1 = "Ti aspetti condoglianze? Non le otterrai. Questa è la punizione del Signore per te. Sembra che tu abbia un cuore - piccolo e nero. E lo troverò con la mia lama.";
			link.l1.go = "enrico_Tonzag_10";
		break;
		
		case "enrico_Tonzag_10":
			dialog.text = "Oh, il dramma riguardo al mio cuore. Ti sbagli se pensi di aver visto peggio di quanto ho visto io.";
			link.l1 = "Pensi che io sia solo un giovane ricco viziato che sperpera denaro? Sappi questo: non ho speso un doblone per il gioco d'azzardo o le donne! Ho gettato tutto nella lotta contro individui come te e ho dedicato la mia vita a questo!";
			link.l1.go = "enrico_Tonzag_11";
		break;
		
		case "enrico_Tonzag_11":
			dialog.text = "E per cosa? Non sembra molto efficace. Le rotte commerciali sono ancora piene di pirati. Sei solo nella tua crociata. E loro sono una legione intera.";
			link.l1 = "Qualcuno deve farlo. Almeno qualcuno. E forse, uccidendo solo un capitano pirata, salverò qualche vita.";
			link.l1.go = "enrico_Tonzag_12";
		break;
		
		case "enrico_Tonzag_12":
			dialog.text = "Stolto. Idealista. E... in un certo senso, nobile, direi, se non fosse per i tuoi metodi. Disonorato, come i tuoi nemici. Alla fine, tu sei... non migliore.";
			link.l1 = "Non predicare a me! L'onore è per coloro che seguono le sue leggi. Ti capisco. Penso come te. E punisco.";
			link.l1.go = "enrico_Tonzag_13";
		break;
		
		case "enrico_Tonzag_13":
			dialog.text = "Hai ragione. Insegnarti è inutile. Quindi, non ci separeremo pacificamente. Ma non mi importa niente di te, Don Enrico. Non vali nemmeno il mio tempo.";
			link.l1 = "Cosa intendi...";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionEnricoAndTonzag2");
		break;
		
		case "enrico_Tonzag_14": // после выстрела в Зорро в подземелье
            dialog.text = "Stai bene, Capitano? Ti avevo avvertito di stare attento. Avrei dovuto ascoltare il mio istinto.";
			link.l1 = "Sì, sto bene. Grazie, Hercule. Solo un po'...";
			link.l1.go = "enrico_Tonzag_15";
		break;
		
		case "enrico_Tonzag_15":
            dialog.text = "...sorpreso? Non aver paura di ammetterlo - è normale per qualcuno della tua età e in una situazione del genere. Inoltre, quel Don è un buon manipolatore.";
			link.l1 = "Eh sì. Anche se, sembrava aver paura di te. Questo mi ha sorpreso. Ma mi ha anche riportato alla realtà. A proposito, è ancora vivo? Sembra di sì. Non dovresti stare con le spalle rivolte verso di lui.";
			link.l1.go = "enrico_Tonzag_16";
		break;
		
		case "enrico_Tonzag_16":
            dialog.text = "Vivo, ma stordito. Sta tornando in sé. Avrei dovuto puntare alla testa, non al torso - sembra che il nostro nobile hidalgo indossi sotto il cappotto una corazza leggera ma robusta. Ehi, anche Fleetwood si è attenuto a un semplice giubbotto. Altrimenti, ci sarebbe già una pozza di sangue qui.";
			link.l1 = "E come sei finito qui? Nello stesso posto come lui?";
			link.l1.go = "enrico_Tonzag_17";
		break;
		
		case "enrico_Tonzag_17":
            dialog.text = "Non c'è tempo per questo ora. Sarà di nuovo in piedi presto. Per ora, solleveremo questo cancello.";
			link.l1 = "Noi... cosa?? Certo, potresti essere Ercole, ma...";
			link.l1.go = "enrico_Tonzag_18";
		break;
		
		case "enrico_Tonzag_18":
            dialog.text = "Gli uomini della mia giovinezza erano forgiati duri. Queste cerniere hanno perni corti. Dai, dammi una mano, Capitano - potrei essere Ercole, ma sto invecchiando.";
			link.l1 = "Bene, a tre! E solleva!";
			link.l1.go = "enrico_Tonzag_19";
		break;
		
		case "enrico_Tonzag_19":
            DialogExit();
			locCameraSleep(true);
			LAi_FadeLong("Mtraxx_RetributionEnricoAndTonzag6", "");
		break;
		
		case "enrico_Tonzag_20": // окружили Зорро
            dialog.text = "Pensi di aver rovinato tutti i miei piani e vinto? È stato inaspettato, certo, ma ho ancora tenuto conto di molto!";
			link.l1 = "Come quella leggera corazza sotto i tuoi vestiti. Perché quella e non una completa sopra? Solo per sfoggiare il tuo cappotto?";
			link.l1.go = "enrico_Tonzag_21";
		break;
		
		case "enrico_Tonzag_21":
            dialog.text = "Non sono una donzella, Principe. I miei motivi sono puramente pratici - un'armatura completa restringe troppo i miei movimenti. Ognuno ha il suo approccio.";
			link.l1 = "Eppure eccomi qui, un francese, già abituato a indossare corazze, a differenza di uno spagnolo. L'ironia. Quindi, cosa succede ora? Non sei riuscito a intrappolarci. Hai preparato tutto... Un duello rientrava nelle possibilità? O la spada - e anche la corazza - servono a tutto tranne che per i veri combattimenti?";
			link.l1.go = "enrico_Tonzag_22";
		break;
		
		case "enrico_Tonzag_22":
            dialog.text = "Stai cercando di chiamarmi anche un codardo? Come ho detto, meriti una lunga sofferenza, non la morte in un duello. Qual è il punto se le tue anime non avranno tempo di sopportare e comprendere tutti i tuoi peccati qui, sulla Terra?";
			link.l1 = "La strada per l'inferno è lastricata di buone intenzioni, come si suol dire... E tormentare le tue vittime non macchierebbe la tua stessa anima?";
			link.l1.go = "enrico_Tonzag_23";
		break;
		
		case "enrico_Tonzag_23":
            dialog.text = "Mai. Mai e poi mai. Perché rimango fedele a me stesso e ai miei principi.";
			link.l1 = "Aha, non come noi. Hai parlato tanto di come siamo spazzatura vile senza un briciolo di onore, quindi... perché non essere all'altezza delle tue aspettative? Ci occuperemo di te da soli. Insieme.";
			link.l1.go = "enrico_Tonzag_24";
			link.l2 = "Ho una proposta per te, Don Enrico. Ti sfido a un duello, qui e ora. Come nobile a nobile.";
			link.l2.go = "enrico_Tonzag_26";
		break;
		
		case "enrico_Tonzag_24":
            dialog.text = "Mm-m. Altrimenti non avresti speranze. Tonzag sarà ovviamente complicato... Quindi mi occuperò di te per primo.";
			link.l1 = "Come se ti avrebbe lasciato fare una cosa del genere.";
			link.l1.go = "enrico_Tonzag_25";
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;
		
		case "enrico_Tonzag_25":
            DialogExit();
			EndQuestMovie();
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Tonzag");
			LAi_SetImmortal(sld, false);
			LAi_SetCheckMinHP(sld, 1, true, "TonzagRanen");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			sld = CharacterFromID("Zorro");
			LAi_SetImmortal(sld, false);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "Mtraxx_RetributionEnricoAndTonzag7");
		break;
		
		case "enrico_Tonzag_26":
            dialog.text = "Tu? Un nobile? Forse sei un “principe”, ma dubito che ci sia una goccia di sangue nobile in te.";
			link.l1 = "Hai rivelato il tuo vero nome a me. Rivelerò il mio. Sono Charles de Maure. E ci siamo insultati a vicenda l'onore abbastanza che ognuno di noi ha il diritto di chiedere soddisfazione. Difenditi, Don Enrico.";
			link.l1.go = "enrico_Tonzag_27";
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			AddCharacterExpToSkill(pchar, "Leadership", 300);
		break;
		
		case "enrico_Tonzag_27":
            dialog.text = "Ma non pentirti della tua decisione più tardi.";
			link.l1 = "Mi sono pentito di molte decisioni nella mia vita, ma questa non sarà una di quelle. In guardia!";
			link.l1.go = "enrico_Tonzag_28";
		break;
		
		case "enrico_Tonzag_28":
			DialogExit();
			EndQuestMovie();
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Tonzag");
			LAi_SetImmortal(sld, true);
			LAi_SetActorType(sld);
			
			sld = CharacterFromID("Zorro");
			LAi_SetImmortal(sld, false);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "Mtraxx_RetributionEnricoAndTonzag7");
		break;
		
		case "enrico_Tonzag_29": // после победы над Зорро
            dialog.text = "Stai bene, Capitano? Il nostro nobile hidalgo non indossava solo una corazza, aveva anche avvelenato la sua lama. Prendi questo. Quando cammino nella giungla porto sempre un paio con me - non si sa mai quando un serpente potrebbe mordere o un pellerossa potrebbe lanciare un dardo avvelenato.";
			link.l1 = "Grazie, Ercole. Sto bene. Il tuo arrivo tempestivo mi ha aiutato a riprendere le forze.";
			link.l1.go = "enrico_Tonzag_30";
			GiveItem2Character(PChar, "potion3");
			LAi_UseAtidoteBottle(pchar);
			LAi_UseAtidoteBottle(npchar);
		break;
		
		case "enrico_Tonzag_30":
            dialog.text = "Non menzionarlo. Andiamo, ti farò uscire da qui - ha menzionato di bloccare l'ingresso con delle pietre. Ho trovato un altro passaggio, una scorciatoia.";
			link.l1 = "Dimmi, Hercule... cosa è successo esattamente a Porto Bello? E quando?";
			link.l1.go = "enrico_Tonzag_31";
		break;
		
		case "enrico_Tonzag_31":
            dialog.text = "Non ho voglia di parlarne oggi. Ma forse un giorno, davanti a un bicchiere di vino o qualcosa di più forte. Per ora, usciamo da qui - il ragazzino aveva ragione, sto invecchiando. Voglio riposare sulla nave.";
			link.l1 = "Allora mostra la via.";
			link.l1.go = "enrico_Tonzag_32";
		break;
		
		case "enrico_Tonzag_32":
            DoQuestReloadToLocation("Shore10", "goto", "goto2", "Mtraxx_RetributionEnricoAndTonzag8");
		break;
		
		case "mishelle_sleep":
            dialog.text = "Dimmi, fratello - come sei diventato una tale abominio? Quando ti ho detto di familiarizzare con i pirati, non intendevo bruciare città, uccidere civili innocenti e torturare donne. Anche una guerra può essere combattuta con onore e dignità\nSei una vergogna per la nostra famiglia. È un bene che nostro padre non sia qui: sarebbe morto di vergogna sapendo che suo figlio era diventato un pirata e un bandito!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep5");
		break;
		
		case "mishelle_sleep_1":
            dialog.text = "Fratello! Fratello!\nMi senti?\nC'è un passaggio dietro una delle due porte. La porta può essere aperta. Una chiave è vicino a te!\nTrovala sulle scale. Sulle scale!..";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep7");
		break;
		
		case "terrax_sleep":
            dialog.text = "Ha-ha-ha, ciao là mio coraggioso tagliagole! Perché sei così triste? Il mare, l'oro, il rum e le donne - cosa ti manca ancora? Ricordi il nostro primo incontro? Ti dissi allora - ho bisogno di uomini che non temano l'odore della polvere da sparo o di prosciugare i fiumi rossi. Hai superato ogni mia speranza! Sei diventato un vero pirata, Charlie Prince! Ha-ha-ha!";
			link.l1 = "";
			link.l1.go = "terrax_sleep_1";
			locCameraSleep(false);
		break;
		
		case "terrax_sleep_1":
            dialog.text = "Un vero cazzo di pirata! Ah-ah-ha-ha!";
			link.l1 = "";
			link.l1.go = "terrax_sleep_2";
		break;
		
		case "terrax_sleep_2":
			Mtraxx_RetributionSleepSkeletons();
            dialog.text = "Ua-ha-ha-ha-ha-ha!!!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep6");
		break;

		// belamour legendary edition -->
		case "SlavesTrader":
            dialog.text = "Chi sei? Cosa stai facendo qui? Rispondi subito!";
			link.l1 = "Sono di Fadey, sono venuto per un lotto di ossa nere. Avrebbe dovuto avvertirti.";
			link.l1.go = "SlavesTrader_1";
		break;
		
		case "SlavesTrader_1":
            dialog.text = "Hah! Non sudare la pelle, amico. Ti abbiamo riconosciuto, Moscovit ha dato una descrizione in grande dettaglio. Ha anche chiesto di non offenderti per il prezzo. Quindi, tenendo conto del pagamento anticipato già effettuato da te 10 000 argento. O, se paghi in oro, allora solo 50 dobloni. Allora, cosa hai deciso? Non tirare la coda al gatto!";
			if(PCharDublonsTotal() >= 50)
			{
				link.l1 = "Pagherò 50 dobloni. È più redditizio.";
				link.l1.go = "SlavesTrader_Dub";
			}
			if(sti(Pchar.money) >= 10000)
			{
				link.l2 = "Pagherò 10 000 pesos.";
				link.l2.go = "SlavesTrader_P";
			}
			link.l3 = "Mi dispiace, ma al momento non posso permettermi schiavi.";
			link.l3.go = "SlavesTrader_X";
		break;
		
		case "SlavesTrader_Dub":
			RemoveDublonsFromPCharTotal(50);
            dialog.text = "Eccellente. Segnala ai tuoi uomini di prendere la merce.";
			link.l1 = "Certo.";
			link.l1.go = "SlavesTrader_End";
		break;
		
		case "SlavesTrader_P":
			AddMoneyToCharacter(pchar, -10000);
            dialog.text = "Questo è fantastico. Fai segno ai tuoi uomini di prendere la merce.";
			link.l1 = "Certo.";
			link.l1.go = "SlavesTrader_End";
		break;
		
		case "SlavesTrader_End":
			DialogExit();
			AddQuestRecord("Roger_3", "25");
            pchar.questTemp.Mtraxx.GiveMeSlaves = "Deal";
			SetCharacterGoods(pchar, GOOD_SLAVES, (GetCargoGoods(pchar, GOOD_SLAVES) + 50));
			Log_Info("Fifty slaves shipped to "+PChar.Ship.Name);
			for(i=1; i<=3; i++)
			{
				sld = characterFromId("Mtraxx_SlavesSeller"+i);
				ChangeCharacterAddressGroup(sld, "none", "", "");
				sld.lifeday = 0;
			}
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation("Shore29")], false); 
			DeleteAttribute(&locations[FindLocation("Shore29")],"DisableEncounters"); //энкаунтеры открыть
		break;
		
		case "SlavesTrader_X":
            dialog.text = "Beh, come desideri. Ci sarà sempre un acquirente per questo prodotto. Ci vediamo, amico.";
			link.l1 = "Addio.";
			link.l1.go = "SlavesTrader_EndX";
		break;
		
		case "SlavesTrader_EndX":
			DialogExit();
			AddQuestRecord("Roger_3", "26");
			pchar.questTemp.Mtraxx.GiveMeSlaves = "WithoutSlaves";
			for(i=1; i<=3; i++)
			{
				sld = characterFromId("Mtraxx_SlavesSeller"+i);
				ChangeCharacterAddressGroup(sld, "none", "", "");
				sld.lifeday = 0;
			}
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation("Shore29")], false); 
			DeleteAttribute(&locations[FindLocation("Shore29")],"DisableEncounters"); //энкаунтеры открыть
		break;
		// диалог Гаспара Златозубого Xenon
		case "GasparGold_meeting":
            dialog.text = "Saluti, Capitano. Se non mi sbaglio, tu sei Charlie Prince? Non preoccuparti, le mie mura non hanno orecchie. Onestamente, non mi importa come ti chiami. Ciò che conta è che mi sei stato raccomandato, il che significa che possiamo fare affari.";
			link.l1 = "Saluti anche a te, Gaspard 'Dentidoro'. D'altronde, non mi importa davvero come ti chiami. Ho sentito dire che potresti essere interessato a comprare alcuni gingilli?";
			link.l1.go = "GasparGold_meeting_01";
		break;
		
		case "GasparGold_meeting_01":
            dialog.text = "È corretto. Nessuno ti offrirà un prezzo migliore del mio. Beh, forse a parte i prestatori su pegno, ma non comprano molto. Sono pronto a comprare tutto ciò che offri. Non devi nemmeno portarmi personalmente i beni preziosi: ho una porta sul retro che conduce a un molo appartato. Sentiti libero di vendermi tutti i gingilli che hai immagazzinato nelle casse sulla tua nave.";
			link.l1 = "Bene, eccellente! Piacere di fare la tua conoscenza.";
			link.l1.go = "GasparGold";
		break;
		
		case "GasparGold_story":
			npchar.mtraxx.story = true;
            dialog.text = "Ecco un affare personale. Preferirei che tu non te ne intromettessi. Ti dirò solo che ho tutto sotto controllo, quindi puoi commerciare con me senza rischi. Il resto non ti riguarda.";
			link.l1 = "Bene, ciò che conta di più è senza rischi! C'era un'altra cosa che volevo chiedere...";
			link.l1.go = "GasparGold";
		break;
		
		case "GasparGold":
			NextDiag.TempNode = "GasparGold";
            dialog.text = "Come posso aiutarti? Vuoi sbarazzarti di qualche perla o gemma extra? Forse oro, argento, gioielli? Comprerò tutto.";
			if(!CheckAttribute(npchar,"mtraxx.story"))
			{
				link.l1 = "Dimmi, com'è essere un acquirente di beni rubati? Non hai paura delle autorità?";
				link.l1.go = "GasparGold_story";
			}
			link.l2 = "Ho qualcosa qui... Voglio scambiarlo per delle monete sonanti.";
			link.l2.go = "GasparGold_01";
		break;
		
		case "GasparGold_01":
            dialog.text = "Bene, facciamo lo scambio. Dobloni o pesos?";
			link.l1 = "Andiamo con i pesos - non c'è bisogno di dobloni. Il denaro comune è accettato ovunque.";
			link.l1.go = "GasparGold_peso";
			link.l2 = "L'hai indovinato - ho bisogno specificamente di dobloni. Quindi venderò solo per quelli.";
			link.l2.go = "GasparGold_dub";
			link.l3 = "Non ho nulla in vendita al momento. Volevo solo assicurarmi che tu sia pronto a comprare oggetti preziosi quando li avrò. Fino alla prossima volta!";
			link.l3.go = "exit";
		break;
		
		// окно торговли
		case "GasparGold_peso":
            Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
			LaunchItemsTrade(NPChar, 0);
		break;
		
		case "GasparGold_dub":
            Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
			LaunchItemsTrade(NPChar, 1);
		break;
		
		// Диалоги после угроз вождю индейцев Кумване
		case "MeridaObsuzhdenie_Bad_1":
            dialog.text = "Ricorri ancora all'intimidazione, Cap? Ho sentito minacce anche da fuori.";
			link.l1 = "Non mi hanno lasciato scelta. Ho offerto dei doni alla moglie di questo Tagofa per il suo aiuto. Non mi ha nemmeno ascoltato. Ora lasciamo che il capo parli con loro. E se non riesce a far tornare alla ragione questi testardi, gli strapperò il cuore dal petto con le mie stesse mani. E a proposito, chi è Yahahu?";
			link.l1.go = "MeridaObsuzhdenie_Bad_2";
			ChangeShowIntarface();
		break;
		
		case "MeridaObsuzhdenie_Bad_2":
            dialog.text = "Non avresti dovuto rovinare i rapporti con gli indiani. Noi pirati abbiamo solo una spada e una nave come alleati. Ma dato che questa è la tua decisione, allora sia. E Yahahu è un demone malvagio. Non so altro di lui.";
			link.l1 = "...";
			link.l1.go = "MeridaObsuzhdenie_Bad_3";
		break;
		
		case "MeridaObsuzhdenie_Bad_3":
            StartInstantDialog("Mrt_Rocur", "MeridaObsuzhdenie_Bad_4", "Quest\Roger.c");
		break;
		
		case "MeridaObsuzhdenie_Bad_4":
            dialog.text = "Perdere tempo con la persuasione, Leprechaun - non è saggio. O preferiresti rinunciare al ricco bottino e mantenere buone relazioni con gli indiani?";
			link.l1 = "...";
			link.l1.go = "MeridaObsuzhdenie_Bad_5";
		break;
		
		case "MeridaObsuzhdenie_Bad_5":
            StartInstantDialog("Lepricon", "MeridaObsuzhdenie_Bad_6", "Quest\Roger.c");
		break;
		
		case "MeridaObsuzhdenie_Bad_6":
            dialog.text = "Preferirei avere entrambi.";
			link.l1 = "Non funzionerà avere un piede in entrambi i campi. Non questa volta. Basta litigi, tutto è già stato fatto. Domani il capo ci informerà della decisione di Tagofa, e spero che non mi deluderà. Altrimenti... dovrò prendere misure estreme. Cosa che vorrei evitare, ovviamente.";
			link.l1.go = "MeridaObsuzhdenie_Bad_7";
		break;
		
		case "MeridaObsuzhdenie_Bad_7":
			DialogExit();
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "GenQuest.CannotWait"); //разрешить отдыхать
			ChangeShowIntarface();
			
            sld = characterFromId("Lepricon");
			sld.dialog.Filename = "Quest\Roger.c";
			sld.dialog.currentnode = "lepricon_3";
			LAi_SetWarriorType(sld);
			
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
		break;
		
		case "MeridaObsuzhdenie_Good_1":
            dialog.text = "Ebbene, come vanno le cose? Avremo una guida?";
			link.l1 = "No, Jean, non lo faremo. Il capo e l'intera tribù temono i Kapongs come il diavolo teme l'incenso. Sembra che dovremo abbandonare il nostro piano.";
			link.l1.go = "MeridaObsuzhdenie_Good_2";
			ChangeShowIntarface();
		break;
		
		case "MeridaObsuzhdenie_Good_2":
            StartInstantDialog("Lepricon", "MeridaObsuzhdenie_Good_3", "Quest\Roger.c");
		break;
		
		case "MeridaObsuzhdenie_Good_3":
            dialog.text = "Terrax non sarà contento di questo cambio di eventi.";
			link.l1 = "Credi che sia incredibilmente felice di come sono andate le cose? I vigliacchi Lokono non vogliono avere a che fare con i Kapongs. Non sono tentati né dalla persuasione né dalle ricompense.";
			link.l1.go = "MeridaObsuzhdenie_Good_4";
		break;
		
		case "MeridaObsuzhdenie_Good_4":
            StartInstantDialog("Mrt_Rocur", "MeridaObsuzhdenie_Good_5", "Quest\Roger.c");
		break;
		
		case "MeridaObsuzhdenie_Good_5":
            dialog.text = "Allora dovremo ricorrere alle minacce. Digli che brucerai il loro maledetto villaggio fino al suolo e torturerai i sopravvissuti fino a quando qualcuno accetterà di guidarci.";
			link.l1 = "Jean, hai completamente perso la testa? Non brucerò le case di persone innocenti. E sicuramente non li torturerò.";
			link.l1.go = "MeridaObsuzhdenie_Good_6";
		break;
		
		case "MeridaObsuzhdenie_Good_6":
            dialog.text = "Charles Prince è un modello di benefattore. Non mi aspettavo mai tali esplosioni di tenerezza da te.";
			link.l1 = "Questa non è tenerezza, Bello. Beh, tortureremo mezzo morto qualche indiano. Per vendetta, ci condurrà direttamente nelle mani dei Kapongs e scomparirà lungo sentieri conosciuti solo a lui. Non rischierò le vite del mio popolo in questo modo.";
			link.l1.go = "MeridaObsuzhdenie_Good_7";
		break;
		
		case "MeridaObsuzhdenie_Good_7":
            dialog.text = "In tal caso, Leprechaun ed io ce ne andiamo. Ecco cinquantamila argenti per avermi liberato dalle piantagioni di Maracaibo. Li stavo risparmiando per una nuova nave. E un mio consiglio: stai fuori dalla vista di Marcus per un po'. Addio, Charles Prince.";
			link.l1 = "Addio, Jean.";
			link.l1.go = "MeridaObsuzhdenie_Good_8";
			AddMoneyToCharacter(pchar, 50000);
		break;
		
		case "MeridaObsuzhdenie_Good_8":
            DialogExit();
			chrDisableReloadToLocation = false;
			ChangeShowIntarface();
			AddQuestRecord("Roger_5", "8b");
			CloseQuestHeader("Roger_5");
			
			sld = characterFromId("Lepricon");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "", "", "", "", -1);
			sld.location = "None";
			RemovePassenger(pchar, sld);
			
			sld = characterFromId("Mrt_Rocur");
			LAi_type_actor_Reset(sld);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "", "", "", "", -1);
			sld.location = "None";
			RemovePassenger(pchar, sld);
			
			sld = characterFromId("Terrax");
			sld.dialog.currentnode = "First time";
		break;
		
		// Немезида. Диалоги с офицерами после взрыва бочонков с порохом
		// Тонзаг
		case "Nemezida_Tonzag_1":
            dialog.text = "Ora tutti della zona si precipiteranno qui! Sei sicuro che far esplodere quegli alberi fosse una buona idea, Capitano?";
			link.l1 = "Maledizione! Forse sarebbe stato meglio se tutti lavorassero con le asce... Ma ora è troppo tardi.";
			link.l1.go = "Nemezida_Tonzag_2";
		break;
		
		case "Nemezida_Tonzag_2":
            dialog.text = "Vero. Dovremo fare con quello che abbiamo. Preparati.";
			link.l1 = "Anche tu, Ercole.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Tonzag_3":
            dialog.text = "Continuano ad avvicinarsi. Quindi, dobbiamo occuparci anche di questi?";
			link.l1 = "E se non avessero fine? Non siamo qui per questo tipo di guai.";
			link.l1.go = "Nemezida_Tonzag_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Tonzag_4":
            dialog.text = "Ebbene, tutto ha una fine... Ma hai ragione. Ritiriamoci. E in fretta.";
			link.l1 = "Affrettiamoci!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Tonzag_5":
            dialog.text = "Così implacabili, ci hanno raggiunto. C'è un sentiero qui, dovremmo entrarci? Sarà più facile tenere la linea.";
			link.l1 = "Aspetta, Ercole. Sentite quello? C'è già qualcuno lì dentro. Tu e i ragazzi gestite le cose qui. Io entro, prima che prendano il tesoro - dubito che qualcuno sia inciampato lì per caso.";
			link.l1.go = "Nemezida_Tonzag_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Tonzag_6":
            dialog.text = "Bene. Ma fai attenzione, ho un brutto presentimento su questo.";
			link.l1 = "Anche tu! Sto andando là.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
		
		case "Nemezida_Tonzag_7": // на берегу
            dialog.text = "Vuoi dire qualcosa, Capitano? Sei stato immerso nei tuoi pensieri per tutta la nostra passeggiata verso la nave.";
			link.l1 = "È vero. Ho riflettuto su ciò che ho fatto recentemente. Su Terrax e... dove mi ha portato. Sono più vicino a salvare mio fratello? O a tornare a casa?..";
			link.l1.go = "Nemezida_Tonzag_8";
		break;
		
		case "Nemezida_Tonzag_8":
            dialog.text = "Mm-m. Buone domande. E quali sono le tue risposte?";
			link.l1 = "Solo un'altra domanda. Se era inutile prima, sarà di nuovo inutile? Terrax non mi aiuterà. Né con mio fratello, né con Tortuga.";
			link.l1.go = "Nemezida_Tonzag_9";
		break;
		
		case "Nemezida_Tonzag_9":
            dialog.text = "Probabilmente no. Non ne ha bisogno. Sorprendente che tu te ne sia reso conto solo ora. Ma qual è la tua prossima domanda?";
			link.l1 = "Perché diavolo stavo correndo dietro a Terrax come un cagnolino, tirando le castagne dal fuoco per lui tutto questo tempo?!";
			link.l1.go = "Nemezida_Tonzag_10";
		break;
		
		case "Nemezida_Tonzag_10":
            dialog.text = "Ora, quella è una buona domanda. Una appropriata. Hai una risposta questa volta?";
			link.l1 = "Più che un desiderio. Sono stato fortunato oggi. Ma sarò fortunato di nuovo? È importante sapere quando fermarsi. E... rispettare se stessi. Ne ho avuto abbastanza.";
			link.l1.go = "Nemezida_Tonzag_11";
		break;
		
		case "Nemezida_Tonzag_11":
            dialog.text = "Hai deciso di terminare la tua collaborazione con Terrax?";
			link.l1 = "Sì. Ho cose più importanti da fare. Famiglia, amici. Con loro, raggiungerò i miei obiettivi. E non in questo modo. E anche se lo faccio... non sarà con Marcus. Sarò il mio proprio padrone. Prenderò le mie decisioni.";
			link.l1.go = "Nemezida_Tonzag_12";
		break;
		
		case "Nemezida_Tonzag_12":
            dialog.text = "L'uomo che una volta seguivo sta parlando di nuovo. Non ti imbattere di nuovo nelle persone sbagliate. Non sprecare il potenziale che una volta mi ha affascinato.";
			link.l1 = "Capito, Hercule. E grazie ancora. Questa volta, per avermi aiutato a capirlo completamente. Non sono più il Principe, un servo. Sono Charles de Maure, un nobile orgoglioso. Saliamo a bordo della nave - siamo entrambi stanchi.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionFinal_Tonzag");
		break;
		
		// Книппель
		case "Nemezida_Knippel_1":
            dialog.text = "È stata un'esplosione da paura, signore - un colpo al mio poppa! Sembra proprio un bordata dalla Valkyrie. Ma temo che anche quei signori laggiù l'abbiano notata...";
			link.l1 = "Se se ne sono accorti, è un loro problema. Nessuno li ha invitati qui. Pronto a impartire loro una lezione, Charlie?";
			link.l1.go = "Nemezida_Knippel_2";
		break;
		
		case "Nemezida_Knippel_2":
            dialog.text = "Sempre pronto, signore!";
			link.l1 = "Eccellente. Cominciamo.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Knippel_3":
            dialog.text = "Temiamo che stiamo per avere più compagnia, Capitano. Quali sono i tuoi ordini?";
			link.l1 = "Andremo più a fondo nella giungla e ci nasconderemo - non c'è modo di respingerli tutti, e comunque non siamo qui per questo.";
			link.l1.go = "Nemezida_Knippel_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Knippel_4":
			PlaySound("VOICE\English\hambit\Charlie Knippel-05.wav");
            dialog.text = "Sì, signore.";
			link.l1 = "Allora muoviamoci!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Knippel_5":
            dialog.text = "Ci hanno rintracciato, Capitano! Ma possiamo rifugiarci qui - sembra che questo sentiero porti da qualche parte, anche se penso che ci sia già qualcuno lì.";
			link.l1 = "Non ci stiamo nascondendo! Sembra che qualcun altro abbia sentito parlare del tesoro. Ecco il piano: andrò a vedere cosa sta succedendo prima che se ne vadano con tutto, e tu li tieni a bada qui con i ragazzi!";
			link.l1.go = "Nemezida_Knippel_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Knippel_6":
			PlaySound("VOICE\English\hambit\Charlie Knippel-05.wav");
            dialog.text = "Sì, signore.";
			link.l1 = "Eccellente. Sto scendendo ora! Mi fido che gestirai le cose qui.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
		
		case "Nemezida_Knippel_7": // на берегу
            dialog.text = "Khe-khe... Sta... bene, signore?";
			link.l1 = "Charlie! Hai scelto il momento perfetto per preoccuparti di me. Risparmia le tue parole. Ti stai tenendo su? Avrei dovuto lasciarti sulla nave e portare più uomini al tuo posto...";
			link.l1.go = "Nemezida_Knippel_8";
		break;
		
		case "Nemezida_Knippel_8":
            dialog.text = "Ah, solo un graffio, signore. Un po' stanco. Non ho mai combattuto così, nemmeno nei miei giorni più giovani! Ma ho dato loro una tale lezione che sentiranno i knippels per l'eternità!";
			link.l1 = "Marina Reale, vecchia scuola! Sembra che tu abbia combattuto come un leone, Charlie. Ma ancora, riesci a malapena a stare in piedi. Non fare il finto - quanto è grave la ferita?";
			link.l1.go = "Nemezida_Knippel_9";
		break;
		
		case "Nemezida_Knippel_9":
            dialog.text = "Non è nulla di grave, Capitano, solo stanchezza. L'ingresso dietro di te è crollato quasi immediatamente, e abbiamo continuato a respingere tutti quegli uomini per un'eternità. Alla fine, sono rimasto solo, ferito. Così, mi sono fatto strada qui per liberare il passaggio e ottenere un primo soccorso.";
			link.l1 = "Capisco. Beh, hai fatto la tua parte oggi. Per quanto riguarda me... ho fallito. Siamo stati tutti ingannati e messi uno contro l'altro per l'amusement di qualcuno - non c'era nemmeno un tesoro. E non ero l'unico sciocco lì.";
			link.l1.go = "Nemezida_Knippel_10";
		break;
		
		case "Nemezida_Knippel_10":
            dialog.text = "Hai fallito?.. Ma sei vivo, signore. Cosa è successo? Sei scappato?";
			link.l1 = "No, ma c'è stata comunque un po' di corsa. Mi dispiace, vecchio amico, ma quello che è successo lì dentro, non lo dirò a nessuno - nemmeno ai miei amici più stretti. Tuttavia, ho tratto le conclusioni necessarie.";
			link.l1.go = "Nemezida_Knippel_11";
		break;
		
		case "Nemezida_Knippel_11":
            dialog.text = "Quali conclusioni, signore? Non capisco sempre il tuo ragionamento. La mia filosofia è semplice - un buon culverino e dei knippels sull'albero.";
			link.l1 = "Dimmi, devi aver ucciso gli spagnoli prima, come ho fatto di recente. Ai tuoi tempi nella Royal Navy. E poi, con Fleetwood.";
			link.l1.go = "Nemezida_Knippel_12";
		break;
		
		case "Nemezida_Knippel_12":
            dialog.text = "L'ho fatto. Spagnoli, olandesi - molti altri ancora. Come Dick mi ha detto una volta, il nostro servizio è pericoloso e impegnativo. Ma perché chiedi? Qual è il tuo punto?";
			link.l1 = "Ti spiegherò. Ma prima, un'altra domanda. Hai mai dubitato di quello che stavi facendo e perché lo stavi facendo, Charlie?";
			link.l1.go = "Nemezida_Knippel_13";
		break;
		
		case "Nemezida_Knippel_13":
            dialog.text = "Uh-mm. Mi sono detto che stavo agendo per il bene della Corona. Preoccuparsi degli ordini è un lavoro ingrato - devi comunque seguirli.";
			link.l1 = "La Corona... Beh, avevi le tue ragioni. Non avevo nemmeno quello - Michel mi ha detto di avvicinarmi a Terrax. Ma valeva tutti i sacrifici? Mi ha aiutato me o lui? Sì, sì, non ci piacciono i don... ma siamo tutti umani.";
			link.l1.go = "Nemezida_Knippel_14";
		break;
		
		case "Nemezida_Knippel_14":
            dialog.text = "Credo di iniziare a capire quello che intendi, signore.";
			link.l1 = "Bene. Dimmi, quando Fleetwood se n'è andato, eri contento di non dover più sparare ai mercanti olandesi? Alcuni di loro erano persone oneste.";
			link.l1.go = "Nemezida_Knippel_15";
		break;
		
		case "Nemezida_Knippel_15":
            dialog.text = "Non ci ho mai pensato, Capitano. Ma dirò questo - mi è sempre piaciuto servire con te, signore. Possa essere dannato con un knippel attorno al mio collo se sto mentendo!";
			link.l1 = "Ha-ha-ha, va bene. Ma dimmi questo - chi pensi che l'abbia passata peggio? Tu, che seguivi gli ordini? O io, che non sono stato costretto a fare quello che ho fatto?";
			link.l1.go = "Nemezida_Knippel_16";
		break;
		
		case "Nemezida_Knippel_16":
            dialog.text = "Non lo so, signore...";
			link.l1 = "Neanch'io. Ma non importa. Quello che conta è che non voglio più avere niente a che fare con Terrax. Basta così. Niente più Charlie Prince. Solo Charles de Maure.";
			link.l1.go = "Nemezida_Knippel_17";
		break;
		
		case "Nemezida_Knippel_17":
            dialog.text = "Ma non era questa parte del tuo piano per salvare tuo fratello?";
			link.l1 = "Lo era. Ma alla fine, non mi ha aiutato affatto. Quindi se dovessi mai fare qualcosa del genere di nuovo - sarà solo la mia decisione. E solo se mi avvicina veramente al mio obiettivo.";
			link.l1.go = "Nemezida_Knippel_18";
		break;
		
		case "Nemezida_Knippel_18":
            dialog.text = "Spero che tu sappia quello che stai facendo, Capitano. E che non finirai come Terrax. O su una forca.";
			link.l1 = "Spero anche io. Ma di quello di cui sono certo è che i miei obiettivi e interessi passeranno prima d'ora in poi. Ora, occupiamoci delle tue ferite.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionFinal_Officers");
		break;
		
		// Лонгвэй
		case "Nemezida_Longway_1":
            dialog.text = "La tua esplosione ha attirato l'attenzione, Signor Capitano. Sembra che una squadra nemica si stia avvicinando a noi.";
			link.l1 = "Maledizione! ...Pensi che ci fosse un modo migliore di affrontare quegli alberi? E cosa avresti fatto tu?";
			link.l1.go = "Nemezida_Longway_2";
		break;
		
		case "Nemezida_Longway_2":
            dialog.text = "Non lo so. Ma so cosa fare ora - occuparmi di quelle persone.";
			link.l1 = "Ebbene, giusto. Suppongo che è esattamente quello che faremo.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Longway_3":
            dialog.text = "Nuove persone arrivano, Signore Capitano.";
			link.l1 = "Sì, ho notato, grazie, Longway. Ma non abbiamo tempo per questi, quindi ritiriamoci nella giungla - forse ci perderanno.";
			link.l1.go = "Nemezida_Longway_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Longway_4":
            dialog.text = "Mmm, potremmo occuparcene, ovviamente, ma come dici tu.";
			link.l1 = "Non abbiamo bisogno di questa lotta, quindi andiamo.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Longway_5":
            dialog.text = "Non molleranno e ci prenderanno, Signor Capitano! Te l'ho detto, avremmo dovuto ucciderli prima. Dovremmo tendere un'imboscata in quella grotta? Anche se sembra che ci sia già qualcuno lì.";
			link.l1 = "Meglio preparare un'imboscata qui con i ragazzi! Quello che non sto per perdere è quel tesoro. Sembra che qualcun altro abbia sentito parlare del bottino... Quindi andrò a controllare da solo.";
			link.l1.go = "Nemezida_Longway_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Longway_6":
            dialog.text = "Sii cauto, Signore Capitano. Ricorda, anche un grande drago una volta è morto sopra un monte d'oro.";
			link.l1 = "Lo terrò a mente, Longway. Cerchiamo tutti di non morire oggi.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
		
		case "Nemezida_Longway_7": // на берегу
            dialog.text = "Signor Capitano, sembra che sia riuscito a sfuggire da lì.";
			link.l1 = "Sorpreso, Longway? Devo ammettere, sono un po' sorpreso anch'io. Sembra che tu sia l'unico che è riuscito a uscirne vivo. Ma come hai fatto?";
			link.l1.go = "Nemezida_Longway_8";
		break;
		
		case "Nemezida_Longway_8":
            dialog.text = "Un branco di gatti randagi non può sconfiggere una tigre. Un nido di serpenti non può abbattere un drago. Tra gli uomini bianchi, pochi sono avversari degni dei miei.";
			link.l1 = "Ma ricorda, Longway, un branco di cani può sbranare un leone.";
			link.l1.go = "Nemezida_Longway_9";
		break;
		
		case "Nemezida_Longway_9":
            dialog.text = "Ora il Signore Capitano condivide la sua saggezza con Longway? Peccato che non hai seguito il mio consiglio prima.";
			link.l1 = "Riguardo al drago sulla montagna d'oro? Vero, quasi ne sono diventato uno - quasi morto, infatti. Ma non su una montagna d'oro - non c'era nulla di tutto ciò. Quello che ho trovato invece era qualcos'altro, altrettanto importante.";
			link.l1.go = "Nemezida_Longway_10";
		break;
		
		case "Nemezida_Longway_10":
            dialog.text = "La prossima volta, 'quasi' potrebbe non succedere. Cosa hai scoperto, Lord Capitano?";
			link.l1 = "Sì, lo vedo ora. Quello che ho trovato era... saggezza. Esperienza. Comprensione. Una decisione. Dimmi, Longway, cosa abbiamo fatto ultimamente?";
			link.l1.go = "Nemezida_Longway_11";
		break;
		
		case "Nemezida_Longway_11":
            dialog.text = "Noi siamo pirati. Lavorando per il tuo nuovo padrone, Signore Terrax. Contrabbando, saccheggio di città, uccisione, salvataggio e aiuto al suo popolo.";
			link.l1 = "Non è il mio padrone, lo sai. Ma dannazione, hai descritto tutto così perfettamente! Ho dimenticato l'orgoglio, l'autostima, e l'ho seguito in giro come un cagnolino.";
			link.l1.go = "Nemezida_Longway_12";
		break;
		
		case "Nemezida_Longway_12":
            dialog.text = "Longway ti capisce, Signor Capitano. Anch'io ho lavorato per van Merden e Rodenburg, dimenticando onore, orgoglio e rispetto per il bene di un obiettivo tanto desiderato.";
			link.l1 = "Dimmi, ti condanni per questo? Ti odi?";
			link.l1.go = "Nemezida_Longway_13";
		break;
		
		case "Nemezida_Longway_13":
            dialog.text = "Condannare? A volte. Odiare? No. So e ricordo chi sono. Ricordo il mio obiettivo, la mia stella guida. Nulla è più importante nella vita. E tu hai un obiettivo?";
			link.l1 = "Non una stella guida come te, ma comunque un obiettivo importante, sì - salvare mio fratello. Ma mi sono allontanato da quel obiettivo. E questo è qualcosa che non posso permettermi di ripetere.";
			link.l1.go = "Nemezida_Longway_14";
		break;
		
		case "Nemezida_Longway_14":
            dialog.text = "Lasciami condividere un altro pezzo di saggezza dall'Impero Celeste con te. Non ci sono persone completamente buone o cattive. Ogni persona possiede sia Yin - oscurità e ignoranza - che Yang - luce e saggezza. Il bilancio cambia dentro ognuno di noi.";
			link.l1 = "Allora, il mio Yang è Charles de Maure. E il mio Yin è Charlie Prince. Anche se forse un giorno anche Charles de Maure dovrà prendere decisioni oscure e difficili.";
			link.l1.go = "Nemezida_Longway_15";
		break;
		
		case "Nemezida_Longway_15":
            dialog.text = "Questa è la vita, Capitano Signore. Ogni persona è destinata a fare scelte sia oscure che luminose.";
			link.l1 = "Eppure la maschera del Principe si è quasi fusa con me. Ma me la toglierò. Charles de Mort è un nobile, non un fattorino. D'ora in poi, sarà solo così. Rivendico il mio orgoglio e la mia dignità. D'ora in poi, sono il mio unico padrone.";
			link.l1.go = "Nemezida_Longway_16";
		break;
		
		case "Nemezida_Longway_16":
            dialog.text = "Longway approva la tua decisione, Signore Capitano.";
			link.l1 = "Grazie, Longway. A proposito, non ti penti di non essere un capitano libero? Servendomi, come dici tu, 'il tuo padrone'?";
			link.l1.go = "Nemezida_Longway_17";
		break;
		
		case "Nemezida_Longway_17":
            dialog.text = "Hm-m. A Longway manca comandare la sua nave. Ma la mia riconosce la tua. Per aver mostrato rispetto e saggezza alla mia, a differenza del tipico barbaro bianco. Forse la mia vorrebbe una vita diversa. Ma la mia non rimpiange di aver aiutato la tua.";
			link.l1 = "Sono lieto di sentire questo, Longway. Ora... lasciamo questo posto e il cammino dello Yin. E portiamo più Yang nelle nostre vite. Ho capito bene?";
			link.l1.go = "Nemezida_Longway_18";
		break;
		
		case "Nemezida_Longway_18":
            dialog.text = "Sì, è corretto. Spero che tu segua un Dao molto migliore d'ora in poi.";
			link.l1 = "Dao?";
			link.l1.go = "Nemezida_Longway_19";
		break;
		
		case "Nemezida_Longway_19":
            dialog.text = "La Via, Capitano Signore. O l'Essenza. Ma nel nostro caso - la Via.";
			link.l1 = "Qualunque cosa il mio futuro possa riservare, non mi allontanerò più da ciò che veramente conta. Lasciamo questo posto, Longway.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionFinal_Officers");
		break;
		
		// Тичингиту
		case "Nemezida_Tichingitu_1":
            dialog.text = "Capitano Charles, molte persone stanno arrivando da questa parte. Il tuo segnale di fumo li ha attirati. E chiaramente non sono amici nostri.";
			link.l1 = "Oh, se solo fosse solo un 'segnale di fumo', come lo hai chiamato - ha risuonato in tutta la giungla. Non c'è scelta - difendiamoci. Sicuramente non abbiamo bisogno di un attacco alle spalle da un intero squadrone.";
			link.l1.go = "Nemezida_Tichingitu_2";
		break;
		
		case "Nemezida_Tichingitu_2":
            dialog.text = "Sì, Capitano Charles. Colpisci per primo!";
			link.l1 = "All'attacco! Non risparmiate le palle!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Tichingitu_3":
            dialog.text = "Arrivano altri! Ancora più persone.";
			link.l1 = "Ritirati nella giungla, Tichingitu! Ci nasconderemo e aspetteremo. Sono venuto qui per un tesoro, non per una lotta!";
			link.l1.go = "Nemezida_Tichingitu_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Tichingitu_4":
            dialog.text = "Se necessario, possiamo tendere un'imboscata nella giungla.";
			link.l1 = "È vero. Ora, muoviamoci - rapidamente, ma silenziosamente.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Tichingitu_5":
            dialog.text = "Capitano Charles, guarda! C'è un passaggio avanti. E posso sentire dei passi e delle voci da lì.";
			link.l1 = "Qualcun altro ha scoperto del tesoro? Accidenti! Senti anche tu quel rumore dietro di noi? Sembra che ci abbiano raggiunto. Tichingitu! Andrò a controllare cosa c'è avanti. Tu trattienili con i ragazzi!";
			link.l1.go = "Nemezida_Tichingitu_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Tichingitu_6":
            dialog.text = "Ci proviamo! Tu vai!";
			link.l1 = "Sto contando su di te!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
			
		case "Nemezida_Tichingitu_7": // на берегу
            dialog.text = "Capitano Charles! Sopravvivi! Tichingitu è felice per questo.";
			link.l1 = "Grazie, amico mio. Sono felice anch'io. Sono contento di essere sopravvissuto, e che tu stia bene. Sembra che tu sia l'unico rimasto di tutta la squadra. Erano in molti? Li hai davvero tenuti a bada bene.";
			link.l1.go = "Nemezida_Tichingitu_8";
		break;
		
		case "Nemezida_Tichingitu_8":
            dialog.text = "Molti. Ma il mio è uno dei migliori guerrieri del nostro villaggio Maskog. Cosa ti è successo lì? Hai trovato il tesoro che stavi cercando?";
			link.l1 = "No, Tichingitu. Siamo stati ingannati - non c'era nessun tesoro. Dimmi, cosa pensi di quello che abbiamo fatto ultimamente?";
			link.l1.go = "Nemezida_Tichingitu_9";
		break;
		
		case "Nemezida_Tichingitu_9":
            dialog.text = "Cosa stiamo facendo, Capitano Charles? Naviga. Sconfiggi i tuoi nemici.";
			link.l1 = "Sembra che tu non mi capisca. Dimmi allora, sei triste per essere stato esiliato dalla tua tribù? Vuoi tornare, ti mancano i tuoi fratelli?";
			link.l1.go = "Nemezida_Tichingitu_10";
		break;
		
		case "Nemezida_Tichingitu_10":
            dialog.text = "Certo, mi mancano i miei amici e la mia famiglia. Ma tornare? La mia casa non esiste più senza... lei. Inoltre, c'è quel malvagio coyote, lo sciamano!";
			link.l1 = "Mi dispiace, non volevo parlare di questo. Sai, recentemente mi sono unito a una tribù, per così dire. Una tribù di capitani come me. Ma alla fine, ho capito che era solo un branco di sciacalli che si considerano lupi di mare...";
			link.l1.go = "Nemezida_Tichingitu_11";
		break;
		
		case "Nemezida_Tichingitu_11":
            dialog.text = "E cosa succede? Cosa facciamo adesso?";
			link.l1 = "Buona domanda. Quasi sono diventato io stesso uno sciacallo con quegli sciacalli. Quindi, per me è abbastanza. I miei amici e il mio equipaggio - quella è la mia 'tribù'.";
			link.l1.go = "Nemezida_Tichingitu_12";
		break;
		
		case "Nemezida_Tichingitu_12":
            dialog.text = "Tichingitu è felice che tu abbia trovato la tua tribù, Capitano Charles.";
			link.l1 = "Grazie, amico mio. Avevo bisogno di dirlo. Tu ed io siamo entrambi i nostri stessi leader e tribù. Ed ora è tempo di tornare a questioni davvero importanti.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionFinal_Officers");
		break;
		
		// Айронс
		case "Nemezida_Irons_1":
            dialog.text = "Arriva qualcuno! E, a giudicare dal rumore, non per unirsi a noi nei festeggiamenti del Ringraziamento.";
			link.l1 = "Maledette radici! Va bene, dovremo occuparci di questi mascalzoni ora - meglio ora che quando stiamo portando il tesoro alla nave.";
			link.l1.go = "Nemezida_Irons_2";
		break;
		
		case "Nemezida_Irons_2":
            dialog.text = "Hai proprio ragione. Pronto?";
			link.l1 = "Non dovevi chiedere. Non è che abbiamo una scelta.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Irons_3":
            dialog.text = "Sono ovunque, come ratti nelle baraccopoli di Londra, Vostro Onore! Qual è il piano - dobbiamo tenere la nostra posizione e farla finita con i ragazzi?";
			link.l1 = "Non ora, indietro! Siamo qui per il tesoro, non per combattere!";
			link.l1.go = "Nemezida_Irons_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Irons_4":
            dialog.text = "Eh, nessuna obiezione qui.";
			link.l1 = "Allora affretta il passo!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Irons_5":
            dialog.text = "Ehi, Capitano, guarda - sembra che questo sentiero porti da qualche parte. E sembra piuttosto animato là, a giudicare dal rumore!";
			link.l1 = "Potrebbe essere che qualcun altro abbia sentito parlare del tesoro? Tommy, senti quello? Ci hanno raggiunto. Va bene, andrò avanti, e voi tutti date loro un degno benvenuto qui!";
			link.l1.go = "Nemezida_Irons_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Irons_6":
            dialog.text = "Ora lo sento! Chiunque siano, faresti meglio a sbrigarti, he-he. Altrimenti, qual era il senso del nostro lungo viaggio fin qui?!";
			link.l1 = "Oh, odierei che fosse così.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
		
		case "Nemezida_Irons_7": // на берегу
            dialog.text = "Ah, sei tu, capitano! Wow, sei sopravvissuto. Non mentirò - non me l'aspettavo. Ma sono contento, non fraintendermi, eh-eh.";
			link.l1 = "Non me l'aspettavo nemmeno io, non mentirò. Ma il fatto che tu sia sopravvissuto - non mi sorprende affatto. Sei scappato?";
			link.l1.go = "Nemezida_Irons_8";
		break;
		
		case "Nemezida_Irons_8":
            dialog.text = "Mi fai un torto! Tommy Irons non scappa mai! Torna solo per rinforzi. Ma non era necessario - io e i miei ragazzi ce la siamo cavati da soli, anche se, ancora una volta, sono l'unico che ne è uscito vivo, eh...";
			link.l1 = "Forse questa volta avresti dovuto cercare rinforzi. Ma io... io sono scappato.";
			link.l1.go = "Nemezida_Irons_9";
		break;
		
		case "Nemezida_Irons_9":
            dialog.text = "Hai scappato? Heh, mi hai sorpreso di nuovo. Ma volevo effettivamente precipitarmi da te non appena avessi finito! Sono meglio di qualsiasi rinforzo, lo sai. È solo che...";
			link.l1 = "Cosa c'è che non va, Tom?";
			link.l1.go = "Nemezida_Irons_10";
		break;
		
		case "Nemezida_Irons_10":
            dialog.text = "Maledizione, mentre stavo perdendo tempo, l'ingresso dietro di te si è bloccato con le rocce. Non riuscivo a passare. È addirittura imbarazzante che ci ho messo così tanto a liberarlo e non ho potuto aiutarti lì. Mi sono un po' perso da solo cercando di tornare indietro per prendere i ragazzi e aiutare a spostare le rocce... Quando sono tornato, eri già tornato tu.";
			link.l1 = "Sì, forse mi vergognerò di ammettere ciò che mi è successo oggi.";
			link.l1.go = "Nemezida_Irons_11";
		break;
		
		case "Nemezida_Irons_11":
            dialog.text = "E cosa è successo? Non aver paura, dimmelo. Ma se è qualcosa di divertente, sto per ridere, solo che tu lo sappia. Come dovrebbe essere altrimenti? Un amico offre la sua spalla e ti dà un colpetto con il gomito ridendo.";
			link.l1 = "Beh, sai davvero come confortare. Dimmi, Tommy. Hai detto che ti piaceva fare il pirata. Eri contento di tornarci con me?";
			link.l1.go = "Nemezida_Irons_12";
		break;
		
		case "Nemezida_Irons_12":
            dialog.text = "Lo dirò così. Che io sia un pirata o no, quello che ho sempre amato maledettamente è l'avventura! Vedo che la mia risposta non ti soddisfa. Queste cose, le questioni importanti, non fanno per me.";
			link.l1 = "Non è che non mi soddisfi. Ma non è di questo che volevo discutere. Sai... ho capito che con Tiraqs, mi sono completamente allontanato dai miei obiettivi. Inoltre... Charlie Prince era una sorta di lacchè, non un coraggioso capitano pirata, capisci, Tom? Ne ho abbastanza.";
			link.l1.go = "Nemezida_Irons_13";
		break;
		
		case "Nemezida_Irons_13":
            dialog.text = "Capisco. Ecco perché ero sorpreso che tu lasciassi Terrax controllarti così. Non sembravi nemmeno tu.";
			link.l1 = "Forse ero davvero Charlie Prince allora. Ma se torniamo o no alla pirateria, deciderò io! E solo se serve davvero ai miei interessi e mi avvicina al mio obiettivo!";
			link.l1.go = "Nemezida_Irons_14";
		break;
		
		case "Nemezida_Irons_14":
            dialog.text = "Ecco, questo è più simile! Ma voglio dire, che sia Charlie Prince o Charles de Maure - sei sempre tu. E con te, è sempre stato maledettamente interessante!";
			link.l1 = "Contento di sentire questo, Tommy.";
			link.l1.go = "Nemezida_Irons_15";
		break;
		
		case "Nemezida_Irons_15":
            dialog.text = "Ricorda, quasi nessuno ti aiuterà tranne te stesso. È meglio fare ciò che ami, anche da solo, piuttosto che lasciare che gli altri prendano decisioni per te!";
			link.l1 = "Vero. È esattamente quello che ho provato con Terrax. Anche se finirò per seguire di nuovo qualcuno, sarà solo in termini degni, non come un maledetto ragazzo delle commissioni!";
			link.l1.go = "Nemezida_Irons_16";
		break;
		
		case "Nemezida_Irons_16":
            dialog.text = "Hai ragione! Ora, usciamo da qui - le mie gambe sono già deboli.";
			link.l1 = "Ehi, stavo per dire proprio quello, ah-ah. Ma hai ragione, andiamo. Abbiamo un sacco di lavoro importante davanti, Tom. Non questo tipo di roba.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionFinal_Officers");
		break;
		
		// Алонсо
		case "Nemezida_Alonso_1":
            dialog.text = "Capitano, sembra che abbiamo compagnia! Non siamo soli qui.";
			link.l1 = "Proprio quello di cui avevamo bisogno... Va bene, occupiamoci di loro adesso. Più tardi, saranno solo un problema in più.";
			link.l1.go = "Nemezida_Alonso_2";
		break;
		
		case "Nemezida_Alonso_2":
            dialog.text = "Sì, Capitano.";
			link.l1 = "Preparati!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Alonso_3":
            dialog.text = "Ce ne sono sempre di più!";
			link.l1 = "Allora non c'è motivo di continuare! Ritiriamoci! Li perderemo e ci dirigeremo direttamente verso il tesoro!";
			link.l1.go = "Nemezida_Alonso_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Alonso_4":
            dialog.text = "Sì, Capitano!";
			link.l1 = "Spostati, spostati!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Alonso_5":
            dialog.text = "Capitano, sembra che ci sia un'entrata qui! E qualcuno è già dentro.";
			link.l1 = "Ascolta attentamente - ci hanno seguito. Andrò a controllare mentre tu tieni questa posizione. Coprimi, ragazzi!";
			link.l1.go = "Nemezida_Alonso_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Alonso_6":
            dialog.text = "Sì, Capitano!";
			link.l1 = "Mantieni la tua posizione. Buona fortuna a te - a tutti noi!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Sei "+GetSexPhrase("un ladro, vedo! Guardie, afferratelo","un ladro, vedo! Guardie, prendetela")+"!!!","Non posso crederci! Mi sono girato per un secondo - e tu stai frugando nelle mie cose! Fermate un ladro!!!","Guardie! Rapina! Fermate un ladro!!!");
			link.l1 = "Aaaah, diavolo!!!";
			link.l1.go = "fight";
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//<-- блок реагирования на попытку залезть в сундук
		
		// <-- legendary edition
	}
}

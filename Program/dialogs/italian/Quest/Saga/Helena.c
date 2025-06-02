// Элен МакАртур - сомнительная любовь и офицер
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	string 	sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Che c’è?";
			link.l1 = "No, non è nulla.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "After_boarding":
			dialog.text = "Grazie per il tuo aiuto, capitano!";
			link.l1 = "Dio mio... Sei ancora più bella di quanto avessi mai potuto immaginare!";
			link.l1.go = "After_boarding_1";
		break;
		
		case "After_boarding_1":
			dialog.text = "Al diavolo la mia bellezza! Sai quanta sventura mi ha portato? Mi taglierei il naso da sola, se non fosse che rovinerei la mia reputazione. Quel dannato non mi avrebbe lasciata uscire viva dalla corvetta, continuava a dire che 'sapevo troppo'. E ieri mi ha detto che era stufo di aspettare e che avrebbe preso ciò che voleva, volente o nolente.\nSei arrivato proprio all’istante giusto! Ma guarda che maleducata sono, mi chiamo Helen McArthur. Mio padre mi chiamava Rumba perché rompevo sempre senza volerlo le sue porcellane 'provenienti chissà da dove', così l’equipaggio ora mi chiama così.";
			link.l1 = "Il mio nome è "+GetFullName(pchar)+" e son qui per trarti in salvo. Ho setacciato i Caraibi per giorni interi cercandoti, tutto per conto della signora Gladys.";
			link.l1.go = "After_boarding_2";
		break;
		
		case "After_boarding_2":
			dialog.text = "Signora Gladys!? Come sta?";
			link.l1 = "Mi sono dannata dall’ansia per te. Ma la rivedrai presto, stiamo salpando verso Blueweld. Potrai raccontarmi tutto ciò che ti è successo durante il viaggio.";
			link.l1.go = "After_boarding_3";
		break;
		
		case "After_boarding_3":
			dialog.text = "A dire il vero, "+pchar.name+"   Vorrei solo mangiare qualcosa e schiacciare un pisolino adesso. Sono sfinita dopo tutti quei giorni passati su quella nave da incubo...";
			link.l1 = "Certamente, signorina McArthur. Ordinerò al mio intendente di servirle un pasto e preparare un letto nei suoi alloggi privati.";
			link.l1.go = "After_boarding_4";
		break;
		
		case "After_boarding_4":
			DialogExit();
			LAi_SetActorType(npchar);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			npchar.greeting = "helena_2";
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			pchar.questTemp.Saga = "returntoblueveld";
			Island_SetReloadEnableGlobal("Antigua", true);//на остров можно
			bQuestDisableMapEnter = false;//открыть карту
			AddQuestRecord("Saga", "11");
			pchar.quest.Saga_returnBlueveld.win_condition.l1 = "location";
			pchar.quest.Saga_returnBlueveld.win_condition.l1.location = "Santacatalina_town";
			pchar.quest.Saga_returnBlueveld.function = "Saga_returnBlueveld";
			SetFunctionTimerCondition("Helena_ReturnOver", 0, 0, 45, false);
			sld = characterFromId("gladis");
			sld.greeting = "gladis_3";
		break;
		
		case "Return_blueveld":
			pchar.quest.Helena_ReturnOver.over = "yes";
			dialog.text = "Capitano de Maure, vi ringrazio ancora dal profondo del cuore per il vostro provvidenziale soccorso. Dovete venire a trovarmi insieme a mia madre. La nostra casa non è lontana da qui, la trovate alla vostra sinistra venendo dal molo. E sappiate questo "+pchar.name+", non te lo perdonerò mai se salperai senza dirmi addio!";
			link.l1 = "Il piacere è stato tutto mio, signorina McArthur. Contate pure che verrò a farvi visita!";
			link.l1.go = "Return_blueveld_1";
		break;
		
		case "Return_blueveld_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "houseSp3", "SantaCatalina_houseSp3_bedroom", "goto", "goto1", "OpenTheDoors", -1);
			AddQuestRecord("Saga", "13");
			LocatorReloadEnterDisable("SantaCatalina_houseS1", "reload2", false); // открыть кабинет Свенсона
			pchar.questTemp.Saga = "svenson";//идем к Свенсону
			sld = characterFromId("JS_girl");
			sld.dialog.currentnode = "js_girl";
			npchar.dialog.currentnode = "Helena_wait";
			sld = characterFromId("Gladis");
			sld.dialog.currentnode = "Gladis_regard";
			LocatorReloadEnterDisable("SantaCatalina_houseSp3", "reload2", true);//закрыть спальню Элен
			// закрыть город до беседы с Глэдис
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", true);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", true);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", true);
		break;
		
		case "Helena_wait":
			dialog.text = "Ah, finalmente siete qui, Capitano de Maure! Sono davvero lieta del vostro arrivo, ho mille domande da porvi.";
			link.l1 = "Mi duole, signorina McArthur, ma dobbiamo rimandare la nostra conversazione per un momento. Devo raccogliere qualche informazione in più prima di potervi dare risposte degne di questo nome. Ora vi chiedo solo di non farvi vedere in strada. Spero che l’attesa non sia lunga. Abbiate fiducia in me e attendete.";
			
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.CanDrink")) {
				link.l1.go = "drinking_refuse";
				link.l2 = "L’hai detto tu stessa che non mi avresti mai perdonato se non fossi passato a trovarti.";
				link.l2.go = "drinking_accept";
				
				DeleteQuestCondition("HelenDrinking_NoVisit");
				DeleteAttribute(pchar, "questTemp.HelenDrinking.CanDrink");
			} else {
				link.l1.go = "exit";
				NextDiag.TempNode = "Helena_wait";
			}
		break;
		
		case "Helena_hire":
			dialog.text = "Ah, eccoti, mio capitano! I tuoi occhi mi dicono che hai notizie per me!";
			link.l1 = "Il capitano Svenson mi ha detto che desideri salpare con me. Apprezzo il tuo desiderio, e la signora Gladys mi ha anche detto che il mare ti mancava. Benvenuta a bordo, signora Helen McArthur!";
			link.l1.go = "Helena_hire_1";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_friend"))
			{
				link.l2 = "Il capitano Svenson mi ha detto che desideri salpare con me. Apprezzo il tuo desiderio, e la signora Gladys mi ha pure detto che ti manca il mare. Benvenuta tra la mia ciurma, signorina Helen Sharp!";
				link.l2.go = "Helena_hire_2";
				pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 2;
			}
		break;
		
		case "Helena_hire_1":
			DeleteAttribute(pchar, "questTemp.Saga.Helena_friend");
			dialog.text = "Ai tuoi ordini, capitano! Mi rincresce doverlo dire, signore, ma so badare a me stessa e non tollero che certi uomini si prendano troppe confidenze. Non rispondo delle mani mozzate o degli occhi cavati.";
			link.l1 = "Non temere, sulla mia nave regna una disciplina di ferro. Però devo chiederti una cosa...";
			link.l1.go = "Helena_hire_1_1";
		break;
		
		case "Helena_hire_1_1":
			dialog.text = "...Sì?";
			link.l1 = "Io e Jan Svenson abbiamo scoperto che sei la vera erede di Isla Tesoro. Sì, è vero, non scuotere la testa! Ho metà della mappa che dimostra i tuoi diritti. Non sarà facile, ma io e Jan faremo il possibile per aiutarti a ottenere ciò che ti spetta.";
			link.l1.go = "Helena_hire_1_2";
		break;
		
		case "Helena_hire_1_2":
			dialog.text = ""+pchar.name+" , sei davvero serio? Non è gentile scherzare così con una povera ragazza! Come potrei mai avere il diritto di possedere un'intera isola?!";
			link.l1 = "Sono assolutamente serio, signorina McArthur. E intendo aiutarti a riprendere ciò che ti spetta di diritto. Salpiamo subito!";
			link.l1.go = "Helena_hire_6";
		break;
		
		case "Helena_hire_2":
			dialog.text = "C-cosa hai detto? Helen Sharp? Perché Sharp?";
			link.l1 = "Helen, sei la figlia di Beatrice Sharp e l'unica erede della dinastia Sharp. Questa è metà della mappa che la signora Gladys ha custodito per tutti questi anni. È la prova dei tuoi diritti su Isla Tesoro. Non sarà facile, ma io e Jan Svenson faremo di tutto per aiutarti a rivendicare l'isola di tuo nonno.";
			link.l1.go = "Helena_hire_3";
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 3;
			notification("Helen approves", "Helena");
			npchar.lastname = "Sharp";
		break;
		
		case "Helena_hire_3":
			dialog.text = "Oh... Mia povera madre! Vorrei tanto poter trovare un giorno la sua tomba e pregare per la sua anima lì. Ma... aspetta! Impossibile!";
			link.l1 = "Che c’è, signorina Sharp?";
			link.l1.go = "Helena_hire_4";
		break;
		
		case "Helena_hire_4":
			dialog.text = "La profezia della zingara si è appena avverata... Ora finalmente la comprendo.";
			link.l1 = "Eh? Quale profezia?";
			link.l1.go = "Helena_hire_5";
		break;
		
		case "Helena_hire_5":
			dialog.text = ""+pchar.name+", potrai anche chiamarmi ingenua, ma te lo dirò lo stesso. Quand’ero una ragazzina, una zingara mi disse: ‘Il tuo destino sarà nelle mani di colui che non prende la moneta della vedova, che restituisce l’oro del morto e che nomina la madre’\nAll’epoca credevo fossero solo fandonie, ma tu sei riuscito a compiere ogni parte della profezia, e non potresti mai averlo saputo!";
			link.l1 = "Il tuo destino, dici... Forse hai ragione. Non ti deluderò. Cercheremo insieme la tomba di tua madre. E ora... Signorina Helen Sharp! Preparati alla partenza e non farti aspettare!";
			link.l1.go = "Helena_hire_6";
		break;
		
		case "Helena_hire_6":
			dialog.text = "Ai vostri ordini, capitano!";
			link.l1 = "...";
			link.l1.go = "Helena_hire_add";
		break;
		
		case "Helena_hire_add":
			LAi_SetImmortal(npchar, false);
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Saga_HireHelena", -1);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", false);//открыть выходы из города
			pchar.questTemp.Saga = "svenson_wait";
			AddQuestRecord("Saga", "24");
			AddQuestUserData("Saga", "sTimer", AddDaysToDateString(367));
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("Saga_BaronsQuestsGo", 0, 0, 2, false);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			
			if (pchar.questTemp.HelenDrinking.Result != "no_visit") {
				AddQuestRecord("HelenDrinking", "3");
				
				SetFunctionLocationCondition("HelenDrinking_IslaTesoroAmbush", "Pirates_town", false);
				sld = &locations[FindLocation("Pirates_town")];
				sld.locators_radius.quest.detector1 = 4.0;
			}
		break;
		
		//-->  консультации по морским сражениям в искушении барбазона
		case "sea_bomb":
			dialog.text = "Capitano "+pchar.name+"! Ho avuto un’idea...";
			link.l1 = ""+npchar.name+"Non è sicuro qua, ti avevo detto di restare a bordo...";
			link.l1.go = "sea_bomb_1";
		break;
		
		case "sea_bomb_1":
			dialog.text = "Charles, c’è tanta polvere da sparo stipata in questa vecchia carretta che se salta in aria, l’isola intera finirà dritta alle porte di San Pietro! Che tu mi dica di nascondermi o no, non cambia un accidente, dunque ascoltami!";
			link.l1 = "D'accordo, parla in fretta!";
			link.l1.go = "sea_bomb_2";
		break;
		
		case "sea_bomb_2":
			dialog.text = "La corvetta e la fregata. Non riconoscono la nave di Knive come nemica. Possiamo sfruttare la loro fiducia cieca contro di loro. Prendiamo qualche barile di polvere da sparo, prepariamo una miccia e navighiamo verso le navi.\nSe ci lasciano avvicinare, accenderemo la miccia, lasceremo il barile su una di loro e scapperemo a vele spiegate. Poi ci godremo uno spettacolo pirotecnico... Che ne dici?";
			link.l1 = "Una nave incendiaria improvvisata... davvero astuto! Il tuo piano è così folle che potrebbe persino funzionare... se solo riuscissimo ad avvicinarci senza farci riconoscere.";
			link.l1.go = "sea_bomb_3";
		break;
		
		case "sea_bomb_3":
			dialog.text = "Cosa mai abbiamo da perdere "+pchar.name+"Non sarà facile affrontare due navi insieme, ma avremo la nostra occasione per pareggiare i conti...";
			link.l1 = "Va bene. Andiamo, forza! Ragazzi! Prendete tre barili di polvere da sparo! Ce ne andiamo da questo inferno! Adoro la tua fantasia, "+npchar.name+"... Non mi sarebbe mai passato per la testa, te lo giuro.";
			link.l1.go = "sea_bomb_4";
		break;
		
		case "sea_bomb_4":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetOfficerType(npchar);
			npchar.dialog.currentnode = "Helena_officer";
			pchar.questTemp.Saga.BarbTemptation.Bomb = "true";
			pchar.questTemp.Saga.BarbTemptation.adviser = "Helena";
		break;
		
		case "fugas":
			dialog.text = "Aye capitano, che succede?";
			link.l1 = "La nave di Jackman si trova alla Baia di Sabo-Matila, la pesante fregata 'Centurion'. Questa nave apparteneva un tempo agli Hawkes, quindi nella cabina di Jackman ci saranno oggetti e documenti importanti... dobbiamo salirci a bordo.";
			link.l1.go = "fugas_1";
		break;
		
		case "fugas_1":
			dialog.text = "Più facile a dirsi che a farsi. E come pensi di riuscirci con la nostra polacca? Hanno più uomini e più cannoni di noi.";
			link.l1 = "Hai ragione. Jackman ha almeno il doppio dei nostri uomini, e tutti sono spadaccini di razza. Attaccarli di petto senza prima bombardare sarebbe una follia. Ma nemmeno uno scontro lungo fa al caso nostro. Ho riflettuto su come muovermi.";
			link.l1.go = "fugas_2";
		break;
		
		case "fugas_2":
			dialog.text = ""+pchar.name+", non ci hanno ancora preso per nemici, proprio come quei babbei a Turks... Possiamo riprovare il nostro trucchetto...";
			link.l1 = "Hélène, ti ho appena detto che dobbiamo abbordare e perquisire la fregata, mandarla al diavolo in mille pezzi non è un’opzione.";
			link.l1.go = "fugas_3";
		break;
		
		case "fugas_3":
			dialog.text = "Aspetta un attimo, "+pchar.name+", non l’affonderemo. Facciamo le cose in modo diverso.  Ascolta, prenderemo alcune botti vuote di rum e le riempiremo di polvere da sparo, mitraglia e micce corte. Poi ci avvicineremo alla loro fregata e lanceremo queste bombe improvvisate sul loro ponte.";
			link.l1 = "Ah! La tua astuzia femminile continua a lasciarmi di stucco! Invece di una nave incendiaria, proponi una fougasse? Pensi davvero che possa funzionare?";
			link.l1.go = "fugas_4";
		break;
		
		case "fugas_4":
			dialog.text = "E perché no? Hanno la murata più alta della nostra, ma con un paio di uomini e una carrucola si può issare e lanciare una botte piena in un attimo. Grideremo: 'Rum gratis da Knive!' – e le botti esploderanno prima che riescano pure a capire che succede.";
			link.l1 = "Le mitraglie esplosive faranno a brandelli i suoi migliori uomini sul ponte... Maledizione, è una tentazione dannata.";
			link.l1.go = "fugas_5";
		break;
		
		case "fugas_5":
			dialog.text = "Buttiamo cinque barili in una volta sola dal cassero fino al ponte di poppa. "+pchar.name+", abbiamo il vantaggio della sorpresa. Non sospetteranno nulla, per ora! E poi leveremo le ancore prima che abbiano il tempo di abbordarci.";
			link.l1 = "D'accordo, proviamoci. Non devono riconoscerci prima che piazziamo quelle botti di polvere sul loro ponte... Avvicinarsi non sarà cosa da poco. Jackman non è uno sprovveduto come lo era Ghoul.";
			link.l1.go = "fugas_6";
		break;
		
		case "fugas_6":
			dialog.text = "Corriamo il rischio, "+pchar.name+"! Come ti ho già detto, che diavolo abbiamo da perdere?";
			link.l1 = "Ben detto... In piedi, ragazzi! Preparate le fougasses e state pronti a menar le mani!";
			link.l1.go = "fugas_7";
		break;
		
		case "fugas_7":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			pchar.questTemp.Saga.BarbTemptation.Fugas = "true";
			AddQuestRecord("BarbTemptation", "21");
			DeleteAttribute(npchar, "quest.fugas");
		break;
		//<--  консультации по морским сражениям
		
	// --> разговор по итогам Саги
		case "result":
			//if (!CheckAttribute(pchar, "questTemp.Saga.Helena_friend")) // не друзья
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 11) {
				Achievment_Set("ach_CL_83");
			}
			
			if (sti(pchar.questTemp.Saga.HelenRelation) < 6)
			{
				dialog.text = "Ebbene, mio caro capitano... È giunta l’ora di darci l’addio. Il mio servizio termina qui e devo abituarmi all’idea di diventare la Regina dei Pirati di Isla Tesoro. Spero di essere una degna erede di mio zio. Ti sono grata per tutto l’aiuto.";
				link.l1 = "Ahimè, mi rincresce separarmi da te, ma così gira la sorte. Orsù, hai ben altri doveri ora che battere il ponte della mia nave.";
				link.l1.go = "result_1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.HelenDrinking.Mary")) {
					dialog.text = "Mi piacerebbe tanto restare sulla tua nave. Essere vicina a te... Ma è impossibile. Sii felice, Charles. E che lei sia davvero degna di te!";
					link.l1 = "Mi dispiace, Hélène.";
					link.l1.go = "result_mary";
				} else {
					dialog.text = "È così strano, "+pchar.name+"! Sono appena diventata la padrona di un’intera isola, ma non mi sento affatto una regina di Isla Tesoro... Credo che il nuovo capo della Fratellanza saprà governare la colonia meglio di me. Ho ancora tanto da imparare.";
					link.l1 = "Non preoccuparti, Helen, sei una donna che sa badare a se stessa – proprio come mi dicesti appena messa piede a bordo.";
					link.l1.go = "result_9";
				}
			}
			
			DeleteQuestCondition("HelenDrinking_AtSHDN");
			DeleteQuestCondition("HelenDrinking_InBlueweldAfterCave");
		break;
		
		case "result_mary":
			dialog.text = "Beh, resteremo comunque amici, vero?";
			link.l1 = "Ma certo... Helen, ci rivedremo a Isla Tesoro. Vuoi che ti accompagni sulla tua isola?";
			link.l1.go = "result_12";
		break;
		
		case "result_1":
			dialog.text = "Hai ragione... Ascolta, ho messo da parte la mia parte di bottino navigando sulla tua nave. Prendilo e non osare rifiutare la mia offerta – non voglio restare in debito con te.";
			link.l1 = "Ehi, aspetta un attimo...";
			link.l1.go = "result_2";
		break;
		
		case "result_2":
			dialog.text = "So cosa stai per dire. Certo, il tuo aiuto è stato ben più prezioso di questo misero forziere. Ma è tutto ciò che ho al momento e devo ripagarti. Prendilo, se non lo prendi tu lo lascerò nella tua cabina.";
			link.l1 = "Veleggerai da solo, adesso? Forse potrei portarti io a Isla Tesoro?";
			link.l1.go = "result_3";
		break;
		
		case "result_3":
			GiveItem2Character(pchar, "chest");
			Log_Info("You have received a chest with doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Non ce n’è bisogno, "+pchar.name+". Ci arriverò da sola all’isola. Ho la mia spada e la pistola con me, mi basteranno per un po’... Sono certa che la Regina di Isla Tesoro non dovrà più preoccuparsi delle entrate, una volta che sarò lì.";
			link.l1 = "Aye aye, maestà. Che il vento ti sia favorevole nella tua nuova vita.";
			if (!CheckAttribute(pchar, "questTemp.Saga.Beltrop_die")) link.l1.go = "result_4";
			else link.l1.go = "result_7";
		break;
		
		case "result_4":
			dialog.text = "Basta con queste moine, anche per scherzo. Resto sempre Helen per te. Ma non è tutto quello che volevo dirti. Ho ritrovato mio padre, anche se è stato… piuttosto strano. Ha sacrificato la sua reputazione di nobile inglese per la mia eredità, e questo mi turba. Ora il Commonwealth inglese gli dà la caccia e io non voglio che tu, "+pchar.name+",   per prendervi parte.";
			link.l1 = "Rinsavisci, Hélène! Quello è un furfante e un bucaniere!";
			link.l1.go = "result_5";
		break;
		
		case "result_5":
			dialog.text = "Pirata? E chi diavolo sei tu per sputar sentenze? Lui è mio padre, e questo è tutto quel che conta per me! E io, figlia d’un fuorilegge e di un pirata, me ne sbatto allegramente di ciò che pensa la giustizia inglese. Se solo provi a fargli del male, dimenticherò ogni bene che hai fatto per me, sappilo. Prendila come un’avvertenza.";
			link.l1 = "Ah davvero? Senti, fanciulla, faresti meglio a misurare le parole. Non ti ho vista tanto schifata dal mio spirito piratesco quando ti ho strappata dalle grinfie di quel porco di Donovan, o quando dividevamo il bottino delle nostre prede!";
			link.l1.go = "result_6";
		break;
		
		case "result_6":
			dialog.text = "Io... io ti chiedo perdono. Ritiro quello che ho detto, scusami. Ho perso la bussola... Ma vorrei comunque restare tua amica, cosa che sarebbe impossibile se ti mettessi sulle tracce di mio padre.";
			link.l1 = "Capito. Ma non ti azzardare mai più a minacciarmi, donna. Dovresti ormai sapere, dopo aver navigato sulla mia nave, che non temo né uomo né diavolo. E men che meno sopporterò mancanza di rispetto da una donna – Regina dei Pirati o no. Sarò pure un gentiluomo, ma anche la mia pazienza ha un termine. Ora che è detto, addio. Ti auguro venti favorevoli.";
			link.l1.go = "result_8";
		break;
		
		case "result_7":
			dialog.text = "Ti ringrazio... Forse ci rincontreremo, "+pchar.name+"...";
			link.l1 = "E perché no? Mi capiterà di tornare a Isla Tesoro più di una volta. Ci vediamo laggiù... Addio, Hélène.";
			link.l1.go = "result_8";
		break;
		
		case "result_8": // Элен уходит, но её не затираем
			DialogExit();
			RemovePassenger(pchar, npchar);
			//chrDisableReloadToLocation = true;//закрыть локацию  // уже не надо.
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "goto", "goto24", "", "", "", "", 7);//OpenTheDoors лесник . чтобы бежала и исчезла а не стояла.
			AddQuestRecord("Testament", "11");
			CloseQuestHeader("Testament");
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false); // лесник . пирс. 
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false); // ворота.
			InterfaceStates.Buttons.Save.enable = true;//можно сохраняться		
			if (CheckAttribute(pchar, "questTemp.LSC.MaryWait")) {
				pchar.questTemp.LSC.Mary = "return";
			}
		break;
		
		case "result_9": // вот тут - ключевой момент, если игрок нашёл Мэри - выбирай, какая девушка милее
			dialog.text = "Ne sono certa. "+pchar.name+", Vorrei restare sulla tua nave, se me lo permetti. Restare con te...";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive")
			{
				link.l1 = "(scegli Maria) Non capisci, Helen. Tutto il tuo avvenire è ancora davanti a te, e non hai nulla di cui crucciarti. Io invece ho solo guerra, intrighi e un futuro avvolto nelle nebbie davanti a me. Tu devi costruirti una vita tua, e per uno sbandato come me non c’è posto accanto a te.";
				link.l1.go = "result_10";
				link.l2 = "È più di quanto potessi sperare, Helen. Certo che non voglio perderti, ma sarebbe meglio per te andare a Isla Tesoro. Chissà dove mi condurrà ancora il destino. Ora ho davanti a me guerra, intrighi politici e solo incertezze.";
				link.l2.go = "result_15";
			}
			else
			{
				link.l1 = "È più di quanto potessi sperare, Helen. Certo che non voglio perderti, ma sarebbe meglio per te andare a Isla Tesoro. Chi lo sa dove mi condurrà il destino. Per ora mi aspettano guerra, intrighi politici e un futuro incerto.";
				link.l1.go = "result_15";
			}
		break;
		
		case "result_10":
			dialog.text = ""+pchar.name+"Non mentirmi. Non vuoi solo... Dimmi, chi è lei? È quella sgualdrina rossa della Città delle Navi Perdute, dico bene?";
			link.l1 = "Hélène! Sto cercando di dirti ciò che credo sia meglio per te! Come puoi non capirlo?!";
			link.l1.go = "result_11";
		break;
		
		case "result_11":
			dialog.text = "Oh certo, ma davvero... E dimmi, come ha fatto a stregarti, eh? Che cosa ha lei che *io* non ho?! È davvero così brava? Eh, "+pchar.name+"... Ebbene, è la tua decisione, non mi resta che tornare alla mia isola. Non posso frappormi tra voi due. \nGrazie di cuore per tutto ciò che hai fatto per me, Charles. Sei l’uomo migliore che abbia mai incontrato. Spero che potremo restare amici?";
			link.l1 = "Certo... Helen, ci rivedremo a Isla Tesoro. Vuoi che ti ci porti?";
			link.l1.go = "result_12";
		break;
		
		case "result_12":
			dialog.text = "Non serve. Mi procurerò una nuova nave. Ho messo da parte abbastanza denaro per comprare e allestire una goletta mentre ero al tuo servizio. Salperò ancora una volta su una nuova 'Arcobaleno'.";
			link.l1 = "Sono lieto, Helene, che tu sia stata così... parsimoniosa. Ma navigare su una goletta non si addice alla Regina dei Pirati di Isla Tesoro. Presto, dovresti procurarti una fregata tutta tua.";
			link.l1.go = "result_13";
		break;
		
		case "result_13":
			dialog.text = "Forse, "+pchar.name+". Va bene. Andrò al cantiere navale ma prima... dammi un bacio d’addio... Ti prego...?";
			link.l1 = "Hélène...";
			link.l1.go = "result_14";
		break;
		
		case "result_14": // прощальный поцелуй
			DialogExit();
			SetMusic("music_romantic");
			SetLaunchFrameFormParam("", "", 0, 12);
			SetLaunchFrameFormPic("loading\inside\kiss.tga");
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 0, 20); //крутим время
			RecalculateJumpTable();
			DoQuestCheckDelay("Saga_HelenaBye", 0.5);
			pchar.questTemp.LSC.Mary = "return"; // к Мэри
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false); // лесник . пирс. 
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false); // ворота.
			InterfaceStates.Buttons.Save.enable = true;//можно сохраняться
		break;
		
		case "result_15":
			dialog.text = "Il mio destino è legato al tuo da quando ci siamo incontrati. Non lo capisci?"+pchar.name+"? Ti seguirò fino ai confini del mondo!";
			link.l1 = "E che ne è di tuo padre? Laurence Beltrope? È il mio nemico...";
			link.l1.go = "result_16";
		break;
		
		case "result_16":
			dialog.text = "Mio padre è Sean McArthur. Gli volevo bene e piango la sua morte. Era l’unico padre che avessi. E quel pirata... non voglio nemmeno nominarlo.";
			link.l1 = "Hélène... Mia cara Hélène!";
			link.l1.go = "result_17";
		break;
		
		case "result_17":
			dialog.text = ""+pchar.name+", Ho sempre desiderato dirti che sei l’uomo più straordinario che abbia mai incontrato! Hai fatto così tanto per me che non potrò mai ripagarti. Voglio restare con te. Per sempre. Se lo desideri, ti sposerò… Ti amo.";
			link.l1 = "Saremo insieme. Lo giuro!"; // а куда же ты теперь денешься :)
			if (!CheckAttribute(pchar, "questTemp.Saga.Helena_friend")) {
				link.l1.go = "result_17A";
			} else {
				link.l1.go = "result_18";
			}
		break;
		
		case "result_17A":
			dialog.text = "Promettimi che farai qualcosa per me subito? E, per favore, non ridere!";
			link.l1 = "Lo giuro, mia cara!";
			link.l1.go = "result_17A_1";
		break;
		
		case "result_17A_1":
			dialog.text = "Chiamami col mio vero nome. Ti prego!";
			link.l1 = "Ti amo, Hélène MacArthur.";
			link.l1.go = "result_18";
		break;
		
		case "result_18":
			dialog.text = ""+pchar.name+", caro... Abbracciami! Ho atteso questo momento per troppo tempo!";
			link.l1 = "Hélène, mia cara...";
			link.l1.go = "result_19";
		break;
		
		case "result_19": // романтик-сцена
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			StartQuestMovie(true, true, true);
			PlayStereoOGG("music_romantic");
			InterfaceStates.Buttons.Save.enable = false;//запретить сохраняться
			locCameraRotateAroundHero(0.0, 2.0, 0.0, 0.01, 0.0, 2.0, 0.0, 580);
			Pchar.FuncCameraFly = "";
			DoQuestCheckDelay("Saga_HelenaRomantic", 20.0);
			pchar.GenQuest.MusicContinue = true;
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			DeleteAttribute(pchar, "questTemp.LSC.MaryWait");
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false); // лесник . пирс. 
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false); // ворота.																					   
			
			pchar.quest.HelenUpgradeShip.win_condition.l1 = "Timer";
			pchar.quest.HelenUpgradeShip.win_condition.l1.date.day = GetAddingDataDay(0, 0, 180);
			pchar.quest.HelenUpgradeShip.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 180);
			pchar.quest.HelenUpgradeShip.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 180);
			pchar.quest.HelenUpgradeShip.win_condition.l2 = "location";
			pchar.quest.HelenUpgradeShip.win_condition.l2.location = "PortRoyal_town";
			pchar.quest.HelenUpgradeShip.function = "HelenUpgradeShip";
			
			// Квест Лонгвея "Путеводная звезда", начало 5 этапа
			if (GetCharacterIndex("Longway") != -1 && CheckPassengerInCharacter(pchar, "Longway") && CheckAttribute(pchar, "questTemp.PZ_Etap5_Start") && !CheckAttribute(pchar, "questTemp.PZ_ProvalFinal"))
			{
				PChar.quest.PZ_Etap5_Start.win_condition.l1 = "location";
				PChar.quest.PZ_Etap5_Start.win_condition.l1.location = "Pirates_town";
				PChar.quest.PZ_Etap5_Start.win_condition = "PZ_Etap5_Start";
				AddMapQuestMarkCity("Pirates", false);
			}
		break;
		
		case "happy":
			dialog.text = ""+pchar.name+"! È stato... incredibile! Non voglio andare da nessun'altra parte... Restiamo qui fino al mattino. Il mondo può aspettare!";
			link.l1 = "Lasciamo perdere per ora, Helen!";
			link.l1.go = "happy_1";
		break;
		
		case "happy_1":
			DialogExit();
			LSC_MaryLoveWaitTime();
			SetLaunchFrameFormParam("Next morning...", "", 0, 4);
			LaunchFrameForm();
			DoQuestCheckDelay("Saga_HelenaRomantic_5", 4.0);
			pchar.questTemp.Saga.Helena_officer = "true"; // показатель, что Элен - наша навсегда
			
			pchar.GenQuest.BrothelCount = 0;
			
			pchar.quest.Helen_GiveSex.win_condition.l1 = "Timer";
			pchar.quest.Helen_GiveSex.win_condition.l1.date.day = GetAddingDataDay(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l1.date.month = GetAddingDataMonth(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l1.date.year  = GetAddingDataYear(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l2 = "Location_Type";
			pchar.quest.Helen_GiveSex.win_condition.l2.location_type = "town";
			pchar.quest.Helen_GiveSex.function = "Helen_GiveSex";
			
			// Запуск квеста Дороже золота
			SetFunctionTimerCondition("GoldenGirl_Start", 0, 0, 1, false);
		break;
		
	// -------------------------------------------- провалы саги ------------------------------------
		case "failcenturion":
			dialog.text = "Capitano! Jackman è morto... La mia famiglia è finalmente al sicuro?";
			link.l1 = "Sì, Helen, siete tutti salvi. Ma il 'Centurion' è affondato insieme a tutti i documenti che ci avrebbero potuto aiutare a trovare la tomba di tua madre e dimostrare il tuo diritto su Isla Tesoro... Eh... Ora dovrò assaltare Tortuga da solo...";
			link.l1.go = "failcenturion_1";
		break;
		
		case "failcenturion_1":
			dialog.text = ""+pchar.name+", non crucciarti così tanto. Non possiamo farci nulla, ormai. E nemmeno preoccuparti per me, me la caverò benissimo senza quell’isola. Ti ringrazio per tutto ciò che hai fatto per me!";
			link.l1 = "Sembra quasi che tu stia per... lasciarmi, vero?";
			link.l1.go = "failcenturion_2";
		break;
		
		case "failcenturion_2":
			dialog.text = "Sì, mio capitano. Sono riuscita a raccogliere abbastanza monete per comprare e armare una goletta. Navigherò di nuovo sulla mia ‘Arcobaleno’. Ci rivedremo a Blueweld... Sto tornando a casa.";
			link.l1 = "Ebbene... in bocca al lupo, Hélène!";
			link.l1.go = "failcenturion_3";
		break;
		
		case "failcenturion_3":
			DialogExit();
			RemovePassenger(pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 5.0);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary") && GetCharacterIndex("Mary") != -1 && !CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) // patch-6
			{
				pchar.questTemp.LSC.Mary = "return"; // к Мэри
			}
		break;
		
		case "late_l1":
			dialog.text = "Ebbene, mio capitano... Pare che abbiamo fallito. Addio. Torno a casa. Sotto il tuo comando ho guadagnato abbastanza da comprarmi una nuova goletta. Ci rivedremo in mare!";
			link.l1 = "Buona fortuna, Helene. Mi dispiace per tutto. Addio.";
			link.l1.go = "failcenturion_3";
		break;
		
		case "late_l2":
			dialog.text = "Capitano! Jackman è morto... Dunque la mia famiglia è fuori pericolo, non è vero?";
			link.l1 = "Sì, Helen, qui è sicuro. Ma io non sono affatto soddisfatto, ho perso troppo tempo e ora Isla Tesoro è una colonia inglese. Sei rimasta senza eredità, così dovrò assaltare Tortuga da solo...";
			link.l1.go = "failcenturion_1";
		break;
		
		case "late_l3":
			dialog.text = ""+pchar.name+", cosa ti ha detto l’avvocato?";
			link.l1 = "Ho perso troppo tempo e Isla Tesoro ora è una colonia inglese. Sei rimasta senza eredità, quindi dovrò assaltare Tortuga da solo... Ahimè, abbiamo perso.";
			link.l1.go = "failcenturion_1";
		break;
	// <-- провалы Саги
		
		// секс - Элен соглашается не всегда (голова болит, а что вы хотели? :)) и сама не требует секса
		case "cabin_sex":
			if (CheckAttribute(npchar, "quest.refusesex")) {
				dialog.text = "No, tesoro, così non va.";
				link.l1 = "Ebbene, perché no?!";
				link.l1.go = "refuse";
				break;
			}
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
			if (hrand(4) == 0)// вероятность отказа 20%
			{
				dialog.text = RandPhraseSimple(""+pchar.name+" Oggi non mi sento bene. Ti prego, non prendertela, non è colpa tua. Meglio rimandare...",""+pchar.name+" , caro, sono stata così stanca negli ultimi giorni. A dire il vero, vorrei solo dormire. Perdonami. Facciamo un’altra volta.");
				link.l1 = RandPhraseSimple("Va bene...","Va bene. Come desideri tu...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = RandPhraseSimple(""+pchar.name+", l’atmosfera è perfetta, andiamo!",""+pchar.name+", certo, senza fare domande! Andiamo!");
				link.l1 = RandPhraseSimple("Questa è la mia ragazza...","Sei così incantevole, Helen...");
				link.l1.go = "exit";
				AddDialogExitQuest("cabin_sex_go");
			}
		break;
		
		case "sex_after":
			dialog.text = LinkRandPhrase(RandPhraseSimple("È stato meraviglioso, "+pchar.name+"!..","Sei stato magnifico come sempre, caro..."),RandPhraseSimple("È stato magnifico, Charles!","Mi son davvero goduta il tempo insieme, caro!"),RandPhraseSimple("Mai un momento di noia con te, mio capitano!","Sei stato magnifico, tesoro!"));
			link.l1 = RandPhraseSimple("Ti amo...","È sempre un piacere stare con te, Hélène...");
			link.l1.go = "exit";
			NextDiag.TempNode = "Helena_officer";
			chrDisableReloadToLocation = false;//открыть локаци.
		break;
		
		case "room_sex":
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "tavern")
			{
				dialog.text = ""+pchar.name+", sai che sono sempre lieta di... Ma ora non è il momento giusto – dobbiamo acciuffare quel furfante di Thibaut prima che sparisca.";
				link.l1 = "Hai sempre ragione tu, Helen...";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(npchar, "quest.refusesex")) {
				dialog.text = "No, tesoro, così non va.";
				link.l1 = "Ebbene, perché no?!";
				link.l1.go = "refuse";
				break;
			}
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
			if (hrand(4) == 0) // вероятность отказа 20%
			{
				dialog.text = RandPhraseSimple(""+pchar.name+", oggi non mi sento bene. Non prenderla a male, ti prego. Meglio rimandare...",""+pchar.name+" , caro, sono così sfinita in questi ultimi giorni. A dire il vero, vorrei solo dormire. Perdonami. Facciamo un'altra volta, ti prego.");
				link.l1 = RandPhraseSimple("Va bene...","Va bene. Come desideri tu...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = RandPhraseSimple(""+pchar.name+"  Ti amo! Andiamo!",""+pchar.name+", aye aye capitano! Andiamo!");
				link.l1 = RandPhraseSimple("Sei la mia brava ragazza...","Sei incantevole, Helen...");
				link.l1.go = "room_sex_go";
			}
		break;
		
		case "room_sex_go":
			DialogExit();
			chrDisableReloadToLocation = true;
			//npchar.quest.daily_sex_room = true; // для первого раза в таверне чтобы счетчик запустить . лесник
			//npchar.quest.daily_sex_cabin = true;
			if (sti(pchar.money) >= 10) AddMoneyToCharacter(pchar, -10);
			sld = CharacterFromID("Helena");
			ChangeCharacterAddressGroup(sld, loadedLocation.fastreload + "_tavern_upstairs", "quest", "quest3");
			DoFunctionReloadToLocation(loadedLocation.fastreload + "_tavern_upstairs", "quest", "quest4", "GiveKissInRoom");
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Helena_officer":
			ref rLoc = &Locations[FindLocation(pchar.location)];
			dialog.text = LinkRandPhrase("Sì, "+pchar.name+"?","Sì, mio capitano?","Ascolto, "+pchar.name+"...");
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.CutlassTraining")) {
				DeleteAttribute(pchar, "questTemp.HelenDrinking.CutlassTraining");
				dialog.text = "Guarda qui, mio capitano!";
				link.l1 = "Accidenti, che presa! Vedo che non hai perso tempo, Helen.";
				link.l1.go = "cutlass_training";
				NextDiag.TempNode = "Helena_officer";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && sti(pchar.GenQuest.BrothelCount) > 0 && !CheckAttribute(npchar, "quest.refusesex")) {
				dialog.text = "Tesoro, riguardo alle tue visite alle puttane.";
				npchar.quest.refusesex = true;
				link.l1 = "Cosa? Helen, ti sbagli di grosso! Io solo...";
				link.l1.go = "brothel_found";
				NextDiag.TempNode = "Helena_officer";
				SetFunctionTimerCondition("Helena_ClearRefuseSex", 0, 0, 180, false);
				DeleteQuestCondition("Helen_GiveSex");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Hélène, sto per avventurarmi nella perduta città indiana di Tayasal. Non ti mentirò: è un viaggio dannatamente pericoloso e, per di più, ci sarà da teletrasportarsi attraverso quell’idolo. Vuoi… seguirmi?";
				Link.l4.go = "tieyasal";
			}
       ////////////////////////казначей///////////////////////////////////////////////////////////
           		// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Elen, dammi un rapporto completo della nave.";
			    Link.l11.go = "QMASTER_1";
			        
			    // Warship. Автозакупка товара
				Link.l12 = "Voglio che tu acquisti certe merci ogni volta che gettiamo l’ancora.";
				Link.l12.go = "QMASTER_2";
			}
			
            /////////////////////////////////////казначей////////////////////////////////////////////////////////////     			
			if (CheckAttribute(NPChar, "IsCompanionClone"))//////////////////компаньон//////////////////////////////////////////////
			{
				//dialog.text = "Son giunto al vostro comando, capitano.";
				Link.l2 = "Helen, devo impartirti alcuni ordini.";
				Link.l2.go = "Companion_Tasks";
				
				sld = GetCharacter(sti(npchar.RealCompanionIdx));
				if (CheckAttribute(pchar, "questTemp.HelenDrinking.Rainbow") && sld.ship.type == pchar.questTemp.HelenDrinking.Rainbow && CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) {
					DeleteAttribute(link, "");
					dialog.text = "Pensi che sia divertente?";
					link.l1 = "Bel vascello, vero? L’ho preso per te, Helen! Dimmi, quanta gente nei Caraibi può dire di aver regalato una nave vera alla propria dama, eh?";
					link.l1.go = "rainbow";
					
					NextDiag.TempNode = "Helena_officer";
					break;
				}
				
				NextDiag.TempNode = "Helena_officer";// не забыть менять в зависисомости от оффа
				break;
			}																															
			if (CheckAttribute(npchar, "quest.fugas"))
			{
				Link.l3 = "Hélène, ho bisogno del tuo consiglio.";
				Link.l3.go = "fugas";
			}
			Link.l1 = "Hélène, ho un incarico per te...";
            Link.l1.go = "stay_follow";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && pchar.location == Get_My_Cabin() && GetNpcQuestPastDayWOInit(npchar, "sex_date") >= 1) // mitrokosta - очередные исправления интима
			{
				Link.l2 = RandPhraseSimple("Hélène, restiamo nella cabina insieme… solo noi due… per qualche ora? Che ne dici?","Tesoro, perché non passiamo qualche ora insieme, solo noi due? Ti piace l’idea?");
				Link.l2.go = "cabin_sex";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && rLoc.type == "tavern" && sti(pchar.money) >= 10 && GetNpcQuestPastDayWOInit(npchar, "sex_date") >= 1) // mitrokosta - очередные исправления интима
			{
				Link.l2 = RandPhraseSimple("Helen, che ne dici se affittiamo una stanza e ci godiamo un po’ d’intimità... solo noi due per qualche ora? Che ne pensi, eh?","Amore, che ne dici di trascorrere insieme le prossime ore, solo io e te? Affittiamo una stanza... che ne pensi?");
				Link.l2.go = "room_sex";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && rLoc.type == "town" && sti(pchar.money) >= 1000 && GetNpcQuestPastDayWOInit(npchar, "special_sex_date") >= 30 && !CheckAttribute(npchar, "quest.refusesex"))
			{
				Link.l2 = "Helen, cara, posso invitarti a passare un po' di tempo di qualità alla taverna?";
				Link.l2.go = "special_sex";
			}
			if (CheckAttribute(pchar, "questTemp.MysteryPortRoyal_Helena")) {
				link.l4 = "Helen, pare che abbia trovato l’ultimo testamento del tuo spasimante – Francis. Ti ha lasciato la sua eredità.";
				link.l4.go = "MysteryPortRoyal_Helena_1";
			}
			if (CheckCharacterItem(pchar, "pirate_cutlass") && !CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) {
				link.l4 = "Penso che questa sciabola ora sia tua. Blaise è il tuo cosiddetto zio...";
				link.l4.go = "give_cutlass";
			}
			link.l9 = "Niente per ora, Helene.";
			NPChar.id = "Helena"; // лесник . Идентификация Элен на всяк. случай . если потеряет сознание.
			link.l9.go = "exit";
			NextDiag.TempNode = "Helena_officer";
		break;
		
		/////////////////////////// ответы для казнаячея - Элен ..(элен казначей - ужас!))///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Charles, caro, hai la febbre o che? Vuoi davvero che scenda in stiva a spazzar via i topi e contarli uno per uno?";
			Link.l1 = "D'accordo, scusami tesoro, tutta colpa mia...";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "E anch’io vorrei il mio vascello di linea, cento cannoni e venti nodi di vento nelle vele. Capitana lo sono da sempre, proprio come te. Vai a scocciare il quartiermastro con queste storie, dannazione.";
			link.l1 = "Hai ragione, Helen. Perdona la mia sbadataggine.";
			link.l1.go = "exit";
		break;
		//Указания для компаньона 19.02.08 -->/////////////////////////////////////////////////////////////////////////////////////////
		case "Companion_Tasks":
			dialog.Text = "Sono tutta orecchi.";
			Link.l1 = "Riguardo la nostra politica d’abbordaggio...";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "Riguardo alla nave che comandi...";
			Link.l2.go = "Companion_TaskChange";
			Link.l8 = "Niente finora.";
			Link.l8.go = "exit";
			 
		break;
		
		case "Companion_TaskBoarding":
			dialog.Text = "Qual è il tuo desiderio, mio capitano?";
			Link.l1 = "Non voglio che tu abbordi nessuna nave. Tieni te stesso e i tuoi uomini al sicuro.";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "Voglio che tu assalga le navi nemiche alla prima occasione.";
			Link.l2.go = "Companion_TaskBoardingYes";
		break;
		
		case "Companion_TaskChange":
			dialog.Text = "Sì, mio capitano?";
			Link.l1 = "Ti sarei grata se evitassi di cambiare nave dopo l’abbordaggio. Questa per me vale più dell’oro.";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "Se ti capita d'abbordare qualcuno, dà una bella occhiata alla nave preda. Se ne vale la pena, sentiti pure libero di prenderla per te.";
			Link.l2.go = "Companion_TaskChangeYes";
		break;
		
		case "Companion_TaskBoardingNo":
			dialog.Text = "D’accordo, ci rifletterò su.";
			Link.l1 = "Ci penserà su... Già, come se potessi davvero darle ordini io.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
		break;
		
		case "Companion_TaskBoardingYes":
			dialog.Text = "Va bene, ci rifletterò su.";
			Link.l1 = "Ci penserà su... Già, come se potessi davvero darle degli ordini.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
		break;
		
		case "Companion_TaskChangeNo":
			dialog.Text = "D'accordo, ci penserò.";
			Link.l1 = "Ci rifletterà... Già, come se potessi davvero darle degli ordini.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;
		
		case "Companion_TaskChangeYes":
			dialog.Text = "Va bene, ci penserò su.";
			Link.l1 = "Ci penserà su... Già, come se potessi davvero darle degli ordini.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;
	//	<========//////////////////////////////////////																																			  
		
		case "stay_follow":
            dialog.Text = "Ordini?";
            Link.l1 = "Fermati qui!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Seguimi e non perdermi di vista!";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Cambia il tipo di munizione per le tue armi da fuoco.";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Scegli il tipo di munizione:";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");;
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;		
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "Subito, capitano!";
            Link.l1 = "...";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Subito, capitano!";
            Link.l1 = "...";
            Link.l1.go = "Exit";
        break;
		//<-- ----------------------------------- офицерский блок ----------------------------------------
		
		// --> суп из черепахи
		case "terrapin_grot":
			dialog.text = "Eccoti qua! Finalmente ti ho trovato... Che impresa, mio capitano! Non ho mai visto nessuno correre sui tetti e saltare da quell’altezza vertiginosa! Il mio cuore stava per scoppiare! Un giorno mi farai morire con questi tuoi colpi di testa, caro... Oh, non sei solo... Chi è questa ragazza?";
			link.l1 = "Questa è Catherine Fox, figlia del colonnello Fox, comandante del rinomato Reggimento di Fanteria Marittima inglese, le ‘Volpi di Mare’. La stiamo portando ad Antigua.";
			link.l1.go = "terrapin_grot_1";
		break;
		
		case "terrapin_grot_1":
			dialog.text = "Ah davvero... Benvenuta a bordo, signorina Volpe!  No no, non c'è bisogno che ti aggrappi al braccio del capitano de Maure, sai benissimo camminare da sola! E ora filiamo sulla scialuppa – dobbiamo levare l’ancora di qui."; 
			link.l1 = "Ah! Grazie, Helen! Cosa farei senza di te? Catherine, seguici!";
			link.l1.go = "terrapin_grot_2";
		break;
		
		case "terrapin_grot_2":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			Terrapin_GotoShip();
		break;
		// <-- суп из черепахи
		
		// --> калеуче
		case "on_coast":
			dialog.text = "Finalmente ti sei svegliato, caro! Come ti senti? Mi hai fatto prendere uno spavento del diavolo...";
			link.l1 = "Hélène, che è successo? La testa mi scoppia...";
			link.l1.go = "on_coast_1";
		break;
		
		case "on_coast_1":
			dialog.text = "Quando siamo entrati nella cabina del capitano, tu giacevi ancora a terra. Il mio cuore quasi si fermò! I ragazzi ti hanno sollevato e trascinato di nuovo sulla nostra nave – appena in tempo, perché i morti stesi sul ponte cominciavano a rialzarsi.\nChe orrore! Quasi mi fa venire voglia di trovarmi un Dio! Erano del tutto insensibili alle nostre lame e pallottole! Abbiamo tagliato in fretta le cime e tentato di salpare, ma una raffica dalla loro nave ha colpito duro la nostra e abbiamo perso il controllo. Poi hanno issato le vele e sono spariti in un lampo.\nLa nostra nave è finita sugli scogli, così siamo dovuti fuggire su questa riva prima che la tempesta la distruggesse. Oggi sono morti tanti buoni marinai, ma alla fine la nave si è salvata... se solo non avessi dato l’ordine di abbandonarla...";
			link.l1 = "Non è colpa tua, Helene. Era la scelta giusta. Che farei io senza di te?";
			link.l1.go = "on_coast_2";
		break;
		
		case "on_coast_2":
			dialog.text = "Ti ho trascinato sulla barca e poi portato a riva. Sembravi uno già passato a miglior vita, solo il cuore ti batteva piano piano. Guarda! Le mie mani tremano ancora";
			link.l1 = "Grazie, amore. Ti sono debitrice. Da quanto tempo sono stesa qui?";
			link.l1.go = "on_coast_3";
		break;
		
		case "on_coast_3":
			dialog.text = "Per un giorno intero. Ho lavato e fasciato le tue ferite, ti ho dato delle medicine e ti ho versato anche un po' di rum. Ora devi rimetterti in sesto!";
			link.l1 = "Non morirò stavolta, caro. Anche se non mi sento affatto bene... urgh...";
			link.l1.go = "on_coast_4";
		break;
		
		case "on_coast_4":
			dialog.text = "Dimmi... Era davvero l'Olandese Volante, Charles? Perché ci hanno assaliti? E come mai non hanno sparato appena ci hanno avvistati, ma hanno cercato subito di mandarci a fondo dopo essere saliti a bordo?";
			link.l1 = "Il loro capitano aveva bisogno di quell’amuleto, quello di cui avevo parlato con Tuttuathapak, uno stregone indiano. Non so perché lo volessero... ma appena il loro capo mise le mani sull’amuleto, ci hanno scaricati... Dio misericordioso, che incubo maledetto! Una nave governata dai morti che camminano! Da non crederci...";
			link.l1.go = "on_coast_5";
		break;
		
		case "on_coast_5":
			dialog.text = "Ah, ora toccava a noi imbatterci nell’Olandese Volante. Dannazione! Mi si raggela il sangue! Al prossimo porto, vado in chiesa, accendo una candela e prego Nostro Signore Gesù Cristo per la nostra miracolosa salvezza. Diavolo, mi sento così riconoscente che pregherò persino qualche santo papista...";
			link.l1 = "Ci sarò anch'io, Helen, è da un bel pezzo che non mi confesso come si deve... Ma prima dobbiamo tornare in quel villaggio. Devo raccontare tutto a Tuttuathapak. Quella maledetta nave ci ha assaltati per colpa dell’amuleto! Spero che quel demonio dalla pelle rossa abbia qualche idea sul perché quei morti ambulanti ne avessero bisogno, dannazione.";
			link.l1.go = "on_coast_6";
		break;
		
		case "on_coast_6":
			dialog.text = "D'accordo. Ma dobbiamo stare all'erta – le tue ferite sono ancora fresche.";
			link.l1 = "Ma tu mi aiuterai a guarire più in fretta, vero? Ti amo, Helen...";
			link.l1.go = "on_coast_7";
		break;
		
		case "on_coast_7":
			chrDisableReloadToLocation = false;//открыть локацию
			dialog.text = "Anch’io ti amo, mio tesoro...";
			link.l1 = "...";
			link.l1.go = "on_coast_8";
		break;
		
		case "on_coast_8":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			AddQuestRecord("Caleuche", "5");
		break;
		// <-- калеуче
		
		// на Тайясаль
		case "tieyasal":
			dialog.text = ""+pchar.name+", ti ho già detto una volta che ormai i nostri destini sono intrecciati. Il tuo fato è il mio fato. Quando salpiamo?";
			link.l1 = "Ne sono davvero lieta. Te ne parlerò più tardi, quando ci arriveremo. Dobbiamo prepararci per bene.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Sono pronta, mio capitano! Ti seguirò fino ai confini della terra!";
			link.l1 = "Grazie, amore mio...";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "20");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		// на Исла Тесоро
		case "islatesoro":
			dialog.text = "Oh, "+pchar.name+"! Lieto di vederti! Che ci fai qui sull'Isla Tesoro?";
			link.l1 = "Come al solito – affari. Ma volevo anche passare a trovarti. Come va, Helen?";
			link.l1.go = "islatesoro_1";
		break;
		
		case "islatesoro_1":
			DialogExit();
			NextDiag.CurrentNode = "islatesoro";
		break;
		
		// Jason Дороже золота
		case "GoldenGirl":
			dialog.text = "Che c’è che non va col nostro carissimo governatore, Capitano? Chi dobbiamo prendere a calci stavolta? Spagnoli, filibustieri o qualche canaglia peggiore?";
			link.l1 = "È peggio, Hélène, molto peggio. Il governatore si prepara a far visita a una cortigiana di lusso e io dovrei accompagnarlo come una curiosità. Ha promesso alla sua amante di portare con sé un vero corsaro, un avventuriero, insomma un vecchio lupo di mare. Quindi mi aspettano chiacchiere noiose, vino caro e nobili insipidi.";
			link.l1.go = "GoldenGirl_1";
			link.l2 = "Tutt'altro, si tratta d'un invito a un piacevole ritrovo mondano, organizzato da una gentildonna. Sua Eccellenza m'ha colto di sorpresa nel chiedermi d'accompagnarlo, ma a dire il vero, son lieta d'avere finalmente altro a cui pensare che non siano le solite faccende.";
			link.l2.go = "GoldenGirl_5";
		break;
		
		case "GoldenGirl_1":
			dialog.text = "Aye... dunque il temibile Capitano Charles de Maure si vestirà e ballerà come una scimmietta per farli ridere? Che tenerezza! Ma ho un’idea migliore. Spieghiamo le vele e leviamoci al diavolo da qui. Se ti va una vacanza come si deve, mettiamo la prua su Isla Tesoro. Lì siamo sempre i benvenuti. Sole, sabbia bianca, vecchi amici, punch al rum, e dimentichiamoci di tutto il resto – come ti pare.";
			link.l1 = "Ascolta, tutto questo sembra un sogno, e mi piacerebbe... ma più tardi. Ho dato la mia parola al governatore, questa faccenda conta per il vecchio e...";
			link.l1.go = "GoldenGirl_2";
		break;
		
		case "GoldenGirl_2":
			dialog.text = "E allora? Credi forse che il tuo sangue nobile valga qualcosa per loro? Io magari non sono francese, ma so bene come funziona la loro 'alta società', e per loro Charles de Maure non è certo un capitano che gli uomini seguono e a cui affidano la vita. Non è un vero gentiluomo come loro. I veri gentiluomini non si spingono in mare né si battono tra le nebbie della polvere da sparo. Charles de Maure per loro è solo un curioso divertissement a tavola. Come una pantera ammaestrata o un servo nero travestito! Un giocattolo di lusso! Da quando ti lasci trattare così?!";
			link.l1 = "Hélène, ti prego, resta calma. Posso sopportare qualche occhiata storta per compiacere il governatore e assicurare un futuro più prospero. È sempre utile avere amici potenti. In fin dei conti, sarà più semplice che guidare un abbordaggio! E questi ‘buoni a nulla’ non sono sempre così. Perfino l’alta società cela qualche anima degna... o almeno così si dice.";
			link.l1.go = "GoldenGirl_3";
		break;
		
		case "GoldenGirl_3":
			dialog.text = "Come vuoi. (si sistema i capelli) Ma ti avverto: non c’è verso che mi infili in uno di quei vestiti pomposi. Se proprio devo venire, ci vado coi miei calzoni. Che svenissero pure tutte le signorine dei Caraibi, non me ne frega un accidente.";
			link.l1 = "Non avevo intenzione di costringerti. Non ha senso che soffriamo entrambi. Sopporterò questa festa e poi salperemo per Isla Tesoro. E come ricompensa, ho tenuto da parte una cassa di ottimo madeira spagnolo nella stiva...";
			link.l1.go = "GoldenGirl_4";
		break;
		
		case "GoldenGirl_4":
			dialog.text = "Oh oh oh, Charles! Dunque mi stai dicendo che non sono degna di tanta illustre compagnia? Che una ragazza in pantaloni ti rovinerebbe la serata? Che curioso. Va bene allora, ma ricordati di agghindarti come un damerino. Persino il cuore di una cortigiana si smuove davanti a una scimmia in abiti eleganti. Buona recita!";
			link.l1 = "Hélène, aspetta! Dannazione... donne!";
			link.l1.go = "GoldenGirl_8";
		break;
		
		case "GoldenGirl_5":
			dialog.text = "Sì, un po' di riposo ce lo siamo guadagnato, senza dubbio. Ma che mi fulmini Nettuno se mi infilo in un vestito elegante per questa faccenda. Secondo te, quanto lontano arriveranno le chiacchiere sulla tua donna che si veste da uomo e da lupo di mare?";
			link.l1 = "Ah... Non credo sia una gran bella idea. Come potrei dire... non è proprio un evento dove gli uomini portano mogli o dame perbene...";
			link.l1.go = "GoldenGirl_6";
		break;
		
		case "GoldenGirl_6":
			dialog.text = "Ah! Puttane e depravazione! Magnifico – dunque vai a una bisboccia! Perché non l’hai detto subito, maledizione? Ringrazia il cielo che non sono una strega gelosa pronta a spararti dove stai. Almeno, non ancora.";
			link.l1 = "Helen, ti prego, sto solo accompagnando il nostro governatore, me l'ha chiesto lui ed era più ostinato d'un mulo. Non ci saranno dannate cortigiane… Aspetta, mi è uscito male… voglio dire, non ci sarà nessun casino con cortigiane… oh maledizione! Voglio solo rendere i miei omaggi, tutto qui!";
			link.l1.go = "GoldenGirl_7";
		break;
		
		case "GoldenGirl_7":
			dialog.text = "Ti consiglio di vestirti con stile per 'rendere omaggio', Capitano de Maure. È tutta alta società, sai com'è. Sarebbe uno scandalo presentarsi senza colletto e polsini. Anche a un'orgia. Divertiti.";
			link.l1 = "Helen, aspetta! Maledizione... donne!";
			link.l1.go = "GoldenGirl_9";
		break;
		
		case "GoldenGirl_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlExit", 15.0);
			pchar.questTemp.GoldenGirl.Angry1 = "true";
		break;
		
		case "GoldenGirl_9":
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlExit", 15.0);
			pchar.questTemp.GoldenGirl.Angry2 = "true";
		break;
		
		case "GoldenGirl_10":
			dialog.text = "Polsini e un colletto, Capitano. E magari un po’ di pizzo. Ho sentito dire che è tornato di moda. Ma che ne so io!";
			link.l1 = "Oh Helen, su, dai!";
			link.l1.go = "GoldenGirl_11";
		break;
		
		case "GoldenGirl_11":
			DialogExit();
			NextDiag.CurrentNode = "GoldenGirl_10";
		break;
		
		case "GoldenGirl_12":
			dialog.text = "Guarda un po’! Il mio caro capitano torna a casa dopo la sua baldoria!";
			link.l1 = "...";
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angry1")) link.l1.go = "GoldenGirl_13";
			else link.l1.go = "GoldenGirl_18";
		break;
		
		case "GoldenGirl_13":
			dialog.text = "I signori locali approvano ancora la loro nuova scimmia? Raccontano che lo spettacolo di ieri notte sia stato leggendario! Hai scommesso navi e sgualdrine, sfidando in duello dei principini di sangue blu? Vuoi spiegarmi, per tutti i diavoli, che diavolo ti sta succedendo?";
			link.l1 = "Hélène, lasciami spiegare! Non è così semplice. Maledizione, mi dispiace, ma non avrei mai pensato di dover passare la notte dalla Madame Botot. Ho solo dormito lì, sì, da solo lo giuro! E sì, ho vinto una fregata al gioco delle carte. Puoi crederci?";
			link.l1.go = "GoldenGirl_14";
		break;
		
		case "GoldenGirl_14":
			dialog.text = "Ebbene! O sei un gran bugiardo, o un santo, o uno sciocco. Delle puttane e delle navi vinte parleremo dopo – ora raccontami ogni cosa del duello e perché tutti bisbigliano che avresti sfidato un principe reale?";
			link.l1 = "Non è certo un principe ereditario, solo un bastardo di conte. È figlio di un nobiluomo assai potente, il Conte de Levi Vantadur. Ascolta, non sono stata io a provocarlo! È stato lui a sfidarmi per primo, e ora devo vincere il duello senza fargli troppo male, altrimenti attirerò su di me l’ira di suo padre.";
			link.l1.go = "GoldenGirl_15";
		break;
		
		case "GoldenGirl_15":
			dialog.text = "Oh, 'solo il figlio di un conte', eh? Sei serio adesso, Charles?! E come diamine dovremmo farcela? E se bara? Ti farà fare una brutta fine!";
			link.l1 = "Ecco perché Sua Eccellenza mi ha fornito dei nobili secondi. Porterò solo loro con me — se le cose andranno a rotoli, almeno potrò dimostrare che tutto è stato fatto secondo il codice del duello e la legge. Ti chiedo di vegliare sulla fregata mentre sarò via.";
			link.l1.go = "GoldenGirl_16";
		break;
		
		case "GoldenGirl_16":
			dialog.text = "Fammi capire bene... Sei sparito per un giorno e una notte interi, e ti sei vinto una sgualdrina e una fregata a carte. E adesso stai per affrontare un bastardo nobile che non puoi nemmeno ammazzare, mentre *io* dovrei restarmene qui ad aspettare? E come diavolo dovrei sentirmi riguardo a tutto questo?!";
			link.l1 = "Hélène, ascolta, hai tutto il diritto di essere furiosa con me e ti chiedo davvero perdono, ma è solo che...";
			link.l1.go = "GoldenGirl_17";
		break;
		
		case "GoldenGirl_17":
			dialog.text = "Sai che c’è, ne ho abbastanza di tutto questo. Vai pure a fare le tue bravate! Intanto io ti spolvero la cabina e lavo i tuoi stracci! Non credere di essere fuori dai guai. Ne parleremo quando sarà finita. Penserò io alla tua nuova fregata, grande Capitano de Maure, non temere. Ah, e Capitano de Maure, cerca di non lasciarci la pelle... perché ho tutta l’intenzione di farlo io, dopo. Ora scusami, vado a chiudermi nei miei alloggi e a scolarmi quella bella madeira che ho trovato nella tua cabina.";
			link.l1 = "Hélène, lasciami spiegare! Maledizione... Eccoci di nuovo punto e a capo!";
			link.l1.go = "GoldenGirl_23";
		break;
		
		case "GoldenGirl_18":
			dialog.text = "Ho sentito che l’ultima moda parigina vuole che i gentiluomini vincano navi e cortigiane al tavolo da gioco invece di comprarle! E, per fare colpo, tocca pure sfidare i vecchi proprietari a duello. In che diavolo ti sei cacciato stavolta?!";
			link.l1 = "Hélène, non è così semplice. Maledizione, mi dispiace, ma mai avrei pensato di dover passare la notte dalla Madame Botot! Ieri sera è stata una battaglia d’ingegno lunga e sfiancante. E sì, ho vinto una maledetta fregata a carte. Riesci a crederci?";
			link.l1.go = "GoldenGirl_19";
		break;
		
		case "GoldenGirl_19":
			dialog.text = "Delizioso. Vuoi dire che ti sei aggiudicato anche una cortigiana? E la fregata che hai vinto, cosa hai messo in gioco? Non la nostra nave, vero? Dimmi che non l’hai fatto...";
			link.l1 = "Dovevo farlo. Ormai non ha importanza, alla fine ho vinto. Il mio avversario mi ha sfidato a duello e mi ha accusato di barare. È un bastardo figlio di un nobilastro potente, il Conte de Levi Vantadur. Il che significa che dovrò dannarmi per non ammazzarlo o ferirlo troppo.";
			link.l1.go = "GoldenGirl_20";
		break;
		
		case "GoldenGirl_20":
			dialog.text = "Farà lo stesso lui? Hai perso la testa, Charles? Metti in gioco la tua nave, la tua pelle, per un’altra donna?! Vale davvero tanto? Io non conto proprio nulla per te?!";
			link.l1 = "Hélène, non hai motivo d’esser gelosa, te lo giuro. È successo e basta. Dovevo farlo, e il governatore m’ha imposto ufficiali nobili come testimoni per assicurarsi che tutto si svolga secondo le regole. Non posso portare te né alcun uomo con me. Abbi cura della fregata mentre sarò via.";
			link.l1.go = "GoldenGirl_21";
		break;
		
		case "GoldenGirl_21":
			dialog.text = "Ma che meraviglia! Prima vai a bagordi con donne sconosciute e torni la mattina dopo, e io manco ti ho tagliato la gola per questo. Ora mi dici che hai quasi perso la nostra nave a carte, ma ti sei portato a casa una cortigiana! E adesso ti prepari a duellare per il suo ‘onore’ contro qualche bastardo di nobile schiatta che nemmeno puoi spedire all’altro mondo! Come dovrei sentirmi, dimmelo tu.";
			link.l1 = "Hélène, ascolta, hai tutto il diritto di essere furiosa con me, ma lasciami almeno spiegare...";
			link.l1.go = "GoldenGirl_22";
		break;
		
		case "GoldenGirl_22":
			dialog.text = "Sai che ti dico? Ne ho abbastanza di tutto questo. Vai pure a farti ammazzare nel tuo maledetto duello. Io mi occuperò della tua nuova fregata, gran Capitano de Maure, non ti crucciare. Ora scusami, vado a chiudermi nella mia cabina a scolarmi una bottiglia di quel buon madeira che ho trovato nella tua stiva. Ma se ti succede qualcosa, giuro sul cielo che scatenerò l’inferno su questa città, e seppellirò questo bordello e il palazzo dell’amata Eccellenza tua!";
			link.l1 = "Hélène, andrà tutto bene, fidati di me... Aspetta, dove diavolo vai?! Maledizione! Ci risiamo...";
			link.l1.go = "GoldenGirl_23";
		break;
		
		case "GoldenGirl_23":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlToFregat", 15.0);
		break;
		
		case "GoldenGirl_24":
			dialog.text = "Charles, hai delle spiegazioni da dare. Mi vuoi dire che diavolo è successo? Non ho messo una vedetta e i ragazzi si sono messi a bere... dei furfanti hanno assaltato la nostra nave e ci hanno legato mentre dormivamo. Poi quelle canaglie mi chiedevano fin dove saresti arrivato per salvarmi. Alla fine mi hanno rinchiusa nella stiva. Ho perso il conto dei giorni che ho passato ad aspettare!";
			link.l1 = "Quel bastardo voleva vendicarsi dell'umiliazione che gli ho inflitto. Temevo che ti avrebbe fatto del male! Sia ringraziato il cielo che stai bene!";
			link.l1.go = "GoldenGirl_25";
		break;
		
		case "GoldenGirl_25":
			dialog.text = "Immagino che tu abbia dovuto fare qualcosa per riportarmi indietro? Qualcosa di losco, vero?";
			link.l1 = "Tutto ciò che conta è che sei di nuovo con me. Ti ho delusa, Helen. Ti chiedo umilmente perdono! Spero che il tuo cuore trovi la forza di scusarmi!";
			link.l1.go = "GoldenGirl_26";
		break;
		
		case "GoldenGirl_26":
			dialog.text = "L’ho già fatto. Ho avuto tutto il tempo per rimuginare su ciò che ho detto… Mi dispiace anche a me, Charles. Se solo non avessi preso così a cuore i tuoi affari con quel marchese. Avrei messo una guardia come si deve quella notte, sarei stata più attenta. Ah! Non sono che una donna buona a nulla!";
			link.l1 = "Smettila di dirlo, il passato è passato. Ti amo e non ti lascerò mai più. Lo giuro!";
			link.l1.go = "GoldenGirl_27";
		break;
		
		case "GoldenGirl_27":
			dialog.text = "Immagino sia meglio che io non sappia esattamente cosa hai combinato, vero? Va bene, siamo di nuovo insieme e questo è ciò che conta davvero.";
			link.l1 = "Non ho segreti per te. Ti dirò tutto...";
			link.l1.go = "GoldenGirl_28";
		break;
		
		case "GoldenGirl_28":
			DialogExit();
			SetLaunchFrameFormParam("Some time has passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			npchar.dialog.currentnode = "GoldenGirl_28_1";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "GoldenGirl_28_1":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "Che pasticcio... So che non avevi altra scelta, ma come faccio a spiegare questo a Di Lu Parkes e ai suoi compari? Voglio dire, ora sei un fuorilegge!";
				link.l1 = "Ho scelto di pagare quel prezzo, ma in verità non avevo scelta. Non preoccuparti, troverò il modo di rimediare e ridare onore al nostro nome. E se non ci riuscirò, saremo sempre i benvenuti a Isla Tesoro! Posso affrontare tutto, se tu sei al mio fianco.";
			}
			else
			{
				dialog.text = "Che storia, Charles... Credo che tu non avessi altra scelta, ma e adesso? Quel dannato inglese sistemerà le cose o ci sarà guerra? Sei proprio sicuro di non voler venire a Basse-Terre a vedere come incatenano quel mascalzone?";
				link.l1 = "Sai, Helen, due settimane fa non me lo sarei mai perso. Ma oggi dico: al diavolo lui! Non mi importa più nemmeno della sua giusta punizione. Siamo di nuovo insieme, e questo è tutto ciò che conta!";
			}
			link.l1.go = "GoldenGirl_29";
		break;
		
		case "GoldenGirl_29":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "Sai che ti starò sempre accanto. Ah! Non è mica la prima volta che tu ed io ci ritroviamo fino al collo nella sentina. Ce la caveremo anche stavolta.";
				link.l1 = "Vero. Allarghiamo le vele, caro! L’orizzonte ci chiama!";
			}
			else
			{
				dialog.text = "Mi piace come ragioni, Charles! Basta nobili: francesi, inglesi, spagnoli – tutti uguali. Credo che ci siamo meritati una vacanza!";
				link.l1 = "D'accordo. Solo tu ed io! Niente più governatori né quei dannati nobili di sangue!";
			}
			link.l1.go = "GoldenGirl_30";
		break;
		
		case "GoldenGirl_30":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "Aye, aye, Capitano!";
				link.l1 = "";
			}
			else
			{
				dialog.text = "Sembra delizioso! Vado a dire ai ragazzi che è ora di salpare! E Charles...";
				link.l1 = "Lo so, Helen, lo so. Ti raggiungo tra un attimo.";
			}
			link.l1.go = "GoldenGirl_31";
		break;
		
		case "GoldenGirl_31":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "GoldenGirl_GirlGoOnBoard", 10.0);
		break;
		
		case "GoldenGirl_32":
			dialog.text = "Charles, ce l’hai fatta! I portoghesi mi hanno raccontato tutto! Che avventura!";
			link.l1 = "Grazie al cielo che sei viva, Helen! Non hai idea di quanto mi rallegri rivederti!";
			link.l1.go = "GoldenGirl_33";
		break;
		
		case "GoldenGirl_33":
			dialog.text = "A proposito. Mi avevi promesso di raccontarmi qualcosa, ricordi? Qualcosa di grosso e contorto. Ecco la tua occasione, Capitano. Che diavolo è successo?!";
			link.l1 = "Ti amo, Hélène. Tutto il resto non conta.";
			link.l1.go = "GoldenGirl_34";
		break;
		
		case "GoldenGirl_34":
			dialog.text = "Aye,   mi sei stato d’aiuto, ma... Maledizione, anch’io, Charles. Ti amo anch’io. Mio Dio, quanto mi sei mancato!";
			link.l1 = "Anch’io. Vieni con me, stanotte non ti lascio, nemmeno se il cielo dovesse crollare su questa lurida città. Non ti lascerò mai più. Mai.";
			link.l1.go = "GoldenGirl_35";
		break;
		
		case "GoldenGirl_35":
			dialog.text = "Immagino sia meglio che io non sappia esattamente cosa hai combinato, vero? Eh già, siamo di nuovo insieme e questo è ciò che conta davvero.";
			link.l1 = "Non ho segreti per te. Ti dirò tutto...";
			link.l1.go = "GoldenGirl_36";
		break;
		
		case "GoldenGirl_36":
			DialogExit();
			SetLaunchFrameFormParam("Some time has passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			npchar.dialog.currentnode = "GoldenGirl_36_1";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "GoldenGirl_36_1":
			dialog.text = "Incredibile! Hai appena detto che Francia e Inghilterra stanno per dichiararsi guerra a causa mia?";
			link.l1 = "No, Helen. È perché ho commesso un errore madornale di giudizio. Ma dovevo riportarti indietro e rimettere tutto a posto.";
			link.l1.go = "GoldenGirl_37";
		break;
		
		case "GoldenGirl_37":
			dialog.text = "Tutto ciò è davvero commovente e romantico, sono quasi pronta a dimenticare come è iniziata tutta questa faccenda. Quasi. Ma seriamente, ti hanno arrestato solo perché i portoghesi hanno dato il nome sbagliato a quella maledetta brigantina?";
			link.l1 = "Al contrario, mi ha dato proprio quella giusta! Vorrei sapere come diavolo ci sia riuscito, e soprattutto perché. E a proposito, dov’è finito quel furfante?!";
			link.l1.go = "GoldenGirl_38";
		break;
		
		case "GoldenGirl_38":
			dialog.text = "Se n'è andato. Appena mi ha portata qui. Non volevo approfittare dell’‘ospitalità’ della cortigiana che hai vinto, così ho chiesto a Bartholomew di affittarmi una stanza. Ha pagato e poi sparito senza una parola. Anzi, no, aspetta – ti ha lasciato una lettera!";
			link.l1 = "Una lettera? Da Bartolomeo il Portoghese? Questa è una novità. Non mi piace affatto dove sta andando a parare...";
			link.l1.go = "GoldenGirl_39";
		break;
		
		case "GoldenGirl_39":
			dialog.text = "Bene, ti lascio qui a leggere mentre vado a salutare i ragazzi. Devono essere in pensiero. Mai avrei detto che mi sarebbero mancate quelle facce tristi da cani bastonati! Nel frattempo cerca di non cacciarti subito in un altro pasticcio!";
			link.l1 = "Maledizione...  Ancora non riesco a credere di averti riportato indietro!";
			link.l1.go = "GoldenGirl_40";
		break;
		
		case "GoldenGirl_40":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_SPGirlReturn", 10.0);
		break;
		
		// Jason Долго и счастливо
		case "LongHappy":
			RemoveItems(pchar, "potionwine", 2);
			dialog.text = "Sabbia bianca, acqua verde e limpida, tu, io e buon vino – Charles, è così romantico! Dovremmo passeggiare così più spesso, va bene?";
			link.l1 = "Mi fa piacere che ti piaccia. Credo dovremmo ritagliarci più tempo per queste cose, ora.";
			link.l1.go = "LongHappy_1";
		break;
		
		case "LongHappy_1":
			dialog.text = "Charles, che stai combinando e perché sei in ginocchio? Così all’improvviso...";
			link.l1 = "Hélène, ti amo. E desidero vivere con te ogni giorno che mi sarà concesso dal cielo. Perciò, qui e ora, davanti a questo mare e questo cielo, ti chiedo – Helen Beatrice Sharp – di concedermi l’onore di stare al mio fianco, davanti agli uomini e a Dio, finché morte non ci separi. Io, Charles de Maure, Chevalier de Monper, ti domando – vuoi sposarmi?";
			link.l1.go = "LongHappy_2";
		break;
		
		case "LongHappy_2":
			if (pchar.location == "Shore_ship1")
			{
				dialog.text = "Sai, non ho mai sopportato queste formalità, ma ti seguirò fino alla fine del mondo. E riguardo alla tua domanda, la risposta è... oh, perdona, ho rovesciato tutto!";
				link.l1 = "Lascia stare, è solo vino e non ho mai amato questa camicia...";
				link.l1.go = "LongHappy_3";
			}
			else
			{
				dialog.text = "Charles, certo che sì! Sì, sì, e ancora sì!!! Ma spero proprio che tu non abbia in mente di rinchiuderci in qualche castello di famiglia pieno di polvere a coltivar rape fino alla fine dei nostri giorni?";
				link.l1 = "Ebbene sì, abbiamo un castello di famiglia, ma non è impolverato e non ci resteremo. La nostra vita è il vento in faccia e l’orizzonte sempre a portata di mano!";
				link.l1.go = "LongHappy_4";
			}
		break;
		
		case "LongHappy_3":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			DoQuestCheckDelay("Helena_LoveSex", 1.0);
			npchar.dialog.currentnode = "LongHappy_5";
			LAi_SetStayType(npchar);
		break;
		
		case "LongHappy_4":
			dialog.text = "Allora un brindisi a te, mio capitano, mio sposo, e alle nostre nozze!";
			link.l1 = "A te, amore mio! E al nostro avvenire insieme, ché il destino ci riserva ancora mille venti!";
			link.l1.go = "LongHappy_6";
		break;
		
		case "LongHappy_5":
			dialog.text = "Allora un brindisi a te, mio capitano, mio sposo, e alle mie nozze!";
			link.l1 = "A te, mio amore! E al nostro futuro assieme, ché il destino ci riserva ancora mille avventure!";
			link.l1.go = "LongHappy_6";
		break;
		
		case "LongHappy_6":
			DialogExit();
			chrDisableReloadToLocation = false;
			npchar.dialog.currentnode = "Helena_officer";
			LongHappy_MarryToSenPierre();
		break;
		
		case "LongHappy_7":
			dialog.text = "Dunque, l'abate Benoit è tornato ed è pronto a sposarci. Ma sappi, non indosserò un vestito nemmeno per un'occasione simile! Pensi che il mio portare i calzoni farà scalpore?";
			link.l1 = "Hélène, ti amo in qualsiasi abito, e quelli se ne faranno una ragione. Prima però volevo chiederti un parere sugli invitati e sulla cerimonia.";
			link.l1.go = "LongHappy_8";
		break;
		
		case "LongHappy_8":
			dialog.text = "Già, c’è un problema – la maggior parte dei nostri veri amici, quelli con cui vorremmo davvero condividere questo giorno, non metteranno mai piede in città, per non dire in chiesa. Perciò… sposiamoci qui, come si conviene, tra la gente giusta, e poi salpiamo per Isla Tessoro e festeggiamo davvero con chi conta per noi, che ne dici?";
			link.l1 = "Mi sembra un'ottima idea! Parlerò con l’Abate Benoit, ma dobbiamo mandare gli inviti e tutto il resto...";
			link.l1.go = "LongHappy_9";
		break;
		
		case "LongHappy_9":
			dialog.text = "Calmati, capitano. La tua adorata futura sposa ti alleggerirà un po’ il peso! Sistemerò tutto a Isla Tesoro e scriverò ai nostri amici, ma dimmi solo: quanto grande vuoi questo matrimonio?";
			link.l1 = "Solo noi due, e i nostri più fidati compagni. Dopo tutta questa buffonata ufficiale qui a Martinica, avremo voglia di un po’ di vera intimità.";
			link.l1.go = "LongHappy_10";
			link.l2 = "Tutti dovranno ricordare questo giorno! Radunate tutti! Nessuno resti fuori!";
			link.l2.go = "LongHappy_11";
		break;
		
		case "LongHappy_10":
			pchar.questTemp.LongHappy.SmallMarry = "true";
			dialog.text = "Accogliente e amichevole – mi leggi nel pensiero! Dovremo fare tappa a Sharptown e organizzerò tutto. Credo che cinquanta barili di rum e due dozzine di barili di vino basteranno. Poi, per il cibo e i passatempi, ci serviranno trecentomila pezzi da otto.";
			link.l1 = "Ricordamelo - perché non ti occupi tu dei conti di bordo, ancora? Ci penso io. Solo una sveltina dall’abate e poi si salpa per Sharptown.";
			link.l1.go = "LongHappy_12";
		break;
		
		case "LongHappy_11":
			pchar.questTemp.LongHappy.BigMarry = "true";
			dialog.text = "Allora, vuoi fare baldoria come veri lupi di mare? Va bene! Dovremo passare per Sharptown e penserò io a tutto. Bisognerà far scorte come si deve – direi che cento botti di rum e cinquanta di vino dovrebbero bastare. E per il resto delle spese, ci vorranno almeno cinquecentomila pezzi da otto.";
			link.l1 = "Stai forse invitando tutta la Fratellanza della Costa? Ah, che diavolo, facciamolo! Mi procuro le provviste. Una visita rapida all’abate e salpiamo per Sharptown.";
			link.l1.go = "LongHappy_12";
		break;
		
		case "LongHappy_12":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "10");
			AddQuestUserData("LongHappy", "sName", "Helen");
			LongHappy_MarryGoToBenua();
		break;
		
		case "LongHappy_13":
			dialog.text = "Charles, mi occupo io del carico, poi passo gli inviti al barone e sistemo le faccende con l’oste. Non ci metterò molto.";
			link.l1 = "Non temere, mia cara, mi troverò un lavoro redditizio... Oppure schiaccerò un pisolino sulla sabbia. Non avrei mai pensato che assaltare Tortuga fosse più semplice che organizzare il mio stesso matrimonio, per l’amor di Dio.";
			link.l1.go = "LongHappy_14";
		break;
		
		case "LongHappy_14":
			DialogExit();
			SetLaunchFrameFormParam("Several hours have passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 4, 0);
			LongHappy_IslaTesoroRemoveGoods();
			npchar.dialog.currentnode = "LongHappy_15";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "LongHappy_15":
			dialog.text = "Ti sei riposato un po’, Charles? Ho buone e cattive notizie. Quelle cattive sono che i locali si sono divertiti così tanto la scorsa settimana che, per sbaglio, hanno mandato in fumo la maledetta taverna ‘Vecchio Picchio’! Ma senti questa: il barone ha promesso di ricostruirla più grande e più bella di prima, per quando torneremo. Ho già sistemato tutto, quindi possiamo mollare gli ormeggi.";
			link.l1 = "Spero che il nostro matrimonio non lasci una simile montagna di cenere in città quando ce ne andremo. Peccato davvero, mi piaceva quel ‘Vecchio Picchio’—accogliente, intimo, con solo un leggero sentor di vomito e stoppa! Ma sì, tesoro, hai ragione—meglio darcela a gambe.";
			link.l1.go = "LongHappy_16";
		break;
		
		case "LongHappy_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "12");
			pchar.questTemp.LongHappy = "marry_wait";
			pchar.questTemp.LongHappy.DrinkReady = "true";
		break;
		
		case "LongHappy_17":
			dialog.text = "Jan è già in città con Gladys, puoi crederci? Non avrei mai pensato che sarebbero venuti davvero al mio matrimonio! Oh Santo Cielo! Persino quando eravamo in quella maledetta città di templi indiani non ero così spaventata come lo sono ora!";
			link.l1 = "Tutto va bene, tesoro, tutto va bene. Anch'io sono in pensiero—i nervi sono cosa normale. Visto che gli ospiti sono già arrivati, dovrei andare da padre Benoit e scoprire quando inizierà la funzione.";
			link.l1.go = "LongHappy_18";
		break;
		
		case "LongHappy_18":
			dialog.text = "Sarà una giornata maledettamente lunga e difficile... Vado a trovare Jan e Gladys.";
			link.l1 = "Sono felice che siano riusciti a venire. Il vecchio Svensson ti vuole bene come a una figlia sua, e la signora McArthur ancor di più. È una fortuna averli qui oggi. Vai pure, non ti crucciare – andrà tutto per il meglio.";
			link.l1.go = "LongHappy_19";
		break;
		
		case "LongHappy_19":
			DialogExit();
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0);
			AddQuestRecord("LongHappy", "14");
			AddQuestUserData("LongHappy", "sName", "Helen");
		break;
		
		case "LongHappy_20":
			dialog.text = "Sì.";
			link.l1 = "";
			link.l1.go = "LongHappy_21";
		break;
		
		case "LongHappy_21":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_27";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_22":
			dialog.text = "Sì.";
			link.l1 = "";
			link.l1.go = "LongHappy_23";
		break;
		
		case "LongHappy_23":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_29";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_24":
			dialog.text = "Sì.";
			link.l1 = "";
			link.l1.go = "LongHappy_25";
		break;
		
		case "LongHappy_25":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_31";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_26":
			dialog.text = "";
			link.l1 = "Io, Charles Henry de Maure, chevalier de Monper, prendo te, Helen Beatrice Sharp, come mia sposa, per avere e per tenere, da oggi in avanti, nella buona e nella cattiva sorte, nella ricchezza e nella povertà, in salute e in malattia, finché morte non ci separi. Secondo la Santa Legge di Dio, alla presenza dell’Altissimo, pronuncio questo voto.";
			link.l1.go = "LongHappy_27";
		break;
		
		case "LongHappy_27":
			dialog.text = "Io, Helen Beatrice Sharp, prendo te, Charles Henry de Maure, come mio sposo, per amarti e onorarti da questo giorno in avanti, nella buona e nella cattiva sorte, nella ricchezza e nella povertà, in salute e in malattia, finché morte non ci separi. Secondo la Santa Legge di Dio, alla presenza dell’Altissimo, ti do questa promessa.";
			link.l1 = "";
			link.l1.go = "LongHappy_28";
		break;
		
		case "LongHappy_28":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_33";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_29":
			dialog.text = "Amen.";
			link.l1 = "";
			link.l1.go = "LongHappy_30";
		break;
		
		case "LongHappy_30":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_35";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_31":
			dialog.text = "Hélène Béatrice de Maure, Madame de Monper - ah, come suona dolce, mio carissimo marito!";
			link.l1 = "Non ho mai sentito di meglio, mia moglie!";
			link.l1.go = "LongHappy_32";
		break;
		
		case "LongHappy_32":
			dialog.text = "Sai, pensavo che questo non avrebbe cambiato nulla, e forse è così – ti amavo già prima e desideravo passare il resto dei miei giorni con te, ma oggi, questa sacra cerimonia… Sono davvero felice, Charles! Felice come non mai, e guarda Gladys e Jan – brillano di gioia! Quante facce liete intorno a noi! A proposito – è ora che tu vada tra gli ospiti a ricevere i loro auguri. Torna quando avrai finito, non scordare – ci aspettano a Sharptown.";
			link.l1 = "Lo faccio subito, tesoro. Un bacio prima che salpi!";
			link.l1.go = "LongHappy_33";
		break;
		
		case "LongHappy_33":
			DialogExit();
			LongHappy_MarryKiss();
		break;
		
		case "LongHappy_34":
			dialog.text = "Ciao marito, hai già parlato con gli ospiti?";
			link.l1 = "Non ancora, abbi pazienza, moglie mia, torno presto.";
			link.l1.go = "LongHappy_34_1";
			link.l2 = "Sì, non mi era mai capitato di sentire così tanti complimenti tutti insieme. E sai che ti dico? Credo proprio che la maggior parte fosse sincera!";
			link.l2.go = "LongHappy_35";
		break;
		
		case "LongHappy_34_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_34";
		break;
		
		case "LongHappy_35":
			dialog.text = "Sì, questi nobili sono sorprendentemente sinceri – devo ammettere che mi aspettavo più menzogne e ipocrisia. O forse sono solo così felice che non noto nulla. Ma dopotutto, i nostri amici ci attendono a Sharptown! Quando salpiamo?";
			link.l1 = "Proprio adesso. Voleremo come aquile verso un banchetto tra amici. Spero che mia moglie non avrà nulla in contrario a passare questa notte nella nostra cabina?";
			link.l1.go = "LongHappy_36";
		break;
		
		case "LongHappy_36":
			dialog.text = "Oh sì, mio marito, quanto sei romantico! E non ti agitare così, ora ho il diritto di baciarti davanti a tutti... Eh, possiamo andare adesso!";
			link.l1 = "Navigatore, rotta su Sharptown e che nessuno osi disturbarci per nessun motivo! Non mi importa nemmeno se una flotta di fantasmi ci punta contro!";
			link.l1.go = "LongHappy_37";
		break;
		
		case "LongHappy_37":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_38";
			LongHappy_MarryComplete();
		break;
		
		case "LongHappy_38":
			dialog.text = "Oh mio caro marito, sono così felice! Oggi è una giornata meravigliosa...";
			link.l1 = "";
			link.l1.go = "LongHappy_38_1";
		break;
		
		case "LongHappy_38_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_38";
		break;
		
		case "LongHappy_39":
			dialog.text = "Andiamo, Charles. Questo bugiardo sarà già morto prima ancora di toccar terra!";
			link.l1 = "";
			link.l1.go = "LongHappy_40";
		break;
		
		case "LongHappy_40":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angerran") && CharacterIsAlive("Angerran")) // fix 02-04-20
			{
				sld = characterFromId("Angerran");
				sld.dialog.currentnode = "Shivo_6";
			}
			else 
			{
				sld = characterFromId("LH_Dussak");
				sld.dialog.currentnode = "Dussak_5";
			}
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "LongHappy_41":
			dialog.text = "Sto bene, Charles, non preoccuparti. Come sta Nathan?";
			link.l1 = "Così tanto sangue... Dannie, respira? Lo vedo che respira!";
			link.l1.go = "LongHappy_42";
		break;
		
		case "LongHappy_42":
			DialogExit();
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_9";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "LongHappy_43":
			dialog.text = "Più svelto, caro, non perdere tempo!";
			link.l1 = "";
			link.l1.go = "LongHappy_43_1";
		break;
		
		case "LongHappy_43_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_43";
		break;
		
		case "LongHappy_44":
			dialog.text = "Charles, stai bene? Che carneficina! Scusa, eravamo bloccati sopra, c’erano una dozzina di quei bastardi e ho dovuto sistemarli prima!";
			link.l1 = "Va tutto bene, me la sono cavata. Sono lieta d’aver chiuso quella faccenda con Jacques... finalmente. Ha avuto ciò che gli spettava.";
			link.l1.go = "LongHappy_45";
		break;
		
		case "LongHappy_45":
			dialog.text = "D’accordo, mio caro, finiamo qui e torniamo indietro. Non riesco a smettere di pensare a Nathan, come sta? Mi ha protetta da quella pallottola!";
			link.l1 = "Hai ragione, caro, anch’io mi preoccupo. Vai pure avanti, ti seguo a ruota.";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner")) link.l1.go = "LongHappy_46";
			else link.l1.go = "LongHappy_48";
		break;
		
		case "LongHappy_46":
			dialog.text = "Abbiamo trovato Marcus! Era nella stiva, legato e privo di sensi.";
			link.l1 = "È vivo?";
			link.l1.go = "LongHappy_47";
		break;
		
		case "LongHappy_47":
			dialog.text = "Non temere, amore, il Barone Tyrex camperà più di noi altri. S’è appena svegliato e già scalpita, chiama a gran voce rum, la sciabola e il ponte – proprio in quest’ordine.";
			link.l1 = "Ecco il nostro vecchio Marcus! Lasciamolo riposare un po' mentre finiamo qui, poi torniamo a riva.";
			link.l1.go = "LongHappy_48";
		break;
		
		case "LongHappy_48":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LongHappy_BarbExit", -1);
		break;
		
		case "LongHappy_49":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") && CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "Mi dispiace tanto, caro... Prima il nostro fedele amico Tichingitu, ora Gino... Barbazon avrebbe dovuto essere impiccato dozzine di volte per tutte le sue malefatte!";
				link.l1 = "Ahimè, l’ho fatto solo una volta. Mi sento in colpa anch’io… Ma abbiamo vinto, e lui non farà mai più del male a nessuno.";
				link.l1.go = "LongHappy_50";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
				{
					dialog.text = "Mi sento così male per Gino, Charles! Quando l’ho saputo, non ci volevo credere! Come stai, amore mio?";
					link.l1 = "Neanch’io riesco a crederci... che fine amara... mai avrei pensato che la giornata avrebbe preso questa piega.";
				}
				else
				{
					dialog.text = "Mi chiedo se i futuri cronisti narreranno della grande battaglia della Baia dei Corsari? Il giorno in cui i baroni della Fratellanza della Costa si sfidarono a viso aperto – scommetto che la Guardia di Costa spagnola si asciuga ancora le lacrime dalla gioia! Ma abbiamo vinto ancora! Gli amici son salvi, i nemici all’inferno – che magnifico dono di nozze!";
					link.l1 = "Sì, che baldoria, ma ce l’abbiamo fatta, mio angelo. Siamo arrivati.";
				}
				link.l1.go = "LongHappy_50";
			}
		break;
		
		case "LongHappy_50":
			dialog.text = "Andiamo, Dannie ci ha trovato una casa qui, fuori città; non ho alcuna voglia di tornare a bordo finché la nave non sarà rimessa a nuovo. Siediamoci e beviamo a chi non ce l'ha fatta.";
			link.l1 = "Sì, Helen, andiamo.";
			link.l1.go = "LongHappy_51";
		break;
		
		case "LongHappy_51":
			DialogExit();
			LongHappy_LogBook();
			DoQuestCheckDelay("LongHappy_MarryFinalizing", 0.5);
		break;
		
		case "LongHappy_52":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "Mi dispiace tanto per Gino, Charles! Quando l'ho saputo, non ci volevo credere! Come stai?";
				link.l1 = "Neanch'io riesco a crederci... che fine amara... Non avrei mai pensato che la giornata sarebbe finita così.";
			}
			else
			{
				dialog.text = "Hai visto Hawk? Dannie mi ha lasciata uscire quando Gino ha detto 'il pericolo è passato'. Sono felice che sia tutto a posto. I nostri amici sono vivi, e i nostri nemici sono stati mandati all’inferno – un regalo di nozze degno di una leggenda!";
				link.l1 = "Anch’io, amore mio. E abbiamo vinto. Barbazon è all’inferno, i baroni stanno radunando ciò che resta dei loro equipaggi. La battaglia è finita.";
			}
			link.l1.go = "LongHappy_53";
		break;
		
		case "LongHappy_53":
			dialog.text = "Charles, ti vedo a malapena in piedi, ma sono passata dalla taverna e non crederesti mai a cosa ho sentito dal locandiere.";
			link.l1 = "Aye, l'ho sentito da Jan, c'è stato anche lui. Mi pare che il nostro caro indio abbia preso la via della guerra. Andiamo a fare due passi verso la baia di Sabo-Matila, qualcuno l'ha visto andare da quella parte.";
			link.l1.go = "LongHappy_54";
		break;
		
		case "LongHappy_54":
			DialogExit();
			LongHappy_LogBook();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.longhappy_shoregirl.win_condition.l1 = "location";
			pchar.quest.longhappy_shoregirl.win_condition.l1.location = "Shore_ship1";
			pchar.quest.longhappy_shoregirl.function = "LongHappy_SetShoreGirl";
		break;
		
		case "LongHappy_55":
			dialog.text = "Dio in cielo! Questo sì che è spirito, Tichingitu! Ahah, mi sto sganasciando dalle risate! Perché noi europei non adottiamo anche noi una simile usanza?! Oh Charles, stai quasi dormendo in piedi! Su, Dannie ci ha trovato una casa qui in periferia – hai proprio bisogno di riposarti.";
			link.l1 = "Avanti ... credo di essermi già addormentata su quella spiaggia una volta.";
			link.l1.go = "LongHappy_56";
		break;
		
		case "LongHappy_56":
			DialogExit();
			DoQuestCheckDelay("LongHappy_MarryFinalizing", 0.5);
		break;
		
		case "tonzag_jailed":
			dialog.text = "... Va bene.";
			link.l1 = "Bene a sapersi.";
			link.l1.go = "exit";
			link.l2 = "Davvero?";
			link.l2.go = "tonzag_jailed_1";
			locCameraFromToPos(-15.50, 2.28, -1.23, true, -27.00, -10.60, -22.70);
		break;
		
		case "tonzag_jailed_1":
			dialog.text = "Sì.";
			link.l1 = "Bene a sapersi.";
			link.l1.go = "exit";
			link.l2 = "Andiamo, vedo che qualcosa ti rode dentro!";
			link.l2.go = "tonzag_jailed_2";
		break;
		
		case "tonzag_jailed_2":
			dialog.text = "Sto benissimo, lasciami stare! \nCharles, vai al diavolo! Odio le prigioni, odio te e odio quest’isola maledetta! Portami via subito!\nScusami... proprio non sopporto le celle, non toccarmi!";
			link.l1 = "Perdonami. Tutti temiamo qualcosa.";
			link.l1.go = "exit";
		break;
		
		case "tonzag_aftershot":
			dialog.text = "AAAA! Lasciaci uscire di qui! Charles, fai qualcosa!";
			link.l1 = "Rimettiti in sesto!";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Helena_officer";
			AddDialogExitQuestFunction("Tonzag_TichingituAfterShot");
		break;
		
		case "tonzag_after_boarding":
			dialog.text = "Mio Capitano, il nemico ha sfondato lo scafo al secondo ponte e ha messo piede a bordo. Si combatte in ogni angolo della nave, e quasi tutti i cannonieri sono messi fuori gioco! Dobbiamo salvare l’equipaggio e Hercule! Vuoi andare tu, o devo farlo io?";
			link.l1 = "Questa volta ci vado io, Helen! Prendi il comando della nave e portaci via di qui!";
			link.l1.go = "tonzag_after_boarding_1";
			DelLandQuestMark(npchar);
		break;
		
		case "tonzag_after_boarding_1":
			dialog.text = "Aye aye, mio Capitano. Non ti deluderò, ma tu fa’ attenzione, ti prego!";
			link.l1 = "Lo so, Helene. E anche tu fa’ attenzione, mi raccomando!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_GoToGunDeck");
		break;
		
		case "tonzag_after_victory":
			dialog.text = "Vittoria, mio Capitano! Il gruppo d'assalto è stato spazzato via, il nemico ha preferito battere in ritirata verso sud. La nave tiene ancora il mare. Equipaggio sopravvissuto: "+GetCrewQuantity(pchar)+" gente. Rapporto completato!";
			link.l1 = "Grazie, Hélène, e cosa...";
			link.l1.go = "tonzag_after_victory_1";
		break;
		
		case "tonzag_after_victory_1":
			dialog.text = "Spogliati, vincitore, il tuo premio è far di me ciò che più ti aggrada!";
			link.l1 = "Ehm...";
			link.l1.go = "tonzag_after_victory_2";
			link.l2 = "Andiamo!";
			link.l2.go = "tonzag_after_victory_2";
		break;
		
		case "tonzag_after_victory_2":
			dialog.text = "Oh, ciao, Hercule. Scusami, ci hai colto proprio in un momento poco opportuno! Ma diavolo, che sollievo vederti vivo e imbrattato del sangue altrui – la tua condizione naturale, eh!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HelenBoardingDialog");
		break;
		
		case "tonzag_after_victory_3":
			dialog.text = "";
			link.l1 = "Eh già, Helene, tu sei proprio un portento!";
			link.l1.go = "tonzag_after_victory_4";
		break;
		
		case "tonzag_after_victory_4":
			dialog.text = "Non ho nemmeno cominciato, mio Capitano. Festeggiamo?";
			link.l1 = "Non c’è bisogno di persuadermi!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ShowFrame");
		break;
		
		case "tonzag_dead":
			dialog.text = "Non guardare, non guardare, non guardare... Questo è un altro mondo, mio Capitano! Non può essere così!";
			link.l1 = "Penso che ormai questo sia il nostro mondo, tesoro. E hai ragione, non indugiamo oltre...";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Helena_officer";
		break;
		
		// Jason Исла Мона
		case "IslaMona":
			dialog.text = "Temo che questa pestilenza stia rovinando le tue ragazze, Rodrigo. Falle lavorare a maglia o trova loro qualcosa da fare!";
			link.l1 = "Questa conversazione non porta proprio a nulla. Abbiamo già deciso che domani andremo in chiesa. A pregare... naturalmente.";
			link.l1.go = "IslaMona_1";
		break;
		
		case "IslaMona_1":
			DialogExit();
			LAi_SetOfficerType(npchar);
			npchar.dialog.currentnode = "Helena_officer";
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_26";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_2":
			dialog.text = "Sono fiera di te, amore mio!";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
		break;
		
		case "IslaMona_3":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			sld = characterFromId("Himenes_companion_1");
			sld.dialog.currentnode = "island_man_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_4":
			dialog.text = "Ebbene, Charles...";
			link.l1 = "Cosa ti frulla per la testa stavolta, Helen?";
			link.l1.go = "IslaMona_5";
		break;
		
		case "IslaMona_5":
			dialog.text = "Il fatto che la coppia più chiacchierata dei Caraibi possieda due intere isole! Il mio rifugio di pirati, Isla Tesora, e la tua terra promessa... Quanto pensi che resisteranno, quando la civiltà finirà per approdare nelle Indie Occidentali?";
			link.l1 = "Quanto basta per tutta la nostra vita, tesoro. E dopo? Quello che sarà non dipende da noi. Altri racconteranno la nostra storia. L’importante è che tu ed io siamo qui, adesso, insieme e felici.";
			link.l1.go = "IslaMona_6";
		break;
		
		case "IslaMona_6":
			dialog.text = "A proposito di felicità... Sto per salire di sopra ora: devo accendere le candele, rifare il letto, magari scrivere qualche riga nel mio diario...";
			link.l1 = "Rimarrò qui ancora un po', poi salirò a darti una mano a 'sistemare la cuccetta'.";
			link.l1.go = "IslaMona_7";
		break;
		
		case "IslaMona_7":
			dialog.text = "Non metterci troppo, eh...";
			link.l1 = "";
			link.l1.go = "IslaMona_8";
		break;
		
		case "IslaMona_8":
			DialogExit();
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			DoQuestFunctionDelay("IslaMona_ChurchReloadToRoom", 0.5);
			ChangeCharacterAddressGroup(npchar, "IslaMona_TwoFloorRoom", "goto", "goto4");
			DoQuestCheckDelay("Helena_LoveSex", 2.5);
			NextDiag.CurrentNode = "sex_after";
			pchar.questTemp.IslaMona.Doorlock = "true";
		break;
		
		case "drinking_refuse":
			dialog.text = "Sei davvero così occupato? Peccato, ma capisco. Troverò altro con cui tenermi impegnata.";
			link.l1 = "";
			link.l1.go = "exit";
			NextDiag.TempNode = "Helena_wait";
			
			pchar.questTemp.HelenDrinking.Result = "no_visit";
			CloseQuestHeader("HelenDrinking");
		break;
		
		case "drinking_accept":
			dialog.text = "Che bello che tu te ne ricordi. Volevo dirti che ti sono davvero grata. Non capita spesso che qualcuno ti salvi da... beh, sai cosa. Vieni, beviamo qualcosa. Offro io.";
			link.l1 = "Hélène...  Che ne dirà Gladys?";
			link.l1.go = "drinking_accept_1";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToHouse");
		break;
		
		case "drinking_accept_1":
			dialog.text = "Spiritoso, Charles. Su, non seccarmi.";
			link.l1 = "È forse un appuntamento?";
			link.l1.go = "drinking_accept_1_1";
			link.l2 = "Arrivo, non c’è bisogno d’andarci giù duro.";
			link.l2.go = "drinking_accept_1_2";
		break;
		
		case "drinking_accept_1_1":
			dialog.text = "Ah-ah! Lo vorresti tu! Dovrei essere ubriaca fradicia per quello!";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "drinking_accept_1_2":
			dialog.text = "Così va meglio.";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "drinking_in_tavern":
			dialog.text = "";
			link.l1 = "... aveva molte virtù, ma il rum la buttava sempre giù. Così ci siamo conosciuti.";
			link.l1.go = "drinking_in_tavern_1";
			link.l2 = "... mio padre pretendeva ch’io servissi nell’esercito. Mi arresi e partii per Parigi con una lettera di raccomandazione. Ma non arrivai mai all’indirizzo indicato e divenni un pittore.";
			link.l2.go = "drinking_in_tavern_2";
		break;
				
		case "drinking_in_tavern_1":
			dialog.text = "Ah, ora comprendo di quali virtù parli. Come si chiamava?";
			link.l1 = "Lulù.";
			link.l1.go = "drinking_in_tavern_1_1";
		break;
		
		case "drinking_in_tavern_1_1":
			dialog.text = "Lulu... Con queste storie, mi hai proprio rovinato Parigi. Credevo fosse una città di gran vita, ma ora sembra solo un gran bordello elegante.";
			link.l1 = "Disprezzi i postriboli?";
			link.l1.go = "drinking_in_tavern_1_2";
		break;
		
		case "drinking_in_tavern_1_2":
			dialog.text = "Sì, Capitano, e non capisco certo gli uomini che ci vanno.";
			link.l1 = "( fissare la tazza )";
			link.l1.go = "drinking_in_tavern_1_4";
			link.l2 = "(ha una tosse terribile)";
			link.l2.go = "drinking_in_tavern_1_4";
			link.l3 = "Ehm... ognuno ha i suoi gusti... suppongo?";
			link.l3.go = "drinking_in_tavern_1_4";
		break;
		
		case "drinking_in_tavern_1_4":
			dialog.text = "(ride) Ah! Dovevi vedere la tua faccia! Impaurito? Versiamone un altro! A Parigi!";
			link.l1 = "A Parigi!";
			link.l1.go = "drinking_in_tavern_3";
		break;
		
		case "drinking_in_tavern_2":
			dialog.text = "(ride) T-tu?! Un artista? Quindi, la gloria e l’orgoglio della flotta inglese, un porco stupratore e gran figlio di puttana come Donovan, è crepato per mano d’un artista parigino? Ah, peccato solo che tu non abbia indossato il tuo candido jabot durante l’abbordaggio né preso a bastonate quella carogna!";
			link.l1 = "Già, proprio una sfortuna. Quel giorno il jabot era finito a lavare, guarda caso.";
			link.l1.go = "drinking_in_tavern_2_1";
		break;
		
		case "drinking_in_tavern_2_1":
			dialog.text = "(ride) Beh, grazie, Charles. Non so come finirà questa notte, ma la serata è già stata magnifica. Potrei perfino lasciarti dipingere il mio ritratto. Ma bada, non con lo stesso stile che usavi per le tue parigine!";
			link.l1 = "Ah! Questo solo se decido di ritrarti, sai.";
			link.l1.go = "drinking_in_tavern_3";
		break;
		
		case "drinking_in_tavern_3":
			dialog.text = "Perdonami, mio Capitano, ascoltando le tue avventure e la vita nobile... e i cortigiani d'ogni sorta. Per mille squali, non mi farai mai credere che non trovassi niente di più degno per occupare il tuo tempo! Non provare nemmeno a dirmi che passavi le giornate a sporcare tele e sperperare i soldi di papà. Se fosse stato così, con noi non avresti retto nemmeno un giorno.";
			link.l1 = "Avevo... altri interessi.";
			link.l1.go = "drinking_in_tavern_" + pchar.HeroParam.HeroType;
		break;
		
		case "drinking_in_tavern_herotype_3":
			dialog.text = "";
			link.l1 = "Ho unito la vita di corte al servizio militare, ma non... eheh, non proprio come avrebbe voluto mio padre, ovviamente. Qualche fuga dalla finestra, una rissa o due – ed eccomi amico delle guardie. Naturalmente ho imparato un sacco di cose, temprato il fisico. I compagni più anziani mi hanno insegnato a incassare, portare armatura, menar di spada e, soprattutto, a godersi la vita. Quest’ultimo mi veniva particolarmente bene, va detto. Non ci crederai, ma non tutti sanno menar la lama dall’alba a mezzodì e poi tracannare dal mezzodì all’alba seguente.";
			link.l1.go = "drinking_in_tavern_4";
		break;
		
		case "drinking_in_tavern_herotype_1":
			dialog.text = "";
			link.l1 = "Pensi che fosse facile per un nobilotto con la fama rovinata e le tasche vuote, perdere la lettera di raccomandazione di papà già il primo giorno nella capitale? Dovevo farmi valere, non lasciare che mi prendessero in giro. Le lezioni di scherma in casa non le avevo dimenticate, e a ogni sguardo storto rispondevo con una sfida. Poi ci ho preso gusto, sai? Ma non ho mai ucciso nessuno, e sono riuscito a lasciare Parigi prima d’incrociare uno spadaccino vero che mi avrebbe mandato al creatore.";
			link.l1.go = "drinking_in_tavern_4";
		break;
		
		case "drinking_in_tavern_herotype_4":
			dialog.text = "";
			link.l1 = "Ho passato un sacco di tempo nei cimiteri. Non pensare male, era solo un passatempo in voga tra la mia gente. Per farci coraggio, ci infilavamo al cimitero di notte, mettevamo bottiglie vuote sulle inferriate e sparavamo a tempo. In una sola notte sprecavamo cento cartucce e una cassa di champagne. Ora, certo, mi vergogno di queste sciocchezze, ma allora il vincitore si portava a casa un bel bottino... e qualche favore dalle dame di corte. Usavamo di tutto, ho persino pasticciato un po’ con miscele di polvere da sparo. Ma come mai a nessuno di noi venne in mente di imparare a fare cartucce di carta, resta un mistero.";
			link.l1.go = "drinking_in_tavern_4";
		break;
		
		case "drinking_in_tavern_herotype_2":
			dialog.text = "";
			link.l1 = "Ho studiato, e con gran zelo – quasi sono finita alla Sorbona. Ho lavorato in un ufficio finché la noia non m’ha cacciata, e in generale – ho provato un po’ di tutto. Il mio maestro, vecchio compagno di mio padre, preferiva la pratica alla teoria, così ho visto Parigi da ogni cantonata e parlato con chiunque: dalla feccia ai gran signori. E sai che ti dico? Tutto ciò qui mi torna utile.";
			link.l1.go = "drinking_in_tavern_4";
		break;
		
		case "drinking_in_tavern_4":
			dialog.text = "E... tutto qui? Dunque, c'è ancora qualcosa in te, mio capitano. Qualcosa che tu stesso non hai ancora scoperto. Alla tua!";
			link.l1 = "Un buon brindisi!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_TavernChange");
		break;
		
		case "drinking_my_background":
			dialog.text = "";
			link.l1 = "Raccontami la tua storia, Helen. Le mie avventure nella Capitale impallidiscono davanti a una fanciulla di meno di trent’anni che comanda una goletta con cento uomini a bordo.";
			link.l1.go = "drinking_my_background_1";
		break;
		
		case "drinking_my_background_1":
			dialog.text = "Non hai ancora trent’anni, eh, Charles? Per una battuta così, dovrai offrire il prossimo giro! Tutti i miei uomini sono morti, e non sono più al comando di uno schooner. Francamente, non so nemmeno se tornerò mai a comandarne uno.";
			link.l1 = "Mi dispiace, Hélène. Non volevo ferirti. Ma perché pensi che la tua carriera da capitano sia finita?";
			link.l1.go = "drinking_my_background_2";
		break;
		
		case "drinking_my_background_2":
			dialog.text = "Because my crew is dead, and a different one won't ever accept me. Eh! Fine, my captain, you've told me a lot about your life; now it's my turn! The truth is not at the bottom of this mug, so let's dispense with the mystery.";
			link.l1 = "";
			link.l1.go = "drinking_my_background_3";
		break;
		
		case "drinking_my_background_3":
			dialog.text = "La mia storia, Charles, è singolare. Mio padre fu uno dei migliori lupi di mare da queste parti, il Diavolo della Foresta lo stimava assai, l’equipaggio lo adorava, e lui mi voleva più bene che alla sua stessa vita.";
			link.l1 = "";
			link.l1.go = "drinking_my_background_4";
		break;
		
		case "drinking_my_background_4":
			dialog.text = "Togli anche solo una di queste cose, e mi avrebbe spedita a Londra, a vivere nella... civiltà, oppure mi avrebbe lasciata a marcire qui come mia madre. All’inizio sembrava tutto perfetto: desideravo la libertà, quella vera, Charles, e il comando abile di una nave da guerra con un equipaggio fedele ti regala proprio questo. Mio padre mi ha dato tutto quel che poteva. Sono salpata con lui a dodici anni, i primi sei mesi li ho passati a cacciare topi nella stiva, e solo dopo mi permise di lavorare insieme ai marinai.";
			link.l1 = "Sean MacArthur ti ha fatto diventare un topo di stiva? Mi dispiace, Helene, ma da lì non si risale! E l'equipaggio come ti ha accolta?";
			link.l1.go = "drinking_my_background_5";
		break;
		
		case "drinking_my_background_5":
			dialog.text = "Well, perhaps I'm exaggerating a bit for the sake of a good story? My father's crew accepted me; he gathered fine people. But since then, I've been afraid... of holds and any small dark spaces in general. Ha! Svensson almost killed my father when he found out!";
			link.l1 = "È importante per te. Ha avuto un ruolo nel tuo destino, né meno di Sean.";
			link.l1.go = "drinking_my_background_6";
		break;
		
		case "drinking_my_background_6":
			dialog.text = "Sì. Tutti i baroni dissero direttamente a mio padre che era uno sciocco, ma fu il Diavolo della Foresta a dargli il suo benestare e a stringergli la mano dopo che avevo battuto il record dell’equipaggio scalando l’albero maestro. Quel momento non lo dimenticherò mai: le urla trionfanti dell’equipaggio e, ovunque guardassi, solo il mare pulito all’orizzonte. E lo sguardo compiaciuto di mio padre… non potevo vederlo, ma lo sentivo con tutto il cuore.";
			link.l1 = "La mia gloria finì quando caddi dagli alberi il primo giorno, mentre si andava verso Guadalupa.";
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.TakeFolke")) {
				link.l1 = link.l1+" Anche il mio timoniere, Deluc, aveva uno sguardo molto eloquente."}
			link.l1.go ="Bere mi aiuta a dimenticare per un po’ chi sono e da где vengo, mon capitaine.";
		break;
		
		case "drinking_my_background_7":
			dialog.text = "Ah-ha-ha! I can imagine! Don't worry, that was a long time ago; now you're a real sea wolf!";
			link.l1 = "";
			link.l1.go = "drinking_my_background_8";
		break;
		
		case "drinking_my_background_8":
			dialog.text = "Alle nostre vittorie!";
			link.l1 = "Ascoltate, ascoltate!";
			link.l1.go = "drinking_my_background_12";
		break;
		
		case "drinking_my_background_12":
			dialog.text = "... And then I gradually rose through the ranks, served at the captain's table in councils with my father and officers. Learned a lot. From the age of fifteen, they started taking me on military campaigns, and I killed a man in my very first battle. It was a disgusting campaign; we shouldn't have set sail on a Monday... Really shouldn't have!";
			link.l1 = "A quindici anni? Mi fai paura, Helen.";
			link.l1.go = "drinking_my_background_13";
		break;
		
		case "drinking_my_background_12":
			dialog.text = "Non ho nemmeno capito cosa sia successo. Quel mercante olandese aveva la sua avanguardia – mercenari della Compagnia. Hanno voluto giocare d’azzardo e ci hanno assalito la tolda di poppa. E io, sciocca, senza alcun timore per la mia pellaccia, ho cacciato fuori la mia testa bionda. Subito mi sono beccata una botta col calcio di una pistola. Ma un attimo prima sono riuscita a piantare il mio fioretto in qualche scellerato della Compagnia.";
			link.l1 = "Santo cielo, e Sean? Come mai non ti ha sbattuto fuori bordo dopo quella?";
			link.l1.go = "drinking_my_background_13";
		break;
		
		case "drinking_my_background_13":
			dialog.text = "Mio padre non uscì indenne da quella battaglia, e vedere la mia testa rotta non gli fece certo bene. Cominciò a spegnersi piano piano, e credo che solo io me ne sia accorta. Poi se ne andò. Nel testamento, mi lasciò la Rainbow con tutto l’equipaggio e denaro a sufficienza per tenerla a galla un anno.";
			link.l1 = "E l’equipaggio ti ha riconosciuta come capitano?";
			link.l1.go = "drinking_my_background_14";
		break;
		
		case "drinking_my_background_14":
			dialog.text = "Non viviamo in una fiaba, mio capitano. Alcuni accolsero la volontà di mio padre con ostilità – le cose presero una brutta piega.\nSe anche solo un marinaio avesse abbandonato l’Arcobaleno, rifiutando di servire sotto il mio comando, la mia reputazione ne avrebbe risentito terribilmente. Ma Svensson intervenne e rimise tutti in riga. Nessuno lasciò l’equipaggio apertamente... allora. Per sette anni ho comandato la mia bellezza, trafficato merci poco raccomandabili per il Diavolo della Foresta, cercato tesori, vissuto... Ma ora, tutto ciò appartiene al passato.";
			link.l1 = "Non in passato. Son certa che il tuo destino sia di tornare a navigare sotto la tua bandiera! Beviamoci su!";
			link.l1.go = "drinking_my_background_sea";
			link.l2 = "Forse la nave è persa, ma la tua spada è ancora al tuo fianco.";
			link.l2.go = "drinking_my_background_land";
		break;
		
		case "drinking_my_background_sea":
			dialog.text = "Sai, detta così, ci credo anch’io. Beviamo!";
			link.l1 = "";
			link.l1.go = "drinking_my_background_15";
			
			AddCharacterSkill(npchar, SKILL_COMMERCE, 5);
			AddCharacterSkill(npchar, SKILL_ACCURACY, 5);
			AddCharacterSkill(npchar, SKILL_CANNONS, 5);
			AddCharacterSkill(npchar, SKILL_SAILING, 5);
			AddCharacterSkill(npchar, SKILL_REPAIR, 5);
			AddCharacterSkill(npchar, SKILL_GRAPPLING, 5);
			AddCharacterSkill(npchar, SKILL_DEFENCE, 5);
			notification("Naval Skills +", "Helena");
			
			pchar.questTemp.HelenDrinking.Background = "sea";
		break;
		
		case "drinking_my_background_land":
			dialog.text = "Ma la mia spada mi porterà davvero felicità? La risposta, forse, giace sul fondo di questa tazza. Beviamo!";
			link.l1 = "";
			link.l1.go = "drinking_my_background_15";
			
			AddCharacterSkill(npchar, SKILL_F_LIGHT, 5);
			AddCharacterSkill(npchar, SKILL_FENCING, 5);
			AddCharacterSkill(npchar, SKILL_F_HEAVY, 5);
			AddCharacterSkill(npchar, SKILL_PISTOL, 5);
			AddCharacterSkill(npchar, SKILL_FORTUNE, 5);
			AddCharacterSkill(npchar, SKILL_LEADERSHIP, 5);
			AddCharacterSkill(npchar, SKILL_SNEAK, 5);
			notification("Personal Skills +", "Helena");
			
			pchar.questTemp.HelenDrinking.Background = "land";
		break;
		
		case "drinking_my_background_15":
			dialog.text = "Ho pensato alla tua vita in Europa... Senti, tu sei un damerino di città, e io una ragazza qualunque, ma ormai ci siamo già fatti un nome nel più pericoloso angolo del mondo.";
			link.l1 = "Sembra un brindisi! Dunque, c’è qualcosa che ci accomuna?";
			link.l1.go = "drinking_my_background_16";
		break;
		
		case "drinking_my_background_16":
			dialog.text = "Ebbene, io cammino sulle orme di mio padre. Non so tu, ma forse anche la tua famiglia ha lasciato un segno su di te? Magari ancora non te ne sei accorto?";
			link.l1 = "Chiederò a mio caro fratello, appena lo tirerò fuori di galera.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_TavernEmpty");
		break;
		
		case "drinking_game":
			dialog.text = "Ebbene, è fatta, mio capitano. Ci siamo raccontati le nostre storie, è ora di chiudere la serata.";
			link.l1 = "Hmm, speravo che la serata finisse in tutt'altro modo.";
			link.l1.go = "drinking_game_1";
		break;
		
		case "drinking_game_1":
			dialog.text = "La notte non è ancora finita. Ti propongo un gioco: se giochi bene le tue carte, magari i tuoi desideri saranno esauditi.";
			link.l1 = "Giochiamo a carte? Ci sto!";
			link.l1.go = "drinking_game_2";
		break;
		
		case "drinking_game_2":
			dialog.text = "Calmati, lupo di mare. Non giocherò a strip poker con te.";
			link.l1 = "Sì, hai ragione, Helen. Qui non abbiamo un briciolo di privacy.";
			link.l1.go = "drinking_game_3";
		break;
		
		case "drinking_game_3":
			dialog.text = "Non è l’unica cosa che ci manca, Charles... Non è un gioco di carte, ma scommetto che te la cavi anche qui. 'Io mai' – mai sentito nominare?";
			link.l1 = "Familiare. Dalla vita passata. E tu, la suoni spesso?";
			link.l1.go = "drinking_game_4";
		break;
		
		case "drinking_game_4":
			dialog.text = "Avrei sempre voluto provarci, ma non avevo mai nessuno con cui giocare.";
			link.l1 = "Gioco audace, per il nostro primo bicchiere insieme. Sei proprio sicuro, capitano?";
			link.l1.go = "drinking_game_5";
			link.l2 = "A proposito, dove sono tutti? Siamo soli qui?";
			link.l2.go = "drinking_game_6";
		break;
		
		case "drinking_game_5":
			dialog.text = "Sì, dopo tutto quello che è successo, sento il bisogno di godermi un po’ la vita. Fare qualche sciocchezza, capisci?";
			link.l1 = "No, finisce sempre male, Rumba.";
			link.l1.go = "drinking_game_refuse";
			link.l2 = "Iniziamo! Le signore avanti!";
			link.l2.go = "drinking_game_accept";
		break;
		
		case "drinking_game_6":
			dialog.text = "Li ho mandati tutti via – non serve che forestieri ascoltino i fatti nostri.";
			link.l1 = "No, finisce sempre in malora, Rumba.";
			link.l1.go = "drinking_game_refuse";
			link.l2 = "Facciamolo! Le signore avanti!";
			link.l2.go = "drinking_game_accept";
		break;
		
		case "drinking_game_refuse":
			dialog.text = "Peccato, ma forse hai ragione. Allora beviamone un altro, eh?";
			link.l1 = "Iniziamo! Le signore per prime!";
			link.l1.go = "drinking_game_refuse_1";
		break;
		
		case "drinking_game_refuse_1":
			dialog.text = "Ho sistemato tutto – la stanza al piano di sopra è tua. Prima ci stava un qualche pezzo grosso francese, ma i ragazzi del Diavolo della Foresta gli hanno fatto capire che doveva sloggiare. Vai a riposare un po’, non ti lascio bighellonare per strada o, peggio ancora, uscire in mare conciato così.";
			link.l1 = "Sissignora!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToTavernRoom");
		break;
		
		case "drinking_game_accept":
			dialog.text = "Ah! Hic! Vuol dire che cominci tu!";
			link.l1 = "Attento, caro! Hmm. Non ho mai dato la caccia ai topi nella stiva!";
			link.l1.go = "drinking_game_accept_1";
		break;
		
		case "drinking_game_accept_1":
			dialog.text = "Ah, è così che stanno le cose? Devo stare all’erta con te! (Beve)";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_2";
		break;
		
		case "drinking_game_accept_2":
			dialog.text = "Brr! Solo il ricordo mi gela il sangue... Ma tieniti forte, bel capitano: io non sono mai caduta dall’alberatura!";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_3";
		break;
		
		case "drinking_game_accept_3":
			dialog.text = "";
			link.l1 = "Brava! Permettimi, mademoiselle, di brindare a te! (Beve)";
			link.l1.go = "drinking_game_accept_4";
		break;
		
		case "drinking_game_accept_4":
			dialog.text = "";
			link.l1 = "Non sono mai stata superstiziosa.";
			link.l1.go = "drinking_game_accept_5";
			
			LAi_Fade("", "");
			pchar.GenQuest.CamShuttle = 1;
			SetCamShuttle(loadedLocation);
			SetPitch(0.95);
		break;
		
		case "drinking_game_accept_5":
			dialog.text = "E ti chiami marinaio! Sai benissimo che razza di gente siamo noi. Mai sapere cosa ci porta il viaggio, né quando e dove vedrai terra, se mai la vedrai. Le risposte bisogna cercarle al di là di mappe e sestanti! Alla tua salute! (Beve)";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_6";
		break;
		
		case "drinking_game_accept_6":
			dialog.text = "E le ragazze che hai ritratto dal vivo... erano contente del risultato?";
			link.l1 = "Non sempre apprezzavano i miei quadri, ma... il risultato, quello sì.";
			link.l1.go = "drinking_game_accept_7";
		break;
		
		case "drinking_game_accept_7":
			dialog.text = "Charles! Se ci fossimo incontrati ai vecchi tempi, ti avrei sparato addosso o ti avrei preso in ostaggio per un bel riscatto. E comunque, non ho mai preso in mano un pennello.";
			link.l1 = "Ehi! Ma questo è davvero banale. Cara Hélène, se dovessi cominciare a elencare le cose a cui non ti sei mai dedicata...";
			link.l1.go = "drinking_game_accept_8";
		break;
		
		case "drinking_game_accept_8":
			dialog.text = "Bene, va bene, giocherò pulito. Tocca a te, mio capitano.";
			link.l1 = "(Sorseggia) Hic! Hmm... Mai successo che una delle mie modelle mi colpisse in testa con l'impugnatura di una pistola.";
			link.l1.go = "drinking_game_accept_9";
		break;
		
		case "drinking_game_accept_9":
			dialog.text = "(Sorseggia) Ugh. Stiamo giocando male, caro. Pensavo che avremmo bevuto e ci saremmo conosciuti meglio, invece ci lanciamo frecciatine e... e... Hip. Dannazione!";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_10";
			
			LAi_Fade("", "");
			pchar.GenQuest.CamShuttle = 2;
			SetCamShuttle(loadedLocation);
			SetPitch(0.90);
		break;
		
		case "drinking_game_accept_10":
			dialog.text = "Rendiamola più interessante! E, se possibile, qualcosa che non abbia nulla a che vedere con quella roba di cui parlavamo un’ora fa!";
			link.l1 = "Non mi era mai capitato di svegliarmi in un luogo sconosciuto dopo una sbronza.";
			link.l1.go = "drinking_game_accept_11";
		break;
		
		case "drinking_game_accept_10":
			dialog.text = "Ahi! Maledizione, Charles! (Beve)";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_11";
		break;
		
		case "drinking_game_accept_11":
			dialog.text = "Io... Hic... non ci posso credere. Lo ammetto, colpevole - la piccola Rumba finiva spesso in fondo. Ma in galera non ci sono mai stata!";
			link.l1 = "Come hai fatto...?";
			link.l1.go = "drinking_game_accept_12";
		break;
		
		case "drinking_game_accept_12":
			dialog.text = "Hahaha! Bevi, bevi!";
			link.l1 = "Me ne pentirò. (Beve)";
			
			if (IsCharacterEquippedArtefact(pchar, "totem_01")) {
				link.l1.go = "drinking_game_accept_13";
			} else {
				link.l1.go = "exit";
				AddDialogExitQuestFunction("HelenDrinking_LightsOut");
			}
		break;
		
		case "drinking_game_accept_13":
			dialog.text = "Andiamo, mio caro. L’ultima domanda e l’ultima occasione per mettermi nel sacco!";
			link.l1 = "No... Io... Usciamo a prendere un po' d'aria.";
			link.l1.go = "drinking_game_enough";
			link.l2 = "Ho bevuto spesso, ma mai così... Non mi sono mai ubriacata così con una donna. Ti giuro sulla mia parola, bere è davvero un gran peccato...";
			link.l2.go = "drinking_game_accept_14";
			
			LAi_Fade("", "");
			pchar.GenQuest.CamShuttle = 3;
			SetCamShuttle(loadedLocation);
			SetPitch(0.85);
		break;
		
		case "drinking_game_enough":
			dialog.text = "Eh!";
			link.l1 = "";
			link.l1.go = "drinking_game_refuse_1";
		break;
		
		case "drinking_game_accept_14":
			dialog.text = "";
			link.l1 = "A-aspetta... Non bevi?";
			link.l1.go = "drinking_game_accept_15";
		break;
		
		case "drinking_game_accept_15":
			dialog.text = "Ah-ah-ah! Che spasso! Miri in alto, mio capitano. Sia... hic!... noto a voi...";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_16";
		break;
		
		case "drinking_game_accept_16":
			dialog.text = "Che ho la sventura di vivere tra una ciurma tutta maschile, e devo sempre stare in guardia. Sono una fanciulla onesta.";
			link.l1 = "Sono... sono felice per te, H-Hélène.";
			link.l1.go = "drinking_game_accept_17";
		break;
		
		case "drinking_game_accept_17":
			dialog.text = "Sarai ancora più felice, perché ho vinto io! Ma, a dire il vero, non mi sono mai ubriacata così tanto con un uomo prima d’ora.";
			link.l1 = "(Senza dire nulla, beve) A-a te. Congratulazioni... h-hic...";
			link.l1.go = "drinking_game_accept_18";
		break;
		
		case "drinking_game_accept_18":
			dialog.text = "Ehi-ehi-ehi! Capitano, dove te ne vai? Forse ti sei offeso?";
			link.l1 = "H-ho bisogno... di una pausa? Vado solo a cercare la mia s-spada...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_ExitTavern");
		break;
		
		case "drinking_at_svenson":
			dialog.text = "Capo, sei pronto? Da qui non si torna indietro, e se qualcosa va storto ti costringerò a sposarmi.";
			link.l1 = "Uff! Fammi prendere almeno una boccata d’aria! Sei proprio sicura di questo, Helen?";
			link.l1.go = "drinking_at_svenson_1";
		break;
		
		case "drinking_at_svenson_1":
			dialog.text = "Sì, maledizione, e non startene lì impalato! Ho bisogno di perdermi, anche solo per una notte!";
			link.l1 = "Temo che dopo questa notte, sarò io a voler perdere la testa. Andiamo, prima che svegliamo tutta la città.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_EnterSvenson");
		break;
		
		case "drinking_give_key":
			dialog.text = "Cap, take the key and go upstairs. There should be a chest; you probably saw it when Svensson had it. Grab the barrel and head back immediately.";
			link.l1 = "Aspetta un attimo, tesoro, perché dovrei derubare il tuo capo?";
			link.l1.go = "drinking_give_key_1";
			
			GiveItem2Character(pchar, "key3");
			PlaySound("interface\important_item.wav");
		break;
		
		case "drinking_give_key_1":
			dialog.text = "Don't be silly. I've been here since childhood; if the owners return, I can handle it and cover for you. Come on, don't lower your sail now!";
			link.l1 = "Tagliente come una lama, una vera contrabbandiera! Aspetta un attimo, sarò rapida.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GotKey");
		break;
		
		case "drinking_got_whiskey":
			dialog.text = "Capito?";
			link.l1 = "Puoi scommetterci! Non è il primo forziere che svuoto, e di certo non sarà l’ultimo!";
			link.l1.go = "drinking_got_whiskey_1";
		break;
		
		case "drinking_got_whiskey_1":
			dialog.text = "Sono fiera di te! Ahah! Whiskey irlandese di prima scelta, 'Bushmills'! Una bevanda così non ce la verseranno certo in taverna.";
			link.l1 = "Sembra un buon piano, ma non credi che Svensson si accorga della sparizione?";
			link.l1.go = "drinking_got_whiskey_2";
		break;
		
		case "drinking_got_whiskey_2":
			dialog.text = "Se ne accorgerà di sicuro, ma lui non lo beve mai. Sembra che l’abbia messo da parte come dono per il suo compare pirata Dodson, e Dodson o s’è dileguato, o ha fatto fuori qualcuno...";
			link.l1 = "Che orrore! Un talento simile non può certo marcire nell’ombra. Prendi la botte e andiamo a cambiare aria!";
			link.l1.go = "drinking_got_whiskey_3";
		break;
		
		case "drinking_got_whiskey_3":
			dialog.text = "Ben detto, Capitano. Un'ultima cosa però – dimmi, hai preso qualcos’altro dal forziere? Rispondi senza menzogne.";
			if (HelenDrinking_RobbedSvenson()) {
				link.l1 = "Preso qualcosa, un vizio, sai com'è.";
				link.l1.go = "drinking_got_whiskey_notbelieve";
			}
			
			link.l2 = "No.   Non so se sia una pirata, ma non sono certo una ladra.";
			link.l2.go = "drinking_got_whiskey_believe";
			
			if (HelenDrinking_RobbedSvenson()) {
				link.l2.go = "drinking_got_whiskey_notbelieve";
				pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 2;
				notification("Helen disapproves", "Helena");
				pchar.questTemp.HelenDrinking.RobbedSvenson = true;
			}
		break;
		
		case "drinking_got_whiskey_believe":
			dialog.text = "In qualche modo ti credo... sciocca che sono!";
			link.l1 = "";
			link.l1.go = "drinking_get_out";
		break;
		
		case "drinking_got_whiskey_notbelieve":
			dialog.text = "Vai e assicurati di non aver preso nulla, per qualche strana ragione.";
			link.l1 = "";
			link.l1.go = "exit";
			if (!HelenDrinking_RobbedSvenson()) {
				AddDialogExitQuestFunction("HelenDrinking_JoanEnter");
				TakeItemFromCharacter(pchar, "cask_whisky");
				sld = ItemsFromID("cask_whisky");
				sld.price = sld.pricebak;
				DeleteAttribute(sld, "pricebak");
			}
			
			NextDiag.TempNode = "drinking_got_whiskey_notbelieve";
		break;
		
		case "drinking_get_out":
			DialogExit();
			
			AddDialogExitQuestFunction("HelenDrinking_JoanEnter");
			TakeItemFromCharacter(pchar, "cask_whisky");
			sld = ItemsFromID("cask_whisky");
			sld.price = sld.pricebak;
			DeleteAttribute(sld, "pricebak");
		break;
		
		case "drinking_at_fort":
			dialog.text = "Ehi, ehi, caro! Attento! Il mio viso, accarezzato dalla brezza marina, è proprio qui!";
			link.l1 = "Uff, beh, che abbigliamento il tuo! Avrai risparmiato un bel po' di soldi sulla stoffa. E io... hic! Di cose ne ho viste tante! Ma questa... questa è la più memorabile.";
			link.l1.go = "drinking_at_fort_1";
			locCameraFromToPos(-1.65, 44.45, 76.64, true, -5.93, 42.10, 70.13);
		break;
		
		case "drinking_at_fort_1":
			dialog.text = "Tutti lo dicono, ma chissà perché, a te ci credo! Ti piace davvero, o no?";
			link.l1 = "Beh, certo, mette in risalto le tue forme, benché...";
			link.l1.go = "drinking_at_fort_2";
		break;
		
		case "drinking_at_fort_2":
			dialog.text = "Oh, adesso hai mandato tutto a monte!";
			link.l1 = "... anche se non dubito che tra la gente comune, incuta un certo timore reverenziale!";
			link.l1.go = "drinking_at_fort_3";
		break;
		
		case "drinking_at_fort_3":
			dialog.text = "Mi stupisce davvero questa strana abitudine diffusa tra la gente — sia povera che ricca — di indossare pesanti vestiti europei sotto questo sole. I nostri villaggi sembrano ancora più buffi... A me piace il mio abito, Charles. Mi fa sentire bella, e questo, per una donna, conta.";
			link.l1 = "Saresti bella lo stesso anche senza quella tenuta, Helen.";
			link.l1.go = "drinking_at_fort_4";
		break;
		
		case "drinking_at_fort_4":
			dialog.text = "Attento, mio capitano! Con parole così dolci potresti pervertire il cuore d’una povera fanciulla!";
			link.l1 = "Se lei non ci mette il veto, non lo metterò certo io.";
			link.l1.go = "drinking_at_fort_5";
		break;
		
		case "drinking_at_fort_5":
			dialog.text = "Ehi ehi! Meglio chiedermi qualcos’altro. Mi fai sorridere quando diventi curioso.";
			link.l1 = "Allora lascia che ti faccia una domanda sul tuo abbigliamento. Non credo proprio che quei vecchi lupi di mare riescano a prendere sul serio un capitano vestito così.";
			link.l1.go = "drinking_at_fort_6";
		break;
		
		case "drinking_at_fort_6":
			dialog.text = "E non credo che quei cani di mare, in generale, riescano a vedere una donna come capitano, quindi forse il mio abbigliamento non ha fatto che peggiorare la situazione. O magari non ha nemmeno avuto il tempo di peggiorarla, visto che è una novità. L’ho cucito con queste mani!\nAh-ah-ah! Prima portavo una di quelle... come si chiamano? Le indossa ancora il nostro esercito! Brrr... Solo a vederne una adesso mi viene la nausea.";
			link.l1 = "Uniformi?";
			link.l1.go = "drinking_at_fort_7";
		break;
		
		case "drinking_at_fort_7":
			dialog.text = "Oh, proprio così, una divisa! Una divisa rossa! Come quella che indossa quel tizio.";
			link.l1 = "";
			link.l1.go = "exit";
			
			pchar.GenQuest.BlockDialogCamera = true;
			AddDialogExitQuestFunction("HelenDrinking_OfficerAtFort");
		break;
		
		case "drinking_at_fort_7_1":
			dialog.text = "Oh, mi scusi, Maggiore, permetta che le offra del buon whiskey irlandese come... hic!... segno di scusa.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog2");
		break;
		
		case "drinking_at_fort_7_2":
			dialog.text = "Charles non si metterà nei guai, vero, Maggiore? Dimmi che non succederà, ti prego, sii gentile!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog4");
		break;
		
		case "drinking_at_fort_8":
			dialog.text = "Che gioia! Beviamo!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToVillage");
		break;
		
		case "drinking_at_miskito":
			dialog.text = "Uff. Guarda cosa ho pescato!";
			link.l1 = "Helen... Hai davvero intenzione di usare quella... per tirarti su il morale?!.. Non ci pensare nemmeno! La datura può ridurre in cenere anche il cuore più forte, ti svuota, ti spezza la volontà! Prima che te ne accorga, sarai un fantoccio senza vita, e ben presto anche senza respiro...";
			link.l1.go = "drinking_at_miskito_1";
		break;
		
		case "drinking_at_miskito_1":
			dialog.text = "Charles, ma... proprio adesso...";
			link.l1 = "Niente storie. Mi spiace essere dura, ma questa non è una burla. Questo te lo tolgo subito. Non riesco a credere a cosa avevi in mente… Su, bevi questo e rimettiti in sesto.";
			link.l1.go = "drinking_at_miskito_2";
			
			GiveItem2Character(pchar, "cannabis7");
			PlaySound("interface\important_item.wav");
		break;
		
		case "drinking_at_miskito_2":
			dialog.text = "Mi dispiace, Charles. Hai perfettamente ragione, lo so. Un attimo di debolezza. Non accadrà più. Grazie per avermi salvata dalla tentazione del diavolo...";
			link.l1 = "Dimentichiamo questa storia... Ora dimmi, come hai fatto a guadagnarti rispetto in città, mantenere buoni rapporti con gli ufficiali della guarnigione e farti amico i nativi?";
			link.l1.go = "drinking_at_miskito_3";
		break;
		
		case "drinking_at_miskito_3":
			dialog.text = "Rispetto per Svensson, e un po’ di quella stima cade anche su di me. Il nostro paesello sopravvive soltanto grazie agli accordi di Jan. Divide una parte dei profitti delle sue piantagioni di cacao coi giubbe rosse, e i Miskito gli devono la vita intera.";
			link.l1 = "Come diavolo è successo?";
			link.l1.go = "drinking_at_miskito_4";
		break;
		
		case "drinking_at_miskito_4":
			dialog.text = "Quando i castigliani comandavano, non seccavano troppo gli indios. Ma appena cacciarono via i nobili Hidalgos, la nostra gente decise di mettere le mani sulle foreste locali. Jan risolse la faccenda in modo piuttosto sbrigativo a quei tempi – mandò persino gente a Londra! Ovviamente, mica per bontà d’animo: estrarre cacao in una selva che ti odia a ogni cespuglio è follia pura. Ora invece, gli indios non solo aiutano Jan a contrabbandare da Porto Bello a Blueweld, ma si tagliano pure le proprie foreste per quattro soldi. Bravo, Diavolo del Bosco, bravo!";
			link.l1 = "Pare che tu non approvi del tutto i suoi metodi.";
			link.l1.go = "drinking_at_miskito_5";
		break;
		
		case "drinking_at_miskito_5":
			dialog.text = "Ho affetto e rispetto per il popolo Miskito, ma rispetto anche l’astuzia di Jan. Non viviamo in una favola, mio capitano.";
			link.l1 = "Hm... Vedo che il tuo rapporto con Svensson è più intricato di quanto sembri a prima vista...";
			link.l1.go = "drinking_at_miskito_6";
		break;
		
		case "drinking_at_miskito_6":
			dialog.text = "Even more than you know. His wife has a good reason to be venomous towards me... Jan has been eyeing me since I was about fifteen. It was around the time I started walking the decks of the Rainbow as an equal, and apparently, something clicked in the Forest Devil's mind back then... But I've said too much, my captain. Let's not delve into this topic; gossiping about our patron is not very decent.";
			link.l1 = "Allora cambiamo discorso. Volevo solo dire che ti sei integrato a meraviglia tra questa ciurma, e ormai ti considerano dei loro.";
			link.l1.go = "drinking_at_miskito_7";
		break;
		
		case "drinking_at_miskito_7":
			dialog.text = "Succede che mi trovo assai meglio in compagnia di indiani, zingari e altri bravi sbandati. Gli stufati di mamma, i falò sulla spiaggia, la passerella dell’Arcobaleno… mi sono creata un piccolo mondo tutto mio, capitano. Peccato che tutto sia andato in malora proprio quando pensavo d’aver capito la vita.";
			link.l1 = "La botte è quasi vuota... Un’ultima bevuta?";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToShipyard");
		break;
		
		case "drinking_at_perlas":
			dialog.text = "È così piacevole... Sono felice che tu abbia accettato di passare un po' di tempo con me, Capitano. Ne avevo davvero bisogno. E credo che anche tu, sai.";
			link.l1 = "Sì, è passato un bel po’ da quando mi sono concessa un momento così. Sarà un ricordo da custodire!";
			link.l1.go = "drinking_at_perlas_1";
		break;
		
		case "drinking_at_perlas_1":
			dialog.text = "Probabilmente ora pensi ogni sorta di diavoleria su di me. Di natura sono una persona molto riservata, Charles. È solo che... dannazione, volevo solo sentirmi viva! Volevo solo parlare con qualcuno!";
			link.l1 = "E Gladys? E Jan?";
			link.l1.go = "drinking_at_perlas_2";
		break;
		
		case "drinking_at_perlas_2":
			dialog.text = "Tutta la mamma fa è piangere, e Jan sembra diventato un altro. Forse me lo sto solo immaginando, non so, ma è come se ora si vergognasse di me? Perdonami, io... (singhiozza).\nBasta così, ragazza mia. Scusa, mi sono lasciata un po’ andare.";
			link.l1 = "Non c'è bisogno di scusarti. Capisco tutto, o almeno credo di capire.";
			link.l1.go = "drinking_at_perlas_3";
		break;
		
		case "drinking_at_perlas_3":
			dialog.text = "Dico tutto questo perché ci conosciamo appena, e non sono abituata ad aprirmi nemmeno con chi frequento da anni. Mi chiamano Rumba, dicono per il mio carattere, ma come vedi, non è proprio il nome giusto. È finito tutto il rum?";
			link.l1 = "È passato un po’, e già l’alba comincia a sorgere.";
			link.l1.go = "drinking_at_perlas_4";
		break;
		
		case "drinking_at_perlas_4":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_friend") && !CheckAttribute(pchar, "questTemp.HelenDrinking.RobbedSvenson")) {
				dialog.text = "Mi dispiace, mio capitano, se avevi altre aspettative per la nostra serata. Io... non posso. Non oggi.";
			} else {
				dialog.text = "Allora grazie per questa serata, Capitano. Chissà, forse la ripeteremo.";
			}
			link.l1 = "Ma certo, Hélène.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_PoormanTalk");
		break;
		
		case "ambush":
			dialog.text = "Grazie per avermi condotta qui, Capitano. Diamo un’occhiata in giro, vuoi? Esploriamo la mia eredità.";
			link.l1 = "Non sei già stato qui, per caso?";
			link.l1.go = "ambush_1";
		break;
		
		case "ambush_1":
			dialog.text = "No, it's quite a ways away; besides, I'm no pirate. This place has never been particularly fascinating, and after they killed Blaise... It's better not to linger here.";
			link.l1 = "Non lo faremo. Già mi pento d’averti portato qui.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPrepareAmbush");
		break;
		
		case "after_ambush":
			switch (pchar.questTemp.HelenDrinking.IslaTesoroAmbush) {
				case "A":
					if (!CheckAttribute(pchar, "questTemp.HelenDrinking.IslaTesoroAmbush.TriedB") && !CheckAttribute(pchar, "questTemp.HelenDrinking.IslaTesoroAmbush.TriedC")) {
						dialog.text = "Did you have to, Captain? Why so quick to fight? Well, one should not just a winner, I guess. Come on, let's take a look at the residence; there's nothing else worth seeing here anyway.";
						pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 1;
						notification("Helen disapproves", "Helena");
					} else {
						dialog.text = "Kudos, my Captain, for trying to resolve the issue wisely before getting into a fight. Come on, let's take a look at the residence; there's nothing else worth seeing here anyway.";
					}
					
					link.l1 = "E quella nave enorme tirata in secco?";
					link.l1.go = "after_ambush_1";
				break;
				
				case "B":
					dialog.text = "You skillfully fooled those fools, my Captain! I almost burst out laughing, honest! Come on, let's take a look at the residence; there's nothing else worth seeing here anyway.";
					pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
					notification("Helen approves", "Helena");
					
					link.l1 = "E quella nave enorme tirata in secco?";
					link.l1.go = "after_ambush_1";
				break;
				
				case "C":
					dialog.text = "Aspetta, lascia che una ragazza riprenda fiato! Sei davvero tu, quel famoso Charlie Prince?";
					pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
					notification("Helen approves", "Helena");
					
					link.l1 = "Ci fu un tempo simile nella mia vita, sì. Sei rimasto colpito?";
					link.l1.go = "after_ambush_c";
				break;
			}
		break;
		
		case "after_ambush_1":
			dialog.text = "Sì, hai ragione. Mi piacerebbe scoprirlo, ma a dire il vero, Charles, mi fa anche un po’ paura. Andiamo.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroGoToResidence");
		break;
		
		case "after_ambush_c":
			dialog.text = "Santo cielo, sì! Mi raccomando, poi raccontami tutto nei dettagli, d’accordo? Perché finora ho sentito solo storie... storie parecchio sconvenienti!";
			link.l1 = "Ti racconterò tutto... o quasi tutto.";
			link.l1.go = "after_ambush_c_1";
		break;
		
		case "after_ambush_c_1":
			dialog.text = "I'll be waiting eagerly! Come on, let's take a look at the residence; there's nothing else worth seeing here anyway.";
			link.l1 = "E che mi dici di quella nave gigantesca tirata in secco?";
			link.l1.go = "after_ambush_1";
		break;
		
		case "ambush_inresidence":
			dialog.text = "Una lurida tana angusta e gelida, con pretese assurde. Mi sembra già d’essere finita in una trappola!";
			link.l1 = "Vedo che finora non sei soddisfatto della possibile proprietà?";
			link.l1.go = "ambush_inresidence_1";
		break;
		
		case "ambush_inresidence_1":
			dialog.text = "No, Charles. Forse sono troppo esigente, ma per ora rappresenta tutto ciò che temo e detesto. Spero di riuscire ad affittarla... Anche se non saprei proprio dove andrei a spendere quei soldi.";
			link.l1 = "Non sottovalutare il valore dell'affitto. Io non ne ho, e spesso devo inventarmi qualcosa per pagare la ciurma. Tu ti comprerai una nuova nave, 'Arcobaleno II' – suona bene, non credi?!";
			link.l1.go = "ambush_inresidence_sea";
			link.l2 = "Ci sono mille modi per spendere denaro per sé stessi. Inizia con una spada su misura e una bottiglia di vino sopraffino. Concediti un capriccio, Hélène, te lo sei meritato.";
			link.l2.go = "ambush_inresidence_land";
		break;
		
		case "ambush_inresidence_sea":
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Background") && pchar.questTemp.HelenDrinking.Background == "sea") {
				dialog.text = "Grazie, mio capitano. Mi fa piacere sentirlo. E ancor di più sentirlo una seconda volta. Mi conosci davvero bene.";
				pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 3;
				notification("Helen approves", "Helena");
			} else {
				dialog.text = "Grazie, mio capitano. Mi fa piacere sentirtelo dire.";
			}
			
			link.l1 = "";
			link.l1.go = "ambush_inresidence_2";
			
			sld = CharacterFromID("Helena");
			
			AddCharacterSkill(sld, SKILL_COMMERCE, 5);
			AddCharacterSkill(sld, SKILL_ACCURACY, 5);
			AddCharacterSkill(sld, SKILL_CANNONS, 5);
			AddCharacterSkill(sld, SKILL_SAILING, 5);
			AddCharacterSkill(sld, SKILL_REPAIR, 5);
			AddCharacterSkill(sld, SKILL_GRAPPLING, 5);
			AddCharacterSkill(sld, SKILL_DEFENCE, 5);
		break;
		
		case "ambush_inresidence_land":
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Background") && pchar.questTemp.HelenDrinking.Background == "land") {
				dialog.text = "Pensi che lo meriti? Non ho mai sprecato monete in simili frivolezze, ma suppongo che a tutto si venga una prima volta. Vedo che non smetti di tentare di farmi scordare il richiamo del mare, eh, Capitano? Forse hai ragione tu...";
				pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 3;
				notification("Helen disapproves", "Helena");
			} else {
				dialog.text = "Pensi che lo meriti? Non ho mai sprecato denaro in simili sciocchezze, ma suppongo che per tutto ci sia una prima volta.";
			}
			link.l1 = "";
			link.l1.go = "ambush_inresidence_2";
			
			sld = CharacterFromID("Helena");
			
			AddCharacterSkill(sld, SKILL_F_LIGHT, 5);
			AddCharacterSkill(sld, SKILL_FENCING, 5);
			AddCharacterSkill(sld, SKILL_F_HEAVY, 5);
			AddCharacterSkill(sld, SKILL_PISTOL, 5);
			AddCharacterSkill(sld, SKILL_FORTUNE, 5);
			AddCharacterSkill(sld, SKILL_LEADERSHIP, 5);
			AddCharacterSkill(sld, SKILL_SNEAK, 5);
		break;
		
		case "ambush_inresidence_2":
			dialog.text = "In ogni caso, l’ispezione è finita. Qui non pare sia rimasto nulla di valore – la gentaglia ha già razziato tutto, e scommetto che anche il piano di sopra è ridotto allo stesso stato.";
			link.l1 = "È come se tu fossi cambiata, Helen. L’ultima volta che ci siamo visti eri... non so, più aperta?";
			link.l1.go = "ambush_inresidence_3";
		break;
		
		case "ambush_inresidence_3":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6) {
				dialog.text = "Niente è cambiato, mio capitano, ma tante fatiche son cadute sulle spalle d’una povera fanciulla, ahah! Non volevo offenderti. Ho solo bisogno di riflettere su molte cose, adesso. Sai, svolte così brusche nella vita non capitano ogni giorno. E poi, abbiamo ancora tanto tempo insieme!";
				link.l1 = "Felice di sentirlo! Andiamocene da qui.";
			} else {
				dialog.text = "Much has changed, Captain. I'm afraid I have to be more mature now and look at life differently. It's not a fairy tale about a princess and inheritance; it's big politics, and I still have to realize my place in it. And my family's place too.";
				link.l1 = "Sono lieta che ci siamo capiti. Andiamocene da qui.";
			}
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroBeforeExit");
		break;
		
		case "ambush_inresidence_wait":
			dialog.text = "Sì?";
			if (CheckCharacterItem(pchar, "pirate_cutlass")) {
				link.l1 = "Ehi, non tutto è stato razziato! Guarda, Hélène! Questa sciabola pare proprio leggendaria, visto che persino la feccia locale ha esitato a metterci le mani sopra.";
				link.l1.go = "ambush_inresidence_give_cutlass";
			}
			
			link.l2 = "No, niente.";
			link.l2.go = "exit";
			
			NextDiag.TempNode = "ambush_inresidence_wait";
		break;
		
		case "ambush_inresidence_give_cutlass":
			dialog.text = "Accidenti, questa è... la leggendaria sciabola di Blaise in persona! Anche i pirati lo rispettavano troppo per portar via la lama dalla sua casa, persino dopo la sua morte. Hanno preso soldi e ricchezze, ovvio, ma persino quei futuri impiccati conservavano un briciolo d’onore...";
			link.l1 = "It looks like someone is clearly tidying up here. As if the owner will come back... This is not a home; it's a memorial!";
			link.l1.go = "ambush_inresidence_give_cutlass_1";
		break;
		
		case "ambush_inresidence_give_cutlass_1":
			dialog.text = "Grazie per l’acuta osservazione, Charles. Ormai questo posto non sarà mai più lo stesso ai miei occhi, ahah!";
			link.l1 = "Penso che questa sciabola ormai sia tua. Blaise è il tuo cosiddetto zio...";
			link.l1.go = "ambush_inresidence_give_cutlass_2";
		break;
		
		case "ambush_inresidence_give_cutlass_2":
			dialog.text = "Tu ci aggiungi ancora più orrore, mio capitano. Io... io non posso. Ho paura che, se accetto, la mia vita di prima finirà per sempre.";
			link.l1 = "Allora prendilo non come parte dell’eredità, ma come dono di un uomo affascinante.";
			link.l1.go = "ambush_inresidence_give_cutlass_3";
		break;
		
		case "ambush_inresidence_give_cutlass_3":
			dialog.text = "Chi sarebbe mai? Scherzo! Grazie per aver scacciato le mie cupe fantasie, mio capitano. Ti prometto che mi eserciterò senza tregua per essere degna di questa lama!";
			link.l1 = "Sei degna della lama più pregiata, Helen. Andiamo, qui abbiamo finito.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GiveCutlass");
		break;
		
		case "give_cutlass":
			dialog.text = "Accidenti, questa è... la leggendaria sciabola di Blaise in persona! I pirati lo rispettavano talmente da non osare portar via la sua lama nemmeno dopo la sua morte. Hanno preso il denaro e i tesori, certo, ma persino quei futuri impiccati conservano qualche briciolo d’onore.\nIo... io non posso. Temo che, se l’accettassi, la mia vecchia vita finirebbe per sempre.";
			link.l1 = "Allora prendilo non come parte dell’eredità, ma come dono di un bel gentiluomo.";
			link.l1.go = "give_cutlass_1";
		break;
		
		case "give_cutlass_1":
			dialog.text = "Chi sarebbe? Scherzo! Grazie per aver scacciato i miei cupi pensieri, mio capitano.";
			link.l1 = "Meriti la lama più pregiata, Helen. Son felice che ti piaccia.";
			link.l1.go = "give_cutlass_2";
		break;
		
		case "give_cutlass_2":
			dialog.text = "Prometto che mi allenerò senza sosta per essere degna di questa lama!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GiveCutlass");
		break;
		
		case "arrive":
			dialog.text = "Mio capitano! Charlie!";
			link.l1 = "Charlie? Questa è nuova! Felice di vederti, caro.";
			link.l1.go = "arrive_1";
		break;

		case "arrive_1":
			dialog.text = "Ops, mi è scappato, ah! Felice di vederti anche io...";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JungleDialog1");
		break;

		case "arrive_2":
			dialog.text = "Così tanto per la solidarietà femminile! Mio capitano, io... ero davvero in pena e mi sei mancato da morire!";
			link.l1 = "E allora, perché sei dovuto scappare a casa tua?";
			link.l1.go = "arrive_3";
		break;

		case "arrive_3":
			dialog.text = "Ah... Giusto! Ho un piccolo dono per te, eccolo!";
			link.l1 = "Tre amuleti... Helen, perché? Volevi seguirmi?";
			link.l1.go = "arrive_4";
			
			GiveItem2Character(pchar, pchar.questTemp.Saga.BaronReturn.Indian);
			GiveItem2Character(pchar, pchar.questTemp.Saga.BaronReturn.Amulet);
			GiveItem2Character(pchar, pchar.questTemp.Saga.BaronReturn.Obereg);
		break;

		case "arrive_4":
			dialog.text = "Vieni qui, sciocco mio!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FirstKiss");
		break;

		case "after_kiss":
			dialog.text = "Non osare rovinare questo momento – l’ho sognato per tutta la vita!";
			link.l1 = "Non lo farò, Helen.";
			link.l1.go = "after_kiss_a";
			link.l2 = "Hai aspettato tutta la vita per incontrarmi? Mi lusinga, davvero!";
			link.l2.go = "after_kiss_b";
			if (GetCharacterIndex("Mary") >= 0 && CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive") {
				link.l3 = "Hélène, devo dirti una cosa... Sull’Isola della Giustizia ho incontrato una donna, e...";
				link.l3.go = "after_kiss_c";
			}
			locCameraFromToPos(-19.00, 1.56, 19.07, true, -11.19, -0.90, 17.49);
		break;
		
		case "after_kiss_a":
			dialog.text = "Accidenti, sì! Mi racconterai tutto, tutto quanto! Ti aspetto sulla nave, mio capitano!";
			link.l1 = "Aspetta!...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterKiss1");
		break;
		
		case "after_kiss_b":
			dialog.text = "Sciocco! Vuoi insultarmi? Benissimo, mi sento offesa! Ah-ah! Ora me ne torno alla nave, prima che Danny si prenda ancora gioco di me...";
			link.l1 = "Aspetta!...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterKiss1");
		break;
		
		case "after_kiss_c":
			dialog.text = "Sciocco! Ti avevo detto di non rovinare il momento! Incontrata... sì, incontrata – ma ancora non vedo un anello al dito tuo. E non pensare di svignartela così – pretendo tutti i dettagli quando sarai di ritorno a bordo.";
			link.l1 = "Aspetta!...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterKiss1");
		break;
		
		case "loot_good":
			dialog.text = "Mio capitano, quali sono le novità? Dal tuo viso pallido capisco che il leguleio ha pensato bene di gettarti altra rogna addosso invece di darti una mano.";
			link.l1 = "Hai ragione, Helen. Loxley ha preteso un anticipo da far tremare i forzieri, e tutta la faccenda mi costerà un occhio della testa. Ora vado a scuotere Jan – ne ho fin sopra i capelli! Pare proprio che la Fratellanza voglia scaricare tutte le sue spese sul sottoscritto!";
			link.l1.go = "loot_good_1";
		break;
		
		case "loot_good_1":
			dialog.text = "Non c’è cattiveria in questo, Charles. Sono fatti così – non si muovono finché non devono. Son certa che Jan ti darà una mano, e io non starò certo a guardare con le mani in mano.";
			link.l1 = "Lo so, Helene. Dimmi che cosa ti frulla per la testa.";
			link.l1.go = "loot_good_2";
		break;
		
		case "loot_good_2":
			dialog.text = "Lavoravo per Jan — portavo legname pregiato di contrabbando su e giù per il Maine. Ma sono una ragazza piena di risorse, sai; durante tutti quei viaggi ho messo da parte qualcosa per me.";
			link.l1 = "E Jan non se n’è accorto? Furba!";
			link.l1.go = "loot_good_3";
		break;
		
		case "loot_good_3":
			dialog.text = "Avevo un ottimo tesoriere. Insomma, ho messo da parte una bella somma e l’ho nascosta non lontano da qui. Vai da Jan adesso? Allora facciamo rotta su San Juan del Norte. C’è una grotta nei paraggi, ci servirà solo qualche marinaio per darci una mano, così non ci tocca trascinare tutto da soli.";
			link.l1 = "Hai già capito tutto, vero? Grazie, Helene, passeremo senz'altro se il tempo ce lo permette.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_CreateLoot");
		break;
		
		case "loot_bad":
			dialog.text = "Mio capitano, quali sono le novità? Dal tuo viso smunto capisco che l’avvocato ha pensato bene di gettarti addosso altri guai invece di darti una mano.";
			link.l1 = "Hai ragione, Helen. Loxley ha preteso un anticipo da vero filibustiere, e tutta questa faccenda mi costerà un occhio della testa. Ora vado a scuotere Jan – ne ho fin sopra i capelli! Pare che i Fratelli abbiano deciso di scaricare tutte le loro spese su di me!";
			link.l1.go = "loot_bad_1";
		break;
		
		case "loot_bad_1":
			dialog.text = "Credevi forse d’essere in una fiaba? Non temere, navighiamo tutti nella stessa barca, e ti darò una mano. Dopotutto, anch’io ho diritto alla mia eredità, o sbaglio?";
			link.l1 = "È vero... Dimmi, cosa ti passa per la testa!";
			link.l1.go = "loot_bad_2";
		break;
		
		case "loot_bad_2":
			dialog.text = "Ho qualcosa nascosto a San Juan del Norte. C’è una grotta lì vicino – ci basterà raccattare qualche marinaio, così non dovremo portarci tutto il malloppo da soli.";
			link.l1 = "Hai già capito tutto, vero? Grazie, Helen, verremo senz'altro a trovarti se il tempo ce lo permetterà.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_CreateLoot");
		break;
		
		case "shdn":
			dialog.text = "Ecco ci siamo, Charles! Ma dovrai andare da solo – odio le grotte!";
			link.l1 = "Come ogni spazio chiuso, lo so, Helen. Aspettami qui.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GoForLoot");
		break;
		
		case "shdn_ambush":
			dialog.text = "Abbiamo un problema! Una pattuglia di soldati sta arrivando da questa parte, e non hanno certo l’aria amichevole. Fa’ attenzione, Charles, non sono i soliti cani da guardia della costa – c’è pure un ufficiale francese con loro! Ti supplico, non fare qualche sciocchezza!";
			link.l1 = "Quando mai avrei fatto qualcosa di sciocco?!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_SpawnAmbushSoldiers");
		break;
		
		case "shdn_ambush_1":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6) {
				dialog.text = "Ah, la seconda opzione sembra più allettante, ma spero che tu non sia troppo fiero di te stesso, Charles?";
			} else {
				dialog.text = "Non posso certo dire di stupirmi, Charles...";
			}
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog1");
		break;
		
		case "shdn_ambush_2":
			dialog.text = "Hai finito? Ora tocca a me parlare!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_HelenKillFrancois");
		break;
		
		case "shdn_ambush_3":
			dialog.text = "Il mio nome è Helen MacArthur! Capitano, sai chi sono e per chi lavoro! Avvisa la tua ciurma, specialmente quel damerino che se ne sta steso per terra, dei risultati di oggi, che sto per proclamare!";
			link.l1 = "";
			link.l1.go = "exit";
			CharacterTurnToLoc(npchar, "quest", "richard");
			sld = CharacterFromID("HelenDrinking_Richard");
			CharacterTurnByChr(sld, npchar);
			
			AddDialogExitQuestFunction("HelenDrinking_AfterFrancoisDeath2");
		break;
		
		case "shdn_ambush_4":
			dialog.text = "Protesta pure? Non m’importa se scrivi finanche a Cromwell in persona. Primo: monsieur de Maure oggi non ha perso il suo onore.";
			link.l1 = "";
			link.l1.go = "shdn_ambush_5";
			CharacterTurnToLoc(npchar, "quest", "richard");
		break;
		
		case "shdn_ambush_5":
			dialog.text = "In secondo luogo, il colonnello de Tavann si beccò una pallottola da una ragazza in abiti davvero piccanti, per averla chiamata sgualdrina.";
			link.l1 = "";
			link.l1.go = "shdn_ambush_6";
		break;
		
		case "shdn_ambush_6":
			dialog.text = "Terzo, ritiri subito i tuoi soldati e ti scordi di tutto questo, a meno che tu non voglia che il Diavolo della Foresta venga a saperlo.";
			link.l1 = "";
			link.l1.go = "shdn_ambush_7";
		break;
		
		case "shdn_ambush_7":
			locCameraSleep(false);
			dialog.text = "Nessuna domanda, vedo. Buona giornata, Capitano.";
			link.l1 = "Santo cielo, Helen, sei un fuoco vivo!";
			link.l1.go = "shdn_ambush_8";
		break;
		
		case "shdn_ambush_8":
			dialog.text = "Più tardi, Charles. Andiamo via di qui prima che si riprendano dallo spavento. Anche io tremo tutta. Possiamo parlare a Blueweld?";
			link.l1 = "D'accordo.";
			link.l1.go = "exit";
			CharacterTurnByChr(npchar, pchar);
			
			AddDialogExitQuestFunction("HelenDrinking_AfterFrancoisDeath3");
		break;
		
		case "duel_victory":
			dialog.text = "Andiamo via di qui prima che si riprendano dallo choc. Dobbiamo ancora recuperare il legno di ferro, ricordi? Parleremo a Blueweld.";
			link.l1 = "Perdinci! Neanche un complimento? Va bene, andiamo.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_DuelVictory1");
		break;
		
		case "after_cave":
			dialog.text = "Finalmente, a casa...";
			link.l1 = "Cosa ne pensi di quello che è successo?";
			link.l1.go = "after_cave_1";
		break;
		
		case "after_cave_1":
			dialog.text = "Non capisco i duelli. Roba da uomini, quasi sempre finisce con due cadaveri, e se la sorte è davvero beffarda, pure di più. E l’onore… Io credo che l’onore si fondi proprio sul tentativo di evitare la rissa fino all’ultimo respiro, ché tanto di rado ne vale la pena. Ah! Sentimi qui – che sciocchezze sto dicendo!";
			link.l1 = "È un punto di vista curioso, Helen. Ma non tutti la penserebbero così.";
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Duel")) {
				link.l1.go = "after_cave_duel";
			} else {
				link.l1.go = "after_cave_notduel";
			}
		break;
		
		case "after_cave_duel":
			dialog.text = "Peccato che tu sia caduto nella loro trappola. Il colonnello era chiaramente ossessionato, e gli altri cercavano solo spettacolo e pettegolezzi. Ma non ti infierirò oltre – oggi ne hai già passate abbastanza.";
			link.l1 = "Sì, dopo i duelli resta sempre un vuoto nell'anima. Basta avventure per oggi. Che vuoi fare adesso?";
			if (sti(pchar.questTemp.Saga.HelenRelation) == 7 || sti(pchar.questTemp.Saga.HelenRelation) == 8) {
				link.l1.go = "after_cave_mild";
			} else {
				if (sti(pchar.questTemp.Saga.HelenRelation) < 7) {
					link.l1.go = "after_cave_cold";
				} else {
					link.l1.go = "after_cave_lewd";
				}
			}
		break;
		
		case "after_cave_notduel":
			dialog.text = "Ugh!  Volevo solo dirti che sono fiera di noi. Hai mostrato vero coraggio oggi, mio capitano. Non ti sei lasciato travolgere dal panico della ciurma che voleva, per una volta, darti ordini. Sei rimasto saldo davanti alle arie del rosso e alla fissazione del blu. Il colonnello cercava la morte, ma non ha trovato altro che una ferita in un posto piuttosto sconveniente, ah-ah!";
			link.l1 = "Grazie, Helen. Ci hai fatto schivare la tempesta come un vero lupo di mare. Sei fiera di te stessa?";
			link.l1.go = "after_cave_notduel_1";
		break;
		
		case "after_cave_notduel_1":
			dialog.text = "Sì, ne avevo proprio bisogno. Peccato solo che fosse una giubba blu invece che rossa, ma almeno chi la indossava ha avuto quel che si meritava.";
			link.l1 = "Quella persona conta ben poco, lo ammetto. Basta avventure per oggi. Che vuoi fare adesso?";
			if (sti(pchar.questTemp.Saga.HelenRelation) == 7 || sti(pchar.questTemp.Saga.HelenRelation) == 8) {
				link.l1.go = "after_cave_mild";
			} else {
				if (sti(pchar.questTemp.Saga.HelenRelation) < 7) {
					link.l1.go = "after_cave_cold";
				} else {
					link.l1.go = "after_cave_lewd";
				}
			}
		break;
		
		case "after_cave_mild":
			dialog.text = "Sto tornando a casa, mio capitano. Mi manca la mia... Gladys. Peccato che sia a casa in questo momento, altrimenti ti avrei invitato io!";
			link.l1 = "Davvero, che peccato!";
			link.l1.go = "after_cave_mild_1";
		break;
		
		case "after_cave_mild_1":
			dialog.text = "Non essere così turbato. Presto, mio caro. Nel frattempo...";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_SecondKiss");
		break;
		
		case "after_second_kiss":
			locCameraFromToPos(4.97, 3.71, 16.06, true, 5.09, 1.25, 11.67);
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Kiss")) {
				dialog.text = "M-m-m, questa è ancora meglio della prima. Ti ricordi? Vicino all’idolo?";
				link.l1 = "Non è cosa che si scorda, caro mio.";
				link.l1.go = "after_second_kiss_1";
			} else {
				dialog.text = "Non osare rovinare questo momento – l’ho sognato per tutta la mia vita!";
				link.l1 = "Non lo farò, Helen.";
				link.l1.go = "after_second_kiss_a";
				link.l2 = "Hai aspettato tutta la vita per incontrarmi? Mi sento lusingata!";
				link.l2.go = "after_second_kiss_b";
			}
		break;
		
		case "after_second_kiss_1":
			dialog.text = "Ohh! Raccogliti, ragazza! Fino al nostro prossimo incontro, mio capitano.";
			link.l1 = "Fino ad allora, Helene.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveMild");
		break;
		
		case "after_second_kiss_a":
			dialog.text = "Accidenti, proprio così!  Ci rivedremo presto, mio capitano.";
			link.l1 = "Fino al nostro prossimo incontro, Hélène. Dio mio, che donna...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveMild");
		break;
		
		case "after_second_kiss_b":
			dialog.text = "Stupido! Vuoi insultarmi? Ebbene sì, mi sento offesa! Ah-ah! Ci rivedremo presto, mio capitano.";
			link.l1 = "Finché non ci rivedremo, Helen. Dio mio, che donna...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveMild");
		break;
		
		case "after_cave_cold":
			dialog.text = "Me ne torno a casa, Capitano. Immagino che la faccenda coi soldi e l’avvocato sia sistemata ormai? Davanti a noi ci aspettano scogli ben più duri, quindi cerchiamo di non cacciarci nei guai per un po’. Tanto saranno loro a trovare noi, maledizione.";
			link.l1 = "Ma davvero?";
			link.l1.go = "after_cave_cold_1";
		break;
		
		case "after_cave_cold_1":
			dialog.text = "Perdonami la franchezza, Capitano. Anche il mio destino si sta giocando proprio adesso, sai.";
			link.l1 = "Lo so, cercherò di affrontare tutto con la massima dignità. Ci vediamo a bordo, Helen.";
			link.l1.go = "after_cave_cold_2";
		break;
		
		case "after_cave_cold_2":
			dialog.text = "Aye aye, Capitano!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveCold");
		break;
		
		case "after_cave_lewd":
			dialog.text = "E adesso? Te lo faccio vedere io.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_SecondKiss");
		break;
		
		case "after_second_kiss1":
			locCameraFromToPos(4.97, 3.71, 16.06, true, 5.09, 1.25, 11.67);
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Kiss")) {
				dialog.text = "M-m-m, questa è ancor più dolce della prima volta. Ricordi? Vicino all'idolo?";
				link.l1 = "Queste cose non si scordano, caro.";
				link.l1.go = "after_second_kiss1_1";
			} else {
				dialog.text = "Non osare rovinare questo momento – l’ho sognato per tutta la vita!";
				link.l1 = "Non lo farò, Helene.";
				link.l1.go = "after_second_kiss1_a";
				link.l2 = "Hai aspettato tutta la vita per incontrarmi? Mi fai arrossire!";
				link.l2.go = "after_second_kiss1_b";
			}
		break;
		
		case "after_second_kiss1_1":
			dialog.text = "Accidenti, proprio così! Oh! Gladys non è a casa ora. Vuoi entrare?";
			link.l1 = "Mi stai invitando da te? E cosa mai faremmo insieme?";
			link.l1.go = "after_cave_lewd_accept";
			if (GetCharacterIndex("Mary") >= 0 && CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive") {
				link.l2 = "No, Helen. Un'altra donna m’attende sull’Isola della Giustizia. Non potrei mai tradirla così.";
				link.l2.go = "after_cave_lewd_refuse_mary";
			}
			link.l3 = "Un'altra volta, mio caro. Lo desidero davvero, ma oggi mi ha quasi mandato all'altro mondo. Recupereremo il tempo perso con gli interessi, te lo prometto.";
			link.l3.go = "after_cave_lewd_refuse_head";
		break;
		
		case "after_second_kiss1_a":
			dialog.text = "Per tutti i diavoli! Accidenti! Gladys non è in casa adesso. Vuoi entrare?";
			if (GetCharacterIndex("Mary") >= 0 && CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive") {
				link.l1 = "No, Helen. Un'altra donna mi aspetta sull’Isola della Giustizia. Non potrei farle questo.";
				link.l1.go = "after_cave_lewd_refuse_mary";
			}
			link.l2 = "Un'altra volta, caro mio. Lo desidero davvero, ma oggi mi ha sfinita. Recupereremo e compenseremo tutto il tempo perso dieci volte tanto.";
			link.l2.go = "after_cave_lewd_refuse_head";
			link.l3 = "Mi stai invitando da te? E che cosa faremmo insieme?";
			link.l3.go = "after_cave_lewd_accept";
		break;
		
		case "after_second_kiss1_b":
			dialog.text = "Stupido! Vuoi offendermi? Benissimo, mi hai offesa! Ah-ah! Ora dovrai farti perdonare, mio capitano. Oh! Gladys non è in casa adesso. Vuoi entrare?";
			if (GetCharacterIndex("Mary") >= 0 && CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive") {
				link.l1 = "No, Helen. Un'altra donna mi attende sull'Isola della Giustizia. Non potrei mai farle questo.";
				link.l1.go = "after_cave_lewd_refuse_mary";
			}
			link.l2 = "Un'altra volta, caro mio. Lo desidero davvero, ma oggi mi ha sfiancata. Recupereremo e ci rifaremo del tempo perduto dieci volte tanto.";
			link.l2.go = "after_cave_lewd_refuse_head";
			link.l3 = "Mi stai invitando da te? E che cosa avresti in mente di fare, eh?";
			link.l3.go = "after_cave_lewd_accept";
		break;
		
		case "after_cave_lewd_refuse_mary":
			dialog.text = "Ah, dunque non sono abbastanza abile nell’arte della seduzione? E lei invece sì? Chi sarebbe, questa lei?";
			link.l1 = "Il suo nome è Mary Casper, e io la amo.";
			link.l1.go = "after_cave_lewd_refuse_mary_1";
		break;
		
		case "after_cave_lewd_refuse_mary_1":
			dialog.text = "Quella rossa con la divisa scarlatta? Con la divisa rossa... Beh, se mi serviva un segno, eccolo qua. Non doveva andare così. E non preoccuparti, Capitano, questo non cambierà il modo in cui servo sulla tua nave.";
			link.l1 = "Mi dispiace, Hélène.";
			link.l1.go = "exit";
			
			pchar.questTemp.HelenDrinking.Mary = true;
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveRefuseMary");
		break;
		
		case "after_cave_lewd_refuse_head":
			dialog.text = "Oh, mio capitano! È rischioso lasciare una donna in questo stato! Mi affido alla tua promessa, e adesso vattene... Ho bisogno di restare sola e affrontare questa faccenda... per conto mio! Ci vediamo a bordo!";
			link.l1 = "Che donna!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveRefuseMild");
		break;
		
		case "after_cave_lewd_accept":
			dialog.text = "Non temere, caro mio, ti farò da bussola se dovessi smarrirti.";
			link.l1 = "Ebbene... guida tu!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveAccept");
		break;
		
		case "after_cave_bedroom":
			dialog.text = "Non dire nulla, te ne supplico.";
			link.l1 = "...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveSex1");
		break;
		
		case "after_cave_sex":
			dialog.text = "... ma certo, fino ad oggi la mia conoscenza in materia si basava unicamente sulle sguaiate chiacchiere dell’equipaggio dell’‘Arcobaleno’, se così si possono chiamare, naturalmente.";
			link.l1 = "E allora, com’è andata? La realtà era all’altezza dei tuoi sogni?";
			link.l1.go = "after_cave_sex_1";
		break;
		
		case "after_cave_sex_1":
			dialog.text = "Mi è piaciuto molto, ma sento di non averlo vissuto fino in fondo. E come...";
			link.l1 = "Lascia che ti mostri! Proseguiamo?";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveSex2");
		break;
		
		case "after_cave_sex_again":
			dialog.text = "Oh, ora capisco! È stato semplicemente magnifico, mio capitano!";
			link.l1 = "Mi hai davvero colta di sorpresa, per dir poco!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveGladysEnter");
		break;
		
		case "after_cave_gladys":
			dialog.text = "Ah-ah-ah! Questa è davvero buona, senza dubbio! Ora o si tapperà le orecchie con la cera, oppure correrà sulla cima della fortezza!";
			link.l1 = "Quello sì che è stato inaspettato ma spassosissimo, ah-ha-ha!";
			link.l1.go = "after_cave_gladys_1";
			locCameraFromToPos(-0.62, 1.93, -0.39, true, -2.46, -1.20, 1.01);	// Sinistra - постельная камера
		break;
		
		case "after_cave_gladys_1":
			dialog.text = "Pronto, mio capitano?";
			link.l1 = "Già?! No, Helen, abbi pietà di me, ti supplico. La comparsa improvvisa di Gladys non ha certo migliorato l’atmosfera.";
			link.l1.go = "after_cave_gladys_2";
		break;
		
		case "after_cave_gladys_2":
			dialog.text = "Ebbene, che ci vuoi fare... Anche se...";
			link.l1 = "No, no, abbassa le vele!";
			link.l1.go = "after_cave_gladys_3";
		break;
		
		case "after_cave_gladys_3":
			dialog.text = "D'accordo, allora restiamo insieme ancora un po'. Il futuro è così oscuro e spaventoso, ma per la prima volta da tanto tempo non temo più nulla. So che qualche nuova paura arriverà, ma non oggi. Non oggi, mio capitano.";
			link.l1 = "Non oggi, mio caro. Non oggi.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveFin");
		break;
		
		case "give_potions":
			dialog.text = "Permesso di parlare, Capitano?";
			link.l1 = "Sì, Hélène?";
			link.l1.go = "give_potions_1";
		break;
		
		case "give_potions_1":
			dialog.text = "Conosco quel Serpente Occhio: è un brav’uomo, ma ha qualche rotella fuori posto. Manda sempre la gente in giro a fare chissà quali imprese. Pare che tu abbia avuto lo stesso, eh?";
			if (!CheckAttribute(CharacterFromID("SnakeEye"), "quest.amulet")) {
				link.l1 = "Già, devo portargli tre amuleti, altrimenti non potrà aiutarmi a raggiungere il rifugio di Hawk. Ma sai qual è la parte buffa? Ce li avevo già con me! Forse lui lo sapeva fin dall’inizio?";
				link.l1.go = "give_potions_already";
			} else {
				link.l1 = "Esatto, devo portargli tre amuleti, altrimenti non potrà aiutarmi a raggiungere il covo di Hawk. Ora non so proprio dove cercarli, e il tempo stringe.";
				link.l1.go = "give_potions_3";
			}
		break;
		
		case "give_potions_already":
			dialog.text = "Oh, che peccato! Son felice che tu non abbia dovuto correre in giro a raccattare quegli amuleti dai guardiani dei fari, ma speravo, almeno per una volta, di poterti essere utile, di dimostrarti il mio valore.";
			link.l1 = " Sciocchezze, Helen. Non devi dimostrarmi proprio nulla. ";
			link.l1.go = "give_potions_4";
		break;
		
		case "give_potions_3":
			dialog.text = "Ti aiuterò! Lo confesso, speravo che per una volta potessi esserti utile, desideravo dimostrarti il mio valore.";
			link.l1 = "Sciocchezze, Helen. Non devi dimostrarmi nulla.";
			link.l1.go = "give_potions_4";
		break;
		
		case "give_potions_4":
			dialog.text = "Tuttavia, voglio aiutarti. Prendi la chiave della mia stanza... cioè, della cassa nella mia stanza! Non c’è granché, ma per te potrebbe tornar utile. E... Charles, ti sfido a non scoppiare a ridere proprio adesso!";
			link.l1 = "Ehm, non ci pensavo nemmeno. Vedo che ti piacciono queste cose?";
			link.l1.go = "give_potions_5";
		break;
		
		case "give_potions_5":
			dialog.text = "Sono una navigante, mio capitano, proprio come te. Nel nostro mestiere bisogna ingegnarsi in tutto per avere la Fortuna dalla nostra parte.";
			link.l1 = "Grazie, Helen. Te ne sono davvero grato.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GivePotionsKey");
		break;
		
		case "upgrade":
			dialog.text = "Tesoro, ho un dono per te!";
			link.l1 = "Ah, eccolo lì – in piedi, tutto sorridente!";
			link.l1.go = "upgrade_1";
		break;
		
		case "upgrade_1":
			dialog.text = "Ah-ha, basta così! Una volta ho portato un bel carico di seta al carpentiere del porto, ora mi deve un restauro completo per la nave. Avevo pensato di affidargli l’Arcobaleno, ma non era destino. Il tuo vascello, invece, potrebbe davvero godere di tante attenzioni, non credi?";
			link.l1 = "In verità, un dono splendido, Hélène – proprio nelle tue corde!";
			link.l1.go = "upgrade_2";
		break;
		
		case "upgrade_2":
			dialog.text = "Sono lieta che ti piaccia. Passa pure da lui quando vuoi e digli che ti mando io. Faranno un lavoro coi fiocchi.";
			link.l1 = "Decisamente!";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Helena_officer";
			AddDialogExitQuestFunction("HelenUpgradeShip1");
		break;
		
		case "give_sex":
			dialog.text = "Permesso di parlare, mio capitano?";
			link.l1 = "Ma certo, caro mio.";
			link.l1.go = "give_sex_1";
		break;
		
		case "give_sex_1":
			dialog.text = LinkRandPhrase("La tua dama sente la tua mancanza e reclama attenzioni. Posso chiedere che le venga preparata una stanza e che tu le dedichi un po' del tuo tempo?","Resoconto: la tua presenza è richiesta in un letto della taverna locale. Solo cinque minuti del tuo tempo, ma l’equipaggio spera che tu resti molto di più!","Ammutinamento a bordo, mio capitano! Mi è stato ordinato di consegnarti il marchio nero in privato. Seguimi senza indugio!");
			link.l1 = "Ehm-ehm! La tua richiesta è esaudita, ufficiale Sharp!";
			link.l1.go = "give_sex_1_yes";
			link.l2 = "Oggi no, caro. Troppa confusione in questo momento.";
			link.l2.go = "give_sex_1_no";
		break;
		
		case "give_sex_1_yes":
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
			DialogExit();
			AddDialogExitQuestFunction("Helen_GiveSexGoToTavern");
		break;
		
		case "give_sex_1_no":
			dialog.text = "Oh, e che cosa dovrebbe fare una povera ragazza, eh? Va bene, caro mio, sarà per un’altra volta allora.";
			link.l1 = "";
			link.l1.go = "give_sex_2_no";
		break;
		
		case "give_sex_2_no":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			npchar.location = "None";
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetOfficerType(npchar);
			chrDisableReloadToLocation = false;
			
			pchar.quest.Helen_GiveSex.win_condition.l1 = "Timer";
			pchar.quest.Helen_GiveSex.win_condition.l1.date.day = GetAddingDataDay(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l1.date.month = GetAddingDataMonth(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l1.date.year  = GetAddingDataYear(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l2 = "Location_Type";
			pchar.quest.Helen_GiveSex.win_condition.l2.location_type = "town";
			pchar.quest.Helen_GiveSex.function = "Helen_GiveSex";
		break;
		
		case "special_sex":
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
			SaveCurrentNpcQuestDateParam(npchar, "special_sex_date");
			
			dialog.text = "Ah! Non c'è bisogno che me lo chieda due volte! Certo, andiamo!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Helen_GiveSexGoToTavern");
		break;
		
		case "rainbow":
			dialog.text = "Ti butto a mare subito, dannato!";
			link.l1 = "Ehi, ehi, ehi! Calmati, cara!";
			link.l1.go = "rainbow_1";
		break;
		
		case "rainbow_1":
			dialog.text = "Vieni qui, furfante!";
			link.l1 = "Scherzavo, Helen! Non volevo offenderti!";
			link.l1.go = "rainbow_2";
		break;
		
		case "rainbow_2":
			dialog.text = "Ah davvero? Sei proprio un buffone...";
			link.l1 = "Sei la più bella che abbia mai visto, e ti amo da impazzire!";
			link.l1.go = "rainbow_3";
		break;
		
		case "rainbow_3":
			dialog.text = "Vattene, Charles.";
			link.l1 = "";
			link.l1.go = "exit";
			
			DeleteAttribute(pchar, "questTemp.HelenDrinking.Rainbow");
			Achievment_Set("ach_CL_84");
		break;
		
		case "joan":
			dialog.text = "Sei tu la sgualdrina! Sii grata che Jan ti abbia reso una donna rispettabile, altrimenti saresti ancora lì ad allargare le gambe al primo che passa!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JoanDialog2");
		break;
		
		case "joan_1":
			dialog.text = "Svergognata! Andiamo, Charles!";
			link.l1 = "";
			link.l1.go = "exit";
			
			ResetSound();
			SetMusic("helendrinking_shanty");
			pchar.questTemp.lockedMusic = true;
			AddDialogExitQuestFunction("HelenDrinking_GoToFort");
		break;
		
		case "cutlass_training":
			dialog.text = "La sciabola mi calza a pennello! Non saprei spiegare... Ho sempre faticato con altre armi bianche, come spade e stocchi. Ma questa sciabola è tutta un’altra faccenda! Sembra fatta per me! Grazie, Charles!";
			link.l1 = "Il destino trova sempre la sua strada. Son felice per te, Helen!";
			link.l1.go = "exit";
			notification("Medium Weapons +", "Helena");
		break;
		
		case "brothel_found":
			dialog.text = "Risparmia le tue storie per qualcun altro, su di me non attaccano. Sembro forse una sciocca ingenua colpita da Amore? Intendo, SÌ, sono perdutamente innamorata di te, ma chiamarmi sciocca sarebbe un tantino esagerato.\n Senti, mio caro, fa’ come ti pare, ma ricorda che una donna migliore di me non la troverai. Se vuoi cercarla nei postriboli, accomodati pure, ma poi io svanirò dalla tua vita per sempre.";
			link.l1 = "Hélène, io...";
			link.l1.go = "brothel_found_1";
		break;
		
		case "brothel_found_1":
			dialog.text = "Capisco tutto, Charles. Tu ami solo me, e il resto sono solo pulsioni naturali. Sai qual è la mia pulsione naturale? Il rispetto da parte del mio uomo. L’amore da solo non basta a una donna, tesoro. Dimentichiamo questo malinteso per ora, ma rifletti sulle mie parole. Va bene?";
			link.l1 = "Va bene, Hélène.";
			link.l1.go = "exit";
		break;
		
		case "refuse":
			dialog.text = "Sai come vanno queste cose. Lascia che una ragazza sbollisca prima.";
			link.l1 = "Sospir...";
			link.l1.go = "exit";
		break;
		
		// Тайна Порт-Рояля
		case "MysteryPortRoyal_Helena_1":
			dialog.text = "Francis... lo ricordo bene. Mi attendeva sempre a Port Royal, perso nei suoi sogni d'amore. Stare con qualcuno così lontano dal mare... tutte quelle poesie, le serenate... Era qualcosa di nuovo per me. Uno scorcio di un mondo che non avevo mai conosciuto.\nFrancis era ricco, astuto e bello – una vera preda. Qualunque ragazza del posto avrebbe perso la testa per lui, ma allora io pensavo solo a mantenere la Rainbow a galla.";
			link.l1 = "Sembra che l’animo delicato di un poeta non abbia retto al tuo rifiuto. In tutte le sue lettere parlava solo di te, rammentando i luoghi dove vi siete incontrati. Posso darti tutto ciò che ha lasciato, se lo desideri.";
			link.l1.go = "MysteryPortRoyal_Helena_2";
		break;
		
		case "MysteryPortRoyal_Helena_2":
			dialog.text = "Non sapevo che fosse malato. Tutto questo ora mi sembra così sciocco. Quanto al suo regalo... Ne ho abbastanza di testamenti e eredità. Fidati, ho tutto quel che mi serve – e anche di più. Ti conviene tenerlo tu.";
			link.l1 = "In un modo o nell'altro, la sua eredità finirà comunque per servirti – il che vuol dire che, senza volerlo, ho realizzato il suo ultimo desiderio. Che storia, eh.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.MysteryPortRoyal_Helena");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}

bool HelenDrinking_RobbedSvenson() {
	sld = &locations[FindLocation("SantaCatalina_houseS1_residence")];
	if (!CheckAttribute(sld, "private1.items.chest")) { 
		return true;
	}
	
	if (sti(sld.private1.items.chest) < 2) {
		return true;
	}
	
	return false;
}

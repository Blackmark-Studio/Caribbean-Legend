// отец Винсенто
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "santiago")
			{
				dialog.text = "Finalmente vedo il rinomato capitano francese "+GetFullName(pchar)+" in carne ed ossa. Ho sentito molto parlare delle tue imprese. Sei un soldato valoroso e, spero, un figlio leale e devoto della nostra Madre, la Santa Chiesa Cattolica Romana. Siediti, figliolo. Non c'è bisogno di restare in piedi per me. Dominus vobiscum! ";
				link.l1 = "Et cum spiritu tuo, Vostra Eccellenza. Il mio viaggio fin qui è stato lungo e faticoso... Per aspera ad astra e tutto il resto...";
				link.l1.go = "utensil";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "twoitems" && !CheckAttribute(npchar, "quest.skinmap"))
			{
				dialog.text = "Sì, vedo dal tuo sguardo che porti notizie per me. Hai tutta la mia attenzione.";
				link.l1 = "Vostra Eccellenza, ho ritrovato il vostro segretario scomparso...";
				link.l1.go = "guardoftruth";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "mayak")
			{
				dialog.text = "Mi hai portato notizie da San Jose, figliolo?";
				link.l1 = "Sì, Vostra Eccellenza. Ho scoperto cosa è accaduto al nostro comune conoscente Miguel Dichoso e alla sua fregata scomparsa. Appena la sua nave è entrata nell'Atlantico diretta in Spagna, fu subito sorpresa da una tempesta contraria e risospinta di nuovo nei Caraibi.";
				link.l1.go = "guardoftruth_10";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Archy") && pchar.questTemp.Guardoftruth.Archy == "begin")
			{
				dialog.text = "Pax vobiscum, figliuolo... Che posso fare per te?";
				link.l1 = TimeGreeting()+", Vostra Eccellenza. Avete notizie riguardo al nostro accordo?"link.l1.go ="guardoftruth_17";
				break;
			}
			dialog.text = "Cercavi qualcosa, figliolo?";
			link.l1 = "No, niente, padre.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "utensil":
			dialog.text = "'Enter by the narrow gate; for wide is the gate and broad is the way that leads to destruction, and there are many who go in by it. Because narrow is the gate and difficult is the way which leads to life, and there are few who find it.' The path of righteousness is always difficult, my son. But the aim that is achieved fully rewards a righteous man for his works.";
			link.l1 = "Concordo, Vostra Eccellenza. Ho portato a termine i compiti che mi avete affidato. Il vile bucaniere che rubò i sacri oggetti della Chiesa è già nelle vostre mani. Ora vi restituisco tutto ciò che fu sottratto: l’ostensorio, la croce e l’incensiere. Prendeteli per la parrocchia di Santiago.";
			link.l1.go = "utensil_1";
		break;
		
		case "utensil_1":
			RemoveItems(pchar, "jewelry33", 1);
			RemoveItems(pchar, "jewelry34", 1);
			RemoveItems(pchar, "jewelry35", 1);
			dialog.text = "Benedicite! Ti ringrazio con tutto il cuore per il tuo fedele servizio alla Santa Madre Chiesa e alla parrocchia di Santiago, figliolo. Le tue gesta non resteranno senza ricompensa. I parrocchiani hanno raccolto un'offerta per il valoroso guerriero che ha restituito i loro averi rubati, e te la consegno volentieri a nome loro. 'Il lavoratore è degno della sua paga.'";
			link.l1 = "Grazie, Vostra Eccellenza. Che lieta sorpresa!";
			link.l1.go = "utensil_2";
		break;
		
		case "utensil_2":
			GiveItem2Character(pchar, "chest");
			Log_Info("You've received a chest of doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Il fedele servizio alla Santa Madre Chiesa viene sempre ricompensato con altrettanta fedeltà, "+pchar.name+"Da parte mia, spero che tu resti un fedele guerriero a difesa e protezione della Cristianità, ché una minaccia mortale incombe su di noi come la mitica Spada di Damocle.";
			link.l1 = "Che potrebbe essere mai, Vostra Eccellenza?";
			link.l1.go = "utensil_3";
		break;
		
		case "utensil_3":
			dialog.text = "Forse sei destinato a diventare il nostro campione nella battaglia imminente contro le forze oscure e i principati di questo mondo, figliolo, poiché molti sono i segni e i presagi che qualcosa di malvagio si avvicina.";
			link.l1 = "Segni e presagi?";
			link.l1.go = "utensil_4";
		break;
		
		case "utensil_4":
			dialog.text = "Molte, figliolo... Una di queste è la tua brama di cercare l’oro perduto degli indiani, il tesoro pagano di Tayasal, poiché ciò che viene custodito nei loro forzieri è proprio ciò che minaccia tutto il mondo cristiano.";
			link.l1 = "Mi potreste illuminare su questo oro, reverendo Padre? La storia della sua sparizione l’ho già sentita, ma di quale minaccia parlate?";
			link.l1.go = "utensil_5";
		break;
		
		case "utensil_5":
			dialog.text = "Ascolta attentamente, figlio mio, e sappi che tutto ciò che stai per udire è solo per le tue orecchie. Molto prima che Miguel Dichoso portasse quel tesoro pagano fuori dall’antica città indiana, feci interrogare un prigioniero degli indiani Itza riguardo alla nostra missione nei Caraibi. Gli Itza discendono dai Maya, un impero potente scomparso secoli prima ancora che Cristoforo Colombo e i suoi uomini posassero piede nel Nuovo Mondo. L’Impero Maya dominava le tribù circostanti con pugno di ferro, possedendo poteri indicibili ottenuti tramite patti infernali con i demoni. Magie oscure pagate col sangue di generazioni di sacrifici umani. \nQuest’uomo Itza conosceva Tayasal, una città maya perduta e il male incredibile ancora sigillato al suo interno. Ci raccontò tutto ciò che sapeva. Se quei sigilli venissero infranti, le conseguenze sarebbero apocalittiche. Da allora ho fatto tutto ciò che era in mio potere per impedire che questo male terribile venisse risvegliato. Scrissi disperatamente all’Escorial e a Roma chiedendo aiuto.\nMi ascoltarono e inviarono Don Ramon de Mendoza y Riba, che stabilì la sua base a Providence e iniziò a cercare Tayasal. Fu allora che scoprii che il buon Don Mendoza aveva... motivi diversi per trovare la città perduta. Invece di impedire la fine del mondo, cercava di servire Mammona anziché Cristo.\nPer questo Dio lo abbandonò e mandò l’angelo della morte nel suo accampamento. Tutte le sue azioni furono vane e portarono solo alla morte inutile di soldati spagnoli e indiani convertiti. Scrissi all’Escorial chiedendo di sollevare Ramon de Mendoza dal comando per manifesta incompetenza e accettarono di liberarlo dai suoi incarichi, ma...";
			link.l1 = "Miguel Dichoso è arrivato.";
			link.l1.go = "utensil_6";
		break;
		
		case "utensil_6":
			if (CheckAttribute(pchar, "questTemp.Dolly")) sTemp = "Kukulcan?! Sancta Maria, Mater Dei, ora pro nobis! Kukulcan again, that old serpent...";
			else sTemp = "Hm...";
			dialog.text = "Esattamente. Quell’avventuriero mandato dal diavolo trovò Tayasal insieme ai tesori degli antichi Maya. Ma la gioia di Don Mendosa durò poco. Tutti quei tesori svanirono insieme a Dichoso sulla via del ritorno in Spagna. È assai probabile che, oltre a lingotti d’oro e ornamenti, Miguel si sia portato dietro un’antica fonte di stregonerie: la terribile maschera d’un demone dio Maya chiamato Kukulcan.";
			link.l1 = sTemp+"Ma di quale malvagità parlate, Vostra Eccellenza? E come ne siete a conoscenza?";
			link.l1.go = "utensil_7";
		break;
		
		case "utensil_7":
			dialog.text = "È un male che porta la morte a tutti i cristiani battezzati dei Caraibi, del Nuovo Mondo, e forse pure del Vecchio. La fine giungerà come un ladro nella notte, e nessuno si accorgerà di cosa sia accaduto. E già ovunque se ne vedono i presagi!";
			link.l1 = "Che presagi? Non capisco...";
			link.l1.go = "utensil_8";
		break;
		
		case "utensil_8":
			dialog.text = "Figliolo, sei davvero così cieco da non accorgertene nemmeno? Succedono da venticinque anni, quasi senza sosta!";
			link.l1 = "Mi permetto umilmente di ricordare, Vostra Eccellenza, che il mio percorso terreno conta giusto questi anni, senza contare che ho vissuto la maggior parte della mia vita in Europa. Bisognerebbe dunque perdonare almeno un poco la mia ignoranza.";
			link.l1.go = "utensil_9";
		break;
		
		case "utensil_9":
			dialog.text = "Capisco, "+pchar.name+"Dimmi, non hai notato stranezze nei Caraibi dal tuo arrivo dall’Europa? Non ti pare curioso che stregoneria, magia nera e riti oscuri qui abbiano mille volte più potere che nella vecchia patria? Amuleti pagani benedetti dagli sciamani indios sprigionano una forza che ogni uomo sente appena li stringe in pugno.\nPersino i nostri alchimisti cristiani—che Dio li illumini!—hanno imparato a fabbricare oggetti incantati. Non capiscono d’esser servi del Demonio. Non percepisci anche tu la presenza innaturale, qualcosa d’infernale che ti scruta appena oltre l’angolo dell’occhio?";
			link.l1 = "Hai ragione, padre. All’inizio mi ha sorpreso, ma ormai credo d’esserci abituato... Dopotutto, questo è il Nuovo Mondo!";
			link.l1.go = "utensil_10";
		break;
		
		case "utensil_10":
			dialog.text = "Ma non è sempre stato così. L’ombra di cui parlo è giunta qui circa venticinque anni fa, e da allora si fa ogni giorno più potente. Questo può significar solo una cosa: ‘esso’ è già arrivato, ‘esso’ è fra noi, e ‘esso’ già trama...";
			link.l1 = "Di chi stai parlando? Chi sarebbe questo misterioso 'esso'?";
			link.l1.go = "utensil_11";
		break;
		
		case "utensil_11":
			dialog.text = "Il giurato nemico dei cristiani, assetato della rovina della Chiesa e di tutta la cristianità.";
			link.l1 = "...Stai parlando dell’Anticristo?";
			link.l1.go = "utensil_12";
		break;
		
		case "utensil_12":
			dialog.text = "Sia che sia 'l'Anticristo' o soltanto 'un' anticristo, non mi permetto di giudicare. Poco importa il nome che questa bestia assume quando si veste di carne mortale in una sprezzante parodia dell’Incarnazione del Nostro Salvatore. Ciò che conta davvero è quel che intende fare. Io sono qui per fermarlo, e tu mi darai una mano. Ma ci siamo lasciati un po’ prendere la mano. Tu sei uomo d’azione, non ti va di perder tempo in prediche e preferiresti passare al sodo, vero?";
			link.l1 = "Al contrario, Vostra Eccellenza, da voi ho appreso molte novità importanti. Sono tutto orecchi, continuate pure.";
			link.l1.go = "utensil_13";
		break;
		
		case "utensil_13":
			dialog.text = "Sei cortese e ben educato, figliolo. Benissimo. Ora torniamo alla ragione per cui sei venuto a parlare con me. Il nostro scopo comune è ritrovare i tesori di Tayasal portati via da Dichoso. Tra quei bottini, con ogni probabilità, si cela un'arma che potremo usare nella prossima battaglia contro il Diavolo.";
			link.l1 = "Ma vuoi vedere che Dichoso se n’è già filato dai Caraibi e ora se ne sta seduto su una montagna d’oro in Spagna?";
			link.l1.go = "utensil_14";
		break;
		
		case "utensil_14":
			dialog.text = "No. Ho le prove che questi tesori sono ancora qui nei Caraibi. Non hai ancora bisogno di sapere da dove le ho; dovrai fidarti di me. Inoltre, credo che Dichoso abbia raccontato frottole al barone.\nLa sua storia sulle rovine di Tayasal non quadra con quello che mi ha confessato il mio indio Itza sotto torchio. E poi, che Dichoso sia uscito vivo da quell’agguato dei Zanzarosi... troppo comodo, non trovi?";
			link.l1 = "Immagino che anche Don Mendosa la pensi così, visto che ha assaltato Saint-Pierre alla ricerca di Dichoso?";
			link.l1.go = "utensil_15";
		break;
		
		case "utensil_15":
			dialog.text = "Non ti curar delle azioni del barone, figliolo. È mosso soltanto dalla brama d’oro e dal proprio tornaconto. La sua avidità sarà il cappio che lo trascinerà a fondo, mentre attorno a lui buoni cristiani combattono le schiere dell’Inferno.";
			link.l1 = "Hai qualche indizio su dove dovremmo cercare Dichoso e il tesoro?";
			link.l1.go = "utensil_16";
		break;
		
		case "utensil_16":
			dialog.text = "Ci penso ogni istante, figlio mio, ma non ho nulla di preciso da dirti. Però qui c'è un uomo che potrà aiutarci, un filosofo naturale di Genova. L'ho portato con me per catalogare le meraviglie del Nuovo Mondo che potrebbero giovare alla missione della Chiesa. Ha assistito all’interrogatorio dell’indio Itza e, a quanto posso giudicare, ciò che udì lo sconvolse e insieme lo attrasse in modo perverso. Il Demonio ha usato la sua curiosità come un amo ben innescato e se l’è preso, corpo e anima. Il Signore gli aveva donato gran talento per la medicina e l’alchimia, ma il nostro genovese è caduto nella tentazione della magia nera e della stregoneria. Ha parlato più volte col mio prigioniero Itza senza il mio permesso, poi è sparito. Dobbiamo trovarlo e salvare la sua anima.";
			link.l1 = "Immagino che tocchi a me trovarlo, eh?";
			link.l1.go = "utensil_17";
		break;
		
		case "utensil_17":
			dialog.text = "Sì, figlio mio. Egli è il primo passo per trovare il tesoro e l’arma che potremo brandire contro le forze malvagie che ci minacciano.";
			link.l1 = "Chi è questo genovese?";
			link.l1.go = "utensil_18";
		break;
		
		case "utensil_18":
			dialog.text = "Si chiama Gino Gvineili. Avrà trent’anni, più o meno. È un medico e alchimista di gran talento. Come ti dicevo, ora si diletta con le arti nere. Secondo le mie ultime notizie, si nasconde da qualche parte tra le colonie inglesi nei Caraibi. \nTrova Gino Gvineili, figliolo. Se sei riuscito a mettere le mani su quel filibustiere che ci ha trafugato i vasi sacri, saprai rintracciare anche il mio segretario ribaldo e ricondurlo qui. Pregherò Sant’Antonio perché ti assista.";
			link.l1 = "Capisco, Vostra Eccellenza. Non perderò altro tempo. Ci vediamo più tardi!";
			link.l1.go = "utensil_19";
		break;
		
		case "utensil_19":
			DialogExit();
			AddQuestRecord("Guardoftruth", "35");
			bool bOk = (pchar.questTemp.HWIC.Detector == "holl_win") || (pchar.questTemp.HWIC.Detector == "eng_win") || (pchar.questTemp.HWIC.Detector == "self_win");
			if (CheckAttribute(pchar, "questTemp.HWIC.Detector") && bOk)
			{
				pchar.questTemp.Guardoftruth = "jino";
				AddQuestUserData("Guardoftruth", "sText", "I almost betrayed myself by a shout of surprise. Father Vincento ordered me to find and bring him his runaway secretary, a physician alchemist named Gino Gvineili. That same Gino who occupies the spare room on the second floor of my house in St. John's!");
			}
			else
			{
				pchar.questTemp.Guardoftruth = "merdok";
				AddQuestUserData("Guardoftruth", "sText", "I must find a man named Gino Gvineili, hiding somewhere in the English Caribbean colonies. He is a physician and an alchemist. Where can a man like him hide?");
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Ero certo che avresti risposto così, "+pchar.name+". Ora la mia fede si rafforza ancor di più, certo che siete stato mandato a меня dalla stessa Mano della Divina Provvidenza. Dov'è mio figlio sciagurato, il figliol prodigo?";
			link.l1 = "Temo che quello che sto per dirti non ti piacerà affatto, ma non ho altra scelta. Il tuo segretario è morto.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Che il Signore abbia pietà della sua anima e gli perdoni i peccati... Com’è successo, figliolo?";
			link.l1 = "Ho trovato Gino ad Antigua. Si nascondeva là, in uno dei vecchi edifici costruiti sotto il laboratorio. Non ha voluto venire con me di buon grado. Quando ha sentito il tuo nome e ha visto che ero pronto a usare la forza, ha tirato fuori dalle pieghe della sua lunga veste una fiala di liquido trasparente e se l'è scolata in un attimo...";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "";
			link.l1 = "E poi accadde qualcosa di terribile: diventò rosso, poi di un blu scurissimo. Crollò a terra contorcendosi in spasmi e in un attimo spirò tra dolori atroci. Un forte odore di mandorle amare riempì la stanza.";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Gino... Povero sciocco... Ha sprecato persino l’ultimo istante della sua vita peccando con quel suicidio. Che perdita funesta. Pregherò per la sua anima...";
			link.l1 = "Dopo la sua morte, ho frugato nella sua dimora e ho trovato questo fascicolo. Potrebbe forse interessarti, o magari esserci utile nelle nostre ricerche? Ci sono delle annotazioni strane, quasi arcane, qui dentro...";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			RemoveItems(pchar, "Almanac", 1);
			Log_Info("You've given the almanac");
			PlaySound("interface\important_item.wav");
			dialog.text = "Questo è l’almanacco del povero Gino. Annotava qui tutte le sue scoperte e avventure. Dammelo, figliolo, darò un’occhiata a ciò che vi è scritto. Magari ci troveremo qualche indizio.\nAnche se non mi hai riportato indietro Gino Gvineili, sono soddisfatto del tuo impegno, figliolo. Ora lascia che ti dia qualche notizia.";
			link.l1 = "Hai catturato la mia attenzione, padre.";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "Ho saputo che l’isola di Trinidad è stato l’ultimo posto dove si è vista la fregata di Dichoso. So anche un periodo approssimativo: i primi di aprile del 1654. \nVai a Trinidad e prova a scoprire tutto ciò che puoi sul destino della fregata: dove era diretta, che piani aveva il capitano, qualsiasi briciola tu riesca a trovare. Capisco che sia passato molto tempo e la memoria degli uomini è fallace, ma quando si affoga ci si aggrappa pure alle alghe.";
			link.l1 = "Farò tutto ciò che è in mio potere.";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "Fammi vedere la tua lettera di salvacondotto. Aggiungerò il permesso per visitare la colonia di San Jose.";
			link.l1 = "Ecco.";
			link.l1.go = "guardoftruth_6a";
		break;
		
		case "guardoftruth_6a":
			RemoveItems(pchar, "VerifyPaper", 1);
			dialog.text = "Ecco... questo è tutto. Non scordarti di issare la bandiera spagnola sulla tua nave. Avanza e ricevi la benedizione di Dio, figliolo!";
			link.l1 = "Un momento, Vostra Grazia. Posso porvi una domanda?";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "Sì, naturalmente. Cosa desideri sapere?";
			link.l1 = "Durante il nostro ultimo incontro, mi parlavi di un indio Itza che ti aveva parlato di Tayasal. Ci ho rimuginato parecchio... Dimmi, quell’uomo aveva qualcosa con sé? Oggetti strani, scritti, o simili? Potrebbe tornarci utile.";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = "Niente di speciale, figliolo. Un perizoma, qualche amuleto da selvaggio, una pipa di bambù piena d’erbe strane, e un pezzo di cuoio rozzo usato come bavaglio. Tutto è stato spedito a Don Ramon de Mendoza y Riba. Ma ti assicuro, non c’era nulla che valesse davvero la pena.";
			link.l1 = "Capisco. Grazie, padre. Fino alla prossima volta!";
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			DialogExit();
			GiveItem2Character(pchar, "VerifyPaper");
			ChangeItemDescribe("VerifyPaper", "itmdescr_VincentoPaper_A");
			AddQuestRecord("Guardoftruth", "38");
			npchar.quest.skinmap = "true";
			pchar.questTemp.Guardoftruth.Trinidad = "begin";
		break;
		
		case "guardoftruth_10":
			dialog.text = "Che l’Onnipotente ti benedica e ti protegga... Che ne è stato di Miguel Dichoso? Hai scoperto qualcosa?";
			link.l1 = "Ahimè, no. L’ultima cosa che i testimoni mi hanno detto è che la Santa Quiteria fu spinta dai venti impetuosi verso la Martinica. Nessuno sa se la nave sia sopravvissuta o sia andata a fondo. Ma io sospetto che Miguel Dichoso sia riuscito a salvarsi.";
			link.l1.go = "guardoftruth_11";
		break;
		
		case "guardoftruth_11":
			dialog.text = "Che ti ha spinto a questa decisione, figliolo?";
			link.l1 = "La chiave è che la fregata si celava da qualche parte verso la Martinica. E proprio di recente un baldo caballero di nome Diego de Montoya, uno degli uomini stessi di Don Ramon de Mendosa, ha assaltato Saint-Pierre nel tentativo di scovare Miguel Dichoso, che pare si nascondesse laggiù.";
			link.l1.go = "guardoftruth_12";
		break;
		
		case "guardoftruth_12":
			dialog.text = "Dunque, il barone crede che Dichoso si sia nascosto coi francesi...";
			link.l1 = "Conosco bene Saint-Pierre e il governatore Jacques Dyel du Parquet, Vostra Eccellenza. Nessuno lì ha mai sentito parlare di uno spagnolo chiamato Miguel Dichoso. Potreste dirmi come rintracciare Diego de Montoya? Vorrei parlargli riguardo a Dichoso.";
			link.l1.go = "guardoftruth_13";
		break;
		
		case "guardoftruth_13":
			dialog.text = "Ne sei proprio certo che ti riceverebbe, figliolo? Io non credo proprio, a meno che tu non parli con spada e pistola.";
			link.l1 = "Forse il tuo nome riuscirà a sciogliergli la lingua?";
			link.l1.go = "guardoftruth_14";
		break;
		
		case "guardoftruth_14":
			dialog.text = "Oh, "+pchar.name+". Dubito che l’uomo giurato di Don Mendosa sia disposto a trattare con voi. Potrei ordinargli di presentarsi a San Diego per una mia udienza, ma non credo proprio che Diego sarebbe del tutto sincero con me nemmeno in quel caso.";
			link.l1 = "Quali ordini, padre, vuoi che io esegua adesso?";
			link.l1.go = "guardoftruth_15";
		break;
		
		case "guardoftruth_15":
			dialog.text = "Lasciami solo per un po', figliolo. Devo riflettere su quanto mi hai raccontato e mettere insieme tutto ciò che già so dalle mie fonti. Dopo ti dirò quale sarà la nostra prossima mossa. Passa più tardi.";
			link.l1 = "Sissignore. Lo farò. Controllerò di tanto in tanto...";
			link.l1.go = "guardoftruth_16";
		break;
		
		case "guardoftruth_16":
			DialogExit();
			AddQuestRecord("Guardoftruth", "43");
			pchar.questTemp.Guardoftruth.Trinidad = "end";
			pchar.quest.GuardOT_setSpaOfficer.win_condition.l1 = "ExitFromLocation";
			pchar.quest.GuardOT_setSpaOfficer.win_condition.l1.location = pchar.location;
			pchar.quest.GuardOT_setSpaOfficer.function = "GuardOT_SetSpaOfficerInTown";
			NextDiag.CurrentNode = "guardoftruth_wait";
		break;
		
		case "guardoftruth_wait":
			dialog.text = "Dio ti benedica, figliolo... Che posso fare per te?";
			link.l1 = "Avete novità, Vostra Eccellenza?";
			link.l1.go = "guardoftruth_wait_1";
		break;
		
		case "guardoftruth_wait_1":
			dialog.text = "Non adesso, figliolo. Ma non disperare. Io e la mia gente ci stiamo lavorando. Passa più tardi.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "guardoftruth_wait";
		break;
		
		case "guardoftruth_17":
			dialog.text = "Sì, figlio mio. Ho raccolto alcune notizie su Miguel Dichoso. Non fu vano il mio sospetto che Dichoso fosse ancora vivo e si aggirasse nei Caraibi. Pare proprio che Don Diego de Montoya avesse ragione. Abbiamo ricevuto conferma da un uomo che conosceva Miguel Dichoso di vista: il gentiluomo scomparso fu avvistato nell’insediamento pirata di Le François, a Martinica, nell’aprile del 1654, poco dopo la sparizione della Santa Quiteria...";
			link.l1 = "Dunque, la fregata è affondata sulle coste della Martinica?";
			link.l1.go = "guardoftruth_18";
		break;
		
		case "guardoftruth_18":
			dialog.text = "Calmati, figliolo. Al momento non abbiamo alcых notizie di un naufragio vicino alla Martinica в то время. E una fregata non è certo una feluca: la sua distruzione avrebbe di sicuro attirato parecchia attenzione e offerto un bel banchetto agli avvoltoi di queste acque.";
			link.l1 = "Forse vale la pena frugare la costa e le spiagge per scovare ciò che resta di quella nave?";
			link.l1.go = "guardoftruth_19";
		break;
		
		case "guardoftruth_19":
			dialog.text = "Figliolo, Don Diego de Montoya ha già fatto tutto questo senza cavarne un ragno dal buco. Ascolta ancora. I miei informatori a Providence dicono che il Barone è convinto che la Santa Quiteria navighi ancora nei Caraibi, anche se sotto altro nome.\nEcco perché dà la caccia a Miguel Dichoso con tale foga. A detta sua, la Santa Quiteria è stata avvistata non lontano da Isla Tesoro e di recente si sarebbe vista sotto bandiera inglese, scortata da una squadra militare.";
			link.l1 = "Cosa? Incredibile. Dicevano che resistere a una tempesta simile fosse impossibile... E adesso la Santa Quiteria non solo ne è uscita viva, ma naviga pure sotto bandiera inglese? Non torna tutto. Cos’ha spinto il Barone a dire che fosse proprio la Santa Quiteria? È davvero una nave tanto unica?";
			link.l1.go = "guardoftruth_20";
		break;
		
		case "guardoftruth_20":
			dialog.text = "Oh sì. Questa fregata è stata costruita secondo le tecniche più moderne d’Europa. Per la sua classe porta un armamento di tutto rispetto, e la sua velocità le consente di seminare qualunque nave meglio armata. Almeno così mi ha detto la mia fonte.";
			link.l1 = "E ora si chiama forse Santa Quiteria?";
			link.l1.go = "guardoftruth_21";
		break;
		
		case "guardoftruth_21":
			dialog.text = "Questo, ahimè, non lo so... Vai all’Isla Tesoro, "+pchar.name+", e cerca di scoprire qualcosa sulla fregata di Dichoso. Magari così riusciremo a rintracciare anche il suo vecchio capitano, due piccioni con una fava. O due topi nella stessa trappola.";
			link.l1 = "Consideralo fatto, Vostra Eccellenza!";
			link.l1.go = "guardoftruth_22";
		break;
		
		case "guardoftruth_22":
			DialogExit();
			AddQuestRecord("Guardoftruth", "59");
			// проверяем, жив ли Акула и где он, если жив
			if (GetCharacterIndex("Dodson") != -1)
			{
				sld = characterFromId("Dodson");
				if (sld.location == "Pirates_townhall") pchar.questTemp.Guardoftruth.Archy = "islatesoro";
				else pchar.questTemp.Guardoftruth.Archy = "islatesorotavern";
			}
			else pchar.questTemp.Guardoftruth.Archy = "islatesorotavern";
			SetTimerCondition("Map_SetNationCoolHanters", 0, 0, 5, false); // немного развлечений
		break;
		
		case "tieyasal":
			dialog.text = "Sono lieto che tu abbia deciso di venire a trovarmi, figlio mio.";
			link.l1 = "Salve, Vostra Eccellenza. Dopo l’incontro con Don Alonso de Maldonado, mai avrei creduto di rivedervi ancora.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Don Alonso de Maldonado ha infranto i miei ordini diretti. Gli avevo tassativamente proibito di affrontarti, figliolo mio, sapevo bene come sarebbe finita per lui. E ciò che avevo previsto si è avverato. Il suo compito era di scortarti fino a Tayasal, poiché vi era già stato in passato.\nOltretutto, la sua squadra e una compagnia di soldati spagnoli dovevano difenderti da un eventuale attacco degli Itza o dei Mosquito. Alonso si è comportato in modo indegno, accecato da un egoistico desiderio di vendetta, .\nNon solo ha mandato in malora la spedizione a Tayasal e condannato i soldati e le navi affidategli, ma ha anche seminato sfiducia e rancore nel tuo cuore nei miei confronti. Ti assicuro, figliolo, che sono completamente dalla tua parte. Dobbiamo restare uniti contro questa tenebra che incombe.";
			link.l1 = "Mi piacerebbe crederci.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = "State tranquillo, "+pchar.name+" Io, fedele e devoto servitore del nostro Signore Gesù Cristo e rappresentante della Sua Chiesa, sono mosso da un unico scopo: impedire che la fine del mondo giunga prima che ogni anima abbia udito la parola del Nostro Beato Redentore. E ciò significa fermare l’agente diabolico che ora riposa nelle mani di un indiano posseduto dal demonio. L’ho sospettato fin dall’inizio, e solo ora ne sono pienamente certo. Sei stato scelto dal Signore come Suo campione nella battaglia contro Satana.";
			link.l1 = "Ma cosa ti fa dire questo, padre?";
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			dialog.text = "Sei riuscito a fare ciò che né io con tutti i miei uomini, né il Barone Mendosa, né Don Diego, né nessun altro avrebbe mai potuto fare. Hai trovato quell’isola maledetta e stai cercando l’artefatto di Kukulcán, vero?";
			link.l1 = "Sì, ho la maschera di Kukulcan.";
			link.l1.go = "tieyasal_4";
		break;
		
		case "tieyasal_4":
			dialog.text = "E vorresti forse dire che tutto ciò è accaduto per caso? Per pura coincidenza? 'Il cuore dell’uomo traccia la sua via, ma è il Signore che guida i suoi passi.' Figlio mio, l’Onnipotente ti ha condotto su questa rotta! Ha reso salda la tua mano in battaglia, ha guidato i tuoi piedi sulla giusta via e t’ha protetto nei momenti di pericolo! 'Ecco, la spada del Signore cala per giudicare Edom, sopra il popolo che ho votato alla distruzione!'";
			link.l1 = "Ehm... Padre, ma la missione, in fondo, è già compiuta. Ho la maschera. Questo non significa forse che il guscio posseduto di Kukulkan non potrà più intromettersi nella nostra storia e mutarla...?";
			link.l1.go = "tieyasal_5";
		break;
		
		case "tieyasal_5":
			dialog.text = "Ti sbagli, figliolo. Il demonio può varcare quel portale con o senza questa maschera. La maschera gli rende soltanto più facile compiere le sue malefatte. L’unica cosa che può fermarlo è la distruzione totale delle maledette porte infernali.";
			link.l1 = "Don Alonso mi ha detto la stessa cosa...";
			link.l1.go = "tieyasal_6";
		break;
		
		case "tieyasal_6":
			dialog.text = "E aveva ragione! In nome di Nostro Signore Gesù Cristo e della Sua Santissima Madre, ti chiamo a impugnare la Croce contro questo male, figliolo! Non puoi rifiutare la grande missione che ti è stata affidata. Io e tutta la cristianità contiamo su di te, figlio mio.";
			link.l1 = "Vostra Eccellenza, è davvero troppo. Mi sento... beh, un po’ a disagio...";
			link.l1.go = "tieyasal_7";
		break;
		
		case "tieyasal_7":
			dialog.text = "La tua modestia ti fa onore, figliolo, ma questo non è il momento di far la verginella timida. Non lasciarti prendere dal timore o dal dubbio, ché il Signore tuo Dio ti precede per donarti la vittoria! Gettati in questa battaglia per amore dei tuoi cari, per tutti i cristiani... e se non per loro, fallo almeno per te stesso, poiché se quel demonio vincerà, tu finirai dannato come tutti gli altri.";
			link.l1 = "Immagino tu mi abbia convinto, padre. Tentenai se imbarcarmi o meno in questa crociata verso Tayasal, ma ora non ho più dubbi. In che modo puoi aiutarmi?";
			link.l1.go = "tieyasal_8";
		break;
		
		case "tieyasal_8":
			dialog.text = "Solo due uomini sapevano come arrivare a Tayasal: Alonso de Maldonado e Miguel Dichoso. Don Alonso è già passato a miglior vita. Quanto a Dichoso... mi dissero che l’hanno visto di recente a Sharptown, su Isla Tesoro. Forse bazzica ancora da quelle parti. Devi trovare Dichoso e convincerlo a farti da guida.\nChe sia col tintinnio dell’oro o con la minaccia della lama, fa’ sì che quest’uomo ti conduca a Tayasal. Lì troverai le porte dell’inferno, e lì dovrai richiuderle.";
			link.l1 = "E che mi dici degli uomini?";
			link.l1.go = "tieyasal_9";
		break;
		
		case "tieyasal_9":
			dialog.text = "L'ultima compagnia di soldati che ho avuto era sotto il comando di Alonso de Maldonado. Ahimè, non posso più radunare un'altra truppa di spagnoli, ho esaurito tutto il mio credito con la guarnigione locale. Dovrai cavartela con i tuoi uomini, figliolo. Ma ti aiuterò in tutto il resto, per quanto potrò.";
			link.l1 = "Che sorta di aiuto?";
			link.l1.go = "tieyasal_10";
		break;
		
		case "tieyasal_10":
			dialog.text = "Dobbiamo sfruttare ogni vantaggio in questa lotta, sia terreno che spirituale. Ho chiesto a Padre Adriano di raggiungermi qui in questa cappella fra cinque giorni. Porterà con sé amuleti sacri per te. Amuleti che possono aiutare i guerrieri di Cristo in battaglia. Ti fornirà anche ogni sorta di pozione. Quanto a me, accetta questa lama, figliolo.\nQuesta è una spada antica dei Cavalieri Templari, un'arma possente dei nostri antenati. Ancora affilata e splendente della benedizione della Chiesa. Solo i più grandi cavalieri hanno avuto l’onore di brandirla. Prendila, portala con orgoglio, e schiaccia i nemici della nostra Fede col nome di Gesù Cristo sulle labbra!";
			link.l1 = "Grazie! Questa spada è davvero straordinaria. Mi lascia senza parole...";
			link.l1.go = "tieyasal_11";
		break;
		
		case "tieyasal_11":
			sTemp = GetBestGeneratedItem("blade_32");
			GiveItem2Character(pchar, sTemp);
			sld = ItemsFromID(sTemp);
			sld.Balance = 2.0;
			sld.Weight = 4.5;
			Log_Info("You've received the Tanath");
			PlaySound("interface\important_item.wav");
			dialog.text = "Dio ti benedica, "+GetFullName(pchar)+", in this coming battle. I embower you with the Holy Cross. Almighty God, in whose hand victory rests and who also gave David miraculous strength to crush Goliath: humbly we pray your mercy to bless these weapons by your life-giving mercy; and grant your servant "+GetFullName(pchar)+" who wills to bear them, that he may use them freely and victoriously for defending Holy Mother Church against the attacks of all enemies visible and invisible. Through Christ our Lord. Amen.";
			link.l1 = "Amen!";
			link.l1.go = "tieyasal_12";
		break;
		
		case "tieyasal_12":
			dialog.text = "E ora va’, figlio mio. Che Dio vegli su di te, che non ti abbandoni mai — né nella tua ricerca, né sul tuo cammino, né in battaglia. Trova Miguel Dichoso e raggiungi Tayasal con il suo aiuto. Non dimenticare padre Adrian: ti fornirà amuleti e rimedi, tutto quel che ti servirà. Ora è il momento che io torni a Santiago. Addio, figlio mio. Vaya con Dios.";
			link.l1 = "Addio, padre Vincento...";
			link.l1.go = "tieyasal_13";
		break;
		
		case "tieyasal_13":
			DialogExit();
			NextDiag.CurrentNode = "first time";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Tieyasal_VinsentoGo", -1);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

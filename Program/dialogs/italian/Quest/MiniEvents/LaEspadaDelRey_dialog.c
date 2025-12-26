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
			dialog.text = "Cosa volete?";
			link.l1 = "Niente.";
			link.l1.go = "exit";
		break;
		
		case "LEDR_Gonsalo_1":
			if (pchar.sex == "man")
			{
				dialog.text = "Ehi, ragazzo! Vedo che sei un marinaio coraggioso, e probabilmente anche un bravo combattente. Mi aiuteresti a fare una sortita in un certo posto, eh?";
			}
			else
			{
				dialog.text = "Ehi, bella! Vedo che non sei una che si spaventa facilmente, visto che sei venuta qui. Non mi aiuteresti a fare una sortita in un certo posto, eh?";
			}
			link.l1 = "Suppongo che tu sia quel vecchio che cerca una guida verso la vecchia nave?";
			link.l1.go = "LEDR_Gonsalo_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LEDR_Gonsalo_2":
			dialog.text = "Heh... Quindi le voci viaggiano più veloci del vento. Sì, sono io. Gonzalo Peralta – l’unico sopravvissuto al naufragio della 'La Espada del Rey'.";
			link.l1 = "E io sono il capitano "+GetFullName(pchar)+". Vuoi dare di nuovo un'occhiata alla tua barca?";
			link.l1.go = "LEDR_Gonsalo_3";
		break;

		case "LEDR_Gonsalo_3":
			dialog.text = "Sì. Vedi, da un po' di tempo a questa parte mi tormenta sempre lo stesso incubo. Ma il punto non è nemmeno quello... Che tu ci creda o no, ogni mattina, appena l'incubo finisce, mi sveglio e... davanti a me c'è uno scheletro maledetto...";
			link.l1 = "In abiti indiani. Mi hanno detto che racconti questa storia a tutti.";
			link.l1.go = "LEDR_Gonsalo_4";
		break;

		case "LEDR_Gonsalo_4":
			dialog.text = "Una storiella? Eh... Magari fosse solo una storiella. Fino a un paio di mesi fa vivevo una vita tranquilla, come si addice a un vecchio marinaio in pensione. Ma ora quel sacco d’ossa mi viene a trovare ogni mattina, mi fissa, lancia un urlo straziante... accidenti, a qualsiasi nostromo si gelerebbe il sangue nelle vene... e poi si lancia all’attacco. E sai che ti dico? Ogni volta mi assale con sempre più furia. Ecco perché voglio arrivare presto alla nave: non mi lascia in pace la sensazione che là debba trovare qualcosa.";
			link.l1 = "Hmm... Bella faccenda. E cosa speri di trovare laggiù, dopo tutto questo tempo?";
			link.l1.go = "LEDR_Gonsalo_5";
		break;
		
		case "LEDR_Gonsalo_5":
			dialog.text = "Non lo so, capitano, non lo so... Ma qualcosa mi attira verso questa nave, come una vecchia barca in tempesta. Il mio sogno, quello scheletro e questa strana sensazione... Lo giuro sul mare, sono collegati in qualche modo. Solo che non riesco proprio a capire come.";
			link.l1 = "Che cosa succede esattamente nel tuo sogno? Ha qualcosa a che fare con gli indiani?";
			link.l1.go = "LEDR_Gonsalo_6";
			link.l2 = "Quindi, di notte hai delle visioni e al mattino combatti con uno scheletro? Forse il problema non è la nave, ma che dovresti andare da un medico. Non intendo assecondare la tua fantasia sfrenata. Cerca qualcun altro disposto a credere alle tue fandonie.";
			link.l2.go = "LEDR_Gonsalo_6_end";
		break;
		
		case "LEDR_Gonsalo_6_end":
			DialogExit();
			AddDialogExitQuestFunction("LEDR_End");
		break;
		
		case "LEDR_Gonsalo_6":
			dialog.text = "Eccome se c'entra, che mi venga un colpo... In quel sogno sono con l'equipaggio perduto  sulla 'La Espada del Rey'. Noi... saccheggiamo i villaggi dei caribi su Hispaniola, uccidiamo tutti senza distinzione - uomini, donne, bambini. Quelli che combattono, e persino quelli che cadono in ginocchio, implorando pietà. Incendiamo gli insediamenti uno dopo l'altro. Le frecce degli indigeni, le loro mazze contro di noi - come una tartana sfondata contro un galeone da guerra. I caribi, disperati, chiedono di trattare, e allora...";
			link.l1 = "Santo cielo! Quindi hai partecipato a quelle atrocità? Altro che aiuto, a te serve una corda al collo!";
			link.l1.go = "LEDR_Gonsalo_7";
		break;
		
		case "LEDR_Gonsalo_7":
			dialog.text = "No! No, maledizione, non è mai successo, capisci?! Non ho la minima idea del perché sogno tutto questo... ma giuro su tutti i santi, né io né la mia ciurma abbiamo mai preso parte a simili atrocità!";
			link.l1 = "Ti conviene davvero che sia così. Continua.";
			link.l1.go = "LEDR_Gonsalo_8";
		break;

		case "LEDR_Gonsalo_8":
			dialog.text = "I Caraibi chiesero di negoziare, e il capitano accettò. Li invitò tutti in una di quelle capanne che 'noi' avevamo conquistato. I capi arrivarono - una ventina di persone, non meno, guidati dalla loro regina - Anacaona. Solo che il capitano non entrò... nessuno di noi entrò. Appena l'ultimo dei capi fu dentro - la porta venne sbattuta e bloccata con delle travi. E poi... maledizione... diedero fuoco. Solo la regina fu risparmiata, ma non per molto. La costrinsero a guardare il suo popolo bruciare vivo... E poi la impiccarono a un albero.";
			link.l1 = "E succede ogni notte? Sempre lo stesso sogno, ancora e ancora? Sai, non mi stupirei se dopo tutto questo, quello scheletro fosse solo frutto della tua mente sconvolta...";
			link.l1.go = "LEDR_Gonsalo_9";
		break;

		case "LEDR_Gonsalo_9":
			dialog.text = "Non è ancora tutto. I caraibi sopravvissuti fuggirono a Cuba, trovarono lì il sostegno delle tribù locali e presto si riunirono in un unico esercito – sotto la guida di un certo capo. Atuey – sembra che si chiamasse così. Lo seguivano come l’ultima speranza. Ma li abbiamo massacrati tutti senza fatica. Atuey fu catturato e preparato per l’esecuzione. Quando lo legarono alla croce, pronti a bruciarlo, un monaco gli propose di accettare la vera fede – disse che così avrebbe alleviato le sue sofferenze e sarebbe andato in paradiso. Atuey chiese al monaco se il paradiso fosse aperto anche agli spagnoli. E quando quello rispose che per i buoni spagnoli, certo, il paradiso era aperto, il cacicco senza pensarci troppo replicò che allora lui preferiva l’inferno – pur di non condividere la dimora con gente tanto crudele. Poi disse ancora qualche frase nella sua lingua, e il rogo fu acceso. Non emise un solo suono quando le fiamme gli avvolsero la carne. Lo giuro sul mare, non vorrei mai vedere una cosa simile dal vivo. Il mio sogno finisce sempre allo stesso modo: il capitano siede immobile. Solo una candela accanto fuma, e lui continua a sfogliare un vecchio diario. Lentamente, come se ogni parola pesasse oro, e borbotta qualcosa tra sé e sé. Anche nel sogno, "+GetSexPhrase("ragazzo","ragazzina")+", capisco - è un segno. È ora di afferrare la spada, perché lui sta già attaccando\nAiutami a liberarmi di questo incubo, capitano. Vieni con me alla baia. Da solo non ci vado - ormai non ho più polvere nelle cartucce. Ma prima che tu risponda, devo avvertirti: non posso pagarti, altrimenti qui ci sarebbe già la fila di aiutanti. Quindi non mi resta che sperare nell’aiuto di un fratello di mare.";
			link.l1 = "E va bene. Se andare alla nave può aiutarti a liberarti di questi sogni e delle altre visioni, ti aiuterò. Sali a bordo. Appena finisco le mie faccende, andremo alla baia.";
			link.l1.go = "LEDR_Gonsalo_10";
		break;
		
		case "LEDR_Gonsalo_10":
			DialogExit();
			AddDialogExitQuestFunction("LEDR_1");
			AddQuestRecord("LEDR", "2");
			AddQuestUserData("LEDR", "sSex", GetSexPhrase("ся","ась"));
		break;
		
		case "LEDR_Gonsalo_11":
			if (GetHour() >= 7 && GetHour() <= 19)
			{
				dialog.text = "Eccolo... Un tempo era l'orgoglio della flotta mercantile spagnola, e ora è solo un mucchio di assi marce che a stento stanno insieme.";
				link.l1 = "Raramente si vede un gigante simile abbattuto - disteso sulla riva.   Come ha fatto ad arrivare qui?";
				link.l1.go = "LEDR_Gonsalo_12";
				link.l2 = "Allora diamo un'occhiata in giro. Forse riuscirai davvero a trovare qualcosa qui.";
				link.l2.go = "LEDR_Gonsalo_20_1";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "Non vorrei sembrare ingrato o codardo... ma adesso qui non mi sento a mio agio. Torniamo quando sorgerà il sole.";
				link.l1 = "Va bene, amico, come vuoi.";
				link.l1.go = "exit";
				NextDiag.TempNode = "LEDR_Gonsalo_11";
			}
		break;
		
		case "LEDR_Gonsalo_12":
			dialog.text = "Siamo salpati allora da Santiago e abbiamo puntato la rotta su Siviglia. Il carico era scarso, ma avevamo un passeggero d'eccezione: un pezzo grosso, il vescovo in persona. Alla ciurma, a dire il vero, quel viaggio non piaceva affatto... ma quando mai ci hanno ascoltato?\nAll’oceano, quella volta, non ci siamo mai arrivati. Vicino a Turks ci ha attaccato una brigantina pirata: veloce, agile, armata fino ai denti. Non erano degli sprovveduti, ma veri lupi di mare. Il capitano all’inizio voleva svignarsela — non gli andava di rischiare la vita del vescovo. Ma con quel vento era impossibile invertire la rotta, e da sud già si avvicinava una tempesta. Così non c’è stata scelta — è iniziata la battaglia.";
			link.l1 = "Trovarsi tra due fuochi non è certo una sorte invidiabile.   E poi cosa è successo?";
			link.l1.go = "LEDR_Gonsalo_13";
			AddCharacterExpToSkill(pchar, "Sailing", 200);
		break;

		case "LEDR_Gonsalo_13":
			dialog.text = "La battaglia non durò a lungo. Siamo riusciti a colpire loro l'albero di mezzana, ma anche i pirati non sono rimasti a guardare: una palla vagante ha tranciato la scotta del timone e, come per volontà del diavolo, la nave si è fermata con la prua rivolta verso la tempesta in arrivo. Si avvicinava così in fretta che i pirati – che gli venga un colpo al fiocco – hanno preferito darsela a gambe, nascondendosi in una delle baie di Turks. A noi non restava che una cosa: aspettare che la tempesta ci inghiottisse. Il capitano ha ordinato di ammainare le vele e sostituire la scotta, ma ormai era troppo tardi.";
			link.l1 = "Quindi la tempesta vi ha colti vicino a Turks, vi ha trascinati fin qui e alla fine vi ha sbattuti sulla riva?";
			link.l1.go = "LEDR_Gonsalo_14";
		break;

		case "LEDR_Gonsalo_14":
			dialog.text = "Era proprio così. A bordo regnava l’inferno. Il vento strappava le sartie, gli alberi cadevano uno dopo l’altro, fracassando il ponte e schiacciando la gente. Chi non aveva fatto in tempo a legarsi veniva spazzato fuori bordo, chi invece ci riusciva veniva schiacciato dai rottami. Nella stiva non era affatto meglio: cannoni, casse, palle di cannone volavano da una parte all’altra come demoni, distruggendo tutto sul loro cammino. Quando alla fine siamo stati sbattuti a riva, ero privo di sensi. Mi sono ripreso già sulla sabbia. Mi ha trovato il nostromo Sergio. Con lui c’erano altri due.";
			link.l1 = "Non è molto, per una nave così grande.";
			link.l1.go = "LEDR_Gonsalo_15";
		break;

		case "LEDR_Gonsalo_15":
			dialog.text = "Ah, capitano... Quanti cadaveri c’erano laggiù... Abbiamo capito subito: non si poteva restare. Le onde potevano portar via sia la nave che noi dietro di lei. Lì vicino abbiamo trovato una grotta – ci siamo addormentati sfiniti appena toccata terra. Quando mi sono svegliato, nella grotta non c’erano né Sergio, né quei due\nHo perlustrato tutta la spiaggia, ma giuro su Dio, non c’erano. Salire sulla nave da solo era impossibile per me, così decisi di addentrarmi nell’isola. Così sono arrivato a Sharptown, dove per la mia ingenuità ho combinato guai\nVolevo sapere almeno qualcosa dei sopravvissuti, ho cominciato a raccontare a tutti quello che ci era successo. Ma a quei furfanti non interessavo né io né l’equipaggio, ma solo il bottino che potevano arraffare dalla nave. La voce si è sparsa in fretta per tutta l’isola e orde di quei ladroni si sono precipitate laggiù.";
			link.l1 = "Quindi, il destino di quelle persone ti è ancora sconosciuto?";
			link.l1.go = "LEDR_Gonsalo_16";
		break;

		case "LEDR_Gonsalo_16":
			dialog.text = "Era troppo pericoloso tornare sulla nave. Chi ha rischiato di andarci in cerca di bottino poteva non riuscire a dividere il malloppo e sparare a chiunque si trovasse vicino... per caso. O forse — nemmeno per caso\nLo giuro sul mare, sono rimasto in taverna per un’intera settimana, interrogando chiunque fosse stato nella baia. Ma nessuno aveva sentito parlare né dei miei ragazzi, né di quello che era successo loro\nAlla fine mi sono rassegnato all’idea: sembra che io sia l’unico ad essere sopravvissuto a quella maledetta tempesta. Semplicemente, la sorte è stata più clemente con me che con gli altri. O forse... è tutto merito dell’amuleto che un tempo mi diede il giovane, allora ancora capitano, Eugenio de la Torre. L’ho sempre avuto con me. E, maledizione, sembra proprio che portasse davvero fortuna.";
			link.l1 = "E dove si trova adesso? Sembra che dagli scheletri non protegga, eh...";
			link.l1.go = "LEDR_Gonsalo_17";
		break;

		case "LEDR_Gonsalo_17":
			dialog.text = "Me lo hanno strappato dal collo mentre stavamo sistemando la parte superiore del pozzo nel mio cortile. Un tronco mi ha colpito al collo e l’amuleto è caduto in acqua. Il pozzo era già pieno e nessuno si sarebbe messo a svuotarlo per un semplice gingillo.";
			link.l1 = "E da quel momento hai iniziato ad avere degli incubi?";
			link.l1.go = "LEDR_Gonsalo_18";
		break;

		case "LEDR_Gonsalo_18":
			dialog.text = "Mille diavoli! Non ci avevo mai pensato, ma è proprio così! Appena abbiamo finito di costruire il pozzo, sono iniziati gli incubi.";
			link.l1 = "Una coincidenza curiosa. Bene, ora sei qui, proprio come volevi. E adesso, cosa pensi di fare?";
			link.l1.go = "LEDR_Gonsalo_19";
		break;

		case "LEDR_Gonsalo_19":
			dialog.text = "Non so, capitano... Non so. Diamo prima un'occhiata in giro – la sensazione che debba trovare qualcosa qui è solo aumentata.";
			link.l1 = "Bene. Spero che non siamo venuti qui per niente.";
			link.l1.go = "LEDR_Gonsalo_20";
		break;
		
		case "LEDR_Gonsalo_20":
			DialogExit();
			AddDialogExitQuestFunction("LEDR_3");
		break;
		
		case "LEDR_Gonsalo_20_1":
			DialogExit();
			AddDialogExitQuestFunction("LEDR_3");
			pchar.questTemp.LEDR_NoStory = true;
		break;
		
		case "LEDR_Gonsalo_21":
			dialog.text = "Ascolta... Questa sensazione si fa sempre più forte. È come se fossi a un passo da qualcosa che devo trovare. Devo salire a bordo della nave. Lo giuro sul mare, lì c'è qualcosa che mi spiegherà perché quello scheletro maledetto non mi lascia mai in pace.";
			link.l1 = "Forse allora non sei venuto qui per caso? Hai nascosto qualcosa di prezioso sulla nave, e ora hai deciso di tornare per riprenderti il tuo bottino?";
			link.l1.go = "LEDR_Gonsalo_22";
		break;

		case "LEDR_Gonsalo_22":
			dialog.text = "Che sciocchezze sono queste? Pensi davvero che sarei venuto fin qui, attraversando tutto l’arcipelago, solo per qualche doblone dopo quarant’anni? Se solo ti fosse capitato di vedere quello scheletro, certi pensieri не ti sarebbero mai venuti in mente.";
			link.l1 = "Va bene, va bene, calmati. E in che modo pensi di salire a bordo della nave?";
			link.l1.go = "LEDR_Gonsalo_23";
		break;

		case "LEDR_Gonsalo_23":
			dialog.text = "Sul ponte di poppa c'è una porta nascosta. Il capitano l'ha fatta lui stesso, nel caso l'abbordaggio non andasse a nostro favore. Per tutti i fulmini, da solo non riuscirei mai a trascinare il mio vecchio corpo lì dentro, ma in due...";
			link.l1 = "E va bene, mostrami la strada e finiamo questa storia.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LEDR_5");
		break;
		
		case "LEDR_Gonsalo_24":
			DelLandQuestMark(npchar);
			dialog.text = "Una palla di cannone nel collo, che macello! Per fortuna questi non erano feroci come quello che mi appare ogni mattina. Allora, adesso mi credi?";
			link.l1 = "Dopo una scena del genere, è difficile *non* crederti. Stai bene?";
			link.l1.go = "LEDR_Gonsalo_24_1";
		break;

		case "LEDR_Gonsalo_24_1":
			dialog.text = "Credo di sì. Maledetti non-morti... le gambe mi hanno ceduto come alberi spezzati.";
			link.l1 = "Beh, se sei intero, basta stare seduto. Dammi la mano, ti aiuto ad alzarti.";
			link.l1.go = "LEDR_Gonsalo_24_2";
		break;

		case "LEDR_Gonsalo_24_2":
			CharacterTurnByChr(npchar, CharacterFromID("blaze"));
			dialog.text = "...";
			link.l1 = "Molto meglio. A quanto pare, non siamo i primi a sapere come entrare qui.";
			link.l1.go = "LEDR_Gonsalo_25";
			LAi_Fade("LEDR_GonsaloStay", "");
		break;

		case "LEDR_Gonsalo_25":
			dialog.text = "Sembra che siano i miei uomini. Quelli che sono sopravvissuti alla tempesta... Ho riconosciuto il gilet di Sergio... o meglio, quello che ne resta. Quindi sono tornati – forse per cercare i superstiti, o per seppellire i morti. Ma sembra che siano stati massacrati da queste stesse creature.";
			link.l1 = "È sorprendente che siano rimasti solo dei brandelli del gilet. E nient'altro.";
			link.l1.go = "LEDR_Gonsalo_26";
		break;

		case "LEDR_Gonsalo_26":
			if(CheckAttribute(pchar, "questTemp.LEDR_NoStory"))
			{
			dialog.text = "Non è rimasta nemmeno l’ombra della tonaca del nostro passeggero – il vescovo. A giudicare dalla chiave stretta nella mano, quel poveraccio laggiù dev’essere lui. Non si separava mai da quella chiave, nemmeno per un secondo. A quanto pare, non è stato più fortunato degli altri. Per il mare – questi non-morti non vagavano qui per caso. Qualcosa li trattiene... o stanno sorvegliando qualcosa.";
			DeleteAttribute(pchar, "LEDR_NoStory");
			}
			else
			{
			dialog.text = "Non è rimasta nemmeno l’ombra della tonaca del vescovo. A giudicare dalla chiave stretta nella mano, quel poveraccio laggiù dev’essere lui. Non si separava mai da quella chiave, nemmeno per un secondo. A quanto pare, non è stato più fortunato degli altri. Per il mare – questi non-morti non vagavano qui per caso. Qualcosa li trattiene... o stanno sorvegliando qualcosa.";
			}
			link.l1 = "Anch’io ho la sensazione che dobbiamo trovare qualcosa qui. Finimola in fretta — non ho nessuna voglia di restare qui più del necessario.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LEDR_8");
		break;
		
		case "LEDR_Gonsalo_27":
			dialog.text = "Allora, capitano, hai trovato qualcosa?";
			link.l1 = "Sembra che fosse il baule del vescovo. Io ho trovat"+GetSexPhrase("ёл","ла")+" c'è qualcosa lì dentro. Dai un'occhiata.";
			link.l1.go = "LEDR_Gonsalo_28";
		break;

		case "LEDR_Gonsalo_28":
			dialog.text = "Velázquez... Maledizione... Ho visto questo diario nei miei sogni! Era proprio lui che sfogliava il capitano, prima che...";
			link.l1 = "...";
			link.l1.go = "LEDR_Gonsalo_29";
		break;

		case "LEDR_Gonsalo_29":
			dialog.text = "Diavolo, sembra che mi bruci le mani!";
			link.l1 = "Ti brucia le mani? Dai, su, è solo un vecchio diario. O credi davvero che ci sia qualche forza oscura dentro?";
			link.l1.go = "LEDR_Gonsalo_30";
		break;

		case "LEDR_Gonsalo_30":
			dialog.text = "Giuro su tutti i santi, non sto scherzando! Questo dannato diario sembra bruciare tra le mie mani. Bisogna distruggerlo! Strapparlo, bruciarlo, affogarlo – qualsiasi cosa! Anzi, no... Meglio bruciarlo. Sì, proprio bruciarlo, così che non ne resti nemmeno la cenere!";
			link.l1 = "Come vuoi. Allora andiamo a riva, accendiamo un fuoco e mandiamo questa cronaca di misfatti tra le fiamme.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LEDR_10");
		break;
		
		case "LEDR_Gonsalo_31":
			dialog.text = "Ecco, è tutto finito... Come se un'ancora mi fosse caduta dal cuore.";
			link.l1 = "Pensi che ora sia tutto finito?";
			link.l1.go = "LEDR_Gonsalo_32";
			TakeItemFromCharacter(pchar, "LEDR_book");
		break;

		case "LEDR_Gonsalo_32":
			dialog.text = "Chi lo sa... Ma giuro sul mare, da tanto non respiravo così facilmente. Come se un vecchio debito fosse finalmente saldato. Eppure... Avrei preferito non aver mai visto quel dannato diario. E non sapere cosa c'era scritto.";
			link.l1 = "Non c’è da stupirsi che tu abbia fatto un sogno del genere. Anche se non hai preso parte a tutto questo, sei l’unico tra i vivi ad avere almeno qualche legame con il diario.";
			link.l1.go = "LEDR_Gonsalo_33";
		break;
		
		case "LEDR_Gonsalo_33":
			dialog.text = "Né l’oro, né la fede possono giustificare ciò che hanno fatto gli uomini agli ordini di Velasquez. E sono contento che tutto ciò che poteva ricordarlo sia andato in fiamme. Cose simili non devono mai попасть в руки di chi decidesse di seguirne l’esempio.";
			link.l1 = "Velázquez è solo uno dei tanti. Chissà quanti altri diari simili circolano ancora per la vecchia Europa, alimentando l’avidità e l’impunità dei nuovi conquistatori? C’è una consolazione: questo non avvelenerà più nessuno. A proposito, nel baule del vescovo c’era non solo il diario, ma anche una bella scorta di dobloni – trecento in tutto. La metà di questi ti spetta di diritto.";
			link.l1.go = "LEDR_Gonsalo_34_share";
			link.l2 = "Velázquez ha pagato per i suoi peccati, e chiunque decida di seguire la sua strada farà la stessa fine. Prima o poi, il destino ricompensa ognuno secondo i propri meriti.";
			link.l2.go = "LEDR_Gonsalo_34_silence";
		break;
		
		case "LEDR_Gonsalo_34_share":
			dialog.text = "Se è così, non mi tiro indietro. Tutti hanno bisogno di soldi, ma io ora più che mai. Ormai nessuno mi prenderà più come marinaio su una nave – sono diventato vecchio. Quindi grazie, capitano, che non mi hai mandato via."+GetSexPhrase("ся","ась")+", come gli altri.";
			link.l1 = "Devo ammettere, all'inizio la tua storia mi è sembrata il delirio di un pazzo. Ma la raccontavi con tanta convinzione che, volente o nolente, finisci per crederci. Eppure, la comparsa di quegli zombi indigeni mi ha colto di sorpresa.";
			link.l1.go = "LEDR_Gonsalo_35_1";
			link.l2 = "Ho solo deciso di vedere se sei sano di mente. Capisci, non è così facile credere a certe storie.";
			link.l2.go = "LEDR_Gonsalo_35_2";
			RemoveDublonsFromPCharTotal(150);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			npchar.quest.LEDR_share = true;
		break;
		
		case "LEDR_Gonsalo_34_silence":
			dialog.text = "Vorrei crederci... Ma ti giuro sul mare, ho visto troppa gente a cui la sorte sorrideva, nonostante tutte le loro malefatte. Forse il conto arriverà anche per loro – ma solo laggiù, in quel dannato calderone. E a te grazie, capitano. Per non avermi voltato le spalle, per avermi ascoltato e accompagnato. Sai, questo vale molto.";
			link.l1 = "Devo ammettere, all'inizio la tua storia mi è sembrata il delirio di un pazzo. Ma la raccontavi con tanta convinzione che, volente o nolente, finisci per crederci. Eppure, l'apparizione di quegli zombi indigeni mi ha colto di sorpresa.";
			link.l1.go = "LEDR_Gonsalo_35_1";
			link.l2 = "Ho solo deciso di vedere se sei impazzito. Capisci, non è così facile credere a storie del genere.";
			link.l2.go = "LEDR_Gonsalo_35_2";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
		break;

		case "LEDR_Gonsalo_35_1":
			dialog.text = "Ora sai cosa ho provato quando ho visto quei non-morti per la prima volta. Spero che sia finita per sempre... Altrimenti, dubito che sopravvivrò a un altro incontro del genere.";
			link.l1 = "Bene, visto che qui abbiamo finito, è ora di andarcene. Sali a bordo, ti lascerò al porto di Sharptown.";
			link.l1.go = "LEDR_Gonsalo_36";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "LEDR_Gonsalo_35_2":
			dialog.text = "Ora sai cosa ho provato quando ho visto per la prima volta quei non-morti. Spero che sia finita per sempre... Altrimenti, dubito di sopravvivere a un altro incontro del genere.";
			link.l1 = "Bene, visto che qui abbiamo finito, è ora di andarcene. Sali a bordo, ti lascio al porto di Sharptown.";
			link.l1.go = "LEDR_Gonsalo_36";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;
		
		case "LEDR_Gonsalo_36":
			DialogExit();
			AddDialogExitQuestFunction("LEDR_12");
		break;
		
		case "LEDR_Gonsalo_37":
			dialog.text = "Ancora una volta, grazie, capitano "+GetFullName(pchar)+". Lo giuro sul mare, quella strana sensazione è sparita, e spero che si sia portata via anche il suo dannato sacco d’ossa. Che ne dici, ci facciamo un bicchiere?";
			link.l1 = "Ti ringrazio per l’invito, Gonzalo, ma ho ancora un sacco di cose da fare. Magari un’altra volta. Bevi anche per me.";
			link.l1.go = "LEDR_Gonsalo_38";
		break;
		
		case "LEDR_Gonsalo_38":
			if (CheckAttribute(npchar, "quest.LEDR_share"))
			{
				dialog.text = "Capisco. Ma lascia che ti dica una cosa, capitano: dopo tutto quello che abbiamo passato insieme, non posso semplicemente andarmene senza ringraziarti. Non sarebbe da persone per bene. Tieni, prendi. Da giovane ho inseguito tesori più di una volta, te lo giuro sul mare. Ma ora la salute non è più quella, e anche la schiena mi tradisce. Tu invece sei giovane, un vero lupo di mare. Lo troverai senza difficoltà. Buona fortuna, "+GetFullName(pchar)+", vento in poppa e sette piedi sotto la chiglia.";
				link.l1 = "Grazie, Gonzalo. Buona fortuna anche a te, addio.";
				AddMapPart();
			}
			else
			{
				dialog.text = "Ebbene, è arrivato il momento di salutarci. Che il vento ti sia favorevole e sette piedi d’acqua sotto la chiglia, capitano "+GetFullName(pchar)+"!";
				link.l1 = "Addio, Gonzalo.";
			}
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LEDR_14");
		break;
		
		
		
	}
}
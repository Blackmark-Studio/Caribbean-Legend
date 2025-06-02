// Дональд Гринспи - лидер нарвалов
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Cosa? Che vuoi, forestiero?";
				link.l1 = TimeGreeting()+". Il mio nome è "+GetFullName(pchar)+"Volevo incontrare il capo del clan.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+" ! Desideri qualcosa?";
				link.l5 = "Volevo solo salutarti. Ci si vede!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Ora mi conosci. Il mio nome è Donald Greenspen e non far arrabbiare né me né la mia ciurma. E non provare a mettere piede sulla 'San Gabriel' senza la parola d’ordine. La bottega è aperta a tutti, il commercio serve a chiunque. Hai domande?";
			link.l2 = "No, ho capito. Ci vediamo.";
			link.l2.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
	// ----------------------------------после разгрома Чада и Мэри на Каролине---------------------------
		case "shark":
			dialog.text = "Che affari avete con me?";
			link.l1 = "Una faccenda assai spiacevole, Donald. Stanotte hanno attentato alla vita di Steven. I combattenti del tuo clan c’erano in mezzo.";
			link.l1.go = "shark_1";
		break;
		
		case "shark_1":
			dialog.text = "Non ne sarei così sicuro. Perché credi che fossero miei uomini?";
			link.l1 = "Perché c’ero anch’io. Sappiamo distinguere tra la tua ciurma, i pirati e i Rivados. Era Mary Casper a guidare il gruppo, insieme a Chad Kapper. Ti serve davvero qualche altra prova?";
			link.l1.go = "shark_2";
		break;
		
		case "shark_2":
			dialog.text = "Posso solo assicurarti che né io né i miei uomini abbiamo nulla a che fare con questa faccenda.";
			link.l1 = "Dovrai assicurarlo all'ammiraglio, e non sarà affatto facile. Dodson è furente con tutti i Narvali dopo l’assalto. Ha intenzione di dichiararvi guerra: smetterà di fornirvi viveri e farà fuoco sui tuoi uomini ogni volta che ne avrà mezzo. E non sono solo chiacchiere.";
			link.l1.go = "shark_3";
		break;
		
		case "shark_3":
			dialog.text = "Spero che quell’ammiraglio sappia bene cosa sta per fare. Dubita forse che i miei uomini sappiano sparare altrettanto bene?";
			link.l1 = "Penso proprio di sì. È pronto a trasformare la 'San Augustine' in una fortezza e resistere finché non morirete tutti di fame. E poi, Dodson parlerà coi Rivados per proporre un’alleanza. Non avrete alcuna speranza contro l’ammiraglio e i Rivados assieme.";
			link.l1.go = "shark_4";
		break;
		
		case "shark_4":
			dialog.text = "Malasorte! Ma noi non c'entriamo un accidente con questa faccenda! Perché tutto il clan deve pagare per le follie di quella sciroccata di Mary e una manica di canaglie della mia ciurma?\nE poi, ragioniamo: uccidendo Marlow, Dodson stesso ha provocato Mary e i miei uomini. È proprio questo che succede quando si compiono simili bassezze.";
			link.l1 = "Non capisci un accidente. Ti hanno fregato. Perché sei così sicuro che sia stato Dodson ad ammazzare Alan? In verità, lui crede che sia stato tu a farlo, per soffiargli il posto...";
			link.l1.go = "shark_5";
		break;
		
		case "shark_5":
			dialog.text = "Non me ne frega un accidente di quel che pensa lui. Tutte le prove sono contro di lui. Solo lui e i suoi uomini potevano entrare nella prigione. Alan era nelle sue grinfie. La Rossa Mary mi ha detto un sacco di cose. Prima che Alan venisse ammazzato, Dodson è venuto di persona alla prigione, e non lo fa quasi mai.";
			link.l1 = "Hai visto la sua dipartita?";
			link.l1.go = "shark_6";
		break;
		
		case "shark_6":
			dialog.text = "Fandonie! Certo che no.";
			link.l1 = "E anche Chimiset. Sì-sì, lo stregone dei Rivados che sedeva vicino ad Alan. Pure lui è stato assassinato di recente. Io ero nella prigione il giorno prima che morisse e ci ho parlato. Milrow è stato fatto fuori da Chad Kapper, il nostromo dello Squalo.";
			link.l1.go = "shark_7";
		break;
		
		case "shark_7":
			dialog.text = "È vero?";
			link.l1 = "Pensa un po': Chimiset non si curava del tuo rapporto con l’ammiraglio. Non aveva motivo di mentire. Quel vecchio stregone temeva Chad, credeva che sarebbe toccato a lui il prossimo. Aveva ragione, Chad lo ha fatto fuori appena ha scoperto che l’ammiraglio voleva dargli la libertà.";
			link.l1.go = "shark_8";
		break;
		
		case "shark_8":
			dialog.text = "Ma perché Kapper voleva la morte di Alan?";
			link.l1 = "Maledizione, non capisci davvero? Ti ho già detto che Kapper tramava con la Rossa Mary. Voleva prendere il posto dello Squalo e ha messo in atto un piano astuto per riuscirci. Ammazzare Alan Milrow e spargere voci sulla complicità dello Squalo nella sua morte ha reso il clan dei Narvali ostile all'ammiraglio...";
			link.l1.go = "shark_9";
		break;
		
		case "shark_9":
			dialog.text = "";
			link.l1 = "La sciocca Mary s’è fidata di lui e s’è schierata col vero assassino del suo compare. Hanno convinto qualche Narvalo a unirsi alla loro causa, per Mary dev’esser stato un gioco da ragazzi. Poi han messo in piedi un assalto contro l’ammiraglio nella cabina di Fazio, costringendolo a scrivere un invito per l’ammiraglio...";
			link.l1.go = "shark_10";
		break;
		
		case "shark_10":
			dialog.text = "";
			link.l1 = "Ho una lettera da Fazio che spiega tutto. Chimiset è stato fatto fuori da Chad, che temeva la sua lingua lunga. Stava collaborando coi Narvali, e i Rivados saranno ben lieti di saperlo quando parleranno con Squalo. Con questa lettera potremo dimostrare facilmente a Eddie il Nero che Chad è diventato uno dei vostri, senza ombra di dubbio.";
			link.l1.go = "shark_11";
		break;
		
		case "shark_11":
			dialog.text = "Hm. Hai tutte le carte in mano, che ci fai qui allora? Vuoi qualcosa da me, vero?";
			link.l1 = "Lo credo davvero. Perché sono convinto che sia tutta una macchinazione di Chad e che tu non c’entri affatto. Chad ha tradito Mary, lei ha chiamato le sue amiche del tuo clan per darle man forte, e il resto è venuto da sé. Almeno, non ho trovato prove contro di te o qualche altro Narvalo...";
			link.l1.go = "shark_12";
		break;
		
		case "shark_12":
			dialog.text = "";
			link.l1 = "Ma ciò non vuol dire che non ci siano altri cospiratori in giro. Voglio che tu li scovi. Così, forse, riusciremo a sistemare le cose senza spargimenti di sangue.";
			link.l1.go = "shark_13";
		break;
		
		case "shark_13":
			dialog.text = "Ti ho già detto che nessun altro dei miei uomini ne faceva parte. Dopo la morte di Marlow, Mary ha praticamente abbandonato il clan e si è rinchiusa nella sua cabina. In verità, non so proprio come abbia fatto a convincere altri a seguirla, ma pare ci sia riuscita. Ti giuro che né io né altri del mio clan stiamo tramando contro l’ammiraglio. \nAbbiamo già perso troppi uomini, non vogliamo cacciarci in nuovi guai ora. Non temo un attacco dell’ammiraglio, nemmeno se si alleasse coi Rivados. I Narvali sono guerrieri veri, e lo dimostreremo nella nostra ultima battaglia. Ma sarebbe inutile. \nAbbiamo già deciso di mantenere la pace con l’ammiraglio. I Rivados sono un altro discorso: non trattiamo con i Negri. Sono pronto a scusarmi di persona con l’ammiraglio, chiedere perdono per i miei sospetti dovuti alla morte di Milrow e per l’attacco alla sua vita. Giurerò sulla Bibbia, se serve dimostrare la mia sincerità. Tu e Dodson siete d’accordo con ciò?";
			link.l1 = "Sì, sono io. Sei proprio certo che i tuoi uomini non abbiano preparato qualche trappola, eh?";
			link.l1.go = "shark_14";
		break;
		
		case "shark_14":
			dialog.text = "Assolutamente. Avviserò il mio clan del vero assassino di Alan Milrow. Il rapporto dei miei uomini con l’ammiraglio cambierà all’istante, te lo giuro. Dimmi, pensi che servirà spargere altro sangue dopo?";
			link.l1 = "No, non accadrà. Sono qui per impedirlo. Ho fiducia in te, Donald, e cercherò di convincere Squalo. Ho ancora qualche asso nella manica... A presto, Donald!";
			link.l1.go = "shark_15";
		break;
		
		case "shark_15":
			DialogExit();
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "narval"; // ноду Акуле
			AddQuestRecord("SharkHunt", "26");
			NextDiag.CurrentNode = "narval_wait";
		break;
		
		case "narval_wait":
			dialog.text = "Hai già parlato con l’ammiraglio? Novità in vista?";
			link.l1 = "Sono in mezzo a qualcosa. Ci vediamo più tardi...";
			link.l1.go = "exit";
			NextDiag.TempNode = "narval_wait";
		break;
		
		case "shark_16":
			dialog.text = "Hai già parlato con l’ammiraglio? Novità in vista?";
			link.l1 = "Sì, l'ho fatto. Le tue scuse sono accettate, la tua accusa è ritirata. E c'è di più, Squalo ti invita a incontrarlo per parlare dei termini di un futuro accordo pacifico tra Narvali e pirati.";
			link.l1.go = "shark_17";
		break;
		
		case "shark_17":
			dialog.text = "A dire il vero, non me l’aspettavo... Questa sì che è una gran notizia. Forse potremo persino rivedere i prezzi delle provviste per il nostro clan e pensare a una nuova politica verso i Rivados.";
			link.l1 = "Questo riguarda solo te e l'ammiraglio.";
			link.l1.go = "shark_18";
		break;
		
		case "shark_18":
			dialog.text = "Sì, certo. Hai reso un grande servizio al clan Narvalo, impedendo uno spargimento di sangue insensato e forse persino la completa rovina dei miei uomini. Prendi questo moschetto da torre come segno della mia gratitudine, non ne troverai un altro simile in queste acque.\nE poi, ora hai il permesso di visitare le nostre zone proibite, come fossi uno di noi.";
			link.l1 = "Grazie! Addio per ora, ho un mare di faccende da sbrigare.";
			link.l1.go = "shark_19";
		break;
		
		case "shark_19":
			GiveItem2Character(pchar, "mushket6"); 
			Log_Info("You have received a tower mousqueton");
			PlaySound("interface\important_item.wav");
			dialog.text = "Buona fortuna. Vieni da me se ti servirà qualche chiarimento.";
			link.l1 = "Ricevuto. Ci si vede!";
			link.l1.go = "exit";
			CloseQuestHeader("SharkHunt");
			bDisableFastReload = false; // belamour legendary edition
			pchar.questTemp.LSC.nrv_friend = "true"; //флаг на проход по кораблям нарвалов
			NextDiag.TempNode = "grinspy_wait";
			for (i=1; i<=6; i++)
			{
				sld = CharacterFromID("NarvalSold_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("NarvalProt_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			AddSimpleRumourCityTip("They say that you are a friend of Donald, Greenspen, the leader of Narwhals. Well, Rivados hate you now...", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("They say that you are Narwhal now. Or do you serve under admiral's command? I don't get it...", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("I've heard that you have made peace between admiral and Narwhals. Hm, Rivados must be insane about that...", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("So Chad Kapper was a murderer of Alan Milrow! That is surprising!", "LostShipsCity", 5, 2, "LSC", "");
		break;
		
		case "grinspy_wait": // стал другом
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "Ohé! "+GetFullName(pchar)+"! Tu sei... no, non può essere! Sei vivo?!";
				link.l1 = "I racconti sulla mia morte erano un po’ esagerati, Donald. Ahah, lieto di rivederti!";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			dialog.text = "A-ah, amico mio "+GetFullName(pchar)+"Ti serve qualcosa?";
			link.l1 = "No, non mi pare. Volevo solo salutarti.";
			link.l1.go = "exit";
			NextDiag.TempNode = "grinspy_wait";
		break;
		
		case "negotiations":
			dialog.text = "Che affari hai da propormi?";
			link.l1 = "Una storia assai spiacevole, Donald. Hanno tentato d’ammazzare Steven. Gente del tuo clan vi ha preso parte.";
			link.l1.go = "negotiations_1";
		break;
		
		case "negotiations_1":
			dialog.text = "Non ne sono così sicuro. Perché pensi che i miei uomini c’entrino qualcosa?";
			link.l1 = "Perché personalmente ne ho fatti fuori alcuni insieme a Chad Kapper, il nostromo dell’ammiraglio, colpevole di tutto questo casino. Da solo non ce l’avrebbe mai fatta, quindi i tuoi uomini gli hanno dato una gran mano. L’ammiraglio lo sa, e credimi, è furibondo.";
			link.l1.go = "negotiations_2";
		break;
		
		case "negotiations_2":
			dialog.text = "I miei uomini? Chi, precisamente, puoi farne i nomi?";
			link.l1 = "Non si sono nemmeno presentati. Sparavano e menavano di spada come forsennati. Gente vostra, senza giudizio. Pronti ad attaccare pure uno dei loro, figurarsi me o l’ammiraglio, ma tentare d’ammazzare una ragazza? Che razza di feccia...";
			link.l1.go = "negotiations_3";
		break;
		
		case "negotiations_3":
			dialog.text = "Hm. Di chi stai parlando?";
			if (pchar.questTemp.LSC.Mary == "alive")
			{
				link.l1 = "Di chi sto parlando? Dico dell’attacco a Mary la Rossa. Due Narvali hanno tentato d’ammazzarla. Sono arrivato alla sua cabina proprio nel momento cruciale, per pura fortuna. Se fossi arrivato dopo, l’avrebbero fatta fuori. Non ho chiesto i loro nomi, mi spiace, non c’era tempo per le cortesie, ma Mary ha giurato che erano Narvali.";
				link.l1.go = "negotiations_4";
			}
			else
			{
				link.l1 = "Di chi parlo? Parlo dell’agguato a Mary la Rossa e di quei due Narvali che l’hanno fatta fuori."link.l1.go ="negoziazioni_6";
			}
		break;
		
		case "negotiations_4":
			dialog.text = "Cosa? Perché non me l'ha detto?! Sarei intervenuto all'istante!";
			link.l1 = "Ultimamente aveva paura persino di uscire dalla sua cabina. Avete litigato da poco, quindi perché mai dovrebbe correre da te a chiedere aiuto?";
			link.l1.go = "negotiations_5";
		break;
		
		case "negotiations_5":
			dialog.text = "Non ho litigato con lei! Pretendeva l’impossibile da me, abbiamo avuto una discussione accesa e l’ho mandata via. Ma non significa che io...";
			link.l1 = "D’accordo, come vuoi. In fondo, ormai tutti i guai sono risolti. Ma tra i tuoi uomini ci son canaglie, questo è certo.";
			link.l1.go = "negotiations_7";
		break;
		
		case "negotiations_6":
			dialog.text = "Cosa? È stata uccisa dai Narvali? Perché mai?";
			link.l1 = "Per ordine di Chad Kapper, Donald. Sapeva troppo e non voleva aiutare Chad. E ora la povera ragazza è morta!";
			link.l1.go = "negotiations_7";
		break;
		
		case "negotiations_7":
			dialog.text = "Giuro, non ne sapevo nulla!";
			link.l1 = "Certo, non l’hai fatto… Ma parliamo dell’ammiraglio. Chad Kapper ha orchestrato il tentativo e i tuoi uomini gli hanno dato man forte. Han provato ad avvelenare Dodson e io per un soffio l’ho impedito.";
			link.l1.go = "negotiations_8";
		break;
		
		case "negotiations_8":
			dialog.text = "Non ho ordinato nulla del genere. Dodson sa bene che non appoggio la politica del defunto Alan e credo che un compromesso magro valga meglio d’una causa grassa.";
			link.l1 = "Dovrai convincere l’ammiraglio, e non sarà una passeggiata. Dodson è furibondo con tutti i Narvali dopo quel tentato colpo. Sta per dichiararti guerra.";
			link.l1.go = "negotiations_9";
		break;
		
		case "negotiations_9":
			dialog.text = "Spero che l’ammiraglio capisca bene quel che fa. Pensa forse che i miei uomini non sappiano rispondere al fuoco?";
			link.l1 = "Proprio così. Crede che la tua ciurma sia una marmaglia di fuorilegge e che vada spazzata via prima che cominciate a sgozzare tutti. Inoltre, abbiamo legami forti coi Rivados. Mi basta scambiare due parole con Eddie il Nero e proporgli un’alleanza. Contro tutti noi, non avrai scampo.";
			link.l1.go = "negotiations_10";
		break;
		
		case "negotiations_10":
			if (pchar.questTemp.LSC.Mary == "alive") sTemp = "Call Red Mary if you don't believe me and ask her! She will confirm.";
			else sTemp = "I have a letter from Chad to Mary which proves everything.";
			dialog.text = "Per tutti i diavoli! Perché tutta la ciurma deve pagare per le follie di qualche idiota? Non credere che io abbia paura. Siamo guerrieri, e lo dimostreremo anche nell’ultima battaglia. Ma io voglio giustizia. In realtà, è l’ammiraglio il responsabile per la morte di Alan Milrow nella prigione.";
			link.l1 = "Come puoi essere tu il capo, Donald... Non sai nulla né di Mary né di Alan. Chad Kapper l’ha fatto fuori."+sTemp+"   Lo ha fatto per rendere i Narvali ostili verso l’ammiraglio e trascinarne alcuni dalla sua parte.";
			link.l1.go = "negotiations_11";
		break;
		
		case "negotiations_11":
			dialog.text = "Capisco. Va bene. Parliamo in altro modo, allora. Sei qui per qualche motivo, vero? Che cosa cerchi?";
			link.l1 = "Non voglio un bagno di sangue sull’Isola Giustizia. Non voglio che la gente ci lasci la pelle. Non mi piace l’idea di sterminare tutti i Narvali, anche se ti assicuro che noi e i Rivados potremmo farlo. E poi credo che non tutto il clan debba pagare per le malefatte di qualche malnato...";
			link.l1.go = "negotiations_12";
		break;
		
		case "negotiations_12":
			dialog.text = "";
			link.l1 = "Ma il mio voto non basterà – dovresti assicurare ufficialmente all'ammiraglio che il tentativo non è stato approvato da te e che il tuo clan non sta tramando di far fuori Dodson.";
			link.l1.go = "negotiations_13";
		break;
		
		case "negotiations_13":
			dialog.text = "Che posso fare? Son pronto a chiedere perdono per il tentato e per i sospetti sulla morte di Marlow. Posso assicurargli che i Narvali non tramano nulla contro di lui e giuro sulla sacra Bibbia. Tu e Dodson riterrete ciò abbastanza?";
			link.l1 = "Lo farò. Son certo che anche Dodson ne sarà persuaso, se andrai da lui di persona. Prima però gli parlerò delle tue intenzioni, poi tornerò da te con ciò che avrò scoperto.";
			link.l1.go = "negotiations_14";
		break;
		
		case "negotiations_14":
			dialog.text = "D’accordo. Aspetterò.";
			link.l1 = "Tornerò presto...";
			link.l1.go = "negotiations_15";
		break;
		
		case "negotiations_15":
			DialogExit();
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "peace"; // ноду Акуле
			sld = characterFromId("Dexter");
			sld.dialog.currentnode = "First time"; 
			LAi_SetStayTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "SanAugustineResidence", "goto", "goto11");
			AddQuestRecord("SharkHunt", "56");
			NextDiag.CurrentNode = "narval_wait";
		break;
		
		case "negotiations_17":
			dialog.text = "Hai già parlato con l’ammiraglio? Qualche novità?";
			link.l1 = "Sì, l’ho fatto. Se gli farai visita in modo ufficiale, il problema sarà risolto.";
			link.l1.go = "negotiations_18";
		break;
		
		case "negotiations_18":
			dialog.text = "A dirla tutta, non mi aspettavo... Questa sì che è una notizia magnifica.";
			link.l1 = "Sì, sai, ne sono felice anch’io.";
			link.l1.go = "negotiations_19";
		break;
		
		case "negotiations_19":
			dialog.text = "Hai reso un grande servizio al clan dei Narvali impedendo un massacro insensato e, forse, persino lo sterminio totale della mia gente. Ti dono questo moschetto della torre – non troverai un’arma simile altrove. Inoltre, ti è concesso visitare le nostre navi senza alcuna restrizione.";
			if (pchar.questTemp.LSC.Mary == "alive") 
			{
				link.l1 = "Grazie. Un dono davvero prezioso. Sì, Donald, ancora una cosa: fai pace con Mary la Rossa. Ha il sangue caldo, ma è anche sincera e d’onore. Il vostro bisticcio l’ha spinta a lasciare il clan e per poco non ci rimetteva la pelle.";
				link.l1.go = "negotiations_20";
			}
			else
			{
				link.l1 = "Grazie. Un dono davvero prezioso. E sono davvero lieto che sia andata a finire così bene.";
				link.l1.go = "negotiations_21";
			}
		break;
		
		case "negotiations_20":
			dialog.text = "Dille che le chiedo perdono per averle fatto del male e per quei due canaglie che hanno osato aggredirla. Voi due siete... amici, vero?";
			link.l1 = "Hai ragione, Donald. Glielo dirò. E sono davvero lieto che tutto sia finito così bene.";
			link.l1.go = "negotiations_21";
		break;
		
		case "negotiations_21":
			GiveItem2Character(pchar, "mushket6"); 
			Log_Info("You have received a tower musket");
			PlaySound("interface\important_item.wav");
			dialog.text = "Buona fortuna. Vieni da me se avrai domande.";
			link.l1 = "Va bene. Addio!";
			link.l1.go = "exit";
			CloseQuestHeader("SharkHunt");
			bDisableFastReload = false; // belamour legendary edition
			pchar.questTemp.LSC.nrv_friend = "true"; //флаг на проход по кораблям нарвалов
			NextDiag.TempNode = "grinspy_wait";
			sld = characterFromId("Mary");
			sld.quest.donald = "true";
			LocatorReloadEnterDisable("CeresSmithy", "reload3", false);
			LocatorReloadEnterDisable("CeresSmithy", "reload4", false); // открываем Церес изнутри
			for (i=1; i<=6; i++)
			{
				sld = CharacterFromID("NarvalSold_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("NarvalProt_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			// здесь почищу весь хлам, который накопился
			DeleteAttribute(pchar, "questTemp.LSC.Donald_enter"); // атрибут гардов
			DeleteAttribute(pchar, "questTemp.LSC.Florentina");
			DeleteAttribute(pchar, "questTemp.LSC.Dodson_poison");
			DeleteAttribute(pchar, "questTemp.LSC.Dodson_warning");
			DeleteAttribute(pchar, "questTemp.LSC.Whiskey_clear");
			DeleteAttribute(pchar, "questTemp.LSC.CapperDie_Aeva");
			AddSimpleRumourCityTip("They say that you are a friend of Donald, Greenspen, the leader of Narwhals. Well, Rivados hate you now...", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("They say that you are Narwhal now. Or do you serve under admiral's command? I don't get it...", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("I've heard that you have made peace between admiral and Narwhals. Hm, Rivados must be insane about that...", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("So Chad Kapper was a murderer of Alan Milrow! That is surprising!", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("Take care of Red Mary cause you are lucky to be with her - she is so reckless! She always gets in trouble...", "LostShipsCity", 20, 5, "LSC", "");
		break;
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Cosa stai facendo laggiù, eh? Ladro!","Guarda un po’ lì! Non appena son sprofondato nei miei pensieri, hai subito pensato di frugare nel mio baule!","Hai deciso di ficcare il naso nei miei forzieri? Non te la caverai così facilmente!");
			link.l1 = "Merda!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Cosa?! Hai deciso di ficcare il naso nei miei forzieri? Non la passerai liscia!";
			link.l1 = "Ragazza sciocca!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Ascolta, faresti meglio a togliere quell'arma. Mi mette a disagio.","Sai, qui non si tollera girare con la lama sguainata. Riponila via.","Ascolta, lascia stare il cavaliere medievale che corre con la spada sguainata. Mettila via, non fa per te...");
			link.l1 = LinkRandPhrase("D'accordo.","Certo.","Come dici tu...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Ascolta, sono cittadino della città e ti chiederei di tenere a bada la lama.","Ascolta, sono un cittadino di questa città e ti chiederei di tenere a bada la tua lama.");
				link.l1 = LinkRandPhrase("D'accordo.","Certo.","Come dite voi...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Fa' attenzione, compare, a correre in giro armato. Potrei innervosirmi...","Non mi piace quando gli uomini camminano davanti a me con l’arma sguainata. Mi mette i brividi...");
				link.l1 = RandPhraseSimple("Capito.","La sto portando via.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

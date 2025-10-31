// Хосе Диос - картограф
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
		case "First time":
			dialog.text = "Che vuoi, bellezza?";
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "dios")
			{
				link.l3 = TimeGreeting()+"! Dimmi, sei tu Jose Dios, il cartografo?";
				link.l3.go = "island";
			}
			link.l1 = "No, niente.";
			link.l1.go = "exit";	
			NextDiag.TempNode = "First time";
		break;
		
		case "island":
			dialog.text = "Sì, sono io. Non ti conosco, signore. Che diavolo vuoi da me?";
			link.l1 = "Il mio nome è "+GetFullName(pchar)+" e sono stato mandato da Jan Svenson. Te lo ricordi, vero?";
			link.l1.go = "island_1";
		break;
		
		case "island_1":
			dialog.text = "Ah, signor Svenson! Certo che me lo ricordo! Su, mettiti comodo... Come se la cava il buon vecchio Jan?";
			link.l1 = "Grazie, sta bene. Señor Dio, ho bisogno del vostro aiuto. Vorrei chiedervi consiglio in una questione che, per la vostra professione, dovreste ben conoscere. Jan mi ha detto che siete un luminare in fatto di geografia dei Caraibi...";
			link.l1.go = "island_2";
		break;
		
		case "island_2":
			dialog.text = "Ascolto, señor. Cosa desideri sapere sulla geografia dell’arcipelago?";
			link.l1 = "Dicono che a nord-ovest dell’Avana, tra Cuba e il Golfo del Messico, ci sia un’isola o forse qualcos’altro. Nessuna mappa l’ha mai segnata. Mi piacerebbe sapere quanto ci si può fidare di queste chiacchiere.";
			link.l1.go = "island_3";
		break;
		
		case "island_3":
			dialog.text = "Hm... Mi hai chiesto d'una faccenda che mi tormenta da molti anni. Quel luogo di cui parli attira da tempo le menti curiose dei geografi, ma nessun cane ha mai avuto il fegato d'esplorare quella regione.";
			link.l1 = "Perché?";
			link.l1.go = "island_4";
		break;
		
		case "island_4":
			dialog.text = "Il fatto è che quel posto è una sorta di anomalia naturale. La probabilità di tempeste in quella zona è molto più alta che altrove. Forse la causa è una corrente marina fredda, ma questa è solo una mia ipotesi. Molte navi sono sparite lì, e questo basta a far sì che i marinai evitino quel luogo; comunque tutte le principali rotte marittime passano ben lontano da quella regione.";
			link.l1 = "Immagino che nemmeno tu conosca la verità...";
			link.l1.go = "island_5";
		break;
		
		case "island_5":
			dialog.text = "Esattamente, signore. Ma possiedo un paio di documenti storici e qualche prova concreta, quindi ho tutto il diritto di sospettare che quel luogo esista davvero.";
			link.l1 = "Puoi raccontarmi di più?";
			link.l1.go = "island_6";
		break;
		
		case "island_6":
			dialog.text = "Certo. La prova più importante è il documento storico con estratti dal diario del capitano Alvarado, che visitò l'Isola nel 1620. Una storia davvero intrigante, ve lo assicuro!";
			link.l1 = "Capitano Alvarado? È la seconda volta che sento quel nome...";
			link.l1.go = "island_7";
		break;
		
		case "island_7":
			dialog.text = "Non mi sorprende. La storia del capitano Alvarado fa parte del folclore da anni. Si è trasformata, col tempo s’è gonfiata di chiacchiere, menzogne e sogni; così è nata la leggenda dell’Isola delle Navi Abbandonate. Le dicerie cambiano, ma la carta e l’inchiostro restano, immutati per centinaia d’anni. Ecco, leggi questa storia: forse ti aiuterà a scoprire ciò che cerchi.";
			link.l1 = "Grazie! Hai altro da offrirmi?";
			link.l1.go = "island_8";
		break;
		
		case "island_8":
			dialog.text = "Si dice che il fondale marino da quelle parti si sollevi tanto da formare un banco enorme. Ho già accennato alla corrente. E, secondo le chiacchiere dei marinai, c’è un gran raduno di gabbiani e altri uccelli marini in quel punto.\nAlvorado ha menzionato i nomi di alcune navi che facevano parte della squadra dell’ammiraglio Francisco Betancourt, dispersa più di cinquant’anni fa. Dubito sia soltanto una coincidenza...";
			link.l1 = "Tornerò alla mia nave e leggerò con attenzione gli appunti di Alvarado. Grazie per l'aiuto, Señor Dios!";
			link.l1.go = "island_9";
		break;
		
		case "island_9":
			dialog.text = "Di nulla. In realtà non ti ho proprio aiutato, non hai le coordinate del posto e neppure io. Non posso nemmeno dimostrare che ci sia davvero un'isola abitata laggiù. Ma se ho ben capito, hai intenzione di esplorare quella zona?\nSe è così, sappi che ti sarò davvero riconoscente per qualsiasi informazione, soprattutto se accompagnata da prove concrete. Mi sembri un uomo di fortuna, ma troverò comunque il modo di sdebitarmi.";
			link.l1 = "Bene. Allora siamo d’accordo, Señor Dios. Chissà, forse un giorno qualcuno leggerà le mie memorie... e magari qualcun altro scriverà una leggenda...";
			link.l1.go = "island_10";
		break;
		
		case "island_10":
			dialog.text = "Perché no? Señor "+pchar.name+", Vedo che siete un uomo d’avventura, sempre in viaggio, dunque vorrei chiedervi un favore.";
			link.l1 = "Sì? Ti ascolto.";
			link.l1.go = "island_11";
		break;
		
		case "island_11":
			dialog.text = "Sai che sono un cartografo. Per due anni ho tracciato mappe dell’arcipelago caraibico, raccogliendo l’atlante dell’ammiraglio per il concorso del Viceré di Nueva Granada. Ma tutte le mie ventiquattro mappe sono state rubate dalla mia casa in modo sfacciato, proprio mentre ero prigioniero dei pirati—quelli da cui mi ha liberato il signor Svenson.\nSono certo che l’attacco sia stato organizzato da uno dei miei rivali per mettere le mani sui miei lavori. È passato molto tempo, ma non ho più visto una sola delle mie mappe.";
			link.l1 = "Capisco. Vuoi che ti restituisca le tue mappe.";
			link.l1.go = "island_12";
		break;
		
		case "island_12":
			dialog.text = "Esattamente. Forse li troverai nel corso delle tue future avventure. È facile riconoscerli – il mio marchio è su ognuno di essi. Ti ricompenserò generosamente se, per qualche miracolo, riuscirai a raccogliere tutte e ventiquattro le mappe.";
			link.l1 = "Va bene. D'ora in poi presterò molta attenzione ad ogni mappa che mi capiterà tra le mani nell’arcipelago. Ora però devo andare. Grazie per la conversazione intrigante e per il documento.";
			link.l1.go = "island_13";
		break;
		
		case "island_13":
			DialogExit();
			AddQuestRecordInfo("LSC_Alvorado", "1");
			AddQuestRecord("SharkHunt", "4");
			pchar.questTemp.Saga.SharkHunt = "LSC";
			NextDiag.CurrentNode = "Dios";
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			pchar.questTemp.AdmiralMap = "true";
		break;
		
		case "Dios":
			dialog.text = "A-ah, sei tu, signor "+GetFullName(pchar)+"Hai qualche storia succosa da raccontarmi?";
			if (CheckAttribute(pchar, "questTemp.AdmiralMap") && CountAdmiralMapFromCharacter() > 0 && CountAdmiralMapFromCharacter() < 24 && !CheckAttribute(npchar, "quest.mapinfo"))
			{
				link.l3 = TimeGreeting()+"! Signor Dio, per carità, dia un’occhiata alla mappa che ho trovato. Deve essere una delle vostre, dal segno che porta.";
				link.l3.go = "map_info";
			}
			if (CheckAttribute(pchar, "questTemp.AdmiralMap") && CountAdmiralMapFromCharacter() > 23)
			{
				link.l3 = TimeGreeting()+"! Señor Dio, porto buone nuove per voi. Sono riuscito a mettere insieme la collezione completa delle vostre mappe uniche, proprio come desideravate. Ecco qui tutte e ventiquattro le mappe.";
				link.l3.go = "amap";
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Dios")) // был в LSC
			{
				link.l4 = TimeGreeting()+"Sì, ci sono stato. Ho visitato quel luogo misterioso di cui parlavamo.";
				link.l4.go = "LSC";
			}
			link.l9 = "Niente da segnalare finora, señor. Volevo solo vedere come ve la passate.";
			link.l9.go = "exit";
			NextDiag.TempNode = "Dios";
		break;
		
		case "map_info":
			dialog.text = "Fammi vedere... (dando un'occhiata) Ma certo! Questa è una delle mie mappe per l'atlante dell'ammiraglio! Capitano, ti supplico davvero di trovarle tutte! So che è quasi un'impresa disperata, ma... non voglio perdere la speranza.";
			link.l1 = "Non perderlo, signore. Ho trovato questa mappa, quindi c’è speranza che trovi anche il resto. Sono ancora nei Caraibi.";
			link.l1.go = "map_info_1";
		break;
		
		case "map_info_1":
			dialog.text = "Il vostro ottimismo mi rinfranca davvero, signor capitano. Forse avrò ancora modo di dimostrare a don Juan de Cordova chi è il miglior cartografo dell’arcipelago!";
			link.l1 = "Riuscirai a sbaragliare tutti quei cani maledetti che ti ostacolano. Le mappe sono davvero magnifiche... Addio, Signore!";
			link.l1.go = "exit";
			npchar.quest.mapinfo = "true";
			NextDiag.TempNode = "Dios";
		break;
		
		case "amap":
			Achievment_Set("ach_CL_110");
			dialog.text = "Non ci posso credere ai miei occhi! Li hai davvero trovati? Tutti quanti?";
			link.l1 = "Sì. Non è stato facile, ma la fortuna alla fine mi ha sorriso in questa impresa. Prenda le sue mappe – sono magnifiche, ognuna di esse supera di gran lunga qualsiasi altra che abbia mai visto.";
			link.l1.go = "amap_1";
		break;
		
		case "amap_1":
			RemoveAllAdmiralMap()
			Log_Info("You have given the complete set of admiral's maps");
			PlaySound("interface\important_item.wav");
			dialog.text = "Incredibile! È semplicemente troppo incredibile! A dire il vero, non avrei mai creduto che questo momento arrivasse davvero.";
			link.l1 = "Dum spiro, spero, Signor Dio. Ora puoi affrontare don Cordova. Son certo che saprà riconoscere a dovere il tuo talento.";
			link.l1.go = "amap_2";
		break;
		
		case "amap_2":
			dialog.text = "Hai la mia gratitudine, Capitano! Non immagini nemmeno quale favore mi hai reso. Come promesso, sarai ricompensato. Ho anche un dono per te: credo che, da vero lupo di mare, ti tornerà assai utile.";
			link.l1 = "Mi hai proprio stuzzicato, signor mio!";
			link.l1.go = "amap_3";
		break;
		
		case "amap_3":
			GiveItem2Character(pchar, "spyglass5"); 
			Log_Info("You have received a ship telescope");
			PlaySound("interface\important_item.wav");
			dialog.text = "Ecco! Questo è un cannocchiale navale di mia invenzione. È unico, non ne troverai uno simile in tutto il mondo. Le lenti sono state forgiate in Europa dal più abile maestro di Spagna. L’astuccio l’ha fatto un bravo armaiolo amico mio. Un treppiede speciale ti permette di puntare lo strumento anche col mare in burrasca. Puoi scrutare ogni cosa che ti serve, sia essa una nave o una fortezza.";
			link.l1 = "Che dono meraviglioso! Grazie, Signor Dio.";
			link.l1.go = "amap_4";
		break;
		
		case "amap_4":
			dialog.text = "Usalo pure, signor capitano. Spero che il mio cannocchiale ti sia utile.";
			link.l1 = "Senza dubbio! Non vedo l’ora di piazzarlo sul ponte della mia nave e scrutare l’orizzonte attraverso di esso.";
			link.l2.go = "amapcopy_01";
		break;
		
		case "amapcopy_01":
			AddCharacterExpToSkill(pchar, "Fortune", 1000);//везение
			AddCharacterExpToSkill(pchar, "Leadership", 1000); // харизма
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность (раз телескоп дали)
			ChangeCharacterComplexReputation(pchar, "nobility", 10);// репутация-известность
			ChangeCharacterComplexReputation(pchar, "authority", 5);// репутация-авторитет
			ChangeCharacterNationReputation(pchar, SPAIN, 20);
			ChangeOfficersLoyality("good_all", 5);
			DeleteAttribute(pchar, "questTemp.AdmiralMap");
			dialog.text = "Sono lieto che tu sia soddisfatto. Inoltre, visto che tutto è andato così, ho ancora un'offerta da farti.";
			link.l1 = "Che c’è? Ti ascolto con la massima attenzione.";
			link.l1.go = "best_map";
		break;
		
		case "best_map":
			dialog.text = "Mi è venuto in mente che queste mappe sono ottime per un esploratore, ma non forniscono tutto ciò di cui ha bisogno un capitano di mare. Guardi lei stesso: tutte le baie, i promontori e le lagune sono disegnati con grande precisione, ma non si può tracciare una rotta tra le isole.";
			link.l1 = "È vero, non si può determinare una rotta con esse.";
			link.l1.go = "best_map_01";
		break;
		
		case "best_map_01":
			dialog.text = "Ma posso anche disegnarti una mappa dell’arcipelago! E non di quelle che compri dalla Compagnia Olandese delle Indie Occidentali, ma una mappa unica, fatta a regola d’arte.";
			link.l1 = "Grazie, señor Dio, ma di una simile mappa non ho bisogno. Ti ringrazio comunque per la tua offerta!";
			link.l1.go = "best_map_02";
			link.l2 = "State scherzando?! Santo Dio, come potrei mai rifiutare? Ditemi solo di cosa avete bisogno – non baderò a spese né a strumenti!";
			link.l2.go = "best_map_04";
		break;
		
		case "best_map_02":
			dialog.text = "Ebbene, dovevo pur proporlo. In ogni caso, è stato un piacere fare affari con voi, señor "+pchar.lastname+"!";
			link.l1 = "Anche a te! Che la fortuna ti assista!";
			link.l1.go = "best_map_03";
		break;
		
		case "best_map_03":
			DeleteAttribute(pchar, "questTemp.AdmiralMapCopy");
			DialogExit();
			NextDiag.CurrentNode = "Dios";
		break;
		
		case "best_map_04":
			dialog.text = "Gli strumenti li ho già, grazie. Mi servirà una mappa ordinaria dell'arcipelago, e inoltre chiederò una bussola e un cronometro tarato: la mappa deve essere precisa, altrimenti sarebbe solo un atto di sabotaggio. E come pagamento – un forziere pieno di dobloni.";
			if(CheckAMapItems())
			{
				link.l1 = "Tutto ciò che ha nominato ce l’ho già con me. Ecco, prenda.";
				link.l1.go = "best_map_07";
			}
			link.l2 = "Mappa ordinaria dell'arcipelago, bussola, cronometro tarato, un forziere di dobloni. Ricordato! Farò il possibile per consegnarli al più presto, mi aspetti!";
			link.l2.go = "best_map_07e";
		break;
		
		case "best_map_07e":
			DialogExit();
			NextDiag.CurrentNode = "best_map_waititems";
		break;
		
		case "best_map_waititems":
			dialog.text = "Benvenuto, mio caro amico! Ha portato la mappa ordinaria dell'arcipelago, la bussola, il cronometro tarato e il forziere di dobloni?";
			link.l1 = "Non ancora, Señor Dios. Ma li porterò di sicuro!";
			link.l1.go = "best_map_07e";
			if(CheckAMapItems())
			{
				link.l2 = "Sì, Señor Dios. Ecco, qui c'è tutto – prenda.";
				link.l2.go = "best_map_07";
			}
		break;
		
		case "best_map_07":
		    Log_Info("You handed over a regular map of the archipelago, a boussole, a tariffed chronometer, and a chest with doubloons.");
			TakeNItems(pchar,"chest", -1);
			TakeNItems(pchar,"map_normal", -1);
			TakeNItems(pchar,"bussol", -1);
			TakeNItems(pchar,"clock2", -1);
			dialog.text = "Ebbene, mi metto subito all’opera. Torna da me fra una settimana, e ti giuro che non te ne pentirai!";
			link.l1 = "Non ho dubbi, señor. Ci si rivede tra una settimana!";
			link.l1.go = "best_map_08";
		break;
		
		case "best_map_08":
			SetTimerFunction("AdmAtlas_comlete", 0, 0, 7);
			NextDiag.CurrentNode = "best_map_wait";
			pchar.questTemp.AdmiralAtlas = true;
			DialogExit();
		break;
		
		case "best_map_wait":
			if(CheckAttribute(pchar,"questTemp.AdmiralAtlas") && pchar.questTemp.AdmiralAtlas == "complete")
			{
				dialog.text = "Ah, eccovi, Señor "+pchar.lastname+"! Sono felice di annunciarvi che ho completato la mappa dell'arcipelago! E vi assicuro che è molto meglio di quella che mi avete fornito.";
				link.l1 = "Amico mio... Questa mappa è straordinaria! È, senza esagerare, un vero capolavoro! Come posso ringraziarvi per tutto quello che avete fatto per me?";
				link.l1.go = "best_map_09";
			}
			else
			{
				dialog.text = "Benvenuto, Señor! Mi dispiace, ma la mappa non è ancora pronta.";
				link.l1 = "Sì, ricordo che avete bisogno di una settimana. Sono solo passato a vedere come andava.";
				link.l1.go = "best_map_wait_01";
			}
		break;
		
		case "best_map_wait_01":
			NextDiag.CurrentNode = "best_map_wait";
			DialogExit();
		break;
		
		case "best_map_09":
			dialog.text = "Ma via, amico mio. È stato un piacere per me creare una mappa del genere per un capitano nobile che sa davvero apprezzarla. Ah, sì – e vi restituisco anche la vostra copia della mappa ordinaria. Buona fortuna nei mari aperti!";
			link.l1 = "Grazie di cuore! Avete ragione, questa mappa per me è semplicemente inestimabile. Addio, Señor Dios!";
			link.l1.go = "best_map_10";
		break;
		
		case "best_map_10":
			TakeNItems(pchar,"Map_Best", 1);
			TakeNItems(pchar,"map_normal", 1);
			Log_Info("You received an excellent archipelago map!");
			PlaySound("interface\important_item.wav");
			NextDiag.CurrentNode = "Dios";
			DialogExit();
		break;
		
		case "LSC":
			dialog.text = "Davvero?! L’hai trovato? Mettiti comodo, credo che la chiacchierata sarà lunga, dico bene?";
			link.l1 = "Ho davvero tanto da raccontarti sull’isola. Ma prima, voglio che tu mi dia la tua parola. Vedo che sei un uomo d’onore, quindi sono certo che manterrai la promessa...";
			link.l1.go = "LSC_1";
		break;
		
		case "LSC_1":
			dialog.text = "Di che diavolo parli, Capitano?";
			link.l1 = "Là ci sono delle anime che vi dimorano... e non saranno certo felici se qualcuno andrà a ficcare il naso nei loro affari. Non credo proprio che l’arrivo di una cosiddetta ‘squadra di ricerca’ verrebbe accolto a braccia aperte.";
			link.l1.go = "LSC_1_1";
		break;
		
		case "LSC_1_1":
			dialog.text = "";
			link.l1 = "Voglio che tu mi dia la tua parola d’onore che non divulgherai alcuna informazione che possa servire a trovare l’Isola nei prossimi dieci anni dopo questa nostra chiacchierata. Sei libero di raccontare tutto quel che vuoi sulla gente del posto, sulle loro abitudini e simili, ma non svelare dove si trova l’isola.";
			link.l1.go = "LSC_2";
		break;
		
		case "LSC_2":
			dialog.text = "Sono d’accordo, Capitano. Vi do la mia parola d’onore di gentiluomo: per i prossimi dieci anni non rivelerò a nessuno né il luogo dell’Isola né alcuna informazione che possa nuocere ai suoi abitanti.";
			link.l1 = "Ascolta allora la mia storia. Se vuoi, mettila pure per iscritto. Dunque, l’Isola è fatta di una miriade di relitti, scafi arenati su una vasta secca...";
			link.l1.go = "LSC_3";
		break;
		
		case "LSC_3":
			DialogExit();
			SetLaunchFrameFormParam("Two hours later...", "LSC_FinalDiosStory", 0, 5);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 2, 10); //крутим время
			RecalculateJumpTable();
		break;
		
		case "LSC_4":
			dialog.text = "Incredibile! Mi hai riferito notizie di gran valore, Capitano! I discendenti dell’ammiraglio de Betancourt vivono sull’isola! Ora sappiamo che fine ha fatto la sua squadra. E c’è una macchia bianca in meno sulla carta dei Caraibi... Ti ringrazio di cuore per il tuo racconto, "+pchar.name+"!";
			link.l1 = "Vedi ora perché ti ho chiesto di andarci davvero piano nel raccontare ciò che ti ho detto?";
			link.l1.go = "LSC_5";
		break;
		
		case "LSC_5":
			dialog.text = "Capisco. Puoi star certo che manterrò la mia parola. Dimmi... hai forse qualche oggetto proveniente dall’Isola?";
			if (CheckCharacterItem(pchar, "LSC_navigation_map"))
			{
				link.l1 = "Ho le istruzioni di rotta per l’Isola delle Navi Abbandonate. Ecco, dai un’occhiata. Grazie a queste puoi guidare una barchetta tra le scogliere e i relitti, e sbarcare sano e salvo sull’Isola. Senza queste dritte, raggiungerla è una chimera.";
				link.l1.go = "LSC_6";
			}
			else
			{
				link.l1 = "Purtroppo, non ne ho nemmeno uno.";
				link.l1.go = "LSC_7_1";
			}
		break;
		
		case "LSC_6":
			Log_Info("You have given sailing directions");
			PlaySound("interface\important_item.wav");
			dialog.text = "(guardando) Che documento magnifico! È stato tracciato da un vero artista della cartografia. Nemmeno io saprei far di meglio. Incredibile! Capitano, perché non mi cedi queste rotte di navigazione? Una storia è pur sempre una storia, ma questo foglio va mostrato ai più celebri geografi del Vecchio Mondo!";
			link.l1 = "Señor Dio, purtroppo ho anch’io bisogno di questo documento. Come ho già detto, è impossibile attraversare le scogliere che circondano l’Isola senza di esso. Ma se lo desiderate, potete farne una copia: sarò lieto che anche voi abbiate le indicazioni con voi.";
			link.l1.go = "LSC_10";
			//link.l2 = "Señor Dios, purtroppo ho bisogno di quest’oggetto per me stesso. Come ho già detto, è impossibile oltrepassare le scogliere intorno all’Isola senza di esso. Lo sacrificherei volentieri in nome della scienza, ma... Sono certo che capite.";
			//link.l2.go = "LSC_7";
		break;
		
		case "LSC_7":
			Log_Info("You received sailing directions");
			PlaySound("interface\important_item.wav");
			dialog.text = "Assolutamente. È un tuo diritto, sebbene sia un vero peccato... Ad ogni modo, grazie per il tuo racconto! Hai reso un gran servizio a geografi, cartografi e a tutta la gente curiosa.";
			link.l1 = "Prego, signor. Ebbene, ora devo levare l’ancora. Addio.";
			link.l1.go = "LSC_8";
		break;
		
		case "LSC_7_1":
			dialog.text = "Che peccato... Comunque, grazie per la tua storia! Hai reso un gran servizio a geografi, cartografi e a tutti i curiosi del mondo.";
			link.l1 = "Prego, signore. Ebbene, ora devo andarmene. Addio.";
			link.l1.go = "LSC_8";
		break;
		
		case "LSC_8":
			dialog.text = "Certo, "+pchar.name+"   Mi hai dedicato parecchio del tuo tempo. Porta i miei saluti al signor Svenson!";
			link.l1 = "Addio, Señor Dio.";
			link.l1.go = "LSC_9";
		break;
		
		case "LSC_9":
			DialogExit();
			NextDiag.CurrentNode = "Dios";
			AddCharacterExpToSkill(pchar, "Fortune", 400);//везение
			AddCharacterExpToSkill(pchar, "Leadership", 500); // харизма
			ChangeCharacterComplexReputation(pchar, "nobility", 5);// репутация-известность
			ChangeCharacterComplexReputation(pchar, "authority", 2);// репутация-авторитет
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			ChangeCharacterNationReputation(pchar, SPAIN, 5);
			DeleteAttribute(pchar, "questTemp.LSC.Dios");
			LAi_SetOwnerType(npchar);
		break;
		
		case "LSC_10":
			Log_Info("You received sailing directions");
			PlaySound("interface\important_item.wav");
			dialog.text = "Grazie di cuore! Sei davvero generoso. Dammi solo un po’ di tempo...";
			link.l1 = "...";
			link.l1.go = "LSC_11";
		break;
		
		case "LSC_11":
			DialogExit();
			SetLaunchFrameFormParam("Two hours later", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 2, 0);
			npchar.dialog.currentnode = "LSC_12";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "LSC_12":
			//RemoveItems(pchar, "LSC_navigation_map", 1);
			dialog.text = "Grazie di cuore! Sei stato davvero generoso. Ora abbiamo non solo la testimonianza, ma anche la prova concreta... Non resterai senza ricompensa, Capitano. Ho un piccolo dono per te.";
			link.l1 = "Che sorta di dono?";
			link.l1.go = "LSC_13";
		break;
		
		case "LSC_13":
			sld = characterFromId("Pirates_shipyarder");
			sld.quest.sextant = "true"; // атрибут Алексу на хронометр
			GiveItem2Character(pchar, "sextant1"); 
			PlaySound("interface\important_item.wav");
			dialog.text = "Non sono solo appassionato di cartografia e geografia, ma anche di matematica e astronomia. Ho passato un anno intero a tentare di creare uno strumento universale per calcolare latitudine e longitudine. E qualche progresso l’ho fatto. Guarda qui:\nQuesto è il mio sestante. L’ho progettato io stesso. Il problema è che non funziona. Serve un cronometro di precisione estrema. Anche quelli fatti dai migliori artigiani danno errori inaccettabili col tempo. Quindi, per ora, il mio strumento non vale un accidente.\nMa visto che navighi spesso, magari troverai un cronometro abbastanza preciso perché il sestante funzioni. Una volta che avrai trovato un simile orologio, non ti serviranno più boussole, bussole, astrolabi, clessidre o altri orpelli da quattro soldi – il mio strumento li manderà tutti a marcire nella stiva.";
			link.l1 = "Grazie, Señor Dios. Speriamo che riesca a trovare un cronometro che faccia funzionare la tua invenzione. Mi piacerebbe proprio avere un simile marchingegno... e che funzioni davvero. Ora però devo andare. Addio.";
			link.l1.go = "LSC_8";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Sei "+GetSexPhrase("Un ladro, eh! Guardie, prendetelo!","Una ladra, eh! Guardie, prendetela!")+"!!!","Non ci posso credere! Mi sono voltato un attimo – e tu già frughi tra le mie cose! Al ladro!!!","Guardie! Al ladro! Fermate quel furfante!!!");
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
	}
}

bool CheckAMapItems()
{
	return GetCharacterItem(pchar,"chest")      && 
		   GetCharacterItem(pchar,"map_normal") &&
		   GetCharacterFreeItem(pchar,"bussol") &&
		   GetCharacterFreeItem(pchar,"clock2");
}
// диалоги Уракана, Канека и прочих индейцев ица
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
			dialog.text = "Ti serve qualcosa, compare?";
			link.l1 = "No, niente.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// ица-горожане
		case "itza_ctz":
			dialog.text = LinkRandPhrase("Un altro viso pallido... Il gran sacerdote sarà lieto di strapparti il cuore...","La faccia pallida sa come arrivare a Tayasal, ma nessuno lascia la città!","Mi sorprendi, muso pallido: ancora non sei andato nel regno degli spiriti... Cammina finché puoi, presto incontrerai i tuoi antenati.");
			link.l1 = LinkRandPhrase("Ebbene, ebbene. Vedremo...","Non cercar di spaventarmi, guerriero dalla pelle rossa. Ho visto di peggio, credimi.","Va', va'. Prova a spaventare i marmocchi.");
			link.l1.go = "exit";
			NextDiag.TempNode = "itza_ctz";
		break;
		
		case "itza_ctz_1":
			dialog.text = LinkRandPhrase("Benedicimi per la battaglia contro il nemico, grande Cavil!","Grande Cavil e possente Kukulcan ci onorano con la loro presenza. Persino nei tempi degli antichi Maya ciò non accadeva!","Trasmetteremo ai nostri figli la leggenda della grande battaglia tra Kukulcan e Cavil!");
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "itza_ctz_1";
		break;
		
		// Уракан - вождь ица
		case "urakan":
			dialog.text = "Sei un grande guerriero, volto pallido. Porteremo il tuo sangue agli dèi. Morirai con onore.";
			link.l1 = "Calma, guerriero dalla pelle rossa. Non permetterò al tuo Kanek di portarmi in sacrificio a Kukulkan o a chiunque altro, per quel che conta. I tuoi guerrieri non sono riusciti a catturarmi. Ognuno di loro è caduto in battaglia.";
			link.l1.go = "urakan_1";
		break;
		
		case "urakan_1":
			dialog.text = "Sì, nobile guerriero dal volto pallido. Ma tu non reggeresti l’assalto di centinaia di guerrieri Tayasal Itza. Però, hai detto una parola interessante. Come conosci il grande Kanek e Kukulcan?";
			link.l1 = "Dunque, fammi indovinare... Se non sei Kanek, allora ti chiami Urakan e sei il figlio del sacerdote Kanek?";
			link.l1.go = "urakan_2";
		break;
		
		case "urakan_2":
			dialog.text = "Le tue labbra non mentono, viso pallido. Io sono Urakan, e mi hai sorpreso.";
			link.l1 = "Resterai ancor più sbalordito quando vedrai questo... Guarda.";
			link.l1.go = "urakan_3";
		break;
		
		case "urakan_3":
			dialog.text = "Per tutti gli dei! Se il volto pallido porta la maschera, vuol dire che è giunta l’ora... Sei tu, quello di cui Kukulcan parlava. Ha ordinato di condurti a lui appena fossi arrivato a Tayasal. Lui sa che tu sei qui.";
			link.l1 = "Kukulcán?! È qui a Tayasal?";
			link.l1.go = "urakan_4";
		break;
		
		case "urakan_4":
			dialog.text = "Sì, guerriero bianco. Quetzalcoatl viene a Tayasal. Presto partirà per portare la luce agli antenati, alla grande città dei Maya.";
			link.l1 = "Maledizione! Quindi, è già arrivato... (abbassando la voce) Urakan, so tutto. So che sei stato tu a mandare Ksatl Cha con il Custode della Verità a cercare Ksocheatem e la maschera di Kukulcan...";
			link.l1.go = "urakan_5";
		break;
		
		case "urakan_5":
			dialog.text = "";
			link.l1 = "Vedo lo stupore nei tuoi occhi, ma anche il dubbio, grande capo Urakan. Non sei soddisfatto di Kukulcan, vero?";
			link.l1.go = "urakan_6";
		break;
		
		case "urakan_6":
			dialog.text = "Ogni guerriero Itza è felice che il grande Kukulkan sia giunto, guerriero bianco. Devi presentarti davanti a Kukulkan. Ti aspetta da molte notti. È un grande profeta. Sa tutto prima ancora che accada. Vai dal Serpente Volante, non hai altra via. Non ti lasciamo lasciare Tayasal.";
			link.l1 = "Non capisci che appena Kukulcan passerà attraverso le porte del tempo, tutti voi, e tu per primo, smetterete d’esistere? E la parte più gustosa è che rinascerai in un’altra forma, in un altro corpo... Magari come un semplice soldato, o forse pure come uno storpio o uno straccione...";
			link.l1.go = "urakan_7";
		break;
		
		case "urakan_7":
			dialog.text = "Vai, guerriero dalla pelle chiara. Troverai Kukulcan nel Grande tempio dei guerrieri di Itza. Attraversa il ponte, dritto fino a vedere la grande piramide. Entra nella porta bassa del tempio e avvicinati al santuario.";
			link.l1 = "Va bene. Andrò da Kukulcan, poiché vedo che da questo incontro non ci scampiamo. Ma t'avverto, sappilo.";
			link.l1.go = "urakan_8";
		break;
		
		case "urakan_8":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetWarriorType(npchar);
			LAi_warrior_SetStay(npchar, true);
			LAi_warrior_DialogEnable(npchar, true);
			NextDiag.CurrentNode = "urakan_9";
			DeleteAttribute(pchar, "GenQuest.Notsearchbody");
			AddQuestRecord("Tieyasal", "25");
			pchar.quest.Tieyasal_Templegreat.win_condition.l1 = "location";
			pchar.quest.Tieyasal_Templegreat.win_condition.l1.location = "Temple_great";
			pchar.quest.Tieyasal_Templegreat.function = "Tieyasal_InGreatTemple";
			// экспа за бой
			AddComplexSelfExpToScill(300, 300, 300, 300);
			AddCharacterExpToSkill(pchar, "Leadership", 500);
			AddCharacterExpToSkill(pchar, "Fortune", 300);
		break;
		
		case "urakan_9":
			dialog.text = "Va', guerriero pallido. Kukulcan ti attende.";
			link.l1 = "Sto arrivando...";
			link.l1.go = "exit";
			NextDiag.TempNode = "urakan_9";
		break;
		
		case "urakan_10":
			PlaySound("Voice\English\Complete.wav");
			dialog.text = "Si è avverato! Quando ti ho visto combattere Kukulcan, ho capito che tu sei Cavil in persona. Sei venuto a Tayasal per salvare il popolo Itza dalla morte portata da mio padre e da Kukulcan. Mio padre, il grande sacerdote Kanek, ha condannato il nostro popolo alla rovina per la gloria degli antenati Maya ormai polvere. Io sono Urakan, capo di guerra che ha protetto gli Itza per molti anni. Nessun viso pallido è mai uscito vivo da Tayasal. Io e i miei guerrieri abbiamo sempre vegliato affinché il nostro popolo restasse salvo e protetto per generazioni. Non voglio sacrificare tutta la mia gente.";
			link.l1 = "Lo sapevo, Urakan. E ti ho chiesto di darmi una mano sul ponte.";
			link.l1.go = "urakan_11";
		break;
		
		case "urakan_11":
			dialog.text = "Niente sfugge agli occhi del grande Cavil. Perdonate Urakan se non ha capito chi siete davvero.";
			link.l1 = "Non preoccuparti, capitano. Ho sconfitto l’incarnazione mortale di Kukulcan, ma ci aspetta ancora un compito importante: dobbiamo chiudere i cancelli del passato. Questa dannata ferita nel tempo va sanata. Mi darai una mano?";
			link.l1.go = "urakan_12";
		break;
		
		case "urakan_12":
			dialog.text = "Con che può aiutarti Urakan, eh Cavil?";
			link.l1 = "Hai mandato Ksatl Cha con il Guardiano della Verità a cercare Ksocheatem e la maschera di Kukulcan. Dunque sai che può essere usata per chiudere le porte del tempo. Te l’ha raccontato tuo padre?";
			link.l1.go = "urakan_13";
		break;
		
		case "urakan_13":
			dialog.text = "Padre non parla. Studio gli scritti nel tempio della Sapienza e della Conoscenza. Ma molte cose sfuggono a Urakan. Forse Cavil saprebbe comprendere?";
			link.l1 = "Che cosa hai scoperto, di preciso?";
			link.l1.go = "urakan_14";
		break;
		
		case "urakan_14":
			dialog.text = "Imparo tutto a memoria. Scrivo e proclamo: 'Quando il sole sorge contro la pioggia, e il fuoco tra loro in triangolo, allora Tohil batte gamba contro gamba e incenerisce la maschera di Kukulcan sull’altare del tempo. E chiude i cancelli di Itzamna fino alla fine dei giorni.'";
			link.l1 = "Cosa.";
			link.l1.go = "urakan_15";
		break;
		
		case "urakan_15":
			dialog.text = "Sì.";
			link.l1 = "Gesù... Mostrami le porte del paradiso.";
			link.l1.go = "urakan_16";
		break;
		
		case "urakan_16":
			dialog.text = "Si trovano nel tempio di Kukulcan. Ma la porta lì è chiusa. Solo mio padre può chiuderla e aprirla. Quando aprì la porta del tempio di Kukulcan, disse: 'Il sole sorge e tramonta, l’acqua cade e si ritira, il fuoco divampa e si spegne, guerra e pace si danno il cambio, ma solo il cielo è eterno. Sopra il tempo c’è solo il cielo.'";
			link.l1 = "Interessante... Ricordiamocelo e vediamo che possiamo combinare...";
			link.l1.go = "urakan_17";
		break;
		
		case "urakan_17":
			dialog.text = "Rimango qui, giù in basso, accanto all’altare del tempo. Vedo ogni piramide e costruzione di Taysal dall’interno. Trova le chiavi. Io resto qui.";
			link.l1 = "Se avrò qualche questione davvero importante, verrò senz’altro da te.";
			link.l1.go = "urakan_18";
		break;
		
		case "urakan_18":
			DialogExit();
			NextDiag.CurrentNode = "urakan_adv";
			DeleteAttribute(pchar, "GenQuest.Notsearchbody");
			pchar.quest.Tieyasal_UrakanTemple.win_condition.l1 = "location";
			pchar.quest.Tieyasal_UrakanTemple.win_condition.l1.location = "Tenochtitlan";
			pchar.quest.Tieyasal_UrakanTemple.function = "Tieyasal_UrakanInTemple";
			AddQuestRecord("Tieyasal", "26");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "quest", "urakan", "", -1);
			// экспа за бой
			AddComplexSelfExpToScill(1000, 1000, 1000, 1000);
			AddCharacterExpToSkill(pchar, "Leadership", 3000);
			AddCharacterExpToSkill(pchar, "Fortune", 1500);
		break;
		
		case "urakan_adv":
			dialog.text = "Può Urakan offrire consiglio o agire per il grande Cavil?";
			if (Tieyasal_CheckTablets() && !CheckAttribute(npchar, "quest.tablets"))
			{
				link.l1 = "Dai un'occhiata a questa tavoletta che ho trovato. Dal luogo in cui l’ho scovata, dev’esserci sotto qualcosa che riguarda tuo padre, e di certo non è un oggetto comune...";
				link.l1.go = "tablets";
			}
			if (CheckAttribute(npchar, "quest.treasureentrance"))
			{
				link.l1 = "Ho trovato un altro ingresso in cima al Gran Tempio, ma è sigillato. Come diavolo ci entro? Forse quello che cerco si trova proprio lì dentro.";
				link.l1.go = "treasure";
			}
			link.l9 = "Niente per ora, Urakan. Me la caverò da solo...";
			link.l9.go = "exit";
			NextDiag.TempNode = "urakan_adv";
		break;
		
		case "tablets":
			dialog.text = "Lastra di pietra degli dèi. Mio padre ne possiede diversi pezzi e per lui valgono quanto l’oro. Gli antichi costruttori di Tayasal usavano queste lastre per attivare meccanismi nascosti, aprire e chiudere porte, persino per rituali magici.\nFunzionano solo se messe al posto giusto – ed è ciò che fa mio padre. Ma io, come te, sono un guerriero, e non so usarle come si deve. Forse Cavil ne sa qualcosa?";
			link.l1 = "Arriveremo senz’altro al fondo della faccenda...";
			link.l1.go = "exit";
			npchar.quest.tablets = "true";
			NextDiag.TempNode = "urakan_adv";
			AddQuestRecord("Tieyasal", "31");
		break;
		
		case "treasure":
			dialog.text = "Questa è la porta verso i tesori di Tayasal. Là riposano le ricchezze degli Itza. Solo mio padre può aprire e chiudere questa porta dall’interno. Nessuno osa accedere ai tesori senza di lui. Nemmeno io.";
			link.l1 = "Come ha fatto tuo padre ad aprire l’ingresso?";
			link.l1.go = "treasure_1";
		break;
		
		case "treasure_1":
			dialog.text = "Mio padre diceva: 'Ogni ricchezza ha due facce. Solo chi conosce entrambe può entrare nei tesori di Tayasal.' Cosa voglia dire... non lo so. Forse Cavil può capirci qualcosa?";
			link.l1 = "Anche questa la risolveremo, vedrai...";
			link.l1.go = "exit";
			NextDiag.TempNode = "urakan_adv";
			DeleteAttribute(npchar, "quest.treasureentrance");
			AddQuestRecord("Tieyasal", "32");
		break;
		
		case "urakan_19":
			PlaySound("Voice\English\Complete.wav");
			dialog.text = "Tu l’hai fatto, oh grande Cavil! Il popolo d’Itza ora è al sicuro. Io, Urakan, figlio di Kanek, ti giuro che non disonorerò l’onore che mi hai concesso, e difenderò Tayasal da ogni invasione di facce pallide senza onore in tuo nome.";
			link.l1 = "Ci credo bene, capitano. Ora possiamo festeggiare: abbiamo messo fine ai piani traditori di Kukulcan. Non potrà mai più scatenare una rivoluzione temporale.";
			link.l1.go = "urakan_20";
		break;
		
		case "urakan_20":
			PlaySound("interface\abordage_wining.wav");
			dialog.text = "Gloria al grande Cavil! A me e alla mia stirpe tocca il grande onore di vedere due dèi a Tayasal. Scriviamo questa storia per i nostri figli. Che sappiano della battaglia degli dèi a Tayasal! Gloria a Cavil! Gloria!";
			link.l1 = "Ho bisogno di un goccio...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Tieyasal_Win_IndianBead");
		break;
		
		// Канек - жрец ица
		case "kanek":
			dialog.text = "Ti trovi dinanzi al Serpente Alato, volto pallido. Lo spirito del possente Kukulcan in carne umana. Sei fortunato ad essere suo fratello per mezzo del padre della sua incarnazione, così come io sono fortunato ad essere il padre di sua madre, la donna che lo ha messo al mondo. È un grande onore. Forse è per questo che sei divenuto un guerriero valoroso e sei ancora vivo. \nMa il tuo tempo finirà, volto pallido. Inizieremo una nuova era, il tempo della grande Maya. Fonderemo il nostro potere e mai più lasceremo che i volti pallidi entrino nel nostro mondo. Presto. Io, Kanek il sacerdote, andrò a iniziare il rituale!";
			link.l1 = "Meraviglioso...";
			link.l1.go = "kanek_1";
		break;
		
		case "kanek_1":
			DialogExit();
			sld = characterFromId("Mishelle");
			sld.dialog.currentnode = "kukulkan_3";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.7);
		break;
		
		case "kanek_2":
			dialog.text = "Urakan, hai sentito cosa ha ordinato il nostro signore. Arrenditi ora!";
			link.l1 = "Quando i grandi si scannano tra loro, per noi poveri mortali è meglio restarsene in disparte a guardare da lontano, padre...";
			link.l1.go = "kanek_3";
		break;
		
		case "kanek_3":
			dialog.text = "Cosa?! Rinfrànati, figliolo!";
			link.l1 = "Quest’uomo è il fratello di Kukulcan, un gran guerriero. In lui vedo la stessa incarnazione di Cavil! Nessun altro resisterebbe così a un dio. Non è uno sprovveduto in duello tra divinità, padre! E se porti offerte a Kukulcan, i miei guerrieri verseranno il loro sangue per Cavil!";
			link.l1.go = "kanek_4";
		break;
		
		case "kanek_4":
			dialog.text = "Sei fuori di testa, Urakan?";
			link.l1 = "Per molti anni io, che porto il nome di Hurakan, ho difeso le nostre terre in nome di Cavil dagli invasori venuti da lontano. Centinaia di loro sono caduti sotto le nostre mazze e nessuno ha mai lasciato Tayasal. Ma mai nei miei giorni ho visto un guerriero tanto forte e veloce quanto questo viso pallido. Se davvero può sconfiggere Kukulcan, allora egli è la personificazione stessa dello spirito di Cavil!";
			link.l1.go = "kanek_5";
		break;
		
		case "kanek_5":
			DialogExit();
			sld = characterFromId("Mishelle");
			sld.dialog.currentnode = "kukulkan_win_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

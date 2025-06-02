void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    ref chr, sld, rShip, rItm, rItem;
    float  fTemp;
    bool bOk;
	int i, iTemp;
	string sAttr, sGun, sBullet, attrL;
	aref rType;
    
	// генератор ИДХ по кейсу -->
	sAttr = Dialog.CurrentNode;
  	if (findsubstr(sAttr, "CabinCompanionTalk_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	PChar.GenQuest.CabinCompanionNum = strcut(sAttr, i+1, strlen(sAttr)-1); // индекс в конце
 	    Dialog.CurrentNode = "Cabin_Companion_Talk";
 	}
	
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	PChar.GenQuest.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	if (findsubstr(sAttr, "SetMusketBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	PChar.GenQuest.SetMusketBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetMusketBullets2";
 	}
	
	if (findsubstr(sAttr, "tonzag_jail_" , 0) != -1) {
	 	pchar.questTemp.Tonzag.JailDialog.ID = strcut(sAttr, strlen("tonzag_jail_"), strlen(sAttr) - 1);
		DeleteAttribute(pchar, "questTemp.TonzagQuest.JailDialog." + pchar.questTemp.Tonzag.JailDialog.ID);
		AddDialogExitQuestFunction("Tonzag_InJailDialog");
 	    Dialog.CurrentNode = "exit";
 	}
 	// генератор ИДХ по кейсу <--

	switch(Dialog.CurrentNode)
	{
        case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
		break;
		
		case "First time":
	      	NextDiag.TempNode = "First time";

	        Dialog.Text = "Se stai leggendo questa riga, c'è un bug nel codice";
			Link.l1 = "Esci";
			Link.l1.go = "exit";
			//--> Вступительный туториал на палубе корабля за Шарля
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_TrumDialogSamSoboi_1"))
			{
				dialog.text = "Dannazione, che emozione! Una vera battaglia navale!\nPeccato che non vedrò lo scontro da qui... Ma non importa. Penso di aver già acquisito abbastanza esperienza in ambito marittimo per immaginare come si svolgeranno i fatti\nSaranno almeno cinque pirati... Una nave grande, un paio di medie e qualche bagnarola. Perfetto contro il nostro pinasco. Ne uscirà un gran racconto — Lulu ne sarà entusiasta!";
				link.l1 = "...";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.SharlieTutorial_TrumDialogSamSoboi_1");
				pchar.wind.speed = 18.0;
				fWeatherSpeed = stf(18.0);
				//AddDialogExitQuestFunction("SharlieTutorial_StartShip");
				AddDialogExitQuestFunction("SharlieTutorial_TrumLoad_3");
			}
			//<-- Вступительный туториал на палубе корабля за Шарля
			//--> Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC_FindIsland"))
    		{
    		    dialog.text = "Allora, abbiamo trovato questo posto sulla mappa. Dovrei segnarlo, e siamo pronti per andare a cercare.";
    			link.l1 = "...";
    			link.l1.go = "exit";
				AddDialogExitQuestFunction("SearchingForIslandOnMap");
    		}
			if (CheckAttribute(pchar, "questTemp.HWICMC") && pchar.questTemp.HWICMC == "Fleetwood")
    		{
    		    dialog.text = "Bene, siamo arrivati. Dovrei nascondere la mia nave nella baia del sud, poi tornare a piedi attraverso la giungla e organizzare una brutta sorpresa per Fleetwood.";
    			link.l1 = "...";
    			link.l1.go = "exit";
				pchar.quest.Fleetwood_repeatShore.win_condition.l1 = "ExitFromLocation";
				pchar.quest.Fleetwood_repeatShore.win_condition.l1.location = pchar.location;
				pchar.quest.Fleetwood_repeatShore.function = "Fleetwood_repeatShore";
    		}
			//<-- Голландский гамбит
			
			//--> Ложный след
			if(CheckAttribute(pchar, "questTemp.FalseTrace") && pchar.questTemp.FalseTrace == "TalkCabinWoman" && PChar.location == Get_My_Cabin()) 
	        {
				dialog.text = "Hm... Affidarsi a questo furfante è pericoloso, sebbene la sua storia sembri autentica. Forse, non sta mentendo questa volta. Ma, comunque, dovrei parlare con sua moglie... Contramaestro! Portami quella donna prigioniera!";
    			link.l1 = "Sì Sì, capitano!";
	    		Link.l1.go = "exit";
				chr = characterFromId("FalseTraceWife");
				chr.dialog.currentnode = "FalseTrace_wife_6";
				pchar.questTemp.FalseTrace.CharID = "FalseTraceWife";
				AddDialogExitQuest("SetFalseTraceCharToCabin");
	    	}
			//<-- Ложный след
			
			//--> Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "DigGems")
    		{
    		    dialog.text = "Sembra essere il posto. È l'unico albero senza linfa nei dintorni. Dovrei scavare qui.";
    			link.l1 = "(scava il tesoro fuori)";
    			link.l1.go = "exit";
				AddDialogExitQuest("FindPortugalGems");
    		}
			//<-- Португалец
			// Сага
			if (CheckAttribute(pchar, "questTemp.Saga.JessSoul"))
    		{
    		    dialog.text = "Cosa sta succedendo? Dove sono?! Che tipo di posto è questo?";
    			link.l1 = "...";
    			link.l1.go = "exit";
				AddDialogExitQuest("Saga_JessikaSoul_2");
    		}
            //--> приколы со стуком в дверь Диффиндура, LSC
			if (CheckAttribute(pchar, "questTemp.LSC.DiffIndoor"))
    		{
    		    dialog.text = "Questa è la porta che conduce agli interni della nave. È chiusa a chiave... Hawk deve essere qui. Cosa ha detto ancora Ole? Dovrei usare un bussare segreto.";
    			link.l1 = "Bussa due volte.";
    			link.l1.go = "knock_2";
				link.l2 = "Bussa tre volte.";
    			link.l2.go = "knock_3";
				link.l3 = "Bussa una volta, pausa, bussa tre volte.";
    			link.l3.go = "knock_1_3";
				link.l4 = "Bussa due volte, pausa, bussa due volte.";
    			link.l4.go = "knock_2_2";
				link.l5 = "Batti tre volte, pausa, batti una volta.";
    			link.l5.go = "knock_3_1";
    		}
			//<-- приколы со стуком в дверь Диффиндура, LSC
			
			//--> напялили водолазный скафандр, для перехода в режим шага
			if (pchar.model == "protocusto")
    		{
    		    dialog.text = "Caspita! Questa cosa è davvero pesante!";
    			link.l1 = "";
    			link.l1.go = "exit";
    		}
			//<-- водолазный скафандр
			// отказ от телепортации
			if (IsCharacterInLocator(pchar, "item", "dolly1") || IsCharacterInLocator(pchar, "item", "dolly2") || IsCharacterInLocator(pchar, "item", "dolly3"))
    		{
    		    dialog.text = "No-no-no! Non c'è modo! Tre volte erano più che sufficienti!";
    			link.l1 = "...";
    			link.l1.go = "exit";
    		}
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "roof")
    		{
    		    dialog.text = "È fatto. Levasseur è morto. Si è rivelato molto più facile di quanto mi aspettassi... Ma qualcosa non va. Thibaut non ha nemmeno parlato con Martene! Significa che o Robert mi ha tradito o c'è stato un incidente\nMa dove potrebbe essere scappato quel bastardo di Thibaut? Deve essere a caccia di Catherine. Devo agire rapidamente se voglio sottrarre la ragazza viva dalle sue grinfie...";
    			link.l1 = "";
    			link.l1.go = "terrapin";
    		}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "think")
    		{
    		    dialog.text = "Tesori, tesori... una città indiana... Non credo in tali coincidenze... Scommetto che mio fratello avesse qualcosa a che fare con la scomparsa della fregata di Dichoso. Probabilmente si è assicurato che Dichoso non aprirà mai più la bocca\nO forse stava lavorando con lui, gli spagnoli devono aver avuto motivi per pensare che Dichoso fosse da qualche parte qui. Non ha senso. Ma sono sicuro che l'oro indiano che Michel stava consegnando a de Poincy, così come l'oro di Miguel Dichoso, è lo stesso oro. La storia del prigioniero coincide con ciò che l'ufficiale mi ha raccontato delle avventure di mio fratello\nStrano, Michel non è riuscito a consegnare l'oro e neanche Miguel! E dove sono i tesori adesso allora? Forse, erano la ragione per cui mio fratello ha una tale fretta\nDunque, trovare l'oro significherà uccidere due uccelli con una pietra: guarderò negli occhi insolenti di mio fratello ancora una volta e... sì, l'oro è sempre una cosa buona. Ma come diavolo lo trovo? Sembra, che sia il momento di avvicinarsi molto agli spagnoli\nDon Ramona Mendoza è fuori discussione, dubito che sarò in grado di trattare con lui, ma il santo padre Vincento, il peggior nemico di un barone... lui farà al caso. Il suo tipo non è scrupoloso ma ama i soldi e i mezzi sporchi\nDichoso, Dichoso... Ho sentito questo cognome prima... o non l'ho fatto? Comunque, al diavolo. Dovrei andare dall'ufficiale e rivendicare il prigioniero spagnolo. Poi potrei dirigermi a Santiago in qualsiasi momento.";
    			link.l1 = "";
    			link.l1.go = "exit";
    		}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "shore")
    		{
    		    dialog.text = "La vaniglia è stata caricata sulla caracca e le sue vele sono sparite all'orizzonte da un pezzo - e questa maledetta galea è tornata al porto invece di prendere il largo. Non devo mostrarmi con la mia nave nel porto - è meglio se pensano che io sia partito da Guadalupa... Credo che andrò in città attraverso la giungla e mi informerò sul mio caro Marchais...";
    			link.l1 = "";
    			link.l1.go = "exit";
    		}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "galeon")
    		{
    		    dialog.text = "Ci sono solo pochi guardie sul ponte superiore, tutti piuttosto assonnati. Penso di poterli eliminare uno ad uno, se arrivo silenziosamente da dietro e li colpisco con un tirapugni alla nuca... ";
    			link.l1 = "";
    			link.l1.go = "exit";
    		}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth_room"))
    		{
    		    dialog.text = "Una casa vuota senza serrature con una stanza accogliente al secondo piano, e nelle vicinanze degli appartamenti di Calhoun... Questa è proprio la risposta alle preghiere di una donzella... Se esco dalla finestra e cammino sul abat-jour del tetto, mi intrufolerò con facilità nella stanza di Archie. Ma tutto questo deve essere fatto di notte per non farmi prendere...";
    			link.l1 = "";
    			link.l1.go = "exit";
				AddDialogExitQuest("GuardOT_FindWayToRoom");
    		}
			// Поиски Ксочитэма
			if (CheckAttribute(pchar, "questTemp.Ksochitam_Dolly") && pchar.questTemp.Ksochitam_Dolly == "half_pearl")
    		{
    		    dialog.text = "Finalmente! Ho localizzato il punto, indicato dalla 'manifestazione': è un idolo indiano. Quando vicino, la 'Freccia della Via' smette di oscillare e punta in una direzione. Beh, sembra logico - magia indiana e un idolo indiano. Ora dovrei segnare la posizione indicata dalla 'Freccia della Via' sulla mappa, e poi andrò a Dominica.";
    			link.l1 = "";
    			link.l1.go = "exit";
				AddDialogExitQuest("Ksochitam_FindFirstWay");
    		}
			if (CheckAttribute(pchar, "questTemp.Ksochitam_Dolly") && pchar.questTemp.Ksochitam_Dolly == "half_dominica")
    		{
    		    dialog.text = "Finalmente! Ho localizzato il posto, indicato dalla 'manifestazione': è un idolo indiano. Quando si avvicina, la 'Freccia della Via' smette di oscillare e punta in una direzione. Beh, sembra logico - magia indiana e un idolo indiano. Ora dovrei segnare la posizione indicata dalla 'Freccia della Via' sulla mappa, e poi andrò a Main.";
    			link.l1 = "";
    			link.l1.go = "exit";
				AddDialogExitQuest("Ksochitam_FindSecondWay");
    		}
			if (CheckAttribute(pchar, "questTemp.Ksochitam_Dolly") && pchar.questTemp.Ksochitam_Dolly == "full")
    		{
    		    dialog.text = "Entrambe le manifestazioni sono state trovate! Ora devo segnare la seconda direzione sulla mappa. L'intersezione di queste due direzioni mi mostrerà la posizione dell'isola di Ksocheatem.";
    			link.l1 = "";
    			link.l1.go = "exit";
				AddDialogExitQuest("Ksochitam_FindFullWay");
    		}
			// рассуждения по Тайясалю
			if (CheckAttribute(pchar, "questTemp.Tieyasal_CabinTalk"))
    		{
				if (pchar.questTemp.Tieyasal_CabinTalk == "calendar")
				{
					dialog.text = "Alonso de Maldonado ha detto che esiste un sentiero per Tayasal che inizia a nord dello Yucatan. Significa che dovrei addentrarmi nella selva della zona. Ma Gino ha detto che le statue del teletrasporto erano originariamente destinate a portare le persone a Tayasal\nE lo sciamano Miskito, Occhio di Serpente, mi ha detto che gli idoli erano progettati per inviare i 'mangiati' al posto. Ma allora, perché quei portali sono rotti? Hm. Inoltre, la mappa delle Due Manifestazioni mostra un cerchio strano vicino alla statua dei Miskito\nChe diavolo significa? Un altro posto magico? O indica che la statua lì ha delle funzioni aggiuntive? Suppongo, dovrei fare una visita allo sciamano. O potrei andare a Nord Ovest di Main e cercare il sentiero lì, in una delle baie locali.";
					link.l1 = "";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Alonso de Maldonado ha detto che c'era un altro modo per raggiungere Tayasal dalla parte settentrionale della penisola dello Yucatan. Ciò significa che devo cercare un sentiero nelle profondità della selva. È probabile che il sentiero di cui ho bisogno inizi in una delle insenature nella parte nord-occidentale della Main.";
					link.l1 = "";
					link.l1.go = "exit";
				}
				AddDialogExitQuest("Tieyasal_AfterCabinTalk");
    		}
			// решаем - титры или фриплей 010912
			if (CheckAttribute(pchar, "questTemp.Tieyasal_final"))
    		{
				dialog.text = "È fatto. La fine del mio lungo viaggio. Non avrei mai potuto immaginare che salvare mio fratello dalla prigione significava prepararmi per l'ultimo combattimento contro di lui! Che avevo quasi condannato il nostro mondo. Grazie a Dio, è finito\nNiente mi trattiene più nei Caraibi. È tempo di tornare a casa, in Francia. Ma... È davvero quello che voglio?";
				link.l1 = "Sì, sto tornando in Europa.";
				link.l1.go = "final_1";
				link.l2 = "No, resterò qui nei Caraibi.";
				link.l2.go = "final_2";
    		}
			// фэйловый финал 040912
			if (CheckAttribute(pchar, "questTemp.Europe"))
    		{
				PlaySound("Voice\English\military02.wav");
				dialog.text = "Hai sentito il colonnello? I ribelli si stanno nascondendo lì! Cerca ovunque, rovescia la casa e arresta chiunque trovi lì! Al lavoro!";
				link.l1 = "...";
				link.l1.go = "exit";
				AddDialogExitQuest("Europe_SharlieFinal_2");
    		}
			// Addon-2016 Jason, французские миниквесты (ФМК) Гваделупа
			/*if (CheckAttribute(pchar, "questTemp.FMQG.Info") && pchar.location == "Bridgetown_Plantation")
    		{
    		    dialog.text = "Questo è il miglior posto per un'imboscata. Dovrei aspettare qui l'arrivo di Pinette.";
    			link.l1 = "...";
    			link.l1.go = "exit";
				AddDialogExitQuest("FMQG_KidnappingInfo");
    		}*/
			// Addon-2016 Jason, французские миниквесты (ФМК) Сент-Кристофер
			if (CheckAttribute(pchar, "questTemp.FMQN.Choose") && pchar.location == "shore40")
    		{
				dialog.text = "Mh. Questa storia non suona giusta. Credo che quel barcone di St. Jones non sia mai stato destinato a esistere. Il tenente mi sta trascinando nella sua operazione militare. Perché ne avrei bisogno? Non sono in guerra con gli olandesi... Cosa dovrei fare? Dovrei andarmene e lasciare che i britannici si divertano da soli? O dovrei restare?";
				link.l1 = "Vattene.";
				link.l1.go = "FMQN_1";
				link.l2 = "Resta.";
				link.l2.go = "FMQN_2";
    		}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Chest") && pchar.location == "shore37")
    		{
    		    dialog.text = "Allora, il baule è preparato. Potrei cercare di trovare tutto il materiale richiesto da solo, ma preferirei andare a trovare Fadey. Mi sembra un uomo che può procurarsi qualsiasi cosa.";
    			link.l1 = "*USA L'OPZIONE DI PENSIERO AD ALTA VOCE PER FINIRE DI RACCOGLIERE LE MUNIZIONI*";
    			link.l1.go = "exit";
				AddDialogExitQuest("Mtraxx_PlantChestReadyExit");
    		}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Boats") && pchar.location == "Maracaibo_river")
    		{
    		    dialog.text = "Allora, dobbiamo costruire sei lunghe barche. Per questo ho bisogno di un falegname, 20 tavole e 10 pacchi di pelle";
    			link.l1 = "*USA UN'OPZIONE DI PENSIERO AD ALTA VOCE PER INIZIARE A COSTRUIRE LUNGHE BARCHE*";
    			link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.Mtraxx.Boats");
				AddQuestRecord("Roger_5", "11");
    		}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Powder") && pchar.location == "shore10")
    		{
    		    dialog.text = "Allora, intendo semplicemente far saltare in aria questo mucchio di vecchi alberi. Tutto ciò di cui ho bisogno per questo sono 300 unità di polvere da sparo, giusto per essere sicuro.";
    			link.l1 = "*usa l'opzione Pensieri Ad Alta Voce per ordinare la collocazione di polvere da sparo*";
    			link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.Mtraxx.Retribution.Powder");
				pchar.questTemp.Mtraxx.Retribution = "powder";
				chrDisableReloadToLocation = false;
    		}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.ExitClosed") && pchar.location == "Judgement_dungeon_01")
    		{
    		    dialog.text = RandSwear()+" L'uscita è sigillata! Sembra che abbiano bloccato la porta con qualcosa di pesante! "+RandSwear()+"\nZitto... Che diavolo?";
    			link.l1 = "";
    			link.l1.go = "mtraxx_dungeon";
				DeleteAttribute(pchar, "questTemp.Mtraxx.Retribution.ExitClosed");
    		}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Bead") && pchar.location == "Judgement_church")
    		{
    		    dialog.text = "Ecco... Fine della linea\n Sembra che don Enrico fosse serio: non c'è via d'uscita da queste segrete. Ho avuto un momento di speranza quando ho trovato una seconda porta al livello dell'acqua ma ora... Ho perso il conto del tempo - da quanto tempo sto aggirando questi tunnel bui? Mezza giornata, l'intera giornata? Questo posto è silenzioso e spaventoso come una bara\nUna volta c'era una chiesa qui, proprio qui. Che luogo perfetto per dire le mie preghiere. Ho peccato molto, troppo... Pregherò e dormirò qui, le mie ferite e la mia stanchezza mi stanno uccidendo. Se sono fortunato non mi alzerò mai più...";
    			link.l1 = "";
    			link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.Mtraxx.Retribution.Bead");
				AddDialogExitQuestFunction("Mtraxx_RetributionBead");
    		}
			// belamour legendary edition -->
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Choice") && pchar.questTemp.Mtraxx.Retribution.Choice == "to_choice")
			{
				dialog.text = "";
    			link.l1 = "Io, Charles de Maure, capitano e nobile francese, giuro a me stesso e alla mia coscienza che ho finito con il mio passato da pirata per sempre!";
    			link.l1.go = "Good_Choice";
				link.l2 = "Sì! Sì! Ah ha ha!! Ce l'ho fatta, sono sopravvissuto! Prendila, Zorro! Vai all'inferno, Marcus! Ora sono per conto mio! Charlie Prince potrà essere morto, ma Charles de Maure nessuno lo potrà mai uccidere!";
    			link.l2.go = "Bad_Choice";
			}
			// <-- legendary edition
			
			if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog")) {
				dialog.text = "Cosa dovremmo fare?";
				if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog.FirstTime")) {
					DeleteAttribute(pchar, "questTemp.TonzagQuest.JailDialog.FirstTime");
					dialog.text = "... naturalmente, Levasseur non è un idiota. Altrimenti, perché dovrebbero arrestarci proprio in questo momento?\nE non hanno detto una parola!\n"+dialog.text;
				}
				
				DeleteAttribute(link, "l1");
				if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog.Helena")) {
					link.l1 = "Elena, perché sei così silenziosa?";
					link.l1.go = "tonzag_jail_helena";
				}
				
				if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog.Mary")) {
					link.l2 = "Mary, perché sembri così felice?!";
					link.l2.go = "tonzag_jail_mary";
				}
				
				if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog.Tichingitu")) {
					link.l3 = "Tichingitu? Di qualcosa di appropriato per la situazione.";
					link.l3.go = "tonzag_jail_tichingitu";
				}
				
				if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog.Tonzag")) {
					link.l4 = "Ercule, riesci a sentirmi? Cosa stiamo per fare?";
					link.l4.go = "tonzag_jail_tonzag";
				}
				
				link.l5 = "Non c'è niente da fare. Immagino che indosserò le scarpe di Michel per un po'.";
				link.l5.go = "tonzag_exit";
			}
			
			if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailPanic")) {
				dialog.text = "";
				link.l1 = "Oh mio Dio, hanno ucciso Hercule!";
				link.l1.go = "exit";
				link.l2 = "Brutti bastardi!";
				link.l2.go = "exit";
				
				DeleteAttribute(pchar, "questTemp.TonzagQuest.JailPanic");
				AddDialogExitQuestFunction("Tonzag_GFAfterShot");
			}
			
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.RefusedGame")) {
				dialog.text = "Che serata! Perché l'ho ascoltata? Mio fratello aveva ragione - le ragazze qui sono completamente diverse. Forse aggiungono qualcosa al rum?";
				link.l1 = "È ora di dormire, e poi - a Cartagena!";
				link.l1.go = "exit";
				
				DeleteAttribute(pchar, "questTemp.HelenDrinking.RefusedGame");

				AddDialogExitQuestFunction("HelenDrinking_LightsOut1");
			}
			
			if (CheckAttribute(pchar, "questTemp.PZ_OsmatrivaemSunduk")) {
				dialog.text = "Non è stato rubato nulla, anche se tutto è sparpagliato in giro. Anche i preziosi sono intatti. ";
				link.l1 = "Non cercavano di derubarmi - cercavano qualcosa di specifico. Ma cosa? E, cosa ancora più importante, chi...?";
				link.l1.go = "exit";
				
				DeleteAttribute(pchar, "questTemp.PZ_OsmatrivaemSunduk");

				AddDialogExitQuest("PZ_OsmatrivaemSunduk_3");
			}
			
			if (CheckAttribute(pchar, "questTemp.PZ_GotovimShlupki")) {
				dialog.text = "Aspettiamo fino al calar della notte e poi attacchiamo!";
				link.l1 = "Nel frattempo, inizieremo a preparare le longarone.";
				link.l1.go = "exit";
				
				DeleteAttribute(pchar, "questTemp.PZ_GotovimShlupki");

				AddDialogExitQuest("PZ_ShturmZvezdy");
			}
			
			if (CheckAttribute(pchar, "questTemp.PZ_TiboUkralDevu")) {
				dialog.text = "Oh mio Dio... No, no, no... ";
				link.l1 = "";
				link.l1.go = "exit";
				
				DeleteAttribute(pchar, "questTemp.PZ_TiboUkralDevu");
				
				LAi_SetActorType(pchar);
				LAi_ActorAnimation(pchar, "kneeling", "1", 7.5);
			}
			
			if (CheckAttribute(pchar, "questTemp.PZ_DevaMertva")) {
				dialog.text = "Oh Dio, oh Dio, oh Dio... Perché? Oh Dio, perché... ma ho fatto tutto quello che potevo...";
				link.l1 = "È tutta colpa mia, solo mia. Non sono arrivato qui in tempo. Sono davvero dispiaciuto... Per favore, per favore perdonami.";
				link.l1.go = "exit";
				
				DeleteAttribute(pchar, "questTemp.PZ_DevaMertva");

				AddDialogExitQuest("PZ_TortureRoom_Levasser_DevushkaMertva8");
			}
		break;
		
		// boal -->
		case "TalkSelf_Main":
	   		NextDiag.TempNode = "First time";
//navy --> after duel in tavern
			if (CheckAttribute(pchar, "questTemp.LocationClone"))
			{
				Dialog.Text = RandPhraseSimple("È stata una battaglia infernale... Ora possiamo chiamare quei codardi che sono fuggiti...","Ha! È stato facile. E quei terroni si sono solo dispersi!");
				link.l1 = "...";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.LocationClone");
				break;
			}
//navy <--
	        Dialog.Text = RandPhraseSimple("Mmm... Quindi cosa dovrei fare ora?","Cosa fare ora?");
	        if (!bDisableMapEnter && pchar.location == Get_My_Cabin())
	        {
				//navy --> 13.02.08
				if (!bDisableMapEnter && GetCompanionQuantity(PChar) > 1)
				{
    				link.l3 = "Chiamate un compagno.";
    				link.l3.go = "Cabin_CompanionSelect";
				}
				//navy <--
			}
			else 
			{   //исп.линейка, квест №6, возможность переночевать в оплаченной комнате
				if (CheckAttribute(pchar, "questTemp.State.Open") && pchar.location == "Tortuga_tavern_upstairs")
				{
					if (makeint(environment.time) >= 22.0 || makeint(environment.time) < 10.0)
	    			{
	    				link.l1 = "Riposa fino al mattino.";
	    				link.l1.go = "TalkSelf_room_day";
	    			}
	    			else
	    			{
	    				link.l1 = "Riposa fino alla notte.";
	    				link.l1.go = "TalkSelf_room_night";
	    				link.l2 = "Riposa fino alla prossima mattina.";
						link.l2.go = "TalkSelf_room_day";
	    			}
				}
			}
	        if (!bDisableMapEnter)//боя в море нет
	        {
	            if (GetCargoGoods(pchar, GOOD_SLAVES) > 0)
	            {
	                Link.l5 = "Arruola gli schiavi nell'equipaggio.";
	        		Link.l5.go = "TalkSelf_SlavesToCrew";
	    		}
	        }
	        // захват города
	        if (GetCharIDXForTownAttack(pchar.location) != -1 && !CheckAttribute(Pchar, "GenQuestFort.StartAttack") && !CheckAttribute(Pchar, "questTemp.Sharlie.DefendSP"))
	        {
	            Link.l6 = "Inizia a catturare la città più vicina.";
	    		Link.l6.go = "TalkSelf_TownAttack";
	        }
	        
			bool bSeaBattle = (bDisableMapEnter) && (bSeaActive) && (!CheckAttribute(pchar, "GenQuest.MapClosedNoBattle"));
	        if(!bSeaBattle && PChar.location != "Deck_Near_Ship" && findsubstr(PChar.location, "_shipyard" , 0) == -1 && PChar.location != "CommonPackhouse_2" && !CheckAttribute(pchar, "GenQuest.CannotWait") && !CheckAttribute(loadedLocation, "CannotWait")) 
	        {
	        	Link.l7 = "Dovrei riposarmi...";
	    		Link.l7.go = "TalkSelf_StartWait";
	    	}
			
			if(CheckAttribute(pchar, "equip.gun"))
			{
				if(CheckAttribute(pchar, "chr_ai.gun.bulletNum") && sti(pchar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l8 = "Voglio cambiare le munizioni per le armi da fuoco.";
					Link.l8.go = "SetGunBullets";
				}	
			}
			
			if(CheckAttribute(pchar, "equip.musket"))
			{
				if(CheckAttribute(pchar, "chr_ai.musket.bulletNum") && sti(pchar.chr_ai.musket.bulletNum) > 1)
				{
					Link.l9 = "Voglio cambiare le munizioni per il moschetto.";
					Link.l9.go = "SetMusketBullets";
				}
					Link.l10 = "Voglio scegliere un'arma prioritaria per il combattimento.";
					Link.l10.go = "SetPriorityMode";
			}
			
			Link.l19 = "Voglio selezionare una pozione per l'uso costante.";
			Link.l19.go = "ChoosePotion";
			
			//--> Голландский гамбит
			if(CheckAttribute(pchar, "questTemp.HWIC_Coordinates") && PChar.location == Get_My_Cabin()) 
	        {
	        	Link.l11 = "Cerca di trovare l'isola dalle coordinate sulla mappa.";
	    		Link.l11.go = "Seek_AbyIsland";
	    	}
			//<-- Голландский гамбит
			
			//--> Ложный след
			if(CheckAttribute(pchar, "questTemp.FalseTrace") && pchar.questTemp.FalseTrace == "TalkCabin" && PChar.location == Get_My_Cabin()) 
	        {
	        	Link.l13 = "Evoca Adam Rayner.";
	    		Link.l13.go = "FalseTrace_Cabin";
	    	}
			if(CheckAttribute(pchar, "questTemp.FalseTrace") && pchar.questTemp.FalseTrace == "CatchAdam" && PChar.location == Get_My_Cabin()) 
	        {
	        	Link.l13 = "Arresta Adam Rayner.";
	    		Link.l13.go = "FalseTrace_Cabin";
	    	}
			//<-- Ложный след
			// Addon 2016-1 Jason Пиратская линейка
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Ammo") && PChar.location == "Shore37") // прогон 3
	        {
	        	Link.l17 = "Conta il contenuto del baule e decidi di finire di raccogliere munizioni per Picard.";
	    		Link.l17.go = "mtraxx_ammo";
	    	}
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Mutiny") && pchar.location == "Maracaibo_Plantation" && stf(environment.time) >= 3.00 && stf(environment.time) < 4.00) 
	        {
	        	Link.l17 = "Dai l'ordine di attaccare la piantagione di Maracaibo.";
	    		Link.l17.go = "mtraxx_mutiny";
	    	}
			if(CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "merida_boats" && pchar.location == "Maracaibo_river") 
	        {
	        	Link.l17 = "Dai un ordine per costruire lunghe barche.";
	    		Link.l17.go = "mtraxx_boats";
	    	}
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "powder" && pchar.location == "shore10") 
	        {
	        	Link.l17 = "Ordine di consegnare la polvere da sparo all'abatis morto.";
	    		Link.l17.go = "mtraxx_powder";
	    	}
			// Jason Долго и счастливо
			if(CheckAttribute(pchar, "questTemp.LongHappy") && pchar.questTemp.LongHappy == "letter") 
	        {
	        	Link.l18 = "Pensa a un matrimonio.";
	    		Link.l18.go = "LH_marry";
	    	}
			if(CheckAttribute(pchar, "questTemp.LongHappy") && pchar.questTemp.LongHappy == "marry_offer" && LongHappy_CheckShore()) // 28-03-20
	        {
	        	Link.l18 = "Fai una proposta di matrimonio.";
	    		Link.l18.go = "LH_marry_3";
	    	}
			if(CheckAttribute(pchar, "questTemp.LongHappy") && pchar.questTemp.LongHappy == "toIslaTesoro" && pchar.location == "Pirates_town") 
	        {
	        	Link.l18 = "Preparate la celebrazione.";
	    		Link.l18.go = "LH_marry_4";
	    	}
			// -->Авторемонт			
			if(Pchar.Location == Pchar.location.from_sea && CheckOfficersPerk(pchar, "SelfRepair") && CheckSelfRepairConditions()) 
			{
				Link.l14 = "Inizia a riparare le navi";
				Link.l14.go = "StartSelfRepair";
			}			
			// <--Авторемонт
			//--> завершение игры
			if(CheckAttribute(pchar, "questTemp.Tieyasal_WinEnd")) // patch-9
	        {
	        	Link.l15 = "Termina gli affari nei Caraibi e salpa per l'Europa.";
	    		Link.l15.go = "final_1";
	    	}
			//<-- завершение игры
			Link.l20 = RandPhraseSimple("Non ora. Non c'è tempo.","Non c'è tempo per quello, c'è troppo da fare.");
			Link.l20.go = "exit";
		break;
		
		case "tonzag_exit":
			DialogExit_Self();
			AddDialogExitQuestFunction("Tonzag_CreateKiller");
		break;
		
		case "StartSelfRepair":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
			LaunchRepair(pchar);
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Scegli il tipo di munizioni:";
			sGun = GetCharacterEquipByGroup(pchar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(pchar.chr_ai.gun.bulletNum); i++)
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
			i = sti(PChar.GenQuest.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(pchar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(pchar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(pchar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(pchar,"GenQuest.SetGunBullets");
			DialogExit_Self();
		break;
		
		case "SetMusketBullets":
			Dialog.Text = "Scegli il tipo di munizioni:";
			sGun = GetCharacterEquipByGroup(pchar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(pchar.chr_ai.musket.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");;
				Link.(attrL).go = "SetMusketBullets1_" + i;
			}
		break;
		
		case "SetMusketBullets2":
			i = sti(PChar.GenQuest.SetMusketBullets) + 1; 
			sGun = GetCharacterEquipByGroup(pchar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(pchar, "musket", sBullet);
			LAi_GunSetUnload(pchar, "musket");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(pchar,"GenQuest.SetMusketBullets");
			DialogExit_Self();
		break;
		
		case "SetPriorityMode":
			Dialog.Text = "All'inizio della lotta userò:";
			Link.l1 = "Spada";
			Link.l1.go = "BladePriorityMode";
			Link.l2 = "Archibugio";
			Link.l2.go = "MusketPriorityMode";
		break;
		
		case "BladePriorityMode":
			pchar.PriorityMode = 1;
			DialogExit_Self();
		break;
		
		case "MusketPriorityMode":
			pchar.PriorityMode = 2;
			DialogExit_Self();
		break;
		
		case "ChoosePotion":
			Dialog.Text = "Scegli la pozione:";
	    	Link.l1 = "Pozione curativa.";
	    	Link.l1.go = "ChoosePotion1";
			Link.l2 = "Elisir.";
	    	Link.l2.go = "ChoosePotion2";
			Link.l3 = "Miscela.";
	    	Link.l3.go = "ChoosePotion3";
			Link.l4 = "Radice di zenzero.";
	    	Link.l4.go = "ChoosePotion4";
			Link.l5 = "Rum.";
	    	Link.l5.go = "ChoosePotion5";
			Link.l6 = "Vino.";
	    	Link.l6.go = "ChoosePotion6";
			if (CheckAttribute(pchar, "GenQuest.Potion_choice"))
			{
				Link.l7 = "Voglio selezionare le pozioni automaticamente.";
				Link.l7.go = "ChoosePotion7";
			}
			Link.l8 = "Aspetta, ho cambiato idea..";
	    	Link.l8.go = "ChoosePotion8";
		break;
		
		case "ChoosePotion1":
			log_info("A healing essence will be used by default.");
			pchar.GenQuest.Potion_choice = "potion1";
			DialogExit_Self();
		break;
		
		case "ChoosePotion2":
			log_info("An elixir will be used by default.");
			pchar.GenQuest.Potion_choice = "potion2";
			DialogExit_Self();
		break;
		
		case "ChoosePotion3":
			log_info("A mixture will be used by default.");
			pchar.GenQuest.Potion_choice = "potion4";
			DialogExit_Self();
		break;
		
		case "ChoosePotion4":
			log_info("A ginger root will be used by default.");
			pchar.GenQuest.Potion_choice = "potion5";
			DialogExit_Self();
		break;
		
		case "ChoosePotion5":
			log_info("Rum will be used by default.");
			pchar.GenQuest.Potion_choice = "potionrum";
			DialogExit_Self();
		break;
		
		case "ChoosePotion6":
			log_info("Wine will be used by default.");
			pchar.GenQuest.Potion_choice = "potionwine";
			DialogExit_Self();
		break;
		
		case "ChoosePotion7":
			log_info("Potions will be selected automatically.");
			DeleteAttribute(pchar, "GenQuest.Potion_choice");
			DialogExit_Self();
		break;
		
		case "ChoosePotion8":
			DialogExit_Self();
		break;
		
		case "TalkSelf_StartWait":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
			PChar.GenQuest.CallFunctionParam = "LaunchTavernWaitScreen";
			DoQuestCheckDelay("CallFunctionParam", 0.1); // Нужно с задержкой, иначе - ГГ начинает крутиться
		break;
		
		case "TalkSelf_room_night":
			NextDiag.CurrentNode = NextDiag.TempNode;
			//AddDialogExitQuestFunction("TavernWaitDate_Night");
			TavernWaitDate("wait_night");
			DialogExit_Self();
		break;

		case "TalkSelf_room_day":
			NextDiag.CurrentNode = NextDiag.TempNode;
			//AddDialogExitQuestFunction("TavernWaitDate_Day");
			TavernWaitDate("wait_day");
			DialogExit_Self();
		break;
		//  захват города
		case "TalkSelf_TownAttack":
            int needCrew = 500;
			if(CheckOfficersPerk(pchar, "Troopers")) needCrew = 300;
            bOk = (GetPartyCrewQuantity(Pchar, true) >= needCrew) || bBettaTestMode;
			if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && bOk)
	        {
	            chr = GetCharacter(GetCharIDXForTownAttack(pchar.location));
	            if (chr.from_sea == Pchar.location.from_sea)
	            {
					Dialog.Text = "Potremmo iniziare a catturare la città, ma la nave non sopporterebbe a lungo le salve dei cannoni del forte, e non saremo in grado di inviare un gruppo di sbarco.";
	    			Link.l1 = "...";
	    			Link.l1.go = "exit";
	            }
	            else
	            {
					if (pchar.location == "Panama_ExitTown" || pchar.location == "Tortuga_ExitTown" || pchar.location == pchar.questTemp.SantaMisericordia.ColonyZapret + "_ExitTown") // patch-5
					{
						Dialog.Text = "No, non sono ancora così pazzo..";
	    				Link.l1 = "...";
	    				Link.l1.go = "exit";
					}
					else
					{
						if (pchar.location == "LosTeques_ExitTown")
						{
							Dialog.Text = "Non ha senso attaccare questa miniera senza prima raccogliere informazioni sull'oro e l'argento estratti lì. Altrimenti manderò i miei uomini a morire invano.";
							Link.l1 = "...";
							Link.l1.go = "exit";
						}
						else
						{
							Dialog.Text = "All'attacco "+GetCityName(chr.City)+".";
							if (CheckAttribute(pchar, "questTemp.Patria.SanJoseAttack") && pchar.location == "PortSpein_ExitTown") // Jason НСО
							{
								Link.l1 = "Smettila di fare il buffone! Fermati!";
								Link.l1.go = "exit";
								break;
							}
							if (CheckAttribute(pchar, "questTemp.Patria")) // Jason НСО
							{
								if (pchar.questTemp.Patria != "fail" || pchar.questTemp.Patria != "complete")
								{
									if (pchar.location == "Marigo_ExitTown" || pchar.location == "Villemstad_ExitTown")
									{
										Link.l1 = "Smettila di fare il buffone! Fermati!";
										Link.l1.go = "exit";
										break;
									}
								}
							}
							Link.l1 = "Alle armi!";
							Link.l1.go = "TalkSelf_TownAttack_Start";
		    			Link.l2 = "Fermati!";
							Link.l2.go = "exit";
						}
	    		}
	        }
	        }
	        else
	        {
				if(!CheckAttribute(Pchar, "GenQuestFort.StartAttack"))
				{
					Dialog.Text = "Heh! There aren't enough people in the crew; we need at least "+needCrew+" men.";
					Link.l1 = "...";
					Link.l1.go = "exit";
				}
				else
				{
					Dialog.Text = "Non disperdervi! Continuate con l'attacco!";
					Link.l2 = "...";
					Link.l2.go = "exit";				
				}			
			}
	    break;

		case "TalkSelf_TownAttack_Start":
	        NextDiag.CurrentNode = NextDiag.TempNode;

			Pchar.GenQuestFort.StartAttack = true;
		    Pchar.GenQuestFort.fortCharacterIdx = GetCharIDXForTownAttack(pchar.location);
		    DeleteQuestAttribute("Union_with_Escadra");
	        chr = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));
			if (isCityHasFort(chr.City))
			{
	        	SetLocationCapturedState(chr.from_sea, true);
	        }
	        else
	        {
	            SetLocationCapturedState(chr.Default, true); // для сухопутных
	        }
	        AddDialogExitQuest("Capture_Forts");
	        Ship_NationAgressive(chr, chr);
	        DialogExit_Self();
	    break;
	    // Зачислить рабов в команду  -->
		case "TalkSelf_SlavesToCrew":
	        if (GetCurCrewEscadr() >= GetMaxCrewAble())
	        {
	            Dialog.Text = "Nessuno degli schiavi è disposto a unirsi all'equipaggio.";
	            Link.l1 = "All'inferno con loro!";
	    		Link.l1.go = "exit";
	        }
	        else
	        {
	            if (GetCrewQuantity(pchar) >= GetMaxCrewQuantity(pchar))
	            {
	                Dialog.Text = "Non c'è spazio libero sulla nave per nuovi marinai.";
	                Link.l1 = "Ehi! Dovrò trasferire parte dell'equipaggio su un'altra nave.";
	        		Link.l1.go = "exit";
	            }
	            else
	            {
	                if (GetFreeCrewQuantity(pchar) <= GetCargoGoods(pchar, GOOD_SLAVES))
	                {
	                    pchar.GenQuest.SlavesToCrew = GetFreeCrewQuantity(pchar);
	                }
	                else
	                {
	                    pchar.GenQuest.SlavesToCrew = GetCargoGoods(pchar, GOOD_SLAVES);
	                }
	                Dialog.Text = "La tua ciurma può essere rifornita di "+pchar.GenQuest.SlavesToCrew+" schiavi che vogliono servire sotto di te. Vorresti accettare?";
	                Link.l1 = "Sì";
	        		Link.l1.go = "TalkSelf_SlavesToCrew_1";
	        		Link.l2 = "No";
	        		Link.l2.go = "exit";
	    		}
			}
		break;

		case "TalkSelf_SlavesToCrew_1":
			// belamour legendary edition перк получил время работы, старый метод не подходит
	        if (GetOfficersPerkUsing(pchar, "IronWill"))
	        {
	            AddCrewMorale(pchar, -makeint(sti(pchar.GenQuest.SlavesToCrew) / 5.0))
	        }
	        else
	        {
	            AddCrewMorale(pchar, -makeint(sti(pchar.GenQuest.SlavesToCrew) / 3.0))
	        }
			ChangeCharacterComplexReputation(pchar,"authority", -0.5);
	        // падение опыта -->
	        fTemp =  stf(GetCrewQuantity(pchar) + sti(pchar.GenQuest.SlavesToCrew));
	        pchar.Ship.Crew.Exp.Sailors   = (stf(pchar.Ship.Crew.Exp.Sailors)*GetCrewQuantity(pchar) + 
			                                        stf(pchar.Ship.Crew.Exp.Sailors)*0.3*sti(pchar.GenQuest.SlavesToCrew)) / fTemp;
			pchar.Ship.Crew.Exp.Cannoners   = (stf(pchar.Ship.Crew.Exp.Cannoners)*GetCrewQuantity(pchar) + 
			                                        stf(pchar.Ship.Crew.Exp.Cannoners)*0.3*sti(pchar.GenQuest.SlavesToCrew)) / fTemp;
			pchar.Ship.Crew.Exp.Soldiers   = (stf(pchar.Ship.Crew.Exp.Soldiers)*GetCrewQuantity(pchar) + 
			                                        stf(pchar.Ship.Crew.Exp.Soldiers)*0.3*sti(pchar.GenQuest.SlavesToCrew)) / fTemp;
			// падение опыта <-- 
			pchar.Ship.Crew.Quantity = sti(pchar.Ship.Crew.Quantity) + sti(pchar.GenQuest.SlavesToCrew); 
	        RemoveCharacterGoodsSelf(pchar, GOOD_SLAVES, sti(pchar.GenQuest.SlavesToCrew));       
			                            
	        NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
		break;
		// Зачислить рабов в команду  <--
		// boal <--

//navy CONTRABAND METRO -->
		case "GenTravel_Main":
			NextDiag.TempNode = "First time";
			dialog.Text = "Questa dolce nave è ora mia, e io sono il capitano qui! È un peccato che ho dovuto uccidere tutto l'equipaggio, però.";
			Link.l1 = "È ora di sbarcare...";
			Link.l1.go = "exit";

			chr = CharacterFromID("Abracham_Gray");
			chr.location = "none";
			SeaExchangeCharactersShips(PChar, chr, false, false);
			SetCrewQuantity(PChar, 0);

			//грузим ГГ куда нужно...
			SetAnyReloadToLocation(pchar.GenQuest.contraTravel.destination.loc, pchar.GenQuest.contraTravel.destination.group, pchar.GenQuest.contraTravel.destination.locator, "", 0, 0, 0, 0);
			AddDialogExitQuest("AnyReloadToLocation");
            chrDisableReloadToLocation = false;
            
			CloseQuestHeader("Gen_ContrabandTravel");
			setCharacterShipLocation(PChar, pchar.GenQuest.contraTravel.destination.loc);
			setWDMPointXZ(pchar.GenQuest.contraTravel.destination.loc);

			//трем аттрибуты
			DeleteAttribute(PChar, "GenQuest.contraTravel");
			break;
//navy CONTRABAND METRO <--

//navy --> 13.02.08
		case "Cabin_CompanionSelect":
			Dialog.Text = "Quale compagno convocare?";
			for (i = 1; i < GetCompanionQuantity(PChar); i++)
			{
				chr = GetCharacter(GetCompanionIndex(PChar, i));
				if (!CheckAttribute(chr, "Tasks.Clone") && sti(chr.Payment) == true)
				{
					sAttr = "l" + i;
					rShip = GetRealShip(sti(chr.Ship.Type));
					link.(sAttr) = GetFullName(chr) + " - " + xiStr(rShip.BaseName) + " '" + chr.Ship.Name + "'.";
					link.(sAttr).go = "CabinCompanionTalk_" + i;
				}
			}
			link.l9 = "Un altro momento.";
			link.l9.go = "exit";
			break;

		case "Cabin_Companion_Talk":
			i = sti(PChar.GenQuest.CabinCompanionNum);
			PlaceCompanionCloneNearMChr(i, false);

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
			break;
//navy <--

		//--> Голландский гамбит
		case "Seek_AbyIsland":
			bOk = CheckCharacterItem(pchar, "bussol") && CheckCharacterItem(pchar, "clock2");
			bool bOk1 = CheckCharacterItem(pchar, "sextant2");
			if (bOk || bOk1)
			{
				DialogExit();
				DeleteAttribute(pchar, "questTemp.HWIC_Coordinates");
				pchar.questTemp.HWIC_FindIsland = "true";
				AddDialogExitQuestFunction("PrepareSearchingFor");
			}
			else
			{
				dialog.text = "Peccato che non ho gli strumenti di navigazione necessari per determinare la latitudine e la longitudine. Dovrò cercare l'isola in un altro momento. ";
				link.l1 = "";
				link.l1.go = "exit";
			}
		break;
		//<-- Голландский гамбит
		
		//--> Ложный след
		case "FalseTrace_Cabin":
			dialog.text = "Bosun! Portami subito Adam Rayner!";
			link.l1 = "Sì sì, capitano!";
			link.l1.go = "exit";
			chr = characterFromId("Mugger");
			if (pchar.questTemp.FalseTrace == "CatchAdam") chr.dialog.currentnode = "FalseTrace_17";
			else chr.dialog.currentnode = "FalseTrace_7";
			pchar.questTemp.FalseTrace.CharID = "Mugger";
			AddDialogExitQuest("SetFalseTraceCharToCabin");
		break;
		
		case "FalseTrace_Woman":
			DialogExit();
			chr = characterFromId("FalseTraceWife");
			chr.dialog.currentnode = "FalseTrace_wife_6";
			pchar.questTemp.FalseTrace.CharID = "FalseTraceWife";
			AddDialogExitQuest("SetFalseTraceCharToCabin");
		break;
		//<-- Ложный след
		
		//--> LSC, приколы со стуком в дверь
		case "knock_2":
			PlaySound("interface\knock_2.wav");
			dialog.text = "Allora, ho bussato, ora aspettiamo la risposta...";
			link.l1 = "(aspetta)";
			link.l1.go = "knock_wrong";
		break;
		
		case "knock_3":
			PlaySound("interface\knock.wav");
			dialog.text = "Allora, ho bussato, adesso aspettiamo la risposta...";
			link.l1 = "(aspetta)";
			link.l1.go = "knock_wrong";
		break;
		
		case "knock_3_1":
			PlaySound("interface\knock_3_1.wav");
			dialog.text = "Allora, ho bussato, adesso aspettiamo la risposta...";
			link.l1 = "(aspetta)";
			link.l1.go = "knock_wrong";
		break;
		
		case "knock_1_3":
			PlaySound("interface\knock_1_3.wav");
			dialog.text = "Allora, ho bussato, ora aspettiamo la risposta...";
			link.l1 = "(aspetta)";
			link.l1.go = "knock_wrong";
		break;
		
		case "knock_2_2":
			PlaySound("interface\knock_2_2.wav");
			dialog.text = "Allora, ho bussato, ora aspettiamo la risposta...";
			link.l1 = "(aspetta)";
			link.l1.go = "knock_right";
		break;
		
		case "knock_wrong":
			dialog.text = "Non sta aprendo la porta... Suppongo di aver usato il tocco segreto sbagliato. Va bene, tornerò domani e proverò di nuovo. Oggi, di sicuro non aprirà la porta.";
			link.l1 = "(vai via)";
			link.l1.go = "exit";
		break;
		
		case "knock_right":
			PlaySound("interface\key.wav");
			PlaySound("Voice\English\YouFace.wav");
			dialog.text = "Caspita! Ha risposto e ha aperto la porta! Posso entrare adesso...";
			link.l1 = "(entra)";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.LSC.DiffIndoor");
			LocatorReloadEnterDisable("LostShipsCity_town", "reload74", false);
		break;
		//<-- LSC, приколы со стуком в дверь
		
		// суп из черепахи
		case "terrapin":
			PlaySound("Interface\Door_Kick.wav");
			PlaySound("Voice\English\EvilPirates02.wav");
			dialog.text = "Caramba! Quindi quella è la copertura ritardata per Levasseur... Non c'è modo che possa uscire dalla porta... Va bene, seguirò le orme di Thibaut - dalla finestra! Dopotutto, questo furfante è riuscito a scappare in qualche modo!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Terrapin_GoWindow");
		break;
		
		// защита Сен-Пьера
		case "SP_defend":
			PlaySound("Voice\English\military02.wav");
			dialog.text = "Allora, la nostra missione è respingere un attacco dei maledetti spagnoli e salvare Saint Pierre. Il forte è stato catturato e una battaglia si sta combattendo per le strade. C'è una potente squadra nella baia di Saint Pierre e hanno una nave di linea come nave ammiraglia. Attaccarla ora è inutile, il forte e la città sono sotto il controllo del nemico, quindi non ci lasceranno sbarcare in porto\nPertanto, ho deciso di muovermi attraverso le giungle e colpirli alle spalle attraverso le porte della città. Una volta che il forte e la città saranno liberati dagli spagnoli, ci occuperemo della squadra. Diventerà molto più vulnerabile senza il supporto di fuoco del forte\nNon sarà facile, quindi ho dato ordini di pagare centomila pesos extra da distribuire tra l'equipaggio in aggiunta al normale salario. Muoviamoci!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("DefendSP_GoJungle");
		break;
		
		// финал игры
		case "final_1": // Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor")) // генерал-губернатор никуда не уедет
			{
				dialog.text = "Aspetta, dove sto andando? Non posso lasciare il posto di Governatore Generale senza il permesso di Parigi! Altrimenti sarò sicuramente arrestato per l'abbandono non autorizzato delle colonie affidatemi quando tornerò in Francia. Parigi, mi mancherai ...";
				link.l1 = "";
				link.l1.go = "exit";
				EndQuestMovie();
			}
			else
			{
				dialog.text = "Allora non perdiamo più tempo! Mi mancano tanto i campi della mia cara Guascogna! Prendiamo il largo!";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuest("Final_ReturnToEurope");
			}
		break;
		
		case "final_2":
			dialog.text = "Credo che questa sia la decisione giusta! Cosa mi aspetta nella vecchia e buona Europa, quando mi sono trovato qui? Inoltre, posso tornare in Francia quando voglio, comunque!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Final_StayInCarribean"); // 010912
			DeleteAttribute(pchar, "questTemp.Tieyasal_final");
		break;
		
		// Addon-2016 Jason, французские миниквесты (ФМК) Сент-Кристофер
		case "FMQN_1":
			dialog.text = "Questo è il miglior modo. Dovrei salire a bordo e navigare via da qui.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_ChooseExit");
		break;
		
		case "FMQN_2":
			dialog.text = "Macché, non se ne parla, io resto. Ma dannazione, non starò qui ad aspettare chissà cosa. Dovrei navigare verso il porto di Philipsburg e indagare la situazione. L'idea di essere uno strumento nelle mani di qualche maledetto inglese bugiardo non mi va a genio.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_ChooseContinue");
		break;
		
		// Addon 2016-1 Jason Пиратская линейка
		case "mtraxx_ammo":
			Mtraxx_PlantCheckShoreBox(); // анализируем содержимое сундука
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Weapon.Blade") && !CheckAttribute(pchar, "questTemp.Mtraxx.Weapon.NoBlade")) // собрали 30 сабель
			{
				dialog.text = "Trenta pezzi di freddo acciaio sono nel baule! Dovrei fermarmi ora, o dovrei raccogliere più armi da fuoco, cariche e pozioni?";
				link.l1 = "Questo è abbastanza!";
				link.l1.go = "mtraxx_ammo_1";
				link.l2 = "No, dovrei continuare a riempire questo baule.";
				link.l2.go = "exit";
				// belamour legendary edition
				if(CheckAttribute(pchar,"questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "Full")
				{
					link.l3 = "Riempi con il contenuto del baule di Fadey e prendi l'eccesso."; 
					link.l3.go = "mtraxx_ammo_1";
				}
			}
			else
			{
				dialog.text = "Non ho ancora raccolto trenta pezzi di freddo acciaio! Dovrei portarne di più.";
				link.l1 = "";
				link.l1.go = "exit";
			}
		break;
		
		case "mtraxx_ammo_1":
			DelMapQuestMarkCity("baster");
			DelLandQuestMark(characterFromId("Fadey"));
            dialog.text = "Chiudendo a chiave il baule e facendo un piano per portarlo di nascosto alla piantagione.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantShoreBoxComplete");
		break;
		
		case "mtraxx_mutiny":
            dialog.text = "Vai, alla carica! Urrà!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantMutiny");
		break;
		
		case "mtraxx_boats":
            if (GetSquadronGoods(pchar, GOOD_PLANKS) >= 20 && GetSquadronGoods(pchar, GOOD_LEATHER) >= 10) // наличие материалов
			{
				if (Mtraxx_MeridaCheckCarpenter()) // наличие плотника
				{
					dialog.text = "Tutti i materiali necessari sono pronti, dovremmo iniziare a costruire le lunghe barche immediatamente.";
					link.l1 = "";
					link.l1.go = "exit";
					AddDialogExitQuestFunction("Mtraxx_MeridaBuildBoats");
				}
				else
				{
					dialog.text = "Non ho un falegname esperto in grado di svolgere il lavoro. Dovrei assegnare un ufficiale a questa posizione.";
					link.l1 = "";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Non ci sono abbastanza materiali, abbiamo bisogno di almeno 20 pacchi di assi più 10 balle di pelle.";
				link.l1 = "";
				link.l1.go = "exit";
			}
		break;
		
		case "mtraxx_powder":
            if (GetSquadronGoods(pchar, GOOD_POWDER) >= 300) // наличие пороха
			{
				if (GetCrewQuantity(pchar) >= 20) // наличие команды
				{
					dialog.text = "Tutto è pronto per una sbornia!";
					link.l1 = "";
					link.l1.go = "exit";
					AddDialogExitQuestFunction("Mtraxx_RetributionBarrels");
				}
				else
				{
					dialog.text = "Ho bisogno di almeno 20 uomini per consegnare la polvere da sparo.";
					link.l1 = "";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Non c'è abbastanza polvere da sparo, ne servono almeno 300.";
				link.l1 = "";
				link.l1.go = "exit";
			}
		break;
		
		case "mtraxx_dungeon":
			PlaySound("ambient\jail\jail_door2.wav");
            dialog.text = "È stata una porta?";
			link.l1 = "";
			link.l1.go = "mtraxx_dungeon_1";
		break;
		
		case "mtraxx_dungeon_1":
			PlaySound("ambient\jail\jail_door1.wav");
            dialog.text = "Giusto! Abbiamo visitatori ... Jan?..";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionRunToEnrico");
		break;
		// belamour legendary edition -->
		case "Good_Choice":
			pchar.questTemp.Mtraxx.Retribution.Choice = "good";
			DoQuestCheckDelay("Mtraxx_RetributionFreedom", 0.5); 
			DialogExit_Self();
		break;
		
		case "Bad_Choice":
			pchar.questTemp.Mtraxx.Retribution.Choice = "bad";
			Achievment_Set("ach_CL_97");
			bNoEatNoRats = false;
			LAi_SetPlayerType(pchar);
			AddQuestRecord("Roger_10", "18");
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			pchar.quest.mtraxx_line_complete.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_line_complete.function = "Mtraxx_RetributionComplete";
			DialogExit_Self();
		break;
		// <-- legendary edition
		
		// Jason Долго и счастливо
		case "LH_marry":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			string sTemp = sld.name;
			dialog.text = "Io e "+sTemp+"siamo stati insieme per molto tempo, e i nostri legami sono più forti di qualsiasi voto di chiesa, ma voglio che entrambi ricordiamo questo momento. Pertanto, devo decidere dove farle la proposta:";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				link.l1 = "Isla Tessoro - quest'isola ha un grande significato nella nostra storia. Suppongo, non c'è posto migliore - la baia di Sabu Matila è affascinante al tramonto!";
				link.l1.go = "LH_marry_1_1";
			}
			link.l2 = "Tortuga - un simbolo di libertà del nostro tempo, e la vista dal faro sullo stretto di Tortu è degna del pennello di qualsiasi pittore!";
			link.l2.go = "LH_marry_1_2";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l3 = "Giamaica - c'è così tanto da vedere! E ammirare l'alba a Portland Cove è come immaginare il Paradiso sulla terra.";
				link.l3.go = "LH_marry_1_3";
			}
		break;
		
		case "LH_marry_1_1":
			pchar.questTemp.LongHappy.Shore = "Shore_ship1";
			AddQuestRecord("LongHappy", "2_1");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestUserData("LongHappy", "sName", sTemp);
			dialog.text = "Ma non possiamo fare questo senza la solennità della chiesa - tutto dovrebbe essere secondo tutti i canoni in modo che mio padre sarebbe costretto ad accettare la mia scelta. Quindi, avrò bisogno di un prete, e non vedo nessuno degno di questa posizione oltre all'Abate Benoit. È un vecchio amico di mio padre e da lui hanno iniziato le mie avventure nel Nuovo Mondo. Penso che accetterà di farmi l'onore.";
			link.l1 = "";
			link.l1.go = "LH_marry_2";
		break;
		
		case "LH_marry_1_2":
			pchar.questTemp.LongHappy.Shore = "Mayak6";
			AddQuestRecord("LongHappy", "2_2");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestUserData("LongHappy", "sName", sTemp);
			dialog.text = "Ma non possiamo fare questo senza la solennità della chiesa - tutto dovrebbe essere secondo tutti i canoni in modo che mio padre sarebbe costretto ad accettare la mia scelta. Quindi, avrò bisogno di un prete, e non vedo nessuno degno di questa posizione oltre all'Abate Benoit. È un vecchio amico di mio padre e da lui iniziarono le mie avventure nel Nuovo Mondo. Penso che accetterà di farmi l'onore.";
			link.l1 = "";
			link.l1.go = "LH_marry_2";
		break;
		
		case "LH_marry_1_3":
			pchar.questTemp.LongHappy.Shore = "Shore36";
			AddQuestRecord("LongHappy", "2_3");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestUserData("LongHappy", "sName", sTemp);
			dialog.text = "Ma non possiamo fare questo senza la solennità della chiesa - tutto dovrebbe essere secondo tutti i canoni in modo che mio padre sarebbe costretto ad accettare la mia scelta. Quindi, mi servirà un prete, e non vedo nessuno degno di questa posizione oltre all'Abate Benoit. È un vecchio amico di mio padre e da lui sono iniziate le mie avventure nel Nuovo Mondo. Penso che accetterà di farmi l'onore.";
			link.l1 = "";
			link.l1.go = "LH_marry_2";
		break;
		
		case "LH_marry_2":
			AddQuestRecord("LongHappy", "3");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestUserData("LongHappy", "sName", sTemp);
			dialog.text = "Ebbene, questo può succedere senza la solennità dell'uomo. Anche se preferirei discutere di questo con "+sTemp+" un po' dopo.";
			link.l1 = "";
			link.l1.go = "exit";
			pchar.questTemp.LongHappy = "choose";
		break;
		
		case "LH_marry_3":
			dialog.text = "Bene, sono pronto!";
			link.l1 = "";
			link.l1.go = "exit";
			LongHappy_MarryOffer();
		break;
		
		case "LH_marry_4":
			if (LongHappy_CheckGoods())
			{
				dialog.text = "Tutto è preparato!";
				link.l1 = "";
				link.l1.go = "exit";
				LongHappy_OnIslaTesoro();
			}
			else
			{
				dialog.text = "Le merci necessarie e le monete non sono ancora state raccolte!";
				link.l1 = "";
				link.l1.go = "exit";
			}
		break;
	}
}

void  DialogExit_Self()
{
    DialogExit();
	locCameraSleep(false); //boal
}

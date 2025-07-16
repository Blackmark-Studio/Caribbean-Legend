// старпом Акулы - Лейтон Декстер
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Cosa vuoi, ragazzo? Parla con Squalo, qui comanda lui.";
				link.l1 = "Posso almeno salutarti, o è vietato pure quello dalle regole?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				if (CheckAttribute(npchar, "quest.map"))
				{
					link.l2 = "Layton, Squalo mi ha detto che possiedi una mappa dell’Isola. La vendi?";
					link.l2.go = "map";
				}
				dialog.text = "A-ah, "+GetFullName(pchar)+"! Hai affari con me, o vuoi solo ciarlare di nuovo? Se è così, la prossima volta porta una bottiglia di rum, ahah!";
				link.l1 = "No, non ho affari particolari per te. Porterò del rum la prossima volta, solo per te.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "Ah! Sei proprio uno spiritoso, ragazzo, eh? Va bene... Mi chiamo Layton Dexter, sono il secondo di Squali e, di questi tempi, il suo vice su questa maledetta Isola Giustizia. Nel frattempo vendo provviste e cerco di spillare qualche moneta a quel fannullone di Fazio.";
			link.l1 = "E il mio nome è "+GetFullName(pchar)+" Lieto d'incontrarti!";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// Акула погиб по варианту N
		case "admiral":
			dialog.text = "Suppongo tu abbia già sentito che Steven è morto. Sono stati i Narvali.";
			link.l1 = "Hai ragione, lo so bene... E allora, ora tu saresti l’ammiraglio?";
			link.l1.go = "admiral_1";
			AddQuestRecord("SharkHunt", "28");
			CloseQuestHeader("SharkHunt");
			bDisableFastReload = false; // belamour legendary edition	
		break;
		
		case "admiral_1":
			dialog.text = "Esatto. Chad è passato coi Narvali, Steven è crepato e dunque – essendo io il secondo, per natura ora comando io la flotta. Qualcuno ha qualcosa da ridire?";
			link.l1 = "No. Nessuna obiezione.";
			link.l1.go = "admiral_2";
		break;
		
		case "admiral_2":
			dialog.text = "Bene. Sentiamo le tue domande.";
			link.l1 = "Vuoi vendicarti dei Narvali per la morte di Steven?";
			link.l1.go = "admiral_3";
		break;
		
		case "admiral_3":
			dialog.text = "Vuoi sapere se dichiarerò guerra, eh? No, ci sono modi migliori per farli pagare. Prima di tutto triplicherò il prezzo delle provviste che devono sborsare.\nSe attaccano la 'San Augustine', li accoglieremo a cannonate. Poi tratterò con i Rivados. Certo, non ci si può fidare di quei luridi bastardi e ci odiano ancora per la morte del loro stregone, ma ogni rancore si scioglie con un po’ di rum e da mangiare.";
			link.l1 = "Capisco. Va bene, Layton, devo andare...";
			link.l1.go = "admiral_4";
		break;
		
		// нода пересечения
		case "admiral_4":
			dialog.text = "Aspetta. Steven mi ha detto che stai cercando in qualche modo di lasciare la Città delle Navi Abbandonate e di tornare qui su una nave?";
			link.l1 = "Questo è il piano.";
			link.l1.go = "admiral_5";
		break;
		
		case "admiral_5":
			dialog.text = "Prendi queste istruzioni di navigazione. Con loro potrai tornare qui via mare sano e salvo. Voglio dire: non ti schianterai sugli scogli, la corrente non ti trascinerà via e la tua nave non finirà sfasciata contro i relitti sul bordo esterno. Senza queste dritte, non troverai mai il passaggio, oppure la tua nave farà compagnia alle altre carcasse che vedi qui. Ricorda, per passare tra le secche ti serve una barca piccola, dal pescaggio leggero. Un lugger, una goletta, una brigantina, al massimo una bricchetta... niente di più grosso di una quarta classe, intesi?";
			link.l1 = "Aye, lo faccio. Grazie! Proprio quel che mi serviva.";
			link.l1.go = "admiral_6";
		break;
		
		case "admiral_6":
			GiveItem2Character(pchar, "LSC_navigation_map");
			dialog.text = "Non scordarti di riempire la stiva di provviste. Te le vendo a buon prezzo. Non mostrare questo documento a nessuno, la nostra base deve restare segreta. Te lo do solo perché lo stesso Steven voleva consegnartelo, e tu sei amico di Jan Svenson.";
			link.l1 = "Non preoccuparti per quello. Grazie ancora e ci si rivede in giro!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Dexter_wait";
			AddQuestRecord("LSC", "5");
			CloseQuestHeader("SharkHunt");
			bDisableFastReload = false; // belamour legendary edition
			// убираем квестовые предметы
			sld = ItemsFromID("key_capper");
			sld.price = 10;
			if (CheckCharacterItem(pchar, "letter_chad")) RemoveItems(pchar, "letter_chad", 1);
		break;
		
		case "Dexter_wait":
			dialog.text = "Hai fatto qualche progresso nel fuggire da questa Città delle Navi Perdute, "+pchar.name+"?";
			link.l1 = "Nessun progresso ancora, Layton. Ci sto lavorando.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Dexter_wait";
		break;
		
		// Акула погиб по варианту M
		case "admiral_7":
			dialog.text = "Eccoti, "+pchar.name+"   Ho alcune questioni di cui parlare con te. ";
			link.l1 = "Per quel che ho capito, hai preso il posto di Steven dopo la sua morte. Allora adesso sei tu l’ammiraglio?";
			link.l1.go = "admiral_8";
		break;
		
		case "admiral_8":
			dialog.text = "Esatto. Essendo il secondo in comando, ora sono io l’ammiraglio. Qualcuno ha da ridire?";
			link.l1 = "Nessuna obiezione. Hai tutto il diritto di mantenere questa posizione.";
			link.l1.go = "admiral_9";
		break;
		
		case "admiral_9":
			dialog.text = "Sono lieto che ci intendiamo. Fammi sapere se ti serve qualcosa.";
			link.l1 = "Intendi vendicarti dei Narvali per la morte di Steven?";
			link.l1.go = "admiral_10";
		break;
		
		case "admiral_10":
			dialog.text = "Vuoi sapere se dichiarerò guerra, eh? No. Ci sono modi più furbi per fargliela pagare. Triplicherò il prezzo che dovranno sborsare per le provviste.\nSe oseranno attaccare la 'San Augustine', gliela faremo vedere noi. E poi, ora siamo in buoni rapporti coi Rivados, quindi i Narvali non rischieranno la pelle per qualche sciocchezza.";
			link.l1 = "Capisco. Vuoi aggiungere qualcos'altro? Oppure posso andare ora?";
			link.l1.go = "admiral_4";
		break;
		
		case "plan":
			PlaySound("Voice\English\LSC\Layton Dexter-07");
			dialog.text = "Già. Vedo solo una via per prenderci i Narvali. Non è la più raffinata, ma non scorgo altre possibilità. Li attaccheremo da due fronti: un branco di tagliagole arditi salirà a bordo della 'Ceres Smithy' con le scialuppe, mentre un altro gruppo, insieme ai Rivados, assalterà la 'Esmeralda'. O li spazzeremo via del tutto, oppure li costringeremo a rifugiarsi sulla 'San Gabriel'. La seconda opzione è la più probabile: la San Gabriel è una fortezza maledetta e assediarla richiederà tempo. Ma comunque vada, la vittoria sarà nostra.";
			link.l1 = "";
			link.l1.go = "plan_1";
		break;
		
		case "plan_1": // ноду Акуле
			DialogExit();
			npchar.greeting = "dexter_1";
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "whyskey_final_3";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_CharacterEnableDialog(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
			NextDiag.CurrentNode = "plan_2";
		break;
		
		case "plan_2":
			dialog.text = "Stiamo attendendo le conseguenze del tuo colloquio con Donald Greenspen. È una faccenda di gran peso, dunque non perdere tempo, per l’amor d’Iddio.";
			link.l1 = "Sto arrivando!";
			link.l1.go = "exit";
			NextDiag.TempNode = "plan_2";
		break;
		
		case "map":
			dialog.text = "Sì, ho la mappa. La vuoi acquistare? Fai pure, se ti va. Sarà tua per appena duecento dobloni.";
			link.l1 = "E i pesos, che mi dici?";
			link.l1.go = "map_1";
		break;
		
		case "map_1":
			dialog.text = "No. Voglio oro. Nessuna trattativa, punto e basta.";
			if (GetCharacterItem(pchar, "gold_dublon") >= 200)
			{
				link.l1 = "D'accordo. Prendi il tuo oro, accetto.";
				link.l1.go = "map_2";
			}
			link.l2 = "Non ho così tanto oro. Forse più tardi...";
			link.l2.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "map_2":
			RemoveItems(pchar, "gold_dublon", 200);
			PlaySound("interface\important_item.wav");
			Log_Info("You have received a map of the City of Abandoned Ships");
			GiveItem2Character(pchar, "map_LSC");
			dialog.text = "Bell’affare, ragazzo! Prendi la tua mappa. Vale ogni moneta – ho strisciato per tutta la Città una settimana intera per disegnarla, quindi di fatto te l’ho lasciata per due soldi.";
			link.l1 = "A buon mercato?! Eh già. Beh, grazie lo stesso.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			DeleteAttribute(npchar, "quest.map");
		break;
		
		// геймовер диким геймерам за издевательство над игрой
		case "LSC_GameOverPrison":
			dialog.text = "Fermo lì, compare! Sì, lo Squalo aveva ragione, questo qui ha perso il senno. A causa sua sono crepati un mucchio di uomini... Legatelo, ragazzi, e buttatelo nella stiva!";
			link.l1 = "...";
			link.l1.go = "LSC_GameOverPrison_1";
		break;
		
		case "LSC_GameOverPrison_1":
			DialogExit();
			DoQuestReloadToLocation("TartarusPrison", "quest", "prison4", "LSC_GameOverInPrison");
		break;
		
		case "return":
			dialog.text = "Steven m’ha fatto ammiraglio della Città al suo posto – suppongo che tu e lui torniate insieme nei Caraibi. Io rimarrò qui a mandare avanti gli affari: io e Steven non vorremmo mai perdere una base così preziosa. E sappi che sarai sempre ospite gradito su questa Isola.";
			link.l1 = "Grazie, Layton. Credo che farò spesso ritorno sulla tua Isola Giustizia.";
			link.l1.go = "return_1";
		break;
		
		case "return_A":
			dialog.text = "Ah, mio vecchio amico "+GetFullName(pchar)+"! Sei riuscito a trovare la Città delle Navi Perdute seguendo le indicazioni di Steven, vero? Sono davvero, davvero felice di vederti. Qui sarai sempre un ospite gradito.";
			link.l1 = "Grazie, Layton. Credo che farò spesso ritorno alla tua Città.";
			link.l1.go = "return_1";
		break;
		
		int iTrade = GetSquadronGoods(pchar, GOOD_FOOD)-GetCrewQuantity(pchar);
		int iMoney = 0;
		case "return_1":
			dialog.text = "Molto bene. Avete da mangiare da vendere? Son pronto a comprarvelo al doppio del prezzo solito.";
			if (iTrade > 0)
			{
				link.l1 = "Sì, posso venderti qualche provvista.";
				link.l1.go = "trade";
			}
			link.l2 = "Sfortunatamente, al momento non ho nulla da venderti.";
			link.l2.go = "return_2";
			npchar.quest.foodqty = 0; // предел затарки складов = 15 000
		break;
		
		case "return_2":
			dialog.text = "Peccato. Non scordarti di portarlo la prossima volta – ti pagherò a dovere.";
			link.l1 = "D'accordo. Cercherò di non scordarmene...";
			link.l1.go = "exit";
			NextDiag.TempNode = "head";
		break;
		
		case "trade":
			dialog.text = "Quanto vuoi?";
			link.l1.edit = 4;
			link.l1 = "";	
			link.l1.go = "trade_1";
		break;
		
		case "trade_1":
			iTemp = dialogEditStrings[4];
			int iMax = GetSquadronGoods(pchar, GOOD_FOOD)-GetCrewQuantity(pchar);
			if (iTemp <= 0 || iTemp > GetSquadronGoods(pchar, GOOD_FOOD))
			{
				dialog.text = "Accidenti, sei ubriaco fradicio, compare! Mi hai davvero stupito! Vai a farti una dormita, poi parliamo d’affari più tardi.";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
			break;
			}
			if (iTemp <= 50)
			{
				dialog.text = "Non mi alzo nemmeno dal sedere per una miseria simile. Portami di più!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
			break;
			}
			if (iTemp > iMax)
			{
				dialog.text = "E come pensi di salpare senza provviste a bordo, compare? Vuoi forse che i tuoi uomini crepino di fame? Tieniti almeno "+FindRussianQtyString(GetCrewQuantity(pchar))+" per conto tuo.";
				link.l1 = "Hm, hai ragione.";
				link.l1.go = "exit";
			break;
			}
			if (iTemp >= 15000) // лесник
			{
			 iTemp = (15000 - sti(npchar.quest.foodqty))	
             dialog.text = "Accidenti, compare, è troppo per noi! Non riusciremo a mangiarlo tutto prima che marcisca. Ora non posso prenderne più di "+iTemp+".";
			 link.l1 = "Come vuoi, amico.";
			 link.l1.go = "trade_3";
			 break;
            }							  
			iMoney = (50+hrand(5, "&Slayer"))*iTemp;
			dialog.text = ""+FindRussianQtyString(iTemp)+"? Va bene. Ti pagherò "+FindRussianMoneyString(iMoney)+"Affare fatto?";
			link.l1 = "Certo! Un piacere fare affari con te!";
			link.l1.go = "trade_2";
			link.l2 = "Hm. No, ho cambiato idea.";
			link.l2.go = "exit";
			NextDiag.TempNode = "head";
		break;
		case "trade_3": // лесник 
		    iTemp = (15000 - sti(npchar.quest.foodqty))	
		    iMoney = (50+hrand(5, "&Slayer"))*iTemp;
			dialog.text = "Affare fatto. Ti pagherò "+FindRussianMoneyString(iMoney)+" per la merce. Basterà?";
			link.l1 = "Certo! Buoni scambi!";
			link.l1.go = "trade_4";
			link.l2 = "Hm. No, ho cambiato idea.";
			link.l2.go = "exit";
			NextDiag.TempNode = "head";
		break;
		case "trade_4": // лесник 
		    iTemp = (15000 - sti(npchar.quest.foodqty))	
			iMoney = (50+hrand(5, "&Slayer"))*iTemp;
			AddMoneyToCharacter(pchar, iMoney);
			RemoveCharacterGoods(pchar, GOOD_FOOD, iTemp);
			npchar.quest.foodqty = sti(npchar.quest.foodqty)+iTemp;
			if(!CheckAttribute(pchar,"Achievment.LSCfood")) pchar.Achievment.LSCfood = iTemp;
			else pchar.Achievment.LSCfood = sti(pchar.Achievment.LSCfood) + iTemp;
			if(sti(pchar.Achievment.LSCfood) >= 20000) Achievment_Set("ach_CL_112");
			if (sti(npchar.quest.foodqty) >= 15000) // склады затарены на полгода
			{
				SetFunctionTimerCondition("LSC_ClearFoodStorage", 0, 0, 180, false);
				dialog.text = "Maledizione ai miei occhi! Il mio magazzino è pieno zeppo! Non avrò bisogno di comprare provviste per i prossimi sei mesi.";
				link.l1 = "Bene. Allora tra sei mesi ti porterò il prossimo carico di viveri.";
				link.l1.go = "exit";
				AddQuestRecord("LSC", "25");
			}
			else
			{
				dialog.text = "Magnifico! Portami dell’altro la prossima volta.";
				link.l1 = "Certo!";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "head";
		break;
		case "trade_2":
			iTemp = dialogEditStrings[4];
			iMoney = (50+hrand(5, "&Slayer"))*iTemp;
			AddMoneyToCharacter(pchar, iMoney);
			RemoveCharacterGoods(pchar, GOOD_FOOD, iTemp);
			npchar.quest.foodqty = sti(npchar.quest.foodqty)+iTemp;
			if(!CheckAttribute(pchar,"Achievment.LSCfood")) pchar.Achievment.LSCfood = iTemp;
			else pchar.Achievment.LSCfood = sti(pchar.Achievment.LSCfood) + iTemp;
			if(sti(pchar.Achievment.LSCfood) >= 20000) Achievment_Set("ach_CL_112");
			if (sti(npchar.quest.foodqty) >= 15000) // склады затарены на полгода
			{
				SetFunctionTimerCondition("LSC_ClearFoodStorage", 0, 0, 180, false);
				dialog.text = "Bene! Il mio magazzino è pieno ormai. Non dovrò comprare vettovaglie per almeno mezzo anno.";
				link.l1 = "Bene. Allora ti porterò la prossima partita di provviste tra sei mesi.";
				link.l1.go = "exit";
				AddQuestRecord("LSC", "25");
			}
			else
			{
				dialog.text = "Magnifico! Portamene ancora la prossima volta.";
				link.l1 = "Certo!";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "head";
		break;
		
		case "head": // стандартный диалог Декстера-адмирала
			dialog.text = "A-ah, "+GetFullName(pchar)+"! Felice di vederti! Che ti porta qui?";
			if (iTrade > 0 && sti(npchar.quest.foodqty) < 15000)
			{
				link.l1 = "Vuoi comprare un po' di provviste da me?";
				link.l1.go = "trade";
			}
			link.l2 = "Non è nulla, volevo solo sapere come te la passi.";
			link.l2.go = "exit";
			NextDiag.TempNode = "head";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

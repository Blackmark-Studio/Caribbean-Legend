// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Vai avanti, cosa desideri?","Ne stavamo proprio parlando. Devi aver dimenticato...","Questa è la terza volta oggi che parli di qualche domanda...","Ascolta, questo è un negozio. Le persone comprano roba qui. Non disturbarmi!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sai, "+NPChar.name+", forse la prossima volta.","Giusto, ho dimenticato per qualche motivo...","Sì, è davvero la terza volta...","Mm, non lo farò...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			/* //--> Бремя гасконца
			if (!CheckAttribute(npchar, "quest.storehelper") && pchar.questTemp.Sharlie == "ship")
			{
				Link.l1 = "Ascolta, signore, sto cercando un lavoro. Non un lavoro a tempo pieno o trasportare sacchi di merce, ma più come fare commissioni, per così dire. Hai per caso bisogno di assistenza?";
				Link.l1.go = "Sharlie_storehelper";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "return")
			{
				Link.l1 = "Ho completato il tuo incarico. Ho trovato Gralam Lavoie.";
				Link.l1.go = "Sharlie_storehelper_2";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "choise")
			{
				Link.l1 = "Incontra il tuo nuovo assistente, signore.";
				Link.l1.go = "Sharlie_storehelper_11";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "final")
			{
				Link.l1 = "Son tornato, signore. Sono venuto per la mia ricompensa.";
				Link.l1.go = "Sharlie_storehelper_13";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
			{
				link.l1 = "Dai un'occhiata a questi orecchini, signore. Li ho trovati sul corpo di un bandito ucciso nella giungla. Questo è chiaramente il lavoro di un fine gioielliere che, ne sono sicuro, non è di queste parti. C'è qualcosa che puoi dire su questi orecchini?";
                link.l1.go = "Sharlie_junglejew";
			}
			//<-- Бремя гасконца */
		break;
		
		//--> Бремя гасконца
		case "Sharlie_storehelper":
			if (FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE) == "") 
			{
				dialog.text = "Mi scusi, signore, ma dov'è la sua spada? Non è sicuro lasciare la città senza un'arma da taglio. Non si sa mai cosa potrebbe succedere nella giungla!";
				link.l1 = "Maledizione, ho completamente dimenticato! Tutto è stato portato via!";
				link.l1.go = "Store_noweapon";
				break;
			}
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("Fortfrance_town", "reload", "reload6_back");
			dialog.text = "Un lavoro? Hm. Suppongo, ho un lavoro che potrebbe interessarti. Il mio assistente è scomparso, lavorava nel mio magazzino. È sparito da una settimana e questo è dannatamente fastidioso, perché sono costretto a fare i suoi compiti e non ho tempo\nPer favore, trova questo idiota e scopri perché diavolo ha abbandonato il suo lavoro. O ancora meglio - riportamelo. Ti pagherò mille pezzi di otto.";
			link.l1 = "Bene, sono dentro. Dimmi il suo nome e descrivi il suo aspetto. Hai qualche idea di dove cercarlo?";
			link.l1.go = "Sharlie_storehelper_1";
			link.l2 = "Cercare un uomo che Dio sa dove per un misero migliaio? Devi scherzare!";
			link.l2.go = "Sharlie_storehelper_exit";
			npchar.quest.storehelper = "true";
		break;
		
		case "Sharlie_storehelper_exit":
			AddTimeToCurrent(2,0);
			LocatorReloadEnterDisable("Fortfrance_town", "reload10_back", false);// пу откр
			dialog.text = "Ehi, signore. Chi sta cercando un lavoro, tu o io? Se non vuoi, non ti sto costringendo. Buona giornata.";
			link.l1 = "Hm... Think I'll go check the port authority; perhaps they'll offer something more substantial there.";
			link.l1.go = "exit";
		break;
		
		case "Sharlie_storehelper_1":
			dialog.text = "Si chiama Gralam Lavois. Come si presenta? Ha trentacinque anni, barba e baffi, indossa un lungo cappotto marrone, camicia bianca. Oh, e indossa sempre quel ridicolo tricorno, finge di essere un ammiraglio con un'ancora nel sedere\nNon è a Saint Pierre, ho controllato tutta la città. Deve essere nella giungla o a Les Francois, nascosto con i pirati che si aggirano là.\nD'altro canto, è probabilmente nell'insediamento pirata di Le Francois, che si trova nella parte orientale della nostra isola. Forse sta chiacchierando con i pirati lì, o trascorre il tempo nella taverna, o ha una discussione con il mercante locale al negozio.\nCome arrivare a Le Francois? Esci dalla città attraverso le porte, entra nella giungla, al bivio prendi il sentiero a sinistra, poi segui la strada fino a quando non giri a destra, e poi prendi il passaggio a sinistra tra le rocce, e troverai Le Francois. Non credo che ti perderai.";
			link.l1 = "Bene. Comincerò a cercare. Non appena trovo qualcosa, ti informerò subito.";
			link.l1.go = "exit";
			AddQuestRecord("SharlieA", "1");
			pchar.questTemp.Sharlie.Storehelper = "true";
			pchar.questTemp.Sharlie.Storehelper.Chance = rand(2);
			AddDialogExitQuestFunction("Sharlie_CreateStorehelper");
			// Rebbebion, новые марки до места назначения
			QuestPointerToLoc("fortfrance_town", "reload", "gate_back");
			QuestPointerToLoc("fortfrance_exittown", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_01", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_02", "reload", "reload3_back");
			QuestPointerToLoc("lefransua_exittown", "reload", "reload1_back");
		break;
		
		case "Sharlie_storehelper_2":
			DelLandQuestMark(npchar);
			// Rebbebion, новые марки до места назначения
			QuestPointerDelLoc("lefransua_town", "reload", "gate_back");
			QuestPointerDelLoc("lefransua_exittown", "reload", "reload2_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerDelLoc("fortfrance_town", "reload", "reload6_back");
			dialog.text = "Oh davvero? E dov'è lui?";
			link.l1 = "L'ho trovato a Le Francois. Non lavorerà più per te. Ha anche aggiunto un sacco di cose piuttosto salate su di te... Saresti interessato a sentirlo?";
			link.l1.go = "Sharlie_storehelper_3";
		break;
		
		case "Sharlie_storehelper_3":
			dialog.text = "No. Risparmiami i dettagli... Che peccato! Cosa farò ora senza un assistente?";
			link.l1 = "Assumi qualcun altro. O è davvero un problema così grande come ha detto Gralam?";
			link.l1.go = "Sharlie_storehelper_4";
		break;
		
		case "Sharlie_storehelper_4":
			dialog.text = "Sfortuna marcita, davvero. E cosa ha detto quel fannullone?";
			link.l1 = "Ebbene, per cominciare, è ovvio che non sta perdendo tempo, eh-eh. Ha detto che nessuno a Saint Pierre si arruolerebbe per te perché... non paghi abbastanza i tuoi lavoratori. Sì, a proposito, "+npchar.name+", devi mille pesos come promesso.";
			link.l1.go = "Sharlie_storehelper_5";
		break;
		
		case "Sharlie_storehelper_5":
			AddMoneyToCharacter(pchar, 1000);
			dialog.text = "Per favore, prendi i tuoi soldi. Ah! Non pago abbastanza! Certo, nessuno vuole lavorare per me. Quel bastardo ha fatto del suo meglio per diffondere pettegolezzi. Che posso fare? Non posso fare tutto da solo!\nNon posso andare a dormire finché non conto ogni pezzo di carico perché quei maledetti lavoratori rubano sempre qualcosa. Dopo l'ultimo carico mi mancano cinque barili di rum. Sono sicuro che i lavoratori li hanno 'presi per errore'...";
			link.l1 = "Ebbene, non so cosa consigliare. Va bene, tutto il meglio. È ora per me di andare.";
			link.l1.go = "Sharlie_storehelper_6";
		break;
		
		case "Sharlie_storehelper_6":
			dialog.text = "Aspetta! Penso che tu possa aiutarmi. Se sei riuscito a scovare quel bastardo, allora potresti essere capace di...";
			link.l1 = "E cosa potrei fare io mi chiedo, se nessuno in questa città crede a te? Sono nuovo qui e...";
			link.l1.go = "Sharlie_storehelper_7";
		break;
		
		case "Sharlie_storehelper_7":
			dialog.text = "Lasciami finire, signore. Sei stato a Le Francois. Vorrei che tu ci tornassi e cercassi un impiegato per me. Forse, Gralam non ha completamente rovinato la mia reputazione in questa tana di pirati\nIl lavoro è facile - contare la merce e sorvegliare i lavoratori del porto per prevenire furti. A volte fare il mio lavoro qui al posto mio mentre sono via, per un extra compenso naturalmente\nDì loro che offro una stanza nel negozio per vivere e cinquecento pezzi di otto a settimana. Monsieur, stavo pensando di espandere la mia attività e finalmente le cose stanno andando bene, ho bisogno di un assistente!\nTra l'altro, è meglio chiedere aiuto per trovare un lavoratore al locandiere locale, Cesare Craig. Quel furfante ti aiuterà sicuramente, anche se non gratuitamente, a trovare individui interessati a lavorare per me.";
			link.l1 = "Hm. Posso provare, anche se non ne sono sicuro... Quanto mi pagherai per il lavoro?";
			link.l1.go = "Sharlie_storehelper_8";
		break;
		
		case "Sharlie_storehelper_8":
			dialog.text = "Questo dipenderà dal lavoratore che sarai in grado di assumere. Più sarà bravo, più ti pagherò per i tuoi sforzi. È giusto, non è vero?";
			link.l1 = "Non pensi che mi stai costringendo a navigare alla cieca? Come faccio a sapere come valuterai un lavoratore? Potresti classificare chiunque come cattivo o...";
			link.l1.go = "Sharlie_storehelper_9";
		break;
		
		case "Sharlie_storehelper_9":
			dialog.text = "Signore! Potrebbe essere del tutto corretto chiamarmi un po' avaro, ma nessuno potrebbe chiamarmi disonesto! Se ti dico che pagherò per i tuoi sforzi a seconda di come va, allora lo intendo. Vedilo anche dal mio punto di vista. Potresti portarmi qui qualche zingaro pigro che non solo se ne starebbe a zonzo a fare nulla, ma potrebbe addirittura derubarmi di notte!";
			link.l1 = "Va bene. Sono d'accordo. Mi fido della tua parola, "+npchar.name+". Sarò sicuro di non riportare zingari.";
			link.l1.go = "Sharlie_storehelper_10";
		break;
		
		case "Sharlie_storehelper_10":
			DialogExit();
			SetLaunchFrameFormParam("Back to Le Francois...", "Reload_To_Location", 0, 3.0);
			SetLaunchFrameReloadLocationParam("LeFransua_tavern", "reload", "reload1", "SharlieA_TeleportLF");
			LaunchFrameForm();
		break;
		
		case "Sharlie_storehelper_11":
			dialog.text = "Hai trovato un lavoratore per me? Meraviglioso. Permettimi di parlare con lui, torna tra un'ora per la tua ricompensa.";
			link.l1 = "Va bene. Tornerò tra un'ora.";
			link.l1.go = "Sharlie_storehelper_12";
			DelLandQuestMark(npchar);
		break;
		
		case "Sharlie_storehelper_12":
			chrDisableReloadToLocation = false;//открыть локацию
			pchar.questTemp.Sharlie.Storehelper = "final";
			DialogExit();
			SetLaunchFrameFormParam("One hour passed...", "", 0, 5);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0); //крутим время
			RecalculateJumpTable();
			AddQuestRecord("SharlieA", "5");
			AddLandQuestMark(npchar, "questmarkmain");
		break;
		
		case "Sharlie_storehelper_13":
			switch (sti(pchar.questTemp.Sharlie.Storehelper.Quality))
			{
				case 0:
					AddMoneyToCharacter(pchar, 3000);
					dialog.text = "Sono piuttosto contento del lavoratore che hai trovato per me, anche se parla molto più di quanto lavora, ma non preoccuparti, gli farò smettere di chiacchierare in poco tempo. La tua ricompensa è di tremila pezzi di otto. Ecco a te.";
					link.l1 = "Grazie! Mi dica, signore, sa se qualcun altro in città potrebbe aver bisogno di aiuto con qualche questione importante?";
					link.l1.go = "Sharlie_storehelper_14a";
				break;
				
				case 1:
					AddMoneyToCharacter(pchar, 5000);
					dialog.text = "Sei riuscito a trovare un lavoratore davvero prezioso! È persino meglio di quel furfante di Gralam. Sono molto, molto soddisfatto, signore. Ecco, prendi la tua ricompensa - cinquemila pezzi di otto.";
					link.l1 = "Grazie! Mi dica, signore, sa se c'è qualcuno in città che potrebbe aver bisogno di aiuto per qualche questione importante?";
					link.l1.go = "Sharlie_storehelper_14a";
				break;
				
				case 2:
					AddMoneyToCharacter(pchar, 4000);
					dialog.text = "Hai trovato un buon lavoratore. E anche se non conosce tutti i trucchi del mestiere, sono sicuro che se la caverà senza troppi problemi. Sono contento di te, signore. Ecco, prendi la tua ricompensa - quattromila pezzi di otto.";
					link.l1 = "Grazie! Mi dica, Monsieur, sa se qualcuno in città potrebbe aver bisogno di aiuto per qualche questione importante?";
					link.l1.go = "Sharlie_storehelper_14a";
				break;
			}
		break;
		
		case "Sharlie_storehelper_14a":
			LocatorReloadEnterDisable("Fortfrance_town", "reload10_back", false);// пу откр
			dialog.text = "Mmm... Proprio di recente, ho visto il capo del porto, chiaramente turbato, dirigendosi verso l'autorità portuale. Verifica con lui, chissà cosa potrebbe essere successo.";
			link.l1 = "Farò proprio così. Grazie, Monsieur.";
			link.l1.go = "Sharlie_storehelper_14";
			DelLandQuestMark(npchar);
		break;
		
		case "Sharlie_storehelper_14":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Sharlie.Storehelper");
			CloseQuestHeader("SharlieA");
			
			QuestPointerDelLoc("lefransua_town", "reload", "gate_back");
			QuestPointerDelLoc("lefransua_exittown", "reload", "reload2_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerDelLoc("fortfrance_town", "reload", "reload6_back");
			
			QuestPointerToLoc("fortfrance_town", "reload", "reload10_back");
		break;
		
		case "Sharlie_junglejew":
			dialog.text = "Ebbene, cosa dovrei dire, orecchini magnifici. Posso darti... vediamo... quattromila pezzi di otto per loro. Dubito che qualcuno ti offrirà di più. Abbiamo un accordo?";
			link.l1 = "Affare fatto! Sono tuoi.";
			link.l1.go = "Sharlie_junglejew_1";
			link.l2 = "No. Credo che terrò questi gioielli per me stesso.";
			link.l2.go = "exit";
			npchar.quest.junglejew = "true";
		break;
		
		case "Sharlie_junglejew_1":
			DialogExit();
			PlaySound("interface\important_item.wav");
			Log_Info("You've given the earrings");
			RemoveItems(pchar, "jewelry25", 1);
			AddMoneyToCharacter(pchar, 4000);
			AddQuestRecord("SharlieE", "4");
			CloseQuestHeader("SharlieE");
			DeleteAttribute(pchar, "questTemp.Sharlie.Junglejew");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
			{
				DelLandQuestMark(characterFromId("FortFrance_Mayor"));
			}
		break;
		
		case "Store_noweapon":
			dialog.text = "Questo non basterà. Suggerisco di rivolgerti al nostro governatore e chiedere il suo aiuto.";
			link.l1 = "Grazie per il consiglio. È quello che intendo fare.";
			link.l1.go = "exit";
		break;
		//<-- Бремя гасконца
	}
	UnloadSegment(NPChar.FileDialog2);
}

// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quali domande hai?","Come posso aiutarti?"),"Hai cercato di farmi quella domanda non molto tempo fa...","Sì, lascia che indovini... Ancora una volta girando in tondo?","Ascolta, io gestisco le finanze qui, non rispondo alle domande...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea...","Non ho nulla di cui parlare al momento."),"Umph, dove se n'è andata la mia memoria...","L'hai indovinato, mi dispiace...","Capisco...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			/* //--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
			{
				link.l1 = "Dai un'occhiata a questi orecchini, signore. Li ho trovati nella tasca di un bandito nella giungla. Questo è chiaramente il lavoro di un fine gioielliere che, ne sono sicuro, non proviene da questa selva. Che ne dici?";
                link.l1.go = "Sharlie_junglejew";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskiper")
			{
				link.l1 = "So che avete un debitore di nome Folke Deluc. Ditemi, quanto è grave la sua... morosità?";
                link.l1.go = "Sharlie";
			}	
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskipermoney")
			{
				link.l1 = "Sono qui per il debito di Folke Deluc.";
                link.l1.go = "Sharlie_repeat";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskipercaptive")
			{
				link.l1 = "Ho completato il vostro incarico, signore. Ecco il vostro... amico spagnolo.";
                link.l1.go = "Sharlie_14";
			}
			//<-- Бремя гасконца */
			
			//--> Миниквест "Делюк" (Делюк снова попал в тюрьму)
			if (CheckAttribute(pchar, "questTemp.Del_Rostovshik"))
			{
				link.l1 = "Sono qui per...";
                link.l1.go = "Del_Deluck";
			}
			if (CheckAttribute(pchar, "questTemp.Del_Rostovshik_repeat"))
			{
				dialog.text = "Hai portato 100 dobloni?";
				if (PCharDublonsTotal() >= 100)
				{
					link.l1 = "Ecco i tuoi soldi per il mio ufficiale...";
					link.l1.go = "Del_Deluck_5";
				}
				link.l2 = "No, sto ancora pensando.";
				link.l2.go = "exit";
			}
			//<-- Миниквест "Делюк"
		break;
		
		case "Sharlie":
			DelLandQuestMark(npchar);
			dialog.text = "E perché te ne importa, posso chiedere?";
			link.l1 = "Mi serve quest'uomo libero, non dietro le sbarre. E per quanto ne so, finché questo debito non ti sarà restituito, non sarà rilasciato, sono interessato a saldare questo debito.";
			link.l1.go = "Sharlie_1";
		break;
		
		case "Sharlie_1":
			dialog.text = "Aha, questo cambia tutto. Sono anche interessato a riavere indietro i miei soldi... Questo Folke Deluc è un tipo strano. Ha preso in prestito una somma di denaro relativamente piccola - cinquemila pesos. Semplicemente non voleva restituirla e ha iniziato a nascondersi. Alla fine, gli interessi sono saliti fino al prezzo del debito originale e si è ritrovato dietro le sbarre.";
			link.l1 = "Segue quindi che, il suo debito si è attualmente accumulato a diecimila?";
			link.l1.go = "Sharlie_2";
		break;
		
		case "Sharlie_2":
			dialog.text = "Diecimila quattrocento cinquanta pesos esattamente, signore. Quindi la sua libertà ha questo prezzo. Sei disposto a pagarlo a me? Sono un po' sorpreso...";
			if (sti(pchar.money) >= 10450)
			{
				link.l1 = "Non sorprenderti. Ecco i soldi.";
				link.l1.go = "Sharlie_3";
			}
			link.l2 = "Hm... Davvero una somma considerevole. Ascolta, signore, forse dovremmo cercare di fare un affare? Ad esempio, hai qualcosa di cui potrei prendermi cura e potresti valutare il mio favore a questi diecimila cinquecento...";
			if (CheckAttribute(pchar, "questTemp.Sharlie.FastStart")) link.l2.go = "Sharlie_5x";
			else link.l2.go = "Sharlie_5"; // Addon 2016-1 Jason пиратскаЯ линейка 1
		break;
		
		case "Sharlie_3":
			AddMoneyToCharacter(pchar, -10450);
			dialog.text = "Sì, sembra che tu abbia davvero bisogno di questo marinaio se sei disposto a sborsare una tale somma di denaro per lui. Comunque, non sono affari miei, vero signore? Ecco la sua cambiale, ora hai diritto al suo debito e hai il diritto di chiedergli del denaro. Beh, e naturalmente, richiedere la sua liberazione dal carcere.";
			link.l1 = "È esattamente quello che volevo. Addio, "+npchar.name+"!";
			link.l1.go = "Sharlie_4";
		break;
		
		case "Sharlie_4":
			DialogExit();
			Log_Info("You have received a bill of debt");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "letter_open");
			ChangeItemDescribe("letter_open", "itmdescr_letter_open_usurer");
			pchar.questTemp.Sharlie = "freeskiper";
			AddLandQuestMark(characterFromId("FortFranceJailOff"), "questmarkmain");
		break;
		
		case "Sharlie_5x": // Addon 2016-1 Jason пиратскаЯ линейка 1
			dialog.text = "Un favore? Ahimè, non ho bisogno di favori da te. Almeno per ora.";
			link.l1 = "Peccato. Allora dovrei portare i soldi per Folke. Addio!";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "bankskipermoney";
		break;
		
		case "Sharlie_5":
			dialog.text = "Favore? Hm... Sai, signore, avrei dato una risposta negativa se fossi venuto ieri, ma ora... sì, ho qualcosa di cui occuparmi, ma ti avverto che è piuttosto pericoloso.";
			link.l1 = "Pericoloso per cosa?";
			link.l1.go = "Sharlie_6";
		break;
		
		case "Sharlie_6":
			dialog.text = "Per la tua preziosa vita, naturalmente. Quindi rifletti, prima di accettare e decidi se sei disposto a fare qualcosa del genere o no.";
			link.l1 = "Signore, il pericolo non mi è affatto estraneo. Sono già stato in situazioni pericolose tante volte. Quindi, passiamo ai dettagli. Finché non coinvolge l'eliminazione dell'intera guarnigione del forte da solo, forse sarò in grado di realizzare ciò a cui alludi così misteriosamente.";
			link.l1.go = "Sharlie_7";
		break;
		
		case "Sharlie_7":
			dialog.text = "Bene. Allora ascolta. Stasera, diversi pirati e un prigioniero lasceranno il covo dei pirati di Le Francois e si dirigeranno verso la baia di Le Marin. Il prigioniero è un ufficiale spagnolo, un grande esperto di ingegneria delle fortificazioni. I britannici intendono usarlo a loro vantaggio, quindi invieranno una nave da guerra a prenderlo dalla baia\nL'ufficiale è un mio vecchio amico e non voglio che finisca prigioniero degli inglesi. Non posso chiedere aiuto alle autorità locali perché siamo in guerra con la Spagna. Se avessi più tempo, assumerei uomini capaci di riprendere lo spagnolo... scusa, di riprendere il mio amico, ma purtroppo!\nSei l'unico uomo a cui posso affidare questo compito. Devi andare alla baia di Le Marin e... convincere i pirati a consegnarti il prigioniero. Dubito che saranno molto collaborativi, quindi sta a te.";
			link.l1 = "Quanti pirati ci saranno nel convoglio?";
			link.l1.go = "Sharlie_8";
		break;
		
		case "Sharlie_8":
			dialog.text = "Non lo so. Forse due persone, forse tre o quattro. Allora, cosa diresti?";
			link.l1 = "Ti ho già detto 'il pericolo non è un estraneo per me' e so da quale lato tenere una spada.";
			link.l1.go = "Sharlie_10";
			link.l2 = "Mh. Hai ragione, è pericoloso. Non attaccherò un equipaggio di pirati tutto solo.";
			link.l2.go = "Sharlie_9";
		break;
		
		case "Sharlie_9":
			dialog.text = "Questa è la tua decisione. Se pensi di non essere all'altezza di questo lavoro, allora sarebbe meglio che rifiuti subito. Allora aspetterò i soldi del debito di Deluc.";
			link.l1 = "Va bene. Porterò i soldi per lui. Ci vediamo dopo!";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "bankskipermoney";
		break;
		
		case "Sharlie_10":
			dialog.text = "Molto bene. Lieto di sentire questo. Allora dovresti andare alla baia di Le Marin, i pirati saranno lì dalle sette di sera alle quattro del mattino. Non mancare! E non pensare nemmeno di usare una nave! Tali azioni li spaventeranno, cammina attraverso la giungla!\nPortami il prigioniero quando lo troverai, terrò la porta aperta. Consiglio di aspettare fino all'una di notte prima di ritornare in città perché devi evitare l'attenzione delle guardie. Fai attenzione e buona fortuna!";
			link.l1 = "Grazie! Avrò sicuramente bisogno di un po' di fortuna...";
			if (CheckAttribute(pchar,"equip."+GUN_ITEM_TYPE)) link.l1.go = "Sharlie_13";
			else link.l1.go = "Sharlie_11";
		break;
		
		case "Sharlie_11":
			dialog.text = "Aspetta un minuto! Vedo che non hai nemmeno una pistola. Prendi una delle mie. Ho anche diversi proiettili per essa. Penso che ti tornerà utile.";
			link.l1 = "Sì, questo sarà sicuramente utile. Grazie, monsieur.";
			link.l1.go = "Sharlie_12";
		break;
		
		case "Sharlie_12":
			Log_Info("You have received a combat pistol");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "pistol1");
			TakeNItems(pchar, "bullet", 20);
			TakeNItems(pchar, "gunpowder", 20);
			dialog.text = "E adesso vai, che Dio ti assista!";
			link.l1 = "...";
			link.l1.go = "Sharlie_13";
		break;
		
		case "Sharlie_13":
			DialogExit();
			pchar.quest.Sharlie_captive_Tut.win_condition.l1 = "location";
			pchar.quest.Sharlie_captive_Tut.win_condition.l1.location = "Shore39";
			pchar.quest.Sharlie_captive_Tut.function = "Tutorial_Rest_Delay";
			pchar.quest.Sharlie_captive.win_condition.l1 = "HardHour";
			pchar.quest.Sharlie_captive.win_condition.l1.hour = 19.00;
			pchar.quest.Sharlie_captive.function = "Captive_Timer";
			SetFunctionTimerCondition("Captive_CreatePiratesOver", 0, 0, 1, false);
			AddQuestRecord("SharlieD", "1");
			pchar.questTemp.Sharlie = "bankskiperfight";
			pchar.questTemp.Sharlie.Captive = "true";
			pchar.questTemp.Sharlie.Captive.Name = GetFullName(npchar);
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			// Rebbebion, новые марки до места назначения
			QuestPointerToLoc("fortfrance_town", "reload", "gate_back");
			QuestPointerToLoc("fortfrance_exittown", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_01", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_02", "reload", "reload2_back");
			QuestPointerToLoc("martinique_jungle_03", "reload", "reload2_back");
		break;
		
		case "Sharlie_14":
			pchar.quest.Sharlie_captive1.over = "yes";
			pchar.quest.Sharlie_captive2.over = "yes";
			pchar.quest.Sharlie_captive3.over = "yes";
			// Rebbebion, новые марки до места назначения
			QuestPointerDelLoc("shore39", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_03", "reload", "reload2_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload2_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload1_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload1_back");
			QuestPointerDelLoc("fortfrance_town", "reload", "reload8_back");
			DelLandQuestMark(npchar);
			ref sld = characterFromId("CaptiveSpain");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", 5.0);
			sld.lifeday = 0;
			SetNationRelation2MainCharacter(FRANCE, RELATION_FRIEND);
			DeleteAttribute(pchar, "questTemp.Sharlie.Captive");
			dialog.text = "Meraviglioso! Sono molto contento che tu sia riuscito a gestirlo con successo. Immagino che non ho bisogno di conoscere i dettagli dell'operazione, giusto? Quindi, il mio caro ospite spagnolo può ora sentirsi al sicuro nella mia casa...";
			link.l1 = "E che ne è del debito di Folke Deluc?";
			link.l1.go = "Sharlie_15";
		break;
		
		case "Sharlie_15":
			dialog.text = "Certo, sì. Prendi la sua cambiale, ora hai diritto al suo debito e hai il diritto di chiedere denaro a lui. Beh, e ovviamente, richiedi il suo rilascio dal carcere. Ho fatto tutto come promesso?";
			link.l1 = "Sì, signore. Tutto è in rigido secondo l'accordo. Ora permettetemi di prendere congedo.";
			link.l1.go = "Sharlie_4";
			AddQuestRecord("SharlieD", "7");
			CloseQuestHeader("SharlieD");
			DeleteAttribute(pchar, "questTemp.Sharlie.Captive");
		break;
		
		case "Sharlie_repeat":
			dialog.text = "Allora, sei pronto a pagare il suo debito?";
			if (sti(pchar.money) >= 10450)
			{
				link.l1 = "Sì. Ecco i soldi.";
				link.l1.go = "Sharlie_3";
			}
			link.l2 = "Sfortunatamente, non ho ancora raccolto la somma richiesta...";
			link.l2.go = "exit";
		break;
		
		case "Sharlie_junglejew":
			dialog.text = "Mh. Sembra che tu abbia ragione, questi sono orecchini costosi e sono stati sicuramente fatti nel Vecchio Mondo... Cosa posso dire? Ti darò per loro trenta... no, addirittura trentacinque dobloni d'oro. Prendi i soldi, non li venderai per di più.";
			link.l1 = "Trentacinque dobloni? Non è un cattivo prezzo. Accetto. Ecco a te.";
			link.l1.go = "Sharlie_junglejew_1";
			link.l2 = "No. Penso che terrò questi orecchini per me.";
			link.l2.go = "exit";
			npchar.quest.junglejew = "true";
		break;
		
		case "Sharlie_junglejew_1":
			DialogExit();
			PlaySound("interface\important_item.wav");
			Log_Info("You've given the earrings");
			RemoveItems(pchar, "jewelry25", 1);
			TakeNItems(pchar, "gold_dublon", 35);
			AddQuestRecord("SharlieE", "3");
			CloseQuestHeader("SharlieE");
			DeleteAttribute(pchar, "questTemp.Sharlie.Junglejew");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
			{
				DelLandQuestMark(characterFromId("FortFrance_Mayor"));
			}
		break;
		
		//--> Миниквест "Делюк"
		case "Del_Deluck":
			DeleteAttribute(pchar, "questTemp.Del_Rostovshik");
			dialog.text = "Lo so, lo so, Capitano. Il vostro navigatore sembra aver accumulato debiti in quasi ogni colonia francese. A dire il vero, ne ero a conoscenza da molto tempo. Ho verificato con i miei colleghi, una procedura standard, capisci...";
			link.l1 = "E non hai ritenuto fosse abbastanza importante informarmi durante il nostro precedente accordo?";
			link.l1.go = "Del_Deluck_2";
		break;
		
		case "Del_Deluck_2":
			dialog.text = "Perché? All'epoca, ero principalmente preoccupato del debito di Deluc nei miei confronti, che, incidentalmente, era il più grande. Una volta che hai risolto quello, ho prontamente avvisato i miei colleghi... Abbiamo una vasta flotta di corrieri professionali, quindi non ci è voluto molto prima che accumulassi una pila di fatture di Deluc sulla mia scrivania.";
			link.l1 = "Capisco... Le hai comprate sapendo che ho un interesse vitale in lui e i mezzi per pagare... Questo è estorsione, Monsenior.";
			link.l1.go = "Del_Deluck_3";
		break;
		
		case "Del_Deluck_3":
			dialog.text = "È solo affari, Capitano! Il debito totale di Deluc è di cento dobloni, e gli interessi stanno aumentando... Sei disposto a riscattarlo?";
			link.l1 = "Non sono pronto a rispondere ancora, ma lo considererò. Arrivederci!";
			link.l1.go = "Del_Deluck_4";
		break;
		
		case "Del_Deluck_4":
			DialogExit();
			
			pchar.questTemp.Del_Rostovshik_repeat = true;
			sld = CharacterFromID("Tichingitu");
			if (sld.location == pchar.location && !LAi_IsDead(sld))
			{
				sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
				sld.dialog.currentnode = "Del_Deluck";
				LAi_SetActorType(sld);
				LAi_ActorDialogDelay(sld, pchar, "", 0.0);
			}
		break;
		
		case "Del_Deluck_5":
			dialog.text = "Eccellente! Sai cosa fare dopo - come l'ultima volta. Ecco i documenti - presentali al comandante della prigione. È stato un piacere fare affari con te, Capitano.";
			link.l1 = "C'è poco da godere in questa situazione. Addio.";
			link.l1.go = "exit";
			RemoveItems(pchar, "gold_dublon", 100);
			DeleteAttribute(pchar, "questTemp.Del_Rostovshik_repeat");
			Log_Info("You have received a bill of debt");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "letter_open");
			ChangeItemDescribe("letter_open", "itmdescr_letter_open_usurer");
			pchar.questTemp.Del_DeluckSvoboda = true;
			AddLandQuestMark(characterFromId("FortFranceJailOff"), "questmarkmain");
			DelLandQuestMark(npchar);
		break;
		//<-- Миниквест "Делюк"
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quali domande hai?","Come posso aiutarti?"),"Hai cercato di farmi una domanda un po' di tempo fa...","Non ho mai incontrato persone con tanta curiosità nel mio cantiere navale o in qualsiasi altro luogo di questa città.","Che succede con tutte queste domande? Il mio lavoro è costruire navi. Occupiamoci di questo.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea...","Non ho nulla di cui parlare al momento."),"Umph, dove è andata a finire la mia memoria...","Uh, beh...","Vai avanti...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Addon-2016 Jason ”ЊЉ-Њартиника
			if (CheckAttribute(pchar, "questTemp.FMQM") && pchar.questTemp.FMQM == "begin")
            {
                link.l1 = "Il tuo uomo mi ha detto che vuoi vedermi. Sono tutto orecchie.";
                link.l1.go = "FMQM";
            }
			if (CheckAttribute(pchar, "questTemp.FMQM") && pchar.questTemp.FMQM == "oil" && GetSquadronGoods(pchar, GOOD_OIL) >= 50)
            {
                link.l1 = "Ho fatto il lavoro. "+FindRussianQtyString(GetSquadronGoods(pchar,GOOD_OIL))+" barili di resina si trovano nelle mie stive.";
                link.l1.go = "FMQM_9";
            }
		break;
		
		// Addon-2016 Jason ”ЊЉ-Њартиника
		case "FMQM":
			pchar.quest.FMQM_Denial.over = "yes";
			dialog.text = "Sì-sì, capitano "+GetFullName(pchar)+". Ho visto la tua nave entrare nel nostro porto e ho immediatamente mandato il mio lavoratore da te. Dritto al punto: sei un novizio, ma dicono che sei già diventato un marinaio esperto e la fortuna è dalla tua parte. Ecco perché ho una proposta di affari per te.";
			link.l1 = "Interessante! Continua, dimmi.";
			link.l1.go = "FMQM_1";
			DelLandQuestMark(npchar);
		break;
		
		case "FMQM_1":
			dialog.text = "Hai mai sentito parlare della resina speciale che gli spagnoli producono sull'isola di Trinidad? È una rara risorsa di valore strategico usata per rinforzare lo scafo delle navi. Ogni barile costa una somma cospicua perché gli spagnoli destinano tutta la resina per le necessità della loro Marina. Ogni autorità coloniale tiene sotto controllo il commercio di questo bene, per dirla semplicemente, è un puro contrabbando\nHo bisogno di questa resina per un ordine speciale. Ovviamente, il nostro negozio non ce l'ha, lo stesso può essere detto dei nostri magazzini militari locali o semplicemente non volevano venderla. È irrilevante davvero. Ciò che è rilevante è che ho bisogno della resina e so dove prenderne un po'. Tutto ciò di cui ho bisogno è un capitano che si trovi a suo agio con gli abbordaggi.";
			link.l1 = "Credo, sto iniziando a capire il tuo punto di vista...";
			link.l1.go = "FMQM_2";
		break;
		
		case "FMQM_2":
			dialog.text = "Splendido. Ora ascolta, un piccolo convoglio commerciale è stato localizzato vicino a Trinidad o per essere più precisi, nel porto di San Jose. Una nave sta trasportando una bella partita di resina, la stessa resina di cui ho un disperato bisogno. Ti dirò di più se ti piace l'idea di depredare i nemici della nostra nazione. Cosa decidi?";
			link.l1 = "Mi piace la tua proposta. Sono pronto a provarci.";
			link.l1.go = "FMQM_3";
			link.l2 = "Rinuncio, signore. La mia nave e il mio equipaggio non sono nel loro miglior stato al momento.";
			link.l2.go = "FMQM_exit";
		break;
		
		case "FMQM_exit":
			dialog.text = "Bene, è tuo diritto fare ciò che vuoi. Scusa per averti fatto perdere tempo, capitano.";
			link.l1 = "Arrivederci.";
			link.l1.go = "FMQM_exit_1";
		break;
		
		case "FMQM_exit_1":
			DialogExit();
			pchar.questTemp.FMQM = "fail";
			AddQuestRecord("FMQ_Martinique", "3");
			CloseQuestHeader("FMQ_Martinique");
		break;
		
		case "FMQM_3":
			string sTemp = "barquentine";
			if (MOD_SKILL_ENEMY_RATE < 7) sTemp = "barque";// Addon 2016-1 Jason пиратскаЯ линейка
			dialog.text = "Allora ascolta: il convoglio è composto da tre navi, la resina si troverà tra le altre merci su una "+sTemp+" chiamato 'Bensecho'. Questo è il tuo obiettivo principale. Come ho detto prima, gli spagnoli stanno navigando da San Jose - Trinidad, a San Juan - Puerto Rico. Salperanno domani, quindi sei libero di scegliere dove attaccarli.";
			link.l1 = "Capito. E riguardo a una ricompensa?";
			link.l1.go = "FMQM_4";
		break;
		
		case "FMQM_4":
			dialog.text = "Tutto ciò che mi interessa è la resina. Pagherò quindici dobloni d'oro per ogni barile di quella roba. Secondo le mie informazioni, il 'Bensecho' trasporta circa un centinaio di barili.";
			link.l1 = "Santo cielo! Questa è una grossa somma!";
			link.l1.go = "FMQM_5";
		break;
		
		case "FMQM_5":
			dialog.text = "Sì. Ti ho già detto che questa merce particolare è molto costosa e rara.";
			link.l1 = "Hai anche detto che questo è un contrabbando.";
			link.l1.go = "FMQM_6";
		break;
		
		case "FMQM_6":
			dialog.text = "Non preoccuparti, non avrai bisogno di portarlo al negozio o ai contrabbandieri. Vieni a trovarmi quando il lavoro è fatto, attraccheremo la tua nave nel mio cantiere navale per ripararla e poi scaricheremo tutto il carico segretamente di notte. Nessuno sospetterà nulla.";
			link.l1 = "Pensate avanti a me, maestro. Molto bene. Non perdiamo tempo. Sono in viaggio per salpare.";
			link.l1.go = "FMQM_7";
		break;
		
		case "FMQM_7":
			dialog.text = "Dio vi accompagni capitano.";
			link.l1 = "...";
			link.l1.go = "FMQM_8";
		break;
		
		case "FMQM_8":
			DialogExit();
			pchar.questTemp.FMQM = "convoy";
			AddQuestRecord("FMQ_Martinique", "4");
			SetFunctionTimerCondition("FMQM_ConvoyStart", 0, 0, 1, false);
		break;
		
		case "FMQM_9":
			dialog.text = "Eccellente! Come abbiamo concordato prima, mettiamo la tua nave nei docks. La scaricheremo là stasera. Torna alla tua nave e lascia che io prepari i soldi per te.";
			link.l1 = "Facciamolo.";
			link.l1.go = "FMQM_10";
			DelLandQuestMark(npchar);
		break;
		
		case "FMQM_10":
			pchar.quest.FMQM_Late.over = "yes";
			DialogExit();
			InterfaceStates.Buttons.Save.enable = false;
			chrDisableReloadToLocation = true;
			pchar.GenQuest.FrameLockEsc = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
			pchar.questTemp.FMQM = "remove_oil";
			pchar.questTemp.FMQM.Oil = "true";
			pchar.questTemp.FMQM.Qty = GetSquadronGoods(pchar, GOOD_OIL);
			DoQuestFunctionDelay("FMQM_WaitTime", 1.0);
			RemoveCharacterGoods(pchar, GOOD_OIL, GetSquadronGoods(pchar, GOOD_OIL));
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

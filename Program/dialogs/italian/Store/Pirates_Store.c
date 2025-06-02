// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	bool bOk;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Avanti, cosa desideri?","Ne stavamo proprio parlando. Devi averlo dimenticato...","Questa è la terza volta oggi che parli di qualche domanda...","Ascolta, questo è un negozio. Le persone comprano roba qui. Non disturbarmi!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sai, "+NPChar.name+", forse la prossima volta.","Giusto, per qualche motivo ho dimenticato...","Sì, è davvero la terza volta...","Mm, non lo farò...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				link.l1 = "Ascolta, "+npchar.name+", hai visto Miguel Dichoso su Isla Tesoro ultimamente?";
				link.l1.go = "tieyasal";
			}
			// Addon 2016-1 Jason пиратскаЯ линейка
			if(CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "pasq_start")
			{
				link.l1 = ""+npchar.name+", Sono qui per conto di Marcus Tyrex. Ha detto che avevi bisogno di un uomo per un lavoro.";
				link.l1.go = "mtraxx";
			}
			if(CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "pasq_win")
			{
				link.l1 = ""+npchar.name+", il 'Rosbohom' è stato trovato e catturato. Dovremmo iniziare a scaricare e contare?";
				link.l1.go = "mtraxx_5";
			}
		break;
				
		// город майя
		case "tieyasal":
			dialog.text = "Sì, l'ho fatto. Ha comprato rifornimenti per la sua nave qui. È stato molto recentemente, tra l'altro. Vi siete letteralmente persi di pochi giorni. Tra l'altro, potrebbe essere ancora in questo insediamento. Non spio per le persone, lo sai. Chiedi in giro un po' di più e chissà, potresti proprio trovare il tuo don.";
			link.l1 = "Bene. Grazie per l'informazione!";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			DialogExit();
			npchar.quest.tieyasal = "true";
		break;
		
		// Addon 2016-1 Jason пиратскаЯ линейка
		case "mtraxx":
			pchar.quest.Mtraxx_PasqualeLate.over = "yes";
            dialog.text = "Esattamente! È bene che tu sia arrivato in tempo. Ora lascia che ti dica il nocciolo della questione...";
			link.l1 = "Sono tutto orecchie.";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
			string sTemp = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.questTemp.Mtraxx.Crdn.Ship), "Name")));
            dialog.text = "In questo momento un "+sTemp+", la nave olandese chiamata 'Rosbohom', sta arrivando nelle nostre acque insieme a una nave da guardia. È carica di ebano e salpa da Willemstad per incontrare un'altra nave da guardia per garantire un viaggio sicuro verso l'Europa. Non so quale rotta prenda, via Sint Maarten o via Espanyol, ma conosco le coordinate del loro punto di incontro\nLa tua missione è trovare gli olandesi lì, salire a bordo del mercantile e portare a me il suo carico. Pagherò non appena il carico sarà consegnato.";
			link.l1 = "Capito. Quando e dove?";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
			int i = sti(pchar.questTemp.Mtraxx.Crdn.minN2)-10;
			int n = sti(pchar.questTemp.Mtraxx.Crdn.minW2)-10;
            dialog.text = ""+sti(pchar.questTemp.Mtraxx.Crdn.degN)+" "+i+" Nord e "+sti(pchar.questTemp.Mtraxx.Crdn.degW)+" "+n+"Ovest. Deve essere da qualche parte a Sud o Sud-Ovest da Isla Tesoro, non sono bravo in questo, non sono un marinaio, ma tu lo sei. Hai circa cinque giorni per svolgere il lavoro.";
			link.l1 = "Capito... Ho capito. Non perdiamo tempo allora!";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = "Buon vento capitano. Aspetterò te e il carico.";
			link.l1 = "...";
			link.l1.go = "mtraxx_4";
		break;
		
		case "mtraxx_4":
           DialogExit();
		   pchar.questTemp.Mtraxx = "pasq_convoy";
		   i = sti(pchar.questTemp.Mtraxx.Crdn.minN2)-10;
           n = sti(pchar.questTemp.Mtraxx.Crdn.minW2)-10;
		   AddQuestRecord("Roger_4", "3");
		   AddQuestUserData("Roger_4", "sShip", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.questTemp.Mtraxx.Crdn.Ship), "Name")+ "Gen")));
		   AddQuestUserData("Roger_4", "sdegN", sti(pchar.questTemp.Mtraxx.Crdn.degN));
		   AddQuestUserData("Roger_4", "sminN", i);
		   AddQuestUserData("Roger_4", "sdegW", sti(pchar.questTemp.Mtraxx.Crdn.degW));
		   AddQuestUserData("Roger_4", "sminW", n);
		   SetFunctionTimerCondition("Mtraxx_PasqualeTimeConvoy", 0, 0, 6, false);
		   SetFunctionTimerCondition("Mtraxx_PasqualeConvoyOver", 0, 0, 7, false);
		break;
		
		case "mtraxx_5":
			iTotalTemp = GetSquadronGoods(pchar, GOOD_EBONY);
			if (iTotalTemp < 1)
			{
				dialog.text = "Ti stai prendendo gioco di me giovane uomo? Nei tuoi stiva non c'è nemmeno una tavola di ebano! Questo è un trucchetto insolente! Fuori di qui! Informerò Marco di tutto questo! Fuori!!!";
				link.l1 = "Mm...";
				link.l1.go = "mtraxx_6";
				break;
			}
			if (iTotalTemp < makeint(sti(pchar.questTemp.Mtraxx.Crdn.Ebony)/4))
			{
				dialog.text = "Stai scherzando con me, ragazzo? La tua stiva ha solo pochi schegge di ebano! Questa è una truffa insolente! Vattene da qui! Informerò Marcus di tutto questo! Vattene!!!";
				link.l1 = "Mh...";
				link.l1.go = "mtraxx_6";
				break;
			}
			if (iTotalTemp < sti(pchar.questTemp.Mtraxx.Crdn.Ebony)-20)
			{
				dialog.text = "La Rosbohom aveva almeno "+FindRussianQtyString(sti(pchar.questTemp.Mtraxx.Crdn.Ebony))+" di ebano. Perché mi hai portato di meno?";
				link.l1 = "Beh... sai, ho dovuto liberarmi di una parte durante la lotta. E poi i ratti, maledetti...";
				link.l1.go = "mtraxx_7";
				break;
			}
            dialog.text = "Molto bene. Quanto ne hai? "+FindRussianQtyString(iTotalTemp)+"? Splendido! Ti pagherò 150 pesos per un pezzo.";
			link.l1 = "150 pezzi di otto? Immagino che l'ebano costi molto di più.";
			link.l1.go = "mtraxx_10";
		break;
		
		case "mtraxx_6":
           DialogExit();
		   pchar.questTemp.Mtraxx = "pasq_angry";
		   DoQuestReloadToLocation("Pirates_town", "reload", "reload6", "");
		   AddQuestRecord("Roger_4", "8");
		   CloseQuestHeader("Roger_4");
		   QuestSetCurrentNode("Terrax", "mtraxx_34");
		break;
		
		case "mtraxx_7":
            dialog.text = "Ratti? Beh-beh... Ma va bene. 100 pesos a pezzo e sei libero di andare.";
			link.l1 = "Solo 100 pesos? Questo è un furto!";
			link.l1.go = "mtraxx_8";
		break;
		
		case "mtraxx_8":
			AddMoneyToCharacter(pchar, iTotalTemp*100);
			RemoveCharacterGoods(pchar, GOOD_EBONY, iTotalTemp);
            dialog.text = "La rapina è il tuo mestiere, capitano, io sono un semplice mercante. Prendi i tuoi soldi e non continuiamo a discutere, hai già fatto un bel guadagno vendendo una parte del mio carico altrove.";
			link.l1 = "Allora, vaffanculo!";
			link.l1.go = "mtraxx_9";
		break;
		
		case "mtraxx_9":
           DialogExit();
		   pchar.questTemp.Mtraxx = "pasq_fail";
		   AddQuestRecord("Roger_4", "8");
		   CloseQuestHeader("Roger_4");
		   QuestSetCurrentNode("Terrax", "mtraxx_34");
		break;
		
		case "mtraxx_10":
            dialog.text = "E hai ragione, capitano, ma prima, prova a vendere merci rubate e vedrò quanto gli altri mercanti ti pagheranno per esse. Il prezzo offerto a te è molto alto. In secondo luogo, era il mio suggerimento, non avresti mai trovato quel convoglio da solo, inoltre c'erano altre merci di valore su di esso e non le sto rivendicando. Terzo, ti darò i migliori crediti agli occhi di Marcus Tyrex e questo costa molto, fidati di me. E infine, quarto, un povero mercante deve pur guadagnarsi da vivere in qualche modo.";
			link.l1 = "Accidenti! Devo ritirarmi di fronte a tali argomenti "+npchar.name+". Facciamo il conteggio.";
			link.l1.go = "mtraxx_11";
		break;
		
		case "mtraxx_11":
			AddMoneyToCharacter(pchar, iTotalTemp*150);
			RemoveCharacterGoods(pchar, GOOD_EBONY, iTotalTemp);
            dialog.text = "Splendido. Prendi le tue monete. È stato un piacere. Assicurati di controllare il mio negozio di tanto in tanto. Possa tu essere fortunato in mare!";
			link.l1 = "E voi nel vostro mestiere...";
			link.l1.go = "mtraxx_12";
		break;
		
		case "mtraxx_12":
           DialogExit();
		   pchar.questTemp.Mtraxx = "pasq_complete";
		   AddQuestRecord("Roger_4", "9");
		   pchar.quest.mtr_pasq_fin.win_condition.l1 = "location";
		   pchar.quest.mtr_pasq_fin.win_condition.l1.location = "Pirates_town";
		   pchar.quest.mtr_pasq_fin.function = "Mtraxx_PasqualeJeffry";
		   bDisableFastReload = true;
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}

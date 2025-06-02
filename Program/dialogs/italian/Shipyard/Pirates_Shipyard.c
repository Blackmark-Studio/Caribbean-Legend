// диалог по городам
// Это мастер тюнинга
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    string 	sTemp;
	int 	amount, iSan, iOil, iSil, iRop;
	int iTemp, iSum; // 280912
	ref 	shTo;
	string 	s1;
	
	int     Matherial1;
	int     Matherial2;
	int     Matherial3;
	int     Matherial4;
	int		HPPrice; 
	
	if ( sti(pchar.Ship.Type) != SHIP_NOTUSED)
	{
		int   	shipCurHP   = sti(RealShips[sti(pchar.Ship.Type)].HP);
		int   	shipBaseHP	= sti(RealShips[sti(pchar.Ship.Type)].BaseHP);
		int   	shipClass   = sti(RealShips[sti(pchar.Ship.Type)].Class);
	}	
 
	switch (Dialog.CurrentNode)
	{		
		// -----------------------------------Диалог первый - первая встреча
		case "First time":  // перехват основного диалога, только один раз
			if(NPChar.quest.meeting == "0")
			{
				Dialog.Text = "Uffa... Che clima terribile... Il mio nome è "+GetFullName(npchar)+", e che Dio mi maledica, se non sono il miglior costruttore di navi in queste isole dimenticate da Dio. Ma questa umidità mi sta proprio abbattendo...";
				Link.l1 = pcharrepphrase("Mille squali, proprio quello che mi mancava, il mormorio di un vecchio. Il mio nome è "+GetFullName(pchar)+", credo che tu abbia sentito parlare di me.","Non è l'umidità, è la vecchiaia, signore. Il mio nome è "+GetFullName(pchar)+", credo che tu abbia sentito parlare di me.");
				Link.l1.go = "node_1";
				npchar.quest.meeting = "1";
			}
			else // нужно, если по квестам будет сброс на  "First time"
			{
				dialog.text = "Oh, sei tu di nuovo, sempre a parlare dei tuoi problemi... (tossendo).";
				link.l1 = pcharrepphrase("Hai ragione, sono di nuovo io. Ma parliamo di affari mentre non hai ancora dato la tua anima a Dio.","La tua memoria ti serve bene, e ora se permetti, passiamo a delle domande più specifiche.");
				link.l1.go = "node_3";
				link.l2 = pcharrepphrase("Mi sono stancato dei tuoi borbottii. Addio.","È ora per me di andare. Scusa per il disturbo");
				link.l2.go = "exit";
			}
			NextDiag.TempNode = "Master_Ship";
			Dialog.CurrentNode = "Master_Ship";
		break;
		
		case "Master_Ship":
		//Jason ----------------------------------- Хронометр Алекса ------------------------------------------
			if (CheckAttribute(npchar, "quest.sextant") && CheckAttribute(pchar, "questTemp.AlexClock") && pchar.location == "Pirates_shipyard" && !CheckAttribute(npchar, "quest.clock"))
			{
				dialog.text = "Aha, capitano "+GetFullName(pchar)+"! Che bello, che sei passato!";
				Link.l1 = "Sembra che tu abbia bisogno di me per qualcosa, non è vero? Di solito non sei così cortese.";
				Link.l1.go = "clock_begin";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.AlexClock") && pchar.questTemp.AlexClock == "clock" && pchar.location == "Pirates_shipyard")
			{
				dialog.text = "Vedo che sei tornato da me a mani vuote, capitano! Che è successo con gli...ospiti?";
				Link.l1 = "Sono andati. Ho chiesto loro e se ne sono andati.";
				Link.l1.go = "clock_complete";
				break;
			}
		//<-- хронометр Алекса
			dialog.text = "Oh, ancora tu, sempre a parlare dei tuoi problemi... (tosse)";
			link.l1 = pcharrepphrase("Hai ragione, sono io di nuovo. Ma parliamo di affari mentre ancora non hai dato la tua anima a Dio.","La tua memoria ti serve bene, e ora se permetti, passiamo a delle domande più specifiche.");
			link.l1.go = "node_3";
			link.l2 = pcharrepphrase("Mi sono stancato del tuo borbottio. Addio.","È ora per me di andare. Scusa per il disturbo.");
			link.l2.go = "exit";
			NextDiag.TempNode = "Master_Ship";
		break;

		case "node_1":
			dialog.text = "I giovani di questi giorni... Non avete mai rispetto. Teste calde, mani dure, di che cosa avete bisogno?";
			link.l1 = pcharrepphrase("È vero. Ma prima o poi tutto ha una fine e sembra che il tuo tempo sia vicino...","Qualcosa mi dice che durante la tua giovinezza, non avevi necessariamente molto rispetto per gli anziani. Ho ragione?");
			link.l1.go = "node_2";
		break;

		case "node_2":
			dialog.text = "Non discutere con i tuoi anziani, cucciolo.";
			link.l1 = pcharrepphrase("Piano, ora. Calmati. Non sforzarti troppo altrimenti potresti avere un infarto. Non voglio essere accusato per la morte del miglior costruttore di navi dei Caraibi. Mettiamoci al lavoro.","Ti perdono per la tua maleducazione, solo per rispetto della tua età. E ora, se hai finito, passiamo ai fatti.");
			link.l1.go = "node_3";
			link.l2 = pcharrepphrase("Bene, basta prediche per me! Addio!","Vedo che non riusciremo a vedere occhio per occhio. Addio.");
			link.l2.go = "exit";
		break;

		case "node_3":
			dialog.text = "(tosse)... La gente non lascia in pace un anziano. Cosa vuoi da me questa volta, "+GetAddress_Form(NPChar)+"? ";
			link.l1 = pcharrepphrase("Devo utilizzare i servizi del cantiere navale.","Voglio usufruire dei servizi del cantiere navale.");
			link.l1.go = "shipyard_dlg";
            Link.l2 = "Ho una domanda.";
			Link.l2.go = "quests"; //(пересылка в файл города)
			// -->
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l3 = "Vorrei parlare di finanza.";
				link.l3.go = "LoanForAll";//(перессылка в файл города)
			}
			link.l9 = pcharrepphrase("Cazzo, ho un paio di questioni urgenti da risolvere, arrivederci.","È ora per me di andare. Mi dispiace.");
			link.l9.go = "exit";
			NextDiag.TempNode = "Master_Ship";
		break;
		
		case "shipyard_dlg":			
			if((shipBaseHP - shipCurHP > 0) && (shipClass < 7))
			{
				dialog.Text = "Posso proporvi un'ottima riparazione dell'ossatura della vostra nave. La gente qui non ha idea di come costruire navi decenti, tutte si sfasciano al primo colpo...";						
				Link.l1 = "Ottimo! Si dà il caso che io abbia una nave che ha bisogno di riparazioni. Forse potresti dare un'occhiata a cosa puoi fare?";
				Link.l1.go = "ship_repair_start";		
			}
			else
			{
				dialog.Text = "Avanti, cosa vuoi? Non tormentare un vecchio...";
			}	
			link.l2 = "Voglio solo usare i servizi del cantiere navale.";
			link.l2.go = "shipyard";
			link.l3 = "Mi servono armi per la nave.";
			link.l3.go = "Cannons";
			if(RealShips[sti(Pchar.Ship.Type)].BaseType != SHIP_CURSED_FDM)
			{
					link.l4 = "Voglio cambiare l'aspetto delle mie vele.";
					link.l4.go = "SailsGerald";
			}
			if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && !CheckAttribute(npchar, "quest.FDM_hull"))
			{
					link.l50 = "La mia nave è piuttosto... speciale. Vorrei apportare qualche modifica.";
					link.l50.go = "FDM";
			}
			if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && CheckAttribute(npchar, "quest.FDM_full") && npchar.quest.FDM_full == "cabin" && GetCharacterItem(pchar, "Chest") > 0)
			{
					link.l50 = "Ho più casse per la ricostruzione della cabina.";
					link.l50.go = "FDM_cabin_pay";
			}
			// Xenon -->
			if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && CheckAttribute(npchar, "quest.FDM_hull") && npchar.quest.FDM_hull == "hull_waitmoney")
			{
					link.l50 = "Sono qui per la ricostruzione della nave.";
					link.l50.go = "FDM_hull_givemoney";
			}

			if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && CheckAttribute(npchar, "quest.FDM_hull") && npchar.quest.FDM_hull == "hull_waitmaterials")
			{
					link.l50 = "Sono qui riguardo alla ricostruzione della nave.";
					link.l50.go = "FDM_hull_checkmaterials";
			}
			// <-- Xenon
			link.l9 = pcharrepphrase("Cavolo, ho un paio di questioni urgenti da risolvere, arrivederci.","È ora per me di andare. Mi dispiace.");
			Link.l9.go = "ship_tunning_not_now";
		break;
		
		case "ship_repair_again":
			if((shipBaseHP - shipCurHP > 0) && (shipClass < 7))
			{
				dialog.Text = RandPhraseSimple("Ah... sei tu di nuovo. Vuoi riparare la tua nave di nuovo?",RandPhraseSimple("Saluti, a un capitano famoso. Cosa, hai bisogno di un'altra riparazione capitale?","Mamma mia... Non un minuto di pace e tranquillità. Non lasci un vecchio concentrarsi.. Un'altra riparazione?"));
				Link.l1 = "Sì. Hai proprio ragione. Diamo un'occhiata a cosa possiamo fare?";
				Link.l1.go = "ship_repair_start";						   
			}
			else
			{
				dialog.Text = "Cosa è successo questa volta? Non vuoi proprio lasciarmi in pace...";
			}				
			link.l2 = "Voglio solo usare i servizi del cantiere navale.";
			link.l2.go = "shipyard";
			link.l3 = "Ho bisogno di armi per la nave.";
			link.l3.go = "Cannons";
			if(RealShips[sti(Pchar.Ship.Type)].BaseType != SHIP_CURSED_FDM)
			{
					link.l31 = "Voglio cambiare l'aspetto delle mie vele.";
					link.l31.go = "SailsGerald";
			}
			if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && !CheckAttribute(npchar, "quest.FDM_hull"))
			{
					link.l50 = "La mia nave è piuttosto... speciale. Vorrei apportare alcune modifiche.";
					link.l50.go = "FDM";
			}
			if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && CheckAttribute(npchar, "quest.FDM_full") && npchar.quest.FDM_full == "cabin" && GetCharacterItem(pchar, "Chest") > 0)
			{
					link.l50 = "Ho più casse per la ricostruzione della cabina.";
					link.l50.go = "FDM_cabin_pay";
			}
            Link.l4 = "Ho una domanda.";
			Link.l4.go = "quests"; //(пересылка в файл города)
			// -->
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l5 = "Vorrei parlare di finanza.";
				link.l5.go = "LoanForAll";//(пересылка в файл города)
			}
			Link.l9 = "No. Sono soddisfatto di quello che ho.";
			Link.l9.go = "ship_tunning_not_now_2";
		break;
		
		case "ship_tunning_not_now_2":
			dialog.Text = "Oh, vedo che stai ancora pensando! Andrai lontano! Torna quando decidi cosa vuoi e non disturbarmi con sciocchezze insignificanti.";
			Link.l1 = RandPhraseSimple("Grazie! Tutto il meglio.","Addio, maestro. E meno sarcasmo.");
			Link.l1.go = "ship_tunning_not_now";
		break;
		
		case "ship_repair_start":
            if ( sti(Pchar.Ship.Type) == SHIP_NOTUSED || Pchar.location.from_sea != "Pirates_town")
            {
                dialog.Text = "Dov'è la nave? Cos'è tutto questo ambaradan?!";
			    Link.l1 = "Sì, hai ragione... Io sono... Mi scuso.";
			    Link.l1.go = "ship_tunning_not_now";
            }
            else
            {
			    if (GetHour() == 13)
			    {
					dialog.Text = "Potrei essere un workaholic, ma ho anche un'ora di pranzo. Torna più tardi!";
			        Link.l1 = "Bene...";
			        Link.l1.go = "ship_tunning_not_now";
			    }
			    else
			    {
                    if( makefloat(shipCurHP)/makefloat(shipBaseHP) < 0.10)
                    {
						dialog.Text = "Caspita... La tua nave è completamente distrutta. Non farò un restauro completo, nemmeno me lo chiedere... Se fossi arrivato un po' prima...";
    			        Link.l1 = "Va bene... Che peccato...";
    			        Link.l1.go = "ship_tunning_not_now";
    			        break;
                    }
					if( makefloat(shipCurHP)/makefloat(shipBaseHP) > 0.95)
                    {
						dialog.Text = "Cosa sono tutte queste stregonerie... La tua nave sembra nuova di zecca... L'ossatura è praticamente lucente. Non c'è nulla da riparare qui.";
						Link.l1 = "Bene... Beh, tornerò più tardi...";
    			        Link.l1.go = "ship_tunning_not_now";
    			        break;
					}
                    s1 = "Fine, alright... What do we have here... Aha, " + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) + ".";
    			    if (sti(RealShips[sti(Pchar.Ship.Type)].Stolen) == true && !CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning"))
    			    {
    			        s1 = s1 + " Bah! This ship's been in too many hands. Yeah and there are a lot of scuffs. Do you have a corsair patent? Just joking... anyway, back to the matter.";
    			    }
                    dialog.Text = s1;
					Link.l1 = "Diamo un'occhiata qui a cosa possiamo fare.";
    			    Link.l1.go = "ship_repair_HP";		    			    
    			    Link.l2 = "Fermati! Ho cambiato idea.";
    			    Link.l2.go = "ship_tunning_not_now_2";
			    }
			}
		break;
		
		case "ship_repair_HP":
			HPPrice 	= GetMaterialQtyRepair( pchar, 0 ); 
			Matherial1	= GetMaterialQtyRepair( pchar, 1 );
			Matherial2	= GetMaterialQtyRepair( pchar, 2 );
			Matherial3	= GetMaterialQtyRepair( pchar, 3 );
			Matherial4	= GetMaterialQtyRepair( pchar, 4 );
			
			s1 = "Let's have a look here at what we can do. At the moment, the ship's frame is " + shipCurHP + ". . The highest possible value is " + shipBaseHP;			
			s1 = s1 + ". In order to make a full repair, I need: ironwood - "+ Matherial1 + ", resin - " + Matherial2 + ", ship silk - " + Matherial3 + " ropes - " + Matherial4 + ".";
			s1 = s1 + " For this work I will charge: "+ HPPrice + " doubloons for the labor... My grandchildren have been calling me back to Europe for a long time. I don't want to come back empty-handed you know... So, that'll be all. And oh yes - the money up front.";
            dialog.Text = s1;
			Link.l1 = "Sembra buono. Accetterò le condizioni. Tutto sarà consegnato come concordato.";
			if(CheckItemMyCabin("gold_dublon") >= HPPrice)
			{
				Link.l1.go = "ship_repair_HP_start_0";
			}
			else
			{
				Link.l1.go = "ship_repair_HP_start";
			}			
			Link.l2 = "No. Non sono soddisfatto di questo.";
			Link.l2.go = "ship_tunning_not_now";
		break;
		
		case "ship_repair_HP_start_0":
			dialog.Text = "Sì... Il pagamento... Puoi pagare ora o puoi mandare un ragazzo a fare un recado sulla nave per l'importo necessario... Cosa preferisci fare?";
			link.l1 = "Pagherò subito.";
			link.l1.go = "ship_repair_HP_start";
			link.l2 = "Manderò un garzone. Credo di avere un po' d'oro che giace nei miei forzieri...";
			link.l2.go = "ship_repair_HP_start_1";
		break;
		
		case "ship_repair_HP_start":
			HPPrice 	= GetMaterialQtyRepair( pchar, 0 ); 
			Matherial1	= GetMaterialQtyRepair( pchar, 1 );
			Matherial2	= GetMaterialQtyRepair( pchar, 2 );
			Matherial3	= GetMaterialQtyRepair( pchar, 3 );
			Matherial4	= GetMaterialQtyRepair( pchar, 4 );
		    amount = HPPrice;
		    if(GetCharacterItem(pchar,"gold_dublon") >= amount)
			{
				TakeNItems(pchar,"gold_dublon", -amount);				
			    NPChar.Repair.Money  		= amount;
			    NPChar.Repair.Matherial1 	= Matherial1; 
			    NPChar.Repair.Matherial2    = Matherial2;
				NPChar.Repair.Matherial3 	= Matherial3; 
			    NPChar.Repair.Matherial4    = Matherial4; 				 				
			    NPChar.Repair.ShipType      = Pchar.Ship.Type;
			    NPChar.Repair.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NPChar.Repair.Delta         = shipBaseHP - shipCurHP;
			    			
				NextDiag.TempNode = "ship_repair_HP_again";
                dialog.text = "Splendido. Starò aspettando i materiali.";
			    link.l1 = "Andando a raccoglierli...";
			    link.l1.go = "Exit";
			    
			    ReOpenQuestHeader("ShipRepair");
			    AddQuestRecord("ShipRepair", "t1");
				AddQuestUserData("ShipRepair", "sText",  "For capital repairing measures of  " + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) +
    " the shipmaster requires: ironwood - " + NPChar.Repair.Matherial1 + ", resin - "+ NPChar.Repair.Matherial2 + ", ship silk - " + NPChar.Repair.Matherial3 + " ropes - " + NPChar.Repair.Matherial4 + 
				". As a deposit we handed in " + NPChar.Repair.Money + " doubloons... He says he's about to take off to Europe. I think that old devil's lying.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now";
                dialog.text = RandPhraseSimple("Non vedo il deposito...","Cosa diavolo è questa stregoneria...");
				link.l1 = "Torno più tardi.";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_repair_HP_start_1":
			HPPrice 	= GetMaterialQtyRepair( pchar, 0 ); 
			Matherial1	= GetMaterialQtyRepair( pchar, 1 );
			Matherial2	= GetMaterialQtyRepair( pchar, 2 );
			Matherial3	= GetMaterialQtyRepair( pchar, 3 );
			Matherial4	= GetMaterialQtyRepair( pchar, 4 );
			AddTimeToCurrent(0, 30);
		    amount = HPPrice;
			GetItemMyCabin("gold_dublon", amount);
		    
			NPChar.Repair.Money  		= amount;
			NPChar.Repair.Matherial1 	= Matherial1; 
			NPChar.Repair.Matherial2    = Matherial2; 
			NPChar.Repair.Matherial3 	= Matherial3; 
			NPChar.Repair.Matherial4    = Matherial4; 				 							
			NPChar.Repair.ShipType      = Pchar.Ship.Type;
			NPChar.Repair.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
			NPChar.Repair.Delta         = shipBaseHP - shipCurHP;
			    			
			NextDiag.TempNode = "ship_repair_HP_again";
			dialog.text = "Splendido. Aspetterò i materiali.";
			link.l1 = "Vado...";
			link.l1.go = "Exit";
			
			ReOpenQuestHeader("ShipRepair");
			AddQuestRecord("ShipRepair", "t1");
			AddQuestUserData("ShipRepair", "sText",  "For capital repairing measures of  " + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) +
    " the shipmaster requires: ironwood - " + NPChar.Repair.Matherial1 + ", resin - "+ NPChar.Repair.Matherial2 + ", ship silk - " + NPChar.Repair.Matherial3 + " ropes - " + NPChar.Repair.Matherial4 + 
				". As a deposit we handed in " + NPChar.Repair.Money + " doubloons... He says he's about to take off to Europe. I think that old devil's lying.");
			
		break;
		
		case "ship_repair_HP_again":
		    if (sti(NPChar.Repair.ShipType) == sti(Pchar.Ship.Type) && NPChar.Repair.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName)
		    {
                NextDiag.TempNode = "ship_repair_HP_again";
				dialog.Text = "L'orologio sta ticchettando. Hai quello che ho chiesto?";
			    Link.l1 = "Sì. Sono riuscito a procurarmi qualcosa.";
			    Link.l1.go = "ship_repair_HP_again_2";
			    Link.l2 = "No. Sto ancora cercando.";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Repair");
                NextDiag.TempNode = "ship_repair_again";
			    dialog.Text = "Mi sembra, signore, che abbiate cambiato la vostra nave da quando abbiamo fatto l'ultimo accordo. Dovremo ricontare tutto da capo...";
			    Link.l1 = "Sì, è vero. Che peccato che il deposito sia sparito...";
			    Link.l1.go = "Exit";		    
			    AddQuestRecord("ShipRepait", "Lose");
			    CloseQuestHeader("ShipRepair");
			}
		break;
		
		case "ship_repair_HP_again_2":
			checkMatherial_repair(Pchar, NPChar, GOOD_SANDAL, 	1);
			checkMatherial_repair(Pchar, NPChar, GOOD_OIL, 		2);
			checkMatherial_repair(Pchar, NPChar, GOOD_SHIPSILK, 3);
			checkMatherial_repair(Pchar, NPChar, GOOD_ROPES, 	4);
		    if(sti(NPChar.Repair.Matherial1) < 1 && 
			   sti(NPChar.Repair.Matherial2) < 1 &&
			   sti(NPChar.Repair.Matherial3) < 1 &&
			   sti(NPChar.Repair.Matherial4) < 1)
			{
                NextDiag.TempNode = "ship_repair_again";
                dialog.text = "Tutto ciò di cui avevo bisogno. Bene! È ora di lavorare...";
			    link.l1 = "Va bene, aspetterò.";
			    link.l1.go = "ship_repair_HP_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_repair_HP_again";
				dialog.Text = "Ora quello che devi ancora portarmi è: "+sti(NPChar.Repair.Matherial1)+" di legno ferro, "+sti(NPChar.Repair.Matherial2)+" resina, "+NPChar.Repair.Matherial3+" di seta della nave, "+NPChar.Repair.Matherial4+"corde.";
				link.l1 = "Bene.";
				link.l1.go = "Exit";

                AddQuestRecord("ShipRepair", "t1");
				AddQuestUserData("ShipRepair", "sText", "Materials left: ironwood - "+ NPChar.Repair.Matherial1 + ", resin - "+ NPChar.Repair.Matherial2 + ", ship silk - " + NPChar.Repair.Matherial3 + " ropes - " + NPChar.Repair.Matherial4 + ".");
			}
		break;
		
		case "ship_repair_HP_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
			shTo.HP = sti(shTo.HP) + sti(NPChar.Repair.Delta);
		    DeleteAttribute(NPChar, "Repair");
			
			pchar.ship.hp = GetCharacterShipBaseHP(pchar);
			DeleteAttribute(pchar, "ship.hulls");
			DeleteAttribute(pchar, "ship.blots");		
			
            NextDiag.TempNode = "node_3";
			dialog.Text = "... Beh, è tutto... Ti garantisco che sarà piuttosto difficile distruggere questa nave ora!";
			Link.l1 = "Grazie! Preferirei non sperimentare ma ti fiderò.";
			Link.l1.go = "Exit";
			AddQuestRecord("ShipRepair", "End");
			CloseQuestHeader("ShipRepair");
		break;		
		
		///////////////////////////////  квестовые ветки
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quali domande hai?","Come posso aiutarti?"),"Hai cercato di farmi una domanda un po' di tempo fa...","Mai ho incontrato persone con tanta curiosità nel mio cantiere navale o in qualsiasi altro luogo di questa città.","Che cosa sono tutte queste domande? Il mio lavoro è costruire navi. Occupiamoci di questo.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea...","Non ho nulla di cui parlare al momento."),"Umph, dove se n'è andata la mia memoria...","Mm, beh...","Bene, lasciaci...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (!CheckAttribute(npchar, "Step_Door"))
			{
				link.l2 = "Ascolta, vorrei passare e quella porta è chiusa a chiave...";
				link.l2.go = "Step_Door_1";
			}

			if ((pchar.questTemp.different == "GiveShipLetters") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakAlexus"))
			{
				link.l1 = "Vorrei proporre un affare.";
				link.l1.go = "Al_ShipLetters_1";// генератор  "Найденные документы"
				pchar.questTemp.different.GiveShipLetters.speakAlexus = true;
			}
			if(CheckAttribute(pchar, "questTemp.AlexClock") && pchar.questTemp.AlexClock == "go") // 280912
			{
				link.l1 = "Sono qui riguardo ai materiali per la fregata.";
				link.l1.go = "clock";
			}
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				link.l1 = "Ascolta, "+npchar.name+", hai visto di recente Miguel Dichoso su Isla Tesoro?";
				link.l1.go = "tieyasal";
			}
		break;
//*************************** Генератор - "Найденные судовые документы" **************
		
		case "Al_ShipLetters_1":
			dialog.text = "Indica le tue condizioni.";
			s1 = "I lucked into finding an absolutely legal ship's documents packet that hasn't been called for search yet.";
			s1 = s1 + "The ship is afloat and it hasn't been excluded from the registry, don't worry. Just a blind fool-owner had the misfortune of losing these papers...";
			link.l1 = s1;
			link.l1.go = "Al_ShipLetters_2";			
		break;
		case "Al_ShipLetters_2":
			s1 = "Let me take a look! It really looks to be freshly filled out. Well, luck is in your favor, sir! ";
			s1 = s1 + "I actually needed a packet just like this. I, in turn, will offer you " + sti(pchar.questTemp.different.GiveShipLetters.price5) + " pesos. What do you say?";
			dialog.text = s1;
			link.l1 = "Vera generosità reale! Naturalmente sono d'accordo!";
			link.l1.go = "Al_ShipLetters_3";
			link.l2 = "No, non credo.";
			link.l2.go = "exit";
		break;
		case "Al_ShipLetters_3":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price5)); 
			ChangeCharacterComplexReputation(pchar,"nobility", -1); 
			OfficersReaction("bad"); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "9");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit(); 
		break;
		

//*************************** Открывание двери ***************************
 		case "Step_Door_1":
			dialog.text = "È corretto. Se vuoi passare attraverso questa porta, devi pagarmi 20000 pesos. Se non paghi, non apro. Questo non è una mensa per i poveri. E non ti consiglio di andarci comunque. Sarà meglio per te se non lo fai...";
			if(sti(pchar.money) >= 20000)
			{
    			link.l1 = "Ecco i tuoi soldi. Apri.";
    			link.l1.go = "Step_Door_2";
            }
            else
            {
    			link.l1 = "Non ho così tanti soldi.";
    			link.l1.go = "Step_Door_3";
            }
            link.l2 = "Assolutamente no! Non pagherei mai per una porta.";
    		link.l2.go = "exit";
		break;
		
 		case "Step_Door_2":
			npchar.Step_Door = true; // fix
			dialog.text = "Entra. La porta è aperta. Non preoccuparti di ringraziarmi!";
			link.l1 = "No, perché no. Grazie, "+npchar.name+"...";
			link.l1.go = "exit";
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", false);
            AddMoneyToCharacter(pchar, -20000);
			pchar.quest.CloseBermudesDungeonDoor.win_condition.l1 = "MapEnter";
            pchar.quest.CloseBermudesDungeonDoor.win_condition = "CloseBermudesDungeonDoor";
		break;
		
 		case "Step_Door_3":
			dialog.text = "Ebbene, quando lo avrai, torna. Altrimenti, non cercare di convincermi. È inutile...";
			link.l1 = "Argh, sono completamente senza parole!";
			link.l1.go = "exit";
		break;
		
	// ------------------------------------------- хронометр Ђлекса ----------------------------------------------// Addon-2016 Jason замена дублонов на песо везде
		case "clock_begin":
			dialog.text = "Su, non essere così severo con un vecchio... Ho davvero bisogno del tuo aiuto, capitano.";
			link.l1 = "Dimmi, maestro. Cosa ti è successo?";
			link.l1.go = "clock_begin_1";
		break;
		
		case "clock_begin_1":
			sTotalTemp = "Steven Dodson";
			if (pchar.questTemp.Alex.Clock == "terrax") sTotalTemp = "Marcus Tyrex";
			dialog.text = "Il nostro nuovo leader dei Fratelli della Costa, "+sTotalTemp+", ha ordinato una nuova nave, una fregata. Ha anche posto compiti piuttosto difficili: uno scafo protetto, velocità veloce e buona manovrabilità più cannoni del calibro più grande possibile\nCapisco che la nave di un ammiraglio, scusa il leader dei fratelli, deve essere qualcosa di speciale, ma ciò significa che ho bisogno di materiali speciali per costruirla. Devi averne sentito parlare. Legno di ferro, resina, seta navale e corde...";
			link.l1 = "Racconta di questo al capo dei Fratelli. O forse hai paura che "+sTotalTemp+" ti taglierà la testa per questo?";
			link.l1.go = "clock_begin_2";
		break;
		
		case "clock_begin_2":
			dialog.text = "Gli ho detto... Il fatto è che il nostro nuovo leader non ha né il tempo né l'opportunità di trovare e portare questi materiali. Devi sapere che tipo di rarità sono. E non c'è modo che io possa costruire una fregata con le caratteristiche dette senza di loro.";
			link.l1 = "E probabilmente proponi che devo trovare i materiali per la nave?";
			link.l1.go = "clock_begin_3";
		break;
		
		case "clock_begin_3":
			dialog.text = "Ebbene, sì. Sei un buon amico del nostro leader. "+sTotalTemp+" dice lui stesso che ti deve molto e che esige tutto il rispetto per te... Quindi ho pensato: dato che sei suo amico, forse non ti dispiacerebbe aiutarlo? E allo stesso tempo: ti rendi conto di che tipo di posizione scomoda mi trovo? Tutti i materiali saranno pagati, "+sTotalTemp+" non è generoso con il suo oro.";
			link.l1 = "Mi dispiace molto, maestro, ma non sono meno occupato di "+sTotalTemp+". Temo che la raccolta dei materiali possa richiedere un'eternità intera. Quindi, sarebbe meglio se chiedessi a qualcun altro.";
			link.l1.go = "clock_exit";
			link.l2 = "Ebbene, se "+sTotalTemp+"ho ordinato una nave da te - quindi ovviamente cercherò di aiutare. Siamo davvero amici, e gli amici devono aiutarsi a vicenda. Di quanti materiali hai bisogno?";
			link.l2.go = "clock_begin_4";
		break;
		
		case "clock_exit":
			dialog.text = "È un peccato. Davvero un peccato. Contavo su di te. Beh, come si dice, no significa no...";
			link.l1 = "...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.AlexClock");
		break;
		
		case "clock_begin_4":
			dialog.text = "Mi mancano 100 unità di legno di ferro, 150 contenitori di resina, 110 rotoli di seta navale e 90 bobine di corde di canapa. Cosa ne pensi? Potresti trovare tutto questo nel corso di quattro mesi? Non credo di avere più tempo.";
			link.l1 = "Posso almeno provare. E per quanto riguarda il pagamento?";
			link.l1.go = "clock_begin_5";
		break;
		
		case "clock_begin_5":
			dialog.text = "Ecco le mie tariffe: legno di ferro a 4000 pesos al pezzo, resine a 1400 pesos al contenitore, seta a 2500 pesos al rotolo e corde a 1500 pesos al giro. E se mi porti tutto questo, riceverai un bel regalo da parte mia.";
			link.l1 = "Che cosa sarà, mi chiedo?";
			link.l1.go = "clock_begin_6";
		break;
		
		case "clock_begin_6":
			dialog.text = "Portami prima i materiali. Ma ti assicuro: ti sarà molto utile, e la cosa è unica, non ce n'è un'altra nei Caraibi, o in tutto il mondo fino ad ora. Spero che quella piccola scintilla di curiosità abbia acceso il tuo interesse a raccogliere i materiali per me.";
			link.l1 = "Ebbene, sei scaltro come un leprechauno, padrone! Va bene, hai ottenuto un accordo.";
			link.l1.go = "clock_begin_7";
		break;
		
		case "clock_begin_7":
			dialog.text = "Sono molto contento. Non vedo l'ora del tuo ritorno.";
			link.l1 = "Spero che non ci metta troppo tempo...";
			link.l1.go = "clock_begin_8";
		break;
		
		case "clock_begin_8":
			DialogExit();
			pchar.questTemp.AlexClock = "go";
			npchar.quest.clock = "true";
			SetFunctionTimerCondition("AlexClock_Over", 0, 0, 122, false); // таймер
			AddQuestRecord("alex_clock", "1");
			// запоминаем переменные
			pchar.questTemp.AlexClock.Sandal = 100;
			pchar.questTemp.AlexClock.Oil = 150;
			pchar.questTemp.AlexClock.Shipsilk = 110;
			pchar.questTemp.AlexClock.Ropes = 90;
		break;
		
		case "clock":
			dialog.text = "Eccellente! Cosa mi hai portato oggi?";
			if (GetSquadronGoods(pchar, GOOD_SANDAL) > 0 && !CheckAttribute(npchar, "quest.sandal"))
			{
				iSan = GetSquadronGoods(pchar, GOOD_SANDAL);
				link.l1 = "Legno di ferro, nella quantità di "+FindRussianQtyString(iSan)+".";
				link.l1.go = "sandal";
			}
			if (GetSquadronGoods(pchar, GOOD_OIL) > 0 && !CheckAttribute(npchar, "quest.oil"))
			{
				iOil = GetSquadronGoods(pchar, GOOD_OIL);
				link.l2 = "Resine, nella quantità di "+FindRussianQtyString(iOil)+".";
				link.l2.go = "oil";
			}
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) > 0 && !CheckAttribute(npchar, "quest.shipsilk"))
			{
				iSil = GetSquadronGoods(pchar, GOOD_SHIPSILK);
				link.l3 = "Seta da nave, nella quantità di "+FindRussianQtyString(iSil)+".";
				link.l3.go = "shipsilk";
			}
			if (GetSquadronGoods(pchar, GOOD_ROPES) > 0 && !CheckAttribute(npchar, "quest.ropes"))
			{
				iRop = GetSquadronGoods(pchar, GOOD_ROPES);
				link.l4 = "Cordami di canapa, nella quantità di "+FindRussianQtyString(iRop)+".";
				link.l4.go = "ropes";
			}
			link.l5 = "Niente al momento. Volevo solo assicurarmi che abbiamo ancora un accordo.";
			link.l5.go = "exit";
		break;
		
		case "clock_1":
			if (CheckAttribute(npchar, "quest.sandal") && CheckAttribute(npchar, "quest.oil") && CheckAttribute(npchar, "quest.shipsilk") && CheckAttribute(npchar, "quest.ropes")) // все привез
			{
				dialog.text = "Meraviglioso! Ho tutti i materiali di cui ho bisogno. Grazie mille per il tuo aiuto, capitano. Mi hai aiutato tantissimo.";
				link.l1 = "Sì, in qualsiasi momento, padrone. Sono molto contento anch'io: ho aiutato un amico e ho guadagnato dei bei soldi. E ora torniamo alla nostra conversazione sul tuo misterioso oggetto che mi hai promesso.";
				link.l1.go = "clock_2";
			}
			else
			{
				dialog.text = "Hai altre sorprese per me, capitano?";
				link.l1 = "Purtroppo, è tutto per ora. Continua solo ad aspettare.";
				link.l1.go = "exit";
				link.l2 = "Sì, ho un'altra cosa...";
				link.l2.go = "clock";
			}
		break;
		
		case "sandal": // бакаут
			amount = sti(pchar.questTemp.AlexClock.Sandal);
			iSan = GetSquadronGoods(pchar, GOOD_SANDAL);
			iTemp = amount-iSan;
			if (iTemp > 0) // ещё не все привез
			{
				iSum = 4000*iSan;
				dialog.text = "Bene, va bene. Avrò anche bisogno di "+FindRussianQtyString(amount)+" di legno di ferro. Mi hai portato "+FindRussianQtyString(iSan)+". . Quindi, cosa ti rimane da portarmi è "+FindRussianQtyString(iTemp)+". Va bene, al tasso di 4000 pesos per pezzo, la tua ricompensa ammonta a "+FindRussianMoneyString(iSum)+". Per favore, prendilo.";
				link.l1 = "Grazie! Avrai il resto presto.";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_SANDAL, iSan);
				pchar.questTemp.AlexClock.Sandal = iTemp; // столько осталось довезти
				AddQuestRecord("alex_clock", "2");
				AddQuestUserData("alex_clock", "sGood", "ironwood");
				AddQuestUserData("alex_clock", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				iSum = 4000*amount;
				dialog.text = "Bene, va bene. Avrò anche bisogno "+FindRussianQtyString(amount)+"  di legno di ferro. Mi hai portato "+FindRussianQtyString(iSan)+". Quindi, ci siamo occupati del legno di ferro ora! Bene, al tasso di 4000 pesos per pezzo, la tua ricompensa totale a "+FindRussianMoneyString(iSum)+". Per favore, prendilo.";
				link.l1 = "Grazie!";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_SANDAL, amount);
				npchar.quest.sandal = "true";
				AddQuestRecord("alex_clock", "3");
				AddQuestUserData("alex_clock", "sGood", "ironwood");
			}
			AddMoneyToCharacter(pchar, iSum);
		break;
		
		case "oil": // смолы
			amount = sti(pchar.questTemp.AlexClock.Oil);
			iOil = GetSquadronGoods(pchar, GOOD_OIL);
			iTemp = amount-iOil;
			if (iTemp > 0) // ещё не все привез
			{
				iSum = 1400*iOil;
				dialog.text = "Bene, ok. Avrò anche bisogno "+FindRussianQtyString(amount)+" resine. Mi hai portato "+FindRussianQtyString(iOil)+". Quindi, cosa ti rimane da portarmi è "+FindRussianQtyString(iTemp)+". Va bene, al tasso di 1400 pesos per contenitore, la tua ricompensa totale a "+FindRussianMoneyString(iSum)+". Per favore, prendilo.";
				link.l1 = "Grazie! Avrete il resto presto.";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_OIL, iOil);
				pchar.questTemp.AlexClock.Oil = iTemp; // столько осталось довезти
				AddQuestRecord("alex_clock", "2");
				AddQuestUserData("alex_clock", "sGood", "resins");
				AddQuestUserData("alex_clock", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				iSum = 1400*amount;
				dialog.text = "Bene, va bene. Avrò bisogno anche di "+FindRussianQtyString(amount)+" resine. Mi hai portato "+FindRussianQtyString(iOil)+". Quindi, ci siamo occupati delle resine ora! Bene, al tasso di 1400 pesos per contenitore, la tua ricompensa ammonta a "+FindRussianMoneyString(iSum)+". Per favore, prendilo.";
				link.l1 = "Grazie!";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_OIL, amount);
				npchar.quest.oil = "true";
				AddQuestRecord("alex_clock", "3");
				AddQuestUserData("alex_clock", "sGood", "resins");
			}
			AddMoneyToCharacter(pchar, iSum);
		break;
		
		case "shipsilk": // шёлк
			amount = sti(pchar.questTemp.AlexClock.Shipsilk);
			iSil = GetSquadronGoods(pchar, GOOD_SHIPSILK);
			iTemp = amount-iSil;
			if (iTemp > 0) // ещё не все привез
			{
				iSum = 2600*iSil;
				dialog.text = "Bene, d'accordo. Avrò anche bisogno di "+FindRussianQtyString(amount)+" seta. Mi hai portato "+FindRussianQtyString(iSil)+". Quindi, cosa ti rimane da portarmi è "+FindRussianQtyString(iTemp)+". Va bene, al tasso di 2600 pesos per pezzo, la tua ricompensa totale è di "+FindRussianMoneyString(iSum)+". Per favore, prendilo.";
				link.l1 = "Grazie! Avrete il resto presto.";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_SHIPSILK, iSil);
				pchar.questTemp.AlexClock.Shipsilk = iTemp; // столько осталось довезти
				AddQuestRecord("alex_clock", "2");
				AddQuestUserData("alex_clock", "sGood", "silk");
				AddQuestUserData("alex_clock", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				iSum = 2600*amount;
				dialog.text = "Bene, va bene. Avrò anche bisogno di "+FindRussianQtyString(amount)+" seta. Mi hai portato "+FindRussianQtyString(iSil)+". Quindi, ci siamo occupati della seta adesso! Quindi, al tasso di 2600 pesos per pezzo, la tua ricompensa totale è "+FindRussianMoneyString(iSum)+". Per favore, prendilo.";
				link.l1 = "Grazie!";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_SHIPSILK, amount);
				npchar.quest.shipsilk = "true";
				AddQuestRecord("alex_clock", "3");
				AddQuestUserData("alex_clock", "sGood", "silk");
			}
			AddMoneyToCharacter(pchar, iSum);
		break;
		
		case "ropes": // канаты
			amount = sti(pchar.questTemp.AlexClock.Ropes);
			iRop = GetSquadronGoods(pchar, GOOD_ROPES);
			iTemp = amount-iRop;
			if (iTemp > 0) // ещё не все привез
			{
				iSum = 1500*iRop;
				dialog.text = "Bene, va bene. Avrò anche bisogno "+FindRussianQtyString(amount)+" corde. Mi hai portato "+FindRussianQtyString(iRop)+". Quindi, cosa ti rimane da portarmi è "+FindRussianQtyString(iTemp)+". Quindi, al tasso di 1500 pesos per pezzo, la tua ricompensa totale è di "+FindRussianMoneyString(iSum)+". Per favore, prendilo.";
				link.l1 = "Grazie! Avrai il resto presto.";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_ROPES, iRop);
				pchar.questTemp.AlexClock.Ropes = iTemp; // столько осталось довезти
				AddQuestRecord("alex_clock", "2");
				AddQuestUserData("alex_clock", "sGood", "ropes");
				AddQuestUserData("alex_clock", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				iSum = 1500*amount;
				dialog.text = "Bene, va bene. Avrò anche bisogno di "+FindRussianQtyString(amount)+" corde. Mi hai portato "+FindRussianQtyString(iRop)+". Quindi, ci siamo già occupati delle corde. Bene, al tasso di 1500 pesos per pezzo, la tua ricompensa ammonta a "+FindRussianMoneyString(iSum)+". Per favore, prendilo.";
				link.l1 = "Grazie!";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_ROPES, amount);
				npchar.quest.ropes = "true";
				AddQuestRecord("alex_clock", "3");
				AddQuestUserData("alex_clock", "sGood", "ropes");
			}
			AddMoneyToCharacter(pchar, iSum);
		break;
		
		case "clock_2":
			dialog.text = "Sì, sì... riguardo alla mia cosa, naturalmente. M-m-mmm...Hmmm... dove l'ho messa... ahhh...";
			link.l1 = "Cosa succede, maestro? Sembri piuttosto preoccupato. C'è qualcosa che non va? Qualche tipo di problema?";
			link.l1.go = "clock_3";
		break;
		
		case "clock_3":
			dialog.text = "Esattamente. Problemi. Recenti. Dannati quei cacciatori di tesori...";
			link.l1 = "Calma, calma. Non è buono per la tua età preoccuparti così tanto. Dio non voglia, potresti essere a un battito di distanza. Chi costruirebbe allora la fregata per il capo dei Fratelli? Calmati e spiegami chi sono questi cacciatori di tesori?";
			link.l1.go = "clock_4";
		break;
		
		case "clock_4":
			dialog.text = "Là vicino al mio tavolo c'è una porta. Conduce direttamente in una vecchia cripta. In questa cripta, in uno dei bauli del tesoro, conservo la mia cassetta di metallo con gli oggetti che erano con me quando sono stato risucchiato in quel dannato imbuto vent'anni fa, e sono finito qui...";
			link.l1 = "Che imbuto? Di cosa stai parlando?";
			link.l1.go = "clock_5";
		break;
		
		case "clock_5":
			dialog.text = "Ah, scusa per le mie fantasticherie. Non è facile essere vecchio, giovane. Perdonami. Ma è irrilevante. Quello che è rilevante è che una scatola con un regalo per te si trova nel baule che è attualmente nel dungeon occupato da alcuni mascalzoni. Non sono dei nostri, né sono dell'Isla Tesoro. Cacciatori di tesori, qualcuno deve averli informati che questo posto è pieno di tesori. Non oserebbero mostrarsi qui, tuttavia ho troppo paura di visitarli, capisci? I loro volti sono...";
			link.l1 = "Capisco. Apri la tua porta. Scaccerò i tuoi ospiti indesiderati.";
			link.l1.go = "clock_6";
		break;
		
		case "clock_6":
			dialog.text = "Così, senza più? Li sconfiggerai? Da solo? Non hai paura? Abbiamo un intero insediamento che combatterà per te se solo lo chiedi...";
			link.l1 = "Meno chiacchiere, più azione, maestro. Apri questa porta e lascia il resto a me. In quale baule tieni le tue cose?";
			link.l1.go = "clock_7";
		break;
		
		case "clock_7":
			dialog.text = "Proprio lungo il corridoio c'è una collezione di barili di legno vuoti. Dietro di loro, in un luogo appartato sul pavimento, c'è un piccolo baule. Ho messo un lucchetto, quindi dubito che quegli intrusi riuscirebbero a mettere le mani sporche dentro, anche se lo trovassero. Ecco, prendi la chiave.";
			link.l1 = "Sono contento che tu pensi in anticipo. Aspetta qui e non andare da nessuna parte.";
			link.l1.go = "clock_8";
		break;
		
		case "clock_8":
			DialogExit();
			GiveItem2Character(pchar, "key3"); 
			bDisableFastReload = true;//закрыть переход
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload1_back", true);
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", false);
			LAi_LocationDisableOfficersGen("Bermudes_Dungeon", true);//офицеров не пускать
			pchar.quest.Alex_Chest.win_condition.l1 = "location";
			pchar.quest.Alex_Chest.win_condition.l1.location = "Bermudes_Dungeon";
			pchar.quest.Alex_Chest.function = "AlexClock_Chest";
			pchar.quest.AlexClock_Over.over = "yes"; //снять прерывание
			pchar.questTemp.AlexClock = "chest";
			AddQuestRecord("alex_clock", "3");
		break;
		
		case "clock_complete":
			dialog.text = "Hanno solo ascoltato te e se ne sono andati?";
			link.l1 = "Esatto. Si sono rivelati dei bravi ragazzi molto educati. Ho spiegato loro che la loro presenza spaventa il famoso maestro d'ascia anziano e per rispetto della tua vecchiaia, hanno lasciato i locali. Puoi scendere là sotto senza preoccupazioni.";
			link.l1.go = "clock_complete_1";
		break;
		
		case "clock_complete_1":
			dialog.text = "Ah-ah, stai prendendo in giro un vecchio! Va bene. Dammi la mia scatola e la aprirò per darti il dispositivo che hai meritato onestamente.";
			link.l1 = "Per favore, prendilo...";
			link.l1.go = "clock_complete_2";
		break;
		
		case "clock_complete_2":
			RemoveItems(pchar, "alexs_chest", 1);
			dialog.text = "Grazie! Apriamolo. Prendi, questo è per te. Un timer meccanico automatico, nessuno qui produce tali dispositivi e nessuno lo farà per i prossimi trecento anni... eh, scusa, perdonami vecchio uomo. Voglio solo dire che questa cosa è unica\nFa tutto il lavoro da sola, non avrai bisogno di stupidi orologi a sabbia e così via. Nessun errore! Basta tenerlo al sicuro da colpi diretti e acqua altrimenti lo perderai. Persino una scimmia può usare questo timer.";
			link.l1 = "Guarda un po'! Non ho mai visto nulla di così miracoloso nella mia vita! Grazie, maestro.";
			link.l1.go = "clock_complete_3";
		break;
		
		case "clock_complete_3":
			GiveItem2Character(pchar, "clock3");
			Log_Info("You've received an automatic mechanical timer");
			SetAlchemyRecipeKnown("sextant2");
			PlaySound("interface\important_item.wav");
			dialog.text = "Prego. Ora saprai sempre con certezza che ore sono. Non chiedermi dove l'ho preso. Non te lo dirò.";
			link.l1 = "Ognuno ha i suoi segreti, vero maestro? Va bene... tieni i tuoi segreti e non mi intrometterò nei tuoi affari. Grazie per il regalo!";
			link.l1.go = "clock_complete_4";
		break;
		
		case "clock_complete_4":
			dialog.text = "E grazie per il tuo aiuto, capitano. Vieni a trovarmi qualche volta. Non dimenticare un vecchio costruttore di navi.";
			link.l1 = "Come potrei dimenticarti... Comunque, lo farò sicuramente, Alexus il Maestro. Arrivederci!";
			link.l1.go = "clock_complete_5";
		break;
		
		case "clock_complete_5":
			DialogExit();
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", true);
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload1_back", false);
			LocatorReloadEnterDisable("Bermudes_Dungeon", "reload2_back", false);
			LAi_LocationDisableOfficersGen("Bermudes_Dungeon", false);
			AddQuestRecord("alex_clock", "5");
			CloseQuestHeader("alex_clock");
			DeleteAttribute(pchar, "questTemp.AlexClock");
			// belamour legendary edition на пару с Акулой
			pchar.questTemp.SharkGoldFleet.KGBB = true;
			if(CheckAttribute(pchar,"questTemp.SharkFrigate")) SetTimerCondition("SharkGoldFleet", 0, 0, 30, false);
		break;
	// <-- хронометр Алекса
		
		// город майя
		case "tieyasal":
			dialog.text = "Aha, Miguel! Il mio vecchio conoscente. Me lo ricordo. Mi chiedeva di ogni piccolo dettaglio più e più volte. Ma come avrei dovuto spiegargli come era costruita una radio all'interno quando non aveva nemmeno visto un semplice telegrafo?";
			link.l1 = "Cosa?.. Di cosa stai parlando, maestro?";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Oh, scusa, giovane. Non prestare molta attenzione alle mie parole... Il nostro curioso Michel ha soddisfatto la sua curiosità ed è sparito. Solo tre giorni fa abbiamo fatto due chiacchiere.";
			link.l1 = "Dove si trova Miguel in questo momento, se non ti dispiace che io chieda?";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = "Chissà. Forse sta facendo affari a Sharptown o forse è già partito da Isla Tesoro.";
			link.l1 = "Capisco. Grazie, maestro!";
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			DialogExit();
			npchar.quest.tieyasal = "true";
		break;
		
		// Калеуче
		case "FDM":
			if(CheckAttribute(npchar, "quest.FDM_secondtime"))
				dialog.text = "Di nuovo con la tua 'nave fantasma'... Sappilo - ci sto lavorando solo nella speranza che si trasformi in qualcosa di decente. Altrimenti, non la toccherei nemmeno. Penso che tutti in mare condividano un'opinione simile. Cosa vuoi farci questa volta?";
			else	
				dialog.text = "Ah, la 'nave fantasma'! Le madri usano il tuo galeone per spaventare i bambini disubbidienti. E hai deciso di tenere quella maledetta nave invece di affondarla! I marinai tremano quando vedono la tua nave all'orizzonte... Quindi, cosa vuoi fare con essa?";
			if (!CheckAttribute(npchar, "quest.FDM_cabin"))
			{
				link.l1 = "Mi piace l'idea di piccoli codardi che sono spaventati a morte. Ma l'interno mi rende triste. Hai visto la cabina? Sembra una bara. Tutta quella muffa e polvere. Voglio sistemarlo. Puoi farlo, maestro?";
				link.l1.go = "FDM_cabin";
			}
			if (!CheckAttribute(npchar, "quest.FDM_sails"))
			{
				link.l2 = "Sono stufo di questi stracci neri lacerati. Lo ammetto, catturano il vento tanto bene quanto le vele normali ma la vista... Ripugnante. Voglio delle normali vele bianche come la neve. Sei d'accordo, maestro?";
				link.l2.go = "FDM_sails";
			}
			
			if (!CheckAttribute(npchar, "quest.FDM_hull"))
			{
				link.l3 = "Ebbene, penso che sia giunto il momento di trasformarlo in qualcosa di decente. La nave è buona, l'equipaggio ci è abituato, ma non è dignitoso per un capitano rispettabile navigare su una nave che può far cagare addosso agli adulti, figuriamoci ai bambini. Voglio ricostruirla completamente così che gli altri capitani la invidino quando vedono la mia nave, invece di farsi il segno della croce. E a chi dovrei rivolgermi per questo se non al miglior costruttore di navi dell'arcipelago?";
				link.l3.go = "FDM_hull";
			}
		break;
		
		case "FDM_cabin":
			dialog.text = "Perché no? Le mie mani sono ancora abili. Il tuo galeone è enorme, quindi potrei addirittura costruire una cabina reale come quelle che costruiscono nelle navi da guerra e nei vascelli. O possiamo mantenere una cabina standard. La scelta è tua?";
			link.l1 = "Costruisci la cabina della nave di linea! Tutti moriranno d'invidia...";
			link.l1.go = "FDM_cabin_m";
			link.l2 = "Non c'è motivo di eccessivi lussi. Mantieni lo standard.";
			link.l2.go = "FDM_cabin_s";
		break;
		
		case "FDM_cabin_m":
			dialog.text = "Bene. Dieci casse di dobloni e sarà fatto in cinque giorni.";
			link.l1 = "Affare fatto!";
			link.l1.go = "FDM_cabin_m1";
			link.l2 = "Dieci casse? Millecinquecento dobloni? Hm, ho bisogno di tempo per considerare tali spese...";
			link.l2.go = "exit";
		break;
		
		case "FDM_cabin_s":
			dialog.text = "Bene. Sette casse di dobloni e sarà fatto in cinque giorni.";
			link.l1 = "Affare fatto!";
			link.l1.go = "FDM_cabin_s1";
			link.l2 = "Sette casse? Più di mille dobloni? Hm, ho bisogno di tempo per considerare tali spese...";
			link.l2.go = "exit";
		break;
		
		case "FDM_cabin_m1":
			iTemp = GetCharacterItem(pchar, "Chest");
			npchar.quest.FDM_cabin = 10;
			npchar.quest.FDM_cabin.type = "Cabin_Huge";
			dialog.text = "Bene, starò aspettando un pagamento.";
			if (iTemp > 0)
			{
				link.l1 = "Ho delle casse con me. Vediamo. Eccole, "+FindRussianQtyString(iTemp)+".";
				link.l1.go = "FDM_cabin_pay";
			}
			else
			{
				link.l1 = "Devo andare e mettere monete nei forzieri.";
				link.l1.go = "FDM_cabin_wait";
			}
		break;
		
		case "FDM_cabin_s1":
			iTemp = GetCharacterItem(pchar, "Chest");
			npchar.quest.FDM_cabin = 7;
			npchar.quest.FDM_cabin.type = "Cabin";
			dialog.text = "Bene, aspetterò il pagamento.";
			if (iTemp > 0)
			{
				link.l1 = "Porto con me dei bauli. Vediamo. Ecco, "+FindRussianQtyString(iTemp)+".";
				link.l1.go = "FDM_cabin_pay";
			}
			else
			{
				link.l1 = "Devo andare e mettere monete nei bauli.";
				link.l1.go = "FDM_cabin_wait";
			}
		break;
		
		case "FDM_cabin_wait":
			DialogExit();
			npchar.quest.FDM_full = "cabin";
		break;
		
		case "FDM_cabin_pay":
			iTemp = GetCharacterItem(pchar, "Chest");
			amount = sti(npchar.quest.FDM_cabin)-iTemp;
			Log_Info("You have given chests to Master Alexus");
			PlaySound("interface\important_item.wav");
			if (amount <= 0) // всё принес
			{
				RemoveItems(pchar, "chest", sti(npchar.quest.FDM_cabin));
				dialog.text = "Allora, dovevi portarmi "+FindRussianQtyString(sti(npchar.quest.FDM_cabin))+" casse, hai portato "+FindRussianQtyString(iTemp)+". Ho il pagamento. Ora è il mio turno. Vai e fai un giro. Non preoccuparti, farò del mio meglio.";
				link.l1 = "Bene...";
				link.l1.go = "FDM_cabin_do";
			}
			else
			{
				RemoveItems(pchar, "chest", iTemp);
				dialog.text = "Allora, hai dovuto portarmi "+FindRussianQtyString(sti(npchar.quest.FDM_cabin))+" casse, hai portato "+FindRussianQtyString(iTemp)+". "+FindRussianQtyString(amount)+" casse rimaste.";
				link.l1 = "Molto bene, padrone.";
				link.l1.go = "FDM_cabin_wait";
				npchar.quest.FDM_cabin = amount;
			}
		break;
		
		case "FDM_cabin_do":
			DialogExit();
			SetLaunchFrameFormParam("Five days later..."+ NewStr() +"Master Alexus has done his job", "", 0, 5);
			WaitDate("", 0, 0, 5, 0, 10); //крутим время
			LaunchFrameForm();
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			shTo = &RealShips[sti(Pchar.Ship.Type)];
			shTo.CabinType = npchar.quest.FDM_cabin.type;
			if (CheckAttribute(npchar, "quest.FDM_sails")) npchar.quest.FDM_full = "done";
			else DeleteAttribute(npchar, "quest.FDM_full");
		break;
		
		case "FDM_sails":
			dialog.text = "Certo, posso farlo! Bene-bene... Questo significa che dobbiamo buttare via ogni vecchio straccio sporco e mettere nuove e pulite vele di cotone. C'è molto lavoro da fare qui. Centomila pesos per il lavoro e i materiali. Affare?";
			if (sti(Pchar.money) >= 100000)
			{
				link.l1 = "Certo, per me va bene. Affare fatto!";
				link.l1.go = "FDM_sails_do";
			}
			link.l2 = "Mm. Suppongo che ho bisogno di pensarci...";
			link.l2.go = "exit";
		break;
		
		case "FDM_sails_do":
			AddMoneyToCharacter(pchar, -100000);
			dialog.text = "Bene. Ho le monete, è ora di fare il mio lavoro. Gira in giro fino a quando non è fatto e non ti preoccupare.";
			link.l1 = "Bene...";
			link.l1.go = "FDM_sails_done";
		break;
		
		case "FDM_sails_done":
			DialogExit();
			SetLaunchFrameFormParam("Two days later..."+ NewStr() +"Master Alexus has done his job", "", 0, 5);
			WaitDate("", 0, 0, 2, 0, 10); //крутим время
			LaunchFrameForm();
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			SetShipSailsFromFile(pchar, "ships/parus_silk.tga");
			SetSailsColor(pchar, 0);//белый хлопковый парус
			npchar.quest.FDM_sails = "true";
			if (CheckAttribute(npchar, "quest.FDM_cabin")) npchar.quest.FDM_full = "done";
		break;
		//--> Xenon
		case "FDM_hull":
			dialog.text = "Ebbene, sono contento di sentire finalmente questo. E in effetti, sembri un bravo ragazzo, eppure navighi su chissà cosa. Ma lascia che ti avverta in anticipo, questo lavoro non è solo per qualche ora, e ti costerà un bel po' di soldi.";
			link.l1 = "Ok, puoi essere un po' più specifico?";
			link.l1.go = "FDM_hull_01";
		break;

		case "FDM_hull_01":
			dialog.text = "Bene, facciamo i conti... Per una revisione completa dello scafo della nave, avrò bisogno di 150 unità di legno di ferro, 130 bobine di corda, 170 rotoli di seta navale e 200 barili di resina. Per tutto questo, prendo 250 mila pesos. E non mi guardare così - la maggior parte di quei soldi andrà comunque al lavoro! Dopotutto, non stiamo ricostruendo un tartano.";
			link.l1 = "Non credo. Non ho voglia di trasportare tale quantità di materiali e di pagare un quarto di milione per il lavoro. Immagino che continuerò a navigare così com'è.";
			link.l1.go = "FDM_hull_thinking";
			link.l2 = "Eh, cosa non faremmo per la nostra nave... Va bene, abbiamo un accordo.";
			link.l2.go = "FDM_hull_02";
		break;

		case "FDM_hull_02":
			dialog.text = "Bene, meno chiacchiere, più azione. Aspetto il denaro da te così posso iniziare ad acquistare tutto ciò di cui ho bisogno. Una volta che ho i soldi, puoi iniziare a portarmi i materiali. E mi metterò al lavoro sulla tua nave.";
			if(sti(pchar.money) >= 250000)
			{
    			link.l1 = "Ebbene, il denaro non è un problema. L'ho con me. Ecco a te, maestro.";
    			link.l1.go = "FDM_hull_waitmaterials";
            }
            else
            {
    			link.l1 = "Al momento, non ho quel tipo di soldi. Aspetta un po', te li porterò.";
    			link.l1.go = "FDM_hull_waitmoney";
            }
		break;

		case "FDM_hull_waitmaterials":
			addMoneyToCharacter(pchar, -250000);
			npchar.quest.FDMsandal = 0;
			npchar.quest.FDMoil = 0;
			npchar.quest.FDMshipsilk = 0;
			npchar.quest.FDMropes = 0;
			AddQuestRecord("renovate_fdm", "1");

			npchar.quest.FDM_hull = "hull_waitmaterials";
			dialog.text = "Non hai paura di girare per un insediamento pirata con una somma così cospicua, hehe? Va bene, sto scherzando, sono tutti persone oneste, a modo loro. Ora sto aspettando i materiali. Come promemoria, dovrai portare un totale di 150 legni di ferro, 130 bobine di corde, 170 rotoli di seta per navi e 200 barili di resina.";
			link.l1 = "Resisti, ti porterò i tuoi materiali.";
			link.l1.go = "exit";
		break;

		case "FDM_hull_checkmaterials":
			dialog.text = "Molto bene! Cosa mi hai portato oggi?";
			if (GetSquadronGoods(pchar, GOOD_SANDAL) > 0 && sti(npchar.quest.FDMsandal) < 150)
			{
				iSan = GetSquadronGoods(pchar, GOOD_SANDAL);
				link.l1 = "Legno di ferro nella quantità di "+FindRussianQtyString(iSan)+".";
				link.l1.go = "FDM_sandal";
			}
			if (GetSquadronGoods(pchar, GOOD_OIL) > 0 && sti(npchar.quest.FDMoil) < 200)
			{
				iOil = GetSquadronGoods(pchar, GOOD_OIL);
				link.l2 = "Resina nella quantità di "+FindRussianQtyString(iOil)+".";
				link.l2.go = "FDM_oil";
			}
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) > 0 && sti(npchar.quest.FDMshipsilk) < 170)
			{
				iSil = GetSquadronGoods(pchar, GOOD_SHIPSILK);
				link.l3 = "Seta navale nella quantità di "+FindRussianQtyString(iSil)+".";
				link.l3.go = "FDM_shipsilk";
			}
			if (GetSquadronGoods(pchar, GOOD_ROPES) > 0 && sti(npchar.quest.FDMropes) < 130)
			{
				iRop = GetSquadronGoods(pchar, GOOD_ROPES);
				link.l4 = "Cordame in quantità di "+FindRussianQtyString(iRop)+".";
				link.l4.go = "FDM_ropes";
			} 
			link.l5 = "Niente ancora. Volevo solo assicurarmi che l'accordo sia ancora valido.";
			link.l5.go = "exit";
		break;

		case "FDM_hull_checkmaterials_1":
			if (sti(npchar.quest.FDMsandal) > 149 && sti(npchar.quest.FDMoil) > 199 && sti(npchar.quest.FDMshipsilk) > 169 && sti(npchar.quest.FDMropes) > 129)
			{
				dialog.text = "Meraviglioso! Tutti i materiali sono contabilizzati. Ora, fammi prendere quel mostro dalle tue mani. Finalmente, avrà un aspetto appropriato.";
				link.l1 = "Ok, basta lamentarsi, maestro. Sto aspettando con ansia il risultato.";
				link.l1.go = "FDM_hull_building";
			}
			else
			{
				dialog.text = "Hai qualcos'altro per illuminare la mia giornata, Capitano?";
				link.l1 = "Purtroppo, è tutto per ora.";
				link.l1.go = "exit";
				link.l2 = "Sì, ho qualcos'altro per te...";
				link.l2.go = "FDM_hull_checkmaterials";
			}
		break;

		case "FDM_sandal": // бакаут
			amount = 150 - sti(npchar.quest.FDMsandal);
			iSan = GetSquadronGoods(pchar, GOOD_SANDAL);
			iTemp = amount-iSan;
			if (iTemp > 0) 
			{
				dialog.text = "Vediamo... Ho bisogno "+FindRussianQtyString(amount)+" di legno ferro. Hai portato "+FindRussianQtyString(iSan)+". di legno di ferro. Quindi, devi ancora portarmi "+FindRussianQtyString(iTemp)+".";
				link.l1 = "Grazie! Ti darò il resto presto.";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_SANDAL, iSan);
				npchar.quest.FDMsandal = sti(npchar.quest.FDMsandal) + iSan;
				AddQuestRecord("renovate_fdm", "2");
				AddQuestUserData("renovate_fdm", "sGood", "ironwood");
				AddQuestUserData("renovate_fdm", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				dialog.text = "Vediamo... Mi serve ancora "+FindRussianQtyString(amount)+" di legno di ferro. Mi hai portato  "+FindRussianQtyString(iSan)+". Quindi, abbiamo finito con il legno di ferro!";
				link.l1 = "Grazie!";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_SANDAL, amount);
				npchar.quest.FDMsandal = sti(npchar.quest.FDMsandal) + amount;
				AddQuestRecord("renovate_fdm", "3");
				AddQuestUserData("renovate_fdm", "sGood", "ironwood"); 
			}
		break;

		case "FDM_oil": // смолы
			amount = 200 - sti(npchar.quest.FDMoil);
			iOil = GetSquadronGoods(pchar, GOOD_OIL);
			iTemp = amount-iOil;
			if (iTemp > 0) 
			{
				dialog.text = "Vediamo... Ho bisogno "+FindRussianQtyString(amount)+" di resina. Hai portato "+FindRussianQtyString(iOil)+". Quindi, devi ancora portarmi "+FindRussianQtyString(iTemp)+".";
				link.l1 = "Grazie! Ti darò il resto presto.";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_OIL, iOil);
				npchar.quest.FDMoil = sti(npchar.quest.FDMoil) + iOil;
				AddQuestRecord("renovate_fdm", "2");
				AddQuestUserData("renovate_fdm", "sGood", "resin");
				AddQuestUserData("renovate_fdm", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				dialog.text = "Vediamo... Mi serve ancora "+FindRussianQtyString(amount)+" di resina. Mi hai portato "+FindRussianQtyString(iOil)+". Quindi, abbiamo finito con la resina!";
				link.l1 = "Grazie!";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_OIL, amount);
				npchar.quest.FDMoil = makeint(npchar.quest.FDMoil) + amount;
				AddQuestRecord("renovate_fdm", "3");
				AddQuestUserData("renovate_fdm", "sGood", "resin");
			}
		break;

		case "FDM_shipsilk": // шёлк
			amount = 170 - sti(npchar.quest.FDMshipsilk);
			iSil = GetSquadronGoods(pchar, GOOD_SHIPSILK);
			iTemp = amount-iSil;
			if (iTemp > 0) 
			{
				dialog.text = "Vediamo... Mi serve "+FindRussianQtyString(amount)+" di seta della nave. Hai portato "+FindRussianQtyString(iSil)+". Quindi, devi ancora portarmi "+FindRussianQtyString(iTemp)+".";
				link.l1 = "Grazie! Ti darò il resto presto";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_SHIPSILK, iSil);
				npchar.quest.FDMshipsilk = sti(npchar.quest.FDMshipsilk) + iSil;
				AddQuestRecord("renovate_fdm", "2");
				AddQuestUserData("renovate_fdm", "sGood", "ship silk");
				AddQuestUserData("renovate_fdm", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				dialog.text = "Vediamo... Mi serve ancora "+FindRussianQtyString(amount)+" di seta da nave. Quindi, devi ancora portarmi "+FindRussianQtyString(iSil)+". Quindi, abbiamo finito con la seta della nave";
				link.l1 = "Grazie!";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_SHIPSILK, amount);
				npchar.quest.FDMshipsilk = sti(npchar.quest.FDMshipsilk) + amount;
				AddQuestRecord("renovate_fdm", "3");
				AddQuestUserData("renovate_fdm", "sGood", "ship silk"); 
			}
		break;

		case "FDM_ropes": // канаты
			amount = 170 - sti(npchar.quest.FDMropes);
			iRop = GetSquadronGoods(pchar, GOOD_ROPES);
			iTemp = amount-iRop;
			if (iTemp > 0) 
			{
				dialog.text = "Vediamo... Mi serve "+FindRussianQtyString(amount)+" di corde. Hai portato "+FindRussianQtyString(iRop)+". Quindi, devi ancora portarmi "+FindRussianQtyString(iTemp)+".";
				link.l1 = "Grazie! Ti darò il resto presto";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_ROPES, iRop);
				npchar.quest.FDMropes = sti(npchar.quest.FDMropes) + iRop;
				AddQuestRecord("renovate_fdm", "2");
				AddQuestUserData("renovate_fdm", "sGood", "ropes");
				AddQuestUserData("renovate_fdm", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				dialog.text = "Vediamo... Mi serve  "+FindRussianQtyString(amount)+" di corde. Hai portato "+FindRussianQtyString(iRop)+". Quindi, abbiamo finito con le corde!";
				link.l1 = "Grazie!";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_ROPES, amount);
				npchar.quest.FDMropes = sti(npchar.quest.FDMropes) + amount;
				AddQuestRecord("renovate_fdm", "3");
				AddQuestUserData("renovate_fdm", "sGood", "ropes");
			}
		break;

		case "FDM_hull_thinking":
			DialogExit();
			npchar.quest.FDM_secondtime = true;
		break;

		case "FDM_hull_waitmoney":
			DialogExit();
			npchar.quest.FDM_hull = "hull_waitmoney";
		break;

		case "FDM_hull_givemoney":
			dialog.text = "Ebbene, hai portato i soldi";
			if(sti(pchar.money) >= 250000)
			{
    			link.l2 = "Sì, l'ho fatto. 250 000 pesos, come concordato.";
    			link.l2.go = "FDM_hull_waitmaterials";
            }
            else
            {
    			link.l1 = "Non ancora, aspetta, maestro.";
    			link.l1.go = "exit";
            }
		break;

		case "FDM_hull_building":
			DialogExit();
			SetLaunchFrameFormParam("Five days passed..."+ NewStr() +"Master Alexus completed the job", "", 0, 5);
			WaitDate("", 0, 0, 5, 0, 10); //Pass time
			LaunchFrameForm();
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			RealShips[sti(Pchar.Ship.Type)].BaseType = SHIP_RENOVATED_FDM;
			RealShips[sti(Pchar.Ship.Type)].Name = "NewFlyingdutchman1";
			RealShips[sti(Pchar.Ship.Type)].BaseName = "NewFlyingdutchman";
			/* RealShips[sti(Pchar.Ship.Type)].CannonsQuantity = 58;
			RealShips[sti(Pchar.Ship.Type)].CannonsQuantityMax = 58;
			RealShips[sti(Pchar.Ship.Type)].CannonsQuantityMin = 58;
			RealShips[sti(Pchar.Ship.Type)].rcannon = 24;
			RealShips[sti(Pchar.Ship.Type)].lcannon = 24;
			RealShips[sti(Pchar.Ship.Type)].fcannon = 6;
			RealShips[sti(Pchar.Ship.Type)].bcannon = 4; */
			if(Get_My_Cabin() == "My_Cabin") RealShips[sti(Pchar.Ship.Type)].CabinType = "Cabin";	
			else RealShips[sti(Pchar.Ship.Type)].CabinType = "Cabin_Huge";
			SetShipSailsFromFile(pchar, "ships/parus_silk.tga");
			SetSailsColor(pchar, 0);//White cotton sail
			RealShips[sti(Pchar.Ship.Type)].HP = GetCharacterShipBaseHP(pchar);
			pchar.ship.hp = GetCharacterShipBaseHP(pchar);
			DeleteAttribute(pchar, "ship.hulls");
			DeleteAttribute(pchar, "ship.blots");	
			CloseQuestHeader("renovate_fdm");
		break;
		//<-- Xenon
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

void checkMatherial_repair(ref Pchar, ref NPChar, int good, int goodType)
{
	int amount;
	string Matherial = "Matherial" + goodType;
	amount = GetSquadronGoods(Pchar, good) - sti(NPChar.Repair.(Matherial));
	
	if (amount < 0)
    {
		amount = amount + sti(NPChar.Repair.(Matherial));
    }
    else
    {
		amount = sti(NPChar.Repair.(Matherial));
    }
    RemoveCharacterGoods(Pchar, good, amount);
    NPChar.Repair.(Matherial) = sti(NPChar.Repair.(Matherial)) - amount;
}

int GetMaterialQtyRepair( ref _chr, int MaterialNum )
{
	if ( sti(_chr.Ship.Type) == SHIP_NOTUSED) return 0;
	
	int   	shipCurHP   = sti(RealShips[sti(_chr.Ship.Type)].HP);
	int   	shipBaseHP	= sti(RealShips[sti(_chr.Ship.Type)].BaseHP);	
	int   	shipClass   = sti(RealShips[sti(_chr.Ship.Type)].Class);
	int     shipWeight  = CWT2Tonnes(sti(RealShips[sti(_chr.Ship.Type)].Weight));
	int     HPPrice     = shipWeight * (1.2 - makefloat(shipCurHP)/makefloat(shipBaseHP));
	int     modifier    = (2 * MOD_SKILL_ENEMY_RATE) + sti(RealShips[sti(_chr.Ship.Type)].MinCrew)/2 + 1;	

	float   fQuest 	= 1.0;
	if(CheckAttribute(&RealShips[sti(_chr.Ship.Type)], "QuestShip")) 
	{
		fQuest  = 1.3;
		HPPrice = HPPrice * 2;
	}					
	
	int     Matherial1 = makeint(fQuest * (10 + MOD_SKILL_ENEMY_RATE) * (7 - shipClass) / 2) + rand(modifier);
	int     Matherial2 = makeint(fQuest * (10 + MOD_SKILL_ENEMY_RATE) * (7 - shipClass) / 2) + rand(modifier);
	int     Matherial3 = makeint(fQuest * (10 + MOD_SKILL_ENEMY_RATE) * (7 - shipClass) / 2) + rand(modifier);
	int     Matherial4 = makeint(fQuest * (10 + MOD_SKILL_ENEMY_RATE) * (7 - shipClass) / 2) + rand(modifier);
		
	if(MaterialNum == 0) return HPPrice;	
	if(MaterialNum == 1) return Matherial1;
	if(MaterialNum == 2) return Matherial2;
	if(MaterialNum == 3) return Matherial3;
	if(MaterialNum == 4) return Matherial4;
	
	return 0;
}

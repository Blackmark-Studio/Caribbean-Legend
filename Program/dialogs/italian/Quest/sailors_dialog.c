// реплики солдат на палубе при разговоре в море
// форт-стража и комендант форта
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
        case "exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
        case "First time":
			dialog.text = "Parla col nostro capitano. Non ho nulla da dirti.";
			Link.l1 = "Va bene.";
			Link.l1.go = "exit";
			
			NextDiag.TempNode = "first time";
		break;
		//  на палубе -->
		case "On_Deck":
			dialog.text = "Parla col nostro capitano. Non ho nulla da dirti.";
			Link.l1 = "D'accordo.";
			Link.l1.go = "exit";

			NextDiag.TempNode = "On_Deck";
/*			
			// Первый церковный генератор
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.CapWaitOnTavern"))
			{
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithSailors"))
				{
					dialog.text = "Signore, cercate qualcuno?";
					Link.l1 = "Sì, compare. Posso vedere il capitano?";
					Link.l1.go = "ChurchQuest1_Node1";
				}
				else
				{
					dialog.text = "Se cerchi il nostro capitano, è appena sbarcato.";
					Link.l1 = "Fine";
					Link.l1.go = "exit";
				}
				break;
			}
*/			
			//--> eddy. квест мэра, закрываем выход с палубы и ноду даем нужную
			if (CheckAttribute(pchar, "GenQuest.DestroyPirate") && pchar.GenQuest.CaptainId == "MQPirate")
			{
	    		dialog.text = RandPhraseSimple("Oh, sei venuto qui da solo. Ah! In tal caso vai dal nostro capitano. Raccontagli delle tue tristi imprese...","Accidenti, sembri proprio fuori di testa, compare. Vai dal nostro capitano, lui saprà che fare con te.");
				Link.l1 = "Peccato...";
				Link.l1.go = "exit";
			}
			//<-- eddy. квест мэра, закрываем выход с палубы
		break;
/*		
		case "ChurchQuest1_Node1":
			dialog.text = "Faresti meglio a cercarlo al porto.";
			Link.l1 = "Grazie, compare.";
			Link.l1.go = "exit";
			NextDiag.TempNode = "On_Deck";
			PChar.GenQuest.ChurchQuest_1.CapWaitOnTavern = true; 
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithSailors"); // Не спрашиваем моряков
		break;
*/		
        //  на палубе <--
				
		// ugeen --> разговор с боцманом по генератору "Повод для спешки"
		case "On_MyShip_Deck":
			dialog.text = "Perdio, che gran casino, capitano! Stavamo nella taverna a tracannare come sempre, quando abbiam sentito delle urla. Siamo corsi fuori e abbiam visto che volevano metterti in ceppi. Al diavolo loro! Così abbiam pensato fosse meglio levare l’ancora da questo porto ostile.";
			link.l1 = "Già, certa gente ha davvero un’idea bizzarra di giustizia.";
			link.l1.go = "On_MyShip_Deck_1";
		break;
		
		case "On_MyShip_Deck_1":
		    if(pchar.questTemp.ReasonToFast == "speakSuccess_chain_A") 
			{
				// карты не было
				dialog.text = "Capitano! Non ti crucciare così! Era chiaro che non si poteva filarsela in santa pace, quindi abbiamo pensato di far visita al banchiere locale per dare un’occhiata ai suoi forzieri. Ecco la tua parte – "+sti(pchar.questTemp.ReasonToFast.p9)+" pesos...";
			}
			if(pchar.questTemp.ReasonToFast == "speakSuccess_chain_B")
			{
				// карту отобрали
				GiveItem2Character(pchar, pchar.questTemp.ReasonToFast.p6);
				dialog.text = "Capitano! Non vi crucciate così! Era chiaro che non ci sarebbe stato modo di scappare in santa pace, così abbiamo pensato di far visita al banchiere del posto e di controllare i suoi scrigni. C’era pure una spada di gran pregio nel baule dei pegni. Ecco la vostra parte – "+sti(pchar.questTemp.ReasonToFast.p9)+" pesos e una spada...";
			}		
			link.l1 = "Ben fatto, ragazzi! Ben fatto! Siete l’orgoglio mio.";
			link.l1.go = "On_MyShip_Deck_End";
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.ReasonToFast.p9));			
			pchar.Ship.Crew.Morale = MORALE_MAX;
			chrDisableReloadToLocation = false; // Откроем выход
			AddQuestRecord("ReasonToFast", "17");		
			AddQuestUserData("ReasonToFast", "sSex", GetSexPhrase("",""));		
			CloseQuestHeader("ReasonToFast");
			DeleteAttribute(pchar,"TownEscape");
			DeleteAttribute(pchar,"questTemp.ReasonToFast");
			QuestOpenSeaExit();
		break;
		
		case "On_MyShip_Deck_End":
			DialogExit();
			AddDialogExitQuest("CanEnterToMap");
		break;
		
		// разговор с боцманом по генератору 'Операция Галеон'
		case "CapComission_OnShipDeck":
			dialog.text = "Capitano, il vostro compare è fuggito.";
			link.l1 = "Che amico?";
			link.l1.go = "CapComission_OnShipDeck1";
		break;
		
		case "CapComission_OnShipDeck1":
			dialog.text = "Ebbene, l’amico che hai tirato fuori dalle segrete.";
			link.l1 = "Come diavolo hai fatto a fartelo sfuggire?!";
			link.l1.go = "CapComission_OnShipDeck2";
		break;
		
		case "CapComission_OnShipDeck2":
			dialog.text = "Non è stata colpa nostra, capitano. Si è lanciato dalla latrina dritto in mare... Abbiamo provato a sparargli, ma lì dentro era buio pesto...";
			link.l1 = "Maledizione! Siete davvero fuori controllo! Vi sbarcherò tutti e vi manderò a sgobbare nelle piantagioni di canna da zucchero! Perdere un pezzo grosso così prezioso! Incredibile!";
			link.l1.go = "CapComission_OnShipDeck3";
		break;
		
		case "CapComission_OnShipDeck3":
			chrDisableReloadToLocation = false; // Откроем выход
			AddQuestRecord("CaptainComission2", "25");	
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));			
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission2");	
			ChangeOfficersLoyality("bad_all", 1);
			ChangeCharacterComplexReputationABS(pchar, "authority", 1);
			DeleteAttribute(pchar,"TownEscape");
			DeleteAttribute(pchar,"GenQuest.CaptainComission.canSpeakBoatswain");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			QuestOpenSeaExit();		
			DialogExit();
			AddDialogExitQuest("CanEnterToMap");
		break;
		// <-- ugeen
		
		// разговор с боцманом по ситуациям в трюме
		case "Hold_GenQuest_OnShipDeck":
			dialog.text = "Capitano, perdonateci, è colpa nostra – il prigioniero è fuggito.";
			link.l1 = "Che prigioniero? Chi è scappato?";
			link.l1.go = "Hold_GenQuest_OnShipDeck1";
		break;
				
		case "Hold_GenQuest_OnShipDeck1":
			dialog.text = "Ebbene, oh, mi sfugge il suo nome, "+pchar.GenQuest.Hold_GenQuest.CapName+", vero?";
			link.l1 = "Maledizione! Dove avevi gli occhi, eh?";
			link.l1.go = "Hold_GenQuest_OnShipDeck2";
		break;
		
		case "Hold_GenQuest_OnShipDeck2":
			dialog.text = "È uscito dalla stiva e si è gettato giù dal parapetto. Non gli abbiamo sparato per evitare rumori e mentre preparavamo la scialuppa, è stato salvato da quegli maledetti pescatori.";
			link.l1 = "E perché ti pago allora! Frusta il capo di guardia e togligli il rum per una settimana. Tutti ai posti! Issiamo l’ancora...";
			link.l1.go = "Hold_GenQuest_OnShipDeck3";
		break;
		
		case "Hold_GenQuest_OnShipDeck3":
			chrDisableReloadToLocation = false; // Откроем выход
			sld = characterFromId(pchar.GenQuest.Hold_GenQuest.CapId);
			ReleasePrisoner(sld);			
			CloseQuestHeader("HoldQuest");	
			DeleteAttribute(pchar, "TownEscape");
			DeleteAttribute(pchar, "GenQuest.Hold_GenQuest.canSpeakSailor");
			DeleteAttribute(pchar, "GenQuest.Hold_GenQuest");
			QuestOpenSeaExit();					
			DialogExit();
			AddDialogExitQuest("CanEnterToMap");
		break;
		
		case "Hold_GenQuest_OnShipDeck4":
			dialog.text = "Saluti, capitano. Non ci sono stati incidenti durante il vostro...";
			link.l1 = "Va bene, va bene, ho capito... C’è il prigioniero nella nostra stiva. Si chiama "+pchar.GenQuest.Hold_GenQuest.CapName+"Prendi alcuni uomini e portalo al porto. Ora è libero.";
			link.l1.go = "Hold_GenQuest_OnShipDeck5";
		break;
		
		case "Hold_GenQuest_OnShipDeck5":
			dialog.text = "È davvero libero? Dobbiamo portarlo via su una scialuppa?";
			link.l1 = "No, su una fottuta tartaruga no... Credevo d’esser stato chiaro. E muoviti, dannazione! Dobbiamo levar l’ancora prima che la marea cali.";
			link.l1.go = "Hold_GenQuest_OnShipDeck3";
		break;
		
		// Warship 09.07.09 Базар с нашим матросом на палубе Мэри Селест -->
		case "On_MaryCeleste_Deck":
			Dialog.text = "Capitano, sulla nave non c’è anima viva! Qui c’è qualcosa che non va... Tommy ha detto d’aver visto un gatto nella cabina di comando, ed era l’unica creatura viva a bordo...";
			Link.l1 = "Idiota, i gatti non hanno un’anima. Pare che non abbia messo piede in chiesa da un secolo, o forse mai. Sei già stato nella cabina del capitano? Mi serve il registro di bordo.";
			Link.l1.go = "On_MaryCeleste_Deck_1";
		break;
		
		case "On_MaryCeleste_Deck_1":
			Dialog.text = "No, hanno un’anima, eccome. Non c’era nessun registro di bordo, né uno strumento da navigazione. Neanche una scialuppa a vista...";
			Link.l1 = "Non lo fanno. È stato forse strappato via da una tempesta?";
			Link.l1.go = "On_MaryCeleste_Deck_2";
		break;
		
		case "On_MaryCeleste_Deck_2":
			Dialog.text = "Sì, capitano. I gatti hanno un’anima. Capitano, la scialuppa è stata tagliata e abbiamo trovato una spada nel pozzetto. È arrugginita e sporca di sangue. Ecco, dia un’occhiata...";
			Link.l1 = "Smettila di rifilarmi questa robaccia, gettala via e piantala di parlare di gatti, maledizione! Diamo un'occhiata alla stiva e andiamocene... Oh, qui c'è qualcosa che puzza davvero e non mi piace affatto, maledetto il diavolo...";
			Link.l1.go = "On_MaryCeleste_Last";
			NextDiag.TempNode = "On_MaryCeleste_Deck_SailorLast";
		break;
		
		case "On_MaryCeleste_Last":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetCitizenType(NPChar); // Чтоб по палубе ходил
			
			NPChar = GetRealShip(GetCharacterShipType(CharacterFromID("MaryCelesteCapitan")));
			NPChar.TurnRate = sti(PChar.QuestTemp.MaryCeleste.TurnRate); // Вернем манёвренность, для интерфейса
			
			chrDisableReloadToLocation = false; // Откроем выход
			
			LaunchTransferMain(PChar, CharacterFromID("MaryCelesteCapitan"), "MaryCelesteTransfer");
		break;
		
		case "On_MaryCeleste_Deck_SailorLast":
			switch(rand(2))
			{
				case 0:
					Dialog.text = "Capitano, ho un brutto presentimento su questo posto... Forse è tempo che ce ne andiamo?";
					Link.l1 = "Sì... Vai alla scialuppa della nave.";
					Link.l1.go = "exit";
				break;
				
				case 1:
					Dialog.text = "Capitano, non resterò su questa nave stramba se volete davvero portarla in porto. Piuttosto mi butto io stesso in mare.";
					Link.l1 = "Non sono disposto a farlo... e, a dire il vero, ho anche un po' di fifa...";
					Link.l1.go = "exit";
				break;
				
				case 2:
					Dialog.text = "Forse dovremmo mandarla a fondo, capitano?";
					Link.l1 = "Per permettere alle anime dei marinai defunti che dimorano qui di venirci a trovare nei nostri incubi?";
					Link.l1.go = "On_MaryCeleste_Deck_SailorLast_1";
				break;
			}
			
			NextDiag.TempNode = "On_MaryCeleste_Deck_SailorLast";
		break;
		
		case "On_MaryCeleste_Deck_SailorLast_1":
			Dialog.text = "Per tutti i santi, no! Capitano... perché dite così?";
			Link.l1 = "Non sbiancare, stavo scherzando... Vai alla scialuppa della nave. E forse hai ragione tu dopotutto, magari i gatti hanno davvero un’anima...";
			Link.l1.go = "exit";
		break;
		// <-- Базар с нашим матросом на палубе Мэри Селест
		
        //  на палубе <--
        case "On_Fort":
			dialog.text = RandPhraseSimple("Parla col capo. Non ho nulla da dirti, furfante.","Sono al mio posto. Tutte le domande vanno rivolte al comandante del forte.");
			Link.l1 = "D’accordo.";
			Link.l1.go = "exit";

			NextDiag.TempNode = "On_Fort";
		break;
		
		case "On_Fort_Head":
			dialog.text = RandPhraseSimple("Ho da fare adesso. Lasciami in pace.","Non farmi perdere tempo con le tue chiacchiere. Non c’è nulla di cui parlare.");
			Link.l1 = "Peccato...";
			Link.l1.go = "exit";

			NextDiag.TempNode = "On_Fort_Head";
		break;
		
		case "Morgan_wait_you":
			Dialog.defAni = "dialog_stay1";
			Dialog.defCam = "1";
			Dialog.defSnd = "dialogs\0\017";
			Dialog.defLinkAni = "dialog_1";
			Dialog.defLinkCam = "1";
			Dialog.defLinkSnd = "dialogs\woman\024";
			Dialog.ani = "dialog_stay2";
			Dialog.cam = "1";
			Dialog.snd = "dialogs\0\009";

			dialog.text = RandPhraseSimple("Morgan voleva dirti 'un paio di cosette'... È da queste parti, sul ponte.","Ehi, cerca Morgan. Ti aspettano brutte notizie...");
			Link.l1 = "Va bene.";
			Link.l1.go = "exit";

			NextDiag.TempNode = "Morgan_wait_you";
		break;
	}
}

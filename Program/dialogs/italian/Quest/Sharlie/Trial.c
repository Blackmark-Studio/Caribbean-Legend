// диалоги НПС по квесту 'Карибские нравы'
void ProcessDialogEvent()
{
	ref NPChar, sld, rColony;
	aref Link, NextDiag;
	int iTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Cosa vuoi, eh?";
			link.l1 = "No, niente.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// Жерар Лекруа
		case "lecrua":
			pchar.quest.Trial_LineOver.over = "yes"; //снять таймер
			dialog.text = "Buon pomeriggio. Dovete essere "+GetFullName(pchar)+"?";
			link.l1 = "Hai ragione, Monsieur LeCroix. Capitano "+GetFullName(pchar)+" al vostro servizio. Fadey il Moscovita mi ha parlato di voi...";
			link.l1.go = "lecrua_1";
			DelLandQuestMark(npchar);
		break;
		
		case "lecrua_1":
			iTemp = FindColony("Baster");
			rColony = GetColonyByIndex(iTemp);
			bOk = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			dialog.text = "Sì, sì. Il mio caro amico Fadey mi ha raccontato tutto di te e della tua situazione con dovizia di particolari. Ho capito subito che eri tu appena ti ho visto sulla soglia. Dimmi, capitano, che tipo di nave comandi?";
			if(sti(pchar.ship.type) == SHIP_NOTUSED || !bOk)
			{
				link.l1 = "Ah... al momento non ho una nave, monsieur...";
				link.l1.go = "lecrua_noship";
			}
			else
			{
				link.l1 = "Ho una "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(RealShips[sti(pchar.ship.type)].basetype),"Name")))+", il suo nome è "+pchar.ship.name+".";
				if (6-sti(RealShips[sti(pchar.ship.type)].Class) < 0) link.l1.go = "lecrua_badship";
				else link.l1.go = "lecrua_2";
			}
		break;
		
		case "lecrua_noship":
			dialog.text = "Ah! E che razza di capitano saresti tu, se nemmeno una nave possiedi? Mi dispiace, monsieur, ma in tal caso non ho nulla da proporti. Buon vento, e saluta Fadey da parte mia!";
			link.l1 = "Hmm...";
			link.l1.go = "lecrua_exit";
			sTotalTemp = "I don't have a ship at the moment";
		break;
		
		case "lecrua_badship":
			dialog.text = "Ebbene, così proprio non va. Quella non è una nave, signore, è una barchetta! Ahimè, monsieur, non siete all’altezza del ruolo. Fate i miei saluti a Fadey, buona giornata!";
			link.l1 = "Uhm...";
			link.l1.go = "lecrua_exit";
			sTotalTemp = "My ship wasn't big enough for him";
		break;
		
		case "lecrua_exit":
			DialogExit();
			npchar.lifeday = 0;
			NextDiag.CurrentNode = "lecrua_repeat";
			AddQuestRecord("Trial", "3");
			AddQuestUserData("Trial", "sText", sTotalTemp);
			CloseQuestHeader("Trial");
			DeleteAttribute(pchar, "questTemp.Trial");
			pchar.questTemp.TrialEnd = true;
		break;
		
		case "lecrua_repeat":
			dialog.text = "Abbiam già detto tutto fra noi, monsieur. Non è vero?";
			link.l1 = "Oui, Monsieur LeCroix... Sto arrivando.";
			link.l1.go = "exit";
			NextDiag.TempNode = "lecrua_repeat";
		break;
		
		case "lecrua_2":
			dialog.text = "Eccellente. In tal caso, sei proprio il tipo che fa al caso mio. Sei pronto a salpare senza indugio?";
			link.l1 = "Sì, monsieur, son pronto. Che devo fare?";
			link.l1.go = "lecrua_3";
		break;
		
		case "lecrua_3":
			sld = characterFromId("BasTer_trader");
			dialog.text = "Devi consegnare una piccola partita di polvere da sparo e bombe a Port-au-Prince, nella parte francese di Hispaniola. Il comandante la aspetta già da tempo, quindi non perdere tempo: ti restano circa dieci giorni\nStimato "+GetFullName(sld)+" si occuperà di consegnarlo e caricarlo sulla vostra nave. Il comandante vi pagherà cinquemila pezzi da otto per il servizio.";
			link.l1 = "E tutto qui il compito?";
			link.l1.go = "lecrua_4";
		break;
		
		case "lecrua_4":
			dialog.text = "Oh, ma neanche per sogno, monsieur. Il comandante le spiegherà il vero incarico quando porterà le munizioni. Questo carico è solo un piccolo antipasto rispetto a ciò che l'aspetta. Ma non tema, se farà un buon lavoro, si riempirà le tasche d'oro.";
			link.l1 = "Hai tutta la mia attenzione, monsieur. La mia nave è pronta a caricare la merce a bordo.";
			link.l1.go = "lecrua_5";
		break;
		
		case "lecrua_5":
			dialog.text = "Non perdiamo tempo allora, capitano! Dirigetevi alla vostra nave e preparatevi a mollare gli ormeggi.";
			link.l1 = "Vado!";
			link.l1.go = "lecrua_6";
		break;
		
		case "lecrua_6":
			DialogExit();
			NextDiag.CurrentNode = "lecrua_repeat";
			AddQuestRecord("Trial", "4");
			pchar.questTemp.Trial = "fraht";
			AddMapQuestMarkCity("PortPax", false);
			// belamour legendary edition халява по чекбоксу
			if(!bImCasual) SetFunctionTimerCondition("Trial_FrahtFail", 0, 0, 17, false); // таймер
			else NewGameTip("Exploration mode: timer is disabled.");
			SetFunctionTimerCondition("Trial_LecruaHide", 0, 0, 1, false); // таймер
			// груз
			SetCharacterGoods(pchar, GOOD_BOMBS, GetCargoGoods(pchar, GOOD_BOMBS)+2500);
			SetCharacterGoods(pchar, GOOD_POWDER, GetCargoGoods(pchar, GOOD_POWDER)+2500);
			// Sinistra Пасхалка с Диего
			pchar.quest.VsD_DiegoNachalo.win_condition.l1 = "Ship_location";
			pchar.quest.VsD_DiegoNachalo.win_condition.l1.location = "PortPax_town";
			PChar.quest.VsD_DiegoNachalo.win_condition = "VsD_DiegoNachalo";
			
			// отключить все враждебные энкаунтеры на глобальной карте
			pchar.worldmapencountersoff = "1";
			SetFunctionTimerCondition("DelNavigatorNoShow", 0, 0, 180, false);
			pchar.systeminfo.tutorial.navigatorTrial = true;
		break;
		
		// Флориан Шоке
		case "florian_deck":
			if(!bImCasual) pchar.quest.Trial_CannonFail.over = "yes"; // belamour legendary edition снять таймер
			DelMapQuestMarkShore("shore47");
			DelLandQuestMark(npchar);
			sld = CharacterFromID("PortRoyal_shipyarder");
			if(CheckAttribute(sld, "TrialDelQuestMark"))
			{
				DeleteAttribute(sld, "TrialDelQuestMark");
				DelLandQuestMark(sld);
				DelMapQuestMarkCity("PortRoyal");
			}
			dialog.text = "In che posso servirvi, signore?";
			link.l1 = "Buon pomeriggio, capitano. Suppongo che siate Florian Shoke, vero?";
			link.l1.go = "florian_deck_1";
		break;
		
		case "florian_deck_1":
			dialog.text = "Sono io. E voi siete la nave postale da Port-au-Prince, se non sbaglio?";
			link.l1 = "Aye, ho quindici cannoni per voi. Per poco non sforavo la scadenza, ci sono arrivato per un pelo...";
			link.l1.go = "florian_deck_2";
		break;
		
		case "florian_deck_2":
			if (GetSquadronGoods(pchar, GOOD_CANNON_24) < 15)
			{
				dialog.text = "Mm. Che strano senso dell’umorismo, signore! Eppure non vedo quindici cannoni sbarcare dalla vostra nave...";
				link.l1 = "Vedi, abbiamo preso una falla e ci toccò gettar parte del carico in mare...";
				link.l1.go = "florian_deck_fail";
			}
			else
			{
				dialog.text = "Felice di vederti, capitano?..";
				link.l1 = ""+GetFullName(pchar)+". Capitano "+GetFullName(pchar)+".";
				link.l1.go = "florian_deck_3";
			}
		break;
		
		case "florian_deck_3":
			dialog.text = "Piacere di conoscerti. Non perdiamo tempo e carichiamo subito questi cannoni a bordo. Non sarà una passeggiata, quindi avrò bisogno che i tuoi uomini mi diano una mano.";
			link.l1 = "Ce la caveremo. Ehi tu, issa il paranco sull’alberetto!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Trial_TakeCannons");
		break;
		
		case "florian_deck_fail":
			dialog.text = "Maledetto imbecille! Se non riesci nemmeno a cavartela con questo compito da nulla, finirai col farti inghiottire dalla prossima tempesta. Torna sulla tua nave, capitano, e dedicati a ciò che ti riesce meglio, tipo portare mazzi di fiori alle dame di corte. Meglio ancora, fai vela verso l’Europa e lascia il Nuovo Mondo agli uomini veri. Buona giornata, messere!";
			link.l1 = "Ma...";
			link.l1.go = "florian_deck_fail_1";
		break;
		
		case "florian_deck_fail_1":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true; 
			RemoveCharacterGoods(pchar, GOOD_CANNON_24, GetCargoGoods(pchar, GOOD_CANNON_24));
			SetFunctionTimerCondition("Trial_RemoveFlorian", 0, 0, 1, false);
			sld = characterFromId("Lecrua");
			sld.lifeday = 0;
			AddQuestRecord("Trial", "10");
			CloseQuestHeader("Trial");
			DeleteAttribute(pchar, "questTemp.Trial");
			pchar.questTemp.TrialEnd = true;
			ChangeCharacterNationReputation(pchar, FRANCE, -3);
		break;
		
		case "florian_deck_4":
			dialog.text = "Uff, che fatica da assetati! Ti ringrazio per il servizio, capitano! Prendi la tua ricompensa, duecento dobloni.";
			link.l1 = "Grazie mille!";
			link.l1.go = "florian_deck_5";
		break;
		
		case "florian_deck_5":
			TakeNItems(pchar, "gold_dublon", 200);
			Log_Info("You've received 200 doubloons.");
			PlaySound("interface\important_item.wav");
			dialog.text = "Ma non è tutto, capitano. Che ne direste di guadagnare altri duecentocinquanta doppi escudos d’oro?";
			link.l1 = "Suona promettente, ma dipende da che diavolo volete che faccia per voi, signore.";
			link.l1.go = "florian_deck_6";
		break;
		
		case "florian_deck_6":
			dialog.text = "Non ti nasconderò la verità, è rischioso. Come forse già sai, sto tendendo un’imboscata a un pesante galeone spagnolo carico di preziosi. La nave è ai cantieri per riparazioni. Secondo le mie fonti, doveva salpare ieri, ma non s’è mossa.\nInoltre, il mio informatore a Portobello non s’è fatto vivo al punto d’incontro per consegnarmi le notizie che aspetto. Temo che gli spagnoli l’abbiano pizzicato. Ti pago se riesci a sgattaiolare a Portobello e scoprire due cose: perché il galeone è ancora fermo e che fine ha fatto il mio uomo. Ci stai?";
			link.l1 = "Temo di non avere l’addestramento adatto per simili imprese. Son un gentiluomo, non una spia. Rischierei d’infilarmi nei guai io stesso e non potrei esservi d’aiuto.";
			link.l1.go = "florian_deck_bye";
			link.l2 = "Sembra rischioso, ma anche redditizio. Accetto la scommessa. Come si chiama il tuo uomo, e come si chiama il galeone?";
			link.l2.go = "florian_deck_7";
		break;
		
		case "florian_deck_bye":
			dialog.text = "Ah, che presuntuoso sei! Ti capisco. Addio allora, capitano, e grazie ancora per il tuo aiuto!";
			link.l1 = "Tutto il meglio, Monsieur Shoke.";
			link.l1.go = "florian_deck_bye_1";
		break;
		
		case "florian_deck_bye_1":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true; 
			SetFunctionTimerCondition("Trial_RemoveFlorian", 0, 0, 1, false);
			sld = characterFromId("Lecrua");
			sld.lifeday = 0;
			AddQuestRecord("Trial", "11");
			CloseQuestHeader("Trial");
			DeleteAttribute(pchar, "questTemp.Trial");
			pchar.questTemp.TrialEnd = true;
		break;
		
		case "florian_deck_7":
			dialog.text = "Ascolta bene, allora. Il mio uomo si chiama Sylvan Laforet, ma a Portobello lo conoscono come Jaime Silicio, un mercante. Il galeone si chiama 'Alacantara'. Ti consiglio di passare le porte della città di notte, attraversando la giungla. Le guardie di Portobello sono sospettose di questi tempi, e la sparizione di Sylvan non promette niente di buono sulla sua sorte. Hai due giorni prima che io debba filarmela, prima che le pattuglie spagnole ci scoprano. Buona fortuna, monsieur!";
			link.l1 = "A presto, Monsieur Shoke...";
			link.l1.go = "florian_deck_8";
		break;
		
		case "florian_deck_8":
			bQuestDisableMapEnter = true;//закрыть карту
			pchar.GenQuest.MapClosedNoBattle = true; // доступно ожидание и sailto
			DialogExit();
			npchar.DeckDialogNode = "florian_deck_repeat";
			NextDiag.CurrentNode = "florian_deck_repeat";
			pchar.questTemp.Trial = "spy";
			AddQuestRecord("Trial", "12");
			// belamour legendary edition -->
			if(!bImCasual) 
			{
				pchar.quest.trial_spy_over.win_condition.l1 = "Timer";
				pchar.quest.trial_spy_over.win_condition.l1.date.hour  = sti(GetTime() + 2);
				pchar.quest.trial_spy_over.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 2);
				pchar.quest.trial_spy_over.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
				pchar.quest.trial_spy_over.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 2);
				pchar.quest.trial_spy_over.function = "Trial_SpyTimeOver";
			}
			else NewGameTip("Exploration mode: timer is disabled.");
			// <-- legendary edition
			//Log_Info("You have received amulet 'Gypsy's fan'");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "obereg_4");
			pchar.quest.NewGameTip5.win_condition.l1 = "location";
			pchar.quest.NewGameTip5.win_condition.l1.location = "PortoBello_town";
			pchar.quest.NewGameTip5.function = "ShowNewGameTip";
			pchar.quest.NewGameTip5.text = "Guards are less suspicious when you walk at slow pace!";
			
			pchar.quest.Trial_CreatHabitue.win_condition.l1 = "location";
			pchar.quest.Trial_CreatHabitue.win_condition.l1.location = "PortoBello_tavern";
			pchar.quest.Trial_CreatHabitue.function = "Trial_CreatHabitue";
			
			pchar.quest.Tutorial_stealth.win_condition.l1 = "location";
			pchar.quest.Tutorial_stealth.win_condition.l1.location = "PortoBello_ExitTown";
			pchar.quest.Tutorial_stealth.function = "Tutorial_stealth";
			
			QuestPointerToLoc("shore47", "reload", "reload1_back");
			QuestPointerToLoc("PortoBello_Jungle_02", "reload", "reload1_back");
			QuestPointerToLoc("PortoBello_Jungle_01", "reload", "reload3_back");
			QuestPointerToLoc("PortoBello_ExitTown", "reload", "reload4");
			QuestPointerToLoc("PortoBello_Town", "reload", "reload41_back");
			QuestPointerToLoc("PortoBello_Town", "reload", "reload4_back");
		break;
		
		case "florian_deck_repeat":
			dialog.text = "Abbiamo discusso tutto, capitano, non è vero?";
			link.l1 = "Sì. Sto arrivando.";
			link.l1.go = "exit";
			NextDiag.TempNode = "florian_deck_repeat";
		break;
		
		case "florian_failspy":
			pchar.quest.trial_spy_over.over = "yes"; //снять прерывание
			dialog.text = "Come vanno le cose, capitano? Che siete riuscito a scoprire?";
			link.l1 = "Le cose vanno male, Monsieur Shoke. Non sono un gran ficcanaso, mi hanno sgamato in quattro e quattr’otto. Ho dovuto filarmela dalla città dopo una scaramuccia con le guardie. L’unica cosa che sono riuscito a scoprire è che il vostro Sylvan Laforet è stato preso e marcisce in galera.";
			link.l1.go = "florian_failspy_1";
		break;
		
		case "florian_failspy_1":
			dialog.text = "Maledizione! Non va affatto bene... Hai scoperto qualcosa sul galeone?";
			link.l1 = "No, non l'ho fatto.";
			link.l1.go = "florian_failspy_2";
		break;
		
		case "florian_failspy_2":
			dialog.text = "Maledizione. Mi serve proprio qualche informazione su questa faccenda. Ma questa preda è troppo grossa per lasciarla andare! Vabbè, proverò a mandare un altro segugio da quelle parti... Capitano, ti chiedo di non abbandonarmi per ora. Potrei aver bisogno del tuo aiuto. Mi aspetterai ancora un giorno, mentre fiuto qualche notizia sull’Alacantara?";
			link.l1 = "Certo, aspetterò! Vorrei riscattarmi per quel fallimento.";
			link.l1.go = "florian_9";
			link.l2 = "Non credo proprio. Pare che sia una frana in questi giochi. Me ne torno a casa.";
			link.l2.go = "florian_failspy_3";
		break;
		
		case "florian_failspy_3":
			dialog.text = "Ebbene, è una tua scelta. Buon vento, capitano.";
			link.l1 = "Addio, Monsieur Shoke.";
			link.l1.go = "florian_failspy_4";
		break;
		
		case "florian_failspy_4":
			DialogExit();
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true; 
			SetFunctionTimerCondition("Trial_RemoveFlorian", 0, 0, 1, false);
			sld = characterFromId("Lecrua");
			sld.lifeday = 0;
			CloseQuestHeader("Trial");
			DeleteAttribute(pchar, "questTemp.Trial");
			pchar.questTemp.TrialEnd = true;
		break;
		
		case "florian_failspy_5":
			pchar.quest.trial_spy_over.over = "yes"; //снять прерывание
			dialog.text = "Come procedono le cose, capitano? Che siete riuscito a scoprire?";
			link.l1 = "Le cose vanno male, Monsieur Shoke. Come spia valgo poco, mi hanno sgamato in un batter d’occhio. Tutto ciò che sono riuscito a scoprire è che il vostro uomo, Sylvan Laforet, è stato arrestato e ora marcisce da qualche parte.";
			link.l1.go = "florian_failspy_1";
		break;
		
		case "florian_9":
			dialog.text = "Allora vai pure alla tua nave, capitano. Domani, più o meno alla stessa ora, o poco dopo, dovrai venire a trovarmi. Forse per allora avrò scoperto qualcosa. Non mettere piede a terra, aspettami a bordo della tua nave!";
			link.l1 = "D'accordo. Lo farò.";
			link.l1.go = "florian_10";
		break;
		
		case "florian_10":
			dialog.text = "E capitano, prenda questa borsa. I vostri sforzi non sono stati del tutto vani, dopotutto. Almeno ora sappiamo che fine ha fatto il povero vecchio Sylvan...";
			link.l1 = "...";
			link.l1.go = "florian_11";
		break;
		
		case "florian_11":
			DialogExit();
			Island_SetReloadEnableGlobal("Portobello", false);//закрыть остров	
			npchar.DeckDialogNode = "florian_deck_wait";
			NextDiag.CurrentNode = "florian_deck_wait";
			pchar.questTemp.Trial = "spy_wait";
			pchar.quest.Trial_spyfail_wait.win_condition.l1 = "Timer";
			pchar.quest.Trial_spyfail_wait.win_condition.l1.date.hour  = sti(GetTime()+rand(12));
			pchar.quest.Trial_spyfail_wait.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Trial_spyfail_wait.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Trial_spyfail_wait.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Trial_spyfail_wait.function = "Trial_Spyfail_NextStage";
			TakeNItems(pchar, "purse2", 1);
			Log_Info("You've received a purse of doubloons");
		break;
		
		case "florian_deck_wait":
			dialog.text = "Capitano, al momento non ci sono novità. Siamo ancora in attesa...";
			link.l1 = "D’accordo...";
			link.l1.go = "exit";
			NextDiag.TempNode = "florian_deck_wait";
		break;
		
		case "florian_12":
			pchar.quest.trial_spy_over.over = "yes"; //снять прерывание
			dialog.text = "Come vanno le cose, capitano? Che sei riuscito a scoprire?";
			link.l1 = "Fatto. Il tuo uomo, Sylvan Laforet, è stato arrestato e marcisce ora nelle segrete. Per lui è finita.";
			link.l1.go = "florian_13";
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("PortoBello_Town", "reload", "gate_back");
			QuestPointerDelLoc("PortoBello_ExitTown", "reload", "reload1_back");
			QuestPointerDelLoc("PortoBello_Jungle_01", "reload", "reload2_back");
			QuestPointerDelLoc("PortoBello_Jungle_02", "reload", "reload3_back");
			QuestPointerDelLoc("shore47", "reload", "boat");
		break;
		
		case "florian_13":
			dialog.text = "Maledizione! Che disgrazia... Hai scoperto qualcosa sul galeone?";
			link.l1 = "Sì. È già un po’ che la stanno preparando per salpare, ma il governatore di Portobello vuole tenerla ferma al molo. Sta aspettando una barchessa chiamata 'Puebla' che deve arrivare da Cartagena con una partita di polvere da sparo per l’‘Alcantara’. Secondo un marinaio del galeone, non ne hanno abbastanza e il governatore teme i pirati.";
			link.l1.go = "florian_14";
		break;
		
		case "florian_14":
			dialog.text = "Che curiosità!";
			link.l1 = "Ma se Puebla non arriva entro tre giorni, l’Alacantara smetterà di aspettare e salperà.";
			link.l1.go = "florian_15";
		break;
		
		case "florian_15":
			dialog.text = "Eccellente lavoro, Capitano "+GetFullName(pchar)+"! Sono davvero lieto! Ecco, prendi la tua ricompensa. Te la sei guadagnata tutta!";
			link.l1 = "Grazie! Avete forse qualche altro incarico per me?";
			link.l1.go = "florian_16";
		break;
		
		case "florian_16":
			TakeNItems(pchar, "gold_dublon", 250);
			Log_Info("You've received 250 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Mi leggi proprio nel pensiero, "+GetFullName(pchar)+"Sì, maledizione! Dal momento che l’Alacantara è a corto di polvere da sparo, posso lasciarla andare al largo e poi costringerla a una lunga battaglia navale, dove finiranno la polvere prima di noi, ahah!\nDevi assicurarti che la polacca di rifornimento Puebla non raggiunga mai Portobello. Io non posso avvicinarmi troppo alla costa, le pattuglie noterebbero subito la mia fregata e mi caccerebbero via prima che possa intercettare l’Alacantara.\nPuebla è affar tuo. Trovala e sbarazzatene. Affondala o prendila come bottino, poco mi importa. Basta che non arrivi mai qui!\nSe ci riesci, vai in Guadalupa da Gérard LeCroix, credo che tu lo conosca già, vero? Lui ti darà il compenso che meriti.";
			link.l1 = "Affare fatto! Vado subito a tagliare la rotta per Puebla!";
			link.l1.go = "florian_19";
			link.l2 = "Aspetti un attimo, Monsieur Choquet. Il fatto è che sono ancora... Diciamo, non proprio avvezzo ai combattimenti navali. E voi siete capitano di una fregata, di certo di battaglie ne avete viste più d’una. Se non vi pesa, potreste... Come dire...";
			link.l2.go = "florian_guide_01";
		break;
		
		case "florian_17":
			dialog.text = "Felice che tu sia arrivato, capitano. Ho appena ricevuto notizie dalla mia spia e ho una missione importante da affidarti.";
			link.l1 = "Sono tutto orecchi.";
			link.l1.go = "florian_18";
		break;
		
		case "florian_18":
			dialog.text = "L'Alacantara è pronta a salpare, ma il capitano del galeone aspetta che la barkentina 'Puebla' arrivi da Cartagena carica di munizioni. Pare che all'Alacantara manchi la polvere da sparo, dunque gli spagnoli non sono ancora pronti a mollare gli ormeggi. Ma la pazienza del capitano ha un limite: se la Puebla non arriva entro tre giorni, il galeone lascerà Portobello senza di lei.\nL'Alacantara ha scarsa polvere da sparo; potrei lasciarla prendere il largo e poi costringerla a un lungo scontro navale, così finiranno le scorte prima di noi. Il tuo compito è intercettare la Puebla e distruggerla. Affondala o prendila come bottino, poco mi importa. Basta che questa maledetta barkentina non arrivi a destinazione!\nSe ci riesci, vai a Guadalupa da Gérard LeCroix. Credo che già lo conosci, vero? Ti pagherà la ricompensa che ti sei guadagnato.";
			link.l1 = "Affare fatto! Mi metto subito in rotta per tagliare la strada a Puebla!";
			link.l1.go = "florian_19";
			link.l2 = "Aspetti un momento, Monsieur Choquet. Il fatto è che io sono ancora... Diciamo che non sono proprio avvezzo alle battaglie navali. Lei invece è capitano di una fregata, sicuramente ha già visto più di uno scontro in mare. Se non le pesa, potrebbe... come dire...";
			link.l2.go = "florian_guide_01";
		break;
		
		case "florian_19":
			DialogExit();
			Island_SetReloadEnableGlobal("Portobello", true); // открыть остров
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true; 
			SetFunctionTimerCondition("Trial_RemoveFlorian", 0, 0, 1, false);
			Trial_CreatePueblaBarqueInWorld();
			pchar.questTemp.Trial = "puebla";
			AddQuestRecord("Trial", "19");
		break;
		// belamour legendary edition дополнительное обучение -->
		case "florian_guide_01":
			dialog.text = "Vorresti che ti dia una lezione sulle tattiche del combattimento navale? Con piacere, capitano! Tanto più che mi conviene: voglio essere certo che riuscirai ad intercettare la 'Puebla'.";
			link.l1 = "No, non intendevo questo. Va bene, lascia perdere: sono certo che non avrò alcun problema a intercettare una barquentina.";
			link.l1.go = "florian_19";
			link.l2 = "Sì, proprio questo intendevo. Son certo che un po’ di sapere in più non mi farà male.";
			link.l2.go = "florian_guide_02";
		break;
		
		case "florian_guide_02":
			dialog.text = "Dunque, la prima cosa da ricordare è che metà della battaglia si vince o si perde ancora до того, как она начнётся. Molto dipende da quanto tu e la tua nave siete pronti.";
			link.l1 = "...";
			link.l1.go = "florian_guide_03";
		break;
		
		case "florian_guide_03":
			dialog.text = "Prima di tutto, accertati che la tua nave sia ben riparata. Se hai falle nello scafo, non ci vorrà molto perché il nemico ti mandi a fondo. E se al posto delle vele ti ritrovi solo degli stracci penzolanti, la tua manovrabilità andrà a farsi benedire. Il nemico potrà seminarti con facilità se la sorte gli è avversa, oppure peggio, raggiungerti e costringerti a un combattimento che non ti conviene — o magari abbordarti sul colpo. Inoltre, con le vele a brandelli, sarà dura guadagnare il sopravvento e metterti sopravento al tuo avversario, proprio dove vorresti essere.";
			link.l1 = "Vantaggio del vento, chiaro. Qualcos'altro?";
			link.l1.go = "florian_guide_04";
		break;
		
		case "florian_guide_04":
			dialog.text = "Assicurati di avere abbastanza uomini. Anche la nave più potente, armata di cannoni da 42 libbre, diventa un barcone inutile se c'è un solo artigliere che corre a ricaricare tre pezzi e nessuno a manovrare le vele. In tal caso, io mi limiterei a salire subito a bordo e prenderla senza fatica.";
			link.l1 = "Basta uomini, capito.";
			link.l1.go = "florian_guide_05";
		break;
		
		case "florian_guide_05":
			dialog.text = "Inoltre, tieni d’occhio i tuoi cannoni: col tempo si consumano e finiscono per scoppiare. Le canne si logorano pian piano, e se ti esplode un pezzo durante una battaglia, può finire davvero male, credimi. A me è andata proprio storta: la partita di cannoni con cui sono salpato aveva un mucchio di difetti di fusione. Se non mi avessi portato i pezzi di ricambio a tempo debito, avrei mollato tutto all’inferno: la Militant non avrebbe mai potuto reggere il confronto con l’Alcantara quanto a potenza di fuoco. Gli attrezzi vanno cambiati quando è ora.";
			link.l1 = "Ora capisco perché era così importante!";
			link.l1.go = "florian_guide_06";
		break;
		
		case "florian_guide_06":
			dialog.text = "Oltre ai cannoni, tieni d’occhio anche la quantità di munizioni. L’Alcantara cadrà per questo motivo. Se avrà scorte scarse di polvere da sparo, non potrà reggere una battaglia lunga — dovrà subito buttarsi nella mischia. E qui giocherò la mia carta: la mia fregata è più veloce, un galeone pesante non potrà seminarmi. Ma nemmeno io devo avvicinarmi troppo: la costringerò a un duello d’artiglieria da lontano, e poi, quando la polvere sull’Alcantara sarà finita, mi avvicinerò, la falcerò con una scarica di mitraglia e salterò a bordo.";
			link.l1 = "Situazione disperata...";
			link.l1.go = "florian_guide_07";
		break;
		
		case "florian_guide_07":
			dialog.text = "Esatto. Tieni d’occhio la polvere da sparo e le munizioni. Se finisci i proiettili pieni – difficilmente riuscirai ad affondare una nave nemica. Se ti mancano le mitraglie, scordati l’abbordaggio se siete in minoranza. Senza palle a catena o knipples, non raggiungerai mai il nemico, né potrai seminarlo se va più veloce di te. Ogni tipo di munizione è fondamentale.";
			link.l1 = "Istruttivo, grazie.";
			link.l1.go = "florian_guide_08";
		break;
		
		case "florian_guide_08":
			dialog.text = "E infine, a seconda del tipo e della stazza della tua nave e di quella del nemico, adotta la tattica più adatta. In mare, c’è sempre un compromesso tra potenza di fuoco e velocità. Se navighi su un vascello grosso e lento, non ha alcun senso inseguire una brigantina o una corvetta per abbordarla: non la raggiungerai mai senza prima averla sfiancata a colpi di mitraglia. In questi casi, conviene sbriciolarla da lontano e poi frugare tra i relitti. Se proprio vuoi abbordare una nave simile, meglio farlo con una barca veloce e manovrabile.";
			link.l1 = "...";
			link.l1.go = "florian_guide_09";
		break;
		
		case "florian_guide_09":
			dialog.text = "Allo stesso tempo, non ti mettere mai a duello con una nave di linea usando una brigantina. Una sola bordata di quella bestia ridurrà lo scafo delle più piccole in schegge. Sfrutta la tua velocità e agilità: abbattene gli alberi e le manovre, poi avvicinati e spazza i ponti con la mitraglia, se ancora vuoi abbordare. Se invece vuoi mandarla a picco... non sarà impresa facile, ma non è impossibile. Puoi salire a bordo e incendiare la santabarbara, ma non c’è vergogna nella fuga. Un bravo capitano sa salvare nave e ciurma invece di cercare gloria in un’impresa suicida. Ricorda, la discrezione e la prudenza sono spesso le migliori armi di un marinaio valoroso.";
			link.l1 = "Grazie mille, Monsieur Choquet!";
			link.l1.go = "florian_guide_10";
		break;
		
		case "florian_guide_10":
			AddCharacterSkillDontClearExp(pchar, SKILL_CANNONS, 1);
			AddCharacterSkillDontClearExp(pchar, SKILL_ACCURACY, 1);
			//Log_info(XI_ConvertString("Experience Bonus")+": +1 "+XI_ConvertString(SKILL_CANNONS));
			notification(XI_ConvertString("Experience Bonus")+": +1 ", SKILL_CANNONS);
			//Log_info(XI_ConvertString("Experience Bonus")+": +1 "+XI_ConvertString(SKILL_ACCURACY));
			notification(XI_ConvertString("Experience Bonus")+": +1 ",SKILL_ACCURACY);
			dialog.text = "Felice di aiutarti, capitano. Spero che questa dritta ti torni utile in futuro.";
			link.l1 = "Sono certo che sarà d’aiuto. Salpiamo per intercettare la ‘Puebla!’";
			link.l1.go = "florian_19";
		break;
		// <-- legendary edition дополнительное обучение

		// испанский офицер в таверне
		case "tavern_officer":
			dialog.text = "Hai un accento proprio curioso, señor. O forse dovrei dire 'monsieur'? Vuoi vedere Jaime Silicio? Magari vi fate compagnia nello stesso buco. Prendetelo, ragazzi!";
			link.l1 = "Se il mio accento ti dà fastidio, posso sempre presentarti la scherma francese!";
			link.l1.go = "tavern_officer_1";
		break;
		
		case "tavern_officer_1":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorTypeNoGroup(npchar);
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
            LAi_group_SetCheck("EnemyFight", "Trial_AfterTavernFight");
			AddDialogExitQuest("MainHeroFightModeOn");
			SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}

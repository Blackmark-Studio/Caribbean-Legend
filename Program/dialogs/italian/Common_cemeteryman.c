// Jason общий диалог смотрителей кладбищ
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;	

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Cemetery\" + NPChar.City + "_cemetery.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	
    int iTemp;
	string sTemp;
	bool ok;
    
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase("La città è in allerta. Sembra che sia il momento anche per me di prendere le armi...","Non stai forse venendo inseguito da tutte le guardie della città? A me, soldati!!!","Non troverai rifugio qui. Ma troverai qualche centimetro di freddo acciaio sotto una costola!"),LinkRandPhrase("Cosa vuoi, mascalzone?! Una guardia municipale ha già preso le tue tracce, non scapperai troppo lontano, "+GetSexPhrase("sporco pirata!","birbante")+"!","Fermati! "+GetSexPhrase("Assassino sporco! Guardia!!!","Non ho paura di te! Presto sarai impiccato nel nostro forte, non c'è posto dove nasconderti...")));
				link.l1 = PCharRepPhrase(RandPhraseSimple("Sembra che tu sia stanco di vivere...","E perché non volete vivere tranquillamente, cittadini..."+XI_ConvertString("Colony"+npchar.city+"Gen")+"!"),RandPhraseSimple("Vai all'inferno!","Ti restano solo pochi secondi in questo mondo..."));
				link.l1.go = PCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			if(!CheckAttribute(pchar, "questTemp.Lantern"))
			{
				dialog.text = "A-a-ah! Ah, sei tu... Chi sei? Perché sei venuto al cimitero?";
				link.l1 = "Il mio nome è "+GetFullName(pchar)+". E chi sei tu e cosa stai facendo qui? E perché hai così paura?";
				link.l1.go = "Lantern_01";
				npchar.quest.meeting = "1";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Lantern") && pchar.questTemp.Lantern == "ToCrypt")
			{
				dialog.text = "Allora, com'è andata? Hai controllato? Mi credi ora?";
				link.l1 = "No, non sono ancora sceso nella cripta. Aspetta un po' più a lungo, controllerò tutto.";
				link.l1.go = "exit";
				break;
			}
			
			if(CheckAttribute(pchar, "questTemp.Lantern") && pchar.questTemp.Lantern == "ToKeeper")
			{
				dialog.text = "Allora? Hai dato un'occhiata? L'hai visto?";
				link.l1 = "Sì, certo che l'ho fatto! Avevi ragione!";
				link.l1.go = "Lantern_10";
				link.l2 = "Non era proprio quello che pensavi.";
				link.l2.go = "Lantern_14";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = RandPhraseSimple("Ciao, marinaio! Il mio nome è "+GetFullName(npchar)+", e sono l'unica anima viva qui. In realtà, moriremo tutti, ah-ah-ah! Perché sei venuto?","Ciao! Non ho visto un uomo in vita da molto tempo... Permettimi di presentarmi - "+GetFullName(npchar)+", e questo cimitero è il mio ultimo rifugio. A quanto pare, sarò sepolto qui. Come posso aiutarti?");
				link.l1 = "Ciao, "+npchar.name+"! Il mio nome è "+GetFullName(pchar)+", e sono un capitano. Ho attraversato la giungla e sono arrivato qui. Pensavo di dare un'occhiata dentro questa confortevole casa, per vedere chi non ha paura di vivere qui...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, il mio vecchio amico, capitano "+GetFullName(pchar)+"! Entra, entra!";
				link.l1 = "Benvenuto, amico! Sono molto contento di vederti. Non vedi scheletri danzanti di notte e morti con monete di rame sugli occhi nei tuoi sogni?";
				link.l1.go = "talk";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "E perché dovrei aver paura, capitano? È necessario temere i vivi, i morti non mordono. Eh! Una volta avevo una vita del tutto diversa, e ora sono il custode di questo cimitero. Mi prendo cura delle tombe. E ogni tanto commercio anche con qualche oggetto strano...";
			link.l1 = "E quali articoli commerci, dimmi, per favore?";
			link.l1.go = "trade_info";
		break;
		
		case "talk":
			dialog.text = "Cosa ti ha portato da me questa volta?";
			link.l1 = "Mostrami cosa hai in vendita oggi.";
			link.l1.go = "trade";
			link.l2 = "Voglio farti una domanda...";
			link.l2.go = "quests";
			link.l3 = "Niente di serio. Sono semplicemente venuto a salutarti.";
			link.l3.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "trade_info":
			dialog.text = "Ho molto tempo libero, quindi mi piace camminare nella giungla per raccogliere piante utili e pietre preziose. Poi li vendo in città. Non costano molto, ma - è meglio di niente. E ricevo una varietà di cose dai miei amici...";
			link.l1 = "Amici? Vuoi dire, rivendi ciò che altri ti portano?";
			link.l1.go = "trade_info_1";
		break;
		
		case "trade_info_1":
			dialog.text = "O-ho-ho... No, mi danno tutto gratuitamente. Chi può essere amico di un guardiano di cimitero, se non i morti?";
			link.l1 = "Cosa... Rubi i cadaveri?";
			link.l1.go = "trade_info_2";
		break;
		
		case "trade_info_2":
			dialog.text = "I don't rob; I just take things off those who don't need them anymore. Many different people are buried here-some unknown and not from our lands. The commandant brings a dead body from the town and says: 'This is for you, "+npchar.name+", send him on his final journey.' Homeless, hanged pirates, bandits killed by guardians-all are buried here. And old "+npchar.name+" buries their bodies on a Christian custom.";
			link.l1 = "Capisco. Beh, i soldi sono soldi, mostrami cosa hai.";
			link.l1.go = "trade";
			link.l2 = "Capito. Devo andare. Sono stato felice di incontrarti.";
			link.l2.go = "exit";
		break;
		
		case "trade":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
			NextDiag.TempNode = "First time";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Man_FackYou"://реакция на попытку залезть в сундук
			dialog.text = LinkRandPhrase("E tu, "+GetFullName(pchar)+", sei un ladro! Guardie!!!","Cosa diamine! Mi sono distratto un attimo e già stai cercando di rubare ciò che è mio! Fermate quel ladro!!!","Guardia! Rapina!!! Afferra il ladro!!!");
			link.l1 = "Cazzo!!!";
			link.l1.go = "fight";
		break;
		//belamour квест на получение фонаря -->
		case "Lantern_01":
			dialog.text = "Uff, quindi sei solo un viaggiatore... Il mio nome è "+GetFullName(npchar)+", sono il custode di questo dannato posto.";
			link.l1 = "Perché provi quel sentimento verso il cimitero? Al contrario, è da qui che il nostro Signore prende i giusti dopo la sepoltura.";
			link.l1.go = "Lantern_02";
		break;
		
		case "Lantern_02":
			dialog.text = "Ma gli ingiusti, a quanto pare, rimangono qui dopo la sepoltura! Per le ultime due notti, è venuto qualche rumore dalla cripta. E i lamenti sono così agghiaccianti che mi danno i brividi... Sembra che un'anima perduta non riesca a trovare pace! Ora dormo solo durante il giorno - di notte, non posso lasciare il mio posto o chiudere gli occhi...";
			link.l1 = "Rumori? Lamenti? Ma lì non c'è nessuno tranne i defunti.";
			link.l1.go = "Lantern_03";
		break;
		
		case "Lantern_03":
			dialog.text = "Ecco quello che sto dicendo, capisci? Faresti meglio a sparire da qui prima che il fantasma ti avverta... Altrimenti, non riuscirai a dormire, proprio come me.";
			link.l1 = "Mh, sì, penso che farei meglio a lasciare questo posto.";
			link.l1.go = "Lantern_04";
			link.l2 = "Forse posso aiutarti? Permettimi di indagare su quei rumori strani stasera.";
			link.l2.go = "Lantern_05";
		break;
		
		case "Lantern_04":
			pchar.questTemp.Lantern = "NoLantern";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Lantern_05":
			dialog.text = "Sei fuori di testa?! Vedo che hai un'arma, ma come pensi di combattere i non morti con essa? E se finisci per tirare le cuoia lì, cosa succederà? Lo spirito vagherà libero, e potrebbe anche risvegliarti come suo servitore!";
			link.l1 = "Beh, è solo superstizione...";
			link.l1.go = "Lantern_06";
		break;
		
		case "Lantern_06":
			dialog.text = "Che superstizione? Questa non è la pia terra d'Europa, maledizione... I nativi, quei volti dal viso rosso, possono evocare qualsiasi cosa - e adesso dobbiamo vivere qui!";
			link.l1 = "Tuttavia, lascia che ci provi. Aspetterò fino al tramonto e poi scenderò nella cripta.";
			link.l1.go = "Lantern_07";
		break;
		
		case "Lantern_07":
			dialog.text = "Bene, fai come vuoi. Ma se non torni entro l'alba, chiuderò tutto a chiave, lo barricaderò e me ne andrò da solo! Che si tratti di strofinare il ponte come un marinaio o di trasportare scatole come un operaio del porto, non tornerò comunque qui!";
			link.l1 = "Solo calmati... Tutto andrà bene.";
			link.l1.go = "Lantern_08";
		break;
		
		case "Lantern_08":
			dialog.text = "Aspetta... Prendi questa lanterna. Ne ho una di riserva. Ne avrai bisogno là. È buio pesto!";
			link.l1 = "Grazie, una lanterna sarà davvero utile in un posto del genere.";
			link.l1.go = "Lantern_09";
		break;
		
		case "Lantern_09":
			GiveItem2Character(pchar, "lantern_belt");
			Log_Info("'Lantern' received");
			PlaySound("interface\important_item.wav");
			if(npchar.city == "Charles") SetFunctionLocationCondition("NoiseCemetery_toCrypt", "Charles_CryptBig2", true);
			if(npchar.city == "Havana") SetFunctionLocationCondition("NoiseCemetery_toCrypt", "Havana_CryptBig2", true);
			if(npchar.city == "Villemstad" || npchar.city == "PortRoyal") SetFunctionLocationCondition("NoiseCemetery_toCrypt", "Common_CryptBig2", true);
			pchar.quest.NoiseCemetery_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NoiseCemetery_SeaExit.function = "NoiseCemetery_SeaExit";
			pchar.questTemp.Lantern = "ToCrypt";
			pchar.questTemp.Lantern.nation = npchar.nation;
			AddQuestRecord("NoiseCemetery", "1");
			AddQuestUserData("NoiseCemetery", "sCity", XI_ConvertString(loadedlocation.islandId)); 
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Lantern_10":
			dialog.text = "Giusto? Cosa c'era lì? Dimmi!";
			link.l1 = "C'era lo spirito irrequieto di una donna! Fortunatamente, ho fatto benedire la mia lama dal prete del posto per colpire i malvagi, quindi tutto è andato per il meglio. Quello spirito non ti darà più fastidio.";
			link.l1.go = "Lantern_11";
		break;
		
		case "Lantern_11":
			dialog.text = "Oh Signore, salva le nostre anime peccaminose! Vi avevo avvertito! E voi non mi avete creduto!";
			link.l1 = "Sì, e me ne pento sinceramente. Ma ora tutto è a posto - ho cosparso questo luogo con acqua santa, e nessuno spirito oserà risorgere dalla tomba. Puoi dormire tranquillo.";
			link.l1.go = "Lantern_12";
		break;
		
		case "Lantern_12":
			dialog.text = "Grazie mille! Non hai idea di cosa significhi per me! Ecco, per favore prendi questo. Non è molto, ma non posso lasciarti andare senza una ricompensa.";
			link.l1 = "Grazie, non posso rifiutare. Buona fortuna a te!";
			link.l1.go = "Lantern_13";
		break;
		
		case "Lantern_13":
			pchar.quest.NoiseCemetery_SeaExit.over = "yes";
			AddMoneyToCharacter(PChar, 1000);
			pchar.questTemp.Lantern = "Done";
			AddQuestRecord("NoiseCemetery", "3");
			CloseQuestHeader("NoiseCemetery");
			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Lantern_14":
			dialog.text = "No? Allora che diavolo... voglio dire, che cosa nel nome di Dio, è successo lì?";
			link.l1 = "Non c'era affatto un fantasma. Una giovane coppia ha scelto questa cripta come luogo per i loro appuntamenti. I loro genitori sono contro questa unione, quindi cercavano un posto dove stare da soli.";
			link.l1.go = "Lantern_15";
		break;
		
		case "Lantern_15":
			dialog.text = "Da solo?.. Perché quei giovani! Lasciali solo provare a venire qui di nuovo! Li caccio entrambi via con una frusta o li rinchiudo nella cripta così restano là!!!";
			link.l1 = "Non torneranno più qui. Ho detto loro che le loro piccole scappatelle hanno veramente spaventato la guardia locale. Intendevano farlo. E a proposito, la serratura sulla porta è comunque rotta.";
			link.l1.go = "Lantern_16";
		break;
		
		case "Lantern_16":
			dialog.text = "Nessun problema, lo sostituirò. Ma se mai li prendo...";
			link.l1 = "Non arrabbiarti così tanto. Siamo stati tutti a quell'età. Non sono venuti qui perché questo era il miglior posto per incontri.";
			link.l1.go = "Lantern_17";
		break;
		
		case "Lantern_17":
			dialog.text = "Giusto... Vabbè, che il Signore stia con loro. Grazie per non aver abbandonato un vecchio in difficoltà. Ecco, per favore prendi questo. Non è molto, ma non posso lasciarti andare senza una ricompensa.";
			link.l1 = "Grazie, non posso rifiutare. Buona fortuna a te!";
			link.l1.go = "Lantern_18";
		break;
		
		case "Lantern_18":
			DialogExit();
			pchar.quest.NoiseCemetery_SeaExit.over = "yes";
			AddMoneyToCharacter(PChar, 1000);
			pchar.questTemp.Lantern = "Done";
			AddQuestRecord("NoiseCemetery", "4");
			CloseQuestHeader("NoiseCemetery");
			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		// <-- квест на получение фонаря 
	}
}

// Джон Мердок, он же Йохан ван Мерден, соратник Роденбурга
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;
	int iTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
		if (!CheckAttribute(pchar, "questTemp.HWIC.Self") && LAi_grp_playeralarm > 0)
		{
			dialog.text = "Monsieur, avete scelto proprio un brutto momento per le chiacchiere. Tutta la guarnigione vi sta dando la caccia. Vi conviene filarvela alla svelta...";
			link.l1 = "Non preoccuparti. Non mi fermerò a lungo.";
			link.l1.go = "exit";
			break;
		}
		// продажа алхимического набора, если провалил гамбит
		if (CheckAttribute(pchar, "questTemp.HWIC.Detector") && !CheckAttribute(npchar, "quest.alchemy"))
		{
			bOk = (findsubstr(pchar.questTemp.HWIC.Detector, "_fail" , 0) != -1) || (pchar.questTemp.HWIC.Detector == "eng_win_half");
			if (bOk)
			{
				dialog.text = "Benvenuto, capitano. Avreste voglia d’ascoltare una proposta intrigante? ";
				link.l1 = "Pare che qui tutti abbiano qualche proposta da rifilare, e io sono un tipo curioso. Di che si tratta? ";
				link.l1.go = "alchemy";
				break;
			}
		}
		// Страж Истины
		if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok1")
		{
			dialog.text = "Buongiorno. Benvenuto nella mia bottega d'apotecario. Ho rimedi per ogni sorta di malanno e debolezza. Cosa posso offrirti?";
			link.l1 = "Ascolta, John, si mormora che qualcuno viva al tuo posto, al secondo piano...";
			link.l1.go = "guardoftruth";
			break;
		}
//-----------------------------------------за Голландию------------------------------------------------
		if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
		{
			if (pchar.location.from_sea == "SentJons_town" && pchar.questTemp.HWIC.Holl == "toAntigua")
			{
				dialog.text = "Buongiorno. Son lieto di vedervi nella mia bottega di rimedi. Ho medicamenti per curare quasi ogni malanno e debolezza. Che posso offrirvi?";
				link.l1 = "Salve, signor Murdock. Sono qui per conto di Lucas Rodenburg. Mi ha mandato da lei per discutere una faccenda riguardante Richard Fleetwood.";
				link.l1.go = "Knippel_exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "toAntigua")
			{
				dialog.text = "Buon pomeriggio. Che grana ti affligge? Ho sia sciroppo per la tosse che polvere per la diarrea!";
				link.l1 = "Salve, signor Murdock. Sono qui per conto di Lucas Rodenburg. Mi ha mandato da voi per discutere una questione riguardante Richard Fleetwood.";
				link.l1.go = "Knippel";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "KillMerdok")
			{
				dialog.text = "Ahhh, ecco il cane assoldato da Rodenburg... Hercule, Longway – volete uscire, per cortesia?\nFate fuori quest’uomo!";
				link.l1 = "Aspetta, ho una prescrizione!";
				link.l1.go = "Merdok_fight";
				break;
			}
			dialog.text = "Buon pomeriggio. Son lieto di vedervi nella mia bottega di rimedi. Ho pozioni e medicamenti per ogni malanno e debolezza. Che cosa posso offrirvi?";
			link.l1 = "Niente al momento, grazie. Mi sento proprio in forma.";
			link.l1.go = "exit";
			break;
		}
//----------------------------------------------за Англию---------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "MerdokMeeteng")
			{
			dialog.text = "Salute, ospite non invitato. Non porti maschera sul volto e non hai l’aria del masnadiero. Deduco dunque che cerchi altro dal povero speziale. Forse un rimedio per il cagotto?";
			link.l1 = "Anche a te, salve, Johan van Merden. Ti porto i saluti di Hercule Tonzag. Vedo che questo nome non ti è nuovo.";
			link.l1.go = "Merdok_talk";
			DelLandQuestMark(npchar);
			break;
			}
//--------------------------------------------против всех--------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				if (pchar.questTemp.HWIC.Self == "HuntFleetwood")
				{
					dialog.text = "Ah, quindi eccoti qui. Allora, hai già fatto la conoscenza di Hercule? ";
					link.l1 = "Sì. Abbiamo raggiunto un accordo. John, aiuterò Hercule, e ho parecchie domande da farti riguardo Richard Fleetwood.";
					link.l1.go = "About_Fleetwood";
					break;
				}
				if (GetQuestPastDayParam("questTemp.Wait_Fleetwood") > 6 && pchar.questTemp.HWIC.Self == "WaitFleetwood")
				{
					dialog.text = "Salute! Mi fa piacere vederti, "+pchar.name+"!";
					link.l1 = "Ciao, John. Hai scoperto qualcosa su Fleetwood?";
					link.l1.go = "About_Fleetwood_9";
					pchar.quest.Wait_FleetwoodOver.over = "yes"; //снять таймер
					break;
				}
				if (pchar.questTemp.HWIC.Self == "HWICSelf_fail")
				{
					dialog.text = "Sei in ritardo. L’uccello è già volato via. Charlie Knippel è passato da Willemstad e ha portato una ragazza per Richard. Ora salpano per l’Inghilterra con tutta una squadra militare, tra un giorno o due. Fleetwood se n’è andato, non lo rivedrai più su questa terra.";
					link.l1 = "Maledizione. Mi sono completamente scordato di Richard e ho perso la cognizione del tempo. A presto.";
					link.l1.go = "About_Fleetwood_17";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileOnShip")
				{
					dialog.text = "Bentornato, "+pchar.name+" !   Nulla per te al momento. Nessuna novità su Fleetwood, e Charlie Knippel non è ancora tornato da Curaçao...";
					link.l1 = "E mai lo farà. Né lui, né la sua brigantina.";
					link.l1.go = "Abigile";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileInHouse")
				{
					dialog.text = "Ah, abbiamo ospiti! Salute, Charlie! Buon pomeriggio, signorina!";
					link.l1 = "Buon pomeriggio, John! Permettimi di presentarti la mia compagna, la fidanzata di Richard, l’incantevole Abigail Shneur.";
					link.l1.go = "Abigile_7_1";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileInRoom")
				{
					dialog.text = "Parla piano... Cosa intendi fare adesso?";
					link.l1 = "Avanti? Preferirei farmi una dormita, ma purtroppo non c’è tempo per simili piaceri. Andrò a stanare Fleetwood dalla sua tana e finirò il lavoro lasciato da Hercule.";
					link.l1.go = "Abigile_9";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "LetterToFleetwood")
				{
					dialog.text = "Hai finito di scrivere? Fammi dare un'occhiata... Santo cielo, Charlie, sei proprio un pazzo scatenato! Non pensi d'esserti lasciato prendere un po' troppo dal dettaglio? Voglio dire, tutta quella roba sulle dita, le orecchie e la faccia di Miss Shneur? Hai un talento maledettamente contorto, su questo non si discute. Maledizione, sto quasi per vomitare!";
					link.l1 = "Sto solo bluffando, John. Non ammazzerò la ragazza. Potrei farle lasciare un dito... Ma nulla di più. In fondo, gliene restano ancora nove.";
					link.l1.go = "Abigile_15";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "FleetwoodAgree")
				{
					dialog.text = "È andata bene? Lo vedo nei tuoi occhi – ce l’hai fatta!";
					link.l1 = "Sì. Fleetwood ha accettato le mie condizioni. La trappola si sta chiudendo. Ora non ci resta che attendere.";
					link.l1.go = "Abigile_23";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "FleetwoodDied")
				{
					dialog.text = "Ah, bentornato, amico mio! Che novità mi porti?";
					link.l1 = "Fleetwood è morto. Tutto è andato secondo i piani. È sbarcato sull’isola, dove avevo teso un’imboscata sulla spiaggia. Si è battuto come un demonio, ma non gli è servito a nulla. Solo uno di noi ha lasciato quella spiaggia con le gambe proprie.";
					link.l1.go = "Abigile_27";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "MeetTonzag")
				{
					dialog.text = "D’accordo "+pchar.name+", ho una proposta seria per te. Quello di cui sto per parlarti è affare assai rischioso, ma visto come ti sei sbarazzato di Fleetwood, sono certo che saprai cavartela. Hai un... talento raro nel risolver grane difficili.";
					link.l1 = "Sono lusingato. Continua pure a parlare.";
					link.l1.go = "Lucas";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SeekAbiIsland")
				{
					DelLandQuestMark(npchar);
					DelMapQuestMarkCity("SentJons");
					dialog.text = "Bentornato, "+pchar.name+"! Buone nuove per me, eh?";
					link.l1 = "Giovanni, d’ora in poi puoi dormire senza il pugnale sotto il cuscino. Lucas non rappresenta più un pericolo per te. Sta in ceppi, sotto chiave, e presto verrà spedito in Olanda, dove lo aspetta un processo per ribellione, tentato omicidio e altri misfatti.";
					link.l1.go = "Lucas_10";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "VanbergDestroyed")
				{
					DelLandQuestMark(npchar);
					DelMapQuestMarkCity("SentJons");
					dialog.text = "Felice di vederti, "+pchar.name+"! Sei vivo – e questa è già una gran fortuna. Novità dal fronte?";
					link.l1 = "Sì. Van Berg è sparito per sempre. Proprio come avevi previsto, mi ha rintracciato e mi ha aggredito nel momento meno opportuno. Era un osso duro, Van Berg, ma alla fine l'ho fatto fuori.";
					link.l1.go = "Final";
					break;
				}
			dialog.text = "Ti serve altro?";
			link.l1 = "No, John, niente. Me ne vado.";
			link.l1.go = "exit";
			break;
			}
			dialog.text = "Buon pomeriggio. Son lieto di vedervi nella mia bottega d’unguenti. Ho rimedi per la maggior parte dei mali e delle debolezze. Cosa posso offrirvi?";
			link.l1 = "Niente al momento, grazie. Mi sento piuttosto bene.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

//--------------------------------------------за Голландию-----------------------------------------------------
		case "Knippel_exit":
			dialog.text = "Non capisco affatto di cosa parli, signore. Quale Lucas Rodenburg? Non ho alcun affare con gli olandesi. Devi avermi scambiato per qualcun altro.";
			link.l1 = "Cosa? Mynheer Rodenburg mi ha mandato da voi!";
			link.l1.go = "Knippel_exit_1";
		break;
		
		case "Knippel_exit_1":
			dialog.text = "Lasciate che ve lo ripeta un'ultima volta – non conosco nessun Mynheer Rodenburg. Quanto agli olandesi, non ci ho nulla a che spartire. Ci sono solo due cose che non sopporto al mondo: chi non tollera le culture altrui, e gli olandesi. Quindi, se non avete bisogno di un rimedio, vi prego, lasciatemi al mio lavoro.";
			link.l1 = "Più strano di così si muore...";
			link.l1.go = "exit";
		break;

		case "Knippel":
			dialog.text = "Ebbene, ebbene... Sei mandato dal signor Rodenburg? D'accordo. Ti presto ascolto.";
			link.l1 = "Devo organizzare un incontro con il Capitano Fleetwood in un luogo appartato. Ho preso in prestito la 'Miraggio' da Jacob van Berg, quel corsaro olandese che il signor Fleetwood tanto desidera catturare. Vorrei informarlo che la 'Miraggio' lancerà l’ancora al largo di Dominica molto presto, proprio a portata di mano.";
			link.l1.go = "Knippel_1";
		break;
		
		case "Knippel_1":
			dialog.text = "Jacob ti ha dato la sua nave? Eh, quindi ora hai bisogno di qualcuno che vada a dirlo al signor Fleetwood che la 'Mirage' sarà presto al largo di Dominica, visto che tu stesso non puoi informare Richard per certe ragioni...";
			link.l1 = "Esatto. Mynheer Rodenburg m'ha raccomandato di rivolgermi a voi per questa faccenda.";
			link.l1.go = "Knippel_2";
		break;
		
		case "Knippel_2":
			dialog.text = "In tal caso, Charlie Knippel è l’uomo che ti serve. Fedele compare di Fleetwood... e la sua spia. Parlaci, e sussurragli tutto ciò che vuoi che Richard sappia. Fa’ attenzione però, Knippel può sembrare un sempliciotto, ma non è uno stupido.\nLo trovi in una capanna poco distante dalla riva. Dovrebbe essere là.";
			link.l1 = "Capisco. Grazie, signor Murdock. Addio!";
			link.l1.go = "Knippel_3";
		break;
		
		case "Knippel_3":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "toKnippel";
			AddQuestRecord("Holl_Gambit", "1-16");
			AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
		break;
		
		case "Merdok_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			sld = characterFromId("Tonzag");
			PlaySound("Voice\English\hambit\Ercule Tongzag-04.wav");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			//а вот и китаец нарисовался
			sld = characterFromId("Longway");
			LAi_SetWarriorType(sld);
			FantomMakeCoolFighter(sld, 18, 40, 40, "blade_08", "pistol1", "bullet", 70);
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.LongwayEnemy"))//враг
			{
				ChangeCharacterAddressGroup(sld, "SentJons_TownCave", "monsters", "monster8");
				LAi_group_MoveCharacter(sld, "EnemyFight");
				PlaySound("Voice\English\hambit\Longway-02.wav");
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.LongwayFriend"))//друг
			{
				LAi_warrior_DialogEnable(sld, true);
				sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
				sld.dialog.currentnode = "Longway_hire";
				ChangeCharacterAddressGroup(sld, "SentJons_TownCave", "monsters", "monster8");
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				PlaySound("Voice\English\hambit\Longway-02.wav");
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.LongwayNeutral")) sld.lifeday = 0;//нейтрал - просто нет
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "Merdok_AfterBattle");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
//-------------------------------------------------за Англию-----------------------------------------------------
		case "Merdok_talk":
			dialog.text = "Davvero? Credevo che quel povero Gaston stesse già bruciando all’inferno da un bel pezzo.";
			link.l1 = "Può darsi, ma uno come Gaston non c’è al mondo. Ho trovato la sua testa nel tesoro d’un vecchio ebreo su un’isola segreta. Eppure è riuscito a mandarti i suoi saluti. Ha anche detto che abbiamo un nemico in comune: monsieur Rodenburg. Tonzag ha detto che forse hai delle carte importanti per Lucas che potrebbero stanarlo dal suo buco a Curaçao.";
			link.l1.go = "Merdok_talk_1";			
		break;
		
		case "Merdok_talk_1":
			dialog.text = "Aveva ragione. È proprio il mio archivio che toglie il sonno a Rodenburg. Pare che se ne stia ancora tra noi solo per colpa sua. La verità è che gli avevano promesso un bel posto nel Comitato dei Direttori della Compagnia nelle Province Unite. Ma se le informazioni contenute in quell’archivio — e lì dentro c’è parecchia roba succosa sul passato e sul presente di Lucas — dovessero venir fuori, le sue ambizioni andrebbero a fondo come un relitto. A quel punto, la sua unica speranza sarebbe di perdere la testa col colpo della scure invece che col cappio.";
			link.l1 = "Dammi l’archivio, e penserò io al nostro nemico.";
			link.l1.go = "Merdok_talk_2";			
		break;
		
		case "Merdok_talk_2":
			dialog.text = "Devi prendermi per uno sciocco. Sono ancora vivo solo perché ce l’ho ancora con me. Come posso sapere che ora non lavori per Lucas?";
			link.l1 = "Dovrai fidarti della mia parola... oppure crepare.";
			link.l1.go = "Merdok_talk_3";			
		break;
		
		case "Merdok_talk_3":
			PlaySound("Voice\English\hambit\John Mardock-07.wav");
			dialog.text = "Risposta sbagliata, morirai qui e adesso! Longway, gongji!";
			link.l1 = "Oh oh, il cinese spunta dalle ombre! Niente paura, vi farò a pezzi come un pollo in casseruola!";
			link.l1.go = "Merdok_fightEng";			
		break;
		
		case "Merdok_fightEng":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");	
			sld = characterFromId("Longway");
			FantomMakeCoolFighter(sld, 20, 50, 50, "blade_08", "pistol1", "bullet", 80);
			LAi_SetWarriorType(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_TownCave", "monsters", "monster8");
			PlaySound("Voice\English\hambit\Longway-02.wav");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "Merdok_AfterBattleEng");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
//----------------------------------------против всех-------------------------------------------------------
		case "MC_InHouse":
			PlaySound("Voice\English\hambit\John Mardock-02.wav");
			dialog.text = "Finalmente ti sei rimesso in piedi. Temevo che non ti saresti più svegliato.";
			link.l1 = "Che...? Chi diavolo sei? Dove diamine mi trovo? Come ci sono finito?";
			link.l1.go = "MC_InHouse_1";	
		break;
		
		case "MC_InHouse_1":
			dialog.text = "Calmati, non fare mille domande tutte insieme, non ti fa bene agitarti così. Il mio nome è John Murdock, sono speziale qui a Saint John's. Hai perso i sensi durante una rissa con la marmaglia di Fleetwood. Devo dire che ti hanno conciato per le feste... È stato Hercule a trascinarti qui nella mia bottega, e insomma, ti ho rimesso in sesto con le mie pozioni e rimedi.";
			link.l1 = "Hercule? Chi? L’uomo che m’ha dato una mano per strada? ";
			link.l1.go = "MC_InHouse_2";			
		break;
		
		case "MC_InHouse_2":
			dialog.text = "Sì. Proprio lui. A proposito, vorrebbe parlarti. Devi incontrarlo in città. Ce la fai ancora a camminare? Bene. Esci di notte – usa il passaggio segreto che parte dietro la porta al piano terra di casa mia. Non farti vedere prima che cali il buio – gli uomini di Fleetwood ti stanno cercando.";
			link.l1 = "Aye... Dov'è la mia nave?";
			link.l1.go = "MC_InHouse_3";			
		break;
		
		case "MC_InHouse_3":
			if (pchar.Ship.Type == SHIP_NOTUSED)
			{
				dialog.text = "La tua nave è stata sequestrata e il tuo equipaggio si è disperso per paura di finire sgozzato dagli uomini di Fleetwood. Mi duole dirlo.";
				link.l1 = "Merda...";
			}
			else
			{
				dialog.text = "È in porto, al suo solito posto.";
				link.l1 = "Fiù... buona notizia. Pensavo d’averla persa.";
			}
			link.l1.go = "MC_InHouse_4";			
		break;
		
		case "MC_InHouse_4":
			dialog.text = "Dovresti incontrare Hercule. Vai in città di notte passando dal tunnel segreto. Sarà lui a venirti incontro. Ora riposati un po', io devo tornare ai miei affari.";
			link.l1 = "D'accordo, John. E... ti ringrazio per l’aiuto e per avermi rimesso in sesto!";
			link.l1.go = "MC_InHouse_5";
		break;
		
		case "MC_InHouse_5":
			NextDiag.CurrentNode = "First time";
			DialogExit();
			npchar.greeting = "merdok_2";
			AddQuestRecord("Holl_Gambit", "3-12");
			pchar.questTemp.HWIC.Self = "MainBegin";//новый флаг квеста
			sld = characterFromId("Bridgetown_tavernkeeper");
			sld.model = "barmen_3";
			sld.greeting = "barmen_1";
			sld.name = "Harry";
			sld.lastname = "Fletcher";//перерисуем бармена Бриджтауна
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload1", true);//закрыть выход из аптеки через дверь
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload2", false);//открыть подземелье из дома
			LocatorReloadEnterDisable("SentJons_TownCave", "reload1_back", false);//открыть дом из подземелья
			pchar.quest.Tonzag_Meeting.win_condition.l1 = "location";
			pchar.quest.Tonzag_Meeting.win_condition.l1.location = "SentJons_town";
			pchar.quest.Tonzag_Meeting.win_condition.l2 = "Night";
			pchar.quest.Tonzag_Meeting.function = "TonzagMeeting";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "SentJons_HouseF3", "goto", "goto1", "MC_TakeCloves", -1);	
		break;
		
		case "About_Fleetwood":
			DelLandQuestMark(npchar);
			dialog.text = "Fleetwood?   Che vuoi sapere su di lui?";
			link.l1 = "Tutto. Raccontami tutto quello che sai. Mi pare che tu sappia bene perché Hercule sia venuto ad Antigua. Io sono dalla sua parte.";
			link.l1.go = "About_Fleetwood_1";
		break;
		
		case "About_Fleetwood_1":
			dialog.text = "Benissimo. Capitano Richard Fleetwood della Reale—ehm, volevo dire della Marina del Commonwealth... maledizione, continuo a scordare che quel fanatico di Cromwell comanda ora e ha cambiato il nome. Comunque, Fleetwood è un buon combattente e un vecchio lupo di mare. Comanda una brigantina chiamata 'Valkyrie'—una nave eccellente, se posso permettermi, con un equipaggio di marinai e fucilieri scelti. Porta avanti una guerra personale contro le Province Unite in generale e contro la Compagnia Olandese delle Indie Occidentali in particolare. Ha depredato innumerevoli mercantili olandesi e fatto schizzare alle stelle il costo delle assicurazioni. Il governatore di Curaçao ha messo sulla sua testa una taglia da record.";
			link.l1 = "Hmm... Pare un tantino insolito che un ufficiale della 'Marina del Commonwealth' si dia alla pirateria...";
			link.l1.go = "About_Fleetwood_2";
		break;
		
		case "About_Fleetwood_2":
			dialog.text = "Sì, proprio così. Sta camminando su un filo sottile. Gli inglesi ufficialmente non riconoscono le sue azioni e si rifiutano di averci a che fare, ma in realtà lo incoraggiano di nascosto. Ho motivo di credere che sia in qualche modo legato alla rete di spie inglesi nei Caraibi, e con quei mascalzoni non si scherza affatto.";
			link.l1 = "Un tipo serio... Tutto qui? Hercule mi parlava sempre di un suo aiutante... un altro Charlie... come si chiamava... Barilotto? Palla di cannone?";
			link.l1.go = "About_Fleetwood_3";
		break;
		
		case "About_Fleetwood_3":
			dialog.text = "Knippel? Sì, c’è proprio un tale. Charlie Knippel era capocannoniere della Marina inglese, ora è in pensione. Vive tranquillo sulla costa. È occhi e orecchie di Fleetwood a St. John's, quindi vedi di non лезть к нему и не пытаться расспрашивать о Ричарде — finirai ai ferri o, peggio, col collo in una corda.";
			link.l1 = "Capisco. Puoi dirmi altro di rilevante su Fleetwood?";
			link.l1.go = "About_Fleetwood_4";
		break;
		
		case "About_Fleetwood_4":
			dialog.text = "Un idolo per tutte le donne di Antigua, dalle fanciulle alle vecchie megeras. Pare che tutto, di fatto, в этом. Beh, credo che tu sappia cosa gli è successo adesso. Sta a letto a leccarsi le ferite.";
			link.l1 = "Deve pur avere qualche vizio o punto debole...";
			link.l1.go = "About_Fleetwood_5";
		break;
		
		case "About_Fleetwood_5":
			dialog.text = "Cosa vuoi dire?";
			link.l1 = "Beh, forse gli piace giocare d’azzardo, alza un po’ troppo il gomito o non sa resistere alle gonne – roba del genere. È sposato?";
			link.l1.go = "About_Fleetwood_6";
		break;
		
		case "About_Fleetwood_6":
			dialog.text = "No, uno scapolo. Quanto alle cose che hai detto – nessuno lo conosce per simili faccende.";
			link.l1 = "Capisco. Ma forse c’è comunque qualcosa di particolare in lui? Persino un tipo simile deve pur avere qualche tallone d’Achille!";
			link.l1.go = "About_Fleetwood_7";
		break;
		
		case "About_Fleetwood_7":
			dialog.text = "Non lo so. Ascolta, facciamo così: torna da me fra una settimana e avrò scavato nella vita privata di Fleetwood. D'accordo?";
			link.l1 = "Affare fatto. Grazie, John! Sarò qui fra una settimana.";
			link.l1.go = "About_Fleetwood_8";
		break;
		
		case "About_Fleetwood_8":
			DialogExit();
			pchar.questTemp.HWIC.Self = "WaitFleetwood";
			SaveCurrentQuestDateParam("questTemp.Wait_Fleetwood");
			SetFunctionTimerCondition("Wait_FleetwoodQM", 0, 0, 7, false);
			SetFunctionTimerCondition("Wait_FleetwoodOver", 0, 0, 12, false);//чтобы не опаздывал
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload1", false);//открыть выход из аптеки
			AddQuestRecord("Holl_Gambit", "3-14");
		break;
		
		case "About_Fleetwood_9":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("SentJons");
			dialog.text = "Sì, ma purtroppo non molto. E temo che comunque non serva a un gran che.";
			link.l1 = "Sputa il rospo! Ogni più piccolo dettaglio conta, se c’entra Fleetwood.";
			link.l1.go = "About_Fleetwood_10";
		break;
		
		case "About_Fleetwood_10":
			dialog.text = "Non molto tempo fa Richard raccolse due rifugiati ebrei da un’isola sconosciuta – un vecchio e sua figlia, in viaggio verso Willemstad. La nave su cui viaggiavano fu mandata a fondo da pirati. Fleetwood li portò di nascosto a Curaçao, rischiando la pelle. Da allora sono passati alcuni mesi. Ora ha spedito il suo fido mastino Charlie Knippel a Willemstad...";
			link.l1 = "Hmm... Come sono collegati?";
			link.l1.go = "About_Fleetwood_11";
		break;
		
		case "About_Fleetwood_11":
			dialog.text = "Son riuscito a scoprire che Charlie ha ricevuto l’ordine di portare qui una ragazza da Willemstad, una giudea di nome Abigail Shneur. Sì, proprio quella ragazza dell’isola. Pare che Richard abbia perso la testa per lei, se manda il suo migliore agente a prenderla.\nTutto qui. Non so se ti servirà a qualcosa.";
			link.l1 = "Oh ho ho! Hahaha! Pare che il nostro impenitente scapolo sia caduto nelle astuzie della giudea! Ottimo lavoro, John, grazie! Ora, quando partirà il nostro amico Knippel per Curaçao?";
			link.l1.go = "About_Fleetwood_12";
		break;
		
		case "About_Fleetwood_12":
			dialog.text = "È partito ieri.";
			link.l1 = "E su quale nave?";
			link.l1.go = "About_Fleetwood_13";
		break;
		
		case "About_Fleetwood_13":
			dialog.text = "Sapevo che l’avresti chiesto. È su una brigantina battente bandiera del Commonwealth—oh, al diavolo, della ‘Royal Navy’. Si chiama ‘Zeekalf’.";
			link.l1 = "'Zeekalf'? È un nome olandese bello tosto per una nave inglese... ahhh, ora ci arrivo.";
			link.l1.go = "About_Fleetwood_14";
		break;
		
		case "About_Fleetwood_14":
			dialog.text = "Hai la mente svelta... Il suo vecchio nome era 'Royal Mary', ma per questo viaggio si chiama 'Zeekalf'. E batte bandiera olandese.";
			link.l1 = "Il tuo aiuto è stato preziosissimo, John. Ora parto. Tornerò presto e avrò bisogno della stanza al secondo piano dove mi hai ospitato mentre mi rimettevo.";
			link.l1.go = "About_Fleetwood_15";
		break;
		
		case "About_Fleetwood_15":
			dialog.text = "Che stai tramando?";
			link.l1 = "Ti racconterò tutto al mio ritorno. Augurami fortuna, John! Addio.";
			link.l1.go = "About_Fleetwood_16";
		break;
		
		case "About_Fleetwood_16":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-16");
			pchar.questTemp.HWIC.Self = "HuntKnippel";
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("HuntKnippelOver", 0, 0, 10, false);
			pchar.quest.Hunt_Knippel.win_condition.l1 = "location";
			pchar.quest.Hunt_Knippel.win_condition.l1.location = "Curacao";
			pchar.quest.Hunt_Knippel.function = "CreateKnippelShip";
			LocatorReloadEnterDisable("SentJons_town", "houseH1", true);//закрыть хижину Чарли
			AddMapQuestMarkIsland("Curacao", true);
		break;
		
		case "About_Fleetwood_17":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-15");
			pchar.questTemp.HWIC.Self = "end";
			pchar.questTemp.HWIC.Detector = "self_fail";
			CloseQuestHeader("Holl_Gambit");
		break;
		
		case "Abigile":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("SentJons");
			dialog.text = "Davvero? E perché ne sei così sicuro?";
			link.l1 = "Perché Charlie ora riposa sul fondo del mare a dar da mangiare ai pesci. Ho arrembato la 'Zeekalf' e spedito Knippel dritto all’inferno. Ovviamente, prima l’ho interrogato... Addosso gli ho trovato una lettera che mi ha permesso di spacciarmi per Knippel quando ho parlato con la nostra ebrea Abigail, la dolce metà del nostro valoroso Richard.";
			link.l1.go = "Abigile_1";
		break;
		
		case "Abigile_1":
			dialog.text = "Hmm... Furbo, davvero. Quindi, vuoi dire che...";
			link.l1 = "Sì. Ho portato la giudea ad Antigua. È a bordo della mia nave. Ora ho un asso nella manica nella mia partita con Fleetwood! Per lei, farà qualsiasi cosa...";
			link.l1.go = "Abigile_2";
		break;
		
		case "Abigile_2":
			dialog.text = "Ne sei proprio certo? Potrebbe darsi che la faccenda non sia così semplice come vuoi far credere...";
			link.l1 = "Oh sì, ne sono assolutamente certo. Dalla lettera ho capito che il padre di Abigail era contrario al matrimonio con Richard per via dei soldi. Lo so, il solito suocero ebreo tirchio. Così Fleetwood ha deciso di pagare al padre una dote – 200.000 pesos! Dimmi tu, quante ragazze al mondo valgono tanto?";
			link.l1.go = "Abigile_3";
		break;
		
		case "Abigile_3":
			dialog.text = "Heh! Di certo non una giudea! Non ho mai incontrato cristiana che valga tanto, questo è poco ma sicuro. "+pchar.name+", sei un furfante astuto. Che ne farai di lei?";
			link.l1 = "Porterò qui la giudea e la terremo nella tua stanza. Le dirò che Richard è salpato e non è ancora tornato, così sarà nostra ospite per una settimana. Lei crede che io sia Charlie Knippel.";
			link.l1.go = "Abigile_4";
		break;
		
		case "Abigile_4":
			dialog.text = "Che storia intrigante. Hai deciso di tenere la ragazza a casa mia? Hmm...";
			link.l1 = "John, è una giudea. Una randagia senza patria venuta da una colonia olandese. Qui a St. John's non è nessuno e nessuno la conosce. Sta' tranquillo, possiamo farne quel che vogliamo, non fiaterà. Non ha un soldo né un cane che la saluti. E comunque, non resterà nostra ospite a lungo. Con lei attirerò Fleetwood come un pesce all’amo, poi non ci servirà più.";
			link.l1.go = "Abigile_5";
		break;
		
		case "Abigile_5":
			dialog.text = "Cominci a farmi paura, Charles. Non vorrai approfittarti di questa ragazza, vero? O farle fare la stessa fine di Knippel?";
			link.l1 = "No, certo che no. ‘Canaglia astuta’ forse sì, ma nemico delle belle fanciulle – ebree o cristiane – non lo sono affatto. Né delle brutte, a dirla tutta. Se si comporta come si deve, la riporterò dal padre a Willemstad quando finirà tutto questo. Quel vecchio avaro probabilmente mi cadrà ai piedi, ringraziandomi per averla salvata da quell’infido inglese.";
			link.l1.go = "Abigile_6";
			// belamour legendary edition -->
			link.l2 = "Ha una parte in questa farsa. Quando la recita sarà finita, non avrò più bisogno di lei.";
			link.l2.go = "Abigile_6a";
		break;
		
		case "Abigile_6a":
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "Sneak", 60);
			dialog.text = "Capisco, quindi per ora devo occuparmi di lei.";
			link.l1 = "Non insisterò, compare. Se sei proprio contrario, può restare sulla mia nave. Ma allora dovrò incatenarla per sicurezza e rinchiuderla nella stiva coi topi, così che la mia ciurma non le metta le mani addosso. Avere donne a bordo è una rarità per loro, sai. Sarebbe un vero peccato trattare così una fanciulla tanto graziosa.";
			link.l1.go = "Abigile_7";
		break;
		
		case "Abigile_6":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 60);
			// <-- legendary edition
			dialog.text = "Capisco, dunque per ora devo badare a lei.";
			link.l1 = "Non insisterò, compare. Se proprio non vuoi, può restare sulla mia nave. Ma dovrò incatenarla per sicurezza e tenerla nella stiva coi topi, giusto per tenerla al sicuro dalla mia ciurma. Per loro una donna a bordo è una rarità, sai. Sarebbe un vero peccato trattare così una ragazza tanto graziosa.";
			link.l1.go = "Abigile_7";
		break;
		
		case "Abigile_7":
			dialog.text = "Capisco. Va bene, conducila qui. È mio dovere aiutarti nella tua lotta contro Fleetwood. Portala e le preparerò la sua 'stanza degli ospiti'.";
			link.l1 = "Grazie John. Sapevo di poter contare su di te.";
			link.l1.go = "exit";
			pchar.questTemp.HWIC.Self = "AbigileInCabin";
			DoQuestCheckDelay("SetAbigileToCabin", 1.0); // fix 180812
			AddQuestRecord("Holl_Gambit", "3-24");
			//поставим табурет
			sld = ItemsFromID("lcheer");
			sld.shown = true;
			sld.startLocation = "SentJons_HouseF3";
			sld.startLocator = "goto2";
			AddLandQuestMark(characterFromId("Abigile"), "questmarkmain");
		break;
		
		case "Abigile_7_1":
			DelLandQuestMark(npchar);
			dialog.text = "Oh! Un vero piacere. Son lieto d’accogliere una dama tanto importante e... sì raffinata. Signorina, vogliate salire al secondo piano, vi prego. La cena v’attende, e il letto è pronto. Son certo che desidererete un buon sonno dopo sì lungo viaggio.";
			link.l1 = "Sì. Abigail sarà sicuramente sfinita dopo un viaggio così lungo da Willemstad.";
			link.l1.go = "Abigile_8";
		break;
		
		case "Abigile_8":
			DialogExit();
			sld = characterFromId("Abigile");
			sld.dialog.currentnode = "Abigile_kidnapping_11";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Abigile_9":
			dialog.text = "Hai già una rotta in testa?";
			link.l1 = "Lo faccio io. Dobbiamo scrivere una lettera a Richard chiedendo un riscatto per Abigail. Organizziamo un incontro su qualche isola deserta, tipo le Turks. E se non si piega alla nostra richiesta, beh, gli spediremo la sua bella ebrea a pezzetti.";
			link.l1.go = "Abigile_10";
		break;
		
		case "Abigile_10":
			dialog.text = "Perché mai tutta questa confusione per un’isola disabitata?";
			link.l1 = "Terreno neutrale. È più sicuro. Non porterò comunque Abigail. Mi serve Fleetwood. Sicuramente preparerebbe un’imboscata ad Antigua, ma a Turks non avrebbe tale vantaggio.";
			link.l1.go = "Abigile_11";
		break;
		
		case "Abigile_11":
			dialog.text = "D'accordo.  Chi consegnerà la lettera?  È un rischio del diavolo.";
			link.l1 = "Uno sconosciuto. Prendi un ubriacone dalla taverna, uno che sembri affidabile. Farà tutto ciò che gli chiedi in cambio di qualche moneta per il rum. Se Richard lo ammazza in preda alla furia, ne manderemo un altro. E stavolta allegheremo una delle dita di Abi alla lettera. Così vedrai quanto diventerà più docile.";
			link.l1.go = "Abigile_12";
		break;
		
		case "Abigile_12":
			dialog.text = ""+pchar.name+"...";
			link.l1 = "Non temere, John. Son certo che non si arriverà a tanto. Devi solo trovare un corriere e io metterò subito mano alla lettera. Hai un po' di carta e inchiostro?";
			link.l1.go = "Abigile_13";
		break;
		
		case "Abigile_13":
			dialog.text = "Sì, certo. E per caso conosco pure un ubriacone adatto allo scopo. Ti consiglio Jack Harrison. Passa ogni sera in taverna, a tracannare rum senza sosta. Lo troverai senza fatica.";
			link.l1 = "Bene, portami penna e inchiostro che scrivo la lettera di riscatto per Richard.";
			link.l1.go = "Abigile_14";
		break;
		
		case "Abigile_14":
			DialogExit();
			StartQuestMovie(true, false, true);
			locCameraFromToPos(0.07, 2.57, -2.46, true, -0.08, -0.38, 1.35);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto2", "MC_writeLetter", -1);
		break;
		
		case "Abigile_15":
			dialog.text = "Quando gli consegnerai la lettera? Hai intenzione di assistere alla consegna in persona?";
			link.l1 = "Certo. Richard non è uno sprovveduto, ma dubito che si arrischierà troppo. Almeno, lo spero. Non voglio far del male alla ragazza, ma se sarà necessario, lo farò. Bene, è ora di trovare quel beone di cui parlavi. Jack... qual era il suo nome completo?";
			link.l1.go = "Abigile_20";
		break;
		
		case "Abigile_20":
			dialog.text = "Si chiama Jack Harrison. Di solito si fa vedere in taverna la sera. Sta’ in campana!";
			link.l1 = "Andrà tutto bene. Aspettami.";
			link.l1.go = "Abigile_22";
		break;
		
		case "Abigile_22":
			DialogExit();
			LAi_SetOwnerType(npchar);
			pchar.questTemp.HWIC.Self = "LetterToDrunkardGo";
			AddDialogExitQuestFunction("CreateDrunckardInTavern");
			AddQuestRecord("Holl_Gambit", "3-25");
		break;
		
		case "Abigile_23":
			DelLandQuestMark(npchar);
			dialog.text = "Beh, non direi proprio. Fleetwood è furbo e pericoloso. Inoltre, è un maestro di spada e un vecchio lupo di mare. Non sarà una preda facile.";
			link.l1 = "Ho smesso di cercare la via più facile da quando sono arrivato ai Caraibi. Bene, John, è giunta l’ora che io me ne vada. A proposito, hai detto che il nostro valoroso Fleetwood se la spassa su una bella nave, vero?";
			link.l1.go = "Abigile_24";
		break;
		
		case "Abigile_24":
			dialog.text = "Ha il brigantino più bello che abbia mai visto. E ne ho visti parecchi.";
			link.l1 = "Bene. Mi piacciono le navi di pregio. È ora di salpare l’ancora!";
			link.l1.go = "Abigile_26";
		break;
		
		case "Abigile_26":
			DialogExit();
			pchar.questTemp.HWIC.Self = "FleetwoodToIsland";
			pchar.quest.Fleetwood_meetingShore.win_condition.l1 = "location";
			pchar.quest.Fleetwood_meetingShore.win_condition.l1.location = "Shore56";
			pchar.quest.Fleetwood_meetingShore.function = "InTerksShore";
			AddQuestRecord("Holl_Gambit", "3-28");
			AddMapQuestMarkShore("Shore57", false);
		break;
		
		case "Abigile_27":
			int iVal = 0;
			for(i = 0; i < COMPANION_MAX; i++)
			{
				iTemp = GetCompanionIndex(PChar, i);
				if(iTemp > 0)
				{
				sld = GetCharacter(iTemp);
				if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_VALCIRIA) iVal = 1;
				}
			}//установили признак наличия Валькирии в эскадре.
			if (iVal != 0)
			{
				dialog.text = "Son senza parole! Un'accoppiata magnifica, un'idea geniale e una realizzazione da vero maestro! I miei complimenti, "+pchar.name+" E sei riuscito pure a prendere la sua brigantina come bottino!";
				link.l1 = "Grazie! E dov’è Hercule? Vorrei vederlo. L’ultima volta che ci siamo incontrati mi ha detto che, con il tuo aiuto, l’avrei trovato.";
				link.l1.go = "Abigile_28";
			}
			else
			{
				dialog.text = "Un'accoppiata eccellente, un'idea brillante e un'esecuzione da maestro! Le mie congratulazioni, "+pchar.name+"!";
				link.l1 = "Grazie! E dove si trova Hercule? Vorrei vederlo. L’ultima volta che ci siamo incontrati, mi disse che l’avrei trovato proprio grazie a te.";
				link.l1.go = "Abigile_28";
			}
		break;
		
		case "Abigile_28":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("SentJons");
			dialog.text = "Lo aspetto da un momento all’altro. Dovrebbe arrivare qui passando dal tunnel segreto. E tu, dovresti spiegarti con Abigail: ha cominciato a preoccuparsi per l’assenza di Richard.";
			link.l1 = "D'accordo, ma non dovremmo rimandarla a casa?";
			link.l1.go = "Abigile_29";
		break;
		
		case "Abigile_29":
			dialog.text = "Non ancora... Prima devo parlarti. Ma aspetta che arrivi Hercule. Vai a consolare Abigail. Raccontale una storia, inventa qualcosa. Poi raggiungimi in cantina. Intesi?";
			link.l1 = "Agli ordini, John.";
			link.l1.go = "Abigile_30";
		break;
		
		case "Abigile_30":
			DialogExit();
			npchar.greeting = "merdok_4";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "SentJons_TownCave", "item", "berglar1", "", -1);
			pchar.questTemp.HWIC.Self = "AbigileLie";
			sld = characterFromId("Abigile");
			LAi_SetCitizenType(sld);
			AddLandQuestMark(sld, "questmarkmain");
			AddQuestRecord("Holl_Gambit", "3-34");
		break;
		
		case "Lucas":
			DelLandQuestMark(npchar);
			dialog.text = "Ebbene, è giunta l’ora di scoprire le carte. Come avrai già capito, non sono un semplice speziale. Il mio vero nome è Johan van Merden e fino a poco tempo fa ero un agente della Compagnia Olandese delle Indie Occidentali, nonché braccio destro del suo vicepresidente, Lucas Rodenburg.";
			link.l1 = "Davvero! Che faccenda intrigante...";
			link.l1.go = "Lucas_1";
		break;
		
		case "Lucas_1":
			dialog.text = "Adesso è tutto diverso. Lucas vuole mollare il gioco e tornarsene nei Paesi Bassi, perciò deve seppellire tutto e tutti quelli legati al suo passato.\nPenso che respiro ancora solo grazie ai miei archivi, che custodiscono tutte le prove delle malefatte di Lucas... come la storia della 'nave fantasma', che in realtà è solo una nave pirata comandata da quel furfante senza scrupoli, Jacob van Berg. È stato Rodenburg a ingaggiare quel cane per saccheggiare e affondare navi mercantili inglesi.\nAnche l'affondamento del fluyt con a bordo Abigail e suo padre è opera di Van Berg. Abigail è una pedina importante in questa partita; Rodenburg voleva conquistarla, proprio come Fleetwood, quindi sono rimasto di sasso quando me l'hai portata qui...";
			link.l1 = "Rodenburg... questo è il genero di cui straparlava quel padre svitato di Abigail!";
			link.l1.go = "Lucas_2";
		break;
		
		case "Lucas_2":
			dialog.text = "Sì, è proprio per questo che voglio che resti qui ancora un po'. Potrebbe essere la mia ultima carta nella partita contro Rodenburg, anche se preferirei non doverla più coinvolgere, è una brava ragazza, non voglio che soffra. Penso che Lucas sceglierebbe il mio archivio piuttosto che lei, se dovesse trovarsi davanti a una scelta.\nDunque, ti propongo di diventare mio alleato contro Lucas... liberatene, con qualsiasi mezzo necessario. La ricompensa sarà generosa.";
			link.l1 = "Hmm... Non credo che sarà più difficile che con Fleetwood. ";
			link.l1.go = "Lucas_3";
		break;
		
		case "Lucas_3":
			dialog.text = "No, ti sbagli. Alla fine, Fleetwood era un lupo solitario, agiva per conto suo. Rodenburg è il vicepresidente della Compagnia. È un uomo molto influente, solo il governatore di Curaçao ha più potere di lui. Jacob van Berg è il suo braccio destro, un tipo davvero pericoloso. Lucas se ne sta seduto sul culo a Willemstad, protetto dagli sbirri della Compagnia, e valgono quanto gli uomini di Fleetwood.  Non sarà affatto una passeggiata.";
			link.l1 = "Le regole del gioco sono le stesse: stanare la tigre dalla sua tana... Ho già un piano. Cos’altro puoi dirmi su Lucas?";
			link.l1.go = "Lucas_4";
		break;
		
		case "Lucas_4":
			dialog.text = "Ebbene, ti ho raccontato quasi tutto. Possiede una nave veloce chiamata 'Meifeng' – Vento Bello. Il suo capitano è un cinese di nome Longway, uomo di fiducia di Rodenburg. Anche lui è un avversario che non vorresti mai trovarti di fronte. Nell’equipaggio di Lucas non trovi mai dei dilettanti.";
			link.l1 = "Sin dall’inizio avevamo un asso nella manica: il tuo archivio. Se tiene più alla sua pellaccia che a quella dell’ebrea, farà di tutto pur di tenere segrete le informazioni contenute lì dentro... Ma... questo archivio esiste davvero, John? O stai facendo il furbo?";
			link.l1.go = "Lucas_5";
		break;
		
		case "Lucas_5":
			dialog.text = "L’archivio esiste davvero. E Lucas ne è al corrente. Hai già avuto qualche idea, per caso?";
			link.l1 = "Lo so. John, se fossi davvero un agente della Compagnia, dovresti saperne qualcosa.";
			link.l1.go = "Lucas_6";
		break;
		
		case "Lucas_6":
			dialog.text = "Cosa precisamente? Chiedimi pure.";
			link.l1 = "Ho bisogno d’intercettare una nave della Compagnia. Meglio se viaggia senza scorta – magari un corriere, o qualcosa di simile. Puoi dirmi qualcosa a riguardo?";
			link.l1.go = "Lucas_7";
		break;
		
		case "Lucas_7":
			dialog.text = "Hm... Non sono in possesso di tali informazioni. Aspetta! So con certezza che la Compagnia manda una nave postale sulle rotte tra Philipsburg e Willemstad una volta al mese. Porta documenti d'affari. È una brigantina chiamata 'Hoop'.\nSalperà da Philipsburg oggi o domani.";
			link.l1 = "Aye, proprio così! Tutto ciò che mi serve per salpare verso le coste di Saint Christophe. La rotta per Curaçao ci passa proprio accanto.";
			link.l1.go = "Lucas_8";
		break;
		
		case "Lucas_8":
			dialog.text = "Buona fortuna, "+pchar.name+". Non ti chiederò i dettagli del tuo piano. Ti aspetterò al tuo ritorno!";
			link.l1 = "Andrà tutto bene, John. Abbi cura della giudea e trattala come si deve!";
			link.l1.go = "Lucas_9";
		break;
		
		case "Lucas_9":
			DialogExit();
			RemoveItems(PChar, "MC_Letter", 1);
			GiveItem2Character(pchar, "MC_Letter");
			ChangeItemDescribe("MC_Letter", "itmdescr_MC_Letter2");
			AddQuestRecordInfo("LetterToLucas", "1");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "SentJons_HouseF3", "goto", "goto1", "MC_TakeCloves", -1);
			pchar.questTemp.HWIC.Self = "LetterToLucas";
			sld = characterFromId("Tonzag");
			sld.dialog.currentnode = "Tonzag_hired";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			AddQuestRecord("Holl_Gambit", "3-36");
			//установим таймер на генерацию энкаунтера
			pchar.quest.HWIC_Cureer.win_condition.l1 = "Timer";
			pchar.quest.HWIC_Cureer.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.HWIC_Cureer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.HWIC_Cureer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.HWIC_Cureer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.HWIC_Cureer.function = "CreateHWICCureerOnMap";
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("HWICCureerOnMapOver", 0, 0, 16, false);//таймер
		break;
		
		case "Lucas_10":
			dialog.text = "Incredibile! Non posso credere alle mie orecchie! Come diavolo è successo?";
			link.l1 = "Ho catturato la nave postale e ho inviato una lettera a Lucas per conto di Fleetwood, dicendo che avevo messo le mani su certi archivi appartenenti a un speziale di St. John's, e che presto le prove di tutte le sue malefatte sarebbero state note da qui fino ad Amsterdam e Londra. Mi aspettavo che mi desse la caccia, ma la faccenda ha preso tutt'altra piega.";
			link.l1.go = "Lucas_11";
		break;
		
		case "Lucas_11":
			dialog.text = "";
			link.l1 = "Lucas ha accusato Matthias Beck di tradimento e d’intrighi con gli inglesi, l’ha cacciato dietro le sbarre e s’è sistemato nel palazzo del governatore. Con ogni probabilità ha fatto sparire anche il capitano della brigantina. Poi ha ordinato al suo fedele cinese della Meifeng di mandare a fondo la nave con a bordo il direttore della Compagnia, Peter Stuyvesant!";
			link.l1.go = "Lucas_12";
		break;
		
		case "Lucas_12":
			dialog.text = "Rodenburg è un uomo spietato. Ma perfino io non avrei mai pensato che potesse spingersi così oltre...";
			link.l1 = "Ho catturato la Meifeng e interrogato Longway. Mi ha raccontato tutto. Ho trovato Stuyvesant e l’ho avvisato delle intenzioni di Rodenburg, così siamo salpati insieme per Willemstad. Stuyvesant ha liberato Beck e fatto arrestare Lucas. Ora marcisce in prigione.";
			link.l1.go = "Lucas_13";
		break;
		
		case "Lucas_13":
			dialog.text = "Heh! Hai un vero talento, amico mio... Dovresti far carriera nella Marina della Compagnia o diventare politico nelle Province Unite – hai tutte le carte in regola per diventare governatore! E che hai combinato con Longway?";
			link.l1 = "L’ho lasciato andare. Si è arreso con onore, quindi non gli ho fatto alcun male.";
			link.l1.go = "Lucas_14";
		break;
		
		case "Lucas_14":
			dialog.text = "Bene così. Longway è un brav’uomo, non come il suo vecchio padrone. Ebbene, "+pchar.name+", hai fatto un lavoro eccellente! Preparerò la tua ricompensa, ma avrò bisogno di un po' di tempo... Nel frattempo...";
			link.l1 = "John, a dir la verità, c’è un piccolo grattacapo. Prima Longway, poi anche Rodenburg mi hanno detto che Jacob van Berg mi sta dando la caccia. Quanto è brutta la faccenda?";
			link.l1.go = "Lucas_15";
		break;
		
		case "Lucas_15":
			dialog.text = "Jacob van Berg? Charlie, questa è roba seria. È un piratto spietato, un marinaio e spadaccino così abile da far sembrare Fleetwood una gattina. Un vero cacciatore di uomini. Fu lui a massacrare i convogli su ordine di Rodenburg.\nTi troverà, quindi devi prepararti. Anch’io farei meglio a prendere precauzioni.";
			link.l1 = "Come posso rintracciare questo van Berg?";
			link.l1.go = "Lucas_16";
		break;
		
		case "Lucas_16":
			dialog.text = "Non lo so. Lucas e Longway erano gli unici che sapevano dove trovarlo. Quindi stai all’erta e pronto.\nSto chiudendo il posto. Se vuoi vedermi, passa dal passaggio segreto. E porta via la giudea, qui per lei tira aria troppo pesante.";
			link.l1 = "Non ti preoccupare, John. Lascia che si faccia vedere e ci penso io. Dov’è Abigail?";
			link.l1.go = "Lucas_17";
		break;
		
		case "Lucas_17":
			dialog.text = "È andata in chiesa. Mi dispiace per lei. Ultimamente è stata molto turbata.";
			link.l1 = "Ebbene... Che piacevole sorpresa. Forse ha compreso che Cristo è il Messia tanto atteso dal suo popolo. Ora, però, è giunto il momento di riportarla da suo padre.";
			link.l1.go = "Lucas_18";
		break;
		
		case "Lucas_18":
			dialog.text = "Voleva vederti. Sono certo che ti chiederà di riportarla a casa.";
			link.l1 = "Abi, eh?";
			link.l1.go = "Lucas_19";
		break;
		
		case "Lucas_19":
			dialog.text = "Devo ammettere che siamo diventati amici. Non mi pento d’averla ospitata sotto il mio tetto, e grazie al cielo non saprà mai per quale motivo fu condotta qui.";
			link.l1 = "D'accordo, John, andrò in chiesa a incontrare Abigail. Poi metterò la prua su Willemstad.";
			link.l1.go = "Lucas_20";
		break;
		
		case "Lucas_20":
			DialogExit();
			sld = characterFromId("Abigile");
			AddLandQuestMark(sld, "questmarkmain");
			ChangeCharacterAddressGroup(sld, "SentJons_church", "goto", "goto1");//Аби - в церковь
			AddQuestRecord("Holl_Gambit", "3-56");
			pchar.questTemp.HWIC.Self = "AbiReturnHome";
			LocatorReloadEnterDisable("SentJons_town", "HouseF3", true);//закрыть аптеку
		break;
		
		case "Final":
			dialog.text = "Hai... schiacciato le sue noci? Ah, una metafora. Beh, con o senza noci, ce l'hai fatta! Complimenti!";
			link.l1 = "Non ti prenderebbe mai in giro, eh. Ora puoi tirare un sospiro di sollievo, John.";
			link.l1.go = "Final_1";
		break;
		
		case "Final_1":
			dialog.text = "Finalmente! Credo sia meglio lasciar perdere tutti questi giochetti politici e intrighi. Ora è il momento di parlare della tua ricompensa per il lavoro.";
			link.l1 = "Beh, te ne sarei davvero grato.";
			link.l1.go = "Final_2";
		break;
		
		case "Final_2":
			dialog.text = "Sto per lasciare i Caraibi per sempre. In segno di gratitudine per il tuo aiuto e per avermi salvato dalle grinfie di Rodenburg, ti lascio l’atto di proprietà di questa casa e della mia bottega di spezie. Ora sono tutte tue. Prendi queste chiavi.";
			link.l1 = "Magnifico! Son proprio felice. Hai una casa assai accogliente e una cantina davvero invitante...";
			link.l1.go = "Final_3";
		break;
		
		case "Final_3":
			GiveItem2Character(pchar, "Drugstore_keys");//ключ
			dialog.text = "E accetta anche questa modesta somma di 100 000 pesos e questo moschetto. Un tempo ha servito me con fedeltà, ora servirà altrettanto bene anche te.";
			link.l1 = "Non rifiuto certo doni simili!";
			link.l1.go = "Final_4";
			LocatorReloadEnterDisable("SentJons_town", "HouseF3", false);//открыть аптеку
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload3", false); // открыть комнату
			pchar.quest.Jino_Door.win_condition.l1 = "locator";
			pchar.quest.Jino_Door.win_condition.l1.location = "SentJons_HouseF3";
			pchar.quest.Jino_Door.win_condition.l1.locator_group = "reload";
			pchar.quest.Jino_Door.win_condition.l1.locator = "reload4";
			pchar.quest.Jino_Door.function = "OpenRoomDoor";//на локатор комнаты Джино
			Achievment_Set("ach_10");
		break;
		
		case "Final_4":
			AddMoneyToCharacter(pchar, 100000);
			GiveItem2Character(pchar, "mushket2");
			dialog.text = "Nella stanza al piano di sopra troverai un giovane filosofo naturale. È il miglior speziale che io conosca. Fu lui a preparare questi intrugli che ti hanno rimesso in sesto in pochi giorni. Occupati della sua paga e la sua sapienza ti ripagherà con interessi.";
			link.l1 = "La mia personale tarma da biblioteca? D'accordo, me ne occuperò io.";
			link.l1.go = "Final_5";
		break;
		
		case "Final_5":
			dialog.text = "Devo dirti addio ora. Scendo in cantina a raccogliere le mie cose. Domani non sarò più qui – salpo via da Antigua. Son lieto d’averti incontrato e che tu sia stato dalla mia parte, e non tra i miei dannati nemici.";
			link.l1 = "Anche io son lieto d’incontrarti, John. Forse ci rivedremo ancora...";
			link.l1.go = "Final_6";
		break;
		
		case "Final_6":
			dialog.text = "Non in questa vita, amico mio. Ora raccolgo le mie cose. Addio, "+pchar.name+"!";
			link.l1 = "Addio, John! Che la fortuna ti accompagni!";
			link.l1.go = "Final_7";
		break;
		
		case "Final_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", -1);
			npchar.lifeday = 0;
			pchar.questTemp.HWIC.Self = "final";
			AddQuestRecord("Holl_Gambit", "3-64");
			CloseQuestHeader("Holl_Gambit");
			pchar.questTemp.HWIC.Detector = "self_win";
			CheckPortugalHWIC();
		break;
		
		// Страж Истины
		case "guardoftruth":
			dialog.text = "Ah, buon signore, non dia retta a queste sciocchezze. Lì non c’è anima viva. È solo il mio laboratorio, dove si preparano intrugli, sa com’è...";
			link.l1 = "Tutte le battute a parte, John. Ti dice niente il nome di Gino Gvineili?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Hmm...";
			link.l1 = "Ah! Lo vedo nei tuoi occhi – ho colto nel segno... È lì che vive e per chi prepara i suoi intrugli!";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Signore, ve lo ripeto ancora una volta – qui non c'è anima viva.";
			link.l1 = "Mettiamo da parte le scuse, John. Non farò del male al tuo alchimista — ma se padre Vincento di Santiago lo trova, non posso garantire nulla. L’Inquisitore già pianifica di mandare i suoi ‘Domini Canes’ ad Antigua...";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Cosa gli vuoi?";
			link.l1 = "Solo per parlare. Ha delle informazioni molto importanti per me. Prometto che non lo consegnerò all’Inquisizione e non gli farò alcun male.";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "Gino è un brav’uomo, fidati. Non dar retta a tutto quel che ti racconta Padre Vincento su di lui. E bada bene – io il mio alchimista lo difenderò sempre.";
			link.l1 = "Ti ho dato la mia parola. Non ti basta, eh?";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "Sali pure al piano di sopra, allora. La porta è aperta. E spera di mantenere la parola data.";
			link.l1 = "Stai tranquillo, ci penserò io.";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			DialogExit();
			pchar.questTemp.Guardoftruth = "jino1";
			AddQuestRecord("Guardoftruth", "36");
			LocatorReloadEnterDisable(pchar.location, "reload4", false);
		break;
		
		// алхимический набор
		case "alchemy":
			dialog.text = "Capitano, non vi piacerebbe addentrarvi nelle arti ermetiche? Potrebbero tornarvi assai utili, sapete.";
			link.l1 = "Mi rincresce, ma il mio mestiere è ben diverso. Sono abituato a impugnare l’elsa di una spada, non fiaschi o provette.";
			link.l1.go = "alchemy_exit";
			link.l2 = "«Ci sono più cose in cielo e in terra di quante ne immagini la tua filosofia.» Ma certo che mi piacerebbe. Che serve fare?";
			link.l2.go = "alchemy_1";
			npchar.quest.alchemy = true;
		break;
		
		case "alchemy_exit":
			dialog.text = "Come desideri. Era solo un’offerta...";
			link.l1 = "...";
			link.l1.go = "exit";
		break;
		
		case "alchemy_1":
			dialog.text = "Dovresti imparare a mescolare le erbe con le tue stesse mani. Ma senza un kit da alchimista non ci riuscirai mai. Guarda questa sacca. C’è tutto ciò che serve a un apprendista alchimista: provette, fiasche, un alambicco, spatole, cannule di vetro, un fornello e altra roba simile...";
			link.l1 = "Molto interessante! E che cosa ci posso cucinare con questa roba?";
			link.l1.go = "alchemy_2";
		break;
		
		case "alchemy_2":
			dialog.text = "Ebbene, non potrai trasformare il piombo in oro, ma potrai mescolare ingredienti seguendo varie ricette e così ottenere pozioni e altre cose utili.";
			link.l1 = "Ricette?";
			link.l1.go = "alchemy_3";
		break;
		
		case "alchemy_3":
			dialog.text = "Giusto. Devi conoscere una ricetta per preparare una pozione o un oggetto. Le ricette si possono comprare dai mercanti o trovare ovunque. Una volta studiata la ricetta, raccogli tutti gli ingredienti necessari e segui esattamente le istruzioni scritte lì\n Usa i tuoi strumenti d’alchimia, procurati o acquista un mortaio e un pestello, trova un crogiolo – ahimè, non ne ho uno di scorta da darti. Erbe, spiriti, pozioni, minerali, robaccia – tutto va bene, purché tu abbia la ricetta giusta e gli attrezzi adatti.";
			link.l1 = "Molto interessante. E quanto vuoi per questo marchingegno?";
			link.l1.go = "alchemy_4";
		break;
		
		case "alchemy_4":
			dialog.text = "Venti mila pesos. Questo è un equipaggiamento di prim’ordine, si ripagherà in men che non si dica.";
			link.l1 = "Mi prendi in giro, vero? Una borsetta piena di bicchieri al prezzo di una lugger? No, rinuncio.";
			link.l1.go = "alchemy_exit";
			if (sti(pchar.money) >= 20000)
			{
				link.l2 = "Sono d’accordo. Credo sarà intrigante provare a creare qualcosa con le mie stesse mani.";
				link.l2.go = "alchemy_5";
			}
		break;
		
		case "alchemy_5":
			AddMoneyToCharacter(pchar, -20000);
			Log_Info("You've got the alchemist's kit.");
			GiveItem2Character(pchar, "alchemy_tool");
			PlaySound("interface\important_item.wav");
			dialog.text = "Non vi pentirete di questo acquisto, ne sono assolutamente certo. Senza dubbio, conviene assai di più preparare le pozioni da sé, all’occorrenza, piuttosto che andare ogni volta dai cerusici a comprare ogni cosa a parte. E poi, non sempre troverete tutto ciò che vi serve in vendita.";
			link.l1 = "Impariamo. Credo di potercela fare!";
			link.l1.go = "alchemy_6";
		break;
		
		case "alchemy_6":
			DialogExit();
			PlaySound("interface\notebook.wav");
			Log_Info("In order to make your own herbs and amulets you must have the Alchemy skill!");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Tu sei un "+GetSexPhrase("Ladro, messere! Guardie, prendetelo!","Ladra, ragazza! Guardie, prendetela")+"!!!","Ma guarda un po’! Appena mi sono distratto a rimirare il mare, tu già frughi nel mio baule! Al ladro!!!","Guardie! Rapina! Prendete il furfante!!!");
			link.l1 = "Maledizione!";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}

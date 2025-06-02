// диалоги прочих НПС
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
		case "First time":
			dialog.text = "Un bug. Avvisa gli sviluppatori.";
			link.l1 = "Lo farò!";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			if (npchar.id == "HWICFernando") NextDiag.CurrentNode = "Fernando";
			DialogExit();
		break;
	
//---------------------------------------за Голландию--------------------------------------------------
		//сопроводить торговца
		case "Baltazar":
			pchar.quest.Create_BaltazarOver.over = "yes";//снять прерывание
			dialog.text = "Che colpo di fortuna! Capitano, guarda caso avrei proprio un disperato bisogno d'una scorta fino a Philipsburg...";
			link.l1 = "Sei tu Balthazar Ridderbock?";
			link.l1.go = "Baltazar_1";
			DelLandQuestMark(npchar);
		break;
		
		case "Baltazar_1":
			dialog.text = "Per mille balene, sono già più famoso del viceré! Chi diavolo sei? Che vuoi da me?";
			link.l1 = "Sono il Capitano "+GetFullName(pchar)+" . Sono stato mandato da Lucas Rodenburg. Ho l’autorità di prenderti sotto la mia protezione, te e la tua nave.";
			link.l1.go = "Baltazar_2";			
		break;
		
		case "Baltazar_2":
			dialog.text = "Oh, monsieur Rodenburg deve aver udito le mie suppliche d'aiuto! Vedete, c’è un certo corsaro...";
			link.l1 = "Saltiamo i dettagli della tua storia, li conosco già.";
			link.l1.go = "Baltazar_3";			
		break;
		
		case "Baltazar_3":
			dialog.text = "Ma certo! Ho già perso fin troppo tempo... Devo arrivare a Philipsburg entro due settimane, non un giorno di più.";
			link.l1 = "Allora vai alla tua nave e preparati a mollare gli ormeggi. Salpiamo subito!";
			link.l1.go = "Baltazar_4";			
		break;
		
		case "Baltazar_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 4);
			SetCharacterRemovable(npchar, false);
			npchar.CompanionEnemyEnable = false; //всегда друзья
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.loyality = MAX_LOYALITY;
			AddQuestRecord("Holl_Gambit", "1-3");
			AddMapQuestMarkCity("Marigo", true);
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("Baltazar_ConvoyOver", 0, 0, 28, false);
			}
			else SetFunctionTimerCondition("Baltazar_ConvoyOver", 0, 0, 14, false); //таймер
			pchar.quest.BaltazarConvoy_fail.win_condition.l1 = "NPC_Death";//прерывание на потопление сопровождаемого
			pchar.quest.BaltazarConvoy_fail.win_condition.l1.character = "Baltazar";
			pchar.quest.BaltazarConvoy_fail.function = "Baltazar_fail";
			pchar.quest.BaltazarConvoy_complete.win_condition.l1 = "location";//прерывание на выполнение
			pchar.quest.BaltazarConvoy_complete.win_condition.l1.location = "Marigo_town";
			pchar.quest.BaltazarConvoy_complete.function = "Baltazar_complete";
			if (rand(1) == 0)
			{
				BaltazarPirateGlobalCreate();
			}
			else
			{
				pchar.questTemp.HWIC.Holl.BaltazarAttack = "true";
				pchar.quest.BaltazarConvoy_Attack.win_condition.l1 = "location";//прерывание на выполнение
				pchar.quest.BaltazarConvoy_Attack.win_condition.l1.location = "SentMartin";
				pchar.quest.BaltazarConvoy_Attack.function = "BaltazarPirateSeaCreate";
			}
		break;
		
		case "Baltazar_5":
			dialog.text = "Grazie per il vostro aiuto, Capitano! La vostra protezione è arrivata proprio al momento giusto, vi prego di accettare la mia gratitudine e questi 5.000 pesos.";
			link.l1 = "Hmm... Questa ricompensa non mi pare proprio all’altezza di una vita salvata...";
			link.l1.go = "Baltazar_6";			
		break;
		
		case "Baltazar_6":
			dialog.text = "Inoltre, appena ne avrò l’occasione, manderò una lettera a monsieur Rodenburg – con le più alte lodi per le vostre imprese. Ora devo andarmene.";
			link.l1 = "Ebbene, addio allora, Balthazar.";
			link.l1.go = "Baltazar_7";			
		break;
		
		case "Baltazar_7":
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2_back", "none", "", "", "", 3.0);
			AddQuestRecord("Holl_Gambit", "1-6");
			AddMoneyToCharacter(pchar, 5000);
			ChangeCharacterComplexReputation(pchar,"nobility", 2); 
			ChangeCharacterNationReputation(pchar, HOLLAND, 1);
			ChangeOfficersLoyality("good_all", 1);
			pchar.questTemp.HWIC.Holl = "BaltazarCom";
			AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
			AddMapQuestMarkCity("Villemstad", true);
		break;
		
		//командировка в Сантьяго
		case "Santiago_Trip":
			dialog.text = "Señor! Aspetta... pare che t’è cascato qualcosa...";
			link.l1 = "Cosa? Eh?!";
			link.l1.go = "Santiago_Trip_1";
		break;
		
		case "Santiago_Trip_1":
			DialogExit();
			PlaySound("People Fight\Death_NPC_08.wav");
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("You were knocked unconscious from behind", "", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 15, 10); //крутим время
			RecalculateJumpTable();
			DoQuestFunctionDelay("SantiagoTripInHouse", 4.0);
		break;
		
		case "Santiago_Trip_2":
			dialog.text = "Scusami, amico mio – ti ho dovuto dare una leggera botta, giusto per non far casino. Immagino che la testa ti rimbombi, ma insomma, sopravviverai. Sempre che ti resti il tempo per pensare a questo...";
			link.l1 = "Chi diavolo sei, e che sta succedendo qui?";
			link.l1.go = "Santiago_Trip_3";
		break;
		
		case "Santiago_Trip_3":
			dialog.text = "Piano, piano, amico mio – altrimenti dovrò calmarti di nuovo. Non vorrai mica che questi piedipiatti irrompano qui, sbattendo le loro spade arrugginite, vero? Meglio parlarci tranquilli.";
			link.l1 = "Ridammi la mia spada, bastardo, e parliamo da uomini, te lo giuro!";
			link.l1.go = "Santiago_Trip_4";
		break;
		
		case "Santiago_Trip_4":
			dialog.text = "Sei davvero un tipetto svelto, eh? Non c’è bisogno di tirare fuori la lama per ora. Dimmi quello che voglio sapere e magari te ne vai da qui tutto intero. Mi segui? Su, parliamo un po’.\nBocca cucita, eh? Va bene, allora siamo d’accordo. Cosa hai portato da Rodenburg al banchiere?";
			link.l1 = "Una lettera.";
			link.l1.go = "Santiago_Trip_5";
		break;
		
		case "Santiago_Trip_5":
			dialog.text = "Astuto. So che non era certo un mazzo di margherite. Che c’era scritto in quella lettera, ragazzo?";
			link.l1 = "Come dovrei saperlo? Non mi capita di ficcare il naso nelle lettere, anche se мне их доверяют. Magari era una missiva d’amore. Sai cosa si dice di chi comanda, eh...";
			link.l1.go = "Santiago_Trip_6";
		break;
		
		case "Santiago_Trip_6":
			dialog.text = "...Un capitano onesto è merce rara in questi tempi maledetti. Eh, brutte nuove per te. Che diavolo ti ha detto quel banchiere, quando ha ricevuto il pacco? Che affari ha in corso con gli olandesi?";
			link.l1 = "Trafficano in profumi di contrabbando dalla Francia... o forse sterco di vacca bavarese, mi pare.";
			link.l1.go = "Santiago_Trip_7";
			link.l2 = "La domanda riguardava un compenso per qualcosa. È tutto ciò che so.";
			link.l2.go = "Santiago_Trip_8";
		break;
		
		case "Santiago_Trip_7":
			dialog.text = "Sei un tipo coraggioso... E pure con spirito. Sarebbe un peccato farti fuori. Gaston ti avrebbe preso in simpatia. Però... resta qui per ora. Devo andare a vedere una cosa, e Miguel baderà a te mentre sarò via.";
			link.l1 = "Te lo giuro, 'amico mio' – te ne pentirai amaramente! ";
			link.l1.go = "Santiago_Trip_9";
		break;
		
		case "Santiago_Trip_8":
			dialog.text = "Là se ne va tutta quell’arroganza… Quando la tempesta si avvicina, il nostro prode capitano si fa finalmente ragionevole. Potevi pensarci prima e ci avresti risparmiato tempo e rogne. Vabbè, ora devo andare a controllare una faccenda, ma poi torno e parleremo ancora, sempre che ce ne sia bisogno. Resta qui per ora. Miguel ti terrà d’occhio mentre sono via.";
			link.l1 = "Giuro, 'mio caro', te ne pentirai amaramente! ";
			link.l1.go = "Santiago_Trip_11";
		break;
		
		case "Santiago_Trip_9":
			dialog.text = "Ma certo. Tieniti la lingua a freno, 'eroe' – magari tutto finirà per il meglio.";
			link.l1 = "...";
			link.l1.go = "Santiago_Trip_11";
		break;
		
		case "Santiago_Trip_10":
			dialog.text = "Resta qui e spera che la tua duttilità ti salvi la pelle.";
			link.l1 = "...";
			link.l1.go = "Santiago_Trip_11";
		break;
		
		case "Santiago_Trip_11":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "1-44");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "Santiago_HouseSp2", "goto", "goto4", "", -1);
			pchar.quest.Santiago_Trip1.win_condition.l1 = "item";
			pchar.quest.Santiago_Trip1.win_condition.l1.item = "slave_01";
			pchar.quest.Santiago_Trip1.function = "SantiagoTrip_wait";
		break;
		
		case "Santiago_Trip_12":
			dialog.text = "Che diavolo?!";
			link.l1 = "Preparati a crepare, canaglia!";
			link.l1.go = "Santiago_Trip_13";
		break;
		
		case "Santiago_Trip_13":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "SantiagoTripExitFromRoom");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Santiago_Trip_14":
			dialog.text = "Che casino! Mi chiedevo da dove venisse tutto questo baccano. Complimenti – hai la testa sulle spalle, ragazzo!";
			link.l1 = "Più furbo di quanto sembri... Vediamo adesso cosa sai fare contro un avversario armato!";
			link.l1.go = "Santiago_Trip_15";
		break;
		
		case "Santiago_Trip_15":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "SantiagoTripExitHouse");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		//офицер-посланник по 5 заданию
		case "HollQuest_Officer":
			dialog.text = "Il signor Lucas Rodenburg desidera vederti immediatamente. Presentati subito da lui.";
			link.l1 = "Sto arrivando.";
			link.l1.go = "HollQuest_Officer_exit";			
		break;
		
		case "HollQuest_Officer_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
			pchar.questTemp.HWIC.Holl = "MerdokStart";
			AddQuestRecord("Holl_Gambit", "1-36");
		break;
		
//---------------------------------------------против всех----------------------------------------------
		//убрать испанского идальго
		case "Fernando":
			dialog.text = "Cosa vuoi da me?";
			link.l1 = "La tua testa!";
			link.l1.go = "Fernando_fight";
			link.l2 = "Niente, lascia stare.";
			link.l2.go = "exit";	
			NextDiag.TempNode = "Fernando_repeat";
		break;
		
		case "Fernando_repeat":
			dialog.text = "Sei ancora tu? Che diavolo vuoi da me?! Parla chiaro!";
			link.l1 = "La tua testa!";
			link.l1.go = "Fernando_fight";
			link.l2 = "Niente, lascia stare.";
			link.l2.go = "exit";	
			NextDiag.TempNode = "Fernando_repeat";		
		break;
		
		case "Fernando_fight":
			chrDisableReloadToLocation = true;//выходы закроем
			LAi_SetWarriorType(npchar);
            LAi_group_MoveCharacter(npchar, "SPAIN_CITIZENS");
			LAi_group_Attack(NPChar, Pchar);
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
			pchar.quest.HWIC_Fernando.win_condition.l1 = "NPC_Death";
			pchar.quest.HWIC_Fernando.win_condition.l1.character = "HWICFernando";
			pchar.quest.HWIC_Fernando.function = "Fernando_died";
		break;
		
		//в доме Флитвуда
		case "Fleetwood_soldier"://для любителей сунуть нос куда не надо
			if (CheckAttribute(npchar, "quest.talked"))
			{
			dialog.text = "Sei di nuovo tu? Che diavolo ci fai qui a ficcare il naso? Non mi piace affatto. Va bene, ti faccio arrestare e ti mando dal comandante per un bell’interrogatorio. Ragazzi, acchiappatelo!";
			link.l1 = "Ma volevo solo...";
			link.l1.go = "Fleetwood_soldier_4";	
			}
			else
			{
			dialog.text = "Chi sei tu e che diavolo vuoi? Spiegati!";
			link.l1 = "Perdonate, messere, temo d’aver bussato alla porta sbagliata. Chiedo venia.";
			link.l1.go = "Fleetwood_soldier_1";	
			link.l2 = "Vorrei parlare con Richard Fleetwood.";
			link.l2.go = "Fleetwood_soldier_2";		
			}
		break;
		
		case "Fleetwood_soldier_1":
			dialog.text = "Proprio così. Hai sbagliato persona, compare. Sii tanto gentile da levar le tende subito!";
			link.l1 = "Sì. Certo.";
			link.l1.go = "Fleetwood_soldier_3";			
		break;
		
		case "Fleetwood_soldier_2":
			dialog.text = "Davvero? E chi ti ha detto che abitava qui? Mi sembra sospetto... Va bene, ti arresto e ti spedisco dal comandante per l’interrogatorio. Ragazzi, acchiappate questo tizio!";
			link.l1 = "Ma volevo solo vedere Richard...";
			link.l1.go = "Fleetwood_soldier_4";	
		break;
		
		case "Fleetwood_soldier_3":
			DialogExit();
			npchar.quest.talked = "true";
			DoQuestReloadToLocation("SentJons_town", "reload", "houseSP3", "");
			pchar.quest.Fleetwood_Soldier.win_condition.l1 = "location";
			pchar.quest.Fleetwood_Soldier.win_condition.l1.location = "SentJons_houseSP3";
			pchar.quest.Fleetwood_Soldier.function = "Fleetwood_Soldier";//для настырных
		break;
		
		case "Fleetwood_soldier_4":
			DialogExit();
			GoToPrison("SentJons", 1000, 10);			
		break;
		
		case "Theft_soldier":
			dialog.text = "Ah! Ladri? Spie? Tieni ben saldo il cappello, adesso!";
			link.l1 = "Hop là!";
			link.l1.go = "Attack_Theft_soldier";			
		break;
		
		case "Attack_Theft_soldier":
			LAi_group_Delete("EnemyFight");
			LAi_SetHP(npchar, 500, 500);
			LAi_SetWarriorType(npchar);
            LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Attack_soldier":
			dialog.text = "Ah! Che ci fa costui qui? Ragazzi, qui abbiamo una spia! Alle armi!";
			link.l1 = "Hup!";
			link.l1.go = "Attack_soldier_fight";			
		break;
		
		case "Attack_soldier_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//снять запрет драки
			LAi_group_Delete("EnemyFight");
			for (i=1; i<=4; i++)
			{
			sld = characterFromId("Attack_sold_"+i);	
			LAi_SetWarriorType(sld);
            LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "PrepareToStreetFight");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		//Книппель-пленник в трюме
		case "Sailor_deck":
			chrDisableReloadToLocation = true;
			dialog.text = "Capitano, abbiamo interrogato questo furfante, come ci avete ordinato. Abbiamo dovuto scottarlo un poco... Aveva questa lettera addosso. Ha provato a mangiarsela, ma non gliel’abbiamo permesso. Proprio come sospettavamo, doveva prendere una ragazzina a Willemstad e portarla dal suo padrone.";
			link.l1 = "Una lettera? Fammi vedere... Poi ci parlerò io stesso.";
			link.l1.go = "Sailor_deck_1";			
		break;
		
		case "Sailor_deck_1":
			DialogExit();
			AddLandQuestMark(characterFromId("KnippelClone"), "questmarkmain");
			GiveItem2Character(pchar, "NPC_Letter");
			AddQuestRecordInfo("LetterToAbi", "1");
		break;
		
		case "Sailor_deck_2":
			dialog.text = "Quali sono i tuoi ordini, Capitano?";
			link.l1 = "Butta il cadavere in mare. E preparatevi a sbarcare!";
			link.l1.go = "Sailor_deck_3";			
			// belamour legendary edition -->
			link.l2 = "Sepellitelo in mare con tutti gli onori militari. Quel vecchio ha combattuto valorosamente fino all’ultimo respiro. Ha persino caricato e puntato quel cannone dopo che era stato rovesciato dal suo affusto. Un vero peccato. In un’altra vita, forse saremmo stati compagni d’arme...";
			link.l2.go = "Sailor_deck_3a";
		break;
		
		case "Sailor_deck_3a":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			dialog.text = "Sì, Capitano!";
			link.l1 = "...";
			link.l1.go = "Sailor_deck_4";			
		break;
		
		case "Sailor_deck_3":
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "Sneak", 120);
			AddCharacterExpToSkill(pchar, "FencingL", 30);
			AddCharacterExpToSkill(pchar, "FencingS", 30);
			AddCharacterExpToSkill(pchar, "FencingH", 30);
			AddCharacterExpToSkill(pchar, "Pistol", 30);
			// <-- legendary edition
			dialog.text = "Ai vostri ordini, Capitano!";
			link.l1 = "...";
			link.l1.go = "Sailor_deck_4";			
		break;
		
		case "Sailor_deck_4":
			DialogExit();
			chrDisableReloadToLocation = false;
			AddQuestRecord("Holl_Gambit", "3-21");
			LAi_SetActorType(pchar);
			sld = characterFromId("KnippelClone");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld.lifeday = 0;
			for (i=1; i<=3; i++)
			{
				sld = characterFromId("Sailor_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "ReturnMCPlayer", 3);
			}
			pchar.questTemp.HWIC.Self = "toVillemstad";
			sld = characterFromId("Solomon");
			sld.greeting = "solomon_2";
			AddLandQuestMark(sld, "questmarkmain");
			AddMapQuestMarkCity("Villemstad", false);
			LocatorReloadEnterDisable("Villemstad_town", "houseSP2", false);//откроем дом Аби
			LocatorReloadEnterDisable("Villemstad_houseSP2", "reload2", true);//закроем комнату Аби
		break;
		
		//Лонгвэй-пленник в трюме
		case "Sailor_deck_5":
			chrDisableReloadToLocation = true;
			dialog.text = "Abbiamo pronto il cinese per l’interrogatorio, proprio come avete ordinato, Capitano. Non aveva nulla addosso, nessun documento. Il braciere è acceso e stiamo arroventando manette e tenaglie proprio adesso.";
			link.l1 = "Ben fatto, Alonso. Ma prima che tu cominci, vorrei provare a ragionare con lui. Magari decide di collaborare spontaneamente?";
			link.l1.go = "Sailor_deck_6";			
		break;
		
		case "Sailor_deck_6":
			dialog.text = "Come dite, Capitano.";
			link.l1 = "...";
			link.l1.go = "exit";	
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
		break;
		
		case "Sailor_deck_7":
			dialog.text = "Sì, capitano?";
			link.l1 = "Mettetelo ai ferri e tenetelo d'occhio senza sosta finché non arriviamo a Guadalupa. Voi tre dovete restare sempre qui. La sua pelle vale la vostra, chiaro?";
			link.l1.go = "Sailor_deck_8";			
		break;
		
		case "Sailor_deck_8":
			dialog.text = "Ai vostri ordini, Capitano!";
			link.l1 = "";
			link.l1.go = "Sailor_deck_9";			
		break;
		
		case "Sailor_deck_9":
			chrDisableReloadToLocation = false;
			AddQuestRecord("Holl_Gambit", "3-48");
			sld = characterFromId("LongwayClone");
			LAi_SetActorType(sld);
			LAi_SetGroundSitType(sld);
			DialogExit();
			pchar.quest.Longway_Shore.win_condition.l1 = "location";
			pchar.quest.Longway_Shore.win_condition.l1.location = "Shore31";
			pchar.quest.Longway_Shore.function = "LongwayInShore";
			AddMapQuestMarkShore("Shore31", true);
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
		break;
		
		//пьяница - передача письма Флитвуду
		case "Drunkard":
			DelLandQuestMark(npchar);
			dialog.text = "Hic! Buonasera, signore! Che cosa desidera? Forse potrebbe offrire da bere a un vecchio ubriacone? E io...";
			link.l1 = "Ascolta, vecchio ubriacone... Sei tu Jack Harrison?";
			link.l1.go = "Drunkard_1";			
		break;
		
		case "Drunkard_1":
			dialog.text = "Oh! Sì, sono proprio io. E chi altri, se non io? Perché? Che co-o-sa fa-aremo con un ma-ri-nai-o u-bri-a-co-o-o...";
			link.l1 = "Oh mio Signore, dammi pazienza! Quale marinaio? Si legge in faccia che sei un novellino di terra... Vuoi mettere qualcosa in tasca?";
			link.l1.go = "Drunkard_2";			
		break;
		
		case "Drunkard_2":
			dialog.text = "Voglio sempre far soldi. Che devo fare? Però, non ammazzerò nessuno. E non ruberò nulla. E tu non sei proprio il mio genere.";
			link.l1 = "Non dovrai ammazzare nessuno, e dubito pure che tu ne sia capace: sei troppo maldestro, ragazzo. Ora ascolta. Prendi questa lettera e consegnala alla casa a sinistra della residenza del governatore. È per Richard Fleetwood.";
			link.l1.go = "Drunkard_3";			
		break;
		
		case "Drunkard_3":
			dialog.text = "Per Richard Fleetwood? No... Mi metterebbero in gattabuia appena mi vedono.";
			link.l1 = "Zitto e ascolta. Nessuno ti metterà in catene. Dirai che vieni da parte di Charlie Knippel per Abigail. Ti faranno entrare. Ripeti quello che ti ho detto.";
			link.l1.go = "Drunkard_4";			
		break;
		
		case "Drunkard_4":
			dialog.text = "Chi è Abigail? Conosco Knippel...";
			link.l1 = "Non sono affari tuoi. Meno sai, più a lungo camperai. Allora, sto aspettando. Ripeti.";
			link.l1.go = "Drunkard_5";			
		break;
		
		case "Drunkard_5":
			dialog.text = "Sono venuto da parte di Charlie Knippel riguardo a... ehm... Abigail. Già, proprio così.";
			link.l1 = "Ben fatto. Ti spetteranno 5000 pesos per questo lavoro.";
			link.l1.go = "Drunkard_6";			
		break;
		
		case "Drunkard_6":
			if (makeint(Pchar.money) >= 5000)
			{
				dialog.text = "5000 pesos? Oh.... Solo per consegnare una lettera?";
				link.l1 = "No. Ti verrà data un'altra lettera. Verrai con essa alla taverna e ti siederai proprio qui. Io la prenderò da te. Non fare sciocchezze e non aver paura – ti terrò d'occhio e sarò nei paraggi. Prendi questa somma come anticipo, così ti sentirai più a tuo agio.";
				link.l1.go = "Drunkard_7";	
			}
			else
			{
				dialog.text = "Cinquemila? Hai davvero tutto questo denaro addosso?";
				link.l1 = "Ah! Ma certo che ce l’ho. Te lo porto subito.";
				link.l1.go = "Drunkard_no_money";	
				NextDiag.CurrentNode = "Drunkard_no_money";
			}
		break;
		
		case "Drunkard_no_money":
			dialog.text = "Hai portato i cinquemila?";
			if (makeint(Pchar.money) >= 5000)
			{
				link.l1 = "Sì. Ecco qua. Non ti crucciare.";
				link.l1.go = "Drunkard_7";
			}
			else
			{
				link.l1 = "No. Aspetta. Tornerò presto.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Drunkard_no_money";
			}
		break;
		
		case "Drunkard_7":
			AddMoneyToCharacter(pchar, -5000);
			RemoveItems(PChar, "MC_Letter", 1);
			dialog.text = "Uhm... Dovrei andare adesso, signore?";
			link.l1 = "No, giovedì mattina... Ma certo che no, adesso, testa di rapa! Finisci il tuo rum e fila via!";
			link.l1.go = "Drunkard_8";			
		break;
		
		case "Drunkard_8":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-26");
			LAi_SetStayType(npchar);
			LAi_RemoveLoginTime(npchar);//удалить время загрузки
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, "sentjons_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "sentjons_town", "reload", "reload4_back", "DrunkardGoTown", -1);
			chrDisableReloadToLocation = true;//закрыть локацию
			LocatorReloadEnterDisable("SentJons_town", "reload1_back", true);
			LocatorReloadEnterDisable("SentJons_town", "reload2_back", true);
			LocatorReloadEnterDisable("SentJons_town", "gate_back", true);//чтобы не сбежал
		break;
		
		case "Drunkard_9":
			DelLandQuestMark(npchar);
			dialog.text = "Ah, eccovi qua, signore... Avrei fatto meglio a non farlo. Richard è andato su tutte le furie quando ha finito di leggere. Ho temuto che mi avrebbe fatto fuori.";
			link.l1 = "Ma eccoti qua! Non temere – non avrebbe mai osato fare una cosa simile – eri troppo prezioso per lui in quel momento, ah-ah! Non puoi nemmeno immaginare quanto...";
			link.l1.go = "Drunkard_10";			
		break;
		
		case "Drunkard_10":
			dialog.text = "Ho proprio bisogno di bere... Ecco la sua risposta per te.";
			link.l1 = "Dammelo! E tieni la bocca chiusa!";
			link.l1.go = "Drunkard_11";			
		break;
		
		case "Drunkard_11":
			GiveItem2Character(pchar, "MC_Letter");
			ChangeItemDescribe("MC_Letter", "itmdescr_MC_Letter1");
			AddQuestRecordInfo("FleetwoodAnswer", "1");
			dialog.text = "Sarà difficile per me parlare nei prossimi giorni... Addio... Spero di non rivederti mai più.";
			link.l1 = "Calmati, vecchio ubriacone, ah-ah-ah! Che facciamo con un marinaio ubriaco... Bevi e riposati – ormai è tutto finito!";
			link.l1.go = "Drunkard_12";			
		break;
		
		case "Drunkard_12":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Holl_Gambit", "3-27");
			pchar.questTemp.HWIC.Self = "FleetwoodAgree";
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
		break;
		
		//кэп курьерского судна
		case "Cureer_abordage":
			dialog.text = "Perché diavolo hai assaltato la mia nave? Non ho né ricchezze né denaro – solo carte, e quelle non ti servirebbero a nulla comunque!";
			link.l1 = "Zitto. Hai perso, adesso ascolterai me. Della tua nave e dei tuoi documenti non me ne faccio niente. Mi serve che tu porti questo messaggio al tuo lurido topo di padrone, Lucas Rodenburg. Digli che il capitano Fleetwood gli manda i suoi saluti.";
			link.l1.go = "Cureer_abordage_1";			
		break;
		
		case "Cureer_abordage_1":
			dialog.text = "Capitano Fleetwood? Ma...";
			link.l1 = "Vuoi consegnare questa lettera al tuo padrone, o preferisci che ti trafigga qui e ora? Posso sempre trovare qualcun altro per recapitare il messaggio. Tanto per saperlo: ogni fine settimana, solo per noia, derubo le navi della tua lurida Compagnia.";
			link.l1.go = "Cureer_abordage_2";			
		break;
		
		case "Cureer_abordage_2":
			dialog.text = "D'accordo, signor Fleetwood. Lo consegnerò io.";
			link.l1 = "Magnifico. Ora possiamo salutarci, Mynheer. Oggi ti è andata proprio di lusso. E ricordati di far visita a una chiesa appena sbarchi!";
			link.l1.go = "Cureer_abordage_3";			
		break;
		
		case "Cureer_abordage_3":
			DialogExit();
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			Lai_SetPlayerType(pchar);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetImmortal(sld, true);
			sld.ShipEnemyDisable  = true;
			pchar.quest.HWICCureer_AfterBattle.over = "yes";
			pchar.quest.HWICCureerOnMapOver.over = "yes";
			AddQuestRecord("Holl_Gambit", "3-39");
			Log_TestInfo("THE LETTER HAS BEEN DELIVERED!");
			RemoveItems(PChar, "MC_Letter", 1);
			pchar.questTemp.HWIC.Self = "LetterToLucasSent";
			pchar.quest.Curacao_exploring.win_condition.l1 = "location";
			pchar.quest.Curacao_exploring.win_condition.l1.location = "Curacao";
			pchar.quest.Curacao_exploring.function = "CuracaoExploring";
			DoQuestCheckDelay("LAi_ReloadBoarding", 1.0);
			AddComplexSeaExpToScill(50, 50, 50, 100, 50, 50, 0);
			AddComplexSelfExpToScill(30, 30, 30, 30);
			AddMapQuestMarkIsland("Curacao", true);
		break;
		
		//Матиас Бек в тюрьме
		case "MatiasBek"://на случай если геймер захочет пообщаться
			dialog.text = "Sono stato arrestato senza ragione! Io con gli inglesi non c'entro nulla! Tutte macchinazioni di Rodenburg, dannato sia lui. Ma poco importa. Peter Stuyvesant arriverà presto – lui rimetterà ogni cosa al suo posto!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "MatiasBek";
		break;
		
		//стражник у входа в резиденцию
		case "QuestGuard":
			dialog.text = "Il signor Lucas Rodenburg non desidera ricevere nessuno al momento. Siate così gentile da lasciare subito la residenza.";
			link.l1 = "Hmm. Capisco. Cercherò di passare fra una settimana...";
			link.l1.go = "exit";
			NextDiag.TempNode = "QuestGuard";		
		break;
		
		//Питер Стайвесант
		case "Stivesant":
			dialog.text = "Andiamo alla residenza, Capitano. Ho già mandato la mia gente al forte per raccogliere notizie su Matthias Beck. Se davvero fosse stato imprigionato, ormai l’avrebbero già rilasciato e scortato in città. Seguitemi!";
			link.l1 = "Sì, Mynheer Stuyvesant.";
			link.l1.go = "Stivesant_1";			
		break;
		
		case "Stivesant_1":
			DialogExit();
			AddLandQuestMark(npchar, "questmarkmain");
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "Villemstad_townhall", "goto", "goto2", "OpenVillemstadResidence", -1);
		break;
		
		case "ArestLucas_1":
			dialog.text = "Lucas! Che diavolo succede qui? Dov'è Matthias Beck? È vero che l'hai sbattuto in galera?";
			link.l1 = "";
			link.l1.go = "ArestLucas_2";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
		break;
		
		case "ArestLucas_2":
			StartInstantDialog("Lucas", "ArestLucas_3", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_3":
			dialog.text = "Salute, Mynheer Stuyvesant. Ho le prove del suo legame con l’intelligence britannica e direttamente col capitano Fleetwood. Ha passato parola a quel dannato inglese d’assaltare la nostra brigantina-corrispondenza per impadronirsi della posta riservata della Compagnia.";
			link.l1 = "";
			link.l1.go = "ArestLucas_4";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));
			LAi_ActorAnimation(npchar, "dialog_stay13", "1", 4.5);
		break;
		
		case "ArestLucas_4":
			StartInstantDialog("Stivesant", "ArestLucas_5", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_5":
			dialog.text = "Da dove hai tirato fuori questa soffiata?";
			link.l1 = "";
			link.l1.go = "ArestLucas_6";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
		break;
		
		case "ArestLucas_6":
			StartInstantDialog("Lucas", "ArestLucas_7", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_7":
			dialog.text = "It was claimed by the captain of the courier brigantine. Richard Fleetwood boarded his ship and took away his papers; then the ship was set free. Nobody except me, you and Matthias Beck had any information about either the route or the schedule.";
			link.l1 = "";
			link.l1.go = "ArestLucas_8";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));
		break;
		
		case "ArestLucas_8":
			StartInstantDialog("Stivesant", "ArestLucas_9", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_9":
			dialog.text = "And that's why you have decided that Beck tipped off Fleetwood to attack the brigantine? What rubbish! Fleetwood is an ordinary pirate; he only attacks merchant ships. Why would he need the papers, which, by the way, only contained bookkeeping information?";
			link.l1 = "";
			link.l1.go = "ArestLucas_10";		
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
		break;
		
		case "ArestLucas_10":
			StartInstantDialog("Lucas", "ArestLucas_11", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_11":
			dialog.text = "Mynheer, il corriere portava anche altri documenti importanti della Compagnia – non solo i soliti rapporti. Ora però tutto è finito nelle mani degli inglesi. Ecco perché ho deciso di mettere Beck agli arresti.";
			link.l1 = "";
			link.l1.go = "ArestLucas_12";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));			
		break;
		
		case "ArestLucas_12":
			StartInstantDialog("Stivesant", "ArestLucas_13", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_13":
			dialog.text = "Maledizione! Questa è una vera usurpazione del potere! Ti rendi conto davvero di ciò che stai facendo, Lucas? Dov'è il capitano della brigantina corriera?";
			link.l1 = "";
			link.l1.go = "ArestLucas_14";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
			LAi_ActorAnimation(npchar, "dialog_stay13", "1", 4.5);
		break;
		
		case "ArestLucas_14":
			StartInstantDialog("Lucas", "ArestLucas_15", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_15":
			dialog.text = "È andato a Philipsburg, signor mio.";
			link.l1 = "";
			link.l1.go = "ArestLucas_16";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));	
		break;
		
		case "ArestLucas_16":
			StartInstantDialog("Stivesant", "ArestLucas_17", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_17":
			dialog.text = "Va bene, allora. Ho ordinato di liberare Beck. Lo porteranno qui e poi noi tre ci faremo una chiacchierata.";
			link.l1 = "";
			link.l1.go = "ArestLucas_18";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
		break;
		
		case "ArestLucas_18":
			StartInstantDialog("Lucas", "ArestLucas_19", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_19":
			dialog.text = "D'accordo, non mi dispiace. In tre va bene. Parliamone.";
			link.l1 = "";
			link.l1.go = "ArestLucas_20";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));	
		break;
		
		case "ArestLucas_20":
			DialogExit();
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			ChangeCharacterAddressGroup(sld, "Villemstad_townhall", "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "governor1", "DoubleTalkWithLucas", -1.0);
			locCameraFromToPos(4.70, 2.92, -4.19, false, 3.60, -0.70, 5.00);
			DoQuestCheckDelay("PiterTalkWithLucas_2", 4.5);
		break;
		
		case "ArestLucas_40":
			dialog.text = "Pagherai per la tua prepotenza, Rodenburg! Le tue accuse sono fandonie. Non mi hai nemmeno lasciato vedere il capitano della brigantina! Non hai portato alcuna prova, tutte le accuse sono solo tue parole.\nGiuro davanti a Dio, sono innocente! Non ho mai avuto, né ho ora, alcun legame coi maledetti inglesi!";
			link.l1 = "";
			link.l1.go = "ArestLucas_41";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
		break;
		
		case "ArestLucas_41":
			StartInstantDialog("Lucas", "ArestLucas_42", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_42":
			dialog.text = "Davvero? E allora come mai Fleetwood ha scoperto del nostro brigantino e che a bordo c’erano non solo le solite carte, eh?";
			link.l1 = "";
			link.l1.go = "ArestLucas_43";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Villemstad_Mayor"));
		break;
		
		case "ArestLucas_43":
			dialog.text = "...";
			link.l1 = "Rodenburg mente. Richard Fleetwood non avrebbe mai attaccato la brigantina del corriere.";
			link.l1.go = "ArestLucas_44";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
			sld = characterFromId("Stivesant");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			sld = characterFromId("Villemstad_Mayor");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
		break;
		
		case "ArestLucas_44":
			dialog.text = "E voi chi siete mai, signor mio? Da dove vi viene l’ardire di proferir simili parole?";
			link.l1 = "Il mio nome è "+GetFullName(pchar)+"Ho fatto fuori personalmente il capitano Fleetwood attirandolo in una trappola. Ora il suo cadavere lo stanno divorando i gabbiani sulle spiagge di Turks. I funzionari non sono stati capaci di difenderci, noi mercanti olandesi, dalla sua prepotenza, così ci ho pensato io. E tutto questo è successo prima che il brigantino-correio venisse saccheggiato...";
			link.l1.go = "ArestLucas_46";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "ArestLucas_46":
			dialog.text = "";
			link.l1 = "Fleetwood non poteva certo averlo fatto, era già morto. Ho saputo dagli abitanti della taverna che Mathias Beck è stato arrestato, così ho deciso di ficcare il naso nella faccenda, perché ho sempre creduto che il signor Beck fosse uomo d’onore specchiato...";
			link.l1.go = "ArestLucas_47";			
		break;
		
		case "ArestLucas_47":
			dialog.text = "";
			link.l1 = "La gente al porto mi ha detto che hai caricato il tuo sciabecco di ogni sorta di canaglia e mercenario, lasciando a terra le guardie della Compagnia. Ho seguito la tua nave e l’ho catturata, facendo fuori ogni mascalzone che avevi arruolato. Ho interrogato il capitano Longway, e in cambio della sua libertà mi ha raccontato tutto, signor Rodenburg...";
			link.l1.go = "ArestLucas_48";			
		break;
		
		case "ArestLucas_48":
			dialog.text = "";
			link.l1 = "Stavi pianificando di prendere il potere su Curaçao e hai ordinato a Longway di affondare il galeone del signor Stuyvesant. Conoscendo i tuoi metodi, sono certo che il povero capitano della brigantina sia già all'altro mondo. Avrai senz'altro organizzato l'assalto alla nave corriera per creare un precedente, vero? E questa faccenda è stata condotta dal tuo sicario, quel tale Jacob van Berg? Longway mi ha raccontato parecchio su quell'uomo.";
			link.l1.go = "ArestLucas_49";			
		break;
		
		case "ArestLucas_49":
			dialog.text = "Questa... questa è una menzogna sfacciata! Di che diavolo stai parlando, signore? Chi diamine sei tu?";
			link.l1 = "Sono un capitano indipendente venuto a ripulire mare e terra da quel furfante di Fleetwood, e che s’è trovato immischiato nelle vostre trame politiche! Ho messo in guardia il signor Stuyvesant dal pericolo che lo minacciava. E ora sono qui per porre fine alle vostre razzie su Curaçao – insieme alle autorità legittime!";
			link.l1.go = "ArestLucas_50";			
		break;
		
		case "ArestLucas_50":
			dialog.text = "Che insolenza! Dovrai rispondere delle tue parole, signor 'capitano indipendente'! Tu...";
			link.l1 = "";
			link.l1.go = "ArestLucas_51";
		break;
		
		case "ArestLucas_51":
			StartInstantDialog("Stivesant", "ArestLucas_52", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_52":
			dialog.text = "Basta così, Lucas. Pagherai per i tuoi misfatti! Ho sentito e visto abbastanza. Lucas Rodenburg, ti arresto per aver attentato alla vita del direttore della Compagnia, per aver tentato di prendere il potere con la forza e per il sospetto d’aver fatto fuori il capitano della nave corriera. \nE poi, sono certo che scopriremo ancora di più su certi capitoli piccanti della tua vita durante l’inchiesta ufficiale. Ti metteremo ai ferri e ti sbatteremo su una nave per Amsterdam, dove ti processeranno. Portatelo via!";
			link.l1 = "";
			link.l1.go = "ArestLucas_53";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
			sld = characterFromId("Lucas");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromID("Stivesant"));					
		break;
		
		case "ArestLucas_53":
			StartInstantDialog("Lucas", "ArestLucas_54", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_54":
			dialog.text = "Ma...";
			link.l1 = "";
			link.l1.go = "ArestLucas_55";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));			
		break;
		
		case "ArestLucas_55":
			DialogExit();
			LAi_ActorTurnToCharacter(pchar, characterFromID("Lucas"));
			sld = characterFromId("Lucas");
			LAi_SetImmortal(sld, true);//защита от хитреца
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Villemstad_townhall", "goto", "goto6");
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "LucasGoToPrison", -1);
			for (i=3; i<=5; i++)
			{
			sld = characterFromId("StivesantGuard_"+i);
			LAi_ActorFollow(sld, characterFromID("Lucas"), "", -1);
			}
			LAi_SetActorType(PChar);
			locCameraFromToPos(4.70, 2.92, -4.19, false, -4.60, -1.70, 5.50);
			DoQuestFunctionDelay("SecondDayInVillemstad", 6.0);
		break;
		
		case "Stivesant_10":
			dialog.text = "Capitano "+GetFullName(pchar)+" ! A nome dell'amministrazione della colonia di Willemstad, vi prego di accettare la nostra più sincera gratitudine per le vostre azioni, che ci hanno permesso di mettere quel pericoloso criminale dietro le sbarre. Vorrei anche ringraziarvi di persona, poiché probabilmente vi devo la vita.";
			link.l1 = "Ho agito per il bene di tutte le colonie olandesi, Mynheer.";
			link.l1.go = "Stivesant_11";			
		break;
		
		case "Stivesant_11":
			dialog.text = "La tua modestia merita rispetto, amico mio. Ora vorrei sistemare alcune formalità: poiché hai catturato la Meifeng solo per nobili scopi e in circostanze disperate, non ci saranno pretese. Tuttavia questa nave appartiene alla Compagnia e ti chiedo cortesemente di restituirla.";
			link.l1 = "Certamente, signor mio.";
			link.l1.go = "Stivesant_12";			
		break;
		
		case "Stivesant_12":
		//удаляем Мейфенг
		DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//удаляем атрибут квестового корабля
		if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_MAYFANG)
		{
			pchar.Ship.Type = GenerateShipExt(SHIP_TARTANE, true, pchar);
			pchar.Ship.name = "A boat";
			SetBaseShipData(pchar);
			SetCrewQuantityOverMax(PChar, 0);//сажаем на тартану
		}
		else
		{
			for(i = 1; i < COMPANION_MAX; i++)
			{
			int iTemp = GetCompanionIndex(PChar, i);
			if(iTemp > 0)
				{
				sld = GetCharacter(iTemp);
				if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
					{
						pchar.questTemp.HWIC.Self.CompanionIndex = sld.Index;
						sld = GetCharacter(sti(pchar.questTemp.HWIC.Self.CompanionIndex));
						RemoveCharacterCompanion(PChar, sld);
						AddPassenger(PChar, sld, false);
					}
				}
			}
		}
			dialog.text = "Ti prego di recarti domani alla mia residenza: sarai ricompensato, a nome della Repubblica delle Province Libere, per le tue azioni a suo beneficio. Ti chiedo cortesemente di non lasciare la città.";
			link.l1 = "Va bene, Mijnheer. Passerò domani.";
			link.l1.go = "Stivesant_13";			
		break;
		
		case "Stivesant_13":
			DialogExit();
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			sld.dialog.currentnode = "Bek_2";
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "Bek_2":
			dialog.text = "Vorrei anche ringraziarti di persona, Capitano, per il tuo spirito d’iniziativa e l’aiuto dato al momento giusto. Non dimenticare di tornare qui domani: avrò pronto un dono di gran valore per te.";
			link.l1 = "Grazie, Mynheer Beck. Ci sarò!";
			link.l1.go = "Bek_3";			
		break;
		
		case "Bek_3":
			DialogExit();
			pchar.quest.Award_FromPiter.win_condition.l1 = "Timer";
			pchar.quest.Award_FromPiter.win_condition.l1.date.hour  = 9.0;
			pchar.quest.Award_FromPiter.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Award_FromPiter.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Award_FromPiter.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Award_FromPiter.function = "OpenResidenceDoor";
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Villemstad_town", "reload5_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload10_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload3_back", true);//закрыть вход в резиденцию
			LocatorReloadEnterDisable("Villemstad_town", "reloadR2", true);//закрыть боковой вход в резиденцию
			AddQuestRecord("Holl_Gambit", "3-53");
			DoQuestReloadToLocation("Villemstad_prison", "goto", "goto23", "TalkWithLucasPrisoner");
			for (i=4; i<=5; i++)
			{
				sld = characterFromId("StivesantGuard_"+i);
				sld.lifeday = 0;//подчистим солдат
			}
		break;
		
		case "Stivesant_14":
			dialog.text = ""+GetFullName(pchar)+", a nome della Repubblica delle Province Libere, vi viene qui conferita un’arma personale e la somma di 100.000 pesos per l’iniziativa mostrata nell’eliminazione del nemico di tutti gli olandesi, il criminale di stato Richard Fleetwood. Le nostre congratulazioni!";
			link.l1 = "Grazie, signor Styuvesant!";
			link.l1.go = "Stivesant_15";			
		break;
		
		case "Stivesant_15":
			dialog.text = "Inoltre, per il coraggio senza pari dimostrato nello smascherare una cospirazione traditrice all’interno della Compagnia e per l’ardita impresa di catturare l’ex vicepresidente, ti vengono assegnati 150.000 pesos. Avrai anche il privilegio di firmare contratti con la Compagnia Olandese delle Indie Occidentali.\nSono certo che il nostro nuovo vice-direttore saprà trovare un incarico ben remunerato per un capitano tanto valoroso come te.";
			link.l1 = "Grazie! Terrò bene a mente.";
			link.l1.go = "Stivesant_16";			
		break;
		
		case "Stivesant_16":
			AddMoneyToCharacter(pchar, 250000);
			GiveItem2Character(pchar, GetGeneratedItem("blade_16")); // belamour legendary edition используем GetGeneratedItem иначе пачка одинаковых клинков из первой части массива
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			dialog.text = "Sappi che potrai sempre contare sul mio aiuto finché agirai dalla parte e nell’interesse dell’Olanda. Ora vediamo cosa ha da raccontarci il governatore di Willemstad, Matthias Beck.";
			link.l1 = "";
			link.l1.go = "Stivesant_17";			
		break;
		
		case "Stivesant_17":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			LAi_SetActorType(sld);
			sld.dialog.currentnode = "Bek_4";
			LAi_ActorDialog(sld, pchar, "", -1, 0);		
		break;
		
		case "Bek_4":
			dialog.text = "Le porgo la mia più sincera gratitudine, Capitano, per il suo coraggio e l’astuzia nel sventare un complotto contro la Corona. Vorrei offrirle questo prezioso strumento di navigazione, un tesoro impareggiabile per ogni uomo di mare.";
			link.l1 = "Grazie, signor Beck";
			link.l1.go = "Bek_5";			
		break;
		
		case "Bek_5":
			GiveItem2Character(pchar, "bussol");
			dialog.text = "Vorrei che tu sapessi: ormai ti considero un amico, e questo conta molto per me. Sarai sempre il benvenuto nella mia dimora. Passa quando vuoi e per qualsiasi motivo – sarò lieto di offrirti tutto l’aiuto che ti occorre.";
			link.l1 = "Mi fa piacere sentirlo, signor mio!";
			link.l1.go = "Bek_6";			
		break;
		
		case "Bek_6"://наведем порядок в городе
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-54");
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			LAi_SetHuberStayType(sld);
			sld.Dialog.Filename = "Common_Mayor.c";//patch-8
			sld.dialog.currentnode = "First time";
			sld.quest.meeting = "1";
			for (i=1; i<=3; i++)
			{
				sld = characterFromId("StivesantGuard_"+i);
				sld.lifeday = 0;//подчистим солдат
			}
			sld = characterFromId("Stivesant");
			LAi_ActorGoToLocator(sld, "goto", "goto6", "StivesantSitDown", -1);
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Villemstad_town", "reload1_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload2_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "gate_back", false);
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			DelMapQuestMarkCity("Villemstad");
		break;
		
		case "Bek_7":
			dialog.text = "L’Olanda è fiera di voi, Mynheer. Capitani come voi sono la spina dorsale della nostra flotta nei Caraibi. Ecco qua, accettate la vostra ricompensa.";
			link.l1 = "Grazie, signor mio. È un onore servire l’Olanda!";
			link.l1.go = "Bek_8";
		break;
		
		case "Bek_8":
			TakeNItems(pchar, "gold_dublon", 1000);
			ChangeCharacterComplexReputation(pchar,"authority", 5);
			ChangeCharacterNationReputation(pchar, HOLLAND, 20);
			DialogExit();
			sld = characterFromId("Lucas");
			LAi_SetActorType(sld);
			sld.dialog.currentnode = "LucasAward_2";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Stivesant_18":
			dialog.text = "Son lieto di vederti. Come va?";
			link.l1 = "Sto bene. Sono passato solo per farti visita.";
			link.l1.go = "exit";	
			NextDiag.TempNode = "Stivesant_18";
		break;
		
		// Jason НСО
		case "Stivesant_19":
			if (ChangeCharacterHunterScore(pchar, "holhunter", 0) > 10)
			{
				dialog.text = "Guarda chi si vede! È "+GetFullName(pchar)+"Abbiamo recentemente mandato i nostri segugi a darti la caccia per portarti qui. E quel favore ci è costato un bel gruzzolo.";
				link.l1 = "Uhm... Dovrei andarmene...";
				link.l1.go = "arest";
				break;
			}
			// belamour legendary edition фикс проверки мундира с мушкетом
			if (pchar.questTemp.Patria == "epizode_4" && IsUniformEquip())
			{
				dialog.text = "Sei forse un capitano della Marina Francese? Bene, ho poco tempo, ma ti darò ascolto. Cosa ti porta da queste parti?";
				link.l1 = "Mynheer Stuyvesant, sono giunto da Saint Christopher con un messaggio dal Governatore Generale delle colonie francesi, il Chevalier de Poincy.";
				link.l1.go = "Stivesant_20";
			}
			else
			{
				dialog.text = "Perdona, Capitano, ma al momento ho le mani troppo piene per occuparmi di te. Parla con il signor Mathias Beck, sarà lui a darti ascolto.";
				link.l1 = "Hmm...";
				link.l1.go = "Stivesant_19_1";
			}
		break;
		
		case "Stivesant_19_1":
			DialogExit();
			npchar.dialog.currentnode = "Stivesant_19";
		break;
		
		case "Stivesant_20":
			sld = characterFromId("Patria_FlautCap");
			dialog.text = "Dal Cavaliere de Poincy? Non mi aspettavo davvero che bastasse così poco... ehm... come se la passa il Cavaliere?";
			link.l1 = "Tutto va bene, signor mio. Monsieur de Poincy m’ha ordinato di consegnarvi questa lettera. L’altro mio incarico era di scortar... "+sld.ship.name+"‘ con il carico per la vostra Compagnia al porto di Willemstad. La nave è ormeggiata al molo e la merce non ha subito danni.";
			link.l1.go = "Stivesant_21";
		break;
		
		case "Stivesant_21":
			dialog.text = "Una flotta che trasporta merci per la nostra Compagnia? Interessante... E la lettera, capitano?";
			link.l1 = "Ecco. Prego, prendilo.";
			link.l1.go = "Stivesant_22";
		break;
		
		case "Stivesant_22":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "Hmmm... (leggendo). Un'ispezione dal regno madre... Ehmm... Eh, beh... questo è curioso, he-he... A proposito, Capitano, ho sentito dire che la Francia è in guerra con la Spagna nei Caraibi? L'assedio e il saccheggio del forte di San Jose, la distruzione della squadra spagnola al largo della costa orientale di Cuba...";
			link.l1 = "Sulla costa occidentale di Hispaniola, vicino a Port-au-Prince, signore mio. E l’unico scopo dell’assedio di San Jose era strappare agli spagnoli un risarcimento per il loro attacco a Saint-Pierre. I rapporti con la Spagna sono burrascosi da tempo... Quando dovrei tornare per la risposta?";
			link.l1.go = "Stivesant_23";
		break;
		
		case "Stivesant_23":
			dialog.text = "Non ti trattengo oltre, Capitano, sei uomo d’arme e avrai certo mille faccende da sbrigare, e sono sicuro che il Cavaliere starà già fremendo per il tuo ritorno. Sii così cortese da attendere proprio qui, nel salotto, per un paio d’ore mentre preparo la risposta a quella lettera. Siediti e riposati, ti porteranno del vino o del rum, se ti aggrada...";
			link.l1 = "La mia gratitudine, signor mio, ma preferirei un bicchiere di buon vino...";
			link.l1.go = "Stivesant_24";
		break;
		
		case "Stivesant_24":
			chrDisableReloadToLocation = true;//закрыть локацию
			pchar.quest.Patria_CureerTimeOver.over = "yes"; //снять таймер
			pchar.quest.Patria_CureerFail.over = "yes"; //снять прерывание
			sld = characterFromId("Patria_FlautCap");
			RemoveCharacterCompanion(pchar, sld);
			sld.lifeday = 0;
			DialogExit();
			npchar.dialog.currentnode = "Stivesant_25";
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, "Villemstad_townhall", "goto", "goto6");
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "Patria_StivesantWait", -1);
			pchar.questTemp.Patria = "epizode_4_return";
		break;
		
		case "Stivesant_25":
			GiveItem2Character(pchar, "Reserve_item_01");
			ChangeItemDescribe("Reserve_item_01", "itmdescr_Reserve_item_01_2");
			dialog.text = "La risposta per monsieur de Poincy è pronta. Ecco, prego, prendetela... Buona fortuna, Capitano.";
			link.l1 = "Grazie, signor mio. Addio!";
			link.l1.go = "Stivesant_26";
		break;
		
		case "Stivesant_26":
			DialogExit();
			npchar.dialog.currentnode = "Stivesant_19";
			chrDisableReloadToLocation = false;
			AddQuestRecord("Patria", "23");
			SetFunctionTimerCondition("Patria_CureerBackOver", 0, 0, 31, false);
		break;
		
		case "Stivesant_27":
			if (ChangeCharacterHunterScore(pchar, "holhunter", 0) > 10)
			{
				dialog.text = "Guarda un po’ chi si vede! È "+GetFullName(pchar)+" . Abbiamo recentemente mandato i nostri segugi a trascinarti qui. E quel servizio ci è costato un occhio della testa.";
				link.l1 = "Uhm... Dovrei andarmene...";
				link.l1.go = "arest";
				break;
			}
			if (pchar.questTemp.Patria == "epizode_6" && IsUniformEquip())
			{
				dialog.text = "Sei tornato di nuovo con un messaggio dal Governatore Generale Philippe de Poincy, vero?";
				link.l1 = "Sì, Mynheer Stuyvesant. Sulle rive di Sint Maarten c'è stato un malinteso spiacevole: una nave che trasportava l'ispettore da Parigi, il Barone Noel Forget, è stata colpita dai cannoni del forte di Philipsburg, e...";
				link.l1.go = "Stivesant_28";
			}
			else
			{
				dialog.text = "Perdonami, Capitano, ma in questo momento sono estremamente indaffarato e non posso dedicarti il tempo che meriti. Parla con mynheer Mathias Beck, fagli sentire ciò che hai da dire.";
				link.l1 = "Hmm...";
				link.l1.go = "Stivesant_27_1";
			}
		break;
		
		case "Stivesant_27_1":
			DialogExit();
			npchar.dialog.currentnode = "Stivesant_27";
		break;
		
		case "Stivesant_28":
			if (pchar.questTemp.HWIC.Detector == "holl_win" || pchar.questTemp.HWIC.Detector == "self_win")
			{
				dialog.text = "Ecco perché siete qui, Capitano. Non intendo perdermi in chiacchiere diplomatiche: dite allo Chevalier che non comanda più a Sint Maarten. Ne abbiamo abbastanza di lui. Quanto all’ispezione dalla madrepatria – che si ingegni, a de Poincy non è mai mancata la fantasia per rivoltare tutto come un calzino.";
				link.l1 = "È proprio questo che dovrei riferirgli?";
				link.l1.go = "Stivesant_29";
			}
			else
			{
				dialog.text = "Ecco perché vi trovate qui, Capitano. Non mi perderò in chiacchiere diplomatiche: il vostro signore s’è fatto troppo avido a Sint Maarten ultimamente, e ora bisogna raffreddare un po’ la sua fame insaziabile. Credo che lui lo capisca benissimo. Quanto a voi, Capitano Charles de Maure, abbiamo delle domande su certi recenti avvenimenti legati al bandito inglese di nome Richard Fleetwood, quindi vi toccherà restare qui per un po’.\nSergente! Prendi le armi del capitano e conducilo all’ufficio del comandante!";
				link.l1 = "Ritardare un ufficiale francese in servizio è intollerabile!";
				link.l1.go = "Stivesant_31";
			}
		break;
		
		case "Stivesant_29":
			dialog.text = "Non avrei potuto dirlo meglio io stesso, Capitano. Il vostro comandante capirà tutto, ma non serve che vi impicciate oltre, tanto non cambierà nulla. Vi auguro ogni fortuna. Sergente, accompagni monsieur Charles de Maure all’uscita!";
			link.l1 = "...";
			link.l1.go = "Stivesant_30";
		break;
		
		case "Stivesant_30":
			DialogExit();
			DoQuestReloadToLocation("Villemstad_town", "reload", "reload3", "Patria_DiplomatGetOut");
		break;
		
		case "Stivesant_31":
			dialog.text = "Purtroppo, la penso diversamente. Sergente! Se oppone resistenza, usate la forza!";
			link.l1 = "Non hai ancora idea di con chi hai a che fare, Mynheer ...";
			link.l1.go = "Stivesant_32";
		break;
		
		case "Stivesant_32":
			DialogExit();
			Patria_DiplomatFight();
		break;
		
		case "Stivesant_33":
			dialog.text = "È un tantino strano vederti in questa veste, Capitano Charles de Maure... Spero tu possa garantire l’immunità a chi viene da te per trattare...";
			link.l1 = "Di questo potete star certo, signor Stuyvesant.";
			link.l1.go = "Stivesant_34";
		break;
		
		case "Stivesant_34":
			dialog.text = "Dunque, mi concederesti di leggere l'accordo che hai preparato? Se ho ben capito, contiene il testo della lettera?";
			link.l1 = "Esattamente, signor mio, ma solo in forma ufficiale. Da parte della Francia — ripristino delle relazioni neutrali, rinuncia a qualsiasi pretesa sull'isola di Sint Maarten. Dall'Inghilterra — fine della guerra commerciale. Tutti i dettagli sono scritti qui dentro... E, ovviamente, compensazione pecuniaria per i danni che abbiamo subito a causa delle vostre azioni militari.";
			link.l1.go = "Stivesant_35";
		break;
		
		case "Stivesant_35":
			dialog.text = "Fate la gentilezza e consegnatemi il documento.";
			link.l1 = "Ma certo.";
			link.l1.go = "Stivesant_36";
		break;
		
		case "Stivesant_36":
			dialog.text = "...(leggendo)...";
			link.l1 = "...";
			link.l1.go = "Stivesant_37";
		break;
		
		case "Stivesant_37":
			LAi_Fade("", "");
			dialog.text = "Dal momento che non mi hai lasciato altra scelta, firmerò questo accordo. Ma per me la sicurezza di Willemstad e dei suoi abitanti viene prima di tutto.";
			link.l1 = "Allora autenticheremo tutte e tre le copie con le firme. Sono autorizzato dal Governatore Generale Philippe de Poincy a siglare il documento per la parte francese, il colonnello Doily lo firmerà per l’Inghilterra.";
			link.l1.go = "Stivesant_38";
		break;
		
		case "Stivesant_38":
			dialog.text = "...(firmando)...";
			link.l1 = "Perfetto! Ora dovremmo mettere la firma su questo...";
			link.l1.go = "Stivesant_39";
		break;
		
		case "Stivesant_39":
			LAi_Fade("", "");
			dialog.text = "Dunque, credo che ora toglierai l’assedio, vero?";
			link.l1 = "Senza dubbio. Mi auguro che tutte le condizioni dell’accordo vengano rispettate dagli olandesi senza alcuna infrazione.";
			link.l1.go = "Stivesant_40";
		break;
		
		case "Stivesant_40":
			dialog.text = "Se Inghilterra o Francia non infrangono gli accordi, allora rispetteremo il contratto, state tranquillo.";
			link.l1 = "È sempre meglio commerciare che menar le mani, Mynheer Stuyvesant. Ora potete far vela per Willemstad senza timore. L’assedio sarà tolto e il nostro squadrone farà presto rotta lontano dalle acque di Curaçao.";
			link.l1.go = "Stivesant_41";
		break;
		
		case "Stivesant_41":
			DialogExit(); // Стайвесант уходит, подходит д'Ойли
			Patria_CuracaoStivesantGo();
		break;
		
		case "Stivesant_42":
			dialog.text = "Dunque, siete voi il Barone Noel Forget? Ah, allora dovete essere proprio Monsieur Charles de Maure! Salute a voi, Vice Ammiraglio! Non per niente vi chiamano il più astuto cospiratore dell’arcipelago – nessuno può mai sapere da che parte state, eh...";
			link.l1 = "Al momento il Vice Ammiraglio sta dalla parte del Re e, per estensione, anche dalla tua, messere rappresentante.";
			link.l1.go = "Stivesant_43";
		break;
		
		case "Stivesant_43":
			dialog.text = "Il Re è lontano da queste acque, e la Francia pure, Barone, ma Saint Christophe e il Cavaliere de Poincy sono vicini. È lui il vero padrone delle colonie francesi. Di fatto... Ma ditemi, siete qui per trovare qualcosa che possa screditare de Poincy agli occhi del ministro delle finanze?";
			link.l1 = "Precisamente, signor mio.";
			link.l1.go = "Stivesant_44";
		break;
		
		case "Stivesant_44":
			dialog.text = "Possiedo tali documenti. Qui c’è un intero registro con i miei conti e quelli di de Poincy per la miniera e altre faccende. Inoltre, troverai un mucchio di carte collegate a questa storia, ognuna col sigillo personale di Philippe de Poincy. Ti assicuro che il contenuto di queste carte, se finisse nelle mani giuste, farebbe affondare il Cavaliere più a fondo del fondo del Mar dei Caraibi.";
			link.l1 = "Cosa vuoi in cambio di questo registro?";
			link.l1.go = "Stivesant_45";
		break;
		
		case "Stivesant_45":
			dialog.text = "La vendo per quattro soldi. Solo un milione di pesos d’argento.";
			link.l1 = "Un milione di pesos?!!";
			link.l1.go = "Stivesant_46";
		break;
		
		case "Stivesant_46":
			dialog.text = "Esatto, Barone. Questa somma coprirà almeno in parte le perdite causate dalla recente guerra. Permettetemi un consiglio: rivolgetevi a Monsieur Charles de Maure. Durante il suo servizio per de Poincy e... ehm, altri gentiluomini, avrà sicuramente accumulato una fortuna considerevole, e mettere insieme un milione non sarà certo un problema per lui. Ne sono quasi certo.\nVi concedo un mese di tempo. Se allo scadere non porterete la cifra richiesta, spedirò una lettera al Cavaliere dove racconterò in dettaglio la vostra visita. Potete immaginare il seguito.";
			link.l1 = "Mi stai ricattando! Devi capire che qui nelle colonie non potrei mai avere un milione!";
			link.l1.go = "Stivesant_47";
		break;
		
		case "Stivesant_47":
			dialog.text = "Ma certo che capisco. Proprio per questo ti ho subito indicato chi possiede quel milione. Se monsieur de Maure si rifiuta, ti conviene, barone, levare l’ancora per l’Europa prima che il Cavaliere riceva la mia lettera, altrimenti rischi di marcire qui per sempre. Quanto a monsieur de Maure... certo, perderà il suo rango d’ammiraglio, ma se la caverà... e magari farà pure fuori de Poincy coi suoi metodi, il che a me va più che bene. \nEbbene, signori, avete sentito. Vi aspetto con il milione fra un mese alla mia residenza. Entrata e uscita libere, parola mia.";
			link.l1 = "...";
			link.l1.go = "Stivesant_48";
		break;
		
		case "Stivesant_48":
			DialogExit();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			locCameraTarget(pchar);
			locCameraFollow();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = true;
			bDisableCharacterMenu = false;
			sld = CharacterFromID("Noel");
			sld.dialog.currentnode = "noel_84";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
			sld = CharacterFromID("Stivesant");
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "Patria_CondotierStivesantInHall", 12.0);
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("Stivesant_sold_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
			}
		break;
		
		case "Stivesant_49":
			if (sti(pchar.money) >= 1000000)
			{
				dialog.text = "Non ne avevo dubbi, Vice Ammiraglio Charles de Maure, che mi avresti portato questi soldi. Forse, ti ho persino chiesto troppo poco, ma tant’è… Il Barone è solo una pedina nella tua prossima partita, vero? Il grado e il denaro non ti bastano più, ora punti a scalzare de Poincy, dico bene? Ammettilo, un milione è una cifra da nulla per diventare Governatore Generale delle colonie francesi! Quei soldi li rifarai in pochi mesi, con la tua presa di ferro.";
				link.l1 = "Prendi il tuo milione, Mynheer. Ora vorrei ricevere il registro che mi hai promesso.";
				link.l1.go = "Stivesant_50";
			}
			else
			{
				dialog.text = "Faresti meglio a concentrarti su come mettere insieme quel milione, Monsieur, invece di sprecare il tempo in visite inutili.";
				link.l1 = "...";
				link.l1.go = "Stivesant_49_1";
			}
		break;
		
		case "Stivesant_49_1":
			DialogExit();
			npchar.dialog.currentnode = "Stivesant_49";
		break;
		
		case "Stivesant_50":
			pchar.quest.Patria_CondotierStivesantTimeOver.over = "yes"; // снять таймер
			AddMoneyToCharacter(pchar, -1000000);
			GiveItem2Character(pchar, "Reserve_item_01");
			ref itm = ItemsFromID("Reserve_item_01");
			itm.picIndex = 15;
			itm.picTexture = "ITEMS_26";
			itm.price = 0;
			itm.Weight = 2.0;
			itm.name = "itmname_Reserve_item_01_1";
			ChangeItemDescribe("Reserve_item_01", "itmdescr_Reserve_item_01_4");
			dialog.text = "Ma certo, Vice Ammiraglio. E non faccia quella faccia: quando sarà Lei il Governatore Generale, vedrà che la Compagnia Olandese delle Indie Occidentali è un socio d’affari assai più redditizio di quei britannici avidi e sempre pronti alla guerra. Non sa che, se dai un dito a un inglese, ti mangia il braccio intero? Se non lo sa, lo scoprirà presto sulla propria pelle. Dunque, non le dico certo addio. Tenga pure i suoi documenti. Mi auguro solo che il Suo barone sia abbastanza sveglio da battere lo Chevalier.";
			link.l1 = "Vi ringrazio. Addio, signor Stuvesant.";
			link.l1.go = "Stivesant_51";
		break;
		
		case "Stivesant_51":
			DialogExit();
			AddQuestRecord("Patria", "84");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", -1);
			pchar.quest.Patria_CondotierCabin.win_condition.l1 = "location";
			pchar.quest.Patria_CondotierCabin.win_condition.l1.location = "Curacao";
			pchar.quest.Patria_CondotierCabin.function = "Patria_CondotierCabin";
		break;
		
		case "vanberg_sold":
			dialog.text = "Ah-ah-ah! Guarda un po’! Jacob aveva ragione, come sempre – questa volpe non è venuta sull’isola per caso. Sembra che nel forziere ci sia una bella montagna d’oro. Sei stato proprio uno sprovveduto a venire qui da solo, compare. Ma d’altronde, così ci faciliti il lavoro!";
			link.l1 = "Quelle canaglie mi hanno trovato! Non l’avevo previsto… Ma non sarò una preda facile!";
			link.l1.go = "vanberg_sold_1";			
		break;
		
		case "vanberg_sold_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("vanberg_sold_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "PrepareMassakraInShore");
			AddDialogExitQuest("MainHeroFightModeOn");			
		break;
		
		case "Abihouselady":
			dialog.text = "Cerchi qualcuno, buon uomo?";
			link.l1 = "Sì, sono io. Dove sono Solomon e Abigail Shneur?";
			link.l1.go = "Abihouselady_1";			
		break;
		
		case "Abihouselady_1":
			dialog.text = "Non abitano più qui. Non potevano più permettersi questa casa. Abigail, poveraccia, lavora ora come serva del governatore. Si spacca la schiena ogni giorno per mantenere sé stessa e suo padre. Solomon si scola il rum in taverna ogni santo giorno, non riesce a sopportare quel che è successo. Ora vivono in una capanna misera vicino al mare...";
			link.l1 = "Oh... Va bene, grazie per l'informazione. Devo andare.";
			link.l1.go = "Abihouselady_2";
		break;
		
		case "Abihouselady_2":
			DialogExit();
			NextDiag.CurrentNode = "Abihouselady_3";
		break;
		
		case "Abihouselady_3":
			dialog.text = "Cos'altro vorresti sapere, signor mio?";
			link.l1 = "Niente, lascia stare.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Abihouselady_3";
		break;
		
		//удаление Мейфенг при провале квеста
		case "TempOffGuard":
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//удаляем атрибут квестового корабля
			if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_MAYFANG)
			{
				pchar.Ship.Type = GenerateShipExt(SHIP_TARTANE, true, pchar);
				pchar.Ship.name = "A boat";
				SetBaseShipData(pchar);
				SetCrewQuantityOverMax(PChar, 0);//сажаем на тартану
			}
			else
			{
				for(i = 1; i < COMPANION_MAX; i++)
				{
						iTemp = GetCompanionIndex(PChar, i);
					if(iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
						{
							pchar.questTemp.HWIC.Self.CompanionIndex = sld.Index;
							sld = GetCharacter(sti(pchar.questTemp.HWIC.Self.CompanionIndex));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			dialog.text = "Capitano, avete sottratto una nave della Compagnia Olandese delle Indie Occidentali. Ho l’autorità di confiscarla, anche ricorrendo alla forza se vi azzardate a resistere. È un ordine di Peter Stuyvesant.";
			link.l1 = "Ebbene, se è un ordine dello stesso Peter Stuyvesant... Non andrò certo in guerra con l’Olanda per una nave. Prendila.";
			link.l1.go = "TempOffGuard_1";			
		break;
		
		case "TempOffGuard_1":
			dialog.text = "Bravo che hai messo giudizio.";
			link.l1 = "...";
			link.l1.go = "TempOffGuard_2";
		break;
		
		case "TempOffGuard_2":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;//открыть локацию
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");
		break;
		
		// Jason НСО
		case "arest":
			dialog.text = "Naturalmente è ora di andarsene, avrai persino compagnia. Guardie! Prendetelo!";
		    link.l1 = "Fammelo vedere!";
		    link.l1.go = "fight";
		break;
		
		case "fight":
            Pchar.quest.ArestInResidenceEnd.win_condition.l1          = "ExitFromLocation";
		    Pchar.quest.ArestInResidenceEnd.win_condition.l1.location = Pchar.location;
		    Pchar.quest.ArestInResidenceEnd.win_condition             = "ArestInResidenceEnd";
		    Pchar.quest.ArestInResidenceEnd.ResidenceLocation = Pchar.location;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_LockFightMode(Pchar, true); // ножками путь убегает
		    LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		    LAi_group_Attack(NPChar, Pchar); // не работает на бессмертного мера :(
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // фантом солдат
			if (i != -1)
			{
			    LAi_group_Attack(&Characters[i], Pchar);
			}
		break;
		
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Ehi, ascolta bene! In quanto cittadino di questa città, ti prego di non andare in giro con la lama sguainata.","Sai, in quanto cittadino di questa città, ti chiedo cortesemente di non andare in giro con la lama sguainata.");
			link.l1 = LinkRandPhrase("Va bene.","D'accordo.","Come dite voi...");
			link.l1.go = "exit";
		break;
	}
}

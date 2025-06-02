void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;
		//----------------- уничтожение банды ----------------------
		case "DestroyGang_begin":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); //боевке можно
			DeleteAttribute(&locations[FindLocation(pchar.GenQuest.DestroyGang.Location)], "DisableEncounters"); //энкаунтеры можно 
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("MayorQuestGang_" + i) == -1) continue;
				sld = CharacterFromID("MayorQuestGang_" + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
			}
			sTemp = GetFullName(&characters[GetCharacterIndex(pchar.GenQuest.DestroyGang.MayorId)]);
			dialog.text = LinkRandPhrase("Denaro sul barile "+GetSexPhrase("compagno","ragazza")+"! Il mio nome è "+GetFullName(npchar)+", e non sono abituato alle obiezioni...","Ora mostrami la tua borsa, "+GetSexPhrase("compagno","ragazza")+", e fai presto! Il mio nome è  "+GetFullName(npchar)+", e spero che tu abbia sentito parlare di me...","Dammi tutto ciò che hai di valore, requisisco anche il contenuto della tua borsa. E sbrigati, la pazienza non è il mio forte. Non posso dire lo stesso della mia sete di sangue!");
			Link.l1 = LinkRandPhrase("Ehi, quindi sei quel famoso bandito "+GetFullName(npchar)+", di cui il governatore locale "+sTemp+"non smette mai di parlare?","Oh, quindi sei quel bandito braccato dal governatore locale "+sTemp+"?! ","Contento"+GetSexPhrase("","")+" vederti, "+GetFullName(npchar)+". Il governatore locale, "+sTemp+" parla solo di te.");
			Link.l1.go = "DestroyGang_1";
		break;		
		case "DestroyGang_1":
			dialog.text = LinkRandPhrase("Sì, sono ben conosciuto in queste terre, he-he... Aspetta, non sei un altro "+GetSexPhrase("cane sporco","sporca cagna")+" del governatore che ha inviato per rintracciarmi?","Il governatore è mio buon amico, è vero. E tu, per caso, "+GetSexPhrase("un altro eroe, inviato","un'altra eroina, inviata")+" per la mia testa da lui?","Il governatore è il mio miglior amico, non è un segreto, he-he. Ma come lo sai? Forse, ti ha mandato lui da me?");
			Link.l1 = LinkRandPhrase("Esatto, mascalzone. Preparati a morire!","Non sei mica uno sveglio! Bene, è ora di procedere con la tua liquidazione. Basta chiacchiere.","Sì, sono io. Sfodera la tua arma, compagno! Vediamo di che colore è il tuo sangue.");
			Link.l1.go = "DestroyGang_ExitFight";	
			Link.l2 = LinkRandPhrase("Oh, non importa! Non ho bisogno di tali problemi affatto...","No, no, non sono affatto un eroe...","No, no, mai! Non ho bisogno di problemi...");
			Link.l2.go = "DestroyGang_2";	
		break;
		case "DestroyGang_2":
			dialog.text = LinkRandPhrase("È meglio così, "+GetSexPhrase("compagno","ragazza")+"...E ora sparisci!","E questa è una decisione giusta. Vorrei tu sapessi quanti eroi ho mandato in un altro mondo... Bene, meno parole. Vattene, "+GetSexPhrase("pezzo di merda","puttana")+"!","Bene "+GetSexPhrase("ragazzo","ragazza")+"! Una decisione molto saggia - non interferire negli affari altrui... Va bene, sparisci già, "+GetSexPhrase("compagno","ragazza")+".");
			Link.l1 = "Addio e buona fortuna a te...";
			Link.l1.go = "DestroyGang_ExitAfraid";	
		break;

		case "DestroyGang_ExitAfraid":
			pchar.GenQuest.DestroyGang = "Found"; //флаг нашёл, но струсил
			npchar.money = AddMoneyToCharacter(npchar, sti(pchar.money));
			pchar.money = 0;
			LAi_SetWarriorType(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetCheckMinHP(npchar, LAi_GetCharacterHP(npchar)-1, false, "DestroyGang_SuddenAttack");
			for(i = 1; i < 4; i++)
			{
				if (GetCharacterIndex("MayorQuestGang_" + i) == -1) continue;	
				sld = CharacterFromID("MayorQuestGang_" + i);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, npchar, "", -1);
				LAi_SetImmortal(sld, true);
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "DestroyGang_SuddenAttack");
			}
			DialogExit();
		break;

		case "DestroyGang_ExitFight":
			for(i = 0; i < 4; i++)
			{
				if (GetCharacterIndex("MayorQuestGang_" + i) == -1) continue;
				sld = CharacterFromID("MayorQuestGang_" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "DestroyGang_Afrer");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		// ОЗГ - пассажир
		case "ContraPass_abordage":
			dialog.text = "Arghh, mascalzone! Come hai osato attaccare la mia nave?! Pagherai per questo!";
			link.l1 = "Al contrario, vengo effettivamente pagato per questo. Hai un certo uomo a bordo, chiamato "+pchar.GenQuest.TakePassenger.Name+". È lui di cui ho bisogno.";
			link.l1.go = "ContraPass_abordage_1";
		break;
		
		case "ContraPass_abordage_1":
			dialog.text = "Sapevo che questo furfante ci avrebbe portato guai... Ma non mi prenderai così facilmente! Difenditi, sporco pirata!";
			link.l1 = "Sei tu che devi pensare alla difesa, canaglia.";
			link.l1.go = "ContraPass_abordage_2";
		break;
		
		case "ContraPass_abordage_2":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "ContraPass_GivePrisoner");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Tempsailor":
			dialog.text = "Capitano, abbiamo perquisito le cabine e la stiva, come avevi ordinato. Quel mascalzone ha cercato di nascondersi, ma lo abbiamo trovato.";
			link.l1 = "Eccellente! Dove si trova ora?";
			link.l1.go = "Tempsailor_1";
		break;
		
		case "Tempsailor_1":
			dialog.text = "Lui è nella stiva, come ci hai ordinato.";
			link.l1 = "Eccellente! Ora lasciamo questa vecchia tinozza. È ora di tornare.";
			link.l1.go = "Tempsailor_2";
		break;
		
		case "Tempsailor_2":
			dialog.text = "Subito, capitano!";
			link.l1 = "...";
			link.l1.go = "Tempsailor_3";
		break;
		
		case "Tempsailor_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
			sld = GetCharacter(NPC_GenerateCharacter("ContraPass", "citiz_"+(rand(9)+11), "man", "man", 10, sti(pchar.GenQuest.TakePassenger.Nation), -1, true, "quest"));
			sld.name = pchar.GenQuest.TakePassenger.Name;
			sld.lastname = "";
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(sld);
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			Pchar.GenQuest.TakePassenger.PrisonerIDX = sti(pchar.GenQuest.LastQuestPrisonerIdx);
		break;
		
		case "Fugitive_city": // ходит по городу
			pchar.quest.AllMayorsQuests_Late.over = "yes"; //снимаем общий таймер
			dialog.text = "Cosa desidera, signore?";
			link.l1 = "Ebbene-e... Quindi tu sei "+pchar.GenQuest.FindFugitive.Name+", vero? Sono molto contento di vederti...";
			link.l1.go = "Fugitive_city_1";
		break;
		
		case "Fugitive_city_1":
			dialog.text = "Ebbene, sono proprio io, anche se non capisco perché tu sia contento di vedermi. Mi sembra strano, visto che non ti ho mai visto prima... Ti va di spiegarti?";
			link.l1 = "Ma certamente. Io vengo da "+XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.Startcity+"Gen")+", per ordine del governatore locale. Sei arrestato e devo consegnarti alla stessa città... Oh, e le mani lontano dalla tua sciabola! Non fare niente di stupido, buon uomo, o andrà male per te!";
			link.l1.go = "Fugitive_city_2";
		break;
		
		case "Fugitive_city_2":
			dialog.text = "Allora, mi hai trovato dopo tutto... Signore, ascoltami e, forse, cambierai idea. Sì, ho disertato dalla guarnigione. Ma non potevo assistere alla degradazione del nostro esercito!\nVolevo una vita tranquilla e l'ho trovata qui, in questo villaggio... Lasciami in pace, digli che non sei riuscito a trovarmi o che sono scappato con i pirati in mare aperto. In cambio ti darò questa borsa di ambra. Un oggetto molto prezioso, devo dire...";
			link.l1 = "Non pensare nemmeno di corrompermi, signore! Consegnate la vostra arma e seguitemi!";
			link.l1.go = "Fugitive_city_fight";
			link.l2 = "Hmm... Decadimento? Una vita tranquilla e pacifica? Va bene, suppongo che posso esaudire il tuo desiderio. Dove si trova il tuo ambra?";
			link.l2.go = "Fugitive_city_gift";
		break;
		
		case "Fugitive_city_fight":
			dialog.text = "Allora sguaina la tua spada, mercenario! Non mi prenderai così facilmente!";
			link.l1 = "Bene, vediamo il tuo valore!";
			link.l1.go = "Fugitive_fight_1";
		break;
		
		case "Fugitive_city_gift":
			TakeNItems(pchar, "jewelry8", 50+hrand(25));
			TakeNItems(pchar, "jewelry7", 2+hrand(5));
			PlaySound("interface\important_item.wav");
			Log_Info("You have received amber");
			dialog.text = "Ecco... E spero davvero di non vedere mai più né te né altri 'inviati'.";
			link.l1 = "Vi assicuro che non lo farete. Addio, signore!";
			link.l1.go = "Fugitive_gift_exit";
		break;
		
		case "Fugitive_gift_exit":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			pchar.GenQuest.FindFugitive = "Found"; //флаг провалил
			AddQuestRecord("MayorsQuestsList", "12-4");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.Startcity));
		break;
		
		case "Fugitive_fight_1":// в городе и бухте
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			Diag.currentnode = "Fugitive_afterfight";
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_SetCheckMinHP(npchar, 10.0, true, "Fugitive_afterfight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Fugitive_afterfight":
			dialog.text = "Arrgh! Hai vinto, dannazione! Mi arrendo...";
			link.l1 = "Guarda la tua lingua, signore! E ora, dammi la tua sciabola, per favore... Seguimi, e senza trucchi stupidi!";
			link.l1.go = "Fugitive_afterfight_1";
		break;
		
		case "Fugitive_afterfight_1":
			DialogExit();
			RemoveAllCharacterItems(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			//DeleteAttribute(npchar, "LifeDay");
			npchar.lifeday = 0;
			LAi_SetImmortal(npchar, true);
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(npchar);
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			Pchar.GenQuest.FindFugitive.PrisonerIDX = sti(pchar.GenQuest.LastQuestPrisonerIdx);
			pchar.GenQuest.FindFugitive = "Execute"; //флаг выполнил успешно
			pchar.quest.FindFugitive1.win_condition.l1 = "location";
			pchar.quest.FindFugitive1.win_condition.l1.location = pchar.GenQuest.FindFugitive.Startcity+"_townhall";
			pchar.quest.FindFugitive1.function = "FindFugitive_inResidence";
			SetFunctionTimerCondition("FindFugitive_Over", 0, 0, 30, false);
		break;
		
		case "Fugitive_shore": // в бухте
			pchar.quest.AllMayorsQuests_Late.over = "yes"; //снимаем общий таймер
			dialog.text = "Signore, non ho voglia di parlare con te, quindi...";
			link.l1 = "Tuttavia, dovrai parlare con me. Tu sei "+pchar.GenQuest.FindFugitive.Name+", non sei vero? Penso che non dovresti negarlo.";
			link.l1.go = "Fugitive_shore_1";
		break;
		
		case "Fugitive_shore_1":
			dialog.text = "E non lo nego, sono io. Ma cosa vuoi?";
			link.l1 = "Ho bisogno di portarti a "+XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.Startcity)+", il governatore locale muore dalla voglia di vederti. Niente scherzi stupidi, per favore! Arrenditi la tua arma e seguimi!";
			link.l1.go = "Fugitive_shore_2";
		break;
		
		case "Fugitive_shore_2":
			dialog.text = "Capisco... Signore, prima che tu agisca d'impulso lascia che ti dica qualcosa. Sì, ho disertato dal presidio. Ma ho avuto i miei motivi per farlo. Non posso restare in servizio, è troppo per me! Capisci quello che sto dicendo? Non posso!\nVoglio una vita tranquilla e ho trovato una tale vita qui, in questo villaggio... Lasciami in pace, dì loro che non sei riuscito a trovarmi o che sono fuggito con i pirati in mare aperto. In cambio ti darò il mio pescato settimanale di perle. È tutto quello che ho.";
			link.l1 = "Non pensare nemmeno di corrompermi, signore! Consegnate la vostra arma e seguitemi!";
			link.l1.go = "Fugitive_city_fight";
			link.l2 = "Hmm... Sei stanco del servizio militare? Desideri una vita tranquilla? Va bene, penso di poter realizzare il tuo desiderio. Dove sono le tue perle?";
			link.l2.go = "Fugitive_shore_gift";
		break;
		
		case "Fugitive_shore_gift":
			TakeNItems(pchar, "jewelry52", 100+hrand(40));
			TakeNItems(pchar, "jewelry53", 400+hrand(100));
			PlaySound("interface\important_item.wav");
			Log_Info("You have received pearls");
			dialog.text = "Ecco... E spero di non vedere mai più né te né altri 'inviati'.";
			link.l1 = "Vi assicuro che non lo farete. Addio, signore!";
			link.l1.go = "Fugitive_gift_exit";
		break;
		
		case "Fugitive_tavern": // в таверне
			pchar.quest.AllMayorsQuests_Late.over = "yes"; //снимаем общий таймер
			dialog.text = "Ehhh... hic! Signore, non sto cercando compagnia - specialmente la tua. Vattene!";
			link.l1 = "Ma STO cercando la tua compagnia, "+pchar.GenQuest.FindFugitive.Name+"! E tollererai la mia compagnia nella stiva della mia nave. Stiamo andando a  "+XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.Startcity)+", al governatore della città. Sta quasi morendo dalla voglia di vederti.";
			link.l1.go = "Fugitive_tavern_1";
		break;
		
		case "Fugitive_tavern_1":
			dialog.text = "H-Hic!"+RandSwear()+" Così mi ha davvero rintracciato alla fine! Ascolta, amico, non sai cosa è successo, non c'eri! Non potevo rimanere al servizio, semplicemente non potevo! Ancora mi ubriaco ogni sera per dimenticare quello\nGuarda, facciamo un accordo. Dìgli che non sei riuscito a trovarmi o che sono fuggito con i pirati in mare aperto. In cambio ti darò tutti i pepite che ho trovato nella grotta locale. È tutto quello che ho, vedi, ti sto dando tutto, solo per non vedere mai più "+XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.Startcity)+"...";
			link.l1 = "Non pensare nemmeno di corrompermi, signore! Rendi la tua arma e seguimi!";
			link.l1.go = "Fugitive_tavern_fight";
			link.l2 = "Mmm... Una storia sgradevole? Sei tormentato da incubi o da una coscienza colpevole? Va bene, suppongo che posso lasciarti a gestire questo da solo. Dove sono i tuoi pepite?";
			link.l2.go = "Fugitive_tavern_gift";
		break;
		
		case "Fugitive_tavern_gift":
			TakeNItems(pchar, "jewelry5", 50+hrand(30));
			TakeNItems(pchar, "jewelry6", 100+hrand(50));
			PlaySound("interface\important_item.wav");
			Log_Info("You have received nuggets");
			dialog.text = "Ecco... E spero davvero di non vedere mai più né te né altri 'inviati'.";
			link.l1 = "Vi assicuro che non lo farete. Addio, signore!";
			link.l1.go = "Fugitive_gift_exit";
		break;
		
		case "Fugitive_tavern_fight":
			dialog.text = "Allora sguaina la tua lama, mercenario! Non mi avrai così facilmente!";
			link.l1 = "Bene, vediamo il tuo valore!";
			link.l1.go = "Fugitive_fight_2";
		break;
		
		case "Fugitive_fight_2":// в таверне
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			LAi_SetImmortal(npchar, false);
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			Diag.currentnode = "Fugitive_afterfight";
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_SetCheckMinHP(npchar, 10.0, true, "Fugitive_afterfight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
	}
}

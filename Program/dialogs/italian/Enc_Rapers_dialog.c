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

		case "Exit_Fight":	
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetPlayerType(pchar); 
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetImmortal(sld, false);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			
			if(pchar.GenQuest.EncGirl == "RapersTreasure")
			{
				LAi_group_SetCheckFunction("EnemyFight", "EncGirl_RapersAfter");
			}			
			else
			{
				LAi_group_SetCheck("EnemyFight", "LandEnc_RapersAfrer");			
				sld = CharacterFromID("CangGirl");
				LAi_SetActorType(sld);
				LAi_ActorAfraid(sld, npchar, true);
			}	
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_noFight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, characterFromId("CangGirl"), "", -1);
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LandEnc_RapersBeforeDialog");
			}
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorAfraid(sld, npchar, true);
			DialogExit();	
			AddDialogExitQuest("OpenTheDoors");			
		break;
		
		case "First time":
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
			}
//			Diag.TempNode = "OnceAgain";
			if(pchar.GenQuest.EncGirl == "Begin_1")
			{
				dialog.text = LinkRandPhrase("Va' per la tua strada, "+GetSexPhrase("compagno","ragazza")+". Lei ci ringrazierà alla fine, lo sai.","Vattene! Lascia che i signori si divertano un po'.","Non sono affari tuoi, "+GetSexPhrase("straniero","ragazza")+". Ci divertiremo solo un po', e tutto qui!");
				link.l1 = LinkRandPhrase("Non lo permetterò!","Abbandona i tuoi piani malvagi in questo istante!","Non tollererò alcuna violenza!");
				link.l1.go = "Node_Fight";
				link.l2 = RandPhraseSimple("Capito, me ne vado. Scusa per il disturbo.","Non oserò più disturbarvi. Scusate per il disturbo.");
				link.l2.go = "Exit_NoFight";
				pchar.GenQuest.EncGirl = "Begin_11";
			}
			if(pchar.GenQuest.EncGirl == "Begin_2")
			{
				if(sti(pchar.rank) < 10)
				{
					dialog.text = LinkRandPhrase("Vai per la tua strada, "+GetSexPhrase("compagno","ragazza")+". Lei ci ringrazierà alla fine, lo sai.","Vattene! Lascia che i signori si divertano un po'.","Non è affar tuo, "+GetSexPhrase("sconosciuto","ragazza")+". Ci divertiremo solo un po', e basta!!");
					link.l1 = LinkRandPhrase("Non permetterò questo!","Abbandona i tuoi piani malvagi in questo istante!","Non tollererò alcuna violenza!");
					link.l1.go = "Node_Fight";
					link.l2 = RandPhraseSimple("Ho capito, me ne vado. Scusa per il disturbo.","Non oserò disturbarti più. Scusa per il disturbo.");
					link.l2.go = "Exit_NoFight";
					pchar.GenQuest.EncGirl = "Begin_11";
				}
				else
				{
					dialog.text = RandPhraseSimple("Ehi, "+GetSexPhrase("straniero","signorina")+", perché stai cercando guai? Questa ragazza è un'individua 'ben conosciuta' nel nostro insediamento. L'abbiamo già pagata, ma ti ha notato e ha deciso di scappare con i nostri soldi.","Ehi, "+GetSexPhrase("compagno","ragazza")+", vai per la tua strada e non interferire con i nostri affari. Abbiamo vinto questa ragazza a un gioco di dadi, ma è stata un po' troppo veloce e quindi è scappata, la stiamo inseguendo da un'ora in questa giungla.");
					link.l1 = "Non mi importa, non ti permetterò di farle del male!";
					link.l1.go = "Node_3";
					link.l2 = RandPhraseSimple("Oh, capisco! E quasi le ho creduto! Che svergognata...","Ah, beh, allora è un'altra questione. Divertitevi, ragazzi!");	
					link.l2.go = "Exit_NoFight";
					pchar.GenQuest.EncGirl = "Begin_22";
				}	
			}
			if(pchar.GenQuest.EncGirl == "Begin_3")
			{
				if(sti(pchar.rank) < 20)
				{	
					dialog.text = "Vai per la tua strada, "+GetSexPhrase("bravo uomo","signorina")+". Ce la faremo senza di te.";
					link.l1 = "Non tollererò alcuna violenza!";
					link.l1.go = "Node_5";
					pchar.GenQuest.EncGirl = "Begin_33";
				}
				else
				{
					dialog.text = RandPhraseSimple("Ehi, "+GetSexPhrase("straniero","signorina")+", perché stai cercando guai? Questa ragazza è un'individuo 'noto', nel nostro insediamento. L'abbiamo già pagata, ma ti ha notato e ha deciso di scappare con i nostri soldi.","Ehi, "+GetSexPhrase("compagno","ragazza")+", vai per la tua strada e non interferire con i nostri affari. Abbiamo vinto questa ragazza in un gioco di dadi, ma è stata un po' troppo veloce a scappare, l'abbiamo inseguita per un'ora.");
					link.l1 = "Non mi importa - non ti permetterò di farle del male!";
					link.l1.go = "Node_3";
					link.l2 = RandPhraseSimple("Oh, capisco! E quasi ci credevo! Che sgualdrina...","Ah, beh, allora è un'altra questione. Divertitevi, ragazzi!");	
					link.l2.go = "Exit_NoFight";
					pchar.GenQuest.EncGirl = "Begin_22";
				}
			}			
		break;
		
		case "Node_Fight":
			dialog.text = RandPhraseSimple(""+GetSexPhrase("Beh, hai certamente scelto il momento giusto per una passeggiata...","Allora, hai deciso di diventare un eroe?")+" Occupati di h"+GetSexPhrase("sono","eh")+", ragazzi!","Tu "+GetSexPhrase("melma","sporcizia")+"! Osate ostacolare la nostra strada?! Taglialo"+GetSexPhrase("sono","eh")+"!");
			link.l1 = "Ho visto persone più minacciose!";
			link.l1.go = "Exit_Fight";
		break;
		
		case "Node_3":
			pchar.GenQuest.EncGirl.price = 1100*(rand(4)+5) + 200 * sti(pchar.rank);
			dialog.text = "Dovresti sapere che ci è costata un bel po'! E se sei così nobile, puoi portartela via "+sti(pchar.GenQuest.EncGirl.price)+" pesos."+GetSexPhrase(" Ti divertirai con lei, he-he...","")+"";
			if(sti(pchar.money) >= sti(pchar.GenQuest.EncGirl.price))
			{
				link.l1 = RandPhraseSimple("Ecco i tuoi soldi. La porto con me.","Smetti di sgranare i denti. Sto portando la ragazza con me. Ecco i tuoi soldi.");
				link.l1.go = "Node_4";
			}	
			link.l2 = LinkRandPhrase("Allora, vuoi soldi? Che ne dici di freddo acciaio?","Si suppone che sia divertente, guarda la ragazza stupido! È spaventata!","A chi stai cercando di fregare, te degenerato!");
			link.l2.go = "Node_Fight";
		break;
		
		case "Node_4": // бандюки уходят, девица остаётся - ГГ ее выкупил у бандюков
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddMoneyToCharacter(pchar, -makeint(sti(pchar.GenQuest.EncGirl.price))); 
			ChangeCharacterComplexReputation(pchar,"nobility", 7);
			//pchar.quest.LandEnc_RapersBadExit.over = "yes";
			sGlobalTemp = "Saved_CangGirl";
			pchar.GenQuest.EncGirl.Ransom = true;
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");			
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetImmortal(sld, true);
				LAi_SetActorType(sld);
				if(i == 1) LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
				else LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "","OpenTheDoors", 5.0);
			}
			DialogExit();
			AddDialogExitQuestFunction("EncGirl_Saved");
		break;
		
		case "Node_5":
			dialog.text = "Perché le credi in primo luogo? Quale violenza? È scappata di casa, e il nostro capo ci ha mandati a trovarla.";
			link.l1 = RandPhraseSimple("Beh, allora è un'altra storia. Vai, insegui il tuo fuggitivo.","Ah, capisco. Beh, continua a inseguirla allora... e ho degli affari da sbrigare.");
			link.l1.go = "Exit_NoFight";
			link.l2 = RandPhraseSimple("Racconta queste favole ai tuoi nipoti, se vivi abbastanza a lungo per averli!","A chi stai cercando di prendere in giro, bastardo?!");
			link.l2.go = "Node_6";
			link.l3 = "La porterò a casa da solo, per evitare guai. Chi sono i suoi genitori?";
			link.l3.go = "Node_7";
		break;
		
		case "Node_6":
			dialog.text = "Vuoi morire? È la tua scelta...";
			link.l1 = "Guarda chi parla.";
			link.l1.go = "Exit_Fight";
		break;
		
		case "Node_7":
			sGlobalTemp = "Saved_CangGirl";
			if(pchar.GenQuest.EncGirl.city == "Panama") i = hrand(2);
			else	i = hrand(3);
			switch (i)
			{
				case 0:
					pchar.GenQuest.EncGirl.FatherNom = "is a store owner";
					pchar.GenQuest.EncGirl.FatherGen = "of a store owner";
					pchar.GenQuest.EncGirl.Father = "store_keeper";
				break;
				case 1:
					pchar.GenQuest.EncGirl.FatherNom = "serves in the port office";
					pchar.GenQuest.EncGirl.FatherGen = "who serves in the port office";
					pchar.GenQuest.EncGirl.Father = "portman_keeper";
				break;
				case 2:
					pchar.GenQuest.EncGirl.FatherNom = "serves as the prison's commandant";
					pchar.GenQuest.EncGirl.FatherGen = "of a prison's commandant";
					pchar.GenQuest.EncGirl.Father = "fort_keeper";
				break;
				case 3:
					pchar.GenQuest.EncGirl.FatherNom = "is a shipyard owner";
					pchar.GenQuest.EncGirl.FatherGen = "of a shipyard owner";
					pchar.GenQuest.EncGirl.Father = "shipyard_keeper";
				break;				
			}
			dialog.text = "Suo padre "+pchar.GenQuest.EncGirl.FatherNom+", nel insediamento di "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+". Ma per favore, non deluderci, perché lui non è qualcuno con cui giocare, ci scuoierà tutti vivi...";
			link.l1 = "Non preoccuparti. La consegnerò a lui.";
			link.l1.go = "Node_12";
			pchar.GenQuest.EncGirl = "toParents";
		break;
		
		case "Node_12":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			ChangeCharacterComplexReputation(pchar,"nobility", 5);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");			
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetActorType(sld);
				LAi_SetImmortal(sld, true);
				if(i == 1) LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
				else LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "","OpenTheDoors", 5.0);
				sld.lifeDay = 0;
			}
			DialogExit();
			AddDialogExitQuestFunction("EncGirl_Saved");
		break;
		
		case "Node_8":
			dialog.text = "E così ci incontriamo di nuovo. Dove è la tua compagna? Oh, beh, in realtà non ho bisogno di lei, se sei qui.";
			link.l1 = "Signori, credo davvero che abbiate già ricevuto abbastanza denaro per lasciare in pace la ragazza.";
			link.l1.go = "Node_9";
		break;
		
		case "Node_9":
			if(hrand(1) == 0)
			{	
				pchar.GenQuest.EncGirl.PirateName1 = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
				pchar.GenQuest.EncGirl.PirateIdx = NAMETYPE_NICK;	
			}	
			else
			{
				pchar.GenQuest.EncGirl.PirateName1 = "l" + rand(GetNamesCount(NAMETYPE_VIP) - 1);	
				pchar.GenQuest.EncGirl.PirateIdx = NAMETYPE_VIP;	
			}	
			pchar.GenQuest.EncGirl.PirateName2 = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			switch(hrand(4))
			{
				case 0:
					sTemp = "a leg";
				break;
				case 1:
					sTemp = "an arm";
				break;
				case 2:
					sTemp = "an ear";
				break;
				case 3:
					sTemp = "a nose";
				break;
				case 4:
					sTemp = "an eye";
				break;
			}
			dialog.text = "Cosa sono i tuoi soldi rispetto ai tesori di "+GetName(pchar.GenQuest.EncGirl.PirateIdx,pchar.GenQuest.EncGirl.PirateName1,NAME_GEN)+"? "+"Era così avido che non voleva sposare sua figlia perché voleva evitare spese extra...\nMa ha la nostra parte nei suoi bauli! "+GetName(NAMETYPE_ORIG,pchar.GenQuest.EncGirl.PirateName2,NAME_NOM)+" ha perso nell'abbordaggio "+sTemp+"! E cosa hai ottenuto invece? "+"Pietosa manciata di argento? "+GetName(pchar.GenQuest.EncGirl.PirateIdx,pchar.GenQuest.EncGirl.PirateName1,NAME_NOM)+" ha sempre portato tutto il bottino nel suo nascondiglio. Ma ora non ci arrenderemo! Mostraci dove sono i suoi forzieri!";
			link.l1 = "Ebbene, certamente non mi sono candidato per proteggere i tesori del tuo capitano, ma non posso mostrarti il posto... Perché non so dove sia questo posto.";
			link.l1.go = "Node_10";
		break;
		
		case "Node_10":
			dialog.text = "Stai mentendo!!! Posso sentire l'odore dell'oro provenire da questa grotta! Mostrami il posto se non vuoi morire!";
			link.l1 = "Vedo che le mie parole non sono riuscite a convincerti. Forse, la mia lama sarà più espressiva?";
			link.l1.go = "Node_11";
		break;
		
		case "Node_11":
			pchar.GenQuest.EncGirl = "RapersTreasure";
			dialog.text = "Tu "+GetSexPhrase("canaglia","sporcizia")+"! Fuori dal mio cammino!";
			link.l1 = "Argh!";
			link.l1.go = "exit_fight";
		break;
		
		case "EncGirl_Berglar":
			dialog.text = "Ciao, buon "+GetSexPhrase("uomo","signora")+". Abbiamo lamentele su di te.";
			link.l1 = "Lamentele da chi? Da quella puttana?";
			link.l1.go = "EncGirl_Berglar1";
		break;
		
		case "EncGirl_Berglar1":
			dialog.text = "Guarda la tua lingua, capito? Non ti permetterò di insultare mia sorella! Prima l'hai molestata nella giungla, poi l'hai portata qui "+GetSexPhrase("per più indecenza","e mi ha derubato")+".";
			link.l1 = "Ehi compagno, devo davvero ascoltare tutto questo?";
			link.l1.go = "EncGirl_Berglar2";
		break;
		
		case "EncGirl_Berglar2":
			pchar.GenQuest.EncGirl.BerglarSum = makeint(sti(pchar.money)/5) + 5000;
			if(sti(pchar.GenQuest.EncGirl.BerglarSum) > 250000) pchar.GenQuest.EncGirl.BerglarSum = 220000 + rand(30000);
			if(sti(pchar.GenQuest.EncGirl.BerglarSum) > 0)
			{
				dialog.text = "No. Una somma modesta di solo "+sti(pchar.GenQuest.EncGirl.BerglarSum)+" pesos ti salveranno da tutti i guai.";
				if(sti(pchar.money) >= sti(pchar.GenQuest.EncGirl.BerglarSum))
				{
					link.l1 = "Ebbene, le nobili imprese sono certamente un po' costose al giorno d'oggi. Va bene, prendilo...";
					link.l1.go = "EncGirl_Berglar3";
				}	
				link.l2 = "Credo sarebbe più economico farti un buco nella pancia così non mi ostacoleresti la via per l'uscita.";
				link.l2.go = "EncGirl_Berglar4";
			}
			else
			{
				dialog.text = "No. Ma svuoterai anche le tue tasche, altrimenti ti pugnalerò!";
				link.l1 = "Bene, prendilo, mascalzone! Ma non te la caverai così facilmente...";
				link.l1.go = "EncGirl_Berglar3_1";
				link.l2 = "Credo che sarebbe più facile farti un buco nella pancia così da non ostacolare la mia via verso l'uscita.";
				link.l2.go = "EncGirl_Berglar4";				
			}			
		break;
		
		case "EncGirl_Berglar3":
			AddMoneyToCharacter(pchar, -makeint(sti(pchar.GenQuest.EncGirl.BerglarSum)));
			dialog.text = "Molto bene. Buon viaggio.";
			link.l1 = "Buona fortuna.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirlFack_outRoom");			
		break;
		
		case "EncGirl_Berglar3_1":
			dialog.text = "Certo che non lo farò, certo... Beh, addio a te, "+GetSexPhrase("compagno","ragazza")+"."+GetSexPhrase(" E ricorda, non sei così affascinante che qualsiasi ragazza si sarebbe innamorata di te al primo sguardo. Questa sarebbe la mia lezione per te.","")+"";
			link.l1 = ""+GetSexPhrase("Questo è sicuro!..","Vattene già!")+"";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirlFack_outRoomRaped");			
		break;
		
		case "EncGirl_Berglar4":
			dialog.text = "Sembreresti come "+GetSexPhrase("un uomo così nobile","una signora così ben educata")+", perché le parolacce?";
			link.l1 = "Mi si addice di più...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirlFack_fight");
		break;
		
		case "Node_2":
			dialog.text = "Ebbene, l'hai chiesto tu! Dovremmo solleticarlo h"+GetSexPhrase("sono","eh")+" con acciaio, ragazzi?";
			Link.l1 = "Prega prima di morire!";
			Link.l1.go = "Exit_Fight";
		break;

		case "OnceAgain":
			Diag.TempNode = "OnceAgain";
			dialog.text = "Allora, vuoi unirti o no? "+GetSexPhrase("Vattene, non c'è abbastanza per tutti noi","Sparisci mentre puoi, una ragazza è più che sufficiente per noi")+"!";
			Link.l1 = "Bene, allora non vi disturberò.";
			Link.l1.go = "Exit_NoFight";
			Link.l2 = "Non permetterò che accada alcuna violenza!";
			Link.l2.go = "Node_2";
		break;				
	}
}

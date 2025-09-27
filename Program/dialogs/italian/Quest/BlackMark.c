void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i, n;
	string sTemp, sStr, sStr2, sGun, sBullet, attrL;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	if (findsubstr(sAttr, "SetMusketBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetMusketBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetMusketBullets2";
 	}

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Cosa volete?";
			link.l1 = "Niente.";
			link.l1.go = "exit";
		break;
		
		case "BM_Contra_1":
			dialog.text = "Chi sei tu, e che diavolo ci fai a bighellonare da queste parti?!";
			if (sti(pchar.reputation.nobility) >= 40)
			{
				link.l1 = "Tranquillo, compare. Sto solo passando. Non ho intenzione d’impicciarmi nei tuoi... affari, qualunque essi siano.";
			}
			else
			{
				link.l1 = "Eh? Questo faro è roba tua? La prossima volta, metti il tuo nome su una palma o tira su una dannata staccionata.";
			}
			link.l1.go = "BM_Contra_2";
			DelLandQuestMark(npchar);
		break;
		
		case "BM_Contra_2":
			if (sti(pchar.reputation.nobility) >= 40)
			{
				dialog.text = "Fuori di qui! Se rovini l’affare spaventando il cliente, ti giuro che...";
			}
			else
			{
				dialog.text = "Ascolta, ragazzino, non costringermi a vedere se la tua lama è affilata come la tua lingua. Sparisci e...";
			}
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_BarbadosPatrolPribegaet");
		break;
		
		case "BM_Contra_3":
			dialog.text = "E allora, Frankie, quale dei due è?";
			link.l1 = "...";
			link.l1.go = "BM_Contra_3_1";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "dialog_stay12", "1", 1.9);
		break;
		case "BM_Contra_3_1":
			StartInstantDialog("BM_PatrolZhitel", "BM_Contra_4", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_4":
			dialog.text = "No... Maledizione, ma non riconosco nessuna di quelle facce.";
			link.l1 = "...";
			link.l1.go = "BM_Contra_4_1";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "dialog_stay15", "1", 1.9);
		break;
		case "BM_Contra_4_1":
			StartInstantDialog("BM_PatrolOff", "BM_Contra_5", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_5":
			dialog.text = "Cosa?! Sei sicuro?";
			link.l1 = "...";
			link.l1.go = "BM_Contra_5_1";
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolZhitel"));
		break;
		case "BM_Contra_5_1":
			StartInstantDialog("BM_PatrolZhitel", "BM_Contra_6", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_6":
			dialog.text = "Pensi ch’io sia cieco?! Ti dico, che diavolo...";
			link.l1 = "...";
			link.l1.go = "exit";
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolOff"));
			CharacterTurnByChr(CharacterFromID("BM_PatrolOff"), CharacterFromID("BM_PatrolZhitel"));
			AddDialogExitQuest("BM_BarbadosMayakVystrel");
		break;
		
		case "BM_Contra_7":
			dialog.text = "Che diavolo?!";
			link.l1 = "...";
			link.l1.go = "BM_Contra_7_1";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "dialog_stay9", "1", 1.9);
			CharacterTurnByChr(npchar, CharacterFromID("BM_Contra_1"));
		break;
		
		case "BM_Contra_7_1":
			StartInstantDialog("BM_Contra_1", "BM_Contra_8", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_8":
			dialog.text = "Chi ha sparato?!";
			link.l1 = "...";
			link.l1.go = "BM_Contra_8_1";
			locCameraFromToPos(-84.11, 6.33, -62.68, true, -78.07, 3.20, -66.67);
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolOff"));
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "dialog_stay13", "1", 1.9);
		break;
		
		case "BM_Contra_8_1":
			StartInstantDialog("BM_PatrolOff", "BM_Contra_9", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_9":
			dialog.text = "Ci prendi per degli allocchi, feccia? Butta le pistole a terra, tutti quanti! E tu pure!";
			link.l1 = "...";
			link.l1.go = "BM_Contra_9_1";
			CharacterTurnByChr(npchar, CharacterFromID("BM_Contra_1"));
		break;
		
		case "BM_Contra_9_1":
			StartInstantDialog("BM_Contra_1", "BM_Contra_10", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_10":
			dialog.text = "Calma la furia, ufficiale. Non siamo stati noi, non vedi? I nostri moschetti sono dove li avevamo. E tu non azzardarti a toccare il tuo!";
			link.l1 = "...";
			link.l1.go = "BM_Contra_10_1";
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolOff"));
		break;
		case "BM_Contra_10_1":
			StartInstantDialog("BM_PatrolOff", "BM_Contra_11", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_11":
			dialog.text = "Mi dai ordini, maledetto?! Arrestateli tutti, subito!";
			link.l1 = "...";
			link.l1.go = "BM_Contra_11_1";
			CharacterTurnByChr(npchar, CharacterFromID("BM_Contra_1"));
		break;
		
		case "BM_Contra_11_1":
			StartInstantDialog("BM_Contra_1", "BM_Contra_12", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_12":
			dialog.text = "Al diavolo te! Non succederà mai. Ragazzi, alle armi!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_BarbadosMayakBoinya");
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolOff"));
		break;
		
		case "BM_Irons_1":
			dialog.text = "Ehi, ehi, bada a come ti muovi! Qualcuno finirà sventrato se continui a sventolare quella lama come un pazzo.";
			link.l1 = "Ah, chi?";
			link.l1.go = "BM_Irons_2";
			LAi_SetCurHPMax(npchar);
			SetOfficerToMushketer(npchar, "mushket1", true);
		break;
		
		case "BM_Irons_2":
			dialog.text = "Ma certo, io.";
			link.l1 = "Che diamine...? Chi diavolo sei tu?";
			link.l1.go = "BM_Irons_4";
			link.l2 = "È proprio quello che sto cercando di fare. Andiamo?";
			link.l2.go = "BM_Irons_3";
		break;
		
		case "BM_Irons_3":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			npchar.MusketerDistance = 10;
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		break;
		
		case "BM_Irons_4":
			if (startHeroType == 4)
			{
				dialog.text = "Sono Tommy! Tommy Irons. Credo. E tu chi diavolo sei? Sei una donna coraggiosa, te lo dico io, andare in giro così, eh eh eh.";
				link.l1 = "Coraggioso, davvero. E non ho paura di tapparti la bocca, se serve. Fa un caldo dell’inferno qui, perciò mi vesto leggera – non certo per piacere a te o ai tuoi simili. Mi chiamo Helen MacArthur. Gli amici mi chiamano Rumba, ma tu non sei certo tra quelli. E che vuol dire quel ‘suppongo’ che hai detto?";
				link.l1.go = "BM_Irons_5";
			}
			else
			{
				dialog.text = "Sono Tommy! Tommy Irons. Credo. E tu chi sei?";
				link.l1 = ""+GetFullName(pchar)+". E cosa vorrebbe dire esattamente quel 'suppongo'?";
				link.l1.go = "BM_Irons_5";
			}
			LAi_SetCurHPMax(pchar);
		break;
		
		case "BM_Irons_5":
			dialog.text = "Vuol dire proprio quel che senti. Ho perso la memoria – m’hanno conciato per le feste in battaglia. Sai com’è, a volte ci si scorda tutto. Però m’è andata bene: mi son dimenticato solo il nome. Fortuna vuole che porto al collo ‘sto ciondolo con scritto ‘Thomas’. Ma preferisco Tommy. E Irons. Ho combattuto tra gli Ironsides per Cromwell, tienilo a mente. Però ‘Ironsides’ è una parola troppo pesante. Irons suona molto meglio.";
			link.l1 = "Capisco cosa non va in te, Tommy. Allora, dimmi – che è successo? Miravi a qualcuno in particolare? Hai colpito il bersaglio? O stavi solo sparando per passatempo? Non mi stupirebbe affatto.";
			link.l1.go = "BM_Irons_6";
		break;
		
		case "BM_Irons_6":
			dialog.text = "L’ho colpito, e l’ho colpito per davvero! In tutti i sensi. Ti ricordi quel damerino? Mi ha seguito con tutta una pattuglia di soldati. Solo perché ho scaldato il letto a sua moglie.";
			link.l1 = "Eh sì, ci hai proprio beccati, eh. Suppongo che vi abbia colto sul fatto, vero?";
			link.l1.go = "BM_Irons_7";
		break;
		
		case "BM_Irons_7":
			dialog.text = "Ah! Non ci crederesti mai – no. La sgualdrina ha confessato dopo. Rimorso, oppure forse non se l’è goduta quanto me, eheh. Chi può mai capire cosa pensano le donne? A me poco importa, ah-ah-ah!";
			link.l1 = ""+GetSexPhrase("Hmm, quella lì è proprio una stramba.","Gli uomini... Un momento cerchi di capire cosa ci passa per la testa, quello dopo dici che non te ne importa nulla. Ma su una cosa hai ragione – quello che ha fatto lei è stato ben strano. Avrebbe dovuto semplicemente andarsene e scordarselo come un brutto sogno. È proprio ciò che farei io, se toccasse a me.")+"";
			link.l1.go = "BM_Irons_8";
		break;
		
		case "BM_Irons_8":
			dialog.text = "Esatto! La gente dice che ho qualche rotella fuori posto. Mi dispiace per quei soldati che ci hanno lasciato la pelle. Lo so, anch’io ero solo carne da cannone una volta. Non te l’ho già detto?";
			link.l1 = "Sì, proprio così. Dagli Ironsides. Cromwell.";
			link.l1.go = "BM_Irons_9";
		break;
		
		case "BM_Irons_9":
			dialog.text = "Ah sì? Non ricordo se l’ho fatto o meno. Sai come sono finito nel Nuovo Mondo? Vuoi che te lo racconti?";
			link.l1 = "No, e non mi interesserebbe, Tommy.";
			link.l1.go = "BM_Irons_10";
		break;
		
		case "BM_Irons_10":
			dialog.text = "Sarebbe proprio così, sarebbe. Te lo dico io.";
			link.l1 = "D'accordo, al diavolo tutto, spara pure. Voglio dire, vai avanti.";
			link.l1.go = "BM_Irons_11";
		break;
		
		case "BM_Irons_11":
			dialog.text = "Non interrompermi, allora! Dove ero rimasto? Ah sì, ero ferito, capisci? Ho ricevuto le mie dimissioni ufficiali perché stavo dalla parte vincente. Ma avresti dovuto vedere la faccia di quei topi da scrivania! Pensavano che stessi fingendo, che facevo finta di aver perso la memoria. Continuavano a chiedermi della mia famiglia.";
			link.l1 = "E allora, che cosa hai raccontato loro?";
			link.l1.go = "BM_Irons_12";
		break;
		
		case "BM_Irons_12":
			dialog.text = "Cosa gli ho detto? Ho detto che non ricordavo. E non mentivo – non li ho mai conosciuti i miei, la mia famiglia. Sono cresciuto tra le strade, tra manovali e servi nei bassifondi. Ho preso parte alla Rivoluzione per loro. Ma l’ingratitudine della gente è incredibile – se avessi perso un braccio o una gamba, sarebbero stati costretti a mandarmi subito in pensione come eroe. E comunque, ho rischiato davvero di lasciarci la testa, per davvero!";
			link.l1 = "Allora, come sei approdato nel Nuovo Mondo, eroe di guerra?";
			link.l1.go = "BM_Irons_13";
		break;
		
		case "BM_Irons_13":
			dialog.text = "Ne dubiti? Combattere per la gente comune – cosa c’è di poco eroico in tutto ciò? Spero che un giorno femminucce come te capiranno cos’è la vera libertà!";
			link.l1 = "Sebbene la libertà sia cosa buona, in qualche modo l’hai fatta sembrare una minaccia. Va bene, Tommy, avanti.";
			link.l1.go = "BM_Irons_14";
		break;
		
		case "BM_Irons_14":
			dialog.text = "Aye. Ho avuto il mio congedo dopo che la Rivoluzione fu vinta, e mi son reso conto che non sapevo far altro che sparare e menar cazzotti in faccia alla gente. E non si può tornare nell'esercito – ti prenderebbero per il culo, specie dopo tutta la fatica che ho fatto per avere il congedo. Eh, mi sa che pure se davvero avessi perso un braccio o una gamba, quei topi da scrivania avrebbero pensato che li nascondevo da qualche parte per riattaccarli dopo aver preso i fogli d'uscita, ah-ah-ah!";
			link.l1 = "Che buffo. Ma non mi hai ancora detto come sei finito qui.";
			link.l1.go = "BM_Irons_15";
		break;
		
		case "BM_Irons_15":
			dialog.text = "Oh, sei proprio un seccatore. Non ti hanno insegnato la pazienza, "+GetSexPhrase("giovanotto","la mia ragazza")+"Non avevo nulla da fare a casa, se non sparare a papere e cervi, così sono venuto nel Nuovo Mondo. Ho veleggiato con i pirati per un po', per divertimento, e quando mi sono stufato di tutta quell'anarchia, ho fatto il mercenario.";
			link.l1 = "Storia poco originale, questa.";
			link.l1.go = "BM_Irons_16";
		break;
		
		case "BM_Irons_16":
			dialog.text = "Forse tu hai un’idea migliore? Non ti serve per caso una guardia del corpo? Perché sembri... debole. Mi sa che non farai molta strada, eh eh. Ricorda, sono i compagni che fanno il re. E una cattiva ciurma può trascinarlo a fondo.";
			link.l1 = "E che razza di "+GetSexPhrase("re","regina")+"sarei io mai in compagnia di una masnada come la tua? "+GetSexPhrase("Re","Regina")+" del letamaio?";
			link.l1.go = "BM_Irons_17";
		break;
		
		case "BM_Irons_17":
			dialog.text = "No, no! Ti sto facendo un'offerta sincera, e tu...";
			link.l1 = "Non ho ancora ricevuto nessuna proposta. Quanto chiedi per i tuoi servigi, Tommy?";
			link.l1.go = "BM_Irons_18";
		break;
		
		case "BM_Irons_18":
			dialog.text = "Duecentocinquanta dobloni subito! Così so che non sei un perdigiorno qualunque. E poi una paga mensile, ovviamente. Credo che possiamo intenderci.";
			link.l1 = "E tu non...";
			link.l1.go = "BM_Irons_19";
		break;
		
		case "BM_Irons_19":
			dialog.text = "... credi d’avere il fegato? Heh, non starò nemmeno a discutere – hai visto come ho steso quel cornuto del faro? Al primo colpo! E niente contrattazioni, se è quel che pensi. Devi dimostrare che puoi permetterti un uomo di mestiere come me.";
			if (PCharDublonsTotal() >= 250)
			{
				link.l1 = "Sì, posso! Duecentocinquanta monete d’oro. Eccoli qua.";
				link.l1.go = "BM_Irons_Hire1";
			}
			link.l2 = "Hai avuto fortuna con quel colpo. E ora cerchi pure di aumentare il tuo prezzo vantandoti. Posso fare a meno di un tipo come te. Troppa gloria e troppi dobloni per i miei gusti.";
			link.l2.go = "BM_Irons_NoHire1";
			link.l3 = "Non posso permettermelo adesso, non porto mai tanto oro addosso. Resta qui e non muoverti – vado a prendere il bottino dalla nave e torno.";
			link.l3.go = "BM_Irons_Wait1";
		break;
		
		case "BM_Irons_Hire1":
			RemoveDublonsFromPCharTotal(250);
			
			dialog.text = "Non sei così malmesso come pensavo! Ma faresti meglio a non farmi annoiare, sai? Sarebbe un vero spreco del mio talento, non trovi? Tommy e "+pchar.name+"! Scuotiamo i Caraibi!";
			link.l1 = "Impara a rispettare la catena di comando, Tommy. E in secondo luogo, per te sono il capitano. Hai capito?";
			link.l1.go = "BM_Irons_Hire2";
		break;
		
		case "BM_Irons_Hire2":
			dialog.text = "Heh, io sì, Capitano Barboso, "+GetSexPhrase("sir","mancata")+".";
			link.l1 = "Oh, sto già cominciando a pentirmene...";
			link.l1.go = "Irons_hire";
		break;
		
		case "Irons_Hire":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetPlayerType(pchar);
			DeleteAttribute(npchar, "LifeDay");
			LAi_SetImmortal(npchar, false);
			npchar.quest.OfficerPrice = 15000;
			npchar.OfficerWantToGo.DontGo = true;
			npchar.CompanionDisable = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
			SetCharacterPerk(npchar, "ShipEscape");
			npchar.CanTakeMushket = true;
			pchar.questTemp.IronsItemsBlock = true;
			LAi_SetOfficerType(npchar);
			NextDiag.CurrentNode = "Irons_officer";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			LAi_SetHP(npchar, 170.0, 170.0);
			
			// Костыли, нужно украсить интерфейс офицера ==>
			//RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			//TakeItemFromCharacter(npchar, "unarmed");
			//GiveItem2Character(npchar, "blade_42");
			//EquipCharacterByItem(npchar, "blade_42");
			//EquipCharacterByItem(npchar, "mushket1");
			//EquipCharacterByItem(npchar, "indian_2");
			// <== Костыли, нужно украсить интерфейс офицера
			
			if (CheckAttribute(pchar, "questTemp.BM_hireInGrot"))
			{
				AddQuestRecord("BlackMark", "4");
			}
			else
			{
				AddQuestRecord("BlackMark", "1");
			}
			
			// Продолжение через неделю в джунглях
			SetTimerCondition("BM_FirstJungle_Time", 0, 0, 7, false);
		break;
		
		case "BM_Irons_NoHire1":
			dialog.text = "Ebbene, sei proprio uno sciocco, ragazzo "+GetSexPhrase("uomo","donna")+"! E totalmente privo di buon senso. Ti consiglio di rimediare, altrimenti non durerai a lungo. Soprattutto su quest'Arcipelago.";
			link.l1 = "Me la caverò senza di te, Tommy. Addio.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_IronsGoodbye");
		break;
		
		case "BM_Irons_Wait1":
			dialog.text = "Sei fuori di testa? Un branco di soldati è appena crepato qui, cervellone! Di sicuro manderanno un’altra pattuglia tra poco. Potrei anche sprangare la porta del faro e preparare una difesa, ma dimmi, me ne frega? Nemmeno per sogno.";
			link.l1 = "E allora, che proponi?";
			link.l1.go = "BM_Irons_Wait2";
		break;
		
		case "BM_Irons_Wait2":
			dialog.text = "Incontrami in una grotta nella giungla. Ti concedo un paio di giorni per racimolare abbastanza monete per pagare i miei servigi – sai come maneggiare una lama, magari te la caverai.";
			link.l1 = "Sei serio? Lì finirai come un topo in trappola.";
			link.l1.go = "BM_Irons_Wait3";
		break;
		
		case "BM_Irons_Wait3":
			dialog.text = "Solo se vengono a cercarmi apposta, e con una bella ciurma. Ma penso che me la caverò. Ora però devo sparire – tra poco saranno qui. Ci si rivede, amico.";
			link.l1 = "Sì, devo andarmene anch'io, per ogni evenienza.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_IronsToCave");
		break;
		
		case "BM_Irons_WaitInCave1":
			dialog.text = "Eccoti, finalmente! Cominciavo a pensare che non fossi tagliato per far soldi. A volte credo che certe canaglie come te ci nascano proprio. E chi non ce l'ha nel sangue, muore in miseria senza lavorare un solo giorno come la brava gente.";
			link.l1 = "Ebbene, ebbene, Tommy. Se non vuoi unirti alla mia ciurma, non farlo. Vedo che ti piace marcire in questa tana.";
			link.l1.go = "BM_Irons_WaitInCave2";
			DelLandQuestMark(npchar);
		break;
		
		case "BM_Irons_WaitInCave2":
			dialog.text = "Chiaramente non ti sei mai nascosto nelle buche durante la stagione delle piogge in Irlanda, "+GetSexPhrase("giovanotto","la mia ragazza")+"! Ma seguirti è meglio che marcire qui nascosto. Ora, parliamo di quell’oro...";
			if (PCharDublonsTotal() >= 250)
			{
				link.l1 = "Ecco il tuo oro.";
				link.l1.go = "BM_Irons_HireInCave1";
			}
			link.l2 = "Non l'ho ancora preso. Pensavo di vedere se non fossi già sparito altrove.";
			link.l2.go = "BM_Irons_NoHireInCave1";
		break;
		
		case "BM_Irons_HireInCave1":
			RemoveDublonsFromPCharTotal(250);
			pchar.quest.BM_IronsTimeOver.over = "yes";
			pchar.questTemp.BM_hireInGrot = true;
			
			dialog.text = "Adesso si ragiona! E ora, che si fa... Capitano?";
			link.l1 = "Prima di tutto, leviamoci da questo buco umido, o mi metto a starnutire.";
			link.l1.go = "BM_Irons_HireInCave2";
		break;
		
		case "BM_Irons_HireInCave2":
			dialog.text = "Oh, dovresti provare la guerra. Mi sento quasi a casa in luoghi come questo.";
			link.l1 = "Capisco, dunque hai preso il congedo e ti sei scordato di rispetto e disciplina, eh, Tommy? Non temere, non mi farò scrupoli a rimetterti in riga se servirà. Ora andiamo.";
			link.l1.go = "Irons_hire";
		break;
		
		case "BM_Irons_NoHireInCave1":
			NextDiag.TempNode = "BM_Irons_WaitInCave3";
			
			dialog.text = "Ehi, Tommy Irons non scappa mai! Mantiene sempre la parola. E tu, terraferma, manterrai la tua?";
			link.l1 = "Ci sto lavorando.";
			link.l1.go = "Exit";
		break;
		
		case "BM_Irons_WaitInCave3":
			dialog.text = "Hai portato l’oro?";
			if (PCharDublonsTotal() >= 250)
			{
				link.l1 = "Ecco il tuo oro.";
				link.l1.go = "BM_Irons_HireInCave1";
			}
			link.l2 = "Non l'ho ancora trovato. Pensavo di vedere se non fossi sparito da qualche altra parte.";
			link.l2.go = "BM_Irons_NoHireInCave1";
		break;
		
		case "BM_IronsJungleUhodit":
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
			
			sld = characterFromID("Irons");
			RemovePassenger(pchar, sld);
			LAi_SetWarriorType(sld);
			DeleteAttribute(sld, "OfficerImmortal");
			if(CheckAttribute(sld, "Health.HP")) DeleteAttribute(sld, "Health.HP");
			if(CheckAttribute(sld, "Health.maxHP")) DeleteAttribute(sld, "Health.maxHP");
			sTemp = "RestoreHealth_" + sld.index;
			if(CheckAttribute(PChar, "quest.RestoreHealth_" + sld.index)) PChar.quest.(sTemp).over = "Yes";
			sld.lifeday = 0;
			LAi_CharacterDisableDialog(sld);
			GiveItem2Character(sld, "blade_42");
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			//LAi_ActorRunToLocation(sld, "reload", "reload1", "", "", "", "", -1);
			AddQuestRecord("BlackMark", "5");
			AddQuestUserData("BlackMark", "sSex1", GetSexPhrase("","а"));
			CloseQuestHeader("BlackMark");
		break;
		
		case "BM_IronsFirstJungle_1":
			dialog.text = "Ascolta, Capitano...";
			link.l1 = "Che succede, Tommy?";
			link.l1.go = "BM_IronsFirstJungle_2";
		break;
		
		case "BM_IronsFirstJungle_2":
			dialog.text = "Non avresti mica una cartuccia di riserva addosso? Non solo una pallottola, ma proprio una cartuccia intera, avvolta nella carta.";
			link.l1 = "È un altro dei tuoi scherzi, eh? Ti fornisco palle e cartucce ogni volta che vuoi, qualsiasi cosa ti serva. E perché ti serve proprio una cartuccia sola, e non una manciata?";
			link.l1.go = "BM_IronsFirstJungle_3";
		break;
		
		case "BM_IronsFirstJungle_3":
			dialog.text = "Perché prendi così male la mia richiesta? Non ti sto mica chiedendo perle maledette, solo una cartuccia. Ho pure aspettato finché eravamo nella giungla, così da non intralciarti con le tue faccende in città. Allora, ce l’hai una pallottola?";
			if (CheckCharacterItem(PChar, "cartridge"))
			{
				link.l1 = "Sì, ho preso un giro. Eccoti qua. Ma non provare a farmi uno scherzo da scemo con quella pallottola. Intesi, Tommy?";
				link.l1.go = "BM_IronsFirstJungle_7";
			}
			link.l2 = "In questo momento no, non ne ho. Non è che vada in giro con una cartuccia sola in tasca, sperando che magari Tommy me la chieda...";
			link.l2.go = "BM_IronsFirstJungle_4";
		break;
		
		case "BM_IronsFirstJungle_4":
			dialog.text = "Ebbene, hai colto nel segno, e sei sveglio come una faina, eh eh. Ma temo che qui le nostre strade si dividano, allora.";
			link.l1 = "Sei serio? Ti sei offeso per una pallottola? Suvvia, andiamo alla nave e te ne procuro una lì. Se ti serve così in fretta, te ne porto una, dieci, quante te ne servono.";
			link.l1.go = "BM_IronsFirstJungle_5";
		break;
		
		case "BM_IronsFirstJungle_5":
			dialog.text = "No.   In fondo, non hai nulla di straordinario. Un vero capitano sa sempre come sfamare e provvedere alla sua ciurma. Dunque, io me ne vado.";
			link.l1 = "E se fossimo in mare, senza più una goccia di rum, e tu ne volessi ancora? Scioglieresti la scialuppa per salpare via? O ti butteresti giù in acqua?";
			link.l1.go = "BM_IronsFirstJungle_6";
		break;
		
		case "BM_IronsFirstJungle_6":
			dialog.text = "Ah-ah-ah! Ho riso, ma in quest’ora mesta nemmeno una buona burla può sollevarmi. Addio, Capitano Noia.";
			link.l1 = "Al diavolo te, Tommy. Addio.";
			link.l1.go = "BM_IronsJungleUhodit";
		break;
		
		case "BM_IronsFirstJungle_7":
			dialog.text = "Non posso promettere nulla, eh eh. Una buona battuta alleggerisce l’aria. Ma grazie, davvero.";
			link.l1 = "D'accordo, andiamo, buffone.";
			link.l1.go = "BM_IronsFirstJungle_8";
			TakeItemFromCharacter(pchar, "cartridge");
		break;
		
		case "BM_IronsFirstJungle_8":
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
			Return_IronsOfficer();
			SetTimerCondition("BM_SecondJungle_Time", 0, 0, 7, false);
		break;
		
		case "BM_IronsSecondJungle_1":
			dialog.text = "Ehi, Capitano!";
			link.l1 = "Sì, Tommy?";
			link.l1.go = "BM_IronsSecondJungle_2";
		break;
		
		case "BM_IronsSecondJungle_2":
			dialog.text = "Hai un’altra cartuccia di carta?";
			link.l1 = "Che ne è stato dell'ultimo? E quella burla sulla cartuccia? Son due settimane che aspetto una tua dannata battuta, e ancora nulla.";
			link.l1.go = "BM_IronsSecondJungle_3";
		break;
		
		case "BM_IronsSecondJungle_3":
			dialog.text = "Oh, sarà una battuta da sganasciarsi, fidati. Ti piacerà, ahah. Non l’ho ancora pensata tutta, però. Allora, che mi dici della cartuccia?";
			if (CheckCharacterItem(PChar, "cartridge"))
			{
				link.l1 = "Ecco qua. Spero proprio che il tuo prossimo scherzo sia degno di внимания. E dove hai cacciato l’ultimo colpo? Te ne do in abbondanza, sai. O forse conservi le palle da sparo in un posto e quelle per gli scherzi in un altro?";
				link.l1.go = "BM_IronsSecondJungle_7";
			}
			link.l2 = "Non tengo polvere per le tue buffonate, Tommy! Due settimane fa potevi chiedere una cassa intera invece d’un solo colpo!";
			link.l2.go = "BM_IronsSecondJungle_4";
		break;
		
		case "BM_IronsSecondJungle_4":
			dialog.text = "L'ho fatto! Pensavo che chiunque si dica mio capitano tenga sempre conto di ciò che serve alla sua ciurma.";
			link.l1 = "Non fingo d’essere nessuno, Tommy. Ho scelto di restare me stesso tanto tempo fa. Chi mi accetta, bene. Chi no, pure bene.";
			link.l1.go = "BM_IronsSecondJungle_5";
		break;
		
		case "BM_IronsSecondJungle_5":
			dialog.text = "Ehi, tu ed io siamo tagliati della stessa stoffa, ragazzo. Ma ho certe pretese per chi mi comanda. E tu ormai non le soddisfi più, figliolo. Qui le nostre strade si dividono.";
			link.l1 = "Parli sul serio? Solo perché non avevo una dannata cartuccia di carta?";
			link.l1.go = "BM_IronsSecondJungle_6";
		break;
		
		case "BM_IronsSecondJungle_6":
			dialog.text = "Fuori questione. Di solito dico alla gente di fare quel che più gli aggrada e di prendere dalla vita ciò che desidera. Ma a te consiglio di pensare un po' di più ai tuoi uomini, in futuro. Addio.";
			link.l1 = "E ti consiglierei di badare alla tua testa – ti hanno conciato peggio di quanto pensi. Addio, Tommy.";
			link.l1.go = "BM_IronsJungleUhodit";
		break;
		
		case "BM_IronsSecondJungle_7":
			dialog.text = "Lo scoprirai. Tutto a suo tempo, eh eh.";
			link.l1 = "Ah, ho una brutta sensazione, Tommy...";
			link.l1.go = "BM_IronsSecondJungle_8";
			TakeItemFromCharacter(pchar, "cartridge");
		break;
		
		case "BM_IronsSecondJungle_8":
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
			Return_IronsOfficer();
			SetTimerCondition("BM_ThirdJungle_Time", 0, 0, 7, false);
		break;
		
		case "BM_IronsThirdJungle_1":
			dialog.text = "Ho una domanda per voi, Capitano.";
			link.l1 = "Ehilà, Tommy, che c’è?";
			link.l1.go = "BM_IronsThirdJungle_2";
		break;
		
		case "BM_IronsThirdJungle_2":
			dialog.text = "Non hai indovinato? Indovinare è un’arte preziosa, eh eh. Tu, io, la giungla... Circa due settimane fa, avevamo già questo discorso. Mi serve un’altra cartuccia di carta.";
			if (CheckCharacterItem(PChar, "cartridge"))
			{
				link.l1 = "Sta diventando una buffa tradizione, vero? Son già due settimane – Tommy chiede una cartuccia. Tieni, prendi. Quante te ne servono ancora per quella tua burla?";
				link.l1.go = "BM_IronsThirdJungle_5";
			}
			link.l2 = "Quanto ancora, Tommy?! Quanto dovremo aspettare? Voi Ironsides avete solo una cartuccia prima di ogni battaglia?! Non sono qui per portarmi sempre appresso una pallottola per i tuoi capricci, lo sai bene!";
			link.l2.go = "BM_IronsThirdJungle_3";
		break;
		
		case "BM_IronsThirdJungle_3":
			dialog.text = "In verità, come mio capitano, sta a te fornirmi tutto ciò che mi serve per le battaglie e non solo.";
			link.l1 = "Sei confuso, Tommy. Il tuo dovere è obbedire agli ordini del capitano. Vi fornisco sempre tutto – medicine, munizioni, rum. Se non prendi ciò che ti serve in tempo e poi ti lamenti come un mendicante, la colpa è solo tua!";
			link.l1.go = "BM_IronsThirdJungle_4";
		break;
		
		case "BM_IronsThirdJungle_4":
			dialog.text = "Sei così furbo – e allora perché non hai combinato nulla di memorabile qui finora? Te lo dico io. Perché non guardi mai avanti, e non sei mai preparato a nulla. Non sai nemmeno cosa stai facendo, noioso che non sei altro. Non riconoscerò mai uno così come mio comandante, quindi addio.";
			link.l1 = "E non usi per niente il cervello! Che ti porti via il diavolo, maledetto sciocco!";
			link.l1.go = "BM_IronsJungleUhodit";
		break;
		
		case "BM_IronsThirdJungle_5":
			dialog.text = "Questa andrà bene, eh eh.";
			link.l1 = "Allora, ti sei finalmente sistemato? Ma per far che, di grazia?";
			link.l1.go = "BM_IronsThirdJungle_6";
			TakeItemFromCharacter(pchar, "cartridge");
		break;
		
		case "BM_IronsThirdJungle_6":
			dialog.text = "Stavo solo scherzando con te, volevo vedere se tornavi subito il solito musone. Eh eh. Ma grazie per la cartuccia.";
			link.l1 = "I tuoi scherzi sono strani, Tommy.";
			link.l1.go = "BM_IronsThirdJungle_7";
		break;
		
		case "BM_IronsThirdJungle_7":
			dialog.text = "That was a joke too. I wasn't collecting them; I was selecting them. Needed a cartridge that was close to perfect. This one will do. Yeah, with this round, the bullet will go far and true. Just like when I blew old Reasley's head off, ha-ha-ha!";
			link.l1 = "Il vecchio Reasley, hai detto... Frankie il Cornuto, giusto? Quello a cui hai sparato al faro? Quindi vi conoscete da un bel pezzo, eh?";
			link.l1.go = "BM_IronsThirdJungle_8";
		break;
		
		case "BM_IronsThirdJungle_8":
			dialog.text = "Cosa? Oh, maledizione, mi è scappato. Ma poco me ne importa – non sono mai stato bravo a mentire o a tener segreti.";
			link.l1 = "Immagino che il secondo proiettile fosse destinato a qualcuno in particolare, vero, Tommy?";
			link.l1.go = "BM_IronsThirdJungle_9";
		break;
		
		case "BM_IronsThirdJungle_9":
			dialog.text = "Bene, genio. Io so chi sono e cosa voglio, e non me ne vergogno. Perciò poco m’importa quel che pensi tu – ti racconterò tutta la storia, dannazione, perché no.";
			link.l1 = "Ebbene, dimmi allora. Non farà male sapere in che guai ti sei cacciato.";
			link.l1.go = "BM_IronsThirdJungle_10";
		break;
		
		case "BM_IronsThirdJungle_10":
			dialog.text = "Ebbene, non interrompermi, come fai sempre. C’erano due felloni nella compagnia con me – Francis Reasley e Gabriel Callow. Veri canaglie! Peggio ancora di quei topi da scrivania che non volevano darmi il congedo, che, come sai, non fu affatto facile ottenere.";
			link.l1 = "E che cosa hanno fatto? Soprattutto il secondo, Callow. Hai messo le mani anche sulla moglie sua? E pure lui ti ha mandato i soldati dietro?";
			link.l1.go = "BM_IronsThirdJungle_11";
		break;
		
		case "BM_IronsThirdJungle_11":
			dialog.text = "Tieniti la lingua in bocca, vuoi? Anche se... non mi dispiacerebbe, eh eh. Ma no. I realisti ci assalirono quel giorno. Pure la cavalleria. Erano molti di più. Gabe e Frankie scapparono come conigli spaventati. Ma io rimasi coi ragazzi. Solo io sono sopravvissuto. Ho dimenticato molte cose della mia infanzia e giovinezza, ma non quella.";
			link.l1 = "E tu vuoi vendetta solo perché sono scappati? Non tutti combattono per un ideale. Tutti cercano di salvar la pelle. O quasi tutti. Anche chi si è unito alla Rivoluzione, magari l'ha fatto per sbaglio e ora se ne pente.";
			link.l1.go = "BM_IronsThirdJungle_12";
		break;
		
		case "BM_IronsThirdJungle_12":
			dialog.text = "Ah, se dovessi cacciare ogni codardo, dovrei sparare all’intero mondo. Che vadano all’inferno, i codardi. Ma loro mi hanno tradito. Hanno raccontato a tutti che io avevo venduto la Rivoluzione e massacrato la nostra compagnia su ordine dei leccapiedi del Re. Ti ho mentito su una cosa, Capitano.";
			link.l1 = "Che c'è? A parte il fatto che hai mentito su Frankie che ti dà la caccia solo per quello che hai combinato con sua moglie?";
			link.l1.go = "BM_IronsThirdJungle_13";
		break;
		
		case "BM_IronsThirdJungle_13":
			dialog.text = "No, no! Non ti ho mentito, semplicemente non ti ho raccontato tutto. C’è differenza. Quello su cui ho mentito è la storia delle dimissioni. Dimissioni non ce ne sono state. C’è stato un tribunale. E il vecchio Tommy, per sua fortuna – invece di impiccarlo, han deciso di spedirlo alle cave nelle colonie del sud. A Barbados, per l’esattezza.";
			link.l1 = "Eh già, ci è andata bene. Quanti anni hai servito lì?";
			link.l1.go = "BM_IronsThirdJungle_14";
		break;
		
		case "BM_IronsThirdJungle_14":
			dialog.text = "Nessuna. Da quando il tribunale terreno mi ha condannato per colpa di quei ratti, quello celeste lassù ha deciso di salvarmi. Appena abbiamo messo piede nell’Arcipelago, abbiamo sentito la sua aria – la nostra nave è stata abbordata da filibustieri.";
			link.l1 = "Quindi invece delle cave e delle piantagioni di Barbados, sei stato venduto come schiavo dai pirati? Ma hai detto che non hai mai lavorato nelle cave.";
			link.l1.go = "BM_IronsThirdJungle_15";
		break;
		
		case "BM_IronsThirdJungle_15":
			dialog.text = "Proprio così ho detto – qualcuno lassù ha deciso di darmi una mano. Che salvataggio, ahah! Hai capito bene – i pirati hanno avuto la meglio su quei bastardi che si divertono a tormentare uomini incatenati. Ma la battaglia è stata rovente, bollente come il sole di queste terre. E pure i nostri salvatori ci hanno rimesso qualche uomo. Così han proposto a chi voleva di salire a bordo con loro.";
			link.l1 = "E allora ti sei unito a loro? Hai detto che navigavi coi pirati.";
			link.l1.go = "BM_IronsThirdJungle_16";
		break;
		
		case "BM_IronsThirdJungle_16":
			dialog.text = "Per tutti i diavoli! Quelli sì che erano anni d’oro, i migliori della mia vita. Jack Mills era un capitano, con la C maiuscola — spero che un giorno sarai come lui. Ho navigato sulla sua 'Gru' per quasi due anni, finché...";
			link.l1 = "... finché non ti sei stufato dell’anarchia, come hai detto? Perché dici che quelli furono gli anni più belli della tua vita?";
			link.l1.go = "BM_IronsThirdJungle_17";
		break;
		
		case "BM_IronsThirdJungle_17":
			dialog.text = "Eh... fino a quando non ho sentito dire che quei due traditori sono finiti pure loro nell’Arcipelago. Sì, lo so, ti avevo detto che ne avevo abbastanza della pirateria d’alto mare e tutto il resto. E t’ho già detto che non m’importa nulla di quel che pensi. Questo è vero ancora, ma quando ci siamo conosciuti non ti conoscevo bene. Non sapevo come avresti reagito. Ecco perché ti ho raccontato storie diverse.";
			link.l1 = "Sei un bugiardo, Tommy! Ma va bene, perché hai mollato la 'Gru'?";
			link.l1.go = "BM_IronsThirdJungle_18";
		break;
		
		case "BM_IronsThirdJungle_18":
			dialog.text = "Perché Jack era un vero capitano, così disse che non avrebbe deviato la rotta per un solo uomo, né aspettato, né sprecato il tempo per vendette, né si sarebbe messo a stuzzicare ufficiali importanti della Marina Britannica invece di dare la caccia ai ricchi mercantili.";
			link.l1 = "Ufficiali di spicco? Frank era un semplice civile, mi pare.";
			link.l1.go = "BM_IronsThirdJungle_19";
		break;
		
		case "BM_IronsThirdJungle_19":
			dialog.text = "Eh, non è sempre stato così. Era sempre un tipo, sai, losco. E quando ha provato a fregare qualcuno, l'hanno cacciato a calci nel sedere. Ha tentato di imbarcarsi su una nave mercantile, ma il lavoro onesto non faceva per lui. Alla fine è venuto a piantare le tende qui.";
			link.l1 = "Non lo definirei certo un ufficiale di spicco.";
			link.l1.go = "BM_IronsThirdJungle_20";
		break;
		
		case "BM_IronsThirdJungle_20":
			dialog.text = "Non ti scordar di Gabe. Ha fatto il tenente nella madrepatria. E qui a Port Royal ha ricevuto la patente da capitano della nave, la 'Principio'.";
			link.l1 = "Non mi pare molto inglese.";
			link.l1.go = "BM_IronsThirdJungle_21";
		break;
		
		case "BM_IronsThirdJungle_21":
			dialog.text = "Giusta osservazione! La nave è passata di mano in mano come una sgualdrina da porto, e ne ha viste di tutti i colori. Ma tiene ancora il mare. E Gabe è un capitano coi fiocchi, maledetto lui.";
			link.l1 = "E Jack aveva paura di trattare con lui? È davvero così in gamba come dici?";
			link.l1.go = "BM_IronsThirdJungle_22";
		break;
		
		case "BM_IronsThirdJungle_22":
			dialog.text = "Va bene, va bene! Più che altro non voleva perdere tempo per colpa mia. A proposito di Jack, mi son piaciute alcune usanze che ho visto da lui per la prima volta – la passerella e il distribuire i marchi neri. All’epoca mi venne in mente una trovata buffa per colpa di ciò.";
			link.l1 = "Macchie... nere? Intendi una macchia nera, vero? E che cos’era, Tommy? Non credo che saprebbe cosa fare se gli avessi dato una macchia nera. È così che è andata? Hai voluto consegnargliela, e lui ti ha assalito appena ti ha visto, così sei corso al faro, e lui ha portato con sé una squadra di soldati, dicendo loro che eri un filibustiere?";
			link.l1.go = "BM_IronsThirdJungle_23";
		break;
		
		case "BM_IronsThirdJungle_23":
			dialog.text = "Preferisco chiamarla una macchia nera. Suona meglio, no? Una semplice macchia nera non gli avrebbe fatto capire un bel niente. Ma una macchia fatta col nostro fazzoletto di seta, il segno distintivo della nostra compagnia – quello sì che avrebbe capito. Gliel’ho infilata in tasca senza farsi accorgere. Poi mi sono assicurato che mi vedesse dirigermi verso il faro. Il resto lo sai già.";
			link.l1 = "E gli contrabbandieri?";
			link.l1.go = "BM_IronsThirdJungle_24";
		break;
		
		case "BM_IronsThirdJungle_24":
			dialog.text = "Posto sbagliato, momento sbagliato. Un po’ mi sono persino dispiaciuto per loro. Ma solo un pochino, eh eh.";
			link.l1 = "E per Frankie?";
			link.l1.go = "BM_IronsThirdJungle_25";
		break;
		
		case "BM_IronsThirdJungle_25":
			dialog.text = "Chi se ne frega adesso? Abbiamo guai più grossi da affrontare. Resta Gabe. Quella sarà dura. Dobbiamo...";
			link.l1 = "Noi?";
			link.l1.go = "BM_IronsThirdJungle_26";
		break;
		
		case "BM_IronsThirdJungle_26":
			dialog.text = "Ebbene, ascoltare una storia è una cosa, ma crearne una con le proprie mani è tutt’altra! Dunque, ecco il piano. Dobbiamo lasciare a Gabe un altro marchio nero speciale – ne ho già preparato uno. Poi seguiremo le sue orme fino a Portland Cove, dove gli daremo una lezione senza lasciare tracce.";
			link.l1 = "E dove andremo a piantarlo?";
			link.l1.go = "BM_IronsThirdJungle_27";
		break;
		
		case "BM_IronsThirdJungle_27":
			dialog.text = "Ah ah ah, è proprio questo che intendevo quando dicevo che avrei voluto che tu fossi più come Jack, Capitano. Su, non fare il pesce lesso, vedo che hai lo sguardo che brucia!";
			link.l1 = "Anzi, la tua storia mi ha incuriosito un po'.";
			link.l1.go = "BM_IronsThirdJungle_28";
		break;
		
		case "BM_IronsThirdJungle_28":
			dialog.text = "A casa sua, naturalmente! Che domande fai? Si è sistemato a Port Royal. Quindi tu ed io attraccheremo nella cala, così da poter mollare l’isola se qualcosa va storto.";
			link.l1 = "Sai dove si trova la sua dimora?";
			link.l1.go = "BM_IronsThirdJungle_29";
		break;
		
		case "BM_IronsThirdJungle_29":
			dialog.text = "No. Ma non sarà difficile scoprirlo. Basterà chiedere agli ubriaconi – venderebbero la madre per una pinta o due. Allora, che ne pensi del mio piano?";
			if (GetSummonSkillFromName(pchar, SKILL_ACCURACY) > 24 && GetSummonSkillFromName(pchar, SKILL_GRAPPLING) > 24 && GetSummonSkillFromName(pchar, SKILL_SAILING) > 24)
			{
				link.l1 = "Se è il capitano di una nave diretta in Giamaica, pattuglia di continuo le acque dell’isola. Meglio assalire sotto falsa bandiera che rischiare qualcosa in città.";
				link.l1.go = "BM_IronsThirdJungle_Sea1";	// Морской вариант
				notification("Skill Check Passed", SKILL_SAILING);
				notification("Skill Check Passed", SKILL_ACCURACY);
				notification("Skill Check Passed", SKILL_GRAPPLING);
			}
			else
			{
				if (GetSummonSkillFromName(pchar, SKILL_SAILING) < 25) notification("Skill Check Failed (25)", SKILL_SAILING);
				if (GetSummonSkillFromName(pchar, SKILL_ACCURACY) < 25) notification("Skill Check Failed (25)", SKILL_ACCURACY);
				if (GetSummonSkillFromName(pchar, SKILL_GRAPPLING) < 25) notification("Skill Check Failed (25)", SKILL_GRAPPLING);
			}
			link.l2 = "Non è privo di difetti, e lasci un bel po' al caso. Ma tutto sommato, si può fare. Sono con te, Tommy. Ne hai tolto uno di mezzo, non puoi mica lasciare l’altro libero, vero?";
			link.l2.go = "BM_IronsThirdJungle_Land1";	// Сухопутный вариант
			link.l3 = "Non mi immischio nella tua vendetta né rischio la mia posizione con l’Inghilterra per questa tua impresa dove il destino gioca a dadi, Tommy.";
			link.l3.go = "BM_IronsThirdJungle_Otkaz1";	// Отказ
		break;
		
		case "BM_IronsThirdJungle_Sea1":
			dialog.text = "Sei un tipo audace, Capitano! Cominci a piacermi. Ma Gabe sulla vecchia 'Principio' non è una preda facile – è molto più pericoloso degli altri capitani con una nave simile.";
			link.l1 = "Che credi che sia, uno smidollato, Tommy? Lo abbordiamo noi stessi, così potrai sputargli in faccia la verità. Dagli il marchio nero prima che lo scaraventino giù.";
			link.l1.go = "BM_IronsThirdJungle_Sea2";
		break;
		
		case "BM_IronsThirdJungle_Sea2":
			dialog.text = "Ehi, forse tu non sei un codardo, ma lui sì, anche se è furbo. Non si metterà mai contro un soldato o un filibustiere con una nave più grossa della sua. Se scorge qualcosa del genere all’orizzonte, si ficca subito sotto l’ala del forte.";
			link.l1 = "Uhm, che mi dici delle navi mercantili?";
			link.l1.go = "BM_IronsThirdJungle_Sea3";
		break;
		
		case "BM_IronsThirdJungle_Sea3":
			dialog.text = "Sì, potrebbe andare! Ma niente di più grosso d'una barca o d'un brigantino, mi raccomando! Gabe non è soltanto un codardo – non è mai stato abbastanza avido da lasciar vincere la prudenza.";
			link.l1 = "Speriamo che funzioni, Tommy. Allora, una barca di quinta categoria o una barquentina sotto bandiera spagnola o olandese. Preparati a incontrare il tuo vecchio compagno d’armi!";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_SeaVariant");
		break;
		
		case "BM_IronsThirdJungle_Land1":
			dialog.text = "Sapevo che potevo contare su di te! Un giorno potresti anche diventare un capitano migliore di Jack. Quanto alla mia fortuna... mi ha portato fin qui, quindi ci farò ancora affidamento. Allora, salpiamo?";
			link.l1 = "Sì, non tiriamo troppo per le lunghe. Prima la facciamo finita, meglio è.";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_LandVariant");
		break;
		
		case "BM_IronsThirdJungle_Otkaz1":
			dialog.text = "Eheh, speravo il contrario, ma me l’aspettavo — non hai fegato per questo genere di faccende, "+GetSexPhrase("giovanotto","la mia ragazza")+"Ogni vero capitano ha dovuto, prima o poi, sistemare qualche topo sottobanco. E a volte pure i suoi stessi topi.";
			link.l1 = "Suppongo che dovrei cadere in quella provocazione e dire che ho cambiato idea e che ti mostrerò di essere un vero capitano, eh, Tommy? Ma capisco la tua sete di vendetta. Non ti sbatterò fuori dall’equipaggio come ha fatto Jack. Quanto tempo ti serve per sistemare la faccenda? Io arriverò in Giamaica per allora.";
			link.l1.go = "BM_IronsThirdJungle_Otkaz2";
		break;
		
		case "BM_IronsThirdJungle_Otkaz2":
			dialog.text = "Ah ah ah, stai diventando grande. Quasi ti rispetto per non esserci cascato. Ma non serve che aspetti per raccogliermi dopo – me la caverò da solo. In fondo, tutto ciò che ho sempre voluto è qualcuno disposto a fare qualcosa per me come mio capitano. Quindi addio. Prenditi cura dell’Inghilterra, ah-ah.";
			link.l1 = "Sei davvero strano. Ma come vuoi tu. Addio! E che la fortuna ti assista nella tua vendetta, Tommy.";
			link.l1.go = "BM_IronsThirdJungle_Otkaz3";
		break;
		
		case "BM_IronsThirdJungle_Otkaz3":
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
			
			sld = characterFromID("Irons");
			RemovePassenger(pchar, sld);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "", "", "", "", -1);
			sld.location = "None";
			AddQuestRecord("BlackMark", "6");
			AddQuestUserData("BlackMark", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("BlackMark", "sSex1", GetSexPhrase("к","чка"));
			CloseQuestHeader("BlackMark");
		break;
		
		case "BM_IronsJamaicaShore1":
			dialog.text = "Perfetto, da qui possiamo battere in ritirata in un lampo, se sarà necessario. Prendi questo — consegna la lettera a Gabe e dagliela insieme al segno nero, appena scopri dove abita e quando lo trovi in casa.";
			link.l1 = "Oh, quindi adesso comandi tu, Tommy. Ma rammenta, sono ancora il tuo capitano. Cosa hai intenzione di fare mentre io sono in città?";
			link.l1.go = "BM_IronsJamaicaShore2";
		break;
		
		case "BM_IronsJamaicaShore2":
			dialog.text = "Heh, come potrei scordarmelo, Capitano Noioso? Se Gabe mi vede per strada, o darà l’allarme o filerà via dall’isola, quel maledetto codardo. Non temere, gli tenderò un agguato proprio qui, eheheh.";
			link.l1 = "Un’imboscata, dici tu. Va bene, Tommy. Diamogli il bentornato che si merita, al tuo vecchio compagno d’armi, ah ah ah ah!";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_IronsJamaicaGo");
		break;
		
		case "BM_Pyanitsa_0":
			dialog.text = "Hic! Che rum portentoso! Hic... Alla salute!";
				link.l1 = "Ascolta, compare, che si dice in città del capitano Gabriel Callow?";
			link.l1.go = "BM_Pyanitsa_1";
			DelLandQuestMark(npchar);	//Удаляем квестмарку
		break;
		
		case "BM_Pyanitsa_1":
			dialog.text = "Vecchio Gabe?! Solo cose buone! Ehi, hic, che c'è?";
			link.l1 = "Ah, davvero? Son lieto di saperlo. Vedi, c’è una grana con un filibustiere. Il Comandante si occupa più che altro di faccende di terra, e non vorrei disturbare Sua Signoria.";
			link.l1.go = "BM_Pyanitsa_2";
		break;
		
		case "BM_Pyanitsa_2":
			dialog.text = "Allora vai dritto da Gabe, te lo dico io! Non troverai capitano più leale o coraggioso in questa città di Gabe. Perfino il colonnello Doyley lo tiene in gran conto. Naviga con una nave che fu di Nicolas Sharp in persona, riesci a crederci?";
			link.l1 = " Non sono ancora abbastanza ciucco per crederci, compare.";
			link.l1.go = "BM_Pyanitsa_3";
		break;
		
		case "BM_Pyanitsa_3":
			dialog.text = "A-Ah, ma certo che sì! È il Principio! Ti dice qualcosa, eh?";
			link.l1 = "Una nave trofeo spagnola, dici? Perché mai?";
			link.l1.go = "BM_Pyanitsa_4";
		break;
		
		case "BM_Pyanitsa_4":
			dialog.text = "Quand’è stata l’ultima volta che hai visto un rosa coi tuoi occhi, eh? So di quel che parlo, dannazione!";
			link.l1 = "Beh, non so se il progetto della nave sia poi così fuori dal comune.";
			link.l1.go = "BM_Pyanitsa_5";
		break;
		
		case "BM_Pyanitsa_5":
			dialog.text = "Ma lo è davvero! Nessun cane comanderebbe una simile baracca, con tutti questi nuovi modelli in giro! Hanno smesso di costruirle nei cantieri quasi t-trent’anni fa! Nic l’ha portata lui stesso, ti dico.";
			link.l1 = "D'accordo, la prendo. Quindi, questa è la nave. Com'è che questa carcassa non si è ancora sfasciata?";
			link.l1.go = "BM_Pyanitsa_6";
		break;
		
		case "BM_Pyanitsa_6":
			if (sti(pchar.basenation) == ENGLAND) sStr = "our";
			else sStr = "your";
			dialog.text = "Beh, non è più veloce come nei suoi giorni migliori – proprio come me dopo un altro bicchiere, ah-ah-ah! Ma un buon capitano può ancora tirar fuori qualcosa da questa vecchia signora. Gabe cerca pure di non metterla troppo sotto il fuoco nemico.";
			link.l1 = "E allora perché la nave non è stata ribattezzata? Magari Sua Maestà la Sferzante, sotto "+sStr+" vecchio regime?";
			link.l1.go = "BM_Pyanitsa_7";
		break;
		
		case "BM_Pyanitsa_7":
			dialog.text = "Tradi... Tradi-tradi-tradizione, ahimè! Nemmeno Nic in persona ebbe mai il coraggio di rinominarla dopo la fuga da quella piantagione spagnola a Cuba. Non voleva mai scordare quell'inferno – e neppure quegli spagnoli! Lascia ch’io ti narri di quella battaglia vicino alle coste di Tendales...";
			if (startHeroType == 4)
			{
				link.l1 = "Tendales, eh? Eh, l’ultima volta che ho sentito quel nome avevo ancora i calzoni corti. Non pensavo che ci fosse ancora anima viva che si ricordasse di quelle rocce abbandonate.";
				link.l1.go = "BM_Pyanitsa_8";
			}
			else
			{
				link.l1 = "Tendales? Dove si trova questa dannata tana?";
				link.l1.go = "BM_Pyanitsa_8";
			}
		break;
		
		case "BM_Pyanitsa_8":
			dialog.text = "O forse era, uh, Highrock? N-no, di certo non là... Ma che importa! Nic combatté e vinse in quel porto rosa, una vittoria incredibile contro la brigantina Seppia, mandata dietro di lui da Desmond Ray Beltrop, Barone dei Pirati. Si rovinarono la vita a vicenda per un bel pezzo, finché Nic non fece fuori lo stesso Desmond.";
			if (startHeroType == 4)
			{
				link.l1 = "Accidenti, che roba! Anche se, da Nicholas non ci si aspetterebbe altro. Eh, gli Sharps e i Beltrops sempre insieme, poi di nuovo separati – pare proprio che la storia si ripeta di tanto in tanto.";
				link.l1.go = "BM_Pyanitsa_9";
			}
			else
			{
				link.l1 = "Impressionante. Dunque, come si separò Sharp dalla nave? La vendette al cantiere navale?";
				link.l1.go = "BM_Pyanitsa_9";
			}
		break;
		
		case "BM_Pyanitsa_9":
			dialog.text = "No. Dopo quell'abbordaggio, ha cominciato a imbarcare acqua, così Nic l'ha lasciata. Poi con l'alta marea, la rosa è finita sulla spiaggia, proprio vicino alla città.";
			link.l1 = "Come se a qualcuno fregasse qualcosa di quel relitto.";
			link.l1.go = "BM_Pyanitsa_10";
		break;
		
		case "BM_Pyanitsa_10":
			dialog.text = "Oh, ma la Marina s’è fatta avanti, altroché! Gente pratica, loro. Han visto una nave con la bandiera d’Inghilterra ma col nome spagnolo, e s’è accesa la curiosità. Nic è crepato qualche anno dopo, ma la sua nave ha continuato a solcare i mari, passando di mano in mano, sempre in mezzo al sangue.";
			link.l1 = "Questa è solo un'altra storia di navi fantasma, mentre il comando di Gabe è ben reale. Penso che andrò a trovarlo. Sai dove abita?";
			link.l1.go = "BM_Pyanitsa_11";
		break;
		
		case "BM_Pyanitsa_11":
			dialog.text = "Ah-ah! Certo, hic, che lo so! Tutti lo sanno! Il vecchio Gabe sta vicino al vecchio mulino a vento. Basta che giri intorno alla taverna e alzi lo sguardo... hic!";
			link.l1 = "Quando torna a casa? Pare sia un uomo sempre in giro.";
			link.l1.go = "BM_Pyanitsa_12";
		break;
		
		case "BM_Pyanitsa_12":
			dialog.text = "Proprio così, compare! Ha un sacco di faccende da sbrigare. Lo trovi a casa solo la sera, dalle dieci in poi. E si sveglia alle sei in punto, ogni singolo giorno, senza che nessuno lo scuota. Una disciplina di ferro!";
			link.l1 = "Grazie di cuore! Per ora ne ho abbastanza di queste storie di pirati.";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_SearchGabeHouse");
		break;
		
		case "BM_Callow1":
			if (startHeroType == 4) 
			{
				dialog.text = "Sei davvero... Rumba? Ho sentito parlare di te... ma non hai mai tradito i tuoi, finora!";
				link.l1 = "E io non l’ho fatto. Non ce l’ho con il mio paese. Ce l’ho con te, Gabe.";
				link.l1.go = "BM_Callow_Helena1";
			}
			else
			{
				dialog.text = "Non sei un mercante...";
				link.l1 = "Sorpresa, Gabe! M'hanno detto che eri prudente, persino vigliacco. Ma l'avidità t'ha annebbiato il cervello, eh? Nessun mercante si butterebbe all'abbordaggio come ho fatto io.";
				link.l1.go = "BM_Callow2";
			}
		break;
		
		case "BM_Callow_Helena1":
			dialog.text = "Con me? Qual è il problema? Potremmo parlare da veri gentiluomini, magari a casa mia... o alla tua, da veri capitani, e... Ma che ci fai TU qui?!";
			link.l1 = "";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_CabinDialog");
		break;
		
		case "BM_Callow2":
			dialog.text = "Già. E tu chi saresti? Anzi, al diavolo tu... Ma chi diavolo è quello là...";
			link.l1 = "";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_CabinDialog");
		break;
		
		case "BM_IronsClone1":
			dialog.text = "Thomas, sei tu...?";
			link.l1 = "Oh sì, Gabe. E sono venuto a farti pagare per quello che mi hai fatto quel giorno.";
			link.l1.go = "BM_IronsClone2";
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			CharacterTurnByChr(sld, CharacterFromID("IronsClone"));
			sld = CharacterFromID("IronsClone");
			CharacterTurnByChr(sld, &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)]);
		break;
		
		case "BM_IronsClone2":
			dialog.text = "Punirmi?! Bada a come parli, Thomas! Se qualcuno qui merita una lezione, quello sei tu! Hai promesso rinforzi! E noi siamo rimasti lì ad aspettare, crepando sotto i piombi e le lame della cavalleria del Re!";
			link.l1 = "Ho corso come un dannato per portare aiuto! Ma sono stato raggiunto da un’altra maledetta banda! I maledetti seguaci di Charles erano ovunque! M’hanno accerchiato, per poco non ci lasciavo la pelle! Fortuna che m’hanno creduto stecchito. Ma sai che ho visto, Gabe?!";
			link.l1.go = "BM_IronsClone3";
		break;
		
		case "BM_IronsClone3":
			dialog.text = "Che c’è, Tom? Sei disposto a inventarti qualsiasi storia pur di far credere a quest’uomo?!";
			link.l1 = "Ehi, quell'uomo non mi tradirà mai. Non è una canaglia come certi altri.";
			link.l1.go = "BM_IronsClone4";
		break;
		
		case "BM_IronsClone4":
			dialog.text = "Non ha altra scelta! Attaccare una nave della marina inglese!";
			link.l1 = "Oh, lui aveva una scelta fin dall'inizio. E ha scelto di aiutarmi. Anche tu e Frankie avevate una scelta. Avete scelto di fuggire per non crepare. Poi siete tornati e mi avete trovata mezza morta. E avete raccontato le vostre luride menzogne al tribunale. Sapevate che nessuno mi avrebbe dato ascolto, visto che avevo preso una botta in testa e perso la memoria!";
			link.l1.go = "BM_IronsClone5";
		break;
		
		case "BM_IronsClone5":
			dialog.text = "Nessuno ti avrebbe dato retta comunque. Sei sempre stato un... rottame, Thomas.";
			link.l1 = "Oh, quindi non ti vergogni di ciò che hai fatto quel giorno. Ho qualcosa per te, Gabe. Un marchio nero. Ma che senso ha darti ‘sta roba ora che la nave è stata presa e che tra poco ti sventriamo le budella, ah ah ah ah ah ah ah...";
			link.l1.go = "BM_IronsClone6"; // здесь переход на кейс с боёвкой
		break;
		
		case "BM_IronsClone6":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			locCameraTarget(PChar);
			locCameraFollow();
			DeleteAttribute(pchar, "GenQuest.BlockDialogCamera");
			
			sld = CharacterFromID("IronsClone");
			LAi_SetCheckMinHP(sld, 1, true, "");
			LAi_SetCurHPMax(sld);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocator(sld, "reload", "reload1", "BM_IronsCloneMushket", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			LAi_SetImmortal(sld, false);
			LAi_SetCurHPMax(sld);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "BM_CabinDialog4");
		break;
		
		case "BM_IronsClone8":
			dialog.text = "Ebbene, Gabe è stato fatto fuori, hehehe. Era tanto che volevo dirlo. Peccato che tu non possa più sentirlo, compare. Ah, aspetta! Magari lo sentirai — dall’Inferno.";
			link.l1 = "Dai, Tommy. Anche se non l’ha sentito, ha visto e capito che era proprio la tua macchinazione e vendetta. E non poteva farci un accidente.";
			link.l1.go = "BM_IronsClone9";
		break;
		
		case "BM_IronsClone9":
			if (startHeroType == 4) 
			{
				dialog.text = "Ehi, hai proprio ragione! Maledizione, sì! Grazie per avermi tirato fuori da questo pasticcio. Sai, pensavo fossi solo una ragazzetta viziata con abiti sgargianti e una nave per divertirsi. Ma sei proprio un capitano coi fiocchi! Scommetto che daresti filo da torcere persino a Jack.";
			}
			else
			{
				dialog.text = "Ehi, hai ragione! Maledizione, è proprio così! Grazie per avermi tirato fuori da questo guaio. Sai, credo che tu sia un capitano in gamba quanto Jack. O forse anche meglio!";
			}
			link.l1 = "Oh, adesso mi lusinghi. Ti ringrazio. Suppongo.";
			link.l1.go = "BM_IronsClone10";
		break;
		
		case "BM_IronsClone10":
			dialog.text = "Per niente. Niente lusinghe, te lo assicuro. Come avrai notato, non mi capita spesso di parlare così di qualcuno. Quindi chiudi quel becco e ringrazia il cielo che ti tengo in così alta considerazione.";
			link.l1 = "Non direi che mi piaccia il modo in cui lo presenti, anche se mi fa piacere che in generale tu pensi che io sia un buon capitano. Ma... la catena di comando, Tommy, la catena di comando.";
			link.l1.go = "BM_IronsClone11";
		break;
		
		case "BM_IronsClone11":
			if (startHeroType == 4) 
			{
				dialog.text = "Ma dai! Tutto quel che abbiamo passato ci ha legati, Ellie. Potremmo essere più che solo capitano e ufficiale. Ammettilo, anche solo dentro di te... lo senti anche tu.";
				link.l1 = "Solo nei tuoi sogni più sfrenati, Tommy. E il mio nome è Helen, non Ellie. Ma suppongo che ora puoi chiamarmi Rumba.";
				link.l1.go = "BM_IronsClone12";
			}
			else
			{
				dialog.text = "Oh, dai, smidollato! Ormai non siamo più solo un capitano e il suo ufficiale, ma veri compagni di ventura. Non lo pensi anche tu?!";
				link.l1 = "Eh. Può darsi. Meglio essere tuo amico che tuo nemico, questo è certo. E visto che le buone maniere non fanno proprio per te, suppongo che dovrò abituarmici.";
				link.l1.go = "BM_IronsClone12";
			}
		break;
		
		case "BM_IronsClone12":
			dialog.text = "Ho un... regalino per te, Capitano.";
			link.l1 = "Ohibò, guarda un po’! Una macchia nera? Vuoi che mi destituiscano anche a me, eh, Tommy? Vuoi diventare capitano tu, furfante? Ah-ah-ah-ah! E pensare che dicevi che eravamo fratelli di ciurma.";
			link.l1.go = "BM_IronsClone13";
			GiveItem2Character(PChar, "talisman15");		//Предмет Чёрная Метка
		break;
		
		case "BM_IronsClone13":
			dialog.text = "È un MARCHIO nero, testa di cazzo. Lo sai, comincio a pensare che appena ho ricamato il teschio e le ossa su questo fazzoletto, abbia iniziato a portarmi fortuna. Non so spiegare come. Prendilo. E poi... se vuoi, puoi sempre prendere in prestito la mia fidata spada e l’armatura... quel che ne resta, ah-ah! Ti tornerà utile! Farai strada, ragazzo. E io voglio vederlo coi miei occhi. Non voglio che ti faccia ammazzare da una pallottola vagante.";
			link.l1 = "Grazie, compare! Farò del mio meglio. E tu – guarda e impara, ahah!";
			link.l1.go = "BM_IronsClone14";
		break;
		
		case "BM_IronsClone14":
			dialog.text = "Ammirare, certo, ah-ah-ah. Aye. Allora, che hai deciso di fare con questa nave? Da una parte, ormai serve a poco. Dall’altra, non ce ne sono più così. E dubito che ne vedremo mai un’altra simile.";
			if (startHeroType == 4) 
			{
				link.l1 = "Non ho ancora deciso... Sai, Tommy, sento una specie di legame con questa nave. Non so spiegartelo. Prima di tutto, togliamo dal ponte questo cadavere puzzolente. Se non ci sono falle nella stiva, forse mi terrò questa fanciulla per me.";
			}
			else
			{
				link.l1 = "Non lo so, Tommy. Non ho ancora deciso. Intanto, sbarazziamoci del corpo di Gabe. Non si sa mai che decidiamo di tenerci la nave.";
			}
			link.l1.go = "BM_IronsClone15";
		break;
		
		case "BM_IronsClone15":
			DialogExit();
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
		break;
		
		case "BM_IronsPinkPotopil1":
			dialog.text = "Ebbene, hai fatto un bel lavoro con quella vecchia carretta, Capitano! E anche se avrei voluto finire Gabe con le mie stesse mani, non provocherò l’ira del Creatore sminuendo questa vittoria.";
			link.l1 = "Non ce n'è bisogno, Tommy. Spero che la tua anima ora riposi in pace.";
			link.l1.go = "BM_IronsPinkPotopil2";
		break;
		
		case "BM_IronsPinkPotopil2":
			if (startHeroType == 4) 
			{
				dialog.text = "Sento che tutto quello che abbiamo passato ci ha avvicinati, Ellie. Potremmo essere più che solo capitano e ufficiale. Ammettilo – anche solo dentro di te, lo senti pure tu.";
				link.l1 = "Solo nei tuoi sogni più sfrenati, Tommy. E il mio nome è Helen, non Ellie. Ma suppongo che tu possa chiamarmi Rumba adesso, se la smetti con queste smancerie.";
			}
			else
			{
				dialog.text = "Non sono mai stato così felice in vita mia! Grazie per avermi tirato fuori da questo guaio. Sai, credo che tu sia bravo come Jack a comandare una nave. Anzi, forse anche meglio!";
				link.l1 = "Oh, mi lusinghi. Ti ringrazio anche per il paragone, suppongo.";
			}
			link.l1.go = "BM_IronsPinkPotopil3";
		break;
		
		case "BM_IronsPinkPotopil3":
			if (startHeroType == 4) 
			{
				dialog.text = "Per niente. Niente lusinghe, te lo assicuro. Avrai già notato che è raro che io parli bene di qualcuno. Quindi taci e sii fiero che ti tenga in così alta considerazione.";
				link.l1 = "Non direi che mi piaccia come l’hai messa, ma mi fa piacere che in generale tu mi consideri un buon capitano. Però... la catena di comando, Tommy, la catena di comando.";
			}
			else
			{
				dialog.text = "Affatto. Nessuna adulazione, per niente. Avrai già notato che non spendo spesso certe lodi. Quindi chiudi il becco e sii contento che ti tenga in così alta considerazione.";
				link.l1 = "Non direi che mi piaccia come l'hai messa, ma sono lieto che tu, in generale, mi consideri un buon capitano. Però... la catena di comando, Tommy, la catena di comando.";
			}
			link.l1.go = "BM_IronsPinkPotopil4";
		break;
		
		case "BM_IronsPinkPotopil4":
			if (startHeroType == 4) 
			{
				dialog.text = "Oh, andiamo, che noia! Ormai tra noi non c’è solo un capitano e il suo ufficiale, ma veri amici, per mille balene! Non lo pensi anche tu?!";
				link.l1 = "Heh. Forse. Meglio essere tuo amico che nemico, sai. E visto che le buone maniere non fanno proprio per te, mi toccherà abituarmici, suppongo.";
			}
			else
			{
				dialog.text = "Oh, andiamo, che noia! Ormai mi pare che tra noi non ci sia più solo capitano e ufficiale, ma la più vera delle amicizie. Non credi anche tu?!";
				link.l1 = "Heh. Forse. È meglio essere tuo amico che tuo nemico. E visto che le buone maniere non fanno per te, suppongo che dovrò solo abituarmici.";
			}
			link.l1.go = "BM_IronsPinkPotopil5";
		break;
		
		case "BM_IronsPinkPotopil5":
			if (startHeroType == 4) 
			{
				dialog.text = "Ho un... regalo per te, Capitano.";
			}
			else
			{
				dialog.text = "Ho un... regalino per te, Capitano.";
			}
			link.l1 = "Ohé, guarda un po'! Una macchia nera? Vuoi spodestarmi anche tu, eh, Tommy? Vuoi diventare capitano al mio posto? Ah-ah-ah-ah! E io che pensavo fossimo compagni.";
			link.l1.go = "BM_IronsPinkPotopil6";
		break;
		
		case "BM_IronsPinkPotopil6":
			dialog.text = "È un MARCHIO nero, testa di cazzo. Sai, inizio a credere che da quando ho ricamato il teschio e le ossa su questa sciarpa, mi porti fortuna. Non so spiegartelo. Tienila. E poi... se vuoi, puoi sempre prenderti in prestito la mia fedele spada e l’armatura... quel che ne resta, ah-ah! Ti sarà utile! Farai strada. E voglio vederlo coi miei occhi. Non voglio che ti freghino con una palla vagante.";
			link.l1 = "Grazie, compare! Farò del mio meglio. E tu - guarda e impara, ah-ha-ha!";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_PinkPotopil_4");
			GiveItem2Character(PChar, "talisman15");		//Предмет Чёрная Метка
		break;
		
		case "BM_GabeHouseGood1":
			notification("Reputation Check Passed", "None");
			if (startHeroType == 4)
			{
				dialog.text = "Chi mai crederebbe a una cosa simile... Perdoni, signorina. "+TimeGreeting()+". Come posso aiutarti? Hai l’aria d’avere una tempesta nell’anima.";
			}
			else
			{
				dialog.text = "Cosa? Chi si fa vedere a quest’ora tarda? Sembri alquanto agitato, signore. In che posso servirvi?";
			}
			link.l1 = "Perdonate se interrompo il vostro riposo, Capitano Callow. Il mio nome è "+GetFullName(pchar)+", e vengo a nome di uno dei tuoi vecchi compagni d'arme.";
			link.l1.go = "BM_GabeHouseGood2";
		break;
		
		case "BM_GabeHouseGood2":
			dialog.text = "Quale compagno? Ne ho avuti tanti, sia nel Vecchio che nel Nuovo Mondo.";
			link.l1 = "All'inizio, volevo solo lasciare qualcosa in uno dei tuoi bauli. O forse sul tavolo, così l'avresti notato prima. Riguarda un uomo del tuo passato. Ecco, guarda e leggi tu stesso.";
			link.l1.go = "BM_GabeHouseGood3";
		break;
		
		case "BM_GabeHouseGood3":
			dialog.text = "Un marchio nero? Non ricordo pirati tra i miei compari. O forse alcuni dei ragazzi si sono dati a quella vita? Seta nera? Sul serio... Oh, Thomas. Mi stupisce che un uomo come te abbia a che fare con quel furfante.";
			link.l1 = "Chiedo venia, ma non spetta a te chiamarlo canaglia. Sei fuggito dal campo di battaglia e hai infangato il nome di Tom. Forse poi ti sei pentito e sei diventato un ufficiale modello qui nell’Arcipelago, ma il passato non si cancella.";
			link.l1.go = "BM_GabeHouseGood4";
		break;
		
		case "BM_GabeHouseGood4":
			dialog.text = "Te l’ha detto lui? Non c’è da stupirsi – sapeva sempre come trovare il gonzo giusto per ammaliare coi suoi racconti. Thomas aveva la parlantina d’argento, quello. Tu non lo conosci, né sai la vera storia, né in che pasticcio ti sei ficcato. Te la racconterò io – tanto ormai stanotte il sonno non mi verrà.";
			link.l1 = "Non è mai sbagliato tendere l’orecchio. Avanti, Capitano Callow.";
			link.l1.go = "BM_GabeHouseGood5";
		break;
		
		case "BM_GabeHouseGood5":
			dialog.text = "Ah, dunque Thomas sostiene che io sia scappato e poi l’abbia infangato? Dovresti sapere che fu proprio l’opposto! Quando la cavalleria del Re si avvicinò, Tom disse che andava a cercare rinforzi. Così non ci siamo ritirati — siamo rimasti ad aspettare. Tutta la nostra compagnia fu massacrata! Se non avessimo atteso i rinforzi che lui aveva promesso, saremmo potuti fuggire e salvarci! Alla fine, solo io, Frankie e quel dannato Thomas siamo sopravvissuti.";
			link.l1 = "Quindi quello che stai dicendo è...";
			link.l1.go = "BM_GabeHouseGood6";
		break;
		
		case "BM_GabeHouseGood6":
			dialog.text = "Dico che il sangue dei nostri ragazzi pesa sulle mani di Tom tanto quanto su quelle dei Reali. È stato fortunato a beccarsi solo la galera e non la forca! E ora ha pure la sfrontatezza di portarmi rancore e sfidarmi a duello! Non è degno nemmeno di questo!";
			link.l1 = "Non ci vai, dunque? Lo capisci cosa vuol dire. Le leggi dell’onore valgono per tutti.";
			link.l1.go = "BM_GabeHouseGood7";
		break;
		
		case "BM_GabeHouseGood7":
			dialog.text = "Certo che sì. Ed è proprio per questo che ci vado io. Dobbiamo finire quello che il nostro tribunale repubblicano non è riuscito a fare a causa dei vecchi meriti militari di Tom. E tu... tu mi sembri uno a posto. Ti consiglierei di scegliere meglio le tue compagnie. Non impicciarti con gente come Tom e la sua ciurma.";
			link.l1 = "Ma ora Thomas è al mio comando, un ufficiale sulla mia nave. "+GetSexPhrase("Terrò d'occhio quel furfante e non gli permetterò di coprirsi di altro disonore, se avrà la ventura di sopravvivere al tuo incontro.","")+"";
			link.l1.go = "BM_GabeHouseGood_Tommi1";
			link.l2 = "E cosa faresti tu al mio posto, Capitano Callow?";
			link.l2.go = "BM_GabeHouseGood_Gabe1";
		break;
		
		case "BM_GabeHouseGood_Tommi1":
			dialog.text = "Eh, se Tom è riuscito a rifilarti la sua storia, non avrà certo difficoltà a rifilarla di nuovo.";
			link.l1 = ""+GetSexPhrase("Ma per le leggi dell’onore, non posso tradirlo. Sono","Sono")+" responsabile dei miei uomini... Non sarò come lui. E d’ora in poi, se sopravvive, lo terrò d’occhio con più giudizio e circospezione.";
			link.l1.go = "BM_GabeHouseGood_Tommi2";
		break;
		
		case "BM_GabeHouseGood_Tommi2":
			dialog.text = "È una scelta difficile. Ma non cercherò di farti cambiare idea. Ebbene, addio, "+GetSexPhrase("sire","mancato")+" - Devo ancora prepararmi per incontrare Tom.";
			link.l1 = "Addio, Capitano Callow.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_GoToJamaicaJungle_TommiPlan");
		break;
		
		case "BM_GabeHouseGood_Gabe1":
			dialog.text = "Che sia fatta giustizia! Aiutami a far cadere Thomas, "+pchar.lastname+"È un furfante raro e un vile, ma con la pistola ci sa davvero fare – non sarà facile. Ma insieme...";
			link.l1 = "Hmm, aiutarti a sconfiggere Thomas? C’è davvero tanto onore in un duello simile? Sistematevela tra voi, io me ne sto fuori dai piedi.";
			link.l1.go = "BM_GabeHouseGood_Gabe2";
		break;
		
		case "BM_GabeHouseGood_Gabe2":
			dialog.text = "Conoscendolo, dubito che avrò un duello leale. Restando neutrale, non fai che accettare l’ingiustizia. Ho forse torto?";
			link.l1 = "Sembra che tu conosca Tom meglio di me, e sappia che razza di uomo sia davvero. Hai ragione – sta già preparando un’imboscata nella baia di Portland, e conta sul mio aiuto... proprio come tu conti sullo stesso adesso.";
			link.l1.go = "BM_GabeHouseGood_Gabe3";
		break;
		
		case "BM_GabeHouseGood_Gabe3":
			dialog.text = "Allora non è un duello, ma una rissa. Ma non sto dicendo che dobbiamo uccidere Thomas con le nostre mani. Lo arresteremo! Porterò dei soldati e finirò ciò che non potemmo fare nel Vecchio Mondo. Se proveranno ancora a scagionarlo, scriverò al Colonnello o lo porterò qui di persona per il processo. Se Thomas non poserà le armi, sarà solo colpa sua.";
			link.l1 = "Questo suona decisamente meglio.";
			link.l1.go = "BM_GabeHouseGood_Gabe4";
		break;
		
		case "BM_GabeHouseGood_Gabe4":
			dialog.text = "Felice di sentirlo, "+pchar.lastname+"! Capisco che forse non sia facile per te prendere una simile decisione, ma ti assicuro che hai fatto la scelta giusta. E per dimostrartelo, ti darò una mano anche con qualcos'altro.";
			link.l1 = "Che c’è, Capitano Callow?";
			link.l1.go = "BM_GabeHouseGood_Gabe5";
		break;
		
		case "BM_GabeHouseGood_Gabe5":
			dialog.text = "Tieni, prendi questo. Non è un regalo, bada, ma un prestito – Thomas, come ti dicevo, è uno spadaccino coi fiocchi, meglio affrontarlo con una lama decente invece che con un ferro arrugginito. Questa bellezza me l’ha data il colonnello Doyley in persona, ma per una vera scazzottata io sceglierei sempre una spada larga.";
			link.l1 = "Infatti, è uno splendido stocco. Ti ringrazio.";
			link.l1.go = "BM_GabeHouseGood_Gabe6";
			GiveItem2Character(PChar, "blade_40");
		break;
		
		case "BM_GabeHouseGood_Gabe6":
			dialog.text = "Non ringraziarmi – te lo presto, non te lo regalo, ricorda? Ora vai alla cala e gioca la tua parte con il nostro caro Tom, mentre io raduno rinforzi. Ci vediamo lì.";
			link.l1 = "Ci vediamo là, Capitano Callow.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_GoToJamaicaJungle_GabePlan");
		break;
		
		case "BM_GabeHouseNeutral1":
			notification("Reputation Too Low! ("+XI_ConvertString(GetReputationName(71))+")", "None");
			if (startHeroType == 4)
			{
				dialog.text = "Chi sei, signorina? Devi aver sbagliato indirizzo. Io, ehm, non ho richiesto alcun servizio notturno.";
				link.l1 = "Helen MacArthur. E tieni a bada i tuoi bollenti spiriti, signor Callow. Sono una ragazza perbene. Questo clima mi fa sentire accaldata, anche di notte. Non ti vergogni a dire certe cose a una dama che nemmeno conosci? Mi hanno parlato di te come d’un ufficiale modello.";
				link.l1.go = "BM_GabeHouseNeutral2";
			}
			else
			{
				dialog.text = "Chi sei tu, e che cosa vuoi? Quel tuo sorrisetto non mi piace affatto, messere.";
				link.l1 = ""+GetFullName(pchar)+". E non siete certo un bravo ospite, signor Callow.";
				link.l1.go = "BM_GabeHouseNeutral2";
			}
		break;
		
		case "BM_GabeHouseNeutral2":
			dialog.text = "Saluti gli sconosciuti a quest’ora in modo diverso?";
			link.l1 = "Mi hanno detto che in altri momenti non vi trovano mai a casa.";
			link.l1.go = "BM_GabeHouseNeutral3";
		break;
		
		case "BM_GabeHouseNeutral3":
			dialog.text = "Ma certo che no – ho il mio servizio, il dovere e il sudato lavoro onesto, parole che a giudicar dal tuo aspetto ti suonano proprio strane.";
			link.l1 = "Che sfacciataggine! Ma d'altronde, senza quella non avresti mai convinto il colonnello Doyley e gli altri della tua onestà. Non ho bisogno di nulla da te, Gabe – ma un tuo vecchio conoscente sì. Tieni, eccoti qua.";
			link.l1.go = "BM_GabeHouseNeutral4";
		break;
		
		case "BM_GabeHouseNeutral4":
			dialog.text = "Convinto? Gabe? Ma guarda! Un marchio nero? Allora sei un pirata? Aspetta un attimo... seta nera... potrebbe essere... Ah, ho capito. Thomas, maledetto cane, sei ancora furioso con me e Frank per averti denunciato, ahahahah!";
			link.l1 = "Dico! Tom è un ufficiale sulla mia nave e merita rispetto. È uno dei migliori tiratori dell’Arcipelago.";
			link.l1.go = "BM_GabeHouseNeutral5";
		break;
		
		case "BM_GabeHouseNeutral5":
			dialog.text = "Non ho detto che sia un pessimo tiratore. Ma vedo che non conosci bene Thomas. È stato lui a tradirci tutti quanti. Ma capisco che discutere con te sia inutile – siete proprio fatti l’uno per l’altra, a quanto pare.";
			link.l1 = "Non m'importa. Tieni le tue storie per Doyley e tutti quegli allocchi creduloni. Se sei davvero tanto coraggioso e onorevole come dicono, accetta la sfida e vieni subito. Allora, la accetti o no?";
			link.l1.go = "BM_GabeHouseNeutral6";
		break;
		
		case "BM_GabeHouseNeutral6":
			dialog.text = "Sì, sì. Adesso fuori di casa mia, prima che chiami le guardie.";
			link.l1 = "Sarà un piacere, Gabe.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_GoToJamaicaJungle_TommiPlan");
		break;
		
		case "BM_IronsJamaicaJungle1":
			if (CheckAttribute(pchar, "questTemp.BM_GabePlan"))
			{
				dialog.text = "Perché sei così nervoso? Hai forse paura, eh?";
				link.l1 = "Chiunque si spaventerebbe vedendo un uomo con un moschetto corrergli incontro – all’inizio non ti avevo riconosciuto. Che diavolo ci fai qui, Tommy?";
				link.l1.go = "BM_IronsJamaicaJungle_GabePlan_2";
			}
			else
			{
				dialog.text = "Com’è andata? Ehi, ehi, perché mi guardi così? Mi hai fatto prendere un colpo, ahah!";
				link.l1 = "Chi spaventa chi! Chi è che scappa così?! Avevamo deciso di accogliere gli ospiti nella cala!";
				link.l1.go = "BM_IronsJamaicaJungle2";
			}
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_2":
			dialog.text = "Eheh, forse sì. Mi sono stancato di aspettare – i nostri cari ospiti e pure te. Così ho pensato che questo posto fosse perfetto per una bella imboscata. In fin dei conti, io sono un cacciatore, non un gentiluomo di spada.";
			link.l1 = "Capisco.";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_3";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_3":
			dialog.text = "Aye. Allora, hai lasciato il mio dono a casa di Gabe? Ce ne hai messo, eh. Io ci avrei messo meno, se potessi entrare in città. Che t'ha preso, Capitano? Che c'è che non va?";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				link.l1 = "(Affidabile) Sono in ansia. Gabe è un codardo, ma non è uno sprovveduto. E se invece di lui arrivasse qui un intero plotone di soldati? O magari fanno rotta verso la cala e ci affondano la nave per primi?";
				link.l1.go = "BM_IronsJamaicaJungle_GabePlan_VD1";
				notification("Trustworthy", "Trustworthy");
			}
			else
			{
				link.l2 = "Gabe mi ha visto. Ho dovuto filarmela.";
				link.l2.go = "BM_IronsJamaicaJungle_GabePlan_4";
				notification("Perk Check Failed", "Trustworthy");
			}
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_VD1":
			dialog.text = "Heh, capisco - nemmeno io sono del tutto sicuro che funzionerà. È la prima volta che ti capita qualcosa di così grosso, eh? Tranquillo, succede. Ho già tutto sistemato. Se i soldati arrivano senza Gabe, ce la filiamo. Se arrivano con Gabe, gli pianto un proiettile fra gli occhi, e di nuovo, ce la filiamo. E se una nave entra nella baia, corriamo a Maroon Town - lì non oseranno metter piede, e poi decidiamo il da farsi.";
			link.l1 = "Vedo che non ti sei fatto mancar nulla, Tommy.";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_VD2";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_VD2":
			dialog.text = "Certo che l'ho fatto. Ora attendiamo il nostro ospite...";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_GazgovorTommiAndGabe");
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_4":
			dialog.text = "Ah ah, sei bravo a rubare quanto io lo sono a servire il Re. Ma perché non mi guardi negli occhi... Capitano? Hai parlato con Gabe, vero?";
			link.l1 = "No, di che diavolo parli? Perché mai dovrei parlarci, io?";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_5";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_5":
			dialog.text = "Perché siete tutti dei gran chiacchieroni. Tutto quello che fate è sparlare. Allora, cosa ti ha raccontato il nostro caro Gabe?";
			link.l1 = "Conta qualcosa, Tommy?";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_6";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_6":
			dialog.text = "Francamente, no. Lo sarà, se non mi pugnali alle spalle. Ma sembra proprio che l’hai già fatto. Ti ha convinto a schierarti con lui, vero?";
			link.l1 = "No. Non proprio. Abbassa la pistola, Tommy. Ti giuro che non deve succedere nulla d’irreparabile. Magari finirai a spaccar pietre alle cave, chissà. Chiederò a Gabe di mostrarti clemenza. E se serve, supplicherò pure il colonnello Doyley.";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_7";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_7":
			dialog.text = "Che buon samaritano che sei. Mi lasci libero così posso sputare i polmoni dopo anni nelle cave? Non torno sulle navi galera. Mai più. E tu... dovevo capirlo che eri solo un altro topo. C’è qualcosa nel tuo sguardo. Prima sistemo te, così con Gabe sarà una passeggiata dopo.";
			link.l1 = "Non ci lasci altra scelta!";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_BitvaSTommi");
		break;
		
		case "BM_GabePlan_TommiMertv":
			dialog.text = "Ebbene, vedo che l'hai già fatto, "+GetSexPhrase("sire","mancato")+". E io stavo radunando una ciurma, pensando che la superiorità numerica avrebbe fatto riflettere Tom e lo avrebbe convinto a deporre le armi.";
			link.l1 = "E ci hai messo il tuo bel tempo, Capitano Novellino.";
			link.l1.go = "BM_GabePlan_TommiMertv2";
		break;
		
		case "BM_GabePlan_TommiMertv2":
			dialog.text = "Te l’ho già detto, stavo radunando uomini. I migliori della nostra guarnigione. Tom è un vecchio soldato, dopotutto. Ma a chi lo vado raccontando? Bel lavoro, "+GetSexPhrase("Signor.","signorina")+" "+pchar.lastname+". "+GetSexPhrase("Son fiero di te, giovanotto","Devo ammettere, possiedi fascino, ingegno e destrezza in egual misura, giovanetta.")+". Come ti dissi quando ci incontrammo la prima volta, hai scelto bene. Ora la giustizia ha avuto il suo corso.";
			link.l1 = "Ti è andata proprio liscia. Ti senti fiero, eh?";
			link.l1.go = "BM_GabePlan_TommiMertv_Konflict";
			link.l2 = "Ebbene, non sono un vecchio soldato, ma so menar le mani, come avrai appena visto. Ma grazie, signore. La giustizia non è solo una parola vuota per me.";
			link.l2.go = "BM_GabePlan_TommiMertv_Mir";
		break;
		
		case "BM_GabePlan_TommiMertv_Mir":
			dialog.text = "E questo è lodevole, "+GetSexPhrase("giovanotto","giovane signorina")+"Tuttavia, resta ancora una cosa da fare per concludere degnamente questa giornata.";
			link.l1 = "Uhm, e che sarebbe? Tom è già stato messo al tappeto, dopotutto.";
			link.l1.go = "BM_GabePlan_TommiMertv_Mir2";
		break;
		
		case "BM_GabePlan_TommiMertv_Mir2":
			dialog.text = "Hai qualcosa che mi appartiene. Restituiscimi la mia splendida spada italiana, per cortesia. Non è solo uno stecchino, dopotutto, ma un ricordo — un dono del colonnello Doyley in persona.";
			if (!CheckCharacterItem(PChar, "blade_40"))
			{
				link.l1 = "Eh... Ecco il guaio, Capitano Callow... lo stocco è sparito. L’ho perso. Mi rincresce.";
				link.l1.go = "BM_GabePlan_TommiMertv_Poteryal";			//Потеряли Рапиру
				break;
			}
			if (CheckCharacterItem(PChar, "blade_40"))
			{
				link.l2 = "Ah, certo. Prego. Non volevo rubarlo, sia chiaro. Però, non ti nascondo che mi piacerebbe tenerlo. Ma eccolo qui, Capitano Callow.";
				link.l2.go = "BM_GabePlan_TommiMertv_Soglasen";			//Согласен
			}
			if (CheckCharacterItem(PChar, "blade_42"))
			{
				link.l3 = "Ho un’offerta migliore per te, Capitano.";
				link.l3.go = "BM_GabePlan_TommiMertv_Obmen";			//Обмен
			}
			link.l4 = "Ma poc'anzi l'hai chiamata stuzzicadenti. E poi hai detto che le rapiere manco ti piacciono. Io invece merito una ricompensa.";
			link.l4.go = "BM_GabePlan_TommiMertv_Otkaz";				//Отказ
		break;
		
		case "BM_GabePlan_TommiMertv_Soglasen":
			dialog.text = "Chiunque avrebbe voluto tenersi questa bellezza! Ti ringrazio per avermela riportata. Al tuo posto, molti avrebbero fatto di testa loro.";
			link.l1 = "È tuo. Suppongo che abbiamo finito qui, eh?";
			link.l1.go = "BM_GabePlan_TommiMertv_Platok";
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			TakeItemFromCharacter(pchar, "blade_40");
			AddCharacterExpToSkill(pchar, "Leadership", 300);
			ChangeCharacterNationReputation(pchar, ENGLAND, 5);
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
		break;
		
		case "BM_GabePlan_TommiMertv_Obmen":
			dialog.text = "Non m’interessa. Restituisci la spada e ce ne andremo senza rancore, "+GetSexPhrase("Signor.","mancato")+" "+pchar.lastname+".";
			link.l1 = "Immagino che questa spada ti sia cara perché apprezzi le armi con una storia, ho ragione? Ne possiedo una identica, e questa qui è quella che preferiresti portare al fianco invece che lasciarla chiusa in un cassetto.";
			link.l1.go = "BM_GabePlan_TommiMertv_Obmen2";
		break;
		
		case "BM_GabePlan_TommiMertv_Obmen2":
			dialog.text = "Ah, davvero? Beh, non posso promettere che troveremo un accordo, ma ti ascolto. In effetti, le armi con una storia mi intrigano. Però questa rapière fu un dono del Colonnello. Ecco perché mi è così cara.";
			link.l1 = "Hai detto che ti piacciono le spade larghe. Tieni. Questa apparteneva al nostro caro Tommy. Immagina quante tempeste abbia affrontato quest’arma negli anni... E quante altre vivrà al tuo fianco.";
			link.l1.go = "BM_GabePlan_TommiMertv_Obmen3";
		break;
		
		case "BM_GabePlan_TommiMertv_Obmen3":
			dialog.text = "Sei davvero persuasivo, ragazzo! Brandire la spada di Thomas... che ironia. Bah, prendi pure il mio stocco. Ma sappi che non me ne separo a cuor leggero, eh.";
			link.l1 = "Sono lieto che siamo giunti a un accordo. Direi che è un addio, capitano Callow?";
			link.l1.go = "BM_GabePlan_TommiMertv_Platok";
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			TakeItemFromCharacter(pchar, "blade_42");
			AddCharacterExpToSkill(pchar, "Leadership", 250);
			AddCharacterExpToSkill(pchar, "Commerce", 500);
		break;
		
		case "BM_GabePlan_TommiMertv_Poteryal":
			dialog.text = "COSA?! Come hai potuto... Come diamine hai potuto perdere un'intera cazzo di spada?! Sei proprio uno sciocco!";
			link.l1 = "Calmati! È solo una spada. Tanto non l’avresti mai usata. Tom è morto – non è forse questo l’unica cosa che conta adesso?";
			link.l1.go = "BM_GabePlan_TommiMertv_Poteryal2";
		break;
		
		case "BM_GabePlan_TommiMertv_Poteryal2":
			dialog.text = "Solo una spada?! Era il mio tesoro! Un dono del colonnello Doyley in persona! Che m’importa se non la usavo!";
			link.l1 = "Allora non avresti dovuto darmelo, vero?";
			link.l1.go = "BM_GabePlan_TommiMertv_Poteryal3";
		break;
		
		case "BM_GabePlan_TommiMertv_Poteryal3":
			dialog.text = "Dovresti tenere la bocca chiusa ora, "+GetSexPhrase("Signor.","signorina")+" "+pchar.lastname+"   Potevamo separarci in pace, ma ora... ora mi vien voglia d'insegnarti una lezione, "+GetSexPhrase("giovanotto","giovane signorina")+".";
			link.l1 = "I cimiteri son pieni di maestri come te.";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_BitvaCallowSoloConflict");
			pchar.questTemp.BM_GabeCallow_Rapira = true;
		break;
		
		case "BM_GabePlan_TommiMertv_Otkaz":
			dialog.text = "Certamente che sì. Ma non puoi mica soffiarti l’arma personale d’un ufficiale solo perché gli hai dato una mano, eh?";
			link.l1 = "Sarei anche d'accordo, ma tanto tu non la usi mai. Finirà solo appesa a un chiodo nella tua stanza. Invece con me troverà degno impiego. Il colonnello Doyley non verrà mica a controllare se l’hai persa, o sbaglio?";
			link.l1.go = "BM_GabePlan_TommiMertv_Otkaz2";
		break;
		
		case "BM_GabePlan_TommiMertv_Otkaz2":
			dialog.text = "Non c’è nulla da discutere, giovanotto. Te l’ho detto fin dall’inizio, non è un dono. Dammi la spada. Ora.";
			link.l1 = ""+GetSexPhrase("Non sono uno dei tuoi fantocci da guerra","Non sono una delle tue sgualdrine da porto")+", di prendere ordini da te. Sono un capitano di nave, proprio come te. Lo stocco resta con me, che ti piaccia o no.";
			link.l1.go = "BM_GabePlan_TommiMertv_Otkaz3";
		break;
		
		case "BM_GabePlan_TommiMertv_Otkaz3":
			dialog.text = "Pare che Thomas ti abbia proprio segnato. Allora crepa per lui, se ci tieni così tanto.";
			link.l1 = "Proprio quello che pensavo anch'io!";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_BitvaCallowSoloConflict");
			pchar.questTemp.BM_GabeCallow_Rapira = true;
		break;
		
		case "BM_GabePlan_TommiMertv_Platok":
			dialog.text = "Tieni, prendi questo. Non mi serve affatto. Sarà il tuo ricordo di questa giornata. Cerca di non essere così credulone d’ora in poi. E non lasciare che qualche furfante come Thomas ti trascini nei suoi luridi affari.";
			link.l1 = "Heh, vuoi forse consegnarmi un punto nero, Capitano Novellino?";
			link.l1.go = "BM_GabePlan_TommiMertv_Platok2";
			GiveItem2Character(PChar, "talisman15");		//Предмет Чёрная Метка
		break;
		
		case "BM_GabePlan_TommiMertv_Platok2":
			dialog.text = "Ebbene, nessuno dei due è un pirata, vero? "+pchar.name+"Che ti serva da monito. Sta’ attento, l’Arcipelago ha bisogno di uomini come te. "+GetSexPhrase("Forse ti consiglierei d’arruolarti in Marina e potrei scrivere una raccomandazione al colonnello Doyley...","")+"";
			link.l1 = "Mi rincresce, Capitano, ma non posso accettare la vostra offerta.";
			if (startHeroType == 3)
			{
				link.l1 = "Mm. Ci rifletterò su. Per davvero, stavolta.";
			}
			if (startHeroType == 4)
			{
				link.l1 = "Addio, signore.";
				link.l1.go = "exit";
				AddDialogExitQuest("BM_GabePlan_CallowDruzhba");
				break;
			}
			link.l1.go = "BM_GabePlan_TommiMertv_Platok3";
		break;
		
		case "BM_GabePlan_TommiMertv_Platok3":
			dialog.text = "Fa’ come ti pare. Beh, addio, "+GetSexPhrase("Signor.","signorina")+" "+pchar.lastname+". Meriti di portare ciò che resta degli Ironsides. Addio.";
			link.l1 = "Addio, signore.";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_CallowDruzhba");
		break;
		
		case "BM_GabePlan_TommiMertv_Konflict":
			dialog.text = "Non mi garba il tuo tono, "+GetSexPhrase("signore","signorina")+"... Qual è il tuo punto?";
			link.l1 = "Hai perso tempo apposta, radunando i tuoi ‘migliori uomini’. Perché? Per catturare un uomo solo? Bastava che prendessi due soldati in ronda e venissi subito in mio soccorso!";
			link.l1.go = "BM_GabePlan_TommiMertv_Konflict2";
		break;
		
		case "BM_GabePlan_TommiMertv_Konflict2":
			dialog.text = "Portare carne da cannone?! Tom non era una semplice guardia cittadina come quei poveracci. Aveva un addestramento e un’esperienza del tutto diversi – è un maledetto Corazzato, proprio come me! Come fai a non capirlo?";
			link.l1 = "Oh, al contrario, lo capisco benissimo. Proprio per questo tu ed io eravamo qui – per incrociare le spade con Tom, così che i ragazzi potessero prenderlo vivo. Inoltre, anche tu sei Corazzato. Della stessa compagnia, persino. Avevi forse paura di affrontarlo faccia a faccia?";
			link.l1.go = "BM_GabePlan_TommiMertv_Konflict3";
		break;
		
		case "BM_GabePlan_TommiMertv_Konflict3":
			dialog.text = "Come osi accusarmi di codardia, ragazzino "+GetSexPhrase("uomo","mancato")+"Chiedi pure in giro, e ti racconteranno per filo e per segno quali imprese ho compiuto per questa città.";
			link.l1 = "Non ho ancora finito. Comincio a domandarmi se queste ‘imprese’ siano davvero opera tua. Hai voluto che io e Tom ci ammazzassimo tra noi, così ti prendevi tutta la gloria. L’hai già fatto in passato, vero?";
			link.l1.go = "BM_GabePlan_TommiMertv_Konflict4";
		break;
		
		case "BM_GabePlan_TommiMertv_Konflict4":
			dialog.text = "Ne ho fin sopra i capelli delle tue accuse, "+GetSexPhrase("Signor.","mancato")+" "+pchar.lastname+"Vuoi la rissa? Allora preparati, perché arriva adesso.";
			link.l1 = "La verità brucia, vero Gabe?";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_BitvaCallowSoloConflict");
			pchar.questTemp.BM_GabeCallow_Conflict = true;
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_1":
			dialog.text = "";
			link.l1 = "Gabe! È passato tanto tempo, tanti freddi inverni! E guarda un po’ – hai ancora quella tua faccia da furfante, maledetto te!";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_2";
			CharacterTurnByChr(npchar, characterFromID("Irons"));
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_2":
			dialog.text = "Thomas! Dovrei esserne lieto, perché oggi finalmente finirò con le mie stesse mani ciò che la nostra giustizia non è riuscita a compiere in anni. E siccome l'animo mio è leggero, ti concedo di deporre le armi e seguirci. Potresti perfino essere rispedito ai lavori forzati. In tal caso, sarò io stesso a consegnarti.";
			link.l1 = "Ehi, fammi provare! Credi che due marmittoni al tuo fianco mi fermeranno!!!";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_3";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_3":
			dialog.text = "Chi ti dice che siano gli unici con me? Parlo di chi ti sta accanto proprio adesso.";
			link.l1 = "Che?";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_4";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_4":
			dialog.text = "Thomas, Thomas, Thomas... sei, come sempre, solo al mondo. Quasi mi fai pena, disgraziato!";
			link.l1 = "Maledetti topi! Dannati bastardi!";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_5";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_5":
			StartInstantDialog("Irons", "BM_GabePlan_GazgovorTommiAndGabe_6", "Quest\BlackMark.c");
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_6":
			dialog.text = "Cosa vuol dire questo?! Che diavolo intendeva con quelle parole?!";
			link.l1 = "Tommy, ascolta...";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_7";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_7":
			dialog.text = "È proprio quello che sto facendo! Dimmi che sta mentendo!";
			link.l1 = "Purtroppo ha ragione. Deponete le armi. Nessuno deve crepare oggi. Metterò io stesso una buona parola per voi, così non vi manderanno all'impiccagione. Un giorno magari tornerete pure a una vita onesta.";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_8";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_8":
			dialog.text = "Non sta a te decidere! E tanto meno a te! Con un comandante così, chi ha bisogno di nemici! Un'altra maledetta canaglia.";
			link.l1 = "Forza, Tommy. Non esistono fughe pulite per gente come te.";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_9";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_9":
			dialog.text = " Un posto nella tua ciurma, sulla tua nave, sarebbe stato un inizio, se solo avessi avuto il coraggio di difendere i tuoi uomini! Ma ormai non importa più. Maledetti siate, tutti quanti! Vi sventrerò, vigliacchi, topi di sentina. E tu, Gabe, cercherò di portarti all'inferno con me...";
			link.l1 = "Aspetta, Tommy, no!";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_GazgovorTommiAndGabe_Fight");
		break;
		
		case "BM_GabePlan_GabeWin_1":
			dialog.text = "Congratulazioni, "+GetSexPhrase("giovanotto","giovane signorina")+"! Mi sorprende che tu sia riuscito a far credere a Thomas che tutto stesse andando secondo i suoi piani – aveva un fiuto infallibile per il tradimento.";
			link.l1 = "Ah, grazie, certo, Capitano Novellino.";
			link.l1.go = "BM_GabePlan_GabeWin_2";
		break;
		
		case "BM_GabePlan_GabeWin_2":
			dialog.text = "Vi turba qualcosa, "+GetSexPhrase("Signor.","signorina")+" "+pchar.lastname+"?";
			link.l1 = "Tom... non era soltanto furioso perché stavo dalla tua parte. Nella sua voce c’era vera disperazione e smarrimento, come se...";
			link.l1.go = "BM_GabePlan_GabeWin_3";
		break;
		
		case "BM_GabePlan_GabeWin_3":
			dialog.text = "...come se fosse lui la vittima, qui. C’era da aspettarselo. Ricorda, Charles, anche un mostro può provare dolore. Ma non smette d’esser un mostro per questo. Molti furfanti son davvero convinti, nel profondo, d’esser nel giusto e innocenti.";
			link.l1 = "Cercherò di ricordarmene. Direi che qui abbiamo finito, non trovi, Capitano?";
			link.l1.go = "BM_GabePlan_GabeWin_4";
		break;
		
		case "BM_GabePlan_GabeWin_4":
			dialog.text = "In generale sì, ma resta ancora una faccenda da sbrigare per concludere degnamente questa giornata.";
			link.l1 = "Oh? Che c’è?";
			link.l1.go = "BM_GabePlan_TommiMertv_Mir2";
		break;
		
		case "BM_IronsJamaicaJungle2":
			dialog.text = "Ce ne hai messo di tempo. Così ho pensato di dare un’occhiata in giro. Comunque, credo sia meglio tendere loro un agguato qui invece di fare i damerini sulla spiaggia col fioretto. Spero tu abbia trovato la casa di Gabe e lasciato tutto bene in vista?";
			link.l1 = "Ma certo che l'ho fatto, per chi mi prendi, per uno scimunito? In verità sono io il tuo capitano, Tommy. E che razza di uomo saresti tu, se stai al servizio d'un idiota?";
			link.l1.go = "BM_IronsJamaicaJungle3";
		break;
		
		case "BM_IronsJamaicaJungle3":
			dialog.text = "Ah-ah-ah-ah, non ci crederesti quante volte ho dovuto affrontare porcherie simili durante il servizio! Ma per nostra fortuna, stavolta non è così. Bene allora. Aspettiamo compagnia. Sei pronto?";
			link.l1 = "Ebbene, a meno che non si presenti qui l’intera flotta o la guarnigione di Port Royal, sono pronto.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_CreateGabeInJungle");
		break;
		
		case "BM_GabeJungle1":
			dialog.text = "Thomas? Sei proprio tu, alla fine dei conti...";
			link.l1 = "Certo che sono proprio io, o aspettavi qualcun altro, Gabe? Eh eh, sembri aver visto un fantasma, sei più pallido d’un lenzuolo. E anche più grasso di quanto eri nella Vecchia Inghilterra.";
			link.l1.go = "BM_GabeJungle2";
			CharacterTurnByChr(npchar, characterFromID("Irons"));
		break;
		
		case "BM_GabeJungle2":
			dialog.text = "Ora sono finalmente convinto che sei proprio tu. Sgarbato come sempre. Ma non temere, presto farò tacere per sempre quella tua lurida bocca, maledetto bastardo.";
			link.l1 = "Ah-ah-ah, ora sì che si ragiona! Sai, Gabe, mi hai proprio deluso, di nuovo! Dovevi portarti dietro più uomini, persino solo per affrontare me. E invece siamo in due! O forse era tutto ciò che quei codardi potevano darti, eh vigliacco?";
			link.l1.go = "BM_GabeJungle3";
		break;
		
		case "BM_GabeJungle3":
			dialog.text = "Basta! Non vedo più alcun senso nel continuare questa conversazione.";
			link.l1 = "Sono d’accordo con te su questo! "+pchar.name+"All’arrembaggio, Capitano!";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_GabeJungleFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "BM_IronsJamaicaJungle4":
			dialog.text = "Ehilà, eccoti servito! Riposa in pace, maledetto bastardo.";
			link.l1 = "E allora, sei contento, Tommy? Lo sai, molti peggiorano soltanto dopo aver avuto la loro vendetta.";
			link.l1.go = "BM_IronsJamaicaJungle5";
		break;
		
		case "BM_IronsJamaicaJungle5":
			dialog.text = "Ahah, dove hai letto ‘sta robaccia? Mai capiti quei damerini! Bah! Soddisfatto, dici? Son così allegro che quasi mi piscio addosso! Quei bastardi erano la causa di tutte le mie più grandi sventure!";
			link.l1 = "Sono felice per te. Non hai più nessuno da vendicare? Devo aspettarmi altre spiritosaggini sulle cartucce di carta da parte tua?";
			link.l1.go = "BM_IronsJamaicaJungle6";
		break;
		
		case "BM_IronsJamaicaJungle6":
			dialog.text = "Calmati, Gabe è stato l’ultimo. E quanto agli scherzi – non temere, per te non ce ne saranno più, almeno per ora.";
			link.l1 = "Torniamo alla nave, dunque?";
			link.l1.go = "BM_IronsJamaicaJungle7";
		break;
		
		case "BM_IronsJamaicaJungle7":
			dialog.text = "Torneremmo comunque a bordo di lei, che abbia ancora qualcuno da vendicare o no. Ma aspetta un attimo...";
			link.l1 = "Oh, dunque non è ancora finita...";
			link.l1.go = "BM_IronsJamaicaJungle8";
		break;
		
		case "BM_IronsJamaicaJungle8":
			dialog.text = "Lo è, lo è. C’è una cosa che voglio confidarti. La dico a pochissimi. E non la ripeterò più. Se osi ridere di me, mi farai andare su tutte le furie.";
			link.l1 = "Prometto che non riderò. In ogni caso, trovo le tue battute più tese che divertenti.";
			link.l1.go = "BM_IronsJamaicaJungle9";
		break;
		
		case "BM_IronsJamaicaJungle9":
			dialog.text = "Bene. Dunque. Ti sono davvero riconoscente che tu abbia deciso d’aiutarmi invece di comportarti come Jack. Sei un vero amico, Capitano. Grazie di cuore. E poi... se vuoi, puoi prendere in prestito la mia fedele spada, e la mia armatura... Quel che ne resta, ahah!";
			link.l1 = "Ebbene, ti ringrazio per le tue parole. Non capita spesso di sentir cose simili dagli ufficiali. Andiamo, compare.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_FinalInJungleWithTommy");
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Irons_officer":
			dialog.text = "Aaaaye-aye, Capitano?";
			if (startHeroType == 4 && CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				dialog.text = "Allora, Rumba, su quali ossa balleremo stanotte?";
			}
			if (startHeroType == 4 && !CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				dialog.text = "Sì, Ellie?";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Sono tutto orecchi, capitano.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = ""+pchar.name+"?";
			}
			//////
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal") && !CheckAttribute(pchar, "questTemp.BM_TommiTieyasalOtkaz"))
			{
				Link.l4 = "Tommy, vorrei chiederti qualcosa di molto serio. C’è... un idolo di pietra dei pellirosse. E avrò bisogno d’aiuto. Posso rivolgermi solo ai miei compagni più fidati, come te. Novellini o gente di cui non mi fido abbastanza non vanno bene.";
				Link.l4.go = "tieyasal_1";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Tommy, smettila di contare i gabbiani. Hai già fatto l’inventario del carico? Voglio un rapporto completo e le tue previsioni.";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "Tommy, da oggi ho bisogno che tu vada a comprare certe merci nei porti.";
				Link.l12.go = "QMASTER_2";
				
				if (startHeroType == 4)
				{
					Link.l11 = "Tommy, potresti riferire tutto quello che succede a bordo?";
					Link.l12 = "Tommy, comincio a sentirmi davvero sfinito. Potresti fare scorta di certe merci in ogni porto?";
				}
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					Link.l11 = "Preparami un resoconto sulle condizioni della nave e di tutto ciò che c’è a bordo, Tommy.";
					Link.l12 = "Potresti fare scorta di certe merci durante le nostre soste in porto?";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					Link.l11 = "Conta tutto quello che ho a bordo e fammi un rapporto sulle condizioni della nave.";
					Link.l12 = "Mi serve che tu compri questa mercanzia ogni volta che facciamo scalo in un porto.";
				}
			}
			//////
			Link.l1 = "Ascolta bene il mio ordine!";
			if (startHeroType == 4 && CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				Link.l1 = "Di certo qualcuno. Ma per ora, ascolta i miei ordini.";
			}
			if (startHeroType == 4 && !CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				Link.l1 = "Ascolta il mio ordine... Tommy. ";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				Link.l1 = "Benone, perché ho un nuovo incarico per te, Tommy.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				Link.l1 = "Ascolta il mio ordine, Tom.";
			}
			Link.l1.go = "stay_follow";
			//////
			link.l2 = "Niente, Tommy. Rilassati.";
			if (startHeroType == 4 && CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				link.l2 = "Vedremo come va a finire, Tommy.";
			}
			if (startHeroType == 4 && !CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				link.l2 = "No, Tom, niente.";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				Link.l2 = "No, niente.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				Link.l2 = "Niente, tutto va a gonfie vele.";
			}
			link.l2.go = "exit";
			NextDiag.TempNode = "Irons_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Non ho nemmeno iniziato con l’inventario. Dovresti ringraziare il cielo che almeno tengo conto dei nostri guadagni e perdite, senza parlare del mercanteggiare con quei cani d'affari. L’inventario non è affar mio, mai dovuto farlo nell’esercito, e di certo non comincerò adesso.";
			Link.l1 = "Questa non è la marina, Tommy. Ma va bene, ho capito, non ti forzerò.";
			if (startHeroType == 4)
			{
				dialog.Text = "Non sono uno scriba, Ellie. Una volta conoscevo un certo Daniel Crimson, che si vantava sempre d’essere scriba, ma la verità è che il campo di battaglia l’aveva visto poco. Però, in battaglia era una vera bestia. Io non sono come lui, e non ti racconterò fandonie. L’inventario non fa proprio per me. Già mi sto occupando dei nostri conti solo per farti contenta. Non esagerare.";
				Link.l1 = "D'accordo, Tommy, non lo farò.";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Ascolta, io non sono uno scriba. Nessuno ha mai chiesto questo a semplici soldati come me, nemmeno nell'esercito. Non cambiamo questa regola.";
				Link.l1 = "Va bene, lasciamo perdere.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "L’unica cosa che so contare è quanti dei nostri nemici ho fatto fuori, ah-ah-ah. E anche lì perdo il conto. Sono un semplice soldato, capisci. Che diavolo ne so di navi – sono stato un terricolo per quasi tutta la vita.";
				Link.l1 = "Pare che dovrò occuparmene da solo.";
			}
			Link.l1.go = "exit";
		break;

		case "QMASTER_2":
			dialog.text = "Per chi mi hai preso, per uno straccione da quattro soldi? Noi disprezzavamo quei codardi mollaccioni nel vecchio mondo. Non sarò nobile, ma l’orgoglio non me lo strappa nessuno.";
			link.l1 = "Va bene, va bene, se non vuoi, non vuoi.";
			link.l1.go = "exit";
			if (startHeroType == 4)
			{
				dialog.Text = "Ascolta, ero solo un soldato semplice e onesto, non un maledetto ufficiale di rifornimento, ragazza mia. Non ne so molto e non ho nessuna voglia di cominciare ora. Sarebbe come chiedere a te di smontare e rimontare un moschetto a tempo.";
				Link.l1 = "Ebbene, potrei nominare a memoria ogni pezzo dell'attrezzatura fissa e corrente di questa nave. Ma come vuoi tu, Tom. La faccenda è chiusa.";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "No, non potevo. Forse ti sei scordato o magari non lo sai proprio, quindi lascia che ti spieghi. Per te sarebbe un compito di ordinaria amministrazione, ma nella nostra armata chi si occupa di provviste e retrovie non gode di gran rispetto. Ti prego, non mettermi tra quella gentaglia.";
				Link.l1 = "Ah-ah, bene, bene.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Ascolta, ti rispetto, certo, ma non vado contro me stesso per fare ciò che non posso e non sopporto. All’epoca a malapena sapevo contare, e tu ora vuoi che faccia il fornitore serio. Comunque sia, quelli non ci piacevano: risparmiavano su munizioni, acqua, cibo e pure sulla freschezza.";
				Link.l1 = "Hm, va bene, lasciamo perdere.";
			}
		break;
		
		case "stay_follow":
            dialog.Text = ""+GetSexPhrase("Oh, un ordine, eh? Ti piace la disciplina e tutte quelle cose da soldato, vero? Preferirei che mi dicessi semplicemente cosa devo fare.","Sei come un sergente o giù di lì. Non ti si addice – sei troppo bella per quella roba. Nell’esercito non ci avresti campato nemmeno un giorno. Ma ti ascolto.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "A quanto pare, hai proprio un debole per uniformi, esercitazioni e simili. Ma va bene, continua pure.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Quale di questi?";
			}
			
            Link.l1 = ""+GetSexPhrase("Non andare da nessuna parte e non combinare nulla – resta a guardare, capisci? Ti conosco, furfante.","Resta dove sei, mi hai capito?")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				Link.l1 = "Stai fermo qui, non andare da nessuna parte e non toccare nulla.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				Link.l1 = "Resta qui e non far passare anima viva.";
			}
			Link.l1.go = "Boal_Stay";
            Link.l2 = ""+GetSexPhrase("Seguimi e non farti distrarre da nulla – né da mogli smarrite né da vecchi compagni d'armi che sbucano all'improvviso.","Stammi vicino, d’accordo? Preferisco avere qualcuno che mi guardi le spalle.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				Link.l2 = "Seguimi. Vedo che hai la testa fra le nuvole.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				Link.l2 = "Seguimi, altrimenti t’è venuto il granchio e t’hai fermato.";
			}
			Link.l2.go = "Boal_Follow";
			
			if(CheckAttribute(NPChar, "equip.gun"))
			{
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Questa volta ho bisogno che tu spari a qualcos'altro.";
					Link.l3.go = "SetGunBullets";
					if (pchar.sex == "man" && pchar.rank >= 15)
					{
						Link.l3 = "Ho bisogno che tu usi munizioni diverse nella prossima battaglia.";
					}
					if (pchar.sex == "man" && pchar.rank >= 25)
					{
						Link.l3 = "Userai munizioni diverse nella prossima battaglia.";
					}
				}	
			}
			if(CheckAttribute(NPChar, "equip.musket"))
			{
				if(CheckAttribute(NPChar, "chr_ai.musket.bulletNum") && sti(NPChar.chr_ai.musket.bulletNum) > 1)
				{
					Link.l4 = "Cambia il tipo di munizione per il tuo moschetto.";
					Link.l4.go = "SetMusketBullets";
				}
				Link.l5 = "Cambia la tua arma principale per il combattimento.";
				Link.l5.go = "SetPriorityMode";
				Link.l6 = "Vorrei che tu mantenessi una certa distanza tra te e i tuoi nemici.";
				Link.l6.go = "TargetDistance";
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					Link.l6 = "Vorrei che mantenessi una certa distanza dal nemico, Tommy.";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					Link.l6 = "Stai a una certa distanza dal nemico, Tommy.";
				}
			}
		break;
		
		case "SetGunBullets":
			Dialog.Text = ""+GetSexPhrase("Che razza di proiettili? Spero tu li abbia forgiati con cura, perché il diavolo solo sa dove finiranno, eh eh.","Sparo a qualsiasi cosa per te. Qualsiasi cosa sia, ma mai a salve, eh eh.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Sento che sta bollendo qualcosa d’interessante! Allora, di che si tratta?";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Di nuovo a menar le mani... Va bene, che razza di guaio stavolta?";
			}
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;

		case "SetMusketBullets":
			Dialog.Text = "Seleziona il tipo di munizioni:";
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.musket.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetMusketBullets2":
			i = sti(NPChar.SetMusketBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, MUSKET_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, MUSKET_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetMusketBullets");
			DialogExit();
		break;
		
		case "SetPriorityMode":
			Dialog.Text = "All’inizio della battaglia userai:";
			Link.l1 = "Lama";
			Link.l1.go = "BladePriorityMode";
			Link.l2 = "Moschetto";
			Link.l2.go = "MusketPriorityMode";
		break;
		
		case "BladePriorityMode":
			SetPriorityMode(NPChar, 1);
			DialogExit();
		break;
		
		case "MusketPriorityMode":
			SetPriorityMode(NPChar, 2);
			DialogExit();
		break;
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = ""+GetSexPhrase("Anche se ti prendono a pugni laggiù, eh eh? Capito, allora me ne starò a guardare.","Vuoi farmi fare la guardia? E se invece ti pestano per davvero?")+"";
            Link.l1 = ""+GetSexPhrase("Ehi, fai attenzione! Se ci arriviamo, troveremo una soluzione.","E allora, non starai lì a guardare soltanto, vero? Se il tuo capitano è davvero così magnifico come dici, farai qualcosa al riguardo.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Perfino in testa? Va bene, va bene, non mi guardare così, ho capito.";
				Link.l1 = "Spero di sì.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Non temere, nessuno passerà.";
				Link.l1 = "Se non senti la mancanza di nessuno, ovviamente. Ma va bene.";
			}
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = ""+GetSexPhrase("Molto spiritoso. Ma ho capito dove vuoi arrivare.","Oh, non temere, la tua schiena è sempre sotto il mio occhio vigile, eh eh.")+"";
            Link.l1 = ""+GetSexPhrase("Bene.","Dio, sei davvero insopportabile, Tom.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Ebbene, sto cercando di ricordare qualcosa di davvero importante. Poi mi accorgo che nemmeno so di cosa si tratti, visto che ho perso la memoria allora, quindi non ne verrà fuori nulla. Su, andiamo.";
				Link.l1 = "Arguto, devo ammetterlo.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Ebbene, sto qui perché me l'hai ordinato tu stesso poco fa. Arrivo, arrivo.";
				Link.l1 = "Hm-m, va bene, va bene.";
			}
            Link.l1.go = "Exit";
        break;
		
		//--> задать дистанцию стрельбы
		case "TargetDistance":
			dialog.text = ""+GetSexPhrase("Che distanza intendi? Tieni a mente che oltre venti passi non garantisco la mira. A meno che tu non voglia solo fare scena, eh eh.","Come se volessi avvicinarmi a uomini puzzolenti dopo aver passato del tempo con te. Allora, qual è la distanza? Ma ricorda, non posso proprio mirare bene oltre venti yarde, nessuno può.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Va bene, che distanza? Ma ti avverto: in mezzo al pandemonio, più di venti metri e non garantisco né mira né calma.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "D'accordo. Che? Ricorda che oltre a... insomma, non siamo più dei ragazzini, tu e io lo sappiamo bene.";
			}
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";
		break;
		
		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = ""+GetSexPhrase("Non dovresti provarci con le battute.","Hai ancora molto da imparare da me sull’arte dello scherzare, ragazza mia. Ma vedo che fai progressi!")+"";
				link.l1 = ""+GetSexPhrase("That's odd; I've always been told the opposite.","Very funny, Tommy.")+"";
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					dialog.text = "Non è la tua battuta peggiore. Forse un giorno smetterai pure di fare il musone, eh-eh.";
					Link.l1 = "Eh, sia come sia.";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					dialog.text = "Ah-ah-ah, bella trovata.";
					Link.l1 = "In realtà, io solo... va bene.";
				}
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "Ebbene, allora resto fermo e tengo la posizione. Se li affronti da troppo lontano, sei tu quello che rischia la pelle, eh eh.";
				link.l1 = "Don't be sarcastic; holding your ground is exactly what I want you to do from now.";
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					dialog.text = "Heh, potevi semplicemente dirmi di restare fermo, senza tirare fuori distanze e cifre.";
					Link.l1 = "Ebbene, l’importante è che tu mi abbia capito.";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					dialog.text = "Capito, terrò la posizione qui. Poi portali più vicino a me così posso sparare.";
					Link.l1 = "Certamente.";
				}
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = "Ascolta, so che vorresti che ogni colpo mio fosse come quello al faro, ma non sarà sempre così. Là avevo una buona posizione. Calma e fermezza. Non puoi riprodurre quella roba nel bel mezzo della battaglia.";
				link.l1 = "Hmm. Allora tieniti a venti passi di distanza.";
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					dialog.text = "So che ti piacerebbe, piacerebbe a tutti i mascalzoni, ma come quella volta al faro, non funzionerà più. Mi serve un posto sicuro, e che nessuno mi disturbi, altrimenti i nervi mi mollano.";
					Link.l1 = "Hm-m, va bene.";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					dialog.text = "Da allora ho affinato certo la mia arte, ma l’impossibile resta tale – nel fuoco della battaglia, non potrei mai ripetere quel colpo sparato dal faro. Nemmeno con un archibugio a ruota.";
					Link.l1 = "E l’impossibile diventa possibile, Tommy. Ma va bene, no vuol dire no.";
				}
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = RandPhraseSimple("Molto bene. Terrò proprio quella distanza, ma se ci toccherà menar le mani in una taverna o in una grotta, uscirò fuori per mantenerla, eh eh.","Ci proverò. Ma i ponti e gli spazi stretti potrebbero imporre le loro condizioni.");
			link.l1 = ""+GetSexPhrase("Non è divertente, Tommy. Comportati come si deve, ma niente scherzi o le tue stupide burle.","Lo so, Thomas, non sono uno sciocco.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Cercherò di ricordare.";
				Link.l1 = "D'accordo, conto su di te.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Sì, capitano.";
				Link.l1 = "Rilassati, Tommy.";
			}
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;
		//<-- задать дистанцию стрельбы
	//<-- ----------------------------------- офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal_1":
			dialog.text = "Aiutare con cosa, rubarlo? Ma perché? Mi lusinghi, certo, ma potevi sputare il rospo molto tempo fa. Su, avanti, sputa il veleno.";
			link.l1 = "Attento a come parli, eh? Bah, maledizione – in fondo mi importa poco come ti esprimi, finché stai dalla mia parte. Allora, quell’idolo. Attraverso di lui puoi... raggiungere un altro posto, come per magia. Non guardarmi così – so bene come suona. Ma ci sono già passato, ho visto tutto coi miei occhi. È... sicuro, se bevi un elisir.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = "Vedo che ti sei già fatto qualche bicchiere. Anzi no, sembri lucido. E pensare che di me dicono che straparlo sempre...";
			link.l1 = "Vieni con me o no? L’idolo dovrebbe condurci in un’antica città maya, e chissà che diavolo ci aspetta laggiù. Sei tra quelli su cui posso contarci nei momenti bui. E ora, proprio uno di quei momenti è arrivato.";
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			dialog.text = "Ho un brutto presentimento su tutta questa faccenda. Se non fossi il mio capitano, ti direi che il tuo posto è in manicomio. La prossima volta mi dirai pure che Dio esiste.";
			link.l1 = "Lo fa, Tommy. E, con mia sorpresa, ho scoperto su quest’Arcipelago che non riguarda solo noi. Puoi vedere coi tuoi occhi tutte le diavolerie che accadono qui. E avrai notato l’influsso di amuleti benedetti o maledetti.";
			link.l1.go = "tieyasal_4";
		break;
		
		case "tieyasal_4":
			dialog.text = "La malvagità esiste anche a casa. E ha sempre avuto una spiegazione normale. Scusa, capitano, ma non ballerò attorno a idoli di pietra con te. Sparare ai nemici, quello sì. Forse ho perso la memoria, ma non la testa. Almeno, così credo.";
			link.l1 = "Ebbene, non posso obbligarti. Dunque... come vuoi tu, Tommy.";
			link.l1.go = "tieyasal_5";
			link.l2 = "Dubito che avrai il fegato di sparare a quei cani, temerario, se già tremi ad avvicinarti all’idolo.";
			link.l2.go = "tieyasal_6";
		break;
		
		case "tieyasal_5":
			dialog.text = "Oh, su su, non fare il muso lungo. Va bene, se torni dopo aver ballato attorno a quell’idolo, forse la prossima volta ci penserò.";
			link.l1 = "Non è detto che ci sarà una prossima volta. Torna sulla nave, Tom.";
			link.l1.go = "exit";
			pchar.questTemp.BM_TommiTieyasalOtkaz = true;
		break;
		
		case "tieyasal_6":
			dialog.text = "Non ho paura, non fraintendermi. Ma son solito dar retta al mio istinto, e in tanti anni non m'ha mai tradito. Ora mi sussurra che da questa storia non verrà nulla di buono. E comunque... Bah, finirai per prendertela.";
			link.l1 = "Avanti, raccontami tutto.";
			link.l1.go = "tieyasal_7";
		break;
		
		case "tieyasal_7":
			dialog.text = "Ebbene, se è così! Ho accettato di combattere al tuo fianco. Ma se, mettiamo caso, questa cosa funziona davvero? E se fosse maledetta? Non ho alcuna voglia di crepare per nessuno, mi dispiace.";
			link.l1 = "Ora ti sei mostrato per quello che sei, Tommy. Avevo bisogno dei più fedeli al mio fianco. E vedo bene che tu non sei tra questi. Io vado per la mia strada. E tu... fa’ pure come ti pare.";
			link.l1.go = "tieyasal_8";
		break;
		
		case "tieyasal_8":
			dialog.text = "Guardalo. Si è offeso, dopotutto.";
			link.l1 = "Chiudi quella bocca. Se ti facciamo così schifo, non c’è bisogno che torni a bordo.";
			link.l1.go = "tieyasal_9";
		break;
		
		case "tieyasal_9":
			dialog.text = "Accidenti! Parli sul serio? Beh, forse è meglio così. Non ho voglia di restare con musoni che non capiscono nemmeno uno scherzo. In tal caso... addio, Vostra Eccellenza.";
			link.l1 = "Addio, Tommy. E va’ all’inferno.";
			link.l1.go = "tieyasal_10";
		break;
		
		case "tieyasal_10":
			DialogExit();
			RemovePassenger(pchar, npchar);
			DeleteAttribute(npchar, "OfficerImmortal");
			npchar.lifeday = 0;
			LAi_SetWarriorType(npchar);
			LAi_CharacterDisableDialog(npchar);
		break;
	}
} 
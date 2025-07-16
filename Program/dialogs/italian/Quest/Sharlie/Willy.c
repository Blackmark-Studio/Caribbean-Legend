// Вильям Патерсон
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "C’è qualcosa che desideri?";
			link.l1 = "No, niente.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "catoche":
			dialog.text = "Salve, Monsieur. Maledizione, sei tu il diavolo che ha scatenato tutto questo trambusto militare da queste parti?!";
			link.l1 = TimeGreeting()+", signore. Sì, è stata la mia nave a sbarcare la spedizione. Ma che diavolo succede? Chi siete voi? Inglese, suppongo?";
			link.l1.go = "catoche_1";
		break;
		
		case "catoche_1":
			dialog.text = "Uno scozzese, Monsieur. Capitano della Marina Inglese William Paterson, e questo è il mio primo ufficiale e mano destra, Archibald Calhoun. Vede, c’è un forte spagnolo nella giungla. Il mio compito è scacciare quei maledetti figli di puttana dal fortino che hanno costruito troppo vicino ai nostri confini.\nDi recente abbiamo provato ad assaltarlo, ma quei cani sono riusciti a resistere nonostante le perdite. Sono tornato per rinforzi e...";
			link.l1 = "Non serve più, ormai. Ho sistemato i tuoi casini: il forte nella giungla è vuoto. Il comandante spagnolo Diego de Montoya è crepato, e la sua squadra è stata spazzata via.";
			link.l1.go = "catoche_2";
		break;
		
		case "catoche_2":
			dialog.text = "Che razza di giustizia sommaria è questa? Che ti spinge a scatenare un'azione militare simile su territorio inglese?";
			link.l1 = "Mi permetto di ricordarvi, Capitano Paterson, che non siamo a Belize. Quale possedimento inglese? Tutto questo trambusto è iniziato per colpa di Don Diego de Montoya e della sua sciagurata decisione di attaccare me e le mie navi.";
			link.l1.go = "catoche_3";
		break;
		
		case "catoche_3":
			dialog.text = "Ehm... e per quale ragione Don Diego ti ha assalito, eh capitano?";
			link.l1 = "Tra me e lui c’è una vecchia ruggine... Da quando la squadra che comandava attaccò Saint-Pierre, e poco dopo fu spazzata via con il mio diretto intervento.";
			link.l1.go = "catoche_4";
		break;
		
		case "catoche_4":
			dialog.text = "Per mille balene! Avevo bisogno che quel vecchio caballero restasse vivo! Volevo interrogarlo per capire perché ha messo su una base militare nella giungla. Non poteva certo farlo senza un valido motivo...";
			link.l1 = "Mi spiace, ma ora non può dirti nulla. Comunque, nel forte potrebbero esserci soldati feriti della guarnigione. C'è qualche speranza che possano parlare?";
			link.l1.go = "catoche_5";
		break;
		
		case "catoche_5":
			dialog.text = "Soldati... Ah, che ci faccio con questi cialtroni dal cervello di legno!... Dov’è il cadavere di Don Diego? Poteva avere addosso carte di gran valore!";
			link.l1 = "Ho lasciato Don Diego nel cortile del forte d’armi. Se ti serve così tanto, cercalo lì. Non credo che possa filarsela.";
			link.l1.go = "catoche_6";
		break;
		
		case "catoche_6":
			dialog.text = "Eh... e chi t’ha chiesto di ficcare il naso negli affari altrui... Mi hai già fatto venire il mal di testa...";
			link.l1 = "Capitano, non capisco perché mi rimproveri. Ho fatto il tuo lavoro, mandato i miei uomini a combattere, rischiato la mia stessa pelle, eppure non sei soddisfatto. Ora basta solo che tu annunci a Port Royal il successo della missione e sistemi i tuoi affari. Non pretendo alcun merito per la tua gloria, te lo assicuro.";
			link.l1.go = "catoche_7";
		break;
		
		case "catoche_7":
			dialog.text = "Prenderti il merito? Che vuoi dire con 'gloria'?! Non ci arrivi proprio... Eh, basta. Addio, signore.";
			link.l1 = "Tanti auguri anche a te!";
			link.l1.go = "catoche_8";
		break;
		
		case "catoche_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "GuardOT_OpenCatocheDoor", 10.0);
			sld = CharacterFromID("Archy");
			LAi_CharacterEnableDialog(sld);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 7.0);
			AddQuestRecord("Guardoftruth", "57");
		break;
		
		case "isladevieques":
			PlaySound("Voice\English\sharlie\Willie Paterson.wav");
			dialog.text = "Diavolo, le ciarle non mentono: hai più vite d'un gatto! "+TimeGreeting()+", Monsieur de Maure. Non avete un bell’aspetto...";
			link.l1 = TimeGreeting()+", Signor Paterson. Devo ammettere che tu e il tuo compare Archibald avete recitato la vostra parte e mi avete gabbato ben bene, maledetti bastardi! Non l’avevo proprio vista arrivare...";
			link.l1.go = "isladevieques_1";
		break;
		
		case "isladevieques_1":
			dialog.text = "Ehi, non bestemmiare davanti alle porte della Terra Santa. Non te l’aspettavi? Sono lusingato: ho ingannato uno degli intriganti più celebri dell’arcipelago. L’idea del diario era geniale, non trovi?\nDovevo attirarti in un posto appartato, ucciderti alla luce del sole sarebbe stato uno scandalo, sei un caro amico di Philippe de Poincy, sbaglio? Ora sparirai senza lasciare traccia e nessuno saprà mai come.";
			link.l1 = "Allora, tutto quello che mi ha raccontato Calhoun... era una bugia?";
			link.l1.go = "isladevieques_2";
		break;
		
		case "isladevieques_2":
			dialog.text = "Per niente. Ho davvero trovato il povero Archibald in questo posto. Però non ha scritto nessuna memoria, il diario che hai trovato nella sua stanza fu scritto su mia richiesta, proprio per te, Monsignore de Maure.\nTi tengo d’occhio fin da quando ci siamo incontrati a Capo Catoche. Sei stato tu a prendere la mappa delle Due Apparizioni dal cadavere di don Diego, vero? Non negare, so che sei stato tu.";
			link.l1 = "Anche tu sai del Guardiano della Verità?";
			link.l1.go = "isladevieques_3";
		break;
		
		case "isladevieques_3":
			dialog.text = "Che domanda sciocca. Certo che sì. E so anche che hai con te l’Artiglio del Capo. E molto presto restituirai ciò che non ti appartiene.";
			link.l1 = "Sono lieto che tu non vacilli come Don Diego. Apprezzo l’onestà e la franchezza. Se ho ben capito, hai tu la bussola, la Freccia della Via?";
			link.l1.go = "isladevieques_4";
		break;
		
		case "isladevieques_4":
			dialog.text = "Ah-ah! Bene, saremo sinceri fino alla fine... Davvero credete, signore, che io sia un balordo come voi e Don Diego, da andare in giro con un oggetto così prezioso addosso? La bussola sta in Giamaica, e nemmeno a Port Royal, ma in un posto dove nessuno penserebbe mai di cercare e sotto chiave sicura. Ma questa notizia non vi servirà.";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.OfficerKill"))
			{
				link.l1 = "A quanto pare, mi avete già dato per morto, signor Paterson? Mi permetto di annunciare che al gatto resta ancora una vita!... Dove sono i miei ufficiali?";
				link.l1.go = "isladevieques_5_1";
			}
			else
			{
				link.l1 = "A quanto pare, mi avete già dato per spacciato, signor Paterson? Ma oso dire che al gatto resta ancora una vita!";
				link.l1.go = "isladevieques_5_2";
			}
		break;
		
		case "isladevieques_5_1":
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.GirlKill"))
			{
				dialog.text = "Preoccupato per la tua dama, capitano? La tua donna giace laggiù tra i cespugli con un buco in fronte. Ti ha già spianato la strada e presto la raggiungerai. Perbacco, che bella ragazza era! Spero che tu l’abbia scopata più d’una volta, eh?";
				link.l1 = "È un figlio di puttana! La pagherai, maledetto bastardo?!";
				link.l1.go = "isladevieques_6";
			}
			else
			{
				dialog.text = "I vostri ufficiali hanno già tracciato il sentiero per voi, Monsieur de Maure. Giacciono laggiù tra quei cespugli. Presto li raggiungerete anche voi.";
				link.l1 = "Questo lo vedremo!";
				link.l1.go = "isladevieques_6";
			}
		break;
		
		case "isladevieques_5_2":
			dialog.text = "Faremo in modo che sia davvero l’ultima volta.";
			link.l1 = "Vedremo, mio caro!";
			link.l1.go = "isladevieques_6";
		break;
		
		case "isladevieques_6":
			dialog.text = "Mi fai ridere. Uno solo contro una schiera! Ma basta ciarlare... Puntate i moschetti! Fuoco!";
			link.l1 = "...";
			link.l1.go = "isladevieques_7";
		break;
		
		case "isladevieques_7":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться patch-8
			LAi_ActorRunToLocation(npchar, "quest", "teleport", "IslaDeVieques_HouseEntrance", "quest", "mushketer", "GuardOT_WillyGetReady", 10.0);
			for(i=1; i<=5; i++)
			{
				sld = CharacterFromID("GuardOT_willymushketer_"+i);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_WillyMushketerDie");
			DoQuestFunctionDelay("Terrapin_SetMusic", 0.2);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}

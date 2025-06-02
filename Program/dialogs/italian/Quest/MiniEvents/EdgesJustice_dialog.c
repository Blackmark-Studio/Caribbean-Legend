void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Cosa vuoi, forestiero?";
			link.l1 = "Niente.";
			link.l1.go = "exit";
		break;

		case "Naemnik":
			dialog.text = "Sei in gamba"+GetSexPhrase("","ess")+"... dannatamente buono"+GetSexPhrase("","ess")+"… Ma prima che tu finisca il lavoro, ascoltami. Son certo che quel che ho da dirti t’intrigherà.";
			link.l1 = "Suppongo tu possa dire le tue ultime parole prima di crepare. Ma non illuderti. Da questa caverna non ci esci vivo.";
			link.l1.go = "Naemnik_2";
		break;

		case "Naemnik_2":
			dialog.text = "Capo del porto, eh? Ti ha mandato a cercar la mia testa?";
			link.l1 = "Sei sempre sveglio come una faina.";
			link.l1.go = "Naemnik_3";
		break;

		case "Naemnik_3":
			dialog.text = "Ti ha mandato per uccidermi, vero? Non per trovarmi, non per catturarmi — per uccidermi.";
			link.l1 = "Esatto. E allora?";
			link.l1.go = "Naemnik_4";
		break;

		case "Naemnik_4":
			dialog.text = "Ah... sei proprio un tipo in gamba "+GetSexPhrase("testa di legno","piccolo sciocco")+"   Ti sei mai chiesto perché per lui era così importante vedermi morto invece che marcire in una cella? No? Non hai la minima idea di chi cerchi di salvare. Quello stramaledetto ragno della banchina ha tessuto una rete di menzogne su tutto questo posto, e tu, "+GetSexPhrase("ragazzo","tesoro")+", siete impantanati fino al collo.\nPensi davvero che sia un funzionario onesto? Ah! L’unica onestà che conosce la sogna mentre russa. Vende soffi ai bucaniere e agli olandesi. Tradisce chiunque gli dia fiducia. Un simile verme merita solo la fossa!";
			link.l1 = "E chi non pesta un po' di fango con gli stivali. Neanche tu sembri un frate, a veder bene.";
			link.l1.go = "Naemnik_5";
		break;

		case "Naemnik_5":
			dialog.text = "Non sono certo un monaco, né fingo d’esserlo. La mia lama non racconta bugie. Basta uno sguardo, e un uomo sa che la Morte è venuta per lui. Non sorrido alle mie prede né stringo loro la mano sapendo che sono già condannate. No. Le mie intenzioni sono limpide. Quel burocrate?\nTradisce chiunque gli dia fiducia, mentre fa finta di aiutare. È peggio di qualsiasi canaglia che abbia mai seppellito.";
			link.l1 = "Supponiamo che tu dica la verità. Chi ti ha assoldato?";
			link.l1.go = "Naemnik_6";
		break;

		case "Naemnik_6":
			dialog.text = "Non ti darò un nome – nemmeno lo conosco. Ma è uno che ha subito un torto da quella feccia. Un uomo che cerca giustizia... o vendetta, chiamala come ti pare. Cinquecento dobloni per la testa di quel lurido funzionario! Aiutami, e dividiamo il bottino.";
			link.l1 = "Basta con le tue chiacchiere! Diresti qualsiasi cosa pur di salvare la pellaccia. Ti ho lasciato parlare, ora è il momento di crepare.";
			link.l1.go = "Naemnik_7";
			link.l2 = "Bel racconto. Ma non ti crederò sulla parola. Hai qualcosa oltre alle tue chiacchiere? Prove, testimoni? O è solo un altro trucco per sfuggire alla morte?";
			link.l2.go = "Naemnik_8";
		break;
		
		case "Naemnik_7":
			DialogExit();
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("GS_Naemnik");
			LAi_SetImmortal(sld, false);
			LAi_SetCurHPMax(sld);
			LAi_GetCharacterMaxEnergy(sld);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheckFunction("EnemyFight", "GS_UbivaemNaemnika");
		break;
		
		case "Naemnik_8":
			dialog.text = "Queste pergamene furono scoperte nei quartieri di un corsaro, un cane di mare che il mio protettore ha spedito all'altro mondo a suon di ferro. Quel furfante riceveva dritta niente meno che dal Capo del Porto in persona. Qui dentro son segnate con cura rotte di navi, i loro orari di partenza e la natura del carico. Quelle stesse navi furono poi depredate, gli equipaggi massacrati o spariti tra gli abissi infiniti.\nTieni bene a mente – la mano che ha vergato queste note è la stessa che compila i registri ufficiali. Questa prova svelerà il traditore. Il mio protettore vuole che questi documenti vengano trovati sul suo cadavere. Una panca da magistrato non basterebbe.\nQuesto mascalzone ha troppo potere e una miriade di complici corrotti. Se mai finisse davanti alla corte, sguscierebbe via come un serpente. Simili ratti non meritano posto tra i figli di Dio. Solo la morte, con eterna infamia, può ricompensare un tradimento del genere.";
			link.l1 = "Maledetto traditore! Gli uomini gli affidano la propria sorte e lui svende la loro vita a tagliagole e mascalzoni! Conta su di me come alleato in questa faccenda. Una simile canaglia non merita di calpestare la terra di Dio.";
			link.l1.go = "Naemnik_9";
			GiveItem2Character(PChar, "GS_letters");
			AddQuestRecordInfo("GS_Letters", "1");
		break;

		case "Naemnik_9":
			dialog.text = "Mi procurai una chiave per la sua dimora – grazie al falegname che aggiustava i mobili in quel palazzo da gran signore. Tutto filò liscio finché scoprii che condivide i suoi alloggi. Quando entrai per fargli assaggiare la giustizia, la sua signora era presente.\nLa sua compagnia inattesa mi fece esitare. Nessuna taglia pendeva sul suo capo, e gli sbirri di Sua Maestà avrebbero cacciato con ben più foga chi avesse ammazzato una donna di rango. Così cambiai rotta e lo attesi nei pressi della dogana.";
			link.l1 = "Fuoco dell’inferno e maledizione! Ora tutta la città è in allerta – non possiamo più colpire allo scoperto come prima. Che strada ci resta da seguire?";
			link.l1.go = "Naemnik_10";
		break;

		case "Naemnik_10":
			dialog.text = "I've kept watch over the town, biding my time until the commotion subsided. After my attempt, that cowardly rat hurried to hide away his wife. With my own eyes I saw her board a vessel and leave the harbor\nNow he remains alone - the perfect time to finish what we started. Under cover of darkness, you can slip into his lair and end this business. Then leave these damning papers where they cannot be missed, so all may know the foul corruption that festered within his heart\nBut for me, the town gates are barred. You, however... you can succeed where I cannot. No guard searches for your face; you'll pass their watch with ease. His house is near the city prison. Five hundred doubloons! Half this bounty will be yours when the traitor lies dead.";
			link.l1 = "Così sia. Con la mia stessa mano manderò questo furfante a rendere conto al Creatore. Questi documenti resteranno nella sua dimora – così che tutti possano conoscere la verità del suo tradimento. Attendimi. Tornerò quando la giustizia sarà fatta.";
			link.l1.go = "Naemnik_11";
		break;
		
		case "Naemnik_11":
			DialogExit();
			chrDisableReloadToLocation = false;
			locations[FindLocation("Beliz_Cave")].DisableEncounters = false;
			AddQuestRecord("GS", "5");
			AddQuestUserData("GS", "sSex", GetSexPhrase("","а"));
			
			sld = CharacterFromID("GS_Naemnik");
			LAi_SetWarriorType(sld);
			LAi_SetCurHPMax(sld);
			LAi_GetCharacterMaxEnergy(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
			NextDiag.CurrentNode = "Naemnik_12";
			
			sld = &Locations[FindLocation("Beliz_town")];
			sld.reload.l11.open_for_night = 1;
			sld = &Locations[FindLocation("Beliz_houseS5_room2")];
			sld.locators_radius.item.button01 = 1.0;
			
			pchar.quest.GS_SoldatyDoma.win_condition.l1 = "Hour";
			pchar.quest.GS_SoldatyDoma.win_condition.l1.start.hour = 0.00;
			pchar.quest.GS_SoldatyDoma.win_condition.l1.finish.hour = 5.00;
			PChar.quest.GS_SoldatyDoma.win_condition.l2 = "location";
			PChar.quest.GS_SoldatyDoma.win_condition.l2.location = "Beliz_houseS5";
			PChar.quest.GS_SoldatyDoma.function = "GS_SoldatyDoma";
		break;
		
		case "Naemnik_12":
			dialog.text = "Perché resti lì impalato, come se avessi i piedi piantati nella pece?";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Naemnik_12";
		break;

		case "Portman_1":
			dialog.text = "Tu? Che diavolo? Come sei entrato qui?";
			link.l1 = "Come ci sono arrivato non conta un accidente. E credo che, in fondo, tu sappia bene perché sono venuto.";
			link.l1.go = "Portman_2";
			DelLandQuestMark(npchar);
		break;

		case "Portman_2":
			dialog.text = "No, non capisco! Se sei venuto per la ricompensa, allora presentati domani all'amministrazione, ti darò tutto quanto.";
			link.l1 = "Smettila di fare il finto innocente! So tutto. Hai venduto informazioni sui vascelli dei tuoi clienti ai pirati. Un furfante come te non merita di occupare certi incarichi. Anzi, non meriti nemmeno di vivere tra gente onesta. Signore, il tuo posto è tra i tuoi pari – all'inferno.";
			link.l1.go = "Portman_3";
		break;

		case "Portman_3":
			dialog.text = "Oh, no-no-no! No! Hai capito tutto male! Mi hanno costretto... Sono venuti da me e hanno minacciato la mia famiglia se non li avessi aiutati... non capisci...";
			link.l1 = "Ne ho abbastanza delle tue miserabili scuse! Ho le tue note tra le mani, dove pretendi la tua parte sulle mance! La tua ipocrisia mi fa schifo, e non intendo più sopportarla. Sfodera la lama e difenditi, se hai fegato!";
			link.l1.go = "Portman_4";
		break;
		
		case "Portman_4":
			DialogExit();
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Beliz_portman_clone");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheckFunction("EnemyFight", "GS_PortmanDead");
		break;
		
		case "Naemnik_21":
			dialog.text = "E allora, quali novità? Abbiamo chiuso i nostri affari?";
			link.l1 = "Dubitavi forse di me? Quel miserabile si sforzò con tutte le sue forze di sputare una qualche miserabile scusa, ma fu tutto vano. Ho lasciato i documenti incriminanti dove nessuno potrà ignorarli, proprio come pattuito.";
			link.l1.go = "Naemnik_22";
		break;

		case "Naemnik_22":
			dialog.text = "Vermi codardi come lui pensano sempre di poter comprare la clemenza della Giustizia con menzogne vili e sonanti monete.";
			link.l1 = "Ebbene, i suoi pensieri non lo tormentano più. Dammi la mia ricompensa e me ne andrò.";
			link.l1.go = "Naemnik_23";
		break;

		case "Naemnik_23":
			dialog.text = "Ecco i tuoi dobloni, ben guadagnati. Un lavoro pulito, lo riconosco. Ma ascolta bene – se la mia mano avesse stretto acciaio più fermo quando prima incrociammo le lame, la sorte avrebbe potuto voltarsi assai diversamente... a tuo eterno rammarico. In quelle camere anguste, una vera arma non può menare colpi giusti, così portavo solo questo miserabile stuzzicadenti, pensando di spedirti all'altro mondo in fretta e senza fronzoli.\nSe avessi previsto come sarebbero andate le cose, mi sarei armato con una lama più degna d'un uomo del mio stampo.";
			link.l1 = "Ah! Il nostro compianto compare t’aveva vantato armato come Orlando alla gola di Roncisvalle! Che paladino sei stato, davvero.";
			link.l1.go = "Naemnik_24";
			AddItems(pchar, "gold_dublon", 250);
		break;

		case "Naemnik_24":
			dialog.text = "Eheh. La paura getta ombre immense, non è vero? Hai visto coi tuoi stessi occhi quel misero ferro da mensa con cui quasi ti ho trafitto il cuore pulsante.";
			link.l1 = "Insinui forse che, con dell’acciaio più pesante in pugno, saresti stato un degno avversario per me?";
			link.l1.go = "Naemnik_25";
		break;

		case "Naemnik_25":
			dialog.text = "Nella maestria delle lame di medio peso, nessuno eguaglia la mia abilità – lo giuro sul mio stesso sangue. Dubiti forse? Bene allora. Ti insegnerò certe astuzie di scherma che mi hanno salvato da mille pericoli. Ascolta bene – non sono fandonie d’osteria, ma saggezza che un giorno potrebbe toglierti la morte di dosso. Simili segreti si rivelano solo ai pupilli più degni.";
			link.l1 = "...";
			link.l1.go = "Naemnik_26";
		break;
		
		case "Naemnik_26":
			DialogExit();
			SetLaunchFrameFormParam("An hour passes...", "Run_Function", 0, 4.0);
			SetLaunchFrameRunFunctionParam("GS_Spravedlivost_2", 0.0);
			LaunchFrameForm();
		break;

		case "Naemnik_27":
			dialog.text = "...";
			link.l1 = "Vedo che sei davvero un maestro nel tuo mestiere. Ti ringrazio per il tuo insegnamento. Ma se i nostri affari sono conclusi, devo mettermi in cammino.";
			link.l1.go = "Naemnik_28";
			AddComplexSelfExpToScill(0, 500, 0, 0);
		break;

		case "Naemnik_28":
			dialog.text = "Buon viaggio, "+GetSexPhrase("Capitano","gentildonna")+". Speriamo di non incrociare più le spade. Mi dispiacerebbe troppo rispedirti al creatore. Ah-ah.";
			link.l1 = "Non avresti una briciola di speranza, nemmeno se fossi ubriaco fradicio e in piedi su una sola gamba! Addio, spadaccino a pagamento.";
			link.l1.go = "Naemnik_29";
		break;
		
		case "Naemnik_29":
			DialogExit();
			chrDisableReloadToLocation = false;
			locations[FindLocation("Beliz_Cave")].DisableEncounters = false;
			LAi_SetPlayerType(pchar);
			
			LAi_SetWarriorType(npchar);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PEACE);
			
			AddQuestRecord("GS", "7");
			CloseQuestHeader("GS");
			
			AddSimpleRumourCity("Word has it the Port Chief was found dead in his own home. Documents were discovered on his body proving his involvement in the disappearance of ships. Just imagine—what a disgrace for our town...", "Beliz", 30, 1, "");
			AddSimpleRumourCity("Have you heard the news? Someone snuck into the Port Chief’s house, killed the guards, and took him out. They found notes on the body with routes of missing ships—written in his own hand! A servant of the Crown, yet a traitor in truth! Got what he deserved! And where was the Governor all these years?", "Beliz", 30, 1, "");
			AddSimpleRumourCity("The Port Master is dead! Killed right in his own home! The guards were slaughtered, and among his possessions were notes mapping routes of vanished ships. No doubt about it—he was behind the disappearances! Justice has finally caught up with the scoundrel.", "Beliz", 30, 1, "");
			break;
	}
}
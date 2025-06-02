// Алонсо де Мальдонадо
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
			dialog.text = "C'è qualcosa di cui hai bisogno?";
			link.l1 = "No, nulla.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "ksochitam":
			dialog.text = "Fermati, Capitano "+GetFullName(pchar)+"...";
			link.l1 = "In qualche modo non mi sorprende nemmeno più vedere soldati spagnoli qui... Ormai mi sono abituato ad avere sempre qualcuno alle calcagna. Che vai cercando su quest’isola maledetta, castigliano? Vuoi forse trovare una tomba rapida per i tuoi stivali?";
			link.l1.go = "ksochitam_1";
		break;
		
		case "ksochitam_1":
			dialog.text = "Il mio nome è Alonso de Maldonado. Forse non ti dirà nulla, ma Diego de Montoya dovrebbe accendere qualche ricordo. Era il mio più caro amico. Mi ha salvato la pelle e adesso il suo sangue grida vendetta per colpa tua.";
			link.l1 = "Immagino che tu mi abbia seguito fin qui per cercare vendetta?";
			link.l1.go = "ksochitam_2";
		break;
		
		case "ksochitam_2":
			dialog.text = "Non cerco soltanto vendetta. Da quel che so, tu hai la maschera di Kukulcan?";
			link.l1 = "Per mille balene! Un altro cercatore di tesori! Vieni forse a finire qualche faccenda lasciata in sospeso da Don Diego?";
			link.l1.go = "ksochitam_3";
		break;
		
		case "ksochitam_3":
			dialog.text = "Non mi interessano i tesori. Ho visto quali ricchezze si nascondono a Tayasal. Miguel Dichoso non è riuscito a portare via che una briciola. È la maschera che voglio.";
			link.l1 = "Sei stato a Tayasal? Questa mi sembra grossa. Se la memoria non m’inganna, l’unico sopravvissuto di quella spedizione fu Dichoso.";
			link.l1.go = "ksochitam_4";
		break;
		
		case "ksochitam_4":
			dialog.text = "Vent'anni prima che quel povero Dichoso mettesse piede a Tayasal, ci sono arrivato io. Proprio quando quel mago folle di Kanek usò il maledetto sacrificio umano per nascondere la maschera in quest’isola.";
			link.l1 = "Non posso credere alle mie orecchie! Fai parte di quella stessa banda di conquistadores che fu portata lì per essere sacrificata durante la creazione del Guardiano della Verità? Siete tutti morti!";
			link.l1.go = "ksochitam_5";
		break;
		
		case "ksochitam_5":
			dialog.text = "Non tutti noi. Io sono sopravvissuto.";
			link.l1 = "Perché gli Itza hanno deciso di risparmiarti? Che diavolo hai tu di così speciale?";
			link.l1.go = "ksochitam_6";
		break;
		
		case "ksochitam_6":
			dialog.text = "Non potresti capire. Dannazione, nemmeno io ci ho capito un accidente. Nessuno mi ha risparmiato. Lo ricordo come fosse ieri... Appena quel selvaggio ha preso un pugnale e ha spellato una striscia di pelle dalla schiena di Casco, poi l’ha fatto fuori e ha cominciato a ululare come un forsennato, credo di esser stato risucchiato dentro quell’idolo maledetto. Mi sono risvegliato lontano da Tayasal vent’anni dopo, come se fosse passato solo un battito di ciglia!";
			link.l1 = "Un dannato imbuto spazio-temporale... Maledizione, tutto quello che ha detto Ksatl Cha era proprio vero! Come hai scoperto della maschera? E che diavolo te ne fai?";
			link.l1.go = "ksochitam_7";
		break;
		
		case "ksochitam_7":
			dialog.text = "Devo fermare la progenie dell’inferno, evocata da uno stregone indiano impazzito. Questa abominazione vuole ridurre il nostro mondo in un rogo!";
			link.l1 = "Hmm... Hai parlato con padre Vincento, vero? L’Inquisitore tiene il piede in due scarpe, che novità. Ti ha mandato a stanarmi per un duello all’ultimo sangue? Complimenti! Missione compiuta, Don Alonso!";
			link.l1.go = "ksochitam_8";
		break;
		
		case "ksochitam_8":
			dialog.text = "Il Signore rafforza la mia mano in battaglia contro il male. Tornerò a Tayasal e userò la maschera per chiudere per sempre i portali. E nessun demonio in sembianze d’uomo metterà più piede nel nostro mondo.";
			link.l1 = "C’è solo un piccolo intoppo nel tuo piano, Don Alonso. Il demonio è GIÀ tra noi. Tutto ciò che dobbiamo fare è non lasciarlo USCIRE da queste porte. Non ci riuscirà finché la maschera resterà lontana dalle sue grinfie.";
			link.l1.go = "ksochitam_9";
		break;
		
		case "ksochitam_9":
			dialog.text = "Ci vorrà ben altro. Chiunque di noi abbia ragione, una cosa è certa: i cancelli vanno chiusi per sempre. E c’è un solo modo per riuscirci: distruggere la maschera sull'altare di Tayasal. Così facendo, al demonio verrà strappato ogni suo potere.";
			link.l1 = "Hm. Sono d’accordo che sia la nostra miglior scommessa... Ma come pensi di arrivare a Tayasal? Sai già la rotta?";
			link.l1.go = "ksochitam_10";
		break;
		
		case "ksochitam_10":
			dialog.text = "Il sentiero facile che usavamo un tempo ormai non esiste più. Le strade sono sepolte sotto le pietre e inghiottite dalla giungla. C’è un altro modo per raggiungere la città, ma è lungo e rischioso. Il cammino parte dalla baia più a nord dello Yucatan. \nCon l’aiuto di padre Vincento e don Ramon de Mendoza metterò insieme una squadra di soldati scelti e ci apriremo la strada a colpi di spada nella selva, difesa dai selvaggi Itza. Non sarà una passeggiata, ma Dio ci darà forza e coraggio per combattere in nome della nostra fede.";
			link.l1 = "Don Alonso, le mie ambizioni sembrano proprio incrociarsi con le vostre. Non sarebbe ora di mettere da parte i vecchi rancori e di unire le nostre forze? Insieme avremo assai più fortuna a portare a termine questa crociata.";
			link.l1.go = "ksochitam_11";
		break;
		
		case "ksochitam_11":
			dialog.text = "Io sono un soldato spagnolo. Non stringo alleanze con eretici né scendo a patti con francesi. Inoltre, ti ho già dichiarato la mia vendetta per Don Diego. Vita per vita!";
			link.l1 = "Sei testardo come un mulo, Don Alonso! Te ne stai lì a predicare che il mondo è minacciato da un gran male, eppure rifiuti il mio aiuto per compiere un'impresa tanto colossale!";
			link.l1.go = "ksochitam_12";
		break;
		
		case "ksochitam_12":
			dialog.text = "Adesso comando io, non padre Vincento! Recita le tue preghiere e preparati a crepare, capitano francese!..";
			link.l1 = "Oh, quante volte ho sentito queste parole negli ultimi mesi! In guardia, testone di caballero!";
			link.l1.go = "ksochitam_13";
		break;
		
		case "ksochitam_13":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Maldonado_soldier_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Maldonado_mushketer_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Ksochitam_MaldonadoDie");
			AddDialogExitQuest("MainHeroFightModeOn");
			if (MOD_SKILL_ENEMY_RATE > 4) Ksochitam_CreateMaldonadoHelpers();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

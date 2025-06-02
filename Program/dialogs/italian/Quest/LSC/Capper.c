// Чад Каппер - боцман Акулы и тюремщик
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
			dialog.text = "Desideri qualcosa?";
			link.l1 = "No, non è nulla.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// вариант R
		case "Chimiset":
			dialog.text = "Ebbene... Dunque sei tu il famigerato ladro? Mh... Non hai proprio l’aria di un miserabile rubagalline.";
			link.l1 = "Ascolta, signore, ti sbagli. Sono appena arrivato su questa dannata isola, come potevo sapere che la stiva dove la tua gente mi ha preso fosse una tua zona privata?";
			link.l1.go = "Chimiset_1";
		break;
		
		case "Chimiset_1":
			dialog.text = "Davvero? Bel tentativo, compare... E allora, da dove sbuchi fuori tu?";
			link.l1 = "Dal Principale... Attraverso una strana statua. Io stesso non so come spiegare ciò che è accaduto.";
			link.l1.go = "Chimiset_2";
		break;
		
		case "Chimiset_2":
			dialog.text = "Statua? Ah-ah! Sei proprio uno spiritoso, eh... Va bene, te lo spiego io: sei passato dal buco nello scafo e volevi intrufolarti nel nostro magazzino. Ma come mai non ti riconosco la faccia? Io conosco tutti i Rivados...";
			link.l1 = "Quali Rivados? Non so di che parli! Ascolta, sono arrivato qui solo un’ora fa...";
			link.l1.go = "Chimiset_3";
		break;
		
		case "Chimiset_3":
			dialog.text = "Non urlare, non sono uno scimunito. Sì, ho sentito abbastanza delle tue fandonie sulla statua e, lo ammetto, mi fanno pure ridere. Anzi, mi fanno crepare dal ridere. Ridiamo insieme, che ne dici? Ah-ah-ah!... Come mai non ridi? Era una bella burla... Rivados. Ma ora basta scherzare. Ti lascio marcire in cella, compare.";
			link.l1 = "Non sono un Rivados! Il mio nome è Charles de Maure!";
			link.l1.go = "Chimiset_4";
		break;
		
		case "Chimiset_4":
			dialog.text = "Prima volta, eh? Mh... forse dici davvero la verità. Dimmi, sei uno di loro?!";
			link.l1 = "Ti giuro sulla mia anima, mai sentito quel nome prima d’ora, non sono dei loro!";
			link.l1.go = "Chimiset_5";
		break;
		
		case "Chimiset_5":
			dialog.text = "Davvero? Bene. Dimostralo. Scendi giù, c'è un Rivados seduto in gabbia. È uno stregone pericoloso. Uccidilo, solo allora sarò convinto. Dimenticherò anche la tua intrusione illegale nel nostro magazzino. \nAllora? Sei pronto? Non avere paura, lo stregone è disarmato e debole. Beh, potrebbe anche ridurti in cenere con qualche incantesimo, come quello che ti ha spedito nella stiva di San Agostino...";
			link.l1 = "Se avessi visto quell’incantesimo all’opera, non saresti così scettico. Dubito persino che ne saresti uscito vivo...";
			link.l1.go = "Chimiset_6";
		break;
		
		case "Chimiset_6":
			dialog.text = "Basta chiacchiere! Lo fai o no? Se sì, prendi questo machete e sistemami quel mago. Altrimenti passerai il resto dei tuoi giorni in gabbia. Chiaro?";
			link.l1 = "Tra due mali scelgo quello minore. Passami il machete.";
			link.l1.go = "Chimiset_7";
		break;
		
		case "Chimiset_7":
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "slave_02");
			EquipCharacterbyItem(pchar, "slave_02");
			dialog.text = "Bravo ragazzo. Prendi, vai e ammazza quel negro. La sua gabbia è aperta. Ma non fare lo stupido, ché non ci faremo scrupolo a tagliarti la gola al solo sospetto! Ora fila!";
			link.l1 = "Perché? Hai paura che vi sventri tutti con questo pezzo di ferro arrugginito, eh?";
			link.l1.go = "Chimiset_8";
		break;
		
		case "Chimiset_8":
			dialog.text = "La mia pazienza è agli sgoccioli. Scendi nella stiva e fai come ti si comanda!";
			link.l1 = "Va bene, va bene, calmati. Me ne vado...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Chimiset_9";
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//разлочим Ф2
		break;
		
		case "Chimiset_9":
			dialog.text = "Stai mettendo a dura prova la mia pazienza, bastardo! Non ti conviene farmi perdere le staffe...";
			link.l1 = "Va bene, va bene, calmati.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Chimiset_9";
		break;
		
		case "Fightfail_Final":
			dialog.text = "Hai fatto fuori quel negromante? Bene... Mi rallegra. Ora so che non sei dei Rivados.";
			link.l1 = "Quando diavolo mi lasceranno finalmente uscire da questa dannata bagnarola? Devo incontrare lo Squalo subito.";
			link.l1.go = "Fightfail_Final_1";
		break;
		
		case "Fightfail_Final_1":
			dialog.text = "Lo incontrerai, certo... Lo incontrerai sulla via per l'inferno!";
			link.l1 = "Cosa?!";
			link.l1.go = "Fightfail_Final_2";
		break;
		
		case "Fightfail_Final_2":
			DialogExit();
			DoQuestCheckDelay("LSC_ChadGuardAttack_Fail", 0.1);
		break;
		
		// вариант N
		case "prisoner":
			dialog.text = "Ah! Guarda un po’. Che ci fai nella mia prigione, eh?";
			link.l1 = "Il tuo nome è Chad Kapper, giusto? Io mi chiamo "+GetFullName(pchar)+" e sono qui per conto di Shark Dodson. Mi ha dato le chiavi.";
			link.l1.go = "prisoner_1";
		break;
		
		case "prisoner_1":
			dialog.text = "Dall'ammiraglio, dici? Mh, capisco. Sei forse il suo nuovo galoppino?";
			link.l1 = "Porta un po’ di rispetto, forestiero. Non servo nessuno, né lo Squalo né te, e non intendo tollerare simili parole.";
			link.l1.go = "prisoner_2";
		break;
		
		case "prisoner_2":
			dialog.text = "Ah-ah, mi piaci, compare! Dimentica quello che ho detto... Allora, che vento ti porta su questa isola?";
			link.l1 = "Squalo ha ordinato di liberare Chimiset, è rinchiuso qui.";
			link.l1.go = "prisoner_3";
		break;
		
		case "prisoner_3":
			dialog.text = "Lo stregone dei Rivados? Mh. Che strano, davvero non me l’aspettavo...";
			link.l1 = "Squalo ha dato un ordine. Vuole fare pace coi Rivados.";
			link.l1.go = "prisoner_4";
		break;
		
		case "prisoner_4":
			dialog.text = "A-ah, ora capisco. Va bene, manderò un uomo dai Rivados. Verranno qui a riprendersi il loro buffone.";
			link.l1 = "Perché non puoi semplicemente lasciarlo andare?";
			link.l1.go = "prisoner_5";
		break;
		
		case "prisoner_5":
			dialog.text = "Potrei, ma per lui sarebbe troppo rischioso. Chimiset qui è ben conosciuto, la sua vita non varrebbe un soldo bucato appena mette piede sulla 'Esmeralda' — territorio dei suoi nemici, i Narvali. Non c’è altra via dalla Tartarus, non possiamo lasciare che il vecchio nuoti intorno all’isola! E se qualcuno lo manda all’altro mondo, i Rivados daranno la colpa a noi, a me in particolare! Vedi, non voglio grane che si possono evitare. Quindi lo lascerò uscire solo sotto la scorta dei guerrieri del suo clan. Forse vuoi parlare tu stesso con Chimiset? È un tipo buffo...";
			if (CheckAttribute(npchar, "quest.chimiset_talk")) link.l1 = "Ho già parlato con lui, è davvero un tipo bizzarro. Comunque, devo andare. A presto, Chad!";
			else link.l1 = "Era proprio quello che avevo in mente. Andrò a parlargli.";
			link.l1.go = "prisoner_6";
		break;
		
		case "prisoner_6":
			DialogExit();
			sld = characterFromId("Chimiset");
			sld.quest.capper_talk = "true"; // разговор с Каппером состоялся
			if (!CheckAttribute(npchar, "quest.chimiset_talk")) chrDisableReloadToLocation = true;//закрыть локацию
			else chrDisableReloadToLocation = false;//открыть локацию
			NextDiag.CurrentNode = "prisoner_7";
		break;
		
		case "prisoner_7":
			dialog.text = "Manderò un messaggero dai Rivados e si prenderanno il loro stregone. Non temere, compare, puoi andare.";
			link.l1 = "Va bene.";
			link.l1.go = "exit";
			NextDiag.TempNode = "prisoner_7";
		break;
		
		// вариант M
		case "Aeva_attack":
			dialog.text = "...avrà già scassinato la botte, ne sono certo. È il suo whiskey prediletto, maledetto irlandese. Presto finirà, ci ho messo tanto arsenico da stecchire un branco intero...";
			link.l1 = "";
			link.l1.go = "Aeva_attack_1";
			CharacterTurnToLoc(npchar, "quest", "quest2");
		break;
		
		case "Aeva_attack_1":
			dialog.text = "Eh? Maledizione, che ci fai qui? Sparisci dai piedi!";
			link.l1 = "Ero sulle tue tracce da tempo... avvelenatore. Strano, non vedo il Ciclope. Volevi prendere il posto dello Squalo, vero?";
			link.l1.go = "Aeva_attack_2";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Aeva_attack_2":
			dialog.text = "Ah-ah, lo Squalo sarà già crepato ormai! E tu lo raggiungerai presto, spione!";
			link.l1 = "...";
			link.l1.go = "Aeva_attack_fight";
		break;
		
		case "Aeva_attack_fight":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("ChadNarval_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LSC_CapperDieAeva");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Aeva_attack_2":
			dialog.text = "... questa sarà una bevuta infernale. Quel dannato irlandese sogna questo whiskey da una vita, se lo tracannerà in un lampo. Dov’è l’arsenico? Versane ancora, per sicurezza... Poi il nostro buon Fazio porterà questa botte all’ammiraglio, come regalo dai Narvali, ah-ah! Non è vero, caro Giuseppe? Vuoi campare ancora un po’?\nDannazione! Guarda chi si vede! Che vuoi, scarto di balena? Sparisci prima che ti inchiodiamo!";
			link.l1 = "Il tuo piano è andato in fumo, Kapper. Ho seguito le tue orme e so bene cosa tu e il tuo compare Ciclope avete in mente. Butta via l’arsenico! Non avvelenerai Squalo!";
			link.l1.go = "Aeva_attack_3";
		break;
		
		case "Aeva_attack_3":
			dialog.text = "Ah, segugio! Allora sarai tu il primo a crepare! Ragazzi, alle armi!";
			link.l1 = "...";
			link.l1.go = "Aeva_attack_fight";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}

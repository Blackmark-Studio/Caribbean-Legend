void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n;
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
			dialog.text = "Cosa vi serve?";
			link.l1 = "Niente.";
			link.l1.go = "exit";
		break;
		
		case "SKD_DomAnri":
			dialog.text = "Benvenuti nella mia dimora, signori. In che posso esservi utile?";
			link.l1 = "Levasseur manda i suoi saluti, monsieur.";
			link.l1.go = "SKD_DomAnri_2";
			StartQuestMovie(true, false, true);
		break;
		
		case "SKD_DomAnri_2":
			dialog.text = "Ah, è così che stanno le cose... Alicia! Lasciaci, per favore. Questi signori hanno affari con me.";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_2_1";
			CharacterTurnToLoc(npchar, "goto", "goto1");
		break;
		case "SKD_DomAnri_2_1":
			StartInstantDialog("SKD_Alisia", "SKD_DomAnri_3", "Quest\CompanionQuests\Duran.c");
		break;
		
		case "SKD_DomAnri_3":
			dialog.text = "Ma...";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_3_1";
			CharacterTurnToLoc(npchar, "barmen", "stay");
		break;
		case "SKD_DomAnri_3_1":
			StartInstantDialog("SKD_Anri", "SKD_DomAnri_4", "Quest\CompanionQuests\Duran.c");
		break;
		
		case "SKD_DomAnri_4":
			dialog.text = "Ti adoro, tesoro. Avanti allora!";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_5";
			CharacterTurnToLoc(npchar, "goto", "goto1");
		break;
		
		case "SKD_DomAnri_5":
			DialogExit();
			locCameraFromToPos(3.47, 2.41, 0.10, false, -1.05, 0.20, -0.07);
			
			sld = CharacterFromID("SKD_Anri");
			CharacterTurnByLoc(sld, "barmen", "stay");
			
			sld = CharacterFromID("SKD_Alisia");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "", "", "", "", -1);
			sld.location = "None";
			sld.lifeday = 0;
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("SKD_DomAnri_2", 4.0);
		break;
		
		case "SKD_DomAnri_6":
			dialog.text = "Miracoli del cielo, mio Capitano! Valeva la pena perder tutto pur di incontrare l’amore della propria vita nei confini del mondo! Signori, sono nelle vostre mani. Non penserete davvero di lasciarmi fuori dall’affare, vero?";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_6_1";
		break;
		case "SKD_DomAnri_6_1":
			StartInstantDialog("Duran", "SKD_DomAnri_7", "Quest\CompanionQuests\Duran.c");
		break;
		
		case "SKD_DomAnri_7":
			dialog.text = "No, e non provare nemmeno a chiedere pietà.";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_7_1";
			CharacterTurnToLoc(npchar, "barmen", "stay");
			locCameraFromToPos(-0.52, 1.47, 0.76, false, -2.52, 0.20, 0.99);
		break;
		case "SKD_DomAnri_7_1":
			StartInstantDialog("SKD_Anri", "SKD_DomAnri_8", "Quest\CompanionQuests\Duran.c");
		break;
		
		case "SKD_DomAnri_8":
			dialog.text = "Non si addice a un Cavaliere dell’Ordine chiedere pietà.";
			link.l1 = "Un tempo ero cavaliere, sai.";
			link.l1.go = "SKD_DomAnri_9";
		break;
		
		case "SKD_DomAnri_9":
			dialog.text = "I burocrati non avrebbero abbastanza inchiostro al mondo per strapparmi quel titolo.";
			link.l1 = "In tal caso, dimostralo.  Ma prima, soddisfa la mia curiosità: Sei forse un traditore della Corona? Altrimenti, non capisco perché Levasseur desiderasse tanto la tua testa.";
			link.l1.go = "SKD_DomAnri_10";
		break;
		
		case "SKD_DomAnri_10":
			dialog.text = "Resto fedele al mio giuramento, monsieur, quindi non me ne vogliate. Dirò solo che un traditore della Corona mi ha mandato a far fuori un altro traditore. E continuerà a farlo, finché un Fratello più abile di me non porterà a termine l’impresa. Basta parole. Signori, avanti alla battaglia!";
			link.l1 = "...";
			link.l1.go = "SKD_DomAnri_11";
		break;
		
		case "SKD_DomAnri_11":
			DialogExit();
			EndQuestMovie();
			
			sld = CharacterFromID("Duran");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetFightMode(pchar, true);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "SKD_DomAnri_6");
		break;
		
		case "SKD_DomAnri_12":
			dialog.text = "Ah-ah! Oh, grazie, Capitano. Era proprio un diavolo tosto, quello lì. Da solo non l’avrei mai steso.";
			link.l1 = "In qualche modo, questa vittoria non mi riempie di gioia. Direi che qui abbiamo finito, vero?";
			link.l1.go = "SKD_DomAnri_13";
		break;
		
		case "SKD_DomAnri_13":
			dialog.text = "Non proprio, prima dobbiamo ripulire e far fuori la ragazza che è corsa via al secondo piano.";
			link.l1 = "Cosa?! Ferma la mano! Hai perso il senno, Claude? Non sono mica un assassino di strada!";
			link.l1.go = "SKD_DomAnri_14";
		break;
		
		case "SKD_DomAnri_14":
			dialog.text = "Non devi fare nulla, Capitano. In fondo, la colpa è tutta tua: non avresti dovuto parlarle di Levasseur.";
			link.l1 = "Queste sono fandonie e lo sai bene. E se osi rifilarmi un’altra ramanzina sconclusionata, stavolta non la passerai liscia.";
			link.l1.go = "SKD_DomAnri_15";
		break;
		
		case "SKD_DomAnri_15":
			dialog.text = "Heh! Colpa mia, Capitano. Hai ragione, gli ordini di Levasseur erano chiari: non solo il cavaliere, ma pure tutta la sua ciurma doveva sparire. Tutti, capisci? Gente con cui non si scherza, e le loro richieste vanno prese sul serio. Non ostacolarmi, Capo. Solo quest’ultimo lavoretto sporco e poi sarò tuo fedele fino all’ultimo respiro, te lo giuro!";
			if (IsCharacterPerkOn(pchar, "Trustworthy") && sti(pchar.reputation.nobility) > 70)
			{
				notification("Reputation Check Passed", "None");
				notification("Trustworthy", "Trustworthy");
				link.l1 = "(Fidato) (Onore) Una volta hai detto che ero destinato a volare alto, e che eri lieto di darmi una spinta.";
				link.l1.go = "SKD_DomAnri_VD";
			}
			else
			{
				notification("Reputation Too Low! ("+XI_ConvertString(GetReputationName(71))+")", "None");
				notification("Perk Check Failed", "Trustworthy");
			}
			link.l2 = "Al diavolo te! Fai il tuo lurido lavoro. Accetto il tuo giuramento, e faresti meglio a prenderlo terribilmente sul serio. Siamo d’accordo, eh?";
			link.l2.go = "SKD_DomAnri_DuranDruzhba";
			link.l3 = "Non a questo prezzo, Claude. Non ti lascerò ammazzare quella ragazza.";
			link.l3.go = "SKD_DomAnri_DuranDraka";
		break;
		
		case "SKD_DomAnri_DuranDraka":
			dialog.text = "Heh! Pare che fossimo nati per farci la pelle a vicenda, eh, Capitano?";
			link.l1 = "Suppongo di sì. Riprendiamo da dove abbiamo lasciato a Tortuga, che ne dici?";
			link.l1.go = "SKD_DomAnri_DuranDraka_2";
		break;
		
		case "SKD_DomAnri_DuranDraka_2":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			
			RemovePassenger(pchar, npchar);
			npchar.SaveItemsForDead = true;
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			
			LAi_SetFightMode(pchar, true);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "SKD_DomAnri_DuranDraka");
		break;
		
		case "SKD_DomAnri_DuranDruzhba":
			dialog.text = "Ai vostri ordini, Capitano!";
			link.l1 = "...";
			link.l1.go = "SKD_DomAnri_DuranDruzhba_2";
		break;
		
		case "SKD_DomAnri_DuranDruzhba_2":
			DialogExit();
			
			LocatorReloadEnterDisable("PortRoyal_houseSp1", "reload2", true);
			sld = CharacterFromID("Duran");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			chrDisableReloadToLocation = false;
			LAi_LocationDisableOfficersGen("PortRoyal_town", true);
			
			PChar.quest.SKD_DomAnri_DuranDruzhba.win_condition.l1 = "location";
			PChar.quest.SKD_DomAnri_DuranDruzhba.win_condition.l1.location = "PortRoyal_town";
			PChar.quest.SKD_DomAnri_DuranDruzhba.win_condition = "SKD_DomAnri_DuranDruzhba";
		break;
		
		case "SKD_DomAnri_DuranDruzhba_3":
			dialog.text = "È fatta, Capitano. Devo ammettere che m’ha colto di sorpresa...";
			link.l1 = "Non voglio sentirne parlare. Ho mantenuto la mia parola. Ora tocca a te.";
			link.l1.go = "SKD_DomAnri_DuranDruzhba_4";
		break;
		
		case "SKD_DomAnri_DuranDruzhba_4":
			dialog.text = "L’oro è una cosa, ma rischiare la pelle per un semplice mercenario vale assai di più. Io resto al tuo fianco fino alla fine, Capitano.";
			link.l1 = "In tal caso, qui abbiamo finito.";
			link.l1.go = "SKD_DomAnri_DuranDruzhba_5";
		break;
		
		case "SKD_DomAnri_DuranDruzhba_5":
			dialog.text = "Ai vostri ordini.";
			link.l1 = "...";
			link.l1.go = "SKD_DomAnri_DuranDruzhba_6";
		break;
		
		case "SKD_DomAnri_DuranDruzhba_6":
			DialogExit();
			
			EndQuestMovie();
			locCameraTarget(PChar);
			locCameraFollow();
			LAi_LocationDisableOfficersGen("PortRoyal_town", false);
			chrDisableReloadToLocation = false;
			AddQuestRecord("TheFormerKnight", "3");
			CloseQuestHeader("TheFormerKnight");
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			
			sld = CharacterFromID("Duran");	//Клод Дюран становится постоянным офицером
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			LAi_SetOfficerType(sld);
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.Dialog.CurrentNode = "hired";
			sld.OfficerImmortal = true;
			sld.Health.HP       = 60.0;
			sld.Health.maxHP    = 60.0;
			SetCharacterPerk(sld, "ShipEscape");
			
			pchar.questTemp.SKD_DuranDruzhba = true;
			pchar.questTemp.SKD_DevushkaUbita = true;
			sld.reputation = sti(sld.reputation) - 15;
			OfficersFollow();
		break;
		
		case "SKD_DomAnri_VD":
			dialog.text = "L'ho fatto. E allora, Capitano?";
			link.l1 = "Dimostrami che quelle parole non erano solo fiato sprecato. Vuoi guadagnarti un posto nella mia ciurma? Una fetta del bottino a venire? Segui i miei ordini. Non toccare la ragazza. Perché? Perché altrimenti resterai sempre un macellaio, e per gente così non c’è posto accanto a me.";
			link.l1.go = "SKD_DomAnri_VD_2";
		break;
		
		case "SKD_DomAnri_VD_2":
			dialog.text = "È la seconda volta che tu ed io stiamo per scannarci, Capitano.\nE ancora una volta vinci solo perché sai menare la lingua! Ah ah! L’hai detto tu! Che si fottesse quella ragazza. In fondo sono una bestia, io. Mi dai il permesso d’imbarcarmi con la ciurma?";
			link.l1 = "Ben arrivato, Claude. Stavolta sul serio.";
			link.l1.go = "SKD_DomAnri_VD_3";
		break;
		
		case "SKD_DomAnri_VD_3":
			dialog.text = "Ai vostri ordini, Capitano!";
			link.l1 = "...";
			link.l1.go = "SKD_DomAnri_VD_4";
		break;
		
		case "SKD_DomAnri_VD_4":
			DialogExit();
			AddQuestRecord("TheFormerKnight", "2");
			CloseQuestHeader("TheFormerKnight");
			chrDisableReloadToLocation = false;
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			
			sld = CharacterFromID("Duran");	//Клод Дюран становится постоянным офицером
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			LAi_SetOfficerType(sld);
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.Dialog.CurrentNode = "hired";
			sld.OfficerImmortal = true;
			sld.Health.HP       = 60.0;
			sld.Health.maxHP    = 60.0;
			SetCharacterPerk(sld, "ShipEscape");
			
			pchar.questTemp.SKD_DuranDruzhba = true;
			sld.reputation = 60;
			OfficersFollow();
		break;
		
		case "SKD_KlodDuran":
			dialog.text = "È saltato fuori un imprevisto, Capitano.";
			Link.l1 = "Fammi indovinare: minaccerai di mollare tutto e chiederai ancora un aumento?";
			Link.l1.go = "SKD_KlodDuran_1";
		break;
		
		case "SKD_KlodDuran_1":
			dialog.text = "Ehi! Stavolta no... Non temere, Capitano, finché il soldo scivola nella mia mano, sono tuo... nei limiti del buon senso, s'intende. È così che noi fratelli di ventura restiamo a galla. E perfino i migliori tra noi vengono pagati quattro soldi.";
			link.l1 = "Perché non andiamo subito al sodo?";
			link.l1.go = "SKD_KlodDuran_2";
		break;
		
		case "SKD_KlodDuran_2":
			dialog.text = "Ti ricordi quella sgualdrina di Tortuga?";
			link.l1 = "Marceline? La moglie del governatore? Una donna così non si scorda mai.";
			link.l1.go = "SKD_KlodDuran_3";
		break;
		
		case "SKD_KlodDuran_3":
			dialog.text = "Non sono capitato per caso a casa di Levasseur. Avevo affari in sospeso con quel furfante e miscredente.";
			link.l1 = "È curioso sentirti parlare così sprezzantemente dei potenti, Claude.";
			link.l1.go = "SKD_KlodDuran_4";
		break;
		
		case "SKD_KlodDuran_4":
			dialog.text = "Eh? Eh! Levasseur è il diavolo in persona! È peggio persino dei filibustieri che gli leccano i piedi!";
			link.l1 = "Tu stesso hai detto di averci fatto affari. Non è un tantino ipocrita, capitano?";
			link.l1.go = "SKD_KlodDuran_5";
		break;
		
		case "SKD_KlodDuran_5":
			dialog.text = "Non sono certo un santo, Capitano, e campo ammazzando chi mi viene ordinato. È per questo che mi tieni così caro, vero? Ma persino uno come me si gela il sangue a sentir certe voci su ciò che combinano alle donne a Tortuga nei covi di Levasseur!";
			link.l1 = "Le chiacchiere non mi interessano. Quest’uomo è un nobile e servitore del Re, e merita rispetto.";
			link.l1.go = "SKD_KlodDuran_6";
		break;
		
		case "SKD_KlodDuran_6":
			dialog.text = "Dunque, hai derubato il servitore del Re e ti sei portato a letto sua moglie? Eh! Fai come ti pare, Capitano. Andiamo al sodo. Sua Eccellenza mi ha ordinato di rintracciare e far fuori un uomo. Un lavoro piuttosto ordinario, anche se non capita spesso che arrivi da uno così in alto, e addirittura di persona.";
			link.l1 = "E che cosa vuoi? Che ti lasci libero così puoi mantenere la parola e far fuori quest’uomo?";
			link.l1.go = "SKD_KlodDuran_7";
		break;
		
		case "SKD_KlodDuran_7":
			dialog.text = "Voglio che tu mi dia una mano, Capo. Quando la situazione si è messa male per me a Tortuga, ho accettato di arruolarmi sotto il tuo comando, ma non avrò pace finché non chiuderò questa faccenda. Levasseur mi farebbe la pelle se lo scoprisse. E poi, lasciare il lavoro a metà non è roba da veri professionisti.";
			link.l1 = "È professionale impicciarsi con la moglie di un cliente? Strana richiesta la tua, davvero, specie dopo come hai definito il nostro rapporto all’inizio: sangue per oro, eh?";
			link.l1.go = "SKD_KlodDuran_8";
		break;
		
		case "SKD_KlodDuran_8":
			dialog.text = "Se mi aiuti, non avrai solo la mia spada, ma anche la mia lealtà. Vedo subito che sei destinato a solcare mari importanti, Capitano. Mi farebbe piacere aiutarti a realizzarlo.";
			link.l1 = "Lo ammetto, preferisco avere un uomo delle tue capacità a guardarmi le spalle. Dove possiamo trovare questo bersaglio che ti dà noia?";
			link.l1.go = "SKD_KlodDuran_10";
			link.l2 = "La tua sciabola basterà per ora. Non sono mica un assassino. Rilassati, ufficiale!";
			link.l2.go = "SKD_KlodDuran_9";
		break;
		
		case "SKD_KlodDuran_9":
			dialog.text = "Aye, aye, Capitano. Non si sa mai, tentar non nuoce.";
			link.l1 = "...";
			link.l1.go = "SKD_KlodDuran_9_1";
		break;
		
		case "SKD_KlodDuran_9_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			npchar.loyality = makeint(npchar.loyality) + 10;
			Return_DurandOfficer();
		break;
		
		case "SKD_KlodDuran_10":
			dialog.text = "Eheh! Ecco il guaio, Capitano. Tutto quel che so è che si tratta d’un ex-cavaliere dell’Ordine di Malta, in fuga da qualche parte nei territori inglesi. Uno di sangue nobile, non starà certo a marcire in una catapecchia.";
			link.l1 = "Cavaliere dell'Ordine?";
			link.l1.go = "SKD_KlodDuran_11";
		break;
		
		case "SKD_KlodDuran_11":
			dialog.text = "Un ex cavaliere. Eh già, e mi sono già pentito mille volte di aver accettato questo incarico. I cavalieri combattono come demoni, quindi ti garantisco che metterai davvero alla prova la tua abilità con la spada.";
			link.l1 = "Non mi garba, ma proviamoci. Allora: non un poveraccio, un nobiluomo e si nasconde dagli inglesi? Levasseur non ha detto perché dobbiamo occuparcene?";
			link.l1.go = "SKD_KlodDuran_12";
		break;
		
		case "SKD_KlodDuran_12":
			dialog.text = "Ma certo che no! Ma è una faccenda politica, altrimenti avrebbe già mandato i suoi soldati.";
			link.l1 = "Ci proverò, ma non posso promettere nulla.";
			link.l1.go = "SKD_KlodDuran_13";
		break;
		
		case "SKD_KlodDuran_13":
			dialog.text = "Grazie, Capo.";
			link.l1 = "...";
			link.l1.go = "SKD_KlodDuran_14";
		break;
		
		case "SKD_KlodDuran_14":
			DialogExit();
			SetQuestHeader("TheFormerKnight");
			AddQuestRecord("TheFormerKnight", "1");
			chrDisableReloadToLocation = false;
			npchar.loyality = makeint(npchar.loyality) + 15;
			Return_DurandOfficer();
			PChar.quest.SKD_DomAnri.win_condition.l1 = "location";
			PChar.quest.SKD_DomAnri.win_condition.l1.location = "PortRoyal_houseSp1";
			PChar.quest.SKD_DomAnri.win_condition = "SKD_DomAnri";
			pchar.GenQuestBox.PortRoyal_houseSp1.box1.items.chest = 1;
		break;
		
	}
} 

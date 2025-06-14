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
			dialog.text = "Cosa volete?";
			link.l1 = "Niente.";
			link.l1.go = "exit";
		break;
		
		// Квест "Длинные тени старых грехов"
		case "DTSG_Knippel_1":
			dialog.text = "Oh, che canicola oggi. Tanto vale legarsi una palla a catena alla gamba e tuffarsi in mare, giusto per liberarsi di questo soffocamento!";
			link.l1 = "Ah-ah, Charlie!.. Queste sì che sono misure estreme, se vuoi il mio parere. Ma non mi dispiacerebbe inumidire la gola – oggi fa davvero un caldo dannato. Ci stai?";
			link.l1.go = "DTSG_Knippel_2";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_Knippel_2":
			dialog.text = "Bere un bicchiere o due con voi, Capitano? Sempre pronto!";
			link.l1 = "Ecco ciò che mi piace sentire. Avanti, muoviamoci!";
			link.l1.go = "DTSG_Knippel_3";
		break;
		
		case "DTSG_Knippel_3":
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "", "", "", "DTSG_BasTerTavern", -1);
			FreeSitLocator("BasTer_tavern", "sit_base2");
			FreeSitLocator("BasTer_tavern", "sit_front2");
		break;
		
		case "DTSG_Ohotnik_1":
			dialog.text = "Ehi, marinaio, hai proprio l’aria di chi ne ha viste di tutti i colori! Che ne dici di bere qualcosa insieme e raccontarci qualche storia? Offro io!";
			link.l1 = "...";
			link.l1.go = "DTSG_Ohotnik_1_Animation";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("Knippel"));
			
		break;
		
		case "DTSG_Ohotnik_1_Animation":
			StartInstantDialogNoType("Knippel", "DTSG_Ohotnik_2", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_Ohotnik_2":
			dialog.text = "Uh, no, grazie, compare. Son venuto qui col mio Capitano. Cercati qualcun altro.";
			link.l1 = "...";
			link.l1.go = "DTSG_Ohotnik_2_Animation";
			LAi_tmpl_SetDialog(npchar, pchar, -1.0);
			locCameraFromToPos(5.57, 2.39, -4.63, true, 8.53, 2.07, 1.84);
		break;
		
		case "DTSG_Ohotnik_2_Animation":
			StartInstantDialog("DTSG_Ohotnik", "DTSG_Ohotnik_3", "Quest\CompanionQuests\Knippel.c");
			locCameraSleep(true);
		break;
		
		case "DTSG_Ohotnik_3":
			dialog.text = "Ah, un cencioso come te si crede tanto in alto da bere solo coi capitani?";
			link.l1 = "...";
			link.l1.go = "DTSG_Ohotnik_3_Animation";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("Knippel"));
		break;
		
		case "DTSG_Ohotnik_3_Animation":
			StartInstantDialogNoType("Knippel", "DTSG_Ohotnik_4", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_Ohotnik_4":
			dialog.text = "Grandi opinioni?! Ho servito per decenni nella Reale Marina! E non ho combattuto per i lord, ma per la gente comune come te e me, per portare legge e ordine dappertutto!..";
			link.l1 = "...";
			link.l1.go = "DTSG_Ohotnik_4_Animation";
			LAi_tmpl_SetDialog(npchar, pchar, -1.0);
		break;
		
		case "DTSG_Ohotnik_4_Animation":
			StartInstantDialog("DTSG_Ohotnik", "DTSG_Ohotnik_5", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_Ohotnik_5":
			dialog.text = "Parli grosso, ma bevi solo coi capitani e coi nobili! Pare proprio che la Marina t’abbia insegnato solo a lucidare i cannoni, eh!";
			link.l1 = "...";
			link.l1.go = "DTSG_Ohotnik_5_Animation";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("Knippel"));
		break;
		
		case "DTSG_Ohotnik_5_Animation":
			StartInstantDialogNoType("Knippel", "DTSG_Ohotnik_6", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_Ohotnik_6":
			dialog.text = "Ti ficco una palla incatenata in gola, cucciolo!";
			link.l1 = "Charlie, non perdere la testa così, non ne vale la pena.";
			link.l1.go = "DTSG_Ohotnik_7";
			LAi_tmpl_SetDialog(npchar, pchar, -1.0);
		break;
		
		case "DTSG_Ohotnik_7":
			dialog.text = "Lascia fare a me, Capitano. L’onore della Marina è in gioco, devo difenderlo io stesso e non celarmi dietro nessuno...";
			link.l1 = "...";
			link.l1.go = "DTSG_Ohotnik_8";
		break;
		
		case "DTSG_Ohotnik_8":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_FadeLong("DTSG_BasTerTavern_7", "");
		break;
		
		case "DTSG_Knippel_l0":
			dialog.text = "Grazie per aver atteso, Capitano. Spero di non avervi fatto aspettare troppo.";
			link.l1 = "Non ci pensare. Non ti sei fatto male? Quel furfante era davvero in gamba.";
			link.l1.go = "DTSG_Knippel_l1";
		break;
		
		case "DTSG_Knippel_l1":
			dialog.text = "Non ti crucciare, Capitano. Quel che conta è che ha avuto ciò che si meritava. Ho raccolto una specie di chiave dal suo cadavere...";
			link.l1 = "...";
			link.l1.go = "DTSG_Knippel_l2";
		break;
		
		case "DTSG_Knippel_l2":
			dialog.text = "Ho raccolto una specie di chiave dal suo cadavere... Mi chiedo a cosa possa servire?";
			link.l1 = "Elementare, Charlie... Per una porta o uno scrigno, ah-ah. Dovremmo parlarne con l’oste riguardo a questo furfante, potrebbe tornarci utile.";
			link.l1.go = "DTSG_Knippel_l3";
			AddItems(pchar, "Key1", 1);
			Log_info("Charlie gave you the key.");
			PlaySound("interface\important_item.wav");
		break;
		
		case "DTSG_Knippel_l3":
			DialogExit();
			
			bDisableCharacterMenu = false;
			InterfaceStates.Buttons.Save.enable = true;
			sld = CharacterFromID("Knippel");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			sld.location = "None";
			pchar.questTemp.DTSG_BasTerTavern = true;
			AddLandQuestMark(characterFromId("BasTer_tavernkeeper"), "questmarkmain");
		break;
		
		case "DTSG_Knippel_20":
			dialog.text = "Incredibile...";
			link.l1 = "Hai in mente quello che penso anch’io, Charlie?";
			link.l1.go = "DTSG_Knippel_21";
		break;
		
		case "DTSG_Knippel_21":
			dialog.text = "Non so voi, signore, ma mi sorprende vedere quanta moneta c’è qui – sembrava un uomo qualunque, mica un mercante o un nobile.";
			link.l1 = "Non è poi così tanto, davvero, ma hai ragione. Quello che mi sorprende è questa strana lettera bruciacchiata.";
			link.l1.go = "DTSG_Knippel_22";
		break;
		
		case "DTSG_Knippel_22":
			dialog.text = "Già, non è stato per nulla furbo da parte sua – è come sparare palle incatenate contro una carena robusta. Avrebbe dovuto distruggere la lettera senza lasciare traccia.";
			link.l1 = "Vero. Ma non ci serve a nulla – non sappiamo chi fosse né con chi si scambiasse lettere. Andiamo, Charlie, qui non abbiamo altro da cercare.";
			link.l1.go = "DTSG_Knippel_23";
		break;
		
		case "DTSG_Knippel_23":			//КОНЕЦ ЭТАПА 1
			DialogExit();
			Return_KnippelOfficer();

			AddQuestRecord("DTSG", "2");
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			pchar.questTemp.DTSG_Nastoroje1 = true;
		break;
		
		case "DTSG_Ohotnik_10":
			dialog.text = "Ecco la tanto decantata Marina Reale, bah!";
			link.l1 = "Charlie era un brav’uomo, per Dio. E non era un fante, ma un artigliere di bordo.";
			link.l1.go = "DTSG_Ohotnik_11";
		break;
		
		case "DTSG_Ohotnik_11":
			dialog.text = "Un cannoniere?! Ah, dunque avevo ragione io, ah-ah-ah! E non mi guardare storto – dovevi sapere bene chi imbarcavi nella tua ciurma.";
			link.l1 = "Avresti dovuto sapere con chi ti mettevi nei guai.";
			link.l1.go = "DTSG_Ohotnik_Agressia_1";
			link.l2 = "Sei ancora vivo solo perché hai vinto onestamente, quindi tieni a freno quella lurida lingua e sparisci di qui.";
			link.l2.go = "DTSG_Ohotnik_Otpustil_1";
		break;
		
		case "DTSG_Ohotnik_Otpustil_1":
			dialog.text = "Ebbene, pensavo che toccasse a me duellare con te dopo. Fa piacere sentire che l'onore conta ancora qualcosa per te.";
			link.l1 = "Non erano solo parole vuote per Charlie, sai. Ma quanto a te, ho i miei dubbi. Comunque, ormai non conta più nulla.";
			link.l1.go = "DTSG_Ohotnik_Otpustil_2";
		break;
		
		case "DTSG_Ohotnik_Otpustil_2":			//ПРОВАЛ ЭТАПА 1
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			npchar.lifeday = 0;
			LAi_LocationDisableOfficersGen("BasTer_tavern", false);
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			bDisableCharacterMenu = false;
			InterfaceStates.Buttons.Save.enable = true;
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterComplexReputation(pchar, "authority", -3);
			ChangeCharacterComplexReputation(pchar, "fame", -3);	
		break;
		
		case "DTSG_Ohotnik_Agressia_1":
			dialog.text = "E con chi avrei avuto a che fare, con uno smidollato viziato?! Hai mai visto quei baffetti da ragazzino che ti ritrovi?..";
			link.l1 = "Sai proprio come far saltare la mosca al naso... Sarà ancora più godurioso sfogare la mia rabbia su di te.";
			link.l1.go = "DTSG_Ohotnik_Agressia_2";
		break;
		
		case "DTSG_Ohotnik_Agressia_2":
			DialogExit();
			
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			sld = CharacterFromID("DTSG_Ohotnik");
			DeleteAttribute(sld, "CantLoot");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_Ohotnik_Agressia_3");
			LAi_SetFightMode(pchar, true);
		break;
		
		case "DTSG_PiterAdams_1":
			dialog.text = "Aspetta, Capitano. Vedo che siete uomo degno e nobile, potreste aiutarmi in una faccenda? È questione d’onore.";
			link.l1 = "Forse posso, ma di che si tratta? E perché sei venuto proprio da me? Ci sono tanti gentiluomini da queste parti. A proposito, con chi ho l’onore di parlare?";
			link.l1.go = "DTSG_PiterAdams_2";
			InterfaceStates.Buttons.Save.enable = true;
		break;
		
		case "DTSG_PiterAdams_2":
			dialog.text = "Peter. Peter Adams. Vedo che non sei uno di quei rampolli viziati delle vecchie famiglie, ma un uomo affidabile dalla mano ferma.";
			link.l1 = "Oh, avreste dovuto vedermi quando sono sbarcato nei Caraibi, signore. Ma avanti, ditemi pure, di che avete bisogno?";
			link.l1.go = "DTSG_PiterAdams_3";
		break;
		
		case "DTSG_PiterAdams_3":
			dialog.text = "Potresti... battersi in duello per me, signore? Un mascalzone del posto, Ralph Faggle, ha insultato mia moglie. E l'ha importunata, davanti a tutti. Proprio sotto i miei occhi. Puoi crederci?";
			link.l1 = "Non c'è molto onore nel sfidare a duello e poi nascondersi dietro le spalle di qualcun altro. Soprattutto quando in gioco non è solo il tuo onore, ma quello di una donna — tua moglie, per giunta. Non la pensi così, Adams? Perché non combatti per la tua donna con le tue stesse mani?";
			link.l1.go = "DTSG_PiterAdams_4";
		break;
		
		case "DTSG_PiterAdams_4":
			dialog.text = "E hai ragione, assolutamente ragione. Ma di recente sono stato colpito da una febbre tremenda, e riesco a malapena a reggermi in piedi\nLo ammetto, non mi è facile chiederti una cosa del genere. Se avesse insultato me, l’avrei sopportato. Ma non quando è in gioco l’onore di mia moglie! Non sono un codardo, signore. Ho servito una volta nella Marina Reale e ho navigato sulla stessa nave di Robert Blake in persona!";
			link.l1 = "Io...";
			link.l1.go = "DTSG_PiterAdams_5";
		break;
		
		case "DTSG_PiterAdams_5":
			StartInstantDialog("Knippel", "DTSG_PiterAdams_6", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_PiterAdams_6":
			dialog.text = "Ti daremo una mano.";
			link.l1 = "Charlie?..";
			link.l1.go = "DTSG_PiterAdams_7";
			CharacterTurnByChr(npchar, characterFromId("DTSG_PiterAdams"))
		break;
		
		case "DTSG_PiterAdams_7":
			dialog.text = "È un uomo degno, Capitano. E che io sia maledetto in eterno dai colpi di cannone, se non è vero! Gente d’onore ha servito con l’Ammiraglio Blake. Hanno combattuto insieme affinché nessuno opprimesse la povera gente.\nE grazie a lui, la Giamaica fu liberata dalla tirannia degli spagnoli!";
			link.l1 = "Anche fosse così, non permetterò mai ai miei uomini d’interrompermi o prendere decisioni al posto mio. È chiaro?";
			link.l1.go = "DTSG_PiterAdams_8";
			link.l2 = "Capisco, davvero. Però non ho nemmeno avuto il tempo di rispondere. Cerca di non essere così precipitoso e non interrompermi la prossima volta, intesi?";
			link.l2.go = "DTSG_PiterAdams_8";
			CharacterTurnByChr(npchar, pchar)
		break;
		
		case "DTSG_PiterAdams_8":
			dialog.text = "Ascoltami bene, Capitano – se non presti aiuto a quest’uomo, il vecchio Charlie mollerà tutto e sfiderà chiunque per lui, che possa l’inferno prendersi la mia anima qui e ora!";
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje1"))
			{
				link.l1 = "Calmati ora, non ho detto che mi rifiuto di aiutare. Dico bene, signor Adams?";
				link.l1.go = "DTSG_PiterAdams_Nastoroje_1";
			}
			else
			{
				link.l1 = "Onestamente, Charlie, mi fai sembrare un codardo. E io non lo sono mai stato. Dovresti saperlo.";
				link.l1.go = "DTSG_PiterAdams_NN_1";
			}
		break;
		
		case "DTSG_PiterAdams_NN_1":
			dialog.text = "Ah, scusami, Capitano, mi sono lasciato prendere la mano.";
			link.l1 = "Va bene. Ma tieni la testa a posto, intesi?";
			link.l1.go = "DTSG_PiterAdams_NN_1_1";
		break;
		
		case "DTSG_PiterAdams_NN_1_1":
			StartInstantDialog("DTSG_PiterAdams", "DTSG_PiterAdams_NN_2", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_PiterAdams_NN_2":
			dialog.text = "";
			link.l1 = "Sfiderò chiunque per voi, signor Adams.";
			link.l1.go = "DTSG_PiterAdams_NN_3";
		break;
		
		case "DTSG_PiterAdams_NN_3":
			dialog.text = "Grazie, signore! Che il Signore vi benedica!";
			link.l1 = "E che il Signore Protettore vegli su di noi, giusto, signor Adams? Non temere, Charles de Maure non abbandona mai un uomo onesto nei guai.";
			link.l1.go = "DTSG_PiterAdams_NN_4";
		break;
		
		case "DTSG_PiterAdams_NN_4":
			dialog.text = "Te ne siamo riconoscenti, signor de Maure, sir! Ti andrebbe di venire a cena con me e Jane?";
			link.l1 = "Ebbene, io...";
			link.l1.go = "DTSG_PiterAdams_NN_5";
		break;
		
		case "DTSG_PiterAdams_NN_5":
			dialog.text = "Insisto!";
			link.l1 = "Ebbene, solo se insisti. Grazie, Peter. Guidami tu.";
			link.l1.go = "DTSG_PiterAdams_IdemKDomu";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_1":
			StartInstantDialog("DTSG_PiterAdams", "DTSG_PiterAdams_Nastoroje_2", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_PiterAdams_Nastoroje_2":
			dialog.text = "Certo che è vero, signore! Vuole forse unirsi a Jane e riposare un po’ dopo il viaggio?";
			link.l1 = "Grazie, ma è giusto approfittare della vostra ospitalità?";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_3";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_3":
			dialog.text = "Oh, al contrario, Capitano, ci offenderemmo se non veniste a bordo.";
			link.l1 = "Come potevo rifiutare allora? Dopo di te, Peter!";
			link.l1.go = "DTSG_PiterAdams_IdemKDomu";
		break;
		
		case "DTSG_PiterAdams_IdemKDomu":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "reload", "houseF1", "DTSG_PiterAdams_VDom", -1);
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, npchar, "", -1);
			sld = CharacterFromID("Knippel");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
		break;
		
		case "DTSG_PiterAdamsRyadomSDomom_1":
			dialog.text = "Siamo noi! Prego, entra.";
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje1"))
			{
				link.l1 = "Grazie. Posso parlare con Jane? Chiedile come è successo – ho bisogno di ogni dettaglio.";
				link.l1.go = "DTSG_PiterAdamsRyadomSDomom_2";
			}
			link.l2 = "Ti chiedo sinceramente scusa, ma ripensandoci devo rifiutare. Ho un duello da preparare, avanti. A proposito, dove e quando si terrà questa faccenda?";
			link.l2.go = "DTSG_PiterAdamsRyadomSDomom_4";
		break;
		
		case "DTSG_PiterAdamsRyadomSDomom_2":
			dialog.text = "Ebbene, certo, signore. Saremo ben lieti di parlare con voi e rispondere a tutte le vostre domande. Seguitemi, prego.";
			link.l1 = "Grazie, Peter.";
			link.l1.go = "DTSG_PiterAdamsRyadomSDomom_3";
		break;
		
		case "DTSG_PiterAdamsRyadomSDomom_3":
			DoQuestReloadToLocation("PortPax_houseF1", "reload", "reload1", "DTSG_PiterAdams_VDom_2");
		break;
		
		case "DTSG_PiterAdamsRyadomSDomom_4":
			dialog.text = "Che peccato! Ma hai ragione, bisogna prepararsi per bene, certo. Due ore. Proprio fuori dalle porte della città.";
			link.l1 = "Capito, grazie. Verrò volentieri non appena sarà tutto finito. Ci vediamo allora!";
			link.l1.go = "DTSG_PiterAdamsRyadomSDomom_5";
		break;
		
		case "DTSG_PiterAdamsRyadomSDomom_5":
			DialogExit();
			bDisableFastReload = false;
			chrDisableReloadToLocation = false; 
			
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "", "", "", "", -1);
			npchar.location = "None";
			
			sld = CharacterFromID("Knippel");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			LAi_SetOfficerType(sld);
			sld.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			sld.Dialog.CurrentNode = "Knippel_officer";
			sld.location = "None";
			
			PChar.quest.DTSG_PoP_DuelTime.win_condition.l1 = "Timer";
			PChar.quest.DTSG_PoP_DuelTime.win_condition.l1.date.hour = sti(GetTime() + 2);
			PChar.quest.DTSG_PoP_DuelTime.win_condition.l1.date.day = GetAddingDataDay(0, 0, 0);
			PChar.quest.DTSG_PoP_DuelTime.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			PChar.quest.DTSG_PoP_DuelTime.win_condition.l1.date.year = GetAddingDataYear(0, 0, 0);
			PChar.quest.DTSG_PoP_DuelTime.win_condition = "DTSG_PoP_DuelTime";
			
			PChar.quest.DTSG_PoP_Duel.win_condition.l1 = "location";
			PChar.quest.DTSG_PoP_Duel.win_condition.l1.location = "PortPax_ExitTown";
			PChar.quest.DTSG_PoP_Duel.win_condition = "DTSG_PoP_Duel";
			
			AddQuestRecord("DTSG", "3");
		break;
		
		case "DTSG_JeinAdams_1":
			dialog.text = "Benvenuto! Diavolo, non mi avevi detto che portavi compagnia – avrei fatto le cose per bene.";
			link.l1 = "Grazie, signora, non ci vorrà molto. Charles de Maure, al vostro servizio. Ho acconsentito ad ascoltare la vostra storia insieme a vostro marito. Raccontatemi come andarono i fatti.";
			link.l1.go = "DTSG_JeinAdams_2";
		break;
		
		case "DTSG_JeinAdams_2":
			dialog.text = "Oh, è stato un vero orrore! Ralph era fradicio di rum, completamente perso. Ha cominciato a tormentarmi davanti ai vicini, persino davanti a Peter, sputando oscenità da marinaio...";
			link.l1 = "E che cosa t'ha detto, di preciso?";
			link.l1.go = "DTSG_JeinAdams_3";
		break;
		
		case "DTSG_JeinAdams_3":
			dialog.text = "Mi vergogno troppo per parlarne. Poi si è ripreso, e...";
			link.l1 = "Ti sei scusato e hai chiesto di annullare il duello, forse?";
			link.l1.go = "DTSG_JeinAdams_4";
		break;
		
		case "DTSG_JeinAdams_4":
			dialog.text = "Neanche una volta.";
			link.l1 = "Mi dispiace per voi. Vorrei sapere ancora una cosa, se me lo permettete, signora.";
			link.l1.go = "DTSG_JeinAdams_5";
		break;
		
		case "DTSG_JeinAdams_5":
			dialog.text = "E che sarebbe, signore?";
			link.l1 = "Quali sventure e traversie vi hanno mai spinti a rifugiarvi in questo scoglio? In qualunque città d’Inghilterra, coi meriti di vostro marito, avreste già rimesso Ralph al suo posto.";
			link.l1.go = "DTSG_JeinAdams_6";
		break;
		
		case "DTSG_JeinAdams_6":
			StartInstantDialog("Knippel", "DTSG_JeinAdams_7", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_JeinAdams_7":
			dialog.text = "Chiedo venia, signore, ma come osate?! Se non foste il mio capitano, prenderei una palla a catena e vi darei una bella lezione!\nNon solo diffidate di un uomo degno come il signor Adams, ma vi permettete pure di schernire una dama in difficoltà...";
			link.l1 = "Hai sentito che ho preso in giro una dama? No? Allora non infangarmi. La nostra gente poteva aiutarli, ecco perché ho chiesto.";
			link.l1.go = "DTSG_JeinAdams_8a";
			link.l1 = "Calmati, Charlie! Come puoi pensare che... Volevo solo sapere di più sulle disgrazie di Jane e Peter e mostrare un po’ di compassione. Nelle colonie inglesi, ormai avrebbero già ricevuto aiuto.";
			link.l1.go = "DTSG_JeinAdams_8b";
		break;
		
		case "DTSG_JeinAdams_8a":
			dialog.text = "La vita può girare in mille modi... Un naufragio, o la maldicenza di qualcuno che costringe persino un uomo onesto a nascondersi nella vergogna.\nSe sei così diffidente e sospettoso – parla pure coi vicini. Son certo che ti confermeranno ogni mia parola. Ma il vecchio Charlie non si abbasserebbe mai a spettegolare sul dolore altrui alle spalle!";
			link.l1 = "Non mi hai sentito? Ho detto che avrei aiutato questa gente.";
			link.l1.go = "DTSG_JeinAdams_9";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
		break;
		
		case "DTSG_JeinAdams_8b":
			dialog.text = "La vita può voltarsi in mille modi... Un naufragio, o la calunnia di qualcuno, che può costringere anche l’uomo più onesto a nascondersi nella vergogna.\nSe siete tanto diffidenti e sospettosi – parlate coi vicini. Son certo che confermeranno ogni mia parola. Ma il vecchio Charlie non si abbasserebbe mai a sparlare del dolore altrui alle spalle!";
			link.l1 = "Non mi hai sentito? Ho detto che avrei aiutato questa gente.";
			link.l1.go = "DTSG_JeinAdams_9";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterComplexReputation(pchar, "authority", -2);
		break;
		
		case "DTSG_JeinAdams_9":
			StartInstantDialog("DTSG_PiterAdams", "DTSG_JeinAdams_10", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_JeinAdams_10":
			dialog.text = "Vi ringraziamo dal profondo del cuore. Pregheremo per voi, che il Signore ve ne renda merito.";
			link.l1 = "Bene.  A proposito, riguardo la nostra faccenda... Dove e quando hai fissato il duello, signor Adams?";
			link.l1.go = "DTSG_JeinAdams_11";
		break;
		
		case "DTSG_JeinAdams_11":
			dialog.text = "Fuori dalle porte della città, signore. Fra due ore.";
			link.l1 = "Ce la farò. Aspettami con buone nuove. E non ti azzardare a pregare per la mia anima prima del tempo!";
			link.l1.go = "DTSG_JeinAdams_13";
		break;
		
		case "DTSG_JeinAdams_13":
			DoQuestReloadToLocation("PortPax_town", "reload", "houseF1", "DTSG_PiterAdams_IsDoma");
		break;
		
		case "DTSG_Knippel_30":
			dialog.text = "C’è qualcosa che vi turba, Capitano? Vi vedo pensieroso.";
			link.l1 = "Sai, sì. C'è qualcosa nella storia di Adams che non quadra, e...";
			link.l1.go = "DTSG_Knippel_31";
		break;
		
		case "DTSG_Knippel_31":
			dialog.text = "Per quanto tempo dovrà durare tutto questo, signore?! Vi scaldate così ogni volta che qualcuno chiede aiuto?";
			link.l1 = "Per l’amor di Dio, parla piano. Vorresti che tutta la strada lo sentisse? Ho già detto che andrò al duello. Non ti basta, questo? Ora dammi retta, e ascolta bene.";
			link.l1.go = "DTSG_Knippel_32";
		break;
		
		case "DTSG_Knippel_32":
			dialog.text = "Hmm, va bene, Capitano. Scusate lo sfogo – mi sta a cuore il destino di chi ha servito nella Royal Navy. Molti di noi erano brava gente, meritavano ben altra sorte di quella che hanno avuto.";
			link.l1 = "Ti capisco, Charlie. Ora rammenta quel che va fatto. Voglio che mandi una parte dell’equipaggio alle porte della città. Quando si avvicina l’ora del duello, che si raccolgano in silenzio e stiano pronti al mio segnale.";
			link.l1.go = "DTSG_Knippel_33";
		break;
		
		case "DTSG_Knippel_33":
			dialog.text = "Intendi trasformare un duello onesto in un assassinio?";
			link.l1 = "Sospetto che non sarà del tutto onesto. Darò segnale solo se ce ne sarà davvero bisogno. Se davvero andrà tutto per il giusto, sarò lieto di sbagliarmi. Capisci adesso? Ricordi cosa è successo un mese fa?";
			link.l1.go = "DTSG_Knippel_34";
		break;
		
		case "DTSG_Knippel_34":
			dialog.text = "Capito, signore. A dirla tutta, non ne sono troppo contento, ma farò quel che va fatto. Non vi crucciate.";
			link.l1 = "Era proprio questo che volevo sentire.";
			link.l1.go = "DTSG_Knippel_35";
		break;
		
		case "DTSG_Knippel_35":
			DialogExit();
			
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "", "", "", "", -1);
			npchar.location = "None";
			AddDialogExitQuestFunction("DTSG_Knippel_36");
		break;
		
		case "DTSG_RalfFaggl":
			LAi_LocationDisableOfficersGen("PortPax_ExitTown", false);
			PChar.quest.DTSG_PoP_DuelTime.over = "yes";
			PChar.quest.DTSG_PoP_Duel.over = "yes";
			dialog.text = "Dunque, de Maure. Sei in anticipo. E siamo ancora in città. Non che cambi molto. Peccato tu non abbia portato con te quel vecchio rimbambito. Ma non ti crucciare, prima o poi metteremo le mani su di lui.";
			link.l1 = "Al vostro servizio, sempre. Siete mercenari, eh? Chi mai avrò fatto arrabbiare stavolta?";
			link.l1.go = "DTSG_RalfFaggl_2";
		break;
		
		case "DTSG_RalfFaggl_2":
			dialog.text = "Proprio così, nessuno. Cerchiamo quel vecchio bastardo, Charlie, e risaliremo a lui passando per te, visto che ci hanno detto che ora sta sulla tua nave. Non siamo nella giungla, quindi toccherà muoversi in fretta per non attirare troppa curiosità. Ma qui, almeno, non scapperai.";
			link.l1 = "Suppongo che tutto questo duello fosse una trappola, eh?";
			link.l1.go = "DTSG_RalfFaggl_3";
		break;
		
		case "DTSG_RalfFaggl_3":
			dialog.text = "Un po' tardi per capirlo, amico. Tanto ci saremmo azzuffati lo stesso – sono Ralph Faggle, al tuo servizio.";
			link.l1 = "In verità, l’avevo già intuito, così sono andato a scambiare due chiacchiere coi vicini. Dimmi, Adams c’entra anche lui in questa storia? E Jane? Non sarà mica... ";
			link.l1.go = "DTSG_RalfFaggl_4";
		break;
		
		case "DTSG_RalfFaggl_4":
			dialog.text = "La curiosità ha ammazzato il gatto, non lo sapevi? Dovevi presentarti al duello, non ficcare il naso dove non ti compete. Magari hai ancora una possibilità di uscirne vivo da tutto 'sto casino.\nCerto, provoca il vecchio marinaio e costringi il suo comandante a sfidarti a duello – un piano degno dei migliori filibustieri, eh Peter? E la cara Jane ha fatto la sua parte pure lei.";
			link.l1 = "Dimmi, chi voleva sbarazzarsi di Charlie?";
			link.l1.go = "DTSG_RalfFaggl_5";
		break;
		
		case "DTSG_RalfFaggl_5":
			dialog.text = "Ah, come se te lo dicessi? Preparati a difenderti.";
			link.l1 = "Peccato. Allora lo chiederò a Peter più tardi.";
			link.l1.go = "DTSG_RalfFaggl_6";
		break;
		
		case "DTSG_RalfFaggl_6":
			DialogExit();
			
			sld = CharacterFromID("DTSG_FrederikStouks");
			LAi_SetCheckMinHP(sld, 1, true, "DTSG_FrederikStouks_ranen");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			sld = CharacterFromID("DTSG_RalfFaggl");
			LAi_SetCheckMinHP(sld, 1, false, "DTSG_RalfFaggl_ubit");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_SetFightMode(pchar, true);
		break;
		
		case "DTSG_PiterAdams_11":
			dialog.text = "Oh, vedo che hai preso a cuore la mia storia e hai già punito Ralph, Capitano.";
			link.l1 = "Certo, visto che come hai detto sono un uomo degno e nobile. E adesso dovrò punirti per questa lurida trappola da traditore.";
			link.l1.go = "DTSG_PiterAdams_12";
			npchar.SaveItemsForDead = true;
			npchar.DontClearDead = true;
			GiveItem2Character(npchar, "letter_1");
			ChangeItemName("letter_1", "itmname_specialletter");
			ChangeItemDescribe("letter_1", "itmdescr_DTSG_letter2");
		break;
		
		case "DTSG_PiterAdams_12":
			dialog.text = "Se vuoi provare, Capitano, avanti pure – ma scommetto che sei già stremato e ferito.";
			link.l1 = "Allora facciamo una pausa. Nel frattempo, dimmi, per chi lavori?";
			link.l1.go = "DTSG_PiterAdams_13";
		break;
		
		case "DTSG_PiterAdams_13":
			dialog.text = "Scusa, ma il mio protettore non gradirebbe, anche se poi ti sistemassi per bene. Cosa che, tra l’altro, sta per succedere adesso.";
			link.l1 = "Maledizione!..";
			link.l1.go = "DTSG_PiterAdams_14";
		break;
		
		case "DTSG_PiterAdams_14":
			DialogExit();
			
			if (MOD_SKILL_ENEMY_RATE > 4)
			{
				sld = CharacterFromID("DTSG_FrederikStouks");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_SetHP(sld, GetCharacterBaseHPValue(sld)/2, GetCharacterBaseHPValue(sld));
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			else
			{
				sld = CharacterFromID("DTSG_FrederikStouks");
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
				LAi_KillCharacter(sld);
			}
			
			sld = CharacterFromID("Knippel");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			sld = CharacterFromID("DTSG_PiterAdams");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_Sosedi_Pobeda");
			LAi_SetFightMode(pchar, true);
		break;
		
		case "DTSG_Knippel_40":
			dialog.text = "Non posso credere che questi... questi furfanti non solo ci abbiano ingannati, ma abbiano anche mentito sulla Reale Marina! Come osano! Se non fossero già all’inferno, gli farei ingoiare un paio di palle incatenate per un tradimento simile!..";
			link.l1 = "La gente mente su ogni sorta di faccenda, Charlie. Pensavo che tu lo sapessi bene. Ma di certo sai chi li ha mandati. Non è la prima trappola che ti tendono, ultimamente. Avevano una lettera con la tua descrizione precisa. Dimmi, chi hai fatto arrabbiare così tanto?";
			link.l1.go = "DTSG_Knippel_41";
		break;
		
		case "DTSG_Knippel_41":
			dialog.text = "Be', io... Forse troveremo qualcos'altro nella casa degli Adams, signore?";
			link.l1 = "Schivi la domanda? Ma hai ragione, tanto volevo già perlustrarlo da cima a fondo. Andiamo.";
			link.l1.go = "DTSG_Knippel_42";
		break;
		
		case "DTSG_Knippel_42":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			npchar.location = "None";
			LAi_LocationDisableOfficersGen("PortPax_town", false);
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			PChar.quest.DTSG_PoP_ProverimSunduk.win_condition.l1 = "ExitFromLocation";
			PChar.quest.DTSG_PoP_ProverimSunduk.win_condition.l1.location = PChar.location;
			PChar.quest.DTSG_PoP_ProverimSunduk.win_condition = "DTSG_PoP_ProverimSunduk";
		break;
		
		case "DTSG_Knippel_50":
			dialog.text = "Santo cielo di cannonate, quanta roba d’oro!";
			link.l1 = "Peccato che qui non ci sia altro. Anche la 'Jane' è sparita nel nulla. Dici che sia ancora viva?";
			link.l1.go = "DTSG_Knippel_51";
		break;
		
		case "DTSG_Knippel_51":
			dialog.text = "Non saprei, signore, gentaglia simile è capace di qualsiasi infamia...";
			link.l1 = "È vero, ma mi pare che tu sappia più di quanto lasci intendere. Non è la prima volta che ti danno la caccia. E ogni volta troviamo un bel mucchio di monete addosso a loro.";
			link.l1.go = "DTSG_Knippel_52";
		break;
		
		case "DTSG_Knippel_52":
			dialog.text = "Non ne sono certo, Capitano, ma forse era un usuraio di St. John's.";
			link.l1 = "Come hai fatto ad inimicartelo?";
			link.l1.go = "DTSG_Knippel_53";
		break;
		
		case "DTSG_Knippel_53":
			dialog.text = "Ehm... tempo fa gli ho chiesto un prestito per saldare tutti gli altri miei debiti. Richard aveva giurato che avrebbe pagato lui, ma...";
			link.l1 = "Pensi che non l’abbia fatto?";
			link.l1.go = "DTSG_Knippel_54";
		break;
		
		case "DTSG_Knippel_54":
			dialog.text = "Non l’avrei mai creduto prima, ma dopo quello che ti ha fatto e se n’è filato via dai Caraibi con Abi... Forse si è scordato del debito. O magari no, ma se n’è andato lo stesso... Richard si è comportato proprio da bastardo, signore. Non mi stupirei se fosse di nuovo così, ma mi deluderebbe lo stesso.";
			link.l1 = "Non essere così categorico prima del tempo, Charlie. Dunque, St. John's sia.";
			link.l1.go = "DTSG_Knippel_55";
		break;
		
		case "DTSG_Knippel_55":			//КОНЕЦ ЭТАПА 2
			DialogExit();
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.location = "None";
			
			n = Findlocation("PortPax_town");
			locations[n].reload.l31.name = "houseF1";
			locations[n].reload.l31.go = "CommonRoom_MH9";
			locations[n].reload.l31.emerge = "reload1";
			locations[n].reload.l31.autoreload = "0";
			locations[n].reload.l31.label = "House";
			
			BackItemName("letter_1");
			BackItemDescribe("letter_1");
			TakeItemFromCharacter(pchar, "letter_1");
			AddQuestRecord("DTSG", "5");
			QuestOpenSeaExit()
			
			AddMapQuestMarkCity("SentJons", true);
			PChar.quest.DTSG_Etap3_Start.win_condition.l1 = "location";
			PChar.quest.DTSG_Etap3_Start.win_condition.l1.location = "Antigua";
			PChar.quest.DTSG_Etap3_Start.win_condition = "DTSG_Etap3_Start";
		break;
		
		case "DTSG_PiterAdams_20":
			if (CheckAttribute(pchar, "questTemp.DTSG_ZovemMatrosov"))
			{
				dialog.text = "Ah, eccovi qui, signore – pare che tutti abbiano deciso d’arrivare in anticipo. A giudicare dal vostro aspetto, sembrate ben allegro... Siete così sicuro delle vostre capacità?";
				link.l1 = "Naturalmente, questo non è di certo il mio primo duello.";
				link.l1.go = "DTSG_PiterAdams_Nastoroje_21";
				ChangeCharacterComplexReputation(pchar, "authority", 1);
			}
			else
			{
				dialog.text = "Temevo che non venisse, signore. Gli altri sono già arrivati.";
				link.l1 = "Un vero gentiluomo può arrivare tardi solo al suo funerale.";
				link.l1.go = "DTSG_PiterAdams_NN_21";
				ChangeCharacterComplexReputation(pchar, "nobility", 1);
			}
		break;
		
		case "DTSG_PiterAdams_NN_21":
			dialog.text = "Parole magnifiche, signore! Ecco il nostro avversario, Ralph Faggle. E questo è il nostro secondo, Frederick Stokes.";
			link.l1 = "...";
			link.l1.go = "DTSG_PiterAdams_NN_22";
		break;
		
		case "DTSG_PiterAdams_NN_22":
			dialog.text = "Incontriamoci...";
			link.l1 = "...";
			link.l1.go = "DTSG_PiterAdams_NN_23";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
		break;
		
		case "DTSG_PiterAdams_NN_23":
			dialog.text = "Il nostro avversario, Ralph Faggle.";
			link.l1 = "...";
			link.l1.go = "DTSG_PiterAdams_NN_24";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
			SetCameraDialogMode(CharacterFromID("DTSG_RalfFaggl2"));
		break;
		
		case "DTSG_PiterAdams_NN_24":
			dialog.text = "E questo è il nostro secondo, Frederick Stokes.";
			link.l1 = "...";
			link.l1.go = "DTSG_PiterAdams_NN_25";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
			SetCameraDialogMode(CharacterFromID("DTSG_FrederikStouks"));
		break;
		
		case "DTSG_PiterAdams_NN_25":
			dialog.text = "...";
			link.l1 = "Allora questo è Ralph? Non sembra proprio il solito ubriacone del vicinato.";
			link.l1.go = "DTSG_PiterAdams_NN_26";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
			SetCameraDialogMode(CharacterFromID("DTSG_RalfFaggl2"));
		break;
		
		case "DTSG_PiterAdams_NN_26":
			dialog.text = "Non puoi mai sapere chi ti capita accanto, ci hai mai pensato, signor de Maure? Eh-eh-eh.";
			link.l1 = "Dunque, è una trappola... Vedo che hai smesso pure di tremare. Stufo di far la parte dell'infermo?";
			link.l1.go = "DTSG_PiterAdams_NN_27";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
			SetCameraDialogMode(npchar);
		break;
		
		case "DTSG_PiterAdams_NN_27":
			dialog.text = "L’unica cosa che posso scrollarmi di dosso ormai è una risata per la tua ingenuità.";
			link.l1 = "Ebbene, ebbene. L’unico rimpianto è che Charlie s’è trascinato dietro – sarebbe stato più facile e silenzioso sistemarti da solo...";
			link.l1.go = "DTSG_PiterAdams_BitvaDuel";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_21":
			dialog.text = "Ebbene, che meraviglia!";
			link.l1 = "...";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_22";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_22":
			dialog.text = "Permettetemi di presentarmi...";
			link.l1 = "...";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_23";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
		break;
		
		case "DTSG_PiterAdams_Nastoroje_23":
			dialog.text = "Il signor Stokes, il nostro secondo.";
			link.l1 = "...";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_24";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
			SetCameraDialogMode(CharacterFromID("DTSG_FrederikStouks"));
		break;
		
		case "DTSG_PiterAdams_Nastoroje_24":
			dialog.text = "E questo è Ralph Faggle.";
			link.l1 = "Allora quello è Ralph? Devo ammetterlo, me lo immaginavo diverso. Ma poco importa, ho affrontato canaglie ben peggiori.";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_25";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
			SetCameraDialogMode(CharacterFromID("DTSG_RalfFaggl2"));
		break;
		
		case "DTSG_PiterAdams_Nastoroje_25":
			dialog.text = "Hmm, mi chiedo, sei tanto ingenuo da non capire nulla? O solo troppo sicuro di te stesso?";
			link.l1 = "E che cosa non capisco io, signor Adams? Avanti, stupiscimi.";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_26";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
			SetCameraDialogMode(npchar);
		break;
		
		case "DTSG_PiterAdams_Nastoroje_26":
			dialog.text = "Di solito, la gente si mostra sbalordita o impaurita in queste situazioni, ma tu sembri fatto d’un’altra pasta. Sarà ancora più soddisfacente cancellare quel sorrisetto arrogante dalla tua faccia, signor de Maure.";
			link.l1 = "Che minacce! Non siamo forse dalla stessa parte, Peter?";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_27";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_27":
			dialog.text = "Non vorrai farmi credere che pensi di batterci tutti con quel vecchio lupo di mare. Siete in netta inferiorità, caro mio.";
			link.l1 = "Come ti ho già detto, SEI TU che non capisci. Charlie ha brontolato un po', ma gli ho comunque ordinato di portare i ragazzi qui, per precauzione. E guarda un po', non per niente. RAGAZZI, VENITE QUI!!!";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_28";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_28":
			DialogExit();
			
			StartQuestMovie(true, false, true);
			locCameraFromToPos(0.34, 0.51, 34.93, true, -5.63, -1.20, 57.46);
			DoQuestCheckDelay("DTSG_PoP_Duel_Podkreplenie", 3.0);
			
			int DTSG_PoP_MK;
			if (MOD_SKILL_ENEMY_RATE == 2) DTSG_PoP_MK = 5;
			if (MOD_SKILL_ENEMY_RATE == 4) DTSG_PoP_MK = 5;
			if (MOD_SKILL_ENEMY_RATE == 6) DTSG_PoP_MK = 4;
			if (MOD_SKILL_ENEMY_RATE == 8) DTSG_PoP_MK = 4;
			if (MOD_SKILL_ENEMY_RATE == 10) DTSG_PoP_MK = 3;
			
			for (i=1; i<=DTSG_PoP_MK; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("DTSG_PoP_Matrosy_"+i, "citiz_3"+i, "man", "man", sti(pchar.rank)-5, sti(pchar.nation), -1, false, "quest"));
				GiveItem2Character(sld, "blade_11");
				sld.equip.blade = "blade_11";
				ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload3");
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, pchar, "", -1);
				sld.lifeday = 0;
				LAi_SetHP(sld, 120.0, 120.0);
			}
		break;
		
		case "DTSG_PiterAdams_Nastoroje_29":
			dialog.text = "Cosa?..";
			link.l1 = "Sorpreso e impaurito, signor Adams? Buon segno, questo.";
			link.l1.go = "DTSG_PiterAdams_BitvaDuel";
			SetCameraDialogMode(npchar);
		break;
		
		case "DTSG_PiterAdams_BitvaDuel":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("PortPax_ExitTown")], false);
			LAi_SetFightMode(pchar, true);
			
			for (i=1; i<=5; i++)
			{
				if (GetCharacterIndex("DTSG_PoP_Matrosy_"+i) != -1)
				{
					sld = CharacterFromID("DTSG_PoP_Matrosy_"+i);
					LAi_SetWarriorType(sld);
					LAi_CharacterDisableDialog(sld);
					LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				}
			}
			
			sld = CharacterFromID("Knippel");
			LAi_SetWarriorType(sld);
			LAi_SetCheckMinHP(sld, 10, true, "KnippelRanen");
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			sld = CharacterFromID("DTSG_PiterAdams");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			sld = CharacterFromID("DTSG_FrederikStouks");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			sld = CharacterFromID("DTSG_RalfFaggl2");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_PiterAdams_Duel_Pobeda");
		break;
		
		case "DTSG_Knippel_60":
			dialog.text = "Così si trattano quei furfanti bugiardi. Non riesco ancora a credere che abbiano avuto l’ardire di sparlare della Reale Marina! Li strozzerei con una palla incatenata!..";
			link.l1 = "Ormai dovresti saperlo, Charlie, che certi uomini non hanno né onore né scrupoli. Ti avevo detto che ci avrei pensato io, potevi benissimo restare a bordo. O volevi accertarti che davvero dessi una mano a questi ‘bravi cristiani’? E allora, chi aveva ragione? Non era poi così semplice, come credevi.";
			link.l1.go = "DTSG_Knippel_61";
		break;
		
		case "DTSG_Knippel_61":
			dialog.text = "Voi, signore...";
			link.l1 = "Esatto. Ma dimmi, perché mai qualcuno dovrebbe volerti dare la caccia? Non è la prima volta.";
			link.l1.go = "DTSG_Knippel_62";
		break;
		
		case "DTSG_Knippel_62":
			dialog.text = "Non so, Capitano. Il vecchio Charlie è solo un semplice cannoniere.";
			link.l1 = "Hmm, bene, bene. D'accordo, visto che i nostri poveri duellanti non avevano nulla di buono addosso... No, andiamo a vedere se riusciamo a scovare qualcosa nella casa di Adams.";
			link.l1.go = "DTSG_Knippel_63";
		break;
		
		case "DTSG_Knippel_63":
			DialogExit();
			
			LAi_RemoveCheckMinHP(npchar);
			LAi_SetImmortal(npchar, false);
			AddDialogExitQuestFunction("DTSG_Knippel_64");
		break;
		
		case "DTSG_Knippel_70":
			dialog.text = "Dunque, anche questa donna è sparita... Forse si stavano preparando a fuggire dalla città subito dopo quel 'duello'? E in tutta fretta – guarda quanta moneta d’oro qui!";
			link.l1 = "Hai ragione, perché non è solo l’oro che hanno lasciato dietro di sé. Un’altra lettera. Avevano talmente fretta che si sono scordati di darle fuoco. Guarda qui, ti piacerà quello che c’è scritto.";
			link.l1.go = "DTSG_Knippel_71";
		break;
		
		case "DTSG_Knippel_71":
			TakeItemFromCharacter(pchar, "letter_1");
			dialog.text = "(legge) Beh, avrei da ridire su 'vecchio'.";
			link.l1 = "Non è questo il punto adesso. È già la seconda volta che ti mandano addosso dei mercenari, fornendogli oro e dritte. E ce l’hanno proprio con te. Dimmi, vecchio artigliere, chi diavolo hai fatto arrabbiare così tanto?";
			link.l1.go = "DTSG_Knippel_72";
		break;
		
		case "DTSG_Knippel_72":
			dialog.text = "Ho un solo sospetto, signore, uno soltanto, e davvero non voglio che sia la verità.";
			link.l1 = "Dunque, sarà quasi certamente vero. Parla, avanti.";
			link.l1.go = "DTSG_Knippel_73";
		break;
		
		case "DTSG_Knippel_73":
			dialog.text = "Un tempo avevo dei debiti con certa gente a St. John's, e...";
			link.l1 = "... e adesso pensi che ti diano la caccia? Quanti possono permettersi mercenari e simili cifre?";
			link.l1.go = "DTSG_Knippel_74";
		break;
		
		case "DTSG_Knippel_74":
			dialog.text = "Hai ragione, signore. Alla fine, ho saldato quasi tutti i miei debiti prendendo in prestito da un usuraio. Lui può permettersi tutto questo, ovvio. Ma...";
			link.l1 = "Ma che c’è? Ti saldiamo il debito, e la faccenda è chiusa. Che ti rode, vecchio mio?";
			link.l1.go = "DTSG_Knippel_75";
		break;
		
		case "DTSG_Knippel_75":
			dialog.text = "Vedi, Capitano, Richard m’aveva giurato che l’avrebbe saldato lui per me.";
			link.l1 = "Pensi che non l’abbia fatto?";
			link.l1.go = "DTSG_Knippel_76";
		break;
		
		case "DTSG_Knippel_76":
			dialog.text = "Non so più che pensare, signore. Per tutto il tempo che ci siamo conosciuti, l’ho sempre ritenuto un vero gentiluomo. Ma dopo che vi ha abbandonato e se n’è scappato con Abigail... ormai nulla mi stupirebbe. Ecco perché ho detto che non vorrei fosse vero.";
			link.l1 = "Le supposizioni vanno verificate prima, poi potrai arrabbiarti, Charlie. Andiamo, farai di nuovo visita a St. John's.";
			link.l1.go = "DTSG_Knippel_77";
		break;
		
		case "DTSG_Knippel_77":			//КОНЕЦ ЭТАПА 2
			DialogExit();
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			npchar.location = "None";
			
			n = Findlocation("PortPax_town");
			locations[n].reload.l31.name = "houseF1";
			locations[n].reload.l31.go = "CommonRoom_MH9";
			locations[n].reload.l31.emerge = "reload1";
			locations[n].reload.l31.autoreload = "0";
			locations[n].reload.l31.label = "House";
			
			BackItemName("letter_1");
			BackItemDescribe("letter_1");
			AddQuestRecord("DTSG", "6");
			QuestOpenSeaExit()
			LAi_LocationDisableOfficersGen("PortPax_town", false);
			LAi_LocationDisableOfficersGen("PortPax_ExitTown", false);
			
			AddMapQuestMarkCity("SentJons", true);
			PChar.quest.DTSG_Etap3_Start.win_condition.l1 = "location";
			PChar.quest.DTSG_Etap3_Start.win_condition.l1.location = "Antigua";
			PChar.quest.DTSG_Etap3_Start.win_condition = "DTSG_Etap3_Start";
		break;
		
		case "DTSG_Knippel_PoPDuelTime":
			dialog.text = "Capitano!!!";
			link.l1 = "Cos’è successo, Charlie, che diavolo è andato storto?";
			link.l1.go = "DTSG_Knippel_PoPDuelTime_2";
		break;
		
		case "DTSG_Knippel_PoPDuelTime_2":
			dialog.text = "Successo?! Non ditemi che vi siete già scordato del duello, signore! Adams potrebbe già essere fatto a brandelli mentre voi ve ne state qui a poltrire!";
			link.l1 = "Bene!.. Me ne andrò subito da questa dannata città.";
			link.l1.go = "DTSG_Knippel_PoPDuelTime_3";
		break;
		
		case "DTSG_Knippel_PoPDuelTime_3":
			DialogExit();
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			DoQuestReloadToLocation("PortPax_ExitTown", "reload", "reload3", "");
		break;
		
		case "DTSG_AntiguaArest":
			dialog.text = "Capitano Charles de Maure? Quello è Charlie Knippel lì con te?";
			link.l1 = "No, questo...";
			link.l1.go = "DTSG_AntiguaArest_2";
		break;
		
		case "DTSG_AntiguaArest_2":
			dialog.text = "Non negarlo, signore – tutti in questa colonia conoscono Charlie.";
			link.l1 = "Allora perché domandi? In che modo posso esserti utile?";
			link.l1.go = "DTSG_AntiguaArest_3";
		break;
		
		case "DTSG_AntiguaArest_3":
			dialog.text = "Non puoi. Ti prego, non opporre resistenza – Charlie è ricercato qui. Dobbiamo metterlo in ceppi.";
			link.l1 = "Posso sapere di quali accuse è colpevole il mio uomo? È forse per i suoi debiti? Posso saldarli io per lui. Andiamo subito dal banchiere, e che si faccia tutto davanti ai vostri occhi.";
			link.l1.go = "DTSG_AntiguaArest_4";
		break;
		
		case "DTSG_AntiguaArest_4":
			dialog.text = "Un debito? Prima volta che ne sento parlare. Non conosco i dettagli, ma ti prego, non metterci nei guai – sto solo eseguendo degli ordini.";
			link.l1 = "Oh, è proprio una meraviglia...";
			link.l1.go = "DTSG_AntiguaArest_5";
		break;
		
		case "DTSG_AntiguaArest_5":
			StartInstantDialog("Knippel", "DTSG_AntiguaArest_6", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_AntiguaArest_6":
			dialog.text = "Capitano...";
			link.l1 = "Charlie, se scappiamo ora, ci metteranno una taglia ancora più grossa! E combattere non è un'opzione? Cercherò di tirarti fuori, ma non fare sciocchezze, dannazione!";
			link.l1.go = "DTSG_AntiguaArest_7";
		break;
		
		case "DTSG_AntiguaArest_7":
			DialogExit();
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			AddQuestRecord("DTSG", "8");
			pchar.questTemp.DTSG_KnippelDolg = true;
			
			sld = CharacterFromID("Knippel");
			RemovePassenger(pchar, sld);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload_jail", "", "", "", "", -1);
			sld.location = "None";
			
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("DTSG_AntiguaSold_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload_jail", "", "", "", "", -1);
				sld.location = "None";
			}
		break;
		
		case "DTSG_AntiguaStrazhBank":
			dialog.text = "Smettila subito di far chiasso e minacciare quest'uomo, signore. Deponi le armi e seguimi all'istante!";
			link.l1 = "Non ho minacciato nessuno, dev’esserci un errore. Si tratta d’affari, non d’un tentato omicidio.";
			link.l1.go = "DTSG_AntiguaStrazhBank_2";
		break;
		
		case "DTSG_AntiguaStrazhBank_2":
			dialog.text = "A me non pare proprio. Dovrai rispondere davanti alla legge.";
			link.l1 = "E se chiedessi scusa e me ne andassi?";
			link.l1.go = "DTSG_AntiguaStrazhBank_3";
		break;
		
		case "DTSG_AntiguaStrazhBank_3":
			dialog.text = "Così puoi sgattaiolare di nuovo dentro e finire quel che ho interrotto? Mi prendi forse per uno scemo?";
			link.l1 = "Devi proprio esserlo, se non vuoi risolverla da gentiluomini. Che Dio mi sia testimone, non volevo arrivare a questo...";
			link.l1.go = "DTSG_AntiguaStrazhBank_4";
		break;
		
		case "DTSG_AntiguaStrazhBank_4":
			DialogExit();
			bDisableFastReload = true;
			chrDisableReloadToLocation = true;
			
			LAi_LocationFightDisable(&Locations[FindLocation("SentJons_bank")], false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetFightMode(pchar, true);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_AntiguaStrazhBank_Ubili");
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki":
			dialog.text = "L’hai fatto fuori!..";
			link.l1 = "Consideralo fatto dalle tue stesse mani, signore. Potevi semplicemente rispondere alle mie domande invece di fare la femminuccia. Lo giuro, ancora un urlo e ti faccio saltare le cervella.";
			link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_V1";
			link.l2 = "Sì, l'ho fatto fuori io. Mi ci ha costretto, maledetto. Ma tu non sei uno stupido come lui, vero? Non seguirai la sua sorte, dico bene?";
			link.l2.go = "DTSG_AntiguaUsurer_PosleDraki_V2";
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki_V1":
			dialog.text = "Cosa vuoi?!";
			link.l1 = "Tempo fa, Charlie Knippel ti prese a prestito del denaro. Il suo compare aveva giurato di saldare il debito, ma a quanto pare ha fatto il furbo. Pretendo che tu la smetta subito d’inviarci quei tuoi tagliagole. Se me lo posso permettere, sono pronto a pagare io il debito di Charlie, qui e ora.";
			link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_3";
			AddComplexLandExpToScill(100, 0, 0);
			AddComplexSeaExpToScill(0, 0, 0, 0, 0, 0, 100);
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki_V2":
			dialog.text = "Cosa vuoi?!";
			link.l1 = "Tempo fa, Charlie Knippel ti ha preso in prestito del denaro. Un suo compare aveva promesso di saldare il debito, ma a quanto pare non l’ha fatto. Pretendo che tu la smetta subito di mandarci addosso quei tuoi tagliagole. Son pronto a pagare il debito di Charlie qui e ora, se il mio borsello lo permette.";
			link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_3";
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki_3":
			dialog.text = "Charlie?! I would never do that to him; he's a good, honest man. Besides, his debt has long been paid off. Mr. Fleetwood, the captain of the Valkyrie, settled it to the last peso.";
			link.l1 = "Davvero? So bene chi sia. Potevi dirmelo subito, accidenti. Scusa per il disturbo, addio.";
			link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_4";
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki_4":
			dialog.text = "Così, senza pensarci?! Mi hai minacciato! E hai sparso sangue, dannazione!..";
			link.l1 = "Hai dimenticato le mie parole? Un altro urlo e raggiungerai lui. Addio.";
			link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_5";
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki_5":
			DialogExit();
			
			LAi_LocationFightDisable(&Locations[FindLocation("SentJons_town")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("SentJons_bank")], true);
			//LAi_LocationDisableOfficersGen("SentJons_town", false);
			LAi_LocationDisableOfficersGen("SentJons_bank", false);
			npchar.dialog.filename = "Usurer_dialog.c";
			npchar.dialog.currentnode = "First time";
			LAi_SetOwnerType(npchar);
			
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterComplexReputation(pchar, "fame", 2);
			
			chrDisableReloadToLocation = false;
			AddQuestRecord("DTSG", "9");
			PChar.quest.DTSG_AntiguaTrevoga.win_condition.l1 = "location";
			PChar.quest.DTSG_AntiguaTrevoga.win_condition.l1.location = "SentJons_town";
			PChar.quest.DTSG_AntiguaTrevoga.win_condition = "DTSG_AntiguaTrevoga";
		break;
		
		case "DTSG_Killer":
			dialog.text = "Sei ancora qui e non ti hanno ancora impiccato? Beh, saluti dalla Sussex, Charlie.";
			link.l1 = "Salute a te, chiunque tu sia.";
			link.l1.go = "DTSG_Killer_2";
			CharacterTurnToLoc(npchar, "goto", "goto9");
		break;
		
		case "DTSG_Killer_2":
			dialog.text = "Ah, Charles de Maure. Che bello vederti, vecchio Charlie t’aspettava. Ci contavamo, sai.";
			link.l1 = "Chi siamo noi?";
			link.l1.go = "DTSG_Killer_3";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "DTSG_Killer_3":
			dialog.text = "Non importa. Ci hai fatto perdere tempo e denaro, signor de Maure. Penso che nessuno si lamenterà se sistemo sia Charlie che te qui e adesso.";
			link.l1 = "Ebbene, visto che siamo già entrambi condannati, vorresti almeno dirci, per puro spirito di carità, chi mai abbiamo fatto imbestialire così tanto? Promettiamo di non rifarlo. E chi diavolo è questo Sussex?";
			link.l1.go = "DTSG_Killer_4";
		break;
		
		case "DTSG_Killer_4":
			dialog.text = "Non posso. Il dovere chiama e, a differenza tua, io sono uomo di fatti, non di chiacchiere.";
			link.l1 = "Per l’amor di Dio, qualcuno si deciderà mai a spiegarmi che diavolo sta succedendo?!";
			link.l1.go = "DTSG_Killer_5";
		break;
		
		case "DTSG_Killer_5":
			DialogExit();
			LAi_SetFightMode(pchar, true);
			
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetImmortal(npchar, false);
			
			for (i=1; i<=12; i++)
			{
				if (GetCharacterIndex("SentJonsPrisoner_"+i) != -1)
				{
					sld = CharacterFromID("SentJonsPrisoner_"+i);
					sld.lifeday = 0;
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
			}
			
			for (i = 0; i < MAX_CHARACTERS; i++)
			{
				sld = GetCharacter(i);
				if (sld.city == "sentjons" && sld.location == "SentJons_prison")
				{
					sld.lifeday = 0;
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
			}
			
			sld = CharacterFromID("SentJonsJailOff");
			sld.lifeday = 0;
			ChangeCharacterAddressGroup(sld, "none", "", "");
			
			sld = GetCharacter(NPC_GenerateCharacter("DTSG_SentJonsJailOff", "off_eng_1", "man", "man", 30, PIRATE, 0, true, "soldier"));
			ChangeCharacterAddressGroup(sld, "SentJons_prison", "goto", "goto18");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			sld.rank = 30;
			SetSelfSkill(sld, 80, 80, 80, 80, 80);
			LAi_SetHP(sld, 200+MOD_SKILL_ENEMY_RATE*20, 200+MOD_SKILL_ENEMY_RATE*20);
			
			for (i=1; i<=3; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("DTSG_AntiguaSoldTurma_"+i, "sold_eng_"+(rand(7)+1), "man", "man", sti(pchar.rank), PIRATE, 0, true, "soldier"));
				ChangeCharacterAddressGroup(sld, "SentJons_prison", "goto", "goto22");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			
			for (i=4; i<=7; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("DTSG_AntiguaSoldTurma_"+i, "sold_eng_"+(rand(7)+1), "man", "man", sti(pchar.rank), PIRATE, 0, true, "soldier"));
				ChangeCharacterAddressGroup(sld, "SentJons_prison", "reload", "reload1");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			
			/*sld = CharacterFromID("SentJons_Mayor");
			LAi_group_Attack(sld, Pchar);*/
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_TurmaDayPobeda");
		break;
		
		case "DTSG_KnippelDaySpasen":
			dialog.text = "Per tutti i diavoli, Capitano, che macello avete combinato qui!";
			link.l1 = "Obietti, eh? Preferiresti la forca? O magari marcire qui finché il tempo non ti consuma?";
			link.l1.go = "DTSG_KnippelDaySpasen_2";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_KnippelDaySpasen_2":
			dialog.text = "No, signore. Grazie per avermi salvato. A dire il vero, son sorpreso che sia venuto, visto con quanta facilità mi ha lasciato nelle loro mani. E son stupito di come abbia sistemato la sentinella – era una Volpe di Mare. Un marine.";
			link.l1 = "Te l’avevo detto che ti avrei tirato fuori, non dovevi dubitare. Ora levati da questa cella prima che tutta la guarnigione venga qui.";
			link.l1.go = "DTSG_KnippelDaySpasen_3";
		break;
		
		case "DTSG_KnippelDaySpasen_3":
			dialog.text = "Ai vostri ordini, Capitano.";
			link.l1 = "...";
			link.l1.go = "DTSG_KnippelDaySpasen_4";
		break;
		
		case "DTSG_KnippelDaySpasen_4":
			DialogExit();
			
			Pchar.GenQuest.Hunter2Pause = true;
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("DTSG_TurmaDayPobeda_2", 1.0);
		break;
		
		case "DTSG_KnippelDaySpasen_5":
			dialog.text = "Maledizione, signore, faccio fatica a crederci...";
			link.l1 = "A proposito, dimmi, di che cosa ti hanno accusato? E chi diavolo è questo Sussex?";
			link.l1.go = "DTSG_KnippelDaySpasen_6";
		break;
		
		case "DTSG_KnippelDaySpasen_6":
			dialog.text = "Non saprei, signore. Non ho la più pallida idea di chi intendessero con quella storia...";
			link.l1 = "D’accordo, lo scopriremo più tardi. Ora dobbiamo levarci di qui.";
			link.l1.go = "DTSG_KnippelDaySpasen_7";
		break;
		
		case "DTSG_KnippelDaySpasen_7":
			DialogExit();
			
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			AddPassenger(pchar, npchar, false);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			npchar.location = "None";
			AddQuestRecord("DTSG", "12");
			
			PChar.quest.DTSG_KnippelRazgovorVKaute.win_condition.l1 = "EnterToSea"
			PChar.quest.DTSG_KnippelRazgovorVKaute.win_condition = "DTSG_KnippelRazgovorVKaute";
		break;
		
		case "DTSG_AntiguaNightPirs":
			dialog.text = "Quali son le prossime mosse, signore? Sbarellare i denti a quel sanguisuga in pieno giorno è roba rischiosa.";
			link.l1 = "Mi hai appena dato un’idea. Perché aspettare il giorno per cavargli il buonsenso a suon di botte, quando possiamo farlo ora, al riparo della notte?";
			link.l1.go = "DTSG_AntiguaNightPirs_2";
		break;
		
		case "DTSG_AntiguaNightPirs_2":
			dialog.text = "Per tutti i diavoli, questa sì che è un’idea geniale, Capitano!";
			link.l1 = "Esattamente. Dimmi, Charlie, hai vissuto qui per un po’. Sai dove abita l’usuraio?";
			link.l1.go = "DTSG_AntiguaNightPirs_3";
		break;
		
		case "DTSG_AntiguaNightPirs_3":
			dialog.text = "Lo sapevo, signore, ma l’ultima volta che ci son passato, stava vendendo la sua casa. Non ho la minima idea di dove abbia messo radici ora.";
			link.l1 = "Ebbene, questo è un bel guaio...";
			link.l1.go = "DTSG_AntiguaNightPirs_4";
		break;
		
		case "DTSG_AntiguaNightPirs_4":
			dialog.text = "Sono certo che troverai una soluzione, Capitano, dopotutto hai messo al tappeto quel gran bastardo di Lucas Rodenburg!";
			link.l2 = "D'accordo, ci penso io. Però, se sapessi dove si trova la casa dell'usuraio, sarebbe ancor meglio!";
			link.l2.go = "DTSG_AntiguaIskat_1";
			link.l1 = "Così ho fatto. Ma, Charlie, la notte porta consiglio: riposiamoci dal viaggio e andiamoci di giorno – non siamo qui per far fuori quell’uomo, dopotutto.";
			link.l1.go = "DTSG_AntiguaSpat_1";
		break;
		
		case "DTSG_AntiguaSpat_1":
			dialog.text = "Ne siete certo, signore? Perderemo l’effetto sorpresa.";
			link.l1 = "Sono sicuro e sono stanco. E poi, voglio solo parlarci. Spaventarlo un poco, se proprio serve.";
			link.l1.go = "DTSG_AntiguaSpat_2";
		break;
		
		case "DTSG_AntiguaSpat_2":
			TavernWaitDate("wait_day");
			DoQuestReloadToLocation("SentJons_tavern_upstairs", "goto", "goto2", "DTSG_AntiguaSpat_3");
		break;
		
		case "DTSG_AntiguaIskat_1":
			dialog.text = "Quello che non so, non lo so, mi dispiace, signore.";
			link.l1 = "Ah, lascia perdere, andiamo a cercarlo.";
			link.l1.go = "DTSG_AntiguaIskat_2";
		break;
		
		case "DTSG_AntiguaIskat_2":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			
			AddQuestRecord("DTSG", "13");
			pchar.questTemp.DTSG_NightIskat = true;
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			pchar.GenQuest.CannotWait = true;
			pchar.questTemp.TimeLock = true;
		break;
		
		case "DTSG_Knippel_SluhSmertFleetWood":
			dialog.text = "State pensando quello che penso anch’io, signore?";
			link.l1 = "Temo di sì, Charlie. Non c’è altro capitano famoso con quel nome nei Caraibi. E Richard è davvero andato a Londra. Difficile che sia una semplice coincidenza.";
			link.l1.go = "DTSG_Knippel_SluhSmertFleetWood_2";
		break;
		
		case "DTSG_Knippel_SluhSmertFleetWood_2":
			dialog.text = "Orribile... Sebbene gli abbia rivolto parole aspre, non gli ho mai augurato una fine simile! E la povera Abi!.. Era incinta. Spero sia ancora in vita...";
			link.l1 = "Già, non lo augurerei a nessuno. Speriamo che Abi stia bene. Hai idea di chi possa aver fatto questo a Dick? Ha mai nominato qualche nemico potente?";
			link.l1.go = "DTSG_Knippel_SluhSmertFleetWood_3";
		break;
		
		case "DTSG_Knippel_SluhSmertFleetWood_3":
			dialog.text = "Devi scherzare, Capitano. Non so com'è in Europa, ma qui ogni dannato olandese voleva vedere Richard stecchito.";
			link.l1 = "Vero. Forse qualcuno qui ha sborsato una fortuna e mandato sicari a inseguirlo fino al Vecchio Mondo. E se dietro gli attacchi a te non ci fosse questo meschino usuraio, ma qualche misterioso nemico di Richard?";
			link.l1.go = "DTSG_Knippel_SluhSmertFleetWood_4";
		break;
		
		case "DTSG_Knippel_SluhSmertFleetWood_4":
			dialog.text = "Non lo so, signore. A questo punto tutto può succedere. Ma ci complicherebbe la vita a tutti quanti...";
			link.l1 = "Sì, hai ragione, nemmeno a me piace questa possibilità.";
			link.l1.go = "DTSG_Knippel_SluhSmertFleetWood_5";
		break;
		
		case "DTSG_Knippel_SluhSmertFleetWood_5":
			DialogExit();
			npchar.location = "None";
			
			AddQuestRecord("DTSG", "14");
			pchar.questTemp.DTSG_Nastoroje2 = true;
			chrDisableReloadToLocation = false;
			
			PChar.quest.DTSG_NightDom.win_condition.l1 = "locator";
			PChar.quest.DTSG_NightDom.win_condition.l1.location = "SentJons_town";
			PChar.quest.DTSG_NightDom.win_condition.l1.locator_group = "reload";
			PChar.quest.DTSG_NightDom.win_condition.l1.locator = "houseSp3";
			PChar.quest.DTSG_NightDom.win_condition = "DTSG_NightDom";
		break;
		
		case "DTSG_NightRostovshik":
			dialog.text = "Cosa, chi... COSA?! Che succede?.. Chi diavolo sei?..";
			link.l1 = "Oh, dai. Se volessi ammazzarti, lo farei mentre dormi. Non rendiamoci la vita più difficile o più corta, eh. Fai cenno se hai capito.";
			link.l1.go = "DTSG_NightRostovshik_2";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_NightRostovshik_2":
			dialog.text = "Mmm-hmm...";
			link.l1 = "Molto bene. Calmati – non sono qui per derubarti, rapirti o farti del male.";
			link.l1.go = "DTSG_NightRostovshik_3";
		break;
		
		case "DTSG_NightRostovshik_3":
			dialog.text = "Allora... perché sei qui? Perché non potevi venire al mattino?";
			link.l1 = "Perché qualche riccone influente sta dando la caccia al mio compare. Abbiamo motivo di credere che sia tu, quindi non è proprio sicuro per lui passeggiare per queste strade in pieno giorno.";
			link.l1.go = "DTSG_NightRostovshik_4";
		break;
		
		case "DTSG_NightRostovshik_4":
			dialog.text = "Ma davvero non capisco di cosa stiate parlando, signore...";
			link.l1 = "Charlie Knippel. Tutti in città lo conoscono. Pensa bene. Ti deve dei soldi.";
			link.l1.go = "DTSG_NightRostovshik_5";
		break;
		
		case "DTSG_NightRostovshik_5":
			dialog.text = "Il nostro vecchio Charlie?? Eh già, ma il suo debito è stato saldato tempo fa, anche se non da lui in persona.";
			link.l1 = "E chi sarebbe stato questo benefattore?";
			link.l1.go = "DTSG_NightRostovshik_6";
		break;
		
		case "DTSG_NightRostovshik_6":
			dialog.text = "Il suo capitano, lord Richard Fleetwood. Se non mi credi, posso mostrarti i miei registri.";
			link.l1 = "Fleetwood, dici? Allora ti credo. Quindi, non hai mandato tagliagole dietro a Charlie?";
			link.l1.go = "DTSG_NightRostovshik_7";
		break;
		
		case "DTSG_NightRostovshik_7":
			dialog.text = "Ma certo che no, perché mai dovrei?? E dimmi, che senso avrebbe tutto ciò?";
			link.l1 = "Proprio così. Scusa per la visita a quest’ora. Buonanotte.";
			link.l1.go = "DTSG_NightRostovshik_8";
		break;
		
		case "DTSG_NightRostovshik_8":
			DialogExit();
			
			PChar.quest.DTSG_NightDom_3.win_condition.l1 = "locator";
			PChar.quest.DTSG_NightDom_3.win_condition.l1.location = "SentJons_houseSP3";
			PChar.quest.DTSG_NightDom_3.win_condition.l1.locator_group = "reload";
			PChar.quest.DTSG_NightDom_3.win_condition.l1.locator = "reload1";
			PChar.quest.DTSG_NightDom_3.win_condition = "DTSG_NightDom_3";
			
			LAi_CharacterDisableDialog(npchar);
			Pchar.GenQuest.Hunter2Pause = true;
			AddQuestRecord("DTSG", "15");
		break;
		
		case "DTSG_NightKiller":
			dialog.text = "Che c’è, Charlie, speravi di nasconderti stanotte dal tuo vecchio protettore? Non c’è più. Ma presto lo incontrerai, statene certo. Saluti dalla Sussex.";
			link.l1 = "Lo sapevamo già. E chi diavolo è questo Sussex? E tu, chi sei?";
			link.l1.go = "DTSG_NightKiller_2";
		break;
		
		case "DTSG_NightKiller_2":
			dialog.text = "Non sono affari tuoi, signor de Maure. Peccato che tu ti sia ficcato in questo pasticcio più di quanto avremmo voluto. Sei una vera scocciatura.";
			link.l1 = "Un fastidio per chi? Ti prego, non dirmi che ho passato la notte con la moglie di qualche inglese importante e furibondo.";
			link.l1.go = "DTSG_NightKiller_3";
		break;
		
		case "DTSG_NightKiller_3":
			dialog.text = "Molto spiritoso. Hai trovato il tempo per scherzare, eh? Pare che quello che si dice di te sia vero.\nCosa vogliamo? La testa di Charlie ci basterebbe. Ma visto tutto il fastidio che ci hai dato, stavolta riguarda anche te – continui a ficcare il naso dove non ti compete.";
			link.l1 = "Suppongo che siamo agli arresti, eh?";
			link.l1.go = "DTSG_NightKiller_4";
		break;
		
		case "DTSG_NightKiller_4":
			dialog.text = "Arresto? No, caro mio, il tempo dei mezzi termini è finito. Questa è un’esecuzione, capitano de Maure.";
			link.l1 = "D'accordo. La sola domanda è: di chi.";
			link.l1.go = "DTSG_NightKiller_5";
		break;
		
		case "DTSG_NightKiller_5":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("SentJons_town")], false);
			LAi_SetFightMode(pchar, true);
			sld = CharacterFromID("Knippel");
			LAi_SetOfficerType(sld);
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("DTSG_Killers_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_NightKiller_Pobeda");
		break;
		
		case "DTSG_Knippel_80":
			dialog.text = "Non pensavo che le Volpi di Mare ci avrebbero messo le zampe...";
			link.l1 = "Ebbene, c’è sempre una prima volta per tutto. Dimmi, Charlie, chi è Sussex?";
			link.l1.go = "DTSG_Knippel_81";
		break;
		
		case "DTSG_Knippel_81":
			dialog.text = "Io...";
			link.l1 = "Non vedi fin dove siamo arrivati? E pare proprio che navighiamo sulla stessa barca, Charlie. Ho dunque il diritto di sapere i dettagli.";
			link.l1.go = "DTSG_Knippel_82";
		break;
		
		case "DTSG_Knippel_82":
			dialog.text = "Certo, Capitano. Ma non qui, giusto? Parliamone a bordo, lontano da quest’isola.";
			link.l1 = "Hai ragione. Va bene, muoviamoci in fretta.";
			link.l1.go = "DTSG_Knippel_83";
		break;
		
		case "DTSG_Knippel_83":
			DialogExit();
			AddQuestRecord("DTSG", "16");
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			DeleteAttribute(pchar,"questTemp.TimeLock");
			chrDisableReloadToLocation = false;
			//LAi_LocationDisableOfficersGen("SentJons_town", false);
			LAi_LocationDisableOfficersGen("SentJons_bank", false);
			
			sld = CharacterFromID("Knippel");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			
			PChar.quest.DTSG_KnippelRazgovorVKaute.win_condition.l1 = "EnterToSea"
			PChar.quest.DTSG_KnippelRazgovorVKaute.win_condition = "DTSG_KnippelRazgovorVKaute";
		break;
		
		case "DTSG_KnippelRazgovorOProshlom":
			dialog.text = "Mi avete chiamato, Capitano?";
			link.l1 = "Sì, Charlie. Dobbiamo parlare. Credo tu abbia già intuito di cosa si tratta.";
			link.l1.go = "DTSG_KnippelRazgovorOProshlom_2";
			DelLandQuestMark(npchar);
			//LAi_LocationDisableOfficersGen("SentJons_town", true);
		break;
		
		case "DTSG_KnippelRazgovorOProshlom_2":
			dialog.text = "Aye, signore...";
			link.l1 = "Bene. Dimmi allora perché i tuoi compatrioti, persino le truppe scelte, ti danno la caccia se non sei un dannato fuorilegge.";
			link.l1.go = "DTSG_KnippelRazgovorOProshlom_3";
		break;
		
		case "DTSG_KnippelRazgovorOProshlom_3":
			dialog.text = "Non ne ho davvero idea, signore...";
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				link.l1 = "Non è uno scherzo, Charlie. Chi ti dà la caccia comanda quei maledetti lupi di mare. Probabilmente è pure coinvolto nell'assassinio di Richard. Quindi se hai qualcosa in mente, sputa il rospo. Che saluti da Sussex sono questi, chi diavolo è?";
			}
			else
			{
				link.l1 = "Non distogliere lo sguardo, Charlie. Vedo che sai qualcosa. Come tuo capitano, ti ordino di raccontarmi tutto. Chi è questo Sussex?";
			}
			link.l1.go = "DTSG_KnippelRazgovorOProshlom_4";
		break;
		
		case "DTSG_KnippelRazgovorOProshlom_4":
			dialog.text = "D'accordo, Capitano. Il Sussex non è una persona. È... una nave.";
			link.l1 = "Saluti da una nave? Che sciocchezze.";
			link.l1.go = "DTSG_KnippelRazgovorOProshlom_5";
		break;
		
		case "DTSG_KnippelRazgovorOProshlom_5":
			dialog.text = "Permettetemi di spiegare. Posso sedermi, signore? La storia è lunga e poco piacevole.";
			link.l1 = "Certo, Charlie. Vai pure avanti.";
			link.l1.go = "DTSG_KnippelRazgovorOProshlom_6";
		break;
		
		case "DTSG_KnippelRazgovorOProshlom_6":
			DialogExit();
			SetCurrentTime(2, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			SetMainCharacterIndex(GetCharacterIndex("Knippel"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			SetLaunchFrameFormParam(StringFromKey("Knippel_11", NewStr()), "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("SentJons_houseH1", "goto", "goto2", "DTSG_KnippelDoma");
			LaunchFrameForm();
			//DoQuestReloadToLocation("SentJons_houseH1", "goto", "goto2", "DTSG_KnippelDoma");
		break;
		
		case "DTSG_Kurier":
			dialog.text = "Ehi, Charlie, vengo dal Capitano Fleetwood. Vuole vederti.";
			link.l1 = "Grazie, compare. È successo qualcosa? Di solito, manda tutto tramite te senza indugio.";
			link.l1.go = "DTSG_Kurier_2";
		break;
		
		case "DTSG_Kurier_2":
			dialog.text = "Non lo so. Dice che vuole parlarne direttamente con te. Sono affari vostri, sistematevela tra di voi.";
			link.l1 = "Oh, ho un brutto presentimento su questa faccenda...";
			link.l1.go = "DTSG_Kurier_3";
		break;
		
		case "DTSG_Kurier_3":
			DialogExit();
			
			locCameraSleep(true);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "", "", "", "DTSG_KD1", -1);
			npchar.lifeday = 0;
			npchar.location = "None";
			
			/*PChar.quest.DTSG_KD1.win_condition.l1 = "locator";
			PChar.quest.DTSG_KD1.win_condition.l1.location = "SentJons_houseH1";
			PChar.quest.DTSG_KD1.win_condition.l1.locator_group = "reload";
			PChar.quest.DTSG_KD1.win_condition.l1.locator = "reload1";
			PChar.quest.DTSG_KD1.win_condition = "DTSG_KD1";
			
			PChar.quest.DTSG_KD2.win_condition.l1 = "locator";
			PChar.quest.DTSG_KD2.win_condition.l1.location = "SentJons_town";
			PChar.quest.DTSG_KD2.win_condition.l1.locator_group = "reload";
			PChar.quest.DTSG_KD2.win_condition.l1.locator = "houseSp3";
			PChar.quest.DTSG_KD2.win_condition = "DTSG_KD2";*/
			
			pchar.questTemp.Knippel.Soldiers_1 = true;
		break;
		
		case "DTSG_Cortny":
			dialog.text = "...";
			link.l1 = "Buona notte, signore!";
			link.l1.go = "DTSG_Cortny_2";
		break;
		
		case "DTSG_Cortny_2":
			dialog.text = "Buona notte. Lasciami passare.";
			link.l1 = "Ma certo, procedi pure, chiedo venia, signore.";
			link.l1.go = "DTSG_Cortny_3";
		break;
		
		case "DTSG_Cortny_3":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "", "", "", "", -1);
			npchar.lifeday = 0;
			npchar.location = "None";
			
			/*PChar.quest.DTSG_KD4.win_condition.l1 = "locator";
			PChar.quest.DTSG_KD4.win_condition.l1.location = "SentJons_houseSP3";
			PChar.quest.DTSG_KD4.win_condition.l1.locator_group = "reload";
			PChar.quest.DTSG_KD4.win_condition.l1.locator = "reload2";
			PChar.quest.DTSG_KD4.win_condition = "DTSG_KD4";*/
			DoQuestCheckDelay("DTSG_KD3_2", 3.0);
			locCameraSleep(true);
			
			sld = CharacterFromID("Fleetwood");
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_houseSP3_room", "goto", "goto1");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Fleetwood";
			sld.greeting = "";
		break;
		
		case "DTSG_Fleetwood":
			dialog.text = "Ah, sei tu, Charlie. Entra, entra pure. Chiudi la porta dietro di te.";
			link.l1 = "Buonanotte, Capitano. Che succede? E chi era quell'uomo? Un pavone vanitoso...";
			link.l1.go = "DTSG_Fleetwood_2";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_Fleetwood_2":
			dialog.text = "Questo non lo posso dire. E non permetterò che nessun orecchio indiscreto ascolti le nostre parole. Non fiatare a nessuno di questo affare, intesi?";
			link.l1 = "Sì, signore. È successo qualcosa? Vi vedo stranamente preoccupato, non è da voi.";
			link.l1.go = "DTSG_Fleetwood_3";
			//locCameraFromToPos(0.77, 1.87, -0.42, true, -1.34, -0.10, -1.35);
		break;
		
		case "DTSG_Fleetwood_3":
			dialog.text = "Così ti pare. Neanche tu hai un aspetto da ballo — è notte, dopotutto. Ma temo che il tuo riposo sia finito per stanotte, compare — ci aspetta una missione urgente e segretissima.";
			link.l1 = "E che cosa comporterà, Capitano?";
			link.l1.go = "DTSG_Fleetwood_4";
		break;
		
		case "DTSG_Fleetwood_4":
			dialog.text = "Eliminare un traditore. Dei nostri. Presto, una nave diplomatica dal Vecchio Mondo farà vela verso le coste di Dominica – la fregata 'Sussex'. Ufficialmente, dovrebbero trattare un buon affare coi dannati olandesi. Ma in verità...";
			link.l1 = "... trasmetteranno forse notizie ai nostri nemici, signore?";
			link.l1.go = "DTSG_Fleetwood_5";
		break;
		
		case "DTSG_Fleetwood_5":
			dialog.text = "Ancora peggio. Passeranno del tutto dalla loro parte. E anche se saranno sfiniti dopo aver traversato l’Atlantico, resta pur sempre una buona fregata – di sicuro tenteranno la fuga se li attacchiamo con un vascello pesante.\nDobbiamo muoverci in fretta e senza esitazioni. Possiamo contare solo sulla 'Valkyrie' – è l’unica capace d’una simile impresa.";
			link.l1 = "La vecchia 'Valkyrie' saprà domare una fregata?..";
			link.l1.go = "DTSG_Fleetwood_6";
		break;
		
		case "DTSG_Fleetwood_6":
			dialog.text = "Ah-ah, Charlie, dubiti del tuo capitano? E poi, come ti ho già detto, saranno sfiniti. Se attacchiamo all’improvviso, tutto il vantaggio sarà dalla nostra parte.";
			link.l1 = "Mai lo farei! Ma spero che tu sappia quel che stai facendo, signore...";
			link.l1.go = "DTSG_Fleetwood_7";
		break;
		
		case "DTSG_Fleetwood_7":
			dialog.text = "Ne sono certo. E un'altra cosa. Questo traditore occupa un posto di rilievo persino in Parlamento, capisci? Potrebbe aver occhi e orecchie ovunque – non solo in patria, ma già qui, nei Caraibi. Quindi non parlare del Sussex né di alcun dettaglio della nostra missione in città.";
			link.l1 = "Non c’era bisogno che lo diceste, signore. Potete sempre contare sul vecchio Charlie.";
			link.l1.go = "DTSG_Fleetwood_8";
		break;
		
		case "DTSG_Fleetwood_8":
			dialog.text = "Lo so. Solo che stavolta la posta in gioco è più alta che mai. Raduna le tue cose e preparati – salpiamo all’alba.";
			link.l1 = "Aye, signore. Buonanotte, signore.";
			link.l1.go = "DTSG_Fleetwood_9";
		break;
		
		case "DTSG_Fleetwood_9":
			DeleteAttribute(pchar,"questTemp.TimeLock");
			SetCurrentTime(11, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			DoQuestReloadToLocation("SentJons_houseH1", "reload", "reload1", "DTSG_KD6");
		break;
		
		case "DTSG_Knippel_SamSoboi":
			dialog.text = "Non ho mai visto Richard così... Era così preoccupato o forse... impaurito?";
			link.l1 = "Ma perché? Non me l'ha nemmeno confidato. Beh, poco importa. È un gran capitano, saprà certo domare questa fregata e la sua ciurma sfiancata.";
			link.l1.go = "DTSG_Knippel_SamSoboi_2";
			DeleteAttribute(pchar, "questTemp.lockedMusic");
		break;
		
		case "DTSG_Knippel_SamSoboi_2":
			DialogExit();
			SetLaunchFrameFormParam("August 17th, 1654"+ NewStr() +", SE of Dominica", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Ship_deck_Big", "reload", "reload1", "DTSG_ProshloeDominika_2");
			LaunchFrameForm();
			DeleteAttribute(pchar, "questTemp.Knippel.Soldiers_1");
			DeleteAttribute(pchar, "questTemp.Knippel.Soldiers_2");
			DeleteAttribute(pchar, "questTemp.Knippel.Soldiers_3");
		break;
		
		case "DTSG_Fleetwood_10":
			dialog.text = "La 'Sussex' è all’orizzonte, Charlie, preparati.";
			link.l1 = "Sempre pronto, Capitano.";
			link.l1.go = "DTSG_Fleetwood_11";
		break;
		
		case "DTSG_Fleetwood_11":
			dialog.text = "Benissimo. Conto su di te e sulle tue palle incatenate. Cerca di sbrindellare le loro vele il più in fretta possibile, o meglio ancora, abbatti un albero. Non ha senso rischiare tutto per affondarli, quindi io proverò ad abbordarli.\nInoltre, dobbiamo essere certi che il traditore sia morto – se li affondiamo, dovremo comunque avvicinarci e assicurarci che nessuno sia sopravvissuto.";
			link.l1 = "E ammazzare tanti compatrioti per un solo traditore...";
			link.l1.go = "DTSG_Fleetwood_12";
		break;
		
		case "DTSG_Fleetwood_12":
			dialog.text = "Tristemente. Anche a me pesa, Charlie. Ma gli ordini son ordini. Almeno non lo facciamo per spasso. Quindi sbrighiamocela in fretta.";
			link.l1 = "Sì, signore...";
			link.l1.go = "DTSG_Fleetwood_13";
		break;
		
		case "DTSG_Fleetwood_13":
			DialogExit();
			EndQuestMovie();
			AddItems(pchar, "potion4", 10);
			AddItems(pchar, "bullet", 10);
			AddItems(pchar, "GunPowder", 10);
			AddItems(pchar, "grapeshot", 10);
			AddItems(pchar, "cartridge", 10);
			PlaySound("interface\abordage.wav");
			PlaySound("interface\abordage.wav");
			PlaySound("interface\MusketFire1.wav");
			PlaySound("interface\MusketFire1.wav");
			
			SetLaunchFrameFormParam("2 hours later..."+ NewStr() +"Boarding the 'Sussex'", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Location_reserve_06", "rld", "aloc14", "DTSG_ProshloeDominika_12");
			LaunchFrameForm();
			
			n = Findlocation("Location_reserve_06");
			DeleteAttribute(&locations[n], "IslandId");
			DeleteAttribute(&locations[n], "type");
			DeleteAttribute(&locations[n], "models");
			DeleteAttribute(&locations[n], "environment");
			DeleteAttribute(&locations[n], "Box1");
			DeleteAttribute(&locations[n], "Box2");
			DeleteAttribute(&locations[n], "Box3");
			Locations[n].id.label = "Orlop deck";
			Locations[n].filespath.models = "locations\decks\oldeck";
			Locations[n].image = "loading\Boarding_B" + rand(3) + ".tga";
			//Sound
			locations[n].type = "deck_fight";
			//Models
			//Always
			Locations[n].models.always.ODeck = "oldeck";
			Locations[n].models.always.locators = "oldeck_locators";

			//Day
			Locations[n].models.day.charactersPatch = "oldeck_patch";
			Locations[n].models.day.fonar = "oldeck_fday";
			//Night
			Locations[n].models.night.charactersPatch = "oldeck_patch";
			Locations[n].models.night.fonar = "oldeck_fnight";
			//Environment
			Locations[n].environment.sea = "true";
			Locations[n].environment.weather = "true";
		break;
		
		case "DTSG_Graf_Sheffild_1":
			//StartQuestMovie(true, false, true);
			dialog.text = "Basta! Sono pronto a consegnare la mia spada e ascoltare le vostre richieste. Ma prima, presentatevi! Chi siete voi e con quale coraggio osate attaccarci?! Questo è tradimento!";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_2";
			SetCameraDialogMode(npchar);
			CharacterTurnByChr(npchar, CharacterFromID("Fleetwood"));
		break;
		case "DTSG_Graf_Sheffild_2":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("Fleetwood");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_3";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_3":
			dialog.text = "Capitano Richard Fleetwood. E tu devi essere il conte Sheffield? E hai proprio ragione, questa è tradimento.";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_5";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Graf_Sheffild"));
		break;
		case "DTSG_Graf_Sheffild_5":
			DialogExit();
			sld = CharacterFromID("DTSG_Graf_Sheffild");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_6";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_6":
			dialog.text = "Sai chi sono io? Maledizione! Lo sapevo che sarebbe finita così, topi dappertutto, quindi ho chiesto, anzi, ho implorato una nave da guerra...";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_7";
			CharacterTurnByChr(npchar, CharacterFromID("Fleetwood"));
		break;
		case "DTSG_Graf_Sheffild_7":
			DialogExit();
			sld = CharacterFromID("Fleetwood");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_8";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_8":
			dialog.text = "Non ti avrebbe salvato, avrebbe solo rimandato l’inevitabile, perché avrei trovato un altro modo. E sì, quando dico tradimento, intendo il tuo, conte Sheffield.";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_9";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Graf_Sheffild"));
		break;
		case "DTSG_Graf_Sheffild_9":
			DialogExit();
			sld = CharacterFromID("DTSG_Graf_Sheffild");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_10";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_10":
			dialog.text = "Allora non sai un accidente di me, signore! Tutti sanno che più leale di me verso l’Inghilterra non ne trovi! Ti pentirai di questo torto, segna le mie parole.";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_12";
			CharacterTurnByChr(npchar, CharacterFromID("Fleetwood"));
		break;
		case "DTSG_Graf_Sheffild_12":
			DialogExit();
			sld = CharacterFromID("Fleetwood");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_13";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_13":
			dialog.text = "Non ho nulla da rimpiangere, visto che non sono io quello che diserta per unirsi agli olandesi.";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_15";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Graf_Sheffild"));
		break;
		case "DTSG_Graf_Sheffild_15":
			DialogExit();
			sld = CharacterFromID("DTSG_Graf_Sheffild");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_16";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_16":
			dialog.text = "Cosa?! Che sciocchezze vai blaterando?! Ti sei fatto abbindolare, e hai seguito una falsa pista come un cane rabbioso\nEhm, è vero, sto andando a trattare con la Compagnia Olandese delle Indie Occidentali. Ma tutto per il bene dell’Inghilterra, Capitano. È un errore tremendo, ma possiamo ancora rimediare.";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_17";
			CharacterTurnByChr(npchar, CharacterFromID("Fleetwood"));
		break;
		case "DTSG_Graf_Sheffild_17":
			DialogExit();
			sld = CharacterFromID("Fleetwood");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_18";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_18":
			dialog.text = "Temo che non dipenda da me. E di certo nemmeno da voi. Avete scelto la parte sbagliata, signori. Addio.";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_19";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Graf_Sheffild"));
		break;

		case "DTSG_Graf_Sheffild_19":
			DialogExit();
			LAi_SetActorType(pchar);
			sld = CharacterFromID("Fleetwood");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Shot", "1", 1.8);
			DoQuestCheckDelay("DTSG_Graf_Sheffild_20", 0.9);
		break;
		
		case "DTSG_Graf_Sheffild_22":
			dialog.text = "Abbiamo finito qui. Pensavo che quell’uomo grasso non avrebbe mai smesso di strillare. Ah, questi conti, vero Charlie?";
			link.l1 = "Mi chiedo solo, signore, e se il colonnello si fosse sbagliato? O, Dio non voglia, ci avesse mentito per sbarazzarsi del Conte?";
			link.l1.go = "DTSG_Graf_Sheffild_23";
		break;
		
		case "DTSG_Graf_Sheffild_23":
			dialog.text = "Ascoltami bene, amico mio. E ascolta con attenzione. Il nostro mestiere è pericoloso e duro, in tutti i sensi. Può succedere di tutto — una tragica svista, una coincidenza beffarda, o un vile tradimento.\nServire la corona non vuol dire solo caricare i cannoni, Charlie. Per chi comanda, significa prendere decisioni difficili. E per marinai come noi — portarle a termine.";
			link.l1 = "Ma che faremo se un giorno verseremo sangue innocente, Capitano? Quello peserà sulle nostre mani, sulla nostra coscienza.";
			link.l1.go = "DTSG_Graf_Sheffild_24";
		break;
		
		case "DTSG_Graf_Sheffild_24":
			dialog.text = "Allora il sangue ricadrà sulle loro mani tanto quanto sulle nostre, se non di più. Che questo ti dia sollievo. L'importante è che le nostre intenzioni erano nobili – eliminare il nemico della patria.\nOra dammi una mano, Charlie, dobbiamo ancora far sembrare che sia stato un attacco olandese.";
			link.l1 = "Sì, signore...";
			link.l1.go = "DTSG_Graf_Sheffild_25";
		break;
		
		case "DTSG_Graf_Sheffild_25":
			DialogExit();
			sld = GetCharacter(NPC_GenerateCharacter("DTSG_Kortni", "off_eng_5", "man", "man", 40, ENGLAND, -1, false, "quest"));
			sld.name = "Thomas";
			sld.lastname = "Lynch";
			sld.rank = 40;
			GiveItem2Character(sld, "blade_16");
			EquipCharacterByItem(sld, "blade_16");
			GiveItem2Character(sld, "pistol6");
			EquipCharacterByItem(sld, "pistol6");
			SetSelfSkill(sld, 100, 100, 100, 100, 100);
			LAi_SetHP(sld, 400.0, 400.0);
			FantomMakeCoolSailor(sld, SHIP_HIMERA, "Сhimera", CANNON_TYPE_CANNON_LBS20, 70, 70, 70);
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "Tireless");
			SetCharacterPerk(sld, "Gunman");
			SetCharacterPerk(sld, "GunProfessional");
			SetCharacterPerk(sld, "Sliding");
			SetCharacterPerk(sld, "HardHitter");
			SetCharacterPerk(sld, "SwordplayProfessional");
			SetCharacterPerk(sld, "ShipSpeedUp");
			SetCharacterPerk(sld, "ShipTurnRateUp");
			SetCharacterPerk(sld, "StormProfessional");
			SetCharacterPerk(sld, "WindCatcher");
			SetCharacterPerk(sld, "SailsMan");
			SetCharacterPerk(sld, "Doctor1");
			SetCharacterPerk(sld, "MusketsShoot");
			SetCharacterPerk(sld, "LongRangeGrappling");
			SetCharacterPerk(sld, "HullDamageUp");
			SetCharacterPerk(sld, "HullDamageUp");
			SetCharacterPerk(sld, "SailsDamageUp");
			SetCharacterPerk(sld, "CrewDamageUp");
			SetCharacterPerk(sld, "CriticalShoot");
			SetCharacterPerk(sld, "BasicCommerce");
			SetCharacterPerk(sld, "AdvancedCommerce");
			sld.Ship.Mode = "war";
			sld.alwaysEnemy = true;
			sld.Coastal_Captain = true;
			sld.AlwaysSandbankManeuver = true;
			sld.DontRansackCaptain = true;
			
			Group_FindOrCreateGroup("DTSG_KortniAttack");
			Group_SetType("DTSG_KortniAttack", "pirate");
			Group_AddCharacter("DTSG_KortniAttack", "DTSG_Kortni");

			Group_SetGroupCommander("DTSG_KortniAttack", "DTSG_Kortni");
			Group_SetTaskAttack("DTSG_KortniAttack", PLAYER_GROUP);
			Group_SetAddress("DTSG_KortniAttack", "Antigua", "Quest_Ships", "Quest_Ship_10");
			Group_LockTask("DTSG_KortniAttack");
			
			SetLaunchFrameFormParam("Present time", "DTSG_SegodnyaVremya", 0, 4.0);
			LaunchFrameForm();
		break;
		
		case "DTSG_Knippel_101":
			dialog.text = "Dunque, abbiamo lasciato false prove per far sembrare che fossero stati gli olandesi. Io e Richard non abbiamo mai più parlato di quel giorno.";
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				link.l1 = "Ebbene, ora molte cose tornano. Credo che dietro la morte di Richard ci sia un parente o un compare del Conte. Ma perché prendersela con te? Sei solo un cannoniere, quel giorno maledetto non hai preso alcuna decisione.";
				link.l1.go = "DTSG_Knippel_ZS_102";
				AddComplexLandExpToScill(50, 50, 50);
				Log_info("Experience bonus received");
			}
			else
			{
				link.l1 = "Già. Questa è una faccenda sporca, puzza da lontano. Forse qualcuno ha scoperto tutto e vuole vendicare il Conte. Ma davvero un solo cannonista vale tutto ’sto spreco? Denaro, mercenari, assoldare quei maledetti Sea Foxes... Non ci credo, Charlie.";
				link.l1.go = "DTSG_Knippel_NS_102";
			}
		break;
		
		case "DTSG_Knippel_ZS_102":
			dialog.text = "Forse questo tizio sta dando la caccia a tutti quelli dell'equipaggio di Richard. Che ne pensate, signore?";
			link.l1 = "Penso che dovremmo allontanarci da Antigua, e prima ce ne andiamo, meglio è.";
			link.l1.go = "DTSG_Knippel_103";
		break;
		
		case "DTSG_Knippel_NS_102":
			dialog.text = "Me lo sono chiesto anch’io, Capitano, ma ancora non ho trovato risposta.";
			link.l1 = "Merda. Qualcuno si avvicina. Avevo detto di non rompermi le scatole!";
			link.l1.go = "DTSG_Knippel_103";
		break;
		
		case "DTSG_Knippel_103":
			DialogExit();
			
			LAi_SetPlayerType(pchar);
			if (GetCharacterIndex("Helena") != -1 && CheckPassengerInCharacter(pchar, "Helena"))
			{
				sld = characterFromId("Helena");
				ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
				sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
				sld.dialog.currentnode = "DTSG_Helena_1";
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", 0, 0);
				break;
			}
			if (GetCharacterIndex("Tichingitu") != -1 && CheckPassengerInCharacter(pchar, "Tichingitu"))
			{
				sld = characterFromId("Tichingitu");
				ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
				sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
				sld.dialog.currentnode = "DTSG_Tichingitu_1";
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", 0, 0);
				break;
			}
			else
			{
				sld = GetCharacter(NPC_GenerateCharacter("Alonso", "Alonso", "man", "man", sti(pchar.rank), pchar.nation, 0, true, "soldier"));
				sld.name 	= "Alonso";
				sld.lastname = "";
				ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
				sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
				sld.dialog.currentnode = "DTSG_Alonso_1";
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", 0, 0);
				sld.location = "None";
			}
		break;
		
		case "DTSG_Helena_1":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				dialog.text = "Charles!..";
				link.l1 = "Che succede, Helen??";
				link.l1.go = "DTSG_Helena_2";
			}
			else
			{
				dialog.text = "Charles, ricordo che mi hai chiesto di non far entrare nessuno e di non disturbare te e Charlie, ma...";
				link.l1 = "... hai deciso di venire di persona. Va bene, va tutto bene, Helen.";
				link.l1.go = "DTSG_Helena_2";
			}
		break;
		
		case "DTSG_Helena_2":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				dialog.text = "Una nave da guerra inglese! È stata avvistata poco fa. All’inizio non ci ho fatto caso, ma ora ci raggiungerà da un momento all’altro! Non ho mai visto un vascello così veloce.";
				link.l1 = "Allora grazie per avermelo detto. Spero che ci sia tempo per prepararci prima che ci raggiunga. Helen, Charlie, ai posti di combattimento!";
				link.l1.go = "DTSG_GotovimsyKBitve";
			}
			else
			{
				dialog.text = "... potete continuare il vostro incontro segreto più tardi. Una nave da guerra inglese sta puntando dritta verso di noi. Pensavo fosse importante.";
				link.l1 = "Va bene, vado a dare un’occhiata. Grazie, Helen.";
				link.l1.go = "DTSG_GotovimsyKBitve";
			}
		break;
		
		case "DTSG_Tichingitu_1":
			dialog.text = "Capitano, una nave veloce si sta avvicinando a noi. Molto veloce. Gli spiriti mi sussurrano che i loro intenti sono malvagi.";
			link.l1 = "Grazie a te e agli spiriti per l'avvertimento. Preparatevi alla battaglia, per ogni evenienza. E riferisci questo messaggio agli altri da parte mia.";
			link.l1.go = "DTSG_GotovimsyKBitve";
		break;
		
		case "DTSG_Alonso_1":
			dialog.text = "Perdoni l'intrusione, Capitano, ma è cosa urgente.";
			link.l1 = "Oh, spero sia davvero importante, Alonso. Rapporta.";
			link.l1.go = "DTSG_Alonso_2";
		break;
		
		case "DTSG_Alonso_2":
			dialog.text = "Una nave inglese si avvicina. È... la 'Mirage', Capitano.";
			link.l1 = "Cosa? Ne sei proprio sicuro? Hai di nuovo alzato il gomito, eh?";
			link.l1.go = "DTSG_Alonso_3";
		break;
		
		case "DTSG_Alonso_3":
			dialog.text = "Sicuro, Capitano – non c’è altra nave simile in tutti i Caraibi, lo sapete bene.";
			link.l1 = "Già. Vado io stesso a dare un’occhiata – vediamo se questa ‘Miraggio’ esiste davvero.";
			link.l1.go = "DTSG_GotovimsyKBitve";
		break;
		
		case "DTSG_GotovimsyKBitve":
			DialogExit();
			AddQuestRecord("DTSG", "17");
			
			if (GetCharacterIndex("Helena") != -1 && CheckPassengerInCharacter(pchar, "Helena"))
			{
				sld = characterFromId("Helena");
				LAi_SetOfficerType(sld);
				sld.Dialog.Filename = "Quest\Saga\Helena.c";
				sld.Dialog.CurrentNode = "Helena_officer";
			}
			if (GetCharacterIndex("Tichingitu") != -1 && CheckPassengerInCharacter(pchar, "Tichingitu"))
			{
				sld = characterFromId("Tichingitu");
				LAi_SetOfficerType(sld);
				sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
				sld.Dialog.CurrentNode = "Tichingitu_officer";
			}
			if (GetCharacterIndex("Knippel") != -1 && CheckPassengerInCharacter(pchar, "Knippel"))
			{
				sld = characterFromId("Knippel");
				LAi_SetOfficerType(sld);
				sld.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
				sld.Dialog.CurrentNode = "Knippel_officer";
			}
			
			PChar.quest.DTSG_KortniPotopil.win_condition.l1 = "Character_sink";
			PChar.quest.DTSG_KortniPotopil.win_condition.l1.character = "DTSG_Kortni";
			PChar.quest.DTSG_KortniPotopil.win_condition = "DTSG_KortniPotopil";
			
			chrDisableReloadToLocation = false;
			bDisableCharacterMenu = false;
			InterfaceStates.Buttons.Save.enable = true;
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			DeleteAttribute(pchar, "GenQuest.CannotWait");
		break;
		
		case "DTSG_Kortni":
			dialog.text = "Oh... Ma non è ancora finita! Brian, eccoti! Dove diavolo sei stato?";
			link.l1 = "Questo non farà che rimandare l’inevitabile.";
			link.l1.go = "DTSG_Kortni_Pikar";
		break;
		
		case "DTSG_Kortni_Pikar":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			LAi_SetWarriorType(npchar);
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetCheckMinHP(npchar, 10, true, "DTSG_KortniRanen");
			LAi_SetImmortal(npchar, false);
			
			sld = GetCharacter(NPC_GenerateCharacter("DTSG_Mrt_Rocur", "citiz_8", "man", "man", sti(pchar.rank), ENGLAND, -1, false, "soldier"));
			sld.name = "Brian";
			sld.lastname = "Tasse";
			GiveItem2Character(sld, "blade_20");
			EquipCharacterByItem(sld, "blade_20");
			GiveItem2Character(sld, "pistol5");
			EquipCharacterByItem(sld, "pistol5");
			AddItems(sld, "purse2", 1);
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
			LAi_SetHP(sld, 300.0, 300.0);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetCheckMinHP(sld, 10, true, "DTSG_PikarRanen");
			sld.location = "None";
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		break;
		
		case "DTSG_Kortni_1":
			dialog.text = "Charles de Maure. Pensare fin dove sei arrivato. Peccato. Speravo di coglierti di sorpresa su questa nave.";
			link.l1 = "Sai chi sono io? Dunque, sei tu la causa dei nostri guai recenti – sembri un uccellaccio di rango costretto a lasciare il suo nido caldo e a sporcarsi le mani di persona, invece di mandare un altro avvoltoio.";
			link.l1.go = "DTSG_Kortni_2";
			
			Island_SetReloadEnableGlobal("Antigua", true);
			bQuestDisableMapEnter = false;
			LAi_LocationDisableOfficersGen("SentJons_town", false);
			DeleteQuestCondition("DTSG_KortniPotopil");
		break;
		
		case "DTSG_Kortni_2":
			dialog.text = "Esatto, su entrambi i fronti. Suppongo che un gentiluomo sappia riconoscerne un altro anche da lontano. Colonnello Thomas Lynch. Pare sia giunta l’ora di parlarci come uomini d’onore, invece di tentare di farci a pezzi. Forse potremmo giungere a un accordo vantaggioso per entrambi.";
			link.l1 = "Non posso promettere nulla, ma ti do la mia parola d’onore che almeno parleremo da gentiluomini, colonnello.";
			link.l1.go = "DTSG_Kortni_3";
		break;
		
		case "DTSG_Kortni_3":
			dialog.text = "Molto bene. Una conversazione del genere con Fleetwood sarebbe stata impossibile. Eppure, abbiamo trovato il modo di tenerlo a bada, e non ci darà più fastidio. Peccato che tra noi non sia andata come speravo, ma pazienza.";
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				link.l1 = "Tutti i Caraibi parlano della morte di Richard. Allora, sei stato tu! E immagino che il vantaggio di cui parlavi fosse Abigail, giusto? Che fine ha fatto lei, a proposito?";
				AddComplexLandExpToScill(50, 50, 50);
				Log_info("Experience bonus received");
			}
			else
			{
				link.l1 = "Non una minaccia, dici?.. Allora l’hai fatto fuori? Sei forse un leccapiedi del conte?";
			}
			link.l1.go = "DTSG_Kortni_4";
		break;
		
		case "DTSG_Kortni_4":
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				dialog.text = "Abigail? Ah, la giovane ebrea, la sua promessa sposa. Ancora una volta, hai dimostrato d’avere un occhio di falco. Sta viva e in salute – era la nostra parola, e l’abbiamo mantenuta in cambio della collaborazione di Fleetwood.";
				link.l1 = "Che bella intesa, devo dire. Ma perché l’hai fatto? Sei forse un sostenitore del Conte?";
			}
			else
			{
				dialog.text = "Sostenitore? Ah, tutt'altro. Ma vedi, certe carte non si possono più giocare quando iniziano a pesare troppo sul mazzo del giocatore. Purtroppo, Richard è diventato proprio una di quelle.";
				link.l1 = "Capisco. Fai sparire tutti i testimoni. Che ne è stato di Abigail? Hai fatto fuori anche lei?";
			}
			link.l1.go = "DTSG_Kortni_5";
		break;
		
		case "DTSG_Kortni_5":
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				dialog.text = "Affatto. Anzi, proprio il contrario. Ma Richard sapeva fin troppo, e tornando nel Vecchio Mondo, è diventato una minaccia. Sarebbe dovuto restare qui, e non avremmo avuto bisogno di togliergli la vita.";
				link.l1 = "Ammazzi forse tutti quelli che hanno mai servito sotto i tuoi ordini, Colonnello?";
			}
			else
			{
				dialog.text = "Chi? Ah, la sua promessa sposa, immagino. Era lei la chiave. La sua vita in cambio della sua. Sta bene, lo giuro sul mio onore.";
				link.l1 = "Dubito che tu sappia cos’è l’onore, visto ciò che hai combinato, colonnello.";
			}
			link.l1.go = "DTSG_Kortni_6";
		break;
		
		case "DTSG_Kortni_6":
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				dialog.text = "Non risponderò a questa provocazione, signore.";
				link.l1 = "Allora rispondi a questo – come hai messo le mani su questa nave? È... la ‘Mirage’?";
			}
			else
			{
				dialog.text = "Chiuderò un occhio su quest'insulto, visto che viene da chi non ha mai dovuto brandire il potere né muovere le fila dell’ordine delle cose.";
				link.l1 = "A proposito, dove hai rimediato la 'Mirage'? È lei, questa?";
			}
			link.l1.go = "DTSG_Kortni_7";
		break;
		
		case "DTSG_Kortni_7":
			dialog.text = "Non proprio. Una nave magnifica, eh? Peccato che non abbia compiuto il suo dovere contro di voi. Conoscete la storia di questa nave, Capitano de Maure?";
			link.l1 = "Intendi la nave fantasma e la caccia ai mercanti inglesi?";
			link.l1.go = "DTSG_Kortni_8";
		break;
		
		case "DTSG_Kortni_8":
			dialog.text = "Quella? Oh, no. Non parlo di cose note a tutti. Intendo quelle che restano celate agli occhi. Questo ketch fu progettato da Johan van Merden e Lucas Rodenburg.\nQuella bella coppia ha tessuto una rete di intrighi e, alla fine, la nave fu varata dal cantiere di L'Avana. Siamo stati fortunati a mettere le mani sui piani originali. Alla fine, abbiamo ricreato la Mirage in tutto il suo splendore, migliorandola persino e correggendo qualche difetto del progetto.";
			link.l1 = "Peccato, come tu stesso hai notato, non ti è servito a granché, colonnello.";
			link.l1.go = "DTSG_Kortni_9";
		break;
		
		case "DTSG_Kortni_9":
			dialog.text = "Ti senti di ridere? Non farlo. Ammetto che mi hai superato sia come capitano che come combattente. Ma qui, la mano vincente ce l’ho ancora io.";
			link.l1 = "È forse una spacconata da moribondo? O solo la solita tracotanza di gente come te? Che cosa si cela dietro queste parole?";
			link.l1.go = "DTSG_Kortni_10";
		break;
		
		case "DTSG_Kortni_10":
			dialog.text = "Domanda eccellente. A quanto pare sei ben più di uno sbruffone di taverna e spadaccino, come mi dicevano le voci. Ho preso precauzioni per ogni possibile esito di questo incontro. Persino quello in cui finisco con la gola tagliata, un proiettile in petto o fatto a pezzi da una palla di cannone vagante. Se oggi sarà la mia fine, tu e Charlie vi pentirete amaramente di non avervi schierato con Fleetwood.";
			link.l1 = "Altri cacciatori di taglie? Bah. Fu spiacevole e noioso, ma non mortale. Li abbiamo scacciati allora – li spazzeremo via di nuovo.";
			link.l1.go = "DTSG_Kortni_11";
		break;
		
		case "DTSG_Kortni_11":
			dialog.text = "Non ho alcun dubbio. Ora rivedo il duellante spensierato che parla di nuovo. Non solo cacciatori di taglie. L’intera furia delle Volpi di Mare e l’intelligence navale inglese ti piomberà addosso come un’onda di tempesta sulla barca d’un pescatore.";
			link.l1 = "Cosa vuoi da me? Non penserai mica che mi arrenda?";
			link.l1.go = "DTSG_Kortni_12";
		break;
		
		case "DTSG_Kortni_12":
			dialog.text = "Ma certo che no. In tutto questo tempo ti abbiamo osservato bene. Voglio proporti un accordo che tornerà a vantaggio di entrambi. Rifiutarlo sarebbe da stolti. E da veri gentiluomini, spero troveremo un’intesa.";
			link.l1 = "Allora ripeto la domanda, Colonnello, che volete da me? Immagino che si tratti di Charlie?.. E pensate di potermi offrire qualcosa in cambio? Non tradirò per due monete d’oro.";
			link.l1.go = "DTSG_Kortni_13";
		break;
		
		case "DTSG_Kortni_13":
			dialog.text = "Giusto di nuovo. Non si tratta solo di qualche moneta d’oro, come dici tu, ma di una montagna intera – diecimila dobloni. L’anticipo ti aspetterà dal banchiere a Port Royal, se troviamo un accordo. Ma la cosa più importante che offro è la tua vita, Capitano de Maure. Hai capito bene. Cesseremo ogni inseguimento se deporremo le armi ora e ci consegnerai Charlie. Hai mai sentito dire ‘l’uomo contro la società’? Nel tuo caso, se rifiuti, sarà ‘l’uomo contro la corona’. Decidi, Charles. Qui e ora.";
			link.l1 = "Puoi pure sbandierare il tuo titolo e la tua influenza per spaventare qualche allocco. Ma io non sono uno sprovveduto. E sento la disperazione da un miglio di distanza. Fuori dai piedi. E ringrazia che non ti abbia fatto saltare le cervella – te lo saresti meritato tutto.";
			link.l1.go = "DTSG_Kortni_PkCh_1";
			link.l2 = "Non hai davvero bisogno di Charlie, Colonnello. Ti serve solo il suo silenzio.";
			link.l2.go = "DTSG_Kortni_LT_1";
			link.l3 = "Acconsento a questo per la sicurezza mia e dei miei uomini, non perché abbia fame del tuo denaro, che sia chiaro.";
			link.l3.go = "DTSG_Kortni_Sdat";
		break;
		
		case "DTSG_Kortni_PkCh_1":
			dialog.text = "Hai preso una delle decisioni peggiori della tua vita, Capitano de Maure. Non ti invidio, davvero. Potrai solo biasimare te stesso – nessuno ti farà più simili proposte. Soprattutto io. Addio.";
			link.l1 = "Aspetta, Colonnello.";
			link.l1.go = "DTSG_Kortni_PkCh_2";
		break;
		
		case "DTSG_Kortni_PkCh_2":
			dialog.text = "Che, hai cambiato idea? Le mie parole ti hanno fatto effetto, alla fine?";
			link.l1 = "Giusto, proprio il contrario.";
			link.l1.go = "DTSG_Kortni_PkCh_3";
		break;
		
		case "DTSG_Kortni_PkCh_3":
			dialog.text = "Cosa intendi? Spiegati.";
			link.l1 = "Le tue parole non hanno fatto che rafforzare la mia decisione contro di te. Non guardarmi così – non ti ammazzerò. E, come ti ho detto, ti lascerò pure andare. Ma penso che potrai cavartela anche senza una barca.";
			link.l1.go = "DTSG_Kortni_PkCh_4";
		break;
		
		case "DTSG_Kortni_PkCh_4":
			dialog.text = "Non mi serve, dato che ho già una nave.";
			link.l1 = "Hai ragione. Ma solo sul fatto che non mi serve. Magari sei un uomo di peso, ma ti manca il senso della misura. E il tatto, dannazione. Farò come sei abituato tu: prendo io il timone, stavolta.";
			link.l1.go = "DTSG_Kortni_PkCh_5";
		break;
		
		case "DTSG_Kortni_PkCh_5":
			dialog.text = "Non sei così, Capitano de Maure. Non ingannarti da solo.";
			link.l1 = "Completamente? Forse no. Ma nemmeno tu lo sei – la tua vita ora è nelle mie mani, Colonnello. Non importa cosa mi capiterà dopo – ora posso fare ciò che voglio. E io... prendo questa nave. Sei libero. La costa non è lontana.";
			link.l1.go = "DTSG_Kortni_PkCh_6";
		break;
		
		case "DTSG_Kortni_PkCh_6":
			dialog.text = "Non ne avresti il coraggio. Ma a giudicare dal tuo sguardo... Goditi questa tua piccola vittoria. Hai fatto...";
			link.l1 = "Sì, sì, una delle peggiori decisioni della mia vita. L’ho già sentita questa storia. Fuori da questa nave. La mia nave. Ti butti da solo, o vuoi che ti scaraventiamo in mare?";
			link.l1.go = "DTSG_Kortni_PkCh_7";
		break;
		
		case "DTSG_Kortni_PkCh_7":
			DialogExit();
			
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "goto", "goto4", "", "", "", "DTSG_Kortni_Vyprygnul", 7);
			npchar.lifeday = 0;
			npchar.location = "None";
		break;
		
		case "DTSG_Kortni_PkCh_8":
			dialog.text = "Mai avrei pensato di vederlo così – umiliato, a saltar giù dalla finestra e a nuotare verso la riva a quattro zampe.";
			link.l1 = "Hai dato un'occhiata? Contento? Splendido. Ora tocca a te.";
			link.l1.go = "DTSG_Kortni_PkCh_9";
		break;
		
		case "DTSG_Kortni_PkCh_9":
			dialog.text = "What are you saying, sir? We're not enemies; I was just following orders!.. Can I at least ask for a boat? You'll never see me again!";
			link.l1 = "Non mi avresti risparmiato al posto mio, dopo aver perso una battaglia contro di te. Quindi ringrazia che non ti ho fatto fuori. Fuori dalla finestra. Ora. Magari raggiungi il tuo protettore.";
			link.l1.go = "DTSG_Kortni_PkCh_10";
		break;
		
		case "DTSG_Kortni_PkCh_10":
			dialog.text = "Preferirei crepare piuttosto che subire un simile affronto, monsieur!";
			link.l1 = "Come desideri.";
			link.l1.go = "DTSG_Kortni_PkCh_11";
		break;
		
		case "DTSG_Kortni_PkCh_11":
			DialogExit();
			
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			LAi_RemoveCheckMinHP(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_Kortni_Vyprygnul_3");
		break;
		
		case "DTSG_Kortni_PkCh_12":
			dialog.text = "Quello era il Colonnello, giusto, Capitano?";
			link.l1 = "D'accordo. Guarda fuori dalla finestra, Charlie, non te ne pentirai.";
			link.l1.go = "DTSG_Kortni_PkCh_13";
		break;
		
		case "DTSG_Kortni_PkCh_13":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto4", "DTSG_Kortni_Vyprygnul_5", 6);
		break;
		
		case "DTSG_Kortni_PkCh_14":
			dialog.text = "Il colonnello?.. Mai avrei pensato di vedere una cosa simile, signore. Che qualcuno osasse gettare in mare un uomo con un titolo così, come fosse un semplice mozzo! Richard non l’avrebbe mai fatto – il rispetto per il grado era la sua legge sacra.";
			link.l1 = "Gliel'hanno martellato in testa con anni di addestramento. È un uomo di guerra, con la testa fatta così. Io no, vedo le cose più in grande, senza... quei paraocchi.";
			link.l1.go = "DTSG_Kortni_PkCh_15";
		break;
		
		case "DTSG_Kortni_PkCh_15":
			dialog.text = "E non ci cacceranno nei guai per averlo conciato così, eh?";
			link.l1 = "Heh, accusi Richard, ma ragioni come lui. Abbiamo osato ribellarci, quindi ci daranno la caccia per un po'. Ma prima o poi, persino la marina inglese si stuferà di inseguirci. E per Lynch, diventerà una faccenda personale. Ma ci siamo assicurati che la prossima volta non avrà la flotta di Sua Maestà alle spalle.";
			link.l1.go = "DTSG_Kortni_PkCh_16";
		break;
		
		case "DTSG_Kortni_PkCh_16":
			dialog.text = "Sai, Capitano, da oggi ti rispetto ancora di più. Non rimpiangerò mai di non essere partito con Dick sulla Valkyrie e di aver scelto di seguirti.";
			link.l1 = "Grazie, compare! Preparati – la burrasca s’avvicina. Ma sai che ti dico? Qualcosa mi dice che la vittoria sarà ancora nostra. Andiamo, è ora di tornare sul ponte.";
			link.l1.go = "DTSG_Kortni_PkCh_17";
		break;
		
		case "DTSG_Kortni_PkCh_17":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			
			DoQuestCheckDelay("DTSG_Kortni_Vyprygnul_7", 3.0);
			Achievment_Set("ach_CL_114");
		break;
		
		case "DTSG_Kortni_LT_1":
			dialog.text = "Non è proprio così, anche se a dire il vero, di Charlie me ne importa poco, purché tenga la bocca chiusa d’ora in poi. Ma i miei compari vogliono vedere il suo cadavere. E sanno bene che faccia abbia.\nQuesta è la vita vera, Charles, non una fiaba per marmocchi o una poesia da cavaliere che ci leggevano le balie quando eravamo piccoli, e io non vedo una soluzione che piaccia a tutti.";
			link.l1 = "Ma io sì. Un cadavere si trova sempre, abiti simili pure, basta ungere qualche ruota. Parlerò con Charlie. E ti do la mia parola d’onore come garanzia.";
			link.l1.go = "DTSG_Kortni_LT_2";
		break;
		
		case "DTSG_Kortni_LT_2":
			if (sti(pchar.reputation.nobility) > 70)
			{
				notification("Reputation Check Passed", "None");
				dialog.text = "È... un rischio bello grosso. E non si tratta solo del fatto che possa fidarmi della tua parola. Ma anche se i miei compagni crederanno a quel che vedranno, quando troveranno un corpo che somiglia a quello di Charlie. E io, quel rischio... non lo correrò così, alla leggera.";
				link.l1 = "Quanto vuoi?";
				link.l1.go = "DTSG_Kortni_LT_4";
			}
			else
			{
				notification("Reputation Too Low! ("+XI_ConvertString(GetReputationName(71))+")", "None");
				dialog.text = "La parola di un uomo con la tua reputazione? Mi prendi in giro. Avere sangue nobile non basta a meritarsi fiducia.";
				link.l1 = "Sentirlo dire da un altro uomo con nascita e gesta simili, perdonatemi, Colonnello.";
				link.l1.go = "DTSG_Kortni_LT_3";
			}
		break;
		
		case "DTSG_Kortni_LT_3":
			dialog.text = "Hai ragione, ovviamente. Ma stavolta si tratta della mia fiducia, non di quella degli altri. E tu come garante non mi vai bene\nTe lo dico per l’ultima volta. Dammi Charlie. A meno che tu non voglia seguire la stessa sorte di Fleetwood.";
			link.l1 = "Con il tuo titolo e la tua influenza puoi spaventare qualche povero idiota. Ma io non sono uno di quelli. E sento la disperazione lontano un miglio. Fuori dai piedi. Ringrazia il cielo che non ti ho mandato all'altro mondo – te lo saresti meritato tutto.";
			link.l1.go = "DTSG_Kortni_PkCh_1";
		break;
		
		case "DTSG_Kortni_LT_4":
			dialog.text = "Finalmente, al sodo. Un milione di pesos. Ultima offerta.";
			if (sti(pchar.Money) >= 1000000)
			{
				link.l1 = "Ti darò il denaro. Non pensare che sia un pezzente o che non tenga alla vita dei miei uomini. Non è affatto così. Prendilo.";
				link.l1.go = "DTSG_Kortni_LT_7";
			}
			else
			{
				link.l1 = "Hai un bell'appetito, anche se non mi sorprende. Ma al momento, io non ho poi così tanto, e...";
				link.l1.go = "DTSG_Kortni_LT_5";
			}
		break;
		
		case "DTSG_Kortni_LT_5":
			dialog.text = "Niente argento, niente accordo. Credevi che avrei avuto pietà? Ti sembro forse un santo, signore?";
			link.l1 = "Ma forse potresti aspettare un po'? Dove e quando ti farebbe comodo rivederci? Potrei prendere in prestito i dobloni da un usuraio.";
			link.l1.go = "DTSG_Kortni_LT_6";
		break;
		
		case "DTSG_Kortni_LT_6":
			dialog.text = "Allora mi credi ancor più ingenua di quanto pensassi\nNon sono una ragazzetta di campagna pronta ad aspettare in eterno qualcuno che una volta l’ha avuta vinta con lei\nNiente soldi? Non li ho mai chiesti. Voglio solo Charlie. Tu non mi servi a nulla, con tutti i guai che hai portato.";
			link.l1 = "Puoi pure sfruttare il tuo titolo e l’influenza per spaventare uno o due sciocchi. Ma io non sono uno sprovveduto. E il tanfo della disperazione lo sento da leghe lontano. Fuori dai piedi. E ringrazia che non ti ho fatto saltare le cervella – te lo saresti ampiamente meritato.";
			link.l1.go = "DTSG_Kortni_PkCh_1";
		break;
		
		case "DTSG_Kortni_LT_7":
			dialog.text = "Ti sei davvero affezionato al povero Charlie? Ad ogni modo, la tua lealtà merita rispetto. Fa' in modo che il tuo cannoniere sia muto come una tomba. Altrimenti ci finirete tutti e due.";
			link.l1 = "Prometto. E tu mantieni la parola e lasci perdere ogni inseguimento.";
			link.l1.go = "DTSG_Kortni_LT_8";
			AddMoneyToCharacter(pchar, -1000000);
		break;
		
		case "DTSG_Kortni_LT_8":
			dialog.text = "Lo prometto anch'io. E un'altra cosa. Nonostante la tua vittoria leale, la mia nave la porto via con me. È fatta su misura, sai. E vale un occhio della testa.";
			link.l1 = "E che ne dici del diritto del vincitore? Ma non tenterò troppo la sorte. Stavolta.";
			link.l1.go = "DTSG_Kortni_LT_9";
		break;
		
		case "DTSG_Kortni_LT_9":
			DialogExit();
			
			LAi_Fade("DTSG_Kortni_Otkup_1", "");
		break;
		
		case "DTSG_Kortni_LT_10":
			dialog.text = "Mi rincresce quasi dirlo, Brian, ma temo che la nostra collaborazione finisca qui.";
			link.l1 = "...";
			link.l1.go = "DTSG_Kortni_LT_11";
			CharacterTurnToLoc(npchar, "rld", "aloc0");
		break;
		case "DTSG_Kortni_LT_11":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("DTSG_Mrt_Rocur");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_12";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Kortni_LT_12":
			dialog.text = "Io... sono libero, Colonnello? Toglierai la taglia dalla mia testa, così potrò ricominciare da capo come un uomo onesto?";
			link.l1 = "...";
			link.l1.go = "DTSG_Kortni_LT_13";
			CharacterTurnToLoc(npchar, "rld", "loc0");
		break;
		case "DTSG_Kortni_LT_13":
			DialogExit();
			sld = CharacterFromID("DTSG_KortniClone");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_14";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Kortni_LT_14":
			dialog.text = "Direi che hai visto fin troppo – proprio come il povero Fleetwood. In pratica ho appena preso una bustarella davanti ai tuoi occhi.";
			link.l1 = "...";
			link.l1.go = "DTSG_Kortni_LT_15";
			CharacterTurnToLoc(npchar, "rld", "aloc0");
		break;
		case "DTSG_Kortni_LT_15":
			DialogExit();
			sld = CharacterFromID("DTSG_Mrt_Rocur");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_16";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Kortni_LT_16":
			dialog.text = "Io... io non dirò nulla a nessuno, lo giuro su Dio!";
			link.l1 = "...";
			link.l1.go = "DTSG_Kortni_LT_17";
			CharacterTurnToLoc(npchar, "rld", "loc0");
		break;
		case "DTSG_Kortni_LT_17":
			DialogExit();
			sld = CharacterFromID("DTSG_KortniClone");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_18";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Kortni_LT_18":
			dialog.text = "Ma certo che non lo farai.";
			link.l1 = "...";
			link.l1.go = "DTSG_Kortni_LT_19";
			CharacterTurnToLoc(npchar, "rld", "aloc0");
		break;
		case "DTSG_Kortni_LT_19":
			DialogExit();
			sld = CharacterFromID("DTSG_Mrt_Rocur");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_20";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Kortni_LT_20":
			dialog.text = "No!..";
			link.l1 = "...";
			link.l1.go = "DTSG_Kortni_LT_21";
			CharacterTurnToLoc(npchar, "rld", "loc0");
		break;
		case "DTSG_Kortni_LT_21":
			DialogExit();
			
			sld = CharacterFromID("DTSG_KortniClone");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Shot", "1", 1.8);
			DoQuestCheckDelay("DTSG_Kortni_Otkup_3", 0.9);
			
			LAi_SetActorType(NPChar);
			LAi_ActorAttack(NPChar, sld, "");
		break;
		
		case "DTSG_Kortni_LT_22":
			dialog.text = "Non guardarmi così, Charles. Se continuo a rimuginare se Brian finirà col vuotare il sacco, non chiuderò occhio manco per sbaglio.";
			link.l1 = "Non so nemmeno se dovrei stupirmi di ciò che ho visto oppure no.";
			link.l1.go = "DTSG_Kortni_LT_23";
		break;
		
		case "DTSG_Kortni_LT_23":
			dialog.text = "Non dovreste. Ho preso il mio impegno. Tutto ciò che vi chiedo, a voi due, è di tenere la bocca chiusa su quel che è successo. Cercherò un corpo simile, sistemerò per bene la faccia, userò saggiamente i soldi e convincerò i miei compari.";
			link.l1 = "Grazie, Colonnello.";
			link.l1.go = "DTSG_Kortni_LT_24";
		break;
		
		case "DTSG_Kortni_LT_24":
			dialog.text = "Non c'è ancora nulla per cui ringraziarmi. C'è sempre il rischio che non mi credano, e allora la caccia ricomincerà. Per ora, addio, Capitano de Maure. Salpo con la mia nave. Nessuna lamentela qui – ho già fatto un gran favore a te e a Charlie.";
			link.l1 = "Ebbene, addio allora.";
			link.l1.go = "DTSG_Kortni_LT_25";
			
			pchar.GenQuest.CannotTakeShip = true;
			PChar.quest.DTSG_Kortni_KechNeNash.win_condition.l1 = "MapEnter";
			PChar.quest.DTSG_Kortni_KechNeNash.win_condition = "DTSG_Kortni_KechNeNash";
		break;
		
		case "DTSG_Kortni_LT_25":
			DialogExit();
			
			//sld = CharacterFromID("Knippel");
			sld = GetCharacter(CreateCharacterClone(CharacterFromID("Knippel"), 0));
			sld.id = "KnippelClone";
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_26";
			ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
			LAi_SetActorType(pchar);
			LAi_SetActorType(sld);
			SetActorDialogAny2Pchar(sld.id, "", -1, 0.0);
			LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 2.0);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 2.0);
		break;
		
		case "DTSG_Kortni_LT_26":
			dialog.text = "Ma ti rendi conto con chi stavi parlando, Capitano? Un colonnello! È stato lui a muovere tutti questi fili, eh?";
			link.l1 = "Lo so, si è presentato da sé. E hai ragione – lo era davvero.";
			link.l1.go = "DTSG_Kortni_LT_27";
		break;
		
		case "DTSG_Kortni_LT_27":
			dialog.text = "È strano, signore, perché un tempo lo conoscevo come superiore di Richard. Com’è possibile, diavolo? E perché se ne va come se nulla fosse? Che cosa voleva davvero?";
			link.l1 = "In verità, non c’è nulla di strano in questo. Chi esegue ordini loschi rischia la vita non tanto per mano dei nemici, ma proprio per colpa dei suoi superiori. E lui voleva la tua testa, Charlie.";
			link.l1.go = "DTSG_Kortni_LT_28";
		break;
		
		case "DTSG_Kortni_LT_28":
			dialog.text = "Non capisco, Capitano. Perché allora se ne va? Ha forse gettato la spugna?";
			link.l1 = "Non è proprio da lui. Ho dovuto dargli dell’oro che pesava quasi quanto la tua zucca. Forse pure di più. Un milione di pesos, per esser precisi.";
			link.l1.go = "DTSG_Kortni_LT_29";
		break;
		
		case "DTSG_Kortni_LT_29":
			dialog.text = "E tu... gli hai dato tutta quella somma? Per me?..";
			link.l1 = "Beh, non solo per te. Anche per me stesso. E per tutti i ragazzi, pure. Ma sì, Charlie, soprattutto per te. Se l’avessimo fatto fuori, saremmo stati inseguiti da dannati spedizioni punitive fino alla fine dei nostri giorni.";
			link.l1.go = "DTSG_Kortni_LT_30";
		break;
		
		case "DTSG_Kortni_LT_30":
			dialog.text = "Non... ci posso credere, signore. Solo... grazie. Non pensavo che Fleetwood al tuo posto avrebbe fatto così.";
			link.l1 = "Sei troppo prevenuto contro di lui dopo la sua fuga. Richard voleva solo una vita tranquilla con Abigail. Mi dispiace che non gli sia andata bene. E poi, ha mantenuto la parola e saldato il tuo debito. Eh, io, Fleetwood... hai proprio fortuna coi capitani, eh, Charlie?";
			link.l1.go = "DTSG_Kortni_LT_31";
		break;
		
		case "DTSG_Kortni_LT_31":
			dialog.text = "Niente scherzi, Capitano. Allora, è tutto finito adesso?";
			link.l1 = "Sì, mio carissimo amico. Almeno per ora. La zuffa è finita – puoi dire ai ragazzi di mettere via le armi. E che si preparino a issare le vele.";
			link.l1.go = "DTSG_Kortni_LT_32";
		break;
		
		case "DTSG_Kortni_LT_32":
			DialogExit();
			
			InterfaceStates.Buttons.Save.enable = true;
			LAi_SetPlayerType(pchar);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			npchar.location = "None";
			
			AddQuestRecord("DTSG", "19");
			CloseQuestHeader("DTSG");
			LAi_ReloadBoarding();
			Achievment_Set("ach_CL_114");
			sld = CharacterFromID("Knippel");
			SetCharacterPerk(sld, "Bombardier");
			notification("Bombardier Unlocked", "Knippel");
		break;
		
		case "DTSG_Kortni_Sdat":
			dialog.text = "Non me ne frega un accidente del perché tu sia d’accordo – che sia per avidità, paura o dovere verso i tuoi uomini. Conta solo che tu lo sia. Manderò il mio uomo a Port Royal con istruzioni per il banchiere.";
			link.l1 = "Bene. Non posso credere che sia finalmente finita.";
			link.l1.go = "DTSG_Kortni_Dengi_1";
			link.l2 = "Sai che ti dico, al diavolo il denaro. Se ne può sempre scovare dell’altro. Voglio qualcos’altro da te in cambio di Charlie, colonnello.";
			link.l2.go = "DTSG_Kortni_Kech_1";
		break;
		
		case "DTSG_Kortni_Kech_1":
			dialog.text = "Oh? Devo ammetterlo, mi sorprendi, Capitano de Maure. E dimmi, secondo te, cosa potrebbe valere quanto la pelata d’un vecchio cannoniere, se nemmeno una montagna d’oro ti tenta?";
			link.l1 = "L’hai detto tu stesso – una nave magnifica, coi suoi difetti d’origine aggiustati. Non vedo l’ora di metterle le mani addosso. I progetti li hai ancora. Ma di Charlie ce n’è uno solo. E poi, ti conviene tenermi di buon umore.";
			link.l1.go = "DTSG_Kortni_Kech_2";
		break;
		
		case "DTSG_Kortni_Kech_2":
			if (IsCharacterPerkOn(pchar, "Trustworthy") && sti(pchar.reputation.nobility) > 70)
			{
				dialog.text = "Sei davvero un osso duro nelle trattative. Hai almeno un'idea di quanto ci sia costato costruire anche solo uno di questi?";
				link.l1 = "(Fidato) (Onore) Lo so fin troppo bene, ecco perché te lo chiedo. Hai la mano tra le mie fauci fino al gomito. Puoi anche provare a sparare a questo lupo. Ma ci rimetterai la mano. E non solo quella.";
			}
			else
			{
				dialog.text = "Temo che costruirne uno di questi costi ben più dell’oro che abbiamo messo da parte per te. Ma mi hai strappato un sorriso, Charles. In senso buono.";
				link.l1 = "Valeva la pena tentare.";
				if (!IsCharacterPerkOn(pchar, "Trustworthy")) notification("Perk Check Failed", "Trustworthy");
				if (sti(pchar.reputation.nobility) < 71) notification("Reputation Too Low! ("+XI_ConvertString(GetReputationName(71))+")", "None");
			}
			link.l1.go = "DTSG_Kortni_Kech_3";
		break;
		
		case "DTSG_Kortni_Kech_3":
			if (IsCharacterPerkOn(pchar, "Trustworthy") && sti(pchar.reputation.nobility) > 70)
			{
				dialog.text = "Vedo che sai quello che vuoi e insegui le tue mete nella vita\nE va bene. Il ketch è tuo. Ma scordati i soldi – l’usuraio farà finta di non saper nulla.";
				link.l1 = "Mi sta bene.";
				link.l1.go = "DTSG_Kortni_Kech_4";
				pchar.questTemp.DTSG_Kech = true;
			}
			else
			{
				dialog.text = "Senza dubbio. La mia vita è stata tutta un cogliere occasioni e mettermi al riparo dai pericoli\nPorta qui Charlie, e ci separeremo senza rancori. Dopo, puoi pure tenerti l’anticipo. Ma io me ne vado su questa nave.";
				link.l1 = "Allora sistemiamola una volta per tutte.";
				link.l1.go = "DTSG_Kortni_VizyvaemKnippel";
				pchar.questTemp.DTSG_depozit = true;
			}
		break;
		
		case "DTSG_Kortni_Kech_4":
			dialog.text = "Non posso dire d'essere del tutto soddisfatto. Ma voglio chiuderla in fretta. Adesso dammi quel che m'è dovuto.";
			link.l1 = "Non 'cosa', ma 'chi'. Ma come preferisci.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel";
		break;
		
		case "DTSG_Kortni_Dengi_1":
			dialog.text = "Nemmeno io posso. Comincio a pensare che non conta solo ciò che un uomo è, ma chi si tiene vicino – un semplice lavoro, acchiappare un vecchio artigliere, è diventato un mal di testa per colpa del suo capitano, cioè te, Charles.\nChiama qui Charlie. Questa faccenda finirà una volta per tutte – salperemo l’ancora, e le nostre navi prenderanno rotte diverse.";
			link.l1 = "Andarsene, dici?";
			link.l1.go = "DTSG_Kortni_Dengi_2";
		break;
		
		case "DTSG_Kortni_Dengi_2":
			dialog.text = "Sembri sorpreso? Credevi che il ketch fosse un premio legittimo, eh? Noi non siamo filibustieri, capitano de Maure. La gente civile segue regole ben più contorte e raffinate. La nave resta con me.";
			link.l1 = "Ebbene allora...";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel";
			pchar.questTemp.DTSG_depozit = true;
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel":
			DialogExit();
			
			//sld = CharacterFromID("Knippel");
			sld = GetCharacter(CreateCharacterClone(CharacterFromID("Knippel"), 0));
			sld.id = "KnippelClone";
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_VizyvaemKnippel_2";
			ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_2":
			dialog.text = "State bene, signore? Quello... è il colonnello?";
			link.l1 = "Sì, Charlie, è il colonnello. Sei arrivato proprio in tempo – stavo per venire a cercarti di persona.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_3";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_3":
			dialog.text = "Portarmi qui, Capitano?.. Proprio adesso? Perché mai hai sprecato tanto fiato con questo... individuo? Ho pensato che fossi nei guai, così sono venuto io stesso.";
			link.l1 = "Esatto. Siamo ancora nei guai, nonostante la vittoria. E lo saremmo tuttora, se il colonnello ed io non avessimo trovato una via d’uscita.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_4";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_4":
			dialog.text = "Siete riuscito a convincerlo a lasciarci in pace, signore?";
			link.l1 = "Purtroppo, solo io. Non noi. Tu... andrai con lui, Charlie.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_5";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_5":
			dialog.text = "Cosa?.. Ma perché?.. Abbiamo vinto!";
			link.l1 = "Non capisci? Non possiamo vincere sempre – non si fermeranno finché non avranno la tua testa.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_6";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_6":
			dialog.text = "Non posso credere che tu lo stia facendo al vecchio Charlie, Capitano. Sei proprio come quel bastardo di Dick. Entrambi mi avete giurato amicizia, e ora mi lasciate solo, come tutti quelli a cui tenevo.";
			link.l1 = "Questo è il peso che grava sulle spalle di un capitano, è la sua responsabilità. Vedo che non puoi comprenderlo, perché tutto ciò che hai mai fatto è stato caricare i cannoni con le palle.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_7";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_7":
			dialog.text = "Non capisci?.. Forse perché non sono un traditore come te? Sai dove dovresti andare?";
			link.l1 = "All’Inferno? Forse hai ragione. Ce lo siamo meritati, tutti quanti.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_8";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_8":
			dialog.text = "Vaffà, signore.";
			link.l1 = "...";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_9";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_9":
			DialogExit();
			
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_VizyvaemKnippel_10";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			
			sld = CharacterFromID("KnippelClone");
			LAi_SetActorType(sld);
			sld = CharacterFromID("Knippel");
			RemovePassenger(pchar, sld);
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_10":
			dialog.text = "Divertente, davvero. Mi hai quasi strappato una risata. L’hai sentito, Brian?\nA volte ascoltare la ciurma sembra una brezza, invece che una seccatura. Hai preso la decisione giusta, Charles. Capisco quanto ti pesa. Ma consola il fatto che né tu né i tuoi uomini patirete adesso.";
			link.l1 = "Spero che tu mantenga questa promessa, Colonnello.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_11";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_11":
			dialog.text = "Sono un uomo di parola. Il destino di Abigail lo dimostra. Guarda anche Brian. Un pirata francese, sì, ma ha scelto la parte giusta quando era il momento. E finché ci serve lealmente, nessuno gli torce un capello. Proprio come lui, anche tu stai navigando verso il porto giusto, Capitano de Maure.";
			if (CheckAttribute(pchar, "questTemp.DTSG_Kech"))
			{
				link.l1 = "A proposito di muoversi. Voglio levarmi dai piedi il prima possibile. Su questa nave, senza dubbio veloce, che mi hai promesso, Colonnello.";
			}
			else
			{
				link.l1 = "Non sono un pirata. E non ho intenzione di arruolarmi nella flotta inglese, almeno per ora. Ma il premio che mi spetta, quello intendo reclamarlo.";
			}
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_12";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_12":
			if (CheckAttribute(pchar, "questTemp.DTSG_Kech"))
			{
				dialog.text = "I won't hide it - it feels like tearing her from my heart. I'll have to spend on a new one, but perhaps it's worth it - too long have I been troubled by the thought that Charlie might spill the beans\nIf you don't talk or commit serious crimes against England, consider that we're no longer enemies. Enjoy the new ship; she's indeed beautiful. Goodbye, Charles. Brian - prepare a boat for us. Charlie - follow me as you have no say in the matter.";
				link.l1 = "Addio. A tutti voi.";
				link.l1.go = "DTSG_Kortni_VizyvaemKnippel_13";
			}
			else
			{
				dialog.text = "Peccato, gente sveglia serve sempre, qualunque sia la loro bandiera. Ma la tua ricompensa te la sei guadagnata. Vai pure tranquillo a Port Royal – arriverò prima io di qualunque altro vascello su questo cutter.";
				link.l1 = "Spero anch’io. E spero pure di non trovare una scorta armata ad attendermi a Port Royal.";
				link.l1.go = "DTSG_Kortni_VizyvaemKnippel_14";
			}
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_13":
			DialogExit();
			
			AddQuestRecord("DTSG", "20");
			CloseQuestHeader("DTSG");
			ChangeOfficersLoyality("bad_all", 5);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			ChangeCharacterComplexReputation(pchar, "fame", -10);
			AddCrewMorale(Pchar, -10);
			LAi_ReloadBoarding();
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_14":
			dialog.text = "Metti di nuovo in dubbio la mia parola? Vergogna su di te. Ti sei guadagnato la riconoscenza di tutta la marina inglese. Se mai avrai bisogno di qualcosa, o deciderai d’arruolarti tra noi, cercami pure, Capitano de Maure.";
			link.l1 = "Una volta ho provato a guadagnarmi il favore e i legami coi servizi segreti inglesi. Non è andata, ahimè. Addio, Colonnello.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_15";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_15":
			DialogExit();
			
			if (CheckAttribute(pchar, "questTemp.DTSG_depozit"))
			{
				ChangeCharacterNationReputation(pchar, ENGLAND, 30);
			}
			pchar.GenQuest.CannotTakeShip = true;
			PChar.quest.DTSG_Kortni_KechNeNash.win_condition.l1 = "MapEnter";
			PChar.quest.DTSG_Kortni_KechNeNash.win_condition = "DTSG_Kortni_KechNeNash";
			AddQuestRecord("DTSG", "21");
			CloseQuestHeader("DTSG");
			ChangeOfficersLoyality("bad_all", 5);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			ChangeCharacterComplexReputation(pchar, "fame", -10);
			AddCrewMorale(Pchar, -10);
			LAi_ReloadBoarding();
			Achievment_Set("ach_CL_114");
		break;
		
	}
} 

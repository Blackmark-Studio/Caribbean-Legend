// Ришард Шамбон - контрабандист
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	float locx, locy, locz;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "Non voglio parlare con te. Assalti civili innocenti senza motivo e li provochi alla rissa. Sparisci dai piedi!";
				link.l1 = "Uhm...";
				link.l1.go = "exit";
				break;
			}
			// --> кольцо
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "find" && CheckAttribute(npchar, "quest.answer_2") && GetNpcQuestPastDayParam(npchar, "quest_date") >= 3 && !CheckAttribute(npchar, "quest.ring"))
			{
				dialog.text = "Oh! Eccoti qua, compare. E pensare che stavo per venire a cercarti io stesso. Ho proprio bisogno di te, amico.";
				link.l1 = "Oggi sei stranamente cordiale, Richard. Va bene, ti ascolto.";
				link.l1.go = "ring";
				break;
			}
			// <-- кольцо
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Cosa vuoi? A dir la verità, oggi non sono proprio dell'umore giusto. Anzi, non ricordo nemmeno l'ultima volta che lo ero.";
				link.l1 = "È davvero così terribile, compare?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+"Vuoi qualcosa?";
				link.l1 = LinkRandPhrase("Hai qualcosa di curioso da raccontare?","È successo qualcosa di nuovo sull’isola?","Mi racconterai gli ultimi pettegolezzi?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Vorrei farti qualche domanda sull’isola.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Volevo solo sapere come te la passi. Ci si vede!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Cattivo? No, non direi cattivo. Semplicemente non ho l’umore giusto. Allora, che volevi?";
			link.l1 = "Volevo solo conoscerti. Sono appena arrivato su quest’isola, così passeggio un po’ per l’Isola Giustizia e cerco di fare conoscenza con la gente.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Davvero? Va bene allora. Sono Richard Shambon. Tanto tempo fa trafficavo in merce pregiata, e sì, qualcuno direbbe che non tutto era lecito... ma ormai da nove anni rovisto tra relitti, cerco ferraglia e la scambio per un tozzo di pane o un po’ d’oro.";
			link.l1 = "E io sono "+GetFullName(pchar)+", un capitano...";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Intendi l’ex capitano, eh eh?";
			link.l1 = "Beh, in realtà la mia nave è ormeggiata a Blueweld adesso. Sono arrivato qui su una tartana.";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Davvero? Impossibile! E dove si trova ora la tua tartana?";
			link.l1 = "Hm... in fondo.";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "A-ah... E pensare che... Bah, amico, meglio che mi versi un po’ di rum...";
			link.l1 = "Buona fortuna con questo. È stato un piacere chiacchierare con te. A presto!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Hai qualcosa di interessante da raccontare?","È successo qualcosa di nuovo sull'isola?","Mi racconterai gli ultimi pettegolezzi?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Vorrei farti qualche domanda sull'isola.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
		// Кольцо
		case "ring":
			dialog.text = "Ero forse diverso, prima? Suvvia, anche a me capitavano giornate nere, chi non ne ha? Senti un po', si mormora sull’Isola Giustizia che tu sia un combattente coi fiocchi. È vero?";
			link.l1 = "Non so che dicono, ma so bene come maneggiare una spada, se è questo che vuoi sapere.";
			link.l1.go = "ring_1";
			npchar.quest.ring = "true";
		break;
		
		case "ring_1":
			dialog.text = "Capisco. Pare che quelle chiacchiere fossero vere... Ascolta, "+pchar.name+", ti ricordi quando ti parlavo dell’anello esterno? E dei tesori preziosi che puoi scovare laggiù?";
			link.l1 = "Tutti voi amate parlare di quell’anello... E tutti dite le stesse cose.";
			link.l1.go = "ring_2";
		break;
		
		case "ring_2":
			dialog.text = "Cos'altro c'è da dire, ah-ah! Va bene. Vado al sodo. (abbassando la voce) Ho trovato una nave intatta all'anello esterno, è in buone condizioni, il che è cosa rara qui.\nLa nave è grossa, una pinaccia. È stata portata qui da poco, due mesi o forse meno. Gli altri ancora non l’hanno scovata, quindi c’è una bella possibilità di fare bottino saccheggiando stive e cabine.";
			link.l1 = "Bene, sono contento per te. Ma che c'entro io in tutto questo? Vuoi forse chiedermi di venirci insieme a te?";
			link.l1.go = "ring_3";
		break;
		
		case "ring_3":
			dialog.text = "Esatto! Ascolta. La prua della pinaccia è danneggiata. Quei dannati granchi hanno trovato una fessura per infilarsi dentro e ci hanno costruito il loro maledetto nido. Intrufolarsi là dentro mentre ci sono loro non si può, e non ho la minima idea di come salire al ponte superiore.\nNon sono mai stato un gran combattente e non tocco una lama da anni, quindi da solo non riuscirò certo ad ammazzare quelle bestiacce. È per questo che mi sono rivolto a te.";
			link.l1 = "Quindi mi suggerisci di ammazzare tutti i granchi dentro quella nave, giusto?";
			link.l1.go = "ring_4";
		break;
		
		case "ring_4":
			dialog.text = "Sì. Avremo un accordo. Ti mostrerò la via verso la nave e tu ti occuperai dei granchi. Divideremo il bottino trovato là. È giusto così: io ho scovato la nave, tu la ripulisci.";
			link.l1 = "No, compare, non mi interessa. Non è nel mio stile azzuffarmi con i granchi dentro una nave mezza affondata per qualche trofeo dubbio. Cercati un altro sventurato che ti tolga le castagne dal fuoco.";
			link.l1.go = "ring_exit";
			link.l2 = "Interessante... Era da tempo che pensavo di dare un'occhiata all'anello esterno. Affare fatto! Andrò a fare fuori quei granchi.";
			link.l2.go = "ring_5";
		break;
		
		case "ring_exit":
			dialog.text = "Peccato... Hai fatto una scelta sbagliata. Ci sono un sacco di bottini succulenti sulle navi dell’anello esterno... E nessuno era mai salito su quella nave prima. Va bene, come preferisci. Addio...";
			link.l1 = "Addio, compare...";
			link.l1.go = "exit";
		break;
		
		case "ring_5":
			dialog.text = "Sono lieto d’averci visto giusto su di te, compare. Ho come il presentimento che dentro di lei ci troveremo un bel po’ di sorprese...";
			link.l1 = "Vedremo. Sai quanti granchi ci sono qui?";
			link.l1.go = "ring_6";
		break;
		
		case "ring_6":
			dialog.text = "Penso siano quattro o cinque di loro... Beh, più o meno.";
			link.l1 = "Sta bene per me. Quando si parte?";
			link.l1.go = "ring_7";
		break;
		
		case "ring_7":
			dialog.text = "Andiamo là domani, dobbiamo prepararci. Prendi qualche antidoto da fratello Giuliano, le chele dei granchi sono velenose. Meglio non rischiare. Incontriamoci domani alle otto del mattino sul 'ponte obliquo'. Sai dov’è?";
			link.l1 = "Non lo so. Spiegati.";
			link.l1.go = "ring_8";
		break;
		
		case "ring_8":
			dialog.text = "C’è il relitto d’una vecchia nave dietro la ‘San Augustine’. La sua prua giace sotto l’acqua, mentre il suo poppa s’innalza verso il cielo. Per questo la chiamano il ‘ponte storto’. Lì ci si arriva solo a nuoto. Basta che t’immergi sotto il ponte e ti volti verso qualsiasi lato della ‘San Augustine’. Da lì nuoteremo assieme.";
			link.l1 = "Va bene. Ci vediamo domani!";
			link.l1.go = "ring_9";
		break;
		
		case "ring_repeat":
			dialog.text = "Le otto, 'ponte obliquo'...";
			link.l1 = "Sì, sì, me lo ricordo...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ring_repeat";
		break;
		
		case "ring_9":
			DialogExit();
			NextDiag.CurrentNode = "ring_repeat";
			pchar.quest.LSC_Ring_Start.win_condition.l1 = "Timer";
			pchar.quest.LSC_Ring_Start.win_condition.l1.date.hour  = 7.0;
			pchar.quest.LSC_Ring_Start.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.LSC_Ring_Start.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.LSC_Ring_Start.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.LSC_Ring_Start.function = "LSC_RingStart"; // готовы
			pchar.quest.LSC_Ring_Over.win_condition.l1 = "Timer";
			pchar.quest.LSC_Ring_Over.win_condition.l1.date.hour  = 10.0;
			pchar.quest.LSC_Ring_Over.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.LSC_Ring_Over.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.LSC_Ring_Over.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.LSC_Ring_Over.function = "LSC_RingOver"; // опоздание
			AddQuestRecord("LSC_Ring", "1");
		break;
		
		case "ring_10":
			dialog.text = "Ahah, eccoti qui, compare. Pronto a preparare un'insalata di granchio?";
			link.l1 = "Certo!";
			link.l1.go = "ring_11";
		break;
		
		case "ring_11":
			dialog.text = "Molto bene. Ora volgi lo sguardo verso l’anello esterno e osserva. Vedi quei due relitti che spuntano dall’acqua?";
			link.l1 = "Hm... Sì, lo faccio.";
			link.l1.go = "ring_12";
		break;
		
		case "ring_12":
			dialog.text = "Ora guarda tra loro verso l'anello esterno. Vedi il galeone con la prua tirata su? Sta proprio verso di noi. Osserva bene.";
			link.l1 = "...";
			link.l1.go = "ring_look";
		break;
		
		case "ring_look":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload_ring");
			DoQuestCheckDelay("LSC_RingTalkLook", 6.0);
		break;
		
		case "ring_13":
			dialog.text = "";
			link.l1 = "Penso di vederla... Sì!";
			link.l1.go = "ring_13a";
		break;
		
		case "ring_13a":
			dialog.text = "È la nostra meta. Nuota dritto senza voltarti. Ti indicherò la via del ritorno quando raggiungeremo l'anello esterno. L'ingresso alla stiva è quel buco sulla prua della nave. Sappi che non ci metterò piede finché non avrai fatto fuori tutti i granchi.";
			link.l1 = "Sì, avevamo un accordo ieri, ricordo. Tu mostri la nave e io ammazzo i granchi. Si va a nuotare?";
			link.l1.go = "ring_14";
		break;
		
		case "ring_14":
			dialog.text = "Certo! Ti seguirò.";
			link.l1 = "...";
			link.l1.go = "ring_swim";
		break;
		
		case "ring_swim":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetImmortal(npchar, true);
			pchar.quest.LSC_Ring_enter.win_condition.l1 = "locator";
			pchar.quest.LSC_Ring_enter.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_Ring_enter.win_condition.l1.locator_group = "reload";
			pchar.quest.LSC_Ring_enter.win_condition.l1.locator = "reload_ring";
			pchar.quest.LSC_Ring_enter.function = "LSC_RingEnter";
			LSC_RingSetItems(); // раскладка итемзов
			AddQuestRecord("LSC_Ring", "3");
		break;
		
		case "ring_15":
			dialog.text = "Ehi, ben fatto! Hai spazzato via tutta questa feccia!";
			link.l1 = "Mi ricordo che qualcuno mi parlò di 'quattro o cinque' granchi... Ricordami, chi fu?";
			link.l1.go = "ring_16";
		break;
		
		case "ring_16":
			dialog.text = "Compare, non sono mai entrato nella stiva per contarli per bene. Ho solo dato un'occhiata dallo squarcio. Non avevo alcuna intenzione di mentirti.";
			link.l1 = "Come vuoi. Diamo un'occhiata alla stiva...";
			link.l1.go = "ring_17";
		break;
		
		case "ring_17":
			dialog.text = "Certo! È proprio per questo che siamo qui, no?";
			link.l1 = "Esatto! Non perdiamo tempo...";
			link.l1.go = "ring_18";
		break;
		
		case "ring_18":
			DialogExit();
			NextDiag.CurrentNode = "ring_wait";
			LAi_SetWarriorType(npchar);
			LAi_warrior_DialogEnable(npchar, true);
			LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
			DoQuestCheckDelay("LSC_RingDialog", 60.0); // 1 минуту на пошариться
			npchar.quest.diagnode = "ring_19";
			AddQuestRecord("LSC_Ring", "4");
		break;
		
		case "ring_wait":
			dialog.text = "Aspetta un po’, compare, non ho ancora rovistato dappertutto dove volevo. Cerca meglio, magari scovi qualche tesoro in più.";
			link.l1 = "Va bene...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ring_wait";
		break;
		
		case "ring_19":
			dialog.text = "Niente di speciale. Peccato che qui non ci sia merce di valore. Solo provviste nei barili e copra nelle casse. Però, ho trovato una cassa con vino pregiato. E tu, che bottino hai trovato?";
			link.l1 = "Niente di che, davvero. Qualche cassa vale qualcosa, ma il resto è manzo salato e copra, proprio come hai detto tu.";
			link.l1.go = "ring_20";
		break;
		
		case "ring_20":
			dialog.text = "Non basta... Andiamo sopra a vedere il ponte superiore e le cabine.";
			link.l1 = "Andiamo.";
			link.l1.go = "ring_21";
		break;
		
		case "ring_21":
			DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("ExternalRingInside", "reload1", true);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.LSC_Ring_deck.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LSC_Ring_deck.win_condition.l1.location = pchar.location;
			pchar.quest.LSC_Ring_deck.win_condition = "LSC_RingEnterDeck";
			for (i=1; i<=3; i++)
			{
				sld = ItemsFromID("purse"+i);
				sld.shown = true;
				sld.startLocation = "ExternalRingDeck";
				sld.startLocator = "item"+i;
			}
		break;
		
		case "ring_22":
			dialog.text = "Maledizione! Guarda un po' lì! Quei maledetti crostacei hanno infestato il ponte! E come diamine ci sono riusciti, quei dannati bastardi?!";
			link.l1 = "Non fare il codardo! Resta qui, non muoverti e non attirare la loro attenzione. Penserò io a quelle bestie, subito...";
			link.l1.go = "ring_23";
		break;
		
		case "ring_23":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocator(npchar, "reload", "reload1", "", -1);
		break;
		
		case "ring_24":
			dialog.text = "Eh! Pare che le storie sul tuo talento con la spada fossero vere! Se fossi qui da solo, mi butterei a mare...";
			link.l1 = "Ascolta, e come sei finito a fare il contrabbandiere, eh? O stavi scappando da tutti quanti?";
			link.l1.go = "ring_25";
		break;
		
		case "ring_25":
			dialog.text = "Amico, innanzitutto ero più giovane, più forte e di certo più incosciente. In secondo luogo, non sono un mercenario da battaglie — sono uno di quelli che fa passare la roba di nascosto, e noi altri cerchiamo sempre di evitare il sangue. Terzo, il mio posto è tra le vele e la barra, non tra lame e pistole. E infine, tutti questi anni su quest’isola mi hanno ammorbidito.\nQuindi non darmi la colpa. Andiamo a vedere il ponte superiore. Sembra che la nave abbia visto una bella rissa — guarda che danni...";
			link.l1 = "Hai ragione. La nave è stata davvero bersagliata da una tempesta di fuoco. Bene, vediamo se troviamo qualcosa d’interessante.";
			link.l1.go = "ring_26";
		break;
		
		case "ring_26":
			dialog.text = "Già. E dobbiamo scovare gli ingressi alle stanze interne.";
			link.l1 = "Affare fatto, non perdiamo tempo. Chiamami se vedi un granchio.";
			link.l1.go = "ring_27";
		break;
		
		case "ring_27":
			DialogExit();
			NextDiag.CurrentNode = "ring_wait";
			LAi_SetWarriorType(npchar);
			LAi_warrior_DialogEnable(npchar, true);
			LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
			DoQuestCheckDelay("LSC_RingDialog", 80.0); // 1.3 минуты на пошариться
			npchar.quest.diagnode = "ring_28";
			AddQuestRecord("LSC_Ring", "5");
		break;
		
		case "ring_28":
			dialog.text = "Niente di prezioso, di nuovo... Ho trovato qualche cosuccia interessante e basta. Ma va bene così, di solito non si trovano tesori di valore sui ponti. Il meglio dev’essere nelle cabine. Lì c’è l’ingresso agli alloggi del capitano. Diamo un’occhiata.";
			link.l1 = "Stai all’erta, chi può dire cosa ci aspetta laggiù. Forse, sarebbe meglio che entrassi io per primo?";
			link.l1.go = "ring_29";
		break;
		
		case "ring_29":
			dialog.text = "Andiamo, "+pchar.name+"Non mi nasconderò più dietro la tua schiena. È davvero una vergogna, questo è certo...";
			link.l1 = "Avanti allora...";
			link.l1.go = "ring_30";
		break;
		
		case "ring_30":
			DialogExit();
			chrDisableReloadToLocation = true;
			LocatorReloadEnterDisable("ExternalRingDeck", "reload2", false);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "ExternalRingCabin1", "reload", "reload1", "OpenTheDoors", -1);
			pchar.quest.LSC_Ring_cabin.win_condition.l1 = "location";
			pchar.quest.LSC_Ring_cabin.win_condition.l1.location = "ExternalRingCabin1";
			pchar.quest.LSC_Ring_cabin.win_condition = "LSC_RingEnterCabin";
			sld = ItemsFromID("RingCapBook"); // кладем журнал 'Санта-Люсии'
			sld.shown = true;
			sld.startLocation = "ExternalRingCabin1";
			sld.startLocator = "item1";
		break;
		
		case "ring_31":
			dialog.text = "Sembra proprio che mi sia andata bene – né granchi né altra feccia qui. Adesso però metteremo sottosopra questa cabina, maledizione, giuro che sto cominciando a perdere la pazienza. Ho trovato solo due fottute dozzine di dobloni e qualche cianfrusaglia!";
			link.l1 = "Calmati. Avevi ragione, tutti i tesori sono sempre nascosti nella cabina del capitano. Vediamo che bottino ci tocca!";
			link.l1.go = "ring_32";
		break;
		
		case "ring_32":
			DialogExit();
			NextDiag.CurrentNode = "ring_wait";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto2", "LSC_RingSetToBarman", -1);
			DoQuestCheckDelay("LSC_RingDialog", 30.0); // 30 сек на пошариться
			npchar.quest.diagnode = "ring_33";
		break;
		
		case "ring_33":
			dialog.text = "Ah-ah! Proprio come pensavo! Conosco bene le abitudini dei mercanti, amano nascondere il tesoro della nave in nascondigli segreti! Il capitano di questa pinaccia era una volpe astuta, ma non mi fregherà così facilmente! Guarda cosa ho trovato! Senza di me non ci saresti mai arrivato!";
			link.l1 = "Mostrami!";
			link.l1.go = "ring_34";
		break;
		
		case "ring_34":
			dialog.text = "Quarantamila pesos, due scrigni colmi di dobloni, un sacchetto di smeraldi e una manciata di gioielli! Il proprietario era davvero benestante... Va bene, almeno ripagherà la fatica, anche se speravo in un bottino più ricco. Dividiamolo con giustizia.";
			link.l1 = "Eccellente, Richard. Almeno abbiamo messo da parte qualche doblone!";
			link.l1.go = "ring_35";
		break;
		
		case "ring_35":
			TakeNItems(pchar, "jewelry4", 25);
			TakeNItems(pchar, "chest", 1);
			TakeNItems(pchar, "icollection", 1);
			AddMoneyToCharacter(pchar, 20000);
			Log_Info("You have received a chest with doubloons");
			Log_Info("You have received 25 emeralds");
			Log_Info("You have received  a collection of jewels");
			PlaySound("interface\important_item.wav");
			dialog.text = "E allora, teniamoci ciascuno ciò che abbiamo recuperato sui ponti. Ti sta bene così? Hai scovato qualcosa d’utile tra i forzieri e negli armadietti?";
			link.l1 = "Qualche oggettino indiano, amuleti, pergamene e simili.";
			link.l1.go = "ring_36";
		break;
		
		case "ring_36":
			dialog.text = "Tienilo per te. In fondo, sei tu che hai corso il rischio più grande.";
			if (CheckAttribute(pchar, "questTemp.LSC.Ring.ReadCapBook")) // прочел журнал
			{
				link.l1 = "Bene. E ho trovato qualcos'altro che un cercatore di tesori come te potrebbe ritenere utile. Vedi, c'era il diario di bordo di un capitano abbandonato sulla scrivania. La storia che racconta è assai triste... ma ci riguarda, in un certo senso. Nella stiva è nascosta una cassa piena d’oro! Leggilo!";
				link.l1.go = "ring_41";
			}
			else
			{
				if (CheckCharacterItem(pchar, "RingCapBook")) // взял журнал
				{
					link.l1 = "Va bene. Ma ho trovato un’altra cosa – il diario di bordo del capitano.";
					link.l1.go = "ring_38";
				}
				else
				{
					link.l1 = "Va bene, accetto questi patti, ah-ah. Allora, che si fa, è l’ora di tornare?";
					link.l1.go = "ring_37";
				}
			}
		break;
		
		case "ring_37":
			dialog.text = "Sì. Non dir nulla a nessun altro della nave, sarà il nostro segreto. Certo, non ci serve copra, ma le provviste ci faranno comodo. Non dovremo più comprarle dall’ammiraglio.";
			link.l1 = "D'accordo, accetto. Spero che gli altri non trovino presto la nave. Andiamo!";
			link.l1.go = "ring_cabin_exit";
		break;
		
		case "ring_38":
			dialog.text = "L’hai letto?";
			link.l1 = "Non ancora...";
			link.l1.go = "ring_39";
		break;
		
		case "ring_39":
			dialog.text = "Allora leggiamola! Potremmo scoprire qualcosa di importante. E poi, sarà curioso capire come diavolo sia finita qui. Leggila!";
			link.l1 = "Hm. Va bene, lo leggerò adesso...";
			link.l1.go = "ring_40";
		break;
		
		case "ring_40":
			DialogExit();
			NextDiag.CurrentNode = "book_wait";
			LAi_SetWarriorType(npchar);
			LAi_warrior_DialogEnable(npchar, true);
			LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
		break;
		
		case "book_wait":
			dialog.text = "L'hai letto? Che c'è scritto?";
			if (CheckAttribute(pchar, "questTemp.LSC.Ring.ReadCapBook")) // прочел журнал
			{
				link.l1 = "Ascolta bene allora... La storia è assai triste... ma ci riguarda, in un modo o nell’altro. Le tue doti da cacciatore di tesori potrebbero tornarci utili. C’è una cassa nascosta, colma d’oro, nella stiva! Leggilo!";
				link.l1.go = "ring_41";
			}
			else
			{
				link.l1 = "Aspetta un attimo. Leggerò e ti dirò...";
				link.l1.go = "exit";
				NextDiag.TempNode = "book_wait";
			}
		break;
		
		case "ring_41":
			dialog.text = "Davvero? "+pchar.name+", Io... beh, non so leggere tanto bene. Raccontami tu cosa ci sta scritto, eh?";
			link.l1 = "In breve: questa pinaccia stava attraversando il Mar dei Caraibi dalla Terraferma del Sud alla Nuova Spagna. Il capitano s’è sposato con la principessa indiana di una tribù del basso Orinoco. Lei gli ha sussurrato dove il suo popolo faceva i sacrifici...";
			link.l1.go = "ring_42";
		break;
		
		case "ring_42":
			dialog.text = "";
			link.l1 = "I pepite d’oro erano le loro offerte. Sì, il nostro capitano audace ha soffiato questa scorta d’oro grazie all’aiuto del suo primo ufficiale e del quartiermastro. L’hanno nascosta nella stiva, dentro una delle casse e coperta con copra...";
			link.l1.go = "ring_43";
		break;
		
		case "ring_43":
			dialog.text = "";
			link.l1 = "Ma pare che il saccheggio del luogo sacro indiano sia stato punito. La nave fu colta da una bonaccia mortale, le scorte d’acqua si assottigliarono, scoppiò una febbre e i pirati assalirono la nave. I marinai accusarono la ragazza indiana, moglie del capitano, chiedendo di gettarla a mare. Naturalmente il capitano si oppose, e l’equipaggio diede inizio all’ammutinamento...";
			link.l1.go = "ring_44";
		break;
		
		case "ring_44":
			dialog.text = "";
			link.l1 = "Il capitano ha perso quella battaglia. Secondo gli ultimi appunti, si è barricato con una ragazza indiana in cabina e ha provato a sparare ai marinai inferociti che sfondavano la porta. E stava arrivando una tempesta... pare che proprio quella abbia trascinato la nave fin qui. Il resto della storia è chiaro: la ragazza è stata colpita e il capitano sicuramente fatto fuori dai rivoltosi.";
			link.l1.go = "ring_45";
		break;
		
		case "ring_45":
			dialog.text = "Hm. È davvero una storia mesta. Ma mi stai prendendo in giro? Davvero c’è uno scrigno d’oro nella stiva? Non credo alle mie orecchie! Quale nave? Andiamo subito! Controllerò ogni balla, ogni barile!";
			link.l1 = "Andiamo. Anch’io fremo dalla voglia di cominciare la ricerca.";
			link.l1.go = "ring_seek_gold";
		break;
		
		case "ring_cabin_exit":
			DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("ExternalRingInside", "reload1", false); // открываем выход
			LocatorReloadEnterDisable("LostShipsCity_town", "reload_ring", false); // открываем вход // patch-2
			DoQuestReloadToLocation("ExternalRingDeck", "reload", "reload2", "LSC_RingFinalStage");
			sld = ItemsFromID("RingCapBook");
			sld.shown = false; // убираем журнал
			AddQuestRecord("LSC_Ring", "6");
		break;
		
		case "ring_seek_gold":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			// ставим прерывание на локатор
			pchar.quest.LSC_Ring_gold.win_condition.l1 = "locator";
			pchar.quest.LSC_Ring_gold.win_condition.l1.location = "ExternalRingInside";
			pchar.quest.LSC_Ring_gold.win_condition.l1.locator_group = "quest";
			pchar.quest.LSC_Ring_gold.win_condition.l1.locator = "gold";
			pchar.quest.LSC_Ring_gold.win_condition = "LSC_RingFindGold";
			// подменяем состав бокса
			pchar.GenQuestBox.ExternalRingInside = true;
			pchar.GenQuestBox.ExternalRingInside.box1.items.jewelry5 = 2522;
			AddQuestRecord("LSC_Ring", "7");
		break;
		
		case "ring_46":
			dialog.text = "Ah-ah! L’abbiamo trovata! Esiste davvero! Guarda che montagna! L’intera cassa! Ci sono cinquemila pepite, se non di più! Mai visto tanto oro in vita mia!";
			link.l1 = "Congratulazioni, compare. Pare che la nostra impresa sia giunta a buon fine... Che ne facciamo di tutto quell’oro?";
			link.l1.go = "ring_47";
		break;
		
		case "ring_47":
			dialog.text = "Cosa vuoi dire? Divideremo a metà!";
			link.l1 = "Certo che lo faremo. Dove vuoi metterlo? Lo lasci qui?";
			link.l1.go = "ring_48";
		break;
		
		case "ring_48":
			dialog.text = "Ah! Certo che nasconderò l’oro nei miei nascondigli e nessuno li troverà mai. A nascondere son maestro! Prendiamo metà dell’oro e mettiamolo in questa botte, quella sarà la mia parte. Me la porterò via prima che cali il sole. \nTu fai quel che vuoi col tuo bottino. Ma ti conviene mettere anche il tuo in qualche buon ripostiglio. Non lamentarti poi se sparisce. Io son uomo d’onore, a modo mio, e mai mi permetterei di toccare la tua parte. Ma gli altri, quelli che verranno dopo... chissà che non mettano le mani su quel che resta.";
			link.l1 = "Bene. Deciderò io che fare del mio oro. Mettiamo la tua parte in una botte...";
			link.l1.go = "ring_49";
		break;
		
		case "ring_49":
			DialogExit();
			SetLaunchFrameFormParam("Two hours later..."+ NewStr() +"The gold was shared!", "", 0, 5);//табличка
			WaitDate("", 0, 0, 0, 2, 10);
			LaunchFrameForm();
			RecalculateJumpTable();
			sld = characterFromId("LSC_Rishard");
			sld.quest.diagnode = "ring_50";
			DoQuestCheckDelay("LSC_RingDialog", 5.0);
		break;
		
		case "ring_50":
			dialog.text = "Fatto... Grazie, "+pchar.name+", per avermi accompagnato. Non ce l’avrei mai fatta senza di te. Ora dovrei pensare a costruire una tartana... per fuggire da quest’isola... Bah, lasciamo stare. Ci penserò più tardi\nHo un lavoro da sbrigare – spostare l’oro in luogo sicuro. Addio, amico, spero che tu spenda il tuo bottino con saggezza!";
			link.l1 = "Addio, Richard. Oggi è stato un giorno glorioso. Ci si rivede!";
			link.l1.go = "ring_51";
		break;
		
		case "ring_51":
			DialogExit();
			LocatorReloadEnterDisable("ExternalRingInside", "reload1", false); // открываем выход
			LocatorReloadEnterDisable("LostShipsCity_town", "reload_ring", false); // открываем вход
			DoQuestCheckDelay("LSC_RingFinalStage", 0.5);
			DeleteAttribute(pchar, "questTemp.LSC.Ring.ReadCapBook");
			AddQuestRecord("LSC_Ring", "8");
		break;
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Domande? Eh, va bene, se proprio ti serve...";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Come sei arrivato qui?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Vuoi lasciare l’Isola Giustizia?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Hai mai pensato di unirti a una delle ciurme? Per esempio, ai Narvali?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "È vero che si può trovare un sacco di roba interessante sull’anello esterno?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Nessuna domanda. Perdono...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Per dieci anni io e i miei compari abbiamo navigato da Cuba fino all’Isola su una tartana ben armata. Il luogo dell’Isola era il nostro segreto – trasportavamo carcasse di toro, vendendo carne fresca in cambio di merci e oro presi dalle stive delle navi che approdavano qui.\nChe tempi quelli! Qui i viveri son sempre stati una croce: pane secco e carne salata, per lo più. Così, per un pezzo di carne succosa ci pagavano in spezie, che in Europa valgono come il diavolo! Ogni viaggio mi fruttava abbastanza da comprare tutte le sgualdrine di Tortuga.\nMa ogni cosa ha una fine, e così la nostra vita beata. Il tempo si guastò – le tempeste si fecero più feroci, e raggiungere l’Isola divenne un affare da disperati. Alcuni dei miei hanno lasciato quel traffico, ma non io, né la dozzina di uomini d’animo saldo che mi seguivano.\nAlla fine, fummo scaraventati su una scogliera a due miglia dall’Isola. Ancora non capisco come sono riuscito a nuotare nel mare furioso. Così sono diventato anch’io uno di quelli con cui trafficavo un tempo.";
			link.l1 = "Storia affascinante...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Ah! Me ne andrò da questo maledetto posto, per mille balene! Ma più tardi. Che dovrei mai fare a Cuba? Non mi è rimasto un cane che mi saluti e le mie tasche son vuote. Comincerò a costruire una barca appena metterò le mani su una nave carica d’oro nel cerchio esterno, o su una montagna di dobloni.";
			link.l1 = "Capisco...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
			SaveCurrentNpcQuestDateParam(npchar, "quest_date");
		break;
		
		case "ansewer_3":
			dialog.text = "E perché dovrei? Fare la guardia come uno scemo ogni tre giorni e tenere la gente lontana dal San Gabriel? E poi non amano arruolare gente nuova. Sono indigeni di qui... E i negri sono uguali. No, meglio che me la cavi da solo.";
			link.l1 = "Capisco...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Certo! È proprio questo che fa vivere ancora l’Isola e i suoi abitanti. Sai quando qui si fa festa? Quando arriva una nuova nave. Comunque, ci sono un sacco di navi intatte cariche d’oro e mercanzie sull’anello esterno.\nIl guaio è che l’anello esterno è quasi impossibile da esplorare, là fuori regna il caos: se ci resti impigliato, scivoli o fai un brutto passo – potresti trovarti in una buca da cui non esci più. E allora sei finito. In tanti ci hanno lasciato la pelle così.";
			link.l1 = "Hm... Interessante.";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Cosa stai combinando laggiù, eh? Ladro!","Guarda un po’! Appena mi sono perso nei miei pensieri, tu hai deciso di frugare nel mio baule!","Hai deciso di frugare nei miei forzieri? Non la passerai liscia, canaglia!");
			link.l1 = "Maledizione!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Cosa?! Hai deciso di frugare nei miei forzieri? Non la passerai liscia!";
			link.l1 = "Ragazza sciocca!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Ascolta, faresti meglio a mettere via quell’arma. Mi mette in agitazione.","Sai, qui non è tollerato andare in giro con la lama sguainata. Riponila.","Ascolta, smettila di fare il cavaliere errante con la spada sguainata. Mettila via, non è roba per te...");
			link.l1 = LinkRandPhrase("Bene.","D'accordo.","Come dite voi...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Ascolta, sono cittadino di questa città e ti chiederei di tenere a bada la tua lama.","Ascolta, sono cittadino di questa città e ti chiedo di tenere a bada la tua lama.");
				link.l1 = LinkRandPhrase("D'accordo.","D'accordo.","Come dici tu...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Fa' attenzione, compare, a girare armato. Potrei innervosirmi...","Non mi piace quando gli uomini mi passano davanti con l’arma sguainata. Mi mette inquietudine...");
				link.l1 = RandPhraseSimple("Capito.","Me ne sto andando.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

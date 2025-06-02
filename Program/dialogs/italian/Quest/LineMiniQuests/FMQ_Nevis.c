// Addon-2016 Jason, французские миниквесты (ФМК) Сент-Кристофер
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Un evidente malfunzionamento. Avvisa i diavoli che han fatto il gioco.";
			link.l1 = "Oh, lo farò.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "seafox":
			DelMapQuestMarkCity("Charles");
			LAi_SetImmortal(npchar, false);
			DelLandQuestMark(npchar);
			LAi_RemoveLoginTime(npchar);
			PlaySound("Voice\English\LE\SeaFox\SeaFox_01.wav");
			dialog.text = TimeGreeting()+", capitano. (si mette sull’attenti) Permettetemi di presentarmi: tenente "+GetFullName(npchar)+", Reggimento di Fanteria Marittima di Antigua, di guarnigione a St. Johns. Avrei un favore da chiederti.";
			link.l1 = "Saluti, Tenente Gretton. Il mio nome è "+GetFullName(pchar)+". Che sorta di favore?";
			link.l1.go = "seafox_1";
		break;
		
		case "seafox_1":
			dialog.text = "Permettimi di spiegare la situazione in breve. Quattro dei miei uomini ed io stavamo navigando da St. Johns verso Sint-Maarten quando una tempesta ha colpito la nostra nave. Il maltempo non è durato a lungo, ma è bastato perché il nostro vecchio barcone imbarcasse acqua. Abbiamo dovuto cambiare rotta e fermarci qui per delle riparazioni. Ci sta portando via un tempo che non abbiamo.\nAndiamo di fretta, dobbiamo raggiungere Sint-Maarten, precisamente Grand Case Beach. Aiutami, capitano, e ti ricompenserò come si deve. Due giorni di viaggio per una paga generosa!";
			link.l1 = "Deve esser proprio una paga generosa, tenente, se volete ch’io infili di nascosto marinai inglesi su un’isola olandese.";
			link.l1.go = "seafox_2";
		break;
		
		case "seafox_2":
			dialog.text = "Non temete. La Francia non è in guerra con gli olandesi, quindi non dovrebbe esserci alcun pericolo. Lasciateci solo sbarcare sulla spiaggia e sarà tutto. Vogliamo solo dare un’occhiata in giro per l’isola. Che ne dite, affare fatto?";
			link.l1 = "D'accordo, ci sto. Non è poi così lontano da qui. Parliamo di quella ricompensa.";
			link.l1.go = "seafox_3";
			link.l2 = "Mi rincresce, ma ho affari urgenti da sbrigare altrove e preferirei non far infuriare quei dannati olandesi.";
			link.l2.go = "seafox_exit";
		break;
		
		case "seafox_exit":
			dialog.text = "Come dite, capitano. Continuerò a cercare, allora. Addio e che il vento vi sia sempre favorevole!";
			link.l1 = "Addio, tenente.";
			link.l1.go = "seafox_exit_1";
		break;
		
		case "seafox_exit_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			npchar.lifeday = 0;
		break;
		
		case "seafox_3":
			GiveItem2Character(pchar, "purse2"); 
			Log_Info("You have received a purse of doubloons");
			dialog.text = "Diecimila pezzi da otto. Ecco un anticipo.";
			link.l1 = "Bene. Fa' salire i tuoi uomini a bordo, non perdiamo tempo.";
			link.l1.go = "seafox_4";
		break;
		
		case "seafox_4":
			dialog.text = "Aye aye, capitano!";
			link.l1 = "...";
			link.l1.go = "seafox_5";
		break;
		
		case "seafox_5":
			DialogExit();
			AddQuestRecord("FMQ_Nevis", "1");
			pchar.questTemp.FMQN = "begin";
			
			chrDisableReloadToLocation = false;
			sld = CharacterFromID("FMQN_seafox_1");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload4_back", "", "", "", "", 10.0); // англичане на борт
			sld.location = "None";
			AddPassenger(pchar, sld, false);//добавить пассажира
			SetCharacterRemovable(sld, false);
			pchar.quest.FMQN_sailing.win_condition.l1 = "location";
			pchar.quest.FMQN_sailing.win_condition.l1.location = "Shore40";
			pchar.quest.FMQN_sailing.win_condition.l2 = "Ship_location";
			pchar.quest.FMQN_sailing.win_condition.l2.location = "Shore40";
			pchar.quest.FMQN_sailing.function = "FMQN_ArriveMaarten";
			if(bImCasual)
			{
				NewGameTip(StringFromKey("FMQ_69"));
			}
			else SetFunctionTimerCondition("FMQN_SailingLate", 0, 0, 10, false);
			for(i = 0; i < MAX_LOCATIONS; i++)
			{	
				sld = &Locations[i];
				if (CheckAttribute(sld, "islandId") && sld.islandId == "SentMartin")
				{
					sld.DisableEncounters = true;	
				}
			}
			sld = &Locations[FindLocation("Shore40")];
			sld.QuestlockWeather = "23 Hour";
			AddMapQuestMarkShore("Shore40", true);
		break;
		
		case "seafox_6":
			PlaySound("Voice\English\LE\SeaFox\SeaFox_02.wav");
			dialog.text = "Grazie per la traversata senza intoppi, capitano! Mi rincresce davvero, ma al momento non posso saldare il debito... doveva esserci un nostro legnetto da queste parti, ma come vedi bene, non si scorge all’orizzonte. Devo chiederti ancora un favore. Potresti attendere in questa baia per due o tre giorni? Dobbiamo andare a vedere che succede in giro. Una volta tornati, portaci ad Antigua. Il colonnello Fox ti ricompenserà generosamente.";
			link.l1 = "Certo che lo farà. E io che speravo che tutto filasse liscio come l’olio.";
			link.l1.go = "seafox_7";
		break;
		
		case "seafox_7":
			dialog.text = "Non ti crucciare, capitano. Capisco bene come ti senti, ma ahimè: non ho un soldo bucato. Posso solo prometterti che riceverai il compenso per entrambe le traversate e per l’attesa qui. E avrai anche i ringraziamenti personali del colonnello Fox!";
			link.l1 = "Non posso proprio abbandonarti al tuo destino... Va bene, tenente Gretton. Aspetterò qui per tre giorni, ma non di più.";
			link.l1.go = "seafox_8";
		break;
		
		case "seafox_8":
			dialog.text = "Grazie, signore! Ci dirigiamo verso l'entroterra. Giuro che torneremo tra 72 ore, non un minuto in più.";
			link.l1 = "Buon vento, tenente. Non farti acciuffare.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_EnglishmanGo");
		break;
		
		case "seafox_9":
			DelLandQuestMark(npchar);
			PlaySound("Voice\English\LE\SeaFox\SeaFox_02.wav");
			dialog.text = "Che incontro fortunato! Pensavo che ci aspettassi già alla spiaggia di Grand Case, Capitano de Maure!";
			link.l1 = "Salve, tenente, la sorpresa è reciproca. Non mi aspettavo di vederti vestito come un soldato olandese.";
			link.l1.go = "seafox_10";
		break;
		
		case "seafox_10":
			dialog.text = "È il nostro travestimento... Perché siete qui fuori, signore?";
			link.l1 = "È un travestimento rischioso, compare. Le spie rischiano d’essere impiccate senza processo. E a proposito d’impiccagione, se vuoi evitare la tua, ti conviene tendere l’orecchio.";
			link.l1.go = "seafox_11";
		break;
		
		case "seafox_11":
			dialog.text = "Hai tutta la mia attenzione, compare.";
			link.l1 = "Ho veleggiato fino a Philipsburg e ho parlato con la gente del posto dopo che sei sbarcato. Gli olandesi ti tengono d’occhio. Sanno della tua missione per salvare quegli ufficiali inglesi di alto rango catturati.";
			link.l1.go = "seafox_12";
		break;
		
		case "seafox_12":
			dialog.text = "Maledizione e dannazione! Come diavolo hanno fatto a scoprirlo?";
			link.l1 = "Uno degli ufficiali inglesi catturati. In cambio della sua libertà, ha spifferato tutto ai dannati olandesi sulla missione di salvataggio. Tutta Philipsburg è all’erta, aspettando te e la tua ciurma che cercherete d’entrare in città. Come se non bastasse, una corvetta olandese pattuglia il mare attorno a Sint-Maartin. È una trappola, tenente.";
			link.l1.go = "seafox_13";
		break;
		
		case "seafox_13":
			dialog.text = RandSwear()+"Quel farabutto disonorato! Scoprirò chi è quel traditore e lo denuncerò davanti al Parlamento!";
			link.l1 = "Dovrà aspettare, signor Gretton. Torna stanotte a Grand Case Beach e risali sulla mia nave prima che ti acchiappino.";
			link.l1.go = "seafox_14";
		break;
		
		case "seafox_14":
			dialog.text = "E abbandonare gentiluomini inglesi in una prigione olandese? Piuttosto crepo, signore. Non deluderò il colonnello Fox.";
			link.l1 = "Eh, pensi che gli olandesi ti lasceranno scegliere tra l’impiccagione o il plotone d’esecuzione quando ti metteranno le mani addosso?";
			link.l1.go = "seafox_15";
		break;
		
		case "seafox_15":
			dialog.text = "Non credere che ti lasceranno semplicemente salpare da qui, Capitano de Maure. Siamo entrambi impantanati fino al collo in questa faccenda.";
			link.l1 = "Maledizione, hai ragione tu. Quella corvetta ci piomberà addosso appena molliamo gli ormeggi...";
			link.l1.go = "seafox_16";
		break;
		
		case "seafox_16":
			dialog.text = "Gli olandesi forse sanno che stiamo arrivando, ma non hanno la minima idea *di come* lo faremo. Il travestimento è già pronto – osserva questa uniforme. Bella, vero? Se il nostro piano non fosse stato tradito, ci saremmo semplicemente presentati alla prigione locale, li avremmo colti di sorpresa e avremmo fatto fuori tutti. Ma di certo ora ci stanno aspettando in agguato. Dovremo improvvisare.\nCapitano, vai alla chiesa di Philipsburg e cerca un predicatore che si chiama Filippe Jacobsen. Dovrebbe essere lì dalle sei alle dieci del mattino. Filippe è uno dei nostri infiltrati.\nDigli questa parola d’ordine: 'Da quanto tempo i marinai prigionieri hanno confessato?'. Poi spiegagli la situazione e pretendine l’aiuto in nome del colonnello Fox. Dopo porta la sua risposta a me. Facile, e nessun rischio per te.";
			link.l1 = "Mi pare una gran bella follia chiedere della confessione in una chiesa calvinista olandese, tenente. Quel pastore mi metterebbe il cappio al collo per papista. Va bene, raccontami di queste uniformi... le hai prese a una pattuglia olandese?";
			link.l1.go = "seafox_17";
		break;
		
		case "seafox_17":
			dialog.text = "Sì, signore.";
			link.l1 = "E dove sono finiti adesso?";
			link.l1.go = "seafox_18";
		break;
		
		case "seafox_18":
			dialog.text = "Tenuti in ostaggio tra i cespugli poco lontano da questa grotta.";
			link.l1 = "Capito. Tienili al sicuro, io vado in città. Aspettami qui e non dare nell’occhio – gli olandesi perlustrano la giungla e i mari a caccia di te.";
			link.l1.go = "seafox_19";
		break;
		
		case "seafox_19":
			dialog.text = "Staremo zitti come topi in chiesa, capitano. Vi prego, fate presto!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_ToChurch");
		break;
		
		case "seafox_20":
			PlaySound("Voice\English\soldier_common_4.wav");
			DelLandQuestMark(npchar);
			dialog.text = "Sei tornato? Capitano, che ci fai qui? Vai in città, stai attirando occhi sul nostro rifugio!";
			link.l1 = "Sono tornato dalla città. Che razza di giochi state tramando voi inglesi?";
			link.l1.go = "seafox_21";
		break;
		
		case "seafox_21":
			dialog.text = "Mi scusi, come dice?";
			link.l1 = "Sono andato in chiesa. Un edificio grande, sobrio e austero proprio come piace a quegli iconoclasti olandesi. Indovina un po', tenente? Non c’è nessun predicatore di nome Filippe Jacobsen.";
			link.l1.go = "seafox_22";
		break;
		
		case "seafox_22":
			dialog.text = "Impossibile, ci mette piede ogni santa mattina—";
			link.l1 = "Zitto e ascoltami! Se mai esiste davvero questo tuo Jacobsen, di certo non mette piede in chiesa! Mai visto lì! Né al mattino, né alla sera! Maledizione a tutti i santi! Per quale diavolo ho accettato questo maledetto incarico?! Comandato da uno stupido figliodiputtana pivello, moccioso col latte ancora sulle labbra tenente—";
			link.l1.go = "seafox_23";
		break;
		
		case "seafox_23":
			dialog.text = "Signore, esigo soddisfazione per quell'insulto. Quando saremo fuori di qui, ci sfideremo a duello secondo le usanze di-";
			link.l1 = ""+RandSwear()+"";
			link.l1.go = "seafox_24";
		break;
		
		case "seafox_24":
			PlaySound("Ambient\Jail\chain.wav");
			PlaySound("Ambient\Land\door_001.wav");
			dialog.text = "Zitti tutti, maledetti!!! ... Ho appena sentito qualcosa.";
			link.l1 = "";
			link.l1.go = "seafox_25";
		break;
		
		case "seafox_25":
			PlaySound("Voice\English\LE\SeaFox\SeaFox_04.wav");
			dialog.text = "Corpo di mille balene, c’è qualcuno fuori! Tu! Hai riportato qui gli olandesi, canaglia! Traditore!";
			link.l1 = ""+RandSwear()+"!!!";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_HollandBattleFight");
		break;
		
		case "seafox_26":
			DelLandQuestMark(npchar);
			pchar.quest.FMQN_fail1.over = "yes";
			PlaySound("Voice\English\LE\SeaFox\SeaFox_02.wav");
			dialog.text = "Felice di vedervi, signore, che novità portate?";
			link.l1 = "Ho incontrato il tuo uomo. Stasera porterà del vino 'corretto' alla guarnigione della prigione. S’è procurato una pozione da una zingara: non è mortale, ma li farà dormire come sassi. Tu dovrai entrare stanotte e tirare fuori i tuoi gentiluomini prigionieri. Ah, questa consegna di vino mi è costata venticinque dobloni. Non scordarti di menzionarlo nel rapporto.";
			link.l1.go = "seafox_27";
		break;
		
		case "seafox_27":
			dialog.text = "Non preoccuparti dei soldi. Capitano, ti chiederei di unirti a noi in questa faccenda e indicarci la strada per la prigione. Sei già stato a Philipsburg, quindi conosci la città meglio di noi. Non serve che tu entri con noi, la fuga la gestiamo noi. Tu portaci solo fino alla porta.";
			link.l1 = "Maledizione, signor Gretton, questo lavoro diventa sempre più interessante. Spero che il compenso salga di pari passo.";
			link.l1.go = "seafox_28";
		break;
		
		case "seafox_28":
			dialog.text = "Certamente lo è, capitano. Non vi pentirete d'averci dato una mano. La vostra nave è ancorata alla Spiaggia di Grand Case?";
			if (pchar.location.from_sea == "Shore40")
			{
				link.l1 = "Aye.";
				link.l1.go = "seafox_29";
			}
			else
			{
				link.l1 = "No.";
				link.l1.go = "seafox_29x";
			}
		break;
		
		case "seafox_29":
			dialog.text = "Bene. Allora preparati e raggiungici alle porte della città verso le undici di sera.";
			link.l1 = "Ci vediamo laggiù.";
			link.l1.go = "seafox_30";
		break;
		
		case "seafox_29x":
			dialog.text = "Assicurati di portarla lì, perché dobbiamo far uscire i nostri uomini attraverso la giungla. Salpare dal porto o da Simpson Bay è impossibile a causa del forte. Prepara tutto e incontraci alle porte della città entro le undici di sera.";
			link.l1 = "Ci vediamo là.";
			link.l1.go = "seafox_30";
		break;
		
		case "seafox_30":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddDialogExitQuestFunction("FMQN_EnglandPrepare");
		break;
		
		case "seafox_31":
			PlaySound("Voice\English\Gr_hovernor01.wav");
			dialog.text = "Pronto, capitano?";
			link.l1 = "Sì.";
			link.l1.go = "seafox_32";
		break;
		
		case "seafox_32":
			dialog.text = "Andiamo, allora.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_EnglandReload");
		break;
		
		case "seafox_33":
			dialog.text = "Zitto... Capitano! È fatta, filiamo via da qui al diavolo!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_EnglandRunToJungle");
		break;
		
		case "seafox_34":
			dialog.text = "Non so come diavolo ci siamo riusciti, ma ce l’abbiamo fatta! Tutto questo non sarebbe stato possibile senza il vostro aiuto, signore. Ora viene la parte relativamente semplice: dobbiamo lasciare Sint-Maartin vivi e interi. Andiamo a Grand Case Beach!";
			link.l1 = "Andiamo!";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_EnglandRunToShore");
		break;
		
		case "seafox_35":
			PlaySound("Voice\English\LE\SeaFox\SeaFox_05.wav");
			dialog.text = "Capitano de Maure... signore, vi ringrazio per l’aiuto! Vi supplico, non salpate subito ma restate in porto ancora un giorno mentre riferisco al colonnello Fox. Andate a trovarlo domani, il suo ufficio è nel palazzo del governatore.";
			link.l1 = "Molto bene, Tenente Gretton. Spero proprio che ne valga la pena. Ci vorrà un'eternità a riparare la mia reputazione con gli olandesi per colpa della tua bravata.";
			link.l1.go = "seafox_36";
		break;
		
		case "seafox_35x":
			PlaySound("Voice\English\LE\SeaFox\SeaFox_05.wav");
			dialog.text = "Grazie per il vostro aiuto, capitano! Siete un vero eroe! È una disgrazia che il tenente Gretton non ce l’abbia fatta. È morto da vero gentiluomo e figlio d’Inghilterra. Vi chiederei di restare qui ancora un giorno, mentre riferisco al colonnello Fox. Fateci un salto domani, il suo ufficio è nel palazzo del governatore.";
			link.l1 = "Va bene. Spero che ne valga la pena. Ci vorrà un bel po’ prima che riesca a rimettere a posto la mia reputazione con gli olandesi per colpa della tua bravata.";
			link.l1.go = "seafox_36";
		break;
		
		case "seafox_36":
			dialog.text = "Non temete, signore. Nel mio rapporto vi darò il massimo degli onori. (saluta) È stato un piacere, signore!";
			link.l1 = "...";
			link.l1.go = "seafox_37";
		break;
		
		case "seafox_37":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", -1);
			pchar.quest.FMQN_eng_reward.win_condition.l1 = "Timer";
			pchar.quest.FMQN_eng_reward.win_condition.l1.date.hour  = 6.0;
			pchar.quest.FMQN_eng_reward.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQN_eng_reward.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQN_eng_reward.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQN_eng_reward.function = "FMQN_EnglandReward";
			AddQuestRecord("FMQ_Nevis", "28");
		break;
		
		case "soldier":
			PlaySound("Voice\English\soldier_common_2.wav");
			dialog.text = "Capitano "+GetFullName(pchar)+"?";
			link.l1 = "Hmm... Sì, che posso fare per voi?";
			link.l1.go = "soldier_1";
		break;
		
		case "soldier_1":
			dialog.text = "L'ufficio del porto ci ha avvisati del recente arrivo della vostra nave. Sua Eccellenza Mynheer Martin Thomas, il governatore di Philipsburg, desidera vedervi.";
			link.l1 = "E perché mai? Sono forse in arresto?";
			link.l1.go = "soldier_2";
		break;
		
		case "soldier_2":
			AddLandQuestMark(characterFromId("Marigo_Mayor"), "questmarkmain");
			dialog.text = "Oh no, no, signor capitano, non siete in arresto. Il governatore ha ordinato di invitare ogni capitano appena sbarcato al suo palazzo per un caffè e le dovute presentazioni. Seguitemi!";
			link.l1 = "Sembra un’offerta che non posso rifiutare. Mostrami la strada.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_ReloadToGovernor");
		break;
		
		case "hol_officer":
			PlaySound("Voice\English\hol_gov_complete.wav");
			dialog.text = "Mynheer, mostrami dove hai visto quei soldati inglesi.";
			link.l1 = "Si nascondono in una grotta nella giungla, come volgari masnadieri.";
			link.l1.go = "hol_officer_1";
		break;
		
		case "hol_officer_1":
			dialog.text = "Avanti, ti seguiamo!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_HollandBattleMarch");
		break;
		
		case "hol_officer_2":
			PlaySound("Voice\English\hol_gov_quest.wav");
			dialog.text = "Aspetta, capitano! Hai detto d’aver incontrato le spie laggiù – vicino all’entrata della grotta?";
			link.l1 = "Sì. Li ho visti entrare poco dopo avermi rivolto la parola.";
			link.l1.go = "hol_officer_3";
		break;
		
		case "hol_officer_3":
			dialog.text = " Molto probabilmente sono ancora là dentro. Se ci buttiamo tutti insieme, si rifugeranno nella grotta. Sarebbe un inferno stanarli da lì... Dobbiamo giocar d'astuzia. Capitano, vai tu da solo a distrarli. Io e i miei uomini ci infileremo in quel pozzo secco dietro l'angolo. Da lì si entra dritti nella grotta. Quei cani non si accorgeranno di nulla finché non li avremo alle spalle.\nTu entra, e se le spie sono ancora lì, attaccaci discorso, fai domande sceme e tienili occupati. Quando sentirai che tutta la loro attenzione è tua – impreca come un vero filibustiere, più sporco che puoi. Sei un marinaio, ti verrà naturale. Quello sarà il nostro segnale. Due dei miei staranno di guardia all'ingresso per tagliar loro la fuga. Li prenderemo.";
			link.l1 = "Il tuo piano mi pare una gran minaccia per la mia pellaccia. A occhio e croce, sarò io il primo che vorranno mandare al Creatore.";
			link.l1.go = "hol_officer_4";
		break;
		
		case "hol_officer_4":
			dialog.text = "Non temere, capitano. Il tuo compito è urlare a squarciagola appena vedrai la banda dei predoni nemici. Se ti attaccano, scappa e continua a strillare. I miei uomini sono ben addestrati, perciò non ti preoccupare, abbatteranno quei cani spioni prima che ti succeda qualcosa.";
			link.l1 = "Farebbero meglio. Sto per entrare là dentro.";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_HollandBattlePosition");
		break;
		
		case "hol_officer_5":
			PlaySound("Voice\English\hol_gov_common.wav");
			dialog.text = "Erano dei bastardi tosti... Ben fatto, capitano, quei cani inglesi sono sistemati. Il nostro comandante e il governatore ne saranno soddisfatti.";
			link.l1 = "Ci hai messo il tuo bel tempo, signor capitano...";
			link.l1.go = "hol_officer_6";
		break;
		
		case "hol_officer_6":
			dialog.text = "Dà la colpa alla corda, c’era un secchio legato in fondo che faceva un baccano infernale. Dovevamo stare all’erta.";
			link.l1 = "Già... la corda. Che importa. Una delle tue pattuglie scomparse è legata laggiù tra i cespugli. Dovrebbero essere ancora vivi.";
			link.l1.go = "hol_officer_7";
		break;
		
		case "hol_officer_7":
			dialog.text = "Ci penso io a loro. Tu dovresti andare in città a riposarti un po'. Domani fai visita al nostro governatore, per allora avrà già ricevuto il mio rapporto con una lode scintillante sul tuo conto.";
			link.l1 = "Lo farò. Buon vento, signor mio.";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_HollandBattleRest");
		break;
		
		case "monk":
			DelLandQuestMark(npchar);
			DelLandQuestMarkToPhantom();
			if (GetCharacterIndex("marigojailoff") != -1)
			{
				DelLandQuestMark(characterFromId("marigojailoff"));
			}
			pchar.questTemp.FMQN = "way_eng_2";
			dialog.text = "Cosa posso fare per te, figliolo?";
			link.l1 = "Salve, reverendo, tanto per sapere... quanto tempo fa hanno confessato quei marinai prigionieri?";
			link.l1.go = "monk_1";
		break;
		
		case "monk_1":
			dialog.text = "Ieri sera, mio figlio... (sussurrando) Suppongo tu sappia che il piano è stato tradito?";
			link.l1 = "Altrimenti non sarei qui. Il tenente Casper Gratton e i suoi uomini sono nella giungla in questo momento. Sono tutti vestiti da soldati olandesi, ma abbiamo bisogno di rinforzi: le guardie della prigione li stanno aspettando.";
			link.l1.go = "monk_2";
		break;
		
		case "monk_2":
			dialog.text = "(ad alta voce) Ho pregato ogni giorno per salvare la sua anima anglicana dalla dannazione! (sottovoce) Ho un piano, ma mi servono due dozzine di dobloni d’oro per procurarmi tutto il necessario.";
			link.l1 = "Piano costoso. A cosa servono tutti quei dobloni?";
			link.l1.go = "monk_3";
		break;
		
		case "monk_3":
			dialog.text = "Fare la guardia in prigione è una noia mortale. Per tirare su il morale, l’ufficiale ordina del vino ogni sera per accompagnare la cena. Il vino arriva da un magazzino a cui ho accesso. In città c’è una zingara che mi deve dei favori, preparerà una pozione per farli dormire. Mi basta comprare qualche bottiglia di buon vino, aggiungerci la pozione e sostituire le bottiglie nel magazzino. Ecco perché mi serve l’oro.";
			if (PCharDublonsTotal() >= 24)
			{
				link.l1 = "Ho i dobloni. Prendili.";
				link.l1.go = "monk_4";
			}
			else
			{
				link.l1 = "Lascia che torni alla mia nave e ne recuperi un po’ per te.";
				link.l1.go = "monk_wait";
			}
		break;
		
		case "monk_wait":
			DialogExit();
			npchar.dialog.currentnode = "monk_repeat";
		break;
		
		case "monk_repeat":
			dialog.text = "Ah, figliolo, hai portato la 'donazione' di cui abbiamo parlato?";
			if (PCharDublonsTotal() >= 24)
			{
				link.l1 = "Sì, ecco.";
				link.l1.go = "monk_4";
			}
			else
			{
				link.l1 = "Lo avrò presto, non temere...";
				link.l1.go = "monk_wait";
			}
		break;
		
		case "monk_4":
			RemoveDublonsFromPCharTotal(24);
			dialog.text = "Splendido. Vieni a trovarmi domani alla stessa ora – ti racconterò com’è andata.";
			link.l1 = "Molto bene...";
			link.l1.go = "monk_5";
		break;
		
		case "monk_5":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("FMQ_Nevis", "18");
			pchar.quest.FMQN_monk.win_condition.l1 = "Timer";
			pchar.quest.FMQN_monk.win_condition.l1.date.hour  = 6.0;
			pchar.quest.FMQN_monk.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQN_monk.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQN_monk.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQN_monk.function = "FMQN_EnglandMonkPlan";
			pchar.quest.FMQN_fail.win_condition.l1 = "Timer";
			pchar.quest.FMQN_fail.win_condition.l1.date.hour  = 11.0;
			pchar.quest.FMQN_fail.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQN_fail.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQN_fail.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQN_fail.function = "FMQN_EnglandFail";
			pchar.questTemp.FMQN = "way_eng_3";
		break;
		
		case "monk_6":
			DelLandQuestMark(npchar);
			pchar.quest.FMQN_fail.over = "yes";
			dialog.text = "Salute a te, figliolo.";
			link.l1 = "Anche a te, reverendo. Novità dai sette mari?";
			link.l1.go = "monk_6x";
		break;
		
		case "monk_6x":
			dialog.text = "Sì. Fatto. Il vino è stato 'condito' e stanotte le guardie avranno un trattamento speciale. Cenano alle nove, entro mezzanotte dormiranno come sassi. È la tua unica occasione, niente seconde possibilità. Sta' all'erta, non puoi fidarti ciecamente del travestimento da olandese.";
			link.l1 = "Capito. Non perdiamo tempo. Addio.";
			link.l1.go = "monk_7";
		break;
		
		case "monk_7":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("FMQ_Nevis", "20");
			sld = CharacterFromID("FMQN_seafox_1");
			sld.dialog.currentnode = "seafox_26";
			LAi_CharacterEnableDialog(sld);
			sld.talker = 9;
			AddLandQuestMark(sld, "questmarkmain");
			pchar.quest.FMQN_fail1.win_condition.l1 = "Timer";
			pchar.quest.FMQN_fail1.win_condition.l1.date.hour  = 20.0;
			pchar.quest.FMQN_fail1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.FMQN_fail1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.FMQN_fail1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.FMQN_fail1.function = "FMQN_EnglandFail";
			pchar.questTemp.FMQN = "way_eng_4";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

// Addon-2016 Jason, французские миниквесты (ФМК) Тортуга
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
			dialog.text = "Un bug lampante. Avvisa i diavoli che han fatto sto gioco.";
			link.l1 = "Oh, lo farò.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "girl":
			DelMapQuestMarkCity("Tortuga");
			LAi_SetImmortal(npchar, false);
			DelLandQuestMark(npchar);
			LAi_RemoveLoginTime(npchar);
			FMQT_FillChest();
			PlaySound("Voice\English\Girls_1.wav");
			dialog.text = "Oh, salve monsieur! Benvenuto a Tortuga! Capitani così nobili come voi sono ospiti rari da queste parti...";
			link.l1 = "Saluti, mademoiselle. Vi ringrazio per il caloroso benvenuto. Ma come mai? Pensavo che un porto così importante fosse sempre meta di gentiluomini di ventura ben più illustri di me.";
			link.l1.go = "girl_1";
		break;
		
		case "girl_1":
			dialog.text = "Ah monsieur... Siete chiaramente un novellino, ho ragione? Vedrete presto da soli. Non avete idea di quanto sia arduo trovare uomini degni per un ballo al palazzo del governatore. Forse potreste accompagnarmi...?";
			link.l1 = "Come posso rendermi utile a una dama così avvenente?";
			link.l1.go = "girl_2";
		break;
		
		case "girl_2":
			dialog.text = "Per mille balene, che cavaliere! (ridacchia) Forse, potresti farci visita stasera alle sei? La moglie del nostro governatore organizza spesso festicciole informali nei quartieri della servitù al palazzo. È raro che si presenti una compagnia così interessante per questi eventi. Che ne dici, verrai? Ti prego, sarebbe un vero piacere per noi.";
			link.l1 = "Sarebbe per me un onore, mademoiselle. Verrò a trovarvi stanotte.";
			link.l1.go = "girl_3";
			link.l2 = "Perdonatemi, mademoiselle, ma ho affari urgenti da sbrigare. Un'altra volta, forse?";
			link.l2.go = "girl_exit";
		break;
		
		case "girl_exit":
			dialog.text = "Peccato. Dovrò trovare qualcun altro che tenga compagnia a me e alle mie amiche... Addio.";
			link.l1 = "Addio.";
			link.l1.go = "girl_exit_1";
		break;
		
		case "girl_exit_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 40.0);
			npchar.lifeday = 0;
			FMQT_ClearChest();
		break;
		
		case "girl_3":
			dialog.text = "Grazie! Ti giuro, questa sarà una notte che non scorderai mai, messere! Au revoir!";
			link.l1 = "Ci si rivede...";
			link.l1.go = "girl_4";
		break;
		
		case "girl_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 40.0);
			npchar.lifeday = 0;
			pchar.questTemp.FMQT = "begin_serveroom";
			FMQT_Begin();
			AddQuestRecord("FMQ_Tortuga", "1");
		break;
		
		case "girl_5":
			DelMapQuestMarkCity("Tortuga");
			LAi_SetImmortal(npchar, false);
			DelLandQuestMark(npchar);
			LAi_RemoveLoginTime(npchar);
			FMQT_FillChest();
			PlaySound("Voice\English\Girls_1.wav");
			dialog.text = "Ehilà, marinaio! Che vento fortunato ti ha portato qui oggi? È raro vedere uomini così gagliardi a Tortuga.";
			link.l1 = "Salve anche a te, madamigella, rischi davvero di farmi arrossire con i tuoi complimenti. Sono il capitano della mia nave e un uomo assai indaffarato, ma sono certo che quest’isola saprà offrire abbastanza per tenere vivo l’interesse di un vagabondo come me.";
			link.l1.go = "girl_6";
		break;
		
		case "girl_6":
			dialog.text = "(risatina) Oh sì, signore, sono certa che possiamo aiutarla con questo! Tortuga ha sempre qualcosa da offrire. E anch’io... Ah, son capace di far quasi *qualsiasi cosa* dopo aver sentito una bella storia di mare. Le adoro, davvero! Un capitano una volta mi raccontò una storia incredibile su come riuscì a scampare a essere abbandonato su un’isola deserta costruendo una zattera con delle tartarughe marine. Che impavido! E voi, potreste?";
			link.l1 = "Potrei cosa?";
			link.l1.go = "girl_7";
		break;
		
		case "girl_7":
			dialog.text = "(ridacchia) Riusciresti a costruire una zattera con delle tartarughe marine?";
			link.l1 = "Posso fare di meglio. Una volta, insieme a un apprendista fuggiasco, ho catturato la nave più veloce della Marina Inglese usando solo un'accetta. E riesco pure a trattener il fiato per dieci minuti. Vuoi vedere?";
			link.l1.go = "girl_8";
		break;
		
		case "girl_8":
			dialog.text = "Forse più tardi. Lavoro come serva nel palazzo del nostro governatore. Vieni lì entro le sei di stasera e troverai me e la mia amica nel padiglione. Potrai raccontarci tutte le tue avventure allora...";
			link.l1 = "Pare proprio un invito a una sfilata che non posso rifiutare. Ci vediamo alle sei stasera.";
			link.l1.go = "girl_9";
			link.l2 = "Intrufolarsi nel palazzo del governatore? Roba troppo grossa per il mio sangue, amico. Passo la mano, tesoro. Cercami alla taverna se vuoi la compagnia di un vero uomo. Yo ho ho!";
			link.l2.go = "girl_exit_2";
		break;
		
		case "girl_exit_2":
			dialog.text = "Pf-f. Bah, troverò un uomo più grande e più gagliardo di te. In fondo, il tuo brachettone pare proprio misero. Addio e non tornare.";
			link.l1 = "Persino un vascello da guerra sembrerebbe una scialuppa solcando il tuo Passaggio Sopravvento.";
			link.l1.go = "girl_exit_1";
		break;
		
		case "girl_9":
			dialog.text = "Non vedo l’ora!";
			link.l1 = "...";
			link.l1.go = "girl_10";
		break;
		
		case "girl_10":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 40.0);
			npchar.lifeday = 0;
			pchar.questTemp.FMQT = "begin_bedroom";
			FMQT_Begin();
			AddQuestRecord("FMQ_Tortuga", "2");
		break;
		
		case "wife":
			DelLandQuestMark(npchar);
			PlaySound("Voice\English\LE\Marselina\Marselina_Levasser_01.wav");
			dialog.text = "Ah, eccoti qui! Capitano "+GetFullName(pchar)+"! Son così lieto di far la vostra conoscenza, è da un pezzo che non mi onorava un visitatore di sì nobile lignaggio e rango!";
			link.l1 = "È un grande onore e piacere per me essere qui in vostra compagnia, madama. Ma che dire degli altri ospiti? Sono forse arrivato troppo presto?";
			link.l1.go = "wife_1";
		break;
		
		case "wife_1":
			dialog.text = "Oh, sono indisposti e non possono venire. Ma lasciamoli perdere, beviamo vino e chiacchieriamo... Ah, se solo sapessi quanto mi annoio e mi sento sola qui! Tortuga è una lurida tana piena di feccia, mascalzoni e pirati! Pirati! E finalmente, un vero gentiluomo nella mia casa! Vorrei che mio marito facesse più affari con uomini della vostra levatura e ingegno! Ma no, solo pirati, pirati dappertutto! Avete sentito parlare di quella nuova moda che spopola a Parigi alla corte di Sua Maestà? Che ne pensate?";
			link.l1 = "Mi dispiace, la mia opinione su cosa, esattamente? I pirati? O la moda?";
			link.l1.go = "wife_2";
		break;
		
		case "wife_2":
			dialog.text = "Oh signore, mi capite così bene! Non posso nemmeno crederci. Mio marito mi passa solo qualche spicciolo mentre si riempie le tasche d’oro coi suoi pirati, vi rendete conto? Pirati! Devo ordinare i vestiti che arrivano fin qui, in questa lurida tana, e quando finalmente giungono sono già passati di moda da sei mesi! Come può una dama del mio rango indossare simili stracci? Ah, quanto desidero vedere e sfoggiare le mode di Parigi! Pensate che sarei incantevole con quei vestiti?";
			link.l1 = "Madame, siete incantevole. Non vi servono mode di Parigi per mostrarlo, ogni uomo di quest’isola lo vede benissimo.";
			link.l1.go = "wife_3";
		break;
		
		case "wife_3":
			dialog.text = "Siete troppo gentile con me... Capitano, devo confessarvi che sono in grande difficoltà. Ma aiuterete una povera donna, vero?";
			link.l1 = "Certo, madama. Qualsiasi cosa desideriate.";
			link.l1.go = "wife_4";
		break;
		
		case "wife_4":
			dialog.text = "Attento lì, monsieur capitano, o perderò la testa! (risatina civettuola) Mio marito ormai non mi dà nemmeno uno scudo. Quella bestia porta a casa sgualdrine di basso rango e a me non rivolge neppure lo sguardo!\nSo dove nasconde parte del suo bottino mal guadagnato, è in uno scrigno nel suo ufficio. Quel denaro mi spetta, per diritto di moglie e di donna. Aiutami a riprendermi ciò che mi deve e sarai ricompensato... Con oro e... altri piaceri squisiti.";
			link.l1 = "Questa è un’offerta interessante. D’accordo, madama, vi aiuterò. Dove si trova questo forziere e come si apre?";
			link.l1.go = "wife_5";
			link.l2 = "Molto bene, madame, vi porterò il contenuto del forziere. Prenderemo il denaro e avremo una piacevole 'conversazione' insieme dopo. Qual uomo saprebbe rifiutare simile proposta? Dov’è questo forziere e come si apre?";
			link.l2.go = "wife_6";
			link.l3 = "Madama, cercate di sedurmi. Mi duole, ma l’onore mio esige che io rifiuti la vostra offerta. Vi compatisco, meritereste di meglio, ma dovrete trovarvi un altro interprete per la vostra commedia.";
			link.l3.go = "wife_exit";
		break;
		
		case "wife_exit":
			dialog.text = "Peccato. Allora non abbiamo più nulla da dirci, monsieur. Vai via e ricorda: se osi sussurrare una parola di questo a mio marito, te ne pentirai amaramente!";
			link.l1 = "Addio.";
			link.l1.go = "wife_exit_1";
		break;
		
		case "wife_exit_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "questTemp.FMQT.Common");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			pchar.questTemp.FMQT = "huber";
			pchar.quest.FMQT_late1.win_condition.l1 = "Timer";
			pchar.quest.FMQT_late1.win_condition.l1.date.hour  = 18.0;
			pchar.quest.FMQT_late1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQT_late1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQT_late1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQT_late1.function = "FMQT_HuberTime";
			AddQuestRecord("FMQ_Tortuga", "4");
		break;
		
		case "wife_5":
			pchar.questTemp.FMQT.Honour = "true"; // вар 1
			dialog.text = "Non me l’aspettavo da te... Il forziere... Lascialo stare per ora, prima dobbiamo trovare la chiave di riserva che è stata rubata da un lurido pirata. In questo momento si sta ubriacando come un maiale in una bettola qui vicino. Sbrigati e riportami quella chiave. Ti aspetto.";
			link.l1 = "Allora, niente tempo da perdere!";
			link.l1.go = "wife_7";
		break;
		
		case "wife_6":
			pchar.questTemp.FMQT.Bed = "true"; // вар 2 
			dialog.text = "Non te ne pentirai, capitano. Prima di tutto dobbiamo trovare una chiave duplicata che fu rubata da un lurido pirata. Al momento si sta sbronzando in una bettola locale, beve come un porco. Muoviti e riportami quella chiave duplicata. Ti aspetterò.";
			link.l1 = "Allora, niente perdite di tempo!";
			link.l1.go = "wife_7";
		break;
		
		case "wife_7":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "FMQT_PirateInTavern", 10.0);
			pchar.quest.FMQT_late2.win_condition.l1 = "Timer";
			pchar.quest.FMQT_late2.win_condition.l1.date.hour  = 0.0;
			pchar.quest.FMQT_late2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQT_late2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQT_late2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQT_late2.function = "FMQT_TavernTime";
			AddQuestRecord("FMQ_Tortuga", "6");
		break;
		
		case "wife_8":
			DelLandQuestMark(npchar);
			PlaySound("Voice\English\LE\Marselina\Marselina_Levasser_01.wav");
			dialog.text = "Capitano "+GetFullName(pchar)+"! Oh oh! Che ci fa un uomo nei miei alloggi privati! Sorpreso, eh? Sei l’unico ospite stasera. (risatina)";
			link.l1 = "Sono sorpreso, madama. Ma non mi dispiace affatto. Si tratta d'affari o di piacere?";
			link.l1.go = "wife_9";
		break;
		
		case "wife_9":
			dialog.text = "Che approccio diretto! Mi piacciono gli uomini come te. Ho una proposta d'affari per te, capitano. Saprò ricompensare i tuoi sforzi se ci riuscirai.";
			link.l1 = "Continua.";
			link.l1.go = "wife_10";
		break;
		
		case "wife_10":
			dialog.text = "Ah... Mio marito ha uno scrigno pieno di soldi e gioielli. Lo detesto, e per le mie pene voglio una borsa più pesante.";
			link.l1 = "Madame, siete splendida. Non avete bisogno di gioielli o mode di Parigi per mostrarlo, è già chiaro a ogni uomo di Hispaniola.";
			link.l1.go = "wife_11";
		break;
		
		case "wife_11":
			dialog.text = "Sei troppo gentile con me... Capitano, devo confessare, sono nei guai seri. Aiuterai una donna in difficoltà??";
			link.l1 = "Certamente, madama. L'onore lo impone. A vostro comando.";
			link.l1.go = "wife_12";
		break;
		
		case "wife_12":
			dialog.text = "Attento lì, monsieur capitano, o perderò la testa! (risatina civettuola) Mio marito ormai non mi dà nemmeno un soldo bucato. Quel bruto porta a casa sgualdrine qualunque e nemmeno si ricorda di me!\nSo dove tiene parte dei suoi sporchi bottini, è in uno scrigno nel suo ufficio. Questi soldi mi spettano, come moglie e come donna. Aiutami a riprendere ciò che mi deve e sarai ricompensato... Con oro e... altri deliziosi piaceri.";
			link.l1 = "D'accordo. Lo farò. Dove si trova questo forziere e come lo apro?";
			link.l1.go = "wife_13";
			link.l2 = "Ah! Nessun dubbio, posso farlo per una dama come te. Non te ne pentirai, mia cara. Prenderemo i soldi e ci godremo dei bei momenti insieme. Dove si trova questo forziere e come lo apro?";
			link.l2.go = "wife_14";
			link.l3 = "Non io, madama. Non sono un gentiluomo da cornificare e derubare un uomo nella stessa notte. Almeno non così, no. Cercatevi un altro attore per questa farsa.";
			link.l3.go = "wife_exit_2";
		break;
		
		case "wife_13":
			pchar.questTemp.FMQT.Honour = "true"; // вар 1
			dialog.text = "Oh... Mi piaci sempre di più... Prima di tutto, dobbiamo recuperare una chiave duplicata che ci ha soffiato un lurido pirata. Sta sbevazzando in una bettola locale, ubriacandosi come un maiale. Sbrigati e riportami quel duplicato. Ti aspetterò.";
			link.l1 = "Niente perdite di tempo, allora!";
			link.l1.go = "wife_7";
		break;
		
		case "wife_14":
			pchar.questTemp.FMQT.Bed = "true"; // вар 2 
			dialog.text = "Calmati, monsieur, avrai tempo per sbronzarti più tardi. (risatina) Prima, dobbiamo recuperare una chiave duplicata che è stata rubata da un lurido pirata. Quello sfaticato ora s’abbuffa di rum in una taverna locale, bevendo come un porco. Sbrigati e porta la copia qui da me. Ti aspetto. Sei sicuro di saperla cavare?";
			link.l1 = "Non dubitare di me, sono già in rotta.";
			link.l1.go = "wife_7";
		break;
		
		case "wife_exit_2":
			dialog.text = "Brutto puritano! Sparisci dalla mia vista! E non ti azzardare a raccontare nulla a mio marito, o te ne pentirai amaramente!";
			link.l1 = "Addio, tesoruccio.";
			link.l1.go = "wife_exit_1";
		break;
		
		case "wife_15":
			DelLandQuestMark(npchar);
			pchar.quest.FMQT_late3.over = "yes";
			dialog.text = "Capitano! Hai preso la chiave?";
			link.l1 = "Sì, ce l'ho. Dov'è il forziere?";
			link.l1.go = "wife_16";
		break;
		
		case "wife_16":
			dialog.text = "Oh! Il mio spregevole marito avrà finalmente ciò che si merita? Sei davvero un uomo straordinario, capitano! Hai un grande avvenire davanti a te, lo sai? Lascia perdere il forziere. Me ne occuperò io. Vieni a trovarmi domani per riscuotere la tua ricompensa. Non te ne pentirai, capitano...";
			link.l1 = "D’accordo. Fa’ come ti pare. Non vedo l’ora di rivederti domani.";
			link.l1.go = "wife_17";
			link.l2 = "No, sono un uomo indaffarato e non ho tempo da perdere aspettando. Perché aspettare? Dimmi solo cosa devo fare e ci penso io. Non posso permettere che una donna così bella rovini quelle mani delicate trafficando con serrature e chiavi.";
			link.l2.go = "wife_18";
		break;
		
		case "wife_17":
			RemoveItems(pchar, "kaleuche_key", 1);
			ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key");
			dialog.text = "Vieni a trovarmi entro le sei, mio valoroso cavaliere...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQT_Deceive");
		break;
		
		case "wife_18":
			dialog.text = "Ne sei certo? Potrebbe essere pericoloso per te. Perché vuoi rischiare la pellaccia, capitano?";
			link.l1 = "Va bene. Che sia come vuoi tu. Non vedo l’ora di rivederti domani.";
			link.l1.go = "wife_17";
			link.l2 = "Ho già preso la mia decisione. Che cosa devo fare, di preciso?";
			link.l2.go = "wife_19";
		break;
		
		case "wife_19":
			dialog.text = "Un cuore di leone!... Vai nell'ufficio di mio marito, troverai il baule lì. Usa la chiave di riserva. A quest'ora della notte lassù non c'è nessuno, quindi prenditi il tuo tempo. Dentro quel baule ci sono... diamanti. Un bel mucchio. Prendili tutti e torna da me. Ti aspetterò. Non tradire la mia fiducia... ti prego.";
			link.l1 = "Tornerò presto.";
			link.l1.go = "wife_20";
		break;
		
		case "wife_20":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("FMQ_Tortuga", "11");
			sld = &Locations[FindLocation("Tortuga_townhallRoom")];
			sld.private2.key = "kaleuche_key"; // допуск к сундуку
			pchar.questTemp.FMQT = "chest";
		break;
		
		case "wife_21":
			DelLandQuestMark(npchar);
			pchar.quest.FMQT_GemsTimeOver.over = "yes";
			PlaySound("Voice\English\LE\Marselina\Marselina_Levasser_02.wav");
			dialog.text = "Oh, capitano! Io...Tu... È fatto? Oh, e chi diavolo è costui?! A-ah!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQT_MercenAttackRoom");
		break;
		
		case "wife_22":
			dialog.text = "Oh cielo! Capitano, mi avete salvata! Siete... siete il mio eroe! Era lo scagnozzo di mio marito, voleva uccidervi! L'ho supplicato di non farlo! Siete ferito? Avete portato i diamanti?";
			link.l1 = "Ah. Davvero? Tuo marito è un uomo geloso... Che importa. Al diavolo lui, ho io le palle.";
			link.l1.go = "wife_23";
		break;
		
		case "wife_21x":
			DelLandQuestMark(npchar);
			pchar.quest.FMQT_GemsTimeOver.over = "yes";
			PlaySound("Voice\English\LE\Marselina\Marselina_Levasser_02.wav");
			dialog.text = "Oh capitano! Io... Tu... È fatta?";
			link.l1 = "C'è stato un piccolo intoppo, ma ormai è tutto sistemato. Perché siete pallida, madama? Vi sentite bene? Ho le gemme, questo dovrebbe rallegrarvi, non è vero?";
			link.l1.go = "wife_23";
		break;
		
		case "wife_23":
			dialog.text = "Grazie al Cielo! Sono vendicata! Mio cavaliere! Quanti diamanti c’erano?";
			if (GetCharacterItem(pchar, "jewelry2") >= 100)
			{
				link.l1 = "Il vostro cavaliere è tornato dalla sua avventura con il sacco pieno di bottino. Ne lascerà la metà alla sua dama, così potrà comprarsi le mode più raffinate di Parigi. Ho mantenuto la mia promessa.";
				if (CheckAttribute(pchar, "questTemp.FMQT.Honour")) link.l1.go = "wife_25";
				else link.l1.go = "wife_26";
			}
			else
			{
				link.l1 = "Oh, di diamanti ce n'erano a bizzeffe ma tu non vedrai neanche una scheggia. Hai pagato un sicario per farmi fuori, maledetta baldracca! Davvero pensavi che avrei diviso con te dopo tutto questo? Prova solo a fiatare, e tuo marito scoprirà del tuo piano per derubarlo e fargli le corna. Quindi tieni la bocca chiusa.";
				link.l1.go = "wife_24";
			}
		break;
		
		case "wife_24":
			PlaySound("Voice\English\LE\Marselina\Marselina_Levasser_03.wav");
			dialog.text = "Furfante! Bastardo! Non la passerai liscia!";
			link.l1 = "Aye, questa l'ho già sentita, vecchio mio.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQT_FinalNoJewelry");
		break;
		
		case "wife_25":
			RemoveItems(pchar, "jewelry2", 100);
			Log_Info("You have given diamonds");
			PlaySound("interface\important_item.wav");
			dialog.text = "Tu non sei come... gli altri. Ottieni sempre ciò che vuoi. Hai un futuro brillante davanti a te. So che sei un uomo occupato ma... Resterai con me per un po’? Nessuno ci disturberà, te lo prometto.";
			link.l1 = "Ho sempre tempo per una dama tanto bella come te. Vuoi che apra una bottiglia del vino di tuo marito?";
			link.l1.go = "wife_sex";
		break;
		
		case "wife_sex":
			DialogExit();
			LAi_SetActorType(npchar);
			pchar.questTemp.HorseQty = sti(pchar.questTemp.HorseQty) + 1;
			DoQuestCheckDelay("PlaySex_1", 1.0);
			
			// Rebbebion, для "Путеводной звезды"
			pchar.questTemp.FMQT.GiveDiamonds = true;
			pchar.questTemp.FMQT.Marceline = "Fuck"; 
		break;
		
		case "wife_26":
			RemoveItems(pchar, "jewelry2", 100);
			Log_Info("You have given diamonds");
			PlaySound("interface\important_item.wav");
			dialog.text = "Penso di poterne fare a meno. Qui non mancano certo modi per spendere denaro. Così tanti uomini aitanti e valorosi a Tortuga... Grazie di tutto, capitano. Sappia solo, la prego, tenga la bocca chiusa su questa faccenda o mio marito la farà finire appesa a una forca. Non è certo un brav’uomo. Addio.";
			link.l1 = "Così, senza altro? È stata un’esperienza istruttiva. Addio, madame, le consiglio di tenere la bocca chiusa anche su questo, non sono certo un uomo perbene. Ma questo lo sapeva già, vero?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQT_FinalNoSex");
			
			// Rebbebion, для "Путеводной звезды"
			pchar.questTemp.FMQT.GiveDiamonds = true;
			pchar.questTemp.FMQT.Marceline = "NoFuck"; 
		break;
		
		case "wife_27":
			PlaySound("Voice\English\Girls_2.wav");
			dialog.text = "Chi sei tu e che diavolo ci fai qui?";
			link.l1 = "Che diavolo stai combinando? Avevamo un accordo...";
			link.l1.go = "wife_28";
		break;
		
		case "wife_28":
			dialog.text = "Che affare, monsieur? Sono una donna sposata, non faccio affari con altri uomini! Uscite dalle mie stanze subito o chiamo mio marito e le sue guardie!";
			link.l1 = "Così, eh? Va bene, credo proprio che illuminerò il tuo buon marito, in tal caso!";
			link.l1.go = "wife_29";
		break;
		
		case "wife_29":
			dialog.text = "Vattene subito, mascalzone insolente, o i miei uomini ti butteranno nel pozzo di Fort La Roche! Delle tue minacce non me ne faccio nulla! Fuori dai piedi!";
			link.l1 = "...";
			link.l1.go = "wife_30";
		break;
		
		case "wife_30":
			DialogExit();
			DoQuestReloadToLocation("Tortuga_town", "reload", "reload3", "FMQT_FinalFail");
			pchar.questTemp.FMQT.Marceline = "Deception"; // Rebbebion, для "Путеводной звезды"
		break;
		
		case "pirate":
			DelLandQuestMark(npchar);
			PlaySound("Voice\English\tavern\Pyanici-03.wav");
			pchar.quest.FMQT_late2.over = "yes";
			FreeSitLocator("Tortuga_tavern", "sit_base2");
			dialog.text = "Chi sei tu? Ah, poco importa. Non fidarti mai delle donne, compare. Come dice la Sacra Scrittura... anche la più sciocca delle sgualdrine può trascinarti all’inferno coi suoi giochetti da femmina. Siediti, amico, beviamo qualcosa!";
			link.l1 = "Con gran piacere!";
			link.l1.go = "pirate_1x";
		break;
		
		case "pirate_1x":
			DialogExit();
			LAi_Fade("", "");
			ChangeCharacterAddressGroup(pchar, "Tortuga_tavern", "sit", "sit_base2");
			LAi_SetSitType(pchar);
			npchar.Dialog.currentnode = "pirate_1";
			LAi_SetActorType(npchar);
			LAi_ActorSetSitMode(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 2.0);
		break;
		
		case "pirate_1":
			PlaySound("Voice\English\tavern\Pyanici-05.wav");
			dialog.text = "Che diamine guardi? Versa da bere, forza!!";
			link.l1 = "Alla tua!.. Ehi compare, non ho tempo da perdere qui. Mi serve quella chiave doppione che hai tu, sai bene di cosa parlo. Dammi quella e ognuno per la sua strada: tu continuerai a tracannare e io a salvare donzelle nei guai.";
			link.l1.go = "pirate_2";
		break;
		
		case "pirate_2":
			dialog.text = "Ahi, compare! Ma hai le orecchie tappate o cosa? Sembri più sveglio di quel che sei... a lavorare per quella sgualdrina. Sai chi è suo marito? Di recente, il Governatore Levasseur ha mandato il suo fedele negro Kampacho a 'parlare' con un mercante locale, persona assai stimata. Quel nero ha massacrato il poveraccio a bastonate dentro la sua stessa bottega! Pare che il mercante avesse rivolto una qualche piccola mancanza di rispetto alla moglie del governatore, forse durante un ballo o roba simile. E quella stessa puttana mi ha sedotto coi suoi sguardi e coi dobloni di lui.\nLa chiave doppia esiste, sì. Ero un discreto scassinatore in Francia, roba da ragazzi per me. Se non fosse stato per la figlia del comandante di Lione... non avrei mai preso la via della pirateria. Bah! Al diavolo tutto!";
			link.l1 = "Tutto ciò è assai triste, ma veniamo agli affari. Dov’è la chiave?";
			link.l1.go = "pirate_3";
		break;
		
		case "pirate_3":
			dialog.text = "Ascolti bene? Io sono fuori dai giochi, compare! Ho avuto abbastanza sale in zucca per capire che tira una brutta aria! Me ne vado da questo dannato posto appena la mia nave sarà pronta a mollare gli ormeggi. Vuoi la chiave? Pagami. Non fare il taccagno, ché a breve il denaro non ti servirà più a nulla.";
			link.l1 = "Sai, hai ragione. Non voglio essere il giocattolo di una donna. Grazie per il consiglio e che il mare ti sia propizio!";
			link.l1.go = "pirate_4";
			link.l2 = "Pagare a te? Tu? Sei un misero ladro e un codardo. Dovevi restare in quella fogna di Lione. Chissà, magari il comandante locale avrebbe avuto pietà e preso un ladro degenere come genero. Io, di certo, non ti farò nessuno sconto. Puoi darmi la chiave di tua spontanea volontà o costringermi a fartela sputare, scegli tu.";
			link.l2.go = "pirate_5";
			link.l3 = "(sospira) Quanto vuoi?";
			link.l3.go = "pirate_6";
		break;
		
		case "pirate_4":
			dialog.text = "Ragazzo sveglio, questa sì che è una scelta saggia, compare. Buona fortuna. Che tu possa trovare una donna vera e affettuosa, un giorno. Meglio se rossa o bionda, eh, dico bene?";
			link.l1 = "Addio, compagno...";
			link.l1.go = "pirate_exit";
		break;
		
		case "pirate_exit":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_Fade("", "");
			ChangeCharacterAddressGroup(pchar, "Tortuga_tavern", "tables", "stay8");
			LAi_SetPlayerType(pchar);
			pchar.questTemp.FMQT = "huber";
			pchar.quest.FMQT_late1.win_condition.l1 = "Timer";
			pchar.quest.FMQT_late1.win_condition.l1.date.hour  = 18.0;
			pchar.quest.FMQT_late1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQT_late1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQT_late1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQT_late1.function = "FMQT_HuberTime";
			AddQuestRecord("FMQ_Tortuga", "9");
		break;
		
		case "pirate_5":
			dialog.text = "Mi offendi! Sfodera la lama, bastardo!";
			link.l1 = "Vediamo quanto sei bravo ad aprire casseforti senza braccia!";
			link.l1.go = "pirate_duel";
		break;
		
		case "pirate_duel":
			DialogExit();
			LAi_SetSitType(npchar);
			// ключ квестовый от Калеуче - вернуть назад
			GiveItem2Character(npchar, "kaleuche_key");
			ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key_FMQT");
			i = makeint(MOD_SKILL_ENEMY_RATE/4);
			pchar.questTemp.FMQT = "duel";
			PChar.questTemp.duel.enemy = NPChar.id;
			if (MOD_SKILL_ENEMY_RATE > 2) PChar.questTemp.duel.enemyQty = i;
			AddDialogExitQuestFunction("Duel_Prepare_Fight");
		break;
		
		case "pirate_6":
			dialog.text = "Sei un vero uomo d’affari, te lo concedo. Potresti anche farcela. Cinquanta dobloni. Sul tavolo.";
			link.l1 = "Cinquanta dobloni d’oro? Per un pezzo di stagno? Che mi prenda il diavolo. Metti subito la chiave sul tavolo.";
			link.l1.go = "pirate_7";
			if (PCharDublonsTotal() >= 50)
			{
				link.l2 = "Bel prezzo... Va bene. Prendili.";
				link.l2.go = "pirate_8";
			}
			else
			{
				link.l2 = "Bel prezzo... Va bene. Li porterò presto. Resta qui.";
				link.l2.go = "pirate_wait";
			}
		break;
		
		case "pirate_wait":
			DialogExit();
			AddLandQuestMark(npchar, "questmarkmain");
			LAi_SetSitType(npchar);
			npchar.Dialog.currentnode = "pirate_dublon";
			LAi_Fade("", "");
			ChangeCharacterAddressGroup(pchar, "Tortuga_tavern", "tables", "stay8");
			LAi_SetPlayerType(pchar);
		break;
		
		case "pirate_dublon":
			NextDiag.TempNode = "pirate_dublon"; // mitrokosta правка явного бага
			dialog.text = "Hai portato cinquanta dobloni?";
			link.l1 = "Sai, credo che tu possa cavartela anche senza di loro. La chiave. Sul tavolo.";
			link.l1.go = "pirate_7";
			if (PCharDublonsTotal() >= 50)
			{
				link.l2 = "Già. Prendili.";
				link.l2.go = "pirate_8";
			}
			else
			{
				link.l2 = "Li sto ancora prendendo.";
				link.l2.go = "exit";
			}
		break;
		
		case "pirate_7":
			dialog.text = "Vuoi ballare, bellezza?";
			link.l1 = "Guiderò io.";
			link.l1.go = "pirate_duel";
		break;
		
		case "pirate_8":
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(50);
			Log_Info("You have given 50 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Bene. Usa il cervello e forse ne uscirai con qualche doblone e la testa sulle spalle. Prendi la chiave e ascolta il mio consiglio. Gratis. La donna di Levasseur è scema come una sogliola, ma si crede furba. Non fidarti di lei. Tieni a bada il tuo uccello e sorveglia le tue tasche. Non è granché come avversaria, ma sta' attento e cerca di non mettere di mezzo il marito.\nUn'ultima cosa: nella sua stanza c’è uno scrigno dove tiene i suoi ninnoli, facile da scassinare. Lì ci metterà la sua parte, hai capito? Buona fortuna per mare, fratello. Ricorda: prima i fratelli, poi le femmine.";
			link.l1 = "Buon vento, compare...";
			link.l1.go = "pirate_9";
		break;
		
		case "pirate_9":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_Fade("", "");
			ChangeCharacterAddressGroup(pchar, "Tortuga_tavern", "tables", "stay8");
			LAi_SetPlayerType(pchar);
			pchar.questTemp.FMQT = "key";
			pchar.questTemp.FMQT.Caution = "true";
			FMQT_KeyNextDay();
			pchar.quest.FMQT_late3.win_condition.l1 = "Timer";
			pchar.quest.FMQT_late3.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.FMQT_late3.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQT_late3.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQT_late3.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQT_late3.function = "FMQT_KeyTime";
			AddQuestRecord("FMQ_Tortuga", "10");
			// ключ квестовый от Калеуче - вернуть назад
			GiveItem2Character(pchar, "kaleuche_key");
			ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key_FMQT");
		break;
		
		case "mercen":
			PlaySound("Voice\English\EvilPirates10.wav");
			dialog.text = "Maledizione! Non me l’aspettavo... al diavolo quella donna! Il mio padrone mi aveva detto di star lontano da tipi come lei. Ma il dovere è dovere. Alla fine ti prenderò comunque.";
			link.l1 = "Ebbene, compare... Pare proprio che volesse fregare entrambi, non mi stupisce granché. Che senso ha scannarci ancora? Cerchi lavoro? Ne ho uno per te. Hai stoffa, e mi servono braccia come le tue sulla mia ciurma. Pappa calda, brandina, paga fissa, rum e una parte giusta del bottino. Te lo giuro sul mio onore di bucaniere. Che ne dici?";
			//if(CheckCharacterPerk(pchar, "IronWill") || CheckCharacterPerk(pchar, "HT2") || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 34 || GetSummonSkillFromName(pchar, SKILL_FORTUNE) > 20) link.l1.go = "mercen_1";
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 34) link.l1.go = "mercen_1";
			else link.l1.go = "mercen_4";
		break;
		
		case "mercen_1":
			//if(CheckCharacterPerk(pchar, "IronWill")) notification("Iron Will", "IronWill");
			//if(CheckCharacterPerk(pchar, "HT2")) notification("Mimicry", "Mimicry");
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 34) notification("Skill Check Passed", SKILL_LEADERSHIP);
			//if(GetSummonSkillFromName(pchar, SKILL_FORTUNE) > 20) notification("Skill Check Passed", SKILL_FORTUNE);
			dialog.text = "Hai proprio una lingua d’argento e la tua fama ti precede, capitano, su questo non c’è dubbio. Aye, ci sto. Come si chiama la tua nave?";
			link.l1 = "'"+pchar.ship.name+"Parla col nostromo, ti troverà una branda. Benvenuto a bordo!";
			link.l1.go = "mercen_2";
		break;
		
		case "mercen_2":
			dialog.text = "Ah! Sto risalendo la china. Dai un calcio a quella sgualdrina da parte mia.";
			link.l1 = "...";
			link.l1.go = "mercen_3";
		break;
		
		case "mercen_3":
			DialogExit();
			LAi_group_Delete("EnemyFight");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "FMQT_MercenHire", 10.0);
			AddQuestRecord("FMQ_Tortuga", "17");
		break;
		
		case "mercen_4":
			//if(!CheckCharacterPerk(pchar, "IronWill")) notification("Perk check failed", "IronWill");
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 35) notification("Skill Check Failed (35)", SKILL_LEADERSHIP);
			//if(GetSummonSkillFromName(pchar, SKILL_FORTUNE) < 21) notification("Skill Check Failed (21)", SKILL_FORTUNE);
			dialog.text = "Parli bene, ragazzo. Ma non abbastanza da convincere veri lupi di mare a imbarcarsi con te. Ricordalo per la prossima volta... se mai ci sarà.";
			link.l1 = "Provaci pure. Fa’ in fretta, ché ho un appuntamento con una dama.";
			link.l1.go = "mercen_5";
			link.l2 = "Oggi niente seconde possibilità. Sono un uomo occupato, quindi non macchiamo il tappeto. Non ti pagano abbastanza per crepare per una puttana da quattro soldi. Sempre che ti paghino, poi.";
			link.l2.go = "mercen_6";
		break;
		
		case "mercen_5":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FMQT_MercenDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "mercen_6":
			dialog.text = "Hai ragione. Nessuno mi ha pagato... ancora. Ora sistemo io la faccenda. Fai un po' quel che ti pare...";
			link.l1 = "...";
			link.l1.go = "mercen_7";
		break;
		
		case "mercen_7":
			DialogExit();
			LAi_SetCurHPMax(npchar); 
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_group_Delete("EnemyFight");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
			AddQuestRecord("FMQ_Tortuga", "18");
			pchar.questTemp.FMQT.Roomfight = "true";
			FMQT_WifeFinalTalk();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

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
		
		// =================================================================
		// ================== ЭТАП 1. «ЛОЩИНА ВЛЮБЛЁННЫХ» ==================
		// =================================================================
		case "Mary_1":
			dialog.text = ""+pchar.name+", guarda qui!";
			link.l1 = "Zitta, "+npchar.name+", potremmo non essere soli qui.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_3");
		break;
		
		case "Mary_2":
			dialog.text = ""+pchar.name+"!";
			link.l1 = ""+npchar.name+"?   Mi hai seguita passo passo, giusto?";
			link.l1.go = "Mary_3";
		break;
		
		case "Mary_3":
			dialog.text = "E, a quanto pare, non invano, giusto!   Cosa è successo qui?";
			link.l1 = "Se solo avessi saputo, "+npchar.name+", se solo avessi saputo...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_3");
		break;
		
		case "Mary_4":
			dialog.text = "Dio mio...";
			link.l1 = "Sì, poverina, sembra che abbia sofferto molto prima di morire. Non augurerei una fine così a nessuno...";
			link.l1.go = "Mary_5";
		break;
		
		case "Mary_5":
			dialog.text = "E quello chi è, suo marito? Che diamine ci fanno nella giungla?! Non hanno mai sentito parlare degli schiavi fuggiaschi?";
			link.l1 = "Temo che a questa domanda non potranno più rispondere...";
			link.l1.go = "Mary_6";
		break;
		
		case "Mary_6":
			dialog.text = "Pensi che chi l'ha fatto sia ancora qui vicino, giusto?";
			link.l1 = "È molto probabile. Quindi, dovremmo stare più attenti - dobbiamo vederli noi per primi.";
			link.l1.go = "Mary_7";
		break;
		
		case "Mary_7":
			dialog.text = "Troppo tardi, "+pchar.name+". Sembra che ci abbiano già notati. Guarda laggiù.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_6");
		break;
		
		case "Naemnik_1":
			dialog.text = "Ehi, ragazzi, guardate un po'. Qui sembra proprio la valle degli innamorati, giusto? Appena due piccioncini hanno lasciato questo mondo, subito ne sono arrivati altri due a prenderne il posto...";
			if (GetOfficersQuantity(pchar) >= 2)
			{
				link.l1 = "Molto spiritoso.   Ma tu, a quanto pare, non sai contare – a differenza di questi poveracci, noi qui non siamo affatto soli.";
				link.l1.go = "Naemnik_2";
			}
			else
			{
				link.l1 = "Beh, con noi sarà un po' più difficile, credimi...";
				link.l1.go = "Naemnik_4";
			}
		break;
		
		case "Naemnik_2":
			dialog.text = "Direi che pensavate di essere più furbo di loro — ma sarebbe stata una bugia empia. Anche in questo numero non avreste avuto la meglio su quegli stronzi. E la vostra bella avrebbe subito lo stesso destino di quella ragazza ai vostri piedi...";
			link.l1 = "Parli degli schiavi fuggitivi? Questo è uno di loro? Allora siete gente di Bishop, giusto?";
			link.l1.go = "Naemnik_3";
		break;
		
		case "Naemnik_3":
			dialog.text = "A tutte le domande — sì. Per più di due giorni, insieme ai soldati, li abbiamo inseguiti per tutta l'isola. Poi quei bastardi si sono divisi. Una parte si è rifugiata verso la grotta — la guardia li ha seguiti, gli altri sono fuggiti verso la baia. A causa di un'imboscata a mezza miglia a ovest da qui abbiamo perso alcuni ragazzi, e mentre ci riprendevamo e ci riorganizzavamo, loro si sono divertiti con quella stupida...";
			link.l1 = "...";
			link.l1.go = "Naemnik_6_add";
		break;
		
		case "Naemnik_4":
			dialog.text = "Non toccare il tuo stuzzicadenti, pivello – non innervosire me e i miei ragazzi. Vorrei proprio vedere come ti avrebbe aiutato, se ti fossi trovato circondato da una decina di quei bastardi che abbiamo fatto fuori nella baia. Ecco, solo uno è stato fortunato – ma non durerà... Appena quel bastardo finirà nelle mani di Bishop...";
			link.l1 = "Quindi siete i suoi mercenari, giusto?";
			link.l1.go = "Naemnik_5";
		break;
		
		case "Naemnik_5":
			dialog.text = "Beh, di certo non sono soldati di guarnigione, giusto? Se non fosse stato per quei mollaccioni, avremmo preso quei furfanti già ieri – e quell'allocco con la sua mogliettina sarebbero ancora vivi...";
			link.l1 = "Quindi, non è opera vostra...";
			link.l1.go = "Naemnik_6";
		break;
		
		case "Naemnik_6":
			dialog.text = "Per chi ci prendi, eh? Noi, certo, non siamo angeli, ma se ci viene voglia, andiamo al bordello, non...";
			link.l1 = "...";
			link.l1.go = "Naemnik_6_add";
		break;
		case "Naemnik_6_add":
			StartInstantDialog("WildRose_Naemnik_Rab", "Naemnik_7", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_7":
			dialog.text = "Lui mente sempre, mente – è un vile mascalzone! Non ascoltatelo, "+GetAddress_Form(NPChar)+"! Non abbiamo nemmeno sfiorato quei poveretti!";
			link.l1 = "Ah sì? E perché dovremmo credere a te e non a lui?";
			link.l1.go = "Naemnik_8";
			link.l2 = "Giusto? E magari sei tu quella che mente davvero? Non sembri proprio una santa, giusto?";
			link.l2.go = "Naemnik_9";
		break;
		
		case "Naemnik_8":
			dialog.text = "Ma pensateci un attimo, per l'amor di Dio! Siamo scappati da quella bestia di Bishop, abbiamo corso per la selva due giorni, confondendo le tracce – per cosa? Per adesso infierire su una povera signora e lasciare che quei sanguisughe ci raggiungano?! I miei amici a malapena sono riusciti a trascinarsi su quella spiaggia, "+GetAddress_Form(NPChar)+"!   Non avevamo nemmeno la forza di sparare con i nostri moschetti, altrimenti non avremmo mai permesso a quei canaglie di portare a termine il loro sporco lavoro...   Sono stati loro, li abbiamo visti!.. ";
			link.l1 = "...";
			link.l1.go = "Naemnik_9_add";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "Naemnik_9":
			dialog.text = "Ma pensateci voi stessi, per l'amor di Dio! Siamo scappati da quella bestia di Bishop, abbiamo corso per la selva due giorni, confondendo le tracce – per cosa? Per adesso oltraggiare una povera signora e permettere a quei sanguisughe di raggiungerci?! I miei amici a stento sono riusciti a trascinarsi su quella spiaggia, "+GetAddress_Form(NPChar)+"! Non avevamo nemmeno la forza di sparare con i nostri moschetti, altrimenti non avremmo mai permesso a quei canaglie di portare a termine il loro sporco lavoro... Sono stati loro, li abbiamo visti!..";
			link.l1 = "...";
			link.l1.go = "Naemnik_9_add";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		case "Naemnik_9_add":
			StartInstantDialog("WildRose_Naemnik_1", "Naemnik_10", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_10":
			dialog.text = "Stai zitto, Casper, cane rognoso!";
			link.l1 = "...";
			link.l1.go = "Naemnik_10_add";
			CharacterTurnByChr(npchar, CharacterFromID("WildRose_Naemnik_Rab"));
		break;
		case "Naemnik_10_add":
			StartInstantDialog("Mary", "Naemnik_11", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_11":
			dialog.text = "Cosa hai detto?!";
			link.l1 = "...";
			link.l1.go = "Naemnik_11_add";
			CharacterTurnByChr(npchar, CharacterFromID("WildRose_Naemnik_1"));
		break;
		case "Naemnik_11_add":
			StartInstantDialog("WildRose_Naemnik_1", "Naemnik_12", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_12":
			dialog.text = "Non ci senti bene, signorina? Ho detto di chiudere quella bocca. Il nostro Jerry può raccontare frottole per ore – in questo è davvero un talento! Bishop voleva tagliargli la lingua e fargliela mangiare, ma poi ha avuto pietà – e ha sbagliato, maledizione!";
			link.l1 = "...";
			link.l1.go = "Naemnik_12_add";
			CharacterTurnByChr(npchar, CharacterFromID("Mary"));
		break;
		case "Naemnik_12_add":
			StartInstantDialog("Mary", "Naemnik_13", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_13":
			dialog.text = "Ma... L'hai chiamato Casper, giusto...";
			link.l1 = "...";
			link.l1.go = "Naemnik_13_add";
			CharacterTurnByChr(npchar, CharacterFromID("WildRose_Naemnik_1"));
		break;
		case "Naemnik_13_add":
			StartInstantDialog("WildRose_Naemnik_1", "Naemnik_14", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_14":
			dialog.text = "Ascolta, ragazzo, spiega alla tua ragazza che le persone, anche tipi come questo moccioso, oltre al nome hanno anche un cognome. Ho sentito dire più di una volta che le belle donne possono essere stupide come un sacco di paglia, ma che io muoia se...";
			link.l1 = "...";
			link.l1.go = "Naemnik_14_add";
			CharacterTurnByChr(npchar, pchar);
		break;
		case "Naemnik_14_add":
			StartInstantDialog("Mary", "Naemnik_15", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_15":
			dialog.text = "Proprio questo sto per farti adesso, giusto!";
			link.l1 = "Mary, fermati! Me ne occupo io. Rimetti l'arma nel fodero. Subito.";
			link.l1.go = "Naemnik_15_add";
			CharacterTurnByChr(npchar, CharacterFromID("WildRose_Naemnik_1"));
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "normal to fight", "1", 2.5);
			DoQuestFunctionDelay("WildRose_Etap1_EscapeSlaves_6_1", 3.0);
		break;
		case "Naemnik_15_add":
			StartInstantDialog("WildRose_Naemnik_1", "Naemnik_16", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_16":
			dialog.text = "Oh, abbiamo qui un vero gentiluomo. Beh, il tuo comportamento è davvero più degno delle strida di quel verme. Urlava più forte della sua povera mogliettina – tanto che si sentiva persino da dietro quella collina. A dire il vero, ci ha persino aiutato – è così che abbiamo rintracciato quei bastardi...";
			link.l1 = "Qui, ai Caraibi, la nobiltà è una cosa piuttosto rara. E ora, rilassiamoci tutti – non c'è niente di nobile nel lasciare questa vita qui e adesso.";
			link.l1.go = "Naemnik_17";
			link.l2 = "I mascalzoni qui siete solo voi. Chiedi subito scusa a Mary, e forse potremo evitare uno spargimento di sangue.";
			link.l2.go = "Naemnik_22";
		break;
		
		case "Naemnik_17":
			dialog.text = "È difficile non essere d'accordo. Solo che prima calma un po' la tua...";
			link.l1 = "Si chiama Mary Casper. Penso che questo chiarisca molte cose.";
			link.l1.go = "Naemnik_18";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
		break;
		
		case "Naemnik_18":
			dialog.text = "Casper? È sua figlia, ah-ah?";
			link.l1 = "Ne dubito fortemente. Ma spero che ora tu abbia abbastanza senno da rimangiarti le tue parole.";
			link.l1.go = "Naemnik_19";
		break;
		
		case "Naemnik_19":
			dialog.text = "Indietro? E se no, che farai? Mi sfiderai a duello? Avanti... Se non hai paura di lasciare la tua adorata tutta sola, in mezzo alla giungla, eh-eh. Io e i ragazzi saremmo mooolto contenti di un simile sviluppo.";
			link.l1 = "Ecco che hai mostrato la tua vera natura. Non è che fingessi poi così bene, giusto?";
			link.l1.go = "Naemnik_bitva";
		break;
		
		case "Naemnik_22":
			dialog.text = "Lei, signore, è davvero pieno di contraddizioni — così pacifico, e allo stesso tempo — un maleducato. Eppure, sono curioso di sapere cosa sperate di ottenere come perdono da quella pazza dai capelli rossi?";
			link.l1 = "Si chiama Mary Casper, e se adesso non...";
			link.l1.go = "Naemnik_23";
		break;
		
		case "Naemnik_23":
			dialog.text = "Casper? Che mi venga un colpo! Jerry, non sarà mica tua figlia, eh? Ah-ah-ah-ah! Non ci posso credere! Succedono davvero certe cose!";
			link.l1 = "E sai, sai cos'altro succede? Quelli come te – degli sciocchi che conoscono l'onore solo per sentito dire – si comportano con le donne come se fossero nati in una stalla. D'altronde, cosa c'è da stupirsi – quando al posto del cervello c'è solo segatura, le buone maniere non possono certo spuntare dal nulla.";
			link.l1.go = "Naemnik_24";
		break;
		
		case "Naemnik_24":
			dialog.text = "Bah... Che verme audace. Dimmi un po', amico, la tua ragazza sta bene nell'amaca? Tuttavia, ne sono sicuro — e avrò il piacere di verificare personalmente...";
			link.l1 = "Ecco, vi siete traditi. Non siete durati molto, giusto? All'attacco!";
			link.l1.go = "Naemnik_bitva";
		break;
		
		case "Naemnik_bitva":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_7");
		break;
		
		case "Djerry_1":
			dialog.text = "Li avete sistemati per bene, giusto? "+GetAddress_Form(NPChar)+", - questi bastardi. Che brucino all'inferno! Peccato, non sono riuscito ad aiutarvi. Il moschetto che avevo notato venendo qui era troppo lontano. Pare che qualcuno dei nostri l'abbia perso mentre scappavamo. Avrei voluto sparare a quel bastardo di Primer con le mie stesse mani.";
			link.l1 = "A quanto pare, Primer ti ha dato davvero fastidio, se hai deciso di tornare.";
			link.l1.go = "Djerry_2";
		break;
		
		case "Djerry_2":
			dialog.text = "Altro che dava fastidio. Per colpa di quella bestia ho tutta la schiena piena di tagli. Ma la cosa peggiore è che poteva vietarci di bere acqua quando gli pareva, giusto?";
			link.l1 = "Peccato che nessuno di questi bastardi sia rimasto vivo. Si sarebbe potuto consegnarlo ai soldati – che, sono sicura, arriveranno presto qui.";
			link.l1.go = "Djerry_3_1";
		break;
		
		case "Djerry_3_1":
			dialog.text = "Non capisco proprio perché, ehm, "+GetAddress_Form(NPChar)+"...";
			link.l1 = "Beh, il comandante gli avrebbe strappato una confessione, scagionando i vostri nomi – il tuo e quelli dei tuoi compagni caduti.";
			link.l1.go = "Djerry_4";
		break;
		
		case "Djerry_4":
			dialog.text = "Ah sì, certo, ahah. E poi William Bishop mi scuoierà vivo – me l'ha raccontato uno nero della piantagione… Bishop non ci va leggero con chi scappa – che tu sia nero o bianco, non fa differenza.";
			link.l1 = "Temo che, in un modo o nell'altro, dovrai tornare alla piantagione...";
			link.l1.go = "Djerry_5";
			link.l2 = "Quindi, non tornerai alla piantagione di tua spontanea volontà, giusto?";
			link.l2.go = "Djerry_6";
		break;
		
		case "Djerry_5":
			dialog.text = "Sei proprio uno spiritoso – te l'hanno mai detto, giusto? "+GetAddress_Form(NPChar)+"?";
			link.l1 = "Niente scherzi, "+npchar.name+". Pensi che sia capitato qui per caso? Sono venuto nella selva per trovare la tua squadra, riportarvi alla piantagione – e magari guadagnare un po' d'oro. Ma sei rimasto solo tu. Non ci ricaverò molto con te, quindi forse ti lascerò andare. Ma dimmi – che cosa ti passava per la testa? Sei rimasto solo. Tutti gli altri sono morti. A cosa speri, maledizione? Nasconderti tra le montagne e i cespugli finché non ti becchi una pallottola, non muori di febbre o non diventi cibo per i giaguari?";
			link.l1.go = "Djerry_8";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "Djerry_6":
			dialog.text = "Ma sei proprio uno spiritoso – te l'hanno mai detto, giusto? "+GetAddress_Form(NPChar)+"?";
			link.l1 = "Niente scherzi, "+npchar.name+". Pensi che sia finito qui per caso? Sono andato nella selva per cercare il tuo reparto, riportarlo alla piantagione — e fare un po' di soldi. Ma sei rimasto solo tu. Non c'è molto da ottenere per te, quindi forse ti lascerò andare. Ma dimmi — cosa pensavi di fare? Sei rimasto solo. Tutti gli altri sono morti. Su cosa conti, dannazione? Nasconderti tra montagne e cespugli finché non prendi un proiettile, non soccombi alla febbre o non diventi cibo per i giaguari?";
			link.l1.go = "Djerry_8";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Djerry_8":
			dialog.text = "È meglio così, per Dio, "+GetAddress_Form(NPChar)+" - Secondo me, è molto meglio che crepare tra le sofferenze che mi aveva preparato Bishop. Ma in realtà, non va poi così male – vicino a Capo Ragged Point c'è una barca a vela nascosta.";
			link.l1 = "Le terre più vicine a Barbados sono Dominica, con gli indigeni, e Tobago, con gli spagnoli. Nemmeno so dirti cosa sia per te... peggio.";
			link.l1.go = "Djerry_9";
		break;
		
		case "Djerry_9":
			dialog.text = "Penso che rischierò con i don, a Tobago spesso gettano l'ancora contrabbandieri e pirati. Oh, vedo che disapprovi la mia scelta, "+GetAddress_Form(NPChar)+". Ho servito onestamente il mio paese – ma cosa dovrei fare, se ormai mi ha mandato alle cave di pietra?";
			link.l1 = "Non giudico, "+npchar.name+". Ognuno ha la sua strada. Ora prendi più polvere da sparo e proiettili che puoi – e vai. Prima che arrivino i soldati.";
			link.l1.go = "Djerry_10";
		break;
		
		case "Djerry_10":
			dialog.text = "Grazie, "+GetAddress_Form(NPChar)+". E anche voi, giovane signorina, ehm, Mary. (fa un inchino). Noi, certo, non siamo parenti, ma incontrare qualcuno con lo stesso cognome in una, ehm, situazione del genere... è davvero inaspettato e...";
			link.l1 = "...";
			link.l1.go = "Djerry_10_add";
		break;
		case "Djerry_10_add":
			StartInstantDialog("Mary", "Djerry_11", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Djerry_11":
			dialog.text = "Forse è così, giusto? E ora addio, Jerry.";
			link.l1 = "...";
			link.l1.go = "Djerry_12";
			CharacterTurnByChr(npchar, CharacterFromID("WildRose_Naemnik_Rab_mushketer"));
		break;
		
		case "Djerry_12":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_9");
		break;
		
		case "Mary_11":
			dialog.text = "...";
			link.l1 = ""+npchar.name+", sei un po' turbata? Hai salutato il tuo omonimo davvero in fretta, giusto?";
			link.l1.go = "Mary_12";
		break;
		
		case "Mary_12":
			dialog.text = "Volevo solo liberarmi al più presto della compagnia di quell'uomo... La sua storia è piena di buchi, giusto?";
			link.l1 = "Di cosa parli, cara?";
			link.l1.go = "Mary_13";
		break;
		
		case "Mary_13":
			dialog.text = "Dopo quello che ho sentito dalla bocca di quel tirapiedi di Bishop, non ho dubbi che quei poveretti siano morti proprio per mano sua. Ma prima di questo... Casper, hai ascoltato bene quello che diceva?";
			link.l1 = "E cosa non ti è andato bene, cara?";
			link.l1.go = "Mary_14";
		break;
		
		case "Mary_14":
			dialog.text = "Lui sostiene che sulla spiaggia c'è una barca nascosta. Però dalla piantagione sono scappate più di venti persone. Quindi la barca dev'essere abbastanza grande, giusto? Jerry è un disertore della flotta, non può non capire che da solo con una barca così grande sarà dura cavarsela, giusto...";
			link.l1 = "Dovrà solo issare la vela e prendere la rotta - il resto lo farà il vento. Giusto? Sì, rischia davvero tanto, ma forse morire in mare è davvero meglio che finire sotto la mano di un boia piantatore.";
			link.l1.go = "Mary_15";
		break;
		
		case "Mary_15":
			dialog.text = "Va bene.   Ma ora ho capito che c'è qualcos'altro che non torna...   Secondo lui, lui e i suoi amici hanno osservato da lontano la violenza dei mercenari su quella poveretta...";
			link.l1 = "Invece di correre a perdifiato verso la tua barca... Giusto, ho capito dove vuoi arrivare, "+npchar.name+". Forse vale la pena fare ancora un paio di domande al signor Casper... ";
			link.l1.go = "Mary_15_add";
		break;
		case "Mary_15_add":
			StartInstantDialog("WildRose_Naemnik_Rab_mushketer", "Mary_16", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Mary_16":
			dialog.text = "...";
			link.l1 = " Ehi, "+npchar.name+", vecchio mio! Aspetta un attimo...";
			link.l1.go = "Mary_17";
		break;
		
		case "Mary_17":
			dialog.text = "...";
			link.l1 = " Maledizione!!! Mary, attenta!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_11");
		break;
		
		case "Mary_21":
			dialog.text = "Maledetto bastardo! Gli abbiamo salvato la vita, e lui! Ma come si fa, "+pchar.name+"? Quindi...";
			link.l1 = "Giusto, "+npchar.name+", non è rimasto più nessuno in vita che sapesse la verità su ciò che è successo...";
			link.l1.go = "Mary_22";
		break;
		
		case "Mary_22":
			dialog.text = "Dovremmo andarcene da qui, "+pchar.name+". Se i soldati ci trovano qui, saremo nei guai, giusto?";
			link.l1 = "Hai ragione, Mary. Andiamo...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_15");
		break;
		
		case "Mary_23":
			dialog.text = "Sai, "+pchar.name+", dopo tutto questo mi piacerebbe proprio bere come si deve, giusto.";
			link.l1 = "Non ho nulla in contrario, cara. Anch'io ho voglia di bagnarmi la gola. Andiamo a dare un'occhiata al 'Cornuto Irlandese'.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_City_2");
		break;
		
		case "Barmen_1":
			dialog.text = "Mi scusi se l'ho svegliata, capitano...";
			if (sti(pchar.reputation.nobility) >= 40)
			{
				link.l1 = "Hai bussato, e già per questo grazie. Ora però sputa il rospo, che cosa vuoi da me?";
				link.l1.go = "Barmen_2";
			}
			else
			{
				link.l1 = "Meno male che ti è venuto in mente di bussare, amico. Se fossi entrato così, saresti già rotolato giù per le scale\nChe guardi? Dai, sputa il rospo, perché hai trascinato qui la tua carcassa?";
				link.l1.go = "Barmen_2";
			}
		break;
		
		case "Barmen_2":
			dialog.text = "Uno dei cittadini desidera vedervi – Lewis Gernon. Dice che ha una conversazione importante da fare con voi.";
			link.l1 = "È la prima volta che sento questo nome. Spero davvero che abbia qualcosa di importante, se si permette di interrompermi così... Che entri pure...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_City_5");
		break;
		
		case "Lewis_1":
			dialog.text = "Salve, signore "+pchar.lastname+". Signorina... Casper.";
			link.l1 = ""+TimeGreeting()+", signore "+npchar.lastname+". Non mi sembra che ci siamo già incontrati. Da dove ci conoscete?";
			link.l1.go = "Lewis_2";
		break;
		
		case "Lewis_2":
			dialog.text = "Non ricordate? Ah, capisco... Avevo il viso tutto sporco di sangue e polvere, anch'io mi sono spaventato quando poche ore fa mi sono visto allo specchio...";
			link.l1 = "...";
			link.l1.go = "Lewis_2_add";
		break;
		case "Lewis_2_add":
			StartInstantDialog("Mary", "Lewis_3", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_3":
			dialog.text = "Tu... tu sei quell'uomo, giusto? Ti abbiamo trovato e...";
			link.l1 = "...";
			link.l1.go = "Lewis_3_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_3_add":
			StartInstantDialog("WildRose_Lewis", "Lewis_4", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_4":
			dialog.text = "E la mia Susan. La mia povera Susie...";
			link.l1 = "...";
			link.l1.go = "Lewis_4_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_4_add":
			StartInstantDialog("Mary", "Lewis_5", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_5":
			dialog.text = "Pensavamo che foste morti. Come anche... Lei era vostra moglie, giusto?";
			link.l1 = "...";
			link.l1.go = "Lewis_5_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_5_add":
			StartInstantDialog("WildRose_Lewis", "Lewis_6", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_6":
			dialog.text = "Sì, signora. Era mia moglie, e io sono rimasto paralizzato dalla paura... e non sono riuscito a fare nulla. Mio Dio, mio Dio...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_City_8");
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		
		case "Lewis_7":
			dialog.text = "(singhiozza) Mi hanno picchiata e mi hanno costretta a guardare...";
			link.l1 = "Alzati, "+GetAddress_Form(NPChar)+" . Non è colpa vostra. Nessuno sarebbe riuscito a resistere da solo contro una tale quantità di furfanti.";
			link.l1.go = "Lewis_8";
		break;
		
		case "Lewis_8":
			dialog.text = "Erano così tanti, così tanti... Ma io comunque...";
			link.l1 = "Ma alla fine siete sopravvissuto, e gli assassini di vostra moglie bruciano all'inferno. È una magra consolazione, ma almeno qualcosa, signor "+npchar.lastname+". Però, volevo chiederti una cosa...";
			link.l1.go = "Lewis_9";
			LAi_ActorAnimation(npchar, "ground_standup", "WildRose_Etap1_City_8_1", 7);
		break;
		
		case "Lewis_9":
			dialog.text = "Sì, signore "+pchar.lastname+"?";
			link.l1 = "Chi erano? Mercenari di Bishop o schiavi fuggiaschi?";
			link.l1.go = "Lewis_10";
		break;
		
		case "Lewis_10":
			dialog.text = "L'hanno fatto Jerry Casper e gli altri fuggitivi. Avete sospettato invano di Bruce Primer e dei suoi uomini.";
			link.l1 = "I mercenari di Bishop?";
			link.l1.go = "Lewis_11";
		break;
		
		case "Lewis_11":
			dialog.text = "Sì. Bruce, certo, era davvero un furfante e faceva molti lavori sporchi per Bishop – ma non era uno stupratore, giusto?";
			link.l1 = "Non mi è sembrato proprio così. Ma non voglio discutere con voi, "+npchar.name+". Tuttavia, visto che eri cosciente e hai visto tutto, potevi anche alzarti e...";
			link.l1.go = "Lewis_12";
		break;
		
		case "Lewis_12":
			dialog.text = "Perdonatemi, "+GetAddress_Form(NPChar)+". Potete considerarmi un codardo patetico – ma non riuscivo nemmeno a muovermi, tanta era la paura. Quando quei furfanti hanno sbarrato la strada a me e a Susie, all'inizio ho urlato con tutta la forza che avevo, volevo chiamare aiuto.";
			link.l1 = "E ti hanno picchiata.";
			link.l1.go = "Lewis_13";
		break;
		
		case "Lewis_13":
			dialog.text = "Jerry mi ha colpito con il calcio del moschetto, poi ha detto che mi avrebbe fatto a pezzi, proprio davanti a Susan. Io... io mi vergogno ad ammetterlo, ma credo di aver perso conoscenza per qualche secondo dalla paura. E loro, intanto...";
			link.l1 = "Ho capito, signore "+npchar.lastname+". Nel vostro comportamento non c'è nulla di vergognoso. Non tutti sarebbero stati in grado di sopportare una cosa simile. Peccato che non siate intervenuto – ma ormai, ciò che è fatto è fatto. Però sono contento che almeno uno degli assassini di vostra moglie abbia fatto una brutta fine – anche se per poco non è riuscito a ingannarci.";
			link.l1.go = "Lewis_14";
			link.l2 = "Quindi siamo quasi morti combattendo i mercenari di Bishop – solo perché avevate paura, giusto? Una scusa perfetta, "+npchar.name+". Meno male che alla fine, anche se con un po' di ritardo, siamo riusciti a capire cosa stava succedendo...";
			link.l2.go = "Lewis_15";
		break;
		
		case "Lewis_14":
			dialog.text = "Giusto, "+GetAddress_Form(NPChar)+". Sono venuto a ringraziarvi per questo. Anche se all'inizio gli avete creduto...";
			link.l1 = "Bruce Primer ci ha messo parecchio impegno per questo. Dovrebbe fare più attenzione a quello che dice...";
			link.l1.go = "Lewis_16";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "Lewis_15":
			dialog.text = "Giusto, "+GetAddress_Form(NPChar)+". Sono venuto a ringraziarvi per questo. Anche se all'inizio gli avete creduto...";
			link.l1 = "Bruce Primer ci ha messo parecchio impegno per questo. Dovrebbe stare più attento a quello che dice...";
			link.l1.go = "Lewis_16";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;
		
		case "Lewis_16":
			dialog.text = "Purtroppo, tutti noi quel giorno abbiamo commesso degli errori... Io e Susan non avremmo dovuto andare a passeggiare a Ragged Point, Bruce avrebbe dovuto mordersi la lingua in tempo... E tu non avresti dovuto fidarti di Jeremy. Ma grazie a miss Casper la giustizia è stata ristabilita.";
			link.l1 = "...";
			link.l1.go = "Lewis_16_add";
		break;
		case "Lewis_16_add":
			StartInstantDialog("Mary", "Lewis_17", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_17":
			sld = CharacterFromID("WildRose_Lewis");
			dialog.text = "Immagino di sapere cosa vuole chiedermi, signor "+sld.lastname+". Ma io non ho nulla a che fare con quella persona.";
			link.l1 = "...";
			link.l1.go = "Lewis_17_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_17_add":
			StartInstantDialog("WildRose_Lewis", "Lewis_18", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_18":
			dialog.text = "So che è così, signorina. L'ho capito subito, appena sono entrato in questa stanza. Non avete nulla in comune, né lei né lui. Eppure, Susan... era convinta che nulla al mondo accada per caso.";
			link.l1 = "...";
			link.l1.go = "Lewis_18_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_18_add":
			StartInstantDialog("Mary", "Lewis_19", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_19":
			dialog.text = "Tua moglie aveva ragione. Io stessa me ne sono convinta più volte, giusto? E "+pchar.name+" anche.";
			link.l1 = "...";
			link.l1.go = "Lewis_19_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_19_add":
			StartInstantDialog("WildRose_Lewis", "Lewis_20", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_20":
			dialog.text = "...";
			link.l1 = "Giusto. Però non credo sia il momento per discorsi filosofici adesso. Dubito che questo vi aiuterà, "+npchar.name+". Solo il tempo può aiutare a superare una cosa del genere.";
			link.l1.go = "Lewis_21";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), pchar);
			CharacterTurnByChr(CharacterFromID("Mary"), pchar);
		break;
		
		case "Lewis_21":
			dialog.text = "Forse avete ragione, signore "+pchar.lastname+". Beh, grazie ancora e addio. Pregherò per voi e per la signorina Casper.";
			link.l1 = "Arrivederci, "+npchar.name+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_City_10");
		break;
		
		case "Mary_31":
			dialog.text = ""+pchar.name+"...";
			link.l1 = "Lo so, cara, ho quasi lasciato andare quel bastardo...";
			link.l1.go = "Mary_32";
		break;
		
		case "Mary_32":
			dialog.text = "Quel bastardo di nome Jerry Casper.";
			link.l1 = "Giusto... Aspetta... ma tu pensi davvero che lui...";
			link.l1.go = "Mary_33";
		break;
		
		case "Mary_33":
			dialog.text = "So che è davvero stupido...";
			link.l1 = "Eccome! E se tu avessi portato il cognome Smith o Jones? Ce ne sono a bizzeffe che camminano per le strade – e qualcuno di loro sicuramente fa qualche malefatta... E quel Jerry, che possa bruciare nelle fiamme dell'inferno – magari non è nemmeno un vero Casper...";
			link.l1.go = "Mary_34";
			link.l2 = "Proprio così, cara. Quel dannato Jerry poteva benissimo usare un cognome falso, tutto qui.";
			link.l2.go = "Mary_35";
		break;
		
		case "Mary_34":
			dialog.text = "Eppure... So che non mi capisci, ma prova solo a immaginare cosa penseresti tu, se avesse il tuo stesso cognome "+pchar.lastname+".";
			link.l1 = "Non è la stessa cosa, Mary. "+pchar.lastname+" - una famiglia nobile, eh...";
			link.l1.go = "Mary_36";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Mary_35":
			dialog.text = "Eppure... So che non mi capisci, ma prova solo a immaginare cosa penseresti tu, se lui avesse quel cognome "+pchar.lastname+".";
			link.l1 = "Non è la stessa cosa, Mary. "+pchar.lastname+" - una famiglia nobile, eh...";
			link.l1.go = "Mary_36";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Mary_36":
			dialog.text = "E i Casper sono così, gente senza radici, senza famiglia, giusto? Forse dovrei ringraziare ogni giorno il Signore nostro per il fatto che tu abbia notato proprio me, e non qualche altezzosa...";
			link.l1 = ""+npchar.name+", non era affatto questo che intendevo - lo capisci, vero? I membri di una casata nobiliare sono legati tra loro da vincoli di sangue - e non è affatto la stessa cosa che semplicemente avere lo stesso cognome di qualcuno. Cognome che, tra l'altro, come ho già detto, quella persona potrebbe semplicemente essersi appropriata...";
			link.l1.go = "Mary_37";
		break;
		
		case "Mary_37":
			dialog.text = "Non è solo questo, "+pchar.name+"...";
			link.l1 = "Tesoro, abbiamo avuto una giornata lunga e pesante. Abbiamo vagato per la selva per più di una miglia, potevamo anche morire... e poi non ci hanno nemmeno lasciato dormire come si deve. Non c'è nulla di strano che ti siano venuti in mente pensieri strani. Abbiamo solo bisogno di dormire bene, tutti e due.";
			link.l1.go = "Mary_38";
		break;
		
		case "Mary_38":
			dialog.text = "Non penso affatto che sia strano, però va bene... ne parliamo domani.";
			link.l1 = "A mente lucida, capiremo tutto più in fretta. Sdraiati, cara, dobbiamo lasciarci questa giornata alle spalle.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_Morning_1");
		break;
		
		case "Waitress_1":
			dialog.text = "State bene, "+GetAddress_Form(NPChar)+"Avete un'aria strana, come se aveste visto un fantasma. Forse volete un po' di rum? O del vino? Abbiamo un'ottima scelta, vi farebbe bene rilassarvi.";
			link.l1 = "Al diavolo il rum. Sto cercando una ragazza...";
			link.l1.go = "Waitress_2";
		break;
		
		case "Waitress_2":
			dialog.text = "Allora avete sbagliato posto, capitano. Qui è una taverna, non un bordello. Basta uscire in strada e vedrete proprio di fronte...";
			link.l1 = "Ascolta, non ho tempo per scherzare. Sto cercando una ragazza dai capelli rossi, con un farsetto rosso, è armata. Si chiama Mary Casper.";
			link.l1.go = "Waitress_3";
		break;
		
		case "Waitress_3":
			dialog.text = "Beh, se non è il momento per scherzare, allora non ho niente da dirvi. Il mio turno è iniziato un'ora fa, e qui non ho visto nessuna rossa con una giacca rossa.";
			link.l1 = "Quindi, se n'è andata di notte...   Ma dove poteva andare?!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_Morning_4");
		break;
		
		case "Mary_41":
			dialog.text = "Buongiorno, amore mio! Hai dormito a lungo, eh...";
			link.l2 = "Mamma mia, mi hai proprio fatto preoccupare, giusto? "+npchar.name+". Non sparire più così, senza avvertire...";
			link.l2.go = "Mary_43";
			DelLandQuestMark(npchar);
		break;
		
		case "Mary_43":
			dialog.text = "Non volevo svegliarti. E poi, anche tu a volte sparisci così, senza dire una parola...";
			link.l1 = "E hai deciso di ricambiare i miei sentimenti, giusto?";
			link.l1.go = "Mary_44";
			AddCharacterExpToSkill(pchar, "Defence", 100);
		break;
		
		case "Mary_44":
			dialog.text = "A dire il vero, avevo solo bisogno di restare un po' da sola con i miei pensieri, giusto? Non volevo che ti preoccupassi.";
			link.l1 = "C'è qualcosa che ti preoccupa, giusto?";
			link.l1.go = "Mary_46";
		break;
		
		case "Mary_46":
			dialog.text = "La nostra conversazione di ieri. Sulle famiglie, i legami di sangue...";
			link.l1 = "Quindi, ti sei davvero offesa con me...";
			link.l1.go = "Mary_47";
		break;
		
		case "Mary_47":
			dialog.text = "Ma no, caro, non intendevo questo. È solo che all'improvviso mi sono resa conto di non sapere proprio nulla della mia famiglia. Tu, per esempio, sei figlio di una casata nobile. I ragazzi sulla nave, ogni tanto, raccontano qualcosa delle loro famiglie. E io? Io non ho proprio nulla da raccontare – non ho mai conosciuto i miei genitori. Accidenti, non so nemmeno dove sono nata...";
			link.l1 = "Non è forse sull'Isola della Giustizia?";
			link.l1.go = "Mary_48";
		break;
		
		case "Mary_48":
			dialog.text = "Eric, l'uomo che mi ha cresciuta, lo diceva sempre. Ma allora perché nessuno degli abitanti dell'Isola ha mai parlato dei miei genitori, nemmeno li ha mai nominati? Una volta l'ho chiesto a Donald Greenspy, ma non mi ha detto niente di chiaro.";
			link.l1 = "O forse non voleva parlare.";
			link.l1.go = "Mary_49";
		break;
		
		case "Mary_49":
			dialog.text = "Ecco! Anch'io ho pensato la stessa cosa, giusto? Sai, prima vivevo e basta, senza farmi troppe domande. Ma ieri, quando ci siamo imbattuti in quella bestia di Jerry... mi sono chiesta – chi era mio padre? E mia madre? Perché non mi hanno mai parlato di loro, come se non fossero mai esistiti? E se mio padre fosse stato un farabutto come quel Jerry?";
			link.l1 = "Non ha alcuna importanza, "+npchar.name+". Sei stata cresciuta da altre persone – e l'hanno fatto con grande dignità.";
			link.l1.go = "Mary_50";
			link.l1 = "Dubito che sia così.   E non riesco proprio a capire che importanza possa avere, visto che prima, per qualche motivo, non ci avevi mai pensato, giusto?";
			link.l1.go = "Mary_51";
		break;
		
		case "Mary_50":
			dialog.text = "Ma per me è importante, "+pchar.name+", giusto. Voglio sapere, ne ho il diritto, chi erano i miei genitori. Non sei d'accordo con questo, giusto?";
			link.l1 = "Certo, sono d'accordo, non potrebbe essere altrimenti. Ma se vuoi davvero scoprire qualcosa su tuo padre e tua madre, allora solo sull'Isola della Giustizia. Dopotutto, non conosci nemmeno i loro nomi, giusto?";
			link.l1.go = "Mary_52";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;
		
		case "Mary_51":
			dialog.text = "Ma per me è importante, "+pchar.name+", giusto. Voglio sapere, ne ho il diritto, chi erano i miei genitori. Non sei d'accordo con questo, giusto?";
			link.l1 = "Certo, sono d'accordo, non potrebbe essere altrimenti. Ma se vogliamo davvero scoprire qualcosa su tuo padre e tua madre, dobbiamo farlo solo sull'Isola della Giustizia. In fondo, non conosci nemmeno i loro nomi, giusto?";
			link.l1.go = "Mary_52";
			AddCharacterExpToSkill(pchar, "Commerce", 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;
		
		case "Mary_52":
			dialog.text = "Proprio così, caro. Non li hanno mai nominati davanti a me, giusto?";
			link.l1 = "Quindi, è troppo presto per andare negli archivi cittadini delle colonie inglesi. Prima dovremo tornare a quel cimitero di navi e cercare di trovare qualche traccia delle tue origini lì.";
			link.l1.go = "Mary_53";
		break;
		
		case "Mary_53":
			dialog.text = "Sono felice che tu mi capisca, "+pchar.name+". Grazie a te.";
			link.l1 = ""+npchar.name+", mi sorprendi davvero, giusto? È il minimo che possa fare per te, amore mio.";
			link.l1.go = "Mary_54";
		break;
		
		case "Mary_54":
			dialog.text = "In qualche modo sono riuscita a vivere quasi vent'anni senza sapere nulla di loro...";
			// dialog.text = "Dopotutto, per più di vent'anni non me n'è importato proprio niente...";
			link.l1 = "...";
			link.l1.go = "Mary_55";
		break;
		
		case "Mary_55":
			dialog.text = "Quindi posso resistere ancora un po', giusto?";
			link.l1 = "Vedo che per te è importante, giusto? "+npchar.name+". Quindi cercherò di non farti aspettare. E ora andiamo, dobbiamo tornare sulla nave. Lì mi sento più tranquilla per te, almeno.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_Morning_6");
		break;
		
		// ============================================================
		// ================== ЭТАП 2. «ДИТЯ ОСТРОВА» ==================
		// ============================================================
		case "Mary_61":
			dialog.text = "Le coste di casa... Sai, "+pchar.name+", secondo me, se ci ritrovassimo qui tra dieci anni, tutto sarebbe esattamente come adesso, giusto.";
			link.l1 = "Forse, "+npchar.name+", forse. Le navi dell'anello interno resteranno a galla, ma qui vivranno già altre persone.";
			link.l1.go = "Mary_62";
			link.l2 = "Ne dubito molto – qui tutto si regge solo sulla parola d'onore. E sul genio del Meccanico.";
			link.l2.go = "Mary_63";
		break;
		
		case "Mary_62":
			dialog.text = "E io, in realtà, non ricordo quasi nessuno di quelli che vivevano su questi relitti dieci o quindici anni fa. Solo le persone a me più care – Alan, Erik...";
			link.l1 = "Forse è proprio così. Non si può ricordare tutto e tutti. Anche a me si cancellano dalla memoria nomi e volti – dei tempi di Parigi, per non parlare della Guascogna. E pensare che credevo che succedesse solo ai vecchi.";
			link.l1.go = "Mary_64";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "Mary_63":
			dialog.text = "E io, in realtà, non ricordo quasi nessuno di quelli che vivevano su questi relitti dieci o quindici anni fa. Solo le persone a me più care – Alan, Erik...";
			link.l1 = "Forse è proprio così. Non si può ricordare tutto e tutti. Anche a me si cancellano dalla memoria nomi e volti – dei tempi di Parigi, per non parlare della Guascogna. E pensare che credevo che succedesse solo ai vecchi.";
			link.l1.go = "Mary_64";
			AddCharacterExpToSkill(pchar, "Repair", 100);
		break;
		
		case "Mary_64":
			dialog.text = "Ma questo posto... Sembra un altro mondo, giusto? Immagina, alcuni di quelli che sono arrivati qui non molto tempo fa dicono che il tempo qui scorra quasi tre volte più veloce che sulla Terraferma...";
			link.l1 = "Ahah, quanti anni hai allora, giusto?";
			link.l1.go = "Mary_65";
		break;
		
		case "Mary_65":
			dialog.text = "Facevo sul serio, giusto? "+pchar.name+", giusto!";
			link.l1 = "Beh, seriamente parlando, è ora di mettersi al lavoro. C'è qualcuno tra i narvali più anziano di Greenspy?";
			link.l1.go = "Mary_66";
		break;
		
		case "Mary_66":
			dialog.text = "Mh, no, sembra di no. Ma ti ho già detto che non mi ha detto nulla quando gliel'ho chiesto, giusto?";
			link.l1 = "E comunque, non ho altre idee su chi potrebbe aiutarci a capire cosa sia successo vent'anni fa. Almeno per ora. Quindi puntiamo verso l'Esmeralda.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_2");
		break;
		
		case "Schmidt_1":
			dialog.text = "A, "+pchar.name+" e Mary, che incontro! Sono felice di vedervi qui... vivi e vegeti, eh-eh. Nell'ultimo mese due o tre navi si sono schiantate sull'anello esterno – il mare è davvero maledettamente agitato ultimamente. Giusto, e non forzate la porta chiusa – potreste anche rompere la serratura, e poi tocca a me ripararla. State andando da Donald, vero?";
			link.l1 = "E anche a te una buona giornata, amico. Da lui stesso. Ma, a giudicare dal fatto che la porta è chiusa, o si è trasferito su un'altra nave, o non vuole vedere i vecchi amici.";
			link.l1.go = "Schmidt_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Schmidt_2":
			dialog.text = "Né l'uno né l'altro, ahah. Greenspy adesso è sull'anello esterno, alle esercitazioni.";
			link.l1 = "Addestramenti? Davvero? Sta forse preparando una nuova guerra contro i rivados, giusto?";
			link.l1.go = "Schmidt_3";
		break;
		
		case "Schmidt_3":
			dialog.text = "Non è che sia mai davvero finita, "+pchar.name+". Ultimamente ci sono molte meno risse di prima, giusto? Però nella taverna di Sancho ogni tanto qualcuno finisce comunque per prendersi un pugno in faccia... e a volte salta fuori anche un coltello.";
			link.l1 = "Hmm, sembra che prima i membri dei clan non si facessero vedere in taverna, giusto?";
			link.l1.go = "Schmidt_4";
		break;
		
		case "Schmidt_4":
			dialog.text = "Beh, qualcosa è cambiato da quando siete partiti dall'Isola. Donald ed Eddie riescono a tenere la gente sotto controllo. Per ora. Ma chissà cosa succederà domani? È stato il vecchio Donnie a mettere in moto tutto questo...";
			link.l1 = "Ho fatto tanta fatica per evitare un massacro sull'Isola, e voi qui di nuovo a giocare ai soldatini? E da quanto tempo sta appostato sull'anello esterno?";
			link.l1.go = "Schmidt_5";
			link.l2 = "Addestrarsi va bene, ma non rischiano di mettere a repentaglio una tregua già così fragile? E da quanto tempo Greenspy sta già addestrando i ragazzi?";
			link.l2.go = "Schmidt_6";
		break;
		
		case "Schmidt_5":
			dialog.text = "È il terzo giorno ormai. Dovrebbe tornare domani prima di mezzogiorno. Con tutto l'entusiasmo che ci mettono a sciacquare quei moschetti, domani non avranno più niente con cui sparare! Ah-ah!";
			link.l1 = "...";
			link.l1.go = "Schmidt_5_add";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Schmidt_6":
			dialog.text = "È il terzo giorno ormai. Dovrebbe tornare domani prima di mezzogiorno. Con tutto l'entusiasmo che ci mettono a pulire quei moschetti, domani non avranno più nulla con cui sparare! Ah-ah!";
			link.l1 = "...";
			link.l1.go = "Schmidt_5_add";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;
		case "Schmidt_5_add":
			StartInstantDialog("Mary", "Schmidt_7", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Schmidt_7":
			dialog.text = "La mia cabina sulla 'Ceres Smithy' è ancora libera? O qualcuno è già riuscito a sistemarsi lì?";
			link.l1 = "...";
			link.l1.go = "Schmidt_7_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Schmidt_Clone"));
			CharacterTurnByChr(CharacterFromID("Schmidt_Clone"), CharacterFromID("Mary"));
		break;
		case "Schmidt_7_add":
			StartInstantDialog("Schmidt_Clone", "Schmidt_8", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Schmidt_8":
			dialog.text = "Lì è tutto esattamente come il giorno in cui ci sei stata l'ultima volta. Non abbiamo nemmeno aperto la porta. A dire il vero, la serratura non l'abbiamo né pulita né oliata per tutto questo tempo. Quindi, se dovesse servire romperla, basta dirlo.";
			link.l1 = "...";
			link.l1.go = "Schmidt_8_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Schmidt_Clone"));
			CharacterTurnByChr(CharacterFromID("Schmidt_Clone"), CharacterFromID("Mary"));
		break;
		case "Schmidt_8_add":
			StartInstantDialog("Mary", "Schmidt_9", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Schmidt_9":
			dialog.text = "Certo. Grazie, Jurgen.";
			link.l1 = "...";
			link.l1.go = "exit";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Schmidt_Clone"));
			CharacterTurnByChr(CharacterFromID("Schmidt_Clone"), CharacterFromID("Mary"));
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_3");
			
			//доп
		break;
		
		case "Mary_71":
			dialog.text = "È davvero tutto rimasto come prima. Tutte le cose sono al loro posto – come se non me ne fossi mai andata da qui... Qui ci siamo incontrati per la prima volta, "+pchar.name+". Ti ricordi?";
			link.l1 = "Altroché! Li hai sistemati così bene che ho pensato – speriamo di non finire anch'io al loro posto!";
			link.l1.go = "Mary_72";
			DelLandQuestMark(npchar);
		break;
		
		case "Mary_72":
			dialog.text = "Non è andata affatto così, giusto! Mi hai letteralmente strappata dalle grinfie della morte!";
			link.l1 = "Sembra che quell'incontro fosse destinato a me dal destino stesso.";
			link.l1.go = "Mary_73";
		break;
		
		case "Mary_73":
			dialog.text = "Lo pensi davvero, caro?";
			link.l1 = "Certo, amore mio. E da allora ogni giorno la ringrazio per avermi portato proprio sulla 'Ceres Smithy'.";
			link.l1.go = "Mary_74";
		break;
		
		case "Mary_74":
			dialog.text = ""+pchar.name+"... Dimmi, cosa hai pensato quando mi hai visto per la prima volta?";
			link.l1 = "Beh... Ricordo solo che, quando è successo, il cuore sembrava volesse saltarmi fuori dal petto. Eri così...";
			link.l1.go = "Mary_75";
		break;
		
		case "Mary_75":
			dialog.text = "Quale?";
			link.l1 = "Non assomigli a nessuna di quelle che ho conosciuto prima. La tua grazia, la tua voce... e quel giubbotto rosso. Non ho avuto la minima possibilità di resisterti. Devo ammettere, mi sono sempre chiesto: perché proprio quello? Perché un giubbotto rosso, e non un vestito, una camicia o un corsetto?";
			link.l1.go = "Mary_76";
		break;
		
		case "Mary_76":
			dialog.text = "L'ho trovato quando avevo nove anni, sull'anello esterno. Allora adoravo passeggiare lì – esplorare tutto ciò che era nuovo, trovare oggetti che non si trovavano sull'isola, soprattutto libri. Avevo una voglia matta di provarlo, ma allora potevo solo affogarci dentro. L'ho nascosto dove mettevo tutte le mie altre scoperte – in uno dei nidi di corvo che spuntano dall'acqua.";
			link.l1 = "E quando ti è tornato utile, ti sei ricordata di lui?";
			link.l1.go = "Mary_77";
		break;
		
		case "Mary_77":
			dialog.text = "Qualche anno fa, girovagando per il ring, mi sono imbattuta in un libro su un valoroso capitano con la giubba rossa. Non aveva paura di niente, combatteva contro centinaia di nemici per amore della donna della sua vita e non conosceva il timore. È stato allora che l'ho indossata per la prima volta. Mi dà sicurezza...";
			link.l1 = "E un fascino unico, tesoro! Ma sai una cosa? Proprio adesso voglio solo una cosa... toglierlo da te...";
			link.l1.go = "Mary_78";
		break;
		
		case "Mary_78":
			dialog.text = "Allora che cosa aspetti, mio valoroso capitano?";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_5");
		break;
		
		case "Mary_81":
			dialog.text = "Buongiorno, caro. I narvali sono appena tornati sull''Esmeralda' e sulla 'San Gabriel', e Donald è con loro. L'ho visto su una delle scialuppe, giusto?";
			link.l1 = "Buongiorno, buongiorno... A dire il vero, dopo una notte così io dormirei fino a mezzogiorno, e invece tu sei già in piedi, che voli qua e là.";
			link.l1.go = "Mary_82";
		break;
		
		case "Mary_82":
			dialog.text = "Ieri abbiamo parlato del farsetto e del nido di corvo, dove una volta l'avevo nascosto… E all'improvviso mi è venuta una nostalgia tremenda per quei tempi in cui mi rifugiavo lì da tutti, per leggere in silenzio libri sulla grande terra… Non ho resistito e ci sono andata. Prima potevo restare lì per ore, ma oggi… ho semplicemente aspettato l'alba. E ho capito: più di ogni altra cosa al mondo, voglio stare accanto a te.";
			link.l1 = "E io sono con te, "+npchar.name+". Allora, andiamo   da Donald? Avremo di che parlare, giusto?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_7");
		break;
		
		case "Grinspy_1":
			dialog.text = ""+pchar.name+", Mary, sono felice di vederti! Mi hanno già riferito della tua visita di ieri. Pensavo di passare io stesso da te alla 'Ceres Smithy', ma mi hai preceduto, vecchio che sono. Eh, avessi io la tua età...";
			link.l1 = "Beh, anche tu hai energia da vendere, come abbiamo capito. Com'è andato l'addestramento?";
			link.l1.go = "Grinspy_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Grinspy_2":
			dialog.text = "Meglio di quanto mi aspettassi. Abbiamo effettuato lo sbarco sulle navi nemiche, assaltato gli edifici... Insomma, un lavoro davvero ben fatto. Certo, li ho spinti parecchio, ma è stato solo utile per loro. Da tempo non muovevano le ossa, oh, da tempo, haha.";
			link.l1 = "E quindi, permettimi di chiedere, cosa ti ha spinto a tali imprese? Ti sei annoiato sull'Isola, giusto?";
			link.l1.go = "Grinspy_3";
		break;
		
		case "Grinspy_3":
			dialog.text = "Hm, mi sembra di sentire un po' di malumore nella tua voce, "+pchar.name+". Posso, certo, capire le sue ragioni...";
			link.l1 = "Davvero, "+npchar.name+"?";
			link.l1.go = "Grinspy_4";
		break;
		
		case "Grinspy_4":
			dialog.text = "Hai dovuto correre parecchio tra questi relitti marci per evitare che ci sgozzassimo a vicenda qui – non l'ho dimenticato. Nessuno l'ha dimenticato.";
			link.l1 = "Ecco come hai ripagato i miei sforzi! Pare che sia vero quello che dicono – il mondo pesa davvero sul cuore di un vero guerriero.";
			link.l1.go = "Grinspy_5";
			link.l2 = "E devo dire, contavo molto di più sul tuo buon senso che su quello dei pirati o dei rivados.";
			link.l2.go = "Grinspy_6";
		break;
		
		case "Grinspy_5":
			dialog.text = "Fammi finire. Giusto? Sì, siamo riusciti a mantenere la pace – ma le nostre divergenze non sono scomparse. Almeno, non con quei negri senza Dio. La settimana scorsa, durante una rissa in taverna, uno dei narvali è stato ucciso. Ma anche noi abbiamo fatto la nostra parte...";
			link.l1 = "Sì sì, è proprio così che di solito tutto comincia, giusto?";
			link.l1.go = "Grinspy_7";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Grinspy_6":
			dialog.text = "Lascia che finisca. Giusto? Sì, siamo riusciti a mantenere la pace – ma le nostre divergenze non sono sparite. Almeno, non con quei dannati miscredenti dalla pelle scura. La settimana scorsa, durante una rissa in taverna, uno dei narvali è stato ucciso. Ma anche noi non siamo rimasti a guardare...";
			link.l1 = "Sì sì, è proprio così che di solito tutto comincia, giusto?";
			link.l1.go = "Grinspy_7";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Grinspy_7":
			dialog.text = "Ti sbagli su due cose, "+pchar.name+". Prima di tutto, non sta iniziando, sta continuando. Se ingenuamente pensavi di averci messo fine, ti sbagli. E poi, non sono una santa da porgere l'altra guancia. I neri si sono di nuovo scatenati, e a me non piace affatto. Anche a Dexter, tra l'altro, ma lui si crede un grande politico e preferisce restare al di sopra della mischia. Così, dopo qualche riflessione, ho scelto, secondo me, il modo più... indolore per mantenere una pace precaria.";
			link.l1 = "Hai deciso di spaventare i rivados con le tue prediche?";
			link.l1.go = "Grinspy_8";
		break;
		
		case "Grinspy_8":
			dialog.text = "Un paio di settimane fa, al cerchio esterno è stato portato un galeone inglese con un carico militare – c'era di tutto, davvero... Ma la cosa più importante erano una cinquantina di fucili nuovi di zecca e della buona polvere da sparo. E poi le scialuppe... Su alcune la vernice non aveva nemmeno fatto in tempo ad asciugarsi! Quelle vecchie erano ormai tutte sfondate, e dopo le tempeste non resta poi così tante barche in buono stato, te lo dico io...";
			link.l1 = "E tutto questo è diventato proprietà dei narvali?";
			link.l1.go = "Grinspy_9";
		break;
		
		case "Grinspy_9":
			dialog.text = "Forse avrei anche condiviso con l'Ammiraglio, ma visto che lui si crede il più furbo, non voglio certo passare per sciocco anch'io. Il mio piano, tra l'altro, ha funzionato, ecco qua.";
			link.l1 = "Black Eddie ti ha mandato una lettera dove promette di non infilzare più i tuoi ragazzi, giusto?";
			link.l1.go = "Grinspy_10";
		break;
		
				case "Grinspy_10":
			dialog.text = "Black Eddie ha ordinato ai suoi neri di starsene buoni. Temetti che, in mia assenza, le loro provocazioni sarebbero aumentate — ma è stato esattamente il contrario: i rivados stanno tranquilli e si tengono lontani sia dai miei ragazzi sia dai civili, che a volte infastidivano. I neri sono neri — capiscono solo la forza. Così diceva Alan, e che questa nave affondi all'istante se si sbagliava!";
			link.l1 = "E se dopo un po' ricominceranno a fare di testa loro, per dare una lezione rovescerai sulla 'Furia' e sul 'Protettore' una pioggia di piombo con i tuoi nuovi moschetti, giusto?";
			link.l1.go = "Grinspy_11";
		break;
		
		case "Grinspy_11":
			dialog.text = "Idea audace e temeraria, ma credo che non si arriverà a tanto. Forse faremo solo finta di preparare un'incursione sulle loro navi — e poi Leighton prenderà i suoi cannoni in mano e interverrà. È un po' presuntuoso, ma è comunque lungimirante. Distruggere né il nostro clan né i neri è nei suoi interessi — tre centri di potere circa equivalenti garantiscono un minimo equilibrio. Se uno crolla, tutto va a rotoli. Ne sono sicuro, lo capisce — ma per qualche motivo tocca a me fare il suo lavoro.";
			link.l1 = "Forse gli farò visita mentre saremo qui – sempre che non si metta a fare le sue prediche in risposta, ah-ah.";
			link.l1.go = "Grinspy_12";
			link.l2 = "Cercherò di passare da lui quando ne avrò l'occasione – per parlargli di questa faccenda. Magari mi ascolterà.";
			link.l2.go = "Grinspy_13";
		break;
		
		case "Grinspy_12":
			dialog.text = "Se c'è qualcuno che può convincerlo a tenere a bada quei negri, sei tu, "+pchar.name+". Tuttavia, dai vostri volti vedo che non siete venuti qui per chiacchierare di politica. Dite pure, cosa vi porta qui.";
			link.l1 = "...";
			link.l1.go = "Grinspy_12_add";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;
		case "Grinspy_12_add":
			StartInstantDialog("Mary", "Grinspy_13", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_13":
			dialog.text = "I miei genitori, Donald.";
			link.l1 = "...";
			link.l1.go = "Grinspy_13_add";
		break;
		case "Grinspy_13_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_14", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_14":
			dialog.text = "Non capisco bene cosa vuoi da me, Mary.";
			link.l1 = "...";
			link.l1.go = "Grinspy_14_add";
		break;
		case "Grinspy_14_add":
			StartInstantDialog("Mary", "Grinspy_15", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_15":
			dialog.text = "Parlami di loro, ti prego, giusto? Tu li conoscevi! Una volta ti avevo già chiesto di loro, ma non hai voluto rispondere alle mie domande...";
			link.l1 = "...";
			link.l1.go = "Grinspy_15_add";
		break;
		case "Grinspy_15_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_16", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_16":
			dialog.text = "E quindi hai deciso di trascinare qui Charles, ah-ah-ah! Sei proprio incredibile, ragazza, che mi colga un fulmine! Se non ti ho mai parlato di tuo padre e tua madre, è solo perché non li ho mai conosciuti, tutto qui!";
			link.l1 = "...";
			link.l1.go = "Grinspy_16_add";
		break;
		case "Grinspy_16_add":
			StartInstantDialog("Mary", "Grinspy_17", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_17":
			dialog.text = "Ma tu sei il membro più anziano del nostro clan, giusto! Sei stato qui da quando ho memoria...";
			link.l1 = "...";
			link.l1.go = "Grinspy_17_add";
		break;
		case "Grinspy_17_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_18", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_18":
			dialog.text = "Sono arrivato sull'Isola poco meno di vent'anni fa, già dopo la tua nascita. Eri proprio una piccolina, correvi e strisciavi sotto i tavoli e gli sgabelli, senza mai lasciare in pace Eric Udett... Ovviamente gli ho chiesto da dove fosse saltata fuori una creatura così instancabile – e lui mi ha risposto che eri nata sull'Isola qualche anno prima. Non ha detto nulla né di tuo padre, né di tua madre. E se l'ha fatto – o non l'ho ricordato, o l'ho dimenticato...";
			link.l1 = "...";
			link.l1.go = "Grinspy_18_add";
		break;
		case "Grinspy_18_add":
			StartInstantDialog("Mary", "Grinspy_19", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_19":
			dialog.text = "Sono passati così tanti anni... Capisco, Donald, giusto.";
			link.l1 = "...";
			link.l1.go = "Grinspy_19_add";
		break;
		case "Grinspy_19_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_20", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_20":
			dialog.text = "Peccato che Erik non sia qui con noi – lui era arrivato in questo posto molto prima di me. A proposito, quando raccontava delle tue solite bravate, nominava spesso Aurélie Bertin. Quella vecchietta ti adorava, questo lo ricordo bene... Non mi sono mai posto questa domanda, ma credo che quando sei venuta al mondo lei fosse già sull'Isola. Forse potrebbe aiutarti?";
			link.l1 = "...";
			link.l1.go = "Grinspy_20_add";
		break;
		case "Grinspy_20_add":
			StartInstantDialog("Mary", "Grinspy_21", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_21":
			dialog.text = "Forse. È una buona scusa per farle visita – non ricordo nemmeno l'ultima volta che sono passata da lei. Non è stato bello, giusto.";
			link.l1 = "...";
			link.l1.go = "Grinspy_21_add";
		break;
		case "Grinspy_21_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_22", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_22":
			dialog.text = "Non credo che ce l'abbia con te.   Ma non darle troppo fastidio – ho sentito che si è sentita male.   Non sia mai che ancora...";
			link.l1 = "...";
			link.l1.go = "Grinspy_22_add";
		break;
		case "Grinspy_22_add":
			StartInstantDialog("Mary", "Grinspy_23", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_23":
			dialog.text = "Zitto, Donald, ci porterai sfortuna! Aurélie ci sopravviverà a tutti, giusto?";
			link.l1 = "...";
			link.l1.go = "Grinspy_24";
		break;
		
		case "Grinspy_24":
			dialog.text = "Andiamo, "+pchar.name+"!";
			link.l1 = "...";
			link.l1.go = "Grinspy_24_add";
		break;
		case "Grinspy_24_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_25", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_25":
			dialog.text = "...";
			link.l1 = "Addio, "+npchar.name+". Ci vediamo presto.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_9");
		break;
		
		//
		case "Jillian_1":
			dialog.text = "Dio misericordioso, il mio cuore stava quasi per saltarmi fuori dal petto. Ma si può spaventare così la gente?..";
			link.l1 = "...";
			link.l1.go = "Jillian_1_add";
			DelLandQuestMark(npchar);
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_1_add":
			StartInstantDialog("Mary", "Jillian_2", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_2":
			dialog.text = "Gillian!   Non mi aspettavo di vederti qui, giusto?   Che ci fai?   E dov'è Aurélie?";
			link.l1 = "...";
			link.l1.go = "Jillian_2_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_2_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_3", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_3":
			dialog.text = "E anche a te, Mary. E a voi, "+pchar.name+". Aurelie è malata, non lo sapevi? Mi prendo cura di lei su richiesta di fratello Julian. Mi passa delle pozioni che le do da bere, ma... sembra che non servano poi molto. Ora è in cabina, a poppa, sta dormendo. L'ho portata lì per poter sistemare qui.";
			link.l1 = "...";
			link.l1.go = "Jillian_3_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_3_add":
			StartInstantDialog("Mary", "Jillian_4", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_4":
			dialog.text = "L'abbiamo saputo solo oggi, giusto? Donald ce l'ha detto. Come sta?";
			link.l1 = "...";
			link.l1.go = "Jillian_4_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_4_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_5", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_5":
			dialog.text = "Male. Si lamenta di debolezza in tutto il corpo, praticamente non si alza mai dal letto. A volte borbotta qualcosa di incomprensibile, delle sciocchezze... Ho già ascoltato così tante storie di tempi ormai passati che ho perso il conto.";
			link.l1 = "...";
			link.l1.go = "Jillian_5_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_5_add":
			StartInstantDialog("Mary", "Jillian_6", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_6":
			dialog.text = "Hmm, è proprio per una storia del genere che siamo venuti qui. Spero che non si rifiuti di parlare con noi...";
			link.l1 = "...";
			link.l1.go = "Jillian_6_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_6_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_7", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_7":
			dialog.text = "È davvero così necessario, Mary? Non credo che dovremmo disturbarla in questo stato.";
			link.l1 = "...";
			link.l1.go = "Jillian_7_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_7_add":
			StartInstantDialog("Mary", "Jillian_8", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_8":
			dialog.text = "Riguarda i miei genitori. Aurélie potrebbe averli conosciuti. Per me è davvero importante, Gillian, giusto?";
			link.l1 = "...";
			link.l1.go = "Jillian_9";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		
		case "Jillian_9":
			dialog.text = "Sull'isola non c'è una medicina che possa migliorare la sua condizione?";
			link.l1 = "...";
			link.l1.go = "Jillian_9_add";
		break;
		case "Jillian_9_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_10", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_10":
			dialog.text = "Fratello Julian le prepara delle tisane. Ma fanno effetto solo per un po'. E poi, lei si rifiuta di berle, e tocca a me versargliele in bocca quasi con la forza. A volte ho paura che possa soffocarsi davvero – devo ancora convincerla a inghiottire tutto...";
			link.l1 = "...";
			link.l1.go = "Jillian_10_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_10_add":
			StartInstantDialog("Mary", "Jillian_11", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_11":
			dialog.text = "Povera Aurélie! Davvero nessuno sull'Isola può aiutarla?";
			link.l1 = "...";
			link.l1.go = "Jillian_11_add";
		break;
		case "Jillian_11_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_12", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_12":
			dialog.text = "Lo sai bene che qui non c'è un vero medico. E poi, che potresti fare tu qui? La vecchiaia, si sa, non risparmia nessuno...";
			link.l1 = "...";
			link.l1.go = "Jillian_12_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_12_add":
			StartInstantDialog("Mary", "Jillian_13", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_13":
			dialog.text = ""+pchar.name+", magari portare qualcuno dalla nostra nave?";
			link.l1 = "Temo, "+npchar.name+", qui non serve un chirurgo di bordo, ma un medico esperto.";
			link.l1.go = "Jillian_14";
		break;
		
		case "Jillian_14":
			dialog.text = "Ora sono pronta a credere persino nella magia, se può aiutare, giusto.";
			link.l1 = "Hmm... Magia? Forse dovrei rivolgermi a Chimiset, giusto...";
			link.l1.go = "Jillian_14_add";
		break;
		case "Jillian_14_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_15", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_15":
			dialog.text = "Chimisetu?   Al mago nero? "+pchar.name+", ma davvero?";
			link.l1 = "Come mai prima. Che sia nero o bianco, è l'ultima cosa che mi preoccupa adesso. Non so chi altro possa aiutare Aurélie. Penso che nemmeno voi lo sappiate. Quindi, fatevi da parte e non osate intralciarmi.";
			link.l1.go = "Jillian_16";
			link.l2 = "Più che mai. Né le medicine né le preghiere di fratello Julian aiutano Aurélie. Chimiset è la nostra ultima speranza.";
			link.l2.go = "Jillian_17";
		break;
		
		case "Jillian_16":
			dialog.text = "Non ci posso credere alle mie orecchie! Ma quello è... un miscredente!";
			link.l1 = "E questa è una donna morente, a un passo dal dimenticare persino il suo nome. Sì, è un mago, ma ho sentito che sono capaci di molto, davvero di molto. E se riuscirà a ridarle la mente — importa davvero ora di quale fede sia?";
			link.l1.go = "Jillian_18";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddComplexSelfExpToScill(100, 100, 100, 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
		break;
		
		case "Jillian_17":
			dialog.text = "Non ci posso credere alle mie orecchie! Ma questo è... un miscredente!";
			link.l1 = "E questa è una donna morente, a un passo dal dimenticare persino il suo nome. Sì, è un mago, ma ho sentito che sono capaci di molto, davvero di molto. E se riuscirà a ridarle la mente — importa davvero ora di quale fede sia?";
			link.l1.go = "Jillian_18";
			AddCharacterExpToSkill(pchar, "Repair", 100);
		break;
		
		case "Jillian_18":
			dialog.text = ""+pchar.name+", ascoltate, anche per me Aurélie è cara... Dio mi è testimone – sto facendo tutto il possibile per alleviare le sue sofferenze! Ma davvero intendete permettere a quell'eretico nero di compiere il suo rito in questa cabina? E se durante il rito desse fuoco alla nave, o decidesse di sacrificare qualcuno?";
			link.l1 = "Non lo permetteremo, "+npchar.name+", vi assicuro.";
			link.l1.go = "Jillian_19";
		break;
		
		case "Jillian_19":
			dialog.text = "E io vi assicuro entrambi che, se qualcuno dovesse venirne a sapere... Vi rendete conto di cosa potrebbe succedere qui? Agli altri abitanti non piacerà, e ai narvali – soprattutto!";
			link.l1 = "In questo avete ragione. Non bisogna portare qui Chimiseta, ma portare Aurelie da lui.";
			link.l1.go = "Jillian_20";
		break;
		
		case "Jillian_20":
			dialog.text = "Non l'avete vista – la vecchia a malapena si regge in piedi. Sarà un miracolo se non cade fuori bordo!";
			link.l1 = "Ebbene, a volte non ci resta che sperare in un miracolo. Giusto? E, Gillian...";
			link.l1.go = "Jillian_21";
		break;
		
		case "Jillian_21":
			dialog.text = "Cos'altro?";
			link.l1 = "Spero che ne terrete il segreto. Siete una ragazza intelligente, e avete giudicato tutto correttamente... I disordini sull'Isola potrebbero facilmente sfociare in spargimenti di sangue, e nessuno lo desidera davvero, giusto?";
			link.l1.go = "Jillian_22";
			link.l2 = "A nessuno una parola, chiaro? Ci siamo fidati di voi – non costringeteci a pentircene. Penso che capiate che, se il nostro piano smetterà di essere un segreto, sull'Isola inizierà una strage come non se n'è mai vista.";
			link.l2.go = "Jillian_23";
		break;
		
		case "Jillian_22":
			dialog.text = "Va bene. Ma allora fate in modo che nessuno vi veda mentre la portate sul 'Protector'... Altrimenti dovrò rispondere a domande scomode.";
			link.l1 = "Vi risparmieremo la fatica di dare risposte scomode. Lo faremo stanotte.";
			link.l1.go = "Jillian_24";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Jillian_23":
			dialog.text = "Va bene. Ma allora fate in modo che nessuno vi veda mentre la portate sul 'Protector'... Altrimenti dovrò rispondere a domande scomode.";
			link.l1 = "Non lo permetteremo. Lo faremo stanotte.";
			link.l1.go = "Jillian_24";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddComplexSelfExpToScill(100, 100, 100, 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
		break;
		
		case "Jillian_24":
			dialog.text = "Venite dopo mezzanotte. Lei sarà qui. E per l'amor di Dio, fate attenzione.";
			link.l1 = "Non preoccupatevi, "+npchar.name+", saremo estremamente attenti.";
			link.l1.go = "Jillian_25";
		break;
		
		case "Jillian_25":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_10");
		break;
		
		case "Jillian_26":
			if (GetHour() >= 3 && GetHour() <= 24)
			{
				dialog.text = "Venite dopo mezzanotte. Sarà qui...";
				link.l1 = "Va bene.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Jillian_26";
			}
			else
			{
				dialog.text = "Aurélie è pronta. Potete portarla.";
				link.l1 = "Perfetto. Allora andiamo.";
				link.l1.go = "exit";
				DelLandQuestMark(npchar);
				AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_10_2");
			}
		break;
		
		case "Oreli_1":
			dialog.text = "Ragazzi, ma dove... dove stiamo andando?! Questo è il vascello dei Rivados! Dov'è Erik?!";
			link.l1 = "Eric è diventato amico di Eddie Black, non lo sapevi, giusto?";
			link.l1.go = "Oreli_2";
		break;
		
		case "Oreli_2":
			dialog.text = "Ma cosa dici, ragazzo! Giusto? Erik non sopporta proprio i neri!";
			link.l1 = "Caspita! Allora chiediamogli pure che diavolo ci sta facendo qui, giusto?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_11");
		break;
		
		case "Eddy_1":
			dialog.text = "Guardate un po', chi si è fatto vivo! "+GetFullName(pchar)+" in persona! Felice di accogliere mio fratello bianco, ah-ah! Allora, racconta, cosa ti porta qui!";
			link.l1 = "E anche a te ciao, "+npchar.name+". Vorrei passare solo per una tazza di rum, ma temo di avere un affare urgente con te, o meglio, con Chimisetu.";
			link.l1.go = "Eddy_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Eddy_2":
			dialog.text = "Ti siamo debitori, amico mio. Faremo tutto ciò che è in nostro potere.";
			link.l1 = "Va bene, se è così. Perché non ho più nessuno su cui contare.";
			link.l1.go = "Eddy_3";
		break;
		
		case "Eddy_3":
			dialog.text = "Di quale di queste signore hai bisogno di aiuto, "+pchar.name+"?";
			link.l1 = "Non so se fai sul serio o stai scherzando, "+npchar.name+", ma non mi viene da ridere. L'aiuto serve ad Aurélie, ovviamente.";
			link.l1.go = "Eddy_3_add";
		break;
		case "Eddy_3_add":
			StartInstantDialog("LSC_Oreli", "Eddy_4", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Eddy_4":
			dialog.text = "Eric! ERIC! Fatti vedere, vecchio furfante! Che razza di scherzi sono questi?! Porta subito qui il tuo sedere magro!";
			link.l1 = "...";
			link.l1.go = "Eddy_4_add";
		break;
		case "Eddy_4_add":
			StartInstantDialog("Eddy", "Eddy_5", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Eddy_5":
			dialog.text = "Quindi era vero... I miei uomini mi avevano detto che questa rovina ha il cervello tutto storto. Ora vedo che avevano ragione. Ma non capisco proprio cosa vuoi da Rivados...";
			link.l1 = "Lascia che parli con Chimiset, e capirai tutto...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_12");
		break;
		
		case "Chimset_1":
			dialog.text = "Parla, mio caro amico. Sono pronta ad ascoltarti con attenzione.";
			link.l1 = "Sarò breve, Chimiset. Oréli possiede le informazioni che io e Mary cerchiamo. Ma a causa delle sue condizioni, dovute, se ho capito bene, semplicemente all'età avanzata, noi... non possiamo né ottenere da lei questi dati né essere certi che siano corretti. Ho sentito dei miracoli di cui sono capaci sia gli sciamani indiani che africani — ed è per questo che sono venuto a chiedere il tuo aiuto, Chimiset.";
			link.l1.go = "Chimset_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Chimset_2":
			dialog.text = "Ti ho sentito, amico mio. Gli sciamani possiedono poteri misteriosi e mistici, spesso incomprensibili e inaccessibili agli estranei, perfino ai propri fratelli di tribù, per non parlare dei bianchi. Alcuni lo chiamano stregoneria, altri un miracolo. In effetti, possiamo fare molte cose – ma nessuno può far scorrere un fiume all'indietro... E nemmeno fermarlo.";
			link.l1 = "Cosa intendi, Chimiset?";
			link.l1.go = "Chimset_3";
		break;
		
		case "Chimset_3":
			dialog.text = "Parlo del fiume del tempo, amico mio. O del fiume della vita – come preferisci. Vedi, hai perfettamente ragione: la radice della malattia di questa poveretta sta proprio nei suoi anni, e in nient'altro.";
			link.l1 = "Ho sentito qualcosa a riguardo. So solo che non è poi un problema così raro.";
			link.l1.go = "Chimset_4";
		break;
		
		case "Chimset_4":
			dialog.text = "Hai ragione. Le persone della sua età spesso si perdono nelle valli dei sogni, e a volte degli incubi. Tornano indietro, solo per essere trascinate di nuovo laggiù – non tanto per loro scelta, quanto per forze misteriose che li attirano. Col passare del tempo, la malattia si fa sempre più forte – e così, la persona non ricorda più né se stessa, né i suoi amici.";
			link.l1 = "Quindi, non puoi farci proprio niente, giusto?";
			link.l1.go = "Chimset_5";
		break;
		
		case "Chimset_5":
			dialog.text = "Scacciare la malattia – no. Non è nelle mie forze. Ma posso fare qualcos'altro...";
			link.l1 = "Cosa esattamente?";
			link.l1.go = "Chimset_6";
		break;
		
		case "Chimset_6":
			dialog.text = "Nel momento in cui questa donna tornerà in sé, eseguirò rapidamente un rituale per il quale mi sarò già preparato...";
			link.l1 = "Se non la fermerà, almeno rallenterà il progresso della malattia?";
			link.l1.go = "Chimset_7";
		break;
		
		case "Chimset_7":
			dialog.text = "Non proprio. La costringerà a richiamare tutte le sue forze vitali per mantenere la lucidità il più a lungo possibile.";
			link.l1 = "Quanto a lungo intendi dire?";
			link.l1.go = "Chimset_8";
		break;
		
		case "Chimset_8":
			dialog.text = "Non dipende dal rituale, ma dalla persona. Qualcuno resiste una settimana, qualcun altro un mese... Ho sentito parlare di un uomo che è rimasto lucido e con la mente chiara per più di un anno, quasi... E quando tutti ormai pensavano che fosse guarito, la malattia è tornata – e se l'è portato via quella stessa notte.";
			link.l1 = "Per scoprire quello che ci serve ci basterà un'ora. Quando potrai fare il rituale, Chimiset?";
			link.l1.go = "Chimset_9";
		break;
		
		case "Chimset_9":
			dialog.text = "Porterò via la donna subito, la condurrò nella stiva – lì ho allestito un santuario... proprio per queste cose. Poi tutto dipenderà da quando tornerà in uno stato normale... Ma penso che per domattina avremo finito.";
			link.l1 = "Allora non vi disturberò oltre. E che ti aiuti... il tuo Dio, Chimiset.";
			link.l1.go = "Chimset_10";
		break;
		
		case "Chimset_10":
			dialog.text = "Grazie! Aiutami a portare la donna bianca nella stiva.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_13");
		break;
		
		case "Chimset_11":
			dialog.text = "Ce l'abbiamo fatta, fratello bianco. Ci siamo riusciti...";
			link.l1 = "...";
			link.l1.go = "Chimset_11_add";
			DelLandQuestMark(npchar);
		break;
		case "Chimset_11_add":
			StartInstantDialog("LSC_Oreli", "Chimset_12", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Chimset_12":
			dialog.text = "Oh, "+GetFullName(pchar)+"! Non sapevo che tu e Mary foste tornati sull'Isola! Che incontro piacevole!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_14_1");
		break;
		
		case "Chimset_13":
			dialog.text = "...";
			link.l1 = "Chimiset, grazie! Non so nemmeno come ringraziarti...";
			link.l1.go = "Chimset_14";
			link.l2 = "Beh guarda un po', Chimiset ce l'ha fatta! Non avevo dubbi su di te, giusto?...";
			link.l2.go = "Chimset_15";
		break;
		
		case "Chimset_14":
			dialog.text = "Tutti i Rivadòs ti sono eternamente debitori, amico mio! Le porte del 'Protettore' sono sempre aperte per te.";
			link.l1 = "Spero di non dovervi disturbare ancora... Mary, Aurélie, dobbiamo tornare sulla 'Pluto'.";
			link.l1.go = "Chimset_15_add";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "Chimset_15":
			dialog.text = "Tutti i rivados ti saranno eternamente debitori, amico mio! Le porte del 'Protettore' per te sono sempre aperte.";
			link.l1 = "Spero di non dovervi disturbare ancora... Mary, Aurélie, dobbiamo tornare sulla 'Pluto'.";
			link.l1.go = "Chimset_15_add";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;
		case "Chimset_15_add":
			StartInstantDialog("LSC_Oreli", "Chimset_16", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Chimset_16":
			dialog.text = "Mi sono persa via, dimenticando persino come ho lasciato la mia cabina... Eh, questa vecchiaia – la memoria non vale proprio niente, giusto? ";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_15");
		break;
		
		case "Oreli_11":
			dialog.text = "Allora, signorina, cosa ci fate nella mia cabina?";
			link.l1 = "...";
			link.l1.go = "Oreli_11_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("LSC_Jillian_clone"));
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_11_add":
			StartInstantDialog("LSC_Jillian_clone", "Oreli_12", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_12":
			dialog.text = "Oreli, io...";
			link.l1 = "...";
			link.l1.go = "Oreli_12_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("LSC_Jillian_clone"));
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_12_add":
			StartInstantDialog("Mary", "Oreli_13", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_13":
			dialog.text = "Aurélie, le ho chiesto io di sistemare qui mentre tu non c'eri. Non c'è motivo che tu ti pieghi con le ginocchia malate...";
			link.l1 = "...";
			link.l1.go = "Oreli_13_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
			
		break;
		case "Oreli_13_add":
			StartInstantDialog("LSC_Jillian_clone", "Oreli_14", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_14":
			dialog.text = "Pulire?! Tu...";
			link.l1 = "Jillian, grazie per il tuo aiuto. (sussurrando) Ce l'abbiamo fatta. Chimiset ce l'ha fatta.";
			link.l1.go = "Oreli_15";
		break;
		
		case "Oreli_15":
			dialog.text = "Non può essere...";
			link.l1 = "Come vedi. E ora, per favore, lasciaci parlare.";
			link.l1.go = "Oreli_15_add";
		break;
		case "Oreli_15_add":
			StartInstantDialog("LSC_Oreli", "Oreli_16", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_16":
			dialog.text = "Ebbene, ragazzi, grazie per aver accompagnato una vecchia signora. Temo che presto smetterò del tutto di uscire. Le mie gambe, le mie gambe...";
			link.l1 = "Se permette, "+npchar.name+", ci fermeremo da voi – solo per poco. Io e Mary abbiamo una questione molto importante da discutere con voi.";
			link.l1.go = "Oreli_17";
		break;
		
		case "Oreli_17":
			dialog.text = "Se non dovrò di nuovo trascinarmi su un'altra nave, ti aiuterò come posso. Ti ascolto.";
			link.l1 = "...";
			link.l1.go = "Oreli_17_add";
		break;
		case "Oreli_17_add":
			StartInstantDialog("Mary", "Oreli_18", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_18":
			dialog.text = "Aurélie, voglio che tu mi racconti dei miei genitori. E del giorno in cui sono venuta al mondo. È successo qui, sull'Isola, giusto? Donald dice che è così, ma lui allora non era ancora qui, quindi non può saperlo con certezza. Però tu vivi qui da molto più tempo di lui, giusto! Da più di vent'anni, vero?";
			link.l1 = "...";
			link.l1.go = "Oreli_18_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_18_add":
			StartInstantDialog("LSC_Oreli", "Oreli_19", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_19":
			dialog.text = "Piano piano, ragazza, non parlare così in fretta, ti prego! Altrimenti non riesco a starti dietro...";
			link.l1 = "...";
			link.l1.go = "Oreli_19_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_19_add":
			StartInstantDialog("Mary", "Oreli_20", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_20":
			dialog.text = "Chiaro, giusto. Va bene, ripetiamo ancora una volta...";
			link.l1 = "...";
			link.l1.go = "Oreli_20_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_20_add":
			StartInstantDialog("LSC_Oreli", "Oreli_21", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_21":
			dialog.text = "Non serve, Mary, non sono ancora così malandata, ah-ah... Ho sentito quello che mi hai detto. Ma, visto che davvero vivo sull'Isola più a lungo di tutti, spero che tu abbia rispetto e comprensione per la mia età...";
			link.l1 = "...";
			link.l1.go = "Oreli_21_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_21_add":
			StartInstantDialog("Mary", "Oreli_22", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_22":
			dialog.text = "Ma certo, Aurélie! Come hai potuto pensare il contrario?";
			link.l1 = "...";
			link.l1.go = "Oreli_22_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_22_add":
			StartInstantDialog("LSC_Oreli", "Oreli_23", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_23":
			dialog.text = "Eh, guardo i giovani d'oggi e… no, no, noi non ci comportavamo così con i più grandi. Ma tu non c'entri, ovviamente. Volevo solo dire che sarà più facile se rispondo alle tue domande una alla volta, invece che a tutte insieme…";
			link.l1 = "...";
			link.l1.go = "Oreli_23_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_23_add":
			StartInstantDialog("Mary", "Oreli_24", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_24":
			dialog.text = "Capisco, Aurélie. Come preferisci tu, giusto? Quindi eri sull'Isola quando sono nata? Se è successo qui, ovviamente...";
			link.l1 = "...";
			link.l1.go = "Oreli_24_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_24_add":
			StartInstantDialog("LSC_Oreli", "Oreli_25", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_25":
			dialog.text = "Sono arrivata sull'Isola nel 1633, a volte quella giornata mi torna negli incubi. La tempesta, la nostra 'Reprisal' – il fluyt su cui io e mio marito stavamo navigando verso la Florida – sbattuto dalle onde, pronto a capovolgersi da un momento all'altro, e noi che ripetevamo tutte le preghiere che conoscevamo e ne inventavamo di nuove… E poi uno schianto e…";
			link.l1 = "...";
			link.l1.go = "Oreli_25_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_25_add":
			StartInstantDialog("Mary", "Oreli_26", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_26":
			dialog.text = "Quindi sei arrivata qui cinque anni prima che io nascessi, giusto.";
			link.l1 = "...";
			link.l1.go = "Oreli_26_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_26_add":
			StartInstantDialog("LSC_Oreli", "Oreli_27", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_27":
			dialog.text = "Più o meno così. Allora qui era tutto un po' diverso – il 'San Geronimo' galleggiava ancora, l'anello esterno delle navi era più piccolo di una volta e mezza, se non il doppio... E non sono nemmeno tutte le navi che restano a galla! Ecco cosa vi dico, ragazzi, se guardate il fondo in una giornata limpida – vi prenderà il terrore, da quante carcasse di navi ci sono laggiù...";
			link.l1 = "...";
			link.l1.go = "Oreli_27_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_27_add":
			StartInstantDialog("Mary", "Oreli_28", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_28":
			dialog.text = "Ci interessa la nave su cui sono arrivati qui i miei genitori. Con me... o senza di me?";
			link.l1 = "...";
			link.l1.go = "Oreli_28_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_28_add":
			StartInstantDialog("LSC_Oreli", "Oreli_29", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_29":
			dialog.text = "Con te, ragazza, con te.";
			link.l1 = "...";
			link.l1.go = "Oreli_29_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_29_add":
			StartInstantDialog("Mary", "Oreli_30", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_30":
			dialog.text = "Quindi, sono davvero nata sulla Terraferma, giusto?";
			link.l1 = "...";
			link.l1.go = "Oreli_30_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_30_add":
			StartInstantDialog("LSC_Oreli", "Oreli_31", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_31":
			dialog.text = "No, intendevo 'con te' in un senso un po' diverso. Eri nella pancia di tua madre e sei nata una settimana dopo.";
			link.l1 = "Secondo te, Aurélie, è divertente?";
			link.l1.go = "Oreli_32";
			link.l2 = "Non ha perso il senso dell'umorismo con gli anni, Aurélie.";
			link.l2.go = "Oreli_33";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		
		case "Oreli_32":
			dialog.text = "Beh, rido di me stessa molto più spesso che degli altri. Scusa, Mary, non volevo offenderti.";
			link.l1 = "...";
			link.l1.go = "Oreli_33_add";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), pchar);
		break;
		
		case "Oreli_33":
			dialog.text = "Beh, rido di me stessa molto più spesso che degli altri. Scusa, Mary, non volevo offenderti.";
			link.l1 = "...";
			link.l1.go = "Oreli_33_add";
			AddCharacterExpToSkill(pchar, "Commerce", 100);
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), pchar);
		break;
		case "Oreli_33_add":
			StartInstantDialog("Mary", "Oreli_34", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_34":
			dialog.text = "Va tutto bene, Aurélie. Ti prego, continua pure, giusto? Che ne è stato dei miei genitori dopo la mia nascita?";
			link.l1 = "...";
			link.l1.go = "Oreli_34_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_34_add":
			StartInstantDialog("LSC_Oreli", "Oreli_35", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_35":
			dialog.text = "Dopo? Tesoro mio, è già un miracolo che siano arrivati entrambi fino a quel momento! Che tempesta terribile infuriava quella notte di giugno! Quando la mattina dopo la scialuppa portò tua madre sull'anello interno, pochi credettero subito ai propri occhi – che una donna incinta, pronta a partorire da un momento all'altro, fosse sopravvissuta a un naufragio così spaventoso. Povera Teresa, me lo ricordo come se fosse ieri...";
			link.l1 = "...";
			link.l1.go = "Oreli_35_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_35_add":
			StartInstantDialog("Mary", "Oreli_36", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_36":
			dialog.text = "Teresa? Così si chiamava?";
			link.l1 = "...";
			link.l1.go = "Oreli_36_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_36_add":
			StartInstantDialog("LSC_Oreli", "Oreli_37", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_37":
			dialog.text = "Sì, così si è presentata – ed è stato quasi tutto ciò che ha detto. Alla fine della giornata è caduta in delirio, in cui è rimasta fino al parto. Nessuno era sicuro che sarebbe riuscita a partorire, e ancor meno che il bambino sarebbe nato vivo – dopo tutto quello che aveva passato. Ma Teresa ce l'ha fatta. Ce l'ha fatta – e poi ha esalato l'ultimo respiro. Che Dio abbia pietà della sua anima...";
			link.l1 = "...";
			link.l1.go = "Oreli_37_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_37_add":
			StartInstantDialog("Mary", "Oreli_38", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_38":
			dialog.text = "Mamma è morta, e io sono rimasta con mio padre? Ma allora perché tutti dicevano che sono stata cresciuta da Eric Udett? E...";
			link.l1 = "...";
			link.l1.go = "Oreli_38_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_38_add":
			StartInstantDialog("LSC_Oreli", "Oreli_39", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_39":
			dialog.text = "Mary, cara, ti avevo chiesto... Non sommergermi di tutte queste domande, giusto?";
			link.l1 = "...";
			link.l1.go = "Oreli_39_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_39_add":
			StartInstantDialog("Mary", "Oreli_40", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_40":
			dialog.text = "Scusa, Aurélie, mi sono distratta, giusto? Mio padre, anche lui è sopravvissuto a un naufragio?";
			link.l1 = "...";
			link.l1.go = "Oreli_40_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_40_add":
			StartInstantDialog("LSC_Oreli", "Oreli_41", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_41":
			dialog.text = "Tuo padre... Sai, non ho molto da dire su tuo padre – tranne che non augurerei un padre simile a nessuno. Pochi giorni dopo la tua nascita è sparito, lasciandoti in balia del destino. Sei stata fortunata che Eric avesse un cuore così buono e gentile – come un biscotto secco ammorbidito in una tazza di grog...";
			link.l1 = "...";
			link.l1.go = "Oreli_41_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_41_add":
			StartInstantDialog("Mary", "Oreli_42", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_42":
			dialog.text = "Dimmi almeno come si chiamava, giusto!";
			link.l1 = "...";
			link.l1.go = "Oreli_42_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_42_add":
			StartInstantDialog("LSC_Oreli", "Oreli_43", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_43":
			dialog.text = "Oh... O era Jeffrey, o era John, che Dio mi aiuti a ricordare...";
			link.l1 = "Quindi, non ricordate? Giusto, "+npchar.name+"?";
			link.l1.go = "Oreli_44";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		
		case "Oreli_44":
			dialog.text = "Dubbiti delle mie parole, giovanotto?!";
			link.l1 = "Zitta, "+npchar.name+", più piano. Non volevo offendervi. È solo che mi è sembrato che ricordiate piuttosto bene quei giorni, tutto qui.";
			link.l1.go = "Oreli_45";
			link.l2 = "Non ho alcun dubbio, "+npchar.name+". Sto solo cercando di ricordare bene tutti i dettagli, nient'altro. Ma tutta questa confusione rende il compito un po' più difficile.";
			link.l2.go = "Oreli_46";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), pchar);
		break;
		
		case "Oreli_45":
			dialog.text = "La memoria è una signora selettiva, "+pchar.name+", molto selettiva. Soprattutto dopo tutti questi anni. È difficile dimenticare Teresa – l'ho osservata soffrire per tutta la settimana! O-oh, quanto mi dispiaceva per lei!";
			link.l1 = "E suo marito, non era forse accanto a lei?";
			link.l1.go = "Oreli_47";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "Oreli_46":
			dialog.text = "La memoria è una signora selettiva, "+pchar.name+", molto selettiva. Soprattutto dopo tutti questi anni. È difficile dimenticare Teresa – l'ho vista soffrire per tutta la settimana! Oh, quanto mi dispiaceva per lei!";
			link.l1 = "E suo marito, non era forse accanto a lei?";
			link.l1.go = "Oreli_47";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Oreli_47":
			dialog.text = "Molto raramente. Per quasi tutta la settimana spariva da qualche parte – era sempre in cerca di medicine e pozioni, che allora sull'Isola scarseggiavano davvero...";
			link.l1 = "Quindi era un buon marito, visto che cercava di aiutare sua moglie.";
			link.l1.go = "Oreli_48";
		break;
		
		case "Oreli_48":
			dialog.text = "Forse come marito era anche bravo. Non ho mai detto il contrario, se mi permetti. Non cercare di confondermi, ragazzo!";
			link.l1 = "Non ci ho mai nemmeno pensato, te lo assicuro, "+npchar.name+".   È semplicemente ovvio che non avete una grande opinione su di lui.   E il fatto che non ricordiate nemmeno il suo nome...";
			link.l1.go = "Oreli_49";
		break;
		
		case "Oreli_49":
			dialog.text = "Ho visto quell'uomo quasi di sfuggita, nell'oscurità della cabina di 'Ceres Smithy', là dove ora vive Herr Jurgen. Veniva solo di notte, e il suo volto lo ricordo molto vagamente. Quanto al suo nome – nessuno lo chiamava mai per nome, solo per cognome. Casper qua, Casper là...";
			link.l1 = "Ho capito, "+npchar.name+". Quindi, Mary è nata e dopo qualche giorno lui è sparito senza lasciare traccia. L'hanno ucciso?";
			link.l1.go = "Oreli_50";
		break;
		
		case "Oreli_50":
			dialog.text = "Domanda difficile, ragazzo. Vede, qui è piuttosto complicato tenere qualcosa segreto – tutto è sotto gli occhi di tutti. Quando scoppia un altro litigio – anche all'interno delle navi – il giorno dopo lo sa già tutta l'Isola.";
			link.l1 = "Non c'è da stupirsi.";
			link.l1.go = "Oreli_51";
		break;
		
		case "Oreli_51":
			dialog.text = "I corpi degli uccisi non si trovano quasi mai – i più esperti li fanno sparire, legando mani e piedi con catene o fissando palle di cannone o pietre. E i granchi sul fondo finiscono il lavoro. Però, gli oggetti personali delle vittime riemergono subito o dopo un po'.";
			link.l1 = "Dal fondo?!";
			link.l1.go = "Oreli_52";
		break;
		
		case "Oreli_52":
			dialog.text = "Certo che no! Intendevo dire che ogni tanto saltano all'occhio – un anello, una pistola con le iniziali, una sciabola da premio... Su queste cose fanno poche domande. Tanto la persona non la riporti indietro, e litigare per niente non serve a nessuno.";
			link.l1 = "Jeffrey o John Casper avevano qualcosa di riconoscibile?";
			link.l1.go = "Oreli_53";
		break;
		
		case "Oreli_53":
			dialog.text = ""+pchar.name+", Signore, ma io nemmeno mi ricordo il suo nome, e voi mi fate certe domande! Se pure fosse successo qualcosa, non ho sentito che quell'oggetto sia finito a qualcun altro sull'Isola. All'epoca lavoravo come cameriera in taverna, e poche voci mi sfuggivano. Ma questo non vuol dire che sapessi proprio tutto.";
			link.l1 = "Quando si dice che le persone spariscono senza lasciare traccia – di solito si intende che sono state uccise. Ma nel caso del signor Casper, non ne siete poi così sicuri...";
			link.l1.go = "Oreli_54";
		break;
		
		case "Oreli_54":
			dialog.text = "Dico solo che 'scomparso' non vuol dire affatto 'morto'. Soprattutto in quegli anni, quando tra l'Isola e Cuba passavano spesso tartane di contrabbandieri e ricettatori... Sapete, non ricordo i lineamenti del suo viso, ma il suo sguardo... Era lo sguardo di uno che non si perde da nessuna parte. O almeno, ci crede davvero con tutto il cuore.";
			link.l1 = "Tartane, tartane... Nulla è impossibile, giusto? Se solo conoscessimo il suo nome, potremmo consultare gli archivi coloniali di quegli anni. Ma sarebbe molto più semplice se avessimo il tipo e il nome della nave su cui è 'arrivato' qui.";
			link.l1.go = "Oreli_55";
		break;
		
		case "Oreli_55":
			dialog.text = "E cosa mi guardi così, ragazzo? Pensi che io possa ricordarlo?";
			link.l1 = "Speriamo in questo, "+npchar.name+" - considerando quanto già ci avete raccontato.";
			link.l1.go = "Oreli_56";
			link.l2 = "Hmm... Ho dei grossi dubbi a riguardo.";
			link.l2.go = "Oreli_57";
		break;
		
		case "Oreli_56":
			dialog.text = "Forse volete anche sapere quante cannoni aveva e di che calibro erano? Caro mio, sapete quante navi sono affondate qui in tutti questi anni? E pensate davvero che io le ricordi tutte? Inoltre, di quella nave si sono salvate solo poche persone – non è rimasta a galla nemmeno un giorno, sapete...";
			link.l1 = "Chiaro... Beh, ci sta, sono passati vent'anni. Grazie per non aver dimenticato almeno quello che ci hanno raccontato.";
			link.l1.go = "Oreli_58";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "Oreli_57":
			dialog.text = "Forse volete anche sapere quante cannoni aveva e di che calibro erano? Caro mio, sapete quante navi sono affondate qui in tutti questi anni? E pensate davvero che io le ricordi tutte? Inoltre, da quella nave si sono salvate solo poche persone – non è rimasta a galla nemmeno un giorno, sapete...";
			link.l1 = "Chiaro... Beh, è comprensibile, sono passati vent'anni. Grazie per non aver dimenticato almeno quello che ci hanno raccontato.";
			link.l1.go = "Oreli_58";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Oreli_58":
			dialog.text = "Spero che non stiate scherzando e non vogliate prendervi gioco di una vecchia la cui memoria è diventata un colabrodo.";
			link.l1 = "In nessun modo, "+npchar.name+"Ci avete davvero aiutato tantissimo. Rimettetevi presto. Beh, noi andiamo.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_16");
		break;
		
		case "Mary_91":
			dialog.text = "Quindi, Teresa... Così si chiamava. Povera la mia mamma, giusto...";
			link.l1 = "Beh, almeno ora sappiamo da chi hai preso tutta questa forza e testardaggine. Una donna incinta su una nave che sta affondando... Mi vengono i brividi solo a pensarci.";
			link.l1.go = "Mary_92";
		break;
		
		case "Mary_92":
			dialog.text = "Ma cosa ci faceva in quello stato su questa nave, "+pchar.name+"?! Bisogna proprio essere pazza per decidere una cosa del genere!";
			link.l1 = "A questa domanda può rispondere solo tuo padre – John, Jack, Jacob, Jasper, Jordan...";
			link.l1.go = "Mary_94";
		break;
		
		case "Mary_94":
			dialog.text = "Hai deciso di ricordare tutti i nomi inglesi che iniziano per “J”? Eppure Aurélie ha nominato solo Jeffrey e John, giusto.";
			link.l1 = "Forse semplicemente non si è ricordata degli altri, come me? Sai, l'età e tutto il resto...";
			link.l1.go = "Mary_95";
		break;
		
		case "Mary_95":
			dialog.text = ""+pchar.name+", pensi...";
			link.l1 = "Non mi fiderei completamente della sua memoria in questo momento. Ma anche se fosse così, dovremo consultare non solo gli archivi coloniali, ma quelli della Marina per il 1638, il che è molto più complicato: le informazioni sono riservate, soprattutto se riguardano ufficiali. E dubito fortemente che a un semplice marinaio sarebbe stato permesso portare a bordo la moglie.";
			link.l1.go = "Mary_96";
		break;
		
		case "Mary_96":
			dialog.text = "D'altra parte, trovare informazioni su un ufficiale è molto più facile che su un semplice marinaio.";
			link.l1 = "Se conosciamo il nome della nave. O il suo nome completo. E non solo 'Jeffrey o John o, alla peggio, Jack...'. E ci andrà ancora bene, se la nave era militare. I mercanti, invece, con le liste degli equipaggi stanno messi molto peggio.";
			link.l1.go = "Mary_97";
		break;
		
		case "Mary_97":
			dialog.text = "Ma allora cosa dovremmo fare, "+pchar.name+"? Parlare ancora con Aurélie? Abbiamo già tirato fuori da lei tutto quello che potevamo, non ti pare?";
			link.l1 = "Non con Aurélie. Con Donald.";
			link.l1.go = "Mary_98";
		break;
		
		case "Mary_98":
			dialog.text = "E come ci aiuterà? Ha detto che nel 1638 non si trovava nemmeno vicino all'Isola della Giustizia, giusto?";
			link.l1 = "Ma gli altri narvali erano qui, giusto?";
			link.l1.go = "Mary_99";
		break;
		
		case "Mary_99":
			dialog.text = "Non capisco molto bene dove vuoi arrivare, giusto?";
			link.l1 = "Vedrai, cara, vedrai. C'è ancora un filo da tirare. Andiamo.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_17");
		break;
		
		case "Grinspy_31":
			dialog.text = "Ah, di nuovo voi! Allora, come vanno le vostre ricerche?";
			link.l1 = "Ciao, "+npchar.name+". Potrebbe andare meglio – per ora vaghiamo come in una caverna di misteri e segreti. Ma sento che l'uscita è già vicina.";
			link.l1.go = "Grinspy_32";
			link.l2 = "E anche a te, ciao "+npchar.name+" . Meglio di quanto potessi immaginare all'inizio. La situazione... non è poi così disperata.";
			link.l2.go = "Grinspy_33";
			DelLandQuestMark(npchar);
		break;
		
		case "Grinspy_32":
			dialog.text = "Sono felice di sentirlo. Davvero. Però, di nuovo avete bisogno di qualcosa da me, giusto? Cosa siete riusciti a scoprire?";
			link.l1 = "Mary è nata qui, sull'Isola, nel giugno del 1638. Sua madre, Teresa, è morta subito dopo il parto. Il padre – un certo Casper – è sparito nel nulla pochi giorni dopo la nascita di Mary. Di lui non sappiamo nulla, se non che il suo nome inizia per 'J.'. C'è chi pensa che non sia finito in pasto ai granchi nelle secche locali, ma che abbia lasciato l'Isola su una delle tartane dei contrabbandieri...";
			link.l1.go = "Grinspy_34";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Grinspy_33":
			dialog.text = "Felice di sentirlo. Davvero. Però, anche stavolta avete bisogno di qualcosa da me, giusto? Cosa siete riusciti a scoprire?";
			link.l1 = "Mary è nata qui, sull'Isola, nel giugno del 1638. Sua madre, Teresa, è morta subito dopo il parto. Il padre – un certo Casper – è sparito nel nulla pochi giorni dopo la nascita di Mary. Di lui non sappiamo nulla, se non che il suo nome inizia con la 'J'. C'è chi pensa che non sia diventato cibo per granchi nelle secche locali, ma che abbia lasciato l'Isola su una delle tartane dei contrabbandieri...";
			link.l1.go = "Grinspy_34";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Grinspy_34":
			dialog.text = "E hai abbandonato tua figlia? Un gesto strano.";
			link.l1 = "È proprio così. Ma nessuno, tranne quel tale signor J., potrà spiegarlo.";
			link.l1.go = "Grinspy_35";
		break;
		
		case "Grinspy_35":
			dialog.text = "E pensate che sia ancora vivo?   E per questo lo state cercando?";
			link.l1 = "Non solo per questo. Vogliamo scoprire chi era, come viveva. Per Mary è davvero importante.";
			link.l1.go = "Grinspy_36";
		break;
		
		case "Grinspy_36":
			dialog.text = "Hm, capisco. E mi dispiace che non posso davvero aiutarvi in nessun modo...";
			link.l1 = "In realtà, puoi. Dimmi, i narvali tengono una sorta di registro delle navi affondate presso l'Isola?";
			link.l1.go = "Grinspy_37";
		break;
		
		case "Grinspy_37":
			dialog.text = "Non capisco bene cosa intendi, "+pchar.name+".";
			link.l1 = "Grinspie, Grinspie... Non dimenticare che ancora scaldi la sedia qui solo grazie a me. Quindi fai il bravo – non mettere alla prova la mia pazienza.";
			link.l1.go = "Grinspy_38";
			link.l2 = "Sono sicura che capisci, Donald. E in nome della nostra amicizia non cercherai di svicolare.";
			link.l2.go = "Grinspy_39";
		break;
		
		case "Grinspy_38":
			dialog.text = "Hmm...";
			link.l1 = "Alle navi capita di tanto in tanto di essere spinte verso l'anello esterno. Alcune affondano subito, altre restano a galla per un po' – vengono perquisite e da esse si prende tutto ciò che ha valore. Non so come sia con i rivados, ma dubito che i narvali si accapiglino per ogni cianfrusaglia trovata a bordo – più probabile che mettano tutto in un unico bottino, poi fanno l'inventario di ogni cosa, e solo dopo di questo dividono il bottino.";
			link.l1.go = "Grinspy_40";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
		break;
		
		case "Grinspy_39":
			dialog.text = "Hmm...";
			link.l1 = "Alle navi capita periodicamente di essere spinte verso l'anello esterno. Alcune affondano subito, altre restano a galla per un po' – vengono perquisite e da esse si prende tutto ciò che vale. Non so come sia con i rivados, ma dubito che i narvali si azzuffino per ogni cianfrusaglia trovata a bordo – più probabile che buttino tutto in un unico mucchio, poi fanno l'inventario di ogni cosa, e solo dopo di ciò dividono il bottino.";
			link.l1.go = "Grinspy_40";
			AddCharacterExpToSkill(pchar, "Commerce", 100);
		break;
		
		case "Grinspy_40":
			dialog.text = "Non sei stupido, "+pchar.name+". A differenza di molti qui. Giusto? Sì, più o meno tutto va proprio così. Personalmente, questa burocrazia mi dà il voltastomaco, ma si faceva già ai tempi di Alan Milrow e di quelli che guidavano il clan 'Narvalo' prima di lui. Teniamo questi registri – e non solo: annotiamo persino le navi su cui sono arrivati prima i rivados o i pirati. Ma in questi casi, ovviamente, non sappiamo chi c'era e cosa ci fosse a bordo...";
			link.l1 = "A giudicare dal fatto che i genitori di Mary furono portati dopo il naufragio sulla 'Ceres Smithy', la loro nave fu trovata proprio dai narvali. Quindi, ci deve essere una registrazione corrispondente.";
			link.l1.go = "Grinspy_41";
		break;
		
		case "Grinspy_41":
			dialog.text = "Potrebbe anche essere così. Non posso dirlo con certezza. E non potrò mai.";
			link.l1 = "Ora sono io che non capisco cosa intendi, "+npchar.name+".";
			link.l1.go = "Grinspy_42";
		break;
		
		case "Grinspy_42":
			dialog.text = "I registri delle navi perdute. Quando Leighton Dexter è diventato Ammiraglio dopo la partenza di Dodson, ci ha portato via questi documenti.";
			link.l1 = "Hai semplicemente preso e portato via?   E tu non ti sei opposto?";
			link.l1.go = "Grinspy_43";
		break;
		
		case "Grinspy_43":
			dialog.text = "Beh, prima di tutto, è stato abbastanza gentile. In secondo luogo, ha promesso di restituirli presto. E poi... a che diavolo mi servono quei fogli, giusto?";
			link.l1 = "Non sono proprio appunti inutili, giusto?";
			link.l1.go = "Grinspy_44";
		break;
		
		case "Grinspy_44":
			dialog.text = "Ve l'ho detto, è solo una tradizione, volta principalmente a evitare che i membri del nostro clan si sbranino tra loro per il bottino delle navi. La nave è stata portata a riva, abbiamo preso tutto ciò che potevamo, fatto l'inventario, diviso qualcosa, nascosto il resto nelle nostre stive — e basta. Perché riempire gli armadi? Si è liberato un po' di spazio — forse dovrei persino ringraziare l'Ammiraglio per questo.";
			link.l1 = "E va bene, chiaro. Allora puntiamo su 'San Agustin'. Ma forse passeremo ancora da te, "+npchar.name+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_18");
		break;
		
		case "WildRose_Dexter_1":
            dialog.text = "A, "+pchar.name+", avanti, avanti. Sei qui per affari, amico, o sei solo passato a trovarmi?";
            link.l1 = "Questa volta, è per una questione seria. Diciamo così, è personale.";
            link.l1.go = "WildRose_Dexter_2";
			DelLandQuestMark(npchar);
        break;

        case "WildRose_Dexter_2":
            dialog.text = "E abbastanza importante per te – a giudicare da quanto sei agitato.";
            link.l1 = "Davvero? Direi piuttosto stanco. Ho dovuto gironzolare parecchio per i tuoi domini negli ultimi giorni. Le articolazioni cominciano già a farsi sentire – e io che ingenuamente pensavo che succedesse solo ai vecchietti come te.";
            link.l1.go = "WildRose_Dexter_3_1";
            link.l2 = "Un po' senza fiato, tutto qui. Vedi, non sto solo seduto sulla sedia. Ma tu, invece, vedo che le gambe proprio non ti reggono più, ah-ah-ah!";
            link.l2.go = "WildRose_Dexter_3_2";
        break;

        case "WildRose_Dexter_3_1":
            dialog.text = "E tu pensavi perché sono incollata a questa sedia con il sedere, eh-eh? Sai, il modo di vedere il mondo può davvero cambiare quando capisci che la salute non la compri nemmeno con tutte le ricchezze di quest'Isola.";
            link.l1 = "Divertente – è proprio di questo che sono venuto a parlare.";
            link.l1.go = "WildRose_Dexter_4";
			AddCharacterExpToSkill(pchar, "Defence", 100);
        break;
		
		case "WildRose_Dexter_3_2":
            dialog.text = "E tu pensavi perché sono incollato con il sedere a questa sedia, eh-eh? Sai, la visione del mondo può davvero cambiare quando capisci che la salute non la compri nemmeno con tutte le ricchezze di quest'Isola.";
            link.l1 = "Divertente – è proprio di questo che sono venuto a parlare.";
            link.l1.go = "WildRose_Dexter_4";
			AddComplexSelfExpToScill(100, 100, 100, 100);
        break;

        case "WildRose_Dexter_4":
            dialog.text = "Della mia salute?";
            link.l1 = "No, delle ricchezze dell'Isola.   E per essere più precisa, dei loro inventari.   Anzi, per essere del tutto precisa, dei registri che contengono questi inventari.";
            link.l1.go = "WildRose_Dexter_5";
        break;

        case "WildRose_Dexter_5":
            dialog.text = "Ehm-ehm... "+pchar.name+", non capisco bene di cosa parli, giusto?";
            link.l1 = "Non molto tempo fa hai preso ai narvali i registri delle navi arenate sull'Isola...";
            link.l1.go = "WildRose_Dexter_6";
        break;

        case "WildRose_Dexter_6":
            dialog.text = "Quindi, quel babbeo di Greenspy ha deciso di mandarti a prenderli? Che faccia tosta.";
            link.l1 = "Per niente, "+npchar.name+", Donald non c'entra niente. Sono stato io ad andare da lui con questa domanda, e lui mi ha mandato da te. Ma la tua reazione, devo ammettere, mi ha divertito. Vuoi dirmi perché ti sono serviti i registri dei narvali?";
            link.l1.go = "WildRose_Dexter_7";
        break;

        case "WildRose_Dexter_7":
            dialog.text = "Perché non me lo racconti? A me, come avrai già capito, delle navi in sé non importa nulla. E dei tesori stipati nelle loro stive, a dire il vero, nemmeno. Qui ce n'è abbastanza per tutti, basta non essere troppo avidi – è quello che penso. Quello che mi interessa davvero sono le armi: moschetti, sciabole... e alla fine anche i cannoni. Giusto, quei furboni a volte si portano via pure quelli. Quei testoni di negri non ci arrivano, ma invece i narvali...";
            link.l1 = "E hai deciso di vedere quanto sono pronti gli abitanti di Greenspy a una nuova ondata di scontri, giusto?";
            link.l1.go = "WildRose_Dexter_8";
        break;

        case "WildRose_Dexter_8":
            dialog.text = "E suggerire che io e i miei ragazzi stiamo sempre all'erta. Il messaggio è piuttosto chiaro, ma considerando tutto quel circo che Donald ha messo su con queste esercitazioni, posso benissimo immaginare che abbia pensato che io sia interessata ai suoi soldi.";
            link.l1 = "Già, vedo che la situazione sta prendendo una piega un po' diversa da quella che ti aspettavi, giusto? E i rivados? Il Nero Eddie non ti dà fastidio?";
            link.l1.go = "WildRose_Dexter_9";
        break;

        case "WildRose_Dexter_9":
            dialog.text = "Rivados, Eddie... Quei neri schifosi – non per niente lo Squalo li odiava così tanto, giusto?";
            link.l1 = "Quindi, ti piace.";
            link.l1.go = "WildRose_Dexter_10";
        break;

        case "WildRose_Dexter_10":
            dialog.text = "Proprio questo è il punto, no, che io sia dannato! Quei negri si sono acquietati, rintanati sulle loro navi...";
            link.l1 = "E allora che diavolo c'è che non ti va bene, "+npchar.name+"?";
            link.l1.go = "WildRose_Dexter_11";
        break;

        case "WildRose_Dexter_11":
            dialog.text = "Come posso spiegartelo, "+pchar.name+"... Vedi, è come il vento in mare aperto. A volte è debole, a volte è forte, e a volte si scatena una vera tempesta. Ma in ogni caso il vento spinge la nave avanti, e un buon capitano sa come domarlo.";
            link.l1 = "Una brezza leggera è sempre meglio di una tempesta furiosa.";
            link.l1.go = "WildRose_Dexter_12";
        break;

        case "WildRose_Dexter_12":
            dialog.text = "Sì.   Ma a volte succede che non ci sia proprio vento.   Bonaccia – e con quella, nessun capitano può fare un accidente, giusto?   Te ne stai seduta a poppa, guardi l'acqua piatta e ti chiedi che diamine succederà dopo.   Con Eddie e il suo compare Chimiset è lo stesso – stanno tramando qualcosa, lo sento nelle ossa, e non porterà a nulla di buono, te lo giuro sul tuono!";
            link.l1 = "Forse dovresti alzare il sedere dalla sedia e andare a parlare con Edward faccia a faccia. O meglio ancora, riunirvi tutti e tre, anche con Donald, e discutere tutto apertamente. È molto meglio che far sprofondare di nuovo l'Isola nel sangue. Ma va bene... Torniamo a quello per cui sono venuto.";
            link.l1.go = "WildRose_Dexter_13";
        break;

        case "WildRose_Dexter_13":
            dialog.text = "Quindi ti interessano i tesori dei narvali, giusto? Cosa speri di trovare lì?";
            link.l1 = "Mi interessano gli elenchi delle navi naufragate qui. In particolare, per l'anno 1638. Vedi, stiamo cercando informazioni sui genitori di Mary. Per quanto riguarda la madre, più o meno tutto è chiaro, ma per il padre non si può dire lo stesso. Le informazioni su di lui sono molto vaghe, non conosciamo nemmeno il suo nome, e se c'è qualcosa a cui possiamo aggrapparci, è solo il nome della nave che si è schiantata sull'anello esterno nel giugno del 1638...";
            link.l1.go = "WildRose_Dexter_14";
        break;

        case "WildRose_Dexter_14":
            dialog.text = "La causa è nobile – anch'io, un tempo, mi sono tormentato pensando a chi fosse davvero mio padre. Solo che non posso aiutarvi.";
            link.l1 = "E perché mai, se non è un segreto?";
            link.l1.go = "WildRose_Dexter_15";
        break;

        case "WildRose_Dexter_15":
            dialog.text = "Non ho segreti per te, "+pchar.name+". Non si tratta affatto di me, ma di Donald – mi ha consegnato solo i documenti a partire dal 1651. Gli ho chiesto delle registrazioni più vecchie, almeno del decennio precedente – e mi ha risposto che non ci sono altri documenti. Questo è tutto ciò che ha ereditato da Alan Milrow in questo ambito – così ha detto.";
            link.l1 = "Non credo che avesse motivi per mentire.";
            link.l1.go = "WildRose_Dexter_16";
        break;

        case "WildRose_Dexter_16":
            dialog.text = "Penso lo stesso, amico. Considerando che mi ha dato i nuovi registri senza fare domande. Anzi, mi è sembrato persino sollevato di liberarsi di quella roba... Chissà, forse Milroe si è semplicemente sbarazzato dei documenti degli ultimi decenni... Li ha bruciati, o magari...";
            link.l1 = "No, non può essere.";
            link.l1.go = "WildRose_Dexter_16_Add";
        break;

        case "WildRose_Dexter_16_Add":
            StartInstantDialog("Mary", "WildRose_Dexter_17", "Quest\CompanionQuests\WildRose.c");
        break;

        case "WildRose_Dexter_17":
            dialog.text = "No, non può essere. Alan non avrebbe mai fatto una cosa del genere.";
            link.l1 = "Perché ne sei così sicura, "+npchar.name+"?";
            link.l1.go = "WildRose_Dexter_17_1";
            link.l2 = "Mi sembrava più uno da coltello e ascia che da tutta questa burocrazia. Sono sorpresa che sapesse persino leggere.";
            link.l2.go = "WildRose_Dexter_17_2";
        break;

        case "WildRose_Dexter_17_1":
			dialog.text = "Trattava con grande rispetto ogni annotazione riguardante l'Isola. Le considerava parte della sua storia. E la storia, non solo di questo luogo, era una vera passione per Alan, sì. Studiava tutti i documenti storici disponibili, libri... A volte mi sembrava che sarebbe stato un accademico molto migliore di un tagliagole — gliel'ho anche detto una volta.";
			link.l1 = "...";
			link.l1.go = "WildRose_Dexter_18";
		break;

		case "WildRose_Dexter_17_2":
			dialog.text = "Trattava con grande rispetto ogni annotazione riguardante l'Isola. Le considerava parte della sua storia. E la storia, non solo di questo luogo, era una vera passione per Alan, sì. Studiava tutti i documenti storici disponibili, libri... A volte mi sembrava che sarebbe stato un accademico molto migliore di un tagliagole — gliel'ho anche detto una volta.";
			link.l1 = "Forse avrebbe davvero dovuto preferire gli occhiali, la carta e la penna alla spada e alla pistola – magari starebbe ancora calpestando le assi marce di queste navi. Ma se Milrow era un tale estimatore dei documenti d'archivio, dove ha messo allora quegli appunti? Mettiamo che uno dei fogli l'abbia potuto macchiare d'inchiostro per sbaglio – ma erano decine, se non centinaia, giusto?";
			link.l1.go = "WildRose_Dexter_18";
		break;

        case "WildRose_Dexter_18":
            dialog.text = "So solo che lui custodiva quei documenti più gelosamente della sua stessa vita. Forse qualcuno li ha rubati, oppure li ha dati via lui stesso a qualcuno...";
            link.l1 = "Hai rubato?   A chi mai potrebbero servire informazioni su navi già sventrate dalla coperta alla chiglia?   Consegnarle – questo è molto più probabile, ma a chi e perché?";
            link.l1.go = "WildRose_Dexter_19_Add";
        break;

        case "WildRose_Dexter_19_Add":
            StartInstantDialogNoType("Dexter", "WildRose_Dexter_20", "Quest\CompanionQuests\WildRose.c");
        break;

        case "WildRose_Dexter_20":
            dialog.text = "A qualche altro appassionato di storia, ah-ah-ah! Sono d'accordo con Charles - non ho la minima idea di chi altro potesse aver bisogno di questi vecchi scarabocchi.";
            link.l1 = "A qualcuno, però, sono serviti. Dovrò rifletterci un po', giusto? Va bene, "+npchar.name+", non ti distraiamo oltre. Ci rivedremo.";
            link.l1.go = "Exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_19");
        break;
		
		case "WildRose_Betancur_1":
			dialog.text = ""+pchar.name+", felice di rivederti. Come vanno le cose tra te e Mary?";
			link.l1 = "E siamo felici di vederti, "+npchar.name+". Ma come andranno le cose tra noi – dipenderà da te.";
			link.l1.go = "WildRose_Betancur_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Betancur_2":
			dialog.text = "Un inizio di conversazione intrigante, devo ammetterlo. E anche un po' inquietante, considerando l'espressione sui vostri volti.";
			link.l1 = "Non spaventarti, "+npchar.name+",   non è mica colpa tua. Siamo solo un po' stanchi di correre su questi relitti scricchiolanti, giusto? E poi oggi fa anche un caldo soffocante, non ti pare?";
			link.l1.go = "WildRose_Betancur_3_1";
			link.l2 = "Questo caldo non ci dà certo più energie. Inoltre, abbiamo dovuto correre per l'Isola mentre ti cercavamo – ci serve il tuo aiuto.";
			link.l2.go = "WildRose_Betancur_3_2";
		break;

		case "WildRose_Betancur_3_1":
			dialog.text = "Ehm, giusto, una brezza leggera adesso ci starebbe proprio bene. Allora, cosa posso fare per voi?";
			link.l1 = "Vedi, io e Mary abbiamo avviato un'indagine per fare luce sugli eventi di vent'anni fa.";
			link.l1.go = "WildRose_Betancur_4";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

		case "WildRose_Betancur_3_2":
			dialog.text = "Ehm, giusto, una brezza leggera adesso sarebbe proprio quello che ci vuole. Allora, cosa posso fare per voi?";
			link.l1 = "Vedi, io e Mary abbiamo avviato un'indagine per fare luce sugli eventi di vent'anni fa.";
			link.l1.go = "WildRose_Betancur_4";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Betancur_4":
			dialog.text = "Sembra interessante. E di cosa si tratta?";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_4_add";
		break;
		
		case "WildRose_Betancur_4_add":
			StartInstantDialog("Mary", "WildRose_Betancur_5", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Betancur_5":
			dialog.text = "I miei genitori, Antonio. Io e Charles stiamo cercando di scoprire chi fossero. E cosa sia successo loro. Mia madre è morta di parto, questo lo abbiamo già scoperto. Ma con mio padre non è così semplice...";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_5_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_5_add":
			StartInstantDialog("LSC_Betancur", "WildRose_Betancur_6", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Betancur_6":
			dialog.text = "In che anno sei nata, ricordami un po'...";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_6_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_6_add":
			StartInstantDialog("Mary", "WildRose_Betancur_7", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Betancur_7":
			dialog.text = "Nel 1638. A giugno.";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_7_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_7_add":
			StartInstantDialog("LSC_Betancur", "WildRose_Betancur_8", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Betancur_8":
			dialog.text = "Avevo solo dodici anni allora, Mary. Non ricordo molto bene quei giorni. Certi ricordi, ovviamente, riaffiorano ogni tanto, ma metterli insieme in un quadro unico, sinceramente, sarebbe un po' difficile. Mi dispiace, ma dubito di poterti aiutare...";
			link.l1 = "Non è proprio questo che ci serve da te, Antonio. Però, se ti ricordi qualcosa di quel giorno in cui è nata Mary, te ne saremo davvero grati.";
			link.l1.go = "WildRose_Betancur_9";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;
		
		case "WildRose_Betancur_9":
			dialog.text = "Allora, come posso aiutarvi, "+pchar.name+"?";
			link.l1 = "Mi hai detto che ti appassiona la storia. Quella del mondo in generale, e quella dell'Isola in particolare.";
			link.l1.go = "WildRose_Betancur_10";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), pchar);
		break;

		case "WildRose_Betancur_10":
			dialog.text = "È vero. Ho letto ogni tipo di libro, ho studiato tutti i manoscritti che sono riuscito a trovare...";
			link.l1 = "Proprio dei manoscritti si parlerà. Oltre a te, sull'Isola c'era solo una persona appassionata di storia quanto te...";
			link.l1.go = "WildRose_Betancur_12";
		break;

		case "WildRose_Betancur_12":
			dialog.text = "Alan Milrow. Sì, ne abbiamo parlato quando non era impegnato a elaborare piani per distruggere i Rivadòs, e poi anche i pirati. Era un tipo intelligente, con talenti davvero fuori dal comune.";
			link.l1 = "Non ho dubbi: quel ragazzo era davvero in gamba. Aveva qualcosa che potrebbe esserci utile. Allo stesso tempo, non ha alcun valore pratico per nessuno sull'Isola della Giustizia, tranne che per voi due. Registri delle navi naufragate presso l'Isola, che contengono anche la descrizione dei carichi e dei tesori recuperati, e forse i nomi dei passeggeri...";
			link.l1.go = "WildRose_Betancur_13";
		break;

		case "WildRose_Betancur_13":
			dialog.text = "Proprio così.";
			link.l1 = "Quindi li hai visti?";
			link.l1.go = "WildRose_Betancur_14";
		break;

		case "WildRose_Betancur_14":
			dialog.text = "Non solo li ho visti — ho anche trascritto le informazioni contenute nei miei appunti. Durante una delle nostre conversazioni, ha accennato all'esistenza di quei diari e io gli ho chiesto di poterli esaminare — sto cercando di mettere insieme una sorta di Cronache dell'Isola della Giustizia, e quelle annotazioni mi sono tornate molto utili. Alan era entusiasta della mia idea — scrivere la storia di questo luogo. È vero, non mi diede tutti gli appunti, tenne per sé quelli degli anni 1650, ma per allora il resto mi bastava.";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_14_add";
		break;
		
		case "WildRose_Betancur_14_add":
			StartInstantDialog("Mary", "WildRose_Betancur_15", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Betancur_15":
			dialog.text = "Ci sono davvero dei registri per il 1638? Ti prego, dimmi che ci sono, giusto!";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_15_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_15_add":
			StartInstantDialog("LSC_Betancur", "WildRose_Betancur_16", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Betancur_16":
			dialog.text = "Ho una pila intera di questi registri - fin dal 1620. Proprio allora, secondo Alan, hanno iniziato a scrivere queste annotazioni. E sì, c'è anche il 1638, Mary.";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_16_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_16_add":
			StartInstantDialog("Mary", "WildRose_Betancur_17", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Betancur_17":
			dialog.text = "Ci permetterai di darci un'occhiata?";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_17_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;
		
		case "WildRose_Betancur_17_add":
			if (PChar.location == "PlutoStoreSmall") StartInstantDialog("LSC_Betancur", "WildRose_Betancur_18", "Quest\CompanionQuests\WildRose.c");
			else StartInstantDialog("LSC_Betancur", "WildRose_Betancur_19", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Betancur_18":
			dialog.text = "Non sembra che io abbia molta scelta, ah-ah-ah! Un attimo. Sono tutti qui, nel cassetto in basso di quell'armadio.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_19_1");
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_19":
			dialog.text = "Prego. Mettetevi comodi, esplorate pure...";
			link.l1 = "È proprio quello che faremo.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_20");
			AddQuestRecordInfo("WildRose_Records", "1");
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), pchar);
		break;
		
		case "WildRose_Mary_101":
			dialog.text = "Ecco, "+pchar.name+", guarda, giusto! Joshua e Teresa Casper! Non ci posso credere – ce l'abbiamo fatta, ce l'abbiamo fatta, giusto! E il nome della nave – 'Wrangler'! Ora possiamo scoprire tutto su mio padre – chi era, come è finito qui...";
			link.l1 = "Temo, "+npchar.name+",   vai troppo di fretta...   Potrebbe non essere così semplice come sembra.   Una nave di Sua Maestà...   Dovremo pensare a chi potrebbe aiutarci a ottenere informazioni dagli archivi della Marina Reale...";
			link.l1.go = "WildRose_Mary_102";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Mary_102":
			dialog.text = "Pensiamoci! Pensiamoci e otterremo, "+pchar.name+"! Il peggio è già passato, giusto!";
			link.l1 = "Forse avrebbe anche senso parlare con i signori Young e Friddick. Tuttavia, non ricordo persone con questi nomi sull'Isola.";
			link.l1.go = "WildRose_Betancur_20_add";
		break;
		
		case "WildRose_Betancur_20_add":
			StartInstantDialog("LSC_Betancur", "WildRose_Betancur_21", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Betancur_21":
			dialog.text = "Perché qui non ci sono, "+pchar.name+".   Questi due sono morti la notte seguente, dopo essere stati salvati insieme ai Casper.";
			link.l1 = "Curioso.   Una donna incinta è sopravvissuta ancora una settimana, mentre due marinai della Royal Navy sono morti all'improvviso...";
			link.l1.go = "WildRose_Betancur_22";
		break;

		case "WildRose_Betancur_22":
			dialog.text = "Erano già pessimi, se non ricordo male. Ora mi sono ricordato, "+pchar.name+" - Mi trovavo proprio vicino alla 'Ceres Smithy' quando li hanno fatti salire a bordo... Giusto? Sì, ero sulla 'Esmeralda' - insieme ad Aurélie Bertin, mi pare. E c'era anche Chimiset - lo sciamano di quei dannati neri, che per qualche motivo era venuto al negozio. All'inizio mi era sembrato che quei due marinai fossero già morti - ma sono morti solo il giorno dopo...";
			link.l1 = "E va bene, non ci possiamo fare niente. Ma abbiamo già scoperto parecchio, giusto? Grazie per l'aiuto, Antonio.";
			link.l1.go = "WildRose_Betancur_23";
		break;

		case "WildRose_Betancur_23":
			dialog.text = "Io non c'entro, "+pchar.name+". È tutto merito di Alan, giusto? Solo lui tra questi corazzieri avrebbe potuto capire davvero il valore di questi documenti. È grazie a carte come queste che si ricostruisce la storia!";
			link.l1 = "Spero che un giorno io e Mary leggeremo le tue Cronache, amico. Tieni il diario, non perderlo. Beh, è ora che andiamo. Forse ci rivedremo ancora, amico.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_21");
		break;
		
		case "WildRose_Betancur_21":
			dialog.text = "Perché qui non ce ne sono, "+pchar.name+".   Questi due sono morti la notte successiva, dopo essere stati salvati insieme ai Casper.";
			link.l1 = "Curioso. Una donna incinta è sopravvissuta ancora una settimana, mentre due marinai della Flotta Reale sono morti all'improvviso...";
			link.l1.go = "WildRose_Betancur_22";
		break;
		
		case "WildRose_Chimiset_21":
			dialog.text = "Felice di rivederti, amico mio. Cosa ti porta da me?";
			link.l1 = "Con una richiesta, "+npchar.name+"...   Anzi,   con una domanda. ";
			link.l1.go = "WildRose_Chimiset_22";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Chimiset_22":
			dialog.text = "Fai la tua domanda. Oppure dimmi cosa desideri. Farò tutto il possibile per aiutarti.";
			link.l1 = "Va bene.   Da quanto tempo vivi sull'Isola?";
			link.l1.go = "WildRose_Chimiset_23";
		break;

		case "WildRose_Chimiset_23":
			dialog.text = "Decine e decine d'anni, amico mio. Sono arrivato qui da bambino, ma già sveglio — a bordo di una nave negriera. La mia storia non è molto diversa da tante altre che hai sentito qui. Tempesta, naufragio... Il galeone inglese in cui ero rinchiuso nella stiva non arrivò nemmeno all'anello esterno: si spezzò in due dopo aver urtato uno degli scogli su cui l'aveva scagliato un'onda.";
			link.l1 = "Come hai fatto a sopravvivere? Gli scogli sono piuttosto lontani dall'anello esterno, e arrivare fin lì tra le onde della tempesta non è certo una passeggiata, diciamolo...";
			link.l1.go = "WildRose_Chimiset_24";
		break;

		case "WildRose_Chimiset_24":
			dialog.text = " Gli dei erano dalla mia parte quella notte. Sono riuscita a liberarmi dalle catene e poi ad aggrapparmi a un relitto che una volta era una scialuppa. Con me c'era un compagno di tribù, Asana – insieme abbiamo lottato contro le onde finché non abbiamo perso conoscenza per la stanchezza. ";
			link.l1 = "Siete stati portati contro una delle navi?";
			link.l1.go = "WildRose_Chimiset_25";
		break;

		case "WildRose_Chimiset_25":
			dialog.text = "Sì, ci siamo infilati in una buca nella stiva... Lì ho perso di nuovo conoscenza, ero talmente sfinito. L'ho ripresa solo quando Asana ha iniziato a urlare: lo stava facendo a pezzi un granchio gigante, salito sulla stessa nave dove eravamo finiti noi. E io guardavo tutto questo e capivo che sarei stato il prossimo – paralizzato dalla paura e dall'impotenza, non riuscivo a muovere un muscolo.";
			link.l1 = "Avresti potuto provare ad aiutare un amico. Però, in tal caso, ora non staremmo parlando, giusto? Come hai fatto a salvarsi?";
			link.l1.go = "WildRose_Chimiset_26_1";
			link.l2 = "Ti è andata bene che non abbia cominciato da te, "+npchar.name+".   Come hai fatto a salvarsi - sei saltato di nuovo in acqua e hai nuotato via?";
			link.l2.go = "WildRose_Chimiset_26_2";
		break;

		case "WildRose_Chimiset_26_1":
			dialog.text = "Le grida di Asana furono sentite da alcuni rivados, usciti a caccia del contenuto delle stive delle navi dopo l'ennesimo uragano. Hanno circondato quella bestiaccia e l'hanno uccisa. Per Asana non c'era ormai più nulla da fare, ma a me è andata molto meglio. Così sono finito qui. Ma ora rispondi tu a me, amico mio: perché volevi sapere tutto questo?";
			link.l1 = "In realtà, "+npchar.name+", volevo sapere non come sei finito qui, ma quando è successo.";
			link.l1.go = "WildRose_Chimiset_27";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;

		case "WildRose_Chimiset_26_2":
			dialog.text = "I lamenti di Asana furono sentiti da alcuni rivados, usciti a caccia del contenuto delle stive delle navi dopo l'ennesimo uragano. Hanno circondato quella bestia e l'hanno uccisa. Per Asana non c'era già più nulla da fare, ma a me è andata molto meglio. Così sono finito qui. Ma ora rispondi tu a me, amico mio: perché volevi sapere tutto questo?";
			link.l1 = "In realtà, "+npchar.name+", non volevo sapere come sei finito qui, ma quando è successo.";
			link.l1.go = "WildRose_Chimiset_27";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

		case "WildRose_Chimiset_27":
			dialog.text = "Hmm, secondo il vostro calendario era il 1623, fine estate – non saprei essere più precisa di così...";
			link.l1 = "Non è nemmeno necessario. Quindi, nel 1638 erano già quindici anni che eri sull'Isola.";
			link.l1.go = "WildRose_Chimiset_28";
		break;

		case "WildRose_Chimiset_28":
			dialog.text = "Così pare, amico mio.";
			link.l1 = "A giugno di quell'anno, un uragano spinse contro l'anello esterno la brigantina 'Wrangler', nave della flotta di Sua Maestà Carlo I, re d'Inghilterra. Di tutto l'equipaggio si salvarono solo in quattro – tra cui i genitori di Mary: Joshua e Teresa Casper.";
			link.l1.go = "WildRose_Chimiset_29";
		break;

		case "WildRose_Chimiset_29":
			dialog.text = "Sì, me lo ricordo, amico mio. Vagamente, come in una nebbia, ma lo ricordo...";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_29_add";
		break;
		
		case "WildRose_Chimiset_29_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_30", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_30":
			dialog.text = "Ti ricordi davvero? Allora racconta!";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_30_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;
		
		case "WildRose_Chimiset_30_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_31", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_31":
			dialog.text = "Posso dire poco. Quattro persone: un ufficiale, sua moglie e due marinai. La donna era incinta, e chi li ha salvati pensava che non sarebbe sopravvissuta fino al mattino – ma si è rivelata forte come una leonessa, mentre quei due marinai hanno lasciato questo mondo in meno di un giorno... Li ho visti: erano deboli, ma avevano ancora abbastanza forza vitale...";
			link.l1 = "Insinui che li abbiano uccisi?";
			link.l1.go = "WildRose_Chimiset_32";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;
		
		case "WildRose_Chimiset_32":
			dialog.text = "Se anche fosse così, non ci sono stati testimoni, né ferite sui loro corpi, amico mio...";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_32_add";
		break;
		
		case "WildRose_Chimiset_32_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_33", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_33":
			dialog.text = "Hai detto 'ufficiale', giusto... Mio padre era davvero un ufficiale?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_33_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;
		
		case "WildRose_Chimiset_33_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_34", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_34":
			dialog.text = "Indossava una divisa da ufficiale - è forse l'unica cosa che ricordo, quando cerco di ricordare com'era.";
			link.l1 = "Se era un ufficiale, non poteva indossare altro – dubito che il suo guardaroba fosse molto vario... Magari ti ricordi qualche altro dettaglio, "+npchar.name+"? Segni particolari... Diciamo, una cicatrice sul viso o qualche altra ferita...";
			link.l1.go = "WildRose_Chimiset_35";
		break;
		
		case "WildRose_Chimiset_35":
			dialog.text = "Non ricordo nulla di particolare, amico mio. Il suo volto è quasi svanito dalla mia memoria – sono passati vent'anni... Ma quello sguardo – quello lo ricordo benissimo. Ho parlato con quest'uomo solo una volta, ma lo sguardo dei suoi occhi grigi – proprio come quelli di Mary – non lo dimenticherò mai. In quegli occhi si mescolavano disperazione, paura, come in un'antilope braccata, e allo stesso tempo rabbia e determinazione, degne di un leone...";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_35_add";
		break;
		
		case "WildRose_Chimiset_35_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_36", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_36":
			dialog.text = "Hai parlato con lui, giusto?   Di cosa?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_36_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_36_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_37", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_37":
			dialog.text = "È successo poche ore prima della tua nascita. Si presentò qui, sul 'Protector', e pretese di incontrarmi. Il capo dei rivados, Mogedi, rimase sbalordito dalla sua sfrontatezza — ma quell'uomo, all'improvviso, mi incuriosì. Quando fu portato al mio cospetto, cadde in ginocchio e cominciò a implorarmi di salvare sua moglie... Qualcuno, nel poco tempo che erano stati qui, aveva già trovato il modo di raccontargli di me. Acconsentii, anche se Mogedi era contrario...";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_37_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_37_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_38", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_38":
			dialog.text = "Quindi, ti devo la vita, giusto?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_38_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_38_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_39", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_39":
			dialog.text = "Non ha senso mentire – siamo riusciti ad arrivare da tua madre, ma troppo tardi: i narvali si rifiutavano di farmi salire sulla 'Ceres Smithy'. Tuo padre è riuscito a... convincerli, ma la povera Teresa l'ho vista solo nel suo ultimo respiro. È riuscita a darti alla luce e, se fossi arrivato prima, forse le avrei salvato la vita, ma...";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_39_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_39_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_40", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_40":
			dialog.text = "Mamma è morta, giusto.";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_40_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_40_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_41", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_41":
			dialog.text = "Purtroppo. Ti ha guardato e ha esalato l'ultimo respiro, ma prima di questo, come se avesse raccolto tutte le sue forze, ha chiamato qualcuno di nome Rupert. Ha gridato il suo nome a squarciagola, come se chiedesse aiuto – e poi è morta.";
			link.l1 = "Ruperta? Non Joshua?";
			link.l1.go = "WildRose_Chimiset_42";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;
		
		case "WildRose_Chimiset_42":
			dialog.text = "Mentre ve lo raccontavo, amico mio, era come se rivivessi quel momento. Non lo dimenticherò mai – né il suo grido prima di morire, né il suo volto stravolto dal dolore. E sì, l'ultima parola che le sfuggì dalle labbra fu proprio 'Rupert'.";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_42_add";
		break;
		
		case "WildRose_Chimiset_42_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_43", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_43":
			dialog.text = "Era bella, mia madre? Puoi descrivermi com'era, Chimiset?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_43_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_43_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_44", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_44":
			dialog.text = "Non ha senso, Mary. Ti basta guardarti allo specchio: siete simili come due gocce d'acqua. Solo quello sguardo penetrante l'hai ereditato da tuo padre.";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_44_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_44_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_45", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_45":
			dialog.text = "E lui, che ne è stato di lui? Siamo riusciti a scoprire che pochi giorni dopo la mia nascita è sparito nel nulla, giusto? Ma non l'hanno mica ucciso, vero?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_45_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_45_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_46", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_46":
			dialog.text = "Non appena gli dissero che Teresa era in fin di vita, Joshua andò su tutte le furie — giuro che nemmeno i leoni nella savana attaccano la preda con la furia con cui tuo padre si scagliò contro quei narvali che mi sbarravano l'accesso al fluyt... Ci vollero sei uomini per immobilizzarlo — dopo che aveva gettato in mare due guerrieri del clan in pieno equipaggiamento.";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_46_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_46_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_47", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_47":
			dialog.text = "E cosa gli hanno fatto - dimmi, dai!";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_47_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_47_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_48", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_48":
			dialog.text = "È stato rinchiuso in una delle celle sul 'Tartarus'. Nessuno ha osato giudicarlo - volevano che la storia si placasse prima... Quasi tutti provavano compassione per lui, ma pochi desideravano vivere fianco a fianco con una persona simile. Joshua è scomparso dopo alcuni giorni - proprio allora diversi barconi di contrabbandieri hanno lasciato l'Isola. Nessuno lo ha visto sulle barche - ed è così che sono nate le voci sulla sua morte.";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_48_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_48_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_49", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_49":
			dialog.text = "Quindi credi che sia vivo, giusto?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_49_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_49_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_50", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_50":
			dialog.text = "Dirò solo quello che sicuramente vi diranno anche altri: nessuno ha mai trovato il suo corpo. Forse si è davvero nascosto sul fondo di una delle barche, oppure gli hanno tagliato la gola in quella cella e l'hanno dato in pasto ai granchi...";
			link.l1 = "Il fatto che sia sparito proprio quando sono salpati quei mercanti fa piuttosto pensare alla prima ipotesi – coincidenze così non succedono. E forse, ha accennato a qualcuno dei suoi piani? Se è fuggito, allora è fuggito lasciando qui una figlia appena nata, il che, in un certo senso, è anche sensato – una neonata forse non avrebbe resistito al viaggio fino alle coste di Cuba su una barchetta fragile... Ma sicuramente aveva intenzione di tornare a prenderla.";
			link.l1.go = "WildRose_Chimiset_51";
		break;
		
		case "WildRose_Chimiset_51":
			dialog.text = "Non ne ho idea, amico mio. Se Joshua Casper ha parlato con qualcuno in quei giorni, sarà stato solo con i suoi carcerieri – ma tutti loro hanno lasciato questo mondo peccatore da molto tempo. Ah già, un giorno da lui venne padre Domingo – era il prete dei bianchi prima di fratello Julian...";
			link.l1 = "Ha deciso di confessarsi? Forse aveva paura di morire durante la fuga.";
			link.l1.go = "WildRose_Chimiset_52";
		break;

		case "WildRose_Chimiset_52":
			dialog.text = "Non sono in grado di far luce su ciò che non so, amico mio. E anche Domingo non potrà più raccontarvi nulla – è annegato ormai quindici anni fa. O qualcuno gli ha dato una botta in testa, o semplicemente si era ubriacato – quello gli piaceva, sai...";
			link.l1 = "Ma forse Domingo teneva un diario... o magari ha raccontato quella conversazione con Joshua a suo fratello Julian, giusto?";
			link.l1.go = "WildRose_Chimiset_52_add";
		break;
		
		case "WildRose_Chimiset_52_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_53", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_53":
			dialog.text = "Devo parlargli, "+pchar.name+", giusto. E il prima possibile. Non voglio nemmeno pensare di tornare sulla nave finché non avremo risolto questa faccenda.";
			link.l1 = "Se c'è ancora qualcosa da chiarire. Julian potrebbe anche non saperlo – ma lo scopriremo di sicuro. Grazie, Chimiset.";
			link.l1.go = "WildRose_Chimiset_53_add";
		break;
		
		case "WildRose_Chimiset_53_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_54", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_54":
			dialog.text = "Sono sempre al tuo servizio, amico mio. Ma permettimi di darvi un consiglio, a entrambi.";
			link.l1 = "E quale sarebbe?";
			link.l1.go = "WildRose_Chimiset_55";
		break;
		
		case "WildRose_Chimiset_55":
			dialog.text = "Quando siete a caccia, non addentratevi troppo nella boscaglia – potreste non riuscire più a uscirne.";
			link.l1 = "Ce ne ricorderemo, sciamano. E ora - addio.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_22");
		break;
		
		case "WildRose_Julian_1":
			dialog.text = "Vi do il benvenuto sotto la protezione della casa di Dio, figli miei. Avete deciso di confessarvi o volete semplicemente pregare?";
			link.l1 = "Ciao, fratello Julian. Temo che elencare tutti i nostri peccati richiederebbe troppo tempo – tempo che, ahimè, non abbiamo. Ma stai tranquillo – da buoni cattolici, frequentiamo la chiesa in ogni porto.";
			link.l1.go = "WildRose_Julian_2_1";
			link.l2 = "Salve, fratello Julian. Con la preghiera al nostro Signore, noi, buoni cattolici, iniziamo la giornata e con essa la concludiamo, giusto?";
			link.l2.go = "WildRose_Julian_2_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Julian_2_1":
			dialog.text = "Buoni cattolici che vivono sotto lo stesso tetto senza essere sposati... È quasi una bestemmia, figliolo. E questo, ti ricordo, è un peccato mortale!";
			link.l1 = "Ma non è forse scritto nelle Scritture che l'amore copre tutti i peccati?";
			link.l1.go = "WildRose_Julian_3";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

		case "WildRose_Julian_2_2":
			dialog.text = "Buoni cattolici che vivono sotto lo stesso tetto senza essere sposati... È quasi una bestemmia, figliolo. E questo, ti ricordo, è un peccato mortale!";
			link.l1 = "E non è forse scritto nelle Scritture che l'amore copre tutti i peccati?";
			link.l1.go = "WildRose_Julian_3";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Julian_3":
			dialog.text = "L'amore consiste nel seguire i Suoi comandamenti – devo forse ricordarteli, figlio mio?";
			link.l1 = "Magari un'altra volta. Siamo qui per un altro motivo.";
			link.l1.go = "WildRose_Julian_4";
		break;

		case "WildRose_Julian_4":
			dialog.text = "Per le anime smarrite non è mai troppo tardi per tornare sulla retta via... Ma vi ascolto, figli miei.";
			link.l1 = "Ci siamo davvero un po' persi, fratello Julian. Nei meandri del passato. E speriamo che tu possa aiutarci a ritrovare la strada verso la luce.";
			link.l1.go = "WildRose_Julian_5";
		break;

		case "WildRose_Julian_5":
			dialog.text = "Molto spiritoso, figlio mio. Dovresti ricordare che non è l'uomo a condurre verso la luce, ma il Signore – e, seguendo Lui, ricorda che imperscrutabili sono le Sue vie.";
			link.l1 = "Sarò breve, fratello Julian. Stiamo cercando di scoprire tutto il possibile sui genitori di Mary. Per quanto riguarda sua madre, Teresa, è tutto più o meno chiaro — arrivò sull’Isola insieme al marito e morì di parto una settimana dopo. Il padre, invece... scomparve pochi giorni dopo la nascita di Mary, fuggendo dal ‘Tartarus’. Secondo le voci, l’ultima persona con cui parlò qui fu padre Domingo — il vostro predecessore.";
			link.l1.go = "WildRose_Julian_6";
		break;

		case "WildRose_Julian_6":
			dialog.text = "Allora siete arrivati con più di un decennio e mezzo di ritardo, figli miei.";
			link.l1 = "Sì, sappiamo che il padre è morto già da un bel po'. E allora lei, fratello Julian, era ancora troppo giovane per trovarsi sull'Isola con il grado adeguato, giusto?";
			link.l1.go = "WildRose_Julian_7";
		break;

		case "WildRose_Julian_7":
			dialog.text = "Mi sono ritrovato qui qualche anno dopo la sua morte. Mi è costato molta fatica rimettere tutto in ordine qui, su questa nave, ma con l'aiuto di Dio ce l'ho fatta, figlio mio.";
			link.l1 = "Quando stavate sistemando qui, non avete trovato per caso qualche scritto di padre Domingo?";
			link.l1.go = "WildRose_Julian_8";
		break;

		case "WildRose_Julian_8":
			dialog.text = "Intendi qualcosa in particolare, figliolo?";
			link.l1 = "Ci interessano i diari o qualche libro dei conti... Le speranze di un miracolo sono poche, ma il padre potrebbe aver annotato il contenuto di quella conversazione in uno dei suoi appunti. Supponiamo che il padre di Mary abbia lasciato l'isola su una delle barche dei contrabbandieri – magari ha accennato al padre dove intendeva andare e quando sarebbe tornato a prendere la figlia?";
			link.l1.go = "WildRose_Julian_9";
		break;

		case "WildRose_Julian_9":
			dialog.text = "Diari o qualcosa di simile non ne ho trovati, questo è certo, ma invece ho trovato varie annotazioni... Per quanto riguarda la gestione degli affari ecclesiastici, era piuttosto scrupoloso – non ogni servo del Signore è dotato di tale pignoleria. Ma i suoi documenti contengono solo numeri secchi e nomi – e nient'altro.";
			link.l1 = "Per quanto siamo riusciti a scoprire, Joshua Casper – così si chiamava – in un impeto di rabbia, causato dalla morte della moglie, ha ucciso due membri del clan 'Narvalo', che si erano rifiutati di far avvicinare lo stregone rivados Chimiseta alla madre di Mary...";
			link.l1.go = "WildRose_Julian_10";
		break;

		case "WildRose_Julian_10":
			dialog.text = "Hanno agito come figli della vera Chiesa! Le segrete dell'Inquisizione piangono per questo servo del Diavolo!";
			link.l1 = "Dio, credo che si sarebbe inorridito – se solo sapesse quante persone sono state torturate in suo nome. Casper è stato più fortunato – l'hanno rinchiuso in una cella sul 'Tartarus', ma non sono arrivati a condannarlo.";
			link.l1.go = "WildRose_Julian_11_1";
			link.l2 = "Sì sì, senza dubbio. Hanno rinchiuso Casper in una delle celle del 'Tartarus', ma la sentenza non è mai stata emessa – non tutti hanno condannato il gesto di un marito che aveva perso la moglie.";
			link.l2.go = "WildRose_Julian_11_2";
		break;

		case "WildRose_Julian_11_1":
			dialog.text = "E poi? Quel bestemmiatore è scappato?";
			link.l1 = "Meno di una settimana dopo, Joshua scomparve. E la notte prima fu visitato da padre Domingo. Sorge una domanda: perché? Difficile credere che un protestante, quale Casper era sicuramente, si sarebbe confessato a un prete cattolico – che ne pensate?";
			link.l1.go = "WildRose_Julian_12";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Julian_11_2":
			dialog.text = "E poi? Quel dannato eretico è scappato, giusto?";
			link.l1 = "Meno di una settimana dopo, Joshua sparì. E la notte prima era stato visitato da padre Domingo. Sorge una domanda: perché? Dubito che un protestante, quale Casper sicuramente era, si sarebbe confessato da un prete cattolico – che ne pensate?";
			link.l1.go = "WildRose_Julian_12";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Julian_12":
			dialog.text = "Non è mai troppo tardi per rivolgersi alla vera fede, figlio mio. Ma il tuo ragionamento è giusto. Se non aveva bisogno di una confessione, forse stava discutendo con il padre della cerimonia funebre per la moglie – sempre che fosse cattolica. Oppure del battesimo della figlia, o meglio, del rifiuto del battesimo, visto che i protestanti non battezzano i neonati, credendo che una persona debba prendere la decisione di essere battezzata da sola e consapevolmente.";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_12_add";
		break;
		
		case "WildRose_Julian_12_add":
			StartInstantDialog("Mary", "WildRose_Julian_13", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Julian_13":
			dialog.text = "Ma sono stata battezzata, fratello Julian. Eric Udett me l'ha detto.";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_13_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Julian"));
			CharacterTurnByChr(CharacterFromID("Julian"), CharacterFromID("Mary"));
		break;

		case "WildRose_Julian_13_add":
			StartInstantDialog("Julian", "WildRose_Julian_14", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Julian_14":
			dialog.text = "Sono solo le mie supposizioni, figlia mia. La verità mi è sconosciuta. Il Signore ci apre gli occhi solo su ciò che è davvero importante e necessario.";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_14_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Julian"));
			CharacterTurnByChr(CharacterFromID("Julian"), CharacterFromID("Mary"));
		break;

		case "WildRose_Julian_14_add":
			StartInstantDialog("Mary", "WildRose_Julian_15", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Julian_15":
			dialog.text = "E per me è proprio così, giusto. Forse, tra le pagine degli appunti di padre Domingo, è rimasto qualcosa che non avete notato, fratello Julian? Dopotutto li avete solo sfogliati, vero?";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_15_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Julian"));
			CharacterTurnByChr(CharacterFromID("Julian"), CharacterFromID("Mary"));
		break;

		case "WildRose_Julian_15_add":
			StartInstantDialog("Julian", "WildRose_Julian_16", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Julian_16":
			dialog.text = "Non avevo nulla da cercare lì, figlia mia. Vedo che da tempo e con grande impegno vi dedicate a questa causa – il Signore vi guida su questa strada piena di spine. Se è destino che tu trovi ciò che cerchi, così vuole Lui, e non sta a me oppormi alla Sua volontà. Posso darti i registri di Domingo per l'anno della tua nascita, forse in essi troverai qualcosa di utile.";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_16_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Julian"));
			CharacterTurnByChr(CharacterFromID("Julian"), CharacterFromID("Mary"));
		break;

		case "WildRose_Julian_16_add":
			StartInstantDialog("Mary", "WildRose_Julian_17", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Julian_17":
			dialog.text = "Sarebbe davvero generoso da parte vostra, fratello Julian. Sono rimasti i registri dell'anno 1638?";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_17_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Julian"));
			CharacterTurnByChr(CharacterFromID("Julian"), CharacterFromID("Mary"));
		break;
		
		case "WildRose_Julian_17_add":
			StartInstantDialog("Julian", "WildRose_Julian_18", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Julian_18":
			dialog.text = "Ecco qua... (soffia via la polvere). Sembra che sia proprio questo. Il registro contabile dell'anno 1638 dalla Natività di Cristo.";
			link.l1 = "Permettimi, fratello Julian...";
			link.l1.go = "exit";
			AddQuestRecordInfo("WildRose_Records_2", "1");
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_23");
		break;
		
		case "WildRose_Mary_111":
			dialog.text = "Guarda, "+pchar.name+": 3 agosto. In questo giorno hanno battezzato me e Fabian. Ma sono nata il 22 giugno. Però di mio padre non c'è una parola, giusto?";
			link.l1 = "Tutto proprio come diceva fratello Julian: solo numeri secchi e nomi. Curioso, padre Domingo era così zelante che dava l'estrema unzione persino ai protestanti – dubito che van Ekkus, Young e Friddicks fossero cattolici.";
			link.l1.go = "WildRose_Mary_111_add";
			DelLandQuestMark(npchar);
		break;
		
		case "WildRose_Mary_111_add":
			StartInstantDialog("Julian", "WildRose_Mary_112", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Mary_112":
			dialog.text = "Avrebbero potuto benissimo convertirsi alla vera fede proprio sulla soglia dell'ingresso nel Regno di Dio, figlio mio.";
			link.l1 = "Ovviamente, fratello Julian - cos'altro avrebbero dovuto fare? Soprattutto se sono morti come Sorrèn e Rojas - credo che siano proprio quei narvali che hanno sbarrato la strada a Chimiseto.";
			link.l1.go = "WildRose_Mary_112_add";
		break;
		
		case "WildRose_Mary_112_add":
			StartInstantDialog("Mary", "WildRose_Mary_113", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Mary_113":
			dialog.text = "Sarebbe stato meglio se padre Domingo avesse scritto per intero i secondi nomi, giusto? Cosa significano queste «V.» e «J.» dopo i nomi di mia madre e il mio?";
			link.l1 = "E chi sarebbe questo Fabian, che è stato battezzato con te lo stesso giorno?";
			link.l1.go = "WildRose_Mary_114";
		break;
		
		case "WildRose_Mary_114":
			dialog.text = "Il figlio di Cécile Gallard. Oh, me ne sono ricordata solo ora! Lei mi ha cresciuta, anche se non è mai stata particolarmente affettuosa. Sicuramente perché io sono sopravvissuta, mentre Fabien no. Lui è morto pochi mesi dopo la nascita, giusto?";
			link.l1 = "Forse dovremmo parlarle, visto che da questo libriccino non abbiamo ricavato quasi nulla di utile – a meno che, certo, non contino le date della tua nascita e del battesimo.";
			link.l1.go = "WildRose_Mary_115";
		break;

		case "WildRose_Mary_115":
			dialog.text = "Non è molto più giovane di Aurélie, "+pchar.name+". Resta solo da sperare che almeno lei abbia la testa a posto. Ma cosa vuoi scoprire da lei?";
			link.l1 = "Beh, visto che era la tua balia, poteva benissimo sapere da padre Domingo qualche dettaglio della sua conversazione con Joshua. A chi, se non a lei, poteva raccontarlo? Forse anche ad Aurélie o a Eric. Ma mi sa che dalla prima abbiamo già ottenuto tutto il possibile, e il secondo ormai non dirà più nulla a nessuno.";
			link.l1.go = "WildRose_Mary_115_add";
		break;
		
		case "WildRose_Mary_115_add":
			StartInstantDialog("Julian", "WildRose_Mary_116", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Mary_116":
			dialog.text = "Questa brava donna è una fedele parrocchiana di questa casa di Dio. Non si perde mai una messa e si confessa regolarmente. Penso che possa davvero aiutarvi, figli miei.";
			link.l1 = "Grazie a voi, padre. Addio.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_24");
		break;
		
		case "WildRose_Sesil_1":
			dialog.text = ""+GetFullName(pchar)+" e Mary Casper. Che piacevole incontro!";
			link.l1 = "Piacere, "+npchar.name+". In effetti, siamo qui per voi. Vorremmo discutere con voi di una certa questione.";
			link.l1.go = "WildRose_Sesil_2";
			DelLandQuestMark(npchar);
			LAi_SetStayType(npchar);
		break;
		
		case "WildRose_Sesil_2":
			dialog.text = "Ah sì? Allora sono tutta orecchi.";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_2_add";
		break;
		
		case "WildRose_Sesil_2_add":
			StartInstantDialog("Mary", "WildRose_Sesil_3", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Sesil_3":
			dialog.text = "Riguarda i miei genitori, Cécile. Di mia madre abbiamo già scoperto tutto quello che potevamo... È morta subito dopo la mia nascita. Ma mio padre... è scomparso senza lasciare traccia dopo pochi giorni. Siamo portati a pensare che non sia morto, giusto?";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_3_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_3_add":
			StartInstantDialog("LSC_Sesil", "WildRose_Sesil_4", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_4":
			dialog.text = "Eh già, per mandare uno come lui all'altro mondo ci voleva davvero impegno...";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_4_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_4_add":
			StartInstantDialog("Mary", "WildRose_Sesil_5", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_5":
			dialog.text = "L'hai visto?! Hai parlato con lui?";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_5_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_5_add":
			StartInstantDialog("LSC_Sesil", "WildRose_Sesil_6", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_6":
			dialog.text = "Ragazza mia, l'ho visto sistemare due narvali quasi a mani nude...";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_6_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_6_add":
			StartInstantDialog("Mary", "WildRose_Sesil_7", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_7":
			dialog.text = "Con Sorrento e Rojas?";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_7_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_7_add":
			StartInstantDialog("LSC_Sesil", "WildRose_Sesil_8", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_8":
			dialog.text = "Avevo già allora un sacco di cose da fare per ricordarmi i nomi di quei furfanti – e adesso proprio non me li ricordo più.";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_8_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_8_add":
			StartInstantDialog("Mary", "WildRose_Sesil_9", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_9":
			dialog.text = "Va bene, non importa. Continua, per favore, Cécile.";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_9_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_9_add":
			StartInstantDialog("LSC_Sesil", "WildRose_Sesil_10", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_10":
			dialog.text = "E cosa c'è da continuare? Ha buttato quei due in acqua, sono andati a fondo come pietre, poi l'hanno bloccato e portato via sulla 'Tartarus'. E hanno fatto bene – chissà chi altro quel tagliagole avrebbe deciso di affogare...";
			link.l1 = "Tagliagole? Un po' forte, non trova, signora Gallard? Stiamo parlando di un uomo, di un ufficiale che ha appena perso la moglie...";
			link.l1.go = "WildRose_Sesil_11_1";
			link.l2 = "Vedo che non avete la migliore opinione su di lui – non di ogni ufficiale si direbbe una cosa simile.";
			link.l2.go = "WildRose_Sesil_11_2";
		break;

		case "WildRose_Sesil_11_1":
			dialog.text = "Ufficiale, eh già. Aveva una divisa notevole, me lo ricordo bene. Quasi impeccabile. Ma ne ho visti tanti di ufficiali, giovanotto. E tutti si comportavano con molta più dignità di quel... signore.";
			link.l1 = "Ha fatto qualcos'altro?   Oltre ad aver ucciso quei due?";
			link.l1.go = "WildRose_Sesil_12";
			ChangeCharacterComplexReputation(pchar, "honor", 1);
		break;

		case "WildRose_Sesil_11_2":
			dialog.text = "Ufficiale, eh già. Aveva una divisa notevole, me lo ricordo bene. Quasi impeccabile. Ma ne ho visti tanti di ufficiali, giovanotto. E tutti si comportavano con molta più dignità di quel... signore.";
			link.l1 = "Ha fatto qualcos'altro? Oltre ad aver ucciso quei due?";
			link.l1.go = "WildRose_Sesil_12";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Sesil_12":
			dialog.text = "Ha chiesto che gli portassero in cella il prete – padre De la Cruz...";
			link.l1 = "Ma guarda un po'! Proprio di questo volevamo parlare con voi. Conoscete i dettagli di quella conversazione?";
			link.l1.go = "WildRose_Sesil_13";
		break;

		case "WildRose_Sesil_13":
			dialog.text = "Beh certo, giovanotto! Quel mascalzone protestante ha preteso che il padre non battezzasse sua figlia – anche se sua madre era irlandese, quindi cattolica.";
			link.l1 = "È quasi la prima volta che sento un'inglese parlare così di un protestante... Ehm, scusate se vi ho interrotto, signora "+npchar.lastname+".";
			link.l1.go = "WildRose_Sesil_14";
		break;

		case "WildRose_Sesil_14":
			dialog.text = "Un tempo anch'io ero protestante, che male c'è ad ammetterlo. Ma fratello Julian è riuscito a guidarmi sulla retta via.";
			link.l1 = "Ecco come stanno le cose... Davvero un degno servitore del Signore. Ma ci siamo distratti. Quindi, Casper voleva che sua figlia crescesse nella fede protestante.";
			link.l1.go = "WildRose_Sesil_15";
		break;

		case "WildRose_Sesil_15":
			dialog.text = "Proprio così ha detto al nostro padre De la Cruz. E poi - ha ordinato di chiamare la bambina Giulia...";
			link.l1 = "Quindi è questo il significato di quella 'J.'. Mary Julia Casper... Ma allora perché l'hanno chiamata Mary?";
			link.l1.go = "WildRose_Sesil_16";
		break;

		case "WildRose_Sesil_16":
			dialog.text = "Perché così voleva sua madre, ecco perché. Quando la bambina fu tirata fuori dal suo grembo, lei sussurrò un nome – Mary. Io non ne fui testimone, ma Aurélie Bertin era presente al parto. Potete chiederlo a lei, se volete...";
			link.l1 = "Quindi, hanno tenuto conto proprio del desiderio di tua madre.";
			link.l1.go = "WildRose_Sesil_17";
		break;

		case "WildRose_Sesil_17":
			dialog.text = "E doveva forse essere diverso – visto che il mio caro papà è sparito come se la terra l'avesse inghiottito, giusto?";
			link.l1 = "Considerando... i talenti di padre De la Cruz, dubito che l'opinione di vostro padre sarebbe stata presa in considerazione, anche se fosse rimasto seduto sul 'Tartarus'. Domingo non vi ha detto nulla — non era a conoscenza dei piani di Kasper riguardo alla fuga e al possibile ritorno per la bambina?";
			link.l1.go = "WildRose_Sesil_18_1";
			link.l2 = "Forse avete ragione. Ma, tornando alla conversazione tra padre Domingo e il signor Kasper, il prete non ha accennato se Joshua avesse parlato con lui della fuga o dei tempi previsti per tornare a prendere sua figlia?";
			link.l2.go = "WildRose_Sesil_18_2";
		break;

		case "WildRose_Sesil_18_1":
			dialog.text = "Non mi ha mai parlato di niente del genere. Giusto? E poi pensaci, "+npchar.name+", se vi steste preparando a fuggire dalla prigione, andreste forse a raccontarlo al primo che capita? Quel tipo di certo non l'avrebbe fatto, ve lo dico io.";
			link.l1 = "Quindi anche questa pista non ci ha portato da nessuna parte. Beh, grazie per il tempo che ci avete dedicato, signora "+npchar.lastname+". Ci rivedremo.";
			link.l1.go = "WildRose_Sesil_19";
			ChangeCharacterComplexReputation(pchar, "honor", -1);
			AddCharacterExpToSkill(pchar, "charisma", 100);
		break;

		case "WildRose_Sesil_18_2":
			dialog.text = "Non mi ha mai parlato di nulla del genere. Giusto, pensaci anche tu, "+pchar.name+",   se doveste organizzare una fuga dalla prigione, raccontereste tutto al primo che capita? Quello lì di certo non l'avrebbe fatto, ve lo dico io.";
			link.l1 = "Quindi anche questa pista non ci ha portato da nessuna parte. Beh, grazie per il tempo che ci ha dedicato, signora "+npchar.lastname+". Ci rivedremo.";
			link.l1.go = "WildRose_Sesil_19";
			ChangeCharacterComplexReputation(pchar, "honor", 1);
		break;
		
		case "WildRose_Sesil_19":
			StartInstantDialog("Mary", "WildRose_Mary_121", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Mary_121":
			dialog.text = "Abbiamo scoperto parecchie cose interessanti, "+pchar.name+". Ma praticamente non siamo andati avanti, giusto.";
			link.l1 = "E si sono persino un po' confusi. Chissà chi è questo Rupert, a cui tua madre si rivolgeva prima di morire?";
			link.l1.go = "WildRose_Mary_122";
		break;

		case "WildRose_Mary_122":
			dialog.text = "Forse un fratello o... un amico intimo?";
			link.l1 = "Amico, dici... vediamo un po'... Mi chiedo se Joshua sapesse di lui...";
			link.l1.go = "WildRose_Mary_123";
		break;

		case "WildRose_Mary_123":
			dialog.text = "A cosa stai alludendo, "+pchar.name+"?";
			link.l1 = "Che dobbiamo rifletterci bene. Per fortuna avremo tutto il tempo del mondo mentre cerchiamo qualcuno che possa aiutarci nelle ricerche. Abbiamo fatto un bel lavoro. Ma non siamo ancora arrivati alla fine. Non possiamo entrare da soli negli uffici della Royal Navy, e poi si trovano oltreoceano, a Londra... Avete qualche idea su chi potrebbe darci una mano in questa faccenda?";
			link.l1.go = "WildRose_Mary_127";
		break;
		
		case "WildRose_Mary_127":
			dialog.text = "E che mi dici di Serge Benoit, Charles?";
			link.l1 = "Abate? Ha delle grandi conoscenze, giusto, ma dubito che riuscirà ad arrivare agli archivi della Marina Reale.";
			link.l1.go = "WildRose_Mary_128";
		break;
		
		case "WildRose_Mary_128":
			dialog.text = "Se non potrà farlo lui, magari ci metterà in contatto con qualcuno che ne è capace, giusto?";
			link.l1 = "Direi di sì. Allora, rotta su Saint-Pierre.";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_25");
		break;
		
		// =================================================================
		// =================== ЭТАП 3. «БУМАЖНАЯ РАБОТА» ===================
		// =================================================================
		
		case "WildRose_Mary_131":
			dialog.text = "E allora, adesso non ci resta che aspettare, giusto?";
			link.l1 = "Sono sicura che scoprirà tutto, "+npchar.name+". Il tempo volerà, non te ne accorgerai nemmeno. E intanto abbiamo altro da fare.";
			link.l1.go = "WildRose_Mary_132";
		break;

		case "WildRose_Mary_132":
			dialog.text = "Stai alludendo a qualcosa in particolare, amore?";
			link.l1 = "Abbiamo un sacco di cose da fare, ma perché adesso non torniamo sulla nave, chiudiamo la porta e ci dedichiamo un po' di tempo? Che ne dici?";
			link.l1.go = "WildRose_Mary_133";
		break;

		case "WildRose_Mary_133":
			dialog.text = "E lo sapevo che l'avresti proposto, giusto! Ti dico una cosa: non perdiamo tempo!";
			link.l1 = "Andiamo, mia adorata.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap3_Paperwork_3");
		break;
		
		case "WildRose_Mary_134":
			dialog.text = "Oh, "+pchar.name+", non puoi immaginare, proprio non puoi immaginare che peso mi sia appena caduto dall'anima, giusto!";
			link.l1 = "Me lo immagino benissimo, cara – sei tutta raggiante, ah-ah! Come vedi, non è stato tutto inutile.";
			link.l1.go = "WildRose_Mary_135";
		break;

		case "WildRose_Mary_135":
			dialog.text = "Mio padre era un ufficiale famoso, pensa un po'! Ma quanto mi dispiace che non abbiamo mai avuto modo di incontrarci. E poi non abbiamo mai saputo se sia riuscito ad arrivare sulla Terraferma, giusto...";
			link.l1 = "Se fosse successo, sarebbe sicuramente tornato in servizio, e da qualche parte si sarebbe sentito parlare di lui, giusto? Difficile immaginare che uno come lui sarebbe rimasto tranquillo in un posto solo – altrimenti, da chi avresti preso quel fuoco che hai dentro?";
			link.l1.go = "WildRose_Mary_136";
		break;

		case "WildRose_Mary_136":
			dialog.text = "Pensi davvero che sia morto? Finito nelle mani degli spagnoli a Cuba, o magari ucciso sull'Isola della Giustizia?";
			link.l1 = "Cerco di guardare la verità in faccia con lucidità, "+npchar.name+". In quegli anni c'era almeno qualche collegamento con l'Isola, i contrabbandieri ci andavano sulle loro tartane con invidiabile regolarità. Se fosse riuscito a lasciare l'Isola, non ho dubbi che, dopo un po', sarebbe tornato lì per te.";
			link.l1.go = "WildRose_Mary_137";
		break;

		case "WildRose_Mary_137":
			dialog.text = "Per portarmi via da lì. Ma allora non ci saremmo incontrati, giusto.";
			link.l1 = "Così è la vita, cara. Non sai mai dove troverai qualcosa e dove la perderai. Spero che non ti penti di essere qui con me, adesso.";
			link.l1.go = "WildRose_Mary_138";
		break;

		case "WildRose_Mary_138":
			dialog.text = "Non ho mai sentito una sciocchezza più grande in vita mia, giusto! "+pchar.name+", sei il migliore, sei fantastico! Grazie per aver fatto così tanto per aiutarmi a scoprire tutto questo. È davvero importante per me, giusto! Ma dai, studiamo i documenti – magari ci troviamo qualcosa che il nostro amico non ci ha raccontato...";
			link.l1 = "Buona idea. Iniziamo proprio adesso.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap3_Paperwork_7");
		break;
		
		case "WildRose_Mary_139":
			dialog.text = "Beh, "+pchar.name+", hai notato qualcosa di interessante?";
			link.l1 = "Sì, "+npchar.name+". Qualcosa c'è... ";
			link.l1.go = "WildRose_Mary_140";
		break;

		case "WildRose_Mary_140":
			dialog.text = "Sembri aver visto un fantasma, giusto.";
			link.l1 = "Qui si parla di un certo Rupert Northwood.";
			link.l1.go = "WildRose_Mary_141";
		break;

		case "WildRose_Mary_141":
			dialog.text = "Rupert Northwood?! Davvero – proprio lui, giusto?";
			link.l1 = "Zitta, "+npchar.name+" - non urlare così. Mh... Penso di sì, giusto? È proprio quella persona di cui parlava Chimiset. Non può essere altrimenti – coincidenze così non esistono.";
			link.l1.go = "WildRose_Mary_142";
		break;

		case "WildRose_Mary_142":
			dialog.text = "E tu che ne pensi di tutto questo, "+pchar.name+"?";
			link.l1 = "Questa storia sta diventando sempre più intricata. Quindi... da Plymouth è salpata la 'Cornwall', ad Antigua è arrivata sempre la 'Cornwall', ma sugli scogli dell'Isola della Giustizia si è schiantata la 'Wrangler' — sempre con Joshua Kasper al comando, che è riuscito a sposarsi in segreto, all'insaputa dell'Ammiragliato, con una donna che in punto di morte invocava un certo Rupert.";
			link.l1.go = "WildRose_Mary_143";
		break;

		case "WildRose_Mary_143":
			dialog.text = "Non capisco niente. Non so nemmeno chi altro potrebbe far luce su di lui. Più cerchiamo di scoprire qualcosa su mio padre, più affondiamo in una palude di misteri e segreti sempre nuovi, giusto?";
			link.l1 = "Se qualcuno può chiarire almeno qualcosa, è o Joshua Kasper o Rupert Northwood.";
			link.l1.go = "WildRose_Mary_144";
		break;

		case "WildRose_Mary_144":
			dialog.text = "Northwood? Ma lui è morto, giusto? Non penserai mica che il rapporto compilato all'arrivo della 'Cornwall' a Saint John contenga informazioni false?";
			link.l1 = "Oh, questa tua ingenuità, "+npchar.name+"... Comincio a pensare che tutta questa storia sia letteralmente intrisa di menzogne. Pensa un po': Joshua Kasper era un ufficiale modello — una marea di onorificenze e nessuna sanzione. Non ti sembra che stoni con tutto ciò che abbiamo scoperto su di lui all'Isola della Giustizia, dove ha mandato all'altro mondo due persone senza esitare?";
			link.l1.go = "WildRose_Mary_145";
		break;

		case "WildRose_Mary_145":
			dialog.text = "Ha lottato per la vita di sua moglie, mia madre, "+pchar.name+"!";
			link.l1 = "Senza dubbio, ma pensiamo un attimo, da dove è saltata fuori? E soprattutto - perché ha nascosto il suo matrimonio all'Ammiragliato? Un militare fino al midollo, fedele al regolamento e al dovere d'ufficiale - altrimenti il suo fascicolo non sarebbe stato così immacolato - e poi all'improvviso un gesto simile.";
			link.l1.go = "WildRose_Mary_146";
		break;

		case "WildRose_Mary_146":
			dialog.text = "E se dietro tutto questo si nascondesse una storia bella e romantica? Succede, anche se raramente, giusto?";
			link.l1 = "Non fraintendermi, Mary, ma tutto questo non sembra affatto una storia romantica. Somiglia piuttosto a una messa in scena, e nemmeno si capisce a che scopo. Perché cambiare nome alla nave durante il viaggio verso Providence? È una nave militare — per simili bravate si rischia la corte marziale.";
			link.l1.go = "WildRose_Mary_147";
		break;

		case "WildRose_Mary_147":
			dialog.text = "D'accordo - bella domanda.";
			link.l1 = "Anche con questo Rupert Northwood c'è chiaramente qualcosa che non va. Nella battaglia è caduta quasi metà dell'equipaggio, ma, stranamente, nessun ufficiale tranne lui. E perché tua madre, prima di morire, ha invocato proprio Rupert e non suo marito Joshua?";
			link.l1.go = "WildRose_Mary_148";
		break;

		case "WildRose_Mary_148":
			dialog.text = "Quindi, sei davvero sicuro che il primo ufficiale non sia morto nella battaglia con gli spagnoli, giusto? E che io non sia affatto la figlia di Joshua Casper, ma di Rupert Northwood – è lì che vuoi arrivare?";
			link.l1 = "Come ho già detto, la verità è nota solo a una persona. O a Joshua Casper, che per qualche motivo ha chiamato Teresa sua moglie, oppure a Rupert Northwood, che altrettanto inspiegabilmente si è fatto passare per il suo capitano.";
			link.l1.go = "WildRose_Mary_149";
		break;

		case "WildRose_Mary_149":
			dialog.text = "Che diavoleria, giusto! E adesso che facciamo, "+pchar.name+"?   Ora voglio ancora di più arrivare alla verità, ma abbiamo già spremuto tutti fino all'ultima goccia, giusto?";
			link.l1 = "Se da qualche parte ci sono delle risposte, allora è sull'Isola della Giustizia – non è rimasto nessun altro, a parte forse oltre l'oceano, che abbia conosciuto i tuoi genitori, anche solo di sfuggita. Penso che dovremmo parlare ancora una volta con Aurélie Bertin – magari le verrà in mente qualcos'altro a cui possiamo aggrapparci.";
			link.l1.go = "WildRose_Mary_150";
		break;

		case "WildRose_Mary_150":
			dialog.text = "Ma cosa vuoi scoprire da lei? Mi sembra che ci abbia già detto tutto quello che sapeva.";
			link.l1 = "Ci ha raccontato quello che le abbiamo chiesto, e potrebbe benissimo aver tralasciato qualche dettaglio importante. Magari tuo padre aveva una cicatrice sul viso, o gli mancava un dito sulla mano... Dubito che una persona capace di inventarsi tutti questi trucchi con il cambio del nome della nave e, forse, anche del proprio nome, possa essere finita in modo così misero su un'isola o nelle segrete dei castigliani.";
			link.l1.go = "WildRose_Mary_151";
		break;

		case "WildRose_Mary_151":
			dialog.text = "Forse hai ragione...";
			link.l1 = "E se decidiamo di continuare la ricerca – non più tra gli scaffali impolverati dell'Ammiragliato, ma qui, nell'Arcipelago – ci servirà qualcosa di più di un semplice nome, e per di più falso.";
			link.l1.go = "WildRose_Mary_152";
		break;

		case "WildRose_Mary_152":
			dialog.text = "Sai, tutto questo mi fa venire la pelle d'oca, giusto? Forse perché è tutto così... travolgente, o forse perché penso che mio padre non fosse poi così diverso da quel bastardo della piantagione di Bishop.";
			link.l1 = "Comunque sia, ti prometto che faremo tutto il possibile per capire cosa sta succedendo. Quindi, non perdiamo tempo. Andiamo!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap3_Paperwork_9");
		break;
		
		// =================================================================
		// ==================== ЭТАП 4. «ПУТЬ К СВЕТУ» =====================
		// =================================================================
		case "WildRose_Mary_161":
			dialog.text = "Andiamo, "+pchar.name+", non perdiamo tempo inutilmente, giusto?";
			link.l1 = "Spero che Aurélie sia nella sua cabina, e che non dovremo perlustrare tutta l'Isola per trovarla...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_2");
		break;
		
		case "WildRose_Mary_162":
			dialog.text = "Sembra che non ci sia andata bene di nuovo, giusto? E dove mai potrebbe essere finita?";
			link.l1 = "Spero che la malattia non abbia di nuovo preso il controllo della sua mente...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_4");
		break;
		
		case "WildRose_Jillian_31":
			dialog.text = "Ah, siete di nuovo qui. Beh, salve... Che succede, avete ancora bisogno di Aurélie?";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_31_add";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Jillian_31_add":
			StartInstantDialog("Mary", "WildRose_Jillian_32", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_32":
			dialog.text = "Non ti manca certo l'ingegno, Gillian. Non sai per caso dove sia?";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_32_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_32_add":
			StartInstantDialog("LSC_Jillian_clone", "WildRose_Jillian_33", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_33":
			dialog.text = "In chiesa, stava per confessarsi. Se vi sbrigate, la troverete ancora lì.";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_33_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_33_add":
			StartInstantDialog("Mary", "WildRose_Jillian_34", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_34":
			dialog.text = "Beh, se lei si sta confessando, allora di sicuro è sana di mente e ricorda tutto, giusto.";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_34_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_34_add":
			StartInstantDialog("LSC_Jillian_clone", "WildRose_Jillian_35", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_35":
			dialog.text = "È difficile da dire... Negli ultimi tre giorni è come fuori di sé, non riesce a stare ferma. Sapete, si è agitata terribilmente quando ha visto gli alberi della vostra nave oltre l'anello esterno.";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_35_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_35_add":
			StartInstantDialog("Mary", "WildRose_Jillian_36", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_36":
			dialog.text = "Chissà perché, eh?";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_36_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_36_add":
			StartInstantDialog("LSC_Jillian_clone", "WildRose_Jillian_37", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_37":
			dialog.text = "Beh, probabilmente la infastidisce l'idea di dover rispondere ancora alle tue domande. Ma quando mai ti sono importati i problemi degli altri, giusto?";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_37_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_37_add":
			StartInstantDialog("Mary", "WildRose_Jillian_38", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_38":
			dialog.text = "Non osare parlarmi in questo tono, Gillian. Questa volta ti perdono, ma osa solo ripetere qualcosa del genere...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_5");
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		
		case "WildRose_Jillian_41":
			dialog.text = "Che tipo nervosa, basta che qualcosa non vada come vuole lei, giusto?";
			link.l1 = "Non vale la pena provocarla senza motivo, "+npchar.name+". Lo sapete, no, che la spada non la porta solo per bellezza.";
			link.l1.go = "WildRose_Jillian_42";
		break;
		
		case "WildRose_Jillian_42":
			dialog.text = "E voi avreste permesso che accadesse una cosa del genere, "+pchar.name+"?";
			link.l1 = "Non avete ancora visto Mary in battaglia, "+npchar.name+". Altrimenti non si farebbero illusioni che qualcuno o qualcosa possa fermarla. Ci rivedremo.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_7");
		break;
		
		case "WildRose_Mary_163":
			dialog.text = "Forse vuoi chiedermi qualcosa, giusto? "+pchar.name+", giusto...";
			link.l1 = "A dire la verità, non mi interessa poi molto che cosa sia successo tra voi due, anche se immagino già come si chiamava quella gatta. Anzi, come si chiamava. Vuoi davvero parlarne così tanto?";
			link.l1.go = "WildRose_Mary_164_1";
			link.l2 = "Tu e Gillian avete litigato per qualcosa? O forse, meglio dire, per qualcuno?";
			link.l2.go = "WildRose_Mary_164_2";
		break;

		case "WildRose_Mary_164_1":
			dialog.text = "Hmm, in realtà, no.";
			link.l1 = "Come vuoi. E adesso andiamo a cercare Aurélie.";
			link.l1.go = "WildRose_Mary_165";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Mary_164_2":
			dialog.text = "Quella biscia non mi perdonerà mai che Alan abbia preferito me a lei. Anche se potrebbe, considerando che lui ormai non c'è più... A dire il vero, "+pchar.name+", preferirei non parlarne, giusto.";
			link.l1 = "Come vuoi, cara. Allora andiamo a cercare Aurélie.";
			link.l1.go = "WildRose_Mary_165";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;
		
		case "WildRose_Mary_165":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_9");
		break;
		
		case "WildRose_Oreli_61":
			dialog.text = ""+pchar.name+", Mary! Sei di nuovo sull'Isola, che gioia!";
			link.l1 = "Felici di vedervi in buona salute, "+npchar.name+". In realtà, siamo venuti sull'Isola proprio per parlare ancora con voi. Ma non preoccupatevi, non ci vorrà molto tempo.";
			link.l1.go = "WildRose_Oreli_62";
			DelLandQuestMark(npchar);
		break;
		
		case "WildRose_Oreli_62":
			dialog.text = "Oh-oh, ragazzi, proprio non avete pietà per una vecchietta. Ma sentivo che sarebbe venuto. È di nuovo per via dei tuoi genitori, giusto, Mary?";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_62_add";
		break;

		case "WildRose_Oreli_62_add":
			StartInstantDialogTurnToNPC("Mary", "WildRose_Oreli_63", "Quest\CompanionQuests\WildRose.c", "LSC_Oreli");
		break;

		case "WildRose_Oreli_63":
			dialog.text = "Ti prego, Aurélie. Capisco che ti sia difficile ricordare tutto questo, visto quanto tempo è passato, ma prova ancora una volta, per favore, giusto?";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_63_add";
		break;

		case "WildRose_Oreli_63_add":
			StartInstantDialogTurnToNPC("LSC_Oreli", "WildRose_Oreli_64", "Quest\CompanionQuests\WildRose.c", "Mary");
		break;

		case "WildRose_Oreli_64":
			dialog.text = "Vi ho già raccontato tutto quello che ricordo. Non riesco proprio a capire cos'altro volete tirarmi fuori, giusto?";
			link.l1 = "Vi faremo un paio di domande, "+npchar.name+". Cercate, per favore, di ricordare qualcosa – qualche dettaglio o particolare. Non vi metteremo sotto pressione...";
			link.l1.go = "WildRose_Oreli_65";
		break;

		case "WildRose_Oreli_65":
			dialog.text = "Ma non è proprio quello che state facendo adesso?";
			link.l1 = "Avete già fatto così tanto per noi, "+npchar.name+"... Speriamo solo che nei labirinti della tua memoria si trovi qualcos'altro che possa davvero aiutarci.";
			link.l1.go = "WildRose_Oreli_66_1";
			link.l2 = "Abbiamo fatto tanta strada, "+npchar.name+". Non potete nemmeno immaginare quanta fatica e quanto tempo ci sia costato. Ma ci siamo smarriti, e solo voi e la vostra memoria potete riportarci sulla strada della verità.";
			link.l2.go = "WildRose_Oreli_66_2";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), pchar);
		break;

		case "WildRose_Oreli_66_1":
			dialog.text = "Alla memoria... Cosa ne è rimasto, di questa memoria. A volte la mattina non riesco nemmeno a ricordare come mi chiamo, e voi volete da me i dettagli – di fatti accaduti vent'anni fa. Ma va bene, chiedete pure.";
			link.l1 = "Ci interessa il signor Casper, il padre di Mary. Può ricordare qualcosa di particolare del suo aspetto? Forse aveva una cicatrice sul viso, oppure zoppicava molto...";
			link.l1.go = "WildRose_Oreli_67";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;

		case "WildRose_Oreli_66_2":
			dialog.text = "Alla memoria... Cosa ne è rimasto, di questa memoria. A volte la mattina non riesco nemmeno a ricordare come arrivare al gabinetto, e voi volete da me i dettagli di quello che succedeva vent'anni fa su questi relitti. Ma va bene, sia come sia, chiedete pure.";
			link.l1 = "Ci interessa il signor Casper, il padre di Mary. Può ricordare qualcosa di particolare del suo aspetto? Magari aveva una cicatrice sul viso, oppure zoppicava molto...";
			link.l1.go = "WildRose_Oreli_67";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Oreli_67":
			dialog.text = "Oh... Mi sa che l'ho già detto, ma l'ho visto solo nell'oscurità più totale, nella stiva della 'Ceres Smiti', dove avevano preparato un giaciglio per la povera Teresa. Non zoppicava, questo è certo – anzi, era un uomo piuttosto agile.";
			link.l1 = "E la sua età? Era giovane o già avanti con gli anni?";
			link.l1.go = "WildRose_Oreli_68";
		break;

		case "WildRose_Oreli_68":
			dialog.text = "Vecchio non lo definirei di certo... Ma non gli ho prestato molta attenzione – ero più preoccupata per Teresa. A dire il vero, aveva un aspetto piuttosto malconcio – sembrava quasi un fantasma. Comunque, considerate che per tutta la settimana, mentre sua moglie era incinta, lui praticamente non ha chiuso occhio... Continuava a correre su e giù per l'Isola, senza fermarsi mai.";
			link.l1 = "Dunque, sua moglie la amava davvero tanto. E voi avete passato molto tempo accanto a lei, giusto? Non vi ha mai parlato di suo marito?";
			link.l1.go = "WildRose_Oreli_69";
		break;

		case "WildRose_Oreli_69":
			dialog.text = "Teresa chiedeva sempre di lui. Dormiva molto, a volte delirava, ma appena si riprendeva, subito domandava dove fosse. E la poverina lo aspettava tanto, tanto. Ma nel momento più importante - non è mai arrivato.";
			link.l1 = "Capisco. Evidentemente, il loro amore era reciproco... Beh, grazie, Aurélie. Ci avete davvero aiutato.";
			link.l1.go = "WildRose_Oreli_70";
		break;

		case "WildRose_Oreli_70":
			dialog.text = "E tutto qui? Pensavo che la nostra conversazione sarebbe durata almeno un'ora o due, giusto?";
			link.l1 = "Abbiamo promesso di non tormentarti a lungo, giusto? Abbi cura di te, "+npchar.name+". Stammi bene.";
			link.l1.go = "WildRose_Oreli_71";
		break;

		case "WildRose_Oreli_71":
			dialog.text = "Aspettate, ragazzi! Ho ancora qualcosa per voi... Anzi, per te, Mary.";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_72_a";
			NPCsLookEachOther("LSC_Oreli", "Mary");
		break;
		
		case "WildRose_Oreli_72_a": //
			dialog.text = "Ecco, piccola mia, prendi... Appena ho visto le vele della sua nave, ho preso con me questo cappello per non dimenticarlo. Ma andare al molo... non ho avuto il coraggio.";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_72_add";
		break;

		case "WildRose_Oreli_72_add":
			StartInstantDialogTurnToNPC("Mary", "WildRose_Oreli_73", "Quest\CompanionQuests\WildRose.c", "LSC_Oreli");
		break;

		case "WildRose_Oreli_73":
			dialog.text = "Cos'è, Aurélie? Un cappello?..";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_73_add";
		break;

		case "WildRose_Oreli_73_add":
			StartInstantDialogTurnToNPC("LSC_Oreli", "WildRose_Oreli_74", "Quest\CompanionQuests\WildRose.c", "Mary");
		break;

		case "WildRose_Oreli_74":
			dialog.text = "Il cappello di tua madre, Teresa. Ce l'aveva con sé quando i superstiti del naufragio furono portati sulla 'Ceres Smitty'. Quando Teresa è morta, ho raccolto quel cappello da terra accanto al suo letto – e poi me ne sono dimenticata… Me ne sono ricordata solo oggi, durante la nostra conversazione.";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_74_add";
		break;

		case "WildRose_Oreli_74_add":
			StartInstantDialogTurnToNPC("Mary", "WildRose_Oreli_75", "Quest\CompanionQuests\WildRose.c", "LSC_Oreli");
		break;

		case "WildRose_Oreli_75":
			dialog.text = "Orelie... L'hai custodita per tutti questi anni! E... e non l'hai buttata, non l'hai venduta... Grazie, grazie davvero! Non immagini nemmeno quanto sia... prezioso e importante per me, giusto!";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_75_add";
		break;

		case "WildRose_Oreli_75_add":
			StartInstantDialogTurnToNPC("LSC_Oreli", "WildRose_Oreli_76", "Quest\CompanionQuests\WildRose.c", "Mary");
		break;

		case "WildRose_Oreli_76":
			dialog.text = "Scusami, Mary – avrei dovuto dartela tanto tempo fa... Ma ormai la mia memoria è un vecchio colabrodo – ecco...";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_76_add";
		break;

		case "WildRose_Oreli_76_add":
			StartInstantDialogTurnToNPC("Mary", "WildRose_Oreli_77", "Quest\CompanionQuests\WildRose.c", "LSC_Oreli");
		break;

		case "WildRose_Oreli_77":
			dialog.text = "Non poteva esserci momento migliore, Aurélie! La provo subito, giusto?";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_hat_1");
		break;
		
		case "WildRose_Mary_166":
			dialog.text = "Allora, caro, come ti sembro?..";
			link.l1 = "Sei bellissima. E il cappello... non è ancora passato di moda, quindi sta benissimo anche lui, giusto?";
			link.l1.go = "WildRose_Mary_167";
		break;
		
		case "WildRose_Mary_167":
			dialog.text = "Davvero? Sono così felice che ti piaccia, giusto!";
			link.l1 = "Ma potrebbe essere altrimenti?";
			link.l1.go = "WildRose_Mary_167_add";
		break;
		
		case "WildRose_Mary_167_add":
			StartInstantDialogTurnToNPC("LSC_Oreli", "WildRose_Mary_168", "Quest\CompanionQuests\WildRose.c", "Mary");
		break;
		
		case "WildRose_Mary_168":
			dialog.text = "...";
			link.l1 = "Grazie ancora, Aurélie — avete reso questa giornata un po' più luminosa! State bene e riposatevi.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_10");
		break;
		
		case "WildRose_Mary_171":
			dialog.text = "Quindi era davvero Rupert. Rupert Northwood, giusto.";
			link.l1 = "Ovviamente sì, cara. Ha fatto di tutto per salvare sua moglie... o la sua amata, non lo so. In realtà non importa. L'importante è che ora sappiamo chi dobbiamo cercare.";
			link.l1.go = "WildRose_Mary_172";
		break;

		case "WildRose_Mary_172":
			dialog.text = "Ma che fine ha fatto il vero Joshua Casper, il capitano del 'Cornwall'?";
			link.l1 = "Domanda interessante, ma non la più importante adesso. Perché Rupert non è tornato a cercarti, se amava così tanto Teresa? Ecco, questo sì che è curioso. Sarà la prima cosa che gli chiederemo. Sempre che sia ancora vivo e che riusciamo a trovarlo. Una cosa è certa: non è tornato alla flotta. Non aveva alcun motivo di rischiare così tanto.";
			link.l1.go = "WildRose_Mary_174";
		break;

		case "WildRose_Mary_174":
			dialog.text = "Cosa mai avrebbe potuto spingerlo a chiamarsi Joshua Casper?   Cosa è successo a bordo del 'Cornwall', che è diventato il 'Wrangler'?   Non può essere che mio padre sia un criminale, "+pchar.name+"?";
			link.l1 = "Temo che non si possa escludere nemmeno questa possibilità, "+npchar.name+". Dobbiamo essere pronti davvero a tutto.";
			link.l1.go = "WildRose_Mary_175";
		break;

		case "WildRose_Mary_175":
			dialog.text = "Non voglio nemmeno pensarci...";
			link.l1 = "Per ora dobbiamo pensare ad altro – dove cercarlo. Potrebbe essersi unito ai pirati o ai contrabbandieri. Oppure si è sistemato in qualche città e non si fa vedere. Tutto è possibile.";
			link.l1.go = "WildRose_Mary_176";
		break;
		
		case "WildRose_Mary_176":
			dialog.text = "E cosa proponi di fare? Come lo troviamo? Dovremmo entrare in ogni colonia, dire il suo nome e sperare che qualcuno abbia sentito parlare di Rupert Northwood?";
			link.l1 = "Oppure Joshua Kasper. Avrebbe potuto benissimo continuare a vivere sotto le spoglie del suo ex capitano — molto probabilmente morto. Ma ciò comportava dei rischi, perché il brigantino scomparso poteva essere cercato. Soprattutto considerando che trasportava un baule d'argento destinato alla guarnigione di Providence.";
			link.l1.go = "WildRose_Mary_177";
		break;

		case "WildRose_Mary_177":
			dialog.text = "Hai proprio ragione, giusto?";
			link.l1 = "E invece il presunto defunto presso le isole Azzorre, Rupert Northwood, difficilmente avrebbe potuto suscitare l'interesse di qualcuno. Tuttavia, qui c'è sicuramente ancora qualcosa su cui riflettere.";
			link.l1.go = "WildRose_Mary_178";
		break;

		case "WildRose_Mary_178":
			dialog.text = "Quanto altro tempo dovremo ancora perdere, "+pchar.name+"?! Potrebbe essere ovunque, in qualsiasi colonia, giusto!";
			link.l1 = "Se è sopravvissuto, naturalmente. Ma non sono d'accordo con te. Dubito che parlasse spagnolo fluentemente, quindi non avrebbe senso per lui andare né a Cuba né a Hispaniola. Poteva parlare francese e andare a Tortuga o in una delle colonie delle Piccole Antille. Oppure poteva stabilirsi nella Main Occidentale, sotto la protezione dei connazionali. Potremmo davvero passare mesi a cercarlo – e non è affatto detto che avremo successo.";
			link.l1.go = "WildRose_Mary_179";
		break;

		case "WildRose_Mary_179":
			dialog.text = "Ma non voglio arrendermi, "+pchar.name+". Solo non adesso, quando ormai abbiamo scoperto così tanto, giusto!";
			link.l1 = "Non l'ho nemmeno proposto, "+npchar.name+" . Non dobbiamo cercarlo da soli - meglio rivolgerci a qualcuno che ha le giuste conoscenze. Una volta ha già funzionato, giusto? Perché non provarci di nuovo?";
			link.l1.go = "WildRose_Mary_180";
		break;

		case "WildRose_Mary_180":
			dialog.text = "Mi stai suggerendo di chiedere di nuovo aiuto all'abate? Mi sembrava che ci avesse già fatto capire che non dovremmo più contare sul suo sostegno in questa faccenda, giusto?";
			link.l1 = "Sarebbe davvero troppo sfacciato nei confronti del vecchio, hai ragione.";
			link.l1.go = "WildRose_Mary_181";
		break;

		case "WildRose_Mary_181":
			dialog.text = "Ma allora da chi dovremmo andare? Chi ha abbastanza soldi e conoscenze per una cosa del genere?";
			link.l1 = "Be', a finanziare le ricerche toccherà sicuramente a noi. Quanto ai contatti... Suppongo che potrebbe aiutarci Faddej Moscovita. Di certo conosce persone competenti da mandare nelle colonie. Oppure saprà indicarci a chi rivolgerci.";
			link.l1.go = "WildRose_Mary_182";
		break;

		case "WildRose_Mary_182":
			dialog.text = "Quindi, andiamo a Basseterre?";
			link.l1 = "Sì, andiamo a trovare il nostro amico. Non mi sembra un compito troppo difficile per lui, giusto?";
			link.l1.go = "WildRose_Mary_183";
		break;

		case "WildRose_Mary_183":
			dialog.text = "Salpiamo domani, che ne dici? Vorrei passare il resto di questa giornata e la notte insieme a te, solo noi due, sulla 'Ceres Smithy'.";
			link.l1 = "A proposte così non si dice di no, cara. Noi due ci siamo proprio meritati un po' di riposo.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_12");
		break;
		
		case "WildRose_Jillian_51":
			dialog.text = "State già lasciando l'Isola? Davvero non resterete nemmeno per il funerale?";
			link.l1 = "Un funerale?..";
			link.l1.go = "WildRose_Jillian_52";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Jillian_52":
			dialog.text = "Ah, quindi non lo sapevi. Capisco... Aurélie Bertin è morta stanotte.";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_52_add";
		break;

		case "WildRose_Jillian_52_add":
			StartInstantDialog("Mary", "WildRose_Jillian_53", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_53":
			dialog.text = "Cosa?! Non può essere – proprio ieri abbiamo parlato con lei, ed era viva e in salute. Oppure qualcuno l'ha...";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_53_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
		break;

		case "WildRose_Jillian_53_add":
			StartInstantDialog("LSC_Jillian_clone", "WildRose_Jillian_54", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_54":
			dialog.text = "No, Mary. Aurelie è morta nel sonno. Sono andata da lei oggi, per portarle degli unguenti per le articolazioni preparati da fratello Julian – e l'ho trovata così. Era sdraiata sul letto, con uno strano sorriso sulle labbra. Ma già pallida e fredda. \nL'ultima settimana la vecchietta non era più la stessa, ho persino pensato che la malattia scacciata dallo stregone nero fosse tornata. Ma la sua mente era lucida e, sembra, non delirava.";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_54_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
		break;

		case "WildRose_Jillian_54_add":
			StartInstantDialog("Mary", "WildRose_Jillian_55", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_55":
			dialog.text = "Almeno non ha sofferto, giusto.";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_55_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
		break;

		case "WildRose_Jillian_55_add":
			StartInstantDialog("LSC_Jillian_clone", "WildRose_Jillian_56", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_56":
			dialog.text = "Allora resterete per il funerale? Si terrà domani, sulla scogliera più lontana – lì l'acqua è abbastanza profonda, e i granchi non ci arrivano, giusto?";
			link.l1 = "Resteremo, Gillian. Aurélie ha fatto così tanto per Mary che non potremmo fare altrimenti, giusto? Se nessuno è contrario, organizzeremo la processione sulla nostra nave. La seppelliremo in mare aperto, con tutti gli onori.";
			link.l1.go = "WildRose_Jillian_57";
		break;
		
		case "WildRose_Jillian_57":
			dialog.text = "Nessuno si opporrà. È più comodo, e alla fine anche più sicuro che arrampicarsi tra i relitti.";
			link.l1 = "Allora occupatevi dell'organizzazione del funerale – Mary vi aiuterà. Io invece devo parlare con qualcuno...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_14");
		break;
		
		case "WildRose_Chimiset_61":
			dialog.text = "E di nuovo sei qui, mio caro amico! Cosa posso fare per te questa volta?";
			link.l1 = "Ciao, "+npchar.name+". Hai già sentito quello che è successo stanotte?";
			link.l1.go = "WildRose_Chimiset_62";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Chimiset_62":
			dialog.text = "Parli della morte di Aurélie? Vedo che sì. Certo che ho sentito. Lei viveva sul 'Pluto', che praticamente è territorio dei Rivadòs. E anche la gente sulle altre navi non parla d'altro.";
			link.l1 = "Ci siamo visti proprio ieri, e stava bene – a parte il fatto che era agitata per qualcosa tutta l'ultima settimana. E quando ha visto la nostra nave, si è agitata ancora di più.";
			link.l1.go = "WildRose_Chimiset_63";
		break;

		case "WildRose_Chimiset_63":
			dialog.text = "Una persona sente quando il fiume della sua vita si sta prosciugando. C'è chi lo mostra a tutti, chi lo tiene dentro di sé, ma in un modo o nell'altro lo sentono tutti – soprattutto quelli che sanno ascoltare il proprio cuore.";
			link.l1 = "Mi è sembrato che fosse in salute, praticamente come una giovane cerbiatta, "+npchar.name+". E qualcosa qui non torna...";
			link.l1.go = "WildRose_Chimiset_64_1";
			link.l2 = "Eppure, non era certo agli ultimi respiri, "+npchar.name+".";
			link.l2.go = "WildRose_Chimiset_64_2";
		break;

		case "WildRose_Chimiset_64_1":
			dialog.text = "Amico mio, mente e corpo sono cose di natura completamente diversa. La mente guida il corpo, a volte è il corpo a cercare di prendere il sopravvento sulla mente. Sono strettamente connessi, ma non formano un tutto unico. Una persona può sembrare perfettamente sana all'esterno, ma la sua anima potrebbe già incamminarsi sul sentiero della morte.";
			link.l1 = "Sei intelligente, amico mio, molto intelligente. Se sentirai che la verità ti gira intorno, la inseguirai come un leone fa con una zebra – e non smetterai finché non l'avrai afferrata. L'ho capito subito, appena ti ho visto.";
			link.l1.go = "WildRose_Chimiset_65";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Chimiset_64_2":
			dialog.text = "Amico mio, la mente e il corpo sono cose di tutt'altro ordine. La mente governa il corpo, a volte il corpo cerca di prendere il controllo sulla mente. Sono strettamente legati, ma non sono un tutt'uno. Una persona può sembrare perfettamente sana fuori, ma la sua anima può già camminare sul sentiero della morte.";
			link.l1 = "Sai, mi è venuto in mente che Aurelie sembrava quasi aspettarci, sapeva che saremmo venuti da lei. La vecchietta avrebbe potuto morire un giorno prima o dopo, ma è successo quasi subito dopo che ci ha raccontato qualcosa di importante sul padre di Mary.";
			link.l1.go ="WildRose_Chimiset_65";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Chimiset_65":
			dialog.text = "Sei intelligente, amico mio, molto intelligente. Se sentirai che la verità ti gira intorno, la inseguirai come un leone fa con una zebra – e la caccerai finché non sarà tua. L'ho capito subito, appena ti ho visto.";
			link.l1 = "Non ho... Aspetta un attimo. Quel rito che hai fatto nella stiva del 'Protector'... non ha rallentato il progresso della malattia di Aurélie, giusto? Allora cosa hai fatto davvero?";
			link.l1.go = "WildRose_Chimiset_66";
		break;

		case "WildRose_Chimiset_66":
			dialog.text = "Si può riempire un fiume di pietre, ma ciò non ne fermerà il corso. Sapevo che da Aurélie volevate qualcosa di importante — e sapevo anche che non ci sareste arrivati subito. Ma quanto tempo avrebbe richiesto il vostro cammino, questo mi era ignoto. Così ho eretto una diga, richiamando tutte le sue forze vitali per contenere la malattia finché non avesse compiuto il suo destino. E non appena è accaduto, l'ostacolo è crollato...";
			link.l1 = "Quindi, Aurélie... nel momento della morte non era affatto in sé, non si rendeva conto di sé stessa - proprio come pensavamo?";
			link.l1.go = "WildRose_Chimiset_67";
		break;

		case "WildRose_Chimiset_67":
			dialog.text = "Ha impiegato tutte le sue forze per restare lucida e cosciente, e quando non è più servito, la malattia l'ha travolta come un'onda immensa, portandola nella valle della morte. Se la sua fine fu serena, o se se n'è andata al vostro Dio tormentata dai fantasmi del passato e da incubi terribili — non posso dirlo, perché non lo so.";
			link.l1 = "Lo sapevi benissimo a cosa avrebbe portato tutto questo, giusto? Perché diavolo non mi hai avvertita delle conseguenze?! Allora, parla!";
			link.l1.go = "WildRose_Chimiset_68_1";
			link.l2 = "Sapevi bene quello che facevi, "+npchar.name+". Perché non mi hai avvertita di dove tutto questo poteva portare?";
			link.l2.go = "WildRose_Chimiset_68_2";
		break;

		case "WildRose_Chimiset_68_1":
			dialog.text = "Perché ho deciso di aiutarti, amico mio, a scoprire ciò che vi serviva sapere, e lei — a compiere il suo destino. Se ti avessi detto ciò che l'aspettava, forse non te la saresti sentita — e Aurélie avrebbe portato i suoi segreti con sé nell'aldilà. A che sarebbe servito? Sarebbe morta invano. Come un'antilope sbranata da un leone, ma non mangiata, lasciata invece agli avvoltoi.";
			link.l1 = "Destino, utilità... Sei proprio un arbitro dei destini, "+npchar.name+". Dio in sembianze umane.";
			link.l1.go = "WildRose_Chimiset_69";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;

		case "WildRose_Chimiset_68_2":
			dialog.text = "Perché ho deciso di aiutarti, amico mio, a scoprire ciò che vi serviva sapere, e lei — a compiere il suo destino. Se ti avessi detto ciò che l'aspettava, forse non te la saresti sentita — e Aurélie avrebbe portato i suoi segreti con sé nell'aldilà. A che sarebbe servito? Sarebbe morta invano. Come un'antilope sbranata da un leone, ma non mangiata, lasciata invece agli avvoltoi.";
			link.l1 = "Destino, utilità... Sei proprio un arbitro dei destini, "+npchar.name+". Dio in sembianze umane.";
			link.l1.go = "WildRose_Chimiset_69";
			AddCharacterExpToSkill(pchar, "Defence", 100);
		break;

		case "WildRose_Chimiset_69":
			dialog.text = "Mi sembra di sentire dell'insoddisfazione nella tua voce, amico mio. Ma no, non mi considero affatto un dio – e credimi, nemmeno lui è onnipotente. Né quello in cui credete voi, né quelli a cui ci rivolgiamo noi. Gli dei non possono dare a un uomo più forza di quella con cui è nato. Noi, sciamani, possiamo solo indirizzarla in una direzione o nell'altra – e niente di più.";
			link.l1 = "E tu li hai indirizzati su una strada che l'ha condannata alla rovina...";
			link.l1.go = "WildRose_Chimiset_70";
		break;

		case "WildRose_Chimiset_70":
			dialog.text = "Ho solo indicato ad Aurélie la strada da seguire, e così facendo ha aiutato Mary — una persona a cui era legata fin dalla nascita. Tua compagna è venuta al mondo sotto i suoi occhi. Ti prego, non guardarmi come se fossi un pazzo. Non vorrai mica dire che mi hai visto come un mago benevolo capace di invertire il corso del tempo con un semplice gesto della mano?";
			link.l1 = "Non so cosa dirti, "+npchar.name+". Forse, tutto questo non è stato davvero vano. Ma non doveva andare così. Dovevi dirmelo, e io avrei dovuto decidere. Però, quello che è fatto è fatto. Beh, addio, amico.";
			link.l1.go = "WildRose_Chimiset_71";
		break;

		case "WildRose_Chimiset_71":
			dialog.text = "Ah, non immaginavo così il nostro ultimo incontro, amico mio...";
			link.l1 = "Come mai pensi che sia l'ultima, giusto?";
			link.l1.go = "WildRose_Chimiset_72";
		break;

		case "WildRose_Chimiset_72":
			dialog.text = "Alcuni fiumi si gettano in altri, diventandone parte, altri si prosciugano, e alcuni – come il nostro – trovano la loro fine in una gigantesca cascata...";
			link.l1 = "Ancora enigmi, Chimiset? Direi che per oggi basta così. Penso che ci rivedremo.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_15");
		break;
		
		case "WildRose_Mary_191":
			dialog.text = "Lo sapevo che ti avrei trovato qui, giusto? Cosa volevi da Chimiset, "+pchar.name+"?   Cosa ti ha detto?";
			link.l1 = "Non è quello che mi aspettavo – o meglio, che volevo – sentire.   Ma qualcosa che in fondo sospettavo, anche se molto vagamente.";
			link.l1.go = "WildRose_Mary_192";
		break;

		case "WildRose_Mary_192":
			dialog.text = "Me lo racconterai, giusto?";
			link.l1 = "No, "+npchar.name+". Questa volta - no. Tutto quello che è stato detto nella cabina del 'Protector' lì resterà, tra me e Chimiset.";
			link.l1.go = "WildRose_Mary_193";
		break;

		case "WildRose_Mary_193":
			dialog.text = "Da tanto non sentivo tanta determinazione nella tua voce, "+pchar.name+". Ma va bene, abbiamo anche altre preoccupazioni, giusto. Il funerale si terrà domani, al tramonto, alle sette.";
			link.l1 = "Andiamo, vi aiuto a preparare tutto.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_17");
		break;
		
		case "WildRose_Mary_201":
			dialog.text = "Sembra che tutti quelli che volevano siano già qui, giusto?";
			link.l1 = "Pensavo che ci sarebbe stata più gente. Almeno tra i pacifici.";
			link.l1.go = "WildRose_Mary_202";
			CharacterTurnToLoc(npchar, "quest", "quest1");
			CharacterTurnToLoc(pchar, "quest", "quest1");
		break;

		case "WildRose_Mary_202":
			dialog.text = "Beh, nessuno ha invitato i Kuranai, né i rivados. Abbott, quel pavone schifoso e arrogante, ha detto che aveva cose più importanti da fare che seppellire una cattolica; qualcosa di simile hanno bofonchiato anche Lauderdale e Musket. Cassel, quel cafone, ha semplicemente detto che non sarebbe venuto. Tutti gli altri sono qui.";
			link.l1 = "Ci sono cose che resteranno sempre al di sopra della mia comprensione. Beh, che sia Dio a giudicarli. Ecco che arriva fratello Julian... Ora tutto avrà inizio.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_18_funeral_2");
		break;

		case "WildRose_funeral_1":
			dialog.text = "Anche se i nostri cuori sono colmi di dolore, rendiamo grazie a Dio per tutti i doni che ha concesso alla defunta Aurélie, e proclamiamo: Ti ringraziamo, Dio, nostro Padre\n"+"Per tutti gli anni e i giorni che Aurélie ha vissuto con noi\n"+"Per il grande dono del santo battesimo, grazie al quale Aurélie è diventata Tua figlia\n"+"Per le capacità e le conoscenze con cui l'hai dotata\n"+"Per il suo servizio al bene della famiglia e degli altri\n"+"Per la sua pazienza verso i nostri errori\n"+"Preghiamo Dio affinché accolga nella Sua gloria la nostra sorella defunta Aurélie e invochiamo: Ti preghiamo, Signore\n"+"Che le buone azioni di Aurélie portino frutti abbondanti\n"+"Che ciò che ha iniziato sia portato avanti\n"+"Perdona i peccati che ha commesso\n"+"Che il ricordo di lei viva nei nostri cuori\n"+"Preghiamo Dio perché rafforzi la fede e la speranza di chi soffre, e rivolgiamoci a Lui: Signore, accresci la nostra fede\n"+"Per mezzo di Tuo Figlio, fatto uomo\n"+"Per mezzo di Tuo Figlio, Gesù Cristo, che ci ha amati infinitamente\n"+"Per mezzo di Tuo Figlio, che ha accettato la morte per i nostri peccati ed è risorto per la nostra salvezza\n"+"Per mezzo di Tuo Figlio, che ci ha aperto la via verso il cielo\n"+"Insieme a tutti i fedeli che ci hanno preceduto nella dimora celeste, preghiamo come ci ha insegnato il Salvatore.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_18_funeral_7");
			
			WildRose_Etap4_PathToLight_18_funeral_6_1();
		break;

		case "WildRose_funeral_2":
			dialog.text = "Dio onnipotente, ascolta le nostre preghiere, innalzate con fede nel Tuo Figlio Risorto, e rafforza la nostra speranza che, insieme alla Tua serva defunta, anche noi saremo degni della resurrezione. Per Cristo nostro Signore, Tuo Figlio, che vive e regna con Te nell'unità dello Spirito Santo, Dio nei secoli dei secoli. Amen.";
			link.l1 = "Dio, Padre Onnipotente, il mistero della croce è la nostra forza, e la Resurrezione di Tuo Figlio è il fondamento della nostra speranza; libera la Tua serva defunta dai vincoli della morte e accoglila tra i salvati. Per Cristo, nostro Signore. Amen.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_18_funeral_8");
			WildRose_Etap4_PathToLight_18_funeral_7_1();
		break;
		
		case "WildRose_funeral_3":
			dialog.text = ""+pchar.name+", entriamo subito in cabina, giusto? Sto per scoppiare a piangere... Non voglio che qualcuno lo veda.";
			link.l1 = "Certo, "+npchar.name+". Andiamo.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_18_funeral_13");
		break;
		
		case "WildRose_Mary_211":
			dialog.text = "Impari davvero ad apprezzare una persona solo dopo la sua morte – hai mai sentito dire una cosa del genere, "+pchar.name+"?";
			link.l1 = "Sì - e non una sola volta, giusto?";
			link.l1.go = "WildRose_Mary_212";
		break;

		case "WildRose_Mary_212":
			dialog.text = "Eric amava ripeterlo. Penso che parlasse della sua famiglia. Non gli ho mai chiesto nulla su di loro – pensavo che ci sarebbe stato tempo, giusto? Poi è morto, giusto. Ora anche Aurélie non c'è più – e solo adesso mi rendo conto di quanto raramente le abbia dedicato tempo e attenzione. Molto meno di quanto meritasse.";
			link.l1 = "Non è colpa tua. Non possiamo sapere quando il Signore ci porterà via le persone care. E il tempo passato con loro non è mai abbastanza. Mai.";
			link.l1.go = "WildRose_Mary_213";
		break;

		case "WildRose_Mary_213":
			dialog.text = "Potrebbe anche essere così, giusto? E poi Eric diceva spesso – e Aurélie era d'accordo con lui – che ogni luogo, prima di tutto, sono le persone. Non le case, gli alberi, le strade – ma le persone. Quando pensi a un punto sulla mappa, la prima cosa che ti viene in mente sono proprio quelli che ci vivono. O che ci vivevano.";
			link.l1 = "Non ci avevo mai pensato. Ma forse Eric aveva ragione – dopotutto, che valore ha una casa, se entrando lì non incontrerai più né tuo padre né tuo fratello?";
			link.l1.go = "WildRose_Mary_214_1";
			link.l2 = "Scommetterei il contrario. Quando penso, per esempio, a Parigi, mi vengono in mente scorci di vicoli, profumi... Delle persone, invece, ne ricordo solo poche – gli altri sono quasi svaniti dalla memoria, anche se sono passati appena pochi anni.";
			link.l2.go = "WildRose_Mary_214_2";
		break;

		case "WildRose_Mary_214_1":
			dialog.text = "Penso che Eric e Aurélie parlassero dell'Isola, giusto? E di quelle persone che vivevano qui – tanto tempo fa. Ero piccola e non capivo, ma ora… ora l'ho capito davvero. Perché qui da più tempo di me ci sono Antonio, Cécile… e alcuni rivados, come Chimiseta – ma con nessuno di loro sono mai stata davvero vicina. Gli altri invece: Eric, Aurélie, Alan e tanti altri, – sono morti.";
			link.l1 = "Capisco. Il mondo è diventato... un po' più piccolo, giusto?";
			link.l1.go = "WildRose_Mary_215";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;

		case "WildRose_Mary_214_2":
			dialog.text = "Penso che Eric e Aurélie parlassero dell'Isola, giusto? E di quella gente che viveva qui – tanto, tanto tempo fa. Ero piccola e non capivo, ma ora… ora l'ho realizzato davvero. Perché solo Antonio, Cécile… e alcuni Rivadòs, come Chimiseta, vivono qui da più tempo di me – ma con nessuno di loro sono mai stata davvero vicina. Gli altri: Eric, Aurélie, Alan e tanti altri, – sono morti.";
			link.l1 = "Capisco. Il mondo è diventato... un po' più piccolo, giusto?";
			link.l1.go = "WildRose_Mary_215";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Mary_215":
			dialog.text = "Piuttosto - si è svuotato. Questo mondo - quello dentro l'anello esterno. Si è svuotato, giusto. E presto - potrebbe anche sparire del tutto.";
			link.l1 = "Di cosa parli, Mary?.";
			link.l1.go = "WildRose_Mary_216";
		break;

		case "WildRose_Mary_216":
			dialog.text = "Non l'hai sentito anche tu, "+pchar.name+"? Ora, mentre stavamo davanti alla tomba di Aurélie.";
			link.l1 = "Cosa esattamente?";
			link.l1.go = "WildRose_Mary_217";
		break;

		case "WildRose_Mary_217":
			dialog.text = "Non so come spiegartelo. Sai che odore ha l'aria prima di un temporale? Ricordi – quando sei arrivato qui per la prima volta, che tensione si sentiva ovunque… Tutti erano pronti a sbranarsi a vicenda, molti sentivano l'odore della polvere da sparo e del sangue. Dopo che hai ucciso Chad, tutto è cambiato – era come se si potesse respirare più facilmente… Ma ora – quella sensazione è tornata di nuovo.";
			link.l1 = "Sì, ho sentito qualcosa di simile. Ma forse è solo l'atmosfera, giusto? Un funerale, dopotutto...";
			link.l1.go = "WildRose_Mary_218_1";
			link.l2 = "Sei esausta, "+npchar.name+". Riposati un po' – ti sentirai meglio. E poi, come si può sentirsi diversamente a un funerale, giusto?";
			link.l2.go = "WildRose_Mary_218_2";
		break;

		case "WildRose_Mary_218_1":
			dialog.text = "Quando abbiamo affidato al mare Erik e tanti altri abitanti dell'Isola, non era così, te lo dico io. Si sentiva una sorta di… unione. Ma oggi – alcuni si guardavano quasi come lupi, anche se recitavano la stessa preghiera.";
			link.l1 = "Parli di Leighton e Donald, giusto?";
			link.l1.go = "WildRose_Mary_219";
			AddCharacterExpToSkill(pchar, "Commerce", 100);
		break;

		case "WildRose_Mary_218_2":
			dialog.text = "Quando abbiamo affidato al mare Erik e tanti altri abitanti dell'Isola, non era così, te lo dico io. Si sentiva una specie di… unione. Ma oggi – alcuni si guardavano quasi come lupi, anche se recitavano la stessa preghiera.";
			link.l1 = "Parli di Leighton e Donald, giusto?";
			link.l1.go = "WildRose_Mary_219";
			AddCharacterExpToSkill(pchar, "Defence", 100);
		break;

		case "WildRose_Mary_219":
			dialog.text = "Quindi anche tu l'hai notato, giusto.";
			link.l1 = "Dexter reagisce nervosamente ai tentativi di Greenspy di organizzare esercitazioni – e come potrebbe essere altrimenti?";
			link.l1.go = "WildRose_Mary_220";
		break;

		case "WildRose_Mary_220":
			dialog.text = "Non finirà bene, giusto.";
			link.l1 = "Se è così, allora oggi si sono celebrate non solo le esequie di Aurélie Bertin, ma anche di questa... City of Abandoned Ships.";
			link.l1.go = "WildRose_Mary_221";
		break;

		case "WildRose_Mary_221":
			dialog.text = "Città delle navi perdute?";
			link.l1 = "Perdonami, Mary, ma proprio non riesco a chiamare questo posto Isola della Giustizia.";
			link.l1.go = "WildRose_Mary_222";
		break;

		case "WildRose_Mary_222":
			dialog.text = "Ora che ho visto il mondo e ho capito quanto sia immenso, questo posto mi sembra... una prigione, giusto. È difficile credere che sia cresciuta qui.";
			link.l1 = "E non riesco a credere che tra questi relitti di navi potesse sbocciare una rosa così selvaggia e splendida come te.";
			link.l1.go = "WildRose_Mary_223";
		break;

		case "WildRose_Mary_223":
			dialog.text = "Voglio dire addio a questo posto, "+pchar.name+"... Forse non torneremo mai più qui, giusto.   Non voglio tornare.   Non voglio vedere con i miei occhi quello che potrebbe succedere qui.";
			link.l1 = "Parlerò con Eddie e Donald. Magari riesco a calmare un po' i loro bollenti spiriti.";
			link.l1.go = "WildRose_Mary_224";
		break;

		case "WildRose_Mary_224":
			dialog.text = "Non capisci... Questo rimanderà solo l'inevitabile, quindi non vale i tuoi sforzi. Verrà il giorno in cui torneremo - e qui\nSarà meglio così, "+pchar.name+", giusto... Qui ormai non mi trattiene più niente.";
			link.l1 = "Come vuoi, cara. Finiremo tutto quello che dobbiamo fare – e poi ce ne andremo via di qui per sempre.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_20");
		break;
		
		// =================================================================
		// ==================== ЭТАП 5. «ЧУЖИМИ РУКАМИ» ====================
		// =================================================================
		case "WildRose_Mary_231":
			dialog.text = "Rupert Casper? Joshua Northwood, giusto?";
			link.l1 = "Ci ho pensato per tutto il viaggio, "+npchar.name+". E sono giunto alla conclusione che tuo padre non avrebbe scelto di nascondersi dietro un nome e un cognome che aveva già usato. Allo stesso tempo, forse non ha avuto il coraggio di rinunciare del tutto a quello vero: cosa sarebbe successo, se in un momento critico non avesse risposto a un nome falso?";
			link.l1.go = "WildRose_Mary_232";
		break;

		case "WildRose_Mary_232":
			dialog.text = "Poteva chiamarsi come voleva, giusto.";
			link.l1 = "Mog, certo. E forse, l'avrei anche fatto. Se è sopravvissuto a Cuba, dove è arrivato su una tartana di contrabbandieri. Se è arrivato, e non è diventato cibo per i granchi dell'Isola della Giustizia. Ora non ci resta che aspettare – per fortuna, non così a lungo come quella volta. Penso che un mese lo supereremo senza problemi.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap5_Fadey_3");
		break;

		case "WildRose_Mary_235":
			dialog.text = "Mio padre è vivo, "+pchar.name+". L'ho sempre saputo, giusto!";
			link.l1 = "Come anch'io, cara. Beh, è ora di andare a trovare quel Jérôme – e anche in fretta, giusto?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap5_Fadey_7");
		break;
		
		// =================================================================
		// ================= ЭТАП 6. «ЖИЗНЬ ПОСЛЕ СМЕРТИ» ==================
		// =================================================================
		case "WildRose_Mary_241":
			dialog.text = "Finalmente siamo arrivati, giusto? E adesso, "+pchar.name+"?";
			link.l1 = "Bisogna trovare Jérôme. O si sta rilassando in una stanza della taverna, oppure ha affittato una casetta – sicuramente ha abbastanza soldi per questo, giusto?";
			link.l1.go = "WildRose_Mary_242";
		break;

		case "WildRose_Mary_242":
			dialog.text = "Considerando quanto gli ha pagato Faddej... Penso che abbia sicuramente preferito la seconda opzione.";
			link.l1 = "D'accordo. Possiamo chiedere di lui al proprietario del 'Vetro di Vetro', oppure fare qualche domanda alla gente del posto. Andiamo, il tempo è prezioso.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_2");
		break;
		
		case "WildRose_BanditBeliz_1":
			dialog.text = "Vediamo un po'... Ecco qui i nostri piccioncini. Dai ragazzi, facciamo quello che dobbiamo – e poi riferiamo a lui.";
			link.l1 = "Jérôme Sauvérnier? Che diamine sta succedendo qui?!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_5");
		break;
		
		case "WildRose_BanditBeliz_2":
			if (!CharacterIsAlive("WildRose_Bandit_1") && !CharacterIsAlive("WildRose_Bandit_2"))
			{
				dialog.text = "Ah, bastardi, khè-khè. Ma non importa...";
				link.l1 = "Ti consiglio di tenere la lingua a freno, se ci tieni alla tua pelle... ";
				link.l1.go = "WildRose_BanditBeliz_2_1";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "...";
				link.l1 = "...";
				link.l1.go = "exit";
			}
		break;
		
		case "WildRose_BanditBeliz_2_1":
			dialog.text = "...";
			link.l1 = "Anche quello. E ora parla: perché diavolo ci avete assaliti – e pure insieme a Sovereignet...";
			link.l1.go = "WildRose_BanditBeliz_3";
		break;

		case "WildRose_BanditBeliz_3":
			dialog.text = "Il vostro Sovereign è un bastardo avido e codardo. Bastava che Casper gli desse una bella lezione, e poi gli promettesse qualche moneta – ed eccolo lì, subito a scrivere quella letterina, giusto... khaa-khaa...";
			link.l1 = "Quindi, l'ha davvero trovato.";
			link.l1.go = "WildRose_BanditBeliz_4";
		break;

		case "WildRose_BanditBeliz_4":
			dialog.text = "Ho trovato, ho trovato. Quindi morirai presto. Proprio come la tua amichetta. Casper vi farà a pezzi tutti e due, eh eh. Io ormai sono spacciato, ma ti aiuterò a trovare la tua fine. Peccato che non sentirò le vostre suppliche quando sarete nelle sue mani...";
			link.l1 = "Sì, non mi resta molto, giusto? Quindi parla più in fretta, prima che esali l'ultimo respiro.";
			link.l1.go = "WildRose_BanditBeliz_6";
		break;

		case "WildRose_BanditBeliz_6":
			dialog.text = "Se volete incontrarlo, andate alla baia di Chetumal, è lì che si aggira. Non dovrete nemmeno cercarlo, sarà lui a trovare voi.";
			link.l1 = "E allora va bene. Ora puoi morire quanto ti pare. Io invece devo andare.";
			link.l1.go = "WildRose_BanditBeliz_Just_Deth";
			link.l2 = "Spero proprio di sì.   E ora vai all'inferno.";
			link.l2.go = "WildRose_BanditBeliz_Hit_Deth";
		break;
		
		case "WildRose_BanditBeliz_Just_Deth":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_8");
		break;
		
		case "WildRose_BanditBeliz_Hit_Deth":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_7");
		break;
		
		case "WildRose_Mary_251":
			dialog.text = "Dio, "+pchar.name+"... Non ci posso credere, proprio non ci riesco, giusto! È stato mio padre a fare tutto questo?!";
			link.l1 = "A quanto pare, giusto? "+npchar.name+". Non so proprio cosa li abbia spinti e chi sia lui, accidenti... Ma difficilmente si tratta di un altro Rupert Casper. Coincidenze del genere non esistono.";
			link.l1.go = "WildRose_Mary_252";
		break;

		case "WildRose_Mary_252":
			dialog.text = "E ora che facciamo?   Cosa gli dirò, guardandolo negli occhi?";
			link.l1 = "Prima di tutto, dobbiamo raggiungerlo. Probabilmente si è messo fuori legge, visto che la sua ricerca ha causato... una reazione così nervosa. Ma, in ogni caso, resta tuo padre. Per trovarlo abbiamo speso un sacco di energie, tempo e denaro.";
			link.l1.go = "WildRose_Mary_253";
		break;

		case "WildRose_Mary_253":
			dialog.text = "Ma cosa succede se non vorrà nemmeno parlare con noi? Perché ha ordinato di ucciderci?";
			link.l1 = "Almeno perché poteva anche non sapere chi esattamente lo stesse cercando. Faddej poteva semplicemente dire un nome e tralasciare i dettagli su di te. Altrimenti, credo che ora non ci sarebbe toccato sporcare le lame di sangue.";
			link.l1.go = "WildRose_Mary_254";
		break;

		case "WildRose_Mary_254":
			dialog.text = "E adesso? Andiamo alla baia di Chetumal? Ma se ci ha teso una trappola qui... chissà cosa ci aspetta là?";
			link.l1 = "Abbiamo un vantaggio di tempo, finché lui non scopre cosa è successo qui. Approfittiamone. Andremo alla baia in nave, e per aiutarci manderemo una squadra via terra guidata da uno degli ufficiali.";
			link.l1.go = "WildRose_Mary_255";
		break;

		case "WildRose_Mary_255":
			dialog.text = "Sembra ragionevole, giusto? Ma chi lo guiderà?";
			if (CheckPassengerInCharacter(pchar, "Tichingitu"))
			{
				link.l1 = "Tichingitu. In battaglia sulla terraferma è temprato. Nessuno se la cava meglio di lui.";
				link.l1.go = "WildRose_Etap6_Tichingitu";
			}
			if (CheckPassengerInCharacter(pchar, "Duran"))
			{
				link.l2 = "Claude. Certo, non ne sarà entusiasta, ma pazienza – sopravviverà.";
				link.l2.go = "WildRose_Etap6_Duran";
			}
			if (CheckPassengerInCharacter(pchar, "Tonzag"))
			{
				link.l3 = "Hercule. Lui sì che sa come si fanno queste cose.";
				link.l3.go = "WildRose_Etap6_Tonzag";
			}
			if (CheckPassengerInCharacter(pchar, "Irons"))
			{
				link.l4 = "Tommy. Anche se qualcosa dovesse andare storto, quel ragazzo saprà cavarsela, fidati.";
				link.l4.go = "WildRose_Etap6_Irons";
			}
			if (CheckPassengerInCharacter(pchar, "Longway"))
			{
				link.l5 = "Longway. Non è la prima volta che dà la caccia a un nemico nella selva.";
				link.l5.go = "WildRose_Etap6_Longway";
			}
			if (!CheckPassengerInCharacter(pchar, "Tichingitu") && !CheckPassengerInCharacter(pchar, "Duran") && !CheckPassengerInCharacter(pchar, "Tonzag") && !CheckPassengerInCharacter(pchar, "Irons") && !CheckPassengerInCharacter(pchar, "Longway"))
			{
				link.l99 = "Alonso. Sa con la spada ci sa fare, e non gli manca certo l'ingegno, giusto?";
				link.l99.go = "WildRose_Etap6_Alonso";
			}
		break;
		
		case "WildRose_Etap6_Tichingitu":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Tichingitu");
		break;
		
		case "WildRose_Etap6_Duran":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Duran");
		break;
		
		case "WildRose_Etap6_Tonzag":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Tonzag");
		break;
		
		case "WildRose_Etap6_Irons":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Irons");
		break;
		
		case "WildRose_Etap6_Longway":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Longway");
		break;
		
		case "WildRose_Etap6_Alonso":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Alonso");
		break;
		
		//
		case "WildRose_Tichingitu_1":
			dialog.text = "Ascoltare attentamente Tichingitu, capitano "+pchar.name+".";
			link.l1 = "Amico mio, ti aspetta un compito importante. Nella baia di Chetumal si è nascosta una banda di furfanti. Devi trovarli e distruggerli. Arriveremo con la nostra nave dal mare.";
			link.l1.go = "WildRose_Tichingitu_2";
		break;

		case "WildRose_Tichingitu_2":
			dialog.text = "";
			link.l1 = "Tu guiderai la nostra squadra attraverso la selva, per prendere quei bastardi alle spalle. Hai domande da farmi?";
			link.l1.go = "WildRose_Tichingitu_3";
		break;

		case "WildRose_Tichingitu_3":
			dialog.text = "Gli indiani non hanno domande. Domani a mezzogiorno la squadra sarà sul posto e attenderà lì in agguato.";
			link.l1 = "Molto bene, Tichingitu. Buona fortuna.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Duran_1":
			dialog.text = "Mi hai chiamato, capo?";
			link.l1 = "Ho un lavoretto per te, Claude.";
			link.l1.go = "WildRose_Duran_2";
		break;

		case "WildRose_Duran_2":
			dialog.text = "";
			link.l1 = "Bisogna radunare una squadra di combattenti e guidarla attraverso la giungla fino alla baia di Chetumal. Lì ci aspetta la banda di un certo Rupert Casper. Vogliono farci una brutta sorpresa. Ma in realtà saremo noi a sorprenderli, anzi, sarai tu. Li attaccherai al mio segnale. Domande?";
			link.l1.go = "WildRose_Duran_3";
		break;

		case "WildRose_Duran_3":
			dialog.text = "Odio andare in giro per la giungla. Ma, come si dice, un ordine è un ordine. Ci vediamo sul posto, penso, domani verso mezzogiorno.";
			link.l1 = "In bocca al lupo, Claude.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Tonzag_1":
			dialog.text = "Ti ascolto, capo.";
			link.l1 = "Ercole, c'è un lavoro per te.";
			link.l1.go = "WildRose_Tonzag_2";
		break;

		case "WildRose_Tonzag_2":
			dialog.text = "Hai bisogno che qualcuno si prenda un paio di pallottole in quella testolina matta? Sono sempre pronta, lo sai.";
			link.l1 = "Hai quasi indovinato. Devi guidare una squadra di combattenti della nostra nave, portarli attraverso la giungla fino alla baia di Chetumal. Lì tenderete un'imboscata alla banda che, secondo me, ci aspetterà proprio lì.";
			link.l1.go = "WildRose_Tonzag_3";
		break;

		case "WildRose_Tonzag_3":
			dialog.text = "Pensavo che parlassi di qualcosa di serio, capo. Invece quasi quasi stai parlando di andare in taverna. Domani a mezzogiorno, considera che saremo già lì.";
			link.l1 = "Ci vediamo direttamente lì. Buona fortuna, Hercule.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Irons_1":
			dialog.text = "Ah, capitano, ma perché sei così serio – sembri pronto per un funerale, giusto?";
			link.l1 = "Scherzi ancora, Tommy? Vuoi che scherzi anch'io? Lo stipendio di questo mese non lo vedrai. E nemmeno quello del prossimo. Perché ti sei irrigidito così?";
			link.l1.go = "WildRose_Irons_2";
		break;

		case "WildRose_Irons_2":
			dialog.text = "E non si può nemmeno scherzare...";
			link.l1 = "A tutto c'è il suo tempo, Tommy. Questo dovrai ancora impararlo bene. Ora ascoltami attentamente: raduna la tua squadra e muovetevi attraverso la selva verso la baia di Chetumal. Quando arrivate, aspettate il mio segnale.";
			link.l1.go = "WildRose_Irons_3";
		break;

		case "WildRose_Irons_3":
			dialog.text = "Attraversare la selva? Ma ci arriveremo non prima di domani a mezzogiorno.";
			link.l1 = "Allora, ci vediamo lì domani a mezzogiorno. Senza ordine, niente combattimento, e non lasciare la posizione. Chiaro? Vedo che è chiaro. E ora, al lavoro.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Longway_1":
			dialog.text = "Longway ascolta voi, signor capitano.";
			link.l1 = "Amico, ho un compito per te.";
			link.l1.go = "WildRose_Longway_2";
		break;

		case "WildRose_Longway_2":
			dialog.text = "...";
			link.l1 = "Devi guidare la nostra squadra di uomini che attraverserà la giungla fino alla baia di Chetumal. Lì potrebbe esserci uno scontro con il nemico, quindi prepara bene i tuoi uomini.";
			link.l1.go = "WildRose_Longway_3";
		break;

		case "WildRose_Longway_3":
			dialog.text = "Longway capirà tutto, non si preoccupi, signor capitano. Arriveremo sul posto domani verso mezzogiorno.";
			link.l1 = "Vai e fai attenzione.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Alonso_1":
			dialog.text = "Mi hai chiamato, capitano?";
			link.l1 = "Sì. Ascolta bene, Alonso.";
			link.l1.go = "WildRose_Alonso_2";
		break;
		
		case "WildRose_Alonso_2":
			dialog.text = "";
			link.l1 = "A capo di una squadra di combattenti dovrai attraversare la giungla e raggiungere la baia di Chetumal. Lì, molto probabilmente, ti aspetterà una banda di furfanti. Dovrai prendere posizione e attaccarli alle spalle al mio segnale.";
			link.l1.go = "WildRose_Alonso_3";
		break;

		case "WildRose_Alonso_3":
			dialog.text = "Una sciocchezza, capitano. Ma non sbarcate nella baia prima di domani a mezzogiorno — io e i ragazzi non riusciremo ad arrivarci prima.";
			link.l1 = "Preparati come si deve, Alonso. E che Dio ci aiuti.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Mary_256":
			dialog.text = "Charles, hai visto, giusto?";
			link.l1 = "Sembra che ci stiano già aspettando. Di sicuro sono appostati dietro quell'angolo.";
			link.l1.go = "WildRose_Mary_257";
		break;

		case "WildRose_Mary_257":
			dialog.text = "Tuttavia, non ci hanno ancora ridotto a un colabrodo. E nemmeno ci stanno provando, giusto?";
			link.l1 = "Forse, all'inizio, è ancora disposto a parlare con noi. Non provochiamolo - andiamo là noi stessi, la nostra squadra ci coprirà. Andiamo, mettiamo fine a tutto questo.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_18_1");
		break;
		
		case "WildRose_Rupert_1":
			dialog.text = "Fermi! Non un passo di più! Ragazzi, se quel damerino si muove, riempitelo di buchi. La ragazza non toccatela.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_1_add";
			// link.l1.go = "WildRose_Rupert_87";
		break;

		case "WildRose_Rupert_1_add":
			StartInstantDialog("Mary", "WildRose_Rupert_2", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_2":
			dialog.text = "Papà?..";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_2_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_2_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_3", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_3":
			sld = CharacterFromID("Mary");
			if (CheckCharacterItem(sld, "hat11")) // У Мэри есть своя шляпа
			{
				dialog.text = "Eh già, ne ho viste tante nella mia lunga e difficile vita. Ogni volta penso che ormai niente possa sorprendermi più – e ogni volta mi sbaglio. Quindi sei riuscita a sopravvivere là... E hai persino conservato il cappello di Teresa. Non pensavo proprio che l'avrei mai più rivisto.";
				link.l1 = "...";
				link.l1.go = "WildRose_Rupert_3_1_add";
			}
			else
			{
				dialog.text = "Sai, ne ho viste tante nella mia lunga e difficile vita. Ogni volta penso che ormai niente possa più sorprendermi – e ogni volta mi sbaglio. Quindi sei sopravvissuta laggiù, Julia...";
				link.l1 = "...";
				link.l1.go = "WildRose_Rupert_3_add";
			}
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_3_1_add":
			StartInstantDialog("Mary", "WildRose_Rupert_3_2", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Rupert_3_2":
			dialog.text = "Me l'ha consegnato Aurélie, prima della sua... dipartita.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_3_2_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_3_2_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_3_3", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_3_3":
			dialog.text = "Che commovente... Sto quasi per piangere. E pensare che credevo che Teresa fosse stata seppellita con lei. Non se ne separava mai, dal giorno in cui gliel'ho regalata. Tua madre, pur essendo solo una cameriera, aveva uno spirito d'avventura che quasi le usciva dalle orecchie. Quando la trovai durante la presa del 'Fleur-de-Lys', capii subito che Teresa ne sarebbe andata matta. Le stava in modo buffo, ma non le importava: si toglieva quel cappello solo per dormire. Ma a te, Julia, sta proprio bene.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_3_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_3_add":
			StartInstantDialog("Mary", "WildRose_Rupert_4", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_4":
			dialog.text = "Giulia? No, vi sbagliate, mi chiamo Mary...";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_4_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_4_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_5", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_5":
			dialog.text = "Hmm, quindi è così. Quindi quei bastardi hanno ignorato le mie parole e hanno deciso di agire da soli. Beh, da quei cani cattolici non ci si poteva aspettare altro, giusto?";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_5_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_5_add":
			StartInstantDialog("Mary", "WildRose_Rupert_6", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_6":
			dialog.text = "Tu... Tu... Sei davvero mio padre?";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_6_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_6_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_7", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_7":
			dialog.text = "Beh, se non fosse così, tu e il tuo amichetto sareste già stesi a terra, crivellati di piombo. È da un pezzo che non credo più né in Dio né nel Diavolo, ma forse esistono davvero. Il primo di sicuro – visto che ti ha dato l'aspetto di Teresa. E con questo ti ha appena salvato la vita. Come si dice: le vie del Signore sono infinite, giusto? Ah-ah-ah!";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_7_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_7_add":
			StartInstantDialog("Mary", "WildRose_Rupert_8", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_8":
			dialog.text = "Papà... Io... io non capisco, giusto...";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_8_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_8_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_9", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_9":
			dialog.text = "Ma figurati se puoi capire, giusto...";
			link.l1 = "Non sembra proprio che siate felice di vedere vostra figlia, signor Casper. Tanto più che l'avete riconosciuta voi stesso.";
			link.l1.go = "WildRose_Rupert_10";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_10":
			dialog.text = "Di ingegno non te ne manca, ragazzino... Come ti chiami, eh?";
			link.l1 = ""+GetFullName(pchar)+".   Mentre vi cercavamo, ci chiedevamo sempre come aveste vissuto tutto questo tempo. Se foste sopravvissuto, poi.   Ma vedo che qui vi siete sistemato piuttosto bene, signor... Northwood.";
			link.l1.go = "WildRose_Rupert_11";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), pchar);
		break;

		case "WildRose_Rupert_11":
			dialog.text = "Ah-ah, quindi siete arrivati perfino a questo. Beh, tanto di cappello, monsieur ranocchio, che altro posso dire — considerando che avevo fatto in modo di tagliare tutti i ponti.";
			link.l1 = "Non solo a questo. Sappiamo anche della 'Cornwall', del suo carico, e di Joshua Kasper, il cui nome avete preso in prestito per un po', e il cognome — a quanto pare — per sempre.";
			link.l1.go = "WildRose_Rupert_12";
		break;

		case "WildRose_Rupert_12":
			dialog.text = "Bravo (applaude). Sono impressionato. Ci sei arrivato da solo, o anche il mio adorato pargolo ci ha messo lo zampino?";
			link.l1 = "Senza Mary non ce l'avrei mai fatta. Lei voleva davvero sapere tutto sui suoi genitori. Scoprire il destino di Teresa non è stato difficile, ma invece sulle vostre tracce abbiamo dovuto camminare a lungo...";
			link.l1.go = "WildRose_Rupert_13";
		break;
		
		case "WildRose_Rupert_13":
			dialog.text = "È tutto così tenero che mi viene quasi da piangere. Allora, figliola, sei soddisfatta? Contenta? Vuoi abbracciare il tuo papino?";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_13_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_13_add":
			StartInstantDialog("Mary", "WildRose_Rupert_14", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_14":
			dialog.text = "Non capisco, padre...   Perché ti prendi gioco di me?   Perché?!   (grida)   Sei stato tu a lasciarmi lì, su quei relitti di navi!   E poi non ti sei nemmeno degnato di tornare, giusto?   Perché?   Chi sei davvero, chi sono queste persone dietro di te?";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_14_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_14_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_15", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_15":
			dialog.text = "Dimmi, "+pchar.lastname+", fa spesso così tante scenate? L'ha preso da sua madre. Teresa era una ragazza meravigliosa, la migliore che abbia mai conosciuto. Ma piangere e fare scenate le piaceva, questo sì... Che dire... irlandese.";
			link.l1 = "Non osate insultarla! Mary non ha colpa delle vostre disgrazie e di certo non merita un trattamento simile.";
			link.l1.go = "WildRose_Rupert_16";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), pchar);
		break;
		
		case "WildRose_Rupert_16":
			dialog.text = "Hai deciso di tappami la bocca, cucciolo?!";
			link.l1 = "Al contrario. Voglio che ci raccontiate la vostra storia. Per Mary è molto importante saperlo. Ma non vi permetterò di umiliarla. Quindi mantenete il controllo, d'accordo?";
			link.l1.go = "WildRose_Rupert_17";
		break;
		
		case "WildRose_Rupert_17":
			dialog.text = "Pensi che io abbia davvero voglia di piangermi addosso davanti a voi? La mia vita è andata come è andata, e, come dite voi papisti – che Dio mi sia testimone – non mi pento di nulla. A parte il fatto che ho perso Teresa allora – per colpa sua. Ti odio, figlia mia? Forse un tempo era così, ma adesso non me ne importa proprio niente di te.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_17_add";
		break;

		case "WildRose_Rupert_17_add":
			StartInstantDialog("Mary", "WildRose_Rupert_18", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_18":
			dialog.text = "Mi incolpi per la morte di mamma?! Tu... In cosa sarei colpevole: di essere nata, giusto? Va bene, papà, "+pchar.name+", hai ragione - raccontaci tutto, poi ce ne andremo. E io non mi farò mai più vedere da te, visto che tu... (inizia a piangere).";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_18_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_18_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_19", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_19":
			dialog.text = "Ahhh, proprio come Teresa. È come se fossi tornato indietro di vent'anni, ah-ah. Al diavolo. Non avevo intenzione di ricordare tutto questo... Quindi, se alla fine di questa storiella decido di piantarti un proiettile in fronte, dolcezza — sarà solo colpa tua.";
			link.l1 = "Allora anche voi vi prenderete una pallottola, Rupert. Ma mi sembra che questo non rientri nei vostri piani – dopotutto, avete l'aria di uno che ci tiene alla propria vita.";
			link.l1.go = "WildRose_Rupert_20";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_20": //
			dialog.text = "So quanto vale, ragazzo. È diverso. Ma che ne può sapere uno come te? Va bene, andiamo al sodo. Volete sapere tutto su di me? E sia. Sono nato in una fattoria, vicino a Eastbourne — una cittadina sulla costa della Manica — nel 1611. Forse un anno prima o dopo — mia madre confondeva sempre le date, il che non sorprende, considerando quanto alcol si versava in corpo.";
			link.l1 = "Un'infanzia difficile? Capisco.";
			link.l1.go = "WildRose_Rupert_21";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), pchar);
		break;

		case "WildRose_Rupert_21":
			dialog.text = "Hai voluto ascoltare — allora ascolta in silenzio, senza battute. Mio padre non c'era, e non ho mai saputo il perché — ma, a differenza tua, figliola, non me ne importava. Il cognome che mi ha lasciato mi andava benissimo. Quando avevo tredici anni, una notte sbarcarono sulla costa dei corsari di Dunkerque. Sì, oggi non piace ricordarlo, ma non colpivano solo gli olandesi — anche noi, quelli che vivevano sulla costa orientale della vecchia Inghilterra, ci rimettevamo.";
			link.l1 = "Ne ho sentito parlare. Quei tipi non risparmiavano nessuno.   Come avete fatto a sopravvivere?";
			link.l1.go = "WildRose_Rupert_22_1";
			link.l2 = "So delle loro atrocità. Non hanno avuto pietà di nessuno – né dei vecchi, né dei bambini. È ancora più sorprendente che tu sia riuscito a uscirne, giusto?";
			link.l2.go = "WildRose_Rupert_22_2";
		break;

		case "WildRose_Rupert_22_1":
			dialog.text = "Quella notte quella feccia papista ha dato fuoco a diverse fattorie, compresa la nostra. Io sono riuscito a scappare, ma mia madre, che si era ingozzata di sidro al punto da non riuscire a sollevare il suo grosso sedere dal letto, è bruciata viva proprio lì. È stata colpa sua, certo – ma era pur sempre mia madre.";
			link.l1 = "E allora avete cominciato a odiare tutti i papisti?";
			link.l1.go = "WildRose_Rupert_23";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Rupert_22_2":
			dialog.text = "Quella notte quella feccia papista ha dato fuoco a diverse fattorie, compresa la nostra. Io sono riuscito a scappare, ma mia madre, che si era ingozzata di sidro al punto da non riuscire a staccare il suo grosso sedere dal letto, è bruciata lì dentro. È stata colpa sua, certo – ma era pur sempre mia madre.";
			link.l1 = "E allora avete cominciato a odiare tutti i papisti?";
			link.l1.go = "WildRose_Rupert_23";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Rupert_23":
			dialog.text = "Fu allora che cominciai a odiare la fame, spiritoso. Tu, ovviamente, non sai nemmeno cosa sia, ma io l'ho conosciuta sulla mia pelle. Me ne andai a nord, nella capitale, dove mi arruolai nella marina — lì ti davano più frustate che cibo, ma una ventina mi bastò per rimettermi in riga, e poi ci presi gusto — arrivai ad amare la vita di bordo. Anche perché non c'era modo di annoiarsi...";
			link.l1 = "Eh già, ci credo volentieri. La fama della flotta inglese la precede.";
			link.l1.go = "WildRose_Rupert_24";
		break;

		case "WildRose_Rupert_24":
			dialog.text = "Nel 1633 ho superato l'esame per il grado di tenente e ho ricevuto l'assegnazione alla brigantina 'Cornwall'.";
			link.l1 = "Sotto il comando di Joshua Casper.";
			link.l1.go = "WildRose_Rupert_26";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Rupert_26":
			dialog.text = "O-oh sììì. Joshua Casper... Una carogna così non la troveresti neanche a cercarla con la lanterna in tutta la dannata flotta, giusto? Sono passati tanti anni, eppure quel bastardo ancora mi viene a trovare nei sogni.";
			link.l1 = "In che cosa si è distinto? Ti metteva di turno extra - per troppo zelo? O forse in segreto era un papista?";
			link.l1.go = "WildRose_Rupert_27";
		break;

		case "WildRose_Rupert_27":
			dialog.text = "Quel bastardo crudele addestrava l'equipaggio a tal punto che la gente crollava in mare dalla stanchezza. Se conosci il suo nome e sai che era il comandante della 'Cornwall', avrai sicuramente visto i suoi documenti — lucidi come il didietro leccato di un gatto\nIl nostro eroico Joshua aveva una scatola piena di medaglie. Tanti ragazzini ingenui come te volevano servire sotto il suo comando — in fondo, diciamolo, falciava voi ranocchi come una falce affilata falcia l'erba bagnata dalla pioggia — ma una volta saliti a bordo della 'Cornwall', capivano in fretta il loro errore\nEravamo stanchi morti di sopportarlo, "+pchar.lastname+". Qualcuno aveva persino scritto delle richieste di trasferimento – ma finivano perse sugli scaffali dell'Ammiragliato o bruciate nei suoi forni. Però la vita ci ha comunque dato una possibilità – non hanno trasferito noi dalla 'Cornwall', ma qualcun altro… a bordo. John Lawson – il cocco di Cromwell, sicuramente ne hai sentito parlare, giusto?";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_28";
		break;

		case "WildRose_Rupert_28":
			dialog.text = "Già allora sapeva come leccare i culi – e forse lui e Kasper avrebbero anche fatto comunella, ma non gliel'ho lasciato fare. Ho incastrato il piccolo Johnny, e Joshua, che non aveva capito la situazione, l'ha riempito di botte dalla rabbia.";
			link.l1 = "Una vera umiliazione per un ufficiale.   E Lawson ha raccontato tutto a mio padre?";
			link.l1.go = "WildRose_Rupert_32";
		break;

		case "WildRose_Rupert_32":
			dialog.text = "Eccome. Ma vedi, il sistema non può divorare sé stesso. La cosa non è mai venuta alla luce — a Lawson offrirono una promozione anticipata, mentre Joshua e la 'Cornwall' furono messi da parte — da Londra ci trasferirono a Plymouth, nel sud dell'Inghilterra. Avremmo potuto continuare a terrorizzare voi mangiarane, ma la 'Cornwall' fu trasformata in una nave da carico militare per il trasporto merci a Dundalk, una cittadina irlandese.";
			link.l1 = "Ed è lì che hai incontrato Teresa?";
			link.l1.go = "WildRose_Rupert_33";
		break;

		case "WildRose_Rupert_33":
			dialog.text = "Al nostro primo scalo lì. Teresa O'Fatt, come ho già detto, era una cameriera in una delle taverne del posto. Ci sono bastati tre giorni per capire che eravamo fatti l'uno per l'altra. Penso che anche tu possa capirmi, "+pchar.lastname+", giusto?";
			link.l1 = "Direi di sì.";
			link.l1.go = "WildRose_Rupert_34_1";
			link.l2 = "Guardandovi adesso, non si direbbe che conoscete la parola 'amore'.";
			link.l2.go = "WildRose_Rupert_34_2";
		break;

		case "WildRose_Rupert_34_1":
			dialog.text = "Non ho mai incontrato nessuno più meraviglioso – né prima, né nei vent'anni successivi. Forse, per la prima volta nella mia vita, mi sono sentito davvero felice, e anche lei – o almeno così diceva.";
			link.l1 = "E le avete proposto di partire con voi?";
			link.l1.go = "WildRose_Rupert_35";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

		case "WildRose_Rupert_34_2":
			dialog.text = "Non ho mai incontrato nessuno più meraviglioso – né prima, né in tutti i vent'anni successivi. Forse, per la prima volta nella mia vita, mi sono sentito davvero felice, e anche lei – almeno così diceva.";
			link.l1 = "E le avete proposto di venire via con voi?";
			link.l1.go = "WildRose_Rupert_35";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Rupert_35":
			dialog.text = "Certo che no – era impossibile, la 'Cornwall' restava una nave militare con quel bastardo di capitano al comando. Dopo una settimana che ci era sembrata un'eternità, il nostro brigantino fece ritorno a Plymouth. Siamo tornati a Dundalk due mesi dopo – e Teresa mi ha sconvolto con la notizia: era incinta.";
			link.l1 = "Sì, succede quando metti una ragazza a letto, giusto?";
			link.l1.go = "WildRose_Rupert_36";
		break;

		case "WildRose_Rupert_36":
			dialog.text = "Non fare lo spiritoso, ranocchio. Teresa piangeva sulla mia spalla, e io pensavo a cosa fare. Volevo restare con lei, lo volevo davvero – ma già allora sentivo che da quella bambina non sarebbe venuto nulla di buono\nHo cercato di convincere Teresa a liberarsene, finché non era troppo tardi – ma invece mi sono beccato una crisi ancora più furiosa. Non sapevamo cosa fare, così abbiamo deciso di aspettare ancora due mesi, fino al prossimo ritorno del 'Cornwall' a Dundalk, perché all'epoca l'Ammiragliato non aveva ancora cambiato la sua rabbia verso Casper in clemenza\nDopo il nostro ritorno non la trovai subito — la gravidanza di Teresa era ormai evidente, e, come mi disse il locandiere dove lavorava, quel bastardo di suo padre l’aveva percossa e rinchiusa in casa. Non c’è bisogno di dire che ho trattato quel bastardo in modo tale che quasi vomitasse le proprie viscere. Ovviamente, era fuori discussione che potesse continuare a vivere in quella casa.";
			link.l1 = "E l'avete portata sulla 'Cornwall'?";
			link.l1.go = "WildRose_Rupert_37";
		break;

		case "WildRose_Rupert_37":
			dialog.text = "La decisione doveva essere presa in fretta. Capivo che Casper non avrebbe tollerato una donna a bordo, e avevo intenzione, la notte dopo la partenza, di rubare una scialuppa e raggiungere Dublino, che sarebbe stato proprio a dritta.";
			link.l1 = "E cosa è successo? Vi hanno catturato?";
			link.l1.go = "WildRose_Rupert_38";
		break;

		case "WildRose_Rupert_38":
			dialog.text = "Esattamente. Casper aveva già buttato giù una dose di whisky, quindi era sordo a qualsiasi supplica e ordinò semplicemente di gettare la ragazza fuori bordo. A tutte le mie preghiere rideva fino alle lacrime – maledizione, lo sto raccontando e nella mia testa risuona ancora la sua risata...";
			link.l1 = "E allora avete deciso di fare ammutinamento?";
			link.l1.go = "WildRose_Rupert_39";
		break;

		case "WildRose_Rupert_39":
			dialog.text = "Non avevo altra scelta. Ho afferrato la pistola dalla cintura del nostromo accanto a me e ho fatto un buco in fronte a quel bastardo. A bordo è subito iniziata una carneficina — nessuno amava il capitano, ma la paura della corte marziale era più forte. È costata la vita a quasi un terzo dell’equipaggio — quando ci siamo finalmente ripresi, tutto il ponte della ‘Cornwall’ era coperto di sangue e disseminato dei corpi dei nostri compagni morti.";
			link.l1 = "Dopo tutto questo, naturalmente avete deciso di non tornare in Inghilterra. Lì vi avrebbe aspettato il cappio.";
			link.l1.go = "WildRose_Rupert_40";
		break;
		
		case "WildRose_Rupert_40":
			dialog.text = "Ero certo che avrei condotto la 'Cornwell' attraverso l’oceano. Qui i nostri volti non erano noti a nessuno, e questo ci dava la possibilità di iniziare una nuova vita. Convincere gli altri ufficiali non fu difficile — contò meno la mia autorità e più il contenuto di alcune casse, di cui i marinai ordinari non erano a conoscenza. L’equipaggio decise che Joshua Kasper doveva vivere. Noi, gli ufficiali montani, decidemmo di guadagnare tempo, sacrificare una delle casse e attraccare ad Antigua, dove avrei assunto il suo nome. Dopodiché, avremmo preso rotta su Providence.\n E così fu: nessuno sospettò lo scambio. Ma quando mancavano solo pochi giorni a Providence, qualche bastardo fece trapelare la seconda cassa — e questo provocò una spaccatura nell’equipaggio.";
			link.l1 = "Ora hanno sollevato una ribellione contro di te?";
			link.l1.go = "WildRose_Rupert_45";
		break;

		case "WildRose_Rupert_45":
			dialog.text = "No, ma il numero di quelli che volevano continuare a servire il nostro glorioso re è diminuito drasticamente. Anche tra chi era pronto a diventare pirata, non erano poi tanti. Così abbiamo trovato una via di mezzo: abbiamo deciso di gettare l'ancora in uno dei porti francesi. Lì avevamo intenzione di vendere la nave, dividere i soldi ricavati dalla vendita e quelli che erano nel forziere, e poi ognuno per la sua strada.";
			link.l1 = "E non vi importava dover vivere tra quei cattolici che tanto detestate, giusto?";
			link.l1.go = "WildRose_Rupert_46";
		break;

		case "WildRose_Rupert_46":
			dialog.text = "A quel punto non mi importava più dove sbarcare: Teresa, anche se faceva la forte, si sentiva esattamente come qualsiasi donna incinta dopo tre mesi di mare ininterrotto. E, come tre mesi prima, non avevo nulla contro la compagnia dei cattolici — purché potessi restare accanto a lei.";
			link.l1 = "Ma nel nord-ovest dei Caraibi non ci sono e non ci sono mai stati insediamenti francesi.";
			link.l1.go = "WildRose_Rupert_47";
		break;

		case "WildRose_Rupert_47":
			dialog.text = "Quando la situazione a bordo del 'Cornovaglia' è arrivata al punto di ebollizione, avevamo già percorso metà del viaggio con il vento in poppa, che ormai non ci permetteva più di fare rotta su Saint-Christophe...";
			link.l1 = "E avete scelto Tortuga come destinazione?";
			link.l1.go = "WildRose_Rupert_48";
		break;

		case "WildRose_Rupert_48":
			dialog.text = "In quegli anni era ancora un semplice villaggio. Per ritardare un possibile inseguimento da parte delle autorità, abbiamo cambiato la targa di poppa con il nome del brigantino - così il 'Cornwall' è diventato il 'Wrangler'.";
			link.l1 = "Ma per qualche motivo non siete mai arrivati a Tartaruga. Non potevate aver sbagliato così tanto la rotta da finire a ovest di Cuba invece che a Tortuga, giusto?";
			link.l1.go = "WildRose_Rupert_49";
		break;

		case "WildRose_Rupert_49":
			dialog.text = "Io, giusto per farti sapere, sono una navigatrice esperta – non come tanti altri. Non c'è stato nessun errore, tenevamo la rotta dritta verso nord. Ma appena siamo entrati nello Stretto Sopravento, si è scatenata una tempesta terribile. Ancora mi chiedo per quale miracolo non ci siamo schiantati contro la costa cubana, ma invece siamo stati trascinati lungo di essa…";
			link.l1 = "Un vero miracolo – non c'è altra spiegazione.";
			link.l1.go = "WildRose_Rupert_50";
		break;

		case "WildRose_Rupert_50":
			dialog.text = "Stringendo a sé Teresa in lacrime, pregava il Signore con tutto il cuore, implorando che ci mandasse la salvezza. E Lui ci ha aiutato, eccome se ci ha aiutato.";
			link.l1 = "Siete stati portati sull'Isola della Giustizia.";
			link.l1.go = "WildRose_Rupert_51";
		break;

		case "WildRose_Rupert_51":
			dialog.text = "Giustizia — oh sì! All’impatto contro gli scogli, la ‘Wrangler’ si spezzò in due, ma in modo sorprendente rimase a galla — abbastanza da essere spinta fino a incagliarsi contro altri relitti ammucchiati. La tempesta infuriò ancora per quasi due giorni, e quando finalmente si placò — ci salvarono gli abitanti di quella povera isoletta.";
			link.l1 = "Voi, Teresa e altri due marinai. Di quello che è successo dopo abbiamo già un'idea. Meglio raccontateci come siete riusciti a fuggire dalla prigione e a lasciare l'isola.";
			link.l1.go = "WildRose_Rupert_63";
		break;

		case "WildRose_Rupert_63":
			dialog.text = "Avrebbero fatto meglio a fucilarmi quel giorno... Se solo avessi saputo cosa mi aspettava, mi sarei incatenato da solo alle sbarre e non mi sarei mosso di lì.";
			link.l1 = "Non era forse così comodo sulla tartana come sul brigantino, eh, "+npchar.name+"?";
			link.l1.go = "WildRose_Rupert_64_1";
			link.l2 = "Non ditemi che siete finiti in una tempesta anche su una tartana.";
			link.l2.go = "WildRose_Rupert_64_2";
		break;

		case "WildRose_Rupert_64_1":
			dialog.text = "Tartana? Ah-ah-ah... Giusto, era proprio questo il mio piano. Pensavo di essere stata fortunata. Il capo delle guardie della prigione era un ex ufficiale della marina inglese, che si è commosso per la mia sventura. È stato lui a raccontarmi sia delle tartane dei contrabbandieri cubani, sia del fatto che volevano giustiziarmi. Forse si potrebbe chiamarlo un uomo d'onore – è stato lui stesso a propormi di lasciarmi andare, perché potessi affidarmi al destino.";
			link.l1 = "Non capisco... Se non sulle tartane, allora come avete lasciato l'isola?";
			link.l1.go = "WildRose_Rupert_68";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Rupert_64_2":
			dialog.text = "Tartana? Ah-ah-ah... Giusto, era proprio questo il mio piano. Pensavo di essere fortunata. Il capo delle guardie della prigione era un ex ufficiale della marina inglese, che si è lasciato toccare dalla mia sventura. È stato lui a raccontarmi sia delle tartane dei contrabbandieri cubani, sia che stavano per giustiziarmi. Forse si potrebbe chiamarlo un uomo d'onore – è stato lui stesso a propormi di lasciarmi andare, perché potessi affidarmi al destino.";
			link.l1 = "Non capisco... Se non sulle tartane, allora come avete lasciato l'isola?";
			link.l1.go = "WildRose_Rupert_68";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;
		
		case "WildRose_Rupert_68":
			dialog.text = "Se chiudi quella bocca e ascolti, capirai. Nuotavo verso le tartane, ho nuotato a lungo — finché, oltre il muro di pioggia, ho visto una luce. Era qualcosa di assolutamente incredibile, maledizione. Brillava come il sole sul ponte di uno dei galeoni semisommersi, e io mi ci sono diretto. Senza sapere che stavo per commettere l’errore più grave della mia vita. Sono salito a bordo per la scaletta laterale — e mi sono ritrovato di fronte alla luce. Brillava sopra una statua d’oro e...";
			link.l1 = "L'idolo di Kukulkan. Giusto, allora la 'San Geronimo' non era ancora affondata...";
			link.l1.go = "WildRose_Rupert_69";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), pchar);
		break;

		case "WildRose_Rupert_69":
			dialog.text = "Quindi anche tu l'hai visto, "+pchar.lastname+"?";
			link.l1 = "Non l'ho solo visto. Mi sono spostato nello spazio grazie a lui, e più di una volta.";
			link.l1.go = "WildRose_Rupert_70";
		break;

		case "WildRose_Rupert_70":
			dialog.text = "Mentendo! Dici che è successo più di una volta?! E allora come fai a stare qui, tutto pieno di salute?!";
			link.l1 = "Dopo essermi spostato ho bevuto una pozione indiana, è stata quella ad aiutarmi a restare in vita e a riprendere le forze.";
			link.l1.go = "WildRose_Rupert_71";
		break;

		case "WildRose_Rupert_71":
			dialog.text = "Ah, ecco come stanno le cose. Ma sai quante forze ci ho messo a riprendermi? Lo sai?!";
			link.l1 = "Immagino. Avete toccato l'idolo, e lui vi ha trasportato a Dominica – al villaggio degli indiani, lì vi hanno sacrificato alla statua e vi siete ritrovati nel Main, giusto?";
			link.l1.go = "WildRose_Rupert_72";
		break;

		case "WildRose_Rupert_72":
			dialog.text = "Esatto. Non ho mai provato un dolore come quello, mentre giacevo accanto a quella statua. Non so con cosa paragonarlo. Forse nemmeno se ti crollasse addosso una casa di pietra proveresti tanta sofferenza. Appena ripresi i sensi, vidi di nuovo una folla di indigeni avvicinarsi. Se solo avessi parlato la loro lingua — giuro, avrei implorato che mi uccidessero lì sul posto.";
			link.l1 = "Erano i Miskito del villaggio qui vicino, giusto?";
			link.l1.go = "WildRose_Rupert_76";
		break;

		case "WildRose_Rupert_76":
			dialog.text = "Proprio loro. Mi trascinarono in una delle capanne, dove un indigeno strano, diverso da loro, mi versò qualcosa direttamente in bocca. Il dolore si attenuò un po’, ma non sparì del tutto. Verso sera mi portarono vicino al fuoco, e quel bastardo tutto dipinto iniziò una specie di rituale. Miserabile bastardo.";
			link.l1 = "Occhio di Serpente... Avresti dovuto essergli grato per averti salvato la pelle.";
			link.l1.go = "WildRose_Rupert_77";
		break;

		case "WildRose_Rupert_77":
			dialog.text = "Salvezza?.. Tre anni, "+pchar.lastname+".   Per tre anni sono rimasto quasi immobile, facevo i miei bisogni addosso, mi svegliavo nel mio stesso vomito – perché non sopportavo più tutti quei decotti puzzolenti e quelle tinture che mi versavano a forza in gola!   E poi, per quasi un altro anno, ho dovuto imparare di nuovo a camminare.";
			link.l1 = "Una storia straziante. Ma davvero, quasi mi fate pena.";
			link.l1.go = "WildRose_Rupert_78";
		break;

		case "WildRose_Rupert_78":
			dialog.text = "Infilati la tua pietà su per il grasso culo cattolico di tuo Padre. Non ho bisogno della compassione di nessuno. Vuoi che continui, o ti serve un po' di tempo per piagnucolare, ragazzino?";
			link.l1 = "Questo viaggio di certo non vi ha reso più galanti. Ma va bene, per Mary posso sopportare. Anche se, credo, abbiamo già scoperto la cosa principale – ascolteremo comunque fino alla fine.";
			link.l1.go = "WildRose_Rupert_79";
		break;

		case "WildRose_Rupert_79":
			dialog.text = "Alzandomi a fatica, ho lasciato quel maledetto villaggio e sono arrivato sulla costa, fino alla baia di Amatique. Lì ho incontrato dei contrabbandieri, la cui nave era ancorata lì vicino, e mi sono unito a loro, presentandomi come Rupert Casper – non ho rinunciato al mio nome, ma ho anche mantenuto il cognome di uno dei responsabili di tutte le mie disgrazie. Per non dimenticare perché mi trovo qui.";
			link.l1 = "Tutti sono colpevoli per te, Northwood... tranne te stesso. Beh, in fondo ti capisco – anni di umiliazioni e sofferenze, ora te ne stai qui in questi boschi. Come non perdere la testa, giusto?";
			link.l1.go = "WildRose_Rupert_80_1";
			link.l2 = "Ne avete passate tante, Northwood – su questo non si discute. E guardate dove siete finito... Nei boschi, ai margini della civiltà. Qui non si impazzisce...";
			link.l2.go = "WildRose_Rupert_80_2";
		break;

		case "WildRose_Rupert_80_1":
			dialog.text = "Io sono il padrone di questi boschi, "+pchar.lastname+". In quindici anni e passa ho fatto strada da un povero marinaio su una nave di contrabbandieri fino a diventarne il capo. Non il capitano di una barchetta qualsiasi, ma il padrone di tutta la costa, dalla baia di Amatique fino al Golfo della Morte.";
			link.l1 = "Ebbene, una rinascita degna, lo ammetto.";
			link.l1.go = "WildRose_Rupert_81";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Rupert_80_2":
			dialog.text = "Io sono il padrone di questi boschi, "+pchar.lastname+". In oltre quindici anni ho fatto strada da miserabile marinaio su una nave di contrabbandieri fino a diventare il loro capo. Non il capitano di qualche bagnarola — ma il padrone di tutta la costa, dalla baia di Amatique al golfo della Morte.";
			link.l1 = "Ebbene, una rinascita degna, lo ammetto.";
			link.l1.go = "WildRose_Rupert_81";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;

		case "WildRose_Rupert_81":
			dialog.text = "C’è chi dice che queste siano le terre del Diavolo della Foresta... Una bugia sfacciata – queste sono le mie terre. E Svenson lo sa, ah-ah-ah. Più di una volta ha mandato qui i suoi uomini per cercare di scoprire la mia identità – e nessuno di loro è mai tornato da lui. Vivo, eh-eh. Solo sulle dita di una mano si contano quelli che sanno con quale nome ho iniziato la mia carriera da contrabbandiere, e dove vivo, in queste foreste.";
			link.l1 = "Quindi adesso vi fate chiamare in un altro modo. Ora capisco perché la notizia che qualcuno cercava Rupert Casper vi abbia fatto andare così nel panico.";
			link.l1.go = "WildRose_Rupert_82";
		break;

		case "WildRose_Rupert_82":
			dialog.text = "Panico? Dici sul serio, ragazzo? L’unico che è in panico qui sei tu — sul mio territorio, circondato dai miei uomini, completamente in mio potere! Posso fare di te tutto quello che voglio. E di lei pure — solo per essere stata la causa di tutte le disgrazie che ho vissuto!";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_82_add";
		break;

		case "WildRose_Rupert_82_add":
			StartInstantDialog("Mary", "WildRose_Rupert_83", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_83":
			dialog.text = "Sei pazzo, semplicemente pazzo e basta, giusto? Non conosco medicina né medico che possano guarirti, Rupert Northwood! Hai passato tormenti terribili, ma... come puoi dare tutta la colpa a me?!";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_83_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_83_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_84", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_84":
			dialog.text = "Te l'ho già detto – senza di te, niente di tutto questo sarebbe successo. Ammettilo e basta.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_84_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_84_add":
			StartInstantDialog("Mary", "WildRose_Rupert_85", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Rupert_85":
			dialog.text = "...";
			link.l1 = "Lascialo, "+npchar.name+". Abbiamo sentito abbastanza. Alcune strade davvero non vale la pena percorrerle fino in fondo. Avevo un brutto presentimento quando abbiamo deciso di metterci in tutto questo. Ma non gli ho dato ascolto. Peccato.";
			link.l1.go = "WildRose_Rupert_85_add";
		break;
		
		case "WildRose_Rupert_85_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_86", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Rupert_86":
			dialog.text = "Sììì, allora non vi sareste trovati qui, tutti e due, in trappola, impotenti a fare qualsiasi cosa. Ora prova sulla tua pelle, figliola, quello che ho provato io!";
			link.l1 = "E chi ti ha detto che siamo impotenti a fare qualcosa? Squadra-a-a, in posizione!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_20");
		break;
		
		case "WildRose_Rupert_87":
			dialog.text = "In che cosa consiste il problema, pivello? Hai perso qualcuno? Ah-ah-ah... Ah-ah-ah. AH-AH-AH-AH-AH-AH!!! Oh, se solo potessi vedere la tua faccia adesso, idiota! Ehi, Mason, porta qui il mio regalo per i nostri ospiti.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_22");
		break;
		
		case "WildRose_Rupert_88":
			dialog.text = "...";
			link.l1 = "Maledetto!   Dove sono i miei uomini?";
			link.l1.go = "WildRose_Rupert_89";
		break;
		
		case "WildRose_Rupert_89":
			dialog.text = "Parli di quel gruppetto di idioti che ha pensato di tendermi un'imboscata? Il mio amico oste mi ha avvisato in tempo del tuo arrivo in città, e li ho accolti come si deve... Alcuni sono riusciti a svignarsela. Ma non preoccuparti – uno l'ho preso vivo. Così potrai vedere con i tuoi occhi quale destino vi aspetta oggi.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_25");
			
			// WildRose_Etap6_LifeAfterDeath_24_1();
		break;
		
		case "WildRose_Rupert_90":
			dialog.text = "Maledetto! La pagherai! (piange) Lo giuro, giusto!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_29");
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Alonso_11":
			dialog.text = "...";
			link.l1 = "Alonso! Quanto sono felice di vederti!";
			link.l1.go = "WildRose_Alonso_12";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Alonso_12":
			dialog.text = "E io che gioia ho avuto nel rivedervi, capitano! Qualcuno ha sussurrato a quel bastardo che lo stavate cercando — e ci hanno accolto con una grandinata di mitraglia a metà strada. Io e una manciata di uomini siamo riusciti a ritirarci e ci siamo precipitati al porto per avvertirvi. Per fortuna, la sentinella di guardia, appena mi ha visto su una barchetta che avevo comprato in fretta in città, ha subito capito cosa stava succedendo. Ha radunato gli uomini — e siamo venuti qui a darvi man forte.";
			link.l1 = "Grazie a te, amico. Ci hai salvati da una morte certa.";
			link.l1.go = "WildRose_Alonso_13";
		break;

		case "WildRose_Alonso_13":
			dialog.text = "Niente di che. Che facciamo adesso, capo?";
			link.l1 = "Raduna la gente e andate sulla nave. Io e Mary dobbiamo restare un po' da soli.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;
		
		case "WildRose_Mary_261":
			dialog.text = "Dio mio, "+pchar.name+"... Non riesco ancora a crederci, proprio non ci riesco. Mio padre... È un mostro... Perché mi ha fatto questo? È davvero impazzito?";
			link.l1 = "Ha dovuto sopportare sofferenze terribili. L'ammutinamento sulla 'Cornovaglia', la fuga attraverso l'Atlantico, la tempesta e la morte di tua madre. Non riesco nemmeno a immaginare come abbia superato il viaggio attraverso i portali di quegli idoli senza la pozione dei Comanche – ma proprio questo gli ha fatto perdere la ragione.";
			link.l1.go = "WildRose_Mary_262";
			locCameraFromToPos(-3.80, 1.10, 52.00, false, 0.61, 0.27, 49.69);
			LAi_ActorAnimation(pchar, "sharle_mary_sit", "", 50.0);
			LAi_ActorAnimation(npchar, "sharle_mary_sit", "", 50.0);
			CharacterTurnAy(pchar, 6.00);
			CharacterTurnAy(npchar, 6.00);
		break;

		case "WildRose_Mary_262":
			dialog.text = "E se fosse stato così anche prima? O magari era già un mascalzone, solo un po' più mite, ma amava davvero mia madre? E se questi eventi avessero solo liberato ciò che aveva dentro? E se è così... cosa succede se anche io ho qualcosa di lui dentro di me? Potrebbe essere, "+pchar.name+", giusto?";
			link.l1 = "Hai sicuramente preso qualcosa da lui, "+npchar.name+". Nella battaglia di oggi l’ho notato — combatti con la stessa tenacia, con lo stesso fuoco negli occhi e con la stessa furia che aveva lui. Ma la sua follia non è in te. Tu sei diversa. Viva, sincera, con il cuore in mano. Ed è proprio per questo che ti ho amato. E a quanto pare, Northwood aveva ragione: di carattere hai preso tutta da tua madre.";
			link.l1.go = "WildRose_Mary_263";
		break;

		case "WildRose_Mary_263":
			dialog.text = "Lo pensi davvero, tesoro?";
			link.l1 = "Certo, amore. Se l'avessi incontrato per caso, senza sapere chi fosse, mai avrei pensato che foste parenti.";
			link.l1.go = "WildRose_Mary_264";
		break;

		case "WildRose_Mary_264":
			dialog.text = "Sai, sull'Isola della Giustizia non ci sono poi così tanti divertimenti. Fin da bambina mi sono innamorata della scherma – prima combattevo con i ragazzi, con bastoni di legno, poi con uomini adulti, con vere lame, giusto? Ho sempre voluto essere alla loro altezza... ma mi sono sempre sentita più debole, anche quando vincevo\nAllora tornavo semplicemente a casa – e ricominciavo ad allenarmi. Mi esercitavo per ore, finché le mani non iniziavano a tremare, giusto? È questo il fuoco di cui parli? Quella rabbia che senti dentro?";
			link.l1 = "In un certo senso, sì. Mi sembra che questo fuoco ti dia molta più forza di quella che tu stessa vedi in te. E, che tu lo voglia o no, è un dono di tuo padre. Anche se lui non aveva alcuna intenzione di farti un regalo.";
			link.l1.go = "WildRose_Mary_265";
			locCameraSleep(false);
			locCameraFromToPos(-1.95, 1.81, 48.29, true, -2.11, -0.04, 52.55);
		break;

		case "WildRose_Mary_265":
			dialog.text = "Pensi che abbiamo fatto bene a scavare nel passato, giusto?";
			link.l1 = "Ora che sappiamo tutto... non sembra poi un'idea così buona. Ma se vuoi conoscere la verità, devi essere pronto al fatto che potrebbe non piacerti.";
			link.l1.go = "WildRose_Mary_266";
		break;

		case "WildRose_Mary_266":
			dialog.text = "Hai ragione, "+pchar.name+", giusto... Restiamo ancora un po' qui. Non ho voglia di tornare sulla nave adesso. Voglio solo... restare qui, in silenzio.";
			link.l1 = "Certo, amore. Anch'io volevo proportelo.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_38");
		break;
		
		// Тичингиту
		case "WildRose_Tichingitu_Final_1":  
			dialog.text = npchar.name+", arrivare puntuale, capitano "+pchar.name+".";
			link.l1 = "Sapevo di poter contare su di te, amico mio. Grazie — nessuno avrebbe potuto fare di meglio.";
			link.l1.go = "WildRose_Tichingitu_Final_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Tichingitu_Final_2":
			dialog.text = "La giungla è casa di "+npchar.name+". "+npchar.name+" felice di combattere nella giungla. La giungla dà forza a "+npchar.name+".";
			link.l1 = "È proprio per questo che ti ho messo a capo della squadra. E ho fatto bene — come vedi, ci aspettavano a braccia aperte.";
			link.l1.go = "WildRose_Tichingitu_Final_3";
		break;

		case "WildRose_Tichingitu_Final_3":
			dialog.text = "Cosa capitano "+pchar.name+" vuole fare adesso?";
			link.l1 = "Io e Mary abbiamo bisogno di stare un po’ da soli. Raduna i feriti e portali sulla nave, prendete anche i morti — li seppelliremo in mare. E, "+npchar.name+"... dì ad Alonso che il padre di Mary va sepolto in modo adeguato, secondo il rito protestante, da qualche parte qui. Solo lui e tu dovete sapere dove sarà la tomba. Non dirlo a nessuno, nemmeno a Mary. Non ha bisogno di tormentarsi con quei ricordi.";
			link.l1.go = "WildRose_Tichingitu_Final_4";
		break;

		case "WildRose_Tichingitu_Final_4":
			dialog.text = npchar.name+" capire, capitano "+pchar.name+". Tichingitu farà tutto.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;
		
		// Дюран
		case "WildRose_Duran_Final_1":   
			dialog.text = "Dei bastardi tosti... Ma li abbiamo fregati, ah ah. Che marciscano qui a chiedersi se ne sia valsa la pena.";
			link.l1 = "Grazie, "+npchar.name+", ottimo lavoro. Fa paura pensare cosa sarebbe successo a Mary... e a me... se non vi avessi mandato a coprirci le spalle...";
			link.l1.go = "WildRose_Duran_Final_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Duran_Final_2":
			dialog.text = "Ah, cap, tu te la saresti cavata — ti conosco. Hai visto quel coltellaccio che aveva il loro capo? Non l’ho perso d’occhio un secondo. Se non ti piace, non mi offendo se me lo regali.";
			link.l1 = "Hmm... Vedremo, amico mio, vedremo. Per ora raduna i sopravvissuti e riportali sulla nave. Prendete anche i morti — li affideremo al mare. E poi... quel capo era il padre di Mary. Prendi Alonso e seppellitelo secondo il rito protestante, qui da qualche parte. Nessuno deve sapere dove sarà la tomba. Soprattutto Mary. Non ha bisogno di rivangare il passato.";
			link.l1.go = "WildRose_Duran_Final_3";
		break;

		case "WildRose_Duran_Final_3":
			dialog.text = "Sarà fatto, cap. Aspetta... Anzi no... Vado.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;
		
		// Тонзаг
		case "WildRose_Tonzag_Final_1": 
			dialog.text = "Faceva un bel caldo qui, cap. Quei bastardi hanno avuto quello che si meritavano. Hai visto la faccia di quel nanerottolo quando siamo arrivati?";
			link.l1 = "Di certo non se lo aspettava. Proprio come io e Mary non ci aspettavamo che fosse un tale farabutto. Ma alla fine il mio istinto non mi ha tradito, quando ho deciso di coprirci le spalle.";
			link.l1.go = "WildRose_Tonzag_Final_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Tonzag_Final_2":
			dialog.text = "Non sei nuovo nei Caraibi. Ormai ti sei abituato alla feccia che circola qui, e senti il pericolo pure con il culo. Cosa ordini adesso? Torniamo alla nave?";
			link.l1 = "Prendi i feriti, anche i morti, e tornate a bordo. I caduti li consegneremo al mare, come fedeli figli dell’oceano. Io e Mary arriveremo più tardi — abbiamo bisogno di stare un po’ da soli. E un’altra cosa: seppellite il padre di Mary secondo il rito protestante. Puoi chiedere aiuto ad Alonso. Ma assicurati che nessuno sappia dove si trova la tomba. Soprattutto Mary. Non voglio che si tormenti con quei ricordi.";
			link.l1.go = "WildRose_Tonzag_Final_3";
		break;

		case "WildRose_Tonzag_Final_3":
			dialog.text = "Hai ragione. Non c’è motivo che venga qui a versare lacrime. Non preoccuparti, faremo tutto come si deve — e nessuno lo verrà mai a sapere.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;
		
		// Айронс
		case "WildRose_Irons_Final_1":
			dialog.text = "Capitano, signore, posso riferire: l’imboscata ha avuto successo, i bastardi sono stati eliminati, il capitano è salvo.";
			link.l1 = "Non è il momento per fare lo spiritoso, eh? Brutta scelta. Non vorrai lavare il ponte davanti a tutta la ciurma, vero? Oh, quanto si divertirebbero... Ti consiglio di non mettere più alla prova la mia pazienza. Soprattutto oggi.";
			link.l1.go = "WildRose_Irons_Final_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Irons_Final_2":
			dialog.text = "Ehm... in realtà sono un ufficiale, e...";
			link.l1 = "Per ora. Oggi ufficiale — domani marinaio, dopodomani mendicante.";
			link.l1.go = "WildRose_Irons_Final_3";
		break;

		case "WildRose_Irons_Final_3":
			dialog.text = "Capito: " + GetFullName(pchar) + " è il Capitano Serietà. Basta scherzi. Ordini, signore?";
			link.l1 = "Raccogli i feriti e portali sulla nave. Dì ad Alonso di formare una squadra e recuperare i corpi dei nostri ragazzi — li consegneremo al mare. Che seppellisca anche il padre di Mary secondo il rito protestante. Solo lui e chi lo aiuta devono sapere dov’è la tomba. Mary non deve sapere nulla. Non voglio che si tormenti con quei ricordi.";
			link.l1.go = "WildRose_Irons_Final_4";
		break;

		case "WildRose_Irons_Final_4":
			dialog.text = "Va bene... Sarà fatto. E non preoccuparti, so tenere la bocca chiusa.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;
		
		// Лонгвэй
		case "WildRose_Longway_Final_1":
			dialog.text = "Signor Capitano, abbiamo vinto. Non è scappato un solo cane.";
			link.l1 = "Bel lavoro, "+npchar.name+", grazie. Sapevo di poter contare su di te. Prendi chi è sopravvissuto e tornate alla nave. Mary ed io restiamo un po’ a terra.";
			link.l1.go = "WildRose_Longway_Final_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Longway_Final_2":
			dialog.text = "Cosa dobbiamo fare con i corpi dei caduti?";
			link.l1 = "Li affideremo al mare. Dì ad Alonso di occuparsi delle esequie. E un’altra cosa: digli che il padre di Mary deve essere seppellito secondo le tradizioni protestanti qui, nella giungla, lontano da occhi indiscreti. Nessuno deve sapere dove sarà la tomba — specialmente Mary. Conoscendola, vorrà tornare qui, e non sarebbe una buona cosa per lei.";
			link.l1.go = "WildRose_Longway_Final_3";
		break;

		case "WildRose_Longway_Final_3":
			dialog.text = "Trasmetterò tutto. Volete altro, signore?";
			link.l1 = "È tutto, amico. Vai, riposati e cura le ferite.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;
		
		// Алонсо
		case "WildRose_Alonso_Final_1":
			dialog.text = "Che macello... Come stai, cap?";
			link.l1 = "Sto bene... a parte che Mary ed io abbiamo dovuto uccidere suo padre...";
			link.l1.go = "WildRose_Alonso_Final_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Alonso_Final_2":
			dialog.text = "A quanto pare, quel bastardo se lo meritava...";
			link.l1 = "Hai ragione, "+npchar.name+". Ma comunque dobbiamo dargli una sepoltura degna — secondo i riti protestanti. Occupatene tu personalmente. Nessuno deve sapere dove si trova la tomba. Specialmente Mary.";
			link.l1.go = "WildRose_Alonso_Final_3";
		break;

		case "WildRose_Alonso_Final_3":
			dialog.text = "Vuoi proteggerla dai brutti ricordi?";
			link.l1 = "E dalle pene inutili. Spedisci tutti gli altri alla nave per curarsi. Porta i caduti a bordo — li seppelliremo in mare appena io e Mary torneremo. Per ora abbiamo bisogno di stare da soli.";
			link.l1.go = "WildRose_Alonso_Final_4";
		break;

		case "WildRose_Alonso_Final_4":
			dialog.text = "Dirò ai ragazzi di non venirvi a cercare.";
			link.l1 = "Grazie, "+npchar.name+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;
	}
} 

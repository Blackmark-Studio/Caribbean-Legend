// диалоги НПС по квесту НСО
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
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
			dialog.text = "Cosa cerchi, marinaio?";
			link.l1 = "Niente.";
			link.l1.go = "exit";
		break;
		
		// инспектор Ноэль Форже
		case "noel":
			dialog.text = "Piacere di conoscerti, capitano!";
			link.l1 = "Sono lieto d’incontrarvi anch’io, monsieur Forget. È raro qui, nella selva, imbattersi in un gentiluomo venuto dalla madrepatria...";
			link.l1.go = "noel_1";
		break;
		
		case "noel_1":
			DialogExit();
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_3";
			LAi_SetActorType(sld);
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "noel_2":
			dialog.text = "Sono lieto che durante questo viaggio sarò a bordo della vostra nave, capitano. Il Chevalier de Poincy mi ha raccontato molte storie affascinanti su di voi. Son certo che, dopo la cena in cambusa, non mancheranno argomenti di conversazione. E un bicchiere di vino potrebbe tornarci utile.";
			link.l1 = "Son sempre pronto per due chiacchiere all’ombra, specie a pancia piena. Sarà un piacere farti compagnia, Barone. ";
			link.l1.go = "noel_3";
		break;
		
		case "noel_3":
			dialog.text = "Perfetto. Quando arriviamo in una colonia, ti chiederò di scortarmi dal governatore, e gli spiegherò io stesso quel che bisogna fare. Tu aspetta solo che io finisca le mie faccende. Intesi?";
			link.l1 = "Aye, monsieur Forget. Benvenuto a bordo!";
			link.l1.go = "noel_4";
		break;
		
		case "noel_4":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 12.0);
		break;
		
		case "noel_5":
			dialog.text = "Tortuga è una colonia piccina, capitano. Direi che mi serviranno tre giorni buoni per esaminare tutto quel che mi serve su quest’Isola.";
			link.l1 = "Inteso, Barone. Fra tre giorni torno qui a prendervi. Buona fortuna!";
			link.l1.go = "noel_6";
		break;
		
		case "noel_6":
			DialogExit();
			DoQuestReloadToLocation("Tortuga_town", "reload", "reload3", "Patria_VisiterTortuga");
		break;
		
		case "noel_7":
			dialog.text = "Il mio lavoro a Tortuga è finito, è ora di salpare l’ancora.";
			link.l1 = "Capito, Barone. Salperemo all’istante.";
			link.l1.go = "noel_8";
		break;
		
		case "noel_8":
			DialogExit();
			Patria_VisiterTortugaSail();
		break;
		
		case "noel_9":
			dialog.text = "Sì, sì, ne daremo sicuramente notizia a Capsterville. La minaccia che una colonia così importante venga conquistata... impensabile, mi assicurerò personalmente che il Chevalier de Poincy prenda misure dure e spietate! Capitano, resterò su quest’isola per una settimana, ci sono tante piantagioni da controllare, mi servirà un po’ di tempo.";
			link.l1 = "Inteso, Barone. Ti aspetterò vicino al palazzo del governatore tra sette giorni. Divertiti e non affaticarti troppo!";
			link.l1.go = "noel_10";
		break;
		
		case "noel_10":
			DialogExit();
			DoQuestReloadToLocation("PortPax_town", "reload", "reload3", "Patria_VisiterPortPax");
		break;
		
		case "noel_11":
			dialog.text = "Eccoti, capitano. Ho finito i miei affari a Hispaniola, è ora di levare l’ancora.";
			link.l1 = "Inteso, Barone. Salpiamo all’istante.";
			link.l1.go = "noel_12";
		break;
		
		case "noel_12":
			DialogExit();
			Patria_VisiterPortPaxSail();
		break;
		
		case "noel_13":
			dialog.text = "Capitano, quest’isola mi pare familiare. Non sarà forse San Cristoforo?";
			link.l1 = "Sì, barone, proprio così. Ci siamo quasi.";
			link.l1.go = "noel_14";
		break;
		
		case "noel_14":
			dialog.text = "Quasi arrivati?! Non dovevamo fermarci anche a Saint-Martin? Pure quella fa parte delle colonie francesi.";
			link.l1 = "Intendi Sint Maarten? È una colonia olandese, monsieur Forget.";
			link.l1.go = "noel_15";
		break;
		
		case "noel_15":
			dialog.text = "Ah sì? A Parigi lo chiamano francese. Com’è che qui è diverso?";
			link.l1 = "Nessuna idea, Barone. Da quando ho messo piede nell’arcipelago, Sint Maarten è sempre stata una colonia olandese. Forse mi sfugge qualcosa. Dovreste parlarne con il Cavaliere de Poincy.";
			link.l1.go = "noel_16";
		break;
		
		case "noel_16":
			dialog.text = "D'accordo, capitano, sia come vuoi. Tanto siamo quasi arrivati a Capsterville.";
			link.l1 = "...";
			link.l1.go = "noel_17";
		break;
		
		case "noel_17":
			DialogExit();
			Island_SetReloadEnableGlobal("Nevis", true);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5.0);
			pchar.quest.Patria_visiter_fin.win_condition.l1 = "location";
			pchar.quest.Patria_visiter_fin.win_condition.l1.location = "Charles_Roomtownhall";
			pchar.quest.Patria_visiter_fin.function = "Patria_VisiterFin";
			pchar.questTemp.Patria = "epizode_2_return";
		break;
		
		case "noel_18":
			dialog.text = TimeGreeting()+", capitano. Mi fa piacere vedervi. Ho sentito che siete stato promosso, accettate le mie congratulazioni! A dirla tutta, siete davvero uno degli ufficiali più saggi e dotati al servizio di de Poincy.";
			link.l1 = "Grazie, monsieur.";
			link.l1.go = "noel_19";
		break;
		
		case "noel_19":
			dialog.text = "Infine, rimane solo una colonia, Saint-Martin. A dir la verità, mi sono stancato di questi viaggi. Sarò lieto di concludere questa ispezione e cominciare a preparare la prossima campagna commerciale delle Indie Occidentali Francesi. Siamo pronti a salpare l’ancora?";
			link.l1 = "Aye, Barone. Sali a bordo.";
			link.l1.go = "noel_20";
		break;
		
		case "noel_20":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_SanMartinBaron", 5.0);
		break;
		
		case "noel_21":
			dialog.text = "Capitano, potresti dirmi che diavolo è appena successo? Vuol forse dire che siamo in guerra? E per tutti i santi, perché i dannati olandesi quasi ci hanno mandato a fondo?";
			link.l1 = "Barone, non ci capisco un'acca nemmeno io! Dev’esserci stato un malinteso, senza dubbio.";
			link.l1.go = "noel_22";
		break;
		
		case "noel_22":
			dialog.text = "Capitano, scommetto il mio ultimo doblone che questa ‘malintesa’ ha pure un nome! Peter Stuyvesant, il famigerato ‘affittuario’ di Saint-Martin e compare del nostro caro Cavaliere de Poincy!";
			link.l1 = "Non ne ho la minima idea, Barone. Sarebbe meglio sbrigarci a Capsterville e riferire questa faccenda al Governatore Generale.";
			link.l1.go = "noel_23";
		break;
		
		case "noel_23":
			dialog.text = "Senza dubbio, è proprio quello che faremo! E pretenderò delle spiegazioni! Lo sapevo che affittare un’isola agli olandesi era una gran fesseria! Filiamo via di qui più in fretta che possiamo, capitano, prima che a qualcuno venga voglia di rincorrerci!";
			link.l1 = "Precisamente, monsieur ...";
			link.l1.go = "noel_24";
		break;
		
		case "noel_24":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_SanMartinBack", 5.0);
		break;
		
		case "noel_25":
			dialog.text = "Monsieur, permettete che vi porga le mie congratulazioni per la vostra promozione! Ho sostenuto con entusiasmo la decisione di monseigneur de Poincy di conferirvi il titolo di Vice Ammiraglio. Questo grado ve lo siete guadagnato! Ora, sono appena tornato da Saint-Martin. Nei magazzini di Philipsburg abbiamo fatto un’inventario, tutte le merci olandesi sono state sequestrate e ora appartengono al tesoro di Francia. A voi, in qualità di comandante dell’operazione, spetta una parte del bottino. Sono d’accordo con il Cavaliere, è giusto così. Le vostre merci sono state trasferite nel magazzino della bottega di St. Christopher, e potrete ritirarle quando vi pare.";
			link.l1 = "Grazie, Barone. Lasciate che le merci restino lì per un po'. Al mio ritorno da Curaçao, le prenderò.";
			link.l1.go = "noel_26";
		break;
		
		case "noel_26":
			dialog.text = "Buona fortuna nella tua prossima impresa, Viceammiraglio! Son certo che tornerai vittorioso e darai a quel furfante di Stuyvesant la punizione che merita.";
			link.l1 = "...";
			link.l1.go = "noel_27";
		break;
		
		case "noel_27":
			DialogExit();
			pchar.questTemp.Patria = "epizode_11_start";
			AddQuestRecord("Patria", "58");
			pchar.questTemp.Patria.GoodsSM = "true";
		break;
		
		case "noel_28":
			dialog.text = "Chi abbiamo qui! Vice Ammiraglio Charles de Maure! Felice di vederti! Che vento ti porta a Port-au-Prince?";
			link.l1 = "Il piacere è mio, Barone. Sono qui per dovere, dovevo fare visita al signor Jeremy Deschamps du Mussaca per una questione di cortesia...";
			link.l1.go = "noel_29";
		break;
		
		case "noel_29":
			dialog.text = "Questo incontro è davvero una gran fortuna, poiché attendevo da tempo di parlarti di persona. Ho da dirti due parole, ma non qui.";
			link.l1 = "Andiamo allora alla taverna, che ne dici?";
			link.l1.go = "noel_30";
		break;
		
		case "noel_30":
			DialogExit();
			FreeSitLocator("PortPax_tavern", "sit_base1");
			DoQuestReloadToLocation("PortPax_tavern", "sit", "sit_base1", "Patria_CondotierTavern");
		break;
		
		case "noel_31":
			LAi_SetSitType(pchar);
			dialog.text = "Qui non ci sono orecchie indiscrete, possiamo parlare senza timore...";
			link.l1 = "Sono tutto orecchi, Barone.";
			link.l1.go = "noel_32";
		break;
		
		case "noel_32":
			dialog.text = "Vice Ammiraglio, parete un uomo d'onore. Un così valoroso ufficiale di marina non può essere altrimenti...";
			link.l1 = "Hmm... Non credo di afferrare a pieno il vostro discorso, monsieur...";
			link.l1.go = "noel_33";
		break;
		
		case "noel_33":
			dialog.text = "Monsieur de Maure, volevo chiederle: che ne pensa del suo signore, il Governatore Generale Philippe de Poincy?";
			link.l1 = "Il dovere d’un ufficiale non è pensare al suo comandante, ma obbedirgli senza fiatare.";
			link.l1.go = "noel_34";
		break;
		
		case "noel_34":
			dialog.text = "Oh, lascia perdere, Vice Ammiraglio, qui non siamo né in caserma né nella sala di de Poincy. Te lo dirò chiaro: non credi anche tu che monsieur de Poincy... abusi del suo potere? Ancora non riesco a scordare come abbiamo rischiato di finire a mollo sotto i cannoni del Forte di Saint-Martin. Sono certo che il tradimento degli olandesi aveva una ragione.";
			link.l1 = "Volevano conquistare l’isola.";
			link.l1.go = "noel_35";
		break;
		
		case "noel_35":
			dialog.text = "Sì, sì, ma perché proprio nell’istante in cui ho deciso d’ispezionarlo? Perché non un mese prima? O due mesi dopo? Non credo affatto che sia stata una coincidenza, monsignore. Non avete qualche sospetto? Lì entrambi rischiavamo la pelle.";
			link.l1 = "Rischio la pelle ogni giorno, monsignor Forget. Credo che lo capiate...";
			link.l1.go = "noel_36";
		break;
		
		case "noel_36":
			dialog.text = "Il tuo coraggio non lascia spazio a dubbi. Ma non è di questo che volevo parlarti. Vedi... Quando svolgevo il mio lavoro a Saint-Martin, che tu hai liberato, ho sentito spesso sussurri tra la gente del posto riguardo a una miniera nascosta nelle viscere dell’isola. Ho provato a chiedere in giro, ma tutti si facevano gli sciocchi. Erano spaventati... Si capiva che non mi ritenevano molto affidabile, e questo ha solo rafforzato i miei sospetti: non è che questa miniera misteriosa sia la causa di tutto, Monsieur de Maure? Si fanno guerre per l’oro, dico bene?";
			link.l1 = "Ci sono numerose miniere nell’arcipelago. La maggior parte è ormai esausta e non vale più un accidente. Conosco una grande miniera d’oro ancora in attività, sta agli spagnoli sulla Terraferma del Sud. Ma d’oro estratto a Saint-Martin, non ne ho mai sentito parlare.";
			link.l1.go = "noel_37";
		break;
		
		case "noel_37":
			dialog.text = "Avete una lingua affilata, Vice Ammiraglio! Capisco: non vi fidate di me. Sono appena arrivato... Monsieur de Maure, ma a Parigi sono una persona influente. Il Ministro delle Finanze è un mio caro amico. Faccio spesso visita al Re. La mia autorità supera di gran lunga quella di Philippe de Poincy, almeno sulla carta, perché qui il Governatore Generale comanda su tutti. Ma a dirla tutta, nelle colonie, solo la legge del più forte conta davvero.";
			link.l1 = "Sono pienamente d’accordo con te su questo.";
			link.l1.go = "noel_38";
		break;
		
		case "noel_38":
			dialog.text = "Ma non a Parigi. Lì, le persone più influenti sono il Re e il Ministro delle Finanze... mio caro amico. Monsieur de Maure, siete un uomo militare brillante, ma temo che Phillip de Poincy vi stia usando per i suoi scopi personali. Siete un uomo d’ingegno, quindi avrete sicuramente dei sospetti. Potete fidarvi di me. Vi garantisco assoluto anonimato e l’appoggio delle autorità di Parigi. Lo giuro sul mio titolo.";
			link.l1 = "***RIMANI FEDELE A POINCY***";
			link.l1.go = "noel_39"; // развилка
			link.l2 = "***SCHIERATI COL BARONE FORGET***";
			link.l2.go = "noel_53";
		break;
		
		case "noel_39":
			dialog.text = "";
			link.l1 = "Vi comprendo, Monsieur Forger. Per chi non conosce la mentalità di queste terre, le azioni di de Poincy possono davvero sembrare bizzarre. Quando misi piede per la prima volta nell’Arcipelago, rimasi letteralmente sconvolto da ciò che accadeva qui. Ricordo ancora le prime parole che mi furono rivolte: 'Se incontri una nave spagnola senza scorta, puoi provare ad abbordarla.' Tradimenti, infamie, inganni – qui sono all’ordine del giorno. Pirateria, saccheggi, rapine...";
			link.l1.go = "noel_40";
		break;
		
		case "noel_40":
			dialog.text = "";
			link.l1 = "In Europa siamo in pace con la Spagna. Ma qui ci scanniamo come cani rabbiosi. Gli olandesi oggi ti sorridono e domani uno sbirro della Compagnia ti sequestra la mercanzia perché, dicono, ora è proibita - peccato che nessuno te l’avesse detto. Gli ufficiali inglesi fanno i bucanieri alla luce del sole, affondano le navi della Compagnia, e la Compagnia risponde assoldando qualche tagliagole travestito da nave fantasma per spaventare i mercanti di Sua Maestà...";
			link.l1.go = "noel_41";
		break;
		
		case "noel_41":
			dialog.text = "";
			link.l1 = "In questa tana di lupi, talvolta dobbiamo prendere decisioni strane che non paiono affatto ovvie a chi non mastica queste faccende. E ciò che a te sembra sospetto, in realtà è l’unica strada giusta. È dura stare seduti su più sedie e riuscire comunque a mandare i profitti alla madrepatria. Il Chevalier de Poincy ci riesce alla perfezione, è un capitano navigato e un politico con la vista lunga. Certo, può anche sbagliare, ma alla fine, a chi di noi non è mai capitato...";
			link.l1.go = "noel_42";
		break;
		
		case "noel_42":
			dialog.text = "";
			link.l1 = "E bisogna far i conti con tutto e con tutti. Con le mire degli spagnoli, convinti che il Nuovo Mondo sia roba loro, con l’avidità dei mercanti olandesi, con la fredda astuzia e la spietata ferocia degli inglesi. E pure con quei dannati pirati.";
			link.l1.go = "noel_43";
		break;
		
		case "noel_43":
			dialog.text = "Con quei dannati pirati?!";
			link.l1 = "Sì, hai capito bene. Gli olandesi e gli inglesi collaborano attivamente coi filibustieri... ufficiosamente, s’intende. La Fratellanza della Costa è una potenza vera che può sfidare qualsiasi nazione da queste parti; sono sempre in conflitto con chiunque incrocino e nessuno riesce a fermarli. L’unica cosa che li rende appena meno temibili è che sono sparpagliati e agiscono per conto loro. Lo sapevi che l’ex governatore di Tortuga, Levasseur, ha praticamente creato uno stato nello stato, contando soltanto sui pirati?";
			link.l1.go = "noel_44";
		break;
		
		case "noel_44":
			dialog.text = "Credo d’averne sentito parlare anch’io...";
			link.l1 = "Alcune potenti navi corsare che difendevano l’isola erano sempre ancorate nel porto di Tortuga. Levasseur tradì la Francia, diventando una sorta di padrone locale. E ora, dopo la distruzione del covo di pirati a Tortuga insieme al loro capo, i filibustieri sono maledettamente furiosi coi francesi...";
			link.l1.go = "noel_45";
		break;
		
		case "noel_45":
			dialog.text = "Non mi dire!";
			link.l1 = "Sì. Dovevamo farlo, altrimenti Tortuga sarebbe andata perduta per noi, anche se il risultato non è stato dei migliori. Ora nessuna nave mercantile francese può sentirsi al sicuro nei Caraibi. Gli spagnoli, che pure non hanno patti coi baroni pirati, almeno dispongono di flotte di poderosi galeoni e navi da guerra capaci di respingere i filibustieri. Come gli olandesi, con le loro indie orientali e gli Xebec. Ma noi, ahimè, non possiamo vantarci di simili potenze. E i pirati francesi spesso derubano persino i mercanti francesi stessi.";
			link.l1.go = "noel_46";
		break;
		
		case "noel_46":
			dialog.text = "Questa è follia! Non c'è proprio modo di mettere fine a tutto ciò?";
			link.l1 = "Molti ci hanno provato. Alla fine, invece di combattere, si comprano la lealtà con l’oro. Concessioni da corsari, capisci.";
			link.l1.go = "noel_47";
		break;
		
		case "noel_47":
			dialog.text = "Hmm...";
			link.l1 = "Parlando per esperienza, fondare una compagnia commerciale francese qui nell’Arcipelago sarebbe una pessima idea. Ora capisci quali difficoltà dovrai affrontare? Quanti cani bastardi vogliono la loro fetta dei profitti da queste parti? E non sono tipi che mollano facilmente. E i pirati... sono capaci di follie, chiamali pure pazzi, ma quasi sempre raggiungono i loro sporchi scopi. Per difendere i mercantili dovresti mantenere una flotta da guerra imponente, ma ne varrebbe la pena, da un punto di vista di dobloni?";
			link.l1.go = "noel_48";
		break;
		
		case "noel_48":
			dialog.text = "Ma i mercanti francesi riescono comunque a cavarsela da queste parti?";
			link.l1 = "Esatto, in qualche modo. Soprattutto adesso, che la fortezza pirata di Levasseur a Tortuga è stata presa...";
			link.l1.go = "noel_49";
		break;
		
		case "noel_49":
			dialog.text = "Le tue parole vanno d'accordo con ciò che ha detto de Poincy.";
			link.l1 = "È la verità. Così vanno le cose qui nell’arcipelago, è sempre stato così.";
			link.l1.go = "noel_50";
		break;
		
		case "noel_50":
			dialog.text = "Sei così impetuoso nel parlare. Persino io non sapevo molte di queste cose e, hai ragione: continuo a non saperle. Immagino che i miei sospetti su Poincy fossero infondati. Mi hai aperto gli occhi. Ti ringrazio, Vice Ammiraglio. Ma il ministro francese conta sulla creazione della Compagnia. Il Re ha bisogno di denaro...";
			link.l1 = "Capisco. Ma ti prego, tieni conto di quel che ho appena detto: se la creazione delle Indie Occidentali Francesi è inevitabile, allora assicurati che ci sia una flotta militare robusta a difenderle.";
			link.l1.go = "noel_51";
		break;
		
		case "noel_51":
			dialog.text = "La vostra grazia è davvero ammirevole, Vice Ammiraglio! Che nobile animo! Non mi stupisce che siate rimasto qui così a lungo senza fretta di tornare a casa. Ma ci rivedremo: farò ritorno tra sei mesi. La Compagnia Francese dei Mercanti sorgerà. E quanto ai pirati, credo che esageriate un po'. In fin dei conti, abbiamo navi da guerra e capitani valorosi, come voi.";
			link.l1 = "Mi dispiace, Barone, ma sono solo un uomo, e oltre a me la Francia ha solo una nave robusta nell’arcipelago, l’‘Eclatant’. Non basterà, ci rimetteremo più di quanto potremmo mai guadagnare... Eh, tant’è, così va il mondo, vedremo di inventarci qualcosa nel frattempo... Quand’è che ve ne tornerete in Francia?";
			link.l1.go = "noel_52";
		break;
		
		case "noel_52":
			dialog.text = "Fra due settimane tornerò a Saint Christopher, e da lì farò rotta verso casa. Monsieur de Poincy mi ha dato una buona nave – una brigantino chiamata 'Favory' – e un capitano valoroso. La nave è veloce e il capitano ha molta esperienza, ma certo, con te mi sentivo più al sicuro. Ricordo i nostri viaggi nell'arcipelago, Vice Ammiraglio, fu davvero un'avventura splendida.";
			link.l1 = "Grazie per le tue gentili parole, Barone. Ebbene, pare sia giunta l’ora di separarci...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Patria_CondotierToPirates");
		break;
		
		case "noel_53":
			dialog.text = "";
			link.l1 = "Qui tutti si servono l’uno dell’altro. Il Chevalier mi ha usato nei suoi intrighi ben prima che diventassi un ufficiale della marina.";
			link.l1.go = "noel_54";
		break;
		
		case "noel_54":
			dialog.text = "E va bene così? Che ne pensi, tu?";
			link.l1 = "No. Ma il Cavaliere non mi ha lasciato scelta: o seguivo i suoi ordini, oppure mio fratello sarebbe marcito in galera fino alla fine dei suoi giorni, e il buon nome della mia famiglia sarebbe stato infangato.";
			link.l1.go = "noel_55";
		break;
		
		case "noel_55":
			dialog.text = "Orribile! Questa è pura pirateria! Aveva forse qualche ragione per tali minacce?";
			link.l1 = "Mio fratello ebbe la sventura di essere il suo uomo di fiducia. Proprio come lo sono io adesso.";
			link.l1.go = "noel_56";
		break;
		
		case "noel_56":
			dialog.text = "Dov'è tuo fratello adesso?";
			link.l1 = "Sono riuscito a liberarlo ma l’ho perso già il giorno dopo, ha scelto di non servire più nessuno d’ora in avanti.";
			link.l1.go = "noel_57";
		break;
		
		case "noel_57":
			dialog.text = "Sapevo che Poincy non era chi diceva di essere! Un lupo travestito da agnello! Vice Ammiraglio, potete fidarvi di me. Sono un uomo d’onore. E vi libererò da questo giogo del vostro ‘protettore’ se riusciremo a trovare prove concrete delle sue malefatte. Sapete nulla di questa storia torbida con Stuyvesant? Parlate senza timore, e non preoccupatevi: siete solo un soldato e dovevate eseguire gli ordini.";
			link.l1 = "Lo so. In effetti c’è una miniera a Saint-Martin. Solo che non ci trovano oro, ma sale. È molto richiesto dagli Spagnoli. Poincy non poteva commerciare con loro direttamente, così Stuyvesant faceva da mezzano.";
			link.l1.go = "noel_58";
		break;
		
		case "noel_58":
			dialog.text = "Allora Poincy e Stuyvesant sono soci in affari?";
			link.l1 = "Un tempo lo era. Dopo che hai mostrato interesse per l’ispezione della Saint-Martin, Stuyvesant ha deciso di far fuori Poincy dal gioco, intascandosi tutti i profitti della miniera di sale. Poincy non poteva parlare con nessuno... Ma Stuyvesant ha fatto male i suoi conti, come vedi.";
			link.l1.go = "noel_59";
		break;
		
		case "noel_59":
			dialog.text = "Pensi che la miniera sia ancora in funzione?";
			link.l1 = "Ne sono certo. Pare che Poincy abbia ora un nuovo compagno di traffici. E non è altri che il colonnello Doily in persona.";
			link.l1.go = "noel_60";
		break;
		
		case "noel_60":
			dialog.text = "Possiamo mostrare qualche prova al ministero?";
			link.l1 = "Hmm. Durante l’assalto alla miniera, che per inciso fu opera degli spagnoli e non degli olandesi, abbiamo preso il padrone. Si trova ancora sulla mia nave. Puoi parlargli. Se gli prometti la libertà, magari ti rivela molte cose curiose.";
			link.l1.go = "noel_61";
		break;
		
		case "noel_61":
			dialog.text = "Andiamo subito alla tua nave. Ordina che il tuo prigioniero venga portato nella tua cabina. Voglio scambiare due parole con lui.";
			link.l1 = "Va bene, andiamo.";
			link.l1.go = "exit";
			npchar.greeting = "noel_4";
			AddDialogExitQuestFunction("Patria_CondotierToCabin");
		break;
		
		case "noel_62":
			dialog.text = "Benissimo, Vice Ammiraglio. Vado a parlargli io. Restate qui, ve ne prego.";
			link.l1 = "Ma certo...";
			link.l1.go = "noel_63";
		break;
		
		case "noel_63":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "rld", "aloc1", "", -1);
			DoQuestFunctionDelay("Patria_CondotierInCabinTalk", 3.0);
		break;
		
		case "noel_64":
			dialog.text = "Ho annotato tutte le prove contro il tuo prigioniero, e lui vi ha apposto la firma. Ora dobbiamo mantenere la parola data: alla prima occasione favorevole, fermati a Cartagena e lascialo sbarcare. Ma hai sentito tutto tu stesso.\nChe canaglia, quel nostro Poincy! Ha affittato un'isola agli olandesi, vi conduceva loschi traffici e permetteva agli spagnoli di gestire la miniera! Non oso nemmeno pensare a quant’oro manca nelle casse del Re, per colpa della sua avidità!";
			link.l1 = "Saranno prove sufficienti per incastrare Poincy?";
			link.l1.go = "noel_65";
		break;
		
		case "noel_65":
			dialog.text = "Purtroppo temo che non basterà. Le prove sono importanti, ma non sufficienti. Tuttavia, non voglio che tu ti impicci in questa faccenda, per ragioni che entrambi conosciamo.";
			link.l1 = "Lo spagnolo ha accettato di testimoniare davanti alla tua commissione quando giungerà qui.";
			link.l1.go = "noel_66";
		break;
		
		case "noel_66":
			dialog.text = "Questo non accadrà prima di sei mesi, e chi può dire che ne sarà di questo spagnolo, o se riusciremo mai a trovarlo più tardi a Cartagena... Dobbiamo procurarci prove ancor più preziose. Vale a dire: una dimostrazione che la miniera continua i suoi traffici segreti e che ancora riempie le tasche del nostro caro governatore generale.";
			link.l1 = "Dunque suggerisci che salpiamo per Saint-Martin?";
			link.l1.go = "noel_67";
		break;
		
		case "noel_67":
			dialog.text = "Sì. Sai come arrivare alla miniera?";
			link.l1 = "Sì, lo voglio.";
			link.l1.go = "noel_68";
		break;
		
		case "noel_68":
			dialog.text = "Allora, di notte, tu ed io ci infileremo là dentro in punta di piedi, senza farci vedere da nessuno, e daremo un’occhiata a cosa diavolo succede là.";
			link.l1 = "Molto bene.";
			link.l1.go = "noel_69";
		break;
		
		case "noel_69":
			dialog.text = "Ma che ne sarà del Cavaliere, eh? Ora capisco perché mi accennava con tanta baldanza che fondare la Compagnia Francese di Commercio nell’Arcipelago sarebbe stato uno spreco... Certo, per lui sarebbe stato davvero una gran perdita!";
			link.l1 = "Dal momento che ora siamo alleati, Barone, ti dirò tutta la verità: Poincy mi ha chiesto... di persuaderti a non fondare la Compagnia Commerciale qui.";
			link.l1.go = "noel_70";
		break;
		
		case "noel_70":
			dialog.text = "Ah, dunque è così! Spero almeno che non t’abbia chiesto di spedirmi all’inferno a fil di spada o con una palla di piombo?";
			link.l1 = "No. Dovevi essere persuaso in altro modo.";
			link.l1.go = "noel_71";
		break;
		
		case "noel_71":
			dialog.text = "Poincy pagherà per questo, ma ora dobbiamo salpare subito per Saint-Martin. Lo spagnolo sarà portato al continente dopo. Si salpa, Vice Ammiraglio!";
			link.l1 = "Ti parrà un tantino strano salpare dall’isola proprio sulla mia nave, non credi?";
			link.l1.go = "noel_72";
		break;
		
		case "noel_72":
			dialog.text = "Non credo proprio. Non dovevi forse convincermi tu? Proprio così hai fatto, ahah! Sì, prima di salpare per l’Europa, dirò al Cavaliere che concordo con lui e che la Compagnia Commerciale non vedrà la luce. Che viva pure nella sua beata menzogna, per ora... Andiamo!";
			link.l1 = "...";
			link.l1.go = "noel_73";
		break;
		
		case "noel_73":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierToSMartin", 5.0);
		break;
		
		case "noel_74":
			dialog.text = "Guida tu, Vice Ammiraglio. La notte ci coprirà col suo manto d’ombra.";
			link.l1 = "Seguimi...";
			link.l1.go = "noel_75";
		break;
		
		case "noel_75":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.quest.Patria_Condotier_inMine.win_condition.l1 = "location";
			pchar.quest.Patria_Condotier_inMine.win_condition.l1.location = "Location_reserve_03";
			pchar.quest.Patria_Condotier_inMine.function = "Patria_CondotierInMine";
		break;
		
		case "noel_76":
			dialog.text = "(sussurrando) L’ho visto! L’ho visto! L’hai visto anche tu? Giubbe rosse! Sono soldati inglesi!";
			link.l1 = "Te l’ho già detto: adesso Poincy fa affari con il colonnello Doily.";
			link.l1.go = "noel_77";
		break;
		
		case "noel_77":
			dialog.text = "Avevi ragione. Ne ho viste abbastanza. Ora filiamo via da qui prima che ci becchino!";
			link.l1 = "D'accordo...";
			link.l1.go = "noel_78";
		break;
		
		case "noel_78":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorRunToLocator(pchar, "reload", "reload2_back", "Patria_CondotierToBeach", -1);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
		break;
		
		case "noel_79":
			dialog.text = "Vedi dove portano i 'progetti commerciali' del nostro caro Cavaliere! Gli inglesi si comportano da padroni su un'isola francese! È uno scandalo!";
			link.l1 = "Dobbiamo muoverci, o senz'altro qualcuno verrà qui. Non possiamo permetterci di farci riconoscere.";
			link.l1.go = "noel_80";
		break;
		
		case "noel_80":
			dialog.text = "Vice Ammiraglio, ho rimuginato per tutto il viaggio verso Saint-Martin e ho preso una decisione: potresti organizzarmi un incontro con Peter Stuyvesant?";
			link.l1 = "Con Stuyvesant? Ma per quale diavolo di motivo?";
			link.l1.go = "noel_81";
		break;
		
		case "noel_81":
			dialog.text = "Un vecchio socio d’affari potrebbe avere indizi importanti, e pure delle prove belle toste sul coinvolgimento dei Chevaliers. Sono certo che Stuyvesant non vede di buon occhio Poincy e cercherà vendetta, specie dopo questi ultimi accadimenti...";
			link.l1 = "Credo di sì, Barone. Personalmente non oso mettere piede nel palazzo di Stuyvesant. Sarebbe troppo rischioso per me, dopo tutto ciò che ho combinato contro di loro...";
			link.l1.go = "noel_82";
		break;
		
		case "noel_82":
			dialog.text = "Ci ho già pensato. Andremo a Curaçao, sbarcheremo in una baia lontana dalla città e manderemo il nostro spagnolo prigioniero dalla miniera con una lettera per Stuyvesant. Non ti nominerò lì, invece gli farò sapere che sto conducendo un'indagine contro Poincy o qualcosa del genere. Credo che l'olandese verrà all'appuntamento.";
			link.l1 = "Hmm. Non credo sia una buona idea. Quel vecchio lupo di Stuyvesant non è uno sprovveduto, prende ciò che può, magari ti sbatte pure in prigione e pretende un riscatto da capogiro... ma se lo convinciamo che tutto è colpa di Poincy, forse si schiererà con noi. Beh, se sei così deciso, proviamoci allora.";
			link.l1.go = "noel_83";
		break;
		
		case "noel_83":
			DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Shore40", "reload1_back", false);
			LocatorReloadEnterDisable("Shore40", "boat", false);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_LocationDisableOfficersGen("shore40", false);
			LAi_LocationDisableOfficersGen("Location_reserve_01", false);
			LAi_LocationDisableOfficersGen("Location_reserve_03", false);
			pchar.quest.Patria_CondotierCuracao.win_condition.l1 = "location";
			pchar.quest.Patria_CondotierCuracao.win_condition.l1.location = "shore22";
			pchar.quest.Patria_CondotierCuracao.function = "Patria_CondotierOnCuracao";
			AddQuestRecord("Patria", "81");
		break;
		
		case "noel_84":
			dialog.text = "Monsieur de Maure, perdonate la mia stoltezza. Avevate ragione su Stuyvesant. Avrei dovuto capire che solo una canaglia ancor più grande poteva sfidare de Poincy!";
			link.l1 = "Ah! Un milione... Poincy voleva un milione, Stuyvesant ne vuole un altro... Sembra che stiamo girando come una bussola impazzita...";
			link.l1.go = "noel_85";
		break;
		
		case "noel_85":
			dialog.text = "Di che diavolo parli, Vice Ammiraglio?";
			link.l1 = "Quando misi piede nei Caraibi, Poincy pretendeva che pagassi un milione come riscatto per mio fratello.";
			link.l1.go = "noel_86";
		break;
		
		case "noel_86":
			dialog.text = "E hai pagato davvero così tanto?";
			link.l1 = "Me lo sono guadagnato e l'ho pagato. Non in un mese, ovviamente. A dir la verità, allora ero solo un novellino di terraferma. Eppure il Chevalier non ha lasciato andare Michel.";
			link.l1.go = "noel_87";
		break;
		
		case "noel_87":
			dialog.text = "E dopo tutto questo ti sei messo al servizio di Poincy? Giuro che non ti capisco.";
			link.l1 = "Mi sono arruolato per servire la Francia e coloro che amo, non mi inchino davanti a nessun altro se non al re.";
			link.l1.go = "noel_88";
		break;
		
		case "noel_88":
			dialog.text = "Perdona, Monsieur de Maure. Ma certo, tu servi la Francia e il Re! Poincy pagherà per tutto! Persino per tutte le pene che ti ha inflitto.";
			link.l1 = "Va bene, Barone, troverò un milione da poter spendere. Sali a bordo... Risolverò questa faccenda.";
			link.l1.go = "noel_89";
		break;
		
		case "noel_89":
			DialogExit();
			//chrDisableReloadToLocation = false; //17-add
			LAi_LocationFightDisable(&Locations[FindLocation("shore22")], false);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "", 10.0);
			pchar.questTemp.Patria = "epizode_12_stivesant";
			AddQuestRecord("Patria", "83");
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("Patria_CondotierStivesantTimeOver", 0, 0, 30, false); // таймер на месяц
		break;
		
		case "noel_90":
			dialog.text = "Volevate vedermi, Vice Ammiraglio?";
			link.l1 = "Sì. Ho avuto un incontro con Stuyvesant. Ecco il suo registro.";
			link.l1.go = "noel_91";
		break;
		
		case "noel_91":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "Non ci posso credere! Vediamo un po'... (leggendo)";
			link.l1 = "...";
			link.l1.go = "noel_92";
		break;
		
		case "noel_92":
			LAi_Fade("", "");
			dialog.text = "Ecco fatto! Il nostro caro Cavaliere è spacciato. Appena il Ministro delle Finanze metterà mano su tutta questa contabilità... non oso nemmeno pensare a cosa gli succederà. Non dovremo nemmeno più cercare lo spagnolo di Cartagena. Monsieur de Maure, avete davvero pagato un milione per questo libro?";
			link.l1 = "L'ho fatto. Se avessi tentato altro, la Francia rischiava di perdere le sue colonie nei Caraibi per una guerra civile, che magari avrei anche vinto, ma che razza di ammiraglio sarei se combattessi contro la mia stessa gente.";
			link.l1.go = "noel_93";
		break;
		
		case "noel_93":
			dialog.text = "Sei davvero degno del tuo nome. Te lo giuro, Vice Ammiraglio, che lo riavrai. Sono certo che troveremo un bel gruzzolo nei forzieri di Poincy e dai suoi usurai. Ti chiedo solo di attendere sei mesi, finché non tornerò dall’Europa con una commissione.";
			link.l1 = "E non ti scordar di portare con te un reggimento di soldati ben addestrati e armati. E una nave come l’‘Eclatant’. Credo pure che il capitano dell’‘Eclatant’ si schiererà dalla nostra parte quando giungerà l’ora.";
			link.l1.go = "noel_94";
		break;
		
		case "noel_94":
			dialog.text = "Non averne dubbio, anche lui è un uomo d’onore. Ho capito che i valori morali pesano assai nelle tue decisioni. Hai fatto un gran lavoro, fidandoti di me e svergognando questo maledetto criminale di stato. Ora portami a Capsterville, dove riferirò a Poincy del buon esito della tua missione – sei riuscito a convincermi, così rinuncerò all’idea di fondare la compagnia commerciale. Forse Poincy vorrà pure ricompensarti – accetta la ricompensa a cuore leggero e non crucciarti di nulla, ché se qualcuno la merita, quello sei tu. Non ti tireranno dentro a questa storia, né il tuo nome verrà macchiato dalle malefatte del tuo superiore; anzi, dirò solo il meglio di te quando parlerò col re. Il barone Forget è uomo d’onore e di parola.";
			link.l1 = "Sono lieto, barone. Salpiamo!";
			link.l1.go = "noel_95";
		break;
		
		case "noel_95":
			DialogExit();
			chrDisableReloadToLocation = false;
			bQuestDisableMapEnter = false;//открыть карту
			Island_SetReloadEnableGlobal("Curacao", true);
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 5.0);
			pchar.questTemp.Patria = "epizode_12_baronwin";
			AddQuestRecord("Patria", "85");
			pchar.quest.Patria_CondotierBaron_win.win_condition.l1 = "location";
			pchar.quest.Patria_CondotierBaron_win.win_condition.l1.location = "Charles_town";
			pchar.quest.Patria_CondotierBaron_win.function = "Patria_CondotierBaronWin";
		break;
		
		case "noel_96":
			dialog.text = "Dunque, Vice Ammiraglio, siamo finalmente giunti. La vostra missione è conclusa, ora tocca a me. Occupatevi dei vostri affari, difendete gli interessi della Francia, come già avete fatto. Fra sei mesi questa lurida faccenda sarà finita. Vi manderò un corriere quando sarete richiesto. Addio, Monsieur de Maure, è stata una gran fortuna incontrare un uomo d’onore come voi! Il ministro e il Re sapranno di voi, ve lo prometto. E saranno solo lodi.";
			link.l1 = "Grazie, Barone. Buon viaggio!";
			link.l1.go = "noel_97";
		break;
		
		case "noel_97":
			DialogExit();
			AddQuestRecord("Patria", "86");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "OpenTheDoors", 15.0);
			SetFunctionTimerCondition("Patria_CondotierPuancieFinal", 0, 0, 1, false); // таймер
		break;
		
		case "noel_98":
			dialog.text = "Felice di rivedervi, Vice Ammiraglio. Sono qui di nuovo, come promesso. E con me - il primo assistente del Ministro delle Finanze, il Barone Olivier Bourdin.";
			link.l1 = "Dove si trova il Chevalier de Poincy?";
			link.l1.go = "noel_99";
		break;
		
		case "noel_99":
			dialog.text = "Dove dovrebbe stare, in prigione. È stato arrestato e sarà portato in Francia per l’interrogatorio e il processo. Vista la sua posizione, di certo sfuggirà all’impiccagione, ma non potrà scansare una multa salata, la degradazione e, probabilmente, la galera.";
			link.l1 = "L’arresto è avvenuto senza spargimento di sangue?";
			link.l1.go = "noel_100";
		break;
		
		case "noel_100":
			dialog.text = "Non proprio. Il Chevalier aveva qui, nella residenza, un’intera guardia di soldati fedeli. Ma noi eravamo pronti a questa faccenda già da prima.";
			link.l1 = "Ebbene, ti faccio i miei complimenti, barone! Forse ora te la vedrai con la Compagnia di Commercio francese?";
			link.l1.go = "noel_101";
		break;
		
		case "noel_101":
			dialog.text = "Io? Sì. Sua eccellenza, monsieur Bourdin, farà ritorno in Francia assieme al Cavaliere de Poincy. E voi, viceammiraglio, dovrete prepararvi a cambiamenti. Ora avete un nuovo incarico. Sua eccellenza vi dirà di più.";
			link.l1 = "...";
			link.l1.go = "noel_102";
		break;
		
		case "noel_102":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("Finansist");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "noel_103":
			dialog.text = "Monsieur de Maure! Aspetta un momento!";
			link.l1 = "Sì, Barone. Vi presto orecchio.";
			link.l1.go = "noel_104";
		break;
		
		case "noel_104":
			dialog.text = "Per quanto riguarda il milione che hai pagato allo Stuyvesant... Non ne ho parlato al ministero, così da... evitare domande, tipo come un ufficiale francese si sia ritrovato con tanto denaro tra le mani. Questo forse ti ha fatto un favore, perché avrebbero potuto chiederti di rimpinguare il tesoro del Re con le tue tasche.";
			link.l1 = "Capisco, grazie.";
			link.l1.go = "noel_105";
		break;
		
		case "noel_105":
			dialog.text = "Tutti i dobloni che si trovarono addosso a Poincy a Casterville furono sequestrati dal barone Bourdin. Ma, a quanto pare, il furfante teneva pure una riserva che gli strozzini inglesi nascondevano per lui. Parlerò con lui del recupero degli investimenti, poi troverò il modo di ricompensarti.";
			link.l1 = "Temo che non ti sarà facile strappare qualcosa dalle grinfie degli usurai inglesi.";
			link.l1.go = "noel_106";
		break;
		
		case "noel_106":
			dialog.text = "Sono d'accordo. Ma ci lavoreremo sopra, e ti terrò aggiornato sui risultati.";
			link.l1 = "Come desideri.";
			link.l1.go = "noel_107";
		break;
		
		case "noel_107":
			dialog.text = "Viceammiraglio, non avete un'aria troppo sana, o son solo i miei occhi? Eppure avete appena ottenuto il grado più alto di tutte le colonie!";
			link.l1 = "No-no, affatto... È solo che tutto è successo così all’improvviso, e sono un po’ smarrito.";
			link.l1.go = "noel_108";
		break;
		
		case "noel_108":
			dialog.text = "Non temere. Ti abituerai presto al tuo nuovo ruolo. E poi, sei già stato governatore di Saint-Martin per mezzo anno con discreto successo, quindi non sarà certo una novità per te.";
			link.l1 = "Oh, sono certo che ci farò l’abitudine. Ne ho viste di peggiori qui ai Caraibi, credimi. Me la caverò anche stavolta, suppongo.";
			link.l1.go = "noel_109";
		break;
		
		case "noel_109":
			// belamour legendary edition -->
			dialog.text = "Ebbene, sia. Inoltre, ho un'altra sorpresa per te. Son certo che ti piacerà. Ma prima ti chiedo di tornare alla residenza. Credo che qualcuno ci stia aspettando laggiù.";
			link.l1 = "Mi avete incuriosito, Monsieur Forget. Ebbene, torniamo indietro.";
			link.l1.go = "noel_110";
		break;
		
		case "noel_110":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "ToEcliatonAward", -1);
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, npchar, "", -1);
		break;
		
		case "noel_111":
			dialog.text = "Va bene, Marchese. Un vero capitano deve sempre prendersi cura prima della sua nave, giusto? Charles, ti ricordi del Marchese Hubert Dassier, capitano del vascello da guerra 'Eclatant'?";
			link.l1 = "Ma certo che ricordo! Se non fosse stato per lui, oggi sarei cibo per pesci. La più solida amicizia tra ufficiali di marina nasce quando si combatte fianco a fianco. E Monsieur Dassier si è rivelato un capitano di rara esperienza.";
			link.l1.go = "noel_112";
		break;
		
		case "noel_112":
			DialogExit();
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_17";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "noel_113":
			dialog.text = "Viceammiraglio, ho l’onore di informarvi quanto segue. Oltre alla vostra nomina a Governatore Generale ad interim delle colonie francesi dell’arcipelago, ho anche sollevato la questione della vostra nave ammiraglia.";
			link.l1 = "Ammiraglia?";
			link.l1.go = "noel_114";
		break;
		
		case "noel_114":
			dialog.text = "Esatto. Per quanto ne so, quando sei entrato al servizio della Francia, ti fu data la leggera fregata 'Gryffondor' a tua disposizione. Una nave magnifica, senza dubbio, ma adatta a un semplice ufficiale, non certo a un vice ammiraglio e ora, a un governatore generale. Tu qui rappresenti la Francia. E la tua nave ammiraglia deve essere degna di ciò. Così abbiamo deciso che la nave che ha affrontato le sue prime battaglie proprio qui nei Caraibi venga aggiunta al tuo squadrone...";
			link.l1 = "Monsieur Forget, state forse cercando di dire...";
			link.l1.go = "noel_115";
		break;
		
		case "noel_115":
			dialog.text = "D'ora in poi, l'orgoglio della Marina Francese, il vascello da guerra da 66 cannoni 'Éclatant', è a tua disposizione! Questa decisione è approvata dal re!";
			link.l1 = "Ma Barone, non posso semplicemente prendere...";
			link.l1.go = "noel_116";
		break;
		
		case "noel_116":
			dialog.text = "Puoi farlo, Charles. Non si discute oltre. In Francia, l’‘Eclatant’ è stato rinforzato apposta per te, perché, a quanto pare, qui nei Caraibi non si combatte in mare come in Europa, e dunque si pretende di più dalle singole navi. Qui tutto dipende dai numeri della nave e dall’esperienza del suo capitano. L’‘Eclatant’ ha lo scafo rinforzato, portata e equipaggio aumentati, l’armamento velico leggermente adattato per stringere il vento, e tutti i cannoni sostituiti con pezzi da quarantadue, i più poderosi che possediamo.";
			link.l1 = "Sì, ora questa nave è davvero la regina dei mari... Ma Monsieur Forget, perché il capitano di questa nave è il Marchese Hubert Dassier. Non posso strappargliela...";
			link.l1.go = "noel_117";
		break;
		
		case "noel_117":
			dialog.text = "È solo che non ti ho ancora detto che il Marchese in persona ha espresso un forte desiderio di servire sotto il tuo comando... Monsieur Dassier?";
			link.l1 = "...";
			link.l1.go = "noel_118";
		break;
		
		case "noel_118":
			DialogExit();
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_19";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "noel_119":
			dialog.text = "Sì, Monsieur Dassier, credo che non vi tratterremo oltre.";
			link.l1 = "...";
			link.l1.go = "noel_120";
		break;
		
		case "noel_120":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload1");
			sld = characterFromId("Ecliaton_Cap");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "reload", "reload1", "EcliatonAwardNoelTalk", -1);
		break;
		
		case "noel_121":
			dialog.text = "Tra noi, Charles, ti consiglierei caldamente di tenere il Marchese al tuo servizio. Ti assicuro che non troverai mai un capitano di tale esperienza.";
			link.l1 = "Credetemi, barone, ebbi l’onore di vederlo coi miei occhi durante le battaglie contro la Spagna e l’Olanda. Monsieur Dassier è davvero un ufficiale di gran valore, e per di più un mio buon compare.";
			link.l1.go = "noel_122";
		break;
		
		case "noel_122":
			dialog.text = "Ebbene, ora concedetemi di congedarmi, Vostra Eccellenza, Governatore Generale! Gli affari non aspettano: la fondazione di una compagnia mercantile è appena cominciata. A presto rivederci!";
			link.l1 = "Buona fortuna, Monsieur Forget. E che il vento ti sia favorevole nei tuoi traffici!";
			link.l1.go = "noel_123";
		break;
		
		case "noel_123":
			DialogExit();
			// ставим Эклятон после апгрейда в Европе
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_24";
			sld.DeckDialogNode = "ecliaton_cap_24";
			sld.Ship.Type = GenerateShipExt(SHIP_ECLIATON, true, sld);
			SetBaseShipData(sld);
			sld.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS42;
			UpgradeShipFull(sld);
			/* UpgradeShipParameter(sld, "SpeedRate");
			UpgradeShipParameter(sld, "TurnRate");
			UpgradeShipParameter(sld, "WindAgainstSpeed");
			UpgradeShipParameter(sld, "HP");
			UpgradeShipParameter(sld, "MaxCrew");
			sld.ship.HP = 11880; */
			sld.Ship.name = "Ecliaton";
			SetCrewQuantityFull(sld);
			AddCrewMorale(sld, 100);
			ChangeCrewExp(sld, "Sailors", 100);
			ChangeCrewExp(sld, "Cannoners", 100);
			ChangeCrewExp(sld, "Soldiers", 100);
			SetCharacterGoods(sld, GOOD_BALLS, 6000);
			SetCharacterGoods(sld, GOOD_GRAPES, 2000);
			SetCharacterGoods(sld, GOOD_KNIPPELS, 2000);
			SetCharacterGoods(sld, GOOD_BOMBS, 5000);
			SetCharacterGoods(sld, GOOD_FOOD, 4000);
			SetCharacterGoods(sld, GOOD_POWDER, 12000);
			SetCharacterGoods(sld, GOOD_WEAPON, 900);
			SetCharacterGoods(sld, GOOD_MEDICAMENT, 900);
			SetCharacterGoods(sld, GOOD_RUM, 200);
			SetCharacterGoods(sld, GOOD_PLANKS, 100);
			SetCharacterGoods(sld, GOOD_SAILCLOTH, 100);
			Group_AddCharacter("Ecliaton_group", "Ecliaton_Cap");
			Group_SetGroupCommander("Ecliaton_group", "Ecliaton_Cap");
			Group_SetAddress("Ecliaton_group", "Nevis", "quest_ships", "quest_ship_1");
			Group_SetTaskNone("Ecliaton_group");
			Group_LockTask("Ecliaton_group");
			
			bDisableFastReload = false;//открыть переход
			bQuestDisableMapEnter = false;//открыть карту
			AddQuestRecord("Patria", "90");
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			pchar.questTemp.Patria = "end"; // конец линейки
			pchar.questTemp.Patria.GenGovernor = "true"; // Шарль генерал-губернатор
			ChangeCharacterAddressGroup(npchar, "none", "", "");
			DoQuestReloadToLocation("Charles_Town", "reload", "reload3", "OpenTheDoors");
		break;
		// <-- legendary edition
		
		case "noel_final":
			dialog.text = "Permettetemi di esprimere la mia più sincera gratitudine, viceammiraglio! Mi avete salvato la vita liberandomi da quei dannati pirati. Vi ringrazio, così come ringrazio Philippe de Poincy. Devo ammettere che ho completamente sbagliato a giudicarlo, e vi chiedo perdono per questo. Voi e il Cavaliere avevate ragione: la Compagnia Francese delle Indie avrà un mare di guai qui, e pare proprio che non faremo altro che perdere denaro in queste acque.\nSolo uomini esperti come Poincy e soldati coraggiosi come voi possono resistere a questi lupi che infestano ogni isola. Devo recarmi al palazzo e poi partirò per l’Europa il prima possibile, per dimenticare questo incubo.";
			link.l1 = "Sono lieto che tutto sia finito bene, Barone. Addio!";
			link.l1.go = "noel_final_1";
		break;
		
		case "noel_final_1":
			DialogExit();
			AddQuestRecord("Patria", "76");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "OpenTheDoors", 15.0);
			SetFunctionTimerCondition("Patria_CondotierPuancieFinal", 0, 0, 1, false); // таймер
		break;
		
		// капитан Эклятона
		case "ecliaton_cap":
			dialog.text = TimeGreeting()+", monsieur. Cosa vi porta sul ponte dell'‘Eclatant’?";
			link.l1 = TimeGreeting()+", monsieur. Permettete che mi presenti – Capitano Charles de Maure, vengo dal Governatore Generale delle colonie francesi nell’arcipelago, il Cavaliere de Poincy. Ho ricevuto l’ordine di prendere la vostra nave nella mia squadra e sotto il mio comando. Ecco la lettera...";
			// belamour legendary edition фикс проверки мундира с мушкетом
			if(IsUniformEquip()) link.l1.go = "ecliaton_cap_1";
			else link.l1.go = "ecliaton_cap_no";
		break;
		
		case "ecliaton_cap_no":
			dialog.text = "Dev’esserci un qualche malinteso, monsieur. State salendo a bordo di una nave di linea della marina francese, ed io prendo ordini solo da chi serve la Real Marina. Non vedo su di voi segni né insegne di quella flotta. Forse avete confuso la nostra nave con un’altra.";
			link.l1 = "Ma...";
			link.l1.go = "ecliaton_cap_no_1";
		break;
		
		case "ecliaton_cap_no_1":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_no_2";
		break;
		
		case "ecliaton_cap_no_2":
			if(IsUniformEquip())
			{
				dialog.text = "Ah, non ti avevo nemmeno riconosciuto in questa divisa, Capitano. Allora, fammi vedere la tua lettera, voglio dare un’occhiata al contenuto.";
				link.l1 = "Ecco.";
				link.l1.go = "ecliaton_cap_1";
			}
			else
			{
				dialog.text = "Abbiamo già discusso tutto, monsignore...";
				link.l1 = "Hmm...";
				link.l1.go = "ecliaton_cap_no_1";
			}
		break;
		
		case "ecliaton_cap_1":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "Vediamo un po'... (legge) Interessante. Dunque, io e la mia nave saremo ai tuoi ordini, Capitano de Maure?";
			link.l1 = "Questo è l’ordine del Governatore Generale.";
			link.l1.go = "ecliaton_cap_2";
		break;
		
		case "ecliaton_cap_2":
			dialog.text = "Sì, sì, gli ordini non si discutono. Molto bene. Permettetemi di presentarmi: sono il Marchese Hubert Dassier, Capitano del vascello di linea francese da 66 cannoni, l’‘Eclatant’, insieme a quest’equipaggio ben addestrato, e vi giuro sul mio onore che questa è una delle migliori navi che la Francia abbia mai avuto.";
			link.l1 = "Mi fa piacere sentirlo, perché il compito affidatoci dal Governatore Generale richiederà una buona conoscenza di navigazione e artiglieria.";
			link.l1.go = "ecliaton_cap_3";
		break;
		
		case "ecliaton_cap_3":
			dialog.text = "Mi svelerai i dettagli di questa prossima impresa?";
			link.l1 = "Certo. Salperemo verso l’isola spagnola di Trinidad, che si trova circa a una settimana di navigazione a sud-est da qui. Daremo l’assalto di sorpresa al forte che protegge la colonia di San Jose e lo ridurremo in cenere. Poi, discuteremo con gli spagnoli la nostra ricompensa per l’ultimo attacco al villaggio francese di Saint-Pierre.";
			link.l1.go = "ecliaton_cap_4";
		break;
		
		case "ecliaton_cap_4":
			dialog.text = "Capisco. Quando salperemo?";
			link.l1 = "Il prima possibile. Dobbiamo finire questo incarico entro un mese, quindi abbiamo tempo a iosa.";
			if (GetCompanionQuantity(pchar) > 4) link.l1.go = "ecliaton_cap_5_1";
			else link.l1.go = "ecliaton_cap_5";
		break;
		
		case "ecliaton_cap_5":
			dialog.text = "D'accordo, Capitano de Maure. Salperemo al vostro ordine.";
			link.l1 = "";
			link.l1.go = "ecliaton_cap_6";
		break;
		
		case "ecliaton_cap_6":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_wait";
			npchar.DeckDialogNode = "ecliaton_cap_wait";
			Patria_AddEcliaton();
		break;
		
		case "ecliaton_cap_wait":
			dialog.text = "Avete ordini da impartire, o magari qualche domanda, Capitano de Maure?";
			link.l1 = "Non ancora...";
			link.l1.go = "ecliaton_cap_wait_1";
		break;
		
		case "ecliaton_cap_wait_1":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_wait";
			npchar.DeckDialogNode = "ecliaton_cap_wait";
		break;
		
		case "ecliaton_cap_5_1":
			dialog.text = "Ma, Capitano de Maure, prima dovete sfoltire la vostra squadra – la mia nave non può unirsi a voi, altrimenti la flottiglia sarebbe troppo numerosa.";
			link.l1 = "Eh. Hai ragione. Lascio una nave qui in porto.";
			link.l1.go = "ecliaton_cap_5_2";
		break;
		
		case "ecliaton_cap_5_2":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_5_3";
		break;
		
		case "ecliaton_cap_5_3":
			if (GetCompanionQuantity(pchar) > 4)
			{
				dialog.text = "Non hai ancora ridotto la tua squadra, monsieur?";
				link.l1 = "Sì, sì, ricordo, ci sto lavorando.";
				link.l1.go = "ecliaton_cap_5_2";
			}
			else
			{
				dialog.text = "Dunque, l’‘Eclatant’ è pronta a unirsi alla tua squadra, monsieur.";
				link.l1 = "Allora vado alla mia nave, e tu dovresti prepararti a salpare.";
				link.l1.go = "ecliaton_cap_5";
			}
		break;
		
		case "ecliaton_cap_7":
			dialog.text = "Saluti, Commodoro. Ci attende un'altra battaglia?";
			link.l1 = "In verità, sì. Ancora una volta uniremo le forze. Andremo all’assalto di Philipsburg. Il Governatore Generale ci ha ordinato di scacciare gli olandesi da Saint-Martin.";
			link.l1.go = "ecliaton_cap_9";
			link.l2 = "Lo faremo, Capitano, ma tra poco. Vi avviserò io. L’'Eclatant' deve essere pronta a salpare in ogni momento.";
			link.l2.go = "ecliaton_cap_8";
		break;
		
		case "ecliaton_cap_8":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_7";
			npchar.DeckDialogNode = "ecliaton_cap_7";
		break;
		
		case "ecliaton_cap_9":
			dialog.text = "Tutto è chiaro. Sarà una missione dura, monsignore. Da quel che ho sentito, il forte di Philipsburg è zeppo di cannoni.";
			link.l1 = "Ne son certo, compare, ma ce la caveremo. Preparati a salpare, presto molliamo gli ormeggi.";
			link.l1.go = "ecliaton_cap_10";
		break;
		
		case "ecliaton_cap_10":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_wait";
			npchar.DeckDialogNode = "ecliaton_cap_wait";
			Patria_BastionAddEcliaton();
		break;
		
		case "ecliaton_cap_11":
			dialog.text = "Felice di vederti sul ponte dell'‘Eclatant’, viceammiraglio! Quali sono i tuoi ordini?";
			link.l1 = "Preparate l’‘Éclatant’ per la partenza. Prima veleggeremo verso le coste della Giamaica, poi, insieme allo squadrone del colonnello D’Oyley, assalteremo Curaçao.";
			link.l1.go = "ecliaton_cap_13";
			link.l2 = "Ci saranno ordini, Capitano, ma più tardi. Vi avviserò io. L’‘Eclatant’ deve esser pronta a salpare in ogni momento.";
			link.l2.go = "ecliaton_cap_12";
		break;
		
		case "ecliaton_cap_12":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_11";
			npchar.DeckDialogNode = "ecliaton_cap_11";
		break;
		
		case "ecliaton_cap_13":
			dialog.text = "L’‘Eclatant’ e il suo equipaggio sono pronti, Vice Ammiraglio!";
			link.l1 = "Eccellente. Allora salpiamo senza indugio.";
			link.l1.go = "ecliaton_cap_14";
		break;
		
		case "ecliaton_cap_14":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_wait";
			npchar.DeckDialogNode = "ecliaton_cap_wait";
			Patria_CuracaoAddEcliaton();
		break;
		
		// belamour legendary edition -->
		case "ecliaton_cap_15":
			dialog.text = "Perdonatemi, signori, non ho potuto unirmi a voi prima, ero occupato a dare ordini sulla nave. Già temevo d’esser giunto tardi, ché non vi ho trovati alla residenza, e così stavo per far ritorno a bordo...";
			link.l1 = "...";
			link.l1.go = "ecliaton_cap_16";
		break;
		
		case "ecliaton_cap_16":
			DialogExit();
			Lai_SetPlayerType(pchar);
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_111";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "ecliaton_cap_17":
			dialog.text = "È stato un onore combattere al vostro fianco, Monsieur de Maure! Devo dire che di rado mi capita d’incontrare ufficiali tanto capaci e abili come voi. Son certo che io stesso non sarei riuscito a ridurre quel forte della colonia spagnola di Trinidad così in fretta!";
			link.l1 = "Vi sottovalutate, Monsieur Dassier. Ce la siamo cavata insieme.";
			link.l1.go = "ecliaton_cap_18";
		break;
		
		case "ecliaton_cap_18":
			DialogExit();
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_113";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "ecliaton_cap_19":
			dialog.text = "Esatto. Benché io sia un marchese, resto un uomo di mare. Per me, questo arcipelago dei Caraibi è ancora nuovo, inesplorato, pieno di avventure che mi chiamano. L’ultima volta che vi misi piede fu solo per pochi mesi, ma una volta tornato in Europa, il richiamo di queste terre non mi diede pace. Vorrei servire la nostra Patria proprio qui. Tu poi, sei un capitano di grande talento ed esperienza: ti sei guadagnato il mio rispetto sincero e la mia amicizia. Sarebbe un vero onore servire sotto il tuo comando, Vice Ammiraglio!";
			link.l1 = "Ebbene, non posso e, per di più! - Non voglio rifiutarti, Monsieur Dassier!";
			link.l1.go = "ecliaton_cap_20";
		break;
		
		case "ecliaton_cap_20":
			dialog.text = "Capisco anche che l’Eclatant sia ora la tua nave ammiraglia, quindi comprenderò perfettamente se deciderai di assumerne il comando personalmente. In tal caso, puoi lasciarmi come tuo ufficiale, affidarmi un’altra nave, o semplicemente sollevarmi dall’incarico – Monsieur Forget mi ha gentilmente promesso che in tal caso mi troverebbe una posizione degna nella flotta della Compagnia Francese delle Indie Occidentali.";
			link.l1 = "Ti assicuro, amico mio, che non si arriverà a tanto. Sei uno dei migliori capitani che abbia mai incontrato, e con te al mio fianco saremo inarrestabili.";
			link.l1.go = "ecliaton_cap_21";
		break;
		
		case "ecliaton_cap_21":
			dialog.text = "Ti ringrazio per le lusinghiere parole sulle mie capacità. E ancora una cosa, Vice Ammiraglio. Non so quanto sia grande la tua squadra al momento, quindi, per sicurezza, ti aspetterò sul ponte di comando dell’Eclatant, ormeggiato al molo di Capsterville. Quando deciderai di prendere la nave sotto il tuo comando – fammi solo sapere.";
			link.l1 = "Molto bene, Monsieur Dassier.";
			link.l1.go = "ecliaton_cap_22";
		break;
		
		case "ecliaton_cap_22":
			dialog.text = "Allora, chiedo il permesso di congedarmi. Vice Ammiraglio, Barone...";
			link.l1 = "A presto, Monsieur Dassier.";
			link.l1.go = "ecliaton_cap_23";
		break;
		
		case "ecliaton_cap_23":
			DialogExit();
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_119";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
	
		case "ecliaton_cap_24":
			dialog.text = "Vice Ammiraglio, benvenuto a bordo. Desiderate prendere l’Eclatant sotto il vostro comando?";
			if (GetCompanionQuantity(pchar) > 4)
			{
				
				link.l1 = "Non ancora, Marchese. Aspetta ordini.";
				link.l1.go = "ecliaton_cap_24_1";
			}
			else
			{
				link.l1 = "Sì, Marchese, vi chiedo di unirvi al mio squadrone. Questa splendida nave sarà il simbolo della grandezza e della potenza di Francia nei Caraibi!";
				link.l1.go = "ecliaton_cap_25";
			}
		break;
		
		case "ecliaton_cap_24_1":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_24";
			npchar.DeckDialogNode = "ecliaton_cap_24";
		break;
		
		case "ecliaton_cap_25":
			dialog.text = "Non potrei essere più d'accordo, Vostra Eccellenza!";
			link.l1 = "... Orsù, vediamo di che pasta siamo fatti davvero!";
			link.l1.go = "ecliaton_cap_26";
		break;
		
		case "ecliaton_cap_26":
			DialogExit();
			DeleteAttribute(npchar, "ShipHideImmortal");
			SetCharacterRemovable(npchar, true);
			npchar.CompanionEnemyEnable = true; 
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			npchar.Dialog.CurrentNode = "hired";
			npchar.DeckDialogNode = "hired";
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.Payment = true;
			npchar.loyality = MAX_LOYALITY;
			npchar.OfficerWantToGo.DontGo = true;
			
			// удаление группы Эклятона, иначе клон-призрак
			pchar.quest.Patria_EcliatonDelGroup.win_condition.l1 = "ExitFromSea";
			pchar.quest.Patria_EcliatonDelGroup.function = "Patria_EcliatonDelGroup";
		break;
		// <-- legendary edition
		
		// д'Ойли на Антигуа
		case "doily":
			if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "end" && colonies[FindColony("Pirates")].nation == PIRATE)
			{
				PlaySound("Voice\English\LE\Doily\Edvard_Doily_01.wav");
				dialog.text = "Oh, che incontro! Non è forse il Capitano Charles de Maure in persona?! Ho sentito dire che ora hai un incarico nella marina francese. Che sorpresa, considerando per chi 'lavoravi' prima, diciamo così...";
				link.l1 = "Salute a voi, signore. Parlate forse della faccenda dell’Isla Tesoro? Ah, non sono stato io a scrivere le leggi inglesi, secondo cui l’isola doveva passare all’erede dell’esploratore che la scoprì, come da suo testamento. Dunque, io non ho colpa alcuna; ho solo aiutato la signorina Sharp a ottenere ciò che le spettava di diritto.";
				link.l1.go = "doily_1";
			}
			else
			{
				dialog.text = TimeGreeting()+", Capitano. Suppongo che il rappresentante della marina francese sia approdato ad Antigua con uno scopo importante, vero?";
				link.l1 = "Proprio così, signore. Mi manda qui il Governatore Generale delle colonie francesi, Philippe de Poincy. Saint-Christopher è assediata dalle squadre navali spagnole e olandesi. Il Cavaliere chiede aiuto a voi e anche a sir Jonathan Fox. Ecco la sua lettera per voi, colonnello.";
				link.l1.go = "doily_3";
			}
		break;
		
		case "doily_1":
			dialog.text = "Mi chiedo, Capitano, quant’oro hai racimolato con tutto questo? Immagino parecchio, visto che sei riuscito a ingaggiare quel furfante di Loxley, che non si vende certo a buon mercato. Scommetto che i baroni della pirateria ti passano la loro parte per tenere l’isola sotto il tuo controllo. Sappiamo entrambi che Helen Sharp è solo una maschera.";
			link.l1 = "Colonnello, sappiamo entrambi che i baroni pirati agiscono perlopiù negli interessi dell’Inghilterra, anche se non ufficialmente... Senza di loro, resistere all’egemonia spagnola in queste acque sarebbe una bella impresa, non trova? Da un punto di vista politico, che la Fratellanza della Costa si sia tenuta l’isola tutta per sé forse è stato persino più vantaggioso che se Isla Tesoro fosse divenuta una base navale inglese...";
			link.l1.go = "doily_2";
		break;
		
		case "doily_2":
			dialog.text = "Questo è forse vero, Capitano, ma... sia come sia. Suppongo che siete giunto ad Antigua con uno scopo importante, vero? Forse ha a che fare col fatto che i rapporti tra due ex alleati – Francia e Olanda – si sono assai incrinati?";
			link.l1 = "Proprio così. Sono stato mandato dal governatore generale delle colonie francesi, Philippe de Poincy. Saint-Christopher è sotto assedio dalla marina spagnola e olandese. Il Cavaliere chiede il vostro aiuto. Ecco la sua lettera per voi, colonnello.";
			link.l1.go = "doily_3";
		break;
		
		case "doily_3":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "Vediamo un po'... (leggendo)";
			link.l1 = "";
			link.l1.go = "doily_3_1";
		break;
		
		case "doily_3_1":
			LAi_Fade("", "");
			dialog.text = "Hmm... davvero intrigante! Capitano, il vostro comandante sa come stuzzicare la mia curiosità, non è poi così strano che lo chiamino una vecchia volpe. Avremmo dovuto farlo tempo fa, invece di perdere tempo a blandire gli olandesi. Sappiamo fin troppo bene cosa rappresentano la Compagnia Olandese e il loro Direttore. Ebbene, credo proprio che in questa situazione non dovremmo negarci d'aiutare la Casterville assediata, e di uomini ne abbiamo in abbondanza per farlo.\nQuali sono i numeri e i tipi di navi nei loro squadroni, Capitano?";
			link.l1 = "Ne ho contate sei: una nave di linea di terzo rango con ottanta cannoni e cinque vascelli di quarto rango. Potrebbero avere anche fregate e galeoni.";
			link.l1.go = "doily_4";
		break;
		
		case "doily_4":
			dialog.text = "Uhm... Possiamo schierare la nostra squadra, composta da un vascello di primo rango con cento cannoni, due navi di quarto rango e una fregata pesante, contro la loro.";
			if (!CheckAttribute(pchar, "questTemp.Patria.FailLugger"))
			{
				link.l1 = "Signore, abbiamo pure una nave da guerra con 66 cannoni, l’‘Eclatant’, che veleggia in soccorso della difesa di Saint-Christopher dalle coste di Guadalupa.";
				link.l1.go = "doily_5";
			}
			else
			{
				link.l1 = "Una nave di primo rango sarà di gran valore nella battaglia che ci attende.";
				link.l1.go = "doily_5_1";
			}
		break;
		
		case "doily_5":
			dialog.text = "Perfetto. In tal caso, siamo ben fuori dalla portata dei cannoni nemici. La vittoria sarà nostra.";
			link.l1 = "E non scordate la mia nave, signore. Una battaglia del genere non me la perdo di certo, non ci pensate nemmeno.";
			link.l1.go = "doily_6";
		break;
		
		case "doily_5_1":
			dialog.text = "Questo è vero. Con l'aiuto della fortezza di Casterville, la vittoria sarà nostra.";
			link.l1 = "E non scordatevi della mia nave, signore. Non ho alcuna intenzione di perdermi una simile battaglia, neppure ci pensate.";
			link.l1.go = "doily_6";
		break;
		
		case "doily_6":
			dialog.text = "Ma certo, monsieur de Maure. In ogni caso, le storie sulle vostre doti di navigazione risuonano per tutto l’arcipelago. La vostra ammiraglia guiderà lo squadrone.";
			if (GetCompanionQuantity(pchar) > 1)
			{
				link.l1 = "Metterò in attesa il resto delle navi della mia squadra, poi tornerò da te e ci lanceremo in soccorso degli assediati.";
				link.l1.go = "doily_7_1";
			}
			else
			{
				link.l1 = "Preparerò la mia nave senza indugio, e salperemo subito in soccorso degli assediati.";
				link.l1.go = "doily_8";
			}
		break;
		
		case "doily_7_1":
			DialogExit();
			npchar.dialog.currentnode = "doily_7_2";
		break;
		
		case "doily_7_2":
			dialog.text = "Allora, sei pronto a salpare?";
			if (GetCompanionQuantity(pchar) > 1)
			{
				link.l1 = "Aspetta solo un attimino, signore.";
				link.l1.go = "doily_7_1";
			}
			else
			{
				link.l1 = "Sì, signore.";
				link.l1.go = "doily_8";
			}
		break;
		
		case "doily_8":
			dialog.text = "Allora cominciamo, e che Dio ci assista!";
			link.l1 = "...";
			link.l1.go = "doily_9";
		break;
		
		case "doily_9":
			DialogExit();
			npchar.dialog.currentnode = "doily_10";
			chrDisableReloadToLocation = true;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			AddQuestRecord("Patria", "42");
			Patria_SiegeAddEngSquadron();
		break;
		
		case "doily_10":
			dialog.text = "Avete ancora qualche domanda, signore?";
			link.l1 = "No, colonnello...";
			link.l1.go = "doily_11";
		break;
		
		case "doily_11":
			DialogExit();
			npchar.dialog.currentnode = "doily_10";
			npchar.DeckDialogNode = "doily_10";
		break;
		
		case "doily_12":
			PlaySound("Voice\English\LE\Doily\Edvard_Doily_02.wav");
			dialog.text = "Prendi la lettera per lo Stuyvesant, signore. Se non sai chi sono, lascia che mi presenti: Colonnello Edward Doily, governatore di Port-Royal e comandante di questa spedizione!\nA dirti la verità, ho una gran voglia di spazzar via il covo di banditi chiamato Willemstad. La più infame, falsa e spregevole organizzazione dei Caraibi, nota come la Compagnia Olandese delle Indie Occidentali, che crede che tutto il commercio nell'Arcipelago sia solo affar loro, e che assolda mascalzoni come Jacob van Berg e altri filibustieri per catturare e affondare le navi dei mercanti inglesi...";
			link.l1 = "...";
			link.l1.go = "doily_13";
		break;
		
		case "doily_13":
			dialog.text = "Sono qui per porre fine a queste infamie e, per vostra fortuna, propongo la via diplomatica. Per ora... Ma se il direttore di questa ignobile congrega non si presenterà per le trattative, manderò il suo losco affare in malora. Dopo l’assalto alla città, non resterà che cenere, e tutta la polvere che troveremo finirà nelle segrete del vostro forte, pronta a saltare in aria. Lo stesso destino toccherà alle vostre piantagioni, e lo Stuyvesant in persona penderà dal pennone della mia nave ammiraglia...";
			link.l1 = "...";
			link.l1.go = "doily_14";
		break;
		
		case "doily_14":
			dialog.text = "Ti servirà ben più d’un anno per ricostruire la tua colonia, e allora non avrai tempo per i tuoi intrighi e maneggi. Riferisci al tuo 'Signor Direttore' ogni parola che ho appena detto, e non pensare che siano scherzi o vane minacce. La mia pazienza è finita, dunque sii ben chiaro su ciò che intendo. Mi hai capito, ufficiale?!";
			link.l1 = "Tutto è chiarissimo, signor Colonnello.";
			link.l1.go = "doily_15";
		break;
		
		case "doily_15":
			dialog.text = "Benissimo. Allora vattene. Ti concedo esattamente un giorno per rifletterci su. Se tra ventiquattr'ore Peter Stuyvesant non sarà qui, dritto davanti a me come lo sei tu adesso, potrà incolpare solo sé stesso.";
			link.l1 = "...";
			link.l1.go = "doily_16";
		break;
		
		case "doily_16":
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("Doily_land");
			sld.dialog.currentnode = "doily_17";
			LAi_SetActorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "doily_17":
			dialog.text = "Penso che quel cane rognoso di Stuyvesant verrà qui. E se non lo farà – potrà solo prendersela con sé stesso!";
			link.l1 = "...";
			link.l1.go = "doily_17_1";
		break;
		
		case "doily_17_1":
			DialogExit();
			npchar.dialog.currentnode = "doily_17";
			AddQuestRecord("Patria", "63");
			Patria_CuracaoParlamenterGo();
		break;
		
		case "doily_18": // д'Ойли на берегу
			dialog.text = "Hai fatto un buon lavoro con il forte, monsieur de Maure. Ora ci avvicineremo alle porte della città via terra. Porterò i cannoni da qui, il percorso è più corto e agevole, mentre tu sbarcherai la tua compagnia di marines al Capo Santa-Maria e avanzerai verso Willemstad. Se incontrerai dei nemici lungo la strada, sai già cosa fare. Nessuno deve restare alle nostre spalle.";
			link.l1 = "Ma certo, colonnello. Vi raggiungerò alle porte!";
			link.l1.go = "doily_19";
		break;
		
		case "doily_19":
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			AddQuestRecord("Patria", "61");
			npchar.dialog.currentnode = "doily_10";
			Patria_CuracaoGotoMarch();
		break;
		
		case "doily_20":
			dialog.text = "Ebbene, pare che la nostra impresa si sia conclusa a gonfie vele. Complimenti, Capitano! Oh, perdoni – Vice Ammiraglio! Torniamo alle navi. Darò ordine ai miei uomini di stare all’erta – quel babbeo di Stuyvesant difficilmente oserà attaccarci durante la ritirata, ma meglio non abbassare la guardia.";
			link.l1 = "Sono certo che gli olandesi non oseranno infrangere un trattato appena siglato.";
			link.l1.go = "doily_21";
		break;
		
		case "doily_21":
			dialog.text = "È stato un piacere fare affari con voi, monsieur de Maure. Ho la sensazione che ci rivedremo ancora a Port-Royal o Capsterville.";
			link.l1 = "Senza dubbio, colonnello. Ora, ordiniamo ai nostri uomini di ritirarsi.";
			link.l1.go = "doily_22";
		break;
		
		case "doily_22":
			DialogExit();
			AddQuestRecord("Patria", "64");
			Patria_CuracaoClear();
		break;
		
		case "doily_23":
			dialog.text = "Pare che gli olandesi abbiano finalmente capito che non hanno alcuna possibilità di avvicinarsi a noi dal forte su quel sentiero stretto sotto il fuoco dei nostri cannoni. E quelli bloccati in città non rischieranno di uscire, a meno che non siano completamente impazziti. Ora semineremo un po’ di panico: bombardiamo la città con i nostri cannoni. I miei uomini sulla nave lo vedranno e faranno finta di prepararsi allo sbarco. Dopo un’ora o due, Stuyvesant si caccherà addosso e sarà pronto a mandare gli ambasciatori per trattare la tregua.";
			link.l1 = "Tutto sta andando secondo i nostri piani, colonnello! Diamoci dentro!";
			link.l1.go = "doily_24";
		break;
		
		case "doily_24":
			DialogExit();
			Patria_CuracaoTownBombing();
		break;
		
		// голландский парламентёр под стенами Виллемстада
		case "holoff":
			dialog.text = "Sono giunto qui per avviare le trattative. Quali sono le vostre richieste?";
			link.l1 = "Esigiamo un incontro col Direttore della Compagnia, Peter Stuyvesant. Vogliamo discutere del fatto che, per colpa della sua compagnia e sua personale, Willemstad si trova ora sull’orlo della rovina.";
			link.l1.go = "holoff_1";
		break;
		
		case "holoff_1":
			dialog.text = "Benissimo, informerò il signor Stuyvesant di questa faccenda e organizzeremo un passaggio sicuro in città per la vostra delegazione...";
			link.l1 = "E per quanto riguarda una via d’uscita sicura?";
			link.l1.go = "holoff_2";
		break;
		
		case "holoff_2":
			dialog.text = "Non capisco, signor mio?";
			link.l1 = "Ho detto: ci organizzerai una via d’uscita sicura dalla città? Non ne sono affatto certo. Temo che il signor Stuyvesant possa benissimo decidere di far prigionieri i nostri emissari. Perciò, invito il signor Stuyvesant a venire qui di persona per le trattative.";
			link.l1.go = "holoff_3";
		break;
		
		case "holoff_3":
			dialog.text = "Ma...";
			link.l1 = "Ufficiale, qui siamo noi a dettare le condizioni. La tua flotta è stata annientata, la guarnigione isolata dalla città, e sfonderemo le difese di Willemstad come una fregata che trapassa una scialuppa, se decidiamo di assaltare la città. Ora riceverai una lettera per il signor Stuyvesant, e gliela consegnerai insieme al nostro invito...";
			link.l1.go = "holoff_4";
		break;
		
		case "holoff_4": // перекидываем pchar на офицера и говорим с д'Ойли
			DialogExit();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Curacao_parlamenter_1"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Doily_land");
			sld.dialog.currentnode = "doily_12";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			bDisableCharacterMenu = true;//лоченые интерфейсы
		break;
		
		// офицер-испанец на маяке Тринидада
		case "SanJoseSpanish":
			dialog.text = "Allora, Capitano, avete convocato gli ambasciatori della tregua perché volete imporre le vostre condizioni?";
			link.l1 = "Hai perfettamente ragione, signore. Permettimi di spiegarti brevemente il motivo della mia venuta a Trinidad – è la nostra risposta al tuo recente attacco a Saint-Pierre. Hai devastato la città a dovere, e ora sarai costretto a risarcirla. Il prezzo del risarcimento è di trecentomila Peso. E non è poi così tanto, se si pensa alle infamie che i tuoi soldati hanno commesso sulla Martinica.";
			link.l1.go = "SanJoseSpanish_1";
		break;
		
		case "SanJoseSpanish_1":
			dialog.text = "Perdonami, señor, ma che c'entra San Jose con Saint-Pierre? Perché la nostra colonia deve pagare?";
			link.l1 = "Poiché gli assalitori erano spagnoli, non olandesi né inglesi. Dunque, presenterete il conto a Providence per Don de Mendosa, insieme ai miei più cordiali saluti. Come potete immaginare, se rifiuterete di pagare il risarcimento, ordinerò ai miei uomini di sbarcare, e allora San Jose perderà assai di più. Sono certo che il governatore della vostra colonia farà la scelta giusta. Avete un giorno per rispondere. Vi auguro ogni bene, señores.";
			link.l1.go = "SanJoseSpanish_2";
		break;
		
		case "SanJoseSpanish_2":
			DialogExit();
			npchar.dialog.currentnode = "SanJoseSpanish_3";
			Patria_SanJoseMayakSpanishGo();
		break;
		
		case "SanJoseSpanish_3":
			dialog.text = "";
			link.l1 = "Dunque, se ho capito bene, il governatore ha preso la decisione giusta?";
			link.l1.go = "SanJoseSpanish_4";
		break;
		
		case "SanJoseSpanish_4":
			AddMoneyToCharacter(pchar, 300000);
			dialog.text = "Prendi le tue trecentomila monete e sparisci dalla nostra colonia.";
			link.l1 = "Eccellente, signori. Vi assicuro – questa era la via migliore. Spero che questo dissuada il Don de Mendosa e gli altri dall’attaccare le nostre colonie. Non dimenticate di mandare il messaggio a Providence e a lui di persona. Vi auguro ogni bene, gentiluomini.";
			link.l1.go = "SanJoseSpanish_5";
		break;
		
		case "SanJoseSpanish_5":
			DialogExit();
			Patria_SanJoseMayakSpanishFin();
		break;
		
		// вестовой на 5 задание
		case "fraofficer":
			dialog.text = "Capitano Charles de Maure, permettetemi di riferire: il Cavaliere Philippe de Poincy desidera farvi sapere che il Barone Noel Forget è pronto a salpare per Saint-Martin e vi aspetterà al molo.";
			link.l1 = "Eccellente! Grazie, monsieur.";
			link.l1.go = "fraofficer_1";
		break;
		
		case "fraofficer_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 10.0);
			Patria_SanMartinSetBaron();
		break;
		
		case "fraofficer_2":
			dialog.text = "Capitano Charles de Maure! Il Governatore Generale ti convoca all’istante. Una potente squadra nemica è apparsa davanti alle coste di Saint-Christopher!";
			link.l1 = "Allora, non perdiamo tempo!";
			link.l1.go = "fraofficer_3";
		break;
		
		case "fraofficer_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;
			Patria_SiegeHovernor();
		break;
		
		// патруль у рудника
		case "engofficer":
			dialog.text = "Chi sei tu? Che diavolo ci fai qui?";
			link.l1 = "Ehm...";
			link.l1.go = "engofficer_1";
		break;
		
		case "engofficer_1":
			dialog.text = "Nessun forestiero può entrare qui! Chi siete voi, spie? Vi porto subito dal comandante, ci penseranno loro a sistemarvi.";
			link.l1 = "Ma non possiamo andare all’ufficio del comandante...";
			link.l1.go = "engofficer_2";
		break;
		
		case "engofficer_2":
			dialog.text = "Se non ci vai di tua spontanea volontà, allora dovremo trascinarti a forza! Consegnaci le tue armi!";
			link.l1 = "Niente accordo...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Patria_CondotierBeachFight");
		break;
		
		// бывший управляющий рудника
		case "miner":
			dialog.text = "";
			link.l1 = "Dunque, tutto chiaro?";
			link.l1.go = "miner_1";
		break;
		
		case "miner_1":
			dialog.text = "Sì, monsieur. La lettera va consegnata di persona al signor Peter Stuyvesant o a Mathias Beck.";
			link.l1 = "Sono certo che non avrai difficoltà a trovare una nave da Willemstad a Cartagena. Ti abbiamo fornito tutto il denaro necessario per il viaggio e per l’alloggio. E, se servirà, tra sei mesi potrai confermare le tue relazioni davanti alla commissione francese, vero?";
			link.l1.go = "miner_2";
		break;
		
		case "miner_2":
			dialog.text = "Monsieur, sono uomo di parola.";
			link.l1 = "Molto bene. Allora ti auguro buona fortuna. Questa strada porta a Willemstad, seguila. Non è lontano da qui.";
			link.l1.go = "miner_3";
		break;
		
		case "miner_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "Patria_CondotierOnCuracaoWait", 15.0);
			AddQuestRecord("Patria", "82");
			ReleasePrisoner(npchar);
		break;
		
		// курьер в Капстервиль
		case "cureer":
			dialog.text = "Viceammiraglio Charles de Maure, giusto?";
			link.l1 = "Proprio così. Con chi ho l'onore di parlare?";
			link.l1.go = "cureer_1";
		break;
		
		case "cureer_1":
			dialog.text = "Porto un messaggio per voi dal Barone Noel Forget. Vi ordina di recarvi al palazzo del governatore a Casterville quanto prima.";
			link.l1 = "Oh! Ottime nuove! Grazie, salperò all’istante!";
			link.l1.go = "cureer_2";
		break;
		
		case "cureer_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			Patria_EuropePrepare();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
		break;
		
		case "burden":
			dialog.text = "Saluti, viceammiraglio. Il barone Forget mi ha raccontato molte storie su di voi. Davvero tante. Vi porgo i miei più sinceri ringraziamenti per il vostro fedele e brillante servizio per la causa della Francia nelle colonie, e per averci aiutato a smascherare le trame dell’impostore de Poincy. Ora io e il Ministro delle Finanze ci occuperemo personalmente di lui, mentre voi prenderete il posto del vostro vecchio comandante. Almeno, per il momento.";
			link.l1 = "Ma...";
			link.l1.go = "burden_1";
		break;
		
		case "burden_1":
			dialog.text = "Niente 'ma', viceammiraglio! Questa decisione è già stata presa e approvata dal Re. Ho qui un ordine firmato di suo pugno che ti nomina Governatore Generale de facto delle colonie francesi nell'Arcipelago. Non abbiamo candidati migliori per questo incarico. La tua eccezionale esperienza nelle arti della guerra, la tua conoscenza della regione e della gente che qui tira le fila, le tue abilità e doti ti rendono degno di questo ruolo tanto alto quanto rispettabile. Se posso permettermi, mi aspetto che, col tempo, ti venga assegnato di nuovo questo incarico, stavolta senza il 'de facto'.";
			link.l1 = "Ma sognavo di tornare a Parigi...";
			link.l1.go = "burden_2";
		break;
		
		case "burden_2":
			dialog.text = "La Francia ha bisogno di te qui! Il Ministro delle Finanze sta radunando una flotta in Europa proprio adesso, e la nostra presenza qui, nell’Arcipelago, non passerà certo inosservata. Il tuo compito principale sarà rafforzare e fortificare le colonie e aumentare la potenza militare della nostra flotta, mentre il Barone Forget e la Compagnia Francese delle Indie Occidentali si occuperanno del commercio e dello sviluppo interno! E chi, se non tu, potrà aiutare a preparare la marina francese?\nDunque, mettiti al lavoro, Governatore Generale! So che non ami star chiuso in una stanza tutto il giorno, ma per questa impresa non ce n’è nemmeno bisogno!";
			link.l1 = "Subito, Vostra Grazia! Gli ordini non si discutono!";
			link.l1.go = "burden_3";
		break;
		
		case "burden_3":
			dialog.text = "Sono lieto che tu mi abbia compreso a dovere. Ti chiederò inoltre d'onorare il Chevalier de Poincy con una visita: ha voluto incontrarti di persona. Non possiamo negargli tale diletto prima che salpi per Parigi, vero? Lo troverai nella prigione.";
			link.l1 = "Molto bene, Vostra Grazia...";
			link.l1.go = "burden_4";
		break;
		
		case "burden_4":
			DialogExit();
			DoQuestReloadToLocation("Charles_prison", "goto", "goto19", "Patria_EuropePuancieInPrison");
		break;
		
		// Портной Пуанси Xenon
		case "Tailor":
			dialog.text = "...si bloccherà, capisci? Ho ordinato questi materiali mesi fa!";
			link.l1 = "...";
			link.l1.go = "Tailor_01";
			CharacterTurnByChr(npchar, characterFromId("Charles_PortMan"));
		break;
		
		case "Tailor_01":
			DialogExit();
			sld = characterFromId("Charles_PortMan");
			sld.dialog.currentnode = "Tailor";
			LAi_SetActorType(pchar);
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;
		
		case "Tailor_02":
			dialog.text = "E come diavolo hanno deciso cosa caricare sulla prima nave e cosa sulla seconda?! Non sono mica una sartina qualunque di qualche buco dimenticato da Dio – ho persino un ordine del governatore generale, Sua Eccellenza cavaliere de Poincy!";
			link.l1 = "...";
			link.l1.go = "Tailor_03";
			CharacterTurnByChr(npchar, characterFromId("Charles_PortMan"));
		break;
		
		case "Tailor_03":
			DialogExit();
			Lai_SetPlayerType(pchar);
			sld = characterFromId("Charles_PortMan");
			sld.dialog.currentnode = "Tailor_02";
			LAi_SetActorType(pchar);
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;
		
		case "Tailor_04":
			dialog.text = "Ebbene, che altro potrei fare adesso... Aspetterò. Ma sappi questo: non risponderò di ordini non rispettati!";
			link.l1 = "Salve. Mi pare che hai grane, vero?";
			link.l1.go = "Tailor_05";
			CharacterTurnByChr(npchar, characterFromId("Charles_PortMan"));
		break;
		
		case "Tailor_05":
			dialog.text = "Guai? Eh, questa è una parola gentile! Ah, credo di riconoscerti... Sei il nuovo viceammiraglio, giusto?";
			link.l1 = "Svelto a capire, eh. Proprio così, davanti a te sta il secondo uomo delle colonie francesi, Vice Ammiraglio della flotta francese, Charles de Maure.";
			link.l1.go = "Tailor_06";
			link.l2 = "Lascia stare le formalità, qui non siamo a bordo. E non preoccuparti, non chiamerò le guardie solo perché non mi hai riconosciuto subito. Chiamami pure Charles de Maure.";
			link.l2.go = "Tailor_07";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Tailor_06":
			AddCharacterExpToSkill(pchar, "Leadership", 300);//харизма
			dialog.text = "Vostra Eccellenza, vi prego di perdonarmi se non vi ho subito riconosciuto! Sì, avete ragione, mi sono imbattuto in circostanze impreviste.";
			link.l1 = "E quali sarebbero queste circostanze? Se ho capito bene, non ti hanno portato materiali da Parigi?";
			link.l1.go = "Tailor_08";
		break;
		
		case "Tailor_07":
			AddCharacterExpToSkill(pchar, "Fortune", 300);//везение
			dialog.text = "Oh, vi ringrazio di cuore. Avete ragione, mi sono trovato in mezzo a delle sventure impreviste, per questo non ho subito capito chi avevo davanti.";
			link.l1 = "E quali sarebbero queste circostanze? Se ho ben capito, non ti hanno portato i materiali da Parigi?";
			link.l1.go = "Tailor_08";
		break;
		
		case "Tailor_08":
			dialog.text = "Sì, esatto. Li ho ordinati diversi mesi fa. All'epoca il governatore firmò il decreto della tua nomina e mi ordinò di preparare tutto il necessario per la nuova uniforme d'ammiraglio, certo che sarebbe stata approvata nella madrepatria.";
			link.l1 = "E i materiali non sono stati consegnati, suppongo?";
			link.l1.go = "Tailor_09";
		break;
		
		case "Tailor_09":
			dialog.text = "Immagina un po’! Ho spiegato quanto fosse importante, ho fatto l’ordine... Ma hanno spedizioni più urgenti da sbrigare! E io che dovrei fare? Ordinare con un anno d’anticipo, sperando che si degnino di portarmi i materiali?";
			link.l1 = "Che cosa ti manca esattamente? Magari si può trovare qui nei Caraibi?";
			link.l1.go = "Tailor_10";
		break;
		
		case "Tailor_10":
			dialog.text = "Anche se fosse possibile, non saprei proprio dove... Qui non troverai buoni materiali. Però... potrei usare la tua vecchia giubba da ufficiale come base, se permetti. Tanto, una volta che avrai la divisa d’ammiraglio, non ti servirà più, vero?";
			link.l1 = "Se avrò una divisa d’ammiraglio, allora certo che non avrò bisogno di una semplice giubba da ufficiale. Cos’altro?";
			link.l1.go = "Tailor_11";
		break;
		
		case "Tailor_11":
			dialog.text = "Devo trovare dei gemelli e un colletto per la divisa. Di solito li ordino direttamente dalle botteghe parigine. Anche se sono piuttosto semplici, posso modificarli e dargli un aspetto più decoroso. Però, in tal caso, me ne serviranno di più...";
			link.l1 = "Dal momento che nei Caraibi non ci sono atelier parigini, ti procuro un intero assortimento di vestiti locali con colletti e polsini staccabili. Cos’altro desideri?";
			link.l1.go = "Tailor_12";
		break;
		
		case "Tailor_12":
			dialog.text = "Per i ritocchi finali, mi servono stoffe di altissima qualità. Ho una filatrice capace di ricavare simile tessuto anche dalla fibra più grezza. Ma mi occorre la materia prima – l’ideale sarebbe il cotone. Un balla sarà più che sufficiente.";
			link.l1 = "Si può ottenere anche quello. E dopo, che si fa?";
			link.l1.go = "Tailor_13";
		break;
		
		case "Tailor_13":
			dialog.text = "Dovevano portare un tricorno d’ammiraglio da Parigi, ma posso confezionartelo io se ho il materiale. Anche se per te era previsto uno di stoffa, la pelle resisterebbe meglio ai venti salmastri e al sole rovente dei Caraibi. Ti durerebbe molto di più.";
			link.l1 = "I'll get you the leather; don't worry. I won't even have to chase bulls through the jungles of Espanola. Is that all?";
			link.l1.go = "Tailor_14";
		break;
		
		case "Tailor_14":
			dialog.text = "Dovevano anche consegnare seta di prima scelta da Lione. È leggera, traspirante, assorbe l’umidità in un baleno e si asciuga ancora più in fretta. E la cosa più importante, non si deforma e mantiene sempre la sua forma.";
			link.l1 = "Sì, capisco di quale seta parli. Ma procurarsela nelle colonie potrebbe essere un’impresa più ardua.";
			link.l1.go = "Tailor_15";
		break;
		
		case "Tailor_15":
			dialog.text = "Ecco tutto per i materiali. Ho sentito anche che ti hanno conferito il più alto onore di Francia... L’Ordine di San Luigi non si porta come un gingillo appeso alla cintura. Va mostrato come si deve. Portamelo, ti prego, e lo cucirò dove gli spetta.";
			link.l1 = "D’accordo, lo porto anch’io. Ma non lo perdere, dannazione!";
			link.l1.go = "Tailor_16";
		break;
		
		case "Tailor_16":
			dialog.text = "Certamente no! Lo proteggerò con la mia vita!";
			link.l1 = "D'accordo allora. Se è tutto qui, vado a procurarmi il materiale.";
			link.l1.go = "Tailor_17";
		break;
		
		case "Tailor_17":
			dialog.text = "C’è ancora una cosa... I miei ferri da sarto sono ormai inutilizzabili. Ne ho ordinati di nuovi da Parigi, ma ahimè... Se potessi procurarmi tutti i materiali necessari e prestarmi gli attrezzi, se li hai – solo in prestito, poi me ne procurerò altri! – inizierei subito a cucire.";
			link.l1 = "Ebbene, che posso fare? Ti porterò tutto ciò che ti serve. Dove posso trovarti? Non starai mica ad aspettarmi all’ufficio del porto, vero?";
			link.l1.go = "Tailor_18";
		break;
		
		case "Tailor_18":
			dialog.text = "La mia bottega si trova proprio nell’edificio accanto al molo – appena metti piede a terra, la troverai sulla destra.";
			link.l1 = "Affare fatto. Ti procurerò i materiali.";
			link.l1.go = "Tailor_19";
		break;
		
		case "Tailor_19":
			DialogExit();
			AddQuestRecord("Patria", "65_1");
			chrDisableReloadToLocation = false;
			ChangeCharacterAddressGroup(npchar, "Charles_houseS3", "barmen", "Stay");
			npchar.dialog.currentnode = "Tailor_20";
			LAi_SetOwnerType(npchar);
			pchar.questTemp.PatriaTailor = true;
		break;
		
		case "Tailor_20":
			dialog.text = "Salute, vice ammiraglio! Hai portato tutto il necessario per la tua nuova uniforme?";
			link.l1 = "Non ancora, non ho avuto il tempo. Aspetta, ora procuro tutto.";
			link.l1.go = "Tailor_20_exit";
			if(CheckCoatItems())
			{
				link.l2 = "Sì, ho portato tutto. Ecco la mia vecchia giacca, l’Onorificenza e gli attrezzi da sarto. Il resto dei materiali i miei marinai li porteranno presto alla tua bottega.";
				link.l2.go = "Tailor_21";
			}
		break;
		
		case "Tailor_20_exit":
			npchar.dialog.currentnode = "Tailor_20";
			DialogExit();
		break;
		
		case "Tailor_21":
			RemoveItems(pchar, "talisman9", 1);
			RemoveItems(pchar, "suit1", 1);
			RemoveItems(pchar, "tailor_tool", 1);
			RemoveCharacterGoods(pchar, GOOD_CLOTHES, 1);
			RemoveCharacterGoods(pchar, GOOD_COTTON, 1);
			RemoveCharacterGoods(pchar, GOOD_LEATHER, 1);
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, 1);
			dialog.text = "Meraviglioso! A dir la verità, non pensavo proprio che saresti riuscito a recuperare tutto questo. Sono abituato a lavorare solo con stoffe di Parigi, ma pare che tu sappia tirar fuori dei bei vestiti anche dai materiali locali.";
			link.l1 = "Quanto tempo ci vorrà prima che la mia nuova uniforme sia pronta?";
			link.l1.go = "Tailor_22";
		break;
		
		case "Tailor_22":
			dialog.text = "Di solito ci vogliono almeno sette giorni, ma visto che i committenti sono i due più alti papaveri della Francia nelle colonie... Torna da me tra tre giorni, e ti giuro che tutto sarà pronto a dovere! Non serve prendere misure, mi basterà il tuo vecchio giaccone come riferimento.";
			link.l1 = "Perfetto! Tornerò fra tre giorni, allora.";
			link.l1.go = "Tailor_23";
		break;
		
		case "Tailor_23":
			DialogExit();
			npchar.dialog.currentnode = "Tailor_24";
			SetFunctionTimerCondition("Patria_Tailor_Done", 0, 0, 3, false);
		break;
		
		case "Tailor_24":
			if(CheckAttribute(pchar,"questTemp.PatriaTailorDone"))
			{
				dialog.text = "Viceammiraglio! È un onore rivederla!";
				link.l1 = "Ebbene, sono venuto per la nuova uniforme, come pattuito.";
				link.l1.go = "Tailor_27";
			}
			else
			{
				dialog.text = "Saluti, vice ammiraglio! Mi rincresce, ma la vostra uniforme non è ancora pronta.";
				link.l1 = "Beh, posso almeno dare una sbirciatina a quel che succede?";
				link.l1.go = "Tailor_25";
			}
		break;
		
		case "Tailor_25":
			dialog.text = "No, no! In questo stato non si può proprio vedere, e non voglio deludere le tue aspettative. Abbi un po' di pazienza, ti prego.";
			link.l1 = "D'accordo, aspetterò.";
			link.l1.go = "Tailor_26";
		break;
		
		case "Tailor_26":
			DialogExit();
			npchar.dialog.currentnode = "Tailor_24";
		break;
		
		case "Tailor_27":
			dialog.text = "Sì, certo! Devo dirti che è venuto fuori niente male, non peggio di quelli fatti a Parigi! Avevi ragione, anche nelle colonie si può trovare il materiale giusto se sai dove cercare. Un istante solo. Eccolo qui! Prego, dai un’occhiata e provalo.";
			link.l1 = "Grazie. Qualità sopraffina! E calza a pennello.";
			link.l1.go = "Tailor_28";
		break;
		
		case "Tailor_28":
			dialog.text = "Non solo bene! Puoi indossare questo con orgoglio come viceammiraglio di Francia nelle colonie! E il tuo Ordine, come promisi, ora è dove gli spetta, non più a penzolare dalla cintura.";
			link.l1 = "Ben fatto! Quando incontrerai il Chevalier de Poincy, digli pure che sono soddisfatto.";
			link.l1.go = "Tailor_29";
		break;
		
		case "Tailor_29":
			dialog.text = "Glielo dirò senz'altro! Che la divisa ti sia leale compagna! Buona fortuna!";
			link.l1 = "Grazie! Addio.";
			link.l1.go = "Tailor_30";
		break;
		
		case "Tailor_30":
			DialogExit();
			npchar.dialog.currentnode = "first time";
			npchar.lifeday = 0;
			DeleteAttribute(pchar,"questTemp.PatriaTailorDone");
			DeleteAttribute(pchar, "questTemp.PatriaTailor");
			//if(CheckAttribute (pchar, "IsMushketer")) SetMainCharacterToMushketer("", false);
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			GiveItem2Character(pchar, "suit5");
			EquipCharacterbyItem(pchar, "suit5");
			GiveItem2Character(pchar, "hat5");
			EquipCharacterbyItem(pchar, "hat5");
			AddItems(pchar, "tailor_tool", 1);
			Log_Info("You have received the Vice-Admiral's uniform!");
			AddQuestRecord("Patria", "65_2");
		break;
		
		//belamour legendary edition
		case "BladeUpg":
			string sItem, attrL, attrB;
			ref rItem;
			aref arItems; 
			int i, n, iItemsNum;
			dialog.text = "Quale lama desideri migliorare?";
			
			i = 1;
			makearef(arItems, pchar.items);
			iItemsNum = GetAttributesNum(arItems);
			for(n=0; n<iItemsNum; n++)
			{
				sItem = GetAttributeName(GetAttributeN(arItems, n));
				rItem = ItemsFromID(sItem);
				if(!CheckAttribute(rItem, "groupID")) continue;
				if(rItem.groupID != BLADE_ITEM_TYPE) continue;
				if(rItem.price == 0) continue;
				if(IsEquipCharacterByItem(pchar, rItem.id)) continue;
				if(sItem != "" && rItem.groupID == BLADE_ITEM_TYPE) 
				{
					attrL = "l" + i;
					Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt") + ": Attack - " + FloatToString(stf(rItem.attack),1) + ", balance - " + FloatToString(stf(rItem.Balance),1) + ", weight - " + FloatToString(stf(rItem.Weight),1);
					Link.(attrL).go = "bladeindex_"+GetItemIndex(rItem.id);
					i++;
				}
			}
			
			link.l500 = "Ho cambiato idea";
			link.l500.go = "exit";
		break;
	}
} 

bool CheckCoatItems()
{
	if(GetSquadronGoods(pchar, GOOD_CLOTHES) > 0
	&& GetSquadronGoods(pchar, GOOD_COTTON) > 0
	&& GetSquadronGoods(pchar, GOOD_LEATHER) > 0
	&& GetSquadronGoods(pchar, GOOD_SHIPSILK) > 0
	&& GetCharacterFreeItem(pchar, "talisman9") > 0
	&& GetCharacterFreeItem(pchar, "suit1") > 0
	&& GetCharacterFreeItem(pchar, "tailor_tool") > 0)
	return true;
	
	return false;
}

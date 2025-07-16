void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
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
		
		case "startoff":
			dialog.text = "Capitan de Mor! Benvenuto a Tortuga!";
			link.l1 = "Buongiorno, Tenente. Ti godi il panorama del mare con i tuoi compari?";
			link.l1.go = "startoff_joke";
			link.l2 = "Fatti da parte, Tenente.";
			link.l2.go = "startoff_silence";
			
			AddDialogExitQuestFunction("Tonzag_Arrested");
		break;
		
		case "startoff_joke":
			dialog.text = "Capitano, la vostra fama vi precede, e i pezzi grossi han deciso di offrirvi un piccolo giro tra le meraviglie della nostra cara Isola di Tortuga. Si comincia subito—con le celle della prigione cittadina. Anche i vostri ufficiali sono cordialmente invitati.";
			link.l1 = "Tenente, non sono uno di quei luridi contrabbandieri che hai pescato sulla spiaggia. Niente scherzi, ti prego. Spiegami le questioni come si deve.";
			link.l1.go = "startoff_joke_1";
			link.l2 = "Allora non perdiamo tempo! Mostra la rotta, tenente!";
			link.l2.go = "startoff_joke_2";
		break;
		
		case "startoff_silence":
			dialog.text = "Vedo che con voi, lupi di mare, ci vuole un altro metodo. Soldati, pronti alla battaglia! Capitano de Maure, voi e i vostri ufficiali siete in arresto. Consegnate le armi!";
			link.l1 = "Posso darti una palla di piombo – dove la vuoi, tenente? Con voi topi di terra, non c’è altro modo.";
			link.l1.go = "startoff_silence_1";
			link.l2 = "Secondo quale legge? Se vuoi fermare una ciurma armata senza spargimento di sangue, tenente, dovrai ingegnarti meglio.";
			link.l2.go = "startoff_silence_2";
		break;
		
		case "startoff_joke_1":
			dialog.text = "Per me, siete tutti uguali... Mi spiace, ma non ci saranno spiegazioni, Capitano. Ordini dall’alto. Consegnate le armi, se vi va di restare intero.";
			link.l1 = "Non voglio grane... non adesso. Fa' come ti dicono.";
			link.l1.go = "exit";
			
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			ChangeCharacterComplexReputation(pchar, "nobility", +5);
		break;
		
		case "startoff_joke_2":
			dialog.text = "Uh... Credo che tu non mi abbia capito bene. Capitano, tu e i tuoi ufficiali siete in arresto! Deposite le armi e venite con noi!";
			link.l1 = "Non ho bisogno di guai... non adesso. Fai come dicono loro.";
			link.l1.go = "exit";
			
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;
		
		case "startoff_silence_1":
			dialog.text = "Un’altra parola, Capitano, e vi seppelliamo qui stesso. Armi a terra, subito!";
			link.l1 = "Non ho bisogno di rogne... non adesso. Fa' come dicono loro.";
			link.l1.go = "exit";
			
			AddComplexSelfExpToScill(100, 100, 100, 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
		break;
		
		case "startoff_silence_2":
			dialog.text = "Non temo il sangue, Capitano. Anche se per miracolo restassi vivo, non metterai mai più piede a Tortuga. E la nostra intelligence militare è convinta che tu tenga moltissimo a poter accedere a quest’isola.";
			link.l1 = "Non ho bisogno di grane... non adesso. Fai come ti dicono.";
			link.l1.go = "exit";
			
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			ChangeCharacterComplexReputation(pchar, "authority", 5);
		break;
		
		case "tonzag_after_boarding":
			dialog.text = "Capitano, la situazione è una vera merda! Il nemico ci tiene stretti come in una morsa, temo che non molleranno finché non saremo stecchiti! I nostri sono nei guai grossi, e la maggior parte degli artiglieri è fuori combattimento!";
			link.l1 = "Li aiuterò. Prendi il comando e portaci via di qui!";
			link.l1.go = "tonzag_after_boarding_1";
			DelLandQuestMark(npchar);
		break;
		
		case "tonzag_after_boarding_1":
			dialog.text = "Sì, capitano!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_GoToGunDeck");
		break;
		
		case "tonzag_after_victory":
			dialog.text = "Vittoria, Capitano! La squadra di sbarco è stata annientata, il nemico ha scelto di battere in ritirata verso sud. La nave regge, tutto sommato. Equipaggio rimasto: "+GetCrewQuantity(pchar)+" gente. Rapporto completato!";
			link.l1 = "Grazie! Rhum per tutti e rinforzate la guardia finché non mettiamo piede in porto!";
			link.l1.go = "tonzag_after_victory_1";
		break;
		
		case "tonzag_after_victory_1":
			dialog.text = "Urrà! Aye aye!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_AlonsoBoardingDialog");
		break;
		
		case "killer":
			dialog.text = "Ecco l’uomo in carne e ossa! Hai visto il macello là fuori? Tutta opera tua, traditore! Ma ora pagherai per tutto: per Porto Bello, per Gruoh e per questa miniera!";
			link.l1 = "Aspetta, che diavolo vorrebbe dire...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_FightInMine");
		break;
		
		case "mine_head":
			dialog.text = "";
			link.l1 = "Agh! Questo non promette nulla di buono...";
			link.l1.go = "mine_head_1";
		break;
		
		case "mine_head_1":
			dialog.text = "San Santiago, proteggimi! Maledizione! Quale mostro potrebbe compiere un simile scempio? Rispondi, signore!";
			link.l1 = "Calmati, signore! Prima presentati! Sì, qui si è consumata una carneficina mostruosa, ma chi l'ha compiuta giace già sottoterra. Ho personalmente ‘addobbato’ le miniere con le loro carogne...";
			link.l1.go = "mine_head_2";
		break;
		
		case "mine_head_2":
			dialog.text = "Io sono "+GetFullName(npchar)+", capo ingegnere della reale miniera di Los Teques. Sono appena tornato da una missione durata mesi e... cosa vedono i miei occhi! Quel che è successo qui è un delitto contro Dio e contro gli uomini, dunque vi ordino di deporre subito le armi. Le autorità di Caracas indagheranno su questa scelleratezza!";
			link.l1 = " Non posso obbedire, señor, e giuro che non ho nulla a che fare con questa carneficina! Ma se insisti, il tuo cadavere finirà insieme agli altri.";
			link.l1.go = "mine_head_3";
		break;
		
		case "mine_head_3":
			dialog.text = "Non temo la morte, ma so sempre quand’è il momento di battere in ritirata. Vai pure, ma ricorda, riferirò tutto quello che è successo qui, senza tralasciare nemmeno un dettaglio!";
			link.l1 = "Non posso accettare, señor. Mi rincresce che si sia arrivati a questo. All’armi!";
			link.l1.go = "mine_head_fight";
			link.l2 = "Sembra che tu stia cercando la morte, señor. Ma oggi nessun altro morirà. Ce ne andiamo, e spero che questo particolare finisca anche nel tuo rapporto!";
			link.l2.go = "mine_head_peace";
		break;
		
		case "mine_head_peace":
			DialogExit();
			
			AddDialogExitQuestFunction("Tonzag_LetMineHeadGo");
		break;
		
		case "mine_head_fight":
			DialogExit();
			
			AddDialogExitQuestFunction("Tonzag_FightMineHead");
		break;
		
		case "alonso":
			dialog.text = "Cosa dobbiamo fare col prigioniero, Capitano?";
			link.l1 = "Niente di che, basta che non lo lasci crepare o scappare.";
			link.l1.go = "alonso_1";
		break;
		
		case "alonso_1":
			dialog.text = "Aye aye! Immagino che oggi non avrò bisogno di mettere mano all'interrogatorio, Capitano?";
			link.l1 = "Perché no? Hai deciso di cambiare mestiere, Alonso?";
			link.l1.go = "alonso_2";
		break;
		
		case "alonso_2":
			dialog.text = "Ah-ah, no, Capitano. Adoro questo mestiere, ma pare che abbiate imbarcato un nuovo maestro dell’arte!";
			link.l1 = "Hercule? Da dove ti salta in testa una simile idea?";
			link.l1.go = "alonso_3";
		break;
		
		case "alonso_3":
			dialog.text = "Ebbene, Capitano, il vecchio ha portato i suoi ferri apposta per l’occasione e li ha messi subito all’opera. Non dovrò nemmeno tirar fuori i miei. Ah!";
			link.l1 = "Capisco... Ai tuoi posti, marinaio!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_DrinkAgain");
		break;
		
		case "captive":
			dialog.text = "Ah... Charles de Maure. Permettetemi di porgere le mie scuse a nome dell’intera Lega. L’ordine di lasciarvi in pace ci è giunto troppo tardi. La nostra organizzazione non ha nulla da ridire contro di voi, Capitano. Quanto a questa bestia pelata... Bah! Finché resta al vostro guinzaglio, è salvo, ma vi consiglio di non tenervelo accanto e di lasciarlo marcire nelle fogne, dove merita di stare!";
			link.l1 = "Grazie per la raccomandazione, ma mi interessa di più sapere perché qualcuno mi protegge dai tuoi tagliagole.";
			link.l1.go = "captive_1";
		break;
		
		case "captive_1":
			dialog.text = "Non saprei, Capitano. Immagino che gli ordini vengano dal nostro nuovo padrone. Lo conosci, traditore? La Lega è di nuovo la padrona adesso!";
			link.l1 = "E chi sarebbe costui?";
			link.l1.go = "captive_2";
		break;
		
		case "captive_2":
			dialog.text = "Non posso saperlo, Capitano, e anche se lo sapessi, certe cose non si rivelano.";
			link.l1 = "In tal caso, raccontami qualcos'altro, e poi potrai andare dove ti pare. Te lo prometto sulla mia parola.";
			link.l1.go = "captive_3";
		break;
		
		case "captive_3":
			dialog.text = "Così, senza tanti complimenti? Va bene, Capitano, fai pure le tue domande e poi lasciami andare. Giuro che non tornerò mai più alla Lega, anche se potessi.";
			link.l1 = "Perché ti ostini tanto con Hercule? Troppa seccatura per un solo disertore.";
			link.l1.go = "captive_4";
		break;
		
		case "captive_4":
			dialog.text = "Cosa gli hai detto, maledetto cane? Non tutto è come sembra, Capitano! La Lega si muove di continuo, i codici cambiano, i padroni pure. Vuoi andartene? Ma certo! La porta resta chiusa solo per gli ufficiali di rango, e questa carogna non lo è mai stato. Sua moglie, sì, ma alla signora Tonzag portavamo un tale rispetto che per lei abbiamo chiuso un occhio.";
			link.l1 = "Allora perché?";
			link.l1.go = "captive_5";
		break;
		
		case "captive_5":
			dialog.text = "C’era una faccenda a Porto Bello... Una cosa grossa. Vedi, il tuo compare non si è semplicemente tirato indietro, non si è limitato a rompere il contratto, né solo a far fuori la squadra mandata a chiudere la partita. No, ha scatenato una carneficina vera e propria per le strade, mettendo in serio impiccio i nostri rapporti coi castigliani. Raramente una scorreria di pirati ha sparso tanto terrore quanto quei buoni cattolici provarono quel giorno. Diavolo, forse ci avrei pure fatto i miei complimenti, se fosse stato qualcun altro.";
			link.l1 = "Un altro massacro? Che faccenda intrigante. Continua pure.";
			link.l1.go = "captive_6";
		break;
		
		case "captive_6":
			dialog.text = "Allora intervenne il Vice-Direttore della Compagnia, Rodenburg. In qualche modo riuscì a mettere tutto a tacere, ma non prima che avessimo perso molti dei nostri migliori uomini sotto i colpi delle spedizioni punitive spagnole. Tuttavia, col tempo, tornammo a fare affari con loro... Ah! Ma niente fu dimenticato, e appena si presentò l’occasione cercammo di pareggiare i conti. Il mandante di tutta quella storia, Tonzag, doveva essere fatto fuori.";
			link.l1 = "Non ci sei riuscito. E la miniera?";
			link.l1.go = "captive_7";
		break;
		
		case "captive_7":
			dialog.text = "We were forced to do it. Getting rid of that scum required too much expense; we needed gold. All because of him... But the attempted assassination failed, and I returned to Los Teques to tidy up a bit... How did you figure out where to look?";
			link.l1 = "Non importa. Devo incontrare il tuo capo. Voglio chiarire il malinteso di persona, ché le garanzie del tuo misterioso protettore possono svanire in qualsiasi momento.";
			link.l1.go = "captive_8";
		break;
		
		case "captive_8":
			dialog.text = "Sono certo che ti stanno già aspettando a Caracas, Capitano. Vedi, non ti nascondo nulla.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HoldDialog");
		break;
		
		case "captive_9":
			dialog.text = "Il comandante Arno è crepato, ora comanda Austin.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HoldDialog2");
		break;
		
		case "captive_10":
			dialog.text = "Ho risposto a tutte le tue domande, Capitano. Ora mantieni la parola.";
			link.l1 = "Ti lascio andare. Scendi dalla mia nave, e prega che a Caracas non mi aspetti un’imboscata.";
			link.l1.go = "captive_spare";
			link.l2 = "Grazie per la chiacchierata interessante. Ma accusare Hercule di aver causato un massacro dopo quello che ho visto nella miniera era davvero troppo. All’inferno con te, dove è il tuo posto.";
			link.l2.go = "captive_execute";
		break;
		
		case "captive_execute":
			DialogExit();
			
			AddDialogExitQuestFunction("Tonzag_ExecuteCaptive");
		break;
		
		case "captive_spare":
			DialogExit();
			
			AddDialogExitQuestFunction("Tonzag_ReturnToCabin2");
		break;
		
		case "cureer":
			dialog.text = "Signori, siete invitati a un incontro. Vi attendono in chiesa, dunque la sicurezza è assicurata.";
			link.l1 = "È stato svelto...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_CureerGoAway");
		break;
		
		case "ostin":
			StartQuestMovie(true, false, true);
			PlaySound("VOICE\" + LanguageGetLanguage() + "\OliverTrast02.wav");
			dialog.text = "Charles de Maure. Hercule. Non uscirete vivi da qui.";
			link.l1 = "Sempre un bel modo di cominciare una conversazione. Hai davvero bisogno di tutto questo?";
			link.l1.go = "ostin_1";
		break;
		
		case "ostin_1":
			dialog.text = "Con te, Capitano, le cose non sono affatto semplici. Vedi, il nostro nuovo padrone ha insistito che ti lasciassimo in pace... e che si ficchi le sue richieste su per il culo! Odio la tua razza, dannazione! Ve ne andate in giro con quelle belle vele bianche, pensando di essere innocenti come agnellini. Ma quando la mia lama vi entra nella carne, urlate tutti come donnicciole. Questa cosa la adoro, Charles, lascia che te lo dica! È passato un po’ dall’ultima volta... e ora ti ho proprio davanti, bel figliolo.";
			link.l1 = "Sei malato, compare.";
			link.l1.go = "ostin_2";
		break;
		
		case "ostin_2":
			dialog.text = "No, non posso lasciarti andare. Quanto al tuo amico, però, la faccenda è persino più semplice – ai miei ragazzi non serve, ma ci sono ancora certi suoi vecchi compari della Lega che dubitano dell’efficacia dei miei metodi... Troppo abituati a lavorare pulito, per dobloni puliti, da gente pulita della Compagnia. Ma so bene cosa gli farà cambiare idea – la testa di un dannato coraggioso su un vassoio d’argento, ah-ah!";
			link.l1 = "Hai scelto il posto sbagliato per questo, matto. Davvero vuoi scatenare una battaglia in chiesa?";
			link.l1.go = "ostin_3";
		break;
		
		case "ostin_3":
			dialog.text = "Certo, perché no? Ti dispiace per quella gente? Forse non ci frutterà come a Los Teques, ma ci divertiremo lo stesso. Impiastricceremo le mura della casa del Signore, ah-ha! Capitano, tu ci porterai secchiate di vernice.";
			link.l1 = "Capisco, eh. Ci invidi, vero, topo maledetto? Invidi la nostra libertà? Che le ragazze ci accolgano a braccia aperte e che le monete ci tintinnino in tasca? Guardati: dove ti hanno riesumato i tuoi padroni, porco? Chi ti ha lasciato entrare in chiesa?";
			link.l1.go = "ostin_4";
		break;
		
		case "ostin_4":
			dialog.text = "Mangia polvere, piccolo bastardo!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ChurchVystrel");
		break;
		
	}
} 

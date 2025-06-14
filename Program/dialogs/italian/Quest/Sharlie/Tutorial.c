void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk;
	int i, n, iTemp, addGold;
	string attrL, sStr;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	attrL = Dialog.CurrentNode;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Volevate qualcosa?";
			link.l1 = "No, niente.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;

		// --> Шaрль на носу корабля, Алонсо подходит с диалогом
		case "StartSailor":
			dialog.text = "È bello, vero?";
			link.l1 = "Questa bellezza cerca di uccidermi da due mesi. Finora senza successo.";
			link.l1.go = "StartSailor_1_fencing";
			link.l2 = "Proprio così. A volte l'oceano ci ricorda quanto siamo piccoli di fronte alla natura.";
			link.l2.go = "StartSailor_1_leadership";
			link.l3 = "Ho imparato che in mare ci sono solo due stati: noia o terrore. Questo... è diverso.";
			link.l3.go = "StartSailor_1_fortune";
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "tutorial_4", "", -1);
			CharacterTurnByLoc(pchar, "quest", "quest6");
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "tutorial_5", "", -1);
			CharacterTurnByLoc(npchar, "quest", "quest7");
		break;

		
		case "StartSailor_1_fencing":
			dialog.text = "Ah! Prima volta in mare, monsieur? Quando è così calmo, chiunque può fare il capitano. Quindi cogliete l'attimo.";
			link.l1 = ""+GetFullName(pchar)+". Un nobile, tra l'altro. Non 'monsieur', ma signore.";
			link.l1.go = "StartSailor_2";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;

		case "StartSailor_1_leadership":
			dialog.text = "Ah! Prima volta in mare, monsieur? Quando è così calmo, chiunque può fare il capitano. Quindi cogliete l'attimo.";
			link.l1 = ""+GetFullName(pchar)+". Un nobile, tra l'altro. Non 'monsieur', ma signore.";
			link.l1.go = "StartSailor_2";
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;

		case "StartSailor_1_fortune":
			dialog.text = "Ah! Prima volta in mare, monsieur? Quando è così calmo, chiunque può fare il capitano. Quindi cogliete l'attimo.";
			link.l1 = ""+GetFullName(pchar)+". Un nobile, tra l'altro. Non 'monsieur', ma signore.";
			link.l1.go = "StartSailor_2";
			AddCharacterSkillPoints(pchar, "Fortune", 1);
		break;

		case "StartSailor_2":
			dialog.text = "Come desidera, signore. Dunque, primo viaggio per mare per voi, signor "+pchar.lastname+"?";
			link.l1 = "È così ovvio? Sì, il mio primo viaggio. E non sono fatto per cabine anguste e gallette ammuffite.";
			link.l1.go = "StartSailor_3";
		break;

		case "StartSailor_3":
			dialog.text = "È chiaro come il sole che siete un lupo di terra, signore.";
			link.l1 = "Bada alla lingua! A un uomo d'onore getterei il guanto e pretenderei soddisfazione. Ma a un villano come te - semplicemente taglierò le orecchie.";
			link.l1.go = "StartSailor_4";
		break;

		case "StartSailor_4":
			dialog.text = "Forse a Parigi. Ma qui, parole del genere possono mandare un uomo a nutrire i pesci. Non andrei in giro agitando quella lama, signore - e non fate pentire il capitano di avervi lasciato camminare armato sul suo ponte. L'ultimo attaccabrighe lo mandò nella stiva - a gallette ammuffite e acqua di sentina che nemmeno i topi volevano bere. E sapete cosa? Il poveretto dovette anche pagare un extra quando arrivammo in porto.";
			link.l1 = "Cosa ci si può aspettare... Bene, dimentichiamo questo malinteso. Devo continuamente ricordarmi che questo relitto non è il Louvre.";
			link.l1.go = "StartSailor_5";
		break;
		
		case "StartSailor_5":
			dialog.text = "Eh? Il Louvre? Che cosa dovrebbe essere?";
			link.l1 = "Ah! Il Louvre è un palazzo per pochi eletti. Balli, ricevimenti, intrighi...";
			link.l1.go = "StartSailor_6";
		break;

		case "StartSailor_6":
			dialog.text = "Ah... un bordello allora. Ne abbiamo in abbondanza. Non si può dire che siano per pochi eletti - paga le tue monete e tutto è tuo.";
			link.l1 = "Ah! Non sei lontano dalla verità, marinaio.";
			link.l1.go = "StartSailor_7";
		break;

		case "StartSailor_7":
			dialog.text = "Io, a proposito, mi chiamo Alonso. E cosa ci fate all’estremità del mondo, signore? Difficile credere che abbiate attraversato l’Atlantico solo per litigare con un semplice marinaio.";
			link.l1 = "Mio padre è malato e non può lasciare la nostra tenuta in Guascogna. Mi è stato affidato il compito di trovare mio... fratello maggiore. È venuto qui per affari, e da tempo non abbiamo più sue notizie.";
			link.l1.go = "StartSailor_8";
		break;

		case "StartSailor_8":
			dialog.text = "Perché non mandare semplicemente un uomo fidato, invece di soffrire voi stesso le pene del mare?";
			link.l1 = "La famiglia viene prima di tutto. Non posso affidare il suo destino al primo venuto.";
			link.l1.go = "StartSailor_9_nobilityplus";
			link.l2 = "L’avrei anche fatto - ma secondo mio padre, dovevo occuparmene io. Il perché, non ne ho idea.";
			link.l2.go = "StartSailor_9_nobilityminus";
		break;

		case "StartSailor_9_nobilityplus":
			dialog.text = "E come si chiama vostro fratello?";
			link.l1 = "Michelle de Monper.";
			link.l1.go = "StartSailor_10";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

		case "StartSailor_9_nobilityminus":
			dialog.text = "E come si chiama vostro fratello?";
			link.l1 = "Michelle de Monper.";
			link.l1.go = "StartSailor_10";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;
		
		case "StartSailor_10":
			dialog.text = "De Monper? E voi siete "+pchar.lastname+"? Com'è possibile?";
			link.l1 = "E non guardarmi così. Sono figlio legittimo. Porto solo il cognome di mia madre.";
			link.l1.go = "StartSailor_11";
		break;

		case "StartSailor_11":
			dialog.text = "Non c'è nulla di cui vergognarsi. Vi integrerete bene - nel Nuovo Mondo ognuno ha la sua storia. Io, per esempio...";
			link.l1 = "Non mi vergogno affatto! Meglio raccontami di Martinica. È una grande città? Come Tolosa?";
			link.l1.go = "StartSailor_12";
		break;

		case "StartSailor_12":
			dialog.text = "Una città? Ah! La Martinica è un'intera isola. Una delle più grandi nei possedimenti francesi nei Caraibi. Lì si coltiva caffè infuocato, si estrae zolfo infernale e si danno alla luce le donne più belle del mondo. Un ottimo mix, se me lo chiedete.";
			link.l1 = "Il caffè e lo zolfo non mi interessano. Ma aspetta... un'isola? Come troverò mio fratello su un'intera isola?";
			link.l1.go = "StartSailor_13";
		break;

		case "StartSailor_13":
			dialog.text = "Non preoccupatevi così. Saint-Pierre è una cittadina, non è il Louvre certo, ma nemmeno una giungla. Invece nel banditesco Le François, Dio ce ne scampi, una persona perbene non dovrebbe nemmeno metterci piede.";
			link.l1 = "Se sarà necessario, andrò anche dai banditi. Michel mi ha sempre tirato fuori dai guai. Ora tocca a me.";
			link.l1.go = "StartSailor_14";
		break;

		case "StartSailor_14":
			dialog.text = "Ben detto... per un lupo di terra.";
			link.l1 = "Ancora con questo? Quanto manca a questa dannata Martinica?";
			link.l1.go = "StartSailor_15";
		break;

		case "StartSailor_15":
			dialog.text = "Cinque giorni.";
			link.l1 = "Cinque?!";
			link.l1.go = "StartSailor_16";
		break;

		case "StartSailor_16":
			dialog.text = "Al minimo. E se ci attaccano i pirati - potremmo non arrivarci affatto. Le Piccole Antille sono luoghi pericolosi, anche senza un carico prezioso a bordo.";
			link.l1 = "Tranne i passeggeri!";
			link.l1.go = "StartSailor_17";
		break;
		
		case "StartSailor_17":
			dialog.text = "Ah-ah! Non preoccupatevi. Al massimo vi nasconderò io stesso nella stiva – nessun pirata penserà mai di cercare un nobile guascone tra le botti di rum! Non siamo mica idioti – mescolare un guascone vivo con del rum... esploderebbe come la polvere da sparo, ah-ah!";
			link.l1 = "Ah! Per fortuna il rum è finito già un mese fa!";
			link.l1.go = "StartSailor_18";
		break;

		case "StartSailor_18":
			dialog.text = "Ehm... certe cose è meglio non dirle ad alta voce. Potrebbero pensare che è colpa vostra se il rum è sparito.";
			link.l1 = "Va bene, Alonso, non lo dirò. Tanto quella robaccia non la bevo comunque. E quanto al tuo piano geniale di rinchiudermi nella stiva prima della battaglia – scordatelo.";
			link.l1.go = "StartSailor_20";
		break;

		case "StartSailor_20":
			dialog.text = "E perché mai?";
			link.l1 = "Sono un nobile, so maneggiare la spada e non me ne starò nascosto nella stiva.";
			link.l1.go = "StartSailor_21_fencing";
			link.l2 = "Se ci sarà battaglia – difenderò la nave e combatterò con tutti gli altri. Come dovrebbe essere.";
			link.l2.go = "StartSailor_21_leadership";
			link.l3 = "So decidere da solo – quando combattere e quando fuggire. Dipenderà dalla situazione.";
			link.l3.go = "StartSailor_21_fortune";
			locCameraFromToPos(-14.85, 4.73, 5.82, true, -10.30, 4.52, 6.14);
		break;

		case "StartSailor_21_fencing":
			dialog.text = "Ah. Forse avete davvero qualcosa dentro di voi. Ma attenti – i Caraibi adorano scorticare quelli che vanno in giro con il naso all’insù. Non sopravvivrete all’avanguardia dei pirati. A dirla tutta, vi sgozzerà il primo straccione che incontrerete fuori Saint-Pierre.";
			link.l1 = "Non mi conosci affatto.";
			link.l1.go = "StartSailor_22";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;
		
		case "StartSailor_21_leadership":
			dialog.text = "Ah. Forse avete davvero qualcosa dentro di voi. Ma attenti – i Caraibi adorano scorticare quelli che vi si avventurano con il naso all’insù. Non sopravvivrete all’avanguardia dei pirati. A dirla tutta, vi sgozzerà il primo straccione che incontrerete fuori Saint-Pierre.";
			link.l1 = "Non mi conosci affatto.";
			link.l1.go = "StartSailor_22";
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;

		case "StartSailor_21_fortune":
			dialog.text = "Ah. Forse avete davvero qualcosa dentro di voi. Ma attenti – i Caraibi adorano scorticare quelli che vi si avventurano con il naso all’insù. Non sopravvivrete all’avanguardia dei pirati. A dirla tutta, vi sgozzerà il primo straccione che incontrerete fuori Saint-Pierre.";
			link.l1 = "Non mi conosci affatto.";
			link.l1.go = "StartSailor_22";
			AddCharacterSkillPoints(pchar, "Fortune", 1);
		break;

		case "StartSailor_22":
			dialog.text = "Ma io conosco il Nuovo Mondo e chi lo abita. Se non intendete trascorrere il tempo tra i registri contabili o servendo in casa del governatore – dovrete imparare tutto da zero.";
			link.l1 = "Per fortuna non intendo restare qui a lungo.";
			link.l1.go = "StartSailor_23";
		break;

		case "StartSailor_23":
			dialog.text = "Questo è quello che pensate. Portiamo raramente passeggeri indietro in Europa. Alcuni muoiono – di febbre, alla forca o per un colpo di pistola. Altri restano – per sempre. Ho visto fragili aristocratici diventare capitani, e feroci banditi trasformarsi in rispettabili piantatori. E anche brillanti ufficiali ridursi a mendicanti.";
			link.l1 = "Tentatore, dannazione... ma io tornerò in Francia. Qualcuno mi aspetta là.";
			link.l1.go = "StartSailor_24";
		break;

		case "StartSailor_24":
			dialog.text = "Ah già, è vero. Il padre malato?";
			link.l1 = "Diciamo così... c’è una certa dama il cui marito non vuole proprio vedermi a Parigi. Ma un paio di mesi – e tutto si calmerà.";
			link.l1.go = "StartSailor_25";
		break;

		case "StartSailor_25":
			dialog.text = "Ah-ah-ah! Allora siete davvero nel posto giusto. I Caraibi sono un paradiso per chi fugge da mariti gelosi. E il tempo qui vola. Vedrete che prima o poi diventerete anche marinaio!";
			link.l1 = "Più probabile capitano. Come semplice marinaio, temo di non valere molto. Non sono fatto per il lavoro manuale.";
			link.l1.go = "StartSailor_26";
		break;

		case "StartSailor_26":
			dialog.text = "In Francia si comanda per diritto di nascita, ma su una nave il capitano è re, giudice e Dio. E nessuno sa cosa ha passato per conquistare il suo cappello da capitano. Qui ognuno ottiene ciò che merita. Come diciamo sulla nostra nave – a ognuno il suo.";
			link.l1 = "Che assurdità. A proposito di capitani – devo parlare con il tuo. Anche perché mi stava cercando. Addio, Alonso.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_StartKino_6");
		break;
		
		// <-- Шарль на носу корабля, матрос подходит с диалогом
		
		// --> С Алонсо можно в любой момент поговорить
		case "AlonsoWait":
			dialog.text = "Volevate chiedere qualcosa?";
			if (PCharDublonsTotal() >= 60 && CheckAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuestActive") && !CheckAttribute(npchar, "SharlieTutorial_KaznacheyQuest_Alonso"))
			{
				link.l1 = "Vengo da monsieur Pinchon.";
				link.l1.go = "AlonsoGold_2";
			}
			link.l2 = "Niente.";
			link.l2.go = "AlonsoWait_2";
		break;

		case "AlonsoGold_2":
			dialog.text = "Ah! Il nostro quattro occhi ha coinvolto anche voi?";
			link.l1 = "Quattro occhi?";
			link.l1.go = "AlonsoGold_3";
		break;

		case "AlonsoGold_3":
			dialog.text = "Avete visto i suoi occhiali? Appunto! Ma non fraintendetemi: la squadra rispetta monsieur Pinchon. I buoni medici sono sempre apprezzati a bordo. E poi è anche un discreto tesoriere.";
			link.l1 = "Che affari avete con lui?";
			link.l1.go = "AlonsoGold_4";
		break;

		case "AlonsoGold_4":
			dialog.text = "Ehm... Scusate, ma è una questione interna. Ma non preoccupatevi, non stiamo infrangendo le leggi di bordo.";
			link.l1 = "E le leggi comuni?";
			link.l1.go = "AlonsoGold_5";
		break;

		case "AlonsoGold_5":
			dialog.text = "Quelle non ci interessano. E quanto avevano detto che devo ricevere?";
			if (PCharDublonsTotal() >= 40)
			{
				link.l1 = "40 dobloni.";
				link.l1.go = "AlonsoGold_DatDeneg_3_gold40";
			}
			if (PCharDublonsTotal() >= 50)
			{
				link.l2 = "50 dobloni.";
				link.l2.go = "AlonsoGold_DatDeneg_3_gold50";
			}
			if (PCharDublonsTotal() >= 60)
			{
				link.l3 = "60 dobloni.";
				link.l3.go = "AlonsoGold_DatDeneg_3_gold60";
			}
			// link.l4 = "Devo ricontrollare tutto. Tornerò più tardi.";
			// link.l4.go = "AlonsoWait_2";
		break;
		
		case "AlonsoGold_DatDeneg_3_gold40":
			dialog.text = "Eccolo, l’oro. Preparati, Saint-Pierre! Ah-ah!";
			link.l1 = "...";
			link.l1.go = "AlonsoWait_2";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(40);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			npchar.SharlieTutorial_KaznacheyQuest_Alonso = true;
		break;

		case "AlonsoGold_DatDeneg_3_gold50":
			dialog.text = "Eccolo, l’oro. Preparati, Saint-Pierre! Ah-ah!";
			link.l1 = "...";
			link.l1.go = "AlonsoWait_2";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(50);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			npchar.SharlieTutorial_KaznacheyQuest_Alonso = true;
		break;

		case "AlonsoGold_DatDeneg_3_gold60":
			dialog.text = "Eccolo, l’oro. Preparati, Saint-Pierre! Ah-ah!";
			link.l1 = "...";
			link.l1.go = "AlonsoWait_2";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(60);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			npchar.SharlieTutorial_KaznacheyQuest_Alonso = true;
		break;
		
		case "AlonsoWait_2":
			DialogExit();
			NextDiag.CurrentNode = "AlonsoWait";
		break;
		
		// <-- С Алонсо можно в любой момент поговорить
		
		// --> капитан на корабле, который идёт из Европы
		case "Captain":
			dialog.text = "Ah, "+pchar.name+". Non vi siete affrettato, vedo. Dovete presentarvi immediatamente quando il capitano della nave desidera parlarvi. Avete problemi a seguire gli ordini?";
			link.l1 = "Non sono abituato a ricevere ordini, capitano.";
			link.l1.go = "Captain_2_fencing";
			link.l2 = "Mi scusi, capitano, sono stato trattenuto.";
			link.l2.go = "Captain_2_leadership";
			link.l3 = "Mi è stato spiegato chiaramente che sulla vostra nave valgono le vostre regole.";
			link.l3.go = "Captain_2_sailing";
			if (bBettaTestMode)
			{
				link.l9 = "BetaTest (salta il tutorial e inizia il gioco in Martinica)";
				link.l9.go = "BetaTest_StartGame";
			}
			//NextDiag.TempNode = "Captain";
			pchar.questTemp.SharlieTutorial_CaptainDialog = true;
		break;

		case "Captain_2_fencing":
			dialog.text = "Non tollero che venga messa in dubbio la mia autorità. Non immaginate quante cose spiacevoli possono capitare ai passeggeri in mare. Siete incredibilmente fortunato che io sia interessato a portarvi sano e salvo a Saint-Pierre.";
			link.l1 = "A cosa vi riferite?";
			link.l1.go = "Captain_3";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;

		case "Captain_2_leadership":
			dialog.text = "Scuse accettate. Cogliete l’attimo. Difficilmente avrete presto l’occasione di godervi un tramonto simile.";
			link.l1 = "A cosa vi riferite?";
			link.l1.go = "Captain_3";
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;

		case "Captain_2_sailing":
			dialog.text = "Almeno qualcosa l’avete imparato durante questa traversata. Il potere del capitano è assoluto – e a volte si estende anche sulla terraferma, lontano dalla nave.";
			link.l1 = "A cosa vi riferite?";
			link.l1.go = "Captain_3";
			AddCharacterSkillPoints(pchar, "Sailing", 1);
		break;

		case "Captain_3":
			dialog.text = "Capitano. Abbiate la cortesia di rivolgervi a me secondo il regolamento navale.";
			link.l1 = "A cosa vi riferite, capitano?";
			link.l1.go = "Captain_4";
		break;

		case "Captain_4":
			dialog.text = "Volevo dirvi che abbiamo ammainato le vele e siamo alla deriva. Purtroppo, il vostro arrivo in Martinica subirà un ritardo di un paio di giorni.";
			link.l1 = "Ma perché, capitano?";
			link.l1.go = "Captain_5";
		break;

		case "Captain_5":
			dialog.text = "Perché è così che ho deciso.";
			link.l1 = "Ha forse a che fare con il nostro incontro di ieri con il convoglio mercantile diretto a quel... come si chiama...";
			link.l1.go = "Captain_6";
		break;
		
		case "Captain_6":
			dialog.text = "Capsterville. Ecco, "+pchar.name+": dobbiamo avere una conversazione seria. Vi invito a cena nella cabina. Tra poco suoneranno le campane, e potremo trascorrere del tempo come persone civili — finendo l'ultima bottiglia di vino della nave.";
			link.l1 = "Grazie per l'invito. Sarà un onore, capitano.";
			link.l1.go = "Captain_7";
		break;
		
		case "Captain_7":
			if (!CheckAttribute(npchar, "SharlieTutorial_question_0"))
			{
				dialog.text = "Fatemi sapere quando sarete pronto. Abbiamo ancora tempo, quindi siete libero di passeggiare per la nave – a patto di non distrarre il mio equipaggio dal lavoro.";
				npchar.SharlieTutorial_question_0 = true;
				// теперь можно пострелять из пушки
				sld = &Locations[FindLocation("Quest_Ship_deck_Medium_trade")];
				SetLocatorEvent(sld.id, "event3", "SharlieTutorial_cannon_1");
			}
			else dialog.text = "Altre domande?";
			link.l1 = "(Concludere gli affari) Sono pronto, capitano. Con voi – berrò persino del borgogna!";
			link.l1.go = "Captain_8";
			if (!CheckAttribute(npchar, "SharlieTutorial_question_1"))
			{
				link.l2 = "Cosa state osservando così attentamente con il cannocchiale... capitano?";
				link.l2.go = "Captain_7_question_1_1";
			}
			if (!CheckAttribute(npchar, "SharlieTutorial_question_2"))
			{
				link.l3 = "Capitano, ho avuto il piacere di parlare con un certo Alonso. Qual è il suo ruolo a bordo?";
				link.l3.go = "Captain_7_question_2_1";
			}
			if (!CheckAttribute(npchar, "SharlieTutorial_question_3"))
			{
				link.l4 = "Capitano, raccontatemi della vostra nave. È una pinassa, giusto?";
				link.l4.go = "Captain_7_question_3_1";
			}
			link.l5 = "A presto, capitano.";
			link.l5.go = "Captain_7_exit";
		break;
		
		case "Captain_7_exit":
			DialogExit();
			NextDiag.CurrentNode = "Captain_7";
			if (!CheckAttribute(npchar, "SharlieTutorial_Zapis"))
			{
				npchar.SharlieTutorial_Zapis = true;
				AddQuestRecord("SharlieTutorial", "0.1");
			}
		break;
		
		case "Captain_7_question_1_1":
			dialog.text = "Niente di specifico, sto solo osservando l’orizzonte. La nave è alla deriva – siamo un facile bersaglio.";
			link.l1 = "State cercando pirati?";
			link.l1.go = "Captain_7_question_1_2";
		break;

		case "Captain_7_question_1_2":
			dialog.text = "O spagnoli. Navighiamo sotto bandiera francese e senza scorta, e le Piccole Antille sono un vero corridoio e il feudo di Jacques Barbazon.";
			link.l1 = "Chi sarebbe? Un governatore?";
			link.l1.go = "Captain_7_question_1_3";
		break;

		case "Captain_7_question_1_3":
			dialog.text = "Peggio – uno dei baroni pirati. Quei dannati hanno creato una sorta di organizzazione e si chiamano Fratellanza della Costa. Hanno diviso i Caraibi in sei zone e messo un barone su ciascuna, per non scannarsi tra loro.";
			link.l1 = "E perché le autorità non fanno nulla?";
			link.l1.go = "Captain_7_question_1_4";
		break;

		case "Captain_7_question_1_4":
			dialog.text = "Siete ingenuo, "+pchar.name+". La pirateria esiste solo perché le autorità locali permettono loro di riparare e rifornire le navi in porti selezionati in cambio della maggior parte del bottino. Mi dispiace ammetterlo, ma gli unici che fanno qualcosa contro questa peste nera sono gli spagnoli. Se non fosse per loro, bisognerebbe non solo armare la nave con cannoni costosi, ma anche assumere una scorta.";
			link.l1 = "...";
			link.l1.go = "Captain_7";
			npchar.SharlieTutorial_question_1 = true;
		break;

		case "Captain_7_question_2_1":
			dialog.text = "Marinaio anziano. So poco di lui, ma posso dirvi una cosa: se ognuno ha degli scheletri nell’armadio, Alonso ha un intero cimitero.";
			link.l1 = "Sembra quasi che non vi fidiate di lui.";
			link.l1.go = "Captain_7_question_2_2";
		break;

		case "Captain_7_question_2_2":
			dialog.text = "Affatto. Pensate sia facile trovare persone così esperte per l’equipaggio? Ci vuole almeno un anno e un ottimo nostromo perché la feccia assunta nelle taverne inizi ad assomigliare a un equipaggio. Inoltre, Alonso è anche la voce dell’equipaggio. Il capitano non si scomoda a parlare con i ranghi più bassi, ma sarebbe stupido e pericoloso ignorare che anche i semplici marinai hanno i loro interessi. Ed è lui a rappresentarli, quando serve.";
			link.l1 = "E cosa succede se l’equipaggio è scontento?";
			link.l1.go = "Captain_7_question_2_3";
		break;
		
		case "Captain_7_question_2_3":
			dialog.text = "Mi impiccheranno, e voi – vi pugnaleranno. Non tremate così. Finché l’equipaggio riceve paga, rum, viveri e cure – il contratto tra capitano e squadra è rispettato. Non rischio inutilmente le loro vite, non punisco per capriccio, condivido il bottino e ogni tanto li vizio con un po’ di alcol gratis e altri piaceri a terra. Così si mantiene un equilibrio fragile, e la nave arriva sempre a destinazione.";
			link.l1 = "...";
			link.l1.go = "Captain_7";
			npchar.SharlieTutorial_question_2 = true;
		break;

		case "Captain_7_question_3_1":
			dialog.text = "Avete toccato un tasto dolente, "+pchar.name+"! Potrei parlare della mia bellezza per ore. Terzo classe, venti cannoni, velocità eccellente – non lasciatevi ingannare dal termine ‘mercantile’!";
			link.l1 = "Ho capito riguardo ai cannoni e alla velocità. Ma ‘classe’? ‘Mercantile’?";
			link.l1.go = "Captain_7_question_3_2";
		break;

		case "Captain_7_question_3_2":
			dialog.text = "I ranghi sono una classificazione approssimativa delle navi in base al numero di cannoni. Il settimo classe è poco più di una barchetta, il primo – un vero e proprio forte. Ma non ripetete mai questo in Europa, soprattutto davanti agli ufficiali di marina.";
			link.l1 = "Perché? È una battuta da marinai?";
			link.l1.go = "Captain_7_question_3_3";
		break;

		case "Captain_7_question_3_3":
			dialog.text = "Vi prenderanno per un ignorante e vi derideranno. A dire il vero, in qualsiasi marina seria la classificazione in classi funziona in modo molto diverso ed è applicata solo alle navi da guerra. Ma nei Caraibi, come al solito, facciamo a modo nostro.";
			link.l1 = "E cosa intendevate chiamando la vostra nave ‘mercantile’?";
			link.l1.go = "Captain_7_question_3_4";
		break;

		case "Captain_7_question_3_4":
			dialog.text = "È un’altra convenzione. Le navi da guerra sono più resistenti e ben armate, i corsari saccheggiano e fuggono. Le mercantili possono trasportare molto carico utile, equipaggio o cannoni, ma bisogna scegliere – altrimenti diventano lente come tartarughe. Esistono anche navi multifunzionali, ma non c’è molto da dire su di loro, se non che si adattano alle esigenze del proprietario.";
			link.l1 = "Vi siete animato, capitano.";
			link.l1.go = "Captain_7_question_3_5";
		break;

		case "Captain_7_question_3_5":
			dialog.text = "Amo la mia nave, "+pchar.name+".";
			link.l1 = "...";
			link.l1.go = "Captain_7";
			npchar.SharlieTutorial_question_3 = true;
		break;

		case "Captain_8":
			if (IsEquipCharacterByItem(pchar, "hat3"))
			{
				dialog.text = "Allora siete fortunato – l’unico borgogna rimasto è proprio per questa occasione... Aspettate, "+pchar.name+". Quello è il mio vecchio cappello?!\nAspettate. Ehi, sull’alberatura! Che succede lassù?";
				ChangeCharacterComplexReputation(pchar, "nobility", -1);
			}
			else dialog.text = "Allora siete fortunato – l’unico borgogna rimasto è proprio per questa occasione\nAspettate. Ehi, sull’alberatura! Che succede lassù?";
			link.l1 = "...";
			link.l1.go = "Captain_9";
		break;
		
		case "Captain_9":
			DialogExit();
			DelLandQuestMark(npchar);
			AddDialogExitQuestFunction("SharlieTutorial_Trevoga");
		break;
		
		case "BetaTest_StartGame":	// досрочный выход на сушу
			DialogExit();
			AddDialogExitQuestFunction("SharlieTutorial_StartGameInMartinique");
		break;
		
		// <-- капитан на корабле, который идёт из Европы
		
		// --> Диалог с охранником каюты
		case "OhrannikCabin":
			dialog.text = "Mi dispiace, signore "+pchar.lastname+", ma non potete entrare lì.";
			link.l1 = "Ho accesso alla cabina del capitano. Dovreste saperlo ormai.";
			link.l1.go = "OhrannikCabin_1";
			link.l2 = "Peccato che il mio piano malvagio sia fallito. Addio, marinaio.";
			link.l2.go = "exit";
			if (GetSummonSkillFromName(pchar, SKILL_Leadership) >= 15) NextDiag.TempNode = "OhrannikCabin";
			else NextDiag.TempNode = "OhrannikCabin_again";
			if (!CheckAttribute(npchar, "SharlieTutorial_OhrannikStay"))
			{
				LAi_SetStayType(npchar);
				npchar.SharlieTutorial_OhrannikStay = true;
				DeleteQuestCondition("SharlieTutorial_OhrannikStopaet");
			}
		break;

		case "OhrannikCabin_1":
			dialog.text = "Mi dispiace, signore, ma la situazione è cambiata.";
			link.l1 = "E cosa sarebbe successo, di preciso?";
			link.l1.go = "OhrannikCabin_2";
		break;

		case "OhrannikCabin_2":
			dialog.text = "Manca poco alla fine del viaggio e il capitano preferirebbe evitare che qualcuno si impossessi dei suoi beni per poi scappare impunito dai banditi di Le François una volta sbarcati.";
			link.l1 = "Dubito che il capitano si riferisse a me quando ha dato quest’ordine.";
			link.l1.go = "OhrannikCabin_3";
		break;

		case "OhrannikCabin_3":
			if (GetSummonSkillFromName(pchar, SKILL_Leadership) >= 15)
			{
				if (!CheckAttribute(npchar, "SharlieTutorial_OhrannikFail"))
				{
					dialog.text = "Be’... avete ragione. E poi avete già cenato più volte nella cabina del capitano. Passate pure, signore "+pchar.lastname+".";
					link.l1 = "Così va meglio!";
					link.l1.go = "OhrannikCabin_4";
					notification("Controllo superato", SKILL_Leadership);
				}
				else
				{
					dialog.text = "Insinua... insinua cosa? Non intendevo nulla del genere, signore "+pchar.lastname+"!";
					link.l1 = "Allora sei obbligato a lasciarmi passare.";
					link.l1.go = "OhrannikCabin_3_1";
				}
			}
			else
			{
				if (!CheckAttribute(npchar, "SharlieTutorial_OhrannikFail"))
				{
					dialog.text = "Signore, sapete bene che la cabina del capitano non è un corridoio pubblico. E qui rispettiamo gli ordini alla lettera.";
					link.l1 = "Dannazione, vorrei già essere a terra. È davvero umiliante!";
					npchar.SharlieTutorial_OhrannikFail = true;
				}
				else
				{
					dialog.text = "Signore, ne abbiamo già parlato. Non posso lasciarvi passare.";
					link.l1 = "Sei davvero testardo, marinaio. Addio.";
				}
				link.l1.go = "exit";
				NextDiag.TempNode = "OhrannikCabin_again";
				notification("Abilità insufficiente (15)", SKILL_Leadership);
			}
		break;
		
		case "OhrannikCabin_3_1":
			dialog.text = "E-eh. Va bene, non credo che succederà nulla di grave.";
			link.l1 = "Così va meglio!";
			link.l1.go = "OhrannikCabin_4";
			notification("Controllo superato", SKILL_Leadership);
		break;

		case "OhrannikCabin_4":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			DelLandQuestMark(npchar);
			LocatorReloadEnterDisable("Quest_Ship_deck_Medium_trade", "reload_cabin", false);
		break;

		case "OhrannikCabin_again":
			dialog.text = "Qualcos’altro, signore? Non posso farvi passare – il capitano teme per i suoi beni.";
			link.l1 = "Marinaio, stai forse insinuando che io sia un ladro? Fai attenzione a come parli. È una vera e propria insinuazione!";
			if (CheckAttribute(npchar, "SharlieTutorial_OhrannikFail")) link.l1.go = "OhrannikCabin_3";
			else link.l1.go = "OhrannikCabin_1";
			link.l2 = "Niente, marinaio.";
			link.l2.go = "exit";
			NextDiag.TempNode = "OhrannikCabin_again";
		break;
		
		// <-- Диалог с охранником каюты
		
		// --> матрос ругается на ГГ, который активировал брашпиль
		case "SailorWithWindlass_1":
			dialog.text = "Ehi, nobile imbecille! Hai forse infilato il diavolo nel verricello?!\nCon il tuo piedino regale hai staccato il fermo! Vuoi portarci tutti a fondo, eh?!\nFai un favore: non toccare nulla, a meno che non sia un raffreddore francese!";
			link.l1 = "E cos’è, esattamente?";
			link.l1.go = "SailorWithWindlass_2";
		break;

		case "SailorWithWindlass_2":
			dialog.text = "È il verricello, testone. Serve a tirare su l’ancora. E se non lo blocchi – può squarciare la nave, o avvolgere qualcuno con la cima come un’arenga nel barile!";
			link.l1 = "Ah... E se lo giri dall’altra parte – allora cala l’ancora, vero?";
			link.l1.go = "SailorWithWindlass_3";
		break;

		case "SailorWithWindlass_3":
			dialog.text = "No, genio, allora gira il tempo al contrario. Peccato per te – sei già nato!";
			link.l1 = "Beh, nessuno si è fatto male – giusto? Una nave è una cosa sorprendentemente complessa. Starò più attento.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_windlass_8");
			AddCharacterSkillPoints(pchar, "Sailing", 1);
		break;
		// <-- матрос ругается на ГГ, который активировал брашпиль
		
		// --> матрос ругается на ГГ, который активировал пушку
		case "SailorWithCannon_1":
			dialog.text = "Osservate la lunga canna di questo pezzo con lo stesso entusiasmo con cui ammiravate il tramonto poco fa.";
			link.l1 = "Vedo che ti piace osservare i miei gesti, Alonso. Perché non mi racconti qualcosa di questo prodigio della scienza militare?";
			link.l1.go = "SailorWithCannon_2";
		break;

		case "SailorWithCannon_2":
			dialog.text = "Questa è una cannoniera da sedici libbre. Non la trovi nemmeno su tutte le navi da guerra.";
			link.l1 = "È facile colpire con questa?";
			link.l1.go = "SailorWithCannon_3";
		break;

		case "SailorWithCannon_3":
			dialog.text = "Da distanza ravvicinata facciamo a pezzi chiunque. A cento yard — si può fare. Più lontano — solo fumo e fiamme, ma è già qualcosa.";
			link.l1 = "A cento yard anche il nemico può fare lo stesso.";
			link.l1.go = "SailorWithCannon_4";
		break;

		case "SailorWithCannon_4":
			dialog.text = "Esatto. Ma lì conta chi ha la squadra più affiatata e i cannonieri migliori. Peccato che il nostro cannoniero stia dormendo ora — lui vi spiegherebbe tutta la scienza, e magari vi caricherebbe pure nella bocca del cannone, ah-ah!";
			link.l1 = "Il cannoniero è un ufficiale, giusto?";
			link.l1.go = "SailorWithCannon_5";
		break;

		case "SailorWithCannon_5":
			dialog.text = "Di norma sì. Senza un cannoniero almeno un po’ esperto è meglio evitare i combattimenti — tanto vale buttare subito i cannoni in mare e darsela a gambe\nI capitani mercantili in genere non portano nulla di più pesante dei sei libbre — si affidano a scorte o alla fortuna\nIn effetti è ragionevole: senza cannoni pesanti e munizioni la nave è più leggera e si può caricare più merce da vendere in stiva\nSe il nostro capitano non si fosse rovinato con questi bei pezzi — magari il rum non sarebbe finito così in fretta. Eh!";
			link.l1 = "Il capitano non dirige personalmente il fuoco?";
			link.l1.go = "SailorWithCannon_6";
		break;

		case "SailorWithCannon_6":
			dialog.text = "Con un buon cannoniero e un equipaggio affiatato non serve. Ma vi dirò questo: se un capitano prende lui stesso la mira invece di gridare solo 'Fuoco!' dal cassero — le falle nello scafo nemico aumentano in fretta.";
			link.l1 = "Posso sparare anch’io?";
			link.l1.go = "SailorWithCannon_7";
			link.l2 = "Grazie per la lezione, Alonso. Sei una vera enciclopedia marina.";
			link.l2.go = "SailorWithCannon_7_exit";
		break;
		
		case "SailorWithCannon_7_exit":
			dialog.text = "Eccome! Ma non toccate il cannone e non fate agitare l’equipaggio.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_cannon_11");
		break;

		case "SailorWithCannon_7":
			dialog.text = "Sparare? Difficile. Ma se volete fare fuoco — bisogna chiedere al capitano. Vado a chiedere!";
			link.l1 = "Non serve!";
			link.l1.go = "SailorWithCannon_8";
		break;

		case "SailorWithCannon_8":
			dialog.text = "Capit-aaaano!";
			link.l1 = "...";
			link.l1.go = "exit";
			locCameraSleep(true);
			AddDialogExitQuestFunction("SharlieTutorial_cannon_3");
		break;

		case "CaptainWithCannon_1":
			dialog.text = "Che succede qui, Alonso?";
			link.l1 = "...";
			link.l1.go = "CaptainWithCannon_2";
		break;

		case "CaptainWithCannon_2":
			StartInstantDialog("SharlieTutorial_Sailor_10", "CaptainWithCannon_3", "Quest\Sharlie\Tutorial.c");
		break;

		case "CaptainWithCannon_3":
			dialog.text = "Il signor "+pchar.name+" chiede di poter sparare con il cannone — solo a scopo didattico.";
			link.l1 = "...";
			link.l1.go = "CaptainWithCannon_4";
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Captain_clone"));
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Captain_clone"), npchar);
		break;

		case "CaptainWithCannon_4":
			StartInstantDialog("SharlieTutorial_Captain_clone", "CaptainWithCannon_5", "Quest\Sharlie\Tutorial.c");
		break;

		case "CaptainWithCannon_5":
			dialog.text = "Credevo che tu rappresentassi gli interessi dell’equipaggio, Alonso. E invece proponi di svegliare il prossimo turno e sconvolgere gli altri nel modo più barbaro?";
			link.l1 = "...";
			link.l1.go = "CaptainWithCannon_6";
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Sailor_10"));
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Sailor_10"), npchar);
		break;
		
		case "CaptainWithCannon_6":
			StartInstantDialog("SharlieTutorial_Sailor_10", "CaptainWithCannon_7", "Quest\Sharlie\Tutorial.c");
		break;
		
		case "CaptainWithCannon_7":
			dialog.text = "Forse è il caso di farli muovere un po’ e tenerli all’erta. Non mi piace che siamo in deriva alla vista di tutti. Potrebbe finire male.";
			link.l1 = "...";
			link.l1.go = "CaptainWithCannon_8";
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Captain_clone"));
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Captain_clone"), npchar);
		break;

		case "CaptainWithCannon_8":
			StartInstantDialog("SharlieTutorial_Captain_clone", "CaptainWithCannon_9", "Quest\Sharlie\Tutorial.c");
		break;

		case "CaptainWithCannon_9":
			dialog.text = "Non portare sfortuna!.. Va bene. Un colpo solo. A salve.";
			link.l1 = "...";
			link.l1.go = "CaptainWithCannon_10";
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Sailor_10"));
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Sailor_10"), npchar);
		break;

		case "CaptainWithCannon_10":
			dialog.text = "Divertitevi, "+pchar.name+". Risveglieremo l’equipaggio... a vostre spese, ha-ha!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_cannon_5");
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Sailor_10"), pchar);
		break;
		
		// <-- матрос ругается на ГГ, который активировал пушку
		
		// --> Диалог с матросом, который хочет рома
		case "SailorWantRum":
			dialog.text = "Mi concede un momento, signore?";
			link.l1 = "Parla, marinaio.";
			link.l1.go = "SailorWantRum_1";
		break;

		case "SailorWantRum_1":
			dialog.text = "Piacere di conoscerla, signore. Mi chiamo Henry. Le andrebbe di guadagnare qualcosa?";
			link.l1 = "Quanto sarebbe questo ‘qualcosa’?";
			link.l1.go = "SailorWantRum_2";
		break;

		case "SailorWantRum_2":
			dialog.text = "Cinquecento pesos.";
			link.l1 = "Quanto?! E cosa dovrei fare per quella cifra? Spero non sia un ammutinamento...";
			link.l1.go = "SailorWantRum_3";
		break;

		case "SailorWantRum_3":
			dialog.text = "Per carità, signore! Non gridate così!";
			link.l1 = "È una bella somma, marinaio. Anche a Parigi ci si vive bene con quei soldi.";
			link.l1.go = "SailorWantRum_4";
		break;

		case "SailorWantRum_4":
			dialog.text = "Eh, non voglio approfittare della sua ignoranza e le dirò come stanno le cose: nei Caraibi cinquecento pesos non sono nulla. Capitani e mercanti portano così tanta roba che i prezzi per tutto ciò che ha un minimo di valore pratico sono alle stelle. Si arriva all’assurdo: a volte una lama rara vale quanto una piccola nave.";
			link.l1 = "È una follia.";
			link.l1.go = "SailorWantRum_5";
		break;

		case "SailorWantRum_5":
			dialog.text = "Che vuole farci? Aspettiamo tutti che le cose si calmino e i prezzi tornino alla normalità. Allora, è interessato a guadagnare cinquecento pesos?";
			link.l1 = "Prima voglio sapere in cosa consiste il lavoro.";
			link.l1.go = "SailorWantRum_6";
		break;

		case "SailorWantRum_6":
			dialog.text = "Di certo sapete della triste situazione del rum a bordo. Eppure sono convinto che, cercando bene, si possano trovare ancora alcune bottiglie. Il rum in bottiglia non è come quello nella botte. Ottimo sapore, previene avvelenamenti, rafforza mano e salute — insomma, cosa utile. Specialmente alla fine del viaggio, quando si diventa pazzi a fissare l’orizzonte.";
			link.l1 = "E cosa ne farai? E perché non cerchi da solo?";
			link.l1.go = "SailorWantRum_7";
		break;
		
		case "SailorWantRum_7":
			dialog.text = "Quando mai trovo il tempo? Siamo in pochi, quindi lavoriamo per tre. E il rum lo rivenderò — troverò a chi darlo.";
			link.l1 = "Apprezzo la sincerità, sai.";
			link.l1.go = "SailorWantRum_8";
		break;

		case "SailorWantRum_8":
			dialog.text = "Allora? Accetta? Mi servirebbero tre bottiglie.";
			link.l1 = "Farò del mio meglio, ma non prometto nulla.";
			link.l1.go = "SailorWantRum_9";
			link.l2 = "Preferisco declinare. Questo tipo di incarico non fa per me.";
			link.l2.go = "SailorWantRum_10";
		break;

		case "SailorWantRum_9":
			DialogExit();
			NextDiag.CurrentNode = "SailorWantRum_PrinestiRum";
			AddDialogExitQuestFunction("SharlieTutorial_PrinestiRum");
		break;

		case "SailorWantRum_10":
			dialog.text = "Peccato, ma non mi offenderò. Buona serata, signore.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SailorWantRum_PrinestiRum";
			npchar.SailorWantRum_Done = true;
			DelLandQuestMark(npchar);
		break;
		
		case "SailorWantRum_PrinestiRum": // ждёт ром
			dialog.text = "Sì, signor "+pchar.lastname+"?";
			if (GetCharacterItem(pchar, "potionrum") >= 3 && !CheckAttribute(npchar, "questTemp.SailorWantRum_Done"))
			{
				link.l1 = "Ecco le tue tre bottiglie di rum.";
				link.l1.go = "SailorWantRum_PrinestiRum_2";
			}
			if (PCharDublonsTotal() >= 42 && CheckAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuestActive") && !CheckAttribute(npchar, "SharlieTutorial_KaznacheyQuest_Anri"))
			{
				link.l2 = "Henry, ho qualcosa per te da parte di monsieur Pinchon.";
				link.l2.go = "RumGold_2";
			}
			link.l3 = "Nulla.";
			link.l3.go = "exit";
			NextDiag.TempNode = "SailorWantRum_PrinestiRum";
		break;

		case "RumGold_2":
			dialog.text = "Felice di essere utile a lui! Quanto mi spetta stavolta?";
			if (PCharDublonsTotal() >= 28)
			{
				link.l1 = "28 dobloni.";
				link.l1.go = "RumGold_DatDeneg_gold28";
			}
			if (PCharDublonsTotal() >= 35)
			{
				link.l2 = "35 dobloni.";
				link.l2.go = "RumGold_DatDeneg_gold35";
			}
			if (PCharDublonsTotal() >= 42)
			{
				link.l3 = "42 dobloni.";
				link.l3.go = "RumGold_DatDeneg_gold42";
			}
			// link.l4 = "Devo controllare tutto. Tornerò più tardi.";
			// link.l4.go = "RumGold_DatDeneg_3";
		break;
		
		case "RumGold_DatDeneg_gold28":
			dialog.text = "Grazie, signore "+pchar.lastname+". Porga i miei saluti al signor tesoriere.";
			link.l1 = "...";
			link.l1.go = "RumGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(28);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			npchar.SharlieTutorial_KaznacheyQuest_Anri = true;
		break;

		case "RumGold_DatDeneg_gold35":
			dialog.text = "Grazie, signore "+pchar.lastname+". Porga i miei saluti al signor tesoriere.";
			link.l1 = "...";
			link.l1.go = "RumGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(35);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			npchar.SharlieTutorial_KaznacheyQuest_Anri = true;
		break;

		case "RumGold_DatDeneg_gold42":
			dialog.text = "Grazie, signore "+pchar.lastname+". Porga i miei saluti al signor tesoriere.";
			link.l1 = "...";
			link.l1.go = "RumGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(42);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			npchar.SharlieTutorial_KaznacheyQuest_Anri = true;
		break;
		
		case "RumGold_DatDeneg_3":
			DialogExit();
			NextDiag.CurrentNode = "SailorWantRum_PrinestiRum";
		break;

		case "SailorWantRum_PrinestiRum_2":
			dialog.text = "Grazie, signore "+pchar.lastname+". L'avete fatto con grande abilità!";
			link.l1 = "Spero di ricevere il mio denaro con la stessa abilità.";
			link.l1.go = "SailorWantRum_PrinestiRum_3";
			RemoveItems(pchar, "potionrum", 3);
			npchar.SailorWantRum_Done = true;
		break;

		case "SailorWantRum_PrinestiRum_3":
			dialog.text = "Forse preferite un pagamento non in denaro?";
			link.l1 = "Non sei poi così onesto, a quanto vedo.";
			link.l1.go = "SailorWantRum_PrinestiRum_4";
		break;

		case "SailorWantRum_PrinestiRum_4":
			dialog.text = "Ma no! Se scegliete i soldi — avrete i soldi! Solo che potrei anche condividere un po' di conoscenza.";
			link.l1 = "Che tipo di conoscenza?";
			link.l1.go = "SailorWantRum_PrinestiRum_5";
		break;

		case "SailorWantRum_PrinestiRum_5":
			dialog.text = "Posso raccontarvi molte cose utili sulla navigazione. Nei vostri libri scolastici non le troverete.";
			link.l1 = "Avanti, fammi la lezione più costosa della mia vita.";
			link.l1.go = "SailorWantRum_PrinestiRum_6";
			link.l2 = "Cinque cento consigli non valgono cinquecento monete. Prenderò i soldi.";
			link.l2.go = "SailorWantRum_PrinestiRum_money";
		break;

		case "SailorWantRum_PrinestiRum_money":
			dialog.text = "Prego, signore "+pchar.lastname+". E grazie ancora!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_PrinestiRumFinal");
		break;

		case "SailorWantRum_PrinestiRum_6":
			dialog.text = "Spero davvero, signore "+pchar.name+", che la mia lezione rimanga tale. Sapete cos'è la navigazione?";
			link.l1 = "Ti sorprenderà, ma lo so. E so anche leggere. La navigazione è determinare la posizione nello spazio e calcolare la rotta, per esempio di una nave.";
			link.l1.go = "SailorWantRum_PrinestiRum_7";
		break;
		
		case "SailorWantRum_PrinestiRum_7":
			dialog.text = "Ahhh. Parlate di stelle e mappe. No, non ne capisco nulla. Dovreste chiedere al navigatore o al capitano. Qui per 'navigazione' si intende la capacità di comandare e gestire una nave.";
			link.l1 = "E chi sarebbero 'qui'?";
			link.l1.go = "SailorWantRum_PrinestiRum_8";
		break;

		case "SailorWantRum_PrinestiRum_8":
			dialog.text = "Nei Caraibi. È così che funziona, non chiedete il perché. Ecco: più siete esperti in navigazione, più velocità e manovrabilità riuscite a ottenere dalla nave. E l'equipaggio gestisce le vele più in fretta. Ma non è la cosa più importante.";
			link.l1 = "Vedo che sai come mantenere la suspense.";
			link.l1.go = "SailorWantRum_PrinestiRum_9";
		break;

		case "SailorWantRum_PrinestiRum_9":
			dialog.text = "Più siete esperti in navigazione, più grande sarà la nave che potrete comandare! Inoltre, se prendete una nave troppo grande rispetto alla vostra abilità, rischiate di perdere concentrazione, energie e perfino salute!";
			link.l1 = "Sembra pericoloso. Strano come abbia vissuto senza saperlo finora.";
			link.l1.go = "SailorWantRum_PrinestiRum_10";
		break;

		case "SailorWantRum_PrinestiRum_10":
			dialog.text = "Per fortuna, non è necessario essere esperti in tutto. Potete sempre assumere un buon navigatore e lui si occuperà della navigazione al posto vostro. Ma assicuratevi che sia pagato puntualmente e che vi sia fedele. Restare senza navigatore su una nave che non sapete gestire da soli — è una pessima esperienza.";
			link.l1 = "Grazie per la lezione, Henry. Non so se mi sarà utile, ma un po’ di conoscenza in più non fa mai male.";
			link.l1.go = "SailorWantRum_PrinestiRum_11";
			AddCharacterSkillPoints(pchar, "Sailing", 3);
		break;

		case "SailorWantRum_PrinestiRum_11":
			dialog.text = "Prego, signore "+pchar.lastname+". E grazie ancora!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_PrinestiRumFinal");
		break;
		
		// <-- Диалог с матросом, который хочет рома
		
		// --> Диалог со старым матросом в трюме
		case "OldSailor":
			dialog.text = "(canta) C’est la mère Michel qui a perdu son chat... Qui crie par la fenêtre à qui le lui rendra...";
			link.l1 = "Che ci fai qui, marinaio?";
			link.l1.go = "OldSailor_1";
			NextDiag.TempNode = "OldSailor";
		break;

		case "OldSailor_1":
			dialog.text = "A quanto pare, sono come madame Michel — sto cercando il gatto. Solo che non urlo — a lei non piace quando le si grida.";
			link.l1 = "L'ho vista stamattina — stava ancora graffiando i miei stivali.";
			link.l1.go = "OldSailor_2";
		break;

		case "OldSailor_2":
			dialog.text = "Questo non è niente. Ma gli stivali del capitano non sono stati così fortunati. Ti piacciono i gatti?";
			link.l1 = "Certo che mi piacciono.";
			link.l1.go = "OldSailor_3";
			link.l2 = "Non molto.";
			link.l2.go = "OldSailor_4";
		break;

		case "OldSailor_3":
			dialog.text = "Non c’è da meravigliarsi. Altrimenti, come faresti a sbarazzarti di quei dannati topi?";
			link.l1 = "Ma non puoi fare sempre affidamento sui gatti, no? Sono creature piuttosto capricciose.";
			link.l1.go = "OldSailor_5";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

		case "OldSailor_4":
			dialog.text = "Peccato. I gatti sono amati e apprezzati sulle navi. Altrimenti, come faresti a sbarazzarti di quei dannati topi?";
			link.l1 = "Ma non puoi fare sempre affidamento sui gatti, no? Sono creature piuttosto capricciose.";
			link.l1.go = "OldSailor_5";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;

		case "OldSailor_5":
			dialog.text = "Hai ragione. Ecco perché ci affidiamo all'arsenico. Ma prova a trovarlo nei Caraibi! Così perdiamo le merci — i topi rovinano il rum, i biscotti e mordono tutto il resto\nE il nostro tesoriere dice: «Prendetela con filosofia, è come una tassa sul commercio»\nMa noi lo sappiamo: è solo pigro, tutto qui. Se non fosse per la nostra cara Chantal — il capitano l'avrebbe già fatto vivere nella stiva a cacciare i topi di persona, ah-ah!";
			link.l1 = "Buona fortuna con il gatto. Io devo andare.";
			link.l1.go = "OldSailor_6";
		break;
		
		case "OldSailor_6":
			dialog.text = "Aspettate, signore. Di solito un semplice marinaio vede i passeggeri nobili solo sul ponte, e voi — siete sceso fin nella stiva!";
			link.l1 = "La curiosità ha ucciso il gatto, ah-ah!";
			link.l1.go = "OldSailor_7";
		break;

		case "OldSailor_7":
			dialog.text = "Vi interessa la marina?";
			link.l1 = "Sembra che ogni membro dell'equipaggio si sia messo in testa di farmi sbarcare come un vero marinaio.";
			link.l1.go = "OldSailor_8";
		break;

		case "OldSailor_8":
			dialog.text = "Non c'è da stupirsi. Anche se per molti di noi il mare ha portato solo dolore, amiamo il nostro lavoro. E per un marinaio è sempre un piacere quando un novizio mostra vero interesse.";
			link.l1 = "...";
			link.l1.go = "OldSailor_9";
		break;

		case "OldSailor_9":
			dialog.text = "Ditemi: qual è l'abilità più importante per un capitano?";
			if (GetSummonSkillFromName(pchar, SKILL_Sailing) >= 6)
			{
				link.l1 = "Navigazione. Determina la dimensione della nave che può comandare.";
				link.l1.go = "OldSailor_10";
				notification("Controllo superato", SKILL_Sailing);
			}
			else
			{
				link.l1 = "Non mentirò, non lo so.";
				link.l1.go = "OldSailor_9_1";
				notification("Abilità insufficiente (6)", SKILL_Sailing);
			}
		break;

		case "OldSailor_9_1":
			dialog.text = "Non vi scoraggiate, signore. Parlate con l'equipaggio, esplorate la nave. Se risponderete — vi racconterò qualcosa di molto interessante. Come a uno di noi.";
			link.l1 = "Terrò a mente. Addio!";
			link.l1.go = "exit";
			NextDiag.TempNode = "OldSailor_again";
		break;
		
		case "OldSailor_10":
			dialog.text = "Esatto! E adesso una domanda trabocchetto: meglio le vele quadre o quelle latine?";
			link.l1 = "Non posso giudicare, ma sento odore di tranello. Credo che ognuna abbia i suoi vantaggi.";
			link.l1.go = "OldSailor_11";
		break;

		case "OldSailor_11":
			dialog.text = "Di nuovo giusto! Le vele quadre sono potenti con il vento in poppa. Ma con quelle latine puoi virare e catturare anche il vento traverso. È bello vedere che non avete sprecato il vostro tempo, signore.";
			link.l1 = "Non so se queste conoscenze mi serviranno mai... A meno che non voglia impressionare le dame dell'alta società spacciandomi per un vero marinaio, ah-ah!";
			link.l1.go = "OldSailor_12";
		break;

		case "OldSailor_12":
			dialog.text = "Oh, non so, signore "+pchar.name+". Forse siete un nobile — ma con noi vi comportate da uomo. E lo apprezziamo. Il nostro capitano ha qualcosa in mente. Qualcosa si è rotto tra voi due.";
			link.l1 = "Sciocchezze. Di cosa parli, marinaio?";
			link.l1.go = "OldSailor_13";
		break;

		case "OldSailor_13":
			dialog.text = "Dicono che non è un caso se ha spedito una lettera a Capsterville l'altro giorno con una nave di passaggio\nE non per caso è andato alla deriva — proprio alla fine del viaggio, quando tutti urlano: almeno metteteci a terra!";
			link.l1 = "Non mi interessano i pettegolezzi. E perché dovrei? Posso semplicemente chiederglielo. A un nobile non negherà una risposta onesta.";
			link.l1.go = "OldSailor_14";
		break;

		case "OldSailor_14":
			dialog.text = "Non lo conoscete, signore "+pchar.name+". Vi negherà la risposta, eccome. Ed è arrabbiato adesso — ha perso la chiave.";
			link.l1 = "La chiave?";
			link.l1.go = "OldSailor_15";
		break;

		case "OldSailor_15":
			dialog.text = "Del suo baule nella cabina. Penso che non sarà difficile trovarla. Sarà da qualche parte, buttata lì.";
			link.l1 = "Trovare la chiave? Io?";
			link.l1.go = "OldSailor_16";
		break;

		case "OldSailor_16":
			dialog.text = "Sta a voi decidere\nA proposito, signore "+pchar.name+", vi è rimasto del rum per caso? Non avrete dato tutto a Henry, ah-ah!";
			if (GetCharacterItem(pchar, "potionrum") >= 1)
			{
				link.l1 = "Sì. Prendilo pure.";
				link.l1.go = "OldSailor_17";
			}
			link.l2 = "Purtroppo no. È già un miracolo che abbia trovato quelle tre bottiglie.";
			link.l2.go = "OldSailor_16_1";
		break;
		
		case "OldSailor_16_1":
			dialog.text = "Davvero. Buona fortuna, signore "+pchar.name+". Vado a cercare quella birbante a strisce.";
			link.l1 = "Buona fortuna anche a te, marinaio.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_OldSailorKey");
			PlaySound("ambient\Animals\Cat_01.wav");
		break;

		case "OldSailor_17":
			dialog.text = "Oh, che favore mi avete fatto! Vi siete comportato degnamente con l'equipaggio, signore "+pchar.name+". Ecco un piccolo regalo — per fortuna!";
			link.l1 = "Un sasso con un buco? Che carino.";
			link.l1.go = "OldSailor_18";
			GiveItem2Character(PChar, "talisman11");
			TakeItemFromCharacter(pchar, "potionrum");
		break;

		case "OldSailor_18":
			dialog.text = "Ridete pure. Ma vi dico questo: in mare, i talismani non fanno mai male.";
			link.l1 = "Siete un popolo superstizioso, voi marinai. Buona fortuna, marinaio.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_OldSailorKey");
			PlaySound("ambient\Animals\Cat_01.wav");
		break;

		case "OldSailor_again":
			dialog.text = "Avete già trovato la risposta? Qual è l'abilità più importante per un capitano?";
			if (GetSummonSkillFromName(pchar, SKILL_Sailing) >= 6)
			{
				link.l1 = "Navigazione. Determina la dimensione della nave che può comandare.";
				link.l1.go = "OldSailor_10";
				notification("Controllo superato", SKILL_Sailing);
			}
			else
			{
				link.l1 = "Non ancora.";
				link.l1.go = "exit";
				NextDiag.TempNode = "OldSailor_again";
				notification("Abilità insufficiente (6)", SKILL_Sailing);
			}
		break;
		
		// <-- Диалог со старым матросом в трюме
		
		// --> Диалог с матросом, которому нужен ящик с ядрами (Поль)
		case "SailorNeedBox":
			dialog.text = "Ehi là, ragazzo!";
			link.l1 = "Non assomigli a mio padre. Grazie a Dio.";
			link.l1.go = "SailorNeedBox_1";
		break;

		case "SailorNeedBox_1":
			dialog.text = "Ah! Sarei orgoglioso di avere un figlio così alto e nobile. Ma posso solo generare sale della terra come me stesso.";
			link.l1 = "Va bene, accetto il complimento. Qual è il problema?";
			link.l1.go = "SailorNeedBox_2";
		break;

		case "SailorNeedBox_2":
			dialog.text = "Ho bisogno di una mano, ragazzo. Mi hanno ordinato di impilare le palle di cannone vicino ai cannoni — nel caso succeda qualcosa in queste acque pericolose. Ho passato mezza guardia a trascinare questi bastardi di ferro dalla stiva, e la schiena ha ceduto all'ultima cassa.";
			link.l1 = "Perché non chiedi semplicemente ai tuoi compagni? Pensavo che voi marinai vi aiutaste a vicenda.";
			link.l1.go = "SailorNeedBox_3";
		break;

		case "SailorNeedBox_3":
			dialog.text = "Una cosa che la nostra fratellanza odia decisamente è trascinare carichi pesanti senza buone ragioni. Oggi ho pescato la pagliuzza più corta — trascinare casse di palle di cannone dalla stiva. Lavoro schifoso, indegno di un marinaio del mio calibro. Ma cosa si può fare?";
			link.l1 = "Deja di lamentarti. Ti aiuterò. Almeno vedrò quella stiva con cui mi spaventano sempre.";
			link.l1.go = "SailorNeedBox_4";
			if (IsCharacterPerkOn(pchar, "HT3"))
			{
				link.l2 = "(Atleta) Vedi questa spada alla mia cintura? Pesa più di te. Andrò a prendere le tue palle — nessun problema.";
				link.l2.go = "SailorNeedBox_4";
			}
			link.l3 = "Non faccio lavori manuali, marinaio. Porta tu stesso le tue casse.";
			link.l3.go = "SailorNeedBox_Net";
		break;

		case "SailorNeedBox_4":
			dialog.text = "Grazie, ragazzo. Ma non sforzarti troppo!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SailorNeedBox_PrinestiBalls";
			AddDialogExitQuestFunction("SharlieTutorial_SailorNeedBoxOfBalls");
		break;
		
		case "SailorNeedBox_Net":
			DialogExit();
			
			LAi_CharacterDisableDialog(npchar);
			DelLandQuestMark(npchar);
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;
		
		case "SailorNeedBox_PrinestiBalls":	// ждёт ядра
			dialog.text = "Come va, ragazzo?";
			if (CheckCharacterItem(PChar, "BoxOfBalls"))
			{
				link.l1 = "Ecco le tue palle. Pensavo fossero più grandi.";
				link.l1.go = "SailorWantRum_PrinestiBalls_2";
			}
			if (PCharDublonsTotal() >= 30 && CheckAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuestActive") && !CheckAttribute(npchar, "SharlieTutorial_KaznacheyQuest_Poli"))
			{
				link.l2 = "Ti chiami Paul, vero?";
				link.l2.go = "BallsGold_2";
			}
			link.l3 = "Addio.";
			link.l3.go = "exit";
			NextDiag.TempNode = "SailorNeedBox_PrinestiBalls";
		break;

		case "BallsGold_2":
			dialog.text = "Eh... s-sì.";
			link.l1 = "Il tuo nome è nella lista che mi ha dato monsieur Pinchon.";
			link.l1.go = "BallsGold_3";
		break;
		
		case "BallsGold_3":
			dialog.text = "Uff, ho pensato per un momento... Sì, Paul - sono io dunque. Quanto avete lì per me?";
			if (PCharDublonsTotal() >= 20)
			{
				link.l1 = "20 dobloni.";
				link.l1.go = "BallsGold_DatDeneg_gold20";
			}
			if (PCharDublonsTotal() >= 25)
			{
				link.l2 = "25 dobloni.";
				link.l2.go = "BallsGold_DatDeneg_gold25";
			}
			if (PCharDublonsTotal() >= 30)
			{
				link.l3 = "30 dobloni.";
				link.l3.go = "BallsGold_DatDeneg_gold30";
			}
			// link.l4 = "Devo ricontrollare tutto. Tornerò più tardi.";
			// link.l4.go = "BallsGold_DatDeneg_3";
		break;
		
		case "BallsGold_DatDeneg_gold20":
			dialog.text = "Grazie, ragazzo.";
			link.l1 = "...";
			link.l1.go = "BallsGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(20);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			npchar.SharlieTutorial_KaznacheyQuest_Poli = true;
		break;

		case "BallsGold_DatDeneg_gold25":
			dialog.text = "Grazie, ragazzo.";
			link.l1 = "...";
			link.l1.go = "BallsGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(25);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			npchar.SharlieTutorial_KaznacheyQuest_Poli = true;
		break;

		case "BallsGold_DatDeneg_gold30":
			dialog.text = "Grazie, ragazzo.";
			link.l1 = "...";
			link.l1.go = "BallsGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(30);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			npchar.SharlieTutorial_KaznacheyQuest_Poli = true;
		break;
		
		case "BallsGold_DatDeneg_3":
			DialogExit();
			NextDiag.CurrentNode = "SailorNeedBox_PrinestiBalls";
		break;
		
		case "SailorWantRum_PrinestiBalls_2":
			dialog.text = "E che vuoi di più! Se un simile regalo colpisce lo scafo — al massimo schegge nel corpo. Ma se buca la poppa, può rimbalzare su tutto il ponte come una palla!";
			link.l1 = "Un’immagine familiare?";
			link.l1.go = "SailorWantRum_PrinestiBalls_3";
			TakeItemFromCharacter(pchar, "BoxOfBalls");
		break;

		case "SailorWantRum_PrinestiBalls_3":
			dialog.text = "È successo, ragazzo. L’uomo è bravo a inventare armi mortali. Prendi lo shrapnel — non colpisce lontano, non buca lo scafo, ma può spedire una dozzina d’uomini all’altro mondo. O le catene — se colpiscono le vele, le fanno a pezzi! E delle bombe non dico niente — non ne ho mai viste, e grazie al cielo! Roba del diavolo. E costose, per di più.";
			link.l1 = "Mi sono già convinto della potenza delle palle di cannone — guardando la tua povera schiena.";
			link.l1.go = "SailorWantRum_PrinestiBalls_4";
		break;

		case "SailorWantRum_PrinestiBalls_4":
			dialog.text = "Mi hai davvero fatto un gran favore. Non resterò in debito. Ecco — una bottiglia di rum di prima qualità, quasi piena, ah-ah!";
			link.l1 = "E da dove salta fuori? Continuo a sentire che il rum a bordo è finito troppo presto. Con una bottiglia del genere potevi convincere chiunque a trasportare non una, ma tutte le casse dalla stiva.";
			link.l1.go = "SailorWantRum_PrinestiBalls_5";
			GiveItem2Character(PChar, "potionrum");
		break;

		case "SailorWantRum_PrinestiBalls_5":
			dialog.text = "È andata così, ragazzo. Grazie e addio.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SailorNeedBox_PrinestiBalls";
			AddDialogExitQuestFunction("SharlieTutorial_SailorNeedBoxOfBallsFinal");
		break;
		
		// <-- Диалог с матросом, которому нужен ящик с ядрами
		
		// --> Диалог с офицером-торговцем, который торгует всяким
		case "OfficerTorgovets":
			dialog.text = "Ah, monsieur "+pchar.lastname+". Se avete intenzione di dormire — niente da fare. Il nostro cannoniere ha preso il vostro posto letto. Sapete bene che svegliarlo è impossibile.";
			link.l1 = "Ma quando vuole — sente tutto alla perfezione!";
			link.l1.go = "OfficerTorgovets_1";
			/*link.l2 = "Нет.";
			link.l2.go = "exit";
			NextDiag.TempNode = "OfficerTorgovets";*/
		break;

		case "OfficerTorgovets_1":
			dialog.text = "E non è niente. Ho sentito dire che nella squadra di Sharpe c’era addirittura un cannoniere cieco. Puntava solo al suono dei colpi.";
			link.l1 = "Oggi siete particolarmente loquace, monsieur nostromo.";
			link.l1.go = "OfficerTorgovets_2";
		break;

		case "OfficerTorgovets_2":
			dialog.text = "E c’è un motivo! Presto saremo a terra, e quindi è ora di convertire la merce rimasta in sonanti pesos. Al bordello di Saint-Pierre li accolgono sempre volentieri, ah-ah!";
			link.l1 = "Strano che sia voi, e non il tesoriere, a commerciare a bordo.";
			link.l1.go = "OfficerTorgovets_3";
		break;

		case "OfficerTorgovets_3":
			dialog.text = "Lui non sa parlare con la gente! Ecco a cosa serve il nostromo — capace di parlare e agire, ah-ah. Il tesoriere ha i suoi affari — ma io in quelle acque torbide non ci metto piede.";
			link.l1 = "E cosa avete oggi in vendita?";
			link.l1.go = "OfficerTorgovets_4";
		break;

		case "OfficerTorgovets_4":
			if (!CheckAttribute(npchar, "SharlieTutorial_question_0"))
			{
				dialog.text = "L’ultima bottiglia di rum sulla nave, qualche amuleto utile... et voilà! Una vera mappa del tesoro.";
				link.l1 = "Altro che nostromo, dovreste fare il mercante! Vediamo cosa avete.";
				npchar.SharlieTutorial_question_0 = true;
			}
			else
			{
				dialog.text = "Altro?";
				link.l1 = "Vediamo cosa avete.";
			}
			link.l1.go = "OfficerTorgovets_5";
			if (!CheckAttribute(npchar, "SharlieTutorial_question_1"))
			{
				link.l2 = "Amuleti? Come quello che vi pende dal collo?";
				link.l2.go = "OfficerTorgovets_6_question_1_1";
			}
			if (!CheckAttribute(npchar, "SharlieTutorial_question_2"))
			{
				link.l3 = "Scusate... una mappa del tesoro?";
				link.l3.go = "OfficerTorgovets_6_question_2_1";
			}
			link.l4 = "Forse un’altra volta.";
			link.l4.go = "exit";
			NextDiag.TempNode = "OfficerTorgovets_4";
		break;
		
		case "OfficerTorgovets_5":
			DialogExit();
			NextDiag.CurrentNode = "OfficerTorgovets_4";
			sld = ItemsFromID("map_full");
			sld.price = 4000;
			LaunchItemsTrade(NPChar, 0);
		break;
		
		case "OfficerTorgovets_6_question_1_1":
			dialog.text = "Ah, occhio acuto, monsieur. Sì, la 'Testa di Corallo' è una cosa utile. Specialmente per me. Se mai dovessi, Dio non voglia, guidare un abbordaggio — con questa metto in riga la gente in un attimo.";
			link.l1 = "Ci credete davvero?";
			link.l1.go = "OfficerTorgovets_6_question_1_2";
		break;

		case "OfficerTorgovets_6_question_1_2":
			dialog.text = "Non ho bisogno di crederci. È la legge dei Caraibi e della nostra sorte marinaresca. Gli amuleti sono cose utili. Se restate con noi, vi consiglio di portarne un paio — per ogni evenienza.";
			link.l1 = "...";
			link.l1.go = "OfficerTorgovets_4";
			npchar.SharlieTutorial_question_1 = true;
		break;

		case "OfficerTorgovets_6_question_2_1":
			dialog.text = "Oh sì. Nei Caraibi non è raro. Qualcuno ha fortuna — fa un bel bottino. Poi due opzioni: paga le tasse e vive tranquillo, oppure nasconde l’oro in una grotta — e ne restano solo una tomba, il tesoro... e un pezzo di carta.";
			link.l1 = "Così semplice?";
			link.l1.go = "OfficerTorgovets_6_question_2_2";
		break;

		case "OfficerTorgovets_6_question_2_2":
			dialog.text = "Non proprio. Le mappe costano care, e attirano altri cacciatori come voi. E il bottino a volte a malapena ripaga gli sforzi. Persino il grande Albert Blackwood non ha avuto successo al primo colpo. Fate del tesoro la vostra professione — più ne trovate, più grandi saranno le ricompense. E se comprate un amuleto della fortuna — sarà ancora più divertente!";
			link.l1 = "...";
			link.l1.go = "OfficerTorgovets_4";
			npchar.SharlieTutorial_question_2 = true;
		break;
		// <-- Диалог с офицером-торговцем, который торгует всяким
		
		// --> Диалог с офицером-казначеем
		case "OfficerKaznachey":
			dialog.text = "Monsieur "+pchar.lastname+"! Un minuto, per favore.";
			link.l1 = "Di nuovo con la morale, monsieur Pinchon? Non ho toccato la vostra preziosa inchiostro!";
			link.l1.go = "OfficerKaznachey_2";
		break;

		case "OfficerKaznachey_2":
			dialog.text = "E con cosa scrivete di nascosto nel vostro libretto? Acqua santa? Nella lista delle proprietà dei passeggeri non c’erano inchiostri. Ad ogni modo, ora avete problemi più seri.";
			link.l1 = "...";
			link.l1.go = "OfficerKaznachey_3";
		break;

		case "OfficerKaznachey_3":
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_ActivateWindlass")) sStr = "E inoltre — duecento per il verricello danneggiato. La cima dell’ancora si è spezzata.";
			dialog.text = "Vi ricordo che dovete ancora trenta pesos alla cassa della nave — per la botte d’acqua piovana rovinata. Il vostro comico tentativo di lavare la camicia avrebbe potuto costare ancora di più, se non fosse tornata la pioggia. "+sStr+"";
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_ActivateWindlass"))
			{
				if (sti(pchar.Money) >= 230)
				{
					link.l1 = "Proprio quello che mi mancava — debiti subito all’arrivo. Ecco qui.";
					link.l1.go = "OfficerKaznachey_4";
				}
			}
			else
			{
				if (sti(pchar.Money) >= 30)
				{
					link.l1 = "Proprio quello che mi mancava — debiti subito all’arrivo. Ecco qui.";
					link.l1.go = "OfficerKaznachey_4";
				}
			}
			link.l2 = "Tutto qui? Non è un debito di gioco, suvvia. Non ho tempo adesso. Dovrete aspettare fino all’arrivo in porto.";
			link.l2.go = "OfficerKaznachey_3_1";
		break;

		case "OfficerKaznachey_3_1":
			dialog.text = "Peccato. Allora andiamo al punto — ho un lavoro per voi.";
			link.l1 = "Non siete molto bravo con le persone, vero?";
			link.l1.go = "OfficerKaznachey_6";
		break;
		
		case "OfficerKaznachey_4":
			dialog.text = "Un momento, devo contare.";
			link.l1 = "Dopo cena non dimenticate di contare anche le briciole del mio pane rimaste sul tavolo.";
			link.l1.go = "OfficerKaznachey_5";
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_ActivateWindlass")) AddMoneyToCharacter(pchar, -230);
			else AddMoneyToCharacter(pchar, -30);
		break;

		case "OfficerKaznachey_5":
			dialog.text = "Congratulazioni. Ora la cassa della nave non ha più questioni con voi. Per ora\nAndiamo subito al sodo — ho un lavoro per voi.";
			link.l1 = "Non andate molto d’accordo con la gente, vero?";
			link.l1.go = "OfficerKaznachey_6";
		break;

		case "OfficerKaznachey_6":
			dialog.text = "Con la gente — non molto. Ma con i conti sì\nE voi, monsieur "+pchar.lastname+", sapete contare?";
			if (IsCharacterPerkOn(pchar, "HT2"))
			{
				link.l1 = "(Contabile) Non mi sono mai stati estranei né i libri contabili, né le cambiali. E conosco anche il concetto di zero.";
				link.l1.go = "OfficerKaznachey_7";
			}
			else
			{
				link.l1 = "Quanto basta per far durare l’esiguo sussidio paterno fino a fine stagione.";
				link.l1.go = "OfficerKaznachey_8";
			}
		break;

		case "OfficerKaznachey_7":
			dialog.text = "Oooh! Peccato non me lo abbiate detto prima — questo viaggio avrebbe potuto essere molto più interessante.";
			link.l1 = "Avevate menzionato un lavoro?";
			link.l1.go = "OfficerKaznachey_9";
		break;

		case "OfficerKaznachey_8":
			dialog.text = "Per il vostro stesso bene — spero che non diventiate mai armatore. Mandereste in rovina non solo voi stessi, ma anche tutti quelli a bordo.";
			link.l1 = "Avevate menzionato un lavoro?";
			link.l1.go = "OfficerKaznachey_9";
		break;
		
		case "OfficerKaznachey_9":
			dialog.text = "Sì. Non so se lo sapete, ma il tesoriere e il medico sono secondi solo al capitano\n"+
			"Andare in mare senza questi due significa rischiare il denaro, e senza denaro una nave è solo un pezzo di legno molto costoso\n"+
			"Senza un tesoriere anche una piccola scialuppa può mandare in rovina il suo capitano. E il primo combattimento senza medico può decimare l’equipaggio, dando inizio a un processo lungo e costoso di reclutamento e addestramento\n"+
			"Fortunatamente per noi, io ricopro entrambi i ruoli. Perciò posso condurre affari personali e usufruire di piccoli servizi dell’equipaggio\n"+
			"Naturalmente, i servizi sono ben retribuiti — e questo è proprio un buon momento per iniziare\n"+
			"Voglio che prendiate questa lista, il forziere con i dobloni — e distribuiate il salario ai membri dell’equipaggio\n"+
			"Strettamente secondo la lista! È per questo che vi ho chiesto se sapete contare.";
			link.l1 = "E perché non lo fate voi? In fondo, se la gente aspetta la paga — che vengano loro stessi.";
			link.l1.go = "OfficerKaznachey_10";
		break;

		case "OfficerKaznachey_10":
			dialog.text = "Ho troppi impegni in questo momento. Mancano solo un paio di giorni alla fine del viaggio, e presto ci sarà una fila di cento persone qui, tutte a chiedere con insistenza la loro paga.";
			link.l1 = "Avete menzionato dei dobloni...";
			link.l1.go = "OfficerKaznachey_11";
		break;
		
		case "OfficerKaznachey_11":
			dialog.text = "Moneta d’oro spagnola. Una valuta solida e il vero indicatore di ricchezza. I servizi più rari, costosi e preziosi — solo per questi\n"+
			"Si conservano in forzieri come questo, per comodità.";
			link.l1 = "E cosa ci guadagno io?";
			link.l1.go = "OfficerKaznachey_12";
		break;

		case "OfficerKaznachey_12":
			if (IsCharacterPerkOn(pchar, "HT2"))
			{
				dialog.text = "(Contabile) 150 pesos, più 5 dobloni extra perché siete quasi un mio collega. E la possibilità di cambiare pesos in dobloni a un buon tasso.";
			}
			else
			{
				dialog.text = "150 pesos e la possibilità di cambiare pesos in dobloni. Non è molto, ma nemmeno il lavoro è complicato.";
			}
			link.l1 = "Va bene. Datemi la lista e il forziere.";
			link.l1.go = "OfficerKaznachey_11_agree";
			link.l2 = "Temo che questo tipo di lavoro non faccia per me. Addio, monsieur Pinchon.";
			link.l2.go = "OfficerKaznachey_11_otkaz";
		break;

		case "OfficerKaznachey_11_otkaz":
			dialog.text = "Scelta vostra. In tal caso, non disturbatemi mentre lavoro, monsieur "+pchar.lastname+".";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			DelLandQuestMark(npchar);
		break;

		case "OfficerKaznachey_11_agree":
			if(GetItemsWeight(pchar) + sti(Items[GetItemIndex("Chest")].weight) > GetMaxItemsWeight(pchar))
			{
				dialog.text = "Prego. Ma per l’amor di Dio — non dimenticate di estrarre i dobloni dal forziere, attenetevi rigorosamente alla lista e non osate tenere nulla per voi. Mi aspetto di riavere anche il forziere vuoto\n"+
				"E cercate di non sforzarvi troppo, monsieur. E perché vi siete caricato di tutta questa roba? Vi consiglio di lasciare qualcosa in un baule.";
			}
			else
			{
				dialog.text = "Prego. Ma per l’amor di Dio — non dimenticate di estrarre i dobloni dal forziere, attenetevi rigorosamente alla lista e non osate tenere nulla per voi. Mi aspetto di riavere anche il forziere vuoto.";
			}
			link.l1 = "Come desiderate. A presto, monsieur Pinchon.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_QuestRazdatZoloto");
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_ActivateWindlass")) AddQuestRecordInfo("SharlieTutorial_ListOfSailors", "1");
			else AddQuestRecordInfo("SharlieTutorial_ListOfSailors", "2");
			GiveItem2Character(PChar, "chest");
			if (!isMultiObjectKnown("gold_dublon"))
			{
				SetAlchemyRecipeKnown("gold_dublon");
				SetAlchemyRecipeKnown("Chest");
			}
		break;
		
		case "OfficerKaznachey_12_Wait": // ждёт выполнения квеста
			dialog.text = "Come va? Hai distribuito il pagamento? Hai portato tutto? Il resto dei dobloni, lo scrigno vuoto?";
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuest") && sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) == 3 && CheckCharacterItem(PChar, "chest_open") && GetCharacterItem(pchar, "gold_dublon") >= 18)
			{
				link.l1 = "Tutto pronto.";
				link.l1.go = "OfficerKaznachey_13";
			}
			link.l2 = "Non ancora, monsieur Pinchon.";
			link.l2.go = "exit";
			NextDiag.TempNode = "OfficerKaznachey_12_Wait";
		break;

		case "OfficerKaznachey_13":
			dialog.text = "Bene, vediamo...";
			link.l1 = "...";
			link.l1.go = "OfficerKaznachey_14";
		break;

		case "OfficerKaznachey_14":
			addGold = GetCharacterItem(pchar, "gold_dublon");
			if (addGold >= 18 && addGold <= 39)
			{
				dialog.text = "E dire che sapevi contare. Qui ce n'è meno del dovuto. Questo significa che la mia contabilità si è appena complicata, e mi hai creato un nuovo problema invece di risolvere quello attuale\n"+
				"Pertanto, monsieur "+pchar.lastname+", non ti spetta alcun pagamento.";
				link.l1 = "Ma almeno mi cambierai i dobloni?";
				link.l1.go = "OfficerKaznachey_15_gold_115";
			}
			if (addGold >= 41)
			{
				dialog.text = "E dire che sapevi contare. Qui ce n'è più del dovuto. Questo significa che la mia contabilità si è appena complicata, e mi hai creato un nuovo problema invece di risolvere quello attuale\n"+
				"Pertanto, monsieur "+pchar.lastname+", non ti spetta alcun pagamento.";
				link.l1 = "E per lo scambio?";
				link.l1.go = "OfficerKaznachey_15_gold_115";
			}
			if (addGold == 40)
			{
				if (IsCharacterPerkOn(pchar, "HT2"))
				{
					dialog.text = "Tutto preciso. È confortante vedere che le nuove generazioni sanno trattare con i numeri. Grazie, monsieur "+pchar.lastname+". Ecco il tuo pagamento — e un piccolo bonus, da quasi collega.";
					link.l1 = "E per lo scambio?";
					link.l1.go = "OfficerKaznachey_15_gold_100";
					AddItems(pchar, "gold_dublon", 5);
				}
				else
				{
					dialog.text = "Tutto preciso. È confortante vedere che le nuove generazioni trattano il denaro con responsabilità. Grazie, monsieur "+pchar.lastname+". Ecco il tuo pagamento.";
					link.l1 = "Cambi ancora i dobloni?";
					link.l1.go = "OfficerKaznachey_15_gold_105";
				}
				AddMoneyToCharacter(pchar, 300);
				AddCharacterSkillPoints(pchar, "Commerce", 1);
			}
			DelLandQuestMark(npchar);
			TakeItemFromCharacter(pchar, "chest_open");
			RemoveDublonsFromPCharTotal(addGold);
			AddItems(npchar, "gold_dublon", 100);
			pchar.questTemp.SharlieTutorial_KaznacheyQuestCompleted = true;
			DeleteAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuestActive");
			npchar.Merchant.type = "SharlieTurorialK";
			pchar.SharlieTutorial.FullyCompleted = sti(pchar.SharlieTutorial.FullyCompleted) + 1;
		break;
		
		case "OfficerKaznachey_15_gold_115":
			dialog.text = "Perché no. Centoquindici pesos per un doblone. Rivolgiti a me se ti interessa.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "TreasurerTrade";
			npchar.questTemp.GoldPrice = 115;
		break;

		case "OfficerKaznachey_15_gold_105":
			dialog.text = "Ma certo. Centocinque pesos per un doblone. Rivolgiti a me se ti interessa\n"+
			"E permettimi un consiglio: se, Dio non voglia, il destino ti mette al comando di una nave — assumi un tesoriere come prima cosa. Anche un principiante ti farà risparmiare una fortuna.";
			link.l1 = "Grazie, monsieur Pinchon.";
			link.l1.go = "exit";
			NextDiag.TempNode = "TreasurerTrade";
			npchar.questTemp.GoldPrice = 105;
		break;

		case "OfficerKaznachey_15_gold_100":
			dialog.text = "Ma certo! Cento pesos per un doblone — è un tasso onesto. Le banche dei Caraibi ti avrebbero spennato di più\n"+
			"E permettimi un consiglio: se, Dio non voglia, il destino ti mette al comando di una nave — assumi un tesoriere come prima cosa. Anche un principiante ti farà risparmiare una fortuna.";
			link.l1 = "Grazie, monsieur Pinchon.";
			link.l1.go = "exit";
			NextDiag.TempNode = "TreasurerTrade";
			npchar.questTemp.GoldPrice = 100;
		break;

		case "OfficerKaznachey_16_Proval": // Если не выполнил задание, то отбирает дублоны
			dialog.text = "Te la spassi, monsieur "+pchar.lastname+"?";
			link.l1 = "Anche tu sei stato mandato nella stiva?";
			link.l1.go = "OfficerKaznachey_16_Proval_2";
		break;

		case "OfficerKaznachey_16_Proval_2":
			dialog.text = "Io sono il medico di bordo, "+pchar.lastname+"! Presto la sala ufficiali sarà piena di feriti, e vedrò più sangue di qualsiasi partecipante alla battaglia. E anche se non fossi un medico, ma solo un tesoriere — in battaglia mi sarei schierato come tutti gli altri. No, l’unico che è stato mandato a poltrire nella comoda stiva — sei tu.";
			link.l1 = "Allora cosa ci fai qui?";
			link.l1.go = "OfficerKaznachey_16_Proval_3";
		break;
		
		case "OfficerKaznachey_16_Proval_3":
			dialog.text = "Bitwa zacznie się dopiero za kilka godzin, więc to idealny czas, żeby zamknąć dzienny rachunek. Macie moją skrzynkę z dublonami, de Maure. Łaskawie ją zwróćcie.";
			if (GetCharacterItem(pchar, "gold_dublon") >= 1 || GetCharacterItem(pchar, "chest") >= 1 || GetCharacterItem(pchar, "chest_open") >= 1)
			{
				link.l1 = "Zabierajcie. I nie pokazujcie już tutaj swojej gęby.";
				link.l1.go = "OfficerKaznachey_16_Proval_4";
			}
			else
			{
				link.l1 = "Zostawiłem wasze graty w innym miejscu.";
				link.l1.go = "OfficerKaznachey_16_Proval_5";
			}
		break;
		
		case "OfficerKaznachey_16_Proval_4":
			addGold = GetCharacterItem(pchar, "gold_dublon");
			dialog.text = "Nie miałem zamiaru. Nie jestem przecież szczurem lądowym - moje miejsce nie jest w ładowni. Żegnajcie.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_TrumLoad_4");
			if (GetCharacterItem(pchar, "gold_dublon") >= 1 || GetCharacterItem(pchar, "chest") >= 1) ChangeCharacterComplexReputation(pchar, "nobility", -3);
			else ChangeCharacterComplexReputation(pchar, "nobility", -6);
			RemoveDublonsFromPCharTotal(addGold);
			AddItems(npchar, "gold_dublon", addGold);
			TakeItemFromCharacter(pchar, "chest");
			TakeItemFromCharacter(pchar, "chest_open");
		break;
		
		case "OfficerKaznachey_16_Proval_5":
			dialog.text = "W innym miejscu... Omówimy to po bitwie - w obecności kapitana. Do zobaczenia.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_TrumLoad_4");
			ChangeCharacterComplexReputation(pchar, "nobility", -6);
		break;

		case "TreasurerTrade":
			dialog.text = "Interessato ai dobloni, monsieur "+pchar.lastname+"?";
			link.l1 = "Facciamo affari.";
			link.l1.go = "TreasurerTrade_1";
			link.l2 = "Non adesso.";
			link.l2.go = "exit";
			NextDiag.TempNode = "TreasurerTrade";
		break;

		case "TreasurerTrade_1":
			DialogExit();
			LaunchItemsTrade(NPChar, 0);
			NextDiag.CurrentNode = "TreasurerTrade";
		break;

	// <-- Диалог с офицером-казначеем

	// --> Матрос сообщает о приближающихся кораблях
	case "Sailor_Trevoga":
		dialog.text = "Capitano, allarme! Pirati all'orizzonte!";
		link.l1 = "...";
		link.l1.go = "Sailor_Trevoga_2";
		SetCameraDialogMode(npchar);
		CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Captain"));
		PlaySound("Ship\rynda_alarm.wav");
	break;

	case "Sailor_Trevoga_2":
		StartInstantDialog("SharlieTutorial_Captain", "Sailor_Trevoga_3", "Quest\Sharlie\Tutorial.c");
	break;

	case "Sailor_Trevoga_3":
		dialog.text = "Alonso, accompagna cortesemente monsieur "+pchar.lastname+" nella stiva. E assicurati che monsieur Drussac si degni di svegliarsi e prepari gli equipaggi dei cannoni per la battaglia.";
		link.l1 = "Capitano, sono pronto a combattere! Un nobile non può...";
		link.l1.go = "Sailor_Trevoga_4_fencing";
		link.l2 = "Se posso aiutare in qualche modo...";
		link.l2.go = "Sailor_Trevoga_4_leadership";
		link.l3 = "Quindi niente Borgogna?...";
		link.l3.go = "Sailor_Trevoga_4_fortune";
	break;

	case "Sailor_Trevoga_4_fencing":
		dialog.text = "Alonso, portatelo via. Al lavoro, fannulloni! Issate le vele!";
		link.l1 = "...";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("SharlieTutorial_Trevoga_7");
		AddCharacterSkillPoints(pchar, "FencingL", 1);
		AddCharacterSkillPoints(pchar, "FencingS", 1);
		AddCharacterSkillPoints(pchar, "FencingH", 1);
		AddCharacterSkillPoints(pchar, "Pistol", 1);
	break;

	case "Sailor_Trevoga_4_leadership":
		dialog.text = "Alonso, portatelo via. Al lavoro, fannulloni! Issate le vele!";
		link.l1 = "...";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("SharlieTutorial_Trevoga_7");
		AddCharacterSkillPoints(pchar, "Leadership", 1);
	break;

	case "Sailor_Trevoga_4_fortune":
		dialog.text = "Alonso, portatelo via. Al lavoro, fannulloni! Issate le vele!";
		link.l1 = "...";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("SharlieTutorial_Trevoga_7");
		AddCharacterSkillPoints(pchar, "Fortune", 1);
	break;
		// <-- Матрос сообщает о приближающихся кораблях
		
		// --> Диалог с пиратом в трюме
		case "EnemyPirate_1":
			dialog.text = "Diavolo! Che teste dure!";
			link.l1 = "...";
			link.l1.go = "EnemyPirate_2";
			//PlaySound("VOICE\Spanish\OliverTrast01.wav"); //вставить для испанской версии
			PlaySound("interface\abordage.wav");
			PlaySound("interface\abordage.wav");
		break;

		case "EnemyPirate_2":
			dialog.text = "E tu che ci fai qui?! Hai abbandonato i tuoi e ti nascondi dalla battaglia, topo di stiva?! Ora ti apro la pancia!";
			link.l1 = "Hai scelto la stiva sbagliata. Sarò io a sventrarti.";
			link.l1.go = "EnemyPirate_3_Fencing";
			link.l2 = "Non stai nemmeno in piedi, e la maggior parte del sangue addosso a te non è nemmeno il tuo.";
			link.l2.go = "EnemyPirate_3_Leadership";
			if (IsCharacterPerkOn(pchar, "HT1"))
			{
				link.l3 = "(Duellante) Questo mi mancava.";
				link.l3.go = "EnemyPirate_3_Duelyant";
			}
		break;

		case "EnemyPirate_3_Fencing":
			dialog.text = "He-he. Provaci, damerino.";
			link.l1 = "...";
			link.l1.go = "EnemyPirate_4";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;

		case "EnemyPirate_3_Leadership":
			dialog.text = "He-he. Allora non ho nulla da perdere.";
			link.l1 = "...";
			link.l1.go = "EnemyPirate_4";
			AddCharacterSkillPoints(pchar, "Leadership", 1);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

		case "EnemyPirate_3_Duelyant":
			dialog.text = "Cosa stai blaterando?!";
			link.l1 = "Due mesi. Per due mesi ho dovuto tenere la spada nel fodero. Balliamo!";
			link.l1.go = "EnemyPirate_4";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;
		
		case "EnemyPirate_4":
			DialogExit();
			AddDialogExitQuestFunction("SharlieTutorial_TrumBitva_2");
		break;
		
		// <-- Диалог с пиратом в трюме
		
		// --> Диалог с выжившим матросом
		case "SailorAlive_1":
			dialog.text = "Almeno voi siete vivi... Io sono finito. Mi hanno colpito forte sul timone...";
			link.l1 = "Cosa è successo?!";
			link.l1.go = "SailorAlive_2";
			DelLandQuestMark(npchar);
		break;

		case "SailorAlive_2":
			dialog.text = "È successo un abbordaggio. Ar-r-gh! Che teste dure!\nAscoltate bene: abbiamo tenuto il ponte dei cannoni, ma sopra è appena cominciata la festa. Vi giuro che torneranno. Prendete la mitraglia! Diavolo, attenti! È carica!";
			if (IsCharacterPerkOn(pchar, "HT4"))
			{
				link.l1 = "(Tiratore scelto) Non preoccuparti per me. Chi si avvicina, si riempie di buchi.";
			}
			else link.l1 = "...";
			link.l1.go = "SailorAlive_3";
		break;

		case "SailorAlive_3":
			dialog.text = "C'è della mitraglia. Se la usate bene — potreste prenderne due o tre in una volta\nCredo in voi, "+pchar.name+". Dopo averli respinti, frugate tra i cadaveri. Magari trovate qualcosa da bere per me... altrimenti non vi sarò d'aiuto.";
			link.l1 = "Resisti, Alonso. Eccoli che arrivano!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_TrumBitva_5");
			GiveItem2Character(PChar, "pistol3");
			EquipCharacterByItem(PChar, "pistol3");
			AddItems(pchar, "grapeshot", 5);
			AddItems(pchar, "GunPowder", 5);
			LAi_GunSetChargeQuant(pchar, GUN_ITEM_TYPE, 1);
		break;

		case "SailorAlive_11":
			dialog.text = "Bene... Avete fatto un buon lavoro, "+pchar.name+". Avete trovato qualcosa per me?";
			if (CheckCharacterItem(PChar, "quest_potion"))
			{
				link.l1 = "Penso sia questa. Anche se ha un aspetto sospetto.";
				link.l1.go = "SailorAlive_12";
			}
			link.l2 = "Sto cercando!";
			link.l2.go = "exit";
			NextDiag.TempNode = "SailorAlive_11";
		break;
		
		case "SailorAlive_12":
			dialog.text = "E non ha nemmeno un cattivo sapore, ha-ha! Grazie, "+pchar.name+". E quei tre li hai stesi bene. Se sei davvero un nobile cavaliere, allora prendi il comando. In due riusciremo sicuramente a tenere il ponte, e se anche i ragazzi sopra riescono a resistere — la giornata sarà nostra!";
			link.l1 = "...";
			//link.l1.go = "exit";
			link.l1.go = "SailorAlive_13";
			//AddDialogExitQuestFunction("SharlieTutorial_TrumBitva_7");
			TakeItemFromCharacter(pchar, "quest_potion");
			PlaySound("Ambient\Tavern\glotok_001.wav");
			DelLandQuestMark(npchar);
		break;

		case "SailorAlive_13":
			/*if (CheckAttribute(npchar, "fighter"))
			{
				dialog.text = "Ecco, molto meglio. Hai caricato la mitraglia?";
				link.l1 = "Ci sto lavorando... Ma perché questo silenzio improvviso?";
				link.l1.go = "SailorAlive_14";
				SetMusic("");
			}
			else
			{
				dialog.text = "Se sei davvero un nobile cavaliere, allora prendi il comando.";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "SailorAlive_13";
			}*/
			dialog.text = "Ecco, molto meglio. Hai caricato la mitraglia?";
			link.l1 = "Ci sto lavorando... Ma perché questo silenzio improvviso?";
			link.l1.go = "SailorAlive_14";
			SetMusic("");
			LAi_SetActorType(npchar);
			LAi_ActorSetGroundSitMode(npchar);
			LAi_ActorAnimation(npchar, "ground_standup", "1", -1);
		break;	

		case "SailorAlive_14":
			dialog.text = "È per rendere la cosa ancora più drammatica. Sta per cominciare.";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			AddDialogExitQuestFunction("SharlieTutorial_TrumBitva_8");
		break;
		// <-- Диалог с выжившим матросом
		
		// --> Диалог с Алонсо после боя
		case "AfterBattle_Alonso_1":
			dialog.text = "E finiamo esattamente dove abbiamo cominciato. Grazie per avermi salvato la pelle, "+pchar.name+".";
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_Ranen"))
			{
				link.l1 = "Direi che siamo pari. Non ricordo nemmeno come mi hai tirato fuori da là.";
			}
			else
			{
				link.l1 = "Direi che siamo pari. Se non fosse stato per te e per i ragazzi, sarei rimasto lì.";
			}
			link.l1.go = "AfterBattle_Alonso_2";
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "tutorial_4", "", -1);
			CharacterTurnByLoc(pchar, "quest", "quest6");
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "tutorial_5", "", -1);
			CharacterTurnByLoc(npchar, "quest", "quest7");
		break;

		case "AfterBattle_Alonso_2":
			dialog.text = "Potevate restare nascosti nella stiva, come vi era stato ordinato. Peccato che il capitano non sia sopravvissuto abbastanza da darvi una bella strigliata.";
			link.l1 = "Abbiamo dovuto tirarlo fuori da sotto una montagna di cadaveri. Quanti bastardi ha abbattuto?";
			link.l1.go = "AfterBattle_Alonso_3";
		break;

		case "AfterBattle_Alonso_3":
			dialog.text = "Qualcuno ha detto che ne ha fatti fuori tre. Altri dicono almeno una dozzina. Penso che solo il diavolo tenesse il conto esatto.";
			link.l1 = "Non mi hai ancora spiegato perché è andata così.";
			link.l1.go = "AfterBattle_Alonso_4";
		break;

		case "AfterBattle_Alonso_4":
			dialog.text = "Cosa c'è da spiegare? I cannoni da sedici libbre non ci hanno salvati da una sola brigantina pirata. Questo è ciò che significa una nave fatta per affari reali\n"+
			"È arrivata in un lampo e, mentre ci stavamo girando, ci ha colpiti con la mitraglia ed è subito salita all'arrembaggio. Avreste dovuto vedere il ponte — non c'era più nulla da portare al medico\n"+
			"La cosa peggiore di combattere contro i pirati — è che non c'è alcun guadagno. Straccioni, tutti quanti. Non siamo riusciti nemmeno a prendere la loro brigantina.";
			link.l1 = "E adesso che succederà?";
			link.l1.go = "AfterBattle_Alonso_5";
		break;

		case "AfterBattle_Alonso_5":
			dialog.text = "La nave è ancora a galla e abbiamo abbastanza uomini per portarvi a Saint-Pierre in orario, dove cercherò un nuovo capitano e voi troverete vostro fratello e gli racconterete le vostre avventure. E poi — solo Dio lo sa.\n"+
			"Ma una cosa la so per certo — vi troverete bene qui da noi. Niente male per un topo di terra, "+pchar.name+".";
			link.l1 = "...";
			link.l1.go = "AfterBattle_Alonso_6";
		break;

		case "AfterBattle_Alonso_6":
			dialog.text = "Ah-ah! Adesso comincerete a vomitare. Non vergognatevi. È la paura che esce fuori. Benvenuto ai Caraibi!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_SeaNearMartinique");
		break;
		
		
		// <-- Диалог с Алонсо после боя
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
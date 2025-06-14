// НПС по квесту Суп из черепахи
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Di che hai bisogno?";
			link.l1 = "No, niente.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// денщик Фокса - Бенджамин Джонс
		case "BenjaminJons":
			if (CheckAttribute(PChar, "questTemp.Terrapin.Benjamin") && pchar.questTemp.Terrapin == "baster")
			{
				dialog.text = "Il signor colonnello è fuori in esercitazione militare al momento. Che ci vuoi fare con lui, capitano?";
				link.l1 = "Questa volta, Ben, sei proprio tu che mi servi. Ho brutte notizie su tua sorella Molly. Quella splendida ragazza sembra essersi cacciata in un bel guaio. È stata catturata dai pirati di Tortuga. Ha bisogno d’aiuto e ha chiesto di avvertirti. L’uomo che si è assunto il rischio di portarmi il messaggio è stato ammazzato, ma prima di tirare le cuoia, è riuscito a raccontarmi della tua sorella.";
				link.l1.go = "sister";
				break;
			}
			sld = characterFromId("Fox");
			if (sld.location == pchar.location)
			{
				dialog.text = "Se sei diretto dal colonnello Fox, allora gira i tacchi e vattene per dove sei venuto. Oggi non riceve nessuno.";
				link.l1 = "Molto bene, allora.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Il colonnello non è qui. Torna più tardi.";
				link.l1 = "D'accordo...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "BenjaminJons";
		break;
		
		case "sister":
			dialog.text = "Ah! Sei il primo uomo che abbia mai chiamato mia sorella 'bella'. Il buon Dio le ha dato il corpo d’un granatiere e il corno di Gerico al posto della voce. La nostra Molly sa difendersi da sola. Ma la fantasia del Signore non si è fermata sotto il suo mento, oh no: la cosa più straordinaria che abbia fatto è stata piantare la pelosa, butterata faccia del nostro defunto padre proprio sopra il suo petto. E ti assicuro, signore, la faccia del vecchio mio faceva svenire persino i cavalli.";
			link.l1 = "Vedo che non ti sei scomposto più di tanto...";
			link.l1.go = "sister_1";
		break;
		
		case "sister_1":
			dialog.text = "E perché mai dovrebbe lei arrivare a Tortuga? Molly serve Catherine Fox, la figlia del nostro valoroso colonnello. Catherine stava arrivando dall’Europa per festeggiare il compleanno del padre. Ma la squadra navale con cui viaggiava la sua nave è rimasta indietro.\nSe vuoi davvero vedere la vera Molly Jones e la sua dama – bellissima, tra l’altro – torna qui tra un mese. Non un giorno prima.";
			link.l1 = "Pare che tua sorella Molly Jones sia al servizio della signora Fox e al momento risieda dall’altra parte dell’Atlantico?";
			link.l1.go = "sister_2";
		break;
		
		case "sister_2":
			dialog.text = "Proprio così! L’ultimo corriere ci ha fatto sapere che uno squadrone della marina, mandato dallo stesso Lord Protettore Cromwell, sarebbe dovuto salpare da Londra appena un mese fa. Il brigantino 'Albatross', con Catherine a bordo, doveva accompagnarli. Sapremo se è vero quando arriverà la prossima nave postale. Anche se le navi non sono ancora giunte, il colonnello aveva severamente proibito all’‘Albatross’ di salpare da sola.\nSapevi che la sua amata moglie è morta durante un assalto di corsari francesi? Non è stato facile per il colonnello, e ancora oggi teme i pericoli dell’oceano... Quindi non posso aiutarti con Molly Jones, capitano! Di ragazze colone che si chiamano Molly ce ne sono a bizzeffe! E poi, portare il cognome Jones in Britannia è come non averne nessuno!\nOgni vecchio lupo di mare ad Antigua conosce me e il mio comandante. Non mi stupisce che qualche poveretta nei guai cerchi il mio aiuto. Vorrei farlo, ma non ho nemmeno un doblone per il riscatto. Il colonnello mi deve tre mesi di paga, il mio salario – come quello di tutti gli altri – arriverà solo con l’‘Albatross’.";
			link.l1 = "A quanto pare mi sbagliavo, allora. Ma grazie comunque per la spiegazione.";
			link.l1.go = "sister_3";
		break;
		
		case "sister_3":
			dialog.text = "Affatto, capitano.";
			link.l1 = "...";
			link.l1.go = "sister_4";
		break;
		
		case "sister_4":
			DialogExit();
			AddQuestRecord("Terrapin", "3");
			pchar.questTemp.Terrapin.Catherina = "take"; // возможен вариант с Кати
			DeleteAttribute(pchar, "questTemp.Terrapin.Benjamin");
		break;
		
		// Робер Мартэн
		case "Rober":
			PlaySound("Voice\English\sharlie\Rober Marten-01.wav");
			dialog.text = "Cosa vuoi?! Non ho voglia di ciarlare.";
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "rober")
			{
				link.l1 = "Ho degli affari da proporti, capitano. Vedo che non sei dell'umore più allegro, magari la mia offerta ti tirerà un po' su.";
				link.l1.go = "rober_1";
			}
			else
			{
				link.l1 = "Calmati, buttati giù un po’ di rum. Colpa mia, compare. Perdona questo scellerato.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Rober";
		break;
		
		case "rober_1":
			DelMapQuestMarkCity("BasTer");
			pchar.quest.Terrapin_LateBaster.over = "yes"; //снять таймер
			dialog.text = "Mi piace come suona! E la tua faccia... giurerei di averla già vista da qualche parte, ma non ricordo proprio dove. Vai, racconta tutto!";
			link.l1 = "So dei tuoi affari con Thibaut... Calmati, compare! Non hai nulla da temere da me. Ho una proposta da farti.";
			link.l1.go = "rober_2";
		break;
		
		case "rober_2":
			dialog.text = "Maledizione all’inferno! Maledetto quel porco ubriaco!... Non sono riuscito a...";
			link.l1 = "Hai colpito nel segno. Il tuo marinaio aveva la lingua lunga, ma le sue chiacchiere non sono arrivate oltre me. E non andranno oltre, visto che sei stato tu a tappare la bocca, vero?";
			link.l1.go = "rober_3";
		break;
		
		case "rober_3":
			dialog.text = "Caramba! Ora ti riconosco! Sei tu quello che ha mandato in rovina il colonnello Doiley e s'è preso tutta la sua isola! Hai avuto a che fare con la Compagnia Olandese delle Indie Occidentali, ti mescoli con i baroni della terraferma... Il tuo nome è... "+GetFullName(pchar)+", vero?";
			link.l1 = "Hai delle informazioni piuttosto precise. Sì, sono io. Ma potresti calmarti un attimo, Robert?";
			link.l1.go = "rober_4";
		break;
		
		case "rober_4":
			PlaySound("Voice\English\sharlie\Rober Marten-02.wav");
			dialog.text = "Argh! E come diavolo vuoi che mi calmi, quando uno dei più rinomati lupi di mare dell’arcipelago s’è messo sulle mie tracce e, per giunta, ha scoperto delle mie faccende! Maledizione a me e al giorno in cui ho assaltato quella brigantina! Che vuoi da me, dannato?";
			link.l1 = "Chiudi quel becco e ascoltami. Mi pare che tutti e due vogliamo la testa di Levasseur su un piatto d’argento. Quel vanaglorioso spaccone si è fatto troppo audace e ha fatto infuriare gente pericolosa. Ho intenzione di cambiare le carte in tavola sull’isola e rimettere de Poincy al suo posto, ma non voglio che il sangue della mia gente scorra inutilmente, tanto meno per colpa di quel lurido ladro. Tu puoi darmi una mano. E io posso aiutare te e Thibaut a tenervi stretti i vostri privilegi.";
			link.l1.go = "rober_5";
		break;
		
		case "rober_5":
			dialog.text = "Aspetta, aspetta! Non credo alle mie orecchie! La fortuna oggi mi sorride. Hai ragione, puntiamo allo stesso bottino. Con te, potrebbe diventare tutto molto più... gustoso. Thibaut sa menar la spada, sì, ma gli manca il fegato per sgozzare lo zio... Ma un vecchio squalo astuto come te potrebbe farlo eccome. La tua fama ti precede.\nNon ho bisogno delle tue promesse, ma ti darò una mano in cambio della ragazza. Mi serve come ostaggio finché non avrò sbrigato le mie faccende nei Caraibi. Presto, le fregate inglesi mi daranno la caccia. Che diavolo mi ha preso ad assaltare quella bricchetta! Sembrava una preda facile, staccata dalla squadra...";
			link.l1 = "Che aveva di tanto speciale? Quella ragazza che celavi a Levasseur?";
			link.l1.go = "rober_6";
		break;
		
		case "rober_6":
			dialog.text = "Sì. Devi convincere Thibaut a separarsi dalla ragazza. Gli avevo chiesto di badare a lei mentre scoprivo chi diavolo fosse, ma questa 'Miss Jones', o come diavolo si chiama, gli ha completamente fatto perdere la testa e ora Henry la nasconde persino da me! Porta qui quella sirena ammaliatrice e ti organizzerò un incontro con Levasseur fuori città. A quel punto avrai l’occasione per tendergli un’imboscata. Ti aspetterò a Fisheye Beach.";
			link.l1 = "Affare fatto. Ora dimmi come mettere le mani su Thibaut.";
			link.l1.go = "rober_7";
		break;
		
		case "rober_7":
			dialog.text = "La gente della taverna ti può indicare la via per casa sua. Henri è un tipo che si fa notare. Minaccialo di sputтанare tutto e fallo portare la ragazza da me. Quello stesso giorno farò sapere a Levasseur che suo nipote nasconde una vera bellezza nelle segrete cittadine. \nIl mio corriere ti troverà in taverna. Quando non riuscirà a scovare Henri, il governatore andrà alle prigioni con una piccola scorta, e tu avrai un'occasione d'oro per scambiare due parole con lui.";
			link.l1 = "Dove devo consegnare la ragazza?";
			link.l1.go = "rober_8";
		break;
		
		case "rober_8":
			dialog.text = "Digli di portarla lui stesso sulla spiaggia. Gli farò sentire due paroline mentre ci sono...";
			link.l1 = "D'accordo. Affare fatto. Ci vediamo a Tortuga!";
			link.l1.go = "rober_9";
		break;
		
		case "rober_9":
			dialog.text = "Se tutto va secondo i piani, non ci incroceremo mai più. Almeno, lo spero. Addio!";
			link.l1 = "...";
			link.l1.go = "rober_10";
		break;
		
		case "rober_10":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, "Baster_tavern", "goto", "goto2");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			if(CheckAttribute(pchar, "questTemp.Terrapin.Catherina")) AddQuestRecord("Terrapin", "6");
			else AddQuestRecord("Terrapin", "5");
			pchar.questTemp.Terrapin = "tortuga";
			// создаем Тибо
			float fMft = MOD_SKILL_ENEMY_RATE/10;
			sld = GetCharacter(NPC_GenerateCharacter("Tibo", "Tibo", "man", "man", 35, FRANCE, -1, true, "quest"));
			FantomMakeCoolFighter(sld, 35, 100, 100, "blade_18", "pistol4", "bullet", 250);
			GiveItem2Character(sld, "cirass7");
			EquipCharacterbyItem(sld, "cirass7");
			sld.name = "Henry";
			sld.lastname = "Thibaut";
			sld.dialog.FileName = "Quest\Sharlie\Terrapin.c";
			sld.dialog.currentnode = "tibo";
			sld.greeting = "Tibo";
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			TakeNItems(sld, "potion2", 8);
			TakeNItems(sld, "potion3", 5);
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "Tireless");
			SetCharacterPerk(sld, "HardHitter");
			SetCharacterPerk(sld, "Sliding");
			SetCharacterPerk(sld, "BladeDancer");
			SetCharacterPerk(sld, "SwordplayProfessional");
			SetCharacterPerk(sld, "Gunman");
			SetCharacterPerk(sld, "GunProfessional");
			sld.MultiFighter = 1.0+fMft; // мультифайтер
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("Terrapin_LateTortuga", 0, 0, 40, false); // таймер
			}
			else SetFunctionTimerCondition("Terrapin_LateTortuga", 0, 0, 20, false); // таймер
			SetFunctionLocationCondition("Tonzag_AtTortuga", "Tortuga_town", false);
		break;
		
		case "rober_abordage":
			dialog.text = "Argh! Non l’avevo previsto... Sei venuto a prenderti la mia anima, vero compare? Ho fatto tutto come pattuito! Che diavolo?!";
			link.l1 = "Hai una condanna sulla testa, Robert. Mi è stato ordinato di eseguirla. Così sto portando a termine il mio incarico.";
			link.l1.go = "rober_abordage_1";
		break;
		
		case "rober_abordage_1":
			dialog.text = "Demone maledetto! È impossibile! Non poteva scoprire tutto così in fretta! E come diamine ci è riuscito?!";
			link.l1 = "Intendi la Volpe? No. Non mi ha mandato lui. Il colonnello nemmeno sa ancora che hai liberato sua figlia. È il tuo vecchio compare Henry Thibaut che ti vuole morto. Mi ha ingaggiato lui.";
			link.l1.go = "rober_abordage_2";
		break;
		
		case "rober_abordage_2":
			dialog.text = "Quel maledetto pederasta! Dovevo darlo in pasto ai granchi quando stava sul 'Voltigeur'... Quanto ti ha promesso quel bastardo?";
			link.l1 = "Non capita tutti i giorni di scoprir quanto vali sulla tua testa, vero Robert? Thibaut ti valutava un quarto di milione, ma l’ho persuaso che sei merce più pregiata. Ora valghi trecentomila pesos d’argento, amico mio. Non ti senti fortunato?";
			link.l1.go = "rober_abordage_3";
		break;
		
		case "rober_abordage_3":
			dialog.text = "Aspetta un attimo... Facciamo un patto! Ti pagherò di più!";
			link.l1 = "Con quali soldi, Robert? Sono più che certo che stai mentendo. Non hai tutti quei dobloni che Henry mi aveva promesso. E poi, non è nemmeno questo il punto. Se не fosse per un certo dettaglio, avrei già rifiutato la sua proposta di darti la caccia e chiudere i tuoi sporchi traffici con Thibaut.";
			link.l1.go = "rober_abordage_4";
		break;
		
		case "rober_abordage_4":
			dialog.text = "Quale fatto sarebbe?";
			link.l1 = "Hai ucciso Catherine Fox. L’unica colpa di quella povera fanciulla era d’esser nata figlia del colonnello Fox. Disprezzo gli infami vigliacchi come te, che mettono a morte donne indifese! Non intendo trattare con te. Non ci penso nemmeno. Non sprecare fiato.";
			link.l1.go = "rober_abordage_5";
		break;
		
		case "rober_abordage_5":
			PlaySound("Voice\English\sharlie\Rober Marten-03.wav");
			dialog.text = "Maledizione! Che altro potevo fare?! Non potevo certo lasciarla viva e tenerla nascosta per sempre sulla nave! E tu chi sei... furfante, figlio di puttana, assassino, per farmi la morale! Guardati allo specchio! Guarda i tuoi 'metodi'! Non vali più di me!";
			link.l1 = "Basta così. Martene, sguaina la lama! È ora di chiudere i conti.";
			link.l1.go = "rober_abordage_6";
		break;
		
		case "rober_abordage_6":
			dialog.text = "Ci vediamo all’inferno!";
			link.l1 = "...";
			link.l1.go = "rober_abordage_7";
		break;
		
		case "rober_abordage_7":
			DialogExit();
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		// Тибо, вариант без Кати
		case "tibo":
			pchar.quest.Terrapin_LateTortuga.over = "yes"; //снять таймер
			PlaySound("Voice\English\sharlie\Henry Thibault-02.wav");
			dialog.text = "Cosa ci fate in casa mia, signore?";
			link.l1 = TimeGreeting()+", Monsieur Thibaut. Sono qui per conto di un uomo che conosci, il capitano Robert Martene.";
			link.l1.go = "tibo_1";
		break;
		
		case "tibo_1":
			dialog.text = "Mm. E allora? Che vuoi?";
			link.l1 = "Il capitano Martene desidera la vostra gradita compagnia proprio adesso sulla Spiaggia dell’Occhio di Pesce. Ma non da solo. Sarebbe lieto anche di vedere Molly Jones al vostro fianco. Capite cosa intendo?";
			link.l1.go = "tibo_2";
		break;
		
		case "tibo_2":
			PlaySound("Voice\English\sharlie\Henry Thibault-01.wav");
			dialog.text = "Ahimè, messere, non so nulla. Non ho mai sentito parlare di nessuna Molly Jones, e Robert non ha mai avuto motivo di mandarmi un... plenipotenziario che non ho mai visto prima. Per vostra informazione, monsieur, io sono il secondo uomo di quest’isola dopo mio zio, il governatore, dunque...";
			link.l1 = "La vita è una bestia imprevedibile, Henry... Ora sei il secondo uomo dell’isola e fra poche ore potresti marcire in catene nelle segrete... Tutto per la vita di qualcuno che non ti darebbe manco un peso. Hai disobbedito all’ordine di tuo zio, vero, monsieur Thibaut? Dimmi, cos’è che conta di più per te: una sgualdrina o la tua pellaccia?";
			link.l1.go = "tibo_3";
		break;
		
		case "tibo_3":
			dialog.text = "Come osi... Bugiardo! Parli a vanvera, furfante!";
			link.l1 = "Tu, come chiunque altro, sai bene quanto possa essere focoso il temperamento di tuo zio. Levasseur scoprirà che nascondi la ragazza prima che cali il sole. Non chiedermi come Roberto l’abbia saputo, ascolta soltanto le mie parole: è terrorizzato a morte ed è pronto a salpare senza indugio. Non ha nemmeno osato mettere piede in città e mi ha pagato una bella somma perché ti recapitassi questo messaggio.";
			link.l1.go = "tibo_4";
		break;
		
		case "tibo_4":
			dialog.text = "Maledizione... Non può essere!";
			link.l1 = "Tocca a voi, messere. Martene non vi aspetterà più di due ore, sappiatelo. Tiene molto alla sua pellaccia. Se ancora indugia sulle rive di Tortuga e non s'è già dato alla macchia coi fiamminghi, è solo per amicizia.";
			link.l1.go = "tibo_5";
		break;
		
		case "tibo_5":
			dialog.text = "Caramba!   Come diavolo l’ha scoperto mio zio?";
			link.l1 = "Lingue, Henry. Lingue malelingue. Perfino io so che tu e Robert vi siete presi la bella sbarcata dalla briccona inglese catturata dal tuo compare. L’avete nascosta a Levasseur... tsk tsk. Davvero credi che solo io sia al corrente di questa faccenda?";
			link.l1.go = "tibo_6";
		break;
		
		case "tibo_6":
			dialog.text = "Sembra che tu dica la verità, signore. Dì a Martene...";
			link.l1 = "Non credo tu abbia capito, Henry. Martene non ti aspetterà. La tua unica speranza è portar via quella ragazza da qui, la stessa ragione per cui tu e Robert avete il cappio al collo. Corri dove la tieni nascosta, prendila per quelle sue belle manine e portala subito al Voltigeur. Trovala in fretta, e portala ancora più svelto. Tuo zio non saprà una parola da me.";
			link.l1.go = "tibo_7";
		break;
		
		case "tibo_7":
			dialog.text = "Va bene. Così faremo allora. Vi ringrazio per la vostra generosità, signore!";
			link.l1 = "Nessun bisogno di ringraziamenti, monsieur. Il mio lavoro si paga... Voglio solo che tu esca dalla pentola prima che ti bolliscano vivo.";
			link.l1.go = "tibo_8";
		break;
		
		case "tibo_8":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			pchar.quest.Terrapin_wait.win_condition.l1 = "Timer";
			pchar.quest.Terrapin_wait.win_condition.l1.date.hour  = sti(GetTime()+3);
			pchar.quest.Terrapin_wait.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.Terrapin_wait.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.Terrapin_wait.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.Terrapin_wait.win_condition.l2 = "location";
			pchar.quest.Terrapin_wait.win_condition.l2.location = "Tortuga_tavern";
			pchar.quest.Terrapin_wait.function = "Terrapin_SetEnvoy";
			pchar.questTemp.Terrapin = "cave";
			AddQuestRecord("Terrapin", "8");
			SetFunctionTimerCondition("Terrapin_ReturnTibo", 0, 0, 10, false);
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("Terrapin_LateDungeon", 0, 0, 4, false);
			} 
			else SetFunctionTimerCondition("Terrapin_LateDungeon", 0, 0, 2, false);
		break;
		
		// вариант с Кати
		case "tibo_9":
			pchar.quest.Terrapin_LateTortuga.over = "yes"; //снять таймер
			PlaySound("Voice\English\sharlie\Henry Thibault-02.wav");
			dialog.text = "Cosa ci fate qui, signore? Non vi ho invitato in questo luogo.";
			link.l1 = TimeGreeting()+", Monsieur Thibaut. Sono giunto da parte di un uomo che conoscete. Il suo nome è Capitano Robert Martene.";
			link.l1.go = "tibo_10";
		break;
		
		case "tibo_10":
			dialog.text = "Hm. E allora? E quindi?";
			link.l1 = "Il capitano Martene desidera la tua presenza immediatamente sulla Spiaggia dell’Occhio di Pesce. Ma non da solo. Vorrebbe anche vedere Molly Jones insieme a te. Capisci cosa intendo?";
			link.l1.go = "tibo_11";
		break;
		
		case "tibo_11":
			dialog.text = "Ahimè, messere, non so nulla.";
			link.l1 = "Era proprio quello che mi aspettavo da te. Certo, dubito che tu abbia mai avuto l’onore di conoscere la figlia del colonnello Fox, sai bene chi è il colonnello Fox, comandante delle famigerate Volpi di Mare... il terrore dei nemici d’Inghilterra nei Caraibi! Tu e Robert avete smosso un tale vespaio che è un miracolo se ancora non vi siete beccati una puntura! Quella ragazza, Molly Jones, che hai preso dall’inglese e nascosto a Levasseur, altro non è che la figlia del colonnello Fox, Catherine Fox!";
			link.l1.go = "tibo_12";
		break;
		
		case "tibo_12":
			dialog.text = "C-cosa?";
			link.l1 = "Sei diventato pallido come uno spettro, signore. Ora ascoltami bene, Henry, e sta' attento: tu e il tuo compare Robert siete fino al collo nei guai. Da un giorno all'altro, la squadra navale di Cromwell sbarcherà nei Caraibi. Verranno a caccia vostra. La loro nave ammiraglia, da sola, potrebbe ridurre in coriandoli la tua tanto decantata La Roche e l’equipaggio nel giro di un paio d’ore. Che ne dici? Ne valeva la pena attaccare quella brigantina inglese e rapire la figlia di Fox?";
			link.l1.go = "tibo_13";
		break;
		
		case "tibo_13":
			dialog.text = "";
			link.l1 = "Ma non è tutto. Le tue manovre non sono passate inosservate solo a me. Il tuo caro zio governatore verrà presto a sapere che hai infranto i suoi severi ordini e nascosto una fanciulla che quel vecchio satiro avrebbe senz’altro voluto per sé. Che ne pensi, Henry? Cosa credi che ti farà tuo zio? Tu meglio di chiunque altro conosci l’ira che gli brucia nelle vene...";
			link.l1.go = "tibo_14";
		break;
		
		case "tibo_14":
			dialog.text = "Tutte fandonie!";
			link.l1 = "Ah sì? Mio caro Henry, puoi chiedere al tuo compare Martene. È stato lui a mandarmi qui. Levasseur saprà che stai nascondendo la ragazza prima che cali il sole. Non chiedermi come Robert l’abbia scoperto, ascolta solo le mie parole: è spaventato da morire e pronto a salpare all’istante. Non ha nemmeno osato mettere piede in città. Ecco perché mi ha chiesto di portarti questo messaggio.";
			link.l1.go = "tibo_15";
		break;
		
		case "tibo_15":
			dialog.text = "";
			link.l1 = "Martene non ti aspetterà più di due ore. Tiene troppo alla sua pellaccia. Solo per rispetto della tua amicizia ancora bazzica sulle spiagge di Tortuga, invece di squagliarsela tra gli olandesi. Ma quel poveraccio di Robert nemmeno immagina chi sia in realtà Molly Jones. Sapete, voi due mi lasciate davvero basito con la vostra straordinaria ignoranza su moda e fattezze femminili! Non riuscireste a distinguere una dama dal suo servetto nemmeno sotto tortura!";
			link.l1.go = "tibo_16";
		break;
		
		case "tibo_16":
			dialog.text = "Cosa vuoi, marinaio?";
			link.l1 = "Finalmente qualche parola saggia dal nostro giovane sbruffone! Va bene, Thibaut: vai subito dove la tieni nascosta, prendila con delicatezza per le sue manine candide, e portala in fretta giù alla Spiaggia dell’Occhio di Pesce dove c’è il Voltigeur di Martene. Digli che i tuoi piani sono cambiati...";
			link.l1.go = "tibo_17";
		break;
		
		case "tibo_17":
			dialog.text = "";
			link.l1 = "Martene deve mantenere la sua parola con me, e non osi nemmeno pensare di portare la ragazza sulla sua nave. Lei rimarrà sulla spiaggia ad aspettarmi. Di' a Robert che se non rispetta i patti, o porta via Catherine, o se solo un capello si farà male sulla sua bella testolina, passerò il resto dei miei giorni a cercarla. E quando la troverò, la consegnerò viva al colonnello Fox... Ma per voi due... vi riporterò a pezzi. Ah, e questo vale anche per te, Thibaut.";
			link.l1.go = "tibo_18";
		break;
		
		case "tibo_18":
			dialog.text = "";
			link.l1 = "Chi sono io e quali siano le mie possibilità, potete chiederlo a Robert. Lui lo sa benissimo. Se farete come vi dico, ci guadagneremo tutti: Robert continuerà a fare il suo mestiere di pirata, voi vi terrete tutti i vostri privilegi e incasserete l’eredità del caro vecchio zio quando tirerà le cuoia. Quanto a me... non rimarrò certo a bocca asciutta. Tutto chiaro?";
			link.l1.go = "tibo_19";
		break;
		
		case "tibo_19":
			PlaySound("Voice\English\sharlie\Henry Thibault-03.wav");
			dialog.text = "Preferirei bruciare nelle fiamme eterne dell’inferno piuttosto che piegarmi ai tuoi comandi... "+GetFullName(pchar)+"! Come ho fatto a non riconoscerti subito? Assassino! Non hai certo intenzione di lasciare vivi né me né Robert! Le tue 'maniere' sono famigerate! Non darò mai Molly... né Catherine, a una carogna come te! Da Tortuga non esci vivo, bastardo!";
			link.l1 = "...";
			link.l1.go = "tibo_20";
		break;
		
		case "tibo_20":
			dialog.text = "";
			link.l1 = "Fermati, codardo!";
			link.l1.go = "tibo_21"; // patch
		break;
		
		case "tibo_21":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload_window", "none", "", "", "Terrapin_LevasserRoomEnter", 5); // patch
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload_window");
			LAi_RemoveLoginTime(npchar);
		break;
		
		case "tibo_22":
			pchar.quest.Terrapin_TiboCallOver.over = "yes"; //снять прерывание
			pchar.quest.Terrapin_tibo_call.over = "yes"; //снять прерывание
			PlaySound("Voice\English\sharlie\Henry Thibault-04.wav");
			dialog.text = "Ebbene, finalmente! Capitano "+GetFullName(pchar)+", Sono davvero lieto che tu sia arrivato. Entra pure, accomodati. Vuoi qualcosa da bere? Ho una proposta d'affari piuttosto redditizia per te, amico mio...";
			link.l1 = "Ma guarda un po', oggi siete proprio di buon umore, Monsieur Thibaut... Non perdiamo tempo a cincischiare. Andiamo dritti al sodo.";
			link.l1.go = "tibo_23";
		break;
		
		case "tibo_23":
			dialog.text = "La faccenda riguarda il mio ex amico e compare che tu conosci come Robert Martene, già capitano del galeone 'Voltigeur'...";
			link.l1 = "Dunque, tu e Robert non siete più compari? Che storia intrigante.";
			link.l1.go = "tibo_24";
		break;
		
		case "tibo_24":
			dialog.text = "Capitano, vi prego, ascoltate le mie ragioni per chiedere il vostro aiuto e tutto vi sarà chiaro. Come ben sapete, Martene ha ingaggiato battaglia con una brigantina inglese e ha preso prigioniera una donna d’Inghilterra, una servetta chiamata Molly Jones, la causa di tutto questo pasticcio.";
			link.l1 = "Certo, lo so. Da quel che ho capito, hai seguito i miei consigli e condotto la ragazza sulla nave di Martene?";
			link.l1.go = "tibo_25";
		break;
		
		case "tibo_25":
			dialog.text = "Sì, l’ho fatto. Ma me ne pento ogni singolo giorno. Sappi che Molly è una ragazza davvero incantevole e splendida, mai visto nessuna come lei. Devo ammetterlo, mi sono innamorato. E anche a lei piacevo, me l’ha detto chiaro e tondo! Non potevo lasciare che mio zio se la portasse via, quel vecchio porco. Quando l’accompagnavo al ‘Voltigeur’, speravo che lo zio si sarebbe calmato non appena avesse capito che nessuno gli nascondeva ragazze, il satiro. Poi Robert l’avrebbe riportata a Tortuga, così io avrei potuto sistemarla a casa mia senza rischi. Questo era il patto che avevo stretto con Martene. Ma le cose sono andate diversamente. Quando ho scoperto che lo zio era stato ammazzato, non c’era più motivo di tenere nascosta Molly, così ho aspettato pazientemente che il ‘Voltigeur’ arrivasse con lei a bordo.";
			link.l1 = "È arrivata?";
			link.l1.go = "tibo_26";
		break;
		
		case "tibo_26":
			dialog.text = "Sì. Purtroppo, Molly non era sulla nave. Robert era sconvolto, come se avesse incrociato il diavolo in persona. Durante la sua breve spedizione, ha scoperto un dettaglio terribile: la ragazza, Molly, non era affatto Molly Jones, ma Catherine Fox! La figlia del colonnello Fox in persona, comandante delle Volpi di Mare, il reggimento scelto dei marines inglesi! Capisci cosa significa, vero?";
			link.l1 = "Maledizione ai miei occhi, guarda un po'! Allora è certo che Robert ha di che tremare. Ma come diavolo si è potuti arrivare a questo?";
			link.l1.go = "tibo_27";
		break;
		
		case "tibo_27":
			dialog.text = "Quando Caterina fu fatta prigioniera, nascose di proposito la sua vera identità fingendosi Molly Jones, una servetta morta durante l’abbordaggio. Temeva che Martene scoprisse chi fosse davvero. E riuscì a ingannarlo. Ma durante l’ultimo viaggio, in qualche modo Roberto scoprì la sua vera natura. Disse di aver trovato alcune sue lettere, o dei documenti...";
			link.l1 = "E dove si trova la fanciulla adesso, se non è salita a bordo del 'Voltigeur'?";
			link.l1.go = "tibo_28";
		break;
		
		case "tibo_28":
			dialog.text = "È morta. Spaventata dalla punizione imminente di Fox per l’attacco alla goletta inglese, Martene ha deciso di far sparire nell’acqua l’ultima prova rimasta. Era l’ultima testimone del suo assalto all’‘Albatross’.";
			link.l1 = "Allora tanto valeva che facesse fuori tutta la sua ciurma... Proprio come Fernand Luc. Altrimenti, un bel giorno si uбрiacano e straparlano in qualche bettola...";
			link.l1.go = "tibo_29";
		break;
		
		case "tibo_29":
			dialog.text = "Sente che tutto il suo equipaggio gli ha giurato fedeltà col sangue. Forse in parte ha ragione. Ma io conosco il colonnello Fox! Quello continuerà a scavare finché avrà fiato in corpo, pur di scoprire chi ha rapito sua figlia!";
			link.l1 = "Non ne dubito affatto. Soprattutto dopo che un pirata francese ha fatto fuori sua moglie. Ora anche la figlia... Ma, a proposito, siete proprio sicuro, monsieur, che Catherine sia davvero morta? Magari Robert l’ha nascosta da qualche parte, lontano dai vostri occhi.";
			link.l1.go = "tibo_30";
		break;
		
		case "tibo_30":
			dialog.text = "Sono sicuro. Ho parlato con un marinaio della 'Voltigeur'. Gli ho creduto. Ha visto coi suoi occhi come le hanno tagliato la gola, poi le hanno legato una palla di cannone ai piedi e l'hanno gettata in mare.";
			link.l1 = "Dio in cielo! Quella povera donna... che diavolo vuoi da me, Henry?";
			link.l1.go = "tibo_31";
		break;
		
		case "tibo_31":
			dialog.text = "Non chiudo occhio da quel giorno. Davanti agli occhi ho sempre Molly... Anzi, Catherine. L’ho condotta dritta alla tomba, io."+GetFullName(pchar)+"Non potrò mai perdonarmi per questo. E oltre a tutto, non mi faccio illusioni su Fox. Quell’uomo non si lascia mai andare, e dubito perfino che chiuda occhio la notte. Prima o poi, troverà la pista di Martene, farà cantare qualcuno, e quando scoprirà chi ha ucciso sua figlia, sarà l’inferno. Chiunque sia stato coinvolto, anche solo di краем, la pagherà cara.";
			link.l1 = "Questo mi comprende pure me.";
			link.l1.go = "tibo_32";
		break;
		
		case "tibo_32":
			dialog.text = "Aye, anch'io. Ecco perché voglio che tu trovi Martene prima che ci arrivi la Volpe. Scova quel bastardo e mandalo all’inferno senza fretta, fallo soffrire se puoi. Per la povera Catherine. Quando avrai finito, taglia quel suo anello grosso insieme al dito e portamelo come prova.\nConosco troppo bene quel suo dito storto e quell’anello. Se lo farai, ti pagherò un quarto di milione in argento.";
			link.l1 = "Sembra proprio che tu abbia ricevuto una bella eredità dal tuo caro zio che riposa in pace, eh? Dimmi, Henry, perché mai hai deciso di chiedere il mio aiuto in questa faccenda?";
			link.l1.go = "tibo_33";
		break;
		
		case "tibo_33":
			dialog.text = "Perché anch’io ho scoperto alcune cosette su di te, "+GetFullName(pchar)+"È stato facile, sei un uomo famoso. Nessuno sa davvero per chi lavori: forse per de Poincy, forse per gli olandesi, gli inglesi, o per quel barone Jan Svenson... Ma una cosa è certa: prendi incarichi delicati, in silenzio, e li porti a termine. E vieni pagato profumatamente per questo. E la cosa migliore è che non hai legami con gli spagnoli.\nDopotutto, hai partecipato anche a quegli eventi che mi hanno permesso di ereditare la fortuna di mio zio. Non negarlo... Un quarto di milione è un bel gruzzolo. Ti dirò dove trovare Martene. Dovrai solo intercettare la sua nave e abbordarla.";
			link.l1 = "Altri centomila e mi occupo io di Martene per te.";
			link.l1.go = "tibo_34";
			link.l2 = "Ahimè, Monsieur Thibaut, dovrete cavarvela con i vostri guai con Martene e il colonnello Fox senza il mio intervento. Da parte mia, vi prometto che non farò giungere alcuna notizia al colonnello riguardo al destino di sua figlia e di chi è responsabile della sua morte. Vi auguro ogni bene, messere.";
			link.l2.go = "tibo_exit";
		break;
		
		case "tibo_exit":
			DialogExit();
			AddQuestRecord("Sharlie", "26");
			NextDiag.CurrentNode = "tibo_over";
		break;
		
		case "tibo_34":
			dialog.text = "Signore, abbiate timor di Dio... Non ho milioni nascosti nei forzieri, credetemi! Capisco che i vostri servigi costano, ecco perché vi ho offerto subito duecentocinquantamila... Va bene... D’accordo, aggiungo altri cinquantamila d’oro. Non posso darvi altro!";
			link.l1 = "D'accordo. Abbiamo un accordo, allora. Dove hai visto Martene l'ultima volta?";
			link.l1.go = "tibo_35";
		break;
		
		case "tibo_35":
			dialog.text = "È salpato verso sud, fino alla Terraferma spagnola, a Caracas, e lì ha trovato il modo di farsi ricevere da Don Diego Francisco de Kerres, il governatore. Pare che gli abbia allungato qualche doblone, perché Don Diego gli ha concesso la protezione della corona spagnola. Ha venduto il 'Voltigeur' e adesso comanda il pesante galeone 'Infanta'. Doveva avere un bel gruzzolo da parte, se ha potuto ungere le mani al governatore e comprare, allestire una nave da guerra simile.\nOra solcherà il mare da Caracas a Santo Domingo, a bordo del suo nuovo vascello, come parte di una squadra spagnola. Questo è tutto ciò che la mia spia ha potuto scoprire. L’unico modo per mettere le mani su Martene è raggiungere quella squadra spagnola prima che arrivi a destinazione.\nSe toccano Santo Domingo, la partita è chiusa. E poi? Nessuno saprà dove finirà Robert. Sparirà come una biscia in una tana, e addio a ogni traccia.";
			link.l1 = "Capito. Li intercetterò io.";
			link.l1.go = "tibo_36";
		break;
		
		case "tibo_36":
			dialog.text = "E non ti scordare il dito con l’anello! È condizione imprescindibile del nostro patto! Devo essere dannatamente sicuro che Robert sia morto!";
			link.l1 = "D'accordo. Non perdiamo tempo, salpo subito!";
			link.l1.go = "tibo_37";
		break;
		
		case "tibo_37":
			DialogExit();
			AddQuestRecord("Sharlie", "27");
			Terrapin_CreateRoberConvoy();
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			NextDiag.CurrentNode = "tibo_time";
		break;
		
		case "tibo_time":
			dialog.text = "Martene appesta ancora i Caraibi con la sua lurida presenza, capitano?";
			link.l1 = "Non gli resta molto tempo!";
			link.l1.go = "exit";
			NextDiag.TempNode = "tibo_time";
		break;
		
		case "tibo_38":
			dialog.text = "Martene sta ammorbando i Caraibi con la sua lurida presenza, capitano?";
			link.l1 = "Non più. Puoi smettere di temere il colonnello Fox, e la tua Catherine è stata vendicata. Ecco la tua prova.";
			link.l1.go = "tibo_39";
		break;
		
		case "tibo_39":
			RemoveItems(pchar, "finger", 1);
			dialog.text = "Sì... Questo è proprio il dito di Martene, senza ombra di dubbio. Non smetti mai di sorprendermi, Capitano "+GetFullName(pchar)+"! Meriti davvero la fama che ti attribuiscono.";
			link.l1 = "Passiamo al pagamento, che ne dici, Thibaut?";
			link.l1.go = "tibo_40";
		break;
		
		case "tibo_40":
			AddMoneyToCharacter(pchar, 250000);
			TakeNItems(pchar, "gold_dublon", 500);
			Log_Info("You've received 500 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Tutto è pronto. Ecco, prendi la tua ricompensa.";
			link.l1 = "La mia riconoscenza. Sono lieto che tu sia riuscito a preparare tutto in anticipo. Ebbene, Henry, spero che tu non ti cacci più in simili guai e che la prossima volta scelga amici migliori. Buona fortuna!";
			link.l1.go = "tibo_41";
		break;
		
		case "tibo_41":
			dialog.text = "Grazie per il vostro aiuto, capitano! Vi raccomanderò a tutti i miei amici. Buona fortuna!";
			link.l1 = "...";
			link.l1.go = "tibo_42";
		break;
		
		case "tibo_42":
			DialogExit();
			AddQuestRecord("Sharlie", "31");
			NextDiag.CurrentNode = "tibo_stop";
		break;
		
		case "tibo_stop":
			dialog.text = "Sì, monsieur "+GetFullName(pchar)+" ? Avete qualche affare con me?";
			link.l1 = "No, monsieur Thibaut. Ho solo pensato di fare una capatina. Addio!";
			link.l1.go = "exit";
			NextDiag.TempNode = "tibo_stop";
		break;
		
		case "tibo_late":
			dialog.text = "Ah, "+GetFullName(pchar)+"...Avanti, che diavolo ci metti così tanto! E ora, chi può sapere dove diamine sia finito Robert Martene?! Se il colonnello Fox scopre tutto quanto, mi sa che sarò nei guai fino al collo...";
			link.l1 = "Capisco. Sono arrivato troppo tardi. Le mie scuse, Monsieur Thibaut, ma sono stato trattenuto da faccende assai urgenti. Non intendo farle perdere altro tempo. Addio.";
			link.l1.go = "exit";
			NextDiag.TempNode = "tibo_over";
		break;
		
		case "tibo_over":
			dialog.text = "Cosa desideri, "+GetFullName(pchar)+"? Non ho tempo per chiacchiere. Ho faccende ben più grosse da sbrigare. Devo trovare Martene prima che ci arrivi quella volpe...";
			link.l1 = "Sì, sì. Sto arrivando.";
			link.l1.go = "exit";
			NextDiag.TempNode = "tibo_over";
		break;
		
		// посланник от Мартэна
		case "envoy":
			dialog.text = "Siete voi il Capitano "+GetFullName(pchar)+"?";
			link.l1 = "Sei capitato dall’uomo giusto, compare. Sono tutto orecchi.";
			link.l1.go = "envoy_1";
		break;
		
		case "envoy_1":
			dialog.text = "Il tuo debitore mi ha incaricato di dirti che l’affare è fatto e il pesce abboccherà all’amo entro meno d’un’ora. Muoviti, dunque.";
			link.l1 = "Capisco. Grazie!";
			link.l1.go = "envoy_2";
		break;
		
		case "envoy_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			AddQuestRecord("Terrapin", "9");
			pchar.quest.Terrapin_cave.win_condition.l1 = "Timer";
			pchar.quest.Terrapin_cave.win_condition.l1.date.hour  = sti(GetTime()+1);
			pchar.quest.Terrapin_cave.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.Terrapin_cave.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.Terrapin_cave.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.Terrapin_cave.win_condition.l2 = "location";
			pchar.quest.Terrapin_cave.win_condition.l2.location = "Tortuga_cave";
			pchar.quest.Terrapin_cave.function = "Terrapin_LevasserInCave";
		break;
		
		// Левассер в пещере
		case "levasser_cave":
			pchar.quest.Terrapin_LateDungeon.over = "yes"; //снять таймер
			dialog.text = "Che diavolo ci fai a gironzolare da queste parti? Chi sei tu? Rispondimi subito!";
			link.l1 = "Chi diavolo sei tu e perché mi fai domande così idiote?";
			link.l1.go = "levasser_cave_1";
		break;
		
		case "levasser_cave_1":
			dialog.text = "Cosa?! Piccolo moccioso arrogante! Chi sono io? Sono il governatore di quest’isola, François Levasseur, Signore di Renet de Boidouflet de Lettre! E tutto ciò che si trova su quest’isola è sotto la mia giurisdizione! Compreso te, finché calpesti il mio suolo, cucciolo!";
			link.l1 = "Ebbene, ebbene... Il lupo cattivo in persona, eh? Ti sei perso, Levasseur, Signore di Renet o come diavolo ti chiami. Il tuo tempo è finito. Per ordine del governatore generale François Longvillier de Poincy sei stato destituito e condannato a morte sul momento! Sono io il tuo giudice e il tuo boia, tutto in uno! Hai qualche ultima parola da sputare?";
			link.l1.go = "levasser_cave_2";
		break;
		
		case "levasser_cave_2":
			dialog.text = "";
			link.l1 = "Suppongo che non ti arrenderai e chiedere pietà non ti servirà a nulla, dunque forza, sfodera la lama!";
			link.l1.go = "levasser_cave_3";
		break;
		
		case "levasser_cave_3":
			dialog.text = "Maledizione! È un agente di de Poincy! Sguainate le spade! Ammazzatelo!";
			link.l1 = "Lasciateci danzare.";
			link.l1.go = "levasser_cave_4";
		break;
		
		case "levasser_cave_4":
			LAi_LocationFightDisable(&Locations[FindLocation("Tortuga_cave")], false);//разрешить драться
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=2; i<=4; i++)
			{
				sld = characterFromId("TerrapinGuard"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			// подкрепление
			int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+7;
			int iScl = 30 + 2*sti(pchar.rank);
			for (i=5; i<=9; i++)
			{		
				sld = GetCharacter(NPC_GenerateCharacter("TerrapinGuard"+i, "citiz_5"+i, "man", "man", iRank, PIRATE, -1, true, "quest"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_19", "pistol5", "bullet", iScl*2+50);
				ChangeCharacterAddressGroup(sld, "Tortuga_cave", "goto", "goto"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Terrapin_LevasserCaveDied");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// Левассер в комнате таверны
		case "levasser_room":
			dialog.text = "Che diavolo ci fai qui? Chi sei tu? Rispondimi subito!";
			link.l1 = "Chi l’avrebbe mai detto! Questa proprio non me l’aspettavo... Monsieur Levasseur in persona, suppongo?";
			link.l1.go = "levasser_room_1";
		break;
		
		case "levasser_room_1":
			dialog.text = "Sì, sono io il governatore di questa isola, François Levasseur, Signore di Renet de Boidouflet de Lettre! E tutto ciò che si trova su quest'isola è sotto la mia giurisdizione! Compreso te, finché cammini sul mio territorio, furfante! Rispondi alle domande! Sergente, chiudi questa porta. Quest’uomo trama qualcosa di losco!";
			link.l1 = "Ma che perspicacia la vostra, monsieur Levasseur, Signore di Renet-di-quel-che-è. Dubito che la mia comparsa vi rallegri. Per ordine del governatore generale François Longvillier de Poincy, siete destituito dal vostro incarico e condannato a morte immediata! Io sono insieme il vostro giudice e il vostro carnefice!";
			link.l1.go = "levasser_room_2";
		break;
		
		case "levasser_room_2":
			dialog.text = "";
			link.l1 = "Suppongo che non intendi arrenderti, e pregarmi per la pietà non ti servirà a nulla, quindi forza, tira fuori la lama! Sei il mio incarico, niente di personale. Solo al servizio della Corona, ah! Sergente, ti sconsiglio di immischiarti mentre eseguo gli ordini del governatore generale!";
			link.l1.go = "levasser_room_3";
		break;
		
		case "levasser_room_3":
			dialog.text = "Non dategli retta, sergente! È una spia spagnola! Ammazzatelo! Guardie, aiuto! Ci sono spagnoli qui!";
			link.l1 = "In verità, in Spagna non ci sono mai stato, solo a Narbona.";
			link.l1.go = "levasser_room_4";
		break;
		
		case "levasser_room_4":
			LAi_LocationFightDisable(&Locations[FindLocation("Tortuga_tavern_upstairs")], false);//разрешить драться
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("TerrapinGuard"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Terrapin_LevasserRoomDied");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// девушка на балконе
		case "roof_girl":
			dialog.text = "Ahi! Aiutatemi! Soldati!";
			link.l1 = "Stai zitto, sciocco! Se non urli, non ti succederà nulla!";
			link.l1.go = "roof_girl_1";
		break;
		
		case "roof_girl_1":
			dialog.text = "Non uccidermi!";
			link.l1 = "Non fare il furbo! Un uomo è passato di qui dieci minuti fa, vestito come un signore. Dove si nasconde? E non osare dirmi che non l’hai visto!";
			link.l1.go = "roof_girl_2";
		break;
		
		case "roof_girl_2":
			dialog.text = "Monsieur Thibaut?";
			link.l1 = "E allora, dunque lo conosci! Dove si è cacciato? Hai intenzione di parlare o devo scuoterti la testa per farla funzionare?";
			link.l1.go = "roof_girl_3";
		break;
		
		case "roof_girl_3":
			dialog.text = "Oh no, vi prego, non fatemi del male! Monsieur Thibaut è scappato, da quella parte verso il mare. E si è buttato giù dalla gru dritto nell’acqua. Sarà pure crepato, è così alto lassù...";
			link.l1 = "Non credo proprio. Non è il tipo da farla finita. Dovresti entrare. Stanotte non è sicuro starsene qui fuori...";
			link.l1.go = "roof_girl_4";
		break;
		
		case "roof_girl_4":
			dialog.text = "Ahi! Ahia! Non sparate!";
			link.l1 = "Cosa?!";
			link.l1.go = "roof_girl_5";
		break;
		
		case "roof_girl_5":
			DialogExit();
			LAi_SetActorType(pchar);
			PlaySound("People Fight\MushketShot.wav");
			DoQuestCheckDelay("Terrapin_GirlShot", 1.0);
		break;
		
		// Кати
		case "kathy":
			PlaySound("Voice\English\Armo02.wav");
			dialog.text = "Chi sei tu? Sei venuto ad ammazzarmi o... peggio?";
			link.l1 = "Niente affatto, madame. Riporterò te, Catherine Fox, da tuo padre a St. John's. Se poi lui ti darà una sculacciata per avergli disobbedito, la mia colpa si ripeterà. Tuttavia, spero che il colonnello sarà lieto di rivedere la figlia viva, nonostante tutti gli affanni che gli hai procurato.";
			link.l1.go = "kathy_1";
		break;
		
		case "kathy_1":
			dialog.text = "Grazie al cielo! Devo star sognando! Non sai chi sono io? Sei francese e cattolico, eppure hai deciso di venire qui per salvarmi dalle grinfie dei miei stessi compatrioti? Hai rischiato la tua pelle solo per la figlia del colonnello Fox?";
			link.l1 = "La mia ragione iniziale per trovarmi qui a Tortuga era ben altra. Ma non potevo certo lasciar una dama così bella nelle grinfie di quei cani ladri e tagliagole.";
			link.l1.go = "kathy_2";
		break;
		
		case "kathy_2":
			dialog.text = "Voi siete un gentiluomo nobile! Come vi chiamate, monsieur?";
			link.l1 = ""+GetFullName(pchar)+". Capitano "+GetFullName(pchar)+".";
			link.l1.go = "kathy_3";
		break;
		
		case "kathy_3":
			dialog.text = "Dimmi, capitano, mi porterai davvero da mio padre a St. John's?";
			link.l1 = "Sì, anche se non sopporta troppo i francesi. Beh, gli ricorderò che pure tra gli inglesi non mancano i farabutti, perfino tra gli ufficiali! Ne ho visto almeno uno coi miei occhi... Si chiamava Richard Fleetwood.";
			link.l1.go = "kathy_4";
		break;
		
		case "kathy_4":
			dialog.text = "Se riusciamo ad arrivare ad Antigua, farò di tutto per convincere mio padre che tra i francesi ci son veri cavalieri.";
			link.l1 = "Lo gradirei assai... D’accordo, spero che i miei angeli custodi abbiano seguito le mie orme sui tetti della città e già si diano da fare per la nostra venuta.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Terrapin_OwrInGrot");
		break;
		
		case "kathy_5":
			PlaySound("Voice\English\Armo01.wav");
			dialog.text = "Non avrei mai creduto che avresti mantenuto la promessa fino ad ora! Quanti orrori e infamie mi sono capitati di recente... Ti ringrazio, capitano, per avermi fatto tornare la fede nell’onore e nella gente. Dovresti andare a trovare mio padre appena puoi!   Lui rispetta uomini come te. E poco importa che tu sia francese. Farò di tutto per convincere mio padre a mutare opinione sulla tua nazione.";
			link.l1 = "Grazie, Catherine. Forse approfitterò della tua gentile offerta.";
			link.l1.go = "kathy_6";
		break;
		
		case "kathy_6":
			dialog.text = "Spero proprio che lo farete, capitano. Vi sono immensamente grato ancora una volta per ciò che avete fatto per me. Non lo dimenticherò mai.";
			link.l1 = "Avanti, sbrigati da tuo padre. Sarà al settimo cielo nel vederti. Forse è già tornato dai campi. Beh, comunque è ora che io vada. Addio!";
			link.l1.go = "kathy_7";
		break;
		
		case "kathy_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "OpenTheDoors", 10.0);
			npchar.lifeday = 0;
			SetFunctionTimerCondition("Terrapin_ReturnFox", 0, 0, 3, false); // Фокса на место
			pchar.questTemp.Terrapin_KathyReward = "true"; // награда за спасение Кати 160912
		break;
		
		// наш матрос
		case "terrapin_grot":
			dialog.text = "Eccoti qua, capitano! Ci hai fatto crepare d’ansia! Una corsa così sui tetti di tegole e poi quel salto da quell’altezza da far rizzare i peli... Per tutti i santi, temevamo che non ne saresti uscito vivo... Bentornato a bordo, capitano, la scialuppa è pronta!";
			link.l1 = "Perfetto. Caterina, seguimi!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Terrapin_GotoShip");
		break;
		
		case "tibo_sailor":
			dialog.text = "Salve, monsieur. Siete voi il capitano "+GetFullName(pchar)+"?";
			link.l1 = "Aye, son proprio io. Che succede, per mille balene?";
			link.l1.go = "tibo_sailor_1";
		break;
		
		case "tibo_sailor_1":
			dialog.text = "Uff, t’ho raggiunto per un pelo... Vengo a te per conto di un gentiluomo che conosci, di nome Henry Thibaut.";
			link.l1 = "Enrico? E che vuole, lui? Forse spartire la sua allegria per quell’eredità piovutagli addosso dopo che il caro zio s’è tirato le cuoia?";
			link.l1.go = "tibo_sailor_2";
		break;
		
		case "tibo_sailor_2":
			dialog.text = "Monsieur Thibaut ti ha mandato a chiamare con grande urgenza: vuole che tu venga alla sua villa a Tortuga il prima possibile. Pare abbia un lavoro ben pagato per te. Mi ha anche detto di farti un nome: Robert Martene. Dovrebbe accenderti la curiosità, no?";
			link.l1 = "Ah sì? E da dove gli è saltata fuori quest’idea, a Henry?";
			link.l1.go = "tibo_sailor_3";
		break;
		
		case "tibo_sailor_3":
			dialog.text = "Inoltre, se questo ancora non ti ha convinto a fargli visita, mi ha anche chiesto di aggiungere quanto segue: 'Robert Martene deve crepare'.";
			link.l1 = "D'accordo, d'accordo... Ora la faccenda si fa intrigante. Due amici per la pelle che si sono messi a beccarsi... Come dici tu, proverò a fare visita a Henry appena ne avrò l'occasione.";
			link.l1.go = "tibo_sailor_4";
		break;
		
		case "tibo_sailor_4":
			dialog.text = "Monsieur Thibaut ti ha raccomandato di non tardare con la visita. ‘Il pesce sfuggirà alla rete tra dieci giorni’, così ha detto lui...";
			link.l1 = "Lui e Robert parlano allo stesso modo. Va bene, farò visita a Henry.";
			link.l1.go = "tibo_sailor_5";
		break;
		
		case "tibo_sailor_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 10.0);
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("Terrapin_TiboCallOver", 0, 0, 10, false);
			AddQuestRecord("Sharlie", "25");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
